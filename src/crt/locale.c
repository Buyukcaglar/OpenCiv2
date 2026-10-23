/*
 * C runtime locale / NLS wrappers (MSVC 4.2 debug CRT): __crtLCMapString*,
 * __crtGetStringType*, __crtCompareString*, and the character-class and
 * case-mapping functions built on them.
 *
 * Each wrapper probes once whether the A or W flavour of the Win32 API works
 * and converts the strings for the other flavour when necessary.  The
 * original's static helpers strncnt/wcsncnt exist at several addresses and
 * are inlined here (crt_strncnt / crt_wcsncnt below are file-local).
 */
#include "game.h"

#define g_lc_ctype_handle   (*(LCID *)((u8 *)&g.d_0063a078))   /* __lc_handle[LC_CTYPE] */
#define g_lc_codepage       (*(UINT *)((u8 *)&g.d_0063a088))   /* __lc_codepage */
#define g_pctype            (*(ushort * *)((u8 *)&g.d_0063a090))
#define g_mb_cur_max        (*(int *)((u8 *)&g.d_0063a29c))
#define g_mbctype           ((byte *)0x0063afa0)
#define g_mbcodepage        (*(UINT *)((u8 *)&g.d_0063b0a4))
#define g_mblcid            (*(LCID *)((u8 *)&g.d_0063b0a8))
#define g_errno             (*(int *)((u8 *)&g.d_00639f14))

#define f_use_lcmapW        (*(int *)((u8 *)&g.d_0063a068))
#define f_use_lcmapA        (*(int *)((u8 *)&g.d_0063a06c))
#define f_use_ctypeW        (*(int *)((u8 *)&g.d_0063b26c))
#define f_use_ctypeA        (*(int *)((u8 *)&g.d_0063b270))
#define f_use_cmpW          (*(int *)((u8 *)&g.d_0063b69c))
#define f_use_cmpA          (*(int *)((u8 *)&g.d_0063b6a0))

#define USE_W 1
#define USE_A 2

#define probe_strA  ((LPCSTR)0x0061e6a8)    /* "\0" */
#define probe_strW  ((LPCWSTR)0x0061e6ac)   /* L"\0" */
#define FILE_aw_map ((char *)0x0061e69c)    /* "aw_map.c" */
#define FILE_aw_str ((char *)0x0061eb78)    /* "aw_str.c" */
#define FILE_aw_cmp ((char *)0x0061ec3c)    /* "aw_cmp.c" */
#define FILE_strupr ((char *)0x0061ec94)    /* "strupr.c" */
#define FILE_strlwr ((char *)0x0061eca0)    /* "strlwr.c" */
#define EXPR_aw_cmp ((char *)0x0061ec48)    /* "(cchCount1==0 && cchCount2==1) || ..." */

/* strncnt / wcsncnt: length of a string, at most cnt. */
static int crt_strncnt(const char *s, int cnt)
{
    const char *p = s;
    int n = cnt;

    while (n-- != 0 && *p != 0)
        p++;
    if (*p == 0)
        return p - s;
    return cnt;
}

static int crt_wcsncnt(const ushort *s, int cnt)
{
    const ushort *p = s;
    int n = cnt;

    while (n-- != 0 && *p != 0)
        p++;
    if (*p == 0)
        return ((int)p - (int)s) >> 1;
    return cnt;
}

/* ------------------------------------------------------------------------ */

