/*
 * The standard controls the game uses (it subclasses them): EDIT, LISTBOX,
 * COMBOBOX, SCROLLBAR, plus minimal BUTTON and STATIC, and window scroll
 * bars.  Behaviour and look follow Wine's builtin controls.
 */
#include "plat.h"

#ifndef ODT_LISTBOX
#define ODT_LISTBOX 2
#endif

typedef struct {
    UINT CtlType, CtlID, itemID, itemAction, itemState;
    HWND hwndItem;
    HDC hDC;
    RECT rcItem;
    ULONG_PTR itemData;
} DRAWITEMSTRUCT_;

typedef struct {
    UINT CtlType, CtlID, itemID, itemWidth, itemHeight;
    ULONG_PTR itemData;
} MEASUREITEMSTRUCT_;

static void notify(HWND h, int code)
{
    Window *w = wnd_get(h);
    if (w && w->parent && w->parent != desktop)
        SendMessageA(w->parent->hwnd, WM_COMMAND, MAKEWPARAM((WORD)(uintptr_t)w->menu, code), (LPARAM)h);
}

static HFONT default_font(void) { return (HFONT)GetStockObject(SYSTEM_FONT); }

static void draw_edge(HDC hdc, const RECT *r, int sunken)
{
    /* Two-pixel 3D edge, as DrawEdge(EDGE_SUNKEN / EDGE_RAISED). */
    RECT e;
    COLORREF tl1 = sunken ? GetSysColor(COLOR_3DSHADOW) : GetSysColor(COLOR_3DLIGHT);
    COLORREF tl2 = sunken ? GetSysColor(COLOR_3DDKSHADOW) : GetSysColor(COLOR_3DHILIGHT);
    COLORREF br1 = sunken ? GetSysColor(COLOR_3DHILIGHT) : GetSysColor(COLOR_3DDKSHADOW);
    COLORREF br2 = sunken ? GetSysColor(COLOR_3DLIGHT) : GetSysColor(COLOR_3DSHADOW);
    DC *dc = dc_get(hdc);
    e = *r; e.bottom = e.top + 1; dc_fill_rect(dc, &e, tl1);
    e = *r; e.right = e.left + 1; dc_fill_rect(dc, &e, tl1);
    e = *r; e.top = e.bottom - 1; dc_fill_rect(dc, &e, br1);
    e = *r; e.left = e.right - 1; dc_fill_rect(dc, &e, br1);
    e = *r; e.left++; e.top++; e.right--; e.bottom--;
    {
        RECT f = e;
        f.bottom = f.top + 1; dc_fill_rect(dc, &f, tl2);
        f = e; f.right = f.left + 1; dc_fill_rect(dc, &f, tl2);
        f = e; f.top = f.bottom - 1; dc_fill_rect(dc, &f, br2);
        f = e; f.left = f.right - 1; dc_fill_rect(dc, &f, br2);
    }
}

/* ======================================================================
 * EDIT
 */

typedef struct {
    char *text;
    int len, cap, limit;
    int sel_start, sel_end;     /* sel_end is the caret */
    int first;                  /* first visible character (single line) */
    HFONT font;
    int focused, modified, readonly;
    int border;                 /* draws a one-pixel border itself */
    int left_margin, right_margin;
} Edit;

static Edit *edit_of(Window *w) { return w ? (Edit *)w->control : NULL; }

static void edit_set_text(Edit *e, const char *s)
{
    int n = s ? (int)strlen(s) : 0;
    if (e->limit && n > e->limit)
        n = e->limit;
    if (n + 1 > e->cap) {
        e->cap = n + 64;
        e->text = realloc(e->text, (size_t)e->cap);
    }
    memcpy(e->text, s ? s : "", (size_t)n);
    e->text[n] = 0;
    e->len = n;
    e->sel_start = e->sel_end = 0;
    e->first = 0;
}

static void edit_replace(Edit *e, const char *s)
{
    int a = e->sel_start < e->sel_end ? e->sel_start : e->sel_end;
    int b = e->sel_start < e->sel_end ? e->sel_end : e->sel_start;
    int n = (int)strlen(s);
    if (e->limit && e->len - (b - a) + n > e->limit)
        n = e->limit - (e->len - (b - a));
    if (n < 0)
        n = 0;
    if (e->len - (b - a) + n + 1 > e->cap) {
        e->cap = e->len - (b - a) + n + 64;
        e->text = realloc(e->text, (size_t)e->cap);
    }
    memmove(e->text + a + n, e->text + b, (size_t)(e->len - b + 1));
    memcpy(e->text + a, s, (size_t)n);
    e->len += n - (b - a);
    e->sel_start = e->sel_end = a + n;
    e->modified = 1;
}

static FontFace *font_face_of(HFONT f)
{
    Font *font = obj_get(f, OBJ_FONT);
    return font ? font->face : NULL;
}

/* Where the text starts (Wine's format rectangle): inside the border
 * (SM_CXBORDER + 1, vertically only if the line fits) and the margins. */
static void edit_origin(Window *w, int *x, int *y)
{
    Edit *e = edit_of(w);
    FontFace *f = font_face_of(e->font);
    int bw = e->border ? GetSystemMetrics(SM_CXBORDER) + 1 : 0, ch = w->client.bottom - w->client.top;
    *x = bw + e->left_margin;
    *y = f && ch >= text_height(f) + 2 * bw ? bw : 0;
}

/* WM_SETFONT: Wine's default margins for a TrueType font -- half the
 * average character width (GdiGetCharDimensions) -- if they fit. */
static void edit_font_margins(Window *w)
{
    static const char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    Edit *e = edit_of(w);
    FontFace *f = font_face_of(e->font);
    int width, cw = w->client.right - w->client.left;
    if (!f || e->font == default_font())
        return;
    width = (text_width(f, alphabet, 52) / 26 + 1) / 2;
    if (cw <= 0)
        cw = 80;
    if (cw < width / 2 * 2 + width * 2)
        return;
    e->left_margin = e->right_margin = width / 2;
}

