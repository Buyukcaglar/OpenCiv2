#!/usr/bin/env python3
"""Build civ2_recon.exe: the original executable with reconstructed functions
grafted in.  Runs inside the civ2-dev container.

Pipeline
  1. compile every source file under src/ to assembly (gcc -S)
  2. rename each function definition FOO to FOO__impl, so that every *call*
     (from original or reconstructed code) still targets the original entry
     address; the entry is then patched to jump to FOO__impl.  This keeps every
     function independently switchable, which is what makes bisecting a
     behavioural difference possible.
  3. link at a fixed address (RECON_BASE) with PROVIDE() fallbacks that bind
     every symbol we do not define to its address in the original image:
     original functions, thunks, globals, and import-table slots.
  4. append the linked image to a copy of civ2.exe as a new section and patch
     the entries of the enabled functions.

Usage: build_recon.py [--only ADDR,ADDR...] [--exclude-file FILE] [--out PATH]
"""
import argparse
import json
import glob
import os
import re
import struct
import subprocess
import sys

import pefile
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import paths  # noqa: E402  (the game's directory)

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BUILD = os.environ.get('CIV2_BUILD_DIR') or os.path.join(ROOT, 'build', 'recon')
CC = 'i686-w64-mingw32-gcc'
AS = 'i686-w64-mingw32-as'
LD = 'i686-w64-mingw32-ld'
OBJCOPY = 'i686-w64-mingw32-objcopy'
NM = 'i686-w64-mingw32-nm'
IMAGE_BASE = 0x400000
RECON_BASE = 0x00800000          # VA where the grafted code/data is linked
CFLAGS = ['-std=gnu89', '-O1', '-fno-omit-frame-pointer', '-fno-inline', '-fno-optimize-sibling-calls', '-fno-strict-aliasing',
          '-fwrapv', '-ffloat-store', '-fno-builtin', '-fno-asynchronous-unwind-tables',
          '-fno-stack-protector', '-fcf-protection=none',
          '-w', '-I', os.path.join(ROOT, 'src', 'include'), '-I', os.path.join(ROOT, 'src', 'auto'),
          '-I', os.path.join(ROOT, 'tools')]


def run(cmd, **kw):
    r = subprocess.run(cmd, capture_output=True, text=True, **kw)
    if r.returncode:
        sys.stderr.write(r.stdout + r.stderr)
        raise SystemExit('command failed: ' + ' '.join(cmd[:4]))
    return r.stdout


def symbol_addresses():
    """Map plain symbol name -> original address for functions, thunks, globals."""
    import csv
    addrs = {}
    for r in csv.DictReader(open(os.path.join(ROOT, 're', 'functions.tsv')), delimiter='\t'):
        addrs[r['name']] = int(r['entry'], 16)
    for r in csv.DictReader(open(os.path.join(ROOT, 're', 'symbols.tsv')), delimiter='\t'):
        if r['kind'] == 'data':
            addrs[r['name']] = int(r['addr'], 16)
    addrs['g'] = 0x0061c000          # the game data struct (src/data/gamedata.h)
    return addrs


def iat_slots(pe):
    """Map imported API name -> IAT slot address in the original image."""
    slots = {}
    for e in pe.DIRECTORY_ENTRY_IMPORT:
        for imp in e.imports:
            if not imp.name:
                slots['Ordinal_%d' % imp.ordinal] = imp.address
            if imp.name:
                name = imp.name.decode()
                if name.startswith('?'):          # C++-mangled (XDaemon): ?XD_Foo@@YA...
                    name = name[1:].split('@@')[0]
                slots[name] = imp.address
    return slots


DEF_LABEL = re.compile(r'^(_[A-Za-z_]\w*(?:@\d+)?):', re.M)


def rename_definitions(asm, known):
    """FOO: -> FOO__impl: (and its .globl/.def) for original functions."""
    defs = []
    for m in DEF_LABEL.finditer(asm):
        sym = m.group(1)
        plain = undecorate(sym)
        if plain in known:
            defs.append(sym)
    for sym in defs:
        impl = impl_name(sym)
        asm = re.sub(r'^%s:' % re.escape(sym), impl + ':', asm, flags=re.M)
        asm = re.sub(r'(\.globl\s+)%s$' % re.escape(sym), r'\g<1>' + impl, asm, flags=re.M)
        asm = re.sub(r'(\.def\s+)%s;' % re.escape(sym), r'\g<1>' + impl + ';', asm, flags=re.M)
    return asm, defs


def undecorate(sym):
    s = sym[1:] if sym.startswith('_') else sym
    return s.split('@')[0]


def impl_name(sym):
    base, _, at = sym.partition('@')
    return base + '__impl' + ('@' + at if at else '')


