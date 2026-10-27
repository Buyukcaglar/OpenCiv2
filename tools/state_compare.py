#!/usr/bin/env python3
"""Check a state-grouping step (tools/state_records.py) on two builds:

    state_compare.py BASE_EXE NEW_EXE [SPEC [RENAMES]]

* the machine code of every function is the same, its absolute addresses
  taken relative to their sections (the sections move when the symbol
  tables change size: every address the code holds is compared that way);
* the data sections of the game's data object (gamedata.cpp, next to
  BASE_EXE and in build/native/linux32) hold the same bytes;
* every data symbol of BASE is in NEW at the same section offset with the same
  size, or it was folded into a record of SPEC (re/state_records.txt): the
  record's instance then starts where its first member was and spans exactly
  its members (each member's offset is a static_assert in gamedata.cpp).
Exit status 1 on any difference.
"""
import re
import subprocess
import sys


def sections(exe):
    out = subprocess.run(['readelf', '-SW', exe], capture_output=True, text=True).stdout
    secs = {}
    for m in re.finditer(r'\]\s+(\S+)\s+(\w+)\s+([0-9a-f]+)\s+([0-9a-f]+)\s+([0-9a-f]+)', out):
        name, typ, addr, off, size = m.groups()
        secs[name] = (typ, int(addr, 16), int(off, 16), int(size, 16))
    return secs


def content(exe, sec):
    typ, addr, off, size = sec
    if typ == 'NOBITS':
        return ('nobits', size)
    with open(exe, 'rb') as f:
        f.seek(off)
        return f.read(size)


def symbols(exe):
    out = subprocess.run(['nm', '-S', '--defined-only', exe], capture_output=True, text=True).stdout
    syms = {}
    for line in out.splitlines():
        p = line.split()
        if len(p) == 4 and p[2] in 'bBdDrR':
            syms[p[3]] = (int(p[0], 16), int(p[1], 16))
    return syms


def spec(path):
    recs, cur = {}, None
    for line in open(path):
        if line.startswith('record '):
            cur = line.split()[2]
            recs[cur] = []
        elif line.strip() == 'end':
            cur = None
        elif cur and line.strip() and not line.lstrip().startswith('#'):
            recs[cur].append(line.split()[0])
    return recs


SEC_RANGES = {}


def secmap(exe):
    out = []
    for name, (typ, addr, off, size) in sections(exe).items():
        if addr and size:
            out.append((addr, addr + size, name))
    return sorted(out)


def symtab(exe):
    """Sorted (address, name) of the defined symbols with a size."""
    out = subprocess.run(['nm', '-S', '--defined-only', exe], capture_output=True, text=True).stdout
    syms = []
    for line in out.splitlines():
        p = line.split()
        if len(p) == 4 and int(p[1], 16) > 0:
            syms.append((int(p[0], 16), p[3], int(p[1], 16)))
    import collections
    n = collections.Counter(name for _, name, _ in syms)
    return sorted(x for x in syms if n[x[1]] == 1)     # local names defined twice anchor nothing


def disasm(exe, fold=None):
    """Functions of .text, each a list of instructions with every absolute
    address written as symbol+offset (the sections move when the symbol
    tables change size); FOLD: name -> (record, offset) for the base build,
    so that a folded variable reads as its record's member."""
    import bisect
    syms = symtab(exe)
    secs = secmap(exe)
    addrs = [a for a, _, _ in syms]
    lo, hi = syms[0][0], syms[-1][0] + 0x1000000

    code_data = [(l, h) for l, h, n in secs if re.match(r'\.(text|rodata|data|bss|plt|got|init|fini|eh_frame)', n)]

    def rel(m):
        v = int(m.group(1), 16)
        if not lo <= v < hi or not any(l <= v < h for l, h in code_data):
            return m.group(0)       # a constant, not an address of code or data
        i = bisect.bisect_right(addrs, v) - 1
        if i < 0:
            return m.group(0)
        a, name, size = syms[i]
        if v >= a + size:
            # unnamed (string literals...): from the next symbol of its
            # section, or from the section's end
            sec = [(l, h, n) for l, h, n in secs if l <= v < h]
            if name == '_ZL6layout':
                # the layout table (gen/layout.cpp) shrinks as variables are
                # folded; what follows it is anchored at its end
                return '%s_end%+#x' % (name, v - (a + size))
            if i + 1 < len(syms) and sec and syms[i + 1][0] < sec[0][1]:
                a, name, size = syms[i + 1]
            elif sec:
                a, name = sec[0][1], sec[0][2] + '_end'
        off = v - a
        if fold and name in fold:
            name, d = fold[name]
            off += d
        return '%s%+#x' % (name, off)
    out = subprocess.run(['objdump', '-d', '--no-show-raw-insn', '-j', '.text', exe],
                         capture_output=True, text=True).stdout
    funcs, places, cur = {}, {}, None
    for line in out.splitlines():
        m = re.match(r'^([0-9a-f]+) <(.+)>:$', line)
        if m:
            cur = funcs.setdefault(m.group(2), [])
            last = m.group(2)
            places[m.group(2)] = (int(m.group(1), 16), [])
            continue
        m = re.match(r'^\s*([0-9a-f]+):\s*(.*)$', line)
        if m and cur is not None:
            ins = m.group(2)
            ins = re.sub(r'\b[0-9a-f]+ <', '<', ins)
            ins = re.sub(r'(?<!\w)(?:0x)?([0-9a-f]{7,8})\b', rel, ins)
            ins = re.sub(r'^add\s+\$0x[0-9a-f]+,%ebx$', 'add $GOT,%ebx', ins)   # the PIC runtime's GOT offset
            cur.append(ins)
            places[last][1].append(int(m.group(1), 16))
    for name, f in funcs.items():
        # jumps within the function: to the target's instruction number, so
        # that a change of instruction size elsewhere does not show
        start, where = places[name]
        index = {a - start: i for i, a in enumerate(where)}
        f[:] = [re.sub(r'<%s\+0x([0-9a-f]+)>' % re.escape(name),
                       lambda m: '<@%s>' % index.get(int(m.group(1), 16), m.group(1)), ins) for ins in f]
    for f in funcs.values():
        while f and re.match(r'(xchg\s+%ax,%ax|nop.*|lea\s+0x0.*|ret)$', f[-1]) and f[-1] != 'ret':
            f.pop()
    return funcs


