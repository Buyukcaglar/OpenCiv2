/*
 * (port) Sharp text: the characters the platform draws, drawn again by the
 * host over the scaled desktop at the screen's own resolution, antialiased
 * (plat.h, "sharp text").  The notes the text leaves on each surface, their
 * fingerprints, their way from surface to surface (gdi.c's blit) and onto
 * the screen (plat_compose), and the screen handed to the host with them.
 */
#include "plat.h"
#include "../host/host.h"

int plat_sharp_text;

#define MAX_NOTES 8192          /* a surface's; past that the invalid ones go, then the oldest */
#define MAX_FONTS 256

int sharp_surface(const Bitmap *b)
{
    return plat_sharp_text && b && (b->bpp == 8 || b->bpp == 16 || b->bpp == 24 || b->bpp == 32);
}

/* ---- fonts: each LOGFONT the text was drawn in, by number ---- */

static struct {
    char name[LF_FACESIZE];
    int height, weight, italic, pitch, sent;
} fonts[MAX_FONTS];
static int nfonts;

int sharp_font_id(const LOGFONTA *lf)
{
    int i, weight = lf->lfWeight ? (int)lf->lfWeight : 400;
    for (i = 0; i < nfonts; i++)
        if (fonts[i].height == (int)lf->lfHeight && fonts[i].weight == weight &&
            fonts[i].italic == (lf->lfItalic != 0) && fonts[i].pitch == lf->lfPitchAndFamily &&
            !strcasecmp(fonts[i].name, lf->lfFaceName))
            return i;
    if (nfonts >= MAX_FONTS)
        return -1;
    i = nfonts++;
    snprintf(fonts[i].name, sizeof fonts[i].name, "%s", lf->lfFaceName);
    fonts[i].height = (int)lf->lfHeight;
    fonts[i].weight = weight;
    fonts[i].italic = lf->lfItalic != 0;
    fonts[i].pitch = lf->lfPitchAndFamily;
    return i;
}

/* ---- notes ---- */

static int bytes_pp(const Bitmap *b) { return b->bpp / 8; }

static void rect_move(RECT *r, int dx, int dy)
{
    r->left += dx; r->right += dx;
    r->top += dy; r->bottom += dy;
}

static int rect_equal(const RECT *a, const RECT *b)
{
    return a->left == b->left && a->top == b->top && a->right == b->right && a->bottom == b->bottom;
}

unsigned long long note_hash(const Bitmap *b, const RECT *r)
{
    unsigned long long h = 1469598103934665603ull;
    int y, i, n = (int)(r->right - r->left) * bytes_pp(b);
    for (y = r->top; y < r->bottom; y++) {
        const unsigned char *p = bmp_row(b, y) + (size_t)r->left * bytes_pp(b);
        for (i = 0; i < n; i++)
            h = (h ^ p[i]) * 1099511628211ull;
    }
    return h;
}

int note_valid(const Bitmap *b, const TextNote *n)
{
    return note_hash(b, &n->r) == n->hash;
}

void note_free(TextNote *n)
{
    free(n->bg);
    n->bg = NULL;
}

void notes_remove(Bitmap *b, int i)
{
    TextNotes *ns = b->notes;
    note_free(&ns->v[i]);
    memmove(&ns->v[i], &ns->v[i + 1], (size_t)(ns->n - i - 1) * sizeof *ns->v);
    ns->n--;
}

static Bitmap *bits_seen[4];     /* plat_notes_copy's last surfaces */

void notes_free(Bitmap *b)
{
    int i;
    for (i = 0; i < 4; i++)
        if (bits_seen[i] == b)
            bits_seen[i] = NULL;
    if (!b || !b->notes)
        return;
    for (i = 0; i < b->notes->n; i++)
        note_free(&b->notes->v[i]);
    free(b->notes->v);
    free(b->notes);
    b->notes = NULL;
}

