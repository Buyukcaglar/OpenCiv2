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
#define minimap_hidden (*(i8 *)((u8 *)&g.d_00624ee0))
void __cdecl minimap_on_minimize(void)

{
  minimap_hidden = 1;
  return;
}
#undef minimap_hidden

/* 00406b02 auto */
#define minimap_hidden (*(i8 *)((u8 *)&g.d_00624ee0))
void __cdecl minimap_on_restore(void)

{
  city_window_bring_to_top((WindowObjectView *)&city_window);
  minimap_hidden = 0;
  minimap_redraw();
  return;
}
#undef minimap_hidden

/* 00406b28 auto */
#define minimap_hidden (*(i8 *)((u8 *)&g.d_00624ee0))
i32 __cdecl minimap_on_close(void)

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
#define minimap_margin_y_i32 (*(i32 *)((u8 *)&g.d_0063caf0))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl minimap_calc_layout(void)

{
  int client_h;
  int tile_size;
  int tile_h;
  
  client_h = minimap_client_height;
  tile_size = minimap_client_width / (int)map.width;
  if (tile_size < 2) {
    tile_size = 1;
  }
  tile_h = minimap_client_height / (int)map.height;
  if (tile_h < 2) {
    tile_h = 1;
  }
  if (tile_h <= tile_size) {
    tile_size = tile_h;
  }
  minimap_tile_height = tile_size;
  if (tile_h <= tile_size) {
    minimap_tile_height = tile_h;
  }
  minimap_tile_width = tile_size * 2;
  tile_size = (minimap_client_width - minimap_tile_width / 2) / minimap_tile_width;
  minimap_view_cols = (int)map.width / 2;
  if (tile_size <= (int)map.width / 2) {
    minimap_view_cols = tile_size;
  }
  minimap_view_rows = (int)map.height;
  if (minimap_client_height / minimap_tile_height <= (int)map.height) {
    minimap_view_rows = minimap_client_height / minimap_tile_height;
  }
  tile_size = int_clamp(minimap_client_width - minimap_view_cols * minimap_tile_width,0,999);
  minimap_margin_y_i32 = int_clamp(client_h - minimap_view_rows * minimap_tile_height,0,999);
  minimap_margin_x = tile_size >> 1;
  minimap_margin_y_i32 = minimap_margin_y_i32 >> 1;
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
#undef minimap_margin_y_i32

/* 00406db8 auto */
#define minimap_origin_x (*(int *)((u8 *)&g.d_0063c814))
#define minimap_origin_y (*(int *)((u8 *)&g.d_0063c810))
#define minimap_margin_y_i32 (*(i32 *)((u8 *)&g.d_0063caf0))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl minimap_tile_to_screen(int x,uint y,iptr out_x,iptr out_y)

{
  int dx;
  
  dx = x - minimap_origin_x;
  if (((game.rules & 0x8000) == 0) && (dx < 0)) {
    dx += map.width;
  }
  *(uint *)out_y = (y - minimap_origin_y) * minimap_tile_height + minimap_margin_y_i32;
  *(int *)out_x = (dx >> 1) * minimap_tile_width + minimap_margin_x;
  if ((y & 1) != 0) {
    *(int *)out_x = *(int *)out_x + (minimap_tile_width >> 1);
  }
  *(int *)out_x = *(int *)out_x + minimap_client_x;
  *(int *)out_y = *(int *)out_y + minimap_client_y;
  return;
}
#undef minimap_origin_x
#undef minimap_origin_y
#undef minimap_margin_y_i32

/* 00406e61 auto */
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define map_cursor_x (*(short *)((u8 *)&g.d_0064b1b4))
#define map_cursor_y (*(short *)((u8 *)&g.d_0064b1b0))
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
#define unit_blink_active (*(char *)((u8 *)&g.d_0062804c))
#define unit_blink_phase (*(char *)((u8 *)&g.d_00628054))
i32 __cdecl minimap_tile_color(int x,int y)

{
  iptr in_bounds;
  iptr visible;
  int city;
  i32 color2;
  
  in_bounds = map_in_bounds(x,y);
  if (in_bounds == 0) {
    color2 = 10;
  }
  else {
    visible = tile_visible_to(x,y,human_civ);
    if ((visible == 0) && (game.reveal_map == '\0')) {
      color2 = 10;
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
            color2 = 0x30;
          }
          else {
            color2 = 0x5d;
          }
        }
        else {
          color2 = 0x29;
        }
      }
      else {
        color2 = *(i32 *)(&civ_secondary_colors + cities[city].owner * 0x10);
      }
    }
  }
  return color2;
}
#undef human_civ
#undef map_cursor_x
#undef map_cursor_y
#undef moving_units_mode
#undef unit_blink_active
#undef unit_blink_phase

/* 0040701e auto */
#define mapview_origin_x (*(i32 *)((u8 *)&g.d_0066ca90))
#define mapview_origin_y (*(i32 *)((u8 *)&g.d_0066ca94))
void __cdecl minimap_draw_view_rect(void)

{
  int bottom;
  i32 top;
  int right;
  int left;
  i8 rect[16];
  
  if ((mapview_margin_x == 0) && (mapview_margin_y == 0)) {
    minimap_tile_to_screen(mapview_origin_x,mapview_origin_y,(iptr)&left,(iptr)&top);
    minimap_tile_to_screen(mapview_end_x,mapview_end_y,(iptr)&right,(iptr)&bottom);
    if (left < right) {
      rect_set((iptr)rect,left,top,right + 1,bottom + 1);
      gfx_target_frame_rect((iptr)rect,0x29);
    }
    else {
      rect_set((iptr)rect,right,top,left + 1,bottom + 1);
      gfx_target_frame_rect((iptr)rect,0x29);
    }
  }
  return;
}
#undef mapview_origin_x
#undef mapview_origin_y

/* 0040733c auto */
#define game_loop_active (*(char *)((u8 *)&g.d_00628044))
#define minimap_hidden (*(char *)((u8 *)&g.d_00624ee0))
#define minimap_origin_x (*(int *)((u8 *)&g.d_0063c814))
#define minimap_origin_y (*(int *)((u8 *)&g.d_0063c810))
#define minimap_margin_y_i32 (*(i32 *)((u8 *)&g.d_0063caf0))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl minimap_redraw(void)

