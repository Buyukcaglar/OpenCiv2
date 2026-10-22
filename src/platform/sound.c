/*
 * Sound: waveOut over the host's audio (src/host), sndPlaySound, mmio (RIFF files), MCI.
 *
 * In replay mode there is no audio device, as in the reference environment
 * (an X server in a container, without sound): the game then runs without
 * sound, identically in both.
 */
#include "plat.h"
#include "../host/host.h"

static int audio_ok;

void sound_init(void)
{
    if (plat_replay || getenv("CIV2_NOSOUND"))
        return;
    audio_ok = host_audio_init();
}

/* ---- waveOut ---- */

#define MAX_HDR 64
typedef struct {
    int dev;
    WAVEFORMATEX fmt;
    DWORD_PTR cb, inst;
    DWORD flags;
    LPWAVEHDR pending[MAX_HDR];         /* written, not yet played */
    uint64_t end_bytes[MAX_HDR];          /* total queued when each ends */
    int npending;
    uint64_t queued_total;
} WaveOut;

static WaveOut *wave_get(HWAVEOUT h) { return obj_get(h, OBJ_WAVEOUT); }

UINT WINAPI waveOutGetNumDevs(void) { API_TRACE(); return audio_ok ? 1 : 0; }

MMRESULT WINAPI waveOutGetDevCapsA(UINT_PTR id, LPWAVEOUTCAPSA caps, UINT n)
{ API_TRACE();
    (void)id;
    if (!audio_ok)
        return MMSYSERR_BADDEVICEID;
    memset(caps, 0, n < sizeof *caps ? n : sizeof *caps);
    snprintf(caps->szPname, sizeof caps->szPname, "Audio");
    caps->dwFormats = 0xfff;
    caps->wChannels = 2;
    caps->dwSupport = WAVECAPS_VOLUME;
    return MMSYSERR_NOERROR;
}

MMRESULT WINAPI waveOutGetErrorTextA(MMRESULT err, LPSTR buf, UINT n)
{ API_TRACE();
    snprintf(buf, n, "wave output error %u", (unsigned)err);
    return MMSYSERR_NOERROR;
}

MMRESULT WINAPI waveOutOpen(LPHWAVEOUT out, UINT id, LPCWAVEFORMATEX f, DWORD_PTR cb, DWORD_PTR inst, DWORD flags)
{ API_TRACE();
    WaveOut *w;
    (void)id;
    if (!audio_ok)
        return MMSYSERR_NODRIVER;
    if (f->wFormatTag != WAVE_FORMAT_PCM)
        return WAVERR_BADFORMAT;
    if (flags & WAVE_FORMAT_QUERY)
        return MMSYSERR_NOERROR;
    w = calloc(1, sizeof *w);
    w->dev = host_audio_open((int)f->nSamplesPerSec, f->nChannels, f->wBitsPerSample == 8 ? 8 : 16);
    if (!w->dev) {
        free(w);
        return MMSYSERR_ALLOCATED;
    }
    w->fmt = *f;
    w->cb = cb;
    w->inst = inst;
    w->flags = flags;
    *out = obj_new(OBJ_WAVEOUT, w);
    if ((flags & CALLBACK_TYPEMASK) == CALLBACK_WINDOW)
        PostMessageA((HWND)cb, MM_WOM_OPEN, (WPARAM)*out, 0);
    return MMSYSERR_NOERROR;
}

static void wave_done(HWAVEOUT h, WaveOut *w, LPWAVEHDR hdr)
{
    hdr->dwFlags = (hdr->dwFlags & ~WHDR_INQUEUE) | WHDR_DONE;
    switch (w->flags & CALLBACK_TYPEMASK) {
    case CALLBACK_WINDOW:
        PostMessageA((HWND)w->cb, MM_WOM_DONE, (WPARAM)h, (LPARAM)hdr);
        break;
    case CALLBACK_FUNCTION:
        ((void (*)(HWAVEOUT, UINT, DWORD_PTR, DWORD_PTR, DWORD_PTR))w->cb)(h, WOM_DONE, w->inst, (DWORD_PTR)hdr, 0);
        break;
    }
}

static uint64_t played_bytes(WaveOut *w)
{
    return w->queued_total - host_audio_queued(w->dev);
}

