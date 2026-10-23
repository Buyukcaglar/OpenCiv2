#!/usr/bin/env python3
"""Functions nothing in the game refers to: re/unreferenced.tsv (address,
name), from what the linker drops from the linux32gc build (no call, no
address taken, no table entry reaches them).  tools/gen_c.py writes these
functions to src/unused/ (not compiled) instead of src/auto/.

Usage (in the container):
    python3 tools/build_native.py --target linux32gc && python3 tools/unreferenced.py
Run it again after changes that may make functions unreachable; functions
already in src/unused/ stay there (the build cannot see them any more).
"""
import csv
import glob
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def main():
    addr_of = {}
    for m in re.finditer(r'\b(\w+)\([^;]*\);\s*/\* ([0-9a-f]{8})', open(os.path.join(ROOT, 'src', 'auto', 'protos.h')).read()):
        addr_of[m.group(1)] = m.group(2)
    found = {}
    path = os.path.join(ROOT, 're', 'unreferenced.tsv')
    if os.path.exists(path):
        for r in csv.DictReader(open(path), delimiter='\t'):
            found[r['addr']] = r['name']
    for line in open(os.path.join(ROOT, 'build', 'native', 'linux32gc', 'unreferenced.txt')):
        name, obj = line.rstrip('\n').split('\t')
        if obj.startswith('src_auto_') and name in addr_of:
            found[addr_of[name]] = name
    # The hand-written sources are compiled whole: what they name stays.
    named = set()
    for d in ('game', 'platform', 'native', 'data', 'crt'):
        for dirpath, _, files in os.walk(os.path.join(ROOT, 'src', d)):
            for fn in files:
                if fn.endswith(('.c', '.h')):
                    named.update(re.findall(r'\b\w+\b', open(os.path.join(dirpath, fn), errors='replace').read()))
    found = {a: n for a, n in found.items() if n not in named}
    # ... and so does everything a kept function names (generated bodies,
    # wherever gen_c put them last time), until nothing changes.
    bodies = {}
    for d in ('auto', 'unused'):
        for fpath in glob.glob(os.path.join(ROOT, 'src', d, '*.c')):
            parts = re.split(r'^/\* ([0-9a-f]{8}) \w+', open(fpath, errors='replace').read(), flags=re.M)
            for i in range(1, len(parts) - 1, 2):
                bodies[parts[i]] = parts[i + 1]
    dead_names = {n: a for a, n in found.items()}
    live = [a for a in bodies if a not in found]
    while live:
        a = live.pop()
        for w in set(re.findall(r'\b\w+\b', bodies[a])) & dead_names.keys():
            b = dead_names.pop(w)
            del found[b]
            if b in bodies:
                live.append(b)
    with open(path, 'w') as f:
        f.write('addr\tname\n')
        for a in sorted(found):
            f.write('%s\t%s\n' % (a, found[a]))
    print('%d unreferenced functions (re/unreferenced.tsv)' % len(found))


if __name__ == '__main__':
    main()
