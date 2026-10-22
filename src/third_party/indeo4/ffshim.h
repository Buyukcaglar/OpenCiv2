/*
 * The small part of FFmpeg's libavutil/libavcodec the Indeo 4 decoder files
 * (taken unchanged from FFmpeg 6.1.2) use, for building them on their own.
 * Each FFmpeg header they include is a one-line file here that includes
 * this one.  Written for this project (not FFmpeg code).
 */
#ifndef CIV2_FFSHIM_H
#define CIV2_FFSHIM_H

#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* ---- attributes, macros ---- */
#define av_cold
#define av_always_inline inline __attribute__((always_inline))
#define av_noinline __attribute__((noinline))
#define av_unused __attribute__((unused))
#define av_const __attribute__((const))
#define av_pure __attribute__((pure))
#define av_flatten
#define av_uninit(x) x
#define av_warn_unused_result
#define av_builtin_constant_p __builtin_constant_p
#define attribute_align_arg
#define attribute_deprecated
#define av_restrict restrict
#define DECLARE_ALIGNED(n, t, v) t __attribute__((aligned(n))) v
#define FFALIGN(x, a) (((x) + (a) - 1) & ~((a) - 1))
#define FFMIN(a, b) ((a) > (b) ? (b) : (a))
#define FFMAX(a, b) ((a) > (b) ? (a) : (b))
#define FFMIN3(a, b, c) FFMIN(FFMIN(a, b), c)
#define FFABS(a) ((a) >= 0 ? (a) : (-(a)))
#define FFSIGN(a) ((a) > 0 ? 1 : -1)
#define FFSWAP(type, a, b) do { type SWAP_tmp = b; b = a; a = SWAP_tmp; } while (0)
#define FF_ARRAY_ELEMS(a) (sizeof(a) / sizeof((a)[0]))
#define MKTAG(a, b, c, d) ((a) | ((b) << 8) | ((c) << 16) | ((unsigned)(d) << 24))
#define AV_INPUT_BUFFER_PADDING_SIZE 64
#define CONFIG_SMALL 0
#define HAVE_BIGENDIAN 0
#define HAVE_FAST_UNALIGNED 0
#define ARCH_X86 0
#define UNCHECKED_BITSTREAM_READER 0
#define CACHED_BITSTREAM_READER 0
#define HAVE_FAST_64BIT 0

/* ---- errors, logging, assertions ---- */
#define AVERROR(e) (-(e))
#define FFERRTAG(a, b, c, d) (-(int)MKTAG(a, b, c, d))
#define AVERROR_INVALIDDATA FFERRTAG('I', 'N', 'D', 'A')
#define AVERROR_PATCHWELCOME FFERRTAG('P', 'A', 'W', 'E')
#define AVERROR_BUG FFERRTAG('B', 'U', 'G', '!')
#define AV_LOG_PANIC 0
#define AV_LOG_FATAL 8
#define AV_LOG_ERROR 16
#define AV_LOG_WARNING 24
#define AV_LOG_INFO 32
#define AV_LOG_VERBOSE 40
#define AV_LOG_DEBUG 48
static inline void av_log(void *avcl, int level, const char *fmt, ...) { (void)avcl; (void)level; (void)fmt; }
#define ff_dlog(ctx, ...) do { } while (0)
#define av_assert0(c) do { if (!(c)) abort(); } while (0)
#define av_assert1(c) do { } while (0)
#define av_assert2(c) do { } while (0)
#define avpriv_request_sample(...) do { } while (0)
#define avpriv_report_missing_feature(...) do { } while (0)

/* ---- memory ---- */
static inline void *av_malloc(size_t n) { return malloc(n ? n : 1); }
static inline void *av_mallocz(size_t n) { return calloc(1, n ? n : 1); }
static inline void *av_calloc(size_t n, size_t s) { return calloc(n ? n : 1, s ? s : 1); }
static inline void *av_malloc_array(size_t n, size_t s) { return malloc(n && s ? n * s : 1); }
static inline void *av_realloc(void *p, size_t n) { return realloc(p, n ? n : 1); }
static inline void *av_realloc_array(void *p, size_t n, size_t s) { return realloc(p, n && s ? n * s : 1); }
static inline void *av_realloc_f(void *p, size_t n, size_t s) { void *r = realloc(p, n && s ? n * s : 1); if (!r) free(p); return r; }
static inline void av_free(void *p) { free(p); }
static inline void av_freep(void *pp) { void **p = (void **)pp; free(*p); *p = NULL; }