/* Room for one more: the invalid notes dropped, then the oldest half. */
static void notes_make_room(Bitmap *b)
{
    TextNotes *ns = b->notes;
    int i;
    if (ns->n < MAX_NOTES)
        return;
    for (i = ns->n - 1; i >= 0; i--)
        if (!note_valid(b, &ns->v[i]))
            notes_remove(b, i);
    while (ns->n >= MAX_NOTES / 2 + MAX_NOTES / 4)
        notes_remove(b, 0);
}

TextNote *notes_add(Bitmap *b)
{
    TextNotes *ns;
    if (!b->notes)
        b->notes = calloc(1, sizeof *b->notes);
    ns = b->notes;
    notes_make_room(b);
    if (ns->n == ns->cap) {
        int cap = ns->cap ? ns->cap * 2 : 64;
        TextNote *v = realloc(ns->v, (size_t)cap * sizeof *v);
        if (!v)
            return NULL;
        ns->v = v;
        ns->cap = cap;
    }
    memset(&ns->v[ns->n], 0, sizeof ns->v[0]);
    return &ns->v[ns->n++];
}

/* Before the text draws r (within the surface): a note with r's pixels as
   they are -- where earlier text that is still there covers them, the
   pixels that text covered, so that the note holds what is under all of
   it.  Earlier text whose pixels have changed is forgotten. */
int note_begin(Bitmap *b, const RECT *r, const RECT *clip)
{
    TextNotes *ns;
    TextNote *n;
    int i, y, bpp, w;
    if (!sharp_surface(b) || rect_empty(r))
        return -1;
    bpp = bytes_pp(b);
    w = (int)(r->right - r->left);
    if (b->notes)
        for (i = b->notes->n - 1; i >= 0; i--) {
            RECT a;
            if (rect_intersect(&a, &b->notes->v[i].r, r) && !note_valid(b, &b->notes->v[i]))
                notes_remove(b, i);
        }
    n = notes_add(b);
    if (!n)
        return -1;
    ns = b->notes;
    n->r = *r;
    n->clip = *clip;
    n->bg = malloc((size_t)w * (size_t)(r->bottom - r->top) * (size_t)bpp);
    if (!n->bg) {
        ns->n--;
        return -1;
    }
    for (y = r->top; y < r->bottom; y++)
        memcpy(n->bg + (size_t)(y - r->top) * w * bpp, bmp_row(b, y) + (size_t)r->left * bpp, (size_t)w * bpp);
    for (i = 0; i < ns->n - 1; i++) {
        const TextNote *o = &ns->v[i];
        RECT a;
        int ow = (int)(o->r.right - o->r.left);
        if (!rect_intersect(&a, &o->r, r))
            continue;
        for (y = a.top; y < a.bottom; y++)
            memcpy(n->bg + ((size_t)(y - r->top) * w + (a.left - r->left)) * bpp,
                   o->bg + ((size_t)(y - o->r.top) * ow + (a.left - o->r.left)) * bpp, (size_t)(a.right - a.left) * bpp);
    }
    return ns->n - 1;
}

/* After: the note's fingerprint, and those of the earlier text it drew
   over (still there, under it); the same character drawn again in the
   same place replaces the earlier note. */
void note_end(Bitmap *b, int k)
{
    TextNotes *ns = b->notes;
    TextNote *n;
    int i;
    if (k < 0 || !ns || k >= ns->n)
        return;
    n = &ns->v[k];
    n->hash = note_hash(b, &n->r);
    for (i = k - 1; i >= 0; i--) {
        TextNote *o = &ns->v[i];
        RECT a;
        if (!rect_intersect(&a, &o->r, &n->r))
            continue;
        if (o->kind == n->kind && o->font == n->font && o->ch == n->ch && o->color == n->color && o->x == n->x &&
            o->y == n->y && rect_equal(&o->r, &n->r)) {
            notes_remove(b, i);
            k--;
            n = &ns->v[k];
            continue;
        }
        o->hash = note_hash(b, &o->r);
    }
}

/* ---- the game's own copies (gfx_copy_pixels) ---- */

static Bitmap *bitmap_at(const void *bits)
{
    Bitmap *b;
    int i;
    for (i = 0; i < 4; i++)
        if (bits_seen[i] && bits_seen[i]->bits == (const unsigned char *)bits)
            return bits_seen[i];
    if (!(b = bmp_of_bits(bits)))
        return NULL;
    memmove(bits_seen + 1, bits_seen, 3 * sizeof *bits_seen);
    bits_seen[0] = b;
    return b;
}

