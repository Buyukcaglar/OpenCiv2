#!/usr/bin/env python3
"""Annotate addresses in a hook log with function names.

Original-image addresses resolve via re/functions.tsv; addresses in the
grafted reconstruction (>= 0x800000) via build/recon/recon.map.
Usage: symbolize.py run/X/hook.log
"""
import bisect, csv, re, sys

orig = sorted((int(r['entry'], 16), r['name']) for r in csv.DictReader(open('re/functions.tsv'), delimiter='\t'))
recon = []
try:
    for line in open('build/recon/recon.map'):
        a, n = line.split()
        recon.append((int(a, 16), n))
except FileNotFoundError:
    pass
recon.sort()


def name(a):
    table = recon if a >= 0x800000 else orig
    i = bisect.bisect_right(table, (a, '￿')) - 1
    if i < 0:
        return '?'
    base, n = table[i]
    return '%s+0x%x' % (n, a - base)


for line in open(sys.argv[1]):
    line = line.rstrip('\n')
    m = re.search(r'(eip=|: )([0-9a-f]{8})', line)
    if m and ('stack+' in line or 'eip=' in line):
        line += '   ' + name(int(m.group(2), 16))
    print(line)
