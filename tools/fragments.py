#!/usr/bin/env python3
"""Find Ghidra "functions" that are really pieces of another function.

MSVC places the epilogue of functions with C++ exception frames after the
unwind funclets, and Ghidra sometimes splits such tails (and other jump-only
blocks) off as separate functions.  A function entry that is only ever
reached by `jmp` from inside one other function (never called, never jumped
to by an incremental-link thunk) is such a fragment.

Code is walked by recursive descent (switch jump tables are embedded in the
code, so a linear sweep loses sync after them).

Writes re/fragments.tsv: fragment_entry  parent_entry
"""
import collections
import csv

import capstone
import pefile
from capstone import x86
import sys
import os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import paths  # noqa: E402  (the game's directory)

BASE = 0x400000
pe = pefile.PE(paths.game_file('civ2.exe'))
img = pe.get_memory_mapped_image()
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
md.detail = True

rows = list(csv.DictReader(open('re/functions.tsv'), delimiter='\t'))
real = sorted(int(r['entry'], 16) for r in rows if not r['thunk_target'])
real_set = set(real)
called = set()
jumped = collections.defaultdict(set)


def walk(entry):
    """Recursive descent over one function; records calls/jumps to other entries."""
    seen, work = set(), [entry]
    while work:
        pc = work.pop()
        first = True
        while 0x401000 <= pc < 0x619000 and pc not in seen and (first or pc not in real_set):
            first = False
            seen.add(pc)
            try:
                ins = next(md.disasm(img[pc - BASE:pc - BASE + 16], pc, count=1))
            except StopIteration:
                break
            m = ins.mnemonic
            op = ins.operands[0] if ins.operands else None
            if m == 'call' and op is not None and op.type == x86.X86_OP_IMM:
                if op.imm in real_set:
                    called.add(op.imm)
            if m == 'ret' or m == 'int3' or m == 'hlt':
                break
            if m == 'jmp':
                if op.type == x86.X86_OP_IMM:
                    if op.imm in real_set and op.imm != entry:
                        jumped[op.imm].add(entry)
                        break
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
            if m.startswith('j') and op is not None and op.type == x86.X86_OP_IMM:
                if op.imm in real_set and op.imm != entry:
                    jumped[op.imm].add(entry)
                else:
                    work.append(op.imm)
            if m == 'push' and op is not None and op.type == x86.X86_OP_IMM and entry < op.imm < entry + 0x20000 \
                    and op.imm not in real_set:
                work.append(op.imm)
            pc += ins.size


for f in real:
    walk(f)
for r in rows:
    if r['thunk_target'] and not r['thunk_target'].startswith('EXTERNAL'):
        called.add(int(r['thunk_target'], 16))

with open('re/fragments.tsv', 'w') as out:
    out.write('fragment\tparent\n')
    n = 0
    for t, parents in sorted(jumped.items()):
        if t in called or len(parents) != 1:
            continue
        out.write('%08x\t%08x\n' % (t, next(iter(parents))))
        n += 1
print('fragments:', n)
