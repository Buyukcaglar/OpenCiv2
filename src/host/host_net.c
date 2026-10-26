/*
 * Network sockets for network play (host.h, host_net_*): non-blocking
 * IPv4 TCP and UDP over BSD sockets, or Winsock on Windows.  The game's
 * networking library (src/platform/xdaemon.c) polls them from the message
 * loop.  Handles are small ints (indices into a table here); addresses
 * are IPv4 in host byte order (a.b.c.d = a << 24 | b << 16 | c << 8 | d).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "host.h"

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
typedef SOCKET sock_t;
#define BAD_SOCK INVALID_SOCKET
#define sock_close closesocket
#define sock_err() WSAGetLastError()
#define ERR_WOULDBLOCK(e) ((e) == WSAEWOULDBLOCK)
#define ERR_INPROGRESS(e) ((e) == WSAEWOULDBLOCK || (e) == WSAEINPROGRESS)
#define SEND_FLAGS 0
typedef int socklen_t_;
#else
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
typedef int sock_t;
#define BAD_SOCK (-1)
#define sock_close close
#define sock_err() errno
#define ERR_WOULDBLOCK(e) ((e) == EWOULDBLOCK || (e) == EAGAIN)
#define ERR_INPROGRESS(e) ((e) == EINPROGRESS || (e) == EWOULDBLOCK || (e) == EAGAIN)
#ifdef MSG_NOSIGNAL
#define SEND_FLAGS MSG_NOSIGNAL
#else
#define SEND_FLAGS 0
#endif
typedef socklen_t socklen_t_;
#endif

#define MAX_SOCKS 64

static struct {
    int used;
    sock_t s;
    int connecting;     /* a TCP connect() still in progress */
} socks[MAX_SOCKS];

static int started;

static int net_start(void)
{
#ifdef _WIN32
    if (!started) {
        WSADATA wsa;
        if (WSAStartup(MAKEWORD(2, 2), &wsa))
            return 0;
    }
#endif
    started = 1;
    return 1;
}

static int non_blocking(sock_t s)
{
#ifdef _WIN32
    u_long on = 1;
    return ioctlsocket(s, FIONBIO, &on) == 0;
#else
    int fl = fcntl(s, F_GETFL, 0);
    return fl != -1 && fcntl(s, F_SETFL, fl | O_NONBLOCK) == 0;
#endif
}

static int set_opt(sock_t s, int level, int name, int value)
{
    return setsockopt(s, level, name, (const char *)&value, sizeof value) == 0;
}

/* A new handle for socket s (closed if the table is full). */
static int handle_new(sock_t s)
{
    int i;
    for (i = 0; i < MAX_SOCKS; i++)
        if (!socks[i].used) {
            socks[i].used = 1;
            socks[i].s = s;
            socks[i].connecting = 0;
            return i;
        }
    sock_close(s);
    return -1;
}

static sock_t sock_of(int h)
{
    return h >= 0 && h < MAX_SOCKS && socks[h].used ? socks[h].s : BAD_SOCK;
}

static void addr_in(struct sockaddr_in *a, uint32_t ip, int port)
{
    memset(a, 0, sizeof *a);
    a->sin_family = AF_INET;
    a->sin_addr.s_addr = htonl(ip);
    a->sin_port = htons((unsigned short)port);
}

static sock_t new_socket(int type)
{
    sock_t s;
    if (!net_start())
        return BAD_SOCK;
    s = socket(AF_INET, type, type == SOCK_STREAM ? IPPROTO_TCP : IPPROTO_UDP);
    if (s == BAD_SOCK)
        return BAD_SOCK;
    if (!non_blocking(s)) {
        sock_close(s);
        return BAD_SOCK;
    }
#ifdef SO_NOSIGPIPE
    set_opt(s, SOL_SOCKET, SO_NOSIGPIPE, 1);
#endif
    return s;
}

/* This machine's address as others reach it: the one the default route
 * leaves from (a UDP "connect" sends nothing), else the host name's
 * first non-loopback address, else 127.0.0.1. */
