/* Probe: how Wine (the reference environment) renders the game's fonts.
 * Prints text metrics and whether glyphs are antialiased on 8 and 32 bpp DIBs. */
#include <windows.h>
#include <stdio.h>

static HDC make_dib(int bpp, int w, int h, void **bits)
{
    struct { BITMAPINFOHEADER h; RGBQUAD c[256]; } bi;
    HDC dc = CreateCompatibleDC(NULL);
    int i;
    memset(&bi, 0, sizeof bi);
    bi.h.biSize = sizeof bi.h; bi.h.biWidth = w; bi.h.biHeight = -h; bi.h.biPlanes = 1; bi.h.biBitCount = bpp;
    for (i = 0; i < 256; i++) { bi.c[i].rgbRed = bi.c[i].rgbGreen = bi.c[i].rgbBlue = (BYTE)i; }
    SelectObject(dc, CreateDIBSection(dc, (BITMAPINFO *)&bi, DIB_RGB_COLORS, bits, NULL, 0));
    return dc;
}

int main(void)
{
    const char *faces[] = {"Times New Roman", "Arial", "System", "Courier"};
    int f, bpp;
    for (f = 0; f < 4; f++) {
        LOGFONTA lf; HFONT font; TEXTMETRICA tm; char face[64]; HDC dc; void *bits; int x, y, levels;
        memset(&lf, 0, sizeof lf);
        lf.lfHeight = -16; lf.lfWeight = 400; lf.lfCharSet = 1; lf.lfOutPrecision = 4; lf.lfClipPrecision = 1;
        lf.lfPitchAndFamily = f == 0 ? 0x10 : f == 1 ? 0x20 : f == 3 ? 0x30 : 0;
        strcpy(lf.lfFaceName, faces[f]);
        font = CreateFontIndirectA(&lf);
        for (bpp = 8; bpp <= 32; bpp += 24) {
            unsigned char seen[256] = {0};
            dc = make_dib(bpp, 200, 40, &bits);
            SelectObject(dc, font);
            PatBlt(dc, 0, 0, 200, 40, WHITENESS);
            SetBkMode(dc, TRANSPARENT);
            TextOutA(dc, 2, 2, "Agw Civ2 &%", 11);
            GetTextMetricsA(dc, &tm);
            GetTextFaceA(dc, sizeof face, face);
            levels = 0;
            for (y = 0; y < 40; y++)
                for (x = 0; x < 200; x++) {
                    unsigned v = bpp == 8 ? ((unsigned char *)bits)[y * 200 + x] : ((unsigned char *)bits)[(y * 200 + x) * 4];
                    if (!seen[v]) { seen[v] = 1; levels++; }
                }
            printf("%s bpp=%d face=%s h=%ld asc=%ld desc=%ld intlead=%ld extlead=%ld ave=%ld max=%ld levels=%d\n",
                   faces[f], bpp, face, tm.tmHeight, tm.tmAscent, tm.tmDescent, tm.tmInternalLeading,
                   tm.tmExternalLeading, tm.tmAveCharWidth, tm.tmMaxCharWidth, levels);
        }
    }
    {
        int i;
        printf("metrics:");
        for (i = 0; i < 96; i++) printf(" %d", GetSystemMetrics(i));
        printf("\nsyscolors:");
        for (i = 0; i < 31; i++) printf(" %06lx", (unsigned long)GetSysColor(i));
        printf("\n");
        {
            HDC s = GetDC(NULL);
            printf("caps bits=%d planes=%d rc=%x sizepal=%d numcolors=%d horz=%d vert=%d logy=%d\n",
                   GetDeviceCaps(s, BITSPIXEL), GetDeviceCaps(s, PLANES), GetDeviceCaps(s, RASTERCAPS),
                   GetDeviceCaps(s, SIZEPALETTE), GetDeviceCaps(s, NUMCOLORS), GetDeviceCaps(s, HORZRES),
                   GetDeviceCaps(s, VERTRES), GetDeviceCaps(s, LOGPIXELSY));
        }
    }
    return 0;
}
