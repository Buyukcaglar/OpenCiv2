#!/usr/bin/env python3
"""Step 6: name the game's magic numbers with the enumerations and flag
constants of src/include/enums.h.

    name_constants.py [-n] [--log FILE] [--only KIND,...] FILE...

A literal is replaced by an enumerator of the same value where the value it
is compared with, assigned to, switched on, passed as or indexes is known to
be of that kind (the rules below):

  compare   `E == 0x2e`, `E != 9` (and <, <=, >, >= for ordered kinds) where
            E is a kinded expression           -> `E == UNIT_DIPLOMAT`
  assign    `E = 0x2e`                          (E a struct field of the kind)
  switch    `switch (E) { case 0x2e: ... }`     (cases of that switch only)
  call      `civ_has_advance(civ, 0x27)`        (CALLS: function, argument)
  index     `game.wonder_city[3]`               (INDEX: the array)
  flags     `E & 0x2000`, `E | 0x2000`, `E &= 0xdfff` -> `E & UNITF_VETERAN`,
            `E &= ~UNITF_VETERAN`; several bits `(A | B)` when every bit has a
            name, else the number stays.

Kinded expressions (classify()): struct fields (`units[i].type`,
`p->type` with `Unit *p`, `civs[c].government`, `game.difficulty` ...),
calls returning a kind (`tile_terrain(x, y)`), locals named for the kind
(`unit_type2`), and locals of a function assigned only from expressions of
one kind (`t = units[u].type; ... if (t == 0x2f)`).

An enumerator compares, converts and promotes exactly as the literal did
when the enum's underlying type promotes to the literal's type: int (the
8/16-bit kinds promote to int, the 32-bit flag words are i32 enums), so the
machine code is the same: tools/cxx_compare.py checks it.  Unsigned literals
(`0x8000U`) stay; a complement mask (`& 0xffbf` -> `& ~X`) is written only
on the field itself, whose width bounds the value.
Strings and comments are left alone.  -n: report only.
"""
import re
import sys
from collections import defaultdict, Counter

ENUMS_H = 'src/include/enums.h'

# kind -> enum type in enums.h
KIND_ENUM = {
    'unit': 'UnitTypeId', 'imp': 'ImprovementId', 'wonder': 'WonderId',
    'adv': 'AdvanceId', 'gov': 'GovernmentId', 'terrain': 'TerrainId',
    'order': 'UnitOrder', 'role': 'UnitRole', 'domain': 'UnitDomain',
    'diff': 'Difficulty', 'nm': 'NetMsgType', 'build': None,
    # flag words
    'utype_f': 'UnitTypeFlag', 'unit_f': 'UnitFlag', 'city_f': 'CityFlag',
    'civ_f': 'CivFlag', 'treaty': 'TreatyFlag', 'tile': 'TileFlag',
    'terrain_b': 'TerrainBits', 'rules_f': 'GameRuleFlag',
    'gameopt': 'GameOption', 'gameflag': 'GameFlag', 'ship_f': 'SpaceshipFlag',
    'menu': 'MenuCommand', 'sound': 'SoundId',
    'transient': 'TransientFlag', 'hint': 'ShownHint', 'msgopt': 'MessageOption',
}
FLAG_KINDS = {'utype_f', 'unit_f', 'city_f', 'civ_f', 'treaty', 'tile', 'terrain_b',
              'rules_f', 'gameopt', 'gameflag', 'ship_f', 'transient', 'hint', 'msgopt'}
# kinds compared with <, <=, >, >= as well (an order is meaningful)
ORDERED = {'gov', 'diff'}

# --- what is of which kind -------------------------------------------------

