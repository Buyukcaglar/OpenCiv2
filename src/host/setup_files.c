/*
 * Finding, checking and copying the game's files (setup.h).
 *
 * The source is walked whole: folders (and their sub-folders), archives
 * (libarchive: zip, 7z, rar), CD images (.cue with its .bin, .iso, a .bin
 * alone; read here as ISO 9660, the audio tracks as the music) and the CD's
 * InstallShield cabinet (libunshield), each found inside another as deep as
 * it goes.  A file is a candidate when its name is one of the manifest's;
 * it is the manifest's file when its size and SHA-256 are.  Files inside
 * an archive or a cabinet are unpacked into a temporary folder first (only
 * the candidates and the containers); those in a CD image are read from it
 * where they are.
 *
 * Paths are UTF-8: the program's manifest makes UTF-8 the process code
 * page, so the C runtime's file functions take them as they are.
 */
#include <windows.h>
#include <ctype.h>
#include <errno.h>
#include <direct.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#ifndef LIBARCHIVE_STATIC
#define LIBARCHIVE_STATIC
#endif
#include <archive.h>
#include <archive_entry.h>
#include <libunshield.h>
#include <lzma.h>
#include "setup.h"
#include "sha256.h"

#define MAX_DEPTH 16            /* containers in containers, folders in folders */
#define CHUNK (1 << 20)
#define RAW 2352                /* bytes of a raw CD sector */
#define ARROW " \xe2\x80\xba "  /* between a container and what is in it, in reports */

/* ---- strings ---- */

typedef struct Buf { char *s; size_t n, cap; } Buf;

static void buf_add(Buf *b, const char *fmt, ...)
{
    va_list ap;
    int n;
    for (;;) {
        size_t room = b->cap - b->n;
        va_start(ap, fmt);
        n = vsnprintf(b->s ? b->s + b->n : NULL, b->s ? room : 0, fmt, ap);
        va_end(ap);
        if (n < 0)
            return;
        if (b->s && (size_t)n < room) {
            b->n += (size_t)n;
            return;
        }
        b->cap = (b->cap + (size_t)n + 1) * 2;
        b->s = realloc(b->s, b->cap);
        if (!b->s)
            abort();
    }
}

static char *xstrdup(const char *s)
{
    char *d = strdup(s ? s : "");
    if (!d)
        abort();
    return d;
}

static char *join(const char *a, const char *sep, const char *b)
{
    Buf r = {0};
    buf_add(&r, "%s%s%s", a, *a ? sep : "", b);
    return r.s;
}

static const char *base_name(const char *p)
{
    const char *b = p, *s;
    for (s = p; *s; s++)
        if (*s == '/' || *s == '\\')
            b = s + 1;
    return b;
}

static int ext_is(const char *p, const char *ext)
{
    const char *b = base_name(p), *dot = strrchr(b, '.');
    return dot && !_stricmp(dot + 1, ext);
}

static int is_archive(const char *p)
{
    return ext_is(p, "zip") || ext_is(p, "7z") || ext_is(p, "rar");
}

/* "Track02.wav" (any case): the CD's audio track 2 as tools/extract_disc.py
   names it; the track number, else 0. */
static int music_track(const char *name)
{
    const char *b = base_name(name);
    if (_strnicmp(b, "track", 5) || !isdigit((unsigned char)b[5]) || !isdigit((unsigned char)b[6]) ||
        _stricmp(b + 7, ".wav"))
        return 0;
    return (b[5] - '0') * 10 + (b[6] - '0');
}

static void human_size(char *out, size_t n, uint64_t v)
{
    char digits[32], *d = out;
    int len, i;
    snprintf(digits, sizeof digits, "%llu", (unsigned long long)v);
    len = (int)strlen(digits);
    for (i = 0; i < len && (size_t)(d - out) + 2 < n; i++) {
        *d++ = digits[i];
        if ((len - i - 1) % 3 == 0 && i < len - 1)
            *d++ = ',';
    }
    *d = 0;
}

/* ---- files ---- */

static int is_dir(const char *p)
{
    DWORD a = GetFileAttributesA(p);
    return a != INVALID_FILE_ATTRIBUTES && (a & FILE_ATTRIBUTE_DIRECTORY);
}

static int64_t file_size(const char *p)
{
    struct _stat64 st;
    return _stat64(p, &st) ? -1 : (int64_t)st.st_size;
}

static int make_dirs(const char *path)
{
    char *p = xstrdup(path), *s;
    int ok;
    for (s = p; *s; s++)
        if ((*s == '/' || *s == '\\') && s > p && s[-1] != ':') {
            char c = *s;
            *s = 0;
            if (!is_dir(p))
                _mkdir(p);
            *s = c;
        }
    ok = is_dir(p) || _mkdir(p) == 0;
    free(p);
    return ok;
}

/* Remove a folder and what is in it (not following links). */
static void remove_tree(const char *dir)
{
    WIN32_FIND_DATAA fd;
    char *pat = join(dir, "\\", "*");
    HANDLE h = FindFirstFileA(pat, &fd);
    free(pat);
    if (h != INVALID_HANDLE_VALUE) {
        do {
            char *p;
            if (!strcmp(fd.cFileName, ".") || !strcmp(fd.cFileName, ".."))
                continue;
            p = join(dir, "\\", fd.cFileName);
            if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !(fd.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT))
                remove_tree(p);
            else if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                RemoveDirectoryA(p);
            else {
                SetFileAttributesA(p, FILE_ATTRIBUTE_NORMAL);
                DeleteFileA(p);
            }
            free(p);
        } while (FindNextFileA(h, &fd));
        FindClose(h);
    }
    RemoveDirectoryA(dir);
}

/* ---- the job ---- */

enum { SRC_FILE, SRC_IMAGE, SRC_CDDA };

typedef struct Src {
    int kind;
    char *path;                 /* the file; or the CD image holding it */
    uint64_t size;              /* its bytes (SRC_CDDA: of the WAV made of it) */
    uint64_t base;              /* SRC_IMAGE: byte offset of the track's first sector */
    uint32_t sector, data;      /* bytes per sector, offset of the 2048 data bytes */
    uint32_t extent;            /* first sector of the file in the track */
    uint64_t first;             /* SRC_CDDA: byte offset of the audio */
    char *origin;               /* where it was found, for the report */
    char sha[65];
} Src;

typedef struct Mismatch {
    char *name;                 /* lowercase */
    char *origin;
    uint64_t size;
    char sha[65];               /* "" when the size alone differed */
} Mismatch;

