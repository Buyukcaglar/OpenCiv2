# Dump a pcap (ethernet) as one line per packet: time, proto, src->dst, flags, len, payload hex (first N bytes).
import struct, sys
f = open(sys.argv[1], 'rb'); N = int(sys.argv[2]) if len(sys.argv) > 2 else 64
skip_udp_bcast = '--no-bcast' in sys.argv
f.read(24); t0 = None
while True:
    h = f.read(16)
    if len(h) < 16: break
    ts, us, cl, ol = struct.unpack('<IIII', h); d = f.read(cl)
    t = ts + us / 1e6; t0 = t0 or t
    if struct.unpack('>H', d[12:14])[0] != 0x0800: continue
    ip = d[14:]; ihl = (ip[0] & 15) * 4; proto = ip[9]
    src = '.'.join(map(str, ip[12:16])); dst = '.'.join(map(str, ip[16:20]))
    tot = struct.unpack('>H', ip[2:4])[0]; l4 = ip[ihl:tot]
    if proto == 6:
        sp, dp, seq, ack, off = struct.unpack('>HHIIB', l4[:13]); fl = l4[13]
        pl = l4[(off >> 4) * 4:]
        fs = ''.join(c for c, b in zip('FSRPAU', [1, 2, 4, 8, 16, 32]) if fl & b)
        print('%8.3f TCP %s:%d > %s:%d [%s] seq=%d ack=%d len=%d %s' % (t - t0, src, sp, dst, dp, fs, seq, ack, len(pl), pl[:N].hex()))
    elif proto == 17:
        sp, dp, ln = struct.unpack('>HHH', l4[:6]); pl = l4[8:]
        if skip_udp_bcast: continue
        print('%8.3f UDP %s:%d > %s:%d len=%d %s' % (t - t0, src, sp, dst, dp, len(pl), pl[:N].hex()))
