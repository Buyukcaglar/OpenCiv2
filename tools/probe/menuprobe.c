/* Probe: the menu font and menu bar layout Wine uses (non-client metrics,
 * and the item rectangles of a menu bar like the game's). */
#include <windows.h>
#include <stdio.h>

static LRESULT CALLBACK proc(HWND h, UINT m, WPARAM w, LPARAM l) { return DefWindowProcA(h, m, w, l); }

int main(void)
{
    NONCLIENTMETRICSA ncm;
    WNDCLASSA wc;
    HWND h;
    HMENU bar;
    const char *items[] = {"&Game", "&Kingdom", "&View", "&Orders", "&Advisors", "&World", "&Cheat", "&Editor", "&Civilopedia"};
    int i;
    ncm.cbSize = sizeof ncm;
    SystemParametersInfoA(SPI_GETNONCLIENTMETRICS, sizeof ncm, &ncm, 0);
    printf("menufont %s h=%ld w=%ld weight=%ld charset=%d quality=%d pitch=%d menuheight=%d\n", ncm.lfMenuFont.lfFaceName,
           ncm.lfMenuFont.lfHeight, ncm.lfMenuFont.lfWidth, ncm.lfMenuFont.lfWeight, ncm.lfMenuFont.lfCharSet,
           ncm.lfMenuFont.lfQuality, ncm.lfMenuFont.lfPitchAndFamily, ncm.iMenuHeight);
    memset(&wc, 0, sizeof wc);
    wc.lpfnWndProc = proc;
    wc.lpszClassName = "probe";
    RegisterClassA(&wc);
    bar = CreateMenu();
    for (i = 0; i < 9; i++)
        AppendMenuA(bar, MF_POPUP, (UINT_PTR)CreatePopupMenu(), items[i]);
    h = CreateWindowExA(0, "probe", "x", WS_OVERLAPPEDWINDOW, 0, 0, 608, 426, NULL, bar, NULL, NULL);
    ShowWindow(h, SW_SHOW);
    for (i = 0; i < 9; i++) {
        RECT r;
        GetMenuItemRect(h, bar, i, &r);
        printf("item %d: %ld %ld %ld %ld\n", i, r.left, r.top, r.right, r.bottom);
    }
    {
        HDC dc = GetDC(h);
        HFONT f = CreateFontIndirectA(&ncm.lfMenuFont);
        TEXTMETRICA tm;
        SIZE sz;
        char face[64];
        SelectObject(dc, f);
        GetTextMetricsA(dc, &tm);
        GetTextFaceA(dc, sizeof face, face);
        GetTextExtentPoint32A(dc, "Kingdom", 7, &sz);
        printf("face %s height %ld ave %ld Kingdom %ld\n", face, tm.tmHeight, tm.tmAveCharWidth, sz.cx);
    }
    return 0;
}