typedef struct Job {
    const SetupProgress *p;
    char *tmp;                  /* the temporary folder (made when first needed) */
    int tmp_n;
    const char **names;         /* the manifest's lowercase file names */
    Src **found;                /* per manifest entry: the file that is it */
    Src **srcs;                 /* all kept, to free */
    int nsrcs, capsrcs;
    Mismatch *mm;
    int nmm, capmm;
    Src *music[100];
    Buf notes;                  /* what could not be read */
    int depth, cancelled;
    char *error;                /* a failure that ends the import (I/O) */
    uint64_t copy_total, copy_done;
} Job;

static void status(Job *j, const char *what, const char *detail)
{
    if (j->p && j->p->status)
        j->p->status(j->p->user, what, detail ? detail : "");
}

static void fraction(Job *j, double f)
{
    if (j->p && j->p->fraction)
        j->p->fraction(j->p->user, f);
}

static int stop(Job *j)
{
    if (!j->cancelled && j->p && j->p->cancelled && j->p->cancelled(j->p->user))
        j->cancelled = 1;
    return j->cancelled || j->error;
}

static void note(Job *j, const char *fmt, ...)
{
    char line[2048];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(line, sizeof line, fmt, ap);
    va_end(ap);
    buf_add(&j->notes, "  %s\n", line);
}

/* A new folder in the temporary one. */
static char *temp_dir(Job *j, const char *kind)
{
    char name[64], *d;
    if (!j->tmp) {
        char t[MAX_PATH + 1];
        DWORD n = GetTempPathA(sizeof t, t);
        if (!n || n > MAX_PATH)
            snprintf(t, sizeof t, ".\\");
        snprintf(name, sizeof name, "Civ2RE-setup-%lu-%lu", (unsigned long)GetCurrentProcessId(),
                 (unsigned long)GetTickCount());
        j->tmp = join(t, "", name);
        if (!make_dirs(j->tmp)) {
            j->error = join("cannot make the temporary folder ", "", j->tmp);
            return NULL;
        }
    }
    snprintf(name, sizeof name, "%s%d", kind, ++j->tmp_n);
    d = join(j->tmp, "\\", name);
    if (!make_dirs(d)) {
        j->error = join("cannot make the temporary folder ", "", d);
        free(d);
        return NULL;
    }
    return d;
}

static Src *src_new(Job *j, int kind, const char *path, uint64_t size, const char *origin)
{
    Src *s = calloc(1, sizeof *s);
    if (!s)
        abort();
    s->kind = kind;
    s->path = xstrdup(path);
    s->size = size;
    s->origin = xstrdup(origin);
    if (j->nsrcs == j->capsrcs) {
        j->capsrcs = j->capsrcs ? j->capsrcs * 2 : 256;
        j->srcs = realloc(j->srcs, (size_t)j->capsrcs * sizeof *j->srcs);
        if (!j->srcs)
            abort();
    }
    j->srcs[j->nsrcs++] = s;
    return s;
}

/* ---- reading a source ---- */

typedef int (*Sink)(void *user, const void *data, size_t n);

static void put_le(uint8_t *p, uint32_t v, int n)
{
    int i;
    for (i = 0; i < n; i++)
        p[i] = (uint8_t)(v >> (8 * i));
}

static void counted(Job *j, size_t n, int counting)
{
    if (counting) {
        j->copy_done += n;
        fraction(j, j->copy_total ? (double)j->copy_done / (double)j->copy_total : -1);
    }
}

/* The source's bytes to sink (counted into copy_done if counting). */
static int src_read(Job *j, Src *s, Sink sink, void *user, int counting)
{
    FILE *f = fopen(s->path, "rb");
    uint8_t *buf;
    uint64_t left = s->size;
    int ok = 1;
    if (!f) {
        note(j, "cannot open %s: %s", s->origin, strerror(errno));
        return 0;
    }
    if (!(buf = malloc(CHUNK)))
        abort();
    if (s->kind == SRC_FILE) {
        while (ok && left) {
            size_t n = fread(buf, 1, left < CHUNK ? (size_t)left : CHUNK, f);
            if (!n) {
                note(j, "cannot read %s", s->origin);
                ok = 0;
                break;
            }
            ok = sink(user, buf, n);
            left -= n;
            counted(j, n, counting);
            if (stop(j))
                ok = 0;
        }
    } else if (s->kind == SRC_IMAGE) {
        /* 2048 data bytes a sector, out of the raw sectors where they are raw */
        uint64_t sec = s->extent;
        size_t per = CHUNK / 2048;
        uint8_t *raw = s->sector == 2048 ? NULL : malloc((size_t)s->sector * per);
        while (ok && left) {
            size_t want = (size_t)((left + 2047) / 2048), i, got, n;
            if (want > per)
                want = per;
            if (_fseeki64(f, (int64_t)(s->base + sec * s->sector), SEEK_SET)) {
                ok = 0;
                break;
            }
            if (!raw) {
                got = fread(buf, 2048, want, f);
            } else {
                got = fread(raw, s->sector, want, f);
                for (i = 0; i < got; i++)
                    memcpy(buf + i * 2048, raw + i * s->sector + s->data, 2048);
            }
            if (!got) {
                note(j, "cannot read %s (the image ends early)", s->origin);
                ok = 0;
                break;
            }
            n = got * 2048 < left ? got * 2048 : (size_t)left;
            ok = sink(user, buf, n);
            left -= n;
            sec += got;
            counted(j, n, counting);
            if (stop(j))
                ok = 0;
        }
        free(raw);
    } else {
        /* CD audio: 44.1 kHz 16-bit stereo, as a WAV file */
        uint8_t h[44];
        uint32_t data = (uint32_t)(s->size - 44);
        memcpy(h, "RIFF", 4);
        put_le(h + 4, 36 + data, 4);
        memcpy(h + 8, "WAVEfmt ", 8);
        put_le(h + 16, 16, 4);
        put_le(h + 20, 1, 2);
        put_le(h + 22, 2, 2);
        put_le(h + 24, 44100, 4);
        put_le(h + 28, 44100 * 4, 4);
        put_le(h + 32, 4, 2);
        put_le(h + 34, 16, 2);
        memcpy(h + 36, "data", 4);
        put_le(h + 40, data, 4);
        ok = sink(user, h, 44);
        left -= 44;
        if (ok && _fseeki64(f, (int64_t)s->first, SEEK_SET))
            ok = 0;
        while (ok && left) {
            size_t n = fread(buf, 1, left < CHUNK ? (size_t)left : CHUNK, f);
            if (!n) {
                ok = 0;
                break;
            }
            ok = sink(user, buf, n);
            left -= n;
            counted(j, n, counting);
            if (stop(j))
                ok = 0;
        }
    }
    free(buf);
    fclose(f);
    return ok;
}

