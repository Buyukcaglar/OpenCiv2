#!/usr/bin/env python3
"""Step 6: the game's methods become C++ member functions of their classes.

A method is a free function `T __thiscall name(Class *self, ...)`; it
becomes `T Class::member(...)`, declared in the class, its body using
`this`, and every call `name(obj, ...)` becomes `obj->member(...)`.  Member
functions under g++ -m32 take `this` as the first stack argument, exactly as
the free functions took `self`: the machine code stays the same (checked by
tools/cxx_compare.py --map re/methods.tsv).

    cxx_methods.py plan            # decide the names: re/methods.tsv (done; --force redoes it)
    cxx_methods.py apply GROUP...  # convert the classes of these groups (see GROUPS)
    cxx_methods.py apply --all

Both need the preprocessor's view of the headers (macros, type names), made
in the container:  F="-x c++ -m32 -std=gnu++17 -include native.h -I src/include
-I src/auto -I tools -I build/native/gen -DCIV2_NATIVE -DCIV2_LOWMEM";
g++ -dM -E $F src/include/auto_common.h > run/methods/macros.txt;
g++ -E -P $F src/include/auto_common.h > run/methods/pp.txt
All methods are converted now (2026-10-27); the plan is kept as the map from
the old names (Ghidra's, re/functions.tsv) to the members.

What stays free (the plan says why): methods whose address is taken (stored
in a callback field or table, passed to the platform layer or the array
constructor iterators, called by replay scripts), methods of `void *` or of
a decompiler "view" (a struct one function's accesses describe), methods that
assign `self` or take its address, and ones the platform layer calls.

Names: the class's prefix is dropped (citywin_draw_tile ->
CityWindow::draw_tile); *_ctor/*_dtor become construct/destruct.  A name is
kept whole when dropping the prefix would clash with a member, a macro, a
keyword, a type or another method of the class.  The same name in a base and
a derived class is allowed: calls that could reach the other one are
qualified (obj->Control::construct()).  Inside member bodies, `self->` is
dropped where no local has the member's name, and a reference to a global the
class's members would now hide is written ::name.
"""
import csv
import glob
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PLAN = os.path.join(ROOT, 're', 'methods.tsv')
RUN = os.path.join(ROOT, 'run', 'methods')

# Class -> prefixes of its methods' free names (longest first is tried).
PREFIXES = {
    'WndBase': ['wnd_record_', 'wnd_'],
    'WndHandlers': ['wnd_handlers_', 'wnd_'],
    'ModalMenuWindow': ['wnd_'],
    'Wnd': ['window_', 'wnd_'],
    'SurfaceWindow': ['surfwnd_', 'window_', 'wnd_'],
    'DibSurface': ['surface_'],
    'FrameWindow': ['frame_wnd_', 'wnd_'],
    'Control': ['control_', 'ctrl_'],
    'Button': ['button_', 'ctrl_'],
    'Checkbox': ['checkbox_'],
    'Scrollbar': ['scrollbar_'],
    'EditControl': ['edit_'],
    'ComboBox': ['combo_'],
    'ListBox': ['listbox_'],
    'Hotspot': ['hotspot_'],
    'Hyperlink': ['hyperlink_'],
    'RadioGroup': ['radiogrp_'],
    'SpriteButton': ['spritebtn_'],
    'Dialog': ['dialog_', 'dlg_'],
    'ScenarioEvents': ['events_', 'event_'],
    'GameMenu': ['menu_'],
    'Sprite': ['sprite_'],
    'GamePalette': ['palette_'],
    'GameFont': ['font_'],
    'CityWindow': ['city_window_', 'citywnd_', 'city_'],
    'CityViewWindow': ['cityview_'],
    'MapView': ['mapview_', 'map_view_'],
    'PediaWindow': ['pedia_window_', 'pedia_'],
    'ParleyWindow': ['parley_wnd_', 'parley_'],
    'EditorWindow': ['editor_wnd_'],
    'SpaceshipWindow': ['spaceship_wnd_', 'spaceship_'],
    'DiploLeaderWindow': ['diplo_leader_wnd_', 'diplo_leader_'],
    'ThroneRoomWindow': ['throneroom_'],
    'DestroyedCivsWindow': ['destroyed_civs_wnd_', 'destroyed_civs_'],
    'EndgameMovieWindow': [],
    'CouncilWindow': ['council_wnd_', 'council_'],
    'PortraitDialog': ['portrait_dlg_'],
    'WonderMovieWindow': ['wonder_movie_wnd_'],
    'PictureWindow': ['picwnd_'],
    'SetupPicWindow': ['setup_picwnd_'],
    'TaxRateDialog': ['taxrate_dialog_', 'taxrate_'],
    'SpritePicker': ['sprite_picker_'],
    'AviPlayer': ['avi_player_', 'mmwnd_'],
    'CityPicturePopup': ['city_picture_popup_'],
    'NetSession': ['net_session_', 'net_'],
    'NetMsgQueue': ['net_msgq_'],
    'NetGamelistView': ['net_gamelist_', 'gamelist_'],
    'LobbyList': ['lobby_list_', 'lobby_'],
    'PtrList': ['ptrlist_'],
    'FileObject': ['file_obj_', 'file_'],
    'ErrorContext': ['err_ctx_', 'err_'],
    'TimerManager': ['timer_mgr_'],
    'DllHandle': ['dll_handle_', 'dll_'],
    'DDControl': ['ddctrl_'],
    'DDWindow': ['ddwin_'],
    'ClickMap': ['clickmap_'],
    'MemBlock': ['memblock_'],
    'PediaLink': ['pedia_link_'],
    'AviAudio': ['avi_audio_'],
    'DiffEngSection': ['diffeng_section_'],
    'NetMsgHeader': ['net_msg_'],
    'NetNamedMsg': ['net_msg_'],
}
# Free name -> member name, where the rule gives a poor one.
OVERRIDES = {
    'surfwnd_wnd_ctor': 'construct',
    'net_msg_addr_header_init': 'init',
    'net_msg_server_info_init': 'init',
    'net_msg_server_answer_init': 'init',
    'net_msg_player_list_node_init': 'init',
    'net_msg_player_list_init': 'init',
    'net_msg_player_info_init': 'init',
    'net_msg_whose_turn_init': 'init',
    'net_msg_init_header': 'init_header',
}
# Classes whose name ends in View but are real classes, not one function's view.
REAL_VIEWS = {'NetGamelistView', 'MapView'}

