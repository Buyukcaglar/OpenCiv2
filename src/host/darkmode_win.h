/*
 * Windows' light and dark modes for the program's own windows (the set-up
 * and message windows, setup_win.c) and the game's window (its title bar
 * and menu bar, host_menu_win.c): as the system's "app mode" setting, and
 * following it when it changes.  High contrast keeps the system's colours.
 */
#ifndef CIV2_DARKMODE_WIN_H
#define CIV2_DARKMODE_WIN_H

#include <windows.h>

typedef struct DmColors {
    COLORREF bg;                /* window background */
    COLORREF field;             /* text fields */
    COLORREF text, dim;         /* text, secondary text */
    COLORREF border;
    COLORREF accent;            /* progress, the primary action */
    COLORREF track;             /* progress bar's empty part */
    COLORREF hot;               /* menu bar item under the pointer */
    COLORREF error;
} DmColors;

/* Once, before the first window: popup menus and scroll bars may be dark. */
void dm_init(void);
/* The system's apps are in dark mode (and high contrast is off). */
int dm_dark(void);
/* High contrast is on: the system's colours, nothing custom. */
int dm_high_contrast(void);
void dm_colors(DmColors *c);
/* A top-level window: its title bar (and the menus, scroll bars it owns)
   in the current mode.  Again after the mode changed. */
void dm_window(HWND hwnd);
/* A control (button, edit) themed for the current mode. */
void dm_control(HWND ctl);
/* WM_SETTINGCHANGE that means the mode (or high contrast) changed. */
int dm_changed(UINT msg, LPARAM lp);
/* The window's Win32 menu bar drawn in the current mode (subclassed). */
void dm_menu_bar(HWND hwnd);

#endif
