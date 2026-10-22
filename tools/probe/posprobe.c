/* Probe: where Wine's text drawing puts each glyph of a string, against the
 * fractional character widths. */
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define W 400
#define H 40
static unsigned char *bits;
static HDC dc;

static void render(const char *s, int n, unsigned char *out)
{
    RECT r = {10, 5, W, H};
    memset(bits, 1, W * H);
    DrawTextA(dc, s, n, &r, DT_NOCLIP | DT_SINGLELINE | DT_NOPREFIX);
    memcpy(out, bits, W * H);
}

static void test(const char *face, int h, int weight, int pitch, const char *s)
{
    struct { BITMAPINFOHEADER h; RGBQUAD c[256]; } bi;
    static unsigned char a[W * H], b[W * H];
    LOGFONTA lf;
    MAT2 m = {{0, 1}, {0, 0}, {0, 0}, {0, 1}};
    int k, n = (int)strlen(s);
    double fsum = 0;
    dc = CreateCompatibleDC(NULL);
    memset(&bi, 0, sizeof bi);
    bi.h.biSize = sizeof bi.h; bi.h.biWidth = W; bi.h.biHeight = -H; bi.h.biPlanes = 1; bi.h.biBitCount = 8;
    bi.c[1].rgbRed = bi.c[1].rgbGreen = bi.c[1].rgbBlue = 255;
    SelectObject(dc, CreateDIBSection(dc, (BITMAPINFO *)&bi, DIB_RGB_COLORS, (void **)&bits, NULL, 0));
    memset(&lf, 0, sizeof lf);
    lf.lfHeight = -h; lf.lfWeight = weight; lf.lfCharSet = 1; lf.lfOutPrecision = 4; lf.lfClipPrecision = 1;
    lf.lfPitchAndFamily = (BYTE)pitch;
    strcpy(lf.lfFaceName, face);
    SelectObject(dc, CreateFontIndirectA(&lf));
    SetBkMode(dc, TRANSPARENT);
    printf("%s %d %d: ", face, h, weight);
    for (k = 0; k < n; k++) {
        GLYPHMETRICS gm;
        int x, y, minx = W;
        float fw;
        INT iw;
        render(s, k, a);
        render(s, k + 1, b);
        for (y = 0; y < H; y++)
            for (x = 0; x < W; x++)
                if (a[y * W + x] != b[y * W + x] && x < minx)
                    minx = x;
        GetGlyphOutlineA(dc, (unsigned char)s[k], GGO_METRICS, &gm, 0, NULL, &m);
        GetCharWidthFloatA(dc, (unsigned char)s[k], (unsigned char)s[k], &fw);
        GetCharWidth32A(dc, (unsigned char)s[k], (unsigned char)s[k], &iw);
        printf("%c pen=%d (int %d float %.3f) ", s[k], minx == W ? -1 : minx - 10 - gm.gmptGlyphOrigin.x, iw, fw);
        fsum += fw;
    }
    printf("\n");
    DeleteDC(dc);
}

int main(void)
{
    test("Times New Roman", 11, 700, 0x10, "Moving Units");
    test("Times New Roman", 24, 400, 0x10, "Start a New Game");
    test("MS Shell Dlg", 11, 400, 0x22, "Kingdom");
    return 0;
}