static void edit_paint(Window *w, HDC hdc)
{
    Edit *e = edit_of(w);
    RECT r;
    FontFace *f = font_face_of(e->font);
    HBRUSH br;
    int x, y, a, b, margin;
    if (!f)
        return;
    GetClientRect(w->hwnd, &r);
    SelectObject(hdc, e->font);
    br = (HBRUSH)SendMessageA(w->parent && w->parent != desktop ? w->parent->hwnd : 0, WM_CTLCOLOREDIT,
                              (WPARAM)hdc, (LPARAM)w->hwnd);
    if (!br)
        br = GetSysColorBrush(COLOR_WINDOW);
    FillRect(hdc, &r, br);
    if (e->border)
        FrameRect(hdc, &r, GetSysColorBrush(COLOR_WINDOWFRAME));
    (void)margin;
    edit_origin(w, &x, &y);
    a = e->sel_start < e->sel_end ? e->sel_start : e->sel_end;
    b = e->sel_start < e->sel_end ? e->sel_end : e->sel_start;
    if (!e->focused && !(w->style & ES_NOHIDESEL))
        a = b = 0;
    {
        DC *dc = dc_get(hdc);
        int first = (w->style & ES_MULTILINE) ? 0 : e->first, i;
        SetBkMode(hdc, TRANSPARENT);
        x -= 0;
        for (i = first; i < e->len; ) {
            int run = i, sel = i >= a && i < b;
            while (run < e->len && (run >= a && run < b) == sel)
                run++;
            {
                int wdt = text_width(f, e->text + i, run - i);
                if (sel) {
                    RECT hl;
                    hl.left = x; hl.right = x + wdt; hl.top = y; hl.bottom = y + text_height(f);
                    dc_fill_rect(dc, &hl, GetSysColor(COLOR_HIGHLIGHT));
                    SetTextColor(hdc, GetSysColor(COLOR_HIGHLIGHTTEXT));
                } else {
                    SetTextColor(hdc, GetSysColor(COLOR_WINDOWTEXT));
                }
                text_draw(dc, x, y, e->text + i, run - i, &r);
                x += wdt;
            }
            i = run;
        }
        if (e->focused) {
            /* the caret (Wine's does not blink in the reference): one pixel
               wide, inverted, at the selection end */
            int cx, cy, k;
            edit_origin(w, &cx, &cy);
            for (k = first; k < e->sel_end && k < e->len; k++)
                cx += text_width(f, e->text + k, 1);
            PatBlt(hdc, cx, cy, 1, text_height(f), DSTINVERT);
        }
    }
}

static int edit_pos_from_x(Window *w, int px)
{
    Edit *e = edit_of(w);
    FontFace *f = font_face_of(e->font);
    int i, x, y;
    if (!f)
        return 0;
    edit_origin(w, &x, &y);
    for (i = e->first; i < e->len; i++) {
        int cw = text_width(f, e->text + i, 1);
        if (px < x + cw / 2)
            return i;
        x += cw;
    }
    return e->len;
}

/* Keep the caret visible in a single-line edit. */
static void edit_scroll(Window *w)
{
    Edit *e = edit_of(w);
    FontFace *f = font_face_of(e->font);
    RECT r;
    if (!f || (w->style & ES_MULTILINE))
        return;
    GetClientRect(w->hwnd, &r);
    if (e->sel_end < e->first)
        e->first = e->sel_end;
    while (e->first < e->sel_end && text_width(f, e->text + e->first, e->sel_end - e->first) > r.right - 2)
        e->first++;
}