/* ---- reading, bits, clipping ---- */
static inline uint32_t AV_RB32(const void *p) { const uint8_t *b = p; return (uint32_t)b[0] << 24 | b[1] << 16 | b[2] << 8 | b[3]; }
static inline uint32_t AV_RL32(const void *p) { const uint8_t *b = p; return (uint32_t)b[3] << 24 | b[2] << 16 | b[1] << 8 | b[0]; }
static inline uint16_t AV_RB16(const void *p) { const uint8_t *b = p; return (uint16_t)(b[0] << 8 | b[1]); }
static inline uint16_t AV_RL16(const void *p) { const uint8_t *b = p; return (uint16_t)(b[1] << 8 | b[0]); }
static inline uint64_t AV_RB64(const void *p) { const uint8_t *b = p; return (uint64_t)AV_RB32(b) << 32 | AV_RB32(b + 4); }
static inline uint64_t AV_RL64(const void *p) { const uint8_t *b = p; return (uint64_t)AV_RL32(b + 4) << 32 | AV_RL32(b); }
#define AV_WN16(p, v) do { uint16_t AV_v = (v); memcpy(p, &AV_v, 2); } while (0)
#define AV_COPY64(d, s) memcpy(d, s, 8)
#define AV_WN32(p, v) do { uint32_t AV_v = (v); memcpy(p, &AV_v, 4); } while (0)
#define AV_WL32(p, v) do { uint8_t *AV_b = (uint8_t *)(p); uint32_t AV_v = (v); AV_b[0] = AV_v; AV_b[1] = AV_v >> 8; AV_b[2] = AV_v >> 16; AV_b[3] = AV_v >> 24; } while (0)
static inline int av_log2(unsigned v) { return v ? 31 - __builtin_clz(v) : 0; }
static inline int av_log2_16bit(unsigned v) { return av_log2(v & 0xffff); }
#define NEG_SSR32(a, s) (((int32_t)(a)) >> ((32 - (s)) & 31))
#define NEG_USR32(a, s) (((uint32_t)(a)) >> ((32 - (s)) & 31))
static inline int sign_extend(int val, unsigned bits) { unsigned shift = 8 * sizeof(int) - bits; union { unsigned u; int s; } v = { (unsigned)val << shift }; return v.s >> shift; }
static inline int64_t sign_extend64(int64_t val, unsigned bits) { unsigned shift = 64 - bits; union { uint64_t u; int64_t s; } v = { (uint64_t)val << shift }; return v.s >> shift; }
static inline unsigned zero_extend(unsigned val, unsigned bits) { return (val << ((8 * sizeof(int)) - bits)) >> ((8 * sizeof(int)) - bits); }
static inline int av_clip(int a, int lo, int hi) { return a < lo ? lo : a > hi ? hi : a; }
static inline uint8_t av_clip_uint8(int a) { return (uint8_t)(a & ~0xFF ? (~a) >> 31 : a); }
static inline int16_t av_clip_int16(int a) { return (int16_t)((a + 0x8000U) & ~0xFFFF ? (a >> 31) ^ 0x7FFF : a); }
static inline unsigned av_clip_uintp2(int a, int p) { return (a & ~((1 << p) - 1)) ? (~a >> 31 & ((1 << p) - 1)) : (unsigned)a; }
static inline unsigned av_mod_uintp2(unsigned a, unsigned p) { return a & ((1U << p) - 1); }
extern const uint8_t ff_reverse[256];
extern const uint8_t ff_zigzag_direct[64];     /* zigzag.c */

/* ---- once ---- */
typedef int AVOnce;
#define AV_ONCE_INIT 0
static inline int ff_thread_once(AVOnce *once, void (*fn)(void)) { if (!*once) { *once = 1; fn(); } return 0; }

/* ---- codec context, frames, packets ---- */
enum AVMediaType { AVMEDIA_TYPE_VIDEO = 0 };
enum AVPixelFormat { AV_PIX_FMT_NONE = -1, AV_PIX_FMT_YUV410P = 6 };
enum AVCodecID { AV_CODEC_ID_NONE, AV_CODEC_ID_INDEO4 };
enum AVPictureType { AV_PICTURE_TYPE_NONE, AV_PICTURE_TYPE_I, AV_PICTURE_TYPE_P, AV_PICTURE_TYPE_B };
#define AV_CODEC_CAP_DR1 (1 << 1)
#define AV_NUM_DATA_POINTERS 8

typedef struct AVFrame {
    uint8_t *data[AV_NUM_DATA_POINTERS];
    int linesize[AV_NUM_DATA_POINTERS];
    int width, height, format, key_frame, flags;
    enum AVPictureType pict_type;
    void *buf;                          /* the planes' allocation */
} AVFrame;
#define AV_FRAME_FLAG_KEY (1 << 1)

typedef struct AVCodecContext {
    void *priv_data;
    int width, height, coded_width, coded_height;
    enum AVPixelFormat pix_fmt;
    enum AVCodecID codec_id;
    int64_t max_pixels;
    int has_b_frames;
} AVCodecContext;

typedef struct AVPacket {
    uint8_t *data;
    int size;
} AVPacket;

AVFrame *av_frame_alloc(void);
void av_frame_unref(AVFrame *f);
void av_frame_free(AVFrame **f);
void av_frame_move_ref(AVFrame *dst, AVFrame *src);
int ff_get_buffer(AVCodecContext *avctx, AVFrame *frame, int flags);
int ff_set_dimensions(AVCodecContext *avctx, int w, int h);
static inline int av_image_check_size2(unsigned w, unsigned h, int64_t max, enum AVPixelFormat f, int o, void *l)
{
    (void)max; (void)f; (void)o; (void)l;
    return (w && h && w < 16384 && h < 16384) ? 0 : AVERROR(EINVAL);
}

/* the decoder's registration (indeo4.c's ff_indeo4_decoder) */
typedef struct FFCodec {
    struct { const char *name; enum AVMediaType type; enum AVCodecID id; int capabilities; } p;
    const char *long_name;
    int priv_data_size;
    int (*init)(AVCodecContext *);
    int (*close)(AVCodecContext *);
    int (*decode)(AVCodecContext *, AVFrame *, int *, AVPacket *);
} FFCodec;
#define CODEC_LONG_NAME(s) .long_name = (s)
#define FF_CODEC_DECODE_CB(f) .decode = (f)

#endif
