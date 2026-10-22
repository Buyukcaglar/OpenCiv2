#!/usr/bin/env python3
"""Recover the field layout of a global array of structs from the machine code.

Usage: fields.py BASE STRIDE COUNT        (hex BASE/STRIDE, decimal COUNT)

Scans every instruction of the original program for memory operands whose
absolute displacement falls inside one element of the array and that are
indexed (base/index register present) — i.e. accesses of the form
array[i].field — and reports, per offset, the access sizes seen and how many
functions use it.  Also lists functions that touch the array, as a starting
point for naming them.
"""
import collections
import csv
import sys

import capstone
import pefile
from capstone import x86
import os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import paths  # noqa: E402  (the game's directory)

BASE = 0x400000


def main():
    base, stride, count = int(sys.argv[1], 16), int(sys.argv[2], 16), int(sys.argv[3])
    pe = pefile.PE(paths.game_file('civ2.exe'))
    img = pe.get_memory_mapped_image()
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    rows = [r for r in csv.DictReader(open('re/functions.tsv'), delimiter='\t') if not r['thunk_target']]
    sizes = collections.defaultdict(collections.Counter)
    funcs = collections.defaultdict(set)
    direct = collections.Counter()
    for r in rows:
        a = int(r['entry'], 16)
        for ins in md.disasm(img[a - BASE:a - BASE + int(r['size'])], a):
            for op in ins.operands:
                if op.type != x86.X86_OP_MEM:
                    continue
                d = op.mem.disp & 0xffffffff
                if base <= d < base + stride * count:
                    off = (d - base) % stride if (op.mem.base or op.mem.index) else d - base
                    if op.mem.base or op.mem.index:
                        sizes[off][op.size] += 1
                        funcs[off].add(r['entry'])
                    else:
                        direct[d - base] += 1
    print('offset  sizes            functions')
    for off in sorted(sizes):
        print('+0x%02x   %-16s %d' % (off, dict(sizes[off]), len(funcs[off])))
    if direct:
        print('direct (non-indexed) accesses:', ', '.join('+0x%x' % o for o in sorted(direct)[:20]))


if __name__ == '__main__':
    main()
