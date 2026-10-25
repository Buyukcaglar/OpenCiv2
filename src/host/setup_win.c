/*
 * Windows: the game set up beside the program, from the user's copy of
 * Civilization II Multiplayer Gold Edition (setup.h).  The game is found
 * where it usually is: installed (where its installer said, in the
 * registry, or in the usual folders) or its CD in a drive; else the user
 * says where.  An installed game's folder is copied; from the CD the game
 * is unpacked from its InstallShield cabinet (DATA1.CAB, with unshield), as
 * its installer would, and its videos copied.  Into GameData beside the
 * program, with the program's own files (the fonts, from its resources)
 * into data.
 */
#include <windows.h>
#include <shlobj.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include <libunshield.h>
#include "setup.h"

#define MGE_KEY "SOFTWARE\\MicroProse Software\\Civilization II Multiplayer Gold Edition"
#define DONE_FILE "OpenCiv2-setup.txt"      /* in GameData: written when the set-up is complete */
#define TITLE "OpenCiv2"

static int dir_exists(const char *p)
{
    DWORD a = GetFileAttributesA(p);
    return a != INVALID_FILE_ATTRIBUTES && (a & FILE_ATTRIBUTE_DIRECTORY);
}

static int file_exists(const char *p)
{
    DWORD a = GetFileAttributesA(p);
    return a != INVALID_FILE_ATTRIBUTES && !(a & FILE_ATTRIBUTE_DIRECTORY);
}

static void make_dirs(const char *path)
{
    char p[MAX_PATH];
    size_t i;
    snprintf(p, sizeof p, "%s", path);
    for (i = 3; p[i]; i++)
        if (p[i] == '\\' || p[i] == '/') {
            char c = p[i];
            p[i] = 0;
            CreateDirectoryA(p, NULL);
            p[i] = c;
        }
    CreateDirectoryA(p, NULL);
}

static void message(const char *text, UINT icon)
{
    MessageBoxA(NULL, text, TITLE, MB_OK | icon);
}

/* ---- where the game is ---- */

/* An installed game (or a copy of its folder). */
static int game_folder(const char *dir)
{
    char p[MAX_PATH + 32];
    snprintf(p, sizeof p, "%s\\Civ2Art.dll", dir);
    if (!file_exists(p))
        return 0;
    snprintf(p, sizeof p, "%s\\RULES.TXT", dir);
    return file_exists(p);
}

/* The game's CD (or a copy of it): the cabinet the installer unpacks, the
   folder with the videos. */
static int game_cd(const char *root)
{
    char p[MAX_PATH + 32];
    snprintf(p, sizeof p, "%s\\DATA1.CAB", root);
    if (!file_exists(p))
        return 0;
    snprintf(p, sizeof p, "%s\\CIV2", root);
    return dir_exists(p);
}

static void registry_path(HKEY root, REGSAM view, char *out, size_t size)
{
    HKEY k;
    DWORD type, n = (DWORD)size - 1;
    out[0] = 0;
    if (RegOpenKeyExA(root, MGE_KEY, 0, KEY_READ | view, &k) != ERROR_SUCCESS)
        return;
    if (RegQueryValueExA(k, "Game Path", NULL, &type, (LPBYTE)out, &n) != ERROR_SUCCESS || type != REG_SZ)
        n = 0;
    out[n] = 0;
    RegCloseKey(k);
    while (n > 3 && (out[n - 1] == '\\' || out[n - 1] == '/' || out[n - 1] == 0))
        out[--n] = 0;
}

/* The installed game: where the registry says, else the usual folders. */
static int find_installed(char *out, size_t size)
{
    static const HKEY roots[] = {HKEY_LOCAL_MACHINE, HKEY_CURRENT_USER};
    static const REGSAM views[] = {KEY_WOW64_32KEY, KEY_WOW64_64KEY};
    static const char *const bases[] = {"ProgramFiles(x86)", "ProgramFiles", "ProgramW6432"};
    static const char *const folders[] = {"MicroProse Software\\Civilization II Multiplayer Gold Edition",
                                          "MicroProse\\Civilization II Multiplayer Gold Edition"};
    static const char *const others[] = {"C:\\MPS\\CIV2", "C:\\Civ2", "C:\\Games\\Civ2"};
    const char *v;
    size_t i, k;
    for (i = 0; i < sizeof roots / sizeof roots[0]; i++)
        for (k = 0; k < sizeof views / sizeof views[0]; k++) {
            registry_path(roots[i], views[k], out, size);
            if (out[0] && game_folder(out))
                return 1;
        }
    for (i = 0; i < sizeof bases / sizeof bases[0]; i++)
        if ((v = getenv(bases[i])) && *v)
            for (k = 0; k < sizeof folders / sizeof folders[0]; k++) {
                snprintf(out, size, "%s\\%s", v, folders[k]);
                if (game_folder(out))
                    return 1;
            }
    for (i = 0; i < sizeof others / sizeof others[0]; i++) {
        snprintf(out, size, "%s", others[i]);
        if (game_folder(out))
            return 1;
    }
    if ((v = getenv("USERPROFILE")) && *v) {
        snprintf(out, size, "%s\\Civ2", v);
        if (game_folder(out))
            return 1;
    }
    return 0;
}

