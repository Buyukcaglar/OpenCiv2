#!/bin/sh
# Step 6 (RAII): check the game sources changed against the committed
# version (or $RAII_REV).  On the host:  tools/raii_check.sh FILE...
# Both compiled at -O1 with the build's -fno-inline (tools/cfg_one.sh; the
# guards of src/include/scoped.h are always_inline).  Per function: the
# control-flow graph (tools/cfg_compare.py); where it differs, the sequences
# of calls per path (tools/calls_compare.py).  Base objects cached in
# run/raii-cbase: delete that directory after a commit.
cd "$(dirname "$0")/.." || exit 1
rev=${RAII_REV:-HEAD}
for f in "$@"; do
    name=$(basename "$f" .cpp)
    obj=$(echo "$f" | tr / _).o
    mkdir -p run/raii-cbase/src run/raii-cnew
    if [ ! -f "run/raii-cbase/$name.o" ]; then
        git show "$rev:$f" > "run/raii-cbase/src/$name.cpp" || exit 1
        tools/dk env OPT=-O1 sh tools/cfg_one.sh "run/raii-cbase/src/$name.cpp" run/raii-cbase/tmp || exit 1
        mv "run/raii-cbase/tmp/run_raii-cbase_src_$name.cpp.o" "run/raii-cbase/$name.o" || exit 1
    fi
    tools/dk env OPT=-O1 sh tools/cfg_one.sh "$f" run/raii-cnew || exit 1
    echo "== $f"
    python3 tools/cfg_compare.py --map re/methods.tsv "run/raii-cbase/$name.o" "run/raii-cnew/$obj" > run/raii-cnew/$name.cfg.txt 2>&1
    grep 'functions the same' run/raii-cnew/$name.cfg.txt
    differ=$(grep -v 'functions the same' run/raii-cnew/$name.cfg.txt | cut -f1)
    [ -z "$differ" ] && continue
    python3 tools/calls_compare.py --map re/methods.tsv "run/raii-cbase/$name.o" "run/raii-cnew/$obj" $differ \
        | sed 's/^/graph differs: /'
done
