/*
 * The set-up window and the message boxes (setup.h), in the system's
 * light or dark mode (darkmode_win.c).
 *
 * The set-up window asks for the user's copy of the game (a file: archive
 * or CD image; or a folder; or either dropped on it), shows the import
 * (setup_files.c, on a thread of its own) and, when files could not be
 * verified, which and why.  Its text is drawn here; the buttons and the
 * report's text field are Windows' own controls, themed.  It is per-monitor
 * DPI aware (the game's window is not: it is created that way only).
 */
#define COBJMACROS
#include <windows.h>
#include <commctrl.h>
#include <shellapi.h>
#include <shobjidl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "darkmode_win.h"
#include "setup.h"

#define CLASS_NAME L"Civ2PortSetup"
#define TITLE L"Civilization II"

enum { VIEW_CHOOSE, VIEW_WORK, VIEW_FAILED, VIEW_MESSAGE, VIEW_ABOUT };
enum { ID_ARCHIVE = 100, ID_FOLDER, ID_QUIT, ID_CANCEL, ID_COPY, ID_AGAIN, ID_REPORT, ID_MSG = 200,
       ID_LICENSE = 300, ID_ABOUT = 310 };
#define TIMER_POLL 1
#define MAX_BUTTONS 8
#define MAX_ABOUT 16

/* ---- text ---- */

static wchar_t *wide(const char *s)
{
    int n = MultiByteToWideChar(CP_UTF8, 0, s ? s : "", -1, NULL, 0);
    wchar_t *w = malloc((size_t)(n > 0 ? n : 1) * sizeof *w);
    if (!w)
        abort();
    if (n <= 0 || !MultiByteToWideChar(CP_UTF8, 0, s ? s : "", -1, w, n))
        w[0] = 0;
    return w;
}

static char *utf8(const wchar_t *w)
{
    int n = WideCharToMultiByte(CP_UTF8, 0, w, -1, NULL, 0, NULL, NULL);
    char *s = malloc((size_t)(n > 0 ? n : 1));
    if (!s)
        abort();
    if (n <= 0 || !WideCharToMultiByte(CP_UTF8, 0, w, -1, s, n, NULL, NULL))
        s[0] = 0;
    return s;
}

/* "\n" -> "\r\n" for the edit control. */
static wchar_t *crlf(const char *s)
{
    size_t n = strlen(s), i, k = 0;
    char *t = malloc(2 * n + 1);
    wchar_t *w;
    if (!t)
        abort();
    for (i = 0; i < n; i++) {
        if (s[i] == '\n' && (i == 0 || s[i - 1] != '\r'))
            t[k++] = '\r';
        t[k++] = s[i];
    }
    t[k] = 0;
    w = wide(t);
    free(t);
    return w;
}

/* ---- DPI ---- */

typedef DPI_AWARENESS_CONTEXT(WINAPI *SetThreadDpiFn)(DPI_AWARENESS_CONTEXT);
typedef UINT(WINAPI *GetDpiForWindowFn)(HWND);
typedef BOOL(WINAPI *SpiForDpiFn)(UINT, UINT, PVOID, UINT, UINT);
typedef BOOL(WINAPI *AdjustForDpiFn)(LPRECT, DWORD, BOOL, DWORD, UINT);

static SetThreadDpiFn set_thread_dpi;
static GetDpiForWindowFn get_dpi_for_window;
static SpiForDpiFn spi_for_dpi;
static AdjustForDpiFn adjust_for_dpi;

static void dpi_init(void)
{
    HMODULE u = GetModuleHandleW(L"user32.dll");
    set_thread_dpi = (SetThreadDpiFn)(void *)GetProcAddress(u, "SetThreadDpiAwarenessContext");
    get_dpi_for_window = (GetDpiForWindowFn)(void *)GetProcAddress(u, "GetDpiForWindow");
    spi_for_dpi = (SpiForDpiFn)(void *)GetProcAddress(u, "SystemParametersInfoForDpi");
    adjust_for_dpi = (AdjustForDpiFn)(void *)GetProcAddress(u, "AdjustWindowRectExForDpi");
}

/* Windows created between begin and end are per-monitor DPI aware. */
static DPI_AWARENESS_CONTEXT dpi_begin(void)
{
    return set_thread_dpi ? set_thread_dpi(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2) : NULL;
}

static void dpi_end(DPI_AWARENESS_CONTEXT old)
{
    if (set_thread_dpi && old)
        set_thread_dpi(old);
}

/* ---- the window ---- */

typedef struct Shared {
    CRITICAL_SECTION lock;
    char what[256], detail[1024];
    double fraction;
    int done, ok, cancel;
    char *report;
} Shared;

typedef struct Win {
    HWND hwnd, owner;
    int view, dpi;
    HFONT font, title, mono;
    DmColors c;
    HBRUSH field_brush, bg_brush;
    /* the choose view's text: why it is shown */
    wchar_t *intro;
    /* VIEW_WORK */
    Shared sh;
    HANDLE thread;
    char *source, *game_dir;
    int phase;                  /* indeterminate progress animation */
    /* VIEW_FAILED */
    HWND report;
    /* VIEW_MESSAGE */
    wchar_t *msg_text;
    int icon, nbuttons, enter, escape, chosen;
    int ids[MAX_BUTTONS];
    HWND buttons[MAX_BUTTONS];
    HWND bquit, barchive, bfolder, bcancel, bcopy, bagain;
    /* VIEW_ABOUT: its lines (about_lines), the licence's field */
    HWND about[MAX_ABOUT], license;
    HFONT link;
    int result;                 /* the set-up: 1 the game is ready, 0 quit */
    int closed;
} Win;

static int px(Win *w, int dips) { return MulDiv(dips, w->dpi, 96); }

