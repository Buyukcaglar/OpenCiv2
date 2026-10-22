/*
 * Functions the generator flagged as taking a register argument (in_EAX,
 * in_AL, in_ECX).  For most of them the "argument" is only a decompiler
 * artifact:
 *
 *   in_EAX  - the function returns a byte (or nothing) and the upper bits of
 *             EAX on some path are whatever the caller left there.  The
 *             naked stub hands the incoming EAX to the body so the returned
 *             EAX is bit-for-bit the original.
 *   in_AL   - an asm loop keeps the current audio sample in AL and may store
 *             it before loading the first one; the stub passes AL through.
 *   in_ECX  - the CRT strrchr (0x005f3c10) is typed __thiscall by Ghidra;
 *             it is really a plain __cdecl function and ECX is unused.
 */
#include "game.h"

/* CRT strrchr: __cdecl, caller cleans (protos.h wrongly says __thiscall). */
#ifdef CIV2_NATIVE
#define crt_strrchr _strrchr
#else
#define crt_strrchr ((char *(__cdecl *)(const char *, int))0x005f3c10)
#endif

#define g_city_improvements(city) (&(*(byte *)((u8 *)&cities + 52)))[(city) * 0x58]
#define g_ddraw (*(int * *)((u8 *)&g.d_006394c0))       /* IDirectDraw * */

typedef int (__stdcall *com_fn1)(int *);
typedef int (__stdcall *com_fn2)(int *, int);
#define COM_METHOD(obj, type, off) (*(type *)(*(obj) + (off)))

/* ------------------------------------------------------------------------ */

/* 0x0043d289: set (on != 0) or clear improvement bit `impr` (1..34) of a
 * city.  Really void; EAX ends up as city*11 or, if impr is out of range,
 * whatever the caller had in it. */
int __cdecl regargs_0043d289(int eax_in, int city, int impr, int on)
{
    int index, mask;

    if (impr <= 0 || impr >= 0x23)
        return eax_in;
    thunk_bit_index_split(impr, &index, &mask);
    if (on != 0)
        (&g_city_improvements(city))[index] |= (byte)mask;
    else
        (&g_city_improvements(city))[index] &= (byte)~mask;
    return city * 0xb;
}

#if defined(__i386__) && !defined(CIV2_NATIVE)
__attribute__((naked)) int __cdecl city_set_improvement(int city, int impr, int on)
{
    __asm__ volatile(
        "pushl 12(%esp)\n\t"
        "pushl 12(%esp)\n\t"
        "pushl 12(%esp)\n\t"
        "pushl %eax\n\t"
        "call _regargs_0043d289\n\t"
        "addl $16, %esp\n\t"
        "ret");
}
#else
int __cdecl city_set_improvement(int city, int impr, int on)
{
    /* Native builds: the register input only ever mattered as leftover state. */
    return (int)regargs_0043d289(0, city, impr, on);
}
#endif

/* ------------------------------------------------------------------------ */

/* 0x005ea578: surface->GetFlipStatus(DDGFS_CANFLIP) == DD_OK (result in AL). */
uint __cdecl regargs_005ea578(uint eax_in, int *surface)
{
    uint hr;

    if (surface == NULL)
        return eax_in & 0xffffff00;
    hr = COM_METHOD(surface, com_fn2, 0x48)(surface, 1);
    if (hr == 0)
        return 1;
    return hr & 0xffffff00;
}

#if defined(__i386__) && !defined(CIV2_NATIVE)
__attribute__((naked)) uint __cdecl FUN_005ea578(int *surface)
{
    __asm__ volatile(
        "pushl 4(%esp)\n\t"
        "pushl %eax\n\t"
        "call _regargs_005ea578\n\t"
        "addl $8, %esp\n\t"
        "ret");
}
#else
uint __cdecl FUN_005ea578(int *surface)
{
    /* Native builds: the register input only ever mattered as leftover state. */
    return (uint)regargs_005ea578(0, surface);
}
#endif

/* 0x005ea677: IDirectDraw::GetVerticalBlankStatus; AL = in vertical blank
 * (0 on failure or without DirectDraw). */
uint __cdecl regargs_005ea677(uint eax_in)
{
    uint hr;
    int in_vblank;

    if (g_ddraw == NULL)
        return eax_in & 0xffffff00;
    hr = COM_METHOD(g_ddraw, com_fn2, 0x44)(g_ddraw, (iptr)&in_vblank);
    if (hr != 0)
        return hr & 0xffffff00;
    return (byte)in_vblank;
}

#if defined(__i386__) && !defined(CIV2_NATIVE)
__attribute__((naked)) uint __cdecl FUN_005ea677(void)
{
    __asm__ volatile(
        "pushl %eax\n\t"
        "call _regargs_005ea677\n\t"
        "addl $4, %esp\n\t"
        "ret");
}
#else
uint __cdecl FUN_005ea677(void)
{
    /* Native builds: the register input only ever mattered as leftover state. */
    return (uint)regargs_005ea677(0);
}
#endif

/* 0x005ef58e: IDirectDraw::RestoreDisplayMode; AL = succeeded. */
uint __cdecl regargs_005ef58e(uint eax_in)
{
    uint hr;

    if (g_ddraw == NULL)
        return eax_in & 0xffffff00;
    hr = COM_METHOD(g_ddraw, com_fn1, 0x4c)(g_ddraw);
    if (hr != 0)
        return hr & 0xffffff00;
    return 1;
}