LRESULT ctl_edit_proc(HWND h, UINT m, WPARAM wp, LPARAM lp)
{
    Window *w = wnd_get(h);
    Edit *e = edit_of(w);
    if (!w)
        return 0;
    if (!e && m != WM_NCCREATE)
        return DefWindowProcA(h, m, wp, lp);
    switch (m) {
    case WM_NCCREATE:
        e = calloc(1, sizeof *e);
        w->control = e;
        e->font = default_font();
        e->limit = 30000;
        /* As Wine's: a WS_BORDER edit without WS_EX_CLIENTEDGE draws its own
         * one-pixel border instead of having a frame. */
        if (w->exstyle & WS_EX_CLIENTEDGE)
            e->border = 0;
        else if (w->style & WS_BORDER) {
            e->border = 1;
            SetWindowLongA(h, GWL_STYLE, (LONG_PTR)(w->style & ~WS_BORDER));
        }
        e->readonly = (w->style & ES_READONLY) != 0;
        edit_set_text(e, w->text);
        return TRUE;
    case WM_DESTROY:
        free(e->text);
        free(e);
        w->control = NULL;
        return 0;
    case WM_SETTEXT:
        edit_set_text(e, (const char *)lp);
        InvalidateRect(h, NULL, TRUE);
        /* Wine: no notification for multiline edits */
        if (!(w->style & ES_MULTILINE)) {
            notify(h, EN_UPDATE);
            notify(h, EN_CHANGE);
        }
        return TRUE;
    case WM_GETTEXT:
        if (!wp)
            return 0;
        snprintf((char *)lp, wp, "%s", e->text);
        return (LRESULT)strlen((char *)lp);
    case WM_GETTEXTLENGTH:
        return e->len;
    case WM_SETFONT:
        e->font = wp ? (HFONT)wp : default_font();
        edit_font_margins(w);
        if (LOWORD(lp))
            InvalidateRect(h, NULL, TRUE);
        return 0;
    case WM_GETFONT:
        return (LRESULT)e->font;
    case WM_SETFOCUS:
        e->focused = 1;
        InvalidateRect(h, NULL, FALSE);
        notify(h, EN_SETFOCUS);
        return 0;
    case WM_KILLFOCUS:
        e->focused = 0;
        InvalidateRect(h, NULL, FALSE);
        notify(h, EN_KILLFOCUS);
        return 0;
    case WM_GETDLGCODE:
        return DLGC_WANTCHARS | DLGC_HASSETSEL | DLGC_WANTARROWS;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(h, &ps);
        edit_paint(w, hdc);
        EndPaint(h, &ps);
        return 0;
    }
    case WM_ERASEBKGND:
        return 1;
    case WM_LBUTTONDOWN:
        SetFocus(h);
        e->sel_start = e->sel_end = edit_pos_from_x(w, (short)LOWORD(lp));
        SetCapture(h);
        InvalidateRect(h, NULL, FALSE);
        return 0;
    case WM_MOUSEMOVE:
        if (GetCapture() == h) {
            e->sel_end = edit_pos_from_x(w, (short)LOWORD(lp));
            InvalidateRect(h, NULL, FALSE);
        }
        return 0;
    case WM_LBUTTONUP:
        if (GetCapture() == h)
            ReleaseCapture();
        return 0;
    case WM_CHAR:
        if (e->readonly)
            return 0;
        if (wp == '\b') {
            if (e->sel_start == e->sel_end && e->sel_end > 0)
                e->sel_start = e->sel_end - 1;
            edit_replace(e, "");
        } else if (wp >= ' ' || (wp == '\r' && (w->style & ES_MULTILINE))) {
            char s[3] = {(char)wp, 0, 0};
            if (wp == '\r') { s[0] = '\r'; s[1] = '\n'; }
            edit_replace(e, s);
        } else {
            return 0;
        }
        edit_scroll(w);
        InvalidateRect(h, NULL, FALSE);
        notify(h, EN_UPDATE);
        notify(h, EN_CHANGE);
        return 0;
    case WM_KEYDOWN: {
        int shift = GetKeyState(VK_SHIFT) < 0, moved = 1;
        switch (wp) {
        case VK_LEFT: if (e->sel_end > 0) e->sel_end--; break;
        case VK_RIGHT: if (e->sel_end < e->len) e->sel_end++; break;
        case VK_HOME: e->sel_end = 0; break;
        case VK_END: e->sel_end = e->len; break;
        case VK_DELETE:
            if (!e->readonly) {
                if (e->sel_start == e->sel_end && e->sel_end < e->len)
                    e->sel_end++;
                edit_replace(e, "");
                notify(h, EN_CHANGE);
            }
            shift = 1;
            break;
        default: moved = 0;
        }
        if (moved) {
            if (!shift)
                e->sel_start = e->sel_end;
            edit_scroll(w);
            InvalidateRect(h, NULL, FALSE);
        }
        return 0;
    }
    case EM_GETSEL:
        if (wp) *(DWORD *)wp = (DWORD)(e->sel_start < e->sel_end ? e->sel_start : e->sel_end);
        if (lp) *(DWORD *)lp = (DWORD)(e->sel_start < e->sel_end ? e->sel_end : e->sel_start);
        return MAKELONG(e->sel_start < e->sel_end ? e->sel_start : e->sel_end,
                        e->sel_start < e->sel_end ? e->sel_end : e->sel_start);
    case EM_SETSEL: {
        int a = (int)wp, b = (int)lp;
        if (a < 0) {
            e->sel_start = e->sel_end;
        } else {
            if (b < 0 || b > e->len) b = e->len;
            if (a > e->len) a = e->len;
            e->sel_start = a;
            e->sel_end = b;
        }
        edit_scroll(w);
        InvalidateRect(h, NULL, FALSE);
        return 0;
    }
    case EM_REPLACESEL:
        edit_replace(e, (const char *)lp);
        edit_scroll(w);
        InvalidateRect(h, NULL, FALSE);
        notify(h, EN_CHANGE);
        return 0;
    case EM_LIMITTEXT:
        e->limit = wp ? (int)wp : 30000;
        return 0;
    case EM_GETMODIFY:
        return e->modified;
    case EM_SETMODIFY:
        e->modified = (int)wp;
        return 0;
    case EM_SETREADONLY:
        e->readonly = (int)wp;
        return TRUE;
    case EM_GETLINECOUNT: {
        int i, n = 1;
        for (i = 0; i < e->len; i++)
            if (e->text[i] == '\n')
                n++;
        return n;
    }
    case EM_LINEINDEX: {
        int line = (int)wp, i, n = 0;
        if (line < 0) {
            for (i = 0; i < e->sel_end; i++)
                if (e->text[i] == '\n')
                    n = i + 1;
            return n;
        }
        for (i = 0; i < e->len && line; i++)
            if (e->text[i] == '\n')
                line--;
        return line ? -1 : i;
    }
    case EM_LINELENGTH: {
        int i = (int)wp, n = 0;
        if (i < 0 || i > e->len)
            return 0;
        while (i > 0 && e->text[i - 1] != '\n')
            i--;
        while (i + n < e->len && e->text[i + n] != '\r' && e->text[i + n] != '\n')
            n++;
        return n;
    }
    case EM_LINEFROMCHAR: {
        int i, n = 0, c = (int)wp < 0 ? e->sel_end : (int)wp;
        for (i = 0; i < c && i < e->len; i++)
            if (e->text[i] == '\n')
                n++;
        return n;
    }
    case EM_GETLINE: {
        int line = (int)wp, i, n = 0, max = *(WORD *)lp;
        for (i = 0; i < e->len && line; i++)
            if (e->text[i] == '\n')
                line--;
        while (i < e->len && e->text[i] != '\r' && e->text[i] != '\n' && n < max)
            ((char *)lp)[n++] = e->text[i++];
        return n;
    }
    case EM_GETFIRSTVISIBLELINE:
        return (w->style & ES_MULTILINE) ? 0 : e->first;
    case EM_LINESCROLL:
    case EM_SCROLLCARET:
        return TRUE;
    }
    return DefWindowProcA(h, m, wp, lp);
}

/* ======================================================================
 * LISTBOX
 */

typedef struct { char *text; ULONG_PTR data; int sel; } LbItem;
typedef struct {
    LbItem *items;
    int n, cap, cur, top, item_h;
    HFONT font;
    int focused;
} ListBox;

static ListBox *lb_of(Window *w) { return w ? (ListBox *)w->control : NULL; }

static int lb_insert(Window *w, int pos, const char *s, ULONG_PTR data)
{
    ListBox *lb = lb_of(w);
    int owner_nostr = (w->style & (LBS_OWNERDRAWFIXED | LBS_OWNERDRAWVARIABLE)) && !(w->style & LBS_HASSTRINGS);
    if (lb->n == lb->cap) {
        lb->cap = lb->cap ? lb->cap * 2 : 16;
        lb->items = realloc(lb->items, sizeof *lb->items * (size_t)lb->cap);
    }
    if ((w->style & LBS_SORT) && pos < 0 && !owner_nostr) {
        for (pos = 0; pos < lb->n; pos++)
            if (strcasecmp(lb->items[pos].text ? lb->items[pos].text : "", s ? s : "") > 0)
                break;
    }
    if (pos < 0 || pos > lb->n)
        pos = lb->n;
    memmove(lb->items + pos + 1, lb->items + pos, sizeof *lb->items * (size_t)(lb->n - pos));
    lb->items[pos].text = owner_nostr ? NULL : plat_strdup(s);
    lb->items[pos].data = owner_nostr ? (ULONG_PTR)s : data;
    lb->items[pos].sel = 0;
    lb->n++;
    if (lb->cur >= pos)
        lb->cur++;
    return pos;
}

