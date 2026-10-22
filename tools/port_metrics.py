#!/usr/bin/env python3
"""How far the source is from compiling as a portable 64-bit program.

Counts, over src/auto/blk_*.c and src/game/*.c (game code; the C runtime is
replaced by the platform's own in the native port):
  addr_globals  references to globals by original address (DAT_xxx, s_xxx,
                PTR_xxx, GLOBAL(...), absolute casts)
  raw_offsets   field accesses through integer/untyped pointer arithmetic,
                e.g. *(short *)((int)p + 0x12) or (&DAT_x)[i * 0x20]
  w64_*         diagnostics of a 64-bit compile (x86_64-w64-mingw32 -fsyntax-only):
                pointer<->int casts of different size, other warnings, errors
Writes re/port_metrics.tsv (per function) and prints totals.
Run inside the civ2-dev container.
"""
import collections
import glob
import os
import re
import subprocess

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
FUNC_MARK = re.compile(r'^/\* ([0-9a-f]{8}) (\S+)', re.M)
ADDR_GLOBAL = re.compile(r'\b(_?(?:DAT|PTR|LAB|BYTE|WORD|DWORD)_[0-9a-f]{8}|_?[su]_\w*_[0-9a-f]{8}|GLOBAL\s*\(|\(\*\([^()]*\*\)0x00[4-6][0-9a-f]{5}\))')
RAW_OFFSET = re.compile(r'\(\(int\)[A-Za-z_]\w*\s*\+\s*(0x[0-9a-f]+|\d+)\)|\(&_?DAT_[0-9a-f]{8}\)\s*\[[^\]]*\*\s*0x[0-9a-f]+\]|\(&_?DAT_[0-9a-f]{8}\s*\+')


def main():
    files = sorted(glob.glob(os.path.join(ROOT, 'src', 'auto', 'blk_*.c')) +
                   glob.glob(os.path.join(ROOT, 'src', 'game', '*.c')))
    per = collections.defaultdict(lambda: collections.Counter())
    absolute_macros = set()
    for hp in glob.glob(os.path.join(ROOT, 'src', 'auto', '*.h')) + files:
        for m in re.finditer(r'^#define (\w+) .*\b0x00[4-6][0-9a-f]{5}\)*\s*$', open(hp).read(), re.M):
            absolute_macros.add(m.group(1))
    totals = collections.Counter()
    for path in files:
        text = open(path).read()
        marks = [(m.start(), m.group(1), m.group(2)) for m in FUNC_MARK.finditer(text)]
        # Only active code: skip #if 0 blocks.
        active = re.sub(r'^#if 0\n.*?^#endif\n', lambda m: '\n' * m.group(0).count('\n'), text, flags=re.M | re.S)
        bounds = marks + [(len(text), None, None)]
        for (s, addr, status), (e, _, _) in zip(bounds, bounds[1:]):
            chunk = active[s:e]
            c = per[addr]
            # References that still resolve to an absolute address: macros
            # defined as a cast of a constant, and GLOBAL(...) in hand-written code.
            for name in re.findall(r'\b([A-Za-z_]\w*)\b', chunk):
                if name in absolute_macros:
                    c['addr_globals'] += 1
            c['addr_globals'] += len(re.findall(r'\(\*\([^()]*\*\)0x00[4-6][0-9a-f]{5}\)', chunk))
            c['addr_globals'] += chunk.count('GLOBAL(')
            c['raw_offsets'] += len(RAW_OFFSET.findall(chunk))
        r = subprocess.run(['x86_64-w64-mingw32-gcc', '-fsyntax-only', '-std=gnu89', '-include', 'native.h',
                            '-Wint-to-pointer-cast', '-Wpointer-to-int-cast', '-Wint-conversion', '-fmax-errors=0',
                            '-I', os.path.join(ROOT, 'src', 'include'), '-I', os.path.join(ROOT, 'src', 'auto'),
                            '-I', os.path.join(ROOT, 'tools'), path], capture_output=True, text=True)
        lines = text.count('\n')
        starts = [(text.count('\n', 0, s) + 1, addr) for s, addr, _ in marks]
        for m in re.finditer(r'^%s:(\d+):\d+: (warning|error): (.*)$' % re.escape(path), r.stderr, re.M):
            ln, kind, msg = int(m.group(1)), m.group(2), m.group(3)
            owner = None
            for l, a in starts:
                if l <= ln:
                    owner = a
            if owner is None:
                continue
            if ('cast' in msg and 'different size' in msg) or 'Wint-conversion' in msg:
                per[owner]['w64_ptrcast'] += 1
            elif kind == 'error':
                per[owner]['w64_error'] += 1
            else:
                per[owner]['w64_warning'] += 1
    with open(os.path.join(ROOT, 're', 'port_metrics.tsv'), 'w') as f:
        keys = ['addr_globals', 'raw_offsets', 'w64_ptrcast', 'w64_error', 'w64_warning']
        f.write('addr\t' + '\t'.join(keys) + '\n')
        for a in sorted(per):
            f.write(a + '\t' + '\t'.join(str(per[a][k]) for k in keys) + '\n')
            totals.update(per[a])
    clean = sum(1 for a in per if not any(per[a].values()))
    print('functions: %d, fully portable: %d' % (len(per), clean))
    for k in ['addr_globals', 'raw_offsets', 'w64_ptrcast', 'w64_error', 'w64_warning']:
        print('  %-13s %7d' % (k, totals[k]))


if __name__ == '__main__':
    main()
