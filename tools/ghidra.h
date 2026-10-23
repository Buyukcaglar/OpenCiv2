/*
 * Types and helper macros used by machine-translated (Ghidra) source.
 *
 * Code under src/auto/ is the raw tier of the reconstruction: Ghidra's
 * decompiler output made compilable.  These definitions give its builtin
 * pseudo-types and operators C meanings that match the original x86
 * semantics (MSVC 4.2, 32-bit, little endian, signed char).
 */
#ifndef CIV2_GHIDRA_H
#define CIV2_GHIDRA_H

/*
 * Ghidra's undefinedN types carry no signedness.  Its printer treats them as
 * signed (constants compared against them print as -1, not 0xff) and inserts
 * explicit (byte)/(uint) casts where an operation is unsigned, so signed C
 * types reproduce the original semantics.
 */
typedef signed char undefined;
typedef signed char undefined1;
typedef short undefined2;
typedef int undefined3;
typedef int undefined4;
typedef long long undefined5;
typedef long long undefined6;
typedef long long undefined7;
typedef long long undefined8;
typedef long long i64;          /* (here: a native build defines long as int after this header) */
typedef unsigned char byte;
typedef unsigned char uchar;
typedef signed char sbyte;
typedef signed char schar;
typedef unsigned short ushort;
typedef unsigned short word;
typedef unsigned int uint;
typedef unsigned int uint3;
typedef int int3;
typedef unsigned long ulong;
typedef long long longlong;
typedef unsigned long long ulonglong;
typedef unsigned long long qword;
#ifdef CIV2_NATIVE
/* x87 80-bit temporaries: the original ran the FPU at 53-bit precision. */
typedef double float10;
/* Calls through function pointers may return pointers. */
typedef iptr code();
#else
typedef long double float10;
typedef int code();
#endif
typedef unsigned char ghidra_bool;
typedef void *pointer;
typedef void *pointer32;
typedef unsigned int ImageBaseOffset32;
typedef char string;
typedef unsigned short unicode;
typedef unsigned int dword;
#define bool ghidra_bool
#define true 1
#define false 0
#ifndef NULL
#define NULL ((void *)0)
#endif

/* CONCATxy: x-byte high part, y-byte low part. */
#define CONCAT11(h, l) ((ushort)(((uint)(byte)(h) << 8) | (byte)(l)))
#define CONCAT12(h, l) ((uint)(((uint)(byte)(h) << 16) | (ushort)(l)))
#define CONCAT13(h, l) ((uint)(((uint)(byte)(h) << 24) | ((uint)(l) & 0xffffff)))
#define CONCAT14(h, l) ((ulonglong)(((ulonglong)(byte)(h) << 32) | (uint)(l)))
#define CONCAT21(h, l) ((uint)(((uint)(ushort)(h) << 8) | (byte)(l)))
#define CONCAT22(h, l) ((uint)(((uint)(ushort)(h) << 16) | (ushort)(l)))
#define CONCAT24(h, l) ((ulonglong)(((ulonglong)(ushort)(h) << 32) | (uint)(l)))
#define CONCAT31(h, l) ((uint)(((uint)(h) << 8) | (byte)(l)))
#define CONCAT32(h, l) ((ulonglong)(((ulonglong)((uint)(h) & 0xffffff) << 16) | (ushort)(l)))
#define CONCAT44(h, l) ((ulonglong)(((ulonglong)(uint)(h) << 32) | (uint)(l)))
#define CONCAT41(h, l) ((ulonglong)(((ulonglong)(uint)(h) << 8) | (byte)(l)))
#define CONCAT42(h, l) ((ulonglong)(((ulonglong)(uint)(h) << 16) | (ushort)(l)))

/* SUBxy(v, off): y bytes of x-byte value v starting at byte offset off. */
#define SUB21(v, off) ((byte)((ushort)(v) >> ((off) * 8)))
#define SUB41(v, off) ((byte)((uint)(v) >> ((off) * 8)))
#define SUB42(v, off) ((ushort)((uint)(v) >> ((off) * 8)))
#define SUB43(v, off) ((uint)((uint)(v) >> ((off) * 8)) & 0xffffff)
#define SUB81(v, off) ((byte)((ulonglong)(v) >> ((off) * 8)))
#define SUB82(v, off) ((ushort)((ulonglong)(v) >> ((off) * 8)))
#define SUB84(v, off) ((uint)((ulonglong)(v) >> ((off) * 8)))
#define SUB101(v, off) ((byte)(ulonglong)(v))
#define SUB104(v, off) ((uint)(longlong)(v))
#define SUB108(v, off) ((ulonglong)(longlong)(v))

