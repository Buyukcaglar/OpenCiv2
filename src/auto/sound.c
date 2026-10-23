/* The game, sound, music and video: functions translated from the original
 * (tools/gen_c.py, now edited directly), in address order. */
#include "auto_common.h"

/* 00419c8b auto */
void __cdecl snd_menu_end(void)

{
  snd_play_effect(-0x6b,0,1,0);
  snd_play_effect(0x6c,0,0,0);
  return;
}

/* 0046dff0 auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall avi_player_set_end_callback(AviPlayerEndCbSetView *this,iptr param_1)

{
  *(iptr *)(this[3].pad_0 + 0x3c) = param_1;
  return;
}

/* 0046e020 auto */
#define local_118 (*(char (*)[16])(frame_ + FRAME_OFF(0)))
#define local_108 (*(char (*)[128])(frame_ + FRAME_OFF(16)))
#define local_88 (*(i8 (*)[128])(frame_ + FRAME_OFF(144)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(272)))
void __cdecl snd_play_effect(iptr param_1,iptr param_2,int param_3,iptr param_4)

{
  int iVar1;
  char *pcVar2;
  i8 frame_[FRAME_OFF(280)] __attribute__((aligned(8)));  /* original stack frame */
  
  snd_last_effect_id = param_1;
  snd_last_effect_arg = param_2;
  if (param_1 < 0) {
    snd_wave_free_by_id(~param_1 + 1);
  }
  else if ((((byte)game.game_options & 0x10) != 0) && (param_1 < 0x85)) {
    FUN_005f22d0(local_118,s_AIRCOMBT_0062af70 + param_1 * 9);
    iVar1 = _strcmp(local_118,s_CHEERS_0062b430);
    if (iVar1 == 0) {
      iVar1 = rand_range(0,2);
      str_append_int((iptr)local_118,iVar1 + 1);
    }
    FUN_005f22e0(local_118,&snd_wav_ext_str);
    str_clear((iptr)local_108);
    str_append((iptr)local_108,ADDR(0x62b440, ((u8 *)&g.d_0062b440)));
    str_append((iptr)local_108,(iptr)local_118);
    str_clear((iptr)local_88);
    str_append((iptr)local_88,ADDR(0x64bb08, ((u8 *)&g.d_0064bb08)));
    str_append((iptr)local_88,ADDR(0x62b44c, ((u8 *)&g.d_0062b44c)));
    str_append((iptr)local_88,(iptr)local_118);
    iVar1 = file_exists((iptr)local_88);
    if (iVar1 == 0) {
      pcVar2 = (char *)file_get_fallback_drive();
      iVar1 = file_resolve_path((iptr)local_108);
      if (iVar1 == 0) {
        return;
      }
      if ((pcVar2 != (char *)0x0) && (local_108[0] == *pcVar2)) {
        return;
      }
    }
    else {
      FUN_005f22d0(local_108,local_88);
    }
    local_8 = 3;
    if (param_2 == 0) {
      local_8 = 0x13;
    }
    if (param_3 != 0) {
      local_8 = local_8 | 8;
    }
    if (param_2 == 99) {
      sndPlaySoundA(local_108,local_8);
    }
    else {
      snd_wave_play((iptr)local_108,(param_3 == 0) - 1 & 8,param_1,param_4);
    }
    win_flush_pending_msgs();
  }
  return;
}
#undef local_118
#undef local_108
#undef local_88
#undef local_8

/* 0046e2f4 auto */
#define cd_music_available (*(i32 *)((u8 *)&g.d_0062b420))
#define cd_music_continue (*(int *)((u8 *)&g.d_0062b42c))
void __cdecl snd_cd_on_notify(void)

{
  cd_music_available = 1;
  if (cd_music_continue != 0) {
    snd_sync_music_option();
  }
  return;
}
#undef cd_music_available
#undef cd_music_continue

/* 0046e320 auto */
#define cd_music_available (*(i32 *)((u8 *)&g.d_0062b420))
#define cd_music_continue (*(i32 *)((u8 *)&g.d_0062b42c))
#define cd_music_current_track (*(uint *)((u8 *)&g.d_0062b428))
#define cd_music_unknown_disc (*(i32 *)((u8 *)&g.d_0062b424))
#define local_18 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(uint *)(frame_ + FRAME_OFF(8)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl snd_cd_play_random_track(void)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  while (local_8 < 10) {
    local_8++;
    local_c = snd_cd_get_track_count();
    if ((((local_c == 0x18) || (local_c == 0x12)) || (local_c == 0xc)) || (local_c == 10)) break;
  }
  if ((local_c == 1) || (local_c == -1)) {
    cd_music_available = 0;
  }
  else {
    while( true ) {
      if (((local_c == 10) || (local_c == 0x12)) || ((local_c == 0x18 || (local_c == 0xc)))) {
        if (local_c == 4 || local_c - 4 < 0) {
          local_18 = 0;
        }
        else {
          local_18 = _rand();
          local_18 = local_18 % (local_c - 3);
        }
        local_10 = local_18 + 4;
        cd_music_unknown_disc = 0;
      }
      else {
        if (local_c == 2 || local_c - 2 < 0) {
          local_14 = 0;
        }
        else {
          local_14 = _rand();
          local_14 = local_14 % (local_c - 1);
        }
        local_10 = local_14 + 2;
        cd_music_unknown_disc = 1;
      }
      if (local_10 != cd_music_current_track) break;
      cd_music_current_track = 0xffffffff;
    }
    cd_music_available = 0;
    cd_music_current_track = local_10;
    cd_music_continue = 1;
    snd_cd_play_track(local_10);
  }
  return;
}
#undef cd_music_available
#undef cd_music_continue
#undef cd_music_current_track
#undef cd_music_unknown_disc
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 0046e4a9 auto */
#define cd_music_available (*(i32 *)((u8 *)&g.d_0062b420))
#define cd_music_continue (*(i32 *)((u8 *)&g.d_0062b42c))
#define cd_music_unknown_disc (*(i32 *)((u8 *)&g.d_0062b424))
void __cdecl snd_cd_detect_layout(void)

{
  int iVar1;
  
  snd_cd_set_notify_callback(ADDR(0x403120, snd_cd_on_notify));
  iVar1 = snd_cd_get_track_count();
  if ((iVar1 == -1) || (iVar1 == 1)) {
    cd_music_available = 0;
  }
  else if ((iVar1 == 10) || (((iVar1 == 0x12 || (iVar1 == 0x18)) || (iVar1 == 0xc)))) {
    cd_music_continue = 1;
    cd_music_available = 1;
    cd_music_unknown_disc = 0;
  }
  else {
    cd_music_continue = 1;
    cd_music_available = 1;
    cd_music_unknown_disc = 1;
  }
  return;
}
#undef cd_music_available
#undef cd_music_continue
#undef cd_music_unknown_disc

/* 0046e571 auto */
#define cd_music_available (*(int *)((u8 *)&g.d_0062b420))
#define cd_music_continue (*(i32 *)((u8 *)&g.d_0062b42c))
#define cd_music_current_track (*(uint *)((u8 *)&g.d_0062b428))
#define cd_music_unknown_disc (*(int *)((u8 *)&g.d_0062b424))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl music_play_track(uint param_1,int param_2)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((byte)game.game_options & 8) == 0) {
    if (cd_music_available == 0) {
      snd_cd_stop();
    }
  }
  else if ((((cd_music_available != 0) || (param_2 != 0)) || (cd_music_current_track != param_1)) &&
          (cd_music_unknown_disc == 0)) {
    local_8 = 0;
    while (local_8 < 10) {
      local_8++;
      local_c = snd_cd_get_track_count();
      if (((local_c == 0x18) || (local_c == 0x12)) || ((local_c == 0xc || (local_c == 10)))) break;
    }
    if ((local_c == 1) || (local_c == -1)) {
      cd_music_available = 0;
    }
    else {
      cd_music_continue = 0;
      snd_cd_mci_stop();
      snd_cd_set_notify_callback(ADDR(0x403120, snd_cd_on_notify));
      snd_cd_play_track(param_1);
      cd_music_current_track = param_1;
      cd_music_continue = 1;
      cd_music_available = 0;
    }
  }
  return;
}
#undef cd_music_available
#undef cd_music_continue
#undef cd_music_current_track
#undef cd_music_unknown_disc
#undef local_c
#undef local_8

/* 0046e6a9 auto */
#define cd_music_available (*(i32 *)((u8 *)&g.d_0062b420))
void __cdecl snd_cd_stop(void)

{
  snd_cd_mci_stop();
  cd_music_available = 1;
  return;
}
#undef cd_music_available

/* 0046e6c8 auto */
#define cd_music_available (*(int *)((u8 *)&g.d_0062b420))
void __cdecl snd_sync_music_option(void)

{
  if (((byte)game.game_options & 8) == 0) {
    if (cd_music_available == 0) {
      snd_cd_stop();
    }
  }
  else if (cd_music_available != 0) {
    snd_cd_play_random_track();
  }
  return;
}
#undef cd_music_available

/* 00472910 auto */
void __thiscall avi_player_set_frame_callback(C_00472910 *this,iptr param_1,u32 param_2)

{
  this->on_frame = param_1;
  this->callback_frame = param_2;
  return;
}

/* 00472950: written by hand in src/game/regargs.c */

/* 004729ab: written by hand in src/game/regargs.c */

/* 004d8b20 auto */
AviPlayer * __thiscall avi_player_scalar_dtor(AviPlayer *this,uint param_1)

