#!/usr/bin/env python3
"""Turn the game's static data into ordinary C variables (step 5 of the
clean-up: no emulation of the original memory layout).

Until now all of .rdata and .data was one packed struct in original address
order (`GameData g`, a field `d_<address>` per item, src/data/gamedata.h),
the code reached it through macros (`#define name (*(T *)((u8 *)&g.d_X))`,
src/auto/globals.h and one block per function) and gamedata.c filled it at
startup from an image of the original bytes.  This writes instead:

  * src/data/gamedata.c: one definition per variable, in original address
    order, initialized in C (numbers, strings, arrays); the slots the
    original relocates (addresses of functions and data) are set by
    gamedata_init();
  * src/data/gamedata.h: their declarations;
  * the code: every macro use becomes the variable (a cast where a function
    reads it as another type), the macros go.

A variable starts at every address the code or a data pointer refers to and
runs to the next one (the bytes nothing names belong to the variable before
them, or follow it as name_rest).  Where the code reaches from one into the
next -- an object and the fields the code also names as globals, a table
split into columns, an array a vector constructor runs past -- they become
one packed struct (a "block") whose members keep their names; the extents
AddressSanitizer found over the replays are in re/data_extents.tsv.  Array
addresses are written as pointers ((T *)&name) where the code indexes from
them: it may run past the declared end, which compilers otherwise assume it
does not.

Done once (src/data/gamedata.c is the source now); it ran inside the
civ2-dev container (pefile) on the tree before:

    unglobal.py plan      print what would be made
    unglobal.py apply
"""
import collections
import csv
import glob
import json
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
LO, HI = 0x61c000, 0x6e6b6c
INIT_END = 0x63c800                     # initialized data ends; bss follows
BASE = 0x400000
MARK = re.compile(r'(?m)^(?=/\* [0-9a-f]{8}[ :])')
INT_TYPES = {'i8': 1, 'u8': 1, 'char': 1, 'byte': 1, 'uchar': 1, 'CHAR': 1, 'BYTE': 1, 'i16': 2, 'u16': 2,
             'short': 2, 'ushort': 2, 'WORD': 2, 'i32': 4, 'u32': 4, 'int': 4, 'uint': 4, 'iptr': 4, 'uptr': 4,
             'DWORD': 4, 'LONG': 4, 'BOOL': 4, 'UINT': 4, 'size_t': 4, 'SIZE_T': 4, 'FOURCC': 4, 'ulong': 4,
             'COLORREF': 4, 'MCIDEVICEID': 4, 'MMRESULT': 4, 'ATOM': 2, 'UINT_PTR': 4, 'DWORD_PTR': 4,
             'LPARAM': 4, 'WPARAM': 4, 'LRESULT': 4, 'undefined4': 4, 'sbyte': 1}
SIGNED = {'i8', 'char', 'CHAR', 'i16', 'short', 'i32', 'int', 'iptr', 'LONG', 'BOOL', 'LPARAM', 'LRESULT', 'sbyte'}


def code_files():
    return sorted(glob.glob(os.path.join(ROOT, 'src', 'auto', '*.c')) +
                  glob.glob(os.path.join(ROOT, 'src', 'game', '*.c')) +
                  [os.path.join(ROOT, 'src', 'native', 'crt.c')])


# ---------------------------------------------------------------- the data

def load_items():
    """The GameData fields: (addr, type, name, count, named)."""
    h = open(os.path.join(ROOT, 'src', 'data', 'gamedata.h')).read()
    body = h[h.index('typedef struct GameData {'):h.index('} GameData;')]
    items = []
    for m in re.finditer(r'(?m)^    (.+?) (n_|d_)(\w+?)(?:\[(\d+)\])?;  /\* ([0-9a-f]{8})', body):
        named = m.group(2) == 'n_'
        items.append({'addr': int(m.group(5), 16), 'type': m.group(1).replace(' ', '') if named else m.group(1),
                      'field': m.group(2) + m.group(3), 'name': m.group(3) if named else None,
                      'count': int(m.group(4)) if m.group(4) else None, 'named': named})
    for i, it in enumerate(items):
        it['size'] = (items[i + 1]['addr'] if i + 1 < len(items) else HI) - it['addr']
    return items


def load_image():
    src = open(os.path.join(ROOT, 'src', 'data', 'gamedata.c')).read()
    m = re.search(r'static const char image\[0x([0-9a-f]+) \+ 1\] =\n(.*?);\n', src, re.S)
    data = bytes(int(x, 16) for x in re.findall(r'\\x([0-9a-f]{2})', m.group(2)))
    return data + bytes(HI - LO - len(data))


def load_relocs(img):
    """slot address -> ('func', name) | ('data', address) | ('zero',) | ('num', value)"""
    import pefile
    import paths
    pe = pefile.PE(paths.game_file('civ2.exe'))
    funcs = {}
    for r in csv.DictReader(open(os.path.join(ROOT, 're', 'functions.tsv')), delimiter='\t'):
        if re.match(r'^[A-Za-z_]\w*$', r['name']):
            funcs[int(r['entry'], 16)] = r['name']
    status = {r['name']: r['status'] for r in csv.DictReader(open(os.path.join(ROOT, 're', 'manifest.tsv')),
                                                             delimiter='\t')}
    absent = {n for n, st in status.items() if st in ('ehfunclet', 'crt', 'crt-manual', 'asm')}
    defined = set()
    for p in code_files():
        defined |= set(re.findall(r'(?m)^[A-Za-z][\w \*]*?\b(\w+)\s*\([^;{}]*\)\s*\n\{', open(p).read()))
    for p in glob.glob(os.path.join(ROOT, 'src', 'platform', '*.c')) + glob.glob(os.path.join(ROOT, 'src', 'native', '*.c')):
        defined |= set(re.findall(r'(?m)^[A-Za-z][\w \*]*?\b(\w+)\s*\([^;{}]*\)\s*\n\{', open(p).read()))
    thunks = {}
    th = os.path.join(ROOT, 'build', 'native', 'gen', 'thunks.h')
    if os.path.exists(th):
        for m in re.finditer(r'#define (\w+) (?:\(\([^)]*\)(\w+)\)|(\w+))', open(th).read()):
            thunks[m.group(1)] = m.group(2) or m.group(3)
    out = {}
    for b in pe.DIRECTORY_ENTRY_BASERELOC:
        for e in b.entries:
            a = e.rva + BASE
            if e.type != 3 or not LO <= a < INIT_END:
                continue
            v = int.from_bytes(img[a - LO:a - LO + 4], 'little')
            if v in funcs and funcs[v] not in absent:
                f = thunks.get(funcs[v], funcs[v])
                out[a] = ('func', f) if (f in defined or funcs[v] in defined) else ('zero', funcs[v])
            elif v in funcs:
                out[a] = ('zero', funcs[v])
            elif LO <= v < HI:
                out[a] = ('data', v)
            elif v == 0:
                out[a] = ('zero', None)
            else:
                out[a] = ('num', v)
    return out


# ---------------------------------------------------------------- the code

MACRO = re.compile(r'^#define (\w+) (.*)$')


