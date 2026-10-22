#!/bin/sh
# Run Ghidra post-scripts against the project, then export into re/.
# Usage: tools/ghidra_run.sh [Script.java [arg]]...   (export always runs last)
set -e
cd "$(dirname "$0")/.."
args=""
while [ $# -gt 0 ]; do
    args="$args -postScript $1"
    shift
    case "$1" in *.java|"") ;; *) args="$args $1"; shift ;; esac
done
mkdir -p scratch_export
docker run --rm -v "$PWD":/work civ2-ghidra /opt/ghidra/support/analyzeHeadless /work/re/gproj civ2 \
    -process civ2.exe -noanalysis -scriptPath /work/tools/ghidra_scripts $args \
    -postScript ExportAll.java /work/scratch_export > re/ghidra-run.log 2>&1
grep -E "^INFO .*(java>|ERROR)" re/ghidra-run.log | grep -v "decompiled [0-9]" || true
mv scratch_export/* re/
rmdir scratch_export