/* The CD, in any CD drive (an empty drive passed over without asking). */
static int find_cd(char *out, size_t size)
{
    UINT old = SetErrorMode(SEM_FAILCRITICALERRORS);
    DWORD drives = GetLogicalDrives();
    char root[4] = "A:\\";
    int i, found = 0;
    for (i = 0; i < 26 && !found; i++)
        if (drives & (1u << i)) {
            root[0] = (char)('A' + i);
            if (GetDriveTypeA(root) == DRIVE_CDROM) {
                snprintf(out, size, "%c:", 'A' + i);
                found = game_cd(out);
            }
        }
    SetErrorMode(old);
    return found;
}

/* The user's choice of folder: the installed game or the CD.  0: none. */
static int ask_folder(char *out, size_t size)
{
    BROWSEINFOA bi;
    LPITEMIDLIST id;
    char path[MAX_PATH];
    int ok = 0;
    memset(&bi, 0, sizeof bi);
    bi.lpszTitle = "Where is Civilization II Multiplayer Gold Edition? Choose the folder it is "
                   "installed in, or its CD.";
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
    CoInitialize(NULL);
    id = SHBrowseForFolderA(&bi);
    if (id) {
        ok = SHGetPathFromIDListA(id, path);
        CoTaskMemFree(id);
    }
    CoUninitialize();
    if (ok) {
        size_t n = strlen(path);
        while (n > 2 && (path[n - 1] == '\\' || path[n - 1] == '/'))
            path[--n] = 0;
        snprintf(out, size, "%s", path);
    }
    return ok;
}

/* ---- the progress window ---- */

static HWND progress, progress_text;
static const char *copy_dest;           /* GameData: not copied into itself */
static int cancelled;

static LRESULT CALLBACK progress_proc(HWND h, UINT msg, WPARAM wp, LPARAM lp)
{
    if (msg == WM_CLOSE) {
        cancelled = 1;
        return 0;
    }
    return DefWindowProcA(h, msg, wp, lp);
}

static void progress_open(void)
{
    WNDCLASSA wc;
    RECT r;
    memset(&wc, 0, sizeof wc);
    wc.lpfnWndProc = progress_proc;
    wc.hInstance = GetModuleHandleA(NULL);
    wc.hCursor = LoadCursor(NULL, IDC_WAIT);
    wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    wc.lpszClassName = "OpenCiv2Setup";
    RegisterClassA(&wc);
    SystemParametersInfoA(SPI_GETWORKAREA, 0, &r, 0);
    progress = CreateWindowA(wc.lpszClassName, TITLE ": setting up the game", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
                             (r.left + r.right) / 2 - 260, (r.top + r.bottom) / 2 - 60, 520, 120, NULL, NULL,
                             wc.hInstance, NULL);
    progress_text = CreateWindowA("STATIC", "", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_PATHELLIPSIS, 16, 16, 480, 50,
                                  progress, NULL, wc.hInstance, NULL);
    SendMessageA(progress_text, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);
    ShowWindow(progress, SW_SHOW);
}

/* what is being done; 0: go on, 1: the user closed the window */
static int progress_show(const char *what, const char *detail)
{
    char text[MAX_PATH + 128];
    MSG m;
    snprintf(text, sizeof text, "%s\n%s", what, detail ? detail : "");
    if (progress_text)
        SetWindowTextA(progress_text, text);
    while (PeekMessageA(&m, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&m);
        DispatchMessageA(&m);
    }
    return cancelled;
}

static void progress_close(void)
{
    if (progress)
        DestroyWindow(progress);
    progress = progress_text = NULL;
}

/* ---- copying and unpacking ---- */

