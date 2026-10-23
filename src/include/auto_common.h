/*
 * Common prelude for the machine-translated tier (src/auto/).
 */
#ifndef CIV2_AUTO_COMMON_H
#define CIV2_AUTO_COMMON_H

/* Native builds: the Windows API is provided by src/platform/. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../platform/win32_api.h"

#include "ghidra.h"
/* The code was written for MSVC, whose `long` is 32-bit (the system headers
 * above keep their own meaning). */
#define long int
#include "civ2types.h"
#include "civ2classes.h"
#include "../data/gamedata.h"

/* new T[n] (MSVC): the element count is kept in the 4 bytes before the
 * array (vector deleting destructors read it back). */
#define VECTOR_COUNT(array) (((u32 *)(array))[-1])

/* Ghidra refers to Win32 structs by their tag names. */
typedef struct tagRECT tagRECT;
typedef struct tagPOINT tagPOINT;
typedef struct tagSIZE tagSIZE;
typedef struct tagMSG tagMSG;
typedef struct tagPAINTSTRUCT tagPAINTSTRUCT;
typedef struct tagTEXTMETRICA tagTEXTMETRICA;
typedef struct tagWNDCLASSA tagWNDCLASSA;
typedef struct tagLOGFONTA tagLOGFONTA;
typedef struct tagBITMAPINFO tagBITMAPINFO;
typedef struct tagBITMAPINFOHEADER tagBITMAPINFOHEADER;
typedef struct tagRGBQUAD tagRGBQUAD;
typedef struct tagPALETTEENTRY tagPALETTEENTRY;
typedef struct tagLOGPALETTE tagLOGPALETTE;
typedef struct tagOFNA tagOFNA;
typedef struct tagWINDOWPOS tagWINDOWPOS;
typedef struct tagMINMAXINFO tagMINMAXINFO;
typedef struct tagCREATESTRUCTA tagCREATESTRUCTA;
typedef struct tagMENUITEMINFOA tagMENUITEMINFOA;
typedef struct _MMIOINFO _MMIOINFO;
typedef struct _MMCKINFO _MMCKINFO;
typedef struct _OFSTRUCT _OFSTRUCT;
typedef struct _SYSTEMTIME _SYSTEMTIME;
typedef struct _WIN32_FIND_DATAA _WIN32_FIND_DATAA;
typedef struct _EXCEPTION_POINTERS _EXCEPTION_POINTERS;
typedef struct _CONTEXT _CONTEXT;
typedef struct mmtime_tag mmtime_tag;
#include "xdaemon.h"
#include "protos.h"
/* Calls through incremental-link thunks go straight to their targets. */
#include "thunks.h"
/* rand() calls name their caller for the rand trace (src/native/crt.c). */
int crt_rand_at(const char *caller);
#define _rand() crt_rand_at(__func__)

#endif
