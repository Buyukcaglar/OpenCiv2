/*
 * The native window's menu bar on Windows: a Win32 menu on SDL's window;
 * its WM_COMMAND arrives as an SDL_SYSWMEVENT (host_sdl.c).  The window's
 * title bar and menus follow the system's light or dark mode
 * (darkmode_win.c); its message boxes are setup_win.c's, in that mode too.
 *
 * The game's menus as Windows shows them: the empty items the game puts
 * between groups are separators (Windows 95 drew them as lines, themed
 * menus as blank rows), no check-mark column where nothing is checked.
 * The program's own About box is the last item of the last menu
 * (Civilopedia) and of the window's system menu.
 *
 * Full screen (Alt+Enter, host_sdl.c) takes the menu bar off the window:
 * a bar drawn by a window of its own, over the game at the top of the
 * screen, shows its titles while the pointer is at the screen's top edge
 * and opens their menus (also with Alt, F10 or Alt+letter); it hides again
 * once the pointer leaves it.
 */
#include <windows.h>
#include <commctrl.h>
#include <SDL.h>
#include <SDL_syswm.h>
#include "host.h"
#include "host_menu.h"
#include "darkmode_win.h"
#include "setup.h"

#define ID_HOST_ABOUT 0x7f00        /* the program's own items (the game's are 200 ...) */
#define SC_HOST_ABOUT 0x0110        /* in the system menu (below 0xf000, low 4 bits clear) */
#define BAR_CLASS L"Civ2PortMenuBar"
#define TIMER_BAR 1
#define WM_BAR_OPEN (WM_APP + 1)    /* wParam: the title to open; lParam: 1 from the keyboard */
#define WM_BAR_LAYOUT (WM_APP + 2)  /* the menu bar changed */
#define MAX_TITLES 16

static HWND main_hwnd;              /* SDL's window */
static HMENU bar;                   /* the menu bar: on main_hwnd, or full screen drawn by bar_hwnd */
static HWND bar_hwnd;               /* full screen: the menu bar's window */
static int in_menu;                 /* one of its menus is open */

static HWND hwnd_of(SDL_Window *window)
{
    SDL_SysWMinfo info;
    if (!window)
        return NULL;
    SDL_VERSION(&info.version);
    return SDL_GetWindowWMInfo(window, &info) ? info.info.win.window : NULL;
}

/* ---- full screen: the menu bar at the top edge ---- */

/* The bar is drawn here: Windows draws no dark menu bar on a window without
   a caption (the full-screen window has none).  Its titles are bar's; each
   opens its popup menu, which Windows draws, in the current mode.  The
   bar's window is per-monitor DPI aware (sharp at any scaling; the game's
   window is not); its procedure runs that way, so positions in it are the
   screen's pixels. */

typedef DPI_AWARENESS_CONTEXT(WINAPI *SetThreadDpiFn)(DPI_AWARENESS_CONTEXT);
typedef UINT(WINAPI *GetDpiForWindowFn)(HWND);
typedef BOOL(WINAPI *SpiForDpiFn)(UINT, UINT, PVOID, UINT, UINT);

static RECT titles[MAX_TITLES];     /* the titles' places (bar_hwnd's client area) */
static int ntitles, hot = -1, tracking = -1, open_next = -1, keyboard_cues, bar_height;
static HFONT bar_font;
static HHOOK menu_hook;
static HMENU menu_shown;            /* the popup menu now shown (WM_MENUSELECT) */
static int item_has_popup;          /* its selected item opens another */

static FARPROC user32(const char *name)
{
    return GetProcAddress(GetModuleHandleW(L"user32.dll"), name);
}

