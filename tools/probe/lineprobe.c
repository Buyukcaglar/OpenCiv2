/* Probe: Wine's Bresenham tie rule (dibdrv bres_line_with_bias).  Draws
 * LineTo from (32,32) to every end point within 12 pixels on a 32-bpp DIB,
 * one line per image, and prints the pixels each one sets (checked against
 * LineTo in src/platform/gdi.c). */
#include <windows.h>
#include <stdio.h>

int main(void)
{
    HDC dc = CreateCompatibleDC(NULL);
    BITMAPINFO bi;
    DWORD *bits;
    HBITMAP bmp;
    int ex, ey, x, y;
    memset(&bi, 0, sizeof bi);
    bi.bmiHeader.biSize = sizeof bi.bmiHeader;
    bi.bmiHeader.biWidth = 64;
    bi.bmiHeader.biHeight = -64;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    bmp = CreateDIBSection(dc, &bi, DIB_RGB_COLORS, (void **)&bits, NULL, 0);
    SelectObject(dc, bmp);
    SelectObject(dc, GetStockObject(WHITE_PEN));
    for (ey = -12; ey <= 12; ey++)
        for (ex = -12; ex <= 12; ex++) {
            memset(bits, 0, 64 * 64 * 4);
            MoveToEx(dc, 32, 32, NULL);
            LineTo(dc, 32 + ex, 32 + ey);
            GdiFlush();
            printf("%d %d:", ex, ey);
            for (y = 0; y < 64; y++)
                for (x = 0; x < 64; x++)
                    if (bits[y * 64 + x])
                        printf(" %d,%d", x - 32, y - 32);
            printf("\n");
        }
    return 0;
}
