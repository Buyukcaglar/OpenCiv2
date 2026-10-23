/* The game, memory, lists, random numbers, debugging and errors: functions translated from the original
 * (tools/gen_c.py, now edited directly), in address order. */
#include "auto_common.h"

/* 00407ff0 auto */
void __cdecl win_flush_pending_msgs(void)

{
  win_dispatch_custom_msgs();
  return;
}

/* 0040ef50 auto */
void __cdecl win_pump_one_message(void)

{
  win_dispatch_one_message();
  return;
}

/* 00414f02 auto */
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
void __cdecl int_pairs_bubble_sort(int param_1,iptr param_2,iptr param_3)

{
  i32 uVar1;
  bool bVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  do {
    bVar2 = false;
    for (local_c = 0; (!bVar2 && (local_c < param_1 - 1)); local_c++) {
      if (*(int *)(param_3 + 4 + local_c * 4) < *(int *)(param_3 + local_c * 4)) {
        uVar1 = *(i32 *)(param_3 + local_c * 4);
        *(i32 *)(param_3 + local_c * 4) = *(i32 *)(param_3 + 4 + local_c * 4);
        *(i32 *)(param_3 + 4 + local_c * 4) = uVar1;
        uVar1 = *(i32 *)(param_2 + local_c * 4);
        *(i32 *)(param_2 + local_c * 4) = *(i32 *)(param_2 + 4 + local_c * 4);
        *(i32 *)(param_2 + 4 + local_c * 4) = uVar1;
        bVar2 = true;
      }
    }
  } while (bVar2);
  return;
}
#undef local_c

/* 00428cb0 auto */
MemBlock * __thiscall memblock_ctor(MemBlock *this)

{
  this->mem_handle = 0;
  this->base_ptr = 0;
  this->capacity = 0;
  return this;
}

/* 0046aaa0 auto */
i32 __cdecl mem_free_handle(iptr param_1)

{
  i32 uVar1;
  
  uVar1 = mem_handle_free(param_1);
  return uVar1;
}

/* 0046aad0 auto */
i32 __cdecl mem_lock_handle(iptr param_1)

{
  i32 uVar1;
  
  uVar1 = mem_handle_lock(param_1);
  return uVar1;
}

/* 0046ab00 auto */
i32 __cdecl mem_unlock_handle(iptr param_1)

{
  i32 uVar1;
  
  uVar1 = mem_handle_unlock(param_1);
  return uVar1;
}

/* 00497ea0 auto */
bool __cdecl memblock_init(iptr param_1,i32 param_2,uint param_3)

{
  i32 uVar1;
  bool bVar2;
  
  if (*(int *)(param_1 + 4) != 0) {
    if (*(int *)(param_1 + 8) != 0) {
      mem_handle_unlock(*(i32 *)(param_1 + 4));
      *(i32 *)(param_1 + 8) = 0;
    }
    mem_handle_free(*(i32 *)(param_1 + 4));
    *(i32 *)(param_1 + 4) = 0;
  }
  *(i8 *)param_1 = (i8)param_2;
  uVar1 = mem_handle_alloc(param_3 & 0xffff);
  *(i32 *)(param_1 + 4) = uVar1;
  bVar2 = *(int *)(param_1 + 4) != 0;
  if (bVar2) {
    *(i8 *)(param_1 + 1) = 1;
    *(i16 *)(param_1 + 0xc) = 0;
    *(i16 *)(param_1 + 0x10) = (i16)param_3;
    *(i16 *)(param_1 + 0xe) = (i16)param_3;
    *(i32 *)(param_1 + 8) = 0;
  }
  else {
    *(i32 *)(param_1 + 4) = 0;
    error_report(0xfffffffe,param_2,0,param_3 & 0xffff,0);
  }
  return !bVar2;
}

/* 00497ff3 auto */
i32 __cdecl memblock_ensure_locked(iptr param_1)

{
  i32 uVar1;
  
  if (*(int *)(param_1 + 8) == 0) {
    uVar1 = mem_handle_lock(*(i32 *)(param_1 + 4));
    *(i32 *)(param_1 + 8) = uVar1;
    if (*(int *)(param_1 + 8) == 0) {
      error_report(0xfffffff6,(uint)*(byte *)param_1,0,0,0);
    }
  }
  return 0;
}

/* 0049805e auto */
void __cdecl memblock_detach(iptr param_1)

{
  *(i32 *)(param_1 + 8) = 0;
  *(i32 *)(param_1 + 4) = 0;
  return;
}

/* 004980a9 auto */
void __cdecl memblock_unlock(iptr param_1)

{
  if (*(int *)(param_1 + 8) != 0) {
    if (*(int *)(param_1 + 4) != 0) {
      mem_handle_unlock(*(i32 *)(param_1 + 4));
    }
    *(i32 *)(param_1 + 8) = 0;
  }
  return;
}

/* 004980ec auto */
iptr __cdecl memblock_free(iptr param_1)

{
  if (*(char *)(param_1 + 1) != '\0') {
    memblock_unlock(param_1);
    if (*(int *)(param_1 + 4) != 0) {
      mem_handle_free(*(i32 *)(param_1 + 4));
      *(i32 *)(param_1 + 4) = 0;
    }
  }
  *(i16 *)(param_1 + 0xc) = 0;
  *(i16 *)(param_1 + 0x10) = 0;
  *(i16 *)(param_1 + 0xe) = 0;
  return param_1;
}

/* 00498159 auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
int __cdecl memblock_alloc(iptr param_1,uint param_2)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  if ((uint)*(ushort *)(param_1 + 0x10) < (param_2 & 0xffff)) {
    error_report(0xfffffffd,(uint)*(byte *)param_1,0,param_2 & 0xffff,
                       (uint)*(ushort *)(param_1 + 0x10));
  }
  iVar1 = memblock_ensure_locked(param_1);
  if (iVar1 == 0) {
    local_8 = (uint)*(ushort *)(param_1 + 0xc) + *(int *)(param_1 + 8);
    *(short *)(param_1 + 0xc) = *(short *)(param_1 + 0xc) + (short)param_2;
    *(short *)(param_1 + 0x10) = *(short *)(param_1 + 0x10) - (short)param_2;
  }
  return local_8;
}
#undef local_8

/* 004b1396 auto */
#define local_28 (*(byte * *)(frame_ + FRAME_OFF(0)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_20 (*(ushort * *)(frame_ + FRAME_OFF(8)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(20)))
#define local_c (*(int * *)(frame_ + FRAME_OFF(28)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(32)))
int __cdecl mem_checksum(iptr param_1,uint param_2)

{
  uint uVar1;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_2 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = 0;
    uVar1 = (int)param_2 >> 0x1f;
    if (((param_2 ^ uVar1) - uVar1 & 3 ^ uVar1) == uVar1) {
      local_c = (int *)param_1;
      for (local_14 = 0; local_14 < (int)param_2 >> 2; local_14++) {
        local_8 += *local_c;
        local_c++;
      }
    }
    else if (((param_2 ^ uVar1) - uVar1 & 1 ^ uVar1) == uVar1) {
      local_20 = (ushort *)param_1;
      for (local_1c = 0; local_1c < (int)param_2 >> 2; local_1c++) {
        local_8 += (uint)*local_20;
        local_20++;
      }
    }
    else {
      local_28 = (byte *)param_1;
      for (local_24 = 0; local_24 < (int)param_2; local_24++) {
        local_8 += (uint)*local_28;
        local_28++;
      }
    }
  }
  return local_8;
}
#undef local_28
#undef local_24
#undef local_20
#undef local_1c
#undef local_14
#undef local_c
#undef local_8