static void lb_paint(Window *w, HDC hdc)
{
    ListBox *lb = lb_of(w);
    RECT r, it;
    int i, y = 0;
    HBRUSH br;
    GetClientRect(w->hwnd, &r);
    SelectObject(hdc, lb->font);
    br = (HBRUSH)SendMessageA(w->parent && w->parent != desktop ? w->parent->hwnd : 0, WM_CTLCOLORLISTBOX,
                              (WPARAM)hdc, (LPARAM)w->hwnd);
    if (!br)
        br = GetSysColorBrush(COLOR_WINDOW);
    for (i = lb->top; i < lb->n && y < r.bottom; i++, y += lb->item_h) {
        int sel = (w->style & (LBS_MULTIPLESEL | LBS_EXTENDEDSEL)) ? lb->items[i].sel : i == lb->cur;
        it.left = 0; it.right = r.right; it.top = y; it.bottom = y + lb->item_h;
        if (w->style & (LBS_OWNERDRAWFIXED | LBS_OWNERDRAWVARIABLE)) {
            DRAWITEMSTRUCT_ di;
            memset(&di, 0, sizeof di);
            di.CtlType = ODT_LISTBOX;
            di.CtlID = (UINT)(uintptr_t)w->menu;
            di.itemID = (UINT)i;
            di.itemAction = ODA_DRAWENTIRE;
            di.itemState = (sel ? ODS_SELECTED : 0) | (lb->focused && i == lb->cur ? ODS_FOCUS : 0);
            di.hwndItem = w->hwnd;
            di.hDC = hdc;
            di.rcItem = it;
            di.itemData = lb->items[i].data;
            SendMessageA(w->parent->hwnd, WM_DRAWITEM, di.CtlID, (LPARAM)&di);
            continue;
        }
        FillRect(hdc, &it, sel ? GetSysColorBrush(COLOR_HIGHLIGHT) : br);
        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, sel ? GetSysColor(COLOR_HIGHLIGHTTEXT) : GetSysColor(COLOR_WINDOWTEXT));
        it.left += 2;
        if (lb->items[i].text)
            DrawTextA(hdc, lb->items[i].text, -1, &it, DT_SINGLELINE | DT_NOPREFIX | DT_LEFT | DT_VCENTER);
    }
    if (y < r.bottom) {
        it.left = 0; it.right = r.right; it.top = y; it.bottom = r.bottom;
        FillRect(hdc, &it, br);
    }
}

static int lb_visible(Window *w)
{
    ListBox *lb = lb_of(w);
    RECT r;
    GetClientRect(w->hwnd, &r);
    return lb->item_h ? (r.bottom + lb->item_h - 1) / lb->item_h : 1;
}

static void lb_update_scroll(Window *w)
{
    ListBox *lb = lb_of(w);
    int vis = lb_visible(w) - 1;
    if (!(w->style & WS_VSCROLL))
        return;
    SetScrollRange(w->hwnd, SB_VERT, 0, lb->n > vis ? lb->n - vis : 0, FALSE);
    SetScrollPos(w->hwnd, SB_VERT, lb->top, TRUE);
}

static void lb_set_cur(Window *w, int i, int scroll)
{
    ListBox *lb = lb_of(w);
    int vis = lb_visible(w) - 1;
    lb->cur = i;
    if (scroll && i >= 0) {
        if (i < lb->top)
            lb->top = i;
        else if (vis > 0 && i >= lb->top + vis)
            lb->top = i - vis + 1;
    }
    lb_update_scroll(w);
    InvalidateRect(w->hwnd, NULL, TRUE);
}

