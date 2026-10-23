#!/usr/bin/env python3
"""Give functions and globals their names everywhere at once.

re/symbols.tsv is the list of names (kind `func`: a function; kind `var`: a
global that keeps the type Ghidra gave each access, named only; Ghidra's
ApplyTypes.java reads the same file).  This propagates them into what was
derived from Ghidra's export and into the sources, without re-running
Ghidra: every whole identifier FUN_xxxxxxxx (or a function's earlier name)
becomes the new name, thunk_FUN_xxxxxxxx becomes thunk_<name>; a global's
identifier (DAT_xxxxxxxx, iptr_xxxxxxxx ..., or its earlier name) likewise.

Checks first: names are C identifiers in lower snake case, unique, and
clash with nothing already in the sources or the platform headers (Win32,
C library).  Usage: tools/rename.py [--dry-run]
"""
import argparse
import csv
import glob
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
NAME = re.compile(r'^[a-z][a-z0-9_]*[a-z0-9]$')
C_KEYWORDS = set('''auto break case char const continue default do double else enum extern float for goto if
inline int long register restrict return short signed sizeof static struct switch typedef union unsigned void
volatile while bool true false main'''.split())


def files():
    out = []
    for pat in ('re/*.tsv', 're/decomp.c', 're/proposals/*', 'tools/*.py', 'hook/*.c', 'hook/*.h',
                'harness/scripts/*.txt', 'harness/diffscripts/*.txt'):     # call FUNCTION
        out += glob.glob(os.path.join(ROOT, pat))
    for d, _, fs in os.walk(os.path.join(ROOT, 'src')):
        out += [os.path.join(d, f) for f in fs if f.endswith(('.c', '.h', '.inc'))]
    return [f for f in out if not f.endswith(('rename.py', 'symbols.tsv', 'function_names.tsv', 'global_names.tsv'))]


def reserved():
    """Identifiers of the platform layer's headers (Win32) and of the C,
    POSIX and SDL headers (tools/reserved_names.txt, made with gcc -E)."""
    ids = set(C_KEYWORDS)
    ids |= set(open(os.path.join(ROOT, 'tools', 'reserved_names.txt')).read().split())
    for pat in ('src/platform/*.h', 'src/host/*.h', 'src/include/win32*.h'):
        for f in glob.glob(os.path.join(ROOT, pat)):
            ids |= set(re.findall(r'\b[A-Za-z_]\w*\b', open(f, errors='replace').read()))
    return ids


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--dry-run', action='store_true')
    a = ap.parse_args()
    current = {}            # address -> current name
    thunks = {}             # target address -> [thunk addresses]
    with open(os.path.join(ROOT, 're', 'functions.tsv')) as f:
        for r in csv.DictReader(f, delimiter='\t'):
            current[r['entry']] = r['name']
            if r['thunk_target'] and not r['thunk_target'].startswith('EXTERNAL'):
                thunks.setdefault(r['thunk_target'], []).append(r['entry'])
    wanted = {}
    wanted_vars = {}
    with open(os.path.join(ROOT, 're', 'symbols.tsv')) as f:
        for r in csv.DictReader(f, delimiter='\t'):
            if r['kind'] == 'func':
                wanted[r['addr']] = r['name']
            elif r['kind'] == 'var':
                wanted_vars[r['addr']] = r['name']
    gnames = {}             # global address -> identifiers Ghidra's export uses for it
    if wanted_vars:
        for line in open(os.path.join(ROOT, 're', 'decomp.c'), errors='replace'):
            if line.startswith('// GLOBAL '):
                n, ga = line[10:].split('\t')[:2]
                gnames.setdefault(ga.rjust(8, '0').lower(), set()).add(n)

    renames = {}            # old identifier -> new
    errors = []
    seen = {}
    for addr, new in wanted.items():
        if addr not in current:
            errors.append('%s: no function at this address' % addr)
            continue
        if new in seen:
            errors.append('%s: %s already names %s' % (addr, new, seen[new]))
        seen[new] = addr
        old = current[addr]
        if old == new:
            continue
        if not NAME.match(new):
            errors.append('%s: %r is not a lower_snake_case identifier' % (addr, new))
        renames[old] = new
        for t in thunks.get(addr, []):
            if current[t] == 'thunk_' + old:
                renames['thunk_' + old] = 'thunk_' + new
    for addr, new in wanted_vars.items():
        olds = set(gnames.get(addr, ()))
        if new in seen:
            errors.append('%s: %s already names %s' % (addr, new, seen[new]))
        seen[new] = addr
        if not NAME.match(new):
            errors.append('%s: %r is not a lower_snake_case identifier' % (addr, new))
        olds.discard(new)
        if len(olds) > 1:
            errors.append('%s: several identifiers for this global: %s' % (addr, ' '.join(sorted(olds))))
        elif not olds and new not in gnames.get(addr, set()):
            errors.append('%s: no global at this address in re/decomp.c' % addr)
        elif olds:
            renames[olds.pop()] = new
    if not renames and not errors:
        print('nothing to rename')
        return apply_types(a.dry_run)

    paths = files()
    texts = {p: open(p, errors='surrogateescape').read() for p in paths}
    res = reserved()
    every = set()
    for t in texts.values():
        every |= set(re.findall(r'\b[A-Za-z_]\w*\b', t))
    for old, new in renames.items():
        if new in res:
            errors.append('%s -> %s: clashes with a platform/C identifier' % (old, new))
        elif new in every:
            errors.append('%s -> %s: the name is already used in the sources' % (old, new))
    if errors:
        print('\n'.join(errors), file=sys.stderr)
        return 1

    # Whole identifiers only; longest first so thunk_X is not split.
    pat = re.compile(r'(?<![A-Za-z0-9_])(%s)(?![A-Za-z0-9_])' %
                     '|'.join(re.escape(o) for o in sorted(renames, key=len, reverse=True)))
    changed = 0
    for p, t in texts.items():
        n = pat.sub(lambda m: renames[m.group(1)], t)
        if n != t:
            changed += 1
            if not a.dry_run:
                open(p, 'w', errors='surrogateescape').write(n)
    print('%d names, %d files %s' % (len(renames), changed, 'would change' if a.dry_run else 'changed'))
    return apply_types(a.dry_run)


