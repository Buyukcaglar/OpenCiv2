#!/usr/bin/env python3
"""Measure how far the game code is from 64-bit clean: compile every game
source for the 64-bit native target with the warnings that flag int <->
pointer truncation, and summarize them.  Runs inside the civ2-dev container
(after build_native.py has generated build/native/gen/).

Usage: port64_warnings.py [--out run/port64.txt] [FILE...]
Writes every warning to the output file and prints counts per kind and file.
"""
import argparse
import collections
import concurrent.futures
import glob
import os
import re
import subprocess

import build_native as bn

WARN = ['-Wint-to-pointer-cast', '-Wpointer-to-int-cast', '-Wint-conversion',
        '-Wincompatible-pointer-types', '-Wbad-function-cast']


def check(src):
    flags = [f for f in bn.CFLAGS if f != '-w'] + WARN
    r = subprocess.run(['gcc', '-fsyntax-only'] + flags + [src], capture_output=True, text=True,
                       cwd=os.path.join(bn.ROOT, 'src', 'include'))
    return src, [l for l in r.stderr.splitlines() if ': warning: ' in l or ': error: ' in l]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--out', default=os.path.join(bn.ROOT, 'run', 'port64.txt'))
    ap.add_argument('files', nargs='*')
    a = ap.parse_args()
    srcs = a.files or sorted([f for f in glob.glob(os.path.join(bn.ROOT, 'src', 'auto', '*.cpp')) if not f.endswith('msvcrt.c')] +
                             glob.glob(os.path.join(bn.ROOT, 'src', 'game', '*.cpp')) +
                             glob.glob(os.path.join(bn.ROOT, 'src', 'native', '*.cpp')))
    with concurrent.futures.ThreadPoolExecutor(os.cpu_count()) as ex:
        results = list(ex.map(check, srcs))
    kinds, files = collections.Counter(), collections.Counter()
    with open(a.out, 'w') as f:
        for src, lines in results:
            for l in lines:
                f.write(l + '\n')
                m = re.search(r'\[(-W[\w-]+)\]', l)
                kinds[m.group(1) if m else ('error' if ': error: ' in l else 'other')] += 1
                files[os.path.relpath(src, bn.ROOT)] += 1
    print('total', sum(kinds.values()))
    for k, n in kinds.most_common():
        print('%7d %s' % (n, k))
    for k, n in files.most_common(15):
        print('%7d %s' % (n, k))


if __name__ == '__main__':
    main()
