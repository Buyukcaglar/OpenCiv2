/* Probe: how Wine clips the glyphs of a multiline EDIT's text (the
 * Civilopedia's text pane).  The same lines are drawn by a multiline EDIT
 * (top) and by plain TextOut (bottom); a pixel that differs is a glyph
 * clipped by the edit (its format rectangle or Uniscribe's per-item
 * clipping in ScriptStringOut).  Writes run/edititems.ppm. */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

static LRESULT CALLBACK proc(HWND h, UINT m, WPARAM w, LPARAM l)
{
    static HBRUSH red;
    if (m == WM_CTLCOLORSTATIC && getenv("PROBE_COLORS")) {
        if (!red)
            red = CreateSolidBrush(RGB(255, 0, 0));
        SetBkColor((HDC)w, RGB(0, 0, 255));
        return (LRESULT)red;
    }
    return DefWindowProcA(h, m, w, l);
}

static const char *lines[] = {
    "f f f.j t,j (j .j ff",
    "fj f-j 1j j1 f1 f) f\" f'j",
    "12.j 1.1 f.. f.)j a1.j f'",
};

int main(int argc, char **argv)
{
    WNDCLASSA wc;
    HWND top, ed;
    MSG msg;
    HDC dc, mem;
    HBITMAP bmp;
    BITMAPINFO bi;
    unsigned char *bits;
    FILE *f;
    RECT r;
    LOGFONTA lf;
    HFONT font;
    TEXTMETRICA tm;
    LRESULT mg;
    int x, y, i;
    char text[1024] = "";
    const int W = 500, H = 200;
    (void)argc; (void)argv;
    memset(&wc, 0, sizeof wc);
    wc.lpfnWndProc = proc;
    wc.lpszClassName = "probe";
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    RegisterClassA(&wc);
    top = CreateWindowExA(0, "probe", "", WS_POPUP | WS_VISIBLE, 0, 0, W, H, NULL, NULL, NULL, NULL);
    ed = CreateWindowExA(0, "EDIT", "", WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_READONLY, 0, 0, W, 90, top,
                         NULL, NULL, NULL);
    memset(&lf, 0, sizeof lf);
    lf.lfHeight = -21;
    lf.lfWeight = 400;
    strcpy(lf.lfFaceName, "DejaVu Serif");
    font = CreateFontIndirectA(&lf);
    SendMessageA(ed, WM_SETFONT, (WPARAM)font, 0);
    for (i = 0; i < 3; i++) {
        strcat(text, lines[i]);
        if (i < 2)
            strcat(text, "\r\n");
    }
    SetWindowTextA(ed, text);
    SendMessageA(ed, EM_GETRECT, 0, (LPARAM)&r);
    mg = SendMessageA(ed, EM_GETMARGINS, 0, 0);
    dc = GetDC(ed);
    SelectObject(dc, font);
    GetTextMetricsA(dc, &tm);
    printf("rect %ld %ld %ld %ld margins %d %d height %ld\n", r.left, r.top, r.right, r.bottom, LOWORD(mg),
           HIWORD(mg), tm.tmHeight);
    ReleaseDC(ed, dc);
    UpdateWindow(top);
    for (i = 0; i < 10; i++) {
        while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
            DispatchMessageA(&msg);
        Sleep(20);
    }
    dc = GetDC(top);
    SelectObject(dc, font);
    SetBkMode(dc, TRANSPARENT);
    for (i = 0; i < 3; i++) {
        int k;
        TextOutA(dc, LOWORD(mg), 100 + i * tm.tmHeight, lines[i], (int)strlen(lines[i]));
        printf("line %d:", i);
        for (k = 0; lines[i][k]; k++) {
            SIZE sz;
            GetTextExtentPoint32A(dc, lines[i], k, &sz);
            printf(" %c@%ld", lines[i][k], LOWORD(mg) + sz.cx);
        }
        printf("\n");
    }
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
    f = fopen("Z:\\work\\run\\edititems.ppm", "wb");
    fprintf(f, "P6\n%d %d\n255\n", W, H);
    for (y = 0; y < H; y++)
        for (x = 0; x < W; x++) {
            unsigned char *p = bits + 4 * (y * W + x);
            fputc(p[2], f); fputc(p[1], f); fputc(p[0], f);
        }
    fclose(f);
    return 0;
}