/* The menu font and the bar's height at the bar's DPI; the titles' places. */
static void bar_layout(void)
{
    GetDpiForWindowFn dpi_for_window = (GetDpiForWindowFn)(void *)user32("GetDpiForWindow");
    SpiForDpiFn spi_for_dpi = (SpiForDpiFn)(void *)user32("SystemParametersInfoForDpi");
    int dpi = dpi_for_window ? (int)dpi_for_window(bar_hwnd) : 96, i, x;
    NONCLIENTMETRICSW m;
    TEXTMETRICW tm;
    HDC dc;
    HFONT old;
    memset(&m, 0, sizeof m);
    m.cbSize = sizeof m;
    if (!(spi_for_dpi && spi_for_dpi(SPI_GETNONCLIENTMETRICS, sizeof m, &m, 0, (UINT)dpi))) {
        SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, sizeof m, &m, 0);
        m.lfMenuFont.lfHeight = MulDiv(m.lfMenuFont.lfHeight, dpi, 96);
    }
    if (bar_font)
        DeleteObject(bar_font);
    bar_font = CreateFontIndirectW(&m.lfMenuFont);
    dc = GetDC(bar_hwnd);
    old = SelectObject(dc, bar_font);
    GetTextMetricsW(dc, &tm);
    bar_height = tm.tmHeight + MulDiv(8, dpi, 96);
    ntitles = bar ? GetMenuItemCount(bar) : 0;
    if (ntitles > MAX_TITLES)
        ntitles = MAX_TITLES;
    for (i = 0, x = MulDiv(2, dpi, 96); i < ntitles; i++) {
        wchar_t t[128];
        RECT r = {0, 0, 0, 0};
        GetMenuStringW(bar, (UINT)i, t, 128, MF_BYPOSITION);
        DrawTextW(dc, t, -1, &r, DT_SINGLELINE | DT_CALCRECT);
        SetRect(&titles[i], x, 0, x + r.right + MulDiv(14, dpi, 96), bar_height);
        x = titles[i].right;
    }
    SelectObject(dc, old);
    ReleaseDC(bar_hwnd, dc);
}

/* Across the top of the game's screen. */
static void bar_place(void)
{
    MONITORINFO mi;
    mi.cbSize = sizeof mi;
    GetMonitorInfoW(MonitorFromWindow(main_hwnd, MONITOR_DEFAULTTONEAREST), &mi);
    bar_layout();
    SetWindowPos(bar_hwnd, HWND_TOPMOST, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left,
                 bar_height, SWP_NOACTIVATE);
    InvalidateRect(bar_hwnd, NULL, FALSE);
}

static void bar_show(int show)
{
    if (!bar_hwnd || !IsWindowVisible(bar_hwnd) == !show)
        return;
    if (show) {
        bar_place();
        ShowWindow(bar_hwnd, SW_SHOWNOACTIVATE);
    } else {
        ShowWindow(bar_hwnd, SW_HIDE);
        hot = -1;
    }
}

static int title_at(POINT p)
{
    int i;
    for (i = 0; i < ntitles; i++)
        if (PtInRect(&titles[i], p))
            return i;
    return -1;
}

static void bar_paint(HWND hwnd)
{
    PAINTSTRUCT ps;
    HDC dc = BeginPaint(hwnd, &ps);
    DmColors c;
    RECT r;
    HBRUSH b;
    int i;
    dm_colors(&c);
    GetClientRect(hwnd, &r);
    b = CreateSolidBrush(c.bg);
    FillRect(dc, &r, b);
    DeleteObject(b);
    SelectObject(dc, bar_font);
    SetBkMode(dc, TRANSPARENT);
    for (i = 0; i < ntitles; i++) {
        wchar_t t[128];
        GetMenuStringW(bar, (UINT)i, t, 128, MF_BYPOSITION);
        if (i == hot || i == tracking) {
            b = CreateSolidBrush(c.hot);
            FillRect(dc, &titles[i], b);
            DeleteObject(b);
        }
        SetTextColor(dc, GetMenuState(bar, (UINT)i, MF_BYPOSITION) & (MF_GRAYED | MF_DISABLED) ? c.dim : c.text);
        DrawTextW(dc, t, -1, &titles[i], DT_SINGLELINE | DT_CENTER | DT_VCENTER | (keyboard_cues ? 0 : DT_HIDEPREFIX));
    }
    EndPaint(hwnd, &ps);
}

/* While a menu is open: the pointer over another title, or Left and Right
   past the menu's ends, open that title's menu instead (as a menu bar does). */
static LRESULT CALLBACK menu_filter(int code, WPARAM wp, LPARAM lp)
{
    MSG *m = (MSG *)lp;
    if (code == MSGF_MENU && tracking >= 0) {
        if (m->message == WM_MOUSEMOVE) {
            POINT p = m->pt;
            int i;
            ScreenToClient(bar_hwnd, &p);
            if ((i = title_at(p)) >= 0 && i != tracking) {
                open_next = i;
                EndMenu();
                return 1;
            }
        } else if (m->message == WM_KEYDOWN && ntitles > 0 &&
                   ((m->wParam == VK_RIGHT && !item_has_popup) ||
                    (m->wParam == VK_LEFT && menu_shown == GetSubMenu(bar, tracking)))) {
            open_next = (tracking + (m->wParam == VK_RIGHT ? 1 : ntitles - 1)) % ntitles;
            keyboard_cues = 1;
            EndMenu();
            return 1;
        }
    }
    return CallNextHookEx(menu_hook, code, wp, lp);
}

