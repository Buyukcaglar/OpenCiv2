/*
 * Light and dark mode for Win32 windows (darkmode_win.h).
 *
 * Windows has no public API for a desktop program's dark mode beyond the
 * title bar (DWMWA_USE_IMMERSIVE_DARK_MODE).  The rest is what Explorer
 * and Notepad use, by ordinal from uxtheme.dll (Windows 10 1809 and
 * later; nothing happens where they are missing): SetPreferredAppMode
 * (135) for popup menus, AllowDarkModeForWindow (133) and the
 * "DarkMode_Explorer" theme for controls and scroll bars, FlushMenuThemes
 * (136).  The menu bar itself is drawn here, from the undocumented
 * WM_UAHDRAWMENU / WM_UAHDRAWMENUITEM messages Windows sends a window
 * before drawing its menu bar.
 */
#include <windows.h>
#include <commctrl.h>
#include <dwmapi.h>
#include <stdlib.h>
#include <string.h>
#include <uxtheme.h>
#include "darkmode_win.h"

#ifndef DWMWA_USE_IMMERSIVE_DARK_MODE
#define DWMWA_USE_IMMERSIVE_DARK_MODE 20
#endif

typedef int(WINAPI *SetPreferredAppModeFn)(int mode);
typedef BOOL(WINAPI *AllowDarkModeForWindowFn)(HWND hwnd, BOOL allow);
typedef void(WINAPI *FlushMenuThemesFn)(void);
typedef void(WINAPI *RefreshPolicyFn)(void);

static SetPreferredAppModeFn set_preferred_app_mode;
static AllowDarkModeForWindowFn allow_dark_for_window;
static FlushMenuThemesFn flush_menu_themes;
static RefreshPolicyFn refresh_policy;

void dm_init(void)
{
    static int done;
    HMODULE ux;
    OSVERSIONINFOW v;
    typedef LONG(WINAPI * RtlGetVersionFn)(OSVERSIONINFOW *);
    RtlGetVersionFn get_version;
    if (done)
        return;
    done = 1;
    /* the ordinals mean these functions from Windows 10 1809 (build 17763) on */
    memset(&v, 0, sizeof v);
    v.dwOSVersionInfoSize = sizeof v;
    get_version = (RtlGetVersionFn)(void *)GetProcAddress(GetModuleHandleW(L"ntdll.dll"), "RtlGetVersion");
    if (!get_version || get_version(&v) || v.dwMajorVersion < 10 || v.dwBuildNumber < 17763)
        return;
    if (!(ux = LoadLibraryExW(L"uxtheme.dll", NULL, LOAD_LIBRARY_SEARCH_SYSTEM32)))
        return;
    set_preferred_app_mode = (SetPreferredAppModeFn)(void *)GetProcAddress(ux, MAKEINTRESOURCEA(135));
    allow_dark_for_window = (AllowDarkModeForWindowFn)(void *)GetProcAddress(ux, MAKEINTRESOURCEA(133));
    flush_menu_themes = (FlushMenuThemesFn)(void *)GetProcAddress(ux, MAKEINTRESOURCEA(136));
    refresh_policy = (RefreshPolicyFn)(void *)GetProcAddress(ux, MAKEINTRESOURCEA(104));
    if (set_preferred_app_mode)
        set_preferred_app_mode(1);              /* AllowDark: follow the system */
    if (refresh_policy)
        refresh_policy();
    if (flush_menu_themes)
        flush_menu_themes();
}

int dm_high_contrast(void)
{
    HIGHCONTRASTW hc;
    hc.cbSize = sizeof hc;
    return SystemParametersInfoW(SPI_GETHIGHCONTRAST, sizeof hc, &hc, 0) && (hc.dwFlags & HCF_HIGHCONTRASTON);
}

int dm_dark(void)
{
    DWORD light = 1, size = sizeof light;
    const char *force = getenv("CIV2_THEME");          /* dark, light: either, whatever the system's */
    if (dm_high_contrast())
        return 0;
    if (force && (!strcmp(force, "dark") || !strcmp(force, "light")))
        return !strcmp(force, "dark");
    if (RegGetValueW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
                     L"AppsUseLightTheme", RRF_RT_REG_DWORD, NULL, &light, &size) != ERROR_SUCCESS)
        return 0;
    return light == 0;
}

