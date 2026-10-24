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
void __cdecl int_pairs_bubble_sort(int count,iptr values,iptr keys)

{
  i32 tmp;
  bool swapped;
  int i;
  
  do {
    swapped = false;
    for (i = 0; (!swapped && (i < count - 1)); i++) {
      if (*(int *)(keys + 4 + i * 4) < *(int *)(keys + i * 4)) {
        tmp = *(i32 *)(keys + i * 4);
        *(i32 *)(keys + i * 4) = *(i32 *)(keys + 4 + i * 4);
        *(i32 *)(keys + 4 + i * 4) = tmp;
        tmp = *(i32 *)(values + i * 4);
        *(i32 *)(values + i * 4) = *(i32 *)(values + 4 + i * 4);
        *(i32 *)(values + 4 + i * 4) = tmp;
        swapped = true;
      }
    }
  } while (swapped);
  return;
}

/* 00428cb0 auto */
MemBlock * __thiscall memblock_ctor(MemBlock *self)

{
  self->mem_handle = 0;
  self->base_ptr = 0;
  self->capacity = 0;
  return self;
}

/* 0046aaa0 auto */
i32 __cdecl mem_free_handle(iptr handle)

{
  i32 result;
  
  result = mem_handle_free(handle);
  return result;
}

/* 0046aad0 auto */
i32 __cdecl mem_lock_handle(iptr handle)

{
  i32 ptr;
  
  ptr = (i32)mem_handle_lock(handle);
  return ptr;
}

/* 0046ab00 auto */
i32 __cdecl mem_unlock_handle(iptr handle)

{
  i32 result;
  
  result = mem_handle_unlock(handle);
  return result;
}

/* 00497ea0 auto */
bool __cdecl memblock_init(iptr block,i32 block_id,uint size)

{
  i32 handle;
  bool ok;
  
  if (*(int *)(block + 4) != 0) {
    if (*(int *)(block + 8) != 0) {
      mem_handle_unlock(*(i32 *)(block + 4));
      *(i32 *)(block + 8) = 0;
    }
    mem_handle_free(*(i32 *)(block + 4));
    *(i32 *)(block + 4) = 0;
  }
  *(i8 *)block = (i8)block_id;
  handle = mem_handle_alloc(size & 0xffff);
  *(i32 *)(block + 4) = handle;
  ok = *(int *)(block + 4) != 0;
  if (ok) {
    *(i8 *)(block + 1) = 1;
    *(i16 *)(block + 0xc) = 0;
    *(i16 *)(block + 0x10) = (i16)size;
    *(i16 *)(block + 0xe) = (i16)size;
    *(i32 *)(block + 8) = 0;
  }
  else {
    *(i32 *)(block + 4) = 0;
    error_report(0xfffffffe,block_id,0,size & 0xffff,0);
  }
  return !ok;
}

/* 00497ff3 auto */
i32 __cdecl memblock_ensure_locked(iptr block)

{
  i32 ptr;
  
  if (*(int *)(block + 8) == 0) {
    ptr = (i32)mem_handle_lock(*(i32 *)(block + 4));
    *(i32 *)(block + 8) = ptr;
    if (*(int *)(block + 8) == 0) {
      error_report(0xfffffff6,(uint)*(byte *)block,0,0,0);
    }
  }
  return 0;
}

/* 0049805e auto */
void __cdecl memblock_detach(iptr block)

{
  *(i32 *)(block + 8) = 0;
  *(i32 *)(block + 4) = 0;
  return;
}

/* 004980a9 auto */
void __cdecl memblock_unlock(iptr block)

{
  if (*(int *)(block + 8) != 0) {
    if (*(int *)(block + 4) != 0) {
      mem_handle_unlock(*(i32 *)(block + 4));
    }
    *(i32 *)(block + 8) = 0;
  }
  return;
}

/* 004980ec auto */
iptr __cdecl memblock_free(iptr block)

{
  if (*(char *)(block + 1) != '\0') {
    memblock_unlock(block);
    if (*(int *)(block + 4) != 0) {
      mem_handle_free(*(i32 *)(block + 4));
      *(i32 *)(block + 4) = 0;
    }
  }
  *(i16 *)(block + 0xc) = 0;
  *(i16 *)(block + 0x10) = 0;
  *(i16 *)(block + 0xe) = 0;
  return block;
}

/* 00498159 auto */
int __cdecl memblock_alloc(iptr block,uint size)

{
  int lock_err;
  i32 ptr;
  
  ptr = 0;
  if ((uint)*(ushort *)(block + 0x10) < (size & 0xffff)) {
    error_report(0xfffffffd,(uint)*(byte *)block,0,size & 0xffff,
                       (uint)*(ushort *)(block + 0x10));
  }
  lock_err = memblock_ensure_locked(block);
  if (lock_err == 0) {
    ptr = (uint)*(ushort *)(block + 0xc) + *(int *)(block + 8);
    *(short *)(block + 0xc) = *(short *)(block + 0xc) + (short)size;
    *(short *)(block + 0x10) = *(short *)(block + 0x10) - (short)size;
  }
  return ptr;
}

/* 004b1396 auto */
int __cdecl mem_checksum(iptr data,uint size)

{
  uint sign;
  byte *byte_ptr;
  int k;
  ushort *word_ptr;
  int j;
  int i;
  int *dword_ptr;
  int sum;
  
  if (size == 0) {
    sum = 0;
  }
  else {
    sum = 0;
    sign = (int)size >> 0x1f;
    if (((size ^ sign) - sign & 3 ^ sign) == sign) {
      dword_ptr = (int *)data;
      for (i = 0; i < (int)size >> 2; i++) {
        sum += *dword_ptr;
        dword_ptr++;
      }
    }
    else if (((size ^ sign) - sign & 1 ^ sign) == sign) {
      word_ptr = (ushort *)data;
      for (j = 0; j < (int)size >> 2; j++) {
        sum += (uint)*word_ptr;
        word_ptr++;
      }
    }
    else {
      byte_ptr = (byte *)data;
      for (k = 0; k < (int)size; k++) {
        sum += (uint)*byte_ptr;
        byte_ptr++;
      }
    }
  }
  return sum;
}

