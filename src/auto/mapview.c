/* The game, the map windows: drawing, scrolling, the mini map: functions translated from the original
 * (tools/gen_c.py, now edited directly), in address order. */
#include "auto_common.h"

/* 00406a80 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl minimap_window_global_init(void)

{
  minimap_window_static_init();
  minimap_window_reg_atexit();
  return;
}

/* 00406a9a auto */
void __cdecl minimap_window_static_init(void)

{
  frame_wnd_ctor((SurfaceWindow *)&minimap_window);
  return;
}

/* 00406ab4 auto */
void __cdecl minimap_window_reg_atexit(void)

{
  _atexit(minimap_window_atexit_dtor);
  return;
}

/* 00406ad1 auto */
void __cdecl minimap_window_atexit_dtor(void)

{
  frame_wnd_dtor((DibSurface *)&minimap_window);
  return;
}

/* 00406aeb auto */
#define minimap_hidden (*(undefined1 *)((u8 *)&g.d_00624ee0))
void __cdecl minimap_on_minimize(void)

{
  minimap_hidden = 1;
  return;
}
#undef minimap_hidden

/* 00406b02 auto */
#define minimap_hidden (*(undefined1 *)((u8 *)&g.d_00624ee0))
void __cdecl minimap_on_restore(void)

{
  city_window_bring_to_top((C_004083b0_4 *)&city_window);
  minimap_hidden = 0;
  minimap_redraw();
  return;
}
#undef minimap_hidden

/* 00406b28 auto */
#define minimap_hidden (*(undefined1 *)((u8 *)&g.d_00624ee0))
undefined4 __cdecl minimap_on_close(void)

{
  minimap_hidden = 1;
  wnd_minimize((WndBase *)&minimap_wnd);
  return 0;
}
#undef minimap_hidden

/* 00406b4c auto */
#define map_view_center_x (*(short *)((u8 *)&g.d_0066ca88))
#define mapview_center_y (*(short *)((u8 *)&g.d_0066ca8a))
#define minimap_origin_x (*(uint *)((u8 *)&g.d_0063c814))
#define minimap_origin_y (*(uint *)((u8 *)&g.d_0063c810))
#define _DAT_0063caf0 (*(undefined4 *)((u8 *)&g.d_0063caf0))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl minimap_calc_layout(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = minimap_client_height;
  iVar2 = minimap_client_width / (int)map.width;
  if (iVar2 < 2) {
    iVar2 = 1;
  }
  iVar3 = minimap_client_height / (int)map.height;
  if (iVar3 < 2) {
    iVar3 = 1;
  }
  if (iVar3 <= iVar2) {
    iVar2 = iVar3;
  }
  minimap_tile_height = iVar2;
  if (iVar3 <= iVar2) {
    minimap_tile_height = iVar3;
  }
  minimap_tile_width = iVar2 * 2;
  iVar2 = (minimap_client_width - minimap_tile_width / 2) / minimap_tile_width;
  minimap_view_cols = (int)map.width / 2;
  if (iVar2 <= (int)map.width / 2) {
    minimap_view_cols = iVar2;
  }
  minimap_view_rows = (int)map.height;
  if (minimap_client_height / minimap_tile_height <= (int)map.height) {
    minimap_view_rows = minimap_client_height / minimap_tile_height;
  }
  iVar2 = int_clamp(minimap_client_width - minimap_view_cols * minimap_tile_width,0,999);
  _DAT_0063caf0 = int_clamp(iVar1 - minimap_view_rows * minimap_tile_height,0,999);
  minimap_margin_x = iVar2 >> 1;
  _DAT_0063caf0 = _DAT_0063caf0 >> 1;
  if (minimap_view_rows < map.height) {
    minimap_origin_y = (int)mapview_center_y - (minimap_view_rows >> 1);
    minimap_origin_y = int_clamp(minimap_origin_y,0,mapview_layout_height - minimap_view_rows);
  }
  else {
    minimap_origin_y = 0;
  }
  minimap_origin_x = map_wrap_x(map_view_center_x - minimap_view_cols);
  if ((game.rules & 0x8000) != 0) {
    if (minimap_view_cols < map.width) {
      minimap_origin_x = int_clamp(minimap_origin_x,0,mapview_layout_width - minimap_view_cols);
    }
    else {
      minimap_origin_x = 0;
    }
  }
  if ((minimap_origin_x & 1) != 0) {
    minimap_origin_x--;
  }
  if ((minimap_origin_y & 1) != 0) {
    minimap_origin_x++;
  }
  return;
}
#undef map_view_center_x
#undef mapview_center_y
#undef minimap_origin_x
#undef minimap_origin_y
#undef _DAT_0063caf0

/* 00406db8 auto */
#define minimap_origin_x (*(int *)((u8 *)&g.d_0063c814))
#define minimap_origin_y (*(int *)((u8 *)&g.d_0063c810))
#define _DAT_0063caf0 (*(undefined4 *)((u8 *)&g.d_0063caf0))
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl minimap_tile_to_screen(int param_1,uint param_2,iptr param_3,iptr param_4)

{
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = param_1 - minimap_origin_x;
  if (((game.rules & 0x8000) == 0) && (local_8 < 0)) {
    local_8 += map.width;
  }
  *(uint *)param_4 = (param_2 - minimap_origin_y) * minimap_tile_height + _DAT_0063caf0;
  *(int *)param_3 = (local_8 >> 1) * minimap_tile_width + minimap_margin_x;
  if ((param_2 & 1) != 0) {
    *(int *)param_3 = *(int *)param_3 + (minimap_tile_width >> 1);
  }
  *(int *)param_3 = *(int *)param_3 + minimap_client_x;
  *(int *)param_4 = *(int *)param_4 + minimap_client_y;
  return;
}
#undef minimap_origin_x
#undef minimap_origin_y
#undef _DAT_0063caf0
#undef local_8

/* 00406e61 auto */
#define human_civ (*(undefined *)((u8 *)&g.d_006d1da0))
#define map_cursor_x (*(short *)((u8 *)&g.d_0064b1b4))
#define map_cursor_y (*(short *)((u8 *)&g.d_0064b1b0))
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
#define unit_blink_active (*(char *)((u8 *)&g.d_0062804c))
#define unit_blink_phase (*(char *)((u8 *)&g.d_00628054))
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
undefined4 __cdecl minimap_tile_color(int x,int y)

{
  iptr iVar1;
  iptr iVar2;
  int city;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = map_in_bounds(x,y);
  if (iVar1 == 0) {
    local_8 = 10;
  }
  else {
    iVar2 = tile_visible_to(x,y,human_civ);
    if ((iVar2 == 0) && (game.reveal_map == '\0')) {
      local_8 = 10;
    }
    else {
      city = city_at(x,y);
      if ((city < 0) ||
         (((game.reveal_map == '\0' &&
           ((1 << ((byte)human_civ & 0x1f) & (int)(char)cities[city].known_to) == 0)) &&
          ((int)cities[city].owner != (human_civ & 0xffU))))) {
        if ((((unit_blink_active == '\0') || ((moving_units_mode == 0) != (bool)unit_blink_phase)) ||
            (map_cursor_x != x)) || (map_cursor_y != y)) {
          city = tile_is_ocean(x,y);
          if (city == 0) {
            local_8 = 0x30;
          }
          else {
            local_8 = 0x5d;
          }
        }
        else {
          local_8 = 0x29;
        }
      }
      else {
        local_8 = *(undefined4 *)(&civ_secondary_colors + cities[city].owner * 0x10);
      }
    }
  }
  return local_8;
}
#undef human_civ
#undef map_cursor_x
#undef map_cursor_y
#undef moving_units_mode
#undef unit_blink_active
#undef unit_blink_phase
#undef local_8

/* 0040701e auto */
#define mapview_origin_x (*(undefined4 *)((u8 *)&g.d_0066ca90))
#define mapview_origin_y (*(undefined4 *)((u8 *)&g.d_0066ca94))
#define local_24 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_20 (*(undefined4 *)(frame_ + FRAME_OFF(8)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_14 (*(undefined1 (*)[16])(frame_ + FRAME_OFF(20)))
void __cdecl minimap_draw_view_rect(void)

{
  undefined1 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((mapview_margin_x == 0) && (mapview_margin_y == 0)) {
    minimap_tile_to_screen(mapview_origin_x,mapview_origin_y,(iptr)&local_18,(iptr)&local_20);
    minimap_tile_to_screen(mapview_end_x,mapview_end_y,(iptr)&local_1c,(iptr)&local_24);
    if (local_18 < local_1c) {
      rect_set((iptr)local_14,local_18,local_20,local_1c + 1,local_24 + 1);
      gfx_target_frame_rect((iptr)local_14,0x29);
    }
    else {
      rect_set((iptr)local_14,local_1c,local_20,local_18 + 1,local_24 + 1);
      gfx_target_frame_rect((iptr)local_14,0x29);
    }
  }
  return;
}
#undef mapview_origin_x
#undef mapview_origin_y
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14

/* 0040733c auto */
#define game_loop_active (*(char *)((u8 *)&g.d_00628044))
#define minimap_hidden (*(char *)((u8 *)&g.d_00624ee0))
#define minimap_origin_x (*(int *)((u8 *)&g.d_0063c814))
#define minimap_origin_y (*(int *)((u8 *)&g.d_0063c810))
#define _DAT_0063caf0 (*(undefined4 *)((u8 *)&g.d_0063caf0))
#define local_24 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(12)))
#define x2 (*(uint *)(frame_ + FRAME_OFF(20)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_c (*(int *)(frame_ + FRAME_OFF(28)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl minimap_redraw(void)

{
  uint y;
  int iVar2;
  undefined4 uVar3;
  undefined1 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((minimap_hidden == '\0') && (game_loop_active != '\0')) {
    frame_wnd_layout((FrameWindow *)&minimap_window);
    gfx_set_draw_target(ADDR(0x63c818, ((u8 *)&g.d_0063c818)));
    minimap_calc_layout();
    gfx_fill_draw_target(0);
    local_10 = minimap_client_y + _DAT_0063caf0;
    for (local_20 = 0; local_20 < minimap_view_rows; local_20++) {
      y = local_20 + minimap_origin_y;
      if ((y & 1) == 0) {
        local_24 = 0;
      }
      else {
        local_24 = minimap_tile_width >> 1;
      }
      local_c = minimap_client_x + minimap_margin_x + local_24;
      for (local_1c = 0; local_1c < minimap_view_cols; local_1c++) {
        x2 = map_wrap_x(local_1c * 2 + minimap_origin_x);
        if ((x2 & 1) != 0) {
          x2--;
        }
        if ((y & 1) != 0) {
          x2++;
        }
        iVar2 = map_in_bounds(x2,y);
        if (iVar2 != 0) {
          uVar3 = minimap_tile_color(x2,y);
          gfx_target_fill_rect(local_c,local_10,minimap_tile_width,minimap_tile_height,uVar3);
          local_c += minimap_tile_width;
        }
      }
      local_10 += minimap_tile_height;
    }
    win_flush_pending_msgs();
    minimap_draw_view_rect();
    frame_wnd_draw_caption((FrameWindow *)&minimap_window);
    wnd_blit_surface((DibSurface *)&minimap_window);
    win_flush_pending_msgs();
  }
  return;
}
#undef game_loop_active
#undef minimap_hidden
#undef minimap_origin_x
#undef minimap_origin_y
#undef _DAT_0063caf0
#undef local_24
#undef local_20
#undef local_1c
#undef x2
#undef local_10
#undef local_c

/* 004074dc auto */
#define city_turn_processing (*(int *)((u8 *)&g.d_0062edf8))
#define minimap_origin_x (*(int *)((u8 *)&g.d_0063c814))
#define minimap_origin_y (*(int *)((u8 *)&g.d_0063c810))
#define _DAT_0063caf0 (*(undefined4 *)((u8 *)&g.d_0063caf0))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(uint *)(frame_ + FRAME_OFF(8)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl minimap_on_lbuttonup(int param_1,int param_2)

{
  uint uVar1;
  iptr iVar2;
  int iVar3;
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  param_1 -= minimap_client_x;
  param_2 -= minimap_client_y;
  if ((((-1 < param_1) && (-1 < param_2)) && (param_1 < minimap_client_width)) && (param_2 < minimap_client_height))
  {
    if (city_turn_processing == 0) {
      uVar1 = int_clamp(minimap_origin_y + (param_2 - _DAT_0063caf0) / minimap_tile_height,
                                 minimap_origin_y,minimap_origin_y + minimap_view_rows - 1);
      if ((uVar1 & 1) == 0) {
        local_14 = 0;
      }
      else {
        local_14 = minimap_tile_width >> 1;
      }
      iVar2 = int_clamp(((param_1 - (minimap_margin_x + local_14)) / minimap_tile_width) * 2 +
                                 minimap_origin_x,minimap_origin_x,minimap_view_cols * 2 - 2 + minimap_origin_x);
      local_10 = map_wrap_x(iVar2);
      if ((local_10 & 1) != 0) {
        local_10--;
      }
      if ((uVar1 & 1) != 0) {
        local_10++;
      }
      iVar3 = map_in_bounds(local_10,uVar1);
      if (iVar3 != 0) {
        mapview_center_on((C_004083b0_430 *)&map_views,local_10,uVar1);
      }
    }
    else {
      city_window_modal_notice();
    }
  }
  return;
}
#undef city_turn_processing
#undef minimap_origin_x
#undef minimap_origin_y
#undef _DAT_0063caf0
#undef local_14
#undef local_10

/* 00407658 auto */
#define city_turn_processing (*(int *)((u8 *)&g.d_0062edf8))
#define minimap_origin_x (*(int *)((u8 *)&g.d_0063c814))
#define minimap_origin_y (*(int *)((u8 *)&g.d_0063c810))
#define _DAT_0063caf0 (*(undefined4 *)((u8 *)&g.d_0063caf0))
#define local_1c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(uint *)(frame_ + FRAME_OFF(8)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_c (*(int *)(frame_ + FRAME_OFF(20)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl minimap_on_rbuttonup(int param_1,int param_2)

