/*
 * The part of WASI (preview 1) the game's wasm32 module imports, over POSIX:
 * files and directories, clocks, arguments, environment and exit.  The host
 * file system's root is the module's one preopened directory, so the paths
 * the module uses are the host's (as in the native builds).  On Windows the
 * module sees MSYS-style paths: /c/Users/... is C:/Users/... (port_main.c
 * converts the paths it hands over).
 */
#define _GNU_SOURCE
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include "port.h"
#include "host.h"

#ifdef _WIN32
#include <direct.h>
#include <io.h>
#define lstat stat
#define mkdir(p, mode) _mkdir(p)
#define lseek _lseeki64
#define environ _environ
#ifndef S_ISLNK
#define S_ISLNK(m) 0
#endif
#ifndef S_ISBLK
#define S_ISBLK(m) 0
#endif
struct iovec { void *iov_base; size_t iov_len; };
/* (no readv/writev: one buffer at a time) */
static long iov_io(int fd, const struct iovec *v, int n, int writing)
{
    long total = 0;
    int i;
    for (i = 0; i < n; i++) {
        int r = writing ? _write(fd, v[i].iov_base, (unsigned)v[i].iov_len)
                        : _read(fd, v[i].iov_base, (unsigned)v[i].iov_len);
        if (r < 0)
            return total ? total : -1;
        total += r;
        if ((size_t)r < v[i].iov_len)
            break;
    }
    return total;
}
#define readv(fd, v, n) iov_io(fd, v, n, 0)
#define writev(fd, v, n) iov_io(fd, v, n, 1)
#else
#include <sys/uio.h>
#define O_BINARY 0
#endif

/* WASI error numbers */
enum {
    W_SUCCESS = 0, W_2BIG = 1, W_ACCES = 2, W_BADF = 8, W_BUSY = 10, W_EXIST = 20, W_FBIG = 22, W_INVAL = 28,
    W_IO = 29, W_ISDIR = 31, W_LOOP = 32, W_MFILE = 33, W_NAMETOOLONG = 37, W_NFILE = 41, W_NOENT = 44,
    W_NOMEM = 48, W_NOSPC = 51, W_NOSYS = 52, W_NOTDIR = 54, W_NOTEMPTY = 55, W_PERM = 63, W_ROFS = 69,
    W_SPIPE = 70, W_XDEV = 75
};

static u32 werr(int e)
{
    switch (e) {
    case 0: return W_SUCCESS;
    case E2BIG: return W_2BIG;
    case EACCES: return W_ACCES;
    case EBADF: return W_BADF;
    case EBUSY: return W_BUSY;
    case EEXIST: return W_EXIST;
    case EFBIG: return W_FBIG;
    case EINVAL: return W_INVAL;
    case EISDIR: return W_ISDIR;
    case ELOOP: return W_LOOP;
    case EMFILE: return W_MFILE;
    case ENAMETOOLONG: return W_NAMETOOLONG;
    case ENFILE: return W_NFILE;
    case ENOENT: return W_NOENT;
    case ENOMEM: return W_NOMEM;
    case ENOSPC: return W_NOSPC;
    case ENOTDIR: return W_NOTDIR;
    case ENOTEMPTY: return W_NOTEMPTY;
    case EPERM: return W_PERM;
    case EROFS: return W_ROFS;
    case ESPIPE: return W_SPIPE;
    case EXDEV: return W_XDEV;
    }
    return W_IO;
}

/* File descriptors: 0-2 the host's, 3 the preopened root, then files
 * (host descriptors) and directories (their paths). */
#define MAX_FD 256
typedef struct { int used, host, is_dir; char *path; } Fd;
static Fd fds[MAX_FD];
static int argc_;
static char **argv_;

void wasi_init(int argc, char **argv)
{
    int i;
    argc_ = argc;
    argv_ = argv;
    for (i = 0; i < 3; i++) {
        fds[i].used = 1;
        fds[i].host = i;
    }
    fds[3].used = 1;
    fds[3].is_dir = 1;
    fds[3].host = -1;
    fds[3].path = strdup("/");
}

static Fd *fd_get(u32 fd)
{
    return fd < MAX_FD && fds[fd].used ? &fds[fd] : NULL;
}

static int fd_new(void)
{
    int i;
    for (i = 4; i < MAX_FD; i++)
        if (!fds[i].used) {
            memset(&fds[i], 0, sizeof fds[i]);
            fds[i].used = 1;
            fds[i].host = -1;
            return i;
        }
    return -1;
}

