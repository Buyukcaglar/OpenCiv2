/*
 * Menus: the menu bar (drawn like Wine's, the only non-client part drawn on
 * the reference desktop) and popup menus, with a modal tracking loop like
 * Windows'.
 */
#include "plat.h"
#include "../host/host.h"

typedef struct MenuItem {
    UINT flags;                 /* MF_* */
    UINT_PTR id;                /* command id, or submenu handle with MF_POPUP */
    char *text;
} MenuItem;

typedef struct { int n, cap; MenuItem *items; } Menu;

static Menu *menu_get(HMENU h) { return obj_get(h, OBJ_MENU); }

HMENU WINAPI CreateMenu(void) { API_TRACE(); return obj_new(OBJ_MENU, calloc(1, sizeof(Menu))); }
HMENU WINAPI CreatePopupMenu(void) { API_TRACE(); return CreateMenu(); }

WINBOOL WINAPI DestroyMenu(HMENU h)
{
    API_TRACE();
    Menu *m = menu_get(h);
    int i;
    if (!m)
        return FALSE;
    for (i = 0; i < m->n; i++) {
        if (m->items[i].flags & MF_POPUP)
            DestroyMenu((HMENU)m->items[i].id);
        free(m->items[i].text);
    }
    free(m->items);
    free(m);
    obj_free(h);
    return TRUE;
}

/* Position of an item by command or by index (MF_BYPOSITION). */
static int find_item(HMENU h, UINT which, UINT flags, Menu **owner)
{
    Menu *m = menu_get(h);
    int i;
    if (!m)
        return -1;
    if (flags & MF_BYPOSITION) {
        *owner = m;
        return which < (UINT)m->n ? (int)which : -1;
    }
    for (i = 0; i < m->n; i++) {
        if (m->items[i].flags & MF_POPUP) {
            int k = find_item((HMENU)m->items[i].id, which, flags, owner);
            if (k >= 0)
                return k;
        } else if (m->items[i].id == which) {
            *owner = m;
            return i;
        }
    }
    return -1;
}

static void set_item(MenuItem *it, UINT flags, UINT_PTR id, LPCSTR text)
{
    free(it->text);
    it->flags = flags & ~(MF_BYPOSITION);
    it->id = id;
    it->text = (flags & (MF_SEPARATOR | MF_BITMAP | MF_OWNERDRAW)) || !text ? NULL : plat_strdup(text);
}

static WINBOOL insert(HMENU h, int pos, UINT flags, UINT_PTR id, LPCSTR text)
{
    Menu *m = menu_get(h);
    if (!m)
        return FALSE;
    if (m->n == m->cap) {
        m->cap = m->cap ? m->cap * 2 : 8;
        m->items = realloc(m->items, sizeof *m->items * (size_t)m->cap);
    }
    if (pos < 0 || pos > m->n)
        pos = m->n;
    memmove(m->items + pos + 1, m->items + pos, sizeof *m->items * (size_t)(m->n - pos));
    memset(&m->items[pos], 0, sizeof m->items[pos]);
    set_item(&m->items[pos], flags, id, text);
    m->n++;
    return TRUE;
}

WINBOOL WINAPI AppendMenuA(HMENU h, UINT flags, UINT_PTR id, LPCSTR text) { API_TRACE(); return insert(h, -1, flags, id, text); }

WINBOOL WINAPI InsertMenuA(HMENU h, UINT pos, UINT flags, UINT_PTR id, LPCSTR text)
{
    API_TRACE();
    Menu *owner;
    int i = pos == (UINT)-1 ? -1 : find_item(h, pos, flags, &owner);
    if (i < 0 || !(flags & MF_BYPOSITION))
        return insert(h, i < 0 ? -1 : i, flags, id, text);
    return insert(h, i, flags, id, text);
}

WINBOOL WINAPI ModifyMenuA(HMENU h, UINT pos, UINT flags, UINT_PTR id, LPCSTR text)
{
    API_TRACE();
    Menu *owner;
    int i = find_item(h, pos, flags, &owner);
    if (i < 0)
        return FALSE;
    set_item(&owner->items[i], flags, id, text);
    return TRUE;
}

static WINBOOL remove_item(HMENU h, UINT pos, UINT flags, int destroy)
{
    Menu *owner;
    int i = find_item(h, pos, flags, &owner);
    if (i < 0)
        return FALSE;
    if (destroy && (owner->items[i].flags & MF_POPUP))
        DestroyMenu((HMENU)owner->items[i].id);
    free(owner->items[i].text);
    memmove(owner->items + i, owner->items + i + 1, sizeof *owner->items * (size_t)(owner->n - i - 1));
    owner->n--;
    return TRUE;
}

