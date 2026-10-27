#!/usr/bin/env python3
"""Step 6: group the game's state into records without moving a byte.

    state_records.py SPEC [--check] [RECORD ...]

SPEC (re/state_records.txt) lists records:

    record TYPE instance  comment
        old_name      new_member
        BLOCK.member  new_member
    end

A record is a run of variables that lie together in the original's data
and describe one thing.  Loose globals (`extern int mapgen_age;`) become one
struct with a single instance defined where the first one was (gamedata.cpp:
one GAMEDATA definition, the old initializers in order); members of a
contiguity block (`tax_rate_icon_sprites_block.diplo_ai_fear_level`) become a
nested struct member of that block, named by a constexpr reference
(`inline constexpr DiploEval &diplo_eval = block.diplo_eval;`: the same constant
address).  Either way every member keeps its address: gamedata.cpp gets a
static_assert per member offset (from the address comments), the layout
check keeps checking the instance, and the `_rest` gaps after a member stay
as `<member>_rest`.

Uses are rewritten in src/{auto,game,native,data,include}: `old_name` (not
after `.`, `->` or an identifier character) -> `instance.member`,
`BLOCK.member` -> `instance.member`.  Refuses when the old name is also a
member of some struct or class (a bare use inside a method would then mean
the member) or when the new type or instance name is already an identifier
in the sources.  --check: report only.

It edits the single src/data/gamedata.h it was written for: the
declarations have since been split by subject (tools/state_split.py), so to
add records, put the declarations back together first (or extend HDR to the
headers of src/data/state/).
"""
import glob
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
HDR = os.path.join(ROOT, 'src', 'data', 'gamedata.h')
CPP = os.path.join(ROOT, 'src', 'data', 'gamedata.cpp')
ASSERT_MARK = '/* Records (re/state_records.txt): each member where the original has it. */'


def sources():
    out = []
    for d in ('auto', 'game', 'native', 'data', 'include'):
        out += glob.glob(os.path.join(ROOT, 'src', d, '*.cpp')) + glob.glob(os.path.join(ROOT, 'src', d, '*.h'))
    return sorted(out)


def parse_spec(path):
    recs, cur = [], None
    for raw in open(path):
        line = raw.rstrip('\n')
        if not line.strip() or line.lstrip().startswith('#'):
            continue
        if line.startswith('record '):
            parts = line.split(None, 3)
            cur = {'type': parts[1], 'inst': parts[2], 'comment': parts[3] if len(parts) > 3 else '', 'fields': []}
            recs.append(cur)
        elif line.strip() == 'end':
            cur = None
        else:
            old, new = line.split()
            cur['fields'].append((old, new))
    return recs


DECL = re.compile(r'^(\s*)(?:extern )?(.*?)\b(\w+)((?:\[\d+\])*);(.*)$')


def rename_decl(line, new, indent='    '):
    """`extern int foo[3];  ...` -> `    int new[3];` (+ the address comment)"""
    m = DECL.match(line)
    if not m:
        raise SystemExit('cannot parse declaration: ' + line)
    typ, dims, rest = m.group(2), m.group(4), m.group(5)
    return '%s%s%s%s;%s' % (indent, typ, new, dims, rest), m.group(3)


def find_block(h, i):
    """The block struct around header line i: (start line of `struct X {`, tag)."""
    depth = 0
    for j in range(i, -1, -1):
        s = h[j]
        depth += s.count('}') - s.count('{')
        if depth < 0:
            m = re.match(r'(?:typedef )?struct (\w+) \{', s)
            if m:
                return j, m.group(1)
            depth = 0 if s.strip() in ('union {', 'struct {') else depth
    raise SystemExit('no block around line %d' % i)


def block_instance(h, tag):
    for s in h:
        m = re.match(r'extern (?:struct )?%s (\w+);' % re.escape(tag), s)
        if m:
            return m.group(1)
    return None         # a record's struct, not a block


def block_addr(cpp, inst):
    for s in cpp:
        m = re.match(r'GAMEDATA\(\d+\) .*?\b%s\s*[\[=;].*/\* ([0-9a-f]{8}) \*/$' % re.escape(inst), s)
        if m:
            return int(m.group(1), 16)
    raise SystemExit('no definition of ' + inst)


def addr_of(line):
    m = re.search(r'/\* ([0-9a-f]{8})', line)
    return int(m.group(1), 16) if m else None


def cpp_addr(cpp, name):
    for s in cpp:
        m = re.match(r'GAMEDATA\(\d+\) [^=;\[]*?\b(\w+)\s*[\[=;].*/\* ([0-9a-f]{8}) \*/$', s)
        if m and m.group(1) == name:
            return int(m.group(2), 16)
    return None


