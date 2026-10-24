#!/usr/bin/env python3
"""Whether a function's source changed other than in its casts: the old
version (git REV, default HEAD) and the working tree, compared token by token
with every cast and parenthesis removed (the clean-up passes only drop
parentheses around a single operand, so this does not hide a change of
grouping).  For the functions tools/cxx_check.sh lists as DIFFER:

    cxx_castdiff.py [--rev REV] CHECK_OUTPUT     prints the functions whose
                                                 tokens changed, with a diff
"""
import difflib
import re
import subprocess
import sys

CAST = re.compile(r'\((?:const\s+)?(?:struct\s+)?[A-Za-z_]\w*(?:\s*\*)*\s*\)(?=\s*[\w(&*"\'-])')


def body(text, name):
    m = (re.search(r'(?m)^(?:[^\n;{}]*\n)?%s\s*\n?\s*\(' % re.escape(name), text)
         or re.search(r'\b%s\s*\([^;{]*\)\s*\{' % re.escape(name), text))
    if not m:
        return ''
    i = text.index('{', m.start())
    d = 0
    for j in range(i, len(text)):
        if text[j] == '{':
            d += 1
        elif text[j] == '}':
            d -= 1
            if d == 0:
                return text[m.start():j + 1]
    return ''


def tokens(t):
    t = re.sub(r'/\*.*?\*/', '', t, flags=re.S)
    prev = None
    while prev != t:
        prev = t
        t = CAST.sub('', t)
    return re.findall(r'[A-Za-z_]\w*|0x[0-9a-fA-F]+|\d+|->|[^\s()]', t)


def main():
    a = sys.argv[1:]
    rev = 'HEAD'
    if a and a[0] == '--rev':
        rev, a = a[1], a[2:]
    cur = None
    bad = 0
    for line in open(a[0]):
        m = re.match(r'(src/\S+): DIFFER', line)
        if m:
            cur = m.group(1)
            continue
        fn = line.strip()
        if not cur or not line.startswith('    ') or not fn:
            continue
        old = subprocess.run(['git', 'show', '%s:%s' % (rev, cur)], capture_output=True, text=True).stdout
        x, y = tokens(body(old, fn)), tokens(body(open(cur).read(), fn))
        if x != y:
            bad += 1
            print('== %s %s' % (cur, fn))
            print('\n'.join(list(difflib.unified_diff(x, y, lineterm='', n=3))[2:20]))
    print('%d functions changed other than in casts' % bad)


if __name__ == '__main__':
    main()
