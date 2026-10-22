/*
 * GDI tracing for comparing builds: CIV2_TRACE_PT=x,y logs every blit or
 * fill whose destination covers that screen pixel, with the caller.  The
 * native platform layer has the same option (src/platform/gdi.c).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hook.h"

static int tx = -1, ty = -1;

static BOOL (WINAPI *real_BitBlt)(HDC, int, int, int, int, HDC, int, int, DWORD);
static BOOL (WINAPI *real_StretchBlt)(HDC, int, int, int, int, HDC, int, int, int, int, DWORD);
static int (WINAPI *real_FillRect)(HDC, const RECT *, HBRUSH);

/* Destination rectangle in screen coordinates, if hdc draws on a window. */
static int on_screen(HDC hdc, int x, int y, int w, int h, RECT *out)
{
    HWND wnd = WindowFromDC(hdc);
    POINT org;
    if (!wnd)
        return 0;
    GetDCOrgEx(hdc, &org);
    out->left = org.x + x;
    out->top = org.y + y;
    out->right = out->left + w;
    out->bottom = out->top + h;
    return 1;
}

static int hit(const RECT *r)
{
    return tx >= r->left && tx < r->right && ty >= r->top && ty < r->bottom;
}

static BOOL WINAPI t_BitBlt(HDC d, int x, int y, int w, int h, HDC s, int sx, int sy, DWORD rop)
{
    RECT r;
    if (on_screen(d, x, y, w, h, &r) && hit(&r))
        hook_logf("trace: blit to %ld,%ld %dx%d from %s %d,%d rop %06lx caller %p\n", r.left, r.top, w, h,
                  WindowFromDC(s) ? "window" : "memory", sx, sy, rop, __builtin_return_address(0));
    return real_BitBlt(d, x, y, w, h, s, sx, sy, rop);
}

static BOOL WINAPI t_StretchBlt(HDC d, int x, int y, int w, int h, HDC s, int sx, int sy, int sw, int sh, DWORD rop)
{
    RECT r;
    if (on_screen(d, x, y, w, h, &r) && hit(&r))
        hook_logf("trace: stretch to %ld,%ld %dx%d rop %06lx caller %p\n", r.left, r.top, w, h, rop,
                  __builtin_return_address(0));
    return real_StretchBlt(d, x, y, w, h, s, sx, sy, sw, sh, rop);
}

static BOOL (WINAPI *real_MoveWindow)(HWND, int, int, int, int, BOOL);
static BOOL (WINAPI *real_SetWindowPos)(HWND, HWND, int, int, int, int, UINT);

static BOOL WINAPI t_MoveWindow(HWND h, int x, int y, int cx, int cy, BOOL r)
{
    BOOL ret = real_MoveWindow(h, x, y, cx, cy, r);
    RECT wr, cr;
    GetWindowRect(h, &wr);
    GetClientRect(h, &cr);
    hook_logf("geom: MoveWindow(%p, %d,%d %dx%d) -> window %ld,%ld,%ld,%ld client %ldx%ld\n", (void *)h, x, y, cx, cy,
              wr.left, wr.top, wr.right, wr.bottom, cr.right, cr.bottom);
    return ret;
}

static BOOL WINAPI t_SetWindowPos(HWND h, HWND after, int x, int y, int cx, int cy, UINT f)
{
    BOOL ret = real_SetWindowPos(h, after, x, y, cx, cy, f);
    RECT wr, cr;
    GetWindowRect(h, &wr);
    GetClientRect(h, &cr);
    hook_logf("geom: SetWindowPos(%p, %d,%d %dx%d flags %x) -> window %ld,%ld,%ld,%ld client %ldx%ld\n", (void *)h, x, y,
              cx, cy, f, wr.left, wr.top, wr.right, wr.bottom, cr.right, cr.bottom);
    return ret;
}

static int WINAPI t_FillRect(HDC d, const RECT *rc, HBRUSH b)
{
    RECT r;
    if (on_screen(d, rc->left, rc->top, rc->right - rc->left, rc->bottom - rc->top, &r) && hit(&r))
        hook_logf("trace: fill %ld,%ld,%ld,%ld caller %p\n", r.left, r.top, r.right, r.bottom,
                  __builtin_return_address(0));
    return real_FillRect(d, rc, b);
}

/* CIV2_LOG_TEXT: DrawTextA calls (as src/platform/text.c logs them), with
 * the text alignment and extent the drawing uses. */
static int (WINAPI *real_DrawTextA)(HDC, LPCSTR, int, LPRECT, UINT);

static int WINAPI t_DrawTextA(HDC dc, LPCSTR s, int n, LPRECT r, UINT fmt)
{
    SIZE sz;
    int len = n < 0 ? (int)strlen(s) : n;
    GetTextExtentPoint32A(dc, s, len, &sz);
    hook_logf("DrawText(\"%.*s\", fmt %x, rect %ld,%ld,%ld,%ld, align %x, extent %ld)\n", len, s, fmt, r->left, r->top,
              r->right, r->bottom, GetTextAlign(dc), sz.cx);
    return real_DrawTextA(dc, s, n, r, fmt);
}

void gditrace_init(void)
{
    const char *s = getenv("CIV2_TRACE_PT");
    if (getenv("CIV2_LOG_TEXT"))
        real_DrawTextA = hook_patch_import("USER32.dll", "DrawTextA", (void *)t_DrawTextA);
    if (!s || sscanf(s, "%d,%d", &tx, &ty) != 2)
        return;
    real_BitBlt = hook_patch_import("GDI32.dll", "BitBlt", (void *)t_BitBlt);
    real_StretchBlt = hook_patch_import("GDI32.dll", "StretchBlt", (void *)t_StretchBlt);
    real_FillRect = hook_patch_import("USER32.dll", "FillRect", (void *)t_FillRect);
    real_MoveWindow = hook_patch_import("USER32.dll", "MoveWindow", (void *)t_MoveWindow);
    real_SetWindowPos = hook_patch_import("USER32.dll", "SetWindowPos", (void *)t_SetWindowPos);
    hook_logf("gditrace: watching %d,%d\n", tx, ty);
}