FUNC_MARK = re.compile(r'^/\* ([0-9a-f]{8}) ', re.M)


def failing_functions(src, stderr):
    """Map compiler error lines back to the function markers gen_c.py emits."""
    text = open(src).read()
    starts = [(text.count('\n', 0, m.start()) + 1, m.group(1)) for m in FUNC_MARK.finditer(text)]
    bad = {}
    for m in re.finditer(r'^%s:(\d+):\d+: error: (.*)$' % re.escape(src), stderr, re.M):
        line = int(m.group(1))
        owner = None
        for l, a in starts:
            if l <= line:
                owner = a
            else:
                break
        if owner:
            bad.setdefault(owner, m.group(2))
    return bad


def compile_all(sources, known, keep_going=False):
    os.makedirs(BUILD, exist_ok=True)
    objs, impls = [], {}
    failures = {}
    for src in sources:
        stem = os.path.splitext(os.path.relpath(src, ROOT))[0].replace('/', '_')
        s_path = os.path.join(BUILD, stem + '.s')
        o_path = os.path.join(BUILD, stem + '.o')
        if not (os.path.exists(o_path) and os.path.getmtime(o_path) > newest_input(src)):
            r = subprocess.run([CC, '-S', '-o', s_path, src] + CFLAGS, capture_output=True, text=True)
            if r.returncode:
                bad = failing_functions(src, r.stderr)
                if not keep_going or not bad:
                    sys.stderr.write(r.stderr[-8000:])
                    raise SystemExit('compile failed: ' + src)
                failures.update(bad)
                if os.path.exists(o_path):
                    os.remove(o_path)
                continue
            asm, defs = rename_definitions(open(s_path).read(), known)
            open(s_path, 'w').write(asm)
            run([AS, '--32', '-o', o_path, s_path])
        objs.append(o_path)
    # Collect the __impl symbols actually defined.
    for o in objs:
        for line in run([NM, '--defined-only', o]).splitlines():
            parts = line.split()
            if len(parts) == 3 and parts[1] in 'Tt' and '__impl' in parts[2]:
                impls[undecorate(parts[2].replace('__impl', ''))] = parts[2]
    return objs, impls, failures


_headers = None


def newest_input(src):
    global _headers
    if _headers is None:
        _headers = max([os.path.getmtime(p) for p in glob.glob(os.path.join(ROOT, 'src', '**', '*.h'), recursive=True)] +
                       [os.path.getmtime(os.path.join(ROOT, 'tools', 'ghidra.h')),
                        os.path.getmtime(os.path.abspath(__file__))])
    return max(os.path.getmtime(src), _headers)


def link(objs, addrs, iat, pe):
    # First pass: find undefined symbols.
    undefined = set()
    for o in objs:
        for line in run([NM, '-u', o]).splitlines():
            undefined.add(line.split()[-1])
    provides = []
    missing = []
    stubs = []
    for sym in sorted(undefined):
        plain = undecorate(sym)
        if sym.startswith('__imp__'):
            api = undecorate(sym[len('__imp_'):])
            if api in iat:
                provides.append('PROVIDE("%s" = 0x%08x);' % (sym, iat[api]))
                continue
        if plain in addrs:
            provides.append('PROVIDE("%s" = 0x%08x);' % (sym, addrs[plain]))
            continue
        if plain in iat:
            stubs.append(sym)
            continue
        missing.append(sym)
    # Symbols nobody provides (libgcc helpers aside): record them so the
    # generator can demote the functions that reference them, and stop.
    libgcc_helpers = {'___divdi3', '___udivdi3', '___moddi3', '___umoddi3', '___divmoddi4', '___udivmoddi4'}
    unresolved = sorted(undecorate(m) for m in missing if m not in libgcc_helpers)
    if unresolved:
        path = os.path.join(ROOT, 're', 'unresolved.txt')
        known = set(open(path).read().split()) if os.path.exists(path) else set()
        new = set(unresolved) - known
        with open(path, 'w') as f:
            f.write('\n'.join(sorted(known | set(unresolved))) + '\n')
        if new:
            print('unresolved symbols recorded in re/unresolved.txt: %s' % ' '.join(sorted(new)))
            raise SystemExit(2)
    if stubs:
        # Direct calls to imported APIs: jump through the original import slot.
        stub_s = os.path.join(BUILD, 'import_stubs.s')
        with open(stub_s, 'w') as f:
            f.write('\t.text\n')
            for sym in stubs:
                f.write('\t.globl %s\n%s:\n\tjmp *0x%08x\n' % (sym, sym, iat[undecorate(sym)]))
        stub_o = os.path.join(BUILD, 'import_stubs.o')
        run([AS, '--32', '-o', stub_o, stub_s])
        objs = objs + [stub_o]
    libgcc = run([CC, '-print-libgcc-file-name']).strip()
    script = os.path.join(BUILD, 'recon.ld')
    with open(script, 'w') as f:
        f.write('SECTIONS {\n  . = 0x%08x;\n' % RECON_BASE)
        f.write('  .text : { *(.text*) }\n  .rdata : { *(.rdata*) *(.rodata*) }\n')
        f.write('  .data : { *(.data*) }\n  .bss : { *(.bss*) *(COMMON) }\n')
        f.write('  /DISCARD/ : { *(.drectve) *(.debug*) *(.eh_frame*) *(.pdata) *(.xdata) *(.reloc) }\n}\n')
        f.write('\n'.join(provides) + '\n')
    out = os.path.join(BUILD, 'recon.elf')
    r = subprocess.run([LD, '-m', 'i386pe', '-T', script, '--image-base', '0', '-o', out] + objs + [libgcc],
                       capture_output=True, text=True)
    if r.returncode:
        sys.stderr.write(r.stderr[-6000:])
        raise SystemExit('link failed')
    return out, missing


