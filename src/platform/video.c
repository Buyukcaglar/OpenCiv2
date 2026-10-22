/*
 * Video for Windows, as much as the game uses: AVI files (AVIFile*,
 * AVIStream*) and an installable decompressor for Intel Indeo 4.1 (ICLocate,
 * ICSendMessage, ICClose) over src/third_party/indeo4.
 *
 * The game asks the decompressor for its palette (entries 10..245 become the
 * window's), hands back the result and has 8-bit frames drawn with it: here
 * a palette of a 6x6x6 colour cube and 20 greys, matched with an ordered
 * dither.  (Intel's own palette and dither are not reproduced, nor the
 * transparency mask of the herald videos: black stands for transparent.)
 */
#include "plat.h"
#include "plat_files.h"
#include "../third_party/indeo4/iv41.h"

#ifndef DRV_USER
#define DRV_USER 0x4000
#endif
#ifndef FIND_NEXT
#define FIND_NEXT 0x0001
#define FIND_PREV 0x0004
#define FIND_KEY 0x0010
#endif

#define FCC(a, b, c, d) ((DWORD)(a) | (DWORD)(b) << 8 | (DWORD)(c) << 16 | (DWORD)(d) << 24)

static DWORD rd32(const unsigned char *p) { return (DWORD)(p[0] | p[1] << 8 | p[2] << 16 | (DWORD)p[3] << 24); }
static WORD rd16(const unsigned char *p) { return (WORD)(p[0] | p[1] << 8); }

/* ---- AVI files ---- */

typedef struct { DWORD off, size; int key; } Sample;

typedef struct {
    unsigned char strh[56];
    unsigned char *fmt;
    LONG fmt_size;
    Sample *samples;
    int n, cap;
} Stream;

#define MAX_STREAMS 4
typedef struct {
    unsigned char *data;
    long size;
    Stream streams[MAX_STREAMS];
    int nstreams;
} AviFile;

typedef struct { AviFile *file; int index; } AviStreamRef;

static void add_sample(Stream *s, DWORD off, DWORD size)
{
    if (s->n == s->cap) {
        s->cap = s->cap ? 2 * s->cap : 256;
        s->samples = realloc(s->samples, sizeof *s->samples * (size_t)s->cap);
    }
    s->samples[s->n].off = off;
    s->samples[s->n].size = size;
    s->samples[s->n].key = s->n == 0;
    s->n++;
}

/* The chunks of a list from p to end: headers, stream lists, the movi data. */
static void parse_list(AviFile *a, long p, long end, int in_movi, long *movi)
{
    while (p + 8 <= end) {
        DWORD id = rd32(a->data + p), len = rd32(a->data + p + 4);
        long body = p + 8;
        if (body + (long)len > end)
            len = (DWORD)(end - body);
        if (id == FCC('L', 'I', 'S', 'T') && len >= 4) {
            DWORD type = rd32(a->data + body);
            if (type == FCC('m', 'o', 'v', 'i'))
                *movi = body;
            if (type == FCC('s', 't', 'r', 'l') && a->nstreams < MAX_STREAMS)
                a->nstreams++;
            parse_list(a, body + 4, body + (long)len, in_movi || type == FCC('m', 'o', 'v', 'i'), movi);
        } else if (id == FCC('s', 't', 'r', 'h') && a->nstreams) {
            memcpy(a->streams[a->nstreams - 1].strh, a->data + body, len < 56 ? len : 56);
        } else if (id == FCC('s', 't', 'r', 'f') && a->nstreams) {
            Stream *s = &a->streams[a->nstreams - 1];
            s->fmt = malloc(len ? len : 1);
            memcpy(s->fmt, a->data + body, len);
            s->fmt_size = (LONG)len;
        } else if (id == FCC('i', 'd', 'x', '1') && *movi) {
            /* key frames: entries in file order, per stream; offsets from movi */
            int seen[MAX_STREAMS] = {0};
            DWORD i;
            for (i = 0; i + 16 <= len; i += 16) {
                const unsigned char *e = a->data + body + i;
                int st = (e[0] - '0') * 10 + (e[1] - '0');
                if (st < 0 || st >= a->nstreams || seen[st] >= a->streams[st].n)
                    continue;
                a->streams[st].samples[seen[st]++].key = (rd32(e + 4) & AVIIF_KEYFRAME) != 0;
            }
        } else if (in_movi && id != FCC('J', 'U', 'N', 'K')) {
            int st = (int)((id & 0xff) - '0') * 10 + (int)(((id >> 8) & 0xff) - '0');
            if (st >= 0 && st < a->nstreams)
                add_sample(&a->streams[st], (DWORD)body, len);
        }
        p = body + (long)len + (long)(len & 1);
    }
}

