/* Indeo Video Interactive 4.1 decoding (iv41.c): frames to YUV 4:1:0. */
#ifndef CIV2_IV41_H
#define CIV2_IV41_H

#include <stdint.h>

typedef struct Iv41 Iv41;

typedef struct {
    int width, height;
    const uint8_t *y, *u, *v;   /* chroma: a quarter of the width and height */
    int y_stride, uv_stride;
    int has_transparency;       /* the stream carries a transparency mask (not decoded) */
} Iv41Frame;

Iv41 *iv41_open(int width, int height);
/* One compressed frame; 1 and the picture in *out (valid until the next
 * call) if a frame came out. */
int iv41_decode(Iv41 *d, const void *data, int size, Iv41Frame *out);
void iv41_close(Iv41 *d);

#endif