# Batches: groups of classes converted together.
GROUPS = {
    'controls': ['Control', 'Button', 'Checkbox', 'Scrollbar', 'EditControl', 'ComboBox', 'ListBox', 'Hotspot',
                 'Hyperlink', 'RadioGroup', 'SpriteButton', 'ClickMap', 'DDControl', 'DDWindow'],
    'windows': ['WndBase', 'WndHandlers', 'ModalMenuWindow', 'Wnd', 'SurfaceWindow', 'DibSurface', 'FrameWindow',
                'GameMenu', 'Sprite', 'GamePalette', 'GameFont', 'PictureWindow', 'SetupPicWindow', 'SpritePicker',
                'TaxRateDialog', 'CityPicturePopup', 'PortraitDialog'],
    'dialogs': ['Dialog', 'ScenarioEvents'],
    'views': ['CityWindow', 'CityViewWindow', 'MapView', 'ThroneRoomWindow', 'SpaceshipWindow', 'DiploLeaderWindow',
              'DestroyedCivsWindow', 'EndgameMovieWindow', 'WonderMovieWindow', 'CouncilWindow'],
    'editors': ['EditorWindow'],
    'pedia': ['PediaWindow', 'PediaLink'],
    'network': ['ParleyWindow', 'NetSession', 'NetMsgQueue', 'NetGamelistView', 'LobbyList', 'NetMsgHeader',
                'NetNamedMsg', 'NetAddrMsg', 'NetServerInfoMsg', 'NetServerAnswerMsg', 'NetPlayerNodeMsg',
                'NetPlayerListMsg', 'NetPlayerInfoMsg', 'NetWhoseTurnMsg', 'DiffEngSection'],
    'sound': ['AviPlayer', 'AviAudio'],
    'rest': ['PtrList', 'FileObject', 'ErrorContext', 'TimerManager', 'DllHandle', 'MemBlock'],
}

KEYWORDS = set('''alignas alignof and and_eq asm auto bitand bitor bool break case catch char char8_t char16_t
char32_t class compl concept const consteval constexpr constinit const_cast continue co_await co_return co_yield
decltype default delete do double dynamic_cast else enum explicit export extern false float for friend goto if
inline int long mutable namespace new noexcept not not_eq nullptr operator or or_eq private protected public
register reinterpret_cast requires return short signed sizeof static static_assert static_cast struct switch
template this thread_local throw true try typedef typeid typename union unsigned using virtual void volatile
wchar_t while xor xor_eq final override main'''.split())

SOURCES = sorted(glob.glob(os.path.join(ROOT, 'src', 'auto', '*.cpp')) + glob.glob(os.path.join(ROOT, 'src', 'game', '*.cpp')) +
                 glob.glob(os.path.join(ROOT, 'src', 'native', '*.cpp')) + [os.path.join(ROOT, 'src', 'data', 'gamedata.cpp')])
HEADERS = sorted(glob.glob(os.path.join(ROOT, 'src', 'include', '*.h')) + [os.path.join(ROOT, 'src', 'data', 'gamedata.h')])
PROTOS = os.path.join(ROOT, 'src', 'auto', 'protos.h')
FOREIGN = sorted(glob.glob(os.path.join(ROOT, 'src', 'platform', '*.[ch]')) + glob.glob(os.path.join(ROOT, 'src', 'host', '*.[ch]')))

