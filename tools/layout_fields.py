#!/usr/bin/env python3
"""Fields where the game code still reaches into a class by offset:

    this->pad_48 + 0x10        (a gap of a partly known class)
    this[0x567].field_0        (the object read as an array of cells: the
                                cell at 0x567 * cell size)
    this[i * 7 + 0x86].field_0 (an array of cells)
    this[3].pad_1e4 + 0x18     (a gap, past the object's declared end)

    layout_fields.py place          declare a field at each such offset in
                                    src/include/civ2classes.h (splitting the
                                    u8 pad_ arrays: the layout and every
                                    class's size stay the same) and rewrite
                                    the accesses to it; the new fields are
                                    called at_<offset> until named
    layout_fields.py dossier OUT    the at_ fields' uses per class family
    layout_fields.py apply ROWS...  rows FAMILY<TAB>at_X<TAB>name: rename
    layout_fields.py check          compile offsetof asserts: every member
                                    named by its offset (field_, pad_, at_,
                                    gap_) is at that offset

A pad_ access becomes a u8 array starting at its offset (this->pad_48 +
0x10 is then this->at_58: the same u8 *); a cell becomes a field of the
cell's own type in the smallest class of the object's family that holds
it (((CityWindowView *)this)->at_159c: the same address and type).  Past
the end of a family's largest class the field is appended to it, or, when
the class is used as an array element or stepped through (p + n), it goes
in an extension struct ClassExt { Class base; ... } so the class keeps its
size.  An index that is an expression goes through a pointer
(((u32 *)&v->at_3f0)[i]): GCC takes an array index to stay inside its
declared array, and these may not.  Pure renaming of addresses: every
field sits at its offset (each placement is checked with offsetof), and
the compiled code is the same but for register choice and addressing
modes in a few functions.
"""
import collections
import glob
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
import field_uses  # noqa: E402
import type_names  # noqa: E402

HEADER = os.path.join(ROOT, 'src', 'include', 'civ2classes.h')
SIZES = {'u8': 1, 'i8': 1, 'u16': 2, 'i16': 2, 'u32': 4, 'i32': 4, 'uptr': 4, 'iptr': 4}
MEMBER = re.compile(r'^(\s+)(?:union \{ (\w+) (\w+)((?:\[\w+\])?); \w+ (\w+)(?:\[\w+\])?; \}|(\w+) (\w+)((?:\[\w+\])?));\s*(/\*.*)?$')


def game_files():
    return sorted(f for f in glob.glob(os.path.join(ROOT, 'src', 'auto', '*.c')) if not f.endswith('msvcrt.c'))


def parse(text):
    """struct -> {'start': line, 'end': line, 'members': [dict]} (offsets from names)."""
    lines = text.split('\n')
    out, cur = {}, None
    for i, ln in enumerate(lines):
        m = re.match(r'^typedef struct (\w+) \{', ln)
        if m:
            cur = {'start': i, 'members': [], 'name': m.group(1)}
            continue
        if cur is None:
            continue
        if re.match(r'^\} (\w+);', ln):
            cur['end'] = i
            out[cur['name']] = cur
            cur = None
            continue
        mm = MEMBER.match(ln)
        if not mm:
            cur['bad'] = True
            continue
        if mm.group(2):
            t, n, dims, alias = mm.group(2), mm.group(3), mm.group(4), mm.group(5)
        else:
            t, n, dims, alias = mm.group(6), mm.group(7), mm.group(8), None
        om = re.match(r'^(?:field|pad|at)_([0-9a-f]+)$', n)
        if not om or t not in SIZES:
            cur['bad'] = True
            continue
        count = int(dims[1:-1], 0) if dims else 1
        cur['members'].append({'line': i, 'off': int(om.group(1), 16), 'type': t, 'name': n, 'alias': alias,
                               'count': count, 'size': SIZES[t] * count, 'dims': dims})
    for s in out.values():
        s['size'] = max((m['off'] + m['size'] for m in s['members']), default=0)
    return out


