/*
 * Our XDaemon (src/platform/xdaemon.c) against a recording of two original
 * games playing each other (docs/xdaemon-protocol.md §2.2, §11): the TCP
 * stream of capture.pcap and what the logging proxy saw the original
 * library do (xdlog-host.txt, xdlog-client.txt).  With fake sockets
 * (host_net_* here), as each side in turn:
 *   - the client: the host's bytes fed in pieces of every size; the game
 *     must get the same records as the original gave it (CB SecureReceive),
 *     its id from the 0xFA record; the game's sends (XD_SendSecureData in
 *     the log) must put the captured records on the wire (padding: zeros
 *     here, junk there, not compared);
 *   - the host: the same with the client's bytes, plus the id record it
 *     sends 500 ms after the accept;
 *   - broadcasts: the game's XD_SendBroadcastData make the captured
 *     datagrams.
 * Then what the recordings do not show: a host with two clients relaying
 * (to all, to the other client), ping replies, the 512-byte cut.
 *
 *   tools/dk sh -c 'gcc -m32 -std=gnu99 -D_GNU_SOURCE -Isrc/platform -Isrc/include \
 *     -o build/xdaemon_test tests/xdaemon_test.c src/platform/xdaemon.c'
 *   build/xdaemon_test run/xd/cap/lan2     (and run/xd/cap/inet1)
 */
#include "plat.h"
#include "../host/host.h"
#include "xdaemon.h"

static int failures;
#define CHECK(c, ...) do { if (!(c)) { failures++; printf("FAIL %s:%d: ", __FILE__, __LINE__); printf(__VA_ARGS__); \
                                       printf("\n"); } } while (0)

/* ---- bytes ---- */

typedef struct { unsigned char *p; size_t n, cap; } Buf;

static void buf_add(Buf *b, const void *p, size_t n)
{
    if (b->n + n > b->cap) {
        b->cap = (b->n + n) * 2 + 64;
        b->p = realloc(b->p, b->cap);
    }
    memcpy(b->p + b->n, p, n);
    b->n += n;
}

static uint32_t u32(const unsigned char *p) { return (uint32_t)p[0] | p[1] << 8 | p[2] << 16 | (uint32_t)p[3] << 24; }

/* ---- the fake machine: clock, messages, sockets ---- */

static uint64_t clock_us = 1000000;
uint64_t host_time_us(void) { return clock_us; }
DWORD WINAPI GetTickCount(void) { clock_us += 1000; return (DWORD)(clock_us / 1000); }
WINBOOL WINAPI PeekMessageA(LPMSG m, HWND h, UINT lo, UINT hi, UINT rm) { (void)m; (void)h; (void)lo; (void)hi; (void)rm; xd_poll(); return 0; }
WINBOOL WINAPI TranslateMessage(const MSG *m) { (void)m; return 0; }
LRESULT WINAPI DispatchMessageA(const MSG *m) { (void)m; return 0; }

#define NSOCK 16
static struct {
    int used, udp, peer_closed;
    Buf in;         /* to be received */
    size_t in_pos;
    Buf out;        /* sent (UDP: [u32 length][datagram]...) */
} sk[NSOCK];
static int accept_pending;          /* connections waiting on the listener */
static unsigned rnd = 12345;
static int send_limit;              /* > 0: send() takes at most this much */

static unsigned next_rand(void) { rnd = rnd * 1103515245u + 12345u; return rnd >> 8; }

static int sock_new(int udp)
{
    int i;
    for (i = 0; i < NSOCK; i++)
        if (!sk[i].used) {
            memset(&sk[i], 0, sizeof sk[i]);
            sk[i].used = 1;
            sk[i].udp = udp;
            return i;
        }
    return -1;
}

