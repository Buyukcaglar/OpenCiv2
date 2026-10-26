#!/bin/sh
# k.sh SHOTPATH keys...   (send keys to display :${DISP:-7} with xdotool, wait $WAIT s, screenshot)
s=$1; shift
for k in "$@"; do DISPLAY=:${DISP:-7} xdotool key --delay 150 "$k"; sleep 0.4; done
sleep ${WAIT:-2}
/work/tools/xdnet/shot.sh ${DISP:-7} $s