LRESULT ctl_listbox_proc(HWND h, UINT m, WPARAM wp, LPARAM lp)
{
    Window *w = wnd_get(h);
    ListBox *lb = lb_of(w);
    int i;
    if (!w)
        return 0;
    if (!lb && m != WM_NCCREATE)
        return DefWindowProcA(h, m, wp, lp);
    switch (m) {
    case WM_NCCREATE: {
        TEXTMETRICA tm;
        lb = calloc(1, sizeof *lb);
        w->control = lb;
        lb->cur = -1;
        lb->font = default_font();
        text_metrics(font_face_of(lb->font), &tm);
        lb->item_h = tm.tmHeight;
        if (w->style & (LBS_OWNERDRAWFIXED | LBS_OWNERDRAWVARIABLE)) {
            MEASUREITEMSTRUCT_ mi;
            memset(&mi, 0, sizeof mi);
            mi.CtlType = ODT_LISTBOX;
            mi.CtlID = (UINT)(uintptr_t)w->menu;
            mi.itemHeight = (UINT)lb->item_h;
            if (w->parent && w->parent != desktop)
                SendMessageA(w->parent->hwnd, WM_MEASUREITEM, mi.CtlID, (LPARAM)&mi);
            lb->item_h = (int)mi.itemHeight;
        }
        return TRUE;
    }
    case WM_DESTROY:
        for (i = 0; i < lb->n; i++)
            free(lb->items[i].text);
        free(lb->items);
        free(lb);
        w->control = NULL;
        return 0;
    case WM_SETFONT:
        lb->font = wp ? (HFONT)wp : default_font();
        if (!(w->style & (LBS_OWNERDRAWFIXED | LBS_OWNERDRAWVARIABLE))) {
            TEXTMETRICA tm;
            text_metrics(font_face_of(lb->font), &tm);
            lb->item_h = tm.tmHeight;
        }
        if (LOWORD(lp))
            InvalidateRect(h, NULL, TRUE);
        return 0;
    case WM_GETFONT:
        return (LRESULT)lb->font;
    case WM_SETFOCUS: lb->focused = 1; InvalidateRect(h, NULL, FALSE); notify(h, LBN_SETFOCUS); return 0;
    case WM_KILLFOCUS: lb->focused = 0; InvalidateRect(h, NULL, FALSE); notify(h, LBN_KILLFOCUS); return 0;
    case WM_GETDLGCODE: return DLGC_WANTARROWS | DLGC_WANTCHARS;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(h, &ps);
        lb_paint(w, hdc);
        EndPaint(h, &ps);
        return 0;
    }
    case WM_ERASEBKGND:
        return 1;
    case WM_SIZE:
        lb_update_scroll(w);
        return 0;
    case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK:
        SetFocus(h);
        i = lb->top + (short)HIWORD(lp) / (lb->item_h ? lb->item_h : 1);
        if (i >= 0 && i < lb->n) {
            if (w->style & (LBS_MULTIPLESEL | LBS_EXTENDEDSEL))
                lb->items[i].sel = !lb->items[i].sel;
            lb_set_cur(w, i, 1);
            if (w->style & LBS_NOTIFY)
                notify(h, m == WM_LBUTTONDBLCLK ? LBN_DBLCLK : LBN_SELCHANGE);
        }
        return 0;
    case WM_KEYDOWN: {
        int n = lb->cur;
        switch (wp) {
        case VK_UP: n--; break;
        case VK_DOWN: n++; break;
        case VK_PRIOR: n -= lb_visible(w) - 1; break;
        case VK_NEXT: n += lb_visible(w) - 1; break;
        case VK_HOME: n = 0; break;
        case VK_END: n = lb->n - 1; break;
        default: return 0;
        }
        if (n < 0) n = 0;
        if (n >= lb->n) n = lb->n - 1;
        if (n != lb->cur) {
            lb_set_cur(w, n, 1);
            if (w->style & LBS_NOTIFY)
                notify(h, LBN_SELCHANGE);
        }
        return 0;
    }
    case WM_VSCROLL: {
        int vis = lb_visible(w) - 1, top = lb->top;
        switch (LOWORD(wp)) {
        case SB_LINEUP: top--; break;
        case SB_LINEDOWN: top++; break;
        case SB_PAGEUP: top -= vis; break;
        case SB_PAGEDOWN: top += vis; break;
        case SB_THUMBTRACK: case SB_THUMBPOSITION: top = HIWORD(wp); break;
        }
        if (top > lb->n - vis) top = lb->n - vis;
        if (top < 0) top = 0;
        lb->top = top;
        lb_update_scroll(w);
        InvalidateRect(h, NULL, TRUE);
        return 0;
    }
    case LB_ADDSTRING:
        i = lb_insert(w, -1, (const char *)lp, 0);
        lb_update_scroll(w);
        InvalidateRect(h, NULL, TRUE);
        return i;
    case LB_INSERTSTRING:
        i = lb_insert(w, (int)wp, (const char *)lp, 0);
        lb_update_scroll(w);
        InvalidateRect(h, NULL, TRUE);
        return i;
    case LB_DELETESTRING:
        i = (int)wp;
        if (i < 0 || i >= lb->n)
            return LB_ERR;
        free(lb->items[i].text);
        memmove(lb->items + i, lb->items + i + 1, sizeof *lb->items * (size_t)(lb->n - i - 1));
        lb->n--;
        if (lb->cur == i) lb->cur = -1;
        else if (lb->cur > i) lb->cur--;
        lb_update_scroll(w);
        InvalidateRect(h, NULL, TRUE);
        return lb->n;
    case LB_RESETCONTENT:
        for (i = 0; i < lb->n; i++)
            free(lb->items[i].text);
        lb->n = 0;
        lb->cur = -1;
        lb->top = 0;
        lb_update_scroll(w);
        InvalidateRect(h, NULL, TRUE);
        return 0;
    case LB_SETSEL:
        if ((int)lp == -1) {
            for (i = 0; i < lb->n; i++)
                lb->items[i].sel = (int)wp;
        } else if ((int)lp >= 0 && (int)lp < lb->n) {
            lb->items[lp].sel = (int)wp;
        }
        InvalidateRect(h, NULL, TRUE);
        return 0;
    case LB_GETSEL:
        if ((int)wp < 0 || (int)wp >= lb->n)
            return LB_ERR;
        return (w->style & (LBS_MULTIPLESEL | LBS_EXTENDEDSEL)) ? lb->items[wp].sel : (int)wp == lb->cur;
    case LB_SETCURSEL:
        if ((int)wp >= lb->n)
            return LB_ERR;
        lb_set_cur(w, (int)wp, 1);
        return (int)wp < 0 ? LB_ERR : (LRESULT)wp;
    case LB_GETCURSEL:
        return lb->cur < 0 ? LB_ERR : lb->cur;
    case LB_GETTEXT:
        if ((int)wp < 0 || (int)wp >= lb->n)
            return LB_ERR;
        if (!lb->items[wp].text) {
            *(ULONG_PTR *)lp = lb->items[wp].data;
            return sizeof(ULONG_PTR);
        }
        strcpy((char *)lp, lb->items[wp].text);
        return (LRESULT)strlen(lb->items[wp].text);
    case LB_GETTEXTLEN:
        if ((int)wp < 0 || (int)wp >= lb->n)
            return LB_ERR;
        return lb->items[wp].text ? (LRESULT)strlen(lb->items[wp].text) : (LRESULT)sizeof(ULONG_PTR);
    case LB_GETCOUNT:
        return lb->n;
    case LB_GETTOPINDEX:
        return lb->top;
    case LB_SETTOPINDEX:
        lb->top = (int)wp;
        lb_update_scroll(w);
        InvalidateRect(h, NULL, TRUE);
        return 0;
    case LB_FINDSTRING: case LB_FINDSTRINGEXACT: case LB_SELECTSTRING: {
        int start = (int)wp, k;
        size_t n = strlen((const char *)lp);
        for (k = 0; k < lb->n; k++) {
            int j = (start + 1 + k) % (lb->n ? lb->n : 1);
            const char *t = lb->items[j].text ? lb->items[j].text : "";
            if (m == LB_FINDSTRINGEXACT ? !strcasecmp(t, (const char *)lp) : !strncasecmp(t, (const char *)lp, n)) {
                if (m == LB_SELECTSTRING)
                    lb_set_cur(w, j, 1);
                return j;
            }
        }
        return LB_ERR;
    }
    case LB_GETSELCOUNT: {
        int n = 0;
        for (i = 0; i < lb->n; i++)
            n += lb->items[i].sel;
        return n;
    }
    case LB_GETSELITEMS: {
        int n = 0;
        for (i = 0; i < lb->n && n < (int)wp; i++)
            if (lb->items[i].sel)
                ((int *)lp)[n++] = i;
        return n;
    }
    case LB_GETITEMDATA:
        if ((int)wp < 0 || (int)wp >= lb->n)
            return LB_ERR;
        return (LRESULT)lb->items[wp].data;
    case LB_SETITEMDATA:
        if ((int)wp < 0 || (int)wp >= lb->n)
            return LB_ERR;
        lb->items[wp].data = (ULONG_PTR)lp;
        return TRUE;
    case LB_SETITEMHEIGHT:
        lb->item_h = LOWORD(lp);
        lb_update_scroll(w);
        InvalidateRect(h, NULL, TRUE);
        return 0;
    case LB_GETITEMHEIGHT:
        return lb->item_h;
    case LB_GETITEMRECT: {
        RECT *r = (RECT *)lp;
        GetClientRect(h, r);
        r->top = ((int)wp - lb->top) * lb->item_h;
        r->bottom = r->top + lb->item_h;
        return 1;
    }
    }
    return DefWindowProcA(h, m, wp, lp);
}

/* ======================================================================
 * COMBOBOX: a selection field with a list shown on demand.
 */

typedef struct { HWND list; int shown; HFONT font; } Combo;

static Combo *combo_of(Window *w) { return w ? (Combo *)w->control : NULL; }

