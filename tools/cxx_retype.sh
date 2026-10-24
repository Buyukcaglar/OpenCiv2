#!/bin/sh
# Retype function parameters / return values (tools/cxx_retype.py ROWS.tsv)
# and fix up the call sites, then compare every function with $CXX_BASE.
# Inside the container:  tools/dk sh tools/cxx_retype.sh ROWS.tsv
# Report: run/retype.log; functions whose code changed: run/retype.differ.
cd /work || exit 1
python3 tools/cxx_retype.py "$1" || exit 1
files="src/auto/*.cpp src/game/*.cpp src/data/gamedata.cpp src/native/crt.cpp"
flags="-m32 -std=gnu++17 -O1 -w -fno-strict-aliasing -fwrapv -fno-delete-null-pointer-checks -fno-inline \
  -include native.h -I src/include -I src/auto -I tools -I build/native/gen -DCIV2_NATIVE -fno-pie -DCIV2_LOWMEM \
  -fno-exceptions -fno-rtti -fmax-errors=100000 -fno-diagnostics-show-caret"
round=0
while [ $round -lt 8 ]; do
    round=$((round + 1))
    : > run/retype.err
    for f in $files; do g++ -fsyntax-only -x c++ $f $flags 2>&1 | grep -E 'error:|initializing argument' >> run/retype.err; done
    n=$(grep -c 'error:' run/retype.err)
    echo "round $round: $n errors"
    [ "$n" = 0 ] && break
    python3 tools/cxx_fix.py convcasts run/retype.err
done
: > run/retype.differ
for f in $files; do
    sh tools/cxx_one.sh $f 2>&1 | grep -v 'functions the same' >> run/retype.differ
done
echo "$(grep -c . run/retype.differ) functions differ (run/retype.differ)"