{
  avi_player_dtor(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 005d48d0 auto */
void __cdecl snd_shutdown(void)

{
  snd_wave_close_all();
  return;
}

/* 005d48f0 auto */
#define snd_wave_buffer_count (*(i32 *)((u8 *)&g.d_00638588))
#define snd_wave_max_buffers (*(i32 *)((u8 *)&g.d_00638584))
#define snd_wave_notify_hwnd (*(i32 *)((u8 *)&g.d_0063857c))
#define snd_wave_out_handle (*(i32 *)((u8 *)&g.d_00638578))
int __cdecl snd_wave_open(i32 param_1,i32 param_2,i32 param_3)

{
  int iVar1;
  
  snd_wave_notify_hwnd = param_1;
  snd_wave_open_buffer_bytes = param_2;
  snd_wave_max_buffers = param_3;
  snd_wave_buffer_count = param_3;
  iVar1 = snd_wave_open_device(param_1,0,ADDR(0x638578, ((u8 *)&g.d_00638578)));
  if (iVar1 == 0) {
    snd_wave_alloc_buffers(param_2,snd_wave_out_handle,param_3);
    iVar1 = 0;
  }
  return iVar1;
}
#undef snd_wave_buffer_count
#undef snd_wave_max_buffers
#undef snd_wave_notify_hwnd
#undef snd_wave_out_handle

/* 005d4965 auto */
#define snd_wave_out_handle (*(int *)((u8 *)&g.d_00638578))
void __cdecl snd_wave_close_all(void)

{
  if (snd_wave_out_handle != 0) {
    snd_wave_reset_all(snd_wave_out_handle);
    snd_wave_close_device(snd_wave_out_handle);
  }
  return;
}
#undef snd_wave_out_handle

/* 005d49a3 auto */
void __cdecl snd_show_error(int param_1)

{
  if (param_1 == 10) {
    MessageBoxA((HWND)0x0,s_This_Sound_format_is_not_support_006385e4,s_Sound_Error_006385d8,0x40);
  }
  else if (param_1 != 0xb) {
    MessageBoxA((HWND)0x0,s_Undefined_Sound_Error_00638614,s_Sound_Error_00638608,0x40);
  }
  return;
}

/* 005d4a11 auto */
#define snd_wave_block_align (*(i32 *)((u8 *)&g.d_006385ac))
#define snd_wave_format (*(i32 *)((u8 *)&g.d_006385a0))
#define snd_wave_out_handle (*(i32 *)((u8 *)&g.d_00638578))
#define local_14 (*(UINT *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(UINT_PTR *)(frame_ + FRAME_OFF(8)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(16)))
uint __cdecl snd_wave_open_device(DWORD_PTR param_1,i32 *param_2,iptr param_3)

{
  bool bVar1;
  UINT UVar2;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  bVar1 = false;
  if (snd_wave_device_open == 0) {
    if (param_2 != (i32 *)0x0) {
      snd_wave_format = *param_2;
      snd_wave_samples_per_sec = param_2[1];
      snd_wave_avg_bytes_per_sec = param_2[2];
      snd_wave_block_align = param_2[3];
    }
    UVar2 = waveOutGetNumDevs();
    for (local_10 = 0; (int)local_10 < (int)UVar2; local_10++) {
      waveOutGetDevCapsA(local_10,(LPWAVEOUTCAPSA)&snd_wave_dev_caps,0x34);
      if ((snd_wave_dev_formats & 0x20) != 0) {
        bVar1 = false;
        local_14 = local_10;
        break;
      }
      if ((snd_wave_dev_formats & 0x10) != 0) {
        local_14 = local_10;
        bVar1 = true;
      }
    }
    if ((bVar1) || (local_10 != UVar2)) {
      if (bVar1) {
        snd_wave_format = CONCAT22(1,(i16)snd_wave_format);
        snd_wave_avg_bytes_per_sec = 0x5622;
        snd_wave_block_align = CONCAT22((*(i16 *)((char *)&snd_wave_block_align + 2)),1);
      }
      local_8 = waveOutOpen((LPHWAVEOUT)&snd_wave_out_handle,local_14,(LPCWAVEFORMATEX)&snd_wave_format,
                            param_1,0,0x10000);
      if ((short)local_8 != 0) {
        sndPlaySoundA((LPCSTR)0x0,0);
        local_8 = waveOutOpen((LPHWAVEOUT)&snd_wave_out_handle,local_14,(LPCWAVEFORMATEX)&snd_wave_format,
                              param_1,0,0x10000);
      }
      local_8 = local_8 & 0xffff;
      if ((local_8 == 0) && (snd_wave_device_open = 1, param_3 != 0)) {
        *(i32 *)param_3 = snd_wave_out_handle;
      }
    }
    else {
      snd_show_error(0xb);
      local_8 = 0xb;
    }
  }
  else {
    local_8 = 0;
  }
  return local_8;
}
#undef snd_wave_block_align
#undef snd_wave_format
#undef snd_wave_out_handle
#undef local_14
#undef local_10
#undef local_8

/* 005d4bcb auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
uint __cdecl snd_wave_close_device(HWAVEOUT param_1)

{
  MMRESULT MVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  if (snd_wave_device_open != 0) {
    MVar1 = waveOutClose(param_1);
    local_8 = MVar1 & 0xffff;
  }
  snd_wave_device_open = 0;
  return local_8;
}
#undef local_8

/* 005d4c18 auto */
#define local_cc (*(CHAR (*)[200])(frame_ + FRAME_OFF(4)))
void __cdecl snd_waveout_error_box(uint param_1)

{
  i8 frame_[FRAME_OFF(208)] __attribute__((aligned(8)));  /* original stack frame */
  
  waveOutGetErrorTextA(param_1 & 0xffff,local_cc,200);
  MessageBoxA((HWND)0x0,local_cc,s_Wave_Out_Error_0063862c,0x40);
  return;
}
#undef local_cc

/* 005d4c5f auto */
#define snd_wave_total_buffer_bytes (*(LONG *)((u8 *)&g.d_006385cc))
#define local_98 (*(_MMCKINFO *)(frame_ + FRAME_OFF(0)))
#define local_84 (*(_MMIOINFO *)(frame_ + FRAME_OFF(20)))
#define local_3c (*(iptr *)(frame_ + FRAME_OFF(92)))
#define local_38 (*(DWORD *)(frame_ + FRAME_OFF(96)))
#define local_34 (*(FOURCC * *)(frame_ + FRAME_OFF(100)))
#define local_30 (*(HGLOBAL *)(frame_ + FRAME_OFF(104)))
#define local_2c (*(FOURCC *)(frame_ + FRAME_OFF(108)))
#define local_28 (*(FOURCC *)(frame_ + FRAME_OFF(112)))
#define local_24 (*(FOURCC *)(frame_ + FRAME_OFF(116)))
#define local_20 (*(i32 *)(frame_ + FRAME_OFF(120)))
#define local_1c (*(_MMCKINFO *)(frame_ + FRAME_OFF(124)))
#define local_8 (*(HMMIO *)(frame_ + FRAME_OFF(144)))
i16 __cdecl snd_wave_load_file(LPSTR param_1,i32 param_2,i32 param_3,FOURCC param_4)

{
  i16 uVar1;
  MMRESULT MVar2;
  DWORD DVar3;
  int iVar4;
  _MMIOINFO *p_Var5;
  _MMCKINFO *p_Var6;
  DWORD *pDVar7;
  FOURCC *pFVar8;
  i8 frame_[FRAME_OFF(152)] __attribute__((aligned(8)));  /* original stack frame */
  
  _memset(&local_84,0,0x48);
  local_84.cchBuffer = snd_wave_total_buffer_bytes;
  local_8 = mmioOpenA(param_1,&local_84,0x10000);
  if (local_8 == (HMMIO)0x0) {
    uVar1 = 7;
  }
  else {
    local_1c.fccType = 0x45564157;
    MVar2 = mmioDescend(local_8,&local_1c,(MMCKINFO *)0x0,0x20);
    if (MVar2 == 0) {
      local_98.ckid = 0x20746d66;
      MVar2 = mmioDescend(local_8,&local_98,&local_1c,0x10);
      if (MVar2 == 0) {
        local_38 = local_98.cksize;
        DVar3 = mmioRead(local_8,(HPSTR)&local_2c,local_98.cksize);
        if (DVar3 == local_38) {
          if ((local_28 == 0x5622) && ((*(i16 *)((char *)&local_20 + 2)) == 8)) {
            mmioAscend(local_8,&local_98,0);
            local_98.ckid = 0x61746164;
            MVar2 = mmioDescend(local_8,&local_98,&local_1c,0x10);
            if (MVar2 == 0) {
              mmioGetInfo(local_8,&local_84,0);
              mmioAdvance(local_8,&local_84,0);
              local_30 = GlobalAlloc(0x2002,0xbc);
              if (local_30 == (HGLOBAL)0x0) {
                mmioClose(local_8,0);
                uVar1 = 2;
              }
              else {
                local_34 = GlobalLock(local_30);
                if (local_34 == (FOURCC *)0x0) {
                  mmioClose(local_8,0);
                  GlobalFree(local_30);
                  uVar1 = 2;
                }
                else {
                  _memset(local_34,0,0xbc);
                  local_34[0x1b] = (FOURCC)local_30;
                  *local_34 = (FOURCC)local_8;
                  p_Var5 = &local_84;
                  pDVar7 = local_34 + 6;
                  for (iVar4 = 0x12; iVar4 != 0; iVar4--) {
                    *pDVar7 = p_Var5->dwFlags;
                    p_Var5 = (_MMIOINFO *)&p_Var5->fccIOProc;
                    pDVar7++;
                  }
                  p_Var6 = &local_98;
                  pFVar8 = local_34;
                  for (iVar4 = 5; pFVar8 = pFVar8 + 1, iVar4 != 0; iVar4--) {
                    *pFVar8 = p_Var6->ckid;
                    p_Var6 = (_MMCKINFO *)&p_Var6->cksize;
                  }
                  *(i16 *)((int)local_34 + 0x8a) = (i16)param_3;
                  local_34[0x1d] = local_2c;
                  local_34[0x1e] = local_28;
                  local_34[0x1f] = local_24;
                  local_34[0x20] = local_20;
                  *(i16 *)(local_34 + 0x22) = 1;
                  local_34[0x2d] = param_4;
                  if (snd_wave_sources == 0) {
                    snd_wave_sources = (iptr)local_34;
                  }
                  else {
                    for (local_3c = snd_wave_sources; *(int *)(local_3c + 0xb8) != 0;
                        local_3c = *(iptr *)(local_3c + 0xb8)) {
                    }
                    *(FOURCC **)(local_3c + 0xb8) = local_34;
                  }
                  uVar1 = 0;
                }
              }
            }
            else {
              mmioClose(local_8,0);
              uVar1 = 8;
            }
          }
          else {
            snd_show_error(10);
            mmioClose(local_8,0);
            uVar1 = 10;
          }
        }
        else {
          mmioClose(local_8,0);
          uVar1 = 8;
        }
      }
      else {
        mmioClose(local_8,0);
        uVar1 = 8;
      }
    }
    else {
      mmioClose(local_8,0);
      uVar1 = 8;
    }
  }
  return uVar1;
}
#undef snd_wave_total_buffer_bytes
#undef local_98
#undef local_84
#undef local_3c
#undef local_38
#undef local_34
#undef local_30
#undef local_2c
#undef local_28
#undef local_24
#undef local_20
#undef local_1c
#undef local_8

/* 005d4f6a auto */
#define snd_wave_total_buffer_bytes (*(LONG *)((u8 *)&g.d_006385cc))
#define local_9c (*(_MMCKINFO *)(frame_ + FRAME_OFF(4)))
#define local_88 (*(_MMIOINFO *)(frame_ + FRAME_OFF(24)))
#define local_40 (*(iptr *)(frame_ + FRAME_OFF(96)))
#define local_3c (*(DWORD *)(frame_ + FRAME_OFF(100)))
#define local_38 (*(FOURCC * *)(frame_ + FRAME_OFF(104)))
#define local_34 (*(HGLOBAL *)(frame_ + FRAME_OFF(108)))
#define local_30 (*(FOURCC *)(frame_ + FRAME_OFF(112)))
#define local_2c (*(FOURCC *)(frame_ + FRAME_OFF(116)))
#define local_28 (*(FOURCC *)(frame_ + FRAME_OFF(120)))
#define local_24 (*(i32 *)(frame_ + FRAME_OFF(124)))
#define local_20 (*(_MMCKINFO *)(frame_ + FRAME_OFF(128)))
#define local_c (*(HMMIO *)(frame_ + FRAME_OFF(148)))
#define local_8 (*(HMMIO *)(frame_ + FRAME_OFF(152)))
i16 __cdecl snd_wave_open_stream(LPSTR param_1,i32 param_2,i32 param_3)

{
  i16 uVar1;
  MMRESULT MVar2;
  DWORD DVar3;
  int iVar4;
  _MMIOINFO *p_Var5;
  _MMCKINFO *p_Var6;
  DWORD *pDVar7;
  FOURCC *pFVar8;
  i8 frame_[FRAME_OFF(160)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = mmioOpenA(param_1,(LPMMIOINFO)0x0,0);
  if (local_c == (HMMIO)0x0) {
    uVar1 = 7;
  }
  else {
    local_20.fccType = 0x45564157;
    MVar2 = mmioDescend(local_c,&local_20,(MMCKINFO *)0x0,0x20);
    if (MVar2 == 0) {
      local_9c.ckid = 0x20746d66;
      MVar2 = mmioDescend(local_c,&local_9c,&local_20,0x10);
      if (MVar2 == 0) {
        local_3c = local_9c.cksize;
        DVar3 = mmioRead(local_c,(HPSTR)&local_30,local_9c.cksize);
        if (DVar3 == local_3c) {
          if ((local_2c == 0x5622) && ((*(i16 *)((char *)&local_24 + 2)) == 8)) {
            mmioAscend(local_c,&local_9c,0);
            local_9c.ckid = 0x61746164;
            MVar2 = mmioDescend(local_c,&local_9c,&local_20,0x10);
            if (MVar2 == 0) {
              _memset(&local_88,0,0x48);
              local_88.cchBuffer = snd_wave_total_buffer_bytes;
              local_88.fccIOProc = 0x204d454d;
              local_88.adwInfo[0] = 0;
              local_8 = mmioOpenA((LPSTR)0x0,&local_88,0x11002);
              if (local_8 == (HMMIO)0x0) {
                uVar1 = 7;
              }
              else {
                mmioGetInfo(local_8,&local_88,0);
                local_34 = GlobalAlloc(0x2002,0xbc);
                if (local_34 == (HGLOBAL)0x0) {
                  uVar1 = 2;
                }
                else {
                  local_38 = GlobalLock(local_34);
                  if (local_38 == (FOURCC *)0x0) {
                    GlobalFree(local_34);
                    uVar1 = 2;
                  }
                  else {
                    _memset(local_38,0,0xbc);
                    local_38[0x1b] = (FOURCC)local_34;
                    *(i16 *)(local_38 + 0x22) = 1;
                    local_38[0x1d] = local_30;
                    local_38[0x1e] = local_2c;
                    local_38[0x1f] = local_28;
                    local_38[0x20] = local_24;
                    *local_38 = (FOURCC)local_8;
                    local_38[0x18] = (FOURCC)local_c;
                    p_Var5 = &local_88;
                    pDVar7 = local_38 + 6;
                    for (iVar4 = 0x12; iVar4 != 0; iVar4--) {
                      *pDVar7 = p_Var5->dwFlags;
                      p_Var5 = (_MMIOINFO *)&p_Var5->fccIOProc;
                      pDVar7++;
                    }
                    p_Var6 = &local_9c;
                    pFVar8 = local_38;
                    for (iVar4 = 5; pFVar8 = pFVar8 + 1, iVar4 != 0; iVar4--) {
                      *pFVar8 = p_Var6->ckid;
                      p_Var6 = (_MMCKINFO *)&p_Var6->cksize;
                    }
                    local_38[0x1c] = local_38[0x1c] | 4;
                    *(i16 *)((int)local_38 + 0x8a) = (i16)param_3;
                    snd_wave_stream_refill((iptr)local_38);
                    if (snd_wave_sources == 0) {
                      snd_wave_sources = (iptr)local_38;
                    }
                    else {
                      for (local_40 = snd_wave_sources; *(int *)(local_40 + 0xb8) != 0;
                          local_40 = *(iptr *)(local_40 + 0xb8)) {
                      }
                      *(FOURCC **)(local_40 + 0xb8) = local_38;
                    }
                    uVar1 = 0;
                  }
                }
              }
            }
            else {
              mmioClose(local_c,0);
              uVar1 = 8;
            }
          }
          else {
            snd_show_error(10);
            mmioClose(local_c,0);
            uVar1 = 10;
          }
        }
        else {
          mmioClose(local_c,0);
          uVar1 = 8;
        }
      }
      else {
        mmioClose(local_c,0);
        uVar1 = 8;
      }
    }
    else {
      mmioClose(local_c,0);
      uVar1 = 8;
    }
  }
  return uVar1;
}
#undef snd_wave_total_buffer_bytes
#undef local_9c
#undef local_88
#undef local_40
#undef local_3c
#undef local_38
#undef local_34
#undef local_30
#undef local_2c
#undef local_28
#undef local_24
#undef local_20
#undef local_c
#undef local_8

/* 005d52a2 auto */
#define snd_wave_format (*(i8 *)((u8 *)&g.d_006385a0))
#define snd_wave_max_buffers (*(uint *)((u8 *)&g.d_00638584))
#define snd_wave_out_handle (*(int *)((u8 *)&g.d_00638578))
#define snd_wave_source_count (*(short *)((u8 *)&g.d_0063858c))
#define snd_wave_total_buffer_bytes (*(uint *)((u8 *)&g.d_006385cc))
#define local_10c (*(_MMIOINFO *)(frame_ + FRAME_OFF(4)))
#define local_c4 (*(i32 *)(frame_ + FRAME_OFF(76)))
#define local_c0 (*(i32 *)(frame_ + FRAME_OFF(80)))
#define local_bc (*(i32 *)(frame_ + FRAME_OFF(84)))
#define local_b8 (*(i32 *)(frame_ + FRAME_OFF(88)))
#define local_b4 (*(i32 * *)(frame_ + FRAME_OFF(92)))
#define local_b0 (*(HGLOBAL *)(frame_ + FRAME_OFF(96)))
#define local_ac (*(i8 (*)[4])(frame_ + FRAME_OFF(100)))
#define local_a8 (*(uint *)(frame_ + FRAME_OFF(104)))
#define local_a4 (*(int *)(frame_ + FRAME_OFF(108)))
#define local_a0 (*(i32 *)(frame_ + FRAME_OFF(112)))
#define local_9c (*(uint *)(frame_ + FRAME_OFF(116)))
#define local_98 (*(int (*)[8])(frame_ + FRAME_OFF(120)))
#define local_78 (*(int *)(frame_ + FRAME_OFF(152)))
#define local_68 (*(int *)(frame_ + FRAME_OFF(168)))
#define local_c (*(HMMIO *)(frame_ + FRAME_OFF(260)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(264)))
i32 __cdecl snd_wave_add_avi_stream(int param_1)

{
  i32 uVar1;
  int iVar2;
  _MMIOINFO *p_Var3;
  DWORD *pDVar4;
  i8 frame_[FRAME_OFF(272)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_a0 = 0xe;
  if (snd_wave_out_handle == 0) {
    uVar1 = 3;
  }
  else if (param_1 == 0) {
    uVar1 = 0xc;
  }
  else if ((snd_wave_sources == 0) || (*(short *)(snd_wave_sources + 0x88) != 4)) {
    AVIStreamInfoA(param_1,local_98,0x8c);
    if (local_98[0] == 0x73647561) {
      AVIStreamRead(param_1,0,1,0,0,local_ac,0);
      local_a4 = local_68 * local_78;
      AVIStreamReadFormat(param_1,0,&local_c4,&local_a0);
      if ((*(i16 *)((char *)&snd_wave_format + 2)) == 1) {
        if ((*(i16 *)((char *)&local_c4 + 2)) == 2) {
          local_8 = CONCAT22((*(i16 *)((char *)&local_8 + 2)),1);
        }
        else {
          local_8 = CONCAT22((*(i16 *)((char *)&local_8 + 2)),2);
        }
      }
      else if ((*(i16 *)((char *)&local_c4 + 2)) == 2) {
        local_8 = (uint)(*(i16 *)((char *)&local_8 + 2)) << 0x10;
      }
      else {
        local_8 = CONCAT22((*(i16 *)((char *)&local_8 + 2)),3);
      }
      _memset(&local_10c,0,0x48);
      if ((local_8 & 0xffff) == 1) {
        local_10c.cchBuffer = snd_wave_total_buffer_bytes * 2;
      }
      else if ((local_8 & 0xffff) == 3) {
        local_10c.cchBuffer = snd_wave_total_buffer_bytes >> 1;
      }
      else {
        local_10c.cchBuffer = snd_wave_total_buffer_bytes;
      }
      local_a8 = (uint)local_10c.cchBuffer / snd_wave_max_buffers;
      local_10c.fccIOProc = 0x204d454d;
      local_10c.adwInfo[0] = 0;
      local_c = mmioOpenA((LPSTR)0x0,&local_10c,0x11002);
      if (local_c == (HMMIO)0x0) {
        uVar1 = 7;
      }
      else {
        mmioGetInfo(local_c,&local_10c,0);
        local_b0 = GlobalAlloc(0x2002,0xbc);
        if (local_b0 == (HGLOBAL)0x0) {
          uVar1 = 2;
        }
        else {
          local_b4 = GlobalLock(local_b0);
          if (local_b4 == (i32 *)0x0) {
            GlobalFree(local_b0);
            uVar1 = 2;
          }
          else {
            _memset(local_b4,0,0xbc);
            local_b4[0x1b] = local_b0;
            *(i16 *)(local_b4 + 0x22) = 4;
            local_b4[0x1d] = local_c4;
            local_b4[0x1e] = local_c0;
            local_b4[0x1f] = local_bc;
            local_b4[0x20] = local_b8;
            *local_b4 = local_c;
            p_Var3 = &local_10c;
            pDVar4 = local_b4 + 6;
            for (iVar2 = 0x12; iVar2 != 0; iVar2--) {
              *pDVar4 = p_Var3->dwFlags;
              p_Var3 = (_MMIOINFO *)&p_Var3->fccIOProc;
              pDVar4++;
            }
            local_b4[1] = local_98[0];
            local_b4[2] = local_a4;
            local_b4[0x21] = param_1;
            local_b4[0x1c] = local_b4[0x1c] | 2;
            local_b4[0x27] = local_a8;
            for (local_9c = local_10c.cchBuffer; 1 < local_9c; local_9c = local_9c >> 1) {
              local_b4[0x2a] = local_b4[0x2a] << 1;
              local_b4[0x2a]++;
            }
            local_b4[0x2e] = snd_wave_sources;
            snd_wave_sources = (iptr)local_b4;
            snd_wave_source_count++;
            uVar1 = 0;
          }
        }
      }
    }
    else {
      uVar1 = 9;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}
#undef snd_wave_format
#undef snd_wave_max_buffers
#undef snd_wave_out_handle
#undef snd_wave_source_count
#undef snd_wave_total_buffer_bytes
#undef local_10c
#undef local_c4
#undef local_c0
#undef local_bc
#undef local_b8
#undef local_b4
#undef local_b0
#undef local_ac
#undef local_a8
#undef local_a4
#undef local_a0
#undef local_9c
#undef local_98
#undef local_78
#undef local_68
#undef local_c
#undef local_8

/* 005d5643: written by hand in src/game/sound_position.c */

/* 005d5706: written by hand in src/game/sound_position.c */

/* 005d57b1 auto */
#define snd_avi_stream_started (*(int *)((u8 *)&g.d_006385bc))
#define snd_wave_out_handle (*(int *)((u8 *)&g.d_00638578))
#define _DAT_00638590 (*(i32 *)((u8 *)&g.d_00638590))
#define _DAT_00638594 (*(i32 *)((u8 *)&g.d_00638594))
#define _DAT_00638598 (*(i32 *)((u8 *)&g.d_00638598))
#define local_24 (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_20 (*(uint *)(frame_ + FRAME_OFF(8)))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(28)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(32)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __cdecl snd_avi_stream_feed(uint param_1)

{
  i32 uVar1;
  uint uVar2;
  iptr iVar1;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = snd_wave_sources;
  if (snd_wave_out_handle == 0) {
    uVar1 = 3;
  }
  else if (snd_avi_stream_started == 0) {
    uVar1 = 0xe;
  }
  else if ((snd_wave_sources == 0) || (*(short *)(snd_wave_sources + 0x88) != 4)) {
    uVar1 = 5;
  }
  else if ((*(byte *)(snd_wave_sources + 0x70) & 1) == 0) {
    if ((*(uint *)(*(int *)(snd_wave_sources + 0x98) + 0xc) >> 3 & 1) == 0) {
      if (((*(uint *)(*(int *)(snd_wave_sources + 0x98) + 0xc) >> 7) -
           (*(uint *)(snd_wave_cur_buffer + 0xc) >> 7) & 7) == 0) {
        param_1 = (uint)(*(int *)(snd_wave_sources + 0x9c) - *(int *)(snd_wave_sources + 0x68)) /
                  (uint)*(ushort *)(snd_wave_sources + 0x80);
        _DAT_00638594++;
      }
      local_c = *(int *)(snd_wave_sources + 0x98);
      uVar2 = (*(int *)(snd_wave_sources + 0x3c) - *(int *)(snd_wave_sources + 0x34)) /
              (int)(uint)*(ushort *)(snd_wave_sources + 0x80);
      if (uVar2 < param_1) {
        param_1 = uVar2;
      }
      local_24 = *(ushort *)(snd_wave_sources + 0x80) * param_1;
      uVar2 = *(int *)(snd_wave_sources + 0x9c) - *(int *)(snd_wave_sources + 0x68);
      _DAT_00638598 = param_1;
      if (uVar2 < local_24) {
        local_24 = uVar2;
      }
      uVar2 = *(int *)(snd_wave_sources + 8) -
              (*(int *)(snd_wave_sources + 0x90) - *(int *)(snd_wave_sources + 0x94));
      if (uVar2 < local_24) {
        local_24 = uVar2;
      }
      local_8 = 0;
      AVIStreamRead(*(i32 *)(snd_wave_sources + 0x84),
                    *(uint *)(snd_wave_sources + 0x90) / (uint)*(ushort *)(snd_wave_sources + 0x80),
                    local_24 / *(ushort *)(snd_wave_sources + 0x80),
                    *(i32 *)(snd_wave_sources + 0x34),local_24,&local_8,0);
      *(int *)(snd_wave_sources + 0x90) = *(int *)(snd_wave_sources + 0x90) + local_8;
      *(int *)(iVar1 + 0x34) = *(int *)(iVar1 + 0x34) + local_8;
      if (*(int *)(iVar1 + 0x3c) == *(int *)(iVar1 + 0x34)) {
        *(i32 *)(iVar1 + 0x34) = *(i32 *)(iVar1 + 0x30);
      }
      *(int *)(snd_wave_sources + 0x68) = *(int *)(snd_wave_sources + 0x68) + local_8;
      if (*(uint *)(snd_wave_sources + 0x9c) <= *(uint *)(snd_wave_sources + 0x68)) {
        *(uint *)(local_c + 0xc) = *(uint *)(local_c + 0xc) | 8;
        *(i32 *)(snd_wave_sources + 0x98) = *(i32 *)(local_c + 0x1c);
        local_c = *(iptr *)(snd_wave_sources + 0x98);
        *(i32 *)(snd_wave_sources + 0x68) = 0;
      }
      if (*(uint *)(snd_wave_sources + 8) <=
          (uint)(*(int *)(snd_wave_sources + 0x90) - *(int *)(snd_wave_sources + 0x94))) {
        for (local_20 = 0;
            local_20 < (uint)(*(int *)(snd_wave_sources + 0x9c) - *(int *)(snd_wave_sources + 0x68));
            local_20 = local_20 + 1) {
          **(i8 **)(iVar1 + 0x34) = 0x80;
          *(int *)(iVar1 + 0x34) = *(int *)(iVar1 + 0x34) + 1;
        }
        if (*(int *)(iVar1 + 0x3c) == *(int *)(iVar1 + 0x34)) {
          *(i32 *)(iVar1 + 0x34) = *(i32 *)(iVar1 + 0x30);
        }
        *(uint *)(local_c + 0xc) = *(uint *)(local_c + 0xc) | 8;
        *(uint *)(local_c + 0xc) = *(uint *)(local_c + 0xc) | 2;
        *(i32 *)(snd_wave_sources + 0x98) = *(i32 *)(local_c + 0x1c);
        *(i32 *)(snd_wave_sources + 0x68) = 0;
        *(uint *)(snd_wave_sources + 0x70) = *(uint *)(snd_wave_sources + 0x70) | 1;
      }
      _DAT_00638590++;
      uVar1 = 0;
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 0xe;
  }
  return uVar1;
}
#undef snd_avi_stream_started
#undef snd_wave_out_handle
#undef _DAT_00638590
#undef _DAT_00638594
#undef _DAT_00638598
#undef local_24
#undef local_20
#undef local_c
#undef local_8

/* 005d5b88 auto */
#define snd_avi_stream_started (*(i32 *)((u8 *)&g.d_006385bc))
i32 __cdecl snd_avi_stream_stop(void)

{
  i32 uVar1;
  
  snd_avi_stream_started = 0;
  if ((snd_wave_sources == 0) || (*(short *)(snd_wave_sources + 0x88) != 4)) {
    uVar1 = 5;
  }
  else {
    snd_wave_sources = snd_wave_free(0,snd_wave_sources);
    uVar1 = 0;
  }
  return uVar1;
}
#undef snd_avi_stream_started

/* 005d5bec auto */
#define local_10 (*(uint *)(frame_ + FRAME_OFF(0)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl snd_avi_stream_refill(iptr param_1)

{
  uint uVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  if ((*(int *)(param_1 + 0x3c) == *(int *)(param_1 + 0x34)) ||
     (*(int *)(param_1 + 0x30) == *(int *)(param_1 + 0x34))) {
    uVar1 = *(int *)(snd_wave_sources + 8) -
            (*(int *)(snd_wave_sources + 0x90) - *(int *)(snd_wave_sources + 0x94));
    local_10 = *(uint *)(param_1 + 0x2c);
    if (uVar1 < *(uint *)(param_1 + 0x2c)) {
      local_10 = uVar1;
    }
    *(i32 *)(param_1 + 0x34) = *(i32 *)(param_1 + 0x30);
    AVIStreamRead(*(i32 *)(param_1 + 0x84),
                  *(uint *)(param_1 + 0x90) / (uint)*(ushort *)(param_1 + 0x80),
                  local_10 / *(ushort *)(param_1 + 0x80),*(i32 *)(param_1 + 0x34),local_10,
                  &local_8,0);
    *(int *)(param_1 + 0x90) = *(int *)(param_1 + 0x90) + local_8;
    iVar2 = *(int *)(param_1 + 0x2c) - local_8;
    if (iVar2 != 0) {
      snd_fill_silence_u8(*(int *)(param_1 + 0x34) + local_8,iVar2);
    }
  }
  return;
}
#undef local_10
#undef local_8

/* 005d5d11 auto */
#define snd_avi_stream_started (*(i32 *)((u8 *)&g.d_006385bc))
#define snd_wave_buffer_count (*(uint *)((u8 *)&g.d_00638588))
#define snd_wave_max_buffers (*(uint *)((u8 *)&g.d_00638584))
#define snd_wave_out_handle (*(int *)((u8 *)&g.d_00638578))
#define local_10 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_c (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 * *)(frame_ + FRAME_OFF(8)))
i32 __cdecl snd_avi_stream_prepare(i32 param_1,i32 param_2,iptr param_3)

{
  i32 uVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (snd_wave_out_handle == 0) {
    uVar1 = 3;
  }
  else if ((snd_wave_sources == 0) || (*(short *)(snd_wave_sources + 0x88) != 4)) {
    uVar1 = 5;
  }
  else {
    if (snd_wave_buffer_count != snd_wave_max_buffers) {
      snd_wave_set_buffer_count(snd_wave_max_buffers);
    }
    iVar2 = AVIStreamTimeToSample(*(i32 *)(snd_wave_sources + 0x84),param_1);
    local_10 = AVIStreamTimeToSample(*(i32 *)(snd_wave_sources + 0x84),param_2);
    local_10 = (uint)*(ushort *)(snd_wave_sources + 0x80) * local_10;
    iVar2 = (uint)*(ushort *)(snd_wave_sources + 0x80) * iVar2;
    if (local_10 == 0) {
      local_10 = *(int *)(snd_wave_sources + 8) - iVar2;
    }
    else {
      local_10 -= iVar2;
    }
    if (local_10 < 0) {
      uVar1 = 0xc;
    }
    else {
      snd_wave_stop_all();
      *(int *)(snd_wave_sources + 8) = local_10;
      *(int *)(snd_wave_sources + 0x90) = iVar2;
      *(int *)(snd_wave_sources + 0x94) = iVar2;
      *(i32 *)(snd_wave_sources + 100) = 0;
      *(i32 *)(snd_wave_sources + 0x68) = 0;
      *(i32 *)(snd_wave_sources + 0x34) = *(i32 *)(snd_wave_sources + 0x3c);
      snd_avi_stream_refill(snd_wave_sources);
      *(uint *)(snd_wave_sources + 0x70) = *(uint *)(snd_wave_sources + 0x70) & 0xfffffffd;
      *(uint *)(snd_wave_sources + 0x70) = *(uint *)(snd_wave_sources + 0x70) & 0xfffffffe;
      *(iptr *)(snd_wave_sources + 0x8c) = param_3;
      snd_avi_stream_started = 0;
      local_8 = (i32 *)snd_wave_buffer_ring;
      for (local_c = 0; local_c < snd_wave_max_buffers; local_c++) {
        local_8[3] = local_8[3] & 0xffffffdf;
        local_8[3] = local_8[3] & 0xfffffffe;
        local_8[3] = local_8[3] & 0xfffffffd;
        local_8[3] = local_8[3] & 0xffffffef;
        local_8[3] = local_8[3] & 0xffffffdf;
        local_8[3] = local_8[3] & 0xffffffbf;
        local_8[4] = *(i32 *)*local_8;
        iVar2 = snd_wave_mix_buffer(*local_8);
        if (iVar2 == 1) break;
        local_8 = (i32 *)local_8[7];
      }
      snd_avi_stream_refill(snd_wave_sources);
      local_8 = (i32 *)snd_wave_buffer_ring;
      for (local_c = 0; local_c < snd_wave_max_buffers; local_c++) {
        *(uint *)((int)local_8 + 0xc) = *(uint *)((int)local_8 + 0xc) | 8;
        local_8 = *(i32 **)((int)local_8 + 0x1c);
      }
      snd_wave_cur_buffer = snd_wave_buffer_ring;
      uVar1 = 0;
    }
  }
  return uVar1;
}
#undef snd_avi_stream_started
#undef snd_wave_buffer_count
#undef snd_wave_max_buffers
#undef snd_wave_out_handle
#undef local_10
#undef local_c
#undef local_8

/* 005d5f91 auto */
#define snd_avi_stream_started (*(i32 *)((u8 *)&g.d_006385bc))
i16 __cdecl snd_avi_stream_start(void)

{
  iptr iVar1;
  
  if ((snd_wave_sources != 0) && (*(short *)(snd_wave_sources + 0x88) == 4)) {
    snd_wave_write_pending(snd_wave_buffer_ring);
    *(uint *)(snd_wave_sources + 0x70) = *(uint *)(snd_wave_sources + 0x70) | 0x10;
    if (*(int *)(snd_wave_sources + 0x8c) != 0) {
      **(ushort **)(snd_wave_sources + 0x8c) = **(ushort **)(snd_wave_sources + 0x8c) | 4;
    }
  }
  iVar1 = snd_wave_buffer_ring;
  snd_avi_stream_started = 1;
  *(iptr *)(snd_wave_sources + 0x98) = snd_wave_buffer_ring;
  return (short)iVar1;
}
#undef snd_avi_stream_started

/* 005d6038 auto */
#define snd_wave_buffer_count (*(uint *)((u8 *)&g.d_00638588))
#define snd_wave_max_buffers (*(i32 *)((u8 *)&g.d_00638584))
#define snd_wave_notify_hwnd (*(i32 *)((u8 *)&g.d_0063857c))
#define snd_wave_out_handle (*(int *)((u8 *)&g.d_00638578))
#define snd_wave_source_count (*(ushort *)((u8 *)&g.d_0063858c))
#define local_10 (*(uint *)(frame_ + FRAME_OFF(0)))
#define local_8 (*(i32 * *)(frame_ + FRAME_OFF(8)))
short __cdecl snd_wave_play(iptr param_1,uint param_2,i32 param_3,i32 param_4)

{
  short sVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (snd_wave_out_handle == 0) {
    sVar1 = 3;
  }
  else if ((snd_wave_device_open == 0) &&
          (iVar2 = snd_wave_open(snd_wave_notify_hwnd,snd_wave_open_buffer_bytes,snd_wave_max_buffers), iVar2 != 0)) {
    sVar1 = 0;
  }
  else if (snd_wave_source_count < 5) {
    if ((param_2 & 8) == 0) {
      sVar1 = snd_wave_load_file(param_1,param_2,param_3,param_4);
    }
    else {
      sVar1 = snd_wave_open_stream(param_1,param_2,param_3);
    }
    if ((sVar1 == 0) &&
       (snd_wave_source_count = snd_wave_source_count + 1, (*(uint *)(snd_wave_cur_buffer + 0xc) >> 5 & 1) == 0)) {
      local_10 = 0;
      local_8 = (i32 *)snd_wave_cur_buffer;
      while ((local_10 < snd_wave_buffer_count && (iVar2 = snd_wave_mix_buffer(*local_8), iVar2 != 1))) {
        local_8 = (i32 *)local_8[7];
        local_10++;
      }
      snd_wave_write_pending(snd_wave_cur_buffer);
    }
  }
  else {
    sVar1 = 0;
  }
  return sVar1;
}
#undef snd_wave_buffer_count
#undef snd_wave_max_buffers
#undef snd_wave_notify_hwnd
#undef snd_wave_out_handle
#undef snd_wave_source_count
#undef local_10
#undef local_8

/* 005d61ab auto */
#define local_c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(8)))
void __cdecl snd_wave_free_by_id(i32 param_1)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  local_c = snd_wave_sources;
  while (local_c != 0) {
    if (*(short *)(local_c + 0x8a) == (short)param_1) {
      local_c = snd_wave_free(local_8,local_c);
    }
    else {
      local_8 = local_c;
      local_c = *(iptr *)(local_c + 0xb8);
    }
  }
  return;
}
#undef local_c
#undef local_8

/* 005d6283 auto */
#define local_5c (*(i32 (*)[5])(frame_ + FRAME_OFF(4)))
#define local_48 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_44 (*(HPSTR *)(frame_ + FRAME_OFF(28)))
#define local_40 (*(HPSTR *)(frame_ + FRAME_OFF(32)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(76)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(80)))
#define local_c (*(int *)(frame_ + FRAME_OFF(84)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(88)))
void __cdecl snd_wave_stream_refill(iptr param_1)

{
  int iVar1;
  i32 *puVar2;
  i32 *puVar3;
  i8 frame_[FRAME_OFF(96)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_10 = 0;
  local_14 = 0;
  puVar2 = (i32 *)(param_1 + 0x18);
  puVar3 = local_5c;
  for (iVar1 = 0x12; iVar1 != 0; iVar1--) {
    *puVar3 = *puVar2;
    puVar2++;
    puVar3++;
  }
  if (local_44 == local_40) {
    local_c = 0;
    local_8 = local_48;
  }
  else {
    local_c = local_38 - (int)local_40;
    local_8 = local_48 - local_c;
  }
  if (local_c == 0) {
    local_40 = local_44;
  }
  else {
    FUN_005f6500(local_44,local_40,local_c);
    local_40 = local_44 + local_c;
  }
  while (local_14 == 0) {
    local_10 = *(int *)(param_1 + 8) - *(int *)(param_1 + 0x68);
    if (local_8 < local_10) {
      mmioRead(*(HMMIO *)(param_1 + 0x60),local_40,local_8);
      *(int *)(param_1 + 0x68) = *(int *)(param_1 + 0x68) + local_8;
      *(HPSTR *)(param_1 + 0x34) = local_44;
      local_14 = 1;
    }
    else {
      mmioRead(*(HMMIO *)(param_1 + 0x60),local_40,local_10);
      *(i32 *)(param_1 + 0x68) = 0;
      local_40 += local_10;
      local_8 = local_38 - (int)local_40;
      mmioSeek(*(HMMIO *)(param_1 + 0x60),*(LONG *)(param_1 + 0x10),0);
    }
  }
  return;
}
#undef local_5c
#undef local_48
#undef local_44
#undef local_40
#undef local_38
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 005d63c5 auto */
LPVOID __cdecl snd_global_alloc_lock(SIZE_T param_1,iptr param_2)

{
  HGLOBAL pvVar1;
  LPVOID pvVar2;
  
  pvVar1 = GlobalAlloc(0x2002,param_1);
  *(HGLOBAL *)param_2 = pvVar1;
  if (*(int *)param_2 == 0) {
    pvVar2 = (LPVOID)0x0;
  }
  else {
    pvVar2 = GlobalLock(*(HGLOBAL *)param_2);
    if (pvVar2 == (LPVOID)0x0) {
      GlobalFree(*(HGLOBAL *)param_2);
      *(i32 *)param_2 = 0;
    }
  }
  return pvVar2;
}

/* 005d6430 auto */
void __cdecl snd_global_free(HGLOBAL param_1)

{
  if (param_1 != (HGLOBAL)0x0) {
    GlobalUnlock(param_1);
    GlobalFree(param_1);
  }
  return;
}

/* 005d645e auto */
#define snd_wave_total_buffer_bytes (*(uint *)((u8 *)&g.d_006385cc))
#define _DAT_006385b4 (*(i32 *)((u8 *)&g.d_006385b4))
#define local_1c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(int * *)(frame_ + FRAME_OFF(8)))
#define local_14 (*(uint *)(frame_ + FRAME_OFF(12)))
#define local_10 (*(MMRESULT *)(frame_ + FRAME_OFF(16)))
#define local_c (*(uint *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(int * *)(frame_ + FRAME_OFF(24)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

MMRESULT __cdecl snd_wave_alloc_buffers(uint param_1,HWAVEOUT param_2,uint param_3)

{
  int iVar1;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = (int *)0x0;
  local_c = param_1 / param_3;
  if (snd_wave_device_open == 0) {
    local_10 = 3;
  }
  else {
    for (local_14 = 0; local_14 < param_3; local_14++) {
      local_18 = local_8;
      local_8 = (int *)snd_global_alloc_lock(0x20,(iptr)&local_1c);
      if (local_8 == (int *)0x0) {
        if (local_14 != 0) {
          snd_wave_reset_all(param_2);
        }
        return 4;
      }
      if (local_14 == 0) {
        snd_wave_buffer_ring = (iptr)local_8;
        snd_wave_cur_buffer = (iptr)local_8;
      }
      _memset(local_8,0,0x20);
      local_8[2] = local_1c;
      iVar1 = snd_global_alloc_lock(local_c + 0x20,(iptr)&local_1c);
      *local_8 = iVar1;
      if (*local_8 == 0) {
        if (local_14 != 0) {
          snd_wave_reset_all(param_2);
        }
        return 4;
      }
      _memset((void *)*local_8,0,0x20);
      *(int *)*local_8 = *local_8 + 0x20;
      local_8[4] = *(int *)*local_8;
      *(uint *)(*local_8 + 4) = local_c;
      local_8[6] = *(int *)(*local_8 + 4);
      local_8[5] = *(int *)*local_8 + local_8[6];
      *(int **)(*local_8 + 0xc) = local_8;
      local_8[1] = local_1c;
      local_8[3] = local_8[3] & 0xffff807fU | (local_14 & 0xff) << 7;
      local_10 = waveOutPrepareHeader(param_2,(LPWAVEHDR)*local_8,0x20);
      if (local_10 != 0) {
        snd_waveout_error_box(local_10);
        snd_wave_reset_all(param_2);
        return 5;
      }
      *(uint *)(*local_8 + 0x10) = *(uint *)(*local_8 + 0x10) | 1;
      if (local_18 != (int *)0x0) {
        local_18[7] = (int)local_8;
      }
      local_10 = 0;
    }
    local_8[7] = snd_wave_buffer_ring;
    _DAT_006385b4 = 1;
    snd_wave_total_buffer_bytes = param_1;
  }
  return local_10;
}
#undef snd_wave_total_buffer_bytes
#undef _DAT_006385b4
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 005d6685 auto */
#define snd_wave_buffer_count (*(int *)((u8 *)&g.d_00638588))
#define local_10 (*(uint *)(frame_ + FRAME_OFF(0)))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(8)))
void __cdecl snd_wave_add_buffers(int param_1)

{
  iptr iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = snd_wave_spare_buffers;
  *(uint *)(snd_wave_spare_buffers + 0xc) = *(uint *)(snd_wave_spare_buffers + 0xc) & 0xfffffffe;
  for (local_10 = 0; (int)local_10 < param_1 - 1; local_10++) {
    local_8 = *(int *)(local_8 + 0x1c);
    *(uint *)(local_8 + 0xc) = *(uint *)(local_8 + 0xc) & 0xfffffffe;
  }
  local_c = snd_wave_buffer_ring;
  for (local_10 = 0; local_10 < snd_wave_buffer_count - 1U; local_10++) {
    local_c = *(iptr *)(local_c + 0x1c);
  }
  iVar1 = *(iptr *)(local_8 + 0x1c);
  *(iptr *)(local_c + 0x1c) = snd_wave_spare_buffers;
  snd_wave_spare_buffers = iVar1;
  *(iptr *)(local_8 + 0x1c) = snd_wave_buffer_ring;
  snd_wave_buffer_count += param_1;
  return;
}
#undef snd_wave_buffer_count
#undef local_10
#undef local_c
#undef local_8

/* 005d673a auto */
#define snd_wave_buffer_count (*(int *)((u8 *)&g.d_00638588))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(16)))
void __cdecl snd_wave_remove_buffers(int param_1)

{
  iptr iVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = snd_wave_buffer_ring;
  if ((uint)(snd_wave_buffer_count - param_1) <= (*(uint *)(snd_wave_cur_buffer + 0xc) >> 7 & 0xff)) {
    snd_wave_cur_buffer = snd_wave_buffer_ring;
  }
  for (local_14 = 0; local_14 < (int)((snd_wave_buffer_count - param_1) - 1U); local_14++) {
    local_8 = *(iptr *)(local_8 + 0x1c);
  }
  iVar1 = *(iptr *)(local_8 + 0x1c);
  *(iptr *)(local_8 + 0x1c) = snd_wave_buffer_ring;
  local_8 = iVar1;
  for (local_14 = 0; local_14 < param_1; local_14++) {
    *(uint *)(local_8 + 0xc) = *(uint *)(local_8 + 0xc) & 0xfffffffd;
    *(uint *)(local_8 + 0xc) = *(uint *)(local_8 + 0xc) & 0xfffffffb;
    *(uint *)(local_8 + 0xc) = *(uint *)(local_8 + 0xc) | 1;
    *(uint *)(local_8 + 0xc) = *(uint *)(local_8 + 0xc) & 0xfffffff7;
    *(uint *)(local_8 + 0xc) = *(uint *)(local_8 + 0xc) & 0xffffffef;
    *(uint *)(local_8 + 0xc) = *(uint *)(local_8 + 0xc) & 0xffffffdf;
    *(uint *)(local_8 + 0xc) = *(uint *)(local_8 + 0xc) & 0xffffffbf;
    local_8 = *(iptr *)(local_8 + 0x1c);
  }
  local_8 = iVar1;
  for (local_14 = 0; local_14 < param_1 - 1; local_14++) {
    local_8 = *(iptr *)(local_8 + 0x1c);
  }
  *(iptr *)(local_8 + 0x1c) = snd_wave_spare_buffers;
  snd_wave_spare_buffers = iVar1;
  snd_wave_buffer_count -= param_1;
  return;
}
#undef snd_wave_buffer_count
#undef local_14
#undef local_8

/* 005d687b auto */
#define snd_wave_buffer_count (*(uint *)((u8 *)&g.d_00638588))
#define snd_wave_max_buffers (*(uint *)((u8 *)&g.d_00638584))
#define snd_wave_out_handle (*(int *)((u8 *)&g.d_00638578))
void __cdecl snd_wave_set_buffer_count(uint param_1)

{
  if ((snd_wave_out_handle != 0) &&
     (((snd_wave_sources == 0 || (*(short *)(snd_wave_sources + 0x88) != 4)) ||
      ((*(uint *)(snd_wave_sources + 0x70) >> 1 & 1) != 0)))) {
    if (snd_wave_max_buffers < param_1) {
      param_1 = snd_wave_max_buffers;
    }
    if ((int)param_1 < 2) {
      param_1 = 2;
    }
    if (snd_wave_buffer_count < param_1) {
      snd_wave_add_buffers(param_1 - snd_wave_buffer_count);
    }
    else if (param_1 < snd_wave_buffer_count) {
      snd_wave_remove_buffers(snd_wave_buffer_count - param_1);
    }
  }
  return;
}
#undef snd_wave_buffer_count
#undef snd_wave_max_buffers
#undef snd_wave_out_handle

/* 005d6947 auto */
#define snd_wave_out_handle (*(HWAVEOUT *)((u8 *)&g.d_00638578))
#define local_14 (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(uint *)(frame_ + FRAME_OFF(8)))
#define local_c (*(byte * *)(frame_ + FRAME_OFF(12)))
i32 __cdecl snd_wave_write_pending(iptr param_1)

{
  MMRESULT MVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_10 = local_10 & 0xffff0000;
  while ((*(uint *)(param_1 + 0xc) >> 6 & 1) != 0) {
    local_c = (byte *)**(i32 **)param_1;
    for (local_14 = 0; local_14 < *(uint *)(*(int *)param_1 + 4); local_14++) {
      *local_c = *local_c ^ 0x80;
      local_c++;
    }
    MVar1 = waveOutWrite(snd_wave_out_handle,*(LPWAVEHDR *)param_1,0x20);
    local_10 = CONCAT22((*(i16 *)((char *)&local_10 + 2)),(short)MVar1);
    if ((short)MVar1 == 0) {
      *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) | 0x20;
      *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) & 0xffffffbf;
    }
    else {
      if ((MVar1 & 0xffff) != 0x21) {
        snd_waveout_error_box(local_10);
      }
      *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) & 0xffffffdf;
    }
    param_1 = *(iptr *)(param_1 + 0x1c);
  }
  return 0;
}
#undef snd_wave_out_handle
#undef local_14
#undef local_10
#undef local_c

/* 005d6a2c auto */
#define snd_wave_buffer_count (*(uint *)((u8 *)&g.d_00638588))
#define snd_wave_notify_hwnd (*(HWND *)((u8 *)&g.d_0063857c))
#define snd_wave_out_handle (*(HWAVEOUT *)((u8 *)&g.d_00638578))
#define _DAT_006385b8 (*(i16 *)((u8 *)&g.d_006385b8))
#define _DAT_006385d4 (*(i32 *)((u8 *)&g.d_006385d4))
#define local_30 (*(tagMSG *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(iptr *)(frame_ + FRAME_OFF(28)))
#define local_10 (*(uint *)(frame_ + FRAME_OFF(32)))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(36)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(40)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl snd_wave_stop_all(void)

{
  BOOL BVar1;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 0;
  _DAT_006385b8 = 0;
  local_14 = snd_wave_sources;
  if (snd_wave_out_handle != (HWAVEOUT)0x0) {
    waveOutReset(snd_wave_out_handle);
    while (BVar1 = PeekMessageA(&local_30,snd_wave_notify_hwnd,0x3bd,0x3bd,1), BVar1 != 0) {
      _DAT_006385d4++;
    }
    while (local_14 != 0) {
      if (*(short *)(local_14 + 0x88) == 4) {
        local_c = local_14;
        local_14 = *(iptr *)(local_14 + 0xb8);
      }
      else {
        local_14 = snd_wave_free(local_c,local_14);
      }
    }
    local_8 = snd_wave_buffer_ring;
    if (snd_wave_buffer_ring != 0) {
      for (local_10 = 0; local_10 < snd_wave_buffer_count; local_10++) {
        *(uint *)(local_8 + 0xc) = *(uint *)(local_8 + 0xc) & 0xffffffdf;
        *(uint *)(local_8 + 0xc) = *(uint *)(local_8 + 0xc) & 0xffffffbf;
        local_8 = *(iptr *)(local_8 + 0x1c);
      }
    }
  }
  return;
}
#undef snd_wave_buffer_count
#undef snd_wave_notify_hwnd
#undef snd_wave_out_handle
#undef _DAT_006385b8
#undef _DAT_006385d4
#undef local_30
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 005d6b4c auto */
#define local_8 (*(uptr *)(frame_ + FRAME_OFF(0)))
void __cdecl snd_fill_silence_u8(iptr param_1,uint param_2)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; local_8 < param_2; local_8++) {
    *(i8 *)(local_8 + param_1) = 0x80;
  }
  return;
}
#undef local_8

/* 005d6b89 auto */
#define snd_wave_buffer_count (*(uint *)((u8 *)&g.d_00638588))
#define snd_wave_max_buffers (*(uint *)((u8 *)&g.d_00638584))
#define _DAT_006385b8 (*(i16 *)((u8 *)&g.d_006385b8))
#define local_14 (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(int * *)(frame_ + FRAME_OFF(16)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __cdecl snd_wave_reset_all(HWAVEOUT param_1)

{
  int *piVar1;
  iptr iVar2;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar2 = snd_wave_buffer_ring;
  local_8 = (int *)snd_wave_buffer_ring;
  _DAT_006385b8 = 0;
  if (snd_wave_device_open != 0) {
    waveOutReset(param_1);
  }
  if (snd_wave_buffer_count != snd_wave_max_buffers) {
    snd_wave_set_buffer_count(snd_wave_max_buffers);
  }
  if (iVar2 != 0) {
    for (local_14 = 0; local_14 < snd_wave_max_buffers; local_14++) {
      piVar1 = (int *)local_8[7];
      if (*local_8 != 0) {
        waveOutUnprepareHeader(param_1,(LPWAVEHDR)*local_8,0x20);
        snd_global_free(local_8[1]);
      }
      snd_global_free(local_8[2]);
      local_8 = piVar1;
    }
  }
  snd_wave_buffer_ring = 0;
  do {
    snd_wave_sources = snd_wave_free(0,snd_wave_sources);
  } while (snd_wave_sources != 0);
  snd_wave_sources = 0;
  return local_c;
}
#undef snd_wave_buffer_count
#undef snd_wave_max_buffers
#undef _DAT_006385b8
#undef local_14
#undef local_c
#undef local_8

/* 005d6c99 auto */
#define snd_wave_block_align (*(i8 *)((u8 *)&g.d_006385ac))
#define snd_wave_buffer_count (*(uint *)((u8 *)&g.d_00638588))
#define _DAT_00638594 (*(i32 *)((u8 *)&g.d_00638594))
#define local_30 (*(i32 * *)(frame_ + FRAME_OFF(0)))
#define local_2c (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_28 (*(byte * *)(frame_ + FRAME_OFF(8)))
#define local_20 (*(int * *)(frame_ + FRAME_OFF(16)))
#define local_18 (*(i32 * *)(frame_ + FRAME_OFF(24)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(28)))
#define local_10 (*(uint *)(frame_ + FRAME_OFF(32)))
#define local_8 (*(code * *)(frame_ + FRAME_OFF(40)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __cdecl snd_wave_on_buffer_done(HWAVEOUT param_1,iptr param_2)

{
  i16 uVar1;
  i32 *puVar2;
  int src;
  MMRESULT MVar5;
  iptr iVar3;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar3 = snd_wave_sources;
  local_10 = local_10 & 0xffff0000;
  local_8 = (code *)0x0;
  uVar1 = 0;
  if (snd_wave_device_open != 0) {
    local_20 = *(int **)(param_2 + 0xc);
    local_2c = 0;
    while ((local_2c < snd_wave_buffer_count &&
           (snd_wave_cur_buffer = *(int *)(snd_wave_cur_buffer + 0x1c),
           (*(uint *)(snd_wave_cur_buffer + 0xc) >> 5 & 1) == 0))) {
      local_2c++;
    }
    if ((*(byte *)(local_20 + 3) & 1) == 0) {
      local_30 = (i32 *)snd_wave_sources;
      if ((((snd_wave_sources != 0) && (*(short *)(snd_wave_sources + 0x88) == 4)) &&
          (((uint)local_20[3] >> 1 & 1) != 0)) && (((uint)local_20[3] >> 4 & 1) != 0)) {
        **(ushort **)(snd_wave_sources + 0x8c) = **(ushort **)(snd_wave_sources + 0x8c) & 0xfffb;
        *(uint *)(iVar3 + 0x70) = *(uint *)(iVar3 + 0x70) | 2;
      }
      do {
        puVar2 = (i32 *)*local_20;
        local_28 = *(byte **)*local_20;
        while ((local_30 != (i32 *)0x0 && ((*(uint *)((int)local_30 + 0x70) >> 1 & 1) != 0)))
        {
          local_30 = *(i32 **)((int)local_30 + 0xb8);
        }
        if (local_30 == (i32 *)0x0) {
          snd_fill_silence_u8(*(iptr *)*local_20,*(i32 *)(*local_20 + 4));
          local_20[3] = local_20[3] & 0xffffffdf;
        }
        else {
          if (((uint)local_20[3] >> 6 & 1) == 0) {
            if (*(short *)((int)local_30 + 0x88) == 4) {
              if (((uint)local_20[3] >> 3 & 1) == 0) {
                snd_avi_fill_buffer((iptr)local_20,(iptr)local_30);
                _DAT_00638594++;
              }
              src = ((uint)local_20[3] >> 7 & 0xff) * *(int *)((int)local_30 + 0x9c) +
                      *(int *)((int)local_30 + 0x30);
              snd_resample_8bit(local_20[4],src,local_20[6] / (int)(uint)(ushort)snd_wave_block_align,
                           CONCAT22((short)((uint)local_30 >> 0x10),
                                    *(i16 *)((int)local_30 + 0x80)),
                           CONCAT22((short)((uint)src >> 0x10),(ushort)snd_wave_block_align));
              if (((uint)local_20[3] >> 1 & 1) != 0) {
                local_20[3] = local_20[3] | 0x10;
              }
            }
            else {
              snd_wave_copy_source((iptr)local_30,*puVar2,puVar2[1]);
            }
            for (local_30 = *(i32 **)((int)local_30 + 0xb8); local_30 != (i32 *)0x0;
                local_30 = *(i32 **)((int)local_30 + 0xb8)) {
              if ((*(uint *)((int)local_30 + 0x70) >> 1 & 1) == 0) {
                snd_wave_mix_source((uptr)local_30,*puVar2,puVar2[1]);
              }
            }
            local_20[3] = local_20[3] | 0x40;
            *(uint *)(*local_20 + 0x10) = *(uint *)(*local_20 + 0x10) & 0xfffffffe;
          }
          for (local_2c = 0; local_2c < (uint)puVar2[1]; local_2c++) {
            *local_28 = *local_28 ^ 0x80;
            local_28++;
          }
          MVar5 = waveOutWrite(param_1,(LPWAVEHDR)*local_20,0x20);
          local_10 = CONCAT22((*(i16 *)((char *)&local_10 + 2)),(short)MVar5);
          if ((short)MVar5 == 0) {
            local_20[3] = local_20[3] & 0xffffffbf;
            local_20[3] = local_20[3] | 0x20;
            local_20[3] = local_20[3] & 0xfffffff7;
          }
          else {
            snd_waveout_error_box(local_10);
            local_20[3] = local_20[3] & 0xffffffdf;
          }
        }
        local_30 = (i32 *)snd_wave_sources;
        local_18 = (i32 *)0x0;
        local_14 = 0;
        while (local_30 != (i32 *)0x0) {
          if ((*(byte *)(local_30 + 0x1c) & 1) == 0) {
            if (((((uint)local_30[0x1c] >> 1 & 1) == 0) &&
                (local_14 = local_14 + 1, ((uint)local_30[0x1c] >> 3 & 1) != 0)) &&
               (*(short *)(local_30 + 0x22) != 4)) {
              if (((uint)local_30[0x1c] >> 2 & 1) == 0) {
                mmioAdvance((HMMIO)*local_30,(LPMMIOINFO)(local_30 + 6),0);
              }
              else {
                snd_wave_stream_refill((iptr)local_30);
              }
            }
            local_18 = local_30;
            local_30 = (i32 *)local_30[0x2e];
          }
          else if (*(short *)(local_30 + 0x22) == 4) {
            local_18 = local_30;
            local_30 = (i32 *)local_30[0x2e];
          }
          else {
            if (local_30[0x2d] != 0) {
              local_8 = (code *)local_30[0x2d];
              local_30[0x2d] = 0;
              uVar1 = *(i16 *)((int)local_30 + 0x8a);
            }
            local_30 = (i32 *)snd_wave_free((iptr)local_18,(iptr)local_30);
          }
        }
        local_30 = (i32 *)snd_wave_sources;
        local_20 = (int *)local_20[7];
      } while ((local_14 != 0) && (((uint)local_20[3] >> 5 & 1) == 0));
      if (local_8 != (code *)0x0) {
        (*local_8)(uVar1);
      }
    }
  }
  return 0;
}
#undef snd_wave_block_align
#undef snd_wave_buffer_count
#undef _DAT_00638594
#undef local_30
#undef local_2c
#undef local_28
#undef local_20
#undef local_18
#undef local_14
#undef local_10
#undef local_8

/* 005d717f auto */
#define snd_wave_block_align (*(i8 *)((u8 *)&g.d_006385ac))
#define local_20 (*(i32 * *)(frame_ + FRAME_OFF(0)))
#define local_c (*(i32 * *)(frame_ + FRAME_OFF(20)))
i32 __cdecl snd_wave_mix_buffer(i32 *param_1)

{
  bool bVar1;
  i32 uVar2;
  int src;
  iptr iVar1;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  bVar1 = false;
  if (snd_wave_device_open == 0) {
    uVar2 = 0;
  }
  else {
    iVar1 = param_1[3];
    *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) & 0xfffffffd;
    local_20 = (i32 *)snd_wave_sources;
    while ((local_20 != (i32 *)0x0 && ((*(uint *)((int)local_20 + 0x70) >> 1 & 1) != 0))) {
      local_20 = *(i32 **)((int)local_20 + 0xb8);
    }
    if (local_20 == (i32 *)0x0) {
      *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) & 0xffffffdf;
    }
    else {
      if ((*(uint *)(iVar1 + 0xc) >> 6 & 1) == 0) {
        if (*(short *)((int)local_20 + 0x88) == 4) {
          src = (*(uint *)(iVar1 + 0xc) >> 7 & 0xff) * *(int *)((int)local_20 + 0x9c) +
                  *(int *)((int)local_20 + 0x30);
          snd_resample_8bit(*(i32 *)(iVar1 + 0x10),src,
                       *(int *)(iVar1 + 0x18) / (int)(uint)(ushort)snd_wave_block_align,
                       CONCAT22((short)((uint)local_20 >> 0x10),
                                *(i16 *)((int)local_20 + 0x80)),
                       CONCAT22((short)((uint)src >> 0x10),(ushort)snd_wave_block_align));
        }
        else {
          src = snd_wave_copy_source((iptr)local_20,*param_1,param_1[1]);
          if (src == 1) {
            bVar1 = true;
          }
        }
        *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) | 0x40;
        local_20 = *(i32 **)((int)local_20 + 0xb8);
      }
      for (; local_20 != (i32 *)0x0; local_20 = *(i32 **)((int)local_20 + 0xb8)) {
        if (((*(uint *)((int)local_20 + 0x70) >> 1 & 1) == 0) &&
           (src = snd_wave_mix_source((uptr)local_20,*param_1,param_1[1]), src == 0)) {
          bVar1 = false;
        }
      }
      param_1[4] = param_1[4] & 0xfffffffe;
    }
    local_20 = (i32 *)snd_wave_sources;
    local_c = (i32 *)0x0;
    while (local_20 != (i32 *)0x0) {
      if ((*(byte *)(local_20 + 0x1c) & 1) == 0) {
        if ((((uint)local_20[0x1c] >> 1 & 1) == 0) && (((uint)local_20[0x1c] >> 3 & 1) != 0)) {
          if (*(short *)(local_20 + 0x22) == 4) {
            snd_avi_stream_refill((iptr)local_20);
          }
          if (*(short *)(local_20 + 0x22) != 4) {
            if (((uint)local_20[0x1c] >> 2 & 1) == 0) {
              mmioAdvance((HMMIO)*local_20,(LPMMIOINFO)(local_20 + 6),0);
            }
            else {
              snd_wave_stream_refill((iptr)local_20);
            }
          }
        }
        local_c = local_20;
        local_20 = (i32 *)local_20[0x2e];
      }
      else if (*(short *)(local_20 + 0x22) == 4) {
        *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) | 2;
        local_20[0x1c] = local_20[0x1c] | 2;
        local_c = local_20;
        local_20 = (i32 *)local_20[0x2e];
      }
      else {
        local_20 = (i32 *)snd_wave_free((iptr)local_c,(iptr)local_20);
      }
    }
    if ((snd_wave_sources == 0) || (bVar1)) {
      uVar2 = 1;
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}
#undef snd_wave_block_align
#undef local_20
#undef local_c

