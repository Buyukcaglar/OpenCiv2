/* Probe: a single-line EDIT like the game's name entry (WS_BORDER |
 * ES_AUTOHSCROLL, Times New Roman -18), its format rectangle, margins and
 * pixels with all text selected.  Writes run/editprobe.ppm. */
#include <windows.h>
#include <stdio.h>

static LRESULT CALLBACK proc(HWND h, UINT m, WPARAM w, LPARAM l) { return DefWindowProcA(h, m, w, l); }

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
    const int W = 400, H = 60;
    memset(&wc, 0, sizeof wc);
    wc.lpfnWndProc = proc;
    wc.lpszClassName = "probe";
    wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
    RegisterClassA(&wc);
    top = CreateWindowExA(0, "probe", "", WS_POPUP | WS_VISIBLE, 0, 0, W, H, NULL, NULL, NULL, NULL);
    ed = CreateWindowExA(4, "EDIT", "", 0x50800080, 10, 10, 368, 30, top, NULL, NULL, NULL);
    memset(&lf, 0, sizeof lf);
    lf.lfHeight = -18;
    lf.lfWeight = 400;
    strcpy(lf.lfFaceName, argc > 1 ? argv[1] : "Times New Roman");
    font = CreateFontIndirectA(&lf);
    SendMessageA(ed, WM_SETFONT, (WPARAM)font, 0);
    SetWindowTextA(ed, "Caesar");
    SetFocus(ed);
    SendMessageA(ed, EM_SETSEL, 0, -1);
    SendMessageA(ed, EM_GETRECT, 0, (LPARAM)&r);
    mg = SendMessageA(ed, EM_GETMARGINS, 0, 0);
    dc = GetDC(ed);
    SelectObject(dc, font);
    GetTextMetricsA(dc, &tm);
    printf("rect %ld %ld %ld %ld margins %d %d height %ld ave %ld\n", r.left, r.top, r.right, r.bottom,
           LOWORD(mg), HIWORD(mg), tm.tmHeight, tm.tmAveCharWidth);
    ReleaseDC(ed, dc);
    UpdateWindow(top);
    for (i = 0; i < 10; i++) {
        while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
            DispatchMessageA(&msg);
        Sleep(20);
    }
    dc = GetDC(top);
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
    f = fopen("Z:\\work\\run\\editprobe.ppm", "wb");
    fprintf(f, "P6\n%d %d\n255\n", W, H);
    for (y = 0; y < H; y++)
        for (x = 0; x < W; x++) {
            unsigned char *p = bits + 4 * (y * W + x);
            fputc(p[2], f); fputc(p[1], f); fputc(p[0], f);
        }
    fclose(f);
    return 0;
}
