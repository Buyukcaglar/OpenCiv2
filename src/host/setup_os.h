/*
 * What the set-up (setup.c) needs of the system: files and folders, where
 * the game usually is, and talking to the user.  setup_win.c on Windows,
 * setup_unix.c on macOS and Linux (with setup_mac.m on macOS).
 */
#ifndef CIV2_SETUP_OS_H
#define CIV2_SETUP_OS_H

#include <stddef.h>

#ifdef _WIN32
#define SEP '\\'
#define SEP_S "\\"
#else
#define SEP '/'
#define SEP_S "/"
#endif

#define SETUP_PATH 4096

/* (setup.c) an installed game's folder; the game's CD */
int setup_game_folder(const char *dir);
int setup_game_cd(const char *root);

enum { OS_INFO, OS_WARNING, OS_ERROR };

int os_dir_exists(const char *path);
int os_file_exists(const char *path);
void os_make_dirs(const char *path);
/* dir's entry called name, whatever its case, into out; 0: none */
int os_entry(const char *dir, const char *name, char *out, size_t size);
/* each of dir's entries (not . and ..) to fn until it returns 0; 0: stopped */
int os_each(const char *dir, int (*fn)(void *ctx, const char *name, int is_dir), void *ctx);
int os_copy_file(const char *from, const char *to);
int os_same_path(const char *a, const char *b);
void os_current_dir(char *out, size_t size);

/* GameData: where the game is set up (and the folder it is in made) */
void os_game_data(char *out, size_t size);
/* the program's own files (Windows: the fonts, from its resources); 0: failed */
int os_program_files(void);
/* where the game usually is: installed, its CD in a drive; 0: not found */
int os_find_installed(char *out, size_t size);
int os_find_cd(char *out, size_t size);

void os_message(const char *text, int kind);
/* the user's choice of folder: the installed game or the CD; 0: none */
int os_ask_folder(char *out, size_t size);
/* the set-up from source into dest about to start: 0: the user said no */
int os_confirm(const char *source, const char *dest);
void os_progress_open(void);
/* what is being done; 0: go on, 1: the user stopped it */
int os_progress_show(const char *what, const char *detail);
int os_progress_stopped(void);
void os_progress_close(void);

#endif