/* 004bb870 auto */
int __cdecl mem_handle_alloc_tracked(i32 size)

{
  int handle;
  
  mem_last_alloc_size = size;
  handle = mem_handle_alloc(size);
  error_last_alloc_failed = (uint)(handle == 0);
  return handle;
}

/* 004cca35 auto */
i32 __cdecl memblock_alloc_checked(iptr block,uint size)

{
  LPCSTR lpCaption;
  LPCSTR lpText;
  iptr wnd;
  i32 result;
  UINT uType;
  
  if ((uint)*(ushort *)(block + 0x10) < (size & 0xffff)) {
    uType = 0;
    lpCaption = (LPCSTR)label_string(*(i32 *)(label_string_ids + 0x8d0));
    lpText = (LPCSTR)label_string(*(i32 *)(label_string_ids + 0x8e8));
    wnd = wnd_get_window((WndBase *)(editor_text_dlg_wnd_block.active_editor_wnd + 0x48));
    MessageBoxA(*(HWND *)(wnd + 4),lpText,lpCaption,uType);
    result = 0;
  }
  else {
    result = memblock_alloc(block,size);
  }
  return result;
}

/* 00511350 auto */
int __cdecl int_clamp_c(int value,int lo,int hi)

{
  if ((value <= hi) && (hi = value, value < lo)) {
    hi = lo;
  }
  return hi;
}

/* 00554145 auto */
i32 __cdecl dbg_pick_player(int include_barbarians)

{
  iptr adjective;
  i32 choice;
  uint civ;
  Dialog dlg;
  i32 seh_prev;
  i8 *seh_handler;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  dialog_ctor(&dlg,0x4000);
  eh_state = 0;
  dialog_load_text(&dlg,(iptr)&str_debug_2,(iptr)&str_pickplayer,1);
  for (civ = (uint)(include_barbarians == 0); (int)civ < 8; civ++) {
    if ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0) {
      text_clear();
      adjective = civ_get_adjective(civ);
      text_append(adjective);
      dialog_add_option((DialogOptionList *)&dlg,(iptr)&map_views_block.text_buffer,civ,0);
    }
  }
  dialog_set_default_choice((DialogOptionList *)&dlg,human_civ[0]);
  choice = dlg_show_modal(&dlg,0);
  eh_state = 0xffffffff;
  /* inlined unwind funclet 00554272 */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
  return choice;
}

/* 0055add0 auto */
i32 __stdcall win_main(i32 instance,i32 prev_instance,i32 cmd_line,i32 show_cmd)

{
  DWORD last_error;
  int started;
  HWND hWnd;
  
  CreateMutexA((LPSECURITY_ATTRIBUTES)0x0,1,str_civilization_ii_once_only);
  last_error = GetLastError();
  if (last_error == 0xb7) {
    hWnd = FindWindowA(str_mswindowclass,(LPCSTR)0x0);
    if (hWnd != (HWND)0x0) {
      BringWindowToTop(hWnd);
    }
  }
  else {
    started = app_startup(instance,prev_instance);
    if (started != 0) {
      game_main_entry();
      app_shutdown();
    }
  }
  return 0;
}

/* 00568176 auto */
i32 __cdecl mem_check_available(i32 size)

{
  return 1;
}

/* 00589d80 auto */
int __cdecl err_register_cleanup_fn(iptr callback)

{
  int slot;
  int index;
  
  slot = fatal_cleanup_count;
  index = -1;
  if (fatal_cleanup_count < 10) {
    index = fatal_cleanup_count;
    fatal_cleanup_count++;
    *(iptr *)(((i8 *)&main_frame_bg_surface_block.crash_handler_callbacks) + slot * 4) = callback;
  }
  return index;
}

/* 00589dc5 auto */
void __cdecl err_dump_text_file(iptr path)

{
  FILE *_File;
  char *line_read;
  size_t len;
  int cmp;
  iptr i;
  char line[80];
  int keep_going;
  
  _File = (FILE *)file_open_path(path,(iptr)&str_rt_8);
  if (_File != (FILE *)0x0) {
    keep_going = 1;
    while (((keep_going != 0 && ((CRT_FEOF(_File)) == 0)) &&
           (line_read = _fgets(line,0x4f,_File), line_read != (char *)0x0))) {
      for (i = 0; len = _strlen(line), i < (int)len; i++)
      {
        if (line[i] < ' ') {
          line[i] = '\0';
        }
      }
      cmp = _strncmp(line,((i8 *)&err_comment_prefix_str),3);
      if (cmp == 0) {
        keep_going = 0;
      }
      else {
        _sprintf(((i8 *)&main_frame_bg_surface_block.crash_debug_buffer),((i8 *)&err_dump_line_fmt),line);
        OutputDebugStringA(((i8 *)&main_frame_bg_surface_block.crash_debug_buffer));
      }
    }
  }
  if (_File != (FILE *)0x0) {
    _fclose(_File);
  }
  return;
}

/* 00589ef8 auto */
void __cdecl error_report(uint error_code,int module_id,iptr context,iptr data1,iptr data2)

{
  char data2_text[12];
  char error_text[80];
  char module_text[80];
  char data1_text[12];
  
  if (context != 0) {
    crt_strcpy(((i8 *)&error_context_text),(const void *)context);
  }
  __itoa(error_code,error_text,10);
  __itoa(module_id,module_text,10);
  __ltoa(data1,data1_text,10);
  __ltoa(data2,data2_text,10);
  file_read_nth_line((iptr)error_text,(iptr)&str_errors_db,~error_code + 1);
  file_read_nth_line((iptr)module_text,(iptr)&str_modules_db,module_id);
  err_fatal_exit((iptr)error_text,(iptr)module_text,(iptr)data1_text,(iptr)data2_text,error_code);
  return;
}

/* 0058a0ee auto */
void __cdecl err_fatal_exit(iptr error_text,iptr module_text,iptr data1_text,iptr data2_text,i32 error_code)

