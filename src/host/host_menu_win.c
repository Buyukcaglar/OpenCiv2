/*
 * The native window's menu bar on Windows: a Win32 menu on SDL's window;
 * its WM_COMMAND arrives as an SDL_SYSWMEVENT (host_sdl.c).
 */
#include <windows.h>
#include <SDL.h>
#include <SDL_syswm.h>
#include "host.h"
#include "host_menu.h"

static HWND hwnd_of(SDL_Window *window)
{
    SDL_SysWMinfo info;
    SDL_VERSION(&info.version);
    return SDL_GetWindowWMInfo(window, &info) ? info.info.win.window : NULL;
}

void host_menu_apply(SDL_Window *window, const HostMenuItem *items, int n)
{
    HWND hwnd = hwnd_of(window);
    HMENU bar, old, stack[4];
    int i;
    if (!hwnd)
        return;
    bar = CreateMenu();
    stack[0] = bar;
    for (i = 0; i < n; i++) {
        const HostMenuItem *it = &items[i];
        UINT flags = (it->flags & HOST_MENU_GRAYED ? MF_GRAYED : 0) | (it->flags & HOST_MENU_CHECKED ? MF_CHECKED : 0);
        HMENU parent;
        if (it->level < 0 || it->level > 2)
            continue;
        parent = stack[it->level];
        if (it->flags & HOST_MENU_SEPARATOR) {
            AppendMenuA(parent, MF_SEPARATOR, 0, NULL);
        } else if (it->flags & HOST_MENU_POPUP) {
            HMENU sub = CreatePopupMenu();
            AppendMenuA(parent, MF_POPUP | flags, (UINT_PTR)sub, it->text);
            stack[it->level + 1] = sub;
        } else {
            AppendMenuA(parent, MF_STRING | flags, (UINT_PTR)it->id, it->text);
        }
    }
    old = GetMenu(hwnd);
    SetMenu(hwnd, bar);
    if (old)
        DestroyMenu(old);
    DrawMenuBar(hwnd);
}

int host_menu_syswm_command(const void *msg)
{
    const SDL_SysWMmsg *m = msg;
    if (m && m->subsystem == SDL_SYSWM_WINDOWS && m->msg.win.msg == WM_COMMAND && HIWORD(m->msg.win.wParam) == 0 &&
        m->msg.win.lParam == 0)
        return LOWORD(m->msg.win.wParam);
    return 0;
}