def size_of_decl(typ_dims):
    return None


def code_only(t):
    """The text without comments and string or character literals."""
    return re.sub(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'', ' ', t, flags=re.S)


def all_text():
    return {f: code_only(open(f).read()) for f in sources()}


TOKENS = {}
MEMBERS = set()


def index(texts):
    for f, t in texts.items():
        TOKENS[f] = set(re.findall(r'[A-Za-z_]\w*', t))
        MEMBERS.update(re.findall(r'(?:\.|->)\s*([A-Za-z_]\w*)', t))
        if f.endswith('.h') and f != HDR:
            MEMBERS.update(re.findall(r'^\s+[\w ]+?[\s*]+(\w+)(?:\[\w*\])*;', t, re.M))


def collisions(texts, rec, olds):
    if not TOKENS:
        index(texts)
    probs = []
    for name in (rec['type'], rec['inst']):
        for f in TOKENS:
            if name in TOKENS[f]:
                probs.append('%s already used in %s' % (name, os.path.relpath(f, ROOT)))
                break
    for old in olds:
        if '.' not in old and old in MEMBERS:
            probs.append('%s is also a member name' % old)
    return probs


def apply(rec, h, cpp, texts, check):
    fields = rec['fields']
    olds = [o for o, _ in fields]
    inblock = '.' in olds[0]
    for o, n in fields:
        if o == n:
            raise SystemExit('%s: %s keeps its name' % (rec['inst'], o))
    if any(('.' in o) != inblock for o in olds):
        raise SystemExit('%s: mixes loose globals and block members' % rec['inst'])
    probs = collisions(texts, rec, olds)
    if probs:
        print('%s: %s' % (rec['inst'], '; '.join(probs)))
        return None
    # locate the header lines
    idx = []
    blockinst = None
    for old, new in fields:
        if inblock:
            b, mname = old.split('.')
            blockinst = blockinst or b
            if b != blockinst:
                raise SystemExit('%s: members of two blocks' % rec['inst'])
            hits = [i for i, s in enumerate(h) if re.match(r'\s+.*\b%s(\[\d+\])*;' % re.escape(mname), s)]
            hits = [i for i in hits if block_instance(h, find_block(h, i)[1]) == b]
        else:
            mname = old
            hits = [i for i, s in enumerate(h) if re.match(r'extern .*\b%s(\[\d+\])*;' % re.escape(old), s)]
        if len(hits) != 1:
            raise SystemExit('%s: %d declarations of %s' % (rec['inst'], len(hits), old))
        idx.append(hits[0])
    # the run: each field, then its _rest gap if any; nothing else between
    plan = []           # (line index, new name, old name)
    i = idx[0]
    for k, (old, new) in enumerate(fields):
        if idx[k] != i:
            raise SystemExit('%s: %s is not right after the previous field (line %d, expected %d: %s)'
                             % (rec['inst'], old, idx[k] + 1, i + 1, h[i].strip()))
        mname = old.split('.')[-1]
        plan.append((i, new, mname))
        i += 1
        if re.match(r'\s*(extern )?u8 %s_rest\[\d+\];' % re.escape(mname), h[i]):
            plan.append((i, new + '_rest', mname + '_rest'))
            i += 1
    first, last = plan[0][0], plan[-1][0]
    # addresses
    if inblock:
        btag = find_block(h, first)[1]
        base_inst = block_addr(cpp, blockinst)
    addrs = {}
    for li, new, old in plan:
        if old.endswith('_rest') and new.endswith('_rest'):
            continue
        a = addr_of(h[li]) if inblock else cpp_addr(cpp, old)
        if a is None:
            raise SystemExit('%s: no address for %s' % (rec['inst'], old))
        addrs[new] = a
    start = addrs[plan[0][1]]
    # the struct
    body = []
    for li, new, old in plan:
        s, _ = rename_decl(h[li], new)
        if not inblock and not new.endswith('_rest'):
            decl, _, note = s.partition(';')
            note = note.strip()
            note = note[2:-2].strip() if note.startswith('/*') and note.endswith('*/') else note
            s = '%s;  /* %08x%s */' % (decl, addrs[new], ' ' + note if note else '')
        body.append(s)
    T, I = rec['type'], rec['inst']
    sdef = []
    if rec['comment']:
        sdef.append('/* %s */' % rec['comment'])
    sdef += ['#pragma pack(push, 1)', 'typedef struct %s {' % T] + body + ['} %s;' % T, '#pragma pack(pop)']
    asserts = ['static_assert(offsetof(%s, %s) == 0x%x, "%s.%s");' % (T, n, a - start, I, n)
               for n, a in addrs.items()]
    if inblock:
        asserts.insert(0, 'static_assert(offsetof(struct %s, %s) == 0x%x, "%s");' % (btag, I, start - base_inst, I))
    if check:
        print('\n'.join(sdef))
        print('\n'.join(asserts))
        return None
    # header edits
    indent = re.match(r'\s*', h[first]).group(0)
    if inblock:
        bstart = find_block(h, first)[0]
        while bstart > 0 and h[bstart - 1].startswith(('#pragma pack(push', '/*', ' *')):
            bstart -= 1
        member = '%s%s %s;  /* %08x */' % (indent, T, I, start)
        h[first:last + 1] = [member]
        ext = [k for k, s in enumerate(h) if re.match(r'extern (?:struct )?%s %s;' % (re.escape(btag), re.escape(blockinst)), s)][0]
        h.insert(ext + 1, 'inline constexpr %s &%s = %s.%s;' % (T, I, blockinst, I))
        h[bstart:bstart] = sdef
    else:
        h[first:last + 1] = sdef + ['extern %s %s;' % (T, I)]
        # gamedata.cpp: the definitions -> one
        ci = []
        for li, new, old in plan:
            k = [j for j, s in enumerate(cpp) if re.match(r'GAMEDATA\(\d+\) [^=;\[]*?\b%s\s*[\[=;]' % re.escape(old), s)]
            if len(k) != 1:
                raise SystemExit('%s: %d definitions of %s' % (I, len(k), old))
            ci.append(k[0])
        if ci != list(range(ci[0], ci[0] + len(ci))):
            raise SystemExit('%s: definitions not consecutive' % I)
        inits = []
        for j in ci:
            m = re.match(r'GAMEDATA\((\d+)\) .*? = (.*);  /\*.*\*/$', cpp[j])
            if not m:
                raise SystemExit('cannot parse definition: ' + cpp[j])
            inits.append(m.group(2))
        align = re.match(r'GAMEDATA\((\d+)\)', cpp[ci[0]]).group(1)
        if all(x == '{0}' for x in inits):
            init = '{0}'
        else:
            init = '{' + ', '.join(inits) + '}'
        cpp[ci[0]:ci[-1] + 1] = ['GAMEDATA(%s) %s %s = %s;  /* %08x */' % (align, T, I, init, start)]
    # asserts
    if ASSERT_MARK not in cpp:
        k = [j for j, s in enumerate(cpp) if s.startswith('void gamedata_init(void)')][0]
        cpp[k:k] = [ASSERT_MARK, '']
    k = cpp.index(ASSERT_MARK) + 1
    while cpp[k].startswith('static_assert'):
        k += 1
    cpp[k:k] = asserts
    # uses
    subs = []
    for li, new, old in plan:
        if inblock:
            subs.append((re.compile(r'\b%s\s*\.\s*%s\b' % (re.escape(blockinst), re.escape(old))), '%s.%s' % (I, new)))
        else:
            subs.append((re.compile(r'(?<![\w.>])%s\b' % re.escape(old)), '%s.%s' % (I, new)))
    return subs


