#!/usr/bin/env python3
"""Compare two saved games of the same network game (each player's own
save): do the games agree?  Each section is compared; the parts that are
each player's own (what each civilization has seen of the map, the
per-player view state at the end) are reported apart.

usage: savecmp.py A.net B.net     (exit status 1 if the shared state differs)
"""
import struct
import sys

CIV = 0x594


def sections(path):
    d = open(path, 'rb').read()
    if d[:8] != b'CIVILIZE':
        raise SystemExit('%s: not a saved game' % path)
    p = 12
    out = {}

    def take(name, n):
        nonlocal p
        out[name] = d[p:p + n]
        p += n

    take('game', 0x14a)
    num_units, num_cities = struct.unpack_from('<hh', out['game'], 0x2e)
    take('civ_names', 0x790)
    take('civs', 0x2ca0)
    take('map_header', 0xe)
    w, h, area, flat, seed, qw, qh = struct.unpack('<hhhHHhh', out['map_header'])
    for civ in range(1, 8):
        take('known%d' % civ, area)
    take('tiles', area * 6)
    take('coarse', qw * qh * 2)
    take('landmass', 0x400)
    take('units', num_units * 0x20)
    take('cities', num_cities * 0x58)
    out['rest'] = d[p:]
    out['_counts'] = (num_units, num_cities, area)
    return out


def diff(a, b):
    n = max(len(a), len(b))
    return [i for i in range(n) if i >= len(a) or i >= len(b) or a[i] != b[i]]


def main():
    a, b = sections(sys.argv[1]), sections(sys.argv[2])
    ok = True
    print('units %d / %d, cities %d / %d, tiles %d' % (a['_counts'][0], b['_counts'][0], a['_counts'][1],
                                                        b['_counts'][1], a['_counts'][2]))
    for name in ('game', 'civ_names', 'civs', 'map_header', 'tiles', 'coarse', 'landmass', 'units', 'cities'):
        dd = diff(a[name], b[name])
        if name == 'civs':
            per = {}
            for i in dd:
                per.setdefault(i // CIV, []).append(i % CIV)
            text = ', '.join('civ %d: %d bytes (first +0x%x)' % (c, len(v), v[0]) for c, v in sorted(per.items()))
        elif name in ('units', 'cities'):
            size = 0x20 if name == 'units' else 0x58
            recs = sorted({i // size for i in dd})
            text = '%d records (%s)' % (len(recs), ' '.join(str(r) for r in recs[:12]))
        else:
            text = ', '.join('+0x%x' % i for i in dd[:12]) + (' ...' if len(dd) > 12 else '')
        same = not dd
        # (the game header holds the saving player's own civ and view flags;
        # a civ's last_contact_turn[] (+0x3e2..0x3f1) is set by the game that
        # showed the audience request, and not sent to the others)
        shared = name not in ('game',)
        if name == 'civs' and dd and all(0x3e2 <= i % CIV < 0x3f2 for i in dd):
            shared = False
            text += '   (last_contact_turn: each game its own)'
        if name == 'tiles' and dd:
            # (a client hears of a tile only when a human civ has seen it: a
            # tile no human has seen may hold an AI unit in the host's map
            # only; the units themselves are compared above)
            humans = a['game'][0x23] & b['game'][0x23]
            if all(i % 6 == 5 and not (a['tiles'][i - 1] & humans) and not (b['tiles'][i - 1] & humans)
                   for i in dd):
                shared = False
                text += '   (who is on tiles no human has seen)'
        if shared and not same:
            ok = False
        print('%-10s %s%s' % (name, 'same' if same else 'DIFFERENT: %d bytes: %s' % (len(dd), text),
                               '' if shared or same or name != 'game' else '   (the saving player\'s own fields)'))
    for civ in range(1, 8):
        dd = diff(a['known%d' % civ], b['known%d' % civ])
        if dd:
            print('known%d    %d tiles differ   (what civ %d has seen: each game keeps its own)' % (civ, len(dd), civ))
    print('SAME' if ok else 'DIFFERENT')
    sys.exit(0 if ok else 1)


if __name__ == '__main__':
    main()
