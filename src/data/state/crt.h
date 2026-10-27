/* The MSVC runtime's data (src/native/crt.cpp and the runtime's texts).
 * Declarations only, in the original's address order; the definitions are in
 * src/data/gamedata.cpp (see src/data/gamedata.h). */
#ifndef CIV2_STATE_CRT_H
#define CIV2_STATE_CRT_H

extern u32 rand_seed;
extern u8 rand_seed_rest[12];
extern u8 crt_block_list[3720];

#endif
