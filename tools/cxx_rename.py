#!/usr/bin/env python3
"""Rename identifiers in C sources outside comments and string/char
literals: cxx_rename.py OLD=NEW [OLD=NEW ...] -- FILES...  (step 6: names
that are C++ keywords, e.g. this=self)."""
import re
import sys

TOKEN = re.compile(r'/\*.*?\*/|//[^\n]*|"(?:[^"\\\n]|\\.)*"|\'(?:[^\'\\\n]|\\.)*\'|[A-Za-z_]\w*|.', re.S)


def rename(text, mapping):
    out = []
    for m in TOKEN.finditer(text):
        t = m.group(0)
        out.append(mapping.get(t, t))
    return ''.join(out)


def main():
    a = sys.argv[1:]
    i = a.index('--')
    mapping = dict(x.split('=', 1) for x in a[:i])
    n = 0
    for path in a[i + 1:]:
        text = open(path).read()
        new = rename(text, mapping)
        if new != text:
            open(path, 'w').write(new)
            n += 1
    print('%d files changed' % n)


if __name__ == '__main__':
    main()
