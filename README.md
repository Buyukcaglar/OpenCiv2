# OpenCiv2 for Windows

OpenCiv2 runs **Civilization II Multiplayer Gold Edition** as a native 64-bit
Windows program, a single `OpenCiv2.exe` with nothing to install. This is a
fork of [OpenCiv2](https://github.com/richardpenman/civ2), Richard Penman's
reconstruction of the game's source code (upstream: `richardpenman/civ2`),
with a Windows launcher and Windows conveniences added on top.

**The game itself is not included.** You need your own copy of Civilization II
Multiplayer Gold Edition (its CD, a CD image, or an installed copy).

<p>
<img src="docs/screenshots/menu.png" width="49%"> <img src="docs/screenshots/city.png" width="49%">
<img src="docs/screenshots/europe-1940.png" width="49%"> <img src="docs/screenshots/top5.png" width="49%">
<img src="docs/screenshots/diplomacy.png" width="49%"> <img src="docs/screenshots/city-view.png" width="49%">
</p>

*The native build: the main menu, a city, the World War II scenario, the Top Five Cities, a foreign
leader receiving an envoy (his video, from the CD) and London's city view with its wonders.*

## Download

**[OpenCiv2-windows.zip](https://github.com/Buyukcaglar/OpenCiv2/releases/latest/download/OpenCiv2-windows.zip)**
(Windows 10 or 11, 64-bit), from the [latest release](https://github.com/Buyukcaglar/OpenCiv2/releases/latest).
Unpack it into any folder and double-click `OpenCiv2.exe`.

## Setting up

The first time, OpenCiv2 asks where your copy of the game is. Any of these works:

- a zip, 7z or rar archive of the game: its files, possibly in subfolders, or
  the CD image (`.cue`/`.bin` or `.iso`) inside it;
- the CD image itself (`.cue`/`.bin` or `.iso`);
- a folder with the game's files, such as an installed copy or a copy of the CD.

OpenCiv2 looks through all of it (including the InstallShield cabinet on the CD),
finds the files the game needs and checks each against its known size and
SHA-256. If a required file is missing or different, it lists which one, what it
expected and what it found, and copies nothing. Otherwise it copies only the
files the game needs (and the CD's music, from a `.cue`/`.bin` image or a
`Music` folder, when there is one) into a `GameData` folder beside the
executable, then starts the game. From then on it starts the game directly.

`OpenCiv2.exe` and its `GameData` folder can be moved or copied anywhere together,
such as to a USB stick. Apart from a temporary folder while setting up, nothing
is written outside them.

- `OpenCiv2.exe ARCHIVE|IMAGE|FOLDER` sets up from that location without asking
  (a folder that already is a game folder is played in place).
- `OpenCiv2.exe --setup` asks for a location again, for example to set up from
  another copy.
- What was found and copied is logged in `GameData\OpenCiv2-setup.txt`.

## Playing

| Keys and commands | |
|---|---|
| **Alt+Enter** | Switches between a window and full screen. In full screen the menu bar is hidden: move the mouse to the top edge of the screen, or press Alt, F10 or a menu's Alt+letter, to show it. |
| **Alt+F4**, the window's **X**, **Close** on the title bar's menu | Close the game. With no game in progress (intro, main menu) it closes at once; during a game it asks first, since whatever was not saved is lost. |
| **Game → Quit** (Ctrl+Q) | Before a game has started, also during the intro videos, closes at once; during a game, the game's own Quit dialog. |
| **Civilopedia → About OpenCiv2…** | Version, credits, links and license (also on the title bar's menu). |

The set-up window, message boxes, title bar and menus follow Windows' light or
dark mode (and high contrast); `CIV2_THEME=dark` or `light` overrides it.
Separators between menu groups are drawn as lines, and items the game disables
are shown grayed.

Music and videos come from the CD: set up from a CD image (or a folder with
the CD's `Music` tracks) to have them. Turn music on in Game → Game Options.

### Differences from the original

- The Game menu's labels are matched to their commands whether the game's
  `MENU.TXT` is the CD's (twelve items) or the 5.4.0f patch's (thirteen, with
  the profile item). Read in order, the patch's file put each label from Pick
  Music on next to the wrong command (Quit retired, Retire changed the timer).
- Empty rows the original used as spacing in menus are proper separators.
- The menus open on the title screen and the main menu too (the game's own
  items grayed until a game starts; Quit and About work).
- Text is measured as wide as it is drawn, so no dialog cuts its lines off.
  (Upstream keeps Wine's slightly narrower measures, to match its recordings
  of the original; `CIV2_WINE_TEXT=1` does that here.)
- OpenCiv2 can live in any folder, however deep: the game keeps its file paths
  in 128-byte buffers, so its own folder is shown to it as `C:\`.
- Building the world takes about a second (the reconstruction's sound layer
  had made it take a minute or more with sound on).

### Known limitations

- The set-up accepts the files of the Multiplayer Gold Edition CD as they are
  on the disc; copies whose files were changed (patched, modded) are reported
  as different and not copied. A folder that already is a complete game folder
  can still be played in place with `OpenCiv2.exe FOLDER`.
- Game → Pick Music asks for the CD, as in the upstream reconstruction.
- Dialogs the game draws itself keep the original's look.
- Multiplayer over a network is untested.

## Building OpenCiv2.exe

In an [MSYS2](https://www.msys2.org) **MINGW64** shell:

```sh
pacman -S git mingw-w64-x86_64-gcc mingw-w64-x86_64-SDL2 mingw-w64-x86_64-python mingw-w64-x86_64-python-pefile \
          mingw-w64-x86_64-cmake mingw-w64-x86_64-ninja
git clone https://github.com/Buyukcaglar/OpenCiv2 && cd OpenCiv2
tools/fetch-toolchain.sh windows   # wasi-sdk, wabt, SDL2 for MinGW into tools/toolchain (once)
python3 tools/build_deps.py        # libarchive, zlib, bzip2, xz, libunshield (static, once)
python3 tools/build_port.py module c exe-windows   # -> build/OpenCiv2.exe (several minutes)
```

`build/OpenCiv2.exe` is a single file (SDL2, the fonts and `CIV2.DAT` are built
in). The game's code is compiled to WebAssembly, translated to C with wasm2c and
compiled with MinGW together with the SDL2 host layer (`src/host/`).
`tools\run-civ2.bat [GAMEDIR]` plays an existing game folder in place
(`%USERPROFILE%\Civ2` by default).

It can also be cross-compiled on Linux with `x86_64-w64-mingw32-gcc`, cmake and
ninja, with the same three commands. `.github/workflows/windows.yml` does that
on every push to `main`, and publishes a release for every `v*` tag.

## The reconstruction (upstream)

The rest of this file comes from [richardpenman/civ2](https://github.com/richardpenman/civ2),
which this repository follows (its `upstream` remote). The reconstructed game
under `src/auto/`, `src/game/`, `src/data/`, `src/include/` and
`src/platform/`, the analysis in `re/`, the tools and the harness are its
work; this fork adds the Windows launcher and the changes above, mostly in
`src/host/`.

Goal: reconstruct the source of *Sid Meier's Civilization II: Multiplayer Gold Edition*
(1998) as portable C++ that builds and runs natively on Linux, macOS and Windows,
and prove it behaves exactly like the original binary: the same screens, pixel for pixel,
and the same random numbers, call for call, on recorded games.

### Layout

| Path | What |
| --- | --- |
| `src/auto/` | The game: decompiled once, now C++ edited directly, a file per subject (`city.cpp`, `unit.cpp`, `ai.cpp`, `diplomacy.cpp`, `map.cpp`, `window.cpp` …). |
| `src/game/` | Functions the decompiler could not translate, reconstructed by hand. |
| `src/data/` | The game's static data (`gamedata.h`/`.cpp`), laid out exactly as in the original. |
| `src/include/` | Types recovered from the binary: units, cities, civilizations, map, the game's classes. |
| `src/platform/` | The Windows API the game uses (windows, GDI, controls, files, sound, video) implemented in portable C. |
| `src/host/` | What the platform layer needs from the machine: window, input and audio over SDL2; the portable build's runtime. |
| `src/native/` | The C runtime pieces the native builds need. |
| `data/` | Fonts as the original renders them, and the original executable's data sections. |
| `re/` | Analysis results: function list, calling conventions, data layout, Ghidra's decompilation. |
| `harness/` | The replay scripts and the comparison with the original (`run.py`, `compare.py`, `native_suite.sh`). |
| `hook/` | An `XDaemon.dll` proxy that makes the original deterministic under Wine. |
| `tools/` | Build, analysis and refactoring scripts. |
| `docs/`, `STATUS.md` | Notes on the reconstruction and its verification. |

### Approach

1. **Inventory**: Ghidra decompiles all ~4,900 functions; names and types for every function,
   global, class and field were recovered from their use.
2. **Translation**: the decompiled code was turned into C that compiles natively, then edited
   by hand: names, types, struct access, real locals, data as ordinary variables. It is now C++
   (`docs/hand-reconstruction.md`).
3. **Platform**: the game keeps calling the Windows API; `src/platform` implements the part it
   uses on top of SDL2, so the same game code runs everywhere.
4. **Determinism**: under Wine, the `hook/` proxy DLL pins the original's random seed, gives it a
   virtual clock and replays recorded input. The native builds do the same, so a recorded
   scenario plays identically in both.
5. **Differential harness**: each scenario in `harness/scripts` (new game, turns, cities,
   diplomacy, editors, 50 turns of play …) is recorded from the original once; the native builds
   replay it and must produce the same screenshots and the same sequence of `rand()` calls.
   Changes to the code are also checked function by function against the previous version's
   machine code (`tools/cxx_compare.py`), which covers the code no scenario reaches.

### Build and run

The game files are not included: install your copy of Civilization II in `~/Civ2` (the
directory with `civ2.exe`, `Tiles.dll`, the `.TXT` files …), or point `CIV2_GAME` at it.

#### macOS

```sh
xcode-select --install          # C/C++ compiler
brew install sdl2
pip3 install pefile

git clone https://github.com/richardpenman/civ2 && cd civ2
tools/fetch-toolchain.sh        # wasi-sdk + wabt into tools/toolchain (once)
python3 tools/build_port.py     # -> build/OpenCiv2  (several minutes)
tools/run-civ2.sh               # plays the game in ~/Civ2
```

#### Linux

As on macOS, with `libsdl2-dev` and `python3-pefile` from the package manager:

```sh
git clone https://github.com/richardpenman/civ2 && cd civ2
tools/fetch-toolchain.sh
python3 tools/build_port.py     # -> build/OpenCiv2
tools/run-civ2.sh
```

#### Windows

**Download:** [OpenCiv2-windows.zip](https://github.com/richardpenman/civ2/releases/download/latest/OpenCiv2-windows.zip),
upstream's build of its latest commit. Unpack it into your Civilization II folder (the one with
`civ2.exe`) and double-click `OpenCiv2.exe`.

To build it yourself, see [Building OpenCiv2.exe](#building-openciv2exe) above.

### Tooling

Development runs in Docker on Linux; `tools/dk CMD` runs a command in the dev container with
the repository at `/work` and the game at `/civ2`.

| Tool | Notes |
| --- | --- |
| Docker images (`make images`) | Wine (runs the original), MinGW, g++/gcc with 32-bit support, SDL2, Python; Ghidra for the analysis. |
| wasi-sdk + wabt (`tools/fetch-toolchain.sh`) | The portable build: the game compiles to a wasm32 module (keeping the original's 32-bit data model), which wasm2c turns into C for any machine. |
| `hook/` (`make hook`) | The proxy DLL that makes the original replayable. |

```sh
make native          # build/civ2-linux32: gcc -m32, the same code, easier to debug
make port            # build/OpenCiv2: the portable build
make ref SCRIPT=harness/scripts/turns.txt    # record the original on a scenario
make native-suite    # replay every scenario on a native build and compare (EXE=OpenCiv2, OpenCiv2.exe under Wine)
```

### Status

Playable. Every function of the game that can run has source; the only parts not reconstructed
are the original's MSVC runtime (replaced by the platform's C library) and unreachable 16-bit
leftovers. 25 of the 29 recorded scenarios match the original exactly; the other four differ in
a few pixels of an editor dialog, a Civilopedia page and the power graph. The scenarios run about
two thirds of the game's functions; multiplayer, the High Council and some editor dialogs are not
covered yet.

The code is being modernized step by step, each step checked by the harness: it compiles as
strict C++ and keeps the original's data layout; recovering the remaining types, classes,
structured control flow and smaller functions is in progress. Details in `STATUS.md`.

## Credits

- **Richard Penman**: the reconstruction of Civilization II's source code
  this program is built from, [github.com/richardpenman/civ2](https://github.com/richardpenman/civ2) (MIT).
- **Onur BUYUKCAGLAR**: this fork, OpenCiv2's Windows port and launcher, with
  the assistance of Anthropic's Claude.
- **alexielios**: the program's icon, ["Icon Civilization II"](https://www.deviantart.com/alexielios/art/Icon-Civilization-II-558913212)
  on DeviantArt (see `src/host/res/ICON-CREDITS.md`; not covered by this
  repository's license).
- Statically linked libraries: [SDL2](https://www.libsdl.org) (zlib license),
  [libarchive](https://www.libarchive.org) (BSD), [libunshield](https://github.com/twogood/unshield) (MIT),
  [zlib](https://zlib.net), [bzip2](https://sourceware.org/bzip2/) and [xz/liblzma](https://tukaani.org/xz/).
- Civilization II is a trademark of its owners; OpenCiv2 is not affiliated
  with or endorsed by them. The game's files are not part of this repository or its
  releases.

## License

MIT (see `LICENSE`). Civilization II itself and its game files are not part of
this repository and are not covered by this license, nor is the icon.