static void fonts(Win *w)
{
    NONCLIENTMETRICSW m;
    LOGFONTW lf;
    if (w->font)
        DeleteObject(w->font);
    if (w->title)
        DeleteObject(w->title);
    if (w->mono)
        DeleteObject(w->mono);
    if (w->link)
        DeleteObject(w->link);
    memset(&m, 0, sizeof m);
    m.cbSize = sizeof m;
    if (!(spi_for_dpi && spi_for_dpi(SPI_GETNONCLIENTMETRICS, sizeof m, &m, 0, (UINT)w->dpi))) {
        SystemParametersInfoW(SPI_GETNONCLIENTMETRICS, sizeof m, &m, 0);
        m.lfMessageFont.lfHeight = MulDiv(m.lfMessageFont.lfHeight, w->dpi, 96);
    }
    w->font = CreateFontIndirectW(&m.lfMessageFont);
    lf = m.lfMessageFont;
    lf.lfHeight = MulDiv(lf.lfHeight, 3, 2);
    lf.lfWeight = FW_SEMIBOLD;
    w->title = CreateFontIndirectW(&lf);
    lf = m.lfMessageFont;
    lf.lfWeight = FW_NORMAL;
    lstrcpyW(lf.lfFaceName, L"Consolas");
    lf.lfPitchAndFamily = FIXED_PITCH | FF_MODERN;
    w->mono = CreateFontIndirectW(&lf);
    lf = m.lfMessageFont;
    lf.lfUnderline = TRUE;
    w->link = CreateFontIndirectW(&lf);
}

static void colors(Win *w)
{
    dm_colors(&w->c);
    if (w->field_brush)
        DeleteObject(w->field_brush);
    if (w->bg_brush)
        DeleteObject(w->bg_brush);
    w->field_brush = CreateSolidBrush(w->c.field);
    w->bg_brush = CreateSolidBrush(w->c.bg);
}

static HWND button(Win *w, int id, const wchar_t *text, int primary)
{
    HWND b = CreateWindowExW(0, WC_BUTTONW, text,
                             WS_CHILD | WS_TABSTOP | (primary ? BS_DEFPUSHBUTTON : BS_PUSHBUTTON), 0, 0, 10, 10,
                             w->hwnd, (HMENU)(INT_PTR)id, GetModuleHandleW(NULL), NULL);
    SendMessageW(b, WM_SETFONT, (WPARAM)w->font, TRUE);
    dm_control(b);
    return b;
}

static int text_height(Win *w, HFONT f, const wchar_t *s, int width)
{
    HDC dc = GetDC(w->hwnd);
    RECT r = {0, 0, width, 0};
    HFONT old = SelectObject(dc, f);
    DrawTextW(dc, s, -1, &r, DT_WORDBREAK | DT_EDITCONTROL | DT_CALCRECT | DT_NOPREFIX);
    SelectObject(dc, old);
    ReleaseDC(w->hwnd, dc);
    return r.bottom;
}

static int button_width(Win *w, HWND b)
{
    wchar_t t[128];
    HDC dc = GetDC(w->hwnd);
    SIZE s = {0, 0};
    HFONT old = SelectObject(dc, w->font);
    int n = GetWindowTextW(b, t, 128);
    GetTextExtentPoint32W(dc, t, n, &s);
    SelectObject(dc, old);
    ReleaseDC(w->hwnd, dc);
    return s.cx + px(w, 32) > px(w, 96) ? s.cx + px(w, 32) : px(w, 96);
}

static const wchar_t *const choose_title = L"Set up Civilization II";
static const wchar_t *const choose_text =
    L"This program plays Civilization II Multiplayer Gold Edition with the files of your own copy of the game.\n\n"
    L"Choose where they are:\n"
    L"\x2022  an archive (.zip, .7z, .rar) with the game or its CD image in it,\n"
    L"\x2022  a CD image (.cue with its .bin, or .iso), or\n"
    L"\x2022  a folder with the installed game.\n\n"
    L"The files the game needs are checked and copied into the GameData folder next to this program; "
    L"from then on it starts by itself, wherever the program and GameData are copied together.";

/* The About box (as Civ1RE's): who made it, where it lives, its licence. */
enum { A_TITLE, A_DIM, A_TEXT, A_LINK, A_GAP };
static const struct {
    int kind;
    const wchar_t *text;
} about_lines[] = {
    {A_TITLE, L"" CIV2RE_NAME " v" CIV2RE_VERSION},
    {A_DIM, L"Civilization II Multiplayer Gold Edition for 64-bit Windows"},
    {A_GAP, NULL},
    {A_TEXT, L"Windows port by Onur BUYUKCAGLAR"},
    {A_TEXT, L"with Anthropic Claude AI assistance"},
    {A_LINK, L"" CIV2RE_URL},
    {A_GAP, NULL},
    {A_TEXT, L"Based on Richard Penman's reconstruction of the game's source"},
    {A_LINK, L"" CIV2RE_UPSTREAM_URL},
    {A_GAP, NULL},
    {A_TEXT, L"Icon: \"Icon Civilization II\" by alexielios"},
    {A_LINK, L"" CIV2RE_ICON_URL},
};
#define N_ABOUT ((int)(sizeof about_lines / sizeof about_lines[0]))

static const wchar_t about_license[] =
    L"MIT License\r\n\r\n"
    L"Copyright (c) 2026 Richard Penman\r\n"
    L"Copyright (c) 2026 Onur BUYUKCAGLAR\r\n\r\n"
    L"Permission is hereby granted, free of charge, to any person obtaining a copy of this software and "
    L"associated documentation files (the \"Software\"), to deal in the Software without restriction, including "
    L"without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell "
    L"copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the "
    L"following conditions:\r\n\r\n"
    L"The above copyright notice and this permission notice shall be included in all copies or substantial "
    L"portions of the Software.\r\n\r\n"
    L"THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT "
    L"LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO "
    L"EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN "
    L"AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE "
    L"USE OR OTHER DEALINGS IN THE SOFTWARE.\r\n\r\n"
    L"The licence covers this program's own code. Civilization II, its program and its data belong to their "
    L"owners; they are not part of this software, which needs a copy of the original game to run.\r\n\r\n"
    L"The program's icon, \"Icon Civilization II\" by alexielios (DeviantArt), is not covered by this licence.";

static int text_width(Win *w, HFONT f, const wchar_t *s)
{
    HDC dc = GetDC(w->hwnd);
    SIZE z = {0, 0};
    HFONT old = SelectObject(dc, f);
    GetTextExtentPoint32W(dc, s, lstrlenW(s), &z);
    SelectObject(dc, old);
    ReleaseDC(w->hwnd, dc);
    return z.cx;
}

static HFONT about_font(Win *w, int i)
{
    return about_lines[i].kind == A_TITLE ? w->title : about_lines[i].kind == A_LINK ? w->link : w->font;
}

