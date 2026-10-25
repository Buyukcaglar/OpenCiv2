/*
 * macOS and Linux: the system's part of the set-up (setup_os.h).  The game
 * is found in the usual folders (also in Wine's and CrossOver's), or its CD
 * (or a copy of it) mounted; GameData is in the user's data folder
 * (macOS: ~/Library/Application Support/OpenCiv2, Linux:
 * ~/.local/share/OpenCiv2); the program's own files are beside it, in data.
 * Messages are SDL's; the folder is asked with the system's dialog (macOS:
 * setup_mac.m; Linux: zenity or kdialog, where there is one).
 */
#include <dirent.h>
#include <glob.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <unistd.h>
#include "SDL.h"
#include "setup.h"
#include "setup_os.h"

#define TITLE "OpenCiv2"

int os_dir_exists(const char *p)
{
    struct stat st;
    return !stat(p, &st) && S_ISDIR(st.st_mode);
}

int os_file_exists(const char *p)
{
    struct stat st;
    return !stat(p, &st) && S_ISREG(st.st_mode);
}

void os_make_dirs(const char *path)
{
    char p[SETUP_PATH];
    size_t i;
    snprintf(p, sizeof p, "%s", path);
    for (i = 1; p[i]; i++)
        if (p[i] == '/') {
            p[i] = 0;
            mkdir(p, 0755);
            p[i] = '/';
        }
    mkdir(p, 0755);
}

int os_entry(const char *dir, const char *name, char *out, size_t size)
{
    DIR *d;
    struct dirent *e;
    int found = 0;
    snprintf(out, size, "%s/%s", dir, name);
    if (!access(out, F_OK))
        return 1;
    if (!(d = opendir(dir)))
        return 0;
    while (!found && (e = readdir(d)))
        if (!strcasecmp(e->d_name, name)) {
            snprintf(out, size, "%s/%s", dir, e->d_name);
            found = 1;
        }
    closedir(d);
    return found;
}

int os_each(const char *dir, int (*fn)(void *ctx, const char *name, int is_dir), void *ctx)
{
    DIR *d = opendir(dir);
    struct dirent *e;
    int ok = 1;
    if (!d)
        return 1;
    while (ok && (e = readdir(d))) {
        char p[SETUP_PATH];
        if (!strcmp(e->d_name, ".") || !strcmp(e->d_name, ".."))
            continue;
        snprintf(p, sizeof p, "%s/%s", dir, e->d_name);
        ok = fn(ctx, e->d_name, os_dir_exists(p));
    }
    closedir(d);
    return ok;
}

/* (writable, though read-only on the CD) */
int os_copy_file(const char *from, const char *to)
{
    char buf[1 << 16];
    size_t n;
    FILE *in = fopen(from, "rb"), *out;
    int ok = 1;
    if (!in)
        return 0;
    if (!(out = fopen(to, "wb"))) {
        fclose(in);
        return 0;
    }
    while (ok && (n = fread(buf, 1, sizeof buf, in)) > 0)
        ok = fwrite(buf, 1, n, out) == n;
    ok = ok && !ferror(in);
    fclose(in);
    if (fclose(out) != 0)
        ok = 0;
    if (!ok)
        remove(to);
    return ok;
}

int os_same_path(const char *a, const char *b)
{
    return !strcmp(a, b);
}

void os_current_dir(char *out, size_t size)
{
    if (!getcwd(out, size))
        snprintf(out, size, ".");
}

static const char *home(void)
{
    const char *h = getenv("HOME");
    return h && *h ? h : ".";
}

void os_game_data(char *out, size_t size)
{
#ifdef __APPLE__
    snprintf(out, size, "%s/Library/Application Support/OpenCiv2/GameData", home());
#else
    const char *x = getenv("XDG_DATA_HOME");
    if (x && *x == '/')
        snprintf(out, size, "%s/OpenCiv2/GameData", x);
    else
        snprintf(out, size, "%s/.local/share/OpenCiv2/GameData", home());
#endif
}

/* (in data beside the program already) */
int os_program_files(void)
{
    return 1;
}

/* ---- where the game is ---- */

/* The first of the folders pattern (glob's) names for which is(folder). */
static int find(const char *pattern, int (*is)(const char *), char *out, size_t size)
{
    glob_t g;
    size_t i;
    int found = 0;
    if (glob(pattern, 0, NULL, &g))
        return 0;
    for (i = 0; i < g.gl_pathc && !found; i++)
        if (is(g.gl_pathv[i])) {
            snprintf(out, size, "%s", g.gl_pathv[i]);
            found = 1;
        }
    globfree(&g);
    return found;
}

