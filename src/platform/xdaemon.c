/*
 * XDaemon.dll, MicroProse's networking library, rebuilt: network play over
 * TCP/IP, on the wire exactly as the original (docs/xdaemon-protocol.md;
 * the sections cited are that document's).  IPX/SPX, modem, serial and the
 * DirectPlay lobby are not provided (their calls fail as without them).
 *
 * TCP port 4993 ("secure"): the host listens, clients connect to it; a
 * star, the host relaying.  Records [u32 total][u32 tag][u32 len][payload]
 * [zero padding], total a multiple of 64; tag = src << 24 | dst << 16 |
 * flags.  The host is id 0, its clients 1..6 (the connection table).
 * UDP port 4994 ("broadcast"): datagrams to 255.255.255.255, [i32 header]
 * [payload, at most 512 bytes].
 *
 * The sockets are the host's (host_net_*), non-blocking.  The original ran
 * its callbacks from its hidden windows' procedures, that is, inside the
 * game's message loop; here xd_poll() does the I/O and calls them, from
 * PeekMessage (message.c) and XD_FlushSendBuffer.  Nothing is opened
 * until the game starts a network game.
 *
 * CIV2_XDLOG=FILE: a log of the calls and callbacks (as the logging proxy
 * tools/xdnet/xdlog.c writes for the original).  CIV2_NET_ADDR=a.b.c.d:
 * the address XD_GetCurrentProtoAddr gives (default: host_net_local_addr).
 */
#include "plat.h"
#include "../host/host.h"
#include "xdaemon.h"

#define SECURE_CHUNK 0x2000     /* largest send() of a record */
#define UDP_PAYLOAD 0x200       /* broadcast payload cut to this */
#define TAG_YOUR_ID 0xFA000000u
#define TAG_PING 0xFC000000u
#define TAG_PING_REPLY 0xFD000000u
#define ID_DELAY_US 500000      /* the host waits this before sending a client its id */
#define MAX_TABLE 0xF8

typedef struct SendItem {
    struct SendItem *next;
    unsigned char *data;
    uint32_t size, sent;
} SendItem;

typedef struct Stream {
    int sock;                   /* host_net handle, -1: closed */
    int connecting;             /* client: connect() in progress */
    int live;                   /* connected or connecting (a client's socket is not, until
                                   XD_OpenConnection) */
    int dead;                   /* client: the server connection was lost */
    int id;                     /* host: its table entry */
    /* receiving: bytes of records not complete yet */
    unsigned char *rbuf;
    uint32_t rlen, rcap;
    /* sending */
    SendItem *head, *tail;
    int items;
    /* host: a new client's id record is held back until then (then
       NewClientConnection) */
    uint64_t hold_until;
    int greeting;
} Stream;

static int proto = -1;          /* -1 not initialised, 0 TCP/IP */
static int is_host;
static int use_secure, use_broadcast;
static int my_id = -1;          /* the original keeps it in a short */
static int secure_port, broadcast_port;
static int udp = -1;
static Stream *server;          /* client: the connection to the host; host: the listener */
static Stream **table;          /* host: the connection table, [0] the listener */
static unsigned table_size;
static int accepting;           /* host: XD_ActivateServer called, XD_StopConnections not */
static int in_flush;
static unsigned generation;     /* changes when a stream goes */
static int timer_on;            /* client: connect timeout running */
static uint64_t timer_start, timer_ms;

static XD_BroadcastReceiveCB cb_broadcast;
static XD_SecureReceiveCB cb_secure;
static XD_NewClientCB cb_new_client;
static XD_ConnectedCB cb_connected;
static XD_ConnectionLostCB cb_lost;
static XD_OversizedMessageCB cb_oversized;
static unsigned long size_limit = 0xFFFFFFF0u;

/* ---- log ---- */

static FILE *xdlog;

