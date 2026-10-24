#!/usr/bin/env python3
"""Fix C-isms the C++ compiler reports (step 6), from its error output:

    cxx_fix.py casts ERRORS.txt   drop an integer cast where the code wants
                                  the pointer it was cast from:
                                  f((iptr)&x) -> f(&x), (void *)((iptr)p) -> p
    cxx_fix.py ptrcasts ERRORS.txt  an explicit cast where C converted between
                                  unrelated pointer types: f(dlg) -> f((B *)(dlg))
                                  (errors of g++ -fpermissive: what it still
                                  rejects)
    cxx_fix.py convcasts ERRORS.txt  the same for any conversion strict C++
                                  rejects (int <-> pointer too)
    cxx_fix.py simplify FILES...  (T *)((iptr)x) -> (T *)x; (T*)(x) -> (T *)x
    cxx_fix.py useless ERRORS.txt drop the casts g++ -Wuseless-cast reports
    cxx_fix.py untyped FILES...   calls through Ghidra's `code` type
                                  (*(code *)p)(a, b) -> call_untyped(p, a, b)

Only a cast of one operand followed by , ) ; or ] is dropped (anything else
could change the arithmetic).  Run the compiler again afterwards: what the
fix leaves wrong shows up as a new error.
"""
import collections
import re
import sys

INT = r'(?:iptr|uptr|i32|u32|int|uint|i16|u16|short|ushort|long|ulong)'
PTR_CAST = r'(?:void|char|i8|u8|byte|undefined)\s*\*'
CAST = re.compile(r'\(\s*(?:%s|%s)\s*\)\s*' % (INT, PTR_CAST))
INT_CAST = re.compile(r'\(\s*%s\s*\)\s*' % INT)
VOID_CAST = re.compile(r'\(\s*void\s*\*\s*\)\s*')
IDENT = re.compile(r'[A-Za-z_]\w*')


def match_paren(s, i):
    """Index after the bracket group opening at s[i]."""
    pairs = {'(': ')', '[': ']'}
    stack = [pairs[s[i]]]
    j = i + 1
    while j < len(s) and stack:
        c = s[j]
        if c == '"' or c == "'":
            q = c
            j += 1
            while j < len(s) and s[j] != q:
                j += 2 if s[j] == '\\' else 1
        elif c in pairs:
            stack.append(pairs[c])
        elif c in ')]':
            if c != stack[-1]:
                return -1
            stack.pop()
        j += 1
    return j if not stack else -1


def unary_end(s, i):
    """End of the unary expression starting at s[i] (or -1)."""
    while i < len(s) and s[i] in '&*' and s[i:i + 2] != '&&':
        i += 1
    if i < len(s) and s[i] == '(':
        j = match_paren(s, i)
        if j < 0:
            return -1
        # a cast followed by its operand
        if CAST.match(s, i) or re.match(r'\(\s*[A-Za-z_]\w*(?:\s+[A-Za-z_]\w*)*\s*\*+\s*\)', s[i:j]):
            return unary_end(s, j + len(s[j:]) - len(s[j:].lstrip()))
        i = j
    else:
        m = IDENT.match(s, i)
        if not m:
            m = re.compile(r'0x[0-9a-fA-F]+|\d+').match(s, i)
            if not m:
                return -1
        i = m.end()
    while i < len(s):
        if s[i] in '([':
            j = match_paren(s, i)
            if j < 0:
                return -1
            i = j
        elif s.startswith('->', i):
            m = IDENT.match(s, i + 2)
            if not m:
                return -1
            i = m.end()
        elif s[i] == '.':
            m = IDENT.match(s, i + 1)
            if not m:
                return -1
            i = m.end()
        else:
            break
    return i


def errors(path):
    for line in open(path):
        m = re.match(r'(src/[^:]+):(\d+):(\d+): error: (?:invalid conversion|cannot convert) from \'(.*?)\'.* to \'(.*?)\'', line)
        if m:
            yield m.group(1), int(m.group(2)), int(m.group(3)), m.group(4), m.group(5)


def drop_casts(path):
    sites = collections.defaultdict(set)
    for f, ln, col, frm, to in errors(path):
        if to.endswith('*') or '(*)' in to:
            sites[f].add((ln, col))
    done = 0
    for f, cols in sites.items():
        lines = open(f).read().split('\n')
        # right to left within a line so earlier columns stay valid
        for ln, col in sorted(cols, key=lambda x: (x[0], -x[1])):
            s = lines[ln - 1]
            i = col - 1
            new = None
            # the column is at the argument (or just inside an opening paren)
            for k in (i, i + 1):
                m = INT_CAST.match(s, k) or VOID_CAST.match(s, k)
                if not m:
                    continue
                e = unary_end(s, m.end())
                if e < 0:
                    continue
                rest = s[e:].lstrip()
                if not rest or rest[0] not in ',);]':
                    continue
                operand = s[m.end():e]
                if m.re is VOID_CAST:
                    # (void *)((iptr)X) or (void *)(iptr)X -> X; any other
                    # (void *) cast stays
                    inner = operand
                    if inner.startswith('(') and match_paren(inner, 0) == len(inner):
                        inner = inner[1:-1].strip()
                    m2 = INT_CAST.match(inner)
                    if not m2 or unary_end(inner, m2.end()) != len(inner):
                        continue
                    operand = inner[m2.end():]
                new = s[:k] + operand + s[e:]
                break
            if new is not None and new != s:
                lines[ln - 1] = new
                done += 1
        open(f, 'w').write('\n'.join(lines))
    print('%d casts dropped' % done)


