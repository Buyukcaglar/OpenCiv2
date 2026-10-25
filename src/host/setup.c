/*
 * The game set up from the user's copy of Civilization II Multiplayer Gold
 * Edition (setup.h).  The game is found where it usually is: installed or
 * its CD in a drive (setup_win.c, setup_unix.c); else the user says where.
 * An installed game's folder is copied; from the CD the game is unpacked
 * from its InstallShield cabinet (DATA1.CAB, with unshield), as its
 * installer would, and its videos copied.  Into GameData: beside the
 * program on Windows, in the user's data folder on macOS and Linux.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libunshield.h>
#include "setup.h"
#include "setup_os.h"

#define DONE_FILE "OpenCiv2-setup.txt"      /* in GameData: written when the set-up is complete */

/* An installed game (or a copy of its folder). */
int setup_game_folder(const char *dir)
{
    char p[SETUP_PATH];
    return *dir && os_entry(dir, "Civ2Art.dll", p, sizeof p) && os_file_exists(p) &&
           os_entry(dir, "RULES.TXT", p, sizeof p) && os_file_exists(p);
}

/* The game's CD (or a copy of it): the cabinet the installer unpacks, the
   folder with the videos. */
int setup_game_cd(const char *root)
{
    char p[SETUP_PATH];
    return *root && os_entry(root, "DATA1.CAB", p, sizeof p) && os_file_exists(p) &&
           os_entry(root, "CIV2", p, sizeof p) && os_dir_exists(p);
}

/* ---- copying and unpacking ---- */

static const char *copy_dest;           /* GameData: not copied into itself */

struct copy {
    const char *src, *dst;
};

static int copy_tree(const char *src, const char *dst);

static int copy_entry(void *ctx, const char *name, int is_dir)
{
    const struct copy *c = ctx;
    char from[SETUP_PATH], to[SETUP_PATH];
    snprintf(from, sizeof from, "%s" SEP_S "%s", c->src, name);
    snprintf(to, sizeof to, "%s" SEP_S "%s", c->dst, name);
    if (is_dir)
        return (copy_dest && os_same_path(from, copy_dest)) || copy_tree(from, to);
    if (os_progress_show("Copying", from))
        return 0;
    if (!os_copy_file(from, to)) {
        char text[2 * SETUP_PATH + 64];
        snprintf(text, sizeof text, "Could not copy %s to %s.", from, to);
        os_message(text, OS_ERROR);
        return 0;
    }
    return 1;
}

/* src's files and folders into dst (made if need be); 0: stopped */
static int copy_tree(const char *src, const char *dst)
{
    struct copy c = {src, dst};
    os_make_dirs(dst);
    return os_each(src, copy_entry, &c);
}

/* The game from the CD's cabinet into dst, as its installer unpacks it
   (the "Sound Files" group into Sound, the others as their folders say). */
static int unpack_cab(const char *cab, const char *dst)
{
    Unshield *u;
    int g, i, ok = 1;
    unshield_set_log_level(0);
    u = unshield_open(cab);
    if (!u) {
        char text[SETUP_PATH + 64];
        snprintf(text, sizeof text, "Could not read %s.", cab);
        os_message(text, OS_ERROR);
        return 0;
    }
    for (g = 0; ok && g < unshield_file_group_count(u); g++) {
        UnshieldFileGroup *fg = unshield_file_group_get(u, g);
        const char *sub = !strcmp(fg->name, "Sound Files") ? "Sound" : "";
        for (i = (int)fg->first_file; ok && i <= (int)fg->last_file; i++) {
            const char *dir, *name;
            char folder[SETUP_PATH], path[SETUP_PATH], *c;
            if (!unshield_file_is_valid(u, i))
                continue;
            dir = unshield_directory_name(u, unshield_file_directory(u, i));
            name = unshield_file_name(u, i);
            snprintf(folder, sizeof folder, "%s%s%s%s%s", dst, *sub ? SEP_S : "", sub, dir && *dir ? SEP_S : "",
                     dir ? dir : "");
            for (c = folder; *c; c++)
                if (*c == '\\' || *c == '/')
                    *c = SEP;
            os_make_dirs(folder);
            snprintf(path, sizeof path, "%s" SEP_S "%s", folder, name);
            if (os_progress_show("Unpacking", path)) {
                ok = 0;
            } else if (!unshield_file_save(u, i, path)) {
                char text[SETUP_PATH + 64];
                snprintf(text, sizeof text, "Could not unpack %s.", name);
                os_message(text, OS_ERROR);
                ok = 0;
            }
        }
    }
    unshield_close(u);
    return ok;
}

