#!/usr/bin/env python3
"""Rewrite address-based code in hand-written sources to use named types.

When globals are named and typed (re/symbols.tsv, src/include/civ2types.h)
the generated code follows automatically (Ghidra prints `units[i].owner`);
hand-written files (src/game, src/crt) still say `(&DAT_006560f7)[i * 0x20]`
or call `FUN_005b8931`.  This rewrites, in place:

    FUN_ADDR / thunk_FUN_ADDR            -> the function's name
    DAT_ADDR                             -> full path, e.g. game.turn, civs[3].gold
    (&DAT_ADDR)[E * S]                   -> path with the index of stride S replaced by E
    *(T *)(&DAT_ADDR + E * S)            -> same
    &DAT_ADDR + E * S                    -> same (array/struct value decays)
and reports references into named globals it could not rewrite.  Repeats
until nothing changes (rewrites can nest).

Usage: rewrite_fields.py [FILES...]   (default: src/game/*.cpp src/crt/*.c)
"""
import glob
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BASIC = {'i8': 1, 'u8': 1, 'i16': 2, 'u16': 2, 'i32': 4, 'u32': 4, 'char': 1, 'void': 1}


def prod(xs):
    n = 1
    for x in xs:
        n *= x
    return n


def type_size(t, structs):
    return BASIC[t] if t in BASIC else structs[t][0]


def parse_structs():
    """struct name -> (size, [(offset, field, type, dims)]) in the original 32-bit packed layout."""
    text = open(os.path.join(ROOT, 'src', 'include', 'civ2types.h')).read()
    text = re.sub(r'/\*.*?\*/', '', text, flags=re.S)
    structs = {}
    for m in re.finditer(r'typedef struct \w+ \{(.*?)\}\s*(\w+);', text, re.S):
        off, fields = 0, []
        for fm in re.finditer(r'(\w+)\s*(\*?)\s*(\w+)\s*((?:\[\w+\])*)\s*;', m.group(1)):
            t, ptr, name, dims = fm.group(1), fm.group(2), fm.group(3), fm.group(4)
            if ptr:
                t = 'u32'           # pointers are 4 bytes in the original layout
            dl = [int(d, 0) for d in re.findall(r'\[(\w+)\]', dims)]
            fields.append((off, name, t, dl))
            off += type_size(t, structs) * prod(dl)
        structs[m.group(2)] = (off, fields)
    return structs


def resolve(off, t, dims, structs):
    """Path segments for byte offset `off` inside an object of type t[dims]:
    ('[]', index, elem_size) or ('.', field).  None unless off starts a scalar."""
    segs = []
    while True:
        if dims:
            elem = type_size(t, structs) * prod(dims[1:])
            k, off = divmod(off, elem)
            if k >= dims[0]:
                return None
            segs.append(('[]', k, elem))
            dims = dims[1:]
            continue
        if t in BASIC:
            return segs if off == 0 else None
        for foff, name, ft, fd in structs[t][1]:
            if foff <= off < foff + type_size(ft, structs) * prod(fd):
                segs.append(('.', name))
                off -= foff
                t, dims = ft, fd
                break
        else:
            return None


def render(name, segs, override=None):
    out = name
    for i, s in enumerate(segs):
        if s[0] == '.':
            out += '.' + s[1]
        else:
            out += '[%s]' % (override[1] if override and override[0] == i else s[1])
    return out


def split_terms(expr):
    """Top-level '+'-separated terms of an index expression -> [(E, S)], S = 1 without '*'."""
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
    out = []
    for t in terms:
        es = split_index(t)
        out.append(es if es else (t.strip(), 1))
    return out


def split_index(expr):
    """'E * S' at top level -> (E, S)."""
    depth = 0
    for i in range(len(expr) - 1, -1, -1):
        c = expr[i]
        if c in ')]':
            depth += 1
        elif c in '([':
            depth -= 1
        elif c == '*' and depth == 0:
            try:
                return expr[:i].strip(), int(expr[i + 1:].strip(), 0)
            except ValueError:
                return None
    return None


def matching(t, i, open_c, close_c):
    depth = 0
    for j in range(i, len(t)):
        if t[j] == open_c:
            depth += 1
        elif t[j] == close_c:
            depth -= 1
            if depth == 0:
                return j
    return -1


