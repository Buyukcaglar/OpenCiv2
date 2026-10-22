/* Probe: the glyph advances Wine's text drawing uses, vs. extents. */
#include <windows.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    HDC dc = CreateCompatibleDC(NULL);
    LOGFONTA lf;
    const char *s = "Moving Units";
    MAT2 m = {{0, 1}, {0, 0}, {0, 0}, {0, 1}};
    int i;
    ABC abc;
    memset(&lf, 0, sizeof lf);
    lf.lfHeight = -11; lf.lfWeight = 700; lf.lfCharSet = 1; lf.lfOutPrecision = 4; lf.lfClipPrecision = 1;
    lf.lfPitchAndFamily = 0x10;
    strcpy(lf.lfFaceName, "Times New Roman");
    SelectObject(dc, CreateFontIndirectA(&lf));
    for (i = 0; s[i]; i++) {
        GLYPHMETRICS gm;
        SIZE sz;
        INT w;
        GetGlyphOutlineA(dc, (unsigned char)s[i], GGO_METRICS, &gm, 0, NULL, &m);
        GetTextExtentPoint32A(dc, s + i, 1, &sz);
        GetCharWidth32A(dc, (unsigned char)s[i], (unsigned char)s[i], &w);
        GetCharABCWidthsA(dc, (unsigned char)s[i], (unsigned char)s[i], &abc);
        printf("%c: extent %ld cellinc %d charwidth %d abc %d+%u+%d origin %ld\n", s[i], sz.cx, gm.gmCellIncX, w,
               abc.abcA, abc.abcB, abc.abcC, gm.gmptGlyphOrigin.x);
    }
    return 0;
}
