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

void __thiscall avi_player_set_end_callback(AviPlayerEndCbSetView *self,iptr callback)

{
  *(iptr *)(((AviPlayerEndCbSetViewExt *)self)->on_end_callback) = callback;
  return;
}

/* 0046e020 auto */
void __cdecl snd_play_effect(iptr effect,iptr play_mode,int loop,iptr user_data)

{
  int result;
  char *drive;
  char wav_name[16];
  char wav_path[128];
  i8 local_path[128];
  uint snd_flags;
  
  prefs_main_menu_choice_block.snd_last_effect_id = effect;
  prefs_main_menu_choice_block.snd_last_effect_arg = play_mode;
  if (effect < 0) {
    snd_wave_free_by_id(~effect + 1);
  }
  else if ((((byte)game.game_options & 0x10) != 0) && (effect < 0x85)) {
    crt_strcpy(wav_name,((char *)&str_aircombt) + effect * 9);
    result = _strcmp(wav_name,str_cheers);
    if (result == 0) {
      result = rand_range(0,2);
      str_append_int((iptr)wav_name,result + 1);
    }
    crt_strcat(wav_name,((i8 *)&snd_wav_ext_str));
    str_clear((iptr)wav_path);
    str_append((iptr)wav_path,(iptr)&str_civ2_sound);
    str_append((iptr)wav_path,(iptr)wav_name);
    str_clear((iptr)local_path);
    str_append((iptr)local_path,(iptr)&net_map_lock_slots_block.scenario_dir_path);
    str_append((iptr)local_path,(iptr)&str_sound);
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

/* 0046e2f4 auto */
void __cdecl snd_cd_on_notify(void)

{
  cd_music_available = 1;
  if (cd_music_continue != 0) {
    snd_sync_music_option();
  }
  return;
}

/* 0046e320 auto */
void __cdecl snd_cd_play_random_track(void)

{
  int rand_offset;
  int rand_offset_alt;
  uint track;
  int track_count;
  int tries;
  
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

/* 0046e4a9 auto */
void __cdecl snd_cd_detect_layout(void)

{
  int track_count;
  
  snd_cd_set_notify_callback((iptr)snd_cd_on_notify);
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

/* 0046e571 auto */
void __cdecl music_play_track(uint track,int force)

{
  int track_count;
  int tries;
  
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
      snd_cd_set_notify_callback((iptr)snd_cd_on_notify);
      snd_cd_play_track(track);
      cd_music_current_track = track;
      cd_music_continue = 1;
      cd_music_available = 0;
    }
  }
  return;
}

/* 0046e6a9 auto */
void __cdecl snd_cd_stop(void)

{
  snd_cd_mci_stop();
  cd_music_available = 1;
  return;
}

/* 0046e6c8 auto */
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

/* 00472910 auto */
void __thiscall avi_player_set_frame_callback(AviPlayerSetFrameCallbackView *self,iptr callback,u32 callback_data)

{
  self->on_frame = callback;
  self->callback_frame = callback_data;
  return;
}

/* 00472950: written by hand in src/game/regargs.cpp */

/* 004729ab: written by hand in src/game/regargs.cpp */

/* 004d8b20 auto */
AviPlayer * __thiscall avi_player_scalar_dtor(AviPlayer *self,uint flags)

{
  avi_player_dtor(self);
  if ((flags & 1) != 0) {
    operator_delete(self);
  }
  return self;
}

/* 005d48d0 auto */
void __cdecl snd_shutdown(void)

{
  snd_wave_close_all();
  return;
}

/* 005d48f0 auto */
int __cdecl snd_wave_open(i32 notify_hwnd,i32 buffer_bytes,i32 buffer_count)

{
  int result;
  
  snd_wave_notify_hwnd = notify_hwnd;
  snd_wave_open_buffer_bytes = buffer_bytes;
  (*(i32 *)&snd_wave_max_buffers) = buffer_count;
  (*(i32 *)&snd_wave_buffer_count) = buffer_count;
  result = snd_wave_open_device(notify_hwnd,0,(iptr)&snd_wave_out_handle);
  if (result == 0) {
    snd_wave_alloc_buffers(buffer_bytes,snd_wave_out_handle,buffer_count);
    result = 0;
  }
  return result;
}

/* 005d4965 auto */
void __cdecl snd_wave_close_all(void)

{
  if (snd_wave_out_handle != 0) {
    snd_wave_reset_all(snd_wave_out_handle);
    snd_wave_close_device(snd_wave_out_handle);
  }
  return;
}

/* 005d49a3 auto */
void __cdecl snd_show_error(int error_code)

{
  if (error_code == 10) {
    MessageBoxA((HWND)0x0,str_this_sound_format_is_not_supported,str_sound_error,0x40);
  }
  else if (error_code != 0xb) {
    MessageBoxA((HWND)0x0,str_undefined_sound_error,str_sound_error_2,0x40);
  }
  return;
}

/* 005d4a11 auto */
uint __cdecl snd_wave_open_device(DWORD_PTR callback,i32 *format,iptr out_handle)

{
  bool use_fallback;
  UINT device_count;
  UINT chosen_device;
  UINT_PTR device;
  uint result;
  
  use_fallback = false;
  if (snd_wave_device_open == 0) {
    if (format != (i32 *)0x0) {
      snd_wave_format[0] = *format;
      snd_wave_samples_per_sec = format[1];
      snd_wave_avg_bytes_per_sec = format[2];
      (*(i32 *)&snd_wave_block_align) = format[3];
    }
    device_count = waveOutGetNumDevs();
    for (device = 0; (int)device < (int)device_count; device++) {
      waveOutGetDevCapsA(device,(LPWAVEOUTCAPSA)&default_draw_font_obj_block.snd_wave_dev_caps,0x34);
      if ((default_draw_font_obj_block.snd_wave_dev_formats & 0x20) != 0) {
        use_fallback = false;
        chosen_device = device;
        break;
      }
      if ((default_draw_font_obj_block.snd_wave_dev_formats & 0x10) != 0) {
        chosen_device = device;
        use_fallback = true;
      }
    }
    if ((use_fallback) || (device != device_count)) {
      if (use_fallback) {
        snd_wave_format[0] = CONCAT22(1,(i16)snd_wave_format[0]);
        snd_wave_avg_bytes_per_sec = 0x5622;
        (*(i32 *)&snd_wave_block_align) = ((*(i32 *)&snd_wave_block_align) & 0xffff0000 | (ushort)(1));
      }
      result = waveOutOpen((LPHWAVEOUT)&snd_wave_out_handle,chosen_device,(LPCWAVEFORMATEX)((i32 *)&snd_wave_format),
                            callback,0,0x10000);
      if ((short)result != 0) {
        sndPlaySoundA((LPCSTR)0x0,0);
        result = waveOutOpen((LPHWAVEOUT)&snd_wave_out_handle,chosen_device,(LPCWAVEFORMATEX)((i32 *)&snd_wave_format),
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

/* 005d4bcb auto */
uint __cdecl snd_wave_close_device(HWAVEOUT wave_out)

{
  MMRESULT close_result;
  i32 result;
  
  result = 0;
  if (snd_wave_device_open != 0) {
    close_result = waveOutClose(wave_out);
    result = close_result & 0xffff;
  }
  snd_wave_device_open = 0;
  return result;
}

/* 005d4c18 auto */
void __cdecl snd_waveout_error_box(uint error_code)

{
  CHAR error_text[200];
  
  waveOutGetErrorTextA(error_code & 0xffff,error_text,200);
  MessageBoxA((HWND)0x0,error_text,str_wave_out_error,0x40);
  return;
}

/* 005d4c5f auto */
i16 __cdecl snd_wave_load_file(LPSTR filename,i32 unused,i32 flags,FOURCC sound_id)

{
  i16 result;
  MMRESULT mmio_result;
  DWORD bytes_read;
  int n;
  _MMIOINFO *p_Var5;
  _MMCKINFO *p_Var6;
  DWORD *dst_flags;
  FOURCC *dst_ckid;
  _MMCKINFO chunk;
  _MMIOINFO mmio_info;
  iptr node2;
  DWORD fmt_size;
  FOURCC *source;
  HGLOBAL mem_handle2;
  WAVEFORMATEX wave_format;
  _MMCKINFO riff_chunk;
  HMMIO mmio;
  
  _memset(&mmio_info,0,0x48);
  mmio_info.cchBuffer = snd_wave_total_buffer_bytes;
  mmio = mmioOpenA(filename,&mmio_info,0x10000);
  if (mmio == (HMMIO)0x0) {
    result = 7;
  }
  else {
    riff_chunk.fccType = 0x45564157;
    mmio_result = mmioDescend(mmio,&riff_chunk,(MMCKINFO *)0x0,0x20);
    if (mmio_result == 0) {
      chunk.ckid = 0x20746d66;
      mmio_result = mmioDescend(mmio,&chunk,&riff_chunk,0x10);
      if (mmio_result == 0) {
        fmt_size = chunk.cksize;
        bytes_read = mmioRead(mmio,(HPSTR)&wave_format,chunk.cksize);
        if (bytes_read == fmt_size) {
          if ((wave_format.nSamplesPerSec == 0x5622) && (wave_format.wBitsPerSample == 8)) {
            mmioAscend(mmio,&chunk,0);
            chunk.ckid = 0x61746164;
            mmio_result = mmioDescend(mmio,&chunk,&riff_chunk,0x10);
            if (mmio_result == 0) {
              mmioGetInfo(mmio,&mmio_info,0);
              mmioAdvance(mmio,&mmio_info,0);
              mem_handle2 = GlobalAlloc(0x2002,0xbc);
              if (mem_handle2 == (HGLOBAL)0x0) {
                mmioClose(mmio,0);
                result = 2;
              }
              else {
                source = (FOURCC *)GlobalLock(mem_handle2);
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
                  dst_flags = source + 6;
                  for (n = 0x12; n != 0; n--) {
                    *dst_flags = p_Var5->dwFlags;
                    p_Var5 = (_MMIOINFO *)&p_Var5->fccIOProc;
                    dst_flags++;
                  }
                  p_Var6 = &chunk;
                  dst_ckid = source;
                  for (n = 5; dst_ckid = dst_ckid + 1, n != 0; n--) {
                    *dst_ckid = p_Var6->ckid;
                    p_Var6 = (_MMCKINFO *)&p_Var6->cksize;
                  }
                  *(i16 *)((int)source + 0x8a) = (i16)flags;
                  source[0x1d] = wave_format.wFormatTag | (u32)wave_format.nChannels << 16;
                  source[0x1e] = wave_format.nSamplesPerSec;
                  source[0x1f] = wave_format.nAvgBytesPerSec;
                  source[0x20] = wave_format.nBlockAlign | (u32)wave_format.wBitsPerSample << 16;
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

/* 005d4f6a auto */
i16 __cdecl snd_wave_open_stream(LPSTR filename,i32 unused,i32 flags)

{
  i16 result;
  MMRESULT mmio_result;
  DWORD bytes_read;
  int n;
  _MMIOINFO *p_Var5;
  _MMCKINFO *p_Var6;
  DWORD *dst_flags;
  FOURCC *dst_ckid;
  _MMCKINFO chunk;
  _MMIOINFO mmio_info;
  iptr node2;
  DWORD fmt_size;
  FOURCC *source;
  HGLOBAL mem_handle2;
  WAVEFORMATEX wave_format;
  _MMCKINFO riff_chunk;
  HMMIO file_mmio;
  HMMIO mem_mmio;
  
  file_mmio = mmioOpenA(filename,(LPMMIOINFO)0x0,0);
  if (file_mmio == (HMMIO)0x0) {
    result = 7;
  }
  else {
    riff_chunk.fccType = 0x45564157;
    mmio_result = mmioDescend(file_mmio,&riff_chunk,(MMCKINFO *)0x0,0x20);
    if (mmio_result == 0) {
      chunk.ckid = 0x20746d66;
      mmio_result = mmioDescend(file_mmio,&chunk,&riff_chunk,0x10);
      if (mmio_result == 0) {
        fmt_size = chunk.cksize;
        bytes_read = mmioRead(file_mmio,(HPSTR)&wave_format,chunk.cksize);
        if (bytes_read == fmt_size) {
          if ((wave_format.nSamplesPerSec == 0x5622) && (wave_format.wBitsPerSample == 8)) {
            mmioAscend(file_mmio,&chunk,0);
            chunk.ckid = 0x61746164;
            mmio_result = mmioDescend(file_mmio,&chunk,&riff_chunk,0x10);
            if (mmio_result == 0) {
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
                  source = (FOURCC *)GlobalLock(mem_handle2);
                  if (source == (FOURCC *)0x0) {
                    GlobalFree(mem_handle2);
                    result = 2;
                  }
                  else {
                    _memset(source,0,0xbc);
                    source[0x1b] = (FOURCC)mem_handle2;
                    *(i16 *)(source + 0x22) = 1;
                    source[0x1d] = wave_format.wFormatTag | (u32)wave_format.nChannels << 16;
                    source[0x1e] = wave_format.nSamplesPerSec;
                    source[0x1f] = wave_format.nAvgBytesPerSec;
                    source[0x20] = wave_format.nBlockAlign | (u32)wave_format.wBitsPerSample << 16;
                    *source = (FOURCC)mem_mmio;
                    source[0x18] = (FOURCC)file_mmio;
                    p_Var5 = &mmio_info;
                    dst_flags = source + 6;
                    for (n = 0x12; n != 0; n--) {
                      *dst_flags = p_Var5->dwFlags;
                      p_Var5 = (_MMIOINFO *)&p_Var5->fccIOProc;
                      dst_flags++;
                    }
                    p_Var6 = &chunk;
                    dst_ckid = source;
                    for (n = 5; dst_ckid = dst_ckid + 1, n != 0; n--) {
                      *dst_ckid = p_Var6->ckid;
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

/* 005d52a2 auto */
i32 __cdecl snd_wave_add_avi_stream(int avi_stream)

{
  i32 result;
  int n;
  _MMIOINFO *p_Var3;
  DWORD *dst_flags;
  _MMIOINFO mmio_info;
  WAVEFORMATEX wave_format;
  i32 *source;
  HGLOBAL mem_handle2;
  i8 sample_buf[4];
  uint bytes_per_buffer;
  int total_bytes;
  i32 format_size;
  uint size_bits;
  AVISTREAMINFOA stream_info;
  HMMIO mmio;
  i32 rate_mode;
  
  format_size = 0xe;
  if (snd_wave_out_handle == 0) {
    result = 3;
  }
  else if (avi_stream == 0) {
    result = 0xc;
  }
  else if ((snd_wave_sources == 0) || (*(short *)(snd_wave_sources + 0x88) != 4)) {
    AVIStreamInfoA(avi_stream,&stream_info,0x8c);
    if (stream_info.fccType == 0x73647561) {
      AVIStreamRead(avi_stream,0,1,0,0,(LONG*)(sample_buf),0);
      total_bytes = stream_info.dwSampleSize * stream_info.dwLength;
      AVIStreamReadFormat(avi_stream,0,&wave_format,&format_size);
      if ((*(i16 *)((char *)((i8 *)&snd_wave_format) + 2)) == 1) {
        if (wave_format.nChannels == 2) {
          rate_mode = (rate_mode & 0xffff0000 | (ushort)(1));
        }
        else {
          rate_mode = (rate_mode & 0xffff0000 | (ushort)(2));
        }
      }
      else if (wave_format.nChannels == 2) {
        rate_mode = rate_mode & 0xffff0000;
      }
      else {
        rate_mode = (rate_mode & 0xffff0000 | (ushort)(3));
      }
      _memset(&mmio_info,0,0x48);
      if ((rate_mode & 0xffff) == 1) {
        mmio_info.cchBuffer = (*(uint *)&snd_wave_total_buffer_bytes) * 2;
      }
      else if ((rate_mode & 0xffff) == 3) {
        mmio_info.cchBuffer = (*(uint *)&snd_wave_total_buffer_bytes) >> 1;
      }
      else {
        mmio_info.cchBuffer = (*(uint *)&snd_wave_total_buffer_bytes);
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
          source = (i32 *)GlobalLock(mem_handle2);
          if (source == (i32 *)0x0) {
            GlobalFree(mem_handle2);
            result = 2;
          }
          else {
            _memset(source,0,0xbc);
            source[0x1b] = mem_handle2;
            *(i16 *)(source + 0x22) = 4;
            source[0x1d] = wave_format.wFormatTag | (u32)wave_format.nChannels << 16;
            source[0x1e] = wave_format.nSamplesPerSec;
            source[0x1f] = wave_format.nAvgBytesPerSec;
            source[0x20] = wave_format.nBlockAlign | (u32)wave_format.wBitsPerSample << 16;
            *source = mmio;
            p_Var3 = &mmio_info;
            dst_flags = (DWORD *)(source + 6);
            for (n = 0x12; n != 0; n--) {
              *dst_flags = p_Var3->dwFlags;
              p_Var3 = (_MMIOINFO *)&p_Var3->fccIOProc;
              dst_flags++;
            }
            source[1] = stream_info.fccType;
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

/* 005d5643: written by hand in src/game/sound_position.cpp */

/* 005d5706: written by hand in src/game/sound_position.cpp */

/* 005d57b1 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __cdecl snd_avi_stream_feed(uint sample_count)

{
  i32 result;
  uint limit;
  iptr source;
  uint byte_count;
  uint i;
  iptr buffer;
  int bytes_read;
  
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
                    (LPVOID)*(i32 *)(snd_wave_sources + 0x34),byte_count,&bytes_read,0);
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

/* 005d5b88 auto */
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

/* 005d5bec auto */
void __cdecl snd_avi_stream_refill(iptr source)

{
  uint remaining;
  int shortfall;
  uint byte_count;
  int bytes_read;
  
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
                  byte_count / *(ushort *)(source + 0x80),(LPVOID)*(i32 *)(source + 0x34),byte_count,
                  &bytes_read,0);
    *(int *)(source + 0x90) = *(int *)(source + 0x90) + bytes_read;
    shortfall = *(int *)(source + 0x2c) - bytes_read;
    if (shortfall != 0) {
      snd_fill_silence_u8(*(int *)(source + 0x34) + bytes_read,shortfall);
    }
  }
  return;
}

/* 005d5d11 auto */
i32 __cdecl snd_avi_stream_prepare(i32 start_time,i32 end_time,iptr status_ptr)

{
  i32 result;
  int start_byte;
  int byte_length;
  uint i;
  i32 *buffer;
  
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
        start_byte = snd_wave_mix_buffer((i32 *)*buffer);
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

/* 005d5f91 auto */
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

/* 005d6038 auto */
short __cdecl snd_wave_play(iptr filename,uint flags,i32 sound_id,i32 sound_tag)

{
  short result;
  int status;
  uint i;
  i32 *buffer;
  
  if (snd_wave_out_handle == 0) {
    result = 3;
  }
  else if ((snd_wave_device_open == 0) &&
          (status = snd_wave_open(snd_wave_notify_hwnd,snd_wave_open_buffer_bytes,(*(i32 *)&snd_wave_max_buffers)), status != 0)) {
    result = 0;
  }
  else if ((*(ushort *)&snd_wave_source_count) < 5) {
    if ((flags & 8) == 0) {
      result = snd_wave_load_file((LPSTR)filename,flags,sound_id,sound_tag);
    }
    else {
      result = snd_wave_open_stream((LPSTR)filename,flags,sound_id);
    }
    if ((result == 0) &&
       ((*(ushort *)&snd_wave_source_count) = (*(ushort *)&snd_wave_source_count) + 1, (*(uint *)(snd_wave_cur_buffer + 0xc) >> 5 & 1) == 0)) {
      i = 0;
      buffer = (i32 *)snd_wave_cur_buffer;
      while ((i < snd_wave_buffer_count && (status = snd_wave_mix_buffer((i32 *)*buffer), status != 1))) {
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

/* 005d61ab auto */
void __cdecl snd_wave_free_by_id(i32 sound_id)

{
  iptr source;
  iptr prev;
  
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

/* 005d6283 auto */
void __cdecl snd_wave_stream_refill(iptr source)

{
  int n;
  i32 *src;
  i32 *dst;
  MMIOINFO mmio_info;
  int done;
  int remaining;
  int leftover;
  int space;
  
  remaining = 0;
  done = 0;
  src = (i32 *)(source + 0x18);
  dst = (i32 *)&mmio_info;
  for (n = 0x12; n != 0; n--) {
    *dst = *src;
    src++;
    dst++;
  }
  if (mmio_info.pchBuffer == mmio_info.pchNext) {
    leftover = 0;
    space = mmio_info.cchBuffer;
  }
  else {
    leftover = (int)mmio_info.pchEndWrite - (int)mmio_info.pchNext;
    space = mmio_info.cchBuffer - leftover;
  }
  if (leftover == 0) {
    mmio_info.pchNext = mmio_info.pchBuffer;
  }
  else {
    crt_memmove(mmio_info.pchBuffer,mmio_info.pchNext,leftover);
    mmio_info.pchNext = mmio_info.pchBuffer + leftover;
  }
  while (done == 0) {
    remaining = *(int *)(source + 8) - *(int *)(source + 0x68);
    if (space < remaining) {
      mmioRead(*(HMMIO *)(source + 0x60),mmio_info.pchNext,space);
      *(int *)(source + 0x68) = *(int *)(source + 0x68) + space;
      *(HPSTR *)(source + 0x34) = mmio_info.pchBuffer;
      done = 1;
    }
    else {
      mmioRead(*(HMMIO *)(source + 0x60),mmio_info.pchNext,remaining);
      *(i32 *)(source + 0x68) = 0;
      mmio_info.pchNext += remaining;
      space = (int)mmio_info.pchEndWrite - (int)mmio_info.pchNext;
      mmioSeek(*(HMMIO *)(source + 0x60),*(LONG *)(source + 0x10),0);
    }
  }
  return;
}

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
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

MMRESULT __cdecl snd_wave_alloc_buffers(uint total_bytes,HWAVEOUT wave_out,uint buffer_count)

{
  int data;
  int mem_handle2;
  int *prev;
  uint i;
  MMRESULT result;
  uint bytes_per_buffer;
  int *buffer;
  
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
      data = (int)snd_global_alloc_lock(bytes_per_buffer + 0x20,(iptr)&mem_handle2);
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
    (*(uint *)&snd_wave_total_buffer_bytes) = total_bytes;
  }
  return result;
}

/* 005d6685 auto */
void __cdecl snd_wave_add_buffers(int count)

{
  iptr next_spare;
  uint i;
  iptr tail2;
  iptr buffer;
  
  buffer = snd_wave_spare_buffers;
  *(uint *)(snd_wave_spare_buffers + 0xc) = *(uint *)(snd_wave_spare_buffers + 0xc) & 0xfffffffe;
  for (i = 0; (int)i < count - 1; i++) {
    buffer = *(int *)(buffer + 0x1c);
    *(uint *)(buffer + 0xc) = *(uint *)(buffer + 0xc) & 0xfffffffe;
  }
  tail2 = snd_wave_buffer_ring;
  for (i = 0; i < (*(int *)&snd_wave_buffer_count) - 1U; i++) {
    tail2 = *(iptr *)(tail2 + 0x1c);
  }
  next_spare = *(iptr *)(buffer + 0x1c);
  *(iptr *)(tail2 + 0x1c) = snd_wave_spare_buffers;
  snd_wave_spare_buffers = next_spare;
  *(iptr *)(buffer + 0x1c) = snd_wave_buffer_ring;
  (*(int *)&snd_wave_buffer_count) += count;
  return;
}

/* 005d673a auto */
void __cdecl snd_wave_remove_buffers(int count)

{
  iptr removed;
  int i;
  iptr buffer;
  
  buffer = snd_wave_buffer_ring;
  if ((uint)((*(int *)&snd_wave_buffer_count) - count) <= (*(uint *)(snd_wave_cur_buffer + 0xc) >> 7 & 0xff)) {
    snd_wave_cur_buffer = snd_wave_buffer_ring;
  }
  for (i = 0; i < (int)(((*(int *)&snd_wave_buffer_count) - count) - 1U); i++) {
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
  (*(int *)&snd_wave_buffer_count) -= count;
  return;
}

/* 005d687b auto */
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

/* 005d6947 auto */
i32 __cdecl snd_wave_write_pending(iptr buffer)

{
  MMRESULT write_result;
  uint i;
  uint result;
  byte *sample;
  
  result = result & 0xffff0000;
  while ((*(uint *)(buffer + 0xc) >> 6 & 1) != 0) {
    sample = (byte *)**(i32 **)buffer;
    for (i = 0; i < *(uint *)(*(int *)buffer + 4); i++) {
      *sample = *sample ^ 0x80;
      sample++;
    }
    write_result = waveOutWrite((*(HWAVEOUT *)&snd_wave_out_handle),*(LPWAVEHDR *)buffer,0x20);
    result = (result & 0xffff0000 | (ushort)((short)write_result));
    if ((short)write_result == 0) {
      *(uint *)(buffer + 0xc) = *(uint *)(buffer + 0xc) | 0x20;
      *(uint *)(buffer + 0xc) = *(uint *)(buffer + 0xc) & 0xffffffbf;
    }
    else {
      if ((write_result & 0xffff) != 0x21) {
        snd_waveout_error_box(result);
      }
      *(uint *)(buffer + 0xc) = *(uint *)(buffer + 0xc) & 0xffffffdf;
    }
    buffer = *(iptr *)(buffer + 0x1c);
  }
  return 0;
}

/* 005d6a2c auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl snd_wave_stop_all(void)

{
  BOOL got_msg;
  tagMSG msg;
  iptr source;
  uint i;
  iptr prev;
  iptr buffer;
  
  prev = 0;
  snd_wave_stop_pending_i16 = 0;
  source = snd_wave_sources;
  if ((*(HWAVEOUT *)&snd_wave_out_handle) != (HWAVEOUT)0x0) {
    waveOutReset((*(HWAVEOUT *)&snd_wave_out_handle));
    while (got_msg = PeekMessageA(&msg,(*(HWND *)&snd_wave_notify_hwnd),0x3bd,0x3bd,1), got_msg != 0) {
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

/* 005d6b4c auto */
void __cdecl snd_fill_silence_u8(iptr dest,uint length)

{
  uptr i;
  
  for (i = 0; i < length; i++) {
    *(i8 *)(i + dest) = 0x80;
  }
  return;
}

/* 005d6b89 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __cdecl snd_wave_reset_all(HWAVEOUT wave_out)

{
  int *next;
  iptr ring;
  uint i;
  i32 result;
  int *buffer;
  
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

/* 005d6c99 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __cdecl snd_wave_on_buffer_done(HWAVEOUT wave_out,iptr wave_hdr)

{
  i16 sound_id;
  i32 *hdr;
  int src;
  MMRESULT write_result;
  iptr first_source;
  i32 *source;
  uint i;
  byte *sample;
  int *buffer;
  i32 *prev;
  int active_count;
  uint result;
  code *done_callback;
  
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
              snd_resample_8bit((byte *)buffer[4],(byte *)src,buffer[6] / (int)(uint)(ushort)snd_wave_block_align,
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
          write_result = waveOutWrite(wave_out,(LPWAVEHDR)*buffer,0x20);
          result = (result & 0xffff0000 | (ushort)((short)write_result));
          if ((short)write_result == 0) {
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
        call_untyped(done_callback, sound_id);
      }
    }
  }
  return 0;
}

/* 005d717f auto */
i32 __cdecl snd_wave_mix_buffer(i32 *hdr)

{
  bool finished;
  i32 result;
  int src;
  iptr buffer;
  i32 *source;
  i32 *prev;
  
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
          snd_resample_8bit((byte *)*(i32 *)(buffer + 0x10),(byte *)src,
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

/* 005d7494 auto */
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

/* 005d753e auto */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

i32 __cdecl snd_wave_copy_source(iptr source,int dst,uint length)

{
  ushort consumed;
  uint want;
  uint avail;
  i32 result;
  uint count;
  uint remaining;
  
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
    consumed = snd_resample_8bit((byte *)dst,(byte *)*(i32 *)(source + 0x34),count,
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

/* 005d778c auto */
i32 __cdecl snd_wave_mix_source(uptr source,i32 dst,uint length)

{
  ushort consumed;
  uint avail;
  uint want;
  uptr flags;
  i32 result;
  i32 advance;
  i32 count;
  uint remaining;
  
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
    consumed = snd_mix_8bit_resample((char *)dst,(byte *)*(i32 *)(source + 0x34),count,
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

/* 005d791b auto */
i32 __cdecl snd_avi_fill_buffer(iptr buffer,iptr source)

{
  i32 result;
  uint limit;
  iptr head;
  uint byte_count;
  uint i;
  int bytes_read;
  
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
                  byte_count / *(ushort *)(snd_wave_sources + 0x80),(LPVOID)*(i32 *)(snd_wave_sources + 0x34)
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

/* 005dd010 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

DocumentWindow * __thiscall mmwnd_ctor(DocumentWindow *self)

{
  i32 eh_next;
  i8 *eh_handler;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  surfwnd_ctor((SurfaceWindow *)self);
  eh_state = 0;
  avi_audio_ctor((AviAudio *)&self->border_width);
  (*(i8 *)((char *)&eh_state + 0)) = 1;
  palette_init((GamePalette *)&self->client_x);
  eh_state = (eh_state & 0xffffff00 | (byte)(2));
  surface_ctor((DibSurface *)(self->movie_surface));
  self->vtable = (u32)((pointer *)&leader_anim_frame_starts_block.ptr_fun_6);
  self->style_flags = 0;
  self->double_size = 0;
  self->avi_option = 0;
  self->target_surface = 0;
  self->has_audio = 1;
  self->audio_playing = 0;
  self->target_surface = 0;
  self->start_frame = 0;
  self->end_frame = 0;
  self->current_frame = 0;
  self->edit_action_button = 0;
  self->cue_frame = 0;
  self->paused = 1;
  self->loop = 0;
  avi_current_player_i32 = (i32)self;
  return self;
}

/* 005dd1a0 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __thiscall avi_player_dtor(AviPlayer *self)

{
  i32 eh_next;
  i8 *eh_handler;
  int eh_state;
  
  *(i8 ***)self->media_window_base = (i8 **)((pointer *)&leader_anim_frame_starts_block.ptr_fun_6);
  eh_state = eh_state & 0xff;
  (*(i8 *)((char *)&eh_state + 0)) = 3;
  avi_play_pause((iptr)self);
  avi_close((iptr)self);
  avi_current_player_i32 = 0;
  (*(i8 *)((char *)&eh_state + 0)) = 2;
  /* inlined unwind funclet 005dd230 */ { surface_dtor((DibSurface *)(*(int *)((iptr)&self) + 0x558)); }
  (*(i8 *)((char *)&eh_state + 0)) = 1;
  /* inlined unwind funclet 005dd23f */ { palette_destroy((GamePalette *)(*(int *)((iptr)&self) + 0x124)); }
  eh_state = eh_state & 0xffffff00;
  /* inlined unwind funclet 005dd24e */ { avi_audio_release((AviAudioReleaseView *)(*(int *)((iptr)&self) + 0x11c)); }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 005dd25d */ { surfwnd_dtor(*(SurfaceWindow **)((iptr)&self)); }
  return eh_next;
}

/* 005dd27e auto */
void __thiscall
avi_player_create
          (MediaWindow *self,iptr parent,i32 style,u32 x,u32 y)

{
  surface_wnd_create
            ((DibSurface *)self,parent,style,x,y,0x140,0xf0,(iptr)&self->client_x
            );
  surface_fill((DibSurface *)self,0);
  self->pos_x = x;
  self->pos_y = y;
  return;
}

/* 005dd2e3 auto */
void __thiscall
avi_player_create_child
          (MediaWindow *self,iptr parent,i32 style,u32 x,u32 y,iptr target
          )

{
  iptr target_dib;
  
  if (target == 0) {
    target_dib = 0;
  }
  else {
    target_dib = target + 0x48;
  }
  wnd_create_with_surface
            ((DibSurface *)self,parent,style,x,y,0x140,0xf0,(iptr)&self->client_x
             ,target_dib);
  surface_fill((DibSurface *)self,0);
  self->target_surface = target;
  self->pos_x = x;
  self->pos_y = y;
  return;
}

/* 005dd377 auto */
int __thiscall avi_player_open(AviPlayerOpenView *self,iptr filename)

{
  int result;
  
  avi_close((iptr)self);
  result = avi_open_file((iptr)self,filename);
  if (result == 0) {
    result = 0;
  }
  return result;
}

/* 005dd3c2 auto */
void __thiscall avi_player_play(AviPlayerPlayView *self)

{
  ((AviPlayerPlayViewExt *)self)->loop_flag[0] = '\0';
  ((AviPlayerPlayViewExt *)self)->loop_flag_byte1[0] = '\0';
  ((AviPlayerPlayViewExt *)self)->loop_flag_byte2[0] = '\0';
  ((AviPlayerPlayViewExt *)self)->loop_flag_byte3[0] = '\0';
  avi_play_start((iptr)self);
  return;
}

/* 005dd3f1 auto */
void __thiscall avi_player_play_range(AviPlayerRangeView *self,u32 first_frame,u32 last_frame)

{
  if ((int)first_frame <= (int)last_frame) {
    self->loop = 0;
    avi_seek_frame((iptr)self,first_frame,0);
    self->end_frame = last_frame;
    self->start_frame = first_frame;
    avi_play_start((iptr)self);
  }
  return;
}

/* 005dd45d auto */
void __thiscall avi_player_show_frame(void *self,i32 frame)

{
  avi_seek_frame((iptr)self,frame,1);
  return;
}

/* 005dd4c2 auto */
void __thiscall avi_player_loop_range(AviPlayerLoopView *self,u32 first_frame,u32 last_frame)

{
  self->start_frame = first_frame;
  avi_seek_frame((iptr)self,first_frame,0);
  self->end_frame = last_frame;
  self->loop = 1;
  avi_play_start((iptr)self);
  return;
}

/* 005dd51d auto */
void __thiscall avi_player_pause(AviPlayerPauseView *self)

{
  avi_play_pause((iptr)self);
  return;
}

/* 005dd561 auto */
void __thiscall avi_player_set_palette(DibSurface *self,iptr palette)

{
  avi_apply_palette((iptr)self,(GamePalette *)palette);
  surface_set_palette(self,palette);
  wnd_set_palette((WndBase *)(self + 1),palette);
  return;
}

/* 005dd64c auto */
void __thiscall
avi_player_draw_to(DibSurface *self,iptr dest,int x,int y)

{
  int dest_size;
  int src_size;
  tagRECT src_rect;
  tagRECT dst_rect;
  
  if ((-1 < x) && (-1 < y)) {
    dest_size = surface_width((DibSurface *)dest);
    src_size = surface_get_width(self);
    if (src_size <= dest_size - x) {
      dest_size = surface_height((DibSurface *)dest);
      src_size = surface_get_height(self);
      if (src_size <= dest_size - y) {
        avi_decode_frame((iptr)self,0);
        dest_size = surface_get_height(self);
        src_size = surface_get_width(self);
        SetRect(&src_rect,0,0,src_size,dest_size);
        CopyRect(&dst_rect,&src_rect);
        OffsetRect(&dst_rect,x,y);
        surface_blit(self,dest,(iptr)&src_rect,(iptr)&dst_rect);
      }
    }
  }
  return;
}

/* 005dd71e auto */
void __thiscall avi_player_set_double_size(MediaWindow *self,i32 enable)

{
  int height;
  int width;
  
  height = surface_get_height((DibSurface *)self);
  height = height * 2;
  width = surface_get_width((DibSurface *)self);
  wnd_resize_clamped((WindowObjectView *)self,width * 2,height);
  self->double_size = 1;
  return;
}

/* 005dd761 auto */
void __thiscall avi_player_set_transparent(AviPlayerSetTransparentView *self,int enable)

{
  if (enable == 0) {
    if (self->is_transparent != 0) {
      self->is_transparent = 0;
      avi_restart_decompress((iptr)self,0);
    }
  }
  else if (self->is_transparent == 0) {
    self->is_transparent = 1;
    avi_restart_decompress((iptr)self,1);
  }
  return;
}

/* 005dd8a0 auto */
void __cdecl snd_system_init(void)

{
  WNDCLASSA wnd_class;
  
  wnd_class.style = 0;
  wnd_class.lpfnWndProc = (WNDPROC)snd_mci_notify_wndproc;
  wnd_class.cbClsExtra = 0;
  wnd_class.cbWndExtra = 0;
  wnd_class.hInstance = err_report_ctx_block.app_hinstance;
  wnd_class.hIcon = (HICON)0x0;
  wnd_class.hCursor = (HCURSOR)0x0;
  wnd_class.hbrBackground = (HBRUSH)0x0;
  wnd_class.lpszMenuName = (LPCSTR)0x0;
  wnd_class.lpszClassName = str_msmmwindow;
  RegisterClassA(&wnd_class);
  err_report_ctx_block.snd_mci_notify_hwnd = CreateWindowExA(0,str_msmmwindow_2,(LPCSTR)0x0,0,-0x80000000,-0x80000000,
                                 -0x80000000,-0x80000000,(HWND)0x0,(HMENU)0x0,err_report_ctx_block.app_hinstance,
                                 (LPVOID)0x0);
  snd_cd_open();
  return;
}

/* 005dd93f auto */
LRESULT __stdcall snd_mci_notify_wndproc(HWND hwnd,UINT msg,WPARAM wparam,uint lparam)

{
  LRESULT ret;
  
  if (msg == 0x3b9) {
    if (wparam == 1) {
      if ((lparam & 0xffff) == snd_midi_device_id) {
        snd_midi_fire_notify_callback();
      }
      else if ((lparam & 0xffff) == snd_cd_device_id) {
        snd_cd_fire_notify_callback();
      }
    }
    ret = 0;
  }
  else {
    ret = DefWindowProcA(hwnd,msg,wparam,lparam);
  }
  return ret;
}

/* 005dda11 auto */
void __cdecl snd_stop_sndplaysound(void)

{
  sndPlaySoundA((LPCSTR)0x0,1);
  return;
}

/* 005ddbc7 auto */
i32 __cdecl snd_cd_play_track(uint track)

{
  MCIERROR mci_result;
  i32 result;
  MCI_PLAY_PARMS play_parms;
  DWORD_PTR play_flags;
  MCI_SEEK_PARMS seek_parms;
  MCIDEVICEID device_id;
  
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
  seek_parms.dwCallback = 0;
  seek_parms.dwTo = track & 0xff;
  mci_result = mciSendCommandA(device_id,0x807,8,(DWORD_PTR)&seek_parms);
  if (mci_result == 0) {
    if ((track & 0xff) == (*(uint *)&snd_cd_track_count)) {
      play_flags = 5;
    }
    else {
      play_flags = 0xd;
    }
    play_parms.dwFrom = track & 0xff;
    play_parms.dwTo = (uint)(byte)((char)track + 1);
    play_parms.dwCallback = (*(i32 *)&err_report_ctx_block.snd_mci_notify_hwnd);
    mci_result = mciSendCommandA(device_id,0x806,play_flags,(DWORD_PTR)&play_parms);
    if (mci_result == 0) {
      result = 1;
    }
    else {
      snd_cd_close();
      dbg_logf((iptr)&str_failed_to_play_requested_cd_track_2,mci_result);
      result = 0;
    }
  }
  else {
    snd_cd_close();
    dbg_logf((iptr)&str_failed_to_play_requested_cd_track,mci_result);
    result = 0;
  }
  return result;
}

/* 005ddd12 auto */
void __cdecl snd_midi_close(void)

{
  if (snd_midi_device_id != 0) {
    mciSendCommandA(snd_midi_device_id,0x808,0,0);
    snd_midi_device_id = 0;
  }
  return;
}

/* 005ddd4e auto */
void __cdecl snd_cd_open(void)

{
  MCIERROR mci_result;
  MCI_OPEN_PARMSA open_parms;
  MCI_SET_PARMS set_parms;
  MCI_STATUS_PARMS status_parms;
  
  if (snd_cd_device_id == 0) {
    open_parms.lpstrDeviceType = str_cdaudio;
    mci_result = mciSendCommandA(0,0x803,0x2000,(DWORD_PTR)&open_parms);
    if (mci_result == 0) {
      snd_cd_device_id = open_parms.wDeviceID;
      set_parms.dwTimeFormat = 10;
      mci_result = mciSendCommandA(open_parms.wDeviceID,0x80d,0x400,(DWORD_PTR)&set_parms);
      if (mci_result == 0) {
        status_parms.dwCallback = 0;
        status_parms.dwReturn = 0;
        status_parms.dwTrack = 0;
        status_parms.dwItem = 3;
        mciSendCommandA(snd_cd_device_id,0x814,0x100,(DWORD_PTR)&status_parms);
        snd_cd_track_count = status_parms.dwReturn;
      }
      else {
        mciSendCommandA(snd_cd_device_id,0x804,0,0);
        snd_cd_device_id = 0;
        dbg_logf((iptr)&str_cdaudio_could_not_set_time_format,mci_result);
      }
    }
    else {
      dbg_logf((iptr)&str_failed_to_open_cdaudio_device,mci_result);
    }
  }
  return;
}

/* 005dde57 auto */
void __cdecl snd_cd_close(void)

{
  if (snd_cd_device_id != 0) {
    mciSendCommandA(snd_cd_device_id,0x804,0,0);
    snd_cd_device_id = 0;
    snd_cd_track_count = 0;
  }
  return;
}

/* 005dde9d auto */
void __cdecl snd_cd_mci_stop(void)

{
  if (snd_cd_device_id != 0) {
    mciSendCommandA(snd_cd_device_id,0x808,0,0);
  }
  return;
}

/* 005ddecf auto */
void __cdecl snd_system_shutdown(void)

{
  snd_stop_sndplaysound();
  snd_cd_mci_stop();
  snd_cd_close();
  snd_midi_close();
  DestroyWindow(err_report_ctx_block.snd_mci_notify_hwnd);
  return;
}

/* 005ddeff auto */
i32 __cdecl snd_cd_get_track_count(void)

{
  MCIERROR mci_result;
  MCI_OPEN_PARMSA open_parms;
  MCIDEVICEID device_id;
  MCI_SET_PARMS set_parms;
  MCI_STATUS_PARMS status_parms;
  i32 track_count;
  
  if (snd_cd_device_id == 0) {
    open_parms.lpstrDeviceType = str_cdaudio_2;
    mci_result = mciSendCommandA(0,0x803,0x2000,(DWORD_PTR)&open_parms);
    if (mci_result != 0) {
      return 0xffffffff;
    }
    device_id = open_parms.wDeviceID;
    snd_cd_device_id = open_parms.wDeviceID;
    set_parms.dwTimeFormat = 10;
    mci_result = mciSendCommandA(open_parms.wDeviceID,0x80d,0x400,(DWORD_PTR)&set_parms);
    if (mci_result != 0) {
      mciSendCommandA(device_id,0x804,0,0);
      snd_cd_device_id = 0;
      return 0xffffffff;
    }
  }
  else {
    device_id = snd_cd_device_id;
  }
  status_parms.dwItem = 3;
  mci_result = mciSendCommandA(device_id,0x814,0x100,(DWORD_PTR)&status_parms);
  if (mci_result == 0) {
    track_count = status_parms.dwReturn;
    snd_cd_track_count = track_count;
  }
  else {
    snd_cd_close();
    track_count = 0xffffffff;
  }
  return track_count;
}

/* 005de6bd auto */
void __cdecl snd_midi_fire_notify_callback(void)

{
  if (err_report_ctx_block.snd_midi_notify_callback != (code *)0x0) {
    (*err_report_ctx_block.snd_midi_notify_callback)();
  }
  return;
}

/* 005de6fc auto */
void __cdecl snd_cd_set_notify_callback(iptr callback)

{
  err_report_ctx_block.snd_cd_notify_callback = callback;
  return;
}

/* 005de714 auto */
void __cdecl snd_cd_fire_notify_callback(void)

{
  if ((*(code * *)&err_report_ctx_block.snd_cd_notify_callback) != (code *)0x0) {
    call_untyped((*(code * *)&err_report_ctx_block.snd_cd_notify_callback));
  }
  return;
}

/* 005e1c70 auto */
void __cdecl avi_update_current_frame(void)

{
  avi_update_frame(avi_active_window);
  return;
}

/* 005e1c8e auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl avi_open_file(iptr player,i32 filename)

{
  int attach_result;
  i32 start_frame;
  int value;
  iptr dib;
  HGLOBAL mem_handle;
  i8 palette_rgb[708];
  AVISTREAMINFOA stream_info;
  iptr i;
  i32 format_size;
  int result;
  
  if (err_report_ctx_block.avi_vfw_initialized == 0) {
    AVIFileInit();
    err_report_ctx_block.avi_vfw_initialized = 1;
  }
  avi_active_window = player;
  err_report_ctx_block.avi_indeo_seq_opts[0] = 0x2c;
  err_report_ctx_block.avi_indeo_seq_fourcc_i32 = 0x31345649;
  err_report_ctx_block.avi_indeo_seq_environment_i32 = 2;
  err_report_ctx_block.avi_indeo_seq_version_i32 = 0x10002;
  err_report_ctx_block.avi_indeo_seq_type_i32 = 4;
  err_report_ctx_block.g_video_flags_a = 0;
  err_report_ctx_block.avi_indeo_seq_extra_i32 = 0;
  err_report_ctx_block.avi_indeo_frame_opts[0] = 0x70;
  err_report_ctx_block.avi_indeo_frame_fourcc_i32 = 0x31345649;
  err_report_ctx_block.avi_indeo_frame_environment_i32 = 2;
  err_report_ctx_block.avi_indeo_frame_version_i32 = 0x10002;
  err_report_ctx_block.avi_indeo_frame_type_i32 = 2;
  err_report_ctx_block.avi_indeo_view_rect_ptr_i32 = (i32)((i32 *)&err_report_ctx_block.avi_view_rect_x);
  err_report_ctx_block.g_video_flags_b = 0x80000008;
  err_report_ctx_block.avi_view_rect_x[0] = 0;
  err_report_ctx_block.avi_view_rect_y = 0;
  err_report_ctx_block.avi_view_rect_width_i32 = 0;
  err_report_ctx_block.avi_view_rect_height_i32 = 0;
  result = AVIFileOpenA(((PAVIFILE *)&avi_file),(LPCSTR)filename,0,0);
  if (result == 0) {
    result = AVIFileGetStream(avi_file[0],((PAVISTREAM *)&avi_video_stream),0x73646976,0);
    if (result == 0) {
      value = 0;
      if (*(int *)(player + 0x5a8) != 0) {
        result = AVIFileGetStream(avi_file[0],((PAVISTREAM *)&avi_audio_stream),0x73647561,0);
        if (result == 0) {
          *(i32 *)(player + 0x5b0) = 0;
          attach_result = avi_audio_attach_stream((AviAudioAttachView *)(player + 0x11c),avi_audio_stream[0]);
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
      AVIStreamReadFormat(avi_video_stream[0],1,(LPVOID)(player + 0x5c0),&format_size);
      AVIStreamInfoA(avi_video_stream[0],&stream_info,0x8c);
      *(SIZE_T *)(player + 0x5d4) = stream_info.dwSuggestedBufferSize;
      err_report_ctx_block.avi_frames_per_second_i32 = stream_info.dwRate / stream_info.dwScale;
      avi_decompressor = ICLocate(0x63646976,stream_info.fccHandler,(LPBITMAPINFOHEADER)(player + 0x5c0),0,2);
      if (avi_decompressor == 0) {
        avi_close(player);
        result = 0;
      }
      else {
        start_frame = AVIStreamStart(avi_video_stream[0]);
        *(i32 *)(player + 0xa10) = start_frame;
        value = AVIStreamLength(avi_video_stream[0]);
        *(int *)(player + 0xa14) = *(int *)(player + 0xa10) + value - 1;
        *(i32 *)(player + 0xa18) = *(i32 *)(player + 0xa10);
        crt_memcpy((void *)(player + 0x5e8),(const void *)(player + 0x5c0),0x28);
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
        if (stream_info.dwSuggestedBufferSize == 0) {
          value = (uint)*(ushort *)(player + 0x5ce) * *(int *)(player + 0x5c4) *
                  *(int *)(player + 0x5c8);
          mem_handle = GlobalAlloc(0x40,(int)(value + (value >> 0x1f & 7U)) >> 3);
          avi_frame_buffer = GlobalLock(mem_handle);
        }
        else {
          mem_handle = GlobalAlloc(0x40,stream_info.dwSuggestedBufferSize);
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
              avi_blit_union_left_block.g_video_frame_count = 0;
              err_report_ctx_block.avi_indeo_frame_extra_i32 = 0;
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

/* 005e22ed: written by hand in src/game/fixups.cpp */

/* 005e250c auto */
i32
__stdcall avi_ic_decompress_ex_begin(i32 hic,i32 flags,iptr bi_src,i32 src_bits,
            i32 x_src,i32 y_src,i32 width_src,i32 height_src,iptr bi_dst
            ,i32 dst_bits,i32 x_dst,i32 y_dst,i32 width_dst,
            i32 height_dst)

{
  i32 result;
  ICDECOMPRESSEX ex;
  
  ex.dwFlags = flags;
  ex.lpbiSrc = (BITMAPINFOHEADER *)bi_src;
  ex.lpSrc = (void *)src_bits;
  ex.xSrc = x_src;
  ex.ySrc = y_src;
  ex.dxSrc = width_src;
  ex.dySrc = height_src;
  ex.lpbiDst = (BITMAPINFOHEADER *)bi_dst;
  ex.lpDst = (void *)dst_bits;
  ex.xDst = x_dst;
  ex.yDst = y_dst;
  ex.dxDst = width_dst;
  ex.dyDst = height_dst;
  result = ICSendMessage(hic,0x403c,(DWORD_PTR)&ex,0x34);
  return result;
}

/* 005e2583 auto */
i32
__stdcall avi_ic_decompress_ex_query(i32 hic,i32 flags,iptr bi_src,i32 src_bits,
            i32 x_src,i32 y_src,i32 width_src,i32 height_src,iptr bi_dst
            ,i32 dst_bits,i32 x_dst,i32 y_dst,i32 width_dst,
            i32 height_dst)

{
  i32 result;
  ICDECOMPRESSEX ex;
  
  ex.dwFlags = flags;
  ex.lpbiSrc = (BITMAPINFOHEADER *)bi_src;
  ex.lpSrc = (void *)src_bits;
  ex.xSrc = x_src;
  ex.ySrc = y_src;
  ex.dxSrc = width_src;
  ex.dySrc = height_src;
  ex.lpbiDst = (BITMAPINFOHEADER *)bi_dst;
  ex.lpDst = (void *)dst_bits;
  ex.xDst = x_dst;
  ex.yDst = y_dst;
  ex.dxDst = width_dst;
  ex.dyDst = height_dst;
  result = ICSendMessage(hic,0x403d,(DWORD_PTR)&ex,0x34);
  return result;
}

/* 005e2675 auto */
void __cdecl avi_play_pause(iptr player)

{
  if ((player != 0) && (avi_file_loaded != 0)) {
    if (*(int *)(player + 0x5a8) != 0) {
      *(i32 *)(player + 0x5b0) = 0;
    }
    *(i32 *)(player + 0x5ac) = 1;
    if (avi_playing != 0) {
      wnd_modal_stack_below_block.avi_idle_update_enabled = 0;
      avi_blit_union_left_block.avi_frame_needs_blit = 0;
      avi_playing = 0;
    }
  }
  return;
}

/* 005e2799 auto */
void __cdecl avi_close(iptr player)

{
  HGLOBAL mem_handle;
  
  if (player != 0) {
    avi_play_pause(player);
    if (avi_decompressor != 0) {
      ICClose(avi_decompressor);
      avi_decompressor = 0;
    }
    if (avi_audio_stream[0] != 0) {
      AVIStreamRelease(avi_audio_stream[0]);
      avi_audio_stream[0] = 0;
    }
    if (avi_video_stream[0] != 0) {
      AVIStreamRelease(avi_video_stream[0]);
      avi_video_stream[0] = 0;
    }
    if (avi_file[0] != 0) {
      AVIFileRelease(avi_file[0]);
      avi_file[0] = 0;
    }
    if (err_report_ctx_block.avi_vfw_initialized != 0) {
      AVIFileExit();
      err_report_ctx_block.avi_vfw_initialized = 0;
    }
    if ((*(LPCVOID *)&avi_frame_buffer) != (LPCVOID)0x0) {
      mem_handle = GlobalHandle((*(LPCVOID *)&avi_frame_buffer));
      GlobalUnlock(mem_handle);
      mem_handle = GlobalHandle((*(LPCVOID *)&avi_frame_buffer));
      GlobalFree(mem_handle);
      (*(LPCVOID *)&avi_frame_buffer) = (LPCVOID)0x0;
    }
    avi_frame_buffer_size = 0;
    avi_frame_width = 0;
    avi_frame_height = 0;
    avi_active_window = 0;
  }
  return;
}

/* 005e28cd auto */
void __cdecl avi_seek_frame(iptr player,uint frame_index,int redraw)

{
  i32 key_frame;
  uint target_frame;
  
  if ((player != 0) && (avi_file_loaded != 0)) {
    if (avi_playing != 0) {
      avi_play_pause(player);
    }
    key_frame = AVIStreamFindSample(avi_video_stream[0],frame_index,0x14);
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

/* 005e2997 auto */
int __cdecl avi_decode_frame(iptr player,int decode_flags)

{
  i32 dst_bits;
  i32 x_dst;
  i32 y_dst;
  int dst_dim_a;
  int dst_dim_b;
  CHAR message[80];
  i32 bytes_read;
  int result;
  
  result = 0;
  bytes_read = 0;
  if ((player == 0) || (avi_file_loaded == 0)) {
    result = 1;
  }
  else {
    if ((*(int *)(player + 0x5a4) != 0) && (decode_flags == 0)) {
      surface_blit((DibSurface *)(player + 0x558),player,(iptr)&avi_blit_union_left_block.avi_blit_union_left,(iptr)&avi_blit_union_left_block.avi_blit_union_left);
    }
    result = AVIStreamRead(avi_video_stream[0],*(i32 *)(player + 0xa18),1,avi_frame_buffer,
                            avi_frame_buffer_size,&bytes_read,0);
    if (result == 0) {
      *(i32 *)(player + 0x5d4) = bytes_read;
      if (*(int *)(player + 0x5a0) == 0) {
        y_dst = 0;
        x_dst = 0;
        dst_dim_b = avi_frame_width;
        dst_dim_a = avi_frame_height;
        dst_bits = surface_get_bits((DibSurface *)player);
        result = avi_ic_decompress_ex(avi_decompressor,decode_flags,player + 0x5c0,(*(i32 *)&avi_frame_buffer),0,0,avi_frame_width,
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
        result = avi_ic_decompress_ex(avi_decompressor,decode_flags,player + 0x5c0,(*(i32 *)&avi_frame_buffer),0,0,avi_frame_width,
                               avi_frame_height,player + 0x5e8,dst_bits,x_dst,y_dst,dst_dim_a,dst_dim_b);
        *(int *)(player + 0x5f0) = *(int *)(player + 0x5f0) >> 1;
        *(int *)(player + 0x5ec) = *(int *)(player + 0x5ec) >> 1;
      }
      if ((result != 0) && (result != 1)) {
        wsprintfA(message,str_icdecompressex_returned_ld,result);
        MessageBoxA((HWND)0x0,message,str_get_frame,0);
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

/* 005e2c5a auto */
i32
__stdcall avi_ic_decompress_ex(i32 hic,i32 flags,iptr bi_src,i32 src_bits,
            i32 x_src,i32 y_src,i32 width_src,i32 height_src,iptr bi_dst
            ,i32 dst_bits,i32 x_dst,i32 y_dst,i32 width_dst,
            i32 height_dst)

{
  i32 result;
  ICDECOMPRESSEX ex;
  
  ex.dwFlags = flags;
  ex.lpbiSrc = (BITMAPINFOHEADER *)bi_src;
  ex.lpSrc = (void *)src_bits;
  ex.xSrc = x_src;
  ex.ySrc = y_src;
  ex.dxSrc = width_src;
  ex.dySrc = height_src;
  ex.lpbiDst = (BITMAPINFOHEADER *)bi_dst;
  ex.lpDst = (void *)dst_bits;
  ex.xDst = x_dst;
  ex.yDst = y_dst;
  ex.dxDst = width_dst;
  ex.dyDst = height_dst;
  result = ICSendMessage(hic,0x403e,(DWORD_PTR)&ex,0x34);
  return result;
}

/* 005e2cd1 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl avi_update_frame(iptr player)

{
  int sample;
  i32 audio_pos_ms;
  uint target_frame;
  RECT dirty_rect;
  int key_frame;
  DWORD now;
  
  if (player == 0) {
    return;
  }
  if (avi_file_loaded == 0) {
    return;
  }
  if (avi_playing != 0) {
    if (*(int *)(player + 0x5a8) == 0) {
      now = timeGetTime();
      sample = AVIStreamTimeToSample(avi_video_stream[0],now - g_video_start_time);
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
      sample = AVIStreamTimeToSample(avi_video_stream[0],audio_pos_ms);
      target_frame = *(int *)(player + 0xa10) + sample;
      if ((*(int *)(player + 0x5ac) == 0) || (target_frame < *(uint *)(player + 0xa18))) {
        snd_avi_stream_feed(0x40);
        avi_blit_union_left_block.g_video_frame_count++;
        return;
      }
    }
    if ((*(uint *)&avi_blit_union_left_block.avi_frame_needs_blit) != 0) {
      if (*(int *)(player + 0x5a4) == 0) {
        wnd_blit_surface((DibSurface *)player);
      }
      else {
        dirty_rect.left = err_report_ctx_block.avi_view_rect_x[0];
        dirty_rect.top = err_report_ctx_block.avi_view_rect_y;
        dirty_rect.right = err_report_ctx_block.avi_view_rect_x[0] + err_report_ctx_block.avi_view_rect_width_i32;
        dirty_rect.bottom = err_report_ctx_block.avi_view_rect_y + err_report_ctx_block.avi_view_rect_height_i32;
        UnionRect(&dirty_rect,&dirty_rect,(RECT *)((i32 *)&avi_blit_union_left_block.avi_blit_union_left));
        wnd_blit_surface_rect((DibSurface *)player,(iptr)&dirty_rect);
        avi_blit_union_left_block.avi_blit_union_left[0] = dirty_rect.left;
        avi_blit_union_left_block.avi_blit_union_top = dirty_rect.top;
        avi_blit_union_left_block.avi_blit_union_right = dirty_rect.right;
        avi_blit_union_left_block.avi_blit_union_bottom = dirty_rect.bottom;
      }
    }
    if (*(uint *)(player + 0xa18) < target_frame) {
      key_frame = *(int *)(player + 0xa18);
      do {
        sample = key_frame;
        key_frame++;
        key_frame = AVIStreamFindSample(avi_video_stream[0],key_frame,0x11);
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
    avi_blit_union_left_block.g_video_frame_count++;
  }
  sample = avi_decode_frame(player,0);
  (*(uint *)&avi_blit_union_left_block.avi_frame_needs_blit) = (uint)(sample == 0);
  return;
}

/* 005e30a1 auto */
void __cdecl avi_apply_palette(iptr player,GamePalette *palette)

{
  i8 palette_rgb[708];
  int i;
  int result;
  
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

/* 005e32b2 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl avi_restart_decompress(iptr player,int transparent)

{
  int yBottom;
  int xRight;
  tagRECT dst_rect;
  tagRECT src_rect;
  i32 cur_frame;
  int result;
  
  if ((player != 0) && (avi_file_loaded != 0)) {
    ICSendMessage(avi_decompressor,0x403f,0,0);
    if (transparent == 0) {
      err_report_ctx_block.g_video_flags_a = 0;
    }
    else {
      err_report_ctx_block.g_video_flags_a = 0x80000004;
    }
    err_report_ctx_block.g_video_flags_b = 0x80000008;
    ICSendMessage(avi_decompressor,0x5001,(DWORD_PTR)((i8 *)&err_report_ctx_block.avi_indeo_seq_opts),0x2c);
    ICSendMessage(avi_decompressor,0x5001,(DWORD_PTR)((i8 *)&err_report_ctx_block.avi_indeo_frame_opts),0x70);
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

/* 005e3550 auto */
void __thiscall avi_player_call_end_callback(AviPlayerEndCbCallView *self)

{
  if (self->on_end != 0) {
    call_untyped((code *)self->on_end);
  }
  return;
}

/* 005e3580 auto */
void __thiscall avi_player_call_cue_callback(AviPlayerCueCbCallView *self)

{
  if (self->on_cue != 0) {
    call_untyped((code *)self->on_cue);
  }
  return;
}

/* 005ec317 auto */
i32 __stdcall moviewnd_wndproc(HWND hwnd,uint msg,uint wparam,uint lparam)

{
  short thumb_pos;
  i32 result;
  iptr window;
  WndBase *wnd_obj;
  BOOL is_iconic;
  int value;
  i8 generic_parms[4];
  int frame_height;
  uptr minmax_info;
  int frame_width;
  iptr parent_window;
  int min_height2;
  int min_width2;
  int scroll_pos2;
  WndOnMciDoneView *wnd2;
  iptr mci_device2;
  int max_height2;
  int max_width2;
  
  wnd2 = (WndOnMciDoneView *)GetWindowLongA(hwnd,4);
  if (wnd2 == (WndOnMciDoneView *)0x0) {
    result = wnd_base_wndproc(hwnd,msg,wparam,lparam);
    return result;
  }
  if (msg < 0x11) {
    if (msg != 0x10) {
      switch(msg) {
      case 3:
        (*(WndOnMciDoneView * *)&wnd_active_child) = wnd2;
        wnd_call_move
                  ((WndOnMoveView *)(wnd2->handlers),lparam & 0xffff,lparam >> 0x10);
        result = wnd_base_wndproc(hwnd,msg,wparam,lparam);
        return result;
      default:
        goto default_wndproc;
      case 5:
handle_size:
        (*(WndOnMciDoneView * *)&wnd_active_child) = wnd2;
        is_iconic = IsIconic(hwnd);
        if (is_iconic == 0) {
          wnd_on_size_nop(wnd2,lparam & 0xffff,lparam >> 0x10);
          wnd_call_size((WndOnSizeView *)(wnd2->handlers),wparam);
        }
        result = wnd_base_wndproc(hwnd,msg,wparam,lparam);
        return result;
      case 6:
        goto handle_mci;
      case 7:
        (*(WndOnMciDoneView * *)&wnd_active_child) = wnd2;
        wnd_call_setfocus((WndOnSetFocusView *)(wnd2->handlers));
        return 0;
      }
    }
    (*(WndOnMciDoneView * *)&wnd_active_child) = wnd2;
    value = wnd_call_close((WndOnCloseView *)(wnd2->handlers));
    if (value != 0) {
      result = wnd_base_wndproc(hwnd,0x10,wparam,lparam);
      return result;
    }
  }
  else {
    if (msg < 0x45) {
      if (msg == 0x44) {
        (*(WndOnMciDoneView * *)&wnd_active_child) = wnd2;
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
default_wndproc:
      result = wnd_base_wndproc(hwnd,msg,wparam,lparam);
      return result;
    }
    if (msg < 0x112) {
      if (msg == 0x111) {
        (*(WndOnMciDoneView * *)&wnd_active_child) = wnd2;
        return 0;
      }
      if (msg == 0x100) {
        (*(WndOnMciDoneView * *)&wnd_active_child) = wnd2;
        result = input_map_vkey(wparam);
        wnd_call_keydown_pre((WndOnKeyDownPreView *)(wnd2->handlers),result);
        result = input_map_vkey(wparam);
        wnd_call_keydown((WndOnKeyDownView *)(wnd2->handlers),result);
        return 0;
      }
      if (msg == 0x101) {
        (*(WndOnMciDoneView * *)&wnd_active_child) = wnd2;
        result = input_map_vkey(wparam);
        wnd_call_keyup((WndOnKeyUpView *)(wnd2->handlers),result);
        return 0;
      }
      if (msg == 0x102) {
        (*(WndOnMciDoneView * *)&wnd_active_child) = wnd2;
        wnd_call_char((WndOnCharView *)(wnd2->handlers),wparam & 0xff);
        return 0;
      }
      goto default_wndproc;
    }
    if (msg < 0x201) {
      if (msg == 0x200) {
        (*(WndOnMciDoneView * *)&wnd_active_child) = wnd2;
        wnd_call_mousemove
                  ((WndOnMouseMoveView *)(wnd2->handlers),lparam & 0xffff,lparam >> 0x10);
        return 0;
      }
      if (msg == 0x112) {
        if (wparam == 0xf020) {
          (*(WndOnMciDoneView * *)&wnd_active_child) = wnd2;
          wnd_call_minimize((WndOnMinimizeView *)(wnd2->handlers));
        }
        else {
          (*(WndOnMciDoneView * *)&wnd_active_child) = wnd2;
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
          (*(WndOnMciDoneView * *)&wnd_active_child) = wnd2;
          *(int *)(wnd2->hscroll_pos) = scroll_pos2;
          wnd_call_hscroll((WndOnHScrollView *)(wnd2->handlers),scroll_pos2);
          return 0;
        case 1:
          scroll_pos2++;
          SetScrollPos(hwnd,0,scroll_pos2,1);
          scroll_pos2 = GetScrollPos(hwnd,0);
          (*(WndOnMciDoneView * *)&wnd_active_child) = wnd2;
          *(int *)(wnd2->hscroll_pos) = scroll_pos2;
          wnd_call_hscroll((WndOnHScrollView *)(wnd2->handlers),scroll_pos2);
          return 0;
        case 2:
          value = wnd_get_hscroll_page((WndHScrollPageView *)wnd2);
          scroll_pos2 -= value;
          SetScrollPos(hwnd,0,scroll_pos2,1);
          scroll_pos2 = GetScrollPos(hwnd,0);
          (*(WndOnMciDoneView * *)&wnd_active_child) = wnd2;
          *(int *)(wnd2->hscroll_pos) = scroll_pos2;
          wnd_call_hscroll((WndOnHScrollView *)(wnd2->handlers),scroll_pos2);
          return 0;
        case 3:
          value = wnd_get_hscroll_page((WndHScrollPageView *)wnd2);
          scroll_pos2 += value;
          SetScrollPos(hwnd,0,scroll_pos2,1);
          scroll_pos2 = GetScrollPos(hwnd,0);
          (*(WndOnMciDoneView * *)&wnd_active_child) = wnd2;
          *(int *)(wnd2->hscroll_pos) = scroll_pos2;
          wnd_call_hscroll((WndOnHScrollView *)(wnd2->handlers),scroll_pos2);
          return 0;
        case 4:
          scroll_pos2 = (int)thumb_pos;
          SetScrollPos(hwnd,0,scroll_pos2,1);
          (*(WndOnMciDoneView * *)&wnd_active_child) = wnd2;
          *(int *)(wnd2->hscroll_pos) = scroll_pos2;
          wnd_call_hscroll
                    ((WndOnHScrollView *)(wnd2->handlers),*(i32 *)(wnd2->hscroll_pos));
          return 0;
        case 5:
          (*(WndOnMciDoneView * *)&wnd_active_child) = wnd2;
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
          (*(WndOnMciDoneView * *)&wnd_active_child) = wnd2;
          *(int *)(wnd2->vscroll_pos) = scroll_pos2;
          wnd_call_vscroll((WndOnVScrollView *)(wnd2->handlers),scroll_pos2);
          return 0;
        case 1:
          scroll_pos2++;
          SetScrollPos(hwnd,1,scroll_pos2,1);
          scroll_pos2 = GetScrollPos(hwnd,1);
          (*(WndOnMciDoneView * *)&wnd_active_child) = wnd2;
          *(int *)(wnd2->vscroll_pos) = scroll_pos2;
          wnd_call_vscroll((WndOnVScrollView *)(wnd2->handlers),scroll_pos2);
          return 0;
        case 2:
          value = wnd_get_vscroll_page((WndVScrollPageView *)wnd2);
          scroll_pos2 -= value;
          SetScrollPos(hwnd,1,scroll_pos2,1);
          scroll_pos2 = GetScrollPos(hwnd,1);
          (*(WndOnMciDoneView * *)&wnd_active_child) = wnd2;
          *(int *)(wnd2->vscroll_pos) = scroll_pos2;
          wnd_call_vscroll((WndOnVScrollView *)(wnd2->handlers),scroll_pos2);
          return 0;
        case 3:
          value = wnd_get_vscroll_page((WndVScrollPageView *)wnd2);
          scroll_pos2 += value;
          SetScrollPos(hwnd,1,scroll_pos2,1);
          scroll_pos2 = GetScrollPos(hwnd,1);
          (*(WndOnMciDoneView * *)&wnd_active_child) = wnd2;
          *(int *)(wnd2->vscroll_pos) = scroll_pos2;
          wnd_call_vscroll((WndOnVScrollView *)(wnd2->handlers),scroll_pos2);
          return 0;
        case 4:
          scroll_pos2 = (int)thumb_pos;
          SetScrollPos(hwnd,1,scroll_pos2,1);
          (*(WndOnMciDoneView * *)&wnd_active_child) = wnd2;
          *(int *)(wnd2->vscroll_pos) = scroll_pos2;
          wnd_call_vscroll
                    ((WndOnVScrollView *)(wnd2->handlers),*(i32 *)(wnd2->vscroll_pos));
          return 0;
        case 5:
          (*(WndOnMciDoneView * *)&wnd_active_child) = wnd2;
          wnd_call_vscroll_track((WndOnVScrollTrackView *)(wnd2->handlers),(int)thumb_pos);
          return 0;
        default:
          return 0;
        }
      }
      goto default_wndproc;
    }
    if (msg < 0x211) {
      if (msg == 0x210) {
        if (wparam == 0x201) {
          (*(WndOnMciDoneView * *)&wnd_active_child) = wnd2;
          wnd_call_lbuttondown
                    ((WndOnLButtonDownView *)(wnd2->handlers),lparam & 0xffff,lparam >> 0x10);
          return 0;
        }
        if (wparam != 0x204) {
          return 0;
        }
        (*(WndOnMciDoneView * *)&wnd_active_child) = wnd2;
        wnd_call_rbuttondown
                  ((WndOnRButtonDownView *)(wnd2->handlers),lparam & 0xffff,lparam >> 0x10);
        return 0;
      }
      switch(msg) {
      case 0x201:
        wnd_obj = (WndBase *)GetWindowLongA(hwnd,0);
        parent_window = wnd_get_window(wnd_obj);
        (*(WndOnMciDoneView * *)&wnd_active_child) = wnd2;
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
        (*(WndOnMciDoneView * *)&wnd_active_child) = wnd2;
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
        (*(WndOnMciDoneView * *)&wnd_active_child) = wnd2;
        wnd_call_dblclick
                  ((WndOnDblClickView *)(wnd2->handlers),lparam & 0xffff,lparam >> 0x10);
        return 0;
      case 0x204:
        wnd_obj = (WndBase *)GetWindowLongA(hwnd,0);
        parent_window = wnd_get_window(wnd_obj);
        if ((*(byte *)(parent_window + 0x49) & 2) != 0) {
          SetFocus(*(HWND *)(parent_window + 4));
          BringWindowToTop(hwnd);
        }
        (*(WndOnMciDoneView * *)&wnd_active_child) = wnd2;
        wnd2->wnd_header_area[0xa8] = 1;
        wnd2->wnd_header_area[0xa9] = '\0';
        wnd2->wnd_header_area[0xaa] = '\0';
        wnd2->wnd_header_area[0xab] = '\0';
        wnd_call_rbuttondown
                  ((WndOnRButtonDownView *)(wnd2->handlers),lparam & 0xffff,lparam >> 0x10);
        return 0;
      case 0x205:
        (*(WndOnMciDoneView * *)&wnd_active_child) = wnd2;
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
      goto default_wndproc;
    }
    if ((msg != 0x30f) && (msg != 0x311)) {
      if (msg == 0x3b9) {
        if (wparam == 1) {
          wnd_call_mci_done(wnd2);
          return 0;
        }
        goto handle_size;
      }
      goto default_wndproc;
    }
handle_mci:
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

/* 005eeca0 auto */
AviAudio * __thiscall avi_audio_ctor(AviAudio *self)

{
  self->audio_stream = 0;
  return self;
}

/* 005eed1b auto */
void __thiscall avi_audio_release(AviAudioReleaseView *self)

{
  if (self->audio_stream != 0) {
    snd_avi_stream_stop();
  }
  return;
}

/* 005eed43 auto */
uint __thiscall avi_audio_is_playing(AviAudioPlayingView *self)

{
  return (uint)((self->state_flags & 4) != 0);
}

/* 005eed76 auto */
int __thiscall avi_audio_attach_stream(AviAudioAttachView *self,u32 stream)

{
  int result;
  
  result = snd_wave_add_avi_stream(stream);
  if (result == 0) {
    self->avi_stream = stream;
    self->stream_flags = self->stream_flags | 1;
  }
  else {
    self->stream_flags = 0;
  }
  return result;
}

/* 005eedd1 auto */
i32 __thiscall avi_audio_get_position_ms(void *self)

{
  i32 position_ms;
  
  position_ms = snd_wave_get_position_ms();
  return position_ms;
}

/* 005eedec auto */
int __thiscall avi_audio_prepare_range(AviAudioPrepareView *self,i32 start_time,i32 end_time)

{
  int result;
  
  result = snd_avi_stream_prepare(start_time,end_time,(iptr)self);
  if (result == 0) {
    self->audio_flags = self->audio_flags | 2;
  }
  else {
    self->audio_flags = self->audio_flags & 0xfffd;
  }
  return result;
}

/* 005eee4f auto */
i16 __thiscall avi_audio_start(void *self)

{
  snd_avi_stream_start();
  return 0;
}
