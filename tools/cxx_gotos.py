#!/usr/bin/env python3
"""Step 6: replace the decompiler's gotos with structured control flow where
the rewrite is mechanical and safe.

    cxx_gotos.py [-n] FILE...        (-n: report what would change)

Each function body is parsed into statements (blocks, if/else, loops,
switch, labels, jumps) and these rewrites are applied until none applies:

  return   `goto L;` where `L:` is followed by `return x;` (or ends a void
           function's body)                     -> `return x;`
  break    `goto L;` inside a loop (not inside an inner loop or switch)
           where `L:` follows that loop         -> `break;`
  continue `goto L;` inside a loop (not inside an inner loop) where `L:`
           ends the loop's body                 -> `continue;`
  if       `if (c) goto L; S...; L:` in one block, L reached from nowhere
           else                                 -> `if (!c) { S... }`
  else     `if (c) { S...; goto L; } T...; L:` in one block, L reached
           from nowhere else                    -> `if (c) { S... } else { T... }`
  do       `L: S...; if (c) goto L;` in one block, L reached from nowhere
           else                                 -> `do { S... } while (c);`
  loop     `L: S...; goto L;`                   -> `for (;;) { S... }`

`do`/`loop` are refused when S contains a break or continue that would
then bind to the new loop.  A label no goto names any more is removed.
Conditions are negated as `!(c)`, or by swapping == and != when c is one
comparison.  Expressions are copied as written: evaluation order and side
effects are unchanged.
"""
import re
import sys

TOKEN = re.compile(r'''
    (?P<ws>\s+)
  | (?P<comment>//[^\n]*|/\*.*?\*/)
  | (?P<pp>^[ \t]*\#[^\n]*(?:\\\n[^\n]*)*)
  | (?P<str>"(?:\\.|[^"\\\n])*"|'(?:\\.|[^'\\\n])*')
  | (?P<id>[A-Za-z_]\w*)
  | (?P<num>\.?\d[\w.]*(?:[eEpP][+-]\w*)?)
  | (?P<punct>::|->|\+\+|--|<<=|>>=|<=|>=|==|!=|&&|\|\||[-+*/%&|^!~<>=]=?|[(){}\[\];:,.?\#])
''', re.S | re.X | re.M)


def tokenize(text):
    toks = []
    pos = 0
    while pos < len(text):
        m = TOKEN.match(text, pos)
        if not m:
            raise SyntaxError('cannot tokenize at %d: %r' % (pos, text[pos:pos + 20]))
        kind = m.lastgroup
        if kind not in ('ws', 'comment', 'pp'):
            toks.append((kind, m.group(), m.start(), m.end()))
        pos = m.end()
    return toks


class Node:
    def __init__(self, kind, start, end, **kw):
        self.kind, self.start, self.end = kind, start, end
        self.__dict__.update(kw)

    def children(self):
        for k in ('body', 'then', 'els'):
            v = getattr(self, k, None)
            if v is not None:
                yield v
        for s in getattr(self, 'stmts', []) or []:
            yield s

    def walk(self):
        yield self
        for c in self.children():
            yield from c.walk()

    def __repr__(self):
        return '<%s %d-%d>' % (self.kind, self.start, self.end)


