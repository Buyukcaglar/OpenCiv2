/*
 * Debug-heap release path of the MSVC 4.2 debug CRT (operator delete,
 * _free_dbg, _free_base) and _CrtDbgReport.
 *
 * operator delete, _free_dbg and _free_base are void in the CRT source, but
 * on some paths the original returns whatever was left in EAX (the caller's
 * EAX when the pointer is NULL).  Their bodies take that incoming EAX
 * explicitly and small naked stubs pass it in, so the returned EAX is
 * bit-for-bit the original's.
 */
#include "game.h"

/* _CrtMemBlockHeader */
typedef struct mem_block {
    struct mem_block *next;     /* +0x00 */
    struct mem_block *prev;     /* +0x04 */
    char *file;                 /* +0x08 */
    int line;                   /* +0x0c */
    int size;                   /* +0x10 */
    int use;                    /* +0x14 */
    int request;                /* +0x18 */
    byte gap[4];                /* +0x1c */
} mem_block;                    /* user data at +0x20 */

#define g_crtDbgFlag        (*(byte *)((u8 *)&g.d_00639f70))
#define g_bNoMansLandFill   (*(byte *)((u8 *)&g.d_00639f7c))
#define g_bDeadLandFill     (*(byte *)((u8 *)&g.d_00639f80))
#define g_szBlockUseName    ((char **)0x00639f88)
#define g_pfnAllocHook      (*(alloc_hook_fn *)((u8 *)&g.d_0063a42c))
#define g_lCurAlloc         (*(int *)((u8 *)&g.d_006e547c))
#define g_pLastBlock        (*(mem_block * *)((u8 *)&g.d_006e5470))
#define g_pFirstBlock       (*(mem_block * *)((u8 *)&g.d_006e5478))
#define g_crtheap           (*(HANDLE *)((u8 *)&g.d_006e69e4))

typedef int (__cdecl *alloc_hook_fn)(int, void *, int, int, int, int, int);

#define CRTDBG_CHECK_ALWAYS_DF  4
#define CRTDBG_DELAY_FREE_MEM_DF 2

#define FILE_dbgheap    ((char *)0x0061dca0)    /* "dbgheap.c" */
#define FILE_dbgdel     ((char *)0x0061d758)    /* "dbgdel.cpp" */

#define dbg_break() __asm__ volatile("int3")

/* ------------------------------------------------------------------------ */

/* _CrtDbgReport, declared non-variadic in protos.h */
int __cdecl crt_dbg_report(int type, char *file, int line, char *module, char *format, ...)
    __asm__("___CrtDbgReport");

#define g_crtAssertBusy     (*(LONG *)((u8 *)&g.d_0063a030))
#define g_CrtDbgMode        ((int *)0x0063a038)
#define g_CrtDbgFile        ((HANDLE *)0x0063a048)
#define g_pfnwsprintfA      (*(wsprintf_fn *)((u8 *)&g.d_0063a064))
#define g_pfnReportHook     (*(report_hook_fn *)((u8 *)&g.d_006e6b30))

typedef int (__cdecl *wsprintf_fn)(char *, const char *, ...);
typedef int (__cdecl *report_hook_fn)(int, char *, int *);

/* The original's 0x3028-byte frame is allocated through __chkstk, which
 * touches each stack page from the top down.  The build disables gcc's own
 * stack probes, so the variadic entry point touches the pages below its
 * (small) frame before calling the body that owns the large buffers. */
static int crt_dbg_report_body(int type, char *file, int line, char *module, char *format,
                               va_list args);

/* 0x005f8b70: _CrtDbgReport(type, file, line, module, format, ...) */
int __cdecl crt_dbg_report(int type, char *file, int line, char *module, char *format, ...)
{
    volatile char *frame = (volatile char *)__builtin_frame_address(0);
    va_list args;
    int k;

    for (k = 1; k <= 4; k++)
        (void)frame[-0x1000 * k];
    va_start(args, format);
    return crt_dbg_report_body(type, file, line, module, format, args);
}