int host_net_local_addr(char *buf, int size) { snprintf(buf, (size_t)size, "10.0.0.1"); return 8; }
int host_net_udp_open(int port) { (void)port; return sock_new(1); }
int host_net_udp_send(int s, uint32_t ip, int port, const void *p, int n)
{
    uint32_t len = (uint32_t)n;
    (void)ip; (void)port;
    buf_add(&sk[s].out, &len, 4);
    buf_add(&sk[s].out, p, (size_t)n);
    return n;
}
int host_net_udp_recv(int s, void *p, int n, uint32_t *from)
{
    uint32_t len;
    if (sk[s].in_pos >= sk[s].in.n)
        return -1;
    len = u32(sk[s].in.p + sk[s].in_pos);
    memcpy(p, sk[s].in.p + sk[s].in_pos + 4, len < (uint32_t)n ? len : (size_t)n);
    sk[s].in_pos += 4 + len;
    if (from)
        *from = 0x0a000002;
    return (int)(len < (uint32_t)n ? len : (uint32_t)n);
}
int host_net_tcp_open(int port) { (void)port; return sock_new(0); }
int host_net_tcp_listen(int s, int backlog) { (void)s; (void)backlog; return 0; }
int host_net_tcp_accept(int s, uint32_t *peer)
{
    (void)s;
    if (!accept_pending)
        return -1;
    accept_pending--;
    if (peer)
        *peer = 0x0a000002;
    return sock_new(0);
}
int host_net_tcp_connect(int s, uint32_t ip, int port) { (void)s; (void)ip; (void)port; return 0; }
int host_net_tcp_state(int s) { (void)s; return 1; }
int host_net_tcp_send(int s, const void *p, int n)
{
    if (send_limit && n > send_limit)
        n = send_limit;
    buf_add(&sk[s].out, p, (size_t)n);
    return n;
}
/* What has "arrived", in pieces of random size (1 byte to 3 KB). */
int host_net_tcp_recv(int s, void *p, int n)
{
    size_t left = sk[s].in.n - sk[s].in_pos, k = 1 + next_rand() % 3000;
    if (!left)
        return sk[s].peer_closed ? 0 : -1;
    if (k > left)
        k = left;
    if (k > (size_t)n)
        k = (size_t)n;
    memcpy(p, sk[s].in.p + sk[s].in_pos, k);
    sk[s].in_pos += k;
    return (int)k;
}
void host_net_close(int s) { sk[s].used = 0; }

static void poll_some(int n)
{
    while (n-- > 0) {
        clock_us += 2000;       /* (xd_poll skips calls less than 1 ms apart) */
        xd_poll();
    }
}

/* ---- what the game is told ---- */

typedef struct { int src; uint32_t len; unsigned char *data; short flags; } Got;
static Got got[4096];
static int ngot, connected_id = -100, lost_id = -100, new_count, new_id = -100;
static Buf bcast_got;
static long bcast_header;

static void on_secure(unsigned short src, void *data, unsigned long len, short flags)
{
    if (ngot < 4096) {
        got[ngot].src = src;
        got[ngot].len = (uint32_t)len;
        got[ngot].data = malloc(len ? len : 1);
        memcpy(got[ngot].data, data, len);
        got[ngot].flags = flags;
        ngot++;
    }
}
static void on_broadcast(void *data, unsigned short len, long header)
{
    bcast_got.n = 0;
    buf_add(&bcast_got, data, len);
    bcast_header = header;
}
static void on_connected(short id) { connected_id = id; }
static void on_lost(unsigned short id) { lost_id = id; }
static void on_new(unsigned short count, unsigned short id) { new_count = count; new_id = id; }

static void reset_game(void)
{
    int i;
    for (i = 0; i < ngot; i++)
        free(got[i].data);
    ngot = 0;
    connected_id = lost_id = new_id = -100;
    new_count = 0;
    XD_ResetLibrary();
    memset(sk, 0, sizeof sk);
    accept_pending = 0;
    send_limit = 0;
}

/* ---- the recording ---- */

typedef struct {
    Buf c2s, s2c;               /* the first connection to port 4993, each way */
    Buf udp[2];                 /* datagrams ([u32 len][bytes]) from the client [0], the host [1] */
} Capture;

