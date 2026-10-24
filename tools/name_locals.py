#!/usr/bin/env python3
"""Names for parameters and locals the decompiler left numbered (param_N,
iVarN, local_XX), from how they are used:

  * as an index of the game's arrays: cities[v] -> city, units[v] -> unit ...
  * compared with or set from a field that says what it holds:
    units[i].owner == v -> civ, v = units[i].home_city -> city, .x / .y
  * passed where a function's parameter has a name (both ways: a caller's
    argument names the callee's parameter and the other way round),
    repeated until the names settle; seeds: tile_at(x, y) and the
    hand-written functions' parameters.

A name is used only when the evidence agrees (the most common kind wins,
ties are left alone) and it collides with nothing: C keywords, types,
globals and functions (globals are macros), field names (the frame locals
local_XX are macros too), other names in the function.  A second variable
of a kind gets a number (city2).  Pure renaming: applied by tools/gen_c.py
to what it writes.
"""
import collections
import glob
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

ARRAYS = {'cities': 'city', 'units': 'unit', 'civs': 'civ', 'unit_types': 'unit_type',
          'improvements': 'improvement', 'advances': 'advance', 'leaders': 'leader',
          'terrain_types': 'terrain', 'civ_names': 'civ', 'map_views': 'view'}
FIELDS = {'owner': 'civ', 'home_city': 'city', 'x': 'x', 'y': 'y'}
SEEDS = {'tile_at': ['x', 'y']}
VAR = r'(?:param_\d+|[a-z]{1,3}Var\d+|local_[0-9a-f]+)'
KEYWORDS = set('''auto break case char const continue default do double else enum extern float for goto if
inline int long register restrict return short signed sizeof static struct switch typedef union unsigned
void volatile while this'''.split())


def forbidden_names():
    """(names a variable must not take, names a frame macro must not take).
    Variables avoid keywords, types, globals (macros) and functions; the
    frame locals local_XX are macros, so they also avoid field names."""
    words = set(KEYWORDS)
    for path in ('src/include/civ2types.h', 'src/include/civ2classes.h', 'tools/ghidra.h', 'src/include/native.h',
                 'src/auto/globals.h', 'src/data/gamedata.h', 'src/auto/auto_common.h'):
        p = os.path.join(ROOT, path)
        if not os.path.exists(p):
            continue
        t = re.sub(r'/\*.*?\*/|//[^\n]*', '', open(p, errors='replace').read(), flags=re.S)
        words.update(re.findall(r'#\s*define\s+(\w+)', t))
        words.update(re.findall(r'\btypedef\b[^;{}]*?\b(\w+)\s*(?:\[[^\]]*\])*\s*;', t))
        words.update(re.findall(r'\}\s*(\w+)\s*;', t))
        words.update(re.findall(r'\b(?:struct|union|enum)\s+(\w+)', t))
        words.update(re.findall(r'\bextern\b[^;(]*?\b(\w+)\s*(?:\[[^\]]*\])*\s*;', t))
    for line in open(os.path.join(ROOT, 're', 'symbols.tsv'), errors='replace'):
        f = line.split('\t')
        if len(f) > 2:
            words.add(f[2])
    for line in open(os.path.join(ROOT, 're', 'type_names.tsv'), errors='replace'):
        words.update(line.split('\t')[:2])
    words.update(re.findall(r'\b(\w+)\(\);', open(os.path.join(ROOT, 'src', 'auto', 'protos.h')).read()))
    fields = set(words)
    for path in ('src/include/civ2types.h', 'src/include/civ2classes.h'):
        t = re.sub(r'/\*.*?\*/', '', open(os.path.join(ROOT, path), errors='replace').read(), flags=re.S)
        fields.update(re.findall(r'\b(\w+)\s*(?:\[[^\]]*\])*\s*;', t))
    for line in open(os.path.join(ROOT, 're', 'field_names.tsv'), errors='replace'):
        f = line.split('\t')
        if len(f) > 2:
            fields.add(f[2])
    return words, fields


def split_functions(text):
    """[(start, end)] of each function's region (from its /* addr */ line)."""
    starts = [m.start() for m in re.finditer(r'^/\* [0-9a-f]{8} \w+', text, re.M)]
    return list(zip(starts, starts[1:] + [len(text)]))


def signature(region):
    """(function name, [parameter names]) of the definition in a region."""
    m = re.search(r'^[A-Za-z_][^;{}#]*?\b(\w+)\s*\(([^()]*(?:\([^()]*\)[^()]*)*)\)\s*\n\{', region, re.M)
    if not m:
        return None, []
    params = []
    for p in m.group(2).split(','):
        w = re.findall(r'\b\w+\b', p)
        params.append(w[-1] if w else '')
    return m.group(1), params


def call_args(region, func):
    """Argument lists of the calls of func in a region."""
    out = []
    for m in re.finditer(r'\b%s\(' % re.escape(func), region):
        depth, i, start, args = 0, m.end(), m.end(), []
        while i < len(region):
            c = region[i]
            if c in '([':
                depth += 1
            elif c in ')]':
                if depth == 0:
                    args.append(region[start:i])
                    break
                depth -= 1
            elif c == ',' and depth == 0:
                args.append(region[start:i])
                start = i + 1
            i += 1
        out.append([a.strip() for a in args])
    return out