{
  size_t len;
  int i;
  i8 msg[256];
  
  crt_strcpy(msg,str_error_4);
  crt_strcat(msg,(const void *)error_text);
  crt_strcat(msg,str_in_module);
  crt_strcat(msg,(const void *)module_text);
  crt_strcat(msg,str_data);
  crt_strcat(msg,(const void *)data1_text);
  crt_strcat(msg,((i8 *)&err_data_sep_str));
  crt_strcat(msg,(const void *)data2_text);
  _sprintf(((i8 *)&main_frame_bg_surface_block.crash_debug_buffer),((i8 *)&err_fatal_msg_fmt),msg);
  OutputDebugStringA(((i8 *)&main_frame_bg_surface_block.crash_debug_buffer));
  dbg_log((iptr)&main_frame_bg_surface_block.crash_debug_buffer);
  len = _strlen(((i8 *)&error_context_text));
  if (len != 0) {
    _sprintf(((i8 *)&main_frame_bg_surface_block.crash_debug_buffer),str_s_2,((i8 *)&error_context_text));
    OutputDebugStringA(((i8 *)&main_frame_bg_surface_block.crash_debug_buffer));
    dbg_log((iptr)&main_frame_bg_surface_block.crash_debug_buffer);
  }
  if ((*(int *)&error_last_alloc_failed) != 0) {
    __ltoa((*(long *)&mem_last_alloc_size),(char *)data1_text,10);
    crt_strcpy(msg,str_tried_to_allocate);
    crt_strcat(msg,(const void *)data1_text);
    crt_strcat(msg,str_bytes);
    _sprintf(((i8 *)&main_frame_bg_surface_block.crash_debug_buffer),((i8 *)&fatal_alloc_line_fmt),msg);
    OutputDebugStringA(((i8 *)&main_frame_bg_surface_block.crash_debug_buffer));
    dbg_log((iptr)&main_frame_bg_surface_block.crash_debug_buffer);
  }
  _sprintf(((i8 *)&main_frame_bg_surface_block.crash_debug_buffer),((i8 *)&fatal_alloc_newline_str));
  OutputDebugStringA(((i8 *)&main_frame_bg_surface_block.crash_debug_buffer));
  dbg_log((iptr)&main_frame_bg_surface_block.crash_debug_buffer);
  if (error_last_open_failed != 0) {
    _sprintf(((i8 *)&main_frame_bg_surface_block.crash_debug_buffer),str_file_open_failed_s,((i8 *)&error_last_open_path));
    OutputDebugStringA(((i8 *)&main_frame_bg_surface_block.crash_debug_buffer));
    dbg_log((iptr)&main_frame_bg_surface_block.crash_debug_buffer);
  }
  crt_strcpy(msg,str_most_recent_dos_error);
  __itoa(crt_errno,(char *)data1_text,10);
  crt_strcat(msg,(const void *)data1_text);
  _sprintf(((i8 *)&main_frame_bg_surface_block.crash_debug_buffer),((i8 *)&fatal_dos_error_line_fmt),msg);
  OutputDebugStringA(((i8 *)&main_frame_bg_surface_block.crash_debug_buffer));
  dbg_log((iptr)&main_frame_bg_surface_block.crash_debug_buffer);
  _sprintf(((i8 *)&main_frame_bg_surface_block.crash_debug_buffer),((i8 *)&fatal_dos_error_newline_str));
  OutputDebugStringA(((i8 *)&main_frame_bg_surface_block.crash_debug_buffer));
  dbg_log((iptr)&main_frame_bg_surface_block.crash_debug_buffer);
  err_dump_text_file((iptr)&str_warn0_dat);
  i = fatal_cleanup_count;
  while (i = i - 1, -1 < i) {
    if (*(int *)(((i8 *)&main_frame_bg_surface_block.crash_handler_callbacks) + i * 4) != 0) {
      call_untyped(*(code **)(((i8 *)&main_frame_bg_surface_block.crash_handler_callbacks) + i * 4));
    }
  }
  DebugBreak();
                    /* WARNING: Subroutine does not return */
  _exit(3);
}

/* 0058ae20 auto */
i32 __cdecl
point_in_rect_ltrb(int x,int y,int left,int top,int right,int bottom)

{
  i32 inside;
  
  if ((((x < left) || (right < x)) || (y < top)) || (bottom < y))
  {
    inside = 0;
  }
  else {
    inside = 1;
  }
  return inside;
}

/* 0059a6f0 auto */
int __cdecl rng_set_seed(int seed)

{
  int prev_state;
  
  prev_state = g_nr_seed;
  if (seed == 0) {
    prev_state = 0;
  }
  else {
    g_nr_seed = seed;
  }
  return prev_state;
}

/* 0059a733: written by hand in src/game/random.cpp */

/* 0059a791: written by hand in src/game/random.cpp */

/* 005a1a44 auto */
int __cdecl int_clamp_b(int value,int lo,int hi)

{
  if (lo <= value) {
    lo = value;
  }
  if (lo <= hi) {
    hi = lo;
  }
  return hi;
}

/* 005adfa0 auto */
int __cdecl int_clamp(iptr value,iptr lo,int hi)

{
  if (lo <= value) {
    lo = value;
  }
  if (lo <= hi) {
    hi = lo;
  }
  return hi;
}

/* 005adfd9 auto */
void __cdecl int_swap(iptr a,iptr b)

{
  i32 tmp;
  
  tmp = *(i32 *)a;
  *(i32 *)a = *(i32 *)b;
  *(i32 *)b = tmp;
  return;
}

/* 005ae0b0 auto */
int __cdecl coarse_wrap_x(int x)

{
  if ((game.rules & 0x8000) == 0) {
    if (x < 0) {
      x = map.quarter_w + x;
    }
    else if (map.quarter_w <= x) {
      x -= map.quarter_w;
    }
  }
  return x;
}

/* 005ae296 auto */
int __cdecl dist_from_deltas(uint dx,uint dy)

