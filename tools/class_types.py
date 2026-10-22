#!/usr/bin/env python3
"""Recover C++ classes as C structs from the __thiscall methods.

Model (no inheritance in C, so classes are flat structs at original offsets):
  * edge A -> B when method A calls method B with its own `this`: A's class
    is B's class or derived from it.  Strongly connected groups of methods
    are one class; the remaining edges form the class hierarchy.
  * a class's fields are the `this + K` accesses of its methods and of all
    its ancestors (a derived object contains its bases at the same offsets),
    so a pointer to a derived class can be passed to base-class methods.
  * `this + K` passed as `this` to a method of class C: an embedded C at K.
  * `operator new(N)` immediately followed by a constructor call: size N.
Writes src/include/civ2classes.h (struct per class, packed, explicit
padding) and re/classes.tsv (class name, methods) for ApplyClasses.java.
"""
import collections
import csv
import re
import sys
import os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import paths  # noqa: E402  (the game's directory)

sys.setrecursionlimit(10000)
conv = {r['entry']: r for r in csv.DictReader(open('re/conventions.tsv'), delimiter='\t')}
names, thunk_of = {}, {}
for r in csv.DictReader(open('re/functions.tsv'), delimiter='\t'):
    names[r['name']] = r['entry']
    if r['thunk_target'] and not r['thunk_target'].startswith('EXT'):
        thunk_of[r['entry']] = r['thunk_target']
methods = {a for a, r in conv.items() if r['cc'] == '__thiscall' and int(a, 16) < 0x5f1b80}

text = open('re/decomp.c').read()
parts = re.split(r'^// ==== FUNCTION ([0-9a-f]{8}) (\S+)\n', text, flags=re.M)
bodies = {parts[i]: parts[i + 2] for i in range(1, len(parts), 3)}

CALL = re.compile(r'\b([A-Za-z_][\w:]*)\(')
SIZES = {'char': 1, 'byte': 1, 'undefined1': 1, 'bool': 1, 'uchar': 1, 'i8': 1, 'u8': 1,
         'short': 2, 'ushort': 2, 'undefined2': 2, 'i16': 2, 'u16': 2, 'word': 2}
TYPES = {1: 'u8', 2: 'u16', 4: 'u32'}


def first_arg(body, pos):
    """Text of the first argument of the call whose '(' is at pos."""
    depth, i = 0, pos
    while i < len(body):
        c = body[i]
        if c in '([':
            depth += 1
        elif c in ')]':
            depth -= 1
            if depth == 0:
                return body[pos + 1:i].strip()
        elif c == ',' and depth == 1:
            return body[pos + 1:i].strip()
        i += 1
    return ''


# Fields known from the previous run (the decompiler prints this->field_K once
# classes are applied), carried over per method.
# Once classes are applied the decompiler prints this->field_K; field sizes
# come from the struct definitions exported from the Ghidra project
# (re/class_fields.tsv, by ExportClassStructs.java).
field_size = {}
try:
    for r in csv.DictReader(open('re/class_fields.tsv'), delimiter='\t'):
        field_size[(r['class'], int(r['offset']))] = int(r['size'])
except FileNotFoundError:
    pass
method_class = {}
try:
    for r in csv.DictReader(open('re/class_methods.tsv'), delimiter='\t'):
        method_class[r['method']] = r['class']
except FileNotFoundError:
    pass

