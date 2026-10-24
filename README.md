# Civ2RE: Civilization II for 64-bit Windows

Civ2RE runs **Civilization II Multiplayer Gold Edition** as a native 64-bit
Windows program, a single `Civ2RE.exe` with nothing to install. It is built
from [Richard Penman's reconstruction of the game's source code](https://github.com/richardpenman/civ2)
(upstream: `richardpenman/civ2`), with a Windows launcher and Windows
conveniences added on top.

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

**[Civ2RE-windows.zip](https://github.com/Buyukcaglar/Civ2RE/releases/latest/download/Civ2RE-windows.zip)**
(Windows 10 or 11, 64-bit), from the [latest release](https://github.com/Buyukcaglar/Civ2RE/releases/latest).
Unpack it into any folder and double-click `Civ2RE.exe`.

## Setting up

The first time, Civ2RE asks where your copy of the game is. Any of these works:

- a zip, 7z or rar archive of the game: its files, possibly in subfolders, or
  the CD image (`.cue`/`.bin` or `.iso`) inside it;
- the CD image itself (`.cue`/`.bin` or `.iso`);
- a folder with the game's files, such as an installed copy or a copy of the CD.

Civ2RE looks through all of it (including the InstallShield cabinet on the CD),
finds the files the game needs and checks each against its known size and
SHA-256. If a required file is missing or different, it lists which one, what it
expected and what it found, and copies nothing. Otherwise it copies only the
files the game needs (and the CD's music, from a `.cue`/`.bin` image or a
`Music` folder, when there is one) into a `GameData` folder beside the
executable, then starts the game. From then on it starts the game directly.

`Civ2RE.exe` and its `GameData` folder can be moved or copied anywhere together,
such as to a USB stick. Apart from a temporary folder while setting up, nothing
is written outside them.

- `Civ2RE.exe ARCHIVE|IMAGE|FOLDER` sets up from that location without asking
  (a folder that already is a game folder is played in place).
- `Civ2RE.exe --setup` asks for a location again, for example to set up from
  another copy.
- What was found and copied is logged in `GameData\Civ2RE-setup.txt`.

## Playing

| Keys and commands | |
|---|---|
| **Alt+Enter** | Switches between a window and full screen. In full screen the menu bar is hidden: move the mouse to the top edge of the screen, or press Alt, F10 or a menu's Alt+letter, to show it. |
| **Alt+F4**, the window's **X**, **Close** on the title bar's menu | Close the game. With no game in progress (intro, main menu) it closes at once; during a game it asks first, since whatever was not saved is lost. |
| **Game → Quit** (Ctrl+Q) | Before a game has started, also during the intro videos, closes at once; during a game, the game's own Quit dialog. |
| **Civilopedia → About Civ2RE…** | Version, credits, links and license (also on the title bar's menu). |

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
- Civ2RE can live in any folder, however deep: the game keeps its file paths
  in 128-byte buffers, so its own folder is shown to it as `C:\`.
- Building the world takes about a second (the reconstruction's sound layer
  had made it take a minute or more with sound on).

### Known limitations

- The set-up accepts the files of the Multiplayer Gold Edition CD as they are
  on the disc; copies whose files were changed (patched, modded) are reported
  as different and not copied. A folder that already is a complete game folder
  can still be played in place with `Civ2RE.exe FOLDER`.
- Game → Pick Music asks for the CD, as in the upstream reconstruction.
- Dialogs the game draws itself keep the original's look.
- Multiplayer over a network is untested.

## Building Civ2RE.exe

In an [MSYS2](https://www.msys2.org) **MINGW64** shell:

```sh
pacman -S git mingw-w64-x86_64-gcc mingw-w64-x86_64-SDL2 mingw-w64-x86_64-python mingw-w64-x86_64-python-pefile \
          mingw-w64-x86_64-cmake mingw-w64-x86_64-ninja
git clone https://github.com/Buyukcaglar/Civ2RE && cd Civ2RE
tools/fetch-toolchain.sh windows   # wasi-sdk, wabt, SDL2 for MinGW into tools/toolchain (once)
python3 tools/build_deps.py        # libarchive, zlib, bzip2, xz, libunshield (static, once)
python3 tools/build_port.py module c exe-windows   # -> build/Civ2RE.exe (several minutes)
```

`build/Civ2RE.exe` is a single file (SDL2, the fonts and `CIV2.DAT` are built
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
under `src/auto/`, `src/game/`, `src/data/`, `src/include/` and `src/platform/`,
the analysis in `re/`, the tools and the harness are its work; Civ2RE adds the
Windows launcher and the changes above, mostly in `src/host/`.

### Files

| path | what |
|------|------|
| `src/auto/` | the game, machine-translated to C once, now C++ edited directly, a file per subject: `city.cpp`, `unit.cpp`, `ai.cpp`, `civ.cpp`, `diplomacy.cpp`, `reports.cpp`, `map.cpp`, `mapview.cpp`, `game.cpp`, `editor.cpp`, `pedia.cpp`, `spaceship.cpp`, `network.cpp`, `sound.cpp`, `window.cpp`, `controls.cpp`, `graphics.cpp`, `text.cpp`, `support.cpp` |
| `src/game/` | game functions reconstructed by hand |
| `src/data/` | the game's static data (`gamedata.h`/`.cpp`) |
| `src/include/` | types recovered from the binary (units, cities, civilizations, classes) |
| `src/platform/` | the Windows API the game uses (windows, GDI, controls, files, sound …) implemented in portable C |
| `src/host/` | what the platform needs from the machine: window, input, audio over SDL2; the portable build's runtime |
| `src/native/` | the C runtime pieces for native builds (C++, as the game) |
| `data/native/` | fonts as the reference renders them (glyph data, generated with Wine) |
| `data/image/` | the original executable's data sections |
| `re/` | analysis results: function list, calling conventions, data layout, Ghidra's decompilation |
| `tools/` | build, naming and clean-up scripts (`build_port.py`, `build_native.py`, `rename.py` …); the retired Ghidra pipeline (`gen_c.py`) |
| `harness/` | replay scripts and the comparison against the original (`run.py`, `compare.py`, `native_suite.sh`, `msgdiff.sh`, `clockdiff.py`) |
| `hook/` | `XDaemon.dll` proxy that makes the original deterministic under Wine (seed, virtual clock, input replay) |
| `docs/`, `STATUS.md` | notes on the reconstruction and its verification |

### Building on macOS and Linux

#### macOS

```sh
xcode-select --install          # C compiler
brew install sdl2
pip3 install pefile

git clone https://github.com/richardpenman/civ2 && cd civ2
tools/fetch-toolchain.sh        # wasi-sdk + wabt into tools/toolchain (once)
python3 tools/build_port.py     # -> build/civ2-port  (several minutes)
tools/run-civ2.sh               # plays the game in ~/Civ2
```

#### Linux

Same as macOS with `libsdl2-dev` and `python3-pefile` from the package manager.

### Music and videos from the CD (macOS and Linux)

The game plays its music from the CD's audio tracks and its heralds and movies
from the CD's video files.  With a disc image (`.cue` and `.bin`, or a zip of
them), copy them into the game directory once:

```sh
python3 tools/extract_disc.py DISC.zip ~/Civ2
```

This writes `KINGS/` (the diplomatic heralds), `Video/` (opening, wonders, High
Council) and `Music/Track02.wav` … (the CD's audio tracks, played by the
reconstruction's CD drive).  Turn music on in Game → Game Options.

### Development (Docker)

Everything else runs in Docker on Linux; `tools/dk CMD` runs a command in the
dev container with the repository at `/work` and the game at `/civ2`.

```sh
make images          # Docker images: wine, mingw, SDL2, wasi-sdk; Ghidra
make hook            # the replay/trace proxy DLL for the original
make port            # build/civ2-port (portable build)
make native          # build/civ2-linux32 (gcc -m32: same code, easier to debug)
make native-suite    # compare a native build against those recordings (EXE=civ2-port, civ2-port.exe under wine)
```

`harness/scripts/*.txt` are the scenarios (menu, new game, load game, turns,
advisors, 50 turns of play).  `make ref SCRIPT=...` records the original on a
script, `make native-suite` checks the native builds against the recordings.

## Credits

- **Richard Penman**: the reconstruction of Civilization II's source code
  this program is built from, [github.com/richardpenman/civ2](https://github.com/richardpenman/civ2) (MIT).
- **Onur BUYUKCAGLAR**: Civ2RE, the Windows port and launcher, with the
  assistance of Anthropic's Claude.
- **alexielios**: the program's icon, ["Icon Civilization II"](https://www.deviantart.com/alexielios/art/Icon-Civilization-II-558913212)
  on DeviantArt (see `src/host/res/ICON-CREDITS.md`; not covered by this
  repository's license).
- Statically linked libraries: [SDL2](https://www.libsdl.org) (zlib license),
  [libarchive](https://www.libarchive.org) (BSD), [libunshield](https://github.com/twogood/unshield) (MIT),
  [zlib](https://zlib.net), [bzip2](https://sourceware.org/bzip2/) and [xz/liblzma](https://tukaani.org/xz/).
- Civilization II is a trademark of its owners; Civ2RE is not affiliated with
  or endorsed by them. The game's files are not part of this repository or its
  releases.

## License

MIT (see `LICENSE`). Civilization II itself and its game files are not part of
this repository and are not covered by this license, nor is the icon.
