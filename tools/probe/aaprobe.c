/*
 * Probe: Wine's antialiased text on 32-bpp surfaces.  Draws strings with
 * TextOut and compares every pixel with a prediction from the glyphs'
 * GGO_GRAY4_BITMAP coverage (0..16) and the blending formula of Wine's DIB
 * engine (reimplemented in src/platform/text.c).  Prints mismatch counts.
 */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define W 400
#define H 60

static const BYTE ramp[17] = {0, 0x4d, 0x68, 0x7c, 0x8c, 0x9a, 0xa7, 0xb2, 0xbd, 0xc7, 0xd0, 0xd9, 0xe1, 0xe9, 0xf0, 0xf8, 0xff};

static BYTE aa_color(BYTE dst, BYTE text, BYTE min_comp, BYTE max_comp)
{
    if (dst == text)
        return dst;
    if (dst > text) {
        DWORD diff = dst - text, range = max_comp - text;
        return (BYTE)(text + (diff * range) / (0xff - text));
    } else {
        DWORD diff = text - dst, range = text - min_comp;
        return (BYTE)(text - (diff * range) / text);
    }
}

static BYTE blend(BYTE dst, BYTE text, int aa)
{
    BYTE mn = (BYTE)((ramp[aa] * text) / 0xff);
    BYTE mx = (BYTE)(ramp[16 - aa] + ((0xff - ramp[16 - aa]) * text) / 0xff);
    if (aa >= 16)
        return text;
    if (aa <= 1)        /* the lowest coverage level leaves the pixel unchanged */
        return dst;
    return aa_color(dst, text, mn, mx);
}

static int test(const char *face, int height, int weight, COLORREF fg, COLORREF bg, const char *s)
{
    struct { BITMAPINFOHEADER h; } bi;
    DWORD *bits, *pred;
    static BYTE cov[W * H];
    HDC dc = CreateCompatibleDC(NULL);
    LOGFONTA lf;
    HFONT f;
    int x, y, i, bad = 0, pen = 10, oy = 10;
    TEXTMETRICA tm;
    MAT2 m = {{0, 1}, {0, 0}, {0, 0}, {0, 1}};
    memset(&bi, 0, sizeof bi);
    bi.h.biSize = sizeof bi.h; bi.h.biWidth = W; bi.h.biHeight = -H; bi.h.biPlanes = 1; bi.h.biBitCount = 32;
    SelectObject(dc, CreateDIBSection(dc, (BITMAPINFO *)&bi, DIB_RGB_COLORS, (void **)&bits, NULL, 0));
    memset(&lf, 0, sizeof lf);
    lf.lfHeight = -height; lf.lfWeight = weight; lf.lfCharSet = 1; lf.lfOutPrecision = 4; lf.lfClipPrecision = 1;
    strcpy(lf.lfFaceName, face);
    f = CreateFontIndirectA(&lf);
    SelectObject(dc, f);
    GetTextMetricsA(dc, &tm);
    for (i = 0; i < W * H; i++)
        bits[i] = (GetRValue(bg) << 16) | (GetGValue(bg) << 8) | GetBValue(bg);
    memset(cov, 0, sizeof cov);
    pred = malloc(W * H * 4);
    memcpy(pred, bits, W * H * 4);
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, fg);
    TextOutA(dc, pen, oy, s, (int)strlen(s));
    GdiFlush();
    for (i = 0; s[i]; i++) {
        GLYPHMETRICS gm;
        DWORD n = GetGlyphOutlineA(dc, (unsigned char)s[i], GGO_GRAY4_BITMAP, &gm, 0, NULL, &m);
        BYTE *g = malloc(n ? n : 1);
        int stride = (gm.gmBlackBoxX + 3) & ~3;
        SIZE sz;
        GetGlyphOutlineA(dc, (unsigned char)s[i], GGO_GRAY4_BITMAP, &gm, n, g, &m);
        for (y = 0; n && y < (int)gm.gmBlackBoxY; y++)
            for (x = 0; x < (int)gm.gmBlackBoxX; x++) {
                int px = pen + gm.gmptGlyphOrigin.x + x, py = oy + tm.tmAscent - gm.gmptGlyphOrigin.y + y;
                DWORD *p = &pred[py * W + px];
                int a = g[y * stride + x];
                cov[py * W + px] = (BYTE)(a > cov[py * W + px] ? a : cov[py * W + px]);
                *p = (blend((BYTE)(*p >> 16), GetRValue(fg), a) << 16) | (blend((BYTE)(*p >> 8), GetGValue(fg), a) << 8) |
                     blend((BYTE)*p, GetBValue(fg), a);
            }
        free(g);
        GetTextExtentPoint32A(dc, &s[i], 1, &sz);
        pen += sz.cx;
    }
    {
        int hist[17] = {0}, off1 = 0;
        for (i = 0; i < W * H; i++)
            if ((bits[i] & 0xffffff) != (pred[i] & 0xffffff)) {
                int k, best = -1;
                BYTE wb = (BYTE)bits[i], d = (BYTE)GetBValue(bg);
                for (k = 0; k <= 16; k++)
                    if (blend(d, GetBValue(fg), k) == wb) best = k;
                if (bad < 6)
                    printf("  pixel %d,%d: cov %d wine %06lx predicted %06lx (wine = level %d)\n", i % W, i / W, cov[i],
                           bits[i] & 0xffffff, pred[i] & 0xffffff, best);
                hist[cov[i]]++;
                if (best >= 0 && abs(best - cov[i]) == 1) off1++;
                bad++;
            }
        printf("  by coverage:");
        for (i = 0; i <= 16; i++) printf(" %d", hist[i]);
        printf("  (off by one level: %d)\n", off1);
    }
    printf("%s %d %d fg %06lx bg %06lx: %d mismatches\n", face, height, weight, fg, bg, bad);
    free(pred);
    DeleteDC(dc);
    return bad;
}

int main(void)
{
    test("MS Shell Dlg", 11, 400, 0x000000, 0xffffff, "Kingdom Civilopedia");
    test("Times New Roman", 24, 400, 0x404040, 0x9e9e9e, "Start a New Game");
    test("Times New Roman", 24, 400, 0xbfbfbf, 0x333333, "Start a New Game");
    test("Times New Roman", 16, 700, 0xfa9632, 0x123456, "Caesar OK");
    test("Arial", 14, 400, 0xffffff, 0xfa9632, "Hello World");
    return 0;
}
