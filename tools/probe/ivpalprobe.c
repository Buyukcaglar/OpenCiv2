/* The palette Intel's Indeo 4.1 decompressor (ir41_32.dll, from the game
 * disc's Indeo installer) gives an 8-bit IV41 decompression, asked as the
 * game asks it (ICM_DECOMPRESSEX_QUERY, then ICM_DECOMPRESS_GET_PALETTE):
 * printed as 256 "index r g b" lines.  Usage: run.sh ivpalprobe DLLPATH */
#include <windows.h>
#include <vfw.h>
#include <stdio.h>

typedef LRESULT (WINAPI *DriverProcFn)(DWORD_PTR, HDRVR, UINT, LPARAM, LPARAM);

int main(int argc, char **argv)
{
    HMODULE m = LoadLibraryA(argc > 1 ? argv[1] : "ir41_32.dll");
    DriverProcFn proc;
    ICOPEN open;
    DWORD_PTR id;
    struct { BITMAPINFOHEADER h; RGBQUAD pal[256]; } in, out;
    ICDECOMPRESSEX dx;
    LRESULT r;
    int i;
    if (!m || !(proc = (DriverProcFn)GetProcAddress(m, "DriverProc"))) {
        printf("cannot load the decompressor\n");
        return 1;
    }
    proc(0, (HDRVR)1, DRV_LOAD, 0, 0);
    proc(0, (HDRVR)1, DRV_ENABLE, 0, 0);
    memset(&open, 0, sizeof open);
    open.dwSize = sizeof open;
    open.fccType = ICTYPE_VIDEO;
    open.fccHandler = mmioFOURCC('I', 'V', '4', '1');
    open.dwFlags = ICMODE_DECOMPRESS;
    id = (DWORD_PTR)proc(0, (HDRVR)1, DRV_OPEN, 0, (LPARAM)&open);
    if (!id) {
        printf("DRV_OPEN failed\n");
        return 1;
    }
    memset(&in, 0, sizeof in);
    in.h.biSize = sizeof in.h;
    in.h.biWidth = 196;
    in.h.biHeight = 396;
    in.h.biPlanes = 1;
    in.h.biBitCount = 24;
    in.h.biCompression = mmioFOURCC('I', 'V', '4', '1');
    out = in;
    out.h.biBitCount = 8;
    out.h.biCompression = BI_RGB;
    out.h.biSizeImage = 196 * 396;
    out.h.biClrUsed = 256;
    memset(&dx, 0, sizeof dx);
    dx.lpbiSrc = &in.h;
    dx.lpbiDst = &out.h;
    dx.dxSrc = dx.dxDst = 196;
    dx.dySrc = dx.dyDst = 396;
    r = proc(id, (HDRVR)1, ICM_DECOMPRESSEX_QUERY, (LPARAM)&dx, sizeof dx);
    printf("query %ld\n", (long)r);
    r = proc(id, (HDRVR)1, ICM_DECOMPRESS_GET_PALETTE, (LPARAM)&in, (LPARAM)&out);
    printf("get_palette %ld, %lu colours\n", (long)r, (unsigned long)out.h.biClrUsed);
    for (i = 0; i < 256; i++)
        printf("%d %d %d %d\n", i, out.pal[i].rgbRed, out.pal[i].rgbGreen, out.pal[i].rgbBlue);
    return 0;
}
