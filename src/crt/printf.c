/*
 * printf family of the MSVC 4.2 debug C runtime: sprintf, _snprintf,
 * printf, fprintf and the formatting engine _output.
 */
#include "game.h"
#include <stdarg.h>

/* MSVC FILE */
typedef struct {
    char *ptr;          /* +0x00 */
    int cnt;            /* +0x04 */
    char *base;         /* +0x08 */
    int flag;           /* +0x0c */
    int file;           /* +0x10 */
    int charbuf;        /* +0x14 */
    int bufsiz;         /* +0x18 */
    char *tmpfname;     /* +0x1c */
} crt_file;

#define crt_stdout ((crt_file *)(0x0063ac58 + 0x20))   /* &_iob[1] */

/* protos.h declares these without parameters; they are variadic. */
int __cdecl sprintf_impl(char *string, char *format, ...) __asm__("__sprintf");
int __cdecl snprintf_impl(char *string, size_t count, char *format, ...) __asm__("___snprintf");
int __cdecl printf_impl(char *format, ...) __asm__("__printf");
int __cdecl fprintf_impl(crt_file *stream, char *format, ...) __asm__("__fprintf");

#define FILE_sprintf    ((char *)0x0061d834)    /* "sprintf.c" */
#define FILE_printf     ((char *)0x0061e2e4)    /* "printf.c" */
#define FILE_fprintf    ((char *)0x0061eb54)    /* "fprintf.c" */
#define FILE_output     ((char *)0x0061e7a4)    /* "output.c" */
#define EXPR_string     ((char *)0x0061d840)    /* "string != NULL" */
#define EXPR_format     ((char *)0x0061d824)    /* "format != NULL" */
#define EXPR_str        ((char *)0x0061d818)    /* "str != NULL" */
#define EXPR_ch         ((char *)0x0061e7b0)    /* "ch != _T('\\0')" */

#define assert_report(file, line, expr) \
    do { if (__CrtDbgReport(2, (file), (line), 0, (expr)) == 1) __asm__ volatile("int3"); } while (0)

/* 0x005f3030: sprintf(string, format, ...) */
int __cdecl sprintf_impl(char *string, char *format, ...)
{
    crt_file str;
    int retval;
    va_list ap;

    if (string == NULL)
        assert_report(FILE_sprintf, 0x5d, EXPR_string);
    if (format == NULL)
        assert_report(FILE_sprintf, 0x5e, EXPR_format);
    str.flag = 0x42;        /* _IOWRT | _IOSTRG */
    str.base = string;
    str.ptr = str.base;
    str.cnt = 0x7fffffff;
    retval = __output(&str, format, (va_start(ap, format), (char *)ap));
    if (--str.cnt >= 0)
        *str.ptr++ = 0;
    else
        __flsbuf(0, &str);
    return retval;
}

/* 0x00601120: _snprintf(string, count, format, ...) */
int __cdecl snprintf_impl(char *string, size_t count, char *format, ...)
{
    crt_file str;
    int retval;
    va_list ap;

    if (string == NULL)
        assert_report(FILE_sprintf, 0x5d, EXPR_string);
    if (format == NULL)
        assert_report(FILE_sprintf, 0x5e, EXPR_format);
    str.flag = 0x42;
    str.base = string;
    str.ptr = str.base;
    str.cnt = count;
    retval = __output(&str, format, (va_start(ap, format), (char *)ap));
    if (--str.cnt >= 0)
        *str.ptr++ = 0;
    else
        __flsbuf(0, &str);
    return retval;
}

/* 0x005f6bd0: printf(format, ...) */
int __cdecl printf_impl(char *format, ...)
{
    int buffing;
    int retval;
    va_list ap;

    if (format == NULL)
        assert_report(FILE_printf, 0x36, EXPR_format);
    buffing = __stbuf(crt_stdout);
    retval = __output(crt_stdout, format, (va_start(ap, format), (char *)ap));
    __ftbuf(buffing, crt_stdout);
    return retval;
}