WINBOOL WINAPI DeleteMenu(HMENU h, UINT pos, UINT flags) { API_TRACE(); return remove_item(h, pos, flags, 1); }
WINBOOL WINAPI RemoveMenu(HMENU h, UINT pos, UINT flags) { API_TRACE(); return remove_item(h, pos, flags, 0); }

HMENU WINAPI GetSubMenu(HMENU h, int pos)
{
    API_TRACE();
    Menu *m = menu_get(h);
    if (!m || pos < 0 || pos >= m->n || !(m->items[pos].flags & MF_POPUP))
        return 0;
    return (HMENU)m->items[pos].id;
}

int WINAPI GetMenuItemCount(HMENU h)
{
    API_TRACE();
    Menu *m = menu_get(h);
    return m ? m->n : -1;
}

UINT WINAPI GetMenuItemID(HMENU h, int pos)
{
    API_TRACE();
    Menu *m = menu_get(h);
    if (!m || pos < 0 || pos >= m->n)
        return (UINT)-1;
    return (m->items[pos].flags & MF_POPUP) ? (UINT)-1 : (UINT)m->items[pos].id;
}

WINBOOL WINAPI EnableMenuItem(HMENU h, UINT which, UINT flags)
{
    API_TRACE();
    Menu *owner;
    int i = find_item(h, which, flags, &owner);
    UINT old;
    if (i < 0)
        return (UINT)-1;
    old = owner->items[i].flags & (MF_GRAYED | MF_DISABLED);
    owner->items[i].flags = (owner->items[i].flags & ~(MF_GRAYED | MF_DISABLED)) | (flags & (MF_GRAYED | MF_DISABLED));
    return old;
}

DWORD WINAPI CheckMenuItem(HMENU h, UINT which, UINT flags)
{
    API_TRACE();
    Menu *owner;
    int i = find_item(h, which, flags, &owner);
    DWORD old;
    if (i < 0)
        return (DWORD)-1;
    old = owner->items[i].flags & MF_CHECKED;
    owner->items[i].flags = (owner->items[i].flags & ~MF_CHECKED) | (flags & MF_CHECKED);
    return old;
}

HMENU WINAPI GetMenu(HWND h)
{
    API_TRACE();
    Window *w = wnd_get(h);
    return w && !(w->style & WS_CHILD) ? w->menu : 0;
}

