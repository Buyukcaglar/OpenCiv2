# Recovering data structures

Goal: give every global data structure of the game a C type and a name, so
the generated code reads `cities[i].owner` instead of address arithmetic,
and so the code can later be compiled as a portable 64-bit program.

* Types live in `src/include/civ2types.h`; names/types of globals in
  `re/symbols.tsv` (`addr kind name type`, kind = data|func).  Read both to
  see the conventions (Unit, City, UnitType are done).
* `tools/dk python3 tools/fields.py BASE STRIDE COUNT` (hex, hex, decimal)
  lists the offsets and access sizes the machine code uses inside an array of
  structs.  `re/decomp.c` is the full decompiler output (grep it; it is large,
  never read it whole).  `python3 tools/show.py ADDR` / `-g` / `-d`
  (disassembly needs `tools/dk`) show one function.  `re/gaccess.tsv` lists,
  per function, every absolute address accessed and its size.
* Rules:
  - Layout must be exactly the original's (32-bit).  Records written to save
    files byte-for-byte go inside the `#pragma pack(push, 1)` block and use
    only fixed-width fields (i8/u8/i16/u16/i32/u32, char arrays).  Records
    that are never saved raw may contain real pointers (`char *name`).
  - Name fields after what they mean, based on evidence (how the code uses
    them, RULES.TXT / save-file format knowledge, strings).  If unsure, use
    `field_XX` (hex offset).  Never guess a confident-sounding wrong name.
  - Signedness: follow how the code compares the field (`(char)x < 0` or
    `== -1` means signed).
  - Comment each field with its hex offset.
* Do NOT edit civ2types.h or symbols.tsv, and do NOT run Ghidra, gen_c,
  build_recon or the harness (one CPU, little memory).  Write your proposal
  to `re/proposals/NAME.h` (struct definitions, ready to paste) and
  `re/proposals/NAME.tsv` (symbols.tsv lines), plus a short evidence note
  at the top of the .h as a comment.  Verify the layout compiles with
  static size/offset checks: write a small C file in `run/` that includes
  `src/include/civ2types.h` and your proposal and checks
  `sizeof`/`offsetof`, and compile it with
  `tools/dk i686-w64-mingw32-gcc -fsyntax-only -I src/include FILE`.
