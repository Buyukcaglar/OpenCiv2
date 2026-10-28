# Interface additions

OpenCiv2 adds to the original game's interface the features of
[CIV2UIA](https://github.com/FoxAhead/Civ2-UI-Additions), the "Civilization II User Interface
Additions" launcher by FoxAhead, which patches the original executable. They are written anew
for OpenCiv2's code from CIV2UIA's description of them; no code of CIV2UIA's is used. Each keeps
the number of its item in CIV2UIA's README (`X<n>` below and in the code). Thanks to FoxAhead
and the CIV2UIA contributors for the ideas and for documenting them.

This file covers the additions to the interface (CIV2UIA's batch of items that change only
what the player sees and does). CIV2UIA's rule changes (items 17, 18, 19, 36, 42 and the
limits) are not part of it. Items 4, 9, 20, 21, 40 and 44 are bug fixes: they are in
[BUGS.md](BUGS.md) (B10, B2, B9, B12, B1, B3). Items 7, 8, 12, 13 and 14 fix problems of the
original executable on modern Windows that OpenCiv2 does not have.

## On and off

The additions are on by default. They are off:

- with `CIV2_CLASSIC=1` (the original game: its look, its bugs, and none of these);
- in replays and unit tests, which are compared with the original game
  (`CIV2_TEST_EXTRAS` turns them on in a replay, for tests: `1` for all, a list of item
  numbers such as `5,6,43`, or all but some, `-43`).

They change only what this player sees and how the interface is used, never what the game
computes, so they stay on in network games (a production changed from the City Status
advisor, or specialists changed with the wheel, are the same orders as through the city
window).

Each one can be switched off in the `[OpenCiv2]` section of `CIV.INI` (the file the game
keeps its own settings in, in its Windows directory): its key `=0`.

| Item | Key | What |
| --- | --- | --- |
| 1 | `MouseWheel` | The mouse wheel scrolls the list or scroll bar under the pointer (advisors, dialogs, the city window's improvements and supported units, the Civilopedia), changes a specialist under the pointer in the city window, turns the tax rates' bars; Ctrl+wheel zooms the map, Ctrl+middle button sets the normal zoom; a middle click centres the map there, a middle drag pans it. |
| 2 | `UnitListScroll` | The Activate Unit list of a stack of more than 9 units shows all of them, in a list that scrolls. |
| 28 | `UnitListKeys` | (with 2) that list's keys (arrows, Page Up/Down) and wheel. |
| 3 | `WorkCounter` | A settler's or engineer's work counter on its picture on the map (own units). |
| 5 | `GameTurn` | The game turn in the status panel, after the year. |
| 6 | `ResearchNumbers` | The Science Advisor: the bulbs so far, the advance's cost and the bulbs per turn. |
| 10 | `ZeroUpkeep` | The Trade Advisor lists the buildings that cost no upkeep too. |
| 11 | `SupportScroll` | The city window's supported units: their total, and a scroll bar when they do not fit. |
| 16 | `SupportSort` | That list sorted: settlers, then the units that can attack (land, air, sea; stronger defence, then attack, first), then the rest. |
| 22 | `AttitudeColors` | The Attitude Advisor: celebrating cities in yellow, the food surplus or shortage icon after the name. |
| 23 | `CityAttitude` | The city window: the texts under the citizens coloured as in the Attitude Advisor (yellow celebrating, red in disorder). |
| 24 | `RadioHotkeys` | Each radio button of a dialog gets a hotkey (the first letter of its label no other has, underlined). |
| 25 | `Quickinfo` | Ctrl held with the pointer over the map: the city's and the units' details on that square. |
| 29 | `ProductionCancel` | A Cancel button in the city's Change Production list (Escape). |
| 30 | `ProductionCost` | The shields each item costs, and the upkeep of buildings, in that list. |
| 31 | `CityStatus` | The City Status advisor: the number of cities, headings that sort the list (size, name, food, shields, trade, production; again: the game's order), the production's picture; a click on a city's production opens its Change Production. |
| 32 | `MassSpecialists` | In the city window, Shift+wheel over a specialist changes all of them, Shift+click on one makes all the others the same. |
| 33 | `SuppressPopups` | Simple popups of GAME.TXT (text and an OK button only) whose sections are listed in `SuppressList=` (`[OpenCiv2]`, names separated by commas: `SuppressList=HIDDENTERRAIN,CITYSIZE`) are shown over the top of the map for a few seconds instead. Empty by default. |
| 35 | `ColorCorrection` | Colour correction of the whole screen: `Gamma=` (percent, 100 none), `Brightness=` and `Contrast=` (-100 to 100, 0 none). |
| 37 | `ForeignGold` | Gold coins in the Foreign Minister's list. |
| 38 | `ArrangeWindowsSL` | View > Arrange Windows S and L: a smaller or larger side panel than Arrange Windows. |
| 39 | `PathLines` | Shift held with the pointer over the map: the way the active unit would go there over the map as the player knows it (Dijkstra's over the known terrain, roads and railroads; hidden units and cities not counted); over the city under the cursor (View Pieces): lines to its trade routes' cities. |
| 41 | `SentryHalftone` | Units on sentry (and aircraft at a base) drawn in grey halftones instead of a grey shape. |
| 43 | `DefaultZoom1` | The map of a new game (or of a save without its layout) at zoom 1:1, whatever the screen width. |

Not done yet: 26 (advisors and lists resizable in height) and 27 (a larger caption area to
move the advisors by); for 39, the road a city needs for a permanent trade bonus (CIV2UIA draws
it); 34 (corrected leader portraits and throne room picture, which needs the player's corrected
`mk.dll` and `pv.dll`).

The texts the additions add ("Turn", the City Status headings ...) are in English; a
translation (`lang/<code>.txt`) can give them as `openciv2.<key>` (`openciv2.turn`,
`openciv2.cities`, `openciv2.size`, `openciv2.name`, `openciv2.production`).

## In the code

`src/include/extras.h`: the items, `extra_ui(X_...)` (`plat_extras`, set in
`src/platform/main.c` as `plat_fix_bugs`, and the item's bit from the settings);
`src/game/extras.cpp`: the settings and most of the additions. In the game's functions each one
reads `if (extra_ui(X_...)) <added> else <original>`, marked `X<n>`; with the additions off the
original's code runs unchanged. The platform delivers the mouse wheel (`WM_MOUSEWHEEL`, from
SDL's wheel events) and gives the additions the mouse and Shift/Ctrl messages before the game's
windows (`extras_input`, from `DispatchMessageA`).

Tests: `harness/extras/*.txt` are replay scripts of the additions (run with
`CIV2_TEST_EXTRAS`, see each script's comment). There is no reference for them (the original
game has none of this), so they are not in the suite: their screenshots were checked by eye.
`CIV2_TEST_FULL=WxH` (tests only) shows the game's window maximized on a desktop of that size,
all of it, so that advisors larger than the reference desktop's 640x480 window can be seen
whole; `CIV2_TEST_SETTINGS` (`Gamma=140,Contrast=20`) and `CIV2_TEST_SUPPRESS`
(`HIDDENTERRAIN`) stand for the settings in a replay. The replay scripts have `wheel X Y N`
and a button number for `click`, `mousedown`, `mousemove` and `mouseup` (2: middle).
