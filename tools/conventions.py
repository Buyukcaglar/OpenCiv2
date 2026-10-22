#!/usr/bin/env python3
"""Infer calling conventions for every function in civ2.exe.

MSVC 4.2 /Od code makes this easy to read off the machine code:
  - a function that reads ECX before writing it receives `this` in ECX
    (__thiscall); in /Od code it is spilled immediately: mov [ebp-N], ecx
  - `ret N` means the callee pops N bytes of arguments (__stdcall/__thiscall)
  - plain `ret` means caller cleanup (__cdecl)
Also flags other registers read before written (EAX/EDX/EBX/ESI/EDI) which
indicate non-standard register arguments (hand-written asm, _chkstk users).

Output: re/conventions.tsv  entry  cc  stack_bytes  reg_inputs
"""
import csv, sys
import pefile, capstone
from capstone import x86
import os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import paths  # noqa: E402  (the game's directory)

pe = pefile.PE(paths.game_file('civ2.exe'))
img = pe.get_memory_mapped_image()
BASE = 0x400000
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
md.detail = True

CHKSTK = 0x5f35f0          # __chkstk
CRT_START = 0x5f1b80
REGS = {'eax', 'ecx', 'edx', 'ebx', 'esi', 'edi'}
SUB = {'al': 'eax', 'ah': 'eax', 'ax': 'eax', 'cl': 'ecx', 'ch': 'ecx', 'cx': 'ecx',
       'dl': 'edx', 'dh': 'edx', 'dx': 'edx', 'bl': 'ebx', 'bh': 'ebx', 'bx': 'ebx',
       'si': 'esi', 'di': 'edi'}


def norm(r):
    return SUB.get(r, r)


def analyze(entry, size, extent):
    code = img[entry - BASE: entry - BASE + max(size, 16)]
    written, inputs = set(), set()
    rets = set()
    # Linear scan of the entry block for register inputs.
    for ins in md.disasm(code, entry):
        if ins.mnemonic == 'call' and ins.op_str == hex(CHKSTK):
            # Stack probe for large frames: preserves ECX (and consumes EAX,
            # which the prologue itself set).
            written.add('eax')
            continue
        if ins.mnemonic in ('call', 'jmp') or ins.mnemonic.startswith('j') or ins.mnemonic.startswith('ret'):
            # A call clobbers eax/ecx/edx; stop looking for inputs at first branch.
            break
        rd, wr = ins.regs_access()
        if ins.mnemonic in ('push',) and ins.op_str in REGS and ins.op_str in ('ebx', 'esi', 'edi', 'ebp'):
            continue  # callee-saved register spill is not an input use
        if ins.mnemonic == 'xor' and len(ins.operands) == 2 and ins.op_str.split(', ')[0] == ins.op_str.split(', ')[-1]:
            for r in wr:
                written.add(norm(ins.reg_name(r)))
            continue
        for r in rd:
            n = norm(ins.reg_name(r))
            if n in REGS and n not in written:
                inputs.add(n)
        for r in wr:
            written.add(norm(ins.reg_name(r)))
    rets = traverse_rets(entry)
    return inputs, rets


ENTRIES = set()
TEXT_END = 0x619000 + BASE - 0x400000 + 0x400000


def traverse_rets(entry):
    """Recursive descent from entry; returns the set of `ret N` operands.

    Follows direct jumps and conditional branches, and MSVC switch tables
    (jmp [reg*4 + table]) whose entries point back into the function.
    """
    rets, seen, work = set(), set(), [entry]
    lo, hi = 0x401000, 0x619000
    while work:
        pc = work.pop()
        first = True
        while lo <= pc < hi and pc not in seen and (first or pc not in ENTRIES):
            first = False
            seen.add(pc)
            try:
                ins = next(md.disasm(img[pc - BASE:pc - BASE + 16], pc, count=1))
            except StopIteration:
                break
            m = ins.mnemonic
            if m == 'ret':
                rets.add(int(ins.op_str, 0) if ins.op_str else 0)
                break
            if m == 'jmp':
                op = ins.operands[0]
                if op.type == x86.X86_OP_IMM:
                    if op.imm in ENTRIES and op.imm != entry:
                        break          # tail jump into another function
                    pc = op.imm
                    first = True
                    continue
                if op.type == x86.X86_OP_MEM and op.mem.base == 0 and op.mem.scale == 4:
                    t = op.mem.disp & 0xffffffff
                    for k in range(512):
                        off = t - BASE + 4 * k
                        tgt = int.from_bytes(img[off:off + 4], 'little')
                        if not (entry <= tgt < entry + 0x20000):
                            break
                        work.append(tgt)
                break
            if m.startswith('j') or m in ('loop', 'loope', 'loopne', 'jecxz'):
                op = ins.operands[0]
                if op.type == x86.X86_OP_IMM and op.imm not in ENTRIES:
                    work.append(op.imm)
            if m == 'push' and ins.operands[0].type == x86.X86_OP_IMM and entry < ins.operands[0].imm < entry + 0x20000 \
                    and ins.operands[0].imm not in ENTRIES:
                # __try/__finally: `push continuation; jmp finally` makes the
                # finally block's plain `ret` return into this function.
                work.append(ins.operands[0].imm)
            if m == 'int3' or m == 'hlt':
                break
            pc += ins.size
    return rets


def main():
    rows = [r for r in csv.DictReader(open('re/functions.tsv'), delimiter='\t') if not r['thunk_target']]
    entries = sorted(int(r['entry'], 16) for r in csv.DictReader(open('re/functions.tsv'), delimiter='\t'))
    ENTRIES.update(entries)
    nxt = {a: b for a, b in zip(entries, entries[1:] + [entries[-1] + 0x1000])}
    out = open('re/conventions.tsv', 'w')
    out.write('entry\tcc\tstack_bytes\treg_inputs\n')
    stats = {}
    for r in rows:
        entry = int(r['entry'], 16)
        inputs, rets = analyze(entry, int(r['size']), nxt[entry] - entry)
        if len(rets) > 1:
            print('warning: multiple ret forms', r['entry'], rets, file=sys.stderr)
        purge = max(rets) if rets else -1
        if purge < 0 and r['purge'] not in ('', '2147483647'):
            purge = int(r['purge'])       # no ret reachable (asm helpers): trust Ghidra
        if 'ecx' in inputs and entry < CRT_START:
            cc = '__thiscall'     # (the C runtime has no member functions; its asm reads ECX freely)
        elif purge > 0:
            cc = '__stdcall'
        else:
            cc = '__cdecl'
        other = sorted(inputs - {'ecx'})
        out.write('%s\t%s\t%d\t%s\n' % (r['entry'], cc, purge, ','.join(other)))
        stats[cc] = stats.get(cc, 0) + 1
        if other:
            stats['reg:' + ','.join(other)] = stats.get('reg:' + ','.join(other), 0) + 1
    print(stats)


main()
