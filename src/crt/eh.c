/*
 * C++ exception-handling support of the MSVC 4.2 runtime (frame handler,
 * catch/unwind machinery, array unwinding) and the unhandled-exception
 * filter.
 *
 * Civilization II never throws, and the reconstructed game code drops the
 * exception-frame registration that would route an exception into
 * ___CxxFrameHandler, so the catch/unwind machinery is unreachable.  Those
 * functions are stubs that report and terminate (same calling convention and
 * argument pop count as the original).  `__CallSettingFrame@12` (0x005f8830)
 * cannot be named in C and is only called from the unreachable machinery, so
 * it is not defined here.
 *
 * Implemented faithfully because they are reachable outside an exception or
 * trivially small:
 *   FUN_005f1d95 / FUN_005f1d9e  _NLG_Notify (debugger notification; called
 *                                from __local_unwind2 and _CrtMessageWindow)
 *   _CallMemberFunction0, FUN_005f1e10, FUN_005f1e20  (thiscall trampolines)
 *   AdjustPointer
 *   __CxxUnhandledExceptionFilter  (installed with SetUnhandledExceptionFilter
 *                                   at start-up; runs on any crash)
 */
#include "game.h"

static volatile int eh_never;

/* Report an impossible entry into the EH machinery and terminate. */
static void eh_unreachable(const char *name)
{
    OutputDebugStringA("civ2 recon: unreachable C++ EH runtime function called: ");
    OutputDebugStringA(name);
    OutputDebugStringA("\n");
    if (eh_never == 0)
        ExitProcess(3);
}

/* ---- faithful ---------------------------------------------------------- */

/* 0x005f1d95: _NLG_Notify1 -- record ECX (frame data), EAX (target address)
 * and EBP in _NLG_Destination (0x639e38) for the debugger; pops 4 bytes. */
__attribute__((naked)) i32 __stdcall FUN_005f1d95(i32 param_1)
{
    __asm__ volatile(
        "pushl %ebx\n\t"
        "pushl %ecx\n\t"
        "movl $0x00639e38, %ebx\n\t"
        "movl %ecx, 8(%ebx)\n\t"
        "movl %eax, 4(%ebx)\n\t"
        "movl %ebp, 12(%ebx)\n\t"
        "popl %ecx\n\t"
        "popl %ebx\n\t"
        "ret $4");
}

/* 0x005f1d9e: _NLG_Notify -- as above, but the frame data is the caller's
 * first argument ([ebp+8]). */
__attribute__((naked)) void __stdcall FUN_005f1d9e(i32 param_1)
{
    __asm__ volatile(
        "pushl %ebx\n\t"
        "pushl %ecx\n\t"
        "movl $0x00639e38, %ebx\n\t"
        "movl 8(%ebp), %ecx\n\t"
        "movl %ecx, 8(%ebx)\n\t"
        "movl %eax, 4(%ebx)\n\t"
        "movl %ebp, 12(%ebx)\n\t"
        "popl %ecx\n\t"
        "popl %ebx\n\t"
        "ret $4");
}

/* 0x005f1e00: _CallMemberFunction0(pthis, pfn): tail-call pfn as thiscall
 * with ECX = pthis, the two arguments removed from the stack. */
__attribute__((naked)) void __stdcall _CallMemberFunction0(void *param_1, void *param_2)
{
    __asm__ volatile(
        "popl %eax\n\t"
        "popl %ecx\n\t"
        "xchgl (%esp), %eax\n\t"
        "jmp *%eax\n\t"
        "ret $8");          /* not reached; marks the 8-byte pop for tools */
}

/* 0x005f1e10: _CallMemberFunction1(pthis, pfn, arg) -- same trampoline; the
 * member function pops its own argument. */
__attribute__((naked)) void __cdecl FUN_005f1e10(void)
{
    __asm__ volatile(
        "popl %eax\n\t"
        "popl %ecx\n\t"
        "xchgl (%esp), %eax\n\t"
        "jmp *%eax\n\t"
        "ret");             /* not reached */
}

/* 0x005f1e20: _CallMemberFunction2(pthis, pfn, arg1, arg2) */
__attribute__((naked)) void __cdecl FUN_005f1e20(void)
{
    __asm__ volatile(
        "popl %eax\n\t"
        "popl %ecx\n\t"
        "xchgl (%esp), %eax\n\t"
        "jmp *%eax\n\t"
        "ret");             /* not reached */
}

/* PMD: pointer-to-member displacement */
typedef struct { int mdisp, pdisp, vdisp; } eh_pmd;

/* 0x005f87e0: AdjustPointer(pThis, pmd) */
void * __cdecl AdjustPointer(void *pthis, eh_pmd *pmd)
{
    char *ret = (char *)pthis + pmd->mdisp;

    if (pmd->pdisp >= 0)
        ret += *(int *)(*(char **)((char *)pthis + pmd->pdisp) + pmd->vdisp) + pmd->pdisp;
    return ret;
}

