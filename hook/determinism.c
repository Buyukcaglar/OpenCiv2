/*
 * Determinism controls for side-by-side runs.
 *
 * CIV2_SEED=<n>        forces every srand() the game performs to use <n>
 *                      instead of whatever it derived from the clock, so two
 *                      runs (original vs reconstructed) see the same random
 *                      sequence.
 * CIV2_RAND_LOG=<path> logs every rand() call (call site and result).  Any
 *                      gameplay divergence shows up here first.
 */
#include <stdio.h>
#include <stdlib.h>
#include "hook.h"

#define ORIG_SRAND 0x005F2260
#define ORIG_RAND  0x005F2280
#define RAND_SEED (*(unsigned int *)0x00639E50)

static int forced_seed_set;
static int rand_stack_depth;     /* CIV2_RAND_STACK=n: also log n callers up the EBP chain */
static unsigned int forced_seed;
static struct maplog rand_log;

static void __cdecl hooked_srand(unsigned int seed)
{
    hook_logf("srand(%u)%s\n", seed, forced_seed_set ? " [forced]" : "");
    maplog_printf(&rand_log, "srand %u\n", forced_seed_set ? forced_seed : seed);
    RAND_SEED = forced_seed_set ? forced_seed : seed;
}

/* Same LCG as the game's rand(); kept here so we can log the call site. */
static int __cdecl hooked_rand(void)
{
    int r;
    RAND_SEED = RAND_SEED * 214013 + 2531011;
    r = (RAND_SEED >> 16) & 0x7fff;
    if (rand_stack_depth) {
        /* The game is compiled /Od: every function keeps an EBP frame. */
        DWORD *fp = (DWORD *)__builtin_frame_address(1);
        int i;
        maplog_printf(&rand_log, "%08lx %d", (unsigned long)__builtin_return_address(0) - 5, r);
        for (i = 0; i < rand_stack_depth && fp && !IsBadReadPtr(fp, 8); i++) {
            maplog_printf(&rand_log, " <%08lx", fp[1] - 5);
            fp = (DWORD *)fp[0];
        }
        maplog_printf(&rand_log, "\n");
    } else
        maplog_printf(&rand_log, "%08lx %d\n", (unsigned long)__builtin_return_address(0) - 5, r);
    return r;
}

void determinism_init(void)
{
    const char *s = getenv("CIV2_SEED");
    if (s && *s) {
        forced_seed_set = 1;
        forced_seed = (unsigned int)strtoul(s, NULL, 0);
    }
    s = getenv("CIV2_RAND_STACK");
    if (s && *s)
        rand_stack_depth = atoi(s);
    s = getenv("CIV2_RAND_LOG");
    if (s && *s)
        maplog_open(&rand_log, s);
    hook_patch_jmp(ORIG_SRAND, (void *)hooked_srand);
    if (rand_log.base)
        hook_patch_jmp(ORIG_RAND, (void *)hooked_rand);
}
