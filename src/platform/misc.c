/*
 * Services the native build does not provide (DirectDraw, AVI video,
 * network play), message boxes, file dialogs, common controls.
 */
#include "plat.h"
#include "../host/host.h"

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

/* Defined with as many (unused) arguments as the game passes: wasm checks
 * that calls match.  XD_OK(name, n) / XD_FAIL(name, n): n arguments. */
#define XD_ARGS0 void
#define XD_ARGS1 int a
#define XD_ARGS2 int a, int b
#define XD_ARGS3 int a, int b, int c
#define XD_ARGS4 int a, int b, int c, int d
#define XD_ARGS6 int a, int b, int c, int d, int e, int f
#define XD_OK(name, n) int name(XD_ARGS##n) { return 0; }
#define XD_FAIL(name, n) int name(XD_ARGS##n) { return -1; }
XD_FAIL(XD_ActivateServer, 0)
XD_OK(XD_CloseConnection, 0)
XD_OK(XD_FlushSendBuffer, 1)
XD_OK(XD_InFlushSendBuffer, 0)
XD_FAIL(XD_InitializeModem, 1)
XD_FAIL(XD_InitializeSerial, 1)
XD_FAIL(XD_InitializeSocketsIPXSPX, 6)
XD_FAIL(XD_InitializeSocketsTCP, 6)
XD_OK(XD_LobbySendMessage, 1)
XD_FAIL(XD_OpenConnection, 2)
XD_OK(XD_ResetLibrary, 0)
XD_FAIL(XD_SendBroadcastData, 3)
XD_FAIL(XD_SendSecureData, 4)
XD_OK(XD_ServerCloseConnection, 1)
XD_OK(XD_SetBroadcastReceive, 1)
XD_OK(XD_SetNewClientConnection, 1)
XD_OK(XD_SetOnClientConnectionToServer, 1)
XD_OK(XD_SetOnConnectionLost, 1)
XD_OK(XD_SetOversizedMessageCB, 2)
XD_OK(XD_SetSecureReceive, 1)
XD_OK(XD_ShutdownModem, 0)
XD_OK(XD_ShutdownSockets, 0)
XD_OK(XD_ShutdownTEN, 0)
XD_OK(XD_StopConnections, 0)

char *XD_GetCurrentProtoAddr(int a, int b) { static char none[1]; (void)a; (void)b; return none; }

int XD_GetXDaemonVersion(int *major, int *minor, int *patch)
{
    API_TRACE();
    *major = 3;
    *minor = 5;
    *patch = 0;
    return 0;
}

int XD_LaunchedByLobby(int a, int b) { (void)a; (void)b; return -3; }