/* Where things go: the window's client size for its view, and the controls placed. */
static void layout(Win *w, int place, int *cw, int *ch)
{
    int m = px(w, 24), width = px(w, w->view == VIEW_MESSAGE ? 420 : w->view == VIEW_FAILED ? 720 : 560);
    int y = m, bh = px(w, 32), gap = px(w, 8), inner = width - 2 * m, x, i;
    HWND row[MAX_BUTTONS];
    int nrow = 0;
    if (w->view == VIEW_ABOUT) {
        /* the icon at the left, the lines beside it; the licence below */
        int col = m + px(w, 48) + px(w, 16), cw = width - m - col, lh = px(w, 140);
        for (i = 0; i < N_ABOUT; i++) {
            HFONT f = about_font(w, i);
            int h, tw;
            if (about_lines[i].kind == A_GAP) {
                y += px(w, 10);
                continue;
            }
            h = text_height(w, f, about_lines[i].text, cw);
            tw = text_width(w, f, about_lines[i].text);
            if (place)      /* (a link only as wide as its text: the click is on it) */
                SetWindowPos(w->about[i], NULL, col, y, about_lines[i].kind == A_LINK && tw < cw ? tw : cw, h,
                             SWP_NOZORDER);
            y += h + (about_lines[i].kind == A_TITLE ? px(w, 2) : 0);
        }
        y += px(w, 16);
        if (place)
            SetWindowPos(w->about[N_ABOUT], NULL, m, y, inner, text_height(w, w->font, L"X", inner), SWP_NOZORDER);
        y += text_height(w, w->font, L"X", inner) + px(w, 6);
        if (place)
            SetWindowPos(w->license, NULL, m, y, inner, lh, SWP_NOZORDER);
        y += lh + px(w, 20);
        row[nrow++] = w->buttons[0];
    } else if (w->view == VIEW_MESSAGE) {
        int icon = w->icon >= 0 ? px(w, 32) + px(w, 16) : 0;
        int th = text_height(w, w->font, w->msg_text, inner - icon);
        if (th > px(w, 500)) {
            width = px(w, 640);
            inner = width - 2 * m;
            th = text_height(w, w->font, w->msg_text, inner - icon);
        }
        y += (th > px(w, 32) ? th : px(w, 32)) + px(w, 24);
        for (i = 0; i < w->nbuttons; i++)
            row[nrow++] = w->buttons[i];
    } else if (w->view == VIEW_CHOOSE) {
        y += text_height(w, w->title, choose_title, inner) + px(w, 12);
        if (w->intro)
            y += text_height(w, w->font, w->intro, inner) + px(w, 12);
        y += text_height(w, w->font, choose_text, inner) + px(w, 20);
        if (place) {
            int a = button_width(w, w->barchive), b = button_width(w, w->bfolder);
            SetWindowPos(w->barchive, NULL, m, y, a, bh, SWP_NOZORDER);
            SetWindowPos(w->bfolder, NULL, m + a + gap, y, b, bh, SWP_NOZORDER);
        }
        y += bh + px(w, 8);
        y += text_height(w, w->font, L"Or drop it on this window.", inner) + px(w, 24);
        row[nrow++] = w->bquit;
    } else if (w->view == VIEW_WORK) {
        y += text_height(w, w->title, L"Setting up", inner) + px(w, 16);
        y += text_height(w, w->font, L"X", inner) * 2 + px(w, 12);
        y += px(w, 6) + px(w, 24);
        row[nrow++] = w->bcancel;
    } else {
        int eh = px(w, 320);
        y += text_height(w, w->title, L"X", inner) + px(w, 12);
        if (place)
            SetWindowPos(w->report, NULL, m, y, inner, eh, SWP_NOZORDER);
        y += eh + px(w, 20);
        row[nrow++] = w->bcopy;
        row[nrow++] = w->bagain;
        row[nrow++] = w->bquit;
    }
    /* the buttons: a row at the bottom right */
    if (place) {
        x = width - m;
        for (i = nrow - 1; i >= 0; i--) {
            int bw = button_width(w, row[i]);
            x -= bw;
            SetWindowPos(row[i], NULL, x, y, bw, bh, SWP_NOZORDER);
            x -= gap;
        }
    }
    y += bh + m;
    *cw = width;
    *ch = y;
}

static void show(HWND h, int on)
{
    if (h)
        ShowWindow(h, on ? SW_SHOW : SW_HIDE);
}

/* Size the window for its view (centred where it was, or on the owner / screen). */
static void relayout(Win *w, int center)
{
    int cw, ch;
    RECT r;
    DWORD style = (DWORD)GetWindowLongPtrW(w->hwnd, GWL_STYLE), ex = (DWORD)GetWindowLongPtrW(w->hwnd, GWL_EXSTYLE);
    show(w->barchive, w->view == VIEW_CHOOSE);
    show(w->bfolder, w->view == VIEW_CHOOSE);
    show(w->bquit, w->view == VIEW_CHOOSE || w->view == VIEW_FAILED);
    show(w->bcancel, w->view == VIEW_WORK);
    show(w->report, w->view == VIEW_FAILED);
    show(w->bcopy, w->view == VIEW_FAILED);
    show(w->bagain, w->view == VIEW_FAILED);
    layout(w, 1, &cw, &ch);
    r.left = r.top = 0;
    r.right = cw;
    r.bottom = ch;
    if (adjust_for_dpi)
        adjust_for_dpi(&r, style, FALSE, ex, (UINT)w->dpi);
    else
        AdjustWindowRectEx(&r, style, FALSE, ex);
    {
        RECT cur, area;
        HMONITOR mon;
        MONITORINFO mi;
        int ww = r.right - r.left, wh = r.bottom - r.top, x, y;
        if (center && w->owner && IsWindowVisible(w->owner))
            GetWindowRect(w->owner, &cur);
        else
            GetWindowRect(w->hwnd, &cur);
        mon = MonitorFromRect(&cur, MONITOR_DEFAULTTONEAREST);
        mi.cbSize = sizeof mi;
        GetMonitorInfoW(mon, &mi);
        area = mi.rcWork;
        if (center && !(w->owner && IsWindowVisible(w->owner)))
            cur = area;
        x = (cur.left + cur.right - ww) / 2;
        y = (cur.top + cur.bottom - wh) / 2;
        if (x + ww > area.right)
            x = area.right - ww;
        if (y + wh > area.bottom)
            y = area.bottom - wh;
        if (x < area.left)
            x = area.left;
        if (y < area.top)
            y = area.top;
        SetWindowPos(w->hwnd, NULL, x, y, ww, wh, SWP_NOZORDER | SWP_NOACTIVATE);
    }
    InvalidateRect(w->hwnd, NULL, TRUE);
}