/* 004bb870 auto */
#define error_last_alloc_failed (*(uint *)((u8 *)&g.d_00634814))
#define mem_last_alloc_size (*(i32 *)((u8 *)&g.d_00634818))
int __cdecl mem_handle_alloc_tracked(i32 param_1)

{
  int iVar1;
  
  mem_last_alloc_size = param_1;
  iVar1 = mem_handle_alloc(param_1);
  error_last_alloc_failed = (uint)(iVar1 == 0);
  return iVar1;
}
#undef error_last_alloc_failed
#undef mem_last_alloc_size

/* 004cca35 auto */
i32 __cdecl memblock_alloc_checked(iptr param_1,uint param_2)

{
  LPCSTR lpCaption;
  LPCSTR lpText;
  iptr iVar1;
  i32 uVar1;
  UINT uType;
  
  if ((uint)*(ushort *)(param_1 + 0x10) < (param_2 & 0xffff)) {
    uType = 0;
    lpCaption = (LPCSTR)label_string(*(i32 *)(label_string_ids + 0x8d0));
    lpText = (LPCSTR)label_string(*(i32 *)(label_string_ids + 0x8e8));
    iVar1 = wnd_get_window((WndBase *)(active_editor_wnd + 0x48));
    MessageBoxA(*(HWND *)(iVar1 + 4),lpText,lpCaption,uType);
    uVar1 = 0;
  }
  else {
    uVar1 = memblock_alloc(param_1,param_2);
  }
  return uVar1;
}

/* 00511350 auto */
int __cdecl int_clamp_c(int param_1,int param_2,int param_3)

{
  if ((param_1 <= param_3) && (param_3 = param_1, param_1 < param_2)) {
    param_3 = param_2;
  }
  return param_3;
}

/* 00554145 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define civ (*(uint *)(frame_ + FRAME_OFF(0)))
#define local_304 (*(Dialog *)(frame_ + FRAME_OFF(4)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(760)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(764)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(768)))
i32 __cdecl dbg_pick_player(int param_1)

{
  iptr iVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(776)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_304,0x4000);
  local_8 = 0;
  dialog_load_text(&local_304,ADDR(0x633710, ((u8 *)&g.d_00633710)),ADDR(0x633704, ((u8 *)&g.d_00633704)),1);
  for (civ = (uint)(param_1 == 0); (int)civ < 8; civ++) {
    if ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0) {
      text_clear();
      iVar1 = civ_get_adjective(civ);
      text_append(iVar1);
      dialog_add_option((DialogOptionList *)&local_304,ADDR(0x679640, ((u8 *)&g.d_00679640)),civ,0);
    }
  }
  dialog_set_default_choice((DialogOptionList *)&local_304,human_civ);
  uVar2 = dlg_show_modal(&local_304,0);
  local_8 = 0xffffffff;
  /* inlined unwind funclet 00554272 */ { dialog_dtor((Dialog *)((iptr)&local_304)); }
  return uVar2;
}
#undef human_civ
#undef civ
#undef local_304
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0055add0 auto */
i32 __stdcall win_main(i32 param_1,i32 param_2,i32 param_3,i32 param_4)

{
  DWORD DVar1;
  int iVar2;
  HWND hWnd;
  
  CreateMutexA((LPSECURITY_ATTRIBUTES)0x0,1,s_Civilization_II_Once_Only_00633a40);
  DVar1 = GetLastError();
  if (DVar1 == 0xb7) {
    hWnd = FindWindowA(s_MSWindowClass_00633a5c,(LPCSTR)0x0);
    if (hWnd != (HWND)0x0) {
      BringWindowToTop(hWnd);
    }
  }
  else {
    iVar2 = app_startup(param_1,param_2);
    if (iVar2 != 0) {
      game_main_entry();
      app_shutdown();
    }
  }
  return 0;
}

/* 00568176 auto */
i32 __cdecl mem_check_available(i32 param_1)

{
  return 1;
}

/* 00589d80 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
int __cdecl err_register_cleanup_fn(iptr param_1)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = fatal_cleanup_count;
  local_8 = -1;
  if (fatal_cleanup_count < 10) {
    local_8 = fatal_cleanup_count;
    fatal_cleanup_count++;
    *(iptr *)(&crash_handler_callbacks + iVar1 * 4) = param_1;
  }
  return local_8;
}
#undef local_8

/* 00589dc5 auto */
#define local_5c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_58 (*(char (*)[80])(frame_ + FRAME_OFF(8)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(88)))
void __cdecl err_dump_text_file(iptr param_1)

{
  FILE *_File;
  char *pcVar1;
  size_t sVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(96)] __attribute__((aligned(8)));  /* original stack frame */
  
  _File = (FILE *)file_open_path(param_1,ADDR(0x63481c, ((u8 *)&g.d_0063481c)));
  if (_File != (FILE *)0x0) {
    local_8 = 1;
    while (((local_8 != 0 && ((CRT_FEOF(_File)) == 0)) &&
           (pcVar1 = _fgets(local_58,0x4f,_File), pcVar1 != (char *)0x0))) {
      for (local_5c = 0; sVar2 = _strlen(local_58), local_5c < (int)sVar2; local_5c++)
      {
        if (local_58[local_5c] < ' ') {
          local_58[local_5c] = '\0';
        }
      }
      iVar3 = _strncmp(local_58,&err_comment_prefix_str,3);
      if (iVar3 == 0) {
        local_8 = 0;
      }
      else {
        _sprintf(&crash_debug_buffer,&err_dump_line_fmt,local_58);
        OutputDebugStringA(&crash_debug_buffer);
      }
    }
  }
  if (_File != (FILE *)0x0) {
    _fclose(_File);
  }
  return;
}
#undef local_5c
#undef local_58
#undef local_8

/* 00589ef8 auto */
#define local_bc (*(char (*)[12])(frame_ + FRAME_OFF(4)))
#define local_b0 (*(char (*)[80])(frame_ + FRAME_OFF(16)))
#define local_60 (*(char (*)[80])(frame_ + FRAME_OFF(96)))
#define local_10 (*(char (*)[12])(frame_ + FRAME_OFF(176)))
void __cdecl error_report(uint param_1,int param_2,iptr param_3,iptr param_4,iptr param_5)