ptr_fields = {}                            # (method, offset) -> holds a pointer
edges = collections.defaultdict(set)
receivers = collections.defaultdict(set)   # object -> methods called on it
member_at = collections.defaultdict(set)   # method -> {(K, callee)}
fields = collections.defaultdict(collections.Counter)
new_size = {}
for f, body in bodies.items():
    for m in CALL.finditer(body):
        callee = names.get(m.group(1).split('::')[-1])
        if not callee:
            continue
        callee = thunk_of.get(callee, callee)
        if callee not in methods:
            continue
        arg = re.sub(r'^\((?:void|\w+) \*\)\s*', '', first_arg(body, m.end() - 1))
        if f in methods and arg == 'this':
            edges[f].add(callee)
        # Same object (a global, or a stack object of this function) receiving
        # several methods: they belong to one class (hierarchy).
        # Only unambiguous objects: a global, or the address of a stack object.
        rg = re.match(r'^&?_?DAT_([0-9a-f]{8})$', arg)
        rl = re.match(r'^&(local_[0-9a-f]+|a\w*Stack_[0-9a-f]+)$', arg)
        if rg:
            receivers[rg.group(1)].add(callee)
        elif rl:
            receivers[f + ':' + rl.group(1)].add(callee)
        mk = re.match(r'^\(\(?int\)this \+ (0x[0-9a-f]+|\d+)\)?$', arg) or re.match(r'^\(int\)this \+ (0x[0-9a-f]+|\d+)$', arg)
        if f in methods and mk:
            member_at[f].add((int(mk.group(1), 0), callee))
    # operator new(N) followed by a constructor call on the result
    for nm in re.finditer(r'(\w+) = (?:\(\w+ \*\))?operator_new\((0x[0-9a-f]+|\d+)\);(.{0,300})', body, re.S):
        var, size, after = nm.group(1), int(nm.group(2), 0), nm.group(3)
        cm = re.search(r'\b([A-Za-z_]\w*)\((?:\(\w+ \*\))?%s\b' % re.escape(var), after)
        if cm and names.get(cm.group(1)):
            ctor = thunk_of.get(names[cm.group(1)], names[cm.group(1)])
            if ctor in methods:
                new_size[ctor] = max(new_size.get(ctor, 0), size)
    if f in methods:
        for fm in re.finditer(r'\*\((\w+) \*\)\(\(int\)this \+ (0x[0-9a-f]+|\d+)\)', body):
            fields[f][(int(fm.group(2), 0), SIZES.get(fm.group(1), 4))] += 1
        for fm in re.finditer(r'\*\((\w+) \*\)this\b', body):
            fields[f][(0, SIZES.get(fm.group(1), 4))] += 1
        for fm in re.finditer(r'\(\w+ \*\)this->field_([0-9a-f]+)\b', body):
            ptr_fields[(f, int(fm.group(1), 16))] = True    # value used as a pointer
        for fm in re.finditer(r'\bthis->field_([0-9a-f]+)\b', body):
            k = int(fm.group(1), 16)
            fields[f][(k, field_size.get((method_class.get(f), k), 4))] += 1

# Classes: union-find over "called with the same this" and "applied to the
# same object".  Base and derived classes are merged into one flat struct.
uf = {}


def find(x):
    while uf.setdefault(x, x) != x:
        uf[x] = uf[uf[x]]
        x = uf[x]
    return x


def union(a, b):
    ra, rb = find(a), find(b)
    if ra != rb:
        uf[max(ra, rb)] = min(ra, rb)


for v in methods:
    find(v)
for a, bs in edges.items():
    for b in bs:
        union(a, b)
for obj, ms in receivers.items():
    ms = sorted(ms)
    for m_ in ms[1:]:
        union(ms[0], m_)
comp = {v: find(v) for v in methods}
cls_methods = collections.defaultdict(set)
for m_ in methods:
    cls_methods[comp[m_]].add(m_)
# ---------------------------------------------------------------------------
# Size levels.  A group mixes base and derived classes; an instance of the
# base (often on the stack) is smaller than the derived objects.  Each method
# needs the object to be at least as large as the fields it (and the methods
# it calls with the same `this`) touches; candidate object sizes come from
# operator new and from the free space around stack instances.  Each method
# gets the smallest level that covers its need, and each level is a struct
# containing every field of the group that fits in it.
need = {}
for m_ in methods:
    need[m_] = max([k + sz for (k, sz) in fields.get(m_, {})] + [0])
changed = True
while changed:
    changed = False
    for a, bs in edges.items():
        for b in bs:
            if need.get(b, 0) > need.get(a, 0):
                need[a] = need[b]
                changed = True

import capstone, pefile
img = pefile.PE(paths.game_file('civ2.exe')).get_memory_mapped_image()
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
fsize = {r['entry']: int(r['size']) for r in csv.DictReader(open('re/functions.tsv'), delimiter='\t')}
levels = collections.defaultdict(set)      # group -> candidate sizes
for ctor, size in new_size.items():
    levels[comp[ctor]].add(size)
