/*
 * Functions whose decompilation got a callee's return value wrong
 * (values left in ECX/EAX by callees declared with the wrong return type).
 */
#include "game.h"

/* 0x00452315 */
#define DAT_0062cd20 (*(FILE * *)((u8 *)&g.d_0062cd20))
#define local_1110 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_110c (*(char (*)[4096])(frame_ + FRAME_OFF(4)))
#define local_10c (*(char * *)(frame_ + FRAME_OFF(4100)))
#define local_108 (*(char (*)[2])(frame_ + FRAME_OFF(4104)))
#define local_106 (*(undefined1 *)(frame_ + FRAME_OFF(4106)))
#define local_104 (*(undefined1 (*)[228])(frame_ + FRAME_OFF(4108)))
/* _strrchr is declared __thiscall without parameters in protos.h; it is the
   plain cdecl CRT strrchr. */
#define STRRCHR ((char *(__cdecl *)(const char *, int))_strrchr)

/*
 * 0x00452315: show the description of a Civilopedia topic.  A __thiscall
 * method (ECX = the Civilopedia window); the decompiler took ECX for a value
 * left over from the __chkstk call.
 */
void __thiscall FUN_00452315(void *this, int param_1)
{
  int self = (iptr)this;
  bool bVar1;
  int iVar2;
  char *pcVar3;
  size_t sVar4;
  size_t sVar5;
  undefined1 frame_[FRAME_OFF(4368)] __attribute__((aligned(8)));  /* original stack frame */
  
  thunk_FUN_004aef20(local_104);
  thunk_FUN_004f4793((void *)self);
  thunk_FUN_00453af0();
  switch(*(undefined4 *)(self + 0x118)) {
  case 1:
    param_1 = *(int *)(self + 0x65c + param_1 * 4);
    FUN_005f22d0(local_104,s__ADVANCE_INDEX_00626858);
    break;
  case 2:
    param_1 = *(int *)(self + 0x980 + param_1 * 4);
    FUN_005f22d0(local_104,s__IMPROVEMENT_INDEX_00626868);
    break;
  case 3:
    param_1 = *(int *)(self + 0xabc + param_1 * 4);
    FUN_005f22d0(local_104,s__WONDER_INDEX_0062687c);
    break;
  case 4:
    param_1 = *(int *)(self + 0xba0 + param_1 * 4);
    FUN_005f22d0(local_104,s__UNIT_INDEX_0062688c);
    break;
  case 5:
    param_1 = *(int *)(self + 0xdd0 + param_1 * 4);
    FUN_005f22d0(local_104,s__TERRAIN_INDEX_00626898);
    break;
  case 6:
    param_1 = *(int *)(self + 0xd94 + param_1 * 4);
    FUN_005f22d0(local_104,s__GOVERNMENT_INDEX_006268a8);
    break;
  case 7:
    param_1 = *(int *)(self + 0xedc + param_1 * 4);
    FUN_005f22d0(local_104,s_CONCEPT_DESCRIPTIONS_006268bc);
    break;
  default:
    FUN_005f22d0(local_104,s_Unknown_Topic_Group_006268d4);
  }
  iVar2 = thunk_FUN_004a2379(s_Describe_006268e8,local_104);
  if (iVar2 == 0) {
    local_1110 = param_1 + 1;
    local_106 = 0;
    bVar1 = true;
    do {
      while( true ) {
        if (local_1110 == 0) goto LAB_0045259e;
        thunk_FUN_004a23fc(1);
        _strncpy(local_108,&DAT_00679640,2);
        iVar2 = _strcmp(local_108,&DAT_006268f4);
        if (iVar2 != 0) break;
        local_1110 = local_1110 + -1;
      }
    } while (local_108[0] != '@');
    bVar1 = false;
LAB_0045259e:
    if (bVar1) {
      thunk_FUN_004aef20(local_110c);
      do {
        do {
          if (!bVar1) {
            thunk_FUN_004a2020();
            goto LAB_00452724;
          }
          if (CRT_FEOF(DAT_0062cd20) != 0) goto LAB_00452724;
          pcVar3 = _fgets(&DAT_00679640,0x800,DAT_0062cd20);
          if ((pcVar3 == (char *)0x0) || (DAT_00679640 == '@')) goto LAB_00452724;
        } while (DAT_00679640 == ';');
        local_10c = STRRCHR(&DAT_00679640,10);
        if (local_10c != (char *)0x0) {
          *local_10c = '\0';
          FUN_005f22e0(&DAT_00679640,&DAT_006268f8);
        }
        sVar4 = _strlen(local_110c);
        sVar5 = _strlen(&DAT_00679640);
        if (0xffe < sVar4 + sVar5) {
          sVar4 = _strlen(local_110c);
          *(undefined1 *)(ADDR(0x67a63f, ((u8 *)&g.d_0067a638 + 7)) - sVar4) = 0;
        }
        FUN_005f22e0(local_110c,&DAT_00679640);
        sVar4 = _strlen(local_110c);
      } while (sVar4 != 0xfff);
    }
    else {
      thunk_FUN_0040bc10(0xe);
      FUN_005f22d0(local_110c,&DAT_00679640);
    }
LAB_00452724:
    thunk_FUN_00418a30((void *)(self + 0x1a98),local_110c);
    thunk_FUN_0040f380(self + 0x1a98);
  }
  return;
}
#undef DAT_0062cd20
#undef local_1110
#undef local_110c
#undef local_10c
#undef local_108
#undef local_106
#undef local_104

/* 0x00475666 */
#define DAT_00627670 (*(undefined4 *)((u8 *)&g.d_00627670))
#define DAT_00628048 (*(byte *)((u8 *)&g.d_00628048))
#define DAT_0062ee08 (*(undefined4 *)((u8 *)&g.d_0062ee08))
#define DAT_006365e0 (*(void * *)((u8 *)&map_coarse))
#define DAT_006365e4 (*(void * *)((u8 *)&map_coarse + 4))
#define DAT_0064b1b0 (*(undefined2 *)((u8 *)&g.d_0064b1b0))
#define DAT_0064b1b4 (*(undefined2 *)((u8 *)&g.d_0064b1b4))
#define DAT_0064b99c (*(int *)((u8 *)&g.d_0064b99c))
#define DAT_0064bc60 (*(undefined2 *)((u8 *)&g.d_0064bc60))
#define DAT_00654c74 (*(undefined2 *)((u8 *)&g.d_00654c74))
#define DAT_00654c76 (*(undefined2 *)((u8 *)&g.d_00654c76))
#define DAT_00654c78 (*(undefined2 *)((u8 *)&g.d_00654c78))
#define DAT_00654c7a (*(undefined2 *)((u8 *)&g.d_00654c7a))
#define DAT_00654fa4 (*(byte *)((u8 *)&g.d_00654fa4))
#define DAT_00654fac (*(undefined2 *)((u8 *)&g.d_00654fac))
#define DAT_00654fae (*(undefined2 *)((u8 *)&g.d_00654fae))
#define DAT_00655128 (*(undefined2 *)((u8 *)&g.d_00655128))
#define DAT_00655280 (*(undefined4 *)((u8 *)&g.d_00655280))
#define DAT_00666548 (*(undefined2 *)((u8 *)&g.d_00666548))
#define DAT_0066654a (*(undefined2 *)((u8 *)&g.d_0066654a))
#define DAT_0066654c (*(undefined2 *)((u8 *)&g.d_0066654c))
#define DAT_0066654e (*(undefined2 *)((u8 *)&g.d_0066654e))
#define DAT_0066c600 (*(undefined2 *)((u8 *)&g.d_0066c600))
#define DAT_0066ca88 (*(undefined2 *)((u8 *)&g.d_0066ca88))
#define DAT_0066ca8a (*(undefined2 *)((u8 *)&g.d_0066ca8a))
#define DAT_0066ca8c (*(undefined2 *)((u8 *)&g.d_0066ca8c))
#define DAT_006ad6ae (*(undefined *)((u8 *)&g.d_006ad6ae))
#define DAT_006ad7b2 (*(undefined *)((u8 *)&g.d_006ad7b2))
#define DAT_006d1da0 (*(int *)((u8 *)&g.d_006d1da0))
#define local_74c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_748 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_744 (*(int *)(frame_ + FRAME_OFF(12)))
#define local_73c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_738 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_734 (*(int *)(frame_ + FRAME_OFF(28)))
#define local_730 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_728 (*(undefined1 (*)[12])(frame_ + FRAME_OFF(40)))
#define local_71c (*(short (*)[4])(frame_ + FRAME_OFF(52)))
#define asStack_714 (*(short (*)[494])(frame_ + FRAME_OFF(60)))
#define local_338 (*(int *)(frame_ + FRAME_OFF(1048)))
#define local_334 (*(uint *)(frame_ + FRAME_OFF(1052)))
#define local_330 (*(int *)(frame_ + FRAME_OFF(1056)))
#define local_32c (*(uint *)(frame_ + FRAME_OFF(1060)))
#define local_328 (*(int *)(frame_ + FRAME_OFF(1064)))
#define local_324 (*(char (*)[260])(frame_ + FRAME_OFF(1068)))
#define local_220 (*(int *)(frame_ + FRAME_OFF(1328)))
#define local_21c (*(int *)(frame_ + FRAME_OFF(1332)))
#define local_218 (*(char (*)[260])(frame_ + FRAME_OFF(1336)))
#define local_114 (*(char (*)[4])(frame_ + FRAME_OFF(1596)))
#define local_110 (*(int *)(frame_ + FRAME_OFF(1600)))
#define local_10c (*(char * *)(frame_ + FRAME_OFF(1604)))
#define local_108 (*(undefined1 (*)[260])(frame_ + FRAME_OFF(1608)))
int __cdecl FUN_00475666(char *param_1)