/* Title i's menu, then whichever the user moves to; a command chosen goes
   to SDL's window, as from its own menu bar. */
static void bar_track(int i)
{
    in_menu = 1;
    while (i >= 0 && i < ntitles) {
        HMENU sub = GetSubMenu(bar, (UINT)i);
        TPMPARAMS tp;
        UINT cmd;
        tracking = i;
        open_next = -1;
        InvalidateRect(bar_hwnd, NULL, FALSE);
        UpdateWindow(bar_hwnd);
        if (!sub || (GetMenuState(bar, (UINT)i, MF_BYPOSITION) & (MF_GRAYED | MF_DISABLED)))
            break;
        tp.cbSize = sizeof tp;
        tp.rcExclude = titles[i];
        MapWindowPoints(bar_hwnd, NULL, (POINT *)&tp.rcExclude, 2);
        if (keyboard_cues)
            PostMessageW(main_hwnd, WM_KEYDOWN, VK_DOWN, 0);    /* (its first item selected) */
        menu_hook = SetWindowsHookExW(WH_MSGFILTER, menu_filter, NULL, GetCurrentThreadId());
        /* (owned by the game's window: a menu's owner must be the foreground window) */
        cmd = (UINT)TrackPopupMenuEx(sub, TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RETURNCMD | TPM_VERTICAL,
                                     tp.rcExclude.left, tp.rcExclude.bottom, main_hwnd, &tp);
        UnhookWindowsHookEx(menu_hook);
        menu_hook = NULL;
        if (cmd)
            PostMessageW(main_hwnd, WM_COMMAND, cmd, 0);
        i = open_next;
    }
    in_menu = 0;
    tracking = hot = -1;
    keyboard_cues = 0;
    InvalidateRect(bar_hwnd, NULL, FALSE);
}

/* Alt+letter: the title with that underlined letter (0: the first title). */
static int title_of_key(WCHAR key)
{
    int i;
    if (!key)
        return 0;
    for (i = 0; i < ntitles; i++) {
        wchar_t t[128], *amp;
        GetMenuStringW(bar, (UINT)i, t, 128, MF_BYPOSITION);
        if ((amp = wcschr(t, L'&')) && amp[1] &&
            CharUpperW((LPWSTR)(UINT_PTR)amp[1]) == CharUpperW((LPWSTR)(UINT_PTR)key))
            return i;
    }
    return -1;
}