{
  int half_sum;
  i32 dist;
  
  if ((int)dx < 1) {
    dx = ~dx + 1;
  }
  if ((int)dy < 1) {
    dy = ~dy + 1;
  }
  half_sum = (int)(dy + dx) >> 1;
  if ((int)dy < (int)dx) {
    dist = dx - ((int)((half_sum - dy) + 1) >> 1);
  }
  else {
    dist = dy - ((int)((half_sum - dx) + 1) >> 1);
  }
  return dist;
}

/* 005ae3ec auto */
int __cdecl int_shift_signed(int value,int shift)

{
  i8 right_shift;
  
  if (shift != 0) {
    if (shift < 1) {
      right_shift = (byte)shift;
      if (shift < 1) {
        right_shift = ~(byte)shift + 1;
      }
      value = value >> (right_shift & 0x1f);
    }
    else {
      value = value << ((byte)shift & 0x1f);
    }
  }
  return value;
}

/* 005bb9c0 auto */
void __cdecl win_drain_input_msgs(void)

{
  BOOL got_msg;
  tagMSG msg;
  
  do {
    got_msg = PeekMessageA(&msg,(HWND)0x0,0x200,0x209,1);
  } while (got_msg != 0);
  do {
    got_msg = PeekMessageA(&msg,(HWND)0x0,0x100,0x108,1);
  } while (got_msg != 0);
  return;
}

/* 005bba4f auto */
i32 __cdecl win_dispatch_one_message(void)

{
  BOOL got_msg;
  i32 dispatched;
  tagMSG msg;
  
  got_msg = PeekMessageA(&msg,(HWND)0x0,0,0,1);
  if (got_msg == 0) {
    win_flush_pending_msgs();
    if (wnd_modal_stack_below_block.avi_idle_update_enabled != 0) {
      avi_update_current_frame();
    }
    dispatched = 0;
  }
  else {
    TranslateMessage(&msg);
    DispatchMessageA(&msg);
    dispatched = 1;
  }
  return dispatched;
}

/* 005bbab8 auto */
uint __cdecl win_dispatch_one_paint(void)

{
  BOOL got_msg;
  tagMSG msg;
  
  got_msg = PeekMessageA(&msg,(HWND)0x0,0xf,0xf,1);
  if (got_msg != 0) {
    TranslateMessage(&msg);
    DispatchMessageA(&msg);
  }
  return (uint)(got_msg != 0);
}

/* 005bbb0a auto */
void __cdecl win_dispatch_all_messages(void)

{
  int dispatched;
  
  do {
    dispatched = win_dispatch_one_message();
  } while (dispatched != 0);
  GdiFlush();
  return;
}

/* 005bbb32 auto */
void __cdecl win_dispatch_all_paints(void)

{
  int dispatched;
  
  do {
    dispatched = win_dispatch_one_paint();
  } while (dispatched != 0);
  GdiFlush();
  return;
}

/* 005bbb76 auto */
uint __cdecl win_dispatch_one_custom_msg(void)

{
  BOOL got_msg;
  tagMSG msg;
  
  got_msg = PeekMessageA(&msg,(HWND)0x0,0x3bd,0x3bd,1);
  if (got_msg != 0) {
    TranslateMessage(&msg);
    DispatchMessageA(&msg);
  }
  return (uint)(got_msg != 0);
}

/* 005bbbce auto */
void __cdecl win_dispatch_custom_msgs(void)

{
  int dispatched;
  
  do {
    dispatched = win_dispatch_one_custom_msg();
  } while (dispatched != 0);
  if (wnd_modal_stack_below_block.avi_idle_update_enabled != 0) {
    avi_update_current_frame();
  }
  return;
}

/* 005c54d0 auto */
i32 __cdecl endian_from_le(i32 value)

{
  return value;
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
  dbg_log_file_ctor(((i8 *)&default_draw_font_obj_block.dbg_log_file));
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
  dbg_log_file_dtor(((i8 *)&default_draw_font_obj_block.dbg_log_file));
  return;
}

/* 005d225b auto */
i8 __cdecl dbg_log(iptr text)

{
  i8 result;
  
  result = dbg_log_write(((i8 *)&default_draw_font_obj_block.dbg_log_file),text);
  return result;
}

/* 005d2279 auto */
i8 __cdecl dbg_logf(iptr fmt,iptr arg)

{
  i8 result;
  char buf[1024];
  
  _sprintf(buf,(char *)fmt,arg);
  result = dbg_log_write(((i8 *)&default_draw_font_obj_block.dbg_log_file),(iptr)buf);
  return result;
}

/* 005d22b7 auto */
i8 __cdecl dbg_logf_int2(iptr fmt,i32 arg1,i32 arg2)

{
  i8 result;
  char buf[1024];
  
  _sprintf(buf,(char *)fmt,arg1,arg2);
  result = dbg_log_write(((i8 *)&default_draw_font_obj_block.dbg_log_file),(iptr)buf);
  return result;
}

/* 005d22f9 auto */
void __cdecl dbg_logf3(iptr fmt,iptr arg1,i32 arg2,i32 arg3)

{
  char buf[1024];
  
  _sprintf(buf,(char *)fmt,arg1,arg2,arg3);
  dbg_log_write(((i8 *)&default_draw_font_obj_block.dbg_log_file),(iptr)buf);
  return;
}

/* 005d233f auto */
void __cdecl dbg_logf_noret(iptr fmt,i32 arg)

{
  char buf[1024];
  
  _sprintf(buf,(char *)fmt,arg);
  dbg_log_write(((i8 *)&default_draw_font_obj_block.dbg_log_file),(iptr)buf);
  return;
}

/* 005d237d auto */
i8 __cdecl dbg_logf_str(iptr fmt,iptr str)

{
  i8 result;
  char buf[1024];
  
  _sprintf(buf,(char *)fmt,str);
  result = dbg_log_write(((i8 *)&default_draw_font_obj_block.dbg_log_file),(iptr)buf);
  return result;
}

/* 005d23bb auto */
void __cdecl dbg_logf_str_int(iptr fmt,iptr str,iptr value)