static void xlog(const char *fmt, ...)
{
    static int opened;
    va_list ap;
    if (!opened) {
        const char *p = getenv("CIV2_XDLOG");
        opened = 1;
        if (p && *p)
            xdlog = fopen(p, "a");
    }
    if (!xdlog)
        return;
    fprintf(xdlog, "%7u ", (unsigned)(host_time_us() / 1000));
    va_start(ap, fmt);
    vfprintf(xdlog, fmt, ap);
    va_end(ap);
    fputc('\n', xdlog);
    fflush(xdlog);
}

static void xlog_hex(const char *dir, const void *p, uint32_t n)
{
    const unsigned char *b = p;
    uint32_t i, k;
    char line[80];
    if (!xdlog)
        return;
    for (i = 0; i < n; i += 32) {
        int len = 0;
        for (k = i; k < n && k < i + 32; k++)
            len += snprintf(line + len, sizeof line - (size_t)len, "%02x", b[k]);
        xlog("  %s %04x: %s", dir, (unsigned)i, line);
    }
}

/* ---- streams ---- */

static uint64_t now_us(void) { return host_time_us(); }

static Stream *stream_new(int sock)
{
    Stream *s = calloc(1, sizeof *s);
    if (!s) {
        if (sock >= 0)
            host_net_close(sock);
        return NULL;
    }
    s->sock = sock;
    s->id = -1;
    return s;
}

static void stream_close_socket(Stream *s)
{
    SendItem *it;
    if (s->sock >= 0)
        host_net_close(s->sock);
    s->sock = -1;
    s->connecting = s->live = 0;
    free(s->rbuf);
    s->rbuf = NULL;
    s->rlen = s->rcap = 0;
    while ((it = s->head)) {        /* what was still queued is dropped, as by the original */
        s->head = it->next;
        free(it->data);
        free(it);
    }
    s->tail = NULL;
    s->items = 0;
}

/* Closes the stream and takes it out of the table. */
static void stream_free(Stream *s)
{
    if (!s)
        return;
    stream_close_socket(s);
    if (table && s->id >= 0 && (unsigned)s->id < table_size && table[s->id] == s)
        table[s->id] = NULL;
    if (s == server)
        server = NULL;
    free(s);
    generation++;
}

static Stream *conn(unsigned id)
{
    return table && id < table_size ? table[id] : NULL;
}

static unsigned connections_used(void)
{
    unsigned i, n = 0;
    for (i = 0; i < table_size; i++)
        n += table[i] != NULL;
    return n;
}

/* A client's fresh, unconnected socket in place of the old one (the
 * original deletes its stream object and makes a new one). */
static void client_fresh_socket(void)
{
    Stream *old = server;
    server = NULL;
    stream_free(old);
    server = stream_new(host_net_tcp_open(0));
    if (server && server->sock < 0) {
        free(server);
        server = NULL;
    }
}

/* ---- sending ---- */

/* A record queued and/or sent: 2 sent at once, 1 queued, -1 too big,
 * -2 out of memory, -4 the connection is dead. */
static int stream_send(Stream *s, uint32_t len, const void *data, uint32_t tag)
{
    uint32_t total = (len + 12 + 63) & ~63u;
    unsigned char *rec;
    int sent = 0;
    if (len >= size_limit - 12) {
        xlog("Oversize message caught (size %u)", (unsigned)len);
        return -1;
    }
    if (!s || s->sock < 0 || !s->live || s->dead)
        return -4;
    rec = calloc(1, total);         /* the padding zeroed (the original's is stale bytes) */
    if (!rec)
        return -2;
    memcpy(rec, &total, 4);
    memcpy(rec + 4, &tag, 4);
    memcpy(rec + 8, &len, 4);
    memcpy(rec + 12, data, len);
    if (!s->head && !s->connecting && !s->hold_until) {
        sent = host_net_tcp_send(s->sock, rec, (int)(total < SECURE_CHUNK ? total : SECURE_CHUNK));
        if (sent == -2) {
            free(rec);
            return -4;
        }
        if (sent < 0)
            sent = 0;
        if ((uint32_t)sent == total) {
            free(rec);
            return 2;
        }
    }
    {
        SendItem *it = malloc(sizeof *it);
        if (!it) {
            free(rec);
            return -2;
        }
        it->next = NULL;
        it->data = rec;
        it->size = total;
        it->sent = (uint32_t)sent;
        if (s->tail)
            s->tail->next = it;
        else
            s->head = it;
        s->tail = it;
        s->items++;
    }
    return 1;
}