/* 0x005f9370: __crtLCMapStringW(lcid, flags, src, cchSrc, dst, cchDest, code_page) */
int __cdecl ___crtLCMapStringW(LCID lcid, DWORD flags, LPCWSTR src, int cchSrc,
                               LPWSTR dst, int cchDest, UINT code_page)
{
    char *inbuf = NULL;
    char *outbuf = NULL;
    int insize, outsize;
    int ret;

    if (f_use_lcmapW == 0) {
        if (LCMapStringW(0, LCMAP_LOWERCASE, probe_strW, 1, NULL, 0) != 0)
            f_use_lcmapW = USE_W;
        else if (LCMapStringA(0, LCMAP_LOWERCASE, probe_strA, 1, NULL, 0) != 0)
            f_use_lcmapW = USE_A;
        else
            return 0;
    }
    if (cchSrc > 0)
        cchSrc = crt_wcsncnt(src, cchSrc);
    if (f_use_lcmapW == USE_W)
        return LCMapStringW(lcid, flags, src, cchSrc, dst, cchDest);
    if (f_use_lcmapW != USE_A)
        return 0;

    if (code_page == 0)
        code_page = g_lc_codepage;
    insize = WideCharToMultiByte(code_page, 0x220, src, cchSrc, NULL, 0, NULL, NULL);
    if (insize == 0)
        return 0;
    inbuf = (char *)__malloc_dbg(insize, 2, FILE_aw_map, 0xcc);
    if (inbuf == NULL)
        return 0;
    if (WideCharToMultiByte(code_page, 0x220, src, cchSrc, inbuf, insize, NULL, NULL) == 0)
        goto error;
    outsize = LCMapStringA(lcid, flags, inbuf, insize, NULL, 0);
    if (outsize == 0)
        goto error;
    outbuf = (char *)__malloc_dbg(outsize, 2, FILE_aw_map, 0xdb);
    if (outbuf == NULL)
        goto error;
    if (LCMapStringA(lcid, flags, inbuf, insize, outbuf, outsize) == 0)
        goto error;
    if (flags & LCMAP_SORTKEY) {
        ret = outsize;
        if (cchDest != 0)
            _strncpy((char *)dst, outbuf, cchDest < outsize ? cchDest : outsize);
    } else if (cchDest == 0) {
        ret = MultiByteToWideChar(code_page, MB_PRECOMPOSED, outbuf, outsize, NULL, 0);
        if (ret == 0)
            goto error;
    } else {
        ret = MultiByteToWideChar(code_page, MB_PRECOMPOSED, outbuf, outsize, dst, cchDest);
        if (ret == 0)
            goto error;
    }
    __free_dbg(inbuf, 2);
    __free_dbg(outbuf, 2);
    return ret;
error:
    __free_dbg(inbuf, 2);
    __free_dbg(outbuf, 2);
    return 0;
}

/* 0x005f96e0: __crtLCMapStringA(lcid, flags, src, cchSrc, dst, cchDest, code_page) */
int __cdecl ___crtLCMapStringA(LCID lcid, DWORD flags, LPCSTR src, int cchSrc,
                               LPSTR dst, int cchDest, UINT code_page)
{
    WCHAR *inbuf = NULL;
    WCHAR *outbuf = NULL;
    int insize, outsize;
    int ret;

    if (f_use_lcmapA == 0) {
        if (LCMapStringA(0, LCMAP_LOWERCASE, probe_strA, 1, NULL, 0) != 0)
            f_use_lcmapA = USE_A;
        else if (LCMapStringW(0, LCMAP_LOWERCASE, probe_strW, 1, NULL, 0) != 0)
            f_use_lcmapA = USE_W;
        else
            return 0;
    }
    if (cchSrc > 0)
        cchSrc = crt_strncnt(src, cchSrc);
    if (f_use_lcmapA == USE_A)
        return LCMapStringA(lcid, flags, src, cchSrc, dst, cchDest);
    if (f_use_lcmapA != USE_W)
        return 0;

    if (code_page == 0)
        code_page = g_lc_codepage;
    insize = MultiByteToWideChar(code_page, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, src, cchSrc, NULL, 0);
    if (insize == 0)
        return 0;
    inbuf = (WCHAR *)__malloc_dbg(insize * 2, 2, FILE_aw_map, 0x16d);
    if (inbuf == NULL)
        return 0;
    if (MultiByteToWideChar(code_page, MB_PRECOMPOSED, src, cchSrc, inbuf, insize) == 0)
        goto error;
    ret = LCMapStringW(lcid, flags, inbuf, insize, NULL, 0);
    if (ret == 0)
        goto error;
    if (flags & LCMAP_SORTKEY) {
        if (cchDest != 0) {
            if (cchDest < ret)
                goto error;
            if (LCMapStringW(lcid, flags, inbuf, insize, (LPWSTR)dst, cchDest) == 0)
                goto error;
        }
    } else {
        outsize = ret;
        outbuf = (WCHAR *)__malloc_dbg(outsize * 2, 2, FILE_aw_map, 0x191);
        if (outbuf == NULL)
            goto error;
        if (LCMapStringW(lcid, flags, inbuf, insize, outbuf, outsize) == 0)
            goto error;
        if (cchDest == 0) {
            ret = WideCharToMultiByte(code_page, 0x220, outbuf, outsize, NULL, 0, NULL, NULL);
            if (ret == 0)
                goto error;
        } else {
            ret = WideCharToMultiByte(code_page, 0x220, outbuf, outsize, dst, cchDest, NULL, NULL);
            if (ret == 0)
                goto error;
        }
    }
    __free_dbg(inbuf, 2);
    __free_dbg(outbuf, 2);
    return ret;
error:
    __free_dbg(inbuf, 2);
    __free_dbg(outbuf, 2);
    return 0;
}

