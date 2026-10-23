#!/usr/bin/env python3
"""Dossiers for naming class fields: per class family (C_<root>, all its
size levels; field offsets are shared within a family), each field's
offset, size, the number of this->field_K accesses in its methods and
sample lines.  Proposals go to re/field_names.tsv (family, offset, name).

Usage: tools/name_fields_dossier.py OUTDIR [--per N]   (N fields per file)
"""
import argparse
import collections
import csv
import glob
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('out')
    ap.add_argument('--per', type=int, default=120)
    a = ap.parse_args()
    os.chdir(ROOT)
    fam_of = {}
    for r in csv.DictReader(open('re/class_methods.tsv'), delimiter='\t'):
        fam_of[r['method']] = r['class'][:10]
    size = {}
    for r in csv.DictReader(open('re/class_fields.tsv'), delimiter='\t'):
        size[(r['class'][:10], int(r['offset']))] = int(r['size'])
    names = {r['entry']: r['name'] for r in csv.DictReader(open('re/functions.tsv'), delimiter='\t')}
    count = collections.Counter()
    samples = collections.defaultdict(list)
    for f in glob.glob('src/auto/*.c') + glob.glob('src/game/*.c'):
        text = open(f, errors='replace').read()
        for m in re.finditer(r'^/\* ([0-9a-f]{8}) [^\n]*\*/\n(.*?)(?=^/\* [0-9a-f]{8} |\Z)', text, re.M | re.S):
            fam = fam_of.get(m.group(1))
            if not fam:
                continue
            for ln in m.group(2).split('\n'):
                for k in set(re.findall(r'\bthis->field_([0-9a-f]+)\b', ln)):
                    key = (fam, int(k, 16))
                    count[key] += 1
                    if len(samples[key]) < 4:
                        samples[key].append('%s: %s' % (names.get(m.group(1), m.group(1)), ln.strip()[:150]))
    fams = collections.defaultdict(list)
    for key in count:
        fams[key[0]].append(key)
    os.makedirs(a.out, exist_ok=True)
    files, cur = [], []
    for fam in sorted(fams, key=lambda x: -sum(count[k] for k in fams[x])):
        keys = sorted(fams[fam], key=lambda k: k[1])
        for k in keys:
            if len(cur) >= a.per:
                files.append(cur)
                cur = []
            cur.append(k)
    if cur:
        files.append(cur)
    for n, keys in enumerate(files):
        out = []
        for k in keys:
            out.append('## %s +0x%x  (%s bytes, %d accesses)\n%s\n' % (
                k[0], k[1], size.get(k, '?'), count[k], '\n'.join('    ' + s for s in samples[k])))
        open(os.path.join(a.out, 'fields%02d.md' % n), 'w').write('\n'.join(out))
    n = len(files)
    print('%d fields in %d families, %d files' % (len(count), len(fams), n))


if __name__ == '__main__':
    main()