{
  char cVar1;
  char *pcVar2;
  FILE *_File;
  int iVar3;
  size_t sVar4;
  size_t sVar5;
  void *pvVar6;
  undefined4 uVar7;
  int iVar8;
  undefined1 frame_[FRAME_OFF(1872)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_338 = 1;
  local_110 = 0;
  local_334 = (uint)game.multiplayer;
  thunk_FUN_00473d5e(0);
  FUN_005f22d0(local_218,param_1);
  pcVar2 = _strchr(local_218,0x2e);
  if (pcVar2 == (char *)0x0) {
    FUN_005f22e0(local_218,&DAT_0066c4e8);
  }
  _File = _fopen(local_218,&DAT_0062bae4);
  if ((_File == (FILE *)0x0) || (iVar3 = thunk_FUN_00497da0(local_324,_File), iVar3 == 0))
  goto LAB_00477352;
  iVar3 = _strcmp(PTR_s_CIVILIZE_0062b990,local_324);
  if (iVar3 != 0) {
    local_338 = 1;
    goto LAB_00477352;
  }
  sVar4 = _fread(&local_32c,2,1,_File);
  if (sVar4 == 0) goto LAB_00477352;
  if (0x2c < (local_32c & 0xffff)) {
    local_338 = 4;
    goto LAB_00477352;
  }
  if (((((local_32c & 0xffff) < 0x26) || ((local_32c & 0xffff) == 0x29)) ||
      ((local_32c & 0xffff) == 0x2a)) || ((local_32c & 0xffff) == 0x2b)) {
    local_338 = 2;
    goto LAB_00477352;
  }
  thunk_FUN_00484d52();
  FUN_005f22d0(&DAT_0064bb08,param_1);
  local_10c = STRRCHR(&DAT_0064bb08,0x5c);
  *local_10c = '\0';
  __chdir(&DAT_0064bb08);
  FUN_005f22d0(local_108,s_GAME__0062bae8);
  FUN_005f22e0(local_108,&DAT_0062cd24);
  iVar3 = thunk_FUN_00415133(local_108);
  if (iVar3 == 0) {
    FUN_005f22d0(&DAT_006558e8,&DAT_0062baf8);
  }
  else {
    FUN_005f22d0(&DAT_006558e8,&DAT_0064bb08);
    FUN_005f22e0(&DAT_006558e8,s__GAME_0062baf0);
  }
  local_10c = STRRCHR(param_1,0x5c);
  local_10c = local_10c + 1;
  FUN_005f22d0(&DAT_006ad6ae,local_10c);
  sVar4 = _strlen(&DAT_00655020);
  iVar3 = __strnicmp(param_1,&DAT_00655020,sVar4);
  if (iVar3 == 0) {
    sVar4 = _strlen(&DAT_00655020);
    local_10c = param_1 + sVar4;
    sVar4 = _strlen(local_10c);
    sVar5 = _strlen(&DAT_006ad6ae);
    if (sVar4 != sVar5) {
      _memset(&DAT_006ad7b2,0,0x104);
      sVar4 = _strlen(local_10c);
      sVar5 = _strlen(&DAT_006ad6ae);
      _strncpy(&DAT_006ad7b2,local_10c,(sVar4 - sVar5) - 1);
    }
  }
  __chdir(&DAT_00655020);
  thunk_FUN_00484d52();
  thunk_FUN_0041e864(1);
  local_338 = 3;
  thunk_FUN_00484d52();
  iVar3 = thunk_FUN_00473660(local_32c & 0xffff,_File);
  if (iVar3 == 0) goto LAB_00477352;
  if (game.multiplayer != 0) {
    game.game_options = game.game_options & 0xffff7fff;
  }
  if (((game.game_flags & 0x40) == 0) && ((game.game_flags & 0x80) == 0)) {
    local_220 = 0;
  }
  else {
    local_220 = 1;
  }
  if (local_220 != 0) {
    game.game_flags = game.game_flags | 0x80;
  }
  if ((game.game_flags & 0x40) != 0) {
    game.game_options = game.game_options & 0xffff7fff;
    game.reveal_map = 0;
    game.game_flags = game.game_flags & 0xffef;
  }
  game.game_flags = game.game_flags & 0xffbf;
  iVar3 = map_read(_File,0);
  if (((iVar3 != 0) ||
      (sVar4 = _fread(DAT_006365e0,(int)map.quarter_w * (int)map.quarter_h,1,_File), sVar4 == 0)) ||
     (sVar4 = _fread(DAT_006365e4,(int)map.quarter_w * (int)map.quarter_h,1,_File), sVar4 == 0))
  goto LAB_00477352;
  thunk_FUN_00484d52();
  sVar4 = _fread(&DAT_00666130,0x400,1,_File);
  if ((sVar4 == 0) || (iVar3 = thunk_FUN_004732a6(local_32c & 0xffff,_File), iVar3 == 0))
  goto LAB_00477352;
  for (local_21c = 0; local_21c < 0x15; local_21c = local_21c + 1) {
    sVar4 = _fread(&leaders[local_21c].times_used,1,1,_File);
    if (((sVar4 == 0) || (sVar4 = _fread(&leaders[local_21c].city_name_index,1,1,_File), sVar4 == 0))
       || (sVar4 = _fread(&leaders[local_21c].female,1,1,_File), sVar4 == 0))
    goto LAB_00477352;
  }
  sVar4 = _fread(&DAT_0064b1b4,2,1,_File);
  if ((sVar4 == 0) ||
     (sVar4 = _fread(&DAT_0064b1b0,2,1,_File), cVar1 = game.player_civ, game.player_civ = cVar1,
     sVar4 == 0)) goto LAB_00477352;
  if (game.multiplayer == 0) {
    sVar4 = _fread(local_728,0x30,1,_File);
    if (sVar4 == 0) goto LAB_00477352;
  }
  else {
    for (local_21c = 0; game.player_civ = cVar1, local_21c < 8; local_21c = local_21c + 1) {
      if ((1 << ((byte)local_21c & 0x1f) & (uint)game.human_players) != 0) {
        game.player_civ = (byte)local_21c;
        sVar4 = _fread(local_728 + civs[(char)(byte)local_21c].tribe * 0x30,
                       0x30,1,_File);
        game.player_civ = cVar1;
        if (sVar4 == 0) goto LAB_00477352;
      }
    }
  }
  sVar4 = _fread(&DAT_00655c38,0x4b0,1,_File);
  if ((sVar4 == 0) || (sVar4 = _fread(&DAT_0066c600,0x6a,1,_File), sVar4 == 0)) goto LAB_00477352;
  thunk_FUN_00473064();
  thunk_FUN_00484d52();
  for (local_21c = 0; local_21c < 8; local_21c = local_21c + 1) {
    sVar4 = _fread(&DAT_0066ca84 + local_21c * 0x3f0,2,1,_File);
    if ((((sVar4 == 0) || (sVar4 = _fread(&DAT_0066ca86 + local_21c * 0x3f0,2,1,_File), sVar4 == 0))
        || (sVar4 = _fread(&DAT_0066ca88 + local_21c * 0x1f8,2,1,_File), sVar4 == 0)) ||
       ((sVar4 = _fread(&DAT_0066ca8a + local_21c * 0x1f8,2,1,_File), sVar4 == 0 ||
        (sVar4 = _fread(&DAT_0066ca8c + local_21c * 0x1f8,2,1,_File), sVar4 == 0))))
    goto LAB_00477352;
  }
  if ((local_220 == 0) && ((game.game_flags & 0x80) == 0)) {
    thunk_FUN_00484cc0();
  }
  else {
    sVar4 = _fread(&DAT_0064bc60,100,1,_File);
    if (sVar4 == 0) goto LAB_00477352;
  }
  if (local_110 == 0) {
    sVar4 = _fread(&DAT_00655128,0x152,1,_File);
    if (sVar4 == 0) goto LAB_00477352;
  }
  else {
    thunk_FUN_004a76f5();
  }
  DAT_006d1da0 = (int)game.field_1c;
  if (((local_32c & 0xffff) < 0x29) || (game.multiplayer == 0)) {
    thunk_FUN_00498784();
    DAT_00654c74 = 1;
    DAT_00654c76 = DAT_00666548;
    DAT_00654c78 = DAT_0066654a;
    DAT_00654c7a = DAT_0066654c;
    DAT_00654fac = 0;
    DAT_00654fae = 0;
    DAT_0066654e = 0;
    DAT_00654fa4 = (byte)DAT_006d1da0;
    DAT_00628048 = (byte)DAT_006d1da0;
  }
  else {
    _memset(&DAT_00654b40,0,0x494);
    sVar4 = _fread(&DAT_00654b40,0x494,1,_File);
    if (sVar4 == 0) goto LAB_00477352;
    if (DAT_00654fa4 == 0) {
      DAT_00654fa4 = game.turn_civ;
    }
    if (DAT_00654fa4 == 0) {
      for (local_328 = 1; local_328 < 8; local_328 = local_328 + 1) {
        if ((1 << ((byte)local_328 & 0x1f) & (uint)game.civs_alive) != 0) {
          DAT_00654fa4 = (byte)local_328;
          break;
        }
      }
    }
    DAT_00628048 = DAT_00654fa4;
    thunk_FUN_0049882b();
  }
  DAT_00627670 = 0;
  sVar4 = _fread(local_114,4,1,_File);
  if ((sVar4 != 0) && (iVar3 = _strncmp(local_114,&DAT_0062bb00,4), iVar3 == 0)) {
    sVar4 = _fread(&local_328,4,1,_File);
    if (sVar4 == 0) goto LAB_00477352;
    thunk_FUN_004fa5d9(&DAT_0064b690,50000);
    for (local_330 = 0; local_330 < local_328; local_330 = local_330 + 1) {
      pvVar6 = (void *)thunk_FUN_004fa617(&DAT_0064b690);
      if (pvVar6 == (void *)0x0) {
        thunk_FUN_00589ef8(0xfffffff7,3,0,0,0);
      }
      sVar4 = _fread(pvVar6,0x1bc,1,_File);
      if (sVar4 == 0) goto LAB_00477352;
    }
    for (local_734 = DAT_0064b99c; local_734 != 0; local_734 = *(int *)(local_734 + 0x1bc)) {
      if (*(int *)(local_734 + 8) != 0) {
        uVar7 = thunk_FUN_00473c68(_File);
        *(undefined4 *)(local_734 + 8) = uVar7;
        if (*(int *)(local_734 + 8) == 0) goto LAB_00477352;
      }
      if (*(int *)(local_734 + 0x10) != 0) {
        uVar7 = thunk_FUN_00473c68(_File);
        *(undefined4 *)(local_734 + 0x10) = uVar7;
        if (*(int *)(local_734 + 0x10) == 0) goto LAB_00477352;
      }
      if (*(int *)(local_734 + 0x14) != 0) {
        uVar7 = thunk_FUN_00473c68(_File);
        *(undefined4 *)(local_734 + 0x14) = uVar7;
        if (*(int *)(local_734 + 0x14) == 0) goto LAB_00477352;
      }
      if (*(int *)(local_734 + 0x20) != 0) {
        uVar7 = thunk_FUN_00473c68(_File);
        *(undefined4 *)(local_734 + 0x20) = uVar7;
        if (*(int *)(local_734 + 0x20) == 0) goto LAB_00477352;
      }
      for (local_330 = 0; (local_330 < 0x14 && (*(int *)(local_734 + 0x38 + local_330 * 4) != 0));
          local_330 = local_330 + 1) {
        uVar7 = thunk_FUN_00473c68(_File);
        *(undefined4 *)(local_734 + 0x38 + local_330 * 4) = uVar7;
        if (*(int *)(local_734 + 0x38 + local_330 * 4) == 0) goto LAB_00477352;
      }
      if (*(int *)(local_734 + 0x88) != 0) {
        uVar7 = thunk_FUN_00473c68(_File);
        *(undefined4 *)(local_734 + 0x88) = uVar7;
        if (*(int *)(local_734 + 0x88) == 0) goto LAB_00477352;
      }
      if (*(int *)(local_734 + 0x90) != 0) {
        uVar7 = thunk_FUN_00473c68(_File);
        *(undefined4 *)(local_734 + 0x90) = uVar7;
        if (*(int *)(local_734 + 0x90) == 0) goto LAB_00477352;
      }
      if (*(int *)(local_734 + 0xc4) != 0) {
        uVar7 = thunk_FUN_00473c68(_File);
        *(undefined4 *)(local_734 + 0xc4) = uVar7;
        if (*(int *)(local_734 + 0xc4) == 0) goto LAB_00477352;
      }
      if (*(int *)(local_734 + 0xcc) != 0) {
        uVar7 = thunk_FUN_00473c68(_File);
        *(undefined4 *)(local_734 + 0xcc) = uVar7;
        if (*(int *)(local_734 + 0xcc) == 0) goto LAB_00477352;
      }
      if (*(int *)(local_734 + 0xd4) != 0) {
        uVar7 = thunk_FUN_00473c68(_File);
        *(undefined4 *)(local_734 + 0xd4) = uVar7;
        if (*(int *)(local_734 + 0xd4) == 0) goto LAB_00477352;
      }
      if (*(int *)(local_734 + 0xdc) != 0) {
        uVar7 = thunk_FUN_00473c68(_File);
        *(undefined4 *)(local_734 + 0xdc) = uVar7;
        if (*(int *)(local_734 + 0xdc) == 0) goto LAB_00477352;
      }
      if (*(int *)(local_734 + 0x13c) != 0) {
        uVar7 = thunk_FUN_00473c68(_File);
        *(undefined4 *)(local_734 + 0x13c) = uVar7;
        if (*(int *)(local_734 + 0x13c) == 0) goto LAB_00477352;
      }
      if (*(int *)(local_734 + 0x140) != 0) {
        uVar7 = thunk_FUN_00473c68(_File);
        *(undefined4 *)(local_734 + 0x140) = uVar7;
        if (*(int *)(local_734 + 0x140) == 0) goto LAB_00477352;
      }
      if (*(int *)(local_734 + 0x148) != 0) {
        uVar7 = thunk_FUN_00473c68(_File);
        *(undefined4 *)(local_734 + 0x148) = uVar7;
        if (*(int *)(local_734 + 0x148) == 0) goto LAB_00477352;
      }
      if (*(int *)(local_734 + 0x174) != 0) {
        uVar7 = thunk_FUN_00473c68(_File);
        *(undefined4 *)(local_734 + 0x174) = uVar7;
        if (*(int *)(local_734 + 0x174) == 0) goto LAB_00477352;
      }
      if (*(int *)(local_734 + 0x184) != 0) {
        uVar7 = thunk_FUN_00473c68(_File);
        *(undefined4 *)(local_734 + 0x184) = uVar7;
        if (*(int *)(local_734 + 0x184) == 0) goto LAB_00477352;
      }
    }
    thunk_FUN_004cef35();
    DAT_00627670 = 1;
  }
  thunk_FUN_00484d52();
  thunk_FUN_00419ed3();
  cVar1 = game.player_civ;
  if ((local_220 == 0) && ((game.game_flags & 0x80) == 0)) {
    if (game.multiplayer == 0) {
      leaders[civs[(char)game.player_civ].tribe].leader_name =
           -leaders[civs[(char)game.player_civ].tribe].leader_name;
      if (local_71c[0] < 0) {
        leaders[civs[(char)game.player_civ].tribe].plural =
             -leaders[civs[(char)game.player_civ].tribe].plural;
      }
      if (local_71c[1] < 0) {
        leaders[civs[(char)game.player_civ].tribe].adjective =
             -leaders[civs[(char)game.player_civ].tribe].adjective;
      }
      for (local_21c = 0; local_21c < 7; local_21c = local_21c + 1) {
        for (local_738 = 0; local_738 < 2; local_738 = local_738 + 1) {
          if (local_71c[local_738 + local_21c * 2 + 4] < 0) {
            leaders[civs[(char)game.player_civ].tribe].titles[local_21c][local_738]
                 = -leaders[civs[(char)game.player_civ].tribe].titles[local_21c][local_738];
          }
        }
      }
    }
    else {
      for (local_748 = 0; game.player_civ = cVar1, local_748 < 8; local_748 = local_748 + 1) {
        if ((1 << ((byte)local_748 & 0x1f) & (uint)game.human_players) != 0) {
          game.player_civ = (byte)local_748;
          leaders[civs[(char)(byte)local_748].tribe].leader_name =
               -leaders[civs[(char)(byte)local_748].tribe].leader_name;
          if (local_71c[civs[(char)game.player_civ].tribe * 0x18] < 0) {
            leaders[civs[(char)game.player_civ].tribe].plural = -leaders[civs[(char)game.player_civ].tribe].plural;
          }
          if (local_71c[civs[(char)game.player_civ].tribe * 0x18 + 1] < 0) {
            leaders[civs[(char)game.player_civ].tribe].adjective = -leaders[civs[(char)game.player_civ].tribe].adjective;
          }
          for (local_21c = 0; local_21c < 7; local_21c = local_21c + 1) {
            for (local_738 = 0; local_738 < 2; local_738 = local_738 + 1) {
              if (local_71c[local_21c * 2 +
                            local_738 +
                            civs[(char)game.player_civ].tribe * 0x18 + 4] < 0)
              {
                leaders[civs[(char)game.player_civ].tribe].titles[local_21c][local_738] =
                     -leaders[civs[(char)game.player_civ].tribe].titles[local_21c][local_738];
              }
            }
          }
        }
      }
    }
  }
  else {
    for (local_748 = 1; local_748 < 8; local_748 = local_748 + 1) {
      if ((civs[local_748].flags & 0x200) == 0) {
        leaders[civs[local_748].tribe].female = 0;
      }
      else {
        leaders[civs[local_748].tribe].female = 1;
      }
      civs[local_748].leader_portrait = civs[local_748].tribe;
      if (leaders[civs[local_748].tribe].female != '\0') {
        civs[local_748].leader_portrait = civs[local_748].leader_portrait + '\x15';
      }
      if (leaders[civs[local_748].tribe].plural < 1) {
        local_74c = ~(int)leaders[civs[local_748].tribe].plural + 1;
      }
      else {
        local_74c = (int)leaders[civs[local_748].tribe].plural;
      }
      pcVar2 = (char *)thunk_FUN_00428b0c(local_74c);
      iVar3 = _strcmp(&civ_names[local_748].tribe_name[0],pcVar2);
      if (iVar3 == 0) {
        for (local_21c = 0; local_21c < 7; local_21c = local_21c + 1) {
          for (local_738 = 0; local_738 < 2; local_738 = local_738 + 1) {
            leaders[civs[local_748].tribe].titles[local_21c][local_738] =
                 (short)(&government_titles[local_21c].male)[local_738]   /* [0] male, [1] female */;
          }
        }
      }
      leaders[civs[local_748].tribe].leader_name =
           -leaders[civs[local_748].tribe].leader_name;
      leaders[civs[local_748].tribe].plural =
           -leaders[civs[local_748].tribe].plural;
      leaders[civs[local_748].tribe].adjective =
           -leaders[civs[local_748].tribe].adjective;
    }
  }
  thunk_FUN_00484d52();
  for (local_748 = 0; local_748 < 8; local_748 = local_748 + 1) {
    for (local_730 = 0; local_730 < 0x3e; local_730 = local_730 + 1) {
      civs[local_748].units_in_production[local_730] = 0;
      civs[local_748].units_active[local_730] = 0;
    }
    for (local_744 = 0; local_744 < game.num_units; local_744 = local_744 + 1) {
      if ((units[local_744].id != 0) &&
         ((char)units[local_744].owner == local_748)) {
        civs[local_748].units_active[(uint)(byte)units[local_744].type] =
             civs[local_748].units_active[(uint)(byte)units[local_744].type] +
             '\x01';
      }
    }
    for (local_73c = 0; local_73c < game.num_cities; local_73c = local_73c + 1) {
      if (((cities[local_73c].id != 0) &&
          ((char)cities[local_73c].owner == local_748)) &&
         (-1 < (char)cities[local_73c].building)) {
        civs[local_748].units_in_production[(int)(char)cities[local_73c].building] =
             civs[local_748].units_in_production[(int)(char)cities[local_73c].building] +
             '\x01';
      }
    }
  }
  DAT_0062ee08 = 0xffffffff;
  thunk_FUN_0041a046(1);
  thunk_FUN_0041a422(1);
  thunk_FUN_0041a5c4(1);
  thunk_FUN_004a2020();
  DAT_00655280 = 1;
  iVar3 = thunk_FUN_00407f90(&DAT_00655284);
  iVar8 = thunk_FUN_00407f90(&DAT_006ab180);
  if (iVar3 == iVar8) {
    iVar3 = thunk_FUN_00407fc0(&DAT_00655284);
    iVar8 = thunk_FUN_00407fc0(&DAT_006ab180);
    if ((iVar3 != iVar8) || (local_220 != 0)) goto LAB_0047733e;
  }
  else {
LAB_0047733e:
    DAT_00655280 = 0;
  }
  local_338 = 0;
LAB_00477352:
  if (_File != (FILE *)0x0) {
    _fclose(_File);
  }
  if ((local_338 == 0) && (game.multiplayer != local_334)) {
    DAT_00654c74 = 1;
    if (local_334 == 0) {
      DAT_00654fac = 0;
      DAT_00654fae = 0;
    }
    DAT_0066654e = 0;
    if (game.human_players == 0) {
      if ((DAT_00628048 == 0) || ((1 << (DAT_00628048 & 0x1f) & (uint)game.civs_alive) == 0)) {
        for (local_330 = 1; local_330 < 8; local_330 = local_330 + 1) {
          if ((1 << ((byte)local_330 & 0x1f) & (uint)game.civs_alive) != 0) {
            game.human_players = (byte)(1 << ((byte)local_330 & 0x1f));
            break;
          }
        }
      }
      else {
        game.human_players = (byte)(1 << (DAT_00628048 & 0x1f));
      }
    }
    if (local_334 != 0) {
      game.multiplayer = (byte)local_334;
    }
  }
  return local_338;
}
#undef DAT_00627670
#undef DAT_00628048
#undef DAT_0062ee08
#undef DAT_006365e0
#undef DAT_006365e4
#undef DAT_0064b1b0
#undef DAT_0064b1b4
#undef DAT_0064b99c
#undef DAT_0064bc60
#undef DAT_00654c74
#undef DAT_00654c76
#undef DAT_00654c78
#undef DAT_00654c7a
#undef DAT_00654fa4
#undef DAT_00654fac
#undef DAT_00654fae
#undef DAT_00655128
#undef DAT_00655280
#undef DAT_00666548
#undef DAT_0066654a
#undef DAT_0066654c
#undef DAT_0066654e
#undef DAT_0066c600
#undef DAT_0066ca88
#undef DAT_0066ca8a
#undef DAT_0066ca8c
#undef DAT_006ad6ae
#undef DAT_006ad7b2
#undef DAT_006d1da0
#undef local_74c
#undef local_748
#undef local_744
#undef local_73c
#undef local_738
#undef local_734
#undef local_730
#undef local_728
#undef local_71c
#undef asStack_714
#undef local_338
#undef local_334
#undef local_330
#undef local_32c
#undef local_328
#undef local_324
#undef local_220
#undef local_21c
#undef local_218
#undef local_114
#undef local_110
#undef local_10c
#undef local_108


/* FUN_005bd610 is declared to return undefined1 but returns the whole window
   style dword (*this); callers test bit 0x200 (SWS_ATTACHED) in AH.  Read
   here directly (a call through a cast to another return type traps in
   wasm). */
#define WIN_STYLE(w) (*(uint *)(w))

/* 0x005bd566 */
void __cdecl FUN_005bd566(int param_1,int param_2)

{
  HWND pHVar1;
  void *this;
  
  if (param_1 != 0) {
    if (param_2 == 0) {
      *(undefined4 *)(param_1 + 0x10) = 0;
    }
    else {
      pHVar1 = GetParent(*(HWND *)(param_2 + 4));
      if (pHVar1 == *(HWND *)(param_1 + 4)) {
        this = (void *)GetWindowLongA(*(HWND *)(param_2 + 4),0);
        if ((WIN_STYLE(this) & 0x200) == 0) {
          FUN_005d225b(s_Window_not_SWS_ATTACHED_in_MSSet_0063672c);
        }
        else {
          *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(param_2 + 4);
        }
      }
      else {
        FUN_005d225b(s_Window_not_a_child_in_MSSetTopMo_00636704);
      }
    }
  }
  return;
}


/* 0x005dbe88 */
#define local_a0 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_98 (*(tagPAINTSTRUCT *)(frame_ + FRAME_OFF(8)))
#define local_58 (*(int *)(frame_ + FRAME_OFF(72)))
#define local_54 (*(void * *)(frame_ + FRAME_OFF(76)))
#define local_50 (*(HDC *)(frame_ + FRAME_OFF(80)))
#define local_4c (*(int *)(frame_ + FRAME_OFF(84)))
#define local_48 (*(int *)(frame_ + FRAME_OFF(88)))
#define local_44 (*(int *)(frame_ + FRAME_OFF(92)))
#define local_40 (*(int *)(frame_ + FRAME_OFF(96)))
#define local_3c (*(int *)(frame_ + FRAME_OFF(100)))
#define local_38 (*(RECT *)(frame_ + FRAME_OFF(104)))
#define local_28 (*(tagRECT *)(frame_ + FRAME_OFF(120)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(136)))
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(140)))
LRESULT __stdcall FUN_005dbe88(HWND param_1,uint param_2,WPARAM param_3,uint param_4)

