#!/usr/bin/env python3
"""Decompiler idioms written the way C is usually written, with the same
values (applied by tools/gen_c.py to what it writes):

    '\\x05'           -> 5      (a non-printable character literal is a number;
                                 '\\x80'..'\\xff' are negative, as char is signed)
    a + -4           -> a - 4
    x = x + 1;       -> x++;     (also as a for loop's step; x = x - 1 likewise)
    x = x + e;       -> x += e;  (x: a name, field or index path without calls;
                                  e: no operator binding less than '+' or '-')
"""
import re

LVALUE = r'[A-Za-z_][\w.]*(?:\[[^\[\]()]*\]|\.\w+|->\w+)*'


def char_literals(text):
    def rep(m):
        v = int(m.group(1), 16)
        return str(v - 256 if v >= 0x80 else v)
    text = re.sub(r"'\\x([0-9a-f]{2})'", rep, text)
    return re.sub(r"'\\([abvf])'", lambda m: str({'a': 7, 'b': 8, 'v': 11, 'f': 12}[m.group(1)]), text)


def simple_operand(e):
    """No top-level binary operator binding less tightly than + and -
    (so x = x + e and x += e group alike)."""
    s = e.strip()
    depth, prev_operand = 0, False
    i = 0
    while i < len(s):
        c = s[i]
        if c in '([':
            depth += 1
            prev_operand = False
        elif c in ')]':
            depth -= 1
            prev_operand = True
        elif depth == 0 and c in ' \t':
            pass
        elif depth == 0:
            two = s[i:i + 2]
            if two == '->':
                i += 2
                continue
            if c in '+-&' and prev_operand:
                return False            # binary + - & (unary ones follow an operator)
            if two in ('<<', '>>', '<=', '>=', '==', '!=', '&&', '||') or c in '<>|^?:=,':
                return False
            prev_operand = c.isalnum() or c in '_.\'"'
        i += 1
    return depth == 0 and bool(s)


def compound(text):
    def rep(m):
        lead, lhs, lhs2, op, e, end = m.groups()
        if lhs != lhs2:
            return m.group(0)
        if e.strip() == '1':
            return '%s%s%s%s' % (lead, lhs, '++' if op == '+' else '--', end)
        if not simple_operand(e):
            return m.group(0)
        return '%s%s %s= %s%s' % (lead, lhs, op, e.strip(), end)
    # a statement on its own line
    text = re.sub(r'(?m)^(\s*)(' + LVALUE + r') = (' + LVALUE + r') ([+-]) ([^;\n]+)(;)$', rep, text)
    # a for loop's step: after '; ', before the ')' closing the header
    return re.sub(r'(; )(' + LVALUE + r') = (' + LVALUE + r') ([+-]) ([^;()\n]+)(\)(?= \{|\n))', rep, text)


def apply(text):
    text = char_literals(text)
    text = re.sub(r' \+ -(?=\d)', ' - ', text)
    return compound(text)


if __name__ == '__main__':
    import sys
    for p in sys.argv[1:]:
        t = open(p).read()
        n = apply(t)
        if n != t:
            open(p, 'w').write(n)
            print(p)