IDENT = re.compile(r'[A-Za-z_]\w*')
# *(T *)&self: self read as another type (the unwind funclets' idiom) -> (T)this
SELF_PUN = re.compile(r'\*\s*\(\s*([A-Za-z_][\w ]*?\s*\**)\s*\*\s*\)\s*&\s*self\b(?!\s*(->|\.|\[))')


# ---------------------------------------------------------------- lexing

def mask(text):
    """The text with comments, string and character literals blanked
    (newlines kept): code positions stay the same."""
    out = list(text)
    i, n = 0, len(text)
    while i < n:
        c = text[i]
        if c == '/' and text.startswith('//', i):
            j = text.find('\n', i)
            j = n if j < 0 else j
            for k in range(i, j):
                out[k] = ' '
            i = j
        elif c == '/' and text.startswith('/*', i):
            j = text.find('*/', i + 2)
            j = n if j < 0 else j + 2
            for k in range(i, j):
                if out[k] != '\n':
                    out[k] = ' '
            i = j
        elif c in '"\'':
            j = i + 1
            while j < n and text[j] != c:
                j += 2 if text[j] == '\\' else 1
            for k in range(i + 1, min(j, n)):
                if out[k] != '\n':
                    out[k] = ' '
            i = j + 1
        elif c == '#' and (i == 0 or text[i - 1] == '\n'):
            # preprocessor line: keep (it may define things) but skip as a unit
            j = i
            while True:
                j = text.find('\n', j)
                if j < 0 or text[j - 1] != '\\':
                    break
                j += 1
            i = n if j < 0 else j
        else:
            i += 1
    return ''.join(out)


def match_close(m, i, open_c='(', close_c=')'):
    """Index of the bracket closing the one at m[i]."""
    depth = 0
    for j in range(i, len(m)):
        c = m[j]
        if c == open_c:
            depth += 1
        elif c == close_c:
            depth -= 1
            if depth == 0:
                return j
    raise ValueError('unbalanced at %d' % i)


def split_args(m, lo, hi):
    """Top-level comma positions in m[lo:hi] -> list of (start, end)."""
    parts, depth, start = [], 0, lo
    for j in range(lo, hi):
        c = m[j]
        if c in '([{':
            depth += 1
        elif c in ')]}':
            depth -= 1
        elif c == ',' and depth == 0:
            parts.append((start, j))
            start = j + 1
    parts.append((start, hi))
    if len(parts) == 1 and not m[lo:hi].strip():
        return []
    return parts


def prev_code(m, i):
    """The non-blank text just before position i (up to 2 characters)."""
    j = i - 1
    while j >= 0 and m[j] in ' \t\n':
        j -= 1
    return m[max(0, j - 1):j + 1]


def next_char(m, i):
    while i < len(m) and m[i] in ' \t\n':
        i += 1
    return (m[i] if i < len(m) else ''), i


# ---------------------------------------------------------------- headers

class ClassInfo:
    def __init__(self, name, base, path, start, end):
        self.name, self.base, self.path, self.start, self.end = name, base, path, start, end
        self.fields = set()


def parse_classes():
    classes = {}
    for path in HEADERS:
        text = open(path).read()
        m = mask(text)
        for d in re.finditer(r'^typedef struct (\w+)\s*(?::\s*(?:public\s+)?(\w+)\s*)?\{', m, re.M):
            name, base = d.group(1), d.group(2)
            ob = d.end() - 1
            cb = match_close(m, ob, '{', '}')
            tail = re.match(r'\}\s*(\w+)\s*;', m[cb:])
            if not tail or tail.group(1) != name:
                continue
            ci = ClassInfo(name, base, path, ob, cb)
            body = m[ob + 1:cb]
            body = re.sub(r'\b(union|struct)\s*\{', ' ', body).replace('}', ';')
            for stmt in body.split(';'):
                stmt = stmt.strip()
                if not stmt or stmt.startswith('static_assert'):
                    continue
                fp = re.search(r'\(\s*\*\s*(\w+)\s*\)\s*\(', stmt)
                if fp:
                    ci.fields.add(fp.group(1))
                    continue
                if '(' in stmt:          # a member function declaration
                    mm = re.search(r'(\w+)\s*\(', stmt)
                    if mm:
                        ci.fields.add(mm.group(1))
                    continue
                for decl in stmt.split(','):
                    decl = re.sub(r'\[.*', '', decl)
                    decl = re.sub(r':\s*\d+\s*$', '', decl)
                    ids = IDENT.findall(decl)
                    if ids:
                        ci.fields.add(ids[-1])
            classes[name] = ci
    return classes


def chain(classes, c):
    """c and its bases, nearest first."""
    out = []
    while c in classes:
        out.append(c)
        c = classes[c].base
    return out