{
  HWND pHVar1;
  HDC pHVar2;
  BOOL BVar3;
  HICON hIcon;
  LRESULT LVar4;
  void *pvVar5;
  int iVar6;
  int iVar7;
  tagRECT *ptVar8;
  tagRECT *ptVar9;
  undefined1 frame_[FRAME_OFF(160)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_2 < 0x10) {
    if (param_2 == 0xf) {
      local_50 = BeginPaint(param_1,&local_98);
      local_54 = (void *)GetWindowLongA(param_1,0);
      BVar3 = IsIconic(param_1);
      if (BVar3 != 0) {
        GetWindowRect(param_1,&local_14);
        iVar6 = thunk_FUN_00414d10(local_54);
        if (*(int *)(iVar6 + 0x20) == 0) {
          hIcon = LoadIconA((HINSTANCE)0x0,(LPCSTR)0x7f00);
          DrawIcon(local_50,0,0,hIcon);
        }
        else {
          iVar6 = thunk_FUN_00414d10(local_54);
          if ((*(int *)(iVar6 + 0x18) != 0) && (DAT_00638b48 == 1)) {
            iVar6 = thunk_FUN_00414d10(local_54);
            RealizePalette(*(HDC *)(iVar6 + 8));
          }
          iVar6 = thunk_FUN_00414d10(local_54);
          DrawIcon(local_50,0,0,*(HICON *)(iVar6 + 0x20));
        }
        return 0;
      }
      iVar6 = thunk_FUN_00414d10(local_54);
      if (*(int *)(iVar6 + 0x24) == 0) {
        iVar6 = thunk_FUN_00414d10(local_54);
        if (*(int *)(iVar6 + 0x14) != 0) {
          iVar6 = thunk_FUN_00414d10(local_54);
          FillRect(local_50,&local_98.rcPaint,*(HBRUSH *)(iVar6 + 0x14));
        }
      }
      else {
        iVar6 = thunk_FUN_00414d10(local_54);
        local_3c = thunk_FUN_0043c590(*(void **)(iVar6 + 0x24));
        iVar6 = thunk_FUN_00414d10(local_54);
        local_44 = thunk_FUN_0043c560(*(void **)(iVar6 + 0x24));
        if ((local_3c != 0) && (local_44 != 0)) {
          local_38.left = local_98.rcPaint.left;
          local_38.top = local_98.rcPaint.top;
          local_38.right = local_98.rcPaint.right;
          local_38.bottom = local_98.rcPaint.bottom;
          SetRect(&local_14,0,0,local_3c,local_44);
          for (local_58 = local_38.top / local_44; local_58 < local_38.bottom / local_44 + 1;
              local_58 = local_58 + 1) {
            for (local_4c = local_38.left / local_3c; local_4c < local_38.right / local_3c + 1;
                local_4c = local_4c + 1) {
              SetRect(&local_28,local_4c * local_3c,local_58 * local_44,
                      local_4c * local_3c + local_3c,local_58 * local_44 + local_44);
              ptVar9 = &local_28;
              ptVar8 = &local_14;
              pvVar5 = local_54;
              iVar6 = thunk_FUN_00414d10(local_54);
              FUN_005c0979(*(void **)(iVar6 + 0x24),pvVar5,ptVar8,ptVar9);
            }
          }
        }
      }
      iVar6 = thunk_FUN_00414d10(local_54);
      if (*(int *)(iVar6 + 0x2c) != 0) {
        iVar6 = thunk_FUN_00414d10(local_54);
        local_3c = thunk_FUN_0043c590(*(void **)(iVar6 + 0x2c));
        iVar6 = thunk_FUN_00414d10(local_54);
        local_44 = thunk_FUN_0043c560(*(void **)(iVar6 + 0x2c));
        local_38.left = local_98.rcPaint.left;
        local_38.top = local_98.rcPaint.top;
        local_38.right = local_98.rcPaint.right;
        local_38.bottom = local_98.rcPaint.bottom;
        SetRect(&local_14,0,0,local_3c,local_44);
        iVar6 = thunk_FUN_00414bb0(local_54);
        iVar6 = iVar6 - local_44 >> 1;
        iVar7 = thunk_FUN_004080c0(local_54);
        OffsetRect(&local_14,iVar7 - local_3c >> 1,iVar6);
        BVar3 = IntersectRect(&local_28,&local_14,&local_38);
        if (BVar3 != 0) {
          local_14.left = local_28.left;
          local_14.top = local_28.top;
          local_14.right = local_28.right;
          local_14.bottom = local_28.bottom;
          iVar6 = thunk_FUN_00414bb0(local_54);
          iVar6 = -(iVar6 - local_44 >> 1);
          iVar7 = thunk_FUN_004080c0(local_54);
          OffsetRect(&local_14,-(iVar7 - local_3c >> 1),iVar6);
          ptVar9 = &local_28;
          ptVar8 = &local_14;
          pvVar5 = local_54;
          iVar6 = thunk_FUN_00414d10(local_54);
          FUN_005c0979(*(void **)(iVar6 + 0x2c),pvVar5,ptVar8,ptVar9);
        }
      }
      EndPaint(param_1,&local_98);
      return 0;
    }
    switch(param_2) {
    case 2:
      SetMenu(param_1,(HMENU)0x0);
      pvVar5 = (void *)GetWindowLongA(param_1,0);
      iVar6 = thunk_FUN_00414d10(pvVar5);
      *(undefined4 *)(iVar6 + 0x44) = 1;
      if ((*(byte *)(iVar6 + 0x49) & 2) != 0) {
        iVar6 = 0;
        pHVar1 = GetParent(param_1);
        pvVar5 = (void *)GetWindowLongA(pHVar1,iVar6);
        local_18 = thunk_FUN_00414d10(pvVar5);
        if (*(HWND *)(local_18 + 0xc) == param_1) {
          *(undefined4 *)(local_18 + 0xc) = 0;
        }
      }
      LVar4 = DefWindowProcA(param_1,param_2,param_3,param_4);
      return LVar4;
    case 3:
      local_54 = (void *)GetWindowLongA(param_1,0);
      if (local_54 != (void *)0x0) {
        iVar6 = thunk_FUN_00414d10(local_54);
        pHVar2 = *(HDC *)(iVar6 + 8);
        iVar6 = thunk_FUN_00414d10(local_54);
        ReleaseDC(*(HWND *)(iVar6 + 4),pHVar2);
        iVar6 = thunk_FUN_00414d10(local_54);
        iVar7 = thunk_FUN_00414d10(local_54);
        pHVar2 = GetDC(*(HWND *)(iVar7 + 4));
        *(HDC *)(iVar6 + 8) = pHVar2;
      }
      break;
    case 5:
      local_54 = (void *)GetWindowLongA(param_1,0);
      if ((local_54 != (void *)0x0) &&
         (iVar6 = thunk_FUN_00414d10(local_54), *(int *)(iVar6 + 0x2c) != 0)) {
        InvalidateRect(param_1,(RECT *)0x0,1);
      }
      if (local_54 != (void *)0x0) {
        iVar6 = thunk_FUN_00414d10(local_54);
        pHVar2 = *(HDC *)(iVar6 + 8);
        iVar6 = thunk_FUN_00414d10(local_54);
        ReleaseDC(*(HWND *)(iVar6 + 4),pHVar2);
        iVar6 = thunk_FUN_00414d10(local_54);
        iVar7 = thunk_FUN_00414d10(local_54);
        pHVar2 = GetDC(*(HWND *)(iVar7 + 4));
        *(HDC *)(iVar6 + 8) = pHVar2;
      }
      break;
    case 7:
      pvVar5 = (void *)GetWindowLongA(param_1,0);
      iVar6 = thunk_FUN_00414d10(pvVar5);
      if (*(int *)(iVar6 + 0xc) != 0) {
        SendMessageA(*(HWND *)(iVar6 + 0xc),0x86,1,0);
      }
      break;
    case 8:
      pvVar5 = (void *)GetWindowLongA(param_1,0);
      iVar6 = thunk_FUN_00414d10(pvVar5);
      if (*(int *)(iVar6 + 0xc) != 0) {
        SendMessageA(*(HWND *)(iVar6 + 0xc),0x86,0,0);
      }
    }
  }
  else if (param_2 < 0x47) {
    if (param_2 == 0x46) {
      if ((*(byte *)(param_4 + 0x18) & 4) == 0) {
        local_54 = (void *)GetWindowLongA(param_1,0);
        thunk_FUN_00414d10(local_54);
        if ((WIN_STYLE(local_54) & 0x200) != 0) {
          iVar6 = 0;
          pHVar1 = GetParent(param_1);
          pvVar5 = (void *)GetWindowLongA(pHVar1,iVar6);
          local_18 = thunk_FUN_00414d10(pvVar5);
          if (((*(int *)(local_18 + 0x10) != 0) && (*(HWND *)(local_18 + 0x10) != param_1)) &&
             (BVar3 = IsWindowVisible(*(HWND *)(local_18 + 0x10)), BVar3 != 0)) {
            *(undefined4 *)(param_4 + 4) = *(undefined4 *)(local_18 + 0x10);
          }
        }
      }
    }
    else if (param_2 == 0x22) {
      pvVar5 = (void *)GetWindowLongA(param_1,0);
      iVar6 = thunk_FUN_00414d10(pvVar5);
      if ((*(byte *)(iVar6 + 0x49) & 2) != 0) {
        iVar6 = 0;
        pHVar1 = GetParent(param_1);
        pvVar5 = (void *)GetWindowLongA(pHVar1,iVar6);
        local_18 = thunk_FUN_00414d10(pvVar5);
        if (*(int *)(local_18 + 0xc) != 0) {
          SendMessageA(*(HWND *)(local_18 + 0xc),0x86,0,0);
        }
        SendMessageA(param_1,0x86,1,0);
        *(HWND *)(local_18 + 0xc) = param_1;
      }
    }
  }
  else {
    if (param_2 < 0xa5) {
      if ((param_2 != 0xa4) && (param_2 != 0xa1)) goto switchD_005dc5f2_caseD_4;
    }
    else {
      if (param_2 == 0x112) {
        if ((param_3 == 0xf100) || (param_3 == 0xf090)) {
          pvVar5 = (void *)GetWindowLongA(param_1,0);
          iVar6 = thunk_FUN_00414d10(pvVar5);
          if ((*(byte *)(iVar6 + 0x48) & 0x20) == 0) {
            return 0;
          }
        }
        goto switchD_005dc5f2_caseD_4;
      }
      if ((param_2 != 0x201) && (param_2 != 0x204)) goto switchD_005dc5f2_caseD_4;
    }
    pvVar5 = (void *)GetWindowLongA(param_1,0);
    iVar6 = thunk_FUN_00414d10(pvVar5);
    if ((*(byte *)(iVar6 + 0x49) & 2) != 0) {
      SetFocus(*(HWND *)(iVar6 + 4));
      BringWindowToTop(param_1);
    }
  }
switchD_005dc5f2_caseD_4:
  local_a0 = DefWindowProcA(param_1,param_2,param_3,param_4);
  if (param_2 == 0x84) {
    pvVar5 = (void *)GetWindowLongA(param_1,0);
    iVar6 = thunk_FUN_00414d10(pvVar5);
    if ((*(int *)(iVar6 + 0x34) != 0) && (local_a0 == 1)) {
      GetWindowRect(param_1,&local_14);
      local_40 = (param_4 & 0xffff) - local_14.left;
      local_48 = (param_4 >> 0x10) - local_14.top;
      if (*(int *)(iVar6 + 0x3c) == 0) {
        local_3c = 5;
      }
      else {
        local_3c = *(int *)(iVar6 + 0x3c);
      }
      GetClientRect(param_1,&local_28);
      local_58 = 0;
      local_4c = 0;
      if (local_48 < local_3c) {
        local_58 = -1;
      }
      else {
        iVar7 = thunk_FUN_00407fc0(&local_28);
        if (iVar7 - local_3c < local_48) {
          local_58 = 1;
        }
      }
      if (local_40 < local_3c) {
        local_4c = -1;
      }
      else {
        iVar7 = thunk_FUN_00407f90(&local_28);
        if (iVar7 - local_3c < local_40) {
          local_4c = 1;
        }
      }
      if (local_58 < 0) {
        if (local_40 < local_3c * 4) {
          local_4c = -1;
        }
        else {
          iVar7 = thunk_FUN_00407f90(&local_28);
          if (iVar7 + local_3c * -4 < local_40) {
            local_4c = 1;
          }
        }
        if (local_4c < 0) {
          local_a0 = 0xd;
        }
        else if (local_4c < 1) {
          local_a0 = 0xc;
        }
        else {
          local_a0 = 0xe;
        }
      }
      else if (local_58 < 1) {
        if (local_4c < 0) {
          if (local_48 < local_3c * 4) {
            local_58 = -1;
          }
          else {
            iVar7 = thunk_FUN_00407fc0(&local_28);
            if (iVar7 + local_3c * -4 < local_48) {
              local_58 = 1;
            }
          }
          if (local_58 < 0) {
            local_a0 = 0xd;
          }
          else if (local_58 < 1) {
            local_a0 = 10;
          }
          else {
            local_a0 = 0x10;
          }
        }
        else if (0 < local_4c) {
          if (local_48 < local_3c * 4) {
            local_58 = -1;
          }
          else {
            iVar7 = thunk_FUN_00407fc0(&local_28);
            if (iVar7 + local_3c * -4 < local_48) {
              local_58 = 1;
            }
          }
          if (local_58 < 0) {
            local_a0 = 0xe;
          }
          else if (local_58 < 1) {
            local_a0 = 0xb;
          }
          else {
            local_a0 = 0x11;
          }
        }
      }
      else {
        if (local_40 < local_3c * 4) {
          local_4c = -1;
        }
        else {
          iVar7 = thunk_FUN_00407f90(&local_28);
          if (iVar7 + local_3c * -4 < local_40) {
            local_4c = 1;
          }
        }
        if (local_4c < 0) {
          local_a0 = 0x10;
        }
        else if (local_4c < 1) {
          local_a0 = 0xf;
        }
        else {
          local_a0 = 0x11;
        }
      }
    }
    if ((*(int *)(iVar6 + 0x30) != 0) && (local_a0 == 1)) {
      GetWindowRect(param_1,&local_14);
      local_48 = (param_4 >> 0x10) - local_14.top;
      if ((*(int *)(iVar6 + 0x38) == 0) || (local_48 < *(int *)(iVar6 + 0x38))) {
        local_a0 = 2;
      }
    }
    if (local_a0 == 1) {
      SetCursor(*(HCURSOR *)(iVar6 + 0x1c));
    }
  }
  return local_a0;
}
#undef local_a0
#undef local_98
#undef local_58
#undef local_54
#undef local_50
#undef local_4c
#undef local_48
#undef local_44
#undef local_40
#undef local_3c
#undef local_38
#undef local_28
#undef local_18
#undef local_14


