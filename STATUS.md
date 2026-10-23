# Status

## Coverage (re/manifest.tsv)

| status      | functions | meaning |
|-------------|-----------|---------|
| auto        | 4040 | game functions, translated from Ghidra's output by `tools/gen_c.py`; since October 2026 the source, edited directly, in files by subject (src/auto/city.c, unit.c, map.c ...) |
| game        |  114 | reconstructed by hand (src/game/*.c, src/crt/*.c) |
| ehfunclet   |  462 | C++ unwind funclets; inlined into their callers, never called on their own |
| crt         |  284 | statically linked MSVC 4.2 debug C runtime, translated (src/auto/msvcrt.c, the Windows build's only) |
| crt-manual  |   11 | runtime functions defined in src/crt under an asm label (printf family etc.) or unreachable exception-handling helpers |
| asm         |    2 | `ASMGRAF` section: 16-bit leftovers from the Win16 version, unreachable |

About 221,000 lines of C.  Every function that can execute has C source.

## Builds

* `build/civ2_recon.exe` — the original executable with all 4445 reconstructed
  functions grafted in.  `--wipe` overwrites every original instruction with
  `int3`; the full suite still passes, so no original machine code runs.
* `build/civ2.exe` — standalone: written by `tools/build_standalone.py` from the
  compiled source plus `data/image/` (initialized data, import table,
  resources), without reading the original `civ2.exe`.

## Behavioural comparison (harness/suite.sh, seed 7)

The standalone executable, the wiped build and the grafted build are each
pixel-identical to the original at every screenshot and produce the
identical sequence of `rand()` calls (call site and value):

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
what the original's stack holds there, and the function's frame starts
with those values (they were applied by `tools/gen_c.py`'s FRAME_PRESETS;
now edited in src/auto directly).  What made it so: matching Wine's exact message semantics
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

* **Names and types.**  About 4,050 of about 4,450 game functions, 2,260 of
  about 2,480 globals, 268 of 355 classes and 870 class fields are named: 95% of
  calls and over 99% of global references in the generated code read by name.
  Each name has its evidence in re/function_names.tsv, re/global_names.tsv,
  re/type_names.tsv and re/field_names.tsv; re/notes.md collects the
  structures found.  Names live in re/symbols.tsv (functions: func,
  globals: var) and the maps above; tools/rename.py applies them to the
  sources (src/auto included).  Naming dossiers:
  tools/name_batches.py, name_globals_batches.py, name_types_dossier.py,
  name_fields_dossier.py; tools/apply_names.py takes proposals in.
  Still to do: the rarely-called remainder (mostly small helpers), the
  larger window subclasses whose fields overlap, and typing parameters
  and locals (still int/undefined4 in many functions).
* **Data is binary.**  `data/image/*.bin` are the original initialized data
  sections; converting them to C tables is mechanical but not done.
* `tools/build_recon.py` still reads the original `civ2.exe` for import-slot
  addresses when linking (the same information is in `data/image/idata.bin`).
* Coverage of the comparison: the scripts execute 2,295 of the 3,417
  compiled game functions (67%, 51% of lines; `tools/coverage_report.py`
  with the linux32cov build, per function in re/coverage.tsv).  Never
  executed: multiplayer (parley, net), sound and video, council, the
  editors' rarely used dialogs, atexit destructors.  Untested paths may still differ.  Add a script under `harness/scripts/`, record it with
  `make ref SCRIPT=...` and bisect differences with `make bisect`.
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