/* 005d7494 auto */
#define snd_wave_source_count (*(short *)((u8 *)&g.d_0063858c))
iptr __cdecl snd_wave_free(iptr param_1,iptr param_2)

{
  iptr iVar2;
  iptr iVar1;
  
  if (param_2 == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = *(iptr *)(param_2 + 0xb8);
    iVar1 = iVar2;
    if (param_1 != 0) {
      *(iptr *)(param_1 + 0xb8) = iVar2;
      iVar1 = snd_wave_sources;
    }
    snd_wave_sources = iVar1;
    mmioClose(*(HMMIO *)param_2,0);
    if ((*(uint *)(param_2 + 0x70) >> 2 & 1) != 0) {
      mmioClose(*(HMMIO *)(param_2 + 0x60),0);
    }
    GlobalUnlock(*(HGLOBAL *)(param_2 + 0x6c));
    GlobalFree(*(HGLOBAL *)(param_2 + 0x6c));
    snd_wave_source_count--;
  }
  return iVar2;
}
#undef snd_wave_source_count

/* 005d753e auto */
#define snd_wave_block_align (*(i8 *)((u8 *)&g.d_006385ac))
#define count (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_c (*(uint *)(frame_ + FRAME_OFF(12)))
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

i32 __cdecl snd_wave_copy_source(iptr param_1,int dst,uint param_3)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  i32 uVar4;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  uVar2 = param_3 / (ushort)snd_wave_block_align;
  if ((param_1 == 0) || ((*(byte *)(param_1 + 0x70) & 1) != 0)) {
    count = 0;
  }
  else {
    if ((*(uint *)(param_1 + 0x70) >> 2 & 1) == 0) {
      local_c = *(int *)(param_1 + 8) - *(int *)(param_1 + 100);
    }
    else {
      local_c = *(int *)(param_1 + 0x3c) - *(int *)(param_1 + 0x34);
    }
    uVar3 = local_c / *(ushort *)(param_1 + 0x80);
    count = uVar2;
    if (uVar3 < uVar2) {
      *(uint *)(param_1 + 0x70) = *(uint *)(param_1 + 0x70) | 1;
      count = uVar3;
    }
    if ((uint)(*(int *)(param_1 + 0x3c) - *(int *)(param_1 + 0x34)) /
        (uint)*(ushort *)(param_1 + 0x80) < uVar2 * 2) {
      *(uint *)(param_1 + 0x70) = *(uint *)(param_1 + 0x70) | 8;
    }
    else {
      *(uint *)(param_1 + 0x70) = *(uint *)(param_1 + 0x70) & 0xfffffff7;
    }
    uVar2 -= count;
  }
  if (count != 0) {
    uVar1 = snd_resample_8bit(dst,*(i32 *)(param_1 + 0x34),count,
                         CONCAT22((short)((uint)param_1 >> 0x10),*(i16 *)(param_1 + 0x80)),
                         CONCAT22((short)(uVar2 >> 0x10),(ushort)snd_wave_block_align));
    *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) + (uint)uVar1;
    if ((*(short *)(param_1 + 0x88) == 4) && (*(int *)(param_1 + 0x3c) == *(int *)(param_1 + 0x34)))
    {
      *(i32 *)(param_1 + 0x34) = *(i32 *)(param_1 + 0x30);
    }
    *(uint *)(param_1 + 0x70) = *(uint *)(param_1 + 0x70) & 0xffffffef;
  }
  if (uVar2 == 0) {
    if ((*(uint *)(param_1 + 0x70) >> 2 & 1) == 0) {
      *(int *)(param_1 + 100) = *(int *)(param_1 + 100) + *(ushort *)(param_1 + 0x80) * count;
    }
    else {
      *(i32 *)(param_1 + 100) = 0;
    }
    uVar4 = 0;
  }
  else {
    _memset((void *)(dst + (ushort)snd_wave_block_align * count),0,(ushort)snd_wave_block_align * uVar2);
    if ((param_1 != 0) && (local_c != 0)) {
      *(int *)(param_1 + 100) = *(int *)(param_1 + 100) + *(ushort *)(param_1 + 0x80) * count;
    }
    uVar4 = 1;
  }
  return uVar4;
}
#undef snd_wave_block_align
#undef count
#undef local_c

