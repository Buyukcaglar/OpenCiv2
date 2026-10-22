/* CIV2_STACKPROBE=ADDR:OFF:LEN[,...] (hex): on every entry to the original
 * function at ADDR, log the LEN bytes at entry ESP - OFF -- the stale stack
 * a local at that frame offset (Ghidra's local_OFF) holds before the
 * function writes it.  Used to find what the 1997 code reads from locals it
 * never initialises (tools/gen_c.py FRAME_PRESETS).  The return address
 * and the first three stack arguments are logged too.
 *
 * The entry byte becomes int3; a vectored handler logs, puts the byte back,
 * single-steps the instruction and re-arms the breakpoint. */
#include <stdio.h>
#include <stdlib.h>
#include "hook.h"

#define MAX_PROBES 8

static struct probe {
    DWORD addr, off, len;
    BYTE saved;
    unsigned calls;
} probes[MAX_PROBES];
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
        s = (const BYTE *)(c->Esp - p->off);
        n = sprintf(line, "stackprobe %06lx #%u from %lx args %lx %lx %lx local_%lx:", p->addr, ++p->calls, ((DWORD *)c->Esp)[0],
                    ((DWORD *)c->Esp)[1], ((DWORD *)c->Esp)[2], ((DWORD *)c->Esp)[3], p->off);
        for (k = 0; k < (int)p->len && n < (int)sizeof line - 4; k += 4)
            n += sprintf(line + n, " %08lx", *(const DWORD *)(s + k));
        hook_logf("%s\n", line);
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
    const char *e = getenv("CIV2_STACKPROBE");
    char *q;
    if (!e || !*e)
        return;
    while (*e && nprobes < MAX_PROBES) {
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
