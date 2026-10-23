/*
 * Entry of the portable build: runs the game's wasm32 module (translated to
 * C by wasm2c) with its imports -- the host interface (host.h, implemented
 * by host_sdl.c) and WASI (wasi.c).  The host functions take module
 * addresses, translated here.
 */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "port.h"
#include "wasm-rt-impl.h"
#include "wasm-rt-exceptions.h"     /* wasm_rt_set_unwind_target (wasm_rt_impl_try) */
#include "host.h"

wasm_rt_memory_t *port_memory;

/* The module's view of a host path: on Windows C:\x\y is /c/x/y (wasi.c
 * maps it back); elsewhere the same path. */
static void module_path(const char *in, char *out, size_t n)
{
#ifdef _WIN32
    if (in[0] && in[1] == ':' && (in[2] == '\\' || in[2] == '/' || !in[2])) {
        size_t i, k = 0;
        if (n < 4)
            return;
        out[k++] = '/';
        out[k++] = (char)(in[0] | 0x20);
        for (i = 2; in[i] && k + 1 < n; i++)
            out[k++] = in[i] == '\\' ? '/' : in[i];
        out[k] = 0;
        return;
    }
#endif
    snprintf(out, n, "%s", in);
}

#define HOST(name) w2c_host_host_##name
typedef struct w2c_host Host;

u32 HOST(init)(Host *h, u32 headless) { (void)h; return (u32)host_init((int)headless); }
void HOST(quit)(Host *h) { (void)h; host_quit(); }
u32 HOST(base_path)(Host *h, u32 buf, u32 size)
{
    char p[4096];
    (void)h;
    host_base_path(p, sizeof p);
    module_path(p, MEM(buf), size);
    return (u32)strlen(MEM(buf));
}
u32 HOST(open_window)(Host *h, u32 w, u32 hh, u32 scale) { (void)h; return (u32)host_open_window((int)w, (int)hh, (int)scale); }
u32 HOST(display_size)(Host *h, u32 w, u32 hh)
{
    int32_t a = 0, b = 0;
    u32 r;
    (void)h;
    r = (u32)host_display_size(&a, &b);
    PUT32(w, (u32)a);
    PUT32(hh, (u32)b);
    return r;
}
u32 HOST(usable_size)(Host *h, u32 w, u32 hh)
{
    int32_t a = 0, b = 0;
    u32 r;
    (void)h;
    r = (u32)host_usable_size(&a, &b);
    PUT32(w, (u32)a);
    PUT32(hh, (u32)b);
    return r;
}
void HOST(present)(Host *h, u32 pixels, u32 stride) { (void)h; host_present(MEM(pixels), (int)stride); }
void HOST(minimize)(Host *h) { (void)h; host_minimize(); }

static u32 event_out(int got, const HostEvent *e, u32 out)
{
    if (got)
        memcpy(MEM(out), e, sizeof *e);     /* five int32s, same layout */
    return (u32)got;
}

u32 HOST(poll_event)(Host *h, u32 out)
{
    HostEvent e;
    (void)h;
    return event_out(host_poll_event(&e), &e, out);
}

u32 HOST(wait_event)(Host *h, u32 out, u32 timeout)
{
    HostEvent e;
    (void)h;
    return event_out(host_wait_event(&e, (int)timeout), &e, out);
}

u64 HOST(time_us)(Host *h) { (void)h; return host_time_us(); }
void HOST(delay_ms)(Host *h, u32 ms) { (void)h; host_delay_ms(ms); }

u32 HOST(cursor_system)(Host *h, u32 kind) { (void)h; return (u32)host_cursor_system((int)kind); }
u32 HOST(cursor_image)(Host *h, u32 argb, u32 w, u32 hh, u32 x, u32 y)
{
    (void)h;
    return (u32)host_cursor_image(MEM(argb), (int)w, (int)hh, (int)x, (int)y);
}
void HOST(cursor_set)(Host *h, u32 c) { (void)h; host_cursor_set((int)c); }
void HOST(cursor_free)(Host *h, u32 c) { (void)h; host_cursor_free((int)c); }
void HOST(cursor_show)(Host *h, u32 show) { (void)h; host_cursor_show((int)show); }

