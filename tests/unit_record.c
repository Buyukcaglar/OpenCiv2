/*
 * The unit tests' recorder: linked into the recording build (build_native.py
 * --target linux32rec), whose game and platform functions are compiled with
 * -finstrument-functions and call the two hooks below on entry and exit.
 * While a replay runs, it records calls of the game's functions as cases
 * (tests/unit_format.h): the arguments and the state at entry, the return
 * value (the function's return address is pointed at a trampoline that
 * catches eax and edx) and the state at exit.  A call that reaches the
 * platform layer (windows, drawing, files, the clock: anything but the rand()
 * trace) is not a case: the runner has none of that.
 *
 * Which calls: per function the 1st, 2nd, 3rd, 4th, 6th, 9th ... call (each
 * about 1.5 times the last), at most CIV2_UNITREC_MAX cases per function
 * and replay and CIV2_UNITREC_TOTAL with the other replays'.  Environment:
 *   CIV2_UNITREC_OUT   the cases (gzip), required
 *   CIV2_UNITREC_SIGS  the functions (tools/unit_sigs.py), required
 *   CIV2_UNITREC_TEXTMASK  where the game's data holds text (tests/unit/textmask.tsv), required
 *   CIV2_UNITREC_MAX   cases per function (default 6)
 *   CIV2_UNITREC_HAVE  cases other replays have per function (symbol, count)
 *   CIV2_UNITREC_TOTAL cases per function with those (default 16)
 * At exit, per function: calls, cases, calls not taken (impure, arguments
 * that point elsewhere than the game's data, the map or the stack) on
 * CIV2_UNITREC_OUT.txt.
 */
#include <malloc.h>
#include <unistd.h>
#include "unit_format.h"

#define NOI __attribute__((no_instrument_function))

typedef struct Fn {
    uint32_t addr;
    char *name, *file;
    char ret;
    int nwords;
    char words[24];
    uint32_t calls, next, attempts, kept, impure, rejected, mismatched, have;
} Fn;

#define HASH 16384
static Fn *table[HASH];
static Fn *fns;
static int nfns;

typedef struct Frame {
    Fn *fn;
    uint32_t ebp, call, ret_addr;
    int impure;
    uint32_t word[24], kind[24], a[24], b[24];
    uint32_t win_lo, win_len;           /* the stack the pointer arguments point into */
    uint8_t *win_in;
    uint8_t *state[UT_REGIONS];
    uint32_t cap[UT_REGIONS], size[UT_REGIONS];
} Frame;

#define MAXDEPTH 48
static Frame frames[MAXDEPTH];
static int depth;           /* frames being recorded */
static int started, disabled;
static uint32_t win_main_addr, plat_begin, stack_top;
static gzFile out;
static int max_cases = 6, max_total = 16;
static uint8_t *chain[UT_REGIONS];      /* the previous case's input */
static uint32_t chain_size[UT_REGIONS], chain_cap[UT_REGIONS];
static uint8_t *scratch[UT_REGIONS];
static uint8_t *init_data;              /* the game's data as the initializers left it */
static uint32_t scratch_cap[UT_REGIONS];
static uint32_t cases;
static const char *impure_by[64];       /* which platform functions made calls impure */
static uint32_t impure_count[64];
static uint32_t whitelist[8];
static int nwhite;
/* Calls of these are not cases: the C runtime's heap (allocating, freeing)
   and the functions that change state outside the game's data (their
   static variables: tools/unit_sigs.py --statics lists them). */
static const char *const outside[] = {
    "heap_alloc", "heap_free", "_Z15lang_load_rulesv", "_Z17text_open_sectionPKcS0_",
    "_Z22text_open_file_sectionPKcS0_", "_Z19lang_section_openedPKcS0_i", "_Z19lang_section_closedv",
    "_Z17lang_section_linePc", "_Z15lang_add_labelsi", "_ZL11set_englishPKcS0_", "_ZL14export_englishv",
    "_ZL16add_descriptionsv", "_ZL16load_translationv", "_ZL17add_file_sectionsPKc", "_Z7_atexitPFvvE",
    "_Z7_fcloseP8_IO_FILE", "_Z8__fsopenPKcS0_i", 0};
static uint32_t heapfns[32];
static int nheap;

void __cyg_profile_func_enter(void *fn, void *site) NOI;
void __cyg_profile_func_exit(void *fn, void *site) NOI;