/* ------------------------------------------------------------------------ */

/* 0x00601300: __crtGetStringTypeW(dwInfoType, src, cchSrc, lpCharType, code_page, lcid) */
BOOL __cdecl ___crtGetStringTypeW(DWORD type, LPCWSTR src, int cchSrc, LPWORD chartype,
                                  UINT code_page, LCID lcid)
{
    WORD dummy;
    BOOL ret = 0;
    char *abuf = NULL;
    WORD *wtype = NULL;
    int size;

    if (f_use_ctypeW == 0) {
        if (GetStringTypeW(CT_CTYPE1, probe_strW, 1, &dummy) != 0)
            f_use_ctypeW = USE_W;
        else if (GetStringTypeA(0, CT_CTYPE1, probe_strA, 1, &dummy) != 0)
            f_use_ctypeW = USE_A;
        else
            return 0;
    }
    if (f_use_ctypeW == USE_W)
        return GetStringTypeW(type, src, cchSrc, chartype);
    if (f_use_ctypeW != USE_A)
        return 0;

    if (code_page == 0)
        code_page = g_lc_codepage;
    size = WideCharToMultiByte(code_page, 0x220, src, cchSrc, NULL, 0, NULL, NULL);
    if (size == 0)
        return 0;
    abuf = (char *)__calloc_dbg(1, size, 2, FILE_aw_str, 0x76);
    if (abuf == NULL)
        return 0;
    if (WideCharToMultiByte(code_page, 0x220, src, cchSrc, abuf, size, NULL, NULL) == 0)
        goto done;
    wtype = (WORD *)__malloc_dbg(size * 2 + 2, 2, FILE_aw_str, 0x80);
    if (wtype == NULL)
        goto done;
    if (lcid == 0)
        lcid = g_lc_ctype_handle;
    wtype[cchSrc] = 0xffff;
    wtype[cchSrc - 1] = wtype[cchSrc];
    ret = GetStringTypeA(lcid, type, abuf, size, wtype);
    if (wtype[cchSrc - 1] == 0xffff || wtype[cchSrc] != 0xffff)
        ret = 0;
    else
        crt_memmove(chartype, wtype, cchSrc * 2);
done:
    __free_dbg(abuf, 2);
    __free_dbg(wtype, 2);
    return ret;
}

/* 0x00601560: __crtGetStringTypeA(dwInfoType, src, cchSrc, lpCharType, code_page, lcid) */
BOOL __cdecl ___crtGetStringTypeA(DWORD type, LPCSTR src, int cchSrc, LPWORD chartype,
                                  UINT code_page, LCID lcid)
{
    WORD dummy;
    BOOL ret = 0;
    WCHAR *wbuf = NULL;
    int size, n;

    if (f_use_ctypeA == 0) {
        if (GetStringTypeA(0, CT_CTYPE1, probe_strA, 1, &dummy) != 0)
            f_use_ctypeA = USE_A;
        else if (GetStringTypeW(CT_CTYPE1, probe_strW, 1, &dummy) != 0)
            f_use_ctypeA = USE_W;
        else
            return 0;
    }
    if (f_use_ctypeA == USE_A) {
        if (lcid == 0)
            lcid = g_lc_ctype_handle;
        return GetStringTypeA(lcid, type, src, cchSrc, chartype);
    }
    if (f_use_ctypeA != USE_W)
        return 0;

    if (code_page == 0)
        code_page = g_lc_codepage;
    size = MultiByteToWideChar(code_page, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, src, cchSrc, NULL, 0);
    if (size == 0)
        goto done;
    wbuf = (WCHAR *)__calloc_dbg(2, size, 2, FILE_aw_str, 0x104);
    if (wbuf == NULL)
        goto done;
    n = MultiByteToWideChar(code_page, MB_PRECOMPOSED, src, cchSrc, wbuf, size);
    if (n == 0)
        goto done;
    ret = GetStringTypeW(type, wbuf, n, chartype);
done:
    __free_dbg(wbuf, 2);
    return ret;
}

