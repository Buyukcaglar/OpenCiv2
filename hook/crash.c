/*
 * Crash reporting: logs every access violation / illegal instruction with
 * registers and the code addresses found on the stack, so a failure in the
 * reconstructed build can be attributed to a function (see tools/symbolize.py).
 */
#include "hook.h"

static int is_code(DWORD a)
{
    return (a >= 0x00401000 && a < 0x00620000) || (a >= 0x00800000 && a < 0x00a00000);
}

static LONG CALLBACK crash_handler(EXCEPTION_POINTERS *ep)
{
    EXCEPTION_RECORD *er = ep->ExceptionRecord;
    CONTEXT *c = ep->ContextRecord;
    DWORD *sp;
    int i, n = 0;
    if (er->ExceptionCode != EXCEPTION_ACCESS_VIOLATION && er->ExceptionCode != EXCEPTION_ILLEGAL_INSTRUCTION &&
        er->ExceptionCode != EXCEPTION_INT_DIVIDE_BY_ZERO && er->ExceptionCode != EXCEPTION_STACK_OVERFLOW &&
        er->ExceptionCode != EXCEPTION_PRIV_INSTRUCTION &&
        er->ExceptionCode != EXCEPTION_BREAKPOINT)
        return EXCEPTION_CONTINUE_SEARCH;
    hook_logf("EXCEPTION %08lx at eip=%08lx (info %08lx %08lx)\n", er->ExceptionCode, c->Eip,
              er->NumberParameters > 0 ? er->ExceptionInformation[0] : 0,
              er->NumberParameters > 1 ? er->ExceptionInformation[1] : 0);
    hook_logf("  eax=%08lx ebx=%08lx ecx=%08lx edx=%08lx esi=%08lx edi=%08lx ebp=%08lx esp=%08lx\n",
              c->Eax, c->Ebx, c->Ecx, c->Edx, c->Esi, c->Edi, c->Ebp, c->Esp);
    sp = (DWORD *)c->Esp;
    for (i = 0; i < 2048 && n < 40; i++) {
        if (IsBadReadPtr(sp + i, 4))
            break;
        if (is_code(sp[i])) {
            hook_logf("  stack+%04x: %08lx\n", i * 4, sp[i]);
            n++;
        }
    }
    return EXCEPTION_CONTINUE_SEARCH;
}

void crash_init(void)
{
    AddVectoredExceptionHandler(1, crash_handler);
}