def expr_end(s, i):
    """End of the expression starting at s[i]: the next , ) ; at its level
    (-1 if the line ends first)."""
    depth = 0
    j = i
    while j < len(s):
        c = s[j]
        if c in '"\'':
            q = c
            j += 1
            while j < len(s) and s[j] != q:
                j += 2 if s[j] == '\\' else 1
        elif c in '([{':
            depth += 1
        elif c in ')]}':
            if depth == 0:
                return j
            depth -= 1
        elif c in ',;' and depth == 0:
            return j
        j += 1
    return -1


def arg_start(s, i):
    """Start of the argument (or right-hand side) that contains s[i]: just
    after the ( , or = that opens it at its level (-1 if not on this line)."""
    depth = 0
    j = i if i < len(s) and s[i] in ')]' else i - 1
    while j >= 0:
        c = s[j]
        if c in ')]':
            depth += 1
        elif c in '([':
            if depth == 0:
                break
            depth -= 1
        elif c == ',' and depth == 0:
            break
        elif c == '=' and depth == 0 and s[j - 1:j] not in ('=', '!', '<', '>') and s[j + 1:j + 2] != '=':
            break
        j -= 1
    if j < 0:
        return -1
    j += 1
    while j < len(s) and s[j] == ' ':
        j += 1
    return j


def ptr_casts(path, any_conversion=False):
    sites = collections.defaultdict(dict)
    for line in open(path):
        m = re.match(r"(src/[^:]+):(\d+):(\d+): error: (?:cannot convert|invalid conversion from) '.*?'(?: \{aka [^}]*\})? to '(.*?)'", line)
        if not m:
            continue
        to = m.group(4)
        if to == 'iptr (*)()':
            to = 'code *'
        if to.endswith('*') or (any_conversion and re.match(r'^[A-Za-z_]\w*$', to)):
            sites[m.group(1)][(int(m.group(2)), int(m.group(3)))] = to
    done = skipped = 0
    for f, cols in sites.items():
        lines = open(f).read().split('\n')
        for (ln, col), to in sorted(cols.items(), key=lambda x: (x[0][0], -x[0][1])):
            s = lines[ln - 1]
            i = col - 1
            # a call is reported at its ( : start from the function's name
            m = re.search(r'[A-Za-z_]\w*\s*$', s[:i])
            if i < len(s) and s[i] == '(' and m:
                i = m.start()
            # g++ points at the operator of a binary expression: start from
            # the beginning of the argument (after the ( or , that opens it)
            if not (s[:i].rstrip() and s[:i].rstrip()[-1] in '=(,') or not re.match(r'[A-Za-z_(&*]', s[i]):
                k = arg_start(s, i)
                if k >= 0:
                    i = k
            e = expr_end(s, i)
            before = s[:i].rstrip()
            if not before and ln > 1:
                # the argument starts a continuation line: what ends the line before
                before = lines[ln - 2].rstrip()
            if (e < 0 or not s[i:e].strip() or not before or before[-1] not in '=(,'
                    or not re.match(r'[A-Za-z_(&*0-9]', s[i])):
                skipped += 1
                continue
            lines[ln - 1] = s[:i] + '(%s)(%s)' % (to, s[i:e].rstrip()) + s[i + len(s[i:e].rstrip()):]
            done += 1
        open(f, 'w').write('\n'.join(lines))
    print('%d casts added, %d sites left for hand' % (done, skipped))


PTR_TYPE = r'(?:const\s+)?[A-Za-z_]\w*(?:\s*\*)+'


