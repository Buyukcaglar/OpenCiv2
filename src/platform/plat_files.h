/*
 * Services of the platform layer used by the game's C runtime
 * (src/native/crt.cpp): Windows paths, the clock and diagnostics.
 *
 * Windows paths map to host paths the way Wine maps them: "Z:\a\b" is
 * "/a/b"; the game directory is the current directory; any other drive
 * letter is the game directory too.  Names match case-insensitively.
 */
#ifndef CIV2_PLAT_FILES_H
#define CIV2_PLAT_FILES_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Host path for a Windows path; for_create: the last component may not exist. */
void plat_host_path(const char *win, char *host, size_t n, int for_create);
int plat_chdir(const char *win);
int plat_getcwd(char *win, int n);
int64_t plat_time(void);                /* seconds since 1970 (virtual in replay) */
void plat_trace_rand(unsigned value, const char *caller);   /* caller: function name */
unsigned plat_srand(unsigned seed);         /* the seed to use (CIV2_SEED forces one) */
void plat_suspicious(const char *fmt, ...);  /* see plat.h */
void plat_fatal(const char *fmt, ...);

#ifdef __cplusplus
}
#endif
#endif
