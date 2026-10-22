#!/usr/bin/env python3
"""Find reconstructed functions that break a harness scenario.

Runs inside the civ2-dev container after a full tools/build_recon.py.  The
candidate set is every function the last build can enable, minus those
already listed in re/bad.tsv.  Repeatedly binary-searches for the shortest
address-ordered prefix of candidates whose enabling makes the scenario fail;
the last function of that prefix is a culprit.  Each culprit is appended to
re/bad.tsv and excluded, until the full set passes.

Failure criteria:
    --crash          the game raised an exception / exited during the script
    --ref DIR        screenshots or rand trace differ from a reference run

Usage: bisect.py --script harness/scripts/boot.txt --crash [--max N]
"""
import argparse
import json
import os
import shutil
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BAD = os.path.join(ROOT, 're', 'bad.tsv')


def load_bad():
    if not os.path.exists(BAD):
        return {}
    out = {}
    for line in open(BAD):
        if line.strip() and not line.startswith('#'):
            a, _, why = line.rstrip('\n').partition('\t')
            out[int(a, 16)] = why
    return out


def candidates():
    st = json.load(open(os.path.join(ROOT, 'build', 'recon', 'state.json')))
    import csv
    addrs = {r['name']: int(r['entry'], 16) for r in csv.DictReader(open(os.path.join(ROOT, 're', 'functions.tsv')), delimiter='\t')}
    return sorted(addrs[n] for n in st['impls'] if n in addrs)


def run_test(enabled, args, tag):
    stem = os.path.splitext(os.path.basename(args.script))[0]
    sel = os.path.join(ROOT, 'build', 'recon', 'bisect_only_%s.txt' % stem)
    with open(sel, 'w') as f:
        f.write('\n'.join('%08x' % a for a in enabled) + '\n')
    subprocess.run([sys.executable, os.path.join(ROOT, 'tools', 'build_recon.py'), '--patch-only',
                    '--only-file', sel, '--out', os.path.join(ROOT, 'build', 'civ2_bisect_%s.exe' % stem)],
                   check=True, capture_output=True)
    out = os.path.join(ROOT, 'run', 'bisect', stem, tag)
    shutil.rmtree(out, ignore_errors=True)
    r = subprocess.run([sys.executable, os.path.join(ROOT, 'harness', 'run.py'), '--build', 'recon',
                        '--recon-exe', os.path.join(ROOT, 'build', 'civ2_bisect_%s.exe' % stem),
                        '--seed', str(args.seed), '--script', args.script, '--out', out],
                       capture_output=True, text=True, timeout=args.timeout)
    failed = False
    if 'game exited' in r.stdout:
        print('  (harness: %s)' % r.stdout.strip().splitlines()[-1])
    log = open(os.path.join(out, 'hook.log')).read() if os.path.exists(os.path.join(out, 'hook.log')) else ''
    if args.crash:
        if 'EXCEPTION' in log or 'game exited' in r.stdout:
            failed = True
    if args.ref and not failed:
        c = subprocess.run([sys.executable, os.path.join(ROOT, 'harness', 'compare.py'), args.ref, out],
                           capture_output=True, text=True)
        failed = c.returncode != 0
    print('  test %-12s %5d enabled -> %s' % (tag, len(enabled), 'FAIL' if failed else 'ok'), flush=True)
    return failed


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--script', required=True)
    ap.add_argument('--seed', default=7)
    ap.add_argument('--crash', action='store_true')
    ap.add_argument('--ref')
    ap.add_argument('--max', type=int, default=50, help='stop after this many culprits')
    ap.add_argument('--timeout', type=int, default=600)
    args = ap.parse_args()

    for round_ in range(args.max):
        bad = load_bad()
        cands = [a for a in candidates() if a not in bad]
        if not run_test(cands, args, 'all'):
            print('all %d candidates pass' % len(cands))
            return
        lo, hi = 0, len(cands)        # invariant: prefix lo passes, prefix hi fails
        while hi - lo > 1:
            mid = (lo + hi) // 2
            if run_test(cands[:mid], args, 'p%d' % mid):
                hi = mid
            else:
                lo = mid
        culprit = cands[hi - 1]
        why = 'crash' if args.crash else 'differs'
        print('culprit: %08x (%s, script %s)' % (culprit, why, os.path.basename(args.script)), flush=True)
        with open(BAD, 'a') as f:
            f.write('%08x\t%s %s\n' % (culprit, why, os.path.basename(args.script)))


if __name__ == '__main__':
    main()
