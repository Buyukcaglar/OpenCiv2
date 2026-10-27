#!/usr/bin/env python3
"""The host's relaying in a capture of a game of three or more (records.txt
from xdparse.py, sniffed in the host's network namespace: nettest.py
--third ... --sniff).  For every record a client sent the host, what the
host did with it: delivered only, or forwarded to which client with which
tag.  Prints the rules seen (client's tag -> forwarded tags) with counts, so
two captures (the original hosting, ours hosting) can be compared.

usage: relaytags.py records.txt
"""
import collections
import re
import sys

REC = re.compile(r'^\s*([\d.]+) TCP (\S+):(\d+)>(\S+):(\d+) rec total=(\d+) tag=([0-9a-f]+) \(src=(\d+) dst=(\d+) '
                 r'flags=(\d+)\) len=(\d+) pad=\d+ (.*)$')


def main():
    recs = []
    for line in open(sys.argv[1], errors='replace'):
        m = REC.match(line)
        if m:
            t, sip, sp, dip, dp, total, tag, src, dst, flags, ln, rest = m.groups()
            recs.append(dict(t=float(t), frm=sip if sp == '4993' else None, to=dip if dp == '4993' else None,
                             peer=dip if sp == '4993' else sip, tag=int(tag, 16), src=int(src), dst=int(dst),
                             flags=int(flags), len=int(ln), total=int(total), what=rest.strip()))
    up = [r for r in recs if r['to']]          # client -> host
    down = [r for r in recs if r['frm']]       # host -> client
    ids = {}
    for r in up:
        ids.setdefault(r['peer'], r['src'])
    rules = collections.Counter()
    used = set()
    for r in up:
        if r['src'] >= 0xfa:
            continue
        # the host's records with the same message (type, size, seq) after it
        outs = [i for i, d in enumerate(down) if i not in used and d['t'] >= r['t'] and d['what'] == r['what']
                and d['len'] == r['len'] and d['t'] - r['t'] < 5]
        seen = set()
        fw = []
        for i in outs:
            if down[i]['peer'] in seen or down[i]['peer'] == r['peer']:
                continue
            seen.add(down[i]['peer'])
            used.add(i)
            fw.append('src=%s dst=%s' % ('client' if down[i]['src'] == r['src'] else down[i]['src'],
                                         'that client' if down[i]['dst'] == ids.get(down[i]['peer']) else down[i]['dst']))
        dst = 'host' if r['dst'] == 0 else 'all' if r['dst'] == 0xff else 'other client'
        rules[('client -> %s (flags %d)' % (dst, r['flags']), ' + '.join(sorted(fw)) or 'not forwarded')] += 1
    hostown = collections.Counter('src=%d dst=%s' % (d['src'], 'that client' if d['dst'] == ids.get(d['peer'])
                                                     else d['dst']) for i, d in enumerate(down) if i not in used)
    print('clients:', ', '.join('%s id %d' % kv for kv in sorted(ids.items())))
    print('records: %d client->host, %d host->client' % (len(up), len(down)))
    for (a, b), n in sorted(rules.items()):
        print('%5d  %-28s -> forwarded: %s' % (n, a, b))
    for k, n in sorted(hostown.items()):
        print('%5d  host\'s own records: %s' % (n, k))


if __name__ == '__main__':
    main()