# Normalized operand (subscripts emptied, `var->` replaced by `Type->` for
# typed locals/parameters, leading casts dropped) -> kind.
FIELDS = [
    (r'^units\[\]\.type$|^Unit->type$', 'unit'),
    (r'^cities\[\]\.building$|^City->building$', 'build'),    # unit type, or -improvement
    (r'^units\[\]\.orders$|^Unit->orders$', 'order'),
    (r'^(unit_types\[\]|UnitType->|unit_types->)\.?role$|^unit_types\[\]\.role$', 'role'),
    (r'\.ai_goals\[\]\.role$|\.ai_standing_goals\[\]\.role$|^CivGoal->role$', 'role'),
    (r'^unit_types\[\]\.domain$|^UnitType->domain$', 'domain'),
    (r'^civs\[\]\.government$|^Civ->government$', 'gov'),
    (r'^game\.difficulty$', 'diff'),
    (r'^tile_terrain\(\)$', 'terrain'),
    (r'^unit_types\[\]\.flags$|^UnitType->flags$', 'utype_f'),
    (r'^units\[\]\.flags$|^Unit->flags$', 'unit_f'),
    (r'^cities\[\]\.flags$|^City->flags$', 'city_f'),
    (r'^civs\[\]\.flags$|^Civ->flags$', 'civ_f'),
    (r'^civs\[\]\.treaties\[\]$|^Civ->treaties\[\]$', 'treaty'),
    (r'^tile_improvements\(\)$|^Tile->improvements$', 'tile'),
    (r'^Tile->terrain$', 'terrain_b'),
    (r'^game\.rules$', 'rules_f'),
    (r'^game\.game_options$', 'gameopt'),
    (r'^game\.game_flags$', 'gameflag'),
    (r'^game\.transient_flags$', 'transient'),
    (r'^game\.shown_event_flags$', 'hint'),
    (r'^game\.message_options$', 'msgopt'),
    (r'^civs\[\]\.spaceship_flags$|^Civ->spaceship_flags$', 'ship_f'),
    (r'^(NetMsgHeader->|NetMsg->)msg_type$|(->|\.)hdr\.msg_type$', 'nm'),
]
FIELDS = [(re.compile(p), k) for p, k in FIELDS]

# locals and parameters named for their kind
NAMES = [
    (r'^unit_type\d*$', 'unit'),
    (r'^(govt|government)\d*$', 'gov'),
    (r'^advance(_id)?\d*$', 'adv'),
    (r'^wonder\d*$', 'wonder'),
    (r'^improvement(_id)?\d*$', 'imp'),
    (r'^msg_type$', 'nm'),
    (r'^terrain\d*$', 'terrain'),
]
NAMES = [(re.compile(p), k) for p, k in NAMES]

# (function, local) -> kind: a local of a generic name in given functions
FUNC_LOCALS = [
    (r'^(menu_command|menu_cmd_\w+)$', 'cmd', 'menu'),
    (r'^dispatch_message$', 'msg[]', 'nm'),        # NetSession::dispatch_message
    (r'^draw_list_terrain_icon$', 'advance', 'terrain'),   # a terrain/resource row
]
FUNC_LOCALS = [(re.compile(f), v, k) for f, v, k in FUNC_LOCALS]

# function -> {argument index: kind}
CALLS = {
    'civ_has_advance': {1: 'adv'},
    'city_has_improvement': {1: 'imp'},
    'civ_has_wonder': {1: 'wonder'},
    'net_send_message': {0: 'nm'},
    'net_msg_build_packet': {0: 'nm'},
    'net_msg_is_priority': {0: 'nm'},
    'menu_set_item_label': {0: 'menu'},
    'snd_play_effect': {0: 'sound'},
    'set_item_enabled': {0: 'menu'},
    'set_item_checked': {0: 'menu'},
}

# ... and every function whose parameter is named for a kind (protos.h and
# the class declarations; names declared once only)
PARAMS = {'unit_type': 'unit', 'advance': 'adv', 'advance_id': 'adv', 'prereq': 'adv',
          'improvement': 'imp', 'improvement_id': 'imp', 'wonder': 'wonder',
          'government': 'gov', 'role': 'role', 'wanted_role': 'role', 'order': 'order',
          'msg_type': 'nm'}
PARAMS_EXCEPT = {('unit_pillage', 1),      # a tile improvement bit
                 ('draw_list_terrain_icon', 0), ('copy_list_item_name', 0),  # any Civilopedia list
                 ('show_topic_modal', 0)}


def load_calls():
    seen = Counter()
    found = {}
    for path in ('src/auto/protos.h', 'src/include/civ2classes.h'):
        for m in re.finditer(r'\b(\w+)\s*\(([^()]*)\)\s*(?:const\s*)?;', strip_comments(open(path).read())):
            name, params = m.groups()
            seen[name] += 1
            for i, prm in enumerate(params.split(',')):
                pm = re.search(r'(\w+)\s*$', prm.strip())
                if pm and pm.group(1) in PARAMS and (name, i) not in PARAMS_EXCEPT:
                    found.setdefault(name, {})[i] = PARAMS[pm.group(1)]
    for name, rule in found.items():
        if name in CALLS:
            continue
        if seen[name] == 1 or name in ('tile_terrain',):
            CALLS[name] = rule

