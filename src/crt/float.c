/*
 * Floating-point <-> text conversion of the MSVC 4.2 C runtime:
 *   output: _cfltcvt / _cftoe / _cftof / _cftog (printf %e %f %g),
 *           _fptostr and $I10_OUTPUT (FUN_006051a0, 80-bit -> decimal digits)
 *   input:  __strgtold12, __STRINGTOLD, _atoldbl, _ld12told
 *
 * Reconstructed from the machine code; the 12-byte arithmetic helpers
 * (__multtenpow12, __ld12mul, __shl_12, __add_12, ...) are the original
 * functions, called by name.
 *
 * The game itself formats no floating-point values and never parses any
 * (no %e/%f/%g format strings, no atof/strtod/scanf), so these run only if
 * some other CRT path asks for them.
 */
#include "game.h"

/* STRFLT */
typedef struct {
    int sign;           /* '-' or ' ' */
    int decpt;
    int flag;
    char *mantissa;
} strflt;

/* FOS ($I10_OUTPUT result) */
typedef struct {
    short exp;
    char sign;
    char manlen;
    char man[24];
} fos_t;

#define g_fmt               (*(char *)((u8 *)&g.d_0063aef8))   /* called from _cftog */
#define g_magnitude         (*(int *)((u8 *)&g.d_0063aefc))
#define g_round_expansion   (*(char *)((u8 *)&g.d_0063af00))
#define g_pflt              (*(strflt * *)((u8 *)&g.d_006e54a4))
#define g_decimal_point     (*(char *)((u8 *)&g.d_0063a2a0))   /* __decimal_point[0] */
#define g_mb_cur_max        (*(int *)((u8 *)&g.d_0063a29c))
#define g_pctype            (*(ushort * *)((u8 *)&g.d_0063a090))

#define STR_e000    ((char *)0x0061e850)    /* "e+000" */

/* protos.h declares _cftog void; it returns buf like its siblings. */
char * __cdecl cftog_impl(double *pvalue, char *buf, int ndec, int caps) __asm__("___cftog");

static strflt *fltout(double *pvalue)
{
    return (strflt *)__fltout(*pvalue);
}

/* 0x00603300: _fptostr(buf, digits, pflt): copy `digits` mantissa digits
 * after a leading '0', round, and drop the '0' unless rounding carried. */
int __cdecl __fptostr(char *buf, int digits, strflt *pflt)
{
    char *p = buf;
    char *mantissa = pflt->mantissa;

    *p++ = '0';
    while (digits > 0) {
        if (*mantissa != 0)
            *p = *mantissa++;
        else
            *p = '0';
        p++;
        digits--;
    }
    *p = 0;
    if (digits >= 0 && *mantissa >= '5') {
        p--;
        while (*p == '9')
            *p-- = '0';
        *p = *p + 1;
    }
    if (*buf == '1') {
        pflt->decpt++;
        return (int)pflt;
    }
    return (int)FUN_005f22d0(buf, buf + 1);
}

/* 0x005fe560: _cftoe(pvalue, buf, ndec, caps) */
int __cdecl __cftoe(double *pvalue, char *buf, int ndec, int caps)
{
    strflt *pflt;
    char *p;
    int exp;

    if (g_fmt != 0) {
        pflt = g_pflt;
        __shift(buf + (pflt->sign == '-'), ndec > 0);
    } else {
        pflt = fltout(pvalue);
        __fptostr(buf + (pflt->sign == '-') + (ndec > 0), ndec + 1, pflt);
    }
    p = buf;
    if (pflt->sign == '-')
        *p++ = '-';
    if (ndec > 0) {
        *p = p[1];
        *++p = g_decimal_point;
    }
    p = (char *)FUN_005f22d0(p + ndec + (g_fmt == 0), STR_e000);
    if (caps != 0)
        *p = 'E';
    p++;
    if (*pflt->mantissa != '0') {
        exp = pflt->decpt - 1;
        if (exp < 0) {
            exp = -exp;
            *p = '-';
        }
        p++;
        if (exp >= 100) {
            *p += (char)(exp / 100);
            exp %= 100;
        }
        p++;
        if (exp >= 10) {
            *p += (char)(exp / 10);
            exp %= 10;
        }
        p++;
        *p += (char)exp;
    }
    return (int)buf;
}

