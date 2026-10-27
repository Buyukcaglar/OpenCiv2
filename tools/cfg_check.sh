#!/bin/sh
# Step 6 (gotos): compare the control-flow graphs of the functions of game
# sources against the committed version (tools/cfg_compare.py).  On the host:
#   tools/cfg_check.sh FILE... [-- FUNCTION]
# At -O0 first (each expression compiled as written, the graph made of the
# source's own jumps); a function that differs there is compared again at
# -O2, where gcc normalizes the control flow.  Base objects (the HEAD
# version, or $CFG_REV) are cached in run/cfg-base; delete that directory
# after a commit.
cd "$(dirname "$0")/.." || exit 1
rev=${CFG_REV:-HEAD}
fn=
files=
while [ $# -gt 0 ]; do
    if [ "$1" = -- ]; then fn=$2; break; fi
    files="$files $1"; shift
done
for f in $files; do
    name=$(basename "$f" .cpp)
    obj=$(echo "$f" | tr / _).o
    echo "== $f"
    differ=
    for o in O0 O2; do
        mkdir -p run/cfg-base/src run/cfg-base/$o run/cfg-new/$o
        if [ ! -f "run/cfg-base/$o/$name.o" ]; then
            git show "$rev:$f" > "run/cfg-base/src/$name.cpp" || exit 1
            tools/dk env OPT=-$o sh tools/cfg_one.sh "run/cfg-base/src/$name.cpp" run/cfg-base/tmp || exit 1
            mv "run/cfg-base/tmp/run_cfg-base_src_$name.cpp.o" "run/cfg-base/$o/$name.o" || exit 1
        fi
        tools/dk env OPT=-$o sh tools/cfg_one.sh "$f" run/cfg-new/$o || exit 1
        if [ $o = O0 ]; then
            python3 tools/cfg_compare.py --map re/methods.tsv "run/cfg-base/$o/$name.o" "run/cfg-new/$o/$obj" $fn \
                > run/cfg-new/$name.O0.txt 2>&1
            grep 'functions the same' run/cfg-new/$name.O0.txt | sed 's/^/-O0: /'
            differ=$(grep -v 'functions the same' run/cfg-new/$name.O0.txt | cut -f1)
            [ -z "$differ" ] && break
        else
            for d in $differ; do
                python3 tools/cfg_compare.py --map re/methods.tsv "run/cfg-base/$o/$name.o" "run/cfg-new/$o/$obj" "$d" 2>/dev/null \
                    | sed 's/^/-O0 differs; -O2: /' | grep . || echo "-O0 differs; -O2: $d	the same graph"
            done
        fi
    done
done