# array (the text before `[`) -> kind of its index
INDEX = [
    (r'(?<![\w.>])game\.(advance_known_by|first_discoverer)$', 'adv'),
    (r'(?<![\w.>])game\.wonder_city$', 'wonder'),
    (r'(?<![\w.>])unit_types$', 'unit'),
    (r'(?<![\w.>])improvements$', 'imp'),
    (r'(?<![\w.>])advances$', 'adv'),
    (r'\]\.(units_active|units_lost|units_in_production)$', 'unit'),
    (r'\]\.advance_source$', 'adv'),
    (r'\]\.government_score$', 'gov'),
]
INDEX = [(re.compile(p), k) for p, k in INDEX]

# --- enums.h ----------------------------------------------------------------

def load_enums(path=ENUMS_H):
    text = strip_comments(open(path).read())
    enums = {}
    for m in re.finditer(r'enum\s+(\w+)\s*:\s*(\w+)\s*\{(.*?)\}', text, re.S):
        name, _, body = m.groups()
        vals, names = {}, {}
        for e in re.finditer(r'(\w+)\s*=\s*(-?(?:0x[0-9a-fA-F]+|\d+))', body):
            v = int(e.group(2), 0)
            names[e.group(1)] = v
            vals.setdefault(v, e.group(1))
        enums[name] = vals
    return enums


def strip_comments(text):
    return re.sub(r'/\*.*?\*/|//[^\n]*', lambda m: ' ' * len(m.group(0)), text, flags=re.S)


def shadow(text):
    """Comments and string literals blanked (char literals kept: they are
    values), same length, so offsets match the original."""
    def blank(m):
        s = m.group(0)
        if s.startswith("'"):
            return s
        return re.sub(r'[^\n]', ' ', s)
    return re.sub(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'', blank, text, flags=re.S)

# --- literals -----------------------------------------------------------------

LIT = r"(?:-\s*)?(?:0x[0-9a-fA-F]+|\d+)(?![\w.])|'(?:\\.|[^'\\])'"
ESC = {'n': 10, 't': 9, 'r': 13, '0': 0, '\\': 92, "'": 39, '"': 34, 'a': 7, 'b': 8, 'f': 12, 'v': 11}


def lit_value(s):
    s = s.strip()
    if s.startswith("'"):
        body = s[1:-1]
        if body.startswith('\\'):
            if body[1] == 'x':
                v = int(body[2:], 16)
            elif body[1] in '01234567' and len(body) > 2:
                v = int(body[1:], 8)
            else:
                v = ESC[body[1]]
        else:
            v = ord(body)
        return v - 256 if v >= 128 else v      # plain char is signed
    neg = s.startswith('-')
    s = s.lstrip('-').strip().rstrip('uU')
    v = int(s, 0)
    return -v if neg else v

# --- operands -----------------------------------------------------------------

IDC = re.compile(r'[\w]')


def match_back(s, i):
    """s[i] is a closing bracket; index of its opening one."""
    close = s[i]
    open_ = {')': '(', ']': '['}[close]
    depth = 0
    while i >= 0:
        c = s[i]
        if c == close:
            depth += 1
        elif c == open_:
            depth -= 1
            if depth == 0:
                return i
        i -= 1
    return -1


def match_fwd(s, i):
    open_ = s[i]
    close = {'(': ')', '[': ']', '{': '}'}[open_]
    depth = 0
    while i < len(s):
        c = s[i]
        if c == open_:
            depth += 1
        elif c == close:
            depth -= 1
            if depth == 0:
                return i
        i += 1
    return -1


def operand_before(s, end):
    """The postfix expression ending at s[end-1] (whitespace skipped):
    (start, end) or None."""
    i = end
    while i > 0 and s[i - 1] in ' \t\n':
        i -= 1
    stop = i
    while i > 0:
        c = s[i - 1]
        if c == ']':
            j = match_back(s, i - 1)
            if j < 0:
                return None
            i = j
            continue
        if c == ')':
            j = match_back(s, i - 1)
            if j < 0:
                return None
            i = j
            k = i
            while k > 0 and IDC.match(s[k - 1]):
                k -= 1
            if k == i:              # a parenthesized expression: the operand
                break
            i = k
        elif IDC.match(c):
            while i > 0 and IDC.match(s[i - 1]):
                i -= 1
            if s[i].isdigit():
                return None
        else:
            return None
        if s[i - 2:i] == '->':
            i -= 2
            continue
        if i > 0 and s[i - 1] == '.':
            i -= 1
            continue
        if i > 0 and s[i - 1] in '])' :
            continue
        break
    if i == stop:
        return None
    return i, stop


