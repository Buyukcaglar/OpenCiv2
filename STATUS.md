# Status

## Coverage (re/manifest.tsv)

| status      | functions | meaning |
|-------------|-----------|---------|
| auto        | 4040 | game functions translated by `tools/gen_c.py` (src/auto/blk_*.c) |
| game        |  114 | reconstructed by hand (src/game/*.c, src/crt/*.c) |
| ehfunclet   |  462 | C++ unwind funclets; inlined into their callers, never called on their own |
| crt         |  284 | statically linked MSVC 4.2 debug C runtime, translated (src/auto/crt_*.c) |
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

| build | how | menu | newgame | loadgame | turns | advisors | long50 |
|-------|-----|------|---------|----------|-------|----------|--------|
| `build/civ2-linux32` | gcc -m32 | ✓ | ✓ | ✓ | ✓ | ✓ | ✓ |
| `build/civ2-port` (64-bit, portable to macOS) | wasm32 → wasm2c → cc | ✓ | ✓ | ✓ | ✓ | ✓ | ✓ |

✓ = every screenshot pixel-identical and identical `rand()` trace (long50:
14 057 calls).  What made it so: matching Wine's exact message semantics
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

* **Names and types.**  Functions and globals are still named by address
  (`FUN_0041ba52`, `DAT_0064f348`) and struct layouts (units, cities,
  civilizations) are not applied; the hand-written files have descriptive
  comments.  The names known from the binary's log strings (`Citywin`,
  `Map_3`, `human_turn` …) and the SAV-file format are the starting point.
* **Data is binary.**  `data/image/*.bin` are the original initialized data
  sections; converting them to C tables is mechanical but not done.
* `tools/build_recon.py` still reads the original `civ2.exe` for import-slot
  addresses when linking (the same information is in `data/image/idata.bin`).
* Coverage of the comparison is what the six scenarios exercise; untested
  paths (multiplayer, scenarios, the editors, video playback) may still
  differ.  Add a script under `harness/scripts/`, record it with
  `make ref SCRIPT=...` and bisect differences with `make bisect`.
