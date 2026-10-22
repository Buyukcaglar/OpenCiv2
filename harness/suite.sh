#!/bin/sh
# Run every scenario on the reconstruction and compare against the original.
# References (run/ref-NAME) are recorded first if missing, or always with -r.
# Runs inside the civ2-dev container:  tools/dk sh harness/suite.sh [-r] [SCRIPT...]
cd /work
SEED=${SEED:-7}
rerecord=0
[ "$1" = "-r" ] && { rerecord=1; shift; }
scripts=${*:-harness/scripts/*.txt}
# Refuse to test a stale build: every source must be older than the executable.
exe=${RECON_EXE:-build/civ2_recon.exe}
newer=$(find src -name '*.[ch]' -newer "$exe" | head -3)
if [ -n "$newer" ]; then
    echo "STALE: $exe is older than $newer -- rebuild first"; exit 2
fi
fail=0
for s in $scripts; do
    n=$(basename "$s" .txt)
    if [ $rerecord = 1 ] || [ ! -d run/ref-$n ]; then
        rm -rf run/ref-$n
        python3 harness/run.py --build orig --seed $SEED --script "$s" --out run/ref-$n > /dev/null 2>&1
    fi
    rm -rf run/recon-$n
    python3 harness/run.py --build recon ${RECON_EXE:+--recon-exe $RECON_EXE} --seed $SEED --script "$s" --out run/recon-$n > /dev/null 2>&1
    if python3 harness/compare.py run/ref-$n run/recon-$n --report run/report-$n > run/compare-$n.txt; then
        echo "PASS $n ($(tail -1 run/compare-$n.txt))"
    else
        echo "FAIL $n"; grep -v ": identical" run/compare-$n.txt | sed 's/^/    /'
        fail=1
    fi
done
exit $fail