static void paint_text(HDC dc, HFONT f, COLORREF c, const wchar_t *s, RECT *r, UINT flags)
{
    RECT t = *r;
    if (flags & DT_WORDBREAK)
        flags |= DT_EDITCONTROL;   /* also break words too long for a line, such as paths */
    SelectObject(dc, f);
    SetTextColor(dc, c);
    DrawTextW(dc, s, -1, &t, flags | DT_NOPREFIX | DT_CALCRECT);
    DrawTextW(dc, s, -1, r, flags | DT_NOPREFIX);
    r->top += t.bottom - t.top;
}

static void fill_rect(HDC dc, int x, int y, int cx, int cy, COLORREF c)
{
    RECT r = {x, y, x + cx, y + cy};
    HBRUSH b = CreateSolidBrush(c);
    FillRect(dc, &r, b);
    DeleteObject(b);
}

/* A text field's border (the report, the licence). */
static void frame_field(Win *w, HDC dc, HWND field)
{
    RECT e;
    HBRUSH b = CreateSolidBrush(w->c.border);
    GetWindowRect(field, &e);
    MapWindowPoints(NULL, w->hwnd, (POINT *)&e, 2);
    InflateRect(&e, 1, 1);
    FrameRect(dc, &e, b);
    DeleteObject(b);
}

static void paint(Win *w)
{
    PAINTSTRUCT ps;
    HDC dc = BeginPaint(w->hwnd, &ps);
    RECT client, r;
    int m = px(w, 24);
    GetClientRect(w->hwnd, &client);
    FillRect(dc, &client, w->bg_brush);
    SetBkMode(dc, TRANSPARENT);
    r.left = m;
    r.right = client.right - m;
    r.top = m;
    r.bottom = client.bottom;
    if (w->view == VIEW_ABOUT) {
        HICON icon = LoadImageW(GetModuleHandleW(NULL), MAKEINTRESOURCEW(1), IMAGE_ICON, px(w, 48), px(w, 48), 0);
        if (icon) {
            DrawIconEx(dc, r.left, r.top, icon, px(w, 48), px(w, 48), 0, NULL, DI_NORMAL);
            DestroyIcon(icon);
        }
        frame_field(w, dc, w->license);
    } else if (w->view == VIEW_MESSAGE) {
        if (w->icon >= 0) {
            HICON icon = NULL;
            LPCWSTR id = (LPCWSTR)(w->icon == 2 ? IDI_ERROR : w->icon == 1 ? IDI_WARNING : IDI_INFORMATION);
            if (FAILED(LoadIconWithScaleDown(NULL, id, px(w, 32), px(w, 32), &icon)))
                icon = LoadIconW(NULL, id);
            DrawIconEx(dc, r.left, r.top, icon, px(w, 32), px(w, 32), 0, NULL, DI_NORMAL);
            DestroyIcon(icon);
            r.left += px(w, 48);
        }
        paint_text(dc, w->font, w->c.text, w->msg_text, &r, DT_WORDBREAK);
    } else if (w->view == VIEW_CHOOSE) {
        paint_text(dc, w->title, w->c.text, choose_title, &r, DT_WORDBREAK);
        r.top += px(w, 12);
        if (w->intro) {
            paint_text(dc, w->font, w->c.error, w->intro, &r, DT_WORDBREAK);
            r.top += px(w, 12);
        }
        paint_text(dc, w->font, w->c.text, choose_text, &r, DT_WORDBREAK);
        r.top += px(w, 20) + px(w, 32) + px(w, 8);
        paint_text(dc, w->font, w->c.dim, L"Or drop it on this window.", &r, DT_WORDBREAK);
    } else if (w->view == VIEW_WORK) {
        wchar_t *what, *detail;
        double f;
        int bar, width = r.right - r.left, line;
        EnterCriticalSection(&w->sh.lock);
        what = wide(w->sh.what);
        detail = wide(w->sh.detail);
        f = w->sh.fraction;
        LeaveCriticalSection(&w->sh.lock);
        paint_text(dc, w->title, w->c.text, L"Setting up", &r, DT_SINGLELINE);
        r.top += px(w, 16);
        line = text_height(w, w->font, L"X", 100);
        paint_text(dc, w->font, w->c.text, *what ? what : L"Starting", &r, DT_SINGLELINE | DT_END_ELLIPSIS);
        {
            RECT d = r;
            d.bottom = d.top + line;
            paint_text(dc, w->font, w->c.dim, detail, &d, DT_SINGLELINE | DT_PATH_ELLIPSIS);
            r.top += line;
        }
        r.top += px(w, 12);
        bar = px(w, 6);
        fill_rect(dc, r.left, r.top, width, bar, w->c.track);
        if (f >= 0) {
            fill_rect(dc, r.left, r.top, (int)(width * (f > 1 ? 1 : f)), bar, w->c.accent);
        } else {
            /* not known how far: a piece going across */
            int seg = width / 4, pos = (w->phase % 100) * (width + seg) / 100 - seg;
            int a = pos < 0 ? 0 : pos, b = pos + seg > width ? width : pos + seg;
            if (b > a)
                fill_rect(dc, r.left + a, r.top, b - a, bar, w->c.accent);
        }
        free(what);
        free(detail);
    } else {
        paint_text(dc, w->title, w->c.text, L"The game's files could not be verified", &r, DT_SINGLELINE);
        frame_field(w, dc, w->report);
    }
    EndPaint(w->hwnd, &ps);
}

/* ---- choosing ---- */