static int read_pcap(const char *path, Capture *c)
{
    FILE *f = fopen(path, "rb");
    unsigned char h[16], *d;
    uint32_t client_ip = 0, host_ip = 0, next[2] = {0, 0};
    unsigned cport = 0;
    int have[2] = {0, 0};
    if (!f)
        return 0;
    fread(h, 1, 24, f);
    d = malloc(70000);
    while (fread(h, 1, 16, f) == 16) {
        uint32_t cl = u32(h + 8), ihl, tot, src, dst;
        unsigned char *ip, *l4;
        if (cl > 70000 || fread(d, 1, cl, f) != cl)
            break;
        if (d[12] != 8 || d[13] != 0)
            continue;
        ip = d + 14;
        ihl = (ip[0] & 15) * 4u;
        tot = (uint32_t)ip[2] << 8 | ip[3];
        src = (uint32_t)ip[12] << 24 | ip[13] << 16 | ip[14] << 8 | ip[15];
        dst = (uint32_t)ip[16] << 24 | ip[17] << 16 | ip[18] << 8 | ip[19];
        l4 = ip + ihl;
        if (ip[9] == 6) {
            unsigned sp = (unsigned)l4[0] << 8 | l4[1], dp = (unsigned)l4[2] << 8 | l4[3];
            uint32_t seq = (uint32_t)l4[4] << 24 | l4[5] << 16 | l4[6] << 8 | l4[7];
            unsigned off = (l4[12] >> 4) * 4u, fl = l4[13];
            uint32_t plen = tot - ihl - off;
            int dir;            /* 0 client -> host, 1 host -> client */
            if (!cport && dp == 4993 && (fl & 0x12) == 0x02) {
                cport = sp;
                client_ip = src;
                host_ip = dst;
            }
            if (!cport)
                continue;
            if (sp == cport && dp == 4993 && src == client_ip)
                dir = 0;
            else if (dp == cport && sp == 4993 && dst == client_ip)
                dir = 1;
            else
                continue;
            if (fl & 2) {
                next[dir] = seq + 1;
                have[dir] = 1;
                continue;
            }
            if (!have[dir] || !plen)
                continue;
            if (seq == next[dir]) {
                buf_add(dir ? &c->s2c : &c->c2s, l4 + off, plen);
                next[dir] += plen;
            } else if ((int32_t)(seq - next[dir]) > 0)
                printf("note: a gap in the TCP stream (lost packet?)\n");
            /* (seq before next: a duplicate) */
        } else if (ip[9] == 17) {
            unsigned dp = (unsigned)l4[2] << 8 | l4[3];
            uint32_t len = ((uint32_t)l4[4] << 8 | l4[5]) - 8;
            if (dp != 4994)
                continue;
            /* (whose: decided below by the address, once the TCP connection is known) */
            buf_add(&c->udp[0], &src, 4);
            buf_add(&c->udp[0], &len, 4);
            buf_add(&c->udp[0], l4 + 8, len);
        }
    }
    free(d);
    fclose(f);
    /* the datagrams split by sender */
    {
        Buf all = c->udp[0];
        size_t i = 0;
        memset(&c->udp[0], 0, sizeof c->udp[0]);
        while (i + 8 <= all.n) {
            uint32_t src = u32(all.p + i), len = u32(all.p + i + 4);
            if (src == client_ip || src == host_ip) {
                Buf *b = &c->udp[src == host_ip && host_ip != client_ip ? 1 : 0];
                buf_add(b, &len, 4);
                buf_add(b, all.p + i + 8, len);
            }
            i += 8 + len;
        }
        free(all.p);
    }
    return cport != 0;
}

/* The log's calls and callbacks with their bytes, in order. */
typedef struct {
    int kind;           /* 's' XD_SendSecureData, 'b' XD_SendBroadcastData, 'r' CB SecureReceive,
                           'n' CB NewClientConnection, 'c' CB ClientConnectionToServer, 'l' CB ConnectionLost */
    int a, b;           /* to / from / id, count */
    Buf data;
} Event;