class Parser:
    def __init__(self, toks):
        self.t = toks
        self.i = 0

    def peek(self, k=0):
        return self.t[self.i + k][1] if self.i + k < len(self.t) else None

    def take(self, want=None):
        tok = self.t[self.i]
        if want is not None and tok[1] != want:
            raise SyntaxError('expected %r, got %r at %d' % (want, tok[1], tok[2]))
        self.i += 1
        return tok

    def balanced(self, open_, close):
        """from an opening token to its match; returns (start, end) offsets"""
        start = self.take(open_)[2]
        depth = 1
        while depth:
            tok = self.take()
            if tok[1] == open_:
                depth += 1
            elif tok[1] == close:
                depth -= 1
        return start, tok[3]

    def block(self):
        start = self.take('{')[2]
        stmts = []
        while self.peek() != '}':
            stmts.append(self.statement())
        end = self.take('}')[3]
        return Node('block', start, end, stmts=stmts)

    def statement(self):
        tok = self.t[self.i]
        v = tok[1]
        start = tok[2]
        if v == '{':
            return self.block()
        if v == 'if':
            self.take()
            cs, ce = self.balanced('(', ')')
            then = self.statement()
            els = None
            if self.peek() == 'else':
                self.take()
                els = self.statement()
            return Node('if', start, (els or then).end, cond=(cs, ce), then=then, els=els)
        if v in ('while', 'switch'):
            self.take()
            cs, ce = self.balanced('(', ')')
            body = self.statement()
            return Node(v, start, body.end, cond=(cs, ce), body=body)
        if v == 'for':
            self.take()
            cs, ce = self.balanced('(', ')')
            body = self.statement()
            return Node('for', start, body.end, cond=(cs, ce), body=body)
        if v == 'do':
            self.take()
            body = self.statement()
            self.take('while')
            cs, ce = self.balanced('(', ')')
            end = self.take(';')[3]
            return Node('do', start, end, cond=(cs, ce), body=body)
        if v in ('case', 'default'):
            self.take()
            while self.peek() != ':':
                self.take()
            end = self.take(':')[3]
            return Node('case', start, end)
        if tok[0] == 'id' and self.peek(1) == ':' and v not in ('public', 'private', 'protected'):
            self.take()
            end = self.take(':')[3]
            return Node('label', start, end, name=v)
        if v == 'goto':
            self.take()
            name = self.take()[1]
            end = self.take(';')[3]
            return Node('goto', start, end, target=name)
        if v in ('break', 'continue'):
            self.take()
            end = self.take(';')[3]
            return Node(v, start, end)
        if v == 'return':
            self.take()
            while self.peek() != ';':
                if self.peek() in ('(', '{', '['):
                    o = self.peek()
                    self.balanced(o, {'(': ')', '{': '}', '[': ']'}[o])
                else:
                    self.take()
            end = self.take(';')[3]
            return Node('return', start, end)
        if v == ';':
            end = self.take()[3]
            return Node('empty', start, end)
        # expression or declaration
        while self.peek() != ';':
            if self.peek() in ('(', '{', '['):
                o = self.peek()
                self.balanced(o, {'(': ')', '{': '}', '[': ']'}[o])
            else:
                self.take()
        end = self.take(';')[3]
        return Node('expr', start, end)


def function_bodies(text, toks):
    """(token index of '{', ...) for each top-level function body"""
    depth = 0
    out = []
    i = 0
    while i < len(toks):
        v = toks[i][1]
        if v == '{':
            if depth == 0:
                # a function body: preceded by ')' or ') const' etc.
                j = i - 1
                while j >= 0 and toks[j][1] in ('const', 'noexcept', 'override'):
                    j -= 1
                if j >= 0 and toks[j][1] == ')':
                    out.append(i)
                    # skip it
                    d = 0
                    while True:
                        if toks[i][1] == '{':
                            d += 1
                        elif toks[i][1] == '}':
                            d -= 1
                            if d == 0:
                                break
                        i += 1
                    i += 1
                    continue
                # extern "C" { or namespace {: stay at depth 0
                j = i - 1
                if j >= 0 and (toks[j][0] == 'str' or toks[j][1] == 'namespace'
                               or (j > 0 and toks[j - 1][1] == 'namespace')):
                    i += 1
                    continue
            depth += 1
        elif v == '}':
            depth = max(0, depth - 1)
        i += 1
    return out


# ---------------------------------------------------------------- analysis

def parents(root):
    par = {}
    for n in root.walk():
        for c in n.children():
            par[id(c)] = n
    return par


def gotos_to(root, name):
    return [n for n in root.walk() if n.kind == 'goto' and n.target == name]


def label_node(root, name):
    for n in root.walk():
        if n.kind == 'label' and n.name == name:
            return n
    return None


def inside(n, a):
    return a.start <= n.start and n.end <= a.end


def free_jumps(stmts, kinds):
    """break/continue statements among stmts that bind outside them"""
    out = []

    def visit(n, in_loop, in_switch):
        if n.kind == 'break' and not in_loop and not in_switch and 'break' in kinds:
            out.append(n)
        if n.kind == 'continue' and not in_loop and 'continue' in kinds:
            out.append(n)
        loop = in_loop or n.kind in ('while', 'for', 'do')
        sw = in_switch or n.kind == 'switch'
        for c in n.children():
            visit(c, loop, sw)
    for s in stmts:
        visit(s, False, False)
    return out


def enclosing_jump_owner(n, par, root, kind):
    """the loop (or switch, for break) a break/continue at n would bind to"""
    p = par.get(id(n))
    while p is not None and p is not root:
        if p.kind in ('while', 'for', 'do'):
            return p
        if kind == 'break' and p.kind == 'switch':
            return p
        p = par.get(id(p))
    return None


def next_stmt(block, n):
    i = next(k for k, s in enumerate(block.stmts) if s is n)
    return block.stmts[i + 1] if i + 1 < len(block.stmts) else None