/* 0x005fe730: _cftof(pvalue, buf, ndec) */
int __cdecl __cftof(double *pvalue, char *buf, int ndec)
{
    strflt *pflt;
    char *p;

    if (g_fmt != 0) {
        pflt = g_pflt;
        p = buf + (pflt->sign == '-');
        if (ndec == g_magnitude) {
            p += g_magnitude;
            *p++ = '0';
            *p = 0;
        }
    } else {
        pflt = fltout(pvalue);
        __fptostr(buf + (pflt->sign == '-'), pflt->decpt + ndec, pflt);
    }
    p = buf;
    if (pflt->sign == '-')
        *p++ = '-';
    if (pflt->decpt <= 0) {
        __shift(p, 1);
        *p++ = '0';
    } else {
        p += pflt->decpt;
    }
    if (ndec > 0) {
        __shift(p, 1);
        *p++ = g_decimal_point;
        if (pflt->decpt < 0) {
            if (g_fmt != 0)
                ndec = -pflt->decpt;
            else
                ndec = -pflt->decpt < ndec ? -pflt->decpt : ndec;
            __shift(p, ndec);
            _memset(p, '0', ndec);
        }
    }
    return (int)buf;
}

/* 0x005fe9e0: _cftoe_g -- _cftoe on the digits _cftog already produced */
int __cdecl __cftoe_g(double *pvalue, char *buf, int ndec, int caps)
{
    int ret;

    g_fmt = 1;
    ret = __cftoe(pvalue, buf, ndec, caps);
    g_fmt = 0;
    return ret;
}

/* 0x005fea20: _cftof_g */
int __cdecl __cftof_g(double *pvalue, char *buf, int ndec)
{
    int ret;

    g_fmt = 1;
    ret = __cftof(pvalue, buf, ndec);
    g_fmt = 0;
    return ret;
}

/* 0x005fe8c0: _cftog(pvalue, buf, ndec, caps) */
char * __cdecl cftog_impl(double *pvalue, char *buf, int ndec, int caps)
{
    char *p;
    char *q;

    g_pflt = fltout(pvalue);
    g_magnitude = g_pflt->decpt - 1;
    p = buf + (g_pflt->sign == '-');
    __fptostr(p, ndec, g_pflt);
    g_round_expansion = g_magnitude < g_pflt->decpt - 1 ? 1 : 0;
    g_magnitude = g_pflt->decpt - 1;
    if (g_magnitude < -4 || g_magnitude >= ndec)
        return (char *)__cftoe_g(pvalue, buf, ndec, caps);
    if (g_round_expansion != 0) {
        /* rounding added a digit: drop the last one */
        do
            q = p++;
        while (*q != 0);
        p[-2] = 0;
    }
    return (char *)__cftof_g(pvalue, buf, ndec);
}

/* 0x005fea60: _cfltcvt(pvalue, buf, format, precision, caps) */
int __cdecl __cfltcvt(double *pvalue, char *buf, int format, int precision, int caps)
{
    if (format == 'e' || format == 'E')
        return __cftoe(pvalue, buf, precision, caps);
    if (format == 'f')
        return __cftof(pvalue, buf, precision);
    return (int)cftog_impl(pvalue, buf, precision, caps);
}

/* ------------------------------------------------------------------------ */

static void fos_zero(fos_t *fos)
{
    fos->exp = 0;
    fos->sign = ' ';
    fos->manlen = 1;
    fos->man[0] = '0';
    fos->man[1] = 0;
}

/* 0x006051a0: $I10_OUTPUT(ld (3 dwords), ndigits, output_flags, fos):
 * decimal digits of an 80-bit long double, rounded to ndigits (or, with
 * flag 1, to ndigits places after the decimal point). */