static char *pick(Win *w, int folder)
{
    IFileOpenDialog *d = NULL;
    IShellItem *item = NULL;
    wchar_t *path = NULL;
    char *result = NULL;
    HRESULT co = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (FAILED(CoCreateInstance(&CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, &IID_IFileOpenDialog, (void **)&d)))
        goto out;
    if (folder) {
        IFileOpenDialog_SetOptions(d, FOS_PICKFOLDERS | FOS_FORCEFILESYSTEM | FOS_PATHMUSTEXIST);
        IFileOpenDialog_SetTitle(d, L"Choose the folder with the installed game");
    } else {
        static const COMDLG_FILTERSPEC types[] = {
            {L"Archives and CD images (*.zip, *.7z, *.rar, *.cue, *.iso, *.bin)",
             L"*.zip;*.7z;*.rar;*.cue;*.iso;*.bin;*.img"},
            {L"All files", L"*.*"}};
        IFileOpenDialog_SetOptions(d, FOS_FORCEFILESYSTEM | FOS_FILEMUSTEXIST | FOS_PATHMUSTEXIST);
        IFileOpenDialog_SetFileTypes(d, 2, types);
        IFileOpenDialog_SetTitle(d, L"Choose the game's archive or CD image");
    }
    if (IFileOpenDialog_Show(d, w->hwnd) != S_OK || FAILED(IFileOpenDialog_GetResult(d, &item)) ||
        FAILED(IShellItem_GetDisplayName(item, SIGDN_FILESYSPATH, &path)))
        goto out;
    result = utf8(path);
out:
    if (path)
        CoTaskMemFree(path);
    if (item)
        IShellItem_Release(item);
    if (d)
        IFileOpenDialog_Release(d);
    if (SUCCEEDED(co))
        CoUninitialize();
    return result;
}

/* ---- importing ---- */

static void on_status(void *user, const char *what, const char *detail)
{
    Shared *s = user;
    EnterCriticalSection(&s->lock);
    snprintf(s->what, sizeof s->what, "%s", what);
    snprintf(s->detail, sizeof s->detail, "%s", detail);
    LeaveCriticalSection(&s->lock);
}

static void on_fraction(void *user, double f)
{
    Shared *s = user;
    EnterCriticalSection(&s->lock);
    s->fraction = f;
    LeaveCriticalSection(&s->lock);
}

static int on_cancelled(void *user)
{
    Shared *s = user;
    int c;
    EnterCriticalSection(&s->lock);
    c = s->cancel;
    LeaveCriticalSection(&s->lock);
    return c;
}

static DWORD WINAPI import_thread(LPVOID arg)
{
    Win *w = arg;
    SetupProgress p;
    char *report = NULL;
    int ok;
    p.user = &w->sh;
    p.status = on_status;
    p.fraction = on_fraction;
    p.cancelled = on_cancelled;
    ok = setup_import(w->source, w->game_dir, &p, &report);
    EnterCriticalSection(&w->sh.lock);
    w->sh.ok = ok;
    w->sh.report = report;
    w->sh.done = 1;
    LeaveCriticalSection(&w->sh.lock);
    return 0;
}

static void start_import(Win *w, char *source)
{
    free(w->source);
    w->source = source;
    w->sh.done = w->sh.ok = w->sh.cancel = 0;
    w->sh.fraction = -1;
    w->sh.what[0] = w->sh.detail[0] = 0;
    free(w->sh.report);
    w->sh.report = NULL;
    w->view = VIEW_WORK;
    EnableWindow(w->bcancel, TRUE);
    relayout(w, 0);
    SetFocus(w->bcancel);
    w->thread = CreateThread(NULL, 0, import_thread, w, 0, NULL);
    SetTimer(w->hwnd, TIMER_POLL, 50, NULL);
}

static void import_done(Win *w)
{
    WaitForSingleObject(w->thread, INFINITE);
    CloseHandle(w->thread);
    w->thread = NULL;
    KillTimer(w->hwnd, TIMER_POLL);
    if (w->sh.ok) {
        w->result = 1;
        DestroyWindow(w->hwnd);
        return;
    }
    if (w->sh.cancel) {
        w->view = VIEW_CHOOSE;
        relayout(w, 0);
        return;
    }
    {
        wchar_t *t = crlf(w->sh.report ? w->sh.report : "");
        SetWindowTextW(w->report, t);
        free(t);
    }
    w->view = VIEW_FAILED;
    relayout(w, 0);
    SetFocus(w->bagain);
}

static void copy_report(Win *w)
{
    int n = GetWindowTextLengthW(w->report);
    HGLOBAL g = GlobalAlloc(GMEM_MOVEABLE, (size_t)(n + 1) * sizeof(wchar_t));
    if (!g)
        return;
    GetWindowTextW(w->report, GlobalLock(g), n + 1);
    GlobalUnlock(g);
    if (OpenClipboard(w->hwnd)) {
        EmptyClipboard();
        if (SetClipboardData(CF_UNICODETEXT, g))
            g = NULL;
        CloseClipboard();
    }
    if (g)
        GlobalFree(g);
    SetWindowTextW(w->bcopy, L"Copied");
}

/* ---- the window procedure ---- */

static void restyle(Win *w)
{
    int i;
    colors(w);
    dm_window(w->hwnd);
    HWND all[] = {w->bquit, w->barchive, w->bfolder, w->bcancel, w->bcopy, w->bagain, w->report, w->license};
    for (i = 0; i < (int)(sizeof all / sizeof all[0]); i++)
        if (all[i])
            dm_control(all[i]);
    for (i = 0; i < w->nbuttons; i++)
        dm_control(w->buttons[i]);
    InvalidateRect(w->hwnd, NULL, TRUE);
}

static void refont(Win *w)
{
    int i;
    fonts(w);
    HWND all[] = {w->bquit, w->barchive, w->bfolder, w->bcancel, w->bcopy, w->bagain};
    for (i = 0; i < (int)(sizeof all / sizeof all[0]); i++)
        if (all[i])
            SendMessageW(all[i], WM_SETFONT, (WPARAM)w->font, TRUE);
    for (i = 0; i < w->nbuttons; i++)
        SendMessageW(w->buttons[i], WM_SETFONT, (WPARAM)w->font, TRUE);
    if (w->report)
        SendMessageW(w->report, WM_SETFONT, (WPARAM)w->mono, TRUE);
    if (w->license)
        SendMessageW(w->license, WM_SETFONT, (WPARAM)w->font, TRUE);
    for (i = 0; i <= N_ABOUT; i++)
        if (w->about[i])
            SendMessageW(w->about[i], WM_SETFONT, (WPARAM)(i < N_ABOUT ? about_font(w, i) : w->font), TRUE);
}

static void choose(Win *w, int folder)
{
    char *p = pick(w, folder);
    if (p)
        start_import(w, p);
}

