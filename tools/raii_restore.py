#!/usr/bin/env python3
"""Step 6 (RAII): put functions back as they are in a git revision.

    raii_restore.py FILE FUNCTION... [--rev REV]

FUNCTION is the name on the definition line (`net_client_turn_loop`,
`ParleyWindow::show`).  Used for the functions a conversion got wrong
(tools/calls_compare.py reports them).
"""
import re
import subprocess
import sys


def spans(lines, name):
    out = []
    for i, l in enumerate(lines):
        if re.match(r'^[A-Za-z_].*\b%s\(' % re.escape(name), l) and not l.rstrip().endswith(';'):
            j = i
            while lines[j] != '{':
                j += 1
            k = j
            while lines[k] != '}':
                k += 1
            out.append((i, k))
    return out


def main():
    args = sys.argv[1:]
    rev = 'HEAD'
    if '--rev' in args:
        k = args.index('--rev')
        rev = args[k + 1]
        del args[k:k + 2]
    path, names = args[0], args[1:]
    cur = open(path).read().split('\n')
    old = subprocess.run(['git', 'show', '%s:%s' % (rev, path)], capture_output=True, text=True,
                         check=True).stdout.split('\n')
    for name in names:
        a, b = spans(cur, name), spans(old, name)
        if len(a) != 1 or len(b) != 1:
            print('%s: %d / %d definitions, skipped' % (name, len(a), len(b)))
            continue
        (i, k), (oi, ok) = a[0], b[0]
        cur[i:k + 1] = old[oi:ok + 1]
        print('%s: restored' % name)
    open(path, 'w').write('\n'.join(cur))


if __name__ == '__main__':
    main()