{
  uint uVar1;
  iptr iVar2;
  int iVar3;
  undefined1 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  param_1 -= minimap_client_x;
  param_2 -= minimap_client_y;
  if ((((-1 < param_1) && (-1 < param_2)) && (param_1 < minimap_client_width)) && (param_2 < minimap_client_height))
  {
    if (city_turn_processing == 0) {
      uVar1 = int_clamp(minimap_origin_y + (param_2 - _DAT_0063caf0) / minimap_tile_height,
                                 minimap_origin_y,minimap_origin_y + minimap_view_rows - 1);
      if ((uVar1 & 1) == 0) {
        local_1c = 0;
      }
      else {
        local_1c = minimap_tile_width >> 1;
      }
      iVar2 = int_clamp(((param_1 - (minimap_margin_x + local_1c)) / minimap_tile_width) * 2 +
                                 minimap_origin_x,minimap_origin_x,minimap_view_cols * 2 - 2 + minimap_origin_x);
      local_18 = map_wrap_x(iVar2);
      if ((local_18 & 1) != 0) {
        local_18--;
      }
      if ((uVar1 & 1) != 0) {
        local_18++;
      }
      iVar3 = map_in_bounds(local_18,uVar1);
      if (iVar3 != 0) {
        local_10 = -1;
        for (local_c = 1; local_c < 8; local_c++) {
          if (*(short *)(&map_view_open_flags + local_c * 0x3f0) == 0) {
            local_10 = local_c;
            break;
          }
        }
        if (0 < local_10) {
          mapview_create((C_004083b0_430 *)(&map_views + local_10 * 0x3f0));
          mapview_center_on
                    ((C_004083b0_430 *)(&map_views + local_10 * 0x3f0),local_18,uVar1);
        }
      }
    }
    else {
      city_window_modal_notice();
    }
  }
  return;
}
#undef city_turn_processing
#undef minimap_origin_x
#undef minimap_origin_y
#undef _DAT_0063caf0
#undef local_1c
#undef local_18
#undef local_10
#undef local_c

/* 0040785b auto */
#define frame_border_width (*(int *)((u8 *)&g.d_0063359c))
#define frame_caption_height (*(int *)((u8 *)&g.d_00633598))
#define main_frame_nonclient_width (*(int *)((u8 *)&g.d_006acbb0))
#define local_18 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl minimap_calc_rect(void)

{
  int iVar1;
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_client_width((WndBase *)&main_frame_wnd);
  local_14 = 0xa0;
  local_18 = 100;
  if ((1000 < main_frame_nonclient_width + iVar1) && (local_14 = 0xf0, DAT_00628060 != 0)) {
    local_18 = 0x96;
  }
  if (local_18 < map.height) {
    local_18 = (int)map.height;
  }
  local_14 += frame_border_width * 2;
  local_10 = 0;
  if (DAT_00628060 != 0) {
    local_10 = DAT_0064bcf4 + 1;
  }
  rect_set_xywh(ADDR(0x655324, ((u8 *)&g.d_00655324)),iVar1 - (sys_dlgframe_w2 + local_14),local_10,local_14 + sys_dlgframe_w2,
                     local_18 + frame_border_width + frame_caption_height + sys_dlgframe_h2);
  return;
}
#undef frame_border_width
#undef frame_caption_height
#undef main_frame_nonclient_width
#undef local_18
#undef local_14
#undef local_10

/* 0040795a auto */
void __cdecl minimap_on_size(void)

{
  wnd_get_rect_in_parent((WndBase *)&minimap_wnd,ADDR(0x655324, ((u8 *)&g.d_00655324)));
  return;
}

/* 00407980 auto */
void __cdecl minimap_on_move(void)

{
  wnd_get_rect_in_parent((WndBase *)&minimap_wnd,ADDR(0x655324, ((u8 *)&g.d_00655324)));
  return;
}

/* 004079a6 auto */
#define minimap_hidden (*(undefined1 *)((u8 *)&g.d_00624ee0))
#define minimap_wnd_rect_top (*(undefined4 *)((u8 *)&g.d_00655328))
#define saved_layout_valid (*(int *)((u8 *)&g.d_00655280))
#define turn_resume_civ (*(char *)((u8 *)&g.d_00628048))
void __cdecl minimap_window_create(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  
  minimap_hidden = 0;
  if ((turn_resume_civ == '\0') || (saved_layout_valid == 0)) {
    minimap_calc_rect();
  }
  uVar9 = 0;
  uVar8 = 0;
  uVar7 = 6;
  iVar1 = rect_height(ADDR(0x655324, ((u8 *)&g.d_00655324)));
  iVar1 -= sys_dlgframe_h2;
  iVar2 = rect_width(ADDR(0x655324, ((u8 *)&g.d_00655324)));
  iVar2 -= sys_dlgframe_w2;
  uVar4 = 6;
  uVar5 = minimap_wnd_rect;
  uVar6 = minimap_wnd_rect_top;
  uVar3 = label_string(*(undefined4 *)(label_string_ids + 0x18));
  frame_wnd_create
            ((FrameWindow *)&minimap_window,uVar3,uVar4,uVar5,uVar6,iVar2,iVar1,uVar7,uVar8,uVar9);
  wnd_set_min_size((C_00408010_b8 *)&minimap_wnd,0x28,0x19);
  wnd_set_redraw_callback((SurfaceWindow *)&minimap_window,ADDR(0x402581, minimap_redraw));
  wnd_set_lbuttonup_handler((C_00408130 *)&minimap_wnd_handlers,ADDR(0x4022de, minimap_on_lbuttonup));
  wnd_set_rbuttonup_handler((C_00408130 *)&minimap_wnd_handlers,ADDR(0x401942, minimap_on_rbuttonup));
  wnd_set_keydown_handler((C_00408130 *)&minimap_wnd_handlers,ADDR(0x402cd4, map_window_key));
  wnd_set_char_handler((C_00408130 *)&minimap_wnd_handlers,ADDR(0x401e56, map_window_ascii));
  wnd_set_cursor((WndBase *)&minimap_wnd,0x1ff);
  wnd_set_icon((WndBase *)&minimap_wnd,1);
  wnd_set_minimize_handler((C_00408130 *)&minimap_wnd_handlers,ADDR(0x403d05, minimap_on_minimize));
  wnd_set_restore_handler((C_00408130 *)&minimap_wnd_handlers,ADDR(0x401956, minimap_on_restore));
  wnd_set_close_handler((C_00408130 *)&minimap_wnd_handlers,ADDR(0x40322e, minimap_on_close));
  wnd_set_size_handler((C_00408130 *)&minimap_wnd_handlers,ADDR(0x4012a8, minimap_on_size));
  wnd_set_move_handler((C_00408130 *)&minimap_wnd_handlers,ADDR(0x403931, minimap_on_move));
  wnd_repaint((SurfaceWindow *)&minimap_window);
  if (game.multiplayer != 1) {
    window_show((C_004083b0_4 *)&minimap_window);
  }
  return;
}
#undef minimap_hidden
#undef minimap_wnd_rect_top
#undef saved_layout_valid
#undef turn_resume_civ

/* 00407b31 auto */
#define minimap_hidden (*(undefined1 *)((u8 *)&g.d_00624ee0))
void __cdecl minimap_window_destroy(void)

{
  minimap_hidden = 1;
  wnd_destroy_with_surface((DibSurface *)&minimap_window);
  return;
}
#undef minimap_hidden

/* 00410302 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define map_cursor_x (*(short *)((u8 *)&g.d_0064b1b4))
#define map_cursor_y (*(short *)((u8 *)&g.d_0064b1b0))
void __thiscall mapview_redraw_cursor_tile(C_004083b0_430 *this)

{
  mapview_redraw_area(this,(int)map_cursor_x,(int)map_cursor_y,0,human_civ,1);
  return;
}
#undef human_civ
#undef map_cursor_x
#undef map_cursor_y

/* 0041033a auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl mapviews_redraw_cursor(void)

{
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; local_8 < 8; local_8++) {
    if ((local_8 == 0) || (*(short *)(&map_view_open_flags + local_8 * 0x3f0) != 0)) {
      mapview_redraw_cursor_tile((C_004083b0_430 *)(&map_views + local_8 * 0x3f0));
    }
  }
  return;
}
#undef local_8

/* 004103ae auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define this2 (*(C_004083b0_430 * *)(frame_ + FRAME_OFF(0)))
void __cdecl mapview_on_redraw(void)

{
  int iVar1;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  city_window_bring_to_top((C_004083b0_4 *)&city_window);
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    this2 = (C_004083b0_430 *)0x0;
  }
  else {
    this2 = (C_004083b0_430 *)(iVar1 - 0x48);
  }
  mapview_redraw(this2,human_civ,1);
  return;
}
#undef human_civ
#undef this2

/* 00410402 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define unit_blink_active (*(undefined1 *)((u8 *)&g.d_0062804c))
void __thiscall mapview_center_on(C_004083b0_430 *this,iptr param_1,undefined4 param_2)

{
  undefined1 uVar1;
  undefined4 uVar2;
  
  uVar2 = map_wrap_x(param_1);
  *(short *)&this->field_2e0 = (short)uVar2;
  *(undefined2 *)((int)&this->field_2e0 + 2) = (undefined2)param_2;
  uVar1 = unit_blink_active;
  unit_blink_active = 0;
  mapview_redraw(this,human_civ,1);
  unit_blink_active = uVar1;
  return;
}
#undef human_civ
#undef unit_blink_active

/* 00410464 auto */
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
#define unit_blink_phase (*(undefined1 *)((u8 *)&g.d_00628054))
#define unit_blink_skip_tick (*(undefined1 *)((u8 *)&g.d_0062805c))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
int __thiscall mapview_scroll_if_near_edge(C_004083b0_430 *this,int param_1,int param_2)

{
  uptr uVar1;
  uptr uVar2;
  u32 uVar3;
  u32 uVar4;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 0;
  uVar1 = this->field_2e8;
  uVar2 = this->field_2ec;
  if ((((game.rules & 0x8000) == 0) && (param_1 <= (int)(this->field_2f8 * 2))) &&
     ((int)((int)map.width + this->field_2f8 * -2) <= (int)uVar1)) {
    param_1 += map.width;
  }
  uVar3 = this->field_300;
  uVar4 = this->field_2f4;
  if (this->field_330 == 0) {
    if ((game.rules & 0x8000) != 0) {
      param_1 = int_clamp(param_1,2,map.width - 3);
    }
    if ((param_1 <= (int)(uVar1 + 1)) || ((int)(uVar3 * 2 + uVar1 - 3) <= param_1)) {
      local_c = 1;
    }
  }
  if ((this->field_334 == 0) &&
     ((param_2 = int_clamp(param_2,2,map.height - 3), param_2 <= (int)(uVar2 + 1) ||
      ((int)(uVar4 - 1) <= param_2)))) {
    local_c = 1;
  }
  if (local_c != 0) {
    unit_blink_skip_tick = 1;
    unit_blink_phase = moving_units_mode == 0;
    mapview_center_on(this,param_1,param_2);
  }
  return local_c;
}
#undef moving_units_mode
#undef unit_blink_phase
#undef unit_blink_skip_tick
#undef local_c

/* 004105f8 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define map_redraw_busy (*(undefined4 *)((u8 *)&g.d_006ad908))
#define local_c (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
uint __cdecl mapviews_ensure_visible(undefined4 param_1,undefined4 param_2,iptr param_3)

{
  ushort uVar1;
  uint uVar2;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 1;
  map_redraw_busy = 1;
  if (param_3 < 0) {
    uVar1 = 3;
  }
  else if (human_civ == param_3) {
    uVar1 = 1;
  }
  else {
    uVar1 = 2;
  }
  for (local_8 = 0; local_8 < 8; local_8++) {
    if ((local_8 == 0) || (*(short *)(&map_view_open_flags + local_8 * 0x3f0) != 0)) {
      if ((uVar1 & *(ushort *)(&mapview_track_moves + local_8 * 0x3f0)) == 0) {
        local_c = 0;
      }
      else {
        uVar2 = mapview_scroll_if_near_edge
                          ((C_004083b0_430 *)(&map_views + local_8 * 0x3f0),param_1,param_2);
        local_c = local_c & uVar2;
      }
    }
  }
  map_redraw_busy = 0;
  return local_c;
}
#undef human_civ
#undef map_redraw_busy
#undef local_c
#undef local_8

/* 004106fd auto */
#define local_18 (*(int (*)[2])(frame_ + FRAME_OFF(0)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
int __thiscall
mapview_point_unit_dir
          (C_004083b0_430 *this,int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  short sVar1;
  short sVar2;
  int iVar3;
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  mapview_tile_to_screen(this,(iptr)local_18,(iptr)&local_8,param_3,param_4);
  if (((short)param_1 < local_18[0]) || ((short)param_2 < local_8)) {
    iVar3 = 8;
  }
  else if (((int)(short)param_1 < (int)(this->total_tax + local_18[0])) &&
          ((int)(short)param_2 < (int)(this->total_science + local_8))) {
    local_c = (short)param_1 - local_18[0];
    local_10 = (short)param_2 - local_8;
    sVar1 = (short)param_1 - (short)this->client_x;
    sVar2 = (short)param_2 - (short)this->client_y;
    if ((sVar1 < 0) || (sVar2 < 0)) {
      iVar3 = 8;
    }
    else if (((int)sVar1 < (int)this->client_width) && ((int)sVar2 < (int)this->client_height)) {
      iVar3 = surface_get_pixel((DibSurface *)&this->field_3a8,local_c,local_10);
      iVar3 = iVar3 - 10 >> 4;
    }
    else {
      iVar3 = 8;
    }
  }
  else {
    iVar3 = 8;
  }
  return iVar3;
}
#undef local_18
#undef local_10
#undef local_c
#undef local_8

/* 00410835 auto */
#define city_turn_processing (*(int *)((u8 *)&g.d_0062edf8))
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
#define x2 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(4)))
#define y2 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define civ (*(int *)(frame_ + FRAME_OFF(12)))
#define local_10 (*(uptr *)(frame_ + FRAME_OFF(16)))
#define local_c (*(C_004083b0_430 * *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(24)))
void __cdecl mapview_on_mousemove(int param_1,int param_2)