#define g_pOldExceptFilter (*(LPTOP_LEVEL_EXCEPTION_FILTER *)((u8 *)&g.d_006e55ac))

/* 0x00600fa0: __CxxUnhandledExceptionFilter(pPtrs) */
int __stdcall __CxxUnhandledExceptionFilter(EXCEPTION_POINTERS *ptrs)
{
    EXCEPTION_RECORD *rec = ptrs->ExceptionRecord;

    if (rec->ExceptionCode == 0xe06d7363 && rec->NumberParameters == 3 &&
        rec->ExceptionInformation[0] == 0x19930520) {
        terminate();
        return 1;
    }
    if (g_pOldExceptFilter != NULL && _ValidateExecute(g_pOldExceptFilter) != 0)
        return g_pOldExceptFilter(ptrs);
    return 0;
}

/* ---- unreachable stubs ------------------------------------------------- */

/* 0x005f1dc0 */
void __stdcall _JumpToContinuation(void *target, void *rn)
{
    eh_unreachable("_JumpToContinuation");
}

/* 0x005f1e30 */
void __stdcall _UnwindNestedFrames(void *rn, void *rec)
{
    eh_unreachable("_UnwindNestedFrames");
}

/* 0x005f1e90: entered from the __ehhandler thunks with EAX = FuncInfo. */
i32 __cdecl ___CxxFrameHandler(void *rec, void *rn, void *ctx, void *dc)
{
    eh_unreachable("___CxxFrameHandler");
    return 0;
}

/* 0x005f1f10 */
void * __cdecl _CallCatchBlock2(void *rn, void *funcinfo, void *handler, int catchdepth, ulong nlg)
{
    eh_unreachable("_CallCatchBlock2");
    return NULL;
}

/* 0x005f1f80 */
int __cdecl CatchGuardHandler(void *rec, void *rn, void *ctx, void *dc)
{
    eh_unreachable("CatchGuardHandler");
    return 0;
}

/* 0x005f1fc0 */
int __cdecl _CallSETranslator(void *rec, void *rn, void *ctx, void *dc, void *funcinfo,
                              int catchdepth, void *pmarker)
{
    eh_unreachable("_CallSETranslator");
    return 0;
}

/* 0x005f20a0 */
int __cdecl TranslatorGuardHandler(void *rec, void *rn, void *ctx, void *dc)
{
    eh_unreachable("TranslatorGuardHandler");
    return 0;
}

/* 0x005f2540: only reached when a constructor throws inside
 * `eh vector constructor/destructor iterator'. */
void __stdcall __ArrayUnwind(void *ptr, uint size, int count, void *dtor)
{
    eh_unreachable("__ArrayUnwind");
}

/* 0x005f79a0 */
int __cdecl ___InternalCxxFrameHandler(void *rec, void *rn, void *ctx, void *dc, void *funcinfo,
                                       int catchdepth, void *pmarker, int recursive)
{
    eh_unreachable("___InternalCxxFrameHandler");
    return 0;
}

/* 0x005f7ac0 */
void __cdecl FindHandler(void *rec, void *rn, void *ctx, void *dc, void *funcinfo,
                         int recursive, int catchdepth, void *pmarker)
{
    eh_unreachable("FindHandler");
}

/* 0x005f7d70 */
void __cdecl FindHandlerForForeignException(void *rec, void *rn, void *ctx, void *dc, void *funcinfo,
                                            int curstate, int catchdepth, void *pmarker)
{
    eh_unreachable("FindHandlerForForeignException");
}

/* 0x005f7e90 */
void * __cdecl GetRangeOfTrysToCheck(void *funcinfo, int catchdepth, int curstate,
                                     uint *pstart, uint *pend)
{
    eh_unreachable("GetRangeOfTrysToCheck");
    return NULL;
}

/* 0x005f7f80 */
int __cdecl TypeMatch(void *handler, void *catchable, void *throwinfo)
{
    eh_unreachable("TypeMatch");
    return 0;
}

/* 0x005f8050 */
void __cdecl ___FrameUnwindToState(void *rn, void *dc, void *funcinfo, int targetstate)
{
    eh_unreachable("___FrameUnwindToState");
}

/* 0x005f81b0 */
void __cdecl CatchIt(void *rec, void *rn, void *ctx, void *dc, void *funcinfo, void *handler,
                     void *catchable, void *tryblock, int catchdepth, void *pmarker)
{
    eh_unreachable("CatchIt");
}

/* 0x005f8290 */
void * __cdecl CallCatchBlock(void *rec, void *rn, void *ctx, void *funcinfo, void *handler,
                              int catchdepth, ulong nlg)
{
    eh_unreachable("CallCatchBlock");
    return NULL;
}

/* 0x005f8460 */
void __cdecl BuildCatchObject(void *rec, void *rn, void *handler, void *catchable)
{
    eh_unreachable("BuildCatchObject");
}

/* 0x005f8740 */
void __cdecl DestructExceptionObject(void *rec, int throw_seen)
{
    eh_unreachable("DestructExceptionObject");
}
