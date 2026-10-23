/*
 * Hand-written assembly routines of the MSVC 4.2 C runtime: memcpy and
 * memmove (both overlap-safe), __chkstk and __ftol.
 */
#include "game.h"

/* Overlap-safe copy shared by memcpy and memmove: forward unless the
 * destination starts inside the source, in which case it copies backwards
 * (the original clears the direction flag again before returning). */
static void *crt_move(void *dst, const void *src, uint n)
{
    void *d = dst;
    const void *s = src;
    uint words;

    if ((uint)dst <= (uint)src || (uint)dst >= (uint)src + n) {
        words = n >> 2;
        __asm__ volatile("rep movsl" : "+D"(d), "+S"(s), "+c"(words) : : "memory");
        n &= 3;
        __asm__ volatile("rep movsb" : "+D"(d), "+S"(s), "+c"(n) : : "memory");
    } else {
        d = (byte *)dst + n - 1;
        s = (const byte *)src + n - 1;
        __asm__ volatile("std\n\trep movsb\n\tcld" : "+D"(d), "+S"(s), "+c"(n) : : "memory");
    }
    return dst;
}

/* 0x005f2110: memcpy(dst, src, n) -> dst */
i32 * __cdecl FUN_005f2110(void *dst, const void *src, uint n)
{
    return (i32 *)crt_move(dst, src, n);
}

/* 0x005f6500: memmove(dst, src, n) -> dst */
i32 * __cdecl FUN_005f6500(void *dst, const void *src, uint n)
{
    return (i32 *)crt_move(dst, src, n);
}

/* 0x005f35f0: __chkstk.  Allocates EAX bytes of stack below the caller's
 * return address, touching every page on the way down, and returns with ESP
 * lowered (ECX preserved). */
__attribute__((naked)) void __cdecl FUN_005f35f0(void)
{
    __asm__ volatile(
        "pushl %ecx\n\t"
        "cmpl $0x1000, %eax\n\t"
        "leal 8(%esp), %ecx\n\t"
        "jb 2f\n"
        "1:\n\t"
        "subl $0x1000, %ecx\n\t"
        "subl $0x1000, %eax\n\t"
        "testl %eax, (%ecx)\n\t"
        "cmpl $0x1000, %eax\n\t"
        "jae 1b\n"
        "2:\n\t"
        "subl %eax, %ecx\n\t"
        "movl %esp, %eax\n\t"
        "testl %eax, (%ecx)\n\t"
        "movl %ecx, %esp\n\t"
        "movl (%eax), %ecx\n\t"
        "movl 4(%eax), %eax\n\t"
        "pushl %eax\n\t"
        "ret");
}

/* 0x005f6c60: __ftol.  Converts ST0 (popped) to a 64-bit integer in EDX:EAX,
 * truncating toward zero regardless of the current rounding mode. */
__attribute__((naked)) i32 __cdecl __ftol(void)
{
    __asm__ volatile(
        "pushl %ebp\n\t"
        "movl %esp, %ebp\n\t"
        "addl $-12, %esp\n\t"
        "wait\n\t"
        "fnstcw -2(%ebp)\n\t"
        "wait\n\t"
        "movw -2(%ebp), %ax\n\t"
        "orb $0x0c, %ah\n\t"
        "movw %ax, -4(%ebp)\n\t"
        "fldcw -4(%ebp)\n\t"
        "fistpll -12(%ebp)\n\t"
        "fldcw -2(%ebp)\n\t"
        "movl -12(%ebp), %eax\n\t"
        "movl -8(%ebp), %edx\n\t"
        "leave\n\t"
        "ret");
}
