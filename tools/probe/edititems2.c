/* Probe: the Civilopedia's text pane (screens 11-pedia-governments-page):
 * a multiline read-only EDIT (style ARG1, default 0x50200844; the game asks
 * for WS_BORDER too: 50a00844) in Times New Roman -21 (DejaVu Serif, ARG2) with
 * the Anarchy text; prints EM_GETRECT and writes run/edititems2.ppm. */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

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
    RECT r, cr;
    LOGFONTA lf;
    HFONT font;
    LRESULT mg;
    int x, y, i;
    const int W = 700, H = 340;
    DWORD style = argc > 1 ? strtoul(argv[1], NULL, 16) : 0x50200844;
    memset(&wc, 0, sizeof wc);
    wc.lpfnWndProc = proc;
    wc.lpszClassName = "probe";
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    RegisterClassA(&wc);
    top = CreateWindowExA(0, "probe", "", WS_POPUP | WS_VISIBLE, 0, 0, W, H, NULL, NULL, NULL, NULL);
    ed = CreateWindowExA(4, "EDIT", "", style, 20, 10, 603 + GetSystemMetrics(SM_CXVSCROLL), 313, top, NULL, NULL, NULL);
    memset(&lf, 0, sizeof lf);
    lf.lfHeight = -21;
    lf.lfWeight = 400;
    strcpy(lf.lfFaceName, argc > 2 ? argv[2] : "DejaVu Serif");
    font = CreateFontIndirectA(&lf);
    SendMessageA(ed, WM_SETFONT, (WPARAM)font, 0);
    SetWindowTextA(ed, "Anarchy represents not so much a government type as the lack of any stable government. Anarchy occurs when your civilization's government falls, or when you decide to have a Revolution. After a few turns of Anarchy, you can rebuild a new government. Anarchy is similar to Despotism, except that the corruption rate is VERY HIGH. However, no taxes are collected during a period of Anarchy, and no scientific research is conducted.");
    SendMessageA(ed, EM_GETRECT, 0, (LPARAM)&r);
    GetClientRect(ed, &cr);
    mg = SendMessageA(ed, EM_GETMARGINS, 0, 0);
    printf("client %ld %ld rect %ld %ld %ld %ld margins %d %d\n", cr.right, cr.bottom, r.left, r.top, r.right, r.bottom,
           LOWORD(mg), HIWORD(mg));
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
    f = fopen("Z:\\work\\run\\edititems2.ppm", "wb");
    fprintf(f, "P6\n%d %d\n255\n", W, H);
    for (y = 0; y < H; y++)
        for (x = 0; x < W; x++) {
            unsigned char *p = bits + 4 * (y * W + x);
            fputc(p[2], f); fputc(p[1], f); fputc(p[0], f);
        }
    fclose(f);
    return 0;
}
