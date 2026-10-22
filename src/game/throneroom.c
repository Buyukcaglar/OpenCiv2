/*
 * The throne room.  Both functions keep the throne-room window object
 * (0x1c44 bytes) on the stack, where the decompiler only saw it as an
 * unnamed stack address, so they are written out here.
 */
#include "game.h"

/* The window object, as the original kept it: on the stack. */
typedef union {
    ThroneRoomWindow room;
    u8 raw[0x1c44];
} ThroneRoom;

/* 0x0044cc80: after the civilization earns a throne-room improvement:
 * show the throne room to place it, unless every piece is complete
 * (pieces 0-6 at level 4, and all the bits of piece 8). */
void __cdecl throneroom_show_upgrade(iptr civ)
{
    ThroneRoom t;
    int i, incomplete = 0;
    thunk_throneroom_ctor(&t.room, civ);
    for (i = 0; i < 7; i++)
        if (civs[civ].throne_room[i] < 4)
            incomplete = 1;
    if ((~civs[civ].throne_room[8] & 0x7f) != 0)
        incomplete = 1;
    if (incomplete)
        thunk_throneroom_run_upgrade(&t.room);
    thunk_throneroom_dtor((ThroneRoomDtorView *)&t.room);
}

/* 0x0044cd9b: show the throne room (to look at it). */
void __cdecl throneroom_show(iptr civ)
{
    ThroneRoom t;
    thunk_throneroom_ctor(&t.room, civ);
    thunk_throneroom_run_view(&t.room);
    thunk_throneroom_dtor((ThroneRoomDtorView *)&t.room);
}