/* The host path of path (len bytes of module memory) under directory dirfd. */
static char *resolve(Fd *dir, u32 path, u32 len)
{
    size_t n = strlen(dir->path);
    char *s = malloc(n + len + 2);
    memcpy(s, dir->path, n);
    if (!n || s[n - 1] != '/')
        s[n++] = '/';
    memcpy(s + n, MEM(path), len);
    s[n + len] = 0;
#ifdef _WIN32
    /* /c/... -> C:/... */
    if (s[0] == '/' && s[1] && (s[2] == '/' || !s[2]) && ((s[1] | 0x20) >= 'a' && (s[1] | 0x20) <= 'z')) {
        s[0] = (char)(s[1] & ~0x20);
        s[1] = ':';
        if (!s[2]) {
            s[2] = '/';
            s[3] = 0;
        }
    }
#endif
    return s;
}

static void put_filestat(u32 buf, const struct stat *st)
{
    u8 type = S_ISDIR(st->st_mode) ? 3 : S_ISREG(st->st_mode) ? 4 : S_ISLNK(st->st_mode) ? 7 :
              S_ISCHR(st->st_mode) ? 2 : S_ISBLK(st->st_mode) ? 1 : 0;
    memset(MEM(buf), 0, 64);
    PUT64(buf, (u64)st->st_dev);
    PUT64(buf + 8, (u64)st->st_ino);
    *(u8 *)MEM(buf + 16) = type;
    PUT64(buf + 24, (u64)st->st_nlink);
    PUT64(buf + 32, (u64)st->st_size);
    PUT64(buf + 40, (u64)st->st_atime * 1000000000ull);
    PUT64(buf + 48, (u64)st->st_mtime * 1000000000ull);
    PUT64(buf + 56, (u64)st->st_ctime * 1000000000ull);
}

/* CIV2_TRACE_FILES=PATH: the files the game opens, one per line (with
 * "-" before those it could not), e.g. to list what it needs of the
 * installed game (tools/gen_manifest.py). */
static void trace_open(const char *path, int ok)
{
    static FILE *log;
    static int tried;
    if (!tried) {
        const char *t = getenv("CIV2_TRACE_FILES");
        tried = 1;
        if (t && *t)
            log = fopen(t, "a");
    }
    if (log) {
        fprintf(log, "%s%s\n", ok ? "" : "-", path);
        fflush(log);
    }
}

/* ---- arguments, environment, clocks, exit ---- */

#define WASI(name) w2c_wasi__snapshot__preview1_##name
typedef struct w2c_wasi__snapshot__preview1 Wasi;

u32 WASI(args_sizes_get)(Wasi *w, u32 argc, u32 size)
{
    int i;
    u32 n = 0;
    (void)w;
    for (i = 0; i < argc_; i++)
        n += (u32)strlen(argv_[i]) + 1;
    PUT32(argc, (u32)argc_);
    PUT32(size, n);
    return 0;
}

u32 WASI(args_get)(Wasi *w, u32 argv, u32 buf)
{
    int i;
    (void)w;
    for (i = 0; i < argc_; i++) {
        size_t n = strlen(argv_[i]) + 1;
        PUT32(argv + 4 * (u32)i, buf);
        memcpy(MEM(buf), argv_[i], n);
        buf += (u32)n;
    }
    return 0;
}

#ifndef _WIN32
extern char **environ;
#endif

u32 WASI(environ_sizes_get)(Wasi *w, u32 count, u32 size)
{
    u32 n = 0, c = 0;
    char **e;
    (void)w;
    for (e = environ; *e; e++, c++)
        n += (u32)strlen(*e) + 1;
    PUT32(count, c);
    PUT32(size, n);
    return 0;
}

u32 WASI(environ_get)(Wasi *w, u32 env, u32 buf)
{
    char **e;
    u32 i = 0;
    (void)w;
    for (e = environ; *e; e++, i++) {
        size_t n = strlen(*e) + 1;
        PUT32(env + 4 * i, buf);
        memcpy(MEM(buf), *e, n);
        buf += (u32)n;
    }
    return 0;
}

u32 WASI(clock_time_get)(Wasi *w, u32 id, u64 precision, u32 out)
{
    struct timespec ts;
    (void)w;
    (void)precision;
    if (clock_gettime(id == 0 ? CLOCK_REALTIME : CLOCK_MONOTONIC, &ts))
        return werr(errno);
    PUT64(out, (u64)ts.tv_sec * 1000000000ull + (u64)ts.tv_nsec);
    return 0;
}

void WASI(proc_exit)(Wasi *w, u32 code)
{
    (void)w;
    fflush(NULL);
    host_quit();            /* SDL's threads stop before the process does */
    exit((int)code);
}

/* ---- descriptors ---- */