/* 005d778c auto */
#define snd_wave_block_align (*(i8 *)((u8 *)&g.d_006385ac))
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(4)))
#define count (*(i32 *)(frame_ + FRAME_OFF(8)))
#define local_c (*(uint *)(frame_ + FRAME_OFF(12)))
i32 __cdecl snd_wave_mix_source(uptr param_1,i32 dst,uint param_3)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  uptr uVar4;
  i32 uVar5;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((*(uint *)(param_1 + 0x70) >> 2 & 1) == 0) {
    local_c = *(int *)(param_1 + 8) - *(int *)(param_1 + 100);
  }
  else {
    local_c = *(int *)(param_1 + 0x3c) - *(int *)(param_1 + 0x34);
  }
  uVar2 = local_c / *(ushort *)(param_1 + 0x80);
  uVar3 = param_3 / (ushort)snd_wave_block_align;
  count = uVar3;
  if (uVar2 < uVar3) {
    *(uint *)(param_1 + 0x70) = *(uint *)(param_1 + 0x70) | 1;
    count = uVar2;
  }
  if ((uint)(*(int *)(param_1 + 0x3c) - *(int *)(param_1 + 0x34)) /
      (uint)*(ushort *)(param_1 + 0x80) < uVar3 * 2) {
    uVar4 = *(uint *)(param_1 + 0x70) | 8;
    *(uptr *)(param_1 + 0x70) = uVar4;
  }
  else {
    *(uint *)(param_1 + 0x70) = *(uint *)(param_1 + 0x70) & 0xfffffff7;
    uVar4 = param_1;
  }
  if (count != 0) {
    uVar1 = snd_mix_8bit_resample(dst,*(i32 *)(param_1 + 0x34),count,
                         CONCAT22((short)(param_1 >> 0x10),*(i16 *)(param_1 + 0x80)),
                         CONCAT22((short)(uVar4 >> 0x10),(ushort)snd_wave_block_align));
    local_14 = (uint)uVar1;
    *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) + local_14;
  }
  if ((*(uint *)(param_1 + 0x70) >> 2 & 1) == 0) {
    *(int *)(param_1 + 100) = *(int *)(param_1 + 100) + *(ushort *)(param_1 + 0x80) * count;
  }
  else {
    *(i32 *)(param_1 + 100) = 0;
  }
  if (((*(byte *)(param_1 + 0x70) & 1) == 0) || ((*(uint *)(param_1 + 0x70) >> 2 & 1) != 0)) {
    uVar5 = 0;
  }
  else {
    uVar5 = 1;
  }
  return uVar5;
}
#undef snd_wave_block_align
#undef local_14
#undef count
#undef local_c