static int crt_dbg_report_body(int type, char *file, int line, char *module, char *format,
                               va_list args)
{
    struct {
        char line_msg[0x1000];      /* ebp-0x3008 */
        char out_msg[0x1000];       /* ebp-0x2008 */
        char user_msg[0x1000];      /* ebp-0x1000 */
    } m;
    int retval;
    DWORD written;
    char line_buf[20];
    char *line_str;
    HMODULE user32;

    _memset(m.line_msg, 0, sizeof m.line_msg);
    _memset(m.out_msg, 0, sizeof m.out_msg);
    _memset(m.user_msg, 0, sizeof m.user_msg);

    if (type < 0 || type >= 3)
        return -1;

    if (type == 2 && InterlockedIncrement(&g_crtAssertBusy) > 0) {
        /* recursive assertion: report with wsprintfA only */
        if (g_pfnwsprintfA == NULL) {
            user32 = LoadLibraryA((char *)0x0061e564 /* "user32.dll" */);
            if (user32 == NULL ||
                (g_pfnwsprintfA = (wsprintf_fn)GetProcAddress(user32, (char *)0x0061e558 /* "wsprintfA" */)) == NULL)
                return -1;
        }
        g_pfnwsprintfA(m.out_msg, (char *)0x0061e524 /* "Second Chance Assertion Failed: File %s, Line %d\n" */,
                       file, line);
        OutputDebugStringA(m.out_msg);
        InterlockedDecrement(&g_crtAssertBusy);
        __CrtDbgBreak();
        return -1;
    }

    if (format != NULL && __vsnprintf(m.user_msg, 0xfed, format, args) < 0)
        crt_strcpy(m.user_msg, (char *)0x0061e4f8 /* "_CrtDbgReport: String too long or IO Error" */);
    if (type == 2)
        crt_strcpy(m.line_msg, format != NULL ? (char *)0x0061e4e4 /* "Assertion failed: " */
                                                : (char *)0x0061e424 /* "Assertion failed!" */);
    crt_strcat(m.line_msg, m.user_msg);
    if (type == 2) {
        if (g_CrtDbgMode[type] & 1)
            crt_strcat(m.line_msg, (char *)0x0061e4e0 /* "\r" */);
        crt_strcat(m.line_msg, (char *)0x0061e300 /* "\n" */);
    }
    if (file != NULL) {
        if (__snprintf(m.out_msg, 0x1000, (char *)0x0061e4d4 /* "%s(%d) : %s" */, file, line, m.line_msg) < 0)
            crt_strcpy(m.out_msg, (char *)0x0061e4f8);
    } else {
        crt_strcpy(m.out_msg, m.line_msg);
    }

    if (g_pfnReportHook != NULL && g_pfnReportHook(type, m.out_msg, &retval) != 0) {
        if (type == 2)
            InterlockedDecrement(&g_crtAssertBusy);
        return retval;
    }
    if ((g_CrtDbgMode[type] & 1) && g_CrtDbgFile[type] != INVALID_HANDLE_VALUE)
        WriteFile(g_CrtDbgFile[type], m.out_msg, _strlen(m.out_msg), &written, NULL);
    if (g_CrtDbgMode[type] & 2)
        OutputDebugStringA(m.out_msg);
    if (g_CrtDbgMode[type] & 4) {
        if (line != 0)
            line_str = (char *)__itoa(line, line_buf, 10);
        else
            line_str = NULL;
        retval = _CrtMessageWindow(type, file, line_str, module, m.user_msg);
        if (type == 2)
            InterlockedDecrement(&g_crtAssertBusy);
        return retval;
    }
    if (type == 2)
        InterlockedDecrement(&g_crtAssertBusy);
    return 0;
}

/* ------------------------------------------------------------------------ */

/* 0x005fcbf0: _free_base(p) */
int __cdecl free_base_body(int eax_in, void *p)
{
    int region;
    int group;
    int entry;

    if (p == NULL)
        return eax_in;
    entry = ___sbh_find_block(p, &group, &region);
    if (entry != 0)
        return ___sbh_free_block(group, region, entry);
    return HeapFree(g_crtheap, 0, p);
}

__attribute__((naked)) BOOL __cdecl __free_base(void *p)
{
    __asm__ volatile(
        "pushl 4(%esp)\n\t"
        "pushl %eax\n\t"
        "call _free_base_body\n\t"
        "addl $8, %esp\n\t"
        "ret");
}

