/*
 * C runtime start-up (MSVC 4.2 debug CRT): process entry point, static
 * initialisers, lowio handle table, multibyte code page, environment and
 * signal().
 */
#include "game.h"

/* protos.h declares `void _signal()`; it really returns the old handler. */
int __cdecl signal_impl(int signum, int action) __asm__("__signal");
/* exit() (0x005f41b0, `_exit` in protos.h) without mingw's noreturn, so entry
 * keeps its epilogue like the original. */
void __cdecl crt_exit(int code) __asm__("__exit");

/* ---- globals ---------------------------------------------------------- */

#define g_osplatform    (*(uint *)((u8 *)&g.d_00639f20))   /* _osver, later platform */
#define g_winver        (*(uint *)((u8 *)&g.d_00639f24))
#define g_winmajor      (*(uint *)((u8 *)&g.d_00639f28))
#define g_winminor      (*(uint *)((u8 *)&g.d_00639f2c))
#define g_acmdln        (*(byte * *)((u8 *)&g.d_006e6b3c))
#define g_aenvptr       (*(void * *)((u8 *)&g.d_00639fc0))
typedef void (__cdecl *voidfn)(void);
#define g_FPinit        (*(voidfn *)((u8 *)&g.d_00639fb0))

#define g_onexitbegin   (*(int * *)((u8 *)&g.d_006e6b68))
#define g_onexitend     (*(int * *)((u8 *)&g.d_006e6b54))

#define g_pioinfo       ((byte **)0x006e69f0)      /* __pioinfo[] */
#define g_nhandle       (*(int *)((u8 *)&g.d_006e6b2c))

#define g_mbcodepage    (*(UINT *)((u8 *)&g.d_0063b0a4))
#define g_mblcid        (*(int *)((u8 *)&g.d_0063b0a8))
#define g_mbulinfo      ((ushort *)0x0063b0b0)     /* __mbulinfo[6] */
#define g_mbctype       ((byte *)0x0063afa0)       /* _mbctype[257] */
#define g_mbcodepages   ((byte *)0x0063b0c8)       /* __rgcode_page_info[5], 0x30 bytes each */
#define g_mbbtype       ((byte *)0x0063b0c0)       /* rgctypeflag[4] */
#define g_fSystemSet    (*(int *)((u8 *)&g.d_0063b0bc))

#define g_envtype       (*(int *)((u8 *)&g.d_0063af94))    /* 0 unknown, 1 wide, 2 ANSI */
#define g_ansicp        (*(UINT *)((u8 *)&g.d_0063a088))   /* __lc_codepage */

#define g_environ       (*(char ** *)((u8 *)&g.d_00639f3c))
#define g___initenv     (*(char ** *)((u8 *)&g.d_00639f40))
#define g_wenviron      (*(void ** *)((u8 *)&g.d_00639f44))

#define g_errno         (*(int *)((u8 *)&g.d_00639f14))
#define g_doserrno      (*(DWORD *)((u8 *)&g.d_00639f18))
#define g_ctrlc_action      (*(int *)((u8 *)&g.d_0063b24c))
#define g_ctrlbreak_action  (*(int *)((u8 *)&g.d_0063b250))
#define g_abort_action      (*(int *)((u8 *)&g.d_0063b254))
#define g_term_action       (*(int *)((u8 *)&g.d_0063b258))
#define g_ctrlhandler_set   (*(int *)((u8 *)&g.d_0063b25c))
#define ctrlevent_capture   ((PHANDLER_ROUTINE)0x00600610)

typedef int (__cdecl *initterm_fn)(int, int);

/* 0x005f6e90: process entry point (WinMainCRTStartup).  The original wraps
 * the body in __try/__except(_XcptFilter(...)); exception frames are dropped
 * in the reconstruction. */
void __cdecl entry(void)
{
    DWORD ver;
    byte *cmd;
    STARTUPINFOA si;
    int show;
    int ret;

    ver = GetVersion();
    g_winminor = ver >> 8 & 0xff;
    g_winmajor = ver & 0xff;
    g_winver = g_winmajor * 0x100 + g_winminor;
    g_osplatform = ver >> 0x10;
    if (__heap_init() == 0)
        __amsg_exit(0x1c);
    __ioinit();
    ___initmbctable();
    g_acmdln = (byte *)GetCommandLineA();
    g_aenvptr = ___crtGetEnvironmentStringsA();
    if (g_aenvptr == NULL || g_acmdln == NULL)
        crt_exit(-1);
    __setargv();
    __setenvp();
    __cinit();

    /* skip the program name */
    cmd = g_acmdln;
    if (*cmd == '"') {
        while (*++cmd != '"' && *cmd != 0) {
            if (__ismbblead((uint)*cmd) != 0)
                cmd++;
        }
        if (*cmd == '"')
            cmd++;
    } else {
        while (*cmd > ' ')
            cmd++;
    }
    while (*cmd != 0 && *cmd <= ' ')
        cmd++;

    si.dwFlags = 0;
    GetStartupInfoA(&si);
    if (si.dwFlags & STARTF_USESHOWWINDOW)
        show = si.wShowWindow;
    else
        show = SW_SHOWDEFAULT;
    ret = thunk_win_main((int)GetModuleHandleA(NULL), 0, (int)cmd, show);
    crt_exit(ret);      /* exit(); never returns */
}