def parse_ref(expr):
    """A macro body that reaches the data: (kind, type, address) or None.
    kind 'lv' (an lvalue of type) or 'ad' (an address of type *)."""
    e = re.sub(r'\s*/\*.*\*/\s*$', '', expr).strip()
    m = re.match(r'^\(\*\((.+?) \*\)\(\(u8 \*\)&g\.d_([0-9a-f]{8})(?:\[(\d+)\])?(?: \+ (\d+))?\)\)$', e)
    if m:
        return 'lv', m.group(1).strip(), int(m.group(2), 16) + 4 * int(m.group(3) or 0) + int(m.group(4) or 0)
    m = re.match(r'^\(\*\((.+?) \*\)g\.d_([0-9a-f]{8})\)$', e)
    if m:
        return 'lv', m.group(1).strip(), int(m.group(2), 16)
    m = re.match(r'^\(\((.+?) \*\)\(\(u8 \*\)&g\.d_([0-9a-f]{8})(?:\[(\d+)\])?\)\)$', e)
    if m:
        return 'ad', m.group(1).strip(), int(m.group(2), 16) + 4 * int(m.group(3) or 0)
    m = re.match(r'^\(\*\((.+?) \*\)\(\(u8 \*\)&units\[2048\](?: \+ (\d+))?\)\)$', e)
    if m:
        return 'lv', m.group(1).strip(), 0x6660f0 + int(m.group(2) or 0)
    return None


def scan_code():
    """Every reference: macros (global and per function) and raw addresses."""
    refs = collections.defaultdict(list)       # address -> [(alias, kind, type, where)]
    raw = collections.Counter()
    gh = open(os.path.join(ROOT, 'src', 'auto', 'globals.h')).read()
    used = set()
    for p in code_files():
        used |= set(re.findall(r'\b\w+\b', re.sub(r'(?m)^#(define|undef) .*$', '', open(p).read())))
    for ln in gh.split('\n'):
        m = MACRO.match(ln)
        if m and m.group(1) in used:
            r = parse_ref(m.group(2))
            if r:
                refs[r[2]].append((m.group(1), r[0], r[1], 'globals.h'))
    for p in code_files():
        for ln in open(p).read().split('\n'):
            m = MACRO.match(ln)
            if m:
                r = parse_ref(m.group(2))
                if r:
                    refs[r[2]].append((m.group(1), r[0], r[1], os.path.basename(p)))
                continue
            for mm in re.finditer(r'g\.d_([0-9a-f]{8})(?:\[(\d+)\])?', ln):
                raw[int(mm.group(1), 16) + 4 * int(mm.group(2) or 0)] += 1
    return refs, raw


# ---------------------------------------------------------------- planning

def type_size(t, sizes):
    t = t.strip()
    if t.endswith('*'):
        return 4
    return INT_TYPES.get(t) or sizes.get(t)


def c_string(b):
    out = []
    for i, c in enumerate(b):
        if c == 0x22 or c == 0x5c:
            out.append('\\' + chr(c))
        elif 32 <= c < 127 and not (chr(c) in '0123456789abcdefABCDEF' and out and out[-1].startswith('\\x')):
            out.append(chr(c))
        elif c == 10:
            out.append('\\n')
        elif c == 0 and (i + 1 == len(b) or not chr(b[i + 1]).isdigit()):
            out.append('\\0')
        else:
            out.append('\\x%02x' % c)
    return ''.join(out)


def is_string(b):
    n = b.find(b'\0')
    return n > 0 and all(32 <= c < 127 or c in (9, 10, 13) for c in b[:n])


def slug(text, maxlen=40):
    w = re.findall(r'[A-Za-z0-9]+', text)
    s = '_'.join(w).lower()[:maxlen].strip('_')
    return s or 'empty'


def compute_sizes(types):
    """sizeof each C type (32-bit), by compiling a probe."""
    types = sorted(set(t for t in types if t and not t.replace(' ', '').endswith('*') and t not in INT_TYPES))
    src = ['#include "auto_common.h"'] + ['char sz_%d[sizeof(%s)];' % (i, t) for i, t in enumerate(types)]
    d = os.path.join(ROOT, 'build', 'unglobal')
    os.makedirs(d, exist_ok=True)
    open(os.path.join(d, 'sizes.c'), 'w').write('\n'.join(src) + '\n')
    inc = ['-I' + os.path.join(ROOT, x) for x in ('src/include', 'src/auto', 'tools', 'build/native/gen')]
    r = subprocess.run(['gcc', '-m32', '-std=gnu89', '-w', '-include', 'native.h', '-DCIV2_NATIVE'] + inc +
                       ['-c', os.path.join(d, 'sizes.c'), '-o', os.path.join(d, 'sizes.o')], capture_output=True, text=True)
    if r.returncode:
        bad = set(re.findall(r'sizes\.c:(\d+):', r.stderr))
        keep = [t for i, t in enumerate(types) if str(i + 2) not in bad]
        if len(keep) < len(types):
            return compute_sizes(keep)
        raise SystemExit(r.stderr[:2000])
    out = {}
    for ln in subprocess.run(['nm', '-S', os.path.join(d, 'sizes.o')], capture_output=True, text=True).stdout.split('\n'):
        f = ln.split()
        if len(f) == 4 and f[3].startswith('sz_'):
            out[types[int(f[3][3:])]] = int(f[1], 16)
    return out


def plan():
    items = load_items()
    img = load_image()
    relocs = load_relocs(img)
    refs, raw = scan_code()
    texts = [open(p).read() for p in code_files()]
    casts = set(re.findall(r'\((\w+) \*\)\s*&', '\n'.join(texts)))
    casts |= set(re.findall(r'(?m)^[\w* ]+?\b\w+\((?:const )?(\w+) \*', open(os.path.join(ROOT, 'src', 'auto', 'protos.h')).read()))
    sizes = compute_sizes([r[2] for rs in refs.values() for r in rs] + [it['type'] for it in items if it['named']] +
                          list(casts))
    by_addr = {it['addr']: it for it in items}
    starts = set(it['addr'] for it in items if it['named'])
    starts |= set(a for a in refs if a in by_addr) | set(a for a in raw if a in by_addr)
    targets = set(v[1] for v in relocs.values() if v[0] == 'data')
    starts |= set(a for a in targets if a in by_addr)
    inner = [a for a in list(refs) + list(raw) if a not in by_addr]
    STATIC_SIZES.update(static_sizes(refs))
    order = sorted(starts)
    vars_ = []
    for i, a in enumerate(order):
        end = order[i + 1] if i + 1 < len(order) else HI
        vars_.append({'addr': a, 'end': end, 'size': end - a, 'item': by_addr[a]})
    return items, img, relocs, refs, raw, sizes, vars_, inner


EQUIV = [{'i32', 'int', 'LONG', 'BOOL', 'iptr', 'LPARAM', 'LRESULT'}, {'u32', 'uint', 'DWORD', 'uptr', 'UINT', 'ulong',
          'size_t', 'SIZE_T', 'FOURCC', 'COLORREF', 'MCIDEVICEID', 'MMRESULT', 'UINT_PTR', 'DWORD_PTR', 'WPARAM'},
         {'i16', 'short'}, {'u16', 'ushort', 'WORD'}, {'i8', 'char', 'CHAR', 'sbyte'}, {'u8', 'byte', 'uchar', 'BYTE'}]


