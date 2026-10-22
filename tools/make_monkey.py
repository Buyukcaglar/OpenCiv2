#!/usr/bin/env python3
"""Write a "monkey" replay script: the autosave loaded, then N random inputs
(unit orders, movement, advisor and report keys, Return/Escape, clicks in the
game window below its menu bar: replays cannot drive menus, whose tracking
reads the host's events) from a seed, with a shot every 25.  For comparing builds
(harness/diff_suite.sh); the same seed gives the same script.

Usage: tools/make_monkey.py SEED [N] > harness/diffscripts/monkeySEED.txt
"""
import random
import sys

# Keys a player uses; nothing that quits, saves over files or opens the
# host's own menus (Alt).
KEYS = (['Up', 'Down', 'Left', 'Right', 'Home', 'End', 'Prior', 'Next'] * 4 +   # move / select
        ['KP_1', 'KP_2', 'KP_3', 'KP_4', 'KP_6', 'KP_7', 'KP_8', 'KP_9'] * 2 +
        ['b', 'f', 's', 'w', 'space', 'h', 'r', 'm', 'i', 'p', 'o', 'c', 'n', 'l', 'u', 'k', 't'] +   # unit orders
        ['F1', 'F2', 'F3', 'F4', 'F5', 'F6', 'F7', 'F8', 'F9', 'F11'] +   # advisors, reports
        ['Return'] * 10 + ['Escape'] * 6 + ['Tab', 'shift+Tab', 'z', 'x', 'shift+c'])


def main():
    seed = int(sys.argv[1])
    n = int(sys.argv[2]) if len(sys.argv) > 2 else 400
    rnd = random.Random(seed)
    out = ['# Monkey test (tools/make_monkey.py %d %d): random play on the autosave.' % (seed, n),
           'wait 8000', 'key Down Down Down Down', 'wait 500', 'file Ca_Auto.SAV', 'key Return',
           'wait 20000', 'key Return', 'wait 8000', 'shot 000-loaded']
    for i in range(1, n + 1):
        r = rnd.random()
        if r < 0.7:
            out.append('key %s' % rnd.choice(KEYS))
        else:
            out.append('click %d %d' % (rnd.randrange(4, 636), rnd.randrange(50, 476)))
        out.append('wait %d' % rnd.choice((300, 800, 1500, 3000)))
        if i % 25 == 0:
            out.append('shot %03d' % i)
    print('\n'.join(out))


if __name__ == '__main__':
    main()
