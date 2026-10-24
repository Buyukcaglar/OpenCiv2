#!/usr/bin/env python3
"""Step 6 check: the machine code of each game function in the C++ build
against the C build it replaces (the same gcc back end, so a conversion that
keeps the meaning gives the same instructions).

    cxx_compare.py BASE_OBJDIR CXX_OBJDIR [FUNCTION]

BASE_OBJDIR: objects of the C build (e.g. a worktree of the last C commit:
run/cbase/build/native/linux32), CXX_OBJDIR: build/native/linux32-cxx.
Lists the functions whose code differs; with FUNCTION, shows the difference.
Addresses are ignored, as are offsets into .text/.rodata (layout, not code),
which stack slot holds which local and the frame size.
"""
import difflib
import glob
import os
import re
import subprocess
import sys

FUNC = re.compile(r'^[0-9a-f]+ <(.+)>:$')


def strip_params(name):
    """city_recalc(int, int) -> city_recalc; call_untyped<..>(..) -> call_untyped"""
    out, depth = [], 0
    for c in name:
        if c in '(<':
            depth += 1
        elif c in ')>':
            depth -= 1
        elif depth == 0:
            out.append(c)
    return ''.join(out).strip()


def normalize(line):
    line = re.sub(r'<([^>]*)>', lambda m: '<%s>' % strip_params(re.sub(r'\+0x[0-9a-f]+$', '', m.group(1))), line)
    line = re.sub(r'\b[0-9a-f]+ <', '<', line)
    line = re.sub(r'\.(text|rodata|data|bss)[\w.]*(\+0x[0-9a-f]+)?', r'.\1', line)
    return line


def functions(obj):
    out = subprocess.run(['objdump', '-d', '-r', '-C', '--no-show-raw-insn', obj],
                         capture_output=True, text=True).stdout
    funcs, cur = {}, None
    for line in out.split('\n'):
        m = FUNC.match(line)
        if m:
            cur = strip_params(m.group(1))
            funcs[cur] = [] if cur not in funcs else None     # None: a name seen twice
            continue
        if cur is None or funcs.get(cur) is None or not line.strip():
            continue
        m = re.match(r'\s*[0-9a-f]+:\s*(.*)$', line)
        if m:
            text = m.group(1).strip()
            if text.startswith('R_386') or text.startswith('R_'):
                text = re.sub(r'(R_\w+)\s+(.*)', lambda r: r.group(1) + ' ' + strip_params(r.group(2)), text)
            funcs[cur].append(normalize(re.sub(r'\s+', ' ', text)))
    return {k: canon_stack(v) for k, v in funcs.items() if v is not None}


def canon_stack(lines):
    """Stack slots renamed in order of first use, the frame size dropped: the
    same code with its locals in other slots compares equal."""
    slots = {}

    def slot(m):
        k = m.group(1) or '0'
        if k not in slots:
            slots[k] = 's%d' % len(slots)
        return '[%s]' % slots[k]
    out = []
    for line in lines:
        line = re.sub(r'(?:(-?0x[0-9a-f]+))?\(%esp\)', slot, line)
        line = re.sub(r'^(sub|add) \$0x[0-9a-f]+,%esp$', r'\1 $FRAME,%esp', line)
        out.append(line)
    return out


def main():
    if len(sys.argv) < 3:
        print(__doc__)
        return 1
    base_dir, cxx_dir = sys.argv[1:3]
    only = sys.argv[3] if len(sys.argv) > 3 else None
    same = differ = 0
    changed = []
    for cobj in sorted(glob.glob(os.path.join(cxx_dir, '*.o'))):
        if not re.match(r'(src_(auto|game|data|native)_|build_native_gen_)', os.path.basename(cobj)):
            continue
        # the same source as .c in an older build
        bobj = next((b for b in (os.path.join(base_dir, os.path.basename(cobj)),
                                  os.path.join(base_dir, os.path.basename(cobj).replace('.cpp.o', '.c.o')))
                     if os.path.exists(b)), None)
        if not bobj:
            continue
        base, cxx = functions(bobj), functions(cobj)
        for name in sorted(base):
            if name not in cxx:
                continue
            if only and name != only:
                continue
            if base[name] == cxx[name]:
                same += 1
                continue
            differ += 1
            changed.append((os.path.basename(cobj), name))
            if only:
                sys.stdout.writelines(difflib.unified_diff([l + '\n' for l in base[name]], [l + '\n' for l in cxx[name]],
                                                           'c', 'c++', n=2))
    if not only:
        for o, n in changed:
            print('%s\t%s' % (o, n))
    print('%d functions the same, %d differ' % (same, differ), file=sys.stderr)
    return 0


if __name__ == '__main__':
    sys.exit(main())