def negate(text):
    t = text.strip()
    toks = tokenize(t)
    depth = 0
    ops = []
    close = {}
    stack = []
    for k, tok in enumerate(toks):
        if tok[1] in '([{':
            depth += 1
            stack.append(k)
        elif tok[1] in ')]}':
            depth -= 1
            close[stack.pop()] = k
        elif depth == 0 and tok[0] == 'punct' and tok[1] not in ('.', '->', '::', '!', '~', '++', '--'):
            ops.append(tok)
    if len(ops) == 1 and ops[0][1] in ('==', '!='):
        tok = ops[0]
        return t[:tok[2]] + ('!=' if tok[1] == '==' else '==') + t[tok[3]:]
    if len(toks) > 2 and toks[0][1] == '!' and toks[1][1] == '(' and close.get(1) == len(toks) - 1:
        return t[toks[1][3]:toks[-1][2]].strip()
    if len(toks) == 1 or (toks[0][1] == '(' and close.get(0) == len(toks) - 1):
        return '!' + t
    return '!(' + t + ')'


# ---------------------------------------------------------------- rewriting

def indent_of(text, pos):
    ls = text.rfind('\n', 0, pos) + 1
    m = re.match(r'[ \t]*', text[ls:])
    return m.group()


def reindent(chunk, delta):
    """shift every line after the first by delta spaces (may be negative)"""
    lines = chunk.split('\n')
    out = [lines[0]]
    for ln in lines[1:]:
        if delta >= 0:
            out.append((' ' * delta + ln) if ln.strip() else ln)
        else:
            k = 0
            while k < -delta and k < len(ln) and ln[k] == ' ':
                k += 1
            out.append(ln[k:])
    return '\n'.join(out)


def line_span(text, start, end):
    """extend [start, end) to whole lines when they hold nothing else"""
    ls = text.rfind('\n', 0, start) + 1
    le = text.find('\n', end)
    le = len(text) if le < 0 else le
    if text[ls:start].strip() == '' and text[end:le].strip() == '':
        return ls, le + 1
    return start, end


def label_span(text, lab, blk):
    """the label's text, with a `;` right after it on the same line, as
    whole lines when nothing else shares them"""
    end = lab.end
    m = re.match(r'[ \t]*;', text[end:])
    if m:
        end += m.end()
    return line_span(text, lab.start, end)


def drop_stmt(text, n):
    a, b = line_span(text, n.start, n.end)
    return text[:a] + text[b:]


def wrap(text, head, after, end, ind, tail=''):
    """head + '{' + text[after:end] indented one level + '}' + tail"""
    inner = reindent(text[after:end], 2)
    return head + ' {' + inner.rstrip(' ') + ('' if inner.endswith('\n') else '\n') + ind + '}' + tail


