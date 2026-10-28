/* CIV2_STACKPROBE=ADDR:OFF:LEN[,...] (hex): on every entry to the original
 * function at ADDR, log the LEN bytes at entry ESP - OFF -- the stale stack
 * a local at that frame offset (Ghidra's local_OFF) holds before the
 * function writes it.  Used to find what the 1997 code reads from locals it
 * never initialises (tools/gen_c.py FRAME_PRESETS).  The return address
 * and the first three stack arguments are logged too.
 *
 * The entry byte becomes int3; a vectored handler logs, puts the byte back,
 * single-steps the instruction and re-arms the breakpoint.
 *
 * CIV2_CALL_LOG=FILE: the same breakpoints log the sounds the game plays
 * and the videos it looks for, which the reference cannot play (no audio
 * device, no video files or Indeo codec): every call of snd_play_effect
 * (0046e020: effect, mode, loop) and every video path file_resolve_path
 * (00564713) is asked for.  The native builds write the same lines
 * (src/platform/replay.c); harness/compare.py compares them. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hook.h"

#define MAX_PROBES 8

static struct probe {
    DWORD addr, off, len;
    BYTE saved;
    unsigned calls;
    int kind;                   /* 0 stack probe, 1 sound, 2 video path */
} probes[MAX_PROBES];
static FILE *call_log;

#define SND_PLAY_EFFECT 0x46e020
#define FILE_RESOLVE_PATH 0x564713

/* A video's path (as the native build's replay_log_video decides). */
static int is_video_path(const char *p)
{
    size_t n = strlen(p);
    return n >= 4 && _stricmp(p + n - 4, ".avi") == 0;
}
static int nprobes;
static struct probe *stepping;

static void arm(struct probe *p, int on)
{
    DWORD old;
    BYTE *b = (BYTE *)p->addr;
    VirtualProtect(b, 1, PAGE_EXECUTE_READWRITE, &old);
    *b = on ? 0xCC : p->saved;
    VirtualProtect(b, 1, old, &old);
    FlushInstructionCache(GetCurrentProcess(), b, 1);
}

static LONG CALLBACK handler(EXCEPTION_POINTERS *e)
{
    DWORD code = e->ExceptionRecord->ExceptionCode;
    CONTEXT *c = e->ContextRecord;
    int i;
    if (code == EXCEPTION_SINGLE_STEP && stepping) {
        arm(stepping, 1);
        stepping = NULL;
        return EXCEPTION_CONTINUE_EXECUTION;
    }
    if (code != EXCEPTION_BREAKPOINT)
        return EXCEPTION_CONTINUE_SEARCH;
    for (i = 0; i < nprobes; i++) {
        struct probe *p = &probes[i];
        char line[400];
        int n, k;
        const BYTE *s;
        if ((DWORD)e->ExceptionRecord->ExceptionAddress != p->addr)
            continue;
        if (p->kind == 1) {
            const DWORD *a = (const DWORD *)c->Esp;
            fprintf(call_log, "sound %ld %ld %ld\n", (long)a[1], (long)a[2], (long)a[3]);
            fflush(call_log);   /* (the replay ends with ExitProcess) */
            goto step;
        }
        if (p->kind == 2) {
            const char *path = (const char *)((const DWORD *)c->Esp)[1];
            if (path && is_video_path(path))
                fprintf(call_log, "video %s\n", path);
            fflush(call_log);
            goto step;
        }
        s = (const BYTE *)(c->Esp - p->off);
        n = sprintf(line, "stackprobe %06lx #%u from %lx args %lx %lx %lx local_%lx:", p->addr, ++p->calls, ((DWORD *)c->Esp)[0],
                    ((DWORD *)c->Esp)[1], ((DWORD *)c->Esp)[2], ((DWORD *)c->Esp)[3], p->off);
        for (k = 0; k < (int)p->len && n < (int)sizeof line - 4; k += 4)
            n += sprintf(line + n, " %08lx", *(const DWORD *)(s + k));
        hook_logf("%s\n", line);
    step:
        arm(p, 0);
        c->Eip = p->addr;
        c->EFlags |= 0x100;     /* trap after the restored instruction */
        stepping = p;
        return EXCEPTION_CONTINUE_EXECUTION;
    }
    return EXCEPTION_CONTINUE_SEARCH;
}

void stackprobe_init(void)
{
    const char *e = getenv("CIV2_STACKPROBE"), *cl = getenv("CIV2_CALL_LOG");
    char *q;
    if (cl && *cl && (call_log = fopen(cl, "w")) != NULL) {
        probes[nprobes].addr = SND_PLAY_EFFECT;
        probes[nprobes++].kind = 1;
        probes[nprobes].addr = FILE_RESOLVE_PATH;
        probes[nprobes++].kind = 2;
        for (int i = 0; i < nprobes; i++)
            probes[i].saved = *(BYTE *)probes[i].addr;
    }
    while (e && *e && nprobes < MAX_PROBES) {
        struct probe *p = &probes[nprobes];
        p->addr = strtoul(e, &q, 16);
        if (*q != ':')
            break;
        p->off = strtoul(q + 1, &q, 16);
        p->len = *q == ':' ? strtoul(q + 1, &q, 16) : 4;
        p->saved = *(BYTE *)p->addr;
        nprobes++;
        e = *q == ',' ? q + 1 : q;
    }
    if (!nprobes)
        return;
    AddVectoredExceptionHandler(1, handler);
    for (int i = 0; i < nprobes; i++)
        arm(&probes[i], 1);
    hook_logf("stackprobe: %d probes\n", nprobes);
}
