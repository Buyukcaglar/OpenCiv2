/*
 * Windows: the system's fonts for the platform layer's text
 * (host_font_open, host_font_glyph; src/platform/text.c): each glyph as
 * GDI draws it, in the font the game asks for, as the original's text was
 * drawn on Windows.  Aliased glyphs are drawn with TextOut (raster fonts,
 * such as System and Courier, too); antialiased ones are GDI's 17 levels of
 * coverage (GetGlyphOutline), or the aliased glyph where the font has no
 * outlines.  The game's text is code page 1252.
 */
#include <windows.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "host.h"

#define MAX_FONTS 256

static struct {
    HFONT plain, aa;            /* NONANTIALIASED_QUALITY, ANTIALIASED_QUALITY */
    int ascent, height;
} fonts[MAX_FONTS + 1];
static int nfonts;

static HDC dc;
static HBITMAP dib;
static uint32_t *dib_px;
static int dib_w, dib_h;

/* A memory DC with a 32-bit top-down bitmap of at least w x h selected. */
static int glyph_dc(int w, int h)
{
    BITMAPINFO bi;
    void *px = NULL;
    HBITMAP b;
    if (!dc && !(dc = CreateCompatibleDC(NULL)))
        return 0;
    if (dib && w <= dib_w && h <= dib_h)
        return 1;
    if (w < dib_w)
        w = dib_w;
    if (h < dib_h)
        h = dib_h;
    memset(&bi, 0, sizeof bi);
    bi.bmiHeader.biSize = sizeof bi.bmiHeader;
    bi.bmiHeader.biWidth = w;
    bi.bmiHeader.biHeight = -h;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    bi.bmiHeader.biCompression = BI_RGB;
    b = CreateDIBSection(dc, &bi, DIB_RGB_COLORS, &px, NULL, 0);
    if (!b)
        return 0;
    SelectObject(dc, b);
    if (dib)
        DeleteObject(dib);
    dib = b;
    dib_px = (uint32_t *)px;
    dib_w = w;
    dib_h = h;
    return 1;
}

int host_font_open(const char *face, int height, int weight, int italic, int pitch_family, int32_t *tm)
{
    LOGFONTA lf;
    TEXTMETRICA m;
    char got[LF_FACESIZE];
    int i;
    if (nfonts >= MAX_FONTS || !glyph_dc(1, 1))
        return 0;
    memset(&lf, 0, sizeof lf);
    lf.lfHeight = height;
    lf.lfWeight = weight;
    lf.lfItalic = (BYTE)(italic != 0);
    lf.lfCharSet = ANSI_CHARSET;
    lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
    lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
    lf.lfPitchAndFamily = (BYTE)pitch_family;
    snprintf(lf.lfFaceName, sizeof lf.lfFaceName, "%s", face ? face : "");
    lf.lfQuality = NONANTIALIASED_QUALITY;
    i = nfonts + 1;
    fonts[i].plain = CreateFontIndirectA(&lf);
    lf.lfQuality = ANTIALIASED_QUALITY;
    fonts[i].aa = CreateFontIndirectA(&lf);
    if (!fonts[i].plain || !fonts[i].aa) {
        if (fonts[i].plain)
            DeleteObject(fonts[i].plain);
        if (fonts[i].aa)
            DeleteObject(fonts[i].aa);
        return 0;
    }
    SelectObject(dc, fonts[i].plain);
    if (!GetTextMetricsA(dc, &m) || !GetTextFaceA(dc, sizeof got, got)) {
        DeleteObject(fonts[i].plain);
        DeleteObject(fonts[i].aa);
        return 0;
    }
    fonts[i].ascent = m.tmAscent;
    fonts[i].height = m.tmHeight;
    tm[0] = m.tmHeight;
    tm[1] = m.tmAscent;
    tm[2] = m.tmDescent;
    tm[3] = m.tmInternalLeading;
    tm[4] = m.tmExternalLeading;
    tm[5] = m.tmAveCharWidth;
    tm[6] = m.tmMaxCharWidth;
    tm[7] = m.tmWeight;
    tm[8] = m.tmOverhang;
    tm[9] = (int32_t)((uint32_t)(BYTE)m.tmFirstChar | (uint32_t)(BYTE)m.tmLastChar << 8 |
                      (uint32_t)(BYTE)m.tmDefaultChar << 16 | (uint32_t)(BYTE)m.tmBreakChar << 24);
    tm[10] = (int32_t)((uint32_t)m.tmPitchAndFamily | (uint32_t)m.tmCharSet << 8);
    nfonts = i;
    return i;
}

/* The aliased glyph as TextOut draws it: into bits (rows of (w+7)/8
   bytes) if it fits size; its place in m.  The bytes it needs. */
