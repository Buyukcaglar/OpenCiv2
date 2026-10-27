#!/bin/sh
# Step 6 (gotos): compile one game source at -O2 for tools/cfg_compare.py.
# Inside the container:  tools/dk sh tools/cfg_one.sh SRC OUTDIR
# Writes OUTDIR/<src with / as _>.o.  Jump tables, hot/cold splitting and
# clones are off so that every branch is an explicit edge of the graph.
cd /work || exit 1
src=$1
out=$2
mkdir -p "$out"
obj=$(echo "$src" | tr / _).o
exec g++ -c -o "$out/$obj" -x c++ "$src" -m32 -std=gnu++17 ${OPT:--O2} -w -fno-strict-aliasing -fwrapv \
    -fno-delete-null-pointer-checks -fno-inline -fno-jump-tables -fno-reorder-blocks-and-partition \
    -fno-ipa-cp -fno-ipa-sra -fno-ipa-icf -fno-optimize-sibling-calls \
    -include native.h -I src/include -I src/auto -I src/game -I tools \
    -I build/native/gen -DCIV2_NATIVE -fno-pie -DCIV2_LOWMEM -fno-exceptions -fno-rtti \
    -fmax-errors=20 -fno-diagnostics-show-caret
