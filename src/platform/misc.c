/*
 * Services the native build does not provide (DirectDraw, AVI video,
 * network play), message boxes, file dialogs, common controls.
 */
#include "plat.h"
#include "../host/host.h"
#include "xdaemon.h"

/* ---- DirectDraw: not available; the game uses GDI ---- */

HRESULT WINAPI DirectDrawCreate(GUID *guid, LPDIRECTDRAW *dd, IUnknown *outer)
{
    API_TRACE();
    (void)guid; (void)outer;
    if (dd)
        *dd = NULL;
    return (HRESULT)0x88760255u;     /* DDERR_NODIRECTDRAWHW */
}

/* AVI files and the IV41 codec: video.c */

HWND MCIWndCreateA(HWND parent, HINSTANCE inst, DWORD style, LPCSTR file)
{
    API_TRACE();
    (void)parent; (void)inst; (void)style; (void)file;
    return 0;
}

void Ordinal_17(void) {}

/* ---- message boxes ---- */

int WINAPI MessageBoxA(HWND owner, LPCSTR text, LPCSTR caption, UINT type)
{
    API_TRACE();
    const char *labels[3];
    int ids[3], n = 0, enter = 0, escape, hit;
    (void)owner;
    plat_log("MessageBox: %s: %s\n", caption ? caption : "", text ? text : "");
    switch (type & MB_TYPEMASK) {
    case MB_OKCANCEL:
        labels[n] = "OK"; ids[n++] = IDOK;
        labels[n] = "Cancel"; ids[n++] = IDCANCEL;
        break;
    case MB_YESNO:
        labels[n] = "Yes"; ids[n++] = IDYES;
        labels[n] = "No"; ids[n++] = IDNO;
        break;
    case MB_YESNOCANCEL:
        labels[n] = "Yes"; ids[n++] = IDYES;
        labels[n] = "No"; ids[n++] = IDNO;
        labels[n] = "Cancel"; ids[n++] = IDCANCEL;
        break;
    default:
        labels[n] = "OK"; ids[n++] = IDOK;
    }
    escape = n - 1;
    if (plat_replay)
        return ids[0];
    hit = host_message_box((type & MB_ICONMASK) == MB_ICONERROR ? 2 : (type & MB_ICONMASK) == MB_ICONWARNING ? 1 : 0,
                           caption ? caption : "Civilization II", text ? text : "", n, labels, ids, enter, escape);
    return hit < 0 ? ids[n - 1] : hit;
}

WINBOOL WINAPI MessageBeep(UINT type) { API_TRACE(); (void)type; return TRUE; }

/* ---- file dialogs ---- */

DWORD WINAPI CommDlgExtendedError(void) { API_TRACE(); return 0; }

/* Without a native dialog, the scripted answer (replay) or a name typed
 * on the terminal. */
static WINBOOL file_dialog(OPENFILENAMEA *ofn, const char *kind)
{
    static int real = -1;
    if (real < 0)
        real = getenv("CIV2_REAL_FILEDLG") != NULL;     /* test the dialog itself in a replay */
    if (plat_replay && !real)
        return replay_file_dialog(ofn, kind);
    return plat_file_dialog(ofn, !strcmp(kind, "Save"));
}

WINBOOL WINAPI GetOpenFileNameA(LPOPENFILENAMEA ofn) { API_TRACE(); return file_dialog(ofn, "Open"); }
WINBOOL WINAPI GetSaveFileNameA(LPOPENFILENAMEA ofn) { API_TRACE(); return file_dialog(ofn, "Save"); }

/* ---- XDaemon (network play): the library as it behaves with no network
 * game set up (the reference run's smeds.log: "Not an IGZ Game!! event = -3",
 * XDaemon v3.5.0). ---- */

#define XD_OK(name, ...) int name(__VA_ARGS__) { return 0; }
#define XD_FAIL(name, ...) int name(__VA_ARGS__) { return -1; }
XD_FAIL(XD_ActivateServer, void)
XD_OK(XD_CloseConnection, void)
XD_OK(XD_FlushSendBuffer, int timeout_ms)
XD_OK(XD_InFlushSendBuffer, void)
XD_FAIL(XD_InitializeModem, int is_server)
XD_FAIL(XD_InitializeSerial, int is_server)
XD_FAIL(XD_InitializeSocketsIPXSPX, int version, int port, int port2, int is_server, int max_players, void *callback)
XD_FAIL(XD_InitializeSocketsTCP, int version, int port, int port2, int is_server, int max_players, void *callback)
XD_OK(XD_LobbySendMessage, int message)
XD_FAIL(XD_OpenConnection, const char *address, int timeout_ms)
XD_OK(XD_ResetLibrary, void)
XD_FAIL(XD_SendBroadcastData, void *msg, unsigned long size, int flags)
XD_FAIL(XD_SendSecureData, unsigned short player, void *msg, unsigned long size, int flags)
XD_OK(XD_ServerCloseConnection, unsigned short conn_id)
XD_OK(XD_SetBroadcastReceive, XD_BroadcastReceiveCB callback)
XD_OK(XD_SetNewClientConnection, XD_NewClientCB callback)
XD_OK(XD_SetOnClientConnectionToServer, XD_ConnectedCB callback)
XD_OK(XD_SetOnConnectionLost, XD_ConnectionLostCB callback)
XD_OK(XD_SetOversizedMessageCB, int max_size, XD_OversizedMessageCB callback)
XD_OK(XD_SetSecureReceive, XD_SecureReceiveCB callback)
XD_OK(XD_ShutdownModem, void)
XD_OK(XD_ShutdownSockets, void)
XD_OK(XD_ShutdownTEN, void)
XD_OK(XD_StopConnections, void)

char *XD_GetCurrentProtoAddr(int adapter, int protocol) { static char none[1]; (void)adapter; (void)protocol; return none; }

int XD_GetXDaemonVersion(int *major, int *minor, int *patch)
{
    API_TRACE();
    *major = 3;
    *minor = 5;
    *patch = 0;
    return 0;
}

int XD_LaunchedByLobby(void *hwnd, LobbyLaunchInfo *info) { (void)hwnd; (void)info; return -3; }