static int plain_glyph(int i, WCHAR wc, int32_t *m, uint8_t *bits, int size)
{
    SIZE ext;
    int pad, w, h, x, y, left, top, right, bottom, stride, need;
    SelectObject(dc, fonts[i].plain);
    if (!GetTextExtentPoint32W(dc, &wc, 1, &ext))
        return -1;
    pad = fonts[i].height + 2;          /* room for italic and kerned overhangs */
    w = (int)ext.cx + 2 * pad;
    h = fonts[i].height;
    if (h <= 0 || !glyph_dc(w, h))
        return -1;
    memset(dib_px, 0, (size_t)dib_w * dib_h * 4);
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, RGB(255, 255, 255));
    SetTextAlign(dc, TA_LEFT | TA_TOP | TA_NOUPDATECP);
    TextOutW(dc, pad, 0, &wc, 1);
    GdiFlush();
    left = w;
    top = h;
    right = bottom = -1;
    for (y = 0; y < h; y++)
        for (x = 0; x < w; x++)
            if (dib_px[(size_t)y * dib_w + x] & 0xffffff) {
                if (x < left) left = x;
                if (x > right) right = x;
                if (y < top) top = y;
                if (y > bottom) bottom = y;
            }
    m[0] = (int32_t)ext.cx;
    if (right < 0) {
        m[1] = m[2] = m[3] = m[4] = 0;
        return 0;
    }
    m[1] = left - pad;
    m[2] = top;
    m[3] = right - left + 1;
    m[4] = bottom - top + 1;
    stride = (m[3] + 7) / 8;
    need = stride * m[4];
    if (need <= size) {
        memset(bits, 0, (size_t)need);
        for (y = 0; y < m[4]; y++)
            for (x = 0; x < m[3]; x++)
                if (dib_px[(size_t)(top + y) * dib_w + left + x] & 0xffffff)
                    bits[y * stride + (x >> 3)] |= (uint8_t)(0x80 >> (x & 7));
    }
    return need;
}

/* The antialiased glyph: GDI's coverage, 0..16 a pixel (w*h bytes). */
static int aa_glyph(int i, WCHAR wc, int32_t *m, uint8_t *bits, int size)
{
    static const MAT2 identity = {{0, 1}, {0, 0}, {0, 0}, {0, 1}};
    GLYPHMETRICS gm;
    DWORD n;
    int x, y, stride, need;
    uint8_t *buf;
    SIZE ext;
    SelectObject(dc, fonts[i].aa);
    if (!GetTextExtentPoint32W(dc, &wc, 1, &ext))
        return -1;
    memset(&gm, 0, sizeof gm);
    n = GetGlyphOutlineW(dc, wc, GGO_GRAY4_BITMAP, &gm, 0, NULL, &identity);
    if (n == GDI_ERROR) {
        /* no outlines (a raster font): the aliased glyph, at full coverage */
        int32_t pm[5];
        int pneed = plain_glyph(i, wc, pm, NULL, 0), pstride;
        uint8_t *pb;
        if (pneed < 0)
            return -1;
        memcpy(m, pm, sizeof pm);
        need = pm[3] * pm[4];
        if (need > size || need == 0)
            return need;
        pb = (uint8_t *)malloc((size_t)pneed);
        if (!pb)
            return -1;
        plain_glyph(i, wc, pm, pb, pneed);
        pstride = (pm[3] + 7) / 8;
        for (y = 0; y < pm[4]; y++)
            for (x = 0; x < pm[3]; x++)
                bits[y * pm[3] + x] = (pb[y * pstride + (x >> 3)] & (0x80 >> (x & 7))) ? 16 : 0;
        free(pb);
        return need;
    }
    m[0] = (int32_t)ext.cx;
    if (n == 0) {
        m[1] = m[2] = m[3] = m[4] = 0;      /* a space */
        return 0;
    }
    m[1] = gm.gmptGlyphOrigin.x;
    m[2] = fonts[i].ascent - gm.gmptGlyphOrigin.y;
    m[3] = (int32_t)gm.gmBlackBoxX;
    m[4] = (int32_t)gm.gmBlackBoxY;
    need = m[3] * m[4];
    if (need > size)
        return need;
    buf = (uint8_t *)malloc(n);
    if (!buf)
        return -1;
    if (GetGlyphOutlineW(dc, wc, GGO_GRAY4_BITMAP, &gm, n, buf, &identity) == GDI_ERROR) {
        free(buf);
        return -1;
    }
    stride = (m[3] + 3) & ~3;
    for (y = 0; y < m[4]; y++)
        for (x = 0; x < m[3]; x++)
            bits[y * m[3] + x] = buf[y * stride + x];
    free(buf);
    return need;
}

int host_font_glyph(int font, int ch, int aa, int32_t *m, uint8_t *bits, int size)
{
    char c = (char)ch;
    WCHAR wc = 0;
    if (font < 1 || font > nfonts || ch < 0 || ch > 255)
        return -1;
    if (!MultiByteToWideChar(1252, 0, &c, 1, &wc, 1))
        wc = (WCHAR)ch;
    return aa ? aa_glyph(font, wc, m, bits, size) : plain_glyph(font, wc, m, bits, size);
}

/* ---- sharp text (host_present_text, host_sdl.c): the platform's texts
   drawn again at k screen pixels per desktop pixel ---- */

#define MAX_TEXT_FONTS 1024
#define MAX_K 8

static struct {
    LOGFONTA lf;
    HFONT at[MAX_K + 1];        /* by scale, made when first drawn */
    short *adv[MAX_K + 1];      /* its letters' advances there, -1 until measured */
} text_fonts[MAX_TEXT_FONTS];