/* ------------------------------------------------------------------------ */

/* 0x00606330: __crtCompareStringW(lcid, flags, s1, cch1, s2, cch2, code_page) */
int __cdecl ___crtCompareStringW(LCID lcid, DWORD flags, LPCWSTR s1, int cch1,
                                 LPCWSTR s2, int cch2, UINT code_page)
{
    int ret = 0;
    char *buf1 = NULL;
    char *buf2 = NULL;
    int n1, n2;

    if (f_use_cmpW == 0) {
        if (CompareStringW(0, 0, probe_strW, 1, probe_strW, 1) != 0)
            f_use_cmpW = USE_W;
        else if (CompareStringA(0, 0, probe_strA, 1, probe_strA, 1) != 0)
            f_use_cmpW = USE_A;
        else
            return 0;
    }
    if (cch1 > 0)
        cch1 = crt_wcsncnt(s1, cch1);
    if (cch2 > 0)
        cch2 = crt_wcsncnt(s2, cch2);
    if (cch1 == 0 || cch2 == 0) {
        if (cch1 - cch2 == 0)
            return 2;
        if (cch1 - cch2 < 0)
            return 1;
        return 3;
    }
    if (f_use_cmpW == USE_W)
        return CompareStringW(lcid, flags, s1, cch1, s2, cch2);
    if (f_use_cmpW != USE_A)
        return 0;

    if (code_page == 0)
        code_page = g_lc_codepage;
    n1 = WideCharToMultiByte(code_page, 0x220, s1, cch1, NULL, 0, NULL, NULL);
    if (n1 == 0)
        return 0;
    buf1 = (char *)__malloc_dbg(n1, 2, FILE_aw_cmp, 0xc4);
    if (buf1 == NULL)
        return 0;
    if (WideCharToMultiByte(code_page, 0x220, s1, cch1, buf1, n1, NULL, NULL) == 0)
        goto error;
    n2 = WideCharToMultiByte(code_page, 0x220, s2, cch2, NULL, 0, NULL, NULL);
    if (n2 == 0)
        goto error;
    buf2 = (char *)__malloc_dbg(n2, 2, FILE_aw_cmp, 0xd5);
    if (buf2 == NULL)
        goto error;
    if (WideCharToMultiByte(code_page, 0x220, s2, cch2, buf2, n2, NULL, NULL) == 0)
        goto error;
    ret = CompareStringA(lcid, flags, buf1, n1, buf2, n2);
    __free_dbg(buf1, 2);
    __free_dbg(buf2, 2);
    return ret;
error:
    __free_dbg(buf1, 2);
    __free_dbg(buf2, 2);
    return 0;
}

/* lead-byte test for the one-character special case of __crtCompareStringA */
static int is_lead_byte(CPINFO *cpi, byte c)
{
    byte *r;

    for (r = cpi->LeadByte; r[0] != 0 && r[1] != 0; r += 2)
        if (r[0] <= c && c <= r[1])
            return 1;
    return 0;
}

