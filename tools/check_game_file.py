#!/usr/bin/env python3
"""Compile one hand-written source file and check it against the original.

Usage (inside the civ2-dev container):  check_game_file.py src/game/foo.c

Checks, for every function the file defines:
  - its name is an original function (FUN_xxxxxxxx or a name from re/functions.tsv)
  - it pops the same number of argument bytes as the original (`ret N`)
The file is compiled with exactly the flags of tools/build_recon.py into a
private temporary directory, so this is safe to run concurrently.
"""
import csv
import os
import re
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
from build_recon import CC, CFLAGS  # noqa: E402


def main():
    src = sys.argv[1]
    names = {r['name']: int(r['entry'], 16) for r in csv.DictReader(open(os.path.join(ROOT, 're', 'functions.tsv')), delimiter='\t')}
    purge = {int(r['entry'], 16): int(r['stack_bytes']) for r in csv.DictReader(open(os.path.join(ROOT, 're', 'conventions.tsv')), delimiter='\t')}
    with tempfile.TemporaryDirectory() as tmp:
        obj = os.path.join(tmp, 'f.o')
        r = subprocess.run([CC, '-c', '-o', obj, src] + CFLAGS + ['-Wall', '-Wno-unused-variable', '-Wno-unused-function'],
                           capture_output=True, text=True)
        sys.stdout.write(r.stderr)
        if r.returncode:
            print('FAIL: does not compile')
            return 1
        dis = subprocess.run(['i686-w64-mingw32-objdump', '-d', '--no-show-raw-insn', obj], capture_output=True, text=True).stdout
    ok = True
    cur = None
    rets = {}
    for line in dis.splitlines():
        m = re.match(r'^[0-9a-f]+ <(.*)>:$', line)
        if m:
            sym = m.group(1)
            cur = (sym[1:] if sym.startswith('_') else sym).split('@')[0]
            rets[cur] = set()
            continue
        if cur and re.search(r'\tret\s*(\$0x[0-9a-f]+)?\s*$', line):
            m = re.search(r'\$0x([0-9a-f]+)', line)
            rets[cur].add(int(m.group(1), 16) if m else 0)
    for name, rs in sorted(rets.items()):
        if name not in names:
            print('note: %s is not an original function (helper?)' % name)
            continue
        want = max(purge.get(names[name], 0), 0)
        if rs != {want}:
            print('FAIL: %s pops %s bytes, original pops %d' % (name, sorted(rs), want))
            ok = False
        else:
            print('ok: %s (0x%08x) ret %d' % (name, names[name], want))
    print('PASS' if ok else 'FAIL')
    return 0 if ok else 1


if __name__ == '__main__':
    sys.exit(main())
