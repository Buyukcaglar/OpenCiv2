#!/usr/bin/env python3
"""Step 6 (gotos): compare each function's control-flow graph in two builds
of the same source file, regardless of how the blocks are laid out.

    cfg_compare.py [--map re/methods.tsv] BASE.o NEW.o [FUNCTION]

Both objects are compiled at -O2 (tools/cfg_one.sh), where gcc normalizes the
control flow: a loop written with a label and a backward goto and the same
loop written with while () usually give the same graph, only laid out
differently.  The two functions are walked side by side from their entry:
instructions must match one for one (normalized as tools/cxx_compare.py does:
addresses, section offsets, stack slots), an unconditional jump or a fall
through is followed, and at a conditional jump both successors are paired,
the condition allowed to be inverted with its successors swapped.  Every
address of one function must pair with a single address of the other.  So
the check holds when the two functions are the same graph of the same
instructions: the same program.
Lists the functions that differ; with FUNCTION, shows where.  A function that
differs is compared again with register names ignored: "but for register
choice" means the same graph and instructions with other registers (worth a
look by hand, usually allocation after a reordering).
"""
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import cxx_compare as cc  # noqa: E402

FUNC = re.compile(r'^([0-9a-f]+) <(.+)>:$')
INSN = re.compile(r'^\s*([0-9a-f]+):\s*(.*)$')
INVERT = {'je': 'jne', 'jne': 'je', 'jl': 'jge', 'jge': 'jl', 'jle': 'jg', 'jg': 'jle',
          'jb': 'jae', 'jae': 'jb', 'jbe': 'ja', 'ja': 'jbe', 'js': 'jns', 'jns': 'js',
          'jo': 'jno', 'jno': 'jo', 'jp': 'jnp', 'jnp': 'jp'}
ALIAS = {'jz': 'je', 'jnz': 'jne', 'jnae': 'jb', 'jc': 'jb', 'jnb': 'jae', 'jnc': 'jae',
         'jna': 'jbe', 'jnbe': 'ja', 'jnge': 'jl', 'jnl': 'jge', 'jng': 'jle', 'jnle': 'jg',
         'jpe': 'jp', 'jpo': 'jnp'}


def functions(obj):
    """name -> (list of (addr, text), {addr: index})"""
    out = subprocess.run(['objdump', '-d', '-r', '-C', '--no-show-raw-insn', obj],
                         capture_output=True, text=True).stdout
    funcs, cur = {}, None
    for line in out.split('\n'):
        m = FUNC.match(line)
        if m:
            cur = cc.strip_params(m.group(2))
            funcs[cur] = [] if cur not in funcs else None
            continue
        if cur is None or funcs.get(cur) is None:
            continue
        m = INSN.match(line)
        if not m:
            continue
        addr, text = int(m.group(1), 16), re.sub(r'\s+', ' ', m.group(2).strip())
        if text.startswith('R_'):
            if funcs[cur]:
                a, t = funcs[cur][-1]
                rel = re.sub(r'(R_\w+)\s+(.*)', lambda r: r.group(1) + ' ' + cc.strip_params(r.group(2)), text)
                funcs[cur][-1] = (a, t + ' @' + rel)
            continue
        funcs[cur].append((addr, text))
    res = {}
    for k, v in funcs.items():
        if v is None:
            continue
        while v and re.match(r'(nop\w*|xchg %ax,%ax|lea 0x0\(%e[a-z]+(,%eiz,1)?\),%e[a-z]+)\b', v[-1][1]):
            v = v[:-1]
        res[k] = (v, {a: i for i, (a, _) in enumerate(v)})
    return res


def target(text):
    if '@R_' in text:
        return None         # a tail call
    m = re.match(r'(j\w+) ([0-9a-f]+) <', text)
    return (m.group(1), int(m.group(2), 16)) if m else None


LOOSE = False       # --regs: register names ignored


class Walk:
    def __init__(self, fn):
        self.insns, self.index = fn
        self.slots = {}

    def norm(self, text):
        text = cc.normalize(text)
        if LOOSE:
            text = re.sub(r'%(e?[abcd]x|[abcd][lh]|e?[sd]i|[sd]il|ebp)\b', '%r', text)

        def slot(m):
            k = m.group(1) or '0'
            if k not in self.slots:
                self.slots[k] = 's%d' % len(self.slots)
            return '[%s]' % self.slots[k]
        return re.sub(r'(?:(-?0x[0-9a-f]+))?\(%esp\)', slot, text)


