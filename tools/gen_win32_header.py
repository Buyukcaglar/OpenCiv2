#!/usr/bin/env python3
"""Generate src/platform/win32_api.h: the Windows constants and function
prototypes the game uses, for native (non-Windows) builds.

Constants and prototypes are taken from the mingw-w64 headers the 32-bit
build uses (run/pre.c = preprocessed auto_common.h, run/macros.txt = its
macros), restricted to identifiers the game source mentions.  Types are
hand-written in src/platform/win32_types.h (LLP64 sizes).
Run inside the civ2-dev container.
"""
import glob
import os
import re
import subprocess

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


# Names the C library's own headers define.
C_LIBRARY_MACROS = {'SIZE_MAX', 'MB_LEN_MAX', 'FILENAME_MAX', 'NULL', 'EOF', 'BUFSIZ', 'SEEK_SET', 'SEEK_CUR', 'SEEK_END',
                    'RAND_MAX', 'EXIT_SUCCESS', 'EXIT_FAILURE', 'MAX_PATH_', 'PATH_MAX', 'TMP_MAX', 'L_tmpnam',
                    'FOPEN_MAX', 'CHAR_BIT', 'INT_MAX', 'INT_MIN', 'UINT_MAX', 'LONG_MAX', 'LONG_MIN', 'ULONG_MAX'}


