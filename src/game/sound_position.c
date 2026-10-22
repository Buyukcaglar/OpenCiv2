/*
 * Playback position of the wave output device.
 */
#include "game.h"

#define g_wave_open        (*(int *)((u8 *)&g.d_006385b0))
#define g_wave_out         (*(HWAVEOUT *)((u8 *)&g.d_00638578))
#define g_wave_block_align (*(ushort *)((u8 *)&g.d_006385ac))

#define SAMPLES_PER_MS 22.05      /* 22050 Hz */

/* 0x005d5643: position in milliseconds. */
undefined4 __cdecl FUN_005d5643(void)
{
    MMTIME t;

    t.wType = TIME_SAMPLES;
    if (g_wave_open)
        waveOutGetPosition(g_wave_out, &t, sizeof t);
    switch (t.wType) {
    case TIME_MS:
        return t.u.ms;
    case TIME_SAMPLES:
        return (int)((double)(ulonglong)t.u.sample / SAMPLES_PER_MS);
    case TIME_BYTES:
        return (int)((double)(ulonglong)(t.u.cb / g_wave_block_align) / SAMPLES_PER_MS);
    default:
        return 0;
    }
}

/* 0x005d5706: position in samples. */
undefined4 __cdecl FUN_005d5706(void)
{
    MMTIME t;

    t.wType = TIME_SAMPLES;
    if (g_wave_open)
        waveOutGetPosition(g_wave_out, &t, sizeof t);
    switch (t.wType) {
    case TIME_MS:
        return (int)((double)(ulonglong)t.u.ms * SAMPLES_PER_MS);
    case TIME_SAMPLES:
        return t.u.sample;
    case TIME_BYTES:
        return t.u.cb / g_wave_block_align;
    default:
        return 0;
    }
}
