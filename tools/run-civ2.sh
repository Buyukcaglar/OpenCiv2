#!/bin/sh
# Play the portable build: tools/run-civ2.sh [GAMEDIR]
# GAMEDIR: the installed game (default $CIV2_GAME, or ~/Civ2); the game
# saves there.  The game fills the screen; CIV2_FULLSCREEN=1: the whole display;
# CIV2_WINDOW=1: a 1024x768 window (CIV2_SCALE=2: twice the size).
here=$(cd "$(dirname "$0")/.." && pwd)
game=${1:-${CIV2_GAME:-$HOME/Civ2}}
[ -d "$game" ] || { echo "no game in $game: install Civilization II there or name its directory" >&2; exit 1; }
[ -f "$game/CIV2.DAT" ] || cp "$here/harness/CIV2.DAT" "$game/"
CIV2_DATA="$here/data/native" exec "$here/build/civ2-port" "$(cd "$game" && pwd)"