static LRESULT CALLBACK proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    Win *w = (Win *)GetWindowLongPtrW(hwnd, GWLP_USERDATA);
    if (msg == WM_NCCREATE) {
        w = ((CREATESTRUCTW *)lp)->lpCreateParams;
        w->hwnd = hwnd;
        SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR)w);
    }
    if (!w)
        return DefWindowProcW(hwnd, msg, wp, lp);
    if (dm_changed(msg, lp)) {
        restyle(w);
        if (msg == WM_SETTINGCHANGE) {
            refont(w);
            relayout(w, 0);
        }
    }
    switch (msg) {
    case WM_PAINT:
        paint(w);
        return 0;
    case WM_ERASEBKGND:
        return 1;
    case WM_CTLCOLORSTATIC: {
        /* the About box's lines: on the window's background (links in the accent colour) */
        int id = GetDlgCtrlID((HWND)lp) - ID_ABOUT;
        if (id >= 0 && id <= N_ABOUT) {
            int kind = id < N_ABOUT ? about_lines[id].kind : A_TEXT;
            SetTextColor((HDC)wp, kind == A_LINK ? w->c.accent : kind == A_DIM ? w->c.dim : w->c.text);
            SetBkColor((HDC)wp, w->c.bg);
            return (LRESULT)w->bg_brush;
        }
    }
        /* fall through: the read-only text fields */
    case WM_CTLCOLOREDIT:
        SetTextColor((HDC)wp, w->c.text);
        SetBkColor((HDC)wp, w->c.field);
        return (LRESULT)w->field_brush;
    case WM_SETCURSOR: {
        int id = GetDlgCtrlID((HWND)wp) - ID_ABOUT;
        if (id >= 0 && id < N_ABOUT && about_lines[id].kind == A_LINK) {
            SetCursor(LoadCursorW(NULL, (LPCWSTR)IDC_HAND));
            return TRUE;
        }
        break;
    }
    case WM_CTLCOLORBTN:
        return (LRESULT)w->bg_brush;
    case WM_DPICHANGED: {
        RECT *r = (RECT *)lp;
        w->dpi = HIWORD(wp);
        refont(w);
        SetWindowPos(hwnd, NULL, r->left, r->top, r->right - r->left, r->bottom - r->top, SWP_NOZORDER | SWP_NOACTIVATE);
        relayout(w, 0);
        return 0;
    }
    case WM_TIMER:
        if (wp == TIMER_POLL && w->view == VIEW_WORK) {
            int done;
            w->phase += 2;
            EnterCriticalSection(&w->sh.lock);
            done = w->sh.done;
            LeaveCriticalSection(&w->sh.lock);
            if (done)
                import_done(w);
            else
                InvalidateRect(hwnd, NULL, FALSE);
        }
        return 0;
    case WM_DROPFILES: {
        HDROP drop = (HDROP)wp;
        if (w->view == VIEW_CHOOSE || w->view == VIEW_FAILED) {
            UINT n = DragQueryFileW(drop, 0, NULL, 0);
            wchar_t *path = malloc((n + 1) * sizeof *path);
            if (path && DragQueryFileW(drop, 0, path, n + 1))
                start_import(w, utf8(path));
            free(path);
        }
        DragFinish(drop);
        return 0;
    }
    case WM_COMMAND:
        if (w->view == VIEW_ABOUT) {
            int id = LOWORD(wp) - ID_ABOUT;
            if (id >= 0 && id < N_ABOUT && about_lines[id].kind == A_LINK && HIWORD(wp) == STN_CLICKED)
                ShellExecuteW(hwnd, L"open", about_lines[id].text, NULL, NULL, SW_SHOWNORMAL);
            else if (LOWORD(wp) == ID_MSG || LOWORD(wp) == IDOK || LOWORD(wp) == IDCANCEL)
                DestroyWindow(hwnd);
            return 0;
        }
        if (w->view == VIEW_MESSAGE && LOWORD(wp) >= ID_MSG && LOWORD(wp) < ID_MSG + w->nbuttons) {
            w->chosen = w->ids[LOWORD(wp) - ID_MSG];
            DestroyWindow(hwnd);
            return 0;
        }
        switch (LOWORD(wp)) {
        case ID_ARCHIVE:
            choose(w, 0);
            return 0;
        case ID_FOLDER:
            choose(w, 1);
            return 0;
        case ID_AGAIN:
            SetWindowTextW(w->bcopy, L"Copy report");
            w->view = VIEW_CHOOSE;
            relayout(w, 0);
            SetFocus(w->barchive);
            return 0;
        case ID_COPY:
            copy_report(w);
            return 0;
        case ID_CANCEL:
        case IDCANCEL:                  /* (Escape) */
            if (w->view == VIEW_WORK) {
                EnterCriticalSection(&w->sh.lock);
                w->sh.cancel = 1;
                LeaveCriticalSection(&w->sh.lock);
                on_status(&w->sh, "Cancelling", "");
                EnableWindow(w->bcancel, FALSE);
            } else if (w->view == VIEW_MESSAGE) {
                if (w->escape >= 0 && w->escape < w->nbuttons) {
                    w->chosen = w->ids[w->escape];
                    DestroyWindow(hwnd);
                }
            } else {
                DestroyWindow(hwnd);
            }
            return 0;
        case ID_QUIT:
            if (w->view != VIEW_WORK)
                DestroyWindow(hwnd);
            return 0;
        case IDOK: {                    /* (Enter) */
            /* a focused button is the one pressed, as in a dialog */
            HWND f = GetFocus();
            if (f && GetParent(f) == hwnd &&
                (SendMessageW(f, WM_GETDLGCODE, 0, 0) & (DLGC_DEFPUSHBUTTON | DLGC_UNDEFPUSHBUTTON))) {
                SendMessageW(hwnd, WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(f), BN_CLICKED), (LPARAM)f);
                return 0;
            }
        }
            if (w->view == VIEW_MESSAGE && w->enter >= 0 && w->enter < w->nbuttons) {
                w->chosen = w->ids[w->enter];
                DestroyWindow(hwnd);
            } else if (w->view == VIEW_CHOOSE) {
                choose(w, 0);
            } else if (w->view == VIEW_FAILED) {
                SendMessageW(hwnd, WM_COMMAND, ID_AGAIN, 0);
            }
            return 0;
        }
        break;
    case WM_CLOSE:
        if (w->view == VIEW_WORK) {
            SendMessageW(hwnd, WM_COMMAND, ID_CANCEL, 0);
            return 0;
        }
        if (w->view == VIEW_MESSAGE && w->escape >= 0 && w->escape < w->nbuttons)
            w->chosen = w->ids[w->escape];
        DestroyWindow(hwnd);
        return 0;
    case WM_DESTROY:
        w->closed = 1;
        return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