def apply_access_macros(dry_run):
    """Ghidra's other spelling of a named global, _DAT_ADDR (a per-function
    macro reading it with one access type, as `(*(i32 *)&g.d_ADDR)`), gets
    the global's name with that type.
    The name of the global itself is a macro (src/auto/globals.h), so the
    per-function macro always takes the access type: advisor_list_top_i32."""
    names = {}
    for line in open(os.path.join(ROOT, 're', 'symbols.tsv')):
        f = line.rstrip('\n').split('\t')
        if len(f) > 2 and f[1] == 'var':
            names[f[0]] = f[2]
    changed = 0
    for d in ('auto', 'game', 'unused'):
        for p in glob.glob(os.path.join(ROOT, 'src', d, '*.c')):
            t = open(p, errors='surrogateescape').read()
            out = []
            for reg in re.split(r'(?m)^(?=/\* [0-9a-f]{8}[ :])', t):
                for a in sorted(set(re.findall(r'\b_DAT_([0-9a-f]{8})\b', reg))):
                    n = names.get(a)
                    if not n:
                        continue
                    m = re.search(r'#define _DAT_%s \(\*\((\w+)' % a, reg)
                    new = '%s_%s' % (n, m.group(1) if m else 'access')
                    if True:
                        k = 2
                        while re.search(r'\b%s\b' % re.escape(new), reg):
                            new = '%s_%s%d' % (n, m.group(1) if m else 'access', k)
                            k += 1
                    reg = re.sub(r'\b_DAT_%s\b' % a, new, reg)
                out.append(reg)
            n = ''.join(out)
            if n != t:
                changed += 1
                if not dry_run:
                    open(p, 'w', errors='surrogateescape').write(n)
    if changed:
        print('_DAT_ accesses of named globals: %d files %s' % (changed, 'would change' if dry_run else 'changed'))


def apply_types(dry_run):
    """Class names (re/type_names.tsv) in the C sources; the analysis
    tables and Ghidra's export keep the C_ names (see tools/type_names.py)."""
    apply_access_macros(dry_run)
    sys.path.insert(0, os.path.join(ROOT, 'tools'))
    import type_names
    if not type_names.mapping() and not type_names.fields():
        return 0
    changed = 0
    for d, _, fs in os.walk(os.path.join(ROOT, 'src')):
        for f in fs:
            if not f.endswith(('.c', '.h', '.inc')):
                continue
            p = os.path.join(d, f)
            t = open(p, errors='surrogateescape').read()
            n = type_names.apply(t)
            if f == 'civ2classes.h':
                n = type_names.apply_header(n)
            if n != t:
                changed += 1
                if not dry_run:
                    open(p, 'w', errors='surrogateescape').write(n)
    if changed:
        print('class names: %d files %s' % (changed, 'would change' if dry_run else 'changed'))
    return 0


if __name__ == '__main__':
    sys.exit(main())
