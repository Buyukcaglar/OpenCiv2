#!/usr/bin/env python3
"""Generate the game's static data as C: src/data/gamedata.h and gamedata.c.

All of .rdata and .data (0x61c000..0x6e6b6c) becomes one packed struct,
`GameData g`, with a field per variable in address order:
  * named globals (re/symbols.tsv) keep their name and type;
  * other variables start at every address the code references or Ghidra
    defined (re/data_refs.tsv, re/data_items.tsv) and run to the next start;
  * every 4-byte slot the original relocation table marks as holding an
    address is a pointer-sized integer (`uptr`); runs of them are arrays.
In the 32-bit build `g` is bound to 0x61c000 and its layout equals the
original (checked at compile time), so the same source drives the original
memory.  The native build defines `g` in gamedata.c, initialized from the
original image with addresses written symbolically.
Also writes re/data_fields.tsv (start end field) for tools/gen_c.py.
Run inside the civ2-dev container.
"""
import bisect
import csv
import os
import re

import pefile
import sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import paths  # noqa: E402  (the game's directory)

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BASE = 0x400000
LO, HI = 0x61c000, 0x6e6b6c        # .rdata start .. .data end (virtual)
SIZES = {'i8': 1, 'u8': 1, 'i16': 2, 'u16': 2, 'i32': 4, 'u32': 4, 'char': 1, 'iptr': 4, 'uptr': 4}


def ident(s):
    s = re.sub(r'\W', '_', s)
    return s if re.match(r'^[A-Za-z_]', s) else '_' + s