{
  i8 frame_[FRAME_OFF(192)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_3 != 0) {
    crt_strcpy(&error_context_text,param_3);
  }
  __itoa(param_1,local_b0,10);
  __itoa(param_2,local_60,10);
  __ltoa(param_4,local_10,10);
  __ltoa(param_5,local_bc,10);
  file_read_nth_line((iptr)local_b0,ADDR(0x634828, ((u8 *)&g.d_00634828)),~param_1 + 1);
  file_read_nth_line((iptr)local_60,ADDR(0x634834, ((u8 *)&g.d_00634834)),param_2);
  err_fatal_exit((iptr)local_b0,(iptr)local_60,(iptr)local_10,(iptr)local_bc,param_1);
  return;
}
#undef local_bc
#undef local_b0
#undef local_60
#undef local_10

/* 0058a0ee auto */
#define error_last_alloc_failed (*(int *)((u8 *)&g.d_00634814))
#define error_last_open_failed (*(int *)((u8 *)&g.d_00634810))
#define mem_last_alloc_size (*(long *)((u8 *)&g.d_00634818))
#define local_108 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_104 (*(i8 (*)[256])(frame_ + FRAME_OFF(4)))
void __cdecl err_fatal_exit(iptr param_1,iptr param_2,iptr param_3,iptr param_4,i32 param_5)

{
  size_t sVar1;
  i8 frame_[FRAME_OFF(264)] __attribute__((aligned(8)));  /* original stack frame */
  
  crt_strcpy(local_104,s_Error___00634844);
  crt_strcat(local_104,param_1);
  crt_strcat(local_104,s___in_module___0063484c);
  crt_strcat(local_104,param_2);
  crt_strcat(local_104,s___data__0063485c);
  crt_strcat(local_104,param_3);
  crt_strcat(local_104,&err_data_sep_str);
  crt_strcat(local_104,param_4);
  _sprintf(&crash_debug_buffer,&err_fatal_msg_fmt,local_104);
  OutputDebugStringA(&crash_debug_buffer);
  dbg_log(ADDR(0x6acbf8, ((u8 *)&g.d_006acbf8)));
  sVar1 = _strlen(&error_context_text);
  if (sVar1 != 0) {
    _sprintf(&crash_debug_buffer,s___s__00634870,&error_context_text);
    OutputDebugStringA(&crash_debug_buffer);
    dbg_log(ADDR(0x6acbf8, ((u8 *)&g.d_006acbf8)));
  }
  if (error_last_alloc_failed != 0) {
    __ltoa(mem_last_alloc_size,(char *)param_3,10);
    crt_strcpy(local_104,s_Tried_to_allocate_00634878);
    crt_strcat(local_104,param_3);
    crt_strcat(local_104,s_bytes__0063488c);
    _sprintf(&crash_debug_buffer,&fatal_alloc_line_fmt,local_104);
    OutputDebugStringA(&crash_debug_buffer);
    dbg_log(ADDR(0x6acbf8, ((u8 *)&g.d_006acbf8)));
  }
  _sprintf(&crash_debug_buffer,&fatal_alloc_newline_str);
  OutputDebugStringA(&crash_debug_buffer);
  dbg_log(ADDR(0x6acbf8, ((u8 *)&g.d_006acbf8)));
  if (error_last_open_failed != 0) {
    _sprintf(&crash_debug_buffer,s_File_open_failed___s_0063489c,&error_last_open_path);
    OutputDebugStringA(&crash_debug_buffer);
    dbg_log(ADDR(0x6acbf8, ((u8 *)&g.d_006acbf8)));
  }
  crt_strcpy(local_104,s_Most_recent_DOS_error__006348b4);
  __itoa(crt_errno,(char *)param_3,10);
  crt_strcat(local_104,param_3);
  _sprintf(&crash_debug_buffer,&fatal_dos_error_line_fmt,local_104);
  OutputDebugStringA(&crash_debug_buffer);
  dbg_log(ADDR(0x6acbf8, ((u8 *)&g.d_006acbf8)));
  _sprintf(&crash_debug_buffer,&fatal_dos_error_newline_str);
  OutputDebugStringA(&crash_debug_buffer);
  dbg_log(ADDR(0x6acbf8, ((u8 *)&g.d_006acbf8)));
  err_dump_text_file(ADDR(0x6348d8, ((u8 *)&g.d_006348d8)));
  local_108 = fatal_cleanup_count;
  while (local_108 = local_108 - 1, -1 < local_108) {
    if (*(int *)(&crash_handler_callbacks + local_108 * 4) != 0) {
      (**(code **)(&crash_handler_callbacks + local_108 * 4))();
    }
  }
  DebugBreak();
                    /* WARNING: Subroutine does not return */
  _exit(3);
}
#undef error_last_alloc_failed
#undef error_last_open_failed
#undef mem_last_alloc_size
#undef local_108
#undef local_104

/* 0058ae20 auto */
i32 __cdecl
point_in_rect_ltrb(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  i32 uVar1;
  
  if ((((param_1 < param_3) || (param_5 < param_1)) || (param_2 < param_4)) || (param_6 < param_2))
  {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

/* 0059a6f0 auto */
#define rng_state (*(int *)((u8 *)&g.d_00635094))
int __cdecl rng_set_seed(int param_1)

{
  int iVar1;
  
  iVar1 = rng_state;
  if (param_1 == 0) {
    iVar1 = 0;
  }
  else {
    rng_state = param_1;
  }
  return iVar1;
}
#undef rng_state

/* 0059a733: written by hand in src/game/random.c */

/* 0059a791: written by hand in src/game/random.c */

/* 005a1a44 auto */
int __cdecl int_clamp_b(int param_1,int param_2,int param_3)

{
  if (param_2 <= param_1) {
    param_2 = param_1;
  }
  if (param_2 <= param_3) {
    param_3 = param_2;
  }
  return param_3;
}

/* 005adfa0 auto */
int __cdecl int_clamp(iptr param_1,iptr param_2,int param_3)

{
  if (param_2 <= param_1) {
    param_2 = param_1;
  }
  if (param_2 <= param_3) {
    param_3 = param_2;
  }
  return param_3;
}

/* 005adfd9 auto */
void __cdecl int_swap(iptr param_1,iptr param_2)

{
  i32 uVar1;
  
  uVar1 = *(i32 *)param_1;
  *(i32 *)param_1 = *(i32 *)param_2;
  *(i32 *)param_2 = uVar1;
  return;
}

/* 005ae0b0 auto */
int __cdecl coarse_wrap_x(int param_1)

{
  if ((game.rules & 0x8000) == 0) {
    if (param_1 < 0) {
      param_1 = map.quarter_w + param_1;
    }
    else if (map.quarter_w <= param_1) {
      param_1 -= map.quarter_w;
    }
  }
  return param_1;
}

/* 005ae296 auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
int __cdecl dist_from_deltas(uint param_1,uint param_2)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((int)param_1 < 1) {
    param_1 = ~param_1 + 1;
  }
  if ((int)param_2 < 1) {
    param_2 = ~param_2 + 1;
  }
  iVar1 = (int)(param_2 + param_1) >> 1;
  if ((int)param_2 < (int)param_1) {
    local_8 = param_1 - ((int)((iVar1 - param_2) + 1) >> 1);
  }
  else {
    local_8 = param_2 - ((int)((iVar1 - param_1) + 1) >> 1);
  }
  return local_8;
}
#undef local_8

/* 005ae3ec auto */
#define local_8 (*(i8 *)(frame_ + FRAME_OFF(0)))
int __cdecl int_shift_signed(int param_1,int param_2)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_2 != 0) {
    if (param_2 < 1) {
      local_8 = (byte)param_2;
      if (param_2 < 1) {
        local_8 = ~(byte)param_2 + 1;
      }
      param_1 = param_1 >> (local_8 & 0x1f);
    }
    else {
      param_1 = param_1 << ((byte)param_2 & 0x1f);
    }
  }
  return param_1;
}
#undef local_8

