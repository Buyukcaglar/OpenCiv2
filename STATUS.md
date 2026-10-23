# Status

## Coverage (re/manifest.tsv)

| status      | functions | meaning |
|-------------|-----------|---------|
| auto        | 4040 | game functions, translated from Ghidra's output by `tools/gen_c.py`; since October 2026 the source, edited directly, in files by subject (src/auto/city.c, unit.c, map.c ...) |
| game        |  114 | reconstructed by hand (src/game/*.c) |
| ehfunclet   |  462 | C++ unwind funclets; inlined into their callers, never called on their own |
| crt         |  295 | statically linked MSVC 4.2 debug C runtime: the native builds use their own C library (src/native/crt.c for what differs) |
| asm         |    2 | `ASMGRAF` section: 16-bit leftovers from the Win16 version, unreachable |

About 221,000 lines of C.  Every function that can execute has C source.

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
| `build/civ2-port` (64-bit, portable to macOS and Windows) | wasm32 → wasm2c → cc |

All 13 scenarios of `harness/scripts` (the six above plus mapview, units,
reports, saveload, diplomacy, the WWII scenario and the cheat menu with
every rules editor) give pixel-identical screenshots and the identical
`rand()` trace, except 2 anti-aliased pixels of one edit field in the
terrain editor.  `harness/diff_suite.sh` plays a 30-turn autoplay and two
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
  initializers in original address order (src/data/gamedata.c, made by
  tools/unglobal.py; strings named from their text).  Where the code relies
  on data lying together, it is one object: Win32 structs and arrays the
  decompiler split into locals, and 115 packed structs of globals
  (`pedia_window_block.pedia_wonder_entry_count`) -- a window object and the
  fields the code also names as globals, tables split into columns.  Found
  with AddressSanitizer over every replay (build_native.py --target
  linux32asan; learned extents in re/data_extents.tsv), by checking that
  every initial value and every data pointer matches the original image, and
  by the replays: every replay runs clean under AddressSanitizer.  Untested
  code may still rely on two variables being adjacent; gamedata.c keeps
  them in the original order (-fno-toplevel-reorder in the gcc builds).  A
  DIB's pixels get a few bytes of slack as on Windows (the GIF decoder
  writes one byte past the last row).
* Coverage of the comparison: the scripts execute 2,295 of the 3,417
  compiled game functions (67%, 51% of lines; `tools/coverage_report.py`
  with the linux32cov build, per function in re/coverage.tsv).  Never
  executed: multiplayer (parley, net), sound and video, council, the
  editors' rarely used dialogs, atexit destructors.  Untested paths may still differ.  Add a script under `harness/scripts/`, record it with
  `make ref SCRIPT=...` and compare with `make native-suite`.
* **Blinking unit under a modal dialog.**  When the spy mission dialog
  opens over the map (harness/scripts/conquest.txt, Roman phalanx at
  22,58 of Ca_Auto.SAV), our build has been seen to leave the active unit
  with its top rows missing; the original showed it whole.  The blink is
  timer-driven, so the script takes no screenshot there; not yet
  explained.
* **Map left black after Arrange Windows.**  After the View menu's zooms
  and Arrange Windows (harness/scripts/menuview.txt run in the old order),
  a cancelled Save Game leaves the main map black; the original repaints
  it.  Message traces (harness/msgdiff.sh) differ in four lines: Wine has a
  WM_PAINT pending for the map view (window 19) when the large child window
  Arrange Windows showed and hid (window 23) is hidden again, and does not
  erase the map frame (window 18) when it is resized.  Not yet explained.
* **Effects editor repaint order.**  When the effects editor's "New Value"
  box closes (harness/scripts/editors.txt), our list is drawn over the top
  8 pixels of the OK/Edit/Help/Cancel buttons; in the original the buttons
  end up on top (the controls overlap without WS_CLIPSIBLINGS, so the order
  in which they repaint decides).
