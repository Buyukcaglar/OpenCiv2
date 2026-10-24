/*
 * Windows API types for native (non-Windows) builds, with the sizes 64-bit
 * Windows uses (LLP64): LONG/DWORD/UINT are 32-bit, *_PTR types, WPARAM,
 * LPARAM and LRESULT are pointer-sized.
 *
 * Handles are 32-bit integers (small values handed out by the platform
 * layer, src/platform/): the 1996 code keeps handles in 32-bit fields of
 * its own structures, so they must stay 4 bytes.
 */
#ifndef CIV2_WIN32_TYPES_H
#define CIV2_WIN32_TYPES_H

#include <stdint.h>
#include <stddef.h>
#include <limits.h>

/* Calling conventions do not exist on other platforms. */
#define __cdecl
#define __stdcall
#define __fastcall
#define __thiscall
#define WINAPI
#define CALLBACK
#define APIENTRY
#define STDMETHODCALLTYPE
#define FAR
#define NEAR
#define CONST const
#define VOID void
#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

typedef int32_t BOOL, WINBOOL, LONG, INT, HRESULT, LSTATUS, MCIERROR_SIGNED;
typedef uint32_t DWORD, UINT, ULONG, LCID, REGSAM, FOURCC, COLORREF, MMRESULT, MCIERROR, MCIDEVICEID;
typedef uint8_t BYTE, BOOLEAN, UCHAR;
typedef char CHAR;
typedef int16_t SHORT;
typedef uint16_t WORD, USHORT, ATOM, WCHAR;
typedef float FLOAT;
typedef intptr_t INT_PTR, LONG_PTR, LPARAM, LRESULT;
typedef uintptr_t UINT_PTR, ULONG_PTR, DWORD_PTR, WPARAM, SIZE_T;
typedef int64_t LONGLONG;
typedef uint64_t ULONGLONG;

typedef void *LPVOID, *PVOID;
typedef const void *LPCVOID;
typedef char *LPSTR, *PSTR, *HPSTR;
typedef const char *LPCSTR, *PCSTR, *LPCCH, *PCNZCH;
typedef WCHAR *LPWSTR;
typedef const WCHAR *LPCWSTR, *LPCWCH, *PCNZWCH;
typedef BYTE *LPBYTE, *PBYTE;
typedef WORD *LPWORD;
typedef DWORD *LPDWORD, *PDWORD;
typedef LONG *LPLONG, *PLONG;
typedef INT *LPINT;
typedef BOOL *LPBOOL;
typedef UINT *LPUINT;

#define __MSABI_LONG(x) x
#define MAKEINTRESOURCEA(i) ((LPSTR)(ULONG_PTR)(WORD)(i))
#define MAKEINTRESOURCE MAKEINTRESOURCEA
#define IS_INTRESOURCE(p) ((((ULONG_PTR)(p)) >> 16) == 0)
#define LOWORD(l) ((WORD)((DWORD_PTR)(l) & 0xffff))
#define HIWORD(l) ((WORD)((DWORD_PTR)(l) >> 16))
#define LOBYTE(w) ((BYTE)((DWORD_PTR)(w) & 0xff))
#define MAKELONG(a, b) ((LONG)(((WORD)((DWORD_PTR)(a) & 0xffff)) | ((DWORD)((WORD)((DWORD_PTR)(b) & 0xffff))) << 16))
#define MAKEWPARAM(l, h) ((WPARAM)(DWORD)MAKELONG(l, h))
#define MAKELPARAM(l, h) ((LPARAM)(DWORD)MAKELONG(l, h))
#define RGB(r, g, b) ((COLORREF)(((BYTE)(r) | ((WORD)((BYTE)(g)) << 8)) | (((DWORD)(BYTE)(b)) << 16)))
#define GetRValue(c) ((BYTE)(c))
#define GetGValue(c) ((BYTE)(((WORD)(c)) >> 8))
#define GetBValue(c) ((BYTE)((c) >> 16))
#define PALETTEINDEX(i) ((COLORREF)(0x01000000 | (DWORD)(WORD)(i)))
#define mmioFOURCC(a, b, c, d) ((DWORD)(BYTE)(a) | ((DWORD)(BYTE)(b) << 8) | ((DWORD)(BYTE)(c) << 16) | ((DWORD)(BYTE)(d) << 24))

