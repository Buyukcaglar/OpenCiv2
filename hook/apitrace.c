/*
 * API call tracing for comparing builds: with CIV2_APITRACE=FROM-TO, every
 * call civ2.exe makes through its import table, while the game retrieves
 * messages number FROM to TO (as counted by replay.c), is logged by name.
 * The native platform layer logs its API entry points the same way, so the
 * two sequences can be diffed.
 *
 * Each import slot is redirected to a stub:
 *     pushad; push idx; call trace_import; add esp, 4; popad; jmp [orig + 4*idx]
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hook.h"

#define MAX_IMPORTS 1024

static void *orig[MAX_IMPORTS];
static char names[MAX_IMPORTS][48];
static int from = -1, to = -1;
extern int replay_msg_count;

static void __cdecl trace_import(int idx)
{
    if (replay_msg_count >= from && replay_msg_count <= to)
        hook_logf("api %s\n", names[idx]);
}

void apitrace_init(void)
{
    const char *s = getenv("CIV2_APITRACE");
    BYTE *base = (BYTE *)GetModuleHandleA(NULL), *stubs;
    IMAGE_NT_HEADERS *nt;
    IMAGE_IMPORT_DESCRIPTOR *imp;
    int n = 0;
    if (!s || sscanf(s, "%d-%d", &from, &to) != 2)
        return;
    nt = (IMAGE_NT_HEADERS *)(base + ((IMAGE_DOS_HEADER *)base)->e_lfanew);
    imp = (IMAGE_IMPORT_DESCRIPTOR *)(base + nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
    stubs = VirtualAlloc(NULL, MAX_IMPORTS * 24, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    for (; imp->Name; imp++) {
        IMAGE_THUNK_DATA *nm = (IMAGE_THUNK_DATA *)(base + (imp->OriginalFirstThunk ? imp->OriginalFirstThunk : imp->FirstThunk));
        IMAGE_THUNK_DATA *slot = (IMAGE_THUNK_DATA *)(base + imp->FirstThunk);
        if (!_stricmp((char *)(base + imp->Name), "XDaemon.dll"))
            continue;
        for (; nm->u1.AddressOfData && n < MAX_IMPORTS; nm++, slot++) {
            BYTE *p = stubs + n * 24;
            DWORD old;
            if (IMAGE_SNAP_BY_ORDINAL(nm->u1.Ordinal))
                _snprintf(names[n], sizeof names[n], "#%u", (unsigned)IMAGE_ORDINAL(nm->u1.Ordinal));
            else
                _snprintf(names[n], sizeof names[n], "%s", ((IMAGE_IMPORT_BY_NAME *)(base + nm->u1.AddressOfData))->Name);
            orig[n] = (void *)slot->u1.Function;
            p[0] = 0x60;                                            /* pushad */
            p[1] = 0x68; *(DWORD *)(p + 2) = (DWORD)n;              /* push n */
            p[6] = 0xe8; *(DWORD *)(p + 7) = (DWORD)trace_import - (DWORD)(p + 11);
            p[11] = 0x83; p[12] = 0xc4; p[13] = 0x04;               /* add esp, 4 */
            p[14] = 0x61;                                           /* popad */
            p[15] = 0xff; p[16] = 0x25; *(DWORD *)(p + 17) = (DWORD)&orig[n];  /* jmp [orig+n] */
            VirtualProtect(&slot->u1.Function, 4, PAGE_READWRITE, &old);
            slot->u1.Function = (DWORD)p;
            VirtualProtect(&slot->u1.Function, 4, old, &old);
            n++;
        }
    }
    hook_logf("apitrace: %d imports, messages %d-%d\n", n, from, to);
}