void WINAPI AVIFileInit(void) { API_TRACE(); }
void WINAPI AVIFileExit(void) { API_TRACE(); }

HRESULT WINAPI AVIFileOpenA(PAVIFILE *pf, LPCSTR name, UINT mode, LPCLSID handler)
{ API_TRACE();
    char host[1024];
    FILE *f;
    AviFile *a;
    long movi = 0;
    (void)mode; (void)handler;
    *pf = 0;
    plat_host_path(name, host, sizeof host, 0);
    f = fopen(host, "rb");
    if (!f)
        return AVIERR_FILEOPEN;
    a = calloc(1, sizeof *a);
    fseek(f, 0, SEEK_END);
    a->size = ftell(f);
    fseek(f, 0, SEEK_SET);
    a->data = malloc((size_t)a->size + 1);
    if (fread(a->data, 1, (size_t)a->size, f) != (size_t)a->size || a->size < 12 ||
        memcmp(a->data, "RIFF", 4) || memcmp(a->data + 8, "AVI ", 4)) {
        fclose(f);
        free(a->data);
        free(a);
        return AVIERR_FILEOPEN;
    }
    fclose(f);
    parse_list(a, 12, a->size, 0, &movi);
    plat_log("AVIFileOpen(%s): %d streams\n", name, a->nstreams);
    *pf = (PAVIFILE)obj_new(OBJ_AVIFILE, a);
    return AVIERR_OK;
}

ULONG WINAPI AVIFileRelease(PAVIFILE pf)
{ API_TRACE();
    AviFile *a = obj_get((Handle)pf, OBJ_AVIFILE);
    int i;
    if (!a)
        return 0;
    for (i = 0; i < a->nstreams; i++) {
        free(a->streams[i].fmt);
        free(a->streams[i].samples);
    }
    free(a->data);
    free(a);
    obj_free((Handle)pf);
    return 0;
}

HRESULT WINAPI AVIFileGetStream(PAVIFILE pf, PAVISTREAM *ps, DWORD type, LONG n)
{ API_TRACE();
    AviFile *a = obj_get((Handle)pf, OBJ_AVIFILE);
    int i;
    *ps = 0;
    if (!a)
        return AVIERR_NODATA;
    for (i = 0; i < a->nstreams; i++)
        if (!type || rd32(a->streams[i].strh) == type) {
            if (n-- == 0) {
                AviStreamRef *r = calloc(1, sizeof *r);
                r->file = a;
                r->index = i;
                *ps = (PAVISTREAM)obj_new(OBJ_AVISTREAM, r);
                return AVIERR_OK;
            }
        }
    return AVIERR_NODATA;
}

static Stream *stream_of(PAVISTREAM ps)
{
    AviStreamRef *r = obj_get((Handle)ps, OBJ_AVISTREAM);
    return r ? &r->file->streams[r->index] : NULL;
}

ULONG WINAPI AVIStreamRelease(PAVISTREAM ps)
{ API_TRACE();
    AviStreamRef *r = obj_get((Handle)ps, OBJ_AVISTREAM);
    if (r) {
        free(r);
        obj_free((Handle)ps);
    }
    return 0;
}

