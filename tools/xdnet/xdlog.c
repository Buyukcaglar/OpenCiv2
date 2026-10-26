/* Logging proxy for the original XDaemon.dll (renamed XDaemon_real.dll):
   logs every interesting XD_* call with its arguments and payload bytes,
   and wraps the game's receive callbacks to log what arrives.
   Log file: %XDLOG% (Windows path), default xdlog.txt in the game dir. */
#include <windows.h>
#include <stdio.h>
#include <stdarg.h>

void *xd_real[64];
#include "stubs.h"

static HANDLE logf_h = INVALID_HANDLE_VALUE;
static CRITICAL_SECTION lk;
static DWORD t0;

static void lg(const char *fmt, ...)
{
    char buf[8192]; int n; DWORD w; va_list ap;
    n = snprintf(buf, 64, "%7lu t%04lx ", GetTickCount() - t0, GetCurrentThreadId() & 0xffff);
    va_start(ap, fmt); n += vsnprintf(buf + n, sizeof buf - n - 2, fmt, ap); va_end(ap);
    if (n > (int)sizeof buf - 2) n = sizeof buf - 2;
    buf[n++] = '\n';
    EnterCriticalSection(&lk);
    WriteFile(logf_h, buf, n, &w, NULL);
    LeaveCriticalSection(&lk);
}

static void hex(const char *tag, const void *p, unsigned long len)
{
    const unsigned char *b = p; unsigned long i, max = len > 4096 ? 4096 : len;
    char line[200];
    if (!p) return;
    for (i = 0; i < max; i += 32) {
        int n = 0; unsigned long j;
        for (j = i; j < i + 32 && j < max; j++) n += sprintf(line + n, "%02x", b[j]);
        lg("  %s %04lx: %s", tag, i, line);
    }
    if (max < len) lg("  %s ... (%lu bytes total)", tag, len);
}

#define REAL(name) ((void *)xd_real[IDX_##name])

/* Wine/Linux report SO_RCVBUF as 128K+; XDaemon stores the buffer size in a
   16-bit field, so it would recv() with length 0 forever.  Report Windows 9x's
   8192 instead (does not change anything on the wire).  CLAMP_RCVBUF=0 disables. */
typedef int (WINAPI *getsockopt_t)(unsigned, int, int, char *, int *);
static getsockopt_t real_getsockopt;
static int clamp_on = 1;
static int WINAPI my_getsockopt(unsigned s, int level, int name, char *val, int *len)
{
    int r = real_getsockopt(s, level, name, val, len);
    if (r == 0 && level == 0xffff && (name == 0x1002 || name == 0x1001) && *len >= 4) {
        int v = *(int *)val;
        if (clamp_on && v > 0xffff) *(int *)val = 8192;
        lg("getsockopt(sock=%u, %s) = %d -> %d", s, name == 0x1002 ? "SO_RCVBUF" : "SO_SNDBUF", v, *(int *)val);
    }
    return r;
}

