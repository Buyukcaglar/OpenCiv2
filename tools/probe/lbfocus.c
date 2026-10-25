/* Where Wine's listbox draws the dotted focus rectangle of the current item
 * after the list is refilled (LB_RESETCONTENT, LB_ADDSTRING..., LB_SETCURSEL
 * of the last item, which scrolls the list): for each count, the corner
 * pixels of the focused item (1 = inverted, 0 = not) and the top index. */
#include <windows.h>
#include <stdio.h>

static void pump(void)
{
    MSG m;
    while (PeekMessageA(&m, 0, 0, 0, PM_REMOVE)) {
        TranslateMessage(&m);
        DispatchMessageA(&m);
    }
}

int main(int argc, char **argv)
{
    HWND top, lb;
    int n, i, ih = argc > 1 ? atoi(argv[1]) : 19, h = argc > 2 ? atoi(argv[2]) : 96;
    char s[32];
    WNDCLASSA wc = {0};
    wc.lpfnWndProc = DefWindowProcA;
    wc.hInstance = GetModuleHandleA(0);
    wc.lpszClassName = "P";
    wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
    RegisterClassA(&wc);
    top = CreateWindowA("P", "p", WS_POPUP | WS_VISIBLE, 0, 0, 600, 400, 0, 0, 0, 0);
    lb = CreateWindowA("LISTBOX", "", WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT, 50, 50, 400, h, top, (HMENU)1, 0, 0);
    SendMessageA(lb, LB_SETITEMHEIGHT, 0, ih);
    SetFocus(lb);
    pump();
    for (n = 1; n <= 9; n++) {
        HDC dc;
        RECT r;
        SendMessageA(lb, LB_RESETCONTENT, 0, 0);
        for (i = 0; i < n; i++) {
            sprintf(s, "%d) ITEM", i + 1);
            SendMessageA(lb, LB_ADDSTRING, 0, (LPARAM)s);
        }
        SendMessageA(lb, LB_SETCURSEL, n - 1, 0);
        pump();
        UpdateWindow(lb);
        SendMessageA(lb, LB_GETITEMRECT, n - 1, (LPARAM)&r);
        dc = GetDC(lb);
        {
            COLORREF hi = GetPixel(dc, r.right - 20, r.top + 9);
            char t[16], l[24], rr[24], b[16];
            int k;
            for (k = 0; k < 6; k++) t[k] = GetPixel(dc, r.left + k, r.top) == hi ? '.' : 'X';
            t[6] = 0;
            for (k = 0; k < 6; k++) b[k] = GetPixel(dc, r.right - 6 + k, r.top) == hi ? '.' : 'X';
            b[6] = 0;
            for (k = 0; k < 19 && k < r.bottom - r.top; k++) l[k] = GetPixel(dc, r.left, r.top + k) == hi ? '.' : 'X';
            l[k] = 0;
            for (k = 0; k < 19 && k < r.bottom - r.top; k++) rr[k] = GetPixel(dc, r.right - 1, r.top + k) == hi ? '.' : 'X';
            rr[k] = 0;
            printf("n=%d top=%d rect=%ld,%ld,%ld,%ld top-left %s top-right %s left %s right %s\n", n,
                   (int)SendMessageA(lb, LB_GETTOPINDEX, 0, 0), r.left, r.top, r.right, r.bottom, t, b, l, rr);
        }
        ReleaseDC(lb, dc);
    }
    return 0;
}
