#!/bin/sh
# Full analysis -> generation -> build pipeline (host side).
#   1. machine-code facts (conventions, call sites) from the current function table
#   2. apply them in Ghidra and re-export the decompilation
#   3. regenerate src/auto, demote what does not compile, build, ABI-check
set -e
cd "$(dirname "$0")/.."
tools/dk python3 tools/conventions.py 2>&1 | grep -v "multiple ret" | tail -1
tools/dk python3 tools/callsites.py
tools/ghidra_run.sh ApplyConventions.java /work/re/conventions.tsv ApplySignatures.java /work/re/callsites.tsv
tools/dk sh tools/autoconvert.sh 2>&1 | grep -v "note:" | tail -3
tools/dk python3 tools/check_abi.py | head -20
