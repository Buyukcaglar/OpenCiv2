#!/usr/bin/env python3
"""Address arithmetic into the game's arrays of structs, as field access.

Ghidra writes a field of an indexed struct as the address of its offset
inside the array plus index * size:

    *(short *)(param_1 * 0x58 + ADDR(0x64f384, ((u8 *)&cities + 68)) + i * 2)

which is cities[param_1].<the short array at 68>[i].  With the layouts of
src/include/civ2types.h this rewrites, in generated code:

    *(T *)(SUM)          -> PATH when T is the field's own type, else *(T *)&PATH
    SUM as an argument   -> (iptr)&PATH, or (iptr)ARRAY for an array's start

where SUM is ADDR(addr, base + offset) plus constants and index terms
E * S (each fills the array dimension whose element is S bytes; a bare E
is an index of byte elements).  Anything not resolved to a field stays as
it was.  tools/gen_c.py applies it to what it writes.
"""
import csv
import os
import re

import rewrite_fields as rf

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# Ghidra's access types and the field types of civ2types.h they read exactly
# (Ghidra's undefinedN are signed here, tools/ghidra.h).
SAME = {
    'i8': {'char', 'undefined1', 'int8_t', 'i8', 'schar'},
    'u8': {'byte', 'uchar', 'uint8_t', 'u8', 'unsigned char'},
    'i16': {'short', 'undefined2', 'int16_t', 'i16'},
    'u16': {'ushort', 'word', 'uint16_t', 'u16', 'unsigned short'},
    'i32': {'int', 'undefined4', 'iptr', 'long', 'int32_t', 'i32'},
    'u32': {'uint', 'uptr', 'dword', 'ulong', 'uint32_t', 'u32', 'unsigned int'},
}
_STATE = None


def state():
    global _STATE
    if _STATE is None:
        structs = rf.parse_structs()
        arrays = {}
        for r in csv.DictReader(open(os.path.join(ROOT, 're', 'symbols.tsv')), delimiter='\t',
                                fieldnames=['addr', 'kind', 'name', 'type']):
            if r['kind'] != 'data' or not r['type'] or '*' in r['type']:
                continue
            m = re.match(r'(\w+)((?:\[\w+\])*)$', r['type'].replace(' ', ''))
            if not m or m.group(1) not in structs:
                continue
            dims = [int(d, 0) for d in re.findall(r'\[(\w+)\]', m.group(2))]
            arrays[r['name']] = (m.group(1), dims)
        _STATE = (structs, arrays)
    return _STATE


def field_type(base_t, base_dims, segs, structs):
    """The scalar type at the end of a resolved path."""
    t, dims = base_t, list(base_dims)
    for s in segs:
        if s[0] == '[]':
            dims = dims[1:]
        else:
            for foff, name, ft, fd in structs[t][1]:
                if name == s[1]:
                    t, dims = ft, list(fd)
                    break
    return t, dims


def resolve_sum(inner):
    """(path, field type, trailing dims) for a '+' sum holding one ADDR term
    into a struct array, or None."""
    structs, arrays = state()
    terms = top_terms(inner)
    addr_terms = [t for t in terms if t.lstrip().startswith('ADDR(')]
    if len(addr_terms) != 1:
        return None
    m = re.match(r'\s*ADDR\(0x[0-9a-f]+, \(\(u8 \*\)&(\w+) \+ (\d+)\)\)\s*$', addr_terms[0])
    if not m or m.group(1) not in arrays:
        return None
    name, off = m.group(1), int(m.group(2))
    t, dims = arrays[name]
    idx = []
    for term in terms:
        if term is addr_terms[0]:
            continue
        s = term.strip()
        if re.match(r'^-?(0x[0-9a-f]+|\d+)$', s):
            off += int(s, 0)
            continue
        es = rf.split_index(s)
        if es and es[1] > 0:
            idx.append(es)
        elif s:
            idx.append((s, 1))
    segs = rf.resolve(off, t, dims, structs)
    if segs is None:
        return None
    repl = {}
    for e, stride in idx:
        for i in range(len(segs) - 1, -1, -1):
            if segs[i][0] == '[]' and segs[i][2] == stride and i not in repl:
                repl[i] = e
                break
        else:
            return None
    out = name
    for i, sg in enumerate(segs):
        if sg[0] == '.':
            out += '.' + sg[1]
        elif i in repl:
            e = repl[i] if re.match(r'^[\w.\[\]]+$', repl[i]) else '(%s)' % repl[i]
            out += '[%s]' % (e if sg[1] == 0 else '%s + %d' % (e, sg[1]))
        else:
            out += '[%d]' % sg[1]
    ft, rest = field_type(t, dims, segs, structs)
    return out, ft, rest


def top_terms(expr):
    """Top-level '+' terms (a leading unary '-' stays with its term)."""
    terms, depth, start = [], 0, 0
    for i, c in enumerate(expr):
        if c in '([':
            depth += 1
        elif c in ')]':
            depth -= 1
        elif c == '+' and depth == 0:
            terms.append(expr[start:i])
            start = i + 1
    terms.append(expr[start:])
    return terms


def apply(text):
    if 'ADDR(' not in text:
        return text
    out, i = [], 0
    while True:
        k = text.find('ADDR(', i)
        if k < 0:
            out.append(text[i:])
            return ''.join(out)
        # the innermost '(' ... ')' group around the ADDR term
        depth, j = 0, k - 1
        while j >= 0:
            c = text[j]
            if c in ')]':
                depth += 1
            elif c in '([':
                if depth == 0:
                    break
                depth -= 1
            elif c in ';{}' and depth == 0:
                j = -1
                break
            j -= 1
        if j < 0 or text[j] != '(':
            out.append(text[i:k + 5])
            i = k + 5
            continue
        end = rf.matching(text, j, '(', ')')
        inner = text[j + 1:end]
        before = text[:j]
        dm = re.search(r'\*\(([A-Za-z_][\w ]*?)\s*\*\)$', before)
        rep = None
        r = None
        # a group whose terms include commas is an argument list, not a sum
        args = split_args(inner)
        if len(args) == 1:
            r = resolve_sum(inner)
        if r and dm:
            path, ft, rest = r
            typ = dm.group(1).strip()
            start = dm.start()
            if not rest and typ in SAME.get(ft, ()):
                rep = (start, end + 1, path)
            else:
                rep = (start, end + 1, '*(%s *)&%s' % (typ, path))
        elif len(args) > 1:
            # a call: rewrite each argument that is a sum on its own
            new_args, changed = [], False
            for a in args:
                ra = resolve_sum(a) if 'ADDR(' in a else None
                if ra:
                    path, ft, rest = ra
                    if path.endswith('[0]'):
                        path = path[:-3]
                    new_args.append(' ' + '(iptr)&' + path if a.startswith(' ') else '(iptr)&' + path)
                    changed = True
                else:
                    new_args.append(a)
            if changed:
                rep = (j + 1, end, ','.join(new_args))
        if rep:
            out.append(text[i:rep[0]])
            out.append(rep[2])
            i = rep[1]
        else:
            out.append(text[i:k + 5])
            i = k + 5


def split_args(expr):
    args, depth, start = [], 0, 0
    for i, c in enumerate(expr):
        if c in '([':
            depth += 1
        elif c in ')]':
            depth -= 1
        elif c == ',' and depth == 0:
            args.append(expr[start:i])
            start = i + 1
    args.append(expr[start:])
    return args


if __name__ == '__main__':
    import sys
    for p in sys.argv[1:]:
        t = open(p).read()
        n = apply(t)
        if n != t:
            open(p, 'w').write(n)
            print(p)