/* 0x005eacc0 */
#define local_4c (*(tagRECT *)(frame_ + FRAME_OFF(4)))
#define local_3c (*(HWND *)(frame_ + FRAME_OFF(20)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_34 (*(HWND *)(frame_ + FRAME_OFF(28)))
#define local_30 (*(HWND *)(frame_ + FRAME_OFF(32)))
#define local_2c (*(undefined4 *)(frame_ + FRAME_OFF(36)))
#define local_28 (*(undefined4 *)(frame_ + FRAME_OFF(40)))
#define local_24 (*(void * *)(frame_ + FRAME_OFF(44)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_1c (*(LONG *)(frame_ + FRAME_OFF(52)))
#define local_18 (*(void * *)(frame_ + FRAME_OFF(56)))
#define local_14 (*(LONG *)(frame_ + FRAME_OFF(60)))
#define local_10 (*(HWND *)(frame_ + FRAME_OFF(64)))
#define local_c (*(HWND *)(frame_ + FRAME_OFF(68)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(72)))
LRESULT __stdcall FUN_005eacc0(HWND param_1,uint param_2,uint param_3,HWND param_4)

{
  char cVar1;
  SHORT SVar2;
  LRESULT LVar3;
  HWND pHVar4;
  void *pvVar5;
  undefined4 uVar6;
  BOOL BVar7;
  uint uVar8;
  DWORD DVar9;
  int iVar10;
  undefined1 frame_[FRAME_OFF(80)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_18 = (void *)GetWindowLongA(param_1,8);
  if (local_18 == (void *)0x0) {
    LVar3 = FUN_005eb447(param_1,param_2,param_3,param_4);
    return LVar3;
  }
  if (param_2 < 6) {
    if (param_2 == 5) {
      local_34 = (HWND)FUN_005eac6d(*(undefined4 *)((int)local_18 + 0xb8));
      if (local_34 != (HWND)0x0) {
        SendMessageA(local_34,5,param_3,(LPARAM)param_4);
      }
      LVar3 = FUN_005eb447(param_1,5,param_3,param_4);
      return LVar3;
    }
    if (param_2 == 2) {
      *(undefined4 *)((int)local_18 + 0xb8) = 0;
      SetWindowLongA(param_1,8,0);
      LVar3 = FUN_005eb447(param_1,2,param_3,param_4);
      return LVar3;
    }
  }
  else if (param_2 < 0x101) {
    if (param_2 == 0x100) {
      SVar2 = GetAsyncKeyState(0x10);
      iVar10 = (int)SVar2;
      (*(undefined1 *)((char *)&local_2c + 1)) = (char)((ushort)SVar2 >> 8);
      local_2c = iVar10;
      if ((param_3 == 9) && ((*(undefined1 *)((char *)&local_2c + 1)) == '\0')) {
        cVar1 = FUN_005cbdd0(local_18);
        if (cVar1 != '\0') {
          FUN_005ea8d3(local_18,0,2);
        }
      }
      else if ((param_3 == 9) && ((*(undefined1 *)((char *)&local_2c + 1)) != '\0')) {
        cVar1 = FUN_005cbdd0(local_18);
        if (cVar1 != '\0') {
          FUN_005ea8d3(local_18,0,3);
        }
      }
      else if ((param_3 == 0xd) && ((*(undefined1 *)((char *)&local_2c + 1)) == '\0')) {
        if (*(int *)((int)local_18 + 0xbc) != 0) {
          uVar6 = thunk_FUN_00418770(*(void **)((int)local_18 + 0xbc));
          FUN_005cac22(uVar6);
        }
      }
      else if ((param_3 == 0x1b) && ((*(undefined1 *)((char *)&local_2c + 1)) == '\0')) {
        if (*(int *)((int)local_18 + 0xc0) != 0) {
          uVar6 = thunk_FUN_00418770(*(void **)((int)local_18 + 0xc0));
          FUN_005cac22(uVar6);
        }
      }
      else {
        uVar6 = FUN_005eb3ed(param_3);
        FUN_005c5c86(local_18,uVar6);
      }
      BVar7 = IsWindow(param_1);
      if (BVar7 == 0) {
        return 0;
      }
      LVar3 = FUN_005eb447(param_1,0x100,param_3,param_4);
      return LVar3;
    }
    if (param_2 == 0x46) {
      if ((((WINDOWPOS *)param_4)->flags & 4) == 0) {   /* WM_WINDOWPOSCHANGING: SWP_NOZORDER */
        local_24 = (void *)GetWindowLongA(param_1,0);
        local_28 = thunk_FUN_00414d10(local_24);
        if ((WIN_STYLE(local_24) & 0x200) != 0) {
          iVar10 = 0;
          pHVar4 = GetParent(param_1);
          pvVar5 = (void *)GetWindowLongA(pHVar4,iVar10);
          local_8 = thunk_FUN_00414d10(pvVar5);
          local_1c = GetWindowLongA(*(HWND *)(local_8 + 4),8);
          if ((local_1c != 0) &&
             (local_38 = FUN_005eac6d(*(undefined4 *)(local_1c + 0xb8)), local_38 != 0)) {
            ((WINDOWPOS *)param_4)->hwndInsertAfter = (HWND)(iptr)local_38;
            LVar3 = DefWindowProcA(param_1,0x46,param_3,(LPARAM)param_4);
            return LVar3;
          }
        }
      }
      LVar3 = FUN_005eb447(param_1,0x46,param_3,param_4);
      return LVar3;
    }
  }
  else {
    if (param_2 < 0x116) {
      if (param_2 < 0x114) {
        if (param_2 != 0x111) goto LAB_005eb241;
        uVar8 = param_3 >> 0x10;
        if (uVar8 < 0x301) {
          if (uVar8 == 0x300) {
            local_10 = param_4;
            DVar9 = GetClassLongA(param_4,-0x12);
            local_20 = DVar9 - 4;
            local_14 = GetWindowLongA(local_10,local_20);
            FUN_005eb330(local_14);
          }
          else if (uVar8 == 1) {
            local_30 = param_4;
            SendMessageA(param_4,0x4c8,param_3,(LPARAM)param_4);
          }
          else {
            if (uVar8 != 2) goto LAB_005eb1df;
            local_30 = param_4;
            SendMessageA(param_4,0x4c8,param_3,(LPARAM)param_4);
          }
        }
        else {
          if (uVar8 != 0x501) {
LAB_005eb1df:
            LVar3 = FUN_005eb447(param_1,0x111,param_3,param_4);
            return LVar3;
          }
          local_10 = param_4;
          DVar9 = GetClassLongA(param_4,-0x12);
          local_20 = DVar9 - 4;
          local_14 = GetWindowLongA(local_10,local_20);
          FUN_005eb2f0(local_14);
        }
      }
      else {
        iVar10 = thunk_FUN_00414d10(local_18);
        if (((*(byte *)(iVar10 + 0x48) & 0x80) != 0) ||
           (iVar10 = thunk_FUN_00414d10(local_18), (*(byte *)(iVar10 + 0x49) & 1) != 0)) {
          LVar3 = FUN_005eb447(param_1,param_2,param_3,param_4);
          return LVar3;
        }
        local_c = param_4;
        FUN_005cd149(param_4,param_2,param_3,param_4);
      }
      return 0;
    }
    if (param_2 == 0x216) {
      local_24 = (void *)GetWindowLongA(param_1,0);
      local_28 = thunk_FUN_00414d10(local_24);
      if ((WIN_STYLE(local_24) & 0x200) != 0) {
        iVar10 = 0;
        pHVar4 = GetParent(param_1);
        pvVar5 = (void *)GetWindowLongA(pHVar4,iVar10);
        local_8 = thunk_FUN_00414d10(pvVar5);
        local_1c = GetWindowLongA(*(HWND *)(local_8 + 4),8);
        if (((local_1c != 0) &&
            (local_3c = (HWND)FUN_005eac6d(*(undefined4 *)(local_1c + 0xb8)), local_3c != (HWND)0x0)
            ) && (BVar7 = IsWindowVisible(local_3c), BVar7 != 0)) {
          iVar10 = GetSystemMetrics(4);
          GetWindowRect(local_3c,&local_4c);
          local_2c = thunk_FUN_00407f90(param_4);
          if (local_4c.top - iVar10 <= ((RECT *)param_4)->top) {   /* WM_MOVING */
            ((RECT *)param_4)->top = local_4c.top - iVar10;
            ((RECT *)param_4)->bottom = (local_4c.top - iVar10) + local_2c;
          }
        }
      }
      LVar3 = FUN_005eb447(param_1,0x216,param_3,param_4);
      return LVar3;
    }
  }
LAB_005eb241:
  LVar3 = FUN_005eb447(param_1,param_2,param_3,param_4);
  return LVar3;
}
#undef local_4c
#undef local_3c
#undef local_38
#undef local_34
#undef local_30
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


/* 0x0048aa24 */
#define DAT_006d1da0 (*(int *)((u8 *)&g.d_006d1da0))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
uint __cdecl FUN_0048aa24(void)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_10 = -1;
  uVar1 = (uint)(short)game.turn;
  if (((1 < (int)uVar1) &&
      (uVar1 = ((short)game.turn + -1) / 0x32, ((short)game.turn + -1) % 0x32 == 0)) &&
     (((*(undefined1 *)((char *)&game.game_options + 2)) & 0x10) != 0)) {
    local_c = -1;
    for (local_14 = 0; local_14 < game.num_cities; local_14 = local_14 + 1) {
      if ((cities[local_14].id != 0) &&
         ((char)cities[local_14].owner == DAT_006d1da0)) {
        local_8 = (int)(char)cities[local_14].size;
        iVar2 = thunk_FUN_0043d20a(local_14,1);
        if (iVar2 != 0) {
          local_8 = local_8 << 1;
        }
        if (local_8 == 1 || local_8 + -1 < 0) {
          local_8 = 0;
        }
        else {
          iVar2 = _rand();
          local_8 = iVar2 % local_8;
        }
        if (local_c < local_8) {
          local_c = local_8;
          local_10 = local_14;
        }
      }
    }
    uVar3 = thunk_FUN_00493c7d(DAT_006d1da0);
    thunk_FUN_0040ff60(0,uVar3);
    thunk_FUN_0040bbb0();
    thunk_FUN_00421f10((int)game.year);
    thunk_FUN_0040ff60(2,&DAT_00679640);
    thunk_FUN_0040bbb0();
    if (local_10 < 0) {
      thunk_FUN_0040bc10(0xe);
    }
    else {
      thunk_FUN_0040bbe0(cities[local_10].name);
      thunk_FUN_00410402(&DAT_0066c7a8,(int)cities[local_10].x,
                         (int)cities[local_10].y);
    }
    thunk_FUN_0040ff60(1,&DAT_00679640);
    uVar1 = thunk_FUN_00410030(s_COUNCILTIME_0062c6a4,&DAT_0063fc58,0);
    if (uVar1 == 0) {
      thunk_FUN_00516570(DAT_006d1da0,0);   /* void; result left in EAX is garbage */
    }
  }
  if (((*(undefined1 *)((char *)&game.game_options + 1)) & 1) != 0) {
    if (game.turn == 1) {
      thunk_FUN_004904c0(PTR_s_TUTORIAL_00627678,s_FIRSTMOVE_0062c6b0,&DAT_00643af8,0);
    }
    if ((game.turn == 0x14) || (game.turn == 0x3c)) {
      thunk_FUN_004904c0(PTR_s_TUTORIAL_00627678,s_HELP1_0062c6bc,&DAT_00643af8,0);
    }
    if ((game.turn == 0x28) || (game.turn == 0x50)) {
      thunk_FUN_004904c0(PTR_s_TUTORIAL_00627678,s_HELP2_0062c6c4,&DAT_00643af8,0);
    }
    if ((((civs[DAT_006d1da0].num_cities == 1) &&
         (2 < civs[DAT_006d1da0].total_city_size)) && (game.turn == 0x23)) &&
       ((civs[DAT_006d1da0].units_active[0] == '\0' &&
        (civs[DAT_006d1da0].units_in_production[0] == '\0')))) {
      uVar1 = thunk_FUN_0043d07a((int)map.width / 2,(int)map.height / 2,DAT_006d1da0,0xffffffff
                                 ,0xffffffff);
      if (-1 < (int)uVar1) {
        thunk_FUN_0040ff60(0,cities[uVar1].name);
        thunk_FUN_00490500(PTR_s_TUTORIAL_00627678,s_ONECITY_0062c6cc,uVar1);
        uVar1 = (int)(short)game.turn - 0x19;
        civs[DAT_006d1da0].last_city_turn = (short)uVar1;
      }
    }
    else {
      uVar1 = (int)(short)game.turn - (int)civs[DAT_006d1da0].last_city_turn;
      if ((0x18 < (int)uVar1) &&
         ((uVar1 = (uint)civs[DAT_006d1da0].num_cities, (int)uVar1 < 6 &&
          (uVar1 = DAT_006d1da0 * 0x165, civs[DAT_006d1da0].units_active[0] == '\0')))) {
        thunk_FUN_004904c0(PTR_s_TUTORIAL_00627678,s_EXPAND0_0062c6d4,&DAT_00643af8,0);
        uVar1 = (uint)game.turn;
        civs[DAT_006d1da0].last_city_turn = game.turn;
      }
    }
  }
  return uVar1;
}
#undef DAT_006d1da0
#undef local_14
#undef local_10
#undef local_c
#undef local_8