void dm_colors(DmColors *c)
{
    if (dm_high_contrast()) {
        c->bg = GetSysColor(COLOR_WINDOW);
        c->field = GetSysColor(COLOR_WINDOW);
        c->text = GetSysColor(COLOR_WINDOWTEXT);
        c->dim = GetSysColor(COLOR_WINDOWTEXT);
        c->border = GetSysColor(COLOR_WINDOWTEXT);
        c->accent = GetSysColor(COLOR_HIGHLIGHT);
        c->track = GetSysColor(COLOR_BTNFACE);
        c->hot = GetSysColor(COLOR_HIGHLIGHT);
        c->error = GetSysColor(COLOR_WINDOWTEXT);
    } else if (dm_dark()) {
        c->bg = RGB(0x20, 0x20, 0x20);
        c->field = RGB(0x2b, 0x2b, 0x2b);
        c->text = RGB(0xff, 0xff, 0xff);
        c->dim = RGB(0xc5, 0xc5, 0xc5);
        c->border = RGB(0x45, 0x45, 0x45);
        c->accent = RGB(0x4c, 0xc2, 0xff);
        c->track = RGB(0x45, 0x45, 0x45);
        c->hot = RGB(0x3d, 0x3d, 0x3d);
        c->error = RGB(0xff, 0x99, 0xa4);
    } else {
        c->bg = RGB(0xf3, 0xf3, 0xf3);
        c->field = RGB(0xff, 0xff, 0xff);
        c->text = RGB(0x1b, 0x1b, 0x1b);
        c->dim = RGB(0x5f, 0x5f, 0x5f);
        c->border = RGB(0xd0, 0xd0, 0xd0);
        c->accent = RGB(0x00, 0x5f, 0xb8);
        c->track = RGB(0xd6, 0xd6, 0xd6);
        c->hot = RGB(0xe0, 0xe0, 0xe0);
        c->error = RGB(0xc4, 0x2b, 0x1c);
    }
}

void dm_window(HWND hwnd)
{
    BOOL dark = dm_dark();
    if (allow_dark_for_window)
        allow_dark_for_window(hwnd, dark);
    if (FAILED(DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &dark, sizeof dark)))
        DwmSetWindowAttribute(hwnd, 19, &dark, sizeof dark);      /* (before Windows 10 20H1) */
    if (refresh_policy)
        refresh_policy();
    if (flush_menu_themes)
        flush_menu_themes();
}

void dm_control(HWND ctl)
{
    BOOL dark = dm_dark();
    if (allow_dark_for_window)
        allow_dark_for_window(ctl, dark);
    SetWindowTheme(ctl, dark ? L"DarkMode_Explorer" : L"Explorer", NULL);
    SendMessageW(ctl, WM_THEMECHANGED, 0, 0);
}

int dm_changed(UINT msg, LPARAM lp)
{
    if (msg == WM_THEMECHANGED || msg == WM_SYSCOLORCHANGE)
        return 1;
    return msg == WM_SETTINGCHANGE && lp &&
           (!lstrcmpW((LPCWSTR)lp, L"ImmersiveColorSet") || !lstrcmpW((LPCWSTR)lp, L"WindowsThemeElement"));
}

/* ---- the menu bar ---- */

#define WM_UAHDRAWMENU 0x0091
#define WM_UAHDRAWMENUITEM 0x0092

typedef struct UAHMENU { HMENU hmenu; HDC hdc; DWORD dwFlags; } UAHMENU;
typedef union UAHMENUITEMMETRICS {
    struct { DWORD cx, cy; } rgsizeBar[2];
    struct { DWORD cx, cy; } rgsizePopup[4];
} UAHMENUITEMMETRICS;
typedef struct UAHMENUPOPUPMETRICS { DWORD rgcx[4]; DWORD fUpdateMaxWidths : 2; } UAHMENUPOPUPMETRICS;
typedef struct UAHMENUITEM { int iPosition; UAHMENUITEMMETRICS umim; UAHMENUPOPUPMETRICS umpm; } UAHMENUITEM;
typedef struct UAHDRAWMENUITEM { DRAWITEMSTRUCT dis; UAHMENU um; UAHMENUITEM umi; } UAHDRAWMENUITEM;

