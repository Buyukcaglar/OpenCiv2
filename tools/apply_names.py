#!/usr/bin/env python3
"""Take naming proposals (addr, name, confidence, evidence rows; see
tools/name_batches.py) into re/symbols.tsv and re/function_names.tsv.

Low-confidence rows, addresses already named and the C runtime are left
out; names that clash (with each other, an existing name or
tools/reserved_names.txt) are listed and left out for a decision by hand.
Then run tools/rename.py.  Usage: tools/apply_names.py [--var] PROPOSALS.tsv...
(--var: names of globals, kind var, evidence in re/global_names.tsv)
"""
import collections
import csv
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CRT_START = 0x5F1B80


def main():
    args = sys.argv[1:]
    var = '--var' in args
    args = [x for x in args if x != '--var']
    kind = 'var' if var else 'func'
    evidence = 're/global_names.tsv' if var else 're/function_names.tsv'
    os.chdir(ROOT)
    sym = list(csv.DictReader(open('re/symbols.tsv'), delimiter='\t'))
    taken = {r['name'] for r in sym}
    named = {r['addr'] for r in sym if r['kind'] == kind}
    reserved = set(open('tools/reserved_names.txt').read().split())
    rows = []
    for path in args:
        for r in csv.DictReader(open(path), delimiter='\t'):
            if r['confidence'] == 'low' or r['addr'] in named or (not var and int(r['addr'], 16) >= CRT_START):
                continue
            rows.append(r)
    count = collections.Counter(r['name'] for r in rows)
    keep, problems = [], []
    for r in rows:
        if count[r['name']] > 1:
            problems.append('%s %s: proposed for %d functions' % (r['addr'], r['name'], count[r['name']]))
        elif r['name'] in taken:
            problems.append('%s %s: already a name' % (r['addr'], r['name']))
        elif r['name'] in reserved:
            problems.append('%s %s: C/POSIX/SDL identifier' % (r['addr'], r['name']))
        else:
            keep.append(r)
    with open('re/symbols.tsv', 'a') as f:
        for r in keep:
            f.write('%s\t%s\t%s\t\n' % (r['addr'], kind, r['name']))
    if not os.path.exists(evidence):
        open(evidence, 'w').write('addr\tname\tconfidence\tevidence\n')
    with open(evidence, 'a') as f:
        for r in keep:
            f.write('\t'.join((r['addr'], r['name'], r['confidence'], r['evidence'].replace('\t', ' '))) + '\n')
    print('%d names added' % len(keep))
    for p in problems:
        print('left out: ' + p)


if __name__ == '__main__':
    main()