def main():
    structs = parse_structs()
    globals_ = []   # (base, size, name, type, dims)
    funcs = {}
    for line in open(os.path.join(ROOT, 're', 'symbols.tsv')):
        f = line.rstrip('\n').split('\t')
        if len(f) >= 3 and f[1] == 'func':
            funcs[f[0]] = f[2]
        if len(f) < 4 or f[1] != 'data' or '*' in f[3]:
            continue
        m = re.match(r'(\w+)((?:\[\w+\])*)$', f[3].replace(' ', ''))
        t, dims = m.group(1), [int(d, 0) for d in re.findall(r'\[(\w+)\]', m.group(2))]
        if t not in BASIC and t not in structs:
            continue
        globals_.append((int(f[0], 16), type_size(t, structs) * prod(dims), f[2], t, dims))

    def path(addr):
        for base, size, name, t, dims in globals_:
            if base <= addr < base + size:
                segs = resolve(addr - base, t, dims, structs)
                return (name, segs) if segs is not None else ('?', None)
        return None

    def indexed(addr, inner):
        """Path of addr with array indices replaced by the terms of `inner`
        (each term E*S fills the index whose element size is S)."""
        p = path(addr)
        if not p or p[1] is None:
            return None
        name, segs = p
        segs = list(segs)
        repl = {}
        for e, stride in split_terms(inner):
            for i in range(len(segs) - 1, -1, -1):
                if segs[i][0] == '[]' and segs[i][2] == stride and segs[i][1] == 0 and i not in repl:
                    repl[i] = e
                    break
            else:
                return None
        out = name
        for i, sg in enumerate(segs):
            out += '.' + sg[1] if sg[0] == '.' else '[%s]' % repl.get(i, sg[1])
        return out

    pat = re.compile(r'\*\(\s*[\w ]+?\s*\*\s*\)\s*\(\s*&_?DAT_([0-9a-f]{8})\s*\+'   # 1: *(T *)(&DAT + E*S)
                     r'|\(&_?DAT_([0-9a-f]{8})\)\['                              # 2: (&DAT)[E*S]
                     r'|&_?DAT_([0-9a-f]{8})\s*\+'                               # 3: &DAT + E*S
                     r'|\b_?DAT_([0-9a-f]{8})\b')                                # 4: DAT (also &DAT)

    def one_pass(text):
        out, i = [], 0
        while True:
            m = pat.search(text, i)
            if not m:
                out.append(text[i:])
                return ''.join(out)
            out.append(text[i:m.start()])
            rep, end = None, m.end()
            if m.group(1) or m.group(3):
                addr = int(m.group(1) or m.group(3), 16)
                if m.group(1):
                    close = matching(text, m.start() + m.group(0).index('(&'), '(', ')')
                    inner, end = text[m.end():close], close + 1
                else:
                    j, depth = m.end(), 0
                    while j < len(text) and not (depth == 0 and text[j] in ',;)'):
                        depth += text[j] in '(['
                        depth -= text[j] in ')]'
                        j += 1
                    inner, end = text[m.end():j], j
                rep = indexed(addr, inner)
                if rep and m.group(3):
                    rep = '&' + rep        # an address, not a value
            elif m.group(2):
                close = matching(text, m.end() - 1, '[', ']')
                rep = indexed(int(m.group(2), 16), text[m.end():close])
                if rep:
                    end = close + 1
            else:
                p = path(int(m.group(4), 16))
                if p and p[1] is not None:
                    rep = render(*p)
            if rep is None and m.group(3):
                # Pointer arithmetic on the address itself ((char *)&DAT + 1):
                # name the object, keep the arithmetic.
                p = path(int(m.group(3), 16))
                if p and p[1] is not None:
                    rep, end = re.sub(r'_?DAT_[0-9a-f]{8}', render(*p), m.group(0)), m.end()
            if rep is None:
                out.append(m.group(0))
                i = m.end()
            else:
                out.append(rep)
                i = end

    files = sys.argv[1:] or sorted(glob.glob(os.path.join(ROOT, 'src', 'game', '*.cpp')) +
                                   glob.glob(os.path.join(ROOT, 'src', 'crt', '*.c')))
    for fpath in files:
        text = orig = open(fpath).read()
        for a, n in funcs.items():
            text = re.sub(r'\b(thunk_)?FUN_%s\b' % a, n, text)
        # Local address macros for addresses that now belong to a named global
        # (copied from generated code) are obsolete; so are any already mangled.
        text = re.sub(r'^#(?:define|undef) _?DAT_([0-9a-f]{8})\b.*\n',
                      lambda m: '' if path(int(m.group(1), 16)) else m.group(0), text, flags=re.M)
        text = re.sub(r'^#(?:define|undef) \w+[.\[].*\n', '', text, flags=re.M)
        for _ in range(5):
            new = one_pass(text)
            if new == text:
                break
            text = new
        left = sorted({m.group(0) for m in re.finditer(r'\b_?DAT_([0-9a-f]{8})\b', text) if path(int(m.group(1), 16))})
        if text != orig:
            open(fpath, 'w').write(text)
            print('rewrote %s' % os.path.relpath(fpath, ROOT))
        if left:
            print('  %s: could not rewrite %s' % (os.path.relpath(fpath, ROOT), ' '.join(left)))


if __name__ == '__main__':
    main()