static HDC text_dc;
static HBITMAP text_dib;
static uint32_t *text_px;
static int text_w, text_h;

void host_text_font(int id, const char *face, int height, int weight, int italic, int pitch_family)
{
    LOGFONTA *lf;
    int k;
    if (id < 0 || id >= MAX_TEXT_FONTS)
        return;
    for (k = 0; k <= MAX_K; k++) {
        if (text_fonts[id].at[k]) {
            DeleteObject(text_fonts[id].at[k]);
            text_fonts[id].at[k] = NULL;
        }
        free(text_fonts[id].adv[k]);
        text_fonts[id].adv[k] = NULL;
    }
    lf = &text_fonts[id].lf;
    memset(lf, 0, sizeof *lf);
    lf->lfHeight = height;
    lf->lfWeight = weight;
    lf->lfItalic = (BYTE)(italic != 0);
    lf->lfCharSet = ANSI_CHARSET;
    lf->lfOutPrecision = OUT_TT_PRECIS;
    lf->lfClipPrecision = CLIP_DEFAULT_PRECIS;
    lf->lfQuality = ANTIALIASED_QUALITY;
    lf->lfPitchAndFamily = (BYTE)pitch_family;
    snprintf(lf->lfFaceName, sizeof lf->lfFaceName, "%s", face ? face : "");
}

/* The frame the texts are drawn into: w x h, 32-bit, top-down. */
uint32_t *host_win_text_buffer(int w, int h)
{
    BITMAPINFO bi;
    void *px = NULL;
    HBITMAP b;
    if (!text_dc && !(text_dc = CreateCompatibleDC(NULL)))
        return NULL;
    if (text_dib && w == text_w && h == text_h)
        return text_px;
    memset(&bi, 0, sizeof bi);
    bi.bmiHeader.biSize = sizeof bi.bmiHeader;
    bi.bmiHeader.biWidth = w;
    bi.bmiHeader.biHeight = -h;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    bi.bmiHeader.biCompression = BI_RGB;
    b = CreateDIBSection(text_dc, &bi, DIB_RGB_COLORS, &px, NULL, 0);
    if (!b)
        return NULL;
    SelectObject(text_dc, b);
    if (text_dib)
        DeleteObject(text_dib);
    text_dib = b;
    text_px = (uint32_t *)px;
    text_w = w;
    text_h = h;
    return text_px;
}

static HFONT text_font_at(int id, int k)
{
    LOGFONTA lf;
    if (id < 0 || id >= MAX_TEXT_FONTS || k < 1 || k > MAX_K || !text_fonts[id].lf.lfHeight)
        return NULL;
    if (!text_fonts[id].at[k]) {
        lf = text_fonts[id].lf;
        lf.lfHeight *= k;
        text_fonts[id].at[k] = CreateFontIndirectA(&lf);
    }
    return text_fonts[id].at[k];
}

void host_win_text_draw(const HostText *t, int n, int k)
{
    int i;
    if (!text_dc || !text_dib)
        return;
    SetBkMode(text_dc, TRANSPARENT);
    SetTextAlign(text_dc, TA_BASELINE | TA_LEFT | TA_NOUPDATECP);
    for (i = 0; i < n; i++) {
        COLORREF c = RGB(t[i].color >> 16 & 255, t[i].color >> 8 & 255, t[i].color & 255);
        RECT r;
        r.left = t[i].left * k;
        r.top = t[i].top * k;
        r.right = t[i].right * k;
        r.bottom = t[i].bottom * k;
        if (t[i].kind == 1) {
            HBRUSH br = CreateSolidBrush(c);
            if (br) {
                FillRect(text_dc, &r, br);
                DeleteObject(br);
            }
        } else {
            HFONT f = text_font_at(t[i].font, k);
            char ch = (char)t[i].ch;
            WCHAR wc = 0;
            if (!f)
                continue;
            if (!MultiByteToWideChar(1252, 0, &ch, 1, &wc, 1))
                wc = (WCHAR)(t[i].ch & 255);
            SelectObject(text_dc, f);
            SetTextColor(text_dc, c);
            {
                /* the letter centred in its cell as the desktop has it, so
                   that the rounding of the advances is shared out evenly */
                short **adv = &text_fonts[t[i].font].adv[k], *a;
                int x = t[i].x * k;
                if (!*adv && (*adv = malloc(256 * sizeof **adv)))
                    memset(*adv, 0xff, 256 * sizeof **adv);
                if ((a = *adv) != NULL) {
                    int ci = t[i].ch & 255;
                    if (a[ci] < 0) {
                        SIZE ext;
                        a[ci] = GetTextExtentPoint32W(text_dc, &wc, 1, &ext) ? (short)ext.cx : 0;
                    }
                    if (t[i].adv > 0 && a[ci] > 0)
                        x += (t[i].adv * k - a[ci]) / 2;
                }
                ExtTextOutW(text_dc, x, t[i].y * k, ETO_CLIPPED, &r, &wc, 1, NULL);
            }
        }
    }
    GdiFlush();
}