u32 WASI(fd_prestat_get)(Wasi *w, u32 fd, u32 buf)
{
    (void)w;
    if (fd != 3)
        return W_BADF;
    PUT32(buf, 0);          /* a directory */
    PUT32(buf + 4, 1);      /* "/" */
    return 0;
}

u32 WASI(fd_prestat_dir_name)(Wasi *w, u32 fd, u32 path, u32 len)
{
    (void)w;
    if (fd != 3)
        return W_BADF;
    if (len)
        *(char *)MEM(path) = '/';
    return 0;
}

u32 WASI(fd_fdstat_get)(Wasi *w, u32 fd, u32 buf)
{
    Fd *f = fd_get(fd);
    struct stat st;
    u8 type = 0;
    (void)w;
    if (!f)
        return W_BADF;
    if (f->is_dir)
        type = 3;
    else if (!fstat(f->host, &st))
        type = S_ISREG(st.st_mode) ? 4 : S_ISCHR(st.st_mode) ? 2 : 0;
    memset(MEM(buf), 0, 24);
    *(u8 *)MEM(buf) = type;
    PUT64(buf + 8, ~0ull);          /* all rights */
    PUT64(buf + 16, ~0ull);
    return 0;
}

u32 WASI(fd_fdstat_set_flags)(Wasi *w, u32 fd, u32 flags)
{
    (void)w;
    (void)flags;
    return fd_get(fd) ? 0 : W_BADF;
}

u32 WASI(fd_filestat_get)(Wasi *w, u32 fd, u32 buf)
{
    Fd *f = fd_get(fd);
    struct stat st;
    (void)w;
    if (!f)
        return W_BADF;
    if (f->is_dir ? stat(f->path, &st) : fstat(f->host, &st))
        return werr(errno);
    put_filestat(buf, &st);
    return 0;
}

u32 WASI(path_filestat_get)(Wasi *w, u32 fd, u32 flags, u32 path, u32 len, u32 buf)
{
    Fd *d = fd_get(fd);
    struct stat st;
    char *p;
    int r;
    (void)w;
    if (!d || !d->is_dir)
        return W_BADF;
    p = resolve(d, path, len);
    r = (flags & 1) ? stat(p, &st) : lstat(p, &st);
    free(p);
    if (r)
        return werr(errno);
    put_filestat(buf, &st);
    return 0;
}

u32 WASI(path_open)(Wasi *w, u32 dirfd, u32 dirflags, u32 path, u32 len, u32 oflags, u64 rights, u64 inheriting,
                    u32 fdflags, u32 out)
{
    Fd *d = fd_get(dirfd);
    char *p;
    struct stat st;
    int flags = 0, h, fd, rd = (rights & (1ull << 1)) != 0, wr = (rights & (1ull << 6)) != 0;
    (void)w;
    (void)dirflags;
    (void)inheriting;
    if (!d || !d->is_dir)
        return W_BADF;
    p = resolve(d, path, len);
    if ((oflags & 2) || (!(oflags & 1) && !stat(p, &st) && S_ISDIR(st.st_mode))) {
        /* a directory: kept as its path */
        if (stat(p, &st) || !S_ISDIR(st.st_mode)) {
            u32 e = stat(p, &st) ? werr(errno) : W_NOTDIR;
            free(p);
            return e;
        }
        if ((fd = fd_new()) < 0) {
            free(p);
            return W_MFILE;
        }
        fds[fd].is_dir = 1;
        fds[fd].path = p;
        PUT32(out, (u32)fd);
        return 0;
    }
    flags = rd && wr ? O_RDWR : wr ? O_WRONLY : O_RDONLY;
    if (oflags & 1) flags |= O_CREAT;
    if (oflags & 4) flags |= O_EXCL;
    if (oflags & 8) flags |= O_TRUNC;
    if (fdflags & 1) flags |= O_APPEND;
    h = open(p, flags | O_BINARY, 0666);
    trace_open(p, h >= 0);
    free(p);
    if (h < 0)
        return werr(errno);
    if ((fd = fd_new()) < 0) {
        close(h);
        return W_MFILE;
    }
    fds[fd].host = h;
    PUT32(out, (u32)fd);
    return 0;
}

u32 WASI(fd_close)(Wasi *w, u32 fd)
{
    Fd *f = fd_get(fd);
    (void)w;
    if (!f || fd < 4)
        return f ? 0 : W_BADF;
    if (f->host >= 0)
        close(f->host);
    free(f->path);
    memset(f, 0, sizeof *f);
    return 0;
}

