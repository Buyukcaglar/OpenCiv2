/*
 * SHA-256 (FIPS 180-4), for checking the game's files (setup_files.c).
 */
#ifndef CIV2_SHA256_H
#define CIV2_SHA256_H

#include <stddef.h>
#include <stdint.h>

typedef struct Sha256 {
    uint32_t h[8];
    uint64_t length;            /* bytes so far */
    uint8_t block[64];
    size_t used;                /* bytes in block */
} Sha256;

void sha256_init(Sha256 *s);
void sha256_update(Sha256 *s, const void *data, size_t n);
/* The digest as 64 lowercase hex digits and a NUL. */
void sha256_final_hex(Sha256 *s, char hex[65]);

#endif