static void register_class(void)
{
    static int done;
    WNDCLASSEXW wc;
    if (done)
        return;
    done = 1;
    memset(&wc, 0, sizeof wc);
    wc.cbSize = sizeof wc;
    wc.lpfnWndProc = proc;
    wc.hInstance = GetModuleHandleW(NULL);
    wc.hCursor = LoadCursorW(NULL, (LPCWSTR)IDC_ARROW);
    wc.lpszClassName = CLASS_NAME;
    wc.hIcon = LoadImageW(wc.hInstance, MAKEINTRESOURCEW(1), IMAGE_ICON, GetSystemMetrics(SM_CXICON),
                          GetSystemMetrics(SM_CYICON), 0);
    wc.hIconSm = LoadImageW(wc.hInstance, MAKEINTRESOURCEW(1), IMAGE_ICON, GetSystemMetrics(SM_CXSMICON),
                            GetSystemMetrics(SM_CYSMICON), 0);
    RegisterClassExW(&wc);
}

static void init_common(void)
{
    static int done;
    INITCOMMONCONTROLSEX icc;
    if (done)
        return;
    done = 1;
    icc.dwSize = sizeof icc;
    icc.dwICC = ICC_STANDARD_CLASSES;
    InitCommonControlsEx(&icc);
    dpi_init();
    dm_init();
}

/* Create w's window (hidden), its fonts and colours.  The thread is left
   per-monitor DPI aware (*old: as it was), for the controls to be made
   the same way; dpi_end(*old) after. */
static int create(Win *w, const wchar_t *title, DWORD style, DPI_AWARENESS_CONTEXT *old)
{
    init_common();
    register_class();
    *old = dpi_begin();
    CreateWindowExW(WS_EX_DLGMODALFRAME | WS_EX_CONTROLPARENT | (w->owner ? 0 : WS_EX_APPWINDOW), CLASS_NAME, title,
                    style, CW_USEDEFAULT, CW_USEDEFAULT, 100, 100, w->owner, NULL, GetModuleHandleW(NULL), w);
    if (!w->hwnd) {
        dpi_end(*old);
        return 0;
    }
    w->dpi = get_dpi_for_window ? (int)get_dpi_for_window(w->hwnd) : 96;
    if (w->dpi <= 0)
        w->dpi = 96;
    fonts(w);
    colors(w);
    dm_window(w->hwnd);
    return 1;
}

static void destroy_resources(Win *w)
{
    if (w->font)
        DeleteObject(w->font);
    if (w->title)
        DeleteObject(w->title);
    if (w->mono)
        DeleteObject(w->mono);
    if (w->link)
        DeleteObject(w->link);
    if (w->field_brush)
        DeleteObject(w->field_brush);
    if (w->bg_brush)
        DeleteObject(w->bg_brush);
}

/* Until the window is closed: its messages (and its owner disabled). */
static void run_modal(Win *w)
{
    MSG m;
    if (w->owner)
        EnableWindow(w->owner, FALSE);
    ShowWindow(w->hwnd, SW_SHOW);
    SetForegroundWindow(w->hwnd);
    while (!w->closed && GetMessageW(&m, NULL, 0, 0) > 0) {
        if (!IsDialogMessageW(w->hwnd, &m)) {
            TranslateMessage(&m);
            DispatchMessageW(&m);
        }
    }
    if (w->owner) {
        EnableWindow(w->owner, TRUE);
        SetForegroundWindow(w->owner);
    }
    if (!w->closed && m.message == WM_QUIT)
        PostQuitMessage((int)m.wParam);
}

/* ---- message boxes ---- */

int setup_message_box(void *owner_hwnd, int icon, const char *title, const char *text, int nbuttons,
                      const char *const *labels, const int *ids, int enter, int escape)
{
    Win w;
    DPI_AWARENESS_CONTEXT old;
    wchar_t *t = wide(title && *title ? title : "Civilization II");
    int i;
    memset(&w, 0, sizeof w);
    w.owner = owner_hwnd && IsWindow(owner_hwnd) ? owner_hwnd : NULL;
    w.view = VIEW_MESSAGE;
    w.icon = icon;
    w.msg_text = wide(text);
    w.nbuttons = nbuttons > MAX_BUTTONS ? MAX_BUTTONS : nbuttons < 1 ? 1 : nbuttons;
    w.enter = enter;
    w.escape = escape;
    w.chosen = -1;
    if (!create(&w, t, WS_POPUP | WS_CAPTION | WS_SYSMENU, &old)) {
        free(t);
        free(w.msg_text);
        return -1;
    }
    for (i = 0; i < w.nbuttons; i++) {
        wchar_t *l = wide(nbuttons ? labels[i] : "OK");
        w.ids[i] = nbuttons ? ids[i] : 1;
        w.buttons[i] = button(&w, ID_MSG + i, l, i == enter);
        ShowWindow(w.buttons[i], SW_SHOW);
        free(l);
    }
    dpi_end(old);
    relayout(&w, 1);
    MessageBeep(icon == 2 ? MB_ICONERROR : icon == 1 ? MB_ICONWARNING : MB_ICONINFORMATION);
    SetFocus(w.buttons[enter >= 0 && enter < w.nbuttons ? enter : 0]);
    run_modal(&w);
    destroy_resources(&w);
    free(t);
    free(w.msg_text);
    return w.chosen;
}

/* ---- the About box ---- */

