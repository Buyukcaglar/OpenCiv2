/*
 * The set-up's music from a CD in its drive (src/host/setup_disc.c's
 * cd_has_music, cd_encode_music), with a fake drive: os_cd_open, os_cd_read
 * serve a disc image's .bin as the CD's sectors (the audio tracks where
 * they are on the disc: after the 2-second pregap the image leaves out).
 * Their Ogg files must be those of the image (image_encode_music's, in
 * IMAGE_MUSIC) but for the ENCODER tag: the same audio pages.  Then a drive
 * that fails after a while: -1, no file half written.
 *
 *   tools/dk sh -c 'T=tools/toolchain; V=$T/libvorbis/lib; cc -O2 \
 *     -DHAVE_ALLOCA_H -Isrc/host -I$T/libogg/include -I$T/libvorbis/include \
 *     -I$V -o build/cd_music_test tests/cd_music_test.c src/host/setup_disc.c \
 *     $T/libogg/src/bitwise.c $T/libogg/src/framing.c $(for f in analysis \
 *     bitrate block codebook envelope floor0 floor1 info lookup lpc lsp \
 *     mapping0 mdct psy registry res0 sharedbook smallft synthesis vorbisenc \
 *     window; do echo $V/$f.c; done) -lm'
 *   build/cd_music_test IMAGE.cue IMAGE_MUSIC OUT_DIR    (OUT_DIR: made)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <strings.h>
#include <unistd.h>
#include "setup_os.h"

#define RAW 2352

/* ---- what setup_disc.c asks of the system ---- */

int os_dir_exists(const char *p)
{
    struct stat st;
    return !stat(p, &st) && S_ISDIR(st.st_mode);
}

int os_file_exists(const char *p)
{
    struct stat st;
    return !stat(p, &st) && S_ISREG(st.st_mode);
}

void os_make_dirs(const char *path)
{
    mkdir(path, 0755);
}

int os_entry(const char *dir, const char *name, char *out, size_t size)
{
    DIR *d;
    struct dirent *e;
    int found = 0;
    snprintf(out, size, "%s/%s", dir, name);
    if (!access(out, F_OK))
        return 1;
    if (!(d = opendir(dir)))
        return 0;
    while (!found && (e = readdir(d)))
        if (!strcasecmp(e->d_name, name)) {
            snprintf(out, size, "%s/%s", dir, e->d_name);
            found = 1;
        }
    closedir(d);
    return found;
}

int os_each(const char *dir, int (*fn)(void *ctx, const char *name, int is_dir), void *ctx)
{
    (void)dir, (void)fn, (void)ctx;
    return 1;
}

void os_message(const char *text, int kind)
{
    printf("message (%d): %s\n", kind, text);
}

int os_progress_show(const char *what, const char *detail)
{
    (void)what, (void)detail;
    return 0;
}

/* ---- the fake drive: the image's .bin, its tracks from the .cue ---- */

static struct cd_toc disc;
static FILE *bin;
static long reads, fail_after = -1, sectors_read;

static int read_cue(const char *cue)
{
    char line[1024], dir[SETUP_PATH], name[1024], path[SETUP_PATH + 1024], *slash, *q;
    FILE *c = fopen(cue, "r");
    int n = 0, audio = 0, m, s, f;
    if (!c)
        return 0;
    snprintf(dir, sizeof dir, "%s", cue);
    if ((slash = strrchr(dir, '/')))
        *slash = 0;
    while (fgets(line, sizeof line, c)) {
        if (sscanf(line, " FILE \"%1023[^\"]\"", name) == 1) {
            snprintf(path, sizeof path, "%s/%s", dir, name);
            if (!(bin = fopen(path, "rb")))
                return 0;
        } else if (sscanf(line, " TRACK %d", &n) == 1) {
            audio = strstr(line, "AUDIO") != NULL;
        } else if ((q = strstr(line, "INDEX 01")) && sscanf(q + 8, "%d:%d:%d", &m, &s, &f) == 3) {
            /* (the image's audio from track 2 on: 150 sectors later on the disc) */
            disc.t[disc.ntracks].number = n;
            disc.t[disc.ntracks].audio = audio;
            disc.t[disc.ntracks].lba = (m * 60L + s) * 75 + f + (n > 1 ? 150 : 0);
            disc.ntracks++;
        }
    }
    fclose(c);
    fseeko(bin, 0, SEEK_END);
    disc.leadout = (long)(ftello(bin) / RAW) + 150;
    return bin && disc.ntracks > 1;
}