/* What is queued, sent as far as the socket takes it: 0, -4 dead. */
static int stream_drain(Stream *s)
{
    SendItem *it;
    while ((it = s->head)) {
        uint32_t left = it->size - it->sent;
        int r = host_net_tcp_send(s->sock, it->data + it->sent, (int)(left < SECURE_CHUNK ? left : SECURE_CHUNK));
        if (r == -2)
            return -4;
        if (r <= 0)
            return 0;
        it->sent += (uint32_t)r;
        if (it->sent < it->size)
            continue;
        s->head = it->next;
        if (!s->head)
            s->tail = NULL;
        s->items--;
        free(it->data);
        free(it);
    }
    return 0;
}

/* ---- connection loss ---- */

/* The connection on stream s is gone (closed by the peer, or a send
 * failed): the original's close handler. */
static void connection_lost(Stream *s)
{
    if (!is_host) {
        xlog("Lost server connection (ID 0)");
        if (s)
            s->dead = 1;
        my_id = -1;
        xlog("CB ConnectionLost id=0");
        if (cb_lost)
            cb_lost(0);
        return;
    }
    {
        int id = s ? s->id : -1;
        if (s) {
            if (s == server)
                server = NULL;
            stream_free(s);
        }
        if (my_id == id)
            my_id = -1;
        xlog("Lost connection to ID %d", id);
        xlog("CB ConnectionLost id=%d", id);
        if (cb_lost)
            cb_lost((unsigned short)id);
    }
}

/* ---- receiving ---- */

static void deliver(uint32_t tag, unsigned char *payload, uint32_t len)
{
    xlog("CB SecureReceive src=%u len=%u tag=%08x", (unsigned)(tag >> 24), (unsigned)len, (unsigned)tag);
    xlog_hex("rx", payload, len < 64 ? len : 64);
    if (cb_secure)
        cb_secure((unsigned short)(tag >> 24), payload, len, (short)tag);
}

/* The client's connect timeout passed, or its id came too late: a fresh
 * socket, and the game told the connection failed. */
static void client_connect_failed(void)
{
    xlog("Terminating temporary connection");
    timer_on = 0;
    client_fresh_socket();
    xlog("CB ClientConnectionToServer id=-1");
    if (cb_connected)
        cb_connected(-1);
}

/* One whole record from stream s (the original's 10002a20). */
static void record(Stream *s, uint32_t tag, unsigned char *payload, uint32_t len)
{
    if (!is_host) {
        if (tag == TAG_YOUR_ID && my_id == -1) {
            if (timer_on && now_us() - timer_start < timer_ms * 1000) {
                uint16_t id;
                memcpy(&id, payload, len >= 2 ? 2 : 0);
                my_id = (short)(len >= 2 ? id : 0);
                timer_on = 0;
                xlog("CB ClientConnectionToServer id=%d", my_id);
                if (cb_connected)
                    cb_connected((short)my_id);
            } else
                client_connect_failed();
            return;
        }
        if (tag == TAG_PING) {
            stream_send(server, len, payload, TAG_PING_REPLY);
            return;
        }
        if (tag == TAG_PING_REPLY || tag == TAG_YOUR_ID)
            return;         /* (nobody asks for pings; the id record only once) */
        deliver(tag, payload, len);
        return;
    }
    if (tag == TAG_PING) {
        uint16_t to = 0;
        if (len >= 2)
            memcpy(&to, payload, 2);
        if (conn(to))
            stream_send(conn(to), len, payload, TAG_PING_REPLY);
        return;
    }
    if (tag == TAG_PING_REPLY || tag == TAG_YOUR_ID)
        return;
    {
        unsigned dst = (tag >> 16) & 0xFF, src = tag >> 24, i;
        if (dst != 0 && dst != 0xFF) {
            /* to another client: passed on as it is */
            if (conn(dst))
                stream_send(conn(dst), len, payload, tag);
            else
                xlog("Could not find the destination address %u", dst);
            return;
        }
        if (dst == 0xFF) {
            /* to everyone: to the other clients as from the host, then here */
            for (i = 1; i < table_size; i++)
                if (i != src && conn(i))
                    stream_send(conn(i), len, payload,
                                (uint32_t)(((my_id & 0xFF) << 8 | i) & 0xFFFF) << 16 | (tag & 0xFFFF));
        }
        (void)s;
        deliver(tag, payload, len);
    }
}