def same_type(a, b):
    a, b = a.replace(' ', ''), b.replace(' ', '')
    return a == b or any(a in e and b in e for e in EQUIV)


def arith_on(alias, texts):
    """Does the code step from the variable's address (an array)?"""
    return alias in index(texts)['arith']


def ad_object(rs, sizes, v):
    """Only its address is used, as a pointer to an object (not char)."""
    ad = collections.Counter(r[2] for r in rs if r[1] == 'ad' and r[2] not in ('char', 'CHAR', 'i8', 'u8', 'byte'))
    if not ad:
        return False
    t, _ = ad.most_common(1)[0]
    ts = type_size(t, sizes)
    if not ts or v['size'] < ts:
        return False
    if v['size'] == ts:
        v['kind'], v['ctype'], v['count'], v['rest'] = 'scalar', t, None, 0
    elif v['size'] % ts == 0:
        v['kind'], v['ctype'], v['count'], v['rest'] = 'array', t, v['size'] // ts, 0
    else:
        v['kind'], v['ctype'], v['count'], v['rest'] = 'bytes', 'u8', v['size'], 0
    return True


# Objects the code reaches past what the decompiler saw of them (found with
# AddressSanitizer over the replays: build_native.py --target linux32asan):
# address -> bytes the object spans.
OBJECT_SIZES = {}
_ext = os.path.join(ROOT, 're', 'data_extents.tsv')
if os.path.exists(_ext):
    for _ln in open(_ext):
        _f = _ln.split('\t')
        if len(_f) >= 2 and re.match(r'^[0-9a-f]{8}$', _f[0]):
            OBJECT_SIZES[int(_f[0], 16)] = int(_f[1])
STATIC_SIZES = {}
OBJECT_TO_NEXT = os.environ.get('OBJECT_TO_NEXT') == '1'


SIZED_CALLS = {        # function -> (argument holding the address, size argument(s): product)
    'crt_vector_ctor_iterator': (0, (1, 2)), 'crt_vector_dtor_iterator': (0, (1, 2)),
    '_memset': (0, (2,)), 'crt_memset': (0, (2,)), 'crt_memcpy': (0, (2,)), '_memcpy': (0, (2,)),
    'crt_memmove': (0, (2,)), 'mem_copy_src_dst': (1, (2,)), '_strncpy': (0, (2,)), '_fread': (0, (1, 2)),
    '_fwrite': (0, (1, 2)), 'file_read_bytes': (0, (1,)), 'file_write_bytes': (0, (1,))}


def split_args(text, start):
    """The arguments of the call whose '(' is at start, and the end."""
    args, d, cur, i = [], 0, '', start + 1
    while i < len(text):
        c = text[i]
        if c in '([':
            d += 1
        elif c in ')]':
            if d == 0:
                args.append(cur)
                return args, i
            d -= 1
        elif c == ',' and d == 0:
            args.append(cur)
            cur = ''
            i += 1
            continue
        cur += c
        i += 1
    return args, i


def static_sizes(refs):
    """Bytes the code says a global spans: vector constructors' counts, the
    size given to memset, memcpy, fread ... on its address."""
    alias_addr = {}
    for a, rs in refs.items():
        for r in rs:
            alias_addr.setdefault(r[0], a)
    need = collections.defaultdict(int)
    for p in code_files():
        t = open(p).read()
        for m in re.finditer(r'\b(%s)\s*\(' % '|'.join(SIZED_CALLS), t):
            args, _ = split_args(t, m.end() - 1)
            ai, si = SIZED_CALLS[m.group(1)]
            if len(args) <= max((ai,) + si):
                continue
            nums = [re.fullmatch(r'\s*(0x[0-9a-f]+|\d+)\s*', args[k]) for k in si]
            if not all(nums):
                continue
            n = 1
            for x in nums:
                n *= int(x.group(1), 0)
            arg = args[ai]
            mm = re.search(r'g\.d_([0-9a-f]{8})', arg)
            if mm and not re.search(r'\+', arg):
                need[int(mm.group(1), 16)] = max(need[int(mm.group(1), 16)], n)
                continue
            mm = re.fullmatch(r'\s*(?:\(\w+ ?\*?\))?\s*\(?\s*(?:\(\w+ \*\))?\s*&?\s*(\w+)\s*\)?\s*', arg)
            if mm and mm.group(1) in alias_addr:
                a = alias_addr[mm.group(1)]
                need[a] = max(need[a], n)
    return need


def object_classes(v, texts, sizes, first_param):
    """The classes the code treats variable v as: casts of its address, and
    the class of the functions it is passed to as their first argument."""
    cls = collections.Counter()
    for al in v.get('aliases', []):
        cls.update(cast_types(al, texts))
        for f, k in index(texts)['calls'].get(al, {}).items():
            c = first_param.get(f)
            if c:
                cls[c] += k
    return [c for c in cls if c not in INT_TYPES and c not in ('void', 'char') and type_size(c, sizes)]


def group_objects(vars_, sizes, texts):
    """A global object (a window, a dialog, a table) is often followed by
    data the decompiler saw as separate globals but the object's methods
    reach through `this`: its embedded window, handlers, fields.  Such a run
    -- from an object to the next object -- becomes one packed struct whose
    members are those variables, in their order: the memory stays as one
    piece, and each keeps its name (block.member)."""
    protos = open(os.path.join(ROOT, 'src', 'auto', 'protos.h')).read()
    first_param = {}
    for m in re.finditer(r'(?m)^[\w* ]+?\b(\w+)\((?:const )?(\w+) \*', protos):
        first_param.setdefault(m.group(1), m.group(2))
    for v in vars_:
        v['classes'] = object_classes(v, texts, sizes, first_param) if v['kind'] not in ('named', 'string') else []
        if not v['classes'] and v['addr'] in OBJECT_SIZES and (v['kind'] != 'named' or v['count']):
            v['classes'] = ['u8']

    def section(a):
        return 0 if a < 0x624000 else 1 if a < INIT_END else 2
    groups = []
    i = 0
    while i < len(vars_):
        v = vars_[i]
        if not v['classes']:
            i += 1
            continue
        big = max([type_size(c, sizes) for c in v['classes'] if type_size(c, sizes) <= 8192] + [0])
        limit = v['addr'] + max(big, STATIC_SIZES.get(v['addr'], 0), OBJECT_SIZES.get(v['addr'], 0))
        j = i + 1
        while j < len(vars_) and vars_[j]['kind'] != 'string' and \
                (vars_[j]['kind'] != 'named' or (vars_[j]['count'] and vars_[j]['addr'] < limit)) and \
                section(vars_[j]['addr']) == section(v['addr']) and \
                (vars_[j]['addr'] < limit or not vars_[j]['classes']):
            if vars_[j]['classes']:
                w = vars_[j]
                wb = max([type_size(c, sizes) for c in w['classes'] if type_size(c, sizes) <= 8192] + [0])
                limit = max(limit, w['addr'] + max(wb, STATIC_SIZES.get(w['addr'], 0), OBJECT_SIZES.get(w['addr'], 0)))
            j += 1
        if j > i + 1 or v['addr'] in OBJECT_SIZES and OBJECT_SIZES[v['addr']] > v['size']:
            groups.append(vars_[i:j])
        i = j
    return groups