def objdata(obj):
    """The bytes of an object's data sections."""
    out = {}
    for name, sec in sections(obj).items():
        if re.match(r'\.(data|rodata|bss)', name):
            out[name] = content(obj, sec)
    return out


def relsyms(exe):
    secs = secmap(exe)
    out = {}
    for s, (a, z) in symbols(exe).items():
        for lo, hi, name in secs:
            if lo <= a < hi or (a == hi and z == 0):
                out[s] = ('%s+0x%x' % (name, a - lo), z)
                break
    return out


def main():
    base, new = sys.argv[1], sys.argv[2]
    bad = 0
    # the code, function by function
    recs = spec(sys.argv[3]) if len(sys.argv) > 3 else {}
    absb = symbols(base)
    fold = {}
    for inst, members in recs.items():
        names = [m for m in members if '.' not in m and m in absb]
        if not names:
            continue
        start = min(absb[m][0] for m in names)
        for m in names + [m + '_rest' for m in names if m + '_rest' in absb]:
            fold[m] = (inst, absb[m][0] - start)
    renamed = {}
    if len(sys.argv) > 4:
        for line in open(sys.argv[4]):
            if line.strip() and not line.startswith('#'):
                o, n = line.split()[:2]
                renamed[o] = n
                fold.setdefault(o, (n, 0))
    fb, fn = disasm(base, fold), disasm(new)
    diff = [f for f in fb if f in fn and fb[f] != fn[f]]
    for f in diff:
        print('code differs: %s' % f)
    bad += len(diff)
    only = sorted(set(fb) ^ set(fn))
    for f in only:
        print('function in one build only: %s' % f)
    bad += len(only)
    print('%d functions compared' % len(fb))
    # the data's initial bytes (the game's data object)
    import os
    ob = os.path.join(os.path.dirname(base), 'src_data_gamedata.cpp.o')
    on = os.path.join(os.path.dirname(os.path.dirname(new)), 'build', 'native', 'linux32', 'src_data_gamedata.cpp.o')
    if os.path.exists(ob) and os.path.exists(on):
        db, dn = objdata(ob), objdata(on)
        for k in sorted(set(db) | set(dn)):
            if db.get(k) != dn.get(k):
                print('gamedata.o section %s differs' % k); bad += 1
        print('gamedata.o data sections: %d compared' % len(db))
    # the data symbols
    yb, yn = relsyms(base), relsyms(new)
    folded = {}
    for inst, members in recs.items():
        for m in members:
            folded[m] = inst
    for inst, members in recs.items():
        if inst not in yn:
            continue
        names = [m for m in members if '.' not in m]
        if not names:
            continue        # members of a block: the block's symbol is unchanged
        parts = []
        for m in names:
            if m not in yb:
                print('%s: %s not in the base build' % (inst, m)); bad += 1; continue
            parts.append(absb[m])
            if m + '_rest' in yb:
                parts.append(absb[m + '_rest'])
                folded[m + '_rest'] = inst
        parts.sort()
        if any(parts[i][0] + parts[i][1] != parts[i + 1][0] for i in range(len(parts) - 1)):
            print('%s: its members were not contiguous' % inst); bad += 1
        first = min(names, key=lambda m: absb[m][0])
        if yn[inst] != (yb[first][0], parts[-1][0] + parts[-1][1] - parts[0][0]):
            print('%s: at %s size %x, its members at %s size %x' % (inst, yn[inst][0], yn[inst][1], yb[first][0],
                  parts[-1][0] + parts[-1][1] - parts[0][0])); bad += 1
    nfold = 0
    for s, v in yb.items():
        if s in yn:
            if v[0].startswith(('.rodata', '.text', '.eh', '.init', '.fini')):
                v, w = v[1], yn[s][1]       # code and read-only data move with the symbol tables: sizes
            else:
                w = yn[s]
            if s != '_ZL6layout' and w != v:
                print('%s: %s -> %s' % (s, v, w)); bad += 1
        elif s in folded:
            nfold += 1
        elif renamed.get(s) in yn:
            if yn[renamed[s]] != v:
                print('%s -> %s: %s -> %s' % (s, renamed[s], v, yn[renamed[s]])); bad += 1
        else:
            print('%s: gone' % s); bad += 1
    for s in yn:
        if s not in yb and s not in recs and s not in renamed.values():
            print('%s: new symbol' % s); bad += 1
    print('%d differences; %d data symbols folded into %d records' % (bad, nfold, len([r for r in recs if r in yn])))
    sys.exit(1 if bad else 0)


if __name__ == '__main__':
    main()