/* The next whole record in s's buffer taken out (the bytes after it
 * kept): 1 with *out (malloc'd) set, 0 if none is complete. */
static int next_record(Stream *s, unsigned char **out, uint32_t *tag, uint32_t *len)
{
    uint32_t total;
    for (;;) {
        if (s->rlen < 4)
            return 0;
        memcpy(&total, s->rbuf, 4);
        if (total < 12 || total > size_limit - 12) {
            /* The original calls the oversize callback and loses its place
               in the stream; here the record is skipped. */
            if (total >= 12 && s->rlen < total)
                return 0;
            xlog("CB OversizedMessage size=%u", (unsigned)total);
            if (total >= 12 && cb_oversized)
                cb_oversized(total - 12);
            if (total < 12)
                total = 4;
            memmove(s->rbuf, s->rbuf + total, s->rlen - total);
            s->rlen -= total;
            continue;
        }
        if (s->rlen < total)
            return 0;
        memcpy(tag, s->rbuf + 4, 4);
        memcpy(len, s->rbuf + 8, 4);
        if (*len > total - 12)
            *len = total - 12;
        *out = malloc(*len ? *len : 1);
        if (!*out)
            return 0;
        memcpy(*out, s->rbuf + 12, *len);
        memmove(s->rbuf, s->rbuf + total, s->rlen - total);
        s->rlen -= total;
        return 1;
    }
}

/* Reads what has arrived on s: 0, or -1 the connection closed. */
static int stream_read(Stream *s)
{
    unsigned char tmp[8192];
    int rounds;
    for (rounds = 0; rounds < 16; rounds++) {
        int r = host_net_tcp_recv(s->sock, tmp, sizeof tmp);
        if (r == -1)
            return 0;
        if (r == 0 || r == -2)
            return -1;
        if (s->rlen + (uint32_t)r > s->rcap) {
            uint32_t cap = s->rcap ? s->rcap : 16384;
            unsigned char *nb;
            while (cap < s->rlen + (uint32_t)r)
                cap *= 2;
            nb = realloc(s->rbuf, cap);
            if (!nb)
                return -1;
            s->rbuf = nb;
            s->rcap = cap;
        }
        memcpy(s->rbuf + s->rlen, tmp, (size_t)r);
        s->rlen += (uint32_t)r;
    }
    return 0;
}

/* Every whole record in s handled: 0, or 1 if streams changed meanwhile
 * (a callback closed something): the caller starts over. */
static int stream_dispatch(Stream *s)
{
    unsigned char *payload;
    uint32_t tag, len;
    unsigned gen = generation;
    while (next_record(s, &payload, &tag, &len)) {
        record(s, tag, payload, len);
        free(payload);
        if (gen != generation)
            return 1;
    }
    return 0;
}

/* ---- polling: the work the original's window procedures did ---- */

static void poll_broadcast(void)
{
    unsigned char buf[UDP_PAYLOAD + 4];
    int rounds;
    for (rounds = 0; rounds < 64 && udp >= 0; rounds++) {
        int32_t header;
        int n;
        memset(buf, 0, sizeof buf);
        n = host_net_udp_recv(udp, buf, (int)sizeof buf, NULL);
        if (n < 0)
            return;
        memcpy(&header, buf, 4);
        xlog("CB BroadcastReceive size=%d x=%d", n - 4, (int)header);
        xlog_hex("rx", buf + 4, n > 4 ? (uint32_t)(n - 4 < 64 ? n - 4 : 64) : 0);
        if (cb_broadcast)
            cb_broadcast(buf + 4, (unsigned short)(n - 4), header);
    }
}