/* 005bb9c0 auto */
#define local_20 (*(tagMSG *)(frame_ + FRAME_OFF(0)))
void __cdecl win_drain_input_msgs(void)

{
  BOOL BVar1;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  do {
    BVar1 = PeekMessageA(&local_20,(HWND)0x0,0x200,0x209,1);
  } while (BVar1 != 0);
  do {
    BVar1 = PeekMessageA(&local_20,(HWND)0x0,0x100,0x108,1);
  } while (BVar1 != 0);
  return;
}
#undef local_20

/* 005bba4f auto */
#define avi_idle_update_enabled (*(int *)((u8 *)&g.d_00637efc))
#define local_20 (*(tagMSG *)(frame_ + FRAME_OFF(0)))
i32 __cdecl win_dispatch_one_message(void)

{
  BOOL BVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  BVar1 = PeekMessageA(&local_20,(HWND)0x0,0,0,1);
  if (BVar1 == 0) {
    win_flush_pending_msgs();
    if (avi_idle_update_enabled != 0) {
      avi_update_current_frame();
    }
    uVar2 = 0;
  }
  else {
    TranslateMessage(&local_20);
    DispatchMessageA(&local_20);
    uVar2 = 1;
  }
  return uVar2;
}
#undef avi_idle_update_enabled
#undef local_20

/* 005bbab8 auto */
#define local_20 (*(tagMSG *)(frame_ + FRAME_OFF(0)))
uint __cdecl win_dispatch_one_paint(void)

{
  BOOL BVar1;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  BVar1 = PeekMessageA(&local_20,(HWND)0x0,0xf,0xf,1);
  if (BVar1 != 0) {
    TranslateMessage(&local_20);
    DispatchMessageA(&local_20);
  }
  return (uint)(BVar1 != 0);
}
#undef local_20

/* 005bbb0a auto */
void __cdecl win_dispatch_all_messages(void)

{
  int iVar1;
  
  do {
    iVar1 = win_dispatch_one_message();
  } while (iVar1 != 0);
  GdiFlush();
  return;
}

/* 005bbb32 auto */
void __cdecl win_dispatch_all_paints(void)

{
  int iVar1;
  
  do {
    iVar1 = win_dispatch_one_paint();
  } while (iVar1 != 0);
  GdiFlush();
  return;
}

/* 005bbb76 auto */
#define local_20 (*(tagMSG *)(frame_ + FRAME_OFF(0)))
uint __cdecl win_dispatch_one_custom_msg(void)

{
  BOOL BVar1;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  BVar1 = PeekMessageA(&local_20,(HWND)0x0,0x3bd,0x3bd,1);
  if (BVar1 != 0) {
    TranslateMessage(&local_20);
    DispatchMessageA(&local_20);
  }
  return (uint)(BVar1 != 0);
}
#undef local_20

/* 005bbbce auto */
#define avi_idle_update_enabled (*(int *)((u8 *)&g.d_00637efc))
void __cdecl win_dispatch_custom_msgs(void)

{
  int iVar1;
  
  do {
    iVar1 = win_dispatch_one_custom_msg();
  } while (iVar1 != 0);
  if (avi_idle_update_enabled != 0) {
    avi_update_current_frame();
  }
  return;
}
#undef avi_idle_update_enabled

/* 005c54d0 auto */
i32 __cdecl endian_from_le(i32 param_1)

{
  return param_1;
}

/* 005d21f0 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl dbg_log_file_global_init(void)

{
  dbg_log_file_static_init();
  dbg_log_file_reg_atexit();
  return;
}

/* 005d220a auto */
void __cdecl dbg_log_file_static_init(void)

{
  dbg_log_file_ctor(&dbg_log_file);
  return;
}

/* 005d2224 auto */
void __cdecl dbg_log_file_reg_atexit(void)

{
  _atexit(dbg_log_file_atexit_dtor);
  return;
}

/* 005d2241 auto */
void __cdecl dbg_log_file_atexit_dtor(void)

{
  dbg_log_file_dtor(&dbg_log_file);
  return;
}

/* 005d225b auto */
i8 __cdecl dbg_log(iptr param_1)

{
  i8 uVar1;
  
  uVar1 = dbg_log_write(&dbg_log_file,param_1);
  return uVar1;
}

/* 005d2279 auto */
#define local_404 (*(char (*)[1024])(frame_ + FRAME_OFF(4)))
i8 __cdecl dbg_logf(iptr param_1,iptr param_2)

{
  i8 uVar1;
  i8 frame_[FRAME_OFF(1032)] __attribute__((aligned(8)));  /* original stack frame */
  
  _sprintf(local_404,(char *)param_1,param_2);
  uVar1 = dbg_log_write(&dbg_log_file,(iptr)local_404);
  return uVar1;
}
#undef local_404

/* 005d22b7 auto */
#define local_404 (*(char (*)[1024])(frame_ + FRAME_OFF(4)))
i8 __cdecl dbg_logf_int2(iptr param_1,i32 param_2,i32 param_3)

{
  i8 uVar1;
  i8 frame_[FRAME_OFF(1032)] __attribute__((aligned(8)));  /* original stack frame */
  
  _sprintf(local_404,(char *)param_1,param_2,param_3);
  uVar1 = dbg_log_write(&dbg_log_file,(iptr)local_404);
  return uVar1;
}
#undef local_404

/* 005d22f9 auto */
#define local_404 (*(char (*)[1024])(frame_ + FRAME_OFF(4)))
void __cdecl dbg_logf3(iptr param_1,iptr param_2,i32 param_3,i32 param_4)

{
  i8 frame_[FRAME_OFF(1032)] __attribute__((aligned(8)));  /* original stack frame */
  
  _sprintf(local_404,(char *)param_1,param_2,param_3,param_4);
  dbg_log_write(&dbg_log_file,(iptr)local_404);
  return;
}
#undef local_404

/* 005d233f auto */
#define local_404 (*(char (*)[1024])(frame_ + FRAME_OFF(4)))
void __cdecl dbg_logf_noret(iptr param_1,i32 param_2)

{
  i8 frame_[FRAME_OFF(1032)] __attribute__((aligned(8)));  /* original stack frame */
  
  _sprintf(local_404,(char *)param_1,param_2);
  dbg_log_write(&dbg_log_file,(iptr)local_404);
  return;
}
#undef local_404

/* 005d237d auto */
#define local_404 (*(char (*)[1024])(frame_ + FRAME_OFF(4)))
i8 __cdecl dbg_logf_str(iptr param_1,iptr param_2)