int os_cd_open(const char *cd, struct cd_toc *toc, void **h)
{
    (void)cd;
    *toc = disc;
    *h = &disc;
    return 1;
}

int os_cd_read(void *h, long lba, int n, unsigned char *buf)
{
    (void)h;
    if (n < 1 || n > 16 || lba < 0 || lba + n > disc.leadout || (fail_after >= 0 && reads >= fail_after))
        return 0;
    reads++;
    sectors_read += n;
    /* (the pregap, not in the image: silence) */
    for (; n && lba >= disc.t[1].lba - 150 && lba < disc.t[1].lba; n--, lba++, buf += RAW)
        memset(buf, 0, RAW);
    if (n && (fseeko(bin, (off_t)(lba - (lba >= disc.t[1].lba ? 150 : 0)) * RAW, SEEK_SET) ||
              fread(buf, RAW, (size_t)n, bin) != (size_t)n))
        return 0;
    return 1;
}

void os_cd_close(void *h)
{
    (void)h;
}

/* ---- comparing ---- */

static unsigned char *slurp(const char *path, long *size)
{
    FILE *f = fopen(path, "rb");
    unsigned char *p;
    if (!f)
        return NULL;
    fseek(f, 0, SEEK_END);
    *size = ftell(f);
    rewind(f);
    p = malloc((size_t)*size + 1);
    if (fread(p, 1, (size_t)*size, f) != (size_t)*size) {
        free(p);
        p = NULL;
    }
    fclose(f);
    return p;
}

/* Where the first page with a granule position (audio) starts; -1: none. */
static long audio_pages(const unsigned char *p, long size)
{
    long at = 0;
    while (at + 27 <= size && !memcmp(p + at, "OggS", 4)) {
        long body = 0, i;
        int nseg = p[at + 26], zero = 1;
        for (i = 6; i < 14; i++)
            zero &= p[at + i] == 0;
        if (!zero)
            return at;
        for (i = 0; i < nseg; i++)
            body += p[at + 27 + i];
        at += 27 + nseg + body;
    }
    return -1;
}

static int same_audio(const char *a, const char *b)
{
    long na, nb, sa, sb;
    unsigned char *pa = slurp(a, &na), *pb = slurp(b, &nb);
    int same = pa && pb && (sa = audio_pages(pa, na)) > 0 && (sb = audio_pages(pb, nb)) > 0 && na - sa == nb - sb &&
               !memcmp(pa + sa, pb + sb, (size_t)(na - sa));
    free(pa);
    free(pb);
    return same;
}

int main(int argc, char **argv)
{
    char out[SETUP_PATH], a[2 * SETUP_PATH], b[2 * SETUP_PATH];
    int i, r, failed = 0, tracks = 0;
    if (argc != 4 || !read_cue(argv[1])) {
        fprintf(stderr, "usage: cd_music_test IMAGE.cue IMAGE_MUSIC OUT_DIR\n");
        return 2;
    }
    snprintf(out, sizeof out, "%s", argv[3]);
    mkdir(out, 0755);
    r = cd_has_music("/fake");
    printf("cd_has_music: %d\n", r);
    failed |= r != 1;
    r = cd_encode_music("/fake", out);
    printf("cd_encode_music: %d (%ld reads, %ld sectors)\n", r, reads, sectors_read);
    failed |= r != 1;
    for (i = 0; i < disc.ntracks; i++) {
        if (!disc.t[i].audio)
            continue;
        snprintf(a, sizeof a, "%s/Track%02d.ogg", argv[2], disc.t[i].number);
        snprintf(b, sizeof b, "%s/Music/Track%02d.ogg", out, disc.t[i].number);
        tracks++;
        if (!same_audio(a, b)) {
            printf("%s: not the image's audio\n", b);
            failed = 1;
        }
    }
    printf("%d tracks compared\n", tracks);

    /* a drive that stops reading (in track 3): -1, no .part left */
    reads = 0;
    fail_after = 2000;
    r = cd_encode_music("/fake", out);
    printf("cd_encode_music, failing drive: %d\n", r);
    failed |= r != -1;
    for (i = 0; i < disc.ntracks; i++) {
        snprintf(b, sizeof b, "%s/Music/Track%02d.ogg.part", out, disc.t[i].number);
        if (os_file_exists(b)) {
            printf("%s left\n", b);
            failed = 1;
        }
    }
    printf(failed ? "FAILED\n" : "ok\n");
    return failed;
}
