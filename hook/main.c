/*
 * civ2 hook runtime.
 *
 * Built as a proxy XDaemon.dll that sits next to the original civ2.exe.  The
 * Windows loader maps it before civ2.exe's entry point runs, which gives us a
 * place to:
 *   - forward the real XDaemon networking API (xdaemon_proxy.c),
 *   - redirect original functions to their reconstructed versions (recon.c),
 *   - make the game deterministic for side-by-side comparison (determinism.c).
 */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "hook.h"

int xd_proxy_init(void);

static struct maplog hook_log;

void hook_logf(const char *fmt, ...)
{
    char buf[512];
    va_list ap;
    va_start(ap, fmt);
    _vsnprintf(buf, sizeof buf - 1, fmt, ap);
    buf[sizeof buf - 1] = 0;
    va_end(ap);
    maplog_printf(&hook_log, "%s", buf);
}

/* Overwrite the first 5 bytes at `from` with `jmp to`. */
void hook_patch_jmp(DWORD from, void *to)
{
    DWORD old;
    BYTE *p = (BYTE *)from;
    VirtualProtect(p, 5, PAGE_EXECUTE_READWRITE, &old);
    p[0] = 0xE9;
    *(DWORD *)(p + 1) = (DWORD)to - (from + 5);
    VirtualProtect(p, 5, old, &old);
    FlushInstructionCache(GetCurrentProcess(), p, 5);
}

static void hook_init(void)
{
    const char *logpath = getenv("CIV2_HOOK_LOG");
    if (logpath && *logpath)
        maplog_open(&hook_log, logpath);
    hook_logf("civ2 hook runtime loaded\n");
    crash_init();
    compat_init();
    determinism_init();
    replay_init();
    gditrace_init();
    proctrace_init();
    apitrace_init();
    stackprobe_init();
    recon_install();
}

BOOL WINAPI DllMain(HINSTANCE inst, DWORD reason, LPVOID reserved)
{
    (void)inst; (void)reserved;
    if (reason == DLL_PROCESS_ATTACH) {
        if (!xd_proxy_init())
            return FALSE;
        hook_init();
    }
    return TRUE;
}