def section_bytes(linked):
    """Flatten the linked image into one blob starting at RECON_BASE."""
    blob = os.path.join(BUILD, 'recon.bin')
    run([OBJCOPY, '-O', 'binary', linked, blob])
    data = open(blob, 'rb').read()
    syms = {}
    for line in run([NM, linked]).splitlines():
        parts = line.split()
        if len(parts) == 3:
            syms[parts[2]] = int(parts[0], 16)
    # objcopy -O binary starts at the lowest section address.
    lowest = min(v for k, v in syms.items() if v >= RECON_BASE) if syms else RECON_BASE
    return data, syms


def graft(orig_path, out_path, blob, patches, wipe=None):
    pe = pefile.PE(orig_path)
    data = bytearray(open(orig_path, 'rb').read())
    sec_align = pe.OPTIONAL_HEADER.SectionAlignment
    file_align = pe.OPTIONAL_HEADER.FileAlignment
    last = pe.sections[-1]
    va = RECON_BASE - IMAGE_BASE
    if va < last.VirtualAddress + last.Misc_VirtualSize:
        raise SystemExit('RECON_BASE overlaps original image')
    # New section header right after the last one.
    hdr_off = last.get_file_offset() + 40
    if hdr_off + 40 > pe.sections[0].PointerToRawData:
        raise SystemExit('no room for another section header')
    raw_off = (len(data) + file_align - 1) // file_align * file_align
    raw_size = (len(blob) + 0x10000 + file_align - 1) // file_align * file_align  # slack for .bss
    vsize = raw_size
    hdr = struct.pack('<8sIIIIIIHHI', b'.recon\0\0', vsize, va, raw_size, raw_off, 0, 0, 0, 0,
                      0xE0000060)  # code | initialized data | exec | read | write
    data[hdr_off:hdr_off + 40] = hdr
    # NumberOfSections and SizeOfImage
    fh = pe.DOS_HEADER.e_lfanew + 4
    struct.pack_into('<H', data, fh + 2, pe.FILE_HEADER.NumberOfSections + 1)
    oh = fh + 20
    size_of_image = (va + vsize + sec_align - 1) // sec_align * sec_align
    struct.pack_into('<I', data, oh + 56, size_of_image)
    data[len(data):] = b'\0' * (raw_off - len(data))
    data += blob + b'\0' * (raw_size - len(blob))
    if wipe is not None:
        # Standalone check: no original instruction may run.  Fill the code
        # sections with int3, then re-create only the incremental-link thunks
        # (jmp to their target) and, below, the entry jumps.
        for sec in pe.sections:
            if sec.Name.rstrip(b'\0') in (b'.text', b'ASMGRAF'):
                off = sec.PointerToRawData
                data[off:off + sec.SizeOfRawData] = b'\xcc' * sec.SizeOfRawData
        # The incremental-link table (0x401000, 5-byte jmp slots) is kept
        # verbatim: it holds no code of its own, only jumps to function
        # entries, and Ghidra does not list every slot as a function.
        orig_bytes = open(orig_path, 'rb').read()
        va = 0x401000
        while True:
            off = pe.get_offset_from_rva(va - IMAGE_BASE)
            if orig_bytes[off] != 0xE9:
                break
            data[off:off + 5] = orig_bytes[off:off + 5]
            va += 5
        # Import stubs (jmp [IAT]) are kept too: they only enter a DLL.
        import csv as _csv
        for r in _csv.DictReader(open(os.path.join(ROOT, 're', 'functions.tsv')), delimiter='\t'):
            if r['thunk_target'].startswith('EXTERNAL'):
                off = pe.get_offset_from_rva(int(r['entry'], 16) - IMAGE_BASE)
                data[off:off + 6] = orig_bytes[off:off + 6]
        for thunk_va, target_va in wipe:
            off = pe.get_offset_from_rva(thunk_va - IMAGE_BASE)
            data[off:off + 5] = b'\xE9' + struct.pack('<I', (target_va - (thunk_va + 5)) & 0xffffffff)
    # Entry patches: jmp rel32 from original function entry to the reconstruction.
    for orig_va, target_va in patches:
        off = pe.get_offset_from_rva(orig_va - IMAGE_BASE)
        rel = (target_va - (orig_va + 5)) & 0xffffffff
        data[off:off + 5] = b'\xE9' + struct.pack('<I', rel)
    open(out_path, 'wb').write(data)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--out', default=os.path.join(ROOT, 'build', 'civ2_recon.exe'))
    ap.add_argument('--only', help='comma-separated hex addresses to enable (default: all built)')
    ap.add_argument('--only-file', help='file with hex addresses to enable (one per line)')
    ap.add_argument('--exclude', help='comma-separated hex addresses to leave original')
    ap.add_argument('--exclude-file', help='file with hex addresses (one per line) to leave original')
    ap.add_argument('--keep-going', action='store_true', help='record failing functions instead of stopping')
    ap.add_argument('--wipe', action='store_true',
                    help='replace all original code with int3 (proves nothing original runs)')
    ap.add_argument('--patch-only', action='store_true', help='reuse the last link, only re-patch entries')
    args = ap.parse_args()

    orig = paths.game_file('civ2.exe')
    pe = pefile.PE(orig)
    addrs = symbol_addresses()
    known = set(addrs)
    state_path = os.path.join(BUILD, 'state.json')
    if args.patch_only:
        # Reuse the last link; only change which entries are patched.
        st = json.load(open(state_path))
        impls, syms = st['impls'], st['syms']
        blob = open(os.path.join(BUILD, 'recon.bin'), 'rb').read()
    else:
        sources = sorted(glob.glob(os.path.join(ROOT, 'src', 'auto', '*.c')) +
                         glob.glob(os.path.join(ROOT, 'src', 'game', '**', '*.c'), recursive=True) +
                         glob.glob(os.path.join(ROOT, 'src', 'crt', '*.c')))
        objs, impls, failures = compile_all(sources, known, args.keep_going)
        if failures:
            with open(os.path.join(ROOT, 're', 'compile_failures.tsv'), 'a') as f:
                for a, err in sorted(failures.items()):
                    f.write('%s\t%s\n' % (a, err.replace('\t', ' ')))
            print('%d functions failed to compile (appended to re/compile_failures.tsv)' % len(failures))
            raise SystemExit(2)
        linked, missing = link(objs, addrs, iat_slots(pe), pe)
        if missing:
            print('unresolved symbols (%d): %s' % (len(missing), ' '.join(missing[:40])))
        blob, syms = section_bytes(linked)
        with open(os.path.join(BUILD, 'recon.map'), 'w') as f:
            for name, va in sorted(syms.items(), key=lambda kv: kv[1]):
                if va >= RECON_BASE:
                    f.write('%08x %s\n' % (va, name))
        json.dump({'impls': impls, 'syms': syms}, open(state_path, 'w'))

    enabled = set(impls)
    if args.only_file:
        args.only = ','.join(l.split()[0] for l in open(args.only_file) if l.strip() and not l.startswith('#'))
    if args.only:
        only = {int(x, 16) for x in args.only.split(',') if x}
        enabled = {n for n in enabled if addrs.get(n) in only}
    excl = set()
    if args.exclude:
        excl |= {int(x, 16) for x in args.exclude.split(',') if x}
    if args.exclude_file:
        excl |= {int(l.split()[0], 16) for l in open(args.exclude_file) if l.strip() and not l.startswith('#')}
    enabled = {n for n in enabled if addrs.get(n) not in excl}
    patches = []
    for n in sorted(enabled):
        patches.append((addrs[n], syms[impls[n]]))
    wipe = None
    if args.wipe:
        import csv
        wipe = [(int(r['entry'], 16), int(r['thunk_target'], 16))
                for r in csv.DictReader(open(os.path.join(ROOT, 're', 'functions.tsv')), delimiter='\t')
                if r['thunk_target'] and not r['thunk_target'].startswith('EXTERNAL')]
    graft(orig, args.out, blob, patches, wipe)
    with open(os.path.join(BUILD, 'enabled.txt'), 'w') as f:
        for n in sorted(enabled, key=lambda n: addrs[n]):
            f.write('%08x %s\n' % (addrs[n], n))
    print('built %s: %d reconstructed functions active, %d bytes of code' % (
        os.path.relpath(args.out, ROOT), len(patches), len(blob)))


if __name__ == '__main__':
    main()
