#!/usr/bin/env python3
"""Static ABI check of the reconstructed image against the original.

For every reconstructed function, the number of argument bytes it pops
(`ret N`) must equal the original's, or callers' stacks get corrupted.
Prints mismatches and writes them to re/abi_mismatch.tsv.
"""
import csv, re, subprocess

conv = {int(r['entry'], 16): int(r['stack_bytes']) for r in csv.DictReader(open('re/conventions.tsv'), delimiter='\t')}
names = {}
for r in csv.DictReader(open('re/functions.tsv'), delimiter='\t'):
    names[r['name']] = int(r['entry'], 16)

out = subprocess.run(['i686-w64-mingw32-objdump', '-d', '--no-show-raw-insn', 'build/recon/recon.elf'],
                     capture_output=True, text=True).stdout
cur = None
rets = {}
for line in out.splitlines():
    m = re.match(r'^[0-9a-f]+ <(.*)>:$', line)
    if m:
        sym = m.group(1)
        base = sym.lstrip('_').split('@')[0]
        cur = base[:-len('__impl')] if base.endswith('__impl') else None
        continue
    if cur and re.search(r'\tret\s*(\$0x[0-9a-f]+)?\s*$', line):
        m = re.search(r'\$0x([0-9a-f]+)', line)
        rets.setdefault(cur, set()).add(int(m.group(1), 16) if m else 0)
bad = []
for name, rs in sorted(rets.items()):
    a = names.get(name)
    if a is None or a not in conv:
        continue
    want = max(conv[a], 0)
    if rs != {want}:
        bad.append((a, name, want, sorted(rs)))
with open('re/abi_mismatch.tsv', 'w') as f:
    for a, n, w, rs in bad:
        f.write('%08x\t%s\t%d\t%s\n' % (a, n, w, rs))
print('%d functions checked, %d ABI mismatches' % (len(rets), len(bad)))
for b in bad[:20]:
    print('%08x %s want ret %d, have %s' % b)