int HOST_API(host_net_local_addr)(char *buf, int size)
{
    struct sockaddr_in a;
    socklen_t_ len = sizeof a;
    uint32_t ip = 0;
    sock_t s;
    if (size <= 0)
        return 0;
    buf[0] = 0;
    if (!net_start())
        return 0;
    s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (s != BAD_SOCK) {
        addr_in(&a, 0x08080808u, 53);
        if (connect(s, (struct sockaddr *)&a, sizeof a) == 0 &&
            getsockname(s, (struct sockaddr *)&a, &len) == 0)
            ip = ntohl(a.sin_addr.s_addr);
        sock_close(s);
    }
    if (!ip || (ip >> 24) == 127) {
        char name[256];
        struct addrinfo hints, *res = NULL, *r;
        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_INET;
        if (gethostname(name, sizeof name) == 0 && getaddrinfo(name, NULL, &hints, &res) == 0) {
            for (r = res; r; r = r->ai_next) {
                uint32_t v = ntohl(((struct sockaddr_in *)r->ai_addr)->sin_addr.s_addr);
                if ((v >> 24) != 127 && v) {
                    ip = v;
                    break;
                }
            }
            freeaddrinfo(res);
        }
    }
    if (!ip)
        ip = 0x7f000001u;
    snprintf(buf, (size_t)size, "%u.%u.%u.%u", ip >> 24, (ip >> 16) & 255, (ip >> 8) & 255, ip & 255);
    return (int)strlen(buf);
}

/* UDP socket bound to INADDR_ANY:port, broadcasts allowed, the port
 * shared with other programs (every game on a machine hears them all). */
int HOST_API(host_net_udp_open)(int port)
{
    struct sockaddr_in a;
    sock_t s = new_socket(SOCK_DGRAM);
    if (s == BAD_SOCK)
        return -1;
    set_opt(s, SOL_SOCKET, SO_BROADCAST, 1);
    set_opt(s, SOL_SOCKET, SO_REUSEADDR, 1);
#ifdef SO_REUSEPORT
    set_opt(s, SOL_SOCKET, SO_REUSEPORT, 1);
#endif
    addr_in(&a, 0, port);
    if (bind(s, (struct sockaddr *)&a, sizeof a) != 0) {
        sock_close(s);
        return -1;
    }
    return handle_new(s);
}

/* Bytes sent, -1 on failure.  ip 0xFFFFFFFF: broadcast. */
int HOST_API(host_net_udp_send)(int h, uint32_t ip, int port, const void *p, int n)
{
    struct sockaddr_in a;
    sock_t s = sock_of(h);
    if (s == BAD_SOCK)
        return -1;
    addr_in(&a, ip, port);
    return (int)sendto(s, (const char *)p, n, SEND_FLAGS, (struct sockaddr *)&a, sizeof a);
}

/* One datagram: its length (cut to n), -1 if none is waiting. */
int HOST_API(host_net_udp_recv)(int h, void *p, int n, uint32_t *from_ip)
{
    struct sockaddr_in a;
    socklen_t_ len = sizeof a;
    sock_t s = sock_of(h);
    int r;
    if (s == BAD_SOCK)
        return -1;
    for (;;) {
        r = (int)recvfrom(s, (char *)p, n, 0, (struct sockaddr *)&a, &len);
        if (r >= 0)
            break;
#ifdef _WIN32
        if (sock_err() == WSAEMSGSIZE) {        /* cut to the buffer, as asked */
            r = n;
            break;
        }
        if (sock_err() == WSAECONNRESET)        /* (ICMP port unreachable from an earlier send) */
            continue;
#endif
        return -1;
    }
    if (from_ip)
        *from_ip = ntohl(a.sin_addr.s_addr);
    return r;
}

/* TCP socket, bound to INADDR_ANY:port if port != 0. */
int HOST_API(host_net_tcp_open)(int port)
{
    sock_t s = new_socket(SOCK_STREAM);
    if (s == BAD_SOCK)
        return -1;
    if (port) {
        struct sockaddr_in a;
#ifndef _WIN32
        set_opt(s, SOL_SOCKET, SO_REUSEADDR, 1);    /* (Windows' SO_REUSEADDR would share the port) */
#endif
        addr_in(&a, 0, port);
        if (bind(s, (struct sockaddr *)&a, sizeof a) != 0) {
            sock_close(s);
            return -1;
        }
    }
    return handle_new(s);
}

