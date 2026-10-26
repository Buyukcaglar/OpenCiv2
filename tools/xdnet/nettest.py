#!/usr/bin/env python3
"""Two-game network test: two copies of the game (ours and/or the original
under Wine), each in its own civ2-dev container on the docker bridge, driven
by xdotool through host -> join -> start -> N turns -> quit; then the two
XDaemon logs are checked.

usage (from the project root, on the docker host):
  tools/xdnet/nettest.py ours-ours   [--turns N] [--run NAME] [--exe EXE] [--keep] [--sniff]
  tools/xdnet/nettest.py ours-orig   (ours hosts, the original joins)
  tools/xdnet/nettest.py orig-ours   (the original hosts, ours joins)
  tools/xdnet/nettest.py orig-orig
  options: --exe civ2-linux32asan   (our build to run; ASan reports are checked)
           --inet                   Internet mode over 127.0.0.1 (both games in one
                                    network namespace, displays :7 and :8)
           --chat                   Chat with Kings both ways, after the turns
           --diplo                  emissary, audience, peace treaty (after the turns)
           --save / --load          the host saves in its turn 2; --load: then loads it, N more turns
           --rejoin                 the client leaves and joins the game in progress
           --third ours|orig        a third player: the host relays
           --keep                   leave the containers running (drive them by hand)
  (docs/xdaemon-protocol.md section 11.1)

Everything goes to run/xd/cap/NAME/: xdlog-{host,client}.txt (the XD logs),
msgs-{host,client}.txt (the game messages, tools/xdnet/xdmsgs.py), shots/
(screenshots at each step), ours-*.log / wine-*.log, result.txt.

Waits are on conditions where there is one: the XD logs (a message type
sent or received, the turn's NM_START_WHOSE_TURN), the screen (unchanged
for a moment, so a dialog has finished drawing), a process's window; fixed
pauses only between keys.

Checks (result.txt, exit status 0 = all passed):
  - each log's game messages are well formed (magic, size = the size sent);
  - what one side sent over TCP the other received, same order and bytes;
  - both games reached turn N (NM_START_WHOSE_TURN for civ 0 starts a turn);
  - the expected message types in order (join, lock, state transfer,
    turns, city founding, quit);
  - no crash: both processes alive until told to quit, no ASan report,
    no Wine 'Unhandled exception'.
"""
import argparse, os, re, subprocess, sys, time

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import xdmsgs  # noqa: E402

try:
    from PIL import Image, ImageChops
except ImportError:  # screen waits degrade to fixed pauses
    Image = None

NM = {}


def nm(name):
    if not NM:
        xdmsgs.load_names()
        NM.update({v: k for k, v in xdmsgs.NAMES.items()})
    return NM[name]


def log(*a):
    print('%7.1f' % (time.time() - T0), *a, flush=True)


T0 = time.time()


class Fail(Exception):
    pass


def sh(*cmd, check=True, capture=False, timeout=None):
    r = subprocess.run(cmd, stdout=subprocess.PIPE if capture else subprocess.DEVNULL,
                       stderr=subprocess.STDOUT if capture else subprocess.DEVNULL, timeout=timeout)
    if check and r.returncode:
        raise Fail('command failed: %s' % ' '.join(cmd))
    return r.stdout.decode(errors='replace') if capture else r.returncode


