"""Readable names for the inferred classes (re/type_names.tsv: old C_<root>[_<size>]
name -> new name).  Ghidra and the analysis tables keep the C_ names; the
names are applied wherever C source is written (tools/gen_c.py,
tools/class_types.py) and to hand-written sources by tools/rename.py."""
import csv
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
_MAP = None
_PAT = None


def mapping():
    global _MAP, _PAT
    if _MAP is None:
        _MAP = {}
        path = os.path.join(ROOT, 're', 'type_names.tsv')
        if os.path.exists(path):
            for r in csv.DictReader(open(path), delimiter='\t'):
                _MAP[r['old']] = r['name']
        _PAT = re.compile(r'\b(C_[0-9a-f]{8}(?:_[0-9a-f]+)?)\b')
    return _MAP


def apply(text):
    """Every C_ class name in text replaced by its readable name."""
    m = mapping()
    if not m:
        return text
    return _PAT.sub(lambda x: m.get(x.group(1), x.group(1)), text)


# ---- field names (re/field_names.tsv: family C_<root>, offset, name) ----
#
# A named field becomes an anonymous union of field_<k> and its name, so
# code the generator cannot type (and hand-written code) keeps compiling;
# accesses whose object type is certain are rewritten to the name.

_FIELDS = None


def fields():
    global _FIELDS
    if _FIELDS is None:
        _FIELDS = {}
        path = os.path.join(ROOT, 're', 'field_names.tsv')
        if os.path.exists(path):
            for r in csv.DictReader(open(path), delimiter='\t'):
                _FIELDS[(r['family'], int(r['offset'], 16))] = r['name']
    return _FIELDS


def family_of(type_name):
    """C_<root> family of a class name (readable or C_)."""
    if type_name.startswith('C_') and len(type_name) >= 10:
        return type_name[:10]
    inv = {v: k for k, v in mapping().items()}
    old = inv.get(type_name)
    return old[:10] if old else None


def apply_header(text):
    """Named fields as unions in the class header (idempotent)."""
    f = fields()
    if not f:
        return text
    out, fam = [], None
    for line in text.split('\n'):
        m = re.match(r'^typedef struct (\w+) \{$', line)
        if m:
            fam = family_of(m.group(1))
        m = re.match(r'^    (\w+) field_([0-9a-f]+);$', line)
        if fam and m and (fam, int(m.group(2), 16)) in f:
            line = '    union { %s field_%s; %s %s; };' % (m.group(1), m.group(2), m.group(1), f[(fam, int(m.group(2), 16))])
        out.append(line)
    return '\n'.join(out)


_CAST = re.compile(r'\(\((\w+) \*\)((?:[^()]|\([^()]*\))*)\)->field_([0-9a-f]+)\b')


def apply_code(text):
    """field_<k> -> name where the object's class is certain: this, casts
    ((T *)x)->field_k, and locals declared T *v (per function)."""
    f = fields()
    if not f:
        return text
    parts = re.split(r'(?m)^(?=/\* [0-9a-f]{8} )', text)
    for i, body in enumerate(parts):
        types = {}
        m = re.search(r'\((\w+) \*this\b', body)
        if m:
            types['this'] = family_of(m.group(1))
        for d in re.finditer(r'(?m)^  (\w+) \*(\w+);$', body):
            fam = family_of(d.group(1))
            if fam:
                types[d.group(2)] = fam
        # parameters declared T *name in the definition's parameter list
        sig = re.search(r'\(([^(){};]*)\)\s*\n\{', body)
        if sig:
            for d in re.finditer(r'(\w+) \*(\w+)\s*(?:,|$)', sig.group(1)):
                fam = family_of(d.group(1))
                if fam and d.group(2) not in types:
                    types[d.group(2)] = fam

        def var(m):
            fam = types.get(m.group(1))
            name = f.get((fam, int(m.group(2), 16))) if fam else None
            return '%s->%s' % (m.group(1), name) if name else m.group(0)

        def cast(m):
            fam = family_of(m.group(1))
            name = f.get((fam, int(m.group(3), 16))) if fam else None
            return '((%s *)%s)->%s' % (m.group(1), m.group(2), name) if name else m.group(0)
        body = re.sub(r'\b(\w+)->field_([0-9a-f]+)\b', var, body)
        parts[i] = _CAST.sub(cast, body)
    return ''.join(parts)