static void host_accept(void)
{
    Stream *listener = conn(0);
    int rounds;
    for (rounds = 0; rounds < 8 && accepting && listener && listener->sock >= 0; rounds++) {
        uint32_t ip = 0;
        unsigned id;
        uint16_t id16;
        Stream *s;
        int c = host_net_tcp_accept(listener->sock, &ip);
        if (c < 0)
            return;
        s = stream_new(c);
        if (!s)
            continue;
        s->live = 1;
        for (id = 0; id < table_size && table[id]; id++)
            ;
        if (id >= table_size) {
            xlog("Could not allocate new position");
            stream_free(s);
            continue;
        }
        s->id = (int)id;
        table[id] = s;
        /* The original sleeps 500 ms, sends the id, then calls
           NewClientConnection; here the id record waits in the queue
           (before anything else for this client) for those 500 ms. */
        s->hold_until = now_us() + ID_DELAY_US;
        s->greeting = 1;
        id16 = (uint16_t)id;
        stream_send(s, 2, &id16, TAG_YOUR_ID);
        xlog("accepted %u.%u.%u.%u as id %u", ip >> 24, (ip >> 16) & 255, (ip >> 8) & 255, ip & 255, id);
    }
}

/* The host's held id records whose time has come (0, 1 streams changed). */
static int host_greetings(void)
{
    unsigned i;
    for (i = 1; i < table_size; i++) {
        Stream *s = table[i];
        if (s && s->greeting && now_us() >= s->hold_until) {
            unsigned gen = generation;
            s->greeting = 0;
            s->hold_until = 0;
            if (stream_drain(s) < 0) {
                connection_lost(s);
                return 1;
            }
            xlog("CB NewClientConnection count=%u id=%u", connections_used(), i);
            if (cb_new_client)
                cb_new_client((unsigned short)connections_used(), (unsigned short)i);
            if (gen != generation)
                return 1;
        }
    }
    return 0;
}

/* One stream's I/O and records (0, 1 streams changed). */
static int poll_stream(Stream *s)
{
    unsigned gen = generation;
    if (!s || s->sock < 0 || !s->live || s->dead || s->hold_until)
        return 0;
    if (s->connecting) {
        int st = host_net_tcp_state(s->sock);
        if (st == 0)
            return 0;
        if (st < 0) {
            /* FD_CONNECT failure: the socket closed; the timeout tells the game */
            xlog("FD_CONNECT failure");
            stream_close_socket(s);
            return 0;
        }
        s->connecting = 0;
        xlog("connected");
    }
    if (stream_drain(s) < 0) {
        connection_lost(s);
        return 1;
    }
    if (stream_read(s) < 0) {
        /* the peer closed: its last records first (FD_READ before FD_CLOSE) */
        if (stream_dispatch(s) || gen != generation)
            return 1;
        xlog("FD_CLOSE");
        connection_lost(s);
        return 1;
    }
    return stream_dispatch(s);
}

static int polling;

static void poll_all(void)
{
    int rounds;
    if (proto != 0)
        return;
    polling++;
    poll_broadcast();
    for (rounds = 0; rounds < 8 && proto == 0; rounds++) {
        int again = 0;
        if (is_host) {
            unsigned i;
            host_accept();
            if (host_greetings())
                continue;
            for (i = 1; i < table_size && !again; i++)
                again = poll_stream(table[i]);
        } else {
            again = poll_stream(server);
            if (!again && timer_on && my_id == -1 && now_us() - timer_start >= timer_ms * 1000)
                client_connect_failed();
        }
        if (!again)
            break;
    }
    polling--;
}