u32 HOST(audio_init)(Host *h) { (void)h; return (u32)host_audio_init(); }
u32 HOST(audio_open)(Host *h, u32 freq, u32 ch, u32 bits) { (void)h; return (u32)host_audio_open((int)freq, (int)ch, (int)bits); }
void HOST(audio_queue)(Host *h, u32 dev, u32 data, u32 len) { (void)h; host_audio_queue((int)dev, MEM(data), len); }
u32 HOST(audio_queued)(Host *h, u32 dev) { (void)h; return host_audio_queued((int)dev); }
void HOST(audio_clear)(Host *h, u32 dev) { (void)h; host_audio_clear((int)dev); }
void HOST(audio_close)(Host *h, u32 dev) { (void)h; host_audio_close((int)dev); }

u32 HOST(message_box)(Host *h, u32 icon, u32 title, u32 text, u32 n, u32 labels, u32 ids, u32 enter, u32 escape)
{
    const char *l[8];
    int id[8];
    u32 i;
    (void)h;
    if (n > 8)
        n = 8;
    for (i = 0; i < n; i++) {
        l[i] = MEM(GET32(labels + 4 * i));
        id[i] = (int)GET32(ids + 4 * i);
    }
    return (u32)host_message_box((int)icon, MEM(title), MEM(text), (int)n, l, id, (int)enter, (int)escape);
}

int main(int argc, char **argv)
{
    static w2c_civ2 module;
    static Host host = {&module};
    static struct w2c_wasi__snapshot__preview1 wasi = {&module};
    wasm_rt_trap_t trap;
    char cwd[4096], game[4096], *args[2];
    /* The module's working directory starts at "/": name the game
       directory (main.c's argument) when none is given. */
    if (argc < 2 && getcwd(cwd, sizeof cwd)) {
        module_path(cwd, game, sizeof game);
        args[0] = argv[0];
        args[1] = game;
        argc = 2;
        argv = args;
    } else if (argc >= 2) {
        module_path(argv[1], game, sizeof game);
        args[0] = argv[0];
        args[1] = game;
        argc = 2;
        argv = args;
    }
#ifdef _WIN32
    if (!getenv("CIV2_SCRIPT")) {
        /* A GUI program has no console: what the game logs (a video it
           could not play ...) goes to civ2-log.txt beside the program. */
        char log[4096];
        size_t n = (size_t)host_base_path(log, (int)sizeof log - 16);
        int fd;
        snprintf(log + n, sizeof log - n, "civ2-log.txt");
        fd = open(log, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd >= 0) {
            dup2(fd, 2);        /* the module writes descriptor 2 (wasi.c) */
            close(fd);
        }
    }
    {
        /* directories in the environment (CIV2_DATA ...), as the module sees them */
        static const char *const vars[] = {"CIV2_DATA", "CIV2_WINDIR", "CIV2_SHOT_DIR", "CIV2_SCRIPT",
                                           "CIV2_RAND_LOG", "CIV2_HOOK_LOG"};
        size_t i;
        for (i = 0; i < sizeof vars / sizeof vars[0]; i++) {
            const char *v = getenv(vars[i]);
            char p[4096], kv[4200];
            if (v && *v) {
                module_path(v, p, sizeof p);
                snprintf(kv, sizeof kv, "%s=%s", vars[i], p);
                _putenv(kv);
            }
        }
    }
#endif
    wasi_init(argc, argv);
    wasm_rt_init();
    wasm2c_civ2_instantiate(&module, &host, &wasi);
    port_memory = w2c_civ2_memory(&module);
    trap = wasm_rt_impl_try();
    if (trap == WASM_RT_TRAP_NONE)
        w2c_civ2_0x5Fstart(&module);
    else
        fprintf(stderr, "civ2: the game stopped: %s\n", wasm_rt_strerror(trap));
    wasm2c_civ2_free(&module);
    wasm_rt_free();
    return trap == WASM_RT_TRAP_NONE ? 0 : 1;
}
