/*
 * Append-only text logs backed by a memory-mapped file.  The OS keeps the
 * written bytes even when the harness kills the game, so nothing is lost to
 * stdio buffering.  Unused tail space stays NUL and readers strip it.
 */
#include <stdarg.h>
#include <stdio.h>
#include "hook.h"

#define MAPLOG_SIZE (256u << 20)

int maplog_open(struct maplog *l, const char *path)
{
    HANDLE f = CreateFileA(path, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL,
                           CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE m;
    if (f == INVALID_HANDLE_VALUE)
        return 0;
    m = CreateFileMappingA(f, NULL, PAGE_READWRITE, 0, MAPLOG_SIZE, NULL);
    if (!m)
        return 0;
    l->base = (char *)MapViewOfFile(m, FILE_MAP_WRITE, 0, 0, MAPLOG_SIZE);
    l->pos = 0;
    l->cap = l->base ? MAPLOG_SIZE : 0;
    return l->base != NULL;
}

void maplog_printf(struct maplog *l, const char *fmt, ...)
{
    va_list ap;
    int n;
    if (!l->base || l->pos + 512 > l->cap)
        return;
    va_start(ap, fmt);
    n = _vsnprintf(l->base + l->pos, 511, fmt, ap);
    va_end(ap);
    if (n > 0)
        l->pos += n;
}