def operand_after(s, start):
    """Postfix expression starting at s[start] (casts `(type)` skipped):
    (start, end) or None."""
    i = start
    while i < len(s) and s[i] in ' \t\n':
        i += 1
    b = i
    # casts
    while True:
        m = re.match(r'\(\s*(?:const\s+)?(?:unsigned\s+)?\w+\s*\**\s*\)', s[i:])
        if not m:
            break
        i += m.end()
    m = re.match(r'[A-Za-z_]\w*', s[i:])
    if not m:
        return None
    i += m.end()
    while i < len(s):
        if s[i] in '([':
            j = match_fwd(s, i)
            if j < 0:
                return None
            i = j + 1
        elif s.startswith('->', i) or (s[i] == '.' and not s[i + 1:i + 2].isdigit()):
            i += 2 if s[i] == '-' else 1
            m = re.match(r'[A-Za-z_]\w*', s[i:])
            if not m:
                return None
            i += m.end()
        else:
            break
    return b, i


CAST = re.compile(r'^(\(\s*(?:const\s+)?(?:unsigned\s+)?\w+\s*\**\s*\)\s*)+')


def normalize(expr, ptypes):
    e = CAST.sub('', expr.strip())
    while e.startswith('(') and match_fwd(e, 0) == len(e) - 1:
        e = CAST.sub('', e[1:-1].strip())
    # empty subscripts and call arguments
    out, i = [], 0
    while i < len(e):
        c = e[i]
        if c in '[(':
            j = match_fwd(e, i)
            if j < 0:
                return None
            out.append('[]' if c == '[' else '()')
            i = j + 1
        else:
            out.append(c)
            i += 1
    e = re.sub(r'\s+', '', ''.join(out))
    m = re.match(r'^([A-Za-z_]\w*)->', e)
    if m and m.group(1) in ptypes:
        e = ptypes[m.group(1)] + e[len(m.group(1)):]
    m = re.match(r'^this->', e)
    if m and 'this' in ptypes:
        e = ptypes['this'] + e[4:]
    return e


def classify(expr, fn):
    e = normalize(expr, fn['ptypes'])
    if e is None:
        return None
    for p, k in FIELDS:
        if p.search(e):
            return k
    if e in fn.get('exprs', ()):
        return fn['exprs'][e]
    if re.match(r'^[A-Za-z_]\w*$', e):
        if e in fn['locals']:
            return fn['locals'][e]
        for p, k in NAMES:
            if p.match(e):
                return k
    return None

# --- functions ----------------------------------------------------------------

DECL = re.compile(r'\b(Unit|City|Civ|UnitType|Tile|CivGoal|NetMsgHeader|NetMsg)\s*\*\s*(?:const\s+)?(\w+)\s*[;,)=]')


def functions(sh):
    """(start, end, name) of each top-level function body."""
    out = []
    for m in re.finditer(r'^\{|^[^\s#/*][^\n;]*\)\s*(?:const\s*)?\{\s*$', sh, re.M):
        b = sh.index('{', m.start())
        e = match_fwd(sh, b)
        if e < 0:
            continue
        head = sh[max(0, sh.rfind('\n', 0, m.start() - 1)):b]
        nm = re.findall(r'([\w:~]+)\s*\(', sh[max(0, m.start() - 300):b])
        out.append((m.start(), e + 1, nm[-1] if nm else '?'))
    return out