int os_find_installed(char *out, size_t size)
{
    /* where Windows' installer would put it, in a Wine (or CrossOver) drive C: */
    static const char *const in_c[] = {"MPS/CIV2", "Program Files (x86)/MicroProse Software/Civilization II Multiplayer "
                                       "Gold Edition", "Program Files/MicroProse Software/Civilization II Multiplayer Gold "
                                       "Edition", "Civ2", "Games/Civ2"};
    static const char *const drives_c[] = {"%s/.wine/drive_c",
#ifdef __APPLE__
                                           "%s/Library/Application Support/CrossOver/Bottles/*/drive_c",
#endif
                                           "%s/Games/*/drive_c"};
    static const char *const others[] = {"%s/Civ2", "%s/civ2", "%s/Games/Civ2", "%s/Games/civ2"};
    char pattern[SETUP_PATH], c[SETUP_PATH];
    const char *v = getenv("CIV2_GAME");
    size_t i, k;
    if (v && *v && setup_game_folder(v)) {
        snprintf(out, size, "%s", v);
        return 1;
    }
    for (i = 0; i < sizeof others / sizeof others[0]; i++) {
        snprintf(pattern, sizeof pattern, others[i], home());
        if (find(pattern, setup_game_folder, out, size))
            return 1;
    }
    for (i = 0; i <= sizeof drives_c / sizeof drives_c[0]; i++) {
        if (i < sizeof drives_c / sizeof drives_c[0])
            snprintf(c, sizeof c, drives_c[i], home());
        else if ((v = getenv("WINEPREFIX")) && *v)
            snprintf(c, sizeof c, "%s/drive_c", v);
        else
            continue;
        for (k = 0; k < sizeof in_c / sizeof in_c[0]; k++) {
            snprintf(pattern, sizeof pattern, "%s/%s", c, in_c[k]);
            if (find(pattern, setup_game_folder, out, size))
                return 1;
        }
    }
    return 0;
}

/* The CD (or a copy of it, as a disk image) mounted. */
int os_find_cd(char *out, size_t size)
{
    static const char *const mounts[] = {
#ifdef __APPLE__
        "/Volumes/*",
#else
        "/media/*/*", "/run/media/*/*", "/media/*", "/mnt/*", "/cdrom",
#endif
    };
    size_t i;
    for (i = 0; i < sizeof mounts / sizeof mounts[0]; i++)
        if (find(mounts[i], setup_game_cd, out, size))
            return 1;
    return 0;
}

/* ---- talking to the user ---- */

void os_message(const char *text, int kind)
{
    Uint32 flags = kind == OS_ERROR ? SDL_MESSAGEBOX_ERROR : kind == OS_WARNING ? SDL_MESSAGEBOX_WARNING :
                   SDL_MESSAGEBOX_INFORMATION;
    if (SDL_ShowSimpleMessageBox(flags, TITLE, text, NULL))
        fprintf(stderr, "OpenCiv2: %s\n", text);
}

#ifdef __APPLE__
int setup_mac_ask_folder(const char *prompt, char *out, size_t size);     /* setup_mac.m */
#else
/* The folder chosen with the command's dialog; 0: none (or no command). */
static int ask_with(const char *command, char *out, size_t size)
{
    FILE *p = popen(command, "r");
    size_t n;
    int st;
    if (!p)
        return 0;
    n = fread(out, 1, size - 1, p);
    st = pclose(p);
    out[n] = 0;
    while (n && (out[n - 1] == '\n' || out[n - 1] == '\r'))
        out[--n] = 0;
    return st == 0 && n > 0;
}
#endif

int os_ask_folder(char *out, size_t size)
{
    static const char prompt[] = "Where is Civilization II Multiplayer Gold Edition? Choose the folder it is "
                                 "installed in, or its CD.";
#ifdef __APPLE__
    return setup_mac_ask_folder(prompt, out, size);
#else
    if (ask_with("zenity --file-selection --directory --title='Where is Civilization II Multiplayer Gold Edition? "
                 "(the folder it is installed in, or its CD)' 2>/dev/null", out, size) ||
        ask_with("kdialog --getexistingdirectory ~ --title 'Where is Civilization II Multiplayer Gold Edition? "
                 "(the folder it is installed in, or its CD)' 2>/dev/null", out, size))
        return 1;
    if (system("command -v zenity >/dev/null 2>&1 || command -v kdialog >/dev/null 2>&1")) {
        char text[512];
        snprintf(text, sizeof text, "%s\n\nStart OpenCiv2 with that folder: OpenCiv2 --setup FOLDER", prompt);
        os_message(text, OS_INFO);
    }
    return 0;
#endif
}

int os_confirm(const char *source, const char *dest)
{
    static const SDL_MessageBoxButtonData buttons[] = {
        {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Set up"},
        {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "Quit"},
    };
    char text[2 * SETUP_PATH + 256];
    SDL_MessageBoxData box;
    int id;
    snprintf(text, sizeof text, "OpenCiv2 sets up the game from %s, %s it into\n%s\n\nThis takes a minute or two; "
             "then the game starts.", source, setup_game_cd(source) ? "unpacking" : "copying", dest);
    memset(&box, 0, sizeof box);
    box.flags = SDL_MESSAGEBOX_INFORMATION;
    box.title = TITLE;
    box.message = text;
    box.numbuttons = 2;
    box.buttons = buttons;
    if (SDL_ShowMessageBox(&box, &id)) {
        fprintf(stderr, "OpenCiv2: %s\n", text);       /* (no display for it: go on) */
        return 1;
    }
    return id == 1;
}

/* (no window: what is done, on the terminal) */
void os_progress_open(void)
{
}

int os_progress_show(const char *what, const char *detail)
{
    fprintf(stderr, "%s %s\n", what, detail ? detail : "");
    return 0;
}

int os_progress_stopped(void)
{
    return 0;
}

void os_progress_close(void)
{
}