{
  uint y;
  int in_bounds;
  i32 color;
  int row_offset;
  int row;
  int col;
  uint x2;
  int screen_y;
  int screen_x;
  
  if ((minimap_hidden == '\0') && (game_loop_active != '\0')) {
    frame_wnd_layout((FrameWindow *)&minimap_window);
    gfx_set_draw_target((iptr)((u8 *)&g.d_0063c818));
    minimap_calc_layout();
    gfx_fill_draw_target(0);
    screen_y = minimap_client_y + minimap_margin_y_i32;
    for (row = 0; row < minimap_view_rows; row++) {
      y = row + minimap_origin_y;
      if ((y & 1) == 0) {
        row_offset = 0;
      }
      else {
        row_offset = minimap_tile_width >> 1;
      }
      screen_x = minimap_client_x + minimap_margin_x + row_offset;
      for (col = 0; col < minimap_view_cols; col++) {
        x2 = map_wrap_x(col * 2 + minimap_origin_x);
        if ((x2 & 1) != 0) {
          x2--;
        }
        if ((y & 1) != 0) {
          x2++;
        }
        in_bounds = map_in_bounds(x2,y);
        if (in_bounds != 0) {
          color = minimap_tile_color(x2,y);
          gfx_target_fill_rect(screen_x,screen_y,minimap_tile_width,minimap_tile_height,color);
          screen_x += minimap_tile_width;
        }
      }
      screen_y += minimap_tile_height;
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
#undef minimap_margin_y_i32

/* 004074dc auto */
#define city_turn_processing (*(int *)((u8 *)&g.d_0062edf8))
#define minimap_origin_x (*(int *)((u8 *)&g.d_0063c814))
#define minimap_origin_y (*(int *)((u8 *)&g.d_0063c810))
#define minimap_margin_y_i32 (*(i32 *)((u8 *)&g.d_0063caf0))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl minimap_on_lbuttonup(int mouse_x,int mouse_y)

{
  uint tile_y;
  iptr col_x;
  int in_bounds;
  int row_offset;
  uint tile_x;
  
  mouse_x -= minimap_client_x;
  mouse_y -= minimap_client_y;
  if ((((-1 < mouse_x) && (-1 < mouse_y)) && (mouse_x < minimap_client_width)) && (mouse_y < minimap_client_height))
  {
    if (city_turn_processing == 0) {
      tile_y = int_clamp(minimap_origin_y + (mouse_y - minimap_margin_y_i32) / minimap_tile_height,
                                 minimap_origin_y,minimap_origin_y + minimap_view_rows - 1);
      if ((tile_y & 1) == 0) {
        row_offset = 0;
      }
      else {
        row_offset = minimap_tile_width >> 1;
      }
      col_x = int_clamp(((mouse_x - (minimap_margin_x + row_offset)) / minimap_tile_width) * 2 +
                                 minimap_origin_x,minimap_origin_x,minimap_view_cols * 2 - 2 + minimap_origin_x);
      tile_x = map_wrap_x(col_x);
      if ((tile_x & 1) != 0) {
        tile_x--;
      }
      if ((tile_y & 1) != 0) {
        tile_x++;
      }
      in_bounds = map_in_bounds(tile_x,tile_y);
      if (in_bounds != 0) {
        mapview_center_on((ViewWindow *)&map_views,tile_x,tile_y);
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
#undef minimap_margin_y_i32

/* 00407658 auto */
#define city_turn_processing (*(int *)((u8 *)&g.d_0062edf8))
#define minimap_origin_x (*(int *)((u8 *)&g.d_0063c814))
#define minimap_origin_y (*(int *)((u8 *)&g.d_0063c810))
#define minimap_margin_y_i32 (*(i32 *)((u8 *)&g.d_0063caf0))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl minimap_on_rbuttonup(int mouse_x,int mouse_y)

{
  uint tile_y;
  iptr col_x;
  int in_bounds;
  int row_offset;
  uint tile_x;
  int free_view;
  int view;
  
  mouse_x -= minimap_client_x;
  mouse_y -= minimap_client_y;
  if ((((-1 < mouse_x) && (-1 < mouse_y)) && (mouse_x < minimap_client_width)) && (mouse_y < minimap_client_height))
  {
    if (city_turn_processing == 0) {
      tile_y = int_clamp(minimap_origin_y + (mouse_y - minimap_margin_y_i32) / minimap_tile_height,
                                 minimap_origin_y,minimap_origin_y + minimap_view_rows - 1);
      if ((tile_y & 1) == 0) {
        row_offset = 0;
      }
      else {
        row_offset = minimap_tile_width >> 1;
      }
      col_x = int_clamp(((mouse_x - (minimap_margin_x + row_offset)) / minimap_tile_width) * 2 +
                                 minimap_origin_x,minimap_origin_x,minimap_view_cols * 2 - 2 + minimap_origin_x);
      tile_x = map_wrap_x(col_x);
      if ((tile_x & 1) != 0) {
        tile_x--;
      }
      if ((tile_y & 1) != 0) {
        tile_x++;
      }
      in_bounds = map_in_bounds(tile_x,tile_y);
      if (in_bounds != 0) {
        free_view = -1;
        for (view = 1; view < 8; view++) {
          if (*(short *)(&map_view_open_flags + view * 0x3f0) == 0) {
            free_view = view;
            break;
          }
        }
        if (0 < free_view) {
          mapview_create((ViewWindow *)(&map_views + free_view * 0x3f0));
          mapview_center_on
                    ((ViewWindow *)(&map_views + free_view * 0x3f0),tile_x,tile_y);
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
#undef minimap_margin_y_i32

/* 0040785b auto */
#define frame_border_width (*(int *)((u8 *)&g.d_0063359c))
#define frame_caption_height (*(int *)((u8 *)&g.d_00633598))
#define main_frame_nonclient_width (*(int *)((u8 *)&g.d_006acbb0))
void __cdecl minimap_calc_rect(void)

{
  int client_w;
  int height2;
  int width2;
  int top;
  
  client_w = wnd_client_width((WndBase *)&main_frame_wnd);
  width2 = 0xa0;
  height2 = 100;
  if ((1000 < main_frame_nonclient_width + client_w) && (width2 = 0xf0, map_layout_wide != 0)) {
    height2 = 0x96;
  }
  if (height2 < map.height) {
    height2 = (int)map.height;
  }
  width2 += frame_border_width * 2;
  top = 0;
  if (map_layout_wide != 0) {
    top = minimap_margin + 1;
  }
  rect_set_xywh((iptr)((u8 *)&g.d_00655324),client_w - (sys_dlgframe_w2 + width2),top,width2 + sys_dlgframe_w2,
                     height2 + frame_border_width + frame_caption_height + sys_dlgframe_h2);
  return;
}
#undef frame_border_width
#undef frame_caption_height
#undef main_frame_nonclient_width

/* 0040795a auto */
void __cdecl minimap_on_size(void)

{
  wnd_get_rect_in_parent((WndBase *)&minimap_wnd,(iptr)((u8 *)&g.d_00655324));
  return;
}

/* 00407980 auto */
void __cdecl minimap_on_move(void)

{
  wnd_get_rect_in_parent((WndBase *)&minimap_wnd,(iptr)((u8 *)&g.d_00655324));
  return;
}

/* 004079a6 auto */
#define minimap_hidden (*(i8 *)((u8 *)&g.d_00624ee0))
#define minimap_wnd_rect_top (*(i32 *)((u8 *)&g.d_00655328))
#define saved_layout_valid (*(int *)((u8 *)&g.d_00655280))
#define turn_resume_civ (*(char *)((u8 *)&g.d_00628048))
void __cdecl minimap_window_create(void)

{
  int wnd_height;
  int wnd_width;
  i32 title_text;
  i32 wnd_style;
  i32 wnd_x;
  i32 wnd_y;
  i32 create_arg7;
  i32 create_arg8;
  i32 create_arg9;
  
  minimap_hidden = 0;
  if ((turn_resume_civ == '\0') || (saved_layout_valid == 0)) {
    minimap_calc_rect();
  }
  create_arg9 = 0;
  create_arg8 = 0;
  create_arg7 = 6;
  wnd_height = rect_height((iptr)((u8 *)&g.d_00655324));
  wnd_height -= sys_dlgframe_h2;
  wnd_width = rect_width((iptr)((u8 *)&g.d_00655324));
  wnd_width -= sys_dlgframe_w2;
  wnd_style = 6;
  wnd_x = minimap_wnd_rect;
  wnd_y = minimap_wnd_rect_top;
  title_text = label_string(*(i32 *)(label_string_ids + 0x18));
  frame_wnd_create
            ((FrameWindow *)&minimap_window,title_text,wnd_style,wnd_x,wnd_y,wnd_width,wnd_height,create_arg7,create_arg8,create_arg9);
  wnd_set_min_size((ModalMenuWindow *)&minimap_wnd,0x28,0x19);
  wnd_set_redraw_callback((SurfaceWindow *)&minimap_window,(iptr)minimap_redraw);
  wnd_set_lbuttonup_handler((WndEventHandlers *)&minimap_wnd_handlers,(iptr)minimap_on_lbuttonup);
  wnd_set_rbuttonup_handler((WndEventHandlers *)&minimap_wnd_handlers,(iptr)minimap_on_rbuttonup);
  wnd_set_keydown_handler((WndEventHandlers *)&minimap_wnd_handlers,(iptr)map_window_key);
  wnd_set_char_handler((WndEventHandlers *)&minimap_wnd_handlers,(iptr)map_window_ascii);
  wnd_set_cursor((WndBase *)&minimap_wnd,0x1ff);
  wnd_set_icon((WndBase *)&minimap_wnd,1);
  wnd_set_minimize_handler((WndEventHandlers *)&minimap_wnd_handlers,(iptr)minimap_on_minimize);
  wnd_set_restore_handler((WndEventHandlers *)&minimap_wnd_handlers,(iptr)minimap_on_restore);
  wnd_set_close_handler((WndEventHandlers *)&minimap_wnd_handlers,(iptr)minimap_on_close);
  wnd_set_size_handler((WndEventHandlers *)&minimap_wnd_handlers,(iptr)minimap_on_size);
  wnd_set_move_handler((WndEventHandlers *)&minimap_wnd_handlers,(iptr)minimap_on_move);
  wnd_repaint((SurfaceWindow *)&minimap_window);
  if (game.multiplayer != 1) {
    window_show((WindowObjectView *)&minimap_window);
  }
  return;
}
#undef minimap_hidden
#undef minimap_wnd_rect_top
#undef saved_layout_valid
#undef turn_resume_civ

/* 00407b31 auto */
#define minimap_hidden (*(i8 *)((u8 *)&g.d_00624ee0))
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
void __thiscall mapview_redraw_cursor_tile(ViewWindow *this)

{
  mapview_redraw_area(this,(int)map_cursor_x,(int)map_cursor_y,0,human_civ,1);
  return;
}
#undef human_civ
#undef map_cursor_x
#undef map_cursor_y

/* 0041033a auto */
void __cdecl mapviews_redraw_cursor(void)

{
  int view;
  
  for (view = 0; view < 8; view++) {
    if ((view == 0) || (*(short *)(&map_view_open_flags + view * 0x3f0) != 0)) {
      mapview_redraw_cursor_tile((ViewWindow *)(&map_views + view * 0x3f0));
    }
  }
  return;
}

/* 004103ae auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
void __cdecl mapview_on_redraw(void)

{
  int child_wnd;
  ViewWindow *this2;
  
  city_window_bring_to_top((WindowObjectView *)&city_window);
  child_wnd = wnd_get_active_child();
  if (child_wnd == 0) {
    this2 = (ViewWindow *)0x0;
  }
  else {
    this2 = (ViewWindow *)(child_wnd - 0x48);
  }
  mapview_redraw(this2,human_civ,1);
  return;
}
#undef human_civ

/* 00410402 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define unit_blink_active (*(i8 *)((u8 *)&g.d_0062804c))
void __thiscall mapview_center_on(ViewWindow *this,iptr x,i32 y)

{
  i8 saved_blink;
  i32 wrapped_x;
  
  wrapped_x = map_wrap_x(x);
  *(short *)&this->tax_rate_sel = (short)wrapped_x;
  *(i16 *)((int)&this->tax_rate_sel + 2) = (i16)y;
  saved_blink = unit_blink_active;
  unit_blink_active = 0;
  mapview_redraw(this,human_civ,1);
  unit_blink_active = saved_blink;
  return;
}
#undef human_civ
#undef unit_blink_active

/* 00410464 auto */
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
#define unit_blink_phase (*(i8 *)((u8 *)&g.d_00628054))
#define unit_blink_skip_tick (*(i8 *)((u8 *)&g.d_0062805c))
int __thiscall mapview_scroll_if_near_edge(ViewWindow *this,int x,int y)

{
  uptr view_left;
  uptr view_top;
  u32 view_cols;
  u32 view_bottom;
  int need_scroll;
  
  need_scroll = 0;
  view_left = this->sci_rate_sel;
  view_top = this->init_tax_rate;
  if ((((game.rules & 0x8000) == 0) && (x <= (int)(this->dialog_w * 2))) &&
     ((int)((int)map.width + this->dialog_w * -2) <= (int)view_left)) {
    x += map.width;
  }
  view_cols = this->label_x_value;
  view_bottom = this->init_sci_rate;
  if (this->tax_label_y == 0) {
    if ((game.rules & 0x8000) != 0) {
      x = int_clamp(x,2,map.width - 3);
    }
    if ((x <= (int)(view_left + 1)) || ((int)(view_cols * 2 + view_left - 3) <= x)) {
      need_scroll = 1;
    }
  }
  if ((this->lux_label_y == 0) &&
     ((y = int_clamp(y,2,map.height - 3), y <= (int)(view_top + 1) ||
      ((int)(view_bottom - 1) <= y)))) {
    need_scroll = 1;
  }
  if (need_scroll != 0) {
    unit_blink_skip_tick = 1;
    unit_blink_phase = moving_units_mode == 0;
    mapview_center_on(this,x,y);
  }
  return need_scroll;
}
#undef moving_units_mode
#undef unit_blink_phase
#undef unit_blink_skip_tick

/* 004105f8 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define map_redraw_busy (*(i32 *)((u8 *)&g.d_006ad908))
uint __cdecl mapviews_ensure_visible(i32 x,i32 y,iptr civ)

{
  ushort track_mask;
  uint scrolled;
  uint result;
  int view;
  
  result = 1;
  map_redraw_busy = 1;
  if (civ < 0) {
    track_mask = 3;
  }
  else if (human_civ == civ) {
    track_mask = 1;
  }
  else {
    track_mask = 2;
  }
  for (view = 0; view < 8; view++) {
    if ((view == 0) || (*(short *)(&map_view_open_flags + view * 0x3f0) != 0)) {
      if ((track_mask & *(ushort *)(&mapview_track_moves + view * 0x3f0)) == 0) {
        result = 0;
      }
      else {
        scrolled = mapview_scroll_if_near_edge
                          ((ViewWindow *)(&map_views + view * 0x3f0),x,y);
        result = result & scrolled;
      }
    }
  }
  map_redraw_busy = 0;
  return result;
}
#undef human_civ
#undef map_redraw_busy

/* 004106fd auto */
int __thiscall
mapview_point_unit_dir
          (ViewWindow *this,int mouse_x,int mouse_y,i32 unit_x,i32 unit_y)

{
  short client_dx;
  short client_dy;
  int dir;
  int tile_sx[2];
  int off_y;
  int off_x;
  int tile_sy;
  
  mapview_tile_to_screen(this,(iptr)tile_sx,(iptr)&tile_sy,unit_x,unit_y);
  if (((short)mouse_x < tile_sx[0]) || ((short)mouse_y < tile_sy)) {
    dir = 8;
  }
  else if (((int)(short)mouse_x < (int)(this->total_tax + tile_sx[0])) &&
          ((int)(short)mouse_y < (int)(this->total_science + tile_sy))) {
    off_x = (short)mouse_x - tile_sx[0];
    off_y = (short)mouse_y - tile_sy;
    client_dx = (short)mouse_x - (short)this->client_x;
    client_dy = (short)mouse_y - (short)this->client_y;
    if ((client_dx < 0) || (client_dy < 0)) {
      dir = 8;
    }
    else if (((int)client_dx < (int)this->client_width) && ((int)client_dy < (int)this->client_height)) {
      dir = surface_get_pixel((DibSurface *)&this->right_agreed_button,off_x,off_y);
      dir = dir - 10 >> 4;
    }
    else {
      dir = 8;
    }
  }
  else {
    dir = 8;
  }
  return dir;
}

/* 00410835 auto */
#define city_turn_processing (*(int *)((u8 *)&g.d_0062edf8))
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
void __cdecl mapview_on_mousemove(int mouse_x,int mouse_y)

{
  iptr child_wnd;
  int check;
  iptr x2;
  iptr unit;
  iptr y2;
  int civ;
  uptr cursor_id;
  ViewWindow *view;
  int dir;
  
  child_wnd = wnd_get_active_child();
  if (child_wnd == 0) {
    view = (ViewWindow *)0x0;
  }
  else {
    view = (ViewWindow *)(child_wnd - 0x48);
  }
  if ((city_turn_processing == 0) && (view->tax_scrollbar != 0x1fe)) {
    check = ui_paradrop_cursor_active();
    if (check == 0) {
      cursor_id = 0x201;
      if ((((((byte)game.game_options & 0x80) != 0) && (moving_units_mode == 1)) &&
          (unit = (iptr)game.active_unit, -1 < unit)) &&
         ((dir = mapview_point_unit_dir
                               (view,mouse_x,mouse_y,(int)units[unit].x,
                                (int)units[unit].y), -1 < dir && (dir < 8)))) {
        cursor_id = (dir + 1U & 7) + 500;
      }
    }
    else {
      cursor_id = 0x202;
      unit = (iptr)game.active_unit;
      check = mapview_screen_to_tile
                        ((MapViewHitView *)view,(iptr)&x2,(iptr)&y2,mouse_x,mouse_y);
      if (check != 0) {
        return;
      }
      check = map_in_bounds(x2,y2);
      if (check == 0) {
        return;
      }
      check = map_distance(x2,y2,(int)units[unit].x,(int)units[unit].y);
      if ((int)(uint)cosmic.paradrop_range < check) {
        cursor_id = 0x203;
      }
      else {
        check = tile_is_ocean(x2,y2);
        if (check == 0) {
          civ = tile_unit_owner(x2,y2);
          if ((-1 < civ) && (units[unit].owner != civ)) {
            cursor_id = 0x203;
          }
        }
        else {
          cursor_id = 0x203;
        }
      }
    }
    if (view->tax_scrollbar != cursor_id) {
      view->tax_scrollbar = cursor_id;
      wnd_set_cursor_now((WndCursorView *)view->window_2,cursor_id,1);
    }
  }
  return;
}
#undef city_turn_processing
#undef moving_units_mode

/* 00410a64 auto */
#define mapview_cursor_id (*(i32 *)((u8 *)&g.d_0066cb00))
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
#define mapview_cursor_id (*(i32 *)((u8 *)&g.d_0066cb00))
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
#define mapview_cursor_id (*(i32 *)((u8 *)&g.d_0066cb00))
#define mapview_drag_hold_timer (*(i32 *)((u8 *)&g.d_00624f54))
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
void __cdecl mapview_on_lbuttondown(void)

{
  SHORT SVar1;
  iptr child_wnd;
  int paradrop;
  iptr view;
  
  if ((city_turn_processing == 0) && ((game.multiplayer == '\0' || (ui_input_busy == 0)))) {
    ui_input_busy = 1;
    child_wnd = wnd_get_active_child();
    if (child_wnd == 0) {
      view = 0;
    }
    else {
      view = child_wnd - 0x48;
    }
    mapview_cancel_drag();
    if ((moving_units_mode == 1) && (paradrop = ui_paradrop_cursor_active(), paradrop == 0)) {
      mapview_drag_view_index = *(int *)(view + 0x2d8);
      SVar1 = GetAsyncKeyState(0x10);
      if ((char)((ushort)SVar1 >> 8) == '\0') {
        mapview_drag_hold_timer = game_timer_create((iptr)mapview_drag_hold_expired,400,1);
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

/* 00410cfa auto */
#define city_turn_processing (*(int *)((u8 *)&g.d_0062edf8))
#define mapview_drag_hold_timer (*(int *)((u8 *)&g.d_00624f54))
void __cdecl mapview_on_lbuttonup_any(void)

{
  int view;
  
  if ((city_turn_processing == 0) && ((game.multiplayer == '\0' || (ui_input_busy == 0)))) {
    ui_input_busy = 1;
    view = wnd_get_active_child();
    if (view == 0) {
      view = 0;
    }
    else {
      view -= 0x48;
    }
    if (-1 < mapview_drag_hold_timer) {
      mapview_cancel_drag();
    }
    wnd_release_capture((WndBase *)(view + 0x48));
    ui_input_busy = 0;
  }
  return;
}
#undef city_turn_processing
#undef mapview_drag_hold_timer

/* 00410e46 auto */
#define mapview_cursor_id (*(i32 *)((u8 *)&g.d_0066cb00))
void __cdecl mapviews_set_paradrop_cursor(void)

{
  int view;
  
  for (view = 0; view < 8; view++) {
    if ((view == 0) || (*(short *)(&map_view_open_flags + view * 0x3f0) != 0)) {
      (&mapview_cursor_id)[view * 0xfc] = 0x202;
      wnd_set_cursor_now((WndCursorView *)(&map_view_wnds + view * 0x3f0),0x202,1);
    }
  }
  return;
}
#undef mapview_cursor_id

/* 00410ed8 auto */
#define mapview_cursor_id (*(i32 *)((u8 *)&g.d_0066cb00))
void __cdecl mapviews_reset_cursor(void)

{
  int paradrop;
  int view;
  
  paradrop = ui_paradrop_cursor_active();
  if (paradrop != 0) {
    for (view = 0; view < 8; view++) {
      if ((view == 0) || (*(short *)(&map_view_open_flags + view * 0x3f0) != 0)) {
        (&mapview_cursor_id)[view * 0xfc] = 0x201;
        wnd_set_cursor_now((WndCursorView *)(&map_view_wnds + view * 0x3f0),0x201,1);
      }
    }
  }
  return;
}
#undef mapview_cursor_id

/* 004116c1 auto */
void __cdecl mapview_on_lbuttonup(i32 x,i32 y)

{
  map_window_click(x,y,0);
  return;
}

/* 004116e3 auto */
void __cdecl mapview_on_rbuttonup(i32 x,i32 y)

{
  map_window_click(x,y,1);
  return;
}

/* 004132b7 auto */
void __cdecl mapview_calc_rect(void)

{
  int client_w;
  int minimap_w;
  iptr height2;
  int top;
  
  client_w = wnd_client_width((WndBase *)&main_frame_wnd);
  minimap_w = rect_width((iptr)((u8 *)&g.d_00655324));
  height2 = wnd_client_height((WndBase *)&main_frame_wnd);
  height2++;
  top = 0;
  if (map_layout_wide != 0) {
    top = minimap_margin + 1;
    height2 -= (minimap_margin + 1);
  }
  rect_set_xywh((iptr)((u8 *)&g.d_006552a4),0,top,client_w - minimap_w,height2);
  return;
}

/* 00413350 auto */
bool __cdecl mapview_on_close(void)

{
  iptr child_wnd;
  bool is_main;
  iptr view;
  
  child_wnd = wnd_get_active_child();
  if (child_wnd == 0) {
    view = 0;
  }
  else {
    view = child_wnd - 0x48;
  }
  is_main = *(int *)(view + 0x2d8) == 0;
  if (is_main) {
    wnd_minimize((WndBase *)(view + 0x48));
  }
  else {
    *(i16 *)(view + 0x2dc) = 0;
  }
  return !is_main;
}

/* 004133c2 auto */
void __cdecl mapview_on_size(void)

{
  iptr child_wnd;
  iptr view;
  
  child_wnd = wnd_get_active_child();
  if (child_wnd == 0) {
    view = 0;
  }
  else {
    view = child_wnd - 0x48;
  }
  wnd_get_rect_in_parent
            ((WndBase *)(view + 0x48),
             (iptr)(&map_view_saved_rects + *(int *)(view + 0x2d8) * 0x10));
  return;
}

/* 0041341c auto */
void __cdecl mapview_on_move(void)

{
  iptr child_wnd;
  iptr view;
  
  child_wnd = wnd_get_active_child();
  if (child_wnd == 0) {
    view = 0;
  }
  else {
    view = child_wnd - 0x48;
  }
  wnd_get_rect_in_parent
            ((WndBase *)(view + 0x48),
             (iptr)(&map_view_saved_rects + *(int *)(view + 0x2d8) * 0x10));
  return;
}

/* 00413476 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
void __thiscall mapview_update_title(FrameWindow *this)

{
  bool show_mode;
  iptr adjective;
  int view;
  uint mode;
  
  mode = (uint)((this->max_rate_value & 0x10000) != 0);
  if ((this->max_rate_value & 0x20000) != 0) {
    mode += 2;
  }
  text_clear();
  if (this->rates_civ == 0) {
    if (game_language != 1) {
      adjective = civ_get_adjective(human_civ);
      text_append_str(adjective);
      if (game_language == 2) {
        text_append((iptr)((u8 *)&g.d_00625090));
      }
      text_append_space();
    }
    show_mode = false;
    for (view = 1; view < 8; view++) {
      if (*(short *)(&map_view_open_flags + view * 0x3f0) != 0) {
        show_mode = true;
        break;
      }
    }
  }
  else {
    show_mode = true;
  }
  text_append_label(4);
  if (show_mode) {
    text_append_colon();
    text_append_label(mode + 300);
  }
  frame_wnd_set_caption(this,(iptr)((u8 *)&g.d_00679640));
  return;
}
#undef human_civ

/* 004135ab auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
void __cdecl mapview_on_caption_button(i32 button)

{
  iptr child_wnd;
  ViewWindow *this2;
  
  if ((game.multiplayer == '\0') || (ui_input_busy == 0)) {
    ui_input_busy = 1;
    child_wnd = wnd_get_active_child();
    if (child_wnd == 0) {
      this2 = (ViewWindow *)0x0;
    }
    else {
      this2 = (ViewWindow *)(child_wnd - 0x48);
    }
    switch(button) {
    case 1:
      *(i16 *)&this2->max_rate_value = 0;
      wnd_destroy_with_surface((DibSurface *)this2);
      mapview_update_title((FrameWindow *)&map_views);
      wnd_repaint((SurfaceWindow *)&map_views);
      break;
    case 2:
      if ((short)this2->lux_rate_sel < 8) {
        *(short *)&this2->lux_rate_sel = (short)this2->lux_rate_sel + 1;
        mapview_redraw(this2,human_civ,1);
      }
      break;
    case 3:
      if (-7 < (short)this2->lux_rate_sel) {
        *(short *)&this2->lux_rate_sel = (short)this2->lux_rate_sel - 1;
        mapview_redraw(this2,human_civ,1);
      }
      break;
    case 4:
      *(ushort *)((int)&this2->max_rate_value + 2) = *(short *)((int)&this2->max_rate_value + 2) + 1U & 3;
      mapview_update_title((FrameWindow *)this2);
      mapview_redraw(this2,human_civ,1);
    }
    ui_input_busy = 0;
  }
  return;
}
#undef human_civ

/* 00413717 auto */
#define saved_layout_valid (*(int *)((u8 *)&g.d_00655280))
#define turn_resume_civ (*(char *)((u8 *)&g.d_00628048))
void __thiscall mapview_create(ViewWindow *this)

{
  i32 title_text;
  i32 wnd_style;
  i32 create_arg7;
  i32 create_arg8;
  i32 create_arg9;
  int height2;
  int width2;
  int top;
  int left;
  
  mapview_init_state(this,this->rates_civ);
  if ((turn_resume_civ == '\0') || (saved_layout_valid == 0)) {
    *(i16 *)&this->lux_rate_sel = 0;
    if (999 < screen_width) {
      *(i16 *)&this->lux_rate_sel = 2;
    }
    if (this->rates_civ == 0) {
      mapview_calc_rect();
    }
  }
  if (this->rates_civ == 0) {
    *(i16 *)((int)&this->max_rate_value + 2) = 3;
  }
  else {
    *(i16 *)((int)&this->max_rate_value + 2) = 2;
  }
  if ((this->rates_civ == 0) || ((short)this->max_rate_value != 0)) {
    left = *(int *)(&map_view_saved_rects + this->rates_civ * 0x10);
    top = *(int *)(&map_view_saved_rect_tops + this->rates_civ * 0x10);
    width2 = rect_width((iptr)(&map_view_saved_rects + this->rates_civ * 0x10));
    width2 -= sys_dlgframe_w2;
    height2 = rect_height((iptr)(&map_view_saved_rects + this->rates_civ * 0x10));
    height2 -= sys_dlgframe_h2;
  }
  else {
    left = this->rates_civ * 0x28;
    top = this->rates_civ * 0x28;
    width2 = 500;
    height2 = 300;
    rect_set_xywh((iptr)(&map_view_saved_rects + this->rates_civ * 0x10),left,top,
                       sys_dlgframe_w2 + 500,sys_dlgframe_h2 + 300);
  }
  *(i16 *)&this->max_rate_value = 1;
  create_arg9 = 0;
  create_arg8 = 0;
  create_arg7 = 6;
  wnd_style = 6;
  title_text = label_string(*(i32 *)(label_string_ids + 0x10));
  frame_wnd_create
            ((FrameWindow *)this,title_text,wnd_style,left,top,width2,height2,create_arg7,create_arg8,create_arg9)
  ;
  wnd_set_min_size((ModalMenuWindow *)this->window_2,0x100,0x80);
  wnd_set_redraw_callback((SurfaceWindow *)this,(iptr)mapview_on_redraw);
  wnd_set_lbuttonup_handler((WndEventHandlers *)(this->event_handlers),(iptr)mapview_on_lbuttonup);
  wnd_set_rbuttonup_handler((WndEventHandlers *)(this->event_handlers),(iptr)mapview_on_rbuttonup);
  wnd_set_lbuttondown_handler((WndHandlersMouseSetView *)(this->event_handlers),(iptr)mapview_on_lbuttondown);
  wnd_set_lbuttonup_any_handler((WndHandlersMouseSetView *)(this->event_handlers),(iptr)mapview_on_lbuttonup_any);
  wnd_set_mousemove_handler((WndHandlersMouseSetView *)(this->event_handlers),(iptr)mapview_on_mousemove);
  wnd_set_dblclick_handler((WndHandlersMouseSetView *)(this->event_handlers),(iptr)map_window_double_click);
  wnd_set_char_handler((WndEventHandlers *)(this->event_handlers),(iptr)map_window_ascii);
  wnd_set_keydown_handler((WndEventHandlers *)(this->event_handlers),(iptr)map_window_key);
  wnd_set_close_handler((WndEventHandlers *)(this->event_handlers),(iptr)mapview_on_close);
  wnd_set_size_handler((WndEventHandlers *)(this->event_handlers),(iptr)mapview_on_size);
  wnd_set_move_handler((WndEventHandlers *)(this->event_handlers),(iptr)mapview_on_move);
  mapview_update_title((FrameWindow *)this);
  if (this->rates_civ != 0) {
    frame_wnd_add_caption_button((PortraitDialog *)this,(iptr)((u8 *)&g.d_00645120),1);
  }
  frame_wnd_add_caption_button((PortraitDialog *)this,(iptr)((u8 *)&g.d_00648820),2);
  frame_wnd_add_caption_button((PortraitDialog *)this,(iptr)((u8 *)&g.d_00647788),3);
  if (this->rates_civ != 0) {
    frame_wnd_add_caption_button((PortraitDialog *)this,(iptr)((u8 *)&g.d_00647348),4);
  }
  wnd_set_caption_button_handler((FrameWindow *)this,(iptr)mapview_on_caption_button);
  wnd_repaint((SurfaceWindow *)this);
  if (game.multiplayer != 1) {
    window_show((WindowObjectView *)this);
  }
  if (this->rates_civ != 0) {
    mapview_update_title((FrameWindow *)&map_views);
    wnd_repaint((SurfaceWindow *)&map_views);
  }
  return;
}
#undef saved_layout_valid
#undef turn_resume_civ

/* 00413a90 auto */
#define main_view_timer_shown (*(i32 *)((u8 *)&g.d_0066c988))
#define mp_turn_time_limit_ms (*(int *)((u8 *)&g.d_00654b70))
#define timer_alt_kind_request (*(i32 *)((u8 *)&g.d_00637ef8))
#define turn_resume_civ (*(char *)((u8 *)&g.d_00628048))
#define main_view_status_shown_i32 (*(i32 *)((u8 *)&g.d_0066c98c))
#define map_view_open_flags_i32 (*(i32 *)((u8 *)&g.d_0066ca84))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl mapviews_create_all(void)

{
  int view;
  
  for (view = 0; view < 8; view++) {
    mapview_init_state((ViewWindow *)(&map_views + view * 0x3f0),view);
    if (turn_resume_civ == '\0') {
      if (view == 0) {
        map_view_open_flags_i32 = 1;
      }
      else {
        *(i16 *)(&map_view_open_flags + view * 0x3f0) = 0;
      }
    }
    if ((view == 0) || (*(short *)(&map_view_open_flags + view * 0x3f0) != 0)) {
      mapview_create((ViewWindow *)(&map_views + view * 0x3f0));
    }
  }
  main_view_status_shown_i32 = 1;
  if (mp_turn_time_limit_ms != 0) {
    main_view_timer_shown = 1;
  }
  timer_alt_kind_request = 1;
  unit_blink_timer = game_timer_create((iptr)unit_blink_timer_tick,0x96,0xffffffff);
  eot_blink_timer = game_timer_create((iptr)eot_blink_timer_tick,500,0xffffffff);
  timer_alt_kind_request = 0;
  return;
}
#undef main_view_timer_shown
#undef mp_turn_time_limit_ms
#undef timer_alt_kind_request
#undef turn_resume_civ
#undef main_view_status_shown_i32
#undef map_view_open_flags_i32

/* 00413bd1 auto */
#define timer_alt_kind_request (*(i32 *)((u8 *)&g.d_00637ef8))
void __cdecl mapviews_destroy_all(void)

{
  int view;
  
  timer_alt_kind_request = 1;
  game_timer_destroy(unit_blink_timer);
  game_timer_destroy(eot_blink_timer);
  timer_alt_kind_request = 0;
  for (view = 0; view < 8; view++) {
    if ((view == 0) || (*(short *)(&map_view_open_flags + view * 0x3f0) != 0)) {
      wnd_destroy_with_surface((DibSurface *)(&map_views + view * 0x3f0));
    }
  }
  return;
}
#undef timer_alt_kind_request

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
void __thiscall clickmap_remove_at(ClickMapRemoveView *this,int index)

{
  int n;
  u8 *src;
  u8 *dst;
  int i;
  
  for (i = index; i < (int)(this->entry_count - 1); i++) {
    src = this->hit_regions + i * 0x18 + 0x18;
    dst = this->hit_regions + i * 0x18;
    for (n = 6; n != 0; n--) {
      *(i32 *)dst = *(i32 *)src;
      src += 4;
      dst += 4;
    }
  }
  this->entry_count--;
  return;
}

/* 0046ac89 auto */
void __thiscall clickmap_remove_by_id(ClickMapRemoveView *this,int id)

{
  u32 count;
  iptr offset;
  u32 idx;
  
  count = this->entry_count;
  while (idx = count - 1, -1 < (int)idx) {
    offset = count * 0x18;
    count = idx;
    if (*(int *)(this->hit_regions + offset - 8) == id) {
      clickmap_remove_at(this,idx);
    }
  }
  return;
}

/* 0046ace7 auto */
u32 __thiscall
clickmap_add
          (ClickMap *this,iptr id,i32 value,i32 x,i32 y,
          iptr width,iptr height)

{
  u32 index;
  
  index = 0xffffffff;
  if ((int)this->entry_count < 200) {
    index = this->entry_count;
    this->entry_count++;
    rect_set_xywh((iptr)(this->hit_regions + index * 0x18),x,y,width,height);
    *(iptr *)(this->hit_regions + index * 0x18 + 0x14) = id;
    *(i32 *)(this->hit_regions + index * 0x18 + 0x10) = value;
  }
  return index;
}

/* 0046ad85 auto */
int __thiscall
clickmap_hit_test(ClickMapHitTestView *this,int x,int y,iptr out_id,iptr out_value)

{
  int hit;
  int i;
  
  hit = -1;
  i = 0;
  do {
    if ((int)this->region_count <= i) {
LAB_0046ae34:
      if (-1 < hit) {
        if (out_id != 0) {
          *(i32 *)out_id = *(i32 *)(this->hit_regions + hit * 0x18 + 0x14);
        }
        if (out_value != 0) {
          *(i32 *)out_value = *(i32 *)(this->hit_regions + hit * 0x18 + 0x10);
        }
      }
      return hit;
    }
    if ((((*(int *)(this->hit_regions + i * 0x18) <= x) &&
         (x < *(int *)(this->hit_regions + i * 0x18 + 8))) &&
        (*(int *)(this->hit_regions + i * 0x18 + 4) <= y)) &&
       (y < *(int *)(this->hit_regions + i * 0x18 + 0xc))) {
      hit = i;
      goto LAB_0046ae34;
    }
    i++;
  } while( true );
}

/* 00472b0a auto */
#define mapview_zoom (*(short *)((u8 *)&g.d_0066ca8c))
void __cdecl mapview_draw_tile_number(i32 x,i32 y,int number,i32 color)

{
  int in_view;
  iptr width;
  iptr height;
  i32 screen_y;
  i32 screen_x;
  char num_text[80];
  i8 rect[16];
  
  in_view = mapview_tile_in_view((ViewWindow *)&map_views,x,y);
  if (in_view != 0) {
    mapview_tile_to_screen
              ((ViewWindow *)&map_views,(iptr)&screen_x,(iptr)&screen_y,x,y);
    width = gfx_zoom_scale(0x40,(int)mapview_zoom);
    height = gfx_zoom_scale(0x20,(int)mapview_zoom);
    rect_set_xywh((iptr)rect,screen_x,screen_y,width,height);
    __itoa(number,num_text,10);
    gfx_set_text_color_index(10);
    rect_offset((iptr)rect,0xffffffff,0xffffffff);
    surface_draw_text_in_rect
              ((DibSurface *)&map_views,(iptr)((u8 *)&g.d_0066cae0),(iptr)num_text,(iptr)rect,0);
    rect_offset((iptr)rect,3,3);
    surface_draw_text_in_rect
              ((DibSurface *)&map_views,(iptr)((u8 *)&g.d_0066cae0),(iptr)num_text,(iptr)rect,0);
    rect_offset((iptr)rect,0xfffffffe,0xfffffffe);
    gfx_set_text_color_index(color);
    surface_draw_text_in_rect
              ((DibSurface *)&map_views,(iptr)((u8 *)&g.d_0066cae0),(iptr)num_text,(iptr)rect,0);
    wnd_blit_surface_rect((DibSurface *)&map_views,(iptr)rect);
  }
  return;
}
#undef mapview_zoom

/* 00479ede auto */
#define turn_resume_civ (*(char *)((u8 *)&g.d_00628048))
void __thiscall mapview_init_state(ViewWindow *this,u32 view_index)

{
  this->rates_civ = view_index;
  if (view_index == 0) {
    *(i16 *)((int)&this->max_rate_value + 2) = 1;
  }
  else {
    *(i16 *)((int)&this->max_rate_value + 2) = 0;
  }
  this->tax_scrollbar = 0xffffffff;
  if (turn_resume_civ == '\0') {
    *(i16 *)&this->lux_rate_sel = 0;
    *(i16 *)&this->tax_rate_sel = map.width >> 1;
    *(i16 *)((int)&this->tax_rate_sel + 2) = map.height >> 1;
    if ((this->tax_rate_sel & 1) != 0) {
      *(short *)&this->tax_rate_sel = (short)this->tax_rate_sel - 1;
    }
    if ((this->tax_rate_sel & 0x10000) != 0) {
      *(short *)&this->tax_rate_sel = (short)this->tax_rate_sel + 1;
    }
  }
  this->no_thanks_button_value = 0xfffffc19;
  return;
}
#undef turn_resume_civ

/* 00479fbe auto */
void __thiscall mapview_update_layout(ViewWindow *this)

{
  u32 scaled;
  i32 wrapped_x;
  uptr wrapped;
  uint clamped;
  i8 dir_mask_rect[16];
  i8 pick_mask_rect[16];
  uptr font_size;
  
  this->button_area_height = this->client_width;
  this->row_spacing_value = this->client_height;
  scaled = mapview_zoom_scale(this,0x40);
  this->total_tax = scaled;
  scaled = mapview_zoom_scale(this,0x20);
  this->total_science = scaled;
  this->total_upkeep_value = (int)this->total_tax / 2;
  this->margin_value = (int)this->total_science / 2;
  this->bar_gap = (int)(this->total_tax + ((int)this->total_tax >> 0x1f & 3U)) >> 2;
  this->bar_width_value = (int)(this->total_science + ((int)this->total_science >> 0x1f & 3U)) >> 2;
  this->bar_height = this->total_tax;
  this->button_row_width = this->total_science + this->margin_value;
  this->dialog_w = (int)((this->button_area_height - 1) + this->total_tax) / (int)this->total_tax;
  this->dialog_h = (int)((this->row_spacing_value - 1) + this->total_science) / (int)this->total_science;
  this->label_x_value = (int)(this->total_upkeep_value * 3 - 1 + this->button_area_height) / (int)this->total_tax;
  this->header_y_value = (int)(this->margin_value * 3 - 1 + this->row_spacing_value) / (int)this->total_science;
  this->tax_label_y = 0;
  this->lux_label_y = 0;
  if ((int)map.width / 2 < (int)this->dialog_w) {
    this->dialog_w = (int)map.width / 2;
    this->tax_label_y = (int)(this->button_area_height - this->total_tax * this->dialog_w) >> 1;
    this->label_x_value = this->dialog_w + 1;
  }
  if ((int)map.height < (int)this->dialog_h) {
    this->dialog_h = (int)map.height / 2;
    this->lux_label_y = (int)(this->row_spacing_value - this->total_science * this->dialog_h) >> 1;
    this->header_y_value = (int)map.height + 1;
  }
  wrapped_x = map_wrap_x((int)(short)this->tax_rate_sel);
  *(short *)&this->tax_rate_sel = (short)wrapped_x;
  this->init_tax_rate = (int)*(short *)((int)&this->tax_rate_sel + 2) - this->dialog_h;
  wrapped = map_wrap_x((int)(short)this->tax_rate_sel - this->dialog_w);
  this->sci_rate_sel = wrapped;
  if (((game.rules & 0x8000) != 0) && (map.width + 1 < (int)(this->dialog_w * 2 + this->sci_rate_sel))
     ) {
    this->sci_rate_sel = map.width + 1 + this->dialog_w * -2;
  }
  if (map.height + 1 < (int)(this->dialog_h * 2 + this->init_tax_rate)) {
    this->init_tax_rate = map.height + 1 + this->dialog_h * -2;
  }
  clamped = this->sci_rate_sel;
  if (0x7fffffff < clamped) {
    clamped = 0xffffffff;
  }
  this->sci_rate_sel = clamped;
  clamped = this->init_tax_rate;
  if (0x7fffffff < clamped) {
    clamped = 0xffffffff;
  }
  this->init_tax_rate = clamped;
  if ((this->sci_rate_sel & 1) != 0) {
    this->sci_rate_sel--;
  }
  if ((this->init_tax_rate & 1) != 0) {
    this->sci_rate_sel++;
  }
  wrapped = map_wrap_x(this->label_x_value * 2 - 2 + this->sci_rate_sel);
  this->init_lux_rate = wrapped;
  this->init_sci_rate = this->header_y_value * 2 - 2 + this->init_tax_rate;
  if ((int)(short)this->lux_rate_sel != this->no_thanks_button_value) {
    surface_create((DibSurface *)&this->counter_button_value,this->total_tax,this->total_science);
    surface_create((DibSurface *)&this->right_agreed_button,this->total_tax,this->total_science);
    this->no_thanks_button_value = (int)(short)this->lux_rate_sel;
    mapview_apply_zoom(this);
    sprite_draw
              ((Sprite *)&tile_pick_mask_sprite,(iptr)pick_mask_rect,(iptr)&this->counter_button_value,0,0);
    sprite_draw
              ((Sprite *)&tile_direction_mask_sprite,(iptr)dir_mask_rect,(iptr)&this->right_agreed_button,0,0);
    gfx_reset_zoom_scale();
  }
  font_size = (int)(this->total_science * 3) / 5;
  if (this->rates_clamped != font_size) {
    font_set((GameFont *)&this->sci_label_y,0,font_size);
    this->rates_clamped = font_size;
  }
  font_size = (int)(this->total_science + ((int)this->total_science >> 0x1f & 3U)) >> 2;
  if (this->mode2_button_value != font_size) {
    font_set((GameFont *)&this->conceal_button_value,1,font_size);
    this->mode2_button_value = font_size;
  }
  return;
}

/* 0047a540 auto */
i32 __thiscall
mapview_screen_to_tile
          (MapViewHitView *this,iptr out_x,iptr out_y,i32 mouse_x,i32 mouse_y)

{
  short px;
  short py;
  i32 result;
  iptr pixel;
  iptr quadrant;
  iptr tile_x;
  short tile_y;
  
  px = (short)mouse_x - (short)this->client_x;
  py = (short)mouse_y - (short)this->client_y;
  if ((px < 0) || (py < 0)) {
    result = 1;
  }
  else if (((int)px < (int)this->view_width) && ((int)py < (int)this->view_height)) {
    px -= (short)this->scroll_px_x;
    py -= (short)this->scroll_px_y;
    tile_x = ((int)px / (int)this->tile_width) * 2 + this->origin_tile_x + 1;
    tile_y = (short)((int)py / (int)this->tile_height) * 2 + (short)this->origin_tile_y + 1;
    pixel = surface_get_pixel
                      ((DibSurface *)(((MapViewHitViewExt *)this)->view_surface),
                       (int)(short)((int)px % (int)this->tile_width),
                       (int)(short)((int)py % (int)this->tile_height));
    quadrant = pixel - 10 >> 4;
    if (quadrant != 0) {
      tile_x += (char)(&pick_quadrant_dx_table)[quadrant];
      tile_y += (char)(&pick_quadrant_dy_table)[quadrant];
    }
    result = map_wrap_x(tile_x);
    *(int *)out_x = (int)(short)result;
    *(int *)out_y = (int)tile_y;
    result = 0;
  }
  else {
    result = 1;
  }
  return result;
}

/* 0047a6b0 auto */
void __thiscall
mapview_tile_to_screen(ViewWindow *this,iptr out_x,iptr out_y,int x,int y)

{
  uptr top;
  int dx;
  
  dx = map_wrap_x(x - this->sci_rate_sel);
  top = this->init_tax_rate;
  *(u32 *)out_x = this->total_upkeep_value * (dx - 1) + this->tax_label_y;
  *(u32 *)out_y = this->margin_value * ((y - top) - 1) + this->lux_label_y;
  *(u32 *)out_x = *(int *)out_x + this->client_x;
  *(u32 *)out_y = *(int *)out_y + this->client_y;
  return;
}

/* 0047a8c9 auto */
#define map_show_hidden_terrain (*(int *)((u8 *)&g.d_0062bcd8))
void __thiscall
mapview_draw_tile_terrain
          (ViewWindow *this,iptr surface,int screen_x,int screen_y,iptr x,int y,
          int viewer_civ,int zoom,iptr city_tile_idx)

{
  byte nbr_raw;
  uint new_flags;
  int check;
  byte *known;
  iptr civ;
  i32 color;
  u32 unexp_dy;
  u32 unexp_dx;
  u32 dither_dy;
  u32 dither_dx;
  i8 unexp_rect[16];
  i8 airbase_rect[16];
  i8 fortress_rect[16];
  i8 hut_rect[16];
  i8 pollution_rect[16];
  i8 mine_rect[16];
  i8 road_dot_rect[16];
  i8 rail_dot_rect[16];
  i8 rail_rect[16];
  i8 road_rect[16];
  i8 resource_rect[16];
  i8 shield_rect[16];
  i8 farm_rect[16];
  i8 irrig_rect[16];
  i8 river_rect[16];
  i8 farmland_rect[16];
  i8 hill_rect[16];
  i8 mountain_rect[16];
  i8 forest_rect[16];
  i8 dither_rect[16];
  i8 base_rect[16];
  i8 mouth_rect[16];
  i8 coast_rect[16];
  i8 ocean_rect[16];
  i8 hidden_rect[16];
  iptr x2;
  int abs_dy;
  uint terrain_byte;
  uint nbr_terrain;
  uint hidden;
  iptr unit;
  int rail_count;
  int road_count;
  int variant;
  uint improvements2;
  iptr quad;
  byte *tile;
  int abs_dx;
  int river_mask;
  byte *nbr_tile;
  u32 half_w;
  uint terrain2;
  uint nbr_improvements;
  int nbr_hidden;
  iptr y2;
  u32 half_h;
  int draw_y;
  iptr dir;
  u32 tile_w;
  int draw_x;
  uint nbr_byte;
  int quarter_y;
  int has_rail;
  uint irrig_flags;
  int resource;
  i8 airbase_area[16];
  int quarter_x;
  uint has_river;
  iptr quarter;
  u32 tile_h;
  uint dither_terrain[4];
  
  if ((short)this->lux_rate_sel == zoom) {
    tile_w = this->total_tax;
    tile_h = this->total_science;
    half_w = this->total_upkeep_value;
    half_h = this->margin_value;
  }
  else {
    tile_w = gfx_zoom_scale(0x40,zoom);
    tile_h = gfx_zoom_scale(0x20,zoom);
    half_w = (int)tile_w >> 1;
    half_h = (int)tile_h >> 1;
  }
  if (city_tile_idx < 0) {
    check = map_in_bounds(x,y);
    hidden = (uint)(check == 0);
  }
  else {
    hidden = (uint)(0x14 < city_tile_idx);
    if (hidden == 0) {
      check = map_in_bounds(x,y);
      if (check == 0) {
        hidden = 1;
      }
      else {
        hidden = 0;
      }
    }
  }
  gfx_set_zoom_scale(zoom);
  if ((-1 < viewer_civ) || (hidden != 0)) {
    if (hidden == 0) {
      check = tile_visible_to(x,y,viewer_civ);
      if (check == 0) {
        hidden = 1;
      }
      else {
        hidden = 0;
      }
    }
    if (hidden != 0) {
      sprite_draw
                ((Sprite *)&unexplored_tile_sprite,(iptr)hidden_rect,surface,screen_x,screen_y);
      goto LAB_0047ba07;
    }
  }
  check = map_in_bounds(x,y);
  if (check == 0) {
    hidden = 1;
    terrain_byte = 7;
    terrain2 = 7;
    improvements2 = 0;
    has_river = 0;
    tile = (byte *)0x0;
  }
  else {
    hidden = 0;
    tile = (byte *)tile_at(x,y);
    terrain_byte = (uint)*tile;
    terrain2 = terrain_byte & 0xf;
    has_river = terrain_byte & 0x80;
    if (viewer_civ < 1) {
      improvements2 = (uint)tile[1];
    }
    else {
      known = (byte *)known_at(x,y,viewer_civ);
      improvements2 = (uint)*known;
    }
  }
  for (dir = 0; dir < 4; dir++) {
    dither_terrain[dir] = 0xffffffff;
  }
  if (terrain2 == 10) {
    if (zoom < -3) {
      sprite_draw
                ((Sprite *)&terrain_ocean_sprite,(iptr)ocean_rect,surface,screen_x,screen_y);
    }
    else {
      variant = tile_calc_coast_masks(x,y);
      for (quarter = 0; quarter < 4; quarter++) {
        quarter_x = (*(int *)(&coast_quarter_dx_table + quarter * 4) + 1) * ((int)half_w >> 1) + screen_x;
        quarter_y = *(int *)(&coast_quarter_dy_table + quarter * 4) * ((int)half_h >> 1) + screen_y;
        sprite_draw
                  ((Sprite *)
                   (&coast_quarter_sprites + quarter * 0x3c + (uint)(byte)(&coast_quarter_land_masks)[quarter] * 0xf0),
                   (iptr)coast_rect,surface,quarter_x,quarter_y);
      }
      for (dir = 0; dir < 4; dir++) {
        x2 = map_wrap_x((char)(&diag_dx_table)[dir] + x);
        y2 = (char)(&diag_dy_table)[dir] + y;
        check = map_in_bounds(x2,y2);
        if ((check != 0) && (known = (byte *)tile_at(x2,y2), (*known & 0x80) != 0)) {
          sprite_draw
                    ((Sprite *)(&river_mouth_sprites + dir * 0x3c),(iptr)mouth_rect,surface,
                     screen_x,screen_y);
        }
      }
    }
  }
  else {
    variant = 0;
    river_mask = 0;
    if (zoom < -4) {
      river_mask = 0xf;
    }
    else {
      for (dir = 0; dir < 4; dir++) {
        x2 = map_wrap_x((char)(&diag_dx_table)[dir] + x);
        y2 = (char)(&diag_dy_table)[dir] + y;
        check = map_in_bounds(x2,y2);
        if (check != 0) {
          nbr_tile = (byte *)tile_at(x2,y2);
          nbr_raw = *nbr_tile;
          nbr_byte = (uint)nbr_raw;
          nbr_terrain = nbr_byte & 0xf;
          if (nbr_terrain == terrain2) {
            variant += (char)(&diag_neighbor_bits)[dir];
          }
          else if (nbr_terrain == 10) {
            dither_terrain[dir] = 0xc;
          }
          else {
            dither_terrain[dir] = nbr_terrain;
          }
          if (((nbr_raw & 0x80) != 0) || (nbr_terrain == 10)) {
            river_mask += (char)(&diag_neighbor_bits)[dir];
          }
        }
      }
    }
    sprite_draw
              ((Sprite *)(&terrain_base_sprites + terrain2 * 0x3c),(iptr)base_rect,surface,screen_x,
               screen_y);
    if (-5 < zoom) {
      for (quad = 0; quad < 4; quad++) {
        if (-1 < (int)dither_terrain[quad]) {
          if (quad < 2) {
            dither_dx = half_w;
          }
          else {
            dither_dx = 0;
          }
          draw_x = dither_dx + screen_x;
          if (((char)quad + 1U & 3) < 2) {
            dither_dy = 0;
          }
          else {
            dither_dy = half_h;
          }
          draw_y = dither_dy + screen_y;
          sprite_draw
                    ((Sprite *)
                     (&terrain_dither_sprites + quad * 0x3c + dither_terrain[quad] * 0xf0),(iptr)dither_rect
                     ,surface,draw_x,draw_y);
        }
      }
    }
    if (terrain2 == 3) {
      sprite_draw
                ((Sprite *)(&forest_sprites + variant * 0x3c),(iptr)forest_rect,surface,screen_x,
                 screen_y);
    }
    else if (terrain2 == 5) {
      sprite_draw
                ((Sprite *)(&mountain_sprites + variant * 0x3c),(iptr)mountain_rect,surface,screen_x,
                 screen_y);
    }
    else if (terrain2 == 4) {
      sprite_draw
                ((Sprite *)(&hill_sprites + variant * 0x3c),(iptr)hill_rect,surface,screen_x,
                 screen_y);
    }
    if (((-4 < zoom) && (map_show_hidden_terrain == 0)) && (((byte)improvements2 & 0xc) == 0xc)) {
      sprite_draw
                ((Sprite *)&farmland_sprite,(iptr)farmland_rect,surface,screen_x,screen_y);
    }
    if (((-7 < zoom) && (has_river != 0)) && (map_show_hidden_terrain == 0)) {
      sprite_draw
                ((Sprite *)(&river_sprites + river_mask * 0x3c),(iptr)river_rect,surface,screen_x,
                 screen_y);
    }
    if (-4 < zoom) {
      irrig_flags = 0;
      if (((byte)improvements2 & 0x42) == 2) {
        for (dir = 2; dir < 5; dir += 2) {
          x2 = map_wrap_x((char)(&dir_dx_table)[dir] + x);
          y2 = (char)(&dir_dy_table)[dir] + y;
          check = map_in_bounds(x2,y2);
          new_flags = irrig_flags;
          if (((check != 0) &&
              (nbr_improvements = tile_improvements(x2,y2), new_flags = irrig_flags,
              (nbr_improvements & 4) != 0)) && (new_flags = irrig_flags | 1, (nbr_improvements & 8) != 0)) {
            new_flags = irrig_flags | 3;
          }
          irrig_flags = new_flags;
        }
      }
      if (map_show_hidden_terrain == 0) {
        if ((((byte)improvements2 & 0xc) == 4) || (irrig_flags == 1)) {
          sprite_draw
                    ((Sprite *)&land_improvement_sprites,(iptr)irrig_rect,surface,screen_x,screen_y);
        }
        else if ((irrig_flags & 2) != 0) {
          sprite_draw
                    ((Sprite *)&farmland_sprite,(iptr)farm_rect,surface,screen_x,screen_y);
        }
      }
    }
    if (((-4 < zoom) && (terrain2 == 2)) &&
       (check = tile_grassland_has_shield(x,y), check != 0)) {
      sprite_draw
                ((Sprite *)&grassland_shield_sprite,(iptr)shield_rect,surface,screen_x,screen_y);
    }
  }
  if (((-4 < zoom) && (hidden == 0)) &&
     (resource = tile_resource(x,y), resource != 0)) {
    sprite_draw
              ((Sprite *)(&terrain_resource_sprites + terrain2 * 0x78 + (resource * 4 - 4) * 0xf),
               (iptr)resource_rect,surface,screen_x,screen_y);
  }
  if (((-4 < zoom) && (map_show_hidden_terrain == 0)) &&
     (((improvements2 & 0x10) != 0 || (check = tile_city_owner(x,y), -1 < check)))) {
    road_count = 0;
    rail_count = 0;
    if (((improvements2 & 0x20) == 0) && (check = tile_city_owner(x,y), check < 0)) {
      has_rail = 0;
    }
    else {
      has_rail = 1;
    }
    for (dir = 0; dir < 8; dir++) {
      x2 = map_wrap_x((char)(&dir_dx_table)[dir] + x);
      y2 = (char)(&dir_dy_table)[dir] + y;
      check = map_in_bounds(x2,y2);
      if (check != 0) {
        if (viewer_civ < 1) {
          nbr_improvements = tile_improvements(x2,y2);
        }
        else {
          known = (byte *)known_at(x2,y2,viewer_civ);
          nbr_improvements = (uint)*known;
        }
        if (((nbr_improvements & 0x12) != 0) &&
           ((road_count = road_count + 1, has_rail == 0 || ((nbr_improvements & 0x22) == 0)))) {
          sprite_draw
                    ((Sprite *)(&road_sprites + (dir * 4 + 4) * 0xf),(iptr)road_rect,
                     surface,screen_x,screen_y);
        }
      }
    }
    if (has_rail != 0) {
      for (dir = 0; dir < 8; dir++) {
        x2 = map_wrap_x((char)(&dir_dx_table)[dir] + x);
        y2 = (char)(&dir_dy_table)[dir] + y;
        check = map_in_bounds(x2,y2);
        if (check != 0) {
          if (viewer_civ < 1) {
            nbr_improvements = tile_improvements(x2,y2);
          }
          else {
            known = (byte *)known_at(x2,y2,viewer_civ);
            nbr_improvements = (uint)*known;
          }
          if ((nbr_improvements & 0x22) != 0) {
            rail_count++;
            sprite_draw
                      ((Sprite *)(&railroad_sprites + (dir * 4 + 4) * 0xf),(iptr)rail_rect,
                       surface,screen_x,screen_y);
          }
        }
      }
    }
    check = tile_city_owner(x,y);
    if (check < 0) {
      if (has_rail == 0) {
        if (road_count == 0) {
          sprite_draw
                    ((Sprite *)&road_sprites,(iptr)road_dot_rect,surface,screen_x,screen_y);
        }
      }
      else if (rail_count == 0) {
        sprite_draw
                  ((Sprite *)&railroad_sprites,(iptr)rail_dot_rect,surface,screen_x,screen_y);
      }
    }
  }
  if (((-4 < zoom) && (map_show_hidden_terrain == 0)) && (((byte)improvements2 & 0xc) == 8)) {
    sprite_draw
              ((Sprite *)&mine_sprite,(iptr)mine_rect,surface,screen_x,screen_y);
  }
  if ((-5 < zoom) && (hidden == 0)) {
    if ((improvements2 & 0x80) != 0) {
      sprite_draw
                ((Sprite *)&pollution_sprite,(iptr)pollution_rect,surface,screen_x,screen_y);
    }
    check = tile_has_hut(x,y);
    if ((check != 0) && (map_show_hidden_terrain == 0)) {
      sprite_draw
                ((Sprite *)&hut_sprite,(iptr)hut_rect,surface,screen_x,screen_y);
    }
    if ((((byte)improvements2 & 0x42) == 0x40) && (map_show_hidden_terrain == 0)) {
      sprite_draw
                ((Sprite *)&fortress_sprite,(iptr)fortress_rect,surface,screen_x,screen_y - half_h);
    }
    if ((((byte)improvements2 & 0x42) == 0x42) && (map_show_hidden_terrain == 0)) {
      variant = 0;
      for (unit = tile_first_unit(x,y); -1 < unit;
          unit = unit_next_in_stack(unit)) {
        if (unit_types[units[unit].type].domain == 1) {
          variant = 1;
          break;
        }
      }
      sprite_draw
                ((Sprite *)(&airbase_sprites + variant * 0x3c),(iptr)airbase_rect,surface,screen_x,
                 screen_y - half_h);
      rect_set_xywh((iptr)airbase_area,screen_x,screen_y - half_h,tile_w,half_h + tile_h);
      civ = tile_owner(x,y);
      color = civ_color_primary(civ);
      surface_replace_color((DibSurface *)surface,(iptr)airbase_area,0x106,color);
    }
  }
  if ((-4 < zoom) && (-1 < viewer_civ)) {
    for (dir = 0; dir < 4; dir++) {
      x2 = map_wrap_x((char)(&diag_dx_table)[dir] + x);
      y2 = (char)(&diag_dy_table)[dir] + y;
      nbr_hidden = 0;
      if (city_tile_idx < 0) {
        check = map_in_bounds(x2,y2);
        if (check != 0) goto LAB_0047b934;
      }
      else {
        if (city_tile_idx < 0x15) {
          check = map_in_bounds(x2,y2);
          if (check == 0) {
            nbr_hidden = 1;
          }
          if ((int)(char)(&diag_dx_table)[dir] + (int)(char)(&city_tile_dx_table)[city_tile_idx] < 1) {
            abs_dx = ~((int)(char)(&diag_dx_table)[dir] + (int)(char)(&city_tile_dx_table)[city_tile_idx])
                       + 1;
          }
          else {
            abs_dx = (int)(char)(&diag_dx_table)[dir] + (int)(char)(&city_tile_dx_table)[city_tile_idx];
          }
          if ((int)(char)(&diag_dy_table)[dir] + (int)(char)(&city_tile_dy_table)[city_tile_idx] < 1) {
            abs_dy = ~((int)(char)(&diag_dy_table)[dir] + (int)(char)(&city_tile_dy_table)[city_tile_idx])
                       + 1;
          }
          else {
            abs_dy = (int)(char)(&diag_dy_table)[dir] + (int)(char)(&city_tile_dy_table)[city_tile_idx];
          }
          check = dist_from_deltas(abs_dx,abs_dy);
          if (2 < check) {
            nbr_hidden = 1;
          }
        }
        else {
          nbr_hidden = 1;
        }
LAB_0047b934:
        if (nbr_hidden == 0) {
          check = tile_visible_to(x2,y2,viewer_civ);
          if (check == 0) {
            nbr_hidden = 1;
          }
          else {
            nbr_hidden = 0;
          }
        }
        if (nbr_hidden != 0) {
          if (dir < 2) {
            unexp_dx = half_w;
          }
          else {
            unexp_dx = 0;
          }
          draw_x = unexp_dx + screen_x;
          if (((char)dir + 1U & 3) < 2) {
            unexp_dy = 0;
          }
          else {
            unexp_dy = half_h;
          }
          draw_y = unexp_dy + screen_y;
          sprite_draw
                    ((Sprite *)(&unexplored_dither_sprites + dir * 0x3c),(iptr)unexp_rect,surface,
                     draw_x,draw_y);
        }
      }
    }
  }
LAB_0047ba07:
  gfx_reset_zoom_scale();
  return;
}
#undef map_show_hidden_terrain

/* 0047ba1d auto */
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
void __thiscall
mapview_draw_tile_city
          (ViewWindow *this,i32 screen_x,int screen_y,iptr x,iptr y)

{
  iptr city;
  int in_bounds;
  int visible2;
  
  city = city_at(x,y);
  if ((-1 < city) && (in_bounds = map_in_bounds(x,y), in_bounds != 0)) {
    visible2 = tile_visible_to(x,y,human_civ);
    if ((int)cities[city].owner != (human_civ & 0xffU)) {
      if ((visible2 == 0) ||
         ((((1 << ((byte)human_civ & 0x1f) & (int)(char)cities[city].known_to) == 0 &&
           ((int)cities[city].owner != (human_civ & 0xffU))) ||
          (*(char *)&cities[city].revealed_size[human_civ] == '\0')))) {
        visible2 = 0;
      }
      else {
        visible2 = 1;
      }
    }
    if (((visible2 != 0) || (game.reveal_map != '\0')) ||
       (((game.game_flags & 0x80) != 0 && ((scenario_flags & 8) != 0)))) {
      gfx_draw_city((iptr)this,city,0,screen_x,screen_y - this->margin_value,
                         (int)(short)this->lux_rate_sel);
    }
  }
  return;
}
#undef human_civ
#undef scenario_flags

/* 0047bba5 auto */
void __thiscall
mapview_draw_unit_stacked
          (ViewWindow *this,iptr unit,uint draw_flags,i32 screen_x,i32 screen_y)

{
  gfx_draw_unit((iptr)this,unit,draw_flags | 3,screen_x,screen_y,(int)(short)this->lux_rate_sel,0);
  return;
}

/* 0047bbea auto */
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
#define unit_blink_active (*(char *)((u8 *)&g.d_0062804c))
#define unit_blink_phase (*(char *)((u8 *)&g.d_00628054))
void __thiscall
mapview_draw_unit_blinking
          (ViewWindow *this,iptr unit,i32 screen_x,i32 screen_y)

{
  if (((unit_blink_active == '\0') || (unit_blink_phase == '\0')) || (moving_units_mode != 1)) {
    gfx_draw_unit((iptr)this,unit,5,screen_x,screen_y,(int)(short)this->lux_rate_sel,0);
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
void __thiscall mapview_draw_unit_at(ViewWindow *this,iptr unit)

{
  int screen_y;
  i32 screen_x;
  
  if (((unit_blink_active == '\0') || (unit_blink_phase == '\0')) || (moving_units_mode != 1)) {
    mapview_tile_to_screen(this,(iptr)&screen_x,(iptr)&screen_y,(int)units[unit].x,
                       (int)units[unit].y);
    screen_y -= this->margin_value;
    gfx_draw_unit((iptr)this,unit,5,screen_x,screen_y,(int)(short)this->lux_rate_sel,0);
  }
  return;
}
#undef moving_units_mode
#undef unit_blink_active
#undef unit_blink_phase

/* 0047bd04 auto */
#define anim_combat_defender (*(int *)((u8 *)&g.d_00633e48))
void __thiscall
mapview_draw_stack_unit
          (ViewWindow *this,iptr unit,i32 screen_x,i32 screen_y)

{
  int selectable;
  
  if ((anim_combat_defender < 0) || (anim_combat_defender != unit)) {
    if ((anim_origin_stack_unit < 0) || (unit != anim_origin_stack_unit)) {
      if ((((units[game.active_unit].x == units[unit].x) &&
           (units[game.active_unit].y == units[unit].y)) &&
          (((uint)game.human_players & 1 << (units[game.active_unit].owner & 0x1fU)) != 0)) &&
         (selectable = unit_is_selectable((int)game.active_unit), selectable != 0)) {
        mapview_draw_unit_blinking(this,(int)game.active_unit,screen_x,screen_y);
        return;
      }
      mapview_draw_unit_stacked(this,unit,4,screen_x,screen_y);
    }
    else {
      gfx_draw_unit((iptr)this,unit,5,screen_x,screen_y,(int)(short)this->lux_rate_sel,0);
    }
  }
  else {
    mapview_draw_unit_blinking(this,unit,screen_x,screen_y);
  }
  return;
}
#undef anim_combat_defender

/* 0047be63 auto */
#define anim_combat_defender (*(int *)((u8 *)&g.d_00633e48))
#define anim_combat_defender_x (*(int *)((u8 *)&g.d_00633e40))
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
#define unit_blink_active (*(char *)((u8 *)&g.d_0062804c))
void __thiscall
mapview_draw_tile_units
          (ViewWindow *this,i32 screen_x,int screen_y,int x,int y)

{
  int draw_y;
  int result;
  iptr unit;
  int visible2;
  
  draw_y = screen_y - this->margin_value;
  result = map_in_bounds(x,y);
  if (result != 0) {
    unit = tile_first_unit(x,y);
    if (((anim_combat_defender < 0) || (anim_combat_defender_x != x)) || (anim_combat_defender_y != y)) {
      if (((anim_origin_stack_unit < 0) || (x != anim_origin_x)) || (y != anim_origin_y)) {
        result = tile_city_owner(x,y);
        if (-1 < result) {
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
          result = unit_is_selectable(unit);
          if (result == 0) {
            return;
          }
          if (units[unit].orders == 1) {
            return;
          }
          if (units[unit].orders == 2) {
            return;
          }
        }
        visible2 = tile_visible_to(x,y,human_civ);
        if ((int)units[unit].owner != (human_civ & 0xffU)) {
          if ((visible2 == 0) ||
             (((1 << ((byte)human_civ & 0x1f) & (uint)units[unit].visibility) == 0 &&
              ((int)units[unit].owner != (human_civ & 0xffU))))) {
            visible2 = 0;
          }
          else {
            visible2 = 1;
          }
        }
        if ((visible2 != 0) || (game.reveal_map != '\0')) {
          mapview_draw_stack_unit(this,unit,screen_x,draw_y);
        }
      }
      else {
        mapview_draw_stack_unit(this,anim_origin_stack_unit,screen_x,draw_y);
      }
    }
    else {
      for (; (unit != anim_combat_defender && (-1 < unit)); unit = unit_next_in_stack(unit)) {
      }
      mapview_draw_stack_unit(this,unit,screen_x,draw_y);
    }
  }
  return;
}
#undef anim_combat_defender
#undef anim_combat_defender_x
#undef human_civ
#undef moving_units_mode
#undef unit_blink_active

/* 0047c103 auto */
#define map_show_hidden_terrain (*(int *)((u8 *)&g.d_0062bcd8))
void __thiscall
mapview_draw_tile(ViewWindow *this,iptr x,iptr y,int civ)

{
  int result;
  i8 grid_rect[16];
  i8 radius_rect[16];
  iptr city;
  i32 screen_y;
  i32 screen_x;
  int near_city;
  
  mapview_tile_to_screen(this,(iptr)&screen_x,(iptr)&screen_y,x,y);
  mapview_draw_tile_terrain(this,(iptr)this,screen_x,screen_y,x,y,civ,
                     (int)(short)this->lux_rate_sel,-1);
  win_flush_pending_msgs();
  if (2 < game.multiplayer) {
    net_process_messages((NetSession *)&net_session,1,0);
  }
  result = map_in_bounds(x,y);
  if (result != 0) {
    if (map_show_hidden_terrain == 0) {
      mapview_draw_tile_city(this,screen_x,screen_y,x,y);
      mapview_draw_tile_units(this,screen_x,screen_y,x,y);
    }
    if (((byte)game.game_options & 0x20) != 0) {
      near_city = 0;
      mapview_apply_zoom(this);
      for (city = 0; city < game.num_cities; city++) {
        if (((cities[city].id != 0) && (cities[city].owner == civ)) &&
           (result = map_distance_diag(x,y,(int)cities[city].x,
                                       (int)cities[city].y), result < 3)) {
          near_city = 1;
          break;
        }
      }
      if (near_city == 0) {
        sprite_draw
                  ((Sprite *)&map_grid_sprite,(iptr)grid_rect,(iptr)this,screen_x,screen_y);
      }
      else {
        sprite_draw
                  ((Sprite *)&city_radius_grid_sprite,(iptr)radius_rect,(iptr)this,screen_x,screen_y);
      }
      gfx_reset_zoom_scale();
    }
  }
  return;
}
#undef map_show_hidden_terrain

/* 0047c3e0 auto */
i32 __thiscall
mapview_tile_in_view(ViewWindow *this,i32 tile_x,i32 tile_y)

{
  i32 in_view;
  
  in_view = map_tile_in_box(tile_x,tile_y,this->sci_rate_sel,this->init_tax_rate,
                             this->dialog_w + this->label_x_value,this->dialog_h + this->header_y_value + 1
                            );
  return in_view;
}

/* 0047c443 auto */
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define map_show_hidden_terrain (*(int *)((u8 *)&g.d_0062bcd8))
void __thiscall
mapview_draw_city_names(ViewWindow *this,i32 center_x,i32 center_y,int radius)

{
  int label_x;
  int text_width;
  i32 shadow_color;
  int name_width;
  i32 text_color;
  i32 shadow_depth;
  i32 shadow_offset;
  int shadow_y;
  int screen_y;
  iptr city;
  int screen_x;
  int y2;
  int x2;
  int visible2;
  int label_y;
  
  if (map_show_hidden_terrain == 0) {
    if (-1 < radius) {
      radius += 3;
    }
    text_set_font((iptr)&this->sci_label_y);
    for (city = 0; city < game.num_cities; city++) {
      if (cities[city].id != 0) {
        x2 = (int)cities[city].x;
        y2 = (int)cities[city].y;
        if (((radius < 0) ||
            (label_x = map_distance(x2,y2,center_x,center_y), label_x <= radius)) &&
           (label_x = mapview_tile_in_view(this,x2,y2), label_x != 0)) {
          visible2 = tile_visible_to(x2,y2,human_civ);
          if ((int)cities[city].owner != (human_civ & 0xffU)) {
            if (((visible2 == 0) ||
                (((1 << ((byte)human_civ & 0x1f) & (int)(char)cities[city].known_to) == 0 &&
                 ((int)cities[city].owner != (human_civ & 0xffU))))) ||
               (*(char *)&cities[city].revealed_size[human_civ] == '\0')) {
              visible2 = 0;
            }
            else {
              visible2 = 1;
            }
          }
          if (game.reveal_map != '\0') {
            visible2 = 1;
          }
          if (visible2 != 0) {
            mapview_tile_to_screen(this,(iptr)&screen_x,(iptr)&screen_y,x2,y2);
            label_x = this->total_upkeep_value + screen_x;
            label_y = ((int)(this->total_science * 3) >> 2) + screen_y;
            text_set_colors(10,0xffffffff,0xffffffff,0xffffffff);
            text_width = mapview_zoom_scale(this,2);
            if (text_width < 3) {
              shadow_y = mapview_zoom_scale(this,2);
            }
            else {
              shadow_y = 2;
            }
            shadow_y = label_y + shadow_y;
            text_width = font_text_width
                              ((GameFont *)&this->sci_label_y,(iptr)&cities[city].name);
            text_draw_shadowed((iptr)this,(iptr)&cities[city].name,label_x - (text_width >> 1),shadow_y);
            text_width = mapview_zoom_scale(this,2);
            if (text_width < 3) {
              shadow_offset = mapview_zoom_scale(this,2);
            }
            else {
              shadow_offset = 2;
            }
            shadow_depth = 0;
            text_color = 10;
            shadow_color = civ_color_secondary((int)cities[city].owner);
            text_set_colors(shadow_color,text_color,shadow_offset,shadow_depth);
            text_width = label_y;
            name_width = font_text_width
                              ((GameFont *)&this->sci_label_y,(iptr)&cities[city].name);
            text_draw_shadowed((iptr)this,(iptr)&cities[city].name,label_x - (name_width >> 1),text_width);
          }
        }
      }
    }
  }
  return;
}
#undef human_civ
#undef map_show_hidden_terrain

/* 0047c7aa auto */
void __thiscall
mapview_tile_radius_rect
          (ViewWindow *this,i32 tile_x,i32 tile_y,int radius,iptr out_rect)

{
  i8 rect[16];
  int width2;
  int top;
  int left;
  
  mapview_tile_to_screen(this,(iptr)&left,(iptr)&top,tile_x,tile_y);
  top -= (radius * 2 + 1) * this->margin_value;
  left += this->total_upkeep_value * radius * -2;
  width2 = (radius * 2 + 1) * this->total_tax;
  rect_set_xywh((iptr)rect,left,top,width2,(radius * 4 + 3) * this->margin_value);
  rect_intersect_into(out_rect,(iptr)rect,(iptr)&this->client_rect);
  return;
}

/* 0047c869 auto */
void __thiscall
mapview_draw_tile_radius
          (ViewWindow *this,int center_x,int center_y,int radius,i32 civ)

{
  uint extent;
  uint row_abs;
  i32 x;
  int in_view;
  uint dx_abs;
  uint dy;
  uint dx;
  int row_extent;
  i8 clip_rect[16];
  
  mapview_tile_radius_rect(this,center_x,center_y,radius,(iptr)clip_rect);
  surface_set_clip((DibSurface *)this,(iptr)clip_rect);
  extent = radius * 2 + 2;
  for (dy = -extent; (int)dy <= (int)extent; dy++) {
    if ((int)dy < 1) {
      row_abs = ~dy + 1;
    }
    else {
      row_abs = dy & 1;
    }
    row_extent = extent - row_abs;
    for (dx = -row_extent; (int)dx <= row_extent; dx += 2) {
      if ((int)dx < 1) {
        dx_abs = ~dx + 1;
      }
      else {
        dx_abs = dx;
      }
      if (dx_abs != extent) {
        x = map_wrap_x(dx + center_x);
        in_view = mapview_tile_in_view(this,x,center_y + dy);
        if (in_view != 0) {
          mapview_draw_tile(this,x,center_y + dy,civ);
        }
      }
    }
  }
  mapview_draw_city_names(this,center_x,center_y,radius);
  surface_set_clip((DibSurface *)this,(iptr)&this->client_rect);
  return;
}

/* 0047c9d4 auto */
void __thiscall mapview_draw_all_tiles(ViewWindow *this,i32 civ)

{
  uptr origin_y;
  uptr origin_x;
  i32 x;
  uint row;
  int col;
  int row_width;
  
  if ((this->tax_label_y != 0) || (this->lux_label_y != 0)) {
    gfx_fill_surface((iptr)this,10);
  }
  for (row = 0; (int)row < (int)(this->dialog_h + this->header_y_value + 1);
      row = row + 1) {
    origin_y = this->init_tax_rate;
    origin_x = this->sci_rate_sel;
    if ((row & 1) == 0) {
      row_width = this->label_x_value;
    }
    else {
      row_width = this->dialog_w;
    }
    for (col = 0; col < row_width; col++) {
      x = map_wrap_x(col * 2 + origin_x + (row & 1));
      mapview_draw_tile(this,x,origin_y + row,civ);
    }
  }
  mapview_draw_city_names(this,0,0,0xffffffff);
  return;
}

/* 0047caea auto */
void __thiscall
mapview_blit_tile_radius
          (ViewWindow *this,i32 tile_x,i32 tile_y,i32 radius)

{
  i8 rect[16];
  
  mapview_tile_radius_rect(this,tile_x,tile_y,radius,(iptr)rect);
  wnd_blit_surface_rect((DibSurface *)this,(iptr)rect);
  return;
}

/* 0047cb26 auto */
void __thiscall
mapview_blit_tile(ViewWindow *this,i32 tile_x,i32 tile_y)

{
  mapview_blit_tile_radius(this,tile_x,tile_y,0);
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
#define map_redraw_busy (*(i32 *)((u8 *)&g.d_006ad908))
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
#define unit_blink_active (*(char *)((u8 *)&g.d_0062804c))
#define unit_blink_phase (*(char *)((u8 *)&g.d_00628054))
void __thiscall
mapview_redraw_area
          (ViewWindow *this,i32 tile_x,i32 tile_y,i32 radius,
          iptr viewer_civ,int do_blit)

{
  int in_view;
  iptr civ;
  i8 cursor_rect[16];
  i32 cursor_x;
  i32 cursor_y;
  
  if (game_loop_active != '\0') {
    map_redraw_busy = 1;
    if (game.reveal_map == '\0') {
      civ = viewer_civ;
    }
    else {
      civ = -1;
    }
    mapview_draw_tile_radius(this,tile_x,tile_y,radius,civ);
    if ((((moving_units_mode == 0) && (unit_blink_phase != '\0')) && (unit_blink_active != '\0')) &&
       ((this->rates_civ == 0 &&
        (in_view = mapview_tile_in_view(this,(int)map_cursor_x,(int)map_cursor_y), in_view != 0)))) {
      mapview_tile_to_screen(this,(iptr)&cursor_x,(iptr)&cursor_y,(int)map_cursor_x,(int)map_cursor_y);
      mapview_apply_zoom(this);
      sprite_draw
                ((Sprite *)&map_cursor_sprite,(iptr)cursor_rect,(iptr)this,cursor_x,cursor_y);
      gfx_reset_zoom_scale();
    }
    if (do_blit != 0) {
      mapview_blit_tile_radius(this,tile_x,tile_y,radius);
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

/* 0047cced auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
void __thiscall
mapview_redraw_tile(ViewWindow *this,i32 tile_x,i32 tile_y)

{
  mapview_redraw_area(this,tile_x,tile_y,0,human_civ,1);
  return;
}
#undef human_civ

/* 0047cd1f auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
void __thiscall
mapview_redraw_tile_neighbors(ViewWindow *this,i32 tile_x,i32 tile_y)

{
  mapview_redraw_area(this,tile_x,tile_y,1,human_civ,1);
  return;
}
#undef human_civ

/* 0047cd51 auto */
#define game_loop_active (*(char *)((u8 *)&g.d_00628044))
#define map_click_in_progress (*(int *)((u8 *)&g.d_0062bcb0))
#define map_redraw_busy (*(i32 *)((u8 *)&g.d_006ad908))
#define mp_simultaneous_moves (*(char *)((u8 *)&g.d_006ad684))
void __thiscall mapview_redraw(ViewWindow *this,iptr viewer_civ,int do_blit)

{
  iptr civ;
  
  if (game_loop_active != '\0') {
    map_redraw_busy = 1;
    frame_wnd_layout((FrameWindow *)this);
    mapview_update_layout(this);
    frame_wnd_draw_caption((FrameWindow *)this);
    if (game.reveal_map == '\0') {
      civ = viewer_civ;
    }
    else {
      civ = -1;
    }
    mapview_draw_all_tiles(this,civ);
    if ((do_blit != 0) &&
       (mapview_blit_with_net_pump((DibSurface *)this), this->rates_civ == 0)) {
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

/* 0047dce0 auto */
ViewWindow * __thiscall mapview_ctor(ViewWindow *this)

{
  i32 seh_prev;
  i8 *seh_handler;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  frame_wnd_ctor((SurfaceWindow *)this);
  eh_state = 0;
  font_init_empty((GameFont *)&this->sci_label_y);
  (*(i8 *)((char *)&eh_state + 0)) = 1;
  font_init_empty((GameFont *)&this->conceal_button_value);
  (*(i8 *)((char *)&eh_state + 0)) = 2;
  surface_ctor((DibSurface *)&this->counter_button_value);
  eh_state = (eh_state & 0xffffff00 | (byte)(3));
  surface_ctor((DibSurface *)&this->right_agreed_button);
  this->vtable = (u32)&PTR_FUN_0061d1e4;
  return this;
}

/* 0047de10 auto */
/* Library Function - Single Match
    public: virtual __thiscall CBitmapButton::~CBitmapButton(void)
   
   Library: Visual Studio 1998 Debug */

void __thiscall mapview_dtor(void *this)

{
  i32 seh_prev;
  i8 *seh_handler;
  int eh_state;
  
  eh_state = eh_state & 0xff;
  (*(i8 *)((char *)&eh_state + 0)) = 3;
  /* inlined unwind funclet 0047de82 */ { surface_dtor((DibSurface *)(*(int *)((iptr)&this) + 0x3a8)); }
  (*(i8 *)((char *)&eh_state + 0)) = 2;
  /* inlined unwind funclet 0047de91 */ { surface_dtor((DibSurface *)(*(int *)((iptr)&this) + 0x360)); }
  (*(i8 *)((char *)&eh_state + 0)) = 1;
  /* inlined unwind funclet 0047dea0 */ { font_destroy((GameFont *)(*(int *)((iptr)&this) + 0x340)); }
  eh_state = eh_state & 0xffffff00;
  /* inlined unwind funclet 0047deaf */ { font_destroy((GameFont *)(*(int *)((iptr)&this) + 0x338)); }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 0047debe */ { frame_wnd_dtor(*(DibSurface **)((iptr)&this)); }
  return;
}

/* 0047dfb0 auto */
i32 __thiscall mapview_zoom_scale(ViewWindow *this,i32 value)

{
  i32 scaled;
  
  scaled = gfx_zoom_scale(value,(int)(short)this->lux_rate_sel);
  return scaled;
}

/* 0047dff0 auto */
void __thiscall mapview_apply_zoom(ViewWindow *this)

{
  gfx_set_zoom_scale((int)(short)this->lux_rate_sel);
  return;
}

/* 0047e030 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
i32 __cdecl mapviews_tile_visible(iptr x,iptr y)

{
  int visible;
  int view_index;
  
  visible = tile_visible_to(x,y,human_civ);
  if (visible != 0) {
    for (view_index = 0; view_index < 8; view_index++) {
      if (((view_index == 0) || (*(short *)(&map_view_open_flags + view_index * 0x3f0) != 0)) &&
         (visible = mapview_tile_in_view
                            ((ViewWindow *)(&map_views + view_index * 0x3f0),x,y),
         visible != 0)) {
        return 1;
      }
    }
  }
  return 0;
}
#undef human_civ

/* 00489b9b auto */
#define map_view_center_x (*(short *)((u8 *)&g.d_0066ca88))
#define mapview_center_y (*(short *)((u8 *)&g.d_0066ca8a))
void __cdecl mapview_center_if_moved(int center_x,int center_y)

{
  if ((map_view_center_x != center_x) || (mapview_center_y != center_y)) {
    mapview_center_on((ViewWindow *)&map_views,center_x,center_y);
  }
  return;
}
#undef map_view_center_x
#undef mapview_center_y

/* 004d8b70 auto */
void __thiscall
clickmap_add_xywh
          (ClickMap *this,iptr id,i32 left,i32 top,i32 width,
          i32 height)

{
  clickmap_add(this,id,0,left,top,width,height);
  return;
}