def func_context(sh, start, end, cls, name=''):
    body = sh[start:end]
    head_start = sh.rfind('\n\n', 0, start)
    head = sh[head_start if head_start >= 0 else 0:start]
    ptypes = {}
    for m in DECL.finditer(head + body):
        ptypes[m.group(2)] = m.group(1)
    if cls:
        ptypes['this'] = cls
    fn = {'ptypes': ptypes, 'locals': {}}
    # locals assigned only from expressions of one kind
    kinds = defaultdict(set)
    for m in re.finditer(r'(?<![\w.>\]])([A-Za-z_]\w*)\s*(?<![=!<>+\-*/%&|^])=(?!=)', body):
        var = m.group(1)
        rhs = operand_after(body, m.end())
        if rhs is None:
            # literal or something we cannot read
            rest = body[m.end():m.end() + 40].lstrip()
            if not re.match(LIT + r'\s*[;,)]', rest):
                kinds[var].add(None)
            continue
        after = body[rhs[1]:rhs[1] + 3].lstrip()
        if after[:1] not in (';', ',', ')'):
            kinds[var].add(None)        # part of a larger expression
            continue
        k = classify(body[rhs[0]:rhs[1]], fn)
        kinds[var].add(k)
    for var, ks in kinds.items():
        if len(ks) == 1 and None not in ks:
            fn['locals'][var] = ks.pop()
    for f, v, k in FUNC_LOCALS:
        if f.match(name.split('::')[-1]):
            if re.match(r'^\w+$', v):
                fn['locals'][v] = k
            else:
                fn.setdefault('exprs', {})[v] = k
    for m in re.finditer(r'(\+\+|--)\s*([A-Za-z_]\w*)|([A-Za-z_]\w*)\s*(\+\+|--|[+\-]=)', body):
        var = m.group(2) or m.group(3)
        if var in fn['locals'] and not any(p.match(var) for p, _ in NAMES):
            del fn['locals'][var]
    return fn

# --- naming values ---------------------------------------------------------------

class Namer:
    def __init__(self, enums):
        self.enums = enums

    def name(self, kind, v, operand_is_field=False, width=None):
        if kind == 'build':
            if v < 0:
                n = self.enums['ImprovementId'].get(-v)
                return '-' + n if n else None
            kind = 'unit'
        vals = self.enums.get(KIND_ENUM[kind])
        if vals is None:
            return None
        if kind not in FLAG_KINDS:
            return vals.get(v)
        if v == 0 or v < 0:
            return None
        if v in vals:
            return vals[v]
        bits = [1 << b for b in range(32) if v >> b & 1]
        if all(b in vals for b in bits) and len(bits) <= 4:
            return '(' + ' | '.join(vals[b] for b in bits) + ')'
        # a complement mask: clear the named bits
        if operand_is_field:
            for w in (8, 16, 32):
                full = (1 << w) - 1
                if v <= full and bin(v).count('1') > w // 2:
                    inv = full & ~v
                    ibits = [1 << b for b in range(32) if inv >> b & 1]
                    if ibits and len(ibits) <= 4 and all(b in vals for b in ibits):
                        if len(ibits) == 1:
                            return '~' + vals[ibits[0]]
                        return '~(' + ' | '.join(vals[b] for b in ibits) + ')'
                    break
        return None

# --- the rewrite --------------------------------------------------------------------

def class_of(name):
    return name.split('::')[0] if '::' in name else None


