/*
 * XDaemon.dll: MicroProse networking library used for multiplayer, called
 * through civ2.exe's import table.  Calls are emitted with plain C names; the
 * build binds each one to a stub that jumps through the import slot.
 */
#ifndef CIV2_XDAEMON_H
#define CIV2_XDAEMON_H

typedef struct LobbyLaunchInfo LobbyLaunchInfo;

/* The calls the game makes (src/platform/misc.c: the library as it behaves
   with no network game set up). */
typedef void (*XD_BroadcastReceiveCB)(int *msg, unsigned short size);
typedef void (*XD_SecureReceiveCB)(unsigned int conn_id, int *msg, unsigned int size);
typedef void (*XD_NewClientCB)(int client_info, unsigned int conn_id);
typedef void (*XD_ConnectedCB)(short conn_id);
typedef void (*XD_ConnectionLostCB)(unsigned short player_id);
typedef void (*XD_OversizedMessageCB)(int size);

#ifdef __cplusplus
extern "C" {
#endif
int XD_ActivateServer(void);
int XD_CloseConnection(void);
int XD_FlushSendBuffer(int timeout_ms);
int XD_InFlushSendBuffer(void);
int XD_InitializeModem(int is_server);
int XD_InitializeSerial(int is_server);
int XD_InitializeSocketsIPXSPX(int version, int port, int port2, int is_server, int max_players, void *callback);
int XD_InitializeSocketsTCP(int version, int port, int port2, int is_server, int max_players, void *callback);
int XD_LobbySendMessage(int message);
int XD_OpenConnection(const char *address, int timeout_ms);
int XD_ResetLibrary(void);
int XD_SendBroadcastData(void *msg, unsigned long size, int flags);
int XD_SendSecureData(unsigned short player, void *msg, unsigned long size, int flags);
int XD_ServerCloseConnection(unsigned short conn_id);
int XD_SetBroadcastReceive(XD_BroadcastReceiveCB callback);
int XD_SetNewClientConnection(XD_NewClientCB callback);
int XD_SetOnClientConnectionToServer(XD_ConnectedCB callback);
int XD_SetOnConnectionLost(XD_ConnectionLostCB callback);
int XD_SetOversizedMessageCB(int max_size, XD_OversizedMessageCB callback);
int XD_SetSecureReceive(XD_SecureReceiveCB callback);
int XD_ShutdownModem(void);
int XD_ShutdownSockets(void);
int XD_ShutdownTEN(void);
int XD_StopConnections(void);
char *XD_GetCurrentProtoAddr(int adapter, int protocol);
int XD_GetXDaemonVersion(int *major, int *minor, int *patch);
int XD_LaunchedByLobby(void *hwnd, LobbyLaunchInfo *info);
#ifdef __cplusplus
}
#endif

#endif