/* 005d791b auto */
#define local_14 (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(uint *)(frame_ + FRAME_OFF(8)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
i32 __cdecl snd_avi_fill_buffer(iptr param_1,iptr param_2)

{
  i32 uVar1;
  uint uVar2;
  iptr iVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = snd_wave_sources;
  if (*(int *)(param_2 + 0x98) == param_1) {
    local_14 = *(int *)(snd_wave_sources + 0x9c) - *(int *)(snd_wave_sources + 0x68);
    local_8 = 0;
    uVar2 = *(int *)(snd_wave_sources + 8) -
            (*(int *)(snd_wave_sources + 0x90) - *(int *)(snd_wave_sources + 0x94));
    if (uVar2 < local_14) {
      local_14 = uVar2;
    }
    AVIStreamRead(*(i32 *)(snd_wave_sources + 0x84),
                  *(uint *)(snd_wave_sources + 0x90) / (uint)*(ushort *)(snd_wave_sources + 0x80),
                  local_14 / *(ushort *)(snd_wave_sources + 0x80),*(i32 *)(snd_wave_sources + 0x34)
                  ,local_14,&local_8,0);
    *(int *)(snd_wave_sources + 0x90) = *(int *)(snd_wave_sources + 0x90) + local_8;
    *(int *)(iVar1 + 0x34) = *(int *)(iVar1 + 0x34) + local_8;
    *(int *)(snd_wave_sources + 0x68) = *(int *)(snd_wave_sources + 0x68) + local_8;
    if (*(int *)(iVar1 + 0x3c) == *(int *)(iVar1 + 0x34)) {
      *(i32 *)(iVar1 + 0x34) = *(i32 *)(iVar1 + 0x30);
    }
    if (*(uint *)(snd_wave_sources + 0x9c) <= *(uint *)(snd_wave_sources + 0x68)) {
      *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) | 8;
      *(i32 *)(snd_wave_sources + 0x98) = *(i32 *)(param_1 + 0x1c);
      param_1 = *(iptr *)(snd_wave_sources + 0x98);
      *(i32 *)(snd_wave_sources + 0x68) = 0;
    }
    if (*(uint *)(snd_wave_sources + 8) <=
        (uint)(*(int *)(snd_wave_sources + 0x90) - *(int *)(snd_wave_sources + 0x94))) {
      local_10 = 0;
      while ((local_10 < (uint)(*(int *)(snd_wave_sources + 0x9c) - *(int *)(snd_wave_sources + 0x68)) &&
             (*(uint *)(iVar1 + 0x34) < *(uint *)(iVar1 + 0x3c)))) {
        **(i8 **)(iVar1 + 0x34) = 0x80;
        *(int *)(iVar1 + 0x34) = *(int *)(iVar1 + 0x34) + 1;
        local_10++;
      }
      if (*(int *)(iVar1 + 0x3c) == *(int *)(iVar1 + 0x34)) {
        *(i32 *)(iVar1 + 0x34) = *(i32 *)(iVar1 + 0x30);
      }
      *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) & 0xfffffff7;
      *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) | 2;
      *(uint *)(snd_wave_sources + 0x70) = *(uint *)(snd_wave_sources + 0x70) | 1;
      *(i32 *)(snd_wave_sources + 0x98) = *(i32 *)(param_1 + 0x1c);
      *(i32 *)(snd_wave_sources + 0x68) = 0;
    }
    uVar1 = 0;
  }
  else {
    uVar1 = 0xd;
  }
  return uVar1;
}
#undef local_14
#undef local_10
#undef local_8

/* 005dd010 auto */
#define _DAT_006389d0 (*(i32 *)((u8 *)&g.d_006389d0))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

C_004083b0_a28 * __thiscall mmwnd_ctor(C_004083b0_a28 *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  surfwnd_ctor((SurfaceWindow *)this);
  local_8 = 0;
  avi_audio_ctor((AviAudio *)&this->border_width);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  palette_init((GamePalette *)&this->client_x);
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),2);
  surface_ctor((DibSurface *)(this->pad_4a4 + 0xb4));
  this->vtable = (u32)&PTR_FUN_0061d718;
  this->style_flags = 0;
  this->double_size = 0;
  this->field_5a4 = 0;
  this->target_surface = 0;
  this->has_audio = 1;
  this->audio_playing = 0;
  this->target_surface = 0;
  this->start_frame = 0;
  this->end_frame = 0;
  this->current_frame = 0;
  this->edit_action_button = 0;
  this->cue_frame = 0;
  this->paused = 1;
  this->loop = 0;
  _DAT_006389d0 = this;
  return this;
}
#undef _DAT_006389d0
#undef local_10
#undef puStack_c
#undef local_8

/* 005dd1a0 auto */
#define _DAT_006389d0 (*(i32 *)((u8 *)&g.d_006389d0))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __thiscall avi_player_dtor(AviPlayer *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  *(i8 ***)this->pad_0 = &PTR_FUN_0061d718;
  (*(i32 *)((char *)&local_8 + 1)) = 0;
  (*(i8 *)((char *)&local_8 + 0)) = 3;
  avi_play_pause((iptr)this);
  avi_close((iptr)this);
  _DAT_006389d0 = 0;
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  /* inlined unwind funclet FUN_005dd230 */ { surface_dtor((DibSurface *)(*(int *)((iptr)&this) + 0x558)); }
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  /* inlined unwind funclet FUN_005dd23f */ { palette_destroy((GamePalette *)(*(int *)((iptr)&this) + 0x124)); }
  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
  /* inlined unwind funclet FUN_005dd24e */ { avi_audio_release((AviAudioReleaseView *)(*(int *)((iptr)&this) + 0x11c)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_005dd25d */ { surfwnd_dtor(*(SurfaceWindow **)((iptr)&this)); }
  return uStack_10;
}
#undef _DAT_006389d0
#undef uStack_10
#undef puStack_c
#undef local_8

/* 005dd27e auto */
void __thiscall
avi_player_create
          (C_004083b0_61c *this,iptr param_1,i32 param_2,u32 param_3,u32 param_4)

{
  surface_wnd_create
            ((DibSurface *)this,param_1,param_2,param_3,param_4,0x140,0xf0,(iptr)&this->client_x
            );
  surface_fill((DibSurface *)this,0);
  this->pos_x = param_3;
  this->pos_y = param_4;
  return;
}

/* 005dd2e3 auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __thiscall
avi_player_create_child
          (C_004083b0_61c *this,iptr param_1,i32 param_2,u32 param_3,u32 param_4,iptr param_5
          )

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_5 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = param_5 + 0x48;
  }
  wnd_create_with_surface
            ((DibSurface *)this,param_1,param_2,param_3,param_4,0x140,0xf0,(iptr)&this->client_x
             ,local_8);
  surface_fill((DibSurface *)this,0);
  this->target_surface = param_5;
  this->pos_x = param_3;
  this->pos_y = param_4;
  return;
}
#undef local_8

/* 005dd377 auto */
int __thiscall avi_player_open(AviPlayerOpenView *this,iptr param_1)

{
  int iVar1;
  
  avi_close((iptr)this);
  iVar1 = avi_open_file((iptr)this,param_1);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  return iVar1;
}

/* 005dd3c2 auto */
void __thiscall avi_player_play(AviPlayerPlayView *this)

{
  this[0x24].pad_0[4] = '\0';
  this[0x24].pad_0[5] = '\0';
  this[0x24].pad_0[6] = '\0';
  this[0x24].pad_0[7] = '\0';
  avi_play_start((iptr)this);
  return;
}

/* 005dd3f1 auto */
void __thiscall avi_player_play_range(AviPlayerRangeView *this,u32 param_1,u32 param_2)

{
  if ((int)param_1 <= (int)param_2) {
    this->loop = 0;
    avi_seek_frame((iptr)this,param_1,0);
    this->end_frame = param_2;
    this->start_frame = param_1;
    avi_play_start((iptr)this);
  }
  return;
}

/* 005dd45d auto */
void __thiscall avi_player_show_frame(void *this,i32 param_1)

{
  avi_seek_frame((iptr)this,param_1,1);
  return;
}

/* 005dd4c2 auto */
void __thiscall avi_player_loop_range(AviPlayerLoopView *this,u32 param_1,u32 param_2)

{
  this->start_frame = param_1;
  avi_seek_frame((iptr)this,param_1,0);
  this->end_frame = param_2;
  this->loop = 1;
  avi_play_start((iptr)this);
  return;
}

/* 005dd51d auto */
void __thiscall avi_player_pause(AviPlayerPauseView *this)

{
  avi_play_pause((iptr)this);
  return;
}

/* 005dd561 auto */
void __thiscall avi_player_set_palette(DibSurface *this,iptr param_1)

{
  avi_apply_palette((iptr)this,param_1);
  surface_set_palette(this,param_1);
  wnd_set_palette((WndBase *)(this + 1),param_1);
  return;
}

/* 005dd64c auto */
#define local_24 (*(tagRECT *)(frame_ + FRAME_OFF(4)))
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(20)))
void __thiscall
avi_player_draw_to(DibSurface *this,iptr param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((-1 < param_2) && (-1 < param_3)) {
    iVar1 = surface_width((DibSurface *)param_1);
    iVar2 = surface_get_width(this);
    if (iVar2 <= iVar1 - param_2) {
      iVar1 = surface_height((DibSurface *)param_1);
      iVar2 = surface_get_height(this);
      if (iVar2 <= iVar1 - param_3) {
        avi_decode_frame((iptr)this,0);
        iVar1 = surface_get_height(this);
        iVar2 = surface_get_width(this);
        SetRect(&local_24,0,0,iVar2,iVar1);
        CopyRect(&local_14,&local_24);
        OffsetRect(&local_14,param_2,param_3);
        surface_blit(this,param_1,(iptr)&local_24,(iptr)&local_14);
      }
    }
  }
  return;
}
#undef local_24
#undef local_14

/* 005dd71e auto */
void __thiscall avi_player_set_double_size(C_004083b0_61c *this,i32 param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = surface_get_height((DibSurface *)this);
  iVar1 = iVar1 * 2;
  iVar2 = surface_get_width((DibSurface *)this);
  wnd_resize_clamped((C_004083b0_4 *)this,iVar2 * 2,iVar1);
  this->double_size = 1;
  return;
}

/* 005dd761 auto */
void __thiscall avi_player_set_transparent(C_005dd761 *this,int param_1)

{
  if (param_1 == 0) {
    if (this->is_transparent != 0) {
      this->is_transparent = 0;
      avi_restart_decompress((iptr)this,0);
    }
  }
  else if (this->is_transparent == 0) {
    this->is_transparent = 1;
    avi_restart_decompress((iptr)this,1);
  }
  return;
}

/* 005dd8a0 auto */
#define app_hinstance (*(HINSTANCE *)((u8 *)&g.d_006e4ff0))
#define snd_mci_notify_hwnd (*(HWND *)((u8 *)&g.d_006e4ff8))
#define local_2c (*(WNDCLASSA *)(frame_ + FRAME_OFF(4)))
void __cdecl snd_system_init(void)

{
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_2c.style = 0;
  local_2c.lpfnWndProc = snd_mci_notify_wndproc;
  local_2c.cbClsExtra = 0;
  local_2c.cbWndExtra = 0;
  local_2c.hInstance = app_hinstance;
  local_2c.hIcon = (HICON)0x0;
  local_2c.hCursor = (HCURSOR)0x0;
  local_2c.hbrBackground = (HBRUSH)0x0;
  local_2c.lpszMenuName = (LPCSTR)0x0;
  local_2c.lpszClassName = s_MSMMWindow_006389e4;
  RegisterClassA(&local_2c);
  snd_mci_notify_hwnd = CreateWindowExA(0,s_MSMMWindow_006389f0,(LPCSTR)0x0,0,-0x80000000,-0x80000000,
                                 -0x80000000,-0x80000000,(HWND)0x0,(HMENU)0x0,app_hinstance,
                                 (LPVOID)0x0);
  snd_cd_open();
  return;
}
#undef app_hinstance
#undef snd_mci_notify_hwnd
#undef local_2c

/* 005dd93f auto */
#define snd_cd_device_id (*(uint *)((u8 *)&g.d_006389d8))
#define snd_midi_device_id (*(uint *)((u8 *)&g.d_006389d4))
LRESULT __stdcall snd_mci_notify_wndproc(HWND param_1,UINT param_2,WPARAM param_3,uint param_4)

{
  LRESULT LVar1;
  
  if (param_2 == 0x3b9) {
    if (param_3 == 1) {
      if ((param_4 & 0xffff) == snd_midi_device_id) {
        snd_midi_fire_notify_callback();
      }
      else if ((param_4 & 0xffff) == snd_cd_device_id) {
        snd_cd_fire_notify_callback();
      }
    }
    LVar1 = 0;
  }
  else {
    LVar1 = DefWindowProcA(param_1,param_2,param_3,param_4);
  }
  return LVar1;
}
#undef snd_cd_device_id
#undef snd_midi_device_id

/* 005dda11 auto */
void __cdecl snd_stop_sndplaysound(void)

{
  sndPlaySoundA((LPCSTR)0x0,1);
  return;
}

/* 005ddbc7 auto */
#define snd_cd_device_id (*(MCIDEVICEID *)((u8 *)&g.d_006389d8))
#define snd_cd_track_count (*(uint *)((u8 *)&g.d_006389e0))
#define snd_mci_notify_hwnd (*(i32 *)((u8 *)&g.d_006e4ff8))
#define local_20 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define local_1c (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(uint *)(frame_ + FRAME_OFF(8)))
#define local_14 (*(DWORD_PTR *)(frame_ + FRAME_OFF(12)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(16)))
#define local_c (*(uint *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(MCIDEVICEID *)(frame_ + FRAME_OFF(24)))
i32 __cdecl snd_cd_play_track(uint param_1)

{
  MCIERROR MVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (snd_cd_device_id == 0) {
    snd_cd_open();
    if (snd_cd_device_id == 0) {
      return 0;
    }
    local_8 = snd_cd_device_id;
  }
  else {
    local_8 = snd_cd_device_id;
    mciSendCommandA(snd_cd_device_id,0x808,0,0);
  }
  local_10 = 0;
  local_c = param_1 & 0xff;
  MVar1 = mciSendCommandA(local_8,0x807,8,(DWORD_PTR)&local_10);
  if (MVar1 == 0) {
    if ((param_1 & 0xff) == snd_cd_track_count) {
      local_14 = 5;
    }
    else {
      local_14 = 0xd;
    }
    local_1c = param_1 & 0xff;
    local_18 = (uint)(byte)((char)param_1 + 1);
    local_20 = snd_mci_notify_hwnd;
    MVar1 = mciSendCommandA(local_8,0x806,local_14,(DWORD_PTR)&local_20);
    if (MVar1 == 0) {
      uVar2 = 1;
    }
    else {
      snd_cd_close();
      dbg_logf(ADDR(0x638aa8, ((u8 *)&g.d_00638aa8)),MVar1);
      uVar2 = 0;
    }
  }
  else {
    snd_cd_close();
    dbg_logf(ADDR(0x638a84, ((u8 *)&g.d_00638a84)),MVar1);
    uVar2 = 0;
  }
  return uVar2;
}
#undef snd_cd_device_id
#undef snd_cd_track_count
#undef snd_mci_notify_hwnd
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 005ddd12 auto */
#define snd_midi_device_id (*(MCIDEVICEID *)((u8 *)&g.d_006389d4))
void __cdecl snd_midi_close(void)

{
  if (snd_midi_device_id != 0) {
    mciSendCommandA(snd_midi_device_id,0x808,0,0);
    snd_midi_device_id = 0;
  }
  return;
}
#undef snd_midi_device_id

/* 005ddd4e auto */
#define snd_cd_device_id (*(MCIDEVICEID *)((u8 *)&g.d_006389d8))
#define snd_cd_track_count (*(i32 *)((u8 *)&g.d_006389e0))
#define local_34 (*(i8 (*)[4])(frame_ + FRAME_OFF(4)))
#define local_30 (*(MCIDEVICEID *)(frame_ + FRAME_OFF(8)))
#define local_2c (*(char * *)(frame_ + FRAME_OFF(12)))
#define local_20 (*(i8 (*)[4])(frame_ + FRAME_OFF(24)))
#define local_1c (*(i32 *)(frame_ + FRAME_OFF(28)))
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(36)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(40)))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(44)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(48)))
void __cdecl snd_cd_open(void)

{
  MCIERROR MVar1;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (snd_cd_device_id == 0) {
    local_2c = s_cdaudio_00638acc;
    MVar1 = mciSendCommandA(0,0x803,0x2000,(DWORD_PTR)local_34);
    if (MVar1 == 0) {
      snd_cd_device_id = local_30;
      local_1c = 10;
      MVar1 = mciSendCommandA(local_30,0x80d,0x400,(DWORD_PTR)local_20);
      if (MVar1 == 0) {
        local_14 = 0;
        local_10 = 0;
        local_8 = 0;
        local_c = 3;
        mciSendCommandA(snd_cd_device_id,0x814,0x100,(DWORD_PTR)&local_14);
        snd_cd_track_count = local_10;
      }
      else {
        mciSendCommandA(snd_cd_device_id,0x804,0,0);
        snd_cd_device_id = 0;
        dbg_logf(ADDR(0x638af4, ((u8 *)&g.d_00638af4)),MVar1);
      }
    }
    else {
      dbg_logf(ADDR(0x638ad4, ((u8 *)&g.d_00638ad4)),MVar1);
    }
  }
  return;
}
#undef snd_cd_device_id
#undef snd_cd_track_count
#undef local_34
#undef local_30
#undef local_2c
#undef local_20
#undef local_1c
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 005dde57 auto */
#define snd_cd_device_id (*(MCIDEVICEID *)((u8 *)&g.d_006389d8))
#define snd_cd_track_count (*(i32 *)((u8 *)&g.d_006389e0))
void __cdecl snd_cd_close(void)