class Game:
    """One game: KIND 'ours' or 'orig', ROLE 'host' or 'client', in CONTAINER on display DISP."""

    def __init__(self, kind, role, container, disp, run, exe):
        self.kind, self.role, self.c, self.disp, self.run, self.exe = kind, role, container, disp, run, exe
        self.out = os.path.join(ROOT, 'run/xd/cap', run)
        self.shots = os.path.join(self.out, 'shots')
        self.xdlog = os.path.join(self.out, 'xdlog-%s.txt' % role)
        self.n = 0
        self.slow = kind == 'orig'      # Wine: give it more time between keys
        self.civ = None
        self.logpos, self.wins, self.shown, self.pending = 0, {}, set(), None
        self.turn_seen, self.turn_t, self.popped, self.last_pop = 0, 0, False, 0

    # ---- driving ----
    def ex(self, cmd, **kw):
        return sh('docker', 'exec', '-e', 'DISPLAY=:%d' % self.disp, self.c, 'sh', '-c', cmd, **kw)

    def keys(self, *keys, pause=None):
        for k in keys:
            self.ex('xdotool key --delay 120 %s' % k)
            time.sleep(pause if pause is not None else (0.8 if self.slow else 0.4))

    def type(self, text):
        self.ex("xdotool type --delay 120 '%s'" % text)
        time.sleep(0.5)

    def click(self, x, y):
        self.ex('xdotool mousemove %d %d click 1' % (x, y))
        time.sleep(0.6 if self.slow else 0.3)

    def shot(self, name=None):
        self.n += 1
        name = name or 'x'
        p = os.path.join(self.shots, '%s%02d-%s.png' % (self.role[0], self.n, name))
        for attempt in range(3):      # (xwd can fail while windows come and go)
            if self.ex('xwd -root -silent -display :%d | convert xwd:- png:%s' % (
                    self.disp, p.replace(ROOT, '/work')), check=False) == 0:
                break
            time.sleep(0.5)
        return p

    def screen(self):
        p = os.path.join(self.shots, '.cur-%s.png' % self.role)
        self.ex('xwd -root -silent -display :%d | convert xwd:- png:%s' % (
            self.disp, p.replace(ROOT, '/work')), check=False)
        try:
            return Image.open(p).convert('RGB')
        except Exception:
            return None

    def wait_stable(self, timeout=30, still=2, tol=600):
        """Wait until the screen stops changing (fewer than TOL pixels differ
        between shots STILL seconds apart: a blinking unit is allowed)."""
        if Image is None:
            time.sleep(still + 2)
            return True
        end = time.time() + timeout
        prev = self.screen()
        while time.time() < end:
            time.sleep(still)
            cur = self.screen()
            if prev is not None and cur is not None:
                bbox = ImageChops.difference(prev, cur).convert('L').point(lambda v: 255 if v > 8 else 0)
                if sum(1 for v in bbox.getdata() if v) < tol:
                    return True
            prev = cur
        log(self.role, 'screen not stable after %ds' % timeout)
        return False

    def step(self, name, *keys, settle=True):
        self.keys(*keys)
        if settle:
            self.wait_stable()
        return self.shot(name)

    # ---- state ----
    def alive(self):
        pat = 'civ2.exe' if self.kind == 'orig' else 'build/%s' % self.exe
        # (a dead game stays a zombie: its container's init doesn't reap it)
        return self.ex('ps -eo stat=,args= | grep -v "^Z" | grep -v grep | grep -q "%s"' % pat, check=False) == 0

    def msgs(self):
        """[(ms, dir, chan, type, size, seq, data)]"""
        out = []
        if not os.path.exists(self.xdlog):
            return out
        for m in xdmsgs.parse(self.xdlog):
            d = xdmsgs.describe(m)
            if d:
                out.append((m['t'], m['dir'], m['chan'], d[0], d[1], d[2], m['data']))
        return out

    def count(self, direction, typ, pred=None):
        return sum(1 for m in self.msgs() if m[1] == direction and m[3] == typ and m[2] == 'tcp'
                   and (pred is None or pred(m)))

    def wait_msg(self, direction, typ, n=1, timeout=300, pred=None, what=None):
        end = time.time() + timeout
        while time.time() < end:
            if self.count(direction, typ, pred) >= n:
                return True
            if not self.alive():
                raise Fail('%s: the game is gone (waiting for %s)' % (self.role, what or typ))
            time.sleep(1)
        raise Fail('%s: no %s %s #%d within %ds' % (self.role, direction, what or typ, n, timeout))

    def turns(self):
        """NM_START_WHOSE_TURN messages seen, as [(ms, civ)]"""
        d = 'tx' if self.role == 'host' else 'rx'
        r = []
        for m in self.msgs():
            if m[1] == d and m[3] == 105 and m[2] == 'tcp' and len(m[6]) >= 20:
                r.append((m[0], int.from_bytes(m[6][16:20], 'little', signed=True)))
        return r


def docker_up(name, volume, net=None):
    sh('docker', 'rm', '-f', name, check=False)
    cmd = ['docker', 'run', '-d', '--name', name] + ([] if net else ['--hostname', name]) + ['-v', '%s:/wine' % volume,
           '-v', '%s:/work' % ROOT, '-v', '%s:/civ2:ro' % os.environ.get('CIV2_GAME', os.path.expanduser('~/Civ2')),
           '-w', '/work']
    if net:
        cmd += ['--network', 'container:%s' % net]
    sh(*cmd, 'civ2-dev', 'sleep', 'infinity')


def start(g, inet, save=None):
    env = 'DISP=%d' % g.disp
    if save:
        env += ' SAVE=%s' % save.replace(ROOT, '/work')
    if g.kind == 'orig':
        g.ex('%s sh /work/tools/xdnet/start1.sh %s %s' % (env, g.run, g.role))
    else:
        asan = 'ASAN_OPTIONS=halt_on_error=0:detect_leaks=0:quarantine_size_mb=16:malloc_context_size=8:log_path=%s/asan-%s' % (
            g.out.replace(ROOT, '/work'), g.role)
        gdb = 'GDB=1' if g.gdb else ''
        g.ex('%s EXE=%s %s %s sh /work/tools/xdnet/start_ours.sh %s %s' % (env, g.exe, asan, gdb, g.run, g.role))
    end = time.time() + 120
    while time.time() < end:
        if g.ex('xdotool search --name "Civilization II" >/dev/null 2>&1', check=False) == 0:
            break
        time.sleep(1)
    else:
        raise Fail('%s: no game window' % g.role)
    # the title sequence, then the start menu
    time.sleep(8 if g.slow else 3)
    g.wait_stable(timeout=60, still=3)
    g.shot('menu')


def to_network_menu(g, inet):
    g.step('multi', 'Down', 'Down', 'Down', 'Down', 'Down', 'Return')   # Multiplayer Game
    if inet:
        g.step('internet', 'Down', 'Down', 'Return')                      # Internet Game
    else:
        g.step('network', 'Down', 'Return')                               # Network Game
        g.step('lan', 'Return')                                           # TCP/IP


def host_setup(g, inet, name='Alice', game='TestGame', chat=False, rejoin=False):
    to_network_menu(g, inet)
    g.step('new', 'Return')                     # Start a New Multiplayer Game
    g.step('world', 'Up', 'Return')             # Small world
    g.step('difficulty', 'Return')
    g.step('civs', 'Down', 'Down', 'Down', 'Down', 'Return')   # 3 civilizations
    g.step('aggression', 'Return')
    g.step('rules', 'Return')                   # standard rules
    if rejoin:
        # [x] Open Game (Players can join during a game)
        g.click(*((76, 182) if g.kind == 'orig' else (79, 508)))
    if chat:
        # [x] All Humans Can Chat From Start (the original under Wine: a 640x480 window)
        g.click(*((76, 278) if g.kind == 'orig' else (79, 604)))
    g.step('features', 'Return')                # multiplayer features
    g.step('timer', 'Return')                   # turn timer: unlimited
    g.type(name)
    g.step('netname', 'Return')
    g.type(game)
    if inet:
        g.step('gamename', 'Return')            # -> Please Verify Your IP Address
    g.keys('Return')
    g.wait_stable(timeout=40)
    g.shot('lobby')                             # Available Players