LRESULT ctl_combobox_proc(HWND h, UINT m, WPARAM wp, LPARAM lp)
{
    Window *w = wnd_get(h);
    Combo *c = combo_of(w);
    static const struct { UINT cb, lb; } map[] = {
        {CB_ADDSTRING, LB_ADDSTRING}, {CB_DELETESTRING, LB_DELETESTRING}, {CB_GETCOUNT, LB_GETCOUNT},
        {CB_GETCURSEL, LB_GETCURSEL}, {CB_GETLBTEXT, LB_GETTEXT}, {CB_GETLBTEXTLEN, LB_GETTEXTLEN},
        {CB_INSERTSTRING, LB_INSERTSTRING}, {CB_RESETCONTENT, LB_RESETCONTENT}, {CB_FINDSTRING, LB_FINDSTRING},
        {CB_FINDSTRINGEXACT, LB_FINDSTRINGEXACT}, {CB_GETITEMDATA, LB_GETITEMDATA}, {CB_SETITEMDATA, LB_SETITEMDATA},
        {CB_GETITEMHEIGHT, LB_GETITEMHEIGHT}, {CB_SETITEMHEIGHT, LB_SETITEMHEIGHT}};
    unsigned k;
    if (!w)
        return 0;
    if (!c && m != WM_NCCREATE)
        return DefWindowProcA(h, m, wp, lp);
    for (k = 0; k < sizeof map / sizeof map[0]; k++)
        if (map[k].cb == m) {
            LRESULT r = SendMessageA(c->list, map[k].lb, wp, lp);
            if (m != CB_GETCOUNT && m != CB_GETCURSEL && m != CB_GETLBTEXT && m != CB_GETLBTEXTLEN)
                InvalidateRect(h, NULL, TRUE);
            return r;
        }
    switch (m) {
    case WM_NCCREATE:
        c = calloc(1, sizeof *c);
        w->control = c;
        c->font = default_font();
        c->list = CreateWindowExA(0, "LISTBOX", "", WS_CHILD | LBS_NOTIFY | WS_VSCROLL | (w->style & CBS_SORT ? LBS_SORT : 0) |
                                  (w->style & CBS_OWNERDRAWFIXED ? LBS_OWNERDRAWFIXED : 0) |
                                  (w->style & CBS_HASSTRINGS ? LBS_HASSTRINGS : 0),
                                  0, 0, 10, 10, h, (HMENU)1000, 0, NULL);
        return TRUE;
    case WM_DESTROY:
        free(c);
        w->control = NULL;
        return 0;
    case CB_SETCURSEL: {
        LRESULT r = SendMessageA(c->list, LB_SETCURSEL, wp, lp);
        InvalidateRect(h, NULL, TRUE);
        return r;
    }
    case CB_SELECTSTRING: {
        LRESULT r = SendMessageA(c->list, LB_SELECTSTRING, wp, lp);
        InvalidateRect(h, NULL, TRUE);
        return r;
    }
    case CB_SHOWDROPDOWN:
    case CB_GETDROPPEDSTATE:
        return 0;
    case WM_SETFONT:
        c->font = wp ? (HFONT)wp : default_font();
        SendMessageA(c->list, WM_SETFONT, wp, lp);
        return 0;
    case WM_GETFONT:
        return (LRESULT)c->font;
    case WM_COMMAND:
        if ((HWND)lp == c->list && HIWORD(wp) == LBN_SELCHANGE) {
            InvalidateRect(h, NULL, TRUE);
            notify(h, CBN_SELCHANGE);
        }
        return 0;
    case WM_KEYDOWN:
        if (wp == VK_UP || wp == VK_DOWN) {
            int cur = (int)SendMessageA(c->list, LB_GETCURSEL, 0, 0), n = (int)SendMessageA(c->list, LB_GETCOUNT, 0, 0);
            cur += wp == VK_UP ? -1 : 1;
            if (cur >= 0 && cur < n) {
                SendMessageA(c->list, LB_SETCURSEL, (WPARAM)cur, 0);
                InvalidateRect(h, NULL, TRUE);
                notify(h, CBN_SELCHANGE);
            }
        }
        return 0;
    case WM_LBUTTONDOWN: {
        /* Cycle through the entries (no drop-down list window). */
        int cur = (int)SendMessageA(c->list, LB_GETCURSEL, 0, 0), n = (int)SendMessageA(c->list, LB_GETCOUNT, 0, 0);
        SetFocus(h);
        if (n) {
            SendMessageA(c->list, LB_SETCURSEL, (WPARAM)((cur + 1) % n), 0);
            InvalidateRect(h, NULL, TRUE);
            notify(h, CBN_SELCHANGE);
        }
        return 0;
    }
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(h, &ps);
        RECT r;
        char text[256] = "";
        int cur = (int)SendMessageA(c->list, LB_GETCURSEL, 0, 0);
        GetClientRect(h, &r);
        FillRect(hdc, &r, GetSysColorBrush(COLOR_WINDOW));
        draw_edge(hdc, &r, 1);
        if (cur >= 0)
            SendMessageA(c->list, LB_GETTEXT, (WPARAM)cur, (LPARAM)text);
        SelectObject(hdc, c->font);
        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, GetSysColor(COLOR_WINDOWTEXT));
        r.left += 4;
        DrawTextA(hdc, text, -1, &r, DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX);
        EndPaint(h, &ps);
        return 0;
    }
    }
    return DefWindowProcA(h, m, wp, lp);
}

/* ======================================================================
 * Scroll bars: SCROLLBAR controls and window scroll bars.
 */

#include "scroll_theme.h"

/* Source row/column of the 17-pixel part for k of n pixels: as the theme
 * stretches it (tools/probe/sbstretch.c) -- three fixed pixels at each end,
 * the middle (and its glyph) centred, its plain edge repeated. */
static int part_index(int k, int n)
{
    int i;
    if (k < 3)
        return k;
    if (k >= n - 3)
        return 17 - (n - k);
    i = k - (n - 17 + 1) / 2;
    return i < 3 ? 3 : i > 13 ? 13 : i;
}

/* A grey part of the theme, w x h at x, y (17 along the bar, the bar's
 * thickness across it), clipped to the bar's rect. */
static void scroll_part(DC *dc, const unsigned char *px, int x, int y, int w, int h, const RECT *clip)
{
    int i, j;
    for (j = 0; j < h; j++)
        for (i = 0; i < w; i++) {
            RECT p;
            int v = px[17 * part_index(j, h) + part_index(i, w)];
            p.left = x + i; p.top = y + j; p.right = p.left + 1; p.bottom = p.top + 1;
            if (p.left >= clip->left && p.right <= clip->right && p.top >= clip->top && p.bottom <= clip->bottom)
                dc_fill_rect(dc, &p, RGB(v, v, v));
        }
}