/* From the message loop (PeekMessage): the network's events, its callbacks
 * run.  Nothing to do outside network games. */
void xd_poll(void)
{
    static uint64_t last;
    uint64_t t;
    if (proto != 0)
        return;
    t = now_us();
    if (t - last < 1000 && polling == 0)
        return;     /* (a busy message loop peeks very often) */
    last = t;
    poll_all();
}

/* ---- the library's API ---- */

int XD_SetBroadcastReceive(XD_BroadcastReceiveCB callback) { cb_broadcast = callback; xlog("XD_SetBroadcastReceive"); return 0; }
int XD_SetSecureReceive(XD_SecureReceiveCB callback) { cb_secure = callback; return 0; }
int XD_SetNewClientConnection(XD_NewClientCB callback) { cb_new_client = callback; return 0; }
int XD_SetOnClientConnectionToServer(XD_ConnectedCB callback) { cb_connected = callback; return 0; }
int XD_SetOnConnectionLost(XD_ConnectionLostCB callback) { cb_lost = callback; return 0; }

int XD_SetOversizedMessageCB(unsigned long limit, XD_OversizedMessageCB callback)
{
    cb_oversized = callback;
    size_limit = callback ? limit : 0xFFFFFFF0u;
    return 0;
}

int XD_GetXDaemonVersion(int *major, int *minor, int *patch)
{
    *major = 3;
    *minor = 5;
    *patch = 0;
    return 0;
}

/* The DirectPlay lobby: never launched by one. */
int XD_LaunchedByLobby(void *hwnd, LobbyLaunchInfo *info) { (void)hwnd; (void)info; return -3; }
int XD_LobbySendMessage(int message) { (void)message; return -2; }

/* Not provided: IPX/SPX, modem, serial ("TEN"). */
int XD_InitializeSocketsIPXSPX(int version, int port, int port2, int is_server, unsigned max_players,
                               XD_BroadcastReceiveCB callback)
{
    (void)version; (void)port; (void)port2; (void)is_server; (void)max_players; (void)callback;
    return -5;
}
int XD_InitializeModem(int is_server) { (void)is_server; return -1; }
int XD_InitializeSerial(int is_server) { (void)is_server; return -1; }
int XD_ShutdownModem(void) { return 0; }
int XD_ShutdownTEN(void) { return 0; }

int XD_InitializeSocketsTCP(int version, int port, int port2, int is_server, unsigned max_players,
                            XD_BroadcastReceiveCB callback)
{
    int r = 0;
    if (proto != -1)
        r = -4;
    else if (max_players > MAX_TABLE)
        r = -11;
    else if (!cb_broadcast && !callback)
        r = -9;
    else {
        if (!cb_broadcast)
            cb_broadcast = callback;
        use_secure = version == 1 || version == 3;
        use_broadcast = version == 2 || version == 3;
        if (!use_secure && !use_broadcast)
            r = -9;
        else if (!use_secure && is_server)
            r = -9;
    }
    if (!r) {
        secure_port = port;
        broadcast_port = port2;
        if (use_broadcast) {
            if (udp >= 0)
                host_net_close(udp);
            udp = host_net_udp_open(port2);
            if (udp < 0)
                r = -5;
        }
    }
    if (!r && use_secure) {
        Stream *s;
        stream_free(server);
        server = NULL;
        s = stream_new(host_net_tcp_open(is_server ? port : 0));
        if (!s || s->sock < 0) {
            free(s);
            r = -5;
        } else if (!is_server) {
            is_host = 0;
            server = s;
        } else {
            is_host = 1;
            my_id = 0;
            free(table);
            table_size = max_players;
            table = calloc(table_size ? table_size : 1, sizeof *table);
            server = s;
            if (table_size) {
                s->id = 0;
                table[0] = s;
            }
        }
    }
    if (!r)
        proto = 0;
    xlog("XD_InitializeSocketsTCP(v=%d, port=%d, port2=%d, server=%d, max=%u) = %d", version, port, port2, is_server,
         max_players, r);
    return r;
}

