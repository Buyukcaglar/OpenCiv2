/*
 * Setting up the game on Windows: OpenCiv2.exe and a GameData folder
 * beside it, made from the user's copy of Civilization II -- an installed
 * game's folder, the CD as an image (.cue/.bin, .iso) or an archive
 * (.zip, .7z, .rar) of either.  The game's files are found wherever they
 * are in it (sub-folders, the CD's InstallShield cabinet, a CD image inside
 * an archive), checked against setup_manifest.c (size and SHA-256) and
 * only those copied.
 *
 *   setup_files.c   finding, checking and copying the files
 *   setup_win.c     the windows: choosing the copy, progress, what failed;
 *                   the game's message boxes; light and dark mode
 */
#ifndef CIV2_SETUP_H
#define CIV2_SETUP_H

#include <stddef.h>
#include <stdint.h>

enum { SETUP_REQUIRED = 1, SETUP_OPTIONAL = 2 };

typedef struct SetupFile {
    const char *path;           /* in GameData, '/'-separated */
    uint32_t size;
    const char *sha256;         /* lowercase hex */
    int flags;
} SetupFile;

extern const SetupFile setup_manifest[];
extern const int setup_manifest_count;

/* What an import reports while it works (from its own thread). */
typedef struct SetupProgress {
    void *user;
    void (*status)(void *user, const char *what, const char *detail);
    void (*fraction)(void *user, double done);     /* 0..1; < 0: unknown */
    int (*cancelled)(void *user);
} SetupProgress;

/* Find the game's files in source (a folder, an archive or a CD image;
   UTF-8), check them and copy them into game_dir (created if need be).
   1: done; 0: not, *report says why in full (malloc'd UTF-8; also when
   done: what was optional and left out). */
int setup_import(const char *source, const char *game_dir, const SetupProgress *p, char **report);

/* Whether game_dir has every required file (present, of the right size);
   if not, *report lists what is wrong (malloc'd). */
int setup_check(const char *game_dir, char **report);

/* The reconstruction's own files in game_dir/native (the fonts) and the
   game's CIV2.DAT, from the program's resources, where missing.  0 and
   *error (malloc'd) if they could not be written. */
int setup_port_files(const char *game_dir, char **error);

/* The folder the program is in (UTF-8, no trailing separator). */
void setup_program_dir(char *buf, size_t size);

/* Decide where the game is before it starts (port_main.c): with no
   arguments GameData beside the program, set up first if need be (the
   set-up window); a folder as argument is the game, run where it is (as
   before; the test harness); a file (archive, CD image) is set up into
   GameData.  1: game set (UTF-8, host path); 0: quit. */
int setup_choose_game(int argc, char **argv, char *game, size_t size);

/* A message box in the system's light or dark style (host_message_box). */
int setup_message_box(void *owner_hwnd, int icon, const char *title, const char *text, int nbuttons,
                      const char *const *labels, const int *ids, int enter, int escape);

/* The program's name and version (also in res/civ2-port.rc), its home. */
#define OPENCIV2_NAME "OpenCiv2"
#define OPENCIV2_VERSION "1.0"
#define OPENCIV2_URL "https://github.com/Buyukcaglar/OpenCiv2"
#define OPENCIV2_UPSTREAM_URL "https://github.com/richardpenman/civ2"
#define OPENCIV2_ICON_URL "https://www.deviantart.com/alexielios/art/Icon-Civilization-II-558913212"

/* The About box, modal over owner_hwnd (may be NULL). */
void setup_about(void *owner_hwnd);

#endif