static int read_log(const char *path, Event *ev, int max)
{
    FILE *f = fopen(path, "r");
    char line[512];
    int n = 0, sessions = 0;
    Event *cur = NULL;
    if (!f)
        return -1;
    while (fgets(line, sizeof line, f) && n < max) {
        char *p;
        unsigned to, size, off;
        int x, y;
        if (cur && (p = strstr(line, "  tx ")) && sscanf(p + 5, "%x:", &off) == 1) {
            char *hx = strchr(p, ':') + 2;
            while (isxdigit((unsigned char)hx[0]) && isxdigit((unsigned char)hx[1])) {
                unsigned v;
                unsigned char byte;
                sscanf(hx, "%2x", &v);
                byte = (unsigned char)v;
                buf_add(&cur->data, &byte, 1);
                hx += 2;
            }
            continue;
        }
        if (cur && (p = strstr(line, "  rx ")) && cur->kind == 'r') {
            char *hx = strchr(p, ':') + 2;
            while (isxdigit((unsigned char)hx[0]) && isxdigit((unsigned char)hx[1])) {
                unsigned v;
                unsigned char byte;
                sscanf(hx, "%2x", &v);
                byte = (unsigned char)v;
                buf_add(&cur->data, &byte, 1);
                hx += 2;
            }
            continue;
        }
        cur = NULL;
        if (strstr(line, "XD_InitializeSocketsTCP") && ++sessions > 1)
            break;              /* (inet1's client becomes the new host: a second session) */
        memset(&ev[n], 0, sizeof ev[n]);
        if ((p = strstr(line, "XD_SendSecureData(to=")) && sscanf(p, "XD_SendSecureData(to=%u, size=%u", &to, &size) == 2) {
            ev[n].kind = 's';
            ev[n].a = (int)to;
            ev[n].b = (int)size;
        } else if ((p = strstr(line, "XD_SendBroadcastData(size=")) && sscanf(p, "XD_SendBroadcastData(size=%u", &size) == 1) {
            ev[n].kind = 'b';
            ev[n].b = (int)size;
        } else if ((p = strstr(line, "CB SecureReceive from=")) && sscanf(p, "CB SecureReceive from=%d size=%u", &x, &size) == 2) {
            ev[n].kind = 'r';
            ev[n].a = x;
            ev[n].b = (int)size;
        } else if ((p = strstr(line, "CB NewClientConnection a=")) && sscanf(p, "CB NewClientConnection a=%d b=%d", &x, &y) == 2) {
            ev[n].kind = 'n';
            ev[n].a = y;
            ev[n].b = x;
        } else if ((p = strstr(line, "CB ClientConnectionToServer id=")) && sscanf(p, "CB ClientConnectionToServer id=%d", &x) == 1) {
            ev[n].kind = 'c';
            ev[n].a = x;
        } else if ((p = strstr(line, "CB ConnectionLost id=")) && sscanf(p, "CB ConnectionLost id=%d", &x) == 1) {
            ev[n].kind = 'l';
            ev[n].a = x;
        } else
            continue;
        cur = &ev[n++];
    }
    fclose(f);
    return n;
}

/* Records of a byte stream: offsets.  0 if it does not divide into records. */
static int records(const Buf *b, size_t *at, int max)
{
    size_t i = 0;
    int n = 0;
    while (i + 12 <= b->n && n < max) {
        uint32_t total = u32(b->p + i);
        if (total < 12 || total % 64 || i + total > b->n)
            break;
        at[n++] = i;
        i += total;
    }
    return n;
}

/* Our records against the captured ones: headers and payloads equal; our
 * padding zero. */
static void compare_records(const char *what, const Buf *ours, const Buf *theirs, int skip_theirs)
{
    static size_t a[8192], b[8192];
    int na = records(ours, a, 8192), nb = records(theirs, b, 8192), i, bad = 0;
    nb -= skip_theirs;
    CHECK(na == nb, "%s: %d records from us, %d captured", what, na, nb);
    for (i = 0; i < na && i < nb && bad < 5; i++) {
        const unsigned char *x = ours->p + a[i], *y = theirs->p + b[i + skip_theirs];
        uint32_t total = u32(x), len = u32(x + 8), k;
        int padok = 1;
        for (k = 12 + len; k < total; k++)
            padok &= x[k] == 0;
        if (total != u32(y) || u32(x + 4) != u32(y + 4) || len != u32(y + 8) || memcmp(x + 12, y + 12, len) || !padok) {
            bad++;
            CHECK(0, "%s: record %d differs: ours total=%u tag=%08x len=%u, captured total=%u tag=%08x len=%u%s", what, i,
                  total, u32(x + 4), len, u32(y), u32(y + 4), u32(y + 8), padok ? "" : " (our padding not zero)");
        }
    }
    printf("%s: %d records compared\n", what, na < nb ? na : nb);
}

