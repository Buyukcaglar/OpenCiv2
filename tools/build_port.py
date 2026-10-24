#!/usr/bin/env python3
"""The portable build: the game and the platform layer compiled to a
wasm32 module (build_native.py --target wasm), turned into C by wasm2c,
then compiled for the machine at hand with the host runtime (src/host:
SDL2 and WASI) -- a native program for any 64-bit (or 32-bit) system,
keeping the original's 32-bit data model.

Steps (each can run on its own):
  module   build/wasm/civ2.wasm            (needs wasi-sdk and the installed game)
  c        build/wasm/c/civ2_wasm*.c,.h    (needs wabt's wasm2c)
  exe      build/civ2-port                 (needs a C compiler and SDL2; on Windows
                                           (MSYS2) Civ2RE.exe and SDL2.dll)
  exe-windows  build/Civ2RE.exe            cross-compiled with MinGW-w64 (e.g. on
                                           Linux; tools/fetch-toolchain.sh windows)
  pack     dist/civ2-port-src.tar.gz       what the exe step needs on another
                                           machine, plus the data and run script

The c step's output is plain C: copy build/wasm/c and src/host to another
machine and run only the exe step there (the pack step bundles it).

Usage: build_port.py [module] [c] [exe] [exe-windows] [pack]   (default: module c exe)
wasi-sdk and wabt: tools/fetch-toolchain.sh downloads them (or set WASI_SDK
and WABT; see tools/paths.py).  Environment: CC (default cc; on macOS the
Command Line Tools' clang), JOBS.
"""
import concurrent.futures
import glob
import os
import re
import shutil
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import paths  # noqa: E402

ROOT = paths.ROOT
WASM = os.path.join(ROOT, 'build', 'wasm')
CDIR = os.path.join(WASM, 'c')
OBJ = os.path.join(WASM, 'obj')
PARTS = 8


def run(cmd, **kw):
    print(' '.join(cmd) if len(cmd) < 12 else ' '.join(cmd[:10]) + ' ...', flush=True)
    subprocess.run(cmd, check=True, **kw)


def module():
    run([sys.executable, os.path.join(ROOT, 'tools', 'build_native.py'), '--target', 'wasm'])


def to_c():
    os.makedirs(CDIR, exist_ok=True)
    for f in glob.glob(os.path.join(CDIR, 'civ2_wasm*')):
        os.remove(f)
    wasm2c = os.path.join(paths.WABT, 'bin', 'wasm2c')
    if not os.path.exists(wasm2c) and os.path.exists(wasm2c + '.exe'):
        wasm2c += '.exe'
    run([wasm2c if os.path.exists(wasm2c) else 'wasm2c', os.path.join(WASM, 'civ2.wasm'), '-n', 'civ2', '--num-outputs=%d' % PARTS,
         '-o', os.path.join(CDIR, 'civ2_wasm.c')])
    # Calls clang could only make by casting a function to another type
    # become traps; the code must not have any.
    bad = sorted(set(re.findall(r'w2c_civ2_0x2EL(\w+)_bitcast_invalid', ''.join(
        open(f).read() for f in glob.glob(os.path.join(CDIR, 'civ2_wasm_*.c'))))))
    if bad:
        sys.exit('calls through casts to incompatible types (trap in wasm): %s' % ' '.join(bad))
    # Indirect calls: the decompiled code calls through function pointers
    # of other types than their targets (as the original freely did on x86,
    # e.g. constructors returning `this` called as returning nothing).  wasm
    # traps on that; here such calls go ahead, with the host ABI's
    # tolerance, like the original's.  Table bounds are still checked.
    impl = os.path.join(CDIR, 'civ2_wasm-impl.h')
    text = open(impl).read()
    old = '(LIKELY((x) < table.size && table.data[x].func &&      \\\n          func_types_eq(ft, table.data[x].func_type)) || \\\n'
    new = '(LIKELY((x) < table.size && table.data[x].func) ||      \\\n'
    if old not in text:
        sys.exit('wasm2c output: CHECK_CALL_INDIRECT not found as expected')
    open(impl, 'w').write(text.replace(old, new))
    # the runtime wasm2c's output needs, so the directory is self-contained
    rt = os.path.join(paths.WABT, 'share', 'wabt', 'wasm2c')
    inc = os.path.join(paths.WABT, 'include')
    for f in glob.glob(os.path.join(rt, '*.[ch]')) + glob.glob(os.path.join(rt, '*.inc')) + glob.glob(os.path.join(inc, 'wasm-rt*.h')):
        shutil.copy(f, CDIR)


def default_cc():
    """cc; on macOS Apple's clang driver (/usr/bin/clang) using the Command
    Line Tools when they are installed, so that compiler, linker and SDK
    match (an older Xcode's linker fails on a newer SDK with "unknown
    architecture" in .tbd files)."""
    clt = '/Library/Developer/CommandLineTools'
    if sys.platform == 'darwin' and os.path.isdir(clt) and 'DEVELOPER_DIR' not in os.environ:
        os.environ['DEVELOPER_DIR'] = clt
        return '/usr/bin/clang'
    return 'cc'