def derived(classes, c):
    """Every class derived from c (not c)."""
    return [d for d in classes if d != c and c in chain(classes, d)]


def macro_names():
    p = os.path.join(RUN, 'macros.txt')
    if not os.path.exists(p):
        raise SystemExit('run/methods/macros.txt missing: g++ -dM -E ... src/include/auto_common.h > it (see plan)')
    out = set()
    for line in open(p):
        mm = re.match(r'#define (\w+)', line)
        if mm:
            out.add(mm.group(1))
    return out


def type_names():
    """Typedef, struct, union and enum names (from the preprocessed headers)."""
    p = os.path.join(RUN, 'pp.txt')
    text = open(p).read()
    m = mask(text)
    out = set('void char short int long float double signed unsigned bool wchar_t'.split())
    for mm in re.finditer(r'\b(?:struct|union|enum|class)\s+(\w+)', m):
        out.add(mm.group(1))
    for mm in re.finditer(r'\btypedef\b', m):
        depth, j = 0, mm.end()
        while j < len(m) and not (m[j] == ';' and depth == 0):
            depth += m[j] == '{'
            depth -= m[j] == '}'
            j += 1
        t = m[mm.end():j]
        t = re.sub(r'\{.*\}', ' ', t, flags=re.S)
        t = re.sub(r'__attribute__\s*\(\(.*?\)\)', '', t)
        if '(' in t:
            fp = re.search(r'\(\s*[^()]*?(\w+)\s*\)\s*\(', t)      # (*name)(...), (CALLBACK *name)(...)
            if not fp:
                fp = re.search(r'(\w+)\s*\(', t)                   # a function type: name(...)
            if fp:
                out.add(fp.group(1))
            continue
        t = re.sub(r'\[[^\]]*\]', '', t)
        t = re.sub(r'__attribute__\s*\(\(.*?\)\)', '', t)
        for decl in t.split(','):
            ids = IDENT.findall(decl)
            if ids:
                out.add(ids[-1])
    return out


# ---------------------------------------------------------------- functions

class Func:
    pass


def find_functions(path, text=None):
    """Function definitions in a source: list of Func with .name (free name or
    Class::member), .cls (for Class::member), .hdr (start of the header line),
    .lparen, .rparen, .lbrace, .rbrace, .thiscall, .params text."""
    text = open(path).read() if text is None else text
    m = mask(text)
    out = []
    depth = 0
    i = 0
    n = len(m)
    while i < n:
        c = m[i]
        if c == '{':
            if depth == 0:
                # a top-level brace: a definition if preceded by `)` (possibly attributes)
                j = i - 1
                while j >= 0 and m[j] in ' \t\n':
                    j -= 1
                close = i
                k = match_close(m, i, '{', '}')
                if j >= 0 and m[j] == ')':
                    # the parameter list's opening paren
                    dep = 0
                    p = j
                    while p >= 0:
                        if m[p] == ')':
                            dep += 1
                        elif m[p] == '(':
                            dep -= 1
                            if dep == 0:
                                break
                        p -= 1
                    q = p - 1
                    while q >= 0 and m[q] in ' \t\n':
                        q -= 1
                    e = q + 1
                    while q >= 0 and (m[q].isalnum() or m[q] in '_:'):
                        q -= 1
                    name = m[q + 1:e]
                    if name and IDENT.match(name.split('::')[-1]) and name not in ('if', 'while', 'for', 'switch'):
                        f = Func()
                        f.name = name
                        f.cls = name.split('::')[0] if '::' in name else None
                        f.member = name.split('::')[-1]
                        ls = m.rfind('\n', 0, q + 1) + 1
                        # a header split over lines (Ghidra's style): back up over the return type lines
                        hs = ls
                        while True:
                            pl = m.rfind('\n', 0, hs - 1) + 1
                            prev = m[pl:hs - 1]
                            if hs > 0 and prev.strip() and not prev.rstrip().endswith((';', '}', '*/')) \
                                    and not prev.lstrip().startswith(('#', '/*')) and '{' not in prev:
                                hs = pl
                            else:
                                break
                        f.hdr = hs
                        f.namepos = q + 1
                        f.lparen, f.rparen, f.lbrace, f.rbrace = p, j, i, k
                        f.thiscall = '__thiscall' in m[hs:q + 1]
                        f.params = text[p + 1:j]
                        f.ret = re.sub(r'\s+', ' ', text[hs:q + 1].replace('__thiscall', '')).strip()
                        out.append(f)
                i = k + 1
                continue
        i += 1
    return out


