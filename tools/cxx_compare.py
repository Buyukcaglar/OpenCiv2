#!/usr/bin/env python3
"""Step 6 check: the machine code of each game function in the C++ build
against the C build it replaces (the same gcc back end, so a conversion that
keeps the meaning gives the same instructions).

    cxx_compare.py [--map re/methods.tsv] BASE_OBJDIR CXX_OBJDIR [FUNCTION]

BASE_OBJDIR: objects of the C build (e.g. a worktree of the last C commit:
run/cbase/build/native/linux32), CXX_OBJDIR: build/native/linux32-cxx.
Lists the functions whose code differs; with FUNCTION, shows the difference.
Addresses are ignored, as are offsets into .text/.rodata (layout, not code),
which stack slot holds which local and the frame size.
--map: functions that became member functions (tools/cxx_methods.py) are
compared, and their calls matched, under their old free names
(`Class::member` -> old name, from the plan's old/class/member columns).
"""
import difflib
import glob
import os
import re
import subprocess
import sys

FUNC = re.compile(r'^[0-9a-f]+ <(.+)>:$')
RENAMED = {}        # Class::member -> free name (--map)


def load_map(path):
    import csv
    lines = [l for l in open(path) if not l.startswith('#')]
    for r in csv.DictReader(lines, delimiter='\t'):
        if r.get('member'):
            RENAMED['%s::%s' % (r['class'], r['member'])] = r['old']


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
    name = ''.join(out).strip()
    return RENAMED.get(name, name)


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
    return {k: canon_stack(temp_regs(fold_push(strip_padding(v)))) for k, v in funcs.items() if v is not None}


def strip_padding(lines):
    """Padding after the last instruction (g++ aligns member functions to 2
    bytes: a function before one ends with a nop)."""
    while lines and re.match(r'(nop\w*|xchg %ax,%ax|lea 0x0\(%e[a-z]+(,%eiz,1)?\),%e[a-z]+)\b', lines[-1]):
        lines = lines[:-1]
    return lines


def temp_regs(lines):
    """A register loaded, computed on and pushed within a few instructions,
    and not read after the push, is a temporary: which one it is does not
    matter, so it is renamed %tmp.  No jump or call may lie in between."""
    out = list(lines)
    for i, line in enumerate(out):
        m = re.match(r'push (%e[a-d]x|%e[sd]i)$', line)
        if not m:
            continue
        reg = m.group(1)
        nxt = out[i + 1] if i + 1 < len(out) else ''
        if reads_reg(nxt, reg):
            continue
        j = i - 1
        while j >= 0 and i - j <= 5:
            t = out[j]
            if re.match(r'(call|j\w+|ret|leave)\b', t) or (re.match(r'(push|pop)\b', t) and reg in t):
                j = -1
                break
            d = re.match(r'(mov\w*|lea) (.+),(%\w+)( @.*)?$', t)
            if d and d.group(3) == reg and reg not in d.group(2):
                break
            j -= 1
        if j < 0 or i - j > 5:
            continue
        for k in range(j, i + 1):
            out[k] = out[k].replace(reg, '%tmp')
    return out


def reads_reg(instr, reg):
    """Whether instr reads reg (a mov/lea/movzx... into reg only writes it)."""
    m = re.match(r'(mov\w*|lea) (.+),(%\w+)( @.*)?$', instr)
    if m and m.group(3) == reg:
        return reg in m.group(2)
    return reg in instr


def fold_push(lines):
    """mov SRC,%reg ... push %reg -> ... push SRC when the instructions
    between touch neither %reg nor SRC (no call or jump either) and nothing
    reads %reg after the push: -O0 loads a value it converts (an integer cast
    of a pointer) into a register first, and pushes one it does not straight
    from memory.  Relocations are attached to their instruction first."""
    merged = []
    for line in lines:
        if line.startswith('R_') and merged:
            merged[-1] += ' @' + line
        else:
            merged.append(line)
    out = []
    skip = set()
    for i, line in enumerate(merged):
        if i in skip:
            continue
        m = re.match(r'mov (.+?),(%e[a-d]x)( @.*)?$', line)
        if m:
            src, reg = m.group(1), m.group(2)
            j = i + 1
            while j < len(merged) and j - i < 6:
                t = merged[j]
                if t == 'push ' + reg:
                    break
                if (reg in t or (not src.startswith('$') and src in t)
                        or re.match(r'(call|j\w+|ret|push|pop) ', t + ' ')):
                    j = len(merged)
                    break
                j += 1
            if j < len(merged) and merged[j] == 'push ' + reg:
                nxt = merged[j + 1] if j + 1 < len(merged) else ''
                if not reads_reg(nxt, reg):
                    out.extend(merged[i + 1:j])
                    out.append('push ' + src + (m.group(3) or ''))
                    skip.update(range(i + 1, j + 1))
                    continue
        out.append(line)
    return out

def canon_stack(lines):
    """Stack slots renamed in order of first use, stack adjustments dropped:
    the same code with its locals in other slots compares equal."""
    slots = {}

    def slot(m):
        k = m.group(1) or '0'
        if k not in slots:
            slots[k] = 's%d' % len(slots)
        return '[%s]' % slots[k]
    out = []
    for line in lines:
        line = re.sub(r'(?:(-?0x[0-9a-f]+))?\(%esp\)', slot, line)
        if re.match(r'^(sub|add) \$(0x[0-9a-f]+|FRAME),%esp$', line):
            continue        # stack adjustments: where they fall is no difference
        out.append(line)
    return out


def main():
    if len(sys.argv) > 2 and sys.argv[1] == '--map':
        load_map(sys.argv[2])
        del sys.argv[1:3]
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
