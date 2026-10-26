# Minimal packet capture (AF_PACKET, all interfaces) -> pcap. Needs CAP_NET_RAW.
# usage: sniff.py OUT.pcap   (stops on SIGTERM/SIGINT)
import socket, struct, sys, time, signal
out = open(sys.argv[1], 'wb')
out.write(struct.pack('<IHHiIII', 0xa1b2c3d4, 2, 4, 0, 0, 65535, 1))  # LINKTYPE_ETHERNET
s = socket.socket(socket.AF_PACKET, socket.SOCK_RAW, socket.htons(3))
s.settimeout(0.5)
stop = False
def h(*a):
    global stop; stop = True
signal.signal(signal.SIGTERM, h); signal.signal(signal.SIGINT, h)
seen_out = {}
while not stop:
    try:
        data, addr = s.recvfrom(65535)
    except socket.timeout:
        continue
    # on lo every packet is seen twice (outgoing + incoming): keep incoming only
    if addr[0] == 'lo' and addr[2] == socket.PACKET_OUTGOING:
        continue
    t = time.time()
    out.write(struct.pack('<IIII', int(t), int((t % 1) * 1e6), len(data), len(data)))
    out.write(data); out.flush()
out.close()