def locals_of(m, f, types):
    """Names a function declares: parameters and locals (an identifier right
    after a type name and optional *s)."""
    names = set()
    seg = m[f.lparen:f.rbrace]
    for mm in re.finditer(r'\b([A-Za-z_]\w*)\b((?:\s*\*)*)\s*(?:const\s+)?([A-Za-z_]\w*)\b', seg):
        t, name = mm.group(1), mm.group(3)
        if t in types and name not in types and name not in KEYWORDS:
            names.add(name)
    # declarations of several: `int a, b;`, function pointer locals `T (*name)(...)`
    for mm in re.finditer(r'\(\s*\*\s*([A-Za-z_]\w*)\s*\)\s*\(', seg):
        names.add(mm.group(1))
    for mm in re.finditer(r'^\s*([A-Za-z_]\w*)\b[^;=(){}]*?,\s*[\*\s]*([A-Za-z_]\w*)\s*[;,]', seg, re.M):
        if mm.group(1) in types:
            names.add(mm.group(2))
    return names


def first_param(params):
    mm = re.match(r'\s*(?:struct\s+)?(\w+)\s*\*\s*self\s*(,|$)', params)
    return mm.group(1) if mm else None


# ---------------------------------------------------------------- plan

def plan():
    classes = parse_classes()
    macros = macro_names()
    types = type_names()
    # every __thiscall definition
    defs = {}
    for path in SOURCES:
        for f in find_functions(path):
            if f.thiscall and f.cls is None:
                defs.setdefault(f.name, []).append((path, f))
    protos = {}
    for line in open(PROTOS):
        mm = re.match(r'(.*?)\b__thiscall\s+(\w+)\((.*)\);\s*/\* ([0-9a-f]{8}) \*/', line)
        if mm:
            protos[mm.group(2)] = (mm.group(4), mm.group(3))
    # uses of each name that are not calls: the address taken
    names = set(defs)
    addr_taken = {}
    texts = {}
    for path in SOURCES + HEADERS + [PROTOS] + glob.glob(os.path.join(ROOT, 'build', 'native', 'gen', '*.cpp')):
        if not os.path.exists(path):
            continue
        t = open(path).read()
        mt = mask(t)
        texts[path] = (t, mt)
        for mm in IDENT.finditer(mt):
            nm = mm.group(0)
            if nm not in names:
                continue
            nc, _ = next_char(mt, mm.end())
            pc = prev_code(mt, mm.start())
            if nc == '(' or pc.endswith(('.', '->', '::')):
                continue
            addr_taken.setdefault(nm, set()).add(os.path.relpath(path, ROOT))
    foreign = set()
    for path in FOREIGN:
        t = mask(open(path).read())
        for nm in IDENT.findall(t):
            if nm in names:
                foreign.add(nm)
    script_calls = set()
    for path in glob.glob(os.path.join(ROOT, 'harness', '*', '*.txt')):
        for line in open(path, errors='replace'):
            mm = re.match(r'call\s+([A-Za-z_]\w*)\s', line)
            if mm:
                script_calls.add(mm.group(1))

    rows = []
    for name in sorted(defs, key=lambda n: protos.get(n, ('~',))[0]):
        lst = defs[name]
        path, f = lst[0]
        cls = first_param(f.params)
        addr = protos.get(name, ('',))[0]
        why = None
        if len(lst) > 1:
            why = 'defined twice'
        elif cls is None:
            why = 'self is not a class pointer'
        elif cls not in classes:
            why = 'self is %s (not a class)' % cls
        elif cls.endswith('View') and cls not in REAL_VIEWS:
            why = "self is a decompiler view (%s)" % cls
        elif name in script_calls:
            why = 'called by replay scripts'
        elif name in foreign:
            why = 'used by the platform layer'
        elif name in addr_taken:
            why = 'address taken (%s)' % ', '.join(sorted(addr_taken[name]))
        else:
            t, mt = texts[path]
            body = SELF_PUN.sub('this', mt[f.lbrace:f.rbrace])
            if re.search(r'(?<![\w.>])self\s*(=[^=]|\+\+|--)|(\+\+|--)\s*self\b|&\s*self\b(?!\s*(->|\[))', body):
                why = 'assigns self or takes its address'
        rows.append(dict(old=name, cls=cls or '', addr=addr, file=os.path.relpath(path, ROOT), why=why or ''))

    # names
    methods_of = {}
    for r in rows:
        if r['why']:
            continue
        c = r['cls']
        new = OVERRIDES.get(r['old'])
        if new is None:
            new = r['old']
            for p in sorted(PREFIXES.get(c, []), key=len, reverse=True):
                if r['old'].startswith(p) and len(r['old']) > len(p):
                    new = r['old'][len(p):]
                    break
            new = re.sub(r'(^|_)ctor$', r'\1construct', new)
            new = re.sub(r'(^|_)dtor$', r'\1destruct', new)
        r['new'] = new
        methods_of.setdefault(c, []).append(r)
    family = {}
    for c in classes:
        family[c] = set(chain(classes, c)) | set(derived(classes, c))
    for c, lst in methods_of.items():
        taken = set()
        fam_fields = set()
        for d in family[c]:
            fam_fields |= classes[d].fields
        for r in lst:
            cand = [r['new'], r['old']]
            for new in cand:
                bad = (new in KEYWORDS or new in macros or new in types or new in classes or new in fam_fields
                       or new in taken or not IDENT.fullmatch(new))
                if not bad:
                    break
            else:
                r['why'] = 'no usable member name'
                continue
            if new != r['new']:
                r['note'] = 'kept whole (%s clashes)' % r['new']
            r['new'] = new
            taken.add(new)
    os.makedirs(RUN, exist_ok=True)
    with open(PLAN, 'w') as fo:
        fo.write('# Methods of the game\'s classes: the original free name, the class, the member name\n'
                 '# (empty: left free, the reason in `why`). tools/cxx_methods.py plan; '
                 'tools/cxx_compare.py --map uses it.\n')
        fo.write('addr\told\tclass\tmember\tfile\twhy\n')
        for r in rows:
            fo.write('%s\t%s\t%s\t%s\t%s\t%s\n' % (r['addr'], r['old'], r['cls'], '' if r['why'] else r['new'],
                                                    r['file'], r['why'] or r.get('note', '')))
    conv = [r for r in rows if not r['why']]
    print('%d __thiscall functions: %d become members, %d stay free' % (len(rows), len(conv), len(rows) - len(conv)))
    reasons = {}
    for r in rows:
        if r['why']:
            k = re.sub(r' \(.*', '', r['why'])
            reasons[k] = reasons.get(k, 0) + 1
    for k, v in sorted(reasons.items(), key=lambda kv: -kv[1]):
        print('  %4d %s' % (v, k))
    ungrouped = sorted({r['cls'] for r in conv} - {c for g in GROUPS.values() for c in g})
    if ungrouped:
        print('classes in no group:', ' '.join(ungrouped))