def client_join(g, host, inet, name='Bob'):
    to_network_menu(g, inet)
    if inet:
        g.step('join', 'Down', 'Down', 'Down', 'Down', 'Down', 'Return')
        g.type(name)
        g.step('netname', 'Return')
        g.ex('xdotool key ctrl+a', check=False)
        g.type('127.0.0.1')
        g.step('address', 'Return')
    else:
        g.step('join', 'Down', 'Down', 'Down', 'Down', 'Down', 'Return')  # Join a Multiplayer Game
        g.type(name)
        g.keys('Return')
        # the game list fills from the host's NM_SERVER_INFO broadcasts
        end = time.time() + 60
        while time.time() < end and not any(
                m[1] == 'rx' and m[2] == 'udp' and m[4] == 408 for m in g.msgs()):
            time.sleep(1)
        g.wait_stable()
        g.shot('gamelist')
        g.keys('Return')                        # Join Game
    g.wait_msg('tx', nm('NM_PLAYER_LIST_NODE'), timeout=90, what='PLAYER_LIST_NODE')
    g.wait_stable()
    g.shot('joined')


def choose_civ(g):
    """gender, tribe, leader name, city style: the defaults (a client may
    not be asked all four: it is done when it has sent its NM_PLAYER_INFO)"""
    for what in ('gender', 'tribe', 'leader', 'style'):
        if g.role.startswith('client') and g.count('tx', nm('NM_PLAYER_INFO')):
            break
        g.wait_stable(timeout=60)
        g.step('after-' + what, 'Return')


MAIN_WINDOWS = re.compile(r'^(Civilization II.*|World|Status|.* Map \(.*\)|Default IME|.*Wine.*|Hot Join|New Player Receiving Game State|Local Area Network \(TCP/IP\)|Internet \(TCP/IP\)|)$')     # (waits: Hot Join, the host's while it sends a joining player the game, which closes by itself; Return = Cancel)


EXTRA = []      # a third player (--third): Games besides the host and the client


def popups(g, raw=False):
    """The titles of the game's dialogs showing now (not its main windows).
    The original under Wine: its top-level windows are X windows.  Ours:
    from the platform log (CreateWindowEx then the first child's parent
    gives the handle; ShowWindow shows and hides it)."""
    if g.kind == 'orig':
        out = g.ex('for w in $(xdotool search --onlyvisible --name . 2>/dev/null); do '
                   'xdotool getwindowname $w; done', check=False, capture=True)
        titles = out.splitlines()
        if raw:     # (the main window and the start menu have the same title)
            main = 'Civilization II Multiplayer Gold'
            return [t for t in titles if t != main] + [main] * (titles.count(main) - 1)
        return [t for t in titles if not MAIN_WINDOWS.match(t)]
    p = os.path.join(g.out, 'ours-%s.log' % g.role)
    try:
        with open(p, errors='replace') as f:
            f.seek(g.logpos)
            data = f.read()
    except OSError:
        return []
    cut = data.rfind('\n') + 1
    g.logpos += len(data[:cut].encode('utf-8', 'replace'))
    for line in data[:cut].splitlines():
        m = re.match(r'CreateWindowEx\(\w+, (\w+), "(.*)", (\w+), .*parent (\w+)\)$', line)
        if m:
            if g.pending is not None and m.group(4) not in g.wins:
                g.wins[m.group(4)] = g.pending
            g.pending = m.group(2) if m.group(1) == 'MSWindowClass' and m.group(3).startswith('8') else None
            continue
        m = re.match(r'ShowWindow\((\w+), (\d+)\)$', line)
        if m and m.group(1) in g.wins:
            if m.group(2) == '0':
                g.shown.discard(m.group(1))
            else:
                g.shown.add(m.group(1))
        m = re.match(r'DestroyWindow\((\w+)\)', line)
        if m:
            g.shown.discard(m.group(1))
    return [g.wins[h] for h in sorted(g.shown) if raw or not MAIN_WINDOWS.match(g.wins[h])]


def dismiss(g, titles):
    t = titles[-1]
    g.popped, g.last_pop = True, time.time()
    g.shot('popup')
    log(g.role, 'popup:', ', '.join(titles))
    g.keys('Escape' if t.startswith('City of') else 'Return')


def turn_actions(g, turn):
    """What we do in our turn TURN (no popup showing), then end it."""
    if turn == 1:
        g.step('move', 'KP_6')                  # the settler one square east
    elif turn == 2:
        g.step('build', 'b')                    # Build New City -> name it
        g.step('name', 'Return')                # -> Found New City, tutorial, city window
        end = time.time() + 60
        while time.time() < end:
            pops = popups(g)
            if pops:
                dismiss(g, pops)
            elif g.wait_stable(timeout=10, still=3) and not popups(g):
                break
        g.step('citywin', 'Escape')             # the city window (ours: not in popups())
    else:
        g.keys('s')                             # sentry a unit if one is waiting
    g.keys('ctrl+n')                            # End Player Turn


def my_turn_over(g):
    t = g.turns()
    mine = [i for i, x in enumerate(t) if x[1] == g.civ]
    return bool(mine) and any(x[1] != g.civ for x in t[mine[-1] + 1:])