/* Called from the message loop: finish buffers that have played. */
void sound_poll(void)
{
    int i;
    for (i = 1; i < 8192; i++) {
        HWAVEOUT h = ((Handle)OBJ_WAVEOUT << 16) | (Handle)i;
        WaveOut *w = wave_get(h);
        if (!w)
            continue;
        while (w->npending && played_bytes(w) >= w->end_bytes[0]) {
            LPWAVEHDR hdr = w->pending[0];
            memmove(w->pending, w->pending + 1, sizeof w->pending[0] * (size_t)(w->npending - 1));
            memmove(w->end_bytes, w->end_bytes + 1, sizeof w->end_bytes[0] * (size_t)(w->npending - 1));
            w->npending--;
            wave_done(h, w, hdr);
        }
    }
}

MMRESULT WINAPI waveOutPrepareHeader(HWAVEOUT h, LPWAVEHDR hdr, UINT n)
{ API_TRACE();
    (void)h; (void)n;
    hdr->dwFlags |= WHDR_PREPARED;
    return MMSYSERR_NOERROR;
}

MMRESULT WINAPI waveOutUnprepareHeader(HWAVEOUT h, LPWAVEHDR hdr, UINT n)
{ API_TRACE();
    (void)h; (void)n;
    if (hdr->dwFlags & WHDR_INQUEUE)
        return WAVERR_STILLPLAYING;
    hdr->dwFlags &= ~WHDR_PREPARED;
    return MMSYSERR_NOERROR;
}

MMRESULT WINAPI waveOutWrite(HWAVEOUT h, LPWAVEHDR hdr, UINT n)
{ API_TRACE();
    WaveOut *w = wave_get(h);
    (void)n;
    if (!w)
        return MMSYSERR_INVALHANDLE;
    if (w->npending == MAX_HDR)
        return MMSYSERR_NOMEM;
    hdr->dwFlags = (hdr->dwFlags & ~WHDR_DONE) | WHDR_INQUEUE;
    host_audio_queue(w->dev, hdr->lpData, hdr->dwBufferLength);
    w->queued_total += hdr->dwBufferLength;
    w->pending[w->npending] = hdr;
    w->end_bytes[w->npending++] = w->queued_total;
    return MMSYSERR_NOERROR;
}

MMRESULT WINAPI waveOutReset(HWAVEOUT h)
{ API_TRACE();
    WaveOut *w = wave_get(h);
    if (!w)
        return MMSYSERR_INVALHANDLE;
    host_audio_clear(w->dev);
    w->queued_total = 0;
    while (w->npending) {
        LPWAVEHDR hdr = w->pending[0];
        memmove(w->pending, w->pending + 1, sizeof w->pending[0] * (size_t)(w->npending - 1));
        w->npending--;
        wave_done(h, w, hdr);
    }
    return MMSYSERR_NOERROR;
}

MMRESULT WINAPI waveOutClose(HWAVEOUT h)
{ API_TRACE();
    WaveOut *w = wave_get(h);
    if (!w)
        return MMSYSERR_INVALHANDLE;
    if (w->npending)
        return WAVERR_STILLPLAYING;
    host_audio_close(w->dev);
    if ((w->flags & CALLBACK_TYPEMASK) == CALLBACK_WINDOW)
        PostMessageA((HWND)w->cb, MM_WOM_CLOSE, (WPARAM)h, 0);
    free(w);
    obj_free(h);
    return MMSYSERR_NOERROR;
}

MMRESULT WINAPI waveOutGetPosition(HWAVEOUT h, LPMMTIME t, UINT n)
{ API_TRACE();
    WaveOut *w = wave_get(h);
    uint64_t bytes;
    (void)n;
    if (!w)
        return MMSYSERR_INVALHANDLE;
    bytes = played_bytes(w);
    if (t->wType == TIME_SAMPLES) {
        t->u.sample = (DWORD)(bytes / (w->fmt.nBlockAlign ? w->fmt.nBlockAlign : 1));
    } else if (t->wType == TIME_MS) {
        t->u.ms = (DWORD)(bytes * 1000 / (w->fmt.nAvgBytesPerSec ? w->fmt.nAvgBytesPerSec : 1));
    } else {
        t->wType = TIME_BYTES;
        t->u.cb = (DWORD)bytes;
    }
    return MMSYSERR_NOERROR;
}

/* ---- sndPlaySound: whole WAV files ---- */

static int snd_dev;

static DWORD rd32le(const unsigned char *p) { return (DWORD)(p[0] | p[1] << 8 | p[2] << 16 | (DWORD)p[3] << 24); }