/* 0x005f4160: run the C (0x6246ac..0x6248bc) and C++ (0x624000..0x6245a8)
 * initialiser tables.  The original returns whatever __initterm left in EAX. */
int __cdecl __cinit(void)
{
    if (g_FPinit != NULL)
        g_FPinit();
    ((initterm_fn)__initterm)(0x006246ac, 0x006248bc);
    return ((initterm_fn)__initterm)(0x00624000, 0x006245a8);
}

/* 0x005f1b80: register an atexit/onexit function (table grows by 4 slots). */
int __cdecl __onexit(int func)
{
    int *p;

    if ((uint)__msize_dbg(g_onexitbegin, 2) < (uint)((int)g_onexitend - (int)g_onexitbegin + 4)) {
        p = (int *)__realloc_dbg(g_onexitbegin, __msize_dbg(g_onexitbegin, 2) + 0x10, 2, (char *)0x0061d74c /* "onexit.c" */, 0x68);
        if (p == NULL)
            return 0;
        g_onexitend = (int *)((((int)g_onexitend - (int)g_onexitbegin) & 0xfffffffc) + (int)p);
        g_onexitbegin = p;
    }
    *g_onexitend = func;
    g_onexitend++;
    return func;
}

/* lowio handle table entry (ioinfo): osfhnd, osfile, pipech */
static void init_ioinfo_block(byte *p, byte *end)
{
    for (; p < end; p += 8) {
        p[4] = 0;
        *(int *)p = -1;
        p[5] = 10;
    }
}

/* 0x005fc160: set up the lowio handle table, inheriting handles passed in
 * STARTUPINFO.lpReserved2 and the three standard handles. */
int __cdecl __ioinit(void)
{
    byte *pio;
    STARTUPINFOA si;
    int ninherit;
    byte *posfile;
    HANDLE *posfhnd;
    int i;
    DWORD type;
    HANDLE h;
    DWORD stdh;

    pio = (byte *)__malloc_dbg(0x100, 2, (char *)0x0061e7e4 /* "ioinit.c" */, 0x83);
    if (pio == NULL)
        __amsg_exit(0x1b);
    g_pioinfo[0] = pio;
    g_nhandle = 0x20;
    init_ioinfo_block(pio, g_pioinfo[0] + 0x100);

    GetStartupInfoA(&si);
    if (si.cbReserved2 != 0 && si.lpReserved2 != NULL) {
        ninherit = *(int *)si.lpReserved2;
        posfile = si.lpReserved2 + 4;
        posfhnd = (HANDLE *)(posfile + ninherit);
        if (ninherit >= 0x800)
            ninherit = 0x800;
        for (i = 1; g_nhandle < ninherit; i++) {
            pio = (byte *)__malloc_dbg(0x100, 2, (char *)0x0061e7e4 /* "ioinit.c" */, 0xb8);
            if (pio == NULL) {
                ninherit = g_nhandle;
                break;
            }
            g_pioinfo[i] = pio;
            g_nhandle += 0x20;
            init_ioinfo_block(pio, g_pioinfo[i] + 0x100);
        }
        for (i = 0; i < ninherit; i++, posfile++, posfhnd++) {
            if (*posfhnd != INVALID_HANDLE_VALUE && (*(signed char *)posfile & 1) &&
                ((*(signed char *)posfile & 8) || GetFileType(*posfhnd) != 0)) {
                pio = g_pioinfo[(i & 0xffffffe0) >> 5] + (i & 0x1f) * 8;
                *(HANDLE *)pio = *posfhnd;
                pio[4] = *posfile;
            }
        }
    }

    for (i = 0; i < 3; i++) {
        pio = g_pioinfo[0] + i * 8;
        if (*(int *)pio == -1) {
            pio[4] = 0x81;
            if (i == 0)
                stdh = STD_INPUT_HANDLE;
            else if (i == 1)
                stdh = STD_OUTPUT_HANDLE;
            else
                stdh = STD_ERROR_HANDLE;
            h = GetStdHandle(stdh);
            if (h != INVALID_HANDLE_VALUE && (type = GetFileType(h)) != 0) {
                *(HANDLE *)pio = h;
                if ((byte)type == FILE_TYPE_CHAR)
                    pio[4] |= 0x40;
                else if ((byte)type == FILE_TYPE_PIPE)
                    pio[4] |= 8;
            } else {
                pio[4] |= 0x40;
            }
        } else {
            pio[4] |= 0x80;
        }
    }
    return SetHandleCount(g_nhandle);
}