static void patch_iat(HMODULE m)
{
    BYTE *base = (BYTE *)m;
    IMAGE_NT_HEADERS *nt = (IMAGE_NT_HEADERS *)(base + ((IMAGE_DOS_HEADER *)base)->e_lfanew);
    IMAGE_IMPORT_DESCRIPTOR *d = (IMAGE_IMPORT_DESCRIPTOR *)(base + nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
    for (; d->Name; d++) {
        IMAGE_THUNK_DATA *o, *f;
        if (lstrcmpiA((char *)base + d->Name, "WSOCK32.dll")) continue;
        o = (IMAGE_THUNK_DATA *)(base + d->OriginalFirstThunk); f = (IMAGE_THUNK_DATA *)(base + d->FirstThunk);
        for (; o->u1.Ordinal; o++, f++)
            if (IMAGE_SNAP_BY_ORDINAL(o->u1.Ordinal) && IMAGE_ORDINAL(o->u1.Ordinal) == 7) {
                DWORD old;
                real_getsockopt = (getsockopt_t)f->u1.Function;
                VirtualProtect(&f->u1.Function, 4, PAGE_READWRITE, &old);
                f->u1.Function = (DWORD)my_getsockopt;
                VirtualProtect(&f->u1.Function, 4, old, &old);
                lg("patched XDaemon's getsockopt import");
            }
    }
}

BOOL WINAPI DllMain(HINSTANCE h, DWORD reason, LPVOID r)
{
    if (reason == DLL_PROCESS_ATTACH) {
        char path[MAX_PATH]; HMODULE m; int i;
        InitializeCriticalSection(&lk);
        t0 = GetTickCount();
        if (!GetEnvironmentVariableA("XDLOG", path, sizeof path)) strcpy(path, "xdlog.txt");
        logf_h = CreateFileA(path, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, 0, NULL);
        m = LoadLibraryA("XDaemon_orig.dll");
        if (!m) { lg("cannot load XDaemon_orig.dll"); return FALSE; }
        for (i = 0; i < NXD; i++) xd_real[i] = (void *)GetProcAddress(m, xd_names[i]);
        lg("proxy loaded, tick0=%lu", t0);
        if (GetEnvironmentVariableA("CLAMP_RCVBUF", path, sizeof path) && path[0] == '0') clamp_on = 0;
        patch_iat(m);
    }
    return TRUE;
}

/* ---- callbacks ---- */
typedef void (*BcastCB)(void *, unsigned short, long);
typedef void (*SecureCB)(unsigned short, void *, unsigned long, short);
typedef void (*NewClientCB)(unsigned short, unsigned short);
typedef void (*ConnCB)(short);
typedef void (*LostCB)(unsigned short);
typedef void (*OversizeCB)(unsigned long);
static BcastCB g_bcast, g_init_cb; static SecureCB g_secure; static NewClientCB g_newc;
static ConnCB g_conn; static LostCB g_lost; static OversizeCB g_over;

static void cb_bcast(void *m, unsigned short sz, long x)
{ lg("CB BroadcastReceive size=%u x=%ld", sz, x); hex("rx", m, sz); if (g_bcast) g_bcast(m, sz, x); }
static void cb_initcb(void *m, unsigned short sz, long x)
{ lg("CB InitCallback size=%u x=%ld", sz, x); hex("rx", m, sz); if (g_init_cb) g_init_cb(m, sz, x); }
static void cb_secure(unsigned short id, void *m, unsigned long sz, short x)
{ lg("CB SecureReceive from=%u size=%lu x=%d", id, sz, x); hex("rx", m, sz); if (g_secure) g_secure(id, m, sz, x); }
static void cb_newc(unsigned short a, unsigned short b)
{ lg("CB NewClientConnection a=%u b=%u", a, b); if (g_newc) g_newc(a, b); }
static void cb_conn(short id)
{ lg("CB ClientConnectionToServer id=%d", id); if (g_conn) g_conn(id); }
static void cb_lost(unsigned short id)
{ lg("CB ConnectionLost id=%u", id); if (g_lost) g_lost(id); }
static void cb_over(unsigned long sz)
{ lg("CB Oversized size=%lu", sz); if (g_over) g_over(sz); }

/* ---- wrapped calls (all __cdecl) ---- */
int w_XD_ActivateServer(void)
{ int r = ((int (*)(void))REAL(XD_ActivateServer))(); lg("XD_ActivateServer() = %d", r); return r; }
int w_XD_CloseConnection(void)
{ int r = ((int (*)(void))REAL(XD_CloseConnection))(); lg("XD_CloseConnection() = %d", r); return r; }
int w_XD_FlushSendBuffer(unsigned long t)
{ int r; lg("XD_FlushSendBuffer(%lu) ...", t); r = ((int (*)(unsigned long))REAL(XD_FlushSendBuffer))(t); lg("XD_FlushSendBuffer = %d", r); return r; }
char *w_XD_GetCurrentProtoAddr(unsigned a, int p)
{ char *r = ((char *(*)(unsigned, int))REAL(XD_GetCurrentProtoAddr))(a, p); lg("XD_GetCurrentProtoAddr(%u,%d) = '%s'", a, p, r ? r : "(null)"); return r; }
char *w_XD_GetConnectedSocketAddr(void)
{ char *r = ((char *(*)(void))REAL(XD_GetConnectedSocketAddr))(); lg("XD_GetConnectedSocketAddr() = '%s'", r ? r : "(null)"); return r; }
int w_XD_GetXDaemonVersion(int *a, int *b, int *c)
{ int r = ((int (*)(int *, int *, int *))REAL(XD_GetXDaemonVersion))(a, b, c); lg("XD_GetXDaemonVersion = %d (%d.%d.%d)", r, *a, *b, *c); return r; }
int w_XD_InitializeSocketsTCP(int v, int port, int port2, int server, unsigned maxp, BcastCB cb)
{
    int r; g_init_cb = cb;
    r = ((int (*)(int, int, int, int, unsigned, BcastCB))REAL(XD_InitializeSocketsTCP))(v, port, port2, server, maxp, cb ? cb_initcb : NULL);
    lg("XD_InitializeSocketsTCP(v=%d, port=%d, port2=%d, server=%d, max=%u, cb=%p) = %d", v, port, port2, server, maxp, cb, r);
    return r;
}
int w_XD_OpenConnection(void *addr, unsigned long t)
{ int r; lg("XD_OpenConnection('%s', %lu) ...", (char *)addr, t); r = ((int (*)(void *, unsigned long))REAL(XD_OpenConnection))(addr, t); lg("XD_OpenConnection = %d", r); return r; }
int w_XD_ResetLibrary(void)
{ int r = ((int (*)(void))REAL(XD_ResetLibrary))(); lg("XD_ResetLibrary() = %d", r); return r; }
int w_XD_SendBroadcastData(void *m, unsigned long sz, long fl)
{ int r = ((int (*)(void *, unsigned long, long))REAL(XD_SendBroadcastData))(m, sz, fl); lg("XD_SendBroadcastData(size=%lu, flags=%ld) = %d", sz, fl, r); hex("tx", m, sz); return r; }
int w_XD_SendSecureData(unsigned short to, void *m, unsigned long sz, short fl)
{ int r = ((int (*)(unsigned short, void *, unsigned long, short))REAL(XD_SendSecureData))(to, m, sz, fl); lg("XD_SendSecureData(to=%u, size=%lu, flags=%d) = %d", to, sz, fl, r); hex("tx", m, sz); return r; }
int w_XD_SendUDPBroadcastData(void *m, unsigned long sz, long fl, const char *a, int b)
{ int r = ((int (*)(void *, unsigned long, long, const char *, int))REAL(XD_SendUDPBroadcastData))(m, sz, fl, a, b); lg("XD_SendUDPBroadcastData(size=%lu, %ld, '%s', %d) = %d", sz, fl, a ? a : "", b, r); hex("tx", m, sz); return r; }
int w_XD_SendDirectBroadcastData(void *m, void *a, unsigned long sz)
{ int r = ((int (*)(void *, void *, unsigned long))REAL(XD_SendDirectBroadcastData))(m, a, sz); lg("XD_SendDirectBroadcastData(size=%lu) = %d", sz, r); hex("tx", m, sz); return r; }
int w_XD_ServerCloseConnection(unsigned short id)
{ int r = ((int (*)(unsigned short))REAL(XD_ServerCloseConnection))(id); lg("XD_ServerCloseConnection(%u) = %d", id, r); return r; }
int w_XD_StopConnections(void)
{ int r = ((int (*)(void))REAL(XD_StopConnections))(); lg("XD_StopConnections() = %d", r); return r; }
void w_XD_ShutdownSockets(void)
{ lg("XD_ShutdownSockets()"); ((void (*)(void))REAL(XD_ShutdownSockets))(); }
int w_XD_EnableServerLocator(int a, unsigned b)
{ int r = ((int (*)(int, unsigned))REAL(XD_EnableServerLocator))(a, b); lg("XD_EnableServerLocator(%d, %u) = %d", a, b, r); return r; }
int w_XD_LaunchedByLobby(void *h, void *info)
{ int r = ((int (*)(void *, void *))REAL(XD_LaunchedByLobby))(h, info); lg("XD_LaunchedByLobby = %d", r); return r; }
int w_XD_LobbySendMessage(unsigned long m)
{ int r = ((int (*)(unsigned long))REAL(XD_LobbySendMessage))(m); lg("XD_LobbySendMessage(%lu) = %d", m, r); return r; }
void w_XD_SetBroadcastReceive(BcastCB cb)
{ g_bcast = cb; lg("XD_SetBroadcastReceive(%p)", cb); ((void (*)(BcastCB))REAL(XD_SetBroadcastReceive))(cb ? cb_bcast : NULL); }
void w_XD_SetSecureReceive(SecureCB cb)
{ g_secure = cb; lg("XD_SetSecureReceive(%p)", cb); ((void (*)(SecureCB))REAL(XD_SetSecureReceive))(cb ? cb_secure : NULL); }
void w_XD_SetNewClientConnection(NewClientCB cb)
{ g_newc = cb; lg("XD_SetNewClientConnection(%p)", cb); ((void (*)(NewClientCB))REAL(XD_SetNewClientConnection))(cb ? cb_newc : NULL); }
void w_XD_SetOnClientConnectionToServer(ConnCB cb)
{ g_conn = cb; lg("XD_SetOnClientConnectionToServer(%p)", cb); ((void (*)(ConnCB))REAL(XD_SetOnClientConnectionToServer))(cb ? cb_conn : NULL); }
void w_XD_SetOnConnectionLost(LostCB cb)
{ g_lost = cb; lg("XD_SetOnConnectionLost(%p)", cb); ((void (*)(LostCB))REAL(XD_SetOnConnectionLost))(cb ? cb_lost : NULL); }
int w_XD_SetOversizedMessageCB(unsigned long max, OversizeCB cb)
{ g_over = cb; lg("XD_SetOversizedMessageCB(%lu, %p)", max, cb); return ((int (*)(unsigned long, OversizeCB))REAL(XD_SetOversizedMessageCB))(max, cb ? cb_over : NULL); }