/* Track: scroll bar controls use the brush WM_CTLCOLORSCROLLBAR gives (by
 * default a 245/255 checker aligned to the control), window scroll bars the
 * theme's 245. */
static void scroll_track(DC *dc, const RECT *t, int ctl, POINT org)
{
    int x, y;
    if (rect_empty(t))
        return;
    if (!ctl) {
        dc_fill_rect(dc, t, RGB(245, 245, 245));
        return;
    }
    for (y = t->top; y < t->bottom; y++)
        for (x = t->left; x < t->right; x++) {
            RECT p;
            int v = ((x - org.x + y - org.y) & 1) ? 255 : 245;
            p.left = x; p.top = y; p.right = x + 1; p.bottom = y + 1;
            dc_fill_rect(dc, &p, RGB(v, v, v));
        }
}

/* Draw a scroll bar in rect r (logical coordinates of hdc), as Wine with its
 * default theme does (SCROLL_GetScrollBarRect geometry). */
static void scroll_draw(HDC hdc, const RECT *r, int vert, const Scroll *s, int ctl, int disabled, POINT org)
{
    DC *dc = dc_get(hdc);
    int len = vert ? r->bottom - r->top : r->right - r->left;
    int arrow, thumb = 0, thumb_pos = 0;
    RECT a, b, t;
    if (len <= 2 * 17 + 4)
        arrow = len > 4 ? (len - 4) / 2 : 0;
    else {
        int px = len - 2 * 17 - 17;
        arrow = 17;
        if (px >= 0 && !disabled) {
            thumb = 17;
            thumb_pos = s->min >= s->max ? arrow : arrow + MulDiv(px, s->pos - s->min, s->max - s->min);
        }
    }
    a = b = t = *r;
    if (vert) {
        a.bottom = a.top + arrow;
        b.top = b.bottom - arrow;
        t.top = a.bottom;
        t.bottom = b.top;
    } else {
        a.right = a.left + arrow;
        b.left = b.right - arrow;
        t.left = a.right;
        t.right = b.left;
    }
    if (thumb) {
        RECT t1 = t, t2 = t;
        if (vert) {
            t1.bottom = r->top + thumb_pos;
            t2.top = r->top + thumb_pos + thumb;
        } else {
            t1.right = r->left + thumb_pos;
            t2.left = r->left + thumb_pos + thumb;
        }
        scroll_track(dc, &t1, ctl, org);
        scroll_track(dc, &t2, ctl, org);
        if (vert)
            scroll_part(dc, sb_vthumb, r->left, r->top + thumb_pos, r->right - r->left, 17, r);
        else
            scroll_part(dc, sb_hthumb, r->left + thumb_pos, r->top, 17, r->bottom - r->top, r);
    } else {
        scroll_track(dc, &t, ctl, org);
    }
    if (arrow) {
        if (vert) {
            scroll_part(dc, disabled ? sb_up_off : sb_up, a.left, a.top, a.right - a.left, 17, &a);
            scroll_part(dc, disabled ? sb_down_off : sb_down, b.left, b.bottom - 17, b.right - b.left, 17, &b);
        } else {
            scroll_part(dc, disabled ? sb_left_off : sb_left, a.left, a.top, 17, a.bottom - a.top, &a);
            scroll_part(dc, disabled ? sb_right_off : sb_right, b.right - 17, b.top, 17, b.bottom - b.top, &b);
        }
    }
}

void scroll_paint_nc(Window *w)
{
    HDC hdc = GetWindowDC(w->hwnd);     /* window coordinates */
    RECT r;
    POINT org = {0, 0};
    int cw = w->client.right - w->client.left, ch = w->client.bottom - w->client.top;
    int both = (w->style & (WS_VSCROLL | WS_HSCROLL)) == (WS_VSCROLL | WS_HSCROLL);
    int disabled = (w->style & WS_DISABLED) != 0;
    if (w->style & WS_VSCROLL) {
        r.left = w->client.left + cw; r.right = r.left + GetSystemMetrics(SM_CXVSCROLL);
        r.top = w->client.top; r.bottom = w->client.top + ch + both;   /* Wine overlaps the corner by one */
        scroll_draw(hdc, &r, 1, &w->vscroll, 0, disabled, org);
    }
    if (w->style & WS_HSCROLL) {
        r.left = w->client.left; r.right = w->client.left + cw + both;
        r.top = w->client.top + ch; r.bottom = r.top + GetSystemMetrics(SM_CYHSCROLL);
        scroll_draw(hdc, &r, 0, &w->hscroll, 0, disabled, org);
    }
    if (both) {
        DC *dc = dc_get(hdc);
        r.left = w->client.left + cw + 1; r.right = w->client.left + cw + GetSystemMetrics(SM_CXVSCROLL);
        r.top = w->client.top + ch + 1; r.bottom = w->client.top + ch + GetSystemMetrics(SM_CYHSCROLL);
        dc_fill_rect(dc, &r, RGB(245, 245, 245));
    }
    ReleaseDC(w->hwnd, hdc);
}

/* Which part of a bar of length len (with button size btn) a point hits. */
static int scroll_hit(const Scroll *s, int len, int thick, int at, int *thumb_pos)
{
    int btn = len < 2 * thick ? len / 2 : thick, track = len - 2 * btn, range = s->max - s->min;
    int th = thick, pos = range > 0 && track > th ? (int)((long long)(s->pos - s->min) * (track - th) / range) : 0;
    *thumb_pos = btn + pos;
    if (at < btn) return SB_LINEUP;
    if (at >= len - btn) return SB_LINEDOWN;
    if (range <= 0 || track <= th) return SB_ENDSCROLL;
    if (at < btn + pos) return SB_PAGEUP;
    if (at >= btn + pos + th) return SB_PAGEDOWN;
    return SB_THUMBTRACK;
}

typedef struct { int dragging, grab, vert; } ScrollCtl;

