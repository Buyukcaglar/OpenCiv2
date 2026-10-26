#!/bin/sh
# Host side: from the start menu, start a new LAN (TCP/IP) game and wait for players.
# usage: host_lan.sh RUN NAME GAMENAME
S=/work/run/xd/cap/$1/shots; mkdir -p $S; K=/work/tools/xdnet/k.sh
until DISPLAY=:${DISP:-7} xdotool search --name "Civilization II" >/dev/null 2>&1; do sleep 1; done
sleep 20
$K $S/h01.png Down Down Down Down Down Return    # Multiplayer Game
$K $S/h02.png Down Return                        # Network Game
WAIT=3 $K $S/h03.png Return                      # TCP/IP
WAIT=3 $K $S/h04.png Return                      # Start a New Multiplayer Game
WAIT=4 $K $S/h05.png Up Return                   # Small world
WAIT=3 $K $S/h06.png Return                      # difficulty (default)
WAIT=3 $K $S/h07.png Down Down Down Down Return  # 3 civilizations
WAIT=3 $K $S/h08.png Return                      # aggression
WAIT=3 $K $S/h09.png Return                      # standard rules
WAIT=3 $K $S/h10.png Return                      # multiplayer features (none)
WAIT=3 $K $S/h11.png Return                      # turn timer unlimited
DISPLAY=:${DISP:-7} xdotool type --delay 120 "$2"
WAIT=3 $K $S/h12.png Return                      # net name
DISPLAY=:${DISP:-7} xdotool type --delay 120 "$3"
WAIT=4 $K $S/h13.png Return                      # game name -> Available Players