/* 0x005ffac0: select the multibyte code page and build _mbctype. */
int __cdecl __setmbcp(int codepage)
{
    UINT cp;
    uint i, c;
    uint j;
    byte *range;
    CPINFO info;

    cp = getSystemCP(codepage);
    if (cp == g_mbcodepage)
        return 0;
    if (cp == 0) {
        setSBCS();
        return 0;
    }
    for (i = 0; i < 5; i++) {
        if (*(UINT *)(g_mbcodepages + i * 0x30) == cp) {
            for (c = 0; c < 0x101; c++)
                g_mbctype[c] = 0;
            for (j = 0; j < 4; j++) {
                for (range = g_mbcodepages + i * 0x30 + j * 8 + 0x10; range[0] != 0 && range[1] != 0; range += 2) {
                    for (c = range[0]; c <= range[1]; c++)
                        g_mbctype[c + 1] |= g_mbbtype[j];
                }
            }
            g_mbcodepage = cp;
            g_mblcid = _CPtoLCID(g_mbcodepage);
            for (j = 0; j < 6; j++)
                g_mbulinfo[j] = *(ushort *)(g_mbcodepages + i * 0x30 + 4 + j * 2);
            return 0;
        }
    }
    if (GetCPInfo(cp, &info) == 1) {
        for (c = 0; c < 0x101; c++)
            g_mbctype[c] = 0;
        if (info.MaxCharSize > 1) {
            for (range = info.LeadByte; range[0] != 0 && range[1] != 0; range += 2) {
                for (c = range[0]; c <= range[1]; c++)
                    g_mbctype[c + 1] |= 4;
            }
            for (c = 1; c < 0xff; c++)
                g_mbctype[c + 1] |= 8;
            g_mbcodepage = cp;
            g_mblcid = _CPtoLCID(g_mbcodepage);
        } else {
            g_mbcodepage = 0;
            g_mblcid = 0;
        }
        for (j = 0; j < 6; j++)
            g_mbulinfo[j] = 0;
        return 0;
    }
    if (g_fSystemSet != 0) {
        setSBCS();
        return 0;
    }
    return -1;
}

/* 0x005ff5a0: copy of the environment block as wide characters (malloc'd). */
LPVOID __cdecl ___crtGetEnvironmentStringsW(void)
{
    void *env = NULL;
    int size = 0;
    WCHAR *wp;
    WCHAR *buf;
    char *ap;
    int n;

    if (g_envtype == 0) {
        if ((env = GetEnvironmentStringsW()) != NULL) {
            g_envtype = 1;
        } else {
            if ((env = GetEnvironmentStrings()) == NULL)
                return NULL;
            g_envtype = 2;
        }
    }
    if (g_envtype == 1) {
        if (env == NULL && (env = GetEnvironmentStringsW()) == NULL)
            return NULL;
        wp = (WCHAR *)env;
        while (*wp != 0) {
            wp++;
            if (*wp == 0)
                wp++;
        }
        size = (int)wp - (int)env + 2;
        buf = (WCHAR *)__malloc_dbg(size, 2, (char *)0x0061e870 /* "aw_env.c" */, 0x57);
        if (buf == NULL) {
            FreeEnvironmentStringsW((LPWCH)env);
            return NULL;
        }
        FUN_005f2110(buf, env, size);
        FreeEnvironmentStringsW((LPWCH)env);
        return buf;
    }
    if (g_envtype == 2) {
        if (env == NULL && (env = GetEnvironmentStrings()) == NULL)
            return NULL;
        for (ap = (char *)env; *ap != 0; ap += _strlen(ap) + 1) {
            n = MultiByteToWideChar(g_ansicp, MB_PRECOMPOSED, ap, -1, NULL, 0);
            if (n == 0)
                return NULL;
            size += n;
        }
        size++;
        buf = (WCHAR *)__malloc_dbg(size * 2, 2, (char *)0x0061e870 /* "aw_env.c" */, 0x87);
        if (buf == NULL) {
            FreeEnvironmentStringsA((LPCH)env);
            return NULL;
        }
        ap = (char *)env;
        wp = buf;
        while (*ap != 0) {
            if (MultiByteToWideChar(g_ansicp, MB_PRECOMPOSED, ap, -1, wp, size - ((int)wp - (int)buf >> 1)) == 0) {
                __free_dbg(buf, 2);
                FreeEnvironmentStringsA((LPCH)env);
                return NULL;
            }
            ap += _strlen(ap) + 1;
            wp += _wcslen(wp) + 1;
        }
        *wp = 0;
        FreeEnvironmentStringsA((LPCH)env);
        return buf;
    }
    return NULL;    /* unreachable: g_envtype is always 1 or 2 here */
}