WINBOOL WINAPI SetMenu(HWND h, HMENU menu)
{
    API_TRACE();
    Window *w = wnd_get(h);
    RECT r;
    plat_log("SetMenu(%x, %x)\n", (unsigned)h, (unsigned)menu);
    if (!w || (w->style & WS_CHILD))
        return FALSE;
    w->menu = menu;
    /* The client area changes: SetWindowPos(SWP_FRAMECHANGED). */
    (void)r;
    SetWindowPos(h, 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
    if (wnd_has_nc(w))
        w->erase |= 2;
    return TRUE;
}

WINBOOL WINAPI DrawMenuBar(HWND h)
{
    API_TRACE();
    /* As Wine: a frame change. */
    Window *w = wnd_get(h);
    plat_log("DrawMenuBar(%x)\n", (unsigned)h);
    if (w && !(w->style & WS_CHILD))
        SetWindowPos(h, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
    return TRUE;
}

/* ---- drawing ---- */

HFONT plat_menu_font(void)
{
    static HFONT f;
    if (!f) {
        LOGFONTA lf;
        memset(&lf, 0, sizeof lf);
        lf.lfHeight = -11;          /* Wine's menu font: MS Shell Dlg, -11 (DejaVu Sans) */
        lf.lfWeight = 400;
        strcpy(lf.lfFaceName, "MS Shell Dlg");
        f = CreateFontIndirectA(&lf);
        obj_set_stock(f);
    }
    return f;
}

int menu_bar_height(Window *w)
{
    (void)w;
    return GetSystemMetrics(SM_CYMENU);
}

static int char_width(void)
{
    TEXTMETRICA tm;
    Font *f = obj_get(plat_menu_font(), OBJ_FONT);
    text_metrics(f->face, &tm);
    return tm.tmAveCharWidth;
}

static int item_text_width(const char *text)
{
    char buf[256];
    int i, o = 0;
    Font *f = obj_get(plat_menu_font(), OBJ_FONT);
    for (i = 0; text && text[i] && o < 255; i++) {
        if (text[i] == '&' && text[i + 1]) {
            i++;
            if (text[i] != '&') {
                buf[o++] = text[i];
                continue;
            }
        }
        if (text[i] == '\t')
            break;
        buf[o++] = text[i];
    }
    return text_width(f->face, buf, o);
}

/* Item rectangles of the bar, in client coordinates horizontally and window
 * coordinates vertically: as Wine lays them out, text width + 14. */
static int bar_items(Window *w, RECT *rects, int max)
{
    Menu *m = menu_get(w->menu);
    int i, x = 0, top, h = menu_bar_height(w);
    if (!m)
        return 0;
    top = w->client.top - h;
    for (i = 0; i < m->n && i < max; i++) {
        int tw = item_text_width(m->items[i].text);
        rects[i].left = x;
        rects[i].right = x + tw + 14;
        rects[i].top = top;
        rects[i].bottom = top + h;
        x = rects[i].right;
    }
    return i;
}

void menu_bar_paint(Window *w)
{
    Menu *m = menu_get(w->menu);
    HDC hdc;
    DC *dc;
    RECT bar, rects[64];
    int i, n, cw;
    if (!m || !wnd_is_visible(w))
        return;
    hdc = GetWindowDC(w->hwnd);         /* window coordinates */
    dc = dc_get(hdc);
    bar.left = w->client.left;
    bar.right = w->client.right;
    bar.bottom = w->client.top;
    bar.top = bar.bottom - menu_bar_height(w);
    dc_fill_rect(dc, &bar, GetSysColor(COLOR_MENU));
    SelectObject(hdc, plat_menu_font());
    SetBkMode(hdc, TRANSPARENT);
    n = bar_items(w, rects, 64);
    (void)cw;
    for (i = 0; i < n; i++) {
        RECT t = rects[i];
        t.left += w->client.left + 7;
        t.right += w->client.left;
        SetTextColor(hdc, (m->items[i].flags & MF_GRAYED) ? GetSysColor(COLOR_GRAYTEXT) : GetSysColor(COLOR_MENUTEXT));
        /* Wine's item rectangles start one pixel below the bar's top. */
        t.top += 1;
        if (m->items[i].text)
            DrawTextA(hdc, m->items[i].text, -1, &t, DT_SINGLELINE | DT_VCENTER | DT_LEFT);
    }
    ReleaseDC(w->hwnd, hdc);
}

/* ---- popup tracking ---- */

typedef struct { int x, y, w, h, n; RECT item[128]; Bitmap *saved; } Popup;

static void popup_layout(HMENU h, int x, int y, Popup *p)
{
    Menu *m = menu_get(h);
    int i, maxw = 60, ih = GetSystemMetrics(SM_CYMENU), cw = char_width();
    p->n = m ? (m->n < 128 ? m->n : 128) : 0;
    for (i = 0; i < p->n; i++) {
        int tw = item_text_width(m->items[i].text) + 4 * cw + 24;
        if (m->items[i].text && strchr(m->items[i].text, '\t'))
            tw += item_text_width(strchr(m->items[i].text, '\t') + 1) + 2 * cw;
        if (tw > maxw)
            maxw = tw;
    }
    p->w = maxw + 6;
    p->h = 6;
    for (i = 0; i < p->n; i++) {
        int hh = (m->items[i].flags & MF_SEPARATOR) ? 8 : ih;
        p->item[i].left = 3;
        p->item[i].right = p->w - 3;
        p->item[i].top = p->h - 3;
        p->item[i].bottom = p->h - 3 + hh;
        p->h += hh;
    }
    if (x + p->w > screen_w) x = screen_w - p->w;
    if (y + p->h > screen_h) y = screen_h - p->h;
    p->x = x < 0 ? 0 : x;
    p->y = y < 0 ? 0 : y;
}

static void popup_draw(HMENU h, Popup *p, int sel)
{
    Menu *m = menu_get(h);
    HDC hdc = plat_overlay_dc();
    DC *dc = dc_get(hdc);
    RECT r;
    int i, cw = char_width();
    r.left = p->x; r.top = p->y; r.right = p->x + p->w; r.bottom = p->y + p->h;
    dc_fill_rect(dc, &r, GetSysColor(COLOR_MENU));
    FrameRect(hdc, &r, GetSysColorBrush(COLOR_3DSHADOW));
    SelectObject(hdc, plat_menu_font());
    SetBkMode(hdc, TRANSPARENT);
    for (i = 0; i < p->n; i++) {
        RECT it = p->item[i];
        it.left += p->x; it.right += p->x; it.top += p->y; it.bottom += p->y;
        if (m->items[i].flags & MF_SEPARATOR) {
            RECT line = it;
            line.top = line.bottom = (it.top + it.bottom) / 2;
            line.bottom++;
            dc_fill_rect(dc, &line, GetSysColor(COLOR_3DSHADOW));
            continue;
        }
        if (i == sel)
            dc_fill_rect(dc, &it, GetSysColor(COLOR_HIGHLIGHT));
        SetTextColor(hdc, (m->items[i].flags & MF_GRAYED) ? GetSysColor(COLOR_GRAYTEXT) :
                          i == sel ? GetSysColor(COLOR_HIGHLIGHTTEXT) : GetSysColor(COLOR_MENUTEXT));
        if (m->items[i].flags & MF_CHECKED) {
            RECT c = it;
            c.left += 2;
            DrawTextA(hdc, "x", 1, &c, DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX);
        }
        if (m->items[i].text) {
            char left[256];
            const char *tab = strchr(m->items[i].text, '\t');
            RECT t = it;
            int n = tab ? (int)(tab - m->items[i].text) : (int)strlen(m->items[i].text);
            snprintf(left, sizeof left, "%.*s", n, m->items[i].text);
            t.left += 2 * cw + 12;
            DrawTextA(hdc, left, -1, &t, DT_SINGLELINE | DT_VCENTER);
            if (tab) {
                t.right -= 2 * cw;
                DrawTextA(hdc, tab + 1, -1, &t, DT_SINGLELINE | DT_VCENTER | DT_RIGHT);
            }
        }
    }
    ReleaseDC(0, hdc);
    plat_present_now();     /* the loop then waits for input */
}

static void save_under(Popup *p)
{
    int y;
    plat_compose();
    plat_overlay++;
    p->saved = bmp_create(p->w, p->h, 32, 0);
    for (y = 0; y < p->h; y++)
        memcpy(bmp_row(p->saved, y), (DWORD *)bmp_row(screen, p->y + y) + p->x, (size_t)p->w * 4);
}

static void restore_under(Popup *p)
{
    int y;
    for (y = 0; y < p->h; y++)
        memcpy((DWORD *)bmp_row(screen, p->y + y) + p->x, bmp_row(p->saved, y), (size_t)p->w * 4);
    bmp_destroy(p->saved);
    p->saved = NULL;
    plat_overlay--;
    plat_present_now();
}

/* Modal loop: returns the chosen command id (0: none). *move: -1/+1 to
 * switch to the neighbouring bar menu. */
static UINT track(HWND owner, HMENU h, int x, int y, int *move)
{
    Menu *m = menu_get(h);
    Popup p;
    int sel = -1, done = 0, pressed = 0, inside;
    UINT result = 0;
    HostEvent e;
    if (!m)
        return 0;
    SendMessageA(owner, WM_INITMENUPOPUP, (WPARAM)h, 0);
    popup_layout(h, x, y, &p);
    save_under(&p);
    popup_draw(h, &p, sel);
    if (move)
        *move = 0;
    while (!done && host_wait_event(&e, -1)) {
        int i, nsel = sel;
        switch (e.type) {
        case HOST_EV_QUIT:
            done = 1;
            break;
        case HOST_EV_MOTION:
            nsel = -1;
            for (i = 0; i < p.n; i++)
                if (e.x >= p.x + p.item[i].left && e.x < p.x + p.item[i].right &&
                    e.y >= p.y + p.item[i].top && e.y < p.y + p.item[i].bottom &&
                    !(m->items[i].flags & MF_SEPARATOR))
                    nsel = i;
            break;
        case HOST_EV_BUTTONDOWN:
            /* (as Windows) a click outside the menu closes it */
            pressed = 1;
            if (e.x < p.x || e.x >= p.x + p.w || e.y < p.y || e.y >= p.y + p.h)
                done = 1;
            break;
        case HOST_EV_BUTTONUP:
            /* Releasing the click that opened the menu (on the menu bar)
               leaves it open: an item is then chosen with a second click.
               Holding the button down and releasing on an item works too. */
            inside = e.x >= p.x && e.x < p.x + p.w && e.y >= p.y && e.y < p.y + p.h;
            if (inside && sel >= 0 && !(m->items[sel].flags & (MF_GRAYED | MF_DISABLED | MF_POPUP)))
                result = (UINT)m->items[sel].id;
            if (result || (!inside && pressed))
                done = 1;
            break;
        case HOST_EV_KEYDOWN:
            switch (e.vk) {
            case VK_ESCAPE: done = 1; break;
            case VK_LEFT: if (move) { *move = -1; done = 1; } break;
            case VK_RIGHT: if (move) { *move = 1; done = 1; } break;
            case VK_UP:
                for (i = 0; i < p.n; i++) {
                    nsel = (nsel <= 0 ? p.n : nsel) - 1;
                    if (!(m->items[nsel].flags & MF_SEPARATOR))
                        break;
                }
                break;
            case VK_DOWN:
                for (i = 0; i < p.n; i++) {
                    nsel = (nsel + 1) % p.n;
                    if (!(m->items[nsel].flags & MF_SEPARATOR))
                        break;
                }
                break;
            case VK_RETURN:
                if (sel >= 0 && !(m->items[sel].flags & (MF_GRAYED | MF_DISABLED | MF_POPUP)))
                    result = (UINT)m->items[sel].id;
                done = 1;
                break;
            default:
                /* The underlined letter. */
                for (i = 0; i < p.n; i++) {
                    const char *amp = m->items[i].text ? strchr(m->items[i].text, '&') : NULL;
                    if (amp && tolower((unsigned char)amp[1]) == tolower(e.vk) &&
                        !(m->items[i].flags & (MF_GRAYED | MF_DISABLED))) {
                        result = (UINT)m->items[i].id;
                        done = 1;
                        break;
                    }
                }
            }
            break;
        }
        if (nsel != sel && !done) {
            sel = nsel;
            popup_draw(h, &p, sel);
            if (sel >= 0)
                SendMessageA(owner, WM_MENUSELECT, MAKEWPARAM(m->items[sel].id, m->items[sel].flags), (LPARAM)h);
        }
    }
    restore_under(&p);
    return result;
}

static void bar_track(Window *w, int index)
{
    Menu *m = menu_get(w->menu);
    RECT rects[64];
    int n, move;
    UINT cmd = 0;
    RECT wr;
    if (!m)
        return;
    SendMessageA(w->hwnd, WM_INITMENU, (WPARAM)w->menu, 0);
    n = bar_items(w, rects, 64);
    wnd_screen_rect(w, &wr);
    while (index >= 0 && index < n) {
        if (!(m->items[index].flags & MF_POPUP)) {
            cmd = (UINT)m->items[index].id;
            break;
        }
        cmd = track(w->hwnd, (HMENU)m->items[index].id, wr.left + w->client.left + rects[index].left,
                    wr.top + rects[index].bottom, &move);
        if (!move)
            break;
        index = (index + move + n) % n;
    }
    SendMessageA(w->hwnd, WM_MENUSELECT, MAKEWPARAM(0, 0xffff), 0);
    if (cmd)
        PostMessageA(w->hwnd, WM_COMMAND, cmd, 0);
}

int menu_bar_click(Window *w, int x, int y)
{
    RECT rects[64], wr;
    int i, n;
    while (w && (w->style & WS_CHILD))
        w = w->parent;
    if (!w || !w->menu)
        return 0;
    wnd_screen_rect(w, &wr);
    n = bar_items(w, rects, 64);
    for (i = 0; i < n; i++)
        if (x >= wr.left + w->client.left + rects[i].left && x < wr.left + w->client.left + rects[i].right &&
            y >= wr.top + rects[i].top && y < wr.top + rects[i].bottom) {
            bar_track(w, i);
            return 1;
        }
    return 0;
}

/* Alt+letter opens the bar menu with that underlined letter. */
int menu_key(Window *w, int vk)
{
    Menu *m;
    int i;
    while (w && (w->style & WS_CHILD))
        w = w->parent;
    if (!w || !(m = menu_get(w->menu)))
        return 0;
    if (vk == VK_MENU || vk == VK_F10)
        return 0;
    for (i = 0; i < m->n; i++) {
        const char *amp = m->items[i].text ? strchr(m->items[i].text, '&') : NULL;
        if (amp && toupper((unsigned char)amp[1]) == vk) {
            bar_track(w, i);
            return 1;
        }
    }
    return 0;
}

WINBOOL WINAPI TrackPopupMenu(HMENU h, UINT flags, int x, int y, int res, HWND owner, const RECT *r)
{
    API_TRACE();
    UINT cmd;
    (void)res; (void)r;
    cmd = track(owner, h, x, y, NULL);
    if (flags & TPM_RETURNCMD)
        return (WINBOOL)cmd;
    if (cmd)
        PostMessageA(owner, WM_COMMAND, cmd, 0);
    return TRUE;
}
