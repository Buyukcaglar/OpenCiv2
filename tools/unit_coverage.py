#!/usr/bin/env python3
"""What the unit tests cover: the functions with recorded cases
(tests/unit/*.gz) against the game functions the recorded replays ran
(run/unitrec-*.raw.gz.txt, the recorder's counts), by source file.  Writes
tests/unit/cases.tsv (function, file, cases) and prints the totals.

    python3 tools/unit_coverage.py      (after tools/unit_record.sh)
    python3 tools/unit_coverage.py --have SCENARIO   the other scenarios' cases per function
"""
import collections
import glob
import gzip
import os
import re
import sys
import struct
import subprocess

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
REGIONS = 13


def cases(path, text=None):
    """(function symbol, rand calls) of each case in a file of cases; with
    text (a list), the runs of text in the game's data its deltas hold."""
    d = gzip.open(path).read()
    assert d[:8] == b'CIV2UT01'
    i = 12
    u = lambda: struct.unpack_from('<I', d, i)[0]
    while i < len(d):
        assert u() == 0x45534143
        i += 4
        n = u(); i += 4
        name = d[i:i + n].decode(); i += n
        i += 8                              # call, flags
        words = u(); i += 4 + 12 * words
        win = u(); i += 8 + win
        if win:
            runs = u(); i += 4
            for k in range(runs):
                i += 8 + struct.unpack_from('<I', d, i + 4)[0]
        rands = u(); i += 4 + 4 * REGIONS
        for part in range(2):
            for r in range(REGIONS):
                runs = u(); i += 4
                for k in range(runs):
                    off, ln = struct.unpack_from('<II', d, i)
                    if text is not None and r == 0:
                        for m in re.finditer(rb'[A-Za-z][ -~]{5,}', d[i + 8:i + 8 + ln]):
                            if sum(c.isalpha() for c in m.group().decode()) >= 5:
                                text.append((off + m.start(), m.group()))
                    i += 8 + ln
            if part == 0:
                i += 8                      # return value
        yield name, rands


def text_report():
    """--text: where text is left in the recorded cases (the program's own
    strings aside), by variable: candidates for tools/unit_textmask.py."""
    syms = []
    for line in subprocess.run(['nm', '-S', 'build/civ2-unittest'], capture_output=True, text=True).stdout.splitlines():
        p = line.split()
        if len(p) == 4 and 0x30000000 <= int(p[0], 16) < 0x30200000:
            syms.append((int(p[0], 16) - 0x30000000, p[3]))
    syms.sort()
    import bisect
    found = collections.defaultdict(set)
    for path in sorted(glob.glob('tests/unit/*.gz')):
        text = []
        for _ in cases(path, text):
            pass
        for off, t in text:
            k = bisect.bisect_right(syms, (off, '\uffff')) - 1
            found[syms[k][1] if k >= 0 else '?'].add(t[:40])
    for name in sorted(found):
        print(name, sorted(found[name])[:5])


def main():
    os.chdir(ROOT)
    if sys.argv[1:] == ['--text']:
        return text_report()
    if sys.argv[1:2] == ['--have']:
        # the cases the other files have, per function (tools/unit_record.sh)
        count = collections.Counter()
        for path in glob.glob('tests/unit/*.gz'):
            if os.path.basename(path) != sys.argv[2] + '.gz':
                count.update(name for name, r in cases(path))
        for name, n in sorted(count.items()):
            print('%s\t%d' % (name, n))
        return
    sigs = {}
    for line in open('run/unit_sigs.tsv'):
        p = line.rstrip('\n').split('\t')
        sigs[p[0]] = p[1]
    ran = set()
    for path in glob.glob('run/unitrec-*.raw.gz.txt'):
        for line in open(path):
            p = line.split('\t')
            if not line.startswith('#') and len(p) > 2 and int(p[1]) > 0:
                ran.add(p[0])
    count = collections.Counter()
    rands = collections.Counter()
    files = sorted(glob.glob('tests/unit/*.gz'))
    for path in files:
        for name, r in cases(path):
            count[name] += 1
            rands[name] += r > 0
    names = sorted(set(count) | ran)
    demangled = dict(zip(names, subprocess.run(['c++filt'], input='\n'.join(names), capture_output=True,
                                               text=True).stdout.splitlines()))
    with open('tests/unit/cases.tsv', 'w') as f:
        f.write('# The functions the unit tests call (tools/unit_coverage.py): function, file, cases, cases with rand()\n')
        for name in sorted(count, key=lambda n: (sigs.get(n, '?'), demangled[n])):
            f.write('%s\t%s\t%d\t%d\n' % (demangled[name].split('(')[0], sigs.get(name, '?'), count[name], rands[name]))
    by_file = collections.defaultdict(lambda: [0, 0, 0])
    for name in ran:
        by_file[sigs.get(name, '?')][0] += 1
    for name in count:
        by_file[sigs.get(name, '?')][1] += 1
        by_file[sigs.get(name, '?')][2] += count[name]
    print('%-24s %8s %8s %8s' % ('file', 'ran', 'tested', 'cases'))
    for file in sorted(by_file, key=lambda k: -by_file[k][1]):
        r, t, c = by_file[file]
        print('%-24s %8d %8d %8d' % (file, r, t, c))
    print('%d files of cases, %d cases (%d with rand() calls) of %d functions; the replays recorded ran %d game functions'
          % (len(files), sum(count.values()), sum(rands.values()), len(count), len(ran)))


if __name__ == '__main__':
    main()
