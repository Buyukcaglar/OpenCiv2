/*
 * Compatibility shims for running a 1999 Windows 95 game on wine.
 * They apply to the original and the reconstructed build alike: they change
 * what the operating system reports, never the game.
 *
 * EDIT window extra bytes.  Civ2 superclasses the system EDIT control as
 * "MSEditBoxClass" with cbWndExtra = cbWndExtra(EDIT) + 8, storing the old
 * window procedure at cbWndExtra(EDIT) and its own object pointer 4 bytes
 * later -- but its window procedure reads the object pointer from the fixed
 * offset 10, which is only right when EDIT has 6 extra bytes, as on Windows
 * 95.  Wine's EDIT has 4, so the read returns garbage and founding a city
 * (whose name box is such a control) crashes.  Reporting Windows 95's value
 * puts the game's data at 6 and 10, clear of wine's own bytes 0..3.
 */
#include <string.h>
#include "hook.h"

void *hook_patch_import(const char *dll, const char *func, void *repl);

static DWORD (WINAPI *real_GetClassLongA)(HWND, int);

static DWORD WINAPI compat_GetClassLongA(HWND hwnd, int index)
{
    if (index == GCL_CBWNDEXTRA) {
        char cls[32];
        if (GetClassNameA(hwnd, cls, sizeof cls) && _stricmp(cls, "Edit") == 0)
            return 6;
    }
    return real_GetClassLongA(hwnd, index);
}

void compat_init(void)
{
    real_GetClassLongA = hook_patch_import("USER32.dll", "GetClassLongA", (void *)compat_GetClassLongA);
}