{
  if (snd_cd_device_id != 0) {
    mciSendCommandA(snd_cd_device_id,0x804,0,0);
    snd_cd_device_id = 0;
    snd_cd_track_count = 0;
  }
  return;
}
#undef snd_cd_device_id
#undef snd_cd_track_count

/* 005dde9d auto */
#define snd_cd_device_id (*(MCIDEVICEID *)((u8 *)&g.d_006389d8))
void __cdecl snd_cd_mci_stop(void)

{
  if (snd_cd_device_id != 0) {
    mciSendCommandA(snd_cd_device_id,0x808,0,0);
  }
  return;
}
#undef snd_cd_device_id

/* 005ddecf auto */
#define snd_mci_notify_hwnd (*(HWND *)((u8 *)&g.d_006e4ff8))
void __cdecl snd_system_shutdown(void)

{
  snd_stop_sndplaysound();
  snd_cd_mci_stop();
  snd_cd_close();
  snd_midi_close();
  DestroyWindow(snd_mci_notify_hwnd);
  return;
}
#undef snd_mci_notify_hwnd

/* 005ddeff auto */
#define snd_cd_device_id (*(MCIDEVICEID *)((u8 *)&g.d_006389d8))
#define snd_cd_track_count (*(i32 *)((u8 *)&g.d_006389e0))
#define local_3c (*(i8 (*)[4])(frame_ + FRAME_OFF(4)))
#define local_38 (*(MCIDEVICEID *)(frame_ + FRAME_OFF(8)))
#define local_34 (*(char * *)(frame_ + FRAME_OFF(12)))
#define local_24 (*(MCIDEVICEID *)(frame_ + FRAME_OFF(28)))
#define local_20 (*(i8 (*)[4])(frame_ + FRAME_OFF(32)))
#define local_1c (*(i32 *)(frame_ + FRAME_OFF(36)))
#define local_14 (*(i8 (*)[4])(frame_ + FRAME_OFF(44)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(48)))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(52)))
i32 __cdecl snd_cd_get_track_count(void)

{
  MCIERROR MVar1;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (snd_cd_device_id == 0) {
    local_34 = s_cdaudio_00638b18;
    MVar1 = mciSendCommandA(0,0x803,0x2000,(DWORD_PTR)local_3c);
    if (MVar1 != 0) {
      return 0xffffffff;
    }
    local_24 = local_38;
    snd_cd_device_id = local_38;
    local_1c = 10;
    MVar1 = mciSendCommandA(local_38,0x80d,0x400,(DWORD_PTR)local_20);
    if (MVar1 != 0) {
      mciSendCommandA(local_24,0x804,0,0);
      snd_cd_device_id = 0;
      return 0xffffffff;
    }
  }
  else {
    local_24 = snd_cd_device_id;
  }
  local_c = 3;
  MVar1 = mciSendCommandA(local_24,0x814,0x100,(DWORD_PTR)local_14);
  if (MVar1 == 0) {
    snd_cd_track_count = local_10;
  }
  else {
    snd_cd_close();
    local_10 = 0xffffffff;
  }
  return local_10;
}
#undef snd_cd_device_id
#undef snd_cd_track_count
#undef local_3c
#undef local_38
#undef local_34
#undef local_24
#undef local_20
#undef local_1c
#undef local_14
#undef local_10
#undef local_c

/* 005de6bd auto */
#define snd_midi_notify_callback (*(code * *)((u8 *)&g.d_006e5004))
void __cdecl snd_midi_fire_notify_callback(void)

{
  if (snd_midi_notify_callback != (code *)0x0) {
    (*snd_midi_notify_callback)();
  }
  return;
}
#undef snd_midi_notify_callback

/* 005de6fc auto */
#define snd_cd_notify_callback (*(iptr *)((u8 *)&g.d_006e5000))
void __cdecl snd_cd_set_notify_callback(iptr param_1)

{
  snd_cd_notify_callback = param_1;
  return;
}
#undef snd_cd_notify_callback

/* 005de714 auto */
#define snd_cd_notify_callback (*(code * *)((u8 *)&g.d_006e5000))
void __cdecl snd_cd_fire_notify_callback(void)

{
  if (snd_cd_notify_callback != (code *)0x0) {
    (*snd_cd_notify_callback)();
  }
  return;
}
#undef snd_cd_notify_callback

/* 005e1c70 auto */
#define avi_active_window (*(iptr *)((u8 *)&g.d_00638dd4))
void __cdecl avi_update_current_frame(void)

{
  avi_update_frame(avi_active_window);
  return;
}
#undef avi_active_window

/* 005e1c8e auto */
#define avi_active_window (*(iptr *)((u8 *)&g.d_00638dd4))
#define avi_audio_stream (*(i32 *)((u8 *)&g.d_00638dc8))
#define avi_decompressor (*(int *)((u8 *)&g.d_00638db0))
#define avi_file (*(i32 *)((u8 *)&g.d_00638dc0))
#define avi_file_loaded (*(i32 *)((u8 *)&g.d_00638dcc))
#define avi_frame_buffer (*(LPVOID *)((u8 *)&g.d_00638da8))
#define avi_frame_buffer_size (*(int *)((u8 *)&g.d_00638dac))
#define avi_frame_height (*(int *)((u8 *)&g.d_00638db8))
#define avi_frame_width (*(int *)((u8 *)&g.d_00638db4))
#define avi_playing (*(i32 *)((u8 *)&g.d_00638dd0))
#define avi_video_stream (*(i32 *)((u8 *)&g.d_00638dc4))
#define avi_view_rect_x (*(i32 *)((u8 *)&g.d_006e50c8))
#define avi_view_rect_y (*(i32 *)((u8 *)&g.d_006e50cc))
#define _DAT_00638dec (*(i32 *)((u8 *)&g.d_00638dec))
#define _DAT_006e5028 (*(i32 *)((u8 *)&g.d_006e5028))
#define _DAT_006e502c (*(i32 *)((u8 *)&g.d_006e502c))
#define _DAT_006e5030 (*(i32 *)((u8 *)&g.d_006e5030))
#define _DAT_006e5034 (*(i32 *)((u8 *)&g.d_006e5034))
#define _DAT_006e5038 (*(i32 *)((u8 *)&g.d_006e5038))
#define _DAT_006e503c (*(i32 *)((u8 *)&g.d_006e503c))
#define _DAT_006e5064 (*(i32 *)((u8 *)&g.d_006e5064))
#define _DAT_006e5098 (*(i32 *)((u8 *)&g.d_006e5098))
#define _DAT_006e509c (*(i32 *)((u8 *)&g.d_006e509c))
#define _DAT_006e50a0 (*(i32 *)((u8 *)&g.d_006e50a0))
#define _DAT_006e50a4 (*(i32 *)((u8 *)&g.d_006e50a4))
#define _DAT_006e50a8 (*(i32 *)((u8 *)&g.d_006e50a8))
#define _DAT_006e50ac (*(i32 *)((u8 *)&g.d_006e50ac))
#define _DAT_006e50bc (*(i32 *)((u8 *)&g.d_006e50bc))
#define _DAT_006e50d0 (*(i32 *)((u8 *)&g.d_006e50d0))
#define _DAT_006e50d4 (*(i32 *)((u8 *)&g.d_006e50d4))
#define _DAT_006e50d8 (*(i32 *)((u8 *)&g.d_006e50d8))
#define _DAT_006e50dc (*(i32 *)((u8 *)&g.d_006e50dc))
#define local_360 (*(i8 (*)[708])(frame_ + FRAME_OFF(0)))
#define local_9c (*(i8 (*)[4])(frame_ + FRAME_OFF(708)))
#define local_98 (*(i32 *)(frame_ + FRAME_OFF(712)))
#define local_88 (*(uint *)(frame_ + FRAME_OFF(728)))
#define local_84 (*(uint *)(frame_ + FRAME_OFF(732)))
#define local_74 (*(SIZE_T *)(frame_ + FRAME_OFF(748)))
#define local_10 (*(iptr *)(frame_ + FRAME_OFF(848)))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(852)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(856)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl avi_open_file(iptr param_1,i32 param_2)

{
  int iVar1;
  i32 uVar2;
  int iVar3;
  iptr iVar4;
  HGLOBAL pvVar5;
  i8 frame_[FRAME_OFF(864)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (avi_vfw_initialized == 0) {
    AVIFileInit();
    avi_vfw_initialized = 1;
  }
  avi_active_window = param_1;
  _DAT_006e5098 = 0x2c;
  _DAT_006e509c = 0x31345649;
  _DAT_006e50a8 = 2;
  _DAT_006e50a0 = 0x10002;
  _DAT_006e50a4 = 4;
  _DAT_006e50ac = 0;
  _DAT_006e50bc = 0;
  _DAT_006e5028 = 0x70;
  _DAT_006e502c = 0x31345649;
  _DAT_006e5038 = 2;
  _DAT_006e5030 = 0x10002;
  _DAT_006e5034 = 2;
  _DAT_006e5064 = &avi_view_rect_x;
  _DAT_006e503c = 0x80000008;
  avi_view_rect_x = 0;
  avi_view_rect_y = 0;
  _DAT_006e50d0 = 0;
  _DAT_006e50d4 = 0;
  local_8 = AVIFileOpenA(&avi_file,param_2,0,0);
  if (local_8 == 0) {
    local_8 = AVIFileGetStream(avi_file,&avi_video_stream,0x73646976,0);
    if (local_8 == 0) {
      iVar3 = 0;
      if (*(int *)(param_1 + 0x5a8) != 0) {
        local_8 = AVIFileGetStream(avi_file,&avi_audio_stream,0x73647561,0);
        if (local_8 == 0) {
          *(i32 *)(param_1 + 0x5b0) = 0;
          iVar1 = avi_audio_attach_stream((AviAudioAttachView *)(param_1 + 0x11c),avi_audio_stream);
          iVar3 = local_8;
          if (iVar1 == 0) {
            *(i32 *)(param_1 + 0x5a8) = 1;
          }
          else {
            *(i32 *)(param_1 + 0x5a8) = 0;
          }
        }
        else {
          *(i32 *)(param_1 + 0x5a8) = 0;
          iVar3 = local_8;
        }
      }
      local_8 = iVar3;
      local_c = 0x28;
      AVIStreamReadFormat(avi_video_stream,1,param_1 + 0x5c0,&local_c);
      AVIStreamInfoA(avi_video_stream,local_9c,0x8c);
      *(SIZE_T *)(param_1 + 0x5d4) = local_74;
      _DAT_006e50d8 = local_84 / local_88;
      avi_decompressor = ICLocate(0x63646976,local_98,param_1 + 0x5c0,0,2);
      if (avi_decompressor == 0) {
        avi_close(param_1);
        local_8 = 0;
      }
      else {
        uVar2 = AVIStreamStart(avi_video_stream);
        *(i32 *)(param_1 + 0xa10) = uVar2;
        iVar3 = AVIStreamLength(avi_video_stream);
        *(int *)(param_1 + 0xa14) = *(int *)(param_1 + 0xa10) + iVar3 - 1;
        *(i32 *)(param_1 + 0xa18) = *(i32 *)(param_1 + 0xa10);
        FUN_005f2110(param_1 + 0x5e8,param_1 + 0x5c0,0x28);
        *(i32 *)(param_1 + 0x5f8) = 0;
        *(i16 *)(param_1 + 0x5f6) = 8;
        *(i32 *)(param_1 + 0x5fc) = 0;
        *(i32 *)(param_1 + 0x608) = 0x100;
        avi_frame_width = *(int *)(param_1 + 0x5c4);
        avi_frame_height = *(int *)(param_1 + 0x5c8);
        iVar4 = surface_get_dib((DibSurface *)param_1);
        iVar3 = dib_is_top_down(iVar4);
        if (iVar3 != 0) {
          *(int *)(param_1 + 0x5f0) = -*(int *)(param_1 + 0x5f0);
        }
        if (*(int *)(param_1 + 0x5a0) == 0) {
          wnd_resize_clamped((C_004083b0_4 *)param_1,avi_frame_width,avi_frame_height);
        }
        else {
          wnd_resize_clamped((C_004083b0_4 *)param_1,avi_frame_width * 2,avi_frame_height * 2);
        }
        if (local_74 == 0) {
          iVar3 = (uint)*(ushort *)(param_1 + 0x5ce) * *(int *)(param_1 + 0x5c4) *
                  *(int *)(param_1 + 0x5c8);
          pvVar5 = GlobalAlloc(0x40,(int)(iVar3 + (iVar3 >> 0x1f & 7U)) >> 3);
          avi_frame_buffer = GlobalLock(pvVar5);
        }
        else {
          pvVar5 = GlobalAlloc(0x40,local_74);
          avi_frame_buffer = GlobalLock(pvVar5);
        }
        if (avi_frame_buffer == (LPVOID)0x0) {
          avi_close(param_1);
          local_8 = 0;
        }
        else {
          local_8 = avi_ic_decompress_ex_query(avi_decompressor,0,param_1 + 0x5c0,0,0,0,
                                 *(i32 *)(param_1 + 0x5c4),*(i32 *)(param_1 + 0x5c8),
                                 param_1 + 0x5e8,0,0,0,*(i32 *)(param_1 + 0x5c4),
                                 *(i32 *)(param_1 + 0x5c8));
          if (local_8 == 0) {
            ICSendMessage(avi_decompressor,0x401e,param_1 + 0x5c0,param_1 + 0x5e8);
            for (local_10 = 0; local_10 < 0xec; local_10++) {
              local_360[local_10 * 3] = *(i8 *)(param_1 + 0x63a + local_10 * 4);
              local_360[local_10 * 3 + 1] = *(i8 *)(param_1 + 0x639 + local_10 * 4);
              local_360[local_10 * 3 + 2] = *(i8 *)(param_1 + 0x638 + local_10 * 4);
            }
            palette_set_rgb
                      ((GamePalette *)(param_1 + 0x124),10,0xec,(iptr)local_360);
            ICSendMessage(avi_decompressor,0x401d,param_1 + 0x5e8,0);
            local_8 = avi_ic_decompress_ex_begin(avi_decompressor,0,param_1 + 0x5c0,0,0,0,
                                   *(i32 *)(param_1 + 0x5c4),*(i32 *)(param_1 + 0x5c8)
                                   ,param_1 + 0x5e8,0,0,0,*(i32 *)(param_1 + 0x5c4),
                                   *(i32 *)(param_1 + 0x5c8));
            if (local_8 == 0) {
              avi_file_loaded = 1;
              avi_playing = 0;
              if (*(int *)(param_1 + 0x5a4) == 0) {
                avi_restart_decompress(param_1,0);
              }
              else {
                avi_restart_decompress(param_1,1);
              }
              iVar3 = (uint)*(ushort *)(param_1 + 0x5ce) * *(int *)(param_1 + 0x5c4) *
                      *(int *)(param_1 + 0x5c8);
              avi_frame_buffer_size = (int)(iVar3 + (iVar3 >> 0x1f & 7U)) >> 3;
              _DAT_00638dec = 0;
              _DAT_006e50dc = 0;
              local_8 = 0;
            }
            else {
              avi_close(param_1);
            }
          }
          else {
            avi_close(param_1);
          }
        }
      }
    }
    else {
      avi_close(param_1);
    }
  }
  else {
    avi_close(param_1);
  }
  return local_8;
}
#undef avi_active_window
#undef avi_audio_stream
#undef avi_decompressor
#undef avi_file
#undef avi_file_loaded
#undef avi_frame_buffer
#undef avi_frame_buffer_size
#undef avi_frame_height
#undef avi_frame_width
#undef avi_playing
#undef avi_video_stream
#undef avi_view_rect_x
#undef avi_view_rect_y
#undef _DAT_00638dec
#undef _DAT_006e5028
#undef _DAT_006e502c
#undef _DAT_006e5030
#undef _DAT_006e5034
#undef _DAT_006e5038
#undef _DAT_006e503c
#undef _DAT_006e5064
#undef _DAT_006e5098
#undef _DAT_006e509c
#undef _DAT_006e50a0
#undef _DAT_006e50a4
#undef _DAT_006e50a8
#undef _DAT_006e50ac
#undef _DAT_006e50bc
#undef _DAT_006e50d0
#undef _DAT_006e50d4
#undef _DAT_006e50d8
#undef _DAT_006e50dc
#undef local_360
#undef local_9c
#undef local_98
#undef local_88
#undef local_84
#undef local_74
#undef local_10
#undef local_c
#undef local_8

/* 005e22ed: written by hand in src/game/fixups.c */

/* 005e250c auto */
#define local_38 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define local_34 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_30 (*(i32 *)(frame_ + FRAME_OFF(8)))
#define local_2c (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_28 (*(i32 *)(frame_ + FRAME_OFF(16)))
#define local_24 (*(i32 *)(frame_ + FRAME_OFF(20)))
#define local_20 (*(i32 *)(frame_ + FRAME_OFF(24)))
#define local_1c (*(i32 *)(frame_ + FRAME_OFF(28)))
#define local_18 (*(i32 *)(frame_ + FRAME_OFF(32)))
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(36)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(40)))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(44)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(48)))
i32
__stdcall avi_ic_decompress_ex_begin(i32 param_1,i32 param_2,iptr param_3,i32 param_4,
            i32 param_5,i32 param_6,i32 param_7,i32 param_8,iptr param_9
            ,i32 param_10,i32 param_11,i32 param_12,i32 param_13,
            i32 param_14)

{
  i32 uVar1;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_38 = param_2;
  local_34 = param_3;
  local_30 = param_4;
  local_14 = param_5;
  local_10 = param_6;
  local_c = param_7;
  local_8 = param_8;
  local_2c = param_9;
  local_28 = param_10;
  local_24 = param_11;
  local_20 = param_12;
  local_1c = param_13;
  local_18 = param_14;
  uVar1 = ICSendMessage(param_1,0x403c,&local_38,0x34);
  return uVar1;
}
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

/* 005e2583 auto */
#define local_38 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define local_34 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_30 (*(i32 *)(frame_ + FRAME_OFF(8)))
#define local_2c (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_28 (*(i32 *)(frame_ + FRAME_OFF(16)))
#define local_24 (*(i32 *)(frame_ + FRAME_OFF(20)))
#define local_20 (*(i32 *)(frame_ + FRAME_OFF(24)))
#define local_1c (*(i32 *)(frame_ + FRAME_OFF(28)))
#define local_18 (*(i32 *)(frame_ + FRAME_OFF(32)))
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(36)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(40)))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(44)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(48)))
i32
__stdcall avi_ic_decompress_ex_query(i32 param_1,i32 param_2,iptr param_3,i32 param_4,
            i32 param_5,i32 param_6,i32 param_7,i32 param_8,iptr param_9
            ,i32 param_10,i32 param_11,i32 param_12,i32 param_13,
            i32 param_14)

{
  i32 uVar1;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_38 = param_2;
  local_34 = param_3;
  local_30 = param_4;
  local_14 = param_5;
  local_10 = param_6;
  local_c = param_7;
  local_8 = param_8;
  local_2c = param_9;
  local_28 = param_10;
  local_24 = param_11;
  local_20 = param_12;
  local_1c = param_13;
  local_18 = param_14;
  uVar1 = ICSendMessage(param_1,0x403d,&local_38,0x34);
  return uVar1;
}
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

/* 005e2675 auto */
#define avi_file_loaded (*(int *)((u8 *)&g.d_00638dcc))
#define avi_frame_needs_blit (*(i32 *)((u8 *)&g.d_00638de8))
#define avi_idle_update_enabled (*(i32 *)((u8 *)&g.d_00637efc))
#define avi_playing (*(int *)((u8 *)&g.d_00638dd0))
void __cdecl avi_play_pause(iptr param_1)

{
  if ((param_1 != 0) && (avi_file_loaded != 0)) {
    if (*(int *)(param_1 + 0x5a8) != 0) {
      *(i32 *)(param_1 + 0x5b0) = 0;
    }
    *(i32 *)(param_1 + 0x5ac) = 1;
    if (avi_playing != 0) {
      avi_idle_update_enabled = 0;
      avi_frame_needs_blit = 0;
      avi_playing = 0;
    }
  }
  return;
}
#undef avi_file_loaded
#undef avi_frame_needs_blit
#undef avi_idle_update_enabled
#undef avi_playing