#if defined(__i386__) && !defined(CIV2_NATIVE)
__attribute__((naked)) uint __cdecl FUN_005ef58e(void)
{
    __asm__ volatile(
        "pushl %eax\n\t"
        "call _regargs_005ef58e\n\t"
        "addl $4, %esp\n\t"
        "ret");
}
#else
uint __cdecl FUN_005ef58e(void)
{
    /* Native builds: the register input only ever mattered as leftover state. */
    return (uint)regargs_005ef58e(0);
}
#endif

/* ------------------------------------------------------------------------ */

/*
 * Sample-rate conversion of 8-bit unsigned audio into signed samples.  Each
 * of `count` steps (count 0 means 2^32) reads `src_step` source bytes and
 * emits `dst_step` output bytes, interleaved one read / one write at a time;
 * each output is the most recently read sample (initially AL).  Returns the
 * number of source bytes consumed.
 */

/* 0x005edc6c: store the samples. */
int __cdecl regargs_005edc6c(uint al_in, byte *dst, byte *src, uint count,
                             uint src_step, uint dst_step)
{
    uint n = (ushort)count;
    int nread = 0;
    byte sample = (byte)al_in;
    byte reads, writes;

    do {
        reads = (byte)src_step;
        writes = (byte)dst_step;
        for (;;) {
            if (reads != 0) {
                sample = *src++ ^ 0x80;
                nread++;
                reads--;
            } else if (writes == 0) {
                break;
            }
            if (writes != 0) {
                *dst++ = sample;
                writes--;
            }
        }
    } while (--n != 0);
    return nread;
}

#if defined(__i386__) && !defined(CIV2_NATIVE)
__attribute__((naked)) short __cdecl snd_resample_8bit(byte *dst, byte *src, uint count,
                                                  undefined4 src_step, undefined4 dst_step)
{
    __asm__ volatile(
        "pushl 20(%esp)\n\t"
        "pushl 20(%esp)\n\t"
        "pushl 20(%esp)\n\t"
        "pushl 20(%esp)\n\t"
        "pushl 20(%esp)\n\t"
        "movzbl %al, %eax\n\t"
        "pushl %eax\n\t"
        "call _regargs_005edc6c\n\t"
        "addl $24, %esp\n\t"
        "ret");
}
#else
short __cdecl snd_resample_8bit(byte *dst, byte *src, uint count,
                                                  undefined4 src_step, undefined4 dst_step)
{
    /* Native builds: the register input only ever mattered as leftover state. */
    return (short)regargs_005edc6c(0, dst, src, count, src_step, dst_step);
}
#endif

/* 0x005edcac: mix the samples into dst with signed saturation. */
int __cdecl regargs_005edcac(uint al_in, signed char *dst, byte *src, uint count,
                             uint src_step, uint dst_step)
{
    uint n = (ushort)count;
    int nread = 0;
    signed char sample = (signed char)al_in;
    byte reads, writes;
    int sum;

    do {
        reads = (byte)src_step;
        writes = (byte)dst_step;
        for (;;) {
            if (reads != 0) {
                sample = (signed char)(*src++ ^ 0x80);
                reads--;
                nread++;
            } else if (writes == 0) {
                break;
            }
            if (writes != 0) {
                sum = *dst + sample;
                if (sum > 0x7f)
                    sum = 0x7f;
                else if (sum < -0x80)
                    sum = -0x80;
                *dst++ = (signed char)sum;
                writes--;
            }
        }
    } while (--n != 0);
    return nread;
}

#if defined(__i386__) && !defined(CIV2_NATIVE)
__attribute__((naked)) short __cdecl snd_mix_8bit_resample(char *dst, byte *src, uint count,
                                                  undefined4 src_step, undefined4 dst_step)
{
    __asm__ volatile(
        "pushl 20(%esp)\n\t"
        "pushl 20(%esp)\n\t"
        "pushl 20(%esp)\n\t"
        "pushl 20(%esp)\n\t"
        "pushl 20(%esp)\n\t"
        "movzbl %al, %eax\n\t"
        "pushl %eax\n\t"
        "call _regargs_005edcac\n\t"
        "addl $24, %esp\n\t"
        "ret");
}
#else
short __cdecl snd_mix_8bit_resample(char *dst, byte *src, uint count,
                                                  undefined4 src_step, undefined4 dst_step)
{
    /* Native builds: the register input only ever mattered as leftover state. */
    return (short)regargs_005edcac(0, dst, src, count, src_step, dst_step);
}
#endif

/* ------------------------------------------------------------------------ */

/* 0x00472950: append "." + ext if the file name has no extension, then
 * uppercase it. */
void __cdecl path_default_extension(char *name, char *ext)
{
    if (crt_strrchr(name, '.') == NULL) {
        FUN_005f22e0(name, &DAT_0062b970);
        FUN_005f22e0(name, ext);
    }
    __strupr(name);
}

/* 0x004729ab: dst = src with its extension replaced by ext, uppercased. */
void __cdecl path_set_extension(char *dst, char *src, char *ext)
{
    char *dot;

    if (src != dst)
        FUN_005f22d0(dst, src);
    dot = crt_strrchr(dst, '.');
    if (dot != NULL)
        *dot = '\0';
    FUN_005f22e0(dst, &DAT_0062b974);
    FUN_005f22e0(dst, ext);
    __strupr(dst);
}

/* 0x0056b810: cut the string at its last newline; returns where (or NULL). */
char * __cdecl str_strip_newline(char *s)
{
    char *nl;

    nl = crt_strrchr(s, '\n');
    if (nl != NULL)
        *nl = '\0';
    return nl;
}
