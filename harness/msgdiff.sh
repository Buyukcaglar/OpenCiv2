#!/bin/sh
# Compare the messages the game's windows receive in the original (under
# Wine, via the hook runtime) and in the native build, for one scenario.
# Run on the host:  sh harness/msgdiff.sh SCRIPTNAME [-r]   (-r: retrace Wine)
# The Wine trace is kept in run/trace-NAME; differences are printed as a diff
# of "create", "msg" (retrieved) and "deliver" (sent to a window procedure)
# lines, windows numbered in creation order.
# WM_PALETTEISCHANGING (0310) is left out: whether it is broadcast depends on
# the game's WM_QUERYNEWPALETTE handler returning an uninitialised local
# (stack garbage from Wine's call chain), and the game ignores it.
cd "$(dirname "$0")/.."
n=$1
if [ "$2" = -r ] || [ ! -f run/trace-$n/hook.log ]; then
    tools/dk2 sh -c "CIV2_TRACE_MSG=1 python3 harness/run.py --build orig --seed 7 --script harness/scripts/$n.txt --out run/trace-$n" >/dev/null 2>&1
fi
tools/dk sh -c "CIV2_TRACE_MSG=1 EXE=${EXE:-civ2-linux32} sh tools/native-run.sh /work/harness/scripts/$n.txt /work/run/native-$n" >/dev/null 2>&1
grep -E "^(msg|create|deliver|shot) " run/trace-$n/hook.log | sed -E 's/ #[0-9]+( @[0-9]+)?$//' | grep -v '^deliver 0310 ' > run/msgs-wine-$n.txt
grep -E "^(msg|create|deliver|shot) " run/native-$n/hook.log | sed -E 's/ #[0-9]+( @[0-9]+)?$//' | grep -v '^deliver 0310 ' > run/msgs-native-$n.txt
echo "wine $(wc -l < run/msgs-wine-$n.txt) lines, native $(wc -l < run/msgs-native-$n.txt) lines"
diff run/msgs-wine-$n.txt run/msgs-native-$n.txt > run/msgdiff-$n.txt
grep -c "^[<>]" run/msgdiff-$n.txt | sed 's/^/differing lines: /'
