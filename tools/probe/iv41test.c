/* Decode the video frames of an IV41 AVI (the video stream's 00dc chunks)
 * and write some as PPM: a check of src/third_party/indeo4.
 * cc -I src/third_party/indeo4 tools/probe/iv41test.c src/third_party/indeo4/{iv41,ivi,ivi_dsp,vlc,reverse}.c
 * ./a.out FILE.AVI OUTPREFIX [EVERY] */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "iv41.h"

static unsigned rd32(const unsigned char *p) { return p[0] | p[1] << 8 | p[2] << 16 | (unsigned)p[3] << 24; }
static unsigned char clip(int v) { return v < 0 ? 0 : v > 255 ? 255 : v; }

int main(int argc, char **argv)
{
    FILE *f = fopen(argv[1], "rb");
    long n;
    unsigned char *b;
    unsigned w = 0, h = 0, i, frames = 0, every = argc > 3 ? atoi(argv[3]) : 10;
    Iv41 *d;
    if (!f) return 1;
    fseek(f, 0, SEEK_END); n = ftell(f); fseek(f, 0, SEEK_SET);
    b = malloc(n); fread(b, 1, n, f); fclose(f);
    for (i = 0; i + 8 < (unsigned)n; i++)
        if (!memcmp(b + i, "strf", 4) && !w) { w = rd32(b + i + 12); h = rd32(b + i + 16); }
    printf("%ux%u\n", w, h);
    d = iv41_open(w, h);
    for (i = 0; i + 8 < (unsigned)n; i++) {
        if (memcmp(b + i, "00", 2) || !memcmp(b + i, "00ix", 4) || i < 2044) continue;   /* stream 0 (tagged 00dc, or 0041 in Civ2's files) */
        unsigned len = rd32(b + i + 4);
        Iv41Frame fr;
        if (len && i + 8 + len <= (unsigned)n && iv41_decode(d, b + i + 8, len, &fr)) {
            if (frames % every == 0) {
                char name[256];
                FILE *o;
                int x, y;
                snprintf(name, sizeof name, "%s%03u.ppm", argv[2], frames);
                o = fopen(name, "wb");
                fprintf(o, "P6\n%d %d\n255\n", fr.width, fr.height);
                for (y = 0; y < fr.height; y++)
                    for (x = 0; x < fr.width; x++) {
                        int Y = fr.y[y * fr.y_stride + x] - 16, U = fr.u[(y / 4) * fr.uv_stride + x / 4] - 128,
                            V = fr.v[(y / 4) * fr.uv_stride + x / 4] - 128;
                        fputc(clip((298 * Y + 409 * V + 128) >> 8), o);
                        fputc(clip((298 * Y - 100 * U - 208 * V + 128) >> 8), o);
                        fputc(clip((298 * Y + 516 * U + 128) >> 8), o);
                    }
                fclose(o);
            }
            if (!frames) printf("transparency: %d\n", fr.has_transparency);
            frames++;
        }
        i += 7 + len;
    }
    printf("%u frames\n", frames);
    iv41_close(d);
    return 0;
}
