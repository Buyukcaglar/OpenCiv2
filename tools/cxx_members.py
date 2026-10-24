#!/usr/bin/env python3
"""Raw accesses through a struct member's address as typed members, correct
by construction:

    cxx_members.py [--into SRC=DST]... FILE...

rewrites `*(T *)(B->m + E)`, `*(T *)((u8 *)&B->m + E)`, `*(T *)(B->m)`,
`*(T *)B->m`, `*(T *)&B->m` (and B.m for a global block variable) where B is
a variable declared `S *`, `((S *)v)` or a global block, m a member of S at
offset O whose elements are bytes (or E is absent): the byte offset O + E
names a typed member f of S (an integer or pointer, or an array of them, of
T's size; not a field_/pad_ member, not bytes unless T is a byte) as B->f or
B->f[I] with I = (E + O - offsetof f) / sizeof T (cxx_array: every term of E
divisible by sizeof T, kept with its type, so it wraps as the byte offset
did).  With --into SRC=DST, S = SRC is read as DST (B becomes ((DST *)v)):
the member's offset is SRC's and f is DST's, at the same address.

Signedness as cxx_fields: a member of the other signedness is read as (T)f,
written as f by statements = += ... whose value is unused; a pointer read
as a 4-byte integer (or the reverse) as (T)f, never written.  Block members
(B.m) only name an element of m itself (m retyped by hand, same size), and
with --block M,... only those members (an index past a member that is a
placeholder [1] would not be an element of it).
Each rewrite is listed in run/fields_check.cpp.
"""
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
import cxx_fields as F  # noqa: E402
from cxx_fix import match_paren  # noqa: E402
from cxx_array import index as array_index, split_terms, num  # noqa: E402

BYTE_PTR = r'\(\s*(?:u8|i8|byte|char|uchar|undefined)\s*\*\s*\)'
CAST = re.compile(r'\*\s*\(\s*(%s)\s*\*\s*\)\s*' % F.TYPE)


def esize(t):
    """(element type, element size, count) of a layout type."""
    am = re.match(r'(.*?) ?\[(\d+)\]$', t)
    if am:
        return am.group(1).strip(), None, int(am.group(2))
    return t.strip(), None, None


def members(s):
    out = []
    for m, off, size, t in F.LAYOUT[s]['members']:
        et, _, k = esize(t)
        es = size // k if k else size
        out.append((m, off, size, t, et, es, k))
    return out


PREFER = []


def find(s, n, t, has_var):
    """Typed member of s at byte offset n read as t: (name, index bytes, elem type, kind)."""
    want = F.canon(t)
    tsize = want[1] if want[0] in 'su' else 4
    best = []
    for m, off, size, mt, et, es, k in members(s):
        if not off <= n < off + size or F.unnamed(m) or es != tsize:
            continue
        if (n - off) % es:
            continue
        if has_var and k is None:
            continue
        ec = F.canon(et)
        if ec[0] == 's' or ec[0] == 'u':
            if ec[1] == 1 and tsize != 1:
                continue
            if want == ec:
                kind = 'exact'
            elif want[0] in 'su':
                kind = 'sign'
            else:
                kind = 'ptr'
        elif et.endswith('*'):
            kind = 'exact' if want == ec else 'ptr'
        else:
            continue
        pref = not any(m.startswith(p) for p in PREFER)
        best.append(((pref, kind != 'exact', kind == 'ptr'), (m, n - off, et, kind, k)))
    if not best:
        return None
    best.sort(key=lambda b: b[0])
    return best[0][1]


def block_members():
    out = {}
    text = open(os.path.join(ROOT, 'src', 'data', 'gamedata.h')).read()
    structs = {}
    for sm in re.finditer(r'(?m)^struct\s+(\w+)\s*\{\n(.*?)^\};', text, re.S):
        mem = {}
        for dm in re.finditer(r'(?m)^\s*(%s?)\s*\b(\w+)\s*(\[(\d+)\])?\s*;' % F.TYPE, sm.group(2)):
            mem[dm.group(2)] = (dm.group(1).strip(), int(dm.group(4)) if dm.group(4) else None)
        structs[sm.group(1)] = mem
    for em in re.finditer(r'(?m)^extern\s+struct\s+(\w+)\s+(\w+)\s*;', text):
        if em.group(1) in structs:
            out[em.group(2)] = structs[em.group(1)]
    return out


BLOCKS = {}


def strip_parens(s):
    s = s.strip()
    while s.startswith('(') and match_paren(s, 0) == len(s):
        s = s[1:-1].strip()
    return s


BASE = re.compile(r'^(?:\(\s*\(\s*(\w+)\s*\*\s*\)\s*(\w+)\s*\)|(\w+))\s*(->|\.)\s*(\w+)$')