def play(host, client, nturns, opts, cont=False):
    """NTURNS turns each (CONT: N more, counting from the turns in the logs)."""
    games = {'host': host, 'client': client}
    games.update((g.role, g) for g in EXTRA)
    # whose civ: a client's own PLAYER_INFO names it (args[0]); the host is
    # the other human
    for g in games.values():
        if g is host:
            continue
        for m in g.msgs():
            if m[1] == 'tx' and m[3] == nm('NM_PLAYER_INFO') and len(m[6]) >= 20:
                g.civ = int.from_bytes(m[6][16:20], 'little')
    if client.civ is None:      # (a loaded game: the second civilization)
        client.civ = 2
    host.civ = min({1, 2, 3, 4} - {g.civ for g in games.values() if g is not host})
    log('civs:', ', '.join('%s %s' % (r, g.civ) for r, g in games.items()))
    acted = {r: 0 for r in games}
    if cont:
        acted = {r: sum(1 for x in g.turns() if x[1] == g.civ) for r, g in games.items()}
    target = {r: acted[r] + nturns for r in acted}
    since = {r: 0 for r in games}
    end = time.time() + 300 + 300 * nturns
    while True:
        for g in games.values():
            if not g.alive():
                raise Fail('%s: the game is gone (turns %s)' % (g.role, acted))
        if all(acted[r] >= target[r] for r in acted) and all(
                my_turn_over(g) or sum(1 for x in g.turns() if x[1] == g.civ) > acted[r] for r, g in games.items()):
            break
        if time.time() > end:
            raise Fail('turns: not done in time (%s)' % acted)
        for role, g in games.items():
            pops = popups(g)
            if pops:
                dismiss(g, pops)
                time.sleep(1.5 if g.slow else 0.8)
                continue
            mine = sum(1 for x in g.turns() if x[1] == g.civ)
            if mine > acted[role] and acted[role] < target[role]:
                # our turn: once its 'It is our turn to move' popup has gone
                # (the turn's set-up done) and the screen has settled, act
                if g.turn_seen != mine:
                    g.turn_seen, g.turn_t = mine, time.time()
                    g.popped = time.time() - g.last_pop < 20     # (its popup may come first)
                if not g.popped and time.time() - g.turn_t < 90:
                    continue
                if not g.wait_stable(timeout=20) or popups(g):
                    continue
                acted[role] += 1
                since[role] = time.time()
                log(role, 'turn', acted[role])
                g.shot('turn%d' % acted[role])
                turn_actions(g, acted[role])
                if acted[role] == 2 and role == 'host' and opts.save:
                    save(g)
            elif mine == acted[role] and mine and not my_turn_over(g) and time.time() - since[role] > 25:
                # still our turn: the end-of-turn key was lost (a popup took it)
                log(role, 'turn %d: still ours, ending it again' % acted[role])
                g.shot('stillturn')
                since[role] = time.time()
                g.keys('Escape', 'Return', 'ctrl+n')   # a city window; 'End of Turn (Press ENTER)'
        time.sleep(1)
    log('turns done', acted)


def rejoin(host, client, opts):
    """The client leaves the game (Quit), starts again and joins the game
    in progress (an open game), takes a civilization; one more turn each."""
    quit_one(client)
    host.wait_msg('rx', nm('NM_QUIT_REQUEST'), timeout=60, what='QUIT_REQUEST')
    settle(host, 30)
    for f in ('xdlog-client.txt', 'ours-client.log', 'wine-client.log'):
        p = os.path.join(client.out, f)
        if os.path.exists(p):
            os.rename(p, p[:-4] + '-left' + p[-4:])
    client.logpos, client.wins, client.shown, client.pending = 0, {}, set(), None
    client.turn_seen, client.turn_t, client.popped, client.last_pop = 0, 0, False, 0
    log('client: joining again')
    start(client, opts.inet)
    client_join(client, host, opts.inet)
    end = time.time() + 300
    while time.time() < end and not client.count('tx', nm('NM_PLAYER_INFO')):
        for g in (client, host):
            if g.wait_stable(timeout=8, still=2):
                pops = popups(g)
                if pops and not any('Waiting' in t or 'TCP' in t for t in pops):
                    g.shot('rejoin')
                    log(g.role, 'rejoin:', ', '.join(pops))
                    g.keys('Return')
        time.sleep(1)
    if not client.count('tx', nm('NM_PLAYER_INFO')):
        raise Fail('client: not back in the game')
    client.civ = None
    log('client: back in the game')
    if opts.stop_after == 'rejoin':
        raise Fail('stopped after rejoin')
    play(host, client, 1, opts, cont=True)


def wait_popup(g, pred, timeout=30):
    end = time.time() + timeout
    while time.time() < end:
        pops = popups(g)
        if any(pred(t) for t in pops):
            return pops
        time.sleep(1)
    g.shot('nopopup')
    raise Fail('%s: no dialog %s' % (g.role, getattr(pred, '__doc__', '') or ''))


