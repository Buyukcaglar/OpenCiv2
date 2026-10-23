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

void __thiscall avi_player_set_end_callback(AviPlayerEndCbSetView *this,iptr callback)

{
  *(iptr *)(((AviPlayerEndCbSetViewExt *)this)->on_end_callback) = callback;
  return;
}

/* 0046e020 auto */
#define wav_name (*(char (*)[16])(frame_ + FRAME_OFF(0)))
#define wav_path (*(char (*)[128])(frame_ + FRAME_OFF(16)))
#define local_path (*(i8 (*)[128])(frame_ + FRAME_OFF(144)))
#define snd_flags (*(uint *)(frame_ + FRAME_OFF(272)))
void __cdecl snd_play_effect(iptr effect,iptr play_mode,int loop,iptr user_data)

{
  int result;
  char *drive;
  i8 frame_[FRAME_OFF(280)] __attribute__((aligned(8)));  /* original stack frame */
  
  snd_last_effect_id = effect;
  snd_last_effect_arg = play_mode;
  if (effect < 0) {
    snd_wave_free_by_id(~effect + 1);
  }
  else if ((((byte)game.game_options & 0x10) != 0) && (effect < 0x85)) {
    crt_strcpy(wav_name,s_AIRCOMBT_0062af70 + effect * 9);
    result = _strcmp(wav_name,s_CHEERS_0062b430);
    if (result == 0) {
      result = rand_range(0,2);
      str_append_int((iptr)wav_name,result + 1);
    }
    crt_strcat(wav_name,&snd_wav_ext_str);
    str_clear((iptr)wav_path);
    str_append((iptr)wav_path,ADDR(0x62b440, ((u8 *)&g.d_0062b440)));
    str_append((iptr)wav_path,(iptr)wav_name);
    str_clear((iptr)local_path);
    str_append((iptr)local_path,ADDR(0x64bb08, ((u8 *)&g.d_0064bb08)));
    str_append((iptr)local_path,ADDR(0x62b44c, ((u8 *)&g.d_0062b44c)));
    str_append((iptr)local_path,(iptr)wav_name);
    result = file_exists((iptr)local_path);
    if (result == 0) {
      drive = (char *)file_get_fallback_drive();
      result = file_resolve_path((iptr)wav_path);
      if (result == 0) {
        return;
      }
      if ((drive != (char *)0x0) && (wav_path[0] == *drive)) {
        return;
      }
    }
    else {
      crt_strcpy(wav_path,local_path);
    }
    snd_flags = 3;
    if (play_mode == 0) {
      snd_flags = 0x13;
    }
    if (loop != 0) {
      snd_flags = snd_flags | 8;
    }
    if (play_mode == 99) {
      sndPlaySoundA(wav_path,snd_flags);
    }
    else {
      snd_wave_play((iptr)wav_path,(loop == 0) - 1 & 8,effect,user_data);
    }
    win_flush_pending_msgs();
  }
  return;
}
#undef wav_name
#undef wav_path
#undef local_path
#undef snd_flags

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
#define rand_offset (*(int *)(frame_ + FRAME_OFF(0)))
#define rand_offset_alt (*(int *)(frame_ + FRAME_OFF(4)))
#define track (*(uint *)(frame_ + FRAME_OFF(8)))
#define track_count (*(int *)(frame_ + FRAME_OFF(12)))
#define tries (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl snd_cd_play_random_track(void)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  tries = 0;
  while (tries < 10) {
    tries++;
    track_count = snd_cd_get_track_count();
    if ((((track_count == 0x18) || (track_count == 0x12)) || (track_count == 0xc)) || (track_count == 10)) break;
  }
  if ((track_count == 1) || (track_count == -1)) {
    cd_music_available = 0;
  }
  else {
    while( true ) {
      if (((track_count == 10) || (track_count == 0x12)) || ((track_count == 0x18 || (track_count == 0xc)))) {
        if (track_count == 4 || track_count - 4 < 0) {
          rand_offset = 0;
        }
        else {
          rand_offset = _rand();
          rand_offset = rand_offset % (track_count - 3);
        }
        track = rand_offset + 4;
        cd_music_unknown_disc = 0;
      }
      else {
        if (track_count == 2 || track_count - 2 < 0) {
          rand_offset_alt = 0;
        }
        else {
          rand_offset_alt = _rand();
          rand_offset_alt = rand_offset_alt % (track_count - 1);
        }
        track = rand_offset_alt + 2;
        cd_music_unknown_disc = 1;
      }
      if (track != cd_music_current_track) break;
      cd_music_current_track = 0xffffffff;
    }
    cd_music_available = 0;
    cd_music_current_track = track;
    cd_music_continue = 1;
    snd_cd_play_track(track);
  }
  return;
}
#undef cd_music_available
#undef cd_music_continue
#undef cd_music_current_track
#undef cd_music_unknown_disc
#undef rand_offset
#undef rand_offset_alt
#undef track
#undef track_count
#undef tries

/* 0046e4a9 auto */
#define cd_music_available (*(i32 *)((u8 *)&g.d_0062b420))
#define cd_music_continue (*(i32 *)((u8 *)&g.d_0062b42c))
#define cd_music_unknown_disc (*(i32 *)((u8 *)&g.d_0062b424))
void __cdecl snd_cd_detect_layout(void)

