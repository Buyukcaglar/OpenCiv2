#!/usr/bin/env python3
"""The game's functions and how to call them, for the unit tests' recorder
(tests/unit_record.c): one line per function of src/auto and src/game,

    symbol  file  return  words

symbol: the ELF symbol (mangled); return: v (void), i (in eax/edx), b and h
(8 and 16 bits in al, ax), f (on the x87 stack); words: a letter per 32-bit argument word, `this` first for a
member function: p (a pointer or an integer that may hold one: classified by
value when recorded), i (an integer).  Functions the recorder cannot call
(arguments by value wider than a word or structs, varargs, struct returns)
are left out.  Signatures from gdb (the program's debugging information),
symbols from nm.  Runs in the container:

    python3 tools/unit_sigs.py build/civ2-linux32rec > build/native/gen/unit_sigs.tsv
    python3 tools/unit_sigs.py --statics build/civ2-linux32rec
"""
import collections
import re
import subprocess
import sys

INTS = {'int', 'unsigned int', 'uint', 'i32', 'u32', 'i16', 'u16', 'i8', 'u8', 'byte', 'char', 'unsigned char',
        'signed char', 'short', 'unsigned short', 'ushort', 'uchar', 'ghidra_bool', 'BOOL', 'LONG', 'DWORD', 'WORD',
        'UINT', 'long', 'unsigned long', 'ulong', 'bool', 'WPARAM', 'LRESULT', 'MMRESULT', 'SIZE_T', 'undefined4',
        'undefined2', 'undefined1', 'COLORREF', 'ATOM'}
WIDE = {'i64', 'u64', 'long long', 'unsigned long long', 'ulonglong', 'longlong', 'LONGLONG'}
FLOATS = {'float', 'double', 'long double', 'float10'}
POINTERISH = {'iptr', 'uptr', 'LPARAM'}
BYTES = {'i8', 'u8', 'byte', 'char', 'unsigned char', 'signed char', 'uchar', 'ghidra_bool', 'bool', 'undefined1'}
SHORTS = {'i16', 'u16', 'short', 'unsigned short', 'ushort', 'WORD', 'undefined2'}


def gdb(exe, cmds):
    script = '\n'.join(cmds) + '\n'
    path = '/tmp/unit_sigs.gdb'
    open(path, 'w').write(script)
    return subprocess.run(['gdb', '-batch', '-x', path, exe], capture_output=True, text=True).stdout


def split_params(s):
    out, depth, cur = [], 0, ''
    for ch in s:
        if ch in '(<[':
            depth += 1
        elif ch in ')>]':
            depth -= 1
        if ch == ',' and depth == 0:
            out.append(cur.strip())
            cur = ''
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


def statics(exe):
    """--statics: the game's functions (and the C runtime's) that use
    variables outside the game's data (statics of src/game, the runtime's
    tables): their state is not in a case, so the ones that change it are
    left out of the recording (tests/unit_record.c `outside`)."""
    h = subprocess.run(['objdump', '-h', exe], capture_output=True, text=True).stdout
    ranges = [(int(m.group(3), 16), int(m.group(3), 16) + int(m.group(2), 16))
              for m in re.finditer(r'^\s*\d+\s+(\.data|\.bss)\s+([0-9a-f]+)\s+([0-9a-f]+)', h, re.M)]
    names = {}
    for line in subprocess.run(['nm', exe], capture_output=True, text=True).stdout.splitlines():
        p = line.split()
        if len(p) == 3:
            names[int(p[0], 16)] = p[2]
    begin = [a for a, n in names.items() if n == 'plat_text_begin'][0]
    cur = None
    for line in subprocess.run(['objdump', '-d', '--no-show-raw-insn', exe], capture_output=True, text=True).stdout.splitlines():
        m = re.match(r'^([0-9a-f]+) <(.*)>:$', line)
        if m:
            cur = m.group(2) if int(m.group(1), 16) < begin else None
            continue
        if cur and 'call' not in line:
            for v in re.findall(r'0x([0-9a-f]{7,8})', line):
                v = int(v, 16)
                if any(a <= v < b for a, b in ranges):
                    print('%s\t%s' % (cur, names.get(v, hex(v))))


