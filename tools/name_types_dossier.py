#!/usr/bin/env python3
"""Dossier for naming the inferred classes (src/include/civ2classes.h,
C_<root>[_<size>]): per type its size, the methods taking it as `this`,
and the named globals and expressions cast to it.
Usage: tools/name_types_dossier.py OUT.md"""
import collections
import csv
import glob
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(ROOT)
hdr = open('src/include/civ2classes.h').read()
types = re.findall(r'/\* (\d+) methods, size (0x[0-9a-f]+|\?) \*/\ntypedef struct (C_[0-9a-f]{8}(?:_[0-9a-f]+)?) ', hdr)
methods = collections.defaultdict(set)
for r in csv.DictReader(open('re/functions.tsv'), delimiter='\t'):
    m = re.search(r'\((C_[0-9a-f]{8}(?:_[0-9a-f]+)?) \* this', r['signature'])
    if m:
        methods[m.group(1)].add(r['name'].replace('thunk_', ''))
casts = collections.defaultdict(collections.Counter)
pat = re.compile(r'\((C_[0-9a-f]{8}(?:_[0-9a-f]+)?) \*\)\s*&?\(?([A-Za-z_][\w]*)')
for f in glob.glob('src/auto/blk_*.c') + glob.glob('src/game/*.c'):
    for m in pat.finditer(open(f, errors='replace').read()):
        if not re.match(r'^(local_|param_|i?Var|u?Var|p\w*Var|this$|DAT_|iptr_)', m.group(2)):
            casts[m.group(1)][m.group(2)] += 1
out = []
for n, size, t in types:
    ms = sorted(methods[t])
    named = [x for x in ms if not x.startswith('FUN_')]
    cs = ', '.join('%s (%d)' % kv for kv in casts[t].most_common(8))
    out.append('%s  size %s; %d methods (%d named): %s%s; casts: %s' % (
        t, size, len(ms), len(named), ' '.join(named[:20]), ' ...' if len(named) > 20 else '', cs or '-'))
open(sys.argv[1], 'w').write('\n'.join(out) + '\n')
print(len(out), 'types')