{
  iptr iVar1;
  int iVar2;
  undefined1 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_c = (C_004083b0_430 *)0x0;
  }
  else {
    local_c = (C_004083b0_430 *)(iVar1 - 0x48);
  }
  if ((city_turn_processing == 0) && (local_c->field_358 != 0x1fe)) {
    iVar2 = ui_paradrop_cursor_active();
    if (iVar2 == 0) {
      local_10 = 0x201;
      if ((((((byte)game.game_options & 0x80) != 0) && (moving_units_mode == 1)) &&
          (unit = (iptr)game.active_unit, -1 < unit)) &&
         ((local_8 = mapview_point_unit_dir
                               (local_c,param_1,param_2,(int)units[unit].x,
                                (int)units[unit].y), -1 < local_8 && (local_8 < 8)))) {
        local_10 = (local_8 + 1U & 7) + 500;
      }
    }
    else {
      local_10 = 0x202;
      unit = (iptr)game.active_unit;
      iVar2 = mapview_screen_to_tile
                        ((MapViewHitView *)local_c,(iptr)&x2,(iptr)&y2,param_1,param_2);
      if (iVar2 != 0) {
        return;
      }
      iVar2 = map_in_bounds(x2,y2);
      if (iVar2 == 0) {
        return;
      }
      iVar2 = map_distance(x2,y2,(int)units[unit].x,(int)units[unit].y);
      if ((int)(uint)cosmic.paradrop_range < iVar2) {
        local_10 = 0x203;
      }
      else {
        iVar2 = tile_is_ocean(x2,y2);
        if (iVar2 == 0) {
          civ = tile_unit_owner(x2,y2);
          if ((-1 < civ) && (units[unit].owner != civ)) {
            local_10 = 0x203;
          }
        }
        else {
          local_10 = 0x203;
        }
      }
    }
    if (local_c->field_358 != local_10) {
      local_c->field_358 = local_10;
      wnd_set_cursor_now((WndCursorView *)local_c->pad_48,local_10,1);
    }
  }
  return;
}
#undef city_turn_processing
#undef moving_units_mode
#undef x2
#undef unit
#undef y2
#undef civ
#undef local_10
#undef local_c
#undef local_8

/* 00410a64 auto */
#define mapview_cursor_id (*(undefined4 *)((u8 *)&g.d_0066cb00))
#define mapview_drag_hold_timer (*(int *)((u8 *)&g.d_00624f54))
void __cdecl mapview_cancel_drag(void)

{
  if (-1 < mapview_drag_hold_timer) {
    game_timer_destroy(mapview_drag_hold_timer);
    mapview_drag_hold_timer = -1;
  }
  if ((-1 < mapview_drag_view_index) && ((&mapview_cursor_id)[mapview_drag_view_index * 0xfc] == 0x1fe)) {
    (&mapview_cursor_id)[mapview_drag_view_index * 0xfc] = 0x201;
    wnd_set_cursor_now((WndCursorView *)(&map_view_wnds + mapview_drag_view_index * 0x3f0),0x201,1);
    wnd_release_capture((WndBase *)(&map_view_wnds + mapview_drag_view_index * 0x3f0));
  }
  mapview_drag_view_index = 0xffffffff;
  return;
}
#undef mapview_cursor_id
#undef mapview_drag_hold_timer

/* 00410b23 auto */
#define mapview_cursor_id (*(undefined4 *)((u8 *)&g.d_0066cb00))
#define mapview_drag_hold_timer (*(int *)((u8 *)&g.d_00624f54))
void __cdecl mapview_drag_hold_expired(void)

{
  if (-1 < mapview_drag_hold_timer) {
    game_timer_destroy(mapview_drag_hold_timer);
    mapview_drag_hold_timer = -1;
    if (-1 < mapview_drag_view_index) {
      (&mapview_cursor_id)[mapview_drag_view_index * 0xfc] = 0x1fe;
      wnd_set_cursor_now((WndCursorView *)(&map_view_wnds + mapview_drag_view_index * 0x3f0),0x1fe,1);
      wnd_set_capture((WndBase *)(&map_view_wnds + mapview_drag_view_index * 0x3f0));
    }
  }
  return;
}
#undef mapview_cursor_id
#undef mapview_drag_hold_timer

/* 00410bc3 auto */
#define city_turn_processing (*(int *)((u8 *)&g.d_0062edf8))
#define mapview_cursor_id (*(undefined4 *)((u8 *)&g.d_0066cb00))
#define mapview_drag_hold_timer (*(undefined4 *)((u8 *)&g.d_00624f54))
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl mapview_on_lbuttondown(void)

{
  SHORT SVar1;
  iptr iVar2;
  int iVar3;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((city_turn_processing == 0) && ((game.multiplayer == '\0' || (ui_input_busy == 0)))) {
    ui_input_busy = 1;
    iVar2 = wnd_get_active_child();
    if (iVar2 == 0) {
      local_8 = 0;
    }
    else {
      local_8 = iVar2 - 0x48;
    }
    mapview_cancel_drag();
    if ((moving_units_mode == 1) && (iVar3 = ui_paradrop_cursor_active(), iVar3 == 0)) {
      mapview_drag_view_index = *(int *)(local_8 + 0x2d8);
      SVar1 = GetAsyncKeyState(0x10);
      if ((char)((ushort)SVar1 >> 8) == '\0') {
        mapview_drag_hold_timer = game_timer_create(ADDR(0x4025cc, mapview_drag_hold_expired),400,1);
      }
      else {
        (&mapview_cursor_id)[mapview_drag_view_index * 0xfc] = 0x1fe;
        wnd_set_cursor_now((WndCursorView *)(&map_view_wnds + mapview_drag_view_index * 0x3f0),0x1fe,1)
        ;
        wnd_set_capture((WndBase *)(&map_view_wnds + mapview_drag_view_index * 0x3f0));
      }
    }
    ui_input_busy = 0;
  }
  return;
}
#undef city_turn_processing
#undef mapview_cursor_id
#undef mapview_drag_hold_timer
#undef moving_units_mode
#undef local_8

/* 00410cfa auto */
#define city_turn_processing (*(int *)((u8 *)&g.d_0062edf8))
#define mapview_drag_hold_timer (*(int *)((u8 *)&g.d_00624f54))
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl mapview_on_lbuttonup_any(void)

{
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((city_turn_processing == 0) && ((game.multiplayer == '\0' || (ui_input_busy == 0)))) {
    ui_input_busy = 1;
    local_8 = wnd_get_active_child();
    if (local_8 == 0) {
      local_8 = 0;
    }
    else {
      local_8 -= 0x48;
    }
    if (-1 < mapview_drag_hold_timer) {
      mapview_cancel_drag();
    }
    wnd_release_capture((WndBase *)(local_8 + 0x48));
    ui_input_busy = 0;
  }
  return;
}
#undef city_turn_processing
#undef mapview_drag_hold_timer
#undef local_8

/* 00410e46 auto */
#define mapview_cursor_id (*(undefined4 *)((u8 *)&g.d_0066cb00))
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl mapviews_set_paradrop_cursor(void)

{
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; local_8 < 8; local_8++) {
    if ((local_8 == 0) || (*(short *)(&map_view_open_flags + local_8 * 0x3f0) != 0)) {
      (&mapview_cursor_id)[local_8 * 0xfc] = 0x202;
      wnd_set_cursor_now((WndCursorView *)(&map_view_wnds + local_8 * 0x3f0),0x202,1);
    }
  }
  return;
}
#undef mapview_cursor_id
#undef local_8

/* 00410ed8 auto */
#define mapview_cursor_id (*(undefined4 *)((u8 *)&g.d_0066cb00))
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl mapviews_reset_cursor(void)

{
  int iVar1;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = ui_paradrop_cursor_active();
  if (iVar1 != 0) {
    for (local_8 = 0; local_8 < 8; local_8++) {
      if ((local_8 == 0) || (*(short *)(&map_view_open_flags + local_8 * 0x3f0) != 0)) {
        (&mapview_cursor_id)[local_8 * 0xfc] = 0x201;
        wnd_set_cursor_now((WndCursorView *)(&map_view_wnds + local_8 * 0x3f0),0x201,1);
      }
    }
  }
  return;
}
#undef mapview_cursor_id
#undef local_8

/* 004116c1 auto */
void __cdecl mapview_on_lbuttonup(undefined4 param_1,undefined4 param_2)

{
  map_window_click(param_1,param_2,0);
  return;
}

/* 004116e3 auto */
void __cdecl mapview_on_rbuttonup(undefined4 param_1,undefined4 param_2)

{
  map_window_click(param_1,param_2,1);
  return;
}

/* 004132b7 auto */
#define local_14 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
void __cdecl mapview_calc_rect(void)

{
  int iVar1;
  int iVar2;
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_client_width((WndBase *)&main_frame_wnd);
  iVar2 = rect_width(ADDR(0x655324, ((u8 *)&g.d_00655324)));
  local_14 = wnd_client_height((WndBase *)&main_frame_wnd);
  local_14++;
  local_c = 0;
  if (DAT_00628060 != 0) {
    local_c = DAT_0064bcf4 + 1;
    local_14 -= (DAT_0064bcf4 + 1);
  }
  rect_set_xywh(ADDR(0x6552a4, ((u8 *)&g.d_006552a4)),0,local_c,iVar1 - iVar2,local_14);
  return;
}
#undef local_14
#undef local_c