for f in bodies:
    a = int(f, 16)
    ins = list(md.disasm(img[a - 0x400000:a - 0x400000 + fsize.get(f, 0)], a))
    slots = set()
    for i in ins:
        for mm in re.finditer(r'\[ebp - (0x[0-9a-f]+|\d+)\]', i.op_str):
            slots.add(int(mm.group(1), 0))
    for j, i in enumerate(ins[:-1]):
        mm = re.match(r'ecx, \[ebp - (0x[0-9a-f]+|\d+)\]$', i.op_str)
        if i.mnemonic != 'lea' or not mm:
            continue
        nxt = next((x for x in ins[j + 1:j + 12] if x.mnemonic == 'call'), None)
        if nxt is None or not nxt.op_str.startswith('0x'):
            continue
        callee = thunk_of.get('%08x' % int(nxt.op_str, 16), '%08x' % int(nxt.op_str, 16))
        if callee not in methods:
            continue
        k = int(mm.group(1), 0)
        above = [x for x in slots if x < k]
        levels[comp[callee]].add(k - max(above) if above else k)

group_fields = collections.defaultdict(dict)   # group -> {offset: widest size}
group_ptr = collections.defaultdict(set)       # group -> offsets holding pointers
for m_ in methods:
    g = comp[m_]
    for (k, sz) in fields.get(m_, {}):
        if sz > group_fields[g].get(k, 0):
            group_fields[g][k] = sz
for (m_, k) in ptr_fields:
    if m_ in comp:
        group_ptr[comp[m_]].add(k)

classes = {}                                   # class name -> (group, size, methods)
for g, ms in cls_methods.items():
    lv = sorted(levels.get(g, ()))
    for m_ in ms:
        fit = [L for L in lv if L >= need[m_]]
        size = fit[0] if fit else need[m_]      # no evidence of a size: just its fields
        name = 'C_%s' % g if not lv or size == max(lv + [size]) else 'C_%s_%x' % (g, size)
        cl = classes.setdefault(name, (g, size, set()))
        cl[2].add(m_)

out = ['/* Generated by tools/class_types.py: C++ classes as flat structs at their',
       ' * original offsets (32-bit layout).  Classes of one hierarchy share a name',
       ' * prefix; C_<group>_<size> is a smaller (base) level of C_<group>.',
       ' * Field names are offsets until named. */',
       '#ifndef CIV2_CLASSES_H', '#define CIV2_CLASSES_H', '', '#pragma pack(push, 1)', '']
emitted = []
for name in sorted(classes, key=lambda n: (classes[n][0], classes[n][1])):
    g, size, ms = classes[name]
    pos, lines = 0, []
    for k in sorted(group_fields[g]):
        sz = group_fields[g][k]
        if k < pos or k + sz > size:
            continue
        if k > pos:
            lines.append('    u8 pad_%x[%d];' % (pos, k - pos))
        t = 'uptr' if sz == 4 and k in group_ptr[g] else TYPES.get(sz, 'u32')   # pointer-sized in native builds
        lines.append('    %s field_%x;' % (t, k))
        pos = k + sz
    if size > pos:
        lines.append('    u8 pad_%x[%d];' % (pos, size - pos))
    if not lines:
        continue
    out.append('/* %d methods, size %#x */' % (len(ms), size))
    out += ['typedef struct %s {' % name] + lines + ['} %s;' % name, '']
    emitted.append(name)
out += ['#pragma pack(pop)', '', '#endif', '']
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import type_names  # noqa: E402  (readable class names, re/type_names.tsv)
open('src/include/civ2classes.h', 'w').write(type_names.apply('\n'.join(out)))
with open('re/classes.tsv', 'w') as f:
    f.write('class\tmethods\n')
    for name in emitted:
        f.write('%s\t%s\n' % (name, ','.join(sorted(classes[name][2]))))
print('methods %d, groups %d, classes %d' % (len(methods), len(cls_methods), len(emitted)))
for name in sorted(emitted, key=lambda n: -len(classes[n][2]))[:10]:
    print('  %s: %d methods, size %#x' % (name, len(classes[name][2]), classes[name][1]))