def rewrite(text, namer, only=None, log=None, fname=''):
    sh = shadow(text)
    edits = {}
    lines = None

    def want(kind):
        return kind and (only is None or kind in only)

    def put(a, b, new, kind, rule, fn_name):
        old = text[a:b]
        if (a, b) in edits:
            return
        edits[(a, b)] = new
        if log is not None:
            ln = text.count('\n', 0, a) + 1
            log.append((fname, ln, fn_name, kind, rule, old.strip(), new))

    def lit_at(s, i):
        m = re.compile(r'\s*(' + LIT + r')').match(s, i)
        if not m or m.group(1)[-1] in 'uU':     # unsigned: an enumerator would be int
            return None
        return m.start(1), m.end(1)

    for fs, fe, fn_name in functions(sh):
        fn = func_context(sh, fs, fe, class_of(fn_name), fn_name)
        body = sh[fs:fe]
        off = fs

        def is_field(expr):
            return bool(re.search(r'\.|->|\[', expr))

        # comparisons: E op LIT
        for m in re.finditer(r'(?<![<>=!\-&|])(==|!=|<=|>=|<(?![<=])|>(?![>=]))', body):
            op = m.group(1)
            if op in ('<', '>') and m.start() > 0 and body[m.start() - 1] == '-':
                continue
            lt = lit_at(body, m.end())
            if lt is None:
                continue
            nxt = body[lt[1]:lt[1] + 3].lstrip()[:2]
            if nxt[:1] not in (')', ',', ';', '?', ':', '&', '|', '') or nxt in ('&=', '|='):
                continue
            od = operand_before(body, m.start())
            if od is None:
                continue
            k = classify(body[od[0]:od[1]], fn)
            if not want(k) or k in FLAG_KINDS:
                continue
            if op not in ('==', '!=') and k not in ORDERED:
                continue
            v = lit_value(body[lt[0]:lt[1]])
            n = namer.name(k, v)
            if n:
                put(off + lt[0], off + lt[1], n, k, 'cmp', fn_name)
        # comparisons: LIT op E
        for m in re.finditer(r'(?<![\w.\'])(' + LIT + r')\s*(==|!=|<=|>=|<(?![<=])|>(?![>=]))', body):
            prev = body[:m.start()].rstrip()[-1:]
            if prev not in ('(', ',', '&', '|', '!', '=', '?', ':', ''):
                continue
            od = operand_after(body, m.end())
            if od is None:
                continue
            after = body[od[1]:od[1] + 3].lstrip()[:1]
            if after not in (')', ',', ';', '?', ':', '&', '|'):
                continue
            k = classify(body[od[0]:od[1]], fn)
            if not want(k) or k in FLAG_KINDS:
                continue
            if m.group(2) not in ('==', '!=') and k not in ORDERED:
                continue
            n = namer.name(k, lit_value(m.group(1)))
            if n:
                put(off + m.start(1), off + m.end(1), n, k, 'cmp', fn_name)
        # assignments: E = LIT (fields only)
        for m in re.finditer(r'(?<![=!<>+\-*/%&|^])=(?!=)', body):
            lt = lit_at(body, m.end())
            if lt is None:
                continue
            nxt = body[lt[1]:lt[1] + 3].lstrip()[:1]
            if nxt not in (';', ',', ')'):
                continue
            od = operand_before(body, m.start())
            if od is None:
                continue
            expr = body[od[0]:od[1]]
            k = classify(expr, fn)
            if not want(k) or k in FLAG_KINDS or not is_field(expr):
                continue
            n = namer.name(k, lit_value(body[lt[0]:lt[1]]))
            if n:
                put(off + lt[0], off + lt[1], n, k, 'assign', fn_name)
        # flags: E & LIT, E | LIT, E &= LIT, E |= LIT, E ^ LIT
        for m in re.finditer(r'(?<![&|])([&|^])(=?)(?![&|])', body):
            lt = lit_at(body, m.end())
            if lt is None:
                continue
            nxt = body[lt[1]:lt[1] + 3].lstrip()[:1]
            if nxt not in (')', ',', ';', '?', ':', '&', '|', '=', '!'):
                continue
            od = operand_before(body, m.start())
            if od is None:
                continue
            # a binary operator, not unary & (address of)
            pre = body[:od[0]].rstrip()[-1:]
            expr = body[od[0]:od[1]]
            k = classify(expr, fn)
            if not want(k) or k not in FLAG_KINDS:
                continue
            v = lit_value(body[lt[0]:lt[1]])
            if m.group(1) != '&' and v > 0 and v.bit_count() > 1 and False:
                continue
            n = namer.name(k, v, operand_is_field=is_field(expr))
            if n and (n.startswith('~') and m.group(1) != '&'):
                n = None
            if n:
                put(off + lt[0], off + lt[1], n, k, 'flag', fn_name)
        # one byte of a flag word: `(byte)(E >> 8) & 0x20`, `*((byte *)&E + 1) & 0x20`
        # -> `& (TREATY_WAR >> 8)` (the same int constant)
        for m in re.finditer(r'\((?:byte|char|u8|i8|ushort|u16)\)\(|\*\(\((?:byte|char|u8|i8) \*\)&', body):
            od = operand_after(body, m.end())
            if od is None:
                continue
            k = classify(body[od[0]:od[1]], fn)
            if not want(k) or k not in FLAG_KINDS:
                continue
            rest = body[od[1]:od[1] + 40]
            if m.group(0).startswith('*'):
                t = re.match(r'\s*\+\s*([1-3])\)\)?\s*&\s*', rest)
                shift = int(t.group(1)) * 8 if t else 0
            else:
                t = re.match(r'\s*>>\s*(8|16|24|0x10|0x18)\s*\)\s*&\s*', rest)
                shift = int(t.group(1), 0) if t else 0
            if not t:
                continue
            a = od[1] + t.end()
            lt = lit_at(body, a)
            if lt is None or lt[0] != a:
                continue
            v = lit_value(body[lt[0]:lt[1]])
            if v <= 0 or v > 0xff:
                continue
            n = namer.name(k, v << shift)
            if n and not n.startswith('~'):
                put(off + lt[0], off + lt[1], '(%s >> %d)' % (n, shift), k, 'flagbyte', fn_name)
        # switch (E) { case LIT: }
        for m in re.finditer(r'\bswitch\s*\(', body):
            p = m.end() - 1
            q = match_fwd(body, p)
            if q < 0:
                continue
            k = classify(body[p + 1:q], fn)
            if not want(k) or k in FLAG_KINDS:
                continue
            b = body.find('{', q)
            e = match_fwd(body, b)
            if b < 0 or e < 0:
                continue
            # skip nested switch bodies
            nested = []
            for n2 in re.finditer(r'\bswitch\s*\(', body[b + 1:e]):
                p2 = b + 1 + n2.end() - 1
                q2 = match_fwd(body, p2)
                b2 = body.find('{', q2)
                e2 = match_fwd(body, b2)
                nested.append((b2, e2))
            for c in re.finditer(r'\bcase\s+(' + LIT + r')\s*:', body[b:e]):
                at = b + c.start(1)
                if any(x <= at <= y for x, y in nested):
                    continue
                n = namer.name(k, lit_value(c.group(1)))
                if n:
                    put(off + at, off + b + c.end(1), n, k, 'case', fn_name)
        # calls
        for m in re.finditer(r'(?<![\w])(\w+)\s*\(', body):
            rule = CALLS.get(m.group(1))
            if not rule:
                continue
            p = m.end() - 1
            q = match_fwd(body, p)
            if q < 0:
                continue
            args, depth, s0 = [], 0, p + 1
            for i in range(p + 1, q):
                c = body[i]
                if c in '([{':
                    depth += 1
                elif c in ')]}':
                    depth -= 1
                elif c == ',' and depth == 0:
                    args.append((s0, i))
                    s0 = i + 1
            args.append((s0, q))
            for idx, k in rule.items():
                if idx >= len(args) or not want(k):
                    continue
                a, b = args[idx]
                txt = body[a:b]
                mm = re.match(r'(\s*(?:\(\s*\w+\s*\)\s*)?)(' + LIT + r')\s*$', txt)
                if not mm:
                    continue
                n = namer.name(k, lit_value(mm.group(2)))
                if n:
                    put(off + a + mm.start(2), off + a + mm.end(2), n, k, 'call', fn_name)
        # array indexes
        for m in re.finditer(r'\[\s*(' + LIT + r')\s*\]', body):
            before = body[max(0, m.start() - 200):m.start()]
            # the array expression ending before `[`
            od = operand_before(body, m.start())
            arr = body[od[0]:od[1]] if od else before[-40:]
            for p, k in INDEX:
                if p.search(arr) and want(k):
                    n = namer.name(k, lit_value(m.group(1)))
                    if n:
                        put(off + m.start(1), off + m.end(1), n, k, 'index', fn_name)
                    break
    out = text
    for (a, b), new in sorted(edits.items(), reverse=True):
        out = out[:a] + new + out[b:]
    return out, len(edits)


def main(argv):
    dry = '-n' in argv
    argv = [a for a in argv if a != '-n']
    logpath, only = None, None
    if '--log' in argv:
        i = argv.index('--log')
        logpath = argv[i + 1]
        del argv[i:i + 2]
    if '--only' in argv:
        i = argv.index('--only')
        only = set(argv[i + 1].split(','))
        del argv[i:i + 2]
    namer = Namer(load_enums())
    load_calls()
    log = []
    total = Counter()
    for path in argv:
        text = open(path).read()
        new, n = rewrite(text, namer, only, log, path)
        total[path] = n
        if not dry and new != text:
            open(path, 'w').write(new)
    if logpath:
        with open(logpath, 'w') as f:
            for r in log:
                f.write('\t'.join(str(x) for x in r) + '\n')
    kinds = Counter(r[3] for r in log)
    print(' '.join('%s:%d' % kv for kv in sorted(kinds.items())), 'total', sum(total.values()))


if __name__ == '__main__':
    main(sys.argv[1:])
