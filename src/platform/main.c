/*
 * Program entry for native builds: host set-up (src/host), the game's static data and
 * initializers, then the game's WinMain.  Also presentation (desktop
 * surface -> host window) and host input events.
 *
 * Usage: civ2 [GAMEDIR]   (default: the current directory)
 * Environment: CIV2_DATA (native data directory, default: next to the
 * executable), CIV2_SCALE (window scale), CIV2_SCRIPT etc. (replay.c).
 */
#include "plat.h"
#include "../host/host.h"
#include <unistd.h>

void gamedata_init(void);
int gamedata_check_layout(void);
extern void (*const civ2_c_inits[])(void);
extern void (*const civ2_cpp_inits[])(void);
int __stdcall win_main(int inst, int prev, int cmdline, int show);   /* WinMain */
void replay_init(void);
void resources_init(void);
void sound_poll(void);

static int window_open;
static uint64_t last_present;

void plat_present(void)
{
    uint64_t now;
    if (!window_open)
        return;
    now = host_time_us();
    if (now - last_present < 15000)
        return;
    last_present = now;
    if (!plat_overlay)
        plat_compose();
    host_present(screen->bits, screen->stride);
}

/* Now, whatever the frame rate: before waiting for input (menus). */
void plat_present_now(void)
{
    last_present = 0;
    plat_present();
}

int msg_pump_events(int wait)
{
    HostEvent e;
    int n = 0;
    sound_poll();               /* (a replay has audio only with CIV2_TEST_AUDIO) */
    if (plat_replay) {
        /* Input comes from the script only; keep the window responsive. */
        while (window_open && host_poll_event(&e))
            ;
        return 0;
    }
    menu_native_sync();
    while (wait ? host_wait_event(&e, 10) : host_poll_event(&e)) {
        wait = 0;
        n++;
        switch (e.type) {
        case HOST_EV_QUIT:
            if (active_wnd)
                PostMessageA(active_wnd, WM_SYSCOMMAND, SC_CLOSE, 0);
            else
                exit(0);
            break;
        case HOST_EV_KEYDOWN:
        case HOST_EV_KEYUP:
            input_key(e.vk, e.type == HOST_EV_KEYDOWN);
            break;
        case HOST_EV_MOTION:
            input_mouse_move(e.x, e.y);
            break;
        case HOST_EV_BUTTONDOWN:
        case HOST_EV_BUTTONUP:
            input_mouse_move(e.x, e.y);
            input_mouse_button(e.button, e.type == HOST_EV_BUTTONDOWN);
            break;
        case HOST_EV_EXPOSED:
            last_present = 0;
            break;
        case HOST_EV_COMMAND:
            menu_native_command(e.vk);
            break;
        }
    }
    return n;
}

/* ---- start-up ---- */

static void set_dirs(const char *argv0, const char *gamedir)
{
    const char *d;
    char base[1024];
    host_base_path(base, sizeof base);
    if (gamedir && chdir(gamedir))
        plat_fatal("cannot enter the game directory %s", gamedir);
    if (!getcwd(plat_game_dir, 1024))
        plat_fatal("no current directory");
    d = getenv("CIV2_WINDIR");
    snprintf(plat_win_dir, 1024, "%s", d && *d ? d : plat_game_dir);
    d = getenv("CIV2_DATA");
    if (d && *d)
        snprintf(plat_data_dir, 1024, "%s", d);
    else
        snprintf(plat_data_dir, 1024, "%sdata", *base ? base : "./");
    (void)argv0;
}


int main(int argc, char **argv)
{
    const char *scale = getenv("CIV2_SCALE");
    int i, cover = 0;
    char cmdline[1] = "";
    plat_replay = getenv("CIV2_SCRIPT") && *getenv("CIV2_SCRIPT");
    /* Replays reproduce the reference desktop (Wine without a window
       manager) unless CIV2_NORMAL_DESKTOP is set. */
    plat_normal_desktop = !plat_replay || (getenv("CIV2_NORMAL_DESKTOP") && *getenv("CIV2_NORMAL_DESKTOP"));
    if (!host_init(plat_replay && !getenv("CIV2_SHOW")))
        return 1;
    set_dirs(argv[0], argc > 1 ? argv[1] : NULL);
    clock_init();
    if (!plat_replay) {
        /* As the original on Windows, whose main window fills the screen.
         * Where the system has its own (Windows, macOS): its window and
         * menu bar (CIV2_FULLSCREEN=1: full screen, CIV2_WINDOW=1: a
         * window).  Elsewhere, or with CIV2_CLASSIC=1 (the menu bar and
         * caption drawn as the original's): a desktop of the display's
         * usable area (full screen: of the whole display), in steps of whole
         * pixels per desktop pixel; CIV2_WINDOW or CIV2_SCALE: the 1024x768
         * desktop in a window. */
        int fullscreen = getenv("CIV2_FULLSCREEN") && *getenv("CIV2_FULLSCREEN");
        int windowed = (getenv("CIV2_WINDOW") && *getenv("CIV2_WINDOW")) || scale;
        int classic = getenv("CIV2_CLASSIC") && *getenv("CIV2_CLASSIC");
        int32_t dw, dh;
        plat_lock_panels = !classic;
        if (!classic && !scale && host_open_native_window(&dw, &dh, fullscreen ? 1 : windowed ? 2 : 0)) {
            screen_w = dw;
            screen_h = dh;
            window_open = plat_native_menu = 1;
        } else if ((fullscreen ? host_display_size(&dw, &dh) : !windowed && host_usable_size(&dw, &dh)) &&
                   dw >= 800 && dh >= 600) {
            int k = dh / 768 > 1 ? dh / 768 : 1;
            screen_w = dw / k;
            screen_h = dh / k;
            cover = !fullscreen;
        }
    }
    if (plat_replay && getenv("CIV2_TEST_NATIVE") && *getenv("CIV2_TEST_NATIVE"))
        /* Tests: the game as on Windows and macOS (the host's menu bar, no
           caption of its own, panels locked), the host's part left out. */
        plat_native_menu = plat_lock_panels = 1;
    gdi_init();
    wnd_init();
    resources_init();
    sound_init();
    if (!window_open && (!plat_replay || getenv("CIV2_SHOW")))
        window_open = host_open_window(screen_w, screen_h, cover ? 0 : scale ? atoi(scale) : 1);
    replay_init();
    pointer_init(screen_w / 2, screen_h / 2);      /* where the X server puts it */
    /* The game's static data, then the C and C++ initializers the MSVC
     * runtime ran before WinMain. */
    gamedata_init();
    gamedata_check_layout();
    for (i = 0; civ2_c_inits[i]; i++)
        civ2_c_inits[i]();
    for (i = 0; civ2_cpp_inits[i]; i++)
        civ2_cpp_inits[i]();
    win_main((int)(uintptr_t)plat_exe_module(), 0, (int)(uintptr_t)cmdline, SW_SHOWNORMAL);
    host_quit();
    return 0;
}