{
  char buf[1024];
  
  _sprintf(buf,(char *)fmt,str,value);
  dbg_log_write(((i8 *)&default_draw_font_obj_block.dbg_log_file),(iptr)buf);
  return;
}

/* 005d246f auto */
void * __thiscall dbg_log_file_ctor(void *self)

{
  DWORD tick_count;
  
  dbg_log_open();
  tick_count = GetTickCount();
  *(DWORD *)self = tick_count;
  return self;
}

/* 005d2498 auto */
void __thiscall dbg_log_file_dtor(void *self)

{
  dbg_log_close();
  return;
}

/* 005d24b3 auto */
i8 __thiscall dbg_log_write(void *self,iptr text)

{
  DWORD tick_count;
  char line[1032];
  
  tick_count = GetTickCount();
  _sprintf(line,str_5d,(tick_count - *(int *)self) / 1000);
  crt_strcat(line,(const void *)text);
  if (dbg_log_to_debugger != '\0') {
    dbg_log_write_debugger((iptr)line);
  }
  if (dbg_log_to_file != '\0') {
    dbg_log_write_file((iptr)line);
  }
  return 1;
}

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
  err_ctx_ctor((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx));
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
  err_ctx_dtor((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx));
  return;
}

/* 005dae6b auto */
void __thiscall
err_report
          (ErrorContext *self,i32 code,iptr file,iptr line,i32 extra)

{
  i32 msg;
  
  err_set_code(self,code);
  msg = (i32)err_format_message(self,(iptr)&str_fatal_error,file,line,extra);
  err_show_fatal_box(self,msg);
  return;
}

/* 005daef7 auto */
ErrorContext * __thiscall
err_format_message
          (ErrorContext *self,iptr fmt,i32 text,i32 file,i32 line)

{
  size_t len;
  i32 trace;
  char *_Format;
  
  crt_strcpy(self,((i8 *)&err_format_empty_str));
  _Format = str_error_s_file_s_line_d;
  len = _strlen((char *)self);
  _sprintf((char *)(self->error_message_text + len),_Format,text,file,line);
  trace = (i32)err_get_stack_trace(self);
  crt_strcat(self,(const void *)trace);
  return self;
}

/* 005daf63 auto */
u8 * __thiscall err_get_stack_trace(ErrorContext *self)

{
  dbg_stack_trace_stub((iptr)(self->stack_trace_text));
  return self->stack_trace_text;
}

/* 005daf92 auto */
void __thiscall err_show_fatal_box(ErrorContext *self,i32 msg)

{
  dbg_fatal_msgbox_break((iptr)&str_smeds_application_error,(LPCSTR)msg);
  return;
}

/* 005dafdf auto */
void __thiscall err_set_code(ErrorContext *self,u32 code)

{
  self->last_error_code = code;
  self->error_bits = self->error_bits | 1 << ((byte)code & 0x1f);
  return;
}

/* 005db035 auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall err_ctx_set_field_708(ErrorContext *self,i32 value)

{
  *(i32 *)((ErrorContextExt *)self)->error_ctx_option = value;
  return;
}

/* 005db059 auto */
void __thiscall err_ctx_clear_codes(ErrorContext *self)

{
  self->error_bits = 0;
  self->last_error_code = 0;
  return;
}

/* 005db089 auto */
ErrorContext * __thiscall err_ctx_ctor(ErrorContext *self)

{
  err_ctx_set_field_708(self,0);
  err_ctx_clear_codes(self);
  return self;
}

/* 005db0b4 auto */
/* Library Function - Single Match
    public: __thiscall Iostream_init::~Iostream_init(void)
   
   Library: Visual Studio 1998 Debug */

void __thiscall err_ctx_dtor(void *self)

{
  return;
}

/* 005dcb8c auto */
void __cdecl mem_copy_src_dst(iptr src,iptr dst,i32 size)

{
  mem_move_src_dst(src,dst,size);
  return;
}

/* 005dcd70 auto */
void __cdecl mem_handle_clone(iptr handle_ptr)

{
  SIZE_T mem_size;
  HGLOBAL hMem;
  LPVOID dst;
  LPVOID src;
  
  mem_size = GlobalSize(*(HGLOBAL *)handle_ptr);
  hMem = (HGLOBAL)mem_handle_alloc(mem_size);
  if (hMem != (HGLOBAL)0x0) {
    dst = GlobalLock(hMem);
    src = GlobalLock(*(HGLOBAL *)handle_ptr);
    crt_memmove(dst,src,mem_size);
    GlobalUnlock(hMem);
    GlobalUnlock(*(HGLOBAL *)handle_ptr);
    *(HGLOBAL *)handle_ptr = hMem;
  }
  return;
}

/* 005dcdf9 auto */
LPVOID __cdecl mem_handle_lock(HGLOBAL handle)

{
  LPVOID ptr;
  
  if (handle == (HGLOBAL)0x0) {
    ptr = (LPVOID)0x0;
  }
  else {
    ptr = GlobalLock(handle);
  }
  return ptr;
}

/* 005dce29 auto */
i32 __cdecl mem_handle_unlock(HGLOBAL handle)

{
  if (handle != (HGLOBAL)0x0) {
    GlobalUnlock(handle);
  }
  return 0;
}

/* 005dce4f auto */
HGLOBAL __cdecl mem_handle_alloc(SIZE_T size)

{
  HGLOBAL handle;
  
  handle = GlobalAlloc(0x42,size);
  if (handle == (HGLOBAL)0x0) {
    err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),1,(iptr)&str_err_memallocfailed,(iptr)&str_d_ss_smeds32_pcmem_cpp,0x4c);
  }
  return handle;
}

/* 005dce96 auto */
HGLOBAL __cdecl mem_handle_free(HGLOBAL handle)

{
  HGLOBAL result;
  
  if (handle == (HGLOBAL)0x0) {
    dbg_log((iptr)&str_error_tried_to_dispose_of_null_handle_in);
    result = (HGLOBAL)0x0;
  }
  else {
    result = GlobalFree(handle);
  }
  return result;
}

