/* Probe: DrawTextA with TA_UPDATECP -- where the text lands (bounding box of
 * its pixels) and the current position afterwards, for several current
 * positions, rects and formats. */
#include <windows.h>
#include <stdio.h>
#include <string.h>

static void test(int cpx, int cpy, int l, int t, int r, int b, UINT fmt)
{
    struct { BITMAPINFOHEADER h; } bi;
    unsigned char *bits;
    HDC dc = CreateCompatibleDC(NULL);
    LOGFONTA lf;
    RECT rc = {l, t, r, b};
    POINT p;
    int x, y, W = 400, H = 120, x0 = W, x1 = -1, y0 = H, y1 = -1, ret;
    memset(&bi, 0, sizeof bi);
    bi.h.biSize = sizeof bi.h; bi.h.biWidth = W; bi.h.biHeight = -H; bi.h.biPlanes = 1; bi.h.biBitCount = 32;
    SelectObject(dc, CreateDIBSection(dc, (BITMAPINFO *)&bi, DIB_RGB_COLORS, (void **)&bits, NULL, 0));
    memset(bits, 0xff, W * H * 4);
    memset(&lf, 0, sizeof lf);
    lf.lfHeight = -24; lf.lfWeight = 400;
    strcpy(lf.lfFaceName, "Times New Roman");
    SelectObject(dc, CreateFontIndirectA(&lf));
    SetBkMode(dc, TRANSPARENT);
    SetTextAlign(dc, TA_UPDATECP);
    MoveToEx(dc, cpx, cpy, NULL);
    ret = DrawTextA(dc, "Hello World", -1, &rc, fmt);
    GetCurrentPositionEx(dc, &p);
    for (y = 0; y < H; y++)
        for (x = 0; x < W; x++)
            if (bits[(y * W + x) * 4] != 0xff) {
                if (x < x0) x0 = x; if (x > x1) x1 = x;
                if (y < y0) y0 = y; if (y > y1) y1 = y;
            }
    printf("cp %d,%d rect %d,%d,%d,%d fmt %x -> ink x %d..%d y %d..%d, cp after %ld,%ld ret %d\n",
           cpx, cpy, l, t, r, b, fmt, x0, x1, y0, y1, p.x, p.y, ret);
    DeleteDC(dc);
}

int main(void)
{
    test(0, 0, 50, 40, 300, 80, 0);
    test(100, 10, 50, 40, 300, 80, 0);
    test(30, 60, 50, 40, 300, 80, 0);
    test(100, 10, 50, 40, 300, 80, DT_CENTER);
    test(100, 10, 50, 40, 300, 80, DT_SINGLELINE | DT_VCENTER);
    test(100, 10, 50, 40, 300, 80, DT_RIGHT);
    SetTextAlign(CreateCompatibleDC(NULL), 0);
    return 0;
}