static int hash_sink(void *user, const void *data, size_t n)
{
    sha256_update(user, data, n);
    return 1;
}

static int src_hash(Job *j, Src *s)
{
    Sha256 h;
    if (s->sha[0])
        return 1;
    sha256_init(&h);
    if (!src_read(j, s, hash_sink, &h, 0))
        return 0;
    sha256_final_hex(&h, s->sha);
    return 1;
}

/* ---- matching ---- */

static void mismatch(Job *j, const char *lname, const Src *s)
{
    Mismatch *m;
    if (j->nmm == j->capmm) {
        j->capmm = j->capmm ? j->capmm * 2 : 64;
        j->mm = realloc(j->mm, (size_t)j->capmm * sizeof *j->mm);
        if (!j->mm)
            abort();
    }
    m = &j->mm[j->nmm++];
    m->name = xstrdup(lname);
    m->origin = xstrdup(s->origin);
    m->size = s->size;
    memcpy(m->sha, s->sha, sizeof m->sha);
}

/* Music: a WAV file of CD audio (44.1 kHz, 16-bit stereo PCM). */
static int cd_audio_wav(const char *path)
{
    uint8_t h[44];
    FILE *f = fopen(path, "rb");
    int ok;
    if (!f)
        return 0;
    ok = fread(h, 1, 44, f) == 44 && !memcmp(h, "RIFF", 4) && !memcmp(h + 8, "WAVEfmt ", 8) && h[20] == 1 &&
         h[22] == 2 && h[24] == 0x44 && h[25] == 0xac && h[34] == 16;
    fclose(f);
    return ok;
}

/* A file found: the manifest's if its name, size and SHA-256 are one of
   its files', the music if it is a CD track. */
static void offer(Job *j, Src *s, const char *name)
{
    char lname[MAX_PATH];
    int i, named = 0, sized = 0, wanted = 0, track;
    size_t k;
    snprintf(lname, sizeof lname, "%s", base_name(name));
    for (k = 0; lname[k]; k++)
        lname[k] = (char)tolower((unsigned char)lname[k]);
    if ((track = music_track(lname)) != 0) {
        if (!j->music[track] && (s->kind == SRC_CDDA || cd_audio_wav(s->path)))
            j->music[track] = s;
        return;
    }
    for (i = 0; i < setup_manifest_count; i++)
        if (!strcmp(j->names[i], lname)) {
            named = 1;
            if (setup_manifest[i].size == s->size) {
                sized = 1;
                if (!j->found[i])
                    wanted = 1;
            }
        }
    if (!named)
        return;
    if (!wanted) {
        /* of a size no file of the name has: a different file (reported if
           the manifest's stays unfound); else one already found again */
        if (!sized)
            mismatch(j, lname, s);
        return;
    }
    status(j, "Checking", s->origin);
    if (!src_hash(j, s))
        return;
    wanted = 0;
    for (i = 0; i < setup_manifest_count; i++)
        if (!strcmp(j->names[i], lname) && setup_manifest[i].size == s->size &&
            !strcmp(setup_manifest[i].sha256, s->sha) && !j->found[i]) {
            j->found[i] = s;
            wanted = 1;
        }
    if (!wanted)
        mismatch(j, lname, s);
}

/* Whether a name inside a container is worth unpacking. */
static int interesting(Job *j, const char *name)
{
    const char *b = base_name(name);
    int i;
    static const char *const containers[] = {"zip", "7z", "rar", "cue", "bin", "iso", "img", "cab", "hdr"};
    for (i = 0; i < (int)(sizeof containers / sizeof containers[0]); i++)
        if (ext_is(b, containers[i]))
            return 1;
    if (music_track(b))
        return 1;
    for (i = 0; i < setup_manifest_count; i++)
        if (!_stricmp(j->names[i], b))
            return 1;
    return 0;
}

/* sep: between origin and the names in it, if path is a folder (a
   backslash in the user's folders; in an unpacked archive ARROW, then a
   slash) */
static void scan_path(Job *j, const char *path, const char *origin, const char *sep);

/* ---- InstallShield cabinets ---- */

static void scan_cab(Job *j, const char *path, const char *origin)
{
    Unshield *u;
    char *out;
    int i, n;
    status(j, "Opening the installer's cabinet", origin);
    unshield_set_log_level(0);
    if (!(u = unshield_open(path))) {
        note(j, "%s: not an InstallShield cabinet that can be read", origin);
        return;
    }
    if (!(out = temp_dir(j, "cab"))) {
        unshield_close(u);
        return;
    }
    n = unshield_file_count(u);
    for (i = 0; i < n && !stop(j); i++) {
        const char *name = unshield_file_name(u, i), *dir;
        char prefix[32], *dst, *where, *in_cab, *t;
        int64_t size;
        if (!name || !unshield_file_is_valid(u, i) || !interesting(j, name))
            continue;
        dir = unshield_directory_name(u, unshield_file_directory(u, i));
        in_cab = join(dir ? dir : "", "\\", name);
        where = join(origin, ARROW, in_cab);
        free(in_cab);
        snprintf(prefix, sizeof prefix, "%d-", i);
        t = join(prefix, "", base_name(name));
        dst = join(out, "\\", t);
        free(t);
        status(j, "Unpacking", where);
        if (!unshield_file_save(u, i, dst) || (size = file_size(dst)) < 0) {
            note(j, "%s: could not be unpacked", where);
        } else if (is_archive(name)) {
            scan_path(j, dst, where, "/");
        } else {
            offer(j, src_new(j, SRC_FILE, dst, (uint64_t)size, where), name);
        }
        free(dst);
        free(where);
    }
    unshield_close(u);
    free(out);
}

/* ---- ISO 9660 ---- */

typedef struct Iso {
    Job *j;
    const char *image, *origin;
    FILE *f;
    uint64_t base;
    uint32_t sector, data;
    uint32_t seen[512];         /* directory extents walked (loops) */
    int nseen;
} Iso;

static int iso_read(Iso *iso, uint32_t lba, uint32_t count, uint8_t *out)
{
    uint32_t i;
    for (i = 0; i < count; i++) {
        if (_fseeki64(iso->f, (int64_t)(iso->base + (uint64_t)(lba + i) * iso->sector + iso->data), SEEK_SET) ||
            fread(out + (size_t)i * 2048, 1, 2048, iso->f) != 2048)
            return 0;
    }
    return 1;
}

static uint32_t le32(const uint8_t *p) { return p[0] | p[1] << 8 | p[2] << 16 | (uint32_t)p[3] << 24; }

static int file_sink(void *user, const void *data, size_t n)
{
    return fwrite(data, 1, n, user) == n;
}