/* 0x005f4f90: _free_dbg(p, blockUse) */
int __cdecl free_dbg_body(int eax_in, void *p, int use)
{
    mem_block *h;
    int r;

    r = eax_in;
    if (g_crtDbgFlag & CRTDBG_CHECK_ALWAYS_DF) {
        r = __CrtCheckMemory();
        if (r == 0) {
            r = crt_dbg_report(2, FILE_dbgheap, 0x3e1, NULL, (char *)0x0061dcac /* "_CrtCheckMemory()" */);
            if (r == 1)
                dbg_break();
        }
    }
    if (p == NULL)
        return r;

    if (g_pfnAllocHook(3, p, 0, use, 0, 0, 0) == 0) {
        r = crt_dbg_report(0, NULL, 0, NULL, (char *)0x0061dc40 /* "%s" */,
                           (char *)0x0061df48 /* "Client hook free failure.\n" */);
        if (r == 1)
            dbg_break();
        return r;
    }

    if (__CrtIsValidHeapPointer(p) == 0 &&
        crt_dbg_report(2, FILE_dbgheap, 0x3f3, NULL, (char *)0x0061ddb0 /* "_CrtIsValidHeapPointer(pUserData)" */) == 1)
        dbg_break();

    h = (mem_block *)((byte *)p - 0x20);
    if ((h->use & 0xffff) != 4 && h->use != 1 && (h->use & 0xffff) != 2 && h->use != 3 &&
        crt_dbg_report(2, FILE_dbgheap, 0x3f9, NULL,
                       (char *)0x0061d764 /* "_BLOCK_TYPE_IS_VALID(pHead->nBlockUse)" */) == 1)
        dbg_break();

    if (!(g_crtDbgFlag & CRTDBG_CHECK_ALWAYS_DF)) {
        if (_CheckBytes(h->gap, g_bNoMansLandFill, 4) == 0 &&
            crt_dbg_report(1, NULL, 0, NULL, (char *)0x0061df1c /* "DAMAGE: before %hs block (#%d) at 0x%08X.\n" */,
                           g_szBlockUseName[h->use & 0xffff], h->request, (byte *)h + 0x20) == 1)
            dbg_break();
        if (_CheckBytes((byte *)h + 0x20 + h->size, g_bNoMansLandFill, 4) == 0 &&
            crt_dbg_report(1, NULL, 0, NULL, (char *)0x0061def0 /* "DAMAGE: after %hs block (#%d) at 0x%08X.\n" */,
                           g_szBlockUseName[h->use & 0xffff], h->request, (byte *)h + 0x20) == 1)
            dbg_break();
    }

    if (h->use == 3) {      /* _IGNORE_BLOCK */
        if ((h->line != (int)0xfedcbabc || h->request != 0) &&
            crt_dbg_report(2, FILE_dbgheap, 0x40e, NULL,
                           (char *)0x0061deb0 /* "pHead->nLine == IGNORE_LINE && pHead->lRequest == IGNORE_REQ" */) == 1)
            dbg_break();
        _memset(h, g_bDeadLandFill, h->size + 0x24);
        return __free_base(h);
    }

    if (h->use == 2 && use == 1)
        use = 2;
    if (h->use != use &&
        crt_dbg_report(2, FILE_dbgheap, 0x41b, NULL, (char *)0x0061de90 /* "pHead->nBlockUse == nBlockUse" */) == 1)
        dbg_break();

    g_lCurAlloc -= h->size;

    if (g_crtDbgFlag & CRTDBG_DELAY_FREE_MEM_DF) {
        h->use = 0;     /* _FREE_BLOCK */
        return (int)_memset((byte *)h + 0x20, g_bDeadLandFill, h->size);
    }

    if (h->next != NULL) {
        h->next->prev = h->prev;
    } else {
        if (g_pLastBlock != h &&
            crt_dbg_report(2, FILE_dbgheap, 0x42a, NULL, (char *)0x0061de78 /* "_pLastBlock == pHead" */) == 1)
            dbg_break();
        g_pLastBlock = h->prev;
    }
    if (h->prev != NULL) {
        h->prev->next = h->next;
    } else {
        if (g_pFirstBlock != h &&
            crt_dbg_report(2, FILE_dbgheap, 0x434, NULL, (char *)0x0061de60 /* "_pFirstBlock == pHead" */) == 1)
            dbg_break();
        g_pFirstBlock = h->next;
    }
    _memset(h, g_bDeadLandFill, h->size + 0x24);
    return __free_base(h);
}

__attribute__((naked)) i32 __cdecl __free_dbg(void *p, int use)
{
    __asm__ volatile(
        "pushl 8(%esp)\n\t"
        "pushl 8(%esp)\n\t"
        "pushl %eax\n\t"
        "call _free_dbg_body\n\t"
        "addl $12, %esp\n\t"
        "ret");
}

/* 0x005f23c0: operator delete(p) */
int __cdecl operator_delete_body(int eax_in, void *p)
{
    mem_block *h;

    if (p == NULL)
        return eax_in;
    h = (mem_block *)((byte *)p - 0x20);
    if ((h->use & 0xffff) != 4 && h->use != 1 && (h->use & 0xffff) != 2 && h->use != 3 &&
        crt_dbg_report(2, FILE_dbgdel, 0x2f, NULL,
                       (char *)0x0061d764 /* "_BLOCK_TYPE_IS_VALID(pHead->nBlockUse)" */) == 1)
        dbg_break();
    return __free_dbg(p, h->use);
}

__attribute__((naked)) i32 __cdecl operator_delete(void *p)
{
    __asm__ volatile(
        "pushl 4(%esp)\n\t"
        "pushl %eax\n\t"
        "call _operator_delete_body\n\t"
        "addl $8, %esp\n\t"
        "ret");
}