/* 0x00606690: __crtCompareStringA(lcid, flags, s1, cch1, s2, cch2, code_page) */
int __cdecl ___crtCompareStringA(LCID lcid, DWORD flags, LPCSTR s1, int cch1,
                                 LPCSTR s2, int cch2, UINT code_page)
{
    int ret = 0;
    int n1 = 0, n2 = 0;
    WCHAR *w1 = NULL;
    WCHAR *w2 = NULL;
    CPINFO cpi;

    if (f_use_cmpA == 0) {
        if (CompareStringA(0, 0, probe_strA, 1, probe_strA, 1) != 0)
            f_use_cmpA = USE_A;
        else if (CompareStringW(0, 0, probe_strW, 1, probe_strW, 1) != 0)
            f_use_cmpA = USE_W;
        else
            return 0;
    }
    if (cch1 > 0)
        cch1 = crt_strncnt(s1, cch1);
    if (cch2 > 0)
        cch2 = crt_strncnt(s2, cch2);
    if (f_use_cmpA == USE_A)
        return CompareStringA(lcid, flags, s1, cch1, s2, cch2);
    if (f_use_cmpA != USE_W)
        return 0;

    if (code_page == 0)
        code_page = g_lc_codepage;
    if (cch1 == 0 || cch2 == 0) {
        if (cch2 == cch1)
            return 2;
        if (cch2 > 1)
            return 1;
        if (cch1 > 1)
            return 3;
        if (GetCPInfo(code_page, &cpi) == 0)
            return 0;
        if (!((cch1 == 0 && cch2 == 1) || (cch1 == 1 && cch2 == 0)) &&
            __CrtDbgReport(2, FILE_aw_cmp, 0x162, 0, EXPR_aw_cmp) == 1)
            __asm__ volatile("int3");
        if (cch1 > 0) {
            if (cpi.MaxCharSize < 2)
                return 3;
            if (is_lead_byte(&cpi, *(byte *)s1))
                return 2;
            return 3;
        }
        if (cch2 > 0) {
            if (cpi.MaxCharSize < 2)
                return 1;
            if (is_lead_byte(&cpi, *(byte *)s2))
                return 2;
            return 1;
        }
    }
    n1 = MultiByteToWideChar(code_page, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, s1, cch1, NULL, 0);
    if (n1 == 0)
        return 0;
    w1 = (WCHAR *)__malloc_dbg(n1 * 2, 2, FILE_aw_cmp, 0x18a);
    if (w1 == NULL)
        return 0;
    if (MultiByteToWideChar(code_page, MB_PRECOMPOSED, s1, cch1, w1, n1) == 0)
        goto done;
    n2 = MultiByteToWideChar(code_page, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, s2, cch2, NULL, 0);
    if (n2 == 0)
        goto done;
    w2 = (WCHAR *)__malloc_dbg(n2 * 2, 2, FILE_aw_cmp, 0x199);
    if (w2 == NULL)
        goto done;
    if (MultiByteToWideChar(code_page, MB_PRECOMPOSED, s2, cch2, w2, n2) == 0)
        goto done;
    ret = CompareStringW(lcid, flags, w1, n1, w2, n2);
done:
    __free_dbg(w1, 2);
    __free_dbg(w2, 2);
    return ret;
}

/* ------------------------------------------------------------------------ */

/* 0x005f9a70: _isctype(c, mask) */
int __cdecl __isctype(int c, int mask)
{
    char buf[3];
    int n;
    int chartype;     /* only the low word is written by GetStringType */

    if ((uint)(c + 1) <= 0x100)
        return g_pctype[c] & mask;
    if (g_pctype[(byte)(c >> 8)] & 0x8000) {
        buf[0] = (char)(c >> 8);
        buf[1] = (char)c;
        buf[2] = 0;
        n = 2;
    } else {
        buf[0] = (char)c;
        buf[1] = 0;
        n = 1;
    }
    if (___crtGetStringTypeA(CT_CTYPE1, buf, n, (LPWORD)&chartype, 0, 0) == 0)
        return 0;
    return chartype & 0xffff & mask;
}

/* 0x005f2700: toupper(c) */
uint __cdecl crt_toupper(uint c)
{
    int is_lower;
    char in[3];
    byte out[4];
    int n;

    if (g_lc_ctype_handle == 0) {
        if ((int)c >= 'a' && (int)c <= 'z')
            c -= 0x20;
        return c;
    }
    if ((int)c < 0x100) {
        if (g_mb_cur_max > 1)
            is_lower = __isctype(c, 2);
        else
            is_lower = g_pctype[c] & 2;
        if (is_lower == 0)
            return c;
    }
    if (g_pctype[(byte)(c >> 8)] & 0x8000) {
        in[0] = (char)(c >> 8);
        in[1] = (char)c;
        in[2] = 0;
        n = 2;
    } else {
        in[0] = (char)c;
        in[1] = 0;
        n = 1;
    }
    n = ___crtLCMapStringA(g_lc_ctype_handle, LCMAP_UPPERCASE, in, n, (char *)out, 3, 0);
    if (n == 0)
        return c;
    if (n == 1)
        return out[0];
    return (uint)out[1] << 8 | out[0];
}