void plat_notes_copy(const void *from_bits, const void *to_bits, int fx, int fy, int tx, int ty, int w, int h)
{
    Bitmap *s, *d;
    TextNote *v;
    RECT want, all = {0, 0, 0, 0};
    int i, n = 0, bpp, dx, dy;
    if (!plat_sharp_text || !(d = bitmap_at(to_bits)) || !sharp_surface(d))
        return;
    bpp = d->bpp / 8;
    if (!(s = bitmap_at(from_bits)) || s->bpp != d->bpp)
        return;
    tx /= bpp;
    fx /= bpp;
    w /= bpp;
    dx = tx - fx;
    dy = ty - fy;
    want.left = tx; want.top = ty; want.right = tx + w; want.bottom = ty + h;
    all.right = d->w;
    all.bottom = d->h;
    if (!rect_intersect(&want, &want, &all))
        return;
    /* the destination's text copied over goes */
    if (d->notes)
        for (i = d->notes->n - 1; i >= 0; i--) {
            RECT a;
            if (rect_intersect(&a, &d->notes->v[i].r, &want) && rect_equal(&a, &d->notes->v[i].r))
                notes_remove(d, i);
        }
    if (!s->notes || !s->notes->n || !(v = malloc((size_t)s->notes->n * sizeof *v)))
        return;
    /* the source's copied whole (taken first: they may be the same surface) */
    for (i = 0; i < s->notes->n; i++) {
        const TextNote *o = &s->notes->v[i];
        RECT r = o->r, a;
        size_t bytes = (size_t)(r.right - r.left) * (size_t)(r.bottom - r.top) * (size_t)bpp;
        rect_move(&r, dx, dy);
        if (!rect_intersect(&a, &r, &want) || !rect_equal(&a, &r) || !note_valid(s, o) || !(v[n].bg = malloc(bytes)))
            continue;
        memcpy(v[n].bg, o->bg, bytes);
        v[n].r = r;
        v[n].clip = o->clip;
        rect_move(&v[n].clip, dx, dy);
        v[n].kind = o->kind;
        v[n].font = o->font;
        v[n].ch = o->ch;
        v[n].adv = o->adv;
        v[n].color = o->color;
        v[n].x = o->x + dx;
        v[n].y = o->y + dy;
        n++;
    }
    for (i = 0; i < n; i++) {
        TextNote *t;
        if (!rect_intersect(&v[i].clip, &v[i].clip, &want) || !(t = notes_add(d))) {
            free(v[i].bg);
            continue;
        }
        *t = v[i];
        t->hash = note_hash(d, &t->r);
    }
    free(v);
}

/* ---- the screen ---- */

/* plat_compose: the screen's notes are those of the background and the
   windows shown, moved to where they show; those another window covers
   are found by their fingerprints on the screen (notes_compose_end). */
void notes_compose_begin(void)
{
    notes_free(screen);
}

void notes_compose_surface(Bitmap *s, int dx, int dy)
{
    int i;
    if (!plat_sharp_text || !s->notes || s->bpp != 32)
        return;
    for (i = s->notes->n - 1; i >= 0; i--)
        if (!note_valid(s, &s->notes->v[i]))
            notes_remove(s, i);
    for (i = 0; i < s->notes->n; i++) {
        const TextNote *o = &s->notes->v[i];
        TextNote *n;
        RECT r = o->r, all = {0, 0, 0, 0};
        size_t bytes = (size_t)(r.right - r.left) * (size_t)(r.bottom - r.top) * 4;
        rect_move(&r, dx, dy);
        all.right = screen->w;
        all.bottom = screen->h;
        {
            RECT a;
            if (!rect_intersect(&a, &r, &all) || !rect_equal(&a, &r))
                continue;
        }
        n = notes_add(screen);
        if (!n)
            return;
        *n = *o;
        n->bg = malloc(bytes);
        if (!n->bg) {
            screen->notes->n--;
            return;
        }
        memcpy(n->bg, o->bg, bytes);
        n->r = r;
        rect_move(&n->clip, dx, dy);
        n->x += dx;
        n->y += dy;
    }
}