/* 0x004eb4ed */
#define DAT_0062ee08 (*(int *)((u8 *)&g.d_0062ee08))
#define DAT_006a6550 (*(int *)((u8 *)&g.d_006a6550))
#define DAT_006a65a8 (*(int *)((u8 *)&g.d_006a65a8))
int __cdecl FUN_004eb4ed(int param_1,int param_2)

{
  int iVar1;
  
  if (param_1 == -1) {
    iVar1 = 0;
  }
  else if (param_2 == 0) {
    iVar1 = DAT_006a6550 - DAT_006a65a8;
  }
  else {
    DAT_0062ee08 = param_1;
    thunk_FUN_004e7641(param_1);
    thunk_FUN_004e7967(param_1);
    thunk_FUN_004e80b1(param_1);
    /* FUN_004eb4a1, which is declared void but returns its last call's
       (FUN_004ea8e4's) int: */
    thunk_FUN_004e8f42(param_1);
    thunk_FUN_004eb327(param_1);
    thunk_FUN_004e97ae(param_1);
    thunk_FUN_004e9c14(param_1);
    iVar1 = thunk_FUN_004ea8e4(param_1);
  }
  return iVar1;
}
#undef DAT_0062ee08
#undef DAT_006a6550
#undef DAT_006a65a8


