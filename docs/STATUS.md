# Status

## Coverage (re/manifest.tsv)

| status      | functions | meaning |
|-------------|-----------|---------|
| auto        | 4040 | game functions, translated from Ghidra's output by `tools/gen_c.py`; since October 2026 the source, edited directly, in files by subject (src/auto/city.cpp, unit.cpp, map.cpp ...) |
| game        |  114 | reconstructed by hand (src/game/*.cpp) |
| ehfunclet   |  462 | C++ unwind funclets; inlined into their callers, never called on their own |
| crt         |  295 | statically linked MSVC 4.2 debug C runtime: the native builds use their own C library (src/native/crt.cpp for what differs) |
| asm         |    2 | `ASMGRAF` section: 16-bit leftovers from the Win16 version, unreachable |

About 221,000 lines of C++ (the game) and C (the platform layer).  Every
function that can execute has source.

## Builds

The native builds below.  Until step 5 of the clean-up (removing the
emulation of the original's memory layout) there was also a Windows build
grafting the compiled functions onto the original `civ2.exe`
(tools/build_recon.py; `make bisect` swapped single functions back to the
original's): retired, available at the git tag `pre-step5`.  It and the
standalone executable written from it were pixel-identical to the original
with the identical `rand()` sequence on these scenarios:

| scenario  | what it does | rand() calls |
|-----------|--------------|-------------:|
| menu      | boot to the main menu | 772 |
| newgame   | all new-game dialogs, world generation, first screens | 13 280 |
| loadgame  | load `Ca_Auto.SAV` | 1 039 |
| turns     | loaded game, 8 turns of AI play | 1 109 |
| advisors  | every advisor / report screen (F1–F9, F11) | 1 055 |
| long50    | new game, found a city, 50 turns of play | 14 057 |

## Native builds (no Windows, no Wine)

See `README.md`.  The Windows API is implemented over SDL2 (`src/platform`,
`src/host`); checked with `harness/native_suite.sh` against the same Wine
recordings:

| build | how |
|-------|-----|
| `build/civ2-linux32` | gcc -m32 |
| `build/OpenCiv2` (64-bit, portable to macOS and Windows) | wasm32 → wasm2c → cc |

All 36 scenarios of `harness/scripts` give pixel-identical screenshots and
the identical `rand()` trace.  The last few pixels came from Wine details
now matched: a combo box's text clipped to its field (a glyph's overhang
shows), a multiline edit's text clipped to its format rectangle and drawn
in Uniscribe items each on its own background box, LineTo's Bresenham
rounding per octant, and a list box drawing its focus rectangle at once
on losing focus (tools/probe: edititems, uspprobe, lineprobe); a window
that grows invalidates only its new strips, as Wine's server keeps the old
client pixels (menuview-arrange); a CS_OWNDC window has one DC, which
BeginPaint clips to the update region (conquest-spy: the blinking unit under
the spy dialog).  `harness/diff_suite.sh` plays a 30-turn autoplay and two
random-click scripts on both builds: identical (3 392 `rand()` calls).

Reads of locals the 1997 code never initialises are the main source of
differences between builds: valgrind finds them, `CIV2_STACKPROBE` reads
what the original's stack holds there, and the function sets those locals
to those values first (marked "stale stack the original reads").  What made it so: matching Wine's exact message semantics
(window positioning, painting and exposure, activation and focus, key
state, posted messages before input) -- `harness/msgdiff.sh` and
`harness/clockdiff.py` compare a native run with the Wine reference
message by message and clock event by clock event.

## Harness notes

* Replay is deterministic (virtual clock, synchronous timers, in-process
  input, scripted file dialogs).  Two runs of the original are identical,
  which is what makes the comparison meaningful.
* `hook/compat.c` works around a crash of the *original* game under wine
  (EDIT control extra-bytes assumption) that made founding a city impossible.
* Waits in scripts are virtual milliseconds at 10 ms per idle message-loop
  iteration; world generation needs ~600 s of virtual time.

## Known limitations / next steps

* **Names and types.**  Everything the game code (src/auto, but for the
  MSVC runtime) refers to has a name: every function, global and class
  (no FUN_, DAT_ or C_ placeholders left), every parameter and local
  (no param_N, iVarN, pCVarN or local_XX: about 14,500 named by
  tools/name_vars.py from proposals per slice of functions, src/game
  included), every goto label (no LAB_ADDR), every class and struct field it
  accesses by name (tools/field_uses.py dossiers, tools/apply_field_names.py),
  and Ghidra's undefinedN types are explicit integers (i8, i16, i32, i64).
  Each rename was checked by building: the Windows build stayed byte for byte
  the same.  Evidence for names: re/function_names.tsv, re/global_names.tsv,
  re/type_names.tsv, re/field_names.tsv; names live in re/symbols.tsv and
  those maps, tools/rename.py applies them.  Layouts: the accesses by
  offset (`this->pad_48 + 0x10`, the object read as an array of cells
  `this[0x567].field_0`, and past a class's declared end) became fields at
  those offsets (tools/layout_fields.py: the pad_ gaps split, classes
  extended, ClassExt structs where a class must keep its size; every field
  checked with offsetof), named from their uses (re/layout_names.tsv).
  None is left: no field_XX, pad_ or cell access in the game code; the gaps
  no code touches stay pad_ in the headers.  The machine code is the same
  but for register choice and addressing modes in six functions (an index
  through a field now, `base + 4 + 4*i` for `base + 4*(i + 1)`).
* **No emulation of the original's memory layout** (step 5).  Locals are
  ordinary locals (tools/unframe.py), callbacks and data are referred to by
  name (no ADDR), and the static data is 4,989 ordinary variables with C
  initializers in original address order (src/data/gamedata.cpp, made by
  tools/unglobal.py; strings named from their text).  Where the code relies
  on data lying together, it is one object: Win32 structs and arrays the
  decompiler split into locals, and 115 packed structs of globals
  (`pedia_window_block.pedia_wonder_entry_count`) -- a window object and the
  fields the code also names as globals, tables split into columns.  Found
  with AddressSanitizer over every replay (build_native.py --target
  linux32asan; learned extents in re/data_extents.tsv), by checking that
  every initial value and every data pointer matches the original image, and
  by the replays: every replay runs clean under AddressSanitizer.  Code no
  replay runs may still reach from one variable into the next, so the data
  keeps the original's layout exactly: one section, in address order, each
  variable at its original alignment, the bytes nothing names kept
  (GAMEDATA() in gamedata.c; -fno-toplevel-reorder for gcc, no forward
  references in static initializers for clang).  Every build checks this
  when it starts (gamedata_check_layout(), generated by build_native.py from
  the address comments) and native_suite.sh fails a run where it differs.  A
  DIB's pixels get a few bytes of slack as on Windows (the GIF decoder
  writes one byte past the last row).
* **C++** (step 6, complete: this and the items below).  The game (src/auto, src/game, src/data,
  src/native) compiles as strict C++: g++ for the linux32 builds, the wasm
  toolchain's clang++ for the portable ones; the platform layer stays C
  (extern "C" at the boundary).  The conversion was checked function by
  function: the machine code of each one is identical to that of the same
  source compiled with g++ -fpermissive (C's integer/pointer conversions;
  CIV2_CXX=permissive, tools/cxx_compare.py), which passes the suite as the C
  build did.  Many conversions are still explicit casts where headers give
  the wrong type (`iptr` for pointers, `void *` for strings); the classes,
  typed callbacks and the rest of the modernization come next.  Types and
  fields are recovered per subsystem: raw offset accesses
  (`*(T *)(p + 0x34)`) went from over 5,100 to 1,100, now struct members
  (network sessions and messages, native windows, dialog lists, scenario
  events, Civilopedia lists, ...).  These rewrites are checked by
  construction instead of by identical machine code: every member's offset
  and type are static_asserts (tools/cxx_layout.py, tools/cxx_fields.py,
  tools/cxx_members.py), uses keep their integer meaning (arithmetic stays on
  the old integer type, never pointer arithmetic), the compiler rejects any
  implicit pointer/integer conversion, and the suite runs on every batch.
  Two bugs of
  the C version surfaced and are fixed: the parley window chose its
  right-hand pane's callbacks by adding the distance between two functions in
  the original executable to a function's address (a garbage pointer in any
  other build; the eight handlers it meant are restored), and unit moves
  compared the address of human_civ, not its value, so
  unit_move_by_local_human was never set.
* **Classes** (step 6).  The decompiler's partial views of each class
  (structs sized by how far one function reads) are folded into one struct
  per real class, with C++ inheritance for bases: Dialog (ScenarioEvents
  on it); the controls on Control (Button, Checkbox, Scrollbar,
  EditControl, ComboBox, ListBox, Hotspot, Hyperlink, RadioGroup,
  SpriteButton); the windows on WndBase -> ModalMenuWindow (Wnd, the city
  view, throne room, spaceship, diplomacy and movie windows); the surfaces
  on DibSurface -> SurfaceWindow -> FrameWindow (the map, city, editor,
  picture, Civilopedia, council, parley windows ...).  Sizes are the
  constructors' allocations.  Each fold was checked by layout (no member
  moved) and access by access (every member access compared function by
  function before and after), plus the suite.  The methods are member
  functions of their classes (tools/cxx_methods.py; old and new names in
  re/methods.tsv): 927 of the 1,030 `__thiscall` functions.
  `void __thiscall wnd_show(Wnd *self, int x)` became `void Wnd::show(int x)`,
  declared in the class, its body using `this` (`self->` dropped where no
  local has the member's name), and every call `wnd_show(w, 3)` became
  `w->show(3)`.  Members are named without the class's prefix
  (`city_window_draw_citizens` -> `CityWindow::draw_citizens`;
  `*_ctor`/`*_dtor` -> `construct`/`destruct`), the whole old name kept
  where the short one would clash with a member, a keyword or a macro (13,
  e.g. `DibSurface::surface_width`, its field being `width`).  No C++
  constructors, destructors or virtual functions: objects live in the
  original's static data and are built explicitly, and the original's
  vtables are data the game reads.  The same name in a base and a derived
  class (`construct`, `create`) is allowed; a call that could reach the
  other one is qualified (`obj->Control::construct()`), and a global a
  member would now hide inside a member function is written `::name`.  What
  stays free (the reason in re/methods.tsv): 17 whose address is taken (the
  array constructor/destructor iterators' ctors and dtors, sprite_init and
  sprite_destroy passed the same way, two in data tables), 49 whose `self`
  is `void *` (mostly unwind-funclet destructors), 33 on a decompiler view
  (a struct one function's accesses describe, `FileSeekView`), 3 that
  assign `self` (font_destroy, menu_dtor, palette_destroy) and
  net_session_init.  Two members call rand(): their trace still names them
  by the free name (`crt_rand_at("palette_new_version")`), as the
  original's does.  Checked function by function: the machine code of every
  function is the same as before (tools/cxx_compare.py --map re/methods.tsv:
  member functions under g++ -m32 take `this` as the first stack argument,
  as the free functions took `self`) but for 22, which differ in register
  choice, stack slots or the order of independent instructions or
  comparisons (C++17 evaluates `obj` in `obj->f(args)` before the
  arguments); and the suite after each subsystem.
* **Structured control flow** (step 6).  The decompiler's gotos (836) are
  loops, if/else, break/continue and early returns; 327 remain, each a
  forward jump to a function's shared cleanup exit (most: the RAII step
  removes them), a jump out of nested loops, or a jump between distant
  sections of the largest functions (ai_unit_choose_orders' shared tails:
  the function-splitting step).  tools/cxx_gotos.py did the safe patterns
  (a third), the rest was rewritten by hand.  Checked function by function
  with tools/cfg_compare.py (cfg_check.sh): each function's control-flow
  graph walked against the previous version's, at -O0 and then -O2; the
  functions that still differ (duplicated tests, folded conditions,
  cleanup copied into early returns) were reviewed by hand twice, those
  replays run by the suite too.  Found on the way: diplo_count_border_intruders
  examines only the first tile with an intruder per city (the original
  does the same; kept, commented).
* **Smaller functions** (step 6).  The functions the original wrote as one
  long body are split into named parts, each beside the function it came
  from with a comment saying so: before, 69 functions were over 300 lines
  and 9 over 1,000 (the AI's unit orders 2,849, the parley window 2,282,
  production choice 1,985); now 9 are over 300 (data tables and flat
  switches of short cases: the spaceship's part rows, the network message
  dispatch, the events editor's trigger lists) and none over 1,000.
  Locals shared between parts are passed by reference or in a small state
  struct, so values that carry over (the original's stale reads included)
  flow as before; a part that called `_rand()` names the original function
  in the rand trace (`crt_rand_at("...")`).  Checks: each split function
  compiled with its parts forced inline and compared with the previous
  version (tools/cfg_compare.py, machine code; optimized GIMPLE graphs;
  for ai.cpp a round trip that puts every part back and gets the original
  text token for token), the uninitialized-read warnings compared (no new
  real ones), then the suite and the network test.  Splitting moves gcc's
  register and block choices, so most split functions are not identical
  at the instruction level: those were reviewed by hand and by the
  replays.
* **Named constants** (step 6).  The game's magic numbers are enumerations
  and flag constants (src/include/enums.h): unit types, improvements and
  wonders, advances, governments, terrain, unit orders, roles, domains,
  difficulty levels (named after the original RULES.TXT's slots, as
  modders do: a scenario's rules may put another unit in slot 46), the
  network message types (the original's NM_* table), the main menu's
  commands and the sound effects (the original's WAV table); flag bits of
  units, unit types, cities, civilizations, treaties (civ a toward civ b),
  tiles, the game options, rules, game state, messages and spaceships.
  About 4,900 numbers replaced by tools/name_constants.py (comparisons,
  assignments, switch cases, call arguments and table indexes where the
  value is known to be of the kind: a field, a call, a local named for it
  or assigned only from such values; a flag word read a byte at a time as
  `(byte)(t >> 8) & (TREATY_WAR >> 8)`).  The enums are unscoped with the
  underlying type of the field (the 32-bit flag words: i32), so each
  enumerator promotes and converts as the int literal did: the machine code
  of every function is the same as before (tools/cxx_compare.py, all
  files), and the suite passes.  Bit meanings come from the functions that
  set and test them; the uncertain ones are marked "?" in the header.  Left
  as numbers: sizes, coordinates and arithmetic; ranges (`orders < 4`,
  `improvement < 0x27`); resources (terrain 11..32); masks of more than
  four bits or bits without a name; unsigned literals (`0x8000U`, an
  enumerator would be int); flag words reached through pointer arithmetic;
  dialog control ids and other UI message numbers.
* **Grouped state** (step 6).  The game's ~3,600 globals are grouped by what
  they describe, without moving a byte.  Records (re/state_records.txt,
  tools/state_records.py): 109 structs whose single instance is where their
  variables were: 63 made of 309 loose globals (`mapgen.climate`,
  `snd_wave.sources`, `dlg_style.text_color`, `map_data.tiles`,
  `pathfind.unit_type` ...), defined as one variable in gamedata.cpp with
  the old initializers, and 46 made of 596 members of the contiguity blocks
  (`prefs.difficulty`, `scenario.max_turns`, `diplo_eval.ai_fear_level`,
  `city_calc.happy_count`, `advisor_state.scrollbar`, `textbuf.buf` ...),
  nested in their block and named by an `inline constexpr` reference (the
  same constant address, so the code is the same); the network session
  object is `net`, its members without the `net_` prefix
  (re/state_renames.tsv, tools/state_rename.py).  Uses through a block's
  name (`some_block.member`) went from 15,000 to 5,200 (window objects,
  sprites, tables the code indexes across).  The declarations are split
  into a header per subject (src/data/state/: game, civ, city, unit,
  diplomacy, map, network, window, graphics, sound ...; the subject is the
  module whose code names them most, tools/state_split.py), the 2,617
  texts in state/strings.h sectioned the same way; gamedata.cpp keeps the
  definitions in address order.  2,891 read-only texts and tables are
  `const` for the game's code (RODATA: gamedata.cpp defines them writable,
  as gcc will not mix const and writable variables in one section); the
  compiler rejected no write (24 locals and two parameters that hold
  them became `const char *`), and the casts it cannot see through were
  checked: lang_file_ext and setup_chosen_leaders are written (they stay
  writable), as is what gamedata_init fills in.  101 loose variables only
  one function uses (the original's statics) stay where they are, marked
  `only F uses it`.  Checks: each record member's offset is a
  static_assert, the layout check and tools/state_compare.py (every data
  symbol of the previous build at the same section offset with the same
  size, or folded into a record spanning exactly its members; the data
  object's bytes the same; the machine code of every function compared
  with its absolute addresses as symbol+offset): the code is the same but
  for 52 game functions, all of them using loose variables made records
  (the block records compile identically: their members already were one
  object), where gcc, seeing one record instead of separate variables,
  keeps the record's address in a register and addresses members from it
  (`movswl 0x30(%eax,%edx,2)` for `start_positions.y[i]`), with the
  register, operand order and branch layout changes that follow; reviewed
  by hand.  Besides: gamedata_check_layout (fewer entries) and the C
  runtime's start-up glue (an end-of-data address).  The suite passes on
  both builds, a replayed game saves the same file (Ctrl+S after three
  turns), and the two-game network test with diplomacy passes.
* **Scope-bound release** (step 6, RAII).  src/include/scoped.h:
  `ON_SCOPE_EXIT(stmt)` (a statement run on every path out of the scope,
  in reverse order of declaration) and `ScopedFile` (a C runtime file
  closed at scope exit), forced inline (the builds use -fno-inline).  The
  decompiler's inlined MSVC unwind funclets that destroyed a local object
  on each return (`/* inlined unwind funclet ... */ { dlg.Dialog::destruct(); }`)
  became one `ON_SCOPE_EXIT(dlg.Dialog::destruct());` after the object's
  construction, in the block that holds it (tools/raii_locals.py; with
  the hand conversions below, 225 guards in 169 functions: dialogs,
  palettes, surfaces, sprites, fonts, buttons, DLL handles, arrays of
  them), and the MSVC trylevel locals
  (`eh_state`, `try_level`, `seh_handler` ..., written, never read) were
  dropped (tools/raii_tidy.py, with the `if (c) { } else` blocks this
  left).  By hand, the shared cleanups that `goto cleanup;` reached:
  save_read_game and save_write_game (the file, the hot-seat player mask,
  the mode adaptation after the close), rules_write_sections and
  events_write_file (two files and the directory), the password dialog
  (the turn timer), net_session_init, the unit menu's busy flag, the
  sprite sheet import, the explosion animation (zoom scale, redraw flag),
  file_read_nth_line; gotos 180 -> 112.  The game's objects keep their
  explicit construct/destruct (no C++ constructors or destructors).  Left
  as written: the funclets inside class destructors (members of objects
  in static data, 201), two functions whose dialog a split-off part
  destroys on some paths (net_client_turn_loop, net_popup_queue_show_next);
  releases followed by more work on a single path (GetDC/ReleaseDC,
  SelectObject restores, GlobalLock/Unlock, the wait cursor, the modal
  loop's owner disable/enable: no function releases them on several
  paths), releases in a different order on different paths or before a
  long epilogue (gfx_build_grey_remap's memory handles, file_copy,
  unit_move_dir's map lock, prefs_save_civ2dat's remove after the close),
  and gotos to epilogues that are not releases (diplo_ai_meet_player,
  setup_choose_tribe, the city change dialog, the parley lists, the
  events parser's error report) or jumps out of nested loops.  Checked
  function by function (tools/raii_check.sh): each converted file
  compiled at -O1 with the build's -fno-inline against the previous
  version, the control-flow graphs compared (tools/cfg_compare.py); the
  85 functions whose graph differs (the compiler shares one copy of the
  release between paths) make the same sequences of calls on every path
  (tools/calls_compare.py: the two call automata accept the same words;
  it caught the two functions above).  20 of them are not run by the
  replays (network dialogs, council, the PBEM and network setup ...).
  The suite passes on both builds (linux32 and the portable build, 36
  of 36), the Windows build compiles, the replays under ASan report
  nothing new (two reports, in code this step did not touch, that the
  previous commit has too: events_compact frees the string pool
  editor_text_dlg_on_ok then writes to, and a split part of
  city_choose_production reads past a local), and the two-game network
  test with diplomacy passes (the client under ASan).
  Both fixed after: the split had turned `score--` into `*score--`
  (the pointer, not the score) in city_choose_production_diplomat_score;
  the pool is the original's own bug (its callers keep event pointers
  across events_compact, valid under Wine only because the new pool is
  the block just freed), so events_compact keeps the pool's block.
* **Unit tests** (step 6, the last part).  `make test` runs 10,485 recorded
  calls of 832 of the game's functions in 2.5 seconds, without the game's
  files (docs/DEVELOPMENT.md "Unit tests"): each call recorded from the
  replays of 35 scenarios (all but `menu`, which runs none that qualify) by
  the recording build (tests/unit_record.c: -finstrument-functions, the
  arguments, the game's data and the map at entry, the return value through a
  return-address trampoline, the state at exit), set up again by the runner
  (tests/unit_run.c) and compared byte for byte, `rand()` calls included (the
  seed is game data).  Calls that reach the platform layer, the heap or
  state outside the game's data are not taken; the runner keeps the cases it
  reproduces twice in each of three processes.  By file: window 112 functions,
  city 104, unit 99, map 71, civ 68, graphics 55, ai 55 (of the 57 the replays
  run), text 53, diplomacy 35, game 29 ... (tests/unit/cases.tsv): combat
  (strengths, odds, the fight, veterans, city defences), movement and paths,
  city food, shields, trade, happiness, workers and production choice, the
  AI's assessments and unit orders, research cost and choice, diplomacy's
  evaluations and treaties, map generation steps; 206 cases call `rand()`.
  Of the 2,225 game functions these replays run, 832 have cases: the rest
  draw, wait for input or read files, or are called only with pointers into
  the heap.  Not covered: rules parsing and the save/load round trip (they
  read and write files; the replays check them), and the top-level turn
  functions that redraw (their parts are covered).  2.6 MB of data (gzip;
  state as deltas from case to case; no text from the game's files: where the
  data holds text, tests/unit/textmask.tsv from tools/unit_textmask.py, the
  cases have what the initializers leave).  Deliberate one-line mutations,
  reverted after, each fail: an attack strength one too high (19 cases of
  unit_attack_strength and unit_resolve_attack), the AI's food box constant
  13 -> 12 (6 cases of city_calc_food_box_rows, city_calc_unit_support,
  city_recalc), the research cost's floor of advances 1 -> 2 (10 cases), one
  more food per citizen in the production choice's surplus (1 case).  The
  release workflow runs the tests (a job of its own, the 32-bit Linux
  build).  The only game-side changes are for the tests' builds and compile
  to nothing in the others (CIV2_FIXED_DATA: the game's data in a section at
  a fixed address; CIV2_UNITTEST: main() runs the cases); the suite passes
  36 of 36 on linux32, and the portable and Windows builds compile.
* **The original's bugs** (docs/BUGS.md: 18, from the reconstruction, the
  compiler's uninitialised-read warnings and the community's lists, CIV2UIA's
  among them) are fixed by default: the AI's attitude starting from a stale
  local (the "aggression bug"), border intruders counted on one tile per city,
  the long-move warning's counter, city names in a second game, citizens'
  click areas, the focus of a city opened from an advisor, Hall of Fame scores
  over 32767, cities past size 127, a hot-seat read past the knowledge maps,
  and smaller ones.  `CIV2_CLASSIC=1` keeps them (the original game, as it
  keeps its look); replays and unit tests always run the original's code, and
  network games the original's game rules (the fixes that change only what one
  player sees stay on).  The suite passes 36 of 36 and `make test` all cases;
  with the fixes on in the replays (`CIV2_TEST_FIXES=1`, tests only) none
  crashes, and the WWII scenario's AI goes on calling `rand()` where the
  original's, gone hostile, stops.
* **Interface additions** (docs/EXTRAS.md): CIV2UIA's interface features, written
  anew from its description, on by default and each switchable in CIV.INI's
  `[OpenCiv2]` section: the mouse wheel and middle button, the Activate Unit list
  past 9 units, settlers' work counters, the turn in the status panel, research
  figures, free buildings in the Trade Advisor, the supported units' total, scroll
  bar and order, attitude colours, radio button hotkeys, quick information with
  Ctrl, Cancel and costs in Change Production, a City Status advisor that sorts and
  changes production, Shift on specialists, popups shown on the map, colour
  correction, coins in the Foreign Minister, Arrange Windows S/L, path lines with
  Shift, sentries in halftones, new games at zoom 1:1.  Off with `CIV2_CLASSIC=1`
  and in replays and unit tests (`CIV2_TEST_EXTRAS` turns them on in a replay);
  not done yet: resizable advisors and their larger caption area (CIV2UIA 26, 27:
  each advisor lays itself out for its fixed height).
* **Rule changes** (docs/EXTRAS.md): CIV2UIA's, off by default, each switched on
  in CIV.INI's `[OpenCiv2]` section, off in network games, replays and unit
  tests: a worker hands its work to the one that joins it and stops, Go To past
  foreign units, Wait flags per stack and rotation from where the last unit
  started, Shift+right click moves the stack's units of a type, `U` sentries the
  stack's land units; limits for the retirement year, the population (to 3,275,800
  x 10,000), the gold (to 1,000,000) and a custom map's squares (to 32767).  The
  units' limit (2048) is left out: more units need a larger unit table than the
  original's state layout and make saves the original cannot load.
* **Network play** (multiplayer over TCP/IP).  The original's networking
  library, XDaemon.dll, is replaced by src/platform/xdaemon.c over sockets
  in the host layer (src/host/host_net.c, BSD sockets or Winsock), speaking
  its wire protocol (docs/xdaemon-protocol.md: TCP 4993 records, UDP 4994
  LAN discovery, the id handshake, host relaying).  `tools/xdnet/nettest.py`
  plays two (or three) games against each other in containers and checks
  the logs (docs/xdaemon-protocol.md §11.1).  Tested, our side under ASan
  where it says so:
  - joining, turns, quitting: ours vs ours, ours vs the original and the
    original vs ours, on a LAN and in Internet mode (127.0.0.1); save and
    load; a player leaving and joining the game in progress; three players
    with either one hosting (the host relaying: the original's and our
    record tags compared on a capture, the same rules); the host rejecting
    a player in its lobby; the host leaving, the client becoming the host
    and playing on (migration); simultaneous moves, the turn timer, the
    multiplayer features, a timer change and option votes, the advisors
    during a network game.
  - the parley, driven on both games (the original's window is fitted to
    our layout, so the same clicks drive both): audiences granted, refused
    by the timeout and granted too late (busy replies), gifts of gold, maps,
    knowledge and units, treaties (cease-fire, peace, alliance, cancelled),
    maps bartered, a proposal, a threat, offers declined and countered,
    the reveal buttons, Check Intelligence, the small layout; ours vs the
    original both ways (ASan), and ours vs ours.  The original and ours put
    the same offers on the wire and answer the timeouts alike.
  - 50 turns, ours (ASan) hosting the original and ours vs ours (ASan):
    no crash, every message received in order and byte for byte, and at
    the end both players' saves hold the same game
    (`tools/xdnet/savecmp.py`; what each game keeps of its own: the saving
    player's header fields, the treaty-turn counters set by the game shown
    an audience request, who stands on tiles no human has seen).
  - the Windows build (OpenCiv2.exe, Winsock) under Wine against ours and
    against the original.
  The game's network code needed: net_session_init (the join dialog)
  written; locals the original's frame kept adjacent (net_send_message's
  buffers, net_process_messages' arguments, four RLE streams, the parley's
  radio labels: garbage treaty names, and the map choice's: a crash on any
  map offer) made structs or arrays; a game-list text buffer 21 bytes
  instead of 256; the difference engine's RLE decoder reading a run's byte
  as a 16-bit word and its encoder reading past its input; a size from the
  original's absolute address; a 5-entry read of a 4-entry label array.  In
  normal play WM_TIMER is Windows' (one pending per timer, no backlog) and
  presenting the screen takes at most a third of the time.  Network code
  run by the tests (`tools/xdnet/netcov.py`, the linux32cov build):
  228 of the 311 network functions (73%; 60% of their lines;
  the scenarios before this round: 168, 54%).  The parley's unit, city
  and advance lists ran in the 50-turn game against the original, outside
  the coverage build.  Never run: the modem, serial, IPX and DirectPlay-lobby
  paths (XD_InitializeModem/Serial/SocketsIPXSPX, XD_ShutdownModem/TEN,
  XD_LobbySendMessage: the library's, dropped), the oversized-message
  callback (no message comes near the limit), the atexit destructors;
  dragging a window by its caption (our panels are fixed unless
  CIV2_CLASSIC=1); offers of cities and war declarations (the test's only
  city to give is a capital, and its civilizations meet no third one);
  the chat macros (Ctrl+F1..F5: they did not fire in ours under the test's
  keys, not yet compared with the original).
* **Play by e-mail** is not in this version of the game, so no scenario can
  record it on the original.  Multiplayer Gold's Multiplayer Game offers Hot
  Seat, Network, Internet and Dial-Up only (GAME.TXT's `@MULTITYPE2`; the main
  menu has no other entry), and the play-by-e-mail setup, setup_pbem_game
  (005ae580, `@PBEM1`: new game, premade world, custom world, scenario, "Make
  an EMAIL Move"), is left over from the earlier Civilization II: the only
  reference to it in civ2.exe is its incremental-link thunk (00403580), which
  no call and no data points to.  A play-by-e-mail save (the `.eml` type,
  game.multiplayer 2) loaded through Load a Game, from the main menu or in a
  game, becomes a single-player game (the loader clears game.multiplayer).  So
  what that mode would run is unreachable in the original and in ours alike:
  the e-mail address asked with each tribe (setup_choose_tribe, mode 2), the
  password set at a player's first turn (civ_password_ensure_set), and at the
  next human player's turn the game saved (game_save_dialog, `@EMAILSAVED`)
  and the "EMAIL the Game" popup (`@EMAILDONE1`/`2`, play_loop_human_turn_start)
  before the turn loop ends.  The game never sends mail itself.  Kept as
  translated, run by no replay.
* Coverage of the comparison: the scripts execute 2,520 of the 3,529
  compiled game functions (71%, 58% of lines; `tools/coverage_report.py`
  with the linux32cov build, per function in re/coverage.tsv).  Never
  executed: multiplayer (parley, net, lobby), sound and video (the
  reference has neither an audio device nor the Indeo codec), council,
  atexit destructors.  Untested paths may still differ.  Add a script under `harness/scripts/`, record it with
  `make ref SCRIPT=...` and compare with `make native-suite`.
