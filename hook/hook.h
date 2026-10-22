#ifndef CIV2_HOOK_H
#define CIV2_HOOK_H
#include <windows.h>

struct maplog {
    char *base;
    unsigned int pos, cap;
};
int maplog_open(struct maplog *l, const char *path);
void maplog_printf(struct maplog *l, const char *fmt, ...);

void hook_logf(const char *fmt, ...);
void hook_patch_jmp(DWORD from, void *to);
void crash_init(void);
void compat_init(void);
void *hook_patch_import(const char *dll, const char *func, void *repl);
void determinism_init(void);
void replay_init(void);
void gditrace_init(void);
void apitrace_init(void);
void proctrace_init(void);
void recon_install(void);
void stackprobe_init(void);

#endif
