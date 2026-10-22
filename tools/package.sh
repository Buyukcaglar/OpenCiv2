#!/bin/sh
# Package the reconstructed game for playing elsewhere (e.g. macOS under Wine):
# the game's data files from $CIV2_GAME (default ~/Civ2), the standalone build/civ2.exe in place of
# the original executable, and the compatibility DLL (hook/XDaemon.dll, which
# forwards to the real XDaemon_real.dll and fixes the wine text-box crash).
set -e
cd "$(dirname "$0")/.."
rm -rf dist/civ2 && mkdir -p dist/civ2
cp -r "${CIV2_GAME:-$HOME/Civ2}"/. dist/civ2/
cp build/civ2.exe dist/civ2/civ2.exe
mv dist/civ2/XDaemon.dll dist/civ2/XDaemon_real.dll
cp hook/XDaemon.dll dist/civ2/XDaemon.dll
cp harness/CIV2.DAT dist/civ2/CIV2.DAT
(cd dist && rm -f civ2-reconstructed.zip && python3 -c "import shutil; shutil.make_archive('civ2-reconstructed', 'zip', '.', 'civ2')")
ls -la dist/civ2-reconstructed.zip