/* 00413350 auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
bool __cdecl mapview_on_close(void)

{
  iptr iVar1;
  bool bVar1;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar1 - 0x48;
  }
  bVar1 = *(int *)(local_8 + 0x2d8) == 0;
  if (bVar1) {
    wnd_minimize((WndBase *)(local_8 + 0x48));
  }
  else {
    *(undefined2 *)(local_8 + 0x2dc) = 0;
  }
  return !bVar1;
}
#undef local_8

/* 004133c2 auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl mapview_on_size(void)

{
  iptr iVar1;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar1 - 0x48;
  }
  wnd_get_rect_in_parent
            ((WndBase *)(local_8 + 0x48),
             (iptr)(&map_view_saved_rects + *(int *)(local_8 + 0x2d8) * 0x10));
  return;
}
#undef local_8

/* 0041341c auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl mapview_on_move(void)

{
  iptr iVar1;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar1 - 0x48;
  }
  wnd_get_rect_in_parent
            ((WndBase *)(local_8 + 0x48),
             (iptr)(&map_view_saved_rects + *(int *)(local_8 + 0x2d8) * 0x10));
  return;
}
#undef local_8

/* 00413476 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(8)))
void __thiscall mapview_update_title(FrameWindow *this)

{
  bool bVar1;
  iptr iVar2;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = (uint)((this->field_2dc & 0x10000) != 0);
  if ((this->field_2dc & 0x20000) != 0) {
    local_8 += 2;
  }
  text_clear();
  if (this->field_2d8 == 0) {
    if (game_language != 1) {
      iVar2 = civ_get_adjective(human_civ);
      text_append_str(iVar2);
      if (game_language == 2) {
        text_append(ADDR(0x625090, ((u8 *)&g.d_00625090)));
      }
      text_append_space();
    }
    bVar1 = false;
    for (local_c = 1; local_c < 8; local_c++) {
      if (*(short *)(&map_view_open_flags + local_c * 0x3f0) != 0) {
        bVar1 = true;
        break;
      }
    }
  }
  else {
    bVar1 = true;
  }
  text_append_label(4);
  if (bVar1) {
    text_append_colon();
    text_append_label(local_8 + 300);
  }
  frame_wnd_set_caption(this,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  return;
}
#undef human_civ
#undef local_c
#undef local_8

/* 004135ab auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define this2 (*(C_004083b0_430 * *)(frame_ + FRAME_OFF(0)))
void __cdecl mapview_on_caption_button(undefined4 param_1)

{
  iptr iVar1;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((game.multiplayer == '\0') || (ui_input_busy == 0)) {
    ui_input_busy = 1;
    iVar1 = wnd_get_active_child();
    if (iVar1 == 0) {
      this2 = (C_004083b0_430 *)0x0;
    }
    else {
      this2 = (C_004083b0_430 *)(iVar1 - 0x48);
    }
    switch(param_1) {
    case 1:
      *(undefined2 *)&this2->field_2dc = 0;
      wnd_destroy_with_surface((DibSurface *)this2);
      mapview_update_title((FrameWindow *)&map_views);
      wnd_repaint((SurfaceWindow *)&map_views);
      break;
    case 2:
      if ((short)this2->field_2e4 < 8) {
        *(short *)&this2->field_2e4 = (short)this2->field_2e4 + 1;
        mapview_redraw(this2,human_civ,1);
      }
      break;
    case 3:
      if (-7 < (short)this2->field_2e4) {
        *(short *)&this2->field_2e4 = (short)this2->field_2e4 - 1;
        mapview_redraw(this2,human_civ,1);
      }
      break;
    case 4:
      *(ushort *)((int)&this2->field_2dc + 2) = *(short *)((int)&this2->field_2dc + 2) + 1U & 3;
      mapview_update_title((FrameWindow *)this2);
      mapview_redraw(this2,human_civ,1);
    }
    ui_input_busy = 0;
  }
  return;
}
#undef human_civ
#undef this2

/* 00413717 auto */
#define saved_layout_valid (*(int *)((u8 *)&g.d_00655280))
#define turn_resume_civ (*(char *)((u8 *)&g.d_00628048))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
void __thiscall mapview_create(C_004083b0_430 *this)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  mapview_init_state(this,this->field_2d8);
  if ((turn_resume_civ == '\0') || (saved_layout_valid == 0)) {
    *(undefined2 *)&this->field_2e4 = 0;
    if (999 < screen_width) {
      *(undefined2 *)&this->field_2e4 = 2;
    }
    if (this->field_2d8 == 0) {
      mapview_calc_rect();
    }
  }
  if (this->field_2d8 == 0) {
    *(undefined2 *)((int)&this->field_2dc + 2) = 3;
  }
  else {
    *(undefined2 *)((int)&this->field_2dc + 2) = 2;
  }
  if ((this->field_2d8 == 0) || ((short)this->field_2dc != 0)) {
    local_8 = *(int *)(&map_view_saved_rects + this->field_2d8 * 0x10);
    local_c = *(int *)(&map_view_saved_rect_tops + this->field_2d8 * 0x10);
    local_10 = rect_width((iptr)(&map_view_saved_rects + this->field_2d8 * 0x10));
    local_10 -= sys_dlgframe_w2;
    local_14 = rect_height((iptr)(&map_view_saved_rects + this->field_2d8 * 0x10));
    local_14 -= sys_dlgframe_h2;
  }
  else {
    local_8 = this->field_2d8 * 0x28;
    local_c = this->field_2d8 * 0x28;
    local_10 = 500;
    local_14 = 300;
    rect_set_xywh((iptr)(&map_view_saved_rects + this->field_2d8 * 0x10),local_8,local_c,
                       sys_dlgframe_w2 + 500,sys_dlgframe_h2 + 300);
  }
  *(undefined2 *)&this->field_2dc = 1;
  uVar5 = 0;
  uVar4 = 0;
  uVar3 = 6;
  uVar2 = 6;
  uVar1 = label_string(*(undefined4 *)(label_string_ids + 0x10));
  frame_wnd_create
            ((FrameWindow *)this,uVar1,uVar2,local_8,local_c,local_10,local_14,uVar3,uVar4,uVar5)
  ;
  wnd_set_min_size((C_00408010_b8 *)this->pad_48,0x100,0x80);
  wnd_set_redraw_callback((SurfaceWindow *)this,ADDR(0x402315, mapview_on_redraw));
  wnd_set_lbuttonup_handler((C_00408130 *)(this->pad_48 + 0x10),ADDR(0x4030c6, mapview_on_lbuttonup));
  wnd_set_rbuttonup_handler((C_00408130 *)(this->pad_48 + 0x10),ADDR(0x4018d9, mapview_on_rbuttonup));
  wnd_set_lbuttondown_handler((WndHandlersMouseSetView *)(this->pad_48 + 0x10),ADDR(0x402d9c, mapview_on_lbuttondown));
  wnd_set_lbuttonup_any_handler((WndHandlersMouseSetView *)(this->pad_48 + 0x10),ADDR(0x401a7d, mapview_on_lbuttonup_any));
  wnd_set_mousemove_handler((WndHandlersMouseSetView *)(this->pad_48 + 0x10),ADDR(0x4014e7, mapview_on_mousemove));
  wnd_set_dblclick_handler((WndHandlersMouseSetView *)(this->pad_48 + 0x10),ADDR(0x40146f, map_window_double_click));
  wnd_set_char_handler((C_00408130 *)(this->pad_48 + 0x10),ADDR(0x401e56, map_window_ascii));
  wnd_set_keydown_handler((C_00408130 *)(this->pad_48 + 0x10),ADDR(0x402cd4, map_window_key));
  wnd_set_close_handler((C_00408130 *)(this->pad_48 + 0x10),ADDR(0x40235b, mapview_on_close));
  wnd_set_size_handler((C_00408130 *)(this->pad_48 + 0x10),ADDR(0x403b43, mapview_on_size));
  wnd_set_move_handler((C_00408130 *)(this->pad_48 + 0x10),ADDR(0x402653, mapview_on_move));
  mapview_update_title((FrameWindow *)this);
  if (this->field_2d8 != 0) {
    frame_wnd_add_caption_button((C_004083b0_208 *)this,ADDR(0x645120, ((u8 *)&g.d_00645120)),1);
  }
  frame_wnd_add_caption_button((C_004083b0_208 *)this,ADDR(0x648820, ((u8 *)&g.d_00648820)),2);
  frame_wnd_add_caption_button((C_004083b0_208 *)this,ADDR(0x647788, ((u8 *)&g.d_00647788)),3);
  if (this->field_2d8 != 0) {
    frame_wnd_add_caption_button((C_004083b0_208 *)this,ADDR(0x647348, ((u8 *)&g.d_00647348)),4);
  }
  wnd_set_caption_button_handler((FrameWindow *)this,ADDR(0x403cd8, mapview_on_caption_button));
  wnd_repaint((SurfaceWindow *)this);
  if (game.multiplayer != 1) {
    window_show((C_004083b0_4 *)this);
  }
  if (this->field_2d8 != 0) {
    mapview_update_title((FrameWindow *)&map_views);
    wnd_repaint((SurfaceWindow *)&map_views);
  }
  return;
}
#undef saved_layout_valid
#undef turn_resume_civ
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 00413a90 auto */
#define main_view_timer_shown (*(undefined4 *)((u8 *)&g.d_0066c988))
#define mp_turn_time_limit_ms (*(int *)((u8 *)&g.d_00654b70))
#define timer_alt_kind_request (*(undefined4 *)((u8 *)&g.d_00637ef8))
#define turn_resume_civ (*(char *)((u8 *)&g.d_00628048))
#define _DAT_0066c98c (*(undefined4 *)((u8 *)&g.d_0066c98c))
#define _DAT_0066ca84 (*(undefined4 *)((u8 *)&g.d_0066ca84))
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl mapviews_create_all(void)

{
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; local_8 < 8; local_8++) {
    mapview_init_state((C_004083b0_430 *)(&map_views + local_8 * 0x3f0),local_8);
    if (turn_resume_civ == '\0') {
      if (local_8 == 0) {
        _DAT_0066ca84 = 1;
      }
      else {
        *(undefined2 *)(&map_view_open_flags + local_8 * 0x3f0) = 0;
      }
    }
    if ((local_8 == 0) || (*(short *)(&map_view_open_flags + local_8 * 0x3f0) != 0)) {
      mapview_create((C_004083b0_430 *)(&map_views + local_8 * 0x3f0));
    }
  }
  _DAT_0066c98c = 1;
  if (mp_turn_time_limit_ms != 0) {
    main_view_timer_shown = 1;
  }
  timer_alt_kind_request = 1;
  unit_blink_timer = game_timer_create(ADDR(0x40364d, unit_blink_timer_tick),0x96,0xffffffff);
  eot_blink_timer = game_timer_create(ADDR(0x402540, eot_blink_timer_tick),500,0xffffffff);
  timer_alt_kind_request = 0;
  return;
}
#undef main_view_timer_shown
#undef mp_turn_time_limit_ms
#undef timer_alt_kind_request
#undef turn_resume_civ
#undef _DAT_0066c98c
#undef _DAT_0066ca84
#undef local_8

/* 00413bd1 auto */
#define timer_alt_kind_request (*(undefined4 *)((u8 *)&g.d_00637ef8))
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl mapviews_destroy_all(void)

{
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  timer_alt_kind_request = 1;
  game_timer_destroy(unit_blink_timer);
  game_timer_destroy(eot_blink_timer);
  timer_alt_kind_request = 0;
  for (local_8 = 0; local_8 < 8; local_8++) {
    if ((local_8 == 0) || (*(short *)(&map_view_open_flags + local_8 * 0x3f0) != 0)) {
      wnd_destroy_with_surface((DibSurface *)(&map_views + local_8 * 0x3f0));
    }
  }
  return;
}
#undef timer_alt_kind_request
#undef local_8

/* 0046ab30 auto */
void * __thiscall clickmap_ctor(void *this)

{
  return this;
}

/* 0046ab49 auto */
void __thiscall clickmap_dtor(void *this)

{
  return;
}

/* 0046ab5f auto */
/* Library Function - Single Match
    public: void __thiscall CRichEditDoc::InvalidateObjectCache(void)
   
   Library: Visual Studio 1998 Debug */

void __thiscall clickmap_clear(ClickMapClearView *this)

{
  this->region_count = 0;
  return;
}

/* 0046ab82 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall clickmap_remove_at(ClickMapRemoveView *this,int param_1)

{
  int iVar1;
  u8 *puVar2;
  u8 *puVar3;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = param_1; local_8 < (int)(this->entry_count - 1); local_8++) {
    puVar2 = this->pad_0 + local_8 * 0x18 + 0x18;
    puVar3 = this->pad_0 + local_8 * 0x18;
    for (iVar1 = 6; iVar1 != 0; iVar1--) {
      *(undefined4 *)puVar3 = *(undefined4 *)puVar2;
      puVar2 += 4;
      puVar3 += 4;
    }
  }
  this->entry_count--;
  return;
}
#undef local_8

/* 0046ac89 auto */
#define local_8 (*(u32 *)(frame_ + FRAME_OFF(0)))
void __thiscall clickmap_remove_by_id(ClickMapRemoveView *this,int param_1)

{
  u32 uVar1;
  iptr iVar2;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  uVar1 = this->entry_count;
  while (local_8 = uVar1 - 1, -1 < (int)local_8) {
    iVar2 = uVar1 * 0x18;
    uVar1 = local_8;
    if (*(int *)(this->pad_0 + iVar2 - 8) == param_1) {
      clickmap_remove_at(this,local_8);
    }
  }
  return;
}
#undef local_8

/* 0046ace7 auto */
#define local_8 (*(u32 *)(frame_ + FRAME_OFF(0)))
u32 __thiscall
clickmap_add
          (ClickMap *this,iptr param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
          iptr param_5,iptr param_6)

{
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  if ((int)this->entry_count < 200) {
    local_8 = this->entry_count;
    this->entry_count++;
    rect_set_xywh((iptr)(this->pad_0 + local_8 * 0x18),param_3,param_4,param_5,param_6);
    *(iptr *)(this->pad_0 + local_8 * 0x18 + 0x14) = param_1;
    *(undefined4 *)(this->pad_0 + local_8 * 0x18 + 0x10) = param_2;
  }
  return local_8;
}
#undef local_8

/* 0046ad85 auto */
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
int __thiscall
clickmap_hit_test(ClickMapHitTestView *this,int param_1,int param_2,iptr param_3,iptr param_4)

{
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = -1;
  local_8 = 0;
  do {
    if ((int)this->region_count <= local_8) {
LAB_0046ae34:
      if (-1 < local_c) {
        if (param_3 != 0) {
          *(undefined4 *)param_3 = *(undefined4 *)(this->pad_0 + local_c * 0x18 + 0x14);
        }
        if (param_4 != 0) {
          *(undefined4 *)param_4 = *(undefined4 *)(this->pad_0 + local_c * 0x18 + 0x10);
        }
      }
      return local_c;
    }
    if ((((*(int *)(this->pad_0 + local_8 * 0x18) <= param_1) &&
         (param_1 < *(int *)(this->pad_0 + local_8 * 0x18 + 8))) &&
        (*(int *)(this->pad_0 + local_8 * 0x18 + 4) <= param_2)) &&
       (param_2 < *(int *)(this->pad_0 + local_8 * 0x18 + 0xc))) {
      local_c = local_8;
      goto LAB_0046ae34;
    }
    local_8++;
  } while( true );
}
#undef local_c
#undef local_8