def bare(arg):
    """The variable an argument is (through casts), or None."""
    m = re.match(r'^(?:\(\s*[\w ]+\**\s*\))*\s*(' + VAR + r')$', arg)
    return m.group(1) if m else None


def evidence(region, param_names):
    ev = collections.defaultdict(collections.Counter)
    for m in re.finditer(r'\b(\w+)\[(' + VAR + r')\]', region):
        if m.group(1) in ARRAYS:
            ev[m.group(2)][ARRAYS[m.group(1)]] += 1
    for m in re.finditer(r'\b(units|cities)\[[^\[\]]*\]\.(\w+)\s*(?:==|!=)\s*(?:\(\w+\))?(' + VAR + r')\b', region):
        if m.group(2) in FIELDS:
            ev[m.group(3)][FIELDS[m.group(2)]] += 1
    for m in re.finditer(r'\b(' + VAR + r')\s*(?:==|!=|=)\s*(?:\(\w+\))?(units|cities)\[[^\[\]]*\]\.(\w+)\b(?!\[)', region):
        if m.group(3) in FIELDS:
            ev[m.group(1)][FIELDS[m.group(3)]] += 1
        elif m.group(2) == 'units' and m.group(3) == 'type':
            ev[m.group(1)]['unit_type'] += 1
    for m in re.finditer(r'\b(' + VAR + r') < game\.num_(cities|units)\b', region):
        ev[m.group(1)]['city' if m.group(2) == 'cities' else 'unit'] += 1
    for func, names in param_names.items():
        if func not in region:
            continue
        for args in call_args(region, func):
            for a, n in zip(args, names):
                v = bare(a)
                if v and n:
                    ev[v][re.sub(r'\d+$', '', n)] += 1
    return ev


def choose(ev, taken, forbidden):
    """var -> new name: parameters first, then the best attested."""
    out = {}
    words, fields = forbidden
    order = sorted(ev, key=lambda v: (not v.startswith('param_'), -ev[v].most_common(1)[0][1], v))
    for v in order:
        top = ev[v].most_common(2)
        if not top or (len(top) > 1 and top[1][1] == top[0][1]):
            continue
        base = top[0][0]
        bad = fields if v.startswith('local_') else words
        n, k = base, 1
        while n in taken or n in bad:
            k += 1
            n = '%s%d' % (base, k)
            if k > 9:
                break
        else:
            out[v] = n
            taken.add(n)
    return out


def files():
    return sorted(glob.glob(os.path.join(ROOT, 'src', 'auto', '*.cpp')) +
                  glob.glob(os.path.join(ROOT, 'src', 'unused', 'blk_*.c')))


def apply_all(paths=None):
    paths = paths or files()
    texts = {p: open(p).read() for p in paths}
    forbidden = forbidden_names()
    # parameter names known: seeds, hand-written definitions, named ones
    known = dict(SEEDS)
    for p in glob.glob(os.path.join(ROOT, 'src', 'game', '*.cpp')):
        for m in re.finditer(r'^[A-Za-z_][\w \*]*\b(\w+)\(([^()]*)\)\s*\n\{', open(p, errors='replace').read(), re.M):
            names = [re.findall(r'\w+', a)[-1] if re.findall(r'\w+', a) else '' for a in m.group(2).split(',')]
            if names and not any(re.match(VAR, n) for n in names) and 'void' not in names:
                known.setdefault(m.group(1), names)
    regions = {p: split_functions(t) for p, t in texts.items()}
    renames = {}
    for _ in range(4):
        params = dict(known)
        for (p, i), rn in renames.items():
            func, ps = signature(texts[p][regions[p][i][0]:regions[p][i][1]])
            if func:
                params[func] = [rn.get(x, '') if re.match(VAR + '$', x) else x for x in ps]
        new = {}
        for p, regs in regions.items():
            for i, (s, e) in enumerate(regs):
                region = texts[p][s:e]
                ev = evidence(region, params)
                if not ev:
                    continue
                # names in use (a field after '.' or '->' is no variable's)
                taken = set(re.findall(r'(?<![.>\w])[A-Za-z_]\w*\b', region))
                ch = choose(ev, taken, forbidden)
                if ch:
                    new[(p, i)] = ch
        if new == renames:
            break
        renames = new
    count = 0
    for p, regs in regions.items():
        t = texts[p]
        out, last = [], 0
        for i, (s, e) in enumerate(regs):
            out.append(t[last:s])
            region = t[s:e]
            rn = renames.get((p, i))
            if rn:
                region = re.sub(r'\b(' + '|'.join(map(re.escape, rn)) + r')\b', lambda m: rn[m.group(1)], region)
                count += len(rn)
            out.append(region)
            last = e
        out.append(t[last:])
        n = ''.join(out)
        if n != t:
            open(p, 'w').write(n)
    return count


if __name__ == '__main__':
    print('%d variables named' % apply_all())
