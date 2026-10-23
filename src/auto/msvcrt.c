/* The game, the MSVC C runtime (compiled for the Windows build only, tools/build_recon.py): functions translated from the original
 * (tools/gen_c.py, now edited directly), in address order. */
#include "auto_common.h"

/* 005f1b80: written by hand in src/crt/startup.c */

/* 005f1c40 crt */
/* Library Function - Single Match
    _atexit
   
   Library: Visual Studio 1998 Debug */

int __cdecl _atexit(code *param_1)

{
  _onexit_t p_Var1;
  int iVar2;
  
  p_Var1 = __onexit((_onexit_t)param_1);
  if (p_Var1 == (_onexit_t)0x0) {
    iVar2 = -1;
  }
  else {
    iVar2 = 0;
  }
  return iVar2;
}

/* 005f1c70 crt */
#define DAT_006e6b54 (*(undefined4 * *)((u8 *)&g.d_006e6b54))
#define DAT_006e6b68 (*(undefined4 * *)((u8 *)&g.d_006e6b68))
/* Library Function - Single Match
    ___onexitinit
   
   Library: Visual Studio 1998 Debug */

void __cdecl ___onexitinit(void)

{
  DAT_006e6b68 = (undefined4 *)__malloc_dbg(0x80,2,"onexit.c",0xb6);
  if (DAT_006e6b68 == (undefined4 *)0x0) {
    __amsg_exit(0x18);
  }
  *DAT_006e6b68 = 0;
  DAT_006e6b54 = DAT_006e6b68;
  return;
}
#undef DAT_006e6b54
#undef DAT_006e6b68

/* 005f1cc8 crt */
/* Library Function - Single Match
    __global_unwind2
   
   Library: Visual Studio */

void __cdecl __global_unwind2(PVOID param_1)

{
  RtlUnwind(param_1,(PVOID)0x5f1ce0,(PEXCEPTION_RECORD)0x0,(PVOID)0x0);
  return;
}

/* 005f1d0a crt */
#define uStack_1c (*(undefined4 *)(frame_ + FRAME_OFF(4)))
#define puStack_18 (*(undefined1 * *)(frame_ + FRAME_OFF(8)))
#define local_14 (*(undefined4 *)(frame_ + FRAME_OFF(12)))
#define iStack_10 (*(int *)(frame_ + FRAME_OFF(16)))
/* Library Function - Single Match
    __local_unwind2
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release, Visual Studio 2003 Debug, Visual
   Studio 2003 Release */

void __cdecl __local_unwind2(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined1 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  iStack_10 = param_1;
  puStack_18 = &LAB_005f1ce8;
  while( true ) {
    iVar1 = *(int *)(param_1 + 8);
    iVar2 = *(int *)(param_1 + 0xc);
    if ((iVar2 == -1) || (iVar2 == param_2)) break;
    local_14 = *(undefined4 *)(iVar1 + iVar2 * 0xc);
    *(undefined4 *)(param_1 + 0xc) = local_14;
    if (*(int *)(iVar1 + 4 + iVar2 * 0xc) == 0) {
      FUN_005f1d9e(0x101);
      (**(code **)(iVar1 + 8 + iVar2 * 0xc))();
    }
  }
  return;
}
#undef uStack_1c
#undef puStack_18
#undef local_14
#undef iStack_10

/* 005f1d72 crt */
/* Library Function - Single Match
    __abnormal_termination
   
   Library: Visual Studio 1998 Debug */

int __cdecl __abnormal_termination(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  if ((*(undefined1 **)(iVar1 + 4) == &LAB_005f1ce8) &&
     (*(int *)(iVar1 + 8) == *(int *)(*(int *)(iVar1 + 0xc) + 0xc))) {
    iVar2 = 1;
  }
  return iVar2;
}

/* 005f1d95: written by hand in src/crt/eh.c */

/* 005f1d9e: written by hand in src/crt/eh.c */

/* 005f1dc0: written by hand in src/crt/eh.c */

/* 005f1e00: written by hand in src/crt/eh.c */

/* 005f1e10: written by hand in src/crt/eh.c */

/* 005f1e20: written by hand in src/crt/eh.c */

/* 005f1e30: written by hand in src/crt/eh.c */

/* 005f1e90: written by hand in src/crt/eh.c */

/* 005f1ed0 crt */
/* Library Function - Single Match
    ___CxxLongjmpUnwind@4
   
   Library: Visual Studio 1998 Debug */

void __stdcall ___CxxLongjmpUnwind_4(int param_1)

{
  ___FrameUnwindToState
            (*(undefined4 *)(param_1 + 0x18),0,*(undefined4 *)(param_1 + 0x28),
             *(undefined4 *)(param_1 + 0x1c));
  return;
}

/* 005f1f10: written by hand in src/crt/eh.c */

/* 005f1f80: written by hand in src/crt/eh.c */

/* 005f1fc0: written by hand in src/crt/eh.c */

/* 005f20a0: written by hand in src/crt/eh.c */

/* 005f2110: written by hand in src/crt/asm.c */

/* 005f2260 crt */
#define DAT_00639e50 (*(undefined4 *)((u8 *)&g.d_00639e50))
void __cdecl FUN_005f2260(undefined4 param_1)

{
  DAT_00639e50 = param_1;
  return;
}
#undef DAT_00639e50

/* 005f2280 crt */
#define DAT_00639e50 (*(uint *)((u8 *)&g.d_00639e50))
/* Library Function - Single Match
    _rand
   
   Library: Visual Studio 1998 Debug */

int __cdecl _rand(void)

{
  DAT_00639e50 = DAT_00639e50 * 0x343fd + 0x269ec3;
  return DAT_00639e50 >> 0x10 & 0x7fff;
}
#undef DAT_00639e50

/* 005f22d0 crt */
uint * __cdecl FUN_005f22d0(uint *param_1,uint *param_2)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  
  puVar4 = param_1;
  while (((uint)param_2 & 3) != 0) {
    bVar1 = (byte)*param_2;
    uVar3 = (uint)bVar1;
    param_2 = (uint *)((int)param_2 + 1);
    if (bVar1 == 0) goto LAB_005f23b8;
    *(byte *)puVar4 = bVar1;
    puVar4 = (uint *)((int)puVar4 + 1);
  }
  do {
    uVar2 = *param_2;
    uVar3 = *param_2;
    param_2 = param_2 + 1;
    if (((uVar2 ^ 0xffffffff ^ uVar2 + 0x7efefeff) & 0x81010100) != 0) {
      if ((char)uVar3 == '\0') {
LAB_005f23b8:
        *(byte *)puVar4 = (byte)uVar3;
        return param_1;
      }
      if ((char)(uVar3 >> 8) == '\0') {
        *(short *)puVar4 = (short)uVar3;
        return param_1;
      }
      if ((uVar3 & 0xff0000) == 0) {
        *(short *)puVar4 = (short)uVar3;
        *(byte *)((int)puVar4 + 2) = 0;
        return param_1;
      }
      if ((uVar3 & 0xff000000) == 0) {
        *puVar4 = uVar3;
        return param_1;
      }
    }
    *puVar4 = uVar3;
    puVar4 = puVar4 + 1;
  } while( true );
}

/* 005f22e0 crt */
uint * __cdecl FUN_005f22e0(uint *param_1,uint *param_2)

{
  byte bVar1;
  uint uVar2;
  uint *puVar3;
  uint uVar4;
  uint *puVar5;
  
  puVar3 = param_1;
  do {
    if (((uint)puVar3 & 3) == 0) goto LAB_005f22fc;
    uVar4 = *puVar3;
    puVar3 = (uint *)((int)puVar3 + 1);
  } while ((byte)uVar4 != 0);
  goto LAB_005f232f;
  while( true ) {
    if ((uVar4 & 0xff0000) == 0) {
      puVar5 = (uint *)((int)puVar5 + 2);
      goto joined_r0x005f234b;
    }
    if ((uVar4 & 0xff000000) == 0) break;
LAB_005f22fc:
    do {
      puVar5 = puVar3;
      puVar3 = puVar5 + 1;
    } while (((*puVar5 ^ 0xffffffff ^ *puVar5 + 0x7efefeff) & 0x81010100) == 0);
    uVar4 = *puVar5;
    if ((char)uVar4 == '\0') goto joined_r0x005f234b;
    if ((char)(uVar4 >> 8) == '\0') {
      puVar5 = (uint *)((int)puVar5 + 1);
      goto joined_r0x005f234b;
    }
  }
LAB_005f232f:
  puVar5 = (uint *)((int)puVar3 + -1);
joined_r0x005f234b:
  do {
    if (((uint)param_2 & 3) == 0) {
      do {
        uVar2 = *param_2;
        uVar4 = *param_2;
        param_2 = param_2 + 1;
        if (((uVar2 ^ 0xffffffff ^ uVar2 + 0x7efefeff) & 0x81010100) != 0) {
          if ((char)uVar4 == '\0') {
LAB_005f23b8:
            *(byte *)puVar5 = (byte)uVar4;
            return param_1;
          }
          if ((char)(uVar4 >> 8) == '\0') {
            *(short *)puVar5 = (short)uVar4;
            return param_1;
          }
          if ((uVar4 & 0xff0000) == 0) {
            *(short *)puVar5 = (short)uVar4;
            *(byte *)((int)puVar5 + 2) = 0;
            return param_1;
          }
          if ((uVar4 & 0xff000000) == 0) {
            *puVar5 = uVar4;
            return param_1;
          }
        }
        *puVar5 = uVar4;
        puVar5 = puVar5 + 1;
      } while( true );
    }
    bVar1 = (byte)*param_2;
    uVar4 = (uint)bVar1;
    param_2 = (uint *)((int)param_2 + 1);
    if (bVar1 == 0) goto LAB_005f23b8;
    *(byte *)puVar5 = bVar1;
    puVar5 = (uint *)((int)puVar5 + 1);
  } while( true );
}

/* 005f23c0: written by hand in src/crt/heap.c */

/* 005f2470 crt */
/* Library Function - Single Match
    void * __cdecl operator new(unsigned int)
   
   Library: Visual Studio 1998 Debug */

void * __cdecl operator_new(uint param_1)

{
  void *pvVar1;
  
  pvVar1 = __nh_malloc(param_1,1);
  return pvVar1;
}

/* 005f2490: written by hand in src/crt/vector_iter.c */

/* 005f2540: written by hand in src/crt/eh.c */

/* 005f25d0 crt */
/* Library Function - Multiple Matches With Different Base Names
    int __cdecl ArrayUnwindFilter(struct _EXCEPTION_POINTERS *)
    int __cdecl FrameUnwindFilter(struct _EXCEPTION_POINTERS *)
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl FUN_005f25d0(undefined4 *param_1)

{
  if (*(int *)*param_1 == -0x1f928c9d) {
    terminate();
  }
  return 0;
}

/* 005f2620: written by hand in src/crt/vector_iter.c */

/* 005f26e0 crt */
int __cdecl FUN_005f26e0(int param_1)

{
  return param_1 + -0x20;
}

/* 005f2700: written by hand in src/crt/locale.c */

/* 005f2840 crt */
/* Library Function - Single Match
    _isalpha
   
   Library: Visual Studio 1998 Debug */

int __cdecl _isalpha(int _C)

{
  uint uVar1;
  
  if (DAT_0063a29c < 2) {
    uVar1 = *(ushort *)(PTR_DAT_0063a090 + _C * 2) & 0x103;
  }
  else {
    uVar1 = __isctype(_C,0x103);
  }
  return uVar1;
}

/* 005f2890 crt */
/* Library Function - Single Match
    _isupper
   
   Library: Visual Studio 1998 Debug */

int __cdecl _isupper(int _C)

{
  uint uVar1;
  
  if (DAT_0063a29c < 2) {
    uVar1 = *(ushort *)(PTR_DAT_0063a090 + _C * 2) & 1;
  }
  else {
    uVar1 = __isctype(_C,1);
  }
  return uVar1;
}

/* 005f28e0 crt */
/* Library Function - Single Match
    _islower
   
   Library: Visual Studio 1998 Debug */

int __cdecl _islower(int _C)

{
  uint uVar1;
  
  if (DAT_0063a29c < 2) {
    uVar1 = *(ushort *)(PTR_DAT_0063a090 + _C * 2) & 2;
  }
  else {
    uVar1 = __isctype(_C,2);
  }
  return uVar1;
}

/* 005f2930 crt */
/* Library Function - Single Match
    _isdigit
   
   Library: Visual Studio 1998 Debug */

int __cdecl _isdigit(int _C)

{
  uint uVar1;
  
  if (DAT_0063a29c < 2) {
    uVar1 = *(ushort *)(PTR_DAT_0063a090 + _C * 2) & 4;
  }
  else {
    uVar1 = __isctype(_C,4);
  }
  return uVar1;
}

/* 005f2980 crt */
/* Library Function - Single Match
    _isxdigit
   
   Library: Visual Studio 1998 Debug */

int __cdecl _isxdigit(int _C)

{
  uint uVar1;
  
  if (DAT_0063a29c < 2) {
    uVar1 = *(ushort *)(PTR_DAT_0063a090 + _C * 2) & 0x80;
  }
  else {
    uVar1 = __isctype(_C,0x80);
  }
  return uVar1;
}

/* 005f29d0 crt */
/* Library Function - Single Match
    _isspace
   
   Library: Visual Studio 1998 Debug */

int __cdecl _isspace(int _C)

{
  uint uVar1;
  
  if (DAT_0063a29c < 2) {
    uVar1 = *(ushort *)(PTR_DAT_0063a090 + _C * 2) & 8;
  }
  else {
    uVar1 = __isctype(_C,8);
  }
  return uVar1;
}

/* 005f2a20 crt */
/* Library Function - Single Match
    _ispunct
   
   Library: Visual Studio 1998 Debug */

int __cdecl _ispunct(int _C)

{
  uint uVar1;
  
  if (DAT_0063a29c < 2) {
    uVar1 = *(ushort *)(PTR_DAT_0063a090 + _C * 2) & 0x10;
  }
  else {
    uVar1 = __isctype(_C,0x10);
  }
  return uVar1;
}

/* 005f2a70 crt */
/* Library Function - Single Match
    _isalnum
   
   Library: Visual Studio 1998 Debug */

int __cdecl _isalnum(int _C)

{
  uint uVar1;
  
  if (DAT_0063a29c < 2) {
    uVar1 = *(ushort *)(PTR_DAT_0063a090 + _C * 2) & 0x107;
  }
  else {
    uVar1 = __isctype(_C,0x107);
  }
  return uVar1;
}

/* 005f2ac0 crt */
/* Library Function - Single Match
    _isprint
   
   Library: Visual Studio 1998 Debug */

int __cdecl _isprint(int _C)

{
  uint uVar1;
  
  if (DAT_0063a29c < 2) {
    uVar1 = *(ushort *)(PTR_DAT_0063a090 + _C * 2) & 0x157;
  }
  else {
    uVar1 = __isctype(_C,0x157);
  }
  return uVar1;
}

/* 005f2b10 crt */
/* Library Function - Single Match
    _isgraph
   
   Library: Visual Studio 1998 Debug */

int __cdecl _isgraph(int _C)

{
  uint uVar1;
  
  if (DAT_0063a29c < 2) {
    uVar1 = *(ushort *)(PTR_DAT_0063a090 + _C * 2) & 0x117;
  }
  else {
    uVar1 = __isctype(_C,0x117);
  }
  return uVar1;
}

/* 005f2b60 crt */
/* Library Function - Single Match
    _iscntrl
   
   Library: Visual Studio 1998 Debug */

int __cdecl _iscntrl(int _C)

{
  uint uVar1;
  
  if (DAT_0063a29c < 2) {
    uVar1 = *(ushort *)(PTR_DAT_0063a090 + _C * 2) & 0x20;
  }
  else {
    uVar1 = __isctype(_C,0x20);
  }
  return uVar1;
}

/* 005f2bb0 crt */
/* Library Function - Single Match
    ___isascii
   
   Library: Visual Studio 1998 Debug */

int __cdecl ___isascii(int _C)

{
  return (uint)((uint)_C < 0x80);
}

/* 005f2be0 crt */
uint __cdecl FUN_005f2be0(uint param_1)

{
  return param_1 & 0x7f;
}

/* 005f2c00 crt */
#define local_8 (*(uint *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    ___iscsymf
   
   Library: Visual Studio 1998 Debug */

int __cdecl ___iscsymf(int _C)

{
  int iVar1;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (DAT_0063a29c < 2) {
    local_8 = *(ushort *)(PTR_DAT_0063a090 + _C * 2) & 0x103;
  }
  else {
    local_8 = __isctype(_C,0x103);
  }
  if ((local_8 == 0) && (_C != 0x5f)) {
    iVar1 = 0;
  }
  else {
    iVar1 = 1;
  }
  return iVar1;
}
#undef local_8

/* 005f2c80 crt */
#define local_8 (*(uint *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    ___iscsym
   
   Library: Visual Studio 1998 Debug */

int __cdecl ___iscsym(int _C)

{
  int iVar1;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (DAT_0063a29c < 2) {
    local_8 = *(ushort *)(PTR_DAT_0063a090 + _C * 2) & 0x107;
  }
  else {
    local_8 = __isctype(_C,0x107);
  }
  if ((local_8 == 0) && (_C != 0x5f)) {
    iVar1 = 0;
  }
  else {
    iVar1 = 1;
  }
  return iVar1;
}
#undef local_8

/* 005f2d00 crt */
/* Library Function - Single Match
    __fsopen
   
   Library: Visual Studio 1998 Debug */

FILE * __cdecl __fsopen(char *_Filename,char *_Mode,int _ShFlag)

{
  code *pcVar1;
  int iVar2;
  FILE *pFVar3;
  
  if (_Filename == (char *)0x0) {
    iVar2 = __CrtDbgReport(2,"fopen.c",0x35,0,"file != NULL");
    if (iVar2 == 1) {
      pcVar1 = (code *)swi(3);
      pFVar3 = (FILE *)(*pcVar1)();
      return pFVar3;
    }
  }
  if (*_Filename == '\0') {
    iVar2 = __CrtDbgReport(2,"fopen.c",0x36,0,"*file != _T(\'\\0\')");
    if (iVar2 == 1) {
      pcVar1 = (code *)swi(3);
      pFVar3 = (FILE *)(*pcVar1)();
      return pFVar3;
    }
  }
  if (_Mode == (char *)0x0) {
    iVar2 = __CrtDbgReport(2,"fopen.c",0x37,0,"mode != NULL");
    if (iVar2 == 1) {
      pcVar1 = (code *)swi(3);
      pFVar3 = (FILE *)(*pcVar1)();
      return pFVar3;
    }
  }
  if (*_Mode == '\0') {
    iVar2 = __CrtDbgReport(2,"fopen.c",0x38,0,"*mode != _T(\'\\0\')");
    if (iVar2 == 1) {
      pcVar1 = (code *)swi(3);
      pFVar3 = (FILE *)(*pcVar1)();
      return pFVar3;
    }
  }
  pFVar3 = __getstream();
  if (pFVar3 == (FILE *)0x0) {
    pFVar3 = (FILE *)0x0;
  }
  else {
    pFVar3 = __openfile(_Filename,_Mode,_ShFlag,pFVar3);
  }
  return pFVar3;
}

/* 005f2e10 crt */
/* Library Function - Single Match
    _fopen
   
   Library: Visual Studio 1998 Debug */

FILE * __cdecl _fopen(char *_Filename,char *_Mode)

{
  FILE *pFVar1;
  
  pFVar1 = __fsopen(_Filename,_Mode,0x40);
  return pFVar1;
}

/* 005f2e40 crt */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    _fclose
   
   Library: Visual Studio 1998 Debug */

int __cdecl _fclose(FILE *_File)

{
  code *pcVar1;
  int iVar2;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = -1;
  if ((_File->_flag & 0x40) == 0) {
    if (_File == (FILE *)0x0) {
      iVar2 = __CrtDbgReport(2,"fclose.c",0x77,0,"str != NULL");
      if (iVar2 == 1) {
        pcVar1 = (code *)swi(3);
        iVar2 = (*pcVar1)();
        return iVar2;
      }
    }
    if ((_File->_flag & 0x83) != 0) {
      local_8 = __flush(_File);
      __freebuf(_File);
      iVar2 = __close(_File->_file);
      if (iVar2 < 0) {
        local_8 = -1;
      }
      else if (_File->_tmpfname != (char *)0x0) {
        __free_dbg(_File->_tmpfname,2);
        _File->_tmpfname = (char *)0x0;
      }
    }
    _File->_flag = 0;
  }
  else {
    _File->_flag = 0;
    local_8 = -1;
  }
  return local_8;
}
#undef local_8

/* 005f2f30 crt */
/* Library Function - Single Match
    _strncpy
   
   Library: Visual Studio 1998 Debug */

char * __cdecl _strncpy(char *_Dest,char *_Source,size_t _Count)

{
  uint uVar1;
  uint uVar2;
  char cVar3;
  uint uVar4;
  uint *puVar5;
  
  if (_Count == 0) {
    return _Dest;
  }
  puVar5 = (uint *)_Dest;
  if (((uint)_Source & 3) != 0) {
    while( true ) {
      uVar4 = *(uint *)_Source;
      _Source = (char *)((int)_Source + 1);
      *(char *)puVar5 = (char)uVar4;
      puVar5 = (uint *)((int)puVar5 + 1);
      _Count = _Count - 1;
      if (_Count == 0) {
        return _Dest;
      }
      if ((char)uVar4 == '\0') break;
      if (((uint)_Source & 3) == 0) {
        uVar4 = _Count >> 2;
        goto joined_r0x005f2f6e;
      }
    }
    do {
      if (((uint)puVar5 & 3) == 0) {
        uVar4 = _Count >> 2;
        cVar3 = '\0';
        if (uVar4 == 0) goto LAB_005f2fab;
        goto LAB_005f3019;
      }
      *(char *)puVar5 = '\0';
      puVar5 = (uint *)((int)puVar5 + 1);
      _Count = _Count - 1;
    } while (_Count != 0);
    return _Dest;
  }
  uVar4 = _Count >> 2;
  if (uVar4 != 0) {
    do {
      uVar1 = *(uint *)_Source;
      uVar2 = *(uint *)_Source;
      _Source = (char *)((int)_Source + 4);
      if (((uVar1 ^ 0xffffffff ^ uVar1 + 0x7efefeff) & 0x81010100) != 0) {
        if ((char)uVar2 == '\0') {
          *puVar5 = 0;
joined_r0x005f3015:
          while( true ) {
            uVar4 = uVar4 - 1;
            puVar5 = puVar5 + 1;
            if (uVar4 == 0) break;
LAB_005f3019:
            *puVar5 = 0;
          }
          cVar3 = '\0';
          _Count = _Count & 3;
          if (_Count != 0) goto LAB_005f2fab;
          return _Dest;
        }
        if ((char)(uVar2 >> 8) == '\0') {
          *puVar5 = uVar2 & 0xff;
          goto joined_r0x005f3015;
        }
        if ((uVar2 & 0xff0000) == 0) {
          *puVar5 = uVar2 & 0xffff;
          goto joined_r0x005f3015;
        }
        if ((uVar2 & 0xff000000) == 0) {
          *puVar5 = uVar2;
          goto joined_r0x005f3015;
        }
      }
      *puVar5 = uVar2;
      puVar5 = puVar5 + 1;
      uVar4 = uVar4 - 1;
joined_r0x005f2f6e: ;
    } while (uVar4 != 0);
    _Count = _Count & 3;
    if (_Count == 0) {
      return _Dest;
    }
  }
  do {
    cVar3 = (char)*(uint *)_Source;
    _Source = (char *)((int)_Source + 1);
    *(char *)puVar5 = cVar3;
    puVar5 = (uint *)((int)puVar5 + 1);
    if (cVar3 == '\0') {
      while (_Count = _Count - 1, _Count != 0) {
LAB_005f2fab:
        *(char *)puVar5 = cVar3;
        puVar5 = (uint *)((int)puVar5 + 1);
      }
      return _Dest;
    }
    _Count = _Count - 1;
  } while (_Count != 0);
  return _Dest;
}

/* 005f3030: written by hand in src/crt/printf.c */

/* 005f3120 crt */
#define local_18 (*(uint *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(16)))
/* Library Function - Single Match
    _atol
   
   Library: Visual Studio 1998 Debug */

long __cdecl _atol(char *_Str)

{
  byte *pbVar1;
  uint uVar2;
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  while( true ) {
    if (DAT_0063a29c < 2) {
      local_14 = *(ushort *)(PTR_DAT_0063a090 + (uint)(byte)*_Str * 2) & 8;
    }
    else {
      local_14 = __isctype((uint)(byte)*_Str,8);
    }
    if (local_14 == 0) break;
    _Str = _Str + 1;
  }
  uVar2 = (uint)(byte)*_Str;
  if ((uVar2 == 0x2d) || (pbVar1 = (byte *)(_Str + 1), local_8 = uVar2, uVar2 == 0x2b)) {
    local_8 = (uint)(byte)_Str[1];
    pbVar1 = (byte *)(_Str + 2);
  }
  _Str = (char *)pbVar1;
  local_c = 0;
  while( true ) {
    if (DAT_0063a29c < 2) {
      local_18 = *(ushort *)(PTR_DAT_0063a090 + local_8 * 2) & 4;
    }
    else {
      local_18 = __isctype(local_8,4);
    }
    if (local_18 == 0) break;
    local_c = (local_8 - 0x30) + local_c * 10;
    local_8 = (uint)(byte)*_Str;
    _Str = _Str + 1;
  }
  if (uVar2 == 0x2d) {
    local_c = -local_c;
  }
  return local_c;
}
#undef local_18
#undef local_14
#undef local_c
#undef local_8

/* 005f3240 crt */
/* Library Function - Single Match
    _atoi
   
   Library: Visual Studio 1998 Debug */

int __cdecl _atoi(char *_Str)

{
  long lVar1;
  
  lVar1 = _atol(_Str);
  return lVar1;
}

/* 005f3260: written by hand in src/crt/conv.c */

/* 005f33b0 crt */
/* Library Function - Single Match
    _fputs
   
   Library: Visual Studio 1998 Debug */

int __cdecl _fputs(char *_Str,FILE *_File)

{
  code *pcVar1;
  int iVar2;
  size_t _Count;
  size_t sVar3;
  
  if (_Str == (char *)0x0) {
    iVar2 = __CrtDbgReport(2,"fputs.c",0x2f,0,"string != NULL");
    if (iVar2 == 1) {
      pcVar1 = (code *)swi(3);
      iVar2 = (*pcVar1)();
      return iVar2;
    }
  }
  if (_File == (FILE *)0x0) {
    iVar2 = __CrtDbgReport(2,"fputs.c",0x30,0,"stream != NULL");
    if (iVar2 == 1) {
      pcVar1 = (code *)swi(3);
      iVar2 = (*pcVar1)();
      return iVar2;
    }
  }
  _Count = _strlen(_Str);
  iVar2 = __stbuf(_File);
  sVar3 = _fwrite(_Str,1,_Count,_File);
  __ftbuf(iVar2,_File);
  if (sVar3 == _Count) {
    iVar2 = 0;
  }
  else {
    iVar2 = -1;
  }
  return iVar2;
}

/* 005f3480 crt */
/* Library Function - Single Match
    _strlen
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

size_t __cdecl _strlen(char *_Str)

{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  
  puVar2 = (uint *)_Str;
  do {
    if (((uint)puVar2 & 3) == 0) goto LAB_005f34a0;
    uVar1 = *puVar2;
    puVar2 = (uint *)((int)puVar2 + 1);
  } while ((char)uVar1 != '\0');
LAB_005f34d3:
  return (size_t)((int)puVar2 + (-1 - (int)_Str));
LAB_005f34a0:
  do {
    do {
      puVar3 = puVar2;
      puVar2 = puVar3 + 1;
    } while (((*puVar3 ^ 0xffffffff ^ *puVar3 + 0x7efefeff) & 0x81010100) == 0);
    uVar1 = *puVar3;
    if ((char)uVar1 == '\0') {
      return (int)puVar3 - (int)_Str;
    }
    if ((char)(uVar1 >> 8) == '\0') {
      return (size_t)((int)puVar3 + (1 - (int)_Str));
    }
    if ((uVar1 & 0xff0000) == 0) {
      return (size_t)((int)puVar3 + (2 - (int)_Str));
    }
  } while ((uVar1 & 0xff000000) != 0);
  goto LAB_005f34d3;
}

/* 005f3500 crt */
/* Library Function - Single Match
    _memset
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

void * __cdecl _memset(void *_Dst,int _Val,size_t _Size)

{
  uint uVar1;
  uint uVar2;
  size_t sVar3;
  uint *puVar4;
  
  if (_Size == 0) {
    return _Dst;
  }
  uVar1 = _Val & 0xff;
  puVar4 = _Dst;
  if (3 < _Size) {
    uVar2 = -(int)_Dst & 3;
    sVar3 = _Size;
    if (uVar2 != 0) {
      sVar3 = _Size - uVar2;
      do {
        *(undefined1 *)puVar4 = (undefined1)_Val;
        puVar4 = (uint *)((int)puVar4 + 1);
        uVar2 = uVar2 - 1;
      } while (uVar2 != 0);
    }
    uVar1 = uVar1 * 0x1010101;
    _Size = sVar3 & 3;
    uVar2 = sVar3 >> 2;
    if (uVar2 != 0) {
      for (; uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar4 = uVar1;
        puVar4 = puVar4 + 1;
      }
      if (_Size == 0) {
        return _Dst;
      }
    }
  }
  do {
    *(char *)puVar4 = (char)uVar1;
    puVar4 = (uint *)((int)puVar4 + 1);
    _Size = _Size - 1;
  } while (_Size != 0);
  return _Dst;
}

/* 005f3560 crt */
/* Library Function - Single Match
    _strcmp
   
   Library: Visual Studio 1998 Debug */

int __cdecl _strcmp(char *_Str1,char *_Str2)

{
  undefined2 uVar1;
  undefined4 uVar2;
  byte bVar3;
  byte bVar4;
  bool bVar5;
  
  if (((uint)_Str1 & 3) != 0) {
    if (((uint)_Str1 & 1) != 0) {
      bVar4 = *_Str1;
      _Str1 = _Str1 + 1;
      bVar5 = bVar4 < (byte)*_Str2;
      if (bVar4 != *_Str2) goto LAB_005f35a4;
      _Str2 = _Str2 + 1;
      if (bVar4 == 0) {
        return 0;
      }
      if (((uint)_Str1 & 2) == 0) goto LAB_005f3570;
    }
    uVar1 = *(undefined2 *)_Str1;
    _Str1 = _Str1 + 2;
    bVar4 = (byte)uVar1;
    bVar5 = bVar4 < (byte)*_Str2;
    if (bVar4 != *_Str2) goto LAB_005f35a4;
    if (bVar4 == 0) {
      return 0;
    }
    bVar4 = (byte)((ushort)uVar1 >> 8);
    bVar5 = bVar4 < (byte)_Str2[1];
    if (bVar4 != _Str2[1]) goto LAB_005f35a4;
    if (bVar4 == 0) {
      return 0;
    }
    _Str2 = _Str2 + 2;
  }
LAB_005f3570:
  while( true ) {
    uVar2 = *(undefined4 *)_Str1;
    bVar4 = (byte)uVar2;
    bVar5 = bVar4 < (byte)*_Str2;
    if (bVar4 != *_Str2) break;
    if (bVar4 == 0) {
      return 0;
    }
    bVar4 = (byte)((uint)uVar2 >> 8);
    bVar5 = bVar4 < (byte)_Str2[1];
    if (bVar4 != _Str2[1]) break;
    if (bVar4 == 0) {
      return 0;
    }
    bVar4 = (byte)((uint)uVar2 >> 0x10);
    bVar5 = bVar4 < (byte)_Str2[2];
    if (bVar4 != _Str2[2]) break;
    bVar3 = (byte)((uint)uVar2 >> 0x18);
    if (bVar4 == 0) {
      return 0;
    }
    bVar5 = bVar3 < (byte)_Str2[3];
    if (bVar3 != _Str2[3]) break;
    _Str2 = _Str2 + 4;
    _Str1 = _Str1 + 4;
    if (bVar3 == 0) {
      return 0;
    }
  }
LAB_005f35a4:
  return (uint)bVar5 * -2 + 1;
}

/* 005f35f0: written by hand in src/crt/asm.c */

/* 005f3630 crt */
/* Library Function - Single Match
    _strchr
   
   Library: Visual Studio 1998 Debug */

char * __cdecl _strchr(char *_Str,int _Val)

{
  uint uVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  
  while (((uint)_Str & 3) != 0) {
    uVar1 = *(uint *)_Str;
    if ((char)uVar1 == (char)_Val) {
      return (char *)(uint *)_Str;
    }
    _Str = (char *)((int)_Str + 1);
    if ((char)uVar1 == '\0') {
      return (char *)0x0;
    }
  }
  while( true ) {
    while( true ) {
      uVar1 = *(uint *)_Str;
      uVar4 = uVar1 ^ CONCAT22(CONCAT11((char)_Val,(char)_Val),CONCAT11((char)_Val,(char)_Val));
      uVar3 = uVar1 ^ 0xffffffff ^ uVar1 + 0x7efefeff;
      puVar5 = (uint *)((int)_Str + 4);
      if (((uVar4 ^ 0xffffffff ^ uVar4 + 0x7efefeff) & 0x81010100) != 0) break;
      _Str = (char *)puVar5;
      if ((uVar3 & 0x81010100) != 0) {
        if ((uVar3 & 0x1010100) != 0) {
          return (char *)0x0;
        }
        if ((uVar1 + 0x7efefeff & 0x80000000) == 0) {
          return (char *)0x0;
        }
      }
    }
    uVar1 = *(uint *)_Str;
    if ((char)uVar1 == (char)_Val) {
      return (char *)(uint *)_Str;
    }
    if ((char)uVar1 == '\0') {
      return (char *)0x0;
    }
    cVar2 = (char)(uVar1 >> 8);
    if (cVar2 == (char)_Val) {
      return (char *)((int)_Str + 1);
    }
    if (cVar2 == '\0') {
      return (char *)0x0;
    }
    cVar2 = (char)(uVar1 >> 0x10);
    if (cVar2 == (char)_Val) {
      return (char *)((int)_Str + 2);
    }
    if (cVar2 == '\0') break;
    cVar2 = (char)(uVar1 >> 0x18);
    if (cVar2 == (char)_Val) {
      return (char *)((int)_Str + 3);
    }
    _Str = (char *)puVar5;
    if (cVar2 == '\0') {
      return (char *)0x0;
    }
  }
  return (char *)0x0;
}

/* 005f36f0 crt */
/* Library Function - Single Match
    _strncmp
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

int __cdecl _strncmp(char *_Str1,char *_Str2,size_t _MaxCount)

{
  char cVar1;
  char cVar2;
  size_t sVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  
  uVar5 = 0;
  sVar3 = _MaxCount;
  pcVar6 = _Str1;
  if (_MaxCount != 0) {
    do {
      if (sVar3 == 0) break;
      sVar3 = sVar3 - 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    iVar4 = _MaxCount - sVar3;
    do {
      pcVar6 = _Str2;
      pcVar7 = _Str1;
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      pcVar7 = _Str1 + 1;
      pcVar6 = _Str2 + 1;
      cVar2 = *_Str1;
      cVar1 = *_Str2;
      _Str2 = pcVar6;
      _Str1 = pcVar7;
    } while (cVar1 == cVar2);
    uVar5 = 0;
    if ((byte)pcVar6[-1] <= (byte)pcVar7[-1]) {
      if (pcVar6[-1] == pcVar7[-1]) {
        return 0;
      }
      uVar5 = 0xfffffffe;
    }
    uVar5 = ~uVar5;
  }
  return uVar5;
}

/* 005f3730 crt */
#define local_20 (*(uint *)(frame_ + FRAME_OFF(0)))
#define local_1c (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(uint *)(frame_ + FRAME_OFF(16)))
#define local_c (*(undefined1 * *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(undefined1 *)(frame_ + FRAME_OFF(24)))
/* Library Function - Single Match
    _fread
   
   Library: Visual Studio 1998 Debug */

size_t __cdecl _fread(void *_DstBuf,size_t _ElementSize,size_t _Count,FILE *_File)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined1 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = _DstBuf;
  uVar1 = _Count * _ElementSize;
  if (uVar1 == 0) {
    _Count = 0;
  }
  else {
    local_10 = uVar1;
    if ((_File->_flag & 0x10cU) == 0) {
      local_20 = 0x1000;
    }
    else {
      local_20 = _File->_bufsiz;
    }
    while (local_10 != 0) {
      if (((_File->_flag & 0x10cU) == 0) || (_File->_cnt == 0)) {
        if (local_10 < local_20) {
          iVar3 = __filbuf(_File);
          if (iVar3 == -1) {
            return (uVar1 - local_10) / _ElementSize;
          }
          local_8 = (undefined1)iVar3;
          *local_c = local_8;
          local_c = local_c + 1;
          local_10 = local_10 - 1;
          local_20 = _File->_bufsiz;
        }
        else {
          if (local_20 == 0) {
            local_1c = local_10;
          }
          else {
            local_1c = local_10 - local_10 % local_20;
          }
          iVar3 = __read(_File->_file,local_c,local_1c);
          if (iVar3 == 0) {
            _File->_flag = _File->_flag | 0x10;
            return (uVar1 - local_10) / _ElementSize;
          }
          if (iVar3 == -1) {
            _File->_flag = _File->_flag | 0x20;
            return (uVar1 - local_10) / _ElementSize;
          }
          local_10 = local_10 - iVar3;
          local_c = local_c + iVar3;
        }
      }
      else {
        uVar2 = _File->_cnt;
        if (local_10 <= (uint)_File->_cnt) {
          uVar2 = local_10;
        }
        FUN_005f2110(local_c,_File->_ptr,uVar2);
        local_10 = local_10 - uVar2;
        _File->_cnt = _File->_cnt - uVar2;
        _File->_ptr = _File->_ptr + uVar2;
        local_c = local_c + uVar2;
      }
    }
  }
  return _Count;
}
#undef local_20
#undef local_1c
#undef local_10
#undef local_c
#undef local_8

/* 005f3900 crt */
#define local_20 (*(uint *)(frame_ + FRAME_OFF(0)))
#define local_1c (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(uint *)(frame_ + FRAME_OFF(16)))
#define local_c (*(char * *)(frame_ + FRAME_OFF(20)))
/* Library Function - Single Match
    _fwrite
   
   Library: Visual Studio 1998 Debug */

size_t __cdecl _fwrite(void *_Str,size_t _Size,size_t _Count,FILE *_File)

{
  uint uVar1;
  size_t sVar2;
  int iVar3;
  uint uVar4;
  undefined1 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = _Str;
  uVar1 = _Count * _Size;
  if (uVar1 == 0) {
    sVar2 = 0;
  }
  else {
    local_10 = uVar1;
    if ((_File->_flag & 0x10cU) == 0) {
      local_20 = 0x1000;
    }
    else {
      local_20 = _File->_bufsiz;
    }
    do {
      while( true ) {
        while( true ) {
          if (local_10 == 0) {
            return _Count;
          }
          if (((_File->_flag & 0x108U) == 0) || (_File->_cnt == 0)) break;
          uVar4 = _File->_cnt;
          if (local_10 <= (uint)_File->_cnt) {
            uVar4 = local_10;
          }
          FUN_005f2110(_File->_ptr,local_c,uVar4);
          local_10 = local_10 - uVar4;
          _File->_cnt = _File->_cnt - uVar4;
          _File->_ptr = _File->_ptr + uVar4;
          local_c = local_c + uVar4;
        }
        if (local_20 <= local_10) break;
        iVar3 = __flsbuf((int)*local_c,_File);
        if (iVar3 == -1) {
          return (uVar1 - local_10) / _Size;
        }
        local_c = local_c + 1;
        local_10 = local_10 - 1;
        if (_File->_bufsiz < 1) {
          local_20 = 1;
        }
        else {
          local_20 = _File->_bufsiz;
        }
      }
      if (((_File->_flag & 0x108U) != 0) && (iVar3 = __flush(_File), iVar3 != 0)) {
        return (uVar1 - local_10) / _Size;
      }
      if (local_20 == 0) {
        local_1c = local_10;
      }
      else {
        local_1c = local_10 - local_10 % local_20;
      }
      uVar4 = __write(_File->_file,local_c,local_1c);
      if (uVar4 == 0xffffffff) {
        _File->_flag = _File->_flag | 0x20;
        return (uVar1 - local_10) / _Size;
      }
      local_10 = local_10 - uVar4;
      local_c = local_c + uVar4;
    } while (local_1c <= uVar4);
    _File->_flag = _File->_flag | 0x20;
    sVar2 = (uVar1 - local_10) / _Size;
  }
  return sVar2;
}
#undef local_20
#undef local_1c
#undef local_10
#undef local_c

/* 005f3b20 crt */
#define local_110 (*(CHAR *)(frame_ + FRAME_OFF(0)))
#define local_10f (*(undefined1 *)(frame_ + FRAME_OFF(1)))
#define local_10e (*(undefined1 *)(frame_ + FRAME_OFF(2)))
#define local_10d (*(undefined1 *)(frame_ + FRAME_OFF(3)))
#define local_10c (*(byte *)(frame_ + FRAME_OFF(4)))
#define local_10b (*(byte *)(frame_ + FRAME_OFF(5)))
/* Library Function - Single Match
    __chdir
   
   Library: Visual Studio 1998 Debug */

int __cdecl __chdir(char *_Path)

{
  BOOL BVar1;
  DWORD DVar2;
  uint uVar3;
  undefined1 frame_[FRAME_OFF(272)] __attribute__((aligned(8)));  /* original stack frame */
  
  BVar1 = SetCurrentDirectoryA(_Path);
  if ((BVar1 != 0) && (DVar2 = GetCurrentDirectoryA(0x105,(LPSTR)&local_10c), DVar2 != 0)) {
    if (((local_10c == 0x5c) || (local_10c == 0x2f)) && (local_10c == local_10b)) {
      return 0;
    }
    local_110 = '=';
    uVar3 = __mbctoupper((uint)local_10c);
    local_10f = (undefined1)uVar3;
    local_10e = 0x3a;
    local_10d = 0;
    BVar1 = SetEnvironmentVariableA(&local_110,(LPCSTR)&local_10c);
    if (BVar1 != 0) {
      return 0;
    }
  }
  DVar2 = GetLastError();
  __dosmaperr(DVar2);
  return -1;
}
#undef local_110
#undef local_10f
#undef local_10e
#undef local_10d
#undef local_10c
#undef local_10b

/* 005f3c10 crt */
/* Library Function - Single Match
    _strrchr
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

char * __cdecl _strrchr(char *_Str,int _Ch)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  
  iVar2 = -1;
  do {
    pcVar4 = _Str;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar4 = _Str + 1;
    cVar1 = *_Str;
    _Str = pcVar4;
  } while (cVar1 != '\0');
  iVar2 = -(iVar2 + 1);
  pcVar4 = pcVar4 + -1;
  do {
    pcVar3 = pcVar4;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar3 = pcVar4 + -1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar3;
  } while ((char)_Ch != cVar1);
  pcVar3 = pcVar3 + 1;
  if (*pcVar3 != (char)_Ch) {
    pcVar3 = (char *)0x0;
  }
  return pcVar3;
}

/* 005f3c40 crt */
#define local_10 (*(uint *)(frame_ + FRAME_OFF(0)))
#define local_c (*(char * *)(frame_ + FRAME_OFF(4)))
/* Library Function - Single Match
    _fgets
   
   Library: Visual Studio 1998 Debug */

char * __cdecl _fgets(char *_Buf,int _MaxCount,FILE *_File)

{
  char cVar1;
  code *pcVar2;
  int iVar3;
  char *pcVar4;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = _Buf;
  if ((_Buf == (char *)0x0) &&
     (iVar3 = __CrtDbgReport(2,"fgets.c",0x3b,0,"string != NULL"), iVar3 == 1)) {
    pcVar2 = (code *)swi(3);
    pcVar4 = (char *)(*pcVar2)();
    return pcVar4;
  }
  if ((_File == (FILE *)0x0) &&
     (iVar3 = __CrtDbgReport(2,"fgets.c",0x3c,0,"str != NULL"), iVar3 == 1)) {
    pcVar2 = (code *)swi(3);
    pcVar4 = (char *)(*pcVar2)();
    return pcVar4;
  }
  if (_MaxCount < 1) {
    _Buf = (char *)0x0;
  }
  else {
    do {
      _MaxCount = _MaxCount + -1;
      if (_MaxCount == 0) break;
      local_10 = CRT_GETC(_File);
      if (local_10 == 0xffffffff) {
        if (_Buf == local_c) {
          return (char *)0x0;
        }
        break;
      }
      pcVar4 = local_c + 1;
      *local_c = (char)local_10;
      cVar1 = *local_c;
      local_c = pcVar4;
    } while (cVar1 != '\n');
    *local_c = '\0';
  }
  return _Buf;
}
#undef local_10
#undef local_c

/* 005f3d70 crt */
#define DAT_006e69f0 (*(undefined4 *)((u8 *)&g.d_006e69f0))
#define local_c (*(undefined * *)(frame_ + FRAME_OFF(4)))
/* Library Function - Single Match
    __filbuf
   
   Library: Visual Studio 1998 Debug */

int __cdecl __filbuf(FILE *_File)

{
  byte *pbVar1;
  code *pcVar2;
  int iVar3;
  uint uVar4;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (_File == (FILE *)0x0) {
    iVar3 = __CrtDbgReport(2,"_filbuf.c",0x69,0,"str != NULL");
    if (iVar3 == 1) {
      pcVar2 = (code *)swi(3);
      iVar3 = (*pcVar2)();
      return iVar3;
    }
  }
  if (((_File->_flag & 0x83) == 0) || ((_File->_flag & 0x40) != 0)) {
    uVar4 = 0xffffffff;
  }
  else if ((_File->_flag & 2) == 0) {
    _File->_flag = _File->_flag | 1;
    if ((_File->_flag & 0x10cU) == 0) {
      __getbuf(_File);
    }
    else {
      _File->_ptr = _File->_base;
    }
    iVar3 = __read(_File->_file,_File->_base,_File->_bufsiz);
    _File->_cnt = iVar3;
    if ((_File->_cnt == 0) || (_File->_cnt == -1)) {
      if (_File->_cnt == 0) {
        _File->_flag = _File->_flag | 0x10;
      }
      else {
        _File->_flag = _File->_flag | 0x20;
      }
      _File->_cnt = 0;
      uVar4 = 0xffffffff;
    }
    else {
      if ((_File->_flag & 0x82) == 0) {
        if (_File->_file == -1) {
          local_c = &DAT_0063a420;
        }
        else {
          local_c = (undefined *)
                    (*(int *)((int)&DAT_006e69f0 + ((int)(_File->_file & 0xffffffe0U) >> 3)) +
                    (_File->_file & 0x1fU) * 8);
        }
        if ((local_c[4] & 0x82) == 0x82) {
          _File->_flag = _File->_flag | 0x2000;
        }
      }
      if (((_File->_bufsiz == 0x200) && ((_File->_flag & 8) != 0)) && ((_File->_flag & 0x400) == 0))
      {
        _File->_bufsiz = 0x1000;
      }
      _File->_cnt = _File->_cnt + -1;
      pbVar1 = (byte *)_File->_ptr;
      _File->_ptr = _File->_ptr + 1;
      uVar4 = (uint)*pbVar1;
    }
  }
  else {
    _File->_flag = _File->_flag | 0x20;
    uVar4 = 0xffffffff;
  }
  return uVar4;
}
#undef DAT_006e69f0
#undef local_c

/* 005f3f50 crt */
#define local_c (*(uint *)(frame_ + FRAME_OFF(4)))
/* Library Function - Single Match
    _fputc
   
   Library: Visual Studio 1998 Debug */

int __cdecl _fputc(int _Ch,FILE *_File)

{
  code *pcVar1;
  int iVar2;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (_File == (FILE *)0x0) {
    iVar2 = __CrtDbgReport(2,"fputc.c",0x2d,0,"str != NULL");
    if (iVar2 == 1) {
      pcVar1 = (code *)swi(3);
      iVar2 = (*pcVar1)();
      return iVar2;
    }
  }
  _File->_cnt = _File->_cnt + -1;
  if (_File->_cnt < 0) {
    local_c = __flsbuf(_Ch,_File);
  }
  else {
    *_File->_ptr = (char)_Ch;
    local_c = (uint)(byte)*_File->_ptr;
    _File->_ptr = _File->_ptr + 1;
  }
  return local_c;
}
#undef local_c

/* 005f3ff0 crt */
/* Library Function - Single Match
    _putc
   
   Library: Visual Studio 1998 Debug */

int __cdecl _putc(int _Ch,FILE *_File)

{
  int iVar1;
  
  iVar1 = _fputc(_Ch,_File);
  return iVar1;
}

/* 005f4010 crt */
#define local_8 (*(uint *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    _fgetc
   
   Library: Visual Studio 1998 Debug */

int __cdecl _fgetc(FILE *_File)

{
  code *pcVar1;
  int iVar2;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (_File == (FILE *)0x0) {
    iVar2 = __CrtDbgReport(2,"fgetc.c",0x29,0,"stream != NULL");
    if (iVar2 == 1) {
      pcVar1 = (code *)swi(3);
      iVar2 = (*pcVar1)();
      return iVar2;
    }
  }
  local_8 = CRT_GETC(_File);
  return local_8;
}
#undef local_8

/* 005f4090 crt */
/* Library Function - Single Match
    _getc
   
   Library: Visual Studio 1998 Debug */

int __cdecl _getc(FILE *_File)

{
  int iVar1;
  
  iVar1 = _fgetc(_File);
  return iVar1;
}

/* 005f40b0 crt */
#define DAT_0063a078 (*(int *)((u8 *)&g.d_0063a078))
/* Library Function - Single Match
    __strnicmp
   
   Library: Visual Studio 1998 Debug */

int __cdecl __strnicmp(char *_Str1,char *_Str2,size_t _MaxCount)

{
  char cVar1;
  byte bVar2;
  ushort uVar3;
  uint _C;
  int iVar4;
  uint uVar5;
  bool bVar6;
  
  iVar4 = 0;
  if (_MaxCount != 0) {
    if (DAT_0063a078 == 0) {
      do {
        bVar2 = *_Str1;
        cVar1 = *_Str2;
        uVar3 = CONCAT11(bVar2,cVar1);
        if (bVar2 == 0) break;
        uVar3 = CONCAT11(bVar2,cVar1);
        uVar5 = (uint)uVar3;
        if (cVar1 == '\0') break;
        _Str1 = _Str1 + 1;
        _Str2 = _Str2 + 1;
        if ((0x40 < bVar2) && (bVar2 < 0x5b)) {
          uVar5 = (uint)CONCAT11(bVar2 + 0x20,cVar1);
        }
        uVar3 = (ushort)uVar5;
        bVar2 = (byte)uVar5;
        if ((0x40 < bVar2) && (bVar2 < 0x5b)) {
          uVar3 = (ushort)CONCAT31((int3)(uVar5 >> 8),bVar2 + 0x20);
        }
        bVar2 = (byte)(uVar3 >> 8);
        bVar6 = bVar2 < (byte)uVar3;
        if (bVar2 != (byte)uVar3) goto LAB_005f410b;
        _MaxCount = _MaxCount - 1;
      } while (_MaxCount != 0);
      iVar4 = 0;
      bVar2 = (byte)(uVar3 >> 8);
      bVar6 = bVar2 < (byte)uVar3;
      if (bVar2 != (byte)uVar3) {
LAB_005f410b:
        iVar4 = -1;
        if (!bVar6) {
          iVar4 = 1;
        }
      }
    }
    else {
      uVar5 = 0;
      _C = 0;
      do {
        _C = CONCAT31((int3)(_C >> 8),*_Str1);
        uVar5 = CONCAT31((int3)(uVar5 >> 8),*_Str2);
        if ((_C == 0) || (uVar5 == 0)) break;
        _Str1 = _Str1 + 1;
        _Str2 = _Str2 + 1;
        uVar5 = _tolower(uVar5);
        _C = _tolower(_C);
        bVar6 = _C < uVar5;
        if (_C != uVar5) goto LAB_005f414d;
        _MaxCount = _MaxCount - 1;
      } while (_MaxCount != 0);
      iVar4 = 0;
      bVar6 = _C < uVar5;
      if (_C != uVar5) {
LAB_005f414d:
        iVar4 = -1;
        if (!bVar6) {
          iVar4 = 1;
        }
      }
    }
  }
  return iVar4;
}
#undef DAT_0063a078

/* 005f4160: written by hand in src/crt/startup.c */

/* 005f41b0 crt */
/* Library Function - Single Match
    _exit
   
   Library: Visual Studio 1998 Debug */

void __cdecl _exit(int _Code)

{
  doexit(_Code,0,0);
  return;
}

/* 005f41d0 crt */
/* Library Function - Single Match
    __exit
   
   Library: Visual Studio 1998 Debug */

void __cdecl __exit(undefined4 param_1)

{
  doexit(param_1,1,0);
  return;
}

/* 005f41f0 crt */
/* Library Function - Single Match
    __cexit
   
   Library: Visual Studio 1998 Debug */

void __cdecl __cexit(void)

{
  doexit(0,0,1);
  return;
}

/* 005f4210 crt */
/* Library Function - Single Match
    __c_exit
   
   Library: Visual Studio 1998 Debug */

void __cdecl __c_exit(void)

{
  doexit(0,1,1);
  return;
}

/* 005f4230 crt */
#define DAT_00639f54 (*(undefined1 *)((u8 *)&g.d_00639f54))
#define DAT_006e6b54 (*(int * *)((u8 *)&g.d_006e6b54))
#define DAT_006e6b68 (*(int * *)((u8 *)&g.d_006e6b68))
#define _DAT_00639f58 (*(undefined4 *)((u8 *)&g.d_00639f58))
#define local_8 (*(int * *)(frame_ + FRAME_OFF(0)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    _doexit
   
   Library: Visual Studio 1998 Debug */

void __cdecl doexit(UINT param_1,int param_2,int param_3)

{
  byte bVar1;
  HANDLE hProcess;
  UINT uExitCode;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (DAT_00639f5c == 1) {
    uExitCode = param_1;
    hProcess = GetCurrentProcess();
    TerminateProcess(hProcess,uExitCode);
  }
  _DAT_00639f58 = 1;
  DAT_00639f54 = (undefined1)param_3;
  if (param_2 == 0) {
    if (DAT_006e6b68 != (int *)0x0) {
      local_8 = DAT_006e6b54;
      while (local_8 = local_8 + -1, DAT_006e6b68 <= local_8) {
        if (*local_8 != 0) {
          (*(code *)*local_8)();
        }
      }
    }
    __initterm(&DAT_006249c0,&DAT_00624bc8);
  }
  __initterm(&DAT_00624ccc,&DAT_00624dd0);
  if ((DAT_00639f60 == 0) && (bVar1 = __CrtSetDbgFlag(0xffffffff), (bVar1 & 0x20) != 0)) {
    DAT_00639f60 = 1;
    __CrtDumpMemoryLeaks();
  }
  if (param_3 == 0) {
    DAT_00639f5c = 1;
                    /* WARNING: Subroutine does not return */
    ExitProcess(param_1);
  }
  return;
}
#undef DAT_00639f54
#undef DAT_006e6b54
#undef DAT_006e6b68
#undef _DAT_00639f58
#undef local_8

/* 005f4330 crt */
/* Library Function - Single Match
    __initterm
   
   Library: Visual Studio 1998 Debug */

void __cdecl __initterm(int *param_1,int *param_2)

{
  for (; param_1 < param_2; param_1 = param_1 + 1) {
    if (*param_1 != 0) {
      (*(code *)*param_1)();
    }
  }
  return;
}

/* 005f4370 crt */
/* Library Function - Single Match
    _strstr
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

char * __cdecl _strstr(char *_Str,char *_SubStr)

{
  char *pcVar1;
  char *pcVar2;
  char cVar3;
  uint uVar4;
  char cVar5;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  uint *puVar9;
  char *pcVar10;
  
  cVar3 = *_SubStr;
  if (cVar3 == '\0') {
    return _Str;
  }
  if (_SubStr[1] == '\0') {
    while (((uint)_Str & 3) != 0) {
      uVar4 = *(uint *)_Str;
      if ((char)uVar4 == cVar3) {
        return (char *)(uint *)_Str;
      }
      _Str = (char *)((int)_Str + 1);
      if ((char)uVar4 == '\0') {
        return (char *)0x0;
      }
    }
    while( true ) {
      while( true ) {
        uVar4 = *(uint *)_Str;
        uVar7 = uVar4 ^ CONCAT22(CONCAT11(cVar3,cVar3),CONCAT11(cVar3,cVar3));
        uVar6 = uVar4 ^ 0xffffffff ^ uVar4 + 0x7efefeff;
        puVar9 = (uint *)((int)_Str + 4);
        if (((uVar7 ^ 0xffffffff ^ uVar7 + 0x7efefeff) & 0x81010100) != 0) break;
        _Str = (char *)puVar9;
        if ((uVar6 & 0x81010100) != 0) {
          if ((uVar6 & 0x1010100) != 0) {
            return (char *)0x0;
          }
          if ((uVar4 + 0x7efefeff & 0x80000000) == 0) {
            return (char *)0x0;
          }
        }
      }
      uVar4 = *(uint *)_Str;
      if ((char)uVar4 == cVar3) {
        return (char *)(uint *)_Str;
      }
      if ((char)uVar4 == '\0') {
        return (char *)0x0;
      }
      cVar5 = (char)(uVar4 >> 8);
      if (cVar5 == cVar3) {
        return (char *)((int)_Str + 1);
      }
      if (cVar5 == '\0') {
        return (char *)0x0;
      }
      cVar5 = (char)(uVar4 >> 0x10);
      if (cVar5 == cVar3) {
        return (char *)((int)_Str + 2);
      }
      if (cVar5 == '\0') break;
      cVar5 = (char)(uVar4 >> 0x18);
      if (cVar5 == cVar3) {
        return (char *)((int)_Str + 3);
      }
      _Str = (char *)puVar9;
      if (cVar5 == '\0') {
        return (char *)0x0;
      }
    }
    return (char *)0x0;
  }
  do {
    cVar5 = *_Str;
    do {
      while (_Str = _Str + 1, cVar5 != cVar3) {
        if (cVar5 == '\0') {
          return (char *)0x0;
        }
        cVar5 = *_Str;
      }
      cVar5 = *_Str;
      pcVar10 = _Str + 1;
      pcVar8 = _SubStr;
    } while (cVar5 != _SubStr[1]);
    do {
      if (pcVar8[2] == '\0') {
LAB_005f43e3:
        return _Str + -1;
      }
      if (*pcVar10 != pcVar8[2]) break;
      pcVar1 = pcVar8 + 3;
      if (*pcVar1 == '\0') goto LAB_005f43e3;
      pcVar2 = pcVar10 + 1;
      pcVar8 = pcVar8 + 2;
      pcVar10 = pcVar10 + 2;
    } while (*pcVar1 == *pcVar2);
  } while( true );
}

/* 005f43f0 crt */
#define DAT_0063a428 (*(undefined4 *)((u8 *)&g.d_0063a428))
/* Library Function - Single Match
    _malloc
   
   Library: Visual Studio 1998 Debug */

void * __cdecl _malloc(size_t _Size)

{
  void *pvVar1;
  
  pvVar1 = (void *)__nh_malloc_dbg(_Size,DAT_0063a428,1,0,0);
  return pvVar1;
}
#undef DAT_0063a428

/* 005f4420 crt */
#define DAT_0063a428 (*(undefined4 *)((u8 *)&g.d_0063a428))
/* Library Function - Single Match
    __malloc_dbg
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl
__malloc_dbg(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  uVar1 = __nh_malloc_dbg(param_1,DAT_0063a428,param_2,param_3,param_4);
  return uVar1;
}
#undef DAT_0063a428

/* 005f4450 crt */
/* Library Function - Single Match
    __nh_malloc
   
   Library: Visual Studio 1998 Debug */

void * __cdecl __nh_malloc(size_t _Size,int _NhFlag)

{
  void *pvVar1;
  
  pvVar1 = (void *)__nh_malloc_dbg(_Size,_NhFlag,1,0,0);
  return pvVar1;
}

/* 005f4480 crt */
/* Library Function - Single Match
    __nh_malloc_dbg
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl
__nh_malloc_dbg(size_t param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

{
  int iVar1;
  
  while( true ) {
    iVar1 = __heap_alloc_dbg(param_1,param_3,param_4,param_5);
    if (iVar1 != 0) {
      return iVar1;
    }
    if (param_2 == 0) break;
    iVar1 = __callnewh(param_1);
    if (iVar1 == 0) {
      return 0;
    }
  }
  return 0;
}

/* 005f44f0 crt */
/* Library Function - Single Match
    __heap_alloc
   
   Library: Visual Studio 1998 Debug */

void * __cdecl __heap_alloc(size_t _Size)

{
  void *pvVar1;
  
  pvVar1 = (void *)__heap_alloc_dbg(_Size,1,0,0);
  return pvVar1;
}

/* 005f4520 crt */
#define DAT_00639f70 (*(undefined *)((u8 *)&g.d_00639f70))
#define DAT_00639f78 (*(int *)((u8 *)&g.d_00639f78))
#define DAT_00639f7c (*(byte *)((u8 *)&g.d_00639f7c))
#define DAT_006e5470 (*(undefined4 * *)((u8 *)&g.d_006e5470))
#define DAT_006e5474 (*(int *)((u8 *)&g.d_006e5474))
#define DAT_006e5478 (*(undefined4 * *)((u8 *)&g.d_006e5478))
#define DAT_006e547c (*(uint *)((u8 *)&g.d_006e547c))
#define DAT_006e5480 (*(uint *)((u8 *)&g.d_006e5480))
/* Library Function - Single Match
    __heap_alloc_dbg
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl __heap_alloc_dbg(uint param_1,uint param_2,int param_3,undefined4 param_4)

{
  code *pcVar1;
  bool bVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 *puVar7;
  
  bVar2 = false;
  if (((((byte)DAT_00639f70 & 4) != 0) && (iVar4 = __CrtCheckMemory(), iVar4 == 0)) &&
     (iVar4 = __CrtDbgReport(2,"dbgheap.c",0x141,0,"_CrtCheckMemory()"), iVar4 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar5 = (*pcVar1)();
    return uVar5;
  }
  iVar4 = DAT_00639f74;
  if (DAT_00639f74 == DAT_00639f78) {
    pcVar1 = (code *)swi(3);
    uVar5 = (*pcVar1)();
    return uVar5;
  }
  iVar6 = (*(code *)PTR_FUN_0063a42c)(1,0,param_1,param_2,DAT_00639f74,param_3,param_4);
  if (iVar6 == 0) {
    if (param_3 == 0) {
      iVar4 = __CrtDbgReport(0,0,0,0,&DAT_0061dc40,"Client hook allocation failure.\n");
      if (iVar4 == 1) {
        pcVar1 = (code *)swi(3);
        uVar5 = (*pcVar1)();
        return uVar5;
      }
    }
    else {
      iVar4 = __CrtDbgReport(0,0,0,0,"Client hook allocation failure at file %hs line %d.\n",param_3
                             ,param_4);
      if (iVar4 == 1) {
        pcVar1 = (code *)swi(3);
        uVar5 = (*pcVar1)();
        return uVar5;
      }
    }
    puVar7 = (undefined4 *)0x0;
  }
  else {
    if (((param_2 & 0xffff) != 2) && (((byte)DAT_00639f70 & 1) == 0)) {
      bVar2 = true;
    }
    if ((param_1 < 0xffffffe1) && (param_1 + 0x24 < 0xffffffe1)) {
      if (((((param_2 & 0xffff) != 4) && (param_2 != 1)) && ((param_2 & 0xffff) != 2)) &&
         ((param_2 != 3 &&
          (iVar6 = __CrtDbgReport(1,0,0,0,&DAT_0061dc40,
                                  "Error: memory allocation: bad memory block type.\n"), iVar6 == 1)
          ))) {
        pcVar1 = (code *)swi(3);
        uVar5 = (*pcVar1)();
        return uVar5;
      }
      puVar7 = (undefined4 *)__heap_alloc_base(param_1 + 0x24);
      if (puVar7 == (undefined4 *)0x0) {
        puVar7 = (undefined4 *)0x0;
      }
      else {
        DAT_00639f74 = DAT_00639f74 + 1;
        if (bVar2) {
          *puVar7 = 0;
          puVar7[1] = 0;
          puVar7[2] = 0;
          puVar7[3] = 0xfedcbabc;
          puVar7[4] = param_1;
          puVar7[5] = 3;
          puVar7[6] = 0;
        }
        else {
          DAT_006e5474 = DAT_006e5474 + param_1;
          DAT_006e547c = DAT_006e547c + param_1;
          if (DAT_006e5480 < DAT_006e547c) {
            DAT_006e5480 = DAT_006e547c;
          }
          puVar3 = puVar7;
          if (DAT_006e5478 != (undefined4 *)0x0) {
            DAT_006e5478[1] = puVar7;
            puVar3 = DAT_006e5470;
          }
          DAT_006e5470 = puVar3;
          *puVar7 = DAT_006e5478;
          puVar7[1] = 0;
          puVar7[2] = param_3;
          puVar7[3] = param_4;
          puVar7[4] = param_1;
          puVar7[5] = param_2;
          puVar7[6] = iVar4;
          DAT_006e5478 = puVar7;
        }
        _memset(puVar7 + 7,(uint)DAT_00639f7c,4);
        _memset((void *)((int)puVar7 + param_1 + 0x20),(uint)DAT_00639f7c,4);
        _memset(puVar7 + 8,(uint)DAT_00639f84,param_1);
        puVar7 = puVar7 + 8;
      }
    }
    else {
      iVar4 = __CrtDbgReport(1,0,0,0,"Invalid allocation size: %u bytes.\n",param_1);
      if (iVar4 == 1) {
        pcVar1 = (code *)swi(3);
        uVar5 = (*pcVar1)();
        return uVar5;
      }
      puVar7 = (undefined4 *)0x0;
    }
  }
  return puVar7;
}
#undef DAT_00639f70
#undef DAT_00639f78
#undef DAT_00639f7c
#undef DAT_006e5470
#undef DAT_006e5474
#undef DAT_006e5478
#undef DAT_006e547c
#undef DAT_006e5480

/* 005f4860 crt */
/* Library Function - Single Match
    _calloc
   
   Library: Visual Studio 1998 Debug */

void * __cdecl _calloc(size_t _Count,size_t _Size)

{
  void *pvVar1;
  
  pvVar1 = (void *)__calloc_dbg(_Count,_Size,1,0,0);
  return pvVar1;
}

/* 005f4890 crt */
#define local_10 (*(undefined1 * *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    __calloc_dbg
   
   Library: Visual Studio 1998 Debug */

undefined1 * __cdecl
__calloc_dbg(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

{
  undefined1 *puVar1;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  puVar1 = (undefined1 *)__malloc_dbg(param_2 * param_1,param_3,param_4,param_5);
  if (puVar1 != (undefined1 *)0x0) {
    for (local_10 = puVar1; local_10 < puVar1 + param_2 * param_1; local_10 = local_10 + 1) {
      *local_10 = 0;
    }
  }
  return puVar1;
}
#undef local_10

/* 005f4900 crt */
/* Library Function - Multiple Matches With Different Base Names
    __expand
    _realloc
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl FUN_005f4900(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = __realloc_dbg(param_1,param_2,1,0,0);
  return uVar1;
}

/* 005f4930 crt */
/* Library Function - Single Match
    __realloc_dbg
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl
__realloc_dbg(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
             undefined4 param_5)

{
  undefined4 uVar1;
  
  uVar1 = realloc_help(param_1,param_2,param_3,param_4,param_5,1);
  return uVar1;
}

/* 005f4970 crt */
#define DAT_00639f70 (*(undefined *)((u8 *)&g.d_00639f70))
#define DAT_00639f78 (*(int *)((u8 *)&g.d_00639f78))
#define DAT_00639f7c (*(byte *)((u8 *)&g.d_00639f7c))
#define DAT_006e5470 (*(int * *)((u8 *)&g.d_006e5470))
#define DAT_006e5474 (*(int *)((u8 *)&g.d_006e5474))
#define DAT_006e5478 (*(int * *)((u8 *)&g.d_006e5478))
#define DAT_006e547c (*(uint *)((u8 *)&g.d_006e547c))
#define DAT_006e5480 (*(uint *)((u8 *)&g.d_006e5480))
#define local_10 (*(int * *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    _realloc_help
   
   Library: Visual Studio 1998 Debug */

int * __cdecl
realloc_help(int param_1,uint param_2,uint param_3,int param_4,int param_5,int param_6)

{
  code *pcVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int *piVar6;
  bool bVar7;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 == 0) {
    piVar2 = (int *)__malloc_dbg(param_2,param_3,param_4,param_5);
  }
  else if ((param_6 == 0) || (param_2 != 0)) {
    if ((((byte)DAT_00639f70 & 4) != 0) &&
       ((iVar3 = __CrtCheckMemory(), iVar3 == 0 &&
        (iVar3 = __CrtDbgReport(2,"dbgheap.c",0x239,0,"_CrtCheckMemory()"), iVar3 == 1)))) {
      pcVar1 = (code *)swi(3);
      uVar4 = (*pcVar1)();
      return (int *)uVar4;
    }
    iVar3 = DAT_00639f74;
    if (DAT_00639f74 == DAT_00639f78) {
      pcVar1 = (code *)swi(3);
      uVar4 = (*pcVar1)();
      return (int *)uVar4;
    }
    iVar5 = (*(code *)PTR_FUN_0063a42c)(2,param_1,param_2,param_3,DAT_00639f74,param_4,param_5);
    if (iVar5 == 0) {
      if (param_4 == 0) {
        iVar3 = __CrtDbgReport(0,0,0,0,&DAT_0061dc40,"Client hook re-allocation failure.\n");
        if (iVar3 == 1) {
          pcVar1 = (code *)swi(3);
          uVar4 = (*pcVar1)();
          return (int *)uVar4;
        }
      }
      else {
        iVar3 = __CrtDbgReport(0,0,0,0,"Client hook re-allocation failure at file %hs line %d.\n",
                               param_4,param_5);
        if (iVar3 == 1) {
          pcVar1 = (code *)swi(3);
          uVar4 = (*pcVar1)();
          return (int *)uVar4;
        }
      }
      piVar2 = (int *)0x0;
    }
    else if (param_2 < 0xffffffdc) {
      if ((((param_3 != 1) && ((param_3 & 0xffff) != 4)) && ((param_3 & 0xffff) != 2)) &&
         (iVar5 = __CrtDbgReport(1,0,0,0,&DAT_0061dc40,
                                 "Error: memory allocation: bad memory block type.\n"), iVar5 == 1))
      {
        pcVar1 = (code *)swi(3);
        uVar4 = (*pcVar1)();
        return (int *)uVar4;
      }
      iVar5 = __CrtIsValidHeapPointer(param_1);
      if ((iVar5 == 0) &&
         (iVar5 = __CrtDbgReport(2,"dbgheap.c",0x261,0,"_CrtIsValidHeapPointer(pUserData)"),
         iVar5 == 1)) {
        pcVar1 = (code *)swi(3);
        uVar4 = (*pcVar1)();
        return (int *)uVar4;
      }
      piVar6 = (int *)(param_1 + -0x20);
      bVar7 = *(int *)(param_1 + -0xc) == 3;
      if (bVar7) {
        if (((*(int *)(param_1 + -0x14) != -0x1234544) || (*(int *)(param_1 + -8) != 0)) &&
           (iVar5 = __CrtDbgReport(2,"dbgheap.c",0x26b,0,
                                   "pOldBlock->nLine == IGNORE_LINE && pOldBlock->lRequest == IGNORE_REQ"
                                  ), iVar5 == 1)) {
          pcVar1 = (code *)swi(3);
          uVar4 = (*pcVar1)();
          return (int *)uVar4;
        }
      }
      else {
        if (((*(uint *)(param_1 + -0xc) & 0xffff) == 2) && ((param_3 & 0xffff) == 1)) {
          param_3 = 2;
        }
        if ((((*(uint *)(param_1 + -0xc) ^ param_3 & 0xffff) & 0xffff) != 0) &&
           (iVar5 = __CrtDbgReport(2,"dbgheap.c",0x272,0,
                                   "_BLOCK_TYPE(pOldBlock->nBlockUse)==_BLOCK_TYPE(nBlockUse)"),
           iVar5 == 1)) {
          pcVar1 = (code *)swi(3);
          uVar4 = (*pcVar1)();
          return (int *)uVar4;
        }
      }
      if (param_6 == 0) {
        local_10 = (int *)__expand_base(piVar6,param_2 + 0x24);
        if (local_10 == (int *)0x0) {
          return (int *)0;
        }
      }
      else {
        local_10 = (int *)__realloc_base(piVar6,param_2 + 0x24);
        if (local_10 == (int *)0x0) {
          return (int *)0;
        }
      }
      DAT_00639f74 = DAT_00639f74 + 1;
      if (!bVar7) {
        DAT_006e5474 = DAT_006e5474 - local_10[4];
        DAT_006e5474 = DAT_006e5474 + param_2;
        DAT_006e547c = DAT_006e547c - local_10[4];
        DAT_006e547c = DAT_006e547c + param_2;
        if (DAT_006e5480 < DAT_006e547c) {
          DAT_006e5480 = DAT_006e547c;
        }
      }
      piVar2 = local_10 + 8;
      if ((uint)local_10[4] < param_2) {
        _memset((void *)(local_10[4] + (int)piVar2),(uint)DAT_00639f84,param_2 - local_10[4]);
      }
      _memset((void *)(param_2 + (int)piVar2),(uint)DAT_00639f7c,4);
      if (!bVar7) {
        local_10[2] = param_4;
        local_10[3] = param_5;
        local_10[6] = iVar3;
      }
      local_10[4] = param_2;
      if (((param_6 == 0) && (local_10 != piVar6)) &&
         (iVar3 = __CrtDbgReport(2,"dbgheap.c",0x2a8,0,
                                 "fRealloc || (!fRealloc && pNewBlock == pOldBlock)"), iVar3 == 1))
      {
        pcVar1 = (code *)swi(3);
        uVar4 = (*pcVar1)();
        return (int *)uVar4;
      }
      if ((local_10 != piVar6) && (!bVar7)) {
        if (*local_10 == 0) {
          if ((DAT_006e5470 != piVar6) &&
             (iVar3 = __CrtDbgReport(2,"dbgheap.c",0x2b7,0,"_pLastBlock == pOldBlock"), iVar3 == 1))
          {
            pcVar1 = (code *)swi(3);
            uVar4 = (*pcVar1)();
            return (int *)uVar4;
          }
          DAT_006e5470 = (int *)local_10[1];
        }
        else {
          *(int *)(*local_10 + 4) = local_10[1];
        }
        if (local_10[1] == 0) {
          if ((DAT_006e5478 != piVar6) &&
             (iVar3 = __CrtDbgReport(2,"dbgheap.c",0x2c2,0,"_pFirstBlock == pOldBlock"), iVar3 == 1)
             ) {
            pcVar1 = (code *)swi(3);
            uVar4 = (*pcVar1)();
            return (int *)uVar4;
          }
          DAT_006e5478 = (int *)*local_10;
        }
        else {
          *(int *)local_10[1] = *local_10;
        }
        if (DAT_006e5478 == (int *)0x0) {
          DAT_006e5470 = local_10;
        }
        else {
          DAT_006e5478[1] = (int)local_10;
        }
        *local_10 = (int)DAT_006e5478;
        local_10[1] = 0;
        DAT_006e5478 = local_10;
      }
    }
    else {
      iVar3 = __CrtDbgReport(1,0,0,0,"Allocation too large or negative: %u bytes.\n",param_2);
      if (iVar3 == 1) {
        pcVar1 = (code *)swi(3);
        uVar4 = (*pcVar1)();
        return (int *)uVar4;
      }
      piVar2 = (int *)0x0;
    }
  }
  else {
    __free_dbg(param_1,param_3);
    piVar2 = (int *)0x0;
  }
  return piVar2;
}
#undef DAT_00639f70
#undef DAT_00639f78
#undef DAT_00639f7c
#undef DAT_006e5470
#undef DAT_006e5474
#undef DAT_006e5478
#undef DAT_006e547c
#undef DAT_006e5480
#undef local_10

/* 005f4f00 crt */
/* Library Function - Multiple Matches With Different Base Names
    __expand
    _realloc
   
   Library: Visual Studio 1998 Debug */

void __cdecl FUN_005f4f00(undefined4 param_1,undefined4 param_2)

{
  __expand_dbg(param_1,param_2,1,0,0);
  return;
}

/* 005f4f30 crt */
/* Library Function - Single Match
    __expand_dbg
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl
__expand_dbg(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  undefined4 uVar1;
  
  uVar1 = realloc_help(param_1,param_2,param_3,param_4,param_5,0);
  return uVar1;
}

/* 005f4f70 crt */
void __cdecl FUN_005f4f70(undefined4 param_1)

{
  __free_dbg(param_1,1);
  return;
}

/* 005f4f90: written by hand in src/crt/heap.c */

/* 005f53c0 crt */
/* Library Function - Single Match
    __msize
   
   Library: Visual Studio 1998 Debug */

size_t __cdecl __msize(void *_Memory)

{
  size_t sVar1;
  
  sVar1 = __msize_dbg(_Memory,1);
  return sVar1;
}

/* 005f53e0 crt */
#define DAT_00639f70 (*(undefined *)((u8 *)&g.d_00639f70))
/* Library Function - Single Match
    __msize_dbg
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl __msize_dbg(int param_1,int param_2)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (((byte)DAT_00639f70 & 4) != 0) {
    iVar2 = __CrtCheckMemory();
    if (iVar2 == 0) {
      iVar2 = __CrtDbgReport(2,"dbgheap.c",0x47c,0,"_CrtCheckMemory()");
      if (iVar2 == 1) {
        pcVar1 = (code *)swi(3);
        uVar3 = (*pcVar1)();
        return uVar3;
      }
    }
  }
  iVar2 = __CrtIsValidHeapPointer(param_1);
  if (iVar2 == 0) {
    iVar2 = __CrtDbgReport(2,"dbgheap.c",0x485,0,"_CrtIsValidHeapPointer(pUserData)");
    if (iVar2 == 1) {
      pcVar1 = (code *)swi(3);
      uVar3 = (*pcVar1)();
      return uVar3;
    }
  }
  if (((((*(uint *)(param_1 + -0xc) & 0xffff) != 4) && (*(int *)(param_1 + -0xc) != 1)) &&
      ((*(uint *)(param_1 + -0xc) & 0xffff) != 2)) && (*(int *)(param_1 + -0xc) != 3)) {
    iVar2 = __CrtDbgReport(2,"dbgheap.c",0x48b,0,"_BLOCK_TYPE_IS_VALID(pHead->nBlockUse)");
    if (iVar2 == 1) {
      pcVar1 = (code *)swi(3);
      uVar3 = (*pcVar1)();
      return uVar3;
    }
  }
  if ((*(int *)(param_1 + -0xc) == 2) && (param_2 == 1)) {
    param_2 = 2;
  }
  if ((*(int *)(param_1 + -0xc) != 3) && (*(int *)(param_1 + -0xc) != param_2)) {
    iVar2 = __CrtDbgReport(2,"dbgheap.c",0x492,0,"pHead->nBlockUse == nBlockUse");
    if (iVar2 == 1) {
      pcVar1 = (code *)swi(3);
      uVar3 = (*pcVar1)();
      return uVar3;
    }
  }
  return *(undefined4 *)(param_1 + -0x10);
}
#undef DAT_00639f70

/* 005f5550 crt */
#define DAT_00639f78 (*(undefined4 *)((u8 *)&g.d_00639f78))
undefined4 __cdecl FUN_005f5550(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_00639f78;
  DAT_00639f78 = param_1;
  return uVar1;
}
#undef DAT_00639f78

/* 005f5580 crt */
/* Library Function - Single Match
    __CrtSetDbgBlockType
   
   Library: Visual Studio 1998 Debug */

void __cdecl __CrtSetDbgBlockType(int param_1,undefined4 param_2)

{
  code *pcVar1;
  int iVar2;
  
  iVar2 = __CrtIsValidHeapPointer(param_1);
  if (iVar2 != 0) {
    if (((((*(uint *)(param_1 + -0xc) & 0xffff) != 4) && (*(int *)(param_1 + -0xc) != 1)) &&
        ((*(uint *)(param_1 + -0xc) & 0xffff) != 2)) && (*(int *)(param_1 + -0xc) != 3)) {
      iVar2 = __CrtDbgReport(2,"dbgheap.c",0x4d3,0,"_BLOCK_TYPE_IS_VALID(pHead->nBlockUse)");
      if (iVar2 == 1) {
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
    }
    *(undefined4 *)(param_1 + -0xc) = param_2;
  }
  return;
}

/* 005f5620 crt */
undefined * __cdecl FUN_005f5620(undefined *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR_FUN_0063a42c;
  PTR_FUN_0063a42c = param_1;
  return puVar1;
}

/* 005f5650 crt */
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    _CheckBytes
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl _CheckBytes(byte *param_1,undefined4 param_2,int param_3)

{
  code *pcVar1;
  byte *pbVar2;
  int iVar3;
  undefined4 uVar4;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 1;
  pbVar2 = param_1;
  while( true ) {
    do {
      param_1 = pbVar2;
      iVar3 = param_3 + -1;
      if (param_3 == 0) {
        return local_8;
      }
      pbVar2 = param_1 + 1;
      param_3 = iVar3;
    } while (*param_1 == (byte)param_2);
    iVar3 = __CrtDbgReport(0,0,0,0,"memory check error at 0x%08X = 0x%02X, should be 0x%02X.\n",
                           param_1,(uint)*param_1,(uint)(byte)param_2);
    if (iVar3 == 1) break;
    local_8 = 0;
  }
  pcVar1 = (code *)swi(3);
  uVar4 = (*pcVar1)();
  return uVar4;
}
#undef local_8

/* 005f56e0 crt */
#define DAT_00639f70 (*(undefined *)((u8 *)&g.d_00639f70))
#define DAT_00639f7c (*(undefined1 *)((u8 *)&g.d_00639f7c))
#define DAT_00639f80 (*(undefined1 *)((u8 *)&g.d_00639f80))
#define DAT_006e5478 (*(char * *)((u8 *)&g.d_006e5478))
#define local_18 (*(char * *)(frame_ + FRAME_OFF(0)))
#define local_c (*(char * *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(16)))
/* Library Function - Single Match
    __CrtCheckMemory
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl __CrtCheckMemory(void)

{
  code *pcVar1;
  bool bVar2;
  int iVar3;
  undefined4 uVar4;
  char *pcVar5;
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 1;
  if (((byte)DAT_00639f70 & 1) == 0) {
    local_8 = 1;
  }
  else {
    iVar3 = __heapchk();
    if ((iVar3 == -1) || (iVar3 == -2)) {
      for (local_c = DAT_006e5478; local_c != (char *)0x0; local_c = *(char **)local_c) {
        bVar2 = true;
        if (((((*(uint *)(local_c + 0x14) & 0xffff) == 4) || (*(int *)(local_c + 0x14) == 1)) ||
            ((*(uint *)(local_c + 0x14) & 0xffff) == 2)) || (*(int *)(local_c + 0x14) == 3)) {
          local_18 = (&PTR_DAT_00639f88)[*(uint *)(local_c + 0x14) & 0xffff];
          pcVar5 = local_18;
        }
        else {
          local_18 = "DAMAGED";
          pcVar5 = local_c;
        }
        iVar3 = _CheckBytes(local_c + 0x1c,CONCAT31((int3)((uint)pcVar5 >> 8),DAT_00639f7c),4);
        if (iVar3 == 0) {
          iVar3 = __CrtDbgReport(0,0,0,0,"DAMAGE: before %hs block (#%d) at 0x%08X.\n",local_18,
                                 *(undefined4 *)(local_c + 0x18),local_c + 0x20);
          if (iVar3 == 1) {
            pcVar1 = (code *)swi(3);
            uVar4 = (*pcVar1)();
            return uVar4;
          }
          bVar2 = false;
        }
        iVar3 = _CheckBytes(local_c + *(int *)(local_c + 0x10) + 0x20,
                            CONCAT31((int3)((uint)iVar3 >> 8),DAT_00639f7c),4);
        if (iVar3 == 0) {
          iVar3 = __CrtDbgReport(0,0,0,0,"DAMAGE: after %hs block (#%d) at 0x%08X.\n",local_18,
                                 *(undefined4 *)(local_c + 0x18),local_c + 0x20);
          if (iVar3 == 1) {
            pcVar1 = (code *)swi(3);
            uVar4 = (*pcVar1)();
            return uVar4;
          }
          bVar2 = false;
        }
        if ((*(int *)(local_c + 0x14) == 0) &&
           (iVar3 = _CheckBytes(local_c + 0x20,
                                CONCAT31((int3)((uint)*(undefined4 *)(local_c + 0x10) >> 8),
                                         DAT_00639f80),*(undefined4 *)(local_c + 0x10)), iVar3 == 0)
           ) {
          iVar3 = __CrtDbgReport(0,0,0,0,"DAMAGE: on top of Free block at 0x%08X.\n",local_c + 0x20)
          ;
          if (iVar3 == 1) {
            pcVar1 = (code *)swi(3);
            uVar4 = (*pcVar1)();
            return uVar4;
          }
          bVar2 = false;
        }
        if (!bVar2) {
          if ((*(int *)(local_c + 8) != 0) &&
             (iVar3 = __CrtDbgReport(0,0,0,0,"%hs allocated at file %hs(%d).\n",local_18,
                                     *(undefined4 *)(local_c + 8),*(undefined4 *)(local_c + 0xc)),
             iVar3 == 1)) {
            pcVar1 = (code *)swi(3);
            uVar4 = (*pcVar1)();
            return uVar4;
          }
          iVar3 = __CrtDbgReport(0,0,0,0,"%hs located at 0x%08X is %u bytes long.\n",local_18,
                                 local_c + 0x20,*(undefined4 *)(local_c + 0x10));
          if (iVar3 == 1) {
            pcVar1 = (code *)swi(3);
            uVar4 = (*pcVar1)();
            return uVar4;
          }
          local_8 = 0;
        }
      }
    }
    else {
      switch(iVar3) {
      case -6:
        iVar3 = __CrtDbgReport(0,0,0,0,&DAT_0061dc40,"_heapchk fails with _HEAPBADPTR.\n");
        if (iVar3 == 1) {
          pcVar1 = (code *)swi(3);
          uVar4 = (*pcVar1)();
          return uVar4;
        }
        break;
      case -5:
        iVar3 = __CrtDbgReport(0,0,0,0,&DAT_0061dc40,"_heapchk fails with _HEAPBADEND.\n");
        if (iVar3 == 1) {
          pcVar1 = (code *)swi(3);
          uVar4 = (*pcVar1)();
          return uVar4;
        }
        break;
      case -4:
        iVar3 = __CrtDbgReport(0,0,0,0,&DAT_0061dc40,"_heapchk fails with _HEAPBADNODE.\n");
        if (iVar3 == 1) {
          pcVar1 = (code *)swi(3);
          uVar4 = (*pcVar1)();
          return uVar4;
        }
        break;
      case -3:
        iVar3 = __CrtDbgReport(0,0,0,0,&DAT_0061dc40,"_heapchk fails with _HEAPBADBEGIN.\n");
        if (iVar3 == 1) {
          pcVar1 = (code *)swi(3);
          uVar4 = (*pcVar1)();
          return uVar4;
        }
        break;
      default:
        iVar3 = __CrtDbgReport(0,0,0,0,&DAT_0061dc40,"_heapchk fails with unknown return value!\n");
        if (iVar3 == 1) {
          pcVar1 = (code *)swi(3);
          uVar4 = (*pcVar1)();
          return uVar4;
        }
      }
      local_8 = 0;
    }
  }
  return local_8;
}
#undef DAT_00639f70
#undef DAT_00639f7c
#undef DAT_00639f80
#undef DAT_006e5478
#undef local_18
#undef local_c
#undef local_8

/* 005f5a60 crt */
#define DAT_00639f70 (*(int *)((u8 *)&g.d_00639f70))
/* Library Function - Single Match
    __CrtSetDbgFlag
   
   Library: Visual Studio 1998 Debug */

undefined1 __cdecl __CrtSetDbgFlag(int param_1)

{
  int iVar1;
  
  iVar1 = DAT_00639f70;
  if (param_1 != -1) {
    DAT_00639f70 = param_1;
  }
  return (char)iVar1;
}
#undef DAT_00639f70

/* 005f5a90 crt */
#define DAT_00639f70 (*(undefined *)((u8 *)&g.d_00639f70))
#define DAT_006e5478 (*(undefined4 * *)((u8 *)&g.d_006e5478))
#define local_8 (*(undefined4 * *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    __CrtDoForAllClientObjects
   
   Library: Visual Studio 1998 Debug */

void __cdecl __CrtDoForAllClientObjects(code *param_1,undefined4 param_2)

{
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((byte)DAT_00639f70 & 1) != 0) {
    for (local_8 = DAT_006e5478; local_8 != (undefined4 *)0x0; local_8 = (undefined4 *)*local_8) {
      if ((local_8[5] & 0xffff) == 4) {
        (*param_1)(local_8 + 8,param_2);
      }
    }
  }
  return;
}
#undef DAT_00639f70
#undef DAT_006e5478
#undef local_8

/* 005f5b00 crt */
/* Library Function - Single Match
    __CrtIsValidPointer
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl __CrtIsValidPointer(void *param_1,UINT_PTR param_2,int param_3)

{
  BOOL BVar1;
  
  if (((param_1 != (void *)0x0) && (BVar1 = IsBadReadPtr(param_1,param_2), BVar1 == 0)) &&
     ((param_3 == 0 || (BVar1 = IsBadWritePtr(param_1,param_2), BVar1 == 0)))) {
    return 1;
  }
  return 0;
}

/* 005f5b60 crt */
#define DAT_00639f20 (*(undefined *)((u8 *)&g.d_00639f20))
#define local_10 (*(undefined1 (*)[4])(frame_ + FRAME_OFF(0)))
#define local_c (*(char * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(undefined1 (*)[4])(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    __CrtIsValidHeapPointer
   
   Library: Visual Studio 1998 Debug */

BOOL __cdecl __CrtIsValidHeapPointer(int param_1)

{
  BOOL BVar1;
  int iVar2;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 == 0) {
    BVar1 = 0;
  }
  else {
    iVar2 = __CrtIsValidPointer(param_1 + -0x20,0x20,1);
    if (iVar2 == 0) {
      BVar1 = 0;
    }
    else {
      local_c = (char *)___sbh_find_block(param_1 + -0x20,local_10,local_8);
      if (local_c == (char *)0x0) {
        if (((*(undefined1 *)((char *)&DAT_00639f20 + 1)) & 0x80) == 0) {
          BVar1 = HeapValidate(DAT_006e69e4,0,(LPCVOID)(param_1 + -0x20));
        }
        else {
          BVar1 = 1;
        }
      }
      else if (*local_c == '\0') {
        BVar1 = 0;
      }
      else {
        BVar1 = 1;
      }
    }
  }
  return BVar1;
}
#undef DAT_00639f20
#undef local_10
#undef local_c
#undef local_8

/* 005f5c30 crt */
/* Library Function - Single Match
    __CrtIsMemoryBlock
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl
__CrtIsMemoryBlock(int param_1,int param_2,undefined4 *param_3,undefined4 *param_4,
                  undefined4 *param_5)

{
  int iVar1;
  
  iVar1 = __CrtIsValidHeapPointer(param_1);
  if (((iVar1 != 0) &&
      (((((*(uint *)(param_1 + -0xc) & 0xffff) == 4 || (*(int *)(param_1 + -0xc) == 1)) ||
        ((*(uint *)(param_1 + -0xc) & 0xffff) == 2)) || (*(int *)(param_1 + -0xc) == 3)))) &&
     (((iVar1 = __CrtIsValidPointer(param_1,param_2,1), iVar1 != 0 &&
       (*(int *)(param_1 + -0x10) == param_2)) && (*(int *)(param_1 + -8) <= DAT_00639f74)))) {
    if (param_3 != (undefined4 *)0x0) {
      *param_3 = *(undefined4 *)(param_1 + -8);
    }
    if (param_4 != (undefined4 *)0x0) {
      *param_4 = *(undefined4 *)(param_1 + -0x18);
    }
    if (param_5 != (undefined4 *)0x0) {
      *param_5 = *(undefined4 *)(param_1 + -0x14);
    }
    return 1;
  }
  return 0;
}

/* 005f5d30 crt */
#define DAT_006e6b48 (*(undefined4 *)((u8 *)&g.d_006e6b48))
undefined4 __cdecl FUN_005f5d30(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_006e6b48;
  DAT_006e6b48 = param_1;
  return uVar1;
}
#undef DAT_006e6b48

/* 005f5d60 crt */
#define DAT_006e5474 (*(undefined4 *)((u8 *)&g.d_006e5474))
#define DAT_006e5478 (*(undefined4 * *)((u8 *)&g.d_006e5478))
#define DAT_006e5480 (*(undefined4 *)((u8 *)&g.d_006e5480))
#define local_c (*(undefined4 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    __CrtMemCheckpoint
   
   Library: Visual Studio 1998 Debug */

void __cdecl __CrtMemCheckpoint(undefined4 *param_1)

{
  code *pcVar1;
  int iVar2;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 == (undefined4 *)0x0) {
    iVar2 = __CrtDbgReport(0,0,0,0,&DAT_0061dc40,"_CrtMemCheckPoint: NULL state pointer.\n");
    if (iVar2 == 1) {
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
  }
  else {
    *param_1 = DAT_006e5478;
    for (local_8 = 0; local_8 < 5; local_8 = local_8 + 1) {
      param_1[local_8 + 6] = 0;
      param_1[local_8 + 1] = param_1[local_8 + 6];
    }
    for (local_c = DAT_006e5478; local_c != (undefined4 *)0x0; local_c = (undefined4 *)*local_c) {
      if ((local_c[5] & 0xffff) < 5) {
        param_1[(local_c[5] & 0xffff) + 1] = param_1[(local_c[5] & 0xffff) + 1] + 1;
        param_1[(local_c[5] & 0xffff) + 6] = param_1[(local_c[5] & 0xffff) + 6] + local_c[4];
      }
      else {
        iVar2 = __CrtDbgReport(0,0,0,0,"Bad memory block found at 0x%08X.\n",local_c);
        if (iVar2 == 1) {
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
      }
    }
    param_1[0xb] = DAT_006e5480;
    param_1[0xc] = DAT_006e5474;
  }
  return;
}
#undef DAT_006e5474
#undef DAT_006e5478
#undef DAT_006e5480
#undef local_c
#undef local_8

/* 005f5ea0 crt */
#define DAT_00639f70 (*(undefined *)((u8 *)&g.d_00639f70))
#define local_c (*(undefined4 *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    __CrtMemDifference
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl __CrtMemDifference(undefined4 *param_1,int param_2,int param_3)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 0;
  if (((param_1 == (undefined4 *)0x0) || (param_2 == 0)) || (param_3 == 0)) {
    iVar2 = __CrtDbgReport(0,0,0,0,&DAT_0061dc40,"_CrtMemDifference: NULL state pointer.\n");
    if (iVar2 == 1) {
      pcVar1 = (code *)swi(3);
      uVar3 = (*pcVar1)();
      return uVar3;
    }
    local_c = 0;
  }
  else {
    for (local_8 = 0; local_8 < 5; local_8 = local_8 + 1) {
      param_1[local_8 + 6] =
           *(int *)(param_3 + 0x18 + local_8 * 4) - *(int *)(param_2 + 0x18 + local_8 * 4);
      param_1[local_8 + 1] =
           *(int *)(param_3 + 4 + local_8 * 4) - *(int *)(param_2 + 4 + local_8 * 4);
      if (((param_1[local_8 + 6] != 0) || (param_1[local_8 + 1] != 0)) &&
         ((local_8 != 0 && ((local_8 != 2 || (((byte)DAT_00639f70 & 0x10) != 0)))))) {
        local_c = 1;
      }
    }
    param_1[0xb] = *(int *)(param_3 + 0x2c) - *(int *)(param_2 + 0x2c);
    param_1[0xc] = *(int *)(param_3 + 0x30) - *(int *)(param_2 + 0x30);
    *param_1 = 0;
  }
  return local_c;
}
#undef DAT_00639f70
#undef local_c
#undef local_8

/* 005f5fe0 crt */
#define DAT_00639f70 (*(undefined *)((u8 *)&g.d_00639f70))
#define DAT_006e5478 (*(undefined4 * *)((u8 *)&g.d_006e5478))
#define DAT_006e6b48 (*(code * *)((u8 *)&g.d_006e6b48))
#define local_c (*(undefined4 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(undefined4 * *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    __CrtMemDumpAllObjectsSince
   
   Library: Visual Studio 1998 Debug */

void __cdecl __CrtMemDumpAllObjectsSince(undefined4 *param_1)

{
  code *pcVar1;
  int iVar2;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = (undefined4 *)0x0;
  iVar2 = __CrtDbgReport(0,0,0,0,&DAT_0061dc40,"Dumping objects ->\n");
  if (iVar2 == 1) {
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  if (param_1 != (undefined4 *)0x0) {
    local_c = (undefined4 *)*param_1;
  }
  local_8 = DAT_006e5478;
  do {
    if ((local_8 == (undefined4 *)0x0) || (local_8 == local_c)) {
      iVar2 = __CrtDbgReport(0,0,0,0,&DAT_0061dc40,"Object dump complete.\n");
      if (iVar2 != 1) {
        return;
      }
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    if ((((local_8[5] & 0xffff) != 3) && ((local_8[5] & 0xffff) != 0)) &&
       (((local_8[5] & 0xffff) != 2 || (((byte)DAT_00639f70 & 0x10) != 0)))) {
      if (local_8[2] != 0) {
        iVar2 = __CrtIsValidPointer(local_8[2],1,0);
        if (iVar2 == 0) {
          iVar2 = __CrtDbgReport(0,0,0,0,"#File Error#(%d) : ",local_8[3]);
          if (iVar2 == 1) {
            pcVar1 = (code *)swi(3);
            (*pcVar1)();
            return;
          }
        }
        else {
          iVar2 = __CrtDbgReport(0,0,0,0,"%hs(%d) : ",local_8[2],local_8[3]);
          if (iVar2 == 1) {
            pcVar1 = (code *)swi(3);
            (*pcVar1)();
            return;
          }
        }
      }
      iVar2 = __CrtDbgReport(0,0,0,0,"{%ld} ",local_8[6]);
      if (iVar2 == 1) {
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      if ((local_8[5] & 0xffff) == 4) {
        iVar2 = __CrtDbgReport(0,0,0,0,"client block at 0x%08X, subtype %x, %u bytes long.\n",
                               local_8 + 8,(uint)local_8[5] >> 0x10,local_8[4]);
        if (iVar2 == 1) {
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
        if (DAT_006e6b48 == (code *)0x0) {
          __printMemBlockData(local_8);
        }
        else {
          (*DAT_006e6b48)(local_8 + 8,local_8[4]);
        }
      }
      else if (local_8[5] == 1) {
        iVar2 = __CrtDbgReport(0,0,0,0,"normal block at 0x%08X, %u bytes long.\n",local_8 + 8,
                               local_8[4]);
        if (iVar2 == 1) {
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
        __printMemBlockData(local_8);
      }
      else if ((local_8[5] & 0xffff) == 2) {
        iVar2 = __CrtDbgReport(0,0,0,0,"crt block at 0x%08X, subtype %x, %u bytes long.\n",
                               local_8 + 8,(uint)local_8[5] >> 0x10,local_8[4]);
        if (iVar2 == 1) {
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
        __printMemBlockData(local_8);
      }
    }
    local_8 = (undefined4 *)*local_8;
  } while( true );
}
#undef DAT_00639f70
#undef DAT_006e5478
#undef DAT_006e6b48
#undef local_c
#undef local_8

/* 005f62a0 crt */
#define local_58 (*(uint *)(frame_ + FRAME_OFF(0)))
#define local_50 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_4c (*(byte (*)[20])(frame_ + FRAME_OFF(12)))
#define local_38 (*(char (*)[52])(frame_ + FRAME_OFF(32)))
/* Library Function - Single Match
    __printMemBlockData
   
   Library: Visual Studio 1998 Debug */

void __cdecl __printMemBlockData(int param_1)

{
  byte bVar1;
  code *pcVar2;
  int iVar3;
  undefined1 frame_[FRAME_OFF(88)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_50 = 0;
  while( true ) {
    iVar3 = *(int *)(param_1 + 0x10);
    if (0xf < iVar3) {
      iVar3 = 0x10;
    }
    if (iVar3 <= local_50) break;
    bVar1 = *(byte *)(param_1 + 0x20 + local_50);
    if (DAT_0063a29c < 2) {
      local_58 = *(ushort *)(PTR_DAT_0063a090 + (uint)bVar1 * 2) & 0x157;
    }
    else {
      local_58 = __isctype((uint)bVar1,0x157);
    }
    if (local_58 == 0) {
      local_4c[local_50] = 0x20;
    }
    else {
      local_4c[local_50] = bVar1;
    }
    _sprintf(local_38 + local_50 * 3,"%.2X ",(uint)bVar1);
    local_50 = local_50 + 1;
  }
  local_4c[local_50] = 0;
  iVar3 = __CrtDbgReport(0,0,0,0," Data: <%s> %s\n",local_4c,local_38);
  if (iVar3 == 1) {
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  return;
}
#undef local_58
#undef local_50
#undef local_4c
#undef local_38

/* 005f63a0 crt */
#define DAT_00639f70 (*(undefined *)((u8 *)&g.d_00639f70))
#define local_38 (*(undefined1 (*)[8])(frame_ + FRAME_OFF(0)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(20)))
/* Library Function - Single Match
    __CrtDumpMemoryLeaks
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl __CrtDumpMemoryLeaks(void)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  __CrtMemCheckpoint(local_38);
  if (((local_24 == 0) && (local_30 == 0)) &&
     ((((byte)DAT_00639f70 & 0x10) == 0 || (local_2c == 0)))) {
    uVar3 = 0;
  }
  else {
    iVar2 = __CrtDbgReport(0,0,0,0,&DAT_0061dc40,"Detected memory leaks!\n");
    if (iVar2 == 1) {
      pcVar1 = (code *)swi(3);
      uVar3 = (*pcVar1)();
      return uVar3;
    }
    __CrtMemDumpAllObjectsSince(0);
    uVar3 = 1;
  }
  return uVar3;
}
#undef DAT_00639f70
#undef local_38
#undef local_30
#undef local_2c
#undef local_24

/* 005f6430 crt */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    __CrtMemDumpStatistics
   
   Library: Visual Studio 1998 Debug */

void __cdecl __CrtMemDumpStatistics(int param_1)

{
  code *pcVar1;
  int iVar2;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 != 0) {
    for (local_8 = 0; local_8 < 5; local_8 = local_8 + 1) {
      iVar2 = __CrtDbgReport(0,0,0,0,"%ld bytes in %ld %hs Blocks.\n",
                             *(undefined4 *)(param_1 + 0x18 + local_8 * 4),
                             *(undefined4 *)(param_1 + 4 + local_8 * 4),(&PTR_DAT_00639f88)[local_8]
                            );
      if (iVar2 == 1) {
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
    }
    iVar2 = __CrtDbgReport(0,0,0,0,"Largest number used: %ld bytes.\n",
                           *(undefined4 *)(param_1 + 0x2c));
    if (iVar2 == 1) {
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    iVar2 = __CrtDbgReport(0,0,0,0,"Total allocations: %ld bytes.\n",*(undefined4 *)(param_1 + 0x30)
                          );
    if (iVar2 == 1) {
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
  }
  return;
}
#undef local_8

/* 005f6500: written by hand in src/crt/asm.c */

/* 005f6650 crt */
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
/* Library Function - Multiple Matches With Different Base Names
    __wrename
    _rename
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl FUN_005f6650(LPCSTR param_1,LPCSTR param_2)

{
  BOOL BVar1;
  undefined4 uVar2;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  BVar1 = MoveFileA(param_1,param_2);
  if (BVar1 == 0) {
    local_8 = GetLastError();
  }
  else {
    local_8 = 0;
  }
  if (local_8 == 0) {
    uVar2 = 0;
  }
  else {
    __dosmaperr(local_8);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}
#undef local_8

/* 005f66b0 crt */
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
/* Library Function - Multiple Matches With Different Base Names
    __wremove
    _remove
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl FUN_005f66b0(LPCSTR param_1)

{
  BOOL BVar1;
  undefined4 uVar2;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  BVar1 = DeleteFileA(param_1);
  if (BVar1 == 0) {
    local_8 = GetLastError();
  }
  else {
    local_8 = 0;
  }
  if (local_8 == 0) {
    uVar2 = 0;
  }
  else {
    __dosmaperr(local_8);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}
#undef local_8

/* 005f6710 crt */
/* Library Function - Multiple Matches With Different Base Names
    __unlink
    __wunlink
   
   Library: Visual Studio 1998 Debug */

void __cdecl FUN_005f6710(undefined4 param_1)

{
  FUN_005f66b0(param_1);
  return;
}

/* 005f6730 crt */
#define DAT_006e69f0 (*(undefined4 *)((u8 *)&g.d_006e69f0))
#define local_10 (*(undefined * *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    _rewind
   
   Library: Visual Studio 1998 Debug */

void __cdecl _rewind(FILE *_File)

{
  uint _FileHandle;
  code *pcVar1;
  int iVar2;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (_File == (FILE *)0x0) {
    iVar2 = __CrtDbgReport(2,"rewind.c",0x2e,0,"str != NULL");
    if (iVar2 == 1) {
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
  }
  _FileHandle = _File->_file;
  __flush(_File);
  _File->_flag = _File->_flag & 0xffffffcf;
  if (_FileHandle == 0xffffffff) {
    local_10 = &DAT_0063a420;
  }
  else {
    local_10 = (undefined *)
               (*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0) >> 3)) +
               (_FileHandle & 0x1f) * 8);
  }
  local_10[4] = local_10[4] & 0xfd;
  if ((_File->_flag & 0x80) != 0) {
    _File->_flag = _File->_flag & 0xfffffffc;
  }
  __lseek(_FileHandle,0,0);
  return;
}
#undef DAT_006e69f0
#undef local_10

/* 005f67f0 crt */
/* Library Function - Single Match
    _fseek
   
   Library: Visual Studio 1998 Debug */

int __cdecl _fseek(FILE *_File,long _Offset,int _Origin)

{
  code *pcVar1;
  int iVar2;
  long lVar3;
  
  if ((_File == (FILE *)0x0) &&
     (iVar2 = __CrtDbgReport(2,"fseek.c",0x92,0,"str != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    iVar2 = (*pcVar1)();
    return iVar2;
  }
  if (((_File->_flag & 0x83) == 0) || (((_Origin != 0 && (_Origin != 1)) && (_Origin != 2)))) {
    crt_errno = 0x16;
    iVar2 = -1;
  }
  else {
    _File->_flag = _File->_flag & 0xffffffef;
    if (_Origin == 1) {
      lVar3 = _ftell(_File);
      _Offset = _Offset + lVar3;
      _Origin = 0;
    }
    __flush(_File);
    if ((_File->_flag & 0x80) == 0) {
      if ((((_File->_flag & 1) != 0) && ((_File->_flag & 8) != 0)) && ((_File->_flag & 0x400) == 0))
      {
        _File->_bufsiz = 0x200;
      }
    }
    else {
      _File->_flag = _File->_flag & 0xfffffffc;
    }
    lVar3 = __lseek(_File->_file,_Offset,_Origin);
    if (lVar3 == -1) {
      iVar2 = -1;
    }
    else {
      iVar2 = 0;
    }
  }
  return iVar2;
}

/* 005f6920 crt */
#define DAT_006e69f0 (*(undefined4 *)((u8 *)&g.d_006e69f0))
#define local_20 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_14 (*(char * *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(char * *)(frame_ + FRAME_OFF(24)))
/* Library Function - Single Match
    _ftell
   
   Library: Visual Studio 1998 Debug */

long __cdecl _ftell(FILE *_File)

{
  uint _FileHandle;
  code *pcVar1;
  int iVar2;
  long lVar3;
  char *pcVar4;
  undefined1 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((_File == (FILE *)0x0) && (iVar2 = __CrtDbgReport(2,"ftell.c",99,0,"str != NULL"), iVar2 == 1)
     ) {
    pcVar1 = (code *)swi(3);
    lVar3 = (*pcVar1)();
    return lVar3;
  }
  _FileHandle = _File->_file;
  if (_File->_cnt < 0) {
    _File->_cnt = 0;
  }
  local_20 = __lseek(_FileHandle,0,1);
  if (local_20 < 0) {
    local_1c = -1;
  }
  else if ((_File->_flag & 0x108U) == 0) {
    local_1c = local_20 - _File->_cnt;
  }
  else {
    local_1c = (int)_File->_ptr - (int)_File->_base;
    if ((_File->_flag & 3) == 0) {
      if ((_File->_flag & 0x80) == 0) {
        crt_errno = 0x16;
        return -1;
      }
    }
    else if ((*(byte *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0) >> 3)) + 4 +
                       (_FileHandle & 0x1f) * 8) & 0x80) != 0) {
      for (local_8 = _File->_base; local_8 < _File->_ptr; local_8 = local_8 + 1) {
        if (*local_8 == '\n') {
          local_1c = local_1c + 1;
        }
      }
    }
    if (local_20 != 0) {
      if ((_File->_flag & 1) != 0) {
        if (_File->_cnt == 0) {
          local_1c = 0;
        }
        else {
          local_14 = _File->_ptr + (_File->_cnt - (int)_File->_base);
          if (((int)*(char *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0) >> 3))
                              + 4 + (_FileHandle & 0x1f) * 8) & 0x80U) != 0) {
            lVar3 = __lseek(_FileHandle,0,2);
            if (lVar3 == local_20) {
              pcVar4 = _File->_base + (int)local_14;
              for (local_8 = _File->_base; local_8 < pcVar4; local_8 = local_8 + 1) {
                if (*local_8 == '\n') {
                  local_14 = local_14 + 1;
                }
              }
              if ((_File->_flag & 0x2000) != 0) {
                local_14 = local_14 + 1;
              }
            }
            else {
              __lseek(_FileHandle,local_20,0);
              if (((local_14 < (char *)0x201) && ((_File->_flag & 8) != 0)) &&
                 ((_File->_flag & 0x400) == 0)) {
                local_14 = (char *)0x200;
              }
              else {
                local_14 = (char *)_File->_bufsiz;
              }
              if ((*(byte *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0) >> 3)) +
                             4 + (_FileHandle & 0x1f) * 8) & 4) != 0) {
                local_14 = local_14 + 1;
              }
            }
          }
          local_20 = local_20 - (int)local_14;
        }
      }
      local_1c = local_20 + local_1c;
    }
  }
  return local_1c;
}
#undef DAT_006e69f0
#undef local_20
#undef local_1c
#undef local_14
#undef local_8

/* 005f6bd0: written by hand in src/crt/printf.c */

/* 005f6c60: written by hand in src/crt/asm.c */

/* 005f6c90 crt */
#define _DAT_00639fac (*(undefined4 *)((u8 *)&g.d_00639fac))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __fpmath
   
   Library: Visual Studio 1998 Debug */

void __cdecl __fpmath(int param_1)

{
  __cfltcvt_init();
  _DAT_00639fac = __ms_p5_mp_test_fdiv();
  __setdefaultprecision();
  return;
}
#undef _DAT_00639fac

/* 005f6cc0 crt */
void __cdecl FUN_005f6cc0(void)

{
  return;
}

/* 005f6cd0 crt */
/* Library Function - Single Match
    __cfltcvt_init
   
   Library: Visual Studio 1998 Debug */

void __cdecl __cfltcvt_init(void)

{
  PTR___fptrap_0063aee0 = __cfltcvt;
  PTR___fptrap_0063aee4 = __cropzeros;
  PTR___fptrap_0063aee8 = __fassign;
  PTR___fptrap_0063aeec = __forcdecpt;
  PTR___fptrap_0063aef0 = __positive;
  PTR___fptrap_0063aef4 = __cfltcvt;
  return;
}

/* 005f6d20 crt */
undefined4 __cdecl FUN_005f6d20(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_00639fa8;
  DAT_00639fa8 = param_1;
  return uVar1;
}

/* 005f6d50 crt */
/* Library Function - Single Match
    _memcmp
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

int __cdecl _memcmp(void *_Buf1,void *_Buf2,size_t _Size)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  byte bVar4;
  uint uVar5;
  byte bVar6;
  uint *puVar7;
  uint *puVar8;
  bool bVar9;
  
  if (_Size != 0) {
    if ((((uint)_Buf1 | (uint)_Buf2) & 3) == 0) {
      uVar2 = _Size & 3;
      uVar5 = _Size >> 2;
      bVar9 = false;
      puVar7 = _Buf1;
      puVar8 = _Buf2;
      if (uVar5 != 0) {
        do {
          _Buf1 = puVar7;
          _Buf2 = puVar8;
          if (uVar5 == 0) break;
          uVar5 = uVar5 - 1;
          _Buf2 = puVar8 + 1;
          _Buf1 = puVar7 + 1;
          bVar9 = *puVar7 == *puVar8;
          puVar7 = _Buf1;
          puVar8 = _Buf2;
        } while (bVar9);
        if (!bVar9) {
          uVar2 = *(uint *)((int)_Buf1 + -4);
          uVar5 = *(uint *)((int)_Buf2 + -4);
          bVar9 = (byte)uVar2 < (byte)uVar5;
          if ((((byte)uVar2 == (byte)uVar5) &&
              (bVar4 = (byte)(uVar2 >> 8), bVar6 = (byte)(uVar5 >> 8), bVar9 = bVar4 < bVar6,
              bVar4 == bVar6)) &&
             (bVar4 = (byte)(uVar2 >> 0x10), bVar6 = (byte)(uVar5 >> 0x10), bVar9 = bVar4 < bVar6,
             bVar4 == bVar6)) {
            bVar9 = (byte)(uVar2 >> 0x18) < (byte)(uVar5 >> 0x18);
          }
          goto LAB_005f6dca;
        }
      }
      if (uVar2 != 0) {
        uVar5 = *(uint *)_Buf1;
        uVar1 = *(uint *)_Buf2;
        bVar9 = (byte)uVar5 < (byte)uVar1;
        if ((byte)uVar5 != (byte)uVar1) {
LAB_005f6dca:
          return (1 - (uint)bVar9) - (uint)(bVar9 != 0);
        }
        iVar3 = 0;
        if (uVar2 != 1) {
          bVar6 = (byte)(uVar5 >> 8);
          bVar4 = (byte)(uVar1 >> 8);
          bVar9 = bVar6 < bVar4;
          if (bVar6 != bVar4) goto LAB_005f6dca;
          iVar3 = 0;
          if (uVar2 != 2) {
            bVar9 = (uVar5 & 0xff0000) < (uVar1 & 0xff0000);
            if ((uVar5 & 0xff0000) != (uVar1 & 0xff0000)) goto LAB_005f6dca;
            iVar3 = uVar2 - 3;
          }
        }
        return iVar3;
      }
    }
    else {
      if ((_Size & 1) == 0) goto LAB_005f6d7d;
      bVar9 = *(byte *)_Buf1 < *(byte *)_Buf2;
      if (*(byte *)_Buf1 != *(byte *)_Buf2) goto LAB_005f6dca;
      _Buf1 = (void *)((int)_Buf1 + 1);
      _Buf2 = (void *)((int)_Buf2 + 1);
      for (_Size = _Size - 1; _Size != 0; _Size = _Size - 2) {
LAB_005f6d7d:
        bVar9 = *(byte *)_Buf1 < *(byte *)_Buf2;
        if ((*(byte *)_Buf1 != *(byte *)_Buf2) ||
           (bVar9 = *(byte *)((int)_Buf1 + 1) < *(byte *)((int)_Buf2 + 1),
           *(byte *)((int)_Buf1 + 1) != *(byte *)((int)_Buf2 + 1))) goto LAB_005f6dca;
        _Buf2 = (void *)((int)_Buf2 + 2);
        _Buf1 = (void *)((int)_Buf1 + 2);
      }
    }
  }
  return 0;
}

/* 005f6e00 crt */
#define DAT_0063a078 (*(int *)((u8 *)&g.d_0063a078))
/* Library Function - Single Match
    __strcmpi
   
   Library: Visual Studio 1998 Debug */

int __cdecl __strcmpi(char *_Str1,char *_Str2)

{
  char cVar1;
  uint uVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  char cVar6;
  int _C;
  int iVar7;
  
  if (DAT_0063a078 == 0) {
    bVar5 = 0xff;
    do {
      do {
        cVar6 = '\0';
        if (bVar5 == 0) goto LAB_005f6e4e;
        bVar5 = *_Str2;
        _Str2 = _Str2 + 1;
        bVar4 = *_Str1;
        _Str1 = _Str1 + 1;
      } while (bVar4 == bVar5);
      bVar3 = bVar5 + 0xbf + (-((byte)(bVar5 + 0xbf) < 0x1a) & 0x20U) + 0x41;
      bVar4 = bVar4 + 0xbf;
      bVar5 = bVar4 + (-(bVar4 < 0x1a) & 0x20U) + 0x41;
    } while (bVar5 == bVar3);
    cVar6 = (bVar5 < bVar3) * -2 + '\x01';
LAB_005f6e4e:
    iVar7 = (int)cVar6;
  }
  else {
    _C = 0;
    iVar7 = 0xff;
    do {
      do {
        if ((char)iVar7 == '\0') {
          return iVar7;
        }
        cVar6 = *_Str2;
        iVar7 = CONCAT31((int3)((uint)iVar7 >> 8),cVar6);
        _Str2 = _Str2 + 1;
        cVar1 = *_Str1;
        _C = CONCAT31((int3)((uint)_C >> 8),cVar1);
        _Str1 = _Str1 + 1;
      } while (cVar6 == cVar1);
      _C = _tolower(_C);
      iVar7 = _tolower(iVar7);
    } while ((byte)_C == (byte)iVar7);
    uVar2 = (uint)((byte)_C < (byte)iVar7);
    iVar7 = (1 - uVar2) - (uint)(uVar2 != 0);
  }
  return iVar7;
}
#undef DAT_0063a078

/* 005f6e90: written by hand in src/crt/startup.c */

/* 005f70e0 crt */
/* Library Function - Single Match
    __amsg_exit
   
   Library: Visual Studio 1998 Debug */

void __cdecl __amsg_exit(int param_1)

{
  if (DAT_00639fcc == 1) {
    __FF_MSGBANNER();
  }
  __NMSG_WRITE(param_1);
  (*(code *)PTR___exit_00639fc8)(0xff);
  return;
}

/* 005f7120 crt */
int __cdecl FUN_005f7120(uint param_1)

{
  return (param_1 ^ (int)param_1 >> 0x1f) - ((int)param_1 >> 0x1f);
}

/* 005f7140 crt */
/* Library Function - Single Match
    __getcwd
   
   Library: Visual Studio 1998 Debug */

char * __cdecl __getcwd(char *_DstBuf,int _SizeInBytes)

{
  char *pcVar1;
  
  pcVar1 = __getdcwd(0,_DstBuf,_SizeInBytes);
  return pcVar1;
}

/* 005f7170 crt */
#define DAT_00639f18 (*(undefined4 *)((u8 *)&g.d_00639f18))
#define local_118 (*(CHAR (*)[260])(frame_ + FRAME_OFF(0)))
#define local_14 (*(DWORD *)(frame_ + FRAME_OFF(260)))
#define local_10 (*(char (*)[4])(frame_ + FRAME_OFF(264)))
#define local_c (*(LPSTR *)(frame_ + FRAME_OFF(268)))
#define local_8 (*(char * *)(frame_ + FRAME_OFF(272)))
/* Library Function - Single Match
    __getdcwd
   
   Library: Visual Studio 1998 Debug */

char * __cdecl __getdcwd(int _Drive,char *_DstBuf,int _SizeInBytes)

{
  int iVar1;
  char *pcVar2;
  uint _Size;
  undefined1 frame_[FRAME_OFF(280)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (_Drive == 0) {
    local_14 = GetCurrentDirectoryA(0x104,local_118);
  }
  else {
    iVar1 = __validdrive(_Drive);
    if (iVar1 == 0) {
      crt_errno = 0xd;
      DAT_00639f18 = 0xf;
      return (char *)0x0;
    }
    local_10[0] = (char)_Drive + '@';
    local_10[1] = 0x3a;
    local_10[2] = 0x2e;
    local_10[3] = 0;
    local_14 = GetFullPathNameA(local_10,0x104,local_118,&local_c);
  }
  if ((local_14 == 0) || (local_14 = local_14 + 1, 0x104 < local_14)) {
    pcVar2 = (char *)0x0;
  }
  else {
    local_8 = _DstBuf;
    if (_DstBuf == (char *)0x0) {
      _Size = local_14;
      if ((int)local_14 <= _SizeInBytes) {
        _Size = _SizeInBytes;
      }
      local_8 = _malloc(_Size);
      if (local_8 == (char *)0x0) {
        crt_errno = 0xc;
        return (char *)0x0;
      }
    }
    else if (_SizeInBytes < (int)local_14) {
      crt_errno = 0x22;
      return (char *)0x0;
    }
    pcVar2 = (char *)FUN_005f22d0(local_8,local_118);
  }
  return pcVar2;
}
#undef DAT_00639f18
#undef local_118
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 005f72b0 crt */
#define local_c (*(char (*)[8])(frame_ + FRAME_OFF(4)))
/* Library Function - Single Match
    __validdrive
   
   Library: Visual Studio 1998 Debug */

int __cdecl __validdrive(uint param_1)

{
  int iVar1;
  UINT UVar2;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 == 0) {
    iVar1 = 1;
  }
  else {
    local_c[0] = (char)param_1 + '@';
    local_c[1] = 0x3a;
    local_c[2] = 0x5c;
    local_c[3] = 0;
    UVar2 = GetDriveTypeA(local_c);
    if ((UVar2 == 0) || (UVar2 == 1)) {
      iVar1 = 0;
    }
    else {
      iVar1 = 1;
    }
  }
  return iVar1;
}
#undef local_c

/* 005f7320: written by hand in src/crt/time.c */

/* 005f74b0 crt */
/* Library Function - Single Match
    _strncat
   
   Library: Visual Studio 1998 Debug */

char * __cdecl _strncat(char *_Dest,char *_Source,size_t _Count)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  uint *puVar6;
  
  puVar5 = (uint *)_Dest;
  if (_Count == 0) {
    return _Dest;
  }
  do {
    if (((uint)puVar5 & 3) == 0) goto LAB_005f74da;
    uVar4 = *puVar5;
    puVar5 = (uint *)((int)puVar5 + 1);
  } while ((byte)uVar4 != 0);
  goto LAB_005f750b;
  while( true ) {
    if ((uVar4 & 0xff0000) == 0) {
      puVar6 = (uint *)((int)puVar6 + 2);
      goto LAB_005f751b;
    }
    if ((uVar4 & 0xff000000) == 0) break;
LAB_005f74da:
    do {
      puVar6 = puVar5;
      puVar5 = puVar6 + 1;
    } while (((*puVar6 ^ 0xffffffff ^ *puVar6 + 0x7efefeff) & 0x81010100) == 0);
    uVar4 = *puVar6;
    if ((char)uVar4 == '\0') goto LAB_005f751b;
    if ((char)(uVar4 >> 8) == '\0') {
      puVar6 = (uint *)((int)puVar6 + 1);
      goto LAB_005f751b;
    }
  }
LAB_005f750b:
  puVar6 = (uint *)((int)puVar5 + -1);
LAB_005f751b:
  if (((uint)_Source & 3) == 0) {
    uVar3 = _Count >> 2;
  }
  else {
    do {
      bVar1 = (byte)*(uint *)_Source;
      uVar4 = (uint)bVar1;
      _Source = (char *)((int)_Source + 1);
      if (bVar1 == 0) goto LAB_005f756a;
      *(byte *)puVar6 = bVar1;
      puVar6 = (uint *)((int)puVar6 + 1);
      _Count = _Count - 1;
      if (_Count == 0) goto LAB_005f7560;
    } while (((uint)_Source & 3) != 0);
    uVar3 = _Count >> 2;
  }
  do {
    if (uVar3 == 0) {
      for (uVar4 = _Count & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        uVar3 = *(uint *)_Source;
        _Source = (char *)((int)_Source + 1);
        *(byte *)puVar6 = (byte)uVar3;
        puVar6 = (uint *)((int)puVar6 + 1);
        if ((byte)uVar3 == 0) {
          return _Dest;
        }
      }
LAB_005f7560:
      *(byte *)puVar6 = 0;
      return _Dest;
    }
    uVar2 = *(uint *)_Source;
    uVar4 = *(uint *)_Source;
    _Source = (char *)((int)_Source + 4);
    if (((uVar2 ^ 0xffffffff ^ uVar2 + 0x7efefeff) & 0x81010100) != 0) {
      if ((char)uVar4 == '\0') {
LAB_005f756a:
        *(byte *)puVar6 = (byte)uVar4;
        return _Dest;
      }
      if ((char)(uVar4 >> 8) == '\0') {
        *(short *)puVar6 = (short)uVar4;
        return _Dest;
      }
      if ((uVar4 & 0xff0000) == 0) {
        *(short *)puVar6 = (short)uVar4;
        *(byte *)((int)puVar6 + 2) = 0;
        return _Dest;
      }
      if ((uVar4 & 0xff000000) == 0) {
        *puVar6 = uVar4;
        return _Dest;
      }
    }
    *puVar6 = uVar4;
    puVar6 = puVar6 + 1;
    uVar3 = uVar3 - 1;
  } while( true );
}

/* 005f75e0 crt */
#define _DAT_0063aca4 (*(undefined4 *)((u8 *)&g.d_0063aca4))
#define local_328 (*(CHAR (*)[260])(frame_ + FRAME_OFF(0)))
#define local_224 (*(char * *)(frame_ + FRAME_OFF(260)))
#define local_220 (*(char (*)[540])(frame_ + FRAME_OFF(264)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __assert
   
   Library: Visual Studio 1998 Debug */

void __cdecl __assert(char *param_1,char *param_2,int param_3)

{
  code *pcVar1;
  DWORD DVar2;
  size_t sVar3;
  size_t sVar4;
  int iVar5;
  undefined1 frame_[FRAME_OFF(808)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((DAT_00639fcc == 1) || ((DAT_00639fcc == 0 && (DAT_00639fd0 == 1)))) {
    if ((_DAT_0063aca4 & 0x10c) == 0) {
      _setvbuf((FILE *)&DAT_0063ac98,(char *)0x0,4,0);
    }
    _fprintf((FILE *)&DAT_0063ac98,s_Assertion_failed___s__file__s__l_00639fe0,param_1,param_2,
             param_3);
    _fflush((FILE *)&DAT_0063ac98);
  }
  else {
    FUN_005f22d0(local_220,"Assertion failed!");
    FUN_005f22e0(local_220,PTR_DAT_0063a010);
    FUN_005f22e0(local_220,"Program: ");
    DVar2 = GetModuleFileNameA((HMODULE)0x0,local_328,0x104);
    if (DVar2 == 0) {
      FUN_005f22d0(local_328,"<program name unknown>");
    }
    local_224 = local_328;
    sVar3 = _strlen(local_328);
    if (0x3c < sVar3 + 0xb) {
      sVar3 = _strlen(local_328);
      local_224 = local_224 + (sVar3 - 0x31);
      _strncpy(local_224,PTR_DAT_0063a008,3);
    }
    FUN_005f22e0(local_220,local_224);
    FUN_005f22e0(local_220,PTR_DAT_0063a00c);
    FUN_005f22e0(local_220,"File: ");
    local_224 = param_2;
    sVar3 = _strlen(param_2);
    if (0x3c < sVar3 + 8) {
      sVar3 = _strlen(param_2);
      local_224 = local_224 + (sVar3 - 0x34);
      _strncpy(local_224,PTR_DAT_0063a008,3);
    }
    FUN_005f22e0(local_220,local_224);
    FUN_005f22e0(local_220,PTR_DAT_0063a00c);
    FUN_005f22e0(local_220,"Line: ");
    iVar5 = 10;
    sVar3 = _strlen(local_220);
    __itoa(param_3,local_220 + sVar3,iVar5);
    FUN_005f22e0(local_220,PTR_DAT_0063a010);
    FUN_005f22e0(local_220,"Expression: ");
    sVar3 = _strlen(param_1);
    sVar4 = _strlen(local_220);
    if (sVar3 + sVar4 + 0xb0 < 0x21d) {
      FUN_005f22e0(local_220,param_1);
    }
    else {
      sVar3 = _strlen(local_220);
      _strncat(local_220,param_1,0x21c - (sVar3 + 0xb1));
      FUN_005f22e0(local_220,PTR_DAT_0063a008);
    }
    FUN_005f22e0(local_220,PTR_DAT_0063a010);
    FUN_005f22e0(local_220,
                 "For information on how your program can cause an assertion\nfailure, see the Visual C++ documentation on asserts"
                );
    FUN_005f22e0(local_220,PTR_DAT_0063a010);
    FUN_005f22e0(local_220,"(Press Retry to debug the application - JIT must be enabled)");
    iVar5 = ___crtMessageBoxA(local_220,"Microsoft Visual C++ Runtime Library",0x12012);
    if (iVar5 == 3) {
      _raise(0x16);
      __exit(3);
    }
    if (iVar5 == 4) {
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    if (iVar5 == 5) {
      return;
    }
  }
                    /* WARNING: Subroutine does not return */
  _abort();
}
#undef _DAT_0063aca4
#undef local_328
#undef local_224
#undef local_220

/* 005f79a0: written by hand in src/crt/eh.c */

/* 005f7ac0: written by hand in src/crt/eh.c */

/* 005f7d70: written by hand in src/crt/eh.c */

/* 005f7e90: written by hand in src/crt/eh.c */

/* 005f7f80: written by hand in src/crt/eh.c */

/* 005f8050: written by hand in src/crt/eh.c */

/* 005f8160 crt */
/* Library Function - Multiple Matches With Different Base Names
    int __cdecl ArrayUnwindFilter(struct _EXCEPTION_POINTERS *)
    int __cdecl FrameUnwindFilter(struct _EXCEPTION_POINTERS *)
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl FUN_005f8160(undefined4 *param_1)

{
  if (*(int *)*param_1 == -0x1f928c9d) {
    terminate();
  }
  return 0;
}

/* 005f81b0: written by hand in src/crt/eh.c */

/* 005f8290: written by hand in src/crt/eh.c */

/* 005f83f0 crt */
/* Library Function - Single Match
    int __cdecl ExFilterRethrow(struct _EXCEPTION_POINTERS *)
   
   Library: Visual Studio 1998 Debug */

int __cdecl ExFilterRethrow(_EXCEPTION_POINTERS *param_1)

{
  PEXCEPTION_RECORD pEVar1;
  int iVar2;
  
  pEVar1 = param_1->ExceptionRecord;
  if ((((pEVar1->ExceptionCode == 0xe06d7363) && (pEVar1->NumberParameters == 3)) &&
      (pEVar1->ExceptionInformation[0] == 0x19930520)) && (pEVar1->ExceptionInformation[2] == 0)) {
    iVar2 = 1;
  }
  else {
    iVar2 = 0;
  }
  return iVar2;
}

/* 005f8460: written by hand in src/crt/eh.c */

/* 005f8740: written by hand in src/crt/eh.c */

/* 005f87e0: written by hand in src/crt/eh.c */

/* 005f8830 crt */
/* WARNING: Restarted to delay deadcode elimination for space: stack */
/* Library Function - Single Match
    __CallSettingFrame@12
   
   Library: Visual Studio 1998 Debug */

undefined4 __stdcall __CallSettingFrame_12(undefined4 param_1,undefined4 param_2,int param_3)

{
  code *pcVar1;
  undefined4 uVar2;
  
  pcVar1 = (code *)FUN_005f1d95(param_3);
  (*pcVar1)();
  if (param_3 == 0x100) {
    param_3 = 2;
  }
  uVar2 = FUN_005f1d95(param_3);
  return uVar2;
}

/* 005f8880 crt */
#define DAT_0063a024 (*(code * *)((u8 *)&g.d_0063a024))
#define uStack_14 (*(undefined4 *)(frame_ + FRAME_OFF(4)))
#define puStack_10 (*(undefined1 * *)(frame_ + FRAME_OFF(8)))
#define puStack_c (*(undefined * *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(16)))
/* Library Function - Single Match
    void __cdecl terminate(void)
   
   Library: Visual Studio 1998 Debug */

void __cdecl terminate(void)

{
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  puStack_c = &DAT_0061e480;
  puStack_10 = &LAB_005f9298;
  if (DAT_0063a024 != (code *)0x0) {
    local_8 = 1;
    (*DAT_0063a024)();
  }
  local_8 = 0xffffffff;
                    /* WARNING: Subroutine does not return */
  _abort();
}
#undef DAT_0063a024
#undef uStack_14
#undef puStack_10
#undef puStack_c
#undef local_8

/* 005f8920 crt */
/* Library Function - Single Match
    void __cdecl unexpected(void)
   
   Library: Visual Studio 1998 Debug */

void __cdecl unexpected(void)

{
  if (PTR_terminate_0063a028 != (undefined *)0x0) {
    (*(code *)PTR_terminate_0063a028)();
  }
  terminate();
  return;
}

/* 005f8950 crt */
#define uStack_14 (*(undefined4 *)(frame_ + FRAME_OFF(4)))
#define puStack_10 (*(undefined1 * *)(frame_ + FRAME_OFF(8)))
#define puStack_c (*(undefined * *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(16)))
/* Library Function - Single Match
    void __cdecl _inconsistency(void)
   
   Library: Visual Studio 1998 Debug */

void __cdecl _inconsistency(void)

{
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  puStack_c = &DAT_0061e498;
  puStack_10 = &LAB_005f9298;
  if (PTR_terminate_0063a02c != (undefined *)0x0) {
    local_8 = 1;
    (*(code *)PTR_terminate_0063a02c)();
  }
  local_8 = 0xffffffff;
  terminate();
  return;
}
#undef uStack_14
#undef puStack_10
#undef puStack_c
#undef local_8

/* 005f89f0 crt */
/* Library Function - Single Match
    __CrtDbgBreak
   
   Library: Visual Studio 1998 Debug */

void __cdecl __CrtDbgBreak(void)

{
  DebugBreak();
  return;
}

/* 005f8a10 crt */
/* Library Function - Single Match
    __CrtSetReportMode
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl __CrtSetReportMode(int param_1,uint param_2)

{
  undefined4 uVar1;
  
  if ((param_1 < 0) || (2 < param_1)) {
    uVar1 = 0xffffffff;
  }
  else if (param_2 == 0xffffffff) {
    uVar1 = *(undefined4 *)(&DAT_0063a038 + param_1 * 4);
  }
  else if ((param_2 & 0xfffffff8) == 0) {
    uVar1 = *(undefined4 *)(&DAT_0063a038 + param_1 * 4);
    *(uint *)(&DAT_0063a038 + param_1 * 4) = param_2;
  }
  else {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}

/* 005f8a90 crt */
/* Library Function - Single Match
    __CrtSetReportFile
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl __CrtSetReportFile(int param_1,int param_2)

{
  undefined4 uVar1;
  HANDLE pvVar2;
  
  if ((param_1 < 0) || (2 < param_1)) {
    uVar1 = 0xfffffffe;
  }
  else if (param_2 == -6) {
    uVar1 = *(undefined4 *)(&DAT_0063a048 + param_1 * 4);
  }
  else {
    uVar1 = *(undefined4 *)(&DAT_0063a048 + param_1 * 4);
    if (param_2 == -4) {
      pvVar2 = GetStdHandle(0xfffffff5);
      *(HANDLE *)(&DAT_0063a048 + param_1 * 4) = pvVar2;
    }
    else if (param_2 == -5) {
      pvVar2 = GetStdHandle(0xfffffff4);
      *(HANDLE *)(&DAT_0063a048 + param_1 * 4) = pvVar2;
    }
    else {
      *(int *)(&DAT_0063a048 + param_1 * 4) = param_2;
    }
  }
  return uVar1;
}

/* 005f8b40 crt */
#define DAT_006e6b30 (*(undefined4 *)((u8 *)&g.d_006e6b30))
undefined4 __cdecl FUN_005f8b40(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_006e6b30;
  DAT_006e6b30 = param_1;
  return uVar1;
}
#undef DAT_006e6b30

/* 005f8b70: written by hand in src/crt/heap.c */

/* 005f8f60 crt */
#define local_1114 (*(char * *)(frame_ + FRAME_OFF(4)))
#define local_1110 (*(char (*)[4036])(frame_ + FRAME_OFF(8)))
#define local_110 (*(int *)(frame_ + FRAME_OFF(4104)))
#define local_10c (*(CHAR (*)[188])(frame_ + FRAME_OFF(4108)))
/* Library Function - Single Match
    _CrtMessageWindow
   
   Library: Visual Studio 1998 Debug */

uint __cdecl _CrtMessageWindow(int param_1,int param_2,int param_3,char *param_4,int param_5)

{
  int iVar1;
  DWORD DVar2;
  size_t sVar3;
  char acStackY_14c [60];
  undefined4 uStackY_50;
  char *_Str;
  undefined1 frame_[FRAME_OFF(4376)] __attribute__((aligned(8)));  /* original stack frame */
  if ((param_5 == 0) &&
     (iVar1 = __CrtDbgReport(2,"dbgrpt.c",0x1da,0,"szUserMessage != NULL"), iVar1 == 1)) {
    __CrtDbgBreak();
  }
  DVar2 = GetModuleFileNameA((HMODULE)0x0,local_10c,0x104);
  if (DVar2 == 0) {
    FUN_005f22d0(local_10c,"<program name unknown>");
  }
  _Str = local_10c;
  sVar3 = _strlen(_Str);
  if (0x40 < sVar3) {
    sVar3 = _strlen(_Str);
    _Str = _Str + (sVar3 - 0x40);
    _strncpy(_Str,"...",3);
  }
  local_1114 = param_4;
  if ((param_4 != (char *)0x0) && (sVar3 = _strlen(param_4), 0x40 < sVar3)) {
    sVar3 = _strlen(param_4);
    local_1114 = param_4 + (sVar3 - 0x40);
    _strncpy(local_1114,"...",3);
  }
  uStackY_50 = 0x5f920b;
  iVar1 = __snprintf(local_1110,0x1000,
                     "Debug %s!\n\nProgram: %s%s%s%s%s%s%s%s%s%s%s\n\n(Press Retry to debug the application)"
                     ,(&PTR_s_Warning_0063a058)[param_1],_Str,
                     "\nModule: " + ((local_1114 != (char *)0x0) - 1 & 0xc924));
  if (iVar1 < 0) {
    FUN_005f22d0(local_1110,"_CrtDbgReport: String too long or IO Error");
  }
  local_110 = ___crtMessageBoxA(local_1110,"Microsoft Visual C++ Debug Library",0x12012);
  if (local_110 == 3) {
    _raise(0x16);
    __exit(3);
  }
  return (uint)(local_110 == 4);
}
#undef local_1114
#undef local_1110
#undef local_110
#undef local_10c

/* 005f9355 crt */
void __stdcall FUN_005f9355(int param_1)

{
  __local_unwind2(*(undefined4 *)(param_1 + 0x18),*(undefined4 *)(param_1 + 0x1c));
  return;
}

/* 005f9370: written by hand in src/crt/locale.c */

/* 005f9670 crt */
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(short * *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    _wcsncnt
   
   Library: Visual Studio 1998 Debug */

int __cdecl wcsncnt_005f9670(short *param_1,int param_2)

{
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = param_2;
  for (local_8 = param_1; (local_c != 0 && (*local_8 != 0)); local_8 = local_8 + 1) {
    local_c = local_c + -1;
  }
  if (*local_8 == 0) {
    param_2 = (int)local_8 - (int)param_1 >> 1;
  }
  return param_2;
}
#undef local_c
#undef local_8

/* 005f96e0: written by hand in src/crt/locale.c */

/* 005f9a00: written by hand in src/crt */

/* 005f9a70: written by hand in src/crt/locale.c */

/* 005f9b30 crt */
#define _DAT_0063aed8 (*(undefined4 *)((u8 *)&g.d_0063aed8))
#define local_20 (*(uint *)(frame_ + FRAME_OFF(0)))
#define local_18 (*(uint *)(frame_ + FRAME_OFF(8)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __openfile
   
   Library: Visual Studio 1998 Debug */

FILE * __cdecl __openfile(char *_Filename,char *_Mode,int _ShFlag,FILE *_File)

{
  char cVar1;
  code *pcVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  int iVar6;
  FILE *pFVar7;
  undefined1 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_20 = DAT_0063b274;
  bVar4 = false;
  bVar5 = false;
  if ((_Filename == (char *)0x0) &&
     (iVar6 = __CrtDbgReport(2,"_open.c",0x47,0,"filename != NULL"), iVar6 == 1)) {
    pcVar2 = (code *)swi(3);
    pFVar7 = (FILE *)(*pcVar2)();
    return pFVar7;
  }
  if ((_Mode == (char *)0x0) &&
     (iVar6 = __CrtDbgReport(2,"_open.c",0x48,0,"mode != NULL"), iVar6 == 1)) {
    pcVar2 = (code *)swi(3);
    pFVar7 = (FILE *)(*pcVar2)();
    return pFVar7;
  }
  if ((_File == (FILE *)0x0) &&
     (iVar6 = __CrtDbgReport(2,"_open.c",0x49,0,"str != NULL"), iVar6 == 1)) {
    pcVar2 = (code *)swi(3);
    pFVar7 = (FILE *)(*pcVar2)();
    return pFVar7;
  }
  cVar1 = *_Mode;
  if (cVar1 == 'a') {
    local_18 = 0x109;
    local_20 = local_20 | 2;
  }
  else if (cVar1 == 'r') {
    local_18 = 0;
    local_20 = local_20 | 1;
  }
  else {
    if (cVar1 != 'w') {
      return (FILE *)0x0;
    }
    local_18 = 0x301;
    local_20 = local_20 | 2;
  }
  bVar3 = true;
  while ((_Mode = _Mode + 1, *_Mode != '\0' && (bVar3))) {
    switch(*_Mode) {
    case '+':
      if ((local_18 & 2) == 0) {
        local_18 = local_18 & 0xfffffffe | 2;
        local_20 = local_20 & 0xfffffffc | 0x80;
      }
      else {
        bVar3 = false;
      }
      break;
    default:
      bVar3 = false;
      break;
    case 'D':
      if ((local_18 & 0x40) == 0) {
        local_18 = local_18 | 0x40;
      }
      else {
        bVar3 = false;
      }
      break;
    case 'R':
      if (bVar5) {
        bVar3 = false;
      }
      else {
        bVar5 = true;
        local_18 = local_18 | 0x10;
      }
      break;
    case 'S':
      if (bVar5) {
        bVar3 = false;
      }
      else {
        bVar5 = true;
        local_18 = local_18 | 0x20;
      }
      break;
    case 'T':
      if ((local_18 & 0x1000) == 0) {
        local_18 = local_18 | 0x1000;
      }
      else {
        bVar3 = false;
      }
      break;
    case 'b':
      if ((local_18 & 0xc000) == 0) {
        local_18 = local_18 | 0x8000;
      }
      else {
        bVar3 = false;
      }
      break;
    case 'c':
      if (bVar4) {
        bVar3 = false;
      }
      else {
        bVar4 = true;
        local_20 = local_20 | 0x4000;
      }
      break;
    case 'n':
      if (bVar4) {
        bVar3 = false;
      }
      else {
        bVar4 = true;
        local_20 = local_20 & 0xffffbfff;
      }
      break;
    case 't':
      if ((local_18 & 0xc000) == 0) {
        local_18 = local_18 | 0x4000;
      }
      else {
        bVar3 = false;
      }
    }
  }
  iVar6 = __sopen(_Filename,local_18,_ShFlag,0x1a4);
  if (iVar6 < 0) {
    _File = (FILE *)0x0;
  }
  else {
    _DAT_0063aed8 = _DAT_0063aed8 + 1;
    _File->_flag = local_20;
    _File->_cnt = 0;
    _File->_ptr = (char *)0x0;
    _File->_base = _File->_ptr;
    _File->_tmpfname = _File->_base;
    _File->_file = iVar6;
  }
  return _File;
}
#undef _DAT_0063aed8
#undef local_20
#undef local_18

/* 005f9ef0 crt */
#define local_c (*(FILE * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    __getstream
   
   Library: Visual Studio 1998 Debug */

FILE * __cdecl __getstream(void)

{
  undefined4 uVar1;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = (FILE *)0x0;
  local_8 = 0;
  do {
    if (DAT_006e69e0 <= local_8) {
LAB_005f9fab:
      if (local_c != (FILE *)0x0) {
        local_c->_cnt = 0;
        local_c->_flag = local_c->_cnt;
        local_c->_base = (char *)0x0;
        local_c->_ptr = local_c->_base;
        local_c->_tmpfname = local_c->_ptr;
        local_c->_file = -1;
      }
      return local_c;
    }
    if (*(int *)(DAT_006e5694 + local_8 * 4) == 0) {
      uVar1 = __malloc_dbg(0x20,2,"stream.c",0x55);
      *(undefined4 *)(DAT_006e5694 + local_8 * 4) = uVar1;
      if (*(int *)(DAT_006e5694 + local_8 * 4) != 0) {
        local_c = *(FILE **)(DAT_006e5694 + local_8 * 4);
      }
      goto LAB_005f9fab;
    }
    if ((*(byte *)(*(int *)(DAT_006e5694 + local_8 * 4) + 0xc) & 0x83) == 0) {
      local_c = *(FILE **)(DAT_006e5694 + local_8 * 4);
      goto LAB_005f9fab;
    }
    local_8 = local_8 + 1;
  } while( true );
}
#undef local_c
#undef local_8

/* 005fa010 crt */
#define DAT_00639f18 (*(undefined4 *)((u8 *)&g.d_00639f18))
#define DAT_006e69f0 (*(undefined4 *)((u8 *)&g.d_006e69f0))
#define DAT_006e6b2c (*(uint *)((u8 *)&g.d_006e6b2c))
#define local_8 (*(ulong *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    __close
   
   Library: Visual Studio 1998 Debug */

int __cdecl __close(int _FileHandle)

{
  intptr_t iVar1;
  intptr_t iVar2;
  HANDLE hObject;
  BOOL BVar3;
  int iVar4;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((DAT_006e6b2c <= (uint)_FileHandle) ||
     ((*(byte *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) + 4 +
                (_FileHandle & 0x1fU) * 8) & 1) == 0)) {
    crt_errno = 9;
    DAT_00639f18 = 0;
    return -1;
  }
  if ((_FileHandle == 1) || (_FileHandle == 2)) {
    iVar1 = __get_osfhandle(2);
    iVar2 = __get_osfhandle(1);
    if (iVar1 != iVar2) goto LAB_005fa099;
  }
  else {
LAB_005fa099:
    hObject = (HANDLE)__get_osfhandle(_FileHandle);
    BVar3 = CloseHandle(hObject);
    if (BVar3 == 0) {
      local_8 = GetLastError();
      goto LAB_005fa0c9;
    }
  }
  local_8 = 0;
LAB_005fa0c9:
  __free_osfhnd(_FileHandle);
  if (local_8 == 0) {
    *(undefined1 *)
     (*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) + 4 +
     (_FileHandle & 0x1fU) * 8) = 0;
    iVar4 = 0;
  }
  else {
    __dosmaperr(local_8);
    iVar4 = -1;
  }
  return iVar4;
}
#undef DAT_00639f18
#undef DAT_006e69f0
#undef DAT_006e6b2c
#undef local_8

/* 005fa120 crt */
/* Library Function - Single Match
    __freebuf
   
   Library: Visual Studio 1998 Debug */

void __cdecl __freebuf(FILE *_File)

{
  code *pcVar1;
  int iVar2;
  
  if (_File == (FILE *)0x0) {
    iVar2 = __CrtDbgReport(2,"_freebuf.c",0x30,0,"stream != NULL");
    if (iVar2 == 1) {
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
  }
  if (((_File->_flag & 0x83) != 0) && ((_File->_flag & 8) != 0)) {
    __free_dbg(_File->_base,2);
    _File->_flag = _File->_flag & 0xfffffbf7;
    _File->_ptr = (char *)0x0;
    _File->_base = _File->_ptr;
    _File->_cnt = 0;
  }
  return;
}

/* 005fa1b0 crt */
/* Library Function - Single Match
    _fflush
   
   Library: Visual Studio 1998 Debug */

int __cdecl _fflush(FILE *_File)

{
  int iVar1;
  
  if (_File == (FILE *)0x0) {
    iVar1 = flsall(0);
  }
  else {
    iVar1 = __flush(_File);
    if (iVar1 == 0) {
      if ((_File->_flag & 0x4000) == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = __commit(_File->_file);
        if (iVar1 == 0) {
          iVar1 = 0;
        }
        else {
          iVar1 = -1;
        }
      }
    }
    else {
      iVar1 = -1;
    }
  }
  return iVar1;
}

/* 005fa230 crt */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    __flush
   
   Library: Visual Studio 1998 Debug */

int __cdecl __flush(FILE *_File)

{
  uint _MaxCharCount;
  uint uVar1;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  if (((((byte)_File->_flag & 3) == 2) && ((_File->_flag & 0x108U) != 0)) &&
     (_MaxCharCount = (int)_File->_ptr - (int)_File->_base, 0 < (int)_MaxCharCount)) {
    uVar1 = __write(_File->_file,_File->_base,_MaxCharCount);
    if (uVar1 == _MaxCharCount) {
      if ((_File->_flag & 0x80) != 0) {
        _File->_flag = _File->_flag & 0xfffffffd;
      }
    }
    else {
      _File->_flag = _File->_flag | 0x20;
      local_8 = -1;
    }
  }
  _File->_ptr = _File->_base;
  _File->_cnt = 0;
  return local_8;
}
#undef local_8

/* 005fa2f0 crt */
/* Library Function - Single Match
    __flushall
   
   Library: Visual Studio 1998 Debug */

int __cdecl __flushall(void)

{
  int iVar1;
  
  iVar1 = flsall(1);
  return iVar1;
}

/* 005fa310 crt */
#define local_10 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    _flsall
   
   Library: Visual Studio 1998 Debug */

int __cdecl flsall(int param_1)

{
  int iVar1;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  local_c = 0;
  for (local_10 = 0; local_10 < DAT_006e69e0; local_10 = local_10 + 1) {
    if ((*(int *)(DAT_006e5694 + local_10 * 4) != 0) &&
       ((*(byte *)(*(int *)(DAT_006e5694 + local_10 * 4) + 0xc) & 0x83) != 0)) {
      if (param_1 == 1) {
        iVar1 = _fflush(*(FILE **)(DAT_006e5694 + local_10 * 4));
        if (iVar1 != -1) {
          local_8 = local_8 + 1;
        }
      }
      else if (((param_1 == 0) &&
               ((*(byte *)(*(int *)(DAT_006e5694 + local_10 * 4) + 0xc) & 2) != 0)) &&
              (iVar1 = _fflush(*(FILE **)(DAT_006e5694 + local_10 * 4)), iVar1 == -1)) {
        local_c = -1;
      }
    }
  }
  if (param_1 == 1) {
    local_c = local_8;
  }
  return local_c;
}
#undef local_10
#undef local_c
#undef local_8

/* 005fa410 crt */
#define DAT_006e69f0 (*(undefined4 *)((u8 *)&g.d_006e69f0))
#define local_1c (*(undefined * *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(uint *)(frame_ + FRAME_OFF(16)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(24)))
/* Library Function - Single Match
    __flsbuf
   
   Library: Visual Studio 1998 Debug */

int __cdecl __flsbuf(int _Ch,FILE *_File)

{
  code *pcVar1;
  FILE *_File_00;
  int iVar2;
  uint uVar3;
  undefined1 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((_File == (FILE *)0x0) &&
     (iVar2 = __CrtDbgReport(2,&DAT_0061e724,0x69,0,"str != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    iVar2 = (*pcVar1)();
    return iVar2;
  }
  _File_00 = _File;
  uVar3 = _File->_file;
  if (((_File->_flag & 0x82) == 0) || ((_File->_flag & 0x40) != 0)) {
    _File->_flag = _File->_flag | 0x20;
    uVar3 = 0xffffffff;
  }
  else {
    if ((_File->_flag & 1) != 0) {
      _File->_cnt = 0;
      if ((CRT_FEOF(_File)) == 0) {
        _File->_flag = _File->_flag | 0x20;
        return -1;
      }
      _File->_ptr = _File->_base;
      _File->_flag = _File->_flag & 0xfffffffe;
    }
    _File->_flag = _File->_flag | 2;
    _File->_flag = _File->_flag & 0xffffffef;
    _File->_cnt = 0;
    local_10 = _File->_cnt;
    if (((_File->_flag & 0x10cU) == 0) &&
       (((_File != (FILE *)&DAT_0063ac78 && (_File != (FILE *)&DAT_0063ac98)) ||
        (iVar2 = __isatty(uVar3), iVar2 == 0)))) {
      __getbuf(_File_00);
    }
    if ((_File_00->_flag & 0x108U) == 0) {
      local_8 = 1;
      local_10 = __write(uVar3,&_Ch,1);
    }
    else {
      if (((int)_File_00->_ptr - (int)_File_00->_base < 0) &&
         (iVar2 = __CrtDbgReport(2,&DAT_0061e724,0xa0,0,
                                 "(\"inconsistent IOB fields\", stream->_ptr - stream->_base >= 0)")
         , iVar2 == 1)) {
        pcVar1 = (code *)swi(3);
        iVar2 = (*pcVar1)();
        return iVar2;
      }
      local_8 = (int)_File_00->_ptr - (int)_File_00->_base;
      _File_00->_ptr = _File_00->_base + 1;
      _File_00->_cnt = _File_00->_bufsiz + -1;
      if ((int)local_8 < 1) {
        if (uVar3 == 0xffffffff) {
          local_1c = &DAT_0063a420;
        }
        else {
          local_1c = (undefined *)
                     (*(int *)((int)&DAT_006e69f0 + ((int)(uVar3 & 0xffffffe0) >> 3)) +
                     (uVar3 & 0x1f) * 8);
        }
        if ((local_1c[4] & 0x20) != 0) {
          __lseek(uVar3,0,2);
        }
      }
      else {
        local_10 = __write(uVar3,_File_00->_base,local_8);
      }
      *_File_00->_base = (char)_Ch;
    }
    if (local_10 == local_8) {
      uVar3 = _Ch & 0xff;
    }
    else {
      _File_00->_flag = _File_00->_flag | 0x20;
      uVar3 = 0xffffffff;
    }
  }
  return uVar3;
}
#undef DAT_006e69f0
#undef local_1c
#undef local_10
#undef local_8

/* 005fa6b0: written by hand in src/crt/printf.c */

/* 005fb440 crt */
#define local_8 (*(uint *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    _write_char
   
   Library: Visual Studio 1998 Debug */

void __cdecl write_char(int param_1,FILE *param_2,int *param_3)

{
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  param_2->_cnt = param_2->_cnt + -1;
  if (param_2->_cnt < 0) {
    local_8 = __flsbuf(param_1,param_2);
  }
  else {
    *param_2->_ptr = (char)param_1;
    local_8 = (uint)(byte)*param_2->_ptr;
    param_2->_ptr = param_2->_ptr + 1;
  }
  if (local_8 == 0xffffffff) {
    *param_3 = -1;
  }
  else {
    *param_3 = *param_3 + 1;
  }
  return;
}
#undef local_8

/* 005fb4c0 crt */
/* Library Function - Single Match
    _write_multi_char
   
   Library: Visual Studio 1998 Debug */

void __cdecl write_multi_char(undefined4 param_1,int param_2,undefined4 param_3,int *param_4)

{
  do {
    if (param_2 < 1) {
      return;
    }
    write_char(param_1,param_3,param_4);
    param_2 = param_2 + -1;
  } while (*param_4 != -1);
  return;
}

/* 005fb510 crt */
/* Library Function - Single Match
    _write_string
   
   Library: Visual Studio 1998 Debug */

void __cdecl write_string(char *param_1,int param_2,undefined4 param_3,int *param_4)

{
  do {
    if (param_2 < 1) {
      return;
    }
    write_char((int)*param_1,param_3,param_4);
    param_1 = param_1 + 1;
    param_2 = param_2 + -1;
  } while (*param_4 != -1);
  return;
}

/* 005fb570 crt */
/* Library Function - Single Match
    _get_int_arg
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl get_int_arg(int *param_1)

{
  *param_1 = *param_1 + 4;
  return *(undefined4 *)(*param_1 + -4);
}

/* 005fb590 crt */
/* Library Function - Single Match
    _get_int64_arg
   
   Library: Visual Studio 1998 Debug */

undefined8 __cdecl get_int64_arg(int *param_1)

{
  *param_1 = *param_1 + 8;
  return *(undefined8 *)(*param_1 + -8);
}

/* 005fb5c0 crt */
/* Library Function - Single Match
    _get_short_arg
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl get_short_arg(int *param_1)

{
  *param_1 = *param_1 + 4;
  return CONCAT22((short)((uint)*param_1 >> 0x10),*(undefined2 *)(*param_1 + -4));
}

/* 005fb5e0 crt */
/* Library Function - Single Match
    __allmul
   
   Library: Visual Studio 1998 Debug */

int __stdcall __allmul(int param_1,int param_2,int param_3,int param_4)

{
  if (param_4 == 0 && param_2 == 0) {
    return param_1 * param_3;
  }
  return param_1 * param_3;
}

/* 005fb620 crt */
#define _DAT_0063aed8 (*(undefined4 *)((u8 *)&g.d_0063aed8))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __stbuf
   
   Library: Visual Studio 1998 Debug */

int __cdecl __stbuf(FILE *_File)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((_File == (FILE *)0x0) &&
     (iVar2 = __CrtDbgReport(2,"_sftbuf.c",0x41,0,"str != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    iVar2 = (*pcVar1)();
    return iVar2;
  }
  iVar2 = __isatty(_File->_file);
  if (iVar2 == 0) {
    iVar2 = 0;
  }
  else {
    if (_File == (FILE *)&DAT_0063ac78) {
      local_c = 0;
    }
    else {
      if (_File != (FILE *)&DAT_0063ac98) {
        return 0;
      }
      local_c = 1;
    }
    _DAT_0063aed8 = _DAT_0063aed8 + 1;
    if ((_File->_flag & 0x10cU) == 0) {
      if (*(int *)(&DAT_0063a2b0 + local_c * 4) == 0) {
        uVar3 = __malloc_dbg(0x1000,2,"_sftbuf.c",0x5e);
        *(undefined4 *)(&DAT_0063a2b0 + local_c * 4) = uVar3;
        if (*(int *)(&DAT_0063a2b0 + local_c * 4) == 0) {
          return 0;
        }
      }
      _File->_base = *(char **)(&DAT_0063a2b0 + local_c * 4);
      _File->_ptr = _File->_base;
      _File->_bufsiz = 0x1000;
      _File->_cnt = _File->_bufsiz;
      _File->_flag = _File->_flag | 0x1102;
      iVar2 = 1;
    }
    else {
      iVar2 = 0;
    }
  }
  return iVar2;
}
#undef _DAT_0063aed8
#undef local_c

/* 005fb770 crt */
/* Library Function - Single Match
    __ftbuf
   
   Library: Visual Studio 1998 Debug */

void __cdecl __ftbuf(int _Flag,FILE *_File)

{
  code *pcVar1;
  int iVar2;
  
  if (((_Flag != 0) && (_Flag != 1)) &&
     (iVar2 = __CrtDbgReport(2,"_sftbuf.c",0x96,0,"flag == 0 || flag == 1"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  if (_Flag == 0) {
    if ((_File->_flag & 0x1000) != 0) {
      __flush(_File);
    }
  }
  else if ((_File->_flag & 0x1000) != 0) {
    __flush(_File);
    _File->_flag = _File->_flag & 0xffffeeff;
    _File->_bufsiz = 0;
    _File->_ptr = (char *)0x0;
    _File->_base = _File->_ptr;
  }
  return;
}

/* 005fb830 crt */
#define DAT_00639f18 (*(undefined4 *)((u8 *)&g.d_00639f18))
#define DAT_006e69f0 (*(undefined4 *)((u8 *)&g.d_006e69f0))
#define DAT_006e6b2c (*(uint *)((u8 *)&g.d_006e6b2c))
#define local_20 (*(char (*)[4])(frame_ + FRAME_OFF(0)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(void * *)(frame_ + FRAME_OFF(8)))
#define local_14 (*(DWORD *)(frame_ + FRAME_OFF(12)))
#define local_10 (*(char * *)(frame_ + FRAME_OFF(16)))
#define local_c (*(DWORD *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(char * *)(frame_ + FRAME_OFF(24)))
/* Library Function - Single Match
    __read
   
   Library: Visual Studio 1998 Debug */

int __cdecl __read(int _FileHandle,void *_DstBuf,uint _MaxCharCount)

{
  BOOL BVar1;
  undefined1 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((uint)_FileHandle < DAT_006e6b2c) &&
     ((*(byte *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) + 4 +
                (_FileHandle & 0x1fU) * 8) & 1) != 0)) {
    local_1c = 0;
    local_18 = _DstBuf;
    if ((_MaxCharCount == 0) ||
       ((*(byte *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) + 4 +
                  (_FileHandle & 0x1fU) * 8) & 2) != 0)) {
      local_1c = 0;
    }
    else {
      if (((*(byte *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) + 4 +
                     (_FileHandle & 0x1fU) * 8) & 0x48) != 0) &&
         (*(char *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) + 5 +
                   (_FileHandle & 0x1fU) * 8) != '\n')) {
        *(undefined1 *)_DstBuf =
             *(undefined1 *)
              (*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) + 5 +
              (_FileHandle & 0x1fU) * 8);
        local_18 = (void *)((int)_DstBuf + 1);
        local_1c = 1;
        _MaxCharCount = _MaxCharCount - 1;
        *(undefined1 *)
         (*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) + 5 +
         (_FileHandle & 0x1fU) * 8) = 10;
      }
      BVar1 = ReadFile(*(HANDLE *)
                        (*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) +
                        (_FileHandle & 0x1fU) * 8),local_18,_MaxCharCount,&local_14,
                       (LPOVERLAPPED)0x0);
      if (BVar1 == 0) {
        local_c = GetLastError();
        if (local_c == 5) {
          crt_errno = 9;
          local_1c = -1;
          DAT_00639f18 = 5;
        }
        else if (local_c == 0x6d) {
          local_1c = 0;
        }
        else {
          __dosmaperr(local_c);
          local_1c = -1;
        }
      }
      else {
        local_1c = local_1c + local_14;
        if ((*(byte *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) + 4 +
                      (_FileHandle & 0x1fU) * 8) & 0x80) != 0) {
          if ((local_14 == 0) || (*(char *)_DstBuf != '\n')) {
            *(byte *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) + 4 +
                     (_FileHandle & 0x1fU) * 8) =
                 *(byte *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) +
                           4 + (_FileHandle & 0x1fU) * 8) & 0xfb;
          }
          else {
            *(byte *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) + 4 +
                     (_FileHandle & 0x1fU) * 8) =
                 *(byte *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) +
                           4 + (_FileHandle & 0x1fU) * 8) | 4;
          }
          local_10 = _DstBuf;
          local_8 = _DstBuf;
          while (local_8 < (char *)(local_1c + (int)_DstBuf)) {
            if (*local_8 == '\x1a') {
              if ((*(byte *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3))
                             + 4 + (_FileHandle & 0x1fU) * 8) & 0x40) == 0) {
                *(byte *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) + 4
                         + (_FileHandle & 0x1fU) * 8) =
                     *(byte *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)
                                       ) + 4 + (_FileHandle & 0x1fU) * 8) | 2;
              }
              break;
            }
            if (*local_8 == '\r') {
              if (local_8 < (char *)((int)_DstBuf + local_1c + -1)) {
                if (local_8[1] == '\n') {
                  local_8 = local_8 + 2;
                  *local_10 = '\n';
                }
                else {
                  *local_10 = *local_8;
                  local_8 = local_8 + 1;
                }
                local_10 = local_10 + 1;
              }
              else {
                local_8 = local_8 + 1;
                local_c = 0;
                BVar1 = ReadFile(*(HANDLE *)
                                  (*(int *)((int)&DAT_006e69f0 +
                                           ((int)(_FileHandle & 0xffffffe0U) >> 3)) +
                                  (_FileHandle & 0x1fU) * 8),local_20,1,&local_14,(LPOVERLAPPED)0x0)
                ;
                if (BVar1 == 0) {
                  local_c = GetLastError();
                }
                if ((local_c == 0) && (local_14 != 0)) {
                  if ((*(byte *)(*(int *)((int)&DAT_006e69f0 +
                                         ((int)(_FileHandle & 0xffffffe0U) >> 3)) + 4 +
                                (_FileHandle & 0x1fU) * 8) & 0x48) == 0) {
                    if ((_DstBuf == local_10) && (local_20[0] == '\n')) {
                      *local_10 = '\n';
                      local_10 = local_10 + 1;
                    }
                    else {
                      __lseek(_FileHandle,-1,1);
                      if (local_20[0] != '\n') {
                        *local_10 = '\r';
                        local_10 = local_10 + 1;
                      }
                    }
                  }
                  else {
                    if (local_20[0] == '\n') {
                      *local_10 = '\n';
                    }
                    else {
                      *local_10 = '\r';
                      *(char *)(*(int *)((int)&DAT_006e69f0 +
                                        ((int)(_FileHandle & 0xffffffe0U) >> 3)) + 5 +
                               (_FileHandle & 0x1fU) * 8) = local_20[0];
                    }
                    local_10 = local_10 + 1;
                  }
                }
                else {
                  *local_10 = '\r';
                  local_10 = local_10 + 1;
                }
              }
            }
            else {
              *local_10 = *local_8;
              local_8 = local_8 + 1;
              local_10 = local_10 + 1;
            }
          }
          local_1c = (int)local_10 - (int)_DstBuf;
        }
      }
    }
  }
  else {
    crt_errno = 9;
    DAT_00639f18 = 0;
    local_1c = -1;
  }
  return local_1c;
}
#undef DAT_00639f18
#undef DAT_006e69f0
#undef DAT_006e6b2c
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 005fbcd0 crt */
#define DAT_00639f18 (*(ulong *)((u8 *)&g.d_00639f18))
#define DAT_006e69f0 (*(undefined4 *)((u8 *)&g.d_006e69f0))
#define DAT_006e6b2c (*(uint *)((u8 *)&g.d_006e6b2c))
#define local_424 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_41c (*(DWORD *)(frame_ + FRAME_OFF(12)))
#define local_418 (*(char (*)[1028])(frame_ + FRAME_OFF(16)))
#define local_14 (*(DWORD *)(frame_ + FRAME_OFF(1044)))
#define local_10 (*(ulong *)(frame_ + FRAME_OFF(1048)))
#define local_c (*(char * *)(frame_ + FRAME_OFF(1052)))
#define local_8 (*(char * *)(frame_ + FRAME_OFF(1056)))
/* Library Function - Single Match
    __write
   
   Library: Visual Studio 1998 Debug */

int __cdecl __write(int _FileHandle,void *_Buf,uint _MaxCharCount)

{
  char cVar1;
  BOOL BVar2;
  undefined1 frame_[FRAME_OFF(1064)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((uint)_FileHandle < DAT_006e6b2c) &&
     ((*(byte *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) + 4 +
                (_FileHandle & 0x1fU) * 8) & 1) != 0)) {
    local_14 = 0;
    local_424 = 0;
    if (_MaxCharCount == 0) {
      local_424 = 0;
    }
    else {
      if ((*(byte *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) + 4 +
                    (_FileHandle & 0x1fU) * 8) & 0x20) != 0) {
        __lseek(_FileHandle,0,2);
      }
      if ((*(byte *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) + 4 +
                    (_FileHandle & 0x1fU) * 8) & 0x80) == 0) {
        BVar2 = WriteFile(*(HANDLE *)
                           (*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) +
                           (_FileHandle & 0x1fU) * 8),_Buf,_MaxCharCount,&local_41c,
                          (LPOVERLAPPED)0x0);
        if (BVar2 == 0) {
          local_10 = GetLastError();
        }
        else {
          local_10 = 0;
          local_14 = local_41c;
        }
      }
      else {
        local_8 = _Buf;
        local_10 = 0;
        do {
          if (_MaxCharCount <= (uint)((int)local_8 - (int)_Buf)) break;
          local_c = local_418;
          while (((int)local_c - (int)local_418 < 0x400 &&
                 ((uint)((int)local_8 - (int)_Buf) < _MaxCharCount))) {
            cVar1 = *local_8;
            local_8 = local_8 + 1;
            if (cVar1 == '\n') {
              local_424 = local_424 + 1;
              *local_c = '\r';
              local_c = local_c + 1;
            }
            *local_c = cVar1;
            local_c = local_c + 1;
          }
          BVar2 = WriteFile(*(HANDLE *)
                             (*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3))
                             + (_FileHandle & 0x1fU) * 8),local_418,(int)local_c - (int)local_418,
                            &local_41c,(LPOVERLAPPED)0x0);
          if (BVar2 == 0) {
            local_10 = GetLastError();
            break;
          }
          local_14 = local_14 + local_41c;
        } while ((int)local_c - (int)local_418 <= (int)local_41c);
      }
      if (local_14 == 0) {
        if (local_10 == 0) {
          if (((*(byte *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) + 4
                         + (_FileHandle & 0x1fU) * 8) & 0x40) == 0) || (*(char *)_Buf != '\x1a')) {
            crt_errno = 0x1c;
            DAT_00639f18 = 0;
            local_424 = -1;
          }
          else {
            local_424 = 0;
          }
        }
        else {
          if (local_10 == 5) {
            crt_errno = 9;
            DAT_00639f18 = local_10;
          }
          else {
            __dosmaperr(local_10);
          }
          local_424 = -1;
        }
      }
      else {
        local_424 = local_14 - local_424;
      }
    }
  }
  else {
    crt_errno = 9;
    DAT_00639f18 = 0;
    local_424 = -1;
  }
  return local_424;
}
#undef DAT_00639f18
#undef DAT_006e69f0
#undef DAT_006e6b2c
#undef local_424
#undef local_41c
#undef local_418
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 005fbfd0 crt */
#define DAT_00639f18 (*(ulong *)((u8 *)&g.d_00639f18))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    __dosmaperr
   
   Library: Visual Studio 1998 Debug */

void __cdecl __dosmaperr(ulong param_1)

{
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  DAT_00639f18 = param_1;
  local_8 = 0;
  while( true ) {
    if (0x2c < local_8) {
      if ((param_1 < 0x13) || (0x24 < param_1)) {
        if ((param_1 < 0xbc) || (0xca < param_1)) {
          crt_errno = 0x16;
        }
        else {
          crt_errno = 8;
        }
      }
      else {
        crt_errno = 0xd;
      }
      return;
    }
    if (*(ulong *)(&DAT_0063a2b8 + local_8 * 8) == param_1) break;
    local_8 = local_8 + 1;
  }
  crt_errno = *(iptr *)(&DAT_0063a2bc + local_8 * 8);
  return;
}
#undef DAT_00639f18
#undef local_8

/* 005fc090: written by hand in src/crt/locale.c */

/* 005fc160: written by hand in src/crt/startup.c */

/* 005fc490 crt */
#define DAT_006e69f0 (*(undefined4 *)((u8 *)&g.d_006e69f0))
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    __ioterm
   
   Library: Visual Studio 1998 Debug */

void __cdecl __ioterm(void)

{
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; local_8 < 0x40; local_8 = local_8 + 1) {
    if ((&DAT_006e69f0)[local_8] != 0) {
      __free_dbg((&DAT_006e69f0)[local_8],2);
    }
  }
  return;
}
#undef DAT_006e69f0
#undef local_8

/* 005fc500 crt */
#define _DAT_0063aed8 (*(undefined4 *)((u8 *)&g.d_0063aed8))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __getbuf
   
   Library: Visual Studio 1998 Debug */

void __cdecl __getbuf(FILE *_File)

{
  code *pcVar1;
  int iVar2;
  char *pcVar3;
  
  if (_File == (FILE *)0x0) {
    iVar2 = __CrtDbgReport(2,"_getbuf.c",0x2e,0,"str != NULL");
    if (iVar2 == 1) {
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
  }
  _DAT_0063aed8 = _DAT_0063aed8 + 1;
  pcVar3 = (char *)__malloc_dbg(0x1000,2,"_getbuf.c",0x3b);
  _File->_base = pcVar3;
  if (_File->_base == (char *)0x0) {
    _File->_flag = _File->_flag | 4;
    _File->_base = (char *)&_File->_charbuf;
    _File->_bufsiz = 2;
  }
  else {
    _File->_flag = _File->_flag | 8;
    _File->_bufsiz = 0x1000;
  }
  _File->_ptr = _File->_base;
  _File->_cnt = 0;
  return;
}
#undef _DAT_0063aed8

/* 005fc5c0 crt */
int __cdecl FUN_005fc5c0(int param_1)

{
  return param_1 + 0x20;
}

/* 005fc5e0: written by hand in src/crt/locale.c */

/* 005fc720 crt */
#define DAT_006e54a0 (*(undefined4 *)((u8 *)&g.d_006e54a0))
undefined4 __cdecl FUN_005fc720(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_006e54a0;
  DAT_006e54a0 = param_1;
  return uVar1;
}
#undef DAT_006e54a0

/* 005fc750 crt */
#define DAT_006e54a0 (*(undefined4 *)((u8 *)&g.d_006e54a0))
undefined4 __cdecl FUN_005fc750(void)

{
  return DAT_006e54a0;
}
#undef DAT_006e54a0

/* 005fc770 crt */
#define DAT_006e54a0 (*(code * *)((u8 *)&g.d_006e54a0))
/* Library Function - Single Match
    __callnewh
   
   Library: Visual Studio 1998 Debug */

int __cdecl __callnewh(size_t _Size)

{
  int iVar1;
  
  if ((DAT_006e54a0 != (code *)0x0) && (iVar1 = (*DAT_006e54a0)(_Size), iVar1 != 0)) {
    return 1;
  }
  return 0;
}
#undef DAT_006e54a0

/* 005fc7b0 crt */
#define DAT_0063a428 (*(undefined4 *)((u8 *)&g.d_0063a428))
/* Library Function - Single Match
    __malloc_base
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl __malloc_base(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = __nh_malloc_base(param_1,DAT_0063a428);
  return uVar1;
}
#undef DAT_0063a428

/* 005fc7e0 crt */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    __nh_malloc_base
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl __nh_malloc_base(uint param_1,int param_2)

{
  int iVar1;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 < 0xffffffe1) {
    if (param_1 == 0) {
      param_1 = 1;
    }
    do {
      if (param_1 < 0xffffffe1) {
        local_8 = __heap_alloc_base(param_1);
      }
      else {
        local_8 = 0;
      }
      if (local_8 != 0) {
        return local_8;
      }
      if (param_2 == 0) {
        return 0;
      }
      iVar1 = __callnewh(param_1);
    } while (iVar1 != 0);
  }
  return 0;
}
#undef local_8

/* 005fc880 crt */
#define DAT_0063ac54 (*(uint *)((u8 *)&g.d_0063ac54))
/* Library Function - Single Match
    __heap_alloc_base
   
   Library: Visual Studio 1998 Debug */

LPVOID __cdecl __heap_alloc_base(int param_1)

{
  uint dwBytes;
  LPVOID pvVar1;
  
  dwBytes = param_1 + 0xfU & 0xfffffff0;
  if ((DAT_0063ac54 < dwBytes) ||
     (pvVar1 = (LPVOID)___sbh_alloc_block(param_1 + 0xfU >> 4), pvVar1 == (LPVOID)0x0)) {
    pvVar1 = HeapAlloc(DAT_006e69e4,0,dwBytes);
  }
  return pvVar1;
}
#undef DAT_0063ac54

/* 005fc8f0 crt */
undefined4 __cdecl FUN_005fc8f0(void)

{
  return 1;
}

/* 005fc910 crt */
#define DAT_0063ac54 (*(uint *)((u8 *)&g.d_0063ac54))
#define local_14 (*(undefined4 *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_c (*(LPVOID *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(16)))
/* Library Function - Single Match
    __expand_base
   
   Library: Visual Studio 1998 Debug */

LPVOID __cdecl __expand_base(LPVOID param_1,uint param_2)

{
  int iVar1;
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_2 < 0xffffffe1) {
    if (param_2 == 0) {
      param_2 = 0x10;
    }
    else {
      param_2 = param_2 + 0xf & 0xfffffff0;
    }
    local_10 = ___sbh_find_block(param_1,&local_14,&local_8);
    if (local_10 == 0) {
      local_c = HeapReAlloc(DAT_006e69e4,0x10,param_1,param_2);
    }
    else {
      local_c = (LPVOID)0x0;
      if ((param_2 <= DAT_0063ac54) &&
         (iVar1 = ___sbh_resize_block(local_14,local_8,local_10,param_2 >> 4), iVar1 != 0)) {
        local_c = param_1;
      }
    }
  }
  else {
    local_c = (LPVOID)0x0;
  }
  return local_c;
}
#undef DAT_0063ac54
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 005fc9e0 crt */
#define DAT_0063a428 (*(int *)((u8 *)&g.d_0063a428))
#define DAT_0063ac54 (*(uint *)((u8 *)&g.d_0063ac54))
#define local_18 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(byte * *)(frame_ + FRAME_OFF(8)))
#define local_c (*(LPVOID *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(16)))
/* Library Function - Single Match
    __realloc_base
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl __realloc_base(LPVOID param_1,uint param_2)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 == (LPVOID)0x0) {
    uVar1 = __malloc_base(param_2);
  }
  else if (param_2 == 0) {
    __free_base(param_1);
    uVar1 = 0;
  }
  else {
    if (param_2 < 0xffffffe1) {
      if (param_2 == 0) {
        param_2 = 0x10;
      }
      else {
        param_2 = param_2 + 0xf & 0xfffffff0;
      }
    }
    do {
      local_c = (LPVOID)0x0;
      if (param_2 < 0xffffffe1) {
        local_10 = (byte *)___sbh_find_block(param_1,&local_18,&local_8);
        if (local_10 == (byte *)0x0) {
          local_c = HeapReAlloc(DAT_006e69e4,0,param_1,param_2);
        }
        else {
          if (param_2 < DAT_0063ac54) {
            iVar2 = ___sbh_resize_block(local_18,local_8,local_10,param_2 >> 4);
            if (iVar2 == 0) {
              local_c = (LPVOID)___sbh_alloc_block(param_2 >> 4);
              if (local_c != (LPVOID)0x0) {
                local_14 = (uint)*local_10 << 4;
                uVar3 = param_2;
                if (local_14 <= param_2) {
                  uVar3 = local_14;
                }
                FUN_005f2110(local_c,param_1,uVar3);
                ___sbh_free_block(local_18,local_8,local_10);
              }
            }
            else {
              local_c = param_1;
            }
          }
          if ((local_c == (LPVOID)0x0) &&
             (local_c = HeapAlloc(DAT_006e69e4,0,param_2), local_c != (LPVOID)0x0)) {
            local_14 = (uint)*local_10 << 4;
            uVar3 = param_2;
            if (local_14 <= param_2) {
              uVar3 = local_14;
            }
            FUN_005f2110(local_c,param_1,uVar3);
            ___sbh_free_block(local_18,local_8,local_10);
          }
        }
      }
      if (local_c != (LPVOID)0x0) {
        return local_c;
      }
      if (DAT_0063a428 == 0) {
        return 0;
      }
      iVar2 = __callnewh(param_2);
    } while (iVar2 != 0);
    uVar1 = 0;
  }
  return uVar1;
}
#undef DAT_0063a428
#undef DAT_0063ac54
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 005fcbf0: written by hand in src/crt/heap.c */

/* 005fcc60 crt */
#define DAT_00639f18 (*(undefined4 *)((u8 *)&g.d_00639f18))
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    __heapchk
   
   Library: Visual Studio 1998 Debug */

int __cdecl __heapchk(void)

{
  int iVar1;
  BOOL BVar2;
  DWORD DVar3;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = -2;
  iVar1 = ___sbh_heap_check();
  if (iVar1 < 0) {
    local_8 = -4;
  }
  BVar2 = HeapValidate(DAT_006e69e4,0,(LPCVOID)0x0);
  if (BVar2 == 0) {
    DVar3 = GetLastError();
    if (DVar3 == 0x78) {
      DAT_00639f18 = 0x78;
      crt_errno = 0x28;
    }
    else {
      local_8 = -4;
    }
  }
  return local_8;
}
#undef DAT_00639f18
#undef local_8

/* 005fcce0 crt */
/* Library Function - Single Match
    __heapset
   
   Library: Visual Studio 1998 Debug */

int __cdecl __heapset(uint _Fill)

{
  int iVar1;
  
  iVar1 = __heapchk();
  return iVar1;
}

/* 005fcd00 crt */
/* Library Function - Single Match
    __heap_init
   
   Library: Visual Studio 1998 Debug */

int __cdecl __heap_init(void)

{
  int iVar1;
  
  DAT_006e69e4 = HeapCreate(1,0x1000,0);
  if (DAT_006e69e4 == (HANDLE)0x0) {
    iVar1 = 0;
  }
  else {
    iVar1 = ___sbh_new_region();
    if (iVar1 == 0) {
      HeapDestroy(DAT_006e69e4);
      iVar1 = 0;
    }
    else {
      iVar1 = 1;
    }
  }
  return iVar1;
}

/* 005fcd60 crt */
#define local_8 (*(undefined ** *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    __heap_term
   
   Library: Visual Studio 1998 Debug */

void __cdecl __heap_term(void)

{
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = &PTR_LOOP_0063a438;
  do {
    if (local_8[0x204] != (undefined *)0x0) {
      VirtualFree(local_8[0x204],0,0x8000);
    }
    local_8 = (undefined **)*local_8;
  } while (local_8 != &PTR_LOOP_0063a438);
  HeapDestroy(DAT_006e69e4);
  return;
}
#undef local_8

/* 005fcdc0 crt */
#define DAT_0063ac54 (*(undefined4 *)((u8 *)&g.d_0063ac54))
undefined4 __cdecl FUN_005fcdc0(void)

{
  return DAT_0063ac54;
}
#undef DAT_0063ac54

/* 005fcde0 crt */
#define DAT_0063ac54 (*(uint *)((u8 *)&g.d_0063ac54))
/* Library Function - Single Match
    __set_sbh_threshold
   
   Library: Visual Studio 1998 Debug */

bool __cdecl __set_sbh_threshold(int param_1)

{
  uint uVar1;
  
  uVar1 = param_1 + 0xfU & 0xfffffff0;
  if (uVar1 < 0x781) {
    DAT_0063ac54 = uVar1;
  }
  return uVar1 < 0x781;
}
#undef DAT_0063ac54

/* 005fce30 crt */
#define DAT_0063ac48 (*(int *)((u8 *)&g.d_0063ac48))
#define local_10 (*(undefined ** *)(frame_ + FRAME_OFF(0)))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(undefined4 * *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    ___sbh_new_region
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl ___sbh_new_region(void)

{
  LPVOID pvVar1;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (DAT_0063ac48 == 0) {
    local_10 = &PTR_LOOP_0063a438;
  }
  else {
    local_10 = HeapAlloc(DAT_006e69e4,0,0x814);
    if (local_10 == (undefined **)0x0) {
      return 0;
    }
  }
  local_8 = VirtualAlloc((LPVOID)0x0,0x400000,0x2000,4);
  if (local_8 != (undefined4 *)0x0) {
    pvVar1 = VirtualAlloc(local_8,0x10000,0x1000,4);
    if (pvVar1 != (LPVOID)0x0) {
      if (local_10 == &PTR_LOOP_0063a438) {
        if (PTR_LOOP_0063a438 == (undefined *)0x0) {
          PTR_LOOP_0063a438 = (undefined *)&PTR_LOOP_0063a438;
        }
        if (PTR_LOOP_0063a43c == (undefined *)0x0) {
          PTR_LOOP_0063a43c = (undefined *)&PTR_LOOP_0063a438;
        }
      }
      else {
        *local_10 = (undefined *)&PTR_LOOP_0063a438;
        local_10[1] = PTR_LOOP_0063a43c;
        PTR_LOOP_0063a43c = (undefined *)local_10;
        *(undefined ***)local_10[1] = local_10;
      }
      local_10[0x204] = (undefined *)local_8;
      local_10[2] = (undefined *)0x0;
      local_10[3] = (undefined *)0x10;
      for (local_c = 0; local_c < 0x400; local_c = local_c + 1) {
        if (local_c < 0x10) {
          *(undefined1 *)(local_c + 0x10 + (int)local_10) = 0xf0;
        }
        else {
          *(undefined1 *)(local_c + 0x10 + (int)local_10) = 0xff;
        }
        *(undefined1 *)(local_c + 0x410 + (int)local_10) = 0xf1;
      }
      _memset(local_8,0,0x10000);
      for (; local_8 < local_10[0x204] + 0x10000; local_8 = local_8 + 0x400) {
        *local_8 = local_8 + 2;
        local_8[1] = 0xf0;
        *(undefined1 *)(local_8 + 0x3e) = 0xff;
      }
      return local_10;
    }
    VirtualFree(local_8,0,0x8000);
  }
  if (local_10 != &PTR_LOOP_0063a438) {
    HeapFree(DAT_006e69e4,0,local_10);
  }
  return 0;
}
#undef DAT_0063ac48
#undef local_10
#undef local_c
#undef local_8

/* 005fd040 crt */
#define DAT_0063ac48 (*(undefined4 *)((u8 *)&g.d_0063ac48))
/* Library Function - Single Match
    ___sbh_release_region
   
   Library: Visual Studio 1998 Debug */

void __cdecl ___sbh_release_region(undefined **param_1)

{
  VirtualFree(param_1[0x204],0,0x8000);
  if (param_1 == (undefined **)PTR_LOOP_0063ac4c) {
    PTR_LOOP_0063ac4c = param_1[1];
  }
  if (param_1 == &PTR_LOOP_0063a438) {
    DAT_0063ac48 = 0;
  }
  else {
    *(undefined **)param_1[1] = *param_1;
    *(undefined **)(*param_1 + 4) = param_1[1];
    HeapFree(DAT_006e69e4,0,param_1);
  }
  return;
}
#undef DAT_0063ac48

/* 005fd0d0 crt */
#define local_18 (*(undefined * *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_c (*(char * *)(frame_ + FRAME_OFF(12)))
/* Library Function - Single Match
    ___sbh_decommit_pages
   
   Library: Visual Studio 1998 Debug */

undefined * __cdecl ___sbh_decommit_pages(int param_1)

{
  undefined *puVar1;
  BOOL BVar2;
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_18 = PTR_LOOP_0063a43c;
  do {
    puVar1 = local_18;
    if (*(int *)(local_18 + 0x810) != 0) {
      local_14 = 0;
      local_c = local_18 + 0x40f;
      for (local_10 = 0x3ff; -1 < local_10; local_10 = local_10 + -1) {
        if ((*local_c == -0x10) &&
           (BVar2 = VirtualFree((LPVOID)(*(int *)(local_18 + 0x810) + local_10 * 0x1000),0x1000,
                                0x4000), BVar2 != 0)) {
          *local_c = -1;
          DAT_0063ac50 = DAT_0063ac50 + -1;
          if ((*(int *)(local_18 + 0xc) == -1) || (local_10 < *(int *)(local_18 + 0xc))) {
            *(int *)(local_18 + 0xc) = local_10;
          }
          local_14 = local_14 + 1;
          param_1 = param_1 + -1;
          if (param_1 == 0) break;
        }
        local_c = local_c + -1;
      }
      puVar1 = *(undefined **)(local_18 + 4);
      if ((local_14 != 0) && (local_18[0x10] == -1)) {
        local_10 = 1;
        for (local_c = local_18 + 0x11; (local_10 < 0x400 && (*local_c == -1));
            local_c = local_c + 1) {
          local_10 = local_10 + 1;
        }
        if (local_10 == 0x400) {
          ___sbh_release_region(local_18);
        }
      }
    }
    local_18 = puVar1;
    if ((PTR_LOOP_0063a43c == local_18) || (param_1 < 1)) {
      return local_18;
    }
  } while( true );
}
#undef local_18
#undef local_14
#undef local_10
#undef local_c

/* 005fd250 crt */
#define local_c (*(undefined ** *)(frame_ + FRAME_OFF(4)))
/* Library Function - Single Match
    ___sbh_find_block
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl ___sbh_find_block(undefined *param_1,undefined4 *param_2,uint *param_3)

{
  uint uVar1;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = &PTR_LOOP_0063a438;
  while (((local_c[0x204] == (undefined *)0x0 || (param_1 <= local_c[0x204])) ||
         (local_c[0x204] + 0x400000 <= param_1))) {
    local_c = (undefined **)*local_c;
    if (local_c == &PTR_LOOP_0063a438) {
      return 0;
    }
  }
  *param_2 = local_c;
  uVar1 = (uint)param_1 & 0xfffff000;
  *param_3 = uVar1;
  return ((int)((int)param_1 - (uVar1 + 0x100)) >> 4) + 8 + uVar1;
}
#undef local_c

/* 005fd300 crt */
/* Library Function - Single Match
    ___sbh_free_block
   
   Library: Visual Studio 1998 Debug */

int __cdecl ___sbh_free_block(int param_1,int param_2,char *param_3)

{
  int iVar1;
  
  iVar1 = param_2 - *(int *)(param_1 + 0x810) >> 0xc;
  *(char *)(iVar1 + 0x10 + param_1) = *(char *)(iVar1 + 0x10 + param_1) + *param_3;
  *param_3 = '\0';
  *(undefined1 *)(iVar1 + 0x410 + param_1) = 0xf1;
  if ((*(char *)(iVar1 + 0x10 + param_1) == -0x10) &&
     (DAT_0063ac50 = DAT_0063ac50 + 1, DAT_0063ac50 == 0x20)) {
    iVar1 = ___sbh_decommit_pages(0x10);
  }
  return iVar1;
}

/* 005fd390 crt */
#define local_18 (*(undefined ** *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(undefined * *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(undefined * *)(frame_ + FRAME_OFF(8)))
#define local_8 (*(undefined4 * *)(frame_ + FRAME_OFF(16)))
/* Library Function - Single Match
    ___sbh_alloc_block
   
   Library: Visual Studio 1998 Debug */

undefined * __cdecl ___sbh_alloc_block(uint param_1)

{
  int *piVar1;
  int iVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined4 *puVar5;
  undefined *puVar6;
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_18 = (undefined **)PTR_LOOP_0063ac4c;
  do {
    if (local_18[0x204] != (undefined *)0x0) {
      for (local_10 = local_18[2]; (int)local_10 < 0x400;
          local_10 = (undefined *)((int)local_10 + 1)) {
        if (((param_1 <= *(byte *)((int)local_10 + 0x10 + (int)local_18)) &&
            (*(char *)((int)local_10 + 0x10 + (int)local_18) != -1)) &&
           (param_1 < *(byte *)((int)local_10 + 0x410 + (int)local_18))) {
          iVar2 = ___sbh_alloc_block_from_page
                            ((int)local_18[0x204] + (int)local_10 * 0x1000,
                             (uint)*(byte *)((int)local_10 + 0x10 + (int)local_18),param_1);
          if (iVar2 != 0) {
            PTR_LOOP_0063ac4c = (undefined *)local_18;
            *(char *)((int)local_10 + 0x10 + (int)local_18) =
                 *(char *)((int)local_10 + 0x10 + (int)local_18) - (char)param_1;
            local_18[2] = local_10;
            return (undefined *)iVar2;
          }
          *(char *)((int)local_10 + 0x410 + (int)local_18) = (char)param_1;
        }
      }
      for (local_10 = (undefined *)0x0; (int)local_10 < (int)local_18[2];
          local_10 = (undefined *)((int)local_10 + 1)) {
        if (((param_1 <= *(byte *)((int)local_10 + 0x10 + (int)local_18)) &&
            (*(char *)((int)local_10 + 0x10 + (int)local_18) != -1)) &&
           (param_1 < *(byte *)((int)local_10 + 0x410 + (int)local_18))) {
          iVar2 = ___sbh_alloc_block_from_page
                            ((int)local_18[0x204] + (int)local_10 * 0x1000,
                             (uint)*(byte *)((int)local_10 + 0x10 + (int)local_18),param_1);
          if (iVar2 != 0) {
            PTR_LOOP_0063ac4c = (undefined *)local_18;
            *(char *)((int)local_10 + 0x10 + (int)local_18) =
                 *(char *)((int)local_10 + 0x10 + (int)local_18) - (char)param_1;
            local_18[2] = local_10;
            return (undefined *)iVar2;
          }
          *(char *)((int)local_10 + 0x410 + (int)local_18) = (char)param_1;
        }
      }
    }
    local_18 = (undefined **)*local_18;
  } while (local_18 != (undefined **)PTR_LOOP_0063ac4c);
  local_18 = &PTR_LOOP_0063a438;
  while ((local_18[0x204] == (undefined *)0x0 || (local_18[3] == (undefined *)0xffffffff))) {
    local_18 = (undefined **)*local_18;
    if (local_18 == &PTR_LOOP_0063a438) {
      puVar6 = (undefined *)___sbh_new_region();
      if (puVar6 != (undefined *)0x0) {
        piVar1 = *(int **)(puVar6 + 0x810);
        *(char *)(piVar1 + 2) = (char)param_1;
        PTR_LOOP_0063ac4c = puVar6;
        *piVar1 = (int)piVar1 + param_1 + 8;
        piVar1[1] = 0xf0 - param_1;
        puVar6[0x10] = puVar6[0x10] - (char)param_1;
        return (undefined *)(*(int *)(puVar6 + 0x810) + 0x100);
      }
      return (undefined *)0;
    }
  }
  puVar6 = local_18[3];
  puVar3 = puVar6 + 0x10;
  if (0x3ff < (int)puVar3) {
    puVar3 = (undefined *)0x400;
  }
  do {
    local_10 = puVar6 + 1;
    if ((int)puVar3 <= (int)local_10) break;
    puVar4 = puVar6 + 0x11;
    puVar6 = local_10;
  } while (puVar4[(int)local_18] == -1);
  puVar6 = local_18[3];
  puVar3 = local_18[0x204];
  puVar4 = VirtualAlloc(local_18[0x204] + (int)local_18[3] * 0x1000,
                        ((int)local_10 - (int)local_18[3]) * 0x1000,0x1000,4);
  if (puVar3 + (int)puVar6 * 0x1000 == puVar4) {
    local_14 = local_18[3];
    local_8 = (undefined4 *)(local_18[0x204] + (int)local_14 * 0x1000);
    for (; (int)local_14 < (int)local_10; local_14 = local_14 + 1) {
      _memset(local_8,0x1000,0);
      *local_8 = local_8 + 2;
      local_8[1] = 0xf0;
      *(undefined1 *)(local_8 + 0x3e) = 0xff;
      (local_14 + 0x10)[(int)local_18] = 0xf0;
      (local_14 + 0x410)[(int)local_18] = 0xf1;
      local_8 = local_8 + 0x400;
    }
    PTR_LOOP_0063ac4c = (undefined *)local_18;
    for (; ((int)local_10 < 0x400 && ((local_10 + 0x10)[(int)local_18] != -1));
        local_10 = local_10 + 1) {
    }
    puVar6 = local_18[3];
    if ((int)local_10 < 0x400) {
      local_18[3] = local_10;
    }
    else {
      local_18[3] = (undefined *)0xffffffff;
    }
    puVar5 = (undefined4 *)(local_18[0x204] + (int)puVar6 * 0x1000);
    *(char *)(puVar5 + 2) = (char)param_1;
    local_18[2] = puVar6;
    (puVar6 + 0x10)[(int)local_18] = (puVar6 + 0x10)[(int)local_18] - (char)param_1;
    *puVar5 = (undefined *)((int)puVar5 + param_1 + 8);
    puVar5[1] = puVar5[1] - param_1;
    puVar6 = local_18[0x204] + (int)puVar6 * 0x1000 + 0x100;
  }
  else {
    puVar6 = (undefined *)0x0;
  }
  return puVar6;
}
#undef local_18
#undef local_14
#undef local_10
#undef local_8

/* 005fd860 crt */
#define local_14 (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(byte * *)(frame_ + FRAME_OFF(8)))
#define local_c (*(byte * *)(frame_ + FRAME_OFF(12)))
/* Library Function - Single Match
    ___sbh_alloc_block_from_page
   
   Library: Visual Studio 1998 Debug */

int __cdecl ___sbh_alloc_block_from_page(int *param_1,uint param_2,uint param_3)

{
  byte *pbVar1;
  int iVar2;
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  pbVar1 = (byte *)*param_1;
  if ((uint)param_1[1] < param_3) {
    local_c = pbVar1;
    if (pbVar1[param_1[1]] != 0) {
      local_c = pbVar1 + param_1[1];
    }
    while (local_c + param_3 < param_1 + 0x3e) {
      if (*local_c == 0) {
        local_14 = 1;
        local_10 = local_c;
        while (local_10 = local_10 + 1, *local_10 == 0) {
          local_14 = local_14 + 1;
        }
        if (param_3 <= local_14) {
          if (local_c + param_3 < param_1 + 0x3e) {
            *param_1 = (int)(local_c + param_3);
            param_1[1] = local_14 - param_3;
          }
          else {
            *param_1 = (int)(param_1 + 2);
            param_1[1] = 0;
          }
          *local_c = (byte)param_3;
          return (int)local_c * 0x10 + (int)param_1 * -0xf + 0x80;
        }
        if (pbVar1 == local_c) {
          param_1[1] = local_14;
        }
        else {
          param_2 = param_2 - local_14;
          if (param_2 < param_3) {
            return 0;
          }
        }
        local_c = local_10;
      }
      else {
        local_c = local_c + *local_c;
      }
    }
    local_c = (byte *)(param_1 + 2);
    while ((local_c < pbVar1 && (local_c + param_3 <= (byte *)((int)param_1 + 0xf7)))) {
      if (*local_c == 0) {
        local_14 = 1;
        local_10 = local_c;
        while (local_10 = local_10 + 1, *local_10 == 0) {
          local_14 = local_14 + 1;
        }
        if (param_3 <= local_14) {
          if (local_c + param_3 < param_1 + 0x3e) {
            *param_1 = (int)(local_c + param_3);
            param_1[1] = local_14 - param_3;
          }
          else {
            *param_1 = (int)(param_1 + 2);
            param_1[1] = 0;
          }
          *local_c = (byte)param_3;
          return (int)local_c * 0x10 + (int)param_1 * -0xf + 0x80;
        }
        param_2 = param_2 - local_14;
        if (param_2 < param_3) {
          return 0;
        }
        local_c = local_10;
      }
      else {
        local_c = local_c + *local_c;
      }
    }
    iVar2 = 0;
  }
  else {
    *pbVar1 = (byte)param_3;
    if (pbVar1 + param_3 < param_1 + 0x3e) {
      *param_1 = *param_1 + param_3;
      param_1[1] = param_1[1] - param_3;
    }
    else {
      *param_1 = (int)(param_1 + 2);
      param_1[1] = 0;
    }
    iVar2 = (int)pbVar1 * 0x10 + (int)param_1 * -0xf + 0x80;
  }
  return iVar2;
}
#undef local_14
#undef local_10
#undef local_c

/* 005fdb60 crt */
#define local_18 (*(byte * *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(undefined4 *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(byte * *)(frame_ + FRAME_OFF(8)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
/* Library Function - Single Match
    ___sbh_resize_block
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl ___sbh_resize_block(int param_1,undefined4 *param_2,byte *param_3,uint param_4)

{
  byte bVar1;
  uint uVar2;
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_14 = 0;
  bVar1 = *param_3;
  uVar2 = (uint)bVar1;
  if (param_4 < uVar2) {
    *param_3 = (byte)param_4;
    *(byte *)(((int)param_2 - *(int *)(param_1 + 0x810) >> 0xc) + 0x10 + param_1) =
         (*(char *)(((int)param_2 - *(int *)(param_1 + 0x810) >> 0xc) + 0x10 + param_1) -
         (byte)param_4) + bVar1;
    *(undefined1 *)(((int)param_2 - *(int *)(param_1 + 0x810) >> 0xc) + 0x410 + param_1) = 0xf1;
    local_14 = 1;
  }
  else if ((uVar2 < param_4) && (param_3 + param_4 <= param_2 + 0x3e)) {
    local_18 = param_3 + param_4;
    for (local_10 = param_3 + uVar2; (local_10 < local_18 && (*local_10 == 0));
        local_10 = local_10 + 1) {
    }
    if (local_18 == local_10) {
      *param_3 = (byte)param_4;
      if ((param_3 <= (byte *)*param_2) && ((byte *)*param_2 < local_18)) {
        if (local_18 < param_2 + 0x3e) {
          *param_2 = local_18;
          local_8 = 0;
          for (; *local_18 == 0; local_18 = local_18 + 1) {
            local_8 = local_8 + 1;
          }
          param_2[1] = local_8;
        }
        else {
          *param_2 = param_2 + 2;
          param_2[1] = 0;
        }
      }
      *(byte *)(((int)param_2 - *(int *)(param_1 + 0x810) >> 0xc) + 0x10 + param_1) =
           (*(char *)(((int)param_2 - *(int *)(param_1 + 0x810) >> 0xc) + 0x10 + param_1) -
           (byte)param_4) + bVar1;
      local_14 = 1;
    }
  }
  return local_14;
}
#undef local_18
#undef local_14
#undef local_10
#undef local_8

/* 005fdd20 crt */
#define local_2c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_28 (*(uint *)(frame_ + FRAME_OFF(8)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(12)))
#define local_20 (*(undefined ** *)(frame_ + FRAME_OFF(16)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_14 (*(undefined * *)(frame_ + FRAME_OFF(28)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_c (*(int *)(frame_ + FRAME_OFF(36)))
#define local_8 (*(int * *)(frame_ + FRAME_OFF(40)))
/* Library Function - Single Match
    ___sbh_heap_check
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl ___sbh_heap_check(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 0;
  local_20 = &PTR_LOOP_0063a438;
  do {
    if (local_20 == (undefined **)PTR_LOOP_0063ac4c) {
      local_c = local_c + 1;
    }
    if (local_20[0x204] != (undefined *)0x0) {
      local_14 = (undefined *)0x0;
      local_2c = 0;
      local_8 = (int *)local_20[0x204];
      for (; (int)local_14 < 0x400; local_14 = local_14 + 1) {
        if ((local_14 + 0x10)[(int)local_20] == -1) {
          if ((local_2c == 0) && (local_20[3] != local_14)) {
            return 0xffffffff;
          }
          local_2c = local_2c + 1;
        }
        else {
          if (local_8 + 0x3e <= (int *)*local_8) {
            return 0xfffffffe;
          }
          if ((char)local_8[0x3e] != -1) {
            return 0xfffffffd;
          }
          local_18 = 0;
          local_10 = 0;
          local_28 = 0;
          local_24 = 0;
          while (local_18 < 0xf0) {
            if ((int)local_8 + local_18 + 8 == *local_8) {
              local_10 = local_10 + 1;
            }
            if (*(char *)(local_18 + 8 + (int)local_8) == '\0') {
              local_28 = local_28 + 1;
              local_24 = local_24 + 1;
              local_18 = local_18 + 1;
            }
            else {
              if ((int)(uint)(byte)(local_14 + 0x410)[(int)local_20] <= local_24) {
                return 0xfffffffc;
              }
              if (local_10 == 1) {
                if (local_24 < local_8[1]) {
                  return 0xfffffffb;
                }
                local_10 = 2;
              }
              local_24 = 0;
              iVar2 = local_18;
              while (local_1c = iVar2 + 1,
                    local_1c < (int)((uint)*(byte *)(local_18 + 8 + (int)local_8) + local_18)) {
                iVar1 = iVar2 + 9;
                iVar2 = local_1c;
                if (*(char *)(iVar1 + (int)local_8) != '\0') {
                  return 0xfffffffa;
                }
              }
              local_18 = local_1c;
            }
          }
          if ((byte)(local_14 + 0x10)[(int)local_20] != local_28) {
            return 0xfffffff9;
          }
          if (local_10 == 0) {
            return 0xfffffff8;
          }
        }
        local_8 = local_8 + 0x400;
      }
    }
    local_20 = (undefined **)*local_20;
    if (local_20 == &PTR_LOOP_0063a438) {
      if (local_c == 0) {
        uVar3 = 0xfffffff7;
      }
      else {
        uVar3 = 0;
      }
      return uVar3;
    }
  } while( true );
}
#undef local_2c
#undef local_28
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 005fdf90 crt */
#define DAT_00639f18 (*(undefined4 *)((u8 *)&g.d_00639f18))
#define DAT_006e69f0 (*(undefined4 *)((u8 *)&g.d_006e69f0))
#define DAT_006e6b2c (*(uint *)((u8 *)&g.d_006e6b2c))
#define local_8 (*(ulong *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    __lseek
   
   Library: Visual Studio 1998 Debug */

long __cdecl __lseek(int _FileHandle,long _Offset,int _Origin)

{
  DWORD DVar1;
  HANDLE hFile;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((uint)_FileHandle < DAT_006e6b2c) &&
     ((*(byte *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) + 4 +
                (_FileHandle & 0x1fU) * 8) & 1) != 0)) {
    hFile = (HANDLE)__get_osfhandle(_FileHandle);
    if (hFile == (HANDLE)0xffffffff) {
      crt_errno = 9;
      DVar1 = 0xffffffff;
    }
    else {
      DVar1 = SetFilePointer(hFile,_Offset,(PLONG)0x0,_Origin);
      if (DVar1 == 0xffffffff) {
        local_8 = GetLastError();
      }
      else {
        local_8 = 0;
      }
      if (local_8 == 0) {
        *(byte *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) + 4 +
                 (_FileHandle & 0x1fU) * 8) =
             *(byte *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) + 4 +
                      (_FileHandle & 0x1fU) * 8) & 0xfd;
      }
      else {
        __dosmaperr(local_8);
        DVar1 = 0xffffffff;
      }
    }
  }
  else {
    crt_errno = 9;
    DAT_00639f18 = 0;
    DVar1 = 0xffffffff;
  }
  return DVar1;
}
#undef DAT_00639f18
#undef DAT_006e69f0
#undef DAT_006e6b2c
#undef local_8

/* 005fe0b0 crt */
#define DAT_006e69f0 (*(undefined4 *)((u8 *)&g.d_006e69f0))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    ___initstdio
   
   Library: Visual Studio 1998 Debug */

void __cdecl ___initstdio(void)

{
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (DAT_006e69e0 == 0) {
    DAT_006e69e0 = 0x200;
  }
  else if (DAT_006e69e0 < 0x14) {
    DAT_006e69e0 = 0x14;
  }
  DAT_006e5694 = __calloc_dbg(DAT_006e69e0,4,2,"_file.c",0x84);
  if (DAT_006e5694 == 0) {
    DAT_006e69e0 = 0x14;
    DAT_006e5694 = __calloc_dbg(0x14,4,2,"_file.c",0x87);
    if (DAT_006e5694 == 0) {
      __amsg_exit(0x1a);
    }
  }
  for (local_8 = 0; (int)local_8 < 0x14; local_8 = local_8 + 1) {
    *(undefined ***)(DAT_006e5694 + local_8 * 4) = &PTR_DAT_0063ac58 + local_8 * 8;
  }
  for (local_8 = 0; (int)local_8 < 3; local_8 = local_8 + 1) {
    if ((*(int *)(*(int *)((int)&DAT_006e69f0 + ((int)(local_8 & 0xffffffe0) >> 3)) +
                 (local_8 & 0x1f) * 8) == -1) ||
       (*(int *)(*(int *)((int)&DAT_006e69f0 + ((int)(local_8 & 0xffffffe0) >> 3)) +
                (local_8 & 0x1f) * 8) == 0)) {
      *(undefined4 *)(&DAT_0063ac68 + local_8 * 0x20) = 0xffffffff;
    }
  }
  return;
}
#undef DAT_006e69f0
#undef local_8

/* 005fe210 crt */
#define DAT_00639f54 (*(char *)((u8 *)&g.d_00639f54))
/* Library Function - Single Match
    ___endstdio
   
   Library: Visual Studio 1998 Debug */

void __cdecl ___endstdio(void)

{
  __flushall();
  if (DAT_00639f54 != '\0') {
    __fcloseall();
  }
  return;
}
#undef DAT_00639f54

/* 005fe240 crt */
/* Library Function - Single Match
    __setdefaultprecision
   
   Library: Visual Studio 1998 Debug */

void __cdecl __setdefaultprecision(void)

{
  __controlfp(0x10000,0x30000);
  return;
}

/* 005fe260 crt */
#define _DAT_0061e818 (*(undefined8 *)((u8 *)&g.d_0061e818))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __ms_p5_test_fdiv
   
   Library: Visual Studio 1998 Debug */

bool __cdecl __ms_p5_test_fdiv(void)

{
  return _DAT_0061e818 < 0.0;
}
#undef _DAT_0061e818

/* 005fe2c0 crt */
/* Library Function - Single Match
    __ms_p5_mp_test_fdiv
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl __ms_p5_mp_test_fdiv(void)

{
  HMODULE hModule;
  FARPROC pFVar1;
  int iVar2;
  undefined4 uVar3;
  
  hModule = GetModuleHandleA("KERNEL32");
  if ((hModule != (HMODULE)0x0) &&
     (pFVar1 = GetProcAddress(hModule,"IsProcessorFeaturePresent"), pFVar1 != (FARPROC)0x0)) {
    iVar2 = (*pFVar1)(0);
    return iVar2;
  }
  uVar3 = __ms_p5_test_fdiv();
  return uVar3;
}

/* 005fe320 crt */
#define local_10 (*(uint *)(frame_ + FRAME_OFF(0)))
#define local_c (*(char *)(frame_ + FRAME_OFF(4)))
/* Library Function - Single Match
    __forcdecpt
   
   Library: Visual Studio 1998 Debug */

void __cdecl __forcdecpt(char *_Buf)

{
  char cVar1;
  int iVar2;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar2 = _tolower((int)*_Buf);
  if (iVar2 != 0x65) {
    do {
      _Buf = _Buf + 1;
      if (DAT_0063a29c < 2) {
        local_10 = *(ushort *)(PTR_DAT_0063a090 + *_Buf * 2) & 4;
      }
      else {
        local_10 = __isctype((int)*_Buf,4);
      }
    } while (local_10 != 0);
  }
  local_c = *_Buf;
  *_Buf = DAT_0063a2a0;
  do {
    _Buf = _Buf + 1;
    cVar1 = *_Buf;
    *_Buf = local_c;
    local_c = cVar1;
  } while (*_Buf != '\0');
  return;
}
#undef local_10
#undef local_c

/* 005fe3e0 crt */
#define local_8 (*(char * *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    __cropzeros
   
   Library: Visual Studio 1998 Debug */

void __cdecl __cropzeros(char *_Buf)

{
  char *pcVar1;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (; (*_Buf != '\0' && (DAT_0063a2a0 != *_Buf)); _Buf = _Buf + 1) {
  }
  if (*_Buf != '\0') {
    do {
      pcVar1 = _Buf;
      _Buf = pcVar1 + 1;
      if ((*_Buf == '\0') || (*_Buf == 'e')) break;
    } while (*_Buf != 'E');
    local_8 = _Buf;
    for (_Buf = pcVar1; *_Buf == '0'; _Buf = _Buf + -1) {
    }
    if (DAT_0063a2a0 == *_Buf) {
      _Buf = _Buf + -1;
    }
    do {
      _Buf = _Buf + 1;
      *_Buf = *local_8;
      local_8 = local_8 + 1;
    } while (*_Buf != '\0');
  }
  return;
}
#undef local_8

/* 005fe4c0 crt */
#define _DAT_0061e848 (*(undefined8 *)((u8 *)&g.d_0061e848))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __positive
   
   Library: Visual Studio 1998 Debug */

int __cdecl __positive(double *arg)

{
  return (uint)(_DAT_0061e848 <= *arg);
}
#undef _DAT_0061e848

/* 005fe500 crt */
#define local_10 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
#define local_c (*(undefined4 *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    __fassign
   
   Library: Visual Studio 1998 Debug */

void __cdecl __fassign(int flag,char *argument,char *number)

{
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (flag == 0) {
    FUN_006032c0(&local_10,number);
    *(undefined4 *)argument = local_10;
  }
  else {
    FUN_00603240(&local_c,number);
    *(undefined4 *)argument = local_c;
    *(undefined4 *)(argument + 4) = local_8;
  }
  return;
}
#undef local_10
#undef local_c
#undef local_8

/* 005fe560: written by hand in src/crt/float.c */

/* 005fe730: written by hand in src/crt/float.c */

/* 005fe8c0: written by hand in src/crt/float.c */

/* 005fe9e0: written by hand in src/crt/float.c */

/* 005fea20: written by hand in src/crt/float.c */

/* 005fea60: written by hand in src/crt/float.c */

/* 005feae0 crt */
/* Library Function - Single Match
    __shift
   
   Library: Visual Studio 1998 Debug */

void __cdecl __shift(char *param_1,int param_2)

{
  size_t sVar1;
  
  if (param_2 != 0) {
    sVar1 = _strlen(param_1);
    FUN_005f6500(param_1 + param_2,param_1,sVar1 + 1);
  }
  return;
}

/* 005feb20 crt */
#define DAT_0063af90 (*(_EXCEPTION_POINTERS * *)((u8 *)&g.d_0063af90))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
/* Library Function - Single Match
    __XcptFilter
   
   Library: Visual Studio 1998 Debug */

int __cdecl __XcptFilter(ulong _ExceptionNum,_EXCEPTION_POINTERS *_ExceptionPtr)

{
  code *pcVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  piVar4 = (int *)xcptlookup(_ExceptionNum);
  uVar3 = DAT_0063af90;
  if ((piVar4 == (int *)0x0) || (piVar4[2] == 0)) {
    iVar5 = UnhandledExceptionFilter(_ExceptionPtr);
  }
  else if (piVar4[2] == 5) {
    piVar4[2] = 0;
    iVar5 = 1;
  }
  else if (piVar4[2] == 1) {
    iVar5 = -1;
    DAT_0063af90 = (_EXCEPTION_POINTERS *)uVar3;
  }
  else {
    pcVar1 = (code *)piVar4[2];
    DAT_0063af90 = _ExceptionPtr;
    if (piVar4[1] == 8) {
      for (local_14 = DAT_0063af80; uVar2 = DAT_0063af8c, local_14 < DAT_0063af84 + DAT_0063af80;
          local_14 = local_14 + 1) {
        *(undefined4 *)(local_14 * 0xc + ADDR(0x63af10, ((u8 *)&g.d_0063af0c + 4))) = 0;
      }
      if (*piVar4 == -0x3fffff72) {
        DAT_0063af8c = 0x83;
      }
      else if (*piVar4 == -0x3fffff70) {
        DAT_0063af8c = 0x81;
      }
      else if (*piVar4 == -0x3fffff6f) {
        DAT_0063af8c = 0x84;
      }
      else if (*piVar4 == -0x3fffff6d) {
        DAT_0063af8c = 0x85;
      }
      else if (*piVar4 == -0x3fffff73) {
        DAT_0063af8c = 0x82;
      }
      else if (*piVar4 == -0x3fffff71) {
        DAT_0063af8c = 0x86;
      }
      else if (*piVar4 == -0x3fffff6e) {
        DAT_0063af8c = 0x8a;
      }
      (*pcVar1)(8,DAT_0063af8c);
      DAT_0063af8c = uVar2;
    }
    else {
      piVar4[2] = 0;
      (*pcVar1)(piVar4[1]);
    }
    iVar5 = -1;
    DAT_0063af90 = (_EXCEPTION_POINTERS *)uVar3;
  }
  return iVar5;
}
#undef DAT_0063af90
#undef local_14

/* 005fed20 crt */
#define local_8 (*(int * *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    _xcptlookup
   
   Library: Visual Studio 1998 Debug */

int * __cdecl xcptlookup(int param_1)

{
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = &DAT_0063af08;
  do {
    if (*local_8 == param_1) break;
    local_8 = local_8 + 3;
  } while (local_8 < &DAT_0063af08 + DAT_0063af88 * 3);
  if (*local_8 != param_1) {
    local_8 = (int *)0x0;
  }
  return local_8;
}
#undef local_8

/* 005fed90 crt */
/* Library Function - Single Match
    __ismbbkalnum
   
   Library: Visual Studio 1998 Debug */

int __cdecl __ismbbkalnum(uint _C)

{
  int iVar1;
  
  iVar1 = x_ismbbtype(_C,0,1);
  return iVar1;
}

/* 005fedb0 crt */
/* Library Function - Single Match
    __ismbbkprint
   
   Library: Visual Studio 1998 Debug */

int __cdecl __ismbbkprint(uint _C)

{
  int iVar1;
  
  iVar1 = x_ismbbtype(_C,0,3);
  return iVar1;
}

/* 005fedd0 crt */
/* Library Function - Single Match
    __ismbbkpunct
   
   Library: Visual Studio 1998 Debug */

int __cdecl __ismbbkpunct(uint _C)

{
  int iVar1;
  
  iVar1 = x_ismbbtype(_C,0,2);
  return iVar1;
}

/* 005fedf0 crt */
/* Library Function - Single Match
    __ismbbalnum
   
   Library: Visual Studio 1998 Debug */

int __cdecl __ismbbalnum(uint _C)

{
  int iVar1;
  
  iVar1 = x_ismbbtype(_C,0x107,1);
  return iVar1;
}

/* 005fee20 crt */
/* Library Function - Single Match
    __ismbbalpha
   
   Library: Visual Studio 1998 Debug */

int __cdecl __ismbbalpha(uint _C)

{
  int iVar1;
  
  iVar1 = x_ismbbtype(_C,0x103,1);
  return iVar1;
}

/* 005fee50 crt */
/* Library Function - Single Match
    __ismbbgraph
   
   Library: Visual Studio 1998 Debug */

int __cdecl __ismbbgraph(uint _C)

{
  int iVar1;
  
  iVar1 = x_ismbbtype(_C,0x117,3);
  return iVar1;
}

/* 005fee80 crt */
/* Library Function - Single Match
    __ismbbprint
   
   Library: Visual Studio 1998 Debug */

int __cdecl __ismbbprint(uint _C)

{
  int iVar1;
  
  iVar1 = x_ismbbtype(_C,0x157,3);
  return iVar1;
}

/* 005feeb0 crt */
/* Library Function - Single Match
    __ismbbpunct
   
   Library: Visual Studio 1998 Debug */

int __cdecl __ismbbpunct(uint _C)

{
  int iVar1;
  
  iVar1 = x_ismbbtype(_C,0x10,2);
  return iVar1;
}

/* 005feed0 crt */
/* Library Function - Single Match
    __ismbblead
   
   Library: Visual Studio 1998 Debug */

int __cdecl __ismbblead(uint _C)

{
  int iVar1;
  
  iVar1 = x_ismbbtype(_C,0,4);
  return iVar1;
}

/* 005feef0 crt */
/* Library Function - Single Match
    __ismbbtrail
   
   Library: Visual Studio 1998 Debug */

int __cdecl __ismbbtrail(uint _C)

{
  int iVar1;
  
  iVar1 = x_ismbbtype(_C,0,8);
  return iVar1;
}

/* 005fef10 crt */
#define DAT_0063b0a4 (*(int *)((u8 *)&g.d_0063b0a4))
/* Library Function - Single Match
    __ismbbkana
   
   Library: Visual Studio 1998 Debug */

int __cdecl __ismbbkana(uint _C)

{
  int iVar1;
  
  if ((DAT_0063b0a4 == 0x3a4) && (iVar1 = x_ismbbtype(_C,0,3), iVar1 != 0)) {
    return 1;
  }
  return 0;
}
#undef DAT_0063b0a4

/* 005fef60 crt */
#define local_8 (*(uint *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    _x_ismbbtype
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl x_ismbbtype(undefined4 param_1,uint param_2,undefined4 param_3)

{
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((byte)param_3 & (&DAT_0063afa1)[(byte)param_1]) == 0) {
    if (param_2 == 0) {
      local_8 = 0;
    }
    else {
      local_8 = *(ushort *)(&DAT_0063a09a + (uint)(byte)param_1 * 2) & param_2;
    }
    if (local_8 == 0) {
      return 0;
    }
  }
  return 1;
}
#undef local_8

/* 005fefd0 crt */
#define DAT_00639fc0 (*(char * *)((u8 *)&g.d_00639fc0))
#define local_10 (*(int * *)(frame_ + FRAME_OFF(0)))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(char * *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    __setenvp
   
   Library: Visual Studio 1998 Debug */

int __cdecl __setenvp(void)

{
  size_t sVar1;
  int iVar2;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 0;
  for (local_8 = DAT_00639fc0; *local_8 != '\0'; local_8 = local_8 + sVar1 + 1) {
    if (*local_8 != '=') {
      local_c = local_c + 1;
    }
    sVar1 = _strlen(local_8);
  }
  local_10 = (int *)__malloc_dbg(local_c * 4 + 4,2,"stdenvp.c",0x55);
  DAT_00639f3c = local_10;
  if (local_10 == (int *)0x0) {
    __amsg_exit(9);
  }
  for (local_8 = DAT_00639fc0; *local_8 != '\0'; local_8 = local_8 + sVar1 + 1) {
    sVar1 = _strlen(local_8);
    if (*local_8 != '=') {
      iVar2 = __malloc_dbg(sVar1 + 1,2,"stdenvp.c",0x61);
      *local_10 = iVar2;
      if (*local_10 == 0) {
        __amsg_exit(9);
      }
      FUN_005f22d0(*local_10,local_8);
      local_10 = local_10 + 1;
    }
  }
  __free_dbg(DAT_00639fc0,2);
  DAT_00639fc0 = (char *)0x0;
  *local_10 = 0;
  return (int)local_10;
}
#undef DAT_00639fc0
#undef local_10
#undef local_c
#undef local_8

/* 005ff110 crt */
#define DAT_006e6b3c (*(char * *)((u8 *)&g.d_006e6b3c))
#define _DAT_00639f30 (*(undefined4 *)((u8 *)&g.d_00639f30))
#define _DAT_00639f34 (*(undefined4 *)((u8 *)&g.d_00639f34))
#define local_14 (*(char * *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __setargv
   
   Library: Visual Studio 1998 Debug */

int __cdecl __setargv(void)

{
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  GetModuleFileNameA((HMODULE)0x0,&DAT_006e54a8,0x104);
  DAT_00639f4c = &DAT_006e54a8;
  if (*DAT_006e6b3c == '\0') {
    local_14 = &DAT_006e54a8;
  }
  else {
    local_14 = DAT_006e6b3c;
  }
  parse_cmdline(local_14,0,0,&local_10,&local_8);
  local_c = __malloc_dbg(local_10 * 4 + local_8,2,"stdargv.c",0x75);
  if (local_c == 0) {
    __amsg_exit(8);
  }
  parse_cmdline(local_14,local_c,local_10 * 4 + local_c,&local_10,&local_8);
  _DAT_00639f30 = local_10 + -1;
  _DAT_00639f34 = local_c;
  return local_c;
}
#undef DAT_006e6b3c
#undef _DAT_00639f30
#undef _DAT_00639f34
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 005ff1e0 crt */
#define local_14 (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(byte * *)(frame_ + FRAME_OFF(16)))
/* Library Function - Single Match
    _parse_cmdline
   
   Library: Visual Studio 1998 Debug */

void __cdecl
parse_cmdline(byte *param_1,undefined4 *param_2,byte *param_3,int *param_4,int *param_5)

{
  byte *pbVar1;
  byte bVar2;
  bool bVar3;
  bool bVar4;
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  *param_5 = 0;
  *param_4 = 1;
  local_8 = param_1;
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = param_3;
    param_2 = param_2 + 1;
  }
  if (*param_1 == 0x22) {
    while ((pbVar1 = local_8 + 1, *pbVar1 != 0x22 && (*pbVar1 != 0))) {
      if ((((&DAT_0063afa1)[*pbVar1] & 4) != 0) && (*param_5 = *param_5 + 1, param_3 != (byte *)0x0)
         ) {
        *param_3 = *pbVar1;
        param_3 = param_3 + 1;
        pbVar1 = local_8 + 2;
      }
      local_8 = pbVar1;
      *param_5 = *param_5 + 1;
      if (param_3 != (byte *)0x0) {
        *param_3 = *local_8;
        param_3 = param_3 + 1;
      }
    }
    *param_5 = *param_5 + 1;
    if (param_3 != (byte *)0x0) {
      *param_3 = 0;
      param_3 = param_3 + 1;
    }
    if (*pbVar1 == 0x22) {
      pbVar1 = local_8 + 2;
    }
  }
  else {
    do {
      *param_5 = *param_5 + 1;
      if (param_3 != (byte *)0x0) {
        *param_3 = *local_8;
        param_3 = param_3 + 1;
      }
      bVar2 = *local_8;
      pbVar1 = local_8 + 1;
      if (((&DAT_0063afa1)[bVar2] & 4) != 0) {
        *param_5 = *param_5 + 1;
        if (param_3 != (byte *)0x0) {
          *param_3 = local_8[1];
          param_3 = param_3 + 1;
        }
        pbVar1 = local_8 + 2;
      }
      local_8 = pbVar1;
    } while (((bVar2 != 0x20) && (bVar2 != 0)) && (bVar2 != 9));
    if (bVar2 == 0) {
      pbVar1 = local_8 + -1;
    }
    else {
      pbVar1 = local_8;
      if (param_3 != (byte *)0x0) {
        param_3[-1] = 0;
      }
    }
  }
  local_8 = pbVar1;
  bVar3 = false;
  while( true ) {
    if (*local_8 != 0) {
      for (; (*local_8 == 0x20 || (*local_8 == 9)); local_8 = local_8 + 1) {
      }
    }
    if (*local_8 == 0) break;
    if (param_2 != (undefined4 *)0x0) {
      *param_2 = param_3;
      param_2 = param_2 + 1;
    }
    *param_4 = *param_4 + 1;
    while( true ) {
      bVar4 = true;
      local_14 = 0;
      for (; *local_8 == 0x5c; local_8 = local_8 + 1) {
        local_14 = local_14 + 1;
      }
      if (*local_8 == 0x22) {
        if ((local_14 & 1) == 0) {
          if (bVar3) {
            bVar4 = local_8[1] == 0x22;
            if (bVar4) {
              local_8 = local_8 + 1;
            }
          }
          else {
            bVar4 = false;
          }
          if (bVar3) {
            bVar3 = false;
          }
          else {
            bVar3 = true;
          }
        }
        local_14 = local_14 >> 1;
      }
      while (local_14 != 0) {
        if (param_3 != (byte *)0x0) {
          *param_3 = 0x5c;
          param_3 = param_3 + 1;
        }
        *param_5 = *param_5 + 1;
        local_14 = local_14 - 1;
      }
      if ((*local_8 == 0) || ((!bVar3 && ((*local_8 == 0x20 || (*local_8 == 9)))))) break;
      if (bVar4) {
        if (param_3 == (byte *)0x0) {
          if (((&DAT_0063afa1)[*local_8] & 4) != 0) {
            local_8 = local_8 + 1;
            *param_5 = *param_5 + 1;
          }
        }
        else {
          if (((&DAT_0063afa1)[*local_8] & 4) != 0) {
            *param_3 = *local_8;
            local_8 = local_8 + 1;
            param_3 = param_3 + 1;
            *param_5 = *param_5 + 1;
          }
          *param_3 = *local_8;
          param_3 = param_3 + 1;
        }
        *param_5 = *param_5 + 1;
      }
      local_8 = local_8 + 1;
    }
    if (param_3 != (byte *)0x0) {
      *param_3 = 0;
      param_3 = param_3 + 1;
    }
    *param_5 = *param_5 + 1;
  }
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = 0;
  }
  *param_4 = *param_4 + 1;
  return;
}
#undef local_14
#undef local_8

/* 005ff5a0: written by hand in src/crt/startup.c */

/* 005ff860 crt */
#define local_1c (*(LPCH *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(LPWCH *)(frame_ + FRAME_OFF(8)))
#define local_10 (*(char * *)(frame_ + FRAME_OFF(16)))
#define local_c (*(LPWCH *)(frame_ + FRAME_OFF(20)))
/* Library Function - Single Match
    ___crtGetEnvironmentStringsA
   
   Library: Visual Studio 1998 Debug */

LPVOID __cdecl ___crtGetEnvironmentStringsA(void)

{
  char *pcVar1;
  LPWCH pWVar2;
  int iVar3;
  int cbMultiByte;
  LPSTR pCVar4;
  undefined1 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_18 = (LPWCH)0x0;
  local_1c = (LPCH)0x0;
  if (DAT_0063af98 == 0) {
    local_18 = GetEnvironmentStringsW();
    if (local_18 == (LPWCH)0x0) {
      local_1c = GetEnvironmentStrings();
      if (local_1c == (LPCH)0x0) {
        return (LPVOID)0x0;
      }
      DAT_0063af98 = 2;
    }
    else {
      DAT_0063af98 = 1;
    }
  }
  if (DAT_0063af98 == 1) {
    if ((local_18 == (LPWCH)0x0) && (local_18 = GetEnvironmentStringsW(), local_18 == (LPWCH)0x0)) {
      pCVar4 = (LPSTR)0x0;
    }
    else {
      local_c = local_18;
      pWVar2 = local_c;
      while (local_c = pWVar2, *local_c != L'\0') {
        pWVar2 = local_c + 1;
        if (local_c[1] == L'\0') {
          pWVar2 = local_c + 2;
        }
      }
      iVar3 = ((int)local_c - (int)local_18 >> 1) + 1;
      cbMultiByte = WideCharToMultiByte(0,0,local_18,iVar3,(LPSTR)0x0,0,(LPCSTR)0x0,(LPBOOL)0x0);
      if ((cbMultiByte == 0) ||
         (local_1c = (LPCH)__malloc_dbg(cbMultiByte,2,"aw_env.c",0xfb), local_1c == (LPSTR)0x0)) {
        FreeEnvironmentStringsW(local_18);
        pCVar4 = (LPSTR)0x0;
      }
      else {
        iVar3 = WideCharToMultiByte(0,0,local_18,iVar3,local_1c,cbMultiByte,(LPCSTR)0x0,(LPBOOL)0x0)
        ;
        if (iVar3 == 0) {
          __free_dbg(local_1c,2);
          local_1c = (LPSTR)0x0;
        }
        FreeEnvironmentStringsW(local_18);
        pCVar4 = local_1c;
      }
    }
  }
  else if (DAT_0063af98 == 2) {
    if ((local_1c == (LPCH)0x0) && (local_1c = GetEnvironmentStrings(), local_1c == (LPCH)0x0)) {
      pCVar4 = (LPSTR)0x0;
    }
    else {
      local_10 = local_1c;
      pcVar1 = local_10;
      while (local_10 = pcVar1, *local_10 != '\0') {
        pcVar1 = local_10 + 1;
        if (local_10[1] == '\0') {
          pcVar1 = local_10 + 2;
        }
      }
      pCVar4 = (LPSTR)__malloc_dbg(local_10 + (1 - (int)local_1c),2,"aw_env.c",0x126);
      if (pCVar4 == (LPSTR)0x0) {
        FreeEnvironmentStringsA(local_1c);
        pCVar4 = (LPSTR)0x0;
      }
      else {
        FUN_005f2110(pCVar4,local_1c,local_10 + (1 - (int)local_1c));
        FreeEnvironmentStringsA(local_1c);
      }
    }
  }
  else {
    pCVar4 = (LPSTR)0x0;
  }
  return pCVar4;
}
#undef local_1c
#undef local_18
#undef local_10
#undef local_c

/* 005ffac0: written by hand in src/crt/startup.c */

/* 005ffdf0 crt */
#define DAT_0063a088 (*(UINT *)((u8 *)&g.d_0063a088))
#define DAT_0063b0bc (*(undefined4 *)((u8 *)&g.d_0063b0bc))
/* Library Function - Single Match
    _getSystemCP
   
   Library: Visual Studio 1998 Debug */

UINT __cdecl getSystemCP(UINT param_1)

{
  DAT_0063b0bc = 0;
  if (param_1 == 0xfffffffe) {
    DAT_0063b0bc = 1;
    param_1 = GetOEMCP();
  }
  else if (param_1 == 0xfffffffd) {
    DAT_0063b0bc = 1;
    param_1 = GetACP();
  }
  else if (param_1 == 0xfffffffc) {
    DAT_0063b0bc = 1;
    param_1 = DAT_0063a088;
  }
  return param_1;
}
#undef DAT_0063a088
#undef DAT_0063b0bc

/* 005ffe80 crt */
/* Library Function - Single Match
    _CPtoLCID
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl _CPtoLCID(undefined4 param_1)

{
  undefined4 uVar1;
  
  switch(param_1) {
  case 0x3a4:
    uVar1 = 0x411;
    break;
  default:
    uVar1 = 0;
    break;
  case 0x3a8:
    uVar1 = 0x804;
    break;
  case 0x3b5:
    uVar1 = 0x412;
    break;
  case 0x3b6:
    uVar1 = 0x404;
  }
  return uVar1;
}

/* 005fff20 crt */
#define DAT_0063b0a4 (*(undefined4 *)((u8 *)&g.d_0063b0a4))
#define DAT_0063b0a8 (*(undefined4 *)((u8 *)&g.d_0063b0a8))
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    _setSBCS
   
   Library: Visual Studio 1998 Debug */

void __cdecl setSBCS(void)

{
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; local_8 < 0x101; local_8 = local_8 + 1) {
    (&DAT_0063afa0)[local_8] = 0;
  }
  DAT_0063b0a4 = 0;
  DAT_0063b0a8 = 0;
  for (local_8 = 0; local_8 < 6; local_8 = local_8 + 1) {
    *(undefined2 *)(&DAT_0063b0b0 + local_8 * 2) = 0;
  }
  return;
}
#undef DAT_0063b0a4
#undef DAT_0063b0a8
#undef local_8

/* 005fffa0 crt */
#define DAT_0063b0a4 (*(undefined4 *)((u8 *)&g.d_0063b0a4))
undefined4 __cdecl FUN_005fffa0(void)

{
  return DAT_0063b0a4;
}
#undef DAT_0063b0a4

/* 005fffc0 crt */
/* Library Function - Single Match
    ___initmbctable
   
   Library: Visual Studio 1998 Debug */

void __cdecl ___initmbctable(void)

{
  __setmbcp(-3);
  return;
}

/* 005fffe0 crt */
#define DAT_0063b248 (*(code * *)((u8 *)&g.d_0063b248))
/* Library Function - Single Match
    __FF_MSGBANNER
   
   Library: Visual Studio 1998 Debug */

void __cdecl __FF_MSGBANNER(void)

{
  if ((DAT_00639fcc == 1) || ((DAT_00639fcc == 0 && (DAT_00639fd0 == 1)))) {
    __NMSG_WRITE(0xfc);
    if (DAT_0063b248 != (code *)0x0) {
      (*DAT_0063b248)();
    }
    __NMSG_WRITE(0xff);
  }
  return;
}
#undef DAT_0063b248

/* 00600040 crt */
#define DAT_006e69f0 (*(int *)((u8 *)&g.d_006e69f0))
#define local_1b8 (*(HANDLE *)(frame_ + FRAME_OFF(0)))
#define local_1b4 (*(CHAR (*)[160])(frame_ + FRAME_OFF(4)))
#define local_114 (*(CHAR (*)[260])(frame_ + FRAME_OFF(164)))
#define local_10 (*(char * *)(frame_ + FRAME_OFF(424)))
#define local_c (*(uint *)(frame_ + FRAME_OFF(428)))
#define local_8 (*(DWORD *)(frame_ + FRAME_OFF(432)))
/* Library Function - Single Match
    __NMSG_WRITE
   
   Library: Visual Studio 1998 Debug */

void __cdecl __NMSG_WRITE(int param_1)

{
  code *pcVar1;
  int iVar2;
  size_t sVar3;
  DWORD DVar4;
  DWORD *lpNumberOfBytesWritten;
  LPOVERLAPPED lpOverlapped;
  undefined1 frame_[FRAME_OFF(440)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_c = 0; (local_c < 0x12 && (*(int *)(&DAT_0063b1b8 + local_c * 8) != param_1));
      local_c = local_c + 1) {
  }
  if (*(int *)(&DAT_0063b1b8 + local_c * 8) == param_1) {
    if ((param_1 != 0xfc) &&
       (iVar2 = __CrtDbgReport(1,0,0,0,(&PTR_s_R6002___floating_point_not_loade_0063b1bc)
                                       [local_c * 2]), iVar2 == 1)) {
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    if ((DAT_00639fcc == 1) || ((DAT_00639fcc == 0 && (DAT_00639fd0 == 1)))) {
      if ((DAT_006e69f0 == 0) || (*(int *)(DAT_006e69f0 + 0x10) == -1)) {
        local_1b8 = GetStdHandle(0xfffffff4);
      }
      else {
        local_1b8 = *(HANDLE *)(DAT_006e69f0 + 0x10);
      }
      lpOverlapped = (LPOVERLAPPED)0x0;
      lpNumberOfBytesWritten = &local_8;
      sVar3 = _strlen((&PTR_s_R6002___floating_point_not_loade_0063b1bc)[local_c * 2]);
      WriteFile(local_1b8,(&PTR_s_R6002___floating_point_not_loade_0063b1bc)[local_c * 2],sVar3,
                lpNumberOfBytesWritten,lpOverlapped);
    }
    else if (param_1 != 0xfc) {
      DVar4 = GetModuleFileNameA((HMODULE)0x0,local_114,0x104);
      if (DVar4 == 0) {
        FUN_005f22d0(local_114,"<program name unknown>");
      }
      local_10 = local_114;
      sVar3 = _strlen(local_10);
      if (0x3c < sVar3 + 1) {
        sVar3 = _strlen(local_114);
        local_10 = local_10 + (sVar3 - 0x3b);
        _strncpy(local_10,"...",3);
      }
      FUN_005f22d0(local_1b4,"Runtime Error!\n\nProgram: ");
      FUN_005f22e0(local_1b4,local_10);
      FUN_005f22e0(local_1b4,&DAT_0061e2fc);
      FUN_005f22e0(local_1b4,(&PTR_s_R6002___floating_point_not_loade_0063b1bc)[local_c * 2]);
      ___crtMessageBoxA(local_1b4,"Microsoft Visual C++ Runtime Library",0x12010);
    }
  }
  return;
}
#undef DAT_006e69f0
#undef local_1b8
#undef local_1b4
#undef local_114
#undef local_10
#undef local_c
#undef local_8

/* 00600260 crt */
#define local_8 (*(uint *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    __GET_RTERRMSG
   
   Library: Visual Studio 1998 Debug */

wchar_t * __cdecl __GET_RTERRMSG(int param_1)

{
  wchar_t *pwVar1;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; (local_8 < 0x12 && (*(int *)(&DAT_0063b1b8 + local_8 * 8) != param_1));
      local_8 = local_8 + 1) {
  }
  if (*(int *)(&DAT_0063b1b8 + local_8 * 8) == param_1) {
    pwVar1 = (wchar_t *)(&PTR_s_R6002___floating_point_not_loade_0063b1bc)[local_8 * 2];
  }
  else {
    pwVar1 = (wchar_t *)0x0;
  }
  return pwVar1;
}
#undef local_8

/* 006002e0: written by hand in src/crt/time.c */

/* 00600400 crt */
/* Library Function - Single Match
    _abort
   
   Library: Visual Studio 1998 Debug */

void __cdecl _abort(void)

{
  __NMSG_WRITE(10);
  _raise(0x16);
  __exit(3);
  return;
}

/* 00600430: written by hand in src/crt/startup.c */

/* 00600610 crt */
#define DAT_0063b24c (*(undefined4 *)((u8 *)&g.d_0063b24c))
#define DAT_0063b250 (*(undefined4 *)((u8 *)&g.d_0063b250))
#define local_10 (*(code * *)(frame_ + FRAME_OFF(0)))
#define local_c (*(undefined4 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    _ctrlevent_capture@4
   
   Library: Visual Studio 1998 Debug
   __stdcall ctrlevent_capture,4 */

undefined4 __stdcall ctrlevent_capture(int param_1)

{
  undefined4 uVar1;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 == 0) {
    local_c = &DAT_0063b24c;
    local_10 = DAT_0063b24c;
    local_8 = 2;
  }
  else {
    local_c = &DAT_0063b250;
    local_10 = DAT_0063b250;
    local_8 = 0x15;
  }
  if (local_10 == (code *)0x0) {
    uVar1 = 0;
  }
  else {
    if (local_10 != (code *)0x1) {
      *local_c = 0;
      (*local_10)(local_8);
    }
    uVar1 = 1;
  }
  return uVar1;
}
#undef DAT_0063b24c
#undef DAT_0063b250
#undef local_10
#undef local_c
#undef local_8

/* 006006a0 crt */
#define DAT_0063af90 (*(undefined4 *)((u8 *)&g.d_0063af90))
#define DAT_0063b24c (*(undefined4 *)((u8 *)&g.d_0063b24c))
#define DAT_0063b250 (*(undefined4 *)((u8 *)&g.d_0063b250))
#define DAT_0063b254 (*(undefined4 *)((u8 *)&g.d_0063b254))
#define DAT_0063b258 (*(undefined4 *)((u8 *)&g.d_0063b258))
#define local_18 (*(code * *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(undefined4 * *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(undefined4 *)(frame_ + FRAME_OFF(8)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(16)))
/* Library Function - Single Match
    _raise
   
   Library: Visual Studio 1998 Debug */

int __cdecl _raise(int _SigNum)

{
  int iVar1;
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  switch(_SigNum) {
  case 2:
    local_14 = &DAT_0063b24c;
    local_18 = DAT_0063b24c;
    break;
  default:
    return -1;
  case 4:
  case 8:
  case 0xb:
    iVar1 = siglookup(_SigNum);
    local_14 = (undefined4 *)(iVar1 + 8);
    local_18 = (code *)*local_14;
    break;
  case 0xf:
    local_14 = &DAT_0063b258;
    local_18 = DAT_0063b258;
    break;
  case 0x15:
    local_14 = &DAT_0063b250;
    local_18 = DAT_0063b250;
    break;
  case 0x16:
    local_14 = &DAT_0063b254;
    local_18 = DAT_0063b254;
  }
  if (local_18 != (code *)0x1) {
    if (local_18 == (code *)0x0) {
      __exit(3);
    }
    if (((_SigNum == 8) || (_SigNum == 0xb)) || (_SigNum == 4)) {
      local_10 = DAT_0063af90;
      DAT_0063af90 = 0;
      if (_SigNum == 8) {
        local_8 = DAT_0063af8c;
        DAT_0063af8c = 0x8c;
      }
    }
    if (_SigNum == 8) {
      for (local_c = DAT_0063af80; local_c < DAT_0063af84 + DAT_0063af80; local_c = local_c + 1) {
        *(undefined4 *)(local_c * 0xc + ADDR(0x63af10, ((u8 *)&g.d_0063af0c + 4))) = 0;
      }
    }
    else {
      *local_14 = 0;
    }
    if (_SigNum == 8) {
      (*local_18)(8,DAT_0063af8c);
    }
    else {
      (*local_18)(_SigNum);
      if ((_SigNum != 0xb) && (_SigNum != 4)) {
        return 0;
      }
    }
    if (_SigNum == 8) {
      DAT_0063af8c = local_8;
    }
    DAT_0063af90 = local_10;
    return 0;
  }
  return 0;
}
#undef DAT_0063af90
#undef DAT_0063b24c
#undef DAT_0063b250
#undef DAT_0063b254
#undef DAT_0063b258
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 006008c0 crt */
#define local_8 (*(undefined4 * *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    _siglookup
   
   Library: Visual Studio 1998 Debug */

undefined4 * __cdecl siglookup(int param_1)

{
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = &DAT_0063af08;
  do {
    if (local_8[1] == param_1) break;
    local_8 = local_8 + 3;
  } while (local_8 < &DAT_0063af08 + DAT_0063af88 * 3);
  if (local_8[1] != param_1) {
    local_8 = (undefined4 *)0x0;
  }
  return local_8;
}
#undef local_8

/* 00600930 crt */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    ___crtMessageBoxA
   
   Library: Visual Studio 1998 Debug */

int __cdecl ___crtMessageBoxA(LPCSTR _LpText,LPCSTR _LpCaption,UINT _UType)

{
  HMODULE hModule;
  int iVar1;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  if (DAT_0063b260 == (FARPROC)0x0) {
    hModule = LoadLibraryA("user32.dll");
    if (hModule != (HMODULE)0x0) {
      DAT_0063b260 = GetProcAddress(hModule,"MessageBoxA");
      if (DAT_0063b260 != (FARPROC)0x0) {
        DAT_0063b264 = GetProcAddress(hModule,"GetActiveWindow");
        DAT_0063b268 = GetProcAddress(hModule,"GetLastActivePopup");
        goto LAB_006009b5;
      }
    }
    iVar1 = 0;
  }
  else {
LAB_006009b5:
    if (DAT_0063b264 != (FARPROC)0x0) {
      local_8 = (*DAT_0063b264)();
    }
    if ((local_8 != 0) && (DAT_0063b268 != (FARPROC)0x0)) {
      local_8 = (*DAT_0063b268)(local_8);
    }
    iVar1 = (*DAT_0063b260)(local_8,_LpText,_LpCaption,_UType);
  }
  return iVar1;
}
#undef local_8

/* 00600a10 crt */
/* Library Function - Single Match
    __itoa
   
   Library: Visual Studio 1998 Debug */

char * __cdecl __itoa(int _Value,char *_Dest,int _Radix)

{
  if ((_Radix == 10) && (_Value < 0)) {
    xtoa(_Value,_Dest,10,1);
  }
  else {
    xtoa(_Value,_Dest,_Radix,0);
  }
  return _Dest;
}

/* 00600a70 crt */
#define local_c (*(char * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(char * *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    _xtoa
   
   Library: Visual Studio 1998 Debug */

void __cdecl xtoa(uint param_1,char *param_2,uint param_3,int param_4)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = param_2;
  if (param_4 != 0) {
    *param_2 = '-';
    local_8 = param_2 + 1;
    param_1 = -param_1;
  }
  local_c = local_8;
  do {
    pcVar2 = local_8;
    uVar3 = param_1 % param_3;
    param_1 = param_1 / param_3;
    cVar1 = (char)uVar3;
    if (uVar3 < 10) {
      *local_8 = cVar1 + '0';
    }
    else {
      *local_8 = cVar1 + 'W';
    }
    local_8 = local_8 + 1;
  } while (param_1 != 0);
  *local_8 = '\0';
  local_8 = pcVar2;
  do {
    cVar1 = *local_8;
    *local_8 = *local_c;
    *local_c = cVar1;
    local_8 = local_8 + -1;
    local_c = local_c + 1;
  } while (local_c < local_8);
  return;
}
#undef local_c
#undef local_8

/* 00600b30 crt */
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    __ltoa
   
   Library: Visual Studio 1998 Debug */

char * __cdecl __ltoa(long _Value,char *_Dest,int _Radix)

{
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((_Radix == 10) && (_Value < 0)) {
    local_8 = 1;
  }
  else {
    local_8 = 0;
  }
  xtoa(_Value,_Dest,_Radix,local_8);
  return _Dest;
}
#undef local_8

/* 00600b90 crt */
/* Library Function - Single Match
    __ultoa
   
   Library: Visual Studio 1998 Debug */

char * __cdecl __ultoa(ulong _Value,char *_Dest,int _Radix)

{
  xtoa(_Value,_Dest,_Radix,0);
  return _Dest;
}

/* 00600bc0 crt */
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    __i64toa
   
   Library: Visual Studio 1998 Debug */

char * __cdecl __i64toa(longlong _Val,char *_DstBuf,int _Radix)

{
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((_Radix == 10) && (_Val < 0x100000000)) && (_Val < 0)) {
    local_8 = 1;
  }
  else {
    local_8 = 0;
  }
  x64toa((undefined4)_Val,(*(undefined4 *)((char *)&_Val + 4)),_DstBuf,_Radix,local_8);
  return _DstBuf;
}
#undef local_8

/* 00600c30: written by hand in src/crt/conv.c */

/* 00600d10 crt */
/* Library Function - Single Match
    __ui64toa
   
   Library: Visual Studio 1998 Debug */

char * __cdecl __ui64toa(ulonglong _Val,char *_DstBuf,int _Radix)

{
  x64toa((undefined4)_Val,(*(undefined4 *)((char *)&_Val + 4)),_DstBuf,_Radix,0);
  return _DstBuf;
}

/* 00600d40: written by hand in src/crt/printf.c */

/* 00600df0 crt */
#define _DAT_0063aed8 (*(undefined4 *)((u8 *)&g.d_0063aed8))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    _setvbuf
   
   Library: Visual Studio 1998 Debug */

int __cdecl _setvbuf(FILE *_File,char *_Buf,int _Mode,size_t _Size)

{
  code *pcVar1;
  int iVar2;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 0;
  if ((_File == (FILE *)0x0) &&
     (iVar2 = __CrtDbgReport(2,"setvbuf.c",0x36,0,"str != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    iVar2 = (*pcVar1)();
    return iVar2;
  }
  if ((_Mode == 4) || (((1 < _Size && (_Size < 0x80000000)) && ((_Mode == 0 || (_Mode == 0x40))))))
  {
    _Size = _Size & 0xfffffffe;
    __flush(_File);
    __freebuf(_File);
    _File->_flag = _File->_flag & 0xffffc2f3;
    if ((_Mode & 4U) == 0) {
      if (_Buf == (char *)0x0) {
        _Buf = (char *)__malloc_dbg(_Size,2,"setvbuf.c",0x85);
        if (_Buf == (char *)0x0) {
          _DAT_0063aed8 = _DAT_0063aed8 + 1;
          return -1;
        }
        _File->_flag = _File->_flag | 0x408;
      }
      else {
        _File->_flag = _File->_flag | 0x500;
      }
    }
    else {
      _File->_flag = _File->_flag | 4;
      _Buf = (char *)&_File->_charbuf;
      _Size = 2;
    }
    _File->_bufsiz = _Size;
    _File->_base = _Buf;
    _File->_ptr = _File->_base;
    _File->_cnt = 0;
  }
  else {
    local_c = -1;
  }
  return local_c;
}
#undef _DAT_0063aed8
#undef local_c

/* 00600f50 crt */
/* Library Function - Single Match
    _$E2
   
   Library: Visual Studio 1998 Debug */

void __cdecl FUN_00600f50(void)

{
  FUN_00600f70();
  return;
}

/* 00600f70 crt */
#define DAT_006e55ac (*(LPTOP_LEVEL_EXCEPTION_FILTER *)((u8 *)&g.d_006e55ac))
/* Library Function - Single Match
    _$E1
   
   Library: Visual Studio 1998 Debug */

void __cdecl FUN_00600f70(void)

{
  _atexit(FUN_00601040);
  DAT_006e55ac = SetUnhandledExceptionFilter(__CxxUnhandledExceptionFilter);
  return;
}
#undef DAT_006e55ac

/* 00600fa0: written by hand in src/crt/eh.c */

/* 00601040 crt */
#define DAT_006e55ac (*(LPTOP_LEVEL_EXCEPTION_FILTER *)((u8 *)&g.d_006e55ac))
void __cdecl FUN_00601040(void)

{
  SetUnhandledExceptionFilter(DAT_006e55ac);
  return;
}
#undef DAT_006e55ac

/* 00601060 crt */
#define local_8 (*(uint *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    int __cdecl _ValidateRead(void const *,unsigned int)
   
   Library: Visual Studio 1998 Debug */

int __cdecl _ValidateRead(void *param_1,uint param_2)

{
  BOOL BVar1;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  BVar1 = IsBadReadPtr(param_1,param_2);
  local_8 = (uint)(BVar1 == 0);
  return local_8;
}
#undef local_8

/* 006010a0 crt */
#define local_8 (*(uint *)(frame_ + FRAME_OFF(0)))
/* Library Function - Multiple Matches With Different Base Names
    int __cdecl _ValidateRead(void const *,unsigned int)
    int __cdecl _ValidateWrite(void *,unsigned int)
   
   Library: Visual Studio 1998 Debug */

int __cdecl _ValidateWrite(void *param_1,uint param_2)

{
  BOOL BVar1;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  BVar1 = IsBadWritePtr(param_1,param_2);
  local_8 = (uint)(BVar1 == 0);
  return local_8;
}
#undef local_8

/* 006010e0 crt */
#define local_8 (*(uint *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    int __cdecl _ValidateExecute(int (__stdcall*)(void))
   
   Library: Visual Studio 1998 Debug */

int __cdecl _ValidateExecute(code *param_1)

{
  BOOL BVar1;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  BVar1 = IsBadCodePtr((FARPROC)param_1);
  local_8 = (uint)(BVar1 == 0);
  return local_8;
}
#undef local_8

/* 00601120: written by hand in src/crt/printf.c */

/* 00601210 crt */
#define local_24 (*(FILE *)(frame_ + FRAME_OFF(4)))
/* Library Function - Single Match
    __vsnprintf
   
   Library: Visual Studio 1998 Debug */

int __cdecl __vsnprintf(char *_Dest,size_t _Count,char *_Format,va_list _Args)

{
  code *pcVar1;
  int iVar2;
  undefined1 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (_Dest == (char *)0x0) {
    iVar2 = __CrtDbgReport(2,"vsprintf.c",0x5a,0,"string != NULL");
    if (iVar2 == 1) {
      pcVar1 = (code *)swi(3);
      iVar2 = (*pcVar1)();
      return iVar2;
    }
  }
  if (_Format == (char *)0x0) {
    iVar2 = __CrtDbgReport(2,"vsprintf.c",0x5b,0,"format != NULL");
    if (iVar2 == 1) {
      pcVar1 = (code *)swi(3);
      iVar2 = (*pcVar1)();
      return iVar2;
    }
  }
  local_24._flag = 0x42;
  local_24._base = _Dest;
  local_24._ptr = _Dest;
  local_24._cnt = _Count;
  iVar2 = __output(&local_24,_Format,_Args);
  local_24._cnt = local_24._cnt - 1;
  if (local_24._cnt < 0) {
    __flsbuf(0,&local_24);
  }
  else {
    *local_24._ptr = '\0';
  }
  return iVar2;
}
#undef local_24

/* 00601300: written by hand in src/crt/locale.c */

/* 00601560: written by hand in src/crt/locale.c */

/* 00601700: written by hand in src/crt/io.c */

/* 00601750: written by hand in src/crt/io.c */

/* 00601cf0 crt */
#define DAT_006e69f0 (*(undefined4 *)((u8 *)&g.d_006e69f0))
#define DAT_006e6b2c (*(int *)((u8 *)&g.d_006e6b2c))
#define local_10 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(undefined4 * *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    __alloc_osfhnd
   
   Library: Visual Studio 1998 Debug */

int __cdecl __alloc_osfhnd(void)

{
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = -1;
  local_10 = 0;
  do {
    if (0x3f < local_10) {
      return local_c;
    }
    if ((&DAT_006e69f0)[local_10] == 0) {
      local_8 = (undefined4 *)__malloc_dbg(0x100,2,"osfinfo.c",0x79);
      if (local_8 == (undefined4 *)0x0) {
        return local_c;
      }
      (&DAT_006e69f0)[local_10] = local_8;
      DAT_006e6b2c = DAT_006e6b2c + 0x20;
      for (; local_8 < (undefined4 *)((&DAT_006e69f0)[local_10] + 0x100); local_8 = local_8 + 2) {
        *(undefined1 *)(local_8 + 1) = 0;
        *local_8 = 0xffffffff;
        *(undefined1 *)((int)local_8 + 5) = 10;
      }
      return local_10 << 5;
    }
    for (local_8 = (undefined4 *)(&DAT_006e69f0)[local_10];
        local_8 < (undefined4 *)((&DAT_006e69f0)[local_10] + 0x100); local_8 = local_8 + 2) {
      if ((*(byte *)(local_8 + 1) & 1) == 0) {
        *local_8 = 0xffffffff;
        local_c = ((int)local_8 - (&DAT_006e69f0)[local_10] >> 3) + local_10 * 0x20;
        break;
      }
    }
    if (local_c != -1) {
      return local_c;
    }
    local_10 = local_10 + 1;
  } while( true );
}
#undef DAT_006e69f0
#undef DAT_006e6b2c
#undef local_10
#undef local_c
#undef local_8

/* 00601e40 crt */
#define DAT_00639f18 (*(undefined4 *)((u8 *)&g.d_00639f18))
#define DAT_006e69f0 (*(undefined4 *)((u8 *)&g.d_006e69f0))
#define DAT_006e6b2c (*(uint *)((u8 *)&g.d_006e6b2c))
/* Library Function - Single Match
    __set_osfhnd
   
   Library: Visual Studio 1998 Debug */

int __cdecl __set_osfhnd(int param_1,intptr_t param_2)

{
  int iVar1;
  
  if (((uint)param_1 < DAT_006e6b2c) &&
     (*(int *)(*(int *)((int)&DAT_006e69f0 + ((int)(param_1 & 0xffffffe0U) >> 3)) +
              (param_1 & 0x1fU) * 8) == -1)) {
    if (DAT_00639fd0 == 1) {
      if (param_1 == 0) {
        SetStdHandle(0xfffffff6,(HANDLE)param_2);
      }
      else if (param_1 == 1) {
        SetStdHandle(0xfffffff5,(HANDLE)param_2);
      }
      else if (param_1 == 2) {
        SetStdHandle(0xfffffff4,(HANDLE)param_2);
      }
    }
    *(intptr_t *)
     (*(int *)((int)&DAT_006e69f0 + ((int)(param_1 & 0xffffffe0U) >> 3)) + (param_1 & 0x1fU) * 8) =
         param_2;
    iVar1 = 0;
  }
  else {
    crt_errno = 9;
    DAT_00639f18 = 0;
    iVar1 = -1;
  }
  return iVar1;
}
#undef DAT_00639f18
#undef DAT_006e69f0
#undef DAT_006e6b2c

/* 00601f40 crt */
#define DAT_00639f18 (*(undefined4 *)((u8 *)&g.d_00639f18))
#define DAT_006e69f0 (*(undefined4 *)((u8 *)&g.d_006e69f0))
#define DAT_006e6b2c (*(uint *)((u8 *)&g.d_006e6b2c))
/* Library Function - Single Match
    __free_osfhnd
   
   Library: Visual Studio 1998 Debug */

int __cdecl __free_osfhnd(int param_1)

{
  int iVar1;
  
  if ((((uint)param_1 < DAT_006e6b2c) &&
      ((*(byte *)(*(int *)((int)&DAT_006e69f0 + ((int)(param_1 & 0xffffffe0U) >> 3)) + 4 +
                 (param_1 & 0x1fU) * 8) & 1) != 0)) &&
     (*(int *)(*(int *)((int)&DAT_006e69f0 + ((int)(param_1 & 0xffffffe0U) >> 3)) +
              (param_1 & 0x1fU) * 8) != -1)) {
    if (DAT_00639fd0 == 1) {
      if (param_1 == 0) {
        SetStdHandle(0xfffffff6,(HANDLE)0x0);
      }
      else if (param_1 == 1) {
        SetStdHandle(0xfffffff5,(HANDLE)0x0);
      }
      else if (param_1 == 2) {
        SetStdHandle(0xfffffff4,(HANDLE)0x0);
      }
    }
    *(undefined4 *)
     (*(int *)((int)&DAT_006e69f0 + ((int)(param_1 & 0xffffffe0U) >> 3)) + (param_1 & 0x1fU) * 8) =
         0xffffffff;
    iVar1 = 0;
  }
  else {
    crt_errno = 9;
    DAT_00639f18 = 0;
    iVar1 = -1;
  }
  return iVar1;
}
#undef DAT_00639f18
#undef DAT_006e69f0
#undef DAT_006e6b2c

/* 00602060 crt */
#define DAT_00639f18 (*(undefined4 *)((u8 *)&g.d_00639f18))
#define DAT_006e69f0 (*(undefined4 *)((u8 *)&g.d_006e69f0))
#define DAT_006e6b2c (*(uint *)((u8 *)&g.d_006e6b2c))
/* Library Function - Single Match
    __get_osfhandle
   
   Library: Visual Studio 1998 Debug */

intptr_t __cdecl __get_osfhandle(int _FileHandle)

{
  intptr_t iVar1;
  
  if (((uint)_FileHandle < DAT_006e6b2c) &&
     ((*(byte *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) + 4 +
                (_FileHandle & 0x1fU) * 8) & 1) != 0)) {
    iVar1 = *(intptr_t *)
             (*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) +
             (_FileHandle & 0x1fU) * 8);
  }
  else {
    crt_errno = 9;
    DAT_00639f18 = 0;
    iVar1 = -1;
  }
  return iVar1;
}
#undef DAT_00639f18
#undef DAT_006e69f0
#undef DAT_006e6b2c

/* 006020e0 crt */
#define DAT_00639f18 (*(undefined4 *)((u8 *)&g.d_00639f18))
#define DAT_006e69f0 (*(undefined4 *)((u8 *)&g.d_006e69f0))
#define local_10 (*(byte *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    __open_osfhandle
   
   Library: Visual Studio 1998 Debug */

int __cdecl __open_osfhandle(intptr_t _OSFileHandle,int _Flags)

{
  DWORD DVar1;
  uint uVar2;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_10 = 0;
  if ((_Flags & 8U) != 0) {
    local_10 = 0x20;
  }
  if ((_Flags & 0x4000U) != 0) {
    local_10 = local_10 | 0x80;
  }
  DVar1 = GetFileType((HANDLE)_OSFileHandle);
  if (DVar1 == 0) {
    DVar1 = GetLastError();
    __dosmaperr(DVar1);
    uVar2 = 0xffffffff;
  }
  else {
    if (DVar1 == 2) {
      local_10 = local_10 | 0x40;
    }
    else if (DVar1 == 3) {
      local_10 = local_10 | 8;
    }
    uVar2 = __alloc_osfhnd();
    if (uVar2 == 0xffffffff) {
      crt_errno = 0x18;
      DAT_00639f18 = 0;
      uVar2 = 0xffffffff;
    }
    else {
      __set_osfhnd(uVar2,_OSFileHandle);
      *(byte *)(*(int *)((int)&DAT_006e69f0 + ((int)(uVar2 & 0xffffffe0) >> 3)) + 4 +
               (uVar2 & 0x1f) * 8) = local_10 | 1;
    }
  }
  return uVar2;
}
#undef DAT_00639f18
#undef DAT_006e69f0
#undef local_10

/* 006021e0 crt */
#define DAT_00639f18 (*(DWORD *)((u8 *)&g.d_00639f18))
#define DAT_006e69f0 (*(undefined4 *)((u8 *)&g.d_006e69f0))
#define DAT_006e6b2c (*(uint *)((u8 *)&g.d_006e6b2c))
#define local_8 (*(DWORD *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    __commit
   
   Library: Visual Studio 1998 Debug */

int __cdecl __commit(int _FileHandle)

{
  HANDLE hFile;
  BOOL BVar1;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((((uint)_FileHandle < DAT_006e6b2c) &&
      ((*(byte *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) + 4 +
                 (_FileHandle & 0x1fU) * 8) & 1) != 0)) &&
     ((*(byte *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) + 4 +
                (_FileHandle & 0x1fU) * 8) & 1) != 0)) {
    hFile = (HANDLE)__get_osfhandle(_FileHandle);
    BVar1 = FlushFileBuffers(hFile);
    if (BVar1 == 0) {
      local_8 = GetLastError();
    }
    else {
      local_8 = 0;
    }
    if (local_8 == 0) {
      return 0;
    }
    DAT_00639f18 = local_8;
  }
  crt_errno = 9;
  return -1;
}
#undef DAT_00639f18
#undef DAT_006e69f0
#undef DAT_006e6b2c
#undef local_8

/* 006022c0 crt */
#define DAT_006e69f0 (*(undefined4 *)((u8 *)&g.d_006e69f0))
#define DAT_006e6b2c (*(uint *)((u8 *)&g.d_006e6b2c))
/* Library Function - Single Match
    __isatty
   
   Library: Visual Studio 1998 Debug */

int __cdecl __isatty(int _FileHandle)

{
  uint uVar1;
  
  if ((uint)_FileHandle < DAT_006e6b2c) {
    uVar1 = (int)*(char *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) +
                           4 + (_FileHandle & 0x1fU) * 8) & 0x40;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}
#undef DAT_006e69f0
#undef DAT_006e6b2c

/* 00602310: written by hand in src/crt/locale.c */

/* 006023e0 crt */
/* Library Function - Single Match
    __aulldiv
   
   Library: Visual Studio 1998 Debug */

int __stdcall __aulldiv(uint param_1,uint param_2,uint param_3,uint param_4)

{
  ulonglong uVar1;
  longlong lVar2;
  int iVar3;
  uint uVar4;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar5;
  
  uVar9 = param_1;
  uVar5 = param_4;
  uVar6 = param_2;
  uVar8 = param_3;
  if (param_4 == 0) {
    iVar3 = (int)(((ulonglong)param_2 % (ulonglong)param_3 << 0x20 | (ulonglong)param_1) /
                 (ulonglong)param_3);
  }
  else {
    do {
      uVar4 = uVar5 >> 1;
      uVar8 = (uint)(CONCAT14((uVar5 & 1) != 0,uVar8) >> 1);
      uVar7 = uVar6 >> 1;
      uVar9 = (uint)(CONCAT14((uVar6 & 1) != 0,uVar9) >> 1);
      uVar5 = uVar4;
      uVar6 = uVar7;
    } while (uVar4 != 0);
    uVar1 = CONCAT44(uVar7,uVar9) / (ulonglong)uVar8;
    iVar3 = (int)uVar1;
    lVar2 = (ulonglong)param_3 * (uVar1 & 0xffffffff);
    uVar8 = (uint)((ulonglong)lVar2 >> 0x20);
    uVar9 = uVar8 + iVar3 * param_4;
    if (((CARRY4(uVar8,iVar3 * param_4)) || (param_2 < uVar9)) ||
       ((param_2 <= uVar9 && (param_1 < (uint)lVar2)))) {
      iVar3 = iVar3 + -1;
    }
  }
  return iVar3;
}

/* 00602450 crt */
/* Library Function - Single Match
    __aullrem
   
   Library: Visual Studio 1998 Debug */

int __stdcall __aullrem(uint param_1,uint param_2,uint param_3,uint param_4)

{
  ulonglong uVar1;
  longlong lVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  
  uVar4 = param_1;
  uVar8 = param_4;
  uVar9 = param_2;
  uVar3 = param_3;
  if (param_4 == 0) {
    iVar6 = (int)(((ulonglong)param_2 % (ulonglong)param_3 << 0x20 | (ulonglong)param_1) %
                 (ulonglong)param_3);
  }
  else {
    do {
      uVar5 = uVar8 >> 1;
      uVar3 = (uint)(CONCAT14((uVar8 & 1) != 0,uVar3) >> 1);
      uVar7 = uVar9 >> 1;
      uVar4 = (uint)(CONCAT14((uVar9 & 1) != 0,uVar4) >> 1);
      uVar8 = uVar5;
      uVar9 = uVar7;
    } while (uVar5 != 0);
    uVar1 = CONCAT44(uVar7,uVar4) / (ulonglong)uVar3;
    uVar3 = (int)uVar1 * param_4;
    lVar2 = (uVar1 & 0xffffffff) * (ulonglong)param_3;
    uVar8 = (uint)((ulonglong)lVar2 >> 0x20);
    uVar4 = (uint)lVar2;
    uVar9 = uVar8 + uVar3;
    if (((CARRY4(uVar8,uVar3)) || (param_2 < uVar9)) || ((param_2 <= uVar9 && (param_1 < uVar4)))) {
      uVar4 = uVar4 - param_3;
    }
    iVar6 = -(uVar4 - param_1);
  }
  return iVar6;
}

/* 006024d0 crt */
#define local_c (*(undefined4 *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    __fcloseall
   
   Library: Visual Studio 1998 Debug */

int __cdecl __fcloseall(void)

{
  int iVar1;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  for (local_c = 3; local_c < DAT_006e69e0; local_c = local_c + 1) {
    if (*(int *)(DAT_006e5694 + local_c * 4) != 0) {
      if ((*(byte *)(*(int *)(DAT_006e5694 + local_c * 4) + 0xc) & 0x83) != 0) {
        iVar1 = _fclose(*(FILE **)(DAT_006e5694 + local_c * 4));
        if (iVar1 != -1) {
          local_8 = local_8 + 1;
        }
      }
      if (0x13 < local_c) {
        __free_dbg(*(undefined4 *)(DAT_006e5694 + local_c * 4),2);
        *(undefined4 *)(DAT_006e5694 + local_c * 4) = 0;
      }
    }
  }
  return local_8;
}
#undef local_c
#undef local_8

/* 00602590 crt */
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    __statusfp
   
   Library: Visual Studio 1998 Debug */

uint __cdecl __statusfp(void)

{
  uint uVar1;
  undefined2 in_FPUStatusWord;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = CONCAT22((*(undefined2 *)((char *)&local_8 + 2)),in_FPUStatusWord);
  uVar1 = __abstract_sw(local_8);
  return uVar1;
}
#undef local_8

/* 006025c0 crt */
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    __clearfp
   
   Library: Visual Studio 1998 Debug */

uint __cdecl __clearfp(void)

{
  uint uVar1;
  undefined2 in_FPUStatusWord;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = CONCAT22((*(undefined2 *)((char *)&local_8 + 2)),in_FPUStatusWord);
  uVar1 = __abstract_sw(local_8);
  return uVar1;
}
#undef local_8

/* 006025f0 crt */
#define local_14 (*(undefined4 *)(frame_ + FRAME_OFF(4)))
/* Library Function - Single Match
    __control87
   
   Library: Visual Studio 1998 Debug */

uint __cdecl __control87(uint _NewValue,uint _Mask)

{
  uint uVar1;
  undefined2 in_FPUControlWord;
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_14 = CONCAT22((*(undefined2 *)((char *)&local_14 + 2)),in_FPUControlWord);
  uVar1 = __abstract_cw(local_14);
  uVar1 = ~_Mask & uVar1 | _NewValue & _Mask;
  __hw_cw(uVar1);
  return uVar1;
}
#undef local_14

/* 00602640 crt */
/* Library Function - Single Match
    __controlfp
   
   Library: Visual Studio 1998 Debug */

uint __cdecl __controlfp(uint _NewValue,uint _Mask)

{
  uint uVar1;
  
  uVar1 = __control87(_NewValue,_Mask & 0xfff7ffff);
  return uVar1;
}

/* 00602670 crt */
#define DAT_0063af90 (*(int *)((u8 *)&g.d_0063af90))
/* Library Function - Single Match
    __fpreset
   
   Library: Visual Studio 1998 Debug */

void __cdecl __fpreset(void)

{
  int iVar1;
  
  iVar1 = DAT_0063af90;
  __setdefaultprecision();
  if ((iVar1 != 0) && ((**(uint **)(iVar1 + 4) & 0x10008) != 0)) {
    iVar1 = *(int *)(iVar1 + 4);
    *(undefined4 *)(iVar1 + 0x20) = 0;
    *(undefined4 *)(iVar1 + 0x24) = 0xffff;
  }
  return;
}
#undef DAT_0063af90

/* 006026d0 crt */
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    __abstract_cw
   
   Library: Visual Studio 1998 Debug */

uint __cdecl __abstract_cw(uint param_1)

{
  uint uVar1;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  if ((param_1 & 1) != 0) {
    local_8 = 0x10;
  }
  if ((param_1 & 4) != 0) {
    local_8 = local_8 | 8;
  }
  if ((param_1 & 8) != 0) {
    local_8 = local_8 | 4;
  }
  if ((param_1 & 0x10) != 0) {
    local_8 = local_8 | 2;
  }
  if ((param_1 & 0x20) != 0) {
    local_8 = local_8 | 1;
  }
  if ((param_1 & 2) != 0) {
    local_8 = local_8 | 0x80000;
  }
  uVar1 = param_1 & 0xc00;
  if (uVar1 < 0x401) {
    if (uVar1 == 0x400) {
      local_8 = local_8 | 0x100;
    }
  }
  else if (uVar1 == 0x800) {
    local_8 = local_8 | 0x200;
  }
  else if (uVar1 == 0xc00) {
    local_8 = local_8 | 0x300;
  }
  if ((param_1 & 0x300) == 0) {
    local_8 = local_8 | 0x20000;
  }
  else if ((param_1 & 0x300) == 0x200) {
    local_8 = local_8 | 0x10000;
  }
  if ((param_1 & 0x1000) != 0) {
    local_8 = local_8 | 0x40000;
  }
  return local_8;
}
#undef local_8

/* 00602820 crt */
/* Library Function - Single Match
    __hw_cw
   
   Library: Visual Studio 1998 Debug */

ushort __cdecl __hw_cw(uint param_1)

{
  ushort uVar1;
  uint uVar2;
  
  uVar1 = (ushort)((param_1 & 0x10) != 0);
  if ((param_1 & 8) != 0) {
    uVar1 = uVar1 | 4;
  }
  if ((param_1 & 4) != 0) {
    uVar1 = uVar1 | 8;
  }
  if ((param_1 & 2) != 0) {
    uVar1 = uVar1 | 0x10;
  }
  if ((param_1 & 1) != 0) {
    uVar1 = uVar1 | 0x20;
  }
  if ((param_1 & 0x80000) != 0) {
    uVar1 = uVar1 | 2;
  }
  uVar2 = param_1 & 0x300;
  if (uVar2 < 0x101) {
    if (uVar2 == 0x100) {
      uVar1 = uVar1 | 0x400;
    }
  }
  else if (uVar2 == 0x200) {
    uVar1 = uVar1 | 0x800;
  }
  else if (uVar2 == 0x300) {
    uVar1 = uVar1 | 0xc00;
  }
  if ((param_1 & 0x30000) == 0) {
    uVar1 = uVar1 | 0x300;
  }
  else if ((param_1 & 0x30000) == 0x10000) {
    uVar1 = uVar1 | 0x200;
  }
  if ((param_1 & 0x40000) != 0) {
    uVar1 = uVar1 | 0x1000;
  }
  return uVar1;
}

/* 006029f0 crt */
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    __abstract_sw
   
   Library: Visual Studio 1998 Debug */

uint __cdecl __abstract_sw(uint param_1)

{
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  if ((param_1 & 1) != 0) {
    local_8 = 0x10;
  }
  if ((param_1 & 4) != 0) {
    local_8 = local_8 | 8;
  }
  if ((param_1 & 8) != 0) {
    local_8 = local_8 | 4;
  }
  if ((param_1 & 0x10) != 0) {
    local_8 = local_8 | 2;
  }
  if ((param_1 & 0x20) != 0) {
    local_8 = local_8 | 1;
  }
  if ((param_1 & 2) != 0) {
    local_8 = local_8 | 0x80000;
  }
  return local_8;
}
#undef local_8

/* 00602a70 crt */
/* Library Function - Single Match
    __fptrap
   
   Library: Visual Studio 1998 Debug */

void __cdecl __fptrap(void)

{
  __amsg_exit(2);
  return;
}

/* 00602a90 crt */
#define local_10 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_8 (*(byte *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    __ZeroTail
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl __ZeroTail(int param_1,int param_2)

{
  uint uVar1;
  byte bVar2;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_10 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  bVar2 = (byte)(param_2 >> 0x1f);
  local_8 = 0x1f - ((((byte)param_2 ^ bVar2) - bVar2 & 0x1f ^ bVar2) - bVar2);
  uVar1 = ~(-1 << (local_8 & 0x1f)) & *(uint *)(param_1 + local_10 * 4);
  while( true ) {
    if (uVar1 != 0) {
      return 0;
    }
    local_10 = local_10 + 1;
    if (2 < local_10) break;
    uVar1 = *(uint *)(param_1 + local_10 * 4);
  }
  return 1;
}
#undef local_10
#undef local_8

/* 00602b30 crt */
#define local_14 (*(undefined4 *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(undefined4 *)(frame_ + FRAME_OFF(8)))
#define local_8 (*(undefined1 *)(frame_ + FRAME_OFF(16)))
/* Library Function - Single Match
    __IncMan
   
   Library: Visual Studio 1998 Debug */

int __cdecl __IncMan(int param_1,int param_2)

{
  byte bVar1;
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_10 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  bVar1 = (byte)(param_2 >> 0x1f);
  local_8 = 0x1f - ((((byte)param_2 ^ bVar1) - bVar1 & 0x1f ^ bVar1) - bVar1);
  local_14 = ___addl(*(undefined4 *)(param_1 + local_10 * 4),1 << (local_8 & 0x1f),
                     local_10 * 4 + param_1);
  while ((local_10 = local_10 + -1, -1 < local_10 && (local_14 != 0))) {
    local_14 = ___addl(*(undefined4 *)(param_1 + local_10 * 4),1,local_10 * 4 + param_1);
  }
  return local_14;
}
#undef local_14
#undef local_10
#undef local_8

/* 00602bf0 crt */
#define local_1c (*(undefined4 *)(frame_ + FRAME_OFF(4)))
#define local_14 (*(undefined4 *)(frame_ + FRAME_OFF(12)))
#define local_c (*(undefined1 *)(frame_ + FRAME_OFF(20)))
/* Library Function - Single Match
    __RoundMan
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl __RoundMan(int param_1,int param_2)

{
  uint *puVar1;
  byte bVar2;
  int iVar3;
  undefined1 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_1c = 0;
  local_14 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  bVar2 = (byte)(param_2 >> 0x1f);
  local_c = 0x1f - ((((byte)param_2 ^ bVar2) - bVar2 & 0x1f ^ bVar2) - bVar2);
  if ((1 << (local_c & 0x1f) & *(uint *)(param_1 + local_14 * 4)) != 0) {
    iVar3 = __ZeroTail(param_1,param_2 + 1);
    if (iVar3 == 0) {
      local_1c = __IncMan(param_1,param_2 + -1);
    }
  }
  puVar1 = (uint *)(param_1 + local_14 * 4);
  *puVar1 = *puVar1 & -1 << (local_c & 0x1f);
  while (local_14 = local_14 + 1, local_14 < 3) {
    *(undefined4 *)(param_1 + local_14 * 4) = 0;
  }
  return local_1c;
}
#undef local_1c
#undef local_14
#undef local_c

/* 00602cd0 crt */
#define local_10 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_c (*(undefined4 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(undefined4 * *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    __CopyMan
   
   Library: Visual Studio 1998 Debug */

void __cdecl __CopyMan(undefined4 *param_1,undefined4 *param_2)

{
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = param_2;
  local_c = param_1;
  for (local_10 = 0; local_10 < 3; local_10 = local_10 + 1) {
    *local_c = *local_8;
    local_8 = local_8 + 1;
    local_c = local_c + 1;
  }
  return;
}
#undef local_10
#undef local_c
#undef local_8

/* 00602d20 crt */
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    __FillZeroMan
   
   Library: Visual Studio 1998 Debug */

void __cdecl __FillZeroMan(int param_1)

{
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; local_8 < 3; local_8 = local_8 + 1) {
    *(undefined4 *)(param_1 + local_8 * 4) = 0;
  }
  return;
}
#undef local_8

/* 00602d60 crt */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    __IsZeroMan
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl __IsZeroMan(int param_1)

{
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  while( true ) {
    if (2 < local_8) {
      return 1;
    }
    if (*(int *)(param_1 + local_8 * 4) != 0) break;
    local_8 = local_8 + 1;
  }
  return 0;
}
#undef local_8

/* 00602db0 crt */
#define local_10 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
#define local_c (*(undefined4 *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(undefined1 *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    __ShrMan
   
   Library: Visual Studio 1998 Debug */

void __cdecl __ShrMan(int param_1,int param_2)

{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar3 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  local_8 = (byte)(param_2 >> 0x1f);
  local_8 = (((byte)param_2 ^ local_8) - local_8 & 0x1f ^ local_8) - local_8;
  local_c = 0;
  for (local_10 = 0; local_10 < 3; local_10 = local_10 + 1) {
    uVar2 = *(uint *)(param_1 + local_10 * 4);
    puVar1 = (uint *)(param_1 + local_10 * 4);
    *puVar1 = *puVar1 >> (local_8 & 0x1f);
    puVar1 = (uint *)(param_1 + local_10 * 4);
    *puVar1 = *puVar1 | local_c;
    local_c = (uVar2 & ~(-1 << (local_8 & 0x1f))) << (0x20 - local_8 & 0x1f);
  }
  for (local_10 = 2; -1 < local_10; local_10 = local_10 + -1) {
    if (local_10 < iVar3) {
      *(undefined4 *)(param_1 + local_10 * 4) = 0;
    }
    else {
      *(undefined4 *)(param_1 + local_10 * 4) = *(undefined4 *)(param_1 + (local_10 - iVar3) * 4);
    }
  }
  return;
}
#undef local_10
#undef local_c
#undef local_8

/* 00602ea0 crt */
#define local_34 (*(undefined1 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_24 (*(uint *)(frame_ + FRAME_OFF(20)))
#define local_20 (*(undefined4 *)(frame_ + FRAME_OFF(24)))
#define local_1c (*(uint *)(frame_ + FRAME_OFF(28)))
#define local_18 (*(uint *)(frame_ + FRAME_OFF(32)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(36)))
#define local_10 (*(byte *)(frame_ + FRAME_OFF(40)))
#define local_c (*(int *)(frame_ + FRAME_OFF(44)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(48)))
/* Library Function - Single Match
    __ld12cvt
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl __ld12cvt(ushort *param_1,uint *param_2,int *param_3)

{
  int iVar1;
  undefined1 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = (param_1[5] & 0x7fff) - 0x3fff;
  local_24 = param_1[5] & 0x8000;
  local_1c = *(uint *)(param_1 + 3);
  local_18 = *(uint *)(param_1 + 1);
  local_14 = (uint)*param_1 << 0x10;
  if (local_8 == -0x3fff) {
    local_c = 0;
    iVar1 = __IsZeroMan(&local_1c);
    if (iVar1 == 0) {
      __FillZeroMan(&local_1c);
      local_20 = 2;
    }
    else {
      local_20 = 0;
    }
  }
  else {
    __CopyMan(local_34,&local_1c);
    iVar1 = __RoundMan(&local_1c,param_3[2]);
    if (iVar1 != 0) {
      local_8 = local_8 + 1;
    }
    if (local_8 < param_3[1] - param_3[2]) {
      __FillZeroMan(&local_1c);
      local_c = 0;
      local_20 = 2;
    }
    else if (param_3[1] < local_8) {
      if (local_8 < *param_3) {
        local_c = param_3[5] + local_8;
        local_1c = local_1c & 0x7fffffff;
        __ShrMan(&local_1c,param_3[3]);
        local_20 = 0;
      }
      else {
        __FillZeroMan(&local_1c);
        local_1c = local_1c | 0x80000000;
        __ShrMan(&local_1c,param_3[3]);
        local_c = param_3[5] + *param_3;
        local_20 = 1;
      }
    }
    else {
      iVar1 = param_3[1] - local_8;
      __CopyMan(&local_1c,local_34);
      __ShrMan(&local_1c,iVar1);
      __RoundMan(&local_1c,param_3[2]);
      __ShrMan(&local_1c,param_3[3] + 1);
      local_c = 0;
      local_20 = 2;
    }
  }
  local_10 = 0x20 - ((char)param_3[3] + '\x01');
  local_1c = (local_24 == 0) - 1 & 0x80000000 | local_c << (local_10 & 0x1f) | local_1c;
  if (param_3[4] == 0x40) {
    param_2[1] = local_1c;
    *param_2 = local_18;
  }
  else if (param_3[4] == 0x20) {
    *param_2 = local_1c;
  }
  return local_20;
}
#undef local_34
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 00603110 crt */
/* Library Function - Multiple Matches With Different Base Names
    __ld12tod
    __ld12tof
   
   Library: Visual Studio 1998 Debug */

void __cdecl FUN_00603110(undefined4 param_1,undefined4 param_2)

{
  __ld12cvt(param_1,param_2,&DAT_0063b280);
  return;
}

/* 00603140 crt */
/* Library Function - Multiple Matches With Different Base Names
    __ld12tod
    __ld12tof
   
   Library: Visual Studio 1998 Debug */

void __cdecl FUN_00603140(undefined4 param_1,undefined4 param_2)

{
  __ld12cvt(param_1,param_2,&DAT_0063b298);
  return;
}

/* 00603170: written by hand in src/crt/float.c */

/* 00603240 crt */
#define local_14 (*(char * *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(_LDBL12 *)(frame_ + FRAME_OFF(8)))
/* Library Function - Multiple Matches With Different Base Names
    __atodbl
    __atoflt
   
   Library: Visual Studio 1998 Debug */

void __cdecl FUN_00603240(undefined4 param_1,char *param_2)

{
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  ___strgtold12(&local_10,&local_14,param_2,0,0,0,0);
  FUN_00603110(&local_10,param_1);
  return;
}
#undef local_14
#undef local_10

/* 00603280: written by hand in src/crt/float.c */

/* 006032c0 crt */
#define local_14 (*(char * *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(_LDBL12 *)(frame_ + FRAME_OFF(8)))
/* Library Function - Multiple Matches With Different Base Names
    __atodbl
    __atoflt
   
   Library: Visual Studio 1998 Debug */

void __cdecl FUN_006032c0(undefined4 param_1,char *param_2)

{
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  ___strgtold12(&local_10,&local_14,param_2,0,0,0,0);
  FUN_00603140(&local_10,param_1);
  return;
}
#undef local_14
#undef local_10

/* 00603300: written by hand in src/crt/float.c */

/* 006033e0 crt */
#define _DAT_006e55d0 (*(undefined4 *)((u8 *)&g.d_006e55d0))
#define _DAT_006e55d4 (*(undefined4 *)((u8 *)&g.d_006e55d4))
#define _DAT_006e55d8 (*(undefined4 *)((u8 *)&g.d_006e55d8))
#define _DAT_006e55dc (*(undefined4 *)((u8 *)&g.d_006e55dc))
#define local_10 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
#define local_c (*(undefined4 *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(8)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __fltout
   
   Library: Visual Studio 1998 Debug */

undefined * __cdecl __fltout(undefined4 param_1,undefined4 param_2)

{
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  u32 pargs_[2] = {(u32)(uptr)param_1, (u32)(uptr)param_2};  /* the arguments, contiguous as on the original stack */
#define param_1 (*(undefined4 *)&pargs_[0])
#define param_2 (*(undefined4 *)&pargs_[1])
  
  ___dtold(&local_10,&param_1);
  _DAT_006e55d8 = FUN_006051a0(local_10,local_c,local_8,0x11,0,&DAT_006e55b0);
  _DAT_006e55d0 = (int)DAT_006e55b2;
  _DAT_006e55d4 = (int)DAT_006e55b0;
  _DAT_006e55dc = ADDR(0x6e55b4, ((u8 *)&g.d_006e55b2 + 2));
  return &DAT_006e55d0;
}
#undef _DAT_006e55d0
#undef _DAT_006e55d4
#undef _DAT_006e55d8
#undef _DAT_006e55dc
#undef local_10
#undef local_c
#undef local_8
#undef param_1
#undef param_2

/* 00603450 crt */
#define local_18 (*(short *)(frame_ + FRAME_OFF(0)))
#define local_10 (*(uint *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    ___dtold
   
   Library: Visual Studio 1998 Debug */

void __cdecl ___dtold(uint *param_1,uint *param_2)

{
  ushort uVar1;
  uint uVar2;
  ushort uVar3;
  uint uVar4;
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_10 = 0x80000000;
  uVar4 = (*(ushort *)((int)param_2 + 6) & 0x7ff0) >> 4;
  uVar1 = *(ushort *)((int)param_2 + 6);
  uVar2 = *param_2;
  local_18 = (short)uVar4;
  if (uVar4 == 0) {
    if (((param_2[1] & 0xfffff) == 0) && (uVar2 == 0)) {
      param_1[1] = 0;
      *param_1 = 0;
      *(undefined2 *)(param_1 + 2) = 0;
      return;
    }
    uVar3 = 0x3c01;
    local_10 = 0;
  }
  else if (uVar4 == 0x7ff) {
    uVar3 = 0x7fff;
  }
  else {
    uVar3 = local_18 + 0x3c00;
  }
  param_1[1] = uVar2 >> 0x15 | (param_2[1] & 0xfffff) << 0xb | local_10;
  *param_1 = uVar2 << 0xb;
  while ((*(byte *)((int)param_1 + 7) & 0x80) == 0) {
    param_1[1] = *param_1 >> 0x1f | param_1[1] * 2;
    *param_1 = *param_1 << 1;
    uVar3 = uVar3 - 1;
  }
  *(ushort *)(param_1 + 2) = uVar3 | uVar1 & 0x8000;
  return;
}
#undef local_18
#undef local_10

/* 006035d0 crt */
#define local_8 (*(wchar_t * *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    _wcslen
   
   Library: Visual Studio 1998 Debug */

size_t __cdecl _wcslen(wchar_t *_Str)

{
  wchar_t *pwVar1;
  wchar_t wVar2;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = _Str;
  do {
    pwVar1 = local_8 + 1;
    wVar2 = *local_8;
    local_8 = pwVar1;
  } while (wVar2 != L'\0');
  return ((int)pwVar1 - (int)_Str >> 1) - 1;
}
#undef local_8

/* 00603620 crt */
#define DAT_0063b36c (*(int *)((u8 *)&g.d_0063b36c))
/* Library Function - Single Match
    ___tzset
   
   Library: Visual Studio 1998 Debug */

void __cdecl ___tzset(void)

{
  if (DAT_0063b36c == 0) {
    __tzset();
    DAT_0063b36c = DAT_0063b36c + 1;
  }
  return;
}
#undef DAT_0063b36c

/* 00603650 crt */
#define DAT_0063b350 (*(undefined4 *)((u8 *)&g.d_0063b350))
#define DAT_0063b360 (*(undefined4 *)((u8 *)&g.d_0063b360))
#define DAT_006e55e0 (*(undefined4 *)((u8 *)&g.d_006e55e0))
#define DAT_006e562e (*(short *)((u8 *)&g.d_006e562e))
#define DAT_006e5682 (*(short *)((u8 *)&g.d_006e5682))
#define local_c (*(char * *)(frame_ + FRAME_OFF(4)))
/* Library Function - Single Match
    __tzset
   
   Library: Visual Studio 1998 Debug */

void __cdecl __tzset(void)

{
  char cVar1;
  char *_Str1;
  DWORD DVar2;
  int iVar3;
  size_t sVar4;
  long lVar5;
  undefined4 uVar6;
  char *pcVar7;
  undefined4 uVar8;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  DAT_006e55e0 = 0;
  DAT_0063b360 = 0xffffffff;
  DAT_0063b350 = 0xffffffff;
  _Str1 = _getenv("TZ");
  if (_Str1 == (char *)0x0) {
    DVar2 = GetTimeZoneInformation((LPTIME_ZONE_INFORMATION)&DAT_006e55e8);
    if (DVar2 != 0) {
      DAT_006e55e0 = 1;
      DAT_0063b2b0 = DAT_006e55e8 * 0x3c;
      if (DAT_006e562e != 0) {
        DAT_0063b2b0 = DAT_0063b2b0 + DAT_006e563c * 0x3c;
      }
      if ((DAT_006e5682 == 0) || (DAT_006e5690 == 0)) {
        DAT_0063b2b4 = 0;
        DAT_0063b2b8 = 0;
      }
      else {
        DAT_0063b2b4 = 1;
        DAT_0063b2b8 = (DAT_006e5690 - DAT_006e563c) * 0x3c;
      }
      _wcstombs(PTR_DAT_0063b340,(wchar_t *)&DAT_006e55ec,0x40);
      _wcstombs(PTR_DAT_0063b344,(wchar_t *)&DAT_006e5640,0x40);
      PTR_DAT_0063b344[0x3f] = 0;
      PTR_DAT_0063b340[0x3f] = PTR_DAT_0063b344[0x3f];
    }
  }
  else if ((*_Str1 != '\0') &&
          ((DAT_0063b348 == (char *)0x0 || (iVar3 = _strcmp(_Str1,DAT_0063b348), iVar3 != 0)))) {
    __free_dbg(DAT_0063b348,2);
    uVar8 = 0xec;
    pcVar7 = "tzset.c";
    uVar6 = 2;
    sVar4 = _strlen(_Str1);
    DAT_0063b348 = (char *)__malloc_dbg(sVar4 + 1,uVar6,pcVar7,uVar8);
    if (DAT_0063b348 != (char *)0x0) {
      FUN_005f22d0(DAT_0063b348,_Str1);
      _strncpy(PTR_DAT_0063b340,_Str1,3);
      PTR_DAT_0063b340[3] = 0;
      local_c = _Str1 + 3;
      cVar1 = *local_c;
      if (cVar1 == '-') {
        local_c = _Str1 + 4;
      }
      lVar5 = _atol(local_c);
      DAT_0063b2b0 = lVar5 * 0xe10;
      for (; (*local_c == '+' || (('/' < *local_c && (*local_c < ':')))); local_c = local_c + 1) {
      }
      if (*local_c == ':') {
        local_c = local_c + 1;
        lVar5 = _atol(local_c);
        DAT_0063b2b0 = DAT_0063b2b0 + lVar5 * 0x3c;
        for (; ('/' < *local_c && (*local_c < ':')); local_c = local_c + 1) {
        }
        if (*local_c == ':') {
          local_c = local_c + 1;
          lVar5 = _atol(local_c);
          DAT_0063b2b0 = DAT_0063b2b0 + lVar5;
          for (; ('/' < *local_c && (*local_c < ':')); local_c = local_c + 1) {
          }
        }
      }
      if (cVar1 == '-') {
        DAT_0063b2b0 = -DAT_0063b2b0;
      }
      DAT_0063b2b4 = (int)*local_c;
      if (DAT_0063b2b4 == 0) {
        *PTR_DAT_0063b344 = 0;
      }
      else {
        _strncpy(PTR_DAT_0063b344,local_c,3);
        PTR_DAT_0063b344[3] = 0;
      }
    }
  }
  return;
}
#undef DAT_0063b350
#undef DAT_0063b360
#undef DAT_006e55e0
#undef DAT_006e562e
#undef DAT_006e5682
#undef local_c

/* 006039b0: written by hand in src/crt/time.c */

/* 00603d20 crt */
#define DAT_0063b350 (*(uint *)((u8 *)&g.d_0063b350))
#define DAT_0063b360 (*(uint *)((u8 *)&g.d_0063b360))
#define DAT_0063b36c (*(undefined4 *)((u8 *)&g.d_0063b36c))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
/* Library Function - Single Match
    _cvtdate
   
   Library: Visual Studio 1998 Debug */

void __cdecl
cvtdate(int param_1,int param_2,uint param_3,int param_4,int param_5,int param_6,int param_7,
       int param_8,int param_9,int param_10,int param_11)

{
  int iVar1;
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_2 == 1) {
    if ((param_3 & 3) == 0) {
      local_10 = (&DAT_0063b36c)[param_4];
    }
    else {
      local_10 = *(int *)(&DAT_0063b3a4 + param_4 * 4);
    }
    iVar1 = (int)((param_3 - 0x46) * 0x16d + ((int)(param_3 - 1) >> 2) + -0xd + local_10 + 1) % 7;
    if (iVar1 < param_6) {
      local_c = (param_6 - iVar1) + (param_5 + -1) * 7;
    }
    else {
      local_c = (param_6 - iVar1) + param_5 * 7;
    }
    local_c = local_10 + 1 + local_c;
    if (param_5 == 5) {
      if ((param_3 & 3) == 0) {
        local_14 = *(int *)(&DAT_0063b370 + param_4 * 4);
      }
      else {
        local_14 = *(int *)(&DAT_0063b3a8 + param_4 * 4);
      }
      if (local_14 < local_c) {
        local_c = local_c + -7;
      }
    }
  }
  else {
    if ((param_3 & 3) == 0) {
      local_c = (&DAT_0063b36c)[param_4];
    }
    else {
      local_c = *(int *)(&DAT_0063b3a4 + param_4 * 4);
    }
    local_c = local_c + param_7;
  }
  if (param_1 == 1) {
    DAT_0063b354 = local_c;
    DAT_0063b358 = ((param_8 * 0x3c + param_9) * 0x3c + param_10) * 1000 + param_11;
    DAT_0063b350 = param_3;
  }
  else {
    DAT_0063b364 = local_c;
    DAT_0063b368 = ((param_8 * 0x3c + param_9) * 0x3c + param_10) * 1000 + param_11 +
                   DAT_0063b2b8 * 1000;
    if (DAT_0063b368 < 0) {
      DAT_0063b368 = DAT_0063b368 + 86399999;
    }
    else if (86399999 < DAT_0063b368) {
      DAT_0063b368 = DAT_0063b368 + -86399999;
    }
    DAT_0063b360 = param_3;
  }
  return;
}
#undef DAT_0063b350
#undef DAT_0063b360
#undef DAT_0063b36c
#undef local_14
#undef local_10
#undef local_c

/* 00603f30 crt */
#define DAT_00639f18 (*(DWORD *)((u8 *)&g.d_00639f18))
#define DAT_006e69f0 (*(undefined4 *)((u8 *)&g.d_006e69f0))
#define DAT_006e6b2c (*(uint *)((u8 *)&g.d_006e6b2c))
#define local_1024 (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_1020 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_101c (*(uint *)(frame_ + FRAME_OFF(12)))
#define local_1008 (*(undefined1 (*)[4064])(frame_ + FRAME_OFF(32)))
/* Library Function - Single Match
    __chsize
   
   Library: Visual Studio 1998 Debug */

int __cdecl __chsize(int _FileHandle,long _Size)

{
  code *pcVar1;
  int iVar2;
  long _Offset;
  long lVar3;
  int iVar4;
  HANDLE hFile;
  BOOL BVar5;
  undefined4 uStackY_28;
  undefined1 frame_[FRAME_OFF(4136)] __attribute__((aligned(8)));  /* original stack frame */
  local_1020 = 0;
  if (((uint)_FileHandle < DAT_006e6b2c) &&
     ((*(byte *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) + 4 +
                (_FileHandle & 0x1fU) * 8) & 1) != 0)) {
    if (_Size < 0) {
      uStackY_28 = 0x603fb9;
      iVar2 = __CrtDbgReport(2,"chsize.c",0x7e,0,"size >= 0");
      if (iVar2 == 1) {
        pcVar1 = (code *)swi(3);
        iVar2 = (*pcVar1)();
        return iVar2;
      }
    }
    _Offset = __lseek(_FileHandle,0,1);
    if ((_Offset == -1) || (lVar3 = __lseek(_FileHandle,0,2), lVar3 == -1)) {
      local_1020 = -1;
    }
    else {
      local_101c = _Size - lVar3;
      if ((int)local_101c < 1) {
        if ((int)local_101c < 0) {
          __lseek(_FileHandle,_Size,0);
          hFile = (HANDLE)__get_osfhandle(_FileHandle);
          BVar5 = SetEndOfFile(hFile);
          if (BVar5 == 0) {
            local_1020 = -1;
          }
          else {
            local_1020 = 0;
          }
          if (local_1020 == -1) {
            crt_errno = 0xd;
            DAT_00639f18 = GetLastError();
          }
        }
      }
      else {
        _memset(local_1008,0,0x1000);
        iVar2 = __setmode(_FileHandle,0x8000);
        do {
          if ((int)local_101c < 0x1000) {
            local_1024 = local_101c;
          }
          else {
            local_1024 = 0x1000;
          }
          iVar4 = __write(_FileHandle,local_1008,local_1024);
          if (iVar4 == -1) {
            if (DAT_00639f18 == 5) {
              crt_errno = 0xd;
            }
            local_1020 = -1;
            break;
          }
          local_101c = local_101c - iVar4;
        } while (0 < (int)local_101c);
        __setmode(_FileHandle,iVar2);
      }
      __lseek(_FileHandle,_Offset,0);
    }
  }
  else {
    crt_errno = 9;
    local_1020 = -1;
  }
  return local_1020;
}
#undef DAT_00639f18
#undef DAT_006e69f0
#undef DAT_006e6b2c
#undef local_1024
#undef local_1020
#undef local_101c
#undef local_1008

/* 006041e0 crt */
#define local_c (*(undefined4 *)(frame_ + FRAME_OFF(4)))
/* Library Function - Single Match
    ___addl
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl ___addl(uint param_1,uint param_2,uint *param_3)

{
  uint uVar1;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 0;
  uVar1 = param_2 + param_1;
  if ((uVar1 < param_1) || (uVar1 < param_2)) {
    local_c = 1;
  }
  *param_3 = uVar1;
  return local_c;
}
#undef local_c

/* 00604230 crt */
/* Library Function - Single Match
    ___add_12
   
   Library: Visual Studio 1998 Debug */

void __cdecl ___add_12(undefined4 *param_1,undefined4 *param_2)

{
  int iVar1;
  
  iVar1 = ___addl(*param_1,*param_2,param_1);
  if (iVar1 != 0) {
    iVar1 = ___addl(param_1[1],1,param_1 + 1);
    if (iVar1 != 0) {
      param_1[2] = param_1[2] + 1;
    }
  }
  iVar1 = ___addl(param_1[1],param_2[1],param_1 + 1);
  if (iVar1 != 0) {
    param_1[2] = param_1[2] + 1;
  }
  ___addl(param_1[2],param_2[2],param_1 + 2);
  return;
}

/* 006042e0 crt */
#define local_c (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    ___shl_12
   
   Library: Visual Studio 1998 Debug */

void __cdecl ___shl_12(int *param_1)

{
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = (uint)((int)(*param_1 & -0x80000000) != 0);
  local_c = (uint)((*(byte *)((int)param_1 + 7) & 0x80) != 0);
  *param_1 = *param_1 << 1;
  param_1[1] = param_1[1] * 2 | local_8;
  param_1[2] = param_1[2] * 2 | local_c;
  return;
}
#undef local_c
#undef local_8

/* 00604360 crt */
#define local_c (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    ___shr_12
   
   Library: Visual Studio 1998 Debug */

void __cdecl ___shr_12(uint *param_1)

{
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((param_1[2] & 1) == 0) {
    local_c = 0;
  }
  else {
    local_c = 0x80000000;
  }
  if ((param_1[1] & 1) == 0) {
    local_8 = 0;
  }
  else {
    local_8 = 0x80000000;
  }
  param_1[2] = param_1[2] >> 1;
  param_1[1] = param_1[1] >> 1 | local_c;
  *param_1 = *param_1 >> 1 | local_8;
  return;
}
#undef local_c
#undef local_8

/* 006043e0 crt */
#define local_14 (*(short *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(uint *)(frame_ + FRAME_OFF(8)))
#define local_c (*(uint *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(16)))
/* Library Function - Single Match
    ___mtold12
   
   Library: Visual Studio 1998 Debug */

void __cdecl ___mtold12(char *param_1,int param_2,uint *param_3)

{
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_14 = 0x404e;
  *param_3 = 0;
  param_3[1] = 0;
  param_3[2] = 0;
  for (; param_2 != 0; param_2 = param_2 + -1) {
    local_10 = *param_3;
    local_c = param_3[1];
    local_8 = param_3[2];
    ___shl_12(param_3);
    ___shl_12(param_3);
    ___add_12(param_3,&local_10);
    ___shl_12(param_3);
    local_10 = (uint)*param_1;
    local_c = 0;
    local_8 = 0;
    ___add_12(param_3,&local_10);
    param_1 = param_1 + 1;
  }
  while (param_3[2] == 0) {
    param_3[2] = param_3[1] >> 0x10;
    param_3[1] = param_3[1] << 0x10 | *param_3 >> 0x10;
    *param_3 = *param_3 << 0x10;
    local_14 = local_14 + -0x10;
  }
  while ((*(byte *)((int)param_3 + 9) & 0x80) == 0) {
    ___shl_12(param_3);
    local_14 = local_14 + -1;
  }
  *(short *)((int)param_3 + 10) = local_14;
  return;
}
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 00604520: written by hand in src/crt/float.c */

/* 00605140: written by hand in src/crt/float.c */

/* 006051a0: written by hand in src/crt/float.c */

/* 006056e0 crt */
#define DAT_0063a078 (*(int *)((u8 *)&g.d_0063a078))
#define DAT_0063a088 (*(UINT *)((u8 *)&g.d_0063a088))
#define local_18 (*(BOOL *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(CHAR (*)[4])(frame_ + FRAME_OFF(8)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(16)))
/* Library Function - Single Match
    _wcstombs
   
   Library: Visual Studio 1998 Debug */

size_t __cdecl _wcstombs(char *_Dest,wchar_t *_Source,size_t _MaxCount)

{
  code *pcVar1;
  int iVar2;
  size_t sVar3;
  DWORD DVar4;
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  local_18 = 0;
  if ((_Dest == (char *)0x0) || (_MaxCount != 0)) {
    if ((_Source == (wchar_t *)0x0) &&
       (iVar2 = __CrtDbgReport(2,"wcstombs.c",0x7a,0,"pwcs != NULL"), iVar2 == 1)) {
      pcVar1 = (code *)swi(3);
      sVar3 = (*pcVar1)();
      return sVar3;
    }
    if (_Dest == (char *)0x0) {
      if (DAT_0063a078 == 0) {
        local_8 = _wcslen(_Source);
      }
      else {
        iVar2 = WideCharToMultiByte(DAT_0063a088,0x220,_Source,-1,(LPSTR)0x0,0,(LPCSTR)0x0,&local_18
                                   );
        if ((iVar2 == 0) || (local_18 != 0)) {
          crt_errno = 0x2a;
          local_8 = 0xffffffff;
        }
        else {
          local_8 = iVar2 - 1;
        }
      }
    }
    else if (DAT_0063a078 == 0) {
      for (; local_8 < _MaxCount; local_8 = local_8 + 1) {
        if (0xff < (ushort)*_Source) {
          crt_errno = 0x2a;
          return 0xffffffff;
        }
        _Dest[local_8] = (char)*_Source;
        if (*_Source == L'\0') {
          return local_8;
        }
        _Source = _Source + 1;
      }
    }
    else if (DAT_0063a29c == 1) {
      if (_MaxCount != 0) {
        _MaxCount = wcsncnt_00605a40(_Source,_MaxCount);
      }
      local_8 = WideCharToMultiByte(DAT_0063a088,0x220,_Source,_MaxCount,_Dest,_MaxCount,(LPCSTR)0x0
                                    ,&local_18);
      if ((local_8 == 0) || (local_18 != 0)) {
        crt_errno = 0x2a;
        local_8 = 0xffffffff;
      }
      else if (_Dest[local_8 - 1] == '\0') {
        local_8 = local_8 - 1;
      }
    }
    else {
      local_8 = WideCharToMultiByte(DAT_0063a088,0x220,_Source,-1,_Dest,_MaxCount,(LPCSTR)0x0,
                                    &local_18);
      if ((local_8 == 0) || (local_18 != 0)) {
        if ((local_18 == 0) && (DVar4 = GetLastError(), DVar4 == 0x7a)) {
          while (local_8 < _MaxCount) {
            local_14 = WideCharToMultiByte(DAT_0063a088,0,_Source,1,local_10,DAT_0063a29c,
                                           (LPCSTR)0x0,&local_18);
            if ((local_14 == 0) || (local_18 != 0)) {
              crt_errno = 0x2a;
              return 0xffffffff;
            }
            if (_MaxCount < local_14 + local_8) {
              return local_8;
            }
            for (local_c = 0; local_c < local_14; local_c = local_c + 1) {
              _Dest[local_8] = local_10[local_c];
              if (_Dest[local_8] == '\0') {
                return local_8;
              }
              local_8 = local_8 + 1;
            }
            _Source = _Source + 1;
          }
        }
        else {
          crt_errno = 0x2a;
          local_8 = 0xffffffff;
        }
      }
      else {
        local_8 = local_8 - 1;
      }
    }
  }
  else {
    local_8 = 0;
  }
  return local_8;
}
#undef DAT_0063a078
#undef DAT_0063a088
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 00605a40 crt */
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(short * *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    _wcsncnt
   
   Library: Visual Studio 1998 Debug */

int __cdecl wcsncnt_00605a40(short *param_1,int param_2)

{
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = param_2 + 1;
  for (local_8 = param_1; (local_c = local_c + -1, local_c != 0 && (*local_8 != 0));
      local_8 = local_8 + 1) {
  }
  if ((local_c != 0) && (*local_8 == 0)) {
    param_2 = ((int)local_8 - (int)param_1 >> 1) + 1;
  }
  return param_2;
}
#undef local_c
#undef local_8

/* 00605ab0 crt */
#define DAT_00639f44 (*(int *)((u8 *)&g.d_00639f44))
#define local_c (*(int * *)(frame_ + FRAME_OFF(4)))
/* Library Function - Single Match
    _getenv
   
   Library: Visual Studio 1998 Debug */

char * __cdecl _getenv(char *_VarName)

{
  int iVar1;
  size_t _MaxCount;
  size_t sVar2;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = DAT_00639f3c;
  if ((DAT_00639f3c == (int *)0x0) && (DAT_00639f44 != 0)) {
    iVar1 = ___wtomb_environ();
    if (iVar1 != 0) {
      return (char *)0x0;
    }
    local_c = DAT_00639f3c;
  }
  DAT_00639f3c = local_c;
  if ((local_c != (int *)0x0) && (_VarName != (char *)0x0)) {
    _MaxCount = _strlen(_VarName);
    for (; *local_c != 0; local_c = local_c + 1) {
      sVar2 = _strlen((char *)*local_c);
      if (((_MaxCount < sVar2) && (*(char *)(_MaxCount + *local_c) == '=')) &&
         (iVar1 = __mbsnbicoll((uchar *)*local_c,(uchar *)_VarName,_MaxCount), iVar1 == 0)) {
        return (char *)(_MaxCount + 1 + *local_c);
      }
    }
  }
  return (char *)0x0;
}
#undef DAT_00639f44
#undef local_c

/* 00605ba0 crt */
#define DAT_006e69f0 (*(undefined4 *)((u8 *)&g.d_006e69f0))
#define DAT_006e6b2c (*(uint *)((u8 *)&g.d_006e6b2c))
/* Library Function - Single Match
    __setmode
   
   Library: Visual Studio 1998 Debug */

int __cdecl __setmode(int _FileHandle,int _Mode)

{
  char cVar1;
  int iVar2;
  
  if (((uint)_FileHandle < DAT_006e6b2c) &&
     ((*(byte *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) + 4 +
                (_FileHandle & 0x1fU) * 8) & 1) != 0)) {
    cVar1 = *(char *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) + 4 +
                     (_FileHandle & 0x1fU) * 8);
    if (_Mode == 0x8000) {
      *(byte *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) + 4 +
               (_FileHandle & 0x1fU) * 8) =
           *(byte *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) + 4 +
                    (_FileHandle & 0x1fU) * 8) & 0x7f;
    }
    else {
      if (_Mode != 0x4000) {
        crt_errno = 0x16;
        return -1;
      }
      *(byte *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) + 4 +
               (_FileHandle & 0x1fU) * 8) =
           *(byte *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) + 4 +
                    (_FileHandle & 0x1fU) * 8) | 0x80;
    }
    if (((int)cVar1 & 0x80U) == 0) {
      iVar2 = 0x8000;
    }
    else {
      iVar2 = 0x4000;
    }
  }
  else {
    crt_errno = 9;
    iVar2 = -1;
  }
  return iVar2;
}
#undef DAT_006e69f0
#undef DAT_006e6b2c

/* 00605ce0 crt */
#define local_3c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_38 (*(ushort *)(frame_ + FRAME_OFF(8)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(28)))
#define local_1c (*(byte (*)[2])(frame_ + FRAME_OFF(36)))
#define uStack_1a (*(undefined2 *)(frame_ + FRAME_OFF(38)))
#define local_18 (*(short (*)[3])(frame_ + FRAME_OFF(40)))
#define uStack_12 (*(undefined1 *)(frame_ + FRAME_OFF(46)))
#define bStack_11 (*(byte *)(frame_ + FRAME_OFF(47)))
#define local_10 (*(undefined2 *)(frame_ + FRAME_OFF(48)))
#define local_c (*(int *)(frame_ + FRAME_OFF(52)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(56)))
/* Library Function - Single Match
    ___ld12mul
   
   Library: Visual Studio 1998 Debug */

void __cdecl ___ld12mul(int *param_1,int *param_2)

{
  short sVar1;
  int iVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  int iVar6;
  undefined1 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_10 = 0;
  local_1c[0] = 0;
  local_1c[1] = 0;
  uStack_1a = 0;
  local_18[0] = 0;
  local_18[1] = 0;
  local_18[2] = 0;
  uStack_12 = 0;
  bStack_11 = 0;
  uVar3 = *(ushort *)((int)param_1 + 10);
  uVar4 = *(ushort *)((int)param_2 + 10);
  uVar5 = uVar4 ^ uVar3;
  local_38 = (uVar4 & 0x7fff) + (uVar3 & 0x7fff);
  if ((((uVar3 & 0x7fff) < 0x7fff) && ((uVar4 & 0x7fff) < 0x7fff)) && (local_38 < 0xbffe)) {
    if (local_38 < 0x3fc0) {
      param_1[2] = 0;
      param_1[1] = 0;
      *param_1 = 0;
    }
    else if ((((uVar3 & 0x7fff) == 0) && (local_38 = local_38 + 1, (param_1[2] & 0x7fffffffU) == 0))
            && ((param_1[1] == 0 && (*param_1 == 0)))) {
      *(undefined2 *)((int)param_1 + 10) = 0;
    }
    else if ((((uVar4 & 0x7fff) == 0) && (local_38 = local_38 + 1, (param_2[2] & 0x7fffffffU) == 0))
            && ((param_2[1] == 0 && (*param_2 == 0)))) {
      param_1[2] = 0;
      param_1[1] = 0;
      *param_1 = 0;
    }
    else {
      local_30 = 0;
      for (local_24 = 0; local_24 < 5; local_24 = local_24 + 1) {
        local_2c = local_24 * 2;
        local_c = 8;
        for (local_3c = 5 - local_24; 0 < local_3c; local_3c = local_3c + -1) {
          iVar6 = ___addl(*(undefined4 *)(local_1c + local_30),
                          (uint)*(ushort *)((int)param_2 + local_c) *
                          (uint)*(ushort *)(local_2c + (int)param_1),local_1c + local_30);
          if (iVar6 != 0) {
            *(short *)((int)local_18 + local_30) = *(short *)((int)local_18 + local_30) + 1;
          }
          local_2c = local_2c + 2;
          local_c = local_c + -2;
        }
        local_30 = local_30 + 2;
      }
      local_38 = local_38 + 0xc002;
      while ((0 < (short)local_38 && ((bStack_11 & 0x80) == 0))) {
        ___shl_12(local_1c);
        local_38 = local_38 - 1;
      }
      if ((short)local_38 < 1) {
        for (local_38 = local_38 - 1; (short)local_38 < 0; local_38 = local_38 + 1) {
          if ((local_1c[0] & 1) != 0) {
            local_8 = local_8 + 1;
          }
          ___shr_12(local_1c);
        }
        if (local_8 != 0) {
          local_1c[0] = local_1c[0] | 1;
        }
      }
      iVar2 = CONCAT22(local_18[0],uStack_1a);
      iVar6 = CONCAT22(local_18[2],local_18[1]);
      sVar1 = CONCAT11(bStack_11,uStack_12);
      if (0x8000 < CONCAT11(local_1c[1],local_1c[0])) {
        if (CONCAT22(local_18[0],uStack_1a) == -1) {
          iVar2 = 0;
          if (CONCAT22(local_18[2],local_18[1]) == -1) {
            iVar6 = 0;
            if (CONCAT11(bStack_11,uStack_12) == -1) {
              sVar1 = -0x8000;
              local_38 = local_38 + 1;
            }
            else {
              sVar1 = CONCAT11(bStack_11,uStack_12) + 1;
            }
          }
          else {
            iVar6 = CONCAT22(local_18[2],local_18[1]) + 1;
          }
        }
        else {
          iVar2 = CONCAT22(local_18[0],uStack_1a) + 1;
          iVar6 = CONCAT22(local_18[2],local_18[1]);
        }
      }
      local_18[0] = (short)((uint)iVar2 >> 0x10);
      uStack_1a = (undefined2)iVar2;
      bStack_11 = (byte)((ushort)sVar1 >> 8);
      uStack_12 = (undefined1)sVar1;
      local_18[2] = (short)((uint)iVar6 >> 0x10);
      local_18[1] = (short)iVar6;
      if (local_38 < 0x7fff) {
        *(undefined2 *)param_1 = uStack_1a;
        *(uint *)((int)param_1 + 2) = CONCAT22(local_18[1],local_18[0]);
        *(uint *)((int)param_1 + 6) = CONCAT13(bStack_11,CONCAT12(uStack_12,local_18[2]));
        *(ushort *)((int)param_1 + 10) = uVar5 & 0x8000 | local_38;
      }
      else {
        if ((uVar5 & 0x8000) == 0) {
          param_1[2] = 0x7fff8000;
        }
        else {
          param_1[2] = -0x8000;
        }
        param_1[1] = 0;
        *param_1 = 0;
      }
    }
  }
  else {
    if ((uVar5 & 0x8000) == 0) {
      param_1[2] = 0x7fff8000;
    }
    else {
      param_1[2] = -0x8000;
    }
    param_1[1] = 0;
    *param_1 = 0;
  }
  return;
}
#undef local_3c
#undef local_38
#undef local_30
#undef local_2c
#undef local_24
#undef local_1c
#undef uStack_1a
#undef local_18
#undef uStack_12
#undef bStack_11
#undef local_10
#undef local_c
#undef local_8

/* 00606110 crt */
#define local_18 (*(ushort *)(frame_ + FRAME_OFF(0)))
#define uStack_16 (*(undefined4 *)(frame_ + FRAME_OFF(2)))
#define uStack_12 (*(undefined2 *)(frame_ + FRAME_OFF(6)))
#define local_10 (*(undefined4 *)(frame_ + FRAME_OFF(8)))
#define local_c (*(ushort * *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(undefined * *)(frame_ + FRAME_OFF(16)))
/* Library Function - Single Match
    ___multtenpow12
   
   Library: Visual Studio 1998 Debug */

void __cdecl ___multtenpow12(undefined2 *param_1,uint param_2,int param_3)

{
  uint uVar1;
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = &DAT_0063b380;
  if (param_2 != 0) {
    if ((int)param_2 < 0) {
      param_2 = -param_2;
      local_8 = &DAT_0063b4e0;
    }
    uStack_16 = CONCAT22((*(undefined2 *)((char *)&uStack_16 + 2)),(undefined2)uStack_16);
    if (param_3 == 0) {
      *param_1 = 0;
      uStack_16 = CONCAT22((*(undefined2 *)((char *)&uStack_16 + 2)),(undefined2)uStack_16);
    }
    while (param_2 != 0) {
      local_8 = local_8 + 0x54;
      uVar1 = param_2 & 7;
      param_2 = (int)param_2 >> 3;
      if (uVar1 != 0) {
        local_c = (ushort *)(local_8 + uVar1 * 0xc);
        if (0x7fff < *local_c) {
          local_18 = (ushort)*(undefined4 *)local_c;
          (*(undefined2 *)((char *)&uStack_16 + 0)) = (undefined2)((uint)*(undefined4 *)local_c >> 0x10);
          (*(undefined2 *)((char *)&uStack_16 + 2)) = (undefined2)*(undefined4 *)(local_c + 2);
          uStack_12 = (undefined2)((uint)*(undefined4 *)(local_c + 2) >> 0x10);
          local_10 = *(undefined4 *)(local_c + 4);
          uStack_16 = CONCAT22((*(undefined2 *)((char *)&uStack_16 + 2)),(undefined2)uStack_16) + -1;
          local_c = &local_18;
        }
        ___ld12mul(param_1,local_c);
      }
    }
  }
  return;
}
#undef local_18
#undef uStack_16
#undef uStack_12
#undef local_10
#undef local_c
#undef local_8

/* 006061f0: written by hand in src/crt/locale.c */

/* 00606260 crt */
#define DAT_00639f44 (*(int * *)((u8 *)&g.d_00639f44))
#define local_8 (*(int * *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    ___wtomb_environ
   
   Library: Visual Studio 1998 Debug */

int __cdecl ___wtomb_environ(void)

{
  int iVar1;
  char **_POption;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = DAT_00639f44;
  while( true ) {
    if (*local_8 == 0) {
      return 0;
    }
    iVar1 = WideCharToMultiByte(1,0,(LPCWSTR)*local_8,-1,(LPSTR)0x0,0,(LPCSTR)0x0,(LPBOOL)0x0);
    if (iVar1 == 0) {
      return -1;
    }
    _POption = (char **)__malloc_dbg(iVar1,2,"wtombenv.c",0x3d);
    if (_POption == (char **)0x0) {
      return -1;
    }
    iVar1 = WideCharToMultiByte(1,0,(LPCWSTR)*local_8,-1,(LPSTR)_POption,iVar1,(LPCSTR)0x0,
                                (LPBOOL)0x0);
    if (iVar1 == 0) break;
    ___crtsetenv(_POption,0);
    local_8 = local_8 + 1;
  }
  return -1;
}
#undef DAT_00639f44
#undef local_8

/* 00606330: written by hand in src/crt/locale.c */

/* 00606620 crt */
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(short * *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    _wcsncnt
   
   Library: Visual Studio 1998 Debug */

int __cdecl wcsncnt_00606620(short *param_1,int param_2)

{
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = param_2;
  for (local_8 = param_1; (local_c != 0 && (*local_8 != 0)); local_8 = local_8 + 1) {
    local_c = local_c + -1;
  }
  if (*local_8 == 0) {
    param_2 = (int)local_8 - (int)param_1 >> 1;
  }
  return param_2;
}
#undef local_c
#undef local_8

/* 00606690: written by hand in src/crt/locale.c */

/* 00606af0: written by hand in src/crt */

/* 00606b60: written by hand in src/crt/startup.c */

/* 00606ed0 crt */
#define local_8 (*(int * *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    _findenv
   
   Library: Visual Studio 1998 Debug */

int __cdecl findenv(uchar *param_1,size_t param_2)

{
  int iVar1;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = DAT_00639f3c;
  while( true ) {
    if (*local_8 == 0) {
      return -((int)local_8 - (int)DAT_00639f3c >> 2);
    }
    iVar1 = __mbsnbicoll(param_1,(uchar *)*local_8,param_2);
    if ((iVar1 == 0) &&
       ((*(char *)(param_2 + *local_8) == '=' || (*(char *)(param_2 + *local_8) == '\0')))) break;
    local_8 = local_8 + 1;
  }
  return (int)local_8 - (int)DAT_00639f3c >> 2;
}
#undef local_8

/* 00606f70 crt */
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(int * *)(frame_ + FRAME_OFF(8)))
#define local_c (*(int * *)(frame_ + FRAME_OFF(12)))
/* Library Function - Single Match
    _copy_environ
   
   Library: Visual Studio 1998 Debug */

int * __cdecl copy_environ(int *param_1)

{
  int *piVar1;
  size_t sVar2;
  int iVar3;
  undefined4 uVar4;
  char *pcVar5;
  undefined4 uVar6;
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_14 = 0;
  local_10 = param_1;
  if (param_1 == (int *)0x0) {
    piVar1 = (int *)0x0;
  }
  else {
    while( true ) {
      if (*local_10 == 0) break;
      local_14 = local_14 + 1;
      local_10 = local_10 + 1;
    }
    piVar1 = (int *)__malloc_dbg(local_14 * 4 + 4,2,"setenv.c",0x146);
    if (piVar1 == (int *)0x0) {
      __amsg_exit(9);
    }
    local_c = piVar1;
    for (local_10 = param_1; *local_10 != 0; local_10 = local_10 + 1) {
      uVar6 = 0x14f;
      pcVar5 = "setenv.c";
      uVar4 = 2;
      sVar2 = _strlen((char *)*local_10);
      iVar3 = __malloc_dbg(sVar2 + 1,uVar4,pcVar5,uVar6);
      *local_c = iVar3;
      if (*local_c != 0) {
        FUN_005f22d0(*local_c,*local_10);
      }
      local_c = local_c + 1;
    }
    *local_c = 0;
  }
  return piVar1;
}
#undef local_14
#undef local_10
#undef local_c

/* 00607070 crt */
#define DAT_0063b0a4 (*(int *)((u8 *)&g.d_0063b0a4))
/* Library Function - Single Match
    __mbschr
   
   Library: Visual Studio 1998 Debug */

uchar * __cdecl __mbschr(uchar *_Str,uint _Ch)

{
  uchar *puVar1;
  byte bVar2;
  ushort uVar3;
  
  if (DAT_0063b0a4 == 0) {
    _Str = (uchar *)_strchr((char *)_Str,_Ch);
  }
  else {
    while( true ) {
      bVar2 = *_Str;
      uVar3 = (ushort)bVar2;
      if (uVar3 == 0) break;
      if (((&DAT_0063afa1)[bVar2] & 4) == 0) {
        puVar1 = _Str;
        if (uVar3 == _Ch) break;
      }
      else {
        puVar1 = _Str + 1;
        if (*puVar1 == '\0') {
          return (uchar *)0x0;
        }
        if (CONCAT11(bVar2,*puVar1) == _Ch) {
          return _Str;
        }
      }
      _Str = puVar1;
      _Str = _Str + 1;
    }
    if (uVar3 != _Ch) {
      _Str = (uchar *)0x0;
    }
  }
  return _Str;
}
#undef DAT_0063b0a4

/* 006075e0 crt */
#define DAT_00639f18 (*(undefined4 *)((u8 *)&g.d_00639f18))
#define DAT_006e69f0 (*(undefined4 *)((u8 *)&g.d_006e69f0))
#define DAT_006e6b2c (*(uint *)((u8 *)&g.d_006e6b2c))
#define local_8 (*(long *)(frame_ + FRAME_OFF(0)))
/* Library Function - Single Match
    __filelength
   
   Library: Visual Studio 1998 Debug */

long __cdecl __filelength(int _FileHandle)

{
  long _Offset;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((uint)_FileHandle < DAT_006e6b2c) &&
     ((*(byte *)(*(int *)((int)&DAT_006e69f0 + ((int)(_FileHandle & 0xffffffe0U) >> 3)) + 4 +
                (_FileHandle & 0x1fU) * 8) & 1) != 0)) {
    _Offset = __lseek(_FileHandle,0,1);
    if (_Offset == -1) {
      local_8 = -1;
    }
    else {
      local_8 = __lseek(_FileHandle,0,2);
      if (_Offset != local_8) {
        __lseek(_FileHandle,_Offset,0);
      }
    }
  }
  else {
    crt_errno = 9;
    DAT_00639f18 = 0;
    local_8 = -1;
  }
  return local_8;
}
#undef DAT_00639f18
#undef DAT_006e69f0
#undef DAT_006e6b2c
#undef local_8

/* 006076a0 crt */
undefined4 __cdecl FUN_006076a0(int param_1)

{
  return *(undefined4 *)(param_1 + 0x10);
}

/* 006076c0: written by hand in src/crt/locale.c */

/* 006077f0: written by hand in src/crt/locale.c */

/* 00607920 crt */
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
/* Library Function - Multiple Matches With Different Base Names
    __mkdir
    __wmkdir
   
   Library: Visual Studio 1998 Debug */

undefined4 __cdecl FUN_00607920(LPCSTR param_1)

{
  BOOL BVar1;
  undefined4 uVar2;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  BVar1 = CreateDirectoryA(param_1,(LPSECURITY_ATTRIBUTES)0x0);
  if (BVar1 == 0) {
    local_8 = GetLastError();
  }
  else {
    local_8 = 0;
  }
  if (local_8 == 0) {
    uVar2 = 0;
  }
  else {
    __dosmaperr(local_8);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}
#undef local_8