def on_windows():
    return sys.platform == 'win32' or bool(os.environ.get('MSYSTEM'))


def windows_resources(cc, obj):
    """src/host/res/civ2-port.rc compiled: the icon, the manifest, and as
    RCDATA the program's own files GameData gets (src/host/setup_files.c):
    the fonts (data/native) and CIV2.DAT (harness), each 8 bytes of size
    and the file xz-compressed."""
    import lzma
    res = os.path.join(obj, 'res')
    os.makedirs(res, exist_ok=True)
    for src in (os.path.join(ROOT, 'data', 'native', 'fonts.bin'), os.path.join(ROOT, 'data', 'native', 'fonts_aa.bin'),
                os.path.join(ROOT, 'harness', 'CIV2.DAT')):
        out = os.path.join(res, os.path.basename(src) + '.xzs')
        if not os.path.exists(out) or os.path.getmtime(out) < os.path.getmtime(src):
            print('compressing %s' % os.path.relpath(src, ROOT), flush=True)
            data = open(src, 'rb').read()
            open(out, 'wb').write(len(data).to_bytes(8, 'little') + lzma.compress(data, preset=9 | lzma.PRESET_EXTREME))
    rc = os.path.join(ROOT, 'src', 'host', 'res', 'civ2-port.rc')
    o = os.path.join(obj, 'civ2-port.res.o')
    windres = os.environ.get('WINDRES')
    if not windres:
        base = os.path.basename(cc)
        windres = (cc[:-len(base)] + base[:base.rindex('-gcc')] + '-windres') if '-gcc' in base else 'windres'
    newer = max(os.path.getmtime(f) for f in glob.glob(os.path.join(ROOT, 'src', 'host', 'res', '*')) +
                glob.glob(os.path.join(res, '*')))
    if not os.path.exists(o) or os.path.getmtime(o) < newer:
        run([windres, '-I', os.path.dirname(rc), '-I', res, '-O', 'coff', '-i', rc, '-o', o])
    return o


