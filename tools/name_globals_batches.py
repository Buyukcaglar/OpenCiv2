#!/usr/bin/env python3
"""Dossiers for naming globals: the unnamed globals used by the most
functions, in batches of N, each with its type(s), the functions using it
and sample lines of use.  Proposals come back as addr/name/confidence/
evidence rows for re/symbols.tsv (kind var); see tools/apply_names.py --var.

Usage: tools/name_globals_batches.py OUTDIR [--skip K] [--count M] [--per N]
"""
import argparse
import collections
import glob
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
UNNAMED = re.compile(r'^(?:DAT|iptr|uptr|INT|UINT|SHORT|USHORT|BYTE|WORD|DWORD|CHAR|PTR_DAT)_00[4-7][0-9a-f]{5}$')


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('out')
    ap.add_argument('--skip', type=int, default=0)
    ap.add_argument('--count', type=int, default=400)
    ap.add_argument('--per', type=int, default=50)
    a = ap.parse_args()
    os.chdir(ROOT)
    users = collections.defaultdict(set)
    info = {}
    func = None
    crt = False
    game_users = set()      # globals the game itself uses (not only the C runtime)
    for line in open('re/decomp.c', errors='replace'):
        if line.startswith('// ==== FUNCTION '):
            fa, func = line.split()[3:5]
            crt = 0x5F1B80 <= int(fa, 16) < 0x61A000
        elif line.startswith('// GLOBAL '):
            n, ga, t, size = line[10:].rstrip('\n').split('\t')
            if UNNAMED.match(n):
                users[n].add(func)
                if not crt:
                    game_users.add(n)
                info.setdefault(n, set()).add('%s (%s bytes)' % (t, size))
    ranked = sorted(((len(u), n) for n, u in users.items() if n in game_users), reverse=True)[a.skip:a.skip + a.count]
    pick = sorted(n for _, n in ranked)
    lines = collections.defaultdict(list)
    want = set(pick)
    pat = re.compile(r'\b(%s)\b' % '|'.join(pick))
    for f in sorted(glob.glob('src/auto/blk_*.c') + glob.glob('src/game/*.c')):
        for ln in open(f, errors='replace'):
            if ln.startswith('#'):
                continue
            for m in set(pat.findall(ln)):
                if len(lines[m]) < 8:
                    lines[m].append(ln.strip()[:160])
    os.makedirs(a.out, exist_ok=True)
    for b in range(0, len(pick), a.per):
        out = []
        for n in pick[b:b + a.per]:
            us = sorted(users[n])
            out.append('## %s  (address %s; type %s; used by %d functions: %s)\n```c\n%s\n```\n' % (
                n, n[-8:], ', '.join(sorted(info[n])), len(us), ', '.join(us[:30]) + (' ...' if len(us) > 30 else ''),
                '\n'.join(lines[n])))
        open(os.path.join(a.out, 'batch%d.md' % (b // a.per)), 'w').write('\n'.join(out))
    print('%d globals in %d batches' % (len(pick), (len(pick) + a.per - 1) // a.per))


if __name__ == '__main__':
    main()
