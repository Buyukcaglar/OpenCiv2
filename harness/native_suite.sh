#!/bin/sh
# Run every scenario on the native build and compare against the original's
# recordings (run/ref-NAME, made by harness/run.py: make ref).
# Runs inside the civ2-dev container:  tools/dk sh harness/native_suite.sh [SCRIPT...]
# EXE selects the executable in build/ (default civ2-linux32).
cd /work
export EXE=${EXE:-civ2-linux32}
scripts=${*:-harness/scripts/*.txt}
fail=0
echo "testing build/$EXE"
for s in $scripts; do
    n=$(basename "$s" .txt)
    rm -rf run/native-$n
    TIMEOUT=${TIMEOUT:-900} sh tools/native-run.sh /work/$s /work/run/native-$n > run/native-$n.log 2>&1
    python3 -c "
import glob
from PIL import Image
for f in glob.glob('/work/run/native-$n/*.bmp'):
    Image.open(f).save(f[:-4] + '.png')
"
    if grep -q "not laid out as in the original" run/native-$n.log; then
        echo "FAIL $n"; grep "not laid out" run/native-$n.log | sed 's/^/    /'
        fail=1
    elif python3 harness/compare.py run/ref-$n run/native-$n --report run/report-native-$n > run/compare-native-$n.txt; then
        echo "PASS $n ($(tail -1 run/compare-native-$n.txt))"
    else
        echo "FAIL $n"; grep -v ": identical" run/compare-native-$n.txt | sed 's/^/    /'
        fail=1
    fi
done
exit $fail