/* 005e2799 auto */
#define avi_active_window (*(i32 *)((u8 *)&g.d_00638dd4))
#define avi_audio_stream (*(int *)((u8 *)&g.d_00638dc8))
#define avi_decompressor (*(int *)((u8 *)&g.d_00638db0))
#define avi_file (*(int *)((u8 *)&g.d_00638dc0))
#define avi_frame_buffer (*(LPCVOID *)((u8 *)&g.d_00638da8))
#define avi_frame_buffer_size (*(i32 *)((u8 *)&g.d_00638dac))
#define avi_frame_height (*(i32 *)((u8 *)&g.d_00638db8))
#define avi_frame_width (*(i32 *)((u8 *)&g.d_00638db4))
#define avi_video_stream (*(int *)((u8 *)&g.d_00638dc4))
void __cdecl avi_close(iptr param_1)

{
  HGLOBAL pvVar1;
  
  if (param_1 != 0) {
    avi_play_pause(param_1);
    if (avi_decompressor != 0) {
      ICClose(avi_decompressor);
      avi_decompressor = 0;
    }
    if (avi_audio_stream != 0) {
      AVIStreamRelease(avi_audio_stream);
      avi_audio_stream = 0;
    }
    if (avi_video_stream != 0) {
      AVIStreamRelease(avi_video_stream);
      avi_video_stream = 0;
    }
    if (avi_file != 0) {
      AVIFileRelease(avi_file);
      avi_file = 0;
    }
    if (avi_vfw_initialized != 0) {
      AVIFileExit();
      avi_vfw_initialized = 0;
    }
    if (avi_frame_buffer != (LPCVOID)0x0) {
      pvVar1 = GlobalHandle(avi_frame_buffer);
      GlobalUnlock(pvVar1);
      pvVar1 = GlobalHandle(avi_frame_buffer);
      GlobalFree(pvVar1);
      avi_frame_buffer = (LPCVOID)0x0;
    }
    avi_frame_buffer_size = 0;
    avi_frame_width = 0;
    avi_frame_height = 0;
    avi_active_window = 0;
  }
  return;
}
#undef avi_active_window
#undef avi_audio_stream
#undef avi_decompressor
#undef avi_file
#undef avi_frame_buffer
#undef avi_frame_buffer_size
#undef avi_frame_height
#undef avi_frame_width
#undef avi_video_stream

/* 005e28cd auto */
#define avi_file_loaded (*(int *)((u8 *)&g.d_00638dcc))
#define avi_playing (*(int *)((u8 *)&g.d_00638dd0))
#define avi_video_stream (*(i32 *)((u8 *)&g.d_00638dc4))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(0)))
void __cdecl avi_seek_frame(iptr param_1,uint param_2,int param_3)

{
  i32 uVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((param_1 != 0) && (avi_file_loaded != 0)) {
    if (avi_playing != 0) {
      avi_play_pause(param_1);
    }
    uVar1 = AVIStreamFindSample(avi_video_stream,param_2,0x14);
    *(i32 *)(param_1 + 0xa18) = uVar1;
    while( true ) {
      if ((int)param_2 < 0) {
        local_8 = 0;
      }
      else {
        local_8 = param_2;
      }
      if (local_8 <= *(uint *)(param_1 + 0xa18)) break;
      avi_decode_frame(param_1,0x80000000);
    }
    avi_decode_frame(param_1,0);
    if (param_3 != 0) {
      avi_update_frame(param_1);
    }
  }
  return;
}
#undef avi_file_loaded
#undef avi_playing
#undef avi_video_stream
#undef local_8

/* 005e2997 auto */
#define avi_decompressor (*(i32 *)((u8 *)&g.d_00638db0))
#define avi_file_loaded (*(int *)((u8 *)&g.d_00638dcc))
#define avi_frame_buffer (*(i32 *)((u8 *)&g.d_00638da8))
#define avi_frame_buffer_size (*(i32 *)((u8 *)&g.d_00638dac))
#define avi_frame_height (*(int *)((u8 *)&g.d_00638db8))
#define avi_frame_width (*(int *)((u8 *)&g.d_00638db4))
#define avi_playing (*(int *)((u8 *)&g.d_00638dd0))
#define avi_video_stream (*(i32 *)((u8 *)&g.d_00638dc4))
#define local_5c (*(CHAR (*)[80])(frame_ + FRAME_OFF(4)))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(84)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(88)))
int __cdecl avi_decode_frame(iptr param_1,int param_2)

{
  i32 uVar1;
  i32 uVar2;
  i32 uVar3;
  int iVar4;
  int iVar5;
  i8 frame_[FRAME_OFF(96)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  local_c = 0;
  if ((param_1 == 0) || (avi_file_loaded == 0)) {
    local_8 = 1;
  }
  else {
    if ((*(int *)(param_1 + 0x5a4) != 0) && (param_2 == 0)) {
      surface_blit((DibSurface *)(param_1 + 0x558),param_1,ADDR(0x638dd8, ((u8 *)&g.d_00638dd8)),ADDR(0x638dd8, ((u8 *)&g.d_00638dd8)));
    }
    local_8 = AVIStreamRead(avi_video_stream,*(i32 *)(param_1 + 0xa18),1,avi_frame_buffer,
                            avi_frame_buffer_size,&local_c,0);
    if (local_8 == 0) {
      *(i32 *)(param_1 + 0x5d4) = local_c;
      if (*(int *)(param_1 + 0x5a0) == 0) {
        uVar3 = 0;
        uVar2 = 0;
        iVar5 = avi_frame_width;
        iVar4 = avi_frame_height;
        uVar1 = surface_get_bits((DibSurface *)param_1);
        local_8 = avi_ic_decompress_ex(avi_decompressor,param_2,param_1 + 0x5c0,avi_frame_buffer,0,0,avi_frame_width,
                               avi_frame_height,param_1 + 0x5e8,uVar1,uVar2,uVar3,iVar5,iVar4);
      }
      else {
        *(int *)(param_1 + 0x5f0) = *(int *)(param_1 + 0x5f0) << 1;
        *(int *)(param_1 + 0x5ec) = *(int *)(param_1 + 0x5ec) << 1;
        iVar5 = avi_frame_height * 2;
        iVar4 = avi_frame_width * 2;
        uVar3 = 0;
        uVar2 = 0;
        uVar1 = surface_get_bits((DibSurface *)param_1);
        local_8 = avi_ic_decompress_ex(avi_decompressor,param_2,param_1 + 0x5c0,avi_frame_buffer,0,0,avi_frame_width,
                               avi_frame_height,param_1 + 0x5e8,uVar1,uVar2,uVar3,iVar4,iVar5);
        *(int *)(param_1 + 0x5f0) = *(int *)(param_1 + 0x5f0) >> 1;
        *(int *)(param_1 + 0x5ec) = *(int *)(param_1 + 0x5ec) >> 1;
      }
      if ((local_8 != 0) && (local_8 != 1)) {
        wsprintfA(local_5c,s_ICDecompressEx_returned__ld_00638df0,local_8);
        MessageBoxA((HWND)0x0,local_5c,s_Get_Frame_00638e0c,0);
      }
      if ((*(int *)(param_1 + 0xa20) != 0) &&
         (*(int *)(param_1 + 0xa20) == *(int *)(param_1 + 0xa18))) {
        *(i32 *)(param_1 + 0xa20) = 0;
        avi_player_call_cue_callback((AviPlayerCueCbCallView *)param_1);
      }
      if ((*(uint *)(param_1 + 0xa14) < *(uint *)(param_1 + 0xa18)) && (avi_playing != 0)) {
        if (*(int *)(param_1 + 0xa24) == 0) {
          avi_play_pause(param_1);
          avi_player_call_end_callback((AviPlayerEndCbCallView *)param_1);
          local_8 = 0;
        }
        else {
          avi_seek_frame(param_1,*(i32 *)(param_1 + 0xa10),0);
          avi_play_start(param_1);
          local_8 = 0;
        }
      }
      else {
        *(int *)(param_1 + 0xa18) = *(int *)(param_1 + 0xa18) + 1;
        if (param_2 != 0) {
          local_8 = 1;
        }
      }
    }
  }
  return local_8;
}
#undef avi_decompressor
#undef avi_file_loaded
#undef avi_frame_buffer
#undef avi_frame_buffer_size
#undef avi_frame_height
#undef avi_frame_width
#undef avi_playing
#undef avi_video_stream
#undef local_5c
#undef local_c
#undef local_8

/* 005e2c5a auto */
#define local_38 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define local_34 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_30 (*(i32 *)(frame_ + FRAME_OFF(8)))
#define local_2c (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_28 (*(i32 *)(frame_ + FRAME_OFF(16)))
#define local_24 (*(i32 *)(frame_ + FRAME_OFF(20)))
#define local_20 (*(i32 *)(frame_ + FRAME_OFF(24)))
#define local_1c (*(i32 *)(frame_ + FRAME_OFF(28)))
#define local_18 (*(i32 *)(frame_ + FRAME_OFF(32)))
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(36)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(40)))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(44)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(48)))
i32
__stdcall avi_ic_decompress_ex(i32 param_1,i32 param_2,iptr param_3,i32 param_4,
            i32 param_5,i32 param_6,i32 param_7,i32 param_8,iptr param_9
            ,i32 param_10,i32 param_11,i32 param_12,i32 param_13,
            i32 param_14)

{
  i32 uVar1;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_38 = param_2;
  local_34 = param_3;
  local_30 = param_4;
  local_14 = param_5;
  local_10 = param_6;
  local_c = param_7;
  local_8 = param_8;
  local_2c = param_9;
  local_28 = param_10;
  local_24 = param_11;
  local_20 = param_12;
  local_1c = param_13;
  local_18 = param_14;
  uVar1 = ICSendMessage(param_1,0x403e,&local_38,0x34);
  return uVar1;
}
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

/* 005e2cd1 auto */
#define avi_file_loaded (*(int *)((u8 *)&g.d_00638dcc))
#define avi_frame_needs_blit (*(uint *)((u8 *)&g.d_00638de8))
#define avi_playing (*(int *)((u8 *)&g.d_00638dd0))
#define avi_video_stream (*(i32 *)((u8 *)&g.d_00638dc4))
#define avi_view_rect_x (*(int *)((u8 *)&g.d_006e50c8))
#define avi_view_rect_y (*(int *)((u8 *)&g.d_006e50cc))
#define _DAT_00638dbc (*(i32 *)((u8 *)&g.d_00638dbc))
#define _DAT_00638dec (*(i32 *)((u8 *)&g.d_00638dec))
#define _DAT_006e50d0 (*(i32 *)((u8 *)&g.d_006e50d0))
#define _DAT_006e50d4 (*(i32 *)((u8 *)&g.d_006e50d4))
#define local_20 (*(uint *)(frame_ + FRAME_OFF(0)))
#define local_1c (*(RECT *)(frame_ + FRAME_OFF(4)))
#define local_c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(DWORD *)(frame_ + FRAME_OFF(24)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl avi_update_frame(iptr param_1)

{
  int iVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 == 0) {
    return;
  }
  if (avi_file_loaded == 0) {
    return;
  }
  if (avi_playing != 0) {
    if (*(int *)(param_1 + 0x5a8) == 0) {
      local_8 = timeGetTime();
      iVar1 = AVIStreamTimeToSample(avi_video_stream,local_8 - _DAT_00638dbc);
      local_20 = *(int *)(param_1 + 0xa10) + iVar1;
      if (local_20 < *(uint *)(param_1 + 0xa18)) {
        return;
      }
      if (*(uint *)(param_1 + 0xa14) < local_20) {
        if (*(int *)(param_1 + 0xa24) == 0) {
          avi_play_pause(param_1);
          avi_player_call_end_callback((AviPlayerEndCbCallView *)param_1);
          return;
        }
        avi_seek_frame(param_1,*(i32 *)(param_1 + 0xa10),0);
        avi_play_start(param_1);
        return;
      }
    }
    else {
      iVar1 = avi_audio_is_playing((AviAudioPlayingView *)(param_1 + 0x11c));
      if (iVar1 == 0) {
        if (*(int *)(param_1 + 0xa24) == 0) {
          avi_play_pause(param_1);
          avi_player_call_end_callback((AviPlayerEndCbCallView *)param_1);
          return;
        }
        avi_seek_frame(param_1,*(i32 *)(param_1 + 0xa10),0);
        avi_play_start(param_1);
        return;
      }
      uVar2 = avi_audio_get_position_ms((void *)(param_1 + 0x11c));
      iVar1 = AVIStreamTimeToSample(avi_video_stream,uVar2);
      local_20 = *(int *)(param_1 + 0xa10) + iVar1;
      if ((*(int *)(param_1 + 0x5ac) == 0) || (local_20 < *(uint *)(param_1 + 0xa18))) {
        snd_avi_stream_feed(0x40);
        _DAT_00638dec++;
        return;
      }
    }
    if (avi_frame_needs_blit != 0) {
      if (*(int *)(param_1 + 0x5a4) == 0) {
        wnd_blit_surface((DibSurface *)param_1);
      }
      else {
        local_1c.left = avi_view_rect_x;
        local_1c.top = avi_view_rect_y;
        local_1c.right = avi_view_rect_x + _DAT_006e50d0;
        local_1c.bottom = avi_view_rect_y + _DAT_006e50d4;
        UnionRect(&local_1c,&local_1c,(RECT *)&avi_blit_union_left);
        wnd_blit_surface_rect((DibSurface *)param_1,(iptr)&local_1c);
        avi_blit_union_left = local_1c.left;
        avi_blit_union_top = local_1c.top;
        avi_blit_union_right = local_1c.right;
        avi_blit_union_bottom = local_1c.bottom;
      }
    }
    if (*(uint *)(param_1 + 0xa18) < local_20) {
      local_c = *(int *)(param_1 + 0xa18);
      do {
        iVar1 = local_c;
        local_c++;
        local_c = AVIStreamFindSample(avi_video_stream,local_c,0x11);
        if ((int)local_20 <= local_c) break;
      } while (local_c != -1);
      if (*(int *)(param_1 + 0xa18) == iVar1) {
        if ((local_c != -1) && (local_c - local_20 < local_20 - *(int *)(param_1 + 0xa18))) {
          *(int *)(param_1 + 0xa18) = local_c;
        }
      }
      else if ((local_c == -1) || ((int)(local_20 - iVar1) <= (int)(local_c - local_20))) {
        if (iVar1 != -1) {
          *(int *)(param_1 + 0xa18) = iVar1;
        }
      }
      else {
        *(int *)(param_1 + 0xa18) = local_c;
      }
      while ((*(uint *)(param_1 + 0xa18) < local_20 &&
             (*(uint *)(param_1 + 0xa18) < *(int *)(param_1 + 0xa14) - 1U))) {
        avi_decode_frame(param_1,0x80000000);
      }
    }
  }
  if ((avi_playing != 0) && (*(int *)(param_1 + 0x5a8) != 0)) {
    snd_avi_stream_feed(0x40);
    _DAT_00638dec++;
  }
  iVar1 = avi_decode_frame(param_1,0);
  avi_frame_needs_blit = (uint)(iVar1 == 0);
  return;
}
#undef avi_file_loaded
#undef avi_frame_needs_blit
#undef avi_playing
#undef avi_video_stream
#undef avi_view_rect_x
#undef avi_view_rect_y
#undef _DAT_00638dbc
#undef _DAT_00638dec
#undef _DAT_006e50d0
#undef _DAT_006e50d4
#undef local_20
#undef local_1c
#undef local_c
#undef local_8

/* 005e30a1 auto */
#define avi_decompressor (*(i32 *)((u8 *)&g.d_00638db0))
#define avi_file_loaded (*(int *)((u8 *)&g.d_00638dcc))
#define local_2d0 (*(i8 (*)[708])(frame_ + FRAME_OFF(0)))
#define local_c (*(int *)(frame_ + FRAME_OFF(708)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(712)))
void __cdecl avi_apply_palette(iptr param_1,GamePalette *param_2)

