/* The game's static data (the original's .rdata and .data), declared by
 * subject in src/data/state/ (tools/state_split.py) and defined in
 * gamedata.cpp in the original's address order (tools/unglobal.py made the
 * variables from the single struct that kept the original layout).
 *
 * Records (re/state_records.txt, tools/state_records.py): variables lying
 * together and describing one thing are one struct, its single instance
 * where they were (`mapgen.climate`, `prefs.difficulty`, `snd_wave.sources`):
 * a loose run of globals is defined as that struct in gamedata.cpp; a run
 * inside a contiguity block (`*_block`: data the code reaches across, kept
 * as one object) is a member of the block, named by an inline constexpr
 * reference, the same constant address.  gamedata.cpp checks every member's
 * offset; the layout check (gamedata_check_layout) the rest.
 *
 * Loose variables a single function uses are marked `only F uses it`: the
 * original's statics of that function, kept here so that the data keeps its
 * layout.  RODATA: read-only (the .rdata texts and tables). */
#ifndef CIV2_GAMEDATA_H
#define CIV2_GAMEDATA_H

#include "civ2types.h"

/* RODATA: the original's read-only data (.rdata texts and tables nothing
   writes), const for the game's code, which the compiler then keeps from
   writing them (a write through a cast to a non-const pointer it cannot see:
   those were checked by hand; lang_file_ext and setup_chosen_leaders, which
   start with values but are written, and what gamedata_init fills in stay
   writable).  gamedata.cpp defines them without const, in the data section
   with the rest: gcc puts const and writable variables in different
   sections. */
#ifdef CIV2_GAMEDATA_DEFINE
#define RODATA
#else
#define RODATA const
#endif

/* The game's state, by subject (tools/state_split.py). */
#include "state/game.h"
#include "state/civ.h"
#include "state/city.h"
#include "state/unit.h"
#include "state/ai.h"
#include "state/diplomacy.h"
#include "state/map.h"
#include "state/mapview.h"
#include "state/network.h"
#include "state/reports.h"
#include "state/pedia.h"
#include "state/spaceship.h"
#include "state/editor.h"
#include "state/window.h"
#include "state/controls.h"
#include "state/graphics.h"
#include "state/text.h"
#include "state/sound.h"
#include "state/support.h"
#include "state/crt.h"
#include "state/misc.h"
#include "state/strings.h"

/* Sets the addresses the data holds (functions, other data). */
EXTERN_C void gamedata_init(void);

#endif