HRESULT WINAPI AVIStreamInfoA(PAVISTREAM ps, LPAVISTREAMINFOA i, LONG n)
{ API_TRACE();
    Stream *s = stream_of(ps);
    const unsigned char *h;
    AVISTREAMINFOA info;
    if (!s)
        return AVIERR_NODATA;
    h = s->strh;
    memset(&info, 0, sizeof info);
    info.fccType = rd32(h);
    info.fccHandler = rd32(h + 4);
    info.dwFlags = rd32(h + 8);
    info.wPriority = rd16(h + 12);
    info.wLanguage = rd16(h + 14);
    info.dwInitialFrames = rd32(h + 16);
    info.dwScale = rd32(h + 20);
    info.dwRate = rd32(h + 24);
    info.dwStart = rd32(h + 28);
    info.dwLength = (DWORD)s->n;
    info.dwSuggestedBufferSize = rd32(h + 36);
    info.dwQuality = rd32(h + 40);
    info.dwSampleSize = rd32(h + 44);
    info.rcFrame.left = (short)rd16(h + 48);
    info.rcFrame.top = (short)rd16(h + 50);
    info.rcFrame.right = (short)rd16(h + 52);
    info.rcFrame.bottom = (short)rd16(h + 54);
    memcpy(i, &info, (size_t)n < sizeof info ? (size_t)n : sizeof info);
    return AVIERR_OK;
}

LONG WINAPI AVIStreamStart(PAVISTREAM ps) { API_TRACE(); Stream *s = stream_of(ps); return s ? (LONG)rd32(s->strh + 28) : 0; }
LONG WINAPI AVIStreamLength(PAVISTREAM ps) { API_TRACE(); Stream *s = stream_of(ps); return s ? s->n : 0; }

HRESULT WINAPI AVIStreamReadFormat(PAVISTREAM ps, LONG pos, LPVOID fmt, LONG *n)
{ API_TRACE();
    Stream *s = stream_of(ps);
    (void)pos;
    if (!s || !s->fmt) {
        *n = 0;
        return AVIERR_NODATA;
    }
    if (fmt)
        memcpy(fmt, s->fmt, (size_t)(*n < s->fmt_size ? *n : s->fmt_size));
    *n = s->fmt_size;
    return AVIERR_OK;
}

HRESULT WINAPI AVIStreamRead(PAVISTREAM ps, LONG start, LONG n, LPVOID buf, LONG cb, LONG *bytes, LONG *samples)
{ API_TRACE();
    AviStreamRef *r = obj_get((Handle)ps, OBJ_AVISTREAM);
    Stream *s = r ? &r->file->streams[r->index] : NULL;
    Sample *x;
    (void)n;
    if (bytes) *bytes = 0;
    if (samples) *samples = 0;
    if (!s || start < 0 || start >= s->n)
        return AVIERR_NODATA;
    x = &s->samples[start];
    if (getenv("CIV2_LOG_VIDEO"))
        plat_log("video: read frame %ld of %d at %lu ms\n", (long)start, s->n, (unsigned long)GetTickCount());
    if (buf) {
        if ((DWORD)cb < x->size)
            return AVIERR_BUFFERTOOSMALL;
        memcpy(buf, r->file->data + x->off, x->size);
    }
    if (bytes) *bytes = (LONG)x->size;
    if (samples) *samples = 1;
    return AVIERR_OK;
}

LONG WINAPI AVIStreamSampleToTime(PAVISTREAM ps, LONG n)
{ API_TRACE();
    Stream *s = stream_of(ps);
    DWORD scale = s ? rd32(s->strh + 20) : 0, rate = s ? rd32(s->strh + 24) : 0;
    return rate ? (LONG)((int64_t)n * scale * 1000 / rate) : 0;
}

LONG WINAPI AVIStreamTimeToSample(PAVISTREAM ps, LONG t)
{ API_TRACE();
    Stream *s = stream_of(ps);
    DWORD scale = s ? rd32(s->strh + 20) : 0, rate = s ? rd32(s->strh + 24) : 0;
    return scale ? (LONG)((int64_t)t * rate / ((int64_t)scale * 1000)) : 0;
}

LONG WINAPI AVIStreamFindSample(PAVISTREAM ps, LONG pos, LONG flags)
{ API_TRACE();
    Stream *s = stream_of(ps);
    int step = (flags & FIND_NEXT) ? 1 : -1;
    if (!s || !s->n)
        return -1;
    if (pos < 0) pos = 0;
    if (pos >= s->n) pos = s->n - 1;
    if (!(flags & FIND_KEY))
        return pos;
    for (; pos >= 0 && pos < s->n; pos += step)
        if (s->samples[pos].key)
            return pos;
    return -1;
}

/* ---- the IV41 decompressor ---- */

typedef struct {
    Iv41 *dec;
    int width, height;
    RGBQUAD pal[256];
    unsigned char lut[32768];   /* RGB 5:5:5 -> palette index */
    int lut_ok;
    int32_t *view;              /* where to report the area drawn: x, y, width, height */
} Codec;

