#!/usr/bin/env python3
"""Call functions by their own names, not through the original's
incremental-link thunks (thunk_X: a jump to X).

The thunk names stay defined (build/native/gen/thunks.h, as casts of
their targets), so code still naming one builds; a call kept through its
thunk (re/thunk_keep.txt) is one the portable build cannot make directly:
its arguments do not match the target's definition.

tools/gen_c.py applies this to what it writes; for hand-written sources:
tools/direct_calls.py FILE...
"""
import csv
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
_MAP = None


def mapping():
    """thunk name -> target name"""
    global _MAP
    if _MAP is None:
        rows = list(csv.DictReader(open(os.path.join(ROOT, 're', 'functions.tsv')), delimiter='\t'))
        names = {r['entry']: r['name'] for r in rows}
        keep_path = os.path.join(ROOT, 're', 'thunk_keep.txt')
        keep = set(open(keep_path).read().split()) if os.path.exists(keep_path) else set()
        _MAP = {}
        for r in rows:
            t = r['thunk_target']
            if t and not t.startswith('EXT') and t in names and r['name'] != names[t] \
                    and re.match(r'^[A-Za-z_]\w*$', r['name']) and re.match(r'^[A-Za-z_]\w*$', names[t]) \
                    and r['name'] not in keep:
                _MAP[r['name']] = names[t]
    return _MAP


def apply(text):
    m = mapping()

    def rep(x):
        return m.get(x.group(0), x.group(0))
    return re.sub(r'\bthunk_\w+\b', rep, text)


def main():
    for path in sys.argv[1:]:
        t = open(path).read()
        n = apply(t)
        if n != t:
            open(path, 'w').write(n)
            print(path)


if __name__ == '__main__':
    main()