def try_rewrite(text, body):
    """one rewrite in the function body (a Node); returns (new text, kind) or None"""
    par = parents(body)
    nodes = list(body.walk())
    gotos = [n for n in nodes if n.kind == 'goto']
    labels = {n.name: n for n in nodes if n.kind == 'label'}
    refs = {}
    for g in gotos:
        refs.setdefault(g.target, []).append(g)

    for name, lab in labels.items():
        if name not in refs:
            blk = par.get(id(lab))
            nxt = next_stmt(blk, lab) if blk is not None and blk.kind == 'block' else None
            a, b = label_span(text, lab, blk)
            return text[:a] + text[b:], 'unused'

    for g in gotos:
        lab = labels.get(g.target)
        if lab is None:
            continue
        lblk = par.get(id(lab))
        if lblk is None or lblk.kind != 'block':
            continue
        nxt = next_stmt(lblk, lab)
        while nxt is not None and nxt.kind in ('label', 'empty'):
            nxt = next_stmt(lblk, nxt)
        if nxt is not None and nxt.kind == 'return':
            return text[:g.start] + text[nxt.start:nxt.end] + text[g.end:], 'return'
        if nxt is None and lblk is body:
            return text[:g.start] + 'return;' + text[g.end:], 'return'
        owner = enclosing_jump_owner(g, par, body, 'break')
        if owner is not None and owner.kind in ('while', 'for', 'do') and par.get(id(owner)) is lblk \
                and next_stmt(lblk, owner) is lab:
            return text[:g.start] + 'break;' + text[g.end:], 'break'
        cowner = enclosing_jump_owner(g, par, body, 'continue')
        if cowner is not None and cowner.body is lblk:
            rest = lblk.stmts[lblk.stmts.index(lab) + 1:]
            if all(s.kind in ('empty', 'label') for s in rest):
                return text[:g.start] + 'continue;' + text[g.end:], 'continue'

    for name, lab in labels.items():
        rs = refs.get(name, [])
        if len(rs) != 1:
            continue
        g = rs[0]
        blk = par.get(id(lab))
        if blk is None or blk.kind != 'block':
            continue
        gp = par.get(id(g))
        ifn = None
        if gp is not None and gp.kind == 'if' and gp.then is g and gp.els is None:
            ifn = gp
        elif gp is not None and gp.kind == 'block' and len(gp.stmts) == 1:
            gpp = par.get(id(gp))
            if gpp is not None and gpp.kind == 'if' and gpp.then is gp and gpp.els is None:
                ifn = gpp
        stmts = blk.stmts
        li = stmts.index(lab)
        la, lb = label_span(text, lab, blk)
        if not (la == 0 or text[la - 1] == '\n') or text[lb - 1] != '\n':
            continue        # the label shares its line
        if ifn is not None and par.get(id(ifn)) is blk:
            ii = stmts.index(ifn)
            cond = text[ifn.cond[0] + 1:ifn.cond[1] - 1]
            ind = indent_of(text, ifn.start)
            if ii < li:
                # if (c) goto L; S; L:  ->  if (!c) { S }
                rng = stmts[ii + 1:li]
                if not rng or not ok_range(rng, refs) or too_long(text, rng):
                    continue
                new = wrap(text, 'if (%s)' % negate(cond), ifn.end, la, ind, '\n')
                return text[:ifn.start] + new + text[lb:], 'if'
            # L: S; if (c) goto L;  ->  do { S } while (c);
            rng = stmts[li + 1:ii]
            if not ok_range(rng, refs) or free_jumps(rng, ('break', 'continue')):
                continue
            if any(s.kind == 'label' for s in rng):
                continue
            if not rng:
                continue
            ind = indent_of(text, rng[0].start)
            ia, ib = line_span(text, ifn.start, ifn.end)
            new = wrap(text, ind + 'do', lb - 1, ia, ind, ' while (%s);\n' % cond.strip())
            return text[:la] + new + text[ib:], 'do'
        # if (c) { S; goto L; } T; L:  ->  if (c) { S } else { T }
        if gp is not None and gp.kind == 'block' and len(gp.stmts) > 1 and gp.stmts[-1] is g:
            gpp = par.get(id(gp))
            if gpp is not None and gpp.kind == 'if' and gpp.then is gp and gpp.els is None \
                    and par.get(id(gpp)) is blk and stmts.index(gpp) < li:
                ii = stmts.index(gpp)
                rng = stmts[ii + 1:li]
                if not rng or not ok_range(rng, refs) or too_long(text, rng):
                    continue
                ind = indent_of(text, gpp.start)
                ga, gb = line_span(text, g.start, g.end)
                els = wrap(text, '\n' + ind + 'else', gpp.end, la, ind, '\n')
                return (text[:ga] + text[gb:gpp.end] + els + text[lb:]), 'else'
        # L: S; goto L;  ->  for (;;) { S }
        if gp is blk and stmts.index(g) > li:
            gi = stmts.index(g)
            rng = stmts[li + 1:gi]
            if not rng or not ok_range(rng, refs) or free_jumps(rng, ('break', 'continue')):
                continue
            if any(s.kind == 'label' for s in rng):
                continue
            ind = indent_of(text, rng[0].start)
            ga, gb = line_span(text, g.start, g.end)
            new = wrap(text, ind + 'for (;;)', lb - 1, ga, ind, '\n')
            return text[:la] + new + text[gb:], 'loop'
    return None


MAX_LINES = 40


def too_long(text, rng):
    """a block this long reads better as an early exit than nested"""
    return text.count('\n', rng[0].start, rng[-1].end) >= MAX_LINES


def ok_range(rng, refs):
    """no case label of an enclosing switch; labels inside reached only from inside"""
    a, b = rng[0].start, rng[-1].end
    for s in rng:
        if s.kind == 'case':
            return False
        for n in s.walk():
            if n.kind == 'label':
                for g in refs.get(n.name, []):
                    if not (a <= g.start and g.end <= b):
                        return False
    return True


def rewrite_file(text, verbose=False):
    counts = {}
    guard = 0
    while guard < 5000:
        guard += 1
        toks = tokenize(text)
        changed = False
        for bi in function_bodies(text, toks):
            p = Parser(toks)
            p.i = bi
            try:
                body = p.block()
            except (SyntaxError, IndexError) as e:
                if verbose:
                    print('parse error in body at %d: %s' % (toks[bi][2], e), file=sys.stderr)
                continue
            if not any(n.kind in ('goto', 'label') for n in body.walk()):
                continue
            r = try_rewrite(text, body)
            if r:
                text, kind = r
                counts[kind] = counts.get(kind, 0) + 1
                changed = True
                break
        if not changed:
            break
    return text, counts


def main():
    args = sys.argv[1:]
    dry = False
    if args and args[0] == '-n':
        dry = True
        args = args[1:]
    for path in args:
        text = open(path).read()
        before = len(re.findall(r'\bgoto\b', text))
        new, counts = rewrite_file(text, verbose=True)
        after = len(re.findall(r'\bgoto\b', new))
        print('%s: gotos %d -> %d  %s' % (path, before, after, ' '.join('%s=%d' % kv for kv in sorted(counts.items()))))
        if not dry and new != text:
            open(path, 'w').write(new)
    return 0


if __name__ == '__main__':
    sys.exit(main())