def main():
    pe = pefile.PE(paths.game_file('civ2.exe'))
    img = pe.get_memory_mapped_image()
    relocs = set()
    for b in pe.DIRECTORY_ENTRY_BASERELOC:
        for e in b.entries:
            if e.type == 3 and LO <= e.rva + BASE < HI:
                relocs.add(e.rva + BASE)

    # Named globals and their sizes (sizes via the layout checker's parser).
    import sys
    sys.path.insert(0, os.path.join(ROOT, 'tools'))
    import rewrite_fields
    structs = rewrite_fields.parse_structs()
    named = {}
    for r in csv.DictReader(open(os.path.join(ROOT, 're', 'symbols.tsv')), delimiter='\t'):
        if r['kind'] != 'data':
            continue
        a = int(r['addr'], 16)
        t = r['type'].replace(' ', '')
        m = re.match(r'(\w+)(\*?)((?:\[\w+\])*)$', t)
        base, ptr, dims = m.group(1), m.group(2), [int(d, 0) for d in re.findall(r'\[(\w+)\]', m.group(3))]
        size = (4 if ptr else (SIZES.get(base) or structs[base][0])) * rewrite_fields.prod(dims)
        named[a] = (r['name'], r['type'], size, bool(ptr))

    starts = {LO, 0x624000}
    for r in csv.DictReader(open(os.path.join(ROOT, 're', 'data_refs.tsv')), delimiter='\t'):
        starts.add(int(r['addr'], 16))
    items = {}
    for r in csv.DictReader(open(os.path.join(ROOT, 're', 'data_items.tsv')), delimiter='\t'):
        a = int(r['addr'], 16)
        starts.add(a)
        items[a] = r
    starts |= relocs
    for slot in relocs:
        starts.add(slot + 4)
    starts |= set(named)
    for a, (n, t, size, ptr) in named.items():
        starts.add(a + size)
    # Nothing starts inside a named global.
    spans = sorted((a, a + v[2]) for a, v in named.items())
    def inside_named(a):
        i = bisect.bisect_right(spans, (a, 1 << 40)) - 1
        return i >= 0 and spans[i][0] < a < spans[i][1]
    starts = sorted(a for a in starts if LO <= a < HI and not inside_named(a))

    fields = []          # (start, size, kind, name, ctype, dims)
    used_names = set()
    i = 0
    while i < len(starts):
        a = starts[i]
        end = starts[i + 1] if i + 1 < len(starts) else HI
        if a in named:
            n, t, size, ptr = named[a]
            fields.append((a, size, 'named', n, t, None))
            i += 1
            while i < len(starts) and starts[i] < a + size:
                i += 1
            continue
        if a in relocs:
            n = 1
            while a + 4 * n in relocs and (i + n < len(starts) and starts[i + n] == a + 4 * n) \
                    and not any(LO <= x < HI and a + 4 * n == x and x in named for x in [a + 4 * n]):
                n += 1
            name = items.get(a, {}).get('name') or 'PTR_%08x' % a
            fields.append((a, 4 * n, 'ptr', name, 'uptr', n))
            i += n
            continue
        name = items.get(a, {}).get('name') or 'DAT_%08x' % a
        fields.append((a, end - a, 'bytes', name, 'u8', end - a))
        i += 1

    # Unique, valid field names.
    out_fields = []
    for a, size, kind, name, ctype, dims in fields:
        # Unnamed variables: d_<address> (the code refers to them through
        # macros named after Ghidra's labels, which must not clash).
        n = name if kind == 'named' else 'd_%08x' % a
        used_names.add(n)
        out_fields.append((a, size, kind, n, ctype, dims))

    os.makedirs(os.path.join(ROOT, 'src', 'data'), exist_ok=True)
    with open(os.path.join(ROOT, 're', 'data_fields.tsv'), 'w') as f:
        f.write('start\tend\tfield\tkind\n')
        for a, size, kind, n, ctype, dims in out_fields:
            f.write('%08x\t%08x\t%s\t%s\n' % (a, a + size, n, kind))

    # Header: the struct.
    h = ['/* Generated by tools/gen_data.py: the game\'s static data (.rdata + .data)',
         ' * as one struct in original address order.  In the 32-bit build `g` is',
         ' * bound to the original address 0x%08x (layout checked below).  */' % LO,
         '#ifndef CIV2_GAMEDATA_H', '#define CIV2_GAMEDATA_H', '', '#include "civ2types.h"', '',
         '#pragma pack(push, 1)', 'typedef struct GameData {']
    for a, size, kind, n, ctype, dims in out_fields:
        if kind == 'named':
            t = ctype.replace(' ', '')
            m = re.match(r'(\w+\*?)((?:\[\w+\])*)$', t)
            h.append('    %s n_%s%s;  /* %08x: see `%s` */' % (m.group(1), n, m.group(2), a, n))
        elif kind == 'ptr':
            h.append('    uptr %s%s;  /* %08x: address%s */' % (n, '[%d]' % dims if dims > 1 else '', a, 'es' if dims > 1 else ''))
        else:
            h.append('    u8 %s[%d];  /* %08x */' % (n, size, a))
    h += ['} GameData;', '#pragma pack(pop)', '', 'extern GameData g;', '']
    # Named globals are real symbols, which the 32-bit build binds to their
    # original addresses, inside g.  Native builds: the named arrays are views
    # of g at those addresses (the game indexes some out of bounds -- units[-1],
    # units[2048] -- reaching their neighbours there); the other named globals
    # are symbols defined in gamedata.c (macros would clash with field names).
    for a, size, kind, n, ctype, dims in out_fields:
        if kind == 'named':
            if is_array(ctype) and n not in field_names():
                t, d = split_type(n, ctype)
                d = '[]' + d[d.index(']') + 1:]     # no bound: the compiler may not assume indexes within it
                h += ['#ifdef CIV2_NATIVE',
                      '#define %s (*(%s (*)%s)&g.n_%s)' % (n, t, d, n),
                      '#else', 'extern %s;' % named_decl(n, ctype), '#endif']
            else:
                h.append('extern %s;' % named_decl(n, ctype))
    h += ['', '#ifndef CIV2_PTR_INTS', '/* 32-bit layout = original layout. */',
          'typedef char gamedata_size_check[sizeof(GameData) == 0x%x ? 1 : -1];' % (HI - LO)]
    for a, size, kind, n, ctype, dims in out_fields[::97]:
        h.append('typedef char gamedata_off_%08x[__builtin_offsetof(GameData, %s%s) == 0x%x ? 1 : -1];' % (
            a, 'n_' if kind == 'named' else '', n, a - LO))
    h += ['#endif', '', '#endif', '']
    open(os.path.join(ROOT, 'src', 'data', 'gamedata.h'), 'w').write('\n'.join(h))
    write_init(img, out_fields, named)
    print('fields: %d (%d named, %d pointer runs), relocated slots %d' % (
        len(out_fields), sum(1 for f in out_fields if f[2] == 'named'),
        sum(1 for f in out_fields if f[2] == 'ptr'), len(relocs)))


# Named arrays the game indexes one element past their end, at data that in
# the original follows them: units[2048] is the scratch unit unit_make_dummy
# sets up (0x6660f0).  Native builds give these arrays the extra elements, and
# the data there is addressed through them (gen_c.data_location).
OVERHANG = {'units': 1}


_FIELDS = None


def field_names():
    """Struct field names in the type headers (a macro of that name would
    break their accesses)."""
    global _FIELDS
    if _FIELDS is None:
        _FIELDS = set()
        for h in ('civ2types.h', 'civ2classes.h'):
            text = open(os.path.join(ROOT, 'src', 'include', h)).read()
            _FIELDS |= set(re.findall(r'^\s+[\w\s\*]+?\b(\w+)\s*(?:\[[^\]]*\])*\s*;', text, re.M))
    return _FIELDS


