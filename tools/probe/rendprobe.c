/* Probe: render strings with DrawTextA on 8-bpp DIBs and print them as
 * rows of '#'/'.' (for fitting glyph positions offline). */
#include <windows.h>
#include <stdio.h>
#include <string.h>

#define W 600
#define H 60

static void test(const char *face, int h, int weight, int pitch, const char *s)
{
    struct { BITMAPINFOHEADER h; RGBQUAD c[256]; } bi;
    unsigned char *bits;
    HDC dc = CreateCompatibleDC(NULL);
    LOGFONTA lf;
    RECT r = {10, 5, W, H};
    int x, y;
    memset(&bi, 0, sizeof bi);
    bi.h.biSize = sizeof bi.h; bi.h.biWidth = W; bi.h.biHeight = -H; bi.h.biPlanes = 1; bi.h.biBitCount = 8;
    bi.c[1].rgbRed = bi.c[1].rgbGreen = bi.c[1].rgbBlue = 255;
    SelectObject(dc, CreateDIBSection(dc, (BITMAPINFO *)&bi, DIB_RGB_COLORS, (void **)&bits, NULL, 0));
    memset(bits, 1, W * H);
    memset(&lf, 0, sizeof lf);
    lf.lfHeight = -h; lf.lfWeight = weight; lf.lfCharSet = 1; lf.lfOutPrecision = 4; lf.lfClipPrecision = 1;
    lf.lfPitchAndFamily = (BYTE)pitch;
    strcpy(lf.lfFaceName, face);
    SelectObject(dc, CreateFontIndirectA(&lf));
    SetBkMode(dc, TRANSPARENT);
    DrawTextA(dc, s, -1, &r, DT_NOCLIP | DT_SINGLELINE | DT_NOPREFIX);
    printf("@ %s|%d|%d|%s\n", face, h, weight, s);
    for (y = 0; y < H; y++) {
        for (x = 0; x < W; x++)
            putchar(bits[y * W + x] ? '.' : '#');
        putchar('\n');
    }
    DeleteDC(dc);
}

int main(void)
{
    static const char *strs[] = {"Moving Units", "Phalanx (Plains) Roman", "Start a New Game", "Dictator Caesar of the Romans",
                                 "iiiiiiiiiiiiiiiiiiii", "nnnnnnnnnnnnnnnnnnnn", "The quick brown fox jumps over 1,234 lazy dogs."};
    int i;
    for (i = 0; i < 7; i++) {
        test("Times New Roman", 11, 700, 0x10, strs[i]);
        test("Times New Roman", 11, 400, 0x10, strs[i]);
        test("Times New Roman", 16, 700, 0x10, strs[i]);
        test("Times New Roman", 24, 400, 0x10, strs[i]);
        test("Arial", 14, 400, 0x20, strs[i]);
    }
    return 0;
}
