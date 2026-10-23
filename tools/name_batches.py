#!/usr/bin/env python3
"""Dossiers for naming functions: the unnamed game functions with the most
callers, in batches of N, each function's C and its callers' names.

Usage: tools/name_batches.py OUTDIR [--skip K] [--count M] [--per N]
Writes OUTDIR/batchI.md; proposals come back as addr/name/confidence/
evidence rows, go into re/symbols.tsv (kind func) and re/function_names.tsv,
and tools/rename.py applies them.
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
    ap.add_argument('--skip', type=int, default=0)
    ap.add_argument('--count', type=int, default=300)
    ap.add_argument('--per', type=int, default=50)
    a = ap.parse_args()
    os.chdir(ROOT)
    funcs = {r['entry']: r for r in csv.DictReader(open('re/functions.tsv'), delimiter='\t')}
    status = {r['addr']: r['status'] for r in csv.DictReader(open('re/manifest.tsv'), delimiter='\t')}

    def target(x):
        r = funcs.get(x)
        while r and r['thunk_target'] and not r['thunk_target'].startswith('EXT') and r['thunk_target'] in funcs:
            x = r['thunk_target']
            r = funcs[x]
        return x
    callers = collections.defaultdict(set)
    for line in open('re/calls.tsv'):
        s, d = line.split()
        s, d = target(s), target(d)
        if s != d:
            callers[d].add(s)
    ranked = sorted((len(callers[x]), x) for x, r in funcs.items()
                    if not r['thunk_target'] and r['name'].startswith('FUN_') and status.get(x) in ('auto', 'game'))
    ranked.reverse()
    pick = sorted(x for _, x in ranked[a.skip:a.skip + a.count])
    src = {}
    for f in glob.glob('src/auto/*.c') + glob.glob('src/game/*.c'):
        t = open(f).read()
        for m in re.finditer(r'^/\* ([0-9a-f]{8}) (?:auto|game)[^\n]*\*/\n(.*?)(?=^/\* [0-9a-f]{8} |\Z)', t, re.M | re.S):
            src[m.group(1)] = (f, m.group(2))
    os.makedirs(a.out, exist_ok=True)
    for b in range(0, len(pick), a.per):
        out = []
        for x in pick[b:b + a.per]:
            f, body = src.get(x, ('?', '(not in src/auto: hand-written, grep src/game for %s)\n' % x))
            names = sorted(funcs[c]['name'] if c in funcs else c for c in callers[x])
            if len(body) > 12000:
                body = body[:12000] + '\n... (truncated; full: python3 tools/show.py %s)\n' % x
            out.append('## %s  %s  (%s, %d callers: %s)\n```c\n%s```\n' % (
                x, funcs[x]['name'], f, len(names), ', '.join(names[:25]) + (' ...' if len(names) > 25 else ''), body))
        open(os.path.join(a.out, 'batch%d.md' % (b // a.per)), 'w').write('\n'.join(out))
    print('%d functions in %d batches' % (len(pick), (len(pick) + a.per - 1) // a.per))


if __name__ == '__main__':
    main()