def exe(cross_windows=False):
    """build/civ2-port: compile the generated C with the host runtime.
    cross_windows: build/Civ2RE.exe with MinGW-w64 and SDL2's MinGW
    release (tools/fetch-toolchain.sh windows), e.g. on Linux."""
    windows = cross_windows or on_windows()
    if cross_windows:
        cc = os.environ.get('CC') or 'x86_64-w64-mingw32-gcc'
        sdl = os.path.join(paths.SDL2_MINGW, 'x86_64-w64-mingw32')
        sdl_cflags = ['-I' + os.path.join(sdl, 'include', 'SDL2'), '-Dmain=SDL_main']
        # (-mwindows: a GUI program, no console window; as sdl2-config gives
        # on MSYS2.)  SDL2 linked in: the program is one file, beside GameData.
        sdl_libs = ['-L' + os.path.join(sdl, 'lib'), '-lmingw32', '-mwindows', '-lSDL2main',
                    '-Wl,-Bstatic', '-lSDL2', '-Wl,-Bdynamic', '-lsetupapi', '-lwinmm', '-limm32', '-lversion',
                    '-loleaut32', '-lcfgmgr32', '-lgdi32']
        sdl_dll = None
        obj = OBJ + '-windows'
    else:
        cc = os.environ.get('CC') or default_cc()
        sdl = subprocess.run(['sdl2-config', '--cflags', '--libs'], capture_output=True, text=True,
                             check=True).stdout.split()
        sdl_cflags = [f for f in sdl if f.startswith(('-I', '-D'))]
        sdl_libs = [f for f in sdl if not f.startswith(('-I', '-D'))]
        sdl_dll = None
        if windows:     # MSYS2: the DLL next to sdl2-config
            prefix = subprocess.run(['sdl2-config', '--prefix'], capture_output=True, text=True).stdout.strip()
            sdl_dll = os.path.join(prefix, 'bin', 'SDL2.dll')
        obj = OBJ
    os.makedirs(obj, exist_ok=True)
    # wasm2c's output: optimized (it is the whole game); no strict aliasing
    # assumptions across the module's memory.
    gen = sorted(glob.glob(os.path.join(CDIR, 'civ2_wasm*.c')))
    rt = [os.path.join(CDIR, f) for f in ('wasm-rt-impl.c', 'wasm-rt-mem-impl.c', 'wasm-rt-exceptions-impl.c')]
    # (the native menu bar: Win32 on Windows, Cocoa on macOS)
    mac = sys.platform == 'darwin' and not cross_windows
    # (Windows: the set-up of GameData from the user's copy of the game, the
    # light and dark mode of the program's windows: src/host/setup.h)
    host = [os.path.join(ROOT, 'src', 'host', f) for f in
            ('port_main.c', 'wasi.c', 'host_sdl.c') +
            (('host_menu_win.c', 'darkmode_win.c', 'setup_win.c', 'setup_files.c', 'setup_manifest.c', 'sha256.c')
             if windows else ()) +
            (('host_menu_mac.m',) if mac else ())]
    deps = ['-I' + os.path.join(paths.DEPS_WINDOWS, 'include'), '-DLIBARCHIVE_STATIC'] if windows else []
    if windows and not os.path.exists(os.path.join(paths.DEPS_WINDOWS, 'lib', 'libarchive.a')):
        sys.exit('the set-up libraries are not built: run tools/build_deps.py (see README)')
    jobs = [(s, ['-O2', '-fno-strict-aliasing', '-w']) for s in gen + rt] + \
           [(s, ['-O2', '-Wall', '-Werror=implicit-function-declaration'] + sdl_cflags + deps +
             (['-fobjc-arc'] if s.endswith('.m') else [])) for s in host]
    headers = max(os.path.getmtime(h) for h in glob.glob(os.path.join(ROOT, 'src', 'host', '*.h')))

    def compile_one(job):
        src, flags = job
        o = os.path.join(obj, os.path.basename(src) + '.o')
        newer = max(os.path.getmtime(src), headers if src in host else 0)
        if not os.path.exists(o) or os.path.getmtime(o) < newer:
            subprocess.run([cc, '-c', '-o', o, src, '-I', CDIR, '-I', os.path.join(ROOT, 'src', 'host')] + flags,
                           check=True)
        return o
    # Few at a time: the generated files are large.
    with concurrent.futures.ThreadPoolExecutor(int(os.environ.get('JOBS', '2'))) as ex:
        objs = list(ex.map(compile_one, jobs))
    # (Windows: the program as published, Civ2RE.exe)
    out = os.path.join(ROOT, 'build', 'Civ2RE.exe' if windows else 'civ2-port')
    # (Windows: the C runtime's threads library linked in, so nothing else
    # is needed beside the program; the set-up's archive, CD and cabinet
    # readers; the icon, manifest and the program's own files as resources)
    libs = ['-lm', '-static-libgcc', '-Wl,-Bstatic', '-lpthread', '-Wl,-Bdynamic'] if windows else ['-lm', '-lpthread']
    if windows:
        objs.append(windows_resources(cc, obj))
        # MinGW-w64's gcc links a default-manifest.o into every program; the
        # program has its own (src/host/res): an empty one found first
        empty = os.path.join(obj, 'no-default-manifest')
        os.makedirs(empty, exist_ok=True)
        if not os.path.exists(os.path.join(empty, 'default-manifest.o')):
            open(os.path.join(empty, 'empty.c'), 'w').write('/* (tools/build_port.py) */\n')
            run([cc, '-c', '-o', os.path.join(empty, 'default-manifest.o'), os.path.join(empty, 'empty.c')])
        objs.insert(0, '-B' + empty + os.sep)
        libs = ['-L' + os.path.join(paths.DEPS_WINDOWS, 'lib'), '-Wl,-Bstatic', '-larchive', '-lunshield', '-llzma',
                '-lbz2', '-lz', '-Wl,-Bdynamic', '-lcomctl32', '-ldwmapi', '-luxtheme', '-lole32', '-luuid',
                '-lshell32', '-ladvapi32', '-luser32', '-lbcrypt'] + libs
    if mac:
        libs += ['-framework', 'Cocoa']
    run([cc, '-o', out] + objs + sdl_libs + libs)
    if sdl_dll and os.path.exists(sdl_dll):
        shutil.copy(sdl_dll, os.path.join(ROOT, 'build'))      # the game runs with SDL2.dll beside it
    print('built %s' % os.path.relpath(out, ROOT))


def pack():
    import tarfile
    out = os.path.join(ROOT, 'dist', 'civ2-port-src.tar.gz')
    os.makedirs(os.path.dirname(out), exist_ok=True)
    with tarfile.open(out, 'w:gz') as t:
        for rel in ('build/wasm/c', 'src/host', 'src/platform/win32_vk.h', 'tools/build_port.py',
                    'tools/paths.py', 'tools/run-civ2.sh', 'data/native', 'harness/CIV2.DAT', 'README.md'):
            t.add(os.path.join(ROOT, rel), arcname=os.path.join('civ2-port', rel))
    print('wrote %s (%d MB)' % (os.path.relpath(out, ROOT), os.path.getsize(out) >> 20))


def main():
    steps = sys.argv[1:] or ['module', 'c', 'exe']
    for s in steps:
        {'module': module, 'c': to_c, 'exe': exe, 'exe-windows': lambda: exe(True), 'pack': pack}[s]()


if __name__ == '__main__':
    main()