/* 00472b0a auto */
#define mapview_zoom (*(short *)((u8 *)&g.d_0066ca8c))
#define local_6c (*(undefined4 *)(frame_ + FRAME_OFF(4)))
#define local_68 (*(undefined4 *)(frame_ + FRAME_OFF(8)))
#define local_64 (*(char (*)[80])(frame_ + FRAME_OFF(12)))
#define local_14 (*(undefined1 (*)[16])(frame_ + FRAME_OFF(92)))
void __cdecl mapview_draw_tile_number(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  iptr iVar2;
  iptr iVar3;
  undefined1 frame_[FRAME_OFF(112)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = mapview_tile_in_view((C_004083b0_430 *)&map_views,param_1,param_2);
  if (iVar1 != 0) {
    mapview_tile_to_screen
              ((C_004083b0_430 *)&map_views,(iptr)&local_68,(iptr)&local_6c,param_1,param_2);
    iVar2 = gfx_zoom_scale(0x40,(int)mapview_zoom);
    iVar3 = gfx_zoom_scale(0x20,(int)mapview_zoom);
    rect_set_xywh((iptr)local_14,local_68,local_6c,iVar2,iVar3);
    __itoa(param_3,local_64,10);
    gfx_set_text_color_index(10);
    rect_offset((iptr)local_14,0xffffffff,0xffffffff);
    surface_draw_text_in_rect
              ((DibSurface *)&map_views,ADDR(0x66cae0, ((u8 *)&g.d_0066cae0)),(iptr)local_64,(iptr)local_14,0);
    rect_offset((iptr)local_14,3,3);
    surface_draw_text_in_rect
              ((DibSurface *)&map_views,ADDR(0x66cae0, ((u8 *)&g.d_0066cae0)),(iptr)local_64,(iptr)local_14,0);
    rect_offset((iptr)local_14,0xfffffffe,0xfffffffe);
    gfx_set_text_color_index(param_4);
    surface_draw_text_in_rect
              ((DibSurface *)&map_views,ADDR(0x66cae0, ((u8 *)&g.d_0066cae0)),(iptr)local_64,(iptr)local_14,0);
    wnd_blit_surface_rect((DibSurface *)&map_views,(iptr)local_14);
  }
  return;
}
#undef mapview_zoom
#undef local_6c
#undef local_68
#undef local_64
#undef local_14

/* 00479ede auto */
#define turn_resume_civ (*(char *)((u8 *)&g.d_00628048))
void __thiscall mapview_init_state(C_004083b0_430 *this,u32 param_1)

{
  this->field_2d8 = param_1;
  if (param_1 == 0) {
    *(undefined2 *)((int)&this->field_2dc + 2) = 1;
  }
  else {
    *(undefined2 *)((int)&this->field_2dc + 2) = 0;
  }
  this->field_358 = 0xffffffff;
  if (turn_resume_civ == '\0') {
    *(undefined2 *)&this->field_2e4 = 0;
    *(i16 *)&this->field_2e0 = map.width >> 1;
    *(i16 *)((int)&this->field_2e0 + 2) = map.height >> 1;
    if ((this->field_2e0 & 1) != 0) {
      *(short *)&this->field_2e0 = (short)this->field_2e0 - 1;
    }
    if ((this->field_2e0 & 0x10000) != 0) {
      *(short *)&this->field_2e0 = (short)this->field_2e0 + 1;
    }
  }
  this->field_35c = 0xfffffc19;
  return;
}
#undef turn_resume_civ

/* 00479fbe auto */
#define local_28 (*(undefined1 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_18 (*(undefined1 (*)[16])(frame_ + FRAME_OFF(16)))
#define local_8 (*(uptr *)(frame_ + FRAME_OFF(32)))
void __thiscall mapview_update_layout(C_004083b0_430 *this)

{
  u32 uVar1;
  undefined4 uVar2;
  uptr uVar3;
  uint uVar4;
  undefined1 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  this->field_328 = this->client_width;
  this->field_32c = this->client_height;
  uVar1 = mapview_zoom_scale(this,0x40);
  this->total_tax = uVar1;
  uVar1 = mapview_zoom_scale(this,0x20);
  this->total_science = uVar1;
  this->field_310 = (int)this->total_tax / 2;
  this->field_314 = (int)this->total_science / 2;
  this->field_318 = (int)(this->total_tax + ((int)this->total_tax >> 0x1f & 3U)) >> 2;
  this->field_31c = (int)(this->total_science + ((int)this->total_science >> 0x1f & 3U)) >> 2;
  this->field_320 = this->total_tax;
  this->field_324 = this->total_science + this->field_314;
  this->field_2f8 = (int)((this->field_328 - 1) + this->total_tax) / (int)this->total_tax;
  this->field_2fc = (int)((this->field_32c - 1) + this->total_science) / (int)this->total_science;
  this->field_300 = (int)(this->field_310 * 3 - 1 + this->field_328) / (int)this->total_tax;
  this->field_304 = (int)(this->field_314 * 3 - 1 + this->field_32c) / (int)this->total_science;
  this->field_330 = 0;
  this->field_334 = 0;
  if ((int)map.width / 2 < (int)this->field_2f8) {
    this->field_2f8 = (int)map.width / 2;
    this->field_330 = (int)(this->field_328 - this->total_tax * this->field_2f8) >> 1;
    this->field_300 = this->field_2f8 + 1;
  }
  if ((int)map.height < (int)this->field_2fc) {
    this->field_2fc = (int)map.height / 2;
    this->field_334 = (int)(this->field_32c - this->total_science * this->field_2fc) >> 1;
    this->field_304 = (int)map.height + 1;
  }
  uVar2 = map_wrap_x((int)(short)this->field_2e0);
  *(short *)&this->field_2e0 = (short)uVar2;
  this->field_2ec = (int)*(short *)((int)&this->field_2e0 + 2) - this->field_2fc;
  uVar3 = map_wrap_x((int)(short)this->field_2e0 - this->field_2f8);
  this->field_2e8 = uVar3;
  if (((game.rules & 0x8000) != 0) && (map.width + 1 < (int)(this->field_2f8 * 2 + this->field_2e8))
     ) {
    this->field_2e8 = map.width + 1 + this->field_2f8 * -2;
  }
  if (map.height + 1 < (int)(this->field_2fc * 2 + this->field_2ec)) {
    this->field_2ec = map.height + 1 + this->field_2fc * -2;
  }
  uVar4 = this->field_2e8;
  if (0x7fffffff < uVar4) {
    uVar4 = 0xffffffff;
  }
  this->field_2e8 = uVar4;
  uVar4 = this->field_2ec;
  if (0x7fffffff < uVar4) {
    uVar4 = 0xffffffff;
  }
  this->field_2ec = uVar4;
  if ((this->field_2e8 & 1) != 0) {
    this->field_2e8--;
  }
  if ((this->field_2ec & 1) != 0) {
    this->field_2e8++;
  }
  uVar3 = map_wrap_x(this->field_300 * 2 - 2 + this->field_2e8);
  this->field_2f0 = uVar3;
  this->field_2f4 = this->field_304 * 2 - 2 + this->field_2ec;
  if ((int)(short)this->field_2e4 != this->field_35c) {
    surface_create((DibSurface *)&this->field_360,this->total_tax,this->total_science);
    surface_create((DibSurface *)&this->field_3a8,this->total_tax,this->total_science);
    this->field_35c = (int)(short)this->field_2e4;
    mapview_apply_zoom(this);
    sprite_draw
              ((Sprite *)&tile_pick_mask_sprite,(iptr)local_18,(iptr)&this->field_360,0,0);
    sprite_draw
              ((Sprite *)&tile_direction_mask_sprite,(iptr)local_28,(iptr)&this->field_3a8,0,0);
    gfx_reset_zoom_scale();
  }
  local_8 = (int)(this->total_science * 3) / 5;
  if (this->field_348 != local_8) {
    font_set((GameFont *)&this->field_338,0,local_8);
    this->field_348 = local_8;
  }
  local_8 = (int)(this->total_science + ((int)this->total_science >> 0x1f & 3U)) >> 2;
  if (this->field_34c != local_8) {
    font_set((GameFont *)&this->field_340,1,local_8);
    this->field_34c = local_8;
  }
  return;
}
#undef local_28
#undef local_18
#undef local_8

/* 0047a540 auto */
#define local_10 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_8 (*(short *)(frame_ + FRAME_OFF(8)))
undefined4 __thiscall
mapview_screen_to_tile
          (MapViewHitView *this,iptr param_1,iptr param_2,undefined4 param_3,undefined4 param_4)

{
  short sVar1;
  short sVar2;
  undefined4 uVar3;
  iptr iVar4;
  iptr iVar5;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  sVar1 = (short)param_3 - (short)this->client_x;
  sVar2 = (short)param_4 - (short)this->client_y;
  if ((sVar1 < 0) || (sVar2 < 0)) {
    uVar3 = 1;
  }
  else if (((int)sVar1 < (int)this->view_width) && ((int)sVar2 < (int)this->view_height)) {
    sVar1 -= (short)this->scroll_px_x;
    sVar2 -= (short)this->scroll_px_y;
    local_10 = ((int)sVar1 / (int)this->tile_width) * 2 + this->origin_tile_x + 1;
    local_8 = (short)((int)sVar2 / (int)this->tile_height) * 2 + (short)this->origin_tile_y + 1;
    iVar4 = surface_get_pixel
                      ((DibSurface *)(this[1].pad_0 + 0x28),
                       (int)(short)((int)sVar1 % (int)this->tile_width),
                       (int)(short)((int)sVar2 % (int)this->tile_height));
    iVar5 = iVar4 - 10 >> 4;
    if (iVar5 != 0) {
      local_10 += (char)(&pick_quadrant_dx_table)[iVar5];
      local_8 += (char)(&pick_quadrant_dy_table)[iVar5];
    }
    uVar3 = map_wrap_x(local_10);
    *(int *)param_1 = (int)(short)uVar3;
    *(int *)param_2 = (int)local_8;
    uVar3 = 0;
  }
  else {
    uVar3 = 1;
  }
  return uVar3;
}
#undef local_10
#undef local_8

/* 0047a6b0 auto */
void __thiscall
mapview_tile_to_screen(C_004083b0_430 *this,iptr param_1,iptr param_2,int param_3,int param_4)

{
  uptr uVar1;
  int iVar2;
  
  iVar2 = map_wrap_x(param_3 - this->field_2e8);
  uVar1 = this->field_2ec;
  *(u32 *)param_1 = this->field_310 * (iVar2 - 1) + this->field_330;
  *(u32 *)param_2 = this->field_314 * ((param_4 - uVar1) - 1) + this->field_334;
  *(u32 *)param_1 = *(int *)param_1 + this->client_x;
  *(u32 *)param_2 = *(int *)param_2 + this->client_y;
  return;
}

/* 0047a8c9 auto */
#define map_show_hidden_terrain (*(int *)((u8 *)&g.d_0062bcd8))
#define local_24c (*(u32 *)(frame_ + FRAME_OFF(4)))
#define local_248 (*(u32 *)(frame_ + FRAME_OFF(8)))
#define local_244 (*(u32 *)(frame_ + FRAME_OFF(12)))
#define local_240 (*(u32 *)(frame_ + FRAME_OFF(16)))
#define local_23c (*(undefined1 (*)[16])(frame_ + FRAME_OFF(20)))
#define local_22c (*(undefined1 (*)[16])(frame_ + FRAME_OFF(36)))
#define local_21c (*(undefined1 (*)[16])(frame_ + FRAME_OFF(52)))
#define local_20c (*(undefined1 (*)[16])(frame_ + FRAME_OFF(68)))
#define local_1fc (*(undefined1 (*)[16])(frame_ + FRAME_OFF(84)))
#define local_1ec (*(undefined1 (*)[16])(frame_ + FRAME_OFF(100)))
#define local_1dc (*(undefined1 (*)[16])(frame_ + FRAME_OFF(116)))
#define local_1cc (*(undefined1 (*)[16])(frame_ + FRAME_OFF(132)))
#define local_1bc (*(undefined1 (*)[16])(frame_ + FRAME_OFF(148)))
#define local_1ac (*(undefined1 (*)[16])(frame_ + FRAME_OFF(164)))
#define local_19c (*(undefined1 (*)[16])(frame_ + FRAME_OFF(180)))
#define local_18c (*(undefined1 (*)[16])(frame_ + FRAME_OFF(196)))
#define local_17c (*(undefined1 (*)[16])(frame_ + FRAME_OFF(212)))
#define local_16c (*(undefined1 (*)[16])(frame_ + FRAME_OFF(228)))
#define local_15c (*(undefined1 (*)[16])(frame_ + FRAME_OFF(244)))
#define local_14c (*(undefined1 (*)[16])(frame_ + FRAME_OFF(260)))
#define local_13c (*(undefined1 (*)[16])(frame_ + FRAME_OFF(276)))
#define local_12c (*(undefined1 (*)[16])(frame_ + FRAME_OFF(292)))
#define local_11c (*(undefined1 (*)[16])(frame_ + FRAME_OFF(308)))
#define local_10c (*(undefined1 (*)[16])(frame_ + FRAME_OFF(324)))
#define local_fc (*(undefined1 (*)[16])(frame_ + FRAME_OFF(340)))
#define local_ec (*(undefined1 (*)[16])(frame_ + FRAME_OFF(356)))
#define local_dc (*(undefined1 (*)[16])(frame_ + FRAME_OFF(372)))
#define local_cc (*(undefined1 (*)[16])(frame_ + FRAME_OFF(388)))
#define local_bc (*(undefined1 (*)[16])(frame_ + FRAME_OFF(404)))
#define x2 (*(iptr *)(frame_ + FRAME_OFF(420)))
#define local_a8 (*(int *)(frame_ + FRAME_OFF(424)))
#define local_a4 (*(uint *)(frame_ + FRAME_OFF(428)))
#define local_a0 (*(uint *)(frame_ + FRAME_OFF(432)))
#define local_9c (*(uint *)(frame_ + FRAME_OFF(436)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(440)))
#define local_94 (*(int *)(frame_ + FRAME_OFF(444)))
#define local_90 (*(int *)(frame_ + FRAME_OFF(448)))
#define local_8c (*(int *)(frame_ + FRAME_OFF(452)))
#define local_88 (*(uint *)(frame_ + FRAME_OFF(456)))
#define local_84 (*(iptr *)(frame_ + FRAME_OFF(460)))
#define local_80 (*(byte * *)(frame_ + FRAME_OFF(464)))
#define local_7c (*(int *)(frame_ + FRAME_OFF(468)))
#define local_78 (*(int *)(frame_ + FRAME_OFF(472)))
#define local_74 (*(byte * *)(frame_ + FRAME_OFF(476)))
#define local_70 (*(u32 *)(frame_ + FRAME_OFF(480)))
#define local_6c (*(uint *)(frame_ + FRAME_OFF(484)))
#define local_68 (*(uint *)(frame_ + FRAME_OFF(488)))
#define local_64 (*(int *)(frame_ + FRAME_OFF(492)))
#define y2 (*(iptr *)(frame_ + FRAME_OFF(496)))
#define local_5c (*(u32 *)(frame_ + FRAME_OFF(500)))
#define local_58 (*(int *)(frame_ + FRAME_OFF(504)))
#define local_54 (*(iptr *)(frame_ + FRAME_OFF(508)))
#define local_50 (*(u32 *)(frame_ + FRAME_OFF(512)))
#define local_4c (*(int *)(frame_ + FRAME_OFF(516)))
#define local_48 (*(uint *)(frame_ + FRAME_OFF(520)))
#define local_44 (*(int *)(frame_ + FRAME_OFF(524)))
#define local_40 (*(int *)(frame_ + FRAME_OFF(528)))
#define local_3c (*(uint *)(frame_ + FRAME_OFF(532)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(536)))
#define local_34 (*(undefined1 (*)[16])(frame_ + FRAME_OFF(540)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(556)))
#define local_20 (*(uint *)(frame_ + FRAME_OFF(560)))
#define local_1c (*(iptr *)(frame_ + FRAME_OFF(564)))
#define local_18 (*(u32 *)(frame_ + FRAME_OFF(568)))
#define auStack_14 (*(uint (*)[4])(frame_ + FRAME_OFF(572)))
void __thiscall
mapview_draw_tile_terrain
          (C_004083b0_430 *this,iptr param_1,int param_2,int param_3,iptr x,int y,
          int param_6,int param_7,iptr param_8)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  byte *pbVar4;
  iptr civ;
  undefined4 uVar6;
  undefined1 frame_[FRAME_OFF(592)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((short)this->field_2e4 == param_7) {
    local_50 = this->total_tax;
    local_18 = this->total_science;
    local_70 = this->field_310;
    local_5c = this->field_314;
  }
  else {
    local_50 = gfx_zoom_scale(0x40,param_7);
    local_18 = gfx_zoom_scale(0x20,param_7);
    local_70 = (int)local_50 >> 1;
    local_5c = (int)local_18 >> 1;
  }
  if (param_8 < 0) {
    iVar3 = map_in_bounds(x,y);
    local_9c = (uint)(iVar3 == 0);
  }
  else {
    local_9c = (uint)(0x14 < param_8);
    if (local_9c == 0) {
      iVar3 = map_in_bounds(x,y);
      if (iVar3 == 0) {
        local_9c = 1;
      }
      else {
        local_9c = 0;
      }
    }
  }
  gfx_set_zoom_scale(param_7);
  if ((-1 < param_6) || (local_9c != 0)) {
    if (local_9c == 0) {
      iVar3 = tile_visible_to(x,y,param_6);
      if (iVar3 == 0) {
        local_9c = 1;
      }
      else {
        local_9c = 0;
      }
    }
    if (local_9c != 0) {
      sprite_draw
                ((Sprite *)&unexplored_tile_sprite,(iptr)local_bc,param_1,param_2,param_3);
      goto LAB_0047ba07;
    }
  }
  iVar3 = map_in_bounds(x,y);
  if (iVar3 == 0) {
    local_9c = 1;
    local_a4 = 7;
    local_6c = 7;
    local_88 = 0;
    local_20 = 0;
    local_80 = (byte *)0x0;
  }
  else {
    local_9c = 0;
    local_80 = (byte *)tile_at(x,y);
    local_a4 = (uint)*local_80;
    local_6c = local_a4 & 0xf;
    local_20 = local_a4 & 0x80;
    if (param_6 < 1) {
      local_88 = (uint)local_80[1];
    }
    else {
      pbVar4 = (byte *)known_at(x,y,param_6);
      local_88 = (uint)*pbVar4;
    }
  }
  for (local_54 = 0; local_54 < 4; local_54++) {
    auStack_14[local_54] = 0xffffffff;
  }
  if (local_6c == 10) {
    if (param_7 < -3) {
      sprite_draw
                ((Sprite *)&terrain_ocean_sprite,(iptr)local_cc,param_1,param_2,param_3);
    }
    else {
      local_8c = tile_calc_coast_masks(x,y);
      for (local_1c = 0; local_1c < 4; local_1c++) {
        local_24 = (*(int *)(&coast_quarter_dx_table + local_1c * 4) + 1) * ((int)local_70 >> 1) + param_2;
        local_44 = *(int *)(&coast_quarter_dy_table + local_1c * 4) * ((int)local_5c >> 1) + param_3;
        sprite_draw
                  ((Sprite *)
                   (&coast_quarter_sprites + local_1c * 0x3c + (uint)(byte)(&coast_quarter_land_masks)[local_1c] * 0xf0),
                   (iptr)local_dc,param_1,local_24,local_44);
      }
      for (local_54 = 0; local_54 < 4; local_54++) {
        x2 = map_wrap_x((char)(&diag_dx_table)[local_54] + x);
        y2 = (char)(&diag_dy_table)[local_54] + y;
        iVar3 = map_in_bounds(x2,y2);
        if ((iVar3 != 0) && (pbVar4 = (byte *)tile_at(x2,y2), (*pbVar4 & 0x80) != 0)) {
          sprite_draw
                    ((Sprite *)(&river_mouth_sprites + local_54 * 0x3c),(iptr)local_ec,param_1,
                     param_2,param_3);
        }
      }
    }
  }
  else {
    local_8c = 0;
    local_78 = 0;
    if (param_7 < -4) {
      local_78 = 0xf;
    }
    else {
      for (local_54 = 0; local_54 < 4; local_54++) {
        x2 = map_wrap_x((char)(&diag_dx_table)[local_54] + x);
        y2 = (char)(&diag_dy_table)[local_54] + y;
        iVar3 = map_in_bounds(x2,y2);
        if (iVar3 != 0) {
          local_74 = (byte *)tile_at(x2,y2);
          bVar1 = *local_74;
          local_48 = (uint)bVar1;
          local_a0 = local_48 & 0xf;
          if (local_a0 == local_6c) {
            local_8c += (char)(&diag_neighbor_bits)[local_54];
          }
          else if (local_a0 == 10) {
            auStack_14[local_54] = 0xc;
          }
          else {
            auStack_14[local_54] = local_a0;
          }
          if (((bVar1 & 0x80) != 0) || (local_a0 == 10)) {
            local_78 += (char)(&diag_neighbor_bits)[local_54];
          }
        }
      }
    }
    sprite_draw
              ((Sprite *)(&terrain_base_sprites + local_6c * 0x3c),(iptr)local_fc,param_1,param_2,
               param_3);
    if (-5 < param_7) {
      for (local_84 = 0; local_84 < 4; local_84++) {
        if (-1 < (int)auStack_14[local_84]) {
          if (local_84 < 2) {
            local_240 = local_70;
          }
          else {
            local_240 = 0;
          }
          local_4c = local_240 + param_2;
          if (((char)local_84 + 1U & 3) < 2) {
            local_244 = 0;
          }
          else {
            local_244 = local_5c;
          }
          local_58 = local_244 + param_3;
          sprite_draw
                    ((Sprite *)
                     (&terrain_dither_sprites + local_84 * 0x3c + auStack_14[local_84] * 0xf0),(iptr)local_10c
                     ,param_1,local_4c,local_58);
        }
      }
    }
    if (local_6c == 3) {
      sprite_draw
                ((Sprite *)(&forest_sprites + local_8c * 0x3c),(iptr)local_11c,param_1,param_2,
                 param_3);
    }
    else if (local_6c == 5) {
      sprite_draw
                ((Sprite *)(&mountain_sprites + local_8c * 0x3c),(iptr)local_12c,param_1,param_2,
                 param_3);
    }
    else if (local_6c == 4) {
      sprite_draw
                ((Sprite *)(&hill_sprites + local_8c * 0x3c),(iptr)local_13c,param_1,param_2,
                 param_3);
    }
    if (((-4 < param_7) && (map_show_hidden_terrain == 0)) && (((byte)local_88 & 0xc) == 0xc)) {
      sprite_draw
                ((Sprite *)&farmland_sprite,(iptr)local_14c,param_1,param_2,param_3);
    }
    if (((-7 < param_7) && (local_20 != 0)) && (map_show_hidden_terrain == 0)) {
      sprite_draw
                ((Sprite *)(&river_sprites + local_78 * 0x3c),(iptr)local_15c,param_1,param_2,
                 param_3);
    }
    if (-4 < param_7) {
      local_3c = 0;
      if (((byte)local_88 & 0x42) == 2) {
        for (local_54 = 2; local_54 < 5; local_54 += 2) {
          x2 = map_wrap_x((char)(&dir_dx_table)[local_54] + x);
          y2 = (char)(&dir_dy_table)[local_54] + y;
          iVar3 = map_in_bounds(x2,y2);
          uVar2 = local_3c;
          if (((iVar3 != 0) &&
              (local_68 = tile_improvements(x2,y2), uVar2 = local_3c,
              (local_68 & 4) != 0)) && (uVar2 = local_3c | 1, (local_68 & 8) != 0)) {
            uVar2 = local_3c | 3;
          }
          local_3c = uVar2;
        }
      }
      if (map_show_hidden_terrain == 0) {
        if ((((byte)local_88 & 0xc) == 4) || (local_3c == 1)) {
          sprite_draw
                    ((Sprite *)&land_improvement_sprites,(iptr)local_16c,param_1,param_2,param_3);
        }
        else if ((local_3c & 2) != 0) {
          sprite_draw
                    ((Sprite *)&farmland_sprite,(iptr)local_17c,param_1,param_2,param_3);
        }
      }
    }
    if (((-4 < param_7) && (local_6c == 2)) &&
       (iVar3 = tile_grassland_has_shield(x,y), iVar3 != 0)) {
      sprite_draw
                ((Sprite *)&grassland_shield_sprite,(iptr)local_18c,param_1,param_2,param_3);
    }
  }
  if (((-4 < param_7) && (local_9c == 0)) &&
     (local_38 = tile_resource(x,y), local_38 != 0)) {
    sprite_draw
              ((Sprite *)(&terrain_resource_sprites + local_6c * 0x78 + (local_38 * 4 - 4) * 0xf),
               (iptr)local_19c,param_1,param_2,param_3);
  }
  if (((-4 < param_7) && (map_show_hidden_terrain == 0)) &&
     (((local_88 & 0x10) != 0 || (iVar3 = tile_city_owner(x,y), -1 < iVar3)))) {
    local_90 = 0;
    local_94 = 0;
    if (((local_88 & 0x20) == 0) && (iVar3 = tile_city_owner(x,y), iVar3 < 0)) {
      local_40 = 0;
    }
    else {
      local_40 = 1;
    }
    for (local_54 = 0; local_54 < 8; local_54++) {
      x2 = map_wrap_x((char)(&dir_dx_table)[local_54] + x);
      y2 = (char)(&dir_dy_table)[local_54] + y;
      iVar3 = map_in_bounds(x2,y2);
      if (iVar3 != 0) {
        if (param_6 < 1) {
          local_68 = tile_improvements(x2,y2);
        }
        else {
          pbVar4 = (byte *)known_at(x2,y2,param_6);
          local_68 = (uint)*pbVar4;
        }
        if (((local_68 & 0x12) != 0) &&
           ((local_90 = local_90 + 1, local_40 == 0 || ((local_68 & 0x22) == 0)))) {
          sprite_draw
                    ((Sprite *)(&road_sprites + (local_54 * 4 + 4) * 0xf),(iptr)local_1ac,
                     param_1,param_2,param_3);
        }
      }
    }
    if (local_40 != 0) {
      for (local_54 = 0; local_54 < 8; local_54++) {
        x2 = map_wrap_x((char)(&dir_dx_table)[local_54] + x);
        y2 = (char)(&dir_dy_table)[local_54] + y;
        iVar3 = map_in_bounds(x2,y2);
        if (iVar3 != 0) {
          if (param_6 < 1) {
            local_68 = tile_improvements(x2,y2);
          }
          else {
            pbVar4 = (byte *)known_at(x2,y2,param_6);
            local_68 = (uint)*pbVar4;
          }
          if ((local_68 & 0x22) != 0) {
            local_94++;
            sprite_draw
                      ((Sprite *)(&railroad_sprites + (local_54 * 4 + 4) * 0xf),(iptr)local_1bc,
                       param_1,param_2,param_3);
          }
        }
      }
    }
    iVar3 = tile_city_owner(x,y);
    if (iVar3 < 0) {
      if (local_40 == 0) {
        if (local_90 == 0) {
          sprite_draw
                    ((Sprite *)&road_sprites,(iptr)local_1dc,param_1,param_2,param_3);
        }
      }
      else if (local_94 == 0) {
        sprite_draw
                  ((Sprite *)&railroad_sprites,(iptr)local_1cc,param_1,param_2,param_3);
      }
    }
  }
  if (((-4 < param_7) && (map_show_hidden_terrain == 0)) && (((byte)local_88 & 0xc) == 8)) {
    sprite_draw
              ((Sprite *)&mine_sprite,(iptr)local_1ec,param_1,param_2,param_3);
  }
  if ((-5 < param_7) && (local_9c == 0)) {
    if ((local_88 & 0x80) != 0) {
      sprite_draw
                ((Sprite *)&pollution_sprite,(iptr)local_1fc,param_1,param_2,param_3);
    }
    iVar3 = tile_has_hut(x,y);
    if ((iVar3 != 0) && (map_show_hidden_terrain == 0)) {
      sprite_draw
                ((Sprite *)&hut_sprite,(iptr)local_20c,param_1,param_2,param_3);
    }
    if ((((byte)local_88 & 0x42) == 0x40) && (map_show_hidden_terrain == 0)) {
      sprite_draw
                ((Sprite *)&fortress_sprite,(iptr)local_21c,param_1,param_2,param_3 - local_5c);
    }
    if ((((byte)local_88 & 0x42) == 0x42) && (map_show_hidden_terrain == 0)) {
      local_8c = 0;
      for (unit = tile_first_unit(x,y); -1 < unit;
          unit = unit_next_in_stack(unit)) {
        if (unit_types[units[unit].type].domain == 1) {
          local_8c = 1;
          break;
        }
      }
      sprite_draw
                ((Sprite *)(&airbase_sprites + local_8c * 0x3c),(iptr)local_22c,param_1,param_2,
                 param_3 - local_5c);
      rect_set_xywh((iptr)local_34,param_2,param_3 - local_5c,local_50,local_5c + local_18);
      civ = tile_owner(x,y);
      uVar6 = civ_color_primary(civ);
      surface_replace_color((DibSurface *)param_1,(iptr)local_34,0x106,uVar6);
    }
  }
  if ((-4 < param_7) && (-1 < param_6)) {
    for (local_54 = 0; local_54 < 4; local_54++) {
      x2 = map_wrap_x((char)(&diag_dx_table)[local_54] + x);
      y2 = (char)(&diag_dy_table)[local_54] + y;
      local_64 = 0;
      if (param_8 < 0) {
        iVar3 = map_in_bounds(x2,y2);
        if (iVar3 != 0) goto LAB_0047b934;
      }
      else {
        if (param_8 < 0x15) {
          iVar3 = map_in_bounds(x2,y2);
          if (iVar3 == 0) {
            local_64 = 1;
          }
          if ((int)(char)(&diag_dx_table)[local_54] + (int)(char)(&city_tile_dx_table)[param_8] < 1) {
            local_7c = ~((int)(char)(&diag_dx_table)[local_54] + (int)(char)(&city_tile_dx_table)[param_8])
                       + 1;
          }
          else {
            local_7c = (int)(char)(&diag_dx_table)[local_54] + (int)(char)(&city_tile_dx_table)[param_8];
          }
          if ((int)(char)(&diag_dy_table)[local_54] + (int)(char)(&city_tile_dy_table)[param_8] < 1) {
            local_a8 = ~((int)(char)(&diag_dy_table)[local_54] + (int)(char)(&city_tile_dy_table)[param_8])
                       + 1;
          }
          else {
            local_a8 = (int)(char)(&diag_dy_table)[local_54] + (int)(char)(&city_tile_dy_table)[param_8];
          }
          iVar3 = dist_from_deltas(local_7c,local_a8);
          if (2 < iVar3) {
            local_64 = 1;
          }
        }
        else {
          local_64 = 1;
        }
LAB_0047b934:
        if (local_64 == 0) {
          iVar3 = tile_visible_to(x2,y2,param_6);
          if (iVar3 == 0) {
            local_64 = 1;
          }
          else {
            local_64 = 0;
          }
        }
        if (local_64 != 0) {
          if (local_54 < 2) {
            local_248 = local_70;
          }
          else {
            local_248 = 0;
          }
          local_4c = local_248 + param_2;
          if (((char)local_54 + 1U & 3) < 2) {
            local_24c = 0;
          }
          else {
            local_24c = local_5c;
          }
          local_58 = local_24c + param_3;
          sprite_draw
                    ((Sprite *)(&unexplored_dither_sprites + local_54 * 0x3c),(iptr)local_23c,param_1,
                     local_4c,local_58);
        }
      }
    }
  }
LAB_0047ba07:
  gfx_reset_zoom_scale();
  return;
}
#undef map_show_hidden_terrain
#undef local_24c
#undef local_248
#undef local_244
#undef local_240
#undef local_23c
#undef local_22c
#undef local_21c
#undef local_20c
#undef local_1fc
#undef local_1ec
#undef local_1dc
#undef local_1cc
#undef local_1bc
#undef local_1ac
#undef local_19c
#undef local_18c
#undef local_17c
#undef local_16c
#undef local_15c
#undef local_14c
#undef local_13c
#undef local_12c
#undef local_11c
#undef local_10c
#undef local_fc
#undef local_ec
#undef local_dc
#undef local_cc
#undef local_bc
#undef x2
#undef local_a8
#undef local_a4
#undef local_a0
#undef local_9c
#undef unit
#undef local_94
#undef local_90
#undef local_8c
#undef local_88
#undef local_84
#undef local_80
#undef local_7c
#undef local_78
#undef local_74
#undef local_70
#undef local_6c
#undef local_68
#undef local_64
#undef y2
#undef local_5c
#undef local_58
#undef local_54
#undef local_50
#undef local_4c
#undef local_48
#undef local_44
#undef local_40
#undef local_3c
#undef local_38
#undef local_34
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef auStack_14

/* 0047ba1d auto */
#define human_civ (*(undefined *)((u8 *)&g.d_006d1da0))
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall
mapview_draw_tile_city
          (C_004083b0_430 *this,undefined4 param_1,int param_2,iptr x,iptr y)

{
  iptr city;
  int iVar2;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  city = city_at(x,y);
  if ((-1 < city) && (iVar2 = map_in_bounds(x,y), iVar2 != 0)) {
    local_8 = tile_visible_to(x,y,human_civ);
    if ((int)cities[city].owner != (human_civ & 0xffU)) {
      if ((local_8 == 0) ||
         ((((1 << ((byte)human_civ & 0x1f) & (int)(char)cities[city].known_to) == 0 &&
           ((int)cities[city].owner != (human_civ & 0xffU))) ||
          (*(char *)&cities[city].revealed_size[human_civ] == '\0')))) {
        local_8 = 0;
      }
      else {
        local_8 = 1;
      }
    }
    if (((local_8 != 0) || (game.reveal_map != '\0')) ||
       (((game.game_flags & 0x80) != 0 && ((scenario_flags & 8) != 0)))) {
      gfx_draw_city((iptr)this,city,0,param_1,param_2 - this->field_314,
                         (int)(short)this->field_2e4);
    }
  }
  return;
}
#undef human_civ
#undef scenario_flags
#undef local_8

/* 0047bba5 auto */
void __thiscall
mapview_draw_unit_stacked
          (C_004083b0_430 *this,iptr unit,uint param_2,undefined4 param_3,undefined4 param_4)

{
  gfx_draw_unit((iptr)this,unit,param_2 | 3,param_3,param_4,(int)(short)this->field_2e4,0);
  return;
}

/* 0047bbea auto */
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
#define unit_blink_active (*(char *)((u8 *)&g.d_0062804c))
#define unit_blink_phase (*(char *)((u8 *)&g.d_00628054))
void __thiscall
mapview_draw_unit_blinking
          (C_004083b0_430 *this,iptr unit,undefined4 param_2,undefined4 param_3)

{
  if (((unit_blink_active == '\0') || (unit_blink_phase == '\0')) || (moving_units_mode != 1)) {
    gfx_draw_unit((iptr)this,unit,5,param_2,param_3,(int)(short)this->field_2e4,0);
  }
  return;
}
#undef moving_units_mode
#undef unit_blink_active
#undef unit_blink_phase

/* 0047bc59 auto */
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
#define unit_blink_active (*(char *)((u8 *)&g.d_0062804c))
#define unit_blink_phase (*(char *)((u8 *)&g.d_00628054))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(8)))
void __thiscall mapview_draw_unit_at(C_004083b0_430 *this,iptr unit)

{
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((unit_blink_active == '\0') || (unit_blink_phase == '\0')) || (moving_units_mode != 1)) {
    mapview_tile_to_screen(this,(iptr)&local_8,(iptr)&local_c,(int)units[unit].x,
                       (int)units[unit].y);
    local_c -= this->field_314;
    gfx_draw_unit((iptr)this,unit,5,local_8,local_c,(int)(short)this->field_2e4,0);
  }
  return;
}
#undef moving_units_mode
#undef unit_blink_active
#undef unit_blink_phase
#undef local_c
#undef local_8

