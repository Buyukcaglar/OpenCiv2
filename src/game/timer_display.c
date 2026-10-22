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
void __cdecl FUN_0055b0fb(void)
{
    int percent, color, elapsed;
    RECT rect;

    if (g_turn_time_limit == 0)
        return;
    g_timer_blink ^= 1;
    if (g_timer_blink != 0) {
        if (g_timer_remaining != 0) {
            /* Seconds since the last tick, rounded (ticks are in 1/60 s). */
            elapsed = (int)((double)(thunk_FUN_00421bb0() - g_timer_last_tick) / 60.0 + 0.5);
            g_timer_remaining -= elapsed;
            if (g_timer_remaining < 0)
                g_timer_remaining = 0;
            g_timer_last_tick = thunk_FUN_00421bb0();
        }
        if (g_timer_remaining == 0) {
            thunk_FUN_0050994f();
            thunk_FUN_00437c6f();
            thunk_FUN_0044f799();
            thunk_FUN_004f8d51();
            g_timer_expired = 0;
            thunk_FUN_0056ac67(100, 0xffffffff);
            return;
        }
        thunk_FUN_00552112(&DAT_0066c7a8);
        rect.left = (*(int *)((u8 *)&g.d_0066ca54));
        rect.top = (*(int *)((u8 *)&g.d_0066ca58));
        rect.right = (*(int *)((u8 *)&g.d_0066ca5c));
        rect.bottom = (*(int *)((u8 *)&g.d_0066ca68));
        thunk_FUN_00408490(&DAT_0066c7a8, &rect);
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
    thunk_FUN_0056ac67(percent, color);
    if (g_timer_event != 0)
        FUN_005d2004(g_timer_event);
    g_timer_event = FUN_005d1f50(((void *)ADDR(0x00402220, FUN_0055b0fb)), 500, 1);
}