static NOI Fn *find(uint32_t addr)
{
    uint32_t h = (addr >> 2) & (HASH - 1);
    while (table[h]) {
        if (table[h]->addr == addr)
            return table[h];
        h = (h + 1) & (HASH - 1);
    }
    return 0;
}

static NOI void grow(uint8_t **p, uint32_t *cap, uint32_t n)
{
    if (*cap < n) {
        *p = (uint8_t *)realloc(*p, n);
        *cap = n;
    }
}

/* The state now, text and the map's pointers masked. */
static NOI void snapshot(uint8_t **buf, uint32_t *cap, uint32_t *size)
{
    int r;
    ut_region_sizes(size);
    for (r = 0; r < UT_REGIONS; r++) {
        grow(&buf[r], &cap[r], size[r] ? size[r] : 1);
        if (size[r])
            memcpy(buf[r], ut_region_ptr(r), size[r]);
    }
    ut_mask_text(buf[0], init_data);
    ut_mask_fixed(buf[0]);
}

static NOI const char *sym_name(uint32_t addr)
{
    int lo = 0, hi = ut_nsyms - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (ut_syms[mid].addr <= addr && addr < ut_syms[mid].addr + (ut_syms[mid].size ? ut_syms[mid].size : 1))
            return ut_syms[mid].name;
        if (ut_syms[mid].addr < addr)
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    return "?";
}

static NOI void report(void)
{
    FILE *f;
    char path[1024];
    int i;
    if (!out)
        return;
    gzclose(out);
    out = 0;
    snprintf(path, sizeof path, "%s.txt", getenv("CIV2_UNITREC_OUT"));
    f = fopen(path, "w");
    if (!f)
        return;
    fprintf(f, "# function\tcalls\tcases\tattempts\timpure\trejected\tmismatched\n");
    for (i = 0; i < nfns; i++)
        if (fns[i].calls)
            fprintf(f, "%s\t%u\t%u\t%u\t%u\t%u\t%u\n", fns[i].name, fns[i].calls, fns[i].kept, fns[i].attempts,
                    fns[i].impure, fns[i].rejected, fns[i].mismatched);
    for (i = 0; i < 64 && impure_by[i]; i++)
        fprintf(f, "# impure by %s\t%u\n", impure_by[i], impure_count[i]);
    fprintf(f, "# cases %u\n", cases);
    fclose(f);
}

