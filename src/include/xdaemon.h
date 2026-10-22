/*
 * XDaemon.dll: MicroProse networking library used for multiplayer, called
 * through civ2.exe's import table.  Calls are emitted with plain C names; the
 * build binds each one to a stub that jumps through the import slot.
 */
#ifndef CIV2_XDAEMON_H
#define CIV2_XDAEMON_H

typedef struct LobbyLaunchInfo LobbyLaunchInfo;

#endif