/* 0x00600d40: fprintf(stream, format, ...) */
int __cdecl fprintf_impl(crt_file *stream, char *format, ...)
{
    crt_file *f;
    int buffing;
    int retval;
    va_list ap;

    if (stream == NULL)
        assert_report(FILE_fprintf, 0x38, EXPR_str);
    if (format == NULL)
        assert_report(FILE_fprintf, 0x39, EXPR_format);
    f = stream;
    buffing = __stbuf(f);
    retval = __output(f, format, (va_start(ap, format), (char *)ap));
    __ftbuf(buffing, f);
    return retval;
}

/* ------------------------------------------------------------------------ */

/* flags */
#define FL_SIGN         0x0001
#define FL_SIGNSP       0x0002
#define FL_LEFT         0x0004
#define FL_LEADZERO     0x0008
#define FL_LONG         0x0010
#define FL_SHORT        0x0020
#define FL_SIGNED       0x0040
#define FL_ALTERNATE    0x0080
#define FL_NEGATIVE     0x0100
#define FL_FORCEOCTAL   0x0200
#define FL_WIDECHAR     0x0800
#define FL_I64          0x8000

/* states */
enum { ST_NORMAL, ST_PERCENT, ST_FLAG, ST_WIDTH, ST_DOT, ST_PRECIS, ST_SIZE, ST_TYPE };

#define g_lookuptable   ((signed char *)0x0061e748)
#define g_pctype        (*(ushort * *)((u8 *)&g.d_0063a090))
#define g_nullstring    (*(char * *)((u8 *)&g.d_0063a2a8))      /* "(null)" */
#define g_wnullstring   (*(ushort * *)((u8 *)&g.d_0063a2a8 + 4))    /* L"(null)" */

typedef void (__cdecl *cfltcvt_fn)(double *, char *, int, int, int);
typedef void (__cdecl *strfn)(char *);
#define g_cfltcvt       (*(cfltcvt_fn *)((u8 *)&g.d_0063aee0))
#define g_cropzeros     (*(strfn *)((u8 *)&g.d_0063aee0 + 4))
#define g_forcdecpt     (*(strfn *)((u8 *)&g.d_0063aee0 + 12))

typedef struct {
    short length;
    short maxlength;
    char *buffer;
} ansi_string;