/* An extent of the image unpacked into a file. */
static int iso_extract_file(Iso *iso, uint32_t extent, uint32_t size, const char *dst)
{
    Src tmp;
    FILE *out = fopen(dst, "wb");
    int ok;
    if (!out)
        return 0;
    memset(&tmp, 0, sizeof tmp);
    tmp.kind = SRC_IMAGE;
    tmp.path = (char *)iso->image;
    tmp.origin = (char *)iso->origin;
    tmp.size = size;
    tmp.base = iso->base;
    tmp.sector = iso->sector;
    tmp.data = iso->data;
    tmp.extent = extent;
    ok = src_read(iso->j, &tmp, file_sink, out, 0);
    if (fclose(out))
        ok = 0;
    return ok;
}

typedef struct IsoEntry { char name[256]; uint32_t extent, size; int dir; } IsoEntry;

static int iso_list(Iso *iso, uint32_t extent, uint32_t size, IsoEntry **out)
{
    uint32_t n = (size + 2047) / 2048, i = 0;
    uint8_t *d;
    int count = 0, cap = 0;
    IsoEntry *e = NULL;
    if (n > 4096 || !(d = malloc((size_t)n * 2048)))
        return -1;
    if (!iso_read(iso, extent, n, d)) {
        free(d);
        return -1;
    }
    while (i < size) {
        uint8_t len = d[i];
        const uint8_t *r;
        uint8_t nl;
        if (!len) {
            i = (i / 2048 + 1) * 2048;
            continue;
        }
        if (i + len > n * 2048 || len < 34)
            break;
        r = d + i;
        nl = r[32];
        if (!(nl == 1 && (r[33] == 0 || r[33] == 1)) && 33u + nl <= len) {
            IsoEntry *x;
            char *semi;
            if (count == cap) {
                cap = cap ? cap * 2 : 64;
                e = realloc(e, (size_t)cap * sizeof *e);
                if (!e)
                    abort();
            }
            x = &e[count++];
            memcpy(x->name, r + 33, nl);
            x->name[nl] = 0;
            if ((semi = strchr(x->name, ';')))
                *semi = 0;
            if (*x->name && x->name[strlen(x->name) - 1] == '.')
                x->name[strlen(x->name) - 1] = 0;
            x->extent = le32(r + 2);
            x->size = le32(r + 10);
            x->dir = (r[25] & 2) != 0;
        }
        i += len;
    }
    free(d);
    *out = e;
    return count;
}

static void iso_walk(Iso *iso, uint32_t extent, uint32_t size, const char *path, int depth)
{
    Job *j = iso->j;
    IsoEntry *e = NULL;
    int n, i, cab = -1;
    if (depth > MAX_DEPTH || iso->nseen >= (int)(sizeof iso->seen / sizeof iso->seen[0]))
        return;
    for (i = 0; i < iso->nseen; i++)
        if (iso->seen[i] == extent)
            return;
    iso->seen[iso->nseen++] = extent;
    if ((n = iso_list(iso, extent, size, &e)) < 0) {
        note(j, "%s: a folder of the CD image cannot be read (%s)", iso->origin, *path ? path : "/");
        return;
    }
    for (i = 0; i < n; i++)
        if (!e[i].dir && (!_stricmp(e[i].name, "data1.hdr") || (cab < 0 && !_stricmp(e[i].name, "data1.cab"))))
            cab = i;
    if (cab >= 0) {
        /* the cabinet and its parts, unpacked side by side */
        char *out = temp_dir(j, "iso");
        if (out) {
            char *first = NULL;
            for (i = 0; i < n && !stop(j); i++)
                if (!e[i].dir && (ext_is(e[i].name, "cab") || ext_is(e[i].name, "hdr"))) {
                    char *dst = join(out, "\\", e[i].name);
                    status(j, "Reading the CD image", e[i].name);
                    if (!iso_extract_file(iso, e[i].extent, e[i].size, dst))
                        note(j, "%s: %s could not be read", iso->origin, e[i].name);
                    if (i == cab)
                        first = dst;
                    else
                        free(dst);
                }
            if (first && !stop(j)) {
                char *in_iso = join(path, "/", e[cab].name), *where = join(iso->origin, ARROW, in_iso);
                scan_cab(j, first, where);
                free(in_iso);
                free(where);
            }
            free(first);
            free(out);
        }
    }
    for (i = 0; i < n && !stop(j); i++) {
        char *p = join(path, "/", e[i].name);
        if (e[i].dir) {
            iso_walk(iso, e[i].extent, e[i].size, p, depth + 1);
        } else if (!ext_is(e[i].name, "cab") && !ext_is(e[i].name, "hdr") && interesting(j, e[i].name)) {
            char *where = join(iso->origin, ARROW, p);
            if (is_archive(e[i].name) || ext_is(e[i].name, "iso") || ext_is(e[i].name, "cue") ||
                ext_is(e[i].name, "bin") || ext_is(e[i].name, "img")) {
                /* a container on the CD: out of it first */
                char *out = temp_dir(j, "iso");
                if (out) {
                    char *dst = join(out, "\\", e[i].name);
                    if (iso_extract_file(iso, e[i].extent, e[i].size, dst))
                        scan_path(j, dst, where, "/");
                    free(dst);
                    free(out);
                }
            } else {
                Src *s = src_new(j, SRC_IMAGE, iso->image, e[i].size, where);
                s->base = iso->base;
                s->sector = iso->sector;
                s->data = iso->data;
                s->extent = e[i].extent;
                offer(j, s, e[i].name);
            }
            free(where);
        }
        free(p);
    }
    free(e);
}

/* An ISO 9660 file system in image at base (sector bytes per sector, the
   2048 data bytes at data). 0 if there is none. */
static int scan_iso(Job *j, const char *image, uint64_t base, uint32_t sector, uint32_t data, const char *origin)
{
    Iso iso;
    uint8_t pvd[2048];
    memset(&iso, 0, sizeof iso);
    iso.j = j;
    iso.image = image;
    iso.origin = origin;
    iso.base = base;
    iso.sector = sector;
    iso.data = data;
    if (!(iso.f = fopen(image, "rb")))
        return 0;
    if (!iso_read(&iso, 16, 1, pvd) || pvd[0] != 1 || memcmp(pvd + 1, "CD001", 5)) {
        fclose(iso.f);
        return 0;
    }
    status(j, "Reading the CD image", origin);
    iso_walk(&iso, le32(pvd + 156 + 2), le32(pvd + 156 + 10), "", 0);
    fclose(iso.f);
    return 1;
}

/* A CD image without a cue sheet (.iso, .img, .bin): which of the usual
   sector layouts has the ISO 9660 descriptor. */
