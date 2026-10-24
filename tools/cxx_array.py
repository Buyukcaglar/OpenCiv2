#!/usr/bin/env python3
"""An integer that holds the address of an array of T, as a T pointer:

    cxx_array.py NAME T FILE...

rewrites `*(T *)(NAME + E)` as NAME[E / sizeof(T)] where E is a sum of terms
each divisible by sizeof(T) (constants, X * k, k * X); other uses of NAME are
listed for hand (the declaration's type is changed by hand).  The index keeps
E's terms and their types, so it wraps as the byte offset did.
"""
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
from cxx_fix import match_paren  # noqa: E402

SIZES = {'i32': 4, 'int': 4, 'u32': 4, 'uint': 4, 'i16': 2, 'u16': 2, 'short': 2, 'ushort': 2}


def split_terms(e):
    """Top-level terms of a sum: [(sign, text)]."""
    terms, depth, cur, sign = [], 0, '', '+'
    i = 0
    while i < len(e):
        c = e[i]
        if c in '([':
            depth += 1
        elif c in ')]':
            depth -= 1
        if depth == 0 and c in '+-' and cur.strip() and not re.search(r'[*/(]\s*$', cur):
            terms.append((sign, cur.strip()))
            sign, cur = c, ''
        else:
            cur += c
        i += 1
    terms.append((sign, cur.strip()))
    return terms


def num(t):
    return int(t, 0) if re.fullmatch(r'0x[0-9a-fA-F]+|\d+', t) else None


def index(e, size):
    out = []
    for sign, t in split_terms(re.sub(r'\s+', ' ', e)):
        n = num(t)
        if n is not None:
            if n % size:
                return None
            q = n // size
            out.append((sign, ('0x%x' % q) if t.startswith('0x') else str(q)))
            continue
        m = re.fullmatch(r'(.*\S)\s*\*\s*(-?)(0x[0-9a-fA-F]+|\d+)', t) or None
        if m and num(m.group(3)) % size == 0:
            k = num(m.group(3)) // size
            x = m.group(1)
            if m.group(2):
                sign = '-' if sign == '+' else '+'
            out.append((sign, x if k == 1 else '%s * %d' % (x, k)))
            continue
        m = re.fullmatch(r'(0x[0-9a-fA-F]+|\d+)\s*\*\s*(.*)', t)
        if m and num(m.group(1)) % size == 0:
            k = num(m.group(1)) // size
            out.append((sign, m.group(2) if k == 1 else '%d * %s' % (k, m.group(2))))
            continue
        return None
    s = ''
    for i, (sign, t) in enumerate(out):
        s += (t if sign == '+' else '-' + t) if i == 0 else ' %s %s' % (sign, t)
    return s


def main():
    name, t, files = sys.argv[1], sys.argv[2], sys.argv[3:]
    size = SIZES[t]
    done = left = 0
    for f in files:
        s = open(f).read()
        out, pos = [], 0
        for m in re.finditer(r'\*\(\s*%s\s*\*\s*\)\s*\(\s*%s\b' % (re.escape(t), re.escape(name)), s):
            if m.start() < pos:
                continue
            o = s.rfind('(', 0, m.end() - len(name))
            e = match_paren(s, o)
            inner = s[o + 1:e - 1].strip()[len(name):].strip()
            if not inner.startswith('+'):
                continue
            idx = index(inner[1:], size)
            if idx is None:
                left += 1
                print('%s:%d: left: %s' % (f, s.count('\n', 0, m.start()) + 1, s[m.start():e]))
                continue
            out.append(s[pos:m.start()] + '%s[%s]' % (name, idx))
            pos = e
            done += 1
        out.append(s[pos:])
        new = ''.join(out)
        if new != s:
            open(f, 'w').write(new)
        for m in re.finditer(r'(?<![\w.>])%s\b(?!\[)' % re.escape(name), new):
            ln = new.count('\n', 0, m.start()) + 1
            print('%s:%d: other use: %s' % (f, ln, new.split('\n')[ln - 1].strip()))
    print('%d rewritten, %d left' % (done, left), file=sys.stderr)


if __name__ == '__main__':
    main()
