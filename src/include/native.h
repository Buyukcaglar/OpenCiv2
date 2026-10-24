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
/* The platform layer is C, the game C++: what one calls in the other has C
   linkage (EXTERN_C on the game's side; the platform headers say extern "C"). */
#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C extern
#endif
/* i8 is plain char (civ2types.h): the game's byte arithmetic needs it signed */
#ifdef __cplusplus
static_assert((char)-1 < 0, "char must be signed (e.g. -fsigned-char)");
#else
_Static_assert((char)-1 < 0, "char must be signed (e.g. -fsigned-char)");
#endif
#endif
