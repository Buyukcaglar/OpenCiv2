/*
 * Turn timer (multiplayer "timed turns"): counts down the remaining time and
 * redraws the progress indicator.
 */
#include "game.h"

#define g_turn_time_limit   (*(int *)((u8 *)&g.d_00654b70))     /* 0 = no timer */
#define g_timer_blink       (*(uint *)((u8 *)&g.d_006ab5ac))
#define g_timer_remaining   (*(int *)((u8 *)&g.d_00633a78))
#define g_timer_last_tick   (*(int *)((u8 *)&g.d_00633a7c))
#define g_timer_event       (*(int *)((u8 *)&g.d_00633a74))
#define g_timer_expired     (*(undefined1 *)((u8 *)&g.d_0064b9bc))

/* 0x0055b0fb */
void __cdecl mp_turn_timer_tick(void)
{
    int percent, color, elapsed;
    RECT rect;

    if (g_turn_time_limit == 0)
        return;
    g_timer_blink ^= 1;
    if (g_timer_blink != 0) {
        if (g_timer_remaining != 0) {
            /* Seconds since the last tick, rounded (ticks are in 1/60 s). */
            elapsed = (int)((double)(thunk_timer_ticks() - g_timer_last_tick) / 60.0 + 0.5);
            g_timer_remaining -= elapsed;
            if (g_timer_remaining < 0)
                g_timer_remaining = 0;
            g_timer_last_tick = thunk_timer_ticks();
        }
        if (g_timer_remaining == 0) {
            thunk_city_window_close();
            thunk_intel_report_end_modal();
            thunk_throneroom_close();
            thunk_pedia_end_modal();
            g_timer_expired = 0;
            thunk_status_draw_timer_bar(100, 0xffffffff);
            return;
        }
        thunk_frame_wnd_draw_caption(&map_views);
        rect.left = (*(int *)((u8 *)&g.d_0066ca54));
        rect.top = (*(int *)((u8 *)&g.d_0066ca58));
        rect.right = (*(int *)((u8 *)&g.d_0066ca5c));
        rect.bottom = (*(int *)((u8 *)&g.d_0066ca68));
        thunk_wnd_blit_surface_rect(&map_views, &rect);
    }
    percent = (g_timer_remaining * 100000) / g_turn_time_limit;
    if (percent < 0x21)
        color = 0x6a;
    else if (percent < 0x42)
        color = 0x7a;
    else
        color = 0x2a;
    if ((color == 0x6a || g_timer_remaining < 0x1e) && g_timer_blink != 0)
        color = -1;
    thunk_status_draw_timer_bar(percent, color);
    if (g_timer_event != 0)
        game_timer_destroy(g_timer_event);
    g_timer_event = game_timer_create(((void *)ADDR(0x00402220, mp_turn_timer_tick)), 500, 1);
}
