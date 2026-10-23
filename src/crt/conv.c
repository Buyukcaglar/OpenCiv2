/*
 * 64-bit integer <-> string conversions from the MSVC 4.2 C runtime.
 */
#include "game.h"

#define g_mb_cur_max    (*(int *)((u8 *)&g.d_0063a29c))
#define g_pctype        (*(ushort * *)((u8 *)&g.d_0063a090))

static int crt_isctype(int c, int mask)
{
    if (g_mb_cur_max > 1)
        return __isctype(c, mask);
    return g_pctype[c] & mask;
}

/* 0x005f3260: _atoi64(s) */
longlong __cdecl __atoi64(char *s)
{
    int c, sign;
    longlong total;

    while (crt_isctype(*(byte *)s, 8))      /* isspace */
        s++;
    c = *(byte *)s++;
    sign = c;
    if (c == '-' || c == '+')
        c = *(byte *)s++;
    total = 0;
    while (crt_isctype(c, 4)) {             /* isdigit */
        total = 10 * total + (c - '0');
        c = *(byte *)s++;
    }
    if (sign == '-')
        return -total;
    return total;
}

/* 0x00600c30: x64toa(lo, hi, buf, radix, is_neg) -- static helper of
 * _i64toa/_ui64toa; digits above 9 are lower case. */
void __stdcall x64toa(int param_1, int param_2, char *param_3, i32 param_4, int param_5)
{
    ulonglong val = (ulonglong)(uint)param_2 << 32 | (uint)param_1;
    uint radix = (uint)param_4;
    char *p = param_3;
    char *firstdig;
    char tmp;
    uint digit;

    if (param_5 != 0)
        *p++ = '-';
    firstdig = p;
    do {
        digit = (uint)(val % radix);
        val /= radix;
        if (digit > 9)
            *p++ = (char)(digit + 'a' - 10);
        else
            *p++ = (char)(digit + '0');
    } while (val > 0);
    *p-- = 0;
    do {
        tmp = *p;
        *p = *firstdig;
        *firstdig = tmp;
        --p;
        ++firstdig;
    } while (firstdig < p);
}