_INDEX = {}


def index(texts):
    """One pass over the code: which names have their address taken, stepped
    from, cast to a class, or passed to a function as its first argument."""
    key = id(texts)
    if key in _INDEX:
        return _INDEX[key]
    ix = {'addr': set(), 'arith': set(), 'casts': collections.defaultdict(collections.Counter),
          'calls': collections.defaultdict(collections.Counter)}
    for t in texts:
        ix['addr'] |= set(re.findall(r'(?:^|[^\w)\]\s]|\*\))\s*&\s*(\w+)', t, re.M))
        ix['arith'] |= set(re.findall(r'&\s*(\w+)\s*[+-]', t)) | set(re.findall(r'\(\s*&\s*(\w+)\s*\)\s*\[', t)) | \
            set(re.findall(r'&(\w+)\)\s*\[', t))
        for m in re.finditer(r'\((\w+) \*\)\s*&\s*(\w+)', t):
            ix['casts'][m.group(2)][m.group(1)] += 1
        for m in re.finditer(r'\b(\w+)\(\s*(?:\([\w ]+\*\))?\s*&\s*(\w+)\b(?!\s*[\[.])', t):
            ix['calls'][m.group(2)][m.group(1)] += 1
    _INDEX[key] = ix
    return ix


def addr_taken(alias, texts):
    """Does the code take the variable's address (a callee may read past it)?"""
    return alias in index(texts)['addr']


def cast_types(alias, texts):
    """The classes the code casts the variable's address to."""
    return index(texts)['casts'].get(alias, collections.Counter())


