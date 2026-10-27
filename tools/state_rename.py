#!/usr/bin/env python3
"""Rename identifiers of the game's state everywhere in src/{auto,game,
native,data,include} (code and comments, not string literals).

    state_rename.py RENAMES.tsv        (lines: old<TAB>new; # comments)

A rename is applied only when the new name is not an identifier anywhere
in those sources yet: renaming every occurrence of a name to a fresh one
cannot change what any other name refers to.  Names whose new name is taken
are listed and left alone.
"""
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from state_records import sources, code_only    # noqa: E402

STRING = re.compile(r'"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'')


def main():
    pairs = []
    for line in open(sys.argv[1]):
        if line.strip() and not line.startswith('#'):
            old, new = line.split()[:2]
            pairs.append((old, new))
    texts = {f: open(f).read() for f in sources()}
    toks = set()
    for t in texts.values():
        toks.update(re.findall(r'[A-Za-z_]\w*', code_only(t)))
    news = [n for _, n in pairs]
    ok, skipped = {}, []
    for old, new in pairs:
        if new in toks or news.count(new) > 1:
            skipped.append('%s -> %s' % (old, new))
        elif old in toks:
            ok[old] = new
    if skipped:
        print('left alone (new name taken): ' + ', '.join(skipped))
    if not ok:
        return
    pat = re.compile(r'\b(%s)\b' % '|'.join(sorted(map(re.escape, ok), key=len, reverse=True)))
    n = 0
    for f, t in texts.items():
        out, last = [], 0
        for m in STRING.finditer(t):
            out.append(pat.sub(lambda x: ok[x.group(1)], t[last:m.start()]))
            out.append(m.group(0))
            last = m.end()
        out.append(pat.sub(lambda x: ok[x.group(1)], t[last:]))
        new = ''.join(out)
        if new != t:
            open(f, 'w').write(new)
            n += 1
    print('renamed %d names in %d files' % (len(ok), n))


if __name__ == '__main__':
    main()