static NOI void init(void)
{
    const char *sigs = getenv("CIV2_UNITREC_SIGS"), *outp = getenv("CIV2_UNITREC_OUT"), *m = getenv("CIV2_UNITREC_MAX");
    const char *mask = getenv("CIV2_UNITREC_TEXTMASK");
    static const char *white[] = {"plat_trace_rand", "plat_log", "plat_suspicious", 0};
    FILE *f, *maps;
    char line[2048];
    int i;
    extern void plat_text_begin(void);
    /* the heap 256 MB further than the runner's will be: a pointer into it
       in a recorded state points to nothing there (a case that follows one
       crashes, and is not kept), never into the runner's own heap; large
       blocks there too, not where the runner's mmap puts its own */
    static void *volatile shift;
    disabled = 1;
    mallopt(M_MMAP_MAX, 0);
    shift = malloc(256 << 20);  /* kept: the heap goes on after it (its pages never touched) */
    mallopt(M_MMAP_MAX, 65536);
    mallopt(M_MMAP_THRESHOLD, 16 << 20);
    if (!shift)
        return;
    if (!sigs || !outp || !mask || !ut_load_textmask(mask))
        return;
    if (m)
        max_cases = atoi(m);
    if (getenv("CIV2_UNITREC_TOTAL"))
        max_total = atoi(getenv("CIV2_UNITREC_TOTAL"));
    if (!ut_load_symbols())
        return;
    f = fopen(sigs, "r");
    if (!f)
        return;
    fns = (Fn *)calloc(8192, sizeof *fns);
    while (fgets(line, sizeof line, f) && nfns < 8192) {
        char *name = strtok(line, "\t\n"), *file = strtok(0, "\t\n"), *ret = strtok(0, "\t\n"), *words = strtok(0, "\t\n");
        Fn *fn = &fns[nfns];
        uint32_t h;
        void *a;
        if (!words || !(a = ut_lookup(name)))
            continue;
        fn->addr = (uint32_t)(uintptr_t)a;
        fn->name = strdup(name);
        fn->file = strdup(file);
        fn->ret = ret[0];
        if (strcmp(words, "-"))
            snprintf(fn->words, sizeof fn->words, "%s", words);
        fn->nwords = (int)strlen(fn->words);
        fn->next = 1;
        for (h = (fn->addr >> 2) & (HASH - 1); table[h]; h = (h + 1) & (HASH - 1))
            ;
        table[h] = fn;
        nfns++;
    }
    fclose(f);
    f = getenv("CIV2_UNITREC_HAVE") ? fopen(getenv("CIV2_UNITREC_HAVE"), "r") : 0;
    while (f && fgets(line, sizeof line, f)) {
        char *name = strtok(line, "\t\n"), *n = strtok(0, "\t\n");
        for (i = 0; name && n && i < nfns; i++)
            if (!strcmp(fns[i].name, name))
                fns[i].have = (uint32_t)atoi(n);
    }
    if (f)
        fclose(f);
    for (i = 0; i < ut_nsyms; i++)
        if (strstr(ut_syms[i].name, "8win_main") || !strcmp(ut_syms[i].name, "win_main"))
            win_main_addr = ut_syms[i].addr;
    for (i = 0; i < ut_nsyms && nheap < 32; i++) {
        int k;
        for (k = 0; outside[k]; k++)
            if (k < 2 ? strstr(ut_syms[i].name, outside[k]) != 0 : !strcmp(ut_syms[i].name, outside[k]))
                heapfns[nheap++] = ut_syms[i].addr;
    }
    for (i = 0; white[i]; i++)
        if (ut_lookup(white[i]))
            whitelist[nwhite++] = (uint32_t)(uintptr_t)ut_lookup(white[i]);
    plat_begin = (uint32_t)(uintptr_t)plat_text_begin;
    maps = fopen("/proc/self/maps", "r");
    while (maps && fgets(line, sizeof line, maps)) {
        unsigned lo, hi;
        if (strstr(line, "[stack]") && sscanf(line, "%x-%x", &lo, &hi) == 2)
            stack_top = hi;
    }
    if (maps)
        fclose(maps);
    out = gzopen(outp, "wb6");
    if (!out || !win_main_addr || !stack_top)
        return;
    gzwrite(out, UT_MAGIC, 8);
    ut_put(out, (uint32_t)(__stop_civ2data - __start_civ2data));
    atexit(report);
    disabled = 0;
}

/* Is the call worth recording: its 1st, 2nd, 3rd, 4th, 6th, 9th, ... */
static NOI int sample(Fn *fn)
{
    if (fn->kept >= (uint32_t)max_cases || fn->kept + fn->have >= (uint32_t)max_total ||
        fn->attempts >= (uint32_t)max_cases * 4 || depth >= MAXDEPTH)
        return 0;
    if (fn->calls != fn->next)
        return 0;
    fn->next = fn->next < 4 ? fn->next + 1 : fn->next * 3 / 2;
    return 1;
}

/* An argument word: an integer, or where a pointer points. */
static NOI int classify(Frame *fr, int i, uint32_t v, uint32_t esp)
{
    uint32_t size[UT_REGIONS];
    int r;
    fr->kind[i] = UT_ARG_INT;
    fr->a[i] = v;
    fr->b[i] = 0;
    /* (every word: gcc's debugging information has `int` where the source
       has iptr, an integer that holds a pointer) */
    if (v < 0x10000 ||
        (v >= (uint32_t)(uintptr_t)__start_civ2data && v < (uint32_t)(uintptr_t)__stop_civ2data))
        return 1;
    ut_region_sizes(size);
    for (r = 1; r < UT_REGIONS; r++) {
        uint32_t base = (uint32_t)(uintptr_t)ut_region_ptr(r);
        if (size[r] && v >= base && v < base + size[r]) {
            fr->kind[i] = UT_ARG_MAP;
            fr->a[i] = r;
            fr->b[i] = v - base;
            return 1;
        }
    }
    if (v >= esp && v < stack_top) {
        fr->kind[i] = UT_ARG_STACK;
        fr->b[i] = v;       /* the offset in the window: below */
        return 1;
    }
    return 0;           /* the heap, the program's code or constants */
}

/* The stack the pointer arguments point into: one window, from the lowest
   to UT_STACKBUF bytes past the highest (their objects may overlap). */