void setup_about(void *owner_hwnd)
{
    Win w;
    DPI_AWARENESS_CONTEXT old;
    HINSTANCE inst = GetModuleHandleW(NULL);
    int i;
    memset(&w, 0, sizeof w);
    w.owner = owner_hwnd && IsWindow(owner_hwnd) ? owner_hwnd : NULL;
    w.view = VIEW_ABOUT;
    w.nbuttons = 1;
    w.enter = w.escape = 0;
    if (!create(&w, L"About " CIV2RE_NAME " v" CIV2RE_VERSION, WS_POPUP | WS_CAPTION | WS_SYSMENU, &old))
        return;
    for (i = 0; i <= N_ABOUT; i++) {
        int link = i < N_ABOUT && about_lines[i].kind == A_LINK;
        if (i < N_ABOUT && about_lines[i].kind == A_GAP)
            continue;
        w.about[i] = CreateWindowExW(0, WC_STATICW, i < N_ABOUT ? about_lines[i].text : L"License:",
                                     WS_CHILD | WS_VISIBLE | SS_NOPREFIX | (link ? SS_NOTIFY : 0), 0, 0, 10, 10,
                                     w.hwnd, (HMENU)(INT_PTR)(ID_ABOUT + i), inst, NULL);
    }
    w.license = CreateWindowExW(0, WC_EDITW, about_license,
                                WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_VSCROLL | ES_MULTILINE | ES_READONLY |
                                    ES_AUTOVSCROLL,
                                0, 0, 10, 10, w.hwnd, (HMENU)(INT_PTR)ID_LICENSE, inst, NULL);
    SendMessageW(w.license, EM_SETMARGINS, EC_LEFTMARGIN | EC_RIGHTMARGIN, MAKELPARAM(px(&w, 6), px(&w, 6)));
    dm_control(w.license);
    w.ids[0] = 1;
    w.buttons[0] = button(&w, ID_MSG, L"OK", 1);
    ShowWindow(w.buttons[0], SW_SHOW);
    refont(&w);
    dpi_end(old);
    relayout(&w, 1);
    SetFocus(w.buttons[0]);
    run_modal(&w);
    destroy_resources(&w);
}

/* ---- the set-up window ---- */

/* 1: the game was set up in game_dir; 0: the user quit.  intro: why it is
   shown (NULL: the first time); source: start importing it at once. */
static int setup_window(const char *game_dir, const char *intro, const char *source)
{
    Win w;
    DPI_AWARENESS_CONTEXT old;
    memset(&w, 0, sizeof w);
    InitializeCriticalSection(&w.sh.lock);
    w.view = VIEW_CHOOSE;
    w.game_dir = (char *)game_dir;
    w.intro = intro ? wide(intro) : NULL;
    w.enter = w.escape = -1;
    if (!create(&w, TITLE, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, &old)) {
        DeleteCriticalSection(&w.sh.lock);
        free(w.intro);
        return 0;
    }
    w.barchive = button(&w, ID_ARCHIVE, L"Archive or CD image\x2026", 1);
    w.bfolder = button(&w, ID_FOLDER, L"Game folder\x2026", 0);
    w.bquit = button(&w, ID_QUIT, L"Quit", 0);
    w.bcancel = button(&w, ID_CANCEL, L"Cancel", 0);
    w.bcopy = button(&w, ID_COPY, L"Copy report", 0);
    w.bagain = button(&w, ID_AGAIN, L"Choose another\x2026", 1);
    w.report = CreateWindowExW(0, WC_EDITW, L"",
                               WS_CHILD | WS_TABSTOP | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_READONLY |
                                   ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_NOHIDESEL,
                               0, 0, 10, 10, w.hwnd, (HMENU)(INT_PTR)ID_REPORT, GetModuleHandleW(NULL), NULL);
    SendMessageW(w.report, WM_SETFONT, (WPARAM)w.mono, TRUE);
    SendMessageW(w.report, EM_SETMARGINS, EC_LEFTMARGIN | EC_RIGHTMARGIN, MAKELPARAM(px(&w, 6), px(&w, 6)));
    dm_control(w.report);
    dpi_end(old);
    DragAcceptFiles(w.hwnd, TRUE);
    relayout(&w, 1);
    if (source)
        start_import(&w, strdup(source));
    else
        SetFocus(w.barchive);
    run_modal(&w);
    destroy_resources(&w);
    DeleteCriticalSection(&w.sh.lock);
    free(w.intro);
    free(w.source);
    free(w.sh.report);
    return w.result;
}

/* ---- where the game is ---- */

static int dir_exists(const char *p)
{
    DWORD a = GetFileAttributesA(p);
    return a != INVALID_FILE_ATTRIBUTES && (a & FILE_ATTRIBUTE_DIRECTORY);
}

static int file_exists(const char *p)
{
    DWORD a = GetFileAttributesA(p);
    return a != INVALID_FILE_ATTRIBUTES && !(a & FILE_ATTRIBUTE_DIRECTORY);
}

static void fail(const char *what, const char *detail)
{
    char *text = malloc(strlen(what) + strlen(detail ? detail : "") + 4);
    const char *ok = "OK";
    int id = 1;
    if (!text)
        abort();
    sprintf(text, "%s%s%s", what, detail ? "\n\n" : "", detail ? detail : "");
    setup_message_box(NULL, 2, "Civilization II", text, 1, &ok, &id, 0, 0);
    free(text);
}

/* The reconstruction's own files into game_dir, and CIV2_DATA naming them. */
static int port_files(const char *game_dir)
{
    char *error = NULL, data[4300];
    if (!setup_port_files(game_dir, &error)) {
        fail("The game cannot start: its folder could not be completed.", error);
        free(error);
        return 0;
    }
    snprintf(data, sizeof data, "%s\\native", game_dir);
    _putenv_s("CIV2_DATA", data);
    return 1;
}

int setup_choose_game(int argc, char **argv, char *game, size_t size)
{
    char dir[4096], game_data[4200], *report = NULL;
    const char *source = NULL;
    int force = 0, i, ok;
    setup_program_dir(dir, sizeof dir);
    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--setup"))
            force = 1;
        else if (!source)
            source = argv[i];
    }
    if (source && dir_exists(source) && !force) {
        /* a folder: the game, where it is (the harness; the old way) */
        char fonts[4200];
        snprintf(game, size, "%s", source);
        snprintf(fonts, sizeof fonts, "%s\\data\\fonts.bin", dir);
        if (!getenv("CIV2_DATA") && !file_exists(fonts))
            return port_files(source);
        return 1;
    }
    snprintf(game_data, sizeof game_data, "%s\\GameData", dir);
    if (source && !dir_exists(source) && !file_exists(source)) {
        fail("There is no such file or folder:", source);
        return 0;
    }
    if (!source && !force && setup_check(game_data, &report)) {
        snprintf(game, size, "%s", game_data);
        return port_files(game_data);
    }
    {
        char *intro = NULL;
        if (report && dir_exists(game_data)) {
            const char *head = "The GameData folder next to this program is incomplete:\n";
            intro = malloc(strlen(head) + strlen(report) + 1);
            if (!intro)
                abort();
            sprintf(intro, "%s%s", head, report);
        }
        ok = setup_window(game_data, intro, source);
        free(intro);
        free(report);
    }
    if (!ok)
        return 0;
    snprintf(game, size, "%s", game_data);
    return port_files(game_data);
}
