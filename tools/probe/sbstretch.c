/* Probe: scroll bar controls thicker than SM_CXVSCROLL, as the game makes
 * some (the tax rate dialog): horizontal bars 17..32 high and vertical bars
 * 17..32 wide, thumb in the middle.  Writes run/sbstretch.ppm. */
#include <windows.h>
#include <stdio.h>

static LRESULT CALLBACK proc(HWND h, UINT m, WPARAM w, LPARAM l) { return DefWindowProcA(h, m, w, l); }

int main(void)
{
    WNDCLASSA wc;
    HWND top, b;
    MSG msg;
    HDC dc, mem;
    HBITMAP bmp;
    BITMAPINFO bi;
    unsigned char *bits;
    FILE *f;
    int x, y, i, t;
    const int W = 1000, H = 760;
    memset(&wc, 0, sizeof wc);
    wc.lpfnWndProc = proc;
    wc.lpszClassName = "probe";
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    RegisterClassA(&wc);
    top = CreateWindowExA(0, "probe", "", WS_POPUP | WS_VISIBLE, 0, 0, W, H, NULL, NULL, NULL, NULL);
    for (i = 0, y = 10; i < 16; i++) {          /* horizontal: x 10, 160 long, height t */
        t = 17 + i;
        b = CreateWindowExA(0, "SCROLLBAR", "", WS_CHILD | WS_VISIBLE | SBS_HORZ, 10, y, 160, t, top, NULL, NULL, NULL);
        SetScrollRange(b, SB_CTL, 0, 100, FALSE);
        SetScrollPos(b, SB_CTL, 50, TRUE);
        y += t + 4;
    }
    for (i = 0, x = 200; i < 16; i++) {         /* vertical: y 10, 160 long, width t */
        t = 17 + i;
        b = CreateWindowExA(0, "SCROLLBAR", "", WS_CHILD | WS_VISIBLE | SBS_VERT, x, 10, t, 160, top, NULL, NULL, NULL);
        SetScrollRange(b, SB_CTL, 0, 100, FALSE);
        SetScrollPos(b, SB_CTL, 50, TRUE);
        x += t + 4;
    }
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
    f = fopen("Z:\\work\\run\\sbstretch.ppm", "wb");
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