static NOI int stack_window(Frame *fr)
{
    uint32_t lo = 0xffffffffu, hi = 0;
    int i;
    fr->win_len = 0;
    fr->win_in = 0;
    for (i = 0; i < fr->fn->nwords; i++)
        if (fr->kind[i] == UT_ARG_STACK) {
            lo = fr->b[i] < lo ? fr->b[i] : lo;
            hi = fr->b[i] > hi ? fr->b[i] : hi;
        }
    if (!hi)
        return 1;
    hi = stack_top - hi < UT_STACKBUF ? stack_top : hi + UT_STACKBUF;
    /* and what pointers in it point to, further up the stack */
    for (i = 0; i < 4 && hi - lo <= UT_STACKWINDOW; i++) {
        uint32_t a, top = hi;
        for (a = (lo + 3) & ~3u; a + 4 <= hi; a += 4) {
            uint32_t v = *(uint32_t *)(uintptr_t)a;
            if (v >= hi && v < stack_top && v - lo < UT_STACKWINDOW && v + UT_STACKBUF > top)
                top = stack_top - v < UT_STACKBUF ? stack_top : v + UT_STACKBUF;
        }
        if (top == hi)
            break;
        hi = top;
    }
    if (hi - lo > UT_STACKWINDOW)
        return 0;
    fr->win_lo = lo;
    fr->win_len = hi - lo;
    fr->win_in = (uint8_t *)malloc(fr->win_len);
    memcpy(fr->win_in, (void *)(uintptr_t)lo, fr->win_len);
    ut_mask_stack_text(fr->win_in, fr->win_len);
    for (i = 0; i < fr->fn->nwords; i++)
        if (fr->kind[i] == UT_ARG_STACK) {
            fr->a[i] = fr->b[i] - lo;
            fr->b[i] = 0;
        }
    return 1;
}

static NOI void drop(Frame *fr)
{
    free(fr->win_in);
    fr->win_in = 0;
}

void __cyg_profile_func_enter(void *fnp, void *site)
{
    uint32_t addr = (uint32_t)(uintptr_t)fnp, ebp, esp;
    Fn *fn;
    Frame *fr;
    int i;
    (void)site;
    if (disabled)
        return;
    if (!started) {
        if (!plat_begin)
            init();
        if (disabled || addr != win_main_addr)
            return;
        /* the state the game's initializers leave: the first case's input
           is a delta from it */
        init_data = (uint8_t *)malloc(__stop_civ2data - __start_civ2data);
        memcpy(init_data, __start_civ2data, __stop_civ2data - __start_civ2data);
        snapshot(chain, chain_cap, chain_size);
        started = 1;
        return;
    }
    if (addr >= plat_begin) {
        /* (all frames impure already: a frame open across the message loop
           sees a great many of these) */
        if (depth && !(frames[0].impure && frames[depth - 1].impure)) {
            const char *name;
            for (i = 0; i < nwhite; i++)
                if (whitelist[i] == addr)
                    return;
            for (i = 0; i < depth; i++)
                frames[i].impure = 1;
            name = sym_name(addr);
            for (i = 0; i < 64; i++)
                if (!impure_by[i] || impure_by[i] == name) {
                    impure_by[i] = name;
                    impure_count[i]++;
                    break;
                }
        }
        return;
    }
    for (i = 0; i < nheap; i++)
        if (heapfns[i] == addr) {
            for (i = 0; i < depth; i++)
                frames[i].impure = 1;
            return;
        }
    fn = find(addr);
    if (!fn)
        return;
    fn->calls++;
    if (!sample(fn))
        return;
    fn->attempts++;
    ebp = (uint32_t)(uintptr_t)__builtin_frame_address(1);
    esp = (uint32_t)(uintptr_t)&fn;
    fr = &frames[depth];
    fr->fn = fn;
    fr->ebp = ebp;
    fr->call = fn->calls;
    fr->impure = 0;
    fr->win_in = 0;
    for (i = 0; i < fn->nwords; i++) {
        fr->word[i] = ((uint32_t *)(uintptr_t)(ebp + 8))[i];
        if (!classify(fr, i, fr->word[i], esp)) {
            fn->rejected++;
            return;
        }
    }
    if (!stack_window(fr)) {
        fn->rejected++;
        return;
    }
    snapshot(fr->state, fr->cap, fr->size);
    depth++;
}

uint32_t unitrec_returned(uint32_t eax, uint32_t edx) NOI;
void unitrec_ret_tramp(void);
__asm__(".text\n"
        ".globl unitrec_ret_tramp\n"
        "unitrec_ret_tramp:\n"
        "    push %ebp\n"
        "    mov %esp, %ebp\n"
        "    push %eax\n"
        "    push %edx\n"
        "    and $-16, %esp\n"
        "    sub $8, %esp\n"
        "    push %edx\n"
        "    push %eax\n"
        "    call unitrec_returned\n"
        "    mov %eax, %ecx\n"
        "    mov -4(%ebp), %eax\n"
        "    mov -8(%ebp), %edx\n"
        "    mov %ebp, %esp\n"
        "    pop %ebp\n"
        "    jmp *%ecx\n");