def main():
    args = [a for a in sys.argv[1:] if not a.startswith('--')]
    check = '--check' in sys.argv
    recs = parse_spec(args[0])
    only = set(args[1:])
    texts = all_text()
    h = open(HDR).read().split('\n')
    cpp = open(CPP).read().split('\n')
    allsubs = []
    done = []
    for rec in recs:
        if only and rec['inst'] not in only:
            continue
        # already applied?
        if any(re.match(r'(typedef struct|extern) %s\b' % rec['type'], s) for s in h):
            continue
        subs = apply(rec, h, cpp, texts, check)
        if subs:
            allsubs += subs
            done.append(rec['inst'])
    if check or not done:
        print('nothing applied' if not done else '')
        return
    open(HDR, 'w').write('\n'.join(h))
    open(CPP, 'w').write('\n'.join(cpp))
    newtypes = set(r['type'] for r in recs)
    for f in sources():
        t = open(f).read()
        out, inside = [], False
        for line in t.split('\n'):
            m = re.match(r'typedef struct (\w+) \{', line)
            if m and m.group(1) in newtypes:
                inside = True
            if not inside and not line.startswith('static_assert(offsetof('):
                for pat, rep in allsubs:
                    line = pat.sub(rep, line)
            if inside and re.match(r'\} \w+;', line):
                inside = False
            out.append(line)
        n = '\n'.join(out)
        if n != t:
            open(f, 'w').write(n)
    print('applied: ' + ' '.join(done))


if __name__ == '__main__':
    main()
