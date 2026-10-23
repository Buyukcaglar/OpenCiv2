#!/usr/bin/env python3
"""Name the parameters and locals the decompiler left numbered (param_N,
iVarN / uVarN / ..., local_XX) from proposals: rows ADDR<TAB>OLD<TAB>NEW,
one per variable, ADDR the function's address (its /* ADDR ... */ marker).

    name_vars.py slices OUTDIR [--lines N]   the game's functions in slices of
                                             about N lines, for proposing names
    name_vars.py apply ROWS.tsv...           rename, within each function only
    name_vars.py count                       how many numbered names are left

A name is used only if it is a lower_snake_case C identifier that collides
with nothing: C keywords, types, functions and globals (globals are macros),
the function's other names, and, for the frame locals local_XX (macros
too), field names.  On a collision a number is added (city2).  Pure
renaming: the compiled code does not change.
"""
import collections
import glob
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
import name_locals  # noqa: E402  (forbidden_names)

VAR = re.compile(r'^(?:param_\d+|[a-z]{1,5}Var\d+|local_[0-9a-f]+|[a-z]Stack_[0-9a-f]+|[a-z]{1,4}Stack[XY]?_[0-9a-f]+)$')
NAME = re.compile(r'^[a-z_][a-z0-9_]*$')
MARK = re.compile(r'(?m)^(?=/\* [0-9a-f]{8}[ :])')


def game_files():
    return sorted(f for f in glob.glob(os.path.join(ROOT, 'src', 'auto', '*.c')) if not f.endswith('msvcrt.c'))


def regions(text):
    return MARK.split(text)


def numbered(region):
    return sorted(set(re.findall(r'\b(?:param_\d+|[a-z]{1,5}Var\d+|local_[0-9a-f]+|[a-z]{1,4}Stack[XY]?_[0-9a-f]+)\b',
                                 region)))


def count():
    c = collections.Counter()
    for f in game_files():
        for v in re.findall(r'\b(param_\d+|[a-z]{1,5}Var\d+|local_[0-9a-f]+|[a-z]{1,4}Stack[XY]?_[0-9a-f]+)\b',
                            open(f).read()):
            c['param' if v.startswith('param_') else 'local_' if v.startswith('local_') else 'stack'
              if 'Stack' in v else 'xVar'] += 1
    for k, v in sorted(c.items()):
        print('%-6s %7d' % (k, v))
    print('total  %7d' % sum(c.values()))


def slices(out, lines):
    os.makedirs(out, exist_ok=True)
    n, buf, size = 0, [], 0
    for f in game_files():
        for r in regions(open(f).read())[1:]:
            if not numbered(r):
                continue
            buf.append(r)
            size += r.count('\n')
            if size >= lines:
                open(os.path.join(out, 'slice%03d.c' % n), 'w').write(''.join(buf))
                n, buf, size = n + 1, [], 0
    if buf:
        open(os.path.join(out, 'slice%03d.c' % n), 'w').write(''.join(buf))
        n += 1
    print('%d slices in %s' % (n, out))


def apply(paths):
    props = collections.defaultdict(dict)
    for p in paths:
        for line in open(p):
            f = line.rstrip('\n').split('\t')
            if len(f) >= 3 and re.match(r'^[0-9a-f]{8}$', f[0]) and VAR.match(f[1]):
                props[f[0]][f[1]] = f[2].strip()
    words, fields = name_locals.forbidden_names()
    # a frame local is a macro: not the name of a member the function uses
    # (rect->right) nor of a macro of the platform headers
    plat_macros = set()
    for pat in ('src/platform/*.h', 'src/host/*.h', 'src/include/win32*.h'):
        for h in glob.glob(os.path.join(ROOT, pat)):
            plat_macros |= set(re.findall(r'(?m)^\s*#\s*define\s+(\w+)', open(h, errors='replace').read()))
    fields = fields | plat_macros
    done = rejected = 0
    for fpath in game_files():
        text = open(fpath).read()
        parts = regions(text)
        for i in range(1, len(parts)):
            r = parts[i]
            ren = props.get(r[3:11])
            if not ren:
                continue
            taken = set(re.findall(r'(?<![.>\w])[A-Za-z_]\w*\b', r))
            members = set(re.findall(r'(?:\.|->)\s*([A-Za-z_]\w*)', r))
            mapping = {}
            for old in sorted(ren):
                new = ren[old]
                if old not in taken:
                    continue
                if not NAME.match(new) or VAR.match(new):
                    rejected += 1
                    continue
                bad = (fields | members) if old.startswith('local_') or 'Stack' in old else words
                base, k = new, 2
                while new in taken or new in bad or new in mapping.values():
                    new = '%s%d' % (base, k)
                    k += 1
                mapping[old] = new
                taken.add(new)
            if mapping:
                parts[i] = re.sub(r'(?<![.\w])(?<!->)(%s)\b' % '|'.join(map(re.escape, sorted(mapping, key=len, reverse=True))),
                                  lambda m: mapping[m.group(1)], r)
                done += len(mapping)
        n = ''.join(parts)
        if n != text:
            open(fpath, 'w').write(n)
    print('%d variables named, %d proposals rejected' % (done, rejected))


def main():
    a = sys.argv[1:]
    if a and a[0] == 'count':
        count()
    elif a and a[0] == 'slices':
        lines = int(a[a.index('--lines') + 1]) if '--lines' in a else 3000
        slices(a[1], lines)
    elif a and a[0] == 'apply':
        apply(a[1:])
    else:
        print(__doc__)
        return 1
    return 0


if __name__ == '__main__':
    sys.exit(main())
