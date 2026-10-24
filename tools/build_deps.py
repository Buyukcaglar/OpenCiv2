#!/usr/bin/env python3
"""The Windows executable's libraries for setting up the game from the
user's copy (src/host/setup_*.c): libarchive (zip, 7z, rar), with zlib,
bzip2 and xz for its compression methods, and libunshield (the
InstallShield cabinet on the game's CD).  Static libraries for MinGW-w64,
built into tools/toolchain/deps-windows (include/, lib/).

    build_deps.py            (CC: the MinGW-w64 gcc; default gcc on
                              Windows, x86_64-w64-mingw32-gcc elsewhere)

Needs cmake and ninja (MSYS2/winlibs have them).  The sources are
downloaded into tools/toolchain/src once, checked against the SHA-256s
below.
"""
import hashlib
import os
import shutil
import subprocess
import sys
import tarfile
import urllib.request

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import paths  # noqa: E402

TOOLCHAIN = os.path.join(paths.ROOT, 'tools', 'toolchain')
SRC = os.path.join(TOOLCHAIN, 'src')
BUILD = os.path.join(TOOLCHAIN, 'deps-build')
PREFIX = paths.DEPS_WINDOWS

SOURCES = {
    'zlib': ('https://github.com/madler/zlib/releases/download/v1.3.2/zlib-1.3.2.tar.gz', 'zlib-1.3.2',
             'bb329a0a2cd0274d05519d61c667c062e06990d72e125ee2dfa8de64f0119d16'),
    'bzip2': ('https://sourceware.org/pub/bzip2/bzip2-1.0.8.tar.gz', 'bzip2-1.0.8',
              'ab5a03176ee106d3f0fa90e381da478ddae405918153cca248e682cd0c4a2269'),
    'xz': ('https://github.com/tukaani-project/xz/releases/download/v5.8.4/xz-5.8.4.tar.gz', 'xz-5.8.4',
           '0014c7886930454fe8bd4228665b51af55eeae560ea135c9c4cd33f55b2591d9'),
    'libarchive': ('https://github.com/libarchive/libarchive/releases/download/v3.8.10/libarchive-3.8.10.tar.gz',
                   'libarchive-3.8.10', 'a1bffbe5152cfe869751179e7b16648c87c461cb8c46eee75062efbe164cc57c'),
    'unshield': ('https://github.com/twogood/unshield/archive/refs/tags/1.6.2.tar.gz', 'unshield-1.6.2',
                 'a937ef596ad94d16e7ed2c8553ad7be305798dcdcfd65ae60210b1e54ab51a2f'),
}


def run(cmd, **kw):
    print(' '.join(cmd), flush=True)
    subprocess.run(cmd, check=True, **kw)


def fetch(name):
    url, top, sha = SOURCES[name]
    os.makedirs(SRC, exist_ok=True)
    tgz = os.path.join(SRC, top + '.tar.gz')
    if not os.path.exists(tgz):
        print('downloading', url, flush=True)
        with urllib.request.urlopen(url) as r, open(tgz + '.part', 'wb') as f:
            shutil.copyfileobj(r, f)
        os.replace(tgz + '.part', tgz)
    digest = hashlib.sha256(open(tgz, 'rb').read()).hexdigest()
    if sha and digest != sha:
        sys.exit('%s: SHA-256 %s, expected %s' % (tgz, digest, sha))
    if not sha:
        print('%s: SHA-256 %s' % (os.path.basename(tgz), digest))
    out = os.path.join(SRC, top)
    if not os.path.isdir(out):
        with tarfile.open(tgz) as t:
            t.extractall(SRC, filter='data') if hasattr(tarfile, 'data_filter') else t.extractall(SRC)
    return out


def tool(cc, name):
    """binutils' NAME beside the compiler (x86_64-w64-mingw32-ar ...)."""
    base = os.path.basename(cc)
    for suffix in ('-gcc-posix', '-gcc-win32', '-gcc'):
        if base.endswith(suffix):
            return os.path.join(os.path.dirname(cc), base[:-len(suffix)] + '-' + name)
    return name


def cmake(name, src, cc, cross, *opts):
    build = os.path.join(BUILD, name)
    args = ['cmake', '-G', 'Ninja', '-S', src, '-B', build, '-DCMAKE_BUILD_TYPE=Release',
            '-DCMAKE_C_COMPILER=' + cc, '-DCMAKE_INSTALL_PREFIX=' + PREFIX, '-DCMAKE_PREFIX_PATH=' + PREFIX,
            '-DBUILD_SHARED_LIBS=OFF', '-DCMAKE_POLICY_VERSION_MINIMUM=3.5']
    if cross:
        args += ['-DCMAKE_SYSTEM_NAME=Windows', '-DCMAKE_RC_COMPILER=' + tool(cc, 'windres'),
                 '-DCMAKE_FIND_ROOT_PATH=' + PREFIX]
    # (cmake reads backslashes in paths as escapes)
    run([a.replace('\\', '/') for a in args + list(opts)])
    run(['cmake', '--build', build])
    run(['cmake', '--install', build])