typedef struct {
    DWORD dwFlags;
    BITMAPINFOHEADER *lpbiSrc;
    void *lpSrc;
    BITMAPINFOHEADER *lpbiDst;
    void *lpDst;
    int xDst, yDst, dxDst, dyDst, xSrc, ySrc, dxSrc, dySrc;
} DecompressEx;

/* The palette offered: Windows' 20 static colours around a colour cube and greys. */
static void video_palette(RGBQUAD *pal)
{
    static const unsigned char sys[20][3] = {
        {0, 0, 0}, {128, 0, 0}, {0, 128, 0}, {128, 128, 0}, {0, 0, 128}, {128, 0, 128}, {0, 128, 128},
        {192, 192, 192}, {192, 220, 192}, {166, 202, 240}, {255, 251, 240}, {160, 160, 164}, {128, 128, 128},
        {255, 0, 0}, {0, 255, 0}, {255, 255, 0}, {0, 0, 255}, {255, 0, 255}, {0, 255, 255}, {255, 255, 255}};
    int i, r, g, b, k = 10;
    memset(pal, 0, sizeof *pal * 256);
    for (i = 0; i < 10; i++) {
        pal[i].rgbRed = sys[i][0]; pal[i].rgbGreen = sys[i][1]; pal[i].rgbBlue = sys[i][2];
        pal[246 + i].rgbRed = sys[10 + i][0]; pal[246 + i].rgbGreen = sys[10 + i][1]; pal[246 + i].rgbBlue = sys[10 + i][2];
    }
    for (r = 0; r < 6; r++)
        for (g = 0; g < 6; g++)
            for (b = 0; b < 6; b++, k++) {
                pal[k].rgbRed = (BYTE)(r * 51); pal[k].rgbGreen = (BYTE)(g * 51); pal[k].rgbBlue = (BYTE)(b * 51);
            }
    for (i = 0; i < 20; i++, k++)       /* greys between the cube's */
        pal[k].rgbRed = pal[k].rgbGreen = pal[k].rgbBlue = (BYTE)(6 + i * 12);
}

static void build_lut(Codec *c)
{
    int i, best, bd, d, k;
    for (i = 0; i < 32768; i++) {
        int r = (i >> 10 & 31) * 255 / 31, g = (i >> 5 & 31) * 255 / 31, b = (i & 31) * 255 / 31;
        best = 10;
        bd = 1 << 30;
        for (k = 10; k < 246; k++) {
            int dr = r - c->pal[k].rgbRed, dg = g - c->pal[k].rgbGreen, db = b - c->pal[k].rgbBlue;
            d = 3 * dr * dr + 4 * dg * dg + 2 * db * db;
            if (d < bd) {
                bd = d;
                best = k;
            }
        }
        c->lut[i] = (unsigned char)best;
    }
    c->lut_ok = 1;
}

static int clamp8(int v) { return v < 0 ? 0 : v > 255 ? 255 : v; }

/* Draw the decoded frame into the destination DIB (8, 16, 24 or 32 bits;
 * bottom-up unless the height is negative), scaling the source rectangle. */
