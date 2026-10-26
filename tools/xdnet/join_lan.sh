#!/bin/sh
# Client side: from the start menu, join the first LAN (TCP/IP) game.  usage: join_lan.sh RUN NAME
S=/work/run/xd/cap/$1/shots; mkdir -p $S; K=/work/tools/xdnet/k.sh
until DISPLAY=:${DISP:-7} xdotool search --name "Civilization II" >/dev/null 2>&1; do sleep 1; done
sleep 20
$K $S/c1.png Down Down Down Down Down Return     # Multiplayer Game
$K $S/c2.png Down Return                         # Network Game
WAIT=3 $K $S/c3.png Return                       # TCP/IP
WAIT=3 $K $S/c4.png Down Down Down Down Down Return   # Join a Multiplayer Game
DISPLAY=:${DISP:-7} xdotool type --delay 120 "$2"
WAIT=6 $K $S/c5.png Return                       # net name -> game list
WAIT=4 $K $S/c6.png Return                       # Join Game
