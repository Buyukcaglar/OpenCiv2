#!/usr/bin/env python3
"""Step 6 (RAII): compare, function by function, the sequences of calls two
builds of a source can make, path by path.

    calls_compare.py [--map re/methods.tsv] BASE.o NEW.o [FUNCTION...]

Each function's control-flow graph (objects from tools/cfg_one.sh: no jump
tables, no inlining but always_inline) is reduced to its calls: an
automaton whose words are the sequences of callees along the paths from the
entry to a return.  Two functions match when the two automata accept the
same words (subset construction, then a product walk).  A guard that runs
a release at scope exit, where the original wrote the release on each
return, gives the same words even when the compiler shares one copy of it
between the paths; a path that gains, loses or reorders a call does not.
Conditions are not compared (the graph comparison, tools/cfg_compare.py,
does that): use this on the functions that one reports.
"""
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import cfg_compare as cfg  # noqa: E402
import cxx_compare as cc  # noqa: E402


def automaton(fn):
    """(start node, {node: [(label or None, node)]}, accepting nodes)."""
    insns, index = fn
    edges = {}
    accept = set()
    n = len(insns)
    for i, (addr, text) in enumerate(insns):
        out = []
        label = None
        if text.startswith('call'):
            m = re.search(r'@R_\w+ (\S+)', text)
            label = m.group(1) if m else ('call*' if '*' in text else re.sub(r'^call\s+\S+\s*', 'call ', text))
            out.append((label, i + 1))
        elif re.match(r'(ret|ud2)', text):
            accept.add(i)
        else:
            t = cfg.target(text)
            if text.startswith('jmp'):
                if t:
                    out.append((None, index.get(t[1], -1)))
                elif '@R_' in text:     # a tail call
                    m = re.search(r'@R_\w+ (\S+)', text)
                    out.append((m.group(1), n))
                    accept.add(n)
                else:
                    return None         # an indirect jump
            elif t:
                out.append((None, index.get(t[1], -1)))
                out.append((None, i + 1))
            else:
                out.append((None, i + 1))
        edges[i] = out
    edges.setdefault(n, [])
    return 0, edges, accept


def closure(edges, nodes):
    seen = set(nodes)
    work = list(nodes)
    while work:
        x = work.pop()
        for lab, y in edges.get(x, []):
            if lab is None and y not in seen:
                seen.add(y)
                work.append(y)
    return frozenset(seen)


def step(edges, state, label):
    return closure(edges, [y for x in state for lab, y in edges.get(x, []) if lab == label])


def labels(edges, state):
    return {lab for x in state for lab, y in edges.get(x, []) if lab is not None}


def equivalent(a, b):
    sa, ea, acc_a = a
    sb, eb, acc_b = b
    start = (closure(ea, [sa]), closure(eb, [sb]))
    seen = {start}
    work = [(start, [])]
    while work:
        (x, y), path = work.pop()
        if bool(x & acc_a) != bool(y & acc_b):
            return 'a return after %s in one only' % (' '.join(path[-6:]) or 'no call')
        for lab in labels(ea, x) | labels(eb, y):
            nx, ny = step(ea, x, lab), step(eb, y, lab)
            if not nx or not ny:
                return '%s after %s in one only' % (lab, ' '.join(path[-6:]) or 'the entry')
            if (nx, ny) not in seen:
                seen.add((nx, ny))
                work.append(((nx, ny), path + [lab]))
    return None


def main():
    args = sys.argv[1:]
    if args[:1] == ['--map']:
        cc.load_map(args[1])
        args = args[2:]
    if len(args) < 2:
        print(__doc__)
        return 1
    a, b = cfg.functions(args[0]), cfg.functions(args[1])
    only = set(args[2:])
    same = 0
    differ = []
    for name in sorted(a):
        if name not in b or (only and name not in only):
            continue
        fa, fb = automaton(a[name]), automaton(b[name])
        if fa is None or fb is None:
            differ.append((name, 'indirect jump'))
            continue
        why = equivalent(fa, fb)
        if why:
            differ.append((name, why))
        else:
            same += 1
    print('%d functions make the same calls, %d differ' % (same, len(differ)))
    for name, why in differ:
        print('%s\t%s' % (name, why))
    return 1 if differ else 0


if __name__ == '__main__':
    sys.exit(main())