/* src's files and folders into dst (made if need be); 0: stopped */
static int copy_tree(const char *src, const char *dst)
{
    WIN32_FIND_DATAA fd;
    char pat[MAX_PATH], from[MAX_PATH], to[MAX_PATH];
    HANDLE h;
    int ok = 1;
    make_dirs(dst);
    snprintf(pat, sizeof pat, "%s\\*", src);
    h = FindFirstFileA(pat, &fd);
    if (h == INVALID_HANDLE_VALUE)
        return 1;
    do {
        if (!strcmp(fd.cFileName, ".") || !strcmp(fd.cFileName, ".."))
            continue;
        snprintf(from, sizeof from, "%s\\%s", src, fd.cFileName);
        snprintf(to, sizeof to, "%s\\%s", dst, fd.cFileName);
        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (!copy_dest || _stricmp(from, copy_dest))
                ok = copy_tree(from, to);
        } else {
            if (progress_show("Copying", from)) {
                ok = 0;
            } else if (!CopyFileA(from, to, FALSE)) {
                char text[2 * MAX_PATH + 64];
                snprintf(text, sizeof text, "Could not copy %s to %s.", from, to);
                message(text, MB_ICONERROR);
                ok = 0;
            } else {
                SetFileAttributesA(to, FILE_ATTRIBUTE_NORMAL);     /* (read-only on the CD) */
            }
        }
    } while (ok && FindNextFileA(h, &fd));
    FindClose(h);
    return ok;
}

/* The game from the CD's cabinet into dst, as its installer unpacks it
   (the "Sound Files" group into Sound, the others as their folders say). */
static int unpack_cab(const char *cab, const char *dst)
{
    Unshield *u;
    int g, i, ok = 1;
    unshield_set_log_level(0);
    u = unshield_open(cab);
    if (!u) {
        char text[MAX_PATH + 64];
        snprintf(text, sizeof text, "Could not read %s.", cab);
        message(text, MB_ICONERROR);
        return 0;
    }
    for (g = 0; ok && g < unshield_file_group_count(u); g++) {
        UnshieldFileGroup *fg = unshield_file_group_get(u, g);
        const char *sub = !strcmp(fg->name, "Sound Files") ? "Sound" : "";
        for (i = (int)fg->first_file; ok && i <= (int)fg->last_file; i++) {
            const char *dir, *name;
            char folder[MAX_PATH], path[MAX_PATH];
            if (!unshield_file_is_valid(u, i))
                continue;
            dir = unshield_directory_name(u, unshield_file_directory(u, i));
            name = unshield_file_name(u, i);
            snprintf(folder, sizeof folder, "%s%s%s%s%s", dst, *sub ? "\\" : "", sub, dir && *dir ? "\\" : "",
                     dir ? dir : "");
            make_dirs(folder);
            snprintf(path, sizeof path, "%s\\%s", folder, name);
            if (progress_show("Unpacking", path)) {
                ok = 0;
            } else if (!unshield_file_save(u, i, path)) {
                char text[MAX_PATH + 64];
                snprintf(text, sizeof text, "Could not unpack %s.", name);
                message(text, MB_ICONERROR);
                ok = 0;
            }
        }
    }
    unshield_close(u);
    return ok;
}

/* The CD's videos (KINGS, VIDEO) into game_dir, where it has none. */
static int copy_videos(const char *cd, const char *game_dir)
{
    static const char *const folders[] = {"KINGS", "VIDEO"};
    char from[MAX_PATH], to[MAX_PATH];
    size_t i;
    for (i = 0; i < sizeof folders / sizeof folders[0]; i++) {
        snprintf(from, sizeof from, "%s\\CIV2\\%s", cd, folders[i]);
        snprintf(to, sizeof to, "%s\\%s", game_dir, folders[i]);
        if (dir_exists(from) && !dir_exists(to) && !copy_tree(from, to))
            return 0;
    }
    return 1;
}

/* ---- the program's own files ---- */

/* Resource id's file into path: 8 bytes of size, then the file deflated
   (tools/build_port.py). */
static int unpack_resource(int id, const char *path)
{
    HRSRC r = FindResourceA(NULL, MAKEINTRESOURCEA(id), (LPCSTR)RT_RCDATA);
    HGLOBAL g = r ? LoadResource(NULL, r) : NULL;
    const unsigned char *data = g ? LockResource(g) : NULL;
    DWORD n = r ? SizeofResource(NULL, r) : 0;
    unsigned char out[1 << 16];
    z_stream z;
    FILE *f;
    int st = Z_OK;
    if (!data || n < 8 || !(f = fopen(path, "wb")))
        return 0;
    memset(&z, 0, sizeof z);
    inflateInit(&z);
    z.next_in = (unsigned char *)data + 8;
    z.avail_in = n - 8;
    while (st == Z_OK) {
        z.next_out = out;
        z.avail_out = sizeof out;
        st = inflate(&z, Z_NO_FLUSH);
        if (st != Z_OK && st != Z_STREAM_END)
            break;
        fwrite(out, 1, sizeof out - z.avail_out, f);
    }
    inflateEnd(&z);
    if (fclose(f) != 0 || st != Z_STREAM_END) {
        DeleteFileA(path);
        return 0;
    }
    return 1;
}