/* 0047bd04 auto */
#define anim_combat_defender (*(int *)((u8 *)&g.d_00633e48))
void __thiscall
mapview_draw_stack_unit
          (C_004083b0_430 *this,iptr unit,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  if ((anim_combat_defender < 0) || (anim_combat_defender != unit)) {
    if ((anim_origin_stack_unit < 0) || (unit != anim_origin_stack_unit)) {
      if ((((units[game.active_unit].x == units[unit].x) &&
           (units[game.active_unit].y == units[unit].y)) &&
          (((uint)game.human_players & 1 << (units[game.active_unit].owner & 0x1fU)) != 0)) &&
         (iVar1 = unit_is_selectable((int)game.active_unit), iVar1 != 0)) {
        mapview_draw_unit_blinking(this,(int)game.active_unit,param_2,param_3);
        return;
      }
      mapview_draw_unit_stacked(this,unit,4,param_2,param_3);
    }
    else {
      gfx_draw_unit((iptr)this,unit,5,param_2,param_3,(int)(short)this->field_2e4,0);
    }
  }
  else {
    mapview_draw_unit_blinking(this,unit,param_2,param_3);
  }
  return;
}
#undef anim_combat_defender

/* 0047be63 auto */
#define anim_combat_defender (*(int *)((u8 *)&g.d_00633e48))
#define anim_combat_defender_x (*(int *)((u8 *)&g.d_00633e40))
#define human_civ (*(undefined *)((u8 *)&g.d_006d1da0))
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
#define unit_blink_active (*(char *)((u8 *)&g.d_0062804c))
#define unit (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __thiscall
mapview_draw_tile_units
          (C_004083b0_430 *this,undefined4 param_1,int param_2,int x,int y)