void notes_compose_end(void)
{
    int i;
    if (!screen->notes)
        return;
    for (i = screen->notes->n - 1; i >= 0; i--)
        if (!note_valid(screen, &screen->notes->v[i]))
            notes_remove(screen, i);
}

/* After the colour correction (X35): the notes' pixels and colours as
   shown. */
void notes_compose_lut(void)
{
    int i;
    if (!screen->notes)
        return;
    for (i = 0; i < screen->notes->n; i++) {
        TextNote *n = &screen->notes->v[i];
        if (plat_color_lut_on) {
            size_t k, count = (size_t)(n->r.right - n->r.left) * (size_t)(n->r.bottom - n->r.top);
            DWORD *p = (DWORD *)n->bg, c = n->color;
            for (k = 0; k < count; k++)
                p[k] = (p[k] & 0xff000000u) | ((DWORD)plat_color_lut[(p[k] >> 16) & 0xff] << 16) |
                       ((DWORD)plat_color_lut[(p[k] >> 8) & 0xff] << 8) | plat_color_lut[p[k] & 0xff];
            n->color = ((DWORD)plat_color_lut[(c >> 16) & 0xff] << 16) | ((DWORD)plat_color_lut[(c >> 8) & 0xff] << 8) |
                       plat_color_lut[c & 0xff];
        }
        n->hash = note_hash(screen, &n->r);
    }
}

/* The screen, its noted text taken off (the pixels it covered), to the
   host with the notes, which it draws over it at its own resolution. */
int sharp_present(void)
{
    static DWORD *clean;
    static size_t clean_size;
    static HostText *texts;
    static int texts_cap;
    TextNotes *ns;
    size_t size;
    int i, y, n = 0;
    if (!plat_sharp_text || !screen->notes || !screen->notes->n || host_text_scale() < 1)
        return 0;
    ns = screen->notes;
    for (i = ns->n - 1; i >= 0; i--)
        if (!note_valid(screen, &ns->v[i]))
            notes_remove(screen, i);
    size = (size_t)screen->stride * (size_t)screen->h;
    if (size > clean_size) {
        free(clean);
        clean = malloc(size);
        clean_size = clean ? size : 0;
        if (!clean)
            return 0;
    }
    if (ns->n > texts_cap) {
        HostText *t = realloc(texts, (size_t)ns->n * sizeof *t);
        if (!t)
            return 0;
        texts = t;
        texts_cap = ns->n;
    }
    memcpy(clean, screen->bits, size);
    for (i = 0; i < ns->n; i++) {
        const TextNote *o = &ns->v[i];
        int w = (int)(o->r.right - o->r.left);
        HostText *t = &texts[n++];
        for (y = o->r.top; y < o->r.bottom; y++)
            memcpy((unsigned char *)clean + (size_t)y * screen->stride + (size_t)o->r.left * 4,
                   o->bg + (size_t)(y - o->r.top) * w * 4, (size_t)w * 4);
        if (o->kind == 0 && o->font >= 0 && !fonts[o->font].sent) {
            host_text_font(o->font, fonts[o->font].name, fonts[o->font].height, fonts[o->font].weight,
                           fonts[o->font].italic, fonts[o->font].pitch);
            fonts[o->font].sent = 1;
        }
        t->kind = o->kind;
        t->font = o->font;
        t->ch = o->ch;
        t->color = (int32_t)o->color;
        t->x = o->x;
        t->y = o->y;
        t->adv = o->adv;
        if (o->kind == 1) {
            t->left = o->r.left;
            t->top = o->r.top;
            t->right = o->r.right;
            t->bottom = o->r.bottom;
        } else {
            t->left = o->clip.left;
            t->top = o->clip.top;
            t->right = o->clip.right;
            t->bottom = o->clip.bottom;
        }
    }
    host_present_text(clean, screen->stride, texts, n);
    return 1;
}
