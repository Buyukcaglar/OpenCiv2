/*
 * Secondary random number generator (Numerical Recipes LCG), used for
 * cosmetic randomness separately from the CRT rand() stream.
 */
#include "game.h"


/* 0x0059a733: uniform value in [0, 1]. */
float10 __cdecl rng_next_unit(void)
{
    (*(uint *)&g_nr_seed) = (*(uint *)&g_nr_seed) * 1664525 + 1013904223;
    return (float10)(*(uint *)&g_nr_seed) / (float10)0xffffffffu;
}

/* 0x0059a791: random integer in [lo, hi] (bounds in either order). */
int __cdecl rand_range(int lo, int hi)
{
    double span;
    int t;

    if (hi == lo) {
        rng_next_unit();     /* still advances the generator */
        return lo;
    }
    if (hi < lo) {
        t = lo;
        lo = hi;
        hi = t;
    }
    span = (double)(hi - lo) + 0.999999;
    return (int)(rng_next_unit() * span) + lo;
}