static LRESULT CALLBACK bar_proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg) {
    case WM_MOUSEACTIVATE:
        return MA_NOACTIVATE;           /* the game's window keeps the keyboard */
    case WM_PAINT:
        bar_paint(hwnd);
        return 0;
    case WM_ERASEBKGND:
        return 1;
    case WM_MOUSEMOVE: {
        POINT p = {(short)LOWORD(lp), (short)HIWORD(lp)};
        TRACKMOUSEEVENT t = {sizeof t, TME_LEAVE, hwnd, 0};
        int i = title_at(p);
        TrackMouseEvent(&t);
        if (i != hot) {
            hot = i;
            InvalidateRect(hwnd, NULL, FALSE);
        }
        return 0;
    }
    case WM_MOUSELEAVE:
        if (hot >= 0) {
            hot = -1;
            InvalidateRect(hwnd, NULL, FALSE);
        }
        return 0;
    case WM_LBUTTONDOWN: {
        POINT p = {(short)LOWORD(lp), (short)HIWORD(lp)};
        int i = title_at(p);
        if (i >= 0)
            PostMessageW(hwnd, WM_BAR_OPEN, (WPARAM)i, 0);
        return 0;
    }
    case WM_BAR_OPEN:
        if (in_menu)
            return 0;
        bar_show(1);
        bar_layout();
        keyboard_cues = (int)lp;
        bar_track((int)wp);
        return 0;
    case WM_BAR_LAYOUT:
        if (IsWindowVisible(hwnd))
            bar_place();
        else
            bar_layout();
        return 0;
    case WM_TIMER: {
        POINT p;
        RECT r;
        MONITORINFO mi;
        if (wp != TIMER_BAR || in_menu)
            return 0;
        GetCursorPos(&p);
        if (!IsWindowVisible(hwnd)) {
            /* the pointer at the top edge, over the game */
            mi.cbSize = sizeof mi;
            GetMonitorInfoW(MonitorFromWindow(main_hwnd, MONITOR_DEFAULTTONEAREST), &mi);
            if (p.y <= mi.rcMonitor.top + 1 && p.x >= mi.rcMonitor.left && p.x < mi.rcMonitor.right &&
                GetForegroundWindow() == main_hwnd && IsWindowEnabled(main_hwnd))
                bar_show(1);
        } else {
            GetWindowRect(hwnd, &r);
            r.bottom += 8;
            if (!PtInRect(&r, p))
                bar_show(0);
        }
        return 0;
    }
    }
    if (dm_changed(msg, lp)) {
        dm_window(hwnd);
        InvalidateRect(hwnd, NULL, FALSE);
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

static void bar_create(void)
{
    static int registered;
    SetThreadDpiFn set_thread_dpi = (SetThreadDpiFn)(void *)user32("SetThreadDpiAwarenessContext");
    DPI_AWARENESS_CONTEXT old = NULL;
    if (!registered) {
        WNDCLASSEXW wc;
        memset(&wc, 0, sizeof wc);
        wc.cbSize = sizeof wc;
        wc.lpfnWndProc = bar_proc;
        wc.hInstance = GetModuleHandleW(NULL);
        wc.hCursor = LoadCursorW(NULL, (LPCWSTR)IDC_ARROW);
        wc.lpszClassName = BAR_CLASS;
        RegisterClassExW(&wc);
        registered = 1;
    }
    if (set_thread_dpi)
        old = set_thread_dpi(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    bar_hwnd = CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_NOACTIVATE, BAR_CLASS, L"", WS_POPUP, 0, 0,
                               10, 10, main_hwnd, NULL, GetModuleHandleW(NULL), NULL);
    if (set_thread_dpi && old)
        set_thread_dpi(old);
    if (!bar_hwnd)
        return;
    dm_window(bar_hwnd);                /* (its popup menus in the current mode) */
    SendMessageW(bar_hwnd, WM_BAR_LAYOUT, 0, 0);
    SetTimer(bar_hwnd, TIMER_BAR, 100, NULL);
}

void host_win_full_screen(SDL_Window *window, int full)
{
    HWND hwnd = hwnd_of(window);
    if (!hwnd)
        return;
    if (full) {
        /* the menu bar off the window first: SDL sizes the window for what it has */
        SetMenu(hwnd, NULL);
        if (!bar_hwnd)
            bar_create();
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    } else {
        if (bar_hwnd) {
            DestroyWindow(bar_hwnd);
            bar_hwnd = NULL;
            in_menu = 0;
        }
        SetMenu(hwnd, bar);
        SDL_SetWindowFullscreen(window, 0);
        DrawMenuBar(hwnd);
    }
}

/* ---- SDL's window ---- */

static LRESULT CALLBACK main_proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp, UINT_PTR id, DWORD_PTR data)
{
    (void)id;
    (void)data;
    switch (msg) {
    case WM_COMMAND:
        if (HIWORD(wp) == 0 && lp == 0 && LOWORD(wp) == ID_HOST_ABOUT) {
            setup_about(hwnd);
            return 0;
        }
        break;
    case WM_SYSCOMMAND:
        if ((wp & 0xfff0) == SC_HOST_ABOUT) {
            setup_about(hwnd);
            return 0;
        }
        /* full screen: Alt, F10 or Alt+letter opens the menu bar's menu */
        if ((wp & 0xfff0) == SC_KEYMENU && bar_hwnd && lp != ' ') {
            int i = title_of_key((WCHAR)lp);
            if (i >= 0)
                PostMessageW(bar_hwnd, WM_BAR_OPEN, (WPARAM)i, 1);
            return 0;
        }
        break;
    case WM_MENUSELECT:
        if (in_menu) {          /* (the full-screen bar's menu: menu_filter) */
            menu_shown = (HMENU)lp;
            item_has_popup = HIWORD(wp) != 0xffff && (HIWORD(wp) & MF_POPUP);  /* (0xffff: none selected) */
        }
        break;
    case WM_ACTIVATE:
        if (LOWORD(wp) == WA_INACTIVE && bar_hwnd && !in_menu)
            ShowWindow(bar_hwnd, SW_HIDE);
        break;
    }
    return DefSubclassProc(hwnd, msg, wp, lp);
}

/* The About box in the window's system menu, above Close. */
static void system_menu(HWND hwnd)
{
    HMENU m = GetSystemMenu(hwnd, FALSE);
    if (!m)
        return;
    InsertMenuW(m, SC_CLOSE, MF_BYCOMMAND | MF_STRING, SC_HOST_ABOUT, L"&About " OPENCIV2_NAME L"\x2026");
    InsertMenuW(m, SC_CLOSE, MF_BYCOMMAND | MF_SEPARATOR, 0, NULL);
}