/* 0x00606b60: __crtsetenv(option "name=value", primary). */
int __cdecl ___crtsetenv(char *option, int primary)
{
    char *equal;
    int remove;
    char **env;
    int ix;
    char *name;
    char *value;

    if (option == NULL || (equal = (char *)__mbschr(option, '=')) == NULL || option == equal)
        return -1;
    remove = equal[1] == 0 ? 1 : 0;
    if (g___initenv == g_environ)
        g_environ = (char **)copy_environ(g_environ);
    if (g_environ == NULL) {
        if (primary != 0 && g_wenviron != NULL) {
            if (___wtomb_environ() != 0)
                return -1;
        } else {
            if (remove)
                return 0;
            if (g_environ == NULL) {
                g_environ = (char **)__malloc_dbg(4, 2, (char *)0x0061ec88 /* "setenv.c" */, 0x87);
                if (g_environ == NULL)
                    return -1;
                *g_environ = NULL;
            }
            if (g_wenviron == NULL) {
                g_wenviron = (void **)__malloc_dbg(4, 2, (char *)0x0061ec88 /* "setenv.c" */, 0x8e);
                if (g_wenviron == NULL)
                    return -1;
                *g_wenviron = NULL;
            }
        }
    }
    env = g_environ;
    ix = findenv(option, (int)equal - (int)option);
    if (ix >= 0 && *env != NULL) {
        if (remove) {
            __free_dbg(env[ix], 2);
            for (; env[ix] != NULL; ix++)
                env[ix] = env[ix + 1];
            env = (char **)__realloc_dbg(env, ix << 2, 2, (char *)0x0061ec88 /* "setenv.c" */, 0xb9);
            if (env != NULL)
                g_environ = env;
        } else {
            env[ix] = option;
        }
    } else {
        if (remove)
            return 0;
        if (ix < 0)
            ix = -ix;
        env = (char **)__realloc_dbg(env, ix * 4 + 8, 2, (char *)0x0061ec88 /* "setenv.c" */, 0xce);
        if (env == NULL)
            return -1;
        env[ix] = option;
        env[ix + 1] = NULL;
        g_environ = env;
    }
    if (primary != 0) {
        name = (char *)__malloc_dbg(_strlen(option) + 2, 2, (char *)0x0061ec88 /* "setenv.c" */, 0xe5);
        if (name != NULL) {
            FUN_005f22d0(name, option);
            value = name + ((int)equal - (int)option);
            *value++ = 0;
            SetEnvironmentVariableA(name, remove ? NULL : value);
            __free_dbg(name, 2);
        }
    }
    return 0;
}

/* 0x00600430: signal(signum, handler); returns the previous handler or
 * SIG_ERR (-1) with errno = EINVAL. */
int __cdecl signal_impl(int signum, int action)
{
    int old;
    int *xcpt;

    if (action == 4 || action == 3)
        goto error;
    if (signum == 2 || signum == 0x15 || signum == 0x16 || signum == 0xf) {
        if ((signum == 2 || signum == 0x15) && g_ctrlhandler_set == 0) {
            if (SetConsoleCtrlHandler(ctrlevent_capture, TRUE) == TRUE) {
                g_ctrlhandler_set = 1;
            } else {
                g_doserrno = GetLastError();
                goto error;
            }
        }
        switch (signum) {
        case 2:    old = g_ctrlc_action;     g_ctrlc_action = action;     break;
        case 0x15: old = g_ctrlbreak_action; g_ctrlbreak_action = action; break;
        case 0x16: old = g_abort_action;     g_abort_action = action;     break;
        case 0xf:  old = g_term_action;      g_term_action = action;      break;
        }
        return old;
    }
    if (signum != 8 && signum != 4 && signum != 0xb)
        goto error;
    xcpt = (int *)siglookup(signum);
    if (xcpt == NULL)
        goto error;
    old = xcpt[2];
    for (; xcpt[1] == signum; xcpt += 3)
        xcpt[2] = action;
    return old;
error:
    g_errno = 0x16;
    return -1;
}