def main():
    if sys.argv[1] == '--statics':
        return statics(sys.argv[2])
    exe = sys.argv[1]
    text = gdb(exe, ['info functions'])
    funcs = []          # (file, qualified name, return type, [param types], static)
    cur = None
    for line in text.splitlines():
        m = re.match(r'^File (.*):$', line)
        if m:
            cur = m.group(1)
            continue
        if line.startswith('Non-debugging'):
            cur = None
        if not cur or not re.search(r'/src/(auto|game)/', cur):
            continue
        m = re.match(r'^\d+:\s+(.*);$', line)
        if not m:
            continue
        sig = m.group(1)
        # the parameter list: the last balanced (...) group
        depth, i = 0, len(sig) - 1
        assert sig[i] == ')'
        while i >= 0:
            if sig[i] == ')':
                depth += 1
            elif sig[i] == '(':
                depth -= 1
                if depth == 0:
                    break
            i -= 1
        params, head = sig[i + 1:-1], sig[:i]
        m = re.match(r'^(.*?)([\w:~]+)$', head)
        if not m:
            continue
        ret, name = m.group(1).strip(), m.group(2)
        static = ret.startswith('static ')
        if static:
            ret = ret[7:]
        funcs.append((cur, name, ret, [] if params.strip() in ('', 'void') else split_params(params), static))
    # typedefs and classes: resolved by gdb
    unknown = set()
    for f in funcs:
        for t in f[3] + [f[2]]:
            t = t.replace('const ', '').strip()
            if t and '*' not in t and '&' not in t and '(' not in t and t not in INTS | WIDE | FLOATS | POINTERISH | {'void'}:
                unknown.add(t)
    resolved = {}
    sizes = {}
    if unknown:
        unknown = sorted(unknown)
        out = gdb(exe, ['echo @@%s\\n\nptype %s\nprint sizeof(%s)' % (t, t, t) for t in unknown])
        for block in out.split('@@')[1:]:
            t, _, rest = block.partition('\n')
            m = re.search(r'^type = (.*)$', rest, re.M)
            s = re.search(r'^\$\d+ = (\d+)', rest, re.M)
            first = m.group(1).strip() if m else ''
            size = int(s.group(1)) if s else 0
            sizes[t] = size
            if first.endswith('*') or first.endswith('*)') or '(*)' in first:
                resolved[t] = 'p'
            elif re.match(r'^(struct|class|union)\b', first) and not first.endswith('*'):
                resolved[t] = 'S'
            elif first.startswith('enum') or size in (1, 2, 4):
                resolved[t] = 'i' if size <= 4 else 'x'
            elif first in FLOATS:
                resolved[t] = 'f'
            elif size == 8:
                resolved[t] = 'w'
            else:
                resolved[t] = 'x'

    def kind(t):
        t = t.replace('const ', '').strip()
        if '*' in t or '&' in t or '(' in t or t in POINTERISH:
            return 'p'
        if t in INTS:
            return 'i'
        if t in WIDE:
            return 'w'
        if t in FLOATS:
            return 'd' if t == 'double' else ('f' if t == 'float' else 'x')
        return resolved.get(t, 'x')

    # symbols: mangled and demangled, in the same order
    nm = subprocess.run(['nm', '--defined-only', exe], capture_output=True, text=True).stdout.splitlines()
    nmc = subprocess.run(['nm', '-C', '--defined-only', exe], capture_output=True, text=True).stdout.splitlines()
    by_qual = collections.defaultdict(list)
    for a, b in zip(nm, nmc):
        pa, pb = a.split(' ', 2), b.split(' ', 2)
        if len(pa) < 3 or pa[1] not in 'Tt':
            continue
        qual = pb[2]
        if '(' in qual:
            qual = qual[:qual.index('(')]
        by_qual[qual].append(pa[2])
    names = collections.Counter(f[1] for f in funcs)
    out = []
    for file, name, ret, params, static in funcs:
        syms = by_qual.get(name, [])
        if names[name] != 1 or len(syms) != 1:
            continue                        # static functions of the same name in several files
        words = ''
        if '::' in name and not static:
            words = 'p'                     # this
        ok = True
        for p in params:
            if p == '...':
                ok = False
                break
            k = kind(p)
            if k in 'pi':
                words += k
            elif k == 'f':
                words += 'i'
            elif k in 'wd':
                words += 'ii'
            else:
                ok = False
        rk = kind(ret) if ret != 'void' else 'v'
        rt = ret.replace('const ', '').strip()
        if rk == 'i' and (rt in BYTES or sizes.get(rt) == 1):
            r = 'b'                         # the rest of eax is not set
        elif rk == 'i' and (rt in SHORTS or sizes.get(rt) == 2):
            r = 'h'
        elif rk in 'pi' or rk == 'w':
            r = 'i'
        elif rk == 'v':
            r = 'v'
        elif rk in 'fd' or ret.replace('const ', '').strip() in FLOATS:
            r = 'f'
        else:
            ok = False                      # a struct returned by value
        if ok:
            out.append('%s\t%s\t%s\t%s' % (syms[0], file.split('/src/', 1)[1], r, words or '-'))
    sys.stdout.write('\n'.join(out) + '\n')
    sys.stderr.write('%d of %d functions callable\n' % (len(out), len(funcs)))


if __name__ == '__main__':
    main()