def parse_base(e):
    """(cast struct or None, variable, op, member) of B->m / B.m."""
    m = BASE.match(strip_parens(e))
    if not m:
        return None
    if m.group(1):
        return m.group(1), m.group(2), m.group(4), m.group(5)
    return None, m.group(3), m.group(4), m.group(5)


CHAIN = re.compile(r'&?\s*(?:\(\s*\(\s*\w+\s*\*\s*\)\s*\w+\s*\)|\w+)\s*(?:->|\.)\s*\w+')


def operand(m, i):
    """The operand after a cast at i: (end, text, grouped)."""
    # a member chain [&]v->m / [&]((S *)v)->m
    x = CHAIN.match(m, i)
    if x:
        if F.next_tok(m, x.end())[0] in ('[', '(', '->', '.'):
            return None
        return x.end(), (i, x.end()), False
    if m[i] == '(':
        e = match_paren(m, i)
        return e, (i + 1, e - 1), True
    return None


def idx_of(e, size):
    r = array_index(e.replace('->', '\x01'), size)
    return None if r is None else r.replace('\x01', '->')


def terms_of(e):
    e = re.sub(r'\s+', ' ', e.strip()).replace('->', '\x01')
    return [(sg, t.replace('\x01', '->')) for sg, t in split_terms(e)]


def split_addr(inner):
    """(address expression, [(sign, term)]) of `A + E`."""
    terms = split_terms(re.sub(r'\s+', ' ', inner.strip()))
    return terms[0], terms[1:]


