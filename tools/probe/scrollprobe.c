/* Probe: how Wine (with its default theme) draws scroll bars -- controls
 * and window scroll bars, both orientations, in the states the game uses.
 * Writes the window's pixels to run/scrollprobe.ppm. */
#include <windows.h>
#include <stdio.h>

static LRESULT CALLBACK proc(HWND h, UINT m, WPARAM w, LPARAM l) { return DefWindowProcA(h, m, w, l); }

static HWND bar(HWND parent, int vert, int x, int y, int len, int pos, int lo, int hi, int enable)
{
    HWND h = CreateWindowExA(0, "SCROLLBAR", "", WS_CHILD | WS_VISIBLE | (vert ? SBS_VERT : SBS_HORZ),
                             x, y, vert ? 17 : len, vert ? len : 17, parent, NULL, NULL, NULL);
    SetScrollRange(h, SB_CTL, lo, hi, FALSE);
    SetScrollPos(h, SB_CTL, pos, TRUE);
    if (!enable)
        EnableWindow(h, FALSE);
    return h;
}

int main(void)
{
    WNDCLASSA wc;
    HWND top, w1, w2;
    MSG msg;
    HDC dc, mem;
    HBITMAP bmp;
    BITMAPINFO bi;
    unsigned char *bits;
    FILE *f;
    int x, y, i;
    const int W = 600, H = 420;
    memset(&wc, 0, sizeof wc);
    wc.lpfnWndProc = proc;
    wc.lpszClassName = "probe";
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    RegisterClassA(&wc);
    top = CreateWindowExA(0, "probe", "", WS_POPUP | WS_VISIBLE, 0, 0, W, H, NULL, NULL, NULL, NULL);
    /* vertical controls: pos 0, 50, 100 of 0..100, disabled, empty range, short */
    bar(top, 1, 10, 10, 200, 0, 0, 100, 1);
    bar(top, 1, 40, 10, 200, 50, 0, 100, 1);
    bar(top, 1, 70, 11, 200, 100, 0, 100, 1);
    bar(top, 1, 100, 10, 200, 0, 0, 100, 0);
    bar(top, 1, 130, 10, 200, 0, 0, 0, 1);
    bar(top, 1, 160, 10, 40, 0, 0, 100, 1);
    bar(top, 1, 160, 60, 30, 0, 0, 100, 1);
    /* horizontal controls */
    bar(top, 0, 200, 10, 200, 0, 0, 100, 1);
    bar(top, 0, 200, 40, 200, 50, 0, 100, 1);
    bar(top, 0, 201, 70, 200, 100, 0, 100, 1);
    bar(top, 0, 200, 100, 200, 0, 0, 100, 0);
    bar(top, 0, 200, 130, 200, 0, 0, 0, 1);
    /* window scroll bars */
    w1 = CreateWindowExA(0, "probe", "", WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL, 200, 170, 150, 150, top, NULL, NULL, NULL);
    SetScrollRange(w1, SB_VERT, 0, 100, FALSE);
    SetScrollPos(w1, SB_VERT, 30, TRUE);
    SetScrollRange(w1, SB_HORZ, 0, 100, FALSE);
    SetScrollPos(w1, SB_HORZ, 70, TRUE);
    w2 = CreateWindowExA(0, "probe", "", WS_CHILD | WS_VISIBLE | WS_VSCROLL, 400, 170, 100, 230, top, NULL, NULL, NULL);
    SetScrollRange(w2, SB_VERT, 0, 10, FALSE);
    SetScrollPos(w2, SB_VERT, 0, TRUE);
    /* vertical control at odd/even offsets for the track pattern origin */
    bar(top, 1, 520, 10, 200, 0, 0, 100, 1);
    bar(top, 1, 541, 13, 200, 0, 0, 100, 1);
    UpdateWindow(top);
    for (i = 0; i < 50; i++) {
        while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
            DispatchMessageA(&msg);
        Sleep(20);
    }
    dc = GetDC(top);
    mem = CreateCompatibleDC(dc);
    memset(&bi, 0, sizeof bi);
    bi.bmiHeader.biSize = sizeof bi.bmiHeader;
    bi.bmiHeader.biWidth = W;
    bi.bmiHeader.biHeight = -H;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    bmp = CreateDIBSection(dc, &bi, DIB_RGB_COLORS, (void **)&bits, NULL, 0);
    SelectObject(mem, bmp);
    BitBlt(mem, 0, 0, W, H, dc, 0, 0, SRCCOPY);
    GdiFlush();
    f = fopen("Z:\\work\\run\\scrollprobe.ppm", "wb");
    fprintf(f, "P6\n%d %d\n255\n", W, H);
    for (y = 0; y < H; y++)
        for (x = 0; x < W; x++) {
            unsigned char *p = bits + 4 * (y * W + x);
            fputc(p[2], f); fputc(p[1], f); fputc(p[0], f);
        }
    fclose(f);
    printf("ok\n");
    return 0;
}
