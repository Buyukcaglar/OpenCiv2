#!/usr/bin/env python3
"""Hand-written code: turn absolute-address globals into paths into the game
data struct `g` (src/data/gamedata.h), so the code no longer depends on the
original memory layout.

    #define name (*(T *)0x006xxxxx)   -> #define name (*(T *)<g path>)
    GLOBAL(T, 0x006xxxxx)             -> (*(T *)<g path>)
"""
import glob, re, sys
sys.path.insert(0, 'tools')
import gen_c

for path in sorted(glob.glob('src/game/*.c') + glob.glob('src/crt/*.c')):
    t = orig = open(path).read()
    t = re.sub(r'(#define \w+ \(\*\([^()]*\*\))0x(00[56][0-9a-f]{5})\)',
               lambda m: m.group(1) + gen_c.data_location(int(m.group(2), 16)) + ')', t)
    t = re.sub(r'\bGLOBAL\(\s*([^,]+?)\s*,\s*0x(00[56][0-9a-f]{5})\s*\)',
               lambda m: '(*(%s *)%s)' % (m.group(1), gen_c.data_location(int(m.group(2), 16))), t)
    if t != orig:
        open(path, 'w').write(t)
        print('rehomed', path)