/* 005dced3 auto */
void __cdecl mem_move_src_dst(iptr src,iptr dst,i32 size)

{
  crt_memmove((void *)dst,(const void *)src,size);
  return;
}

/* 005dcef7 auto */
SIZE_T __cdecl mem_handle_size(HGLOBAL handle)

{
  SIZE_T mem_size;
  
  mem_size = GlobalSize(handle);
  return mem_size;
}

/* 005dfb61 auto */
iptr __cdecl mem_rle_decompress(iptr buf_ptr)

{
  byte fill_byte;
  size_t src_size;
  byte *src_copy;
  iptr grown;
  int final_buf;
  byte *out_end;
  uint run_len;
  byte *src;
  byte *out;
  int capacity2;
  iptr out_size;
  
  src_size = __msize(*(void **)buf_ptr);
  src_copy = (byte *)operator_new(src_size);
  if (src_copy == (byte *)0x0) {
    dbg_log((iptr)&str_rlldecode_could_not_allocate_decompressi);
    out_size = 0;
  }
  else {
    mem_move_src_dst(*(iptr *)buf_ptr,(iptr)src_copy,src_size);
    capacity2 = src_size * 2;
    out = (byte *)crt_realloc((void *)*(i32 *)buf_ptr,capacity2);
    if (out == (byte *)0x0) {
      dbg_log((iptr)&str_rlldecode_could_not_allocate_decompressi_2);
      out_size = 0;
    }
    else {
      *(byte **)buf_ptr = out;
      out_end = out + capacity2;
      out_size = 0;
      src = src_copy;
      while (src < src_copy + (src_size - 1)) {
        run_len = (uint)*src;
        if (out_end < out + (run_len & 0x7f) + 1) {
          capacity2 += 1000;
          grown = (iptr)crt_realloc((void *)*(i32 *)buf_ptr,capacity2);
          if (grown == 0) {
            dbg_log((iptr)&str_rlldecode_could_not_allocate_decompressi_3);
            return 0;
          }
          *(iptr *)buf_ptr = grown;
          out = (byte *)(out_size + grown);
          out_end = (byte *)(capacity2 + grown);
        }
        if (run_len < 0x80) {
          fill_byte = src[1];
          src += 2;
          while (run_len != 0) {
            *out = fill_byte;
            out++;
            out_size++;
            run_len--;
          }
        }
        else {
          run_len -= 0x80;
          src++;
          while (run_len != 0) {
            *out = *src;
            src++;
            out++;
            out_size++;
            run_len--;
          }
        }
      }
      final_buf = (int)crt_realloc((void *)*(i32 *)buf_ptr,out_size);
      if (final_buf == 0) {
        dbg_log((iptr)&str_rlldecode_could_not_allocate_decompressi_4);
        out_size = 0;
      }
      else {
        *(int *)buf_ptr = final_buf;
        operator_delete(src_copy);
      }
    }
  }
  return out_size;
}

/* 005dfd8f auto */
uint __cdecl mem_rle_compress(iptr buf_ptr,int size)

{
  char *out_pos;
  char *out_buf;
  uint out_size;
  char *src_end;
  void *new_buf;
  char *scan;
  char *src;
  char *out;
  int literal_len;
  int run_len;
  int written;
  
  out_buf = (char *)operator_new(size + ((int)(size + (size >> 0x1f & 0x7fU)) >> 7) + 5);
  if (out_buf == (char *)0x0) {
    dbg_log((iptr)&str_rllencode_could_not_allocate_compression);
    out_size = 0xffffffff;
  }
  else {
    src = *(char **)buf_ptr;
    scan = src + 1;
    src_end = src + size;
    written = 0;
    out = out_buf;
    while (src < src_end) {
      for (; (scan < src_end && (*scan == *src)); scan++) {
      }
      run_len = (int)scan - (int)src;
      if (2 < run_len) {
        while (out_pos = out, run_len != 0) {
          if (run_len < 0x80) {
            *out = (char)run_len;
            if (size <= written + 1) goto compress_fail;
            run_len = 0;
          }
          else {
            *out = 127;
            if (size <= written + 1) goto compress_fail;
            run_len -= 0x7f;
          }
          out++;
          *out = *src;
          out = out_pos + 2;
          written += 2;
          if (size <= written) goto compress_fail;
        }
        src = scan;
      }
      for (; (scan < src_end && (scan[1] != *scan)); scan++) {
      }
      run_len = (int)scan - (int)src;
      while (run_len != 0) {
        if (run_len < 0x80) {
          *out = (char)run_len - 0x80;
          out++;
          written++;
          if (size <= written) goto compress_fail;
          literal_len = run_len;
          run_len = 0;
        }
        else {
          *out = -1;
          out++;
          written++;
          if (size <= written) goto compress_fail;
          run_len -= 0x7f;
          literal_len = 0x7f;
        }
        while (literal_len != 0) {
          *out = *src;
          src++;
          out++;
          written++;
          literal_len--;
          if (size <= written) goto compress_fail;
        }
      }
    }
    out_size = (int)out - (int)out_buf;
    if (size < (int)out_size) {
compress_fail:
      operator_delete(out_buf);
      out_size = 0xffffffff;
    }
    else {
      operator_delete(*(void **)buf_ptr);
      new_buf = operator_new(out_size);
      *(void **)buf_ptr = new_buf;
      mem_move_src_dst((iptr)out_buf,*(iptr *)buf_ptr,out_size);
      operator_delete(out_buf);
    }
  }
  return out_size;
}

/* 005ed920 auto */
i32 __cdecl dbg_log_open(void)

