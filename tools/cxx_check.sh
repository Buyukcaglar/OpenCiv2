#!/bin/sh
# Step 6: check an edited game source against the last commit: every
# function must compile to the same code at -O1 (tools/cxx_one.sh) or, if
# the optimizer only chose differently, at -O0 (code that follows the source
# literally).  Inside the container:  tools/dk sh tools/cxx_check.sh FILE...
# Bases: run/cxx-base (-O1) and run/cxx-base-O0, the last commit's objects.
cd /work || exit 1
for src in "$@"; do
    o1=$(sh tools/cxx_one.sh "$src" 2>&1)
    case "$o1" in *errors*) echo "$src: $o1"; continue ;; esac
    differ=$(echo "$o1" | grep -v 'functions the same' | cut -f2)
    if [ -z "$differ" ]; then echo "$src: OK (all the same at -O1)"; continue; fi
    o0=$(OPT=-O0 CXX_BASE=run/cxx-base-O0 sh tools/cxx_one.sh "$src" 2>&1 | grep -v 'functions the same' | cut -f2)
    both=$(for f in $differ; do echo "$o0" | grep -qx "$f" && echo "$f"; done)
    if [ -z "$both" ]; then echo "$src: OK ($(echo $differ | wc -w) differ at -O1 only)"; else
        echo "$src: DIFFER at -O1 and -O0:"; echo "$both" | sed 's/^/    /'; fi
done