#define MAKE_AVIERR(e) ((HRESULT)(0x80044000u + (e)))
#define FOURCC_RIFF mmioFOURCC('R', 'I', 'F', 'F')
#define FOURCC_LIST mmioFOURCC('L', 'I', 'S', 'T')

#define DECLARE_HANDLE(n) typedef uint32_t n
DECLARE_HANDLE(HWND);
DECLARE_HANDLE(HDC);
DECLARE_HANDLE(HINSTANCE);
DECLARE_HANDLE(HMENU);
DECLARE_HANDLE(HICON);
DECLARE_HANDLE(HBITMAP);
DECLARE_HANDLE(HBRUSH);
DECLARE_HANDLE(HFONT);
DECLARE_HANDLE(HPEN);
DECLARE_HANDLE(HPALETTE);
DECLARE_HANDLE(HRGN);
DECLARE_HANDLE(HKEY);
DECLARE_HANDLE(HHOOK);
DECLARE_HANDLE(HRSRC);
DECLARE_HANDLE(HMMIO);
DECLARE_HANDLE(HWAVEOUT);
DECLARE_HANDLE(HIC);
DECLARE_HANDLE(HGLRC);
typedef uint32_t HANDLE, HGDIOBJ, HGLOBAL, HLOCAL;
typedef HANDLE *LPHANDLE;
typedef HICON HCURSOR;
typedef HINSTANCE HMODULE;
typedef HKEY *PHKEY;
typedef HWAVEOUT *LPHWAVEOUT;
typedef int HFILE;
#define HFILE_ERROR ((HFILE)-1)