{
  int track_count;
  
  snd_cd_set_notify_callback(ADDR(0x403120, snd_cd_on_notify));
  track_count = snd_cd_get_track_count();
  if ((track_count == -1) || (track_count == 1)) {
    cd_music_available = 0;
  }
  else if ((track_count == 10) || (((track_count == 0x12 || (track_count == 0x18)) || (track_count == 0xc)))) {
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
#define track_count (*(int *)(frame_ + FRAME_OFF(4)))
#define tries (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl music_play_track(uint track,int force)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((byte)game.game_options & 8) == 0) {
    if (cd_music_available == 0) {
      snd_cd_stop();
    }
  }
  else if ((((cd_music_available != 0) || (force != 0)) || (cd_music_current_track != track)) &&
          (cd_music_unknown_disc == 0)) {
    tries = 0;
    while (tries < 10) {
      tries++;
      track_count = snd_cd_get_track_count();
      if (((track_count == 0x18) || (track_count == 0x12)) || ((track_count == 0xc || (track_count == 10)))) break;
    }
    if ((track_count == 1) || (track_count == -1)) {
      cd_music_available = 0;
    }
    else {
      cd_music_continue = 0;
      snd_cd_mci_stop();
      snd_cd_set_notify_callback(ADDR(0x403120, snd_cd_on_notify));
      snd_cd_play_track(track);
      cd_music_current_track = track;
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
#undef track_count
#undef tries

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
void __thiscall avi_player_set_frame_callback(AviPlayerSetFrameCallbackView *this,iptr callback,u32 callback_data)

{
  this->on_frame = callback;
  this->callback_frame = callback_data;
  return;
}

/* 00472950: written by hand in src/game/regargs.c */

/* 004729ab: written by hand in src/game/regargs.c */

/* 004d8b20 auto */
AviPlayer * __thiscall avi_player_scalar_dtor(AviPlayer *this,uint flags)

{
  avi_player_dtor(this);
  if ((flags & 1) != 0) {
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
int __cdecl snd_wave_open(i32 notify_hwnd,i32 buffer_bytes,i32 buffer_count)

{
  int result;
  
  snd_wave_notify_hwnd = notify_hwnd;
  snd_wave_open_buffer_bytes = buffer_bytes;
  snd_wave_max_buffers = buffer_count;
  snd_wave_buffer_count = buffer_count;
  result = snd_wave_open_device(notify_hwnd,0,ADDR(0x638578, ((u8 *)&g.d_00638578)));
  if (result == 0) {
    snd_wave_alloc_buffers(buffer_bytes,snd_wave_out_handle,buffer_count);
    result = 0;
  }
  return result;
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
void __cdecl snd_show_error(int error_code)

{
  if (error_code == 10) {
    MessageBoxA((HWND)0x0,s_This_Sound_format_is_not_support_006385e4,s_Sound_Error_006385d8,0x40);
  }
  else if (error_code != 0xb) {
    MessageBoxA((HWND)0x0,s_Undefined_Sound_Error_00638614,s_Sound_Error_00638608,0x40);
  }
  return;
}

/* 005d4a11 auto */
#define snd_wave_block_align (*(i32 *)((u8 *)&g.d_006385ac))
#define snd_wave_format (*(i32 *)((u8 *)&g.d_006385a0))
#define snd_wave_out_handle (*(i32 *)((u8 *)&g.d_00638578))
#define chosen_device (*(UINT *)(frame_ + FRAME_OFF(4)))
#define device (*(UINT_PTR *)(frame_ + FRAME_OFF(8)))
#define result (*(uint *)(frame_ + FRAME_OFF(16)))
uint __cdecl snd_wave_open_device(DWORD_PTR callback,i32 *format,iptr out_handle)

{
  bool use_fallback;
  UINT UVar2;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  use_fallback = false;
  if (snd_wave_device_open == 0) {
    if (format != (i32 *)0x0) {
      snd_wave_format = *format;
      snd_wave_samples_per_sec = format[1];
      snd_wave_avg_bytes_per_sec = format[2];
      snd_wave_block_align = format[3];
    }
    UVar2 = waveOutGetNumDevs();
    for (device = 0; (int)device < (int)UVar2; device++) {
      waveOutGetDevCapsA(device,(LPWAVEOUTCAPSA)&snd_wave_dev_caps,0x34);
      if ((snd_wave_dev_formats & 0x20) != 0) {
        use_fallback = false;
        chosen_device = device;
        break;
      }
      if ((snd_wave_dev_formats & 0x10) != 0) {
        chosen_device = device;
        use_fallback = true;
      }
    }
    if ((use_fallback) || (device != UVar2)) {
      if (use_fallback) {
        snd_wave_format = CONCAT22(1,(i16)snd_wave_format);
        snd_wave_avg_bytes_per_sec = 0x5622;
        snd_wave_block_align = CONCAT22((*(i16 *)((char *)&snd_wave_block_align + 2)),1);
      }
      result = waveOutOpen((LPHWAVEOUT)&snd_wave_out_handle,chosen_device,(LPCWAVEFORMATEX)&snd_wave_format,
                            callback,0,0x10000);
      if ((short)result != 0) {
        sndPlaySoundA((LPCSTR)0x0,0);
        result = waveOutOpen((LPHWAVEOUT)&snd_wave_out_handle,chosen_device,(LPCWAVEFORMATEX)&snd_wave_format,
                              callback,0,0x10000);
      }
      result = result & 0xffff;
      if ((result == 0) && (snd_wave_device_open = 1, out_handle != 0)) {
        *(i32 *)out_handle = snd_wave_out_handle;
      }
    }
    else {
      snd_show_error(0xb);
      result = 0xb;
    }
  }
  else {
    result = 0;
  }
  return result;
}
#undef snd_wave_block_align
#undef snd_wave_format
#undef snd_wave_out_handle
#undef chosen_device
#undef device
#undef result

/* 005d4bcb auto */
#define result (*(i32 *)(frame_ + FRAME_OFF(0)))
uint __cdecl snd_wave_close_device(HWAVEOUT wave_out)

{
  MMRESULT MVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  result = 0;
  if (snd_wave_device_open != 0) {
    MVar1 = waveOutClose(wave_out);
    result = MVar1 & 0xffff;
  }
  snd_wave_device_open = 0;
  return result;
}
#undef result

/* 005d4c18 auto */
#define error_text (*(CHAR (*)[200])(frame_ + FRAME_OFF(4)))
void __cdecl snd_waveout_error_box(uint error_code)

{
  i8 frame_[FRAME_OFF(208)] __attribute__((aligned(8)));  /* original stack frame */
  
  waveOutGetErrorTextA(error_code & 0xffff,error_text,200);
  MessageBoxA((HWND)0x0,error_text,s_Wave_Out_Error_0063862c,0x40);
  return;
}
#undef error_text

/* 005d4c5f auto */
#define snd_wave_total_buffer_bytes (*(LONG *)((u8 *)&g.d_006385cc))
#define chunk (*(_MMCKINFO *)(frame_ + FRAME_OFF(0)))
#define mmio_info (*(_MMIOINFO *)(frame_ + FRAME_OFF(20)))
#define node2 (*(iptr *)(frame_ + FRAME_OFF(92)))
#define fmt_size (*(DWORD *)(frame_ + FRAME_OFF(96)))
#define source (*(FOURCC * *)(frame_ + FRAME_OFF(100)))
#define mem_handle2 (*(HGLOBAL *)(frame_ + FRAME_OFF(104)))
#define format_tag (*(FOURCC *)(frame_ + FRAME_OFF(108)))
#define samples_per_sec (*(FOURCC *)(frame_ + FRAME_OFF(112)))
#define avg_bytes_per_sec (*(FOURCC *)(frame_ + FRAME_OFF(116)))
#define block_align (*(i32 *)(frame_ + FRAME_OFF(120)))
#define riff_chunk (*(_MMCKINFO *)(frame_ + FRAME_OFF(124)))
#define mmio (*(HMMIO *)(frame_ + FRAME_OFF(144)))
i16 __cdecl snd_wave_load_file(LPSTR filename,i32 unused,i32 flags,FOURCC sound_id)

{
  i16 result;
  MMRESULT MVar2;
  DWORD DVar3;
  int n;
  _MMIOINFO *p_Var5;
  _MMCKINFO *p_Var6;
  DWORD *pDVar7;
  FOURCC *pFVar8;
  i8 frame_[FRAME_OFF(152)] __attribute__((aligned(8)));  /* original stack frame */
  
  _memset(&mmio_info,0,0x48);
  mmio_info.cchBuffer = snd_wave_total_buffer_bytes;
  mmio = mmioOpenA(filename,&mmio_info,0x10000);
  if (mmio == (HMMIO)0x0) {
    result = 7;
  }
  else {
    riff_chunk.fccType = 0x45564157;
    MVar2 = mmioDescend(mmio,&riff_chunk,(MMCKINFO *)0x0,0x20);
    if (MVar2 == 0) {
      chunk.ckid = 0x20746d66;
      MVar2 = mmioDescend(mmio,&chunk,&riff_chunk,0x10);
      if (MVar2 == 0) {
        fmt_size = chunk.cksize;
        DVar3 = mmioRead(mmio,(HPSTR)&format_tag,chunk.cksize);
        if (DVar3 == fmt_size) {
          if ((samples_per_sec == 0x5622) && ((*(i16 *)((char *)&block_align + 2)) == 8)) {
            mmioAscend(mmio,&chunk,0);
            chunk.ckid = 0x61746164;
            MVar2 = mmioDescend(mmio,&chunk,&riff_chunk,0x10);
            if (MVar2 == 0) {
              mmioGetInfo(mmio,&mmio_info,0);
              mmioAdvance(mmio,&mmio_info,0);
              mem_handle2 = GlobalAlloc(0x2002,0xbc);
              if (mem_handle2 == (HGLOBAL)0x0) {
                mmioClose(mmio,0);
                result = 2;
              }
              else {
                source = GlobalLock(mem_handle2);
                if (source == (FOURCC *)0x0) {
                  mmioClose(mmio,0);
                  GlobalFree(mem_handle2);
                  result = 2;
                }
                else {
                  _memset(source,0,0xbc);
                  source[0x1b] = (FOURCC)mem_handle2;
                  *source = (FOURCC)mmio;
                  p_Var5 = &mmio_info;
                  pDVar7 = source + 6;
                  for (n = 0x12; n != 0; n--) {
                    *pDVar7 = p_Var5->dwFlags;
                    p_Var5 = (_MMIOINFO *)&p_Var5->fccIOProc;
                    pDVar7++;
                  }
                  p_Var6 = &chunk;
                  pFVar8 = source;
                  for (n = 5; pFVar8 = pFVar8 + 1, n != 0; n--) {
                    *pFVar8 = p_Var6->ckid;
                    p_Var6 = (_MMCKINFO *)&p_Var6->cksize;
                  }
                  *(i16 *)((int)source + 0x8a) = (i16)flags;
                  source[0x1d] = format_tag;
                  source[0x1e] = samples_per_sec;
                  source[0x1f] = avg_bytes_per_sec;
                  source[0x20] = block_align;
                  *(i16 *)(source + 0x22) = 1;
                  source[0x2d] = sound_id;
                  if (snd_wave_sources == 0) {
                    snd_wave_sources = (iptr)source;
                  }
                  else {
                    for (node2 = snd_wave_sources; *(int *)(node2 + 0xb8) != 0;
                        node2 = *(iptr *)(node2 + 0xb8)) {
                    }
                    *(FOURCC **)(node2 + 0xb8) = source;
                  }
                  result = 0;
                }
              }
            }
            else {
              mmioClose(mmio,0);
              result = 8;
            }
          }
          else {
            snd_show_error(10);
            mmioClose(mmio,0);
            result = 10;
          }
        }
        else {
          mmioClose(mmio,0);
          result = 8;
        }
      }
      else {
        mmioClose(mmio,0);
        result = 8;
      }
    }
    else {
      mmioClose(mmio,0);
      result = 8;
    }
  }
  return result;
}
#undef snd_wave_total_buffer_bytes
#undef chunk
#undef mmio_info
#undef node2
#undef fmt_size
#undef source
#undef mem_handle2
#undef format_tag
#undef samples_per_sec
#undef avg_bytes_per_sec
#undef block_align
#undef riff_chunk
#undef mmio

/* 005d4f6a auto */
#define snd_wave_total_buffer_bytes (*(LONG *)((u8 *)&g.d_006385cc))
#define chunk (*(_MMCKINFO *)(frame_ + FRAME_OFF(4)))
#define mmio_info (*(_MMIOINFO *)(frame_ + FRAME_OFF(24)))
#define node2 (*(iptr *)(frame_ + FRAME_OFF(96)))
#define fmt_size (*(DWORD *)(frame_ + FRAME_OFF(100)))
#define source (*(FOURCC * *)(frame_ + FRAME_OFF(104)))
#define mem_handle2 (*(HGLOBAL *)(frame_ + FRAME_OFF(108)))
#define format_tag (*(FOURCC *)(frame_ + FRAME_OFF(112)))
#define samples_per_sec (*(FOURCC *)(frame_ + FRAME_OFF(116)))
#define avg_bytes_per_sec (*(FOURCC *)(frame_ + FRAME_OFF(120)))
#define block_align (*(i32 *)(frame_ + FRAME_OFF(124)))
#define riff_chunk (*(_MMCKINFO *)(frame_ + FRAME_OFF(128)))
#define file_mmio (*(HMMIO *)(frame_ + FRAME_OFF(148)))
#define mem_mmio (*(HMMIO *)(frame_ + FRAME_OFF(152)))
i16 __cdecl snd_wave_open_stream(LPSTR filename,i32 unused,i32 flags)

{
  i16 result;
  MMRESULT MVar2;
  DWORD DVar3;
  int n;
  _MMIOINFO *p_Var5;
  _MMCKINFO *p_Var6;
  DWORD *pDVar7;
  FOURCC *pFVar8;
  i8 frame_[FRAME_OFF(160)] __attribute__((aligned(8)));  /* original stack frame */
  
  file_mmio = mmioOpenA(filename,(LPMMIOINFO)0x0,0);
  if (file_mmio == (HMMIO)0x0) {
    result = 7;
  }
  else {
    riff_chunk.fccType = 0x45564157;
    MVar2 = mmioDescend(file_mmio,&riff_chunk,(MMCKINFO *)0x0,0x20);
    if (MVar2 == 0) {
      chunk.ckid = 0x20746d66;
      MVar2 = mmioDescend(file_mmio,&chunk,&riff_chunk,0x10);
      if (MVar2 == 0) {
        fmt_size = chunk.cksize;
        DVar3 = mmioRead(file_mmio,(HPSTR)&format_tag,chunk.cksize);
        if (DVar3 == fmt_size) {
          if ((samples_per_sec == 0x5622) && ((*(i16 *)((char *)&block_align + 2)) == 8)) {
            mmioAscend(file_mmio,&chunk,0);
            chunk.ckid = 0x61746164;
            MVar2 = mmioDescend(file_mmio,&chunk,&riff_chunk,0x10);
            if (MVar2 == 0) {
              _memset(&mmio_info,0,0x48);
              mmio_info.cchBuffer = snd_wave_total_buffer_bytes;
              mmio_info.fccIOProc = 0x204d454d;
              mmio_info.adwInfo[0] = 0;
              mem_mmio = mmioOpenA((LPSTR)0x0,&mmio_info,0x11002);
              if (mem_mmio == (HMMIO)0x0) {
                result = 7;
              }
              else {
                mmioGetInfo(mem_mmio,&mmio_info,0);
                mem_handle2 = GlobalAlloc(0x2002,0xbc);
                if (mem_handle2 == (HGLOBAL)0x0) {
                  result = 2;
                }
                else {
                  source = GlobalLock(mem_handle2);
                  if (source == (FOURCC *)0x0) {
                    GlobalFree(mem_handle2);
                    result = 2;
                  }
                  else {
                    _memset(source,0,0xbc);
                    source[0x1b] = (FOURCC)mem_handle2;
                    *(i16 *)(source + 0x22) = 1;
                    source[0x1d] = format_tag;
                    source[0x1e] = samples_per_sec;
                    source[0x1f] = avg_bytes_per_sec;
                    source[0x20] = block_align;
                    *source = (FOURCC)mem_mmio;
                    source[0x18] = (FOURCC)file_mmio;
                    p_Var5 = &mmio_info;
                    pDVar7 = source + 6;
                    for (n = 0x12; n != 0; n--) {
                      *pDVar7 = p_Var5->dwFlags;
                      p_Var5 = (_MMIOINFO *)&p_Var5->fccIOProc;
                      pDVar7++;
                    }
                    p_Var6 = &chunk;
                    pFVar8 = source;
                    for (n = 5; pFVar8 = pFVar8 + 1, n != 0; n--) {
                      *pFVar8 = p_Var6->ckid;
                      p_Var6 = (_MMCKINFO *)&p_Var6->cksize;
                    }
                    source[0x1c] = source[0x1c] | 4;
                    *(i16 *)((int)source + 0x8a) = (i16)flags;
                    snd_wave_stream_refill((iptr)source);
                    if (snd_wave_sources == 0) {
                      snd_wave_sources = (iptr)source;
                    }
                    else {
                      for (node2 = snd_wave_sources; *(int *)(node2 + 0xb8) != 0;
                          node2 = *(iptr *)(node2 + 0xb8)) {
                      }
                      *(FOURCC **)(node2 + 0xb8) = source;
                    }
                    result = 0;
                  }
                }
              }
            }
            else {
              mmioClose(file_mmio,0);
              result = 8;
            }
          }
          else {
            snd_show_error(10);
            mmioClose(file_mmio,0);
            result = 10;
          }
        }
        else {
          mmioClose(file_mmio,0);
          result = 8;
        }
      }
      else {
        mmioClose(file_mmio,0);
        result = 8;
      }
    }
    else {
      mmioClose(file_mmio,0);
      result = 8;
    }
  }
  return result;
}
#undef snd_wave_total_buffer_bytes
#undef chunk
#undef mmio_info
#undef node2
#undef fmt_size
#undef source
#undef mem_handle2
#undef format_tag
#undef samples_per_sec
#undef avg_bytes_per_sec
#undef block_align
#undef riff_chunk
#undef file_mmio
#undef mem_mmio

/* 005d52a2 auto */
#define snd_wave_format (*(i8 *)((u8 *)&g.d_006385a0))
#define snd_wave_max_buffers (*(uint *)((u8 *)&g.d_00638584))
#define snd_wave_out_handle (*(int *)((u8 *)&g.d_00638578))
#define snd_wave_source_count (*(short *)((u8 *)&g.d_0063858c))
#define snd_wave_total_buffer_bytes (*(uint *)((u8 *)&g.d_006385cc))
#define mmio_info (*(_MMIOINFO *)(frame_ + FRAME_OFF(4)))
#define format_tag (*(i32 *)(frame_ + FRAME_OFF(76)))
#define samples_per_sec (*(i32 *)(frame_ + FRAME_OFF(80)))
#define avg_bytes_per_sec (*(i32 *)(frame_ + FRAME_OFF(84)))
#define block_align (*(i32 *)(frame_ + FRAME_OFF(88)))
#define source (*(i32 * *)(frame_ + FRAME_OFF(92)))
#define mem_handle2 (*(HGLOBAL *)(frame_ + FRAME_OFF(96)))
#define sample_buf (*(i8 (*)[4])(frame_ + FRAME_OFF(100)))
#define bytes_per_buffer (*(uint *)(frame_ + FRAME_OFF(104)))
#define total_bytes (*(int *)(frame_ + FRAME_OFF(108)))
#define format_size (*(i32 *)(frame_ + FRAME_OFF(112)))
#define size_bits (*(uint *)(frame_ + FRAME_OFF(116)))
#define stream_info (*(int (*)[8])(frame_ + FRAME_OFF(120)))
#define stream_length (*(int *)(frame_ + FRAME_OFF(152)))
#define sample_size (*(int *)(frame_ + FRAME_OFF(168)))
#define mmio (*(HMMIO *)(frame_ + FRAME_OFF(260)))
#define rate_mode (*(i32 *)(frame_ + FRAME_OFF(264)))
i32 __cdecl snd_wave_add_avi_stream(int avi_stream)

{
  i32 result;
  int n;
  _MMIOINFO *p_Var3;
  DWORD *pDVar4;
  i8 frame_[FRAME_OFF(272)] __attribute__((aligned(8)));  /* original stack frame */
  
  format_size = 0xe;
  if (snd_wave_out_handle == 0) {
    result = 3;
  }
  else if (avi_stream == 0) {
    result = 0xc;
  }
  else if ((snd_wave_sources == 0) || (*(short *)(snd_wave_sources + 0x88) != 4)) {
    AVIStreamInfoA(avi_stream,stream_info,0x8c);
    if (stream_info[0] == 0x73647561) {
      AVIStreamRead(avi_stream,0,1,0,0,sample_buf,0);
      total_bytes = sample_size * stream_length;
      AVIStreamReadFormat(avi_stream,0,&format_tag,&format_size);
      if ((*(i16 *)((char *)&snd_wave_format + 2)) == 1) {
        if ((*(i16 *)((char *)&format_tag + 2)) == 2) {
          rate_mode = CONCAT22((*(i16 *)((char *)&rate_mode + 2)),1);
        }
        else {
          rate_mode = CONCAT22((*(i16 *)((char *)&rate_mode + 2)),2);
        }
      }
      else if ((*(i16 *)((char *)&format_tag + 2)) == 2) {
        rate_mode = (uint)(*(i16 *)((char *)&rate_mode + 2)) << 0x10;
      }
      else {
        rate_mode = CONCAT22((*(i16 *)((char *)&rate_mode + 2)),3);
      }
      _memset(&mmio_info,0,0x48);
      if ((rate_mode & 0xffff) == 1) {
        mmio_info.cchBuffer = snd_wave_total_buffer_bytes * 2;
      }
      else if ((rate_mode & 0xffff) == 3) {
        mmio_info.cchBuffer = snd_wave_total_buffer_bytes >> 1;
      }
      else {
        mmio_info.cchBuffer = snd_wave_total_buffer_bytes;
      }
      bytes_per_buffer = (uint)mmio_info.cchBuffer / snd_wave_max_buffers;
      mmio_info.fccIOProc = 0x204d454d;
      mmio_info.adwInfo[0] = 0;
      mmio = mmioOpenA((LPSTR)0x0,&mmio_info,0x11002);
      if (mmio == (HMMIO)0x0) {
        result = 7;
      }
      else {
        mmioGetInfo(mmio,&mmio_info,0);
        mem_handle2 = GlobalAlloc(0x2002,0xbc);
        if (mem_handle2 == (HGLOBAL)0x0) {
          result = 2;
        }
        else {
          source = GlobalLock(mem_handle2);
          if (source == (i32 *)0x0) {
            GlobalFree(mem_handle2);
            result = 2;
          }
          else {
            _memset(source,0,0xbc);
            source[0x1b] = mem_handle2;
            *(i16 *)(source + 0x22) = 4;
            source[0x1d] = format_tag;
            source[0x1e] = samples_per_sec;
            source[0x1f] = avg_bytes_per_sec;
            source[0x20] = block_align;
            *source = mmio;
            p_Var3 = &mmio_info;
            pDVar4 = source + 6;
            for (n = 0x12; n != 0; n--) {
              *pDVar4 = p_Var3->dwFlags;
              p_Var3 = (_MMIOINFO *)&p_Var3->fccIOProc;
              pDVar4++;
            }
            source[1] = stream_info[0];
            source[2] = total_bytes;
            source[0x21] = avi_stream;
            source[0x1c] = source[0x1c] | 2;
            source[0x27] = bytes_per_buffer;
            for (size_bits = mmio_info.cchBuffer; 1 < size_bits; size_bits = size_bits >> 1) {
              source[0x2a] = source[0x2a] << 1;
              source[0x2a]++;
            }
            source[0x2e] = snd_wave_sources;
            snd_wave_sources = (iptr)source;
            snd_wave_source_count++;
            result = 0;
          }
        }
      }
    }
    else {
      result = 9;
    }
  }
  else {
    result = 0;
  }
  return result;
}
#undef snd_wave_format
#undef snd_wave_max_buffers
#undef snd_wave_out_handle
#undef snd_wave_source_count
#undef snd_wave_total_buffer_bytes
#undef mmio_info
#undef format_tag
#undef samples_per_sec
#undef avg_bytes_per_sec
#undef block_align
#undef source
#undef mem_handle2
#undef sample_buf
#undef bytes_per_buffer
#undef total_bytes
#undef format_size
#undef size_bits
#undef stream_info
#undef stream_length
#undef sample_size
#undef mmio
#undef rate_mode

/* 005d5643: written by hand in src/game/sound_position.c */

/* 005d5706: written by hand in src/game/sound_position.c */

/* 005d57b1 auto */
#define snd_avi_stream_started (*(int *)((u8 *)&g.d_006385bc))
#define snd_wave_out_handle (*(int *)((u8 *)&g.d_00638578))
#define snd_avi_feed_count_i32 (*(i32 *)((u8 *)&g.d_00638590))
#define snd_avi_fill_count_i32 (*(i32 *)((u8 *)&g.d_00638594))
#define snd_avi_feed_samples_i32 (*(i32 *)((u8 *)&g.d_00638598))
#define byte_count (*(uint *)(frame_ + FRAME_OFF(4)))
#define i (*(uint *)(frame_ + FRAME_OFF(8)))
#define buffer (*(iptr *)(frame_ + FRAME_OFF(28)))
#define bytes_read (*(int *)(frame_ + FRAME_OFF(32)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __cdecl snd_avi_stream_feed(uint sample_count)

{
  i32 result;
  uint limit;
  iptr source;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  source = snd_wave_sources;
  if (snd_wave_out_handle == 0) {
    result = 3;
  }
  else if (snd_avi_stream_started == 0) {
    result = 0xe;
  }
  else if ((snd_wave_sources == 0) || (*(short *)(snd_wave_sources + 0x88) != 4)) {
    result = 5;
  }
  else if ((*(byte *)(snd_wave_sources + 0x70) & 1) == 0) {
    if ((*(uint *)(*(int *)(snd_wave_sources + 0x98) + 0xc) >> 3 & 1) == 0) {
      if (((*(uint *)(*(int *)(snd_wave_sources + 0x98) + 0xc) >> 7) -
           (*(uint *)(snd_wave_cur_buffer + 0xc) >> 7) & 7) == 0) {
        sample_count = (uint)(*(int *)(snd_wave_sources + 0x9c) - *(int *)(snd_wave_sources + 0x68)) /
                  (uint)*(ushort *)(snd_wave_sources + 0x80);
        snd_avi_fill_count_i32++;
      }
      buffer = *(int *)(snd_wave_sources + 0x98);
      limit = (*(int *)(snd_wave_sources + 0x3c) - *(int *)(snd_wave_sources + 0x34)) /
              (int)(uint)*(ushort *)(snd_wave_sources + 0x80);
      if (limit < sample_count) {
        sample_count = limit;
      }
      byte_count = *(ushort *)(snd_wave_sources + 0x80) * sample_count;
      limit = *(int *)(snd_wave_sources + 0x9c) - *(int *)(snd_wave_sources + 0x68);
      snd_avi_feed_samples_i32 = sample_count;
      if (limit < byte_count) {
        byte_count = limit;
      }
      limit = *(int *)(snd_wave_sources + 8) -
              (*(int *)(snd_wave_sources + 0x90) - *(int *)(snd_wave_sources + 0x94));
      if (limit < byte_count) {
        byte_count = limit;
      }
      bytes_read = 0;
      AVIStreamRead(*(i32 *)(snd_wave_sources + 0x84),
                    *(uint *)(snd_wave_sources + 0x90) / (uint)*(ushort *)(snd_wave_sources + 0x80),
                    byte_count / *(ushort *)(snd_wave_sources + 0x80),
                    *(i32 *)(snd_wave_sources + 0x34),byte_count,&bytes_read,0);
      *(int *)(snd_wave_sources + 0x90) = *(int *)(snd_wave_sources + 0x90) + bytes_read;
      *(int *)(source + 0x34) = *(int *)(source + 0x34) + bytes_read;
      if (*(int *)(source + 0x3c) == *(int *)(source + 0x34)) {
        *(i32 *)(source + 0x34) = *(i32 *)(source + 0x30);
      }
      *(int *)(snd_wave_sources + 0x68) = *(int *)(snd_wave_sources + 0x68) + bytes_read;
      if (*(uint *)(snd_wave_sources + 0x9c) <= *(uint *)(snd_wave_sources + 0x68)) {
        *(uint *)(buffer + 0xc) = *(uint *)(buffer + 0xc) | 8;
        *(i32 *)(snd_wave_sources + 0x98) = *(i32 *)(buffer + 0x1c);
        buffer = *(iptr *)(snd_wave_sources + 0x98);
        *(i32 *)(snd_wave_sources + 0x68) = 0;
      }
      if (*(uint *)(snd_wave_sources + 8) <=
          (uint)(*(int *)(snd_wave_sources + 0x90) - *(int *)(snd_wave_sources + 0x94))) {
        for (i = 0;
            i < (uint)(*(int *)(snd_wave_sources + 0x9c) - *(int *)(snd_wave_sources + 0x68));
            i = i + 1) {
          **(i8 **)(source + 0x34) = 0x80;
          *(int *)(source + 0x34) = *(int *)(source + 0x34) + 1;
        }
        if (*(int *)(source + 0x3c) == *(int *)(source + 0x34)) {
          *(i32 *)(source + 0x34) = *(i32 *)(source + 0x30);
        }
        *(uint *)(buffer + 0xc) = *(uint *)(buffer + 0xc) | 8;
        *(uint *)(buffer + 0xc) = *(uint *)(buffer + 0xc) | 2;
        *(i32 *)(snd_wave_sources + 0x98) = *(i32 *)(buffer + 0x1c);
        *(i32 *)(snd_wave_sources + 0x68) = 0;
        *(uint *)(snd_wave_sources + 0x70) = *(uint *)(snd_wave_sources + 0x70) | 1;
      }
      snd_avi_feed_count_i32++;
      result = 0;
    }
    else {
      result = 0;
    }
  }
  else {
    result = 0xe;
  }
  return result;
}
#undef snd_avi_stream_started
#undef snd_wave_out_handle
#undef snd_avi_feed_count_i32
#undef snd_avi_fill_count_i32
#undef snd_avi_feed_samples_i32
#undef byte_count
#undef i
#undef buffer
#undef bytes_read

/* 005d5b88 auto */
#define snd_avi_stream_started (*(i32 *)((u8 *)&g.d_006385bc))
i32 __cdecl snd_avi_stream_stop(void)

{
  i32 result;
  
  snd_avi_stream_started = 0;
  if ((snd_wave_sources == 0) || (*(short *)(snd_wave_sources + 0x88) != 4)) {
    result = 5;
  }
  else {
    snd_wave_sources = snd_wave_free(0,snd_wave_sources);
    result = 0;
  }
  return result;
}
#undef snd_avi_stream_started

/* 005d5bec auto */
#define byte_count (*(uint *)(frame_ + FRAME_OFF(0)))
#define bytes_read (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl snd_avi_stream_refill(iptr source)

{
  uint remaining;
  int shortfall;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  bytes_read = 0;
  if ((*(int *)(source + 0x3c) == *(int *)(source + 0x34)) ||
     (*(int *)(source + 0x30) == *(int *)(source + 0x34))) {
    remaining = *(int *)(snd_wave_sources + 8) -
            (*(int *)(snd_wave_sources + 0x90) - *(int *)(snd_wave_sources + 0x94));
    byte_count = *(uint *)(source + 0x2c);
    if (remaining < *(uint *)(source + 0x2c)) {
      byte_count = remaining;
    }
    *(i32 *)(source + 0x34) = *(i32 *)(source + 0x30);
    AVIStreamRead(*(i32 *)(source + 0x84),
                  *(uint *)(source + 0x90) / (uint)*(ushort *)(source + 0x80),
                  byte_count / *(ushort *)(source + 0x80),*(i32 *)(source + 0x34),byte_count,
                  &bytes_read,0);
    *(int *)(source + 0x90) = *(int *)(source + 0x90) + bytes_read;
    shortfall = *(int *)(source + 0x2c) - bytes_read;
    if (shortfall != 0) {
      snd_fill_silence_u8(*(int *)(source + 0x34) + bytes_read,shortfall);
    }
  }
  return;
}
#undef byte_count
#undef bytes_read

/* 005d5d11 auto */
#define snd_avi_stream_started (*(i32 *)((u8 *)&g.d_006385bc))
#define snd_wave_buffer_count (*(uint *)((u8 *)&g.d_00638588))
#define snd_wave_max_buffers (*(uint *)((u8 *)&g.d_00638584))
#define snd_wave_out_handle (*(int *)((u8 *)&g.d_00638578))
#define byte_length (*(int *)(frame_ + FRAME_OFF(0)))
#define i (*(uint *)(frame_ + FRAME_OFF(4)))
#define buffer (*(i32 * *)(frame_ + FRAME_OFF(8)))
i32 __cdecl snd_avi_stream_prepare(i32 start_time,i32 end_time,iptr status_ptr)

{
  i32 result;
  int start_byte;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (snd_wave_out_handle == 0) {
    result = 3;
  }
  else if ((snd_wave_sources == 0) || (*(short *)(snd_wave_sources + 0x88) != 4)) {
    result = 5;
  }
  else {
    if (snd_wave_buffer_count != snd_wave_max_buffers) {
      snd_wave_set_buffer_count(snd_wave_max_buffers);
    }
    start_byte = AVIStreamTimeToSample(*(i32 *)(snd_wave_sources + 0x84),start_time);
    byte_length = AVIStreamTimeToSample(*(i32 *)(snd_wave_sources + 0x84),end_time);
    byte_length = (uint)*(ushort *)(snd_wave_sources + 0x80) * byte_length;
    start_byte = (uint)*(ushort *)(snd_wave_sources + 0x80) * start_byte;
    if (byte_length == 0) {
      byte_length = *(int *)(snd_wave_sources + 8) - start_byte;
    }
    else {
      byte_length -= start_byte;
    }
    if (byte_length < 0) {
      result = 0xc;
    }
    else {
      snd_wave_stop_all();
      *(int *)(snd_wave_sources + 8) = byte_length;
      *(int *)(snd_wave_sources + 0x90) = start_byte;
      *(int *)(snd_wave_sources + 0x94) = start_byte;
      *(i32 *)(snd_wave_sources + 100) = 0;
      *(i32 *)(snd_wave_sources + 0x68) = 0;
      *(i32 *)(snd_wave_sources + 0x34) = *(i32 *)(snd_wave_sources + 0x3c);
      snd_avi_stream_refill(snd_wave_sources);
      *(uint *)(snd_wave_sources + 0x70) = *(uint *)(snd_wave_sources + 0x70) & 0xfffffffd;
      *(uint *)(snd_wave_sources + 0x70) = *(uint *)(snd_wave_sources + 0x70) & 0xfffffffe;
      *(iptr *)(snd_wave_sources + 0x8c) = status_ptr;
      snd_avi_stream_started = 0;
      buffer = (i32 *)snd_wave_buffer_ring;
      for (i = 0; i < snd_wave_max_buffers; i++) {
        buffer[3] = buffer[3] & 0xffffffdf;
        buffer[3] = buffer[3] & 0xfffffffe;
        buffer[3] = buffer[3] & 0xfffffffd;
        buffer[3] = buffer[3] & 0xffffffef;
        buffer[3] = buffer[3] & 0xffffffdf;
        buffer[3] = buffer[3] & 0xffffffbf;
        buffer[4] = *(i32 *)*buffer;
        start_byte = snd_wave_mix_buffer(*buffer);
        if (start_byte == 1) break;
        buffer = (i32 *)buffer[7];
      }
      snd_avi_stream_refill(snd_wave_sources);
      buffer = (i32 *)snd_wave_buffer_ring;
      for (i = 0; i < snd_wave_max_buffers; i++) {
        *(uint *)((int)buffer + 0xc) = *(uint *)((int)buffer + 0xc) | 8;
        buffer = *(i32 **)((int)buffer + 0x1c);
      }
      snd_wave_cur_buffer = snd_wave_buffer_ring;
      result = 0;
    }
  }
  return result;
}
#undef snd_avi_stream_started
#undef snd_wave_buffer_count
#undef snd_wave_max_buffers
#undef snd_wave_out_handle
#undef byte_length
#undef i
#undef buffer

/* 005d5f91 auto */
#define snd_avi_stream_started (*(i32 *)((u8 *)&g.d_006385bc))
i16 __cdecl snd_avi_stream_start(void)

{
  iptr ring;
  
  if ((snd_wave_sources != 0) && (*(short *)(snd_wave_sources + 0x88) == 4)) {
    snd_wave_write_pending(snd_wave_buffer_ring);
    *(uint *)(snd_wave_sources + 0x70) = *(uint *)(snd_wave_sources + 0x70) | 0x10;
    if (*(int *)(snd_wave_sources + 0x8c) != 0) {
      **(ushort **)(snd_wave_sources + 0x8c) = **(ushort **)(snd_wave_sources + 0x8c) | 4;
    }
  }
  ring = snd_wave_buffer_ring;
  snd_avi_stream_started = 1;
  *(iptr *)(snd_wave_sources + 0x98) = snd_wave_buffer_ring;
  return (short)ring;
}
#undef snd_avi_stream_started

/* 005d6038 auto */
#define snd_wave_buffer_count (*(uint *)((u8 *)&g.d_00638588))
#define snd_wave_max_buffers (*(i32 *)((u8 *)&g.d_00638584))
#define snd_wave_notify_hwnd (*(i32 *)((u8 *)&g.d_0063857c))
#define snd_wave_out_handle (*(int *)((u8 *)&g.d_00638578))
#define snd_wave_source_count (*(ushort *)((u8 *)&g.d_0063858c))
#define i (*(uint *)(frame_ + FRAME_OFF(0)))
#define buffer (*(i32 * *)(frame_ + FRAME_OFF(8)))
short __cdecl snd_wave_play(iptr filename,uint flags,i32 sound_id,i32 sound_tag)

{
  short result;
  int status;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (snd_wave_out_handle == 0) {
    result = 3;
  }
  else if ((snd_wave_device_open == 0) &&
          (status = snd_wave_open(snd_wave_notify_hwnd,snd_wave_open_buffer_bytes,snd_wave_max_buffers), status != 0)) {
    result = 0;
  }
  else if (snd_wave_source_count < 5) {
    if ((flags & 8) == 0) {
      result = snd_wave_load_file(filename,flags,sound_id,sound_tag);
    }
    else {
      result = snd_wave_open_stream(filename,flags,sound_id);
    }
    if ((result == 0) &&
       (snd_wave_source_count = snd_wave_source_count + 1, (*(uint *)(snd_wave_cur_buffer + 0xc) >> 5 & 1) == 0)) {
      i = 0;
      buffer = (i32 *)snd_wave_cur_buffer;
      while ((i < snd_wave_buffer_count && (status = snd_wave_mix_buffer(*buffer), status != 1))) {
        buffer = (i32 *)buffer[7];
        i++;
      }
      snd_wave_write_pending(snd_wave_cur_buffer);
    }
  }
  else {
    result = 0;
  }
  return result;
}
#undef snd_wave_buffer_count
#undef snd_wave_max_buffers
#undef snd_wave_notify_hwnd
#undef snd_wave_out_handle
#undef snd_wave_source_count
#undef i
#undef buffer

/* 005d61ab auto */
#define source (*(iptr *)(frame_ + FRAME_OFF(4)))
#define prev (*(iptr *)(frame_ + FRAME_OFF(8)))
void __cdecl snd_wave_free_by_id(i32 sound_id)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  prev = 0;
  source = snd_wave_sources;
  while (source != 0) {
    if (*(short *)(source + 0x8a) == (short)sound_id) {
      source = snd_wave_free(prev,source);
    }
    else {
      prev = source;
      source = *(iptr *)(source + 0xb8);
    }
  }
  return;
}
#undef source
#undef prev

/* 005d6283 auto */
#define mmio_info (*(i32 (*)[5])(frame_ + FRAME_OFF(4)))
#define buffer_size (*(int *)(frame_ + FRAME_OFF(24)))
#define buffer_start (*(HPSTR *)(frame_ + FRAME_OFF(28)))
#define read_ptr (*(HPSTR *)(frame_ + FRAME_OFF(32)))
#define buffer_end (*(int *)(frame_ + FRAME_OFF(40)))
#define done (*(int *)(frame_ + FRAME_OFF(76)))
#define remaining (*(int *)(frame_ + FRAME_OFF(80)))
#define leftover (*(int *)(frame_ + FRAME_OFF(84)))
#define space (*(int *)(frame_ + FRAME_OFF(88)))
void __cdecl snd_wave_stream_refill(iptr source)

{
  int n;
  i32 *src;
  i32 *dst;
  i8 frame_[FRAME_OFF(96)] __attribute__((aligned(8)));  /* original stack frame */
  
  remaining = 0;
  done = 0;
  src = (i32 *)(source + 0x18);
  dst = mmio_info;
  for (n = 0x12; n != 0; n--) {
    *dst = *src;
    src++;
    dst++;
  }
  if (buffer_start == read_ptr) {
    leftover = 0;
    space = buffer_size;
  }
  else {
    leftover = buffer_end - (int)read_ptr;
    space = buffer_size - leftover;
  }
  if (leftover == 0) {
    read_ptr = buffer_start;
  }
  else {
    crt_memmove(buffer_start,read_ptr,leftover);
    read_ptr = buffer_start + leftover;
  }
  while (done == 0) {
    remaining = *(int *)(source + 8) - *(int *)(source + 0x68);
    if (space < remaining) {
      mmioRead(*(HMMIO *)(source + 0x60),read_ptr,space);
      *(int *)(source + 0x68) = *(int *)(source + 0x68) + space;
      *(HPSTR *)(source + 0x34) = buffer_start;
      done = 1;
    }
    else {
      mmioRead(*(HMMIO *)(source + 0x60),read_ptr,remaining);
      *(i32 *)(source + 0x68) = 0;
      read_ptr += remaining;
      space = buffer_end - (int)read_ptr;
      mmioSeek(*(HMMIO *)(source + 0x60),*(LONG *)(source + 0x10),0);
    }
  }
  return;
}
#undef mmio_info
#undef buffer_size
#undef buffer_start
#undef read_ptr
#undef buffer_end
#undef done
#undef remaining
#undef leftover
#undef space

/* 005d63c5 auto */
LPVOID __cdecl snd_global_alloc_lock(SIZE_T size,iptr handle_out)

{
  HGLOBAL handle;
  LPVOID ptr;
  
  handle = GlobalAlloc(0x2002,size);
  *(HGLOBAL *)handle_out = handle;
  if (*(int *)handle_out == 0) {
    ptr = (LPVOID)0x0;
  }
  else {
    ptr = GlobalLock(*(HGLOBAL *)handle_out);
    if (ptr == (LPVOID)0x0) {
      GlobalFree(*(HGLOBAL *)handle_out);
      *(i32 *)handle_out = 0;
    }
  }
  return ptr;
}

/* 005d6430 auto */
void __cdecl snd_global_free(HGLOBAL handle)

{
  if (handle != (HGLOBAL)0x0) {
    GlobalUnlock(handle);
    GlobalFree(handle);
  }
  return;
}

/* 005d645e auto */
#define snd_wave_total_buffer_bytes (*(uint *)((u8 *)&g.d_006385cc))
#define snd_wave_buffers_ready_i32 (*(i32 *)((u8 *)&g.d_006385b4))
#define mem_handle2 (*(int *)(frame_ + FRAME_OFF(4)))
#define prev (*(int * *)(frame_ + FRAME_OFF(8)))
#define i (*(uint *)(frame_ + FRAME_OFF(12)))
#define result (*(MMRESULT *)(frame_ + FRAME_OFF(16)))
#define bytes_per_buffer (*(uint *)(frame_ + FRAME_OFF(20)))
#define buffer (*(int * *)(frame_ + FRAME_OFF(24)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

MMRESULT __cdecl snd_wave_alloc_buffers(uint total_bytes,HWAVEOUT wave_out,uint buffer_count)

{
  int data;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  buffer = (int *)0x0;
  bytes_per_buffer = total_bytes / buffer_count;
  if (snd_wave_device_open == 0) {
    result = 3;
  }
  else {
    for (i = 0; i < buffer_count; i++) {
      prev = buffer;
      buffer = (int *)snd_global_alloc_lock(0x20,(iptr)&mem_handle2);
      if (buffer == (int *)0x0) {
        if (i != 0) {
          snd_wave_reset_all(wave_out);
        }
        return 4;
      }
      if (i == 0) {
        snd_wave_buffer_ring = (iptr)buffer;
        snd_wave_cur_buffer = (iptr)buffer;
      }
      _memset(buffer,0,0x20);
      buffer[2] = mem_handle2;
      data = snd_global_alloc_lock(bytes_per_buffer + 0x20,(iptr)&mem_handle2);
      *buffer = data;
      if (*buffer == 0) {
        if (i != 0) {
          snd_wave_reset_all(wave_out);
        }
        return 4;
      }
      _memset((void *)*buffer,0,0x20);
      *(int *)*buffer = *buffer + 0x20;
      buffer[4] = *(int *)*buffer;
      *(uint *)(*buffer + 4) = bytes_per_buffer;
      buffer[6] = *(int *)(*buffer + 4);
      buffer[5] = *(int *)*buffer + buffer[6];
      *(int **)(*buffer + 0xc) = buffer;
      buffer[1] = mem_handle2;
      buffer[3] = buffer[3] & 0xffff807fU | (i & 0xff) << 7;
      result = waveOutPrepareHeader(wave_out,(LPWAVEHDR)*buffer,0x20);
      if (result != 0) {
        snd_waveout_error_box(result);
        snd_wave_reset_all(wave_out);
        return 5;
      }
      *(uint *)(*buffer + 0x10) = *(uint *)(*buffer + 0x10) | 1;
      if (prev != (int *)0x0) {
        prev[7] = (int)buffer;
      }
      result = 0;
    }
    buffer[7] = snd_wave_buffer_ring;
    snd_wave_buffers_ready_i32 = 1;
    snd_wave_total_buffer_bytes = total_bytes;
  }
  return result;
}
#undef snd_wave_total_buffer_bytes
#undef snd_wave_buffers_ready_i32
#undef mem_handle2
#undef prev
#undef i
#undef result
#undef bytes_per_buffer
#undef buffer

/* 005d6685 auto */
#define snd_wave_buffer_count (*(int *)((u8 *)&g.d_00638588))
#define i (*(uint *)(frame_ + FRAME_OFF(0)))
#define tail2 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define buffer (*(iptr *)(frame_ + FRAME_OFF(8)))
void __cdecl snd_wave_add_buffers(int count)

{
  iptr next_spare;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  buffer = snd_wave_spare_buffers;
  *(uint *)(snd_wave_spare_buffers + 0xc) = *(uint *)(snd_wave_spare_buffers + 0xc) & 0xfffffffe;
  for (i = 0; (int)i < count - 1; i++) {
    buffer = *(int *)(buffer + 0x1c);
    *(uint *)(buffer + 0xc) = *(uint *)(buffer + 0xc) & 0xfffffffe;
  }
  tail2 = snd_wave_buffer_ring;
  for (i = 0; i < snd_wave_buffer_count - 1U; i++) {
    tail2 = *(iptr *)(tail2 + 0x1c);
  }
  next_spare = *(iptr *)(buffer + 0x1c);
  *(iptr *)(tail2 + 0x1c) = snd_wave_spare_buffers;
  snd_wave_spare_buffers = next_spare;
  *(iptr *)(buffer + 0x1c) = snd_wave_buffer_ring;
  snd_wave_buffer_count += count;
  return;
}
#undef snd_wave_buffer_count
#undef i
#undef tail2
#undef buffer

/* 005d673a auto */
#define snd_wave_buffer_count (*(int *)((u8 *)&g.d_00638588))
#define i (*(int *)(frame_ + FRAME_OFF(4)))
#define buffer (*(iptr *)(frame_ + FRAME_OFF(16)))
void __cdecl snd_wave_remove_buffers(int count)

{
  iptr removed;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  buffer = snd_wave_buffer_ring;
  if ((uint)(snd_wave_buffer_count - count) <= (*(uint *)(snd_wave_cur_buffer + 0xc) >> 7 & 0xff)) {
    snd_wave_cur_buffer = snd_wave_buffer_ring;
  }
  for (i = 0; i < (int)((snd_wave_buffer_count - count) - 1U); i++) {
    buffer = *(iptr *)(buffer + 0x1c);
  }
  removed = *(iptr *)(buffer + 0x1c);
  *(iptr *)(buffer + 0x1c) = snd_wave_buffer_ring;
  buffer = removed;
  for (i = 0; i < count; i++) {
    *(uint *)(buffer + 0xc) = *(uint *)(buffer + 0xc) & 0xfffffffd;
    *(uint *)(buffer + 0xc) = *(uint *)(buffer + 0xc) & 0xfffffffb;
    *(uint *)(buffer + 0xc) = *(uint *)(buffer + 0xc) | 1;
    *(uint *)(buffer + 0xc) = *(uint *)(buffer + 0xc) & 0xfffffff7;
    *(uint *)(buffer + 0xc) = *(uint *)(buffer + 0xc) & 0xffffffef;
    *(uint *)(buffer + 0xc) = *(uint *)(buffer + 0xc) & 0xffffffdf;
    *(uint *)(buffer + 0xc) = *(uint *)(buffer + 0xc) & 0xffffffbf;
    buffer = *(iptr *)(buffer + 0x1c);
  }
  buffer = removed;
  for (i = 0; i < count - 1; i++) {
    buffer = *(iptr *)(buffer + 0x1c);
  }
  *(iptr *)(buffer + 0x1c) = snd_wave_spare_buffers;
  snd_wave_spare_buffers = removed;
  snd_wave_buffer_count -= count;
  return;
}
#undef snd_wave_buffer_count
#undef i
#undef buffer

/* 005d687b auto */
#define snd_wave_buffer_count (*(uint *)((u8 *)&g.d_00638588))
#define snd_wave_max_buffers (*(uint *)((u8 *)&g.d_00638584))
#define snd_wave_out_handle (*(int *)((u8 *)&g.d_00638578))
void __cdecl snd_wave_set_buffer_count(uint count)

{
  if ((snd_wave_out_handle != 0) &&
     (((snd_wave_sources == 0 || (*(short *)(snd_wave_sources + 0x88) != 4)) ||
      ((*(uint *)(snd_wave_sources + 0x70) >> 1 & 1) != 0)))) {
    if (snd_wave_max_buffers < count) {
      count = snd_wave_max_buffers;
    }
    if ((int)count < 2) {
      count = 2;
    }
    if (snd_wave_buffer_count < count) {
      snd_wave_add_buffers(count - snd_wave_buffer_count);
    }
    else if (count < snd_wave_buffer_count) {
      snd_wave_remove_buffers(snd_wave_buffer_count - count);
    }
  }
  return;
}
#undef snd_wave_buffer_count
#undef snd_wave_max_buffers
#undef snd_wave_out_handle

/* 005d6947 auto */
#define snd_wave_out_handle (*(HWAVEOUT *)((u8 *)&g.d_00638578))
#define i (*(uint *)(frame_ + FRAME_OFF(4)))
#define result (*(uint *)(frame_ + FRAME_OFF(8)))
#define sample (*(byte * *)(frame_ + FRAME_OFF(12)))
i32 __cdecl snd_wave_write_pending(iptr buffer)

{
  MMRESULT MVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  result = result & 0xffff0000;
  while ((*(uint *)(buffer + 0xc) >> 6 & 1) != 0) {
    sample = (byte *)**(i32 **)buffer;
    for (i = 0; i < *(uint *)(*(int *)buffer + 4); i++) {
      *sample = *sample ^ 0x80;
      sample++;
    }
    MVar1 = waveOutWrite(snd_wave_out_handle,*(LPWAVEHDR *)buffer,0x20);
    result = CONCAT22((*(i16 *)((char *)&result + 2)),(short)MVar1);
    if ((short)MVar1 == 0) {
      *(uint *)(buffer + 0xc) = *(uint *)(buffer + 0xc) | 0x20;
      *(uint *)(buffer + 0xc) = *(uint *)(buffer + 0xc) & 0xffffffbf;
    }
    else {
      if ((MVar1 & 0xffff) != 0x21) {
        snd_waveout_error_box(result);
      }
      *(uint *)(buffer + 0xc) = *(uint *)(buffer + 0xc) & 0xffffffdf;
    }
    buffer = *(iptr *)(buffer + 0x1c);
  }
  return 0;
}
#undef snd_wave_out_handle
#undef i
#undef result
#undef sample

/* 005d6a2c auto */
#define snd_wave_buffer_count (*(uint *)((u8 *)&g.d_00638588))
#define snd_wave_notify_hwnd (*(HWND *)((u8 *)&g.d_0063857c))
#define snd_wave_out_handle (*(HWAVEOUT *)((u8 *)&g.d_00638578))
#define snd_wave_stop_pending_i16 (*(i16 *)((u8 *)&g.d_006385b8))
#define snd_stop_drained_msg_count_i32 (*(i32 *)((u8 *)&g.d_006385d4))
#define msg (*(tagMSG *)(frame_ + FRAME_OFF(0)))
#define source (*(iptr *)(frame_ + FRAME_OFF(28)))
#define i (*(uint *)(frame_ + FRAME_OFF(32)))
#define prev (*(iptr *)(frame_ + FRAME_OFF(36)))
#define buffer (*(iptr *)(frame_ + FRAME_OFF(40)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl snd_wave_stop_all(void)

{
  BOOL BVar1;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  prev = 0;
  snd_wave_stop_pending_i16 = 0;
  source = snd_wave_sources;
  if (snd_wave_out_handle != (HWAVEOUT)0x0) {
    waveOutReset(snd_wave_out_handle);
    while (BVar1 = PeekMessageA(&msg,snd_wave_notify_hwnd,0x3bd,0x3bd,1), BVar1 != 0) {
      snd_stop_drained_msg_count_i32++;
    }
    while (source != 0) {
      if (*(short *)(source + 0x88) == 4) {
        prev = source;
        source = *(iptr *)(source + 0xb8);
      }
      else {
        source = snd_wave_free(prev,source);
      }
    }
    buffer = snd_wave_buffer_ring;
    if (snd_wave_buffer_ring != 0) {
      for (i = 0; i < snd_wave_buffer_count; i++) {
        *(uint *)(buffer + 0xc) = *(uint *)(buffer + 0xc) & 0xffffffdf;
        *(uint *)(buffer + 0xc) = *(uint *)(buffer + 0xc) & 0xffffffbf;
        buffer = *(iptr *)(buffer + 0x1c);
      }
    }
  }
  return;
}
#undef snd_wave_buffer_count
#undef snd_wave_notify_hwnd
#undef snd_wave_out_handle
#undef snd_wave_stop_pending_i16
#undef snd_stop_drained_msg_count_i32
#undef msg
#undef source
#undef i
#undef prev
#undef buffer

/* 005d6b4c auto */
#define i (*(uptr *)(frame_ + FRAME_OFF(0)))
void __cdecl snd_fill_silence_u8(iptr dest,uint length)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (i = 0; i < length; i++) {
    *(i8 *)(i + dest) = 0x80;
  }
  return;
}
#undef i

/* 005d6b89 auto */
#define snd_wave_buffer_count (*(uint *)((u8 *)&g.d_00638588))
#define snd_wave_max_buffers (*(uint *)((u8 *)&g.d_00638584))
#define snd_wave_stop_pending_i16 (*(i16 *)((u8 *)&g.d_006385b8))
#define i (*(uint *)(frame_ + FRAME_OFF(4)))
#define result (*(i32 *)(frame_ + FRAME_OFF(12)))
#define buffer (*(int * *)(frame_ + FRAME_OFF(16)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __cdecl snd_wave_reset_all(HWAVEOUT wave_out)

{
  int *next;
  iptr ring;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  ring = snd_wave_buffer_ring;
  buffer = (int *)snd_wave_buffer_ring;
  snd_wave_stop_pending_i16 = 0;
  if (snd_wave_device_open != 0) {
    waveOutReset(wave_out);
  }
  if (snd_wave_buffer_count != snd_wave_max_buffers) {
    snd_wave_set_buffer_count(snd_wave_max_buffers);
  }
  if (ring != 0) {
    for (i = 0; i < snd_wave_max_buffers; i++) {
      next = (int *)buffer[7];
      if (*buffer != 0) {
        waveOutUnprepareHeader(wave_out,(LPWAVEHDR)*buffer,0x20);
        snd_global_free(buffer[1]);
      }
      snd_global_free(buffer[2]);
      buffer = next;
    }
  }
  snd_wave_buffer_ring = 0;
  do {
    snd_wave_sources = snd_wave_free(0,snd_wave_sources);
  } while (snd_wave_sources != 0);
  snd_wave_sources = 0;
  return result;
}
#undef snd_wave_buffer_count
#undef snd_wave_max_buffers
#undef snd_wave_stop_pending_i16
#undef i
#undef result
#undef buffer

/* 005d6c99 auto */
#define snd_wave_block_align (*(i8 *)((u8 *)&g.d_006385ac))
#define snd_wave_buffer_count (*(uint *)((u8 *)&g.d_00638588))
#define snd_avi_fill_count_i32 (*(i32 *)((u8 *)&g.d_00638594))
#define source (*(i32 * *)(frame_ + FRAME_OFF(0)))
#define i (*(uint *)(frame_ + FRAME_OFF(4)))
#define sample (*(byte * *)(frame_ + FRAME_OFF(8)))
#define buffer (*(int * *)(frame_ + FRAME_OFF(16)))
#define prev (*(i32 * *)(frame_ + FRAME_OFF(24)))
#define active_count (*(int *)(frame_ + FRAME_OFF(28)))
#define result (*(uint *)(frame_ + FRAME_OFF(32)))
#define done_callback (*(code * *)(frame_ + FRAME_OFF(40)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __cdecl snd_wave_on_buffer_done(HWAVEOUT wave_out,iptr wave_hdr)

{
  i16 sound_id;
  i32 *hdr;
  int src;
  MMRESULT MVar5;
  iptr first_source;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  first_source = snd_wave_sources;
  result = result & 0xffff0000;
  done_callback = (code *)0x0;
  sound_id = 0;
  if (snd_wave_device_open != 0) {
    buffer = *(int **)(wave_hdr + 0xc);
    i = 0;
    while ((i < snd_wave_buffer_count &&
           (snd_wave_cur_buffer = *(int *)(snd_wave_cur_buffer + 0x1c),
           (*(uint *)(snd_wave_cur_buffer + 0xc) >> 5 & 1) == 0))) {
      i++;
    }
    if ((*(byte *)(buffer + 3) & 1) == 0) {
      source = (i32 *)snd_wave_sources;
      if ((((snd_wave_sources != 0) && (*(short *)(snd_wave_sources + 0x88) == 4)) &&
          (((uint)buffer[3] >> 1 & 1) != 0)) && (((uint)buffer[3] >> 4 & 1) != 0)) {
        **(ushort **)(snd_wave_sources + 0x8c) = **(ushort **)(snd_wave_sources + 0x8c) & 0xfffb;
        *(uint *)(first_source + 0x70) = *(uint *)(first_source + 0x70) | 2;
      }
      do {
        hdr = (i32 *)*buffer;
        sample = *(byte **)*buffer;
        while ((source != (i32 *)0x0 && ((*(uint *)((int)source + 0x70) >> 1 & 1) != 0)))
        {
          source = *(i32 **)((int)source + 0xb8);
        }
        if (source == (i32 *)0x0) {
          snd_fill_silence_u8(*(iptr *)*buffer,*(i32 *)(*buffer + 4));
          buffer[3] = buffer[3] & 0xffffffdf;
        }
        else {
          if (((uint)buffer[3] >> 6 & 1) == 0) {
            if (*(short *)((int)source + 0x88) == 4) {
              if (((uint)buffer[3] >> 3 & 1) == 0) {
                snd_avi_fill_buffer((iptr)buffer,(iptr)source);
                snd_avi_fill_count_i32++;
              }
              src = ((uint)buffer[3] >> 7 & 0xff) * *(int *)((int)source + 0x9c) +
                      *(int *)((int)source + 0x30);
              snd_resample_8bit(buffer[4],src,buffer[6] / (int)(uint)(ushort)snd_wave_block_align,
                           CONCAT22((short)((uint)source >> 0x10),
                                    *(i16 *)((int)source + 0x80)),
                           CONCAT22((short)((uint)src >> 0x10),(ushort)snd_wave_block_align));
              if (((uint)buffer[3] >> 1 & 1) != 0) {
                buffer[3] = buffer[3] | 0x10;
              }
            }
            else {
              snd_wave_copy_source((iptr)source,*hdr,hdr[1]);
            }
            for (source = *(i32 **)((int)source + 0xb8); source != (i32 *)0x0;
                source = *(i32 **)((int)source + 0xb8)) {
              if ((*(uint *)((int)source + 0x70) >> 1 & 1) == 0) {
                snd_wave_mix_source((uptr)source,*hdr,hdr[1]);
              }
            }
            buffer[3] = buffer[3] | 0x40;
            *(uint *)(*buffer + 0x10) = *(uint *)(*buffer + 0x10) & 0xfffffffe;
          }
          for (i = 0; i < (uint)hdr[1]; i++) {
            *sample = *sample ^ 0x80;
            sample++;
          }
          MVar5 = waveOutWrite(wave_out,(LPWAVEHDR)*buffer,0x20);
          result = CONCAT22((*(i16 *)((char *)&result + 2)),(short)MVar5);
          if ((short)MVar5 == 0) {
            buffer[3] = buffer[3] & 0xffffffbf;
            buffer[3] = buffer[3] | 0x20;
            buffer[3] = buffer[3] & 0xfffffff7;
          }
          else {
            snd_waveout_error_box(result);
            buffer[3] = buffer[3] & 0xffffffdf;
          }
        }
        source = (i32 *)snd_wave_sources;
        prev = (i32 *)0x0;
        active_count = 0;
        while (source != (i32 *)0x0) {
          if ((*(byte *)(source + 0x1c) & 1) == 0) {
            if (((((uint)source[0x1c] >> 1 & 1) == 0) &&
                (active_count = active_count + 1, ((uint)source[0x1c] >> 3 & 1) != 0)) &&
               (*(short *)(source + 0x22) != 4)) {
              if (((uint)source[0x1c] >> 2 & 1) == 0) {
                mmioAdvance((HMMIO)*source,(LPMMIOINFO)(source + 6),0);
              }
              else {
                snd_wave_stream_refill((iptr)source);
              }
            }
            prev = source;
            source = (i32 *)source[0x2e];
          }
          else if (*(short *)(source + 0x22) == 4) {
            prev = source;
            source = (i32 *)source[0x2e];
          }
          else {
            if (source[0x2d] != 0) {
              done_callback = (code *)source[0x2d];
              source[0x2d] = 0;
              sound_id = *(i16 *)((int)source + 0x8a);
            }
            source = (i32 *)snd_wave_free((iptr)prev,(iptr)source);
          }
        }
        source = (i32 *)snd_wave_sources;
        buffer = (int *)buffer[7];
      } while ((active_count != 0) && (((uint)buffer[3] >> 5 & 1) == 0));
      if (done_callback != (code *)0x0) {
        (*done_callback)(sound_id);
      }
    }
  }
  return 0;
}
#undef snd_wave_block_align
#undef snd_wave_buffer_count
#undef snd_avi_fill_count_i32
#undef source
#undef i
#undef sample
#undef buffer
#undef prev
#undef active_count
#undef result
#undef done_callback

/* 005d717f auto */
#define snd_wave_block_align (*(i8 *)((u8 *)&g.d_006385ac))
#define source (*(i32 * *)(frame_ + FRAME_OFF(0)))
#define prev (*(i32 * *)(frame_ + FRAME_OFF(20)))
i32 __cdecl snd_wave_mix_buffer(i32 *hdr)

{
  bool finished;
  i32 result;
  int src;
  iptr buffer;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  finished = false;
  if (snd_wave_device_open == 0) {
    result = 0;
  }
  else {
    buffer = hdr[3];
    *(uint *)(buffer + 0xc) = *(uint *)(buffer + 0xc) & 0xfffffffd;
    source = (i32 *)snd_wave_sources;
    while ((source != (i32 *)0x0 && ((*(uint *)((int)source + 0x70) >> 1 & 1) != 0))) {
      source = *(i32 **)((int)source + 0xb8);
    }
    if (source == (i32 *)0x0) {
      *(uint *)(buffer + 0xc) = *(uint *)(buffer + 0xc) & 0xffffffdf;
    }
    else {
      if ((*(uint *)(buffer + 0xc) >> 6 & 1) == 0) {
        if (*(short *)((int)source + 0x88) == 4) {
          src = (*(uint *)(buffer + 0xc) >> 7 & 0xff) * *(int *)((int)source + 0x9c) +
                  *(int *)((int)source + 0x30);
          snd_resample_8bit(*(i32 *)(buffer + 0x10),src,
                       *(int *)(buffer + 0x18) / (int)(uint)(ushort)snd_wave_block_align,
                       CONCAT22((short)((uint)source >> 0x10),
                                *(i16 *)((int)source + 0x80)),
                       CONCAT22((short)((uint)src >> 0x10),(ushort)snd_wave_block_align));
        }
        else {
          src = snd_wave_copy_source((iptr)source,*hdr,hdr[1]);
          if (src == 1) {
            finished = true;
          }
        }
        *(uint *)(buffer + 0xc) = *(uint *)(buffer + 0xc) | 0x40;
        source = *(i32 **)((int)source + 0xb8);
      }
      for (; source != (i32 *)0x0; source = *(i32 **)((int)source + 0xb8)) {
        if (((*(uint *)((int)source + 0x70) >> 1 & 1) == 0) &&
           (src = snd_wave_mix_source((uptr)source,*hdr,hdr[1]), src == 0)) {
          finished = false;
        }
      }
      hdr[4] = hdr[4] & 0xfffffffe;
    }
    source = (i32 *)snd_wave_sources;
    prev = (i32 *)0x0;
    while (source != (i32 *)0x0) {
      if ((*(byte *)(source + 0x1c) & 1) == 0) {
        if ((((uint)source[0x1c] >> 1 & 1) == 0) && (((uint)source[0x1c] >> 3 & 1) != 0)) {
          if (*(short *)(source + 0x22) == 4) {
            snd_avi_stream_refill((iptr)source);
          }
          if (*(short *)(source + 0x22) != 4) {
            if (((uint)source[0x1c] >> 2 & 1) == 0) {
              mmioAdvance((HMMIO)*source,(LPMMIOINFO)(source + 6),0);
            }
            else {
              snd_wave_stream_refill((iptr)source);
            }
          }
        }
        prev = source;
        source = (i32 *)source[0x2e];
      }
      else if (*(short *)(source + 0x22) == 4) {
        *(uint *)(buffer + 0xc) = *(uint *)(buffer + 0xc) | 2;
        source[0x1c] = source[0x1c] | 2;
        prev = source;
        source = (i32 *)source[0x2e];
      }
      else {
        source = (i32 *)snd_wave_free((iptr)prev,(iptr)source);
      }
    }
    if ((snd_wave_sources == 0) || (finished)) {
      result = 1;
    }
    else {
      result = 0;
    }
  }
  return result;
}
#undef snd_wave_block_align
#undef source
#undef prev

/* 005d7494 auto */
#define snd_wave_source_count (*(short *)((u8 *)&g.d_0063858c))
iptr __cdecl snd_wave_free(iptr prev,iptr source)

{
  iptr next;
  iptr new_head;
  
  if (source == 0) {
    next = 0;
  }
  else {
    next = *(iptr *)(source + 0xb8);
    new_head = next;
    if (prev != 0) {
      *(iptr *)(prev + 0xb8) = next;
      new_head = snd_wave_sources;
    }
    snd_wave_sources = new_head;
    mmioClose(*(HMMIO *)source,0);
    if ((*(uint *)(source + 0x70) >> 2 & 1) != 0) {
      mmioClose(*(HMMIO *)(source + 0x60),0);
    }
    GlobalUnlock(*(HGLOBAL *)(source + 0x6c));
    GlobalFree(*(HGLOBAL *)(source + 0x6c));
    snd_wave_source_count--;
  }
  return next;
}
#undef snd_wave_source_count

/* 005d753e auto */
#define snd_wave_block_align (*(i8 *)((u8 *)&g.d_006385ac))
#define count (*(uint *)(frame_ + FRAME_OFF(4)))
#define remaining (*(uint *)(frame_ + FRAME_OFF(12)))
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

i32 __cdecl snd_wave_copy_source(iptr source,int dst,uint length)

{
  ushort consumed;
  uint want;
  uint avail;
  i32 result;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  want = length / (ushort)snd_wave_block_align;
  if ((source == 0) || ((*(byte *)(source + 0x70) & 1) != 0)) {
    count = 0;
  }
  else {
    if ((*(uint *)(source + 0x70) >> 2 & 1) == 0) {
      remaining = *(int *)(source + 8) - *(int *)(source + 100);
    }
    else {
      remaining = *(int *)(source + 0x3c) - *(int *)(source + 0x34);
    }
    avail = remaining / *(ushort *)(source + 0x80);
    count = want;
    if (avail < want) {
      *(uint *)(source + 0x70) = *(uint *)(source + 0x70) | 1;
      count = avail;
    }
    if ((uint)(*(int *)(source + 0x3c) - *(int *)(source + 0x34)) /
        (uint)*(ushort *)(source + 0x80) < want * 2) {
      *(uint *)(source + 0x70) = *(uint *)(source + 0x70) | 8;
    }
    else {
      *(uint *)(source + 0x70) = *(uint *)(source + 0x70) & 0xfffffff7;
    }
    want -= count;
  }
  if (count != 0) {
    consumed = snd_resample_8bit(dst,*(i32 *)(source + 0x34),count,
                         CONCAT22((short)((uint)source >> 0x10),*(i16 *)(source + 0x80)),
                         CONCAT22((short)(want >> 0x10),(ushort)snd_wave_block_align));
    *(int *)(source + 0x34) = *(int *)(source + 0x34) + (uint)consumed;
    if ((*(short *)(source + 0x88) == 4) && (*(int *)(source + 0x3c) == *(int *)(source + 0x34)))
    {
      *(i32 *)(source + 0x34) = *(i32 *)(source + 0x30);
    }
    *(uint *)(source + 0x70) = *(uint *)(source + 0x70) & 0xffffffef;
  }
  if (want == 0) {
    if ((*(uint *)(source + 0x70) >> 2 & 1) == 0) {
      *(int *)(source + 100) = *(int *)(source + 100) + *(ushort *)(source + 0x80) * count;
    }
    else {
      *(i32 *)(source + 100) = 0;
    }
    result = 0;
  }
  else {
    _memset((void *)(dst + (ushort)snd_wave_block_align * count),0,(ushort)snd_wave_block_align * want);
    if ((source != 0) && (remaining != 0)) {
      *(int *)(source + 100) = *(int *)(source + 100) + *(ushort *)(source + 0x80) * count;
    }
    result = 1;
  }
  return result;
}
#undef snd_wave_block_align
#undef count
#undef remaining

/* 005d778c auto */
#define snd_wave_block_align (*(i8 *)((u8 *)&g.d_006385ac))
#define advance (*(i32 *)(frame_ + FRAME_OFF(4)))
#define count (*(i32 *)(frame_ + FRAME_OFF(8)))
#define remaining (*(uint *)(frame_ + FRAME_OFF(12)))
i32 __cdecl snd_wave_mix_source(uptr source,i32 dst,uint length)

{
  ushort consumed;
  uint avail;
  uint want;
  uptr flags;
  i32 result;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((*(uint *)(source + 0x70) >> 2 & 1) == 0) {
    remaining = *(int *)(source + 8) - *(int *)(source + 100);
  }
  else {
    remaining = *(int *)(source + 0x3c) - *(int *)(source + 0x34);
  }
  avail = remaining / *(ushort *)(source + 0x80);
  want = length / (ushort)snd_wave_block_align;
  count = want;
  if (avail < want) {
    *(uint *)(source + 0x70) = *(uint *)(source + 0x70) | 1;
    count = avail;
  }
  if ((uint)(*(int *)(source + 0x3c) - *(int *)(source + 0x34)) /
      (uint)*(ushort *)(source + 0x80) < want * 2) {
    flags = *(uint *)(source + 0x70) | 8;
    *(uptr *)(source + 0x70) = flags;
  }
  else {
    *(uint *)(source + 0x70) = *(uint *)(source + 0x70) & 0xfffffff7;
    flags = source;
  }
  if (count != 0) {
    consumed = snd_mix_8bit_resample(dst,*(i32 *)(source + 0x34),count,
                         CONCAT22((short)(source >> 0x10),*(i16 *)(source + 0x80)),
                         CONCAT22((short)(flags >> 0x10),(ushort)snd_wave_block_align));
    advance = (uint)consumed;
    *(int *)(source + 0x34) = *(int *)(source + 0x34) + advance;
  }
  if ((*(uint *)(source + 0x70) >> 2 & 1) == 0) {
    *(int *)(source + 100) = *(int *)(source + 100) + *(ushort *)(source + 0x80) * count;
  }
  else {
    *(i32 *)(source + 100) = 0;
  }
  if (((*(byte *)(source + 0x70) & 1) == 0) || ((*(uint *)(source + 0x70) >> 2 & 1) != 0)) {
    result = 0;
  }
  else {
    result = 1;
  }
  return result;
}
#undef snd_wave_block_align
#undef advance
#undef count
#undef remaining

/* 005d791b auto */
#define byte_count (*(uint *)(frame_ + FRAME_OFF(4)))
#define i (*(uint *)(frame_ + FRAME_OFF(8)))
#define bytes_read (*(int *)(frame_ + FRAME_OFF(16)))
i32 __cdecl snd_avi_fill_buffer(iptr buffer,iptr source)

{
  i32 result;
  uint limit;
  iptr head;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  head = snd_wave_sources;
  if (*(int *)(source + 0x98) == buffer) {
    byte_count = *(int *)(snd_wave_sources + 0x9c) - *(int *)(snd_wave_sources + 0x68);
    bytes_read = 0;
    limit = *(int *)(snd_wave_sources + 8) -
            (*(int *)(snd_wave_sources + 0x90) - *(int *)(snd_wave_sources + 0x94));
    if (limit < byte_count) {
      byte_count = limit;
    }
    AVIStreamRead(*(i32 *)(snd_wave_sources + 0x84),
                  *(uint *)(snd_wave_sources + 0x90) / (uint)*(ushort *)(snd_wave_sources + 0x80),
                  byte_count / *(ushort *)(snd_wave_sources + 0x80),*(i32 *)(snd_wave_sources + 0x34)
                  ,byte_count,&bytes_read,0);
    *(int *)(snd_wave_sources + 0x90) = *(int *)(snd_wave_sources + 0x90) + bytes_read;
    *(int *)(head + 0x34) = *(int *)(head + 0x34) + bytes_read;
    *(int *)(snd_wave_sources + 0x68) = *(int *)(snd_wave_sources + 0x68) + bytes_read;
    if (*(int *)(head + 0x3c) == *(int *)(head + 0x34)) {
      *(i32 *)(head + 0x34) = *(i32 *)(head + 0x30);
    }
    if (*(uint *)(snd_wave_sources + 0x9c) <= *(uint *)(snd_wave_sources + 0x68)) {
      *(uint *)(buffer + 0xc) = *(uint *)(buffer + 0xc) | 8;
      *(i32 *)(snd_wave_sources + 0x98) = *(i32 *)(buffer + 0x1c);
      buffer = *(iptr *)(snd_wave_sources + 0x98);
      *(i32 *)(snd_wave_sources + 0x68) = 0;
    }
    if (*(uint *)(snd_wave_sources + 8) <=
        (uint)(*(int *)(snd_wave_sources + 0x90) - *(int *)(snd_wave_sources + 0x94))) {
      i = 0;
      while ((i < (uint)(*(int *)(snd_wave_sources + 0x9c) - *(int *)(snd_wave_sources + 0x68)) &&
             (*(uint *)(head + 0x34) < *(uint *)(head + 0x3c)))) {
        **(i8 **)(head + 0x34) = 0x80;
        *(int *)(head + 0x34) = *(int *)(head + 0x34) + 1;
        i++;
      }
      if (*(int *)(head + 0x3c) == *(int *)(head + 0x34)) {
        *(i32 *)(head + 0x34) = *(i32 *)(head + 0x30);
      }
      *(uint *)(buffer + 0xc) = *(uint *)(buffer + 0xc) & 0xfffffff7;
      *(uint *)(buffer + 0xc) = *(uint *)(buffer + 0xc) | 2;
      *(uint *)(snd_wave_sources + 0x70) = *(uint *)(snd_wave_sources + 0x70) | 1;
      *(i32 *)(snd_wave_sources + 0x98) = *(i32 *)(buffer + 0x1c);
      *(i32 *)(snd_wave_sources + 0x68) = 0;
    }
    result = 0;
  }
  else {
    result = 0xd;
  }
  return result;
}
#undef byte_count
#undef i
#undef bytes_read

/* 005dd010 auto */
#define avi_current_player_i32 (*(i32 *)((u8 *)&g.d_006389d0))
#define eh_next (*(i32 *)(frame_ + FRAME_OFF(0)))
#define eh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

DocumentWindow * __thiscall mmwnd_ctor(DocumentWindow *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  surfwnd_ctor((SurfaceWindow *)this);
  eh_state = 0;
  avi_audio_ctor((AviAudio *)&this->border_width);
  (*(i8 *)((char *)&eh_state + 0)) = 1;
  palette_init((GamePalette *)&this->client_x);
  eh_state = CONCAT31((*(i32 *)((char *)&eh_state + 1)),2);
  surface_ctor((DibSurface *)(this->movie_surface));
  this->vtable = (u32)&PTR_FUN_0061d718;
  this->style_flags = 0;
  this->double_size = 0;
  this->avi_option = 0;
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
  avi_current_player_i32 = this;
  return this;
}
#undef avi_current_player_i32
#undef eh_next
#undef eh_handler
#undef eh_state

/* 005dd1a0 auto */
#define avi_current_player_i32 (*(i32 *)((u8 *)&g.d_006389d0))
#define eh_next (*(i32 *)(frame_ + FRAME_OFF(0)))
#define eh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define eh_state (*(int *)(frame_ + FRAME_OFF(8)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __thiscall avi_player_dtor(AviPlayer *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  *(i8 ***)this->media_window_base = &PTR_FUN_0061d718;
  (*(i32 *)((char *)&eh_state + 1)) = 0;
  (*(i8 *)((char *)&eh_state + 0)) = 3;
  avi_play_pause((iptr)this);
  avi_close((iptr)this);
  avi_current_player_i32 = 0;
  (*(i8 *)((char *)&eh_state + 0)) = 2;
  /* inlined unwind funclet 005dd230 */ { surface_dtor((DibSurface *)(*(int *)((iptr)&this) + 0x558)); }
  (*(i8 *)((char *)&eh_state + 0)) = 1;
  /* inlined unwind funclet 005dd23f */ { palette_destroy((GamePalette *)(*(int *)((iptr)&this) + 0x124)); }
  eh_state = (uint)(*(i32 *)((char *)&eh_state + 1)) << 8;
  /* inlined unwind funclet 005dd24e */ { avi_audio_release((AviAudioReleaseView *)(*(int *)((iptr)&this) + 0x11c)); }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 005dd25d */ { surfwnd_dtor(*(SurfaceWindow **)((iptr)&this)); }
  return eh_next;
}
#undef avi_current_player_i32
#undef eh_next
#undef eh_handler
#undef eh_state

/* 005dd27e auto */
void __thiscall
avi_player_create
          (MediaWindow *this,iptr parent,i32 style,u32 x,u32 y)

{
  surface_wnd_create
            ((DibSurface *)this,parent,style,x,y,0x140,0xf0,(iptr)&this->client_x
            );
  surface_fill((DibSurface *)this,0);
  this->pos_x = x;
  this->pos_y = y;
  return;
}

/* 005dd2e3 auto */
#define target_dib (*(iptr *)(frame_ + FRAME_OFF(0)))
void __thiscall
avi_player_create_child
          (MediaWindow *this,iptr parent,i32 style,u32 x,u32 y,iptr target
          )

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (target == 0) {
    target_dib = 0;
  }
  else {
    target_dib = target + 0x48;
  }
  wnd_create_with_surface
            ((DibSurface *)this,parent,style,x,y,0x140,0xf0,(iptr)&this->client_x
             ,target_dib);
  surface_fill((DibSurface *)this,0);
  this->target_surface = target;
  this->pos_x = x;
  this->pos_y = y;
  return;
}
#undef target_dib

/* 005dd377 auto */
int __thiscall avi_player_open(AviPlayerOpenView *this,iptr filename)

{
  int result;
  
  avi_close((iptr)this);
  result = avi_open_file((iptr)this,filename);
  if (result == 0) {
    result = 0;
  }
  return result;
}

/* 005dd3c2 auto */
void __thiscall avi_player_play(AviPlayerPlayView *this)

{
  ((AviPlayerPlayViewExt *)this)->loop_flag[0] = '\0';
  ((AviPlayerPlayViewExt *)this)->loop_flag_byte1[0] = '\0';
  ((AviPlayerPlayViewExt *)this)->loop_flag_byte2[0] = '\0';
  ((AviPlayerPlayViewExt *)this)->loop_flag_byte3[0] = '\0';
  avi_play_start((iptr)this);
  return;
}

/* 005dd3f1 auto */
void __thiscall avi_player_play_range(AviPlayerRangeView *this,u32 first_frame,u32 last_frame)

{
  if ((int)first_frame <= (int)last_frame) {
    this->loop = 0;
    avi_seek_frame((iptr)this,first_frame,0);
    this->end_frame = last_frame;
    this->start_frame = first_frame;
    avi_play_start((iptr)this);
  }
  return;
}

/* 005dd45d auto */
void __thiscall avi_player_show_frame(void *this,i32 frame)

{
  avi_seek_frame((iptr)this,frame,1);
  return;
}

/* 005dd4c2 auto */
void __thiscall avi_player_loop_range(AviPlayerLoopView *this,u32 first_frame,u32 last_frame)

{
  this->start_frame = first_frame;
  avi_seek_frame((iptr)this,first_frame,0);
  this->end_frame = last_frame;
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
void __thiscall avi_player_set_palette(DibSurface *this,iptr palette)

{
  avi_apply_palette((iptr)this,palette);
  surface_set_palette(this,palette);
  wnd_set_palette((WndBase *)(this + 1),palette);
  return;
}

/* 005dd64c auto */
#define src_rect (*(tagRECT *)(frame_ + FRAME_OFF(4)))
#define dst_rect (*(tagRECT *)(frame_ + FRAME_OFF(20)))
void __thiscall
avi_player_draw_to(DibSurface *this,iptr dest,int x,int y)

{
  int dest_size;
  int src_size;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((-1 < x) && (-1 < y)) {
    dest_size = surface_width((DibSurface *)dest);
    src_size = surface_get_width(this);
    if (src_size <= dest_size - x) {
      dest_size = surface_height((DibSurface *)dest);
      src_size = surface_get_height(this);
      if (src_size <= dest_size - y) {
        avi_decode_frame((iptr)this,0);
        dest_size = surface_get_height(this);
        src_size = surface_get_width(this);
        SetRect(&src_rect,0,0,src_size,dest_size);
        CopyRect(&dst_rect,&src_rect);
        OffsetRect(&dst_rect,x,y);
        surface_blit(this,dest,(iptr)&src_rect,(iptr)&dst_rect);
      }
    }
  }
  return;
}
#undef src_rect
#undef dst_rect

/* 005dd71e auto */
void __thiscall avi_player_set_double_size(MediaWindow *this,i32 enable)

{
  int height;
  int width;
  
  height = surface_get_height((DibSurface *)this);
  height = height * 2;
  width = surface_get_width((DibSurface *)this);
  wnd_resize_clamped((WindowObjectView *)this,width * 2,height);
  this->double_size = 1;
  return;
}

/* 005dd761 auto */
void __thiscall avi_player_set_transparent(AviPlayerSetTransparentView *this,int enable)

{
  if (enable == 0) {
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
#define wnd_class (*(WNDCLASSA *)(frame_ + FRAME_OFF(4)))
void __cdecl snd_system_init(void)

{
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  wnd_class.style = 0;
  wnd_class.lpfnWndProc = snd_mci_notify_wndproc;
  wnd_class.cbClsExtra = 0;
  wnd_class.cbWndExtra = 0;
  wnd_class.hInstance = app_hinstance;
  wnd_class.hIcon = (HICON)0x0;
  wnd_class.hCursor = (HCURSOR)0x0;
  wnd_class.hbrBackground = (HBRUSH)0x0;
  wnd_class.lpszMenuName = (LPCSTR)0x0;
  wnd_class.lpszClassName = s_MSMMWindow_006389e4;
  RegisterClassA(&wnd_class);
  snd_mci_notify_hwnd = CreateWindowExA(0,s_MSMMWindow_006389f0,(LPCSTR)0x0,0,-0x80000000,-0x80000000,
                                 -0x80000000,-0x80000000,(HWND)0x0,(HMENU)0x0,app_hinstance,
                                 (LPVOID)0x0);
  snd_cd_open();
  return;
}
#undef app_hinstance
#undef snd_mci_notify_hwnd
#undef wnd_class

/* 005dd93f auto */
#define snd_cd_device_id (*(uint *)((u8 *)&g.d_006389d8))
#define snd_midi_device_id (*(uint *)((u8 *)&g.d_006389d4))
LRESULT __stdcall snd_mci_notify_wndproc(HWND hwnd,UINT msg,WPARAM wparam,uint lparam)

{
  LRESULT LVar1;
  
  if (msg == 0x3b9) {
    if (wparam == 1) {
      if ((lparam & 0xffff) == snd_midi_device_id) {
        snd_midi_fire_notify_callback();
      }
      else if ((lparam & 0xffff) == snd_cd_device_id) {
        snd_cd_fire_notify_callback();
      }
    }
    LVar1 = 0;
  }
  else {
    LVar1 = DefWindowProcA(hwnd,msg,wparam,lparam);
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
#define play_parms (*(i32 *)(frame_ + FRAME_OFF(0)))
#define from_track (*(uint *)(frame_ + FRAME_OFF(4)))
#define to_track (*(uint *)(frame_ + FRAME_OFF(8)))
#define play_flags (*(DWORD_PTR *)(frame_ + FRAME_OFF(12)))
#define set_parms (*(i32 *)(frame_ + FRAME_OFF(16)))
#define time_format_item (*(uint *)(frame_ + FRAME_OFF(20)))
#define device_id (*(MCIDEVICEID *)(frame_ + FRAME_OFF(24)))
i32 __cdecl snd_cd_play_track(uint track)

{
  MCIERROR MVar1;
  i32 result;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (snd_cd_device_id == 0) {
    snd_cd_open();
    if (snd_cd_device_id == 0) {
      return 0;
    }
    device_id = snd_cd_device_id;
  }
  else {
    device_id = snd_cd_device_id;
    mciSendCommandA(snd_cd_device_id,0x808,0,0);
  }
  set_parms = 0;
  time_format_item = track & 0xff;
  MVar1 = mciSendCommandA(device_id,0x807,8,(DWORD_PTR)&set_parms);
  if (MVar1 == 0) {
    if ((track & 0xff) == snd_cd_track_count) {
      play_flags = 5;
    }
    else {
      play_flags = 0xd;
    }
    from_track = track & 0xff;
    to_track = (uint)(byte)((char)track + 1);
    play_parms = snd_mci_notify_hwnd;
    MVar1 = mciSendCommandA(device_id,0x806,play_flags,(DWORD_PTR)&play_parms);
    if (MVar1 == 0) {
      result = 1;
    }
    else {
      snd_cd_close();
      dbg_logf(ADDR(0x638aa8, ((u8 *)&g.d_00638aa8)),MVar1);
      result = 0;
    }
  }
  else {
    snd_cd_close();
    dbg_logf(ADDR(0x638a84, ((u8 *)&g.d_00638a84)),MVar1);
    result = 0;
  }
  return result;
}
#undef snd_cd_device_id
#undef snd_cd_track_count
#undef snd_mci_notify_hwnd
#undef play_parms
#undef from_track
#undef to_track
#undef play_flags
#undef set_parms
#undef time_format_item
#undef device_id

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
#define open_parms (*(i8 (*)[4])(frame_ + FRAME_OFF(4)))
#define device_id (*(MCIDEVICEID *)(frame_ + FRAME_OFF(8)))
#define device_type (*(char * *)(frame_ + FRAME_OFF(12)))
#define set_parms (*(i8 (*)[4])(frame_ + FRAME_OFF(24)))
#define time_format (*(i32 *)(frame_ + FRAME_OFF(28)))
#define status_parms (*(i32 *)(frame_ + FRAME_OFF(36)))
#define track_count (*(i32 *)(frame_ + FRAME_OFF(40)))
#define status_item (*(i32 *)(frame_ + FRAME_OFF(44)))
#define status_track (*(i32 *)(frame_ + FRAME_OFF(48)))
void __cdecl snd_cd_open(void)

{
  MCIERROR MVar1;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (snd_cd_device_id == 0) {
    device_type = s_cdaudio_00638acc;
    MVar1 = mciSendCommandA(0,0x803,0x2000,(DWORD_PTR)open_parms);
    if (MVar1 == 0) {
      snd_cd_device_id = device_id;
      time_format = 10;
      MVar1 = mciSendCommandA(device_id,0x80d,0x400,(DWORD_PTR)set_parms);
      if (MVar1 == 0) {
        status_parms = 0;
        track_count = 0;
        status_track = 0;
        status_item = 3;
        mciSendCommandA(snd_cd_device_id,0x814,0x100,(DWORD_PTR)&status_parms);
        snd_cd_track_count = track_count;
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
#undef open_parms
#undef device_id
#undef device_type
#undef set_parms
#undef time_format
#undef status_parms
#undef track_count
#undef status_item
#undef status_track

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
#define open_parms (*(i8 (*)[4])(frame_ + FRAME_OFF(4)))
#define opened_id (*(MCIDEVICEID *)(frame_ + FRAME_OFF(8)))
#define device_type (*(char * *)(frame_ + FRAME_OFF(12)))
#define device_id (*(MCIDEVICEID *)(frame_ + FRAME_OFF(28)))
#define set_parms (*(i8 (*)[4])(frame_ + FRAME_OFF(32)))
#define time_format (*(i32 *)(frame_ + FRAME_OFF(36)))
#define status_parms (*(i8 (*)[4])(frame_ + FRAME_OFF(44)))
#define track_count (*(i32 *)(frame_ + FRAME_OFF(48)))
#define status_item (*(i32 *)(frame_ + FRAME_OFF(52)))
i32 __cdecl snd_cd_get_track_count(void)

{
  MCIERROR MVar1;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (snd_cd_device_id == 0) {
    device_type = s_cdaudio_00638b18;
    MVar1 = mciSendCommandA(0,0x803,0x2000,(DWORD_PTR)open_parms);
    if (MVar1 != 0) {
      return 0xffffffff;
    }
    device_id = opened_id;
    snd_cd_device_id = opened_id;
    time_format = 10;
    MVar1 = mciSendCommandA(opened_id,0x80d,0x400,(DWORD_PTR)set_parms);
    if (MVar1 != 0) {
      mciSendCommandA(device_id,0x804,0,0);
      snd_cd_device_id = 0;
      return 0xffffffff;
    }
  }
  else {
    device_id = snd_cd_device_id;
  }
  status_item = 3;
  MVar1 = mciSendCommandA(device_id,0x814,0x100,(DWORD_PTR)status_parms);
  if (MVar1 == 0) {
    snd_cd_track_count = track_count;
  }
  else {
    snd_cd_close();
    track_count = 0xffffffff;
  }
  return track_count;
}
#undef snd_cd_device_id
#undef snd_cd_track_count
#undef open_parms
#undef opened_id
#undef device_type
#undef device_id
#undef set_parms
#undef time_format
#undef status_parms
#undef track_count
#undef status_item

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
void __cdecl snd_cd_set_notify_callback(iptr callback)

{
  snd_cd_notify_callback = callback;
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
#define avi_update_tick_count_i32 (*(i32 *)((u8 *)&g.d_00638dec))
#define avi_indeo_frame_opts_i32 (*(i32 *)((u8 *)&g.d_006e5028))
#define avi_indeo_frame_fourcc_i32 (*(i32 *)((u8 *)&g.d_006e502c))
#define avi_indeo_frame_version_i32 (*(i32 *)((u8 *)&g.d_006e5030))
#define avi_indeo_frame_type_i32 (*(i32 *)((u8 *)&g.d_006e5034))
#define avi_indeo_frame_environment_i32 (*(i32 *)((u8 *)&g.d_006e5038))
#define avi_indeo_frame_flags_i32 (*(i32 *)((u8 *)&g.d_006e503c))
#define avi_indeo_view_rect_ptr_i32 (*(i32 *)((u8 *)&g.d_006e5064))
#define avi_indeo_seq_opts_i32 (*(i32 *)((u8 *)&g.d_006e5098))
#define avi_indeo_seq_fourcc_i32 (*(i32 *)((u8 *)&g.d_006e509c))
#define avi_indeo_seq_version_i32 (*(i32 *)((u8 *)&g.d_006e50a0))
#define avi_indeo_seq_type_i32 (*(i32 *)((u8 *)&g.d_006e50a4))
#define avi_indeo_seq_environment_i32 (*(i32 *)((u8 *)&g.d_006e50a8))
#define avi_indeo_seq_flags_i32 (*(i32 *)((u8 *)&g.d_006e50ac))
#define avi_indeo_seq_extra_i32 (*(i32 *)((u8 *)&g.d_006e50bc))
#define avi_view_rect_width_i32 (*(i32 *)((u8 *)&g.d_006e50d0))
#define avi_view_rect_height_i32 (*(i32 *)((u8 *)&g.d_006e50d4))
#define avi_frames_per_second_i32 (*(i32 *)((u8 *)&g.d_006e50d8))
#define avi_indeo_frame_extra_i32 (*(i32 *)((u8 *)&g.d_006e50dc))
#define palette_rgb (*(i8 (*)[708])(frame_ + FRAME_OFF(0)))
#define stream_info (*(i8 (*)[4])(frame_ + FRAME_OFF(708)))
#define codec_handler (*(i32 *)(frame_ + FRAME_OFF(712)))
#define time_scale (*(uint *)(frame_ + FRAME_OFF(728)))
#define time_rate (*(uint *)(frame_ + FRAME_OFF(732)))
#define suggested_buffer_size (*(SIZE_T *)(frame_ + FRAME_OFF(748)))
#define i (*(iptr *)(frame_ + FRAME_OFF(848)))
#define format_size (*(i32 *)(frame_ + FRAME_OFF(852)))
#define result (*(int *)(frame_ + FRAME_OFF(856)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl avi_open_file(iptr player,i32 filename)

{
  int attach_result;
  i32 start_frame;
  int value;
  iptr dib;
  HGLOBAL mem_handle;
  i8 frame_[FRAME_OFF(864)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (avi_vfw_initialized == 0) {
    AVIFileInit();
    avi_vfw_initialized = 1;
  }
  avi_active_window = player;
  avi_indeo_seq_opts_i32 = 0x2c;
  avi_indeo_seq_fourcc_i32 = 0x31345649;
  avi_indeo_seq_environment_i32 = 2;
  avi_indeo_seq_version_i32 = 0x10002;
  avi_indeo_seq_type_i32 = 4;
  avi_indeo_seq_flags_i32 = 0;
  avi_indeo_seq_extra_i32 = 0;
  avi_indeo_frame_opts_i32 = 0x70;
  avi_indeo_frame_fourcc_i32 = 0x31345649;
  avi_indeo_frame_environment_i32 = 2;
  avi_indeo_frame_version_i32 = 0x10002;
  avi_indeo_frame_type_i32 = 2;
  avi_indeo_view_rect_ptr_i32 = &avi_view_rect_x;
  avi_indeo_frame_flags_i32 = 0x80000008;
  avi_view_rect_x = 0;
  avi_view_rect_y = 0;
  avi_view_rect_width_i32 = 0;
  avi_view_rect_height_i32 = 0;
  result = AVIFileOpenA(&avi_file,filename,0,0);
  if (result == 0) {
    result = AVIFileGetStream(avi_file,&avi_video_stream,0x73646976,0);
    if (result == 0) {
      value = 0;
      if (*(int *)(player + 0x5a8) != 0) {
        result = AVIFileGetStream(avi_file,&avi_audio_stream,0x73647561,0);
        if (result == 0) {
          *(i32 *)(player + 0x5b0) = 0;
          attach_result = avi_audio_attach_stream((AviAudioAttachView *)(player + 0x11c),avi_audio_stream);
          value = result;
          if (attach_result == 0) {
            *(i32 *)(player + 0x5a8) = 1;
          }
          else {
            *(i32 *)(player + 0x5a8) = 0;
          }
        }
        else {
          *(i32 *)(player + 0x5a8) = 0;
          value = result;
        }
      }
      result = value;
      format_size = 0x28;
      AVIStreamReadFormat(avi_video_stream,1,player + 0x5c0,&format_size);
      AVIStreamInfoA(avi_video_stream,stream_info,0x8c);
      *(SIZE_T *)(player + 0x5d4) = suggested_buffer_size;
      avi_frames_per_second_i32 = time_rate / time_scale;
      avi_decompressor = ICLocate(0x63646976,codec_handler,player + 0x5c0,0,2);
      if (avi_decompressor == 0) {
        avi_close(player);
        result = 0;
      }
      else {
        start_frame = AVIStreamStart(avi_video_stream);
        *(i32 *)(player + 0xa10) = start_frame;
        value = AVIStreamLength(avi_video_stream);
        *(int *)(player + 0xa14) = *(int *)(player + 0xa10) + value - 1;
        *(i32 *)(player + 0xa18) = *(i32 *)(player + 0xa10);
        crt_memcpy(player + 0x5e8,player + 0x5c0,0x28);
        *(i32 *)(player + 0x5f8) = 0;
        *(i16 *)(player + 0x5f6) = 8;
        *(i32 *)(player + 0x5fc) = 0;
        *(i32 *)(player + 0x608) = 0x100;
        avi_frame_width = *(int *)(player + 0x5c4);
        avi_frame_height = *(int *)(player + 0x5c8);
        dib = surface_get_dib((DibSurface *)player);
        value = dib_is_top_down(dib);
        if (value != 0) {
          *(int *)(player + 0x5f0) = -*(int *)(player + 0x5f0);
        }
        if (*(int *)(player + 0x5a0) == 0) {
          wnd_resize_clamped((WindowObjectView *)player,avi_frame_width,avi_frame_height);
        }
        else {
          wnd_resize_clamped((WindowObjectView *)player,avi_frame_width * 2,avi_frame_height * 2);
        }
        if (suggested_buffer_size == 0) {
          value = (uint)*(ushort *)(player + 0x5ce) * *(int *)(player + 0x5c4) *
                  *(int *)(player + 0x5c8);
          mem_handle = GlobalAlloc(0x40,(int)(value + (value >> 0x1f & 7U)) >> 3);
          avi_frame_buffer = GlobalLock(mem_handle);
        }
        else {
          mem_handle = GlobalAlloc(0x40,suggested_buffer_size);
          avi_frame_buffer = GlobalLock(mem_handle);
        }
        if (avi_frame_buffer == (LPVOID)0x0) {
          avi_close(player);
          result = 0;
        }
        else {
          result = avi_ic_decompress_ex_query(avi_decompressor,0,player + 0x5c0,0,0,0,
                                 *(i32 *)(player + 0x5c4),*(i32 *)(player + 0x5c8),
                                 player + 0x5e8,0,0,0,*(i32 *)(player + 0x5c4),
                                 *(i32 *)(player + 0x5c8));
          if (result == 0) {
            ICSendMessage(avi_decompressor,0x401e,player + 0x5c0,player + 0x5e8);
            for (i = 0; i < 0xec; i++) {
              palette_rgb[i * 3] = *(i8 *)(player + 0x63a + i * 4);
              palette_rgb[i * 3 + 1] = *(i8 *)(player + 0x639 + i * 4);
              palette_rgb[i * 3 + 2] = *(i8 *)(player + 0x638 + i * 4);
            }
            palette_set_rgb
                      ((GamePalette *)(player + 0x124),10,0xec,(iptr)palette_rgb);
            ICSendMessage(avi_decompressor,0x401d,player + 0x5e8,0);
            result = avi_ic_decompress_ex_begin(avi_decompressor,0,player + 0x5c0,0,0,0,
                                   *(i32 *)(player + 0x5c4),*(i32 *)(player + 0x5c8)
                                   ,player + 0x5e8,0,0,0,*(i32 *)(player + 0x5c4),
                                   *(i32 *)(player + 0x5c8));
            if (result == 0) {
              avi_file_loaded = 1;
              avi_playing = 0;
              if (*(int *)(player + 0x5a4) == 0) {
                avi_restart_decompress(player,0);
              }
              else {
                avi_restart_decompress(player,1);
              }
              value = (uint)*(ushort *)(player + 0x5ce) * *(int *)(player + 0x5c4) *
                      *(int *)(player + 0x5c8);
              avi_frame_buffer_size = (int)(value + (value >> 0x1f & 7U)) >> 3;
              avi_update_tick_count_i32 = 0;
              avi_indeo_frame_extra_i32 = 0;
              result = 0;
            }
            else {
              avi_close(player);
            }
          }
          else {
            avi_close(player);
          }
        }
      }
    }
    else {
      avi_close(player);
    }
  }
  else {
    avi_close(player);
  }
  return result;
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
#undef avi_update_tick_count_i32
#undef avi_indeo_frame_opts_i32
#undef avi_indeo_frame_fourcc_i32
#undef avi_indeo_frame_version_i32
#undef avi_indeo_frame_type_i32
#undef avi_indeo_frame_environment_i32
#undef avi_indeo_frame_flags_i32
#undef avi_indeo_view_rect_ptr_i32
#undef avi_indeo_seq_opts_i32
#undef avi_indeo_seq_fourcc_i32
#undef avi_indeo_seq_version_i32
#undef avi_indeo_seq_type_i32
#undef avi_indeo_seq_environment_i32
#undef avi_indeo_seq_flags_i32
#undef avi_indeo_seq_extra_i32
#undef avi_view_rect_width_i32
#undef avi_view_rect_height_i32
#undef avi_frames_per_second_i32
#undef avi_indeo_frame_extra_i32
#undef palette_rgb
#undef stream_info
#undef codec_handler
#undef time_scale
#undef time_rate
#undef suggested_buffer_size
#undef i
#undef format_size
#undef result

/* 005e22ed: written by hand in src/game/fixups.c */

/* 005e250c auto */
#define ex_flags (*(i32 *)(frame_ + FRAME_OFF(0)))
#define ex_bi_src (*(iptr *)(frame_ + FRAME_OFF(4)))
#define ex_src_bits (*(i32 *)(frame_ + FRAME_OFF(8)))
#define ex_bi_dst (*(iptr *)(frame_ + FRAME_OFF(12)))
#define ex_dst_bits (*(i32 *)(frame_ + FRAME_OFF(16)))
#define ex_x_dst (*(i32 *)(frame_ + FRAME_OFF(20)))
#define ex_y_dst (*(i32 *)(frame_ + FRAME_OFF(24)))
#define ex_width_dst (*(i32 *)(frame_ + FRAME_OFF(28)))
#define ex_height_dst (*(i32 *)(frame_ + FRAME_OFF(32)))
#define ex_x_src (*(i32 *)(frame_ + FRAME_OFF(36)))
#define ex_y_src (*(i32 *)(frame_ + FRAME_OFF(40)))
#define ex_width_src (*(i32 *)(frame_ + FRAME_OFF(44)))
#define ex_height_src (*(i32 *)(frame_ + FRAME_OFF(48)))
i32
__stdcall avi_ic_decompress_ex_begin(i32 hic,i32 flags,iptr bi_src,i32 src_bits,
            i32 x_src,i32 y_src,i32 width_src,i32 height_src,iptr bi_dst
            ,i32 dst_bits,i32 x_dst,i32 y_dst,i32 width_dst,
            i32 height_dst)

{
  i32 result;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  ex_flags = flags;
  ex_bi_src = bi_src;
  ex_src_bits = src_bits;
  ex_x_src = x_src;
  ex_y_src = y_src;
  ex_width_src = width_src;
  ex_height_src = height_src;
  ex_bi_dst = bi_dst;
  ex_dst_bits = dst_bits;
  ex_x_dst = x_dst;
  ex_y_dst = y_dst;
  ex_width_dst = width_dst;
  ex_height_dst = height_dst;
  result = ICSendMessage(hic,0x403c,&ex_flags,0x34);
  return result;
}
#undef ex_flags
#undef ex_bi_src
#undef ex_src_bits
#undef ex_bi_dst
#undef ex_dst_bits
#undef ex_x_dst
#undef ex_y_dst
#undef ex_width_dst
#undef ex_height_dst
#undef ex_x_src
#undef ex_y_src
#undef ex_width_src
#undef ex_height_src

/* 005e2583 auto */
#define ex_flags (*(i32 *)(frame_ + FRAME_OFF(0)))
#define ex_bi_src (*(iptr *)(frame_ + FRAME_OFF(4)))
#define ex_src_bits (*(i32 *)(frame_ + FRAME_OFF(8)))
#define ex_bi_dst (*(iptr *)(frame_ + FRAME_OFF(12)))
#define ex_dst_bits (*(i32 *)(frame_ + FRAME_OFF(16)))
#define ex_x_dst (*(i32 *)(frame_ + FRAME_OFF(20)))
#define ex_y_dst (*(i32 *)(frame_ + FRAME_OFF(24)))
#define ex_width_dst (*(i32 *)(frame_ + FRAME_OFF(28)))
#define ex_height_dst (*(i32 *)(frame_ + FRAME_OFF(32)))
#define ex_x_src (*(i32 *)(frame_ + FRAME_OFF(36)))
#define ex_y_src (*(i32 *)(frame_ + FRAME_OFF(40)))
#define ex_width_src (*(i32 *)(frame_ + FRAME_OFF(44)))
#define ex_height_src (*(i32 *)(frame_ + FRAME_OFF(48)))
i32
__stdcall avi_ic_decompress_ex_query(i32 hic,i32 flags,iptr bi_src,i32 src_bits,
            i32 x_src,i32 y_src,i32 width_src,i32 height_src,iptr bi_dst
            ,i32 dst_bits,i32 x_dst,i32 y_dst,i32 width_dst,
            i32 height_dst)

{
  i32 result;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  ex_flags = flags;
  ex_bi_src = bi_src;
  ex_src_bits = src_bits;
  ex_x_src = x_src;
  ex_y_src = y_src;
  ex_width_src = width_src;
  ex_height_src = height_src;
  ex_bi_dst = bi_dst;
  ex_dst_bits = dst_bits;
  ex_x_dst = x_dst;
  ex_y_dst = y_dst;
  ex_width_dst = width_dst;
  ex_height_dst = height_dst;
  result = ICSendMessage(hic,0x403d,&ex_flags,0x34);
  return result;
}
#undef ex_flags
#undef ex_bi_src
#undef ex_src_bits
#undef ex_bi_dst
#undef ex_dst_bits
#undef ex_x_dst
#undef ex_y_dst
#undef ex_width_dst
#undef ex_height_dst
#undef ex_x_src
#undef ex_y_src
#undef ex_width_src
#undef ex_height_src

/* 005e2675 auto */
#define avi_file_loaded (*(int *)((u8 *)&g.d_00638dcc))
#define avi_frame_needs_blit (*(i32 *)((u8 *)&g.d_00638de8))
#define avi_idle_update_enabled (*(i32 *)((u8 *)&g.d_00637efc))
#define avi_playing (*(int *)((u8 *)&g.d_00638dd0))
void __cdecl avi_play_pause(iptr player)

{
  if ((player != 0) && (avi_file_loaded != 0)) {
    if (*(int *)(player + 0x5a8) != 0) {
      *(i32 *)(player + 0x5b0) = 0;
    }
    *(i32 *)(player + 0x5ac) = 1;
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
void __cdecl avi_close(iptr player)

{
  HGLOBAL mem_handle;
  
  if (player != 0) {
    avi_play_pause(player);
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
      mem_handle = GlobalHandle(avi_frame_buffer);
      GlobalUnlock(mem_handle);
      mem_handle = GlobalHandle(avi_frame_buffer);
      GlobalFree(mem_handle);
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
#define target_frame (*(uint *)(frame_ + FRAME_OFF(0)))
void __cdecl avi_seek_frame(iptr player,uint frame_index,int redraw)

{
  i32 key_frame;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((player != 0) && (avi_file_loaded != 0)) {
    if (avi_playing != 0) {
      avi_play_pause(player);
    }
    key_frame = AVIStreamFindSample(avi_video_stream,frame_index,0x14);
    *(i32 *)(player + 0xa18) = key_frame;
    while( true ) {
      if ((int)frame_index < 0) {
        target_frame = 0;
      }
      else {
        target_frame = frame_index;
      }
      if (target_frame <= *(uint *)(player + 0xa18)) break;
      avi_decode_frame(player,0x80000000);
    }
    avi_decode_frame(player,0);
    if (redraw != 0) {
      avi_update_frame(player);
    }
  }
  return;
}
#undef avi_file_loaded
#undef avi_playing
#undef avi_video_stream
#undef target_frame

/* 005e2997 auto */
#define avi_decompressor (*(i32 *)((u8 *)&g.d_00638db0))
#define avi_file_loaded (*(int *)((u8 *)&g.d_00638dcc))
#define avi_frame_buffer (*(i32 *)((u8 *)&g.d_00638da8))
#define avi_frame_buffer_size (*(i32 *)((u8 *)&g.d_00638dac))
#define avi_frame_height (*(int *)((u8 *)&g.d_00638db8))
#define avi_frame_width (*(int *)((u8 *)&g.d_00638db4))
#define avi_playing (*(int *)((u8 *)&g.d_00638dd0))
#define avi_video_stream (*(i32 *)((u8 *)&g.d_00638dc4))
#define message (*(CHAR (*)[80])(frame_ + FRAME_OFF(4)))
#define bytes_read (*(i32 *)(frame_ + FRAME_OFF(84)))
#define result (*(int *)(frame_ + FRAME_OFF(88)))
int __cdecl avi_decode_frame(iptr player,int decode_flags)

{
  i32 dst_bits;
  i32 x_dst;
  i32 y_dst;
  int dst_dim_a;
  int dst_dim_b;
  i8 frame_[FRAME_OFF(96)] __attribute__((aligned(8)));  /* original stack frame */
  
  result = 0;
  bytes_read = 0;
  if ((player == 0) || (avi_file_loaded == 0)) {
    result = 1;
  }
  else {
    if ((*(int *)(player + 0x5a4) != 0) && (decode_flags == 0)) {
      surface_blit((DibSurface *)(player + 0x558),player,ADDR(0x638dd8, ((u8 *)&g.d_00638dd8)),ADDR(0x638dd8, ((u8 *)&g.d_00638dd8)));
    }
    result = AVIStreamRead(avi_video_stream,*(i32 *)(player + 0xa18),1,avi_frame_buffer,
                            avi_frame_buffer_size,&bytes_read,0);
    if (result == 0) {
      *(i32 *)(player + 0x5d4) = bytes_read;
      if (*(int *)(player + 0x5a0) == 0) {
        y_dst = 0;
        x_dst = 0;
        dst_dim_b = avi_frame_width;
        dst_dim_a = avi_frame_height;
        dst_bits = surface_get_bits((DibSurface *)player);
        result = avi_ic_decompress_ex(avi_decompressor,decode_flags,player + 0x5c0,avi_frame_buffer,0,0,avi_frame_width,
                               avi_frame_height,player + 0x5e8,dst_bits,x_dst,y_dst,dst_dim_b,dst_dim_a);
      }
      else {
        *(int *)(player + 0x5f0) = *(int *)(player + 0x5f0) << 1;
        *(int *)(player + 0x5ec) = *(int *)(player + 0x5ec) << 1;
        dst_dim_b = avi_frame_height * 2;
        dst_dim_a = avi_frame_width * 2;
        y_dst = 0;
        x_dst = 0;
        dst_bits = surface_get_bits((DibSurface *)player);
        result = avi_ic_decompress_ex(avi_decompressor,decode_flags,player + 0x5c0,avi_frame_buffer,0,0,avi_frame_width,
                               avi_frame_height,player + 0x5e8,dst_bits,x_dst,y_dst,dst_dim_a,dst_dim_b);
        *(int *)(player + 0x5f0) = *(int *)(player + 0x5f0) >> 1;
        *(int *)(player + 0x5ec) = *(int *)(player + 0x5ec) >> 1;
      }
      if ((result != 0) && (result != 1)) {
        wsprintfA(message,s_ICDecompressEx_returned__ld_00638df0,result);
        MessageBoxA((HWND)0x0,message,s_Get_Frame_00638e0c,0);
      }
      if ((*(int *)(player + 0xa20) != 0) &&
         (*(int *)(player + 0xa20) == *(int *)(player + 0xa18))) {
        *(i32 *)(player + 0xa20) = 0;
        avi_player_call_cue_callback((AviPlayerCueCbCallView *)player);
      }
      if ((*(uint *)(player + 0xa14) < *(uint *)(player + 0xa18)) && (avi_playing != 0)) {
        if (*(int *)(player + 0xa24) == 0) {
          avi_play_pause(player);
          avi_player_call_end_callback((AviPlayerEndCbCallView *)player);
          result = 0;
        }
        else {
          avi_seek_frame(player,*(i32 *)(player + 0xa10),0);
          avi_play_start(player);
          result = 0;
        }
      }
      else {
        *(int *)(player + 0xa18) = *(int *)(player + 0xa18) + 1;
        if (decode_flags != 0) {
          result = 1;
        }
      }
    }
  }
  return result;
}
#undef avi_decompressor
#undef avi_file_loaded
#undef avi_frame_buffer
#undef avi_frame_buffer_size
#undef avi_frame_height
#undef avi_frame_width
#undef avi_playing
#undef avi_video_stream
#undef message
#undef bytes_read
#undef result

/* 005e2c5a auto */
#define ex_flags (*(i32 *)(frame_ + FRAME_OFF(0)))
#define ex_bi_src (*(iptr *)(frame_ + FRAME_OFF(4)))
#define ex_src_bits (*(i32 *)(frame_ + FRAME_OFF(8)))
#define ex_bi_dst (*(iptr *)(frame_ + FRAME_OFF(12)))
#define ex_dst_bits (*(i32 *)(frame_ + FRAME_OFF(16)))
#define ex_x_dst (*(i32 *)(frame_ + FRAME_OFF(20)))
#define ex_y_dst (*(i32 *)(frame_ + FRAME_OFF(24)))
#define ex_width_dst (*(i32 *)(frame_ + FRAME_OFF(28)))
#define ex_height_dst (*(i32 *)(frame_ + FRAME_OFF(32)))
#define ex_x_src (*(i32 *)(frame_ + FRAME_OFF(36)))
#define ex_y_src (*(i32 *)(frame_ + FRAME_OFF(40)))
#define ex_width_src (*(i32 *)(frame_ + FRAME_OFF(44)))
#define ex_height_src (*(i32 *)(frame_ + FRAME_OFF(48)))
i32
__stdcall avi_ic_decompress_ex(i32 hic,i32 flags,iptr bi_src,i32 src_bits,
            i32 x_src,i32 y_src,i32 width_src,i32 height_src,iptr bi_dst
            ,i32 dst_bits,i32 x_dst,i32 y_dst,i32 width_dst,
            i32 height_dst)

{
  i32 result;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  ex_flags = flags;
  ex_bi_src = bi_src;
  ex_src_bits = src_bits;
  ex_x_src = x_src;
  ex_y_src = y_src;
  ex_width_src = width_src;
  ex_height_src = height_src;
  ex_bi_dst = bi_dst;
  ex_dst_bits = dst_bits;
  ex_x_dst = x_dst;
  ex_y_dst = y_dst;
  ex_width_dst = width_dst;
  ex_height_dst = height_dst;
  result = ICSendMessage(hic,0x403e,&ex_flags,0x34);
  return result;
}
#undef ex_flags
#undef ex_bi_src
#undef ex_src_bits
#undef ex_bi_dst
#undef ex_dst_bits
#undef ex_x_dst
#undef ex_y_dst
#undef ex_width_dst
#undef ex_height_dst
#undef ex_x_src
#undef ex_y_src
#undef ex_width_src
#undef ex_height_src

/* 005e2cd1 auto */
#define avi_file_loaded (*(int *)((u8 *)&g.d_00638dcc))
#define avi_frame_needs_blit (*(uint *)((u8 *)&g.d_00638de8))
#define avi_playing (*(int *)((u8 *)&g.d_00638dd0))
#define avi_video_stream (*(i32 *)((u8 *)&g.d_00638dc4))
#define avi_view_rect_x (*(int *)((u8 *)&g.d_006e50c8))
#define avi_view_rect_y (*(int *)((u8 *)&g.d_006e50cc))
#define avi_play_start_time_i32 (*(i32 *)((u8 *)&g.d_00638dbc))
#define avi_update_tick_count_i32 (*(i32 *)((u8 *)&g.d_00638dec))
#define avi_view_rect_width_i32 (*(i32 *)((u8 *)&g.d_006e50d0))
#define avi_view_rect_height_i32 (*(i32 *)((u8 *)&g.d_006e50d4))
#define target_frame (*(uint *)(frame_ + FRAME_OFF(0)))
#define dirty_rect (*(RECT *)(frame_ + FRAME_OFF(4)))
#define key_frame (*(int *)(frame_ + FRAME_OFF(20)))
#define now (*(DWORD *)(frame_ + FRAME_OFF(24)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl avi_update_frame(iptr player)

{
  int sample;
  i32 audio_pos_ms;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (player == 0) {
    return;
  }
  if (avi_file_loaded == 0) {
    return;
  }
  if (avi_playing != 0) {
    if (*(int *)(player + 0x5a8) == 0) {
      now = timeGetTime();
      sample = AVIStreamTimeToSample(avi_video_stream,now - avi_play_start_time_i32);
      target_frame = *(int *)(player + 0xa10) + sample;
      if (target_frame < *(uint *)(player + 0xa18)) {
        return;
      }
      if (*(uint *)(player + 0xa14) < target_frame) {
        if (*(int *)(player + 0xa24) == 0) {
          avi_play_pause(player);
          avi_player_call_end_callback((AviPlayerEndCbCallView *)player);
          return;
        }
        avi_seek_frame(player,*(i32 *)(player + 0xa10),0);
        avi_play_start(player);
        return;
      }
    }
    else {
      sample = avi_audio_is_playing((AviAudioPlayingView *)(player + 0x11c));
      if (sample == 0) {
        if (*(int *)(player + 0xa24) == 0) {
          avi_play_pause(player);
          avi_player_call_end_callback((AviPlayerEndCbCallView *)player);
          return;
        }
        avi_seek_frame(player,*(i32 *)(player + 0xa10),0);
        avi_play_start(player);
        return;
      }
      audio_pos_ms = avi_audio_get_position_ms((void *)(player + 0x11c));
      sample = AVIStreamTimeToSample(avi_video_stream,audio_pos_ms);
      target_frame = *(int *)(player + 0xa10) + sample;
      if ((*(int *)(player + 0x5ac) == 0) || (target_frame < *(uint *)(player + 0xa18))) {
        snd_avi_stream_feed(0x40);
        avi_update_tick_count_i32++;
        return;
      }
    }
    if (avi_frame_needs_blit != 0) {
      if (*(int *)(player + 0x5a4) == 0) {
        wnd_blit_surface((DibSurface *)player);
      }
      else {
        dirty_rect.left = avi_view_rect_x;
        dirty_rect.top = avi_view_rect_y;
        dirty_rect.right = avi_view_rect_x + avi_view_rect_width_i32;
        dirty_rect.bottom = avi_view_rect_y + avi_view_rect_height_i32;
        UnionRect(&dirty_rect,&dirty_rect,(RECT *)&avi_blit_union_left);
        wnd_blit_surface_rect((DibSurface *)player,(iptr)&dirty_rect);
        avi_blit_union_left = dirty_rect.left;
        avi_blit_union_top = dirty_rect.top;
        avi_blit_union_right = dirty_rect.right;
        avi_blit_union_bottom = dirty_rect.bottom;
      }
    }
    if (*(uint *)(player + 0xa18) < target_frame) {
      key_frame = *(int *)(player + 0xa18);
      do {
        sample = key_frame;
        key_frame++;
        key_frame = AVIStreamFindSample(avi_video_stream,key_frame,0x11);
        if ((int)target_frame <= key_frame) break;
      } while (key_frame != -1);
      if (*(int *)(player + 0xa18) == sample) {
        if ((key_frame != -1) && (key_frame - target_frame < target_frame - *(int *)(player + 0xa18))) {
          *(int *)(player + 0xa18) = key_frame;
        }
      }
      else if ((key_frame == -1) || ((int)(target_frame - sample) <= (int)(key_frame - target_frame))) {
        if (sample != -1) {
          *(int *)(player + 0xa18) = sample;
        }
      }
      else {
        *(int *)(player + 0xa18) = key_frame;
      }
      while ((*(uint *)(player + 0xa18) < target_frame &&
             (*(uint *)(player + 0xa18) < *(int *)(player + 0xa14) - 1U))) {
        avi_decode_frame(player,0x80000000);
      }
    }
  }
  if ((avi_playing != 0) && (*(int *)(player + 0x5a8) != 0)) {
    snd_avi_stream_feed(0x40);
    avi_update_tick_count_i32++;
  }
  sample = avi_decode_frame(player,0);
  avi_frame_needs_blit = (uint)(sample == 0);
  return;
}
#undef avi_file_loaded
#undef avi_frame_needs_blit
#undef avi_playing
#undef avi_video_stream
#undef avi_view_rect_x
#undef avi_view_rect_y
#undef avi_play_start_time_i32
#undef avi_update_tick_count_i32
#undef avi_view_rect_width_i32
#undef avi_view_rect_height_i32
#undef target_frame
#undef dirty_rect
#undef key_frame
#undef now

/* 005e30a1 auto */
#define avi_decompressor (*(i32 *)((u8 *)&g.d_00638db0))
#define avi_file_loaded (*(int *)((u8 *)&g.d_00638dcc))
#define palette_rgb (*(i8 (*)[708])(frame_ + FRAME_OFF(0)))
#define i (*(int *)(frame_ + FRAME_OFF(708)))
#define result (*(int *)(frame_ + FRAME_OFF(712)))
void __cdecl avi_apply_palette(iptr player,GamePalette *palette)

{
  i8 frame_[FRAME_OFF(720)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((player != 0) && (avi_file_loaded != 0)) {
    ICSendMessage(avi_decompressor,0x403f,0,0);
    palette_get_rgb(palette,(iptr)palette_rgb,0,0xec);
    for (i = 0; i < 0xec; i++) {
      *(i8 *)(player + 0x610 + i * 4) = palette_rgb[i * 3 + 2];
      *(i8 *)(player + 0x611 + i * 4) = palette_rgb[i * 3 + 1];
      *(i8 *)(player + 0x612 + i * 4) = palette_rgb[i * 3];
      *(i8 *)(player + 0x613 + i * 4) = 0;
    }
    ICSendMessage(avi_decompressor,0x401d,player + 0x5e8,0);
    if (*(int *)(player + 0x5a0) == 0) {
      result = avi_ic_decompress_ex_begin(avi_decompressor,0,player + 0x5c0,0,0,0,*(i32 *)(player + 0x5c4),
                             *(i32 *)(player + 0x5c8),player + 0x5e8,0,0,0,
                             *(i32 *)(player + 0x5c4),*(i32 *)(player + 0x5c8));
    }
    else {
      *(int *)(player + 0x5f0) = *(int *)(player + 0x5f0) << 1;
      *(int *)(player + 0x5ec) = *(int *)(player + 0x5ec) << 1;
      result = avi_ic_decompress_ex_begin(avi_decompressor,0,player + 0x5c0,0,0,0,*(i32 *)(player + 0x5c4),
                             *(i32 *)(player + 0x5c8),player + 0x5e8,0,0,0,
                             *(int *)(player + 0x5c4) * 2,*(int *)(player + 0x5c8) * 2);
      *(int *)(player + 0x5f0) = *(int *)(player + 0x5f0) / 2;
      *(int *)(player + 0x5ec) = *(int *)(player + 0x5ec) / 2;
    }
    if (result != 0) {
      avi_file_loaded = 0;
    }
  }
  return;
}
#undef avi_decompressor
#undef avi_file_loaded
#undef palette_rgb
#undef i
#undef result

/* 005e32b2 auto */
#define avi_decompressor (*(i32 *)((u8 *)&g.d_00638db0))
#define avi_file_loaded (*(int *)((u8 *)&g.d_00638dcc))
#define avi_frame_height (*(int *)((u8 *)&g.d_00638db8))
#define avi_frame_width (*(int *)((u8 *)&g.d_00638db4))
#define avi_indeo_frame_flags_i32 (*(i32 *)((u8 *)&g.d_006e503c))
#define avi_indeo_seq_flags_i32 (*(i32 *)((u8 *)&g.d_006e50ac))
#define dst_rect (*(tagRECT *)(frame_ + FRAME_OFF(4)))
#define src_rect (*(tagRECT *)(frame_ + FRAME_OFF(20)))
#define cur_frame (*(i32 *)(frame_ + FRAME_OFF(36)))
#define result (*(int *)(frame_ + FRAME_OFF(40)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl avi_restart_decompress(iptr player,int transparent)

{
  int yBottom;
  int xRight;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((player != 0) && (avi_file_loaded != 0)) {
    ICSendMessage(avi_decompressor,0x403f,0,0);
    if (transparent == 0) {
      avi_indeo_seq_flags_i32 = 0;
    }
    else {
      avi_indeo_seq_flags_i32 = 0x80000004;
    }
    avi_indeo_frame_flags_i32 = 0x80000008;
    ICSendMessage(avi_decompressor,0x5001,&avi_indeo_seq_opts,0x2c);
    ICSendMessage(avi_decompressor,0x5001,&avi_indeo_frame_opts,0x70);
    if (*(int *)(player + 0x5a0) == 0) {
      result = avi_ic_decompress_ex_begin(avi_decompressor,0,player + 0x5c0,0,0,0,avi_frame_width,avi_frame_height,
                             player + 0x5e8,0,0,0,avi_frame_width,avi_frame_height);
    }
    else {
      *(int *)(player + 0x5f0) = *(int *)(player + 0x5f0) << 1;
      *(int *)(player + 0x5ec) = *(int *)(player + 0x5ec) << 1;
      result = avi_ic_decompress_ex_begin(avi_decompressor,0,player + 0x5c0,0,0,0,avi_frame_width,avi_frame_height,
                             player + 0x5e8,0,0,0,avi_frame_width * 2,avi_frame_height * 2);
      *(int *)(player + 0x5f0) = *(int *)(player + 0x5f0) >> 1;
      *(int *)(player + 0x5ec) = *(int *)(player + 0x5ec) >> 1;
    }
    if (result != 0) {
      avi_file_loaded = 0;
    }
    if (transparent == 0) {
      surface_create((DibSurface *)(player + 0x558),0,0);
    }
    else {
      surface_create((DibSurface *)(player + 0x558),avi_frame_width,avi_frame_height);
      yBottom = surface_get_height((DibSurface *)player);
      xRight = surface_get_width((DibSurface *)player);
      SetRect(&src_rect,0,0,xRight,yBottom);
      dst_rect.left = src_rect.left;
      dst_rect.top = src_rect.top;
      dst_rect.right = src_rect.right;
      dst_rect.bottom = src_rect.bottom;
      OffsetRect(&dst_rect,*(int *)(player + 0x5b8),*(int *)(player + 0x5bc));
      if (*(int *)(player + 0x5b4) != 0) {
        surface_blit
                  (*(DibSurface **)(player + 0x5b4),player + 0x558,(iptr)&dst_rect,
                   (iptr)&src_rect);
      }
      if (avi_file_loaded != 0) {
        surface_blit
                  ((DibSurface *)(player + 0x558),player,(iptr)&src_rect,(iptr)&src_rect);
        cur_frame = *(i32 *)(player + 0xa18);
        avi_seek_frame(player,cur_frame,0);
        wnd_blit_surface((DibSurface *)player);
      }
    }
  }
  return;
}
#undef avi_decompressor
#undef avi_file_loaded
#undef avi_frame_height
#undef avi_frame_width
#undef avi_indeo_frame_flags_i32
#undef avi_indeo_seq_flags_i32
#undef dst_rect
#undef src_rect
#undef cur_frame
#undef result

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
#define generic_parms (*(i8 (*)[4])(frame_ + FRAME_OFF(4)))
#define frame_height (*(int *)(frame_ + FRAME_OFF(8)))
#define minmax_info (*(uptr *)(frame_ + FRAME_OFF(12)))
#define frame_width (*(int *)(frame_ + FRAME_OFF(16)))
#define parent_window (*(iptr *)(frame_ + FRAME_OFF(20)))
#define min_height2 (*(int *)(frame_ + FRAME_OFF(24)))
#define min_width2 (*(int *)(frame_ + FRAME_OFF(28)))
#define scroll_pos2 (*(int *)(frame_ + FRAME_OFF(32)))
#define wnd2 (*(WndOnMciDoneView * *)(frame_ + FRAME_OFF(36)))
#define mci_device2 (*(iptr *)(frame_ + FRAME_OFF(40)))
#define max_height2 (*(int *)(frame_ + FRAME_OFF(44)))
#define max_width2 (*(int *)(frame_ + FRAME_OFF(48)))
i32 __stdcall moviewnd_wndproc(HWND hwnd,uint msg,uint wparam,uint lparam)

{
  short thumb_pos;
  i32 result;
  iptr window;
  WndBase *pCVar4;
  BOOL BVar5;
  int value;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  wnd2 = (WndOnMciDoneView *)GetWindowLongA(hwnd,4);
  if (wnd2 == (WndOnMciDoneView *)0x0) {
    result = wnd_base_wndproc(hwnd,msg,wparam,lparam);
    return result;
  }
  if (msg < 0x11) {
    if (msg != 0x10) {
      switch(msg) {
      case 3:
        wnd_active_child = wnd2;
        wnd_call_move
                  ((WndOnMoveView *)(wnd2->handlers),lparam & 0xffff,lparam >> 0x10);
        result = wnd_base_wndproc(hwnd,msg,wparam,lparam);
        return result;
      default:
        goto switchD_005ecda6_caseD_4;
      case 5:
switchD_005ecda6_caseD_5:
        wnd_active_child = wnd2;
        BVar5 = IsIconic(hwnd);
        if (BVar5 == 0) {
          wnd_on_size_nop(wnd2,lparam & 0xffff,lparam >> 0x10);
          wnd_call_size((WndOnSizeView *)(wnd2->handlers),wparam);
        }
        result = wnd_base_wndproc(hwnd,msg,wparam,lparam);
        return result;
      case 6:
        goto switchD_005ecda6_caseD_6;
      case 7:
        wnd_active_child = wnd2;
        wnd_call_setfocus((WndOnSetFocusView *)(wnd2->handlers));
        return 0;
      }
    }
    wnd_active_child = wnd2;
    value = wnd_call_close((WndOnCloseView *)(wnd2->handlers));
    if (value != 0) {
      result = wnd_base_wndproc(hwnd,0x10,wparam,lparam);
      return result;
    }
  }
  else {
    if (msg < 0x45) {
      if (msg == 0x44) {
        wnd_active_child = wnd2;
        wnd_call_msg44((WndOnMsg44View *)(wnd2->handlers),lparam & 0xffff);
        return 1;
      }
      if (msg == 0x24) {
        minmax_info = lparam;
        window = wnd_get_window((WndBase *)wnd2);
        frame_height = wnd_obj_frame_height(window);
        window = wnd_get_window((WndBase *)wnd2);
        frame_width = wnd_obj_frame_width(window);
        wnd_get_min_size((WndMinSizeView *)wnd2,(iptr)&min_width2,(iptr)&min_height2);
        wnd_get_max_size((WndMaxSizeView *)wnd2,(iptr)&max_width2,(iptr)&max_height2);
        *(int *)(minmax_info + 0x20) = frame_width + max_width2;
        *(int *)(minmax_info + 0x24) = frame_height + max_height2;
        *(int *)(minmax_info + 0x18) = frame_width + min_width2;
        *(int *)(minmax_info + 0x1c) = frame_height + min_height2;
        return 0;
      }
switchD_005ecda6_caseD_4:
      result = wnd_base_wndproc(hwnd,msg,wparam,lparam);
      return result;
    }
    if (msg < 0x112) {
      if (msg == 0x111) {
        wnd_active_child = wnd2;
        return 0;
      }
      if (msg == 0x100) {
        wnd_active_child = wnd2;
        result = input_map_vkey(wparam);
        wnd_call_keydown_pre((WndOnKeyDownPreView *)(wnd2->handlers),result);
        result = input_map_vkey(wparam);
        wnd_call_keydown((WndOnKeyDownView *)(wnd2->handlers),result);
        return 0;
      }
      if (msg == 0x101) {
        wnd_active_child = wnd2;
        result = input_map_vkey(wparam);
        wnd_call_keyup((WndOnKeyUpView *)(wnd2->handlers),result);
        return 0;
      }
      if (msg == 0x102) {
        wnd_active_child = wnd2;
        wnd_call_char((WndOnCharView *)(wnd2->handlers),wparam & 0xff);
        return 0;
      }
      goto switchD_005ecda6_caseD_4;
    }
    if (msg < 0x201) {
      if (msg == 0x200) {
        wnd_active_child = wnd2;
        wnd_call_mousemove
                  ((WndOnMouseMoveView *)(wnd2->handlers),lparam & 0xffff,lparam >> 0x10);
        return 0;
      }
      if (msg == 0x112) {
        if (wparam == 0xf020) {
          wnd_active_child = wnd2;
          wnd_call_minimize((WndOnMinimizeView *)(wnd2->handlers));
        }
        else {
          wnd_active_child = wnd2;
          if (wparam == 0xf120) {
            wnd_call_restore((WndOnRestoreView *)(wnd2->handlers));
          }
        }
        result = wnd_base_wndproc(hwnd,0x112,wparam,lparam);
        return result;
      }
      thumb_pos = (short)(wparam >> 0x10);
      if (msg == 0x114) {
        scroll_pos2 = wnd_get_hscroll_pos((WndHScrollPosView *)wnd2);
        switch(wparam) {
        case 0:
          scroll_pos2--;
          SetScrollPos(hwnd,0,scroll_pos2,1);
          scroll_pos2 = GetScrollPos(hwnd,0);
          wnd_active_child = wnd2;
          *(int *)(wnd2->hscroll_pos) = scroll_pos2;
          wnd_call_hscroll((WndOnHScrollView *)(wnd2->handlers),scroll_pos2);
          return 0;
        case 1:
          scroll_pos2++;
          SetScrollPos(hwnd,0,scroll_pos2,1);
          scroll_pos2 = GetScrollPos(hwnd,0);
          wnd_active_child = wnd2;
          *(int *)(wnd2->hscroll_pos) = scroll_pos2;
          wnd_call_hscroll((WndOnHScrollView *)(wnd2->handlers),scroll_pos2);
          return 0;
        case 2:
          value = wnd_get_hscroll_page((WndHScrollPageView *)wnd2);
          scroll_pos2 -= value;
          SetScrollPos(hwnd,0,scroll_pos2,1);
          scroll_pos2 = GetScrollPos(hwnd,0);
          wnd_active_child = wnd2;
          *(int *)(wnd2->hscroll_pos) = scroll_pos2;
          wnd_call_hscroll((WndOnHScrollView *)(wnd2->handlers),scroll_pos2);
          return 0;
        case 3:
          value = wnd_get_hscroll_page((WndHScrollPageView *)wnd2);
          scroll_pos2 += value;
          SetScrollPos(hwnd,0,scroll_pos2,1);
          scroll_pos2 = GetScrollPos(hwnd,0);
          wnd_active_child = wnd2;
          *(int *)(wnd2->hscroll_pos) = scroll_pos2;
          wnd_call_hscroll((WndOnHScrollView *)(wnd2->handlers),scroll_pos2);
          return 0;
        case 4:
          scroll_pos2 = (int)thumb_pos;
          SetScrollPos(hwnd,0,scroll_pos2,1);
          wnd_active_child = wnd2;
          *(int *)(wnd2->hscroll_pos) = scroll_pos2;
          wnd_call_hscroll
                    ((WndOnHScrollView *)(wnd2->handlers),*(i32 *)(wnd2->hscroll_pos));
          return 0;
        case 5:
          wnd_active_child = wnd2;
          wnd_call_hscroll_track((WndOnHScrollTrackView *)(wnd2->handlers),(int)thumb_pos);
          return 0;
        default:
          return 0;
        }
      }
      if (msg == 0x115) {
        scroll_pos2 = wnd_get_vscroll_pos((WndVScrollPosView *)wnd2);
        switch(wparam) {
        case 0:
          scroll_pos2--;
          SetScrollPos(hwnd,1,scroll_pos2,1);
          scroll_pos2 = GetScrollPos(hwnd,1);
          wnd_active_child = wnd2;
          *(int *)(wnd2->vscroll_pos) = scroll_pos2;
          wnd_call_vscroll((WndOnVScrollView *)(wnd2->handlers),scroll_pos2);
          return 0;
        case 1:
          scroll_pos2++;
          SetScrollPos(hwnd,1,scroll_pos2,1);
          scroll_pos2 = GetScrollPos(hwnd,1);
          wnd_active_child = wnd2;
          *(int *)(wnd2->vscroll_pos) = scroll_pos2;
          wnd_call_vscroll((WndOnVScrollView *)(wnd2->handlers),scroll_pos2);
          return 0;
        case 2:
          value = wnd_get_vscroll_page((WndVScrollPageView *)wnd2);
          scroll_pos2 -= value;
          SetScrollPos(hwnd,1,scroll_pos2,1);
          scroll_pos2 = GetScrollPos(hwnd,1);
          wnd_active_child = wnd2;
          *(int *)(wnd2->vscroll_pos) = scroll_pos2;
          wnd_call_vscroll((WndOnVScrollView *)(wnd2->handlers),scroll_pos2);
          return 0;
        case 3:
          value = wnd_get_vscroll_page((WndVScrollPageView *)wnd2);
          scroll_pos2 += value;
          SetScrollPos(hwnd,1,scroll_pos2,1);
          scroll_pos2 = GetScrollPos(hwnd,1);
          wnd_active_child = wnd2;
          *(int *)(wnd2->vscroll_pos) = scroll_pos2;
          wnd_call_vscroll((WndOnVScrollView *)(wnd2->handlers),scroll_pos2);
          return 0;
        case 4:
          scroll_pos2 = (int)thumb_pos;
          SetScrollPos(hwnd,1,scroll_pos2,1);
          wnd_active_child = wnd2;
          *(int *)(wnd2->vscroll_pos) = scroll_pos2;
          wnd_call_vscroll
                    ((WndOnVScrollView *)(wnd2->handlers),*(i32 *)(wnd2->vscroll_pos));
          return 0;
        case 5:
          wnd_active_child = wnd2;
          wnd_call_vscroll_track((WndOnVScrollTrackView *)(wnd2->handlers),(int)thumb_pos);
          return 0;
        default:
          return 0;
        }
      }
      goto switchD_005ecda6_caseD_4;
    }
    if (msg < 0x211) {
      if (msg == 0x210) {
        if (wparam == 0x201) {
          wnd_active_child = wnd2;
          wnd_call_lbuttondown
                    ((WndOnLButtonDownView *)(wnd2->handlers),lparam & 0xffff,lparam >> 0x10);
          return 0;
        }
        if (wparam != 0x204) {
          return 0;
        }
        wnd_active_child = wnd2;
        wnd_call_rbuttondown
                  ((WndOnRButtonDownView *)(wnd2->handlers),lparam & 0xffff,lparam >> 0x10);
        return 0;
      }
      switch(msg) {
      case 0x201:
        pCVar4 = (WndBase *)GetWindowLongA(hwnd,0);
        parent_window = wnd_get_window(pCVar4);
        wnd_active_child = wnd2;
        if ((*(byte *)(parent_window + 0x49) & 2) != 0) {
          SetFocus(*(HWND *)(parent_window + 4));
          BringWindowToTop(hwnd);
        }
        wnd2->wnd_header_area[0xa4] = 1;
        wnd2->wnd_header_area[0xa5] = '\0';
        wnd2->wnd_header_area[0xa6] = '\0';
        wnd2->wnd_header_area[0xa7] = '\0';
        wnd_call_lbuttondown
                  ((WndOnLButtonDownView *)(wnd2->handlers),lparam & 0xffff,lparam >> 0x10);
        return 0;
      case 0x202:
        wnd_active_child = wnd2;
        if (*(int *)(wnd2->lbutton_held) == 1) {
          wnd2->wnd_header_area[0xa4] = '\0';
          wnd2->wnd_header_area[0xa5] = '\0';
          wnd2->wnd_header_area[0xa6] = '\0';
          wnd2->wnd_header_area[0xa7] = '\0';
          wnd_call_lbuttonup
                    ((WndOnLButtonUpView *)(wnd2->handlers),lparam & 0xffff,lparam >> 0x10);
        }
        wnd_call_lbuttonup_raw
                  ((WndOnLButtonUpRawView *)(wnd2->handlers),lparam & 0xffff,lparam >> 0x10);
        return 0;
      case 0x203:
        wnd_active_child = wnd2;
        wnd_call_dblclick
                  ((WndOnDblClickView *)(wnd2->handlers),lparam & 0xffff,lparam >> 0x10);
        return 0;
      case 0x204:
        pCVar4 = (WndBase *)GetWindowLongA(hwnd,0);
        parent_window = wnd_get_window(pCVar4);
        if ((*(byte *)(parent_window + 0x49) & 2) != 0) {
          SetFocus(*(HWND *)(parent_window + 4));
          BringWindowToTop(hwnd);
        }
        wnd_active_child = wnd2;
        wnd2->wnd_header_area[0xa8] = 1;
        wnd2->wnd_header_area[0xa9] = '\0';
        wnd2->wnd_header_area[0xaa] = '\0';
        wnd2->wnd_header_area[0xab] = '\0';
        wnd_call_rbuttondown
                  ((WndOnRButtonDownView *)(wnd2->handlers),lparam & 0xffff,lparam >> 0x10);
        return 0;
      case 0x205:
        wnd_active_child = wnd2;
        if (*(int *)(wnd2->rbutton_held) == 1) {
          wnd2->wnd_header_area[0xa8] = '\0';
          wnd2->wnd_header_area[0xa9] = '\0';
          wnd2->wnd_header_area[0xaa] = '\0';
          wnd2->wnd_header_area[0xab] = '\0';
          wnd_call_rbuttonup
                    ((WndOnRButtonUpView *)(wnd2->handlers),lparam & 0xffff,lparam >> 0x10);
        }
        wnd_call_rbuttonup_raw
                  ((WndOnRButtonUpRawView *)(wnd2->handlers),lparam & 0xffff,lparam >> 0x10);
        return 0;
      }
      goto switchD_005ecda6_caseD_4;
    }
    if ((msg != 0x30f) && (msg != 0x311)) {
      if (msg == 0x3b9) {
        if (wparam == 1) {
          wnd_call_mci_done(wnd2);
          return 0;
        }
        goto switchD_005ecda6_caseD_5;
      }
      goto switchD_005ecda6_caseD_4;
    }
switchD_005ecda6_caseD_6:
    mci_device2 = wnd_get_mci_device((WndMciDeviceView *)wnd2);
    if (mci_device2 == 0) {
      result = wnd_base_wndproc(hwnd,msg,wparam,lparam);
      return result;
    }
    mciSendCommandA(*(MCIDEVICEID *)(mci_device2 + 8),0x840,*(DWORD_PTR *)(mci_device2 + 0x10),
                    (DWORD_PTR)generic_parms);
  }
  return 0;
}
#undef wnd_active_child
#undef generic_parms
#undef frame_height
#undef minmax_info
#undef frame_width
#undef parent_window
#undef min_height2
#undef min_width2
#undef scroll_pos2
#undef wnd2
#undef mci_device2
#undef max_height2
#undef max_width2

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
int __thiscall avi_audio_attach_stream(AviAudioAttachView *this,u32 stream)

{
  int result;
  
  result = snd_wave_add_avi_stream(stream);
  if (result == 0) {
    this->avi_stream = stream;
    this->stream_flags = this->stream_flags | 1;
  }
  else {
    this->stream_flags = 0;
  }
  return result;
}

/* 005eedd1 auto */
i32 __thiscall avi_audio_get_position_ms(void *this)

{
  i32 position_ms;
  
  position_ms = snd_wave_get_position_ms();
  return position_ms;
}

/* 005eedec auto */
int __thiscall avi_audio_prepare_range(AviAudioPrepareView *this,i32 start_time,i32 end_time)

{
  int result;
  
  result = snd_avi_stream_prepare(start_time,end_time,(iptr)this);
  if (result == 0) {
    this->audio_flags = this->audio_flags | 2;
  }
  else {
    this->audio_flags = this->audio_flags & 0xfffd;
  }
  return result;
}

/* 005eee4f auto */
i16 __thiscall avi_audio_start(void *this)

{
  snd_avi_stream_start();
  return 0;
}