def main():
    pre = subprocess.run(['i686-w64-mingw32-gcc', '-E', '-P', '-I', 'src/include', '-I', 'src/auto', '-I', 'tools',
                          '-x', 'c', '-'], input='#include "auto_common.h"\n', capture_output=True, text=True,
                         cwd=ROOT).stdout
    sys_headers = ''.join('#include <%s>\n' % h for h in ('windows.h', 'stdio.h', 'mmsystem.h', 'vfw.h', 'ddraw.h',
                                                          'commdlg.h'))
    macros_txt = subprocess.run(['i686-w64-mingw32-gcc', '-E', '-dM', '-x', 'c', '-'],
                                input='#define WIN32_LEAN_AND_MEAN\n#define NOMINMAX\n' + sys_headers,
                                capture_output=True, text=True, cwd=ROOT).stdout
    ids = set()
    for f in glob.glob(os.path.join(ROOT, 'src', 'auto', '*.c')) + glob.glob(os.path.join(ROOT, 'src', 'game', '*.c')):
        ids |= set(re.findall(r'\b[A-Za-z_]\w*\b', open(f).read()))

    # Function declarations in the preprocessed headers: one statement each.
    decls = {}
    for stmt in re.split(r';', pre):
        s = ' '.join(stmt.split())
        s = s[s.rfind('}') + 1:].strip()    # after an inline function body
        m = re.search(r'\b([A-Za-z_]\w*)\s*\((?:[^()]|\([^()]*\))*\)\s*$', s)
        if not m or s.startswith('typedef'):
            continue
        name = m.group(1)
        if name in ids and name not in decls and not name.startswith(('FUN_', 'thunk_')):
            decls[name] = s
    # Values that carry pointers in the game (window and class extra data):
    # pointer-sized in native builds, as their *Ptr variants are on Win64.
    pointer_sized = {
        'GetWindowLongA': 'LONG_PTR WINAPI GetWindowLongA(HWND hWnd,int nIndex)',
        'SetWindowLongA': 'LONG_PTR WINAPI SetWindowLongA(HWND hWnd,int nIndex,LONG_PTR dwNewLong)',
        'GetClassLongA': 'ULONG_PTR WINAPI GetClassLongA(HWND hWnd,int nIndex)',
        'SetClassLongA': 'ULONG_PTR WINAPI SetClassLongA(HWND hWnd,int nIndex,LONG_PTR dwNewLong)',
    }
    protos = []
    for name in sorted(decls):
        if name in pointer_sized:
            protos.append(pointer_sized[name] + ';')
            continue
        s = decls[name]
        if '__stdcall' not in s:      # only real Windows APIs; C library functions come from libc
            continue
        s = s.replace('__attribute__((__stdcall__))', 'WINAPI')
        s = re.sub(r'__attribute__\s*\(\((?:[^()]|\([^()]*\))*\)\)', '', s)
        s = re.sub(r'__declspec\s*\([^)]*\)', '', s)
        s = s.replace('extern ', '').replace('__stdcall', 'WINAPI').replace('__cdecl', '')
        s = re.sub(r'\b(WINAPI\s+)+', 'WINAPI ', s)
        s = ' '.join(s.split())
        protos.append(s + ';')

    # Constants: object-like macros with numeric values that the game
    # mentions or that belong to families the platform layer implements.
    families = re.compile(r'^(WM|WS|WS_EX|SW|SWP|VK|GWL|GCL|GW|MF|MFT|MFS|SM|COLOR|CS|PM|HT|SB|SBS|ESB|ES|EM|EN|LB|LBS|LBN|'
                          r'CB|CBS|CBN|BS|DT|TA|PS|BS|BI|DIB|TRANSPARENT|OPAQUE|MB|ID|OFN|OF|GENERIC|FILE|CREATE|'
                          r'OPEN|TRUNCATE|MMSYSERR|WAVE|WHDR|MCI|MMIO|SEEK|TIME|TIMERR|HKEY|KEY|REG|ERROR|SND|MK|'
                          r'SIZE|WA|SC|PC|NULL|WHITE|BLACK|GRAY|LTGRAY|DKGRAY|HOLLOW|SYSTEM|ANSI|DEFAULT|OEM|DEVICE|'
                          r'FW|RASTERCAPS|BITSPIXEL|PLANES|SIZEPALETTE|NUMCOLORS|HORZRES|VERTRES|LOGPIXELS|RC|'
                          r'SRC|DST|MERGE|PAT|NOTSRC|WH|HC|INVALID|DRIVE|TPM|MAX|GMEM|LMEM|SEM|DDERR|DD|CLR|'
                          r'IDC|IDI|PAGE|FILE_MAP|MAKEINTRESOURCE|RT|LOAD|CW|HWND|USER|STOCK|R2|OUT|CLIP|ANTI|'
                          r'PROOF|NONANTI|VARIABLE|FIXED|FF|CF|ICM|IC|AVI|STREAM|MMIO|CALLBACK|DS|DC|ODA|ODS|ODT|'
                          r'SPI|SS|FNERR|CDERR|LPTR|GPTR|GHND|DLGC|BN|GDI|TECHNOLOGY|AVIERR|WOM|MM|FOURCC|TRUETYPE|RASTER|MCIERR|ICERR|'
                          r'EN|LBN|CBN|ODA|ODS|ODT|KF|MA|HC|WA|DT|SIF|SBM|ESB)_?\w*$')
    consts = []
    for line in macros_txt.splitlines():
        m = re.match(r'#define (\w+) (.+)$', line)
        if not m or m.group(1) in decls or not re.match(r'^[A-Z][A-Z0-9_]*$', m.group(1)):
            continue
        if m.group(1) not in ids and not families.match(m.group(1)):
            continue
        if m.group(1) in C_LIBRARY_MACROS:
            continue
        v = m.group(2)
        calls = set(re.findall(r'\b(?!0x)([A-Za-z_]\w*)\(', v)) - {'__MSABI_LONG', 'MAKEINTRESOURCE', 'MAKEINTRESOURCEA', 'MAKE_AVIERR'}
        if re.match(r'^[\w\s()+\-*/|&~<>xXuUlL.]+$', v) and not calls:
            consts.append('#define %s %s' % (m.group(1), v))
    out = ['/* Generated by tools/gen_win32_header.py: Windows API constants and',
           ' * prototypes used by the game, for native builds (see src/platform/). */',
           '#ifndef CIV2_WIN32_API_H', '#define CIV2_WIN32_API_H', '', '#include "win32_types.h"', '']
    # (the platform layer is C, the game C++)
    out += consts + ['', '#ifdef __cplusplus', 'extern "C" {', '#endif'] + protos + \
        ['#ifdef __cplusplus', '}', '#endif', '', '#endif', '']
    os.makedirs(os.path.join(ROOT, 'src', 'platform'), exist_ok=True)
    open(os.path.join(ROOT, 'src', 'platform', 'win32_api.h'), 'w').write('\n'.join(out))
    print('constants %d, functions %d' % (len(consts), len(protos)))


if __name__ == '__main__':
    main()