def bzip2(src, cc):
    """bzip2 1.0.8 has no build for MinGW worth using: the library by hand."""
    build = os.path.join(BUILD, 'bzip2')
    os.makedirs(build, exist_ok=True)
    objs = []
    for f in ('blocksort', 'huffman', 'crctable', 'randtable', 'compress', 'decompress', 'bzlib'):
        o = os.path.join(build, f + '.o')
        run([cc, '-O2', '-w', '-D_FILE_OFFSET_BITS=64', '-c', os.path.join(src, f + '.c'), '-o', o])
        objs.append(o)
    os.makedirs(os.path.join(PREFIX, 'lib'), exist_ok=True)
    os.makedirs(os.path.join(PREFIX, 'include'), exist_ok=True)
    lib = os.path.join(PREFIX, 'lib', 'libbz2.a')
    if os.path.exists(lib):
        os.remove(lib)
    run([tool(cc, 'ar'), 'rcs', lib] + objs)
    shutil.copy(os.path.join(src, 'bzlib.h'), os.path.join(PREFIX, 'include'))


def main():
    windows_host = sys.platform == 'win32' or bool(os.environ.get('MSYSTEM'))
    cc = os.environ.get('CC') or ('gcc' if windows_host else 'x86_64-w64-mingw32-gcc')
    cc = shutil.which(cc) or cc
    cross = not windows_host
    inc, lib = os.path.join(PREFIX, 'include'), os.path.join(PREFIX, 'lib')
    cmake('zlib', fetch('zlib'), cc, cross, '-DZLIB_BUILD_SHARED=OFF', '-DZLIB_BUILD_TESTING=OFF')
    # zlib 1.3.2 installs libz.a (or libzs.a): one name for those who look for zlib
    for alt in ('libzs.a', 'libzlibstatic.a'):
        if os.path.exists(os.path.join(lib, alt)) and not os.path.exists(os.path.join(lib, 'libz.a')):
            shutil.copy(os.path.join(lib, alt), os.path.join(lib, 'libz.a'))
    bzip2(fetch('bzip2'), cc)
    cmake('xz', fetch('xz'), cc, cross, '-DXZ_NLS=OFF', '-DXZ_TOOL_XZ=OFF', '-DXZ_TOOL_XZDEC=OFF',
          '-DXZ_TOOL_LZMADEC=OFF', '-DXZ_TOOL_LZMAINFO=OFF', '-DXZ_TOOL_SCRIPTS=OFF', '-DXZ_DOC=OFF',
          '-DBUILD_TESTING=OFF', '-DXZ_THREADS=no')
    zlib = ['-DZLIB_INCLUDE_DIR=' + inc, '-DZLIB_LIBRARY=' + os.path.join(lib, 'libz.a')]
    cmake('libarchive', fetch('libarchive'), cc, cross, *zlib,
          '-DBZIP2_INCLUDE_DIR=' + inc, '-DBZIP2_LIBRARIES=' + os.path.join(lib, 'libbz2.a'),
          '-DLIBLZMA_INCLUDE_DIR=' + inc, '-DLIBLZMA_LIBRARY=' + os.path.join(lib, 'liblzma.a'),
          '-DENABLE_LZMA=ON', '-DENABLE_BZip2=ON', '-DENABLE_ZLIB=ON',
          '-DENABLE_OPENSSL=OFF', '-DENABLE_MBEDTLS=OFF', '-DENABLE_NETTLE=OFF', '-DENABLE_LIBB2=OFF',
          '-DENABLE_LZ4=OFF', '-DENABLE_LZO=OFF', '-DENABLE_ZSTD=OFF', '-DENABLE_LIBXML2=OFF',
          '-DENABLE_EXPAT=OFF', '-DENABLE_WIN32_XMLLITE=OFF', '-DENABLE_PCREPOSIX=OFF', '-DENABLE_PCRE2POSIX=OFF',
          '-DENABLE_CNG=OFF', '-DENABLE_ICONV=OFF', '-DENABLE_ACL=OFF', '-DENABLE_XATTR=OFF',
          '-DENABLE_TAR=OFF', '-DENABLE_CPIO=OFF', '-DENABLE_CAT=OFF', '-DENABLE_UNZIP=OFF', '-DENABLE_TEST=OFF',
          '-DENABLE_INSTALL=ON')
    # (its MD5 is K&R C, which C23 -- newer gcc's default -- no longer accepts)
    cmake('unshield', fetch('unshield'), cc, cross, *zlib, '-DBUILD_STATIC=ON', '-DUSE_OUR_OWN_MD5=ON',
          '-DBUILD_TESTING=OFF', '-DCMAKE_C_FLAGS=-std=gnu17')
    print('libraries ready in %s' % os.path.relpath(PREFIX, paths.ROOT))


if __name__ == '__main__':
    main()