def diplomacy(host, client):
    """The host (ours: the clicks are at our layout) sends an emissary
    (Foreign Minister), the client grants the audience, the host offers a
    peace treaty, the client (ours) accepts it; both end the negotiations.
    Checked: NM_PARLEYREQUEST_REPLY, NM_PARLEY_TRANSACTION and
    NM_PARLEY_ACCEPT_OFFER on the wire."""
    settle(host, 40)
    settle(client, 40)
    host.keys('F3')
    wait_popup(host, lambda t: t == 'Foreign Minister')
    host.shot('foreign')
    host.click(404, 511)                        # Send Emissary
    wait_popup(client, lambda t: '(' in t)      # 'Dictator Caesar of the Romans (Icy)'
    client.shot('audience')
    client.keys('Down', 'Return')               # "Granted" (within the 15 s it waits)
    pops = wait_popup(host, lambda t: t.startswith('Opponent'))
    host.shot('granted')
    host.keys('Return')
    time.sleep(3)
    host.click(510, 400)                        # Offer Treaty: Continue
    time.sleep(2)
    host.click(131, 275)                        # Peace Treaty
    host.click(510, 400)                        # Transmit Offer
    host.wait_msg('tx', nm('NM_PARLEY_TRANSACTION'), timeout=30, what='PARLEY_TRANSACTION')
    client.wait_msg('rx', nm('NM_PARLEY_TRANSACTION'), timeout=30, what='PARLEY_TRANSACTION')
    time.sleep(3)
    client.shot('offer')
    if client.kind == 'ours':
        client.click(246, 400)                  # Accept Offer
        client.wait_msg('tx', nm('NM_PARLEY_ACCEPT_OFFER'), timeout=30, what='PARLEY_ACCEPT_OFFER')
        time.sleep(3)
        client.shot('accepted')
        host.shot('accepted')
    for g in (host, client):
        settle(g, 20)
        g.click(511, 661)                       # End Negotiations
        time.sleep(2)
        settle(g, 20)
    log('diplomacy done')


def chat(host, client):
    """Chat with Kings both ways (ours: the clicks are at our layout): the
    client writes to the host, the host's chat window opens and it answers."""
    for g in (client, host):
        settle(g, 40)
    for g, other, text in ((client, host, 'hello from Bob'), (host, client, 'hi Bob, Alice here')):
        if g.kind != 'ours':
            continue
        n = g.count('tx', nm('NM_CHAT'))
        r = other.count('rx', nm('NM_CHAT'))
        if g is client or not other.count('tx', nm('NM_CHAT')):
            g.keys('ctrl+c')                    # (the host's opens by itself on a message)
        time.sleep(3)
        g.click(188, 251)                       # [x] Send (to the one other king)
        g.click(400, 350)
        g.type(text)
        g.click(870, 333)                       # Send
        g.wait_msg('tx', nm('NM_CHAT'), n + 1, timeout=30, what='CHAT')
        other.wait_msg('rx', nm('NM_CHAT'), r + 1, timeout=30, what='CHAT')
        time.sleep(3)
        g.shot('chat')
        other.shot('chat')
    for g in (client, host):
        if g.kind == 'ours':
            g.click(511, 661)                   # End Chat
            time.sleep(2)
    log('chat done')


def save(g):
    """Game menu: Save Game, the name it proposes; the file is copied to
    the run's directory as saved.net (for --load)."""
    settle(g, 30)
    g.step('save', 'ctrl+s')
    g.step('saved', 'Return')
    settle(g, 20)
    d = '/tmp/g' if g.kind == 'orig' else '/tmp/ours%d' % g.disp
    g.ex('cp "$(ls -t %s/*.net | head -1)" %s/saved.net' % (d, g.out.replace(ROOT, '/work')))
    if not os.path.exists(os.path.join(g.out, 'saved.net')):
        raise Fail('%s: no saved game' % g.role)
    log(g.role, 'saved the game')


def host_load(g, inet, name='Alice', game='LoadedGame'):
    """Load a Saved Multiplayer Game (saved.net), then as a new game."""
    to_network_menu(g, inet)
    g.step('load', 'Down', 'Down', 'Down', 'Down', 'Return')
    time.sleep(2)
    g.type('saved.net')
    g.step('loadfile', 'Return')
    g.type(name)
    g.step('netname', 'Return')
    g.type(game)
    if inet:
        g.step('gamename', 'Return')
    g.keys('Return')
    g.wait_stable(timeout=40)
    g.shot('lobby')


def start_loaded(host, client):
    """After the join: civilizations from the saved game (the defaults),
    names; until the host starts the first turn."""
    end = time.time() + 300
    while time.time() < end and host.count('tx', nm('NM_START_WHOSE_TURN')) == 0:
        for g in (host, client):
            if g.wait_stable(timeout=8, still=2):
                pops = popups(g)
                if pops and not any('Waiting' in t or 'TCP' in t for t in pops):
                    g.shot('setup')
                    log(g.role, 'set-up:', ', '.join(pops))
                    g.keys('Return')
        time.sleep(1)
    if host.count('tx', nm('NM_START_WHOSE_TURN')) == 0:
        raise Fail('the loaded game did not start')


def settle(g, secs=60):
    """Dismiss the dialogs showing until none comes for a moment."""
    end = time.time() + secs
    while time.time() < end:
        pops = popups(g)
        if pops:
            dismiss(g, pops)
            time.sleep(1)
        elif g.wait_stable(timeout=10, still=2) and not popups(g):
            return


def quit_one(g):
    """Game menu: Quit, 'Do you really want to quit?' Yes; then whatever
    else it asks, until the game has gone."""
    settle(g, 30)
    g.keys('Escape')                            # a city window
    for attempt in range(4):                    # (a key can be lost while the game is busy)
        settle(g, 20)
        g.keys('ctrl+q')
        end = time.time() + 15
        while time.time() < end and not popups(g):
            time.sleep(1)
        if 'Confirmation' in popups(g):
            break
        pops = popups(g)
        if pops:                                # (another dialog came first)
            dismiss(g, pops)
        else:
            g.keys('Escape')
    g.shot('quit')
    g.keys('Down', 'Return')                    # Yes
    # a network game ends at the start menu: Cancel there leaves the game
    end = time.time() + 90
    while time.time() < end and g.alive():
        pops = popups(g)
        if pops:                                # (Escape: from the set-up menus back out)
            g.shot('popup')
            log(g.role, 'quitting:', ', '.join(pops))
            g.keys('Escape')
            time.sleep(1)
        elif 'Civilization II Multiplayer Gold' in popups(g, raw=True):
            g.wait_stable()
            g.shot('menu-again')
            g.keys('Escape')
            time.sleep(3)
        time.sleep(2)
    if g.alive():
        g.shot('still-running')
        raise Fail('%s: still running after Quit' % g.role)
    log(g.role, 'quit')


