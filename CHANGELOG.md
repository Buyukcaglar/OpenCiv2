# Changelog

Civ2RE's releases. The reconstruction itself changes upstream, in
[richardpenman/civ2](https://github.com/richardpenman/civ2); each release
names the upstream commit it is built on.

## v1.0

The first release, on upstream commit `2cbc514` ("The game is C++: strict,
every function checked against the C conversions").

- **Civ2RE.exe**: one 64-bit Windows executable with SDL2, the fonts and
  `CIV2.DAT` built in; nothing to install.
- **Set-up from your own copy**: a zip, 7z or rar archive, a `.cue`/`.bin` or
  `.iso` CD image, or a folder. Each of the game's files is checked against its
  size and SHA-256, mismatches are listed, and only the needed files (and the
  CD's music) are copied into a portable `GameData` folder beside the program.
- **Full screen** with Alt+Enter; the menu bar appears when the mouse reaches
  the top of the screen, or with Alt, F10 and the menus' Alt+letter keys.
- **Closing**: Alt+F4, the window's X and the title bar menu's Close work.
  With no game in progress they close at once, during a game they ask first.
- **Game → Quit** (Ctrl+Q) closes at once when no game is in progress, also
  during the intro videos, instead of opening the retire dialogs.
- **Menus**: separators instead of blank rows, no extra spaces in items, grayed
  disabled items; the Game menu's labels match their commands with the CD's and
  the 5.4.0f patch's `MENU.TXT` alike.
- **Building the world** takes about a second instead of a minute or more:
  the sound layer looked through all 8192 handle slots on every one of the
  generator's ~26,000 message checks; it now keeps a list of the open devices.
- **Any folder**: a game folder deep in the file system is shown to the game
  as `C:\`, since the game keeps its paths in 128-byte buffers (sound effects
  overran them, the intro and other videos did not play).
- **About Civ2RE** (Civilopedia menu and title bar menu): version, credits,
  links and license.
- Light and dark mode (and high contrast) for the set-up window, message boxes,
  title bar and menus.
- Icon: "Icon Civilization II" by alexielios
  (https://www.deviantart.com/alexielios/art/Icon-Civilization-II-558913212).