undefined4 __cdecl FUN_006051a0(uint manlo, uint manhi, uint expword, int ndigits,
                                uint flags, fos_t *fos)
{
    static const byte one_tenth_init[12] = {
        0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xfb, 0x3f
    };
    byte one_tenth[12];
    byte ld12[12];
    byte tmp12[12];
    ushort expn, sign;
    int r;
    short ir;
    int shift, i, n;
    char *p;
    char c;
    int retval = 1;

    for (i = 0; i < 12; i++)
        one_tenth[i] = one_tenth_init[i];
    expn = (ushort)expword;
    sign = expn & 0x8000;
    expn &= 0x7fff;
    fos->sign = sign ? '-' : ' ';

    if (expn == 0 && manhi == 0 && manlo == 0) {
        fos_zero(fos);
        return 1;
    }
    if (expn == 0x7fff) {
        fos->exp = 1;
        if (!(manhi == 0x80000000 && manlo == 0) && !(manhi & 0x40000000)) {
            FUN_005f22d0(fos->man, (char *)0x0061ec0c);     /* "1#SNAN" */
            fos->manlen = 6;
        } else if (sign && manhi == 0xc0000000 && manlo == 0) {
            FUN_005f22d0(fos->man, (char *)0x0061ec04);     /* "1#IND" */
            fos->manlen = 5;
        } else if (manhi == 0x80000000 && manlo == 0) {
            FUN_005f22d0(fos->man, (char *)0x0061ebfc);     /* "1#INF" */
            fos->manlen = 5;
        } else {
            FUN_005f22d0(fos->man, (char *)0x0061ebf4);     /* "1#QNAN" */
            fos->manlen = 6;
        }
        return 0;
    }

    /* estimate the decimal exponent: r = log10(x) * 2^16 */
    r = (int)expn * 0x4d10 + (int)(manhi >> 24) * 0x9a + (int)(expn >> 8) * 0x4d - 0x134312f4;
    ir = (short)(r >> 16);

    *(ushort *)(ld12 + 0) = 0;
    *(uint *)(ld12 + 2) = manlo;
    *(uint *)(ld12 + 6) = manhi;
    *(ushort *)(ld12 + 10) = expn;
    ___multtenpow12(ld12, -(int)ir, 1);
    if (*(ushort *)(ld12 + 10) >= 0x3fff) {
        ir++;
        ___ld12mul(ld12, one_tenth);
    }
    fos->exp = ir;

    if ((flags & 1) && (ndigits += ir) <= 0) {
        fos_zero(fos);
        return 1;
    }
    if (ndigits > 0x15)
        ndigits = 0x15;

    shift = *(ushort *)(ld12 + 10) - 0x3ffe;
    *(ushort *)(ld12 + 10) = 0;
    for (i = 0; i < 8; i++)
        ___shl_12(ld12);
    if (shift < 0) {
        for (n = -shift & 0xff; n > 0; n--)
            ___shr_12(ld12);
    }

    p = fos->man;
    for (n = ndigits + 1; n > 0; n--) {
        for (i = 0; i < 12; i++)
            tmp12[i] = ld12[i];
        ___shl_12(ld12);
        ___shl_12(ld12);
        ___add_12(ld12, tmp12);
        ___shl_12(ld12);            /* ld12 *= 10; next digit in byte 11 */
        *p++ = (char)(ld12[11] + '0');
        ld12[11] = 0;
    }

    p--;
    c = *p;
    p--;
    if (c >= '5') {
        while (p >= fos->man && *p == '9')
            *p-- = '0';
        if (p < fos->man) {
            p++;
            fos->exp++;
        }
        (*p)++;
    } else {
        while (p >= fos->man && *p == '0')
            p--;
        if (p < fos->man) {
            fos_zero(fos);
            return 1;
        }
    }
    fos->manlen = (char)(p - fos->man + 1);
    fos->man[(int)fos->manlen] = 0;
    return retval;
}

/* ------------------------------------------------------------------------ */

static int crt_isdigit(byte c)
{
    if (g_mb_cur_max > 1)
        return __isctype(c, 4);
    return g_pctype[c] & 4;
}

/* 0x00604520: __strgtold12(pld12, p_end_ptr, str, mult12, scale, decpt,
 * implicit_E): parse a decimal floating-point number into a 12-byte long
 * double.  Returns SLD_UNDERFLOW (1) / SLD_OVERFLOW (2) / SLD_NODIGITS (4). */
