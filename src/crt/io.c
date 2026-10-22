/*
 * Low-level file open (_open / _sopen) from the MSVC 4.2 C runtime.
 */
#include "game.h"
#include <stdarg.h>

/* protos.h declares both without parameters; they are variadic (pmode). */
int __cdecl open_impl(char *path, int oflag, ...) __asm__("___open");
int __cdecl sopen_impl(char *path, int oflag, int shflag, ...) __asm__("___sopen");

#define g_errno     (*(int *)((u8 *)&g.d_00639f14))
#define g_doserrno  (*(DWORD *)((u8 *)&g.d_00639f18))
#define g_umaskval  (*(int *)((u8 *)&g.d_00639f1c))
#define g_fmode     (*(int *)((u8 *)&g.d_0063b3dc))
#define g_pioinfo   ((byte **)0x006e69f0)

#define osfile(fh) (g_pioinfo[((fh) & 0xffffffe0) >> 5][((fh) & 0x1f) * 8 + 4])

/* 0x00601700: _open(path, oflag, pmode) = _sopen(path, oflag, _SH_DENYNO, pmode) */
int __cdecl open_impl(char *path, int oflag, ...)
{
    va_list ap;
    int pmode;

    va_start(ap, oflag);
    pmode = va_arg(ap, int);
    va_end(ap);
    return sopen_impl(path, oflag, 0x40, pmode);
}

/* 0x00601750: _sopen(path, oflag, shflag, pmode) */
int __cdecl sopen_impl(char *path, int oflag, int shflag, ...)
{
    va_list ap;
    SECURITY_ATTRIBUTES sa;
    byte fileflags;
    DWORD access, share, create, attrib, type;
    int pmode;
    int fh;
    HANDLE h;
    long pos;
    char ch;

    sa.nLength = 0xc;
    sa.lpSecurityDescriptor = NULL;
    if (oflag & 0x80) {         /* _O_NOINHERIT */
        sa.bInheritHandle = FALSE;
        fileflags = 0x10;
    } else {
        sa.bInheritHandle = TRUE;
        fileflags = 0;
    }
    if (!(oflag & 0x8000)) {    /* not _O_BINARY */
        if (oflag & 0x4000)     /* _O_TEXT */
            fileflags |= 0x80;
        else if (g_fmode != 0x8000)
            fileflags |= 0x80;
    }

    switch (oflag & 3) {
    case 0: access = GENERIC_READ; break;
    case 1: access = GENERIC_WRITE; break;
    case 2: access = GENERIC_READ | GENERIC_WRITE; break;
    default:
        g_errno = 0x16;
        g_doserrno = 0;
        return -1;
    }

    switch (shflag) {
    case 0x10: share = 0; break;
    case 0x20: share = FILE_SHARE_READ; break;
    case 0x30: share = FILE_SHARE_WRITE; break;
    case 0x40: share = FILE_SHARE_READ | FILE_SHARE_WRITE; break;
    default:
        g_errno = 0x16;
        g_doserrno = 0;
        return -1;
    }

    switch (oflag & 0x700) {
    case 0:
    case 0x400: create = OPEN_EXISTING; break;
    case 0x100: create = OPEN_ALWAYS; break;
    case 0x500:
    case 0x700: create = CREATE_NEW; break;
    case 0x200:
    case 0x600: create = TRUNCATE_EXISTING; break;
    case 0x300: create = CREATE_ALWAYS; break;
    default:
        g_errno = 0x16;
        g_doserrno = 0;
        return -1;
    }

    attrib = FILE_ATTRIBUTE_NORMAL;
    if (oflag & 0x100) {        /* _O_CREAT */
        va_start(ap, shflag);
        pmode = va_arg(ap, int);
        va_end(ap);
        if (!(~g_umaskval & pmode & 0x80))
            attrib = FILE_ATTRIBUTE_READONLY;
    }
    if (oflag & 0x40) {         /* _O_TEMPORARY */
        attrib |= FILE_FLAG_DELETE_ON_CLOSE;
        access |= DELETE;
    }
    if (oflag & 0x1000)         /* _O_SHORT_LIVED */
        attrib |= FILE_ATTRIBUTE_TEMPORARY;
    if (oflag & 0x20)           /* _O_SEQUENTIAL */
        attrib |= FILE_FLAG_SEQUENTIAL_SCAN;
    else if (oflag & 0x10)      /* _O_RANDOM */
        attrib |= FILE_FLAG_RANDOM_ACCESS;

    fh = __alloc_osfhnd();
    if (fh == -1) {
        g_errno = 0x18;
        g_doserrno = 0;
        return -1;
    }
    h = CreateFileA(path, access, share, &sa, create, attrib, NULL);
    if (h == INVALID_HANDLE_VALUE) {
        __dosmaperr(GetLastError());
        return -1;
    }
    type = GetFileType(h);
    if (type == 0) {
        CloseHandle(h);
        __dosmaperr(GetLastError());
        return -1;
    }
    if (type == FILE_TYPE_CHAR)
        fileflags |= 0x40;
    else if (type == FILE_TYPE_PIPE)
        fileflags |= 8;
    __set_osfhnd(fh, h);
    fileflags |= 1;
    osfile(fh) = fileflags;

    /* text mode, read/write: strip a trailing ^Z */
    if (!(fileflags & 0x48) && (fileflags & 0x80) && (oflag & 2)) {
        pos = __lseek(fh, -1, 2);
        if (pos == -1) {
            if (g_doserrno != 0x83) {
                __close(fh);
                return -1;
            }
        } else {
            ch = 0;
            if (__read(fh, &ch, 1) == 0 && ch == 0x1a && __chsize(fh, pos) == -1) {
                __close(fh);
                return -1;
            }
            if (__lseek(fh, 0, 0) == -1) {
                __close(fh);
                return -1;
            }
        }
    }
    if (!(fileflags & 0x48) && (oflag & 8))     /* _O_APPEND */
        osfile(fh) |= 0x20;
    return fh;
}
