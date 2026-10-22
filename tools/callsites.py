#!/usr/bin/env python3
"""Machine-code facts the decompiler cannot see one function at a time.

  returns  - which functions return a value: some caller reads EAX after the
             call, or the function passes a callee's EAX through to its own
             caller (`return g(x);` compiles to call g; jmp epilogue).
  arity    - stack argument count: the callee's `ret N`, or for caller-cleanup
             functions the largest `add esp, N` after any call site.
  gaccess  - per function, the size of each absolute-address memory access
             (resolves Ghidra's `_DAT_xxx` overlapping-symbol references).

Writes re/callsites.tsv (entry, returns, ret_size, arity) and re/gaccess.tsv.
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
thunk_target = {}
funcs = {}
for r in rows:
    a = int(r['entry'], 16)
    if r['thunk_target'] and not r['thunk_target'].startswith('EXTERNAL'):
        thunk_target[a] = int(r['thunk_target'], 16)
    elif not r['thunk_target']:
        funcs[a] = int(r['size'])
conv = {int(r['entry'], 16): r for r in csv.DictReader(open('re/conventions.tsv'), delimiter='\t')}

EAX_PARTS = {'eax': 4, 'ax': 2, 'al': 1, 'ah': 2}   # reading AH needs at least 16 bits


def resolve(t):
    return thunk_target.get(t, t)


reads_eax = collections.defaultdict(int)     # callee -> max size read by callers
passthrough = collections.defaultdict(set)   # caller -> callees whose EAX it returns
arity = collections.defaultdict(int)
site_arities = collections.defaultdict(set)
gaccess = collections.defaultdict(collections.Counter)
DATA_LO, DATA_HI = 0x61C000, 0x6F0000

for f, size in funcs.items():
    ins = list(md.disasm(img[f - BASE:f - BASE + size], f))
    by_addr = {i.address: k for k, i in enumerate(ins)}
    for k, i in enumerate(ins):
        for op in i.operands:
            if op.type == x86.X86_OP_MEM and op.mem.base == 0 and op.mem.index == 0 and DATA_LO <= op.mem.disp < DATA_HI:
                gaccess[f][(op.mem.disp & 0xffffffff, op.size)] += 1
            elif op.type == x86.X86_OP_MEM and op.mem.base == 0 and DATA_LO <= op.mem.disp < DATA_HI:
                gaccess[f][(op.mem.disp & 0xffffffff, op.size)] += 1
        if i.mnemonic != 'call' or i.operands[0].type != x86.X86_OP_IMM:
            continue
        callee = resolve(i.operands[0].imm)
        # Walk forward from the call site.
        j = k + 1
        steps = 0
        while j < len(ins) and steps < 40:
            n = ins[j]
            steps += 1
            if n.mnemonic == 'add' and n.op_str.startswith('esp, '):
                k_args = int(n.op_str.split(', ')[1], 0) // 4
                arity[callee] = max(arity[callee], k_args)
                site_arities[callee].add(k_args)
                j += 1
                continue
            if n.mnemonic == 'jmp' and n.operands[0].type == x86.X86_OP_IMM:
                tgt = n.operands[0].imm
                if tgt in by_addr:
                    j = by_addr[tgt]
                    continue
                break
            if n.mnemonic in ('pop', 'leave') and n.op_str in ('edi', 'esi', 'ebx', 'ebp', ''):
                j += 1
                continue
            if n.mnemonic == 'ret':
                passthrough[f].add(callee)
                break
            rd, wr = n.regs_access()
            rnames = {n.reg_name(r) for r in rd}
            wnames = {n.reg_name(r) for r in wr}
            used = [EAX_PARTS[r] for r in rnames if r in EAX_PARTS]
            # xor eax, eax / mov eax, x reads nothing of interest
            if n.mnemonic == 'xor' and n.op_str in ('eax, eax',):
                break
            if used:
                reads_eax[callee] = max(reads_eax[callee], max(used))
                break
            if wnames & set(EAX_PARTS) or n.mnemonic in ('call',) or n.mnemonic.startswith('j'):
                break
            j += 1

# Propagate: a function whose EAX is consumed and that passes a callee's EAX
# through, makes that callee value-returning too.
returns = dict(reads_eax)
changed = True
while changed:
    changed = False
    for f, callees in passthrough.items():
        if f in returns:
            for c in callees:
                if returns.get(c, 0) < returns[f]:
                    returns[c] = returns[f]
                    changed = True

with open('re/callsites.tsv', 'w') as out:
    # A caller-cleanup function called with different argument counts is
    # variadic (sprintf-like): its fixed part is the smallest count seen.
    out.write('entry\treturns\tret_size\tarity\tvariadic\n')
    for f in sorted(funcs):
        c = conv.get(f)
        purge = int(c['stack_bytes']) if c else -1
        variadic = purge <= 0 and len(site_arities.get(f, ())) > 1
        if purge > 0:
            n = purge // 4
        elif variadic:
            n = min(site_arities[f])
        else:
            n = arity.get(f, 0)
        out.write('%08x\t%d\t%d\t%d\t%d\n' % (f, 1 if f in returns else 0, returns.get(f, 0), n, variadic))

with open('re/gaccess.tsv', 'w') as out:
    out.write('func\taddr\tsize\tcount\n')
    for f in sorted(gaccess):
        for (a, s), n in sorted(gaccess[f].items()):
            out.write('%08x\t%08x\t%d\t%d\n' % (f, a, s, n))

print('value-returning functions:', len(returns), 'of', len(funcs))