static u32 rw(u32 fd, u32 iovs, u32 n, u32 done, int writing)
{
    Fd *f = fd_get(fd);
    struct iovec v[64];
    u32 i;
    ssize_t r;
    if (!f || f->is_dir)
        return W_BADF;
    if (n > 64)
        n = 64;
    for (i = 0; i < n; i++) {
        v[i].iov_base = MEM(GET32(iovs + 8 * i));
        v[i].iov_len = GET32(iovs + 8 * i + 4);
    }
    r = writing ? writev(f->host, v, (int)n) : readv(f->host, v, (int)n);
    if (r < 0)
        return werr(errno);
    PUT32(done, (u32)r);
    return 0;
}

u32 WASI(fd_read)(Wasi *w, u32 fd, u32 iovs, u32 n, u32 done)
{
    (void)w;
    return rw(fd, iovs, n, done, 0);
}

u32 WASI(fd_write)(Wasi *w, u32 fd, u32 iovs, u32 n, u32 done)
{
    (void)w;
    return rw(fd, iovs, n, done, 1);
}

u32 WASI(fd_seek)(Wasi *w, u32 fd, u64 offset, u32 whence, u32 out)
{
    Fd *f = fd_get(fd);
    int64_t r;
    (void)w;
    if (!f || f->is_dir)
        return W_BADF;
    r = lseek(f->host, (off_t)(int64_t)offset, whence == 0 ? SEEK_SET : whence == 1 ? SEEK_CUR : SEEK_END);
    if (r < 0)
        return werr(errno);
    PUT64(out, (u64)r);
    return 0;
}

/* Directory entries from position cookie: 24-byte headers, each followed
 * by its name; a last entry that does not fit is cut short (the caller then
 * retries with a larger buffer). */
u32 WASI(fd_readdir)(Wasi *w, u32 fd, u32 buf, u32 len, u64 cookie, u32 used)
{
    Fd *f = fd_get(fd);
    DIR *dir;
    struct dirent *e;
    u64 k = 0;
    u32 pos = 0;
    (void)w;
    if (!f || !f->is_dir)
        return W_BADF;
    if (!(dir = opendir(f->path)))
        return werr(errno);
    while (pos < len && (e = readdir(dir))) {
        u8 hdr[24];
        u32 n = (u32)strlen(e->d_name), m;
        if (k++ < cookie)
            continue;
        memset(hdr, 0, sizeof hdr);
        memcpy(hdr, &k, 8);                          /* d_next */
        {
            u64 ino = (u64)e->d_ino;
            memcpy(hdr + 8, &ino, 8);
        }
        memcpy(hdr + 16, &n, 4);
#ifdef _WIN32
        hdr[20] = 0;                                 /* unknown: the reader stats it */
#else
        hdr[20] = e->d_type == DT_DIR ? 3 : e->d_type == DT_REG ? 4 : e->d_type == DT_LNK ? 7 : 0;
#endif
        m = len - pos < 24 ? len - pos : 24;
        memcpy(MEM(buf + pos), hdr, m);
        pos += m;
        m = len - pos < n ? len - pos : n;
        memcpy(MEM(buf + pos), e->d_name, m);
        pos += m;
    }
    closedir(dir);
    PUT32(used, pos);
    return 0;
}

/* ---- paths ---- */

static u32 path_op(u32 fd, u32 path, u32 len, int (*op)(const char *))
{
    Fd *d = fd_get(fd);
    char *p;
    int r;
    if (!d || !d->is_dir)
        return W_BADF;
    p = resolve(d, path, len);
    r = op(p);
    free(p);
    return r ? werr(errno) : 0;
}

static int make_dir(const char *p) { return mkdir(p, 0777); }

u32 WASI(path_create_directory)(Wasi *w, u32 fd, u32 path, u32 len)
{
    (void)w;
    return path_op(fd, path, len, make_dir);
}

u32 WASI(path_remove_directory)(Wasi *w, u32 fd, u32 path, u32 len)
{
    (void)w;
    return path_op(fd, path, len, rmdir);
}

u32 WASI(path_unlink_file)(Wasi *w, u32 fd, u32 path, u32 len)
{
    (void)w;
    return path_op(fd, path, len, unlink);
}

u32 WASI(path_rename)(Wasi *w, u32 fd, u32 old, u32 old_len, u32 fd2, u32 new, u32 new_len)
{
    Fd *d = fd_get(fd), *d2 = fd_get(fd2);
    char *a, *b;
    int r;
    (void)w;
    if (!d || !d2 || !d->is_dir || !d2->is_dir)
        return W_BADF;
    a = resolve(d, old, old_len);
    b = resolve(d2, new, new_len);
    r = rename(a, b);
    free(a);
    free(b);
    return r ? werr(errno) : 0;
}