static void draw_frame(Codec *c, const Iv41Frame *fr, const DecompressEx *d)
{
    static const int bayer[4][4] = {{-24, 8, -16, 16}, {20, -8, 28, 0}, {-12, 20, -20, 12}, {24, 0, 16, -4}};
    BITMAPINFOHEADER *bi = d->lpbiDst;
    int bpp = bi->biBitCount, w = bi->biWidth, h = bi->biHeight < 0 ? -bi->biHeight : bi->biHeight;
    int stride = ((w * bpp + 31) / 32) * 4, top_down = bi->biHeight < 0, x, y;
    /* The destination is a DIB of ours: its real size, which can be smaller
       than the header says (a window's client area clamped to its maximum). */
    Bitmap *bm = bmp_of_bits(d->lpDst);
    if (getenv("CIV2_LOG_VIDEO"))
        plat_log("video: dst bitmap %dx%d/%d\n", bm ? bm->w : -1, bm ? bm->h : -1, bm ? bm->bpp : -1);
    if (bm && bm->bpp == bpp) {
        w = bm->w;
        h = bm->h;
        stride = bm->stride;
        top_down = !bm->bottom_up;
    }
    int dxs = d->dxSrc ? d->dxSrc : fr->width, dys = d->dySrc ? d->dySrc : fr->height;
    int dxd = d->dxDst ? d->dxDst : dxs, dyd = d->dyDst ? d->dyDst : dys;
    unsigned char *base = d->lpDst;
    if (bpp == 8 && !c->lut_ok)
        build_lut(c);
    for (y = 0; y < dyd; y++) {
        int ty = d->yDst + y, sy = d->ySrc + y * dys / dyd;
        unsigned char *row;
        if (ty < 0 || ty >= h || sy < 0 || sy >= fr->height)
            continue;
        row = base + (size_t)(top_down ? ty : h - 1 - ty) * stride;
        for (x = 0; x < dxd; x++) {
            int tx = d->xDst + x, sx = d->xSrc + x * dxs / dxd;
            int Y, U, V, r, g, b;
            if (tx < 0 || tx >= w || sx < 0 || sx >= fr->width)
                continue;
            Y = fr->y[sy * fr->y_stride + sx];
            U = fr->u[(sy >> 2) * fr->uv_stride + (sx >> 2)] - 128;
            V = fr->v[(sy >> 2) * fr->uv_stride + (sx >> 2)] - 128;
            /* Transparent areas (the heralds: a figure over the throne room)
               are encoded black; the mask itself is not decoded, so black
               stands for it and the background the game put there shows. */
            if (fr->has_transparency && Y <= 16 && U >= -2 && U <= 2 && V >= -2 && V <= 2)
                continue;
            Y = 298 * (Y - 16);
            r = clamp8((Y + 409 * V + 128) >> 8);
            g = clamp8((Y - 100 * U - 208 * V + 128) >> 8);
            b = clamp8((Y + 516 * U + 128) >> 8);
            switch (bpp) {
            case 8: {
                int e = bayer[ty & 3][tx & 3];
                r = clamp8(r + e); g = clamp8(g + e); b = clamp8(b + e);
                row[tx] = c->lut[(r >> 3) << 10 | (g >> 3) << 5 | (b >> 3)];
                break;
            }
            case 16: {
                WORD p = (WORD)((r >> 3) << 10 | (g >> 3) << 5 | (b >> 3));
                row[2 * tx] = (unsigned char)p;
                row[2 * tx + 1] = (unsigned char)(p >> 8);
                break;
            }
            case 24:
                row[3 * tx] = (unsigned char)b; row[3 * tx + 1] = (unsigned char)g; row[3 * tx + 2] = (unsigned char)r;
                break;
            case 32:
                row[4 * tx] = (unsigned char)b; row[4 * tx + 1] = (unsigned char)g; row[4 * tx + 2] = (unsigned char)r;
                row[4 * tx + 3] = 0;
                break;
            }
        }
    }
}

HIC WINAPI ICLocate(DWORD type, DWORD handler, LPBITMAPINFOHEADER in, LPBITMAPINFOHEADER out, WORD mode)
{ API_TRACE();
    Codec *c;
    (void)type; (void)out; (void)mode;
    if (!(in && (in->biCompression == FCC('I', 'V', '4', '1') || in->biCompression == FCC('i', 'v', '4', '1'))) &&
        handler != FCC('I', 'V', '4', '1') && handler != FCC('i', 'v', '4', '1'))
        return 0;
    c = calloc(1, sizeof *c);
    video_palette(c->pal);
    if (in) {
        c->width = in->biWidth;
        c->height = in->biHeight < 0 ? -in->biHeight : in->biHeight;
    }
    return (HIC)(uintptr_t)obj_new(OBJ_CODEC, c);
}