static int scan_image(Job *j, const char *path, const char *origin)
{
    static const uint32_t layouts[][2] = {{2048, 0}, {RAW, 16}, {RAW, 24}, {2336, 8}};
    FILE *f = fopen(path, "rb");
    int i;
    if (!f)
        return 0;
    for (i = 0; i < 4; i++) {
        char id[6] = {0};
        if (!_fseeki64(f, (int64_t)16 * layouts[i][0] + layouts[i][1] + 1, SEEK_SET) && fread(id, 1, 5, f) == 5 &&
            !memcmp(id, "CD001", 5)) {
            fclose(f);
            return scan_iso(j, path, 0, layouts[i][0], layouts[i][1], origin);
        }
    }
    fclose(f);
    return 0;
}

/* ---- cue sheets ---- */

typedef struct Track { int number; char mode[16]; uint64_t index1; char *file; } Track;

/* The file a cue sheet names, beside it (any case; else the only .bin
   with the cue's name). */
static char *cue_file(const char *cue, const char *name)
{
    char *dir = xstrdup(cue), *p, *pat, stem[MAX_PATH], *dot;
    WIN32_FIND_DATAA fd;
    HANDLE h;
    *(char *)base_name(dir) = 0;
    p = join(dir, "", base_name(name));
    if (file_size(p) >= 0) {
        free(dir);
        return p;
    }
    free(p);
    p = NULL;
    pat = join(dir, "", "*.bin");
    snprintf(stem, sizeof stem, "%s", base_name(cue));
    if ((dot = strrchr(stem, '.')))
        *dot = 0;
    h = FindFirstFileA(pat, &fd);
    free(pat);
    if (h != INVALID_HANDLE_VALUE) {
        do {
            char fstem[MAX_PATH];
            snprintf(fstem, sizeof fstem, "%s", fd.cFileName);
            if ((dot = strrchr(fstem, '.')))
                *dot = 0;
            if (!_stricmp(fstem, stem) || !_stricmp(fd.cFileName, base_name(name))) {
                p = join(dir, "", fd.cFileName);
                break;
            }
        } while (FindNextFileA(h, &fd));
        FindClose(h);
    }
    free(dir);
    return p;
}

/* A cue sheet: its data track's file system, its audio tracks (the music).
   The .bin files it uses are added to *used (to be passed over). */
static void scan_cue(Job *j, const char *cue, const char *origin, char ***used, int *nused)
{
    FILE *f = fopen(cue, "r");
    char line[1024], *file = NULL;
    Track t[100];
    int n = 0, i;
    if (!f)
        return;
    while (fgets(line, sizeof line, f) && n < 99) {
        char *s = line, word[32];
        while (*s == ' ' || *s == '\t')
            s++;
        if (sscanf(s, "%31s", word) != 1)
            continue;
        if (!_stricmp(word, "FILE")) {
            char name[MAX_PATH], *q = strchr(s, '"'), *e;
            if (q && (e = strchr(q + 1, '"')))
                snprintf(name, sizeof name, "%.*s", (int)(e - q - 1), q + 1);
            else if (sscanf(s + 4, "%259s", name) != 1)
                continue;
            free(file);
            file = cue_file(cue, name);
            if (!file)
                note(j, "%s: names %s, which is not beside it", origin, name);
        } else if (!_stricmp(word, "TRACK") && file) {
            memset(&t[n], 0, sizeof t[n]);
            if (sscanf(s + 5, "%d %15s", &t[n].number, t[n].mode) == 2) {
                t[n].file = xstrdup(file);
                t[n].index1 = (uint64_t)-1;
                n++;
            }
        } else if (!_stricmp(word, "INDEX") && n) {
            int idx, m, sec, fr;
            if (sscanf(s + 5, "%d %d:%d:%d", &idx, &m, &sec, &fr) == 4 && idx == 1)
                t[n - 1].index1 = ((uint64_t)m * 60 + (uint64_t)sec) * 75 + (uint64_t)fr;
        }
    }
    fclose(f);
    free(file);
    for (i = 0; i < n && !stop(j); i++) {
        uint32_t sector = 0, off = 0;
        int k;
        if (t[i].index1 == (uint64_t)-1)
            continue;
        for (k = 0; k < *nused && _stricmp((*used)[k], t[i].file); k++)
            ;
        if (k == *nused) {
            *used = realloc(*used, (size_t)(*nused + 1) * sizeof **used);
            if (!*used)
                abort();
            (*used)[(*nused)++] = xstrdup(t[i].file);
        }
        if (!_stricmp(t[i].mode, "MODE1/2048")) {
            sector = 2048;
        } else if (!_stricmp(t[i].mode, "MODE1/2352")) {
            sector = RAW;
            off = 16;
        } else if (!_stricmp(t[i].mode, "MODE2/2352")) {
            sector = RAW;
            off = 24;
        } else if (!_stricmp(t[i].mode, "MODE2/2336")) {
            sector = 2336;
            off = 8;
        } else if (!_stricmp(t[i].mode, "AUDIO")) {
            /* the track's sectors: to the next track in its file, or the file's end */
            int64_t fsize = file_size(t[i].file);
            uint64_t end = fsize > 0 ? (uint64_t)fsize / RAW : 0;
            for (k = i + 1; k < n; k++)
                if (!_stricmp(t[k].file, t[i].file) && t[k].index1 != (uint64_t)-1) {
                    end = t[k].index1;
                    break;
                }
            if (end > t[i].index1 && t[i].number < 100) {
                char name[32], *where;
                Src *s;
                snprintf(name, sizeof name, "Track%02d.wav", t[i].number);
                snprintf(line, sizeof line, "audio track %d", t[i].number);
                where = join(origin, ARROW, line);
                s = src_new(j, SRC_CDDA, t[i].file, 44 + (end - t[i].index1) * RAW, where);
                s->first = t[i].index1 * RAW;
                offer(j, s, name);
                free(where);
            }
            continue;
        }
        if (sector) {
            char *where = join(origin, ARROW, base_name(t[i].file));
            if (!scan_iso(j, t[i].file, t[i].index1 * sector, sector, off, where))
                note(j, "%s: track %d has no ISO 9660 file system", origin, t[i].number);
            free(where);
        }
    }
    for (i = 0; i < n; i++)
        free(t[i].file);
}

/* ---- archives ---- */

/* A name inside an archive as a relative path that stays inside the
   folder it is unpacked into ("" if there is nothing left of it). */