def decide(vars_, refs, raw, img, relocs, sizes, texts):
    """Name, type and shape of each variable."""
    gh_names = {}
    for a, rs in refs.items():
        for r in rs:
            if r[3] == 'globals.h':
                gh_names.setdefault(a, r[0])
    for v in vars_:
        a, it = v['addr'], v['item']
        rs = refs.get(a, [])
        if it['named']:
            v['name'] = it['name']
            v['kind'] = 'named'
            v['ctype'] = it['type']
            v['count'] = it['count']
            continue
        lv = collections.Counter(r[2] for r in rs if r[1] == 'lv' and not (r[3] == 'globals.h' and r[2] == 'i8'))
        if not lv:
            lv = collections.Counter(r[2] for r in rs if r[1] == 'lv')
        aliases = [r[0] for r in rs]
        good = [n for n in set(aliases) if not re.search(r'(^_?(DAT|UNK|LAB|PTR)_)|_[0-9a-f]{8}$', n)]
        plain = [n for n in good if not re.search(r'_(i8|u8|i16|u16|i32|u32|int|uint|short|ushort|iptr|uptr|'
                                                    r'char|byte|value\d*)$', n)]
        cnt = collections.Counter(aliases)
        if gh_names.get(a) in plain:
            base = gh_names[a]
        elif plain or good:
            base = max(plain or good, key=lambda n: (cnt[n], -len(n)))
        else:
            base = gh_names.get(a) or (cnt.most_common(1)[0][0] if aliases else None)
        v['aliases'] = sorted(set(aliases))
        v['name'] = base
        b = img[a - LO:v['end'] - LO]
        v['lv'] = bool(lv)
        if a in STRING_KIND:
            lv = None
        if lv:
            t, _ = lv.most_common(1)[0]
            ts = type_size(t, sizes)
            casts = collections.Counter()
            for al in set(aliases):
                casts.update(cast_types(al, texts))
            if t in ('i8', 'u8', 'char', 'byte') and casts:   # a placeholder type: an object
                big = [c for c in casts if c not in INT_TYPES and type_size(c, sizes) and
                       v['size'] < type_size(c, sizes) <= 4096]
                if big:
                    c = max(big, key=lambda c: type_size(c, sizes))
                    v['big'] = (c, type_size(c, sizes))
                fit = [c for c in casts if c not in INT_TYPES and type_size(c, sizes) and type_size(c, sizes) <= v['size']]
                ct = max(fit, key=lambda c: (type_size(c, sizes), casts[c])) if fit else None
                cs = type_size(ct, sizes) if ct else None
                if ct and v['size'] == cs:
                    v['kind'], v['ctype'], v['count'], v['rest'] = 'scalar', ct, None, 0
                    continue
                if ct and v['size'] % cs == 0:          # an array of them (a vector constructor's)
                    v['kind'], v['ctype'], v['count'], v['rest'] = 'array', ct, v['size'] // cs, 0
                    continue
                if ct:                                  # bigger than the class: the whole span
                    v['kind'], v['ctype'], v['count'], v['rest'] = 'bytes', 'u8', v['size'], 0
                    continue
            v['ctype'] = t
            arr = any(arith_on(al, texts) or addr_taken(al, texts) for al in set(aliases))
            if arr and ts and v['size'] > ts and v['size'] % ts and t in ('i8', 'char', 'CHAR', 'u8', 'byte'):
                v['size'] -= v['size'] % ts
            if ts and v['size'] >= ts and (arr and v['size'] % ts == 0):
                v['kind'], v['count'] = 'array', v['size'] // ts
            elif ts and v['size'] >= ts:
                v['kind'], v['count'] = 'scalar', None
                v['rest'] = v['size'] - ts
            else:
                v['kind'], v['count'], v['ctype'] = 'bytes', v['size'], 'u8'
        elif ad_object(rs, sizes, v):
            pass
        elif is_string(b) and a < INIT_END:
            v['kind'], v['ctype'], v['count'] = 'string', 'char', v['size']
        elif all(a + 4 * k in relocs for k in range(v['size'] // 4)) and v['size'] % 4 == 0:
            v['kind'], v['ctype'], v['count'] = 'ptrs', 'uptr', v['size'] // 4
        else:
            v['kind'], v['ctype'], v['count'] = 'bytes', 'u8', v['size']


# ---------------------------------------------------------------- emitting

OVERHANG = {'units': 1}      # units[2048]: the scratch unit the game keeps after the table


def elem(v, sizes):
    """(element type, element size, count or None) of a variable."""
    t = v['ctype']
    if v['kind'] == 'named':
        cnt = v['count']
        if cnt is not None and not v.get('block'):    # in a block, what follows is the next member
            cnt += OVERHANG.get(v['name'], 0)
        return t, type_size(t, sizes), cnt
    if v['kind'] in ('array', 'string', 'ptrs', 'bytes'):
        return t, type_size(t, sizes), v['count']
    return t, type_size(t, sizes), None


def decl_text(t, name, cnt):
    m = re.match(r'^(.*?)\s*((?:\*\s*)*)$', t)
    base, stars = m.group(1), m.group(2).replace(' ', '')
    return '%s %s%s%s' % (base, stars, name, '[%d]' % cnt if cnt is not None else '')


def int_value(b, t):
    v = int.from_bytes(b, 'little')
    if t in SIGNED and v >> (8 * len(b) - 1):
        v -= 1 << (8 * len(b))
    return str(v) if -10 < v < 10 else ('-0x%x' % -v if v < 0 else '0x%x' % v)


def base(v):
    """How code names variable v (a member of its object's block)."""
    return '%s.%s' % (v['block'], v['name']) if v.get('block') else v['name']


def rest_base(v):
    return base(v) + '_rest'


class Emitter:
    def __init__(self, vars_, img, relocs, sizes):
        self.vars = vars_
        self.img, self.relocs, self.sizes = img, relocs, sizes
        self.starts = [v['addr'] for v in vars_]
        self.fix = []                               # runtime fixups
        self.init_blobs = []
        for v in vars_:
            t, es, cnt = elem(v, sizes)
            main = v['size'] - v.get('rest', 0)
            if v['kind'] == 'named' and es:
                main = min(v['size'], es * (cnt or 1))
            v['main'], v['rest'] = main, v['size'] - main

    def var_at(self, a):
        import bisect
        i = bisect.bisect_right(self.starts, a) - 1
        return self.vars[i]

    def target(self, slot, cast='uptr'):
        r = self.relocs[slot]
        if r[0] == 'func':
            return '(%s)&%s' % (cast, r[1])
        if r[0] == 'data':
            w = self.var_at(r[1])
            off = r[1] - w['addr']
            if off >= w['main']:
                return '(%s)((u8 *)%s + %d)' % (cast, rest_base(w), off - w['main'])
            return '(%s)&%s' % (cast, base(w)) if not off else '(%s)((u8 *)&%s + %d)' % (cast, base(w), off)
        if r[0] == 'zero':
            return '0' + ('  /* %s: not in native builds */' % r[1] if r[1] else '')
        return '0x%08xu' % r[1]

    def runtime(self, lhs_base, a, n):
        """Relocated slots in [a, a+n) that hold a function or data address:
        set at startup (the initial bytes hold 0 there)."""
        for off in range(0, n):
            r = self.relocs.get(a + off)
            if r and r[0] in ('func', 'data'):
                self.fix.append('    *(uptr *)((u8 *)%s + %d) = %s;' % (lhs_base, off, self.target(a + off)))

    def bytes_of(self, a, n):
        """The initial bytes, the relocated slots cleared (set at startup, or
        0 where the function is not in native builds); code addresses of the
        original stay as numbers."""
        b = bytearray(self.img[a - LO:a - LO + n])
        for off in range(n):
            r = self.relocs.get(a + off)
            if r and r[0] != 'num':
                b[off:off + 4] = bytes(4)
        return bytes(b)

    def blob_init(self, b):
        b = b.rstrip(b'\0')
        return ' = "%s"' % c_string(b) if b else ''

    def define_block(self, bname, members):
        """(header lines, definition lines) of a block: its struct type in the
        header, the variable here, its bytes copied in at startup."""
        a0 = members[0]['addr']
        end = members[-1]['end']
        body = []
        for v in members:
            t, es, cnt = elem(v, self.sizes)
            size = (es or 0) * (cnt or 1)
            if size != v['main']:
                raise SystemExit('block member %s: %d bytes declared, %d there' % (v['name'], size, v['main']))
            body.append('    %s;  /* %08x */' % (decl_text(t, v['name'], cnt), v['addr']))
            if v['rest']:
                body.append('    u8 %s_rest[%d];' % (v['name'], v['rest']))
        h = ['#pragma pack(push, 1)', 'struct %s {' % bname] + body + ['};', '#pragma pack(pop)',
                                                                      'extern struct %s %s;' % (bname, bname)]
        aliases = []
        for v in members:
            if v['kind'] == 'named':          # the game's own table: its name points into the block
                t, es, cnt = elem(v, self.sizes)
                h.append('extern %s *const %s;  /* = %s.%s */' % (t, v['name'], bname, v['name']))
                aliases.append('%s *const %s = %s.%s;' % (t, v['name'], bname, v['name']))
        b = self.bytes_of(a0, end - a0) if a0 < INIT_END else b''
        if any(b):
            self.init_blobs.append('static const char %s_init[] = "%s";' % (bname, c_string(b.rstrip(b'\0'))))
            self.fix.append('    memcpy(&%s, %s_init, sizeof %s_init - 1);' % (bname, bname, bname))
        self.runtime('&' + bname, a0, end - a0)
        return h, ['struct %s %s;  /* %08x */' % (bname, bname, a0)] + aliases

    def define(self, v):
        """(header declaration, definition lines) of variable v."""
        t, es, cnt = elem(v, self.sizes)
        a, name = v['addr'], v['name']
        main_size = v['main']
        decl = decl_text(t, name, cnt)
        b = self.bytes_of(a, main_size) if a < INIT_END else b''
        init = ''
        intlike = t in INT_TYPES
        ptr = t.replace(' ', '').endswith('*')
        if v['kind'] in ('string', 'bytes'):
            init = self.blob_init(b)
            self.runtime(name, a, main_size)
        elif intlike or ptr or v['kind'] == 'ptrs':
            vals = []
            n = cnt or 1
            for k in range(n):
                slot = a + k * es
                if es == 4 and slot in self.relocs:
                    vals.append(self.target(slot, t if ptr else 'uptr'))
                elif ptr:
                    x = int.from_bytes(b[k * es:(k + 1) * es], 'little') if b else 0
                    vals.append('0' if not x else '(%s)0x%x' % (t, x))
                else:
                    vals.append(int_value(b[k * es:(k + 1) * es], t) if b else '0')
            if cnt is None:
                init = '' if vals[0] in ('0', '0x0') else ' = ' + vals[0]
            elif any(x not in ('0', '0x0') for x in vals):
                while vals and vals[-1] in ('0', '0x0'):
                    vals.pop()
                init = ' = {%s}' % ', '.join(x.split('  /*')[0] for x in vals)
        else:                                   # a struct (or array of structs)
            if any(b):
                self.fix.append('    memcpy(&%s, %s_init, sizeof %s_init - 1);' % (name, name, name))
                self.init_blobs.append('static const char %s_init[] = "%s";' % (name, c_string(b.rstrip(b'\0'))))
            self.runtime('&' + name, a, main_size)
        lines = ['%s%s;  /* %08x */' % (decl, init, a)]
        hdecl = ['extern %s;' % decl]
        rest = v['size'] - main_size
        if rest > 0:
            rb = self.bytes_of(a + main_size, rest) if a + main_size < INIT_END else b''
            lines.append('u8 %s_rest[%d]%s;  /* what follows it, named by nothing */' % (name, rest, self.blob_init(rb)))
            hdecl.append('extern u8 %s_rest[%d];' % (name, rest))
            self.runtime(name + '_rest', a + main_size, rest)
        return hdecl, lines


# ---------------------------------------------------------------- rewriting

def class_members(classes):
    """class -> {offset: [(name, type, count)]} for the classes of objects
    (offsets by compiling offsetof probes)."""
    text = open(os.path.join(ROOT, 'src', 'include', 'civ2classes.h')).read() + \
        open(os.path.join(ROOT, 'src', 'include', 'civ2types.h')).read()
    members = {}
    probes = []
    for c in classes:
        m = re.search(r'typedef struct %s \{(.*?)\} %s;' % (c, c), text, re.S)
        if not m:
            continue
        found = []
        for d in re.finditer(r'\b([A-Za-z_][\w]*(?:\s*\*)*)\s+(\w+)(?:\[(\w+)\])?;', m.group(1)):
            t, n, cnt = d.group(1).strip(), d.group(2), d.group(3)
            if t in ('struct', 'union') or re.match(r'^(field|pad|gap|at)_[0-9a-f]+$', n):
                continue
            found.append((n, t, int(cnt, 0) if cnt else None))
        members[c] = found
        probes += ['char off_%d[__builtin_offsetof(%s, %s) + 1];' % (len(probes), c, n) for n, t, cnt in found]
    keys = [(c, i) for c in members for i in range(len(members[c]))]
    src = ['#include "auto_common.h"'] + probes
    d = os.path.join(ROOT, 'build', 'unglobal')
    os.makedirs(d, exist_ok=True)
    open(os.path.join(d, 'offs.c'), 'w').write('\n'.join(src) + '\n')
    inc = ['-I' + os.path.join(ROOT, x) for x in ('src/include', 'src/auto', 'tools', 'build/native/gen')]
    r = subprocess.run(['gcc', '-m32', '-std=gnu89', '-w', '-include', 'native.h', '-DCIV2_NATIVE'] + inc +
                       ['-c', os.path.join(d, 'offs.c'), '-o', os.path.join(d, 'offs.o')], capture_output=True, text=True)
    out = collections.defaultdict(lambda: collections.defaultdict(list))
    if r.returncode:
        return out
    for ln in subprocess.run(['nm', '-S', os.path.join(d, 'offs.o')], capture_output=True, text=True).stdout.split('\n'):
        f = ln.split()
        if len(f) == 4 and f[3].startswith('off_'):
            c, i = keys[int(f[3][4:])]
            n, t, cnt = members[c][i]
            out[c][int(f[1], 16) - 1].append((n, t, cnt))
    return out


class Rewriter:
    def __init__(self, em, sizes):
        self.em, self.sizes = em, sizes
        self.members = class_members(sorted(set(v['ctype'] for v in em.vars if v.get('object'))))

    def member(self, w, t, off):
        """name.member for a piece of an object, when the class has a member of
        that type there."""
        for n, mt, cnt in self.members.get(w['ctype'], {}).get(off, []):
            if same_type(mt, t) and cnt is None:
                return '%s.%s' % (w['name'], n), '&%s.%s' % (w['name'], n)
        for base, lst in self.members.get(w['ctype'], {}).items():
            for n, mt, cnt in lst:
                es = type_size(mt, self.sizes)
                if cnt and es and same_type(mt, t) and base <= off < base + es * cnt and (off - base) % es == 0:
                    k = (off - base) // es
                    return '%s.%s[%d]' % (w['name'], n, k), '&%s.%s[%d]' % (w['name'], n, k)
        return None

    def lv(self, t, a):
        """(value, address) expressions for an lvalue of type t at address a."""
        w = self.em.var_at(a)
        off = a - w['addr']
        name = base(w)
        et, es, cnt = elem(w, self.sizes)
        if off >= w['main']:
            rb, off = rest_base(w), off - w['main']
            p = '(%s + %d)' % (rb, off) if off else rb
            return '(*(%s *)%s)' % (t, p), '((%s *)%s)' % (t, p)
        if cnt is None and off == 0 and same_type(t, et):
            return name, '&' + name
        if w.get('object') and off:
            r = self.member(w, t, off)
            if r:
                return r
        if cnt is not None and es and off % es == 0 and same_type(t, et):
            k = off // es
            # the address through a pointer: the code may index past the
            # array's declared end (into the table it is part of), which
            # compilers take to be impossible for an array
            return '%s[%d]' % (name, k), ('((%s *)&%s)' % (t, name) if k == 0 else '((%s *)&%s + %d)' % (t, name, k))
        if cnt is not None and es and w['kind'] == 'named':
            k, inner = divmod(off, es)
            p = '&%s[%d]' % (name, k) if not inner else '((u8 *)&%s[%d] + %d)' % (name, k, inner)
        else:
            p = '&' + name if not off else '((u8 *)&%s + %d)' % (name, off)
        return '(*(%s *)%s)' % (t, p), '((%s *)%s)' % (t, p)

    def ad(self, t, a):
        w = self.em.var_at(a)
        off = a - w['addr']
        et, es, cnt = elem(w, self.sizes)
        if off == 0 and cnt is not None and same_type(t, et):
            return '((%s *)&%s)' % (t, base(w))
        if off == 0 and cnt is None and same_type(t, et):
            return '&' + base(w)
        if off >= w['main']:
            off -= w['main']
            return '((%s *)%s)' % (t, rest_base(w)) if not off else '((%s *)(%s + %d))' % (t, rest_base(w), off)
        return '((%s *)&%s)' % (t, base(w)) if not off else '((%s *)((u8 *)&%s + %d))' % (t, base(w), off)

    def raw(self, a):
        w = self.em.var_at(a)
        off = a - w['addr']
        if off >= w['main']:
            off -= w['main']
            return '(u8 *)%s' % rest_base(w) if not off else '((u8 *)%s + %d)' % (rest_base(w), off)
        return '(u8 *)&%s' % base(w) if not off else '((u8 *)&%s + %d)' % (base(w), off)

    def expr(self, info, amp):
        kind, t, a = info
        if kind == 'lv':
            val, adr = self.lv(t, a)
            return adr if amp else val
        e = self.ad(t, a)
        return ('&' + e) if amp else e


IDENT_DECL = re.compile(r'(?m)^\s+[A-Za-z_][\w ]*?[\s\*]+(\w+)\s*(?:\[[^\]]*\])*\s*(?:=[^;]*)?;')


def rewrite_text(text, gmap, rw, report):
    """Replace every macro use and raw g reference in one file.  A local
    that has the name a global now takes (where the function uses that
    global) is renamed first."""
    lines = text.split('\n')
    out, active, body = [], {}, None
    sig = ''
    for ln in lines:
        if body is not None:
            body.append(ln)
            if ln == '}':
                out.extend(finish_body(body, dict(active), gmap, rw, report, sig))
                body = None
            continue
        m = MACRO.match(ln)
        if m:
            r = parse_ref(m.group(2))
            if r:
                active[m.group(1)] = r
                continue
        u = re.match(r'^#undef (\w+)\s*$', ln)
        if u and (u.group(1) in active or u.group(1) in gmap):
            active.pop(u.group(1), None)
            continue
        if ln == '{' and out:
            body = [ln]
            sig = '\n'.join(out[-4:])
            continue
        out.append(sub_line(ln, active, gmap, rw))
    if body:
        out.extend(finish_body(body, active, gmap, rw, report, sig))
    return '\n'.join(out)


def finish_body(body, active, gmap, rw, report, sig):
    text = '\n'.join(body)
    used = set(n for n in re.findall(r'\b[A-Za-z_]\w*\b', text) if n in active or n in gmap)
    new_names = set()
    for n in used:
        info = active.get(n) or gmap[n]
        new_names.add(rw.em.var_at(info[2])['name'])
    params = set(re.findall(r'(\w+)\s*[,)]', sig.split('(', 1)[1])) if '(' in sig else set()
    locals_ = set(m.group(1) for m in IDENT_DECL.finditer(text)) | params
    clash = (new_names & locals_) - used
    for n in sorted(clash):
        k = 2
        while n + str(k) in text:
            k += 1
        text = re.sub(r'(?<![\w.])(?<!->)\b%s\b' % re.escape(n), n + str(k), text)
        report.append('renamed local %s -> %s%d' % (n, n, k))
        if n in params:
            report.append('  (a parameter: also in the signature, fix by hand)')
    return [sub_line(ln, active, gmap, rw) for ln in text.split('\n')]


_TYPES = None


def type_names():
    global _TYPES
    if _TYPES is None:
        _TYPES = set('char short int long unsigned signed float double void struct union enum'.split()) | set(INT_TYPES)
        for p in glob.glob(os.path.join(ROOT, 'src', 'include', '*.h')) + glob.glob(os.path.join(ROOT, 'src', 'platform', '*.h')) + \
                [os.path.join(ROOT, 'tools', 'ghidra.h'), os.path.join(ROOT, 'src', 'auto', 'protos.h')]:
            t = open(p, errors='replace').read()
            _TYPES |= set(re.findall(r'\}\s*(\w+)\s*[;,]', t)) | set(re.findall(r'typedef [^;]*?\b(\w+)\s*;', t))
            _TYPES |= set(re.findall(r'typedef [^;]*?\(\s*\*\s*(\w+)\s*\)', t))
    return _TYPES


def tidy(text, strings):
    """Plainer forms of what the rewrite leaves: (iptr)&x for (iptr)((u8 *)&x),
    a string's name for its address (unless the code steps from it)."""
    x = r'[A-Za-z_][\w.]*(?:\[\d+\])?'
    text = re.sub(r'\(u8 \*\)\(\(i8 \*\)&(%s)\)' % x, r'(u8 *)&\1', text)
    text = re.sub(r'\(iptr\)\(\(u8 \*\)&(%s)\)' % x, r'(iptr)&\1', text)

    def string(m):
        return m.group(1) if m.group(1) in strings else m.group(0)
    text = re.sub(r'\(\(char \*\)&(%s)\)(?!\s*[\[+-])' % x, string, text)
    return text


def sub_line(ln, active, gmap, rw):
    if ln.startswith('#'):
        return ln
    ln = re.sub(r'\(u8 \*\)&g\.d_([0-9a-f]{8})(?:\[(\d+)\])?(?: \+ (\d+))?',
                lambda m: rw.raw(int(m.group(1), 16) + 4 * int(m.group(2) or 0) + int(m.group(3) or 0)), ln)
    names = set(re.findall(r'\b[A-Za-z_]\w*\b', ln))
    hits = [n for n in names if n in active or n in gmap]
    if not hits:
        return ln
    pat = re.compile(r'(?<![\w.])(?<!->)(&\s*)?\b(%s)\b' % '|'.join(map(re.escape, sorted(hits, key=len, reverse=True))))

    def rep(m):
        info = active.get(m.group(2)) or gmap[m.group(2)]
        amp = bool(m.group(1))
        before = m.string[:m.start()]
        cast = re.search(r'\(\s*(?:const\s+)?([A-Za-z_]\w*)(?:\s+\w+)?\s*\**\s*\)\s*$', before)
        cast = cast and cast.group(1) in type_names()
        if amp and re.search(r'[\w)\]]\s*$', before) and not cast:     # a & b: binary
            return m.group(1) + rw.expr(info, False)
        return rw.expr(info, amp)
    return pat.sub(rep, ln)




def reserved_names():
    """Identifiers a variable must not take: functions, types, macros, keywords."""
    names = set('auto break case char const continue default do double else enum extern float for goto if inline '
                'int long register restrict return short signed sizeof static struct switch typedef union unsigned '
                'void volatile while'.split())
    for p in [os.path.join(ROOT, 'src', 'auto', 'protos.h')] + glob.glob(os.path.join(ROOT, 'src', 'include', '*.h')) + \
            glob.glob(os.path.join(ROOT, 'src', 'platform', '*.h')) + [os.path.join(ROOT, 'tools', 'ghidra.h')]:
        t = open(p, errors='replace').read()
        names |= set(re.findall(r'(?m)^\s*#\s*define\s+(\w+)', t))
        names |= set(re.findall(r'\b(\w+)\s*\(', t))
        names |= set(re.findall(r'\}\s*(\w+)\s*[;,]', t)) | set(re.findall(r'typedef [^;]*?\b(\w+)\s*;', t))
    for p in code_files() + glob.glob(os.path.join(ROOT, 'src', 'platform', '*.c')):
        names |= set(re.findall(r'(?m)^[A-Za-z][\w \*]*?\b(\w+)\s*\([^;{}]*\)\s*\n\{', open(p).read()))
    return names


def assign_names(vars_, img):
    reserved = reserved_names()
    taken = set()
    unnamed = []

    def unique(n):
        n = re.sub(r'\W', '_', n)
        if re.match(r'^\d', n):
            n = 'n' + n
        base, k = n, 2
        while n in taken or n in reserved:
            n = '%s_%d' % (base, k)
            k += 1
        taken.add(n)
        return n
    for v in vars_:                          # the game's own names first
        if v['kind'] == 'named':
            v['name'] = v['name']
            taken.add(v['name'])
    for v in vars_:
        if v['kind'] == 'named':
            continue
        n = v.get('name')
        b = img[v['addr'] - LO:v['end'] - LO]
        text = b[:b.find(b'\0')].decode('latin-1') if is_string(b) else ''
        m = re.match(r'^s_(.*)_[0-9a-f]{8}$', n or '')
        if m:
            n = 'str_' + slug(text or m.group(1))
        elif re.match(r'^PTR_s_(.*)_[0-9a-f]{8}$', n or ''):
            n = 'str_ptr_' + slug(re.match(r'^PTR_s_(.*)_[0-9a-f]{8}$', n).group(1))
        elif re.match(r'^PTR_(.*)_[0-9a-f]{8}$', n or ''):
            n = 'ptr_' + slug(re.match(r'^PTR_(.*)_[0-9a-f]{8}$', n).group(1))
        elif n and re.match(r'^(DAT|_DAT|UNK|LAB)_', n):
            n = None
        if v['addr'] in MANUAL_NAMES:
            n = MANUAL_NAMES[v['addr']]
        if not n:
            if v['kind'] == 'string':
                n = 'str_' + slug(text)
            elif not any(b[:8]) and v['size'] <= 8 and not v.get('lv'):
                n = 'str_empty'
        if not n:
            n = MANUAL_NAMES.get(v['addr'])
        if not n:
            unnamed.append(v)
            n = 'data_%08x' % v['addr']
        v['name'] = unique(n)
    return unnamed


MANUAL_NAMES = {        # unnamed data the code reaches by address, named from its uses
    0x0061cce0: 'cityview_slot_tables_init', 0x006250d8: 'open_path_prefix', 0x006254f8: 'str_game',
    0x0062551c: 'str_name', 0x006359d4: 'str_game', 0x00638d90: 'str_ok', 0x0063a438: 'crt_block_list',
    0x0063d058: 'profile_difficulty_text', 0x0063d260: 'profile_barbarians_text', 0x0063d468: 'profile_count_text',
    0x0063d56c: 'profile_count_text2', 0x0063d670: 'profile_map_width_text', 0x0063d774: 'profile_map_height_text',
    0x0063e540: 'casualty_parent_wnd', 0x00641884: 'research_popup_sprite', 0x00641b54: 'research_popup_sprite2',
    0x006451d8: 'notify_sprites', 0x00645700: 'research_dialog_sprite', 0x006458e0: 'research_popup_sprite3',
    0x00645fe8: 'city_notify_sprite', 0x00655294: 'layout_rect_main', 0x0066c60a: 'saved_layout_rects',
    0x0066c662: 'saved_layout_rect2', 0x0066cae0: 'tile_number_font', 0x006a1b7c: 'editor_text_fill_rect',
    0x006a6c60: 'pedia_describe_rect', 0x006ac0f8: 'sprite_editor_marker_rect', 0x006ac46c: 'sprite_editor_fill_rect',
    0x006ad014: 'unit_sound_editor_fill_rect', 0x006ad110: 'net_ping_message', 0x006ad24c: 'startup_log_text',
    0x006cedc0: 'path_grid_costs', 0x00639e50: 'rand_seed', 0x0064bc1a: 'prefs_science_rate',
    0x0064bc1c: 'prefs_tax_rate'}
STRING_KIND = {0x006254f8, 0x0062551c, 0x006359d4, 0x00638d90}   # read as a 4-byte tag in one place


def apply():
    items, img, relocs, refs, raw, sizes, vars_, inner = plan()
    texts = [open(p).read() for p in code_files()]
    decide(vars_, refs, raw, img, relocs, sizes, texts)
    assign_names(vars_, img)
    groups = group_objects(vars_, sizes, texts)
    for g in groups:
        bname = g[0]['name'] + '_block'
        for v in g:
            v['block'] = bname
    em = Emitter(vars_, img, relocs, sizes)
    hdecls, defs = [], []
    i = 0
    while i < len(vars_):
        v = vars_[i]
        if v.get('block'):
            j = i
            while j < len(vars_) and vars_[j].get('block') == v['block']:
                j += 1
            h, d = em.define_block(v['block'], vars_[i:j])
            i = j
        else:
            h, d = em.define(v)
            i += 1
        hdecls += h
        defs += d
    gmap = {}
    for ln in open(os.path.join(ROOT, 'src', 'auto', 'globals.h')).read().split('\n'):
        m = MACRO.match(ln)
        if m:
            r = parse_ref(m.group(2))
            if r:
                gmap[m.group(1)] = r
    rw = Rewriter(em, sizes)
    report = []
    # the game's tables that became pointers into a block: &table is the table
    ptab = [v['name'] for v in vars_ if v['kind'] == 'named' and v.get('block')]
    strings = set(base(v) for v in vars_ if v['kind'] == 'string')
    for p in code_files():
        t = open(p).read()
        n = rewrite_text(t, gmap, rw, report)
        if ptab:
            n = re.sub(r'&\s*(%s)\b(?!\s*\[)' % '|'.join(ptab), r'\1', n)
        n = tidy(n, strings)
        if n != t:
            open(p, 'w').write(n)
    h = ['/* The game\'s static data (the original\'s .rdata and .data): one variable',
         ' * per item, in the original\'s address order (tools/unglobal.py made them',
         ' * from the single struct that kept the original layout). */',
         '#ifndef CIV2_GAMEDATA_H', '#define CIV2_GAMEDATA_H', '', '#include "civ2types.h"', ''] + hdecls + \
        ['', '/* Sets the addresses the data holds (functions, other data). */', 'void gamedata_init(void);', '',
         '#endif', '']
    open(os.path.join(ROOT, 'src', 'data', 'gamedata.h'), 'w').write('\n'.join(h))
    c = ['/* The game\'s static data, initialized as the original\'s (see gamedata.h). */',
         '#include <string.h>', '#include "auto_common.h"', ''] + defs + [''] + em.init_blobs + \
        ['', 'void gamedata_init(void)', '{'] + em.fix + ['}', '']
    open(os.path.join(ROOT, 'src', 'data', 'gamedata.c'), 'w').write('\n'.join(c))
    os.remove(os.path.join(ROOT, 'src', 'auto', 'globals.h'))
    ac = os.path.join(ROOT, 'src', 'include', 'auto_common.h')
    acs = open(ac).read()
    open(ac, 'w').write(acs.replace('#include "globals.h"\n', ''))
    print('%d variables, %d runtime fixups; %s' % (len(vars_), len(em.fix), '\n'.join(report)))


def main():
    if sys.argv[1:2] == ['plan']:
        items, img, relocs, refs, raw, sizes, vars_, inner = plan()
        print('items %d, variables %d, references inside a variable %d' % (len(items), len(vars_), len(inner)))
        print('relocated slots %d (%s)' % (len(relocs), collections.Counter(v[0] for v in relocs.values())))
        multi = sum(1 for a, rs in refs.items() if len(set(r[2] for r in rs if r[1] == 'lv')) > 1)
        print('addresses read as more than one type: %d' % multi)
        texts = [open(p).read() for p in code_files()]
        decide(vars_, refs, raw, img, relocs, sizes, texts)
        print(collections.Counter(v['kind'] for v in vars_))
        print('scalars with bytes after', sum(1 for v in vars_ if v.get('rest')))
        for v in vars_:
            if v.get('parts'):
                print('  object %08x %s %s %d bytes, %d pieces: %s' % (v['addr'], v['name'] if v.get('name') else '?', v['ctype'], v['size'], len(v['parts']), ' '.join(v['parts'][:6])))
            if v.get('big'):
                print('  object %08x %s: class %s %d > %d' % (v['addr'], v['name'], v['big'][0], v['big'][1], v['size']))
        unnamed = assign_names(vars_, img)
        print('to name by hand: %d' % len(unnamed))
        for v in unnamed:
            b = img[v['addr'] - LO:v['addr'] - LO + min(v['size'], 24)]
            print('  %08x %s %s %d %s aliases=%s' % (v['addr'], v['kind'], v['ctype'], v['size'], b, v.get('aliases')))
    elif sys.argv[1:2] == ['apply']:
        apply()
    else:
        print(__doc__)


if __name__ == '__main__':
    main()
