#!/usr/bin/env python3
"""Which game functions the test runs execute: gcov data of the
coverage build (build_native.py --target linux32cov, run with
EXE=civ2-linux32cov).  Writes re/coverage.tsv (function, executed lines,
lines) and prints totals and the never-executed functions by subsystem
(name prefix), the places new test scripts should go.

Usage (in the container): python3 tools/coverage_report.py
"""
import collections
import glob
import os
import re
import subprocess

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
OBJ = os.path.join(ROOT, 'build', 'native', 'linux32cov')


def main():
    os.chdir(ROOT)
    rows = []
    for src in sorted([f for f in glob.glob('src/auto/*.c') if not f.endswith('msvcrt.c')] + glob.glob('src/game/*.c')):
        obj = os.path.join(OBJ, src.replace('/', '_') + '.o')
        if not os.path.exists(obj[:-2] + '.gcda'):
            continue
        out = subprocess.run(['gcov', '-f', '-n', '-o', obj, src], capture_output=True, text=True).stdout
        for m in re.finditer(r"Function '([^']+)'\nLines executed:([\d.]+)% of (\d+)", out):
            n = int(m.group(3))
            rows.append((m.group(1), round(float(m.group(2)) * n / 100), n))
    with open('re/coverage.tsv', 'w') as f:
        f.write('function\texecuted\tlines\n')
        for r in rows:
            f.write('%s\t%d\t%d\n' % r)
    ran = [r for r in rows if r[1] > 0]
    lines = sum(r[2] for r in rows)
    print('functions executed: %d of %d (%.0f%%); lines: %.0f%%' % (
        len(ran), len(rows), 100.0 * len(ran) / max(1, len(rows)), 100.0 * sum(r[1] for r in rows) / max(1, lines)))
    never = collections.Counter()
    for name, done, n in rows:
        if not done and not name.startswith(('FUN_', 'thunk_')):
            never[name.split('_')[0]] += 1
    print('never executed, named, by prefix:', ', '.join('%s %d' % kv for kv in never.most_common(25)))


if __name__ == '__main__':
    main()
