#!/usr/bin/env python3
"""Step 6: split the declarations of src/data/gamedata.h into a header per
subject (src/data/state/SUBJECT.h; the read-only texts in
src/data/state/strings.h, sectioned by subject).  Only declarations move:
the data keeps its layout, which gamedata.cpp's definitions (in address
order) decide.

    state_split.py

A declaration's subject is the module of src/auto (src/game: the module it
belongs with) whose code names it most; one no code names goes to misc.h.
A block keeps its records' types and the references naming them.  Run once
(on the single gamedata.h); tools/state_records.py works on that file too,
so it runs before.
"""
import collections
import glob
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from state_records import code_only     # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
HDR = os.path.join(ROOT, 'src', 'data', 'gamedata.h')
OUTDIR = os.path.join(ROOT, 'src', 'data', 'state')

SUBJECTS = [
    ('game', 'The game: its settings and the scenario, the turn, setup, saving and loading, events.'),
    ('civ', 'Civilizations and the rules (RULES.TXT): advances, governments, leaders, the rules editors\' tables.'),
    ('city', 'Cities: their calculation and production, the city window and the city view.'),
    ('unit', 'Units: moves and combat, the unit editors and unit sounds.'),
    ('ai', 'The AI\'s working state.'),
    ('diplomacy', 'Diplomacy: meetings, the AI\'s evaluation, the leaders\' screens.'),
    ('map', 'The map, world generation and path finding.'),
    ('mapview', 'The map views, the world map window and the animations on the map.'),
    ('network', 'Network play: the session, its messages, the difference engine, the parley and chat.'),
    ('reports', 'Advisors, reports, the High Council and the end-of-game screens.'),
    ('pedia', 'The Civilopedia.'),
    ('spaceship', 'The spaceship.'),
    ('editor', 'The scenario and events editors.'),
    ('window', 'Windows, dialogs and menus.'),
    ('controls', 'Controls: buttons, check boxes, radio buttons, lists, scroll bars, edit boxes.'),
    ('graphics', 'Graphics: sprites, surfaces, palettes, fonts and drawing.'),
    ('text', 'Text: the game\'s texts and labels, their arguments, the string pool, text files.'),
    ('sound', 'Sound, music and video.'),
    ('support', 'Errors, memory and debugging.'),
    ('crt', 'The MSVC runtime\'s data (src/native/crt.cpp and the runtime\'s texts).'),
    ('misc', 'Data no code names: kept so that everything else lies where the original has it.'),
]
GAME_FILES = {'lang': 'text', 'random': 'support', 'rules': 'civ', 'sound_position': 'sound',
              'throneroom': 'reports', 'timer_display': 'network', 'zz_rules_dump': 'civ',
              'crt': 'crt', 'bigframes': None, 'fixups': None, 'regargs': None, 'retvals': None, 'unwind': None}


def chunks(lines):
    """[(lines, declared names)] of the body of gamedata.h."""
    out, cur, names = [], [], []
    i = 0
    while i < len(lines):
        s = lines[i]
        cur.append(s)
        m = re.match(r'extern (?:RODATA )?(?:struct )?[^;(]*?\b(\w+)(?:\[\d+\])*;', s)
        if s.startswith('extern') and m:
            names.append(m.group(1))
            # what goes with it: its _rest, references to its parts, aliases
            while i + 1 < len(lines):
                t = lines[i + 1]
                mr = re.match(r'extern u8 (\w+)_rest\[\d+\];', t)
                if mr and mr.group(1) == m.group(1):
                    pass
                elif t.startswith('inline constexpr'):
                    names.append(re.match(r'inline constexpr \w+ &(\w+)', t).group(1))
                elif t.startswith('extern') and '*const' in t:
                    names.append(re.search(r'\(?\*const (\w+)', t).group(1))
                else:
                    break
                cur.append(t)
                i += 1
            out.append((cur, names))
            cur, names = [], []
        i += 1
    if any(s.strip() for s in cur):
        raise SystemExit('trailing lines: %r' % cur[:5])
    return out


def main():
    text = open(HDR).read()
    lines = text.split('\n')
    start = [i for i, s in enumerate(lines) if s.startswith('#endif') and 'RODATA' not in s][0] + 1
    while not lines[start].strip():
        start += 1
    end = [i for i, s in enumerate(lines) if s.startswith('/* Sets the addresses the data holds')][0]
    pre, body, post = lines[:start], lines[start:end], lines[end:]
    while body and not body[-1].strip():
        body.pop()
    ch = chunks(body)
    # usage
    files = glob.glob(os.path.join(ROOT, 'src', 'auto', '*.cpp')) + glob.glob(os.path.join(ROOT, 'src', 'game', '*.cpp')) + \
        glob.glob(os.path.join(ROOT, 'src', 'native', '*.cpp'))
    counts = collections.defaultdict(collections.Counter)
    for f in files:
        base = os.path.splitext(os.path.basename(f))[0]
        subj = base if '/src/auto/' in f else GAME_FILES.get(base, None)
        for tok in re.findall(r'[A-Za-z_]\w*', code_only(open(f).read())):
            counts[tok][subj] += 1
    by_subject = collections.defaultdict(list)
    strings = collections.defaultdict(list)
    for clines, names in ch:
        c = collections.Counter()
        for n in names:
            c.update(counts.get(n, {}))
        known = collections.Counter({k: v for k, v in c.items() if k})
        if known:
            subj = known.most_common(1)[0][0]
        elif c:
            subj = 'game'
        else:
            subj = 'misc'
        if names and names[0].startswith(('crt_', '_crt')) and subj == 'misc':
            subj = 'crt'
        if len(clines) == 1 and re.match(r'extern RODATA char str_', clines[0]):
            strings[subj].append(clines[0])
        else:
            by_subject[subj].append(clines)
    os.makedirs(OUTDIR, exist_ok=True)
    desc = dict(SUBJECTS)
    order = [s for s, _ in SUBJECTS]
    for subj in order:
        if not by_subject.get(subj):
            continue
        guard = 'CIV2_STATE_%s_H' % subj.upper()
        out = ['/* %s' % desc[subj],
               ' * Declarations only, in the original\'s address order; the definitions are in',
               ' * src/data/gamedata.cpp (see src/data/gamedata.h). */',
               '#ifndef ' + guard, '#define ' + guard, '']
        for cl in by_subject[subj]:
            out += cl
        out += ['', '#endif', '']
        open(os.path.join(OUTDIR, subj + '.h'), 'w').write('\n'.join(out))
    out = ['/* The original\'s texts (.rdata strings, read-only: RODATA), by the subject of',
           ' * the code that shows them; in address order within a subject.  The',
           ' * definitions are in src/data/gamedata.cpp. */',
           '#ifndef CIV2_STATE_STRINGS_H', '#define CIV2_STATE_STRINGS_H', '']
    for subj in order:
        if strings.get(subj):
            out += ['', '/* ---- %s ---- */' % subj] + strings[subj]
    out += ['', '#endif', '']
    open(os.path.join(OUTDIR, 'strings.h'), 'w').write('\n'.join(out))
    inc = ['/* The game\'s state, by subject (tools/state_split.py). */']
    inc += ['#include "state/%s.h"' % s for s in order if by_subject.get(s)]
    inc += ['#include "state/strings.h"', '']
    open(HDR, 'w').write('\n'.join(pre + inc + post))
    for subj in order:
        print('%-10s %4d declarations, %4d strings' % (subj, sum(len([l for l in c if l.startswith(('extern', 'inline'))]) for c in by_subject.get(subj, [])),
                                                   len(strings.get(subj, []))))


if __name__ == '__main__':
    main()
