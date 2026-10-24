/* The game, windows, dialogs and menus: functions translated from the original
 * (tools/gen_c.py, now edited directly), in address order. */
#include "auto_common.h"

/* 00408010 auto */
void __thiscall wnd_set_cursor(WndBase *self,i32 cursor)

{
  wnd_obj_set_cursor(self->native_wnd,cursor);
  return;
}

/* 00408050 auto */
void __thiscall wnd_set_icon(WndBase *self,i32 icon)

{
  wnd_obj_set_icon(self->native_wnd,icon);
  return;
}

/* 00408090 auto */
void __thiscall wnd_minimize(WndBase *self)

{
  wnd_obj_minimize(self->native_wnd);
  return;
}

/* 004080c0 auto */
i32 __thiscall wnd_client_width(WndBase *self)

{
  i32 width;
  
  width = wnd_obj_client_width(self->native_wnd);
  return width;
}

/* 004080f0 auto */
void __thiscall wnd_get_rect_in_parent(WndBase *self,iptr rect)

{
  wnd_obj_get_rect_in_parent(self->native_wnd,(LPRECT)rect);
  return;
}

/* 00408130 auto */
u32 __thiscall wnd_set_lbuttonup_handler(WndEventHandlers *self,iptr handler)

{
  u32 old_handler;
  
  old_handler = self->on_lbuttonup;
  self->on_lbuttonup = handler;
  return old_handler;
}

/* 00408170 auto */
u32 __thiscall wnd_set_rbuttonup_handler(WndEventHandlers *self,iptr handler)

{
  u32 old_handler;
  
  old_handler = self->on_rbuttonup;
  self->on_rbuttonup = handler;
  return old_handler;
}

/* 004081b0 auto */
/* Library Function - Single Match
    public: virtual int __thiscall COleControlSite::SetDlgCtrlID(int)
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall wnd_set_keydown_handler(WndEventHandlers *self,iptr handler)

{
  u32 old_handler;
  
  old_handler = self->on_keydown;
  self->on_keydown = handler;
  return old_handler;
}

/* 004081f0 auto */
/* Library Function - Multiple Matches With Same Base Name
    public: class basic_ostream<char,struct char_traits<char> > * __thiscall basic_ios<char,struct
   char_traits<char> >::tie(class basic_ostream<char,struct char_traits<char> > *)
    public: class basic_ostream<unsigned short,struct char_traits<unsigned short> > * __thiscall
   basic_ios<unsigned short,struct char_traits<unsigned short> >::tie(class basic_ostream<unsigned
   short,struct char_traits<unsigned short> > *)
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall wnd_set_char_handler(WndEventHandlers *self,iptr handler)

{
  u32 old_handler;
  
  old_handler = self->on_char;
  self->on_char = handler;
  return old_handler;
}

/* 00408230 auto */
u32 __thiscall wnd_set_close_handler(WndEventHandlers *self,iptr handler)

{
  u32 old_handler;
  
  old_handler = self->on_close;
  self->on_close = handler;
  return old_handler;
}

/* 00408270 auto */
u32 __thiscall wnd_set_minimize_handler(WndEventHandlers *self,iptr handler)

{
  u32 old_handler;
  
  old_handler = self->on_minimize;
  self->on_minimize = handler;
  return old_handler;
}

/* 004082b0 auto */
u32 __thiscall wnd_set_restore_handler(WndEventHandlers *self,iptr handler)

{
  u32 old_handler;
  
  old_handler = self->on_restore;
  self->on_restore = handler;
  return old_handler;
}

/* 004082f0 auto */
u32 __thiscall wnd_set_size_handler(WndEventHandlers *self,iptr handler)

{
  u32 old_handler;
  
  old_handler = self->on_size;
  self->on_size = handler;
  return old_handler;
}

/* 00408330 auto */
u32 __thiscall wnd_set_move_handler(WndEventHandlers *self,iptr handler)

{
  u32 old_handler;
  
  old_handler = self->on_move;
  self->on_move = handler;
  return old_handler;
}

/* 00408370 auto */
void __thiscall wnd_set_min_size(ModalMenuWindow *self,u32 width,u32 height)

{
  self->min_width = width;
  self->min_height = height;
  return;
}

/* 004083b0 auto */
void __thiscall wnd_destroy_with_surface(DibSurface *self)

{
  wnd_destroy_native((WndBase *)(self + 1));
  surface_release(self);
  return;
}

/* 00408420 auto */
void __thiscall wnd_destroy_native(WndBase *self)

{
  NativeWindow *native;
  
  native = (NativeWindow *)wnd_obj_destroy(self->native_wnd);
  self->native_wnd = native;
  return;
}

/* 00408460 auto */
void __thiscall wnd_blit_surface(DibSurface *self)

{
  wnd_blit_surface_rect(self,0);
  return;
}

/* 00408490 auto */
void __thiscall wnd_blit_surface_rect(DibSurface *self,iptr rect)

{
  DibSurface *view;
  DibSurface *view2;
  
  if (rect == 0) {
    if (self == (DibSurface *)0x0) {
      view = (DibSurface *)0x0;
    }
    else {
      view = self + 1;
    }
    surface_blit_to_wnd(self,(iptr)view,(RECT *)&self->bounds_rect,(iptr)&self->bounds_rect);
    wnd_view_validate_rect((WndValidateRectView *)(self + 1),(iptr)&self->bounds_rect);
  }
  else {
    if (self == (DibSurface *)0x0) {
      view2 = (DibSurface *)0x0;
    }
    else {
      view2 = self + 1;
    }
    surface_blit_to_wnd(self,(iptr)view2,(RECT *)rect,rect);
    wnd_view_validate_rect((WndValidateRectView *)(self + 1),rect);
  }
  return;
}

/* 00408580 auto */
void __thiscall wnd_view_validate_rect(WndValidateRectView *self,iptr rect)

{
  wnd_obj_validate_rect(self->wnd_obj,(RECT *)rect);
  return;
}

/* 004085c0 auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall wnd_set_redraw_callback(SurfaceWindow *self,iptr callback)

{
  self->on_paint = callback;
  return;
}

/* 004085f0 auto */
void __thiscall window_show(WindowObjectView *self)

{
  window_show_focus_first((Wnd *)(self + 0x12));
  return;
}

/* 00408620 auto */
void __thiscall window_show_focus_first(Wnd *self)

{
  wnd_handle_show_raise((WndBase *)self);
  wnd_focus_first_control(self);
  return;
}

/* 00408650 auto */
void __thiscall wnd_handle_show_raise(WndBase *self)

{
  wnd_obj_show_raise(self->native_wnd);
  return;
}

/* 0040894c auto */
void __cdecl ui_pump_messages_net(void)

{
  win_flush_pending_msgs();
  if (2 < game.multiplayer) {
    net_process_messages(&net_session_block,1,0);
  }
  return;
}

/* 0040bc40 auto */
void __thiscall dlg_reset(Dialog *self,i32 flags)

{
  dialog_init(self,0,0,0,flags);
  return;
}

/* 0040bc80 auto */
i32 __thiscall dlg_show_modal(Dialog *self,iptr parent)

{
  i32 result;
  
  result = dialog_run_modal(self,0,parent);
  return result;
}

/* 0040e017 auto */
void __cdecl menu_find_city(void)

{
  bool visible;
  iptr adjective;
  iptr objective;
  iptr city2;
  iptr civ2;
  byte civ_byte;
  iptr city;
  int count;
  Dialog dialog2;
  int civ;
  i32 seh_handler;
  i8 *seh_scope;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  dialog_ctor(&dialog2,0x4000);
  civ2 = human_civ[0];
  eh_state = 0;
  count = 0;
  dlg_load_game_section(&dialog2,(const char *)&str_findcity,0x800001);
  for (city = 0; city < game.num_cities; city++) {
    if (cities[city].id != 0) {
      visible = false;
      civ = (int)cities[city].owner;
      if ((game.reveal_map != '\0') ||
         (((game.game_flags & 0x80) != 0 && ((prefs_game_rules_block.scenario_flags[0] & 8) != 0)))) {
        visible = true;
      }
      if (civ == civ2) {
        visible = true;
      }
      civ_byte = (byte)civ2;
      if (((1 << (civ_byte & 0x1f) & (int)(char)cities[city].known_to) != 0) ||
         ((int)cities[city].owner == (civ2 & 0xffU))) {
        visible = true;
      }
      if (visible) {
        text_clear();
        text_append((const char *)(city * 0x58 + (iptr)((u8 *)&cities + 32)));
        if (civ != civ2) {
          text_append_space();
          text_append_lparen();
          adjective = civ_adjective(civ);
          text_append((const char *)adjective);
          text_append_rparen();
        }
        if ((((game.game_flags & 0x80) != 0) && ((prefs_game_rules_block.scenario_flags[0] & 2) != 0)) &&
           (objective = city_objective_value(city), objective != 0)) {
          text_append_space();
          text_append_lparen();
          text_append_label(0x1b0);
          if (1 < objective) {
            text_append((const char *)&str_x);
            text_append_int(objective);
          }
          text_append_rparen();
        }
        dialog_add_option((DialogOptionList *)&dialog2,(const char *)&map_views_block.text_buffer,city,0);
        count++;
      }
    }
  }
  if (count == 0) {
    eh_state = 0xffffffff;
    /* inlined unwind funclet 0040e38d */ { dialog_dtor(&dialog2); }
  }
  else {
    city2 = dlg_show_modal(&dialog2,0);
    if (city2 < 0) {
      eh_state = 0xffffffff;
      /* inlined unwind funclet 0040e38d */ { dialog_dtor(&dialog2); }
    }
    else {
      mapview_center_on
                ((ViewWindow *)((i8 *)&map_views_block.map_views),(int)cities[city2].x,(int)cities[city2].y);
      if ((dialog2.result_extra != 0) && ((cities[city2].owner == civ2 || (game.reveal_map != '\0')))
         ) {
        city_window_open((ScaledWindowView *)((i8 *)&city_window_block.city_window),city2);
      }
      eh_state = 0xffffffff;
      /* inlined unwind funclet 0040e38d */ { dialog_dtor(&dialog2); }
    }
  }
  return;
}

/* 0040e3b1 auto */
void __cdecl menu_revolution(void)

{
  iptr text;
  int choice;
  iptr civ;
  
  civ = human_civ[0];
  if (((game.game_flags & 0x80) == 0) || ((prefs_game_rules_block.scenario_flags[0] & 0x10) == 0)) {
    if ((civs[human_civ[0]].flags & 8) == 0) {
      if (civs[human_civ[0]].government != '\0') {
        text = civ_get_adjective(human_civ[0]);
        text_set_string_arg(0,(const char *)text);
        text_set_label_arg(1,government_names[civs[civ].government]);
        choice = popup_game_with_sprite((const char *)&str_revolution,(iptr)(((i8 *)&government_sprites_block.government_sprites) +
                                                  (uint)civs[civ].government * 0x3c),
                                   (ui_large_screen == 0) - 1 & 8);
        if (choice == 0) {
          snd_play_effect(0x3e,1,0,0);
          text = (iptr)(civ_name_plural(civ));
          text_set_string_arg(0,(const char *)text);
          popup_game_with_sprite((const char *)&str_startrev,(iptr)&popup_info_icon_sprite,0);
          civ_set_government(civ,0);
          menu_update_states();
        }
      }
    }
    else {
      civ_change_government(human_civ[0],1);
    }
  }
  return;
}

/* 0040f320 auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall wnd_set_modal_idle_callback(ModalMenuWindow *self,iptr callback)

{
  self->on_modal_idle = callback;
  return;
}

/* 0040f350 auto */
void __thiscall wnd_set_keyboard_nav(Wnd *self,i32 enabled)

{
  *(i8 *)&self->keyboard_nav = (i8)enabled;
  return;
}

/* 0040ffa0 auto */
i32 __thiscall
dlg_load_game_section(Dialog *self,const char *section,i32 flags)

{
  i32 result;
  
  result = dialog_load_text_ex(self,(const char *)&str_game_7,section,0,flags);
  return result;
}

/* 0040ffe0 auto */
i32 __thiscall
dialog_load_text_ex
          (Dialog *self,const char *filename,const char *section,i32 arg,i32 flags)

{
  i32 result;
  
  result = dialog_load_text_section(self,filename,section,arg,0,0,0,0,flags);
  return result;
}

/* 00410030 auto */
i32 __cdecl popup_game_with_sprite(const char *section,iptr sprite,i32 sprite_flags)

{
  i32 result;
  
  result = popup_text_with_sprite((iptr)&str_game_7,section,0,sprite,sprite_flags);
  return result;
}

/* 00410e0a auto */
i32 __cdecl ui_paradrop_cursor_active(void)

{
  i32 active;
  
  if ((map_views_block.mapview_cursor_id[0] == 0x202) || (map_views_block.mapview_cursor_id[0] == 0x203)) {
    active = 1;
  }
  else {
    active = 0;
  }
  return active;
}

/* 00414b70 auto */
void __thiscall wnd_set_cursor_now(WndCursorView *self,iptr cursor,i32 flag)

{
  wnd_obj_set_cursor_now(self->native_wnd,cursor,flag);
  return;
}

/* 00414bb0 auto */
i32 __thiscall wnd_client_height(WndBase *self)

{
  i32 height;
  
  height = wnd_obj_client_height(self->native_wnd);
  return height;
}

/* 00414be0 auto */
u32 __thiscall wnd_set_mousemove_handler(WndHandlersMouseSetView *self,iptr handler)

{
  u32 old_handler;
  
  old_handler = self->on_mouse_move;
  self->on_mouse_move = handler;
  return old_handler;
}

/* 00414c20 auto */
u32 __thiscall wnd_set_lbuttondown_handler(WndHandlersMouseSetView *self,iptr handler)

{
  u32 old_handler;
  
  old_handler = self->on_lbutton_down;
  self->on_lbutton_down = handler;
  return old_handler;
}

/* 00414c60 auto */
u32 __thiscall wnd_set_lbuttonup_any_handler(WndHandlersMouseSetView *self,iptr handler)

{
  u32 old_handler;
  
  old_handler = ((WndHandlersMouseSetViewExt *)self)->on_lbutton_up_any;
  ((WndHandlersMouseSetViewExt *)self)->on_lbutton_up_any = handler;
  return old_handler;
}

/* 00414ca0 auto */
u32 __thiscall wnd_set_dblclick_handler(WndHandlersMouseSetView *self,iptr handler)

{
  u32 old_handler;
  
  old_handler = ((WndHandlersMouseSetViewExt *)self)->on_dblclick;
  ((WndHandlersMouseSetViewExt *)self)->on_dblclick = handler;
  return old_handler;
}

/* 00414ce0 auto */
void __thiscall wnd_set_capture(WndBase *self)

{
  NativeWindow *hwnd;
  
  hwnd = wnd_get_window(self);
  wnd_obj_set_capture(hwnd);
  return;
}

/* 00414d10 auto */
NativeWindow * __thiscall wnd_get_window(WndBase *self)

{
  return self->native_wnd;
}

/* 00414d40 auto */
void __thiscall wnd_release_capture(WndBase *self)

{
  NativeWindow *hwnd;
  
  hwnd = wnd_get_window(self);
  wnd_obj_release_capture(hwnd);
  return;
}

/* 00414da0 auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall wnd_set_caption_button_handler(FrameWindow *self,iptr handler)

{
  self->on_caption_button = handler;
  return;
}

/* 00414dd0 auto */
i32 __cdecl popup_game_with_city(const char *section,iptr city)

{
  i32 result;
  
  result = popup_text_with_city((const char *)&str_game_7,section,0,city);
  return result;
}

/* 004190d0 auto */
i32 __cdecl popup_text(const char *filename,const char *section)

{
  i32 result;
  
  result = popup_text_flags(filename,section,0);
  return result;
}

/* 00419100 auto */
i32 __cdecl popup_text_flags(const char *filename,const char *section,i32 flags)

{
  i32 result;
  
  result = popup_text_ex(filename,section,0,flags);
  return result;
}

/* 00419130 auto */
i32 __cdecl popup_text_ex(const char *filename,const char *section,i32 dlg_flags,i32 flags)

{
  i32 result;
  
  result = popup_text_run((iptr)filename,section,dlg_flags,0,0,0,flags);
  return result;
}

/* 00419b80 auto */
void __cdecl wnd_flush_paint(void)

{
  win_dispatch_all_paints();
  return;
}

/* 00419ba0 auto */
void __thiscall wnd_set_bg_color(WndBase *self,i32 color)

{
  wnd_obj_set_bg_color(self->native_wnd,color);
  return;
}

/* 00419be0 auto */
void __thiscall wnd_set_bg_surface(WndBase *self,DibSurface *surface)

{
  wnd_obj_set_bg_surface(self->native_wnd,surface);
  return;
}

/* 00421dd0 auto */
void __thiscall dialog_init_default(Dialog *self)

{
  dialog_init(self,0,0,0,0);
  return;
}

/* 00421e00 auto */
/* Library Function - Single Match
    public: int __thiscall CSocket::Create(unsigned int,int,char const *)
   
   Library: Visual Studio 1998 Debug */

i32 __thiscall
dialog_load_text(Dialog *self,const char *filename,const char *section,i32 flags)

{
  i32 result;
  
  result = dialog_load_text_ex(self,filename,section,0,flags);
  return result;
}

/* 00421e40 auto */
void __cdecl dlg_set_scale(i32 numerator,i32 denominator)

{
  dlg_scale_num = numerator;
  dlg_scale_den = denominator;
  return;
}

/* 00421e70 auto */
i32 __cdecl popup_game_flags(const char *section,i32 flags)

{
  i32 result;
  
  result = popup_text_flags((const char *)&str_game_7,section,flags);
  return result;
}

/* 00421ea0 auto */
i32 __cdecl popup_game(const char *section)

{
  i32 result;
  
  result = popup_text((const char *)&str_game_7,section);
  return result;
}

/* 00421ed0 auto */
i32 __cdecl dlg_game_text_input(const char *section,i32 max_len,char *buf,iptr default_text)

{
  i32 result;
  
  result = dlg_text_input((iptr)&str_game_7,section,max_len,(iptr)buf,default_text);
  return result;
}

/* 00426f30 auto */
Dialog * __thiscall dialog_scalar_dtor(Dialog *self,uint flags)

{
  dialog_dtor(self);
  if ((flags & 1) != 0) {
    operator_delete(self);
  }
  return self;
}

/* 00426f80 auto */
void __thiscall wnd_maximize(WndBase *self)

{
  wnd_obj_maximize(self->native_wnd);
  return;
}

/* 00426fb0 auto */
i32 __cdecl popup_game_sprite_flags(const char *section,i32 dlg_flags,iptr sprite,i32 sprite_flags)

{
  i32 result;
  
  result = popup_text_with_sprite((iptr)&str_game_7,section,dlg_flags,sprite,sprite_flags);
  return result;
}

/* 0042a768 auto */
void __thiscall picwnd_close(PictureWindowCore *self)

{
  if (-1 < (int)self->report_id) {
    self->report_id = 0xffffffff;
    wnd_remove_all_controls((WndControlRemoveView *)self->window_2);
    surface_release((DibSurface *)&self->rates_civ);
    frame_wnd_close((DibSurface *)self);
  }
  return;
}

/* 0042a7bc auto */
void __thiscall
picwnd_open
          (PictureWindow *self,uint resource_id,u32 report,u32 style,u32 img_width,u32 img_height,
          u32 win_width,u32 win_height)

{
  u32 wnd_h;
  int border;
  int scr_height;
  u32 wnd_w;
  int nonclient_height;
  GamePalette palette;
  i32 seh_handler;
  i8 *seh_scope;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  palette_init(&palette);
  eh_state = 0;
  picwnd_close((PictureWindowCore *)((i8 *)&advisor_window_block.advisor_window));
  ui_set_button_font((iptr)&advisor_button_font_block.advisor_button_font);
  self->controls_created = 0;
  self->frame_state = 0;
  self->page_count = 1;
  self->first_row = 0;
  self->report_civ = 1;
  self->report_param = 0;
  self->report_id = report;
  self->frame_style = style;
  wnd_w = GetSystemMetrics(2);
  self->vscroll_width = wnd_w;
  border = frame_border_width;
  if ((int)resource_id < 0) {
    resource_id = ~resource_id + 1;
  }
  else if (resource_id != 10000) {
    resource_id += 0x31;
  }
  self->image_width = img_width;
  self->image_height = img_height;
  win_flush_pending_msgs();
  if (resource_id == 10000) {
    surface_load_gif_file((DibSurface *)&self->rates_civ,(const char *)&str_scredits_gif,10,0xc0,(iptr)&palette)
    ;
  }
  else {
    surface_load_gif_resource((DibSurface *)&self->rates_civ,resource_id,10,0xc0,(iptr)&palette);
  }
  win_flush_pending_msgs();
  if ((int)img_width < 1) {
    wnd_w = surface_width((DibSurface *)&self->rates_civ);
    self->image_width = wnd_w;
  }
  if ((int)img_height < 1) {
    wnd_w = surface_height((DibSurface *)&self->rates_civ);
    self->image_height = wnd_w;
  }
  self->window_width = win_width;
  self->window_height = win_height;
  if (self->window_width == 0) {
    self->window_width = self->image_width;
  }
  if ((int)self->window_width < 0) {
    self->window_width = self->image_width - self->window_width;
  }
  if (self->window_height == 0) {
    self->window_height = self->image_height;
  }
  if ((int)self->window_height < 0) {
    self->window_height = self->image_height - self->window_height;
  }
  scr_height = caption_font_block.screen_height;
  wnd_w = self->window_width;
  wnd_h = self->window_height;
  nonclient_height = wnd_nonclient_height((WndBase *)((i8 *)&main_frame_wnd_block.main_frame_wnd));
  frame_wnd_create
            ((FrameWindow *)self,0,(self->frame_style == 0) - 1 & 8,
             (caption_font_block.screen_width >> 1) - ((int)(wnd_w + border * 2) >> 1),
             (scr_height - nonclient_height >> 1) - ((int)(wnd_h + border * 2) >> 1),self->image_width,self->image_height,
             0,border,border);
  eh_state = 0xffffffff;
  /* inlined unwind funclet 0042ab9b */ { palette_destroy(&palette); }
  return;
}

/* 0042abc1 auto */
void __thiscall
picwnd_blit_at
          (FrameWindow *self,int x,int y,i32 width,i32 height)

{
  gfx_copy_rect_xywh((iptr)&self->rates_civ,(iptr)self,x,y,self->client_x + x,
                     self->client_y + y,width,height);
  return;
}

/* 0042ac18 auto */
void __thiscall picwnd_blit(PictureWindow *self)

{
  picwnd_blit_at((FrameWindow *)self,0,0,self->image_width,self->image_height);
  return;
}

/* 0043c110 auto */
/* Library Function - Single Match
    public: __thiscall CDaoFieldInfo::~CDaoFieldInfo(void)
   
   Library: Visual Studio 1998 Debug */

void __thiscall picwnd_dtor(void *self)

{
  i32 seh_handler;
  i8 *seh_scope;
  int eh_state;
  
  eh_state = eh_state & 0xff;
  (*((char *)&eh_state + 0)) = 5;
  /* inlined unwind funclet 0043c19c */ { scrollbar_dtor((Control *)(*(int *)&self + 0x410)); }
  (*((char *)&eh_state + 0)) = 4;
  /* inlined unwind funclet 0043c1ab */ { ctrl_dtor((Control *)(*(int *)&self + 0x3d4)); }
  (*((char *)&eh_state + 0)) = 3;
  /* inlined unwind funclet 0043c1ba */ { ctrl_dtor((Control *)(*(int *)&self + 0x398)); }
  (*((char *)&eh_state + 0)) = 2;
  /* inlined unwind funclet 0043c1c9 */ { ctrl_dtor((Control *)(*(int *)&self + 0x35c)); }
  (*((char *)&eh_state + 0)) = 1;
  /* inlined unwind funclet 0043c1d8 */ { ctrl_dtor((Control *)(*(int *)&self + 800)); }
  eh_state = eh_state & 0xffffff00;
  /* inlined unwind funclet 0043c1e7 */ { surface_dtor((DibSurface *)(*(int *)&self + 0x2d8)); }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 0043c1f6 */ { frame_wnd_dtor(*(DibSurface **)&self); }
  return;
}

/* 0043c260 auto */
ViewWindow * __thiscall picwnd_ctor(ViewWindow *self)

{
  i32 seh_handler;
  i8 *seh_scope;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  frame_wnd_ctor((SurfaceWindow *)self);
  eh_state = 0;
  surface_ctor((DibSurface *)&self->rates_civ);
  (*((char *)&eh_state + 0)) = 1;
  button_ctor((Control *)&self->bar_height);
  (*((char *)&eh_state + 0)) = 2;
  button_ctor((Control *)&self->no_thanks_button_value);
  (*((char *)&eh_state + 0)) = 3;
  button_ctor((Control *)self->lux_rate_scrollbar);
  (*((char *)&eh_state + 0)) = 4;
  button_ctor((Control *)self->picwnd_extra_button);
  eh_state = (eh_state & 0xffffff00 | (byte)(5));
  scrollbar_ctor((Control *)self->picwnd_scrollbar);
  self->vtable = (u32)((pointer *)(ptr_fun_rest + 4));
  return self;
}

/* 0043c5c0 auto */
i32 __thiscall wnd_nonclient_height(WndBase *self)

{
  i32 height;
  
  height = wnd_obj_frame_height(self->native_wnd);
  return height;
}

/* 0043c630 auto */
void __thiscall wnd_disable(WndBase *self)

{
  wnd_obj_enable(self->native_wnd,0);
  return;
}

/* 0043c660 auto */
void __thiscall wnd_enable(WndBase *self)

{
  wnd_obj_enable(self->native_wnd,1);
  return;
}

/* 0043c990 auto */
void __thiscall dialog_set_list_indent(DialogCore *self,uptr indent,iptr index)

{
  ((DialogWindowView *)self)->list_indents[index] = indent;
  return;
}

/* 0043c9d0 auto */
void __thiscall dialog_load_game_text(Dialog *self,const char *section)

{
  dialog_load_text_noflags(self,(const char *)&str_game_7,section);
  return;
}

/* 0043ca10 auto */
void __thiscall dialog_load_text_noflags(Dialog *self,const char *filename,const char *section)

{
  dialog_load_text(self,filename,section,0);
  return;
}

/* 00444270 auto */
i32 __cdecl popup_debug_text(const char *section)

{
  i32 result;
  
  result = popup_text((const char *)&str_debug_11,section);
  return result;
}

/* 004442a0 auto */
i32 __cdecl dlg_game_txt_with_unit_flags(const char *section,iptr unit,i32 flags)

{
  i32 result;
  
  result = popup_text_with_unit_sprite((const char *)&str_game_7,section,0,unit,flags);
  return result;
}

/* 004442e0 auto */
i32 __cdecl dlg_game_txt_with_unit(const char *section,iptr unit)

{
  i32 result;
  
  result = popup_text_with_unit((const char *)&str_game_7,section,0,unit);
  return result;
}

/* 00447c3c auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl caption_close_button_sprite_global_init(void)

{
  caption_close_button_sprite_static_init();
  caption_close_button_sprite_reg_atexit();
  return;
}

/* 00447c56 auto */
void __cdecl caption_close_button_sprite_static_init(void)

{
  sprite_init((Sprite *)((i8 *)&caption_close_button_sprite_block.caption_close_button_sprite));
  return;
}

/* 00447c70 auto */
void __cdecl caption_close_button_sprite_reg_atexit(void)

{
  _atexit(caption_close_button_sprite_atexit_dtor);
  return;
}

/* 00447c8d auto */
void __cdecl caption_close_button_sprite_atexit_dtor(void)

{
  sprite_destroy((Sprite *)((i8 *)&caption_close_button_sprite_block.caption_close_button_sprite));
  return;
}

/* 00447ca7 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl caption_zoom_out_sprite_global_init(void)

{
  caption_zoom_out_sprite_static_init();
  caption_zoom_out_sprite_reg_atexit();
  return;
}

/* 00447cc1 auto */
void __cdecl caption_zoom_out_sprite_static_init(void)

{
  sprite_init((Sprite *)((i8 *)&caption_zoom_out_sprite));
  return;
}

/* 00447cdb auto */
void __cdecl caption_zoom_out_sprite_reg_atexit(void)

{
  _atexit(caption_zoom_out_sprite_atexit_dtor);
  return;
}

/* 00447cf8 auto */
void __cdecl caption_zoom_out_sprite_atexit_dtor(void)

{
  sprite_destroy((Sprite *)((i8 *)&caption_zoom_out_sprite));
  return;
}

/* 00447d12 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl caption_zoom_out_btn_sprite_global_init(void)

{
  caption_zoom_out_btn_sprite_static_init();
  caption_zoom_out_btn_sprite_reg_atexit();
  return;
}

/* 00447d2c auto */
void __cdecl caption_zoom_out_btn_sprite_static_init(void)

{
  sprite_init((Sprite *)((i8 *)&caption_zoom_out_button_sprite_block.caption_zoom_out_button_sprite));
  return;
}

/* 00447d46 auto */
void __cdecl caption_zoom_out_btn_sprite_reg_atexit(void)

{
  _atexit(caption_zoom_out_btn_sprite_atexit_dtor);
  return;
}

/* 00447d63 auto */
void __cdecl caption_zoom_out_btn_sprite_atexit_dtor(void)

{
  sprite_destroy((Sprite *)((i8 *)&caption_zoom_out_button_sprite_block.caption_zoom_out_button_sprite));
  return;
}

/* 00447d7d auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl caption_view_mode_btn_sprite_global_init(void)

{
  caption_view_mode_btn_sprite_static_init();
  caption_view_mode_btn_sprite_reg_atexit();
  return;
}

/* 00447d97 auto */
void __cdecl caption_view_mode_btn_sprite_static_init(void)

{
  sprite_init((Sprite *)((i8 *)&caption_view_mode_button_sprite));
  return;
}

/* 00447db1 auto */
void __cdecl caption_view_mode_btn_sprite_reg_atexit(void)

{
  _atexit(caption_view_mode_button_sprite_static_dtor);
  return;
}

/* 00447dce auto */
void __cdecl caption_view_mode_button_sprite_static_dtor(void)

{
  sprite_destroy((Sprite *)((i8 *)&caption_view_mode_button_sprite));
  return;
}

/* 00447de8 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl scroll_up_button_sprite_global_init(void)

{
  scroll_up_button_sprite_static_init();
  scroll_up_button_sprite_reg_atexit();
  return;
}

/* 00447e02 auto */
void __cdecl scroll_up_button_sprite_static_init(void)

{
  sprite_init((Sprite *)((i8 *)&scroll_up_button_sprite));
  return;
}

/* 00447e1c auto */
void __cdecl scroll_up_button_sprite_reg_atexit(void)

{
  _atexit(scroll_up_button_sprite_static_dtor);
  return;
}

/* 00447e39 auto */
void __cdecl scroll_up_button_sprite_static_dtor(void)

{
  sprite_destroy((Sprite *)((i8 *)&scroll_up_button_sprite));
  return;
}

/* 00448d7b auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl popup_info_icon_sprite_global_init(void)

{
  popup_info_icon_sprite_static_init();
  popup_info_icon_sprite_reg_atexit();
  return;
}

/* 00448d95 auto */
void __cdecl popup_info_icon_sprite_static_init(void)

{
  sprite_init((Sprite *)((i8 *)&popup_info_icon_sprite));
  return;
}

/* 00448daf auto */
void __cdecl popup_info_icon_sprite_reg_atexit(void)

{
  _atexit(popup_info_icon_sprite_static_dtor);
  return;
}

/* 00448dcc auto */
void __cdecl popup_info_icon_sprite_static_dtor(void)

{
  sprite_destroy((Sprite *)((i8 *)&popup_info_icon_sprite));
  return;
}

/* 00448e51 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl window_border_tile_surface_global_init(void)

{
  window_border_tile_surface_static_init();
  window_border_tile_surface_reg_atexit();
  return;
}

/* 00448e6b auto */
void __cdecl window_border_tile_surface_static_init(void)

{
  surface_ctor((DibSurface *)((i8 *)&window_border_tile_surface));
  return;
}

/* 00448e85 auto */
void __cdecl window_border_tile_surface_reg_atexit(void)

{
  _atexit(window_border_tile_surface_static_dtor);
  return;
}

/* 00448ea2 auto */
void __cdecl window_border_tile_surface_static_dtor(void)

{
  surface_dtor((DibSurface *)((i8 *)&window_border_tile_surface));
  return;
}

/* 00448ebc auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl panel_texture_surface_global_init(void)

{
  panel_texture_surface_static_init();
  panel_texture_surface_reg_atexit();
  return;
}

/* 00448ed6 auto */
void __cdecl panel_texture_surface_static_init(void)

{
  surface_ctor((DibSurface *)((i8 *)&panel_texture_surface));
  return;
}

/* 00448ef0 auto */
void __cdecl panel_texture_surface_reg_atexit(void)

{
  _atexit(panel_texture_surface_static_dtor);
  return;
}

/* 00448f0d auto */
void __cdecl panel_texture_surface_static_dtor(void)

{
  surface_dtor((DibSurface *)((i8 *)&panel_texture_surface));
  return;
}

/* 0044c5a0 auto */
SurfaceWindow * __thiscall surfwnd_ctor(SurfaceWindow *self)

{
  i32 seh_handler;
  i8 *seh_scope;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  surface_ctor((DibSurface *)self);
  eh_state = 0;
  surfwnd_wnd_ctor((Wnd *)self->window_2);
  self->vtable = (u32)((pointer *)(ptr_fun_rest + 8));
  self->handler_slot_100 = 0;
  self->on_paint = 0;
  return self;
}

/* 0044c670 auto */
Wnd * __thiscall surfwnd_wnd_ctor(Wnd *self)

{
  i32 seh_handler;
  i8 *seh_scope;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  wnd_ctor((ModalMenuWindow *)self);
  self->control_list = 0;
  self->handler_slot_bc = 0;
  self->handler_slot_c0 = 0;
  *(i8 *)&self->keyboard_nav = 1;
  return self;
}

/* 0044c730 auto */
ModalMenuWindow * __thiscall wnd_ctor(ModalMenuWindow *self)

{
  i32 seh_handler;
  i8 *seh_scope;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  wnd_record_init((WndBase *)self);
  eh_state = 0;
  wnd_handlers_ctor((WndHandlers *)self->wnd_handlers);
  self->menu = 0;
  self->on_menu_pos_command = 0;
  self->on_command = 0;
  self->min_width = 0;
  self->min_height = 0;
  self->max_width = 0x4000;
  self->max_height = 0x4000;
  self->handler_slot_a8 = 0;
  self->handler_slot_ac = 0;
  self->modal_running = 0;
  self->hscroll_step = 1;
  self->vscroll_step = 1;
  self->on_menu_select = 0;
  self->on_modal_idle = 0;
  return self;
}

/* 0044c8b0 auto */
/* Library Function - Single Match
    public: __thiscall CString::CString(void)
   
   Library: Visual Studio 1998 Debug */

WndHandlers * __thiscall wnd_handlers_ctor(WndHandlers *self)

{
  wnd_clear_handlers(self);
  return self;
}

/* 0044c8e0 auto */
void __thiscall wnd_clear_handlers(WndHandlers *self)

{
  self->on_mouse_move = 0;
  self->on_lbutton_down = 0;
  self->on_lbutton_up_raw = 0;
  self->on_lbutton_up = 0;
  self->on_rbutton_down = 0;
  self->on_rbutton_up_raw = 0;
  self->on_rbutton_up = 0;
  self->on_dblclick = 0;
  self->on_key_down_pre = 0;
  self->on_key_up = 0;
  self->on_key_down = 0;
  self->on_char = 0;
  self->on_close = 0;
  self->on_minimize = 0;
  self->on_restore = 0;
  self->on_set_focus = 0;
  self->on_size = 0;
  self->on_move = 0;
  self->on_msg_44 = 0;
  self->on_hscroll = 0;
  self->on_hscroll_track = 0;
  self->on_vscroll = 0;
  self->on_vscroll_track = 0;
  self->on_msg_4c8 = 0;
  self->on_enter_size_move = 0;
  self->on_exitsizemove = 0;
  return;
}

/* 0044ca40 auto */
void __thiscall wnd_handlers_dtor(void *self)

{
  return;
}

/* 0044ca60: written by hand in src/game/unwind.cpp */

/* 0044cb20 auto */
i32 __thiscall surfwnd_wnd_dtor(void *self)

{
  i32 seh_handler;
  i8 *seh_scope;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  /* inlined unwind funclet 0044cb5e */ { wnd_dtor(*(WndBase **)&self); }
  return seh_handler;
}

/* 0044cba0: written by hand in src/game/unwind.cpp */

/* 0044cc80: written by hand in src/game/throneroom.cpp */

/* 0044cd9b: written by hand in src/game/throneroom.cpp */

/* 00450390 auto */
void __thiscall wnd_set_palette(WndBase *self,iptr palette)

{
  self->wnd_palette = palette;
  wnd_apply_palette_handle(self,palette);
  return;
}

/* 004503d0 auto */
void __thiscall wnd_hide(WndBase *self)

{
  wnd_obj_hide(self->native_wnd);
  return;
}

/* 00450400 auto */
void __thiscall wnd_center(WndCenterView *self)

{
  wnd_obj_center(self->wnd_obj,0,0);
  return;
}

/* 00450440 auto */
void __thiscall wnd_apply_palette_handle(WndBase *self,iptr palette)

{
  wnd_obj_select_palette(self->native_wnd,*(i32 *)(palette + 0x404));
  return;
}

/* 00451890 auto */
void __thiscall wnd_get_cursor_pos(WndBase *self,iptr out_x,iptr out_y)

{
  NativeWindow *hwnd;
  
  hwnd = wnd_get_window(self);
  wnd_obj_get_cursor_pos(hwnd,(LONG *)out_x,(LONG *)out_y);
  return;
}

/* 004518d0 auto */
void __thiscall wnd_activate(Wnd *self)

{
  wnd_focus_and_raise((WndBase *)self);
  wnd_focus_first_control(self);
  return;
}

/* 00451900 auto */
void __thiscall wnd_focus_and_raise(WndBase *self)

{
  wnd_obj_focus_and_raise(self->native_wnd);
  return;
}

/* 00451930 auto */
Control * __thiscall hotspot_ctor(Control *self)

{
  i32 seh_handler;
  i8 *seh_scope;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  ctrl_base_ctor(self);
  return self;
}

/* 004519b0 auto */
void __thiscall
hotspot_create(ClickControl *self,iptr parent,iptr id,iptr rect)

{
  u32 new_hwnd;
  
  if (self->hwnd != 0) {
    ctrl_destroy((Control *)self);
  }
  ctrl_init((Control *)self,parent,1,id,(RECT *)rect);
  self->is_enabled = 0;
  self->on_click = 0;
  self->on_select = 0;
  self->font = 0;
  self->scroll_pos = 0;
  new_hwnd = hotspot_create_hwnd((int *)rect,(iptr)self);
  self->hwnd = new_hwnd;
  return;
}

/* 00451a60 auto */
void __thiscall hotspot_set_click_callback(HotspotClickSetView *self,iptr callback)

{
  self->on_click = callback;
  return;
}

/* 00451a90 auto */
/* Library Function - Single Match
    public: void __thiscall CDialog::SetHelpID(unsigned int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall hotspot_set_dblclick_callback(HotspotDblClickSetView *self,iptr callback)

{
  self->on_dblclick = callback;
  return;
}

/* 00453aa0 auto */
Hotspot * __thiscall hotspot_scalar_dtor(Hotspot *self,uint flags)

{
  hotspot_dtor(self);
  if ((flags & 1) != 0) {
    operator_delete(self);
  }
  return self;
}

/* 00453af0 auto */
void __cdecl ui_pump_messages(void)

{
  win_dispatch_all_messages();
  return;
}

/* 00453ba0 auto */
void __thiscall hotspot_dtor(Hotspot *self)

{
  i32 seh_handler;
  i8 *seh_scope;
  i32 eh_state;
  
  eh_state = 0;
  if (self->hwnd != 0) {
    region_dispose(self->hwnd);
  }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 00453bfa */ { ctrl_base_dtor(*(ControlBase **)&self); }
  return;
}

/* 00456ee0 auto */
/* Library Function - Single Match
    public: class ostream * __thiscall ios::tie(class ostream *)
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall wnd_set_keydown_pre_handler(WndSetKeydownPreHandlerView *self,iptr handler)

{
  u32 old_handler;
  
  old_handler = self->tied_stream;
  self->tied_stream = handler;
  return old_handler;
}

/* 0046768b auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl menu_handle_654fd4_global_init(void)

{
  menu_handle_654fd4_static_init();
  menu_handle_654fd4_reg_atexit();
  return;
}

/* 004676a5 auto */
void __cdecl menu_handle_654fd4_static_init(void)

{
  menu_handle_ctor((GameMenu *)((i8 *)&civ_saved_cursor_x_block.secondary_menu_handle));
  return;
}

/* 004676bf auto */
void __cdecl menu_handle_654fd4_reg_atexit(void)

{
  _atexit(menu_handle_654fd4_atexit_dtor);
  return;
}

/* 004676dc auto */
void __cdecl menu_handle_654fd4_atexit_dtor(void)

{
  menu_handle_dtor((GameMenu *)((i8 *)&civ_saved_cursor_x_block.secondary_menu_handle));
  return;
}

/* 0046e287 auto */
void __cdecl ui_delay_ticks(int ticks)

{
  DWORD start_tick;
  DWORD now_tick;
  
  start_tick = timeGetTime();
  do {
    win_flush_pending_msgs();
    now_tick = timeGetTime();
    if (2 < game.multiplayer) {
      net_process_messages(&net_session_block,1,0);
    }
  } while ((int)(now_tick - start_tick) < (ticks * 0x32) / 3);
  return;
}

/* 0046f18f auto */
void __cdecl ui_blit_all_windows(void)

{
  int view;
  
  for (view = 0; view < 8; view++) {
    if ((view == 0) || (*(short *)(((i8 *)&map_views_block.map_view_open_flags) + view * 0x3f0) != 0)) {
      wnd_blit_surface((DibSurface *)(((i8 *)&map_views_block.map_views) + view * 0x3f0));
    }
  }
  wnd_blit_surface((DibSurface *)((i8 *)&minimap_window_block.minimap_window));
  wnd_blit_surface((DibSurface *)((i8 *)&status_window_block.status_window));
  wnd_blit_surface((DibSurface *)((i8 *)&city_window_block.city_window));
  wnd_flush_paint();
  return;
}

/* 004731d2 auto */
uint __cdecl
ui_file_name_dialog(iptr parent,const char *title,iptr file_buf,iptr filter,iptr default_ext,int must_exist,
            int is_save)

{
  NativeWindow *wnd;
  BOOL dlg_ok;
  char success;
  OPENFILENAMEA ofn;
  
  _memset(&ofn,0,0x4c);
  ofn.lStructSize = 0x4c;
  ofn.hwndOwner = (HWND)0x0;
  if (parent != 0) {
    wnd = wnd_get_window((WndBase *)parent);
    ofn.hwndOwner = wnd->hwnd;
  }
  ofn.lpstrFilter = (LPCSTR)filter;
  ofn.nFilterIndex = 1;
  ofn.lpstrFile = (LPSTR)file_buf;
  ofn.nMaxFile = 0x100;
  ofn.lpstrTitle = title;
  ofn.lpstrDefExt = (LPCSTR)default_ext;
  if (must_exist == 0) {
    ofn.Flags = 0x80e;
  }
  else {
    ofn.Flags = 0x180e;
  }
  if (is_save == 0) {
    dlg_ok = GetOpenFileNameA(&ofn);
    success = (char)dlg_ok;
  }
  else {
    dlg_ok = GetSaveFileNameA(&ofn);
    success = (char)dlg_ok;
  }
  if (success != 1) {
    CommDlgExtendedError();
  }
  return (uint)(success == 1);
}

/* 00484d52 auto */
void __cdecl ui_flush_input(void)

{
  if (net_session_block.mp_simultaneous_moves == '\0') {
    input_flush_events();
  }
  win_flush_pending_msgs();
  wnd_flush_paint();
  win_flush_pending_msgs();
  return;
}

/* 004897fa auto */
void __cdecl ui_redraw_all_maps(int force)

{
  if ((moving_units_mode != 0) || (force != 0)) {
    moving_units_mode = 0;
    unit_blink_phase = 1;
    unit_blink_skip_tick = 1;
    unit_blink_active = 0;
    status_redraw(1);
    mapviews_redraw_cursor();
    menu_update_states();
  }
  return;
}

/* 00489a0d auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl ui_focus_active_unit(int auto_next)

{
  iptr selectable;
  iptr unit;
  int unit_ok;
  bool start_blink;
  
  start_blink = moving_units_mode != 1;
  if (start_blink) {
    unit_blink_phase = 0;
    unit_blink_skip_tick = 1;
    mapviews_redraw_cursor();
    moving_units_mode = 1;
    unit_blink_active = 0;
  }
  selectable = unit_is_selectable((int)game.active_unit);
  if (selectable == 0) {
    unit_activate_next(auto_next);
  }
  start_blink = selectable != 0 && start_blink;
  unit = (iptr)game.active_unit;
  if ((((-1 < unit) && (unit < game.num_units)) && (units[unit].id != 0)) &&
     ((unit_ok = unit_is_selectable(unit), unit_ok != 0 &&
      (((game.multiplayer < 3 || (net_session_block.mp_simultaneous_moves != '\0')) ||
       ((auto_next == 0 || (net_session_block.mp_turn_civ == human_civ[0])))))))) {
    if (start_blink) {
      status_redraw(1);
    }
    map_cursor_x[0] = units[unit].x;
    map_cursor_y[0] = units[unit].y;
    if (start_blink) {
      mapviews_ensure_visible((int)map_cursor_x[0],(int)map_cursor_y[0],(int)units[unit].owner);
    }
    menu_update_states();
    map_views_block.unit_focus_done = 1;
    return;
  }
  unit_blink_active = 0;
  ui_redraw_all_maps(0);
  return;
}

/* 004904c0 auto */
void __cdecl popup_file_with_sprite(const char *filename,const char *section,iptr sprite,i32 sprite_flags)

{
  popup_text_with_sprite((iptr)filename,section,0,sprite,sprite_flags);
  return;
}

/* 00490500 auto */
void __cdecl popup_text_with_city_noflags(const char *filename,const char *section,i32 city)

{
  popup_text_with_city(filename,section,0,city);
  return;
}

/* 00490530 auto */
void __cdecl popup_text_with_unit_noflags(const char *filename,const char *section,iptr unit)

{
  popup_text_with_unit(filename,section,0,unit);
  return;
}

/* 004923c0 auto */
void __thiscall wnd_set_focus(WndBase *self)

{
  wnd_obj_set_focus(self->native_wnd);
  return;
}

/* 00497cc0 auto */
void __thiscall wnd_set_bg_tile(DiploLeaderView *self,DibSurface *tile)

{
  wnd_obj_set_bg_tile(self->wnd_obj,tile);
  return;
}

/* 00497d00 auto */
void __thiscall wnd_set_caption_height(WndBase *self,i32 height)

{
  wnd_obj_set_caption_height(self->native_wnd,height);
  return;
}

/* 004a6b80 auto */
void __cdecl
popup_text_with_advance(const char *filename,const char *section,i32 dlg_flags,iptr advance,i32 sprite_flags)

{
  popup_text_with_sprite((iptr)filename,section,dlg_flags,
                     (iptr)(((i8 *)&government_sprites_block.advance_category_icon_sprites) +
                           (char)advances[advance].category * 0xf0 +
                           (char)advances[advance].epoch * 0x3c),sprite_flags);
  return;
}

/* 004a6bdc auto */
i32 __cdecl
popup_text_with_improvement(const char *filename,const char *section,i32 dlg_flags,int improvement,i32 sprite_flags)

{
  i32 result;
  i8 *sprite;
  
  if (improvement < 0x27) {
    sprite = ((i8 *)&caption_close_button_sprite_block.improvement_icon_sprites) + improvement * 0x3c;
  }
  else {
    sprite = ((i8 *)&caption_close_button_sprite_block.wonder_icon_sprites) + (improvement * 4 - 0x9c) * 0xf;
  }
  result = popup_text_with_sprite((iptr)filename,section,dlg_flags,(iptr)sprite,sprite_flags);
  return result;
}

/* 004a6c4b auto */
i32 __cdecl
popup_text_with_unit_sprite(const char *filename,const char *section,i32 dlg_flags,int unit_type,i32 sprite_flags)

{
  i32 result;
  
  result = popup_text_with_sprite((iptr)filename,section,dlg_flags,(iptr)(((i8 *)&pollution_sprite_block.unit_sprites) + unit_type * 0x3c),sprite_flags)
  ;
  return result;
}

/* 004a6c85 auto */
void __cdecl
popup_city_sprite_draw_cb(i32 dlg,iptr sprite,iptr city,i32 left,int x,
            i32 y)

{
  gfx_draw_city(sprite,city,0,x + 2,y,(ui_large_screen == 0) - 1 & 8);
  return;
}

/* 004a6cc5 auto */
i32 __cdecl popup_text_with_city(const char *filename,const char *section,i32 dlg_flags,iptr city)

{
  i32 result;
  Dialog dialog2;
  Sprite sprite;
  i32 seh_handler;
  i8 *seh_scope;
  int eh_state;
  
  eh_state = 0xffffffff;
  dialog_ctor(&dialog2,0x4000);
  eh_state = 0;
  sprite_init(&sprite);
  (*((char *)&eh_state + 0)) = 1;
  sprite_create_solid
            (&sprite,(2 - (uint)(ui_large_screen == 0)) * 0x40,(2 - (uint)(ui_large_screen == 0)) * 0x30
             ,0);
  dialog_load_text(&dialog2,filename,section,dlg_flags);
  dialog_set_sprite_draw_fn((DialogCore *)&dialog2,(iptr)popup_city_sprite_draw_cb);
  dialog_set_image_zoom((DialogWindowView *)&dialog2,0);
  dialog_add_sprite((DialogOptionList *)&dialog2,(iptr)&sprite,city,0);
  result = dlg_show_modal(&dialog2,0);
  (*(u32 *)&dlg_help_pressed) = dialog2.result_extra;
  eh_state = eh_state & 0xffffff00;
  /* inlined unwind funclet 004a6dc9 */ { sprite_destroy(&sprite); }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 004a6dd2 */ { dialog_dtor(&dialog2); }
  return result;
}

/* 004a6df7 auto */
void __cdecl
popup_unit_sprite_draw_cb(i32 dlg,iptr sprite,iptr unit,i32 left,int x,
            i32 y)

{
  gfx_draw_unit(sprite,unit,4,x + 2,y,(ui_large_screen == 0) - 1 & 8,0);
  return;
}

/* 004a6e39 auto */
i32 __cdecl popup_text_with_unit(const char *filename,const char *section,i32 dlg_flags,iptr unit)

{
  i32 result;
  Dialog dialog2;
  Sprite sprite;
  i32 seh_handler;
  i8 *seh_scope;
  int eh_state;
  
  eh_state = 0xffffffff;
  dialog_ctor(&dialog2,0x4000);
  eh_state = 0;
  sprite_init(&sprite);
  (*((char *)&eh_state + 0)) = 1;
  sprite_create_solid
            (&sprite,(2 - (uint)(ui_large_screen == 0)) * 0x40,(2 - (uint)(ui_large_screen == 0)) * 0x30
             ,0);
  dialog_load_text(&dialog2,filename,section,dlg_flags);
  dialog_set_sprite_draw_fn((DialogCore *)&dialog2,(iptr)popup_unit_sprite_draw_cb);
  dialog_set_image_zoom((DialogWindowView *)&dialog2,0);
  dialog_add_sprite((DialogOptionList *)&dialog2,(iptr)&sprite,unit,0);
  result = dlg_show_modal(&dialog2,0);
  (*(u32 *)&dlg_help_pressed) = dialog2.result_extra;
  eh_state = eh_state & 0xffffff00;
  /* inlined unwind funclet 004a6f3d */ { sprite_destroy(&sprite); }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 004a6f46 */ { dialog_dtor(&dialog2); }
  return result;
}

/* 004a93b3 auto */
void __cdecl accel_start_develop_city(iptr city,int num_tiles)

{
  byte civ;
  i8 terrain;
  char best_terrain;
  int x2;
  int y2;
  iptr x;
  int y;
  int result;
  int landmass;
  iptr best_tile;
  int i;
  iptr tile;
  uint best_score;
  uint score;
  
  x2 = (int)cities[city].x;
  y2 = (int)cities[city].y;
  net_batch_begin();
  for (i = 0; i < num_tiles; i++) {
    best_score = 0;
    best_tile = -1;
    for (tile = 0; tile < 0x14; tile++) {
      x = map_wrap_x((((i8 *)&dir_dy_table_block.city_tile_dx_table))[tile] + x2);
      y = (((i8 *)&dir_dy_table_block.city_tile_dy_table))[tile] + y2;
      result = map_in_bounds(x,y);
      if ((result != 0) && (result = tile_improvements(x,y), result == 0)) {
        score = 0;
        terrain = tile_terrain(x,y);
        switch(terrain) {
        case 0:
          score = 1;
          break;
        case 1:
          score = 4;
          break;
        case 2:
          result = tile_grassland_has_shield(x,y);
          if (result == 0) {
            score = 3;
          }
          else {
            score = 5;
          }
          break;
        case 4:
          score = 2;
        }
        if (score != 0) {
          if (tile < 8) {
            score++;
          }
          y = tile_resource(x,y);
          if (y != 0) {
            score += 3;
          }
          if (best_score < score) {
            best_score = score;
            best_tile = tile;
          }
        }
      }
    }
    if (best_tile < 0) break;
    x = map_wrap_x((((i8 *)&dir_dy_table_block.city_tile_dx_table))[best_tile] + x2);
    y = (((i8 *)&dir_dy_table_block.city_tile_dy_table))[best_tile] + y2;
    best_terrain = tile_terrain(x,y);
    tile_at(x,y);
    tile_set_improvements(x,y,0x10,1,1);
    if (best_terrain == 4) {
      tile_set_improvements(x,y,8,1,1);
    }
    else {
      tile_set_improvements(x,y,4,1,1);
    }
    tile_update_known(x,y,(int)cities[city].owner);
  }
  civ = cities[city].owner;
  for (tile = 0; tile < 0x2d; tile++) {
    x = map_wrap_x((((i8 *)&dir_dy_table_block.city_tile_dx_table))[tile] + x2);
    y = (((i8 *)&dir_dy_table_block.city_tile_dy_table))[tile] + y2;
    result = map_in_bounds(x,y);
    if ((result != 0) && (result = tile_is_ocean(x,y), result == 0)) {
      result = tile_landmass((int)cities[city].x,(int)cities[city].y);
      landmass = tile_landmass(x,y);
      if (result == landmass) {
        tile_set_visible(x,y,1 << (civ & 0x1f) & 0xff,1,1);
      }
    }
  }
  net_batch_flush();
  return;
}

/* 004bb570 auto */
void __thiscall wnd_move_to_rect(WndBase *self,iptr rect)

{
  wnd_obj_move_to_rect(self->native_wnd,(int *)rect);
  return;
}

/* 004c4240 auto */
void __cdecl popup_game_with_advance(const char *section,iptr advance,i32 sprite_flags)

{
  popup_text_with_advance((const char *)&str_game_7,section,0,advance,sprite_flags);
  return;
}

/* 004cc870 auto */
i32 __cdecl popup_game_with_improvement(const char *section,iptr improvement,i32 sprite_flags)

{
  i32 result;
  
  result = popup_text_with_improvement((const char *)&str_game_7,section,0,improvement,sprite_flags);
  return result;
}

/* 004cc8b0 auto */
i32 __cdecl popup_game_with_unit(const char *section,i32 dlg_flags,iptr unit)

{
  i32 result;
  
  result = popup_text_with_unit((const char *)&str_game_7,section,dlg_flags,unit);
  return result;
}

/* 004cff70 auto */
void __thiscall wnd_set_resize_border(WndBase *self,i32 width)

{
  wnd_obj_set_resize_border(self->native_wnd,width);
  return;
}

/* 004e01b0 auto */
void __cdecl menu_wonder_movies(void)

{
  iptr wonder_name;
  i32 flags;
  iptr wonder_id;
  Dialog dialog2;
  iptr wonder;
  iptr last_choice;
  i32 seh_handler;
  i8 *seh_scope;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  dialog_ctor(&dialog2,0x4000);
  eh_state = 0;
  last_choice = 0;
  while( true ) {
    dlg_reset(&dialog2,0x1001);
    dialog_set_width((DialogWindowView *)&dialog2,0x1b8);
    dialog_set_listbox((DialogTextView *)&dialog2,0x10,0x1b8,0);
    for (wonder = 0; wonder < 0x1c; wonder++) {
      flags = 0;
      wonder_id = wonder;
      wonder_name = (iptr)label_string(improvements[wonder + 0x27].name);
      dialog_add_option((DialogOptionList *)&dialog2,(const char *)wonder_name,wonder_id,flags);
    }
    dialog_set_default_choice((DialogOptionList *)&dialog2,last_choice);
    wonder = dlg_show_modal(&dialog2,0);
    last_choice = wonder;
    if (wonder < 0) break;
    wonder_show_movie(wonder);
  }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 004e02cb */ { dialog_dtor(&dialog2); }
  return;
}

/* 004e02ef auto */
void __cdecl ui_reset_window_layout(void)

{
  int left;
  int client_height;
  int chat_font_height;
  int parley_font_height;
  int height2;
  int width2;
  int view;
  
  wnd_maximize((WndBase *)((i8 *)&main_frame_wnd_block.main_frame_wnd));
  city_window_init_size();
  wnd_show_restored((WndBase *)((i8 *)&city_window_block.city_window_wnd));
  wnd_move_to_rect((WndBase *)((i8 *)&city_window_block.city_window_wnd),(iptr)&minimap_wnd_rect_block.city_wnd_rect);
  city_window_close();
  minimap_calc_rect();
  wnd_show_restored((WndBase *)((i8 *)&minimap_window_block.minimap_wnd));
  minimap_hidden = 0;
  wnd_move_to_rect((WndBase *)((i8 *)&minimap_window_block.minimap_wnd),(iptr)&minimap_wnd_rect_block.minimap_wnd_rect);
  wnd_repaint((SurfaceWindow *)((i8 *)&minimap_window_block.minimap_window));
  status_calc_wnd_rect();
  wnd_show_restored((WndBase *)((i8 *)&status_window_block.status_window_wnd));
  status_wnd_hidden = 0;
  wnd_move_to_rect((WndBase *)((i8 *)&status_window_block.status_window_wnd),(iptr)&minimap_wnd_rect_block.status_wnd_rect);
  wnd_repaint((SurfaceWindow *)((i8 *)&status_window_block.status_window));
  if (parley_wnd_block.large_layout == 0) {
    width2 = 0x208;
    height2 = 0x14f;
    parley_font_height = font_cached_height((GameFont *)((i8 *)&font_size20));
  }
  else {
    width2 = 800;
    height2 = 0x1cc;
    parley_font_height = font_cached_height((GameFont *)((i8 *)&font_size30));
  }
  parley_wnd_block.caption_height = panel_margin_y * 2 + panel_bevel_width * 2 + parley_font_height;
  width2 = width2 + (panel_padding_x + panel_margin_x) * 2 + 6;
  height2 = height2 + panel_margin_y * 2 + (int)parley_wnd_block.caption_height * 2 + 0xe;
  left = wnd_client_width((WndBase *)((i8 *)&main_frame_wnd_block.main_frame_wnd));
  left = (left >> 1) - (width2 >> 1);
  parley_wnd_block.wnd_x = left;
  client_height = wnd_client_height((WndBase *)((i8 *)&main_frame_wnd_block.main_frame_wnd));
  parley_wnd_block.wnd_y = (client_height >> 1) - (height2 >> 1);
  SetRect((LPRECT)parley_wnd_block.init_rect,left,(int)parley_wnd_block.wnd_y,left + width2,(int)parley_wnd_block.wnd_y + height2);
  wnd_move_to_rect((WndBase *)((i8 *)&parley_wnd_block.base.window_2),(iptr)(LPRECT)parley_wnd_block.init_rect);
  if (chat_wnd_block.large_layout == 0) {
    width2 = 0x208;
    height2 = 0x14f;
    chat_font_height = font_cached_height((GameFont *)((i8 *)&font_size20));
  }
  else {
    width2 = 800;
    height2 = 0x1cc;
    chat_font_height = font_cached_height((GameFont *)((i8 *)&font_size30));
  }
  chat_wnd_block.caption_height = panel_margin_y * 2 + panel_bevel_width * 2 + chat_font_height;
  width2 = width2 + (panel_padding_x + panel_margin_x) * 2 + 6;
  height2 = height2 + panel_margin_y * 2 + (int)chat_wnd_block.caption_height * 2 + 0xe;
  left = wnd_client_width((WndBase *)((i8 *)&main_frame_wnd_block.main_frame_wnd));
  left = (left >> 1) - (width2 >> 1);
  chat_wnd_block.wnd_x = left;
  client_height = wnd_client_height((WndBase *)((i8 *)&main_frame_wnd_block.main_frame_wnd));
  chat_wnd_block.wnd_y = (client_height >> 1) - (height2 >> 1);
  SetRect((LPRECT)chat_wnd_block.init_rect,left,(int)chat_wnd_block.wnd_y,left + width2,(int)chat_wnd_block.wnd_y + height2);
  wnd_move_to_rect((WndBase *)((i8 *)&chat_wnd_block.base.window_2),(iptr)(LPRECT)chat_wnd_block.init_rect);
  for (view = 1; view < 8; view++) {
    if (*(short *)(((i8 *)&map_views_block.map_view_open_flags) + view * 0x3f0) != 0) {
      *(i16 *)(((i8 *)&map_views_block.map_view_open_flags) + view * 0x3f0) = 0;
      wnd_destroy_with_surface((DibSurface *)(((i8 *)&map_views_block.map_views) + view * 0x3f0));
    }
  }
  mapview_calc_rect();
  wnd_show_restored((WndBase *)((i8 *)&map_views_block.map_view_wnds));
  wnd_move_to_rect((WndBase *)((i8 *)&map_views_block.map_view_wnds),(iptr)&map_view_saved_rects_block.map_view_saved_rects);
  wnd_repaint((SurfaceWindow *)((i8 *)&map_views_block.map_views));
  ui_flush_input();
  return;
}

/* 004e068d auto */
void __cdecl menu_load_game(void)

{
  byte music_was_on;
  int result;
  int view;
  
  mp_turn_timer_stop(1);
  city_window_close();
  parley_wnd_close();
  chat_wnd_close();
  pedia_close();
  picwnd_close((PictureWindowCore *)((i8 *)&advisor_window_block.advisor_window));
  picwnd_close((PictureWindowCore *)((i8 *)&casualty_window_block.casualty_window));
  music_was_on = (byte)game.game_options & 8;
  result = game_load_dialog(0,0,0);
  if (result == 0) {
    if (game.multiplayer != '\0') {
      load_game_pick_civ(1);
    }
    (*(byte *)&civ_saved_cursor_x_block.saved_turn_civ) = (byte)(*(i8 *)&human_civ);
    (*(byte *)&turn_resume_civ) = (byte)(*(i8 *)&human_civ);
    game.multiplayer = '\0';
    game.human_players = (u8)(1 << ((byte)(*(i8 *)&human_civ) & 0x1f));
    if (((byte)game.game_options & 8) == 0) {
      snd_cd_stop();
    }
    else {
      if (music_was_on == 0) {
        snd_cd_mci_stop();
        snd_cd_close();
        snd_cd_open();
        snd_cd_detect_layout();
      }
      snd_sync_music_option();
    }
    civ_check_password((*(i8 *)&human_civ));
    if (destroyed_civ_count_block.saved_layout_valid == 0) {
      ui_reset_window_layout();
      wnd_show_restored((WndBase *)((i8 *)&map_views_block.map_view_wnds));
      wnd_move_to_rect((WndBase *)((i8 *)&map_views_block.map_view_wnds),(iptr)&map_view_saved_rects_block.map_view_saved_rects);
      mapview_update_title((FrameWindow *)((i8 *)&map_views_block.map_views));
      wnd_repaint((SurfaceWindow *)((i8 *)&map_views_block.map_views));
      for (view = 1; view < 8; view++) {
        if (*(short *)(((i8 *)&map_views_block.map_view_open_flags) + view * 0x3f0) != 0) {
          mapview_create((ViewWindow *)(((i8 *)&map_views_block.map_views) + view * 0x3f0));
          wnd_move_to_rect
                    ((WndBase *)(((i8 *)&map_views_block.map_view_wnds) + view * 0x3f0),
                     (iptr)(((i8 *)&map_view_saved_rects_block.map_view_saved_rects) + view * 0x10));
          mapview_update_title((FrameWindow *)(((i8 *)&map_views_block.map_views) + view * 0x3f0));
          wnd_repaint((SurfaceWindow *)(((i8 *)&map_views_block.map_views) + view * 0x3f0));
        }
      }
    }
    else {
      wnd_maximize((WndBase *)((i8 *)&main_frame_wnd_block.main_frame_wnd));
      wnd_show_restored((WndBase *)((i8 *)&city_window_block.city_window_wnd));
      wnd_move_to_rect((WndBase *)((i8 *)&city_window_block.city_window_wnd),(iptr)&minimap_wnd_rect_block.city_wnd_rect);
      city_window_close();
      wnd_show_restored((WndBase *)((i8 *)&minimap_window_block.minimap_wnd));
      minimap_hidden = 0;
      wnd_move_to_rect((WndBase *)((i8 *)&minimap_window_block.minimap_wnd),(iptr)&minimap_wnd_rect_block.minimap_wnd_rect);
      wnd_repaint((SurfaceWindow *)((i8 *)&minimap_window_block.minimap_window));
      wnd_show_restored((WndBase *)((i8 *)&status_window_block.status_window_wnd));
      status_wnd_hidden = 0;
      wnd_move_to_rect((WndBase *)((i8 *)&status_window_block.status_window_wnd),(iptr)&minimap_wnd_rect_block.status_wnd_rect);
      wnd_repaint((SurfaceWindow *)((i8 *)&status_window_block.status_window));
      wnd_show_restored((WndBase *)((i8 *)&map_views_block.map_view_wnds));
      wnd_move_to_rect((WndBase *)((i8 *)&map_views_block.map_view_wnds),(iptr)&map_view_saved_rects_block.map_view_saved_rects);
      mapview_update_title((FrameWindow *)((i8 *)&map_views_block.map_views));
      wnd_repaint((SurfaceWindow *)((i8 *)&map_views_block.map_views));
      for (view = 1; view < 8; view++) {
        if (*(short *)(((i8 *)&map_views_block.map_view_open_flags) + view * 0x3f0) != 0) {
          mapview_create((ViewWindow *)(((i8 *)&map_views_block.map_views) + view * 0x3f0));
          wnd_move_to_rect
                    ((WndBase *)(((i8 *)&map_views_block.map_view_wnds) + view * 0x3f0),
                     (iptr)(((i8 *)&map_view_saved_rects_block.map_view_saved_rects) + view * 0x10));
          mapview_update_title((FrameWindow *)(((i8 *)&map_views_block.map_views) + view * 0x3f0));
          wnd_repaint((SurfaceWindow *)(((i8 *)&map_views_block.map_views) + view * 0x3f0));
        }
      }
      wnd_repaint((SurfaceWindow *)((i8 *)&minimap_window_block.minimap_window));
    }
    moving_units_mode = 0;
    wnd_repaint((SurfaceWindow *)((i8 *)&status_window_block.status_window));
    ui_redraw_all_maps(1);
    ui_focus_active_unit(0);
    menu_update_states();
    pedia_load_indexes((DocumentWindow *)((i8 *)&pedia_window_block.pedia_window));
    ui_flush_input();
    if ((game.multiplayer != '\0') && (civ_saved_cursor_x_block.mp_turn_time_limit_ms != 0)) {
      mp_turn_timer_start(1);
    }
  }
  else {
    game.multiplayer = '\0';
    mp_turn_timer_resume(1);
  }
  return;
}

/* 004e0a8c auto */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __cdecl dlg_check_set_bool(i32 index,int value)

{
  dlg_check_set(index,(uint)(value != 0));
  return;
}

/* 004e0ab0 auto */
void __cdecl menu_game_options(void)

{
  uint music_was_on;
  int result;
  
  music_was_on = game.game_options & 8;
  dlg_checks_clear();
  dlg_check_set_bool(0,game.game_options & 0x10);
  dlg_check_set_bool(1,game.game_options & 8);
  dlg_check_set_bool(2,game.game_options & 0x4000);
  dlg_check_set_bool(3,game.game_options & 0x2000);
  dlg_check_set_bool(4,game.game_options & 0x1000);
  dlg_check_set_bool(5,game.game_options & 0x800);
  dlg_check_set_bool(6,game.game_options & 0x400);
  dlg_check_set_bool(7,game.game_options & 0x200);
  dlg_check_set_bool(8,game.game_options & 0x100);
  dlg_check_set_bool(9,game.game_options & 0x80);
  dlg_check_set_bool(10,game.game_options & 0x40);
  text_set_string_arg(0,(const char *)str_ptr_5_4_0f_multiplayer_26_march_99);
  crt_strcat(((i8 *)&minimap_window_block.text_string_args),((i8 *)&game_options_version_sep_str));
  crt_strcat(((i8 *)&minimap_window_block.text_string_args),(*(i8 * *)str_ptr_5_4_0f_multiplayer_26_march_99_rest));
  result = popup_game_flags((const char *)&str_gameoptions,1);
  if (result == 0) {
    game.game_options = game.game_options & 0xffff8027;
    result = dlg_check_get(0);
    if (result != 0) {
      game.game_options = game.game_options | 0x10;
    }
    result = dlg_check_get(1);
    if (result == 0) {
      snd_cd_stop();
    }
    else {
      game.game_options = game.game_options | 8;
      if (music_was_on == 0) {
        snd_cd_mci_stop();
        snd_cd_close();
        snd_cd_open();
        snd_cd_detect_layout();
      }
      snd_sync_music_option();
    }
    result = dlg_check_get(2);
    if (result != 0) {
      game.game_options = game.game_options | 0x4000;
    }
    result = dlg_check_get(3);
    if (result != 0) {
      game.game_options = game.game_options | 0x2000;
    }
    result = dlg_check_get(4);
    if (result != 0) {
      game.game_options = game.game_options | 0x1000;
    }
    result = dlg_check_get(5);
    if (result != 0) {
      game.game_options = game.game_options | 0x800;
    }
    result = dlg_check_get(6);
    if (result != 0) {
      game.game_options = game.game_options | 0x400;
    }
    result = dlg_check_get(7);
    if (result != 0) {
      game.game_options = game.game_options | 0x200;
    }
    result = dlg_check_get(8);
    if (result != 0) {
      game.game_options = game.game_options | 0x100;
    }
    result = dlg_check_get(9);
    if (result != 0) {
      game.game_options = game.game_options | 0x80;
    }
    result = dlg_check_get(10);
    if (result != 0) {
      game.game_options = game.game_options | 0x40;
    }
    prefs_game_rules_block.prefs_game_options = game.game_options;
    prefs_save_civ2dat();
  }
  return;
}

/* 004e0d71 auto */
void __cdecl menu_graphic_options(void)

{
  uint hires_was_on;
  int result;
  
  hires_was_on = game.game_options & 0x200000;
  dlg_checks_clear();
  dlg_check_set_bool(0,game.game_options & 0x20000);
  dlg_check_set_bool(1,game.game_options & 0x40000);
  dlg_check_set_bool(2,game.game_options & 0x200000);
  dlg_check_set_bool(3,game.game_options & 0x80000);
  dlg_check_set_bool(4,game.game_options & 0x100000);
  dlg_check_set_bool(5,game.game_options & 0x10000);
  result = popup_game_flags((const char *)&str_graphicoptions,1);
  if (result == 0) {
    game.game_options = game.game_options & 0xffc0ffff;
    result = dlg_check_get(0);
    if (result != 0) {
      game.game_options = game.game_options | 0x20000;
    }
    result = dlg_check_get(1);
    if (result != 0) {
      game.game_options = game.game_options | 0x40000;
    }
    result = dlg_check_get(2);
    if (result != 0) {
      if (hires_was_on == 0) {
        result = mem_check_available(0x800000);
        if (result == 0) {
          popup_game((const char *)&str_lowmemory);
        }
      }
      game.game_options = game.game_options | 0x200000;
    }
    result = dlg_check_get(3);
    if (result != 0) {
      game.game_options = game.game_options | 0x80000;
    }
    result = dlg_check_get(4);
    if (result != 0) {
      game.game_options = game.game_options | 0x100000;
    }
    result = dlg_check_get(5);
    if (result != 0) {
      game.game_options = game.game_options | 0x10000;
    }
    prefs_game_rules_block.prefs_game_options = game.game_options;
    prefs_save_civ2dat();
  }
  return;
}

/* 004e0f18 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl menu_multiplayer_options(void)

{
  int result;
  int choice;
  
  dlg_checks_clear();
  dlg_check_set_bool(0,(int)(short)(*(ushort *)&prefs_main_menu_choice_block.prefs_clear_chat_on_new_game));
  dlg_check_set_bool(1,(int)(short)(*(ushort *)&prefs_main_menu_choice_block.prefs_clear_chat_on_boot));
  if (net_session_block.net_host_flag != '\0') {
    dlg_check_set_bool(2,(int)(short)(*(ushort *)&civ_saved_cursor_x_block.mp_double_production));
    dlg_check_set_bool(3,(int)(short)(*(ushort *)&civ_saved_cursor_x_block.mp_double_moves));
  }
  if (((game.multiplayer < 3) || (net_session_block.net_host_flag == '\0')) && (2 < game.multiplayer)) {
    choice = popup_game_flags((const char *)&str_multiplayeroptions2,1);
  }
  else {
    choice = popup_game_flags((const char *)&str_multiplayeroptions,1);
  }
  if (choice == 0) {
    result = dlg_check_get(0);
    (*(ushort *)&prefs_main_menu_choice_block.prefs_clear_chat_on_new_game) = (ushort)(result != 0);
    result = dlg_check_get(1);
    (*(ushort *)&prefs_main_menu_choice_block.prefs_clear_chat_on_boot) = (ushort)(result != 0);
    prefs_save_civ2dat();
    if (((2 < game.multiplayer) && (net_session_block.net_host_flag != '\0')) || (game.multiplayer < 3)) {
      result = dlg_check_get(2);
      (*(ushort *)&prefs_main_menu_choice_block.prefs_mp_double_production) = (ushort)(result != 0);
      result = dlg_check_get(3);
      (*(ushort *)&prefs_main_menu_choice_block.prefs_mp_double_moves) = (ushort)(result != 0);
      if (((*(ushort *)&civ_saved_cursor_x_block.mp_double_production) != (*(ushort *)&prefs_main_menu_choice_block.prefs_mp_double_production)) || ((*(ushort *)&civ_saved_cursor_x_block.mp_double_moves) != (*(ushort *)&prefs_main_menu_choice_block.prefs_mp_double_moves))) {
        if ((2 < game.multiplayer) && (1 < net_session_block.net_player_count[0])) {
          crt_strcpy(((i8 *)&minimap_window_block.text_string_args),((i8 *)&net_session_block.net_local_player_name));
          str_clear((char *)&minimap_window_block.text_string_arg1);
          str_append_label((iptr)&minimap_window_block.text_string_arg1,0x350 - (uint)((*(ushort *)&prefs_main_menu_choice_block.prefs_mp_double_production) == 0));
          crt_strcat(((i8 *)&minimap_window_block.text_string_arg1),((i8 *)&mp_options_vote_sep_str));
          str_append_label((iptr)&minimap_window_block.text_string_arg1,0x352 - (uint)((*(ushort *)&prefs_main_menu_choice_block.prefs_mp_double_moves) == 0));
          net_session_block.net_vote_replies_pending = net_session_block.net_player_count[0] - 1;
          net_session_block.net_vote_status = 0;
          net_send_text_args(0x43,0xff,2,0,0,0);
          dlg_pending_idle_callback = ((i8 *)net_vote_wait_idle_cb);
          dialog_title_font_obj_block.dialog_timeout_start_i32 = timer_ticks();
          result = popup_game_sprite_flags((const char *)&str_pmchangeserver,0x2000001,(iptr)&popup_info_icon_sprite,0);
          if (((result < 0) || (net_session_block.net_vote_status == -1)) || (net_session_block.net_vote_replies_pending != 0)) {
            (*(ushort *)&prefs_main_menu_choice_block.prefs_mp_double_production) = (*(ushort *)&civ_saved_cursor_x_block.mp_double_production);
            (*(ushort *)&prefs_main_menu_choice_block.prefs_mp_double_moves) = (*(ushort *)&civ_saved_cursor_x_block.mp_double_moves);
            net_send_text_args(0x44,0xff,0,0,0,0);
            popup_game_with_sprite((const char *)&str_pmchangeno,(iptr)&popup_info_icon_sprite,0);
            return;
          }
        }
        (*(ushort *)&civ_saved_cursor_x_block.mp_double_production) = (*(ushort *)&prefs_main_menu_choice_block.prefs_mp_double_production);
        (*(ushort *)&civ_saved_cursor_x_block.mp_double_moves) = (*(ushort *)&prefs_main_menu_choice_block.prefs_mp_double_moves);
        rules_apply_double_moves();
        if ((2 < game.multiplayer) && (1 < net_session_block.net_player_count[0])) {
          net_send_message(0x1b,0xff,0,0,0,0,0,0,0,0);
          net_send_message(0x33,0xff,(int)(short)(*(ushort *)&civ_saved_cursor_x_block.mp_double_production),(int)(short)(*(ushort *)&civ_saved_cursor_x_block.mp_double_moves),
                             (int)civ_saved_cursor_x_block.mp_simultaneous_setting,0,0,0,0,0);
          net_send_text_args(0x45,0xff,0,0,0,0);
          popup_game_with_sprite((const char *)&str_pmchangeyes,(iptr)&popup_info_icon_sprite,0);
        }
      }
    }
  }
  return;
}

/* 004e1452 auto */
void __cdecl menu_message_options(void)

{
  int result;
  
  dlg_checks_clear();
  dlg_check_set(0,~(uint)game.message_options & 1);
  dlg_check_set(1,(uint)((game.message_options & 2) == 0));
  dlg_check_set(2,(uint)((game.message_options & 4) == 0));
  dlg_check_set(3,(uint)((game.message_options & 8) == 0));
  dlg_check_set(4,(uint)((game.message_options & 0x10) == 0));
  dlg_check_set(5,(uint)((game.message_options & 0x20) == 0));
  dlg_check_set(6,(uint)((game.message_options & 0x40) == 0));
  dlg_check_set(7,(uint)((game.message_options & 0x80) == 0));
  dlg_check_set(8,(uint)((game.message_options & 0x100) == 0));
  dlg_check_set(9,(uint)((game.message_options & 0x200) == 0));
  dlg_check_set(10,(uint)((game.message_options & 0x400) == 0));
  result = popup_game_flags((const char *)&str_messageoptions,1);
  if (result == 0) {
    game.message_options = 0;
    result = dlg_check_get(0);
    if (result == 0) {
      game.message_options = game.message_options | 1;
    }
    result = dlg_check_get(1);
    if (result == 0) {
      game.message_options = game.message_options | 2;
    }
    result = dlg_check_get(2);
    if (result == 0) {
      game.message_options = game.message_options | 4;
    }
    result = dlg_check_get(3);
    if (result == 0) {
      game.message_options = game.message_options | 8;
    }
    result = dlg_check_get(4);
    if (result == 0) {
      game.message_options = game.message_options | 0x10;
    }
    result = dlg_check_get(5);
    if (result == 0) {
      game.message_options = game.message_options | 0x20;
    }
    result = dlg_check_get(6);
    if (result == 0) {
      game.message_options = game.message_options | 0x40;
    }
    result = dlg_check_get(7);
    if (result == 0) {
      game.message_options = game.message_options | 0x80;
    }
    result = dlg_check_get(8);
    if (result == 0) {
      game.message_options = game.message_options | 0x100;
    }
    result = dlg_check_get(9);
    if (result == 0) {
      game.message_options = game.message_options | 0x200;
    }
    result = dlg_check_get(10);
    if (result == 0) {
      game.message_options = game.message_options | 0x400;
    }
    prefs_game_rules_block.prefs_message_options = game.message_options;
    prefs_save_civ2dat();
  }
  return;
}

/* 004e2597 auto */
void __cdecl menu_show_hidden_terrain(void)

{
  unit_blink_active = 0;
  map_show_hidden_terrain = 1;
  map_redraw_all_views(human_civ[0],1);
  popup_game((const char *)&str_hiddenterrain);
  map_show_hidden_terrain = 0;
  map_redraw_all_views(human_civ[0],1);
  return;
}

/* 004e25ef auto */
void __cdecl menu_select_music(void)

{
  int choice;
  Dialog dialog2;
  int track_count;
  int tries;
  i32 seh_handler;
  i8 *seh_scope;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  dialog_ctor(&dialog2,0x4000);
  eh_state = 0;
  tries = 0;
  while (tries < 5) {
    tries++;
    track_count = snd_cd_get_track_count();
    if ((((track_count == 0x18) || (track_count == 0x12)) || (track_count == 0xc)) || (track_count == 10))
    break;
    if (track_count == -1) {
      snd_cd_close();
    }
    Sleep(200);
  }
  if (track_count == -1) {
    popup_game((const char *)&str_nopickmusicnew);
    eh_state = 0xffffffff;
    /* inlined unwind funclet 004e27df */ { dialog_dtor(&dialog2); }
  }
  else {
    if (track_count == 0x18) {
      dlg_load_game_section(&dialog2,(const char *)&str_pickmusicfanworlds,1);
    }
    else if (track_count == 0x12) {
      dlg_load_game_section(&dialog2,(const char *)&str_pickmusicscenario,1);
    }
    else if (track_count == 0xc) {
      dlg_load_game_section(&dialog2,(const char *)&str_pickmusicgold,1);
    }
    else {
      if (track_count != 10) {
        popup_game((const char *)&str_nopickmusicnew_2);
        eh_state = 0xffffffff;
        /* inlined unwind funclet 004e27df */ { dialog_dtor(&dialog2); }
        goto done;
      }
      dlg_load_game_section(&dialog2,(const char *)&str_pickmusic,1);
    }
    if (1 < (*(int *)&cd_music_current_track)) {
      dialog_set_default_choice((DialogOptionList *)&dialog2,(*(int *)&cd_music_current_track) - 2);
    }
    choice = dlg_show_modal(&dialog2,0);
    if (choice < 0) {
      eh_state = 0xffffffff;
      /* inlined unwind funclet 004e27df */ { dialog_dtor(&dialog2); }
    }
    else {
      music_play_track(choice + 2,1);
      eh_state = 0xffffffff;
      /* inlined unwind funclet 004e27df */ { dialog_dtor(&dialog2); }
    }
  }
done:
  return;
}

/* 004e2803 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl menu_command(i32 menu,int cmd)

{
  SHORT shift_state;
  int result;
  
  result = XD_InFlushSendBuffer();
  if ((((((((result == 0) && (net_session_block.unit_create_busy == 0)) && (net_session_block.unit_delete_busy == 0)) &&
         ((net_session_block.city_create_busy == 0 && (net_session_block.city_delete_busy == 0)))) && (net_session_block.net_lock_map_busy == 0)) &&
       (((net_session_block.net_unlock_map_busy == 0 && (net_session_block.unit_stack_unlink_busy == 0)) &&
        ((net_session_block.unit_stack_link_busy == 0 && (((net_session_block.unit_stack_bottom_busy == 0 && (net_session_block.unit_relocate_busy == 0)) && (net_session_block.city_acquire_wonder_busy == 0)))
         ))))) && ((net_session_block.civ_eliminate_busy == 0 && (net_session_block.civ_create_busy == 0)))) &&
     ((net_session_block.civ_check_destroyed_busy == 0 &&
      (((net_session_block.unit_gather_cargo_busy == 0 && (net_session_block.unit_lift_off_map_busy == 0)) && ((net_session_block.unit_delete_cargo_busy == 0 && (net_session_block.unit_destroy_redraw_busy == 0)))))
      ))) {
    if (city_turn_processing == 0) {
      result = ui_paradrop_cursor_active();
      if ((result == 0) || (mapviews_reset_cursor(), cmd != 0x441)) {
        if (cmd < 0x111) {
          if (cmd == 0x110) {
            game_save_dialog(0);
          }
          else {
            switch(cmd) {
            case 0x101:
              menu_game_options();
              break;
            case 0x102:
              menu_graphic_options();
              break;
            case 0x103:
              menu_message_options();
              break;
            case 0x104:
              menu_multiplayer_options();
              break;
            case 0x105:
              game_profile_popup(0);
              break;
            case 0x106:
              menu_select_music();
            }
          }
        }
        else if (cmd < 0x131) {
          if (cmd == 0x130) {
            game_join_dialog();
          }
          else if (cmd == 0x120) {
            menu_load_game();
          }
        }
        else if (cmd < 0x1f1) {
          if (cmd == 0x1f0) {
            game_quit_or_retire(1);
          }
          else if (cmd == 0x131) {
            civ_change_password_dialog(human_civ[0]);
          }
          else if (cmd == 0x132) {
            mp_cmd_change_timer();
          }
        }
        else if (cmd < 0x202) {
          if (cmd == 0x201) {
            taxrate_dialog_show(human_civ[0]);
          }
          else if (cmd == 0x1f1) {
            game_quit_or_retire(0);
          }
          else if ((cmd == 0x1f2) && (game.multiplayer == 1)) {
            result = popup_game_with_sprite((const char *)&str_reallyquit_4,(iptr)&popup_info_icon_sprite,0);
            if (result == 0) {
              return;
            }
            snd_cd_stop();
            map_display_disable();
            return;
          }
        }
        else if (cmd < 0x211) {
          if (cmd == 0x210) {
            menu_find_city();
          }
          else if (cmd == 0x205) {
            throneroom_show(human_civ[0]);
          }
        }
        else if (cmd < 0x302) {
          if (cmd == 0x301) {
            ui_focus_active_unit(1);
          }
          else if (cmd == 0x220) {
            menu_revolution();
          }
        }
        else if (cmd < 0x311) {
          if (cmd == 0x310) {
            if (map_views_block.mapview_zoom[0] < 8) {
              map_views_block.mapview_zoom[0]++;
              mapview_redraw((ViewWindow *)((i8 *)&map_views_block.map_views),human_civ[0],1);
            }
          }
          else if (cmd == 0x302) {
            ui_redraw_all_maps(0);
          }
        }
        else if (cmd < 0x321) {
          if (cmd == 800) {
            map_views_block.mapview_zoom[0] = 8;
            mapview_redraw((ViewWindow *)((i8 *)&map_views_block.map_views),human_civ[0],1);
          }
          else if ((cmd == 0x311) && (-7 < map_views_block.mapview_zoom[0])) {
            map_views_block.mapview_zoom[0]--;
            mapview_redraw((ViewWindow *)((i8 *)&map_views_block.map_views),human_civ[0],1);
          }
        }
        else if (cmd < 0x331) {
          if (cmd == 0x330) {
            menu_show_hidden_terrain();
          }
          else {
            switch(cmd) {
            case 0x321:
              map_views_block.mapview_zoom[0] = 0;
              map_views_block.map_view_center_x[0] = map_cursor_x[0];
              map_views_block.mapview_center_y[0] = map_cursor_y[0];
              mapview_redraw((ViewWindow *)((i8 *)&map_views_block.map_views),human_civ[0],1);
              break;
            case 0x322:
              map_views_block.mapview_zoom[0] = -3;
              mapview_redraw((ViewWindow *)((i8 *)&map_views_block.map_views),human_civ[0],1);
              break;
            case 0x324:
              map_views_block.mapview_zoom[0] = -7;
              mapview_redraw((ViewWindow *)((i8 *)&map_views_block.map_views),human_civ[0],1);
              break;
            case 0x327:
              game.game_options = game.game_options ^ 0x20;
              menu_set_item_checked
                        ((GameMenu *)((i8 *)&main_menu_block.main_menu),0x327,(game.game_options & 0x20) >> 5);
              map_redraw_all_views(human_civ[0],1);
              prefs_game_rules_block.prefs_game_options = game.game_options;
              prefs_save_civ2dat();
              break;
            case 0x328:
              ui_reset_window_layout();
            }
          }
        }
        else if (cmd < 0x402) {
          if (cmd == 0x401) {
            unit_cmd_build_city();
          }
          else if (cmd == 0x340) {
            mapview_center_on
                      ((ViewWindow *)((i8 *)&map_views_block.map_views),(int)map_cursor_x[0],(int)map_cursor_y[0]);
          }
        }
        else if (cmd < 0x431) {
          if (cmd == 0x430) {
            unit_cmd_unload();
          }
          else {
            switch(cmd) {
            case 0x410:
              unit_cmd_terraform(5);
              break;
            case 0x411:
              unit_cmd_terraform(6);
              break;
            case 0x412:
              unit_cmd_terraform(7);
              break;
            case 0x413:
              unit_cmd_terraform(8);
              break;
            case 0x417:
              unit_cmd_terraform(10);
              break;
            case 0x418:
              unit_cmd_terraform(4);
              break;
            case 0x41b:
              unit_cmd_automate();
              break;
            case 0x420:
              unit_cmd_terraform(9);
              break;
            case 0x421:
              unit_cmd_pillage();
            }
          }
        }
        else if (cmd < 0x451) {
          if (cmd == 0x450) {
            unit_cmd_fortify();
          }
          else {
            switch(cmd) {
            case 0x440:
              unit_cmd_goto_city();
              break;
            case 0x441:
              unit_cmd_paradrop();
              break;
            case 0x442:
              unit_cmd_airlift();
              break;
            case 0x445:
              unit_cmd_home_city();
            }
          }
        }
        else if (cmd < 0x461) {
          if (cmd == 0x460) {
            unit_cmd_disband();
          }
          else if (cmd == 0x451) {
            unit_cmd_sleep();
          }
        }
        else if (cmd < 0x471) {
          if (cmd == 0x470) {
            unit_cmd_wait();
          }
          else if (cmd == 0x468) {
            ui_pick_unit_from_stack();
          }
        }
        else if (cmd < 0x491) {
          if (cmd == 0x490) {
            cmd_end_player_turn();
          }
          else if (cmd == 0x480) {
            cmd_unit_skip_turn();
          }
        }
        else if (cmd < 0x602) {
          if (cmd == 0x601) {
            shift_state = GetAsyncKeyState(0x10);
            if ((((char)((ushort)shift_state >> 8) == '\0') || ((game.game_options & 0x8000) == 0)) ||
               (game.multiplayer != '\0')) {
              wonders_report_show(human_civ[0]);
            }
            else {
              menu_wonder_movies();
            }
          }
          else {
            switch(cmd) {
            case 0x500:
              if ((((game.game_options & 0x8000) == 0) || (game.multiplayer != '\0')) ||
                 (shift_state = GetAsyncKeyState(0x10), (char)((ushort)shift_state >> 8) == '\0')) {
                council_show(human_civ[0],0);
              }
              else {
                council_show(human_civ[0],1);
              }
              break;
            case 0x501:
              city_status_show(human_civ[0]);
              break;
            case 0x502:
              defense_minister_show(human_civ[0]);
              break;
            case 0x503:
              foreign_minister_show(human_civ[0]);
              break;
            case 0x504:
              attitude_advisor_show(human_civ[0]);
              break;
            case 0x505:
              trade_advisor_show(human_civ[0]);
              break;
            case 0x506:
              science_advisor_show(human_civ[0]);
              break;
            case 0x507:
              parley_wnd_open(&chat_wnd_block,0,4);
              break;
            case 0x508:
              casualty_timeline_show(human_civ[0]);
            }
          }
        }
        else if (cmd < 0x702) {
          if (cmd == 0x701) {
            if ((game.multiplayer == '\0') || (mp_cheat_menu_allowed[0] != 0)) {
              cheat_toggle_mode();
            }
          }
          else {
            switch(cmd) {
            case 0x602:
              shift_state = GetAsyncKeyState(0x10);
              if ((((char)((ushort)shift_state >> 8) == '\0') || ((game.game_options & 0x8000) == 0)) ||
                 (game.multiplayer != '\0')) {
                top_cities_show(human_civ[0]);
              }
              else {
                endgame_defeat_movie(human_civ[0]);
              }
              break;
            case 0x603:
              shift_state = GetAsyncKeyState(0x10);
              if ((((char)((ushort)shift_state >> 8) == '\0') || ((game.game_options & 0x8000) == 0)) ||
                 (game.multiplayer != '\0')) {
                civ_score_window_show(human_civ[0]);
                if (game.reveal_map != '\0') {
                  civ_rating_window_show(human_civ[0]);
                  powergraph_show();
                }
              }
              else {
                destroyed_civs_show(human_civ[0]);
              }
              break;
            case 0x605:
              shift_state = GetAsyncKeyState(0x10);
              if ((((char)((ushort)shift_state >> 8) == '\0') || ((game.game_options & 0x8000) == 0)) ||
                 (game.multiplayer != '\0')) {
                demographics_show(human_civ[0]);
              }
              else {
                endgame_spaceship_arrival(-(human_civ[0] + 1U & 7));
              }
              break;
            case 0x606:
              shift_state = GetAsyncKeyState(0x10);
              if ((((char)((ushort)shift_state >> 8) == '\0') || ((game.game_options & 0x8000) == 0)) ||
                 (game.multiplayer != '\0')) {
                spaceship_select_view_dialog(human_civ[0]);
              }
              else {
                endgame_spaceship_arrival(human_civ[0]);
              }
            }
          }
        }
        else if (cmd < 0x722) {
          if (cmd == 0x721) {
            if (((game.game_options & 0x8000) != 0) && (game.multiplayer == '\0')) {
              cheat_set_game_year();
            }
          }
          else if (cmd == 0x711) {
            if (((game.game_options & 0x8000) != 0) && (game.multiplayer == '\0')) {
              cheat_create_unit();
            }
          }
          else if (cmd == 0x712) {
            if (((game.game_options & 0x8000) != 0) && (game.multiplayer == '\0')) {
              cheat_reveal_map();
            }
          }
          else if (((cmd == 0x713) && ((game.game_options & 0x8000) != 0)) &&
                  (game.multiplayer == '\0')) {
            cheat_set_human_player();
          }
        }
        else if (cmd < 0x732) {
          if (cmd == 0x731) {
            if (((game.game_options & 0x8000) != 0) && (game.multiplayer == '\0')) {
              cheat_tech_advance();
            }
          }
          else if (((cmd == 0x722) && ((game.game_options & 0x8000) != 0)) &&
                  (game.multiplayer == '\0')) {
            cheat_kill_civ();
          }
        }
        else if (cmd < 0x741) {
          if (cmd == 0x740) {
            if (((game.game_options & 0x8000) != 0) && (game.multiplayer == '\0')) {
              cheat_force_government();
            }
          }
          else if (((cmd == 0x732) && ((game.game_options & 0x8000) != 0)) &&
                  (game.multiplayer == '\0')) {
            cheat_edit_technologies();
          }
        }
        else if (cmd < 0x751) {
          if (cmd == 0x750) {
            if (((game.game_options & 0x8000) != 0) && (game.multiplayer == '\0')) {
              cheat_destroy_units_at_cursor();
              ui_focus_active_unit(0);
            }
          }
          else if (((cmd == 0x748) && ((game.game_options & 0x8000) != 0)) &&
                  (game.multiplayer == '\0')) {
            cheat_terrain_saved_bits = 0xffffffff;
            cheat_change_terrain();
          }
        }
        else if (cmd < 0x756) {
          if (cmd == 0x755) {
            if (((game.game_options & 0x8000) != 0) && (game.multiplayer == '\0')) {
              cheat_edit_unit();
            }
          }
          else if (((cmd == 0x752) && ((game.game_options & 0x8000) != 0)) &&
                  (game.multiplayer == '\0')) {
            cheat_change_money();
          }
        }
        else if (cmd < 0x766) {
          if (cmd == 0x765) {
            if (((game.game_options & 0x8000) != 0) && (game.multiplayer == '\0')) {
              cheat_edit_king();
            }
          }
          else if (((cmd == 0x760) && ((game.game_options & 0x8000) != 0)) &&
                  (game.multiplayer == '\0')) {
            cheat_edit_city();
          }
        }
        else if (cmd < 0x771) {
          if (cmd == 0x770) {
            if (((game.game_options & 0x8000) != 0) && (game.multiplayer == '\0')) {
              cheat_save_as_scenario();
            }
          }
          else if (((cmd == 0x768) && ((game.game_options & 0x8000) != 0)) &&
                  (game.multiplayer == '\0')) {
            cheat_scenario_params();
          }
        }
        else if (cmd < 0x902) {
          if (cmd == 0x901) {
            pedia_open_category((MediaWindow *)((i8 *)&pedia_window_block.pedia_window),1,1);
          }
          else {
            switch(cmd) {
            case 0x801:
              editor_toggle_scenario_flag();
              break;
            case 0x802:
              tech_editor_run();
              break;
            case 0x803:
              city_editor_run();
              break;
            case 0x804:
              cosmic_editor_run();
              break;
            case 0x805:
              impr_editor_run();
              break;
            case 0x806:
              terrain_editor_open();
              break;
            case 0x807:
              tribe_editor_run();
              break;
            case 0x808:
              unit_editor_run();
              break;
            case 0x809:
              events_editor_open();
            }
          }
        }
        else {
          switch(cmd) {
          case 0x903:
            pedia_open_category((MediaWindow *)((i8 *)&pedia_window_block.pedia_window),2,1);
            break;
          case 0x905:
            pedia_open_category((MediaWindow *)((i8 *)&pedia_window_block.pedia_window),3,1);
            break;
          case 0x907:
            pedia_open_category((MediaWindow *)((i8 *)&pedia_window_block.pedia_window),4,1);
            break;
          case 0x909:
            pedia_open_category((MediaWindow *)((i8 *)&pedia_window_block.pedia_window),6,1);
            break;
          case 0x90b:
            pedia_open_category((MediaWindow *)((i8 *)&pedia_window_block.pedia_window),5,1);
            break;
          case 0x90d:
            if ((cmd == 0x905) &&
               (shift_state = GetAsyncKeyState(0x10), (char)((ushort)shift_state >> 8) != '\0')) {
              menu_wonder_movies();
            }
            else {
              pedia_open_category((MediaWindow *)((i8 *)&pedia_window_block.pedia_window),7,1);
            }
            break;
          case 0x9f0:
            if (game.multiplayer < 3) {
              result = popup_game_flags((const char *)&str_newcredits_2,1);
              if (-1 < result) {
                credits_show(result);
              }
              text_close_file();
            }
          }
        }
      }
    }
    else {
      city_window_modal_notice();
    }
  }
  else {
    dbg_log((const char *)&str_mainmenu_menu_exec_blocked_by_xd_flushse);
    net_session_block.blocked_input_kind = 5;
    net_session_block.blocked_input_arg1_i32 = menu;
    net_session_block.blocked_input_arg2_i32 = cmd;
  }
  return;
}

/* 004e3a86 auto */
void __cdecl menu_build_main(void)

{
  int status;
  i32 item_arg;
  iptr label;
  i32 editor_disabled;
  i32 editor_checked;
  i32 cheat_checked;
  i32 cheat_disabled;
  
  menu_reset((GameMenu *)((i8 *)&main_menu_block.main_menu),0x1bbc);
  status = text_open_section((const char *)&str_menu,(const char *)&str_game_5);
  if (status == 0) {
    item_arg = (i32)text_read_line(1);
    menu_add_menu((GameMenu *)((i8 *)&main_menu_block.main_menu),1,(char *)item_arg);
    item_arg = 0;
    label = (iptr)text_read_line(1);
    menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),1,0x101,(const char *)label,item_arg);
    item_arg = 0;
    label = (iptr)text_read_line(1);
    menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),1,0x102,(const char *)label,item_arg);
    item_arg = 0;
    label = (iptr)text_read_line(1);
    menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),1,0x103,(const char *)label,item_arg);
    item_arg = 0;
    label = (iptr)text_read_line(1);
    menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),1,0x104,(const char *)label,item_arg);
    item_arg = 0;
    label = (iptr)text_read_line(1);
    menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),1,0x105,(const char *)label,item_arg);
    menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),1,0,0,0);
    item_arg = 0;
    label = (iptr)text_read_line(1);
    menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),1,0x106,(const char *)label,item_arg);
    menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),1,0,0,0);
    item_arg = 0;
    label = (iptr)text_read_line(1);
    menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),1,0x110,(const char *)label,item_arg);
    item_arg = 0;
    label = (iptr)text_read_line(1);
    menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),1,0x120,(const char *)label,item_arg);
    item_arg = 0;
    label = (iptr)text_read_line(1);
    menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),1,0x130,(const char *)label,item_arg);
    menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),1,0,0,0);
    item_arg = 0;
    label = (iptr)text_read_line(1);
    menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),1,0x131,(const char *)label,item_arg);
    item_arg = 0;
    label = (iptr)text_read_line(1);
    menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),1,0x132,(const char *)label,item_arg);
    menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),1,0,0,0);
    item_arg = 0;
    label = (iptr)text_read_line(1);
    menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),1,0x1f0,(const char *)label,item_arg);
    item_arg = 0;
    label = (iptr)text_read_line(1);
    menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),1,0x1f1,(const char *)label,item_arg);
    status = text_open_section(0,(const char *)&str_kingdom);
    if (status == 0) {
      item_arg = (i32)text_read_line(1);
      menu_add_menu((GameMenu *)((i8 *)&main_menu_block.main_menu),2,(char *)item_arg);
      item_arg = 0;
      label = (iptr)text_read_line(1);
      menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),2,0x201,(const char *)label,item_arg);
      menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),2,0,0,0);
      item_arg = 0;
      label = (iptr)text_read_line(1);
      menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),2,0x205,(const char *)label,item_arg);
      item_arg = 0;
      label = (iptr)text_read_line(1);
      menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),2,0x210,(const char *)label,item_arg);
      menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),2,0,0,0);
      item_arg = 0;
      label = (iptr)text_read_line(1);
      menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),2,0x220,(const char *)label,item_arg);
      status = text_open_section(0,(const char *)&str_view);
      if (status == 0) {
        item_arg = (i32)text_read_line(1);
        menu_add_menu((GameMenu *)((i8 *)&main_menu_block.main_menu),3,(char *)item_arg);
        item_arg = 0;
        label = (iptr)text_read_line(1);
        menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),3,0x301,(const char *)label,item_arg);
        item_arg = 0;
        label = (iptr)text_read_line(1);
        menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),3,0x302,(const char *)label,item_arg);
        menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),3,0,0,0);
        item_arg = 0;
        label = (iptr)text_read_line(1);
        menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),3,0x310,(const char *)label,item_arg);
        item_arg = 0;
        label = (iptr)text_read_line(1);
        menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),3,0x311,(const char *)label,item_arg);
        menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),3,0,0,0);
        item_arg = 0;
        label = (iptr)text_read_line(1);
        menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),3,800,(const char *)label,item_arg);
        item_arg = 0;
        label = (iptr)text_read_line(1);
        menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),3,0x321,(const char *)label,item_arg);
        item_arg = 0;
        label = (iptr)text_read_line(1);
        menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),3,0x322,(const char *)label,item_arg);
        item_arg = 0;
        label = (iptr)text_read_line(1);
        menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),3,0x324,(const char *)label,item_arg);
        menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),3,0,0,0);
        item_arg = 0;
        label = (iptr)text_read_line(1);
        menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),3,0x327,(const char *)label,item_arg);
        item_arg = 0;
        label = (iptr)text_read_line(1);
        menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),3,0x328,(const char *)label,item_arg);
        item_arg = 0;
        label = (iptr)text_read_line(1);
        menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),3,0x330,(const char *)label,item_arg);
        item_arg = 0;
        label = (iptr)text_read_line(1);
        menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),3,0x340,(const char *)label,item_arg);
        menu_set_item_checked
                  ((GameMenu *)((i8 *)&main_menu_block.main_menu),0x327,(game.game_options & 0x20) >> 5);
        status = text_open_section(0,(const char *)&str_orders_2);
        if (status == 0) {
          item_arg = (i32)text_read_line(1);
          menu_add_menu((GameMenu *)((i8 *)&main_menu_block.main_menu),4,(char *)item_arg);
          item_arg = 0x3c;
          label = (iptr)text_read_line(1);
          menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),4,0x401,(const char *)label,item_arg);
          item_arg = 0x3c;
          label = (iptr)text_read_line(1);
          menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),4,0x410,(const char *)label,item_arg);
          item_arg = 0x3c;
          label = (iptr)text_read_line(1);
          menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),4,0x411,(const char *)label,item_arg);
          item_arg = 0x3c;
          label = (iptr)text_read_line(1);
          menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),4,0x412,(const char *)label,item_arg);
          item_arg = 0x3c;
          label = (iptr)text_read_line(1);
          menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),4,0x413,(const char *)label,item_arg);
          menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),4,0,0,0);
          item_arg = 0;
          label = (iptr)text_read_line(1);
          menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),4,0x417,(const char *)label,item_arg);
          item_arg = 0;
          label = (iptr)text_read_line(1);
          menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),4,0x418,(const char *)label,item_arg);
          item_arg = 0;
          label = (iptr)text_read_line(1);
          menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),4,0x41b,(const char *)label,item_arg);
          item_arg = 0;
          label = (iptr)text_read_line(1);
          menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),4,0x420,(const char *)label,item_arg);
          item_arg = 0;
          label = (iptr)text_read_line(1);
          menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),4,0x421,(const char *)label,item_arg);
          menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),4,0,0,0);
          item_arg = 0;
          label = (iptr)text_read_line(1);
          menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),4,0x430,(const char *)label,item_arg);
          item_arg = 0;
          label = (iptr)text_read_line(1);
          menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),4,0x440,(const char *)label,item_arg);
          item_arg = 0;
          label = (iptr)text_read_line(1);
          menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),4,0x441,(const char *)label,item_arg);
          item_arg = 0;
          label = (iptr)text_read_line(1);
          menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),4,0x442,(const char *)label,item_arg);
          item_arg = 0x3c;
          label = (iptr)text_read_line(1);
          menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),4,0x445,(const char *)label,item_arg);
          menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),4,0,0,0);
          item_arg = 0;
          label = (iptr)text_read_line(1);
          menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),4,0x450,(const char *)label,item_arg);
          item_arg = 0;
          label = (iptr)text_read_line(1);
          menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),4,0x451,(const char *)label,item_arg);
          menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),4,0,0,0);
          item_arg = 0;
          label = (iptr)text_read_line(1);
          menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),4,0x460,(const char *)label,item_arg);
          item_arg = 0;
          label = (iptr)text_read_line(1);
          menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),4,0x468,(const char *)label,item_arg);
          item_arg = 0;
          label = (iptr)text_read_line(1);
          menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),4,0x470,(const char *)label,item_arg);
          item_arg = 0;
          label = (iptr)text_read_line(1);
          menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),4,0x480,(const char *)label,item_arg);
          menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),4,0,0,0);
          item_arg = 0;
          label = (iptr)text_read_line(1);
          menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),4,0x490,(const char *)label,item_arg);
          status = text_open_section(0,(const char *)&str_advisors);
          if (status == 0) {
            item_arg = (i32)text_read_line(1);
            menu_add_menu((GameMenu *)((i8 *)&main_menu_block.main_menu),5,(char *)item_arg);
            item_arg = 0;
            label = (iptr)text_read_line(1);
            menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),5,0x507,(const char *)label,item_arg);
            item_arg = 0;
            label = (iptr)text_read_line(1);
            menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),5,0x500,(const char *)label,item_arg);
            menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),5,0,0,0);
            item_arg = 0;
            label = (iptr)text_read_line(1);
            menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),5,0x501,(const char *)label,item_arg);
            item_arg = 0;
            label = (iptr)text_read_line(1);
            menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),5,0x502,(const char *)label,item_arg);
            item_arg = 0;
            label = (iptr)text_read_line(1);
            menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),5,0x503,(const char *)label,item_arg);
            menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),5,0,0,0);
            item_arg = 0;
            label = (iptr)text_read_line(1);
            menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),5,0x504,(const char *)label,item_arg);
            item_arg = 0;
            label = (iptr)text_read_line(1);
            menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),5,0x505,(const char *)label,item_arg);
            item_arg = 0;
            label = (iptr)text_read_line(1);
            menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),5,0x506,(const char *)label,item_arg);
            menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),5,0,0,0);
            item_arg = 0;
            label = (iptr)text_read_line(1);
            menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),5,0x508,(const char *)label,item_arg);
            status = text_open_section(0,(const char *)&str_world);
            if (status == 0) {
              item_arg = (i32)text_read_line(1);
              menu_add_menu((GameMenu *)((i8 *)&main_menu_block.main_menu),6,(char *)item_arg);
              item_arg = 0;
              label = (iptr)text_read_line(1);
              menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),6,0x601,(const char *)label,item_arg);
              item_arg = 0;
              label = (iptr)text_read_line(1);
              menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),6,0x602,(const char *)label,item_arg);
              item_arg = 0;
              label = (iptr)text_read_line(1);
              menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),6,0x603,(const char *)label,item_arg);
              menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),6,0,0,0);
              item_arg = 0;
              label = (iptr)text_read_line(1);
              menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),6,0x605,(const char *)label,item_arg);
              item_arg = 0;
              label = (iptr)text_read_line(1);
              menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),6,0x606,(const char *)label,item_arg);
              status = text_open_section(0,(const char *)&str_cheat);
              if (status == 0) {
                item_arg = (i32)text_read_line(1);
                menu_add_menu((GameMenu *)((i8 *)&main_menu_block.main_menu),7,(char *)item_arg);
                item_arg = 0;
                label = (iptr)text_read_line(1);
                menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),7,0x701,(const char *)label,item_arg);
                menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),7,0,0,0);
                item_arg = 0;
                label = (iptr)text_read_line(1);
                menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),7,0x711,(const char *)label,item_arg);
                item_arg = 0;
                label = (iptr)text_read_line(1);
                menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),7,0x712,(const char *)label,item_arg);
                item_arg = 0;
                label = (iptr)text_read_line(1);
                menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),7,0x713,(const char *)label,item_arg);
                menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),7,0,0,0);
                item_arg = 0;
                label = (iptr)text_read_line(1);
                menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),7,0x721,(const char *)label,item_arg);
                item_arg = 0;
                label = (iptr)text_read_line(1);
                menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),7,0x722,(const char *)label,item_arg);
                menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),7,0,0,0);
                item_arg = 0;
                label = (iptr)text_read_line(1);
                menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),7,0x731,(const char *)label,item_arg);
                item_arg = 0;
                label = (iptr)text_read_line(1);
                menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),7,0x732,(const char *)label,item_arg);
                item_arg = 0;
                label = (iptr)text_read_line(1);
                menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),7,0x740,(const char *)label,item_arg);
                item_arg = 0;
                label = (iptr)text_read_line(1);
                menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),7,0x748,(const char *)label,item_arg);
                item_arg = 0;
                label = (iptr)text_read_line(1);
                menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),7,0x750,(const char *)label,item_arg);
                item_arg = 0;
                label = (iptr)text_read_line(1);
                menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),7,0x752,(const char *)label,item_arg);
                menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),7,0,0,0);
                item_arg = 0;
                label = (iptr)text_read_line(1);
                menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),7,0x755,(const char *)label,item_arg);
                item_arg = 0;
                label = (iptr)text_read_line(1);
                menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),7,0x760,(const char *)label,item_arg);
                item_arg = 0;
                label = (iptr)text_read_line(1);
                menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),7,0x765,(const char *)label,item_arg);
                menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),7,0,0,0);
                item_arg = 0;
                label = (iptr)text_read_line(1);
                menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),7,0x768,(const char *)label,item_arg);
                item_arg = 0;
                label = (iptr)text_read_line(1);
                menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),7,0x770,(const char *)label,item_arg);
                if (((game.game_options & 0x8000) == 0) || (game.multiplayer != '\0')) {
                  cheat_disabled = 1;
                }
                else {
                  cheat_disabled = 0;
                }
                menu_set_menu_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),7,cheat_disabled);
                if (((game.game_options & 0x8000) == 0) || (game.multiplayer != '\0')) {
                  cheat_checked = 0;
                }
                else {
                  cheat_checked = 1;
                }
                menu_set_item_checked((GameMenu *)((i8 *)&main_menu_block.main_menu),0x701,cheat_checked);
                menu_set_item_enabled
                          ((GameMenu *)((i8 *)&main_menu_block.main_menu),0x701,
                           (game.multiplayer != '\0' &((int *)&mp_cheat_menu_allowed) == 0));
                status = text_open_section(0,(const char *)&str_editor);
                if (status == 0) {
                  item_arg = (i32)text_read_line(1);
                  menu_add_menu((GameMenu *)((i8 *)&main_menu_block.main_menu),8,(char *)item_arg);
                  item_arg = 0;
                  label = (iptr)text_read_line(1);
                  menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),8,0x801,(const char *)label,item_arg);
                  menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),8,0,0,0);
                  item_arg = 0;
                  label = (iptr)text_read_line(1);
                  menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),8,0x802,(const char *)label,item_arg);
                  item_arg = 0;
                  label = (iptr)text_read_line(1);
                  menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),8,0x803,(const char *)label,item_arg);
                  item_arg = 0;
                  label = (iptr)text_read_line(1);
                  menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),8,0x804,(const char *)label,item_arg);
                  item_arg = 0;
                  label = (iptr)text_read_line(1);
                  menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),8,0x805,(const char *)label,item_arg);
                  item_arg = 0;
                  label = (iptr)text_read_line(1);
                  menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),8,0x806,(const char *)label,item_arg);
                  item_arg = 0;
                  label = (iptr)text_read_line(1);
                  menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),8,0x807,(const char *)label,item_arg);
                  item_arg = 0;
                  label = (iptr)text_read_line(1);
                  menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),8,0x808,(const char *)label,item_arg);
                  item_arg = 0;
                  label = (iptr)text_read_line(1);
                  menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),8,0x809,(const char *)label,item_arg);
                  if (((((game.game_options & 0x8000) == 0) || (game.multiplayer != '\0')) ||
                      ((game.game_flags & 0x80) == 0)) ||
                     (status = _strcmp(((i8 *)&net_map_lock_slots_block.scenario_dir_path),((i8 *)&civ_saved_cursor_x_block.game_home_dir)), status == 0)) {
                    editor_checked = 0;
                  }
                  else {
                    editor_checked = 1;
                  }
                  menu_set_item_checked((GameMenu *)((i8 *)&main_menu_block.main_menu),0x801,editor_checked);
                  if ((((game.game_options & 0x8000) == 0) || (game.multiplayer != '\0')) ||
                     (((game.game_flags & 0x80) == 0 ||
                      (status = _strcmp(((i8 *)&net_map_lock_slots_block.scenario_dir_path),((i8 *)&civ_saved_cursor_x_block.game_home_dir)), status == 0)))) {
                    editor_disabled = 1;
                  }
                  else {
                    editor_disabled = 0;
                  }
                  menu_set_menu_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),8,editor_disabled);
                  menu_set_item_enabled
                            ((GameMenu *)((i8 *)&main_menu_block.main_menu),0x801,(game.multiplayer != '\0'));
                  status = text_open_section(0,(const char *)&str_pedia_2);
                  if (status == 0) {
                    item_arg = (i32)text_read_line(1);
                    menu_add_menu((GameMenu *)((i8 *)&main_menu_block.main_menu),9,(char *)item_arg);
                    item_arg = 0;
                    label = (iptr)text_read_line(1);
                    menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),9,0x901,(const char *)label,item_arg);
                    item_arg = 0;
                    label = (iptr)text_read_line(1);
                    menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),9,0x903,(const char *)label,item_arg);
                    item_arg = 0;
                    label = (iptr)text_read_line(1);
                    menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),9,0x905,(const char *)label,item_arg);
                    item_arg = 0;
                    label = (iptr)text_read_line(1);
                    menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),9,0x907,(const char *)label,item_arg);
                    menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),9,0,0,0);
                    item_arg = 0;
                    label = (iptr)text_read_line(1);
                    menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),9,0x909,(const char *)label,item_arg);
                    item_arg = 0;
                    label = (iptr)text_read_line(1);
                    menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),9,0x90b,(const char *)label,item_arg);
                    menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),9,0,0,0);
                    item_arg = 0;
                    label = (iptr)text_read_line(1);
                    menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),9,0x90d,(const char *)label,item_arg);
                    menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),9,0,0,0);
                    item_arg = 0;
                    label = (iptr)text_read_line(1);
                    menu_add_item((GameMenu *)((i8 *)&main_menu_block.main_menu),9,0x9f0,(const char *)label,item_arg);
                    menu_set_item_hidden((GameMenu *)((i8 *)&main_menu_block.main_menu),0x441,1);
                    menu_set_item_hidden((GameMenu *)((i8 *)&main_menu_block.main_menu),0x413,1);
                    menu_set_item_hidden((GameMenu *)((i8 *)&main_menu_block.main_menu),0x442,1);
                    menu_set_item_hidden((GameMenu *)((i8 *)&main_menu_block.main_menu),0x417,1);
                    menu_set_item_hidden((GameMenu *)((i8 *)&main_menu_block.main_menu),0x418,1);
                    menu_set_item_hidden((GameMenu *)((i8 *)&main_menu_block.main_menu),0x41b,1);
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  text_close_file();
  menu_rebuild((GameMenu *)((i8 *)&main_menu_block.main_menu),(iptr)&main_frame_wnd_block.main_frame_wnd);
  menu_set_command_handler((GameMenu *)((i8 *)&main_menu_block.main_menu),(iptr)menu_command);
  return;
}

/* 004e4c92 auto */
void __cdecl menu_set_item_label(i32 item_id,i32 label_id,i32 enabled)

{
  i8 label_text[80];
  
  text_clear();
  text_append_label(label_id);
  text_expand_vars((iptr)&map_views_block.text_buffer,(iptr)label_text);
  menu_set_item_text((GameMenu *)((i8 *)&main_menu_block.main_menu),item_id,(const char *)label_text);
  menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),item_id,enabled);
  return;
}

/* 004e4ceb auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl menu_update_states(void)

{
  u8 unit_role;
  char dy;
  bool no_adjacent_city;
  byte terrain_byte;
  int unit;
  int x;
  int y;
  int civ;
  iptr has_airbase_tech;
  iptr has_fortress_tech;
  int city;
  iptr x2;
  uint improvements2;
  i32 improvements22;
  iptr airbase_owner;
  iptr airbase_owner2;
  int terrain2;
  byte *tile;
  iptr path_cmp;
  iptr path_cmp2;
  uptr terrain;
  bool is_ocean;
  i32 scenario_menu_disabled;
  i32 scenario_checked;
  i32 cheat_checked;
  i32 cheat_menu_disabled;
  i32 mine_disabled;
  i32 irrigate_disabled;
  i32 farmland_disabled;
  i32 road_disabled;
  i32 railroad_disabled;
  i32 build_city_disabled;
  i32 fortress_hidden;
  i32 airbase_hidden;
  i32 pillage_hidden;
  i32 revolution_disabled;
  iptr dir;
  
  menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x606,game.rules & 0x80);
  if (game.multiplayer == '\0') {
    menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x130,1);
    menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x132,1);
    menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x507,1);
    menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x104,1);
    menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x105,1);
    menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x120,0);
    menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x9f0,0);
  }
  else {
    menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x9f0,1);
    menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x104,0);
    menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x105,0);
    if (mp_cheat_menu_allowed[0] == 0) {
      menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x701,1);
    }
    menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x120,1);
    if ((civ_saved_cursor_x_block.mp_open_game == 0) || (game.multiplayer != 1)) {
      menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x130,1);
    }
    else {
      menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x130,0);
    }
    if (game.multiplayer == 1) {
      menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x205,1);
    }
    else {
      menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x205,0);
    }
    menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x507,(game.multiplayer < 3));
    if (game.multiplayer == 2) {
      menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x132,1);
      menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x110,1);
    }
    else {
      if (net_session_block.net_host_flag == '\0') {
        menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x132,1);
      }
      else {
        menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x132,0);
      }
      menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x110,0);
    }
    menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x1f1,0);
    menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x1f0,0);
  }
  menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x302,(moving_units_mode == 0));
  menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x301,(moving_units_mode == 1));
  if ((((game.game_flags & 0x80) == 0) || ((prefs_game_rules_block.scenario_flags[0] & 0x10) == 0)) &&
     (civs[human_civ[0]].government != '\0')) {
    revolution_disabled = 0;
  }
  else {
    revolution_disabled = 1;
  }
  menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x220,revolution_disabled);
  if (((moving_units_mode == 0) || (game.num_units == 0)) ||
     ((game.active_unit < 0 ||
      ((game.num_units < game.active_unit || (units[game.active_unit].id == 0)))))) {
    menu_set_menu_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),4,1);
    menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x460,0);
    menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x468,0);
  }
  else {
    unit = (int)game.active_unit;
    x = (int)units[unit].x;
    y = (int)units[unit].y;
    civ = (int)units[unit].owner;
    terrain_byte = tile_terrain(x,y);
    terrain = (uptr)terrain_byte;
    is_ocean = terrain == 10;
    unit_role = unit_types[units[unit].type].role;
    menu_set_menu_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),4,0);
    menu_set_item_hidden((GameMenu *)((i8 *)&main_menu_block.main_menu),0x401,(uint)(unit_role != 5));
    menu_set_item_label(0x401,0x32,(uint)(unit_role != 5));
    menu_set_item_label(0x410,0x34,(uint)(unit_role != 5));
    menu_set_item_label(0x411,0x36,(uint)(unit_role != 5));
    menu_set_item_label(0x412,0x38,(uint)(unit_role != 5));
    menu_set_item_hidden((GameMenu *)((i8 *)&main_menu_block.main_menu),0x450,(uint)(unit_role == 5));
    if ((unit_role == 5) && (has_airbase_tech = civ_has_advance(civ,0x12), has_airbase_tech != 0)) {
      pillage_hidden = 0;
    }
    else {
      pillage_hidden = 1;
    }
    menu_set_item_hidden((GameMenu *)((i8 *)&main_menu_block.main_menu),0x418,pillage_hidden);
    if ((unit_role == 5) && (has_fortress_tech = civ_has_advance(civ,0x42), has_fortress_tech != 0)) {
      airbase_hidden = 0;
    }
    else {
      airbase_hidden = 1;
    }
    menu_set_item_hidden((GameMenu *)((i8 *)&main_menu_block.main_menu),0x417,airbase_hidden);
    menu_set_item_hidden((GameMenu *)((i8 *)&main_menu_block.main_menu),0x430,(uint)(unit_role == 5));
    menu_set_item_hidden((GameMenu *)((i8 *)&main_menu_block.main_menu),0x41b,(uint)(unit_role != 5));
    city = civ_has_advance(civ,0xd);
    if ((city == 0) && ((unit_types[units[unit].type].flags & 0x100) == 0)) {
      fortress_hidden = 1;
    }
    else {
      fortress_hidden = 0;
    }
    menu_set_item_hidden((GameMenu *)((i8 *)&main_menu_block.main_menu),0x441,fortress_hidden);
    menu_set_item_enabled
              ((GameMenu *)((i8 *)&main_menu_block.main_menu),0x441,
               ((unit_types[units[unit].type].flags & 0x100) == 0));
    city = civ_has_advance(civ,0x42);
    menu_set_item_hidden((GameMenu *)((i8 *)&main_menu_block.main_menu),0x442,(uint)(city == 0));
    city = tile_city_owner(x,y);
    menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x442,(city < 0));
    if (unit_role == 5) {
      no_adjacent_city = true;
      for (dir = 0; dir < 8; dir++) {
        x2 = map_wrap_x((((i8 *)&dir_dx_table_block.dir_dx_table))[dir] + x);
        dy = (((i8 *)&dir_dy_table_block.dir_dy_table))[dir];
        city = map_in_bounds(x2,dy + y);
        if ((city != 0) && (city = tile_city_owner(x2,dy + y), -1 < city)) {
          no_adjacent_city = false;
        }
      }
      city = city_at(x,y);
      if (city < 0) {
        terrain2 = tile_is_ocean(x,y);
        if ((terrain2 == 0) && (no_adjacent_city)) {
          build_city_disabled = 0;
        }
        else {
          build_city_disabled = 1;
        }
        menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x401,build_city_disabled);
      }
      else {
        menu_set_item_label(0x401,0x33,(uint)('\t' < cities[city].size));
      }
      improvements2 = tile_improvements(x,y);
      if ((improvements2 & 0x80) == 0) {
        menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x420,1);
      }
      improvements22 = tile_improvements(x,y);
      if ((((((byte)improvements22 & 0x42) == 0x40) ||
           (airbase_owner = tile_airbase_owner(x,y), -1 < airbase_owner)) || (is_ocean)) || (-1 < city)) {
        menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x418,1);
      }
      improvements22 = tile_improvements(x,y);
      if (((((byte)improvements22 & 0x42) == 0x40) ||
          (airbase_owner2 = tile_airbase_owner(x,y), -1 < airbase_owner2)) || ((is_ocean || (-1 < city)))) {
        menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x417,1);
      }
      improvements2 = tile_improvements(x,y);
      if (((improvements2 & 0x10) == 0) || (terrain2 = civ_has_advance(civ,0x43), terrain2 == 0)) {
        if (((is_ocean) ||
            ((-1 < city || (improvements2 = tile_improvements(x,y), (improvements2 & 0x10) != 0)))) ||
           ((tile = (byte *)tile_at(x,y), (*tile & 0x80) != 0 &&
            (terrain2 = civ_has_advance(civ,7), terrain2 == 0)))) {
          road_disabled = 1;
        }
        else {
          road_disabled = 0;
        }
        menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x410,road_disabled);
      }
      else {
        improvements2 = tile_improvements(x,y);
        if ((((improvements2 & 0x20) != 0) || (-1 < city)) || (is_ocean)) {
          railroad_disabled = 1;
        }
        else {
          railroad_disabled = 0;
        }
        menu_set_item_label(0x410,0x35,railroad_disabled);
      }
      terrain2 = (int)terrain_types[terrain].irrigate_to;
      if (terrain2 < 0) {
        improvements2 = tile_improvements(x,y);
        if ((improvements2 & 4) == 0) {
          if (((terrain2 == -1) || (is_ocean)) || (-1 < city)) {
            irrigate_disabled = 1;
          }
          else {
            irrigate_disabled = 0;
          }
          menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x411,irrigate_disabled);
        }
        else {
          terrain2 = civ_has_advance(civ,0x46);
          if (((terrain2 == 0) || (is_ocean)) || (-1 < city)) {
            farmland_disabled = 1;
          }
          else {
            farmland_disabled = 0;
          }
          menu_set_item_label(0x411,0x3d,farmland_disabled);
        }
      }
      else {
        text_set_label_arg(0,terrain_types[terrain2].name);
        menu_set_item_label(0x411,0x37,0);
      }
      terrain2 = (int)terrain_types[terrain].mine_to;
      if (terrain2 < 0) {
        if (((terrain2 == -1) || (is_ocean)) || (-1 < city)) {
          mine_disabled = 1;
        }
        else {
          mine_disabled = 0;
        }
        menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x412,mine_disabled);
      }
      else {
        text_set_label_arg(0,terrain_types[terrain2].name);
        menu_set_item_label(0x412,0x39,0);
      }
      civ = civ_can_build_unit(civ,-1,1);
      menu_set_item_hidden((GameMenu *)((i8 *)&main_menu_block.main_menu),0x413,(uint)(civ == 0));
      if (terrain_types[terrain].transform_to < 0) {
        menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x413,1);
      }
      else {
        text_set_label_arg(0,terrain_types[terrain_types[terrain].transform_to].name);
        menu_set_item_label(0x413,0x3c,(uint)(units[unit].type != 1));
      }
    }
    else {
      menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x413,1);
      menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x418,1);
      menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x420,1);
    }
    civ = tile_city_owner(x,y);
    if (civ < 0) {
      menu_set_item_label(0x445,0x3b,0);
    }
    else {
      x = tile_city_owner(x,y);
      menu_set_item_label(0x445,0x3a,(uint)(x < 0));
    }
    menu_set_item_enabled
              ((GameMenu *)((i8 *)&main_menu_block.main_menu),0x430,(unit_types[units[unit].type].hold == '\0'))
    ;
    menu_set_item_hidden((GameMenu *)((i8 *)&main_menu_block.main_menu),0x421,(uint)(unit_role == 5));
    if ((unit_types[units[unit].type].attack == '\0') ||
       (unit_types[units[unit].type].domain != '\0')) {
      menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x421,1);
    }
  }
  if ((((*((char *)&game.game_options + 1)) & 0x80) == 0) || (game.multiplayer != '\0')) {
    cheat_menu_disabled = 1;
  }
  else {
    cheat_menu_disabled = 0;
  }
  menu_set_menu_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),7,cheat_menu_disabled);
  if ((((*((char *)&game.game_options + 1)) & 0x80) == 0) || (game.multiplayer != '\0')) {
    cheat_checked = 0;
  }
  else {
    cheat_checked = 1;
  }
  menu_set_item_checked((GameMenu *)((i8 *)&main_menu_block.main_menu),0x701,cheat_checked);
  menu_set_item_enabled
            ((GameMenu *)((i8 *)&main_menu_block.main_menu),0x701,(uint)(game.multiplayer != '\0' &((int *)&mp_cheat_menu_allowed) == 0)
            );
  if ((2 < game.multiplayer) && (net_session_block.mp_turn_civ != human_civ[0])) {
    menu_set_menu_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),4,1);
  }
  if ((((((*((char *)&game.game_options + 1)) & 0x80) == 0) || (game.multiplayer != '\0')) ||
      ((game.game_flags & 0x80) == 0)) ||
     (path_cmp = _strcmp(((i8 *)&net_map_lock_slots_block.scenario_dir_path),((i8 *)&civ_saved_cursor_x_block.game_home_dir)), path_cmp == 0)) {
    scenario_checked = 0;
  }
  else {
    scenario_checked = 1;
  }
  menu_set_item_checked((GameMenu *)((i8 *)&main_menu_block.main_menu),0x801,scenario_checked);
  if (((((*((char *)&game.game_options + 1)) & 0x80) == 0) || (game.multiplayer != '\0')) ||
     (((game.game_flags & 0x80) == 0 || (path_cmp2 = _strcmp(((i8 *)&net_map_lock_slots_block.scenario_dir_path),((i8 *)&civ_saved_cursor_x_block.game_home_dir)), path_cmp2 == 0)
      ))) {
    scenario_menu_disabled = 1;
  }
  else {
    scenario_menu_disabled = 0;
  }
  menu_set_menu_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),8,scenario_menu_disabled);
  menu_set_item_enabled((GameMenu *)((i8 *)&main_menu_block.main_menu),0x801,(game.multiplayer != '\0'))
  ;
  menu_rebuild((GameMenu *)((i8 *)&main_menu_block.main_menu),0);
  return;
}

/* 004e7240 auto */
void __thiscall wnd_show_restored(WndBase *self)

{
  wnd_obj_show_restored(self->native_wnd);
  return;
}

/* 004eb80a auto */
int __cdecl popup_city_picture_zoom(const char *section,iptr city,uint picture,int silent,iptr civ)

{
  ViewWindow *self;
  int result;
  i32 height;
  i32 width;
  iptr option_text;
  iptr option_id;
  uint picture_id;
  void *popup_new;
  Sprite sprite;
  void *popup;
  GamePalette palette;
  i32 eh_prev;
  i8 *eh_handler;
  uint eh_state;
  
  eh_state = 0xffffffff;
  palette_init(&palette);
  eh_state = 0;
  sprite_init(&sprite);
  (*((char *)&eh_state + 0)) = 1;
  if (civ_saved_cursor_x_block.autoplay_active == 0) {
    if (silent == 0) {
      if (main_menu_block.city_notify_enabled == 0) {
        eh_state = eh_state & 0xffffff00;
        /* inlined unwind funclet 004ebbad */ { sprite_destroy(&sprite); }
        eh_state = 0xffffffff;
        /* inlined unwind funclet 004ebbb9 */ { palette_destroy(&palette); }
        result = 0;
        goto return_result;
      }
      civ = (iptr)cities[city].owner;
      mapviews_ensure_visible((int)cities[city].x,(int)cities[city].y,civ);
      text_set_string_arg_b(0,(const char *)&cities[city].name);
    }
    self = (ViewWindow *)operator_new(0x798);
    (*((char *)&eh_state + 0)) = 2;
    if (self == (ViewWindow *)0x0) {
      popup_new = (void *)0x0;
    }
    else {
      popup_new = (void *)city_picture_popup_ctor(self);
    }
    eh_state = (eh_state & 0xffffff00 | (byte)(1));
    popup = popup_new;
    result = civ_has_advance(civ,0x25);
    if (result != 0) {
      picture++;
    }
    if ((int)picture < 1) {
      picture_id = ~picture + 1;
    }
    else {
      picture_id = picture;
    }
    surface_load_gif_resource
              ((DibSurface *)((int)popup + 0x2d8),picture_id,10,0xc0,(iptr)&palette);
    height = surface_height((DibSurface *)((int)popup + 0x2d8));
    width = surface_width((DibSurface *)((int)popup + 0x2d8));
    sprite_grab_from_surface(&sprite,(int)popup + 0x2d8,7,0,0,width,height);
    dialog_load_game_text((Dialog *)((int)popup + 0x4a4),section);
    dialog_add_sprite
              ((DialogOptionList *)((int)popup + 0x4a4),(iptr)&sprite,0,0);
    if ((silent == 0) && (main_menu_block.city_zoom_requested == 0)) {
      height = 0;
      option_id = 1;
      option_text = (iptr)label_string(label_string_ids[0x20]);
      dialog_add_option
                ((DialogOptionList *)((int)popup + 0x4a4),(const char *)option_text,option_id,height);
      height = 0;
      option_id = 0;
      option_text = (iptr)label_string(label_string_ids[0x21]);
      dialog_add_option
                ((DialogOptionList *)((int)popup + 0x4a4),(const char *)option_text,option_id,height);
      if ((game.message_options & 0x400) == 0) {
        dialog_set_default_choice((DialogOptionList *)((int)popup + 0x4a4),0);
      }
      else {
        dialog_set_default_choice((DialogOptionList *)((int)popup + 0x4a4),1);
      }
    }
    result = dlg_show_modal((Dialog *)((int)popup + 0x4a4),0);
    if ((silent == 0) && (0 < result)) {
      main_menu_block.city_zoom_requested = 1;
    }
    if (popup != (void *)0x0) {
      city_picture_popup_scalar_dtor(popup,1);
    }
    eh_state = eh_state & 0xffffff00;
    /* inlined unwind funclet 004ebbad */ { sprite_destroy(&sprite); }
    eh_state = 0xffffffff;
    /* inlined unwind funclet 004ebbb9 */ { palette_destroy(&palette); }
  }
  else {
    eh_state = eh_state & 0xffffff00;
    /* inlined unwind funclet 004ebbad */ { sprite_destroy(&sprite); }
    eh_state = 0xffffffff;
    /* inlined unwind funclet 004ebbb9 */ { palette_destroy(&palette); }
    result = 0;
  }
return_result:
  return result;
}

/* 00511320 auto */
u32 __thiscall wnd_get_palette(WndPaletteView *self)

{
  return self->wnd_palette;
}

/* 00511460 auto */
void __thiscall
hotspot_add_rect(ClickMap *self,iptr id,i32 cursor,RECT *rect)

{
  clickmap_add(self,id,cursor,rect->left,rect->top,
                     rect->right - rect->left,
                     rect->bottom - rect->top);
  return;
}

/* 00511520 auto */
i32 __cdecl popup_game_with_city_flags(const char *section,i32 city,i32 flags)

{
  i32 result;
  
  result = popup_text_with_city((const char *)&str_game_7,section,city,flags);
  return result;
}

/* 00511820 auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall frame_wnd_set_title_font(FrameWindow *self,iptr font)

{
  self->title_font = font;
  return;
}

/* 00511850 auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall frame_wnd_set_title_small_font(FrameWindow *self,iptr font)

{
  self->title_small_font = font;
  return;
}

/* 00518e80 auto */
void __thiscall wnd_move_xy(WndMoveView *self,i32 x,i32 y)

{
  wnd_obj_move_xy(self->native_wnd,x,y);
  return;
}

/* 00518ec0 auto */
i32 __cdecl dlg_input_number_game(const char *section,i32 initial,iptr out_value)

{
  i32 result;
  
  result = dlg_input_number((iptr)&str_game_7,section,initial,out_value);
  return result;
}

/* 0051d3e0 auto */
i32 __cdecl
popup_text_run(iptr file,const char *section,i32 result,i32 arg4,i32 arg5,
            i32 arg6,i32 arg7)

{
  int status;
  Dialog dialog2;
  int i;
  i32 eh_prev;
  i8 *eh_handler;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  dialog_ctor(&dialog2,0x4000);
  eh_state = 0;
  status = dialog_load_text_section
                    (&dialog2,(const char *)file,section,result,0,arg4,arg5,arg6,arg7);
  if (status == 0) {
    if (((byte)dialog2.style_flags & 4) != 0) {
      for (i = 0; i < (int)dialog2.option_count; i++) {
        dialog_set_option_checked
                  ((DialogOptionList *)&dialog2,i,1 << ((byte)i & 0x1f) & dlg_check_bits
                  );
      }
    }
    result = dlg_show_modal(&dialog2,0);
    (*(u32 *)&dlg_help_pressed) = dialog2.result_extra;
    if (((byte)dialog2.style_flags & 4) != 0) {
      dlg_check_bits = 0;
      for (i = 0; i < (int)dialog2.option_count; i++) {
        status = dialog_option_is_checked((DialogOptionList *)&dialog2,i);
        if (status != 0) {
          dlg_check_bits = dlg_check_bits | 1 << ((byte)i & 0x1f);
        }
      }
    }
  }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 0051d53f */ { dialog_dtor(&dialog2); }
  return result;
}

/* 0051d564 auto */
i32 __cdecl
popup_text_with_sprite(iptr file,const char *section,i32 flags,iptr sprite,i32 zoom)

{
  i32 result;
  Dialog dialog2;
  i32 eh_prev;
  i8 *eh_handler;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  dialog_ctor(&dialog2,0x4000);
  eh_state = 0;
  dialog_load_text(&dialog2,(const char *)file,section,flags);
  dialog_add_sprite((DialogOptionList *)&dialog2,sprite,0,0);
  dialog_set_image_zoom((DialogWindowView *)&dialog2,zoom);
  result = dlg_show_modal(&dialog2,0);
  (*(u32 *)&dlg_help_pressed) = dialog2.result_extra;
  eh_state = 0xffffffff;
  /* inlined unwind funclet 0051d616 */ { dialog_dtor(&dialog2); }
  return result;
}

/* 0051d63b auto */
i32 __cdecl
dlg_text_input(iptr file,const char *section,i32 max_len,iptr initial_text,iptr out_text)

{
  int status;
  i32 result;
  Dialog dialog2;
  char *p;
  i32 eh_prev;
  i8 *eh_handler;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  result = 0;
  dialog_ctor(&dialog2,0x4000);
  eh_state = 0;
  str_clear((char *)out_text);
  status = dialog_load_text_section(&dialog2,(const char *)file,section,max_len,initial_text,0,0,0,1);
  if (status == 0) {
    result = dialog_run_modal(&dialog2,out_text,0);
    for (p = (char *)out_text;
        (*p != '\0' && ((*p == ' ' || (*p == '\t')))); p++)
    {
      *p = '_';
    }
  }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 0051d738 */ { dialog_dtor(&dialog2); }
  return result;
}

/* 0051d75d auto */
i32 __cdecl dlg_input_number(iptr file,const char *section,int initial,iptr out_value)

{
  long value;
  char input_text[260];
  char initial_text[20];
  i32 result;
  
  __itoa(initial,initial_text,10);
  result = dlg_text_input(file,section,5,(iptr)initial_text,(iptr)input_text);
  value = _atol(input_text);
  *(long *)out_value = value;
  return result;
}

/* 0051d7bc auto */
void __cdecl dlg_checks_clear(void)

{
  (*(i32 *)&dlg_check_bits) = 0;
  return;
}

/* 0051d7d6 auto */
void __cdecl dlg_check_set(i32 index,int checked)

{
  if (checked == 0) {
    dlg_check_bits = dlg_check_bits & ~(1 << ((byte)index & 0x1f));
  }
  else {
    dlg_check_bits = dlg_check_bits | 1 << ((byte)index & 0x1f);
  }
  return;
}

/* 0051d817 auto */
uint __cdecl dlg_check_get(i32 index)

{
  return 1 << ((byte)index & 0x1f) & dlg_check_bits;
}

/* 0052182c auto */
void __cdecl dialog_prepend_title_label(iptr dialog,i32 label_id)

{
  size_t len;
  i32 buffer;
  char title[128];
  
  title[0] = '\0';
  str_append_label((iptr)title,label_id);
  if (*(int *)(dialog + 0x134) != 0) {
    crt_strcat(title,((i8 *)&dialog_title_label_space_str));
    crt_strcat((char *)((void *)title),(const char *)((void *)(*(i32 *)(dialog + 0x134))));
  }
  len = _strlen(title);
  buffer = memblock_alloc(dialog + 0x254,len + 1);
  *(i32 *)(dialog + 0x134) = buffer;
  crt_strcpy((char *)((void *)(*(i32 *)(dialog + 0x134))),(const char *)((void *)title));
  return;
}

/* 00548b70 auto */
int __cdecl ui_calc_item_spacing(int count,int item_size,int total_size,iptr out_count,iptr out_remainder)

{
  int free_space;
  int spacing;
  int result;
  
  if (item_size < 2) {
    item_size = 1;
  }
  if (count < 2) {
    count = 1;
  }
  result = item_size;
  if (count == 1) {
    if (out_remainder != 0) {
      *(i32 *)out_remainder = 0;
    }
    if (out_count != 0) {
      *(i32 *)out_count = 1;
    }
  }
  else {
    free_space = total_size - item_size;
    spacing = free_space / (count - 1);
    if (out_remainder != 0) {
      *(int *)out_remainder = free_space % (count - 1);
    }
    if (out_count != 0) {
      *(int *)out_count = count;
    }
    if ((spacing < item_size) && (result = spacing, spacing < 1)) {
      if (out_remainder != 0) {
        *(i32 *)out_remainder = 0;
      }
      if (out_count != 0) {
        *(int *)out_count = (free_space - item_size) + 1;
      }
      result = 1;
    }
  }
  return result;
}

/* 00551e20 auto */
i32 __cdecl popup_game_ex(const char *section,i32 arg2,i32 arg3)

{
  i32 result;
  
  result = popup_text_ex((const char *)&str_game_7,section,arg2,arg3);
  return result;
}

/* 00551e60 auto */
i32 __cdecl popup_debug_ex(const char *section,i32 arg2,i32 arg3)

{
  i32 result;
  
  result = popup_text_ex((const char *)&str_debug_11,section,arg2,arg3);
  return result;
}

/* 00551ea0 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E41
    _$E46
    _$E51
    _$E56
     6 names - too many to list
   
   Library: Visual Studio 1998 Debug */

void __cdecl caption_font_global_init(void)

{
  caption_font_static_init();
  caption_font_reg_atexit();
  return;
}

/* 00551eba auto */
void __cdecl caption_font_static_init(void)

{
  font_init((GameFont *)((i8 *)&caption_font_block.caption_font),0,0x10);
  return;
}

/* 00551ed8 auto */
void __cdecl caption_font_reg_atexit(void)

{
  _atexit(caption_font_static_dtor);
  return;
}

/* 00551ef5 auto */
void __cdecl caption_font_static_dtor(void)

{
  font_destroy((GameFont *)((i8 *)&caption_font_block.caption_font));
  return;
}

/* 00551f0f auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E41
    _$E46
    _$E51
    _$E56
     6 names - too many to list
   
   Library: Visual Studio 1998 Debug */

void __cdecl caption_small_font_global_init(void)

{
  caption_small_font_static_init();
  caption_small_font_reg_atexit();
  return;
}

/* 00551f29 auto */
void __cdecl caption_small_font_static_init(void)

{
  font_init((GameFont *)((i8 *)&caption_small_font_block.caption_small_font),0,10);
  return;
}

/* 00551f47 auto */
void __cdecl caption_small_font_reg_atexit(void)

{
  _atexit(caption_small_font_static_dtor);
  return;
}

/* 00551f64 auto */
void __cdecl caption_small_font_static_dtor(void)

{
  font_destroy((GameFont *)((i8 *)&caption_small_font_block.caption_small_font));
  return;
}

/* 00551f7e auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E41
    _$E46
    _$E51
    _$E56
     6 names - too many to list
   
   Library: Visual Studio 1998 Debug */

void __cdecl ui_text_font_global_init(void)

{
  ui_text_font_static_init();
  ui_text_font_reg_atexit();
  return;
}

/* 00551f98 auto */
void __cdecl ui_text_font_static_init(void)

{
  font_init((GameFont *)((i8 *)&ui_text_font),0,0x10);
  return;
}

/* 00551fb6 auto */
void __cdecl ui_text_font_reg_atexit(void)

{
  _atexit(ui_text_font_static_dtor);
  return;
}

/* 00551fd3 auto */
void __cdecl ui_text_font_static_dtor(void)

{
  font_destroy((GameFont *)((i8 *)&ui_text_font));
  return;
}

/* 00551fed auto */
void __cdecl ui_init_screen_metrics(void)

{
  int metric;
  
  gfx_get_screen_rect((iptr)&caption_small_font_block.screen_rect);
  caption_font_block.screen_width = rect_width((RECT *)&caption_small_font_block.screen_rect);
  caption_font_block.screen_height = rect_height((RECT *)&caption_small_font_block.screen_rect);
  ui_font_height = 0x10;
  if (999 < caption_font_block.screen_width) {
    ui_font_height = 0x18;
  }
  (*(uint *)&ui_large_screen) = (uint)(999 < caption_font_block.screen_width);
  font_set((GameFont *)((i8 *)&caption_font_block.caption_font),0,ui_font_height);
  font_set((GameFont *)((i8 *)&caption_small_font_block.caption_small_font),0,(ui_font_height * 2) / 3);
  font_set((GameFont *)((i8 *)&ui_text_font),0,ui_font_height);
  metric = font_cached_height((GameFont *)((i8 *)&caption_font_block.caption_font));
  frame_caption_height = metric + frame_padding * 2 + frame_bevel_width * 2;
  frame_border_width = frame_bevel_width * 2 + frame_padding * 2;
  metric = GetSystemMetrics(7);
  sys_dlgframe_w2 = metric * 2;
  metric = GetSystemMetrics(8);
  sys_dlgframe_h2 = metric * 2;
  return;
}

/* 005520fa auto */
void __cdecl frame_set_border_tile(iptr tile)

{
  frame_border_tile = tile;
  return;
}

/* 00552112 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall frame_wnd_draw_caption(FrameWindow *self)

{
  i32 adjective;
  int title_height;
  int small_height;
  uptr len;
  uptr len2;
  u32 caption_h2;
  u32 caption_h;
  i8 sprite_rect[16];
  int minutes;
  int seconds;
  int height2;
  int bevel;
  i32 shadow_color2;
  int text_width;
  int width2;
  int button_y2;
  int button_x;
  int offset;
  GameFont *font2;
  int text_y2;
  i32 highlight_color2;
  int text_x2;
  int i;
  char caption[256];
  struct { u32 left; u32 top; u32 right; u32 bottom; } rect2;
  
  surface_reset_clip((DibSurface *)self);
  highlight_color2 = frame_highlight_color;
  shadow_color2 = frame_shadow_color;
  bevel = frame_bevel_width;
  if (self->caption_height == 0) {
    caption_h = self->border_width;
  }
  else {
    caption_h = self->caption_height;
  }
  height2 = caption_h + frame_bevel_width * -2;
  width2 = rect_width((RECT *)&self->frame_rect);
  gfx_tile_fill((iptr)self,frame_border_tile,0,bevel,width2,height2,0,bevel);
  height2 = self->border_width + bevel * -2;
  offset = rect_height((RECT *)&self->frame_rect);
  offset -= (bevel + height2);
  gfx_tile_fill((iptr)self,frame_border_tile,0,offset,width2,height2,0,offset);
  width2 = self->border_width + bevel * -2;
  height2 = rect_height((RECT *)&self->frame_rect);
  gfx_tile_fill((iptr)self,frame_border_tile,bevel,0,width2,height2,bevel,0);
  offset = rect_width((RECT *)&self->frame_rect);
  offset -= (bevel + width2);
  gfx_tile_fill((iptr)self,frame_border_tile,offset,0,width2,height2,offset,0);
  rect2.left = self->frame_rect;
  rect2.top = self->frame_top;
  rect2.right = self->frame_right;
  rect2.bottom = self->frame_bottom;
  for (i = 0; i < bevel; i++) {
    gfx_draw_bevel_rect((iptr)self,(RECT *)&rect2,highlight_color2,shadow_color2);
    rect_deflate((iptr)&rect2,1,1);
  }
  rect_deflate((iptr)&rect2,self->border_width + bevel * -2,0);
  if (self->caption_height == 0) {
    caption_h2 = self->border_width;
  }
  else {
    caption_h2 = self->caption_height;
  }
  rect2.top = rect2.top + caption_h2 + bevel * -2;
  rect2.bottom -= (self->border_width + bevel * -2);
  for (i = 0; i < bevel; i++) {
    gfx_draw_bevel_rect((iptr)self,(RECT *)&rect2,shadow_color2,highlight_color2);
    rect_deflate((iptr)&rect2,1,1);
  }
  button_x = frame_border_width;
  for (i = 0; i < (int)self->caption_button_count; i++) {
    width2 = (int)(*(int *)(self->pane_selection_flags_area + i * 0x1c + 0xc) * self->caption_height) / 0x18;
    height2 = (int)(*(int *)(self->pane_selection_flags_area + i * 0x1c + 0x10) * self->caption_height) / 0x18;
    button_y2 = ((int)self->caption_height >> 1) - (height2 >> 1);
    rect_set_xywh((iptr)&rect2,button_x,button_y2,width2,height2);
    gfx_set_scale_ratio(self->caption_height,0x18);
    sprite_draw
              (*(Sprite **)(self->pane_selection_flags_area + i * 0x1c + 0x14),(iptr)sprite_rect,
               (iptr)self,button_x,button_y2);
    gfx_reset_zoom_scale();
    button_x = button_x + width2 + frame_padding;
  }
  if ((civ_saved_cursor_x_block.autoplay_active == 0) || (self->show_turn_status == 0)) {
    if ((((uint)game.human_players & 1 << (game.turn_civ & 0x1fU)) == 0) || (self->show_turn_timer == 0))
    {
      self->timer_text = '\0';
    }
    else if (self->timer_last_value != (*(u32 *)&mp_turn_seconds_left)) {
      if (self->timer_last_value == 0xffffffff) {
        self->timer_last_value = civ_saved_cursor_x_block.mp_turn_time_limit_ms / 1000;
      }
      else {
        self->timer_last_value = (*(u32 *)&mp_turn_seconds_left);
      }
      if ((int)self->timer_last_value < 0) {
        self->timer_last_value = 0;
      }
      minutes = (int)(self->timer_last_value - 1) / 0x3c;
      seconds = (self->timer_last_value - 1) + minutes * -0x3c;
      if (minutes < 10) {
        self->timer_text = '0';
        __itoa(minutes,(char *)self->timer_minutes_text,10);
      }
      else {
        __itoa(minutes,(char *)&self->timer_text,10);
      }
      self->timer_colon = ':';
      if (seconds < 10) {
        if (seconds < 0) {
          seconds = 0;
        }
        self->timer_seconds_text = '0';
        __itoa(seconds,(char *)self->timer_seconds_digits,10);
      }
      else {
        __itoa(seconds,(char *)&self->timer_seconds_text,10);
      }
    }
  }
  else if ((int)civ_saved_cursor_x_block.autoplay_turns_left != self->timer_last_value) {
    self->timer_last_value = (int)civ_saved_cursor_x_block.autoplay_turns_left;
    __itoa((int)civ_saved_cursor_x_block.autoplay_turns_left,(char *)&self->timer_text,10);
  }
  crt_strcpy(caption,(const char *)self->frame_title);
  if (((self->show_turn_status == 0) || (game.multiplayer == '\0')) || (net_session_block.mp_simultaneous_moves != '\0')) {
    if (((self->show_turn_status != 0) && (game.multiplayer != '\0')) && (net_session_block.mp_simultaneous_moves != '\0')) {
      if ((1 << ((*(byte *)&net_session_block.mp_turn_civ) & 0x1f) & (uint)game.human_players) == 0) {
        crt_strcat(caption,((i8 *)&caption_simul_open_paren_str));
        if (game_language == 1) {
          crt_strcat(caption,((i8 *)&caption_simul_ai_fr_str));
        }
        else {
          crt_strcat(caption,((i8 *)&caption_simul_ai_str));
        }
        crt_strcat(caption,((i8 *)&caption_simul_space_str));
        str_append_label((iptr)caption,0x369);
        if (self->timer_text != '\0') {
          crt_strcat(caption,((i8 *)&caption_simul_timer_sep_str));
          crt_strcat(caption,(const char *)(&self->timer_text));
        }
        crt_strcat(caption,((i8 *)&caption_simul_close_paren_str));
      }
      else if (self->timer_text != '\0') {
        crt_strcat(caption,((i8 *)&caption_timer_open_paren_str));
        crt_strcat(caption,(const char *)(&self->timer_text));
        crt_strcat(caption,((i8 *)&caption_timer_close_paren_str));
      }
    }
  }
  else {
    crt_strcat(caption,((i8 *)&caption_status_open_paren_str));
    if ((((*(byte *)&civs[human_civ[0]].treaties[net_session_block.mp_turn_civ] & 1) == 0) &&
        (net_session_block.mp_turn_civ != human_civ[0])) &&
       ((game.multiplayer != 1 || ((1 << ((*(byte *)&net_session_block.mp_turn_civ) & 0x1f) & (uint)net_session_block.hotseat_human_players) == 0)))) {
      if ((1 << ((*(byte *)&net_session_block.mp_turn_civ) & 0x1f) & (uint)game.human_players) == 0) {
        if (game_language == 1) {
          crt_strcat(caption,((i8 *)&caption_ai_fr_str));
        }
        else {
          crt_strcat(caption,((i8 *)&caption_ai_str));
        }
        if (civ_saved_cursor_x_block.autoplay_active == 0) {
          self->timer_text = '\0';
        }
      }
      else {
        crt_strcat(caption,((i8 *)&net_session_block.net_slot_player_names) + net_session_block.net_civ_slots[net_session_block.mp_turn_civ] * 0x54);
      }
    }
    else {
      adjective = civ_adjective(net_session_block.mp_turn_civ);
      crt_strcat((char *)((void *)caption),(const char *)((void *)adjective));
      if (((1 << ((*(byte *)&net_session_block.mp_turn_civ) & 0x1f) & (uint)game.human_players) == 0) && (civ_saved_cursor_x_block.autoplay_active == 0)) {
        self->timer_text = '\0';
      }
    }
    crt_strcat(caption,((i8 *)&caption_moves_space_str));
    str_append_label((iptr)caption,0x369);
    if (self->timer_text != '\0') {
      crt_strcat(caption,((i8 *)&caption_timer_sep_str));
      crt_strcat(caption,(const char *)(&self->timer_text));
    }
    crt_strcat(caption,((i8 *)&caption_close_paren_str));
  }
  width2 = rect_width((RECT *)&self->frame_rect);
  text_width = font_text_width((GameFont *)self->title_font,(const char *)caption);
  text_width += 4;
  text_x2 = (width2 >> 1) - (text_width >> 1);
  text_y2 = bevel + 1;
  font2 = (GameFont *)self->title_font;
  if (text_x2 < button_x) {
    text_x2 = button_x;
  }
  if (width2 < text_width + text_x2) {
    font2 = (GameFont *)self->title_small_font;
    text_width = font_text_width(font2,(const char *)caption);
    text_width += 4;
    text_x2 = (width2 >> 1) - (text_width >> 1);
    if (text_x2 < button_x) {
      text_x2 = button_x;
    }
    title_height = font_cached_height((GameFont *)self->title_font);
    small_height = font_cached_height(font2);
    text_y2 += (title_height - small_height >> 1);
    while ((len = _strlen(caption), len != 0 &&
           (title_height = font_text_width(font2,(const char *)caption),
           width2 < text_x2 + title_height + 4))) {
      len2 = _strlen(caption);
      caption[len2 - 1] = '\0';
    }
  }
  gfx_set_text_color_index(10);
  surface_draw_text
            ((DibSurface *)self,(iptr)font2,(const char *)caption,text_x2 + 2,text_y2 + 1,5);
  gfx_set_text_color_index(0x1a);
  surface_draw_text
            ((DibSurface *)self,(iptr)font2,(const char *)caption,text_x2 + 1,text_y2,5);
  surface_draw_text
            ((DibSurface *)self,(iptr)font2,(const char *)caption,text_x2,text_y2,5);
  surface_set_clip((DibSurface *)self,(RECT *)&self->client_rect);
  return;
}

/* 00552e5b auto */
void __cdecl frame_wnd_on_caption_button_click(int button_id)

{
  iptr child;
  iptr frame_wnd;
  
  child = wnd_get_active_child();
  if (child == 0) {
    frame_wnd = 0;
  }
  else {
    frame_wnd = child - 0x48;
  }
  if (*(int *)(frame_wnd + 0x2a8) != 0) {
    call_untyped(((code **)frame_wnd)[170], *(i32 *)(frame_wnd + 0x200 + (button_id - 1000) * 0x1c));
  }
  return;
}

/* 00552ed2 auto */
void __thiscall frame_wnd_layout(FrameWindow *self)

{
  int width;
  int height;
  u32 size;
  Control *this_00;
  u8 *native_wnd2;
  Control *hotspot;
  int button_x;
  int i;
  i8 button_rect[16];
  i32 eh_prev;
  i8 *eh_handler;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  width = surface_get_width((DibSurface *)self);
  height = surface_get_height((DibSurface *)self);
  rect_set_xywh((iptr)&self->frame_rect,0,0,width,height);
  rect_set_xywh((iptr)&self->client_rect,0,0,width + self->border_width * -2,
                     height - (self->caption_height + self->border_width));
  rect_offset((iptr)&self->client_rect,self->border_width,self->caption_height);
  self->client_x = self->client_rect;
  self->client_y = self->client_top;
  size = rect_width((RECT *)&self->client_rect);
  self->client_width = size;
  size = rect_height((RECT *)&self->client_rect);
  self->client_height = size;
  frame_wnd_destroy_caption_buttons((WindowObjectView *)self);
  button_x = frame_border_width;
  for (i = 0; i < (int)self->caption_button_count; i++) {
    width = (int)(*(int *)(self->pane_selection_flags_area + i * 0x1c + 0xc) * self->caption_height) / 0x18;
    height = (int)(*(int *)(self->pane_selection_flags_area + i * 0x1c + 0x10) * self->caption_height) / 0x18;
    rect_set_xywh((iptr)button_rect,button_x,((int)self->caption_height >> 1) - (height >> 1),width,
                       height);
    this_00 = (Control *)operator_new(0x40);
    eh_state = 0;
    if (this_00 == (Control *)0x0) {
      hotspot = 0;
    }
    else {
      hotspot = hotspot_ctor(this_00);
    }
    eh_state = 0xffffffff;
    *(i32 *)(self->pane_selection_flags_area + i * 0x1c + 0x18) = (i32)hotspot;
    if (self == (FrameWindow *)0x0) {
      native_wnd2 = (u8 *)0x0;
    }
    else {
      native_wnd2 = self->window_2;
    }
    hotspot_create
              (*(ClickControl **)(self->pane_selection_flags_area + i * 0x1c + 0x18),(iptr)native_wnd2,
               i + 1000,(iptr)button_rect);
    hotspot_set_click_callback
              (*(HotspotClickSetView **)(self->pane_selection_flags_area + i * 0x1c + 0x18),(iptr)frame_wnd_on_caption_button_click);
    button_x = button_x + width + frame_padding;
  }
  return;
}

/* 0055318c auto */
void __thiscall frame_wnd_add_caption_button(PortraitDialog *self,iptr sprite,i32 callback)

{
  u8 *slot;
  u32 index;
  i32 dim;
  
  if ((int)self->caption_button_count < 6) {
    index = self->caption_button_count;
    self->caption_button_count++;
    *(iptr *)(((FrameWindow *)self)->close_caption_sprite_slot + index * 0x1c - 0x3c) = sprite;
    *(i32 *)(self->pane_selection_flags_area + index * 0x1c) = callback;
    dim = sprite_width((Sprite *)sprite);
    *(i32 *)(((FrameWindow *)self)->close_caption_sprite_slot + index * 0x1c - 0x44) = dim;
    dim = sprite_height((Sprite *)sprite);
    *(i32 *)(((FrameWindow *)self)->close_caption_sprite_slot + index * 0x1c - 0x40) = dim;
    slot = ((FrameWindow *)self)->close_caption_sprite_slot + index * 0x1c - 0x38;
    slot[0] = '\0';
    slot[1] = '\0';
    slot[2] = '\0';
    slot[3] = '\0';
  }
  return;
}

/* 0055324c auto */
void __thiscall frame_wnd_set_caption(FrameWindow *self,const char *title)

{
  struct { u32 left; u32 top; u32 right; u32 bottom; } rect2;
  
  _memset(self->frame_title,0,0x84);
  _strncpy((char *)self->frame_title,(char *)title,0x83);
  frame_wnd_draw_caption(self);
  rect2.left = self->frame_rect;
  rect2.top = self->frame_top;
  rect2.right = self->frame_right;
  rect2.bottom = self->client_top;
  wnd_blit_surface_rect((DibSurface *)self,(iptr)&rect2);
  return;
}

/* 005532d7 auto */
void __thiscall frame_wnd_destroy_caption_buttons(WindowObjectView *self)

{
  int i;
  
  for (i = 0; i < 6; i++) {
    if (((u32 *)&((PediaRedrawView *)self)->caption_button_slots)[i * 7] != 0) {
      if ((Hotspot *)((u32 *)&((PediaRedrawView *)self)->caption_button_slots)[i * 7] != (Hotspot *)0x0) {
        hotspot_scalar_dtor((Hotspot *)((u32 *)&((PediaRedrawView *)self)->caption_button_slots)[i * 7],1);
      }
      ((u32 *)&((PediaRedrawView *)self)->caption_button_slots)[i * 7] = 0;
    }
  }
  return;
}

/* 00553379 auto */
void __thiscall frame_wnd_close(DibSurface *self)

{
  frame_wnd_destroy_caption_buttons((WindowObjectView *)self);
  wnd_destroy_with_surface(self);
  return;
}

/* 0055339f auto */
SurfaceWindow * __thiscall frame_wnd_ctor(SurfaceWindow *self)

{
  u8 *slot;
  int i;
  i32 eh_prev;
  i8 *eh_handler;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  surfwnd_ctor(self);
  self->vtable = (u32)((pointer *)&leader_anim_frame_starts_block.ptr_fun_3 + 7);
  for (i = 0; i < 6; i++) {
    slot = (u8 *)&((PediaRedrawView *)self)->caption_button_slots + i * 0x1c;
    slot[0] = '\0';
    slot[1] = '\0';
    slot[2] = '\0';
    slot[3] = '\0';
  }
  return self;
}

/* 00553444 auto */
/* Library Function - Single Match
    public: virtual __thiscall COleCntrFrameWnd::~COleCntrFrameWnd(void)
   
   Library: Visual Studio 1998 Debug */

void __thiscall frame_wnd_dtor(DibSurface *self)

{
  i32 eh_prev;
  i8 *eh_handler;
  i32 eh_state;
  
  self->vtable = (u32)((pointer *)&leader_anim_frame_starts_block.ptr_fun_3 + 7);
  eh_state = 0;
  frame_wnd_destroy_caption_buttons((WindowObjectView *)self);
  wnd_destroy_with_surface(self);
  eh_state = 0xffffffff;
  /* inlined unwind funclet 0055349b */ { surfwnd_dtor(*(SurfaceWindow **)&self); }
  return;
}

/* 005534bc auto */
void __thiscall
frame_wnd_create
          (FrameWindow *self,const char *title,uint flags,int x,int y,int width,
          int height,u32 resize_width,u32 caption_h,u32 border_w)

{
  uint wnd_style;
  
  if (title == 0) {
    crt_strcpy((char *)self->frame_title,((i8 *)&frame_default_title_str));
  }
  else {
    crt_strcpy((char *)((void *)self->frame_title),(const char *)((void *)title));
  }
  *(i8 **)self->editor_combo_boxes = ((i8 *)&ui_text_font);
  self->title_font = (uptr)((i8 *)&caption_font_block.caption_font);
  self->title_small_font = (uptr)((i8 *)&caption_small_font_block.caption_small_font);
  self->show_turn_timer = 0;
  self->show_turn_status = 0;
  self->style_flags = flags;
  self->caption_height = caption_h;
  self->border_width = border_w;
  self->resize_border = resize_width;
  self->caption_button_count = 0;
  self->on_caption_button = 0;
  if ((flags & 4) != 0) {
    self->caption_height = (*(u32 *)&frame_caption_height);
    self->border_width = (*(u32 *)&frame_border_width);
  }
  if ((flags & 8) == 0) {
    wnd_style = 0x202;
  }
  else {
    wnd_style = 0x802;
  }
  if (self->caption_height != 0) {
    wnd_style = wnd_style | 0x400;
  }
  if (self->resize_border != 0) {
    wnd_style = wnd_style | 0x1000;
  }
  if ((flags & 2) == 0) {
    width += self->border_width * 2;
    height = height + self->caption_height + self->border_width;
  }
  if ((flags & 1) != 0) {
    x = (caption_font_block.screen_width >> 1) - (width >> 1);
    y = (caption_font_block.screen_height >> 1) - (height >> 1);
  }
  wnd_create_with_surface
            ((DibSurface *)self,0,wnd_style,x,y,width,height,(iptr)&game_palette_block.game_palette,(iptr)&main_frame_wnd_block.main_frame_wnd);
  if (self->caption_height != 0) {
    wnd_set_caption_height((WndBase *)self->window_2,self->caption_height);
  }
  if (self->resize_border != 0) {
    wnd_set_resize_border((WndBase *)self->window_2,self->resize_border);
  }
  frame_wnd_layout(self);
  wnd_set_drag_begin_callback((WndDragBeginSetView *)self->event_handlers,(iptr)mp_window_drag_begin);
  wnd_set_drag_end_callback((WndDragEndSetView *)self->event_handlers,(iptr)mp_window_drag_end);
  return;
}

/* 00553d30 auto */
u32 __thiscall wnd_set_drag_begin_callback(WndDragBeginSetView *self,iptr callback)

{
  u32 old_callback;
  
  old_callback = self->on_drag_begin;
  self->on_drag_begin = callback;
  return old_callback;
}

/* 00553d70 auto */
u32 __thiscall wnd_set_drag_end_callback(WndDragEndSetView *self,iptr callback)

{
  u32 old_callback;
  
  old_callback = self->on_drag_end;
  self->on_drag_end = callback;
  return old_callback;
}

/* 0056810b auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl frame_texture_surface_global_init(void)

{
  frame_texture_surface_static_init();
  frame_texture_surface_reg_atexit();
  return;
}

/* 00568125 auto */
void __cdecl frame_texture_surface_static_init(void)

{
  surface_ctor((DibSurface *)((i8 *)&frame_texture_surface_block.frame_texture_surface));
  return;
}

/* 0056813f auto */
void __cdecl frame_texture_surface_reg_atexit(void)

{
  _atexit(frame_texture_surface_static_dtor);
  return;
}

/* 0056815c auto */
void __cdecl frame_texture_surface_static_dtor(void)

{
  surface_dtor((DibSurface *)((i8 *)&frame_texture_surface_block.frame_texture_surface));
  return;
}

/* 005681c9 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl frame_texture_load(void)

{
  int ok;
  i8 sprite_rect[16];
  DllHandle dll;
  DibSurface surface;
  i8 path[128];
  Sprite sprite;
  i32 eh_prev;
  i8 *eh_handler;
  int eh_state;
  
  eh_state = 0xffffffff;
  gfx_build_grey_remap();
  surface_ctor(&surface);
  eh_state = 0;
  sprite_init(&sprite);
  (*((char *)&eh_state + 0)) = 1;
  frame_texture_loaded_i32 = 1;
  str_clear((char *)path);
  str_append((char *)path,(const char *)&str_civ2_civ2art_dll_4);
  ok = file_resolve_path((const char *)path);
  if (ok == 0) {
    surface_create((DibSurface *)((i8 *)&frame_texture_surface_block.frame_texture_surface),0x40,0x20);
    surface_fill((DibSurface *)((i8 *)&frame_texture_surface_block.frame_texture_surface),0x21);
  }
  else {
    resource_dll_load(&dll,(iptr)path);
    eh_state = (eh_state & 0xffffff00 | (byte)(2));
    ok = surface_load_gif_resource(&surface,999,10,0xec,(iptr)&art_palette);
    if (ok == 0) {
      MessageBoxA((HWND)0x0,str_failed_to_load_civ2art_gif_2,str_notice_15,0x40);
    }
    else {
      sprite_grab_from_surface(&sprite,(iptr)&surface,2,1,1,0x40,0x20);
      surface_create((DibSurface *)((i8 *)&frame_texture_surface_block.frame_texture_surface),0x40,0x20);
      sprite_draw(&sprite,(iptr)sprite_rect,(iptr)&frame_texture_surface_block.frame_texture_surface,0,0);
      sprite_free(&sprite);
      surface_release(&surface);
    }
    dll_handle_free(&dll);
    (*((char *)&eh_state + 0)) = 1;
    /* inlined unwind funclet 00568348 */ { dll_free(&dll); }
  }
  frame_texture_load_hook_nop();
  eh_state = eh_state & 0xffffff00;
  /* inlined unwind funclet 00568354 */ { sprite_destroy(&sprite); }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 0056835d */ { surface_dtor(&surface); }
  return;
}

/* 00568381 auto */
void __cdecl frame_texture_free(void)

{
  surface_release((DibSurface *)((i8 *)&frame_texture_surface_block.frame_texture_surface));
  gfx_free_grey_remap();
  frame_texture_free_hook_nop();
  return;
}

/* 005683a5 auto */
void __cdecl frame_texture_load_hook_nop(void)

{
  return;
}

/* 005683b5 auto */
void __cdecl frame_texture_free_hook_nop(void)

{
  return;
}

/* 005785d0 auto */
/* Library Function - Single Match
    public: int __thiscall ios_base::precision(int)
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall wnd_set_rbuttondown_handler(WndHandlersMouseSetView *self,iptr handler)

{
  u32 old_handler;
  
  old_handler = ((WndHandlersMouseSetViewExt *)self)->on_rbutton_down;
  ((WndHandlersMouseSetViewExt *)self)->on_rbutton_down = handler;
  return old_handler;
}

/* 00578610 auto */
/* Library Function - Single Match
    public: int __thiscall ios_base::width(int)
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall wnd_set_rbuttonup_any_handler(WndHandlersMouseSetView *self,iptr handler)

{
  u32 old_handler;
  
  old_handler = ((WndHandlersMouseSetViewExt *)self)->on_rbutton_up_any;
  ((WndHandlersMouseSetViewExt *)self)->on_rbutton_up_any = handler;
  return old_handler;
}

/* 00578650 auto */
void __thiscall menu_storage_reinit(GameMenu *self,uint size)

{
  memblock_free((iptr)self->item_storage);
  memblock_init((iptr)self->item_storage,0xb,size);
  return;
}

/* 0057868c auto */
/* Library Function - Single Match
    public: virtual void __thiscall CHtmlStream::Reset(void)
   
   Library: Visual Studio 1998 Debug */

void __thiscall menu_clear_lists(GameMenu *self)

{
  self->menus = 0;
  self->menu_flags = 0;
  return;
}

/* 005786b6 auto */
void __thiscall menu_reset(GameMenu *self,i32 size)

{
  memblock_detach((iptr)self->item_storage);
  menu_clear_lists(self);
  menu_storage_reinit(self,size);
  return;
}

/* 005786f1 auto */
GameMenu * __thiscall menu_ctor(GameMenu *self,i32 size)

{
  i32 eh_prev;
  i8 *eh_handler;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  menu_handle_ctor(self);
  eh_state = 0;
  memblock_ctor((MemBlock *)self->item_storage);
  menu_reset(self,size);
  return self;
}

/* 00578770 auto */
void __thiscall menu_dtor(GameMenu *self)

{
  i32 eh_prev;
  i8 *eh_handler;
  i32 eh_state;
  
  eh_state = 0;
  memblock_free((iptr)self->item_storage);
  eh_state = 0xffffffff;
  /* inlined unwind funclet 005787bd */ { menu_handle_dtor(*&self); }
  return;
}

/* 005787de auto */
MenuNode * __thiscall menu_find_menu(GameMenu *self,int menu_id)

{
  MenuNode *menu2;
  
  menu2 = self->menus;
  while( true ) {
    if (menu2 == 0) {
      return 0;
    }
    if (menu2->id == menu_id) break;
    menu2 = menu2->next;
  }
  return menu2;
}

/* 00578840 auto */
int __thiscall menu_visible_index(GameMenu *self,MenuNode *menu)

{
  int index;
  MenuNode *cur;
  
  index = 1;
  for (cur = self->menus; (cur != 0 && ((uptr)menu != (uptr)cur));
      cur = cur->next) {
    if ((cur->flags_byte & 2) == 0) {
      index++;
    }
  }
  return index;
}

/* 005788a9 auto */
i32 __thiscall menu_id_at_visible_index(GameMenu *self,int visible_index)

{
  int index;
  MenuNode *menu2;
  
  index = 1;
  menu2 = self->menus;
  do {
    if (menu2 == 0) {
      return 0xffffffff;
    }
    if ((menu2->flags_byte & 2) == 0) {
      if (index == visible_index) {
        return menu2->id;
      }
      index++;
    }
    menu2 = menu2->next;
  } while( true );
}

/* 00578922 auto */
MenuNode * __thiscall menu_find_item(GameMenu *self,int item_id)

{
  MenuNode *menu2;
  MenuNode *item;
  MenuNode *found;
  
  found = 0;
  menu2 = self->menus;
  do {
    if (menu2 == 0) {
      return found;
    }
    for (item = menu2->link; item != 0; item = item->next) {
      if (item->id == item_id) {
        found = item;
        break;
      }
    }
    menu2 = menu2->next;
  } while( true );
}

/* 005789aa auto */
int __thiscall menu_item_visible_index(GameMenu *self,MenuNode *item)

{
  int index;
  iptr cur;
  
  index = 1;
  for (cur = *(iptr *)((int)item->link + 0x18); (cur != 0 && ((iptr)item != cur));
      cur = *(iptr *)(cur + 0x10)) {
    if ((*(byte *)(cur + 8) & 2) == 0) {
      index++;
    }
  }
  return index;
}

/* 00578a1c auto */
i32 __thiscall menu_item_id_at_visible_index(GameMenu *self,i32 menu_id,int visible_index)

{
  MenuNode *menu;
  int index;
  MenuNode *item;
  
  index = 1;
  menu = menu_find_menu(self,menu_id);
  if (menu != 0) {
    for (item = menu->link; item != 0; item = item->next) {
      if ((item->flags_byte & 2) == 0) {
        if (index == visible_index) {
          return item->id;
        }
        index++;
      }
    }
  }
  return 0xffffffff;
}

/* 00578b06 auto */
MenuNode * __thiscall menu_add_menu(GameMenu *self,i32 menu_id,char *title)

{
  MenuNode *menu;
  size_t len;
  i32 text;
  MenuNode *last;
  
  menu = (MenuNode *)memblock_alloc((iptr)self->item_storage,0x1c);
  if (self->menus == 0) {
    self->menus = menu;
    menu->prev = 0;
  }
  else {
    for (last = self->menus; (int)last->next != 0;
        last = last->next) {
    }
    last->next = menu;
    menu->prev = last;
  }
  menu->next = 0;
  menu->link = 0;
  menu->flags = 0;
  menu->id = menu_id;
  menu->field_0c = 0;
  len = _strlen(title);
  text = memblock_alloc((iptr)self->item_storage,len + 1);
  menu->text = (char *)text;
  crt_strcpy((char *)((void *)menu->text),(const char *)((void *)title));
  str_pipes_to_tabs(menu->text);
  self->menu_flags = self->menu_flags & 0xffff7fff;
  return menu;
}

/* 00578c12 auto */
MenuNode * __thiscall
menu_add_item
          (GameMenu *self,i32 menu_id,i32 item_id,const char *text,size_t min_len)

{
  MenuNode *menu;
  size_t len;
  i32 buffer;
  size_t buf_len;
  MenuNode *item;
  MenuNode *last;
  
  item = (MenuNode *)0x0;
  menu = menu_find_menu(self,menu_id);
  if (menu != 0) {
    item = (MenuNode *)memblock_alloc((iptr)self->item_storage,0x1c);
    if (menu->link == 0) {
      menu->link = item;
      item->prev = 0;
    }
    else {
      for (last = menu->link; (int)last->next != 0;
          last = last->next) {
      }
      last->next = item;
      item->prev = last;
    }
    item->link = menu;
    item->next = 0;
    item->flags = 0;
    item->id = item_id;
    item->field_0c = 0;
    if (text == 0) {
      item->text = 0;
    }
    else {
      len = _strlen((char *)text);
      if ((int)len < (int)min_len) {
        buf_len = min_len;
      }
      else {
        buf_len = _strlen((char *)text);
      }
      buffer = memblock_alloc((iptr)self->item_storage,buf_len + 1);
      item->text = (char *)buffer;
      crt_strcpy((char *)((void *)item->text),(const char *)((void *)text));
      str_pipes_to_tabs(item->text);
    }
    self->menu_flags = self->menu_flags & 0xffff7fff;
  }
  return item;
}

/* 00578d8a auto */
void __cdecl menu_dispatch_command(i32 menu_index,i32 item_index)

{
  i32 menu_id;
  i32 item_id;
  
  if (menu_command_callback != (code *)0x0) {
    menu_id = menu_id_at_visible_index(menu_active_object,menu_index);
    item_id = menu_item_id_at_visible_index(menu_active_object,menu_id,item_index);
    call_untyped(menu_command_callback, menu_id,item_id);
  }
  return;
}

/* 00578de8 auto */
void __thiscall menu_attach_to_window(GameMenu *self,ModalMenuWindow *window)

{
  if (window != (ModalMenuWindow *)0x0) {
    menu_owner_window = window;
    menu_active_object = self;
    wnd_attach_menu(window,(iptr)self);
    wnd_set_menu_callback((WndMenuCbSetView *)window,(iptr)menu_dispatch_command);
  }
  return;
}

/* 00578e38 auto */
void __thiscall menu_set_command_handler(GameMenu *self,iptr handler)

{
  menu_active_object = self;
  (*(iptr *)&menu_command_callback) = handler;
  return;
}

/* 00578e60 auto */
i32 __thiscall menu_apply_item_enabled(GameMenu *self,i32 item_id)

{
  MenuNode *item;
  uint enabled;
  i32 result;
  i32 menu_index;
  
  item = menu_find_item(self,item_id);
  if (item == 0) {
    result = 0;
  }
  else {
    enabled = ~item->flags & 1;
    result = menu_item_visible_index(self,item);
    menu_index = menu_visible_index(self,item->link);
    result = menu_native_enable(self,menu_index,result,enabled);
  }
  return result;
}

/* 00578ec7 auto */
void __thiscall menu_apply_item_checked(GameMenu *self,i32 item_id)

{
  MenuNode *item;
  uint checked;
  i32 item_index;
  i32 menu_index;
  
  item = menu_find_item(self,item_id);
  if (item != 0) {
    checked = item->flags & 4;
    item_index = menu_item_visible_index(self,item);
    menu_index = menu_visible_index(self,item->link);
    menu_native_check(self,menu_index,item_index,checked);
  }
  return;
}

/* 00578f2c auto */
void __thiscall menu_rebuild(GameMenu *self,iptr window)

{
  i32 *menu2;
  int menu_index;
  int item_index;
  i32 *item;
  int i;
  i8 spec[256];
  
  if ((self->menu_flags & 0x8000) == 0) {
    spec[0] = 0;
    menu2 = (i32 *)self->menus;
    menu_index = 1;
    for (; menu2 != (i32 *)0x0; menu2 = (i32 *)menu2[4]) {
      if ((*(byte *)(menu2 + 2) & 2) == 0) {
        crt_strcat((char *)((void *)spec),(const char *)((void *)*menu2));
        crt_strcat(spec,((i8 *)&menu_title_sep_str));
      }
      if (window == 0) {
        for (i = 0x1e; 0 < i; i--) {
          menu_native_delete(self,menu_index,i);
        }
        menu2[3] = 0;
      }
      menu_index++;
    }
    if (window != 0) {
      menu_native_build(self,(iptr)spec);
    }
    menu2 = (i32 *)self->menus;
    menu_index = 1;
    for (; menu2 != (i32 *)0x0; menu2 = *(i32 **)((int)menu2 + 0x10)) {
      if ((*(byte *)((int)menu2 + 8) & 2) == 0) {
        if (window != 0) {
          menu_native_delete(self,menu_index,1);
        }
        item = *(i32 **)((int)menu2 + 0x18);
        item_index = 1;
        for (; item != (i32 *)0x0; item = (i32 *)item[4]) {
          if ((*(byte *)(item + 2) & 2) == 0) {
            *(int *)((int)menu2 + 0xcU) = *(int *)((int)menu2 + 0xcU) + 1;
            menu_native_insert(self,menu_index,item_index,(const char *)(*item));
            if ((*(byte *)(item + 2) & 1) != 0) {
              menu_apply_item_enabled(self,item[1]);
            }
            if ((*(byte *)(item + 2) & 4) != 0) {
              menu_apply_item_checked(self,item[1]);
            }
            item_index++;
          }
        }
        menu_index++;
      }
    }
    self->menu_flags = self->menu_flags | 0x8000;
    menu_attach_to_window(self,(ModalMenuWindow *)window);
  }
  if (menu_owner_window != (ModalMenuWindow *)0x0) {
    wnd_redraw_menu_bar(menu_owner_window);
  }
  return;
}

/* 00579260 auto */
void __thiscall menu_set_item_hidden(GameMenu *self,i32 item_id,int hidden)

{
  MenuNode *item;
  
  item = menu_find_item(self,item_id);
  if (item != 0) {
    if (hidden == 0) {
      if ((item->flags_byte & 2) != 0) {
        self->menu_flags = self->menu_flags & 0xffff7fff;
      }
      item->flags = item->flags & 0xfffffffd;
    }
    else {
      if ((item->flags_byte & 2) == 0) {
        self->menu_flags = self->menu_flags & 0xffff7fff;
      }
      item->flags = item->flags | 2;
    }
  }
  return;
}

/* 005792e1 auto */
GameMenu * __thiscall
menu_set_item_enabled(GameMenu *self,i32 item_id,int enabled)

{
  GameMenu *item;
  GameMenu *ret_val;
  int was_enabled;
  
  item = (GameMenu *)menu_find_item(self,item_id);
  ret_val = item;
  if (item != (GameMenu *)0x0) {
    enabled = enabled != 0;
    was_enabled = (item->item_storage[4] & 1) != 0;
    if (enabled == 0) {
      *(uint *)item->item_flags = *(uint *)(item->item_flags) & 0xfffffffe;
    }
    else {
      *(uint *)item->item_flags = *(uint *)item->item_flags | 1;
    }
    ret_val = self;
    if ((((self->menu_flags & 0x8000) != 0) && (ret_val = item, (item->item_storage[4] & 2) == 0)) &&
       (ret_val = (GameMenu *)enabled, was_enabled != enabled)) {
      ret_val = (GameMenu *)menu_apply_item_enabled(self,item_id);
    }
  }
  return ret_val;
}

/* 005793a3 auto */
void __thiscall menu_remove_item(GameMenu *self,i32 item_id)

{
  MenuNode *item;
  i32 item_index;
  i32 menu_index;
  
  item = menu_find_item(self,item_id);
  if (item != 0) {
    item_index = menu_item_visible_index(self,item);
    menu_index = menu_visible_index(self,item->link);
    menu_native_delete(self,menu_index,item_index);
    *(i32 *)((int)item->prev + 0x10) = (i32)item->next;
  }
  return;
}

/* 0057940d auto */
void __thiscall menu_set_item_checked(GameMenu *self,i32 item_id,int checked)

{
  byte old_flags;
  MenuNode *item;
  
  item = menu_find_item(self,item_id);
  if (item != 0) {
    old_flags = item->flags_byte;
    if (checked != 0) {
      item->flags = item->flags | 4;
    }
    else {
      item->flags = item->flags & 0xfffffffb;
    }
    if ((((self->menu_flags & 0x8000) != 0) && ((item->flags_byte & 2) == 0)) &&
       (((old_flags & 4) != 0) != (checked != 0))) {
      menu_apply_item_checked(self,item_id);
    }
  }
  return;
}

/* 005794cf auto */
void __thiscall menu_set_menu_enabled(GameMenu *self,i32 menu_id,i32 enabled)

{
  MenuNode *menu;
  MenuNode *item;
  
  menu = menu_find_menu(self,menu_id);
  if (menu != 0) {
    for (item = menu->link; item != 0; item = item->next) {
      menu_set_item_enabled(self,item->id,enabled);
    }
  }
  return;
}

/* 0057953e auto */
void __thiscall menu_set_item_text(GameMenu *self,i32 item_id,const char *text)

{
  MenuNode *item;
  i32 item_index;
  i32 menu_index;
  i32 item_text;
  
  item = menu_find_item(self,item_id);
  if (item != (MenuNode *)0x0) {
    crt_strcpy((char *)((void *)item->text),(const char *)((void *)text));
    str_pipes_to_tabs(item->text);
    if (((self->menu_flags & 0x8000) != 0) && ((item->flags_byte & 2) == 0)) {
      item_text = (i32)item->text;
      item_index = menu_item_visible_index(self,item);
      menu_index = menu_visible_index(self,item->link);
      menu_native_set_text(self,menu_index,item_index,(const char *)item_text);
    }
  }
  return;
}

/* 005799c0 auto */
void __thiscall menu_native_build(GameMenu *self,iptr spec)

{
  u32 menu_handle;
  
  menu_handle = menu_hmenu_build_from_spec((char *)spec);
  self->hmenu = menu_handle;
  return;
}

/* 00579a00 auto */
void __thiscall
menu_native_insert(GameMenu *self,i32 menu_index,i32 item_index,const char *text)

{
  menu_hmenu_insert_item(self->hmenu,menu_index,item_index,text);
  return;
}

/* 00579a40 auto */
void __thiscall menu_native_delete(GameMenu *self,i32 menu_index,i32 item_index)

{
  menu_hmenu_delete_item(self->hmenu,menu_index,item_index);
  return;
}

/* 00579a80 auto */
void __thiscall
menu_native_set_text(GameMenu *self,i32 menu_index,i32 item_index,const char *text)

{
  menu_hmenu_set_item_text(self->hmenu,menu_index,item_index,text);
  return;
}

/* 00579ac0 auto */
i32 __thiscall
menu_native_enable(GameMenu *self,i32 menu_index,i32 item_index,i32 enabled)

{
  i32 result;
  
  result = menu_hmenu_enable_item(self->hmenu,menu_index,item_index,enabled);
  return result;
}

/* 00579b00 auto */
void __thiscall
menu_native_check(GameMenu *self,i32 menu_index,i32 item_index,i32 checked)

{
  menu_hmenu_check_item(self->hmenu,menu_index,item_index,checked);
  return;
}

/* 00579b40 auto */
void __thiscall wnd_attach_menu(ModalMenuWindow *self,iptr menu_obj)

{
  i32 hmenu;
  NativeWindow *hwnd;
  
  hmenu = menu_get_hmenu((MenuHandleView *)menu_obj);
  hwnd = wnd_get_window((WndBase *)self);
  wnd_obj_attach_menu(hwnd,hmenu);
  self->menu = menu_obj;
  return;
}

/* 00579b90 auto */
u32 __thiscall menu_get_hmenu(MenuHandleView *self)

{
  return self->hmenu;
}

/* 00579bc0 auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall wnd_set_menu_callback(WndMenuCbSetView *self,iptr callback)

{
  self->on_menu = callback;
  return;
}

/* 00579bf0 auto */
void __thiscall wnd_redraw_menu_bar(ModalMenuWindow *self)

{
  NativeWindow *hwnd;
  
  if (self->menu != 0) {
    hwnd = wnd_get_window((WndBase *)self);
    menu_redraw_bar(hwnd);
  }
  return;
}

/* 00589d50 auto */
i32 __thiscall wnd_frame_width(WndBase *self)

{
  i32 width;
  
  width = wnd_obj_frame_width(self->native_wnd);
  return width;
}

/* 0058bd60 auto */
void __cdecl cmd_unit_skip_turn(void)

{
  unit_move_dir((int)game.active_unit,0xffffffff,3);
  return;
}

/* 0058bd84 auto */
void __cdecl cmd_end_player_turn(void)

{
  iptr unit;
  
  for (unit = 0; unit < game.num_units; unit++) {
    if ((units[unit].id != 0) && (units[unit].owner == human_civ[0])) {
      unit_exhaust_moves(unit);
    }
  }
  return;
}

/* 0058d442 auto */
void __cdecl ui_pick_unit_from_stack(void)

{
  int stack_count;
  iptr prompt;
  i32 dialog_flags;
  iptr unit;
  
  unit_blink_active = 0;
  if (moving_units_mode == 1) {
    unit = (iptr)game.active_unit;
    if (units[unit].id == 0) {
      unit_blink_active = 0;
      return;
    }
    if (units[unit].owner != human_civ[0]) {
      unit_blink_active = 0;
      return;
    }
    stack_count = unit_stack_sum(unit,2);
    if (stack_count == 1) {
      return;
    }
  }
  else {
    unit = tile_first_unit((int)map_cursor_x[0],(int)map_cursor_y[0]);
    if (unit < 0) {
      return;
    }
    if (units[unit].owner != human_civ[0]) {
      return;
    }
    if ((units[unit].owner != game.turn_civ) && (game.reveal_map == '\0')) {
      return;
    }
    stack_count = unit_stack_sum(unit,2);
    if (stack_count == 1) goto activate_unit;
  }
  dialog_flags = 1;
  prompt = (iptr)label_string(label_string_ids[0x3e]);
  unit = unit_stack_select_dialog(unit,(const char *)prompt,dialog_flags);
  if (unit < 0) {
    return;
  }
activate_unit:
  game.active_unit = (i16)unit;
  units[unit].orders = -1;
  units[unit].flags = units[unit].flags & 0x7fff;
  moving_units_mode = 0;
  ui_focus_active_unit(0);
  if (units[unit].moves_used == '\0') {
    unit_reveal_surroundings(unit,1);
  }
  return;
}

/* 0059d190 auto */
void __cdecl dialog_text_font_global_init(void)

{
  dialog_text_font_static_init();
  dialog_text_font_reg_atexit();
  return;
}

/* 0059d1aa auto */
void __cdecl dialog_text_font_static_init(void)

{
  font_init_styled((GameFont *)((i8 *)&dialog_text_font_obj_block.dialog_text_font_obj),0,0x10,1);
  return;
}

/* 0059d1ca auto */
void __cdecl dialog_text_font_reg_atexit(void)

{
  _atexit(dialog_text_font_atexit_dtor);
  return;
}

/* 0059d1e7 auto */
void __cdecl dialog_text_font_atexit_dtor(void)

{
  font_destroy((GameFont *)((i8 *)&dialog_text_font_obj_block.dialog_text_font_obj));
  return;
}

/* 0059d201 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E41
    _$E46
    _$E51
    _$E56
     6 names - too many to list
   
   Library: Visual Studio 1998 Debug */

void __cdecl dialog_title_font_global_init(void)

{
  dialog_title_font_static_init();
  dialog_title_font_reg_atexit();
  return;
}

/* 0059d21b auto */
void __cdecl dialog_title_font_static_init(void)

{
  font_init((GameFont *)((i8 *)&dialog_title_font_obj_block.dialog_title_font_obj),0,0x10);
  return;
}

/* 0059d239 auto */
void __cdecl dialog_title_font_reg_atexit(void)

{
  _atexit(dialog_title_font_atexit_dtor);
  return;
}

/* 0059d256 auto */
void __cdecl dialog_title_font_atexit_dtor(void)

{
  font_destroy((GameFont *)((i8 *)&dialog_title_font_obj_block.dialog_title_font_obj));
  return;
}

/* 0059d270 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E41
    _$E46
    _$E51
    _$E56
     6 names - too many to list
   
   Library: Visual Studio 1998 Debug */

void __cdecl dialog_list_font_global_init(void)

{
  dialog_list_font_static_init();
  dialog_list_font_reg_atexit();
  return;
}

/* 0059d28a auto */
void __cdecl dialog_list_font_static_init(void)

{
  font_init((GameFont *)((i8 *)&dialog_list_font_obj),1,0xe);
  return;
}

/* 0059d2a8 auto */
void __cdecl dialog_list_font_reg_atexit(void)

{
  _atexit(dialog_list_font_atexit_dtor);
  return;
}

/* 0059d2c5 auto */
void __cdecl dialog_list_font_atexit_dtor(void)

{
  font_destroy((GameFont *)((i8 *)&dialog_list_font_obj));
  return;
}

/* 0059d2df auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E41
    _$E46
    _$E51
    _$E56
     6 names - too many to list
   
   Library: Visual Studio 1998 Debug */

void __cdecl dialog_plain_font_global_init(void)

{
  dialog_plain_font_static_init();
  dialog_plain_font_reg_atexit();
  return;
}

/* 0059d2f9 auto */
void __cdecl dialog_plain_font_static_init(void)

{
  font_init((GameFont *)((i8 *)&dialog_plain_font_obj_block.dialog_plain_font_obj),0,0x10);
  return;
}

/* 0059d317 auto */
void __cdecl dialog_plain_font_reg_atexit(void)

{
  _atexit(dialog_plain_font_atexit_dtor);
  return;
}

/* 0059d334 auto */
void __cdecl dialog_plain_font_atexit_dtor(void)

{
  font_destroy((GameFont *)((i8 *)&dialog_plain_font_obj_block.dialog_plain_font_obj));
  return;
}

/* 0059d34e auto */
void __cdecl active_dialog_global_init(void)

{
  active_dialog_static_init();
  return;
}

/* 0059d363 auto */
void __cdecl active_dialog_static_init(void)

{
  dialog_title_font_obj_block.active_dialog = (Dialog *)dialog_stack[0];
  return;
}

/* 0059d37d auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl dialog_edit_on_change(void)

{
  dialog_title_font_obj_block.dialog_timeout_start_i32 = timer_ticks();
  return;
}

/* 0059d397 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl dialog_radio_on_select(void)

{
  dialog_title_font_obj_block.dialog_timeout_start_i32 = timer_ticks();
  return;
}

/* 0059d3b1 auto */
void __cdecl dlg_set_palette(iptr palette)

{
  dlg_palette = palette;
  return;
}

/* 0059d3c9 auto */
void __cdecl dlg_set_parent_window(iptr window)

{
  dlg_parent_window = window;
  return;
}

/* 0059d3e1 auto */
void __cdecl dialog_set_default_offset(i32 x,i32 y)

{
  dlg_default_x = x;
  dlg_default_y = y;
  return;
}

/* 0059d401 auto */
void __cdecl dialog_load_button_labels(void)

{
  int status;
  i32 label_id;
  i8 *label;
  iptr i;
  
  status = text_open_section((const char *)&str_labels_6,(const char *)&str_popups);
  if (status == 0) {
    for (i = 0; i < 3; i++) {
      label_id = text_read_line_pooled();
      *(i32 *)(((i8 *)&dialog_plain_font_obj_block.dialog_button_label_ids) + i * 4) = label_id;
      label = label_string(*(i32 *)(((i8 *)&dialog_plain_font_obj_block.dialog_button_label_ids) + i * 4));
      (((i8 * *)&dialog_button_labels))[i] = label;
    }
  }
  return;
}

/* 0059d487 auto */
void __cdecl
dialog_set_colors(i32 text_color,i32 text_shadow,i32 frame_color,i32 highlight_color,
            i32 bg_color,i32 bevel_light,i32 bevel_dark,i32 title_color,
            i32 title_shadow)

{
  dlg_text_color = (i8)text_color;
  dlg_text_shadow_color = (i8)text_shadow;
  dlg_frame_color = (i8)frame_color;
  (*(i8 *)&dlg_highlight_text_color) = (i8)highlight_color;
  (*(i8 *)&dlg_bg_color) = (i8)bg_color;
  (*(i8 *)&dlg_bevel_light_color) = (i8)bevel_light;
  (*(i8 *)&dlg_bevel_dark_color) = (i8)bevel_dark;
  dlg_title_text_color = (i8)title_color;
  dlg_title_shadow_color = (i8)title_shadow;
  return;
}

/* 0059d4df auto */
void __cdecl
dialog_set_list_colors(i32 bg_color,i32 text_color,i32 shadow_color,i32 sel_bg_color,
            i32 sel_text_color,i32 sel_shadow_color,i32 default_color)

{
  list_bg_color = bg_color;
  list_text_color = text_color;
  list_shadow_color = shadow_color;
  list_sel_bg_color = sel_bg_color;
  dlg_sel_text_color = sel_text_color;
  dlg_sel_text_shadow_color = sel_shadow_color;
  dialog_default_list_color = default_color;
  return;
}

/* 0059d59d auto */
void __cdecl dialog_set_frame_tile_surface(iptr surface)

{
  dlg_frame_tile_surface = surface;
  return;
}

/* 0059d5b5 auto */
void __thiscall dialog_reset_string_pool(DialogCore *self,uint size)

{
  memblock_free((iptr)&((DialogTextLineView *)self)->string_pool);
  memblock_init((iptr)&((DialogTextLineView *)self)->string_pool,9,size);
  return;
}

/* 0059d5f5 auto */
void __thiscall dialog_init_defaults(Dialog *self)

{
  u8 *slot;
  int i;
  
  self->surf_wnd = 0;
  self->bg_surface = 0;
  self->pool_valid = '\0';
  self->list_font = 0;
  self->title_font = self->list_font;
  self->body_font = self->title_font;
  self->sprite_count = 0;
  self->option_count = self->sprite_count;
  self->edit_count = self->option_count;
  self->line_count = self->edit_count;
  self->extra_button_count = 0;
  self->std_button_count = self->extra_button_count;
  self->style_flags = 0;
  self->scale_num = (*(u32 *)&dlg_scale_num);
  self->scale_den = (*(u32 *)&dlg_scale_den);
  self->window_y = 0xfffffc19;
  self->window_x = self->window_y;
  self->origin_y = 0;
  self->origin_x = self->origin_y;
  self->wnd_height = 0;
  self->wnd_width = self->wnd_height;
  if (((*(u32 *)&dlg_default_x) == 0) && ((*(u32 *)&dlg_default_y) == 0)) {
    self->req_y = 0xfffffc19;
    self->req_x = self->req_y;
  }
  else {
    self->req_x = (*(u32 *)&dlg_default_x);
    self->req_y = (*(u32 *)&dlg_default_y);
  }
  self->min_height = 0;
  self->edit_label_width = 0;
  self->bg_color = (uint)dlg_bg_color;
  self->text_color = (uint)(*(byte *)&dlg_text_color);
  self->shadow_color = (uint)(*(byte *)&dlg_text_shadow_color);
  self->frame_color = (uint)(*(byte *)&dlg_frame_color);
  self->highlight_color = (uint)dlg_highlight_text_color;
  self->bevel_light_color = (uint)dlg_bevel_light_color;
  self->bevel_dark_color = (uint)dlg_bevel_dark_color;
  self->title_color = (uint)(*(byte *)&dlg_title_text_color);
  self->title_shadow_color = (uint)(*(byte *)&dlg_title_shadow_color);
  self->list_fill_color = (*(u32 *)&list_bg_color);
  self->list_fg_color = (*(u32 *)&list_text_color);
  self->list_fg_shadow_color = (*(u32 *)&list_shadow_color);
  self->list_sel_fill_color = (*(u32 *)&list_sel_bg_color);
  self->sel_text_color = (*(u32 *)&dlg_sel_text_color);
  self->sel_shadow_color = (*(u32 *)&dlg_sel_text_shadow_color);
  self->list_default_color = (*(u32 *)&dialog_default_list_color);
  for (i = 0; i < 2; i++) {
    slot = (u8 *)&self->list_row_height_override[i];
    slot[0] = '\0';
    slot[1] = '\0';
    slot[2] = '\0';
    slot[3] = '\0';
    slot = (u8 *)&self->list_indents[i];
    slot[0] = '\0';
    slot[1] = '\0';
    slot[2] = '\0';
    slot[3] = '\0';
    slot = (u8 *)&self->pane_drawn[i];
    slot[0] = '\0';
    slot[1] = '\0';
    slot[2] = '\0';
    slot[3] = '\0';
  }
  self->cur_pane = 0;
  self->edit_width = 0;
  self->item_width_value = self->edit_width;
  self->max_sprite_width = self->item_width_value;
  self->content_width = self->max_sprite_width;
  self->option_width = self->content_width;
  self->selected_option = 0;
  self->selected_sprite = 0;
  self->option_tail = 0;
  self->option_list = self->option_tail;
  self->line_list = 0;
  self->sprite_list = 0;
  self->edit_field_list = 0;
  self->option_spacing = 0;
  self->pad_y = 2;
  self->pad_x = 2;
  self->section_gap = 4;
  self->sprite_gap = 4;
  self->border_width = 8;
  self->bevel_width = 2;
  self->option_extra_width = 0;
  self->columns = 1;
  self->list_left_col[1] = 0;
  self->list_left_col[0] = self->list_left_col[1];
  self->sprite_zoom = 0;
  self->title_text = 0;
  self->radio_group = 0;
  self->checkboxes = 0;
  self->edit_controls = 0;
  self->button_controls = 0;
  self->listbox[1] = 0;
  self->listbox[0] = self->listbox[1];
  self->sprite_hotspots = 0;
  self->list_vscroll[1] = 0;
  self->list_vscroll[0] = self->list_vscroll[1];
  self->list_hscroll[1] = 0;
  self->list_hscroll[0] = self->list_hscroll[1];
  self->on_draw_sprite = 0;
  self->on_sprite_click = 0;
  self->on_sprite_dblclick = 0;
  self->on_draw_option = 0;
  self->on_select_change = 0;
  self->on_modal_poll = 0;
  self->result_id = 0;
  self->result_extra = 0;
  return;
}

/* 0059db08 auto */
Dialog * __thiscall dialog_ctor(Dialog *self,i32 size)

{
  memblock_ctor((MemBlock *)self->string_pool);
  self->pool_ptr = 0;
  self->pool_handle = self->pool_ptr;
  dialog_init_defaults(self);
  self->pool_size = (u16)size;
  return self;
}

/* 0059db65 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall dialog_close(Dialog *self)

{
  if ((*(WndBase * *)&dlg_parent_window) == (WndBase *)0x0) {
    if (main_frame_created != 0) {
      wnd_focus_and_raise((WndBase *)((i8 *)&main_frame_wnd_block.main_frame_wnd));
    }
  }
  else {
    wnd_focus_and_raise((*(WndBase * *)&dlg_parent_window));
  }
  if (self->radio_group != 0) {
    if ((RadioGroupDtorView *)self->radio_group != (RadioGroupDtorView *)0x0) {
      radiogrp_scalar_dtor((RadioGroupDtorView *)self->radio_group,1);
    }
    self->radio_group = 0;
  }
  if (self->checkboxes != 0) {
    if ((Checkbox *)self->checkboxes != (Checkbox *)0x0) {
      checkbox_vector_dtor((Checkbox *)self->checkboxes,3);
    }
    self->checkboxes = 0;
  }
  if (self->edit_controls != 0) {
    if ((Control *)self->edit_controls != (Control *)0x0) {
      edit_vector_dtor((Control *)self->edit_controls,3);
    }
    self->edit_controls = 0;
  }
  if (self->button_controls != 0) {
    if ((Control *)self->button_controls != (Control *)0x0) {
      ctrl_vector_dtor((Control *)self->button_controls,3);
    }
    self->button_controls = 0;
  }
  if (self->listbox[0] != 0) {
    if ((ListBoxControl *)self->listbox[0] != (ListBoxControl *)0x0) {
      listbox_scalar_dtor((ListBoxControl *)self->listbox[0],1);
    }
    self->listbox[0] = 0;
  }
  if (self->listbox[1] != 0) {
    if ((ListBoxControl *)self->listbox[1] != (ListBoxControl *)0x0) {
      listbox_scalar_dtor((ListBoxControl *)self->listbox[1],1);
    }
    self->listbox[1] = 0;
  }
  if (self->sprite_hotspots != 0) {
    if ((Hotspot *)self->sprite_hotspots != (Hotspot *)0x0) {
      hotspot_vector_dtor((Hotspot *)self->sprite_hotspots,3);
    }
    self->sprite_hotspots = 0;
  }
  if (self->list_vscroll[0] != 0) {
    if ((Control *)self->list_vscroll[0] != (Control *)0x0) {
      scrollbar_scalar_dtor((Control *)self->list_vscroll[0],1);
    }
    self->list_vscroll[0] = 0;
  }
  if (self->list_vscroll[1] != 0) {
    if ((Control *)self->list_vscroll[1] != (Control *)0x0) {
      scrollbar_scalar_dtor((Control *)self->list_vscroll[1],1);
    }
    self->list_vscroll[1] = 0;
  }
  if (self->list_hscroll[0] != 0) {
    if ((Control *)self->list_hscroll[0] != (Control *)0x0) {
      scrollbar_scalar_dtor((Control *)self->list_hscroll[0],1);
    }
    self->list_hscroll[0] = 0;
  }
  if (self->list_hscroll[1] != 0) {
    if ((Control *)self->list_hscroll[1] != (Control *)0x0) {
      scrollbar_scalar_dtor((Control *)self->list_hscroll[1],1);
    }
    self->list_hscroll[1] = 0;
  }
  if (((self->style_flags & 0x10) == 0) && (self->surf_wnd != 0)) {
    if ((SurfaceWindow *)self->surf_wnd != (SurfaceWindow *)0x0) {
      surfwnd_scalar_dtor((SurfaceWindow *)self->surf_wnd,1);
    }
    self->surf_wnd = 0;
    self->style_flags = self->style_flags | 0x10;
  }
  if (self == dialog_title_font_obj_block.active_dialog) {
    if ((dialog_stack_depth < 1) || (0x10 < dialog_stack_depth)) {
      err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_popupstackindex_0_popupstackindex_17,(iptr)&str_d_ss_franklinton_popup_1_cpp,0x19c);
    }
    dialog_stack_depth--;
    (*(iptr *)&net_session_block.dialog_stack_top) = (((i32 *)&dialog_stack))[dialog_stack_depth];
    dialog_title_font_obj_block.active_dialog = (Dialog *)(*(iptr *)&net_session_block.dialog_stack_top);
    dialog_title_font_obj_block.dialog_timeout_start_i32 = timer_ticks();
  }
  return;
}

/* 0059df8a auto */
i32 __thiscall dialog_dtor(Dialog *self)

{
  i32 result;
  
  dialog_close(self);
  result = memblock_free((iptr)self->string_pool);
  return result;
}

/* 0059dfb9 auto */
void __thiscall
dialog_init
          (Dialog *self,iptr surface_wnd,iptr background,RECT *rect,u32 flags)

{
  i32 size;
  
  if ((self->style_flags & 0x20) == 0) {
    memblock_init((iptr)self->string_pool,9,CONCAT22((short)((uint)self >> 0x10),self->pool_size));
  }
  else {
    dialog_close(self);
    dialog_init_defaults(self);
    dialog_reset_string_pool((DialogCore *)self,(uint)self->pool_size);
  }
  dialog_set_font((DialogTextView *)self,(iptr)dialog_default_text_font);
  dialog_set_title_font((DialogCore *)self,(iptr)(*(i8 * *)dialog_default_text_font_rest));
  dialog_set_list_font((DialogCore *)self,(iptr)(*(i8 * *)(dialog_default_text_font_rest + 4)));
  self->surf_wnd = surface_wnd;
  self->bg_surface = background;
  self->result_id = 0;
  self->style_flags = flags;
  if (rect == 0) {
    dialog_set_width((DialogWindowView *)self,0x1b8);
  }
  else {
    self->origin_x = (u32)rect->left;
    self->origin_y = (u32)rect->top;
    size = rect_width(rect);
    dialog_set_width((DialogWindowView *)self,size);
    size = rect_height(rect);
    dialog_set_height((DialogCore *)self,size);
  }
  if (surface_wnd != 0) {
    self->style_flags = self->style_flags | 0x10;
  }
  return;
}

/* 0059e0eb auto */
i32 __thiscall dialog_set_item_text(Dialog *self,int line_id,const char *text)

{
  size_t len;
  DialogLine *line;
  
  for (line = self->line_list; (line->number != line_id && (line != (DialogLine *)0x0));
      line = line->next) {
  }
  if (((line != (DialogLine *)0x0) && (-1 < line->capacity)) &&
     (len = _strlen((char *)text), (int)(len + 1) <= line->capacity)) {
    crt_strcpy((char *)((void *)line->text),(const char *)((void *)text));
    return 1;
  }
  return 0;
}

/* 0059e18b auto */
DialogLine * __thiscall
dialog_add_line
          (DialogAddLineView *self,const char *text,int x,int y,int max_len,int color)

{
  DialogLine *line;
  size_t len;
  int buffer;
  DialogLine *last;
  DialogLine *cur;
  
  last = (DialogLine *)0x0;
  for (cur = self->line_list; cur != (DialogLine *)0x0; cur = cur->next) {
    last = cur;
  }
  line = (DialogLine *)memblock_alloc((iptr)(self->line_storage),0x20);
  if (last == (DialogLine *)0x0) {
    self->line_list = line;
    line->number = 1;
  }
  else {
    last->next = line;
    line->number = last->number + 1;
  }
  line->next = 0;
  line->flags = 0;
  if (*(char *)text == '^') {
    if (*(char *)(text + 1) == '^') {
      line->flags = (int)line->flags | 1;
      text += 2;
    }
    else {
      line->flags = (int)line->flags | 2;
      text++;
    }
  }
  if (0 < max_len) {
    len = _strlen((char *)text);
    if ((int)(len + 1) < max_len) {
      buffer = memblock_alloc((iptr)(self->line_storage),max_len + 1);
      line->text = (char *)buffer;
      line->capacity = max_len + 1;
      goto copy_line_text;
    }
  }
  len = _strlen((char *)text);
  buffer = memblock_alloc((iptr)(self->line_storage),len + 1);
  line->text = (char *)buffer;
  len = _strlen((char *)text);
  line->capacity = len + 1;
copy_line_text:
  crt_strcpy((char *)((void *)line->text),(const char *)((void *)text));
  line->x = x;
  line->y = y;
  line->color = color;
  self->line_count++;
  return line;
}

/* 0059e356 auto */
i32 __thiscall dialog_option_icon_width(DialogCore *self)

{
  return 0x20;
}

/* 0059e376 auto */
int __thiscall dialog_option_row_height(DialogCore *self)

{
  int spacing;
  int result;
  int icon_width;
  
  icon_width = dialog_option_icon_width(self);
  spacing = font_line_spacing((GameFont *)self->body_font);
  if (spacing * 5 >> 2 <= icon_width) {
    spacing = font_line_spacing((GameFont *)self->body_font);
    icon_width = spacing * 5 >> 2;
  }
  spacing = font_line_spacing((GameFont *)self->body_font);
  if (spacing < icon_width) {
    result = icon_width;
  }
  else {
    result = font_line_spacing((GameFont *)self->body_font);
  }
  return result;
}

/* 0059e3fa auto */
u32 __thiscall dialog_list_row_height(DialogTextView *self)

{
  int font_height;
  u32 result;
  
  if (((DialogWindowView *)self)->list_row_height_override[self->cur_pane] == 0) {
    font_height = font_cached_height((GameFont *)self->list_font);
    result = font_height + 1;
  }
  else {
    result = ((DialogWindowView *)self)->list_row_height_override[self->cur_pane];
  }
  return result;
}

/* 0059e448 auto */
int __thiscall dialog_edit_row_height(DialogCore *self)

{
  int spacing;
  
  spacing = font_line_spacing((GameFont *)self->body_font);
  return spacing + 10;
}

/* 0059e472 auto */
void __thiscall dialog_set_font(DialogTextView *self,iptr font)

{
  u32 row_height;
  
  self->body_font = font;
  row_height = dialog_option_row_height((DialogCore *)self);
  self->option_row_height = row_height;
  return;
}

/* 0059e4a4 auto */
/* Library Function - Single Match
    public: void __thiscall CArchive::SetObjectSchema(unsigned int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall dialog_set_title_font(DialogCore *self,iptr font)

{
  self->title_font = font;
  return;
}

/* 0059e4c5 auto */
void __thiscall dialog_set_list_font(DialogCore *self,iptr font)

{
  self->list_font = font;
  return;
}

/* 0059e4e6 auto */
void __thiscall dialog_set_columns(DialogButtonsView *self,u32 column_count)

{
  self->columns = column_count;
  return;
}

/* 0059e507 auto */
void __thiscall dialog_set_list_rows(DialogTextView *self,u32 rows)

{
  int row_height;
  
  self->style_flags = self->style_flags | 0x1000;
  self->list_rows[self->cur_pane] = rows;
  if ((self->style_flags & 0x40000) == 0) {
    row_height = dialog_list_row_height(self);
    self->list_height[self->cur_pane] = row_height * rows + 2;
  }
  else {
    row_height = font_cached_height((GameFont *)((i32 *)&default_draw_font_obj_block.default_draw_font_obj));
    self->list_height[self->cur_pane] = row_height * rows + 2;
  }
  return;
}

/* 0059e585 auto */
void __thiscall dialog_set_current_pane(DialogSetCurrentPaneView *self,u32 pane)

{
  if ((pane == 0) || (pane == 1)) {
    self->cur_pane = pane;
  }
  else {
    self->cur_pane = 0;
  }
  return;
}

/* 0059e5c9 auto */
void __thiscall dialog_set_listbox(DialogTextView *self,int rows,u32 width,u32 list_flags)

{
  self->style_flags = self->style_flags | 0x1000;
  self->list_width[self->cur_pane] = width;
  ((DialogWindowView *)self)->list_x_offset[self->cur_pane] = list_flags;
  if (rows != 0) {
    dialog_set_list_rows(self,rows);
  }
  return;
}

/* 0059e648 auto */
int __thiscall dialog_line_height(DialogTextView *self)

{
  int spacing;
  
  spacing = font_line_spacing((GameFont *)self->body_font);
  return spacing + 4 + self->pad_y * 2;
}

/* 0059e676 auto */
int __thiscall dialog_button_width_for(DialogButtonWidthForView *self,const char *text)

{
  u32 padding;
  int text_width;
  
  padding = self->button_padding;
  text_width = font_text_width((GameFont *)((i8 *)&dialog_plain_font_obj_block.dialog_plain_font_obj),text);
  return text_width + 4 + padding * 4;
}

/* 0059e6a9 auto */
void __thiscall dialog_set_title(DialogWindowView *self,const char *title)

{
  size_t len;
  uptr buffer;
  
  len = _strlen((char *)title);
  buffer = memblock_alloc((iptr)&((DialogTextLineView *)self)->string_pool,len + 1);
  self->title_text = buffer;
  crt_strcpy((char *)((void *)self->title_text),(const char *)((void *)title));
  return;
}

/* 0059e6ff auto */
void __thiscall dialog_set_width(DialogWindowView *self,u32 width)

{
  if ((self->scale_num != self->scale_den) && ((self->style_flags & 0x80000) == 0)) {
    width = (int)(self->scale_num * width) / (int)self->scale_den;
  }
  self->content_width = width;
  return;
}

/* 0059e762 auto */
/* Library Function - Single Match
    public: void __thiscall ios::delbuf(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall dialog_set_height(DialogCore *self,u32 height)

{
  self->min_height = height;
  return;
}

/* 0059e783 auto */
void __thiscall dialog_set_position(DialogCore *self,u32 x,u32 y)

{
  self->req_x = x;
  self->req_y = y;
  return;
}

/* 0059e7ad auto */
DialogOption * __thiscall dialog_find_option(DialogOptionList *self,int option_id)

{
  DialogOption *cur;
  DialogOption *found;
  
  found = 0;
  cur = self->option_list;
  while ((cur != 0 && (found == 0))) {
    if (cur->id == option_id) {
      found = cur;
    }
    cur = cur->next;
  }
  return found;
}

/* 0059e877 auto */
DialogSprite * __thiscall dialog_find_sprite(DialogOptionList *self,int sprite_id)

{
  DialogSprite *cur;
  DialogSprite *found;
  
  found = (DialogSprite *)0x0;
  cur = self->sprite_list;
  while ((cur != (DialogSprite *)0x0 && (found == (DialogSprite *)0x0))) {
    if (cur->id == sprite_id) {
      found = cur;
    }
    cur = cur->next;
  }
  return found;
}

/* 0059e8db auto */
void __thiscall dialog_set_option_disabled(DialogOptionList *self,iptr option_id,int disabled)

{
  DialogOption *option;
  
  option = dialog_find_option(self,option_id);
  if (option != (DialogOption *)0x0) {
    if (disabled == 0) {
      option->flags = option->flags & 0xfffffffe;
    }
    else {
      option->flags = option->flags | 1;
    }
  }
  return;
}

/* 0059e9f3 auto */
i32 __thiscall dialog_option_is_checked(DialogOptionList *self,i32 option_id)

{
  DialogOption *option;
  i32 checked;
  
  checked = 0;
  option = dialog_find_option(self,option_id);
  if (option != (DialogOption *)0x0) {
    if ((option->flags_byte & 4) == 0) {
      checked = 0;
    }
    else {
      checked = 1;
    }
  }
  return checked;
}

/* 0059ea4d auto */
void __thiscall dialog_set_option_checked(DialogOptionList *self,i32 option_id,int checked)

{
  DialogOption *option;
  
  option = dialog_find_option(self,option_id);
  if (option != (DialogOption *)0x0) {
    if (checked == 0) {
      option->flags = option->flags & 0xfffffffb;
    }
    else {
      option->flags = option->flags | 4;
    }
  }
  return;
}

/* 0059ea99 auto */
void __thiscall dialog_set_default_choice(DialogOptionList *self,iptr choice_id)

{
  uptr entry;
  
  if (self->option_count == 0) {
    entry = (uptr)dialog_find_sprite(self,choice_id);
    if (entry != 0) {
      self->selected_sprite = (DialogSprite *)entry;
    }
  }
  else {
    entry = (uptr)dialog_find_option(self,choice_id);
    if (entry != 0) {
      self->selected_option = (DialogOption *)entry;
    }
  }
  return;
}

/* 0059eb8c auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall dialog_set_sprite_click_fn(DialogOptionList *self,iptr callback)

{
  self->on_sprite_click = callback;
  return;
}

/* 0059ebb0 auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall dialog_set_sprite_dblclick_fn(DialogOptionList *self,iptr callback)

{
  self->on_sprite_dblclick = callback;
  return;
}

/* 0059ebd4 auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall dialog_set_sprite_draw_fn(DialogCore *self,iptr callback)

{
  ((DialogTextLineView *)self)->sprite_draw_callback = callback;
  return;
}

/* 0059ebf8 auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall dialog_set_option_draw_fn(DialogOptionList *self,iptr callback)

{
  self->on_draw_option = callback;
  return;
}

/* 0059ec1c auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall dialog_set_select_change_fn(DialogSelChangeSetView *self,iptr callback)

{
  self->on_select_change = callback;
  return;
}

/* 0059ec64 auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall dialog_set_image_zoom(DialogWindowView *self,u32 zoom)

{
  self->sprite_zoom = zoom;
  return;
}

/* 0059ec88 auto */
DialogSprite * __thiscall
dialog_add_sprite(DialogOptionList *self,iptr sprite,iptr sprite_id,const char *label)

{
  DialogSprite *entry;
  size_t len;
  iptr label_buf;
  int label_width;
  u32 max_width;
  DialogSprite *last;
  DialogSprite *cur;
  u32 entry_width;
  
  last = 0;
  for (cur = self->sprite_list; cur != 0; cur = cur->next) {
    last = cur;
  }
  entry = (DialogSprite *)memblock_alloc((iptr)self->string_pool,0x14);
  if (last == 0) {
    self->sprite_list = entry;
    if (self->selected_sprite == 0) {
      self->selected_sprite = entry;
    }
  }
  else {
    last->next = (DialogSprite *)((iptr *)entry);
  }
  entry->next = 0;
  entry->field_04 = 0;
  entry->sprite = (Sprite *)sprite;
  entry_width = sprite_width((Sprite *)sprite);
  if (label == 0) {
    entry->label = 0;
  }
  else {
    len = _strlen((char *)label);
    label_buf = memblock_alloc((iptr)self->string_pool,len + 1);
    entry->label = (char *)label_buf;
    crt_strcpy((char *)((void *)entry->label),(const char *)((void *)label));
    label_width = font_text_width((GameFont *)self->body_font,(const char *)entry->label);
    entry_width = entry_width + self->sprite_gap + label_width;
  }
  entry->id = sprite_id;
  max_width = self->max_sprite_width;
  if ((int)self->max_sprite_width <= (int)entry_width) {
    max_width = entry_width;
  }
  self->max_sprite_width = max_width;
  self->sprite_count++;
  return entry;
}

/* 0059edf0 auto */
DialogOption * __thiscall
dialog_add_option(DialogOptionList *self,const char *text,iptr option_id,uint data)

{
  u32 width;
  int cmp;
  DialogOption *option;
  size_t len;
  uint text_buf;
  int icon_width;
  u32 max_width;
  DialogOption *prev;
  DialogOption *cur;
  
  prev = 0;
  cur = self->option_list;
  if (((self->style_flags & 0x800000) == 0) || (cur == 0)) {
    if (cur != 0) {
      for (; cur != 0; cur = cur->next) {
        prev = cur;
      }
    }
  }
  else {
    while ((cur != 0 && (cmp = __strcmpi((char *)text,cur->text), 0 < cmp))
          ) {
      prev = cur;
      cur = cur->next;
    }
  }
  option = (DialogOption *)memblock_alloc((iptr)self->string_pool,0x18);
  if (prev == 0) {
    option->next = self->option_list;
    option->prev = 0;
    if (self->option_list == 0) {
      self->option_tail = option;
    }
    else {
      self->option_list->prev = option;
    }
    self->option_list = option;
    self->selected_option = option;
  }
  else {
    option->next = prev->next;
    option->prev = prev;
    if (option->next == 0) {
      self->option_tail = option;
    }
    else {
      *(uint **)((uint)option->next + 0x14) = (uint *)option;
    }
    prev->next = (DialogOption *)((uint *)option);
  }
  option->flags = 0;
  len = _strlen((char *)text);
  text_buf = memblock_alloc((iptr)self->string_pool,len + 1);
  option->text = (char *)text_buf;
  crt_strcpy((char *)((void *)option->text),(const char *)((void *)text));
  if (*(char *)text == '\0') {
    option->flags = option->flags | 1;
  }
  option->id = option_id;
  option->group = data;
  cmp = font_text_width((GameFont *)self->body_font,(const char *)option->text);
  icon_width = dialog_option_icon_width((DialogCore *)self);
  width = cmp + icon_width + self->option_extra_width + 5;
  max_width = self->option_width;
  if ((int)self->option_width <= (int)width) {
    max_width = width;
  }
  self->option_width = max_width;
  self->option_count++;
  return option;
}

/* 0059f026 auto */
DialogOption * __thiscall
dialog_add_checkbox_option(DialogOptionList *self,const char *text,iptr option_id,int checked)

{
  DialogOption *option;
  
  self->style_flags = self->style_flags | 5;
  option = dialog_add_option(self,text,option_id,0);
  if (checked != 0) {
    option->flags = option->flags | 4;
  }
  return option;
}

/* 0059f06d auto */
DialogEditField * __thiscall
dialog_add_edit_field(DialogOptionList *self,const char *label,iptr initial_text,size_t max_len)

{
  DialogEditField *field;
  size_t len;
  i32 buffer;
  u32 label_width;
  int char_width;
  u32 max_width;
  DialogEditField *last;
  DialogEditField *cur;
  u32 field_width;
  
  last = 0;
  for (cur = self->edit_field_list; cur != 0; cur = cur->next) {
    last = cur;
  }
  field = (DialogEditField *)memblock_alloc((iptr)self->string_pool,0x1c);
  if (last == 0) {
    self->edit_field_list = field;
  }
  else {
    last->next = (DialogEditField *)((i32 *)field);
  }
  field->next = 0;
  field->field_00 = 0;
  len = _strlen((char *)label);
  buffer = memblock_alloc((iptr)self->string_pool,len + 2);
  field->label = (char *)buffer;
  crt_strcpy((char *)((void *)field->label),(const char *)((void *)label));
  label_width = font_text_width((GameFont *)self->body_font,(const char *)field->label);
  max_width = self->edit_label_width;
  if ((int)self->edit_label_width <= (int)label_width) {
    max_width = label_width;
  }
  self->edit_label_width = max_width;
  if (0xfe < (int)max_len) {
    max_len = 0xff;
  }
  field->max_len = max_len;
  buffer = memblock_alloc((iptr)self->string_pool,0x100);
  field->buffer = (char *)buffer;
  char_width = font_text_width((GameFont *)(*(i8 * *)(draw_current_font_rest + 12)),(const char *)&str_w);
  field->width = char_width * max_len;
  field_width = field->width + self->edit_label_width;
  if ((self->content_width != 0) && ((int)self->content_width < (int)field_width)) {
    field->width -= ((field_width - self->content_width) - 3);
    field_width = field->width + self->edit_label_width + 3;
  }
  max_width = self->edit_width;
  if ((int)self->edit_width <= (int)field_width) {
    max_width = field_width;
  }
  self->edit_width = max_width;
  if (initial_text == 0) {
    *field->buffer = 0;
  }
  else {
    _memset((void *)field->buffer,0,0x100);
    _strncpy(field->buffer,(char *)initial_text,max_len);
  }
  field->index = self->edit_count;
  self->edit_count++;
  return field;
}

/* 0059f2a3 auto */
void __thiscall dialog_add_button(DialogButtonsView *self,const char *label)

{
  size_t len;
  uptr buffer;
  
  if ((int)self->extra_button_count < 6) {
    len = _strlen((char *)label);
    buffer = memblock_alloc((iptr)&((DialogTextLineView *)self)->string_pool,len + 1);
    (&((Dialog *)self)->extra_button_labels)[self->extra_button_count] = buffer;
    crt_strcpy((char *)((void *)((&((Dialog *)self)->extra_button_labels)[self->extra_button_count])),(const char *)((void *)label));
    self->extra_button_count++;
  }
  return;
}

/* 0059f31a auto */
void __thiscall dialog_set_text_color(DialogTextView *self,int highlighted,int use_alt,int shadow)

{
  u32 normal_color;
  u32 alt_color;
  u32 hilite_color;
  
  if (highlighted == 0) {
    if (use_alt == 0) {
      if (shadow == 0) {
        normal_color = self->text_color;
      }
      else {
        normal_color = self->shadow_color;
      }
      gfx_set_text_color_index(normal_color);
    }
    else {
      if (shadow == 0) {
        alt_color = self->frame_color;
      }
      else {
        alt_color = self->shadow_color;
      }
      gfx_set_text_color_index(alt_color);
    }
  }
  else {
    if (shadow == 0) {
      hilite_color = self->highlight_color;
    }
    else {
      hilite_color = self->shadow_color;
    }
    gfx_set_text_color_index(hilite_color);
  }
  return;
}

/* 0059f3d7 auto */
int __thiscall
dialog_draw_text_shadowed
          (DialogTextView *self,iptr font,char *text,int x,int y,uint flags)

{
  char *underscore;
  i32 use_alt;
  int text_width;
  i32 shadow;
  
  while (underscore = _strchr(text,0x5f), underscore != (char *)0x0) {
    *underscore = ' ';
  }
  if (self->shadow_color != self->text_color) {
    shadow = 1;
    use_alt = dialog_uses_alt_text_color((DialogAltColorView *)self);
    dialog_set_text_color(self,flags & 1,use_alt,shadow);
    surface_draw_text
              ((DibSurface *)self->surf_wnd,font,(const char *)text,x + 1,y + 1,5);
  }
  shadow = 0;
  use_alt = dialog_uses_alt_text_color((DialogAltColorView *)self);
  dialog_set_text_color(self,flags & 1,use_alt,shadow);
  surface_draw_text
            ((DibSurface *)self->surf_wnd,font,(const char *)text,x,y,5);
  text_width = font_text_width((GameFont *)font,(const char *)text);
  return x + text_width;
}

/* 0059f5ba auto */
void __thiscall
dialog_draw_text_line(DialogTextLineView *self,const char *text,int x_offset,i32 y)

{
  dialog_draw_text_default_font
            ((DialogTextView *)self,text,self->text_x + x_offset,y,0);
  return;
}

/* 0059f5f7 auto */
i32 __thiscall dialog_has_text_lines(DialogOptionList *self)

{
  DialogLine *line;
  
  line = self->line_list;
  while( true ) {
    if (line == 0) {
      return 0;
    }
    if (line->x < 0) break;
    line = line->next;
  }
  return 1;
}

/* 0059f64a auto */
int __thiscall dialog_draw_wrapped_text(DialogOptionList *self,int draw)

{
  u32 max_width;
  int text_width;
  uptr remaining;
  char *space;
  uptr word_len;
  int buf_width;
  int center_x;
  bool has_shadow;
  u32 line_y;
  char *src;
  int total_height;
  u32 y2;
  int x2;
  char line_buf[256];
  char word_buf[80];
  int line_width;
  DialogLine *line;
  int line_height;
  
  has_shadow = self->shadow_color != self->text_color;
  line = self->line_list;
  max_width = self->content_width;
  total_height = 0;
  y2 = self->text_y;
  line_height = font_line_spacing((GameFont *)self->body_font);
  line_buf[0] = '\0';
  line_width = 0;
  for (; center_x = (int)max_width >> 1, line != 0; line = line->next) {
    if (line->x < 1) {
      src = line->text;
      if ((line->flags_byte & 3) != 0) {
        if (line_buf[0] != '\0') {
          if (draw != 0) {
            dialog_draw_text_line((DialogTextLineView *)self,(const char *)line_buf,0,y2);
          }
          total_height += line_height;
          y2 += line_height;
          line_buf[0] = '\0';
          line_width = 0;
        }
        if (draw != 0) {
          if ((line->flags_byte & 1) == 0) {
            x2 = 0;
          }
          else if (line->color == 0) {
            text_width = font_text_width((GameFont *)self->body_font,(const char *)src);
            x2 = center_x - ((int)((uint)has_shadow + text_width) >> 1);
          }
          else {
            x2 = line->color;
            text_width = font_text_width((GameFont *)self->body_font,(const char *)src);
            x2 -= ((int)((uint)has_shadow + text_width) >> 1);
          }
          if (line->y == -1) {
            line_y = y2;
          }
          else {
            line_y = (u32)line->y;
          }
          dialog_draw_text_line
                    ((DialogTextLineView *)self,(const char *)src,x2,line_y);
        }
        for (; *src != '\0'; src++) {
        }
        if (line->y < 0) {
          total_height += line_height;
          y2 += line_height;
        }
      }
      while (remaining = _strlen(src), remaining != 0) {
        for (; *src == ' '; src++) {
        }
        space = _strchr(src,0x20);
        if (space != (char *)0x0) {
          *space = '\0';
        }
        word_len = _strlen(src);
        word_buf[0] = '\0';
        if (line_buf[0] != '\0') {
          crt_strcat(word_buf,((i8 *)&dialog_wrap_space_str));
        }
        crt_strcat(word_buf,src);
        text_width = font_text_width((GameFont *)self->body_font,(const char *)word_buf);
        if ((int)max_width < (int)((uint)has_shadow + text_width + line_width)) {
          if (draw != 0) {
            if ((self->style_flags & 0x200000) == 0) {
              x2 = 0;
            }
            else {
              buf_width = font_text_width
                                ((GameFont *)self->body_font,(const char *)line_buf);
              x2 = center_x - ((int)((uint)has_shadow + buf_width) >> 1);
            }
            dialog_draw_text_line
                      ((DialogTextLineView *)self,(const char *)line_buf,x2,y2);
          }
          total_height += line_height;
          y2 += line_height;
          while (word_buf[0] == ' ') {
            crt_strcpy(word_buf,(word_buf + 1));
          }
          line_buf[0] = '\0';
          line_width = 0;
        }
        crt_strcat(line_buf,word_buf);
        line_width += text_width;
        if (space != (char *)0x0) {
          *space = ' ';
        }
        src += word_len;
      }
    }
    else if (draw != 0) {
      dialog_draw_text_default_font
                ((DialogTextView *)self,(const char *)line->text,line->x,
                 line->y,(i32)line->flags);
    }
  }
  if (line_buf[0] != '\0') {
    if (draw != 0) {
      if ((self->style_flags & 0x200000) == 0) {
        x2 = 0;
      }
      else {
        text_width = font_text_width((GameFont *)self->body_font,(const char *)line_buf);
        x2 = center_x - ((int)((uint)has_shadow + text_width) >> 1);
      }
      dialog_draw_text_line((DialogTextLineView *)self,(const char *)line_buf,x2,y2)
      ;
    }
    total_height += line_height;
  }
  return total_height;
}

/* 0059fb78 auto */
i32 __thiscall dialog_option_group_index(DialogOptionList *self,DialogOption *option)

{
  int index;
  DialogOption *cur;
  
  if (self->option_list != 0) {
    index = 0;
    for (cur = self->option_list; cur != 0; cur = cur->next) {
      if ((option->group == cur->group) && ((uptr)option == (uptr)cur)) {
        return index;
      }
      if (option->group == cur->group) {
        index++;
      }
    }
  }
  return 0;
}

/* 0059fc19 auto */
DialogOption * __thiscall dialog_option_at(DialogOptionList *self,int target_index)

{
  int index;
  DialogOption *cur;
  
  if (self->option_list != 0) {
    index = 0;
    for (cur = self->option_list; cur != 0; cur = cur->next) {
      if ((self->cur_pane == (u32)cur->group) && (index == target_index)) {
        return cur;
      }
      if (self->cur_pane == (u32)cur->group) {
        index++;
      }
    }
  }
  return 0;
}

/* 0059fcba auto */
int __thiscall dialog_column_of_option(DialogOptionList *self,DialogOption *option)

{
  int group_index;
  
  group_index = dialog_option_group_index(self,option);
  return group_index / (int)self->list_rows[self->cur_pane];
}

/* 0059fd2a auto */
i32 __thiscall dialog_compute_layout(DialogOptionList *self)

{
  u32 pos;
  int value;
  size_t len;
  i32 height;
  u32 tmp;
  uptr column_count;
  int button_x;
  int text_height;
  int top_index;
  RECT frame_rect2;
  u32 text_width;
  RECT screen_rect2;
  i32 result;
  int remainder_acc;
  int rows;
  u32 left;
  int extra_space;
  u32 top;
  u32 avail_width;
  int sprites_height;
  int edit_height;
  DialogSprite *sprite;
  uptr i;
  u32 sprite_width2;
  DialogLine *line;
  u32 lists_height;
  DialogOption *first_option;
  int content_height;
  
  result = 1;
  text_height = 0;
  lists_height = 0;
  edit_height = 0;
  if ((self->style_flags & 0x100000) == 0) {
    for (line = self->line_list; line != 0; line = line->next) {
      if ((line->flags_byte & 3) != 0) {
        tmp = self->shadow_color;
        pos = self->text_color;
        value = font_text_width
                          ((GameFont *)self->body_font,(const char *)line->text);
        text_width = (uint)(tmp != pos) + value;
        tmp = self->content_width;
        if ((int)self->content_width <= (int)text_width) {
          tmp = text_width;
        }
        self->content_width = tmp;
      }
    }
  }
  if (((self->title_text != 0) && (self->title_font != 0)) &&
     (len = _strlen((char *)self->title_text), len != 0)) {
    value = font_text_width((GameFont *)self->title_font,(const char *)self->title_text);
    text_width = value + 4;
    tmp = self->content_width;
    if ((int)self->content_width <= (int)text_width) {
      tmp = text_width;
    }
    self->content_width = tmp;
  }
  for (sprite = self->sprite_list; sprite != 0; sprite = sprite->next) {
  }
  if ((self->edit_count != 0) && (self->option_count != 0)) {
    self->edit_count = 0;
    self->edit_field_list = 0;
  }
  if ((self->style_flags & 0x10000) == 0) {
    value = font_cached_height((GameFont *)self->title_font);
    self->title_height = value + self->bevel_width * 2 + self->pad_y * 2;
  }
  else {
    self->border_width = 0;
    self->bevel_width = 0;
    self->title_height = 0;
  }
  self->chrome_height = self->title_height;
  self->window_x = self->req_x;
  self->window_y = self->req_y;
  left = self->border_width + self->pad_x;
  top = self->title_height + self->pad_y;
  if ((self->style_flags & 0x100000) == 0) {
    self->wnd_width = left * 2;
    self->wnd_height = self->pad_y * 2 + self->title_height;
    self->text_x = left;
    self->text_y = top;
    self->list_x = left;
    self->list_y = top;
    self->edit_x = left;
    self->edit_y = top;
    self->sprite_x = left;
    self->sprite_y = top;
    tmp = self->option_width;
    if ((int)self->option_width <= (int)self->content_width) {
      tmp = self->content_width;
    }
    if ((int)tmp <= (int)self->edit_width) {
      tmp = self->edit_width;
    }
    self->content_width = tmp;
    self->edit_width = self->content_width;
    self->option_width = self->edit_width;
  }
  self->std_button_count = 0;
  if ((self->style_flags & 0x40) != 0) {
    (&((Dialog *)self)->button_alignment)[self->std_button_count * 2] = 1;
    self->std_button_count++;
  }
  if (((self->style_flags & 8) == 0) && ((self->style_flags & 0x2000000) == 0)) {
    (&((Dialog *)self)->button_alignment)[self->std_button_count * 2] = 0;
    self->std_button_count++;
  }
  if ((self->style_flags & 1) != 0) {
    (&((Dialog *)self)->button_alignment)[self->std_button_count * 2] = 2;
    self->std_button_count++;
  }
  if (self->edit_count + self->option_count + self->sprite_count + self->std_button_count + self->line_count == 0) {
    if (self->surf_wnd != 0) {
      self->text_x += self->origin_x;
      self->text_y += self->origin_y;
    }
  }
  else if ((self->option_count != 0) || ((self->style_flags & 0x1004) == 0)) {
    sprites_height = 0;
    if (self->sprite_list != 0) {
      sprite_width2 = gfx_zoom_scale(self->max_sprite_width,self->sprite_zoom);
      if (self->sprite_list->label == 0) {
        self->text_x += sprite_width2;
        self->list_x += sprite_width2;
        self->edit_x += sprite_width2;
        self->wnd_width += sprite_width2;
      }
      else {
        tmp = self->content_width;
        if ((int)self->content_width <= (int)sprite_width2) {
          tmp = sprite_width2;
        }
        self->content_width = tmp;
      }
      for (sprite = self->sprite_list; sprite != 0; sprite = sprite->next) {
        tmp = self->sprite_zoom;
        height = sprite_height(sprite->sprite);
        value = gfx_zoom_scale(height,tmp);
        sprites_height += value;
        if (sprite->next != 0) {
          sprites_height += self->section_gap;
        }
      }
    }
    if ((self->line_list != 0) && (value = dialog_has_text_lines(self), value != 0)) {
      text_height = dialog_draw_wrapped_text(self,0);
      self->list_y = self->list_y + self->section_gap + text_height;
      self->edit_y = self->edit_y + self->section_gap + text_height;
    }
    if (self->option_list != 0) {
      column_count = self->columns;
      if ((int)column_count < 2) {
        column_count = 1;
      }
      rows = (int)((self->columns - 1) + self->option_count) / (int)column_count;
      lists_height = self->option_row_height * rows;
      if ((self->style_flags & 0x1000) != 0) {
        self->cur_pane = 0;
        lists_height = self->list_height[0];
        if ((self->style_flags & 0x40000) == 0) {
          tmp = GetSystemMetrics(2);
          self->list_vscroll_width[0] = tmp;
          tmp = GetSystemMetrics(3);
          self->list_hscroll_height[0] = tmp;
          rect_set_xywh((iptr)&self->pane_rect[0].left,self->list_x_offset[0] + self->list_x,self->list_y,
                             self->list_width[0],self->list_height[0]);
          self->list_client_rect[0].left = self->pane_rect[0].left;
          self->list_client_rect[0].top = self->pane_rect[0].top;
          self->list_client_rect[0].right = self->pane_rect[0].right;
          self->list_client_rect[0].bottom = self->pane_rect[0].bottom;
          if (((int)(self->list_rows[0] * self->columns) < (int)self->option_count) ||
             ((self->style_flags & 0x1000000) != 0)) {
            if (self->columns == 1) {
              rect_set_xywh((iptr)&self->list_vscroll_rect[0],self->pane_rect[0].right - self->list_vscroll_width[0],
                                 self->list_y,self->list_vscroll_width[0],self->list_height[0]);
              self->list_client_rect[0].right -= self->list_vscroll_width[0];
            }
            else {
              self->list_height[0] += self->list_hscroll_height[0];
              self->pane_rect[0].bottom += self->list_hscroll_height[0];
              self->list_client_rect[0].bottom += self->list_hscroll_height[0];
              lists_height = self->list_height[0];
              rect_set_xywh((iptr)&self->list_hscroll_rect[0],self->list_x_offset[0] + self->list_x,
                                 self->pane_rect[0].bottom - self->list_hscroll_height[0],self->list_width[0],self->list_hscroll_height[0]);
              self->list_client_rect[0].bottom -= self->list_hscroll_height[0];
            }
          }
          rect_deflate((iptr)&self->list_client_rect[0].left,1,1);
          self->list_origin_x[0] = self->list_client_rect[0].left;
          self->list_origin_y[0] = self->list_client_rect[0].top;
          value = rect_width((RECT *)&self->list_client_rect[0].left);
          self->list_column_width[0] = value / (int)self->columns;
          tmp = dialog_list_row_height((DialogTextView *)self);
          self->list_row_height[0] = tmp;
          first_option = dialog_option_at(self,0);
          top_index = dialog_option_group_index(self,first_option);
          value = dialog_option_group_index(self,self->selected_option);
          while ((int)(self->list_rows[0] * self->columns + top_index) <= value) {
            if (self->columns == 1) {
              top_index++;
            }
            else {
              top_index += self->list_rows[0];
            }
          }
          tmp = (u32)dialog_option_at(self,top_index);
          self->list_top_option[0] = (DialogOption *)tmp;
        }
        if ((self->style_flags & 0x400000) != 0) {
          self->cur_pane = 1;
          if ((int)lists_height < (int)self->list_height[1]) {
            lists_height = self->list_height[1];
          }
          if ((self->style_flags & 0x40000) == 0) {
            tmp = GetSystemMetrics(2);
            self->list_vscroll_width[1] = tmp;
            tmp = GetSystemMetrics(3);
            self->list_hscroll_height[1] = tmp;
            rect_set_xywh((iptr)&self->pane_rect[1].left,self->list_x_offset[1] + self->list_x,
                               self->list_y,self->list_width[1],self->list_height[1]);
            self->list_client_rect[1].left = self->pane_rect[1].left;
            self->list_client_rect[1].top = self->pane_rect[1].top;
            self->list_client_rect[1].right = self->pane_rect[1].right;
            self->list_client_rect[1].bottom = self->pane_rect[1].bottom;
            if (((int)(self->list_rows[1] * self->columns) < (int)self->option_count) ||
               ((self->style_flags & 0x1000000) != 0)) {
              if (self->columns == 1) {
                rect_set_xywh((iptr)&self->list_vscroll_rect[1],self->pane_rect[1].right - self->list_vscroll_width[1],
                                   self->list_y,self->list_vscroll_width[1],self->list_height[1]);
                self->list_client_rect[1].right -= self->list_vscroll_width[1];
              }
              else {
                self->list_height[1] += self->list_hscroll_height[1];
                self->pane_rect[1].bottom += self->list_hscroll_height[1];
                self->list_client_rect[1].bottom += self->list_hscroll_height[1];
                if ((int)lists_height < (int)self->list_height[1]) {
                  lists_height = self->list_height[1];
                }
                rect_set_xywh((iptr)&self->list_hscroll_rect[1],self->list_x_offset[1] + self->list_x,
                                   self->pane_rect[1].bottom - self->list_hscroll_height[1],self->list_width[1],self->list_hscroll_height[1])
                ;
                self->list_client_rect[1].bottom -= self->list_hscroll_height[1];
              }
            }
            rect_deflate((iptr)&self->list_client_rect[1].left,1,1);
            self->list_origin_x[1] = self->list_client_rect[1].left;
            self->list_origin_y[1] = self->list_client_rect[1].top;
            value = rect_width((RECT *)&self->list_client_rect[1].left);
            self->list_column_width[1] = value / (int)self->columns;
            tmp = dialog_list_row_height((DialogTextView *)self);
            self->list_row_height[1] = tmp;
            first_option = dialog_option_at(self,0);
            top_index = dialog_option_group_index(self,first_option);
            value = dialog_option_group_index(self,self->selected_option);
            while ((int)(self->list_rows[1] * self->columns + top_index) <= value) {
              if (self->columns == 1) {
                top_index++;
              }
              else {
                top_index += self->list_rows[1];
              }
            }
            tmp = (u32)dialog_option_at(self,top_index);
            self->list_top_option[1] = (DialogOption *)tmp;
          }
          self->cur_pane = 0;
        }
      }
    }
    if (self->edit_field_list != 0) {
      edit_height = dialog_edit_row_height((DialogCore *)self);
      edit_height = edit_height * self->edit_count;
    }
    content_height = edit_height + lists_height + text_height;
    if (((content_height != 0) && (text_height != 0)) && (edit_height + lists_height != 0)) {
      content_height += self->section_gap;
    }
    if ((self->style_flags & 0x100000) == 0) {
      if ((sprites_height != 0) && (content_height != 0)) {
        self->text_x += self->sprite_gap;
        self->list_x += self->sprite_gap;
        self->edit_x += self->sprite_gap;
      }
      value = sprites_height;
      if (sprites_height <= content_height) {
        value = content_height;
      }
      self->wnd_height += value;
      self->wnd_width += self->content_width;
    }
    if (self->std_button_count + self->extra_button_count == 0) {
      self->wnd_height += self->border_width;
      self->chrome_height += self->border_width;
    }
    else {
      button_x = self->wnd_width - (self->border_width - self->bevel_width);
      self->button_width = 0;
      for (i = 0; (int)i < 3; i++) {
        value = dialog_button_width_for
                          ((DialogButtonWidthForView *)self,(const char *)(((i8 * *)&dialog_button_labels))[i]);
        if ((int)self->button_width <= value) {
          tmp = dialog_button_width_for
                            ((DialogButtonWidthForView *)self,(const char *)(((i8 * *)&dialog_button_labels))[i]);
          self->button_width = tmp;
        }
      }
      for (i = 0; (int)i < (int)self->extra_button_count; i++) {
        value = dialog_button_width_for((DialogButtonWidthForView *)self,(const char *)((&(*&((Dialog *)self)->extra_button_labels))[i]));
        if ((int)self->button_width <= value) {
          tmp = dialog_button_width_for((DialogButtonWidthForView *)self,(const char *)((&(*&((Dialog *)self)->extra_button_labels))[i]));
          self->button_width = tmp;
        }
      }
      value = (self->wnd_width + (self->border_width - self->bevel_width) * -2) -
              (self->std_button_count + self->extra_button_count - 1) * self->pad_x;
      extra_space = value % (int)(self->std_button_count + self->extra_button_count);
      avail_width = value / (int)(self->std_button_count + self->extra_button_count);
      tmp = self->button_width;
      if ((int)self->button_width <= (int)avail_width) {
        tmp = avail_width;
      }
      self->button_width = tmp;
      if (self->button_width != avail_width) {
        extra_space = 0;
      }
      if ((self->style_flags & 0x100000) == 0) {
        if ((sprites_height != 0) || (content_height != 0)) {
          self->wnd_height += self->section_gap * 2;
        }
        value = dialog_line_height((DialogTextView *)self);
        self->wnd_height += value;
        if (self->border_width != 0) {
          if ((sprites_height != 0) || (content_height != 0)) {
            self->chrome_height += self->section_gap * 2;
          }
          value = dialog_line_height((DialogTextView *)self);
          self->chrome_height += value;
        }
      }
      remainder_acc = self->std_button_count + self->extra_button_count - 1;
      tmp = self->std_button_count;
      while (i = tmp - 1, -1 < (int)i) {
        pos = button_x - self->button_width;
        (&((Dialog *)self)->button_layout)[tmp * 2] = pos;
        button_x = pos - self->pad_x;
        for (remainder_acc = remainder_acc + extra_space; tmp = i,
            (int)(self->std_button_count + self->extra_button_count) <= remainder_acc;
            remainder_acc = remainder_acc - (self->std_button_count + self->extra_button_count)) {
          button_x--;
        }
      }
      tmp = self->extra_button_count;
      while (i = tmp - 1, -1 < (int)i) {
        pos = button_x - self->button_width;
        (&((Dialog *)self)->button_layout)[tmp * 2 + self->std_button_count * 2] = pos;
        button_x = pos - self->pad_x;
        for (remainder_acc = remainder_acc + extra_space; tmp = i,
            (int)(self->std_button_count + self->extra_button_count) <= remainder_acc;
            remainder_acc = remainder_acc - (self->std_button_count + self->extra_button_count)) {
          button_x--;
        }
      }
    }
    tmp = self->min_height;
    if ((int)self->min_height <= (int)self->wnd_height) {
      tmp = self->wnd_height;
    }
    self->wnd_height = tmp;
    tmp = self->wnd_height;
    value = dialog_line_height((DialogTextView *)self);
    self->button_y = tmp - (self->bevel_width + value + self->pad_y);
    if ((self->style_flags & 0x100000) == 0) {
      gfx_get_screen_rect((iptr)((i8 *)&screen_rect2.left));
      wnd_get_screen_rect((WndBase *)((i8 *)&main_frame_wnd_block.main_frame_wnd),(iptr)((i8 *)&frame_rect2.left));
      if (self->window_x == 0xfffffc19) {
        value = rect_width((RECT *)(iptr)((i8 *)&screen_rect2.left));
        self->window_x = (value >> 1) - ((int)self->wnd_width >> 1);
      }
      else if ((((int)self->window_x < 0) &&
               (self->window_x = self->window_x + ((screen_rect2.right - 1) - self->wnd_width),
               main_frame_created != 0)) && ((self->style_flags & 0x10000) != 0)) {
        value = wnd_frame_width((WndBase *)((i8 *)&main_frame_wnd_block.main_frame_wnd));
        self->window_x -= value;
      }
      if (self->window_y == 0xfffffc19) {
        value = rect_height((RECT *)(iptr)((i8 *)&screen_rect2.left));
        self->window_y = (value >> 1) - ((int)self->wnd_height >> 1);
      }
      else if ((int)self->window_y < 0) {
        if (-(screen_rect2.bottom - frame_rect2.bottom) < (int)self->window_y) {
          self->window_y -= (screen_rect2.bottom - frame_rect2.bottom);
        }
        self->window_y += ((screen_rect2.bottom - 1) - self->wnd_height);
        if ((main_frame_created != 0) && ((self->style_flags & 0x10000) != 0)) {
          value = wnd_nonclient_height((WndBase *)((i8 *)&main_frame_wnd_block.main_frame_wnd));
          self->window_y -= value;
        }
      }
      if ((dialog_clamp_overflow == 0) &&
         (value = rect_width((RECT *)(iptr)((i8 *)&screen_rect2.left)), (int)self->wnd_width <= value)) {
        rect_height((RECT *)(iptr)((i8 *)&screen_rect2.left));
      }
      self->list_x += self->origin_x;
      self->list_y += self->origin_y;
      self->text_x += self->origin_x;
      self->text_y += self->origin_y;
      self->edit_x += self->origin_x;
      self->edit_y += self->origin_y;
    }
    self->button_y += self->origin_y;
    for (i = 0; (int)i < (int)(self->std_button_count + self->extra_button_count);
        i = i + 1) {
      (&((Dialog *)self)->button_x_coords)[i * 2] = (&((Dialog *)self)->button_x_coords)[i * 2] + self->origin_x;
    }
    result = 0;
  }
  return result;
}

/* 005a0fea auto */
void __thiscall
dialog_draw_option_cell
          (DialogOptionDrawView *self,const char *text,int x,int y,int selected,int disabled)

{
  int col_width;
  int text_width;
  uptr text_len;
  u32 shadow_color2;
  u32 fg_color;
  
  while (*(char *)text != '\0') {
    col_width = *(int *)(((DialogOptionDrawViewExt *)self)->pane_column_widths + self->cur_pane * 4 - 4);
    text_width = font_text_width((GameFont *)self->list_font,text);
    if (text_width <= col_width - 6) break;
    text_len = _strlen((char *)text);
    *(i8 *)((text_len - 1) + text) = 0;
  }
  if (selected == 0) {
    fg_color = self->list_fg_color;
    shadow_color2 = self->list_fg_shadow_color;
  }
  else {
    fg_color = self->sel_text_color;
    shadow_color2 = self->sel_shadow_color;
  }
  if (shadow_color2 != fg_color) {
    gfx_set_text_color_index(shadow_color2);
    surface_draw_text
              ((DibSurface *)self->surface_value,self->list_font,text,x + 2,y + 1,5);
    gfx_set_text_color_index(fg_color);
    surface_draw_text
              ((DibSurface *)self->surface_value,self->list_font,text,x + 1,y,5);
  }
  if (disabled == 0) {
    gfx_set_text_color_index(fg_color);
  }
  else {
    gfx_set_text_color_index(self->highlight_color);
  }
  surface_draw_text
            ((DibSurface *)self->surface_value,self->list_font,text,x,y,5);
  return;
}

/* 005a1148 auto */
void __thiscall
dialog_draw_option_text
          (DialogOptionDrawView *self,char *text,int x,i32 y,i32 selected,
          i32 disabled)

{
  int col_width;
  char *separator;
  int right_width;
  char *right_text;
  
  right_text = (char *)0x0;
  separator = _strchr(text,0x7c);
  if (separator != (char *)0x0) {
    right_text = separator + 1;
    *separator = '\0';
  }
  dialog_draw_option_cell(self,(const char *)text,*(int *)(((DialogOptionDrawViewExt *)self)->pane_column_offsets + self->cur_pane * 4 - 4) + x
                     ,y,selected,disabled);
  if (right_text != (char *)0x0) {
    col_width = *(int *)(((DialogOptionDrawViewExt *)self)->pane_column_widths + self->cur_pane * 4 - 4);
    right_width = font_text_width((GameFont *)self->list_font,(const char *)right_text);
    dialog_draw_option_cell(self,(const char *)right_text,(col_width + x - 4) - right_width,y,selected,disabled);
    *separator = '|';
  }
  return;
}

/* 005a120b auto */
uint __thiscall dialog_draw_option(DialogOptionList *self,DialogOption *option,int blit)

{
  int rel_index;
  int group_index;
  int visible_count;
  RECT inner_rect;
  int row;
  int cell_y;
  int col;
  int cell_x;
  u32 fill_color;
  uint is_selected;
  RECT cell_rect;
  
  if (option == 0) {
    is_selected = 0;
  }
  else if (self->option_count == 0) {
    is_selected = 0;
  }
  else {
    rel_index = dialog_option_group_index(self,self->list_top_option[option->group]);
    group_index = dialog_option_group_index(self,option);
    rel_index = group_index - rel_index;
    if ((rel_index < 0) ||
       (visible_count = self->list_rows[option->group] * self->columns,
       visible_count - rel_index == 0 || visible_count < rel_index)) {
      is_selected = 0;
    }
    else {
      col = rel_index / (int)self->list_rows[option->group];
      row = rel_index % (int)self->list_rows[option->group];
      cell_x = (int)self->list_column_width[option->group] * col +
                 (int)self->list_origin_x[option->group];
      cell_y = (int)self->list_row_height[option->group] * row +
                 (int)self->list_origin_y[option->group];
      rect_set_xywh((iptr)&cell_rect,cell_x,cell_y,
                         (iptr)self->list_column_width[option->group],
                         (iptr)self->list_row_height[option->group]);
      is_selected = (uint)((uptr)self->selected_option == (iptr)option);
      if (is_selected == 0) {
        fill_color = self->list_fill_color;
      }
      else {
        fill_color = self->list_sel_fill_color;
      }
      inner_rect.left = cell_rect.left;
      inner_rect.top = cell_rect.top;
      inner_rect.right = cell_rect.right;
      inner_rect.bottom = cell_rect.bottom;
      if (self != (DialogOptionList *)0xfffffdf8) {
        inner_rect.left = cell_rect.left + (int)self->list_indents[option->group];
      }
      if ((self->on_draw_option == 0) ||
         (group_index = call_untyped((code *)self->on_draw_option, self,self->surf_wnd,option->id,group_index,cell_x,cell_y
                             ,(i32)self->list_row_height[option->group]),
         group_index == 0)) {
        if (is_selected != 0) {
          gfx_draw_bevel_rect(self->surf_wnd,&inner_rect,self->bevel_light_color,self->bevel_dark_color);
          rect_deflate((iptr)&inner_rect,1,1);
        }
        gfx_fill_rect(self->surf_wnd,&inner_rect,fill_color);
        dialog_draw_option_text
                  ((DialogOptionDrawView *)self,option->text,cell_x + 2,cell_y,is_selected,
                   option->flags & 1);
      }
      if (blit != 0) {
        wnd_blit_surface_rect((DibSurface *)self->surf_wnd,(iptr)&cell_rect);
      }
    }
  }
  return is_selected;
}

/* 005a14d2 auto */
void __thiscall dialog_draw_option_list(DialogOptionList *self)

{
  u8 *pane_drawn;
  u32 saved_pane;
  u32 pane;
  int first_index;
  DialogOption *option;
  uint drawn;
  i32 no_blit;
  int group_pos;
  u32 pane_idx;
  DialogOption *node2;
  int i;
  RECT clip_rect2;
  
  saved_pane = self->cur_pane;
  for (pane_idx = 0; (int)pane_idx < 2; pane_idx++) {
    if ((pane_idx != 1) || ((self->style_flags & 0x400000) != 0)) {
      self->cur_pane = pane_idx;
      pane_drawn = (u8 *)&self->pane_drawn[self->cur_pane];
      pane_drawn[0] = '\0';
      pane_drawn[1] = '\0';
      pane_drawn[2] = '\0';
      pane_drawn[3] = '\0';
      pane = self->cur_pane;
      clip_rect2.left = self->list_client_rect[pane].left;
      clip_rect2.top = self->list_client_rect[pane].top;
      clip_rect2.right = self->list_client_rect[pane].right;
      clip_rect2.bottom = self->list_client_rect[pane].bottom;
      if ((1 < (int)self->columns) || ((self->option_count == 0 || (self->on_draw_option != 0)))) {
        gfx_fill_rect(self->surf_wnd,&self->list_client_rect[self->cur_pane],
                           self->list_fill_color);
      }
      gfx_draw_rect_frame(self->surf_wnd,&self->pane_rect[self->cur_pane],
                         self->bevel_dark_color);
      surface_set_clip((DibSurface *)self->surf_wnd,&clip_rect2);
      if (self->option_count != 0) {
        node2 = dialog_title_font_obj_block.active_dialog->option_list;
        first_index = dialog_option_group_index(self,self->list_top_option[self->cur_pane]);
        group_pos = 0;
        for (i = 0; (node2 != 0 && (i < (int)self->option_count));
            i = i + 1) {
          if (self->cur_pane == (u32)node2->group) {
            if ((first_index <= group_pos) &&
               (group_pos < (int)(self->list_rows[self->cur_pane] * self->columns + first_index))) {
              no_blit = 0;
              option = dialog_option_at(self,group_pos);
              drawn = dialog_draw_option(self,option,no_blit);
              self->pane_drawn[self->cur_pane] =
                   self->pane_drawn[self->cur_pane] | drawn;
              clip_rect2.top += (int)self->list_row_height[self->cur_pane];
            }
            group_pos++;
          }
          node2 = node2->next;
        }
        if (((self->columns == 1) && (self->on_draw_option == 0)) &&
           (first_index = rect_height(&clip_rect2), 0 < first_index)) {
          gfx_fill_rect(self->surf_wnd,&clip_rect2,self->list_fill_color);
        }
      }
      surface_reset_clip((DibSurface *)self->surf_wnd);
      wnd_blit_surface_rect
                ((DibSurface *)self->surf_wnd,
                 (iptr)&self->pane_rect[self->cur_pane]);
    }
  }
  self->cur_pane = saved_pane;
  return;
}

/* 005a1766 auto */
int __thiscall dialog_column_of_index(DialogTextView *self,int index)

{
  if (self->columns != 1) {
    index = index / (int)self->list_rows[self->cur_pane];
  }
  return index;
}

/* 005a17a4 auto */
int __thiscall dialog_column_start_index(DialogTextView *self,int index)

{
  if (self->columns != 1) {
    index -= index % (int)self->list_rows[self->cur_pane];
  }
  return index;
}

/* 005a17e9 auto */
void __thiscall dialog_select_option(DialogOptionList *self,DialogOption *option,int redraw)

{
  DialogOption *prev_option;
  bool scrolled;
  int option_index;
  i32 top_option;
  iptr scroll_pos;
  int top_index;
  
  scrolled = false;
  if ((option != 0) && ((uptr)self->selected_option != (uptr)option)) {
    top_index = dialog_option_group_index(self,self->list_top_option[self->cur_pane]);
    option_index = dialog_option_group_index(self,option);
    if (option_index < top_index) {
      scrolled = true;
      top_index = option_index;
    }
    while ((int)(self->list_rows[self->cur_pane] * self->columns + top_index) <= option_index) {
      if (self->columns == 1) {
        top_index++;
      }
      else {
        top_index += self->list_rows[self->cur_pane];
      }
      scrolled = true;
    }
    top_option = dialog_column_start_index((DialogTextView *)self,self->option_count - 1);
    top_option = int_clamp_b(top_index,0,top_option);
    top_option = (i32)dialog_option_at(self,top_option);
    self->list_top_option[self->cur_pane] = (DialogOption *)top_option;
    prev_option = self->selected_option;
    self->selected_option = option;
    if ((scrolled) || (redraw == 0)) {
      if ((&((DialogTextLineView *)self)->list_vscroll_controls)[self->cur_pane] != 0) {
        scroll_pos = dialog_option_group_index(self,self->list_top_option[self->cur_pane]);
        scrollbar_set_pos
                  ((ClickControl *)(&((DialogTextLineView *)self)->list_vscroll_controls)[self->cur_pane],scroll_pos);
      }
      if ((&((DialogTextLineView *)self)->list_hscroll_controls)[self->cur_pane] != 0) {
        scroll_pos = dialog_column_of_option(self,self->list_top_option[self->cur_pane]);
        scrollbar_set_pos
                  ((ClickControl *)(&((DialogTextLineView *)self)->list_hscroll_controls)[self->cur_pane],scroll_pos);
      }
    }
    if (redraw != 0) {
      if (scrolled) {
        dialog_draw_option_list(self);
        if (self->on_select_change != 0) {
          call_untyped((code *)self->on_select_change, self,option->id);
        }
      }
      else {
        dialog_draw_option(self,prev_option,1);
        dialog_draw_option(self,option,1);
        if (self->on_select_change != 0) {
          call_untyped((code *)self->on_select_change, self,option->id);
        }
      }
    }
  }
  return;
}

/* 005a1a7d auto */
i32 __thiscall dialog_option_at_point(DialogOptionList *self,int x,int y)

{
  i32 result;
  int top_index;
  
  dialog_pick_pane_at((DialogWindowView *)self,x,y);
  if ((&((DialogTextLineView *)self)->list_hscroll_controls)[self->cur_pane] != 0) {
    if (x < self->list_client_rect[self->cur_pane].left) {
      return 0xfffffffd;
    }
    if (self->list_client_rect[self->cur_pane].right <= x) {
      return 0xfffffffc;
    }
  }
  if (y < self->list_client_rect[self->cur_pane].top) {
    result = 0xffffffff;
  }
  else if (y < self->list_client_rect[self->cur_pane].bottom) {
    if (x < self->list_client_rect[self->cur_pane].left) {
      result = 0xfffffffd;
    }
    else if (x < self->list_client_rect[self->cur_pane].right) {
      top_index = dialog_option_group_index(self,self->list_top_option[self->cur_pane]);
      result = int_clamp_b(self->list_rows[self->cur_pane] *
                           ((x - self->list_client_rect[self->cur_pane].left) /
                           (int)self->list_column_width[self->cur_pane]) +
                           (y - self->list_client_rect[self->cur_pane].top) /
                           (int)self->list_row_height[self->cur_pane] + top_index,0,
                           self->option_count - 1);
    }
    else {
      result = 0xfffffffc;
    }
  }
  else {
    result = 0xfffffffe;
  }
  return result;
}

/* 005a1c52 auto */
int __thiscall dialog_count_group_options(DialogOptionList *self,int group)

{
  DialogOption *node2;
  int count;
  
  count = 0;
  for (node2 = self->option_list; node2 != 0; node2 = node2->next) {
    if (node2->group == group) {
      count++;
    }
  }
  return count;
}

/* 005a1caf auto */
void __thiscall dialog_pick_pane_at(DialogWindowView *self,int x,int y)

{
  u32 prev_pane;
  
  prev_pane = self->cur_pane;
  if ((self->style_flags & 0x400000) == 0) {
    self->cur_pane = 0;
  }
  else {
    self->cur_pane = 0;
    if (((((y < self->pane_rect[0].top) || (self->pane_rect[0].bottom < y)) ||
         (x < self->pane_rect[0].left)) || (self->pane_rect[0].right < x)) &&
       (((self->cur_pane = 1, y < self->pane_rect[1].top || (self->pane_rect[1].bottom < y)) ||
        ((x < self->pane_rect[1].left || (self->pane_rect[1].right < x)))))) {
      self->cur_pane = prev_pane;
    }
  }
  return;
}

/* 005a1da3 auto */
void __cdecl dialog_list_on_vscroll(i32 scroll_pos)

{
  DialogOption *top_option;
  
  if (dialog_title_font_obj_block.active_dialog != 0) {
    dialog_title_font_obj_block.active_dialog->cur_pane = 0;
    top_option = dialog_option_at((DialogOptionList *)dialog_title_font_obj_block.active_dialog,scroll_pos);
    if ((int)dialog_title_font_obj_block.active_dialog->list_top_option[dialog_title_font_obj_block.active_dialog->cur_pane] != (iptr)top_option) {
      dialog_title_font_obj_block.active_dialog->list_top_option[dialog_title_font_obj_block.active_dialog->cur_pane] = top_option;
      dialog_draw_option_list((DialogOptionList *)dialog_title_font_obj_block.active_dialog);
    }
  }
  return;
}

/* 005a1e28 auto */
i32 __thiscall dialog_create_window(DialogWindowView *self)

{
  i32 result;
  SurfaceWindow *this_00;
  int surf_width;
  u32 new_size;
  SurfaceWindow *surf_wnd2;
  i32 wnd_style;
  i8 *palette;
  i8 *parent2;
  i8 *title;
  i8 empty_title[4];
  i32 saved_seh;
  i8 *seh_handler;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  if (self->surf_wnd == 0) {
    this_00 = (SurfaceWindow *)operator_new(0x114);
    eh_state = 0;
    if (this_00 == (SurfaceWindow *)0x0) {
      surf_wnd2 = 0;
    }
    else {
      surf_wnd2 = surfwnd_ctor(this_00);
    }
    eh_state = 0xffffffff;
    self->surf_wnd = (uptr)surf_wnd2;
    empty_title[0] = 0;
    title = (i8 *)self->title_text;
    if (title == (i8 *)0x0) {
      title = empty_title;
    }
    if ((self->style_flags & 0x10000) == 0) {
      wnd_style = 0xc02;
    }
    else {
      wnd_style = 0x842;
    }
    if ((*(i8 * *)&dlg_parent_window) == (i8 *)0x0) {
      if (main_frame_created == 0) {
        parent2 = (i8 *)0x0;
      }
      else {
        parent2 = ((i8 *)&main_frame_wnd_block.main_frame_wnd);
      }
    }
    else {
      parent2 = (*(i8 * *)&dlg_parent_window);
    }
    if ((*(i8 * *)&dlg_palette) == (i8 *)0x0) {
      palette = ((i8 *)&game_palette_block.game_palette);
    }
    else {
      palette = (*(i8 * *)&dlg_palette);
    }
    if (parent2 == (i8 *)0x0) {
      surface_wnd_create
                ((DibSurface *)self->surf_wnd,(iptr)title,wnd_style,self->window_x,
                 self->window_y,self->wnd_width,self->wnd_height,(iptr)&game_palette_block.game_palette);
    }
    else {
      wnd_create_with_surface
                ((DibSurface *)self->surf_wnd,(const char *)title,wnd_style,self->window_x,
                 self->window_y,self->wnd_width,self->wnd_height,(iptr)palette,(iptr)parent2);
    }
    if ((self->style_flags & 0x10000) == 0) {
      wnd_set_caption_height((WndBase *)(self->surf_wnd + 0x48),self->title_height);
    }
    surf_width = surface_get_width((DibSurface *)self->surf_wnd);
    if ((int)self->wnd_width <= surf_width) {
      new_size = surface_get_width((DibSurface *)self->surf_wnd);
      self->wnd_width = new_size;
    }
    surf_width = surface_get_height((DibSurface *)self->surf_wnd);
    if ((int)self->wnd_height <= surf_width) {
      new_size = surface_get_height((DibSurface *)self->surf_wnd);
      self->wnd_height = new_size;
    }
    wnd_set_redraw_callback((SurfaceWindow *)self->surf_wnd,(iptr)dialog_on_redraw);
    if ((*(int *)&dlg_pending_idle_callback) == 0) {
      if ((*(int *)&dlg_default_idle_callback) != 0) {
        wnd_set_modal_idle_callback((ModalMenuWindow *)(self->surf_wnd + 0x48),(*(int *)&dlg_default_idle_callback));
      }
    }
    else {
      wnd_set_modal_idle_callback((ModalMenuWindow *)(self->surf_wnd + 0x48),(*(int *)&dlg_pending_idle_callback));
      (*(int *)&dlg_pending_idle_callback) = 0;
    }
    if (dlg_pending_move_handler != 0) {
      wnd_set_move_handler((WndEventHandlers *)(self->surf_wnd + 0x58),dlg_pending_move_handler);
      dlg_pending_move_handler = 0;
    }
    result = 1;
  }
  else {
    result = 0;
  }
  return result;
}

/* 005a20f4 auto */
void __cdecl dialog_on_redraw(void)

{
  if (dialog_title_font_obj_block.active_dialog != 0) {
    dialog_render(dialog_title_font_obj_block.active_dialog);
  }
  return;
}

/* 005a211c auto */
void __thiscall dialog_create_controls(Dialog *self)

{
  uint is_checkbox;
  Control *ctrl_mem;
  InputControl *this_00;
  i32 value;
  int count;
  iptr pos;
  u32 x;
  i32 text;
  u32 zoom;
  iptr parent_198;
  int parent_194;
  iptr parent_190;
  iptr parent_18c;
  iptr parent_188;
  iptr parent_184;
  iptr parent_180;
  iptr parent_17c;
  iptr parent_178;
  iptr parent_174;
  iptr parent_170;
  int *buttons;
  u32 *edits;
  u32 *hotspots;
  InputControl *radio_group2;
  u32 *checkboxes2;
  Control *hscroll2;
  Control *vscroll2;
  Control *listbox22;
  Control *hscroll;
  Control *vscroll;
  Control *listbox3;
  int item_index;
  DialogEditField *edit_field;
  u32 y2;
  i8 *label;
  i8 rect[16];
  iptr label_count2;
  iptr button_id;
  uint is_listbox;
  DialogOption *option;
  DialogSprite *sprite;
  int i;
  i8 unused_flag;
  iptr width2;
  uint labels[41];
  i32 saved_seh;
  i8 *seh_handler;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  label_count2 = 0;
  if (self != dialog_title_font_obj_block.active_dialog) {
    if ((dialog_stack_depth < 0) || (0xf < dialog_stack_depth)) {
      err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_popupstackindex_0_popupstackindex_16,(iptr)&str_d_ss_franklinton_popup_1_cpp_2,0xc75);
    }
    dialog_stack_depth++;
    (*(Dialog * *)&net_session_block.dialog_stack_top) = self;
    dialog_title_font_obj_block.active_dialog = self;
    (((i32 *)&dialog_stack))[dialog_stack_depth] = (i32)self;
  }
  if ((self->style_flags & 0x200) == 0) {
    unused_flag = 0;
    ctrl_set_pending_font((iptr)dialog_title_font_obj_block.active_dialog->body_font);
    ui_set_button_font((iptr)&dialog_plain_font_obj_block.dialog_plain_font_obj);
    ui_set_ctrl_font((iptr)dialog_title_font_obj_block.active_dialog->body_font);
    ui_set_default_font((iptr)&dialog_plain_font_obj_block.dialog_plain_font_obj);
    is_checkbox = self->style_flags & 4;
    is_listbox = self->style_flags & 0x1000;
    if ((is_checkbox == 0) && (is_listbox == 0)) {
      if (0x28 < (int)self->option_count) {
        if (dialog_clamp_overflow == 0) {
          error_report(0xfffffff2,9,0,0x28,self->option_count);
        }
        else {
          self->option_count = 0x28;
        }
      }
      for (option = self->option_list; option != (DialogOption *)0x0;
          option = option->next) {
        labels[label_count2] = (uint)option->text;
        label_count2++;
      }
    }
    if (self->option_count != 0) {
      if (is_listbox == 0) {
        if (is_checkbox == 0) {
          this_00 = (InputControl *)operator_new(0x50);
          eh_state = 7;
          if (this_00 == (InputControl *)0x0) {
            radio_group2 = 0;
          }
          else {
            radio_group2 = radiogrp_ctor(this_00);
          }
          eh_state = 0xffffffff;
          self->radio_group = (uptr)radio_group2;
          x = self->columns;
          if ((int)x < 2) {
            x = 1;
          }
          rect_set_xywh((iptr)rect,self->list_x,self->list_y,self->option_width,
                             self->option_row_height *
                             ((int)((self->columns - 1) + self->option_count) / (int)x));
          if (self->surf_wnd == 0) {
            parent_18c = 0;
          }
          else {
            parent_18c = self->surf_wnd + 0x48;
          }
          radiogrp_create
                    ((RadioGroup *)self->radio_group,parent_18c,200,(iptr)rect,self->columns,
                     self->option_count,(iptr)labels);
          option = self->option_list;
          item_index = 0;
          for (; option != (DialogOption *)0x0; option = option->next) {
            if ((uint *)self->selected_option == ((uint *)option)) {
              radiogrp_set_selected((RadioGroupSetSelView *)self->radio_group,item_index);
            }
            if ((option->flags & 1) != 0) {
              radiogrp_disable_item((RadioGroupDisableView *)self->radio_group,item_index);
            }
            item_index++;
          }
          radiogrp_set_select_callback((Control *)self->radio_group,(iptr)dialog_radio_on_select);
          radiogrp_set_dblclick_callback((Control *)self->radio_group,(iptr)dialog_radio_on_dblclick);
        }
        else {
          x = self->option_count;
          checkboxes2 = (u32 *)operator_new(x * 0x3c + 4);
          eh_state = 6;
          if (checkboxes2 == (u32 *)0x0) {
            checkboxes2 = (u32 *)0x0;
          }
          else {
            *checkboxes2 = x;
            crt_vector_ctor_iterator(checkboxes2 + 1,0x3c,*checkboxes2,(code *)checkbox_elem_ctor,
                         (code *)checkbox_dtor);
            checkboxes2++;
          }
          eh_state = 0xffffffff;
          self->checkboxes = (uptr)checkboxes2;
          x = self->list_x;
          y2 = self->list_y;
          i = 0;
          for (option = self->option_list; option != (DialogOption *)0x0;
              option = option->next) {
            if (self->surf_wnd == 0) {
              parent_188 = 0;
            }
            else {
              parent_188 = self->surf_wnd + 0x48;
            }
            checkbox_create
                      ((Control *)(self->checkboxes + i * 0x3c),parent_188,i + 200
                       ,x,y2,(const char *)option->text);
            checkbox_set_checked
                      ((Control *)(self->checkboxes + i * 0x3c),option->flags & 4);
            if ((option->flags & 1) != 0) {
              checkbox_disable((CheckboxDisableView *)(self->checkboxes + i * 0x3c));
            }
            y2 += self->option_row_height;
            i++;
          }
        }
      }
      else {
        self->cur_pane = 0;
        if ((self->style_flags & 0x40000) == 0) {
          if (((int)(self->list_rows[self->cur_pane] * self->columns) < (int)self->option_count) ||
             ((self->style_flags & 0x1000000) != 0)) {
            if (self->columns == 1) {
              ctrl_mem = (Control *)operator_new(0x40);
              eh_state = 1;
              if (ctrl_mem == (Control *)0x0) {
                vscroll = 0;
              }
              else {
                vscroll = scrollbar_ctor(ctrl_mem);
              }
              eh_state = 0xffffffff;
              self->list_vscroll[self->cur_pane] = (i32)vscroll;
              if (self->surf_wnd == 0) {
                parent_174 = 0;
              }
              else {
                parent_174 = self->surf_wnd + 0x48;
              }
              scrollbar_create
                        ((Control *)self->list_vscroll[self->cur_pane],parent_174,
                         0xb,(iptr)&self->list_vscroll_rect[self->cur_pane],1);
              count = dialog_count_group_options((DialogOptionList *)self,self->cur_pane);
              scrollbar_set_range
                        ((Control *)self->list_vscroll[self->cur_pane],0,
                         count - 1);
              pos = dialog_option_group_index
                                ((DialogOptionList *)self,
                                 self->list_top_option[self->cur_pane]);
              scrollbar_set_pos
                        ((ClickControl *)self->list_vscroll[self->cur_pane],pos);
              scrollbar_set_page_size
                        ((Control *)self->list_vscroll[self->cur_pane],
                         self->list_rows[self->cur_pane] - 1);
              scrollbar_set_callback
                        ((Control *)self->list_vscroll[self->cur_pane],(iptr)dialog_list_on_vscroll);
              scrollbar_set_track_callback
                        ((ScrollbarTrackSetView *)self->list_vscroll[self->cur_pane],(iptr)dialog_list_on_vscroll);
            }
            else {
              ctrl_mem = (Control *)operator_new(0x40);
              eh_state = 2;
              if (ctrl_mem == (Control *)0x0) {
                hscroll = 0;
              }
              else {
                hscroll = scrollbar_ctor(ctrl_mem);
              }
              eh_state = 0xffffffff;
              self->list_hscroll[self->cur_pane] = (i32)hscroll;
              if (self->surf_wnd == 0) {
                parent_178 = 0;
              }
              else {
                parent_178 = self->surf_wnd + 0x48;
              }
              scrollbar_create
                        ((Control *)self->list_hscroll[self->cur_pane],parent_178,0xc,
                         (iptr)&self->list_hscroll_rect[self->cur_pane],0);
              count = dialog_count_group_options((DialogOptionList *)self,self->cur_pane);
              value = dialog_column_of_index((DialogTextView *)self,count - 1);
              scrollbar_set_range
                        ((Control *)self->list_hscroll[self->cur_pane],0,value);
              value = dialog_option_group_index
                                ((DialogOptionList *)self,
                                 self->list_top_option[self->cur_pane]);
              pos = dialog_column_of_index((DialogTextView *)self,value);
              scrollbar_set_pos
                        ((ClickControl *)self->list_hscroll[self->cur_pane],pos);
              scrollbar_set_page_size
                        ((Control *)self->list_hscroll[self->cur_pane],self->columns
                        );
              scrollbar_set_callback
                        ((Control *)self->list_hscroll[self->cur_pane],(iptr)dialog_list_on_hscroll);
              scrollbar_set_track_callback
                        ((ScrollbarTrackSetView *)self->list_hscroll[self->cur_pane],(iptr)dialog_list_on_hscroll);
            }
          }
          wnd_set_lbuttondown_handler((WndHandlersMouseSetView *)(self->surf_wnd + 0x58),(iptr)dialog_list_on_lbuttondown);
          wnd_set_lbuttonup_any_handler((WndHandlersMouseSetView *)(self->surf_wnd + 0x58),(iptr)dialog_list_on_lbuttonup);
          wnd_set_mousemove_handler((WndHandlersMouseSetView *)(self->surf_wnd + 0x58),(iptr)dialog_list_on_mousemove);
          wnd_set_dblclick_handler((WndHandlersMouseSetView *)(self->surf_wnd + 0x58),(iptr)dialog_list_on_dblclick);
        }
        else {
          ctrl_mem = (Control *)operator_new(0x3c);
          eh_state = 0;
          if (ctrl_mem == (Control *)0x0) {
            listbox3 = 0;
          }
          else {
            listbox3 = checkbox_ctor(ctrl_mem);
          }
          eh_state = 0xffffffff;
          self->listbox[self->cur_pane] = (i32)listbox3;
          rect_set_xywh((iptr)rect,self->list_x,self->list_y,
                             self->list_width[self->cur_pane],self->list_height[self->cur_pane]);
          if (self->surf_wnd == 0) {
            parent_170 = 0;
          }
          else {
            parent_170 = self->surf_wnd + 0x48;
          }
          listbox_create
                    ((Control *)self->listbox[self->cur_pane],parent_170,10,
                     (iptr)rect);
          option = self->option_list;
          item_index = 0;
          for (; option != (DialogOption *)0x0; option = option->next) {
            if (self->cur_pane == (uint)option->group) {
              listbox_add_string
                        ((ListBoxAddView *)self->listbox[self->cur_pane],(const char *)option->text);
              if ((uint *)self->selected_option == ((uint *)option)) {
                listbox_set_cur_sel
                          ((ListBoxSetSelView *)self->listbox[self->cur_pane],item_index);
              }
              item_index++;
            }
          }
          listbox_set_dblclick_callback
                    ((ListBoxDblClickSetView *)self->listbox[self->cur_pane],(iptr)dialog_listbox_on_dblclick);
        }
        if ((self->style_flags & 0x400000) != 0) {
          self->cur_pane = 1;
          if ((self->style_flags & 0x40000) == 0) {
            if (((int)(self->list_rows[self->cur_pane] * self->columns) < (int)self->option_count) ||
               ((self->style_flags & 0x1000000) != 0)) {
              if (self->columns == 1) {
                ctrl_mem = (Control *)operator_new(0x40);
                eh_state = 4;
                if (ctrl_mem == (Control *)0x0) {
                  vscroll2 = 0;
                }
                else {
                  vscroll2 = scrollbar_ctor(ctrl_mem);
                }
                eh_state = 0xffffffff;
                self->list_vscroll[self->cur_pane] = (i32)vscroll2;
                if (self->surf_wnd == 0) {
                  parent_180 = 0;
                }
                else {
                  parent_180 = self->surf_wnd + 0x48;
                }
                scrollbar_create
                          ((Control *)self->list_vscroll[self->cur_pane],parent_180
                           ,0xb,(iptr)&self->list_vscroll_rect[self->cur_pane],1);
                count = dialog_count_group_options((DialogOptionList *)self,self->cur_pane);
                scrollbar_set_range
                          ((Control *)self->list_vscroll[self->cur_pane],0,
                           count - 1);
                pos = dialog_option_group_index
                                  ((DialogOptionList *)self,
                                   self->list_top_option[self->cur_pane]);
                scrollbar_set_pos
                          ((ClickControl *)self->list_vscroll[self->cur_pane],pos);
                scrollbar_set_page_size
                          ((Control *)self->list_vscroll[self->cur_pane],
                           self->list_rows[self->cur_pane] - 1);
                scrollbar_set_callback
                          ((Control *)self->list_vscroll[self->cur_pane],(iptr)dialog_list2_on_vscroll)
                ;
                scrollbar_set_track_callback
                          ((ScrollbarTrackSetView *)self->list_vscroll[self->cur_pane],(iptr)dialog_list2_on_vscroll);
              }
              else {
                ctrl_mem = (Control *)operator_new(0x40);
                eh_state = 5;
                if (ctrl_mem == (Control *)0x0) {
                  hscroll2 = 0;
                }
                else {
                  hscroll2 = scrollbar_ctor(ctrl_mem);
                }
                eh_state = 0xffffffff;
                self->list_hscroll[self->cur_pane] = (i32)hscroll2;
                if (self->surf_wnd == 0) {
                  parent_184 = 0;
                }
                else {
                  parent_184 = self->surf_wnd + 0x48;
                }
                scrollbar_create
                          ((Control *)self->list_hscroll[self->cur_pane],parent_184,
                           0xc,(iptr)&self->list_hscroll_rect[self->cur_pane],0);
                count = dialog_count_group_options((DialogOptionList *)self,self->cur_pane);
                value = dialog_column_of_index((DialogTextView *)self,count - 1);
                scrollbar_set_range
                          ((Control *)self->list_hscroll[self->cur_pane],0,value);
                value = dialog_option_group_index
                                  ((DialogOptionList *)self,
                                   self->list_top_option[self->cur_pane]);
                pos = dialog_column_of_index((DialogTextView *)self,value);
                scrollbar_set_pos
                          ((ClickControl *)self->list_hscroll[self->cur_pane],pos);
                scrollbar_set_page_size
                          ((Control *)self->list_hscroll[self->cur_pane],
                           self->columns);
                scrollbar_set_callback
                          ((Control *)self->list_hscroll[self->cur_pane],(iptr)dialog_list2_on_hscroll);
                scrollbar_set_track_callback
                          ((ScrollbarTrackSetView *)self->list_hscroll[self->cur_pane],(iptr)dialog_list2_on_hscroll);
              }
            }
          }
          else {
            ctrl_mem = (Control *)operator_new(0x3c);
            eh_state = 3;
            if (ctrl_mem == (Control *)0x0) {
              listbox22 = 0;
            }
            else {
              listbox22 = checkbox_ctor(ctrl_mem);
            }
            eh_state = 0xffffffff;
            self->listbox[self->cur_pane] = (i32)listbox22;
            rect_set_xywh((iptr)rect,self->list_x,self->list_y,
                               self->list_width[self->cur_pane],self->list_height[self->cur_pane]);
            if (self->surf_wnd == 0) {
              parent_17c = 0;
            }
            else {
              parent_17c = self->surf_wnd + 0x48;
            }
            listbox_create
                      ((Control *)self->listbox[self->cur_pane],parent_17c,10,
                       (iptr)rect);
            option = self->option_list;
            item_index = 0;
            for (; option != (DialogOption *)0x0; option = option->next) {
              if (self->cur_pane == (uint)option->group) {
                listbox_add_string
                          ((ListBoxAddView *)self->listbox[self->cur_pane],(const char *)option->text);
                if ((uint *)self->selected_option == ((uint *)option)) {
                  listbox_set_cur_sel
                            ((ListBoxSetSelView *)self->listbox[self->cur_pane],item_index);
                }
                item_index++;
              }
            }
            listbox_set_dblclick_callback
                      ((ListBoxDblClickSetView *)self->listbox[self->cur_pane],(iptr)dialog_listbox_on_dblclick);
          }
          self->cur_pane = 0;
        }
      }
    }
    if ((1 < (int)self->sprite_count) && (self->option_count == 0)) {
      x = self->sprite_count;
      hotspots = (u32 *)operator_new(x * 0x40 + 4);
      eh_state = 8;
      if (hotspots == (u32 *)0x0) {
        hotspots = (u32 *)0x0;
      }
      else {
        *hotspots = x;
        crt_vector_ctor_iterator(hotspots + 1,0x40,*hotspots,(code *)hotspot_ctor,
                     (code *)hotspot_dtor);
        hotspots++;
      }
      eh_state = 0xffffffff;
      self->sprite_hotspots = (uptr)hotspots;
      x = self->sprite_x;
      y2 = self->sprite_y;
      sprite = self->sprite_list;
      i = 0;
      for (; sprite != 0; sprite = sprite->next) {
        width2 = gfx_zoom_scale(self->max_sprite_width,self->sprite_zoom);
        zoom = self->sprite_zoom;
        value = sprite_height(sprite->sprite);
        count = gfx_zoom_scale(value,zoom);
        rect_set_xywh((iptr)rect,x,y2,width2,count);
        if (self->surf_wnd == 0) {
          parent_190 = 0;
        }
        else {
          parent_190 = self->surf_wnd + 0x48;
        }
        hotspot_create
                  ((ClickControl *)(self->sprite_hotspots + i * 0x40),parent_190,i + 300,
                   (iptr)rect);
        hotspot_set_click_callback((HotspotClickSetView *)(self->sprite_hotspots + i * 0x40),(iptr)dialog_on_sprite_click);
        hotspot_set_dblclick_callback((HotspotDblClickSetView *)(self->sprite_hotspots + i * 0x40),(iptr)dialog_sprite_on_dblclick);
        y2 = y2 + self->section_gap + count;
        i++;
      }
    }
    if (self->edit_field_list != 0) {
      edit_field = self->edit_field_list;
      x = self->edit_count;
      edits = (u32 *)operator_new(x * 0x48 + 4);
      eh_state = 9;
      if (edits == (u32 *)0x0) {
        edits = (u32 *)0x0;
      }
      else {
        *edits = x;
        crt_vector_ctor_iterator(edits + 1,0x48,*edits,(code *)edit_ctor,
                     (code *)edit_dtor);
        edits++;
      }
      eh_state = 0xffffffff;
      self->edit_controls = (uptr)edits;
      i = 0;
      for (; edit_field != 0; edit_field = edit_field->next) {
        if (self->surf_wnd == 0) {
          parent_194 = 0;
        }
        else {
          parent_194 = self->surf_wnd + 0x48;
        }
        value = (i32)edit_field->buffer;
        text = edit_field->width;
        count = dialog_edit_row_height((DialogCore *)self);
        edit_create_at
                  ((EditControl *)(self->edit_controls + i * 0x48),parent_194,0x14,
                   self->edit_x + self->edit_label_width,count * i + self->edit_y,text,(const char *)value)
        ;
        if (2 < game.multiplayer) {
          edit_set_change_callback((EditChangeSetView *)(self->edit_controls + i * 0x48),(iptr)dialog_edit_on_change)
          ;
        }
        edit_set_max_len
                  ((EditMaxLenView *)(self->edit_controls + i * 0x48),edit_field->max_len);
        i++;
      }
    }
    if (self->std_button_count + self->extra_button_count != 0) {
      count = self->std_button_count + self->extra_button_count;
      buttons = (int *)operator_new(count * 0x3c + 4);
      eh_state = 10;
      if (buttons == (int *)0x0) {
        buttons = (int *)0x0;
      }
      else {
        *buttons = count;
        crt_vector_ctor_iterator(buttons + 1,0x3c,*buttons,(code *)button_ctor,
                     (code *)ctrl_dtor);
        buttons++;
      }
      eh_state = 0xffffffff;
      self->button_controls = (uptr)buttons;
    }
    for (i = 0; i < (int)(self->std_button_count + self->extra_button_count); i++) {
      if (i < (int)self->std_button_count) {
        button_id = *(iptr *)((u8 *)&self->extra_button_labels + i * 8 + 0x18);
        label = (((i8 * *)&dialog_button_labels))[button_id];
      }
      else {
        button_id = -1;
        label = *(i8 **)((int)self + (i - self->std_button_count) * 4 + 0x294);
      }
      pos = dialog_line_height((DialogTextView *)self);
      rect_set_xywh((iptr)rect,*(i32 *)((u8 *)&self->extra_button_labels + i * 8 + 0x1c),
                         self->button_y,self->button_width,pos);
      if (self->surf_wnd == 0) {
        parent_198 = 0;
      }
      else {
        parent_198 = self->surf_wnd + 0x48;
      }
      button_create
                ((Control *)(self->button_controls + i * 0x3c),parent_198,i + 100,
                 (iptr)rect,(const char *)label);
      if ((button_id == 2) || ((button_id == 0 && ((self->style_flags & 1) == 0)))) {
        ctrl_set_cancel_button((Control *)(self->button_controls + i * 0x3c));
      }
      if (button_id == 0) {
        ctrl_set_default_button((Control *)(self->button_controls + i * 0x3c));
      }
      button_set_callback
                ((Control *)(self->button_controls + i * 0x3c),(iptr)dialog_on_button_click);
    }
    wnd_set_keydown_handler((WndEventHandlers *)(self->surf_wnd + 0x58),(iptr)dialog_on_keydown);
    wnd_set_char_handler((WndEventHandlers *)(self->surf_wnd + 0x58),(iptr)dialog_on_char);
    self->style_flags = self->style_flags | 0x200;
  }
  return;
}

/* 005a3bae auto */
void __cdecl dialog_radio_on_dblclick(i32 ctrl_id,int item)

{
  DialogOption *found;
  i32 index;
  DialogOption *node2;
  
  found = 0;
  if (dialog_title_font_obj_block.active_dialog != 0) {
    index = 0;
    for (node2 = dialog_title_font_obj_block.active_dialog->option_list; node2 != 0;
        node2 = node2->next) {
      if (item == index) {
        found = node2;
      }
      index++;
    }
    dialog_title_font_obj_block.active_dialog->result_id = 0xffffffff;
    if (found != 0) {
      dialog_title_font_obj_block.active_dialog->result_id = found->id;
    }
    dialog_title_font_obj_block.active_dialog->style_flags = dialog_title_font_obj_block.active_dialog->style_flags | 0x2000;
    dialog_end_current();
  }
  return;
}

/* 005a3c58 auto */
void __cdecl dialog_end_current(void)

{
  dialog_title_font_obj_block.active_dialog->style_flags = dialog_title_font_obj_block.active_dialog->style_flags | 0x400;
  wnd_end_modal_loop((ModalMenuWindow *)((int)dialog_title_font_obj_block.active_dialog->surf_wnd + 0x48));
  return;
}

/* 005a3c83 auto */
void __cdecl dialog_listbox_on_dblclick(void)

{
  if ((dialog_title_font_obj_block.active_dialog != 0) && ((*(byte *)((iptr)dialog_title_font_obj_block.active_dialog + 0x3d) & 4) == 0)) {
    dialog_title_font_obj_block.active_dialog->style_flags = dialog_title_font_obj_block.active_dialog->style_flags | 0x2000;
    dialog_end_current();
  }
  return;
}

/* 005a3cca auto */
void __cdecl dialog_on_sprite_click(int ctrl_id)

{
  bool changed;
  int done;
  i32 *sprite;
  int i;
  
  changed = false;
  sprite = *(i32 **)((iptr)dialog_title_font_obj_block.active_dialog + 0x234);
  if (sprite != (i32 *)0x0) {
    for (i = 0; i < ctrl_id - 300; i++) {
      sprite = (i32 *)sprite[4];
      if (sprite == (i32 *)0x0) {
        return;
      }
    }
    dialog_title_font_obj_block.active_dialog->result_id = *sprite;
    if ((*(i32 **)((iptr)dialog_title_font_obj_block.active_dialog + 0x224) != sprite) &&
       (*(i32 **)((iptr)dialog_title_font_obj_block.active_dialog + 0x224) = sprite,
       (*(byte *)((iptr)dialog_title_font_obj_block.active_dialog + 0x3e) & 2) != 0)) {
      changed = true;
    }
    if (dialog_title_font_obj_block.active_dialog->on_sprite_click == 0) {
      if (changed) {
        dialog_render(dialog_title_font_obj_block.active_dialog);
      }
    }
    else {
      done = call_untyped(((code **)dialog_title_font_obj_block.active_dialog)[143], *sprite);
      dialog_render(dialog_title_font_obj_block.active_dialog);
      if (done != 0) {
        dialog_title_font_obj_block.active_dialog->style_flags = dialog_title_font_obj_block.active_dialog->style_flags | 0x2000;
        dialog_end_current();
      }
    }
  }
  return;
}

/* 005a3df3 auto */
void __cdecl dialog_sprite_on_dblclick(void)

{
  int done;
  
  if (dialog_title_font_obj_block.active_dialog->on_sprite_dblclick != 0) {
    done = call_untyped(((code **)dialog_title_font_obj_block.active_dialog)[144], 0);
    if (done == 0) {
      dialog_render(dialog_title_font_obj_block.active_dialog);
    }
    else {
      dialog_title_font_obj_block.active_dialog->style_flags = dialog_title_font_obj_block.active_dialog->style_flags | 0x2000;
      dialog_end_current();
    }
  }
  return;
}

/* 005a3e56 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl dialog_on_button_click(int ctrl_id)

{
  int button_index;
  int sprite_index;
  DialogOption *found;
  int button_id;
  int index;
  DialogOption *node2;
  DialogSprite *sprite;
  
  if (dialog_title_font_obj_block.active_dialog != 0) {
    dialog_title_font_obj_block.dialog_timeout_start_i32 = timer_ticks();
    button_index = ctrl_id - 100;
    if (button_index < (int)dialog_title_font_obj_block.active_dialog->std_button_count) {
      button_id = *(int *)((iptr)dialog_title_font_obj_block.active_dialog + 0x2ac + button_index * 8);
    }
    else {
      dialog_title_font_obj_block.active_dialog->result_extra = (button_index - (int)dialog_title_font_obj_block.active_dialog->std_button_count) + 1;
      button_id = 0;
    }
    if (button_id == 1) {
      dialog_title_font_obj_block.active_dialog->style_flags = dialog_title_font_obj_block.active_dialog->style_flags | 0x80;
    }
    if (((button_id == 0) && ((*(byte *)((iptr)dialog_title_font_obj_block.active_dialog + 0x3e) & 2) != 0)) &&
       (dialog_title_font_obj_block.active_dialog->selected_sprite != 0)) {
      sprite = dialog_title_font_obj_block.active_dialog->sprite_list;
      sprite_index = 0;
      for (; (sprite != 0 && ((int)dialog_title_font_obj_block.active_dialog->selected_sprite != (iptr)sprite));
          sprite = sprite->next) {
        sprite_index++;
      }
      if (sprite != 0) {
        dialog_on_sprite_click(sprite_index + 300);
      }
    }
    if (button_id == 2) {
      dialog_title_font_obj_block.active_dialog->result_id = 0xffffffff;
    }
    else {
      if (((int)dialog_title_font_obj_block.active_dialog->sprite_count < 2) || (dialog_title_font_obj_block.active_dialog->option_count != 0)) {
        dialog_title_font_obj_block.active_dialog->result_id = 0;
      }
      if ((dialog_title_font_obj_block.active_dialog->option_count != 0) && ((dialog_title_font_obj_block.active_dialog->style_flags & 0x1004) == 0)
         ) {
        index = 0;
        found = 0;
        node2 = dialog_title_font_obj_block.active_dialog->option_list;
        button_index = radiogrp_get_selected(*(RadioGroupGetSelView **)((iptr)dialog_title_font_obj_block.active_dialog + 0x268));
        for (; node2 != 0; node2 = node2->next) {
          if (button_index == index) {
            found = node2;
          }
          index++;
        }
        if (found != 0) {
          dialog_title_font_obj_block.active_dialog->result_id = found->id;
        }
      }
    }
    dialog_end_current();
  }
  return;
}

/* 005a407f auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl dialog_on_keydown(i32 key)

{
  int count;
  DialogOption *option;
  int index;
  int pos;
  i32 redraw;
  DialogSprite *sprite;
  DialogOption *node2;
  
  if (dialog_title_font_obj_block.active_dialog == 0) {
    return;
  }
  if (((*(byte *)((iptr)dialog_title_font_obj_block.active_dialog + 0x3d) & 0x10) == 0) || (dialog_title_font_obj_block.active_dialog->edit_count != 0)) {
    dialog_title_font_obj_block.dialog_timeout_start_i32 = timer_ticks();
  }
  if ((*(byte *)((iptr)dialog_title_font_obj_block.active_dialog + 0x3e) & 2) != 0) {
    switch(key) {
    case 0xa2:
    case 0xc1:
      dialog_title_font_obj_block.active_dialog->selected_sprite =
           (DialogSprite *)*(i32 *)((int)dialog_title_font_obj_block.active_dialog->selected_sprite + 0x10);
      if (dialog_title_font_obj_block.active_dialog->selected_sprite == 0) {
        dialog_title_font_obj_block.active_dialog->selected_sprite = dialog_title_font_obj_block.active_dialog->sprite_list;
      }
      dialog_render(dialog_title_font_obj_block.active_dialog);
      break;
    case 0xa8:
    case 0xc0:
      for (sprite = dialog_title_font_obj_block.active_dialog->sprite_list;
          ((sprite != 0 && ((int)sprite->next != (int)dialog_title_font_obj_block.active_dialog->selected_sprite)) &&
          (sprite->next != 0)); sprite = sprite->next) {
      }
      dialog_title_font_obj_block.active_dialog->selected_sprite = sprite;
      dialog_render(dialog_title_font_obj_block.active_dialog);
      break;
    case 0xd1:
      if (dialog_title_font_obj_block.active_dialog->selected_sprite != 0) {
        dialog_on_sprite_click(**(i32 **)((iptr)dialog_title_font_obj_block.active_dialog + 0x224));
      }
    }
  }
  if ((dialog_title_font_obj_block.active_dialog->style_flags & 0x41000) != 0x1000) {
    return;
  }
  if (dialog_title_font_obj_block.active_dialog->option_count == 0) {
    key = 0;
  }
  do {
    switch(key) {
    case 0xa1:
    case 199:
      index = dialog_option_group_index
                        ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,dialog_title_font_obj_block.active_dialog->selected_option);
      pos = dialog_count_group_options
                        ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,(i32)dialog_title_font_obj_block.active_dialog->cur_pane);
      if (pos - 1 <= index) {
        return;
      }
      index = dialog_count_group_options
                        ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,(i32)dialog_title_font_obj_block.active_dialog->cur_pane);
      redraw = (i32)dialog_option_at((DialogOptionList *)dialog_title_font_obj_block.active_dialog,index - 1);
      dialog_title_font_obj_block.active_dialog->list_top_option[dialog_title_font_obj_block.active_dialog->cur_pane] = (DialogOption *)redraw;
      dialog_select_option
                ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,
                 dialog_title_font_obj_block.active_dialog->list_top_option[dialog_title_font_obj_block.active_dialog->cur_pane],0);
      dialog_draw_option_list((DialogOptionList *)dialog_title_font_obj_block.active_dialog);
      return;
    case 0xa2:
    case 0xc1:
      node2 = dialog_title_font_obj_block.active_dialog->selected_option;
      goto find_next_option;
    case 0xa3:
    case 0xc6:
      if ((int)dialog_title_font_obj_block.active_dialog->columns < 2) {
        pos = dialog_option_group_index
                          ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,dialog_title_font_obj_block.active_dialog->selected_option);
        index = (int)dialog_title_font_obj_block.active_dialog->list_rows[dialog_title_font_obj_block.active_dialog->cur_pane];
        count = dialog_count_group_options
                          ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,(i32)dialog_title_font_obj_block.active_dialog->cur_pane);
        if (index + pos < count) {
          redraw = 1;
          option = (dialog_option_at
                            ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,
                             pos + (int)dialog_title_font_obj_block.active_dialog->list_rows[dialog_title_font_obj_block.active_dialog->cur_pane]));
          dialog_select_option((DialogOptionList *)dialog_title_font_obj_block.active_dialog,option,redraw);
          return;
        }
        index = dialog_count_group_options
                          ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,(i32)dialog_title_font_obj_block.active_dialog->cur_pane);
        redraw = 1;
        option = dialog_option_at((DialogOptionList *)dialog_title_font_obj_block.active_dialog,index - 1);
        dialog_select_option((DialogOptionList *)dialog_title_font_obj_block.active_dialog,option,redraw);
        return;
      }
      key = 0xc3;
      break;
    case 0xa4:
    case 0xc2:
      if ((int)dialog_title_font_obj_block.active_dialog->columns != 1) {
        index = dialog_option_group_index
                          ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,dialog_title_font_obj_block.active_dialog->selected_option);
        pos = dialog_option_group_index
                          ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,
                           dialog_title_font_obj_block.active_dialog->list_top_option[dialog_title_font_obj_block.active_dialog->cur_pane]);
        if ((int)dialog_title_font_obj_block.active_dialog->list_rows[dialog_title_font_obj_block.active_dialog->cur_pane] + pos <= index) {
          redraw = 1;
          option = (dialog_option_at
                            ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,
                             index - (int)dialog_title_font_obj_block.active_dialog->list_rows[dialog_title_font_obj_block.active_dialog->cur_pane]));
          dialog_select_option((DialogOptionList *)dialog_title_font_obj_block.active_dialog,option,redraw);
          return;
        }
        if (index < (int)dialog_title_font_obj_block.active_dialog->list_rows[dialog_title_font_obj_block.active_dialog->cur_pane]) {
          return;
        }
        index = dialog_option_group_index
                          ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,
                           dialog_title_font_obj_block.active_dialog->list_top_option[dialog_title_font_obj_block.active_dialog->cur_pane]);
        redraw = (i32)dialog_option_at
                          ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,
                           index - (int)dialog_title_font_obj_block.active_dialog->list_rows[dialog_title_font_obj_block.active_dialog->cur_pane]);
        dialog_title_font_obj_block.active_dialog->list_top_option[dialog_title_font_obj_block.active_dialog->cur_pane] = (DialogOption *)redraw;
        index = dialog_option_group_index
                          ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,dialog_title_font_obj_block.active_dialog->selected_option);
        redraw = 0;
        option = (dialog_option_at
                          ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,
                           index - (int)dialog_title_font_obj_block.active_dialog->list_rows[dialog_title_font_obj_block.active_dialog->cur_pane]));
        dialog_select_option((DialogOptionList *)dialog_title_font_obj_block.active_dialog,option,redraw);
        dialog_draw_option_list((DialogOptionList *)dialog_title_font_obj_block.active_dialog);
        return;
      }
      key = 0xc0;
      break;
    default:
      return;
    case 0xa6:
    case 0xc3:
      if ((int)dialog_title_font_obj_block.active_dialog->columns != 1) {
        pos = dialog_option_group_index
                          ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,dialog_title_font_obj_block.active_dialog->selected_option);
        index = (int)dialog_title_font_obj_block.active_dialog->list_rows[dialog_title_font_obj_block.active_dialog->cur_pane];
        count = dialog_count_group_options
                          ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,(i32)dialog_title_font_obj_block.active_dialog->cur_pane);
        if (count <= index + pos) {
          return;
        }
        redraw = 1;
        option = (dialog_option_at
                          ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,
                           pos + (int)dialog_title_font_obj_block.active_dialog->list_rows[dialog_title_font_obj_block.active_dialog->cur_pane]));
        dialog_select_option((DialogOptionList *)dialog_title_font_obj_block.active_dialog,option,redraw);
        return;
      }
      key = 0xc1;
      break;
    case 0xa7:
    case 0xc4:
      index = dialog_option_group_index
                        ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,dialog_title_font_obj_block.active_dialog->selected_option);
      if (index < 1) {
        return;
      }
      redraw = (i32)dialog_option_at((DialogOptionList *)dialog_title_font_obj_block.active_dialog,0);
      dialog_title_font_obj_block.active_dialog->list_top_option[dialog_title_font_obj_block.active_dialog->cur_pane] = (DialogOption *)redraw;
      dialog_select_option
                ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,
                 dialog_title_font_obj_block.active_dialog->list_top_option[dialog_title_font_obj_block.active_dialog->cur_pane],0);
      dialog_draw_option_list((DialogOptionList *)dialog_title_font_obj_block.active_dialog);
      return;
    case 0xa8:
    case 0xc0:
      node2 = dialog_title_font_obj_block.active_dialog->selected_option;
      goto find_prev_option;
    case 0xa9:
    case 0xc5:
      if ((int)dialog_title_font_obj_block.active_dialog->columns < 2) {
        index = dialog_option_group_index
                          ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,dialog_title_font_obj_block.active_dialog->selected_option);
        if ((int)dialog_title_font_obj_block.active_dialog->list_rows[dialog_title_font_obj_block.active_dialog->cur_pane] <= index) {
          redraw = 1;
          option = (dialog_option_at
                            ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,
                             index - (int)dialog_title_font_obj_block.active_dialog->list_rows[dialog_title_font_obj_block.active_dialog->cur_pane]));
          dialog_select_option((DialogOptionList *)dialog_title_font_obj_block.active_dialog,option,redraw);
          return;
        }
        redraw = 1;
        option = dialog_option_at((DialogOptionList *)dialog_title_font_obj_block.active_dialog,0);
        dialog_select_option((DialogOptionList *)dialog_title_font_obj_block.active_dialog,option,redraw);
        return;
      }
      key = 0xc2;
    }
  } while( true );
  while (node2 = node2->prev,
        (int)dialog_title_font_obj_block.active_dialog->cur_pane != node2->group) {
find_prev_option:
    if (node2->prev == 0) break;
  }
  if ((int)dialog_title_font_obj_block.active_dialog->cur_pane != node2->group) {
    return;
  }
  if (dialog_title_font_obj_block.active_dialog->selected_option == node2) {
    return;
  }
  if ((int)dialog_title_font_obj_block.active_dialog->columns != 1) {
    index = dialog_option_group_index
                      ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,
                       dialog_title_font_obj_block.active_dialog->list_top_option[dialog_title_font_obj_block.active_dialog->cur_pane]);
    pos = dialog_option_group_index((DialogOptionList *)dialog_title_font_obj_block.active_dialog,node2);
    if (pos < index) {
      index = dialog_option_group_index
                        ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,
                         dialog_title_font_obj_block.active_dialog->list_top_option[dialog_title_font_obj_block.active_dialog->cur_pane]);
      redraw = (i32)dialog_option_at
                        ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,
                         index - (int)dialog_title_font_obj_block.active_dialog->list_rows[dialog_title_font_obj_block.active_dialog->cur_pane]
                        );
      dialog_title_font_obj_block.active_dialog->list_top_option[dialog_title_font_obj_block.active_dialog->cur_pane] = (DialogOption *)redraw;
      dialog_select_option((DialogOptionList *)dialog_title_font_obj_block.active_dialog,node2,0);
      dialog_draw_option_list((DialogOptionList *)dialog_title_font_obj_block.active_dialog);
      return;
    }
  }
  dialog_select_option((DialogOptionList *)dialog_title_font_obj_block.active_dialog,node2,1);
  return;
  while (node2 = node2->next,
        (int)dialog_title_font_obj_block.active_dialog->cur_pane != node2->group) {
find_next_option:
    if (node2->next == 0) break;
  }
  if (((int)dialog_title_font_obj_block.active_dialog->cur_pane == node2->group) &&
     (dialog_title_font_obj_block.active_dialog->selected_option != node2)) {
    dialog_select_option((DialogOptionList *)dialog_title_font_obj_block.active_dialog,node2,1);
  }
  return;
}

/* 005a49c1 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl dialog_on_char(byte ch)

{
  int target_index;
  uint upper_ch;
  uint first_ch;
  int top_index;
  int bottom_index;
  DialogOption *top_option;
  iptr match_index;
  DialogOption *match;
  DialogOption *node2;
  iptr counter2;
  
  if ((dialog_title_font_obj_block.active_dialog != 0) && (target_index = _isalpha((uint)ch), target_index != 0)) {
    dialog_title_font_obj_block.dialog_timeout_start_i32 = timer_ticks();
    upper_ch = crt_toupper((uint)ch);
    if ((dialog_title_font_obj_block.active_dialog->style_flags & 0x41000) == 0x1000) {
      node2 = dialog_title_font_obj_block.active_dialog->selected_option;
      match = 0;
      counter2 = 0;
      do {
        do {
          node2 = node2->next;
          if (node2 == 0) {
            node2 = dialog_title_font_obj_block.active_dialog->option_list;
          }
        } while ((int)dialog_title_font_obj_block.active_dialog->cur_pane != node2->group);
        first_ch = crt_toupper((int)*node2->text);
        if (first_ch == (upper_ch & 0xff)) {
          match = node2;
        }
      } while ((match == 0) && (counter2 = counter2 + 1, counter2 < 2000));
      if (match != 0) {
        target_index = dialog_option_group_index((DialogOptionList *)dialog_title_font_obj_block.active_dialog,match);
        counter2 = 0;
        while( true ) {
          top_index = dialog_option_group_index
                            ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,
                             dialog_title_font_obj_block.active_dialog->list_top_option[dialog_title_font_obj_block.active_dialog->cur_pane]);
          bottom_index = (int)dialog_title_font_obj_block.active_dialog->list_rows[dialog_title_font_obj_block.active_dialog->cur_pane] *
                  (int)dialog_title_font_obj_block.active_dialog->columns + top_index;
          if (((int)dialog_title_font_obj_block.active_dialog->columns == 1) || ((top_index <= target_index && (target_index < bottom_index)))) break;
          if (target_index < top_index) {
            top_option = (dialog_option_at
                              ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,
                               top_index - (int)dialog_title_font_obj_block.active_dialog->list_rows[dialog_title_font_obj_block.active_dialog->cur_pane]));
            dialog_title_font_obj_block.active_dialog->list_top_option[dialog_title_font_obj_block.active_dialog->cur_pane] = top_option;
            counter2++;
          }
          else {
            if (target_index < bottom_index) {
              return;
            }
            top_option = (dialog_option_at
                              ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,
                               top_index + (int)dialog_title_font_obj_block.active_dialog->list_rows[dialog_title_font_obj_block.active_dialog->cur_pane]));
            dialog_title_font_obj_block.active_dialog->list_top_option[dialog_title_font_obj_block.active_dialog->cur_pane] = top_option;
            counter2++;
          }
        }
        if (counter2 == 0) {
          dialog_select_option((DialogOptionList *)dialog_title_font_obj_block.active_dialog,match,1);
        }
        else {
          dialog_select_option((DialogOptionList *)dialog_title_font_obj_block.active_dialog,match,0);
          dialog_draw_option_list((DialogOptionList *)dialog_title_font_obj_block.active_dialog);
        }
      }
    }
    else if ((*(byte *)((iptr)dialog_title_font_obj_block.active_dialog + 0x3e) & 2) == 0) {
      if (dialog_title_font_obj_block.active_dialog->extra_button_count != 0) {
        match_index = -1;
        for (counter2 = 0; counter2 < (int)dialog_title_font_obj_block.active_dialog->extra_button_count; counter2++) {
          first_ch = crt_toupper((int)**(char **)((iptr)dialog_title_font_obj_block.active_dialog + 0x294 + counter2 * 4));
          if (first_ch == (upper_ch & 0xff)) {
            match_index = counter2;
            break;
          }
        }
        if (-1 < match_index) {
          ctrl_set_focus
                    ((ControlFocusView *)
                     (((int)dialog_title_font_obj_block.active_dialog->std_button_count + counter2) * 0x3c +
                     (int)dialog_title_font_obj_block.active_dialog->button_controls));
          dialog_on_button_click((int)dialog_title_font_obj_block.active_dialog->std_button_count + counter2 + 100);
          return;
        }
      }
      if (dialog_title_font_obj_block.active_dialog->option_count != 0) {
        match = 0;
        match_index = 0;
        for (node2 = dialog_title_font_obj_block.active_dialog->option_list; node2 != 0;
            node2 = node2->next) {
          first_ch = crt_toupper((int)*node2->text);
          if (first_ch == (upper_ch & 0xff)) {
            match = node2;
            break;
          }
          match_index++;
        }
        if (match != 0) {
          if ((*(byte *)((iptr)dialog_title_font_obj_block.active_dialog + 0x3d) & 0x10) == 0) {
            if ((*(byte *)((iptr)dialog_title_font_obj_block.active_dialog + 0x3c) & 4) == 0) {
              radiogrp_set_selected(*(RadioGroupSetSelView **)((iptr)dialog_title_font_obj_block.active_dialog + 0x268),match_index);
            }
          }
          else {
            listbox_set_cur_sel
                      ((ListBoxSetSelView *)dialog_title_font_obj_block.active_dialog->listbox[dialog_title_font_obj_block.active_dialog->cur_pane],
                       match_index);
          }
        }
      }
    }
    else {
      dialog_end_current();
    }
  }
  return;
}

/* 005a4df3 auto */
void __cdecl dialog_list_on_lbuttondown(i32 x,i32 y)

{
  int hit_index;
  DialogOption *option;
  i32 redraw;
  
  if (dialog_title_font_obj_block.active_dialog != 0) {
    dialog_pick_pane_at((DialogWindowView *)dialog_title_font_obj_block.active_dialog,x,y);
    dialog_title_font_obj_block.active_dialog->list_left_col[dialog_title_font_obj_block.active_dialog->cur_pane] = 0;
    if ((((dialog_title_font_obj_block.active_dialog->style_flags & 0x41000) == 0x1000) &&
        (dialog_title_font_obj_block.active_dialog->option_count != 0)) &&
       (hit_index = dialog_option_at_point((DialogOptionList *)dialog_title_font_obj_block.active_dialog,x,y),
       -1 < hit_index)) {
      dialog_title_font_obj_block.active_dialog->list_left_col[dialog_title_font_obj_block.active_dialog->cur_pane] = 1;
      wnd_set_capture((WndBase *)((int)dialog_title_font_obj_block.active_dialog->surf_wnd + 0x48));
      redraw = 1;
      option = dialog_option_at((DialogOptionList *)dialog_title_font_obj_block.active_dialog,hit_index);
      dialog_select_option((DialogOptionList *)dialog_title_font_obj_block.active_dialog,option,redraw);
    }
  }
  return;
}

/* 005a4edf auto */
void __cdecl dialog_list_on_mousemove(i32 x,i32 y)

{
  int rows;
  int hit;
  DialogOption *option;
  int top_index;
  int last_col;
  i32 value;
  int sel_index;
  
  if (((dialog_title_font_obj_block.active_dialog != 0) && ((dialog_title_font_obj_block.active_dialog->style_flags & 0x41000) == 0x1000)) &&
     (dialog_title_font_obj_block.active_dialog->list_left_col[dialog_title_font_obj_block.active_dialog->cur_pane] != 0)) {
    hit = dialog_option_at_point((DialogOptionList *)dialog_title_font_obj_block.active_dialog,x,y);
    if (hit < 0) {
      if ((int)dialog_title_font_obj_block.active_dialog->list_rows[dialog_title_font_obj_block.active_dialog->cur_pane] *
          (int)dialog_title_font_obj_block.active_dialog->columns < (int)dialog_title_font_obj_block.active_dialog->option_count) {
        top_index = dialog_option_group_index
                          ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,
                           dialog_title_font_obj_block.active_dialog->list_top_option[dialog_title_font_obj_block.active_dialog->cur_pane]);
        switch(hit) {
        case -4:
          if ((1 < (int)dialog_title_font_obj_block.active_dialog->columns) &&
             (hit = dialog_column_start_index
                                ((DialogTextView *)dialog_title_font_obj_block.active_dialog,(int)dialog_title_font_obj_block.active_dialog->option_count - 1)
             , top_index < hit)) {
            hit = (int)dialog_title_font_obj_block.active_dialog->list_rows[dialog_title_font_obj_block.active_dialog->cur_pane];
            rows = (int)dialog_title_font_obj_block.active_dialog->list_rows[dialog_title_font_obj_block.active_dialog->cur_pane];
            last_col = dialog_column_of_index
                              ((DialogTextView *)dialog_title_font_obj_block.active_dialog,(int)dialog_title_font_obj_block.active_dialog->option_count - 1);
            hit = int_clamp_b(top_index + hit,0,rows * last_col);
            top_index = dialog_option_group_index
                              ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,dialog_title_font_obj_block.active_dialog->selected_option);
            for (sel_index = top_index % (int)dialog_title_font_obj_block.active_dialog->list_rows[dialog_title_font_obj_block.active_dialog->cur_pane] + hit;
                (int)dialog_title_font_obj_block.active_dialog->list_rows[dialog_title_font_obj_block.active_dialog->cur_pane] + sel_index <
                (int)dialog_title_font_obj_block.active_dialog->list_rows[dialog_title_font_obj_block.active_dialog->cur_pane] *
                (int)dialog_title_font_obj_block.active_dialog->columns + hit;
                sel_index = sel_index + (int)dialog_title_font_obj_block.active_dialog->list_rows[dialog_title_font_obj_block.active_dialog->cur_pane]) {
            }
            value = int_clamp_b(sel_index,0,(int)dialog_title_font_obj_block.active_dialog->option_count - 1);
            value = (i32)dialog_option_at((DialogOptionList *)dialog_title_font_obj_block.active_dialog,value);
            dialog_title_font_obj_block.active_dialog->selected_option = (DialogOption *)value;
            value = (i32)dialog_option_at((DialogOptionList *)dialog_title_font_obj_block.active_dialog,hit);
            dialog_title_font_obj_block.active_dialog->list_top_option[dialog_title_font_obj_block.active_dialog->cur_pane] = (DialogOption *)value;
            dialog_draw_option_list((DialogOptionList *)dialog_title_font_obj_block.active_dialog);
          }
          break;
        case -3:
          if ((1 < (int)dialog_title_font_obj_block.active_dialog->columns) && (0 < top_index)) {
            top_index -= (int)dialog_title_font_obj_block.active_dialog->list_rows[dialog_title_font_obj_block.active_dialog->cur_pane];
            if (top_index < 1) {
              top_index = 0;
            }
            value = (i32)dialog_option_at((DialogOptionList *)dialog_title_font_obj_block.active_dialog,top_index);
            dialog_title_font_obj_block.active_dialog->list_top_option[dialog_title_font_obj_block.active_dialog->cur_pane] = (DialogOption *)value;
            hit = dialog_option_group_index
                              ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,dialog_title_font_obj_block.active_dialog->selected_option);
            value = (i32)dialog_option_at
                              ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,
                               top_index + hit % (int)dialog_title_font_obj_block.active_dialog->list_rows[dialog_title_font_obj_block.active_dialog->cur_pane]);
            dialog_title_font_obj_block.active_dialog->selected_option = (DialogOption *)value;
            dialog_draw_option_list((DialogOptionList *)dialog_title_font_obj_block.active_dialog);
          }
          break;
        case -2:
          if ((top_index < (int)dialog_title_font_obj_block.active_dialog->option_count - 1) && ((int)dialog_title_font_obj_block.active_dialog->columns == 1)
             ) {
            value = (i32)dialog_option_at((DialogOptionList *)dialog_title_font_obj_block.active_dialog,top_index + 1);
            dialog_title_font_obj_block.active_dialog->list_top_option[dialog_title_font_obj_block.active_dialog->cur_pane] = (DialogOption *)value;
            value = int_clamp_b((int)dialog_title_font_obj_block.active_dialog->list_rows[dialog_title_font_obj_block.active_dialog->cur_pane]
                                 * (int)dialog_title_font_obj_block.active_dialog->columns + top_index + 1 - 1,0,
                                 (int)dialog_title_font_obj_block.active_dialog->option_count - 1);
            value = (i32)dialog_option_at((DialogOptionList *)dialog_title_font_obj_block.active_dialog,value);
            dialog_title_font_obj_block.active_dialog->selected_option = (DialogOption *)value;
            dialog_draw_option_list((DialogOptionList *)dialog_title_font_obj_block.active_dialog);
          }
          break;
        case -1:
          if ((0 < top_index) && ((int)dialog_title_font_obj_block.active_dialog->columns == 1)) {
            value = (i32)dialog_option_at((DialogOptionList *)dialog_title_font_obj_block.active_dialog,top_index - 1);
            dialog_title_font_obj_block.active_dialog->selected_option = (DialogOption *)value;
            dialog_title_font_obj_block.active_dialog->list_top_option[dialog_title_font_obj_block.active_dialog->cur_pane] = dialog_title_font_obj_block.active_dialog->selected_option;
            dialog_draw_option_list((DialogOptionList *)dialog_title_font_obj_block.active_dialog);
          }
        }
      }
    }
    else {
      value = 1;
      option = dialog_option_at((DialogOptionList *)dialog_title_font_obj_block.active_dialog,hit);
      dialog_select_option((DialogOptionList *)dialog_title_font_obj_block.active_dialog,option,value);
    }
  }
  return;
}

/* 005a535e auto */
void __cdecl dialog_list_on_lbuttonup(i32 x,i32 y)

{
  if (dialog_title_font_obj_block.active_dialog != 0) {
    dialog_list_on_mousemove(x,y);
    dialog_title_font_obj_block.active_dialog->list_left_col[dialog_title_font_obj_block.active_dialog->cur_pane] = 0;
    wnd_release_capture((WndBase *)((int)dialog_title_font_obj_block.active_dialog->surf_wnd + 0x48));
  }
  return;
}

/* 005a53b8 auto */
void __cdecl dialog_list_on_dblclick(i32 x,i32 y)

{
  int hit_index;
  
  if ((((dialog_title_font_obj_block.active_dialog != 0) &&
       (dialog_pick_pane_at((DialogWindowView *)dialog_title_font_obj_block.active_dialog,x,y),
       (dialog_title_font_obj_block.active_dialog->style_flags & 0x41000) == 0x1000)) &&
      (dialog_title_font_obj_block.active_dialog->option_count != 0)) &&
     (((*(byte *)((iptr)dialog_title_font_obj_block.active_dialog + 0x3d) & 4) == 0 &&
      (hit_index = dialog_option_at_point((DialogOptionList *)dialog_title_font_obj_block.active_dialog,x,y),
      -1 < hit_index)))) {
    dialog_title_font_obj_block.active_dialog->list_left_col[dialog_title_font_obj_block.active_dialog->cur_pane] = 1;
    dialog_list_on_lbuttonup(x,y);
    dialog_title_font_obj_block.active_dialog->style_flags = dialog_title_font_obj_block.active_dialog->style_flags | 0x2000;
    dialog_end_current();
  }
  return;
}

/* 005a5494 auto */
void __cdecl dialog_list_on_hscroll(int scroll_pos)

{
  DialogOption *top_option;
  
  if (dialog_title_font_obj_block.active_dialog != 0) {
    dialog_title_font_obj_block.active_dialog->cur_pane = 0;
    top_option = (dialog_option_at
                      ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,
                       (int)dialog_title_font_obj_block.active_dialog->list_rows[dialog_title_font_obj_block.active_dialog->cur_pane] * scroll_pos
                      ));
    if ((int)dialog_title_font_obj_block.active_dialog->list_top_option[dialog_title_font_obj_block.active_dialog->cur_pane] != (iptr)top_option) {
      dialog_title_font_obj_block.active_dialog->list_top_option[dialog_title_font_obj_block.active_dialog->cur_pane] = top_option;
      dialog_draw_option_list((DialogOptionList *)dialog_title_font_obj_block.active_dialog);
    }
  }
  return;
}

/* 005a552c auto */
void __cdecl dialog_list2_on_vscroll(i32 scroll_pos)

{
  DialogOption *top_option;
  
  if (dialog_title_font_obj_block.active_dialog != 0) {
    dialog_title_font_obj_block.active_dialog->cur_pane = 1;
    top_option = dialog_option_at((DialogOptionList *)dialog_title_font_obj_block.active_dialog,scroll_pos);
    if ((int)dialog_title_font_obj_block.active_dialog->list_top_option[dialog_title_font_obj_block.active_dialog->cur_pane] != (iptr)top_option) {
      dialog_title_font_obj_block.active_dialog->list_top_option[dialog_title_font_obj_block.active_dialog->cur_pane] = top_option;
      dialog_draw_option_list((DialogOptionList *)dialog_title_font_obj_block.active_dialog);
    }
  }
  return;
}

/* 005a55b1 auto */
void __cdecl dialog_list2_on_hscroll(int scroll_pos)

{
  DialogOption *top_option;
  
  if (dialog_title_font_obj_block.active_dialog != 0) {
    dialog_title_font_obj_block.active_dialog->cur_pane = 1;
    top_option = (dialog_option_at
                      ((DialogOptionList *)dialog_title_font_obj_block.active_dialog,
                       (int)dialog_title_font_obj_block.active_dialog->list_rows[dialog_title_font_obj_block.active_dialog->cur_pane] * scroll_pos
                      ));
    if ((int)dialog_title_font_obj_block.active_dialog->list_top_option[dialog_title_font_obj_block.active_dialog->cur_pane] != (iptr)top_option) {
      dialog_title_font_obj_block.active_dialog->list_top_option[dialog_title_font_obj_block.active_dialog->cur_pane] = top_option;
      dialog_draw_option_list((DialogOptionList *)dialog_title_font_obj_block.active_dialog);
    }
  }
  return;
}

/* 005a5649 auto */
void __thiscall dialog_fill_rect_bg(DialogTextView *self,RECT *rect,int area)

{
  i32 height;
  i32 width;
  i32 src_x;
  i32 src_y;
  
  if (self->bg_surface == 0) {
    if ((dlg_frame_tile_surface == 0) || (area != 1)) {
      if ((dlg_client_tile_surface == 0) || (area != 2)) {
        gfx_fill_rect(self->surf_wnd,rect,self->bg_color);
      }
      else {
        src_y = 0;
        src_x = 0;
        height = rect_height(rect);
        width = rect_width(rect);
        gfx_tile_fill(self->surf_wnd,dlg_client_tile_surface,rect->left,
                           rect->top,width,height,src_x,src_y);
      }
    }
    else {
      src_y = 0;
      src_x = 0;
      height = rect_height(rect);
      width = rect_width(rect);
      gfx_tile_fill(self->surf_wnd,dlg_frame_tile_surface,rect->left,
                         rect->top,width,height,src_x,src_y);
    }
  }
  else {
    height = rect_height(rect);
    width = rect_width(rect);
    gfx_copy_rect_same_pos(self->bg_surface,self->surf_wnd,rect->left,
                       rect->top,width,height);
  }
  return;
}

/* 005a577e auto */
void __thiscall dialog_render(Dialog *self)

{
  int tmp;
  i32 size;
  int row_height;
  int line_spacing;
  u32 zoom;
  i8 sprite_rect[16];
  u32 pane;
  u32 saved_pane;
  int label_x;
  int sprite_h;
  DialogEditField *edit_field;
  u32 sprite_y2;
  u32 sprite_x2;
  int created;
  int title_y;
  int label_y;
  int title_x;
  DialogSprite *sprite;
  int i;
  int sprite_w;
  RECT rect;
  
  created = 0;
  if ((self->style_flags & 0x20) == 0) {
    tmp = dialog_compute_layout((DialogOptionList *)self);
    if (tmp != 0) {
      return;
    }
    created = dialog_create_window((DialogWindowView *)self);
    dialog_create_controls(self);
  }
  if ((self->style_flags & 0x4000) == 0) {
    rect_set_xywh((iptr)((i8 *)&rect.left),self->origin_x,self->origin_y,self->wnd_width,self->wnd_height);
    if (self->border_width != 0) {
      for (i = 0; i < (int)self->bevel_width; i++) {
        gfx_draw_bevel_rect(self->surf_wnd,(RECT *)(iptr)((i8 *)&rect.left),self->bevel_light_color,self->bevel_dark_color);
        rect_deflate((iptr)((i8 *)&rect.left),1,1);
      }
      dialog_fill_rect_bg((DialogTextView *)self,(RECT *)(iptr)((i8 *)&rect.left),1);
      rect_deflate((iptr)((i8 *)&rect.left),self->border_width + self->bevel_width * -2,0);
      rect.top = rect.top + self->title_height + self->bevel_width * -2;
      rect.bottom -= ((self->chrome_height - self->title_height) + self->bevel_width * -2);
      for (i = 0; i < (int)self->bevel_width; i++) {
        gfx_draw_bevel_rect(self->surf_wnd,(RECT *)(iptr)((i8 *)&rect.left),self->bevel_dark_color,self->bevel_light_color);
        rect_deflate((iptr)((i8 *)&rect.left),1,1);
      }
    }
    dialog_fill_rect_bg((DialogTextView *)self,(RECT *)(iptr)((i8 *)&rect.left),2);
  }
  if ((self->title_text != 0) && ((self->style_flags & 0x10000) == 0)) {
    zoom = self->wnd_width;
    tmp = font_text_width((GameFont *)self->title_font,(const char *)self->title_text);
    title_x = ((int)zoom >> 1) - (tmp + 4 >> 1);
    title_y = self->bevel_width + self->pad_y;
    gfx_set_text_color_index(self->title_shadow_color);
    surface_draw_text
              ((DibSurface *)self->surf_wnd,self->title_font,(const char *)self->title_text,title_x + 2,
               title_y + 1,5);
    gfx_set_text_color_index(self->title_color);
    surface_draw_text
              ((DibSurface *)self->surf_wnd,self->title_font,(const char *)self->title_text,title_x + 1,title_y,5)
    ;
    surface_draw_text
              ((DibSurface *)self->surf_wnd,self->title_font,(const char *)self->title_text,title_x,title_y,5);
  }
  dialog_draw_wrapped_text((DialogOptionList *)self,1);
  if (self->sprite_count != 0) {
    gfx_set_zoom_scale(self->sprite_zoom);
    sprite_x2 = self->sprite_x;
    sprite_y2 = self->sprite_y;
    for (sprite = self->sprite_list; sprite != (DialogSprite *)0x0;
        sprite = sprite->next) {
      zoom = self->sprite_zoom;
      size = sprite_width(sprite->sprite);
      sprite_w = gfx_zoom_scale(size,zoom);
      zoom = self->sprite_zoom;
      size = sprite_height(sprite->sprite);
      sprite_h = gfx_zoom_scale(size,zoom);
      if (self->on_draw_sprite == 0) {
        sprite_draw
                  (sprite->sprite,(iptr)sprite_rect,self->surf_wnd,sprite_x2,sprite_y2);
      }
      else {
        call_untyped((code *)self->on_draw_sprite, (i32)sprite->sprite,self->surf_wnd,sprite->id,sprite->field_04,sprite_x2,sprite_y2);
      }
      if (((self->style_flags & 0x20000) != 0) && ((i32 *)self->selected_sprite == ((i32 *)sprite))) {
        rect_set((iptr)((i8 *)&rect.left),sprite_x2 - 1,sprite_y2 - 1,sprite_w + sprite_x2,
                           sprite_h + sprite_y2);
        gfx_draw_rect_frame(self->surf_wnd,(RECT *)(iptr)((i8 *)&rect.left),self->frame_color);
      }
      tmp = sprite_h;
      if (sprite->label != 0) {
        label_x = self->sprite_gap + sprite_w + sprite_x2;
        row_height = font_line_spacing((GameFont *)self->body_font);
        label_y = (tmp - row_height >> 1) + sprite_y2;
        dialog_draw_text_default_font((DialogTextView *)self,(const char *)sprite->label,label_x,label_y,0);
      }
      sprite_y2 = sprite_y2 + sprite_h + self->section_gap;
    }
    gfx_reset_zoom_scale();
  }
  if (self->edit_count != 0) {
    edit_field = self->edit_field_list;
    i = 0;
    for (; edit_field != 0; edit_field = edit_field->next) {
      gfx_set_text_color_index(self->text_color);
      size = 5;
      tmp = dialog_edit_row_height((DialogCore *)self);
      tmp = tmp * i;
      row_height = dialog_edit_row_height((DialogCore *)self);
      zoom = self->edit_y;
      line_spacing = font_line_spacing((GameFont *)self->body_font);
      surface_draw_text_cur_font
                ((SurfaceTextCurFontView *)self->surf_wnd,(const char *)edit_field->label,self->edit_x,
                 (tmp + (row_height >> 1) + zoom) - (line_spacing >> 1),size);
      i++;
    }
  }
  if ((self->style_flags & 0x41000) == 0x1000) {
    dialog_draw_option_list((DialogOptionList *)self);
  }
  if (created == 0) {
    wnd_blit_surface((DibSurface *)self->surf_wnd);
    if (self->option_count != 0) {
      if ((self->style_flags & 0x1000) == 0) {
        if ((self->style_flags & 4) == 0) {
          radiogrp_show_all((RadioGroupShowView *)self->radio_group);
        }
        else {
          for (i = 0; i < (int)self->option_count; i++) {
            ctrl_show_and_redraw((Control *)(self->checkboxes + i * 0x3c));
          }
        }
      }
      else if ((self->style_flags & 0x40000) == 0) {
        saved_pane = self->cur_pane;
        for (pane = 0; (int)pane < 2; pane++) {
          if ((pane != 1) || ((self->style_flags & 0x400000) != 0)) {
            self->cur_pane = pane;
            if (self->list_vscroll[self->cur_pane] != 0) {
              ctrl_show_and_redraw
                        ((Control *)self->list_vscroll[self->cur_pane]);
            }
            if (self->list_hscroll[self->cur_pane] != 0) {
              ctrl_show_and_redraw
                        ((Control *)self->list_hscroll[self->cur_pane]);
            }
          }
        }
        self->cur_pane = saved_pane;
      }
    }
    if (self->edit_count != 0) {
      for (i = 0; i < (int)self->edit_count; i++) {
        ctrl_show_and_redraw((Control *)(i * 0x48 + self->edit_controls));
      }
    }
    if (self->std_button_count + self->extra_button_count != 0) {
      for (i = 0; i < (int)(self->std_button_count + self->extra_button_count); i++)
      {
        ctrl_show_and_redraw((Control *)(self->button_controls + i * 0x3c));
      }
    }
    if ((1 < (int)self->sprite_count) && (self->option_count == 0)) {
      for (i = 0; i < (int)self->sprite_count; i++) {
        ctrl_show_and_redraw((Control *)(self->sprite_hotspots + i * 0x40));
      }
    }
  }
  else {
    window_show((WindowObjectView *)self->surf_wnd);
  }
  self->style_flags = self->style_flags | 0x20;
  return;
}

/* 005a5f34 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

u32 __thiscall dialog_run_modal(Dialog *self,iptr out_text,iptr timeout_secs)

{
  NativeWindow *main_hwnd;
  BOOL is_iconic;
  int result;
  char item_text[132];
  char sel_text[132];
  DialogOption *option;
  int i;
  
  if (dialog_stack_depth != 0x10) {
    if (timeout_secs == 0) {
      dialog_title_font_obj_block.dialog_timeout_start_i32 = timer_ticks();
    }
    else {
      dialog_title_font_obj_block.dialog_timeout_start_i32 = timer_ticks();
      dialog_title_font_obj_block.dialog_timeout_start_i32 = timeout_secs * 0x3c - 0x4b0 + dialog_title_font_obj_block.dialog_timeout_start_i32;
    }
    if (game_session_active != 0) {
      main_hwnd = wnd_get_window((WndBase *)((i8 *)&main_frame_wnd_block.main_frame_wnd));
      is_iconic = IsIconic(main_hwnd->hwnd);
      if (is_iconic != 0) {
        wnd_show_restored((WndBase *)((i8 *)&main_frame_wnd_block.main_frame_wnd));
      }
    }
    self->style_flags = self->style_flags & 0xffffdfff;
    if ((self->style_flags & 0x4000) != 0) {
      self->style_flags = self->style_flags | 0x10000;
    }
    dialog_render(self);
    if (((self->style_flags & 0x20) != 0) && ((self->style_flags & 8) == 0)) {
      if (self->on_modal_poll == 0) {
        wnd_run_modal_loop((ModalMenuWindow *)(self->surf_wnd + 0x48));
        while ((self->style_flags & 0x400) == 0) {
          win_pump_one_message();
        }
      }
      else {
        while ((self->style_flags & 0x400) == 0) {
          result = call_untyped((code *)self->on_modal_poll, self);
          if (result != 0) {
            dialog_end_current();
          }
        }
      }
      if ((out_text != 0) && (self->edit_controls != 0)) {
        ctrl_get_text((ControlTextView *)self->edit_controls,(char *)out_text);
      }
      if (1 < (int)self->edit_count) {
        for (i = 0; i < (int)self->edit_count; i++) {
          ctrl_get_text
                    ((ControlTextView *)(self->edit_controls + i * 0x48),
                     (((i8 *)&minimap_window_block.text_string_args) + i * 0x104));
        }
      }
      if ((self->style_flags & 0x1000) == 0) {
        if ((self->style_flags & 4) != 0) {
          option = self->option_list;
          i = 0;
          for (; option != (DialogOption *)0x0; option = option->next) {
            option->flags = option->flags & 0xfffffffb;
            result = checkbox_is_checked
                              ((Control *)(self->checkboxes + i * 0x3c));
            if (result != 0) {
              option->flags = option->flags | 4;
            }
            i++;
          }
        }
      }
      else if (self->result_id == 0) {
        if ((self->style_flags & 0x40000) == 0) {
          self->result_id = (u32)self->selected_option->id;
        }
        else {
          listbox_get_sel_text
                    ((ListBoxSelTextView *)self->listbox[self->cur_pane],(char *)sel_text);
          self->result_id = (u32)self->option_list->id;
          option = self->option_list;
          i = 0;
          for (; option != (DialogOption *)0x0; option = option->next) {
            listbox_get_text
                      ((ListBoxTextView *)self->listbox[self->cur_pane],i,
                       (char *)item_text);
            result = _strcmp(sel_text,item_text);
            if (result == 0) {
              self->result_id = (uint)option->id;
            }
            i++;
          }
        }
      }
      if ((self->style_flags & 0x800) == 0) {
        dialog_close(self);
        input_flush_events();
        win_flush_pending_msgs();
        wnd_flush_paint();
        win_flush_pending_msgs();
      }
    }
  }
  return self->result_id;
}

/* 005a632a auto */
i32 __thiscall
dialog_load_text_section
          (Dialog *self,const char *file_name,const char *section,int default_value,iptr edit_default,iptr init_arg1,
          iptr init_arg2,iptr init_arg3,uint flags)

{
  int cmp;
  size_t len;
  u32 coord;
  i8 expanded[256];
  int mode;
  i32 result;
  uint has_edit;
  char *line;
  i8 edit_text[80];
  int list_rows2;
  char *key2;
  DialogOption *option;
  int option_index;
  int number;
  i8 *edit_buf;
  
  result = 1;
  mode = 1;
  option_index = 0;
  crt_strcpy((char *)((void *)(((i8 *)&dialog_text_font_obj_block.dialog_section_name))),(const char *)((void *)section));
  cmp = text_open_section(file_name,section);
  if (cmp == 0) {
    if ((flags & 0x8000) == 0) {
      dialog_init(self,init_arg1,init_arg2,(RECT *)init_arg3,flags);
    }
    else {
      self->style_flags = self->style_flags | flags;
    }
    has_edit = (uint)(edit_default != 0);
    if (has_edit != 0) {
      crt_strcpy((char *)((void *)edit_text),(const char *)((void *)edit_default));
    }
    do {
      line = text_read_line(1);
      if (line == (char *)0x0) {
        mode = 3;
      }
      else {
        len = _strlen(line);
        if (len == 0) {
          if ((flags & 0x4000000) == 0) {
            mode++;
          }
          else {
            dialog_add_line
                      ((DialogAddLineView *)self,(const char *)&str_empty_185,0xffffffff,0xffffffff,0xffffffff,0);
          }
        }
        else if (*line == '@') {
          key2 = line + 1;
          cmp = __strcmpi(key2,str_options);
          if ((cmp == 0) || (cmp = _strcmp(key2,str_prompt), cmp == 0)) {
            mode = 2;
          }
          else {
            cmp = __strcmpi(key2,((i8 *)&dlg_key_text_str));
            if (cmp == 0) {
              mode = 1;
            }
            else {
              cmp = __strnicmp(key2,str_title,5);
              if (cmp == 0) {
                for (; (*key2 != '\0' && (*key2 != '=')); key2++) {
                }
                if (*key2 != '\0') {
                  key2++;
                }
                text_expand_vars((iptr)key2,(iptr)expanded);
                dialog_set_title((DialogWindowView *)self,(const char *)expanded);
              }
              else {
                cmp = __strnicmp(key2,str_button,6);
                if (cmp == 0) {
                  for (; (*key2 != '\0' && (*key2 != '=')); key2++) {
                  }
                  if (*key2 != '\0') {
                    key2++;
                  }
                  text_expand_vars((iptr)key2,(iptr)expanded);
                  dialog_add_button((DialogButtonsView *)self,(const char *)expanded);
                }
                else {
                  cmp = __strnicmp(key2,str_columns,7);
                  if (cmp == 0) {
                    while ((*key2 != '\0' && (cmp = _isdigit((int)*key2), cmp == 0))) {
                      key2++;
                    }
                    number = _atoi(key2);
                    dialog_set_columns((DialogButtonsView *)self,number);
                  }
                  else {
                    cmp = __strnicmp(key2,str_height,6);
                    if (cmp == 0) {
                      while ((*key2 != '\0' && (cmp = _isdigit((int)*key2), cmp == 0)))
                      {
                        key2++;
                      }
                      number = _atoi(key2);
                      dialog_set_height((DialogCore *)self,number);
                    }
                    else {
                      cmp = __strcmpi(key2,str_smallfont);
                      if (cmp != 0) {
                        cmp = __strnicmp(key2,((i8 *)&dlg_key_y_prefix),1);
                        if ((cmp == 0) && (cmp = _isalpha((int)key2[1]), cmp == 0)) {
                          while (((*key2 != '\0' &&
                                  (cmp = _isdigit((int)*key2), cmp == 0)) &&
                                 (*key2 != '-'))) {
                            key2++;
                          }
                          coord = _atoi(key2);
                          self->req_y = coord;
                        }
                        else {
                          cmp = __strnicmp(key2,((i8 *)&dlg_key_x_prefix),1);
                          if ((cmp == 0) && (cmp = _isalpha((int)key2[1]), cmp == 0)) {
                            while (((*key2 != '\0' &&
                                    (cmp = _isdigit((int)*key2), cmp == 0)) &&
                                   (*key2 != '-'))) {
                              key2++;
                            }
                            coord = _atoi(key2);
                            self->req_x = coord;
                          }
                          else {
                            cmp = __strnicmp(key2,str_width,5);
                            if (cmp == 0) {
                              while ((*key2 != '\0' &&
                                     (cmp = _isdigit((int)*key2), cmp == 0))) {
                                key2++;
                              }
                              number = _atoi(key2);
                              dialog_set_width((DialogWindowView *)self,number);
                            }
                            else {
                              cmp = __strnicmp(key2,str_length,6);
                              if (cmp == 0) {
                                while ((*key2 != '\0' &&
                                       (cmp = _isdigit((int)*key2), cmp == 0))) {
                                  key2++;
                                }
                                if (default_value == 0) {
                                  default_value = _atoi(key2);
                                }
                              }
                              else {
                                cmp = __strnicmp(key2,str_checkbox,7);
                                if (cmp == 0) {
                                  self->style_flags = self->style_flags | 5;
                                }
                                else {
                                  cmp = __strnicmp(key2,str_listbox,7);
                                  if (cmp == 0) {
                                    while ((*key2 != '\0' &&
                                           (cmp = _isdigit((int)*key2), cmp == 0))) {
                                      key2++;
                                    }
                                    list_rows2 = _atoi(key2);
                                    if (list_rows2 == 0) {
                                      list_rows2 = 0x10;
                                    }
                                    dialog_set_listbox
                                              ((DialogTextView *)self,list_rows2,self->content_width,0);
                                  }
                                  else {
                                    cmp = __strnicmp(key2,str_system,6);
                                    if (cmp == 0) {
                                      self->style_flags = self->style_flags | 0x40000;
                                    }
                                    else {
                                      cmp = __strnicmp(key2,str_default_3,7);
                                      if (cmp == 0) {
                                        if (has_edit == 0) {
                                          while ((*key2 != '\0' &&
                                                 (cmp = _isdigit((int)*key2), cmp == 0))) {
                                            key2++;
                                          }
                                          if (default_value == 0) {
                                            default_value = _atoi(key2);
                                          }
                                        }
                                        else {
                                          for (; (*key2 != '\0' && (*key2 != '='));
                                              key2 = key2 + 1) {
                                          }
                                          if (*key2 != '\0') {
                                            key2++;
                                          }
                                          len = _strlen((char *)edit_default);
                                          if (len == 0) {
                                            crt_strcpy(edit_text,key2);
                                          }
                                        }
                                      }
                                      else if (*key2 != '@') {
                                        mode = 3;
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
        else if (mode == 1) {
          text_expand_vars((iptr)line,(iptr)expanded);
          dialog_add_line
                    ((DialogAddLineView *)self,(const char *)expanded,0xffffffff,0xffffffff,0xffffffff,0);
        }
        else if (mode == 2) {
          text_expand_vars((iptr)line,(iptr)expanded);
          if (has_edit == 0) {
            if ((self->style_flags & 4) == 0) {
              option = (DialogOption *)((uptr)dialog_add_option
                                   ((DialogOptionList *)self,(const char *)expanded,option_index,0));
            }
            else {
              option = (DialogOption *)((uptr)dialog_add_checkbox_option
                                   ((DialogOptionList *)self,(const char *)expanded,option_index,0));
            }
            if (default_value == option_index) {
              self->selected_option = option;
            }
            option_index++;
          }
          else {
            if (default_value == 0) {
              default_value = 5;
            }
            edit_buf = edit_text;
            if (self->edit_count != 0) {
              edit_buf = ((i8 *)&minimap_window_block.text_string_args) + self->edit_count * 0x104;
            }
            dialog_add_edit_field
                      ((DialogOptionList *)self,(const char *)expanded,(iptr)edit_buf,default_value);
          }
        }
      }
    } while (mode < 3);
    result = 0;
  }
  else if ((flags & 0x8000) == 0) {
    dialog_init(self,init_arg1,init_arg2,(RECT *)init_arg3,flags);
  }
  return result;
}

/* 005a6c23 auto */
void __cdecl dlg_push_parent_window(iptr parent)

{
  dlg_saved_parent_window = dlg_parent_window;
  dlg_parent_window = parent;
  return;
}

/* 005a6c45 auto */
void __cdecl dlg_pop_parent_window(void)

{
  dlg_parent_window = dlg_saved_parent_window;
  return;
}

/* 005a9520 auto */
/* Library Function - Multiple Matches With Different Base Names
    public: void * __thiscall CDaoIndexFieldInfo::`vector deleting destructor'(unsigned int)
    public: void * __thiscall CDaoRelationFieldInfo::`vector deleting destructor'(unsigned int)
    public: void * __thiscall CODBCFieldInfo::`vector deleting destructor'(unsigned int)
    public: void * __thiscall CString::`vector deleting destructor'(unsigned int)
   
   Library: Visual Studio 1998 Debug */

Hotspot * __thiscall hotspot_vector_dtor(Hotspot *self,uint flags)

{
  if ((flags & 2) == 0) {
    hotspot_dtor(self);
    if ((flags & 1) != 0) {
      operator_delete(self);
    }
  }
  else {
    crt_vector_dtor_iterator(self,0x40,VECTOR_COUNT(self),(code *)hotspot_dtor);
    operator_delete(&VECTOR_COUNT(self));
  }
  return self;
}

/* 005a95b0 auto */
SurfaceWindow * __thiscall surfwnd_scalar_dtor(SurfaceWindow *self,uint flags)

{
  surfwnd_dtor(self);
  if ((flags & 1) != 0) {
    operator_delete(self);
  }
  return self;
}

/* 005a9600 auto */
void __thiscall wnd_get_screen_rect(WndBase *self,iptr rect)

{
  wnd_obj_get_screen_rect(self->native_wnd,(LPRECT)rect);
  return;
}

/* 005a96f0 auto */
uint __thiscall dialog_uses_alt_text_color(DialogAltColorView *self)

{
  return (uint)((self->style_flags & 0x100) != 0);
}

/* 005a9730 auto */
void __thiscall
dialog_draw_text_default_font
          (DialogTextView *self,const char *text,i32 x,i32 y,
          i32 flags)

{
  dialog_draw_text_shadowed(self,self->body_font,(char *)text,x,y,flags);
  return;
}

/* 005bb4ae auto */
void __thiscall
wnd_create_with_surface
          (DibSurface *self,const char *title,i32 style,i32 x,i32 y
          ,i32 width,i32 height,iptr palette,iptr parent)

{
  NativeWindow *hwnd;
  
  wnd_create_framed_child
            ((WndBase *)(self + 1),title,style,x,y,width,height,palette,
             parent);
  surface_create(self,width,height);
  surface_set_palette(self,palette);
  hwnd = wnd_get_window((WndBase *)(self + 1));
  wnd_install_paint_proc((iptr)self,hwnd);
  return;
}

/* 005bb574 auto */
void __thiscall wnd_repaint(SurfaceWindow *self)

{
  if (self == (SurfaceWindow *)0x0) {
    (*(u8 * *)&wnd_active_child) = (u8 *)0x0;
  }
  else {
    (*(u8 * *)&wnd_active_child) = self->window_2;
  }
  wnd_call_paint_cb(self);
  wnd_blit_surface((DibSurface *)self);
  return;
}

/* 005bb5be auto */
bool __thiscall surfwnd_resize_dib(DibSurface *self,iptr rect)

{
  int result;
  i32 height;
  i32 width;
  
  result = surface_alloc_dib_by_bpp(self,rect);
  if (result == 1) {
    height = rect_height((RECT *)rect);
    width = rect_width((RECT *)rect);
    wnd_set_client_size((WndClientSizeView *)(self + 1),width,height);
  }
  return result == 1;
}

/* 005bb621 auto */
void __thiscall surfwnd_on_resize(SurfaceWindow *self,int width,int height)

{
  int cur_size;
  i32 palette;
  tagRECT rect;
  
  cur_size = surface_get_width((DibSurface *)self);
  if ((cur_size == width) &&
     (cur_size = surface_get_height((DibSurface *)self), cur_size == height)) {
    return;
  }
  SetRect(&rect,0,0,width,height);
  call_untyped(((code **)self->vtable)[0], self,&rect);
  palette = wnd_get_palette_obj((WndPaletteObjView *)self->window_2);
  surface_apply_palette((DibSurface *)self,(PaletteVersionView *)palette);
  if (self == (SurfaceWindow *)0x0) {
    (*(u8 * *)&wnd_active_child) = (u8 *)0x0;
  }
  else {
    (*(u8 * *)&wnd_active_child) = self->window_2;
  }
  wnd_call_paint_cb(self);
  wnd_blit_surface((DibSurface *)self);
  return;
}

/* 005bb6c7 auto */
void __thiscall wnd_resize_clamped(WindowObjectView *self,int width,int height)

{
  int min_height2;
  int min_width2;
  int max_height2;
  int max_width2;
  
  wnd_get_min_size((WndMinSizeView *)(self + 0x12),(iptr)&min_width2,(iptr)&min_height2);
  wnd_get_max_size((WndMaxSizeView *)(self + 0x12),(iptr)&max_width2,(iptr)&max_height2);
  if (width < min_width2) {
    width = min_width2;
  }
  if (max_width2 < width) {
    width = max_width2;
  }
  if (height < min_height2) {
    height = min_height2;
  }
  if (max_height2 < height) {
    height = max_height2;
  }
  wnd_set_client_size((WndClientSizeView *)(self + 0x12),width,height);
  return;
}

/* 005bb8c0 auto */
u32 __thiscall wnd_get_palette_obj(WndPaletteObjView *self)

{
  return self->palette_obj;
}

/* 005bb8e0 auto */
void __thiscall wnd_set_client_size(WndClientSizeView *self,i32 width,i32 height)

{
  wnd_obj_set_client_size(self->native_wnd,width,height);
  return;
}

/* 005bb910 auto */
void __thiscall wnd_get_min_size(WndMinSizeView *self,iptr out_width,iptr out_height)

{
  *(u32 *)out_width = self->min_width;
  *(u32 *)out_height = self->min_height;
  return;
}

/* 005bb950 auto */
void __thiscall wnd_get_max_size(WndMaxSizeView *self,iptr out_width,iptr out_height)

{
  *(u32 *)out_width = self->max_width;
  *(u32 *)out_height = self->max_height;
  return;
}

/* 005bb990 auto */
void __thiscall wnd_call_paint_cb(SurfaceWindow *self)

{
  if (self->on_paint != 0) {
    call_untyped((code *)self->on_paint);
  }
  return;
}

/* 005bbc10 auto */
NativeWindow * __cdecl
wnd_obj_create(LPCSTR title,uint flags,int x,int y,int width,int height,
            NativeWindow *parent)

{
  i32 handle;
  NativeWindow *wnd;
  int metric;
  HWND new_hwnd;
  HDC hdc;
  HCURSOR cursor;
  int pos_x2;
  int pos_y2;
  int outer_width;
  int outer_height;
  HWND parent_hwnd;
  DWORD ex_style;
  uint style2;
  int caption_height2;
  int frame_height;
  int frame_width;
  
  ex_style = 0;
  handle = mem_handle_alloc(0x4c);
  wnd = (NativeWindow *)mem_handle_lock(handle);
  wnd->mem_handle = handle;
  frame_width = 0;
  frame_height = 0;
  caption_height2 = GetSystemMetrics(4);
  style2 = 0x2000000;
  if ((flags & 4) == 0) {
    if (((flags & 2) == 0) || ((flags & 0x40) != 0)) {
      if (((flags & 2) == 0) || ((flags & 0x40) == 0)) {
        if ((flags & 1) != 0) {
          style2 = 0x2800000;
          frame_width = GetSystemMetrics(7);
          frame_width = frame_width * 2;
          frame_height = GetSystemMetrics(8);
          frame_height = frame_height * 2;
          caption_height2++;
        }
      }
      else {
        style2 = 0x2800000;
        frame_width = GetSystemMetrics(7);
        frame_width = frame_width * 2;
        frame_height = GetSystemMetrics(8);
        frame_height = frame_height * 2;
      }
    }
    else {
      style2 = 0x2400000;
      frame_width = GetSystemMetrics(7);
      frame_width = frame_width * 2;
      frame_height = GetSystemMetrics(8);
      frame_height = frame_height * 2;
    }
  }
  else {
    style2 = 0x2040000;
    frame_width = GetSystemMetrics(0x20);
    frame_width = frame_width * 2;
    frame_height = GetSystemMetrics(0x21);
    frame_height = frame_height * 2;
  }
  if ((flags & 8) != 0) {
    style2 = style2 | 0x20000;
    flags = flags | 0x40;
  }
  if ((flags & 0x10) != 0) {
    style2 = style2 | 0x10000;
    flags = flags | 0x40;
  }
  if ((flags & 0x20) != 0) {
    style2 = style2 | 0x80000;
    flags = flags | 0x40;
  }
  if ((flags & 0x40) == 0) {
    caption_height2 = 0;
  }
  else {
    style2 = style2 | 0xc00000;
  }
  if ((flags & 0x80) != 0) {
    style2 = style2 | 0x200000;
    metric = GetSystemMetrics(2);
    frame_width = frame_width + metric - 1;
  }
  if ((flags & 0x100) != 0) {
    style2 = style2 | 0x100000;
    metric = GetSystemMetrics(3);
    frame_height = frame_height + metric - 1;
  }
  if (((flags & 0x200) != 0) && (parent != 0)) {
    style2 = style2 | 0x44000000;
    ex_style = 4;
  }
  if ((flags & 0x800) != 0) {
    style2 = style2 & 0xbfffffff | 0x80000000;
  }
  if ((flags & 0x400) == 0) {
    wnd->flag_400 = 0;
  }
  else {
    wnd->flag_400 = 1;
  }
  if ((flags & 0x1000) == 0) {
    wnd->flag_1000 = 0;
  }
  else {
    wnd->flag_1000 = 1;
  }
  if (parent == 0) {
    parent_hwnd = (HWND)0x0;
  }
  else {
    parent_hwnd = parent->hwnd;
  }
  if (height == -1) {
    outer_height = -0x80000000;
  }
  else {
    outer_height = frame_height + caption_height2 + height - 1;
  }
  if (width == -1) {
    outer_width = -0x80000000;
  }
  else {
    outer_width = frame_width + width;
  }
  if (y == -1) {
    pos_y2 = -0x80000000;
  }
  else {
    pos_y2 = y;
  }
  if (x == -1) {
    pos_x2 = -0x80000000;
  }
  else {
    pos_x2 = x;
  }
  new_hwnd = CreateWindowExA(ex_style,str_mswindowclass_2,title,style2,pos_x2,pos_y2,
                           outer_width,outer_height,parent_hwnd,(HMENU)0x0,err_report_ctx_block.app_hinstance,(LPVOID)0x0);
  wnd->hwnd = new_hwnd;
  wnd_list_add_hwnd(wnd->hwnd);
  hdc = GetDC(wnd->hwnd);
  wnd->hdc = hdc;
  cursor = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
  wnd->cursor = cursor;
  wnd->palette = 0;
  wnd->icon = 0;
  wnd->destroyed = 0;
  wnd->bg_brush = 0;
  wnd->active_child = 0;
  wnd->bg_tile = 0;
  wnd->field_28 = 0;
  wnd->bg_surface = 0;
  wnd->flags = flags;
  wnd->caption_height = 0;
  wnd->resize_border = 0;
  wnd->topmost_child = 0;
  wnd->field_40 = 8;
  return wnd;
}

/* 005bbfee auto */
void __cdecl wnd_obj_enable(NativeWindow *wnd,BOOL enable)

{
  if (wnd != 0) {
    EnableWindow(wnd->hwnd,enable);
  }
  return;
}

/* 005bc0ab auto */
i32 __cdecl wnd_obj_destroy(NativeWindow *wnd)

{
  i32 handle;
  
  if (wnd != (NativeWindow *)0x0) {
    wnd_stack_remove(wnd->hwnd);
    if (wnd->destroyed == 0) {
      if (wnd->hwnd != 0) {
        SetWindowLongA(wnd->hwnd,4,0);
        ShowWindow(wnd->hwnd,0);
        SetMenu(wnd->hwnd,(HMENU)0x0);
        DestroyWindow(wnd->hwnd);
      }
      wnd->hwnd = 0;
    }
    if (wnd->bg_brush != 0) {
      DeleteObject(wnd->bg_brush);
    }
    handle = wnd->mem_handle;
    mem_handle_unlock(handle);
    mem_handle_free(handle);
  }
  return 0;
}

/* 005bc173 auto */
void __cdecl wnd_stack_check_leaks_nop(void)

{
  int i;
  
  if (ms_window_stack_count != 0) {
    for (i = 0; i < ms_window_stack_count; i++) {
    }
  }
  return;
}

/* 005bc1b5 auto */
void __cdecl wnd_list_add_hwnd(i32 hwnd)

{
  *(i32 *)(((i8 *)&ms_window_stack_block.ms_window_stack) + ms_window_stack_count * 4) = hwnd;
  ms_window_stack_count++;
  return;
}

/* 005bc1db auto */
void __cdecl wnd_stack_remove(int hwnd)

{
  int i;
  
  for (i = 0; (i < ms_window_stack_count && (*(int *)(((i8 *)&ms_window_stack_block.ms_window_stack) + i * 4) != hwnd));
      i = i + 1) {
  }
  if (i < ms_window_stack_count - 1) {
    for (; i < ms_window_stack_count - 1; i++) {
      *(i32 *)(((i8 *)&ms_window_stack_block.ms_window_stack) + i * 4) = *(i32 *)(((i8 *)&ms_window_stack_block.ms_window_stack_elem1) + i * 4);
    }
  }
  ms_window_stack_count--;
  if (ms_window_stack_count < 0) {
    dbg_log((const char *)&str_error_ms_window_stack_inaccurate);
  }
  return;
}

/* 005bc280 auto */
void __cdecl wnd_obj_set_bg_color(NativeWindow *wnd,uint color_index)

{
  HBRUSH brush;
  GamePalette *self;
  i8 green[4];
  WndPaletteView *wnd_view;
  i8 red[4];
  i8 blue[4];
  
  if (wnd->bg_brush != 0) {
    DeleteObject(wnd->bg_brush);
  }
  if (gfx_palettized_display == 0) {
    wnd_view = (WndPaletteView *)GetWindowLongA(wnd->hwnd,0);
    self = (GamePalette *)wnd_get_palette(wnd_view);
    palette_get_entry
              (self,color_index & 0xff,(iptr)red,(iptr)green,(iptr)blue);
    brush = CreateSolidBrush(CONCAT12(blue[0],CONCAT11(green[0],red[0])));
    wnd->bg_brush = brush;
  }
  else {
    if (wnd->palette != 0) {
      RealizePalette(wnd->hdc);
    }
    brush = CreateSolidBrush(color_index & 0xff | 0x1000000);
    wnd->bg_brush = brush;
  }
  InvalidateRect(wnd->hwnd,(RECT *)0x0,0);
  return;
}

/* 005bc3bf auto */
void __cdecl wnd_obj_set_bg_tile(NativeWindow *wnd,DibSurface *tile)

{
  wnd->bg_tile = tile;
  return;
}

/* 005bc3f1 auto */
void __cdecl wnd_obj_set_bg_surface(NativeWindow *wnd,DibSurface *surface)

{
  wnd->bg_surface = surface;
  return;
}

/* 005bc40a auto */
void __cdecl wnd_obj_show_raise(NativeWindow *wnd)

{
  if (wnd != 0) {
    ShowWindow(wnd->hwnd,5);
    if ((wnd->flags_bytes[1] & 2) != 0) {
      BringWindowToTop(wnd->hwnd);
    }
  }
  return;
}

/* 005bc44d auto */
void __cdecl wnd_obj_hide(NativeWindow *wnd)

{
  if (wnd != 0) {
    ShowWindow(wnd->hwnd,0);
  }
  return;
}

/* 005bc4a1 auto */
void __cdecl wnd_obj_move_xy(NativeWindow *wnd,int x,int y)

{
  int nHeight;
  int nWidth;
  BOOL bRepaint;
  tagRECT rect;
  
  if (wnd != 0) {
    GetWindowRect(wnd->hwnd,&rect);
    bRepaint = 1;
    nHeight = rect_height(&rect);
    nWidth = rect_width(&rect);
    MoveWindow(wnd->hwnd,x,y,nWidth,nHeight,bRepaint);
  }
  return;
}

/* 005bc505 auto */
void __cdecl wnd_obj_set_client_size(NativeWindow *wnd,int width,int height)

{
  int frame_w;
  int frame_h;
  tagPOINT origin;
  HWND parent_hwnd;
  tagRECT rect;
  
  if (wnd != 0) {
    GetWindowRect(wnd->hwnd,&rect);
    frame_w = wnd_obj_frame_width(wnd);
    frame_h = wnd_obj_frame_height(wnd);
    parent_hwnd = GetParent(wnd->hwnd);
    if ((parent_hwnd != (HWND)0x0) && ((wnd->flags_bytes[1] & 2) != 0)) {
      origin.x = 0;
      origin.y = 0;
      MapWindowPoints(parent_hwnd,(HWND)0x0,&origin,1);
      rect.left -= origin.x;
      rect.top -= origin.y;
    }
    MoveWindow(wnd->hwnd,rect.left,rect.top,width + frame_w,height + frame_h,1);
  }
  return;
}

/* 005bc5da auto */
void __cdecl wnd_obj_maximize(NativeWindow *wnd)

{
  if (wnd != 0) {
    ShowWindow(wnd->hwnd,3);
  }
  return;
}

/* 005bc636 auto */
void __cdecl wnd_obj_minimize(NativeWindow *wnd)

{
  if (wnd != 0) {
    ShowWindow(wnd->hwnd,6);
  }
  return;
}

/* 005bc692 auto */
void __cdecl wnd_obj_show_restored(NativeWindow *wnd)

{
  if (wnd != 0) {
    ShowWindow(wnd->hwnd,9);
  }
  return;
}

/* 005bc6bb auto */
void __cdecl wnd_obj_validate_rect(NativeWindow *wnd,RECT *rect)

{
  if (wnd != 0) {
    ValidateRect(wnd->hwnd,rect);
  }
  return;
}

/* 005bc713 auto */
void __cdecl wnd_obj_move_to_rect(NativeWindow *wnd,int *rect)

{
  int nHeight;
  int nWidth;
  BOOL bRepaint;
  
  if (wnd != 0) {
    bRepaint = 1;
    nHeight = rect_height((RECT *)rect);
    nWidth = rect_width((RECT *)rect);
    MoveWindow(wnd->hwnd,*rect,rect[1],nWidth,nHeight,bRepaint);
  }
  return;
}

/* 005bc763 auto */
void __cdecl wnd_obj_center(NativeWindow *wnd,int offset_x,int offset_y)

{
  HWND hWnd;
  int outer_w;
  int outer_h;
  int wnd_w;
  BOOL bRepaint;
  tagRECT wnd_rect;
  int pos_y2;
  int pos_x2;
  tagPOINT origin;
  tagRECT parent_rect;
  
  if (wnd != 0) {
    GetWindowRect(wnd->hwnd,&wnd_rect);
    hWnd = GetParent(wnd->hwnd);
    if (hWnd == (HWND)0x0) {
      outer_w = GetSystemMetrics(0);
      outer_h = GetSystemMetrics(1);
      wnd_w = rect_width(&wnd_rect);
      pos_x2 = outer_w - wnd_w >> 1;
      outer_w = rect_height(&wnd_rect);
      pos_y2 = outer_h - outer_w >> 1;
    }
    else if ((wnd->flags_bytes[1] & 2) == 0) {
      GetWindowRect(hWnd,&parent_rect);
      outer_w = rect_width(&parent_rect);
      outer_h = rect_height(&parent_rect);
      wnd_w = rect_width(&wnd_rect);
      pos_x2 = outer_w - wnd_w >> 1;
      outer_w = rect_height(&wnd_rect);
      pos_y2 = outer_h - outer_w >> 1;
      origin.x = 0;
      origin.y = 0;
      MapWindowPoints(hWnd,(HWND)0x0,&origin,1);
      pos_x2 += parent_rect.left;
      pos_y2 += parent_rect.top;
    }
    else {
      GetClientRect(hWnd,&parent_rect);
      outer_w = rect_width(&parent_rect);
      outer_h = rect_height(&parent_rect);
      wnd_w = rect_width(&wnd_rect);
      pos_x2 = outer_w - wnd_w >> 1;
      outer_w = rect_height(&wnd_rect);
      pos_y2 = outer_h - outer_w >> 1;
      if (pos_y2 < 0) {
        pos_y2 = 0;
      }
    }
    bRepaint = 1;
    outer_w = rect_height(&wnd_rect);
    outer_h = rect_width(&wnd_rect);
    MoveWindow(wnd->hwnd,pos_x2 + offset_x,pos_y2 + offset_y,outer_h,outer_w,bRepaint);
  }
  return;
}

/* 005bc933 auto */
LONG __cdecl wnd_obj_client_width(NativeWindow *wnd)

{
  tagRECT rect;
  
  if (wnd == 0) {
    rect.right = 0;
  }
  else {
    GetClientRect(wnd->hwnd,&rect);
  }
  return rect.right;
}

/* 005bc96b auto */
LONG __cdecl wnd_obj_client_height(NativeWindow *wnd)

{
  tagRECT rect;
  
  if (wnd == 0) {
    rect.bottom = 0;
  }
  else {
    GetClientRect(wnd->hwnd,&rect);
  }
  return rect.bottom;
}

/* 005bc9a3 auto */
void __cdecl wnd_obj_get_screen_rect(NativeWindow *wnd,LPRECT rect)

{
  if (wnd != 0) {
    GetWindowRect(wnd->hwnd,rect);
  }
  return;
}

/* 005bc9d3 auto */
int __cdecl wnd_obj_frame_width(NativeWindow *wnd)

{
  int result;
  int client_w;
  tagRECT rect;
  
  if (wnd == 0) {
    result = 0;
  }
  else {
    GetWindowRect(wnd->hwnd,&rect);
    result = rect_width(&rect);
    GetClientRect(wnd->hwnd,&rect);
    client_w = rect_width(&rect);
    result -= client_w;
  }
  return result;
}

/* 005bca3d auto */
int __cdecl wnd_obj_frame_height(NativeWindow *wnd)

{
  int result;
  int client_h;
  tagRECT rect;
  
  if (wnd == 0) {
    result = 0;
  }
  else {
    GetWindowRect(wnd->hwnd,&rect);
    result = rect_height(&rect);
    GetClientRect(wnd->hwnd,&rect);
    client_h = rect_height(&rect);
    result -= client_h;
  }
  return result;
}

/* 005bcb85 auto */
void __cdecl wnd_obj_get_rect_in_parent(NativeWindow *wnd,LPRECT rect)

{
  HWND hWndTo;
  tagPOINT *lpPoints;
  UINT cPoints;
  tagPOINT corners[2];  /* top left, bottom right */
  
  if (wnd != 0) {
    GetWindowRect(wnd->hwnd,rect);
    corners[0].x = rect->left;
    corners[0].y = rect->top;
    corners[1].x = rect->right;
    corners[1].y = rect->bottom;
    cPoints = 2;
    lpPoints = corners;
    hWndTo = GetParent(wnd->hwnd);
    MapWindowPoints((HWND)0x0,hWndTo,lpPoints,cPoints);
    SetRect(rect,corners[0].x,corners[0].y,corners[1].x,corners[1].y);
  }
  return;
}

/* 005bcdc3 auto */
void __cdecl wnd_obj_select_palette(NativeWindow *wnd,HPALETTE palette)

{
  if (gfx_palettized_display == 1) {
    wnd->palette = palette;
    SelectPalette(wnd->hdc,palette,0);
  }
  return;
}

/* 005bcdfc auto */
void __cdecl wnd_obj_attach_menu(NativeWindow *wnd,HMENU menu)

{
  int new_height;
  int menu_height;
  i32 width;
  
  if (wnd != 0) {
    SetMenu(wnd->hwnd,menu);
    new_height = wnd_obj_client_height(wnd);
    menu_height = GetSystemMetrics(0xf);
    new_height = new_height + menu_height + 1;
    width = wnd_obj_client_width(wnd);
    wnd_obj_set_client_size(wnd,width,new_height);
  }
  return;
}

/* 005bce5f auto */
void __cdecl wnd_obj_set_icon(NativeWindow *wnd,uint icon_id)

{
  HICON icon;
  BOOL is_window;
  
  if (wnd != 0) {
    if (wnd->icon != 0) {
      DestroyIcon(wnd->icon);
    }
    icon = LoadIconA(err_report_ctx_block.app_hinstance,(LPCSTR)(icon_id & 0xffff));
    wnd->icon = icon;
    is_window = IsWindow(wnd->hwnd);
    if ((is_window != 0) && (is_window = IsIconic(wnd->hwnd), is_window != 0)) {
      InvalidateRect(wnd->hwnd,(RECT *)0x0,0);
    }
  }
  return;
}

/* 005bcfdd auto */
void __cdecl wnd_obj_set_cursor_now(NativeWindow *wnd,i32 cursor_id,int apply_now)

{
  if ((wnd != 0) && (wnd_obj_set_cursor(wnd,cursor_id), apply_now != 0)) {
    SetCursor(wnd->cursor);
  }
  return;
}

/* 005bd05f auto */
void __cdecl wnd_obj_set_cursor(NativeWindow *wnd,uint cursor_id)

{
  HCURSOR cursor;
  
  if (wnd != 0) {
    if ((int)cursor_id < 0) {
      if (cursor_id == 0xffffffff) {
        cursor = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
        wnd->cursor = cursor;
      }
      else if (cursor_id == 0xfffffffe) {
        cursor = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f02);
        wnd->cursor = cursor;
      }
    }
    else {
      cursor = LoadCursorA(err_report_ctx_block.app_hinstance,(LPCSTR)(cursor_id & 0xffff));
      wnd->cursor = cursor;
    }
  }
  return;
}

/* 005bd0e7 auto */
void __cdecl wnd_obj_focus_and_raise(NativeWindow *wnd)

{
  if (wnd != 0) {
    SetFocus(wnd->hwnd);
    BringWindowToTop(wnd->hwnd);
  }
  return;
}

/* 005bd120 auto */
void __cdecl wnd_obj_set_focus(NativeWindow *wnd)

{
  if (wnd != 0) {
    SetFocus(wnd->hwnd);
  }
  return;
}

/* 005bd14c auto */
void __cdecl wnd_obj_disable_owner(NativeWindow *wnd,NativeWindow *owner)

{
  HWND parent_hwnd;
  BOOL is_window;
  
  if ((owner == 0) && (wnd != 0)) {
    parent_hwnd = GetParent(wnd->hwnd);
    is_window = IsWindow(parent_hwnd);
    if (is_window != 0) {
      is_window = 0;
      parent_hwnd = GetParent(wnd->hwnd);
      EnableWindow(parent_hwnd,is_window);
    }
  }
  else if (owner != 0) {
    EnableWindow(owner->hwnd,0);
  }
  return;
}

/* 005bd1c5 auto */
void __cdecl wnd_obj_enable_owner(NativeWindow *wnd,NativeWindow *owner)

{
  HWND parent_hwnd;
  BOOL is_window;
  
  if ((owner == 0) && (wnd != 0)) {
    parent_hwnd = GetParent(wnd->hwnd);
    is_window = IsWindow(parent_hwnd);
    if (is_window != 0) {
      is_window = 1;
      parent_hwnd = GetParent(wnd->hwnd);
      EnableWindow(parent_hwnd,is_window);
    }
  }
  else if (owner != 0) {
    EnableWindow(owner->hwnd,1);
  }
  return;
}

/* 005bd248 auto */
void __cdecl wnd_obj_set_caption_height(NativeWindow *wnd,i32 height)

{
  if (wnd != 0) {
    wnd->caption_height = height;
  }
  return;
}

/* 005bd270 auto */
void __cdecl wnd_obj_set_resize_border(NativeWindow *wnd,i32 border)

{
  if (wnd != 0) {
    wnd->resize_border = border;
  }
  return;
}

/* 005bd48f auto */
void __cdecl wnd_obj_get_cursor_pos(NativeWindow *wnd,LONG *out_x,LONG *out_y)

{
  tagPOINT pt;
  
  GetCursorPos(&pt);
  ScreenToClient(wnd->hwnd,&pt);
  *out_x = pt.x;
  *out_y = pt.y;
  return;
}

/* 005bd533 auto */
void __cdecl wnd_obj_set_capture(NativeWindow *wnd)

{
  SetCapture(wnd->hwnd);
  return;
}

/* 005bd550 auto */
void __cdecl wnd_obj_release_capture(NativeWindow *wnd)

{
  ReleaseCapture();
  return;
}

/* 005bd566: written by hand in src/game/retvals.cpp */

/* 005bd610 auto */
i16 __thiscall wnd_get_style_flags(WndStyleView *self)

{
  return (short)self->style_flags;
}

/* 005c5760 auto */
void __thiscall
wnd_create_framed
          (WndBase *self,const char *title,i32 style,i32 x,i32 y
          ,i32 width,i32 height,iptr palette)

{
  NativeWindow *hwnd;
  
  wnd_create_with_cmd_proc(self,title,style,x,y,width,height,palette);
  hwnd = wnd_get_window(self);
  wnd_install_frame_proc((iptr)self,hwnd);
  return;
}

/* 005c57f9 auto */
void __thiscall
wnd_create_framed_child
          (WndBase *self,const char *title,i32 style,i32 x,i32 y
          ,i32 width,i32 height,iptr palette,iptr parent)

{
  NativeWindow *hwnd;
  
  wnd_create_with_handlers(self,title,style,x,y,width,height,palette,parent);
  hwnd = wnd_get_window(self);
  wnd_install_frame_proc((iptr)self,hwnd);
  return;
}

/* 005c59c4 auto */
void __thiscall wnd_append_control(WndControlListView *self,iptr ctrl)

{
  uptr last;
  
  last = self->first_control;
  if (last == 0) {
    self->first_control = ctrl;
  }
  else {
    for (; *(int *)(last + 0x20) != 0; last = *(uptr *)(last + 0x20)) {
    }
    *(iptr *)(last + 0x20) = ctrl;
  }
  return;
}

/* 005c5a27 auto */
void __thiscall wnd_remove_control(WndControlRemoveView *self,int ctrl_id)

{
  int id;
  ControlIdView *this_00;
  ControlNextView *this_01;
  u32 next_next;
  ControlNextView *ctrl;
  
  if (self->first_control != 0) {
    ctrl = (ControlNextView *)self->first_control;
    id = ctrl_get_id((ControlIdView *)ctrl);
    if (id == ctrl_id) {
      self->first_control = ctrl->next_control;
    }
    else {
      while( true ) {
        if (ctrl == (ControlNextView *)0x0) {
          return;
        }
        id = control_get_next(ctrl);
        if (id == 0) {
          return;
        }
        this_00 = (ControlIdView *)control_get_next(ctrl);
        id = ctrl_get_id(this_00);
        if (id == ctrl_id) break;
        ctrl = (ControlNextView *)control_get_next(ctrl);
      }
      this_01 = (ControlNextView *)control_get_next(ctrl);
      next_next = control_get_next(this_01);
      ctrl->next_control = next_next;
    }
  }
  return;
}

/* 005c5aeb auto */
void __thiscall wnd_remove_all_controls(WndControlRemoveView *self)

{
  i32 ctrl_id;
  ControlIdView *ctrl;
  
  for (ctrl = (ControlIdView *)self->first_control; ctrl != (ControlIdView *)0x0;
      ctrl = *(ControlIdView **)((ControlIdViewExt *)ctrl)->next_control) {
    ctrl_id = ctrl_get_id(ctrl);
    wnd_remove_control(self,ctrl_id);
  }
  return;
}

/* 005c5b7f auto */
void __thiscall wnd_focus_first_control(Wnd *self)

{
  char wants_focus;
  ControlInitialFocusView *ctrl;
  
  ctrl = (ControlInitialFocusView *)self->control_list;
  while( true ) {
    if (ctrl == (ControlInitialFocusView *)0x0) {
      if ((self->control_list != 0) && ((char)self->keyboard_nav != '\0')) {
        wnd_focus_control((iptr)self,self->control_list);
      }
      return;
    }
    wants_focus = ctrl_get_initial_focus(ctrl);
    if (wants_focus != '\0') break;
    ctrl = (ControlInitialFocusView *)control_get_next((ControlNextView *)ctrl);
  }
  if ((char)self->keyboard_nav == '\0') {
    return;
  }
  wnd_focus_control((iptr)self,(iptr)ctrl);
  return;
}

/* 005c5c86 auto */
i32 __thiscall wnd_dispatch_hotkey_char(void *self,i32 ch)

{
  u8 key;
  iptr ctrl_type;
  iptr enabled;
  i32 hwnd;
  int value;
  int item_count;
  int i;
  i32 handled;
  RadioGroupItemsView *ctrl;
  u8 key_str[4];
  char done;
  
  done = '\0';
  handled = 0;
  key_str[0] = (u8)ch;
  key_str[1] = 0;
  __strlwr((char *)key_str);
  key = key_str[0];
  ctrl = *(RadioGroupItemsView **)((int)self + 0xb8);
  do {
    if (ctrl == (RadioGroupItemsView *)0x0) {
      return handled;
    }
    if (done != '\0') {
      return handled;
    }
    if (*(int *)ctrl->hotkey_index < 0) {
      value = control_get_type((ControlTypeView *)ctrl);
      if (value == 3) {
        value = radiogrp_get_items(ctrl);
        item_count = radiogrp_item_count((RadioGroupCountView *)ctrl);
        for (i = 0; i < item_count; i++) {
          if ((-1 < *(int *)(value + 0xa0 + i * 0xa4)) &&
             (*(u8 *)(value + 0x9c + i * 0xa4) == key)) {
            radiogrp_item_activate(*(i32 *)(value + i * 0xa4));
            handled = 1;
            done = 1;
            break;
          }
        }
      }
    }
    else if (ctrl->control_header[0x25] == key) {
      ctrl_type = control_get_type((ControlTypeView *)ctrl);
      if ((ctrl_type == 6) &&
         (enabled = ctrl_is_enabled((ControlEnabledView *)ctrl), enabled != 0)) {
        hwnd = control_get_hwnd((ControlHwndView *)ctrl);
        button_press_animated(hwnd);
        return 1;
      }
      value = control_get_type((ControlTypeView *)ctrl);
      if ((value == 2) && (value = checkbox_is_enabled((CheckboxEnabledView *)ctrl), value != 0)) {
        hwnd = control_get_hwnd((ControlHwndView *)ctrl);
        checkbox_toggle_by_hotkey(hwnd);
        return 1;
      }
    }
    ctrl = *(RadioGroupItemsView **)ctrl->next_control;
  } while( true );
}

/* 005c5f20 auto */
void __thiscall
wnd_create_with_cmd_proc
          (WndBase *self,const char *title,i32 style,i32 x,i32 y
          ,i32 width,i32 height,iptr palette)

{
  NativeWindow *hwnd;
  
  wnd_record_create(self,(i32)title,style,x,y,width,height,palette);
  hwnd = wnd_get_window(self);
  wnd_install_command_proc((iptr)self,hwnd);
  wnd_clear_handlers((WndHandlers *)(self + 1));
  return;
}

/* 005c5fc4 auto */
void __thiscall
wnd_create_with_handlers
          (WndBase *self,const char *title,i32 style,i32 x,i32 y
          ,i32 width,i32 height,iptr palette,iptr parent)

{
  NativeWindow *hwnd;
  
  wnd_record_create_child(self,(i32)title,style,x,y,width,height,palette,(WndBase *)parent);
  hwnd = wnd_get_window(self);
  wnd_install_command_proc((iptr)self,hwnd);
  wnd_clear_handlers((WndHandlers *)(self + 1));
  return;
}

/* 005c61b0 auto */
void __thiscall wnd_run_modal_loop(ModalMenuWindow *self)

{
  NativeWindow *wnd;
  NativeWindow *owner_after;
  NativeWindow *owner2;
  
  if (wnd_modal_depth != 0xf) {
    self->modal_running = 1;
    wnd_modal_depth++;
    (((i32 *)&wnd_modal_stack_below_block.wnd_modal_stack))[wnd_modal_depth] = (i32)self;
    if (wnd_modal_depth == 0) {
      owner2 = 0;
    }
    else {
      owner2 = wnd_get_window((WndBase *)(((i32 *)&wnd_modal_stack_below_block.wnd_modal_stack_below))[wnd_modal_depth]);
    }
    wnd = wnd_get_window((WndBase *)self);
    wnd_obj_disable_owner(wnd,owner2);
    while (self->modal_running != 0) {
      win_pump_one_message();
      if (self->on_modal_idle != 0) {
        call_untyped((code *)self->on_modal_idle);
      }
    }
    if (wnd_modal_depth == 0) {
      owner_after = 0;
    }
    else {
      owner_after = wnd_get_window((WndBase *)(((i32 *)&wnd_modal_stack_below_block.wnd_modal_stack_below))[wnd_modal_depth]);
    }
    wnd = wnd_get_window((WndBase *)self);
    wnd_obj_enable_owner(wnd,owner_after);
    wnd_modal_depth--;
    if (-1 < wnd_modal_depth) {
      self->modal_running = 1;
    }
  }
  return;
}

/* 005c62cb auto */
/* Library Function - Single Match
    public: void __thiscall CRichEditDoc::InvalidateObjectCache(void)
   
   Library: Visual Studio 1998 Debug */

void __thiscall wnd_end_modal_loop(ModalMenuWindow *self)

{
  self->modal_running = 0;
  return;
}

/* 005c62ee auto */
i32 __cdecl wnd_get_active_child(void)

{
  return wnd_active_child;
}

/* 005c6303 auto */
i32 __cdecl wnd_set_active_child(iptr child)

{
  i32 prev;
  
  prev = wnd_active_child;
  wnd_active_child = child;
  return prev;
}

/* 005c63af auto */
bool __thiscall wnd_fire_menu_select(WndMenuSelectView *self,i32 item_id)

{
  bool has_handler;
  
  has_handler = self->on_menu_select != 0;
  if (has_handler) {
    call_untyped((code *)self->on_menu_select, item_id);
  }
  return has_handler;
}

/* 005c8b00 auto */
void __cdecl wnd_invalidate(HWND hwnd)

{
  if (hwnd != (HWND)0x0) {
    InvalidateRect(hwnd,(RECT *)0x0,0);
  }
  return;
}

/* 005c8b2d auto */
void __cdecl hwnd_show(HWND hwnd)

{
  if (hwnd != (HWND)0x0) {
    ShowWindow(hwnd,5);
  }
  return;
}

/* 005c8b58 auto */
void __cdecl hwnd_hide(HWND hwnd)

{
  if (hwnd != (HWND)0x0) {
    ShowWindow(hwnd,0);
  }
  return;
}

/* 005c8be1 auto */
HWND __cdecl hotspot_create_hwnd(int *rect,iptr ctrl)

{
  WndBase *self;
  NativeWindow *parent_wnd;
  iptr height;
  int width;
  HWND hotspot_hwnd;
  HMENU hMenu;
  HINSTANCE hInstance;
  LPVOID lpParam;
  
  lpParam = (LPVOID)0x0;
  hMenu = (HMENU)0x0;
  hInstance = err_report_ctx_block.app_hinstance;
  self = (WndBase *)ctrl_get_parent((Control *)ctrl);
  parent_wnd = wnd_get_window(self);
  hotspot_hwnd = parent_wnd->hwnd;
  height = rect_height((RECT *)rect);
  width = rect_width((RECT *)rect);
  hotspot_hwnd = CreateWindowExA(4,str_mscontrolclass,((i8 *)&hotspot_wnd_title),0x50000000,*rect,rect[1],
                           width,height,hotspot_hwnd,hMenu,hInstance,lpParam);
  width = (int)ctrl_init_block(hotspot_hwnd,ctrl);
  *(i32 *)(width + 0x2c) = 1;
  SetWindowLongA(hotspot_hwnd,-4,(iptr)hotspot_wndproc);
  return hotspot_hwnd;
}

/* 005c8f70 auto */
void __thiscall hotspot_fire_enter(HotspotEnterView *self,i32 arg)

{
  if (self->on_enter != 0) {
    call_untyped((code *)self->on_enter, arg);
  }
  return;
}

/* 005c8fb0 auto */
void __thiscall hotspot_fire_leave(HotspotLeaveView *self,i32 event_arg)

{
  if (self->on_leave != 0) {
    call_untyped((code *)self->on_leave, event_arg);
  }
  return;
}

/* 005c8ff0 auto */
void __thiscall hotspot_fire_click(HotspotClickView *self,i32 event_arg)

{
  if (self->on_click != 0) {
    call_untyped((code *)self->on_click, event_arg);
  }
  return;
}

/* 005c9030 auto */
void __thiscall hotspot_fire_press(HotspotPressView *self,i32 event_arg)

{
  if (self->on_press != 0) {
    call_untyped((code *)self->on_press, event_arg);
  }
  return;
}

/* 005c9070 auto */
void __thiscall hotspot_fire_dblclick(HotspotDblClickView *self,i32 event_arg)

{
  if (self->on_dblclick != 0) {
    call_untyped((code *)self->on_dblclick, event_arg);
  }
  return;
}

/* 005c9563 auto */
ControlBlock * __cdecl wnd_from_hwnd(HWND hwnd)

{
  ControlBlock *wnd_data;
  
  if (hwnd == (HWND)0x0) {
    wnd_data = 0;
  }
  else {
    wnd_data = (ControlBlock *)GetWindowLongA(hwnd,0);
  }
  return wnd_data;
}

/* 005c96cc auto */
void __cdecl wnd_redraw_client(HWND hwnd)

{
  tagRECT client_rect2;
  
  GetClientRect(hwnd,&client_rect2);
  InvalidateRect(hwnd,&client_rect2,1);
  UpdateWindow(hwnd);
  return;
}

/* 005cbdd0 auto */
u8 __thiscall wnd_keyboard_nav_enabled(WndKeyNavView *self)

{
  return self->keyboard_nav;
}

/* 005cbeb0 auto */
void __cdecl ui_wait_ticks(i32 ticks)

{
  timer_busy_wait_ticks(ticks);
  return;
}

/* 005cbed0 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl default_draw_font_static_init(void)

{
  default_draw_font_ctor();
  default_draw_font_reg_dtor();
  return;
}

/* 005cbeea auto */
void __cdecl default_draw_font_ctor(void)

{
  font_init_empty((GameFont *)((i32 *)&default_draw_font_obj_block.default_draw_font_obj));
  return;
}

/* 005cbf04 auto */
void __cdecl default_draw_font_reg_dtor(void)

{
  _atexit(default_draw_font_static_dtor);
  return;
}

/* 005cbf21 auto */
void __cdecl default_draw_font_static_dtor(void)

{
  font_destroy((GameFont *)((i32 *)&default_draw_font_obj_block.default_draw_font_obj));
  return;
}

/* 005d2550 auto */
void __cdecl ui_set_ctrl_text_color(i32 color_index)

{
  (*(i8 *)&ctrl_text_color_index) = (i8)color_index;
  return;
}

/* 005d2568 auto */
void __cdecl ui_set_ctrl_text_shadow(i32 color_index,i32 dx,i32 dy)

{
  (*(i8 *)&ctrl_shadow_color_index) = (i8)color_index;
  (*(i8 *)&ctrl_shadow_dx) = (i8)dx;
  (*(i8 *)&ctrl_shadow_dy) = (i8)dy;
  return;
}

/* 005d2590 auto */
void __cdecl ui_set_ctrl_disabled_color(i32 color_index)

{
  (*(i8 *)&ctrl_disabled_color_index) = (i8)color_index;
  return;
}

/* 005d25a8 auto */
void __cdecl ui_set_ctrl_font(iptr font)

{
  (*(i8 * *)(draw_current_font_rest + 8)) = (i8 *)font;
  return;
}

/* 005d268e auto */
void __cdecl ui_set_default_font(iptr font)

{
  (*(i8 * *)(draw_current_font_rest + 12)) = (i8 *)font;
  return;
}

/* 005d2d4d auto */
void __cdecl hwnd_get_text(HWND hwnd,LPARAM buffer)

{
  LRESULT text_len;
  
  text_len = SendMessageA(hwnd,0xe,0,0);
  SendMessageA(hwnd,0xd,text_len + 1,buffer);
  return;
}

/* 005d2d7f auto */
void __cdecl hwnd_send_settext(HWND hwnd,LPARAM text)

{
  SendMessageA(hwnd,0xc,0,text);
  return;
}

/* 005d417f auto */
void __cdecl ui_set_radio_text_color(i32 color_index)

{
  (*(i8 *)&radio_text_color_index) = (i8)color_index;
  return;
}

/* 005d4197 auto */
void __cdecl ui_set_radio_disabled_color(i32 color_index)

{
  (*(i8 *)&radio_disabled_color_index) = (i8)color_index;
  return;
}

/* 005d41af auto */
void __cdecl ui_set_radio_text_shadow(i32 color_index,i32 dx,i32 dy)

{
  (*(i8 *)&radio_shadow_color_index) = (i8)color_index;
  (*(i8 *)&radio_shadow_dx) = (i8)dx;
  (*(i8 *)&radio_shadow_dy) = (i8)dy;
  return;
}

/* 005d8236 auto */
void __cdecl ui_set_button_font(iptr font)

{
  (*(i8 * *)draw_current_font_rest) = (i8 *)font;
  return;
}

/* 005db610 auto */
WndBase * __thiscall wnd_record_init(WndBase *self)

{
  self->native_wnd = 0;
  self->wnd_palette = 0;
  self->wnd_record = 0;
  self->style = 0;
  return self;
}

/* 005db650 auto */
void __thiscall wnd_record_destroy(WndDestroyView *self)

{
  NativeWindow *destroyed_obj;
  
  destroyed_obj = (NativeWindow *)wnd_obj_destroy(self->wnd_obj);
  self->wnd_obj = destroyed_obj;
  return;
}

/* 005db67b auto */
void __thiscall
wnd_record_create
          (WndBase *self,i32 wnd_kind,u32 style,i32 x,i32 y,
          i32 width,i32 height,iptr palette)

{
  NativeWindow *native;
  
  self->style = style;
  if (self->native_wnd != 0) {
    native = (NativeWindow *)wnd_obj_destroy(self->native_wnd);
    self->native_wnd = native;
  }
  native = wnd_obj_create((LPCSTR)wnd_kind,style,x,y,width,height,0);
  self->native_wnd = native;
  wnd_set_owner_ptr((iptr)self,self->native_wnd);
  wnd_set_palette(self,palette);
  return;
}

/* 005db893 auto */
void __thiscall
wnd_record_create_child
          (WndBase *self,i32 wnd_kind,u32 style,i32 x,i32 y,
          i32 width,i32 height,iptr palette,WndBase *parent)

{
  NativeWindow *native;
  NativeWindow *parent_wnd;
  
  self->style = style;
  if (self->native_wnd != 0) {
    native = (NativeWindow *)wnd_obj_destroy(self->native_wnd);
    self->native_wnd = native;
  }
  parent_wnd = wnd_get_window(parent);
  native = wnd_obj_create((LPCSTR)wnd_kind,style,x,y,width,height,parent_wnd);
  self->native_wnd = native;
  wnd_set_owner_ptr((iptr)self,self->native_wnd);
  wnd_set_palette(self,palette);
  return;
}

/* 005dba95 auto */
i32 __thiscall wnd_is_shift_down(void *self)

{
  i32 is_down;
  
  is_down = input_poll_modifier(0x100);
  return is_down;
}

/* 005dbab8 auto */
i32 __thiscall wnd_is_ctrl_down(void *self)

{
  i32 is_down;
  
  is_down = input_poll_modifier(0x200);
  return is_down;
}

/* 005dcc10 auto */
GameMenu * __thiscall menu_handle_ctor(GameMenu *self)

{
  self->hmenu = 0;
  return self;
}

/* 005dcc32 auto */
/* Library Function - Single Match
    public: __thiscall _Timevec::~_Timevec(void)
   
   Library: Visual Studio 1998 Debug */

void __thiscall menu_handle_dtor(GameMenu *self)

{
  menu_hmenu_destroy(self->hmenu);
  return;
}

/* 005e00bb auto */
void __cdecl dlg_radio_choice_button_cb(int button_id)

{
  if (button_id == 0x65) {
    wnd_end_modal_loop((ModalMenuWindow *)(err_report_ctx_block.choice_dlg_window + 0x48));
  }
  else if (button_id == 0x66) {
    err_report_ctx_block.choice_dlg_selection = 0xffffffff;
    wnd_end_modal_loop((ModalMenuWindow *)(err_report_ctx_block.choice_dlg_window + 0x48));
  }
  return;
}

/* 005e0863: written by hand in src/game/unwind.cpp */

/* 005e0ce0 auto */
iptr __cdecl menu_hmenu_parse_items(HMENU hmenu,iptr spec)

{
  bool done;
  iptr _Source;
  size_t uBytes;
  HLOCAL hMem;
  char *_Dest;
  int cmp;
  int item_count2;
  HMENU item_id;
  uint flags2;
  size_t label_len;
  
  done = false;
  item_count2 = 0;
  uBytes = _strlen((char *)spec);
  hMem = LocalAlloc(2,uBytes);
  _Dest = (char *)LocalLock(hMem);
  *_Dest = '\0';
  for (; *(char *)spec == ' '; spec++) {
  }
  while (!done) {
    if (*(char *)spec == '!') {
      flags2 = 3;
      spec++;
    }
    else {
      flags2 = 0;
    }
    if (*(char *)spec == '*') {
      flags2 = flags2 | 8;
      spec++;
    }
    _Source = spec;
    label_len = 0;
    for (; ((*(char *)spec != '}' && (*(char *)spec != '_')) && (*(char *)spec != '{'));
        spec = spec + 1) {
      label_len++;
    }
    _strncat(_Dest,(char *)_Source,label_len);
    if ((*(char *)spec == '_') || (*(char *)spec == '}')) {
      if (*(char *)spec == '}') {
        done = true;
      }
      item_id = menu_next_item_id;
      menu_next_item_id = (HMENU)((iptr)menu_next_item_id + 1);
      do {
        spec++;
      } while (*(char *)spec == ' ');
    }
    else if (*(char *)spec == '{') {
      item_id = CreateMenu();
      spec = menu_hmenu_parse_items(item_id,spec + 1);
      flags2 = flags2 | 0x10;
      for (; *(char *)spec == ' '; spec++) {
      }
      if (*(char *)spec == '}') {
        done = true;
        spec++;
      }
    }
    item_count2++;
    if (0x16 < item_count2) {
      item_count2 = 0;
      flags2 = flags2 | 0x40;
    }
    cmp = _strcmp(_Dest,((i8 *)&menu_separator_tag));
    if (cmp == 0) {
      flags2 = 0x800;
      *_Dest = '\0';
      item_id = (HMENU)0x0;
    }
    AppendMenuA(hmenu,flags2,item_id,_Dest);
    *_Dest = '\0';
  }
  LocalUnlock(hMem);
  LocalFree(hMem);
  return spec;
}

/* 005e0f2a auto */
HMENU __cdecl menu_hmenu_build_from_spec(char *spec)

{
  char prefix_char;
  int base_item_id;
  char *_Source;
  HMENU hMenu;
  size_t uBytes;
  HLOCAL hMem;
  char *_Dest;
  HMENU uIDNewItem;
  size_t label_len;
  char *cursor;
  
  cursor = spec;
  hMenu = CreateMenu();
  base_item_id = (*(int *)&menu_next_item_id);
  uBytes = _strlen(spec);
  hMem = LocalAlloc(2,uBytes);
  _Dest = (char *)LocalLock(hMem);
  *_Dest = '\0';
  while (*cursor != '\0') {
    for (; *cursor == ' '; cursor++) {
    }
    prefix_char = *cursor;
    if (prefix_char == '!') {
      cursor++;
    }
    _Source = cursor;
    label_len = 0;
    for (; *cursor != '{'; cursor++) {
      label_len++;
    }
    _strncat(_Dest,_Source,label_len);
    do {
      cursor++;
    } while (*cursor == ' ');
    uIDNewItem = CreateMenu();
    cursor = (char *)menu_hmenu_parse_items(uIDNewItem,(iptr)cursor);
    if (prefix_char != '!') {
      AppendMenuA(hMenu,0x10,uIDNewItem,_Dest);
    }
    else {
      AppendMenuA(hMenu,0x13,uIDNewItem,_Dest);
    }
    *_Dest = '\0';
  }
  (*(int *)&menu_next_item_id) = base_item_id + 100;
  LocalUnlock(hMem);
  LocalFree(hMem);
  return hMenu;
}

/* 005e10c7 auto */
void __cdecl menu_hmenu_destroy(HMENU hmenu)

{
  if (hmenu != (HMENU)0x0) {
    DestroyMenu(hmenu);
  }
  return;
}

/* 005e10fb auto */
void __cdecl menu_redraw_bar(NativeWindow *wnd)

{
  DrawMenuBar(wnd->hwnd);
  return;
}

/* 005e1118 auto */
BOOL __cdecl menu_hmenu_enable_item(HMENU hmenu,int menu_pos,int item_pos,i32 enable)

{
  BOOL enable_ret;
  HMENU hMenu;
  
  if (item_pos == 0) {
    if ((char)enable == '\0') {
      enable_ret = EnableMenuItem(hmenu,menu_pos - 1,0x403);
    }
    else {
      enable_ret = EnableMenuItem(hmenu,menu_pos - 1,0x400);
    }
  }
  else {
    hMenu = GetSubMenu(hmenu,menu_pos - 1);
    if ((char)enable == '\0') {
      enable_ret = EnableMenuItem(hMenu,item_pos - 1,0x403);
    }
    else {
      enable_ret = EnableMenuItem(hMenu,item_pos - 1,0x400);
    }
  }
  return enable_ret;
}

/* 005e11be auto */
void __cdecl menu_hmenu_check_item(HMENU hmenu,int menu_pos,int item_pos,i32 checked)

{
  HMENU hMenu;
  
  if (hmenu != (HMENU)0x0) {
    hMenu = GetSubMenu(hmenu,menu_pos - 1);
    if ((char)checked == '\0') {
      CheckMenuItem(hMenu,item_pos - 1,0x400);
    }
    else {
      CheckMenuItem(hMenu,item_pos - 1,0x408);
    }
  }
  return;
}

/* 005e1226 auto */
void __cdecl menu_hmenu_delete_item(HMENU hmenu,int menu_pos,int item_pos)

{
  HMENU hMenu;
  
  if (hmenu != (HMENU)0x0) {
    hMenu = GetSubMenu(hmenu,menu_pos - 1);
    if (item_pos == -1) {
      RemoveMenu(hmenu,menu_pos - 1,0x400);
    }
    else {
      DeleteMenu(hMenu,item_pos - 1,0x400);
    }
  }
  return;
}

/* 005e128c auto */
void __cdecl menu_hmenu_insert_item(HMENU hmenu,int menu_pos,int item_pos,LPCSTR text)

{
  UINT_PTR uIDNewItem;
  HMENU submenu;
  int item_count2;
  uint flags2;
  
  if (hmenu != (HMENU)0x0) {
    submenu = GetSubMenu(hmenu,menu_pos - 1);
    item_count2 = 0;
    if (((submenu != (HMENU)0x0) && (item_pos != -1)) && (menu_pos != -1)) {
      item_count2 = GetMenuItemCount(submenu);
    }
    uIDNewItem = (*&menu_next_item_id);
    if ((item_count2 % 0x16 == 0) && (item_count2 != 0)) {
      flags2 = 0x440;
    }
    else {
      flags2 = 0x400;
    }
    if (item_pos == -1) {
      submenu = CreatePopupMenu();
      if (menu_pos == -1) {
        AppendMenuA(hmenu,flags2 | 0x10,submenu,text);
      }
      else {
        InsertMenuA(hmenu,menu_pos - 1,flags2 | 0x10,submenu,text);
      }
    }
    else {
      (*&menu_next_item_id)++;
      InsertMenuA(submenu,item_pos - 1,flags2,uIDNewItem,text);
    }
  }
  return;
}

/* 005e14c8 auto */
void __cdecl menu_hmenu_set_item_text(HMENU hmenu,int menu_pos,int item_pos,LPCSTR text)

{
  HMENU hMenu;
  UINT uIDNewItem;
  
  if (hmenu != (HMENU)0x0) {
    hMenu = GetSubMenu(hmenu,menu_pos - 1);
    if (item_pos == -1) {
      ModifyMenuA(hmenu,menu_pos - 1,0x410,hMenu,text);
    }
    else {
      uIDNewItem = GetMenuItemID(hMenu,item_pos - 1);
      ModifyMenuA(hMenu,item_pos - 1,0x400,uIDNewItem,text);
    }
  }
  return;
}

/* 005e1880 auto */
void __cdecl wnd_install_paint_proc(iptr surface,NativeWindow *wnd)

{
  SetWindowLongA(wnd->hwnd,0xc,surface);
  SetWindowLongA(wnd->hwnd,-4,(iptr)surfwnd_subclass_wndproc);
  return;
}

/* 005e18ff auto */
i32 __stdcall surfwnd_subclass_wndproc(HWND hwnd,int msg,i32 wparam,uint lparam)

{
  SurfaceWindow *self;
  i32 result;
  BOOL is_iconic;
  NativeWindow *owner_wnd;
  iptr surf_width;
  int src_dim;
  int dim_b;
  int paint_extent;
  int dest_extent;
  int yDest;
  LONG wDest;
  LONG hDest;
  HDC hdcSrc;
  int xSrc;
  int ySrc;
  DWORD rop;
  u8 *owner_ptr;
  tagPAINTSTRUCT ps;
  HDC hdc;
  tagRECT dest_rect;
  RECT paint_rect;
  
  self = (SurfaceWindow *)GetWindowLongA(hwnd,0xc);
  if (self == (SurfaceWindow *)0x0) {
    result = wnd_frame_wndproc(hwnd,msg,wparam,lparam);
  }
  else if (msg == 2) {
    surface_create((DibSurface *)self,0,0);
    SetWindowLongA(hwnd,0xc,0);
    result = wnd_frame_wndproc(hwnd,2,wparam,lparam);
  }
  else if (msg == 5) {
    if (self == (SurfaceWindow *)0x0) {
      (*(u8 * *)&wnd_active_child) = (u8 *)0x0;
    }
    else {
      (*(u8 * *)&wnd_active_child) = self->window_2;
    }
    is_iconic = IsIconic(hwnd);
    if (is_iconic == 0) {
      surfwnd_on_resize(self,lparam & 0xffff,lparam >> 0x10);
    }
    result = wnd_frame_wndproc(hwnd,5,wparam,lparam);
  }
  else if (msg == 0xf) {
    is_iconic = IsIconic(hwnd);
    if (is_iconic == 0) {
      is_iconic = IsWindowVisible(hwnd);
      if (is_iconic != 0) {
        BeginPaint(hwnd,&ps);
        paint_rect.left = ps.rcPaint.left;
        paint_rect.top = ps.rcPaint.top;
        paint_rect.right = ps.rcPaint.right;
        paint_rect.bottom = ps.rcPaint.bottom;
        if (self == (SurfaceWindow *)0x0) {
          owner_ptr = (u8 *)0x0;
        }
        else {
          owner_ptr = self->window_2;
        }
        surface_blit_to_wnd
                  ((DibSurface *)self,(iptr)owner_ptr,&paint_rect,(iptr)&paint_rect);
        EndPaint(hwnd,&ps);
      }
    }
    else {
      owner_wnd = wnd_get_window((WndBase *)self->window_2);
      if (owner_wnd->icon != 0) {
        result = wnd_base_wndproc(hwnd,0xf,wparam,lparam);
        return result;
      }
      hdc = BeginPaint(hwnd,&ps);
      paint_rect.left = ps.rcPaint.left;
      paint_rect.top = ps.rcPaint.top;
      paint_rect.right = ps.rcPaint.right;
      paint_rect.bottom = ps.rcPaint.bottom;
      SetRect(&dest_rect,0,0,0,0);
      surf_width = surface_get_width((DibSurface *)self);
      src_dim = surface_get_height((DibSurface *)self);
      if (surf_width < src_dim) {
        src_dim = surface_get_width((DibSurface *)self);
        dim_b = rect_width(&paint_rect);
        dest_rect.right = surface_get_height((DibSurface *)self);
        dest_rect.right = (src_dim * dim_b) / dest_rect.right;
        dest_rect.bottom = rect_height(&paint_rect);
      }
      else {
        dest_rect.right = rect_width(&paint_rect);
        src_dim = surface_get_height((DibSurface *)self);
        dim_b = rect_height(&paint_rect);
        dest_rect.bottom = surface_get_width((DibSurface *)self);
        dest_rect.bottom = (src_dim * dim_b) / dest_rect.bottom;
      }
      src_dim = (int)surface_get_dib((DibSurface *)self);
      hdcSrc = *(HDC *)(src_dim + 4);
      rop = 0xcc0020;
      src_dim = surface_get_height((DibSurface *)self);
      dim_b = surface_get_width((DibSurface *)self);
      ySrc = 0;
      xSrc = 0;
      wDest = dest_rect.right;
      hDest = dest_rect.bottom;
      paint_extent = rect_height(&paint_rect);
      dest_extent = rect_height(&dest_rect);
      yDest = paint_extent - dest_extent >> 1;
      paint_extent = rect_width(&paint_rect);
      dest_extent = rect_width(&dest_rect);
      StretchBlt(hdc,paint_extent - dest_extent >> 1,yDest,wDest,hDest,hdcSrc,xSrc,ySrc,dim_b,src_dim,rop);
      EndPaint(hwnd,&ps);
    }
    result = 0;
  }
  else {
    result = wnd_frame_wndproc(hwnd,msg,wparam,lparam);
  }
  return result;
}

/* 005ea7a0 auto */
void __cdecl wnd_install_frame_proc(iptr owner,NativeWindow *wnd)

{
  SetWindowLongA(wnd->hwnd,8,owner);
  SetWindowLongA(wnd->hwnd,-4,(iptr)wnd_frame_wndproc);
  return;
}

/* 005ea825 auto */
HWND __cdecl hwnd_next_sibling_wrap(HWND hwnd)

{
  BOOL is_window;
  HWND sibling;
  
  is_window = IsWindow(hwnd);
  if (is_window == 0) {
    sibling = (HWND)0x0;
  }
  else {
    sibling = GetWindow(hwnd,2);
    if (sibling == (HWND)0x0) {
      sibling = GetWindow(hwnd,0);
    }
  }
  return sibling;
}

/* 005ea87c auto */
HWND __cdecl hwnd_prev_sibling_wrap(HWND hwnd)

{
  BOOL is_window;
  HWND sibling;
  
  is_window = IsWindow(hwnd);
  if (is_window == 0) {
    sibling = (HWND)0x0;
  }
  else {
    sibling = GetWindow(hwnd,3);
    if (sibling == (HWND)0x0) {
      sibling = GetWindow(hwnd,1);
    }
  }
  return sibling;
}

/* 005ea8d3 auto */
void __cdecl wnd_cycle_control_focus(iptr wnd,HWND hwnd,int direction)

{
  NativeWindow *frame_win;
  BOOL is_child;
  NativeWindow *frame_win2;
  HWND start_hwnd;
  int result;
  CheckboxEnabledView *self;
  UINT first_cmd;
  UINT uCmd;
  HWND group_hwnd;
  
  if (hwnd == (HWND)0x0) {
    hwnd = GetFocus();
    start_hwnd = hwnd;
    frame_win = wnd_get_window((WndBase *)wnd);
    is_child = IsChild(frame_win->hwnd,start_hwnd);
    if (is_child == 0) {
      hwnd = (HWND)0x0;
    }
  }
  if (hwnd == (HWND)0x0) {
    if (*(int *)(wnd + 0xb8) == 0) {
      return;
    }
    if (direction == 2) {
      first_cmd = 5;
      frame_win2 = wnd_get_window((WndBase *)wnd);
      hwnd = GetWindow(frame_win2->hwnd,first_cmd);
      start_hwnd = hwnd;
    }
    else {
      uCmd = 1;
      first_cmd = 5;
      result = (int)wnd_get_window((WndBase *)wnd);
      start_hwnd = GetWindow(((NativeWindow *)result)->hwnd,first_cmd);
      hwnd = GetWindow(start_hwnd,uCmd);
      start_hwnd = hwnd;
    }
  }
  else if (direction == 2) {
    hwnd = hwnd_next_sibling_wrap(hwnd);
    start_hwnd = hwnd;
  }
  else {
    hwnd = hwnd_prev_sibling_wrap(hwnd);
    start_hwnd = hwnd;
  }
  do {
    is_child = IsWindow(hwnd);
    if (is_child == 0) {
      return;
    }
    is_child = IsWindowVisible(hwnd);
    if (is_child == 0) {
      if (direction == 2) {
        hwnd = hwnd_next_sibling_wrap(hwnd);
      }
      else {
        hwnd = hwnd_prev_sibling_wrap(hwnd);
      }
    }
    else {
      result = ctrl_hwnd_is_radio(hwnd);
      if (result != 0) {
        group_hwnd = hwnd;
        while( true ) {
          is_child = IsWindow(hwnd);
          if (is_child == 0) {
            return;
          }
          result = radiogrp_hwnds_same_group(group_hwnd,hwnd);
          if (result == 0) break;
          result = radiogrp_hwnd_is_selected(hwnd);
          if (result != 0) {
            SetFocus(hwnd);
            return;
          }
          group_hwnd = hwnd;
          if (direction == 2) {
            hwnd = hwnd_next_sibling_wrap(hwnd);
          }
          else {
            hwnd = hwnd_prev_sibling_wrap(hwnd);
          }
        }
        wnd_cycle_control_focus(wnd,group_hwnd,direction);
        return;
      }
      self = (CheckboxEnabledView *)ctrl_list_find_by_hwnd(hwnd,(ControlNextView *)*(i32 *)(wnd + 0xb8));
      if ((self != (CheckboxEnabledView *)0x0) &&
         ((((result = control_get_type((ControlTypeView *)self), result == 6 &&
            (result = ctrl_is_enabled((ControlEnabledView *)self), result != 0)) ||
           ((result = control_get_type((ControlTypeView *)self), result == 2 &&
            (result = checkbox_is_enabled(self), result != 0)))) ||
          (((result = control_get_type((ControlTypeView *)self), result == 4 ||
            (result = control_get_type((ControlTypeView *)self), result == 7)) ||
           (result = control_get_type((ControlTypeView *)self), result == 10)))))) {
        SetFocus(hwnd);
        return;
      }
      if (direction == 2) {
        hwnd = hwnd_next_sibling_wrap(hwnd);
      }
      else {
        hwnd = hwnd_prev_sibling_wrap(hwnd);
      }
    }
    if (hwnd == start_hwnd) {
      return;
    }
  } while( true );
}

/* 005eabcc auto */
void __cdecl wnd_focus_control(iptr wnd,iptr control)

{
  char nav_enabled;
  int ctrl_type;
  i32 *items;
  i32 start_hwnd;
  
  nav_enabled = wnd_keyboard_nav_enabled((WndKeyNavView *)wnd);
  if (nav_enabled != '\0') {
    ctrl_type = control_get_type((ControlTypeView *)control);
    if (ctrl_type == 3) {
      items = (i32 *)radiogrp_get_items((RadioGroupItemsView *)control);
      start_hwnd = hwnd_prev_sibling_wrap(*items);
      wnd_cycle_control_focus(wnd,start_hwnd,2);
    }
    else {
      start_hwnd = control_get_hwnd((ControlHwndView *)control);
      start_hwnd = hwnd_prev_sibling_wrap(start_hwnd);
      wnd_cycle_control_focus(wnd,start_hwnd,2);
    }
  }
  return;
}

/* 005eb370 auto */
void __cdecl wnd_set_owner_ptr(iptr owner,NativeWindow *wnd)

{
  SetWindowLongA(wnd->hwnd,0,owner);
  return;
}

/* 005eb393 auto */
void __cdecl wnd_install_command_proc(iptr owner,NativeWindow *wnd)

{
  SetWindowLongA(wnd->hwnd,4,owner);
  SetWindowLongA(wnd->hwnd,-4,(iptr)wnd_child_wndproc);
  return;
}

/* 005ec1a1 auto */
void __cdecl wnd_on_menu_command(HWND hwnd,i32 cmd_id)

{
  char handled;
  WndOnCommandView *self;
  HMENU hmenu;
  uint pos;
  
  self = (WndOnCommandView *)GetWindowLongA(hwnd,4);
  handled = wnd_call_command(self,cmd_id);
  if (handled == '\0') {
    err_report_ctx_block.menu_search_pos = 0;
    hmenu = GetMenu(hwnd);
    if (hmenu != (HMENU)0x0) {
      pos = menu_find_item_pos(hmenu,cmd_id);
      wnd_call_menu_pos_command((WndOnMenuPosCommandView *)self,pos & 0xffff,pos >> 0x10);
    }
  }
  return;
}

/* 005ec23a auto */
uint __cdecl menu_find_item_pos(HMENU hmenu,UINT item_id)

{
  int item_count;
  UINT sub_id;
  HMENU submenu;
  i32 result;
  int i;
  
  result = 0;
  err_report_ctx_block.menu_search_pos++;
  item_count = GetMenuItemCount(hmenu);
  for (i = 0; i < item_count; i++) {
    sub_id = GetMenuItemID(hmenu,i);
    if (sub_id == 0xffffffff) {
      submenu = GetSubMenu(hmenu,i);
      result = menu_find_item_pos(submenu,item_id);
      if (result != 0) {
        i = item_count + 1;
      }
    }
    else {
      sub_id = GetMenuItemID(hmenu,i);
      if (item_id == sub_id) {
        result = (i + 1) * 0x10000 | err_report_ctx_block.menu_search_pos - 1U;
        i = item_count + 1;
      }
    }
  }
  return result;
}

/* 005ecf50 auto */
void __thiscall wnd_call_mousemove(WndOnMouseMoveView *self,i32 x,i32 y)

{
  if (self->on_mousemove != 0) {
    call_untyped((code *)self->on_mousemove, x,y);
  }
  return;
}

/* 005ecf90 auto */
void __thiscall wnd_call_lbuttondown(WndOnLButtonDownView *self,iptr x,iptr y)

{
  if (self->on_lbuttondown != 0) {
    call_untyped((code *)self->on_lbuttondown, x,y);
  }
  return;
}

/* 005ecfd0 auto */
void __thiscall wnd_call_lbuttonup_raw(WndOnLButtonUpRawView *self,iptr x,iptr y)

{
  if (self->on_lbuttonup_raw != 0) {
    call_untyped((code *)self->on_lbuttonup_raw, x,y);
  }
  return;
}

/* 005ed010 auto */
void __thiscall wnd_call_lbuttonup(WndOnLButtonUpView *self,i32 x,i32 y)

{
  if (self->on_lbuttonup != 0) {
    call_untyped((code *)self->on_lbuttonup, x,y);
  }
  return;
}

/* 005ed050 auto */
void __thiscall wnd_call_rbuttondown(WndOnRButtonDownView *self,iptr x,iptr y)

{
  if (self->on_rbuttondown != 0) {
    call_untyped((code *)self->on_rbuttondown, x,y);
  }
  return;
}

/* 005ed090 auto */
void __thiscall wnd_call_rbuttonup_raw(WndOnRButtonUpRawView *self,i32 x,i32 y)

{
  if (self->on_rbuttonup_raw != 0) {
    call_untyped((code *)self->on_rbuttonup_raw, x,y);
  }
  return;
}

/* 005ed0d0 auto */
void __thiscall wnd_call_rbuttonup(WndOnRButtonUpView *self,i32 x,i32 y)

{
  if (self->on_rbuttonup != 0) {
    call_untyped((code *)self->on_rbuttonup, x,y);
  }
  return;
}

/* 005ed110 auto */
void __thiscall wnd_call_dblclick(WndOnDblClickView *self,i32 x,i32 y)

{
  if (self->on_dblclick != 0) {
    call_untyped((code *)self->on_dblclick, x,y);
  }
  return;
}

/* 005ed150 auto */
void __thiscall wnd_call_keydown_pre(WndOnKeyDownPreView *self,i32 key)

{
  if (self->on_keydown_pre != 0) {
    call_untyped((code *)self->on_keydown_pre, key);
  }
  return;
}

/* 005ed190 auto */
void __thiscall wnd_call_keyup(WndOnKeyUpView *self,i32 key)

{
  if (self->on_keyup != 0) {
    call_untyped((code *)self->on_keyup, key);
  }
  return;
}

/* 005ed1d0 auto */
void __thiscall wnd_call_keydown(WndOnKeyDownView *self,i32 key)

{
  if (self->on_keydown != 0) {
    call_untyped((code *)self->on_keydown, key);
  }
  return;
}

/* 005ed210 auto */
void __thiscall wnd_call_char(WndOnCharView *self,i32 ch)

{
  if (self->on_char != 0) {
    call_untyped((code *)self->on_char, ch);
  }
  return;
}

/* 005ed250 auto */
i32 __thiscall wnd_call_close(WndOnCloseView *self)

{
  i32 result;
  
  if (self->on_close == 0) {
    result = 0;
  }
  else {
    result = call_untyped((code *)self->on_close);
  }
  return result;
}

/* 005ed290 auto */
void __thiscall wnd_call_minimize(WndOnMinimizeView *self)

{
  if (self->on_minimize != 0) {
    call_untyped((code *)self->on_minimize);
  }
  return;
}

/* 005ed2c0 auto */
void __thiscall wnd_call_restore(WndOnRestoreView *self)

{
  if (self->on_restore != 0) {
    call_untyped((code *)self->on_restore);
  }
  return;
}

/* 005ed2f0 auto */
void __thiscall wnd_call_setfocus(WndOnSetFocusView *self)

{
  if (self->on_setfocus != 0) {
    call_untyped((code *)self->on_setfocus);
  }
  return;
}

/* 005ed320 auto */
void __thiscall wnd_call_size(WndOnSizeView *self,i32 size_type)

{
  if (self->on_size != 0) {
    call_untyped((code *)self->on_size, size_type);
  }
  return;
}

/* 005ed360 auto */
void __thiscall wnd_call_move(WndOnMoveView *self,i32 x,i32 y)

{
  if (self->on_move != 0) {
    call_untyped((code *)self->on_move, x,y);
  }
  return;
}

/* 005ed3a0 auto */
void __thiscall wnd_call_msg44(WndOnMsg44View *self,iptr notify_arg)

{
  if (self->on_commnotify != 0) {
    call_untyped((code *)self->on_commnotify, notify_arg);
  }
  return;
}

/* 005ed3e0 auto */
void __thiscall wnd_call_hscroll(WndOnHScrollView *self,i32 scroll_pos)

{
  if (self->on_hscroll != 0) {
    call_untyped((code *)self->on_hscroll, scroll_pos);
  }
  return;
}

/* 005ed420 auto */
void __thiscall wnd_call_hscroll_track(WndOnHScrollTrackView *self,i32 scroll_pos)

{
  if (self->on_hscroll_track != 0) {
    call_untyped((code *)self->on_hscroll_track, scroll_pos);
  }
  return;
}

/* 005ed460 auto */
void __thiscall wnd_call_vscroll(WndOnVScrollView *self,i32 scroll_pos)

{
  if (self->on_vscroll != 0) {
    call_untyped((code *)self->on_vscroll, scroll_pos);
  }
  return;
}

/* 005ed4a0 auto */
void __thiscall wnd_call_vscroll_track(WndOnVScrollTrackView *self,i32 scroll_pos)

{
  if (self->on_vscroll_track != 0) {
    call_untyped((code *)self->on_vscroll_track, scroll_pos);
  }
  return;
}

/* 005ed4e0 auto */
void __thiscall wnd_call_msg4c8(WndCallMsg4c8View *self,i32 msg_arg)

{
  if (self->on_msg_4c8 != 0) {
    call_untyped((code *)self->on_msg_4c8, msg_arg);
  }
  return;
}

/* 005ed520 auto */
void __thiscall wnd_call_entersizemove(WndOnEnterSizeMoveView *self)

{
  if (self->on_entersizemove != 0) {
    call_untyped((code *)self->on_entersizemove);
  }
  return;
}

/* 005ed550 auto */
void __thiscall wnd_call_exitsizemove(WndOnExitSizeMoveView *self)

{
  if (self->on_exitsizemove != 0) {
    call_untyped((code *)self->on_exitsizemove);
  }
  return;
}

/* 005ed580 auto */
void __thiscall wnd_on_size_nop(void *self,i32 width,i32 height)

{
  return;
}

/* 005ed5a0 auto */
bool __thiscall wnd_call_menu_pos_command(WndOnMenuPosCommandView *self,i32 menu_pos,i32 item_pos)

{
  bool has_handler;
  
  has_handler = self->on_menu_pos_command != 0;
  if (has_handler) {
    call_untyped((code *)self->on_menu_pos_command, menu_pos,item_pos);
  }
  return has_handler;
}

/* 005ed5f0 auto */
bool __thiscall wnd_call_command(WndOnCommandView *self,i32 cmd_id)

{
  bool has_handler;
  
  has_handler = self->on_command != 0;
  if (has_handler) {
    call_untyped((code *)self->on_command, cmd_id);
  }
  return has_handler;
}

/* 005ed640 auto */
/* Library Function - Single Match
    public: int __thiscall CSplitterWnd::IsTracking(void)
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall wnd_get_hscroll_pos(WndHScrollPosView *self)

{
  return self->hscroll_pos;
}

/* 005ed660 auto */
/* Library Function - Single Match
    public: int __thiscall CSplitterWnd::IsTracking(void)
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall wnd_get_vscroll_pos(WndVScrollPosView *self)

{
  return self->vscroll_pos;
}

/* 005ed680 auto */
/* Library Function - Single Match
    public: int __thiscall CSplitterWnd::IsTracking(void)
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall wnd_get_hscroll_page(WndHScrollPageView *self)

{
  return self->hscroll_page;
}

/* 005ed6a0 auto */
/* Library Function - Single Match
    public: int __thiscall CSplitterWnd::IsTracking(void)
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall wnd_get_vscroll_page(WndVScrollPageView *self)

{
  return self->vscroll_page;
}

/* 005ed6c0 auto */
/* Library Function - Single Match
    public: int __thiscall CSplitterWnd::IsTracking(void)
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall wnd_get_mci_device(WndMciDeviceView *self)

{
  return self->mci_device;
}

/* 005ed6e0 auto */
void __thiscall wnd_call_mci_done(WndOnMciDoneView *self)

{
  if (self->on_mci_done != 0) {
    call_untyped((code *)self->on_mci_done);
  }
  return;
}

/* 005ef5db auto */
i32 __cdecl ddwin_destroy_native(i32 *ddwin)

{
  i32 mem_handle;
  
  if (ddwin != (i32 *)0x0) {
    if (ddwin[5] == 0) {
      if (ddwin[1] != 0) {
        ShowWindow((HWND)ddwin[1],0);
        DestroyWindow((HWND)ddwin[1]);
      }
      ddwin[1] = 0;
    }
    mem_handle = *ddwin;
    mem_handle_unlock(mem_handle);
    mem_handle_free(mem_handle);
  }
  return 0;
}

/* 005ef6cb auto */
LRESULT __stdcall ddwin_native_wndproc(HWND hwnd,uint msg,uint wparam,uint lparam)

{
  char handled;
  DDWindow *self;
  LRESULT def_result;
  i32 key;
  int can_close;
  uptr wnd_obj;
  i32 zero_arg;
  
  self = (DDWindow *)GetClassLongA(hwnd,4);
  if (self == (DDWindow *)0x0) {
    def_result = DefWindowProcA(hwnd,msg,wparam,lparam);
    return def_result;
  }
  if (msg < 0x11) {
    if (msg != 0x10) {
      if (msg == 2) {
        wnd_obj = GetClassLongA(hwnd,0);
        *(i32 *)(wnd_obj + 0x14) = 1;
        def_result = DefWindowProcA(hwnd,2,wparam,lparam);
        return def_result;
      }
      goto default_proc;
    }
    can_close = wnd_call_close((WndOnCloseView *)self->handlers);
    if (can_close != 0) {
      def_result = DefWindowProcA(hwnd,0x10,wparam,lparam);
      return def_result;
    }
  }
  else if (msg < 0x45) {
    if (msg != 0x44) {
      if (msg != 0x1c) goto default_proc;
      if (wparam != ddwin_last_activate_app) {
        ddwin_call_activate_app((DDWindowActivateView *)self,wparam);
        ddwin_last_activate_app = wparam;
      }
    }
  }
  else if (msg < 0x201) {
    if (msg == 0x200) {
      handled = ddwin_dispatch_ctrl_msg(self,0x200,lparam & 0xffff,lparam >> 0x10);
      if (handled == '\0') {
        wnd_call_mousemove
                  ((WndOnMouseMoveView *)self->handlers,lparam & 0xffff,lparam >> 0x10);
      }
    }
    else if (msg == 0x100) {
      zero_arg = 0;
      key = input_map_vkey(wparam);
      handled = ddwin_dispatch_ctrl_msg(self,0x100,key,zero_arg);
      if (handled == '\0') {
        key = input_map_vkey(wparam);
        wnd_call_keydown_pre((WndOnKeyDownPreView *)self->handlers,key);
        key = input_map_vkey(wparam);
        wnd_call_keydown((WndOnKeyDownView *)self->handlers,key);
      }
    }
    else if (msg == 0x101) {
      key = input_map_vkey(wparam);
      wnd_call_keyup((WndOnKeyUpView *)self->handlers,key);
    }
    else {
      if (msg != 0x102) goto default_proc;
      handled = ddwin_dispatch_ctrl_msg(self,0x102,wparam & 0xff,0);
      if (handled == '\0') {
        wnd_call_char((WndOnCharView *)self->handlers,wparam & 0xff);
      }
    }
  }
  else if (msg < 0x211) {
    if (msg == 0x210) {
      if ((wparam & 0xffff) == 0x201) {
        wnd_call_lbuttondown
                  ((WndOnLButtonDownView *)self->handlers,lparam & 0xffff,lparam >> 0x10);
      }
      else if ((wparam & 0xffff) == 0x204) {
        wnd_call_rbuttondown
                  ((WndOnRButtonDownView *)self->handlers,lparam & 0xffff,lparam >> 0x10);
      }
    }
    else {
      switch(msg) {
      case 0x201:
        handled = ddwin_dispatch_ctrl_msg(self,msg,lparam & 0xffff,lparam >> 0x10);
        if (handled == '\0') {
          ((DDWindowExt *)self)->lbutton_held[0] = 1;
          ((DDWindowExt *)self)->lbutton_held_byte1[0] = '\0';
          ((DDWindowExt *)self)->lbutton_held_byte2[0] = '\0';
          ((DDWindowExt *)self)->lbutton_held_byte3[0] = '\0';
          wnd_call_lbuttondown
                    ((WndOnLButtonDownView *)self->handlers,lparam & 0xffff,lparam >> 0x10);
        }
        break;
      case 0x202:
        handled = ddwin_dispatch_ctrl_msg(self,msg,lparam & 0xffff,lparam >> 0x10);
        if (handled == '\0') {
          if (*(int *)((DDWindowExt *)self)->lbutton_held == 1) {
            ((DDWindowExt *)self)->lbutton_held[0] = '\0';
            ((DDWindowExt *)self)->lbutton_held_byte1[0] = '\0';
            ((DDWindowExt *)self)->lbutton_held_byte2[0] = '\0';
            ((DDWindowExt *)self)->lbutton_held_byte3[0] = '\0';
            wnd_call_lbuttonup
                      ((WndOnLButtonUpView *)self->handlers,lparam & 0xffff,lparam >> 0x10);
          }
          wnd_call_lbuttonup_raw
                    ((WndOnLButtonUpRawView *)self->handlers,lparam & 0xffff,lparam >> 0x10);
        }
        break;
      case 0x203:
        handled = ddwin_dispatch_ctrl_msg(self,msg,lparam & 0xffff,lparam >> 0x10);
        if (handled == '\0') {
          wnd_call_dblclick
                    ((WndOnDblClickView *)self->handlers,lparam & 0xffff,lparam >> 0x10);
        }
        break;
      case 0x204:
        handled = ddwin_dispatch_ctrl_msg(self,msg,lparam & 0xffff,lparam >> 0x10);
        if (handled == '\0') {
          ((DDWindowExt *)self)->rbutton_held[0] = 1;
          ((DDWindowExt *)self)->rbutton_held_byte1[0] = '\0';
          ((DDWindowExt *)self)->rbutton_held_byte2[0] = '\0';
          ((DDWindowExt *)self)->rbutton_held_byte3[0] = '\0';
          wnd_call_rbuttondown
                    ((WndOnRButtonDownView *)self->handlers,lparam & 0xffff,lparam >> 0x10);
        }
        break;
      case 0x205:
        handled = ddwin_dispatch_ctrl_msg(self,msg,lparam & 0xffff,lparam >> 0x10);
        if (handled == '\0') {
          if (*(int *)(((DDWindowExt *)self)->rbutton_held) == 1) {
            ((DDWindowExt *)self)->rbutton_held[0] = '\0';
            ((DDWindowExt *)self)->rbutton_held_byte1[0] = '\0';
            ((DDWindowExt *)self)->rbutton_held_byte2[0] = '\0';
            ((DDWindowExt *)self)->rbutton_held_byte3[0] = '\0';
            wnd_call_rbuttonup
                      ((WndOnRButtonUpView *)self->handlers,lparam & 0xffff,lparam >> 0x10);
          }
          wnd_call_rbuttonup_raw
                    ((WndOnRButtonUpRawView *)self->handlers,lparam & 0xffff,lparam >> 0x10);
        }
        break;
      default:
        goto default_proc;
      }
    }
  }
  else {
    if (msg != 0x4c8) {
default_proc:
      def_result = DefWindowProcA(hwnd,msg,wparam,lparam);
      return def_result;
    }
    if (lparam == 0x20d) {
      wnd_call_msg4c8((WndCallMsg4c8View *)self->handlers,0);
    }
  }
  return 0;
}

/* 005efd70 auto */
void __thiscall ddwin_call_activate_app(DDWindowActivateView *self,i32 active)

{
  if (self->on_activate_app != 0) {
    call_untyped((code *)self->on_activate_app, active);
  }
  return;
}

/* 005efeb0: written by hand in src/game/unwind.cpp */

/* 005f029e auto */
void __thiscall ddwin_remove_all_controls(DDWindow *self)

{
  i32 ctrl;
  
  ctrl = ptrlist_first((PtrList *)self->child_controls);
  while (ctrl != 0) {
    ptrlist_remove_current((PtrList *)self->child_controls);
    ctrl = ptrlist_first((PtrList *)self->child_controls);
  }
  return;
}

/* 005f0342 auto */
void __thiscall ddwin_deactivate_controls(DDWindow *self)

{
  i32 ctrl;
  
  ctrl = ptrlist_first((PtrList *)self->child_controls);
  while (ctrl != 0) {
    ddctrl_deactivate((DDControl *)ctrl);
    ctrl = ptrlist_next((PtrList *)self->child_controls);
  }
  return;
}

/* 005f0391 auto */
i8 __thiscall ddwin_dispatch_ctrl_msg(DDWindow *self,int msg,int x,int y)

{
  int *rect;
  int handled;
  DDControl *ctrl;
  
  if ((self->hover_control != 0) && (msg == 0x200)) {
    rect = (int *)ddctrl_get_rect((DDControl *)self->hover_control);
    if ((x < *rect) ||
       (((rect[2] < x || (y < rect[1])) || (rect[3] < y)))) {
      ddctrl_dispatch_msg((DDControl *)self->hover_control,0xfff0,x,y);
      self->hover_control = 0;
    }
  }
  ctrl = (DDControl *)ptrlist_first((PtrList *)self->child_controls);
  while( true ) {
    if (ctrl == (DDControl *)0x0) {
      return 0;
    }
    handled = ddctrl_dispatch_msg(ctrl,msg,x,y);
    if (handled != 0) break;
    ctrl = (DDControl *)ptrlist_next((PtrList *)self->child_controls);
  }
  if (msg == 0x200) {
    self->hover_control = (uptr)ctrl;
  }
  return 1;
}