LRESULT WINAPI ICSendMessage(HIC h, UINT msg, DWORD_PTR a, DWORD_PTR b)
{ API_TRACE();
    Codec *c = obj_get((Handle)(uintptr_t)h, OBJ_CODEC);
    if (!c)
        return ICERR_BADHANDLE;
    switch (msg) {
    case ICM_DECOMPRESS_GET_PALETTE: {
        BITMAPINFOHEADER *bo = (BITMAPINFOHEADER *)b;
        if (bo) {
            memcpy((unsigned char *)bo + bo->biSize, c->pal, sizeof c->pal);
            bo->biClrUsed = 256;
        }
        return ICERR_OK;
    }
    case ICM_DECOMPRESS_SET_PALETTE: {
        BITMAPINFOHEADER *bo = (BITMAPINFOHEADER *)a;
        if (bo && bo->biBitCount == 8) {
            memcpy(c->pal, (unsigned char *)bo + bo->biSize, sizeof c->pal);
            c->lut_ok = 0;
        }
        return ICERR_OK;
    }
    case ICM_DECOMPRESSEX_QUERY:
    case ICM_DECOMPRESS_QUERY: {
        const DecompressEx *d = (const DecompressEx *)a;
        if (msg == ICM_DECOMPRESSEX_QUERY && d && d->lpbiDst) {
            int bpp = d->lpbiDst->biBitCount;
            if (d->lpbiDst->biCompression != BI_RGB || (bpp != 8 && bpp != 16 && bpp != 24 && bpp != 32))
                return ICERR_BADFORMAT;
        }
        return ICERR_OK;
    }
    case ICM_DECOMPRESSEX_BEGIN: {
        const DecompressEx *d = (const DecompressEx *)a;
        int w = d && d->lpbiSrc ? d->lpbiSrc->biWidth : c->width;
        int hh = d && d->lpbiSrc ? (d->lpbiSrc->biHeight < 0 ? -d->lpbiSrc->biHeight : d->lpbiSrc->biHeight) : c->height;
        if (!c->dec || w != c->width || hh != c->height) {
            iv41_close(c->dec);
            c->width = w;
            c->height = hh;
            c->dec = iv41_open(w, hh);
        }
        if (d && d->lpbiDst && d->lpbiDst->biBitCount == 8 && !c->lut_ok)
            memcpy(c->pal, (unsigned char *)d->lpbiDst + d->lpbiDst->biSize, sizeof c->pal);
        return c->dec ? ICERR_OK : ICERR_ERROR;
    }
    case ICM_DECOMPRESSEX: {
        const DecompressEx *d = (const DecompressEx *)a;
        Iv41Frame fr;
        if (!c->dec || !d || !d->lpbiSrc || !d->lpSrc)
            return ICERR_ERROR;
        if (!iv41_decode(c->dec, d->lpSrc, (int)d->lpbiSrc->biSizeImage, &fr))
            return ICERR_OK;            /* a frame that only updates the decoder's state */
        if (getenv("CIV2_LOG_VIDEO"))
            plat_log("video: frame %dx%d -> dst %ldx%ld/%d at %p (%d,%d %dx%d) flags %lx\n", fr.width, fr.height,
                     (long)d->lpbiDst->biWidth, (long)d->lpbiDst->biHeight, d->lpbiDst->biBitCount, d->lpDst, d->xDst,
                     d->yDst, d->dxDst, d->dyDst, (unsigned long)d->dwFlags);
        if (!(d->dwFlags & ICDECOMPRESS_PREROLL) && d->lpDst && d->lpbiDst) {
            draw_frame(c, &fr, d);
            if (c->view) {              /* the game copies this area to the screen */
                c->view[0] = d->xDst;
                c->view[1] = d->yDst;
                c->view[2] = d->dxDst ? d->dxDst : fr.width;
                c->view[3] = d->dyDst ? d->dyDst : fr.height;
            }
        }
        return ICERR_OK;
    }
    case ICM_DECOMPRESSEX_END:
        return ICERR_OK;
    case 0x5001:
        /* Indeo's private settings: the 0x70-byte frame settings hold, at
           0x3c, where the decoder reports each frame's drawn area (the game
           copies only that to the screen in its keyed mode, the heralds) */
        if (b == 0x70 && a)
            c->view = (int32_t *)(uintptr_t)*(const uint32_t *)((const unsigned char *)a + 0x3c);
        return ICERR_OK;
    }
    return ICERR_UNSUPPORTED;
}

LRESULT WINAPI ICClose(HIC h)
{ API_TRACE();
    Codec *c = obj_get((Handle)(uintptr_t)h, OBJ_CODEC);
    if (c) {
        iv41_close(c->dec);
        free(c);
        obj_free((Handle)(uintptr_t)h);
    }
    return ICERR_OK;
}
