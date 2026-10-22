/*
 * Secondary random number generator (Numerical Recipes LCG), used for
 * cosmetic randomness separately from the CRT rand() stream.
 */
#include "game.h"

#define g_nr_seed (*(uint *)((u8 *)&g.d_00635094))

/* 0x0059a733: uniform value in [0, 1]. */
float10 __cdecl FUN_0059a733(void)
{
    g_nr_seed = g_nr_seed * 1664525 + 1013904223;
    return (float10)g_nr_seed / (float10)0xffffffffu;
}

/* 0x0059a791: random integer in [lo, hi] (bounds in either order). */
int __cdecl FUN_0059a791(int lo, int hi)
{
    double span;
    int t;

    if (hi == lo) {
        thunk_FUN_0059a733();     /* still advances the generator */
        return lo;
    }
    if (hi < lo) {
        t = lo;
        lo = hi;
        hi = t;
    }
    span = (double)(hi - lo) + 0.999999;
    return (int)(thunk_FUN_0059a733() * span) + lo;
}