#define ZEXT12(v) ((ushort)(byte)(v))
#define ZEXT14(v) ((uint)(byte)(v))
#define ZEXT18(v) ((ulonglong)(byte)(v))
#define ZEXT24(v) ((uint)(ushort)(v))
#define ZEXT28(v) ((ulonglong)(ushort)(v))
#define ZEXT48(v) ((ulonglong)(uint)(v))
#define ZEXT816(v) ((ulonglong)(v))
#define SEXT12(v) ((short)(sbyte)(v))
#define SEXT14(v) ((int)(sbyte)(v))
#define SEXT18(v) ((longlong)(sbyte)(v))
#define SEXT24(v) ((int)(short)(v))
#define SEXT28(v) ((longlong)(short)(v))
#define SEXT48(v) ((longlong)(int)(v))

#define CARRY1(a, b) ((byte)((byte)(a) + (byte)(b)) < (byte)(a))
#define CARRY2(a, b) ((ushort)((ushort)(a) + (ushort)(b)) < (ushort)(a))
#define CARRY4(a, b) ((uint)((uint)(a) + (uint)(b)) < (uint)(a))
#define SCARRY1(a, b) ((((sbyte)(a) + (sbyte)(b)) > 127) || (((sbyte)(a) + (sbyte)(b)) < -128))
#define SCARRY2(a, b) ((((short)(a) + (short)(b)) > 32767) || (((short)(a) + (short)(b)) < -32768))
#define SCARRY4(a, b) ((((longlong)(int)(a) + (int)(b)) > 0x7fffffffLL) || (((longlong)(int)(a) + (int)(b)) < -0x80000000LL))
#define SBORROW1(a, b) ((((sbyte)(a) - (sbyte)(b)) > 127) || (((sbyte)(a) - (sbyte)(b)) < -128))
#define SBORROW2(a, b) ((((short)(a) - (short)(b)) > 32767) || (((short)(a) - (short)(b)) < -32768))
#define SBORROW4(a, b) ((((longlong)(int)(a) - (int)(b)) > 0x7fffffffLL) || (((longlong)(int)(a) - (int)(b)) < -0x80000000LL))
#define POPCOUNT(v) __builtin_popcount((uint)(v))
#define ABS(v) ((v) < 0 ? -(v) : (v))
#define SQRT(v) __builtin_sqrtl(v)
#define ROUND(v) __builtin_rintl(v)
#define TRUNC(v) ((longlong)(v))
#define FLOAT2FLOAT(v) (v)
#define NAN(v) ((v) != (v))

#define halt_baddata() __builtin_trap()
#define halt_unimplemented() __builtin_trap()
#define software_interrupt(n) __builtin_trap()
/* `int n` as Ghidra prints it: (*(code *)swi(3))() is a debugger break. */
static inline code *swi(int n) { (void)n; __builtin_trap(); return (code *)0; }

/* The MSVC runtime's getc() and feof() macros (they read FILE internals). */
#ifdef CIV2_NATIVE
#define CRT_GETC(f) getc(f)
#define CRT_FEOF(f) (feof(f) ? 0x10 : 0)
#else
#define CRT_GETC(f) (--(f)->_cnt >= 0 ? 0xff & *(f)->_ptr++ : __filbuf(f))
#define CRT_FEOF(f) ((f)->_flag & 0x10)
#endif

/* Emulated stack frames (see emulate_frame in tools/gen_c.py) keep each
 * local at its original offset.  Native builds double the offsets: every
 * original 4-byte slot gets 8 bytes, room for anything that grows with
 * pointer size. */
#if defined(__LP64__) || defined(_WIN64)
#define FRAME_OFF(n) ((n) * 2)
#else
#define FRAME_OFF(n) (n)
#endif

/* An address of the original image written as a number (data, or a function
 * passed as a callback): the number itself in the 32-bit build, where the
 * data is at its original address; the symbol in native builds. */
#ifdef CIV2_NATIVE
#define ADDR(orig, native) ((iptr)(native))
#else
#define ADDR(orig, native) (orig)
#endif

/* A global by its original address (hand-written code): an offset into the
 * game data struct `g`, whose 32-bit layout is the original one. */
#define GLOBAL(type, addr) (*(type *)((unsigned char *)&g + ((addr) - 0x0061c000)))

#endif
