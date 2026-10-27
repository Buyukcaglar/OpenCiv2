/*
 * Playback position of the wave output device.
 */
#include "game.h"


#define SAMPLES_PER_MS 22.05      /* 22050 Hz */

/* 0x005d5643: position in milliseconds. */
i32 __cdecl snd_wave_get_position_ms(void)
{
    MMTIME t;

    t.wType = TIME_SAMPLES;
    if (snd_wave.device_open)
        waveOutGetPosition((*(HWAVEOUT *)&snd_wave.out_handle), &t, sizeof t);
    switch (t.wType) {
    case TIME_MS:
        return t.u.ms;
    case TIME_SAMPLES:
        return (int)((double)(ulonglong)t.u.sample / SAMPLES_PER_MS);
    case TIME_BYTES:
        return (int)((double)(ulonglong)(t.u.cb / (*(ushort *)&snd_wave.block_align)) / SAMPLES_PER_MS);
    default:
        return 0;
    }
}

/* 0x005d5706: position in samples. */
i32 __cdecl snd_wave_get_position_samples(void)
{
    MMTIME t;

    t.wType = TIME_SAMPLES;
    if (snd_wave.device_open)
        waveOutGetPosition((*(HWAVEOUT *)&snd_wave.out_handle), &t, sizeof t);
    switch (t.wType) {
    case TIME_MS:
        return (int)((double)(ulonglong)t.u.ms * SAMPLES_PER_MS);
    case TIME_SAMPLES:
        return t.u.sample;
    case TIME_BYTES:
        return t.u.cb / (*(ushort *)&snd_wave.block_align);
    default:
        return 0;
    }
}