/* 0x004efd44 */
#define DAT_0064bc60 (*(ushort *)((u8 *)&g.d_0064bc60))
#define DAT_00654fa8 (*(short *)((u8 *)&g.d_00654fa8))
#define DAT_006d1da0 (*(undefined4 *)((u8 *)&g.d_006d1da0))
#define local_20 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(12)))
int __cdecl FUN_004efd44(int param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  undefined1 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  cVar1 = cities[param_1].owner;
  local_14 = (int)((uint)(byte)civs[cVar1].num_advances * (uint)game.difficulty) >> 1;
  if (((game.game_flags & 0x80) != 0) && ((DAT_0064bc60 & 0x40) != 0)) {
    local_14 = 0;
    DAT_006a6584 = 0;
  }
  iVar2 = thunk_FUN_0043d20a(param_1,0x1d);
  if (iVar2 != 0) {
    for (; 0xff < local_14; local_14 = local_14 / 2) {
    }
  }
  if (-local_14 == -0xff || -local_14 + 0xff < 0) {
    local_1c = 0;
  }
  else {
    local_1c = _rand();
    local_1c = local_1c % (0x100 - local_14);
  }
  if (local_1c < DAT_006a6584 * 2) {
    iVar2 = _rand();
    uVar3 = map_wrap_x((int)cities[param_1].x +
                               (int)(char)(&DAT_00628370)[iVar2 % 0x14]);
    iVar2 = (int)cities[param_1].y +
            (int)(char)(&DAT_006283a0)[iVar2 % 0x14];
    iVar4 = map_in_bounds(uVar3,iVar2);
    if (iVar4 != 0) {
      uVar5 = tile_improvements(uVar3,iVar2);
      if ((uVar5 & 0x82) == 0) {
        iVar4 = tile_is_ocean(uVar3,iVar2);
        if (iVar4 == 0) {
          tile_add_pollution(uVar3,iVar2);
          iVar4 = tile_visible_to(uVar3,iVar2,DAT_006d1da0);
          if (iVar4 != 0) {
            thunk_FUN_00410402(&DAT_0066c7a8,uVar3,iVar2);
            if ((game.message_options & 0x100) == 0) {
              thunk_FUN_004eb571(s_POLLUTION_0062ef64,param_1,0,0);
            }
          }
        }
      }
    }
  }
  iVar2 = param_1 * 0xb;
  if ((cities[param_1].flags & 1) != 0) {
    iVar4 = thunk_FUN_0043d20a(param_1,0x15);
    iVar2 = 0;
    if (iVar4 != 0) {
      iVar2 = thunk_FUN_004bd9f0((int)cVar1,0x20);
      if (iVar2 == 0) {
        iVar2 = 5 - (uint)game.difficulty;
        if (iVar2 < 1) {
          local_20 = 0;
        }
        else {
          local_20 = _rand();
          iVar2 = local_20 / (int)(6 - (uint)game.difficulty);
          local_20 = local_20 % (int)(6 - (uint)game.difficulty);
        }
        if (local_20 == 0) {
          iVar2 = tile_visible_to((int)cities[param_1].x,
                                     (int)cities[param_1].y,DAT_006d1da0);
          if (iVar2 != 0) {
            thunk_FUN_004105f8((int)cities[param_1].x,
                               (int)cities[param_1].y,
                               (int)(char)cities[param_1].owner);
          }
          thunk_FUN_0057f657((int)cities[param_1].x,
                             (int)cities[param_1].y);
          nuclear_blast((int)cities[param_1].x,
                             (int)cities[param_1].y);
          thunk_FUN_0043d289(param_1,0x15,0);
          iVar2 = (int)DAT_00654fa8;
          if (iVar2 == 0) {
            /* FUN_004f3f30 is declared void but returns FUN_004eb571's int:
               it is FUN_004eb571(a, b, 0, c) */
            iVar2 = thunk_FUN_004eb571(s_CHERNOBYL_0062ef70,param_1,0,&DAT_00645fe8);
          }
        }
      }
    }
  }
  return iVar2;
}
#undef DAT_0064bc60
#undef DAT_00654fa8
#undef DAT_006d1da0
#undef local_20
#undef local_1c
#undef local_14