WINBOOL WINAPI sndPlaySoundA(LPCSTR name, UINT flags)
{ API_TRACE();
    char host[1024];
    unsigned char *buf;
    long size;
    unsigned pos, rate = 0, chans = 0, bits = 0, data = 0, len = 0;
    FILE *f;
    if (snd_dev) {
        host_audio_close(snd_dev);
        snd_dev = 0;
    }
    if (!name || !audio_ok)
        return name == NULL;
    if (flags & SND_MEMORY)
        return FALSE;
    plat_host_path(name, host, sizeof host, 0);
    if (!(f = fopen(host, "rb")))
        return FALSE;
    fseek(f, 0, SEEK_END);
    size = ftell(f);
    fseek(f, 0, SEEK_SET);
    buf = malloc((size_t)(size > 0 ? size : 1));
    if (size < 12 || fread(buf, 1, (size_t)size, f) != (size_t)size || memcmp(buf, "RIFF", 4) || memcmp(buf + 8, "WAVE", 4)) {
        fclose(f);
        free(buf);
        return FALSE;
    }
    fclose(f);
    /* the PCM format and the samples */
    for (pos = 12; pos + 8 <= (unsigned)size; pos += 8 + ((rd32le(buf + pos + 4) + 1) & ~1u)) {
        unsigned n = rd32le(buf + pos + 4);
        if (!memcmp(buf + pos, "fmt ", 4) && n >= 16 && buf[pos + 8] == 1 && buf[pos + 9] == 0) {
            chans = buf[pos + 10] | buf[pos + 11] << 8;
            rate = rd32le(buf + pos + 12);
            bits = buf[pos + 22] | buf[pos + 23] << 8;
        } else if (!memcmp(buf + pos, "data", 4)) {
            data = pos + 8;
            len = n < (unsigned)size - data ? n : (unsigned)size - data;
        }
    }
    if (!rate || !data || (bits != 8 && bits != 16) || !(snd_dev = host_audio_open((int)rate, (int)chans, (int)bits))) {
        free(buf);
        return FALSE;
    }
    host_audio_queue(snd_dev, buf + data, len);
    free(buf);
    if (!(flags & SND_ASYNC))
        while (host_audio_queued(snd_dev))
            host_delay_ms(10);
    return TRUE;
}

/* ---- mmio: a file read into memory, with RIFF chunk navigation ---- */

typedef struct { unsigned char *data; LONG size, pos; } Mmio;
#define MMIO_BUF 8192

static Mmio *mmio_get(HMMIO h) { return obj_get(h, OBJ_MMIO); }

HMMIO WINAPI mmioOpenA(LPSTR name, LPMMIOINFO info, DWORD flags)
{ API_TRACE();
    char host[1024];
    FILE *f;
    Mmio *m;
    (void)flags;
    if (info)
        info->wErrorRet = 0;
    plat_host_path(name, host, sizeof host, 0);
    f = fopen(host, "rb");
    if (!f) {
        if (info)
            info->wErrorRet = MMIOERR_CANNOTOPEN;
        return 0;
    }
    m = calloc(1, sizeof *m);
    fseek(f, 0, SEEK_END);
    m->size = (LONG)ftell(f);
    fseek(f, 0, SEEK_SET);
    m->data = malloc((size_t)m->size + MMIO_BUF);
    if (fread(m->data, 1, (size_t)m->size, f) != (size_t)m->size)
        plat_log("mmioOpen: short read\n");
    fclose(f);
    return obj_new(OBJ_MMIO, m);
}

MMRESULT WINAPI mmioClose(HMMIO h, UINT flags)
{ API_TRACE();
    Mmio *m = mmio_get(h);
    (void)flags;
    if (!m)
        return MMSYSERR_INVALHANDLE;
    free(m->data);
    free(m);
    obj_free(h);
    return MMSYSERR_NOERROR;
}

LONG WINAPI mmioRead(HMMIO h, HPSTR buf, LONG n)
{ API_TRACE();
    Mmio *m = mmio_get(h);
    if (!m)
        return -1;
    if (n > m->size - m->pos)
        n = m->size - m->pos;
    if (n < 0)
        n = 0;
    memcpy(buf, m->data + m->pos, (size_t)n);
    m->pos += n;
    return n;
}

LONG WINAPI mmioSeek(HMMIO h, LONG off, int origin)
{ API_TRACE();
    Mmio *m = mmio_get(h);
    LONG p;
    if (!m)
        return -1;
    p = origin == SEEK_SET ? off : origin == SEEK_CUR ? m->pos + off : m->size + off;
    if (p < 0 || p > m->size)
        return -1;
    return m->pos = p;
}

