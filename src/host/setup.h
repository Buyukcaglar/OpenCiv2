/*
 * Windows: the game set up beside the program from the user's copy
 * (src/host/setup_win.c).
 */
#ifndef CIV2_SETUP_H
#define CIV2_SETUP_H

#include <stddef.h>

/* The program's own files, as resources (src/host/setup.rc): deflated. */
#define SETUP_RES_FONTS 1
#define SETUP_RES_FONTS_AA 2

/* Where the game is, before it starts (port_main.c): with no arguments
   GameData beside the program, set up first if need be; "--setup [FOLDER]":
   set up again (from FOLDER: an installed game or the CD); a folder: the
   game, played where it is.  The fonts beside the program (data), from its
   resources, where missing.  1: game set (a Windows path); 0: quit. */
int setup_choose_game(int argc, char **argv, char *game, size_t size);

#endif
