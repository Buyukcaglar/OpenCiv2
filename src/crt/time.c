/*
 * time(), __loctotime_t and _isindst from the MSVC 4.2 C runtime.
 */
#include "game.h"

/* struct tm (MSVC layout) */
typedef struct {
    int tm_sec, tm_min, tm_hour, tm_mday, tm_mon, tm_year, tm_wday, tm_yday, tm_isdst;
} crt_tm;

/* time() caches the DST state for the last GetSystemTime minute */
#define g_dstflag_cache     (*(int *)((u8 *)&g.d_006e5488))
#define g_gmt_cache         (*(SYSTEMTIME *)((u8 *)&g.d_006e5490))

#define g_timezone          (*(long *)((u8 *)&g.d_0063b2b0))
#define g_daylight          (*(int *)((u8 *)&g.d_0063b2b4))
#define g_dstbias           (*(long *)((u8 *)&g.d_0063b2b8))
#define g_days              ((int *)0x0063b3a4)        /* _days[]: cumulative days before month */
#define g_use_tz_info       (*(int *)((u8 *)&g.d_006e55e0))
#define g_tz_std_date       (*(SYSTEMTIME *)((u8 *)&g.d_006e562c))   /* tzinfo.StandardDate */
#define g_tz_dst_date       (*(SYSTEMTIME *)((u8 *)&g.d_006e5680))   /* tzinfo.DaylightDate */

/* transitiondate dststart / dstend: { yr, yd, ms } */
#define g_dststart_yr       (*(int *)((u8 *)&g.d_0063b350))
#define g_dststart_yd       (*(int *)((u8 *)&g.d_0063b354))
#define g_dststart_ms       (*(int *)((u8 *)&g.d_0063b358))
#define g_dstend_yr         (*(int *)((u8 *)&g.d_0063b360))
#define g_dstend_yd         (*(int *)((u8 *)&g.d_0063b364))
#define g_dstend_ms         (*(int *)((u8 *)&g.d_0063b368))

/* 0x005f7320: time(timeptr) */
time_t __cdecl _time(time_t *timeptr)
{
    SYSTEMTIME loct;
    SYSTEMTIME gmt;
    TIME_ZONE_INFORMATION tzinfo;
    DWORD tzstate;
    int dstflag;
    time_t tim;

    GetLocalTime(&loct);
    GetSystemTime(&gmt);
    if (gmt.wMinute == g_gmt_cache.wMinute && gmt.wHour == g_gmt_cache.wHour &&
        gmt.wDay == g_gmt_cache.wDay && gmt.wMonth == g_gmt_cache.wMonth &&
        gmt.wYear == g_gmt_cache.wYear) {
        dstflag = g_dstflag_cache;
    } else {
        tzstate = GetTimeZoneInformation(&tzinfo);
        if (tzstate == 2)
            dstflag = 1;
        else if (tzstate == 1)
            dstflag = 0;
        else
            dstflag = -1;
        g_dstflag_cache = dstflag;
        g_gmt_cache = gmt;
    }
    tim = ___loctotime_t(loct.wYear, loct.wMonth, loct.wDay, loct.wHour, loct.wMinute,
                         loct.wSecond, dstflag);
    if (timeptr != NULL)
        *timeptr = tim;
    return tim;
}

/* 0x006002e0: __loctotime_t(yr, mo, dy, hr, mn, sc, dstflag) */
int __cdecl ___loctotime_t(int yr, int mo, int dy, int hr, int mn, int sc, int dstflag)
{
    int tmpdays;
    int tmptim;
    crt_tm tb;

    yr -= 1900;
    if (yr < 70 || yr > 138)
        return -1;
    tmpdays = g_days[mo] + dy;
    if ((yr & 3) == 0 && mo > 2)
        tmpdays++;
    tmptim = (((yr - 70) * 365 + ((yr - 1) >> 2) - 17 + tmpdays) * 24 + hr) * 60 + mn;
    tmptim = tmptim * 60 + sc;
    ___tzset();
    tmptim += g_timezone;
    /* The original leaves tm_sec/tm_min (read by _isindst on a transition
     * day) uninitialised; they are zeroed here. */
    tb.tm_sec = 0;
    tb.tm_min = 0;
    tb.tm_yday = tmpdays;
    tb.tm_year = yr;
    tb.tm_mon = mo - 1;
    tb.tm_hour = hr;
    if (dstflag == 1 || (dstflag == -1 && g_daylight != 0 && __isindst(&tb) != 0))
        tmptim += g_dstbias;
    return tmptim;
}

/* 0x006039b0: _isindst(tb) */
int __cdecl __isindst(crt_tm *tb)
{
    int ms;

    if (g_daylight == 0)
        return 0;
    if (tb->tm_year != g_dststart_yr || tb->tm_year != g_dstend_yr) {
        if (g_use_tz_info != 0) {
            if (g_tz_dst_date.wYear == 0)
                cvtdate(1, 1, tb->tm_year, g_tz_dst_date.wMonth, g_tz_dst_date.wDay,
                        g_tz_dst_date.wDayOfWeek, 0, g_tz_dst_date.wHour, g_tz_dst_date.wMinute,
                        g_tz_dst_date.wSecond, g_tz_dst_date.wMilliseconds);
            else
                cvtdate(1, 0, tb->tm_year, g_tz_dst_date.wMonth, 0, 0, g_tz_dst_date.wDay,
                        g_tz_dst_date.wHour, g_tz_dst_date.wMinute, g_tz_dst_date.wSecond,
                        g_tz_dst_date.wMilliseconds);
            if (g_tz_std_date.wYear == 0)
                cvtdate(0, 1, tb->tm_year, g_tz_std_date.wMonth, g_tz_std_date.wDay,
                        g_tz_std_date.wDayOfWeek, 0, g_tz_std_date.wHour, g_tz_std_date.wMinute,
                        g_tz_std_date.wSecond, g_tz_std_date.wMilliseconds);
            else
                cvtdate(0, 0, tb->tm_year, g_tz_std_date.wMonth, 0, 0, g_tz_std_date.wDay,
                        g_tz_std_date.wHour, g_tz_std_date.wMinute, g_tz_std_date.wSecond,
                        g_tz_std_date.wMilliseconds);
        } else {
            /* USA rules: first Sunday in April .. last Sunday in October, 2am */
            cvtdate(1, 1, tb->tm_year, 4, 1, 0, 0, 2, 0, 0, 0);
            cvtdate(0, 1, tb->tm_year, 10, 5, 0, 0, 2, 0, 0, 0);
        }
    }
    if (g_dststart_yd < g_dstend_yd) {
        if (tb->tm_yday < g_dststart_yd || tb->tm_yday > g_dstend_yd)
            return 0;
        if (tb->tm_yday > g_dststart_yd && tb->tm_yday < g_dstend_yd)
            return 1;
    } else {
        if (tb->tm_yday < g_dstend_yd || tb->tm_yday > g_dststart_yd)
            return 1;
        if (tb->tm_yday > g_dstend_yd && tb->tm_yday < g_dststart_yd)
            return 0;
    }
    ms = (tb->tm_hour * 3600 + tb->tm_min * 60 + tb->tm_sec) * 1000;
    if (tb->tm_yday == g_dststart_yd)
        return ms >= g_dststart_ms ? 1 : 0;
    return ms < g_dstend_ms ? 1 : 0;
}
