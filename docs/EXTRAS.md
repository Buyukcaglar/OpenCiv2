# Interface additions

OpenCiv2 adds to the original game's interface the features of
[CIV2UIA](https://github.com/FoxAhead/Civ2-UI-Additions), the "Civilization II User Interface
Additions" launcher by FoxAhead, which patches the original executable. They are written anew
for OpenCiv2's code from CIV2UIA's description of them; no code of CIV2UIA's is used. Each keeps
the number of its item in CIV2UIA's README (`X<n>` below and in the code). Thanks to FoxAhead
and the CIV2UIA contributors for the ideas and for documenting them.

This file covers the additions to the interface (CIV2UIA's items that change only what the
player sees and does, on by default) and, under [Rule changes](#rule-changes), CIV2UIA's
items that change the game's rules (17, 18, 19, 36, 42 and the limits it takes from
[civ2patch](https://github.com/vinceho/civ2patch)), off by default. Items 4, 9, 20, 21, 40 and 44 are bug fixes: they are in
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
move the advisors by): each advisor lays out its own rows, scroll bar and buttons for its
fixed height, in its own drawing function (about a dozen of them), so there is no common
layout to make resizable, and a caption area larger than the original's needs that new
layout too; for 39, the road a city needs for a permanent trade bonus (CIV2UIA draws
it); 34 (corrected leader portraits and throne room picture, which needs the player's corrected
`mk.dll` and `pv.dll`).

The texts the additions add ("Turn", the City Status headings ...) are in English; a
translation (`lang/<code>.txt`) can give them as `openciv2.<key>` (`openciv2.turn`,
`openciv2.cities`, `openciv2.size`, `openciv2.name`, `openciv2.production`).

## Rule changes

CIV2UIA's items that change the game's rules, and the limits it took from civ2patch, are off
by default: each is switched on in the same `[OpenCiv2]` section of `CIV.INI`, the item by
its key `=1`, a limit by its value (`=0` or no key: the original's). They are off with
`CIV2_CLASSIC=1`, in replays and unit tests, and in network games (as the state fixes of
[BUGS.md](BUGS.md): every player, the original game included, must compute the same game);
they stay on in hot-seat and play-by-email games. The changes for units apply to the human
players' units only: the computer players play by the original rules.

| Item | Key | What |
| --- | --- | --- |
| 17 | `WorkerHandover` | A settler or engineer given the terrain order of one already working on its square takes its work (as the original) and the other one stops (no orders), so that it can go elsewhere at once: one worker with the order on a square. |
| 18 | `GotoNoZocStop` | A unit on Go To does not stop when it comes next to a foreign unit (the original: only caravans and freight go on). Zones of control still apply: it stops when they block its way or its moves run out; a unit sent at an enemy attacks what is in its way. |
| 19 | `UnitRotation` | Activating a unit (from the map or the stack's list) clears the Wait of the units of its stack and sets it on all the civilization's other units: the stack's units come next. And the next unit is looked for near the square where the last unit was activated (by the player or as the next one), not where it has moved to. |
| 36 | `MassMove` | Shift+right click on a square: the active unit and the units of its type on its square that can move and have no orders (not fortified, on sentry or working) go there, as with Go To, the others first, each as far as it gets this turn. |
| 42 | `StackSentry` | `U` (unload: wakes the land units on sentry in the stack) when none is on sentry: the stack's land units that can move and have no orders go on sentry (loaded, on a ship). |
| 50 | `RetirementYear=` | The year of the retirement (1 to 9999; the original's 2020), and `RetirementWarningYear=` its warning's (0: none; default 20 years before). Each comes the turn the year is reached or passed (the original: the turn of that very year). The texts (GAME.TXT's PLANRETIRE, "in 20 years") are the game's. |
| 51 | `PopulationLimit=` | A civilization's population, in 10,000 people (32000 to 3275800; the original's 32000, 320 million). Past 999 million the figure gets a second separator. The Hall of Fame keeps at most 32000 (its field is 16 bits). |
| 52 | `GoldLimit=` | The treasury (30000 to 1000000; the original's 30000), at the start of each turn, by scenario events and the cheat. |
| 53 | `MapTilesLimit=` | A custom world's width x height (10000 to 32767; the original's 10000). The dialog's text (GAME.TXT's CUSTOMSIZE) still says 10,000; the sides stay 20 to 250. |

The limits and the saved game: the units' limit (CIV2UIA's 2048, the size of the unit table)
is left out: more units need a larger table than the original's game state (its fixed layout,
which the saves and the replays use) and make saves the original cannot load. The others fit
the original's fields: the gold is 32 bits, the population is not saved (it is counted from
the cities), the year 16 bits, and a map of up to 32767 squares is what the original's
16-bit square count holds (civ2patch raised the same limit of the original game). The ranges
keep the game's own sums from overflowing: the population milestone (16 bits, the population
/ 100 + 9), the AI's sums with the treasury (gold / 50 x military strength, gold x 2). A save
with more than 30000 gold loads in the original, which brings the treasury back to 30000 at
the start of its next turn; the original checks the map's size only in the custom world
dialog, not when it loads a save.

In the code: `extra_rule(X_...)` (`src/include/extras.h`), off in network games like
`bugfix_state()`; each reads `if (extra_rule(X_...)) <changed> else <original>`, marked
`X<n>`; the limits' values come from `extras_gold_limit()` and the like (the original's
value with the rule off). Tests: `harness/extras/x-r*.txt`, run with `CIV2_TEST_EXTRAS` set to
the item (each script's comment says how); in a replay `CIV2_TEST_EXTRAS=all` turns on the
additions and the rule changes, `1` the additions only, and a list of numbers turns on those
(rule changes included); the limits are then the largest unless `CIV2_TEST_SETTINGS` gives
them (`RetirementYear=1902,RetirementWarningYear=1901`).

There is no dialog in the game to switch them: `CIV.INI` only, read at start.

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
