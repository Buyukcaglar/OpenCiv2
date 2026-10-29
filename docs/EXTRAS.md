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

Each one can be switched off in the game with Game > OpenCiv2 Options (Interface additions),
which shows at once what it changes, or in the `[OpenCiv2]` section of `CIV.INI` (the file the
game keeps its own settings in, in its Windows directory, where the dialog writes them too): its
key `=0`.

| Key | What |
| --- | --- |
| `MouseWheel` | Use the mouse wheel and middle button. The wheel scrolls whatever list or scroll bar is under the pointer (advisors, dialogs, the city window, the Civilopedia), changes the specialist under the pointer in the city window, and moves the tax rate bars. Ctrl+wheel zooms the map and Ctrl+middle click returns to normal zoom. Middle click centres the map on that spot; dragging with the middle button pans it. |
| `UnitListScroll` | When you click a stack of more than 9 units, the list of units to activate shows all of them and scrolls, instead of stopping at 9. |
| `UnitListKeys` | In that scrolling unit list, the arrow keys, Page Up/Down and the mouse wheel move through the list. Needs `UnitListScroll`. |
| `WorkCounter` | Your settlers and engineers show on the map how much terrain work they have done so far. |
| `GameTurn` | The status panel shows the turn number after the year. |
| `ResearchNumbers` | The Science Advisor shows the research points collected so far, the cost of the current advance, and the points gained per turn. |
| `ZeroUpkeep` | The Trade Advisor also lists buildings that cost nothing to maintain. |
| `SupportScroll` | The city window shows how many units the city supports, with a scroll bar when they don't all fit. |
| `SupportSort` | The city window's supported units are sorted: settlers and engineers first, then attack units (land, air, then sea; strongest first), then the rest. |
| `AttitudeColors` | The Attitude Advisor shows celebrating cities in yellow, and an icon after a city's name when it has a food surplus or shortage. |
| `CityAttitude` | In the city window, the text under the citizens is coloured as in the Attitude Advisor: yellow when the city celebrates, red when it is in disorder. |
| `RadioHotkeys` | Options in dialogs get a keyboard shortcut: a letter of the option's name, shown underlined. |
| `Quickinfo` | Hold Ctrl with the pointer over a map square to see details of the city and units there. |
| `ProductionCancel` | The city's Change Production dialog gets a Cancel button; Escape cancels too. |
| `ProductionCost` | The Change Production list shows what each item costs in shields, and each building's upkeep. |
| `CityStatus` | The City Status advisor shows how many cities you have and each city's production as a picture. Click a column heading (size, name, food, shields, trade, production) to sort by it; click it again for the game's usual order. Click a city's production to change it. |
| `MassSpecialists` | In the city window, Shift+wheel over a specialist changes all specialists at once, and Shift+click on one makes all the others the same type. |
| `SuppressPopups` | Simple messages that only have an OK button can be shown for a few seconds across the top of the map instead of waiting for a click. List which ones by their GAME.TXT section names in `SuppressList=`, separated by commas, for example `SuppressList=HIDDENTERRAIN,CITYSIZE`. The list is empty by default. |
| `ColorCorrection` | Adjusts the colours of the whole screen: `Gamma=` (a percentage, 100 means no change), `Brightness=` and `Contrast=` (-100 to 100, 0 means no change). These and `SuppressList=` are also in Game > OpenCiv2 Options (Display and messages). |
| `ForeignGold` | The Foreign Minister shows each civilization's gold with a coin icon. |
| `ArrangeWindowsSL` | The View menu gets Arrange Windows S and Arrange Windows L, which arrange the windows with a narrower or wider side panel than Arrange Windows. |
| `PathLines` | Hold Shift with the pointer over the map to see the path the active unit would take there, based on the map as you know it (units and cities you can't see aren't counted). With a city selected (View Pieces, the cursor on it), hold Shift over the same city to see lines to the cities it has trade routes with, or over another city to see the way a road or railroad must take to give their trade routes the road bonus (the game looks for it along this way only, up to the other city or one of your cities on the way): yellow if the road is already there and gives the bonus, white if not. |
| `SentryHalftone` | Units on sentry, and aircraft at a base, are drawn in grey shades so you can still tell what they are, instead of as a flat grey shape. |
| `DefaultZoom1` | A new game (or a save without a saved window layout) starts with the map at normal 1:1 zoom, whatever the screen size. |
| `IntegerZoom` | The map zooms only in whole steps, at which every pixel of the tiles is drawn the same size: ¼, ½, 1:1 and 2× (tiles 16, 32, 64 and 128 pixels wide). Zoom In and Zoom Out (Z, X, Ctrl+wheel) go to the next of these; the View menu's zooms and a saved game's go to the nearest (Medium Zoom Out: ½, Max Zoom Out: ¼). The original's other twelve zooms draw some rows and columns of each tile twice, or leave them out, and not the rest. OpenCiv2's own addition, not CIV2UIA's. |

## Screen scale