static char *safe_relative(const char *name)
{
    Buf r = {0};
    const char *s = name;
    buf_add(&r, "%s", "");
    while (*s) {
        const char *e = s;
        size_t len;
        while (*e && *e != '/' && *e != '\\')
            e++;
        len = (size_t)(e - s);
        if (len && !(len == 1 && s[0] == '.') && !(len == 2 && s[0] == '.' && s[1] == '.') && !memchr(s, ':', len)) {
            char part[256];
            size_t k;
            snprintf(part, sizeof part, "%.*s", (int)(len < 200 ? len : 200), s);
            for (k = 0; part[k]; k++)
                if (strchr("<>\"|?*", part[k]) || (unsigned char)part[k] < 32)
                    part[k] = '_';
            buf_add(&r, "%s%s", r.n ? "\\" : "", part);
        }
        s = *e ? e + 1 : e;
    }
    return r.s;
}

static void scan_archive(Job *j, const char *path, const char *origin)
{
    struct archive *a = archive_read_new();
    struct archive_entry *e;
    char *out = NULL;
    int r, any = 0;
    archive_read_support_filter_all(a);
    archive_read_support_format_all(a);
    status(j, "Reading the archive", origin);
    if (archive_read_open_filename(a, path, 1 << 16) != ARCHIVE_OK) {
        note(j, "%s: cannot be read as an archive (%s)", origin, archive_error_string(a));
        archive_read_free(a);
        return;
    }
    while (!stop(j) && (r = archive_read_next_header(a, &e)) != ARCHIVE_EOF) {
        const char *name;
        char *rel, *dst, *where, *dir;
        FILE *f;
        if (r == ARCHIVE_FATAL) {
            note(j, "%s: %s", origin, archive_error_string(a));
            break;
        }
        name = archive_entry_pathname_utf8(e);
        if (!name)
            name = archive_entry_pathname(e);
        if (!name || archive_entry_filetype(e) != AE_IFREG || !interesting(j, name))
            continue;
        if (archive_entry_is_encrypted(e)) {
            note(j, "%s" ARROW "%s: encrypted, passed over", origin, name);
            continue;
        }
        if (!out && !(out = temp_dir(j, "arc")))
            break;
        rel = safe_relative(name);
        if (!*rel) {
            free(rel);
            continue;
        }
        dst = join(out, "\\", rel);
        where = join(origin, ARROW, name);
        status(j, "Unpacking", where);
        dir = xstrdup(dst);
        *(char *)base_name(dir) = 0;
        make_dirs(dir);
        free(dir);
        if (!(f = fopen(dst, "wb"))) {
            note(j, "%s: cannot be unpacked (%s)", where, strerror(errno));
        } else {
            const void *block;
            size_t size;
            la_int64_t offset, at = 0;
            int ok = 1;
            while ((r = archive_read_data_block(a, &block, &size, &offset)) == ARCHIVE_OK) {
                if (offset > at) {          /* a sparse gap */
                    _fseeki64(f, offset, SEEK_SET);
                    at = offset;
                }
                if (fwrite(block, 1, size, f) != size) {
                    ok = 0;
                    break;
                }
                at += (la_int64_t)size;
                if (stop(j)) {
                    ok = 0;
                    break;
                }
            }
            if (r != ARCHIVE_EOF && ok) {
                note(j, "%s: %s", where, archive_error_string(a));
                ok = 0;
            }
            if (fclose(f))
                ok = 0;
            if (!ok)
                remove(dst);
            else
                any = 1;
        }
        free(rel);
        free(dst);
        free(where);
    }
    archive_read_free(a);
    if (any && !stop(j))
        scan_path(j, out, origin, ARROW);   /* what was unpacked, as a folder (cue sheets beside their .bin) */
    free(out);
}

/* ---- folders ---- */

typedef struct DirEntry { char *name; int dir; } DirEntry;

static int cmp_entry(const void *a, const void *b)
{
    return _stricmp(((const DirEntry *)a)->name, ((const DirEntry *)b)->name);
}