def is_array(ctype):
    return '[' in ctype


def split_type(n, ctype):
    """(element type, dimensions) of a named array, overhang included."""
    decl = named_decl(n, ctype)
    i = decl.index(' ' + n + '[')
    return decl[:i], decl[i + len(n) + 1:]


def named_decl(n, ctype):
    t = ctype.replace(' ', '')
    m = re.match(r'(\w+\*?)((?:\[\w+\])*)$', t)
    dims = m.group(2)
    if n in OVERHANG:
        first = re.match(r'\[(\w+)\]', dims)
        dims = '[%s + %d]' % (first.group(1), OVERHANG[n]) + dims[first.end():]
    return '%s %s%s' % (m.group(1), n, dims)


def write_init(img, out_fields, named):
    """gamedata.c (native builds): fill g and the named globals at startup."""
    sys_path = os.path.join(ROOT, 'tools')
    import sys
    sys.path.insert(0, sys_path)
    import gen_c
    raw_end = {0x61c000: 0x61c000 + 0x8000, 0x624000: 0x624000 + 0x18800}   # initialized bytes per section
    def initialized(a):
        return 0x61c000 <= a < 0x624000 or 0x624000 <= a < 0x63c800
    funcs = {}
    for r in csv.DictReader(open(os.path.join(ROOT, 're', 'functions.tsv')), delimiter='\t'):
        if re.match(r'^[A-Za-z_]\w*$', r['name']):
            funcs[int(r['entry'], 16)] = r['name']
    # Functions native builds do not have: the C runtime's own (replaced by
    # the platform's) and exception-unwind funclets (inlined at their call
    # sites; the tables that point at them are the runtime's).
    status = {r['name']: r['status'] for r in csv.DictReader(open(os.path.join(ROOT, 're', 'manifest.tsv')),
                                                             delimiter='\t')}
    absent = {n for n, st in status.items() if st in ('ehfunclet', 'crt', 'crt-manual', 'asm')}
    last = 0x63c800                       # end of initialized .data (bss follows)
    img_lo, img_hi = LO, last
    blob = img[img_lo - BASE:img_hi - BASE]
    c = ['/* Generated by tools/gen_data.py: initial contents of the game data for',
         ' * native builds (the 32-bit build uses the original memory directly). */',
         '#include <string.h>', '#include "auto_common.h"', '',
         'GameData g;']
    for a, size, kind, n, ctype, dims in out_fields:
        if kind == 'named' and not (is_array(ctype) and n not in field_names()):
            c.append('%s;' % named_decl(n, ctype))
    # The image as a string literal: far cheaper for compilers than a list.
    c += ['', 'static const char image[0x%x + 1] =' % len(blob)]
    for i in range(0, len(blob), 32):
        c.append('    "' + ''.join('\\x%02x' % b for b in blob[i:i + 32]) + '"')
    c += [';', '', '#define IMG(a) ((const unsigned char *)image + ((a) - 0x%xu))' % img_lo, '',
          'void gamedata_init(void)', '{']
    run_start = None
    def flush(end):
        nonlocal run_start
        if run_start is not None:
            a0, f0 = run_start
            hi = min(end, last)
            if hi > a0:
                c.append('    memcpy(%s, IMG(0x%08xu), 0x%x);' % (f0, a0, hi - a0))
            run_start = None
    for a, size, kind, n, ctype, dims in out_fields:
        if kind == 'named':
            flush(a)
            if a < last and any(img[a - BASE:min(a + size, last) - BASE]):
                c.append('    memcpy(&%s, IMG(0x%08xu), 0x%x);' % (n, a, min(size, last - a)))
            continue
        if kind == 'ptr':
            flush(a)
            for k in range(dims):
                slot = a + 4 * k
                v = int.from_bytes(img[slot - BASE:slot - BASE + 4], 'little')
                lhs = 'g.%s%s' % (n, '[%d]' % k if dims > 1 else '')
                if v in funcs and funcs[v] in absent:
                    c.append('    %s = 0;   /* %s: not in native builds */' % (lhs, funcs[v]))
                elif v in funcs:
                    c.append('    %s = (uptr)&%s;' % (lhs, funcs[v]))
                elif LO <= v < HI:
                    c.append('    %s = (uptr)%s;' % (lhs, gen_c.data_location(v)))
                elif v == 0:
                    c.append('    %s = 0;' % lhs)
                else:
                    c.append('    %s = 0x%08xu;   /* not a known function or data */' % (lhs, v))
            continue
        if run_start is None and a < last:
            run_start = (a, '&g.%s' % n)
    flush(HI)
    c += ['}', '']
    open(os.path.join(ROOT, 'src', 'data', 'gamedata.c'), 'w').write('\n'.join(c))


if __name__ == '__main__':
    main()
