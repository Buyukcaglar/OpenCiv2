# Interface additions

OpenCiv2 adds to the original game's interface the features of
[CIV2UIA](https://github.com/FoxAhead/Civ2-UI-Additions), the "Civilization II User Interface
Additions" launcher by FoxAhead, which patches the original executable. They are written anew
for OpenCiv2's code from CIV2UIA's description of them; no code of CIV2UIA's is used.
Thanks to FoxAhead and the CIV2UIA contributors for the ideas and for documenting them.

This file covers the additions to the interface, which change only what the player sees and
does and are on by default, and, under [Rule changes](#rule-changes), the changes to the
game's rules (with the limits CIV2UIA takes from
[civ2patch](https://github.com/vinceho/civ2patch)), which are off by default. CIV2UIA's bug
fixes are in [BUGS.md](BUGS.md).

## On and off

The additions are on by default. They are off:

- with `CIV2_CLASSIC=1` (the original game: its look, its bugs, and none of these);
- in replays and unit tests, which are compared with the original game.

They change only what this player sees and how the interface is used, never what the game
computes, so they stay on in network games (a production changed from the City Status
advisor, or specialists changed with the wheel, are the same orders as through the city
window).

Each one can be switched off in the `[OpenCiv2]` section of `CIV.INI` (the file the game
keeps its own settings in, in its Windows directory): its key `=0`.

| Key | What |
| --- | --- |
| `MouseWheel` | The mouse wheel scrolls the list or scroll bar under the pointer (advisors, dialogs, the city window's improvements and supported units, the Civilopedia), changes a specialist under the pointer in the city window, turns the tax rates' bars; Ctrl+wheel zooms the map, Ctrl+middle button sets the normal zoom; a middle click centres the map there, a middle drag pans it. |
| `UnitListScroll` | The Activate Unit list of a stack of more than 9 units shows all of them, in a list that scrolls. |
| `UnitListKeys` | (with `UnitListScroll`) that list's keys (arrows, Page Up/Down) and wheel. |
| `WorkCounter` | A settler's or engineer's work counter on its picture on the map (own units). |
| `GameTurn` | The game turn in the status panel, after the year. |
| `ResearchNumbers` | The Science Advisor: the bulbs so far, the advance's cost and the bulbs per turn. |
| `ZeroUpkeep` | The Trade Advisor lists the buildings that cost no upkeep too. |
| `SupportScroll` | The city window's supported units: their total, and a scroll bar when they do not fit. |
| `SupportSort` | That list sorted: settlers, then the units that can attack (land, air, sea; stronger defence, then attack, first), then the rest. |
| `AttitudeColors` | The Attitude Advisor: celebrating cities in yellow, the food surplus or shortage icon after the name. |
| `CityAttitude` | The city window: the texts under the citizens coloured as in the Attitude Advisor (yellow celebrating, red in disorder). |
| `RadioHotkeys` | Each radio button of a dialog gets a hotkey (the first letter of its label no other has, underlined). |
| `Quickinfo` | Ctrl held with the pointer over the map: the city's and the units' details on that square. |
| `ProductionCancel` | A Cancel button in the city's Change Production list (Escape). |
| `ProductionCost` | The shields each item costs, and the upkeep of buildings, in that list. |
| `CityStatus` | The City Status advisor: the number of cities, headings that sort the list (size, name, food, shields, trade, production; again: the game's order), the production's picture; a click on a city's production opens its Change Production. |
| `MassSpecialists` | In the city window, Shift+wheel over a specialist changes all of them, Shift+click on one makes all the others the same. |
| `SuppressPopups` | Simple popups of GAME.TXT (text and an OK button only) whose sections are listed in `SuppressList=` (`[OpenCiv2]`, names separated by commas: `SuppressList=HIDDENTERRAIN,CITYSIZE`) are shown over the top of the map for a few seconds instead. Empty by default. |
| `ColorCorrection` | Colour correction of the whole screen: `Gamma=` (percent, 100 none), `Brightness=` and `Contrast=` (-100 to 100, 0 none). |
| `ForeignGold` | Gold coins in the Foreign Minister's list. |
| `ArrangeWindowsSL` | View > Arrange Windows S and L: a smaller or larger side panel than Arrange Windows. |
| `PathLines` | Shift held with the pointer over the map: the way the active unit would go there over the map as the player knows it (Dijkstra's over the known terrain, roads and railroads; hidden units and cities not counted); over the city under the cursor (View Pieces): lines to its trade routes' cities. |
| `SentryHalftone` | Units on sentry (and aircraft at a base) drawn in grey halftones instead of a grey shape. |
| `DefaultZoom1` | The map of a new game (or of a save without its layout) at zoom 1:1, whatever the screen width. |

## Rule changes

CIV2UIA's items that change the game's rules, and the limits it took from civ2patch, are off
by default: each is switched on in the same `[OpenCiv2]` section of `CIV.INI`, the item by
its key `=1`, a limit by its value (`=0` or no key: the original's). They are off with
`CIV2_CLASSIC=1`, in replays and unit tests, and in network games (as the state fixes of
[BUGS.md](BUGS.md): every player, the original game included, must compute the same game);
they stay on in hot-seat games. The changes for units apply to the human
players' units only: the computer players play by the original rules.

| Key | What |
| --- | --- |
| `WorkerHandover` | A settler or engineer given the terrain order of one already working on its square takes its work (as the original) and the other one stops (no orders), so that it can go elsewhere at once: one worker with the order on a square. |
| `GotoNoZocStop` | A unit on Go To does not stop when it comes next to a foreign unit (the original: only caravans and freight go on). Zones of control still apply: it stops when they block its way or its moves run out; a unit sent at an enemy attacks what is in its way. |
| `UnitRotation` | Activating a unit (from the map or the stack's list) clears the Wait of the units of its stack and sets it on all the civilization's other units: the stack's units come next. And the next unit is looked for near the square where the last unit was activated (by the player or as the next one), not where it has moved to. |
| `MassMove` | Shift+right click on a square: the active unit and the units of its type on its square that can move and have no orders (not fortified, on sentry or working) go there, as with Go To, the others first, each as far as it gets this turn. |
| `StackSentry` | `U` (unload: wakes the land units on sentry in the stack) when none is on sentry: the stack's land units that can move and have no orders go on sentry (loaded, on a ship). |
| `RetirementYear=` | The year of the retirement (1 to 9999; the original's 2020), and `RetirementWarningYear=` its warning's (0: none; default 20 years before). Each comes the turn the year is reached or passed (the original: the turn of that very year). The texts (GAME.TXT's PLANRETIRE, "in 20 years") are the game's. |
| `PopulationLimit=` | A civilization's population, in 10,000 people (32000 to 3275800; the original's 32000, 320 million). Past 999 million the figure gets a second separator. The Hall of Fame keeps at most 32000 (its field is 16 bits). |
| `GoldLimit=` | The treasury (30000 to 1000000; the original's 30000), at the start of each turn, by scenario events and the cheat. |
| `MapTilesLimit=` | A custom world's width x height (10000 to 32767; the original's 10000). The dialog's text (GAME.TXT's CUSTOMSIZE) still says 10,000; the sides stay 20 to 250. |