def simplify(paths):
    done = 0
    for f in paths:
        s = open(f).read()
        o = s
        # (T *)((iptr)X) -> (T *)X  and  (T *)((iptr)(X)) -> (T *)(X)
        while True:
            m = None
            for m in re.finditer(r'\((%s)\s*\)\(\(\s*(?:iptr|uptr|int|uint|i32|u32)\s*\)' % PTR_TYPE, s):
                inner_open = m.end() - len(re.search(r'\(\s*(?:iptr|uptr|int|uint|i32|u32)\s*\)$', m.group(0)).group(0)) - 1
                close = match_paren(s, inner_open)
                e = unary_end(s, m.end())
                if close > 0 and e == close - 1:
                    s = s[:m.start()] + '(%s)' % m.group(1) + s[m.end():e] + s[close:]
                    done += 1
                    break
            else:
                break
        # (T*)(simple) -> (T *)simple
        def tidy(m):
            t = re.sub(r'\s*(\*+)$', lambda x: ' ' + x.group(1), m.group(1).strip())
            return '(%s)%s' % (t, m.group(2))
        # (not when a postfix operator follows: (T *)(f)(x) is not (T *)f(x))
        s, n = re.subn(r'\((%s)\)\(([A-Za-z_]\w*(?:(?:->|\.)[A-Za-z_]\w*|\[[^\[\]()]*\])*)\)(?!\s*(?:[\w(\[.&]|->))' % PTR_TYPE, tidy, s)
        done += n
        if s != o:
            open(f, 'w').write(s)
    print('%d simplified' % done)


def useless(path):
    sites = collections.defaultdict(set)
    for line in open(path):
        m = re.match(r"(src/[^:]+):(\d+):(\d+): (?:warning|error): useless cast to type '(.*?)'", line)
        if m:
            sites[m.group(1)].add((int(m.group(2)), int(m.group(3))))
    done = 0
    for f, cols in sites.items():
        lines = open(f).read().split('\n')
        for ln, col in sorted(cols, key=lambda x: (x[0], -x[1])):
            s = lines[ln - 1]
            # the location is the cast's ( or its operand: find the cast at or before it
            i = col - 1
            k = s.rfind('(', 0, i + 1)
            while k >= 0:
                m = re.match(r'\(\s*(?:const\s+)?[A-Za-z_]\w*(?:\s*\*)*\s*\)\s*', s[k:])
                if m and k + m.end() > i - 1:
                    break
                k = s.rfind('(', 0, k)
            if k < 0 or not m:
                continue
            rest = s[k + m.end():]
            # (T)(x) -> x when the parentheses only held the operand (and
            # x has no prefix operator a following [ ( . -> would bind into)
            if rest.startswith('('):
                close = match_paren(s, k + m.end())
                inner = s[k + m.end() + 1:close - 1]
                # (the line may end there: the operator can be on the next one)
                postfix = re.match(r'\s*(\[|\(|\.|->|$)', s[close:]) if close > 0 else None
                if (close > 0 and unary_end(inner, 0) == len(inner)
                        and not (postfix and re.match(r'[&*!~+-]|\(', inner))):
                    lines[ln - 1] = s[:k] + inner + s[close:]
                    done += 1
                    continue
            lines[ln - 1] = s[:k] + s[k + m.end():]
            done += 1
        open(f, 'w').write('\n'.join(lines))
    print('%d useless casts dropped' % done)


def untyped(paths):
    done = 0
    for f in paths:
        s = open(f).read()
        out, i = [], 0
        while True:
            k = s.find('(*', i)
            if k < 0:
                break
            inner = s[k + 2:].lstrip()
            if not re.match(r'\(*\*?\(*code \*(?: ?\*)?\)', inner):
                out.append(s[i:k + 2])
                i = k + 2
                continue
            close = match_paren(s, k)          # just after the (*fn) group
            e = close
            if e >= 0:
                e += len(s[e:]) - len(s[e:].lstrip())
            if e < 0 or e >= len(s) or s[e] != '(':
                out.append(s[i:k + 2])
                i = k + 2
                continue
            a = match_paren(s, e)
            fn = s[k + 2:close - 1].strip()
            args = s[e + 1:a - 1].strip()
            out.append(s[i:k] + 'call_untyped(' + fn + (', ' + args if args else '') + ')')
            i = a
            done += 1
        out.append(s[i:])
        new = ''.join(out)
        if new != s:
            open(f, 'w').write(new)
    print('%d calls rewritten' % done)


def main():
    if len(sys.argv) == 3 and sys.argv[1] == 'casts':
        drop_casts(sys.argv[2])
    elif len(sys.argv) == 3 and sys.argv[1] == 'ptrcasts':
        ptr_casts(sys.argv[2])
    elif len(sys.argv) == 3 and sys.argv[1] == 'convcasts':
        ptr_casts(sys.argv[2], any_conversion=True)
    elif len(sys.argv) >= 3 and sys.argv[1] == 'simplify':
        simplify(sys.argv[2:])
    elif len(sys.argv) == 3 and sys.argv[1] == 'useless':
        useless(sys.argv[2])
    elif len(sys.argv) >= 3 and sys.argv[1] == 'untyped':
        untyped(sys.argv[2:])
    else:
        print(__doc__)
        return 1
    return 0


if __name__ == '__main__':
    sys.exit(main())
