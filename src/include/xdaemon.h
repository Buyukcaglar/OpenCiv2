/*
 * XDaemon.dll: MicroProse's networking library, which the game uses for
 * network play (civ2.exe imports it).  Plain C names here.
 */
#ifndef CIV2_XDAEMON_H
#define CIV2_XDAEMON_H

typedef struct LobbyLaunchInfo LobbyLaunchInfo;

/* The callbacks, as the library's exports declare them (their C++-mangled
   names; all __cdecl).  src/platform/xdaemon.c implements the library
   (docs/xdaemon-protocol.md). */
typedef void (*XD_BroadcastReceiveCB)(void *data, unsigned short len, long header);
typedef void (*XD_SecureReceiveCB)(unsigned short src, void *data, unsigned long len, short flags);
typedef void (*XD_NewClientCB)(unsigned short connected_count, unsigned short new_id);
typedef void (*XD_ConnectedCB)(short my_id);              /* -1: the connection failed */
typedef void (*XD_ConnectionLostCB)(unsigned short id);
typedef void (*XD_OversizedMessageCB)(unsigned long size);

#ifdef __cplusplus
extern "C" {
#endif
int XD_ActivateServer(void);
int XD_CloseConnection(void);
int XD_FlushSendBuffer(unsigned long timeout_ms);
int XD_InFlushSendBuffer(void);
int XD_InitializeModem(int is_server);
int XD_InitializeSerial(int is_server);
int XD_InitializeSocketsIPXSPX(int version, int port, int port2, int is_server, unsigned max_players,
                               XD_BroadcastReceiveCB callback);
int XD_InitializeSocketsTCP(int version, int port, int port2, int is_server, unsigned max_players,
                            XD_BroadcastReceiveCB callback);
int XD_LobbySendMessage(int message);
int XD_OpenConnection(void *address, unsigned long timeout_ms);
int XD_ResetLibrary(void);
int XD_SendBroadcastData(void *msg, unsigned long size, long header);
int XD_SendSecureData(unsigned short to, void *msg, unsigned long size, short flags);
int XD_ServerCloseConnection(unsigned short conn_id);
int XD_SetBroadcastReceive(XD_BroadcastReceiveCB callback);
int XD_SetNewClientConnection(XD_NewClientCB callback);
int XD_SetOnClientConnectionToServer(XD_ConnectedCB callback);
int XD_SetOnConnectionLost(XD_ConnectionLostCB callback);
int XD_SetOversizedMessageCB(unsigned long limit, XD_OversizedMessageCB callback);
int XD_SetSecureReceive(XD_SecureReceiveCB callback);
int XD_ShutdownModem(void);
int XD_ShutdownSockets(void);
int XD_ShutdownTEN(void);
int XD_StopConnections(void);
char *XD_GetCurrentProtoAddr(unsigned adapter, int protocol);
int XD_GetXDaemonVersion(int *major, int *minor, int *patch);
int XD_LaunchedByLobby(void *hwnd, LobbyLaunchInfo *info);
#ifdef __cplusplus
}
#endif

#endif