typedef LRESULT (*WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef LRESULT (*HOOKPROC)(int, WPARAM, LPARAM);
typedef void (*TIMERPROC)(HWND, UINT, UINT_PTR, DWORD);
typedef void (*LPTIMECALLBACK)(UINT, UINT, DWORD_PTR, DWORD_PTR, DWORD_PTR);
typedef INT_PTR (*FARPROC)(void);
typedef INT_PTR (*DLGPROC)(HWND, UINT, WPARAM, LPARAM);
typedef UINT_PTR (*LPOFNHOOKPROC)(HWND, UINT, WPARAM, LPARAM);
typedef LRESULT (*LPMMIOPROC)(LPSTR, UINT, LPARAM, LPARAM);

typedef struct tagRECT { LONG left, top, right, bottom; } RECT, *LPRECT, *PRECT;
typedef const RECT *LPCRECT;
typedef struct tagPOINT { LONG x, y; } POINT, *LPPOINT, *PPOINT;
typedef struct tagSIZE { LONG cx, cy; } SIZE, *LPSIZE, *PSIZE;

typedef struct tagMSG {
    HWND hwnd; UINT message; WPARAM wParam; LPARAM lParam; DWORD time; POINT pt;
} MSG, *LPMSG, *PMSG;

typedef struct tagPAINTSTRUCT {
    HDC hdc; BOOL fErase; RECT rcPaint; BOOL fRestore; BOOL fIncUpdate; BYTE rgbReserved[32];
} PAINTSTRUCT, *LPPAINTSTRUCT;

typedef struct tagWNDCLASSA {
    UINT style; WNDPROC lpfnWndProc; int cbClsExtra; int cbWndExtra; HINSTANCE hInstance; HICON hIcon;
    HCURSOR hCursor; HBRUSH hbrBackground; LPCSTR lpszMenuName; LPCSTR lpszClassName;
} WNDCLASSA, *LPWNDCLASSA;

typedef struct tagCREATESTRUCTA {
    LPVOID lpCreateParams; HINSTANCE hInstance; HMENU hMenu; HWND hwndParent; int cy, cx, y, x; LONG style;
    LPCSTR lpszName; LPCSTR lpszClass; DWORD dwExStyle;
} CREATESTRUCTA, *LPCREATESTRUCTA;

typedef struct tagWINDOWPOS {
    HWND hwnd; HWND hwndInsertAfter; int x, y, cx, cy; UINT flags;
} WINDOWPOS, *LPWINDOWPOS;

typedef struct tagSTYLESTRUCT { DWORD styleOld, styleNew; } STYLESTRUCT, *LPSTYLESTRUCT;
typedef struct tagSCROLLINFO { UINT cbSize, fMask; int nMin, nMax; UINT nPage; int nPos, nTrackPos; } SCROLLINFO, *LPSCROLLINFO;

typedef struct tagNCCALCSIZE_PARAMS { RECT rgrc[3]; WINDOWPOS *lppos; } NCCALCSIZE_PARAMS;
#define ISC_SHOWUIALL 0xC000000F

typedef struct tagMINMAXINFO {
    POINT ptReserved, ptMaxSize, ptMaxPosition, ptMinTrackSize, ptMaxTrackSize;
} MINMAXINFO, *LPMINMAXINFO;

typedef struct tagMENUITEMINFOA {
    UINT cbSize, fMask, fType, fState, wID; HMENU hSubMenu; HBITMAP hbmpChecked, hbmpUnchecked;
    ULONG_PTR dwItemData; LPSTR dwTypeData; UINT cch; HBITMAP hbmpItem;
} MENUITEMINFOA, *LPMENUITEMINFOA;

typedef struct tagRGBQUAD { BYTE rgbBlue, rgbGreen, rgbRed, rgbReserved; } RGBQUAD;
typedef struct tagBITMAPINFOHEADER {
    DWORD biSize; LONG biWidth; LONG biHeight; WORD biPlanes; WORD biBitCount; DWORD biCompression;
    DWORD biSizeImage; LONG biXPelsPerMeter; LONG biYPelsPerMeter; DWORD biClrUsed; DWORD biClrImportant;
} BITMAPINFOHEADER, *LPBITMAPINFOHEADER, *PBITMAPINFOHEADER;
typedef struct tagBITMAPINFO { BITMAPINFOHEADER bmiHeader; RGBQUAD bmiColors[1]; } BITMAPINFO, *LPBITMAPINFO;
#pragma pack(push, 2)
typedef struct tagBITMAPFILEHEADER {
    WORD bfType; DWORD bfSize; WORD bfReserved1, bfReserved2; DWORD bfOffBits;
} BITMAPFILEHEADER;
#pragma pack(pop)

typedef struct tagPALETTEENTRY { BYTE peRed, peGreen, peBlue, peFlags; } PALETTEENTRY, *LPPALETTEENTRY;
typedef struct tagLOGPALETTE { WORD palVersion; WORD palNumEntries; PALETTEENTRY palPalEntry[1]; } LOGPALETTE;

#define LF_FACESIZE 32
typedef struct tagLOGFONTA {
    LONG lfHeight, lfWidth, lfEscapement, lfOrientation, lfWeight;
    BYTE lfItalic, lfUnderline, lfStrikeOut, lfCharSet, lfOutPrecision, lfClipPrecision, lfQuality, lfPitchAndFamily;
    CHAR lfFaceName[LF_FACESIZE];
} LOGFONTA, *LPLOGFONTA;

typedef struct tagTEXTMETRICA {
    LONG tmHeight, tmAscent, tmDescent, tmInternalLeading, tmExternalLeading, tmAveCharWidth, tmMaxCharWidth;
    LONG tmWeight, tmOverhang, tmDigitizedAspectX, tmDigitizedAspectY;
    BYTE tmFirstChar, tmLastChar, tmDefaultChar, tmBreakChar, tmItalic, tmUnderlined, tmStruckOut;
    BYTE tmPitchAndFamily, tmCharSet;
} TEXTMETRICA, *LPTEXTMETRICA;
typedef int (*FONTENUMPROCA)(const LOGFONTA *, const TEXTMETRICA *, DWORD, LPARAM);

typedef struct tagOFNA {
    DWORD lStructSize; HWND hwndOwner; HINSTANCE hInstance; LPCSTR lpstrFilter; LPSTR lpstrCustomFilter;
    DWORD nMaxCustFilter; DWORD nFilterIndex; LPSTR lpstrFile; DWORD nMaxFile; LPSTR lpstrFileTitle;
    DWORD nMaxFileTitle; LPCSTR lpstrInitialDir; LPCSTR lpstrTitle; DWORD Flags; WORD nFileOffset;
    WORD nFileExtension; LPCSTR lpstrDefExt; LPARAM lCustData; LPOFNHOOKPROC lpfnHook; LPCSTR lpTemplateName;
} OPENFILENAMEA, *LPOPENFILENAMEA;

#define OFS_MAXPATHNAME 128
typedef struct _OFSTRUCT {
    BYTE cBytes; BYTE fFixedDisk; WORD nErrCode; WORD Reserved1; WORD Reserved2; CHAR szPathName[OFS_MAXPATHNAME];
} OFSTRUCT, *LPOFSTRUCT;

typedef struct _SYSTEMTIME {
    WORD wYear, wMonth, wDayOfWeek, wDay, wHour, wMinute, wSecond, wMilliseconds;
} SYSTEMTIME, *LPSYSTEMTIME;
typedef struct _FILETIME { DWORD dwLowDateTime, dwHighDateTime; } FILETIME;

#define MAX_PATH 260
typedef struct _WIN32_FIND_DATAA {
    DWORD dwFileAttributes; FILETIME ftCreationTime, ftLastAccessTime, ftLastWriteTime;
    DWORD nFileSizeHigh, nFileSizeLow, dwReserved0, dwReserved1; CHAR cFileName[MAX_PATH]; CHAR cAlternateFileName[14];
} WIN32_FIND_DATAA, *LPWIN32_FIND_DATAA;

typedef struct _cpinfo { UINT MaxCharSize; BYTE DefaultChar[2]; BYTE LeadByte[12]; } CPINFO, *LPCPINFO;

typedef struct _SECURITY_ATTRIBUTES { DWORD nLength; LPVOID lpSecurityDescriptor; BOOL bInheritHandle; }
    SECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;
typedef struct _OVERLAPPED { ULONG_PTR Internal, InternalHigh; DWORD Offset, OffsetHigh; HANDLE hEvent; }
    OVERLAPPED, *LPOVERLAPPED;

typedef struct _CRT_CRITICAL_SECTION { void *p[6]; } _CRT_CRITICAL_SECTION, CRITICAL_SECTION, *LPCRITICAL_SECTION;
typedef struct _CONTEXT { DWORD ContextFlags; BYTE rest[712]; } CONTEXT;
typedef struct _EXCEPTION_RECORD {
    DWORD ExceptionCode; DWORD ExceptionFlags; struct _EXCEPTION_RECORD *ExceptionRecord; PVOID ExceptionAddress;
    DWORD NumberParameters; ULONG_PTR ExceptionInformation[15];
} EXCEPTION_RECORD;
typedef struct _EXCEPTION_POINTERS { EXCEPTION_RECORD *ExceptionRecord; CONTEXT *ContextRecord; }
    EXCEPTION_POINTERS;

/* Multimedia. */
typedef struct _MMCKINFO { FOURCC ckid; DWORD cksize; FOURCC fccType; DWORD dwDataOffset; DWORD dwFlags; }
    MMCKINFO, *LPMMCKINFO;
typedef struct _MMIOINFO {
    DWORD dwFlags; FOURCC fccIOProc; LPMMIOPROC pIOProc; UINT wErrorRet; void *htask; LONG cchBuffer; HPSTR pchBuffer;
    HPSTR pchNext; HPSTR pchEndRead; HPSTR pchEndWrite; LONG lBufOffset; LONG lDiskOffset; DWORD adwInfo[3];
    DWORD dwReserved1, dwReserved2; HMMIO hmmio;
} MMIOINFO, *LPMMIOINFO;
typedef struct mmtime_tag {
    UINT wType;
    union { DWORD ms; DWORD sample; DWORD cb; DWORD ticks; struct { BYTE hour, min, sec, frame, fps, dummy, pad[2]; } smpte;
            struct { DWORD songptrpos; } midi; } u;
} MMTIME, *LPMMTIME;
typedef struct { DWORD_PTR dwCallback; MCIDEVICEID wDeviceID; LPCSTR lpstrDeviceType, lpstrElementName, lpstrAlias; }
    MCI_OPEN_PARMSA;
typedef struct { DWORD_PTR dwCallback; DWORD dwTimeFormat, dwAudio; } MCI_SET_PARMS;
typedef struct { DWORD_PTR dwCallback; DWORD_PTR dwReturn; DWORD dwItem, dwTrack; } MCI_STATUS_PARMS;
typedef struct { DWORD_PTR dwCallback; DWORD dwFrom, dwTo; } MCI_PLAY_PARMS;
typedef struct { DWORD_PTR dwCallback; DWORD dwTo; } MCI_SEEK_PARMS;
#pragma pack(push, 1)
typedef struct tWAVEFORMATEX {
    WORD wFormatTag; WORD nChannels; DWORD nSamplesPerSec; DWORD nAvgBytesPerSec; WORD nBlockAlign;
    WORD wBitsPerSample; WORD cbSize;
} WAVEFORMATEX, *LPWAVEFORMATEX;
#pragma pack(pop)
typedef const WAVEFORMATEX *LPCWAVEFORMATEX;
typedef struct wavehdr_tag {
    LPSTR lpData; DWORD dwBufferLength; DWORD dwBytesRecorded; DWORD_PTR dwUser; DWORD dwFlags; DWORD dwLoops;
    struct wavehdr_tag *lpNext; DWORD_PTR reserved;
} WAVEHDR, *LPWAVEHDR;
typedef struct tagWAVEOUTCAPSA {
    WORD wMid, wPid; UINT vDriverVersion; CHAR szPname[32]; DWORD dwFormats; WORD wChannels, wReserved1;
    DWORD dwSupport;
} WAVEOUTCAPSA, *LPWAVEOUTCAPSA;

/* COM, DirectDraw and AVI: the platform layer reports them unavailable. */
typedef struct _GUID { DWORD Data1; WORD Data2, Data3; BYTE Data4[8]; } GUID, IID, CLSID;
typedef GUID *LPGUID, *LPCLSID;
typedef const GUID *REFIID, *REFCLSID;
typedef struct IUnknown { struct { void *fn[3]; } *lpVtbl; } IUnknown, *LPUNKNOWN;
typedef struct IDirectDraw { void **lpVtbl; } IDirectDraw, *LPDIRECTDRAW;
typedef struct IDirectDrawSurface { void **lpVtbl; } IDirectDrawSurface, *LPDIRECTDRAWSURFACE;
typedef struct IDirectDrawPalette { void **lpVtbl; } IDirectDrawPalette, *LPDIRECTDRAWPALETTE;
typedef struct _DDCAPS { DWORD dwSize; BYTE rest[312]; } DDCAPS, *LPDDCAPS;
typedef uint32_t PAVIFILE;
typedef uint32_t PAVISTREAM;
typedef struct {
    DWORD dwFlags; BITMAPINFOHEADER *lpbiSrc; void *lpSrc; BITMAPINFOHEADER *lpbiDst; void *lpDst;
    int xDst, yDst, dxDst, dyDst, xSrc, ySrc, dxSrc, dySrc;
} ICDECOMPRESSEX;
typedef struct _AVISTREAMINFOA {
    DWORD fccType, fccHandler, dwFlags, dwCaps; WORD wPriority, wLanguage; DWORD dwScale, dwRate, dwStart, dwLength;
    DWORD dwInitialFrames, dwSuggestedBufferSize, dwQuality, dwSampleSize; RECT rcFrame; DWORD dwEditCount;
    DWORD dwFormatChangeCount; CHAR szName[64];
} AVISTREAMINFOA, *LPAVISTREAMINFOA;


#ifdef __cplusplus
extern "C" {
#endif
/* Not __stdcall, so not in win32_api.h. */
int wsprintfA(LPSTR buf, LPCSTR fmt, ...);
HWND MCIWndCreateA(HWND parent, HINSTANCE inst, DWORD style, LPCSTR file);
void Ordinal_17(void);         /* comctl32 InitCommonControls */
HBRUSH WINAPI GetSysColorBrush(int i);
DWORD WINAPI GetSysColor(int i);
WINBOOL WINAPI FindClose(HANDLE h);
WINBOOL WINAPI GetMessageA(LPMSG msg, HWND h, UINT lo, UINT hi);
HWND WINAPI GetCapture(void);
int WINAPI MulDiv(int a, int b, int c);
WINBOOL WINAPI PatBlt(HDC hd, int x, int y, int w, int h, DWORD rop);
int WINAPI GetWindowTextA(HWND h, LPSTR buf, int n);
WINBOOL WINAPI IsWindowEnabled(HWND h);
HWND WINAPI SetActiveWindow(HWND h);
void WINAPI PostQuitMessage(int code);

#ifdef __cplusplus
}
#endif
#endif
