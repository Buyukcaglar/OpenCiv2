/*
 * Window procedure tracing for comparing builds: with CIV2_TRACE_MSG set,
 * every message delivered to one of the game's window procedures (sent or
 * dispatched) is logged ("deliver"), windows numbered as in replay.c.  The
 * game's procedures are wrapped where it installs them (RegisterClassA,
 * SetWindowLongA(GWL_WNDPROC)); calls it makes to old procedures with
 * CallWindowProcA are not logged.  The native platform logs the same.
 */
#include <stdio.h>
#include <stdlib.h>
#include "hook.h"

#define NWRAP 64
static WNDPROC wrapped[NWRAP];
static int nwrapped;
int replay_hwnd_index(HWND h);

static LRESULT deliver(int i, HWND h, UINT m, WPARAM w, LPARAM l)
{
    if (m != WM_TIMER)
        hook_logf("deliver %04x w%d\n", m, replay_hwnd_index(h));
    return CallWindowProcA(wrapped[i], h, m, w, l);
}

#define W(i) static LRESULT CALLBACK wrap##i(HWND h, UINT m, WPARAM w, LPARAM l) { return deliver(i, h, m, w, l); }
W(0) W(1) W(2) W(3) W(4) W(5) W(6) W(7) W(8) W(9) W(10) W(11) W(12) W(13) W(14) W(15)
W(16) W(17) W(18) W(19) W(20) W(21) W(22) W(23) W(24) W(25) W(26) W(27) W(28) W(29) W(30) W(31)
W(32) W(33) W(34) W(35) W(36) W(37) W(38) W(39) W(40) W(41) W(42) W(43) W(44) W(45) W(46) W(47)
W(48) W(49) W(50) W(51) W(52) W(53) W(54) W(55) W(56) W(57) W(58) W(59) W(60) W(61) W(62) W(63)
static WNDPROC wraps[NWRAP] = {
    wrap0, wrap1, wrap2, wrap3, wrap4, wrap5, wrap6, wrap7, wrap8, wrap9, wrap10, wrap11, wrap12, wrap13, wrap14, wrap15,
    wrap16, wrap17, wrap18, wrap19, wrap20, wrap21, wrap22, wrap23, wrap24, wrap25, wrap26, wrap27, wrap28, wrap29, wrap30,
    wrap31, wrap32, wrap33, wrap34, wrap35, wrap36, wrap37, wrap38, wrap39, wrap40, wrap41, wrap42, wrap43, wrap44, wrap45,
    wrap46, wrap47, wrap48, wrap49, wrap50, wrap51, wrap52, wrap53, wrap54, wrap55, wrap56, wrap57, wrap58, wrap59, wrap60,
    wrap61, wrap62, wrap63};

static WNDPROC wrap(WNDPROC p)
{
    int i;
    if (!p)
        return p;
    for (i = 0; i < nwrapped; i++)
        if (wrapped[i] == p || wraps[i] == p)
            return wraps[i];
    if (nwrapped == NWRAP)
        return p;
    wrapped[nwrapped] = p;
    return wraps[nwrapped++];
}

static WNDPROC unwrap(WNDPROC p)
{
    int i;
    for (i = 0; i < nwrapped; i++)
        if (wraps[i] == p)
            return wrapped[i];
    return p;
}

static ATOM (WINAPI *real_RegisterClassA)(const WNDCLASSA *);
static LONG (WINAPI *real_SetWindowLongA)(HWND, int, LONG);

static ATOM WINAPI t_RegisterClassA(const WNDCLASSA *wc)
{
    WNDCLASSA c = *wc;
    c.lpfnWndProc = wrap(wc->lpfnWndProc);
    return real_RegisterClassA(&c);
}

static LONG WINAPI t_SetWindowLongA(HWND h, int i, LONG v)
{
    if (i == GWL_WNDPROC)
        return (LONG)unwrap((WNDPROC)real_SetWindowLongA(h, i, (LONG)wrap((WNDPROC)v)));
    return real_SetWindowLongA(h, i, v);
}

void proctrace_init(void)
{
    if (!getenv("CIV2_TRACE_MSG"))
        return;
    real_RegisterClassA = hook_patch_import("USER32.dll", "RegisterClassA", (void *)t_RegisterClassA);
    real_SetWindowLongA = hook_patch_import("USER32.dll", "SetWindowLongA", (void *)t_SetWindowLongA);
}