def load_plan():
    rows = []
    with open(PLAN) as f:
        lines = [l for l in f if not l.startswith('#')]
    for r in csv.DictReader(lines, delimiter='\t'):
        rows.append(r)
    return rows


# ---------------------------------------------------------------- apply

class Ctx:
    pass


def apply(groups):
    classes = parse_classes()
    macros = macro_names()
    types = type_names()
    rows = load_plan()
    TYPES.update(types)
    members = [r for r in rows if r['member']]
    by_old = {r['old']: r for r in members}
    sel_classes = set(c for g in groups for c in GROUPS[g])
    now = {r['old']: r for r in members if r['class'] in sel_classes}
    # names declared per class: fields and every planned member (all batches)
    declared = {c: set(ci.fields) for c, ci in classes.items()}
    for r in members:
        declared.setdefault(r['class'], set()).add(r['member'])

    def hidden_below(target, name):
        """Some class derived from target declares name: a call through a
        pointer of unknown type must be qualified."""
        return any(name in declared.get(d, ()) for d in derived(classes, target))

    def hidden_between(static, target, name):
        """Lookup of name from class `static` stops before reaching target."""
        for c in chain(classes, static):
            if c == target:
                return False
            if name in declared.get(c, ()):
                return True
        return False

    def visible(c):
        out = set()
        for b in chain(classes, c):
            out |= declared.get(b, set())
        return out

    report = []
    edits_total = 0
    for path in SOURCES:
        text = open(path).read()
        new_text = convert_file(path, text, classes, by_old, now, declared, types, macros, hidden_below,
                                hidden_between, visible, report)
        if new_text != text:
            open(path, 'w').write(new_text)
            edits_total += 1
    # headers: declarations into the classes, prototypes out of protos.h
    decls = {}
    for r in now.values():
        decls.setdefault(r['class'], []).append(r)
    sigs = collect_signatures(now)
    for path in HEADERS:
        text = open(path).read()
        m = mask(text)
        inserts = []
        for c, lst in decls.items():
            ci = classes[c]
            if ci.path != path:
                continue
            lines = ['', '    /* methods */']
            for r in sorted(lst, key=lambda r: r['addr'] or '~'):
                ret, params = sigs[r['old']]
                decl = '    %s%s%s(%s);' % (ret, '' if ret.endswith('*') else ' ', r['member'], params)
                if r['addr']:
                    decl += '    /* %s */' % r['addr']
                lines.append(decl)
            # before the closing brace's line
            ls = text.rfind('\n', 0, ci.end) + 1
            inserts.append((ls, '\n'.join(lines[1:]) + '\n' if text[ls:ci.end].strip() == '' else None, ci.end))
        for ls, block, end in sorted(inserts, reverse=True):
            if block is None:
                raise SystemExit('closing brace of a class not on its own line: %s' % path)
            text = text[:ls] + block + text[ls:]
        if inserts:
            open(path, 'w').write(text)
    out = []
    for line in open(PROTOS):
        mm = re.match(r'.*?\b__thiscall\s+(\w+)\(', line)
        if mm and mm.group(1) in now:
            continue
        out.append(line)
    open(PROTOS, 'w').write(''.join(out))
    # the map for cxx_compare
    os.makedirs(RUN, exist_ok=True)
    with open(os.path.join(RUN, 'report.txt'), 'a') as f:
        f.write(''.join(l + '\n' for l in report))
    print('%d methods converted (%s); %d sources changed; notes in run/methods/report.txt (%d)' % (
        len(now), ' '.join(groups), edits_total, len(report)))