{
  i8 uVar1;
  i8 frame_[FRAME_OFF(1032)] __attribute__((aligned(8)));  /* original stack frame */
  
  _sprintf(local_404,(char *)param_1,param_2);
  uVar1 = dbg_log_write(&dbg_log_file,(iptr)local_404);
  return uVar1;
}
#undef local_404

/* 005d23bb auto */
#define local_404 (*(char (*)[1024])(frame_ + FRAME_OFF(4)))
void __cdecl dbg_logf_str_int(iptr param_1,iptr param_2,iptr param_3)

{
  i8 frame_[FRAME_OFF(1032)] __attribute__((aligned(8)));  /* original stack frame */
  
  _sprintf(local_404,(char *)param_1,param_2,param_3);
  dbg_log_write(&dbg_log_file,(iptr)local_404);
  return;
}
#undef local_404

/* 005d246f auto */
void * __thiscall dbg_log_file_ctor(void *this)

{
  DWORD DVar1;
  
  dbg_log_open();
  DVar1 = GetTickCount();
  *(DWORD *)this = DVar1;
  return this;
}

/* 005d2498 auto */
void __thiscall dbg_log_file_dtor(void *this)

{
  dbg_log_close();
  return;
}

/* 005d24b3 auto */
#define dbg_log_to_debugger (*(char *)((u8 *)&g.d_00638308))
#define dbg_log_to_file (*(char *)((u8 *)&g.d_00638304))
#define local_40c (*(char (*)[1032])(frame_ + FRAME_OFF(4)))
i8 __thiscall dbg_log_write(void *this,iptr param_1)

{
  DWORD DVar1;
  i8 frame_[FRAME_OFF(1040)] __attribute__((aligned(8)));  /* original stack frame */
  
  DVar1 = GetTickCount();
  _sprintf(local_40c,s___5d__0063830c,(DVar1 - *(int *)this) / 1000);
  crt_strcat(local_40c,param_1);
  if (dbg_log_to_debugger != '\0') {
    dbg_log_write_debugger((iptr)local_40c);
  }
  if (dbg_log_to_file != '\0') {
    dbg_log_write_file((iptr)local_40c);
  }
  return 1;
}
#undef dbg_log_to_debugger
#undef dbg_log_to_file
#undef local_40c

/* 005dae00 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl err_report_ctx_global_init(void)

{
  err_report_ctx_static_init();
  err_report_ctx_reg_atexit();
  return;
}

/* 005dae1a auto */
void __cdecl err_report_ctx_static_init(void)

{
  err_ctx_ctor((ErrorContext *)&err_report_ctx);
  return;
}

/* 005dae34 auto */
void __cdecl err_report_ctx_reg_atexit(void)

{
  _atexit(err_report_ctx_atexit_dtor);
  return;
}

/* 005dae51 auto */
void __cdecl err_report_ctx_atexit_dtor(void)

{
  err_ctx_dtor((ErrorContext *)&err_report_ctx);
  return;
}

/* 005dae6b auto */
void __thiscall
err_report
          (ErrorContext *this,i32 param_1,iptr param_2,iptr param_3,i32 param_4)

{
  i32 uVar1;
  
  err_set_code(this,param_1);
  uVar1 = err_format_message(this,ADDR(0x638778, ((u8 *)&g.d_00638778)),param_2,param_3,param_4);
  err_show_fatal_box(this,uVar1);
  return;
}

/* 005daef7 auto */
ErrorContext * __thiscall
err_format_message
          (ErrorContext *this,iptr param_1,i32 param_2,i32 param_3,i32 param_4)

{
  size_t sVar1;
  i32 uVar2;
  char *_Format;
  
  crt_strcpy(this,&err_format_empty_str);
  _Format = s_Error___s_File___s_Line___d_00638790;
  sVar1 = _strlen((char *)this);
  _sprintf((char *)(this->pad_0 + sVar1),_Format,param_2,param_3,param_4);
  uVar2 = err_get_stack_trace(this);
  crt_strcat(this,uVar2);
  return this;
}

/* 005daf63 auto */
u8 * __thiscall err_get_stack_trace(ErrorContext *this)

{
  dbg_stack_trace_stub((iptr)(this->pad_0 + 0x400));
  return this->pad_0 + 0x400;
}

/* 005daf92 auto */
void __thiscall err_show_fatal_box(ErrorContext *this,i32 param_1)

{
  dbg_fatal_msgbox_break(ADDR(0x6387b4, ((u8 *)&g.d_006387b4)),param_1);
  return;
}

/* 005dafdf auto */
void __thiscall err_set_code(ErrorContext *this,u32 param_1)

{
  this->field_704 = param_1;
  this->field_700 = this->field_700 | 1 << ((byte)param_1 & 0x1f);
  return;
}

/* 005db035 auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall err_ctx_set_field_708(ErrorContext *this,i32 param_1)

{
  *(i32 *)this[1].pad_0 = param_1;
  return;
}

/* 005db059 auto */
void __thiscall err_ctx_clear_codes(ErrorContext *this)

{
  this->field_700 = 0;
  this->field_704 = 0;
  return;
}

/* 005db089 auto */
ErrorContext * __thiscall err_ctx_ctor(ErrorContext *this)

{
  err_ctx_set_field_708(this,0);
  err_ctx_clear_codes(this);
  return this;
}

/* 005db0b4 auto */
/* Library Function - Single Match
    public: __thiscall Iostream_init::~Iostream_init(void)
   
   Library: Visual Studio 1998 Debug */

void __thiscall err_ctx_dtor(void *this)

{
  return;
}

/* 005dcb8c auto */
void __cdecl mem_copy_src_dst(iptr param_1,iptr param_2,i32 param_3)

{
  mem_move_src_dst(param_1,param_2,param_3);
  return;
}

/* 005dcd70 auto */
void __cdecl mem_handle_clone(iptr param_1)

{
  SIZE_T SVar1;
  HGLOBAL hMem;
  LPVOID pvVar2;
  LPVOID pvVar3;
  
  SVar1 = GlobalSize(*(HGLOBAL *)param_1);
  hMem = (HGLOBAL)mem_handle_alloc(SVar1);
  if (hMem != (HGLOBAL)0x0) {
    pvVar2 = GlobalLock(hMem);
    pvVar3 = GlobalLock(*(HGLOBAL *)param_1);
    crt_memmove(pvVar2,pvVar3,SVar1);
    GlobalUnlock(hMem);
    GlobalUnlock(*(HGLOBAL *)param_1);
    *(HGLOBAL *)param_1 = hMem;
  }
  return;
}

/* 005dcdf9 auto */
LPVOID __cdecl mem_handle_lock(HGLOBAL param_1)

{
  LPVOID pvVar1;
  
  if (param_1 == (HGLOBAL)0x0) {
    pvVar1 = (LPVOID)0x0;
  }
  else {
    pvVar1 = GlobalLock(param_1);
  }
  return pvVar1;
}

/* 005dce29 auto */
i32 __cdecl mem_handle_unlock(HGLOBAL param_1)

{
  if (param_1 != (HGLOBAL)0x0) {
    GlobalUnlock(param_1);
  }
  return 0;
}

/* 005dce4f auto */
HGLOBAL __cdecl mem_handle_alloc(SIZE_T param_1)

