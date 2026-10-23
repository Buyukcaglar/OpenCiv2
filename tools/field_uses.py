#!/usr/bin/env python3
"""The unnamed fields (field_XX) the game code uses, where the object's type
is known, with sample lines: dossiers for naming them.

    field_uses.py OUTDIR [--per N]

Types come from `this` and the other parameters, locals declared `T *v` or
`T v`, casts ((T *)x)->field_k, and the game's globals (game, civs[i],
units[i], cities[i] ...: src/include/civ2types.h).  Classes are named per
family and offset (re/field_names.tsv; tools/type_names.py applies them);
the game's own structs per struct and field (civ2types.h is edited).
Accesses this[N].field_0 (an object read as an array of 4-byte cells: a
layout not recovered yet) are left out.
"""
import collections
import glob
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
import type_names  # noqa: E402

GLOBALS = {'game': 'GameState', 'civs': 'Civ', 'units': 'Unit', 'cities': 'City'}


def struct_types():
    """Struct names declared in civ2types.h (the game's own data)."""
    t = open(os.path.join(ROOT, 'src', 'include', 'civ2types.h')).read()
    return set(re.findall(r'\}\s*(\w+);', t))


def global_types():
    out = dict(GLOBALS)
    for line in open(os.path.join(ROOT, 're', 'symbols.tsv')):
        f = line.rstrip('\n').split('\t')
        if len(f) > 3 and f[1] == 'data' and f[3]:
            m = re.match(r'(\w+)', f[3])
            if m:
                out.setdefault(f[2], m.group(1))
    return out


KEYWORDS = ('return', 'goto', 'case', 'else', 'do', 'break', 'continue')


def local_types(body):
    """name -> type for a function's parameters, declared locals and its
    macros (frame locals and globals: #define v (*(T *)...) or (*(T **)...))."""
    types = {}
    for d in re.finditer(r'(?m)^#define (\w+) \(\*\((\w+) \*(?: ?\*)?\)', body):
        types[d.group(1)] = d.group(2)
    sig = re.search(r'\(([^(){};]*)\)\s*\n\{', body)
    if sig:
        for d in re.finditer(r'(\w+) \*?\s*(\w+)\s*(?:,|$)', sig.group(1)):
            types[d.group(2)] = d.group(1)
    for d in re.finditer(r'(?m)^  (\w+) \*?(\w+)(?:\[\w*\])?;$', body):
        if d.group(1) not in KEYWORDS:
            types[d.group(2)] = d.group(1)
    return types


def collect():
    structs = struct_types()
    gtypes = global_types()
    uses = collections.defaultdict(list)       # (owner, offset) -> lines
    for f in sorted(glob.glob(os.path.join(ROOT, 'src', 'auto', '*.c'))):
        if f.endswith('msvcrt.c'):
            continue
        text = open(f).read()
        for body in re.split(r'(?m)^(?=/\* [0-9a-f]{8}[ :])', text)[1:]:
            types = local_types(body)
            fname = re.search(r'\b(\w+)\s*\([^;{}]*\)\s*\n\{', body)
            fname = fname.group(1) if fname else '?'
            for ln in body.split('\n'):
                if 'field_' not in ln or ln.startswith('#'):
                    continue
                for m in re.finditer(r'(?:\(\((\w+) \*\)[^()]*\)|(\w+)(\[[^\]]*\])?)(?:->|\.)field_([0-9a-f]+)\b', ln):
                    cast, var, idx, off = m.group(1), m.group(2), m.group(3), m.group(4)
                    if (var == 'this' and idx) or (idx and 'this[' in idx):
                        continue        # this[N].field_0: an unrecovered layout
                    t = cast or types.get(var) or gtypes.get(var)
                    if not t:
                        continue
                    owner = t if t in structs else (type_names.family_of(t) or t)
                    if len(uses[(owner, off)]) < 6:
                        uses[(owner, off)].append('%s: %s' % (fname, ln.strip()[:150]))
                    elif len(uses[(owner, off)]) == 6:
                        uses[(owner, off)].append('...')
    return uses


def main():
    out = sys.argv[1]
    per = int(sys.argv[sys.argv.index('--per') + 1]) if '--per' in sys.argv else 80
    named = type_names.fields()
    uses = collect()
    todo = [k for k in sorted(uses) if not (k[0].startswith('C_') and (k[0], int(k[1], 16)) in named)]
    os.makedirs(out, exist_ok=True)
    for b in range(0, len(todo), per):
        with open(os.path.join(out, 'fields%02d.md' % (b // per)), 'w') as f:
            for owner, off in todo[b:b + per]:
                f.write('## %s field_%s\n%s\n\n' % (owner, off, '\n'.join('    ' + s for s in uses[(owner, off)])))
    print('%d unnamed fields in use, %d files' % (len(todo), (len(todo) + per - 1) // per))


if __name__ == '__main__':
    main()