_SIGS = {}


def collect_signatures(now):
    return _SIGS


TYPES = set()


def is_postfix(e):
    """Whether `e->m()` parses as intended (e is a postfix expression)."""
    e = e.strip()
    m = mask(e)
    if re.fullmatch(r'[A-Za-z_]\w*', m):
        return True
    # a primary followed by ->x, .x, [..], (..)
    i = 0
    mm = re.match(r'[A-Za-z_]\w*', m)
    if mm:
        i = mm.end()
    elif m.startswith('('):
        i = match_close(m, 0) + 1
        inner = m[1:i - 1].strip()
        if i < len(m) and (inner.endswith('*') or inner in TYPES or re.fullmatch(r'(const\s+|unsigned\s+|struct\s+)*\w+', inner) and inner.split()[-1] in TYPES):
            return False        # a cast: (T *)x
    else:
        return False
    while i < len(m):
        rest = m[i:]
        mm = re.match(r'\s*(->|\.)\s*[A-Za-z_]\w*', rest)
        if mm:
            i += mm.end()
            continue
        mm = re.match(r'\s*[\[(]', rest)
        if mm:
            o = i + mm.end() - 1
            i = match_close(m, o, m[o], ']' if m[o] == '[' else ')') + 1
            continue
        return False
    return True


def convert_file(path, text, classes, by_old, now, declared, types, macros, hidden_below, hidden_between, visible,
                 report):
    rel = os.path.relpath(path, ROOT)
    funcs = find_functions(path, text)
    m = mask(text)
    # the enclosing function of each position; and which are members (now or before)
    edits = []        # (start, end, replacement)
    for f in funcs:
        conv = f.cls is None and f.name in now and f.thiscall
        if f.cls is not None:
            ccls = f.cls            # converted earlier
        elif conv:
            ccls = now[f.name]['class']
        else:
            ccls = None
        selfname = 'this' if f.cls is not None else ('self' if conv else None)
        local = locals_of(m, f, types) if ccls else set()
        if conv:
            local.discard('self')
        ctx = Ctx()
        ctx.ccls, ctx.selfname, ctx.local, ctx.conv = ccls, selfname, local, conv
        ctx.fname = f.name
        # rewrite the body (calls, then self/this) as one replacement
        body_start, body_end = f.lbrace, f.rbrace + 1
        body = rewrite_calls(text[body_start:body_end], ctx, by_old, now, declared, hidden_below, hidden_between,
                             classes, report, rel)
        if conv:
            body = convert_body(body, ctx, visible(ccls), declared, classes, macros, report, rel)
        if body != text[body_start:body_end]:
            edits.append((body_start, body_end, body))
        if conv:
            r = now[f.name]
            params = text[f.lparen + 1:f.rparen]
            mm = re.match(r'\s*(?:struct\s+)?\w+\s*\*\s*self\s*,?', params)
            rest = params[mm.end():].strip()
            rest = re.sub(r'\s*\n\s*', ' ', rest)
            if not rest:
                rest = ''
            ret = f.ret
            _SIGS[f.name] = (ret, rest)
            # keep any comment lines inside the header region? the header is
            # RET __thiscall NAME (params): one line now
            hdr = '%s%s%s::%s(%s)' % (ret, '' if ret.endswith('*') else ' ', r['class'], r['member'], rest)
            # from the header start to the closing paren
            edits.append((f.hdr, f.rparen + 1, hdr))
    # calls outside function bodies (initializers): rewrite too
    for s, e, rep in sorted(edits, key=lambda x: x[0], reverse=True):
        text = text[:s] + rep + text[e:]
    return text.replace('\x01', '')


