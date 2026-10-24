#!/bin/sh
# Step 6: compile one game source as C++ (the linux32 build's flags) and
# compare its functions with the C build's (tools/cxx_compare.py).  Inside
# the container:  tools/dk sh tools/cxx_one.sh src/auto/city.c [FUNCTION]
# Errors: run/cxxone/NAME.err.  Base objects: $CXX_BASE (default
# run/cbase/build/native/linux32, a worktree of the last C commit).
cd /work || exit 1
src=$1
obj=$(echo "$src" | tr / _).o
out=run/cxxone/$(basename "$src" .c)
base=${CXX_BASE:-run/cbase/build/native/linux32}
mkdir -p "$out"
extra=
case "$src" in */gamedata.c) extra=-fno-toplevel-reorder ;; esac
if ! g++ -c -o "$out/$obj" -x c++ "$src" -m32 -std=gnu++17 -O1 -g -w -fno-strict-aliasing -fwrapv \
        -fno-delete-null-pointer-checks -fno-inline -include native.h -I src/include -I src/auto -I tools \
        -I build/native/gen -DCIV2_NATIVE -fno-pie -DCIV2_LOWMEM -fno-exceptions -fno-rtti $extra \
        -fmax-errors=100000 -fno-diagnostics-show-caret 2> "$out.err"; then
    echo "$(grep -c 'error:' "$out.err") errors (run/cxxone/$(basename "$src" .c).err)"
    exit 1
fi
rm -f "$out.err"
python3 tools/cxx_compare.py "$base" "$out" $2