{
  int iVar1;
  int iVar2;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = param_2 - this->field_314;
  iVar2 = map_in_bounds(x,y);
  if (iVar2 != 0) {
    unit = tile_first_unit(x,y);
    if (((anim_combat_defender < 0) || (anim_combat_defender_x != x)) || (anim_combat_defender_y != y)) {
      if (((anim_origin_stack_unit < 0) || (x != anim_origin_x)) || (y != anim_origin_y)) {
        iVar2 = tile_city_owner(x,y);
        if (-1 < iVar2) {
          if (moving_units_mode != 1) {
            return;
          }
          if (unit_blink_active == '\0') {
            return;
          }
          for (; (game.active_unit != unit && (-1 < unit));
              unit = unit_next_in_stack(unit)) {
          }
          if (unit < 0) {
            return;
          }
          iVar2 = unit_is_selectable(unit);
          if (iVar2 == 0) {
            return;
          }
          if (units[unit].orders == 1) {
            return;
          }
          if (units[unit].orders == 2) {
            return;
          }
        }
        local_8 = tile_visible_to(x,y,human_civ);
        if ((int)units[unit].owner != (human_civ & 0xffU)) {
          if ((local_8 == 0) ||
             (((1 << ((byte)human_civ & 0x1f) & (uint)units[unit].visibility) == 0 &&
              ((int)units[unit].owner != (human_civ & 0xffU))))) {
            local_8 = 0;
          }
          else {
            local_8 = 1;
          }
        }
        if ((local_8 != 0) || (game.reveal_map != '\0')) {
          mapview_draw_stack_unit(this,unit,param_1,iVar1);
        }
      }
      else {
        mapview_draw_stack_unit(this,anim_origin_stack_unit,param_1,iVar1);
      }
    }
    else {
      for (; (unit != anim_combat_defender && (-1 < unit)); unit = unit_next_in_stack(unit)) {
      }
      mapview_draw_stack_unit(this,unit,param_1,iVar1);
    }
  }
  return;
}
#undef anim_combat_defender
#undef anim_combat_defender_x
#undef human_civ
#undef moving_units_mode
#undef unit_blink_active
#undef unit
#undef local_8

/* 0047c103 auto */
#define map_show_hidden_terrain (*(int *)((u8 *)&g.d_0062bcd8))
#define local_34 (*(undefined1 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_24 (*(undefined1 (*)[16])(frame_ + FRAME_OFF(20)))
#define city (*(iptr *)(frame_ + FRAME_OFF(36)))
#define local_10 (*(undefined4 *)(frame_ + FRAME_OFF(40)))
#define local_c (*(undefined4 *)(frame_ + FRAME_OFF(44)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(48)))
void __thiscall
mapview_draw_tile(C_004083b0_430 *this,iptr x,iptr y,int civ)

{
  int iVar1;
  undefined1 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  mapview_tile_to_screen(this,(iptr)&local_c,(iptr)&local_10,x,y);
  mapview_draw_tile_terrain(this,(iptr)this,local_c,local_10,x,y,civ,
                     (int)(short)this->field_2e4,-1);
  win_flush_pending_msgs();
  if (2 < game.multiplayer) {
    net_process_messages((NetSession *)&net_session,1,0);
  }
  iVar1 = map_in_bounds(x,y);
  if (iVar1 != 0) {
    if (map_show_hidden_terrain == 0) {
      mapview_draw_tile_city(this,local_c,local_10,x,y);
      mapview_draw_tile_units(this,local_c,local_10,x,y);
    }
    if (((byte)game.game_options & 0x20) != 0) {
      local_8 = 0;
      mapview_apply_zoom(this);
      for (city = 0; city < game.num_cities; city++) {
        if (((cities[city].id != 0) && (cities[city].owner == civ)) &&
           (iVar1 = map_distance_diag(x,y,(int)cities[city].x,
                                       (int)cities[city].y), iVar1 < 3)) {
          local_8 = 1;
          break;
        }
      }
      if (local_8 == 0) {
        sprite_draw
                  ((Sprite *)&map_grid_sprite,(iptr)local_34,(iptr)this,local_c,local_10);
      }
      else {
        sprite_draw
                  ((Sprite *)&city_radius_grid_sprite,(iptr)local_24,(iptr)this,local_c,local_10);
      }
      gfx_reset_zoom_scale();
    }
  }
  return;
}
#undef map_show_hidden_terrain
#undef local_34
#undef local_24
#undef city
#undef local_10
#undef local_c
#undef local_8

/* 0047c3e0 auto */
undefined4 __thiscall
mapview_tile_in_view(C_004083b0_430 *this,undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = map_tile_in_box(param_1,param_2,this->field_2e8,this->field_2ec,
                             this->field_2f8 + this->field_300,this->field_2fc + this->field_304 + 1
                            );
  return uVar1;
}

/* 0047c443 auto */
#define human_civ (*(undefined *)((u8 *)&g.d_006d1da0))
#define map_show_hidden_terrain (*(int *)((u8 *)&g.d_0062bcd8))
#define local_2c (*(undefined4 *)(frame_ + FRAME_OFF(4)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(16)))
#define city (*(iptr *)(frame_ + FRAME_OFF(20)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(24)))
#define y2 (*(int *)(frame_ + FRAME_OFF(28)))
#define x2 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_c (*(int *)(frame_ + FRAME_OFF(36)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(40)))
void __thiscall
mapview_draw_city_names(C_004083b0_430 *this,undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined1 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (map_show_hidden_terrain == 0) {
    if (-1 < param_3) {
      param_3 += 3;
    }
    text_set_font((iptr)&this->field_338);
    for (city = 0; city < game.num_cities; city++) {
      if (cities[city].id != 0) {
        x2 = (int)cities[city].x;
        y2 = (int)cities[city].y;
        if (((param_3 < 0) ||
            (iVar1 = map_distance(x2,y2,param_1,param_2), iVar1 <= param_3)) &&
           (iVar1 = mapview_tile_in_view(this,x2,y2), iVar1 != 0)) {
          local_c = tile_visible_to(x2,y2,human_civ);
          if ((int)cities[city].owner != (human_civ & 0xffU)) {
            if (((local_c == 0) ||
                (((1 << ((byte)human_civ & 0x1f) & (int)(char)cities[city].known_to) == 0 &&
                 ((int)cities[city].owner != (human_civ & 0xffU))))) ||
               (*(char *)&cities[city].revealed_size[human_civ] == '\0')) {
              local_c = 0;
            }
            else {
              local_c = 1;
            }
          }
          if (game.reveal_map != '\0') {
            local_c = 1;
          }
          if (local_c != 0) {
            mapview_tile_to_screen(this,(iptr)&local_18,(iptr)&local_20,x2,y2);
            iVar1 = this->field_310 + local_18;
            local_8 = ((int)(this->total_science * 3) >> 2) + local_20;
            text_set_colors(10,0xffffffff,0xffffffff,0xffffffff);
            iVar2 = mapview_zoom_scale(this,2);
            if (iVar2 < 3) {
              local_28 = mapview_zoom_scale(this,2);
            }
            else {
              local_28 = 2;
            }
            local_28 = local_8 + local_28;
            iVar2 = font_text_width
                              ((GameFont *)&this->field_338,(iptr)&cities[city].name);
            text_draw_shadowed((iptr)this,(iptr)&cities[city].name,iVar1 - (iVar2 >> 1),local_28);
            iVar2 = mapview_zoom_scale(this,2);
            if (iVar2 < 3) {
              local_2c = mapview_zoom_scale(this,2);
            }
            else {
              local_2c = 2;
            }
            uVar6 = 0;
            uVar5 = 10;
            uVar3 = civ_color_secondary((int)cities[city].owner);
            text_set_colors(uVar3,uVar5,local_2c,uVar6);
            iVar2 = local_8;
            iVar4 = font_text_width
                              ((GameFont *)&this->field_338,(iptr)&cities[city].name);
            text_draw_shadowed((iptr)this,(iptr)&cities[city].name,iVar1 - (iVar4 >> 1),iVar2);
          }
        }
      }
    }
  }
  return;
}
#undef human_civ
#undef map_show_hidden_terrain
#undef local_2c
#undef local_28
#undef local_20
#undef city
#undef local_18
#undef y2
#undef x2
#undef local_c
#undef local_8

