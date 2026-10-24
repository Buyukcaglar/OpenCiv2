# Civilization II (Multiplayer Gold Edition) — reconstructed source

The game itself is not included.  Install your copy of Civilization II in
`~/Civ2` (the directory with `civ2.exe`, `Tiles.dll`, the `.TXT` files …), or
point `CIV2_GAME` at it.

<p>
<img src="docs/screenshots/menu.png" width="49%"> <img src="docs/screenshots/city.png" width="49%">
<img src="docs/screenshots/europe-1940.png" width="49%"> <img src="docs/screenshots/top5.png" width="49%">
<img src="docs/screenshots/diplomacy.png" width="49%"> <img src="docs/screenshots/city-view.png" width="49%">
</p>

*The native build: the main menu, a city, the World War II scenario, the Top Five Cities, a foreign
leader receiving an envoy (his video, from the CD) and London's city view with its wonders.*

## Files

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

## Build and run

### macOS

```sh
xcode-select --install          # C compiler
brew install sdl2
pip3 install pefile

git clone https://github.com/richardpenman/civ2 && cd civ2
tools/fetch-toolchain.sh        # wasi-sdk + wabt into tools/toolchain (once)
python3 tools/build_port.py     # -> build/civ2-port  (several minutes)
tools/run-civ2.sh               # plays the game in ~/Civ2
```

### Linux

Same as macOS with `libsdl2-dev` and `python3-pefile` from the package manager.

### Windows

**Download:** [civ2-reconstructed-windows.zip](https://github.com/richardpenman/civ2/releases/download/latest/civ2-reconstructed-windows.zip),
built from the latest commit. Unpack it into your Civilization II folder (the
one with `civ2.exe`) and double-click `civ2-reconstructed.exe`.

To build it yourself, in an [MSYS2](https://www.msys2.org) **MINGW64** shell:

```sh
pacman -S git mingw-w64-x86_64-gcc mingw-w64-x86_64-SDL2 mingw-w64-x86_64-python mingw-w64-x86_64-python-pefile
git clone https://github.com/richardpenman/civ2 && cd civ2
tools/fetch-toolchain.sh
python3 tools/build_port.py     # -> build/civ2-port.exe and SDL2.dll
```

Then play from a normal Command Prompt (or double-click):
`tools\run-civ2.bat [GAMEDIR]` — the game in `%USERPROFILE%\Civ2` by default.

The Windows executable can also be cross-compiled on Linux:
`tools/fetch-toolchain.sh windows` (adds SDL2's MinGW release), then
`python3 tools/build_port.py module c exe-windows`; copy `build/civ2-port.exe`,
`build/SDL2.dll`, `data/native`, `harness/CIV2.DAT` and `tools/run-civ2.bat`
(keeping the directories) to the Windows machine.

### Music and videos from the CD

The game plays its music from the CD's audio tracks and its heralds and movies
from the CD's video files.  With a disc image (`.cue` and `.bin`, or a zip of
them), copy them into the game directory once:

```sh
python3 tools/extract_disc.py DISC.zip ~/Civ2
```

This writes `KINGS/` (the diplomatic heralds), `Video/` (opening, wonders, High
Council) and `Music/Track02.wav` … (the CD's audio tracks, played by the
reconstruction's CD drive).  Turn music on in Game → Game Options.

## Development (Docker)

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

## License

MIT (see `LICENSE`). Civilization II itself and its game files are not part of
this repository and are not covered by this license.