def compare(fa, fb):
    """None when the graphs match, else a description of the first mismatch."""
    wa, wb = Walk(fa), Walk(fb)
    if not wa.insns or not wb.insns:
        return None if len(wa.insns) == len(wb.insns) else 'empty'
    pair = {}           # index in a -> index in b (instruction starts paired)
    back = {}
    work = [(0, 0)]
    while work:
        ia, ib = work.pop()
        while True:
            # follow unconditional jumps (no instruction of their own)
            seen = 0
            while 0 <= ia < len(wa.insns) and seen < 50:
                if wa.insns[ia][1].startswith('jmp ') and target(wa.insns[ia][1]):
                    ia = wa.index.get(target(wa.insns[ia][1])[1], -1)
                elif wa.insns[ia][1] == 'nop':
                    ia += 1
                else:
                    break
                seen += 1
            seen = 0
            while 0 <= ib < len(wb.insns) and seen < 50:
                if wb.insns[ib][1].startswith('jmp ') and target(wb.insns[ib][1]):
                    ib = wb.index.get(target(wb.insns[ib][1])[1], -1)
                elif wb.insns[ib][1] == 'nop':
                    ib += 1
                else:
                    break
                seen += 1
            if ia < 0 or ib < 0:
                return 'jump outside the function'
            if ia in pair or ib in back:
                if pair.get(ia) != ib or back.get(ib) != ia:
                    return 'join differs at %x / %x' % (wa.insns[ia][0] if ia < len(wa.insns) else -1,
                                                         wb.insns[ib][0] if ib < len(wb.insns) else -1)
                break
            if ia >= len(wa.insns) or ib >= len(wb.insns):
                if ia >= len(wa.insns) and ib >= len(wb.insns):
                    break
                return 'falls off the end'
            pair[ia], back[ib] = ib, ia
            ta, tb = wa.insns[ia][1], wb.insns[ib][1]
            ja, jb = target(ta), target(tb)
            if ja and jb and ja[0] != 'jmp' and jb[0] != 'jmp':
                ca, cb = ALIAS.get(ja[0], ja[0]), ALIAS.get(jb[0], jb[0])
                sa, sb = wa.index.get(ja[1], -1), wb.index.get(jb[1], -1)
                if ca == cb:
                    work.append((sa, sb))
                    ia, ib = ia + 1, ib + 1
                elif INVERT.get(ca) == cb:
                    work.append((sa, ib + 1))
                    ia, ib = ia + 1, sb
                else:
                    return 'condition %s / %s at %x / %x' % (ta, tb, wa.insns[ia][0], wb.insns[ib][0])
                continue
            if bool(ja) != bool(jb) or wa.norm(ta) != wb.norm(tb):
                return 'instruction at %x / %x: %s | %s' % (wa.insns[ia][0], wb.insns[ib][0], ta, tb)
            if re.match(r'(ret|jmp|ud2)', ta):
                break
            ia, ib = ia + 1, ib + 1
    return None


def main():
    args = sys.argv[1:]
    if args[:1] == ['--map']:
        cc.load_map(args[1])
        args = args[2:]
    if len(args) < 2:
        print(__doc__)
        return 1
    a, b = functions(args[0]), functions(args[1])
    only = args[2] if len(args) > 2 else None
    same = differ = 0
    regs = []
    for name in sorted(a):
        if name not in b or (only and name != only):
            continue
        why = compare(a[name], b[name])
        if why is not None:
            global LOOSE
            LOOSE = True
            if compare(a[name], b[name]) is None:
                why = 'same graph and instructions but for register choice (%s)' % why
                regs.append(name)
            LOOSE = False
        if why is None:
            same += 1
        else:
            differ += 1
            print('%s\t%s' % (name, why))
    missing = sorted(set(a) ^ set(b))
    for name in missing:
        print('%s\tonly in %s' % (name, 'base' if name in a else 'new'))
    print('%d functions the same graph, %d differ (%d of them only by register choice)'
          % (same, differ, len(regs)), file=sys.stderr)
    return 0


if __name__ == '__main__':
    sys.exit(main())
