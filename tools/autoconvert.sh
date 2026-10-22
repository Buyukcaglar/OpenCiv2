#!/bin/sh
# Regenerate src/auto from the Ghidra export and demote functions that do not
# compile until the whole tree builds.  Runs inside the civ2-dev container.
set -e
rm -f re/compile_failures.tsv re/unresolved.txt
for round in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20; do
    python3 tools/gen_c.py
    status=0
    python3 tools/build_recon.py --keep-going "$@" || status=$?
    [ $status -eq 0 ] && exit 0
    [ $status -eq 2 ] || exit 1
done
echo "still failing after 20 rounds" >&2
exit 1