/* 0x005fc5e0: tolower(c) */
int __cdecl _tolower(int c)
{
    int is_upper;
    char in[3];
    byte out[4];
    int n;

    if (g_lc_ctype_handle == 0) {
        if (c >= 'A' && c <= 'Z')
            c += 0x20;
        return c;
    }
    if (c < 0x100) {
        if (g_mb_cur_max > 1)
            is_upper = __isctype(c, 1);
        else
            is_upper = g_pctype[c] & 1;
        if (is_upper == 0)
            return c;
    }
    if (g_pctype[(byte)(c >> 8)] & 0x8000) {
        in[0] = (char)(c >> 8);
        in[1] = (char)c;
        in[2] = 0;
        n = 2;
    } else {
        in[0] = (char)c;
        in[1] = 0;
        n = 1;
    }
    n = ___crtLCMapStringA(g_lc_ctype_handle, LCMAP_LOWERCASE, in, n, (char *)out, 3, 0);
    if (n == 0)
        return c;
    if (n == 1)
        return out[0];
    return (int)out[1] << 8 | out[0];
}

/* shared body of _strupr / _strlwr */
static char *map_string(char *string, DWORD map, char lo, char hi, int delta, char *file, int line)
{
    char *p;
    char *dst = NULL;
    int size;

    if (g_lc_ctype_handle == 0) {
        for (p = string; *p != 0; p++)
            if (*p >= lo && *p <= hi)
                *p = *p + delta;
        return string;
    }
    size = ___crtLCMapStringA(g_lc_ctype_handle, map, string, -1, NULL, 0, 0);
    if (size != 0 && (dst = (char *)__malloc_dbg(size, 2, file, line)) != NULL &&
        ___crtLCMapStringA(g_lc_ctype_handle, map, string, -1, dst, size, 0) != 0)
        crt_strcpy(string, dst);
    __free_dbg(dst, 2);
    return string;
}

/* 0x006076c0: _strupr(string) */
char * __cdecl __strupr(char *string)
{
    return map_string(string, LCMAP_UPPERCASE, 'a', 'z', -0x20, FILE_strupr, 0x61);
}

/* 0x006077f0: _strlwr(string) */
char * __cdecl __strlwr(char *string)
{
    return map_string(string, LCMAP_LOWERCASE, 'A', 'Z', 0x20, FILE_strlwr, 0x64);
}

/* 0x005fc090: _mbctoupper(c) */
uint __cdecl __mbctoupper(uint c)
{
    byte in[4];
    byte out[4];

    if (c > 0xff) {
        in[0] = (byte)(c >> 8);
        in[1] = (byte)c;
        if (!(g_mbctype[in[0] + 1] & 4))
            return c;
        if (___crtLCMapStringA(g_mblcid, LCMAP_UPPERCASE, (char *)in, 2, (char *)out, 2, g_mbcodepage) == 0)
            return c;
        return (uint)out[1] + ((uint)out[0] << 8);
    }
    if ((int)c >= 'a' && (int)c <= 'z')
        return c - 0x20;
    return c;
}

/* 0x006061f0: _mbsnbicoll(s1, s2, n) */
int __cdecl __mbsnbicoll(uchar *s1, uchar *s2, size_t n)
{
    int ret;

    if (n == 0)
        return 0;
    ret = ___crtCompareStringA(g_mblcid, NORM_IGNORECASE, (LPCSTR)s1, n, (LPCSTR)s2, n, g_mbcodepage);
    if (ret == 0)
        return 0x7fffffff;
    return ret - 2;
}

/* 0x00602310: wctomb(mbchar, wchar).  wchar arrives promoted to int; its
 * low word is passed to WideCharToMultiByte in place. */
int __cdecl _wctomb(char *mbchar, int wchar)
{
    int defused;
    int n;

    if (mbchar == NULL)
        return 0;
    if (g_lc_ctype_handle == 0) {
        if ((wchar & 0xffff) > 0xff) {
            g_errno = 0x2a;
            return -1;
        }
        *mbchar = (char)wchar;
        return 1;
    }
    defused = 0;
    n = WideCharToMultiByte(g_lc_codepage, 0x220, (LPCWSTR)&wchar, 1, mbchar, g_mb_cur_max, NULL, &defused);
    if (n == 0 || defused != 0) {
        g_errno = 0x2a;
        return -1;
    }
    return n;
}