{
  i8 frame_[FRAME_OFF(720)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((param_1 != 0) && (avi_file_loaded != 0)) {
    ICSendMessage(avi_decompressor,0x403f,0,0);
    palette_get_rgb(param_2,(iptr)local_2d0,0,0xec);
    for (local_c = 0; local_c < 0xec; local_c++) {
      *(i8 *)(param_1 + 0x610 + local_c * 4) = local_2d0[local_c * 3 + 2];
      *(i8 *)(param_1 + 0x611 + local_c * 4) = local_2d0[local_c * 3 + 1];
      *(i8 *)(param_1 + 0x612 + local_c * 4) = local_2d0[local_c * 3];
      *(i8 *)(param_1 + 0x613 + local_c * 4) = 0;
    }
    ICSendMessage(avi_decompressor,0x401d,param_1 + 0x5e8,0);
    if (*(int *)(param_1 + 0x5a0) == 0) {
      local_8 = avi_ic_decompress_ex_begin(avi_decompressor,0,param_1 + 0x5c0,0,0,0,*(i32 *)(param_1 + 0x5c4),
                             *(i32 *)(param_1 + 0x5c8),param_1 + 0x5e8,0,0,0,
                             *(i32 *)(param_1 + 0x5c4),*(i32 *)(param_1 + 0x5c8));
    }
    else {
      *(int *)(param_1 + 0x5f0) = *(int *)(param_1 + 0x5f0) << 1;
      *(int *)(param_1 + 0x5ec) = *(int *)(param_1 + 0x5ec) << 1;
      local_8 = avi_ic_decompress_ex_begin(avi_decompressor,0,param_1 + 0x5c0,0,0,0,*(i32 *)(param_1 + 0x5c4),
                             *(i32 *)(param_1 + 0x5c8),param_1 + 0x5e8,0,0,0,
                             *(int *)(param_1 + 0x5c4) * 2,*(int *)(param_1 + 0x5c8) * 2);
      *(int *)(param_1 + 0x5f0) = *(int *)(param_1 + 0x5f0) / 2;
      *(int *)(param_1 + 0x5ec) = *(int *)(param_1 + 0x5ec) / 2;
    }
    if (local_8 != 0) {
      avi_file_loaded = 0;
    }
  }
  return;
}
#undef avi_decompressor
#undef avi_file_loaded
#undef local_2d0
#undef local_c
#undef local_8

/* 005e32b2 auto */
#define avi_decompressor (*(i32 *)((u8 *)&g.d_00638db0))
#define avi_file_loaded (*(int *)((u8 *)&g.d_00638dcc))
#define avi_frame_height (*(int *)((u8 *)&g.d_00638db8))
#define avi_frame_width (*(int *)((u8 *)&g.d_00638db4))
#define _DAT_006e503c (*(i32 *)((u8 *)&g.d_006e503c))
#define _DAT_006e50ac (*(i32 *)((u8 *)&g.d_006e50ac))
#define local_2c (*(tagRECT *)(frame_ + FRAME_OFF(4)))
#define local_1c (*(tagRECT *)(frame_ + FRAME_OFF(20)))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(36)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(40)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl avi_restart_decompress(iptr param_1,int param_2)

{
  int yBottom;
  int xRight;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((param_1 != 0) && (avi_file_loaded != 0)) {
    ICSendMessage(avi_decompressor,0x403f,0,0);
    if (param_2 == 0) {
      _DAT_006e50ac = 0;
    }
    else {
      _DAT_006e50ac = 0x80000004;
    }
    _DAT_006e503c = 0x80000008;
    ICSendMessage(avi_decompressor,0x5001,&avi_indeo_seq_opts,0x2c);
    ICSendMessage(avi_decompressor,0x5001,&avi_indeo_frame_opts,0x70);
    if (*(int *)(param_1 + 0x5a0) == 0) {
      local_8 = avi_ic_decompress_ex_begin(avi_decompressor,0,param_1 + 0x5c0,0,0,0,avi_frame_width,avi_frame_height,
                             param_1 + 0x5e8,0,0,0,avi_frame_width,avi_frame_height);
    }
    else {
      *(int *)(param_1 + 0x5f0) = *(int *)(param_1 + 0x5f0) << 1;
      *(int *)(param_1 + 0x5ec) = *(int *)(param_1 + 0x5ec) << 1;
      local_8 = avi_ic_decompress_ex_begin(avi_decompressor,0,param_1 + 0x5c0,0,0,0,avi_frame_width,avi_frame_height,
                             param_1 + 0x5e8,0,0,0,avi_frame_width * 2,avi_frame_height * 2);
      *(int *)(param_1 + 0x5f0) = *(int *)(param_1 + 0x5f0) >> 1;
      *(int *)(param_1 + 0x5ec) = *(int *)(param_1 + 0x5ec) >> 1;
    }
    if (local_8 != 0) {
      avi_file_loaded = 0;
    }
    if (param_2 == 0) {
      surface_create((DibSurface *)(param_1 + 0x558),0,0);
    }
    else {
      surface_create((DibSurface *)(param_1 + 0x558),avi_frame_width,avi_frame_height);
      yBottom = surface_get_height((DibSurface *)param_1);
      xRight = surface_get_width((DibSurface *)param_1);
      SetRect(&local_1c,0,0,xRight,yBottom);
      local_2c.left = local_1c.left;
      local_2c.top = local_1c.top;
      local_2c.right = local_1c.right;
      local_2c.bottom = local_1c.bottom;
      OffsetRect(&local_2c,*(int *)(param_1 + 0x5b8),*(int *)(param_1 + 0x5bc));
      if (*(int *)(param_1 + 0x5b4) != 0) {
        surface_blit
                  (*(DibSurface **)(param_1 + 0x5b4),param_1 + 0x558,(iptr)&local_2c,
                   (iptr)&local_1c);
      }
      if (avi_file_loaded != 0) {
        surface_blit
                  ((DibSurface *)(param_1 + 0x558),param_1,(iptr)&local_1c,(iptr)&local_1c);
        local_c = *(i32 *)(param_1 + 0xa18);
        avi_seek_frame(param_1,local_c,0);
        wnd_blit_surface((DibSurface *)param_1);
      }
    }
  }
  return;
}
#undef avi_decompressor
#undef avi_file_loaded
#undef avi_frame_height
#undef avi_frame_width
#undef _DAT_006e503c
#undef _DAT_006e50ac
#undef local_2c
#undef local_1c
#undef local_c
#undef local_8

/* 005e3550 auto */
void __thiscall avi_player_call_end_callback(AviPlayerEndCbCallView *this)

{
  if (this->on_end != 0) {
    (*(code *)this->on_end)();
  }
  return;
}

/* 005e3580 auto */
void __thiscall avi_player_call_cue_callback(AviPlayerCueCbCallView *this)

{
  if (this->on_cue != 0) {
    (*(code *)this->on_cue)();
  }
  return;
}

/* 005ec317 auto */
#define wnd_active_child (*(WndOnMciDoneView * *)((u8 *)&g.d_00637ea4))
#define local_34 (*(i8 (*)[4])(frame_ + FRAME_OFF(4)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_2c (*(uptr *)(frame_ + FRAME_OFF(12)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_24 (*(iptr *)(frame_ + FRAME_OFF(20)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(28)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_14 (*(WndOnMciDoneView * *)(frame_ + FRAME_OFF(36)))
#define local_10 (*(iptr *)(frame_ + FRAME_OFF(40)))
#define local_c (*(int *)(frame_ + FRAME_OFF(44)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(48)))
i32 __stdcall moviewnd_wndproc(HWND param_1,uint param_2,uint param_3,uint param_4)

{
  short sVar1;
  i32 uVar2;
  iptr iVar3;
  WndBase *pCVar4;
  BOOL BVar5;
  int iVar6;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_14 = (WndOnMciDoneView *)GetWindowLongA(param_1,4);
  if (local_14 == (WndOnMciDoneView *)0x0) {
    uVar2 = wnd_base_wndproc(param_1,param_2,param_3,param_4);
    return uVar2;
  }
  if (param_2 < 0x11) {
    if (param_2 != 0x10) {
      switch(param_2) {
      case 3:
        wnd_active_child = local_14;
        wnd_call_move
                  ((WndOnMoveView *)(local_14->pad_4 + 0xc),param_4 & 0xffff,param_4 >> 0x10);
        uVar2 = wnd_base_wndproc(param_1,param_2,param_3,param_4);
        return uVar2;
      default:
        goto switchD_005ecda6_caseD_4;
      case 5:
switchD_005ecda6_caseD_5:
        wnd_active_child = local_14;
        BVar5 = IsIconic(param_1);
        if (BVar5 == 0) {
          wnd_on_size_nop(local_14,param_4 & 0xffff,param_4 >> 0x10);
          wnd_call_size((WndOnSizeView *)(local_14->pad_4 + 0xc),param_3);
        }
        uVar2 = wnd_base_wndproc(param_1,param_2,param_3,param_4);
        return uVar2;
      case 6:
        goto switchD_005ecda6_caseD_6;
      case 7:
        wnd_active_child = local_14;
        wnd_call_setfocus((WndOnSetFocusView *)(local_14->pad_4 + 0xc));
        return 0;
      }
    }
    wnd_active_child = local_14;
    iVar6 = wnd_call_close((WndOnCloseView *)(local_14->pad_4 + 0xc));
    if (iVar6 != 0) {
      uVar2 = wnd_base_wndproc(param_1,0x10,param_3,param_4);
      return uVar2;
    }
  }
  else {
    if (param_2 < 0x45) {
      if (param_2 == 0x44) {
        wnd_active_child = local_14;
        wnd_call_msg44((WndOnMsg44View *)(local_14->pad_4 + 0xc),param_4 & 0xffff);
        return 1;
      }
      if (param_2 == 0x24) {
        local_2c = param_4;
        iVar3 = wnd_get_window((WndBase *)local_14);
        local_30 = wnd_obj_frame_height(iVar3);
        iVar3 = wnd_get_window((WndBase *)local_14);
        local_28 = wnd_obj_frame_width(iVar3);
        wnd_get_min_size((WndMinSizeView *)local_14,(iptr)&local_1c,(iptr)&local_20);
        wnd_get_max_size((WndMaxSizeView *)local_14,(iptr)&local_8,(iptr)&local_c);
        *(int *)(local_2c + 0x20) = local_28 + local_8;
        *(int *)(local_2c + 0x24) = local_30 + local_c;
        *(int *)(local_2c + 0x18) = local_28 + local_1c;
        *(int *)(local_2c + 0x1c) = local_30 + local_20;
        return 0;
      }
switchD_005ecda6_caseD_4:
      uVar2 = wnd_base_wndproc(param_1,param_2,param_3,param_4);
      return uVar2;
    }
    if (param_2 < 0x112) {
      if (param_2 == 0x111) {
        wnd_active_child = local_14;
        return 0;
      }
      if (param_2 == 0x100) {
        wnd_active_child = local_14;
        uVar2 = input_map_vkey(param_3);
        wnd_call_keydown_pre((WndOnKeyDownPreView *)(local_14->pad_4 + 0xc),uVar2);
        uVar2 = input_map_vkey(param_3);
        wnd_call_keydown((WndOnKeyDownView *)(local_14->pad_4 + 0xc),uVar2);
        return 0;
      }
      if (param_2 == 0x101) {
        wnd_active_child = local_14;
        uVar2 = input_map_vkey(param_3);
        wnd_call_keyup((WndOnKeyUpView *)(local_14->pad_4 + 0xc),uVar2);
        return 0;
      }
      if (param_2 == 0x102) {
        wnd_active_child = local_14;
        wnd_call_char((WndOnCharView *)(local_14->pad_4 + 0xc),param_3 & 0xff);
        return 0;
      }
      goto switchD_005ecda6_caseD_4;
    }
    if (param_2 < 0x201) {
      if (param_2 == 0x200) {
        wnd_active_child = local_14;
        wnd_call_mousemove
                  ((WndOnMouseMoveView *)(local_14->pad_4 + 0xc),param_4 & 0xffff,param_4 >> 0x10);
        return 0;
      }
      if (param_2 == 0x112) {
        if (param_3 == 0xf020) {
          wnd_active_child = local_14;
          wnd_call_minimize((WndOnMinimizeView *)(local_14->pad_4 + 0xc));
        }
        else {
          wnd_active_child = local_14;
          if (param_3 == 0xf120) {
            wnd_call_restore((WndOnRestoreView *)(local_14->pad_4 + 0xc));
          }
        }
        uVar2 = wnd_base_wndproc(param_1,0x112,param_3,param_4);
        return uVar2;
      }
      sVar1 = (short)(param_3 >> 0x10);
      if (param_2 == 0x114) {
        local_18 = wnd_get_hscroll_pos((WndHScrollPosView *)local_14);
        switch(param_3) {
        case 0:
          local_18--;
          SetScrollPos(param_1,0,local_18,1);
          local_18 = GetScrollPos(param_1,0);
          wnd_active_child = local_14;
          *(int *)(local_14->pad_4 + 0xac) = local_18;
          wnd_call_hscroll((WndOnHScrollView *)(local_14->pad_4 + 0xc),local_18);
          return 0;
        case 1:
          local_18++;
          SetScrollPos(param_1,0,local_18,1);
          local_18 = GetScrollPos(param_1,0);
          wnd_active_child = local_14;
          *(int *)(local_14->pad_4 + 0xac) = local_18;
          wnd_call_hscroll((WndOnHScrollView *)(local_14->pad_4 + 0xc),local_18);
          return 0;
        case 2:
          iVar6 = wnd_get_hscroll_page((WndHScrollPageView *)local_14);
          local_18 -= iVar6;
          SetScrollPos(param_1,0,local_18,1);
          local_18 = GetScrollPos(param_1,0);
          wnd_active_child = local_14;
          *(int *)(local_14->pad_4 + 0xac) = local_18;
          wnd_call_hscroll((WndOnHScrollView *)(local_14->pad_4 + 0xc),local_18);
          return 0;
        case 3:
          iVar6 = wnd_get_hscroll_page((WndHScrollPageView *)local_14);
          local_18 += iVar6;
          SetScrollPos(param_1,0,local_18,1);
          local_18 = GetScrollPos(param_1,0);
          wnd_active_child = local_14;
          *(int *)(local_14->pad_4 + 0xac) = local_18;
          wnd_call_hscroll((WndOnHScrollView *)(local_14->pad_4 + 0xc),local_18);
          return 0;
        case 4:
          local_18 = (int)sVar1;
          SetScrollPos(param_1,0,local_18,1);
          wnd_active_child = local_14;
          *(int *)(local_14->pad_4 + 0xac) = local_18;
          wnd_call_hscroll
                    ((WndOnHScrollView *)(local_14->pad_4 + 0xc),*(i32 *)(local_14->pad_4 + 0xac));
          return 0;
        case 5:
          wnd_active_child = local_14;
          wnd_call_hscroll_track((WndOnHScrollTrackView *)(local_14->pad_4 + 0xc),(int)sVar1);
          return 0;
        default:
          return 0;
        }
      }
      if (param_2 == 0x115) {
        local_18 = wnd_get_vscroll_pos((WndVScrollPosView *)local_14);
        switch(param_3) {
        case 0:
          local_18--;
          SetScrollPos(param_1,1,local_18,1);
          local_18 = GetScrollPos(param_1,1);
          wnd_active_child = local_14;
          *(int *)(local_14->pad_4 + 0xb0) = local_18;
          wnd_call_vscroll((WndOnVScrollView *)(local_14->pad_4 + 0xc),local_18);
          return 0;
        case 1:
          local_18++;
          SetScrollPos(param_1,1,local_18,1);
          local_18 = GetScrollPos(param_1,1);
          wnd_active_child = local_14;
          *(int *)(local_14->pad_4 + 0xb0) = local_18;
          wnd_call_vscroll((WndOnVScrollView *)(local_14->pad_4 + 0xc),local_18);
          return 0;
        case 2:
          iVar6 = wnd_get_vscroll_page((WndVScrollPageView *)local_14);
          local_18 -= iVar6;
          SetScrollPos(param_1,1,local_18,1);
          local_18 = GetScrollPos(param_1,1);
          wnd_active_child = local_14;
          *(int *)(local_14->pad_4 + 0xb0) = local_18;
          wnd_call_vscroll((WndOnVScrollView *)(local_14->pad_4 + 0xc),local_18);
          return 0;
        case 3:
          iVar6 = wnd_get_vscroll_page((WndVScrollPageView *)local_14);
          local_18 += iVar6;
          SetScrollPos(param_1,1,local_18,1);
          local_18 = GetScrollPos(param_1,1);
          wnd_active_child = local_14;
          *(int *)(local_14->pad_4 + 0xb0) = local_18;
          wnd_call_vscroll((WndOnVScrollView *)(local_14->pad_4 + 0xc),local_18);
          return 0;
        case 4:
          local_18 = (int)sVar1;
          SetScrollPos(param_1,1,local_18,1);
          wnd_active_child = local_14;
          *(int *)(local_14->pad_4 + 0xb0) = local_18;
          wnd_call_vscroll
                    ((WndOnVScrollView *)(local_14->pad_4 + 0xc),*(i32 *)(local_14->pad_4 + 0xb0));
          return 0;
        case 5:
          wnd_active_child = local_14;
          wnd_call_vscroll_track((WndOnVScrollTrackView *)(local_14->pad_4 + 0xc),(int)sVar1);
          return 0;
        default:
          return 0;
        }
      }
      goto switchD_005ecda6_caseD_4;
    }
    if (param_2 < 0x211) {
      if (param_2 == 0x210) {
        if (param_3 == 0x201) {
          wnd_active_child = local_14;
          wnd_call_lbuttondown
                    ((WndOnLButtonDownView *)(local_14->pad_4 + 0xc),param_4 & 0xffff,param_4 >> 0x10);
          return 0;
        }
        if (param_3 != 0x204) {
          return 0;
        }
        wnd_active_child = local_14;
        wnd_call_rbuttondown
                  ((WndOnRButtonDownView *)(local_14->pad_4 + 0xc),param_4 & 0xffff,param_4 >> 0x10);
        return 0;
      }
      switch(param_2) {
      case 0x201:
        pCVar4 = (WndBase *)GetWindowLongA(param_1,0);
        local_24 = wnd_get_window(pCVar4);
        wnd_active_child = local_14;
        if ((*(byte *)(local_24 + 0x49) & 2) != 0) {
          SetFocus(*(HWND *)(local_24 + 4));
          BringWindowToTop(param_1);
        }
        local_14->pad_4[0xa4] = 1;
        local_14->pad_4[0xa5] = '\0';
        local_14->pad_4[0xa6] = '\0';
        local_14->pad_4[0xa7] = '\0';
        wnd_call_lbuttondown
                  ((WndOnLButtonDownView *)(local_14->pad_4 + 0xc),param_4 & 0xffff,param_4 >> 0x10);
        return 0;
      case 0x202:
        wnd_active_child = local_14;
        if (*(int *)(local_14->pad_4 + 0xa4) == 1) {
          local_14->pad_4[0xa4] = '\0';
          local_14->pad_4[0xa5] = '\0';
          local_14->pad_4[0xa6] = '\0';
          local_14->pad_4[0xa7] = '\0';
          wnd_call_lbuttonup
                    ((WndOnLButtonUpView *)(local_14->pad_4 + 0xc),param_4 & 0xffff,param_4 >> 0x10);
        }
        wnd_call_lbuttonup_raw
                  ((WndOnLButtonUpRawView *)(local_14->pad_4 + 0xc),param_4 & 0xffff,param_4 >> 0x10);
        return 0;
      case 0x203:
        wnd_active_child = local_14;
        wnd_call_dblclick
                  ((WndOnDblClickView *)(local_14->pad_4 + 0xc),param_4 & 0xffff,param_4 >> 0x10);
        return 0;
      case 0x204:
        pCVar4 = (WndBase *)GetWindowLongA(param_1,0);
        local_24 = wnd_get_window(pCVar4);
        if ((*(byte *)(local_24 + 0x49) & 2) != 0) {
          SetFocus(*(HWND *)(local_24 + 4));
          BringWindowToTop(param_1);
        }
        wnd_active_child = local_14;
        local_14->pad_4[0xa8] = 1;
        local_14->pad_4[0xa9] = '\0';
        local_14->pad_4[0xaa] = '\0';
        local_14->pad_4[0xab] = '\0';
        wnd_call_rbuttondown
                  ((WndOnRButtonDownView *)(local_14->pad_4 + 0xc),param_4 & 0xffff,param_4 >> 0x10);
        return 0;
      case 0x205:
        wnd_active_child = local_14;
        if (*(int *)(local_14->pad_4 + 0xa8) == 1) {
          local_14->pad_4[0xa8] = '\0';
          local_14->pad_4[0xa9] = '\0';
          local_14->pad_4[0xaa] = '\0';
          local_14->pad_4[0xab] = '\0';
          wnd_call_rbuttonup
                    ((WndOnRButtonUpView *)(local_14->pad_4 + 0xc),param_4 & 0xffff,param_4 >> 0x10);
        }
        wnd_call_rbuttonup_raw
                  ((WndOnRButtonUpRawView *)(local_14->pad_4 + 0xc),param_4 & 0xffff,param_4 >> 0x10);
        return 0;
      }
      goto switchD_005ecda6_caseD_4;
    }
    if ((param_2 != 0x30f) && (param_2 != 0x311)) {
      if (param_2 == 0x3b9) {
        if (param_3 == 1) {
          wnd_call_mci_done(local_14);
          return 0;
        }
        goto switchD_005ecda6_caseD_5;
      }
      goto switchD_005ecda6_caseD_4;
    }
switchD_005ecda6_caseD_6:
    local_10 = wnd_get_mci_device((WndMciDeviceView *)local_14);
    if (local_10 == 0) {
      uVar2 = wnd_base_wndproc(param_1,param_2,param_3,param_4);
      return uVar2;
    }
    mciSendCommandA(*(MCIDEVICEID *)(local_10 + 8),0x840,*(DWORD_PTR *)(local_10 + 0x10),
                    (DWORD_PTR)local_34);
  }
  return 0;
}
#undef wnd_active_child
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

/* 005eeca0 auto */
AviAudio * __thiscall avi_audio_ctor(AviAudio *this)

{
  this->audio_stream = 0;
  return this;
}

/* 005eed1b auto */
void __thiscall avi_audio_release(AviAudioReleaseView *this)

{
  if (this->audio_stream != 0) {
    snd_avi_stream_stop();
  }
  return;
}

/* 005eed43 auto */
uint __thiscall avi_audio_is_playing(AviAudioPlayingView *this)

{
  return (uint)((this->state_flags & 4) != 0);
}

/* 005eed76 auto */
int __thiscall avi_audio_attach_stream(AviAudioAttachView *this,u32 param_1)

{
  int iVar1;
  
  iVar1 = snd_wave_add_avi_stream(param_1);
  if (iVar1 == 0) {
    this->avi_stream = param_1;
    this->stream_flags = this->stream_flags | 1;
  }
  else {
    this->stream_flags = 0;
  }
  return iVar1;
}

/* 005eedd1 auto */
i32 __thiscall avi_audio_get_position_ms(void *this)

{
  i32 uVar1;
  
  uVar1 = snd_wave_get_position_ms();
  return uVar1;
}

/* 005eedec auto */
int __thiscall avi_audio_prepare_range(AviAudioPrepareView *this,i32 param_1,i32 param_2)

{
  int iVar1;
  
  iVar1 = snd_avi_stream_prepare(param_1,param_2,(iptr)this);
  if (iVar1 == 0) {
    this->audio_flags = this->audio_flags | 2;
  }
  else {
    this->audio_flags = this->audio_flags & 0xfffd;
  }
  return iVar1;
}

/* 005eee4f auto */
i16 __thiscall avi_audio_start(void *this)

{
  snd_avi_stream_start();
  return 0;
}
