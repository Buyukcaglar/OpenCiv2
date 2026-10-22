/*
 * Indeo Video Interactive 4.1 (IV41) frames to YUV 4:1:0 planes, with
 * FFmpeg's decoder (indeo4.c, ivi.c, ivi_dsp.c: LGPL 2.1 or later, see
 * COPYING.LGPLv2.1) and the stand-ins of ffshim.h.  Written for this project.
 */
#include "indeo4.c"
#include "iv41.h"

AVFrame *av_frame_alloc(void) { return calloc(1, sizeof(AVFrame)); }

void av_frame_unref(AVFrame *f)
{
    if (!f)
        return;
    free(f->buf);
    memset(f, 0, sizeof *f);
}

void av_frame_free(AVFrame **f)
{
    if (*f) {
        av_frame_unref(*f);
        free(*f);
        *f = NULL;
    }
}

void av_frame_move_ref(AVFrame *dst, AVFrame *src)
{
    *dst = *src;
    memset(src, 0, sizeof *src);
}

int ff_set_dimensions(AVCodecContext *avctx, int w, int h)
{
    if (av_image_check_size2(w, h, 0, AV_PIX_FMT_NONE, 0, NULL) < 0)
        return AVERROR(EINVAL);
    avctx->width = avctx->coded_width = w;
    avctx->height = avctx->coded_height = h;
    return 0;
}

/* YUV 4:1:0: chroma at a quarter of the width and height. */
int ff_get_buffer(AVCodecContext *avctx, AVFrame *frame, int flags)
{
    int w = avctx->width, h = avctx->height, i;
    int lw[3], lh[3];
    size_t total = 0, off[3];
    uint8_t *p;
    (void)flags;
    lw[0] = FFALIGN(w + 32, 32);
    lh[0] = h + 32;
    lw[1] = lw[2] = FFALIGN((w + 3) / 4 + 32, 32);
    lh[1] = lh[2] = (h + 3) / 4 + 32;
    for (i = 0; i < 3; i++) {
        off[i] = total;
        total += (size_t)lw[i] * lh[i];
    }
    p = calloc(1, total + AV_INPUT_BUFFER_PADDING_SIZE);
    if (!p)
        return AVERROR(ENOMEM);
    frame->buf = p;
    for (i = 0; i < 3; i++) {
        frame->data[i] = p + off[i];
        frame->linesize[i] = lw[i];
    }
    frame->width = w;
    frame->height = h;
    frame->format = AV_PIX_FMT_YUV410P;
    return 0;
}

struct Iv41 {
    AVCodecContext avctx;
    AVFrame *frame;
    uint8_t *pkt;
    int pkt_cap;
};

Iv41 *iv41_open(int width, int height)
{
    Iv41 *d = calloc(1, sizeof *d);
    if (!d)
        return NULL;
    d->avctx.width = d->avctx.coded_width = width;
    d->avctx.height = d->avctx.coded_height = height;
    d->avctx.codec_id = AV_CODEC_ID_INDEO4;
    d->avctx.priv_data = calloc(1, ff_indeo4_decoder.priv_data_size);
    d->frame = av_frame_alloc();
    if (!d->avctx.priv_data || !d->frame || ff_indeo4_decoder.init(&d->avctx) < 0) {
        iv41_close(d);
        return NULL;
    }
    return d;
}

int iv41_decode(Iv41 *d, const void *data, int size, Iv41Frame *out)
{
    AVPacket pkt;
    int got = 0;
    if (size + AV_INPUT_BUFFER_PADDING_SIZE > d->pkt_cap) {
        free(d->pkt);
        d->pkt_cap = size + AV_INPUT_BUFFER_PADDING_SIZE;
        d->pkt = malloc((size_t)d->pkt_cap);
        if (!d->pkt) {
            d->pkt_cap = 0;
            return 0;
        }
    }
    memcpy(d->pkt, data, (size_t)size);
    memset(d->pkt + size, 0, AV_INPUT_BUFFER_PADDING_SIZE);
    pkt.data = d->pkt;
    pkt.size = size;
    av_frame_unref(d->frame);
    if (ff_indeo4_decoder.decode(&d->avctx, d->frame, &got, &pkt) < 0 || !got)
        return 0;
    out->width = d->frame->width;
    out->height = d->frame->height;
    out->y = d->frame->data[0];
    out->u = d->frame->data[1];
    out->v = d->frame->data[2];
    out->y_stride = d->frame->linesize[0];
    out->uv_stride = d->frame->linesize[1];
    out->has_transparency = ((IVI45DecContext *)d->avctx.priv_data)->has_transp;
    return 1;
}

void iv41_close(Iv41 *d)
{
    if (!d)
        return;
    if (d->avctx.priv_data)
        ff_indeo4_decoder.close(&d->avctx);
    free(d->avctx.priv_data);
    av_frame_free(&d->frame);
    free(d->pkt);
    free(d);
}
