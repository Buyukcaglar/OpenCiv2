/*
 * The portable build's runtime (src/host/port_main.c, wasi.c): the game's
 * wasm32 module, translated to C by wasm2c (civ2_wasm.h), and access to its
 * memory.  Module addresses are 32-bit offsets into that memory.
 */
#ifndef CIV2_PORT_H
#define CIV2_PORT_H

#include <string.h>
#include "civ2_wasm.h"

struct w2c_host { w2c_civ2 *module; };
struct w2c_wasi__snapshot__preview1 { w2c_civ2 *module; };

extern wasm_rt_memory_t *port_memory;

#define MEM(a) ((void *)(port_memory->data + (u32)(a)))
static inline u32 GET32(u32 a) { u32 v; memcpy(&v, MEM(a), 4); return v; }
static inline void PUT32(u32 a, u32 v) { memcpy(MEM(a), &v, 4); }
static inline void PUT64(u32 a, u64 v) { memcpy(MEM(a), &v, 8); }

void wasi_init(int argc, char **argv);

#endif