static void fill(HDC dc, const RECT *r, COLORREF c)
{
    HBRUSH b = CreateSolidBrush(c);
    FillRect(dc, r, b);
    DeleteObject(b);
}

/* The line Windows draws under the menu bar, in the light colour: over it. */
static void menu_bar_line(HWND hwnd, COLORREF c)
{
    MENUBARINFO mbi;
    RECT client, window, line;
    HDC dc;
    mbi.cbSize = sizeof mbi;
    if (!GetMenu(hwnd) || !GetMenuBarInfo(hwnd, OBJID_MENU, 0, &mbi))
        return;
    GetClientRect(hwnd, &client);
    MapWindowPoints(hwnd, NULL, (POINT *)&client, 2);
    GetWindowRect(hwnd, &window);
    OffsetRect(&client, -window.left, -window.top);
    line = client;
    line.bottom = line.top;
    line.top--;
    if ((dc = GetWindowDC(hwnd))) {
        fill(dc, &line, c);
        ReleaseDC(hwnd, dc);
    }
}

static LRESULT CALLBACK menu_bar_proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp, UINT_PTR id, DWORD_PTR data)
{
    DmColors c;
    (void)id;
    (void)data;
    if (dm_changed(msg, lp)) {
        dm_window(hwnd);
        DrawMenuBar(hwnd);
        RedrawWindow(hwnd, NULL, NULL, RDW_FRAME | RDW_INVALIDATE);
    }
    if (!dm_dark())
        return DefSubclassProc(hwnd, msg, wp, lp);
    dm_colors(&c);
    switch (msg) {
    case WM_UAHDRAWMENU: {
        UAHMENU *um = (UAHMENU *)lp;
        MENUBARINFO mbi;
        RECT window;
        mbi.cbSize = sizeof mbi;
        if (!GetMenuBarInfo(hwnd, OBJID_MENU, 0, &mbi))
            break;
        GetWindowRect(hwnd, &window);
        OffsetRect(&mbi.rcBar, -window.left, -window.top);
        mbi.rcBar.top--;
        fill(um->hdc, &mbi.rcBar, c.bg);
        return TRUE;
    }
    case WM_UAHDRAWMENUITEM: {
        UAHDRAWMENUITEM *it = (UAHDRAWMENUITEM *)lp;
        wchar_t text[256];
        MENUITEMINFOW mii;
        UINT state = it->dis.itemState;
        UINT flags = DT_CENTER | DT_SINGLELINE | DT_VCENTER;
        memset(&mii, 0, sizeof mii);
        mii.cbSize = sizeof mii;
        mii.fMask = MIIM_STRING;
        mii.dwTypeData = text;
        mii.cch = sizeof text / sizeof text[0] - 1;
        text[0] = 0;
        GetMenuItemInfoW(it->um.hmenu, (UINT)it->umi.iPosition, TRUE, &mii);
        fill(it->um.hdc, &it->dis.rcItem, (state & (ODS_HOTLIGHT | ODS_SELECTED)) ? c.hot : c.bg);
        if (state & ODS_NOACCEL)
            flags |= DT_HIDEPREFIX;
        SetBkMode(it->um.hdc, TRANSPARENT);
        SetTextColor(it->um.hdc, (state & (ODS_INACTIVE | ODS_GRAYED | ODS_DISABLED)) ? c.dim : c.text);
        DrawTextW(it->um.hdc, text, -1, &it->dis.rcItem, flags);
        return TRUE;
    }
    case WM_NCPAINT:
    case WM_NCACTIVATE: {
        LRESULT r = DefSubclassProc(hwnd, msg, wp, lp);
        menu_bar_line(hwnd, c.bg);
        return r;
    }
    }
    return DefSubclassProc(hwnd, msg, wp, lp);
}

void dm_menu_bar(HWND hwnd)
{
    dm_init();
    dm_window(hwnd);
    SetWindowSubclass(hwnd, menu_bar_proc, 1, 0);
}