/* 0x005fa6b0: _output(stream, format, argptr) -- the printf engine */
int __cdecl __output(crt_file *stream, char *format, char *argptr)
{
    int hexadd;             /* 'a'-'9'-1 or 'A'-'9'-1 */
    char ch;
    int flags;
    int radix;
    int charsout;
    int fldwidth;
    int precision;
    char prefix[2];
    int prefixlen;
    int capexp;
    int no_output;
    char *text;
    int textlen;
    int bufferiswide;
    int state;
    int chclass;
    char buffer[0x200];
    char mbbuf[4];
    double tmp;
    longlong number;
    ulonglong unumber;
    int digit;
    int *pint;
    ansi_string *pstr;
    int i;
    int len;
    char *p;
    ushort *pw;
    ushort wchar;
    int padding;

    charsout = 0;
    state = ST_NORMAL;

    while ((ch = *format++) != 0 && charsout >= 0) {
        if (ch < ' ' || ch > 'x')
            chclass = 0;
        else
            chclass = g_lookuptable[ch - ' '] & 0xf;
        state = g_lookuptable[chclass * 8 + state] >> 4;

        switch (state) {
        case ST_NORMAL:
        normal_state:
            bufferiswide = 0;
            if (g_pctype[(byte)ch] & 0x8000) {      /* isleadbyte */
                write_char((int)ch, stream, &charsout);
                ch = *format++;
                if (ch == 0)
                    assert_report(FILE_output, 0x185, EXPR_ch);
            }
            write_char((int)ch, stream, &charsout);
            break;

        case ST_PERCENT:
            no_output = capexp = fldwidth = prefixlen = 0;
            flags = 0;
            precision = -1;
            bufferiswide = 0;
            break;

        case ST_FLAG:
            switch (ch) {
            case '-': flags |= FL_LEFT; break;
            case '+': flags |= FL_SIGN; break;
            case ' ': flags |= FL_SIGNSP; break;
            case '#': flags |= FL_ALTERNATE; break;
            case '0': flags |= FL_LEADZERO; break;
            }
            break;

        case ST_WIDTH:
            if (ch == '*') {
                fldwidth = get_int_arg(&argptr);
                if (fldwidth < 0) {
                    flags |= FL_LEFT;
                    fldwidth = -fldwidth;
                }
            } else {
                fldwidth = fldwidth * 10 + (ch - '0');
            }
            break;

        case ST_DOT:
            precision = 0;
            break;

        case ST_PRECIS:
            if (ch == '*') {
                precision = get_int_arg(&argptr);
                if (precision < 0)
                    precision = -1;
            } else {
                precision = precision * 10 + (ch - '0');
            }
            break;

        case ST_SIZE:
            switch (ch) {
            case 'l': flags |= FL_LONG; break;
            case 'I':
                if (format[0] == '6' && format[1] == '4') {
                    format += 2;
                    flags |= FL_I64;
                } else {
                    state = ST_NORMAL;
                    goto normal_state;
                }
                break;
            case 'h': flags |= FL_SHORT; break;
            case 'w': flags |= FL_WIDECHAR; break;
            }
            break;

        case ST_TYPE:
            switch (ch) {
            case 'C':
                if (!(flags & (FL_SHORT | FL_LONG | FL_WIDECHAR)))
                    flags |= FL_WIDECHAR;
                /* fall through */
            case 'c':
                if (flags & (FL_LONG | FL_WIDECHAR)) {
                    wchar = (ushort)get_short_arg(&argptr);
                    textlen = _wctomb(buffer, wchar);
                    if (textlen < 0)
                        no_output = 1;
                } else {
                    buffer[0] = (char)get_int_arg(&argptr);
                    textlen = 1;
                }
                text = buffer;
                break;

            case 'Z':
                pstr = (ansi_string *)get_int_arg(&argptr);
                if (pstr == NULL || pstr->buffer == NULL) {
                    text = g_nullstring;
                    textlen = _strlen(text);
                } else if (flags & FL_WIDECHAR) {
                    text = pstr->buffer;
                    textlen = (uint)(int)pstr->length >> 1;
                    bufferiswide = 1;
                } else {
                    bufferiswide = 0;
                    text = pstr->buffer;
                    textlen = pstr->length;
                }
                break;

            case 'S':
                if (!(flags & (FL_SHORT | FL_LONG | FL_WIDECHAR)))
                    flags |= FL_WIDECHAR;
                /* fall through */
            case 's':
                i = precision == -1 ? 0x7fffffff : precision;
                text = (char *)get_int_arg(&argptr);
                if (flags & (FL_LONG | FL_WIDECHAR)) {
                    if (text == NULL)
                        text = (char *)g_wnullstring;
                    bufferiswide = 1;
                    pw = (ushort *)text;
                    while (i-- != 0 && *pw != 0)
                        pw++;
                    textlen = ((int)pw - (int)text) >> 1;
                } else {
                    if (text == NULL)
                        text = g_nullstring;
                    p = text;
                    while (i-- != 0 && *p != 0)
                        p++;
                    textlen = p - text;
                }
                break;

            case 'n':
                pint = (int *)get_int_arg(&argptr);
                if (flags & FL_SHORT)
                    *(short *)pint = (short)charsout;
                else
                    *pint = charsout;
                no_output = 1;
                break;

            case 'E':
            case 'G':
                capexp = 1;
                ch += 'a' - 'A';
                /* fall through */
            case 'e':
            case 'f':
            case 'g':
                flags |= FL_SIGNED;
                text = buffer;
                if (precision < 0)
                    precision = 6;
                else if (precision == 0 && ch == 'g')
                    precision = 1;
                tmp = *(double *)argptr;
                argptr += 8;
                g_cfltcvt(&tmp, text, ch, precision, capexp);
                if ((flags & FL_ALTERNATE) && precision == 0)
                    g_forcdecpt(text);
                if (ch == 'g' && !(flags & FL_ALTERNATE))
                    g_cropzeros(text);
                if (*text == '-') {
                    flags |= FL_NEGATIVE;
                    text++;
                }
                textlen = _strlen(text);
                break;

            case 'd':
            case 'i':
                flags |= FL_SIGNED;
                radix = 10;
                goto COMMON_INT;

            case 'u':
                radix = 10;
                goto COMMON_INT;

            case 'p':
                precision = 8;
                /* fall through */
            case 'X':
                hexadd = 'A' - '9' - 1;
                goto COMMON_HEX;

            case 'x':
                hexadd = 'a' - '9' - 1;
            COMMON_HEX:
                radix = 16;
                if (flags & FL_ALTERNATE) {
                    prefix[0] = '0';
                    prefix[1] = (char)('x' - 'a' + '9' + 1 + hexadd);
                    prefixlen = 2;
                }
                goto COMMON_INT;

            case 'o':
                radix = 8;
                if (flags & FL_ALTERNATE)
                    flags |= FL_FORCEOCTAL;
            COMMON_INT:
                if (flags & FL_I64) {
                    number = get_int64_arg(&argptr);
                } else if (flags & FL_SHORT) {
                    if (flags & FL_SIGNED)
                        number = (short)get_int_arg(&argptr);
                    else
                        number = (ushort)get_int_arg(&argptr);
                } else {
                    if (flags & FL_SIGNED)
                        number = (int)get_int_arg(&argptr);
                    else
                        number = (uint)get_int_arg(&argptr);
                }
                if ((flags & FL_SIGNED) && number < 0) {
                    unumber = -(ulonglong)number;
                    flags |= FL_NEGATIVE;
                } else {
                    unumber = number;
                }
                if (!(flags & FL_I64))
                    unumber &= 0xffffffff;
                if (precision < 0)
                    precision = 1;
                else
                    flags &= ~FL_LEADZERO;
                if (unumber == 0)
                    prefixlen = 0;
                text = &buffer[0x1ff];
                while (precision-- > 0 || unumber != 0) {
                    digit = (int)(unumber % (ulonglong)(longlong)radix) + '0';
                    unumber = unumber / (ulonglong)(longlong)radix;
                    if (digit > '9')
                        digit += hexadd;
                    *text-- = (char)digit;
                }
                textlen = &buffer[0x1ff] - text;
                text++;
                if ((flags & FL_FORCEOCTAL) && (*text != '0' || textlen == 0)) {
                    *--text = '0';
                    textlen++;
                }
                break;
            }

            if (!no_output) {
                if (flags & FL_SIGNED) {
                    if (flags & FL_NEGATIVE) {
                        prefix[0] = '-';
                        prefixlen = 1;
                    } else if (flags & FL_SIGN) {
                        prefix[0] = '+';
                        prefixlen = 1;
                    } else if (flags & FL_SIGNSP) {
                        prefix[0] = ' ';
                        prefixlen = 1;
                    }
                }
                padding = fldwidth - textlen - prefixlen;
                if (!(flags & (FL_LEFT | FL_LEADZERO)))
                    write_multi_char(' ', padding, stream, &charsout);
                write_string(prefix, prefixlen, stream, &charsout);
                if ((flags & FL_LEADZERO) && !(flags & FL_LEFT))
                    write_multi_char('0', padding, stream, &charsout);
                if (bufferiswide && textlen > 0) {
                    pw = (ushort *)text;
                    i = textlen;
                    while (i-- != 0) {
                        len = _wctomb(mbbuf, *pw++);
                        if (len <= 0)
                            break;
                        write_string(mbbuf, len, stream, &charsout);
                    }
                } else {
                    write_string(text, textlen, stream, &charsout);
                }
                if (flags & FL_LEFT)
                    write_multi_char(' ', padding, stream, &charsout);
            }
            break;
        }
    }
    return charsout;
}
