#!/usr/bin/env python3
"""Take field names (rows OWNER<TAB>field_XX<TAB>name, as tools/field_uses.py
dossiers are answered) into the sources:

  * a class family's (OWNER C_<root>): re/field_names.tsv, applied by
    tools/type_names.py (a union alias in civ2classes.h);
  * a game struct's (GameState, Civ, Unit, City ...): a union alias in
    src/include/civ2types.h (same layout: the old name stays valid);
  * then every use whose object type is known (see tools/field_uses.py)
    takes the name.

Usage: apply_field_names.py NAMES.tsv...
"""
import glob
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
import field_uses  # noqa: E402
import type_names  # noqa: E402


def struct_alias(text, struct, field, name):
    """In civ2types.h: `T field_XX;` of struct -> union { T field_XX; T name; };"""
    m = re.search(r'typedef struct %s \{(.*?)\}\s*%s;' % (struct, struct), text, re.S)
    if not m:
        m = re.search(r'struct \w*\s*\{((?:(?!\btypedef\b).)*?)\}\s*%s;' % struct, text, re.S)
    if not m:
        return text, False
    body = m.group(1)
    fm = re.search(r'(?m)^(\s+)([\w ]+?) %s((?:\[\w+\])?);' % field, body)
    if not fm:
        return text, False
    new = '%sunion { %s %s%s; %s %s%s; };' % (fm.group(1), fm.group(2), field, fm.group(3), fm.group(2), name, fm.group(3))
    body = body[:fm.start()] + new + body[fm.end():]
    return text[:m.start(1)] + body + text[m.end(1):], True


def main():
    rows = []
    for p in sys.argv[1:]:
        for line in open(p):
            f = line.rstrip('\n').split('\t')
            if len(f) >= 3 and re.match(r'^field_[0-9a-f]+$', f[1]) and re.match(r'^[a-z_][a-z0-9_]*$', f[2]):
                rows.append((f[0], f[1], f[2]))
    # every macro name of the sources (globals and frame locals are macros):
    # a field so named would be rewritten after -> and .
    macros = set()
    for d in ('src/auto', 'src/include', 'src/data', 'src/game', 'src/platform', 'src/host', 'tools'):
        for f in glob.glob(os.path.join(ROOT, d, '*.[ch]')):
            macros |= set(re.findall(r'(?m)^\s*#\s*define\s+(\w+)', open(f, errors='replace').read()))
    fixed = []
    for owner, field, name in rows:
        if name in macros:
            new, k = name + '_value', 2
            while new in macros:
                new, k = '%s_value%d' % (name, k), k + 1
            name = new
        fixed.append((owner, field, name))
    rows = fixed
    structs = field_uses.struct_types()
    fn_path = os.path.join(ROOT, 're', 'field_names.tsv')
    known = type_names.fields()
    added = []
    types_h = os.path.join(ROOT, 'src', 'include', 'civ2types.h')
    th = open(types_h).read()
    struct_names = {}
    for owner, field, name in rows:
        off = int(field[6:], 16)
        if owner.startswith('C_'):
            taken = {v for (fam, _), v in known.items() if fam == owner}
            if (owner, off) in known or name in taken:
                continue
            added.append('%s\t0x%x\t%s\tmedium\tnamed from its uses (tools/field_uses.py)\n' % (owner, off, name))
            known[(owner, off)] = name
        elif owner in structs:
            th, ok = struct_alias(th, owner, field, name)
            if ok:
                struct_names[(owner, field)] = name
    open(fn_path, 'a').write(''.join(added))
    open(types_h, 'w').write(th)
    type_names._FIELDS = None
    # headers (class unions) and uses through this/casts/locals
    os.system('cd %s && python3 tools/rename.py >/dev/null' % ROOT)
    # uses of struct fields and the remaining class fields, by object type
    names = {(o, f): n for (o, f), n in struct_names.items()}
    # the game structs' existing aliases: union { T field_XX; T name; }
    for m in re.finditer(r'typedef struct (\w+) \{(.*?)\}\s*\1;', th, re.S):
        for a in re.finditer(r'union \{ [\w ]+? (field_[0-9a-f]+)(?:\[\w+\])?; [\w ]+? (\w+)(?:\[\w+\])?; \}', m.group(2)):
            names.setdefault((m.group(1), a.group(1)), a.group(2))
    for (fam, off), n in type_names.fields().items():
        names[(fam, 'field_%x' % off)] = n
        names[(fam, 'field_%02x' % off)] = n
    gtypes = field_uses.global_types()
    count = 0
    for path in glob.glob(os.path.join(ROOT, 'src', 'auto', '*.c')):
        text = open(path).read()
        parts = re.split(r'(?m)^(?=/\* [0-9a-f]{8}[ :])', text)
        for i in range(1, len(parts)):
            body = parts[i]
            types = field_uses.local_types(body)

            def rep(m):
                nonlocal count
                cast, var, idx, op, field = m.group(1), m.group(2), m.group(3), m.group(4), m.group(5)
                if (var == 'this' and idx) or (idx and 'this[' in idx):
                    return m.group(0)
                t = cast or types.get(var) or gtypes.get(var)
                if not t:
                    return m.group(0)
                owner = t if t in structs else (type_names.family_of(t) or t)
                n = names.get((owner, field))
                if not n:
                    return m.group(0)
                count += 1
                return m.group(0)[:-len(field)] + n
            parts[i] = re.sub(r'(?:\(\((\w+) \*\)[^()]*\)|(\w+)(\[[^\]]*\])?)(->|\.)(field_[0-9a-f]+)\b', rep, body)
        n = ''.join(parts)
        if n != text:
            open(path, 'w').write(n)
    print('%d class fields named, %d struct fields named, %d uses rewritten' % (len(added), len(struct_names), count))


if __name__ == '__main__':
    main()