/* The case of the frame on top, which has returned (eax, edx). */
static NOI void finish(Frame *fr, uint32_t eax, uint32_t edx)
{
    static uint32_t size[UT_REGIONS];
    int r, i, same = 1;
    Fn *fn = fr->fn;
    snapshot(scratch, scratch_cap, size);
    for (r = 0; r < UT_REGIONS; r++)
        same &= size[r] == fr->size[r];
    if (!same) {            /* the map was made anew */
        fn->mismatched++;
        drop(fr);
        return;
    }
    fn->kept++;
    cases++;
    ut_put(out, UT_CASE);
    ut_put(out, (uint32_t)strlen(fn->name));
    gzwrite(out, fn->name, (unsigned)strlen(fn->name));
    ut_put(out, fr->call);
    ut_put(out, fn->ret == 'f' ? UT_F_FLOATRET : fn->ret == 'b' ? UT_F_RET8 : fn->ret == 'h' ? UT_F_RET16
                : fn->ret == 'i' ? UT_F_RET : 0);
    ut_put(out, fn->nwords);
    for (i = 0; i < fn->nwords; i++) {
        ut_put(out, fr->kind[i]);
        ut_put(out, fr->a[i]);
        ut_put(out, fr->b[i]);
    }
    ut_put(out, fr->win_len);
    ut_put(out, fr->win_lo);
    if (fr->win_len) {
        uint8_t *win_out = (uint8_t *)malloc(fr->win_len);
        memcpy(win_out, (const uint8_t *)(uintptr_t)fr->win_lo, fr->win_len);
        ut_mask_stack_text(win_out, fr->win_len);
        gzwrite(out, fr->win_in, fr->win_len);
        ut_write_delta(out, fr->win_in, win_out, fr->win_len);
        free(win_out);
    }
    ut_put(out, 0);         /* rand calls: the runner counts them */
    for (r = 0; r < UT_REGIONS; r++)
        ut_put(out, fr->size[r]);
    for (r = 0; r < UT_REGIONS; r++) {
        if (chain_size[r] != fr->size[r]) {     /* a new map: from zeros */
            grow(&chain[r], &chain_cap[r], fr->size[r] ? fr->size[r] : 1);
            memset(chain[r], 0, fr->size[r]);
            chain_size[r] = fr->size[r];
        }
        ut_write_delta(out, chain[r], fr->state[r], fr->size[r]);
        memcpy(chain[r], fr->state[r], fr->size[r]);
    }
    ut_put(out, fn->ret != 'v' && fn->ret != 'f' ? eax : 0);
    ut_put(out, fn->ret == 'i' ? edx : 0);
    for (r = 0; r < UT_REGIONS; r++)
        ut_write_delta(out, fr->state[r], scratch[r], size[r]);
    if (cases % 64 == 0)
        gzflush(out, Z_SYNC_FLUSH);
    drop(fr);
}

uint32_t unitrec_returned(uint32_t eax, uint32_t edx)
{
    Frame *fr = &frames[--depth];
    uint32_t ret = fr->ret_addr;
    finish(fr, eax, edx);
    return ret;
}

void __cyg_profile_func_exit(void *fnp, void *site)
{
    Frame *fr;
    uint32_t ebp;
    (void)site;
    if (disabled || !started || !depth)
        return;
    fr = &frames[depth - 1];
    ebp = (uint32_t)(uintptr_t)__builtin_frame_address(1);
    if (fr->fn->addr != (uint32_t)(uintptr_t)fnp || fr->ebp != ebp)
        return;
    if (fr->impure) {
        fr->fn->impure++;
        depth--;
        drop(fr);
        return;
    }
    if (fr->fn->ret == 'f') {      /* the result on the x87 stack: not taken */
        depth--;
        finish(fr, 0, 0);
        return;
    }
    /* catch the return value: return through the trampoline */
    fr->ret_addr = *(uint32_t *)(uintptr_t)(ebp + 4);
    *(uint32_t *)(uintptr_t)(ebp + 4) = (uint32_t)(uintptr_t)unitrec_ret_tramp;
}