def member_at(s, off):
    for m in s['members']:
        if m['off'] <= off < m['off'] + m['size']:
            return m
    return None


def label(m):
    return m['alias'] or m['name']


def collect(structs):
    """Accesses: list of (path, region index, match span, kind, ...)."""
    fams = collections.defaultdict(list)
    for n in structs:
        fams[type_names.family_of(n) or n].append(n)
    return fams


def indexed_classes(structs):
    """Classes some function indexes as an array (v[i].x): their size counts."""
    out = set()
    for path in game_files():
        for body in re.split(r'(?m)^(?=/\* [0-9a-f]{8}[ :])', open(path).read())[1:]:
            types = field_uses.local_types(body)
            for v in set(re.findall(r'\b(\w+)\[', body)):
                if types.get(v) in structs:
                    out.add(types[v])
    return out


ACCESS = re.compile(r'(?:\(\((\w+) \*\)([\w.>-]+)\)|\b(\w+))(->|\.)pad_([0-9a-f]+)'
                    r'(?:\s*\+\s*(0x[0-9a-f]+|\d+)(?![\w.*/%\[(]|\s*[*/%]))?')
IDXPAD = re.compile(r'\b(\w+)\[(0x[0-9a-f]+|\d+)\]\.pad_([0-9a-f]+)'
                    r'(?:\s*\+\s*(0x[0-9a-f]+|\d+)(?![\w.*/%\[(]|\s*[*/%])|\[(0x[0-9a-f]+|\d+)\])?')
CELL = re.compile(r'\b(\w+)\[((?:[^\[\]]|\[[^\[\]]*\])+)\]\.field_([0-9a-f]+)\b')


def want(offs, off, req):
    """One member per offset: an array before a scalar before a u8 gap part."""
    rank = lambda r: 2 if r[1] == 'array' else 1 if r[0] != 'u8' else 0
    if off not in offs or rank(req) > rank(offs[off]):
        offs[off] = req


def unary_before(body, pos):
    """A cast or unary operator applies to the access at pos (it binds
    before a following + K)."""
    return body[:pos].rstrip()[-1:] in (')', '*', '&', '-', '!', '~')


def cells(body, pos=0, end=None):
    """CELL matches, those inside another's index too (inner ones after)."""
    for m in CELL.finditer(body, pos, len(body) if end is None else end):
        yield m
        yield from cells(body, m.start(2), m.end(2))


def cell_index(idx, k):
    """v[E + K].field_x as an index of the field's type: E (times k, the
    cells per object)."""
    e = re.match(r'^(.*\S)\s*\+\s*(0x[0-9a-f]+|\d+)$', idx).group(1)
    if k == 1:
        return e
    return '(%s) * %d' % (e, k) if re.search(r'\W', e) else '%s * %d' % (e, k)


def choose(structs, fams, indexed, t, off, ctype, scalar):
    """The class of t's family to hold a ctype at off: (class, new field?)."""
    width = SIZES[ctype]
    fam = sorted(fams[type_names.family_of(t) or t], key=lambda n: structs[n]['size'])
    for cand in fam:                       # a member of that type there
        cs = structs[cand]
        mem = member_at(cs, off) if not cs.get('bad') else None
        if scalar and mem and mem['off'] == off and mem['type'] == ctype and not mem['dims']:
            return cand, False
    for cand in fam:                       # else a gap that holds it
        cs = structs[cand]
        mem = member_at(cs, off) if not cs.get('bad') else None
        if mem and mem['name'].startswith('pad_') and off + width <= mem['off'] + mem['size']:
            return cand, True
    for cand in reversed(fam):             # else past the largest class's end
        cs = structs[cand]
        if not cs.get('bad') and cand not in indexed and off >= cs['size']:
            return cand, True
    big = fam[-1]                          # else an extension of it (Class + Ext:
    if structs[big].get('bad') or off < structs[big]['size']:   # the class
        return None                        # itself keeps its size, as arrays
    ext = big + 'Ext'                      # and pointer steps use it)
    if ext not in structs:
        structs[ext] = {'name': ext, 'members': [], 'size': structs[big]['size'], 'ext': big}
    return ext, True


