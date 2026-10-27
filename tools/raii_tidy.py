#!/usr/bin/env python3
"""Step 6 (RAII): blocks left empty when a release moved into a guard.

    raii_tidy.py FILE...

    if (C) {        ->   if (!C) {         (C inverted when it is one
    }                      BODY            comparison: == / !=, < / >= ...)
    else {               }
      BODY
    }
and an empty `else { }` is dropped; the MSVC trylevel locals left unused
(eh_state, seh_handler ...) are dropped.  Other empty blocks are listed.
"""
import re
import sys

INV = {'==': '!=', '!=': '==', '<': '>=', '>=': '<', '>': '<=', '<=': '>'}


def top_split(c):
    """top-level comparison operators of c: [(pos, op)], or None if c has
    other top-level operators that bind looser."""
    depth = 0
    ops = []
    i = 0
    while i < len(c):
        ch = c[i]
        if ch in '([':
            depth += 1
        elif ch in ')]':
            depth -= 1
        elif depth == 0:
            two = c[i:i + 2]
            if two in ('&&', '||') or ch in '?':
                return None
            if two in ('==', '!=', '<=', '>='):
                ops.append((i, two))
                i += 2
                continue
            if two in ('<<', '>>'):
                i += 2
                continue
            if ch in '<>' and c[i - 1] != '-':
                ops.append((i, ch))
            elif ch == '=':
                return None
        i += 1
    return ops


def invert(c):
    while c.startswith('(') and c.endswith(')') and top_split(c[1:-1]) is not None and balanced(c[1:-1]):
        c = c[1:-1]
    ops = top_split(c)
    if ops is not None and len(ops) == 1:
        p, op = ops[0]
        return c[:p].rstrip() + ' ' + INV[op] + ' ' + c[p + len(op):].lstrip()
    return '!(%s)' % c


def balanced(c):
    d = 0
    for ch in c:
        d += ch == '('
        d -= ch == ')'
        if d < 0:
            return False
    return d == 0


EH = re.compile(r'^\s*(s?eh_state|try_level|unwind_state|\(\*\(\(char \*\)&(?:s?eh_state|try_level|unwind_state) \+ \d+\)\)) = [^;]*;$')


def unused_eh(lines):
    """the MSVC trylevel locals (written, never read) in functions with no
    unwind funclet left: their writes, then their declarations"""
    start = None
    for i, l in enumerate(lines):
        if l == '{':
            start = i
        elif l == '}' and start is not None:
            if 'inlined unwind funclet' not in '\n'.join(x for x in lines[start:i] if x is not None):
                for k in range(start, i):
                    if lines[k] is not None and EH.match(lines[k]):
                        lines[k] = None
            body = '\n'.join(x for x in lines[start:i] if x is not None)
            for v in ('eh_state', 'seh_state', 'try_level', 'unwind_state', 'seh_next', 'seh_handler', 'eh_handler', 'seh_prev'):
                if len(re.findall(r'\b%s\b' % v, body)) == 1:
                    for k in range(start, i):
                        if lines[k] is not None and re.match(r'^\s*[\w ]+\*?\s*%s;$' % v, lines[k]):
                            lines[k] = None
            start = None
    return [l for l in lines if l is not None]


def tidy(path):
    lines = unused_eh(open(path).read().split('\n'))
    open(path, 'w').write('\n'.join(lines))
    total = 0
    while True:
        n = tidy_once(path)
        total += n
        if n == 0:
            break
    lines = unused_eh(open(path).read().split('\n'))
    open(path, 'w').write('\n'.join(lines))
    print('%s: %d blocks' % (path, total))
    for k, l in enumerate(lines[:-1]):
        if l.rstrip().endswith('{') and lines[k + 1].strip() == '}' and not l.startswith('{'):
            print('  empty block left at line %d: %s' % (k + 1, l.strip()))


def tidy_once(path):
    lines = open(path).read().split('\n')
    out = []
    i = 0
    n = 0
    while i < len(lines):
        l = lines[i]
        m = re.match(r'^(\s*)(\} )?(else )?if \((.*)\) \{$', l)
        if m and i + 2 < len(lines) and lines[i + 1].strip() == '}' and lines[i + 2].strip() == 'else {' \
                and balanced(m.group(4)):
            ind = m.group(1)
            # find the else block's end
            depth = 1
            j = i + 3
            while j < len(lines) and depth:
                depth += lines[j].count('{') - lines[j].count('}')
                j += 1
            out.append('%s%s%sif (%s) {' % (ind, m.group(2) or '', m.group(3) or '', invert(m.group(4))))
            out.extend(lines[i + 3:j])
            i = j
            n += 1
            continue
        if l.strip() == 'else {' and i + 1 < len(lines) and lines[i + 1].strip() == '}':
            i += 2
            n += 1
            continue
        out.append(l)
        i += 1
    open(path, 'w').write('\n'.join(out))
    return n


for p in sys.argv[1:]:
    tidy(p)
