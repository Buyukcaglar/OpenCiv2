/*
 * Configuration for native (non-Windows-32, e.g. 64-bit) builds, force-included
 * before everything else: pointer-holding integers become pointer-sized.
 */
#ifndef CIV2_NATIVE_H
#define CIV2_NATIVE_H
#include <stdint.h>
#define CIV2_PTR_INTS 1
typedef intptr_t iptr;
typedef uintptr_t uptr;
#endif