/* 0047c7aa auto */
#define local_20 (*(undefined1 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(24)))
void __thiscall
mapview_tile_radius_rect
          (C_004083b0_430 *this,undefined4 param_1,undefined4 param_2,int param_3,iptr param_4)

{
  undefined1 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  mapview_tile_to_screen(this,(iptr)&local_8,(iptr)&local_c,param_1,param_2);
  local_c -= (param_3 * 2 + 1) * this->field_314;
  local_8 += this->field_310 * param_3 * -2;
  local_10 = (param_3 * 2 + 1) * this->total_tax;
  rect_set_xywh((iptr)local_20,local_8,local_c,local_10,(param_3 * 4 + 3) * this->field_314);
  rect_intersect_into(param_4,(iptr)local_20,(iptr)&this->client_rect);
  return;
}
#undef local_20
#undef local_10
#undef local_c
#undef local_8

/* 0047c869 auto */
#define local_34 (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_2c (*(uint *)(frame_ + FRAME_OFF(12)))
#define local_24 (*(uint *)(frame_ + FRAME_OFF(20)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_14 (*(undefined1 (*)[16])(frame_ + FRAME_OFF(36)))
void __thiscall
mapview_draw_tile_radius
          (C_004083b0_430 *this,int param_1,int param_2,int param_3,undefined4 civ)

{
  uint uVar1;
  uint uVar2;
  undefined4 x;
  int iVar4;
  undefined1 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  mapview_tile_radius_rect(this,param_1,param_2,param_3,(iptr)local_14);
  surface_set_clip((DibSurface *)this,(iptr)local_14);
  uVar1 = param_3 * 2 + 2;
  for (local_2c = -uVar1; (int)local_2c <= (int)uVar1; local_2c++) {
    if ((int)local_2c < 1) {
      uVar2 = ~local_2c + 1;
    }
    else {
      uVar2 = local_2c & 1;
    }
    local_18 = uVar1 - uVar2;
    for (local_24 = -local_18; (int)local_24 <= local_18; local_24 += 2) {
      if ((int)local_24 < 1) {
        local_34 = ~local_24 + 1;
      }
      else {
        local_34 = local_24;
      }
      if (local_34 != uVar1) {
        x = map_wrap_x(local_24 + param_1);
        iVar4 = mapview_tile_in_view(this,x,param_2 + local_2c);
        if (iVar4 != 0) {
          mapview_draw_tile(this,x,param_2 + local_2c,civ);
        }
      }
    }
  }
  mapview_draw_city_names(this,param_1,param_2,param_3);
  surface_set_clip((DibSurface *)this,(iptr)&this->client_rect);
  return;
}
#undef local_34
#undef local_2c
#undef local_24
#undef local_18
#undef local_14

/* 0047c9d4 auto */
#define local_1c (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(12)))
void __thiscall mapview_draw_all_tiles(C_004083b0_430 *this,undefined4 civ)

{
  uptr uVar1;
  uptr uVar2;
  undefined4 x;
  undefined1 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((this->field_330 != 0) || (this->field_334 != 0)) {
    gfx_fill_surface((iptr)this,10);
  }
  for (local_1c = 0; (int)local_1c < (int)(this->field_2fc + this->field_304 + 1);
      local_1c = local_1c + 1) {
    uVar1 = this->field_2ec;
    uVar2 = this->field_2e8;
    if ((local_1c & 1) == 0) {
      local_14 = this->field_300;
    }
    else {
      local_14 = this->field_2f8;
    }
    for (local_18 = 0; local_18 < local_14; local_18++) {
      x = map_wrap_x(local_18 * 2 + uVar2 + (local_1c & 1));
      mapview_draw_tile(this,x,uVar1 + local_1c,civ);
    }
  }
  mapview_draw_city_names(this,0,0,0xffffffff);
  return;
}
#undef local_1c
#undef local_18
#undef local_14

/* 0047caea auto */
#define local_14 (*(undefined1 (*)[16])(frame_ + FRAME_OFF(4)))
void __thiscall
mapview_blit_tile_radius
          (C_004083b0_430 *this,undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  mapview_tile_radius_rect(this,param_1,param_2,param_3,(iptr)local_14);
  wnd_blit_surface_rect((DibSurface *)this,(iptr)local_14);
  return;
}
#undef local_14

/* 0047cb26 auto */
void __thiscall
mapview_blit_tile(C_004083b0_430 *this,undefined4 param_1,undefined4 param_2)

{
  mapview_blit_tile_radius(this,param_1,param_2,0);
  return;
}

/* 0047cb50 auto */
void __thiscall mapview_blit_with_net_pump(DibSurface *this)

{
  win_flush_pending_msgs();
  if (2 < game.multiplayer) {
    net_process_messages((NetSession *)&net_session,1,0);
  }
  wnd_blit_surface(this);
  win_flush_pending_msgs();
  if (2 < game.multiplayer) {
    net_process_messages((NetSession *)&net_session,1,0);
  }
  return;
}

/* 0047cbb4 auto */
#define game_loop_active (*(char *)((u8 *)&g.d_00628044))
#define map_cursor_x (*(short *)((u8 *)&g.d_0064b1b4))
#define map_cursor_y (*(short *)((u8 *)&g.d_0064b1b0))
#define map_redraw_busy (*(undefined4 *)((u8 *)&g.d_006ad908))
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
#define unit_blink_active (*(char *)((u8 *)&g.d_0062804c))
#define unit_blink_phase (*(char *)((u8 *)&g.d_00628054))
#define civ (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_1c (*(undefined1 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_c (*(undefined4 *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(24)))
void __thiscall
mapview_redraw_area
          (C_004083b0_430 *this,undefined4 param_1,undefined4 param_2,undefined4 param_3,
          iptr param_4,int param_5)

{
  int iVar1;
  undefined1 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (game_loop_active != '\0') {
    map_redraw_busy = 1;
    if (game.reveal_map == '\0') {
      civ = param_4;
    }
    else {
      civ = -1;
    }
    mapview_draw_tile_radius(this,param_1,param_2,param_3,civ);
    if ((((moving_units_mode == 0) && (unit_blink_phase != '\0')) && (unit_blink_active != '\0')) &&
       ((this->field_2d8 == 0 &&
        (iVar1 = mapview_tile_in_view(this,(int)map_cursor_x,(int)map_cursor_y), iVar1 != 0)))) {
      mapview_tile_to_screen(this,(iptr)&local_c,(iptr)&local_8,(int)map_cursor_x,(int)map_cursor_y);
      mapview_apply_zoom(this);
      sprite_draw
                ((Sprite *)&map_cursor_sprite,(iptr)local_1c,(iptr)this,local_c,local_8);
      gfx_reset_zoom_scale();
    }
    if (param_5 != 0) {
      mapview_blit_tile_radius(this,param_1,param_2,param_3);
    }
    map_redraw_busy = 0;
  }
  return;
}
#undef game_loop_active
#undef map_cursor_x
#undef map_cursor_y
#undef map_redraw_busy
#undef moving_units_mode
#undef unit_blink_active
#undef unit_blink_phase
#undef civ
#undef local_1c
#undef local_c
#undef local_8

/* 0047cced auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
void __thiscall
mapview_redraw_tile(C_004083b0_430 *this,undefined4 param_1,undefined4 param_2)

{
  mapview_redraw_area(this,param_1,param_2,0,human_civ,1);
  return;
}
#undef human_civ

/* 0047cd1f auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
void __thiscall
mapview_redraw_tile_neighbors(C_004083b0_430 *this,undefined4 param_1,undefined4 param_2)

{
  mapview_redraw_area(this,param_1,param_2,1,human_civ,1);
  return;
}
#undef human_civ

/* 0047cd51 auto */
#define game_loop_active (*(char *)((u8 *)&g.d_00628044))
#define map_click_in_progress (*(int *)((u8 *)&g.d_0062bcb0))
#define map_redraw_busy (*(undefined4 *)((u8 *)&g.d_006ad908))
#define mp_simultaneous_moves (*(char *)((u8 *)&g.d_006ad684))
#define civ (*(iptr *)(frame_ + FRAME_OFF(0)))
void __thiscall mapview_redraw(C_004083b0_430 *this,iptr param_1,int param_2)

{
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (game_loop_active != '\0') {
    map_redraw_busy = 1;
    frame_wnd_layout((FrameWindow *)this);
    mapview_update_layout(this);
    frame_wnd_draw_caption((FrameWindow *)this);
    if (game.reveal_map == '\0') {
      civ = param_1;
    }
    else {
      civ = -1;
    }
    mapview_draw_all_tiles(this,civ);
    if ((param_2 != 0) &&
       (mapview_blit_with_net_pump((DibSurface *)this), this->field_2d8 == 0)) {
      minimap_redraw();
    }
    if ((map_click_in_progress == 0) && (mp_simultaneous_moves == '\0')) {
      input_flush_events();
    }
    map_redraw_busy = 0;
  }
  return;
}
#undef game_loop_active
#undef map_click_in_progress
#undef map_redraw_busy
#undef mp_simultaneous_moves
#undef civ

/* 0047dce0 auto */
#define local_10 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(undefined1 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(8)))
C_004083b0_430 * __thiscall mapview_ctor(C_004083b0_430 *this)

{
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  frame_wnd_ctor((SurfaceWindow *)this);
  local_8 = 0;
  font_init_empty((GameFont *)&this->field_338);
  (*(undefined1 *)((char *)&local_8 + 0)) = 1;
  font_init_empty((GameFont *)&this->field_340);
  (*(undefined1 *)((char *)&local_8 + 0)) = 2;
  surface_ctor((DibSurface *)&this->field_360);
  local_8 = CONCAT31((*(undefined3 *)((char *)&local_8 + 1)),3);
  surface_ctor((DibSurface *)&this->field_3a8);
  this->vtable = (u32)&PTR_FUN_0061d1e4;
  return this;
}
#undef local_10
#undef puStack_c
#undef local_8

/* 0047de10 auto */
#define uStack_10 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(undefined1 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    public: virtual __thiscall CBitmapButton::~CBitmapButton(void)
   
   Library: Visual Studio 1998 Debug */

void __thiscall mapview_dtor(void *this)

{
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  (*(undefined3 *)((char *)&local_8 + 1)) = 0;
  (*(undefined1 *)((char *)&local_8 + 0)) = 3;
  /* inlined unwind funclet FUN_0047de82 */ { surface_dtor((DibSurface *)(*(int *)((iptr)&this) + 0x3a8)); }
  (*(undefined1 *)((char *)&local_8 + 0)) = 2;
  /* inlined unwind funclet FUN_0047de91 */ { surface_dtor((DibSurface *)(*(int *)((iptr)&this) + 0x360)); }
  (*(undefined1 *)((char *)&local_8 + 0)) = 1;
  /* inlined unwind funclet FUN_0047dea0 */ { font_destroy((GameFont *)(*(int *)((iptr)&this) + 0x340)); }
  local_8 = (uint)(*(undefined3 *)((char *)&local_8 + 1)) << 8;
  /* inlined unwind funclet FUN_0047deaf */ { font_destroy((GameFont *)(*(int *)((iptr)&this) + 0x338)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_0047debe */ { frame_wnd_dtor(*(DibSurface **)((iptr)&this)); }
  return;
}
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0047dfb0 auto */
undefined4 __thiscall mapview_zoom_scale(C_004083b0_430 *this,undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = gfx_zoom_scale(param_1,(int)(short)this->field_2e4);
  return uVar1;
}

/* 0047dff0 auto */
void __thiscall mapview_apply_zoom(C_004083b0_430 *this)

{
  gfx_set_zoom_scale((int)(short)this->field_2e4);
  return;
}

/* 0047e030 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
undefined4 __cdecl mapviews_tile_visible(iptr x,iptr y)

{
  int iVar1;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = tile_visible_to(x,y,human_civ);
  if (iVar1 != 0) {
    for (local_8 = 0; local_8 < 8; local_8++) {
      if (((local_8 == 0) || (*(short *)(&map_view_open_flags + local_8 * 0x3f0) != 0)) &&
         (iVar1 = mapview_tile_in_view
                            ((C_004083b0_430 *)(&map_views + local_8 * 0x3f0),x,y),
         iVar1 != 0)) {
        return 1;
      }
    }
  }
  return 0;
}
#undef human_civ
#undef local_8

/* 00489b9b auto */
#define map_view_center_x (*(short *)((u8 *)&g.d_0066ca88))
#define mapview_center_y (*(short *)((u8 *)&g.d_0066ca8a))
void __cdecl mapview_center_if_moved(int param_1,int param_2)

{
  if ((map_view_center_x != param_1) || (mapview_center_y != param_2)) {
    mapview_center_on((C_004083b0_430 *)&map_views,param_1,param_2);
  }
  return;
}
#undef map_view_center_x
#undef mapview_center_y

/* 004d8b70 auto */
void __thiscall
clickmap_add_xywh
          (ClickMap *this,iptr param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
          undefined4 param_5)

{
  clickmap_add(this,param_1,0,param_2,param_3,param_4,param_5);
  return;
}