{
  size_t nNumberOfBytesToWrite;
  DWORD *lpNumberOfBytesWritten;
  LPOVERLAPPED lpOverlapped;
  char version[32];
  char header[1024];
  HANDLE file;
  DWORD bytes_written;
  
  file = (HANDLE)0x0;
  file = CreateFileA(str_smeds_log,0xc0000000,0,(LPSECURITY_ATTRIBUTES)0x0,2,0x80,
                        (HANDLE)0x0);
  if (file != (HANDLE)0xffffffff) {
    smeds_log_enabled = 1;
  }
  crt_strcpy(header,str_smeds_log_2);
  crt_strcat(header,str_file_output_to);
  crt_strcat(header,str_smeds_log_3);
  crt_strcat(header,((i8 *)&dbg_log_header_crlf));
  crt_strcat(header,str_smeds32_version);
  _sprintf(version,str_d_d_d,2,0,0);
  crt_strcat(header,version);
  crt_strcat(header,((i8 *)&dbg_log_header_blank_lines));
  if (smeds_log_enabled != '\0') {
    lpOverlapped = (LPOVERLAPPED)0x0;
    lpNumberOfBytesWritten = &bytes_written;
    nNumberOfBytesToWrite = _strlen(header);
    WriteFile(file,header,nNumberOfBytesToWrite,lpNumberOfBytesWritten,lpOverlapped);
    CloseHandle(file);
  }
  OutputDebugStringA(header);
  return 1;
}

/* 005eda65 auto */
i32 __cdecl dbg_log_close(void)

{
  size_t nNumberOfBytesToWrite;
  DWORD *lpNumberOfBytesWritten;
  LPOVERLAPPED lpOverlapped;
  char footer[1024];
  HANDLE file;
  DWORD bytes_written;
  
  file = (HANDLE)0x0;
  if (smeds_log_enabled != '\0') {
    file = CreateFileA(str_smeds_log_4,0xc0000000,0,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,
                          (HANDLE)0x0);
    SetFilePointer(file,0,(PLONG)0x0,2);
    crt_strcpy(footer,str_log_closed);
    lpOverlapped = (LPOVERLAPPED)0x0;
    lpNumberOfBytesWritten = &bytes_written;
    nNumberOfBytesToWrite = _strlen(footer);
    WriteFile(file,footer,nNumberOfBytesToWrite,lpNumberOfBytesWritten,lpOverlapped);
    CloseHandle(file);
    OutputDebugStringA(footer);
  }
  return 1;
}

/* 005edb15 auto */
i32 __cdecl dbg_log_write_file(iptr text)

{
  HANDLE hFile;
  size_t nNumberOfBytesToWrite;
  DWORD *lpNumberOfBytesWritten;
  LPOVERLAPPED lpOverlapped;
  DWORD bytes_written;
  
  if (smeds_log_enabled != '\0') {
    hFile = CreateFileA(str_smeds_log_5,0xc0000000,0,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,
                        (HANDLE)0x0);
    SetFilePointer(hFile,0,(PLONG)0x0,2);
    lpOverlapped = (LPOVERLAPPED)0x0;
    lpNumberOfBytesWritten = &bytes_written;
    nNumberOfBytesToWrite = _strlen((char *)text);
    WriteFile(hFile,(LPCVOID)text,nNumberOfBytesToWrite,lpNumberOfBytesWritten,lpOverlapped);
    WriteFile(hFile,((i8 *)&dbg_log_file_crlf),2,&bytes_written,(LPOVERLAPPED)0x0);
    CloseHandle(hFile);
  }
  return 1;
}

/* 005edbb2 auto */
i32 __cdecl dbg_log_write_debugger(iptr text)

{
  OutputDebugStringA((LPCSTR)text);
  OutputDebugStringA(((i8 *)&dbg_log_debugger_crlf));
  return 1;
}

/* 005edc6c: written by hand in src/game/regargs.cpp */

/* 005edcac: written by hand in src/game/regargs.cpp */

/* 005edd00 auto */
void __cdecl dbg_fatal_msgbox_break(iptr caption,LPCSTR text)

{
  MessageBoxA((HWND)0x0,text,(LPCSTR)caption,0x2030);
  DebugBreak();
  return;
}

/* 005eddaa auto */
void __cdecl dbg_stack_trace_stub(iptr buf)

{
  _sprintf((char *)buf,str_stack_trace_not_yet_available_in_win32);
  return;
}

/* 005eeeb0 auto */
i32 __cdecl sys_msgbox_potentially_fatal(LPCSTR text,i32 severity,i32 buttons)

{
  int choice;
  i32 result;
  uint style2;
  
  style2 = 0;
  switch(severity) {
  case 0:
    style2 = 0x40;
    break;
  case 1:
    style2 = 0x20;
    break;
  case 2:
    style2 = 0x30;
    break;
  case 3:
    style2 = 0x10;
  }
  switch(buttons) {
  case 1:
    break;
  case 2:
    style2 = style2 | 1;
    break;
  case 4:
    style2 = style2 | 4;
    break;
  case 8:
    style2 = style2 | 3;
    break;
  case 0x10:
    style2 = style2 | 2;
    break;
  case 0x20:
    style2 = style2 | 5;
  }
  choice = MessageBoxA((HWND)0x0,text,str_potentially_fatal_error,style2 | 0x2000);
  switch(choice) {
  case 1:
    result = 0;
    break;
  case 2:
    result = 1;
    break;
  case 3:
    result = 4;
    break;
  case 4:
    result = 5;
    break;
  case 5:
    result = 6;
    break;
  case 6:
    result = 2;
    break;
  case 7:
    result = 3;
  }
  return result;
}

/* 005ef0b9 auto */
i32 __cdecl sys_msgbox_mapped(LPCSTR caption,LPCSTR text,i32 severity,i32 buttons)

{
  int choice;
  i32 result;
  uint style2;
  
  style2 = 0;
  switch(severity) {
  case 0:
    style2 = 0x40;
    break;
  case 1:
    style2 = 0x20;
    break;
  case 2:
    style2 = 0x30;
    break;
  case 3:
    style2 = 0x10;
  }
  switch(buttons) {
  case 1:
    break;
  case 2:
    style2 = style2 | 1;
    break;
  case 4:
    style2 = style2 | 4;
    break;
  case 8:
    style2 = style2 | 3;
    break;
  case 0x10:
    style2 = style2 | 2;
    break;
  case 0x20:
    style2 = style2 | 5;
  }
  choice = MessageBoxA((HWND)0x0,text,caption,style2 | 0x2000);
  switch(choice) {
  case 1:
    result = 0;
    break;
  case 2:
    result = 1;
    break;
  case 3:
    result = 4;
    break;
  case 4:
    result = 5;
    break;
  case 5:
    result = 6;
    break;
  case 6:
    result = 2;
    break;
  case 7:
    result = 3;
  }
  return result;
}

