#!/usr/bin/env python3
"""Write build/civ2.exe from source alone — no part of orig/civ2.exe is read.

Inputs
  build/recon/recon.bin, state.json   the compiled reconstruction (tools/build_recon.py)
  re/functions.tsv                    original address of every function
  data/image/*.bin, layout.json       initialized data, import table and resources,
                                      at their original addresses
  data/image/code_map.tsv             incremental-link thunks and import stubs

The game's code refers to functions and data by their original addresses
(function pointers stored in data, absolute globals), so the image keeps the
original layout: data sections where they were, and a code section at
0x401000 that holds no code of its own, only a jump at every original
function entry into the compiled reconstruction (linked at 0x800000).
"""
import csv
import json
import os
import struct

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BUILD = os.path.join(ROOT, 'build', 'recon')
IMAGE_BASE = 0x400000
RECON_BASE = 0x800000
TEXT_VA, TEXT_END = 0x1000, 0x21C000
SECT_ALIGN, FILE_ALIGN, HEADERS = 0x1000, 0x200, 0x400


def align(v, a):
    return (v + a - 1) // a * a


def jmp(at, to):
    return b'\xE9' + struct.pack('<i', to - (at + 5))


def main():
    layout = json.load(open(os.path.join(ROOT, 'data', 'image', 'layout.json')))
    st = json.load(open(os.path.join(BUILD, 'state.json')))
    impls, syms = st['impls'], st['syms']
    blob = open(os.path.join(BUILD, 'recon.bin'), 'rb').read()
    addrs = {r['name']: int(r['entry'], 16) for r in
             csv.DictReader(open(os.path.join(ROOT, 're', 'functions.tsv')), delimiter='\t')}

    # Code section: int3 everywhere, jumps at the original entry points.
    text = bytearray(b'\xCC' * (TEXT_END - TEXT_VA))

    def put(va, code):
        off = va - IMAGE_BASE - TEXT_VA
        text[off:off + len(code)] = code

    for line in open(os.path.join(ROOT, 'data', 'image', 'code_map.tsv')):
        if line.startswith('#'):
            continue
        kind, at, target = line.split()
        at, target = int(at, 16), int(target, 16)
        if kind == 'thunk':
            put(at, jmp(at, target))
        else:                                   # import stub: jmp [IAT slot]
            put(at, b'\xFF\x25' + struct.pack('<I', target))
    missing = []
    for name, impl in impls.items():
        put(addrs[name], jmp(addrs[name], syms[impl]))
    entry = syms.get('_entry__impl')
    if entry is None:
        raise SystemExit('the C runtime entry point is not reconstructed')

    # Sections in address order; gaps are filled with uninitialized space
    # (the PE loader wants contiguous sections).
    sections = [('.text', TEXT_VA, len(text), bytes(text), 0x60000020)]
    for s in layout['sections']:
        raw = open(os.path.join(ROOT, s['file']), 'rb').read()
        sections.append((s['name'], s['va'], max(s['vsize'], len(raw)), raw, s['flags']))
    recon_va = RECON_BASE - IMAGE_BASE
    end = align(sections[-1][1] + sections[-1][2], SECT_ALIGN)
    if end < recon_va:
        sections.append(('.gap', end, recon_va - end, b'', 0xC0000080))
    sections.append(('.recon', recon_va, len(blob) + 0x10000, blob, 0xE0000060))

    nsec = len(sections)
    out = bytearray(HEADERS)
    pos = HEADERS
    headers = []
    for name, va, vsize, raw, flags in sections:
        rawsize = align(len(raw), FILE_ALIGN)
        headers.append(struct.pack('<8sIIIIIIHHI', name.encode().ljust(8, b'\0'), vsize, va,
                                   rawsize, pos if rawsize else 0, 0, 0, 0, 0, flags))
        if rawsize:
            out += raw + b'\0' * (rawsize - len(raw))
            pos += rawsize
    size_of_image = align(sections[-1][1] + sections[-1][2], SECT_ALIGN)

    o = layout['optional']
    dirs = [(0, 0)] * 16
    names = ['EXPORT', 'IMPORT', 'RESOURCE', 'EXCEPTION', 'SECURITY', 'BASERELOC', 'DEBUG', 'COPYRIGHT',
             'GLOBALPTR', 'TLS', 'LOAD_CONFIG', 'BOUND_IMPORT', 'IAT']
    for k, (rva, size) in layout['dirs'].items():
        key = k.replace('IMAGE_DIRECTORY_ENTRY_', '')
        if key in ('IMPORT', 'RESOURCE', 'IAT'):
            dirs[names.index(key)] = (rva, size)

    dos = bytearray(0x40)
    dos[0:2] = b'MZ'
    struct.pack_into('<I', dos, 0x3C, 0x40)
    coff = struct.pack('<HHIIIHH', 0x14C, nsec, 0, 0, 0, 0xE0, 0x010F)
    opt = struct.pack('<HBBIIIIIIIIIHHHHHHIIIIHHIIIIII',
                      0x10B, 4, 20, len(text), 0, 0, entry - IMAGE_BASE, TEXT_VA, 0x21C000,
                      IMAGE_BASE, SECT_ALIGN, FILE_ALIGN,
                      o['MajorOperatingSystemVersion'], o['MinorOperatingSystemVersion'], 0, 0,
                      o['MajorSubsystemVersion'], o['MinorSubsystemVersion'], 0,
                      size_of_image, HEADERS, 0, o['Subsystem'], 0,
                      o['SizeOfStackReserve'], o['SizeOfStackCommit'],
                      o['SizeOfHeapReserve'], o['SizeOfHeapCommit'], 0, 16)
    opt += b''.join(struct.pack('<II', *d) for d in dirs)
    hdr = bytes(dos) + b'PE\0\0' + coff + opt + b''.join(headers)
    assert len(hdr) <= HEADERS
    out[0:len(hdr)] = hdr
    path = os.path.join(ROOT, 'build', 'civ2.exe')
    open(path, 'wb').write(out)
    print('wrote build/civ2.exe: %d bytes, %d functions, entry 0x%08x' % (len(out), len(impls), entry))


if __name__ == '__main__':
    main()