def fit(s, offs):
    """A requested field that overlaps the next one (or its gap's end) is
    declared as u8 bytes instead; its uses then cast its address."""
    bounds = sorted(m['off'] + m['size'] for m in s['members'] if m['name'].startswith('pad_'))
    order = sorted(offs)
    for k, o in enumerate(order):
        t, kind = offs[o]
        nxt = [x for x in order[k + 1:k + 2]] + [b for b in bounds if b > o and
                                                 any(m['off'] <= o < m['off'] + m['size'] == b for m in s['members'])]
        if t != 'u8' and nxt and o + SIZES[t] > min(nxt):
            offs[o] = ('u8', None)


def place():
    text = open(HEADER).read()
    structs = parse(text)
    fams = collect(structs)
    indexed = indexed_classes(structs)
    adds = collections.defaultdict(dict)      # struct -> off -> (type, kind)
    plans = []
    skipped = collections.Counter()
    for path in game_files():
        parts = re.split(r'(?m)^(?=/\* [0-9a-f]{8}[ :])', open(path).read())
        for i in range(1, len(parts)):
            body = parts[i]
            types = field_uses.local_types(body)
            for m in ACCESS.finditer(body):
                cast, cvar, var, op, p, k = m.groups()
                span = (m.start(), m.end())
                if k and unary_before(body, m.start()):     # (T *)v->pad_P + K: K is not bytes
                    k, span = None, (m.start(), m.end(5))
                t = cast or types.get(var)
                if t not in structs or structs[t].get('bad'):
                    skipped['pad: type'] += 1
                    continue
                off = int(p, 16) + (int(k, 0) if k else 0)
                mem = member_at(structs[t], off)
                if not mem or not mem['name'].startswith('pad_') or mem['off'] != int(p, 16):
                    skipped['pad: not in its gap'] += 1
                    continue
                want(adds[t], off, ('u8', None))
                plans.append((path, i, span, ('pad', t, off, cast, cvar or var, op, None)))
            for m in IDXPAD.finditer(body):
                var, n, p, k, ix = m.groups()
                span = (m.start(), m.end())
                if k and unary_before(body, m.start()):
                    k, span = None, (m.start(), m.end(3))
                t = types.get(var)
                if t not in structs or structs[t].get('bad'):
                    skipped['idxpad: type'] += 1
                    continue
                s = structs[t]
                mem = member_at(s, int(p, 16))
                if not mem or not mem['name'].startswith('pad_') or mem['off'] != int(p, 16):
                    skipped['idxpad: not a gap'] += 1
                    continue
                off = int(n, 0) * s['size'] + int(p, 16) + int(k or '0', 0) + int(ix or '0', 0)
                best = choose(structs, fams, indexed, t, off, 'u8', True)
                if not best:
                    skipped['idxpad: no class'] += 1
                    if os.environ.get('LAYOUT_DEBUG'):
                        print('no class: %s u8 %#x %s' % (t, off, m.group(0)))
                    continue
                cand, new = best
                if new:
                    want(adds[cand], off, ('u8', None))
                plans.append((path, i, span, ('idxpad', cand, off, 'u8', var, '->', ix)))
            for m in cells(body):
                var, idx, x = m.group(1), m.group(2).strip(), int(m.group(3), 16)
                t = types.get(var)
                if t not in structs or structs[t].get('bad'):
                    skipped['cell: type'] += 1
                    continue
                s = structs[t]
                cm = member_at(s, x)
                if not cm or cm['off'] != x or cm['dims']:
                    skipped['cell: field'] += 1
                    continue
                const = re.match(r'^(0x[0-9a-f]+|\d+)$', idx)
                em = re.match(r'^(.*\S)\s*\+\s*(0x[0-9a-f]+|\d+)$', idx)
                if const:
                    off, expr = int(idx, 0) * s['size'] + x, None
                elif em and s['size'] % SIZES[cm['type']] == 0:
                    off, expr = int(em.group(2), 0) * s['size'] + x, cell_index(idx, s['size'] // SIZES[cm['type']])
                else:
                    skipped['cell: index'] += 1
                    continue
                best = choose(structs, fams, indexed, t, off, cm['type'], expr is None)
                if not best:
                    skipped['cell: no class'] += 1
                    if os.environ.get('LAYOUT_DEBUG'):
                        print('no class: %s %s %#x %s' % (t, cm['type'], off, m.group(0)))
                    continue
                cand, new = best
                if new:
                    want(adds[cand], off, (cm['type'], 'array' if expr else None))
                plans.append((path, i, (m.start(), m.end()),
                              ('cell', cand, off, cm['type'], var, s['size'] // SIZES[cm['type']], expr)))
    lines = text.split('\n')
    for st, offs in adds.items():
        s = structs[st]
        fit(s, offs)
        gaps = sorted([m for m in s['members'] if m['name'].startswith('pad_')], key=lambda m: -m['line'])
        for mem in gaps:
            cuts = sorted(o for o in offs if mem['off'] <= o < mem['off'] + mem['size'])
            if not cuts:
                continue
            end = mem['off'] + mem['size']
            inner, pos = [], mem['off']
            for k, o in enumerate(cuts):
                t, kind = offs[o]
                if o > pos:
                    inner.append('u8 gap_%x[%d];' % (pos, o - pos))
                nxt = cuts[k + 1] if k + 1 < len(cuts) else end
                if t == 'u8':
                    inner.append('u8 at_%x[%d];' % (o, nxt - o))
                    pos = nxt
                elif kind == 'array':
                    n = (nxt - o) // SIZES[t]
                    inner.append('%s at_%x[%d];' % (t, o, n))
                    pos = o + n * SIZES[t]
                else:
                    inner.append('%s at_%x;' % (t, o))
                    pos = o + SIZES[t]
            if pos < end:
                inner.append('u8 gap_%x[%d];' % (pos, end - pos))
            indent = re.match(r'^(\s*)', lines[mem['line']]).group(1)
            lines[mem['line']] = '%sunion { u8 %s[%d]; struct { %s }; };' % (indent, mem['name'], mem['size'], ' '.join(inner))
        appended = sorted(o for o in offs if o >= s['size'])
        if appended and s.get('ext'):
            base = structs[s['ext']]
            new, pos = ['', '/* %s where the code reaches past its end: the object is larger */' % s['ext'],
                        'typedef struct %s {' % st, '    %s base;' % s['ext']], s['size']
            for k, o in enumerate(appended):
                t, kind = offs[o]
                if o > pos:
                    new.append('    u8 pad_%x[%d];' % (pos, o - pos))
                nxt = appended[k + 1] if k + 1 < len(appended) else None
                if t == 'u8' or kind == 'array':
                    n = ((nxt - o) // SIZES[t]) if nxt else 1
                    new.append('    %s at_%x[%d];' % (t, o, n))
                    pos = o + n * SIZES[t]
                else:
                    new.append('    %s at_%x;' % (t, o))
                    pos = o + SIZES[t]
            new.append('} %s;' % st)
            lines[base['end']] += '\n' + '\n'.join(new)
        elif appended:
            last = max(s['members'], key=lambda m: m['line'])
            indent = re.match(r'^(\s*)', lines[last['line']]).group(1)
            new, pos = [], s['size']
            for k, o in enumerate(appended):
                t, kind = offs[o]
                if o > pos:
                    new.append('%su8 pad_%x[%d];' % (indent, pos, o - pos))
                nxt = appended[k + 1] if k + 1 < len(appended) else None
                if t == 'u8' or kind == 'array':
                    n = ((nxt - o) // SIZES[t]) if nxt else 1
                    new.append('%s%s at_%x[%d];' % (indent, t, o, n))
                    pos = o + n * SIZES[t]
                else:
                    new.append('%s%s at_%x;' % (indent, t, o))
                    pos = o + SIZES[t]
            lines[last['line']] += '\n' + '\n'.join(new)
    newtext = '\n'.join(lines)
    after = parse_sizes(newtext)
    for n, s in structs.items():
        grown = any(o >= s['size'] for o in adds.get(n, {}))
        if after.get(n) != s['size'] and not grown:
            sys.exit('layout changed: %s %d -> %s' % (n, s['size'], after.get(n)))
    open(HEADER, 'w').write(newtext)
    by_region = collections.defaultdict(list)
    for path, i, old, info in plans:
        by_region[(path, i)].append((old, info))
    done = 0
    newstructs = parse_layout(newtext)
    for path in game_files():
        parts = re.split(r'(?m)^(?=/\* [0-9a-f]{8}[ :])', open(path).read())
        changed = False
        for i in range(1, len(parts)):
            reps = by_region.get((path, i))
            if not reps:
                continue
            body = parts[i]
            types = field_uses.local_types(body)
            applied = []            # (start, end, growth) of the edits made
            for (a, b), (kind, cls, off, cast, var, op, expr) in sorted(reps, key=lambda r: -r[0][0]):
                inner = [d for (x, y, d) in applied if a <= x and y <= b]
                if inner:               # an access inside this one's index
                    b += sum(inner)
                    cm = CELL.match(body, a)
                    assert cm and cm.end() == b, body[a:b]
                    expr = cell_index(cm.group(2).strip(), op)
                nm = newstructs[cls].get(off)
                if not nm:
                    if os.environ.get('LAYOUT_DEBUG'):
                        print('no name: %s %s %#x %s' % (kind, cls, off, body[a:b]))
                    continue
                final = adds.get(cls, {}).get(off)       # (type, kind) when declared here
                if kind == 'idxpad':
                    base = var if types.get(var) == cls else '((%s *)%s)' % (cls, var)
                    u8arr = final and final[0] == 'u8' and final[1] is None
                    if expr is not None:
                        new = '%s->%s[0]' % (base, nm) if u8arr else '((u8 *)&%s->%s)[0]' % (base, nm)
                    else:
                        new = '%s->%s' % (base, nm) if u8arr else '(u8 *)&%s->%s' % (base, nm)
                elif kind == 'pad':
                    base = '((%s *)%s)' % (cast, var) if cast else var
                    if final and final[0] == 'u8' and final[1] is None:
                        new = '%s%s%s' % (base, op, nm)
                    else:
                        new = '(u8 *)&%s%s%s' % (base, op, nm)
                else:
                    base = var if types.get(var) == cls else '((%s *)%s)' % (cls, var)
                    ctype = cast            # the cell's type
                    if expr is not None:
                        # through a pointer: the index may run past the
                        # array's declared end (GCC assumes an array index
                        # stays inside its array)
                        new = '((%s *)&%s->%s)[%s]' % (ctype, base, nm, expr)
                    elif final is None or (final[0] == ctype and final[1] is None):
                        new = '%s->%s' % (base, nm)
                    elif final[0] == ctype and final[1] == 'array':
                        new = '%s->%s[0]' % (base, nm)
                    else:
                        new = '(*(%s *)&%s->%s)' % (ctype, base, nm)
                if nm.startswith(('gap_', 'pad_')):
                    print('no field for %s %s at %#x in %s' % (kind, cls, off, body[a:b]))
                    continue
                body = body[:a] + new + body[b:]
                applied.append((a, b, len(new) - (b - a)))
                done += 1
                changed = True
            parts[i] = body
        if changed:
            open(path, 'w').write(''.join(parts))
    print('%d accesses rewritten, %d fields declared in %d classes; skipped: %s' %
          (done, sum(len(v) for v in adds.values()), len(adds), dict(skipped)))


def parse_layout(text):
    """struct -> {offset: name} of every member, the overlaid ones included."""
    out, cur = {}, None
    for ln in text.split('\n'):
        m = re.match(r'^typedef struct (\w+) \{', ln)
        if m:
            cur = out.setdefault(m.group(1), {})
            continue
        if re.match(r'^\} \w+;', ln):
            cur = None
            continue
        if cur is None:
            continue
        for fm in re.finditer(r'\b(?:field|pad|at|gap)_([0-9a-f]+)\b(?:\[\w+\])?;(?= (\w+) (?!(?:field|pad|at|gap)_[0-9a-f]+\b)(\w+)(?:\[\w+\])?; \})?', ln):
            off = int(fm.group(1), 16)
            name = fm.group(3) or re.match(r'(\w+)', fm.group(0)).group(1)   # union { T field_X; T alias; }
            if fm.group(0).startswith(('at_', 'field_')) or off not in cur:
                cur[off] = name
    return out


def parse_sizes(text):
    """struct -> size, the overlays (union of a pad and its parts) counted once."""
    flat = re.sub(r'union \{ u8 (pad_\w+)\[(\d+)\]; struct \{[^}]*\}; \};', r'u8 \1[\2];', text)
    return {n: s['size'] for n, s in parse(flat).items()}


def family(cls):
    base = cls[:-3] if cls.endswith('Ext') else cls
    return type_names.family_of(base) or base


def class_bodies(text):
    """struct -> its definition's text."""
    return {m.group(1): m.group(2) for m in re.finditer(r'(?ms)^typedef struct (\w+) \{(.*?)^\} \1;', text)}


ATUSE = re.compile(r'(?:\(\((\w+) \*\)(\w+)\)|\b(\w+))(?:->|\.)(at_[0-9a-f]+)\b')


def dossier(out):
    bodies = class_bodies(open(HEADER).read())
    decl = {}
    for cls, body in bodies.items():
        for m in re.finditer(r'\b(\w+) (at_[0-9a-f]+)(\[\d+\])?;', body):
            decl.setdefault((family(cls), m.group(2)), '%s%s' % (m.group(1), m.group(3) or ''))
    uses = collections.defaultdict(list)
    for path in game_files():
        for body in re.split(r'(?m)^(?=/\* [0-9a-f]{8}[ :])', open(path).read())[1:]:
            fn = re.search(r'(?m)^[A-Za-z][^#;\n]*?\b(\w+)\([^;{}]*\)\s*\n\{', body)
            fn = fn.group(1) if fn else '?'
            types = field_uses.local_types(body)
            for ln in body.split('\n'):
                for m in ATUSE.finditer(ln):
                    cls = m.group(1) or types.get(m.group(3))
                    key = (family(cls), m.group(4)) if cls else None
                    if key and len(uses[key]) < 6:
                        uses[key].append('%s: %s' % (fn, ln.strip()[:160]))
    os.makedirs(out, exist_ok=True)
    keys = sorted(uses)
    per = 70
    for b in range(0, len(keys), per):
        with open(os.path.join(out, 'layout%02d.md' % (b // per)), 'w') as f:
            for fam, at in keys[b:b + per]:
                f.write('## %s %s  (%s)\n%s\n\n' % (fam, at, decl.get((fam, at), '?'),
                                                    '\n'.join('    ' + u for u in uses[(fam, at)])))
    print('%d fields in %d files' % (len(keys), (len(keys) + per - 1) // per))


def apply(paths):
    """Rows FAMILY<TAB>at_X<TAB>name (FAMILY as the dossiers give it): every
    class of the family that declares at_X, and its uses, take the name."""
    rows = []
    for p in paths:
        for line in open(p):
            f = line.rstrip('\n').split('\t')
            if len(f) >= 3 and re.match(r'^at_[0-9a-f]+$', f[1]) and re.match(r'^[a-z_][a-z0-9_]*$', f[2]):
                rows.append(tuple(f[:3]))
    macros = set()
    for d in ('src/auto', 'src/include', 'src/data', 'src/game', 'src/platform', 'src/host', 'tools'):
        for f in glob.glob(os.path.join(ROOT, d, '*.[ch]')):
            macros |= set(re.findall(r'(?m)^\s*#\s*define\s+(\w+)', open(f, errors='replace').read()))
    text = open(HEADER).read()
    bodies = class_bodies(text)
    fam_classes = collections.defaultdict(list)
    for cls in bodies:
        fam_classes[family(cls)].append(cls)
    taken = collections.defaultdict(set)      # family -> every member name of its classes
    for cls, body in bodies.items():
        taken[family(cls)] |= set(re.findall(r'\b(\w+)(?:\[\w+\])?;', body))
    names = {}
    for fam, at, name in rows:
        if not any(re.search(r'\b%s\b' % at, bodies[c]) for c in fam_classes.get(fam, [])):
            continue
        n, k = name, 2
        while n in macros or n in taken[fam]:
            n = '%s_%d' % (name, k)
            k += 1
        taken[fam].add(n)
        names[(fam, at)] = n
    for cls, body in bodies.items():
        nb = re.sub(r'\b(at_[0-9a-f]+)\b', lambda m: names.get((family(cls), m.group(1)), m.group(1)), body)
        text = text.replace('typedef struct %s {%s} %s;' % (cls, body, cls), 'typedef struct %s {%s} %s;' % (cls, nb, cls))
    open(HEADER, 'w').write(text)
    count = 0
    for path in game_files():
        src = open(path).read()
        parts = re.split(r'(?m)^(?=/\* [0-9a-f]{8}[ :])', src)
        for i in range(1, len(parts)):
            types = field_uses.local_types(parts[i])

            def rep(m):
                nonlocal count
                cls = m.group(1) or types.get(m.group(3))
                n = names.get((family(cls), m.group(4))) if cls else None
                if not n:
                    return m.group(0)
                count += 1
                return m.group(0)[:-len(m.group(4))] + n
            parts[i] = ATUSE.sub(rep, parts[i])
        n = ''.join(parts)
        if n != src:
            open(path, 'w').write(n)
    print('%d fields named, %d uses' % (len(names), count))


def check():
    text = open(HEADER).read()
    out = ['typedef unsigned char u8; typedef signed char i8; typedef unsigned short u16; typedef short i16;',
           'typedef unsigned int u32; typedef int i32; typedef unsigned int uptr; typedef int iptr;',
           '#include "civ2classes.h"']
    for cls, body in class_bodies(text).items():
        for name, off in sorted(set(re.findall(r'\b((?:field|pad|at|gap)_([0-9a-f]+))\b', body))):
            out.append('_Static_assert(__builtin_offsetof(%s, %s) == 0x%s, "%s.%s");' % (cls, name, off, cls, name))
    src = os.path.join(ROOT, 'build', 'layout_check.c')
    os.makedirs(os.path.dirname(src), exist_ok=True)
    open(src, 'w').write('\n'.join(out) + '\n')
    cc = os.environ.get('CC', 'gcc')
    rc = os.system('%s -m32 -fsyntax-only -I %s %s' % (cc, os.path.dirname(HEADER), src))
    print('%d offsets %s' % (len(out) - 3, 'checked' if rc == 0 else 'WRONG'))
    return 1 if rc else 0


if __name__ == '__main__':
    a = sys.argv[1:]
    if a[:1] == ['place']:
        place()
    elif a[:1] == ['dossier']:
        dossier(a[1])
    elif a[:1] == ['apply']:
        apply(a[1:])
    elif a[:1] == ['check']:
        sys.exit(check())
    else:
        print(__doc__)