/* The fonts in data beside the program, where missing. */
static int program_files(const char *dir)
{
    static const struct { int id; const char *name; } files[] = {
        {SETUP_RES_FONTS, "fonts.bin"}, {SETUP_RES_FONTS_AA, "fonts_aa.bin"}};
    char data[MAX_PATH], path[MAX_PATH];
    size_t i;
    snprintf(data, sizeof data, "%s\\data", dir);
    for (i = 0; i < sizeof files / sizeof files[0]; i++) {
        snprintf(path, sizeof path, "%s\\%s", data, files[i].name);
        if (file_exists(path))
            continue;
        make_dirs(data);
        progress_show("Unpacking", path);
        if (!unpack_resource(files[i].id, path)) {
            char text[MAX_PATH + 64];
            snprintf(text, sizeof text, "Could not write %s.", path);
            message(text, MB_ICONERROR);
            return 0;
        }
    }
    return 1;
}

/* ---- the set-up ---- */

/* GameData from source (an installed game's folder or the CD), and from
   the CD (cd, may be "") its videos.  1: done. */
static int set_up(const char *game_dir, const char *source, const char *cd)
{
    char done[MAX_PATH];
    FILE *f;
    int ok;
    progress_show(game_cd(source) ? "Unpacking the game from its CD" : "Copying the game", source);
    if (game_cd(source)) {
        char cab[MAX_PATH];
        snprintf(cab, sizeof cab, "%s\\DATA1.CAB", source);
        ok = unpack_cab(cab, game_dir);
    } else {
        ok = copy_tree(source, game_dir);
    }
    if (ok && *cd)
        ok = copy_videos(cd, game_dir);
    if (!ok)
        return 0;
    snprintf(done, sizeof done, "%s\\%s", game_dir, DONE_FILE);
    if ((f = fopen(done, "w"))) {
        fprintf(f, "OpenCiv2: the game set up from %s%s%s.\n", source, *cd && strcmp(cd, source) ? ", videos from " : "",
                *cd && strcmp(cd, source) ? cd : "");
        fclose(f);
    }
    return 1;
}

int setup_choose_game(int argc, char **argv, char *game, size_t size)
{
    char dir[MAX_PATH], game_data[MAX_PATH], done[MAX_PATH], source[MAX_PATH], cd[MAX_PATH] = "";
    char *slash;
    int again = argc > 1 && !strcmp(argv[1], "--setup"), ok;

    GetModuleFileNameA(NULL, dir, sizeof dir);
    if ((slash = strrchr(dir, '\\')))
        *slash = 0;
    if (argc > 1 && !again) {
        /* a folder: the game, played where it is */
        if (!dir_exists(argv[1])) {
            char text[MAX_PATH + 64];
            snprintf(text, sizeof text, "There is no folder %s.", argv[1]);
            message(text, MB_ICONERROR);
            return 0;
        }
        snprintf(game, size, "%s", argv[1]);
        return program_files(dir);
    }
    if (argc < 2 && getenv("CIV2_SCRIPT") && *getenv("CIV2_SCRIPT")) {
        /* a replay (the test harness): the game where it is run */
        GetCurrentDirectoryA((DWORD)size, game);
        return program_files(dir);
    }
    snprintf(game_data, sizeof game_data, "%s\\GameData", dir);
    snprintf(done, sizeof done, "%s\\%s", game_data, DONE_FILE);
    snprintf(game, size, "%s", game_data);
    if (file_exists(done) && !again)
        return program_files(dir);

    /* where the game is: --setup FOLDER, the installed game, the CD, else asked */
    if (!find_cd(cd, sizeof cd))
        cd[0] = 0;
    if (again && argc > 2)
        snprintf(source, sizeof source, "%s", argv[2]);
    else if (!find_installed(source, sizeof source))
        snprintf(source, sizeof source, "%s", cd);
    while (!game_folder(source) && !game_cd(source)) {
        if (source[0]) {
            char text[MAX_PATH + 160];
            snprintf(text, sizeof text, "%s has neither an installed Civilization II Multiplayer Gold Edition nor "
                     "its CD.", source);
            message(text, MB_ICONWARNING);
        } else {
            message("Civilization II Multiplayer Gold Edition was found neither where it is usually installed "
                    "nor in a CD drive. Please show where it is: the folder it is installed in, or its CD.",
                    MB_ICONINFORMATION);
        }
        if (!ask_folder(source, sizeof source))
            return 0;
    }
    if (game_cd(source))
        snprintf(cd, sizeof cd, "%s", source);
    copy_dest = game_data;
    progress_open();
    ok = program_files(dir) && set_up(game_data, source, cd);
    progress_close();
    if (!ok && cancelled)
        message("The set-up was stopped; it starts again the next time.", MB_ICONINFORMATION);
    return ok;
}