int __cdecl ___strgtold12(byte *pld12, char **p_end_ptr, char *str, int mult12, int scale,
                           int decpt, int implicit_E)
{
    enum { S_INIT, S_EAT0L, S_SIGNM, S_GETL, S_GETR, S_POINT, S_E, S_SIGNE,
           S_EAT0E, S_GETE, S_END, S_E_IMPLICIT };
    char buf[25];
    char *manp = buf;
    ushort man_sign = 0;
    int exp_sign = 1;
    uint manlen = 0;
    int found_digits = 0;
    int found_point = 0;
    int found_exp = 0;
    int overflow = 0;
    int underflow = 0;
    int exp = 0;
    int nzero = 0;
    uint result = 0;
    int state = S_INIT;
    char *p;
    char *savedp;
    byte c;
    int e;
    byte tmp12[12];
    ushort r_exp, r_lo16;
    uint r_man_lo, r_man_hi;

    p = str;
    savedp = p;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;

    while (state != S_END) {
        c = *p++;
        switch (state) {
        case S_INIT:
            if ((char)c >= '1' && (char)c <= '9') {
                state = S_GETL;
                p--;
            } else if (g_decimal_point == (char)c) {
                state = S_POINT;
            } else if (c == '+') {
                state = S_SIGNM;
                man_sign = 0;
            } else if (c == '-') {
                state = S_SIGNM;
                man_sign = 0x8000;
            } else if (c == '0') {
                state = S_EAT0L;
            } else {
                state = S_END;
                p--;
            }
            break;

        case S_EAT0L:
            found_digits = 1;
            if ((char)c >= '1' && (char)c <= '9') {
                state = S_GETL;
                p--;
            } else if (g_decimal_point == (char)c) {
                state = S_GETR;
            } else {
                switch (c) {
                case '0': state = S_EAT0L; break;
                case 'E': case 'e': case 'D': case 'd': state = S_E; break;
                case '+': case '-': p--; state = S_E_IMPLICIT; break;
                default: state = S_END; p--; break;
                }
            }
            break;

        case S_SIGNM:
            if ((char)c >= '1' && (char)c <= '9') {
                state = S_GETL;
                p--;
            } else if (g_decimal_point == (char)c) {
                state = S_POINT;
            } else if (c == '0') {
                state = S_EAT0L;
            } else {
                state = S_END;
                p = savedp;
            }
            break;

        case S_GETL:
            found_digits = 1;
            for (; crt_isdigit(c); c = *p++) {
                if (manlen < 25) {
                    manlen++;
                    *manp++ = (char)(c - '0');
                } else {
                    nzero++;
                }
            }
            if (g_decimal_point == (char)c) {
                state = S_GETR;
            } else {
                switch (c) {
                case 'E': case 'e': case 'D': case 'd': state = S_E; break;
                case '+': case '-': p--; state = S_E_IMPLICIT; break;
                default: state = S_END; p--; break;
                }
            }
            break;

        case S_GETR:
            found_digits = 1;
            found_point = 1;
            if (manlen == 0) {
                for (; c == '0'; c = *p++)
                    nzero--;
            }
            for (; crt_isdigit(c); c = *p++) {
                if (manlen < 25) {
                    manlen++;
                    *manp++ = (char)(c - '0');
                    nzero--;
                }
            }
            switch (c) {
            case 'E': case 'e': case 'D': case 'd': state = S_E; break;
            case '+': case '-': p--; state = S_E_IMPLICIT; break;
            default: state = S_END; p--; break;
            }
            break;

        case S_POINT:
            found_point = 1;
            if (crt_isdigit(c)) {
                state = S_GETR;
                p--;
            } else {
                state = S_END;
                p = savedp;
            }
            break;

        case S_E:
            savedp = p - 2;     /* the 'E' */
            if ((char)c >= '1' && (char)c <= '9') {
                state = S_GETE;
                p--;
            } else if (c == '+') {
                state = S_SIGNE;
            } else if (c == '-') {
                state = S_SIGNE;
                exp_sign = -1;
            } else if (c == '0') {
                state = S_EAT0E;
            } else {
                state = S_END;
                p = savedp;
            }
            break;

        case S_SIGNE:
            if ((char)c >= '1' && (char)c <= '9') {
                state = S_GETE;
                p--;
            } else if (c == '0') {
                state = S_EAT0E;
            } else {
                state = S_END;
                p = savedp;
            }
            break;

        case S_EAT0E:
            found_exp = 1;
            while (c == '0')
                c = *p++;
            if ((char)c >= '1' && (char)c <= '9') {
                state = S_GETE;
                p--;
            } else {
                state = S_END;
                p--;
            }
            break;

        case S_GETE:
            found_exp = 1;
            e = 0;
            for (; crt_isdigit(c); c = *p++) {
                e = e * 10 + ((char)c - '0');
                if (e > 0x1450) {
                    e = 0x1451;
                    break;
                }
            }
            exp = e;
            while (crt_isdigit(c))
                c = *p++;
            state = S_END;
            p--;
            break;

        case S_E_IMPLICIT:
            if (implicit_E != 0) {
                savedp = p - 1;
                if (c == '+') {
                    state = S_SIGNE;
                } else if (c == '-') {
                    state = S_SIGNE;
                    exp_sign = -1;
                } else {
                    state = S_END;
                    p = savedp;
                }
            } else {
                state = S_END;
                p--;
            }
            break;
        }
    }

    *p_end_ptr = p;

    if (found_digits && !overflow && !underflow) {
        if (manlen > 24) {
            if (buf[23] >= 5)
                buf[23]++;
            manlen = 24;
            manp--;
            nzero++;
        }
        if (manlen > 0) {
            manp--;
            while (*manp == 0) {
                manlen--;
                nzero++;
                manp--;
            }
            ___mtold12(buf, manlen, tmp12);
            if (exp_sign < 0)
                exp = -exp;
            exp += nzero;
            if (!found_exp)
                exp += scale;
            if (!found_point)
                exp -= decpt;
            if (exp > 0x1450) {
                overflow = 1;
            } else if (exp < -0x1450) {
                underflow = 1;
            } else {
                ___multtenpow12(tmp12, exp, mult12);
                r_lo16 = *(ushort *)(tmp12 + 0);
                r_man_lo = *(uint *)(tmp12 + 2);
                r_man_hi = *(uint *)(tmp12 + 6);
                r_exp = *(ushort *)(tmp12 + 10);
            }
        } else {
            r_lo16 = 0;
            r_exp = 0;
            r_man_hi = 0;
            r_man_lo = 0;
        }
    }

    if (!found_digits) {
        r_lo16 = 0;
        r_exp = 0;
        r_man_hi = 0;
        r_man_lo = 0;
        result |= 4;
    } else if (overflow) {
        r_exp = 0x7fff;
        r_man_hi = 0x80000000;
        r_man_lo = 0;
        r_lo16 = 0;
        result |= 2;
    } else if (underflow) {
        r_lo16 = 0;
        r_exp = 0;
        r_man_hi = 0;
        r_man_lo = 0;
        result |= 1;
    }

    *(ushort *)(pld12 + 0) = r_lo16;
    *(uint *)(pld12 + 2) = r_man_lo;
    *(uint *)(pld12 + 6) = r_man_hi;
    *(ushort *)(pld12 + 10) = man_sign | r_exp;
    return result;
}

