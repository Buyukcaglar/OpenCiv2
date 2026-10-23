/*
 * C++ array construction/destruction helpers from the MSVC runtime
 * ("eh vector constructor/destructor iterator").  The originals wrap the
 * loop in __try/__finally to unwind a partially built array if a
 * constructor throws; the game never throws, so the finally block (which
 * only acts when the loop did not complete) is omitted.
 */
#include "game.h"

typedef void (__thiscall *xstructor)(void *);

/* 0x005f2620: construct `count` objects of `size` bytes at `array`. */
void __stdcall crt_vector_ctor_iterator(void *array, uint size, int count, code *ctor, code *dtor)
{
    char *p = (char *)array;
    int i;
    (void)dtor;
    for (i = 0; i < count; i++) {
        ((xstructor)ctor)(p);
        p += (uint)size;
    }
}

/* 0x005f2490: destroy `count` objects of `size` bytes at `array`, last first. */
void __stdcall crt_vector_dtor_iterator(void *array, uint size, int count, code *dtor)
{
    char *p = (char *)array + (uint)size * count;
    while (--count >= 0) {
        p -= (uint)size;
        ((xstructor)dtor)(p);
    }
}