/* The game's deliveries against the log's CB SecureReceive. */
static void compare_got(const char *what, Event *ev, int nev)
{
    int i, k = 0, bad = 0;
    for (i = 0; i < nev; i++) {
        if (ev[i].kind != 'r')
            continue;
        if (k >= ngot) {
            CHECK(0, "%s: delivery %d (size %d) missing", what, k, ev[i].b);
            return;
        }
        if (bad < 5 && (got[k].src != ev[i].a || got[k].len != (uint32_t)ev[i].b || ev[i].data.n != got[k].len ||
                        memcmp(got[k].data, ev[i].data.p, got[k].len))) {
            bad++;
            CHECK(0, "%s: delivery %d: ours src=%d len=%u, the original's src=%d len=%d", what, k, got[k].src,
                  got[k].len, ev[i].a, ev[i].b);
        }
        k++;
    }
    CHECK(k == ngot, "%s: %d deliveries, the original %d", what, ngot, k);
    printf("%s: %d deliveries compared\n", what, k);
}

/* The game's broadcasts against the captured datagrams. */
static void compare_broadcasts(const char *what, Event *ev, int nev, const Buf *udp_out, const Buf *captured)
{
    size_t i = 0, j = 0;
    int e, n = 0, bad = 0;
    (void)ev; (void)nev;
    if (!captured->n) {
        printf("%s: none captured from that address (inet1: both games share one)\n", what);
        return;
    }
    while (i + 4 <= udp_out->n && j + 4 <= captured->n) {
        uint32_t la = u32(udp_out->p + i), lb = u32(captured->p + j);
        if (bad < 5 && (la != lb || memcmp(udp_out->p + i + 4, captured->p + j + 4, la))) {
            bad++;
            CHECK(0, "%s: datagram %d: ours %u bytes, captured %u", what, n, la, lb);
        }
        i += 4 + la;
        j += 4 + lb;
        n++;
    }
    e = (i < udp_out->n) - (j < captured->n);
    CHECK(e == 0, "%s: %s datagrams left over", what, e > 0 ? "our" : "captured");
    printf("%s: %d datagrams compared\n", what, n);
}

static Event events[20000];

static void as_client(const Capture *c, const char *dir)
{
    char path[1024];
    int nev, i;
    Buf udp_out;
    reset_game();
    snprintf(path, sizeof path, "%s/xdlog-client.txt", dir);
    nev = read_log(path, events, 20000);
    CHECK(nev > 0, "no %s", path);
    CHECK(XD_InitializeSocketsTCP(3, 4993, 4994, 0, 7, NULL) == 0, "client init");
    CHECK(XD_OpenConnection("10.0.0.2", 15000) == 0, "open");
    /* the connection: socket 1 (0 is UDP) */
    buf_add(&sk[1].in, c->s2c.p, c->s2c.n);
    poll_some(4000);            /* (the id first: the game sends once it has it) */
    send_limit = 700;           /* partial sends: the rest queued */
    for (i = 0; i < nev; i++)
        if (events[i].kind == 's') {
            CHECK(events[i].data.n == (size_t)events[i].b, "log: send of %d bytes with %u logged", events[i].b,
                  (unsigned)events[i].data.n);
            CHECK(XD_SendSecureData((unsigned short)events[i].a, events[i].data.p, events[i].data.n, 0) > 0, "send");
        } else if (events[i].kind == 'b')
            XD_SendBroadcastData(events[i].data.p, events[i].data.n, 0);
    poll_some(4000);
    CHECK(connected_id == 1, "client: told id %d", connected_id);
    CHECK(XD_FlushSendBuffer(5000) == 0, "client: flushed");
    compare_records("client -> host", &sk[1].out, &c->c2s, 0);
    compare_got("host -> client", events, nev);
    udp_out = sk[0].out;
    compare_broadcasts("client broadcasts", events, nev, &udp_out, &c->udp[0]);
    /* the host goes */
    sk[1].peer_closed = 1;
    poll_some(4);
    CHECK(lost_id == 0, "client: lost id %d", lost_id);
    CHECK(XD_SendSecureData(0, "x", 1, 0) == -4, "client: send after loss");
}