Where the system scales things up, the game is drawn larger, in whole steps: each of the
game's pixels becomes 2×2 or 3×3 of the screen's. By default the step is the system's own
scale, rounded down: on Windows its display scaling (100% to 175%: 1, the screen's own pixels;
200%: 2; 300%: 3), on a Mac the Retina screen's pixels per point (2). Elsewhere (Linux, and
with `CIV2_CLASSIC=1`) it is the largest step that still leaves the game at least 1024×768 (a
4K screen: 2, the game at 1920×1080). Change it in Game > OpenCiv2 Options (Display and
messages), Screen scale, or with `Scale=` in `CIV.INI` (0 means the default); it takes effect
the next time the game starts. The game is never made smaller than 640×480.

At a step of 2 or 3 (4, 6: 2 or 3, then doubled) the game's pixels are smoothed with Scale2x or
Scale3x, which round off the steps along the edges of one colour against another (text,
outlines) and leave the rest as blocks. `SmoothScale=0` (or Smooth that scale: 0 in the same
dialog, at once) shows them as plain blocks. The game draws its text at its own size, as
pixels like the rest, so drawn larger it cannot be as sharp as the screen's own text.

## Fonts

On Windows the game's text is drawn in the fonts it asks for, as Windows draws them, as the
original's was: Times New Roman, Arial, Courier and System, each letter drawn by Windows (GDI)
and then placed by the game as before. On the game's own 256-colour surfaces the letters are
not antialiased, as on Windows; elsewhere they are, in Windows' grey levels. `SystemFonts=0`
(or System's fonts: 0 in Game > OpenCiv2 Options, Display and messages; from the next start)
uses the glyphs recorded from the original under Wine instead, which has none of these fonts
and draws DejaVu Serif, DejaVu Sans and DejaVu Sans Mono in their place. Those are also what
the other systems, the replays and the unit tests use, since the replays compare the game's
screens with the original's under Wine (`CIV2_TEST_SYSFONTS=1` turns the system's fonts on in
a replay, for tests of them).

With the system's fonts, where the desktop is drawn larger (`Scale` 2 or more), the text is
also drawn sharp: each letter the game draws is noted, with where it was drawn and in which
font, followed as the game copies its pictures from surface to surface and onto the screen,
and drawn again by Windows over the enlarged screen, at the screen's own pixels and
antialiased, in place of the enlarged letter. Text that is not the game's letters (the
numbers and words in its pictures, such as the city sizes' digits) stays as drawn.
`SharpText=0` (Text drawn sharp: 0, from the next start) draws the letters enlarged as the rest.

## Rule changes

CIV2UIA's items that change the game's rules, and the limits it took from civ2patch, are off
by default: each is switched on with Game > OpenCiv2 Options (Rule changes, Limits) or in the
same `[OpenCiv2]` section of `CIV.INI`, the item by its key `=1`, a limit by its value (`=0` or
no key: the original's).  In a network game the dialog does not change them. They are off with
`CIV2_CLASSIC=1`, in replays and unit tests, and in network games (as the state fixes of
[BUGS.md](BUGS.md): every player, the original game included, must compute the same game);
they stay on in hot-seat games. The changes for units apply to the human
players' units only: the computer players play by the original rules.

| Key | What |
| --- | --- |
| `WorkerHandover` | When a settler or engineer joins another already doing the same terrain work on its square, the newcomer takes over the work done so far and the first one is freed to go elsewhere. Only one worker keeps the order on each square. |
| `GotoNoZocStop` | A unit on Go To keeps going when it comes next to a foreign unit, instead of stopping (in the original, only caravans and freight do). Zones of control still apply: it stops when one blocks its way or it runs out of moves. A unit sent at an enemy will attack whatever is in its way. |
| `UnitRotation` | When you activate a unit, the other units on its square come next before any elsewhere. After that, the next unit is the one nearest to where you last activated a unit, rather than to where that unit has since moved. |
| `MassMove` | Shift+right click on a square sends the active unit there along with every unit of the same type on its square that can move and has no orders (not fortified, on sentry or working). Each goes as far as it can this turn, as with Go To. |
| `StackSentry` | `U` normally wakes the land units on sentry in a stack. If none is on sentry, `U` instead puts all the stack's land units that have no orders on sentry (on a ship: loads them). |
| `RetirementYear=` | Sets the year the game ends with retirement (1 to 9999; the original is 2020). `RetirementWarningYear=` sets the year of the warning (0 for none; by default 20 years earlier). Each happens on the first turn on or after that year. The game's own messages still say "in 20 years". |
| `PopulationLimit=` | Raises the highest population a civilization can reach, in units of 10,000 people (32000 to 3275800; the original is 32000, which is 320 million). The Hall of Fame still records at most 320 million. |
| `GoldLimit=` | Raises the most gold a treasury can hold (30000 to 1000000; the original is 30000). |
| `MapTilesLimit=` | Raises the largest custom world, as width × height in squares (10000 to 32767; the original is 10000). Each side is still 20 to 250 squares. The dialog's text still says 10,000. |
