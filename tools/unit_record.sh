#!/bin/sh
# Record the unit tests' cases (tests/unit/*.gz) from replays: the recording
# build plays each scenario (as the replay suite does; its screenshots and
# rand() trace are compared with the original's), recording calls of the
# game's functions (tests/unit_record.c), then the runner keeps the cases it
# reproduces, twice in each of three processes (civ2-unittest --bless).
# Inside the container, after
#   python3 tools/build_native.py --target linux32rec
#   python3 tools/build_native.py --target linux32test
#   python3 tools/unit_textmask.py build/civ2-unittest > tests/unit/textmask.tsv
# usage: tools/dk sh tools/unit_record.sh SCRIPT...    (make unit-record: all of UNIT_SCRIPTS)
# Each scenario takes a few minutes.  Per function at most 6 cases per
# scenario, 16 with the other scenarios' (tests/unit_record.c: CIV2_UNITREC_*).
cd /work || exit 1
mkdir -p run tests/unit
python3 tools/unit_sigs.py build/civ2-linux32rec > run/unit_sigs.tsv || exit 1
for s in "$@"; do
    n=$(basename "$s" .txt)
    rm -rf run/unitrec-$n
    python3 tools/unit_coverage.py --have $n > run/unit_have.tsv
    CIV2_UNITREC_HAVE=/work/run/unit_have.tsv CIV2_UNITREC_SIGS=/work/run/unit_sigs.tsv CIV2_UNITREC_TEXTMASK=/work/tests/unit/textmask.tsv CIV2_UNITREC_OUT=/work/run/unitrec-$n.raw.gz EXE=civ2-linux32rec \
        TIMEOUT=${TIMEOUT:-1200} sh tools/native-run.sh /work/$s /work/run/unitrec-$n > run/unitrec-$n.log 2>&1
    python3 -c "
import glob
from PIL import Image
for f in glob.glob('/work/run/unitrec-$n/*.bmp'):
    Image.open(f).save(f[:-4] + '.png')
"
    if python3 harness/compare.py run/ref-$n run/unitrec-$n > run/unitrec-$n.compare.txt; then
        echo "$n: the recording run matches the original ($(tail -1 run/unitrec-$n.compare.txt))"
    else
        echo "$n: the recording run differs from the original: not kept"; grep -v ": identical" run/unitrec-$n.compare.txt | head
        continue
    fi
    # three times, each in a process of its own (addresses differ from one
    # to the next): what a case does must not depend on them
    (cd build && ./civ2-unittest --mask ../tests/unit/textmask.tsv --bless ../run/unitrec-$n.1.gz ../run/unitrec-$n.raw.gz >/dev/null &&
     ./civ2-unittest --mask ../tests/unit/textmask.tsv --bless ../run/unitrec-$n.2.gz ../run/unitrec-$n.1.gz >/dev/null &&
     ./civ2-unittest --mask ../tests/unit/textmask.tsv --bless ../tests/unit/$n.gz ../run/unitrec-$n.2.gz) | sed "s/^/$n: /"
    rm -f run/unitrec-$n.1.gz run/unitrec-$n.2.gz
done
