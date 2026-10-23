/*
 * What the platform layer (src/platform) needs from the machine it runs on:
 * a window to show the desktop in, input, time, cursors, audio and message
 * boxes.  Plain C types only: the portable build compiles the game and the
 * platform layer to wasm32 and these become the module's imports (pointers
 * are then offsets into its memory); native builds call them directly.
 * src/host/host_sdl.c implements them with SDL2.
 */
#ifndef CIV2_HOST_H
#define CIV2_HOST_H

#include <stdint.h>

#ifdef __wasm__
#define HOST_API(name) __attribute__((import_module("host"), import_name(#name))) name
#else
#define HOST_API(name) name
#endif

/* Input events; keys arrive as Windows virtual-key codes. */
enum {
    HOST_EV_NONE, HOST_EV_QUIT, HOST_EV_KEYDOWN, HOST_EV_KEYUP, HOST_EV_MOTION,
    HOST_EV_BUTTONDOWN, HOST_EV_BUTTONUP, HOST_EV_EXPOSED
};
typedef struct HostEvent {
    int32_t type;
    int32_t vk;             /* keys */
    int32_t x, y;           /* pointer, desktop coordinates */
    int32_t button;         /* 1 left, 2 right, 3 middle */
} HostEvent;

/* Set-up: headless (no window, no audio device) for replays. */
int HOST_API(host_init)(int headless);
void HOST_API(host_quit)(void);
/* The directory the program is in, with a trailing separator ("" if unknown). */
int HOST_API(host_base_path)(char *buf, int size);

/* The window: w x h desktop pixels, scaled; present() shows 32-bit
 * 0xAARRGGBB pixels, rows stride bytes apart.  scale 0: a window without
 * a frame over the display's usable area (the desktop drawn to fill it). */
int HOST_API(host_open_window)(int w, int h, int scale);
/* The size of the main display (in the units windows are sized in). */
int HOST_API(host_display_size)(int32_t *w, int32_t *h);
/* ... and of its usable area: without the taskbar, dock or menu bar. */
int HOST_API(host_usable_size)(int32_t *w, int32_t *h);
void HOST_API(host_present)(const void *pixels, int stride);
/* Minimize the window (the desktop's main window was minimized). */
void HOST_API(host_minimize)(void);

/* 1 if an event was returned; wait: up to timeout_ms (-1: forever). */
int HOST_API(host_poll_event)(HostEvent *e);
int HOST_API(host_wait_event)(HostEvent *e, int timeout_ms);

/* Monotonic clock. */
uint64_t HOST_API(host_time_us)(void);
void HOST_API(host_delay_ms)(uint32_t ms);

/* Cursors: handles > 0.  System kinds: 0 arrow, 1 I-beam, 2 wait, 3 cross,
 * 4 size NW-SE, 5 size NE-SW, 6 size W-E, 7 size N-S, 8 size all, 9 no, 10 hand. */
int HOST_API(host_cursor_system)(int kind);
int HOST_API(host_cursor_image)(const uint32_t *argb, int w, int h, int hot_x, int hot_y);
void HOST_API(host_cursor_set)(int cursor);
void HOST_API(host_cursor_free)(int cursor);
void HOST_API(host_cursor_show)(int show);

/* Audio: 1 if there is any; devices > 0 play queued PCM (8 or 16-bit). */
int HOST_API(host_audio_init)(void);
int HOST_API(host_audio_open)(int freq, int channels, int bits);
void HOST_API(host_audio_queue)(int dev, const void *data, uint32_t len);
uint32_t HOST_API(host_audio_queued)(int dev);
void HOST_API(host_audio_clear)(int dev);
void HOST_API(host_audio_close)(int dev);

/* A modal message box; returns the chosen button's id, -1 if it failed.
 * icon: 0 information, 1 warning, 2 error; enter/escape: the indices of
 * the buttons those keys choose (-1: none). */
int HOST_API(host_message_box)(int icon, const char *title, const char *text, int nbuttons,
                               const char *const *labels, const int *ids, int enter, int escape);

#endif
