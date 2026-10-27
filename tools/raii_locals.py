#!/usr/bin/env python3
"""Step 6 (RAII): the decompiler's inlined unwind funclets that destroy a
local object become one ON_SCOPE_EXIT (src/include/scoped.h) right after the
object is built.

    raii_locals.py [--dry] FILE...

A funclet line looks like
    /* inlined unwind funclet 0040dea8 */ { taxrate_dialog_dtor(&dialog2); }
and stands on every path out of the function after the object's
construction (MSVC ran it on each return).  A function is converted only
when, for each such object:
  - the object's first use (its construction) is a one-line statement at the
    function's top level, so the guard lives until the function returns;
  - every `return` after that, and the end of the function, is preceded by
    the funclet (only other funclets and `eh_state = ...;` between), and the
    funclet appears nowhere else;
  - the returned value is a constant or a plain local other than the object,
    so it is the same read before or after the destruction;
  - at each exit the funclets come in the reverse order of construction (the
    guards' order).
The MSVC trylevel bookkeeping (`eh_state`, `seh_next`, `seh_handler`
locals, never read) is dropped with them.  Blocks left empty are reported:
fix them by hand.  The result is checked by compiling (a guard skipped by a
jump does not compile) and by tools/cxx_one.sh against the previous objects.
"""
import re
import sys

RELAXED = False

FUNCLET = re.compile(r'^(\s*)/\* inlined unwind funclet ([0-9a-f]+) \*/ \{ (.*) \}$')
EH = re.compile(r'^\s*(s?eh_state|try_level|unwind_state|\(\*\(\(char \*\)&(?:s?eh_state|try_level|unwind_state) \+ \d+\)\)) = [^;]*;$')
RET = re.compile(r'^\s*return\b\s*([^;]*);')
SIMPLE_RET = re.compile(r'^(|-?(0x)?[0-9a-fA-F]+[UL]*|\'.\'|[A-Za-z_]\w*|\(\w+\)-?(0x)?[0-9a-fA-F]+)$')


def object_of(stmt):
    """The local object a funclet statement destroys, or None."""
    if re.search(r'\b(self|this)\b', stmt):
        return None
    # only a whole local: X.f(), f(&X), f((T *)&X), ((T *)&X)->f(),
    # crt_vector_dtor_iterator(&X or X, ...); not a part of one (&X + 0x2d8)
    for pat in (r'^(\w+)\.(?:\w+::)?\w+\(\);?$',
                r'^\w+\((?:\(\w+ \*\))?&(\w+)\);?$',
                r'^\(\(\w+ \*\)&(\w+)\)->(?:\w+::)?\w+\(\);?$',
                r'^crt_vector_dtor_iterator\(&?(\w+),\w+,\w+,\w+\);?$'):
        m = re.match(pat, stmt)
        if m:
            return m.group(1)
    return None


def functions(lines):
    i = 0
    while i < len(lines):
        if lines[i] == '{':
            j = i + 1
            while j < len(lines) and lines[j] != '}':
                j += 1
            yield i, j
            i = j
        i += 1