/* 0x00603170: _ld12told(pld12, pld): round a 12-byte long double to the
 * 10-byte format; returns 1 on overflow to infinity. */
int __cdecl __ld12told(byte *pld12, byte *pld)
{
    uint man[3];        /* hi, lo, extra */
    ushort expn, sign;
    int ret = 0;

    expn = *(ushort *)(pld12 + 10) & 0x7fff;
    sign = *(ushort *)(pld12 + 10) & 0x8000;
    man[0] = *(uint *)(pld12 + 6);
    man[1] = *(uint *)(pld12 + 2);
    man[2] = (uint)*(ushort *)(pld12 + 0) << 16;
    if (__RoundMan(man, 0x40) != 0) {
        man[0] = 0x80000000;
        expn++;
    }
    if (expn == 0x7fff)
        ret = 1;
    *(uint *)(pld + 4) = man[0];
    *(uint *)(pld + 0) = man[1];
    *(ushort *)(pld + 8) = sign | expn;
    return ret;
}

/* 0x00603280: _atoldbl(pld, str) */
int __cdecl __atoldbl(byte *pld, char *str)
{
    byte ld12[12];
    char *end;

    ___strgtold12(ld12, &end, str, 1, 0, 0, 0);
    return __ld12told(ld12, pld);
}

/* 0x00605140: __STRINGTOLD(pld, p_end_ptr, str, mult12) */
int __cdecl ___STRINGTOLD(byte *pld, char **p_end_ptr, char *str, int mult12)
{
    byte ld12[12];
    uint ret;

    ret = ___strgtold12(ld12, p_end_ptr, str, mult12, 0, 0, 0);
    if (__ld12told(ld12, pld) == 1)
        ret |= 2;
    return ret;
}
