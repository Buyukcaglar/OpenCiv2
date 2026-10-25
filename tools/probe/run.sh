#!/bin/sh
# Run a probe program under Wine on a virtual X display, the way the harness
# runs the game.  Usage (in the container): sh tools/probe/run.sh NAME [ARGS]
cd /work/tools/probe
name=$1; shift
i686-w64-mingw32-gcc -O1 -o /tmp/$name.exe $name.c -lgdi32 -luser32 -lwinmm -lusp10 || exit 1
Xvfb :9 -screen 0 1024x768x24 -nolisten tcp >/dev/null 2>&1 &
xvfb=$!
sleep 1.5
DISPLAY=:9 wine /tmp/$name.exe "$@" 2>/dev/null
kill $xvfb