def rewrite(body, ds, into, checks, stats):
    m = F.masked(body)
    edits = []
    for cm in CAST.finditer(m):
        t = cm.group(1)
        pt, pj = F.prev_tok(m, cm.start())
        if pt == ')':
            # a cast (T)*(...) or a multiplication (x)*(...)
            o = m.rfind('(', 0, pj)
            if not re.fullmatch(r'\(\s*%s\s*\)' % F.TYPE, m[o:pj + 1]) or o < 0:
                continue
        elif pt == ']' or re.match(r'\w', pt or ' ') and pt not in F.KEYWORDS:
            continue    # a multiplication
        op = operand(m, cm.end())
        if not op:
            continue
        end, (ia, ib), grouped = op
        if any(a <= cm.start() < b for a, b, _ in edits):
            continue    # inside a rewritten access: the next run
        inner = body[ia:ib]
        addr_terms = terms_of(inner) if grouped else [('+', inner)]
        if not addr_terms or addr_terms[0][0] != '+':
            continue
        a = addr_terms[0][1].strip()
        rest = addr_terms[1:]
        a = strip_parens(a)
        byte_cast = False
        bm = re.match(BYTE_PTR + r'\s*(.*)$', a, re.S)
        if bm:
            byte_cast = True
            a = strip_parens(bm.group(1))
        amp = a.startswith('&')
        if amp:
            a = a[1:].strip()
        pb = parse_base(a)
        vm = re.match(r'^\(\s*(?:iptr|uptr|int|uint|i32|u32|u8\s*\*|i8\s*\*|char\s*\*|byte\s*\*)\s*\)\s*(\w+)$', a)
        if not pb and vm and not amp and grouped and vm.group(1) in ds and F.struct_of(ds[vm.group(1)][0]):
            # (iptr)v + E, v an S *: bytes from v
            pb = (None, vm.group(1), '->', None)
            byte_cast = True
        if not pb:
            continue
        cast, v, opr, mem = pb
        if opr == '.':
            if cast or v not in BLOCKS or mem not in BLOCKS[v]:
                continue
            r = block_access(m, cm, end, t, v, mem, rest, amp, byte_cast)
            if r:
                edits.extend(r)
                stats['block'] += 1
            continue
        if cast:
            s = cast
        elif v in ds:
            s = F.struct_of(ds[v][0])
        else:
            s = None
        if not s or s not in F.LAYOUT:
            continue
        if mem is None:
            off, k, es = 0, 1, 1
        else:
            mi = [x for x in members(s) if x[0] == mem]
            if not mi:
                continue
            _, off, size, mt, et, es, k = mi[0]
        if rest and not byte_cast:
            # pointer arithmetic on the member: bytes only
            if amp or k is None or es != 1:
                continue
        if amp and not byte_cast and rest:
            continue
        dst, base = s, ('((%s *)%s)' % (cast, v) if cast else v)
        if s in into:
            dst = into[s]
            base = v if v in ds and F.struct_of(ds[v][0]) == dst else '((%s *)%s)' % (dst, v)
        c = 0
        var = []
        for sign, term in rest:
            n = num(term.strip())
            if n is None:
                var.append((sign, term))
            else:
                c += n if sign == '+' else -n
        n = off + c
        if n < 0 or n >= F.LAYOUT[dst]['size']:
            continue
        f = find(dst, n, t, bool(var))
        if var:
            # E's constant may reach the element before an array (x[i - 1]):
            # the nearer array start wins
            want = F.canon(t)
            tsize = want[1] if want[0] in 'su' else 4
            g = find(dst, n + tsize, t, True)
            if g and g[1] == 0 and g[4] is not None and (not f or f[1] > tsize):
                f = (g[0], -tsize, g[2], g[3], g[4])
        if not f:
            stats['left'] += 1
            continue
        fname, rel, fet, kind, fk = f
        if fk is None:
            path = fname
        else:
            es2 = F.canon(fet)[1] if F.canon(fet)[0] in 'su' else 4
            e = ' '.join(('' if i == 0 and sg == '+' else sg + ' ') + tm.strip() for i, (sg, tm) in enumerate(var))
            if not var:
                e = str(rel // es2)
            else:
                e = idx_of(e + (' + %d' % rel if rel > 0 else ' - %d' % -rel if rel < 0 else ''), es2)
            if e is None:
                stats['left'] += 1
                continue
            path = '%s[%s]' % (fname, e)
        new = access(m, cm.start(), end, t, '%s->%s' % (base, path), fet, kind)
        if new is None:
            stats['left'] += 1
            continue
        out, pend = new
        checks.append((dst, fname if fk is None else fname + '[0]', [x for x in members(dst) if x[0] == fname][0][1], fet))
        edits.append((cm.start(), end, out))
        edits.extend(pend)
        stats['named'] += 1
    return F.apply(body, edits)


def access(m, start, end, t, expr, mt, kind):
    # (the access in parentheses: its context is outside them)
    while True:
        pt, pj = F.prev_tok(m, start)
        nt, nj = F.next_tok(m, end)
        if pt != '(' or nt != ')':
            break
        bt = F.prev_tok(m, pj)[0]
        if re.match(r'\w', bt or ' ') or bt in (')', ']'):
            break
        start, end = pj, nj + 1
    nt, nj = F.next_tok(m, end)
    pt, pj = F.prev_tok(m, start)
    if pt == '&' and F.binary_and(m, pj):
        pt = '&&'
    if pt in ('&', 'sizeof'):
        return None
    if kind == 'exact':
        return expr, []
    store = pt != '*' and (nt in F.STORE_OK or nt in ('++', '--') or pt in ('++', '--'))
    if kind == 'ptr':
        if store:
            return None
        return '(%s)%s' % (F.cast_type(t), expr), []
    if store:
        if pt in ('++', '--'):
            if not F.is_statement_start(m, pj) or F.statement_end(m, end) < 0:
                return None
        elif not F.is_statement_start(m, start) or F.statement_end(m, end) < 0:
            return None
        if nt in ('/=', '%=', '>>='):
            return None
        return expr, []
    return '(%s)%s' % (F.cast_type(t), expr), []


BLOCK_ONLY = set()


def block_access(m, cm, end, t, v, mem, rest, amp, byte_cast):
    if BLOCK_ONLY and mem not in BLOCK_ONLY:
        return None
    mt, k = BLOCKS[v][mem]
    if k is None or not (amp or byte_cast or rest == []):
        return None
    want = F.canon(t)
    mc = F.canon(mt)
    if mc[0] not in 'su' or want[0] not in 'su' or mc[1] != want[1] or mc[1] == 1:
        return None
    if not byte_cast and not amp:
        return None
    e = ' '.join(('' if i == 0 and sg == '+' else sg + ' ') + tm.strip() for i, (sg, tm) in enumerate(rest)) or '0'
    if e.startswith('-'):
        return None
    idx = idx_of(e, mc[1])
    if idx is None:
        return None
    if num(idx) is not None and not 0 <= num(idx) < k:
        return None
    r = access(m, cm.start(), end, t, '%s.%s[%s]' % (v, mem, idx), mt, 'exact' if mc == want else 'sign')
    if r is None:
        return None
    return [(cm.start(), end, r[0])]


def main():
    args = sys.argv[1:]
    into = {}
    while args and args[0] in ('--into', '--prefer', '--block'):
        if args[0] == '--block':
            BLOCK_ONLY.update(args[1].split(','))
        elif args[0] == '--into':
            a, b = args[1].split('=')
            into[a] = b
        else:
            PREFER.append(args[1])
        args = args[2:]
    F.LAYOUT = F.load_layout()
    BLOCKS.update(block_members())
    checks, stats = [], {'named': 0, 'left': 0, 'block': 0}
    for f in args:
        def one(header, body):
            return rewrite(body, F.decls(header, body), into, checks, stats)
        F.each_function(f, one)
    F.write_checks([c for c in checks if c[2] is not None])
    print(stats)


if __name__ == '__main__':
    main()