def convert(lines, start, end, report, name):
    body = range(start + 1, end)
    fls = [k for k in body if FUNCLET.match(lines[k])]
    if not fls:
        return None
    objs = {}
    for k in fls:
        ind, addr, stmt = FUNCLET.match(lines[k]).groups()
        o = object_of(stmt)
        if o is None:
            return 'funclet on no local: ' + stmt
        if o in objs and objs[o][1] != stmt:
            return 'two statements for ' + o
        objs.setdefault(o, [addr, stmt, []])[2].append(k)
    # construction: first line naming the object after its declaration
    decl = {}
    for o in objs:
        first = None
        for k in body:
            if k in fls:
                continue
            if re.search(r'\b%s\b' % re.escape(o), lines[k]):
                if re.match(r'^\s*[\w:<>\s*]+\b%s(\[[^]]*\])?;' % re.escape(o), lines[k]):
                    continue    # declaration
                first = k
                break
        if first is None:
            return 'no construction of ' + o
        if not lines[first].rstrip().endswith(';') or not re.match(r'^\s+[\w(*]', lines[first]) \
                or re.match(r'^\s*(if|for|while|else|return)\b', lines[first]):
            return 'construction of %s not a statement: %s' % (o, lines[first].strip())
        ind = len(lines[first]) - len(lines[first].lstrip())
        if ind != 2:
            # nested: the guard lives until the enclosing block's end, so
            # every funclet of the object must be inside that block
            k = first + 1
            while k < end and not (lines[k].strip() == '}' and len(lines[k]) - len(lines[k].lstrip()) < ind):
                k += 1
            if not RELAXED or any(not (first < f < k) for f in objs[o][2]):
                return 'construction of %s not a top-level statement: %s' % (o, lines[first].strip())
        decl[o] = first
    order = sorted(objs, key=lambda o: decl[o])   # construction order
    # exits: returns after the first construction, and the end
    exits = [k for k in body if RET.match(lines[k]) and k > min(decl.values())]
    if not any(k == end - 1 or (RET.match(lines[k]) and all(lines[x].strip() == '' for x in range(k + 1, end)))
               for k in exits):
        exits.append(end)
    used = set(fls) if RELAXED else set()
    for e in ([] if RELAXED else exits):
        if e < end:
            m = RET.match(lines[e])
            val = m.group(1).strip()
            if not SIMPLE_RET.match(val) or val in objs:
                return 'returns %s' % val
        k = e - 1
        seen = []
        while k > start and (FUNCLET.match(lines[k]) or EH.match(lines[k]) or lines[k].strip() == ''):
            if FUNCLET.match(lines[k]):
                seen.append(object_of(FUNCLET.match(lines[k]).group(3)))
                used.add(k)
            k -= 1
        seen.reverse()
        live = [o for o in order if decl[o] < e]
        # the objects live at this exit, destroyed last-built first
        if seen != list(reversed(live)):
            return 'exit at line %d destroys %s, live %s' % (e + 1, seen, live)
    if set(fls) - used:
        return 'funclet not at an exit (line %d)' % (min(set(fls) - used) + 1)
    # rewrite
    for o in objs:
        addr, stmt, _ = objs[o]
        k = decl[o]
        lines[k] = lines[k] + '\n%sON_SCOPE_EXIT(%s);' % (re.match(r'\s*', lines[k]).group(0), stmt.rstrip(';'))
    for k in fls:
        lines[k] = None
    for k in body:
        if lines[k] is not None and EH.match(lines[k]):
            lines[k] = None
    text = '\n'.join(l for l in lines[start:end] if l is not None)
    for v in ('eh_state', 'seh_state', 'try_level', 'unwind_state', 'seh_next', 'seh_handler', 'eh_handler', 'seh_prev'):
        if len(re.findall(r'\b%s\b' % v, text)) == 1:
            for k in body:
                if lines[k] is not None and re.match(r'^\s*[\w ]+\*?\s*%s;$' % v, lines[k]):
                    lines[k] = None
    # empty blocks left
    kept = [k for k in body if lines[k] is not None]
    for a, b in zip(kept, kept[1:]):
        if lines[a].rstrip().endswith('{') and lines[b].strip() == '}':
            report.append('%s: empty block at line %d' % (name, a + 1))
    return 'ok'


def main():
    args = sys.argv[1:]
    global RELAXED
    dry = '--dry' in args
    RELAXED = '--relaxed' in args
    args = [a for a in args if a not in ('--dry', '--relaxed')]
    for path in args:
        lines = open(path).read().split('\n')
        report = []
        nok = nskip = 0
        for start, end in list(functions(lines)):
            name = lines[start - 1].strip()
            r = convert(lines, start, end, report, name)
            if r is None:
                continue
            if r == 'ok':
                nok += 1
            else:
                nskip += 1
                print('%s:%d %s: left: %s' % (path, start, name[:60], r))
        out = '\n'.join(l for l in lines if l is not None)
        if not dry:
            open(path, 'w').write(out)
        print('%s: %d functions converted, %d left' % (path, nok, nskip))
        for r in report:
            print('  ' + r)


if __name__ == '__main__':
    main()
