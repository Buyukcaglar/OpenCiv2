# Hand-reconstructing a function

Most of the game was machine-translated (`src/auto/`, generated once by
`tools/gen_c.py` from Ghidra's output) and is now edited directly: the
generator no longer runs.  Functions it could not translate were written by
hand in `src/game/*.c`; `src/auto` keeps a one-line pointer where each was
(`/* 005e22ed: written by hand in src/game/fixups.c */`).  A function can be
moved between the two freely.

## Rules

* **Exact behaviour.**  The native builds are compared against recordings of
  the original game (`harness/native_suite.sh`) screen by screen and `rand()`
  call by `rand()` call.  Follow the original machine code
  (`tools/show.py ADDR -d`), not Ghidra, wherever they disagree: the
  decompiler output is wrong precisely where the artifacts are.
* **Same name, same signature.**  Define the function under its name with the
  parameter list declared in `src/auto/protos.h` (types must match or the
  compiler reports "conflicting types").
* **Calls** go to other functions by name; Win32 APIs are called normally
  (`src/platform` implements them).
* **Globals** are ordinary variables (`src/data/gamedata.h`).  Data the code
  reaches as one piece -- an object and the fields the code also names as
  globals, a table split into columns -- is a packed struct
  (`pedia_window_block.pedia_wonder_entry_count`).
* **Locals** are ordinary locals.  Where the original relies on two of them
  being next to each other (a struct built field by field, a buffer written
  past its first element), declare them as one struct or array.  The
  AddressSanitizer build finds such places:
  `tools/build_native.py --target linux32asan`, then run the replays with it.
* **Register arguments** (`in_EAX`, `in_ECX`, `in_AL`) are usually leftover
  register contents, not arguments: see src/game/regargs.c.
* **Unwind funclets / EBP-relative code** (`unaff_EBP`): MSVC emits small
  `call $L` blocks that run with the *caller's* EBP to destroy locals;
  translate them as plain destructor calls on the caller's locals.
* **Exception frames** (`fs:[0]` bookkeeping, `unaff_FS_OFFSET`) are dropped:
  the game never throws.

## Tools (run inside the container via `tools/dk`)

* `python3 tools/show.py ADDR` — the function's C source
* `python3 tools/show.py ADDR -g` — Ghidra's raw output
* `python3 tools/show.py ADDR -d` — original disassembly