MMRESULT WINAPI mmioDescend(HMMIO h, LPMMCKINFO ck, const MMCKINFO *parent, UINT flags)
{ API_TRACE();
    Mmio *m = mmio_get(h);
    LONG end;
    if (!m)
        return MMSYSERR_INVALHANDLE;
    end = parent ? (LONG)(parent->dwDataOffset + parent->cksize) : m->size;
    for (;;) {
        DWORD id, size, type = 0;
        if (m->pos + 8 > end)
            return MMIOERR_CHUNKNOTFOUND;
        id = rd32le(m->data + m->pos);
        size = rd32le(m->data + m->pos + 4);
        if (id == FOURCC_RIFF || id == FOURCC_LIST)
            type = m->pos + 12 <= m->size ? rd32le(m->data + m->pos + 8) : 0;
        if ((flags & MMIO_FINDCHUNK) && id != ck->ckid) {
            m->pos += 8 + (LONG)((size + 1) & ~1u);
            continue;
        }
        if ((flags & MMIO_FINDRIFF) && (id != FOURCC_RIFF || type != ck->fccType)) {
            m->pos += 8 + (LONG)((size + 1) & ~1u);
            continue;
        }
        if ((flags & MMIO_FINDLIST) && (id != FOURCC_LIST || type != ck->fccType)) {
            m->pos += 8 + (LONG)((size + 1) & ~1u);
            continue;
        }
        ck->ckid = id;
        ck->cksize = size;
        ck->dwDataOffset = (DWORD)(m->pos + 8);
        ck->dwFlags = 0;
        if (id == FOURCC_RIFF || id == FOURCC_LIST) {
            ck->fccType = type;
            m->pos += 12;
        } else {
            m->pos += 8;
        }
        return MMSYSERR_NOERROR;
    }
}

MMRESULT WINAPI mmioAscend(HMMIO h, LPMMCKINFO ck, UINT flags)
{ API_TRACE();
    Mmio *m = mmio_get(h);
    (void)flags;
    if (!m)
        return MMSYSERR_INVALHANDLE;
    m->pos = (LONG)(ck->dwDataOffset + ((ck->cksize + 1) & ~1u));
    return MMSYSERR_NOERROR;
}

/* Direct buffer access: the buffer is the file image from the position. */
MMRESULT WINAPI mmioGetInfo(HMMIO h, LPMMIOINFO info, UINT flags)
{ API_TRACE();
    Mmio *m = mmio_get(h);
    (void)flags;
    if (!m)
        return MMSYSERR_INVALHANDLE;
    memset(info, 0, sizeof *info);
    info->hmmio = h;
    info->cchBuffer = MMIO_BUF;
    info->pchBuffer = (HPSTR)m->data + m->pos;
    info->pchNext = info->pchBuffer;
    info->pchEndRead = (HPSTR)m->data + (m->pos + MMIO_BUF < m->size ? m->pos + MMIO_BUF : m->size);
    info->pchEndWrite = info->pchBuffer + MMIO_BUF;
    info->lBufOffset = m->pos;
    info->lDiskOffset = m->pos;
    return MMSYSERR_NOERROR;
}

MMRESULT WINAPI mmioAdvance(HMMIO h, LPMMIOINFO info, UINT flags)
{ API_TRACE();
    Mmio *m = mmio_get(h);
    (void)flags;
    if (!m)
        return MMSYSERR_INVALHANDLE;
    m->pos = (LONG)(info->pchNext - (HPSTR)m->data);
    info->pchBuffer = (HPSTR)m->data + m->pos;
    info->pchNext = info->pchBuffer;
    info->pchEndRead = (HPSTR)m->data + (m->pos + MMIO_BUF < m->size ? m->pos + MMIO_BUF : m->size);
    info->lBufOffset = m->pos;
    info->lDiskOffset = m->pos;
    return MMSYSERR_NOERROR;
}

/* ---- MCI: no devices (music and video are not played) ---- */

MCIERROR WINAPI mciSendCommandA(MCIDEVICEID id, UINT msg, DWORD_PTR flags, DWORD_PTR param)
{ API_TRACE();
    (void)id; (void)flags; (void)param;
    if (msg == MCI_CLOSE)
        return 0;
    return MCIERR_DEVICE_NOT_INSTALLED;
}

MCIDEVICEID WINAPI mciGetDeviceIDA(LPCSTR name) { API_TRACE(); (void)name; return 0; }
