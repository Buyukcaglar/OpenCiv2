# The game messages in an XDaemon log (ours: CIV2_XDLOG; the original's: the
# log proxy's XDLOG), one line each: ms, tx/rx, channel, type, name, size,
# sequence, and for some types the interesting field.
# usage: xdmsgs.py XDLOG [--tcp] [--check]
#   --check: also verify the records are well formed (header magic, size as
#   given by the call, ...); exit status 1 and a FAIL line on a problem.
import re, struct, sys

NAMES = {}
def load_names():
    try:
        import os
        src = open(os.path.join(os.path.dirname(os.path.abspath(__file__)), '../../src/data/gamedata.cpp'), encoding='latin1').read()
        m = re.search(r'char str_nm_datagram\[\d+\] = "(.*?)";', src)
        raw = m.group(1).encode().decode('unicode_escape').encode('latin1')
        for i in range(len(raw) // 32 + 1):
            NAMES[i] = raw[i*32:i*32+32].split(b'\0')[0].decode()
    except Exception:
        pass

CALL = re.compile(r'^\s*(\d+)(?: t\w+)? (XD_SendSecureData|XD_SendBroadcastData|CB SecureReceive|CB BroadcastReceive)\((.*?)\)?(?: = (-?\d+))?\s*$|^\s*(\d+)(?: t\w+)? (CB SecureReceive|CB BroadcastReceive) (.*)$')
HEX = re.compile(r'^\s*(\d+)(?: t\w+)?\s+(tx|rx) ([0-9a-f]{4}): ([0-9a-f]+)\s*$')

def parse(path):
    """-> list of dicts: t, dir, chan, size (from the call), data (bytes)"""
    msgs = []; cur = None
    for line in open(path, errors='replace'):
        m = HEX.match(line)
        if m:
            if cur is not None and m.group(2) == cur['dir']:
                off = int(m.group(3), 16)
                if off == len(cur['data']):
                    cur['data'] += bytes.fromhex(m.group(4))
            continue
        cur = None
        if 'XD_Send' in line or 'CB SecureReceive' in line or 'CB BroadcastReceive' in line:
            t = int(line.split()[0])
            d = 'tx' if 'XD_Send' in line else 'rx'
            chan = 'udp' if 'Broadcast' in line else 'tcp'
            sm = re.search(r'size=(\d+)', line)
            tm = re.search(r'to=(\d+)', line)
            cur = {'t': t, 'dir': d, 'chan': chan, 'size': int(sm.group(1)) if sm else -1, 'data': b'', 'line': line.strip(),
                   'to': int(tm.group(1)) if tm else None}
            msgs.append(cur)
    return msgs

def describe(m):
    d = m['data']
    if len(d) < 16 or d[:4] != b'\x60\x66\x60\x66':
        return None
    mag, typ, size, seq = struct.unpack('<IiII', d[:16])
    extra = ''
    if typ == 105 and len(d) >= 20:
        extra = 'civ=%d' % struct.unpack('<i', d[16:20])
    elif len(d) >= 0x2c and typ not in (0,):
        a = struct.unpack('<6i', d[16:40])
        extra = 'args=' + ','.join(str(x) for x in a)
    return typ, size, seq, extra

def check_diff(d):
    """NM_DIFFERENCE_ENGINE / NM_ALPHA_DIFFERENCE_ENGINE: args[0] records of
    [u32 section (0x8000: RLE)][u32 offset][u32 size][size bytes]; an RLE
    stream is [u16 n < 0x7fff][byte] runs and [u16 0x8000 + n][n bytes]
    literals (diffeng_rle_decode).  -> a problem, or None."""
    size = struct.unpack('<I', d[8:12])[0]
    if len(d) < size:
        return None                     # (the log has only the start)
    n = struct.unpack('<i', d[16:20])[0]
    p = 0x2c
    for i in range(n):
        if p + 12 > size:
            return 'record %d of %d past the end' % (i, n)
        sid, off, sz = struct.unpack('<III', d[p:p + 12])
        p += 12
        if p + sz > size:
            return 'record %d: %d bytes past the end' % (i, p + sz - size)
        if sid & 0x8000:
            q, e = p, p + sz
            while q < e:
                if q + 2 > e:
                    return 'record %d: RLE stream ends inside a code' % i
                c = struct.unpack('<H', d[q:q + 2])[0]
                q += 3 if c < 0x7fff else 2 + ((c - 0x8000) & 0xffff)
            if q != e:
                return 'record %d: RLE stream overruns by %d' % (i, q - e)
        p += sz
    if p != size:
        return '%d bytes after the records' % (size - p)
    return None


def main():
    load_names()
    args = sys.argv[1:]
    check = '--check' in args; tcp_only = '--tcp' in args
    path = [a for a in args if not a.startswith('--')][0]
    bad = 0
    for m in parse(path):
        if tcp_only and m['chan'] != 'tcp':
            continue
        r = describe(m)
        if r is None:
            if m['data']:
                print('%8d %s %s raw %s' % (m['t'], m['dir'], m['chan'], m['data'][:16].hex()))
            if check and m['data']:
                print('FAIL not a game message: %s' % m['line']); bad += 1
            continue
        typ, size, seq, extra = r
        print('%8d %s %s %3d %-28s size=%d seq=%d %s' % (m['t'], m['dir'], m['chan'], typ, NAMES.get(typ, '?'), size, seq, extra))
        if check:
            if m['size'] >= 0 and size != m['size']:
                print('FAIL size %d in header, %d given to the call: %s' % (size, m['size'], m['line'])); bad += 1
            if typ in (21, 92) and m['chan'] == 'tcp':
                prob = check_diff(m['data'])
                if prob:
                    print('FAIL %s: %s' % (NAMES.get(typ), prob)); bad += 1
            if not (0 <= typ < max(NAMES or {0: 0}) + 1):
                print('FAIL unknown type %d' % typ); bad += 1
            if m['size'] >= 0 and len(m['data']) not in (m['size'], min(m['size'], len(m['data']))):
                pass
    sys.exit(1 if bad else 0)

if __name__ == '__main__':
    main()