def rewrite_calls(seg, ctx, by_old, now, declared, hidden_below, hidden_between, classes, report, rel):
    """Calls name(obj, args) of methods converted now -> obj->member(args)."""
    m = mask(seg)
    out = []
    pos = 0
    for mm in IDENT.finditer(m):
        if mm.start() < pos:
            continue
        nm = mm.group(0)
        if nm not in now:
            continue
        nc, lp = next_char(m, mm.end())
        pc = prev_code(m, mm.start())
        if nc != '(' or pc.endswith(('.', '->', '::')):
            continue
        rp = match_close(m, lp)
        args = split_args(m, lp + 1, rp)
        if not args:
            report.append('%s: %s: call without arguments' % (rel, ctx.fname))
            continue
        r = now[nm]
        target, member = r['class'], r['member']
        a0 = seg[args[0][0]:args[0][1]].strip()
        rest = [rewrite_calls(seg[s:e], ctx, by_old, now, declared, hidden_below, hidden_between, classes, report,
                              rel) for s, e in args[1:]]
        rest_text = ','.join(rest)
        if rest and rest_text.startswith(' '):
            pass
        a0 = rewrite_calls(a0, ctx, by_old, now, declared, hidden_below, hidden_between, classes, report, rel)
        a0s = a0.strip()
        if ctx.selfname and a0s == ctx.selfname:
            static = ctx.ccls
            if static != target and target not in chain(classes, static):
                rep = '((%s *)%s)->%s(%s)' % (target, 'this', member, rest_text.strip() if False else rest_text)
                report.append('%s: %s: %s called on this of unrelated class %s' % (rel, ctx.fname, nm, static))
            elif hidden_between(static, target, member):
                rep = '\x01%s::%s(%s)' % (target, member, rest_text)
            elif member in ctx.local:
                rep = 'this->%s(%s)' % (member, rest_text)
            else:
                rep = '\x01%s(%s)' % (member, rest_text)
        else:
            if re.fullmatch(r'0|NULL|nullptr|\(\w+\s*\*\)\s*0', a0s):
                report.append('%s: %s: %s called on a null object' % (rel, ctx.fname, nm))
                obj = '((%s *)0)' % target
                arrow = '->'
            else:
                am = re.fullmatch(r'&\s*(.+)', a0s, re.S)
                if am and is_postfix(am.group(1)) and not am.group(1).strip().startswith('('):
                    obj, arrow = am.group(1).strip(), '.'
                elif is_postfix(a0s):
                    obj, arrow = a0s, '->'
                else:
                    obj, arrow = '(%s)' % a0s, '->'
            q = '%s::' % target if hidden_below(target, member) else ''
            rep = '%s%s%s%s(%s)' % (obj, arrow, q, member, rest_text)
        out.append(seg[pos:mm.start()])
        out.append(rep)
        pos = rp + 1
    out.append(seg[pos:])
    return ''.join(out)


def convert_body(body, ctx, vis, declared, classes, macros, report, rel):
    """self -> this; this->name -> name where nothing local hides it; a
    global the class's members now hide -> ::name."""
    body = SELF_PUN.sub(lambda mm: '((%s)self)' % mm.group(1).strip(), body)
    # the rand trace names a member function by its free name (as the original's trace does)
    body = re.sub(r'\b_rand\(\)', 'crt_rand_at("%s")' % ctx.fname, body)
    m = mask(body)
    out = []
    pos = 0
    toks = list(IDENT.finditer(m))
    for k, mm in enumerate(toks):
        nm = mm.group(0)
        if mm.start() < pos:
            continue
        pc = prev_code(m, mm.start())
        if nm == 'self' and not pc.endswith(('.', '->', '::')):
            # self->name ?
            am = re.match(r'\s*->\s*([A-Za-z_]\w*)', m[mm.end():])
            if am:
                name = am.group(1)
                after, _ = next_char(m, mm.end() + am.end())
                if name not in ctx.local and name in vis and name not in macros:
                    out.append(body[pos:mm.start()])
                    pos = mm.end() + am.start(1)
                    continue
                out.append(body[pos:mm.start()])
                out.append('this')
                pos = mm.end()
                continue
            out.append(body[pos:mm.start()])
            out.append('this')
            pos = mm.end()
            continue
        if nm in vis and nm not in ctx.local and nm not in macros and not pc.endswith(('.', '->', '::', '\x01')) \
                and pc[-1:] != '~' and not re.search(r'\b(goto|struct|union|enum)\s*$', m[max(0, mm.start() - 8):mm.start()]):
            # a label?
            nc, ni = next_char(m, mm.end())
            if nc == ':' and not m.startswith('::', ni):
                ls = m.rfind('\n', 0, mm.start()) + 1
                if not m[ls:mm.start()].strip():
                    continue
            out.append(body[pos:mm.start()])
            out.append('::' + nm)
            pos = mm.end()
            report.append('%s: %s: %s -> ::%s (a member of %s hides it)' % (rel, ctx.fname, nm, nm, ctx.ccls))
            continue
    out.append(body[pos:])
    return ''.join(out)


def main():
    if len(sys.argv) < 2:
        print(__doc__)
        return 1
    if sys.argv[1] == 'plan':
        if os.path.exists(PLAN) and '--force' not in sys.argv:
            raise SystemExit('re/methods.tsv exists (the names of methods converted already): --force to redo it')
        plan()
    elif sys.argv[1] == 'apply':
        groups = list(GROUPS) if sys.argv[2:] == ['--all'] else sys.argv[2:]
        for g in groups:
            if g not in GROUPS:
                raise SystemExit('unknown group %s' % g)
        apply(groups)
    else:
        print(__doc__)
        return 1
    return 0


if __name__ == '__main__':
    sys.exit(main())
