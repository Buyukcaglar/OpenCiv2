#!/usr/bin/env python3
"""Split the game's functions from files by address (src/auto/blk_XXXX.c,
crt_XXXX.c, as tools/gen_c.py wrote them) into files by subject:
src/auto/<module>.c.

A function goes to the module of its name's prefix (MODULES); one whose
name says nothing (FUN_..., a pointer to a hand-written function) goes with
the function before it in address order -- the original's source files were
linked as contiguous runs, so neighbours belong together.  Within a module
the functions stay in address order.  Each function brings its own
#define/#undef block, so moving it changes nothing else.

Usage: split_modules.py [--dry-run]
"""
import collections
import glob
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
AUTO = os.path.join(ROOT, 'src', 'auto')

# module: (description, name prefixes)
MODULES = {
    'city': ('cities: growth, production, happiness, the city window and city view',
             'city cityview cities impr improvement wonder wonders trade taxrate tax lux citizen unhappy citywnd'),
    'unit': ('units: movement, orders, combat, pathfinding, diplomats and spies',
             'unit units path spy combat stack nuke nuclear explosion fortify'),
    'ai': ('the computer players', 'ai'),
    'civ': ('civilizations: advances, research, government, the rules',
            'civ tech advance research science cosmic rules government golden'),
    'diplomacy': ('diplomacy and treaties', 'diplo'),
    'reports': ('the advisors, the High Council and the reports',
                'advisor council intel attitude defense foreign casualty hall credits demographics defeat '
                'arrival destroyed throneroom endgame victory powergraph historian top leaders'),
    'map': ('the world map: terrain, generation, visibility',
            'map tile tiles terrain river forest mountain hill mapgen resource continent landmass coast land '
            'grassland unexplored road airbase hut pollution known'),
    'mapview': ('the map windows: drawing, scrolling, the mini map', 'mapview mapviews minimap clickmap'),
    'pedia': ('the Civilopedia', 'pedia hyperlink'),
    'spaceship': ('the space race', 'spaceship'),
    'game': ('the game: start-up, turns, saving, scenarios, events, cheats',
             'game main app setup save load scenario events event cheat timer turn eot diffeng tutorial status '
             'intro password passwords prefs registry'),
    'editor': ('the scenario editors', 'editor tribe'),
    'network': ('multiplayer: network sessions, negotiation, lobby and chat', 'net parley lobby chat mp xd'),
    'sound': ('sound, music and video', 'snd avi music sound video mmwnd moviewnd'),
    'window': ('windows, dialogs and menus',
               'wnd window frame surfwnd picwnd ddwin hwnd caption dialog dlg popup menu ui hotspot panel '
               'scroll accel cmd'),
    'controls': ('controls: buttons, lists, combo and check boxes, edit fields, scroll bars',
                 'ctrl control scrollbar listbox combo checkbox radiogrp edit button spritebtn ddctrl input'),
    'graphics': ('graphics: sprites, surfaces, palettes, fonts',
                 'sprite gfx surface dib palette logpal font icons icon rect portrait small bitmap screen gif '
                 'gdi ddsurf grey bits bit region'),
    'text': ('text: game text files, strings, resources and files',
             'text str strpool res file dll label labels'),
    'support': ('memory, lists, random numbers, debugging and errors',
                'dbg err error mem memblock ptrlist int win rng endian dist point coarse sys'),
}
PREFIX = {}
for mod, (_, prefixes) in MODULES.items():
    for p in prefixes.split():
        PREFIX[p] = mod


def chunks(text):
    """[(address, chunk text)] of a file: each function from its marker on."""
    parts = re.split(r'(?m)^(?=/\* [0-9a-f]{8}[ :])', text)
    return [(c[3:11], c) for c in parts[1:]]


def name_of(chunk):
    """The name of the function a chunk defines, or None."""
    code = re.sub(r'(?m)^#.*$', '', chunk)
    code = re.sub(r'/\*.*?\*/', '', code, flags=re.S)
    m = re.search(r'\b(\w+)\s*\([^;{}]*\)\s*\{', code)
    return m.group(1) if m else None


def module_of(name):
    if not name:
        return None
    if name.startswith('_') or name.startswith('crt'):
        return 'crt'
    words = name.split('_')
    for k in range(len(words), 0, -1):
        p = '_'.join(words[:k])
        if p in PREFIX:
            return PREFIX[p]
    return None


def main():
    dry = '--dry-run' in sys.argv
    files = sorted(glob.glob(os.path.join(AUTO, 'blk_*.c')) + glob.glob(os.path.join(AUTO, 'crt_*.c')))
    allc = []
    for f in files:
        # the MSVC runtime (crt_*.c) stays apart: only the Windows build
        # (tools/build_recon.py) compiles it, the native builds use the C library
        runtime = os.path.basename(f).startswith('crt_')
        allc += [(a, c, runtime) for a, c in chunks(open(f).read())]
    allc.sort(key=lambda c: int(c[0], 16))
    out = collections.defaultdict(list)
    unnamed = collections.Counter()
    prev = 'game'
    for addr, c, runtime in allc:
        if runtime:
            out['msvcrt'].append(c)
            continue
        n = name_of(c)
        m = module_of(n)
        if m is None:
            unnamed[prev] += 1
            m = prev
        out[m].append(c)
        prev = m
    for m in sorted(out, key=lambda m: -len(out[m])):
        print('%-10s %5d functions (%d by neighbour)' % (m, len(out[m]), unnamed[m]))
    if dry:
        return
    for m, cs in out.items():
        desc = MODULES[m][0] if m in MODULES else {
            'crt': 'the C runtime functions the native builds also compile',
            'msvcrt': 'the MSVC C runtime (compiled for the Windows build only, tools/build_recon.py)'}[m]
        with open(os.path.join(AUTO, m + '.c'), 'w') as f:
            f.write('/* The game, %s: functions translated from the original\n * (tools/gen_c.py, now edited directly), in address order. */\n' % desc)
            f.write('#include "auto_common.h"\n\n')
            f.write(''.join(cs).rstrip('\n') + '\n')
    for f in files:
        os.remove(f)
    print('%d files -> %d modules' % (len(files), len(out)))


if __name__ == '__main__':
    main()
