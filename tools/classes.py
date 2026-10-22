#!/usr/bin/env python3
"""Recover C++ classes from how __thiscall methods are called.

Evidence used (all from re/decomp.c):
  * method A calls method B with A's own `this`   -> same class (or B is a
    method of A's base class; the two are merged, which is what C needs)
  * A calls B with `this + k` (k > 0)            -> class(B) is a member of
    class(A) at offset k
  * a method is called on `&DAT_x` / `DAT_x` global -> that global is an
    instance of the method's class
  * `*(T *)((int)this + k)` in a method           -> field at offset k of size T
  * `*(undefined ***)this = &PTR_x`               -> class has vtable at x
Writes re/classes.tsv (class id, methods, instances, members, fields, size
estimate) and prints a summary.
"""
import collections
import csv
import re

conv = {r['entry']: r for r in csv.DictReader(open('re/conventions.tsv'), delimiter='\t')}
names = {}
thunk_of = {}
for r in csv.DictReader(open('re/functions.tsv'), delimiter='\t'):
    names[r['name']] = r['entry']
    if r['thunk_target'] and not r['thunk_target'].startswith('EXT'):
        thunk_of[r['entry']] = r['thunk_target']
thiscall = {a for a, r in conv.items() if r['cc'] == '__thiscall'}

text = open('re/decomp.c').read()
parts = re.split(r'^// ==== FUNCTION ([0-9a-f]{8}) (\S+)\n', text, flags=re.M)
bodies = {parts[i]: parts[i + 2] for i in range(1, len(parts), 3)}

parent = {}


def find(x):
    while parent.setdefault(x, x) != x:
        parent[x] = parent[parent[x]]
        x = parent[x]
    return x


def union(a, b):
    ra, rb = find(a), find(b)
    if ra != rb:
        parent[max(ra, rb)] = min(ra, rb)


CALL = re.compile(r'\b([A-Za-z_]\w*)\(\s*(\(void \*\)\s*)?([^,()]*(?:\([^()]*\))?[^,()]*?)\s*[,)]')
members = collections.defaultdict(set)     # (caller method, k, callee method)
instances = collections.defaultdict(set)   # method -> global addresses
fields = collections.defaultdict(collections.Counter)
vtables = {}

for f in thiscall:
    union(f, f)
for f, body in bodies.items():
    is_method = f in thiscall
    for m in CALL.finditer(body):
        callee = names.get(m.group(1))
        if not callee:
            continue
        callee = thunk_of.get(callee, callee)
        if callee not in thiscall:
            continue
        arg = m.group(3).strip()
        if is_method and arg == 'this':
            union(f, callee)
            continue
        mk = re.match(r'^\(int\)this \+ (0x[0-9a-f]+|\d+)$', arg)
        if is_method and mk:
            members[f].add((int(mk.group(1), 0), callee))
            continue
        mg = re.match(r'^&?_?DAT_([0-9a-f]{8})$', arg) or re.match(r'^&?([a-z_][a-z_0-9]*)$', arg)
        if mg and not arg.startswith('local_') and not arg.startswith('param_'):
            instances[callee].add(mg.group(1))
    if is_method:
        for fm in re.finditer(r'\*\((\w+) \*\)\(\(int\)this \+ (0x[0-9a-f]+|\d+)\)', body):
            fields[f][(int(fm.group(2), 0), fm.group(1))] += 1
        vm = re.search(r'\*\(undefined \*\*\*\)this = &PTR_\w*?([0-9a-f]{8})\b', body)
        if vm:
            vtables[f] = vm.group(1)

classes = collections.defaultdict(lambda: {'methods': set(), 'instances': set(), 'members': set(),
                                           'fields': collections.Counter(), 'vtables': set()})
for f in thiscall:
    c = classes[find(f)]
    c['methods'].add(f)
    c['instances'] |= instances.get(f, set())
    c['members'] |= {(k, find(cm)) for k, cm in members.get(f, set())}
    c['fields'] += fields.get(f, collections.Counter())
    if f in vtables:
        c['vtables'].add(vtables[f])

with open('re/classes.tsv', 'w') as out:
    out.write('class\tmethods\tsize_est\tinstances\tvtables\tmembers\tmethod_list\n')
    for cid, c in sorted(classes.items(), key=lambda kv: -len(kv[1]['methods'])):
        size = max([k + {'char': 1, 'byte': 1, 'short': 2, 'ushort': 2}.get(t, 4) for k, t in c['fields']] or [0])
        out.write('%s\t%d\t0x%x\t%s\t%s\t%s\t%s\n' % (
            cid, len(c['methods']), size, ','.join(sorted(c['instances'])), ','.join(sorted(c['vtables'])),
            ','.join('%x:%s' % m for m in sorted(c['members'])), ','.join(sorted(c['methods']))))

big = sorted(classes.values(), key=lambda c: -len(c['methods']))
print('classes:', len(classes), ' with >=5 methods:', sum(1 for c in big if len(c['methods']) >= 5))
for c in big[:25]:
    print('%4d methods  size~0x%-5x instances %-40s vt %s' % (
        len(c['methods']),
        max([k + 4 for k, t in c['fields']] or [0]),
        ','.join(sorted(c['instances']))[:40], ','.join(sorted(c['vtables']))))
