#!/bin/sh
# Compare two native builds on the same scripts: a difference is a bug of one
# of them, with no recording of the original needed (the 32-bit build has the
# original's x86 behaviour; the portable build is the one that differs most).
# Also fails on a crash, a timeout or a SUSPICIOUS request (CIV2_STRICT).
# Runs inside the civ2-dev container:
#   tools/dk sh harness/diff_suite.sh [SCRIPT...]   (default: harness/diffscripts: autoplay, monkeys)
# A=, B= select the builds (default civ2-linux32 and OpenCiv2).
cd /work
A=${A:-civ2-linux32}
B=${B:-OpenCiv2}
scripts=${*:-harness/diffscripts/*.txt}
fail=0
echo "comparing build/$A with build/$B"
for s in $scripts; do
    n=$(basename "$s" .txt)
    for side in a b; do
        exe=$A; [ $side = b ] && exe=$B
        rm -rf run/diff$side-$n
        EXE=$exe CIV2_STRICT=1 TIMEOUT=${TIMEOUT:-5400} sh tools/native-run.sh /work/$s /work/run/diff$side-$n \
            > run/diff$side-$n.log 2>&1
        status=$?
        python3 -c "
import glob
from PIL import Image
for f in glob.glob('/work/run/diff$side-$n/*.bmp'):
    Image.open(f).save(f[:-4] + '.png')
"
        if [ $status != 0 ]; then
            echo "FAIL $n: $exe exited with status $status (124: timeout)"; fail=1
        fi
        if grep -q SUSPICIOUS run/diff$side-$n/hook.log 2>/dev/null; then
            echo "FAIL $n: $exe:"; grep SUSPICIOUS run/diff$side-$n/hook.log | head -3 | sed 's/^/    /'; fail=1
        fi
    done
    if python3 harness/compare.py run/diffa-$n run/diffb-$n --report run/report-diff-$n > run/compare-diff-$n.txt; then
        echo "SAME $n ($(tail -1 run/compare-diff-$n.txt))"
    else
        echo "DIFF $n"; grep -v ": identical" run/compare-diff-$n.txt | head -12 | sed 's/^/    /'
        fail=1
    fi
done
exit $fail