def quit_games(host, client):
    n = host.count('rx', nm('NM_QUIT_REQUEST'))
    for g in EXTRA + [client]:
        quit_one(g)
        n += 1
        host.wait_msg('rx', nm('NM_QUIT_REQUEST'), n, timeout=60, what='QUIT_REQUEST')
    quit_one(host)


# ---- checks ----

EXPECT_CLIENT_TX = ['NM_PLAYER_LIST_NODE', 'NM_LOCK_NATION', 'NM_PLAYER_INFO', 'NM_CREATE_CITY',
                    'NM_TURN_FINISHED', 'NM_QUIT_REQUEST']
EXPECT_HOST_TX = ['NM_PLAYER_LIST', 'NM_GAME_GOING', 'NM_SERVER_PATH', 'NM_JOIN_GAMESTATE', 'NM_LOCK_DATA',
                  'NM_NATION_ACCEPT', 'NM_MAP_STRUCT', 'NM_START_CIVILIZATION', 'NM_COSMIC', 'NM_ATTITUDES',
                  'NM_READY_TO_START', 'NM_START_WHOSE_TURN', 'NM_CITY_CREATED']


def subsequence(have, want):
    i = 0
    for h in have:
        if i < len(want) and h == want[i]:
            i += 1
    return want[i:]


def relay_check(games, rep):
    """Three players: the host relays.  Every message a game received was
    sent by another (same type, sequence number and bytes); every message a
    client sent to everyone (to=255) reached both others (but for the
    last few, when one had left)."""
    sent = {}
    for g in games:
        for m in xdmsgs.parse(g.xdlog):
            d = xdmsgs.describe(m)
            if d and m['dir'] == 'tx' and m['chan'] == 'tcp':
                sent.setdefault((d[0], d[2], m['data']), []).append((g, m['to']))
    for g in games:
        got = [(xdmsgs.describe(m), m['data']) for m in xdmsgs.parse(g.xdlog)
               if m['dir'] == 'rx' and m['chan'] == 'tcp']
        unknown = [d for d, data in got if d and (d[0], d[2], data) not in sent]
        rep(not unknown, '%s: all %d received messages were sent by another game%s' % (
            g.role, len(got), '' if not unknown else ' (%d not, the first %s)' % (len(unknown), unknown[0][:3])))
    for g in games:
        if g.role == 'host':
            continue
        allm = [(d[0], d[2], m['data']) for m in xdmsgs.parse(g.xdlog)
                for d in [xdmsgs.describe(m)] if d and m['dir'] == 'tx' and m['chan'] == 'tcp' and m['to'] == 255]
        for o in games:
            if o is g:
                continue
            rx = {(d[0], d[2], m['data']) for m in xdmsgs.parse(o.xdlog)
                  for d in [xdmsgs.describe(m)] if d and m['dir'] == 'rx' and m['chan'] == 'tcp'}
            missed = [k for k in allm if k not in rx]
            rep(len(missed) <= 3, '%s -> %s: %d of %d messages to everyone received' % (
                g.role, o.role, len(allm) - len(missed), len(allm)))