int XD_ActivateServer(void)
{
    int r;
    if (proto == -1)
        r = -1;
    else if (!is_host)
        r = -6;
    else if (!conn(0) || conn(0)->sock < 0)
        r = -3;
    else if (host_net_tcp_listen(conn(0)->sock, 5) != 0)
        r = -5;
    else {
        accepting = 1;
        r = 0;
    }
    xlog("XD_ActivateServer() = %d", r);
    return r;
}

int XD_StopConnections(void)
{
    xlog("XD_StopConnections()");
    if (proto == -1)
        return -1;
    if (!is_host)
        return -6;
    if (!conn(0))
        return -1;
    accepting = 0;      /* (the listener stays open) */
    return 1;
}

int XD_OpenConnection(void *address, unsigned long timeout_ms)
{
    const char *text = address;
    unsigned a, b, c, d;
    char end;
    int r;
    if (is_host)
        r = -7;
    else if (!cb_connected)
        r = -15;
    else {
        my_id = -1;
        if (proto != 0)
            r = proto == -1 ? -1 : -10;
        else if (!use_secure)
            r = -14;
        else if (!server)
            r = -1;
        else {
            /* inet_addr: a dotted quad; anything else gives an address
               connect() refuses */
            uint32_t ip = 0xFFFFFFFFu;
            if (sscanf(text, "%u.%u.%u.%u%c", &a, &b, &c, &d, &end) == 4 && a < 256 && b < 256 && c < 256 && d < 256)
                ip = a << 24 | b << 16 | c << 8 | d;
            stream_close_socket(server);
            server->dead = 0;
            server->sock = host_net_tcp_open(0);
            if (ip != 0xFFFFFFFFu && server->sock >= 0 && host_net_tcp_connect(server->sock, ip, secure_port) == 0) {
                server->connecting = server->live = 1;
                timer_on = 1;
                timer_start = now_us();
                timer_ms = timeout_ms;
                r = 0;
            } else {
                client_fresh_socket();
                r = -10;
            }
        }
    }
    xlog("XD_OpenConnection('%s', %lu) = %d", text ? text : "", timeout_ms, r);
    return r;
}

int XD_SendSecureData(unsigned short to, void *data, unsigned long len, short flags)
{
    uint32_t tag;
    int r;
    if (proto == -1)
        return -1;
    if (!use_secure)
        return -14;
    if (my_id == (int)to) {
        xlog("Error: Attempting to transmit data to self");
        return -9;
    }
    if (!server)
        return -5;
    xlog("XD_SendSecureData(to=%u, size=%lu, flags=%d)", to, len, flags);
    xlog_hex("tx", data, len < 64 ? (uint32_t)len : 64);
    if (to == 0xFF && is_host) {
        int ok = 1;
        unsigned i;
        for (i = 1; i < table_size; i++) {
            Stream *s = conn(i);
            if (!s)
                continue;
            tag = (uint32_t)(((my_id & 0xFF) << 8 | i) & 0xFFFF) << 16 | (uint16_t)flags;
            r = stream_send(s, (uint32_t)len, data, tag);
            if (r < 0) {
                ok = 0;
                if (r == -4)
                    connection_lost(s);
            }
        }
        return ok ? (int)len : -13;
    }
    tag = (uint32_t)(((my_id & 0xFF) << 8 | (to & 0xFF)) & 0xFFFF) << 16 | (uint16_t)flags;
    if (!is_host) {
        r = stream_send(server, (uint32_t)len, data, tag);
        if (r == -4)
            connection_lost(server);
        return r;
    }
    if (!conn(to))
        return -13;
    r = stream_send(conn(to), (uint32_t)len, data, tag);
    if (r == -4)
        connection_lost(conn(to));
    return r;
}