static void as_host(const Capture *c, const char *dir)
{
    char path[1024];
    int nev, i, s;
    reset_game();
    snprintf(path, sizeof path, "%s/xdlog-host.txt", dir);
    nev = read_log(path, events, 20000);
    CHECK(nev > 0, "no %s", path);
    XD_SetBroadcastReceive(on_broadcast);
    CHECK(XD_InitializeSocketsTCP(3, 4993, 4994, 1, 7, NULL) == 0, "host init");
    CHECK(XD_ActivateServer() == 0, "activate");
    s = -1;
    for (i = 0; i < nev; i++) {
        if (events[i].kind == 'n') {
            accept_pending = 1;
            poll_some(1);
            s = 2;          /* 0 UDP, 1 the listener */
            CHECK(sk[s].used && sk[s].out.n == 0, "host: the id record before 500 ms");
            poll_some(300);
            CHECK(new_id == 1 && new_count == 2, "host: NewClientConnection(%d, %d)", new_count, new_id);
            CHECK(sk[s].out.n == 64 && u32(sk[s].out.p + 4) == 0xFA000000u && sk[s].out.p[12] == 1,
                  "host: the id record");
            buf_add(&sk[s].in, c->c2s.p, c->c2s.n);
        } else if (events[i].kind == 'l')
            break;              /* (the client left: nothing more for it) */
        else if (events[i].kind == 's')
            CHECK(XD_SendSecureData((unsigned short)events[i].a, events[i].data.p, events[i].data.n, 0) > 0,
                  "host send %d", i);
        else if (events[i].kind == 'b')
            XD_SendBroadcastData(events[i].data.p, events[i].data.n, 0);
    }
    CHECK(s == 2, "host: no client in the log");
    poll_some(4000);
    compare_records("host -> client", &sk[2].out, &c->s2c, 0);
    compare_got("client -> host", events, nev);
    compare_broadcasts("host broadcasts", events, nev, &sk[0].out, &c->udp[1]);
    sk[2].peer_closed = 1;
    poll_some(4);
    CHECK(lost_id == 1, "host: lost id %d", lost_id);
}

/* A record as a client would send it. */
static void rec(Buf *b, uint32_t tag, const void *p, uint32_t len)
{
    uint32_t total = (len + 12 + 63) & ~63u;
    unsigned char z[64] = {0};
    buf_add(b, &total, 4);
    buf_add(b, &tag, 4);
    buf_add(b, &len, 4);
    buf_add(b, p, len);
    buf_add(b, z, total - 12 - len);
}