LRESULT ctl_scrollbar_proc(HWND h, UINT m, WPARAM wp, LPARAM lp)
{
    Window *w = wnd_get(h);
    ScrollCtl *sc = w ? (ScrollCtl *)w->control : NULL;
    if (!w)
        return 0;
    switch (m) {
    case WM_NCCREATE:
        sc = calloc(1, sizeof *sc);
        sc->vert = (w->style & SBS_VERT) != 0;
        w->control = sc;
        w->hscroll.max = 100;
        w->hscroll.enabled = 1;
        return TRUE;
    case WM_DESTROY:
        free(sc);
        w->control = NULL;
        return 0;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(h, &ps);
        RECT r;
        GetClientRect(h, &r);
        /* Wine asks the parent for the interior brush (the drawing here
           uses the default the reference ends up with) */
        if (w->parent && w->parent != desktop)
            SendMessageA(w->parent->hwnd, WM_CTLCOLORSCROLLBAR, (WPARAM)hdc, (LPARAM)h);
        {
            POINT org = {0, 0};
            scroll_draw(hdc, &r, sc->vert, &w->hscroll, 1, !w->hscroll.enabled || (w->style & WS_DISABLED), org);
        }
        EndPaint(h, &ps);
        return 0;
    }
    case WM_ERASEBKGND:
        return 1;
    case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK: {
        RECT r;
        int at = sc->vert ? (short)HIWORD(lp) : (short)LOWORD(lp), tp, code;
        GetClientRect(h, &r);
        code = scroll_hit(&w->hscroll, sc->vert ? r.bottom : r.right, sc->vert ? r.right : r.bottom, at, &tp);
        if (code == SB_THUMBTRACK) {
            sc->dragging = 1;
            sc->grab = at - tp;
            SetCapture(h);
            return 0;
        }
        if (code != SB_ENDSCROLL && w->parent)
            SendMessageA(w->parent->hwnd, sc->vert ? WM_VSCROLL : WM_HSCROLL, (WPARAM)code, (LPARAM)h);
        if (w->parent)
            SendMessageA(w->parent->hwnd, sc->vert ? WM_VSCROLL : WM_HSCROLL, SB_ENDSCROLL, (LPARAM)h);
        return 0;
    }
    case WM_MOUSEMOVE:
        if (sc && sc->dragging) {
            RECT r;
            int at = sc->vert ? (short)HIWORD(lp) : (short)LOWORD(lp), len, thick, btn, track, range, pos;
            GetClientRect(h, &r);
            len = sc->vert ? r.bottom : r.right;
            thick = sc->vert ? r.right : r.bottom;
            btn = len < 2 * thick ? len / 2 : thick;
            track = len - 2 * btn - thick;
            range = w->hscroll.max - w->hscroll.min;
            pos = track > 0 ? w->hscroll.min + (int)((long long)(at - sc->grab - btn) * range / track) : 0;
            if (pos < w->hscroll.min) pos = w->hscroll.min;
            if (pos > w->hscroll.max) pos = w->hscroll.max;
            if (w->parent)
                SendMessageA(w->parent->hwnd, sc->vert ? WM_VSCROLL : WM_HSCROLL, MAKEWPARAM(SB_THUMBTRACK, pos), (LPARAM)h);
        }
        return 0;
    case WM_LBUTTONUP:
        if (sc && sc->dragging) {
            sc->dragging = 0;
            ReleaseCapture();
            if (w->parent) {
                SendMessageA(w->parent->hwnd, sc->vert ? WM_VSCROLL : WM_HSCROLL,
                             MAKEWPARAM(SB_THUMBPOSITION, w->hscroll.pos), (LPARAM)h);
                SendMessageA(w->parent->hwnd, sc->vert ? WM_VSCROLL : WM_HSCROLL, SB_ENDSCROLL, (LPARAM)h);
            }
        }
        return 0;
    case WM_ENABLE:
        w->hscroll.enabled = (int)wp;
        InvalidateRect(h, NULL, FALSE);
        return 0;
    case SBM_SETSCROLLINFO: {
        const SCROLLINFO *si = (const SCROLLINFO *)lp;
        Scroll *s = &w->hscroll;
        if (si->fMask & SIF_RANGE) {
            s->min = si->nMin;
            s->max = si->nMax;
        }
        if (si->fMask & SIF_PAGE)
            s->page = (int)si->nPage;
        if (si->fMask & SIF_POS)
            s->pos = si->nPos;
        if (s->pos < s->min) s->pos = s->min;
        if (s->pos > s->max) s->pos = s->max;
        if (wp)
            InvalidateRect(h, NULL, FALSE);
        return s->pos;
    }
    case SBM_GETSCROLLINFO: {
        SCROLLINFO *si = (SCROLLINFO *)lp;
        if (si->fMask & SIF_RANGE) { si->nMin = w->hscroll.min; si->nMax = w->hscroll.max; }
        if (si->fMask & SIF_PAGE) si->nPage = (UINT)w->hscroll.page;
        if (si->fMask & SIF_POS) si->nPos = w->hscroll.pos;
        return TRUE;
    }
    case SBM_SETPOS: {
        int old = w->hscroll.pos;
        w->hscroll.pos = (int)wp < w->hscroll.min ? w->hscroll.min : (int)wp > w->hscroll.max ? w->hscroll.max : (int)wp;
        if (lp)
            InvalidateRect(h, NULL, FALSE);
        return old;
    }
    case SBM_GETPOS:
        return w->hscroll.pos;
    case SBM_SETRANGE: case SBM_SETRANGEREDRAW:
        w->hscroll.min = (int)wp;
        w->hscroll.max = (int)lp;
        if (m == SBM_SETRANGEREDRAW)
            InvalidateRect(h, NULL, FALSE);
        return 0;
    case SBM_GETRANGE:
        if (wp) *(int *)wp = w->hscroll.min;
        if (lp) *(int *)lp = w->hscroll.max;
        return 0;
    case SBM_ENABLE_ARROWS:
        return TRUE;
    }
    return DefWindowProcA(h, m, wp, lp);
}

/* ======================================================================
 * BUTTON and STATIC: text and push behaviour only.
 */

LRESULT ctl_button_proc(HWND h, UINT m, WPARAM wp, LPARAM lp)
{
    Window *w = wnd_get(h);
    if (!w)
        return 0;
    switch (m) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(h, &ps);
        RECT r;
        GetClientRect(h, &r);
        FillRect(hdc, &r, GetSysColorBrush(COLOR_3DFACE));
        draw_edge(hdc, &r, 0);
        SetBkMode(hdc, TRANSPARENT);
        DrawTextA(hdc, w->text, -1, &r, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        EndPaint(h, &ps);
        return 0;
    }
    case WM_LBUTTONUP:
        notify(h, BN_CLICKED);
        return 0;
    }
    return DefWindowProcA(h, m, wp, lp);
}

LRESULT ctl_static_proc(HWND h, UINT m, WPARAM wp, LPARAM lp)
{
    Window *w = wnd_get(h);
    if (!w)
        return 0;
    if (m == WM_PAINT) {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(h, &ps);
        RECT r;
        GetClientRect(h, &r);
        SetBkMode(hdc, TRANSPARENT);
        DrawTextA(hdc, w->text, -1, &r, DT_WORDBREAK);
        EndPaint(h, &ps);
        return 0;
    }
    return DefWindowProcA(h, m, wp, lp);
}