static void scan_dir(Job *j, const char *dir, const char *origin, const char *sep)
{
    const char *next = strcmp(sep, "\\") ? "/" : "\\";
    WIN32_FIND_DATAA fd;
    DirEntry *e = NULL;
    int n = 0, cap = 0, i, cab = -1, nused = 0;
    char **used = NULL, *pat = join(dir, "\\", "*");
    HANDLE h = FindFirstFileA(pat, &fd);
    free(pat);
    if (h == INVALID_HANDLE_VALUE) {
        note(j, "%s: cannot be listed", origin);
        return;
    }
    do {
        if (!strcmp(fd.cFileName, ".") || !strcmp(fd.cFileName, "..") ||
            (fd.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT))
            continue;
        if (n == cap) {
            cap = cap ? cap * 2 : 64;
            e = realloc(e, (size_t)cap * sizeof *e);
            if (!e)
                abort();
        }
        e[n].name = xstrdup(fd.cFileName);
        e[n].dir = (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
        n++;
    } while (FindNextFileA(h, &fd));
    FindClose(h);
    qsort(e, (size_t)n, sizeof *e, cmp_entry);
    status(j, "Looking through", origin);
    /* the CD's cabinet, if this is (a copy of) the CD */
    for (i = 0; i < n; i++)
        if (!e[i].dir && (!_stricmp(e[i].name, "data1.hdr") || (cab < 0 && !_stricmp(e[i].name, "data1.cab"))))
            cab = i;
    if (cab >= 0) {
        char *p = join(dir, "\\", e[cab].name), *where = join(origin, sep, e[cab].name);
        scan_cab(j, p, where);
        free(p);
        free(where);
    }
    /* cue sheets before the images they use */
    for (i = 0; i < n && !stop(j); i++)
        if (!e[i].dir && ext_is(e[i].name, "cue")) {
            char *p = join(dir, "\\", e[i].name), *where = join(origin, sep, e[i].name);
            scan_cue(j, p, where, &used, &nused);
            free(p);
            free(where);
        }
    for (i = 0; i < n && !stop(j); i++) {
        char *p = join(dir, "\\", e[i].name), *where = join(origin, sep, e[i].name);
        int k;
        if (e[i].dir) {
            scan_path(j, p, where, next);
        } else if (!ext_is(e[i].name, "cue") && !ext_is(e[i].name, "cab") && !ext_is(e[i].name, "hdr")) {
            for (k = 0; k < nused && _stricmp(used[k], p); k++)
                ;
            if (k == nused)
                scan_path(j, p, where, next);
        }
        free(p);
        free(where);
    }
    for (i = 0; i < nused; i++)
        free(used[i]);
    free(used);
    for (i = 0; i < n; i++)
        free(e[i].name);
    free(e);
}

/* Anything: a folder, an archive, a CD image, a cue sheet, a game file. */
static void scan_path(Job *j, const char *path, const char *origin, const char *sep)
{
    int64_t size;
    if (stop(j))
        return;
    if (j->depth >= MAX_DEPTH) {
        note(j, "%s: nested too deep, passed over", origin);
        return;
    }
    j->depth++;
    if (is_dir(path)) {
        scan_dir(j, path, origin, sep);
    } else if ((size = file_size(path)) < 0) {
        note(j, "%s: not found", origin);
    } else if (is_archive(path)) {
        scan_archive(j, path, origin);
    } else if (ext_is(path, "cue")) {
        char **used = NULL;
        int nused = 0, i;
        scan_cue(j, path, origin, &used, &nused);
        for (i = 0; i < nused; i++)
            free(used[i]);
        free(used);
    } else if (ext_is(path, "iso") || ext_is(path, "img") || ext_is(path, "bin")) {
        if (!scan_image(j, path, origin) && !ext_is(path, "bin"))
            note(j, "%s: not a CD image this can read (no ISO 9660 file system)", origin);
    } else if (ext_is(path, "cab") || ext_is(path, "hdr")) {
        scan_cab(j, path, origin);
    } else {
        offer(j, src_new(j, SRC_FILE, path, (uint64_t)size, origin), path);
    }
    j->depth--;
}

/* ---- copying ---- */

typedef struct CopyOut { FILE *f; Sha256 h; } CopyOut;

static int copy_sink(void *user, const void *data, size_t n)
{
    CopyOut *c = user;
    sha256_update(&c->h, data, n);
    return fwrite(data, 1, n, c->f) == n;
}

/* src into game_dir/rel; checked against sha (unless NULL) as written. */
static int copy_to(Job *j, Src *s, const char *game_dir, const char *rel, const char *sha)
{
    char *dst = join(game_dir, "\\", rel), *part, *k, *dir, hex[65];
    CopyOut c;
    int ok;
    for (k = dst; *k; k++)
        if (*k == '/')
            *k = '\\';
    part = join(dst, "", ".part");
    dir = xstrdup(dst);
    *(char *)base_name(dir) = 0;
    make_dirs(dir);
    free(dir);
    status(j, "Copying", rel);
    if (!(c.f = fopen(part, "wb"))) {
        j->error = join("cannot write ", "", part);
        free(dst);
        free(part);
        return 0;
    }
    sha256_init(&c.h);
    ok = src_read(j, s, copy_sink, &c, 1);
    if (fclose(c.f))
        ok = 0;
    sha256_final_hex(&c.h, hex);
    if (ok && sha && strcmp(hex, sha)) {
        note(j, "%s: changed while it was being copied", s->origin);
        ok = 0;
    }
    if (ok && !MoveFileExA(part, dst, MOVEFILE_REPLACE_EXISTING | MOVEFILE_COPY_ALLOWED)) {
        j->error = join("cannot write ", "", dst);
        ok = 0;
    }
    if (!ok)
        DeleteFileA(part);
    if (!ok && !j->error && !j->cancelled)
        j->error = join("cannot copy ", "", s->origin);
    free(dst);
    free(part);
    return ok;
}

/* ---- reports ---- */

static void report_file(Job *j, Buf *r, int i)
{
    const SetupFile *f = &setup_manifest[i];
    char size[32];
    int k, shown = 0;
    human_size(size, sizeof size, f->size);
    buf_add(r, "  %s\n    expected: %s bytes, SHA-256 %s\n", f->path, size, f->sha256);
    for (k = 0; k < j->nmm; k++)
        if (!strcmp(j->mm[k].name, j->names[i])) {
            char got[32];
            if (shown++ == 4) {
                buf_add(r, "    (and more)\n");
                break;
            }
            human_size(got, sizeof got, j->mm[k].size);
            if (j->mm[k].sha[0])
                buf_add(r, "    found:    %s\n              %s bytes, SHA-256 %s: not the same file\n", j->mm[k].origin,
                        got, j->mm[k].sha);
            else
                buf_add(r, "    found:    %s\n              %s bytes: not the same size\n", j->mm[k].origin, got);
        }
    if (!shown)
        buf_add(r, "    not found anywhere in the location\n");
}

static void free_job(Job *j)
{
    int i;
    for (i = 0; i < j->nsrcs; i++) {
        free(j->srcs[i]->path);
        free(j->srcs[i]->origin);
        free(j->srcs[i]);
    }
    for (i = 0; i < j->nmm; i++) {
        free(j->mm[i].name);
        free(j->mm[i].origin);
    }
    for (i = 0; i < setup_manifest_count; i++)
        free((char *)j->names[i]);
    free(j->srcs);
    free(j->mm);
    free(j->names);
    free(j->found);
    free(j->notes.s);
    free(j->error);
    if (j->tmp) {
        remove_tree(j->tmp);
        free(j->tmp);
    }
}

int setup_import(const char *source, const char *game_dir, const SetupProgress *p, char **report)
{
    Job j;
    Buf r = {0};
    int i, missing = 0, opt_missing = 0, copied = 0, music = 0, ok = 0;
    char *src = xstrdup(source);
    size_t len = strlen(src);
    while (len > 3 && (src[len - 1] == '\\' || src[len - 1] == '/'))
        src[--len] = 0;
    memset(&j, 0, sizeof j);
    j.p = p;
    j.names = calloc((size_t)setup_manifest_count, sizeof *j.names);
    j.found = calloc((size_t)setup_manifest_count, sizeof *j.found);
    if (!j.names || !j.found)
        abort();
    for (i = 0; i < setup_manifest_count; i++) {
        char *n = xstrdup(base_name(setup_manifest[i].path)), *k;
        for (k = n; *k; k++)
            *k = (char)tolower((unsigned char)*k);
        j.names[i] = n;
    }
    fraction(&j, -1);
    scan_path(&j, src, src, "\\");

    buf_add(&r, "Location: %s\n\n", src);
    if (j.cancelled) {
        buf_add(&r, "Cancelled.\n");
        goto done;
    }
    if (j.error) {
        buf_add(&r, "Stopped: %s.\n", j.error);
        goto done;
    }
    for (i = 0; i < setup_manifest_count; i++)
        if (!j.found[i]) {
            if (setup_manifest[i].flags & SETUP_REQUIRED)
                missing++;
            else
                opt_missing++;
        }
    if (missing) {
        int total = 0;
        for (i = 0; i < setup_manifest_count; i++)
            total += (setup_manifest[i].flags & SETUP_REQUIRED) != 0;
        buf_add(&r, "%d of the %d files the game needs could not be verified, so nothing was copied.\n"
                    "This program works with Civilization II Multiplayer Gold Edition (version 5.4.0f,\n"
                    "as on its CD).\n\n", missing, total);
        for (i = 0; i < setup_manifest_count; i++)
            if (!j.found[i] && (setup_manifest[i].flags & SETUP_REQUIRED))
                report_file(&j, &r, i);
        if (j.notes.n)
            buf_add(&r, "\nWhile looking:\n%s", j.notes.s);
        goto done;
    }
    /* everything there: copy */
    for (i = 0; i < setup_manifest_count; i++)
        if (j.found[i])
            j.copy_total += j.found[i]->size;
    for (i = 1; i < 100; i++)
        if (j.music[i])
            j.copy_total += j.music[i]->size;
    fraction(&j, 0);
    for (i = 0; i < setup_manifest_count && !stop(&j); i++)
        if (j.found[i] && copy_to(&j, j.found[i], game_dir, setup_manifest[i].path, setup_manifest[i].sha256))
            copied++;
    for (i = 1; i < 100 && !stop(&j); i++)
        if (j.music[i]) {
            char rel[32];
            snprintf(rel, sizeof rel, "Music\\Track%02d.wav", i);
            if (copy_to(&j, j.music[i], game_dir, rel, NULL))
                music++;
        }
    if (j.cancelled) {
        buf_add(&r, "Cancelled while copying: the game's folder is incomplete.\n");
        goto done;
    }
    if (j.error) {
        buf_add(&r, "Stopped while copying: %s.\n", j.error);
        goto done;
    }
    ok = 1;
    buf_add(&r, "Copied %d verified files into %s", copied, game_dir);
    if (music)
        buf_add(&r, ", and %d music tracks", music);
    buf_add(&r, ".\n");
    if (opt_missing) {
        buf_add(&r, "\n%d optional files (the CD's videos and heralds, the extra scenarios) were not found or\n"
                    "did not match; the game runs without them:\n", opt_missing);
        for (i = 0; i < setup_manifest_count; i++)
            if (!j.found[i] && (setup_manifest[i].flags & SETUP_OPTIONAL))
                buf_add(&r, "  %s\n", setup_manifest[i].path);
    }
    if (!music)
        buf_add(&r, "\nNo music: it comes from the CD's audio tracks (a .cue/.bin image).\n");
    if (j.notes.n)
        buf_add(&r, "\nWhile looking:\n%s", j.notes.s);
done:
    if (ok) {
        /* what was done, beside the game */
        char *log = join(game_dir, "\\", "Civ2RE-setup.txt");
        FILE *f = fopen(log, "w");
        if (f) {
            fputs(r.s, f);
            fclose(f);
        }
        free(log);
    }
    free_job(&j);
    free(src);
    *report = r.s;
    return ok;
}

int setup_check(const char *game_dir, char **report)
{
    Buf r = {0};
    int i, bad = 0;
    for (i = 0; i < setup_manifest_count; i++) {
        char *p;
        int64_t size;
        if (!(setup_manifest[i].flags & SETUP_REQUIRED))
            continue;
        p = join(game_dir, "\\", setup_manifest[i].path);
        size = file_size(p);
        if (size != (int64_t)setup_manifest[i].size) {
            if (bad++ < 20)
                buf_add(&r, "  %s: %s\n", setup_manifest[i].path, size < 0 ? "missing" : "not the right size");
        }
        free(p);
    }
    if (bad > 20)
        buf_add(&r, "  (and %d more)\n", bad - 20);
    *report = bad ? r.s : NULL;
    if (!bad)
        free(r.s);
    return !bad;
}

/* ---- the program's own files ---- */

/* An RCDATA resource of the program: 8 bytes of size, then that many
   bytes xz-compressed (tools/build_port.py).  Written to dst unless it is
   there (keep_existing) or there with that size. */
static int write_resource(int id, const char *dst, int keep_existing, char **error)
{
    HRSRC res = FindResourceA(NULL, MAKEINTRESOURCEA(id), MAKEINTRESOURCEA(10) /* RT_RCDATA */);
    HGLOBAL g;
    const uint8_t *d;
    DWORD n;
    uint64_t size = 0;
    int64_t have = file_size(dst);
    uint8_t *out;
    size_t in_pos = 0, out_pos = 0;
    uint64_t memlimit = UINT64_MAX;
    char *part, *dir;
    FILE *f;
    int i;
    if (!res || !(g = LoadResource(NULL, res)) || !(d = LockResource(g)) || (n = SizeofResource(NULL, res)) < 8) {
        *error = join("the program has no resource for ", "", base_name(dst));
        return 0;
    }
    for (i = 0; i < 8; i++)
        size |= (uint64_t)d[i] << (8 * i);
    if (have >= 0 && (keep_existing || (uint64_t)have == size))
        return 1;
    if (!(out = malloc((size_t)size ? (size_t)size : 1)))
        abort();
    if (lzma_stream_buffer_decode(&memlimit, 0, NULL, d + 8, &in_pos, n - 8, out, &out_pos, (size_t)size) != LZMA_OK ||
        out_pos != size) {
        free(out);
        *error = join("the program's copy of this is damaged: ", "", base_name(dst));
        return 0;
    }
    dir = xstrdup(dst);
    *(char *)base_name(dir) = 0;
    make_dirs(dir);
    free(dir);
    part = join(dst, "", ".part");
    f = fopen(part, "wb");
    if (!f || fwrite(out, 1, (size_t)size, f) != size || fclose(f) || !MoveFileExA(part, dst, MOVEFILE_REPLACE_EXISTING)) {
        DeleteFileA(part);
        free(out);
        free(part);
        *error = join("cannot write ", "", dst);
        return 0;
    }
    free(out);
    free(part);
    return 1;
}

int setup_port_files(const char *game_dir, char **error)
{
    char *fonts = join(game_dir, "\\", "native\\fonts.bin"), *aa = join(game_dir, "\\", "native\\fonts_aa.bin"),
         *dat = join(game_dir, "\\", "CIV2.DAT");
    int ok = write_resource(201, fonts, 0, error) && write_resource(202, aa, 0, error) &&
             write_resource(203, dat, 1, error);
    free(fonts);
    free(aa);
    free(dat);
    return ok;
}

void setup_program_dir(char *buf, size_t size)
{
    wchar_t w[32768];
    DWORD n = GetModuleFileNameW(NULL, w, sizeof w / sizeof w[0]);
    char *b;
    if (!n || n >= sizeof w / sizeof w[0] ||
        !WideCharToMultiByte(CP_UTF8, 0, w, -1, buf, (int)size, NULL, NULL)) {
        snprintf(buf, size, ".");
        return;
    }
    b = (char *)base_name(buf);
    if (b > buf)
        b[-1] = 0;
}
