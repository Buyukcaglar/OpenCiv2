/* Probe: a string drawn by DrawTextA on an 8-bpp DIB, as text rows. */
#include <windows.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    struct { BITMAPINFOHEADER h; RGBQUAD c[256]; } bi;
    unsigned char *bits;
    HDC dc = CreateCompatibleDC(NULL);
    LOGFONTA lf;
    RECT r = {4, 2, 200, 30};
    const char *s = argc > 1 ? argv[1] : "Moving Units";
    int x, y, W = 120, H = 20;
    memset(&bi, 0, sizeof bi);
    bi.h.biSize = sizeof bi.h; bi.h.biWidth = W; bi.h.biHeight = -H; bi.h.biPlanes = 1; bi.h.biBitCount = 8;
    bi.c[1].rgbRed = bi.c[1].rgbGreen = bi.c[1].rgbBlue = 255;
    SelectObject(dc, CreateDIBSection(dc, (BITMAPINFO *)&bi, DIB_RGB_COLORS, (void **)&bits, NULL, 0));
    memset(bits, 1, W * H);
    memset(&lf, 0, sizeof lf);
    lf.lfHeight = -11; lf.lfWeight = 700; lf.lfCharSet = 1; lf.lfOutPrecision = 4; lf.lfClipPrecision = 1;
    lf.lfPitchAndFamily = 0x10;
    strcpy(lf.lfFaceName, "Times New Roman");
    SelectObject(dc, CreateFontIndirectA(&lf));
    SetBkMode(dc, TRANSPARENT);
    DrawTextA(dc, s, -1, &r, 0);
    for (y = 0; y < H; y++) {
        for (x = 0; x < W; x++)
            putchar(bits[y * W + x] ? '.' : '#');
        putchar('\n');
    }
    return 0;
}