{
  HGLOBAL pvVar1;
  
  pvVar1 = GlobalAlloc(0x42,param_1);
  if (pvVar1 == (HGLOBAL)0x0) {
    err_report((ErrorContext *)&err_report_ctx,1,ADDR(0x638980, ((u8 *)&g.d_00638980)),ADDR(0x638968, ((u8 *)&g.d_00638968)),0x4c);
  }
  return pvVar1;
}

/* 005dce96 auto */
HGLOBAL __cdecl mem_handle_free(HGLOBAL param_1)

{
  HGLOBAL pvVar1;
  
  if (param_1 == (HGLOBAL)0x0) {
    dbg_log(ADDR(0x638994, ((u8 *)&g.d_00638994)));
    pvVar1 = (HGLOBAL)0x0;
  }
  else {
    pvVar1 = GlobalFree(param_1);
  }
  return pvVar1;
}

/* 005dced3 auto */
void __cdecl mem_move_src_dst(iptr param_1,iptr param_2,i32 param_3)

{
  crt_memmove(param_2,param_1,param_3);
  return;
}

/* 005dcef7 auto */
SIZE_T __cdecl mem_handle_size(HGLOBAL param_1)

{
  SIZE_T SVar1;
  
  SVar1 = GlobalSize(param_1);
  return SVar1;
}

/* 005dfb61 auto */
#define local_30 (*(byte * *)(frame_ + FRAME_OFF(0)))
#define local_2c (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_1c (*(byte * *)(frame_ + FRAME_OFF(20)))
#define local_18 (*(byte * *)(frame_ + FRAME_OFF(24)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(28)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(40)))
iptr __cdecl mem_rle_decompress(iptr param_1)

{
  byte bVar1;
  size_t sVar2;
  byte *pbVar3;
  iptr iVar4;
  int iVar5;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  sVar2 = __msize(*(void **)param_1);
  pbVar3 = operator_new(sVar2);
  if (pbVar3 == (byte *)0x0) {
    dbg_log(ADDR(0x638c78, ((u8 *)&g.d_00638c78)));
    local_8 = 0;
  }
  else {
    mem_move_src_dst(*(iptr *)param_1,(iptr)pbVar3,sVar2);
    local_14 = sVar2 * 2;
    local_18 = (byte *)crt_realloc(*(i32 *)param_1,local_14);
    if (local_18 == (byte *)0x0) {
      dbg_log(ADDR(0x638cac, ((u8 *)&g.d_00638cac)));
      local_8 = 0;
    }
    else {
      *(byte **)param_1 = local_18;
      local_30 = local_18 + local_14;
      local_8 = 0;
      local_1c = pbVar3;
      while (local_1c < pbVar3 + (sVar2 - 1)) {
        local_2c = (uint)*local_1c;
        if (local_30 < local_18 + (local_2c & 0x7f) + 1) {
          local_14 += 1000;
          iVar4 = crt_realloc(*(i32 *)param_1,local_14);
          if (iVar4 == 0) {
            dbg_log(ADDR(0x638ce0, ((u8 *)&g.d_00638ce0)));
            return 0;
          }
          *(iptr *)param_1 = iVar4;
          local_18 = (byte *)(local_8 + iVar4);
          local_30 = (byte *)(local_14 + iVar4);
        }
        if (local_2c < 0x80) {
          bVar1 = local_1c[1];
          local_1c += 2;
          while (local_2c != 0) {
            *local_18 = bVar1;
            local_18++;
            local_8++;
            local_2c--;
          }
        }
        else {
          local_2c -= 0x80;
          local_1c++;
          while (local_2c != 0) {
            *local_18 = *local_1c;
            local_1c++;
            local_18++;
            local_8++;
            local_2c--;
          }
        }
      }
      iVar5 = crt_realloc(*(i32 *)param_1,local_8);
      if (iVar5 == 0) {
        dbg_log(ADDR(0x638d14, ((u8 *)&g.d_00638d14)));
        local_8 = 0;
      }
      else {
        *(int *)param_1 = iVar5;
        operator_delete(pbVar3);
      }
    }
  }
  return local_8;
}
#undef local_30
#undef local_2c
#undef local_1c
#undef local_18
#undef local_14
#undef local_8

/* 005dfd8f auto */
#define local_24 (*(char * *)(frame_ + FRAME_OFF(4)))
#define local_1c (*(char * *)(frame_ + FRAME_OFF(12)))
#define local_14 (*(char * *)(frame_ + FRAME_OFF(20)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_c (*(int *)(frame_ + FRAME_OFF(28)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(32)))
uint __cdecl mem_rle_compress(iptr param_1,int param_2)

{
  char *pcVar1;
  char *pcVar2;
  uint uVar3;
  char *pcVar4;
  void *pvVar5;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  pcVar2 = operator_new(param_2 + ((int)(param_2 + (param_2 >> 0x1f & 0x7fU)) >> 7) + 5);
  if (pcVar2 == (char *)0x0) {
    dbg_log(ADDR(0x638d48, ((u8 *)&g.d_00638d48)));
    uVar3 = 0xffffffff;
  }
  else {
    local_1c = *(char **)param_1;
    local_24 = local_1c + 1;
    pcVar4 = local_1c + param_2;
    local_8 = 0;
    local_14 = pcVar2;
    while (local_1c < pcVar4) {
      for (; (local_24 < pcVar4 && (*local_24 == *local_1c)); local_24++) {
      }
      local_c = (int)local_24 - (int)local_1c;
      if (2 < local_c) {
        while (pcVar1 = local_14, local_c != 0) {
          if (local_c < 0x80) {
            *local_14 = (char)local_c;
            if (param_2 <= local_8 + 1) goto LAB_005e0071;
            local_c = 0;
          }
          else {
            *local_14 = 127;
            if (param_2 <= local_8 + 1) goto LAB_005e0071;
            local_c -= 0x7f;
          }
          local_14++;
          *local_14 = *local_1c;
          local_14 = pcVar1 + 2;
          local_8 += 2;
          if (param_2 <= local_8) goto LAB_005e0071;
        }
        local_1c = local_24;
      }
      for (; (local_24 < pcVar4 && (local_24[1] != *local_24)); local_24++) {
      }
      local_c = (int)local_24 - (int)local_1c;
      while (local_c != 0) {
        if (local_c < 0x80) {
          *local_14 = (char)local_c - 0x80;
          local_14++;
          local_8++;
          if (param_2 <= local_8) goto LAB_005e0071;
          local_10 = local_c;
          local_c = 0;
        }
        else {
          *local_14 = -1;
          local_14++;
          local_8++;
          if (param_2 <= local_8) goto LAB_005e0071;
          local_c -= 0x7f;
          local_10 = 0x7f;
        }
        while (local_10 != 0) {
          *local_14 = *local_1c;
          local_1c++;
          local_14++;
          local_8++;
          local_10--;
          if (param_2 <= local_8) goto LAB_005e0071;
        }
      }
    }
    uVar3 = (int)local_14 - (int)pcVar2;
    if (param_2 < (int)uVar3) {
LAB_005e0071:
      operator_delete(pcVar2);
      uVar3 = 0xffffffff;
    }
    else {
      operator_delete(*(void **)param_1);
      pvVar5 = operator_new(uVar3);
      *(void **)param_1 = pvVar5;
      mem_move_src_dst((iptr)pcVar2,*(iptr *)param_1,uVar3);
      operator_delete(pcVar2);
    }
  }
  return uVar3;
}
#undef local_24
#undef local_1c
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 005ed920 auto */
#define local_42c (*(char (*)[32])(frame_ + FRAME_OFF(4)))
#define local_40c (*(char (*)[1024])(frame_ + FRAME_OFF(36)))
#define local_c (*(HANDLE *)(frame_ + FRAME_OFF(1060)))
#define local_8 (*(DWORD *)(frame_ + FRAME_OFF(1064)))
i32 __cdecl dbg_log_open(void)