/* 005ef58e: written by hand in src/game/regargs.cpp */

/* 005f04c0 auto */
void __thiscall ptrlist_dtor(void *self)

{
  i32 seh_prev;
  i8 *seh_handler;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  /* inlined unwind funclet 005f04fe */ { ptrlist_clear(*(PtrList **)((iptr)&self)); }
  return;
}

/* 005f0590 auto */
i32 __thiscall ptrlist_first(PtrList *self)

{
  i32 data;
  
  data = ptrlist_first_impl(self);
  return data;
}

/* 005f05d0 auto */
i32 __thiscall ptrlist_next(PtrList *self)

{
  i32 data;
  
  data = ptrlist_next_impl(self);
  return data;
}

/* 005f0676 auto */
/* Library Function - Single Match
    public: __thiscall CDataBoundProperty::~CDataBoundProperty(void)
   
   Library: Visual Studio 1998 Debug */

void __thiscall ptrlist_node_dtor(void *self)

{
  return;
}

/* 005f068c auto */
void __thiscall ptrlist_node_set_next(PtrListNodeNextSetView *self,iptr next)

{
  self->next_node = next;
  return;
}

/* 005f06ad auto */
void __thiscall ptrlist_node_set_prev(PtrListNodePrevSetView *self,iptr prev)

{
  self->prev_node = prev;
  return;
}

/* 005f0724 auto */
void __thiscall ptrlist_clear(PtrList *self)

{
  ptrlist_clear_impl(self);
  return;
}

/* 005f0742 auto */
uint __thiscall ptrlist_is_empty(PtrList *self)

{
  return (uint)(self->head == 0);
}

/* 005f0770 auto */
i32 __thiscall ptrlist_first_impl(PtrList *self)

{
  i32 data;
  
  if (self->head == 0) {
    data = 0;
  }
  else {
    self->iter_node = self->head;
    data = ptrlist_node_data((PtrListNodeDataView *)self->head);
  }
  return data;
}

/* 005f0833 auto */
i32 __thiscall ptrlist_next_impl(PtrList *self)

{
  uptr next;
  i32 data;
  
  if (self->iter_node == 0) {
    data = 0;
  }
  else {
    next = ptrlist_node_next((PtrListNodeNextView *)self->iter_node);
    self->iter_node = next;
    if (self->iter_node == 0) {
      data = 0;
    }
    else {
      data = ptrlist_node_data((PtrListNodeDataView *)self->iter_node);
    }
  }
  return data;
}

/* 005f0c69 auto */
void __thiscall ptrlist_remove_current(PtrList *self)

{
  int empty;
  PtrListNodeNextSetView *this_00;
  PtrListNodePrevSetView *this_01;
  
  if ((self->iter_node != 0) && (empty = ptrlist_is_empty(self), empty == 0)) {
    this_00 = (PtrListNodeNextSetView *)ptrlist_node_prev((PtrListNodePrevView *)self->iter_node);
    this_01 = (PtrListNodePrevSetView *)ptrlist_node_next((PtrListNodeNextView *)self->iter_node);
    if ((this_00 == (PtrListNodeNextSetView *)0x0) && (this_01 == (PtrListNodePrevSetView *)0x0)) {
      if ((void *)self->iter_node != (void *)0x0) {
        ptrlist_node_delete((void *)self->iter_node,1);
      }
      self->head = 0;
      self->tail = 0;
      self->iter_node = 0;
    }
    else if (this_00 == (PtrListNodeNextSetView *)0x0) {
      self->head = (uptr)this_01;
      ptrlist_node_set_prev((PtrListNodePrevSetView *)self->head,0);
      if ((void *)self->iter_node != (void *)0x0) {
        ptrlist_node_delete((void *)self->iter_node,1);
      }
      self->iter_node = self->head;
    }
    else if (this_01 == (PtrListNodePrevSetView *)0x0) {
      self->tail = (uptr)this_00;
      ptrlist_node_set_next((PtrListNodeNextSetView *)self->tail,0);
      if ((void *)self->iter_node != (void *)0x0) {
        ptrlist_node_delete((void *)self->iter_node,1);
      }
      self->iter_node = self->tail;
    }
    else {
      ptrlist_node_set_next(this_00,(iptr)this_01);
      ptrlist_node_set_prev(this_01,(iptr)this_00);
      if ((void *)self->iter_node != (void *)0x0) {
        ptrlist_node_delete((void *)self->iter_node,1);
      }
      self->iter_node = (uptr)this_01;
    }
  }
  return;
}

/* 005f0e13 auto */
void __thiscall ptrlist_clear_impl(PtrList *self)

{
  ptrlist_first_impl(self);
  while (self->iter_node != 0) {
    ptrlist_remove_current(self);
  }
  return;
}

/* 005f0e50 auto */
u32 __thiscall ptrlist_node_data(PtrListNodeDataView *self)

{
  return self->node_data;
}

/* 005f0e70 auto */
u32 __thiscall ptrlist_node_next(PtrListNodeNextView *self)

{
  return self->next_node;
}

/* 005f0e90 auto */
u32 __thiscall ptrlist_node_prev(PtrListNodePrevView *self)

{
  return self->prev_node;
}

/* 005f0eb0 auto */
/* Library Function - Single Match
    public: void * __thiscall CDataBoundProperty::`scalar deleting destructor'(unsigned int)
   
   Library: Visual Studio 1998 Debug */

void * __thiscall ptrlist_node_delete(void *self,uint flags)

{
  ptrlist_node_dtor(self);
  if ((flags & 1) != 0) {
    operator_delete(self);
  }
  return self;
}