int XD_SendBroadcastData(void *data, unsigned long len, long header)
{
    unsigned char buf[UDP_PAYLOAD + 4];
    uint32_t n = (uint32_t)(len & 0xFFFF);
    int32_t h = (int32_t)header;
    int r;
    if (proto == -1)
        return -1;
    if (!use_broadcast)
        return -14;
    if (udp < 0)
        return -3;
    if (n > UDP_PAYLOAD)
        n = UDP_PAYLOAD;
    memcpy(buf, &h, 4);
    if (data)
        memcpy(buf + 4, data, n);
    r = host_net_udp_send(udp, 0xFFFFFFFFu, broadcast_port, buf, (int)n + 4);
    xlog("XD_SendBroadcastData(size=%lu, flags=%ld) = %d", len, header, r);
    xlog_hex("tx", data, n < 64 ? n : 64);
    return r;
}

static int queued_items(void)
{
    int n = 0;
    unsigned i;
    if (!is_host)
        return server ? server->items : 0;
    for (i = 0; i < table_size; i++)
        if (table[i])
            n += table[i]->items;
    return n;
}

/* Pumps the thread's messages (the game's included, as the original) until
 * everything queued is sent or timeout_ms passed: what is left. */
int XD_FlushSendBuffer(unsigned long timeout_ms)
{
    DWORD start;
    int left = 1;
    MSG m;
    if (proto == -1)
        return -1;
    in_flush = 1;
    start = GetTickCount();
    do {
        if (GetTickCount() - start >= timeout_ms)
            break;
        left = 0;
        if (PeekMessageA(&m, 0, 0, 0, PM_REMOVE)) {
            TranslateMessage(&m);
            DispatchMessageA(&m);
        }
        xd_poll();
        if (proto == -1)
            break;
        left = queued_items();
    } while (left != 0);
    if (left > 0)
        xlog("XD_FlushSendBuffer has run out of time: %d items remaining", left);
    in_flush = 0;
    return left;
}

int XD_InFlushSendBuffer(void) { return in_flush; }

int XD_ServerCloseConnection(unsigned short id)
{
    xlog("XD_ServerCloseConnection(%u)", id);
    if (proto == -1)
        return -1;
    if (!is_host)
        return -6;
    if (id >= table_size || !conn(id))
        return -9;
    stream_free(conn(id));
    return 0;
}

int XD_CloseConnection(void)
{
    unsigned i;
    xlog("XD_CloseConnection()");
    if (proto == -1)
        return -1;
    if (!is_host) {
        timer_on = 0;
        client_fresh_socket();
        if (!server)
            proto = -1;
    } else
        for (i = 1; i < table_size; i++)
            if (conn(i))
                stream_free(conn(i));
    my_id = -1;
    return 0;
}

int XD_ShutdownSockets(void)
{
    unsigned i;
    xlog("XD_ShutdownSockets()");
    if (udp >= 0)
        host_net_close(udp);
    udp = -1;
    if (is_host)
        for (i = 1; i < table_size; i++)
            if (conn(i))
                stream_free(conn(i));
    is_host = 0;
    stream_free(server);
    server = NULL;
    free(table);
    table = NULL;
    table_size = 0;
    accepting = 0;
    timer_on = 0;
    my_id = -1;
    proto = -1;
    return 0;
}

int XD_ResetLibrary(void)
{
    if (proto == 0)
        XD_ShutdownSockets();
    my_id = -1;
    proto = -1;
    is_host = 0;
    use_secure = use_broadcast = 0;
    accepting = 0;
    timer_on = 0;
    return 0;
}

/* The local address as text (adapter 0; TCP/IP only). */
char *XD_GetCurrentProtoAddr(unsigned adapter, int protocol)
{
    static char addr[52];
    const char *env = getenv("CIV2_NET_ADDR");
    memset(addr, 0, sizeof addr);
    if (protocol != 0)
        return NULL;
    if (adapter == 0) {
        if (env && *env)
            snprintf(addr, sizeof addr, "%s", env);
        else
            host_net_local_addr(addr, (int)sizeof addr);
    }
    xlog("XD_GetCurrentProtoAddr(%u,%d) = '%s'", adapter, protocol, addr);
    return addr;
}