/* The CD's videos (CIV2's KINGS, VIDEO) into game_dir, where it has none. */
static int copy_videos(const char *cd, const char *game_dir)
{
    static const char *const folders[] = {"KINGS", "VIDEO"};
    char civ2[SETUP_PATH], from[SETUP_PATH], to[SETUP_PATH];
    size_t i;
    if (!os_entry(cd, "CIV2", civ2, sizeof civ2))
        return 1;
    for (i = 0; i < sizeof folders / sizeof folders[0]; i++) {
        snprintf(to, sizeof to, "%s" SEP_S "%s", game_dir, folders[i]);
        if (os_entry(civ2, folders[i], from, sizeof from) && os_dir_exists(from) && !os_dir_exists(to) &&
            !copy_tree(from, to))
            return 0;
    }
    return 1;
}

/* ---- the set-up ---- */

/* GameData from source (an installed game's folder or the CD), and from
   the CD (cd, may be "") its videos.  1: done. */
static int set_up(const char *game_dir, const char *source, const char *cd)
{
    char done[SETUP_PATH];
    FILE *f;
    int ok;
    os_progress_show(setup_game_cd(source) ? "Unpacking the game from its CD" : "Copying the game", source);
    os_make_dirs(game_dir);
    if (setup_game_cd(source)) {
        char cab[SETUP_PATH];
        os_entry(source, "DATA1.CAB", cab, sizeof cab);
        ok = unpack_cab(cab, game_dir);
    } else {
        ok = copy_tree(source, game_dir);
    }
    if (ok && *cd)
        ok = copy_videos(cd, game_dir);
    if (!ok)
        return 0;
    snprintf(done, sizeof done, "%s" SEP_S "%s", game_dir, DONE_FILE);
    if ((f = fopen(done, "w"))) {
        fprintf(f, "OpenCiv2: the game set up from %s%s%s.\n", source, *cd && strcmp(cd, source) ? ", videos from " : "",
                *cd && strcmp(cd, source) ? cd : "");
        fclose(f);
    }
    return 1;
}

int setup_choose_game(int argc, char **argv, char *game, size_t size)
{
    char game_data[SETUP_PATH], done[SETUP_PATH], source[SETUP_PATH], cd[SETUP_PATH] = "";
    int again, ok, cancelled;

#ifdef __APPLE__
    /* (started from the Finder by an older macOS: its process serial number) */
    if (argc > 1 && !strncmp(argv[1], "-psn_", 5))
        argc = 1;
#endif
    again = argc > 1 && !strcmp(argv[1], "--setup");
    if (argc > 1 && !again) {
        /* a folder: the game, played where it is */
        if (!os_dir_exists(argv[1])) {
            char text[SETUP_PATH + 64];
            snprintf(text, sizeof text, "There is no folder %s.", argv[1]);
            os_message(text, OS_ERROR);
            return 0;
        }
        snprintf(game, size, "%s", argv[1]);
        return os_program_files();
    }
    os_current_dir(game, size);
    if (argc < 2 && ((getenv("CIV2_SCRIPT") && *getenv("CIV2_SCRIPT"))
#ifndef _WIN32
                     || setup_game_folder(game)
#endif
                     ))
        /* a replay (the test harness), or (macOS, Linux) started in the
           game's folder: the game where it is run */
        return os_program_files();
    os_game_data(game_data, sizeof game_data);
    snprintf(done, sizeof done, "%s" SEP_S "%s", game_data, DONE_FILE);
    snprintf(game, size, "%s", game_data);
    if (os_file_exists(done) && !again)
        return os_program_files();

    /* where the game is: --setup FOLDER, the installed game, the CD, else asked */
    if (!os_find_cd(cd, sizeof cd))
        cd[0] = 0;
    if (again && argc > 2)
        snprintf(source, sizeof source, "%s", argv[2]);
    else if (!os_find_installed(source, sizeof source))
        snprintf(source, sizeof source, "%s", cd);
    while (!setup_game_folder(source) && !setup_game_cd(source)) {
        if (source[0]) {
            char text[SETUP_PATH + 160];
            snprintf(text, sizeof text, "%s has neither an installed Civilization II Multiplayer Gold Edition nor "
                     "its CD.", source);
            os_message(text, OS_WARNING);
        } else {
            os_message("Civilization II Multiplayer Gold Edition was found neither where it is usually installed "
                       "nor in a CD drive. Please show where it is: the folder it is installed in, or its CD.",
                       OS_INFO);
        }
        if (!os_ask_folder(source, sizeof source))
            return 0;
    }
    if (setup_game_cd(source))
        snprintf(cd, sizeof cd, "%s", source);
    if (!os_confirm(source, game_data))
        return 0;
    copy_dest = game_data;
    os_progress_open();
    ok = os_program_files() && set_up(game_data, source, cd);
    cancelled = !ok && os_progress_stopped();
    os_progress_close();
    if (cancelled)
        os_message("The set-up was stopped; it starts again the next time.", OS_INFO);
    return ok;
}