int HOST_API(host_net_tcp_listen)(int h, int backlog)
{
    sock_t s = sock_of(h);
    return s != BAD_SOCK && listen(s, backlog) == 0 ? 0 : -1;
}

/* A pending connection's handle, -1 if none. */
int HOST_API(host_net_tcp_accept)(int h, uint32_t *peer_ip)
{
    struct sockaddr_in a;
    socklen_t_ len = sizeof a;
    sock_t s = sock_of(h), c;
    if (s == BAD_SOCK)
        return -1;
    c = accept(s, (struct sockaddr *)&a, &len);
    if (c == BAD_SOCK)
        return -1;
    if (!non_blocking(c)) {
        sock_close(c);
        return -1;
    }
#ifdef SO_NOSIGPIPE
    set_opt(c, SOL_SOCKET, SO_NOSIGPIPE, 1);
#endif
    if (peer_ip)
        *peer_ip = ntohl(a.sin_addr.s_addr);
    return handle_new(c);
}

/* Starts connecting (host_net_tcp_state tells how it goes): 0, -1 failed. */
int HOST_API(host_net_tcp_connect)(int h, uint32_t ip, int port)
{
    struct sockaddr_in a;
    sock_t s = sock_of(h);
    if (s == BAD_SOCK)
        return -1;
    addr_in(&a, ip, port);
    if (connect(s, (struct sockaddr *)&a, sizeof a) == 0) {
        socks[h].connecting = 0;
        return 0;
    }
    if (ERR_INPROGRESS(sock_err())) {
        socks[h].connecting = 1;
        return 0;
    }
    return -1;
}

/* 1 connected, 0 still connecting, -1 failed. */
int HOST_API(host_net_tcp_state)(int h)
{
    sock_t s = sock_of(h);
    int err = 0, ready;
    socklen_t_ len = sizeof err;
    if (s == BAD_SOCK)
        return -1;
    if (!socks[h].connecting)
        return 1;
#ifdef _WIN32
    {
        fd_set w, e;
        struct timeval tv = {0, 0};
        FD_ZERO(&w);
        FD_ZERO(&e);
        FD_SET(s, &w);
        FD_SET(s, &e);
        if (select(0, NULL, &w, &e, &tv) < 0)
            return -1;
        if (FD_ISSET(s, &e))
            return -1;
        ready = FD_ISSET(s, &w);
    }
#else
    {
        struct pollfd pf;
        pf.fd = s;
        pf.events = POLLOUT;
        pf.revents = 0;
        if (poll(&pf, 1, 0) < 0)
            return errno == EINTR ? 0 : -1;
        ready = pf.revents != 0;
    }
#endif
    if (!ready)
        return 0;
    if (getsockopt(s, SOL_SOCKET, SO_ERROR, (char *)&err, &len) != 0 || err)
        return -1;
    socks[h].connecting = 0;
    return 1;
}

/* Bytes taken (maybe fewer than n), -1 would block, -2 the connection is dead. */
int HOST_API(host_net_tcp_send)(int h, const void *p, int n)
{
    sock_t s = sock_of(h);
    int r;
    if (s == BAD_SOCK)
        return -2;
    r = (int)send(s, (const char *)p, n, SEND_FLAGS);
    if (r >= 0)
        return r;
    return ERR_WOULDBLOCK(sock_err()) || ERR_INPROGRESS(sock_err()) ? -1 : -2;
}

/* Bytes read, 0 the peer closed, -1 nothing to read, -2 error. */
int HOST_API(host_net_tcp_recv)(int h, void *p, int n)
{
    sock_t s = sock_of(h);
    int r;
    if (s == BAD_SOCK)
        return -2;
    r = (int)recv(s, (char *)p, n, 0);
    if (r >= 0)
        return r;
    return ERR_WOULDBLOCK(sock_err()) ? -1 : -2;
}

/* A graceful close: no more sends (FIN), what the peer still sends is
 * read and dropped, then the socket is closed. */
void HOST_API(host_net_close)(int h)
{
    sock_t s = sock_of(h);
    char junk[1024];
    if (s == BAD_SOCK)
        return;
#ifdef _WIN32
    shutdown(s, SD_SEND);
#else
    shutdown(s, SHUT_WR);
#endif
    while (recv(s, junk, sizeof junk, 0) > 0)
        ;
    sock_close(s);
    socks[h].used = 0;
}