def check(host, client, nturns, result, opts=None):
    ok = True

    def rep(good, text):
        nonlocal ok
        ok &= good
        result.append(('PASS ' if good else 'FAIL ') + text)

    everyone = [host, client] + EXTRA
    for g in everyone:
        r = subprocess.run([sys.executable, os.path.join(ROOT, 'tools/xdnet/xdmsgs.py'), g.xdlog, '--check'],
                           stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        text = r.stdout.decode(errors='replace')
        open(os.path.join(g.out, 'msgs-%s.txt' % g.role), 'w').write(text)
        rep(r.returncode == 0, '%s: records well formed (%d messages)%s' % (
            g.role, text.count('\n'), '' if r.returncode == 0 else ': ' + '; '.join(
                l for l in text.splitlines() if l.startswith('FAIL'))[:300]))
    if EXTRA:
        relay_check(everyone, rep)
    # what each sent over TCP the other received, in order, byte for byte
    for a, b in (((host, client), (client, host)) if not EXTRA else ()):
        sent = [(m[3], m[5], m[6]) for m in a.msgs() if m[1] == 'tx' and m[2] == 'tcp']
        got = [(m[3], m[5], m[6]) for m in b.msgs() if m[1] == 'rx' and m[2] == 'tcp']
        if got and got[0] in sent:      # (a client that joined again: from its first message)
            sent = sent[sent.index(got[0]):]
        elif sent and sent[0] in got:   # (the host heard the client's first game as well)
            got = got[len(got) - 1 - got[::-1].index(sent[0]):]
        # the last few may still be in flight when a game quits
        n = min(len(sent), len(got))
        same = sent[:n] == got[:n]
        first = next((i for i in range(n) if sent[i] != got[i]), None)
        # (what the host sent after the client had left is not received)
        left = b.role == 'client' and b.count('tx', nm('NM_QUIT_REQUEST')) > 0
        rep(same and (len(got) >= len(sent) - 3 or left), '%s -> %s: %d sent, %d received, %s%s' % (
            a.role, b.role, len(sent), len(got), 'identical' if same else 'first difference at #%d: %s / %s' % (
                first, sent[first][:2], got[first][:2]),
            ' (the rest after it left)' if left and len(got) < len(sent) else ''))
    for g in everyone:
        t = sum(1 for x in g.turns() if x[1] == 0)
        want = 1 if g is client and opts is not None and opts.rejoin else nturns   # (since it joined again)
        rep(t >= want, '%s: reached turn %d (want %d)' % (g.role, t, want))
    expect_client = EXPECT_CLIENT_TX
    if opts is not None and opts.rejoin:
        expect_client = ['NM_PLAYER_LIST_NODE', 'NM_TURN_FINISHED', 'NM_QUIT_REQUEST']
    for g, want in [(c, expect_client) for c in [client] + EXTRA] + [(host, EXPECT_HOST_TX)]:
        have = [xdmsgs.NAMES.get(m[3]) for m in g.msgs() if m[1] == 'tx' and m[2] == 'tcp']
        missing = subsequence(have, want)
        rep(not missing, '%s: sent %s in order%s' % (g.role, ' '.join(w[3:] for w in want),
                                                    '' if not missing else ' (missing from %s)' % missing[0]))
    want = []
    if opts is not None and opts.chat:
        want += [(g, 'NM_CHAT') for g in (host, client) if g.kind == 'ours']
    if opts is not None and opts.diplo:
        want += [(client, 'NM_PARLEYREQUEST_REPLY'), (host, 'NM_PARLEY_TRANSACTION')]
        if client.kind == 'ours':
            want.append((client, 'NM_PARLEY_ACCEPT_OFFER'))
    for g, name in want:
        other = client if g is host else host
        rep(g.count('tx', nm(name)) > 0 and other.count('rx', nm(name)) > 0,
            '%s -> %s: %s' % (g.role, other.role, name[3:]))
    for g in everyone:
        problems = []
        for f in os.listdir(g.out):
            p = os.path.join(g.out, f)
            if f.startswith('asan-%s.' % g.role):
                problems.append('ASan report %s' % f)
            if f in ('wine-%s.log' % g.role, 'ours-%s.log' % g.role):
                t = open(p, errors='replace').read()
                bad = [l for l in t.splitlines() if re.search(
                    r'Unhandled|AddressSanitizer|Segmentation|^fatal:|^civ2: |SIGSEGV|SIGABRT', l)]
                if bad:
                    problems.append('%s: %s' % (f, bad[0][:200]))
        rep(not problems, '%s: no crash%s' % (g.role, '' if not problems else ': ' + '; '.join(problems)))
    return ok


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('pairing', choices=['ours-ours', 'ours-orig', 'orig-ours', 'orig-orig'])
    ap.add_argument('--turns', type=int, default=3)
    ap.add_argument('--run')
    ap.add_argument('--exe', default='civ2-linux32')
    ap.add_argument('--exe-host', help='our build for the host only (e.g. ASan on one side: memory)')
    ap.add_argument('--exe-client')
    ap.add_argument('--gdb', choices=['host', 'client', 'both'], help='run our game(s) under gdb: a backtrace on a crash or fatal error')
    ap.add_argument('--rejoin', action='store_true', help='after the turns the client leaves and joins again (an open game), one more turn')
    ap.add_argument('--third', choices=['ours', 'orig'], help='a third player (LAN), joining after the client: the host relays')
    ap.add_argument('--inet', action='store_true')
    ap.add_argument('--keep', action='store_true')
    ap.add_argument('--sniff', action='store_true')
    ap.add_argument('--save', action='store_true', help='the host saves the game in its turn 2')
    ap.add_argument('--load', action='store_true', help='then (after quitting) the host loads that game, the client joins, N more turns (implies --save)')
    ap.add_argument('--chat', action='store_true', help='host: chat from the start; the client chats in its turn 2')
    ap.add_argument('--diplo', action='store_true', help='after the turns: emissary, audience, peace treaty (implies --chat: contact)')
    ap.add_argument('--stop-after', choices=['lobby', 'join', 'civ', 'turns', 'rejoin'], help='stop there (with --keep: drive by hand)')
    opts = ap.parse_args()
    opts.chat = opts.chat or opts.diplo
    opts.save = opts.save or opts.load
    kh, kc = opts.pairing.split('-')
    run = opts.run or 'test-%s%s' % (opts.pairing, '-inet' if opts.inet else '')
    out = os.path.join(ROOT, 'run/xd/cap', run)
    if os.path.exists(out):
        sh('rm', '-rf', out)
    os.makedirs(os.path.join(out, 'shots'))
    # two containers: the bridge gives each its address (LAN); for Internet
    # mode the client shares the host's network namespace and uses :8
    docker_up('xdh', 'civ2-wine2')
    docker_up('xdc', 'civ2-wine', net='xdh' if opts.inet else None)
    sniffer = None
    if opts.sniff:
        sh('docker', 'rm', '-f', 'xdsniff', check=False)
        sh('docker', 'run', '-d', '--name', 'xdsniff', '--network', 'container:xdh', '--user', 'root', '-v',
           '%s:/work' % ROOT, 'civ2-dev', 'python3', '-I', '/work/tools/xdnet/sniff.py',
           '/work/run/xd/cap/%s/capture.pcap' % run)
        sniffer = 'xdsniff'
    host = Game(kh, 'host', 'xdh', 7, run, opts.exe_host or opts.exe)
    client = Game(kc, 'client', 'xdc', 8 if opts.inet else 7, run, opts.exe_client or opts.exe)
    host.gdb = opts.gdb in ('host', 'both')
    client.gdb = opts.gdb in ('client', 'both')
    if opts.third:
        # a third player (LAN only): its own container; an original needs a
        # Wine prefix the other games' originals don't use
        vols = [v for v, g in (('civ2-wine2', host), ('civ2-wine', client)) if g.kind != 'orig']
        if opts.third == 'orig' and not vols:
            raise SystemExit('--third orig: both Wine prefixes are in use')
        docker_up('xdc2', vols[0] if vols else 'civ2-wine')
        third = Game(opts.third, 'client2', 'xdc2', 7, run, opts.exe_client or opts.exe)
        third.gdb = False
        EXTRA.append(third)
    result = []
    ok = False
    try:
        log('starting', opts.pairing)
        start(host, opts.inet)
        start(client, opts.inet)
        for g in EXTRA:
            start(g, opts.inet)
        log('host: new game')
        host_setup(host, opts.inet, chat=opts.chat, rejoin=opts.rejoin)
        if opts.stop_after == 'lobby':
            raise Fail('stopped after lobby')
        log('client: join')
        client_join(client, host, opts.inet)
        for g in EXTRA:
            log('%s: join' % g.role)
            client_join(g, host, opts.inet)
        host.wait_msg('rx', nm('NM_PLAYER_LIST_NODE'), 1 + len(EXTRA), timeout=60, what='PLAYER_LIST_NODE')
        host.wait_stable()
        host.step('players', 'Return')              # Start Game
        host.step('profile', 'Return')              # Game Profile: OK
        for g in [client] + EXTRA:
            g.wait_msg('rx', nm('NM_JOIN_GAMESTATE'), timeout=60, what='JOIN_GAMESTATE')
            g.wait_stable()
            g.step('profile', 'Return')
        if opts.stop_after == 'join':
            raise Fail('stopped after join')
        log('choosing civilizations')
        choose_civ(host)
        choose_civ(client)
        for g in EXTRA:
            choose_civ(g)
        log('building the world')
        host.wait_msg('tx', nm('NM_READY_TO_START'), timeout=600, what='READY_TO_START')
        if opts.stop_after == 'civ':
            raise Fail('stopped after civ')
        play(host, client, opts.turns, opts)
        if opts.rejoin:
            rejoin(host, client, opts)
        if opts.chat:
            chat(host, client)
        if opts.diplo:
            diplomacy(host, client)
        if opts.stop_after == 'turns':
            raise Fail('stopped after turns')
        log('quitting')
        quit_games(host, client)
        if opts.load:
            # the game saved in it, loaded by the host, the client joining
            check(host, client, opts.turns, result, opts)
            result[:] = [r[:5] + 'game 1: ' + r[5:] for r in result]
            for g in (host, client):
                for f in os.listdir(out):
                    if f.startswith(('xdlog-', 'msgs-')) and not f.endswith('-game1.txt'):
                        os.rename(os.path.join(out, f), os.path.join(out, f[:-4] + '-game1.txt'))
                g.logpos, g.wins, g.shown, g.pending = 0, {}, set(), None
                g.turn_seen, g.turn_t, g.popped, g.last_pop = 0, 0, False, 0
            for f in os.listdir(out):
                if f.startswith('ours-') and not f.endswith('-game1.log'):
                    os.rename(os.path.join(out, f), os.path.join(out, f[:-4] + '-game1.log'))
            log('loading the saved game')
            start(host, opts.inet, save=os.path.join(out, 'saved.net'))
            start(client, opts.inet)
            host_load(host, opts.inet)
            client_join(client, host, opts.inet)
            host.wait_msg('rx', nm('NM_PLAYER_LIST_NODE'), timeout=60, what='PLAYER_LIST_NODE')
            host.wait_stable()
            host.step('players', 'Return')
            host.step('profile', 'Return')
            client.wait_msg('rx', nm('NM_JOIN_GAMESTATE'), timeout=60, what='JOIN_GAMESTATE')
            client.wait_stable()
            client.step('profile', 'Return')
            start_loaded(host, client)
            opts.chat = opts.diplo = opts.save = False
            play(host, client, opts.turns, opts)
            log('quitting the loaded game')
            quit_games(host, client)
    except Fail as e:
        result.append('FAIL ' + str(e))
        log('FAIL', e)
        for g in (host, client):
            try:
                g.shot('fail')
            except Exception:
                pass
    except KeyboardInterrupt:
        result.append('FAIL interrupted')
    finally:
        if sniffer:
            sh('docker', 'stop', sniffer, check=False)
            sh('docker', 'rm', '-f', sniffer, check=False)
            pc = os.path.join(out, 'capture.pcap')
            if os.path.exists(pc):
                with open(os.path.join(out, 'records.txt'), 'w') as f:
                    subprocess.run([sys.executable, '-I', os.path.join(ROOT, 'tools/xdnet/xdparse.py'), pc], stdout=f)
        ok = check(host, client, opts.turns, result, opts) and not any(r.startswith('FAIL') for r in result)
        if not opts.keep:
            sh('docker', 'rm', '-f', 'xdc2', check=False)
            sh('docker', 'rm', '-f', 'xdc', check=False)
            sh('docker', 'rm', '-f', 'xdh', check=False)
    result.append('%s %s %s (%d turns, %s)' % ('PASS' if ok else 'FAIL', opts.pairing,
                                                'inet' if opts.inet else 'lan', opts.turns, opts.exe))
    open(os.path.join(out, 'result.txt'), 'w').write('\n'.join(result) + '\n')
    print('\n'.join(result))
    sys.exit(0 if ok else 1)


if __name__ == '__main__':
    main()