void host_win_theme(SDL_Window *window)
{
    static HWND themed;
    HWND hwnd = hwnd_of(window);
    if (hwnd && hwnd != themed) {
        dm_menu_bar(hwnd);
        SetWindowSubclass(hwnd, main_proc, 2, 0);
        system_menu(hwnd);
        themed = main_hwnd = hwnd;
    }
}

int host_win_message_box(SDL_Window *window, int icon, const char *title, const char *text, int nbuttons,
                         const char *const *labels, const int *ids, int enter, int escape)
{
    return setup_message_box(hwnd_of(window), icon, title, text, nbuttons, labels, ids, enter, escape);
}

/* ---- the game's menus ---- */

/* A separator, unless it would lead, follow another or end the menu. */
static void add_separator(HMENU menu)
{
    int n = GetMenuItemCount(menu);
    if (n > 0 && !(GetMenuState(menu, (UINT)(n - 1), MF_BYPOSITION) & MF_SEPARATOR))
        AppendMenuW(menu, MF_SEPARATOR, 0, NULL);
}

/* A popup as it ends: no separator last; no check-mark column if nothing is checked. */
static void finish_popup(HMENU menu)
{
    int n = GetMenuItemCount(menu), i, checked = 0;
    MENUINFO mi;
    while (n > 0 && (GetMenuState(menu, (UINT)(n - 1), MF_BYPOSITION) & MF_SEPARATOR))
        DeleteMenu(menu, (UINT)--n, MF_BYPOSITION);
    for (i = 0; i < n; i++)
        if (GetMenuState(menu, (UINT)i, MF_BYPOSITION) & MF_CHECKED)
            checked = 1;
    memset(&mi, 0, sizeof mi);
    mi.cbSize = sizeof mi;
    mi.fMask = MIM_STYLE;
    GetMenuInfo(menu, &mi);
    mi.dwStyle = checked ? mi.dwStyle & ~(DWORD)MNS_NOCHECK : mi.dwStyle | MNS_NOCHECK;
    SetMenuInfo(menu, &mi);
}

void host_menu_apply(SDL_Window *window, const HostMenuItem *items, int n)
{
    HWND hwnd = hwnd_of(window);
    HMENU old, stack[4], popups[64], last = NULL;
    int i, npopups = 0;
    if (!hwnd)
        return;
    host_win_theme(window);
    old = bar;
    bar = CreateMenu();
    stack[0] = bar;
    for (i = 0; i < n; i++) {
        const HostMenuItem *it = &items[i];
        UINT flags = (it->flags & HOST_MENU_GRAYED ? MF_GRAYED : 0) | (it->flags & HOST_MENU_CHECKED ? MF_CHECKED : 0);
        HMENU parent;
        if (it->level < 0 || it->level > 2)
            continue;
        parent = stack[it->level];
        if ((it->flags & HOST_MENU_SEPARATOR) || (!(it->flags & HOST_MENU_POPUP) && !*it->text)) {
            add_separator(parent);
        } else if (it->flags & HOST_MENU_POPUP) {
            HMENU sub = CreatePopupMenu();
            AppendMenuA(parent, MF_POPUP | flags, (UINT_PTR)sub, it->text);
            stack[it->level + 1] = sub;
            if (npopups < (int)(sizeof popups / sizeof popups[0]))
                popups[npopups++] = sub;
            if (it->level == 0)
                last = sub;
        } else {
            AppendMenuA(parent, MF_STRING | flags, (UINT_PTR)it->id, it->text);
        }
    }
    if (last) {
        AppendMenuW(last, MF_SEPARATOR, 0, NULL);
        AppendMenuW(last, MF_STRING, ID_HOST_ABOUT, L"About " OPENCIV2_NAME L"\x2026");
    }
    for (i = 0; i < npopups; i++)
        finish_popup(popups[i]);
    if (bar_hwnd) {
        SendMessageW(bar_hwnd, WM_BAR_LAYOUT, 0, 0);
    } else {
        SetMenu(hwnd, bar);
        DrawMenuBar(hwnd);
    }
    if (old)
        DestroyMenu(old);
}

int host_menu_syswm_command(const void *msg)
{
    const SDL_SysWMmsg *m = msg;
    if (m && m->subsystem == SDL_SYSWM_WINDOWS && m->msg.win.msg == WM_COMMAND && HIWORD(m->msg.win.wParam) == 0 &&
        m->msg.win.lParam == 0)
        return LOWORD(m->msg.win.wParam);
    return 0;
}
