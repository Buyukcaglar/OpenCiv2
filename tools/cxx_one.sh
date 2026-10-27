#!/bin/sh
# Step 6: compile one game source as C++ (the linux32 build's flags) and
# compare its functions with the C build's (tools/cxx_compare.py).  Inside
# the container:  tools/dk sh tools/cxx_one.sh src/auto/city.cpp [FUNCTION]
# OPT=-O0: at -O0 (with CXX_BASE objects built so), where code follows the
# source literally: what -O1 changes only by register or scheduling
# choices compares equal there.  Errors: run/cxxone/NAME.err.  Base objects: $CXX_BASE (default
# run/cxx-base: copy build/native/linux32's game objects there from the
# commit to compare with; CIV2_CXX=permissive objects compare a source that
# strict C++ does not accept yet).
cd /work || exit 1
src=$1
obj=$(echo "$src" | tr / _).o
name=$(basename "$src"); name=${name%.*}
out=run/cxxone/$name
base=${CXX_BASE:-run/cxx-base}
mkdir -p "$out"
extra=
case "$src" in */gamedata.cpp) extra=-fno-toplevel-reorder ;; esac
if ! g++ -c -o "$out/$obj" -x c++ "$src" -m32 -std=gnu++17 ${OPT:--O1} -g -w -fno-strict-aliasing -fwrapv \
        -fno-delete-null-pointer-checks -fno-inline -include native.h -I src/include -I src/auto -I tools \
        -I build/native/gen -DCIV2_NATIVE -fno-pie -DCIV2_LOWMEM -fno-exceptions -fno-rtti $extra \
        -fmax-errors=100000 -fno-diagnostics-show-caret 2> "$out.err"; then
    echo "$(grep -c 'error:' "$out.err") errors (run/cxxone/$name.err)"
    exit 1
fi
rm -f "$out.err"
python3 tools/cxx_compare.py --map re/methods.tsv "$base" "$out" $2