static void synthetic(void)
{
    static const char hello[] = "hello, everyone";
    uint16_t id1 = 1;
    size_t at[16];
    unsigned char big[600];
    reset_game();
    /* a host with two clients */
    XD_SetBroadcastReceive(on_broadcast);
    XD_InitializeSocketsTCP(3, 4993, 4994, 1, 7, NULL);
    XD_ActivateServer();
    accept_pending = 2;
    poll_some(300);
    CHECK(new_id == 2 && new_count == 3, "two clients: NewClientConnection(%d, %d)", new_count, new_id);
    sk[2].out.n = sk[3].out.n = 0;
    rec(&sk[2].in, 0x01FF0000u | 7, hello, sizeof hello);       /* 1 to all, flags 7 */
    rec(&sk[2].in, 0x01020000u, hello, 5);                      /* 1 to 2 */
    rec(&sk[2].in, 0xFC000000u, &id1, 2);                       /* ping from 1 */
    poll_some(4);
    CHECK(ngot == 1 && got[0].src == 1 && got[0].len == sizeof hello && got[0].flags == 7,
          "relay: the host gets one record from 1 (got %d)", ngot);
    CHECK(records(&sk[3].out, at, 16) == 2 && u32(sk[3].out.p + 4) == (0x00020000u | 7) &&
          u32(sk[3].out.p + at[1] + 4) == 0x01020000u, "relay: client 2 gets the to-all as from the host, then 1's");
    CHECK(records(&sk[2].out, at, 16) == 1 && u32(sk[2].out.p + 4) == 0xFD000000u && u32(sk[2].out.p + 8) == 2,
          "ping: 1 gets the reply");
    /* to all from the host: each client its own tag */
    sk[2].out.n = sk[3].out.n = 0;
    CHECK(XD_SendSecureData(0xFF, (void *)hello, 4, 0) == 4, "host to all");
    CHECK(u32(sk[2].out.p + 4) == 0x00010000u && u32(sk[3].out.p + 4) == 0x00020000u, "host to all: tags");
    CHECK(XD_SendSecureData(0, (void *)hello, 4, 0) == -9, "host to itself");
    CHECK(XD_SendSecureData(5, (void *)hello, 4, 0) == -13, "host to nobody");
    /* the 512-byte cut, the header word */
    memset(big, 'x', sizeof big);
    CHECK(XD_SendBroadcastData(big, sizeof big, 9) == 516, "broadcast cut to 512");
    {
        uint32_t len = 6;
        unsigned char dg[6] = {3, 0, 0, 0, 'a', 'b'};
        buf_add(&sk[0].in, &len, 4);
        buf_add(&sk[0].in, dg, 6);
        poll_some(2);
        CHECK(bcast_got.n == 2 && bcast_header == 3 && !memcmp(bcast_got.p, "ab", 2), "broadcast received");
    }
    /* 2 rejected by the host */
    CHECK(XD_ServerCloseConnection(2) == 0 && !sk[3].used, "kicked");
    CHECK(XD_SendSecureData(2, (void *)hello, 4, 0) == -13, "to the kicked one");
    /* a client: the id too late, then a ping */
    reset_game();
    XD_InitializeSocketsTCP(3, 4993, 4994, 0, 7, NULL);
    XD_OpenConnection("10.0.0.2", 1000);
    poll_some(600);
    CHECK(connected_id == -1, "connect timeout: told %d", connected_id);
    XD_OpenConnection("10.0.0.2", 1000);
    rec(&sk[1].in, 0xFA000000u, &id1, 2);
    rec(&sk[1].in, 0xFC000000u, hello, 32);
    poll_some(4);
    CHECK(connected_id == 1 && ngot == 0, "client: id 1, ping not passed on");
    CHECK(records(&sk[1].out, at, 16) == 1 && u32(sk[1].out.p + 4) == 0xFD000000u, "client: ping answered");
    CHECK(XD_SendSecureData(1, (void *)hello, 4, 0) == -9, "client to itself");
    CHECK(XD_OpenConnection("not an address", 1000) == -10, "bad address");
}

int main(int argc, char **argv)
{
    int i;
    XD_SetSecureReceive(on_secure);
    XD_SetBroadcastReceive(on_broadcast);
    XD_SetOnClientConnectionToServer(on_connected);
    XD_SetOnConnectionLost(on_lost);
    XD_SetNewClientConnection(on_new);
    XD_SetOversizedMessageCB(50000, NULL);
    for (i = 1; i < argc; i++) {
        Capture c;
        char path[1024];
        memset(&c, 0, sizeof c);
        snprintf(path, sizeof path, "%s/capture.pcap", argv[i]);
        if (!read_pcap(path, &c)) {
            CHECK(0, "%s: no connection to port 4993", path);
            continue;
        }
        printf("== %s: %u bytes to the host, %u to the client\n", argv[i], (unsigned)c.c2s.n, (unsigned)c.s2c.n);
        as_client(&c, argv[i]);
        as_host(&c, argv[i]);
    }
    printf("== relays, pings, limits\n");
    synthetic();
    printf(failures ? "%d FAILED\n" : "all passed\n", failures);
    return failures != 0;
}
