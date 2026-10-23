#!/usr/bin/env python3
"""Print one function: generated C (default), Ghidra output (-g) or original disassembly (-d).
Usage: show.py ADDR [-g] [-d]"""
import glob
import re, sys
import os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import paths  # noqa: E402  (the game's directory)
addr = sys.argv[1].lower().rjust(8, '0')
if '-g' in sys.argv:
    t = open('re/decomp.c').read()
    m = re.search(r'^// ==== FUNCTION %s .*?(?=^// ==== FUNCTION )' % addr, t, re.M | re.S)
    print(m.group(0) if m else 'not found')
elif '-d' in sys.argv:
    import csv, pefile, capstone
    rows = {r['entry']: r for r in csv.DictReader(open('re/functions.tsv'), delimiter='\t')}
    size = int(rows[addr]['size'])
    img = pefile.PE(paths.game_file('civ2.exe')).get_memory_mapped_image()
    a = int(addr, 16)
    for i in capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32).disasm(img[a - 0x400000:a - 0x400000 + size], a):
        print('%08x  %-8s %s' % (i.address, i.mnemonic, i.op_str))
else:
    m = None
    for f in sorted(glob.glob('src/auto/*.c')):
        m = re.search(r'^/\* %s[ :].*?(?=^/\* [0-9a-f]{8}[ :]|\Z)' % addr, open(f).read(), re.M | re.S)
        if m:
            break
    print(m.group(0) if m else 'not found')
