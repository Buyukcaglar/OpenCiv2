# Parse an XDaemon capture: UDP 4994 datagrams and TCP 4993 streams -> records.
# usage: xdparse.py capture.pcap [names_file]
import struct, sys, re
f = open(sys.argv[1], 'rb'); f.read(24)
names = {}
try:
    src = open('/home/labaron/code/civ2/src/data/gamedata.cpp', encoding='latin1').read()
    m = re.search(r'char str_nm_datagram\[\d+\] = "(.*?)";', src)
    raw = m.group(1).encode().decode('unicode_escape').encode('latin1')
    for i in range(len(raw) // 32 + 1):
        names[i] = raw[i*32:i*32+32].split(b'\0')[0].decode()
except Exception as e:
    print('names:', e)
streams = {}; t0 = None; out = []
def game(pl):
    if len(pl) >= 16 and pl[:4] == b'\x60\x66\x60\x66':
        mag, typ, size, seq = struct.unpack('<IiII', pl[:16])
        return 'NM %d %s size=%d seq=%d' % (typ, names.get(typ, '?'), size, seq)
    return 'raw ' + pl[:16].hex()
while True:
    h = f.read(16)
    if len(h) < 16: break
    ts, us, cl, ol = struct.unpack('<IIII', h); d = f.read(cl)
    t = ts + us / 1e6; t0 = t0 or t
    if struct.unpack('>H', d[12:14])[0] != 0x0800: continue
    ip = d[14:]; ihl = (ip[0] & 15) * 4; proto = ip[9]
    src = '.'.join(map(str, ip[12:16])); dst = '.'.join(map(str, ip[16:20]))
    tot = struct.unpack('>H', ip[2:4])[0]; l4 = ip[ihl:tot]
    if proto == 17:
        sp, dp = struct.unpack('>HH', l4[:4]); pl = l4[8:]
        hdr = struct.unpack('<I', pl[:4])[0]
        out.append('%8.3f UDP %s:%d>%s:%d dlen=%d hdr=%08x payload=%d %s' % (t - t0, src, sp, dst, dp, len(pl), hdr, len(pl) - 4, game(pl[4:])))
    elif proto == 6:
        sp, dp, seq, ack, off = struct.unpack('>HHIIB', l4[:13]); fl = l4[13]
        pl = l4[(off >> 4) * 4:]
        key = (src, sp, dst, dp)
        st = streams.setdefault(key, {'buf': b'', 'isn': None})
        if fl & 2: st['isn'] = seq + 1; out.append('%8.3f TCP %s:%d>%s:%d SYN%s' % (t - t0, src, sp, dst, dp, '+ACK' if fl & 16 else '')); continue
        if fl & 1: out.append('%8.3f TCP %s:%d>%s:%d FIN' % (t - t0, src, sp, dst, dp))
        if fl & 4: out.append('%8.3f TCP %s:%d>%s:%d RST' % (t - t0, src, sp, dst, dp))
        if not pl: continue
        st['buf'] += pl  # (no retransmissions expected on a local bridge)
        while len(st['buf']) >= 12:
            total, tag, plen = struct.unpack('<III', st['buf'][:12])
            if len(st['buf']) < total: break
            rec = st['buf'][:total]; st['buf'] = st['buf'][total:]
            body = rec[12:12 + plen]; pad = rec[12 + plen:]
            tgt = (tag >> 16) & 0xff; srcid = tag >> 24; fl16 = tag & 0xffff
            out.append('%8.3f TCP %s:%d>%s:%d rec total=%d tag=%08x (src=%d dst=%d flags=%d) len=%d pad=%d%s %s' % (
                t - t0, src, sp, dst, dp, total, tag, srcid, tgt, fl16, plen, len(pad), '' if total % 64 == 0 else ' NOT64', game(body) if plen != 2 else 'id=' + body.hex()))
print('\n'.join(out))