{
  size_t nNumberOfBytesToWrite;
  DWORD *lpNumberOfBytesWritten;
  LPOVERLAPPED lpOverlapped;
  i8 frame_[FRAME_OFF(1072)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = (HANDLE)0x0;
  local_c = CreateFileA(s_smeds_log_00639bec,0xc0000000,0,(LPSECURITY_ATTRIBUTES)0x0,2,0x80,
                        (HANDLE)0x0);
  if (local_c != (HANDLE)0xffffffff) {
    smeds_log_enabled = 1;
  }
  crt_strcpy(local_40c,s______________________SMEDS_LOG___00639bf8);
  crt_strcat(local_40c,s_File_Output_to__00639c30);
  crt_strcat(local_40c,s_smeds_log_00639c44);
  crt_strcat(local_40c,&dbg_log_header_crlf);
  crt_strcat(local_40c,s_SMEDS32_Version__00639c54);
  _sprintf(local_42c,s__d__d__d_00639c68,2,0,0);
  crt_strcat(local_40c,local_42c);
  crt_strcat(local_40c,&dbg_log_header_blank_lines);
  if (smeds_log_enabled != '\0') {
    lpOverlapped = (LPOVERLAPPED)0x0;
    lpNumberOfBytesWritten = &local_8;
    nNumberOfBytesToWrite = _strlen(local_40c);
    WriteFile(local_c,local_40c,nNumberOfBytesToWrite,lpNumberOfBytesWritten,lpOverlapped);
    CloseHandle(local_c);
  }
  OutputDebugStringA(local_40c);
  return 1;
}
#undef local_42c
#undef local_40c
#undef local_c
#undef local_8

/* 005eda65 auto */
#define local_40c (*(char (*)[1024])(frame_ + FRAME_OFF(4)))
#define local_c (*(HANDLE *)(frame_ + FRAME_OFF(1028)))
#define local_8 (*(DWORD *)(frame_ + FRAME_OFF(1032)))
i32 __cdecl dbg_log_close(void)

{
  size_t nNumberOfBytesToWrite;
  DWORD *lpNumberOfBytesWritten;
  LPOVERLAPPED lpOverlapped;
  i8 frame_[FRAME_OFF(1040)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = (HANDLE)0x0;
  if (smeds_log_enabled != '\0') {
    local_c = CreateFileA(s_smeds_log_00639c84,0xc0000000,0,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,
                          (HANDLE)0x0);
    SetFilePointer(local_c,0,(PLONG)0x0,2);
    crt_strcpy(local_40c,s______________________LOG_CLOSED___00639c90);
    lpOverlapped = (LPOVERLAPPED)0x0;
    lpNumberOfBytesWritten = &local_8;
    nNumberOfBytesToWrite = _strlen(local_40c);
    WriteFile(local_c,local_40c,nNumberOfBytesToWrite,lpNumberOfBytesWritten,lpOverlapped);
    CloseHandle(local_c);
    OutputDebugStringA(local_40c);
  }
  return 1;
}
#undef local_40c
#undef local_c
#undef local_8

/* 005edb15 auto */
#define local_8 (*(DWORD *)(frame_ + FRAME_OFF(0)))
i32 __cdecl dbg_log_write_file(iptr param_1)

{
  HANDLE hFile;
  size_t nNumberOfBytesToWrite;
  DWORD *lpNumberOfBytesWritten;
  LPOVERLAPPED lpOverlapped;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (smeds_log_enabled != '\0') {
    hFile = CreateFileA(s_smeds_log_00639ccc,0xc0000000,0,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,
                        (HANDLE)0x0);
    SetFilePointer(hFile,0,(PLONG)0x0,2);
    lpOverlapped = (LPOVERLAPPED)0x0;
    lpNumberOfBytesWritten = &local_8;
    nNumberOfBytesToWrite = _strlen((char *)param_1);
    WriteFile(hFile,(LPCVOID)param_1,nNumberOfBytesToWrite,lpNumberOfBytesWritten,lpOverlapped);
    WriteFile(hFile,&dbg_log_file_crlf,2,&local_8,(LPOVERLAPPED)0x0);
    CloseHandle(hFile);
  }
  return 1;
}
#undef local_8

/* 005edbb2 auto */
i32 __cdecl dbg_log_write_debugger(iptr param_1)

{
  OutputDebugStringA((LPCSTR)param_1);
  OutputDebugStringA(&dbg_log_debugger_crlf);
  return 1;
}

/* 005edc6c: written by hand in src/game/regargs.c */

/* 005edcac: written by hand in src/game/regargs.c */

/* 005edd00 auto */
void __cdecl dbg_fatal_msgbox_break(iptr param_1,LPCSTR param_2)

{
  MessageBoxA((HWND)0x0,param_2,(LPCSTR)param_1,0x2030);
  DebugBreak();
  return;
}

/* 005eddaa auto */
void __cdecl dbg_stack_trace_stub(iptr param_1)

{
  _sprintf((char *)param_1,s_Stack_trace_not_yet_available_in_00639ce4);
  return;
}

/* 005eeeb0 auto */
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define local_c (*(uint *)(frame_ + FRAME_OFF(4)))
i32 __cdecl sys_msgbox_potentially_fatal(LPCSTR param_1,i32 param_2,i32 param_3)

{
  int iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 0;
  switch(param_2) {
  case 0:
    local_c = 0x40;
    break;
  case 1:
    local_c = 0x20;
    break;
  case 2:
    local_c = 0x30;
    break;
  case 3:
    local_c = 0x10;
  }
  switch(param_3) {
  case 1:
    break;
  case 2:
    local_c = local_c | 1;
    break;
  case 4:
    local_c = local_c | 4;
    break;
  case 8:
    local_c = local_c | 3;
    break;
  case 0x10:
    local_c = local_c | 2;
    break;
  case 0x20:
    local_c = local_c | 5;
  }
  iVar1 = MessageBoxA((HWND)0x0,param_1,s_Potentially_fatal_error_00639d5c,local_c | 0x2000);
  switch(iVar1) {
  case 1:
    local_10 = 0;
    break;
  case 2:
    local_10 = 1;
    break;
  case 3:
    local_10 = 4;
    break;
  case 4:
    local_10 = 5;
    break;
  case 5:
    local_10 = 6;
    break;
  case 6:
    local_10 = 2;
    break;
  case 7:
    local_10 = 3;
  }
  return local_10;
}
#undef local_10
#undef local_c

/* 005ef0b9 auto */
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define local_c (*(uint *)(frame_ + FRAME_OFF(4)))
i32 __cdecl sys_msgbox_mapped(LPCSTR param_1,LPCSTR param_2,i32 param_3,i32 param_4)

{
  int iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 0;
  switch(param_3) {
  case 0:
    local_c = 0x40;
    break;
  case 1:
    local_c = 0x20;
    break;
  case 2:
    local_c = 0x30;
    break;
  case 3:
    local_c = 0x10;
  }
  switch(param_4) {
  case 1:
    break;
  case 2:
    local_c = local_c | 1;
    break;
  case 4:
    local_c = local_c | 4;
    break;
  case 8:
    local_c = local_c | 3;
    break;
  case 0x10:
    local_c = local_c | 2;
    break;
  case 0x20:
    local_c = local_c | 5;
  }
  iVar1 = MessageBoxA((HWND)0x0,param_2,param_1,local_c | 0x2000);
  switch(iVar1) {
  case 1:
    local_10 = 0;
    break;
  case 2:
    local_10 = 1;
    break;
  case 3:
    local_10 = 4;
    break;
  case 4:
    local_10 = 5;
    break;
  case 5:
    local_10 = 6;
    break;
  case 6:
    local_10 = 2;
    break;
  case 7:
    local_10 = 3;
  }
  return local_10;
}
#undef local_10
#undef local_c

/* 005ef58e: written by hand in src/game/regargs.c */

/* 005f04c0 auto */
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
void __thiscall ptrlist_dtor(void *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  /* inlined unwind funclet 005f04fe */ { ptrlist_clear(*(PtrList **)((iptr)&this)); }
  return;
}
#undef uStack_10
#undef puStack_c
#undef local_8

/* 005f0590 auto */
i32 __thiscall ptrlist_first(PtrList *this)

{
  i32 uVar1;
  
  uVar1 = ptrlist_first_impl(this);
  return uVar1;
}

/* 005f05d0 auto */
i32 __thiscall ptrlist_next(PtrList *this)

{
  i32 uVar1;
  
  uVar1 = ptrlist_next_impl(this);
  return uVar1;
}

/* 005f0676 auto */
/* Library Function - Single Match
    public: __thiscall CDataBoundProperty::~CDataBoundProperty(void)
   
   Library: Visual Studio 1998 Debug */

void __thiscall ptrlist_node_dtor(void *this)

{
  return;
}

/* 005f068c auto */
void __thiscall ptrlist_node_set_next(PtrListNodeNextSetView *this,iptr param_1)

{
  this->next_node = param_1;
  return;
}

/* 005f06ad auto */
void __thiscall ptrlist_node_set_prev(PtrListNodePrevSetView *this,iptr param_1)

{
  this->prev_node = param_1;
  return;
}

/* 005f0724 auto */
void __thiscall ptrlist_clear(PtrList *this)

{
  ptrlist_clear_impl(this);
  return;
}

/* 005f0742 auto */
uint __thiscall ptrlist_is_empty(PtrList *this)

{
  return (uint)(this->head == 0);
}

/* 005f0770 auto */
i32 __thiscall ptrlist_first_impl(PtrList *this)

{
  i32 uVar1;
  
  if (this->head == 0) {
    uVar1 = 0;
  }
  else {
    this->iter_node = this->head;
    uVar1 = ptrlist_node_data((PtrListNodeDataView *)this->head);
  }
  return uVar1;
}

/* 005f0833 auto */
i32 __thiscall ptrlist_next_impl(PtrList *this)

{
  uptr uVar1;
  i32 uVar2;
  
  if (this->iter_node == 0) {
    uVar2 = 0;
  }
  else {
    uVar1 = ptrlist_node_next((PtrListNodeNextView *)this->iter_node);
    this->iter_node = uVar1;
    if (this->iter_node == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = ptrlist_node_data((PtrListNodeDataView *)this->iter_node);
    }
  }
  return uVar2;
}

/* 005f0c69 auto */
void __thiscall ptrlist_remove_current(PtrList *this)

{
  int iVar1;
  PtrListNodeNextSetView *this_00;
  PtrListNodePrevSetView *this_01;
  
  if ((this->iter_node != 0) && (iVar1 = ptrlist_is_empty(this), iVar1 == 0)) {
    this_00 = (PtrListNodeNextSetView *)ptrlist_node_prev((PtrListNodePrevView *)this->iter_node);
    this_01 = (PtrListNodePrevSetView *)ptrlist_node_next((PtrListNodeNextView *)this->iter_node);
    if ((this_00 == (PtrListNodeNextSetView *)0x0) && (this_01 == (PtrListNodePrevSetView *)0x0)) {
      if ((void *)this->iter_node != (void *)0x0) {
        ptrlist_node_delete((void *)this->iter_node,1);
      }
      this->head = 0;
      this->tail = 0;
      this->iter_node = 0;
    }
    else if (this_00 == (PtrListNodeNextSetView *)0x0) {
      this->head = (uptr)this_01;
      ptrlist_node_set_prev((PtrListNodePrevSetView *)this->head,0);
      if ((void *)this->iter_node != (void *)0x0) {
        ptrlist_node_delete((void *)this->iter_node,1);
      }
      this->iter_node = this->head;
    }
    else if (this_01 == (PtrListNodePrevSetView *)0x0) {
      this->tail = (uptr)this_00;
      ptrlist_node_set_next((PtrListNodeNextSetView *)this->tail,0);
      if ((void *)this->iter_node != (void *)0x0) {
        ptrlist_node_delete((void *)this->iter_node,1);
      }
      this->iter_node = this->tail;
    }
    else {
      ptrlist_node_set_next(this_00,(iptr)this_01);
      ptrlist_node_set_prev(this_01,(iptr)this_00);
      if ((void *)this->iter_node != (void *)0x0) {
        ptrlist_node_delete((void *)this->iter_node,1);
      }
      this->iter_node = (uptr)this_01;
    }
  }
  return;
}

/* 005f0e13 auto */
void __thiscall ptrlist_clear_impl(PtrList *this)

{
  ptrlist_first_impl(this);
  while (this->iter_node != 0) {
    ptrlist_remove_current(this);
  }
  return;
}

/* 005f0e50 auto */
u32 __thiscall ptrlist_node_data(PtrListNodeDataView *this)

{
  return this->node_data;
}

/* 005f0e70 auto */
u32 __thiscall ptrlist_node_next(PtrListNodeNextView *this)

{
  return this->next_node;
}

/* 005f0e90 auto */
u32 __thiscall ptrlist_node_prev(PtrListNodePrevView *this)

{
  return this->prev_node;
}

/* 005f0eb0 auto */
/* Library Function - Single Match
    public: void * __thiscall CDataBoundProperty::`scalar deleting destructor'(unsigned int)
   
   Library: Visual Studio 1998 Debug */

void * __thiscall ptrlist_node_delete(void *this,uint param_1)

{
  ptrlist_node_dtor(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
