#!/usr/bin/env python3
"""Where do the virtual clocks of two replays part?  Aligns the retrieved
messages of a Wine trace and a native trace (hook.log lines
`msg ... #N @US`, CIV2_TRACE_MSG=1) and prints the first messages that are
the same but were retrieved at different virtual times, with the time gained
or lost since the previous aligned message.

Usage: clockdiff.py WINE_HOOK_LOG NATIVE_HOOK_LOG [--max 10]
"""
import argparse
import difflib
import re

MSG = re.compile(r'^(msg \S+ w\d+ wp=\S+ \[\S+\]) #(\d+) @(\d+)')


def load(path):
    out = []
    for line in open(path, errors='replace'):
        m = MSG.match(line)
        if m:
            out.append((m.group(1), int(m.group(2)), int(m.group(3))))
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('wine')
    ap.add_argument('native')
    ap.add_argument('--max', type=int, default=10)
    a = ap.parse_args()
    w, n = load(a.wine), load(a.native)
    sm = difflib.SequenceMatcher(None, [x[0] for x in w], [x[0] for x in n], autojunk=False)
    shown = 0
    prev = None
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag != 'equal':
            continue
        for k in range(i2 - i1):
            wm, nm = w[i1 + k], n[j1 + k]
            if wm[2] != nm[2]:
                gap = ''
                if prev:
                    gap = ' (since previous aligned: wine +%d us, native +%d us; msg #%d->#%d vs #%d->#%d)' % (
                        wm[2] - prev[0][2], nm[2] - prev[1][2], prev[0][1], wm[1], prev[1][1], nm[1])
                print('%s: wine @%d native @%d diff %+d us%s' % (wm[0], wm[2], nm[2], nm[2] - wm[2], gap))
                shown += 1
                if shown >= a.max:
                    return
            prev = (wm, nm)
    if not shown:
        print('aligned messages all at the same virtual times (%d wine, %d native)' % (len(w), len(n)))


if __name__ == '__main__':
    main()
