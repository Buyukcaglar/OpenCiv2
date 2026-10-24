#!/usr/bin/env python3
"""dist/OpenCiv2-windows.zip, as published: OpenCiv2/ with OpenCiv2.exe (from
build/), LICENSE.txt, CHANGELOG.txt and README.txt (this folder's, with the
version from src/host/setup.h and the build named).

    python3 tools/release/package.py [BUILD]     BUILD: e.g. the commit
"""
import os
import re
import subprocess
import sys
import zipfile

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))


def version():
    h = open(os.path.join(ROOT, 'src', 'host', 'setup.h'), encoding='utf-8').read()
    return re.search(r'#define\s+OPENCIV2_VERSION\s+"([^"]+)"', h).group(1)


def build_name():
    if len(sys.argv) > 1:
        return sys.argv[1]
    try:
        return subprocess.check_output(['git', 'rev-parse', '--short', 'HEAD'], cwd=ROOT,
                                       text=True).strip()
    except (OSError, subprocess.CalledProcessError):
        return 'local'


def text(path):
    """A text file with Windows line endings, for Notepad."""
    s = open(path, encoding='utf-8').read().replace('\r\n', '\n')
    return s.replace('\n', '\r\n').encode('utf-8')


def main():
    exe = os.path.join(ROOT, 'build', 'OpenCiv2.exe')
    if not os.path.exists(exe):
        sys.exit('no build/OpenCiv2.exe: run tools/build_port.py module c exe-windows first')
    readme = open(os.path.join(HERE, 'README.txt'), encoding='utf-8').read()
    readme = readme.replace('@VERSION@', version()).replace('@BUILD@', build_name())

    os.makedirs(os.path.join(ROOT, 'dist'), exist_ok=True)
    out = os.path.join(ROOT, 'dist', 'OpenCiv2-windows.zip')
    with zipfile.ZipFile(out, 'w', zipfile.ZIP_DEFLATED, compresslevel=9) as z:
        z.write(exe, 'OpenCiv2/OpenCiv2.exe')
        z.writestr('OpenCiv2/README.txt', readme.replace('\r\n', '\n').replace('\n', '\r\n').encode('utf-8'))
        z.writestr('OpenCiv2/LICENSE.txt', text(os.path.join(ROOT, 'LICENSE')))
        z.writestr('OpenCiv2/CHANGELOG.txt', text(os.path.join(ROOT, 'CHANGELOG.md')))
    print(out)


if __name__ == '__main__':
    main()
