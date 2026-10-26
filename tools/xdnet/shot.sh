#!/bin/sh
# shot.sh DISPLAY OUTPNG
xwd -root -silent -display :$1 | convert xwd:- png:$2
