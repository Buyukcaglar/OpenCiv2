/* Probe: string extents vs the sum of single-character extents. */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void test(const char *face, int h, int weight, const char *s)
{
    HDC dc = CreateCompatibleDC(NULL);
    LOGFONTA lf;
    SIZE sz, c;
    int i, sum = 0;
    INT dx[256];
    memset(&lf, 0, sizeof lf);
    lf.lfHeight = -h; lf.lfWeight = weight; lf.lfCharSet = 1; lf.lfOutPrecision = 4; lf.lfClipPrecision = 1;
    strcpy(lf.lfFaceName, face);
    lf.lfPitchAndFamily = !strcmp(face, "Times New Roman") ? 0x10 : 0;
    SelectObject(dc, CreateFontIndirectA(&lf));
    GetTextExtentPoint32A(dc, s, (int)strlen(s), &sz);
    for (i = 0; s[i]; i++) {
        GetTextExtentPoint32A(dc, s + i, 1, &c);
        sum += c.cx;
    }
    GetTextExtentExPointA(dc, s, (int)strlen(s), 0, NULL, dx, &sz);
    printf("%s %d %d \"%s\": extent %ld sum %d  partial:", face, h, weight, s, sz.cx, sum);
    for (i = 0; s[i]; i++) printf(" %d", dx[i]);
    printf("\n");
    DeleteDC(dc);
}

int main(int argc, char **argv)
{
    if (argc > 4) {         /* extprobe FACE HEIGHT WEIGHT STRING */
        test(argv[1], atoi(argv[2]), atoi(argv[3]), argv[4]);
        return 0;
    }
    test("Times New Roman", 11, 700, "Moving Units");
    test("Times New Roman", 11, 700, "Phalanx");
    test("Times New Roman", 11, 700, "(Plains)");
    test("Times New Roman", 24, 400, "Start a New Game");
    test("Times New Roman", 16, 400, "Cancel");
    test("MS Shell Dlg", 11, 400, "Kingdom");
    return 0;
}