/* 0x0058f040 */
#define DAT_006d1da0 (*(uint *)((u8 *)&g.d_006d1da0))
#define local_60 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
#define local_50 (*(uint *)(frame_ + FRAME_OFF(16)))
#define local_4c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_48 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_40 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_3c (*(undefined4 *)(frame_ + FRAME_OFF(36)))
#define local_38 (*(undefined4 *)(frame_ + FRAME_OFF(40)))
#define local_28 (*(undefined4 *)(frame_ + FRAME_OFF(56)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(64)))
#define local_14 (*(undefined4 *)(frame_ + FRAME_OFF(76)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(80)))
#define local_c (*(undefined4 *)(frame_ + FRAME_OFF(84)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(88)))
uint __cdecl FUN_0058f040(int param_1)

{
  bool bVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  int iVar9;
  uint uVar10;
  undefined1 frame_[FRAME_OFF(96)] __attribute__((aligned(8)));  /* original stack frame */
  
  bVar2 = units[param_1].owner;
  uVar3 = (uint)(char)bVar2;
  iVar4 = (int)units[param_1].x;
  uVar5 = (uint)units[param_1].y;
  local_50 = uVar5;
  if ((uVar3 != 0) &&
     (local_50 = (int)(char)unit_types[(uint)(byte)units[param_1].type].domain,
     (int)(char)unit_types[(uint)(byte)units[param_1].type].domain == 0)) {
    thunk_FUN_0043d07a(iVar4,uVar5,0xffffffff,0xffffffff,0xffffffff);
    iVar6 = _rand();
    local_50 = iVar6 % 5;
    if ((((((1 << (bVar2 & 0x1f) & (uint)game.human_players) == 0) || (iVar6 = _rand(), iVar6 % 3 == 0))
         && ((civs[uVar3].num_cities != 0 &&
             (iVar6 = tile_landmass(iVar4,uVar5),
             civs[uVar3].continent_cities[iVar6] == '\0')))) &&
        (((civs[uVar3].continent_flags[iVar6] & 0x7f) == 0 || (0xc < DAT_0063f660)))) &&
       (civs[uVar3].continent_cities[iVar6] == '\0')) {
      local_50 = 0;
    }
LAB_0058f1bc:
    switch(local_50) {
    case 0:
      if (DAT_0063f660 < 4) {
        local_50 = 1;
        goto LAB_0058f1bc;
      }
      if ((civs[uVar3].num_cities == 0) && (game.turn < 0x32)) {
        local_8 = 0;
        for (param_1 = 0; param_1 < game.num_units; param_1 = param_1 + 1) {
          if (((units[param_1].id != 0) &&
              (unit_types[(uint)(byte)units[param_1].type].role == '\x05')) &&
             (units[param_1].home_city == -1)) {
            local_8 = local_8 + 1;
          }
        }
        if (1 < local_8) {
          local_50 = 1;
          goto LAB_0058f1bc;
        }
      }
      iVar6 = thunk_FUN_005b8c42(iVar4,uVar5);
      if (0xb < iVar6) {
        if (DAT_006ad0d0 != '\0') {
          thunk_FUN_00410030(s_SURPRISETRIBE_00634ca4,&DAT_0063fc58,0);
        }
        iVar6 = thunk_FUN_0043f8b0(iVar4,uVar5,uVar3);
        if (999 < game.year) {
          iVar9 = _rand();
          bVar2 = (byte)(iVar9 >> 0x1f);
          cities[iVar6].size =
               ((((byte)iVar9 ^ bVar2) - bVar2 & 3 ^ bVar2) - bVar2) + '\x01';
          thunk_FUN_0043d289(iVar6,4,1);
          uVar3 = _rand();
          uVar7 = (int)uVar3 >> 0x1f;
          if (((uVar3 ^ uVar7) - uVar7 & 1 ^ uVar7) == uVar7) {
            thunk_FUN_0043d289(iVar6,5,1);
          }
          iVar9 = _rand();
          if (iVar9 % 3 == 0) {
            thunk_FUN_0043d289(iVar6,3,1);
          }
          uVar3 = _rand();
          uVar7 = (int)uVar3 >> 0x1f;
          if (((uVar3 ^ uVar7) - uVar7 & 3 ^ uVar7) == uVar7) {
            thunk_FUN_0043d289(iVar6,6,1);
          }
        }
        if (DAT_006ad0d0 == '\0') {
          return 0;
        }
        thunk_FUN_0047cf22(iVar4,uVar5);
        uVar3 = thunk_FUN_0046b14d(0x75,0xff,iVar4,uVar5,0,0,0,0,0,0);
        if (iVar6 < 0) {
          return uVar3;
        }
        thunk_FUN_00509590(&DAT_006a91b8,iVar6);   /* void: the caller ignores our result */
        return uVar3;
      }
      local_50 = 5;
      goto LAB_0058f1bc;
    case 1:
      if (DAT_006ad0d0 != '\0') {
        thunk_FUN_00410030(s_SURPRISEMERCS_00634d04,&DAT_0063fc58,0);
      }
      local_14 = 0x13;
      if (game.advance_known_by[11] == '\0') {
        iVar6 = _rand();
        if (iVar6 % 3 == 0) {
          local_14 = 0x10;
        }
        else {
          local_14 = 0xf;
        }
        if (game.advance_known_by[64] != '\0') {
          uVar7 = _rand();
          uVar10 = (int)uVar7 >> 0x1f;
          if (((uVar7 ^ uVar10) - uVar10 & 1 ^ uVar10) != uVar10) {
            local_14 = 0x11;
          }
        }
      }
      if (game.advance_known_by[55] != '\0') {
        local_14 = 0x12;
      }
      if (game.advance_known_by[42] != '\0') {
        local_14 = 0x14;
      }
      if (game.advance_known_by[17] != '\0') {
        local_14 = 0xb;
      }
      local_c = 8;
      if (game.advance_known_by[34] == '\0') {
        local_c = 7;
      }
      if (game.advance_known_by[35] == '\0') {
        local_c = 5;
      }
      if (game.advance_known_by[39] == '\0') {
        local_c = 4;
      }
      uVar7 = _rand();
      uVar10 = (int)uVar7 >> 0x1f;
      if (((uVar7 ^ uVar10) - uVar10 & 1 ^ uVar10) == uVar10) {
        local_60 = local_14;
      }
      else {
        local_60 = local_c;
      }
      iVar6 = thunk_FUN_005b3d06(local_60,uVar3,iVar4,uVar5);
      if ((DAT_006ad0d0 == '\0') && (DAT_006d1da0 != uVar3)) {
        local_50 = uVar3;
        if (-1 < iVar6) {
          local_50 = iVar6 * 0x20;
          *((i8 *)&units[0].home_city + local_50) = -1;   /* local_50 is a byte offset (unit index * 0x20) */
        }
      }
      else {
        thunk_FUN_0047cf22(iVar4,uVar5);
        local_50 = thunk_FUN_0046b14d(0x75,0xff,iVar4,uVar5,0,0,0,0,0,0);
      }
      break;
    case 2:
      local_20 = 0x32;
      iVar4 = _rand();
      if (iVar4 % 3 == 0) {
        iVar4 = _rand();
        if ((int)((iVar4 % 10 - (uint)game.difficulty) + 2) < 5) {
          local_20 = 0x19;
        }
        else {
          local_20 = 100;
        }
      }
      if (1000 < game.year) {
        local_20 = local_20 << 1;
      }
      civs[uVar3].gold = civs[uVar3].gold + local_20;
      thunk_FUN_00421da0(0,local_20);
      if (DAT_006ad0d0 != '\0') {
        thunk_FUN_00410030(s_SURPRISEMETALS_00634cd4,&DAT_0063fc58,0);
      }
      if (DAT_006d1da0 != uVar3) {
        return uVar3;
      }
      thunk_FUN_00569363(1);   /* void */
      return uVar3;
    case 3:
      if ((DAT_0063f660 < 4) ||
         ((civs[uVar3].num_cities == 0 && (game.turn < 0x32)))) {
        local_50 = 1;
        goto LAB_0058f1bc;
      }
      if (((1 << (bVar2 & 0x1f) & (uint)game.human_players) == 0) &&
         ((byte)game.power_rank[uVar3] < (byte)game.power_rank[game.field_139])) {
        uVar7 = _rand();
        uVar10 = (int)uVar7 >> 0x1f;
        if ((int)(((uVar7 ^ uVar10) - uVar10 & 7 ^ uVar10) - uVar10) < (int)(uint)game.difficulty) {
          local_50 = 0;
          goto LAB_0058f1bc;
        }
      }
      bVar1 = false;
      if (game.barbarian_activity < 3) {
        if (game.turn < 0x1e) {
LAB_0058f87c:
          thunk_FUN_0043d07a(iVar4,uVar5,uVar3,0xffffffff,0xffffffff);
          iVar6 = tile_landmass(iVar4,uVar5);
          if ((civs[uVar3].continent_cities[iVar6] != '\0') && (DAT_0063f660 < 0x18)) {
            if (DAT_006ad0d0 == '\0') {
              return 0;
            }
            uVar3 = thunk_FUN_00410030(s_SURPRISENOTHING_00634ce4,&DAT_0063fc58,0);
            return uVar3;
          }
        }
        else if (game.turn < 0x32) {
          uVar7 = _rand();
          uVar10 = (int)uVar7 >> 0x1f;
          if (((uVar7 ^ uVar10) - uVar10 & 1 ^ uVar10) == uVar10) goto LAB_0058f87c;
        }
      }
      if (0x31 < game.turn) {
        if (0x4a < game.turn) goto LAB_0058f939;
        uVar7 = _rand();
        uVar10 = (int)uVar7 >> 0x1f;
        if (((uVar7 ^ uVar10) - uVar10 & 1 ^ uVar10) != uVar10) goto LAB_0058f939;
      }
      bVar1 = true;
LAB_0058f939:
      uVar7 = 0;
      if (DAT_006ad0d0 != '\0') {
        uVar7 = thunk_FUN_00410030(s_SURPRISEBARB_00634cf4,&DAT_0063fc58,0);
      }
      local_10 = 0;
      do {
        if (7 < local_10) {
          return uVar7;
        }
        uVar7 = game.turn + local_10 >> 0x1f;
        iVar6 = ((game.turn + local_10 ^ uVar7) - uVar7 & 7 ^ uVar7) - uVar7;
        uVar8 = map_wrap_x((char)(&DAT_00628350)[iVar6] + iVar4);
        iVar6 = (int)(char)(&DAT_00628360)[iVar6] + uVar5;
        iVar9 = map_in_bounds(uVar8,iVar6);
        if ((((iVar9 != 0) && (iVar9 = tile_unit_owner(uVar8,iVar6), iVar9 < 0)) &&
            (iVar9 = tile_city_owner(uVar8,iVar6), iVar9 < 0)) &&
           (iVar9 = tile_is_ocean(uVar8,iVar6), iVar9 == 0)) {
          bVar2 = tile_terrain(uVar8,iVar6);
          local_28 = 5;
          local_3c = 0xf;
          if (game.advance_known_by[51] != '\0') {
            local_28 = 7;
            local_3c = 0x13;
          }
          if (game.advance_known_by[unit_types[22].prerequisite] != '\0') {
            local_28 = 0xb;
            local_3c = 0x15;
          }
          if (game.advance_known_by[34] != '\0') {
            local_28 = 8;
            local_3c = 9;
          }
          if ((char)terrain_types[(uint)bVar2].move_cost < '\x03') {
            local_38 = local_3c;
          }
          else {
            local_38 = local_28;
          }
          uVar7 = thunk_FUN_005b3d06(local_38,0,uVar8,iVar6);
          if (-1 < (int)uVar7) {
            iVar9 = tile_at(iVar4,uVar5);
            units[uVar7].visibility = *(byte *)(iVar9 + 4) | units[uVar7].visibility;
            thunk_FUN_0047cea6(uVar8,iVar6);
            uVar7 = (uint)game.multiplayer;
            if (2 < game.multiplayer) {
              uVar7 = thunk_FUN_0046b14d(0x72,0xff,uVar8,iVar6,0,0,0,0,0,0);
            }
          }
          if (bVar1) {
            return uVar7;
          }
        }
        uVar7 = thunk_FUN_005adfa0(4 - civs[uVar3].num_cities,1,4);
        local_10 = local_10 + uVar7;
      } while( true );
    case 4:
      if ((game.turn == 0) || (iVar6 = thunk_FUN_004bd9f0(uVar3,0x26), iVar6 != 0)) {
        local_50 = 2;
      }
      else {
        local_40 = 0;
        local_4c = _rand();
        local_4c = local_4c % 100;
        do {
          iVar6 = thunk_FUN_004bfdbe(uVar3,local_4c);
          if (iVar6 == 0) {
            uVar7 = (local_4c + 1) / 100;
            local_4c = (local_4c + 1) % 100;
          }
          else {
            if (DAT_006ad0d0 != '\0') {
              thunk_FUN_00410030(s_SURPRISESCROLLS_00634cc4,&DAT_0063fc58,0);
            }
            thunk_FUN_004bf05b(uVar3,local_4c,uVar3,0,0);   /* void */
            local_4c = -1;
          }
          local_40 = local_40 + 1;
        } while ((local_40 < 999) && (-1 < local_4c));
        if (local_4c < 0) {
          return uVar7;
        }
        local_50 = 0;
      }
      goto LAB_0058f1bc;
    case 5:
      if (game.advance_known_by[28] == '\0') {
        local_48 = 0;
        for (param_1 = 0; param_1 < game.num_units; param_1 = param_1 + 1) {
          if ((((units[param_1].id != 0) &&
               ((int)(char)units[param_1].owner == uVar3)) &&
              (unit_types[(uint)(byte)units[param_1].type].role == '\x05')) &&
             (units[param_1].home_city == -1)) {
            local_48 = local_48 + 1;
          }
        }
        if (local_48 <= (int)civs[uVar3].num_cities >> 3) {
          if (DAT_006ad0d0 != '\0') {
            thunk_FUN_00410030(s_SURPRISENOMADS_00634cb4,&DAT_0063fc58,0);
          }
          iVar6 = thunk_FUN_005b3d06(0,uVar3,iVar4,uVar5);
          if (-1 < iVar6) {
            units[iVar6].home_city = 0xff;
          }
          if (DAT_006ad0d0 == '\0') {
            return 0;
          }
          thunk_FUN_0047cf22(iVar4,uVar5);
          uVar3 = thunk_FUN_0046b14d(0x75,0xff,iVar4,uVar5,0,0,0,0,0,0);
          return uVar3;
        }
        local_50 = 4;
      }
      else {
        local_50 = 2;
      }
      goto LAB_0058f1bc;
    default:
      break;
    }
  }
  return local_50;
}
#undef DAT_006d1da0
#undef local_60
#undef local_50
#undef local_4c
#undef local_48
#undef local_40
#undef local_3c
#undef local_38
#undef local_28
#undef local_20
#undef local_14
#undef local_10
#undef local_c
#undef local_8

