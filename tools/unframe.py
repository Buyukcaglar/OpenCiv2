#!/usr/bin/env python3
"""Turn the emulated stack frames into ordinary locals.

The translation kept each function's locals at their original stack
offsets: `i8 frame_[FRAME_OFF(n)]` and per local a macro
`#define name (*(T *)(frame_ + FRAME_OFF(off)))`.  Each such local becomes
a declaration `T name;` (`T name[k];` for an array) where frame_ was
declared, and its #define/#undef lines go.  Run once (src/auto); locals
that share storage on purpose are reported and left alone.

    unframe.py FILES...            (src/auto: per function marker)
    unframe.py --linear FILES...   (src/game)
"""
import re
import sys

MACRO = re.compile(r'^#define (\w+) \(\*\((.+?) (\*|\(\*\)\[(\d+)\])\)\(frame_ \+ FRAME_OFF\((\d+)\)\)\)\n', re.M)
FRAME = re.compile(r'^(\s*)i8 frame_\[FRAME_OFF\((\d+)\)\] __attribute__\(\(aligned\(8\)\)\);[^\n]*\n', re.M)
SIZES = {'int': 4, 'i32': 4, 'uint': 4, 'u32': 4, 'char': 1, 'i8': 1, 'u8': 1, 'byte': 1, 'short': 2,
         'i16': 2, 'u16': 2, 'tagRECT': 16, 'tagPOINT': 8}
MARK = re.compile(r'(?m)^(?=/\* [0-9a-f]{8}[ :])')


def decl(t, name, count):
    m = re.match(r'^(.*?)\s*((?:\*\s*)*)$', t)
    base, stars = m.group(1), m.group(2).replace(' ', '')
    return '%s %s%s%s;' % (base, stars, name, '[%s]' % count if count else '')


def convert(region):
    locs = [(int(m.group(5)), m.group(1), m.group(2), m.group(4)) for m in MACRO.finditer(region)]
    frames = list(FRAME.finditer(region))
    if not locs and not frames:
        return region, 0
    if len(frames) != 1:
        raise SystemExit('frame declarations: %d in %s' % (len(frames), region[:60]))
    names = {n for _, n, _, _ in locs}
    if len(names) != len(locs):
        raise SystemExit('a name twice in %s' % region[:60])
    region = MACRO.sub('', region)
    region = re.sub(r'(?m)^#undef (%s)\n' % '|'.join(map(re.escape, names)), '', region) if names else region
    fm = FRAME.search(region)
    indent = fm.group(1)
    lines = ''.join('%s%s\n' % (indent, decl(t, n, c)) for _, n, t, c in sorted(locs))
    region = region[:fm.start()] + lines + region[fm.end():]
    assert not re.search(r'\bframe_\b', region), region[:200]
    return region, len(locs)


def convert_linear(text, sizes):
    """Hand-written files (no per-function markers): a frame declaration
    takes the frame macros defined, and not yet #undef'd, before it."""
    out, active, total = [], {}, 0
    for ln in text.splitlines(keepends=True):
        m = MACRO.match(ln)
        if m:
            active[m.group(1)] = (int(m.group(5)), m.group(1), m.group(2), m.group(4))
            continue
        u = re.match(r'^#undef (\w+)\n', ln)
        if u and u.group(1) in active:
            del active[u.group(1)]
            continue
        f = FRAME.match(ln)
        if f:
            locs = sorted(active.values())
            for a, b in zip(locs, locs[1:]):
                if b[0] < a[0] + sizes.get(a[2], 1) * int(a[3] or 1):
                    print('overlap: %s and %s' % (a[1], b[1]))
            out.append(''.join('%s%s\n' % (f.group(1), decl(t, n, c)) for _, n, t, c in locs))
            total += len(locs)
            continue
        out.append(ln)
    return ''.join(out), total


def main():
    total = 0
    linear = sys.argv[1:2] == ['--linear']
    for path in sys.argv[1 + linear:]:
        text = open(path).read()
        if linear:
            new, n = convert_linear(text, SIZES)
            total += n
            if new != text:
                open(path, 'w').write(new)
            continue
        parts = MARK.split(text)
        for i in range(1, len(parts)):
            parts[i], n = convert(parts[i])
            total += n
        new = ''.join(parts)
        if new != text:
            open(path, 'w').write(new)
    print('%d locals' % total)


if __name__ == '__main__':
    main()
