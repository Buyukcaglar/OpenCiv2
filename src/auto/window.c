/* The game, windows, dialogs and menus: functions translated from the original
 * (tools/gen_c.py, now edited directly), in address order. */
#include "auto_common.h"

/* 00408010 auto */
void __thiscall wnd_set_cursor(WndBase *this,i32 cursor)

{
  wnd_obj_set_cursor(this->native_wnd,cursor);
  return;
}

/* 00408050 auto */
void __thiscall wnd_set_icon(WndBase *this,i32 icon)

{
  wnd_obj_set_icon(this->native_wnd,icon);
  return;
}

/* 00408090 auto */
void __thiscall wnd_minimize(WndBase *this)

{
  wnd_obj_minimize(this->native_wnd);
  return;
}

/* 004080c0 auto */
i32 __thiscall wnd_client_width(WndBase *this)

{
  i32 width;
  
  width = wnd_obj_client_width(this->native_wnd);
  return width;
}

/* 004080f0 auto */
void __thiscall wnd_get_rect_in_parent(WndBase *this,iptr rect)

{
  wnd_obj_get_rect_in_parent(this->native_wnd,rect);
  return;
}

/* 00408130 auto */
u32 __thiscall wnd_set_lbuttonup_handler(WndEventHandlers *this,iptr handler)

{
  u32 old_handler;
  
  old_handler = this->on_lbuttonup;
  this->on_lbuttonup = handler;
  return old_handler;
}

/* 00408170 auto */
u32 __thiscall wnd_set_rbuttonup_handler(WndEventHandlers *this,iptr handler)

{
  u32 old_handler;
  
  old_handler = this->on_rbuttonup;
  this->on_rbuttonup = handler;
  return old_handler;
}

/* 004081b0 auto */
/* Library Function - Single Match
    public: virtual int __thiscall COleControlSite::SetDlgCtrlID(int)
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall wnd_set_keydown_handler(WndEventHandlers *this,iptr handler)

{
  u32 old_handler;
  
  old_handler = this->on_keydown;
  this->on_keydown = handler;
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

u32 __thiscall wnd_set_char_handler(WndEventHandlers *this,iptr handler)

{
  u32 old_handler;
  
  old_handler = this->on_char;
  this->on_char = handler;
  return old_handler;
}

/* 00408230 auto */
u32 __thiscall wnd_set_close_handler(WndEventHandlers *this,iptr handler)

{
  u32 old_handler;
  
  old_handler = this->on_close;
  this->on_close = handler;
  return old_handler;
}

/* 00408270 auto */
u32 __thiscall wnd_set_minimize_handler(WndEventHandlers *this,iptr handler)

{
  u32 old_handler;
  
  old_handler = this->on_minimize;
  this->on_minimize = handler;
  return old_handler;
}

/* 004082b0 auto */
u32 __thiscall wnd_set_restore_handler(WndEventHandlers *this,iptr handler)

{
  u32 old_handler;
  
  old_handler = this->on_restore;
  this->on_restore = handler;
  return old_handler;
}

/* 004082f0 auto */
u32 __thiscall wnd_set_size_handler(WndEventHandlers *this,iptr handler)

{
  u32 old_handler;
  
  old_handler = this->on_size;
  this->on_size = handler;
  return old_handler;
}

/* 00408330 auto */
u32 __thiscall wnd_set_move_handler(WndEventHandlers *this,iptr handler)

{
  u32 old_handler;
  
  old_handler = this->on_move;
  this->on_move = handler;
  return old_handler;
}

/* 00408370 auto */
void __thiscall wnd_set_min_size(ModalMenuWindow *this,u32 width,u32 height)

{
  this->min_width = width;
  this->min_height = height;
  return;
}

/* 004083b0 auto */
void __thiscall wnd_destroy_with_surface(DibSurface *this)

{
  wnd_destroy_native((WndBase *)(this + 1));
  surface_release(this);
  return;
}

/* 00408420 auto */
void __thiscall wnd_destroy_native(WndBase *this)

{
  u32 native;
  
  native = wnd_obj_destroy(this->native_wnd);
  this->native_wnd = native;
  return;
}

/* 00408460 auto */
void __thiscall wnd_blit_surface(DibSurface *this)

{
  wnd_blit_surface_rect(this,0);
  return;
}

/* 00408490 auto */
#define view (*(DibSurface * *)(frame_ + FRAME_OFF(4)))
#define view2 (*(DibSurface * *)(frame_ + FRAME_OFF(8)))
void __thiscall wnd_blit_surface_rect(DibSurface *this,iptr rect)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (rect == 0) {
    if (this == (DibSurface *)0x0) {
      view = (DibSurface *)0x0;
    }
    else {
      view = this + 1;
    }
    surface_blit_to_wnd(this,(iptr)view,(iptr)&this->bounds_rect,(iptr)&this->bounds_rect);
    wnd_view_validate_rect((WndValidateRectView *)(this + 1),(iptr)&this->bounds_rect);
  }
  else {
    if (this == (DibSurface *)0x0) {
      view2 = (DibSurface *)0x0;
    }
    else {
      view2 = this + 1;
    }
    surface_blit_to_wnd(this,(iptr)view2,rect,rect);
    wnd_view_validate_rect((WndValidateRectView *)(this + 1),rect);
  }
  return;
}
#undef view
#undef view2

/* 00408580 auto */
void __thiscall wnd_view_validate_rect(WndValidateRectView *this,iptr rect)

{
  wnd_obj_validate_rect(this->wnd_obj,rect);
  return;
}

/* 004085c0 auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall wnd_set_redraw_callback(SurfaceWindow *this,iptr callback)

{
  this->on_paint = callback;
  return;
}

/* 004085f0 auto */
void __thiscall window_show(WindowObjectView *this)

{
  window_show_focus_first((Wnd *)(this + 0x12));
  return;
}

/* 00408620 auto */
void __thiscall window_show_focus_first(Wnd *this)

{
  wnd_handle_show_raise((WndBase *)this);
  wnd_focus_first_control(this);
  return;
}

/* 00408650 auto */
void __thiscall wnd_handle_show_raise(WndBase *this)

{
  wnd_obj_show_raise(this->native_wnd);
  return;
}

/* 0040894c auto */
void __cdecl ui_pump_messages_net(void)

{
  win_flush_pending_msgs();
  if (2 < game.multiplayer) {
    net_process_messages((NetSession *)&net_session,1,0);
  }
  return;
}

/* 0040bc40 auto */
void __thiscall dlg_reset(Dialog *this,i32 flags)

{
  dialog_init(this,0,0,0,flags);
  return;
}

/* 0040bc80 auto */
i32 __thiscall dlg_show_modal(Dialog *this,iptr parent)

{
  i32 result;
  
  result = dialog_run_modal(this,0,parent);
  return result;
}

/* 0040e017 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
#define civ_byte (*(byte *)(frame_ + FRAME_OFF(4)))
#define city (*(iptr *)(frame_ + FRAME_OFF(8)))
#define count (*(int *)(frame_ + FRAME_OFF(16)))
#define dialog2 (*(Dialog *)(frame_ + FRAME_OFF(24)))
#define civ (*(int *)(frame_ + FRAME_OFF(780)))
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(784)))
#define seh_scope (*(i8 * *)(frame_ + FRAME_OFF(788)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(792)))
void __cdecl menu_find_city(void)

{
  bool visible;
  iptr adjective;
  iptr objective;
  iptr city2;
  iptr civ2;
  i8 frame_[FRAME_OFF(800)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  dialog_ctor(&dialog2,0x4000);
  civ2 = human_civ;
  eh_state = 0;
  count = 0;
  dlg_load_game_section(&dialog2,(iptr)((u8 *)&g.d_00624f24),0x800001);
  for (city = 0; city < game.num_cities; city++) {
    if (cities[city].id != 0) {
      visible = false;
      civ = (int)cities[city].owner;
      if ((game.reveal_map != '\0') ||
         (((game.game_flags & 0x80) != 0 && ((scenario_flags & 8) != 0)))) {
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
        text_append(city * 0x58 + (iptr)((u8 *)&cities + 32));
        if (civ != civ2) {
          text_append_space();
          text_append_lparen();
          adjective = civ_adjective(civ);
          text_append(adjective);
          text_append_rparen();
        }
        if ((((game.game_flags & 0x80) != 0) && ((scenario_flags & 2) != 0)) &&
           (objective = city_objective_value(city), objective != 0)) {
          text_append_space();
          text_append_lparen();
          text_append_label(0x1b0);
          if (1 < objective) {
            text_append((iptr)((u8 *)&g.d_00624f30));
            text_append_int(objective);
          }
          text_append_rparen();
        }
        dialog_add_option((DialogOptionList *)&dialog2,(iptr)((u8 *)&g.d_00679640),city,0);
        count++;
      }
    }
  }
  if (count == 0) {
    eh_state = 0xffffffff;
    /* inlined unwind funclet 0040e38d */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
  }
  else {
    city2 = dlg_show_modal(&dialog2,0);
    if (city2 < 0) {
      eh_state = 0xffffffff;
      /* inlined unwind funclet 0040e38d */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
    }
    else {
      mapview_center_on
                ((ViewWindow *)&map_views,(int)cities[city2].x,(int)cities[city2].y);
      if ((dialog2.result_extra != 0) && ((cities[city2].owner == civ2 || (game.reveal_map != '\0')))
         ) {
        city_window_open((ScaledWindowView *)&city_window,city2);
      }
      eh_state = 0xffffffff;
      /* inlined unwind funclet 0040e38d */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
    }
  }
  return;
}
#undef human_civ
#undef scenario_flags
#undef civ_byte
#undef city
#undef count
#undef dialog2
#undef civ
#undef seh_handler
#undef seh_scope
#undef eh_state

/* 0040e3b1 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
#define ui_large_screen (*(int *)((u8 *)&g.d_00633584))
void __cdecl menu_revolution(void)

{
  iptr text;
  int choice;
  iptr civ;
  
  civ = human_civ;
  if (((game.game_flags & 0x80) == 0) || ((scenario_flags & 0x10) == 0)) {
    if ((civs[human_civ].flags & 8) == 0) {
      if (civs[human_civ].government != '\0') {
        text = civ_get_adjective(human_civ);
        text_set_string_arg(0,text);
        text_set_label_arg(1,government_names[civs[civ].government]);
        choice = popup_game_with_sprite((iptr)((u8 *)&g.d_00624f34),(iptr)(&government_sprites +
                                                  (uint)civs[civ].government * 0x3c),
                                   (ui_large_screen == 0) - 1 & 8);
        if (choice == 0) {
          snd_play_effect(0x3e,1,0,0);
          text = civ_name_plural(civ);
          text_set_string_arg(0,text);
          popup_game_with_sprite((iptr)((u8 *)&g.d_00624f40),(iptr)((u8 *)&g.d_0063fc58),0);
          civ_set_government(civ,0);
          menu_update_states();
        }
      }
    }
    else {
      civ_change_government(human_civ,1);
    }
  }
  return;
}
#undef human_civ
#undef scenario_flags
#undef ui_large_screen

/* 0040f320 auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall wnd_set_modal_idle_callback(ModalMenuWindow *this,iptr callback)

{
  this->on_modal_idle = callback;
  return;
}

/* 0040f350 auto */
void __thiscall wnd_set_keyboard_nav(Wnd *this,i32 enabled)

{
  *(i8 *)&this->keyboard_nav = (i8)enabled;
  return;
}

/* 0040ffa0 auto */
i32 __thiscall
dlg_load_game_section(Dialog *this,iptr section,i32 flags)

{
  i32 result;
  
  result = dialog_load_text_ex(this,(iptr)((u8 *)&g.d_006359d4),section,0,flags);
  return result;
}

/* 0040ffe0 auto */
i32 __thiscall
dialog_load_text_ex
          (Dialog *this,iptr filename,iptr section,i32 arg,i32 flags)

{
  i32 result;
  
  result = dialog_load_text_section(this,filename,section,arg,0,0,0,0,flags);
  return result;
}

/* 00410030 auto */
i32 __cdecl popup_game_with_sprite(iptr section,iptr sprite,i32 sprite_flags)

{
  i32 result;
  
  result = popup_text_with_sprite((iptr)((u8 *)&g.d_006359d4),section,0,sprite,sprite_flags);
  return result;
}

/* 00410e0a auto */
#define mapview_cursor_id (*(int *)((u8 *)&g.d_0066cb00))
i32 __cdecl ui_paradrop_cursor_active(void)

{
  i32 active;
  
  if ((mapview_cursor_id == 0x202) || (mapview_cursor_id == 0x203)) {
    active = 1;
  }
  else {
    active = 0;
  }
  return active;
}
#undef mapview_cursor_id

/* 00414b70 auto */
void __thiscall wnd_set_cursor_now(WndCursorView *this,iptr cursor,i32 flag)

{
  wnd_obj_set_cursor_now(this->native_wnd,cursor,flag);
  return;
}

/* 00414bb0 auto */
i32 __thiscall wnd_client_height(WndBase *this)

{
  i32 height;
  
  height = wnd_obj_client_height(this->native_wnd);
  return height;
}

/* 00414be0 auto */
u32 __thiscall wnd_set_mousemove_handler(WndHandlersMouseSetView *this,iptr handler)

{
  u32 old_handler;
  
  old_handler = this->on_mouse_move;
  this->on_mouse_move = handler;
  return old_handler;
}

/* 00414c20 auto */
u32 __thiscall wnd_set_lbuttondown_handler(WndHandlersMouseSetView *this,iptr handler)

{
  u32 old_handler;
  
  old_handler = this->on_lbutton_down;
  this->on_lbutton_down = handler;
  return old_handler;
}

/* 00414c60 auto */
u32 __thiscall wnd_set_lbuttonup_any_handler(WndHandlersMouseSetView *this,iptr handler)

{
  u32 old_handler;
  
  old_handler = ((WndHandlersMouseSetViewExt *)this)->on_lbutton_up_any;
  ((WndHandlersMouseSetViewExt *)this)->on_lbutton_up_any = handler;
  return old_handler;
}

/* 00414ca0 auto */
u32 __thiscall wnd_set_dblclick_handler(WndHandlersMouseSetView *this,iptr handler)

{
  u32 old_handler;
  
  old_handler = ((WndHandlersMouseSetViewExt *)this)->on_dblclick;
  ((WndHandlersMouseSetViewExt *)this)->on_dblclick = handler;
  return old_handler;
}

/* 00414ce0 auto */
void __thiscall wnd_set_capture(WndBase *this)

{
  iptr hwnd;
  
  hwnd = wnd_get_window(this);
  wnd_obj_set_capture(hwnd);
  return;
}

/* 00414d10 auto */
u32 __thiscall wnd_get_window(WndBase *this)

{
  return this->native_wnd;
}

/* 00414d40 auto */
void __thiscall wnd_release_capture(WndBase *this)

{
  i32 hwnd;
  
  hwnd = wnd_get_window(this);
  wnd_obj_release_capture(hwnd);
  return;
}

/* 00414da0 auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall wnd_set_caption_button_handler(FrameWindow *this,iptr handler)

{
  this->on_caption_button = handler;
  return;
}

/* 00414dd0 auto */
i32 __cdecl popup_game_with_city(iptr section,iptr city)

{
  i32 result;
  
  result = popup_text_with_city((iptr)((u8 *)&g.d_006359d4),section,0,city);
  return result;
}

/* 004190d0 auto */
i32 __cdecl popup_text(iptr filename,iptr section)

{
  i32 result;
  
  result = popup_text_flags(filename,section,0);
  return result;
}

/* 00419100 auto */
i32 __cdecl popup_text_flags(iptr filename,iptr section,i32 flags)

{
  i32 result;
  
  result = popup_text_ex(filename,section,0,flags);
  return result;
}

/* 00419130 auto */
i32 __cdecl popup_text_ex(iptr filename,iptr section,i32 dlg_flags,i32 flags)

{
  i32 result;
  
  result = popup_text_run(filename,section,dlg_flags,0,0,0,flags);
  return result;
}

/* 00419b80 auto */
void __cdecl wnd_flush_paint(void)

{
  win_dispatch_all_paints();
  return;
}

/* 00419ba0 auto */
void __thiscall wnd_set_bg_color(WndBase *this,i32 color)

{
  wnd_obj_set_bg_color(this->native_wnd,color);
  return;
}

/* 00419be0 auto */
void __thiscall wnd_set_bg_surface(WndBase *this,iptr surface)

{
  wnd_obj_set_bg_surface(this->native_wnd,surface);
  return;
}

/* 00421dd0 auto */
void __thiscall dialog_init_default(Dialog *this)

{
  dialog_init(this,0,0,0,0);
  return;
}

/* 00421e00 auto */
/* Library Function - Single Match
    public: int __thiscall CSocket::Create(unsigned int,int,char const *)
   
   Library: Visual Studio 1998 Debug */

i32 __thiscall
dialog_load_text(Dialog *this,iptr filename,iptr section,i32 flags)

{
  i32 result;
  
  result = dialog_load_text_ex(this,filename,section,0,flags);
  return result;
}

/* 00421e40 auto */
#define dlg_scale_den (*(i32 *)((u8 *)&g.d_00635a38))
#define dlg_scale_num (*(i32 *)((u8 *)&g.d_00635a34))
void __cdecl dlg_set_scale(i32 numerator,i32 denominator)

{
  dlg_scale_num = numerator;
  dlg_scale_den = denominator;
  return;
}
#undef dlg_scale_den
#undef dlg_scale_num

/* 00421e70 auto */
i32 __cdecl popup_game_flags(iptr section,i32 flags)

{
  i32 result;
  
  result = popup_text_flags((iptr)((u8 *)&g.d_006359d4),section,flags);
  return result;
}

/* 00421ea0 auto */
i32 __cdecl popup_game(iptr section)

{
  i32 result;
  
  result = popup_text((iptr)((u8 *)&g.d_006359d4),section);
  return result;
}

/* 00421ed0 auto */
i32 __cdecl dlg_game_text_input(iptr section,i32 max_len,iptr buf,iptr default_text)

{
  i32 result;
  
  result = dlg_text_input((iptr)((u8 *)&g.d_006359d4),section,max_len,buf,default_text);
  return result;
}

/* 00426f30 auto */
Dialog * __thiscall dialog_scalar_dtor(Dialog *this,uint flags)

{
  dialog_dtor(this);
  if ((flags & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 00426f80 auto */
void __thiscall wnd_maximize(WndBase *this)

{
  wnd_obj_maximize(this->native_wnd);
  return;
}

/* 00426fb0 auto */
i32 __cdecl popup_game_sprite_flags(iptr section,i32 dlg_flags,iptr sprite,i32 sprite_flags)

{
  i32 result;
  
  result = popup_text_with_sprite((iptr)((u8 *)&g.d_006359d4),section,dlg_flags,sprite,sprite_flags);
  return result;
}

/* 0042a768 auto */
void __thiscall picwnd_close(PictureWindowCore *this)

{
  if (-1 < (int)this->report_id) {
    this->report_id = 0xffffffff;
    wnd_remove_all_controls((WndControlRemoveView *)this->window_2);
    surface_release((DibSurface *)&this->rates_civ);
    frame_wnd_close((DibSurface *)this);
  }
  return;
}

/* 0042a7bc auto */
#define frame_border_width (*(int *)((u8 *)&g.d_0063359c))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define palette (*(GamePalette *)(frame_ + FRAME_OFF(4)))
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(1080)))
#define seh_scope (*(i8 * *)(frame_ + FRAME_OFF(1084)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(1088)))
void __thiscall
picwnd_open
          (PictureWindow *this,uint resource_id,u32 report,u32 style,u32 img_width,u32 img_height,
          u32 win_width,u32 win_height)

{
  u32 wnd_h;
  int border;
  int scr_height;
  u32 wnd_w;
  int nonclient_height;
  i8 frame_[FRAME_OFF(1096)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  palette_init(&palette);
  eh_state = 0;
  picwnd_close((PictureWindowCore *)&advisor_window);
  ui_set_button_font((iptr)((u8 *)&g.d_0063eaa0));
  this->controls_created = 0;
  this->frame_state = 0;
  this->page_count = 1;
  this->first_row = 0;
  this->report_civ = 1;
  this->report_param = 0;
  this->report_id = report;
  this->frame_style = style;
  wnd_w = GetSystemMetrics(2);
  this->vscroll_width = wnd_w;
  border = frame_border_width;
  if ((int)resource_id < 0) {
    resource_id = ~resource_id + 1;
  }
  else if (resource_id != 10000) {
    resource_id += 0x31;
  }
  this->image_width = img_width;
  this->image_height = img_height;
  win_flush_pending_msgs();
  if (resource_id == 10000) {
    surface_load_gif_file((DibSurface *)&this->rates_civ,(iptr)((u8 *)&g.d_00625ee0),10,0xc0,(iptr)&palette)
    ;
  }
  else {
    surface_load_gif_resource((DibSurface *)&this->rates_civ,resource_id,10,0xc0,(iptr)&palette);
  }
  win_flush_pending_msgs();
  if ((int)img_width < 1) {
    wnd_w = surface_width((DibSurface *)&this->rates_civ);
    this->image_width = wnd_w;
  }
  if ((int)img_height < 1) {
    wnd_w = surface_height((DibSurface *)&this->rates_civ);
    this->image_height = wnd_w;
  }
  this->window_width = win_width;
  this->window_height = win_height;
  if (this->window_width == 0) {
    this->window_width = this->image_width;
  }
  if ((int)this->window_width < 0) {
    this->window_width = this->image_width - this->window_width;
  }
  if (this->window_height == 0) {
    this->window_height = this->image_height;
  }
  if ((int)this->window_height < 0) {
    this->window_height = this->image_height - this->window_height;
  }
  scr_height = screen_height;
  wnd_w = this->window_width;
  wnd_h = this->window_height;
  nonclient_height = wnd_nonclient_height((WndBase *)&main_frame_wnd);
  frame_wnd_create
            ((FrameWindow *)this,0,(this->frame_style == 0) - 1 & 8,
             (screen_width >> 1) - ((int)(wnd_w + border * 2) >> 1),
             (scr_height - nonclient_height >> 1) - ((int)(wnd_h + border * 2) >> 1),this->image_width,this->image_height,
             0,border,border);
  eh_state = 0xffffffff;
  /* inlined unwind funclet 0042ab9b */ { palette_destroy((GamePalette *)((iptr)&palette)); }
  return;
}
#undef frame_border_width
#undef screen_height
#undef palette
#undef seh_handler
#undef seh_scope
#undef eh_state

/* 0042abc1 auto */
void __thiscall
picwnd_blit_at
          (FrameWindow *this,int x,int y,i32 width,i32 height)

{
  gfx_copy_rect_xywh((iptr)&this->rates_civ,(iptr)this,x,y,this->client_x + x,
                     this->client_y + y,width,height);
  return;
}

/* 0042ac18 auto */
void __thiscall picwnd_blit(PictureWindow *this)

{
  picwnd_blit_at((FrameWindow *)this,0,0,this->image_width,this->image_height);
  return;
}

/* 0043c110 auto */
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_scope (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define eh_state (*(int *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    public: __thiscall CDaoFieldInfo::~CDaoFieldInfo(void)
   
   Library: Visual Studio 1998 Debug */

void __thiscall picwnd_dtor(void *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  (*(i32 *)((char *)&eh_state + 1)) = 0;
  (*(i8 *)((char *)&eh_state + 0)) = 5;
  /* inlined unwind funclet 0043c19c */ { scrollbar_dtor((Control *)(*(int *)((iptr)&this) + 0x410)); }
  (*(i8 *)((char *)&eh_state + 0)) = 4;
  /* inlined unwind funclet 0043c1ab */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x3d4)); }
  (*(i8 *)((char *)&eh_state + 0)) = 3;
  /* inlined unwind funclet 0043c1ba */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x398)); }
  (*(i8 *)((char *)&eh_state + 0)) = 2;
  /* inlined unwind funclet 0043c1c9 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x35c)); }
  (*(i8 *)((char *)&eh_state + 0)) = 1;
  /* inlined unwind funclet 0043c1d8 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 800)); }
  eh_state = (uint)(*(i32 *)((char *)&eh_state + 1)) << 8;
  /* inlined unwind funclet 0043c1e7 */ { surface_dtor((DibSurface *)(*(int *)((iptr)&this) + 0x2d8)); }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 0043c1f6 */ { frame_wnd_dtor(*(DibSurface **)((iptr)&this)); }
  return;
}
#undef seh_handler
#undef seh_scope
#undef eh_state

/* 0043c260 auto */
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_scope (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
ViewWindow * __thiscall picwnd_ctor(ViewWindow *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  frame_wnd_ctor((SurfaceWindow *)this);
  eh_state = 0;
  surface_ctor((DibSurface *)&this->rates_civ);
  (*(i8 *)((char *)&eh_state + 0)) = 1;
  button_ctor((Control *)&this->bar_height);
  (*(i8 *)((char *)&eh_state + 0)) = 2;
  button_ctor((Control *)&this->no_thanks_button_value);
  (*(i8 *)((char *)&eh_state + 0)) = 3;
  button_ctor((Control *)(this->lux_rate_scrollbar));
  (*(i8 *)((char *)&eh_state + 0)) = 4;
  button_ctor((Control *)(this->picwnd_extra_button));
  eh_state = CONCAT31((*(i32 *)((char *)&eh_state + 1)),5);
  scrollbar_ctor((Control *)(this->picwnd_scrollbar));
  this->vtable = (u32)&PTR_FUN_0061c05c;
  return this;
}
#undef seh_handler
#undef seh_scope
#undef eh_state

/* 0043c5c0 auto */
i32 __thiscall wnd_nonclient_height(WndBase *this)

{
  i32 height;
  
  height = wnd_obj_frame_height(this->native_wnd);
  return height;
}

/* 0043c630 auto */
void __thiscall wnd_disable(WndBase *this)

{
  wnd_obj_enable(this->native_wnd,0);
  return;
}

/* 0043c660 auto */
void __thiscall wnd_enable(WndBase *this)

{
  wnd_obj_enable(this->native_wnd,1);
  return;
}

/* 0043c990 auto */
void __thiscall dialog_set_list_indent(DialogCore *this,uptr indent,iptr index)

{
  (&((DialogWindowView *)this)->list_indents)[index] = indent;
  return;
}

/* 0043c9d0 auto */
void __thiscall dialog_load_game_text(Dialog *this,iptr section)

{
  dialog_load_text_noflags(this,(iptr)((u8 *)&g.d_006359d4),section);
  return;
}

/* 0043ca10 auto */
void __thiscall dialog_load_text_noflags(Dialog *this,iptr filename,iptr section)

{
  dialog_load_text(this,filename,section,0);
  return;
}

/* 00444270 auto */
i32 __cdecl popup_debug_text(iptr section)

{
  i32 result;
  
  result = popup_text((iptr)((u8 *)&g.d_006359dc),section);
  return result;
}

/* 004442a0 auto */
i32 __cdecl dlg_game_txt_with_unit_flags(iptr section,iptr unit,i32 flags)

{
  i32 result;
  
  result = popup_text_with_unit_sprite((iptr)((u8 *)&g.d_006359d4),section,0,unit,flags);
  return result;
}

/* 004442e0 auto */
i32 __cdecl dlg_game_txt_with_unit(iptr section,iptr unit)

{
  i32 result;
  
  result = popup_text_with_unit((iptr)((u8 *)&g.d_006359d4),section,0,unit);
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
  sprite_init((Sprite *)&caption_close_button_sprite);
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
  sprite_destroy((Sprite *)&caption_close_button_sprite);
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
  sprite_init((Sprite *)&caption_zoom_out_sprite);
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
  sprite_destroy((Sprite *)&caption_zoom_out_sprite);
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
  sprite_init((Sprite *)&caption_zoom_out_button_sprite);
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
  sprite_destroy((Sprite *)&caption_zoom_out_button_sprite);
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
  sprite_init((Sprite *)&caption_view_mode_button_sprite);
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
  sprite_destroy((Sprite *)&caption_view_mode_button_sprite);
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
  sprite_init((Sprite *)&scroll_up_button_sprite);
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
  sprite_destroy((Sprite *)&scroll_up_button_sprite);
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
  sprite_init((Sprite *)&popup_info_icon_sprite);
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
  sprite_destroy((Sprite *)&popup_info_icon_sprite);
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
  surface_ctor((DibSurface *)&window_border_tile_surface);
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
  surface_dtor((DibSurface *)&window_border_tile_surface);
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
  surface_ctor((DibSurface *)&panel_texture_surface);
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
  surface_dtor((DibSurface *)&panel_texture_surface);
  return;
}

/* 0044c5a0 auto */
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_scope (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
SurfaceWindow * __thiscall surfwnd_ctor(SurfaceWindow *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  surface_ctor((DibSurface *)this);
  eh_state = 0;
  surfwnd_wnd_ctor((Wnd *)this->window_2);
  this->vtable = (u32)&PTR_FUN_0061c060;
  this->handler_slot_100 = 0;
  this->on_paint = 0;
  return this;
}
#undef seh_handler
#undef seh_scope
#undef eh_state

/* 0044c670 auto */
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_scope (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
Wnd * __thiscall surfwnd_wnd_ctor(Wnd *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  wnd_ctor((ModalMenuWindow *)this);
  this->control_list = 0;
  this->handler_slot_bc = 0;
  this->handler_slot_c0 = 0;
  *(i8 *)&this->keyboard_nav = 1;
  return this;
}
#undef seh_handler
#undef seh_scope
#undef eh_state

/* 0044c730 auto */
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_scope (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
ModalMenuWindow * __thiscall wnd_ctor(ModalMenuWindow *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  wnd_record_init((WndBase *)this);
  eh_state = 0;
  wnd_handlers_ctor((WndHandlers *)this->wnd_handlers);
  this->menu = 0;
  this->on_menu_pos_command = 0;
  this->on_command = 0;
  this->min_width = 0;
  this->min_height = 0;
  this->max_width = 0x4000;
  this->max_height = 0x4000;
  this->handler_slot_a8 = 0;
  this->handler_slot_ac = 0;
  this->modal_running = 0;
  this->hscroll_step = 1;
  this->vscroll_step = 1;
  this->on_menu_select = 0;
  this->on_modal_idle = 0;
  return this;
}
#undef seh_handler
#undef seh_scope
#undef eh_state

/* 0044c8b0 auto */
/* Library Function - Single Match
    public: __thiscall CString::CString(void)
   
   Library: Visual Studio 1998 Debug */

WndHandlers * __thiscall wnd_handlers_ctor(WndHandlers *this)

{
  wnd_clear_handlers(this);
  return this;
}

/* 0044c8e0 auto */
void __thiscall wnd_clear_handlers(WndHandlers *this)

{
  this->on_mouse_move = 0;
  this->on_lbutton_down = 0;
  this->on_lbutton_up_raw = 0;
  this->on_lbutton_up = 0;
  this->on_rbutton_down = 0;
  this->on_rbutton_up_raw = 0;
  this->on_rbutton_up = 0;
  this->on_dblclick = 0;
  this->on_key_down_pre = 0;
  this->on_key_up = 0;
  this->on_key_down = 0;
  this->on_char = 0;
  this->on_close = 0;
  this->on_minimize = 0;
  this->on_restore = 0;
  this->on_set_focus = 0;
  this->on_size = 0;
  this->on_move = 0;
  this->on_msg_44 = 0;
  this->on_hscroll = 0;
  this->on_hscroll_track = 0;
  this->on_vscroll = 0;
  this->on_vscroll_track = 0;
  this->on_msg_4c8 = 0;
  this->on_enter_size_move = 0;
  this->on_exitsizemove = 0;
  return;
}

/* 0044ca40 auto */
void __thiscall wnd_handlers_dtor(void *this)

{
  return;
}

/* 0044ca60: written by hand in src/game/unwind.c */

/* 0044cb20 auto */
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_scope (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
i32 __thiscall surfwnd_wnd_dtor(void *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  /* inlined unwind funclet 0044cb5e */ { wnd_dtor(*(WndBase **)((iptr)&this)); }
  return seh_handler;
}
#undef seh_handler
#undef seh_scope
#undef eh_state

/* 0044cba0: written by hand in src/game/unwind.c */

/* 0044cc80: written by hand in src/game/throneroom.c */

/* 0044cd9b: written by hand in src/game/throneroom.c */

/* 00450390 auto */
void __thiscall wnd_set_palette(WndBase *this,iptr palette)

{
  this->wnd_palette = palette;
  wnd_apply_palette_handle(this,palette);
  return;
}

/* 004503d0 auto */
void __thiscall wnd_hide(WndBase *this)

{
  wnd_obj_hide(this->native_wnd);
  return;
}

/* 00450400 auto */
void __thiscall wnd_center(WndCenterView *this)

{
  wnd_obj_center(this->wnd_obj,0,0);
  return;
}

/* 00450440 auto */
void __thiscall wnd_apply_palette_handle(WndBase *this,iptr palette)

{
  wnd_obj_select_palette(this->native_wnd,*(i32 *)(palette + 0x404));
  return;
}

/* 00451890 auto */
void __thiscall wnd_get_cursor_pos(WndBase *this,iptr out_x,iptr out_y)

{
  iptr hwnd;
  
  hwnd = wnd_get_window(this);
  wnd_obj_get_cursor_pos(hwnd,out_x,out_y);
  return;
}

/* 004518d0 auto */
void __thiscall wnd_activate(Wnd *this)

{
  wnd_focus_and_raise((WndBase *)this);
  wnd_focus_first_control(this);
  return;
}

/* 00451900 auto */
void __thiscall wnd_focus_and_raise(WndBase *this)

{
  wnd_obj_focus_and_raise(this->native_wnd);
  return;
}

/* 00451930 auto */
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_scope (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
Control * __thiscall hotspot_ctor(Control *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  ctrl_base_ctor(this);
  return this;
}
#undef seh_handler
#undef seh_scope
#undef eh_state

/* 004519b0 auto */
void __thiscall
hotspot_create(ClickControl *this,iptr parent,iptr id,iptr rect)

{
  u32 new_hwnd;
  
  if (this->hwnd != 0) {
    ctrl_destroy((Control *)this);
  }
  ctrl_init((Control *)this,parent,1,id,rect);
  this->is_enabled = 0;
  this->on_click = 0;
  this->on_select = 0;
  this->font = 0;
  this->scroll_pos = 0;
  new_hwnd = hotspot_create_hwnd(rect,(iptr)this);
  this->hwnd = new_hwnd;
  return;
}

/* 00451a60 auto */
void __thiscall hotspot_set_click_callback(HotspotClickSetView *this,iptr callback)

{
  this->on_click = callback;
  return;
}

/* 00451a90 auto */
/* Library Function - Single Match
    public: void __thiscall CDialog::SetHelpID(unsigned int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall hotspot_set_dblclick_callback(HotspotDblClickSetView *this,iptr callback)

{
  this->on_dblclick = callback;
  return;
}

/* 00453aa0 auto */
Hotspot * __thiscall hotspot_scalar_dtor(Hotspot *this,uint flags)

{
  hotspot_dtor(this);
  if ((flags & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 00453af0 auto */
void __cdecl ui_pump_messages(void)

{
  win_dispatch_all_messages();
  return;
}

/* 00453ba0 auto */
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_scope (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
void __thiscall hotspot_dtor(Hotspot *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0;
  if (this->hwnd != 0) {
    region_dispose(this->hwnd);
  }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 00453bfa */ { ctrl_base_dtor(*(ControlBase **)((iptr)&this)); }
  return;
}
#undef seh_handler
#undef seh_scope
#undef eh_state

/* 00456ee0 auto */
/* Library Function - Single Match
    public: class ostream * __thiscall ios::tie(class ostream *)
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall wnd_set_keydown_pre_handler(WndSetKeydownPreHandlerView *this,iptr handler)

{
  u32 old_handler;
  
  old_handler = this->tied_stream;
  this->tied_stream = handler;
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
  menu_handle_ctor((GameMenu *)&secondary_menu_handle);
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
  menu_handle_dtor((GameMenu *)&secondary_menu_handle);
  return;
}

/* 0046e287 auto */
void __cdecl ui_delay_ticks(int ticks)

{
  DWORD DVar1;
  DWORD DVar2;
  
  DVar1 = timeGetTime();
  do {
    win_flush_pending_msgs();
    DVar2 = timeGetTime();
    if (2 < game.multiplayer) {
      net_process_messages((NetSession *)&net_session,1,0);
    }
  } while ((int)(DVar2 - DVar1) < (ticks * 0x32) / 3);
  return;
}

/* 0046f18f auto */
#define view (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl ui_blit_all_windows(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (view = 0; view < 8; view++) {
    if ((view == 0) || (*(short *)(&map_view_open_flags + view * 0x3f0) != 0)) {
      wnd_blit_surface((DibSurface *)(&map_views + view * 0x3f0));
    }
  }
  wnd_blit_surface((DibSurface *)&minimap_window);
  wnd_blit_surface((DibSurface *)&status_window);
  wnd_blit_surface((DibSurface *)&city_window);
  wnd_flush_paint();
  return;
}
#undef view

/* 004731d2 auto */
#define success (*(char *)(frame_ + FRAME_OFF(0)))
#define ofn (*(DWORD *)(frame_ + FRAME_OFF(4)))
#define owner_hwnd (*(HWND *)(frame_ + FRAME_OFF(8)))
#define filter_str (*(LPCSTR *)(frame_ + FRAME_OFF(16)))
#define filter_index (*(DWORD *)(frame_ + FRAME_OFF(28)))
#define file_str (*(LPSTR *)(frame_ + FRAME_OFF(32)))
#define max_file (*(DWORD *)(frame_ + FRAME_OFF(36)))
#define title_str (*(LPCSTR *)(frame_ + FRAME_OFF(52)))
#define ofn_flags (*(DWORD *)(frame_ + FRAME_OFF(56)))
#define def_ext_str (*(LPCSTR *)(frame_ + FRAME_OFF(64)))
uint __cdecl
ui_file_name_dialog(iptr parent,iptr title,iptr file_buf,iptr filter,iptr default_ext,int must_exist,
            int is_save)

{
  iptr wnd;
  BOOL BVar1;
  i8 frame_[FRAME_OFF(88)] __attribute__((aligned(8)));  /* original stack frame */
  
  _memset(&ofn,0,0x4c);
  ofn = 0x4c;
  owner_hwnd = (HWND)0x0;
  if (parent != 0) {
    wnd = wnd_get_window((WndBase *)parent);
    owner_hwnd = *(HWND *)(wnd + 4);
  }
  filter_str = (LPCSTR)filter;
  filter_index = 1;
  file_str = (LPSTR)file_buf;
  max_file = 0x100;
  title_str = (LPCSTR)title;
  def_ext_str = (LPCSTR)default_ext;
  if (must_exist == 0) {
    ofn_flags = 0x80e;
  }
  else {
    ofn_flags = 0x180e;
  }
  if (is_save == 0) {
    BVar1 = GetOpenFileNameA((LPOPENFILENAMEA)&ofn);
    success = (char)BVar1;
  }
  else {
    BVar1 = GetSaveFileNameA((LPOPENFILENAMEA)&ofn);
    success = (char)BVar1;
  }
  if (success != 1) {
    CommDlgExtendedError();
  }
  return (uint)(success == 1);
}
#undef success
#undef ofn
#undef owner_hwnd
#undef filter_str
#undef filter_index
#undef file_str
#undef max_file
#undef title_str
#undef ofn_flags
#undef def_ext_str

/* 00484d52 auto */
#define mp_simultaneous_moves (*(char *)((u8 *)&g.d_006ad684))
void __cdecl ui_flush_input(void)

{
  if (mp_simultaneous_moves == '\0') {
    input_flush_events();
  }
  win_flush_pending_msgs();
  wnd_flush_paint();
  win_flush_pending_msgs();
  return;
}
#undef mp_simultaneous_moves

/* 004897fa auto */
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
#define unit_blink_active (*(i8 *)((u8 *)&g.d_0062804c))
#define unit_blink_phase (*(i8 *)((u8 *)&g.d_00628054))
#define unit_blink_skip_tick (*(i8 *)((u8 *)&g.d_0062805c))
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
#undef moving_units_mode
#undef unit_blink_active
#undef unit_blink_phase
#undef unit_blink_skip_tick

/* 00489a0d auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define map_cursor_x (*(short *)((u8 *)&g.d_0064b1b4))
#define map_cursor_y (*(short *)((u8 *)&g.d_0064b1b0))
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
#define mp_simultaneous_moves (*(char *)((u8 *)&g.d_006ad684))
#define mp_turn_civ (*(i8 *)((u8 *)&g.d_006ad578))
#define unit_blink_active (*(i8 *)((u8 *)&g.d_0062804c))
#define unit_blink_phase (*(i8 *)((u8 *)&g.d_00628054))
#define unit_blink_skip_tick (*(i8 *)((u8 *)&g.d_0062805c))
#define unit_focus_done (*(i8 *)((u8 *)&g.d_00673b04))
#define mp_turn_civ_i32 (*(i32 *)((u8 *)&g.d_006ad578))
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
      (((game.multiplayer < 3 || (mp_simultaneous_moves != '\0')) ||
       ((auto_next == 0 || (mp_turn_civ_i32 == human_civ)))))))) {
    if (start_blink) {
      status_redraw(1);
    }
    map_cursor_x = units[unit].x;
    map_cursor_y = units[unit].y;
    if (start_blink) {
      mapviews_ensure_visible((int)map_cursor_x,(int)map_cursor_y,(int)units[unit].owner);
    }
    menu_update_states();
    unit_focus_done = 1;
    return;
  }
  unit_blink_active = 0;
  ui_redraw_all_maps(0);
  return;
}
#undef human_civ
#undef map_cursor_x
#undef map_cursor_y
#undef moving_units_mode
#undef mp_simultaneous_moves
#undef mp_turn_civ
#undef unit_blink_active
#undef unit_blink_phase
#undef unit_blink_skip_tick
#undef unit_focus_done
#undef mp_turn_civ_i32

/* 004904c0 auto */
void __cdecl popup_file_with_sprite(iptr filename,iptr section,iptr sprite,i32 sprite_flags)

{
  popup_text_with_sprite(filename,section,0,sprite,sprite_flags);
  return;
}

/* 00490500 auto */
void __cdecl popup_text_with_city_noflags(iptr filename,iptr section,i32 city)

{
  popup_text_with_city(filename,section,0,city);
  return;
}

/* 00490530 auto */
void __cdecl popup_text_with_unit_noflags(iptr filename,iptr section,iptr unit)

{
  popup_text_with_unit(filename,section,0,unit);
  return;
}

/* 004923c0 auto */
void __thiscall wnd_set_focus(WndBase *this)

{
  wnd_obj_set_focus(this->native_wnd);
  return;
}

/* 00497cc0 auto */
void __thiscall wnd_set_bg_tile(DiploLeaderView *this,iptr tile)

{
  wnd_obj_set_bg_tile(this->wnd_obj,tile);
  return;
}

/* 00497d00 auto */
void __thiscall wnd_set_caption_height(WndBase *this,i32 height)

{
  wnd_obj_set_caption_height(this->native_wnd,height);
  return;
}

/* 004a6b80 auto */
void __cdecl
popup_text_with_advance(iptr filename,iptr section,i32 dlg_flags,iptr advance,i32 sprite_flags)

{
  popup_text_with_sprite(filename,section,dlg_flags,
                     (iptr)(&advance_category_icon_sprites +
                           (char)advances[advance].category * 0xf0 +
                           (char)advances[advance].epoch * 0x3c),sprite_flags);
  return;
}

/* 004a6bdc auto */
#define sprite (*(i8 * *)(frame_ + FRAME_OFF(0)))
i32 __cdecl
popup_text_with_improvement(iptr filename,iptr section,i32 dlg_flags,int improvement,i32 sprite_flags)

{
  i32 result;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (improvement < 0x27) {
    sprite = &improvement_icon_sprites + improvement * 0x3c;
  }
  else {
    sprite = &wonder_icon_sprites + (improvement * 4 - 0x9c) * 0xf;
  }
  result = popup_text_with_sprite(filename,section,dlg_flags,(iptr)sprite,sprite_flags);
  return result;
}
#undef sprite

/* 004a6c4b auto */
i32 __cdecl
popup_text_with_unit_sprite(iptr filename,iptr section,i32 dlg_flags,int unit_type,i32 sprite_flags)

{
  i32 result;
  
  result = popup_text_with_sprite(filename,section,dlg_flags,(iptr)(&unit_sprites + unit_type * 0x3c),sprite_flags)
  ;
  return result;
}

/* 004a6c85 auto */
#define ui_large_screen (*(int *)((u8 *)&g.d_00633584))
void __cdecl
popup_city_sprite_draw_cb(i32 dlg,iptr sprite,iptr city,i32 left,int x,
            i32 y)

{
  gfx_draw_city(sprite,city,0,x + 2,y,(ui_large_screen == 0) - 1 & 8);
  return;
}
#undef ui_large_screen

/* 004a6cc5 auto */
#define dlg_help_pressed (*(u32 *)((u8 *)&g.d_00631edc))
#define ui_large_screen (*(int *)((u8 *)&g.d_00633584))
#define dialog2 (*(Dialog *)(frame_ + FRAME_OFF(0)))
#define sprite (*(Sprite *)(frame_ + FRAME_OFF(756)))
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(816)))
#define seh_scope (*(i8 * *)(frame_ + FRAME_OFF(820)))
#define eh_state (*(int *)(frame_ + FRAME_OFF(824)))
i32 __cdecl popup_text_with_city(iptr filename,iptr section,i32 dlg_flags,iptr city)

{
  i32 result;
  i8 frame_[FRAME_OFF(832)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  dialog_ctor(&dialog2,0x4000);
  eh_state = 0;
  sprite_init(&sprite);
  (*(i8 *)((char *)&eh_state + 0)) = 1;
  sprite_create_solid
            (&sprite,(2 - (uint)(ui_large_screen == 0)) * 0x40,(2 - (uint)(ui_large_screen == 0)) * 0x30
             ,0);
  dialog_load_text(&dialog2,filename,section,dlg_flags);
  dialog_set_sprite_draw_fn((DialogCore *)&dialog2,(iptr)popup_city_sprite_draw_cb);
  dialog_set_image_zoom((DialogWindowView *)&dialog2,0);
  dialog_add_sprite((DialogOptionList *)&dialog2,(iptr)&sprite,city,0);
  result = dlg_show_modal(&dialog2,0);
  dlg_help_pressed = dialog2.result_extra;
  eh_state = (uint)(*(i32 *)((char *)&eh_state + 1)) << 8;
  /* inlined unwind funclet 004a6dc9 */ { sprite_destroy((Sprite *)((iptr)&sprite)); }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 004a6dd2 */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
  return result;
}
#undef dlg_help_pressed
#undef ui_large_screen
#undef dialog2
#undef sprite
#undef seh_handler
#undef seh_scope
#undef eh_state

/* 004a6df7 auto */
#define ui_large_screen (*(int *)((u8 *)&g.d_00633584))
void __cdecl
popup_unit_sprite_draw_cb(i32 dlg,iptr sprite,iptr unit,i32 left,int x,
            i32 y)

{
  gfx_draw_unit(sprite,unit,4,x + 2,y,(ui_large_screen == 0) - 1 & 8,0);
  return;
}
#undef ui_large_screen

/* 004a6e39 auto */
#define dlg_help_pressed (*(u32 *)((u8 *)&g.d_00631edc))
#define ui_large_screen (*(int *)((u8 *)&g.d_00633584))
#define dialog2 (*(Dialog *)(frame_ + FRAME_OFF(0)))
#define sprite (*(Sprite *)(frame_ + FRAME_OFF(756)))
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(816)))
#define seh_scope (*(i8 * *)(frame_ + FRAME_OFF(820)))
#define eh_state (*(int *)(frame_ + FRAME_OFF(824)))
i32 __cdecl popup_text_with_unit(iptr filename,iptr section,i32 dlg_flags,iptr unit)

{
  i32 result;
  i8 frame_[FRAME_OFF(832)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  dialog_ctor(&dialog2,0x4000);
  eh_state = 0;
  sprite_init(&sprite);
  (*(i8 *)((char *)&eh_state + 0)) = 1;
  sprite_create_solid
            (&sprite,(2 - (uint)(ui_large_screen == 0)) * 0x40,(2 - (uint)(ui_large_screen == 0)) * 0x30
             ,0);
  dialog_load_text(&dialog2,filename,section,dlg_flags);
  dialog_set_sprite_draw_fn((DialogCore *)&dialog2,(iptr)popup_unit_sprite_draw_cb);
  dialog_set_image_zoom((DialogWindowView *)&dialog2,0);
  dialog_add_sprite((DialogOptionList *)&dialog2,(iptr)&sprite,unit,0);
  result = dlg_show_modal(&dialog2,0);
  dlg_help_pressed = dialog2.result_extra;
  eh_state = (uint)(*(i32 *)((char *)&eh_state + 1)) << 8;
  /* inlined unwind funclet 004a6f3d */ { sprite_destroy((Sprite *)((iptr)&sprite)); }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 004a6f46 */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
  return result;
}
#undef dlg_help_pressed
#undef ui_large_screen
#undef dialog2
#undef sprite
#undef seh_handler
#undef seh_scope
#undef eh_state

/* 004a93b3 auto */
#define best_tile (*(iptr *)(frame_ + FRAME_OFF(0)))
#define i (*(int *)(frame_ + FRAME_OFF(24)))
#define tile (*(iptr *)(frame_ + FRAME_OFF(32)))
#define best_score (*(uint *)(frame_ + FRAME_OFF(36)))
#define score (*(uint *)(frame_ + FRAME_OFF(40)))
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
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  x2 = (int)cities[city].x;
  y2 = (int)cities[city].y;
  net_batch_begin();
  for (i = 0; i < num_tiles; i++) {
    best_score = 0;
    best_tile = -1;
    for (tile = 0; tile < 0x14; tile++) {
      x = map_wrap_x((char)(&city_tile_dx_table)[tile] + x2);
      y = (char)(&city_tile_dy_table)[tile] + y2;
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
    x = map_wrap_x((char)(&city_tile_dx_table)[best_tile] + x2);
    y = (char)(&city_tile_dy_table)[best_tile] + y2;
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
    x = map_wrap_x((char)(&city_tile_dx_table)[tile] + x2);
    y = (char)(&city_tile_dy_table)[tile] + y2;
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
#undef best_tile
#undef i
#undef tile
#undef best_score
#undef score

/* 004bb570 auto */
void __thiscall wnd_move_to_rect(WndBase *this,iptr rect)

{
  wnd_obj_move_to_rect(this->native_wnd,rect);
  return;
}

/* 004c4240 auto */
void __cdecl popup_game_with_advance(iptr section,iptr advance,i32 sprite_flags)

{
  popup_text_with_advance((iptr)((u8 *)&g.d_006359d4),section,0,advance,sprite_flags);
  return;
}

/* 004cc870 auto */
i32 __cdecl popup_game_with_improvement(iptr section,iptr improvement,i32 sprite_flags)

{
  i32 result;
  
  result = popup_text_with_improvement((iptr)((u8 *)&g.d_006359d4),section,0,improvement,sprite_flags);
  return result;
}

/* 004cc8b0 auto */
i32 __cdecl popup_game_with_unit(iptr section,i32 dlg_flags,iptr unit)

{
  i32 result;
  
  result = popup_text_with_unit((iptr)((u8 *)&g.d_006359d4),section,dlg_flags,unit);
  return result;
}

/* 004cff70 auto */
void __thiscall wnd_set_resize_border(WndBase *this,i32 width)

{
  wnd_obj_set_resize_border(this->native_wnd,width);
  return;
}

/* 004e01b0 auto */
#define dialog2 (*(Dialog *)(frame_ + FRAME_OFF(4)))
#define wonder (*(iptr *)(frame_ + FRAME_OFF(760)))
#define last_choice (*(iptr *)(frame_ + FRAME_OFF(764)))
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(768)))
#define seh_scope (*(i8 * *)(frame_ + FRAME_OFF(772)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(776)))
void __cdecl menu_wonder_movies(void)

{
  iptr wonder_name;
  i32 flags;
  iptr wonder_id;
  i8 frame_[FRAME_OFF(784)] __attribute__((aligned(8)));  /* original stack frame */
  
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
      wonder_name = label_string(improvements[wonder + 0x27].name);
      dialog_add_option((DialogOptionList *)&dialog2,wonder_name,wonder_id,flags);
    }
    dialog_set_default_choice((DialogOptionList *)&dialog2,last_choice);
    wonder = dlg_show_modal(&dialog2,0);
    last_choice = wonder;
    if (wonder < 0) break;
    wonder_show_movie(wonder);
  }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 004e02cb */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
  return;
}
#undef dialog2
#undef wonder
#undef last_choice
#undef seh_handler
#undef seh_scope
#undef eh_state

/* 004e02ef auto */
#define minimap_hidden (*(i8 *)((u8 *)&g.d_00624ee0))
#define panel_margin_x (*(int *)((u8 *)&g.d_0062d858))
#define status_wnd_hidden (*(i8 *)((u8 *)&g.d_00633e00))
#define chat_font_height (*(int *)(frame_ + FRAME_OFF(0)))
#define parley_font_height (*(int *)(frame_ + FRAME_OFF(4)))
#define height2 (*(int *)(frame_ + FRAME_OFF(8)))
#define width2 (*(int *)(frame_ + FRAME_OFF(12)))
#define view (*(int *)(frame_ + FRAME_OFF(24)))
void __cdecl ui_reset_window_layout(void)

{
  int left;
  int client_height;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  wnd_maximize((WndBase *)&main_frame_wnd);
  city_window_init_size();
  wnd_show_restored((WndBase *)&city_window_wnd);
  wnd_move_to_rect((WndBase *)&city_window_wnd,(iptr)((u8 *)&g.d_00655344));
  city_window_close();
  minimap_calc_rect();
  wnd_show_restored((WndBase *)&minimap_wnd);
  minimap_hidden = 0;
  wnd_move_to_rect((WndBase *)&minimap_wnd,(iptr)((u8 *)&g.d_00655324));
  wnd_repaint((SurfaceWindow *)&minimap_window);
  status_calc_wnd_rect();
  wnd_show_restored((WndBase *)&status_window_wnd);
  status_wnd_hidden = 0;
  wnd_move_to_rect((WndBase *)&status_window_wnd,(iptr)((u8 *)&g.d_00655334));
  wnd_repaint((SurfaceWindow *)&status_window);
  if (parley_large_layout == 0) {
    width2 = 0x208;
    height2 = 0x14f;
    parley_font_height = font_cached_height((GameFont *)&font_size20);
  }
  else {
    width2 = 800;
    height2 = 0x1cc;
    parley_font_height = font_cached_height((GameFont *)&font_size30);
  }
  parley_caption_height = panel_margin_y * 2 + panel_bevel_width * 2 + parley_font_height;
  width2 = width2 + (panel_padding_x + panel_margin_x) * 2 + 6;
  height2 = height2 + panel_margin_y * 2 + parley_caption_height * 2 + 0xe;
  left = wnd_client_width((WndBase *)&main_frame_wnd);
  left = (left >> 1) - (width2 >> 1);
  parley_wnd_x = left;
  client_height = wnd_client_height((WndBase *)&main_frame_wnd);
  parley_wnd_y = (client_height >> 1) - (height2 >> 1);
  SetRect(parley_wnd_rect_ptr,left,parley_wnd_y,left + width2,parley_wnd_y + height2);
  wnd_move_to_rect((WndBase *)&parley_wnd_frame,(iptr)parley_wnd_rect_ptr);
  if (chat_wnd_large_layout == 0) {
    width2 = 0x208;
    height2 = 0x14f;
    chat_font_height = font_cached_height((GameFont *)&font_size20);
  }
  else {
    width2 = 800;
    height2 = 0x1cc;
    chat_font_height = font_cached_height((GameFont *)&font_size30);
  }
  chat_wnd_row_height = panel_margin_y * 2 + panel_bevel_width * 2 + chat_font_height;
  width2 = width2 + (panel_padding_x + panel_margin_x) * 2 + 6;
  height2 = height2 + panel_margin_y * 2 + chat_wnd_row_height * 2 + 0xe;
  left = wnd_client_width((WndBase *)&main_frame_wnd);
  left = (left >> 1) - (width2 >> 1);
  chat_wnd_x = left;
  client_height = wnd_client_height((WndBase *)&main_frame_wnd);
  chat_wnd_y = (client_height >> 1) - (height2 >> 1);
  SetRect(chat_wnd_init_rect,left,chat_wnd_y,left + width2,chat_wnd_y + height2);
  wnd_move_to_rect((WndBase *)&chat_wnd_frame,(iptr)chat_wnd_init_rect);
  for (view = 1; view < 8; view++) {
    if (*(short *)(&map_view_open_flags + view * 0x3f0) != 0) {
      *(i16 *)(&map_view_open_flags + view * 0x3f0) = 0;
      wnd_destroy_with_surface((DibSurface *)(&map_views + view * 0x3f0));
    }
  }
  mapview_calc_rect();
  wnd_show_restored((WndBase *)&map_view_wnds);
  wnd_move_to_rect((WndBase *)&map_view_wnds,(iptr)((u8 *)&g.d_006552a4));
  wnd_repaint((SurfaceWindow *)&map_views);
  ui_flush_input();
  return;
}
#undef minimap_hidden
#undef panel_margin_x
#undef status_wnd_hidden
#undef chat_font_height
#undef parley_font_height
#undef height2
#undef width2
#undef view

/* 004e068d auto */
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define minimap_hidden (*(i8 *)((u8 *)&g.d_00624ee0))
#define moving_units_mode (*(i32 *)((u8 *)&g.d_006d1da8))
#define mp_turn_time_limit_ms (*(int *)((u8 *)&g.d_00654b70))
#define saved_layout_valid (*(int *)((u8 *)&g.d_00655280))
#define saved_turn_civ (*(byte *)((u8 *)&g.d_00654fa4))
#define status_wnd_hidden (*(i8 *)((u8 *)&g.d_00633e00))
#define turn_resume_civ (*(byte *)((u8 *)&g.d_00628048))
#define view (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl menu_load_game(void)

{
  byte music_was_on;
  int result;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  mp_turn_timer_stop(1);
  city_window_close();
  parley_wnd_close();
  chat_wnd_close();
  pedia_close();
  picwnd_close((PictureWindowCore *)&advisor_window);
  picwnd_close((PictureWindowCore *)&casualty_window);
  music_was_on = (byte)game.game_options & 8;
  result = game_load_dialog(0,0,0);
  if (result == 0) {
    if (game.multiplayer != '\0') {
      load_game_pick_civ(1);
    }
    saved_turn_civ = (byte)human_civ;
    turn_resume_civ = (byte)human_civ;
    game.multiplayer = '\0';
    game.human_players = (u8)(1 << ((byte)human_civ & 0x1f));
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
    civ_check_password(human_civ);
    if (saved_layout_valid == 0) {
      ui_reset_window_layout();
      wnd_show_restored((WndBase *)&map_view_wnds);
      wnd_move_to_rect((WndBase *)&map_view_wnds,(iptr)((u8 *)&g.d_006552a4));
      mapview_update_title((FrameWindow *)&map_views);
      wnd_repaint((SurfaceWindow *)&map_views);
      for (view = 1; view < 8; view++) {
        if (*(short *)(&map_view_open_flags + view * 0x3f0) != 0) {
          mapview_create((ViewWindow *)(&map_views + view * 0x3f0));
          wnd_move_to_rect
                    ((WndBase *)(&map_view_wnds + view * 0x3f0),
                     (iptr)(&map_view_saved_rects + view * 0x10));
          mapview_update_title((FrameWindow *)(&map_views + view * 0x3f0));
          wnd_repaint((SurfaceWindow *)(&map_views + view * 0x3f0));
        }
      }
    }
    else {
      wnd_maximize((WndBase *)&main_frame_wnd);
      wnd_show_restored((WndBase *)&city_window_wnd);
      wnd_move_to_rect((WndBase *)&city_window_wnd,(iptr)((u8 *)&g.d_00655344));
      city_window_close();
      wnd_show_restored((WndBase *)&minimap_wnd);
      minimap_hidden = 0;
      wnd_move_to_rect((WndBase *)&minimap_wnd,(iptr)((u8 *)&g.d_00655324));
      wnd_repaint((SurfaceWindow *)&minimap_window);
      wnd_show_restored((WndBase *)&status_window_wnd);
      status_wnd_hidden = 0;
      wnd_move_to_rect((WndBase *)&status_window_wnd,(iptr)((u8 *)&g.d_00655334));
      wnd_repaint((SurfaceWindow *)&status_window);
      wnd_show_restored((WndBase *)&map_view_wnds);
      wnd_move_to_rect((WndBase *)&map_view_wnds,(iptr)((u8 *)&g.d_006552a4));
      mapview_update_title((FrameWindow *)&map_views);
      wnd_repaint((SurfaceWindow *)&map_views);
      for (view = 1; view < 8; view++) {
        if (*(short *)(&map_view_open_flags + view * 0x3f0) != 0) {
          mapview_create((ViewWindow *)(&map_views + view * 0x3f0));
          wnd_move_to_rect
                    ((WndBase *)(&map_view_wnds + view * 0x3f0),
                     (iptr)(&map_view_saved_rects + view * 0x10));
          mapview_update_title((FrameWindow *)(&map_views + view * 0x3f0));
          wnd_repaint((SurfaceWindow *)(&map_views + view * 0x3f0));
        }
      }
      wnd_repaint((SurfaceWindow *)&minimap_window);
    }
    moving_units_mode = 0;
    wnd_repaint((SurfaceWindow *)&status_window);
    ui_redraw_all_maps(1);
    ui_focus_active_unit(0);
    menu_update_states();
    pedia_load_indexes((DocumentWindow *)&pedia_window);
    ui_flush_input();
    if ((game.multiplayer != '\0') && (mp_turn_time_limit_ms != 0)) {
      mp_turn_timer_start(1);
    }
  }
  else {
    game.multiplayer = '\0';
    mp_turn_timer_resume(1);
  }
  return;
}
#undef human_civ
#undef minimap_hidden
#undef moving_units_mode
#undef mp_turn_time_limit_ms
#undef saved_layout_valid
#undef saved_turn_civ
#undef status_wnd_hidden
#undef turn_resume_civ
#undef view

/* 004e0a8c auto */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __cdecl dlg_check_set_bool(i32 index,int value)

{
  dlg_check_set(index,(uint)(value != 0));
  return;
}

/* 004e0ab0 auto */
#define prefs_game_options (*(u32 *)((u8 *)&g.d_0064bc1e))
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
  text_set_string_arg(0,(iptr)PTR_s_5_4_0f_Multiplayer_26_March_99_0062765c);
  crt_strcat(&text_string_args,&game_options_version_sep_str);
  crt_strcat(&text_string_args,PTR_s_Patch_3_00627660);
  result = popup_game_flags((iptr)((u8 *)&g.d_0062eb38),1);
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
    prefs_game_options = game.game_options;
    prefs_save_civ2dat();
  }
  return;
}
#undef prefs_game_options

/* 004e0d71 auto */
#define prefs_game_options (*(u32 *)((u8 *)&g.d_0064bc1e))
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
  result = popup_game_flags((iptr)((u8 *)&g.d_0062eb44),1);
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
          popup_game((iptr)((u8 *)&g.d_0062eb54));
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
    prefs_game_options = game.game_options;
    prefs_save_civ2dat();
  }
  return;
}
#undef prefs_game_options

/* 004e0f18 auto */
#define dlg_pending_idle_callback (*(i8 * *)((u8 *)&g.d_00635a3c))
#define mp_double_moves (*(ushort *)((u8 *)&g.d_00654fae))
#define mp_double_production (*(ushort *)((u8 *)&g.d_00654fac))
#define mp_simultaneous_setting (*(short *)((u8 *)&g.d_00654c7c))
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define net_vote_status (*(int *)((u8 *)&g.d_006ad670))
#define prefs_clear_chat_on_boot (*(ushort *)((u8 *)&g.d_006665fc))
#define prefs_clear_chat_on_new_game (*(ushort *)((u8 *)&g.d_006665fa))
#define prefs_mp_double_moves (*(ushort *)((u8 *)&g.d_00666600))
#define prefs_mp_double_production (*(ushort *)((u8 *)&g.d_006665fe))
#define dialog_timeout_start_i32 (*(i32 *)((u8 *)&g.d_006cec80))
#define choice (*(int *)(frame_ + FRAME_OFF(0)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl menu_multiplayer_options(void)

{
  int result;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  dlg_checks_clear();
  dlg_check_set_bool(0,(int)(short)prefs_clear_chat_on_new_game);
  dlg_check_set_bool(1,(int)(short)prefs_clear_chat_on_boot);
  if (net_host_flag != '\0') {
    dlg_check_set_bool(2,(int)(short)mp_double_production);
    dlg_check_set_bool(3,(int)(short)mp_double_moves);
  }
  if (((game.multiplayer < 3) || (net_host_flag == '\0')) && (2 < game.multiplayer)) {
    choice = popup_game_flags((iptr)((u8 *)&g.d_0062eb74),1);
  }
  else {
    choice = popup_game_flags((iptr)((u8 *)&g.d_0062eb60),1);
  }
  if (choice == 0) {
    result = dlg_check_get(0);
    prefs_clear_chat_on_new_game = (ushort)(result != 0);
    result = dlg_check_get(1);
    prefs_clear_chat_on_boot = (ushort)(result != 0);
    prefs_save_civ2dat();
    if (((2 < game.multiplayer) && (net_host_flag != '\0')) || (game.multiplayer < 3)) {
      result = dlg_check_get(2);
      prefs_mp_double_production = (ushort)(result != 0);
      result = dlg_check_get(3);
      prefs_mp_double_moves = (ushort)(result != 0);
      if ((mp_double_production != prefs_mp_double_production) || (mp_double_moves != prefs_mp_double_moves)) {
        if ((2 < game.multiplayer) && (1 < net_player_count)) {
          crt_strcpy(&text_string_args,&net_local_player_name);
          str_clear((iptr)((u8 *)&g.d_0063cd4c));
          str_append_label((iptr)((u8 *)&g.d_0063cd4c),0x350 - (uint)(prefs_mp_double_production == 0));
          crt_strcat(&text_string_arg1,&mp_options_vote_sep_str);
          str_append_label((iptr)((u8 *)&g.d_0063cd4c),0x352 - (uint)(prefs_mp_double_moves == 0));
          net_vote_replies_pending = net_player_count - 1;
          net_vote_status = 0;
          net_send_text_args(0x43,0xff,2,0,0,0);
          dlg_pending_idle_callback = ((void *)(iptr)net_vote_wait_idle_cb);
          dialog_timeout_start_i32 = timer_ticks();
          result = popup_game_sprite_flags((iptr)((u8 *)&g.d_0062eb8c),0x2000001,(iptr)((u8 *)&g.d_0063fc58),0);
          if (((result < 0) || (net_vote_status == -1)) || (net_vote_replies_pending != 0)) {
            prefs_mp_double_production = mp_double_production;
            prefs_mp_double_moves = mp_double_moves;
            net_send_text_args(0x44,0xff,0,0,0,0);
            popup_game_with_sprite((iptr)((u8 *)&g.d_0062eb9c),(iptr)((u8 *)&g.d_0063fc58),0);
            return;
          }
        }
        mp_double_production = prefs_mp_double_production;
        mp_double_moves = prefs_mp_double_moves;
        rules_apply_double_moves();
        if ((2 < game.multiplayer) && (1 < net_player_count)) {
          net_send_message(0x1b,0xff,0,0,0,0,0,0,0,0);
          net_send_message(0x33,0xff,(int)(short)mp_double_production,(int)(short)mp_double_moves,
                             (int)mp_simultaneous_setting,0,0,0,0,0);
          net_send_text_args(0x45,0xff,0,0,0,0);
          popup_game_with_sprite((iptr)((u8 *)&g.d_0062eba8),(iptr)((u8 *)&g.d_0063fc58),0);
        }
      }
    }
  }
  return;
}
#undef dlg_pending_idle_callback
#undef mp_double_moves
#undef mp_double_production
#undef mp_simultaneous_setting
#undef net_host_flag
#undef net_vote_status
#undef prefs_clear_chat_on_boot
#undef prefs_clear_chat_on_new_game
#undef prefs_mp_double_moves
#undef prefs_mp_double_production
#undef dialog_timeout_start_i32
#undef choice

/* 004e1452 auto */
#define prefs_message_options (*(u16 *)((u8 *)&g.d_0064bc22))
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
  result = popup_game_flags((iptr)((u8 *)&g.d_0062ebb4),1);
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
    prefs_message_options = game.message_options;
    prefs_save_civ2dat();
  }
  return;
}
#undef prefs_message_options

/* 004e2597 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define map_show_hidden_terrain (*(i32 *)((u8 *)&g.d_0062bcd8))
#define unit_blink_active (*(i8 *)((u8 *)&g.d_0062804c))
void __cdecl menu_show_hidden_terrain(void)

{
  unit_blink_active = 0;
  map_show_hidden_terrain = 1;
  map_redraw_all_views(human_civ,1);
  popup_game((iptr)((u8 *)&g.d_0062ec5c));
  map_show_hidden_terrain = 0;
  map_redraw_all_views(human_civ,1);
  return;
}
#undef human_civ
#undef map_show_hidden_terrain
#undef unit_blink_active

/* 004e25ef auto */
#define cd_music_current_track (*(int *)((u8 *)&g.d_0062b428))
#define dialog2 (*(Dialog *)(frame_ + FRAME_OFF(4)))
#define track_count (*(int *)(frame_ + FRAME_OFF(760)))
#define tries (*(int *)(frame_ + FRAME_OFF(764)))
#define seh_handler (*(i32 *)(frame_ + FRAME_OFF(768)))
#define seh_scope (*(i8 * *)(frame_ + FRAME_OFF(772)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(776)))
void __cdecl menu_select_music(void)

{
  int choice;
  i8 frame_[FRAME_OFF(784)] __attribute__((aligned(8)));  /* original stack frame */
  
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
    popup_game((iptr)((u8 *)&g.d_0062ec6c));
    eh_state = 0xffffffff;
    /* inlined unwind funclet 004e27df */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
  }
  else {
    if (track_count == 0x18) {
      dlg_load_game_section(&dialog2,(iptr)((u8 *)&g.d_0062ec7c),1);
    }
    else if (track_count == 0x12) {
      dlg_load_game_section(&dialog2,(iptr)((u8 *)&g.d_0062ec90),1);
    }
    else if (track_count == 0xc) {
      dlg_load_game_section(&dialog2,(iptr)((u8 *)&g.d_0062eca4),1);
    }
    else {
      if (track_count != 10) {
        popup_game((iptr)((u8 *)&g.d_0062ecc0));
        eh_state = 0xffffffff;
        /* inlined unwind funclet 004e27df */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
        goto LAB_004e27f5;
      }
      dlg_load_game_section(&dialog2,(iptr)((u8 *)&g.d_0062ecb4),1);
    }
    if (1 < cd_music_current_track) {
      dialog_set_default_choice((DialogOptionList *)&dialog2,cd_music_current_track - 2);
    }
    choice = dlg_show_modal(&dialog2,0);
    if (choice < 0) {
      eh_state = 0xffffffff;
      /* inlined unwind funclet 004e27df */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
    }
    else {
      music_play_track(choice + 2,1);
      eh_state = 0xffffffff;
      /* inlined unwind funclet 004e27df */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
    }
  }
LAB_004e27f5:
  return;
}
#undef cd_music_current_track
#undef dialog2
#undef track_count
#undef tries
#undef seh_handler
#undef seh_scope
#undef eh_state

/* 004e2803 auto */
#define blocked_input_kind (*(i32 *)((u8 *)&g.d_006c31ac))
#define cheat_terrain_saved_bits (*(i32 *)((u8 *)&g.d_00633678))
#define city_acquire_wonder_busy (*(int *)((u8 *)&g.d_006ad8e8))
#define city_create_busy (*(int *)((u8 *)&g.d_006ad8c4))
#define city_delete_busy (*(int *)((u8 *)&g.d_006ad8c8))
#define city_turn_processing (*(int *)((u8 *)&g.d_0062edf8))
#define civ_check_destroyed_busy (*(int *)((u8 *)&g.d_006ad8f4))
#define civ_create_busy (*(int *)((u8 *)&g.d_006ad8f0))
#define civ_eliminate_busy (*(int *)((u8 *)&g.d_006ad8ec))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define map_cursor_x (*(short *)((u8 *)&g.d_0064b1b4))
#define map_cursor_y (*(short *)((u8 *)&g.d_0064b1b0))
#define map_view_center_x (*(short *)((u8 *)&g.d_0066ca88))
#define mapview_center_y (*(short *)((u8 *)&g.d_0066ca8a))
#define mapview_zoom (*(short *)((u8 *)&g.d_0066ca8c))
#define net_lock_map_busy (*(int *)((u8 *)&g.d_006ad8cc))
#define net_unlock_map_busy (*(int *)((u8 *)&g.d_006ad8d0))
#define prefs_game_options (*(u32 *)((u8 *)&g.d_0064bc1e))
#define unit_create_busy (*(int *)((u8 *)&g.d_006ad8bc))
#define unit_delete_busy (*(int *)((u8 *)&g.d_006ad8c0))
#define unit_delete_cargo_busy (*(int *)((u8 *)&g.d_006ad900))
#define unit_destroy_redraw_busy (*(int *)((u8 *)&g.d_006ad904))
#define unit_gather_cargo_busy (*(int *)((u8 *)&g.d_006ad8f8))
#define unit_lift_off_map_busy (*(int *)((u8 *)&g.d_006ad8fc))
#define unit_relocate_busy (*(int *)((u8 *)&g.d_006ad8e4))
#define unit_stack_bottom_busy (*(int *)((u8 *)&g.d_006ad8e0))
#define unit_stack_link_busy (*(int *)((u8 *)&g.d_006ad8dc))
#define unit_stack_unlink_busy (*(int *)((u8 *)&g.d_006ad8d8))
#define blocked_input_arg1_i32 (*(i32 *)((u8 *)&g.d_006c31b0))
#define blocked_input_arg2_i32 (*(i32 *)((u8 *)&g.d_006c31b4))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl menu_command(i32 menu,int cmd)

{
  SHORT SVar1;
  int result;
  
  result = XD_InFlushSendBuffer();
  if ((((((((result == 0) && (unit_create_busy == 0)) && (unit_delete_busy == 0)) &&
         ((city_create_busy == 0 && (city_delete_busy == 0)))) && (net_lock_map_busy == 0)) &&
       (((net_unlock_map_busy == 0 && (unit_stack_unlink_busy == 0)) &&
        ((unit_stack_link_busy == 0 && (((unit_stack_bottom_busy == 0 && (unit_relocate_busy == 0)) && (city_acquire_wonder_busy == 0)))
         ))))) && ((civ_eliminate_busy == 0 && (civ_create_busy == 0)))) &&
     ((civ_check_destroyed_busy == 0 &&
      (((unit_gather_cargo_busy == 0 && (unit_lift_off_map_busy == 0)) && ((unit_delete_cargo_busy == 0 && (unit_destroy_redraw_busy == 0)))))
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
            civ_change_password_dialog(human_civ);
          }
          else if (cmd == 0x132) {
            mp_cmd_change_timer();
          }
        }
        else if (cmd < 0x202) {
          if (cmd == 0x201) {
            taxrate_dialog_show(human_civ);
          }
          else if (cmd == 0x1f1) {
            game_quit_or_retire(0);
          }
          else if ((cmd == 0x1f2) && (game.multiplayer == 1)) {
            result = popup_game_with_sprite((iptr)((u8 *)&g.d_0062ed14),(iptr)((u8 *)&g.d_0063fc58),0);
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
            throneroom_show(human_civ);
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
            if (mapview_zoom < 8) {
              mapview_zoom++;
              mapview_redraw((ViewWindow *)&map_views,human_civ,1);
            }
          }
          else if (cmd == 0x302) {
            ui_redraw_all_maps(0);
          }
        }
        else if (cmd < 0x321) {
          if (cmd == 800) {
            mapview_zoom = 8;
            mapview_redraw((ViewWindow *)&map_views,human_civ,1);
          }
          else if ((cmd == 0x311) && (-7 < mapview_zoom)) {
            mapview_zoom--;
            mapview_redraw((ViewWindow *)&map_views,human_civ,1);
          }
        }
        else if (cmd < 0x331) {
          if (cmd == 0x330) {
            menu_show_hidden_terrain();
          }
          else {
            switch(cmd) {
            case 0x321:
              mapview_zoom = 0;
              map_view_center_x = map_cursor_x;
              mapview_center_y = map_cursor_y;
              mapview_redraw((ViewWindow *)&map_views,human_civ,1);
              break;
            case 0x322:
              mapview_zoom = -3;
              mapview_redraw((ViewWindow *)&map_views,human_civ,1);
              break;
            case 0x324:
              mapview_zoom = -7;
              mapview_redraw((ViewWindow *)&map_views,human_civ,1);
              break;
            case 0x327:
              game.game_options = game.game_options ^ 0x20;
              menu_set_item_checked
                        ((GameMenu *)&main_menu,0x327,(game.game_options & 0x20) >> 5);
              map_redraw_all_views(human_civ,1);
              prefs_game_options = game.game_options;
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
                      ((ViewWindow *)&map_views,(int)map_cursor_x,(int)map_cursor_y);
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
            SVar1 = GetAsyncKeyState(0x10);
            if ((((char)((ushort)SVar1 >> 8) == '\0') || ((game.game_options & 0x8000) == 0)) ||
               (game.multiplayer != '\0')) {
              wonders_report_show(human_civ);
            }
            else {
              menu_wonder_movies();
            }
          }
          else {
            switch(cmd) {
            case 0x500:
              if ((((game.game_options & 0x8000) == 0) || (game.multiplayer != '\0')) ||
                 (SVar1 = GetAsyncKeyState(0x10), (char)((ushort)SVar1 >> 8) == '\0')) {
                council_show(human_civ,0);
              }
              else {
                council_show(human_civ,1);
              }
              break;
            case 0x501:
              city_status_show(human_civ);
              break;
            case 0x502:
              defense_minister_show(human_civ);
              break;
            case 0x503:
              foreign_minister_show(human_civ);
              break;
            case 0x504:
              attitude_advisor_show(human_civ);
              break;
            case 0x505:
              trade_advisor_show(human_civ);
              break;
            case 0x506:
              science_advisor_show(human_civ);
              break;
            case 0x507:
              parley_wnd_open((ViewWindow *)&chat_wnd,0,4);
              break;
            case 0x508:
              casualty_timeline_show(human_civ);
            }
          }
        }
        else if (cmd < 0x702) {
          if (cmd == 0x701) {
            if ((game.multiplayer == '\0') || (mp_cheat_menu_allowed != 0)) {
              cheat_toggle_mode();
            }
          }
          else {
            switch(cmd) {
            case 0x602:
              SVar1 = GetAsyncKeyState(0x10);
              if ((((char)((ushort)SVar1 >> 8) == '\0') || ((game.game_options & 0x8000) == 0)) ||
                 (game.multiplayer != '\0')) {
                top_cities_show(human_civ);
              }
              else {
                endgame_defeat_movie(human_civ);
              }
              break;
            case 0x603:
              SVar1 = GetAsyncKeyState(0x10);
              if ((((char)((ushort)SVar1 >> 8) == '\0') || ((game.game_options & 0x8000) == 0)) ||
                 (game.multiplayer != '\0')) {
                civ_score_window_show(human_civ);
                if (game.reveal_map != '\0') {
                  civ_rating_window_show(human_civ);
                  powergraph_show();
                }
              }
              else {
                destroyed_civs_show(human_civ);
              }
              break;
            case 0x605:
              SVar1 = GetAsyncKeyState(0x10);
              if ((((char)((ushort)SVar1 >> 8) == '\0') || ((game.game_options & 0x8000) == 0)) ||
                 (game.multiplayer != '\0')) {
                demographics_show(human_civ);
              }
              else {
                endgame_spaceship_arrival(-(human_civ + 1U & 7));
              }
              break;
            case 0x606:
              SVar1 = GetAsyncKeyState(0x10);
              if ((((char)((ushort)SVar1 >> 8) == '\0') || ((game.game_options & 0x8000) == 0)) ||
                 (game.multiplayer != '\0')) {
                spaceship_select_view_dialog(human_civ);
              }
              else {
                endgame_spaceship_arrival(human_civ);
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
            pedia_open_category((MediaWindow *)&pedia_window,1,1);
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
            pedia_open_category((MediaWindow *)&pedia_window,2,1);
            break;
          case 0x905:
            pedia_open_category((MediaWindow *)&pedia_window,3,1);
            break;
          case 0x907:
            pedia_open_category((MediaWindow *)&pedia_window,4,1);
            break;
          case 0x909:
            pedia_open_category((MediaWindow *)&pedia_window,6,1);
            break;
          case 0x90b:
            pedia_open_category((MediaWindow *)&pedia_window,5,1);
            break;
          case 0x90d:
            if ((cmd == 0x905) &&
               (SVar1 = GetAsyncKeyState(0x10), (char)((ushort)SVar1 >> 8) != '\0')) {
              menu_wonder_movies();
            }
            else {
              pedia_open_category((MediaWindow *)&pedia_window,7,1);
            }
            break;
          case 0x9f0:
            if (game.multiplayer < 3) {
              result = popup_game_flags((iptr)((u8 *)&g.d_0062ed20),1);
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
    dbg_log((iptr)((u8 *)&g.d_0062ecd0));
    blocked_input_kind = 5;
    blocked_input_arg1_i32 = menu;
    blocked_input_arg2_i32 = cmd;
  }
  return;
}
#undef blocked_input_kind
#undef cheat_terrain_saved_bits
#undef city_acquire_wonder_busy
#undef city_create_busy
#undef city_delete_busy
#undef city_turn_processing
#undef civ_check_destroyed_busy
#undef civ_create_busy
#undef civ_eliminate_busy
#undef human_civ
#undef map_cursor_x
#undef map_cursor_y
#undef map_view_center_x
#undef mapview_center_y
#undef mapview_zoom
#undef net_lock_map_busy
#undef net_unlock_map_busy
#undef prefs_game_options
#undef unit_create_busy
#undef unit_delete_busy
#undef unit_delete_cargo_busy
#undef unit_destroy_redraw_busy
#undef unit_gather_cargo_busy
#undef unit_lift_off_map_busy
#undef unit_relocate_busy
#undef unit_stack_bottom_busy
#undef unit_stack_link_busy
#undef unit_stack_unlink_busy
#undef blocked_input_arg1_i32
#undef blocked_input_arg2_i32

/* 004e3a86 auto */
#define editor_disabled (*(i32 *)(frame_ + FRAME_OFF(4)))
#define editor_checked (*(i32 *)(frame_ + FRAME_OFF(8)))
#define cheat_checked (*(i32 *)(frame_ + FRAME_OFF(12)))
#define cheat_disabled (*(i32 *)(frame_ + FRAME_OFF(16)))
void __cdecl menu_build_main(void)

{
  int status;
  i32 item_arg;
  iptr label;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  menu_reset((GameMenu *)&main_menu,0x1bbc);
  status = text_open_section((iptr)((u8 *)&g.d_0062ed34),(iptr)((u8 *)&g.d_0062ed2c));
  if (status == 0) {
    item_arg = text_read_line(1);
    menu_add_menu((GameMenu *)&main_menu,1,item_arg);
    item_arg = 0;
    label = text_read_line(1);
    menu_add_item((GameMenu *)&main_menu,1,0x101,label,item_arg);
    item_arg = 0;
    label = text_read_line(1);
    menu_add_item((GameMenu *)&main_menu,1,0x102,label,item_arg);
    item_arg = 0;
    label = text_read_line(1);
    menu_add_item((GameMenu *)&main_menu,1,0x103,label,item_arg);
    item_arg = 0;
    label = text_read_line(1);
    menu_add_item((GameMenu *)&main_menu,1,0x104,label,item_arg);
    item_arg = 0;
    label = text_read_line(1);
    menu_add_item((GameMenu *)&main_menu,1,0x105,label,item_arg);
    menu_add_item((GameMenu *)&main_menu,1,0,0,0);
    item_arg = 0;
    label = text_read_line(1);
    menu_add_item((GameMenu *)&main_menu,1,0x106,label,item_arg);
    menu_add_item((GameMenu *)&main_menu,1,0,0,0);
    item_arg = 0;
    label = text_read_line(1);
    menu_add_item((GameMenu *)&main_menu,1,0x110,label,item_arg);
    item_arg = 0;
    label = text_read_line(1);
    menu_add_item((GameMenu *)&main_menu,1,0x120,label,item_arg);
    item_arg = 0;
    label = text_read_line(1);
    menu_add_item((GameMenu *)&main_menu,1,0x130,label,item_arg);
    menu_add_item((GameMenu *)&main_menu,1,0,0,0);
    item_arg = 0;
    label = text_read_line(1);
    menu_add_item((GameMenu *)&main_menu,1,0x131,label,item_arg);
    item_arg = 0;
    label = text_read_line(1);
    menu_add_item((GameMenu *)&main_menu,1,0x132,label,item_arg);
    menu_add_item((GameMenu *)&main_menu,1,0,0,0);
    item_arg = 0;
    label = text_read_line(1);
    menu_add_item((GameMenu *)&main_menu,1,0x1f0,label,item_arg);
    item_arg = 0;
    label = text_read_line(1);
    menu_add_item((GameMenu *)&main_menu,1,0x1f1,label,item_arg);
    status = text_open_section(0,(iptr)((u8 *)&g.d_0062ed3c));
    if (status == 0) {
      item_arg = text_read_line(1);
      menu_add_menu((GameMenu *)&main_menu,2,item_arg);
      item_arg = 0;
      label = text_read_line(1);
      menu_add_item((GameMenu *)&main_menu,2,0x201,label,item_arg);
      menu_add_item((GameMenu *)&main_menu,2,0,0,0);
      item_arg = 0;
      label = text_read_line(1);
      menu_add_item((GameMenu *)&main_menu,2,0x205,label,item_arg);
      item_arg = 0;
      label = text_read_line(1);
      menu_add_item((GameMenu *)&main_menu,2,0x210,label,item_arg);
      menu_add_item((GameMenu *)&main_menu,2,0,0,0);
      item_arg = 0;
      label = text_read_line(1);
      menu_add_item((GameMenu *)&main_menu,2,0x220,label,item_arg);
      status = text_open_section(0,(iptr)((u8 *)&g.d_0062ed44));
      if (status == 0) {
        item_arg = text_read_line(1);
        menu_add_menu((GameMenu *)&main_menu,3,item_arg);
        item_arg = 0;
        label = text_read_line(1);
        menu_add_item((GameMenu *)&main_menu,3,0x301,label,item_arg);
        item_arg = 0;
        label = text_read_line(1);
        menu_add_item((GameMenu *)&main_menu,3,0x302,label,item_arg);
        menu_add_item((GameMenu *)&main_menu,3,0,0,0);
        item_arg = 0;
        label = text_read_line(1);
        menu_add_item((GameMenu *)&main_menu,3,0x310,label,item_arg);
        item_arg = 0;
        label = text_read_line(1);
        menu_add_item((GameMenu *)&main_menu,3,0x311,label,item_arg);
        menu_add_item((GameMenu *)&main_menu,3,0,0,0);
        item_arg = 0;
        label = text_read_line(1);
        menu_add_item((GameMenu *)&main_menu,3,800,label,item_arg);
        item_arg = 0;
        label = text_read_line(1);
        menu_add_item((GameMenu *)&main_menu,3,0x321,label,item_arg);
        item_arg = 0;
        label = text_read_line(1);
        menu_add_item((GameMenu *)&main_menu,3,0x322,label,item_arg);
        item_arg = 0;
        label = text_read_line(1);
        menu_add_item((GameMenu *)&main_menu,3,0x324,label,item_arg);
        menu_add_item((GameMenu *)&main_menu,3,0,0,0);
        item_arg = 0;
        label = text_read_line(1);
        menu_add_item((GameMenu *)&main_menu,3,0x327,label,item_arg);
        item_arg = 0;
        label = text_read_line(1);
        menu_add_item((GameMenu *)&main_menu,3,0x328,label,item_arg);
        item_arg = 0;
        label = text_read_line(1);
        menu_add_item((GameMenu *)&main_menu,3,0x330,label,item_arg);
        item_arg = 0;
        label = text_read_line(1);
        menu_add_item((GameMenu *)&main_menu,3,0x340,label,item_arg);
        menu_set_item_checked
                  ((GameMenu *)&main_menu,0x327,(game.game_options & 0x20) >> 5);
        status = text_open_section(0,(iptr)((u8 *)&g.d_0062ed4c));
        if (status == 0) {
          item_arg = text_read_line(1);
          menu_add_menu((GameMenu *)&main_menu,4,item_arg);
          item_arg = 0x3c;
          label = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x401,label,item_arg);
          item_arg = 0x3c;
          label = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x410,label,item_arg);
          item_arg = 0x3c;
          label = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x411,label,item_arg);
          item_arg = 0x3c;
          label = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x412,label,item_arg);
          item_arg = 0x3c;
          label = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x413,label,item_arg);
          menu_add_item((GameMenu *)&main_menu,4,0,0,0);
          item_arg = 0;
          label = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x417,label,item_arg);
          item_arg = 0;
          label = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x418,label,item_arg);
          item_arg = 0;
          label = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x41b,label,item_arg);
          item_arg = 0;
          label = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x420,label,item_arg);
          item_arg = 0;
          label = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x421,label,item_arg);
          menu_add_item((GameMenu *)&main_menu,4,0,0,0);
          item_arg = 0;
          label = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x430,label,item_arg);
          item_arg = 0;
          label = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x440,label,item_arg);
          item_arg = 0;
          label = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x441,label,item_arg);
          item_arg = 0;
          label = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x442,label,item_arg);
          item_arg = 0x3c;
          label = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x445,label,item_arg);
          menu_add_item((GameMenu *)&main_menu,4,0,0,0);
          item_arg = 0;
          label = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x450,label,item_arg);
          item_arg = 0;
          label = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x451,label,item_arg);
          menu_add_item((GameMenu *)&main_menu,4,0,0,0);
          item_arg = 0;
          label = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x460,label,item_arg);
          item_arg = 0;
          label = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x468,label,item_arg);
          item_arg = 0;
          label = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x470,label,item_arg);
          item_arg = 0;
          label = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x480,label,item_arg);
          menu_add_item((GameMenu *)&main_menu,4,0,0,0);
          item_arg = 0;
          label = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x490,label,item_arg);
          status = text_open_section(0,(iptr)((u8 *)&g.d_0062ed54));
          if (status == 0) {
            item_arg = text_read_line(1);
            menu_add_menu((GameMenu *)&main_menu,5,item_arg);
            item_arg = 0;
            label = text_read_line(1);
            menu_add_item((GameMenu *)&main_menu,5,0x507,label,item_arg);
            item_arg = 0;
            label = text_read_line(1);
            menu_add_item((GameMenu *)&main_menu,5,0x500,label,item_arg);
            menu_add_item((GameMenu *)&main_menu,5,0,0,0);
            item_arg = 0;
            label = text_read_line(1);
            menu_add_item((GameMenu *)&main_menu,5,0x501,label,item_arg);
            item_arg = 0;
            label = text_read_line(1);
            menu_add_item((GameMenu *)&main_menu,5,0x502,label,item_arg);
            item_arg = 0;
            label = text_read_line(1);
            menu_add_item((GameMenu *)&main_menu,5,0x503,label,item_arg);
            menu_add_item((GameMenu *)&main_menu,5,0,0,0);
            item_arg = 0;
            label = text_read_line(1);
            menu_add_item((GameMenu *)&main_menu,5,0x504,label,item_arg);
            item_arg = 0;
            label = text_read_line(1);
            menu_add_item((GameMenu *)&main_menu,5,0x505,label,item_arg);
            item_arg = 0;
            label = text_read_line(1);
            menu_add_item((GameMenu *)&main_menu,5,0x506,label,item_arg);
            menu_add_item((GameMenu *)&main_menu,5,0,0,0);
            item_arg = 0;
            label = text_read_line(1);
            menu_add_item((GameMenu *)&main_menu,5,0x508,label,item_arg);
            status = text_open_section(0,(iptr)((u8 *)&g.d_0062ed60));
            if (status == 0) {
              item_arg = text_read_line(1);
              menu_add_menu((GameMenu *)&main_menu,6,item_arg);
              item_arg = 0;
              label = text_read_line(1);
              menu_add_item((GameMenu *)&main_menu,6,0x601,label,item_arg);
              item_arg = 0;
              label = text_read_line(1);
              menu_add_item((GameMenu *)&main_menu,6,0x602,label,item_arg);
              item_arg = 0;
              label = text_read_line(1);
              menu_add_item((GameMenu *)&main_menu,6,0x603,label,item_arg);
              menu_add_item((GameMenu *)&main_menu,6,0,0,0);
              item_arg = 0;
              label = text_read_line(1);
              menu_add_item((GameMenu *)&main_menu,6,0x605,label,item_arg);
              item_arg = 0;
              label = text_read_line(1);
              menu_add_item((GameMenu *)&main_menu,6,0x606,label,item_arg);
              status = text_open_section(0,(iptr)((u8 *)&g.d_0062ed68));
              if (status == 0) {
                item_arg = text_read_line(1);
                menu_add_menu((GameMenu *)&main_menu,7,item_arg);
                item_arg = 0;
                label = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x701,label,item_arg);
                menu_add_item((GameMenu *)&main_menu,7,0,0,0);
                item_arg = 0;
                label = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x711,label,item_arg);
                item_arg = 0;
                label = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x712,label,item_arg);
                item_arg = 0;
                label = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x713,label,item_arg);
                menu_add_item((GameMenu *)&main_menu,7,0,0,0);
                item_arg = 0;
                label = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x721,label,item_arg);
                item_arg = 0;
                label = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x722,label,item_arg);
                menu_add_item((GameMenu *)&main_menu,7,0,0,0);
                item_arg = 0;
                label = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x731,label,item_arg);
                item_arg = 0;
                label = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x732,label,item_arg);
                item_arg = 0;
                label = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x740,label,item_arg);
                item_arg = 0;
                label = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x748,label,item_arg);
                item_arg = 0;
                label = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x750,label,item_arg);
                item_arg = 0;
                label = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x752,label,item_arg);
                menu_add_item((GameMenu *)&main_menu,7,0,0,0);
                item_arg = 0;
                label = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x755,label,item_arg);
                item_arg = 0;
                label = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x760,label,item_arg);
                item_arg = 0;
                label = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x765,label,item_arg);
                menu_add_item((GameMenu *)&main_menu,7,0,0,0);
                item_arg = 0;
                label = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x768,label,item_arg);
                item_arg = 0;
                label = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x770,label,item_arg);
                if (((game.game_options & 0x8000) == 0) || (game.multiplayer != '\0')) {
                  cheat_disabled = 1;
                }
                else {
                  cheat_disabled = 0;
                }
                menu_set_menu_enabled((GameMenu *)&main_menu,7,cheat_disabled);
                if (((game.game_options & 0x8000) == 0) || (game.multiplayer != '\0')) {
                  cheat_checked = 0;
                }
                else {
                  cheat_checked = 1;
                }
                menu_set_item_checked((GameMenu *)&main_menu,0x701,cheat_checked);
                menu_set_item_enabled
                          ((GameMenu *)&main_menu,0x701,
                           (uint)(game.multiplayer != '\0' && mp_cheat_menu_allowed == 0));
                status = text_open_section(0,(iptr)((u8 *)&g.d_0062ed70));
                if (status == 0) {
                  item_arg = text_read_line(1);
                  menu_add_menu((GameMenu *)&main_menu,8,item_arg);
                  item_arg = 0;
                  label = text_read_line(1);
                  menu_add_item((GameMenu *)&main_menu,8,0x801,label,item_arg);
                  menu_add_item((GameMenu *)&main_menu,8,0,0,0);
                  item_arg = 0;
                  label = text_read_line(1);
                  menu_add_item((GameMenu *)&main_menu,8,0x802,label,item_arg);
                  item_arg = 0;
                  label = text_read_line(1);
                  menu_add_item((GameMenu *)&main_menu,8,0x803,label,item_arg);
                  item_arg = 0;
                  label = text_read_line(1);
                  menu_add_item((GameMenu *)&main_menu,8,0x804,label,item_arg);
                  item_arg = 0;
                  label = text_read_line(1);
                  menu_add_item((GameMenu *)&main_menu,8,0x805,label,item_arg);
                  item_arg = 0;
                  label = text_read_line(1);
                  menu_add_item((GameMenu *)&main_menu,8,0x806,label,item_arg);
                  item_arg = 0;
                  label = text_read_line(1);
                  menu_add_item((GameMenu *)&main_menu,8,0x807,label,item_arg);
                  item_arg = 0;
                  label = text_read_line(1);
                  menu_add_item((GameMenu *)&main_menu,8,0x808,label,item_arg);
                  item_arg = 0;
                  label = text_read_line(1);
                  menu_add_item((GameMenu *)&main_menu,8,0x809,label,item_arg);
                  if (((((game.game_options & 0x8000) == 0) || (game.multiplayer != '\0')) ||
                      ((game.game_flags & 0x80) == 0)) ||
                     (status = _strcmp(&scenario_dir_path,&game_home_dir), status == 0)) {
                    editor_checked = 0;
                  }
                  else {
                    editor_checked = 1;
                  }
                  menu_set_item_checked((GameMenu *)&main_menu,0x801,editor_checked);
                  if ((((game.game_options & 0x8000) == 0) || (game.multiplayer != '\0')) ||
                     (((game.game_flags & 0x80) == 0 ||
                      (status = _strcmp(&scenario_dir_path,&game_home_dir), status == 0)))) {
                    editor_disabled = 1;
                  }
                  else {
                    editor_disabled = 0;
                  }
                  menu_set_menu_enabled((GameMenu *)&main_menu,8,editor_disabled);
                  menu_set_item_enabled
                            ((GameMenu *)&main_menu,0x801,(uint)(game.multiplayer != '\0'));
                  status = text_open_section(0,(iptr)((u8 *)&g.d_0062ed78));
                  if (status == 0) {
                    item_arg = text_read_line(1);
                    menu_add_menu((GameMenu *)&main_menu,9,item_arg);
                    item_arg = 0;
                    label = text_read_line(1);
                    menu_add_item((GameMenu *)&main_menu,9,0x901,label,item_arg);
                    item_arg = 0;
                    label = text_read_line(1);
                    menu_add_item((GameMenu *)&main_menu,9,0x903,label,item_arg);
                    item_arg = 0;
                    label = text_read_line(1);
                    menu_add_item((GameMenu *)&main_menu,9,0x905,label,item_arg);
                    item_arg = 0;
                    label = text_read_line(1);
                    menu_add_item((GameMenu *)&main_menu,9,0x907,label,item_arg);
                    menu_add_item((GameMenu *)&main_menu,9,0,0,0);
                    item_arg = 0;
                    label = text_read_line(1);
                    menu_add_item((GameMenu *)&main_menu,9,0x909,label,item_arg);
                    item_arg = 0;
                    label = text_read_line(1);
                    menu_add_item((GameMenu *)&main_menu,9,0x90b,label,item_arg);
                    menu_add_item((GameMenu *)&main_menu,9,0,0,0);
                    item_arg = 0;
                    label = text_read_line(1);
                    menu_add_item((GameMenu *)&main_menu,9,0x90d,label,item_arg);
                    menu_add_item((GameMenu *)&main_menu,9,0,0,0);
                    item_arg = 0;
                    label = text_read_line(1);
                    menu_add_item((GameMenu *)&main_menu,9,0x9f0,label,item_arg);
                    menu_set_item_hidden((GameMenu *)&main_menu,0x441,1);
                    menu_set_item_hidden((GameMenu *)&main_menu,0x413,1);
                    menu_set_item_hidden((GameMenu *)&main_menu,0x442,1);
                    menu_set_item_hidden((GameMenu *)&main_menu,0x417,1);
                    menu_set_item_hidden((GameMenu *)&main_menu,0x418,1);
                    menu_set_item_hidden((GameMenu *)&main_menu,0x41b,1);
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
  menu_rebuild((GameMenu *)&main_menu,(iptr)((u8 *)&g.d_006553d8));
  menu_set_command_handler((GameMenu *)&main_menu,(iptr)menu_command);
  return;
}
#undef editor_disabled
#undef editor_checked
#undef cheat_checked
#undef cheat_disabled

/* 004e4c92 auto */
#define label_text (*(i8 (*)[80])(frame_ + FRAME_OFF(4)))
void __cdecl menu_set_item_label(i32 item_id,i32 label_id,i32 enabled)

{
  i8 frame_[FRAME_OFF(88)] __attribute__((aligned(8)));  /* original stack frame */
  
  text_clear();
  text_append_label(label_id);
  text_expand_vars((iptr)((u8 *)&g.d_00679640),(iptr)label_text);
  menu_set_item_text((GameMenu *)&main_menu,item_id,(iptr)label_text);
  menu_set_item_enabled((GameMenu *)&main_menu,item_id,enabled);
  return;
}
#undef label_text

/* 004e4ceb auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
#define mp_open_game (*(short *)((u8 *)&g.d_00654c74))
#define mp_turn_civ (*(i8 *)((u8 *)&g.d_006ad578))
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
#define mp_turn_civ_i32 (*(i32 *)((u8 *)&g.d_006ad578))
#define scenario_menu_disabled (*(i32 *)(frame_ + FRAME_OFF(0)))
#define scenario_checked (*(i32 *)(frame_ + FRAME_OFF(4)))
#define cheat_checked (*(i32 *)(frame_ + FRAME_OFF(8)))
#define cheat_menu_disabled (*(i32 *)(frame_ + FRAME_OFF(12)))
#define mine_disabled (*(i32 *)(frame_ + FRAME_OFF(16)))
#define irrigate_disabled (*(i32 *)(frame_ + FRAME_OFF(20)))
#define farmland_disabled (*(i32 *)(frame_ + FRAME_OFF(24)))
#define road_disabled (*(i32 *)(frame_ + FRAME_OFF(28)))
#define railroad_disabled (*(i32 *)(frame_ + FRAME_OFF(32)))
#define build_city_disabled (*(i32 *)(frame_ + FRAME_OFF(36)))
#define fortress_hidden (*(i32 *)(frame_ + FRAME_OFF(40)))
#define airbase_hidden (*(i32 *)(frame_ + FRAME_OFF(44)))
#define pillage_hidden (*(i32 *)(frame_ + FRAME_OFF(48)))
#define revolution_disabled (*(i32 *)(frame_ + FRAME_OFF(52)))
#define dir (*(iptr *)(frame_ + FRAME_OFF(104)))
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
  i8 frame_[FRAME_OFF(112)] __attribute__((aligned(8)));  /* original stack frame */
  
  menu_set_item_enabled((GameMenu *)&main_menu,0x606,game.rules & 0x80);
  if (game.multiplayer == '\0') {
    menu_set_item_enabled((GameMenu *)&main_menu,0x130,1);
    menu_set_item_enabled((GameMenu *)&main_menu,0x132,1);
    menu_set_item_enabled((GameMenu *)&main_menu,0x507,1);
    menu_set_item_enabled((GameMenu *)&main_menu,0x104,1);
    menu_set_item_enabled((GameMenu *)&main_menu,0x105,1);
    menu_set_item_enabled((GameMenu *)&main_menu,0x120,0);
    menu_set_item_enabled((GameMenu *)&main_menu,0x9f0,0);
  }
  else {
    menu_set_item_enabled((GameMenu *)&main_menu,0x9f0,1);
    menu_set_item_enabled((GameMenu *)&main_menu,0x104,0);
    menu_set_item_enabled((GameMenu *)&main_menu,0x105,0);
    if (mp_cheat_menu_allowed == 0) {
      menu_set_item_enabled((GameMenu *)&main_menu,0x701,1);
    }
    menu_set_item_enabled((GameMenu *)&main_menu,0x120,1);
    if ((mp_open_game == 0) || (game.multiplayer != 1)) {
      menu_set_item_enabled((GameMenu *)&main_menu,0x130,1);
    }
    else {
      menu_set_item_enabled((GameMenu *)&main_menu,0x130,0);
    }
    if (game.multiplayer == 1) {
      menu_set_item_enabled((GameMenu *)&main_menu,0x205,1);
    }
    else {
      menu_set_item_enabled((GameMenu *)&main_menu,0x205,0);
    }
    menu_set_item_enabled((GameMenu *)&main_menu,0x507,(uint)(game.multiplayer < 3));
    if (game.multiplayer == 2) {
      menu_set_item_enabled((GameMenu *)&main_menu,0x132,1);
      menu_set_item_enabled((GameMenu *)&main_menu,0x110,1);
    }
    else {
      if (net_host_flag == '\0') {
        menu_set_item_enabled((GameMenu *)&main_menu,0x132,1);
      }
      else {
        menu_set_item_enabled((GameMenu *)&main_menu,0x132,0);
      }
      menu_set_item_enabled((GameMenu *)&main_menu,0x110,0);
    }
    menu_set_item_enabled((GameMenu *)&main_menu,0x1f1,0);
    menu_set_item_enabled((GameMenu *)&main_menu,0x1f0,0);
  }
  menu_set_item_enabled((GameMenu *)&main_menu,0x302,(uint)(moving_units_mode == 0));
  menu_set_item_enabled((GameMenu *)&main_menu,0x301,(uint)(moving_units_mode == 1));
  if ((((game.game_flags & 0x80) == 0) || ((scenario_flags & 0x10) == 0)) &&
     (civs[human_civ].government != '\0')) {
    revolution_disabled = 0;
  }
  else {
    revolution_disabled = 1;
  }
  menu_set_item_enabled((GameMenu *)&main_menu,0x220,revolution_disabled);
  if (((moving_units_mode == 0) || (game.num_units == 0)) ||
     ((game.active_unit < 0 ||
      ((game.num_units < game.active_unit || (units[game.active_unit].id == 0)))))) {
    menu_set_menu_enabled((GameMenu *)&main_menu,4,1);
    menu_set_item_enabled((GameMenu *)&main_menu,0x460,0);
    menu_set_item_enabled((GameMenu *)&main_menu,0x468,0);
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
    menu_set_menu_enabled((GameMenu *)&main_menu,4,0);
    menu_set_item_hidden((GameMenu *)&main_menu,0x401,(uint)(unit_role != 5));
    menu_set_item_label(0x401,0x32,(uint)(unit_role != 5));
    menu_set_item_label(0x410,0x34,(uint)(unit_role != 5));
    menu_set_item_label(0x411,0x36,(uint)(unit_role != 5));
    menu_set_item_label(0x412,0x38,(uint)(unit_role != 5));
    menu_set_item_hidden((GameMenu *)&main_menu,0x450,(uint)(unit_role == 5));
    if ((unit_role == 5) && (has_airbase_tech = civ_has_advance(civ,0x12), has_airbase_tech != 0)) {
      pillage_hidden = 0;
    }
    else {
      pillage_hidden = 1;
    }
    menu_set_item_hidden((GameMenu *)&main_menu,0x418,pillage_hidden);
    if ((unit_role == 5) && (has_fortress_tech = civ_has_advance(civ,0x42), has_fortress_tech != 0)) {
      airbase_hidden = 0;
    }
    else {
      airbase_hidden = 1;
    }
    menu_set_item_hidden((GameMenu *)&main_menu,0x417,airbase_hidden);
    menu_set_item_hidden((GameMenu *)&main_menu,0x430,(uint)(unit_role == 5));
    menu_set_item_hidden((GameMenu *)&main_menu,0x41b,(uint)(unit_role != 5));
    city = civ_has_advance(civ,0xd);
    if ((city == 0) && ((unit_types[units[unit].type].flags & 0x100) == 0)) {
      fortress_hidden = 1;
    }
    else {
      fortress_hidden = 0;
    }
    menu_set_item_hidden((GameMenu *)&main_menu,0x441,fortress_hidden);
    menu_set_item_enabled
              ((GameMenu *)&main_menu,0x441,
               (uint)((unit_types[units[unit].type].flags & 0x100) == 0));
    city = civ_has_advance(civ,0x42);
    menu_set_item_hidden((GameMenu *)&main_menu,0x442,(uint)(city == 0));
    city = tile_city_owner(x,y);
    menu_set_item_enabled((GameMenu *)&main_menu,0x442,(uint)(city < 0));
    if (unit_role == 5) {
      no_adjacent_city = true;
      for (dir = 0; dir < 8; dir++) {
        x2 = map_wrap_x((char)(&dir_dx_table)[dir] + x);
        dy = (&dir_dy_table)[dir];
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
        menu_set_item_enabled((GameMenu *)&main_menu,0x401,build_city_disabled);
      }
      else {
        menu_set_item_label(0x401,0x33,(uint)('\t' < cities[city].size));
      }
      improvements2 = tile_improvements(x,y);
      if ((improvements2 & 0x80) == 0) {
        menu_set_item_enabled((GameMenu *)&main_menu,0x420,1);
      }
      improvements22 = tile_improvements(x,y);
      if ((((((byte)improvements22 & 0x42) == 0x40) ||
           (airbase_owner = tile_airbase_owner(x,y), -1 < airbase_owner)) || (is_ocean)) || (-1 < city)) {
        menu_set_item_enabled((GameMenu *)&main_menu,0x418,1);
      }
      improvements22 = tile_improvements(x,y);
      if (((((byte)improvements22 & 0x42) == 0x40) ||
          (airbase_owner2 = tile_airbase_owner(x,y), -1 < airbase_owner2)) || ((is_ocean || (-1 < city)))) {
        menu_set_item_enabled((GameMenu *)&main_menu,0x417,1);
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
        menu_set_item_enabled((GameMenu *)&main_menu,0x410,road_disabled);
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
          menu_set_item_enabled((GameMenu *)&main_menu,0x411,irrigate_disabled);
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
        menu_set_item_enabled((GameMenu *)&main_menu,0x412,mine_disabled);
      }
      else {
        text_set_label_arg(0,terrain_types[terrain2].name);
        menu_set_item_label(0x412,0x39,0);
      }
      civ = civ_can_build_unit(civ,-1,1);
      menu_set_item_hidden((GameMenu *)&main_menu,0x413,(uint)(civ == 0));
      if (terrain_types[terrain].transform_to < 0) {
        menu_set_item_enabled((GameMenu *)&main_menu,0x413,1);
      }
      else {
        text_set_label_arg(0,terrain_types[terrain_types[terrain].transform_to].name);
        menu_set_item_label(0x413,0x3c,(uint)(units[unit].type != 1));
      }
    }
    else {
      menu_set_item_enabled((GameMenu *)&main_menu,0x413,1);
      menu_set_item_enabled((GameMenu *)&main_menu,0x418,1);
      menu_set_item_enabled((GameMenu *)&main_menu,0x420,1);
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
              ((GameMenu *)&main_menu,0x430,(uint)(unit_types[units[unit].type].hold == '\0'))
    ;
    menu_set_item_hidden((GameMenu *)&main_menu,0x421,(uint)(unit_role == 5));
    if ((unit_types[units[unit].type].attack == '\0') ||
       (unit_types[units[unit].type].domain != '\0')) {
      menu_set_item_enabled((GameMenu *)&main_menu,0x421,1);
    }
  }
  if ((((*(i8 *)((char *)&game.game_options + 1)) & 0x80) == 0) || (game.multiplayer != '\0')) {
    cheat_menu_disabled = 1;
  }
  else {
    cheat_menu_disabled = 0;
  }
  menu_set_menu_enabled((GameMenu *)&main_menu,7,cheat_menu_disabled);
  if ((((*(i8 *)((char *)&game.game_options + 1)) & 0x80) == 0) || (game.multiplayer != '\0')) {
    cheat_checked = 0;
  }
  else {
    cheat_checked = 1;
  }
  menu_set_item_checked((GameMenu *)&main_menu,0x701,cheat_checked);
  menu_set_item_enabled
            ((GameMenu *)&main_menu,0x701,(uint)(game.multiplayer != '\0' && mp_cheat_menu_allowed == 0)
            );
  if ((2 < game.multiplayer) && (mp_turn_civ_i32 != human_civ)) {
    menu_set_menu_enabled((GameMenu *)&main_menu,4,1);
  }
  if ((((((*(i8 *)((char *)&game.game_options + 1)) & 0x80) == 0) || (game.multiplayer != '\0')) ||
      ((game.game_flags & 0x80) == 0)) ||
     (path_cmp = _strcmp(&scenario_dir_path,&game_home_dir), path_cmp == 0)) {
    scenario_checked = 0;
  }
  else {
    scenario_checked = 1;
  }
  menu_set_item_checked((GameMenu *)&main_menu,0x801,scenario_checked);
  if (((((*(i8 *)((char *)&game.game_options + 1)) & 0x80) == 0) || (game.multiplayer != '\0')) ||
     (((game.game_flags & 0x80) == 0 || (path_cmp2 = _strcmp(&scenario_dir_path,&game_home_dir), path_cmp2 == 0)
      ))) {
    scenario_menu_disabled = 1;
  }
  else {
    scenario_menu_disabled = 0;
  }
  menu_set_menu_enabled((GameMenu *)&main_menu,8,scenario_menu_disabled);
  menu_set_item_enabled((GameMenu *)&main_menu,0x801,(uint)(game.multiplayer != '\0'))
  ;
  menu_rebuild((GameMenu *)&main_menu,0);
  return;
}
#undef human_civ
#undef moving_units_mode
#undef mp_open_game
#undef mp_turn_civ
#undef net_host_flag
#undef scenario_flags
#undef mp_turn_civ_i32
#undef scenario_menu_disabled
#undef scenario_checked
#undef cheat_checked
#undef cheat_menu_disabled
#undef mine_disabled
#undef irrigate_disabled
#undef farmland_disabled
#undef road_disabled
#undef railroad_disabled
#undef build_city_disabled
#undef fortress_hidden
#undef airbase_hidden
#undef pillage_hidden
#undef revolution_disabled
#undef dir

/* 004e7240 auto */
void __thiscall wnd_show_restored(WndBase *this)

{
  wnd_obj_show_restored(this->native_wnd);
  return;
}

/* 004eb80a auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define city_notify_enabled (*(int *)((u8 *)&g.d_006a65ac))
#define city_zoom_requested (*(int *)((u8 *)&g.d_006a65a0))
#define picture_id (*(uint *)(frame_ + FRAME_OFF(0)))
#define popup_new (*(void * *)(frame_ + FRAME_OFF(16)))
#define sprite (*(Sprite *)(frame_ + FRAME_OFF(36)))
#define popup (*(void * *)(frame_ + FRAME_OFF(96)))
#define palette (*(GamePalette *)(frame_ + FRAME_OFF(100)))
#define eh_prev (*(i32 *)(frame_ + FRAME_OFF(1176)))
#define eh_handler (*(i8 * *)(frame_ + FRAME_OFF(1180)))
#define eh_state (*(uint *)(frame_ + FRAME_OFF(1184)))
int __cdecl popup_city_picture_zoom(iptr section,iptr city,uint picture,int silent,iptr civ)

{
  ViewWindow *this;
  int result;
  i32 height;
  i32 width;
  iptr option_text;
  iptr option_id;
  i8 frame_[FRAME_OFF(1192)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  palette_init(&palette);
  eh_state = 0;
  sprite_init(&sprite);
  (*(i8 *)((char *)&eh_state + 0)) = 1;
  if (autoplay_active == 0) {
    if (silent == 0) {
      if (city_notify_enabled == 0) {
        eh_state = (uint)(*(i32 *)((char *)&eh_state + 1)) << 8;
        /* inlined unwind funclet 004ebbad */ { sprite_destroy((Sprite *)((iptr)&sprite)); }
        eh_state = 0xffffffff;
        /* inlined unwind funclet 004ebbb9 */ { palette_destroy((GamePalette *)((iptr)&palette)); }
        result = 0;
        goto LAB_004ebbcf;
      }
      civ = (iptr)cities[city].owner;
      mapviews_ensure_visible((int)cities[city].x,(int)cities[city].y,civ);
      text_set_string_arg_b(0,(iptr)&cities[city].name);
    }
    this = operator_new(0x798);
    (*(i8 *)((char *)&eh_state + 0)) = 2;
    if (this == (ViewWindow *)0x0) {
      popup_new = (void *)0x0;
    }
    else {
      popup_new = (void *)city_picture_popup_ctor(this);
    }
    eh_state = CONCAT31((*(i32 *)((char *)&eh_state + 1)),1);
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
    if ((silent == 0) && (city_zoom_requested == 0)) {
      height = 0;
      option_id = 1;
      option_text = label_string(*(i32 *)(label_string_ids + 0x80));
      dialog_add_option
                ((DialogOptionList *)((int)popup + 0x4a4),option_text,option_id,height);
      height = 0;
      option_id = 0;
      option_text = label_string(*(i32 *)(label_string_ids + 0x84));
      dialog_add_option
                ((DialogOptionList *)((int)popup + 0x4a4),option_text,option_id,height);
      if ((game.message_options & 0x400) == 0) {
        dialog_set_default_choice((DialogOptionList *)((int)popup + 0x4a4),0);
      }
      else {
        dialog_set_default_choice((DialogOptionList *)((int)popup + 0x4a4),1);
      }
    }
    result = dlg_show_modal((Dialog *)((int)popup + 0x4a4),0);
    if ((silent == 0) && (0 < result)) {
      city_zoom_requested = 1;
    }
    if (popup != (void *)0x0) {
      city_picture_popup_scalar_dtor(popup,1);
    }
    eh_state = eh_state & 0xffffff00;
    /* inlined unwind funclet 004ebbad */ { sprite_destroy((Sprite *)((iptr)&sprite)); }
    eh_state = 0xffffffff;
    /* inlined unwind funclet 004ebbb9 */ { palette_destroy((GamePalette *)((iptr)&palette)); }
  }
  else {
    eh_state = (uint)(*(i32 *)((char *)&eh_state + 1)) << 8;
    /* inlined unwind funclet 004ebbad */ { sprite_destroy((Sprite *)((iptr)&sprite)); }
    eh_state = 0xffffffff;
    /* inlined unwind funclet 004ebbb9 */ { palette_destroy((GamePalette *)((iptr)&palette)); }
    result = 0;
  }
LAB_004ebbcf:
  return result;
}
#undef autoplay_active
#undef city_notify_enabled
#undef city_zoom_requested
#undef picture_id
#undef popup_new
#undef sprite
#undef popup
#undef palette
#undef eh_prev
#undef eh_handler
#undef eh_state

/* 00511320 auto */
u32 __thiscall wnd_get_palette(WndPaletteView *this)

{
  return this->wnd_palette;
}

/* 00511460 auto */
void __thiscall
hotspot_add_rect(ClickMap *this,iptr id,i32 cursor,iptr rect)

{
  clickmap_add(this,id,cursor,*(i32 *)rect,*(i32 *)(rect + 4),
                     *(int *)(rect + 8) - *(int *)rect,
                     *(int *)(rect + 0xc) - *(int *)(rect + 4));
  return;
}

/* 00511520 auto */
i32 __cdecl popup_game_with_city_flags(iptr section,i32 city,i32 flags)

{
  i32 result;
  
  result = popup_text_with_city((iptr)((u8 *)&g.d_006359d4),section,city,flags);
  return result;
}

/* 00511820 auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall frame_wnd_set_title_font(FrameWindow *this,iptr font)

{
  this->title_font = font;
  return;
}

/* 00511850 auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall frame_wnd_set_title_small_font(FrameWindow *this,iptr font)

{
  this->title_small_font = font;
  return;
}

/* 00518e80 auto */
void __thiscall wnd_move_xy(WndMoveView *this,i32 x,i32 y)

{
  wnd_obj_move_xy(this->native_wnd,x,y);
  return;
}

/* 00518ec0 auto */
i32 __cdecl dlg_input_number_game(iptr section,i32 initial,iptr out_value)

{
  i32 result;
  
  result = dlg_input_number((iptr)((u8 *)&g.d_006359d4),section,initial,out_value);
  return result;
}

/* 0051d3e0 auto */
#define dlg_check_bits (*(uint *)((u8 *)&g.d_00631ed8))
#define dlg_help_pressed (*(u32 *)((u8 *)&g.d_00631edc))
#define dialog2 (*(Dialog *)(frame_ + FRAME_OFF(0)))
#define i (*(int *)(frame_ + FRAME_OFF(756)))
#define eh_prev (*(i32 *)(frame_ + FRAME_OFF(760)))
#define eh_handler (*(i8 * *)(frame_ + FRAME_OFF(764)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(768)))
i32 __cdecl
popup_text_run(iptr file,iptr section,i32 result,i32 arg4,i32 arg5,
            i32 arg6,i32 arg7)

{
  int status;
  i8 frame_[FRAME_OFF(776)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  dialog_ctor(&dialog2,0x4000);
  eh_state = 0;
  status = dialog_load_text_section
                    (&dialog2,file,section,result,0,arg4,arg5,arg6,arg7);
  if (status == 0) {
    if (((byte)dialog2.style_flags & 4) != 0) {
      for (i = 0; i < (int)dialog2.option_count; i++) {
        dialog_set_option_checked
                  ((DialogOptionList *)&dialog2,i,1 << ((byte)i & 0x1f) & dlg_check_bits
                  );
      }
    }
    result = dlg_show_modal(&dialog2,0);
    dlg_help_pressed = dialog2.result_extra;
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
  /* inlined unwind funclet 0051d53f */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
  return result;
}
#undef dlg_check_bits
#undef dlg_help_pressed
#undef dialog2
#undef i
#undef eh_prev
#undef eh_handler
#undef eh_state

/* 0051d564 auto */
#define dlg_help_pressed (*(u32 *)((u8 *)&g.d_00631edc))
#define dialog2 (*(Dialog *)(frame_ + FRAME_OFF(4)))
#define eh_prev (*(i32 *)(frame_ + FRAME_OFF(760)))
#define eh_handler (*(i8 * *)(frame_ + FRAME_OFF(764)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(768)))
i32 __cdecl
popup_text_with_sprite(iptr file,iptr section,i32 flags,iptr sprite,i32 zoom)

{
  i32 result;
  i8 frame_[FRAME_OFF(776)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  dialog_ctor(&dialog2,0x4000);
  eh_state = 0;
  dialog_load_text(&dialog2,file,section,flags);
  dialog_add_sprite((DialogOptionList *)&dialog2,sprite,0,0);
  dialog_set_image_zoom((DialogWindowView *)&dialog2,zoom);
  result = dlg_show_modal(&dialog2,0);
  dlg_help_pressed = dialog2.result_extra;
  eh_state = 0xffffffff;
  /* inlined unwind funclet 0051d616 */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
  return result;
}
#undef dlg_help_pressed
#undef dialog2
#undef eh_prev
#undef eh_handler
#undef eh_state

/* 0051d63b auto */
#define result (*(i32 *)(frame_ + FRAME_OFF(4)))
#define dialog2 (*(Dialog *)(frame_ + FRAME_OFF(8)))
#define p (*(char * *)(frame_ + FRAME_OFF(764)))
#define eh_prev (*(i32 *)(frame_ + FRAME_OFF(768)))
#define eh_handler (*(i8 * *)(frame_ + FRAME_OFF(772)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(776)))
i32 __cdecl
dlg_text_input(iptr file,iptr section,i32 max_len,iptr initial_text,iptr out_text)

{
  int status;
  i8 frame_[FRAME_OFF(784)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  result = 0;
  dialog_ctor(&dialog2,0x4000);
  eh_state = 0;
  str_clear(out_text);
  status = dialog_load_text_section(&dialog2,file,section,max_len,initial_text,0,0,0,1);
  if (status == 0) {
    result = dialog_run_modal(&dialog2,out_text,0);
    for (p = (char *)out_text;
        (*p != '\0' && ((*p == ' ' || (*p == '\t')))); p++)
    {
      *p = '_';
    }
  }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 0051d738 */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
  return result;
}
#undef result
#undef dialog2
#undef p
#undef eh_prev
#undef eh_handler
#undef eh_state

/* 0051d75d auto */
#define input_text (*(char (*)[260])(frame_ + FRAME_OFF(0)))
#define initial_text (*(char (*)[20])(frame_ + FRAME_OFF(260)))
#define result (*(i32 *)(frame_ + FRAME_OFF(280)))
i32 __cdecl dlg_input_number(iptr file,iptr section,int initial,iptr out_value)

{
  long value;
  i8 frame_[FRAME_OFF(288)] __attribute__((aligned(8)));  /* original stack frame */
  
  __itoa(initial,initial_text,10);
  result = dlg_text_input(file,section,5,(iptr)initial_text,(iptr)input_text);
  value = _atol(input_text);
  *(long *)out_value = value;
  return result;
}
#undef input_text
#undef initial_text
#undef result

/* 0051d7bc auto */
#define dlg_check_bits (*(i32 *)((u8 *)&g.d_00631ed8))
void __cdecl dlg_checks_clear(void)

{
  dlg_check_bits = 0;
  return;
}
#undef dlg_check_bits

/* 0051d7d6 auto */
#define dlg_check_bits (*(uint *)((u8 *)&g.d_00631ed8))
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
#undef dlg_check_bits

/* 0051d817 auto */
#define dlg_check_bits (*(uint *)((u8 *)&g.d_00631ed8))
uint __cdecl dlg_check_get(i32 index)

{
  return 1 << ((byte)index & 0x1f) & dlg_check_bits;
}
#undef dlg_check_bits

/* 0052182c auto */
#define title (*(char (*)[128])(frame_ + FRAME_OFF(4)))
void __cdecl dialog_prepend_title_label(iptr dialog,i32 label_id)

{
  size_t len;
  i32 buffer;
  i8 frame_[FRAME_OFF(136)] __attribute__((aligned(8)));  /* original stack frame */
  
  title[0] = '\0';
  str_append_label((iptr)title,label_id);
  if (*(int *)(dialog + 0x134) != 0) {
    crt_strcat(title,&dialog_title_label_space_str);
    crt_strcat(title,*(i32 *)(dialog + 0x134));
  }
  len = _strlen(title);
  buffer = memblock_alloc(dialog + 0x254,len + 1);
  *(i32 *)(dialog + 0x134) = buffer;
  crt_strcpy(*(i32 *)(dialog + 0x134),title);
  return;
}
#undef title

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
i32 __cdecl popup_game_ex(iptr section,i32 arg2,i32 arg3)

{
  i32 result;
  
  result = popup_text_ex((iptr)((u8 *)&g.d_006359d4),section,arg2,arg3);
  return result;
}

/* 00551e60 auto */
i32 __cdecl popup_debug_ex(iptr section,i32 arg2,i32 arg3)

{
  i32 result;
  
  result = popup_text_ex((iptr)((u8 *)&g.d_006359dc),section,arg2,arg3);
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
  font_init((GameFont *)&caption_font,0,0x10);
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
  font_destroy((GameFont *)&caption_font);
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
  font_init((GameFont *)&caption_small_font,0,10);
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
  font_destroy((GameFont *)&caption_small_font);
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
  font_init((GameFont *)&ui_text_font,0,0x10);
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
  font_destroy((GameFont *)&ui_text_font);
  return;
}

/* 00551fed auto */
#define frame_border_width (*(int *)((u8 *)&g.d_0063359c))
#define frame_caption_height (*(int *)((u8 *)&g.d_00633598))
#define screen_height (*(i32 *)((u8 *)&g.d_006ab19c))
#define ui_large_screen (*(uint *)((u8 *)&g.d_00633584))
void __cdecl ui_init_screen_metrics(void)

{
  int metric;
  
  gfx_get_screen_rect((iptr)((u8 *)&g.d_006ab180));
  screen_width = rect_width((iptr)((u8 *)&g.d_006ab180));
  screen_height = rect_height((iptr)((u8 *)&g.d_006ab180));
  ui_font_height = 0x10;
  if (999 < screen_width) {
    ui_font_height = 0x18;
  }
  ui_large_screen = (uint)(999 < screen_width);
  font_set((GameFont *)&caption_font,0,ui_font_height);
  font_set((GameFont *)&caption_small_font,0,(ui_font_height * 2) / 3);
  font_set((GameFont *)&ui_text_font,0,ui_font_height);
  metric = font_cached_height((GameFont *)&caption_font);
  frame_caption_height = metric + frame_padding * 2 + frame_bevel_width * 2;
  frame_border_width = frame_bevel_width * 2 + frame_padding * 2;
  metric = GetSystemMetrics(7);
  sys_dlgframe_w2 = metric * 2;
  metric = GetSystemMetrics(8);
  sys_dlgframe_h2 = metric * 2;
  return;
}
#undef frame_border_width
#undef frame_caption_height
#undef screen_height
#undef ui_large_screen

/* 005520fa auto */
void __cdecl frame_set_border_tile(iptr tile)

{
  frame_border_tile = tile;
  return;
}

/* 00552112 auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define autoplay_turns_left (*(short *)((u8 *)&g.d_00654faa))
#define frame_border_width (*(int *)((u8 *)&g.d_0063359c))
#define hotseat_human_players (*(byte *)((u8 *)&g.d_006c31a9))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define mp_simultaneous_moves (*(char *)((u8 *)&g.d_006ad684))
#define mp_turn_civ (*(byte *)((u8 *)&g.d_006ad578))
#define mp_turn_seconds_left (*(u32 *)((u8 *)&g.d_00633a78))
#define mp_turn_time_limit_ms (*(int *)((u8 *)&g.d_00654b70))
#define mp_turn_civ_i32 (*(i32 *)((u8 *)&g.d_006ad578))
#define caption_h2 (*(u32 *)(frame_ + FRAME_OFF(0)))
#define caption_h (*(u32 *)(frame_ + FRAME_OFF(4)))
#define sprite_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(8)))
#define minutes (*(int *)(frame_ + FRAME_OFF(24)))
#define seconds (*(int *)(frame_ + FRAME_OFF(28)))
#define height2 (*(int *)(frame_ + FRAME_OFF(32)))
#define bevel (*(int *)(frame_ + FRAME_OFF(36)))
#define shadow_color2 (*(i32 *)(frame_ + FRAME_OFF(40)))
#define text_width (*(int *)(frame_ + FRAME_OFF(44)))
#define width2 (*(int *)(frame_ + FRAME_OFF(48)))
#define button_y2 (*(int *)(frame_ + FRAME_OFF(52)))
#define button_x (*(int *)(frame_ + FRAME_OFF(56)))
#define offset (*(int *)(frame_ + FRAME_OFF(60)))
#define font2 (*(GameFont * *)(frame_ + FRAME_OFF(64)))
#define text_y2 (*(int *)(frame_ + FRAME_OFF(68)))
#define highlight_color2 (*(i32 *)(frame_ + FRAME_OFF(72)))
#define text_x2 (*(int *)(frame_ + FRAME_OFF(76)))
#define i (*(int *)(frame_ + FRAME_OFF(80)))
#define caption (*(char (*)[256])(frame_ + FRAME_OFF(84)))
#define rect_left2 (*(u32 *)(frame_ + FRAME_OFF(340)))
#define rect_top2 (*(u32 *)(frame_ + FRAME_OFF(344)))
#define rect_right2 (*(u32 *)(frame_ + FRAME_OFF(348)))
#define rect_bottom2 (*(u32 *)(frame_ + FRAME_OFF(352)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall frame_wnd_draw_caption(FrameWindow *this)

{
  i32 adjective;
  int title_height;
  int small_height;
  uptr len;
  uptr len2;
  i8 frame_[FRAME_OFF(360)] __attribute__((aligned(8)));  /* original stack frame */
  
  surface_reset_clip((DibSurface *)this);
  highlight_color2 = frame_highlight_color;
  shadow_color2 = frame_shadow_color;
  bevel = frame_bevel_width;
  if (this->caption_height == 0) {
    caption_h = this->border_width;
  }
  else {
    caption_h = this->caption_height;
  }
  height2 = caption_h + frame_bevel_width * -2;
  width2 = rect_width((iptr)&this->frame_rect);
  gfx_tile_fill((iptr)this,frame_border_tile,0,bevel,width2,height2,0,bevel);
  height2 = this->border_width + bevel * -2;
  offset = rect_height((iptr)&this->frame_rect);
  offset -= (bevel + height2);
  gfx_tile_fill((iptr)this,frame_border_tile,0,offset,width2,height2,0,offset);
  width2 = this->border_width + bevel * -2;
  height2 = rect_height((iptr)&this->frame_rect);
  gfx_tile_fill((iptr)this,frame_border_tile,bevel,0,width2,height2,bevel,0);
  offset = rect_width((iptr)&this->frame_rect);
  offset -= (bevel + width2);
  gfx_tile_fill((iptr)this,frame_border_tile,offset,0,width2,height2,offset,0);
  rect_left2 = this->frame_rect;
  rect_top2 = this->frame_top;
  rect_right2 = this->frame_right;
  rect_bottom2 = this->frame_bottom;
  for (i = 0; i < bevel; i++) {
    gfx_draw_bevel_rect((iptr)this,(iptr)&rect_left2,highlight_color2,shadow_color2);
    rect_deflate((iptr)&rect_left2,1,1);
  }
  rect_deflate((iptr)&rect_left2,this->border_width + bevel * -2,0);
  if (this->caption_height == 0) {
    caption_h2 = this->border_width;
  }
  else {
    caption_h2 = this->caption_height;
  }
  rect_top2 = rect_top2 + caption_h2 + bevel * -2;
  rect_bottom2 -= (this->border_width + bevel * -2);
  for (i = 0; i < bevel; i++) {
    gfx_draw_bevel_rect((iptr)this,(iptr)&rect_left2,shadow_color2,highlight_color2);
    rect_deflate((iptr)&rect_left2,1,1);
  }
  button_x = frame_border_width;
  for (i = 0; i < (int)this->caption_button_count; i++) {
    width2 = (int)(*(int *)(this->pane_selection_flags_area + i * 0x1c + 0xc) * this->caption_height) / 0x18;
    height2 = (int)(*(int *)(this->pane_selection_flags_area + i * 0x1c + 0x10) * this->caption_height) / 0x18;
    button_y2 = ((int)this->caption_height >> 1) - (height2 >> 1);
    rect_set_xywh((iptr)&rect_left2,button_x,button_y2,width2,height2);
    gfx_set_scale_ratio(this->caption_height,0x18);
    sprite_draw
              (*(Sprite **)(this->pane_selection_flags_area + i * 0x1c + 0x14),(iptr)sprite_rect,
               (iptr)this,button_x,button_y2);
    gfx_reset_zoom_scale();
    button_x = button_x + width2 + frame_padding;
  }
  if ((autoplay_active == 0) || (this->show_turn_status == 0)) {
    if ((((uint)game.human_players & 1 << (game.turn_civ & 0x1fU)) == 0) || (this->show_turn_timer == 0))
    {
      this->timer_text = '\0';
    }
    else if (this->timer_last_value != mp_turn_seconds_left) {
      if (this->timer_last_value == 0xffffffff) {
        this->timer_last_value = mp_turn_time_limit_ms / 1000;
      }
      else {
        this->timer_last_value = mp_turn_seconds_left;
      }
      if ((int)this->timer_last_value < 0) {
        this->timer_last_value = 0;
      }
      minutes = (int)(this->timer_last_value - 1) / 0x3c;
      seconds = (this->timer_last_value - 1) + minutes * -0x3c;
      if (minutes < 10) {
        this->timer_text = '0';
        __itoa(minutes,(char *)this->timer_minutes_text,10);
      }
      else {
        __itoa(minutes,(char *)&this->timer_text,10);
      }
      this->timer_colon = ':';
      if (seconds < 10) {
        if (seconds < 0) {
          seconds = 0;
        }
        this->timer_seconds_text = '0';
        __itoa(seconds,(char *)this->timer_seconds_digits,10);
      }
      else {
        __itoa(seconds,(char *)&this->timer_seconds_text,10);
      }
    }
  }
  else if ((int)autoplay_turns_left != this->timer_last_value) {
    this->timer_last_value = (int)autoplay_turns_left;
    __itoa((int)autoplay_turns_left,(char *)&this->timer_text,10);
  }
  crt_strcpy(caption,this->frame_title);
  if (((this->show_turn_status == 0) || (game.multiplayer == '\0')) || (mp_simultaneous_moves != '\0')) {
    if (((this->show_turn_status != 0) && (game.multiplayer != '\0')) && (mp_simultaneous_moves != '\0')) {
      if ((1 << (mp_turn_civ & 0x1f) & (uint)game.human_players) == 0) {
        crt_strcat(caption,&caption_simul_open_paren_str);
        if (game_language == 1) {
          crt_strcat(caption,&caption_simul_ai_fr_str);
        }
        else {
          crt_strcat(caption,&caption_simul_ai_str);
        }
        crt_strcat(caption,&caption_simul_space_str);
        str_append_label((iptr)caption,0x369);
        if (this->timer_text != '\0') {
          crt_strcat(caption,&caption_simul_timer_sep_str);
          crt_strcat(caption,&this->timer_text);
        }
        crt_strcat(caption,&caption_simul_close_paren_str);
      }
      else if (this->timer_text != '\0') {
        crt_strcat(caption,&caption_timer_open_paren_str);
        crt_strcat(caption,&this->timer_text);
        crt_strcat(caption,&caption_timer_close_paren_str);
      }
    }
  }
  else {
    crt_strcat(caption,&caption_status_open_paren_str);
    if ((((*(byte *)&civs[human_civ].treaties[mp_turn_civ_i32] & 1) == 0) &&
        (mp_turn_civ_i32 != human_civ)) &&
       ((game.multiplayer != 1 || ((1 << (mp_turn_civ & 0x1f) & (uint)hotseat_human_players) == 0)))) {
      if ((1 << (mp_turn_civ & 0x1f) & (uint)game.human_players) == 0) {
        if (game_language == 1) {
          crt_strcat(caption,&caption_ai_fr_str);
        }
        else {
          crt_strcat(caption,&caption_ai_str);
        }
        if (autoplay_active == 0) {
          this->timer_text = '\0';
        }
      }
      else {
        crt_strcat(caption,&net_slot_player_names + *(int *)(&net_civ_slots + mp_turn_civ_i32 * 4) * 0x54);
      }
    }
    else {
      adjective = civ_adjective(mp_turn_civ_i32);
      crt_strcat(caption,adjective);
      if (((1 << (mp_turn_civ & 0x1f) & (uint)game.human_players) == 0) && (autoplay_active == 0)) {
        this->timer_text = '\0';
      }
    }
    crt_strcat(caption,&caption_moves_space_str);
    str_append_label((iptr)caption,0x369);
    if (this->timer_text != '\0') {
      crt_strcat(caption,&caption_timer_sep_str);
      crt_strcat(caption,&this->timer_text);
    }
    crt_strcat(caption,&caption_close_paren_str);
  }
  width2 = rect_width((iptr)&this->frame_rect);
  text_width = font_text_width((GameFont *)this->title_font,(iptr)caption);
  text_width += 4;
  text_x2 = (width2 >> 1) - (text_width >> 1);
  text_y2 = bevel + 1;
  font2 = (GameFont *)this->title_font;
  if (text_x2 < button_x) {
    text_x2 = button_x;
  }
  if (width2 < text_width + text_x2) {
    font2 = (GameFont *)this->title_small_font;
    text_width = font_text_width(font2,(iptr)caption);
    text_width += 4;
    text_x2 = (width2 >> 1) - (text_width >> 1);
    if (text_x2 < button_x) {
      text_x2 = button_x;
    }
    title_height = font_cached_height((GameFont *)this->title_font);
    small_height = font_cached_height(font2);
    text_y2 += (title_height - small_height >> 1);
    while ((len = _strlen(caption), len != 0 &&
           (title_height = font_text_width(font2,(iptr)caption),
           width2 < text_x2 + title_height + 4))) {
      len2 = _strlen(caption);
      caption[len2 - 1] = '\0';
    }
  }
  gfx_set_text_color_index(10);
  surface_draw_text
            ((DibSurface *)this,(iptr)font2,(iptr)caption,text_x2 + 2,text_y2 + 1,5);
  gfx_set_text_color_index(0x1a);
  surface_draw_text
            ((DibSurface *)this,(iptr)font2,(iptr)caption,text_x2 + 1,text_y2,5);
  surface_draw_text
            ((DibSurface *)this,(iptr)font2,(iptr)caption,text_x2,text_y2,5);
  surface_set_clip((DibSurface *)this,(iptr)&this->client_rect);
  return;
}
#undef autoplay_active
#undef autoplay_turns_left
#undef frame_border_width
#undef hotseat_human_players
#undef human_civ
#undef mp_simultaneous_moves
#undef mp_turn_civ
#undef mp_turn_seconds_left
#undef mp_turn_time_limit_ms
#undef mp_turn_civ_i32
#undef caption_h2
#undef caption_h
#undef sprite_rect
#undef minutes
#undef seconds
#undef height2
#undef bevel
#undef shadow_color2
#undef text_width
#undef width2
#undef button_y2
#undef button_x
#undef offset
#undef font2
#undef text_y2
#undef highlight_color2
#undef text_x2
#undef i
#undef caption
#undef rect_left2
#undef rect_top2
#undef rect_right2
#undef rect_bottom2

/* 00552e5b auto */
#define frame_wnd (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl frame_wnd_on_caption_button_click(int button_id)

{
  iptr child;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  child = wnd_get_active_child();
  if (child == 0) {
    frame_wnd = 0;
  }
  else {
    frame_wnd = child - 0x48;
  }
  if (*(int *)(frame_wnd + 0x2a8) != 0) {
    (*((code **)(frame_wnd))[170])(*(i32 *)(frame_wnd + 0x200 + (button_id - 1000) * 0x1c));
  }
  return;
}
#undef frame_wnd

/* 00552ed2 auto */
#define frame_border_width (*(int *)((u8 *)&g.d_0063359c))
#define native_wnd2 (*(u8 * *)(frame_ + FRAME_OFF(0)))
#define hotspot (*(i32 *)(frame_ + FRAME_OFF(4)))
#define button_x (*(int *)(frame_ + FRAME_OFF(24)))
#define i (*(int *)(frame_ + FRAME_OFF(28)))
#define button_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(32)))
#define eh_prev (*(i32 *)(frame_ + FRAME_OFF(48)))
#define eh_handler (*(i8 * *)(frame_ + FRAME_OFF(52)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(56)))
void __thiscall frame_wnd_layout(FrameWindow *this)

{
  int width;
  int height;
  u32 size;
  Control *this_00;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  width = surface_get_width((DibSurface *)this);
  height = surface_get_height((DibSurface *)this);
  rect_set_xywh((iptr)&this->frame_rect,0,0,width,height);
  rect_set_xywh((iptr)&this->client_rect,0,0,width + this->border_width * -2,
                     height - (this->caption_height + this->border_width));
  rect_offset((iptr)&this->client_rect,this->border_width,this->caption_height);
  this->client_x = this->client_rect;
  this->client_y = this->client_top;
  size = rect_width((iptr)&this->client_rect);
  this->client_width = size;
  size = rect_height((iptr)&this->client_rect);
  this->client_height = size;
  frame_wnd_destroy_caption_buttons((WindowObjectView *)this);
  button_x = frame_border_width;
  for (i = 0; i < (int)this->caption_button_count; i++) {
    width = (int)(*(int *)(this->pane_selection_flags_area + i * 0x1c + 0xc) * this->caption_height) / 0x18;
    height = (int)(*(int *)(this->pane_selection_flags_area + i * 0x1c + 0x10) * this->caption_height) / 0x18;
    rect_set_xywh((iptr)button_rect,button_x,((int)this->caption_height >> 1) - (height >> 1),width,
                       height);
    this_00 = operator_new(0x40);
    eh_state = 0;
    if (this_00 == (Control *)0x0) {
      hotspot = 0;
    }
    else {
      hotspot = hotspot_ctor(this_00);
    }
    eh_state = 0xffffffff;
    *(i32 *)(this->pane_selection_flags_area + i * 0x1c + 0x18) = hotspot;
    if (this == (FrameWindow *)0x0) {
      native_wnd2 = (u8 *)0x0;
    }
    else {
      native_wnd2 = this->window_2;
    }
    hotspot_create
              (*(ClickControl **)(this->pane_selection_flags_area + i * 0x1c + 0x18),(iptr)native_wnd2,
               i + 1000,(iptr)button_rect);
    hotspot_set_click_callback
              (*(HotspotClickSetView **)(this->pane_selection_flags_area + i * 0x1c + 0x18),(iptr)frame_wnd_on_caption_button_click);
    button_x = button_x + width + frame_padding;
  }
  return;
}
#undef frame_border_width
#undef native_wnd2
#undef hotspot
#undef button_x
#undef i
#undef button_rect
#undef eh_prev
#undef eh_handler
#undef eh_state

/* 0055318c auto */
void __thiscall frame_wnd_add_caption_button(PortraitDialog *this,iptr sprite,i32 callback)

{
  u8 *slot;
  u32 index;
  i32 dim;
  
  if ((int)this->caption_button_count < 6) {
    index = this->caption_button_count;
    this->caption_button_count++;
    *(iptr *)(((FrameWindow *)this)->close_caption_sprite_slot + index * 0x1c - 0x3c) = sprite;
    *(i32 *)(this->pane_selection_flags_area + index * 0x1c) = callback;
    dim = sprite_width((Sprite *)sprite);
    *(i32 *)(((FrameWindow *)this)->close_caption_sprite_slot + index * 0x1c - 0x44) = dim;
    dim = sprite_height((Sprite *)sprite);
    *(i32 *)(((FrameWindow *)this)->close_caption_sprite_slot + index * 0x1c - 0x40) = dim;
    slot = ((FrameWindow *)this)->close_caption_sprite_slot + index * 0x1c - 0x38;
    slot[0] = '\0';
    slot[1] = '\0';
    slot[2] = '\0';
    slot[3] = '\0';
  }
  return;
}

/* 0055324c auto */
#define rect_left2 (*(u32 *)(frame_ + FRAME_OFF(4)))
#define rect_top2 (*(u32 *)(frame_ + FRAME_OFF(8)))
#define rect_right2 (*(u32 *)(frame_ + FRAME_OFF(12)))
#define rect_bottom2 (*(u32 *)(frame_ + FRAME_OFF(16)))
void __thiscall frame_wnd_set_caption(FrameWindow *this,iptr title)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  _memset(this->frame_title,0,0x84);
  _strncpy((char *)this->frame_title,(char *)title,0x83);
  frame_wnd_draw_caption(this);
  rect_left2 = this->frame_rect;
  rect_top2 = this->frame_top;
  rect_right2 = this->frame_right;
  rect_bottom2 = this->client_top;
  wnd_blit_surface_rect((DibSurface *)this,(iptr)&rect_left2);
  return;
}
#undef rect_left2
#undef rect_top2
#undef rect_right2
#undef rect_bottom2

/* 005532d7 auto */
#define i (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall frame_wnd_destroy_caption_buttons(WindowObjectView *this)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (i = 0; i < 6; i++) {
    if (((u32 *)&((PediaRedrawView *)this)->caption_button_slots)[i * 7] != 0) {
      if ((Hotspot *)((u32 *)&((PediaRedrawView *)this)->caption_button_slots)[i * 7] != (Hotspot *)0x0) {
        hotspot_scalar_dtor((Hotspot *)((u32 *)&((PediaRedrawView *)this)->caption_button_slots)[i * 7],1);
      }
      ((u32 *)&((PediaRedrawView *)this)->caption_button_slots)[i * 7] = 0;
    }
  }
  return;
}
#undef i

/* 00553379 auto */
void __thiscall frame_wnd_close(DibSurface *this)

{
  frame_wnd_destroy_caption_buttons((WindowObjectView *)this);
  wnd_destroy_with_surface(this);
  return;
}

/* 0055339f auto */
#define i (*(int *)(frame_ + FRAME_OFF(4)))
#define eh_prev (*(i32 *)(frame_ + FRAME_OFF(8)))
#define eh_handler (*(i8 * *)(frame_ + FRAME_OFF(12)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(16)))
SurfaceWindow * __thiscall frame_wnd_ctor(SurfaceWindow *this)

{
  u8 *slot;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  surfwnd_ctor(this);
  this->vtable = (u32)&PTR_FUN_0061d6dc;
  for (i = 0; i < 6; i++) {
    slot = (u8 *)&((PediaRedrawView *)this)->caption_button_slots + i * 0x1c;
    slot[0] = '\0';
    slot[1] = '\0';
    slot[2] = '\0';
    slot[3] = '\0';
  }
  return this;
}
#undef i
#undef eh_prev
#undef eh_handler
#undef eh_state

/* 00553444 auto */
#define eh_prev (*(i32 *)(frame_ + FRAME_OFF(0)))
#define eh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    public: virtual __thiscall COleCntrFrameWnd::~COleCntrFrameWnd(void)
   
   Library: Visual Studio 1998 Debug */

void __thiscall frame_wnd_dtor(DibSurface *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  this->vtable = (u32)&PTR_FUN_0061d6dc;
  eh_state = 0;
  frame_wnd_destroy_caption_buttons((WindowObjectView *)this);
  wnd_destroy_with_surface(this);
  eh_state = 0xffffffff;
  /* inlined unwind funclet 0055349b */ { surfwnd_dtor(*(SurfaceWindow **)((iptr)&this)); }
  return;
}
#undef eh_prev
#undef eh_handler
#undef eh_state

/* 005534bc auto */
#define frame_border_width (*(u32 *)((u8 *)&g.d_0063359c))
#define frame_caption_height (*(u32 *)((u8 *)&g.d_00633598))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define wnd_style (*(uint *)(frame_ + FRAME_OFF(0)))
void __thiscall
frame_wnd_create
          (FrameWindow *this,int title,uint flags,int x,int y,int width,
          int height,u32 resize_width,u32 caption_h,u32 border_w)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (title == 0) {
    crt_strcpy(this->frame_title,&frame_default_title_str);
  }
  else {
    crt_strcpy(this->frame_title,title);
  }
  *(i8 **)this->editor_combo_boxes = &ui_text_font;
  this->title_font = (uptr)&caption_font;
  this->title_small_font = (uptr)&caption_small_font;
  this->show_turn_timer = 0;
  this->show_turn_status = 0;
  this->style_flags = flags;
  this->caption_height = caption_h;
  this->border_width = border_w;
  this->resize_border = resize_width;
  this->caption_button_count = 0;
  this->on_caption_button = 0;
  if ((flags & 4) != 0) {
    this->caption_height = frame_caption_height;
    this->border_width = frame_border_width;
  }
  if ((flags & 8) == 0) {
    wnd_style = 0x202;
  }
  else {
    wnd_style = 0x802;
  }
  if (this->caption_height != 0) {
    wnd_style = wnd_style | 0x400;
  }
  if (this->resize_border != 0) {
    wnd_style = wnd_style | 0x1000;
  }
  if ((flags & 2) == 0) {
    width += this->border_width * 2;
    height = height + this->caption_height + this->border_width;
  }
  if ((flags & 1) != 0) {
    x = (screen_width >> 1) - (width >> 1);
    y = (screen_height >> 1) - (height >> 1);
  }
  wnd_create_with_surface
            ((DibSurface *)this,0,wnd_style,x,y,width,height,(iptr)((u8 *)&g.d_006a8c00),(iptr)((u8 *)&g.d_006553d8));
  if (this->caption_height != 0) {
    wnd_set_caption_height((WndBase *)this->window_2,this->caption_height);
  }
  if (this->resize_border != 0) {
    wnd_set_resize_border((WndBase *)this->window_2,this->resize_border);
  }
  frame_wnd_layout(this);
  wnd_set_drag_begin_callback((WndDragBeginSetView *)(this->event_handlers),(iptr)mp_window_drag_begin);
  wnd_set_drag_end_callback((WndDragEndSetView *)(this->event_handlers),(iptr)mp_window_drag_end);
  return;
}
#undef frame_border_width
#undef frame_caption_height
#undef screen_height
#undef wnd_style

/* 00553d30 auto */
u32 __thiscall wnd_set_drag_begin_callback(WndDragBeginSetView *this,iptr callback)

{
  u32 old_callback;
  
  old_callback = this->on_drag_begin;
  this->on_drag_begin = callback;
  return old_callback;
}

/* 00553d70 auto */
u32 __thiscall wnd_set_drag_end_callback(WndDragEndSetView *this,iptr callback)

{
  u32 old_callback;
  
  old_callback = this->on_drag_end;
  this->on_drag_end = callback;
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
  surface_ctor((DibSurface *)&frame_texture_surface);
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
  surface_dtor((DibSurface *)&frame_texture_surface);
  return;
}

/* 005681c9 auto */
#define frame_texture_loaded_i32 (*(i32 *)((u8 *)&g.d_00633dac))
#define sprite_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define dll (*(DllHandle *)(frame_ + FRAME_OFF(16)))
#define surface (*(DibSurface *)(frame_ + FRAME_OFF(20)))
#define path (*(i8 (*)[128])(frame_ + FRAME_OFF(92)))
#define sprite (*(Sprite *)(frame_ + FRAME_OFF(220)))
#define eh_prev (*(i32 *)(frame_ + FRAME_OFF(280)))
#define eh_handler (*(i8 * *)(frame_ + FRAME_OFF(284)))
#define eh_state (*(int *)(frame_ + FRAME_OFF(288)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl frame_texture_load(void)

{
  int ok;
  i8 frame_[FRAME_OFF(296)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  gfx_build_grey_remap();
  surface_ctor(&surface);
  eh_state = 0;
  sprite_init(&sprite);
  (*(i8 *)((char *)&eh_state + 0)) = 1;
  frame_texture_loaded_i32 = 1;
  str_clear((iptr)path);
  str_append((iptr)path,(iptr)((u8 *)&g.d_00633db0));
  ok = file_resolve_path((iptr)path);
  if (ok == 0) {
    surface_create((DibSurface *)&frame_texture_surface,0x40,0x20);
    surface_fill((DibSurface *)&frame_texture_surface,0x21);
  }
  else {
    resource_dll_load(&dll,(iptr)path);
    eh_state = CONCAT31((*(i32 *)((char *)&eh_state + 1)),2);
    ok = surface_load_gif_resource(&surface,999,10,0xec,(iptr)((u8 *)&g.d_006ab6a8));
    if (ok == 0) {
      MessageBoxA((HWND)0x0,s_Failed_to_load_civ2art_gif_00633dcc,s_NOTICE_00633dc4,0x40);
    }
    else {
      sprite_grab_from_surface(&sprite,(iptr)&surface,2,1,1,0x40,0x20);
      surface_create((DibSurface *)&frame_texture_surface,0x40,0x20);
      sprite_draw(&sprite,(iptr)sprite_rect,(iptr)((u8 *)&g.d_006abae0),0,0);
      sprite_free(&sprite);
      surface_release(&surface);
    }
    dll_handle_free(&dll);
    (*(i8 *)((char *)&eh_state + 0)) = 1;
    /* inlined unwind funclet 00568348 */ { dll_free((DllHandle *)((iptr)&dll)); }
  }
  frame_texture_load_hook_nop();
  eh_state = (uint)(*(i32 *)((char *)&eh_state + 1)) << 8;
  /* inlined unwind funclet 00568354 */ { sprite_destroy((Sprite *)((iptr)&sprite)); }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 0056835d */ { surface_dtor((DibSurface *)((iptr)&surface)); }
  return;
}
#undef frame_texture_loaded_i32
#undef sprite_rect
#undef dll
#undef surface
#undef path
#undef sprite
#undef eh_prev
#undef eh_handler
#undef eh_state

/* 00568381 auto */
void __cdecl frame_texture_free(void)

{
  surface_release((DibSurface *)&frame_texture_surface);
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

u32 __thiscall wnd_set_rbuttondown_handler(WndHandlersMouseSetView *this,iptr handler)

{
  u32 old_handler;
  
  old_handler = ((WndHandlersMouseSetViewExt *)this)->on_rbutton_down;
  ((WndHandlersMouseSetViewExt *)this)->on_rbutton_down = handler;
  return old_handler;
}

/* 00578610 auto */
/* Library Function - Single Match
    public: int __thiscall ios_base::width(int)
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall wnd_set_rbuttonup_any_handler(WndHandlersMouseSetView *this,iptr handler)

{
  u32 old_handler;
  
  old_handler = ((WndHandlersMouseSetViewExt *)this)->on_rbutton_up_any;
  ((WndHandlersMouseSetViewExt *)this)->on_rbutton_up_any = handler;
  return old_handler;
}

/* 00578650 auto */
void __thiscall menu_storage_reinit(GameMenu *this,uint size)

{
  memblock_free((iptr)this->item_storage);
  memblock_init((iptr)this->item_storage,0xb,size);
  return;
}

/* 0057868c auto */
/* Library Function - Single Match
    public: virtual void __thiscall CHtmlStream::Reset(void)
   
   Library: Visual Studio 1998 Debug */

void __thiscall menu_clear_lists(GameMenu *this)

{
  this->menus = 0;
  this->menu_flags = 0;
  return;
}

/* 005786b6 auto */
void __thiscall menu_reset(GameMenu *this,i32 size)

{
  memblock_detach((iptr)this->item_storage);
  menu_clear_lists(this);
  menu_storage_reinit(this,size);
  return;
}

/* 005786f1 auto */
#define eh_prev (*(i32 *)(frame_ + FRAME_OFF(0)))
#define eh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
GameMenu * __thiscall menu_ctor(GameMenu *this,i32 size)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  menu_handle_ctor(this);
  eh_state = 0;
  memblock_ctor((MemBlock *)this->item_storage);
  menu_reset(this,size);
  return this;
}
#undef eh_prev
#undef eh_handler
#undef eh_state

/* 00578770 auto */
#define eh_prev (*(i32 *)(frame_ + FRAME_OFF(0)))
#define eh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
void __thiscall menu_dtor(GameMenu *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0;
  memblock_free((iptr)this->item_storage);
  eh_state = 0xffffffff;
  /* inlined unwind funclet 005787bd */ { menu_handle_dtor(*(GameMenu **)((iptr)&this)); }
  return;
}
#undef eh_prev
#undef eh_handler
#undef eh_state

/* 005787de auto */
#define menu2 (*(uptr *)(frame_ + FRAME_OFF(4)))
i32 __thiscall menu_find_menu(GameMenu *this,int menu_id)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  menu2 = this->menus;
  while( true ) {
    if (menu2 == 0) {
      return 0;
    }
    if (*(int *)(menu2 + 4) == menu_id) break;
    menu2 = *(uptr *)(menu2 + 0x10);
  }
  return menu2;
}
#undef menu2

/* 00578840 auto */
#define index (*(int *)(frame_ + FRAME_OFF(4)))
#define cur (*(uptr *)(frame_ + FRAME_OFF(8)))
int __thiscall menu_visible_index(GameMenu *this,uptr menu)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  index = 1;
  for (cur = this->menus; (cur != 0 && (menu != cur));
      cur = *(uptr *)(cur + 0x10)) {
    if ((*(byte *)(cur + 8) & 2) == 0) {
      index++;
    }
  }
  return index;
}
#undef index
#undef cur

/* 005788a9 auto */
#define index (*(int *)(frame_ + FRAME_OFF(0)))
#define menu2 (*(uptr *)(frame_ + FRAME_OFF(4)))
i32 __thiscall menu_id_at_visible_index(GameMenu *this,int visible_index)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  index = 1;
  menu2 = this->menus;
  do {
    if (menu2 == 0) {
      return 0xffffffff;
    }
    if ((*(byte *)(menu2 + 8) & 2) == 0) {
      if (index == visible_index) {
        return *(i32 *)(menu2 + 4);
      }
      index++;
    }
    menu2 = *(uptr *)(menu2 + 0x10);
  } while( true );
}
#undef index
#undef menu2

/* 00578922 auto */
#define menu2 (*(uptr *)(frame_ + FRAME_OFF(0)))
#define item (*(iptr *)(frame_ + FRAME_OFF(4)))
#define found (*(iptr *)(frame_ + FRAME_OFF(8)))
iptr __thiscall menu_find_item(GameMenu *this,int item_id)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  found = 0;
  menu2 = this->menus;
  do {
    if (menu2 == 0) {
      return found;
    }
    for (item = *(iptr *)(menu2 + 0x18); item != 0; item = *(iptr *)(item + 0x10)) {
      if (*(int *)(item + 4) == item_id) {
        found = item;
        break;
      }
    }
    menu2 = *(uptr *)(menu2 + 0x10);
  } while( true );
}
#undef menu2
#undef item
#undef found

/* 005789aa auto */
#define index (*(int *)(frame_ + FRAME_OFF(4)))
#define cur (*(iptr *)(frame_ + FRAME_OFF(8)))
int __thiscall menu_item_visible_index(GameMenu *this,iptr item)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  index = 1;
  for (cur = *(iptr *)(*(int *)(item + 0x18) + 0x18); (cur != 0 && (item != cur));
      cur = *(iptr *)(cur + 0x10)) {
    if ((*(byte *)(cur + 8) & 2) == 0) {
      index++;
    }
  }
  return index;
}
#undef index
#undef cur

/* 00578a1c auto */
#define index (*(int *)(frame_ + FRAME_OFF(0)))
#define item (*(iptr *)(frame_ + FRAME_OFF(4)))
i32 __thiscall menu_item_id_at_visible_index(GameMenu *this,i32 menu_id,int visible_index)

{
  iptr menu;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  index = 1;
  menu = menu_find_menu(this,menu_id);
  if (menu != 0) {
    for (item = *(iptr *)(menu + 0x18); item != 0; item = *(iptr *)(item + 0x10)) {
      if ((*(byte *)(item + 8) & 2) == 0) {
        if (index == visible_index) {
          return *(i32 *)(item + 4);
        }
        index++;
      }
    }
  }
  return 0xffffffff;
}
#undef index
#undef item

/* 00578b06 auto */
#define last (*(uptr *)(frame_ + FRAME_OFF(4)))
i32 * __thiscall menu_add_menu(GameMenu *this,i32 menu_id,char *title)

{
  i32 *menu;
  size_t len;
  i32 text;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  menu = (i32 *)memblock_alloc((iptr)this->item_storage,0x1c);
  if (this->menus == 0) {
    this->menus = (uptr)menu;
    menu[5] = 0;
  }
  else {
    for (last = this->menus; *(int *)(last + 0x10) != 0;
        last = *(uptr *)(last + 0x10)) {
    }
    *(i32 **)(last + 0x10) = menu;
    menu[5] = last;
  }
  menu[4] = 0;
  menu[6] = 0;
  menu[2] = 0;
  menu[1] = menu_id;
  menu[3] = 0;
  len = _strlen(title);
  text = memblock_alloc((iptr)this->item_storage,len + 1);
  *menu = text;
  crt_strcpy(*menu,title);
  str_pipes_to_tabs(*menu);
  this->menu_flags = this->menu_flags & 0xffff7fff;
  return menu;
}
#undef last

/* 00578c12 auto */
#define buf_len (*(size_t *)(frame_ + FRAME_OFF(0)))
#define item (*(i32 * *)(frame_ + FRAME_OFF(4)))
#define last (*(iptr *)(frame_ + FRAME_OFF(8)))
i32 * __thiscall
menu_add_item
          (GameMenu *this,i32 menu_id,i32 item_id,iptr text,size_t min_len)

{
  iptr menu;
  size_t len;
  i32 buffer;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  item = (i32 *)0x0;
  menu = menu_find_menu(this,menu_id);
  if (menu != 0) {
    item = (i32 *)memblock_alloc((iptr)this->item_storage,0x1c);
    if (*(int *)(menu + 0x18) == 0) {
      *(i32 **)(menu + 0x18) = item;
      item[5] = 0;
    }
    else {
      for (last = *(iptr *)(menu + 0x18); *(int *)(last + 0x10) != 0;
          last = *(iptr *)(last + 0x10)) {
      }
      *(i32 **)(last + 0x10) = item;
      item[5] = last;
    }
    item[6] = menu;
    item[4] = 0;
    item[2] = 0;
    item[1] = item_id;
    item[3] = 0;
    if (text == 0) {
      *item = 0;
    }
    else {
      len = _strlen((char *)text);
      if ((int)len < (int)min_len) {
        buf_len = min_len;
      }
      else {
        buf_len = _strlen((char *)text);
      }
      buffer = memblock_alloc((iptr)this->item_storage,buf_len + 1);
      *item = buffer;
      crt_strcpy(*item,text);
      str_pipes_to_tabs(*item);
    }
    this->menu_flags = this->menu_flags & 0xffff7fff;
  }
  return item;
}
#undef buf_len
#undef item
#undef last

/* 00578d8a auto */
#define menu_command_callback (*(code * *)((u8 *)&g.d_0063430c))
void __cdecl menu_dispatch_command(i32 menu_index,i32 item_index)

{
  i32 menu_id;
  i32 item_id;
  
  if (menu_command_callback != (code *)0x0) {
    menu_id = menu_id_at_visible_index(menu_active_object,menu_index);
    item_id = menu_item_id_at_visible_index(menu_active_object,menu_id,item_index);
    (*menu_command_callback)(menu_id,item_id);
  }
  return;
}
#undef menu_command_callback

/* 00578de8 auto */
void __thiscall menu_attach_to_window(GameMenu *this,ModalMenuWindow *window)

{
  if (window != (ModalMenuWindow *)0x0) {
    menu_owner_window = window;
    menu_active_object = this;
    wnd_attach_menu(window,(iptr)this);
    wnd_set_menu_callback((WndMenuCbSetView *)window,(iptr)menu_dispatch_command);
  }
  return;
}

/* 00578e38 auto */
#define menu_command_callback (*(iptr *)((u8 *)&g.d_0063430c))
void __thiscall menu_set_command_handler(GameMenu *this,iptr handler)

{
  menu_active_object = this;
  menu_command_callback = handler;
  return;
}
#undef menu_command_callback

/* 00578e60 auto */
i32 __thiscall menu_apply_item_enabled(GameMenu *this,i32 item_id)

{
  iptr item;
  uint enabled;
  i32 result;
  i32 menu_index;
  
  item = menu_find_item(this,item_id);
  if (item == 0) {
    result = 0;
  }
  else {
    enabled = ~*(uint *)(item + 8) & 1;
    result = menu_item_visible_index(this,item);
    menu_index = menu_visible_index(this,*(i32 *)(item + 0x18));
    result = menu_native_enable(this,menu_index,result,enabled);
  }
  return result;
}

/* 00578ec7 auto */
void __thiscall menu_apply_item_checked(GameMenu *this,i32 item_id)

{
  iptr item;
  uint checked;
  i32 item_index;
  i32 menu_index;
  
  item = menu_find_item(this,item_id);
  if (item != 0) {
    checked = *(uint *)(item + 8) & 4;
    item_index = menu_item_visible_index(this,item);
    menu_index = menu_visible_index(this,*(i32 *)(item + 0x18));
    menu_native_check(this,menu_index,item_index,checked);
  }
  return;
}

/* 00578f2c auto */
#define menu2 (*(i32 * *)(frame_ + FRAME_OFF(0)))
#define menu_index (*(int *)(frame_ + FRAME_OFF(4)))
#define item_index (*(int *)(frame_ + FRAME_OFF(8)))
#define item (*(i32 * *)(frame_ + FRAME_OFF(12)))
#define i (*(int *)(frame_ + FRAME_OFF(16)))
#define spec (*(i8 (*)[256])(frame_ + FRAME_OFF(20)))
void __thiscall menu_rebuild(GameMenu *this,iptr window)

{
  i8 frame_[FRAME_OFF(280)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((this->menu_flags & 0x8000) == 0) {
    spec[0] = 0;
    menu2 = (i32 *)this->menus;
    menu_index = 1;
    for (; menu2 != (i32 *)0x0; menu2 = (i32 *)menu2[4]) {
      if ((*(byte *)(menu2 + 2) & 2) == 0) {
        crt_strcat(spec,*menu2);
        crt_strcat(spec,&menu_title_sep_str);
      }
      if (window == 0) {
        for (i = 0x1e; 0 < i; i--) {
          menu_native_delete(this,menu_index,i);
        }
        menu2[3] = 0;
      }
      menu_index++;
    }
    if (window != 0) {
      menu_native_build(this,(iptr)spec);
    }
    menu2 = (i32 *)this->menus;
    menu_index = 1;
    for (; menu2 != (i32 *)0x0; menu2 = *(i32 **)((int)menu2 + 0x10)) {
      if ((*(byte *)((int)menu2 + 8) & 2) == 0) {
        if (window != 0) {
          menu_native_delete(this,menu_index,1);
        }
        item = *(i32 **)((int)menu2 + 0x18);
        item_index = 1;
        for (; item != (i32 *)0x0; item = (i32 *)item[4]) {
          if ((*(byte *)(item + 2) & 2) == 0) {
            *(int *)((int)menu2 + 0xcU) = *(int *)((int)menu2 + 0xcU) + 1;
            menu_native_insert(this,menu_index,item_index,*item);
            if ((*(byte *)(item + 2) & 1) != 0) {
              menu_apply_item_enabled(this,item[1]);
            }
            if ((*(byte *)(item + 2) & 4) != 0) {
              menu_apply_item_checked(this,item[1]);
            }
            item_index++;
          }
        }
        menu_index++;
      }
    }
    this->menu_flags = this->menu_flags | 0x8000;
    menu_attach_to_window(this,window);
  }
  if (menu_owner_window != (ModalMenuWindow *)0x0) {
    wnd_redraw_menu_bar(menu_owner_window);
  }
  return;
}
#undef menu2
#undef menu_index
#undef item_index
#undef item
#undef i
#undef spec

/* 00579260 auto */
void __thiscall menu_set_item_hidden(GameMenu *this,i32 item_id,int hidden)

{
  iptr item;
  
  item = menu_find_item(this,item_id);
  if (item != 0) {
    if (hidden == 0) {
      if ((*(byte *)(item + 8) & 2) != 0) {
        this->menu_flags = this->menu_flags & 0xffff7fff;
      }
      *(uint *)(item + 8) = *(uint *)(item + 8) & 0xfffffffd;
    }
    else {
      if ((*(byte *)(item + 8) & 2) == 0) {
        this->menu_flags = this->menu_flags & 0xffff7fff;
      }
      *(uint *)(item + 8) = *(uint *)(item + 8) | 2;
    }
  }
  return;
}

/* 005792e1 auto */
#define was_enabled (*(GameMenu * *)(frame_ + FRAME_OFF(4)))
GameMenu * __thiscall
menu_set_item_enabled(GameMenu *this,i32 item_id,GameMenu *enabled)

{
  GameMenu *pCVar1;
  GameMenu *pCVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  pCVar1 = (GameMenu *)menu_find_item(this,item_id);
  pCVar2 = pCVar1;
  if (pCVar1 != (GameMenu *)0x0) {
    enabled = (GameMenu *)(uint)(enabled != (GameMenu *)0x0);
    was_enabled = (GameMenu *)(uint)((pCVar1->item_storage[4] & 1) != 0);
    if (enabled == (GameMenu *)0x0) {
      *(uint *)(pCVar1->item_flags) = *(uint *)(pCVar1->item_flags) & 0xfffffffe;
    }
    else {
      *(uint *)(pCVar1->item_flags) = *(uint *)(pCVar1->item_flags) | 1;
    }
    pCVar2 = this;
    if ((((this->menu_flags & 0x8000) != 0) && (pCVar2 = pCVar1, (pCVar1->item_storage[4] & 2) == 0)) &&
       (pCVar2 = enabled, was_enabled != enabled)) {
      pCVar2 = (GameMenu *)menu_apply_item_enabled(this,item_id);
    }
  }
  return pCVar2;
}
#undef was_enabled

/* 005793a3 auto */
void __thiscall menu_remove_item(GameMenu *this,i32 item_id)

{
  iptr item;
  i32 item_index;
  i32 menu_index;
  
  item = menu_find_item(this,item_id);
  if (item != 0) {
    item_index = menu_item_visible_index(this,item);
    menu_index = menu_visible_index(this,*(i32 *)(item + 0x18));
    menu_native_delete(this,menu_index,item_index);
    *(i32 *)(*(int *)(item + 0x14) + 0x10) = *(i32 *)(item + 0x10);
  }
  return;
}

/* 0057940d auto */
void __thiscall menu_set_item_checked(GameMenu *this,i32 item_id,int checked)

{
  byte old_flags;
  iptr item;
  
  item = menu_find_item(this,item_id);
  if (item != 0) {
    old_flags = *(byte *)(item + 8);
    if (checked != 0) {
      *(uint *)(item + 8) = *(uint *)(item + 8) | 4;
    }
    else {
      *(uint *)(item + 8) = *(uint *)(item + 8) & 0xfffffffb;
    }
    if ((((this->menu_flags & 0x8000) != 0) && ((*(byte *)(item + 8) & 2) == 0)) &&
       (((old_flags & 4) != 0) != (checked != 0))) {
      menu_apply_item_checked(this,item_id);
    }
  }
  return;
}

/* 005794cf auto */
#define item (*(iptr *)(frame_ + FRAME_OFF(0)))
void __thiscall menu_set_menu_enabled(GameMenu *this,i32 menu_id,i32 enabled)

{
  iptr menu;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  menu = menu_find_menu(this,menu_id);
  if (menu != 0) {
    for (item = *(iptr *)(menu + 0x18); item != 0; item = *(iptr *)(item + 0x10)) {
      menu_set_item_enabled(this,*(i32 *)(item + 4),enabled);
    }
  }
  return;
}
#undef item

/* 0057953e auto */
void __thiscall menu_set_item_text(GameMenu *this,i32 item_id,iptr text)

{
  i32 *item;
  i32 item_index;
  i32 menu_index;
  i32 item_text;
  
  item = (i32 *)menu_find_item(this,item_id);
  if (item != (i32 *)0x0) {
    crt_strcpy(*item,text);
    str_pipes_to_tabs(*item);
    if (((this->menu_flags & 0x8000) != 0) && ((*(byte *)(item + 2) & 2) == 0)) {
      item_text = *item;
      item_index = menu_item_visible_index(this,(iptr)item);
      menu_index = menu_visible_index(this,item[6]);
      menu_native_set_text(this,menu_index,item_index,item_text);
    }
  }
  return;
}

/* 005799c0 auto */
void __thiscall menu_native_build(GameMenu *this,iptr spec)

{
  u32 menu_handle;
  
  menu_handle = menu_hmenu_build_from_spec(spec);
  this->hmenu = menu_handle;
  return;
}

/* 00579a00 auto */
void __thiscall
menu_native_insert(GameMenu *this,i32 menu_index,i32 item_index,i32 text)

{
  menu_hmenu_insert_item(this->hmenu,menu_index,item_index,text);
  return;
}

/* 00579a40 auto */
void __thiscall menu_native_delete(GameMenu *this,i32 menu_index,i32 item_index)

{
  menu_hmenu_delete_item(this->hmenu,menu_index,item_index);
  return;
}

/* 00579a80 auto */
void __thiscall
menu_native_set_text(GameMenu *this,i32 menu_index,i32 item_index,i32 text)

{
  menu_hmenu_set_item_text(this->hmenu,menu_index,item_index,text);
  return;
}

/* 00579ac0 auto */
i32 __thiscall
menu_native_enable(GameMenu *this,i32 menu_index,i32 item_index,i32 enabled)

{
  i32 result;
  
  result = menu_hmenu_enable_item(this->hmenu,menu_index,item_index,enabled);
  return result;
}

/* 00579b00 auto */
void __thiscall
menu_native_check(GameMenu *this,i32 menu_index,i32 item_index,i32 checked)

{
  menu_hmenu_check_item(this->hmenu,menu_index,item_index,checked);
  return;
}

/* 00579b40 auto */
void __thiscall wnd_attach_menu(ModalMenuWindow *this,iptr menu_obj)

{
  i32 hmenu;
  iptr hwnd;
  
  hmenu = menu_get_hmenu((MenuHandleView *)menu_obj);
  hwnd = wnd_get_window((WndBase *)this);
  wnd_obj_attach_menu(hwnd,hmenu);
  this->menu = menu_obj;
  return;
}

/* 00579b90 auto */
u32 __thiscall menu_get_hmenu(MenuHandleView *this)

{
  return this->hmenu;
}

/* 00579bc0 auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall wnd_set_menu_callback(WndMenuCbSetView *this,iptr callback)

{
  this->on_menu = callback;
  return;
}

/* 00579bf0 auto */
void __thiscall wnd_redraw_menu_bar(ModalMenuWindow *this)

{
  iptr hwnd;
  
  if (this->menu != 0) {
    hwnd = wnd_get_window((WndBase *)this);
    menu_redraw_bar(hwnd);
  }
  return;
}

/* 00589d50 auto */
i32 __thiscall wnd_frame_width(WndBase *this)

{
  i32 width;
  
  width = wnd_obj_frame_width(this->native_wnd);
  return width;
}

/* 0058bd60 auto */
void __cdecl cmd_unit_skip_turn(void)

{
  unit_move_dir((int)game.active_unit,0xffffffff,3);
  return;
}

/* 0058bd84 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define unit (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl cmd_end_player_turn(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (unit = 0; unit < game.num_units; unit++) {
    if ((units[unit].id != 0) && (units[unit].owner == human_civ)) {
      unit_exhaust_moves(unit);
    }
  }
  return;
}
#undef human_civ
#undef unit

/* 0058d442 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define map_cursor_x (*(short *)((u8 *)&g.d_0064b1b4))
#define map_cursor_y (*(short *)((u8 *)&g.d_0064b1b0))
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
#define unit_blink_active (*(i8 *)((u8 *)&g.d_0062804c))
#define unit (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl ui_pick_unit_from_stack(void)

{
  int stack_count;
  iptr prompt;
  i32 dialog_flags;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  unit_blink_active = 0;
  if (moving_units_mode == 1) {
    unit = (iptr)game.active_unit;
    if (units[unit].id == 0) {
      unit_blink_active = 0;
      return;
    }
    if (units[unit].owner != human_civ) {
      unit_blink_active = 0;
      return;
    }
    stack_count = unit_stack_sum(unit,2);
    if (stack_count == 1) {
      return;
    }
  }
  else {
    unit = tile_first_unit((int)map_cursor_x,(int)map_cursor_y);
    if (unit < 0) {
      return;
    }
    if (units[unit].owner != human_civ) {
      return;
    }
    if ((units[unit].owner != game.turn_civ) && (game.reveal_map == '\0')) {
      return;
    }
    stack_count = unit_stack_sum(unit,2);
    if (stack_count == 1) goto LAB_0058d58e;
  }
  dialog_flags = 1;
  prompt = label_string(*(i32 *)(label_string_ids + 0xf8));
  unit = unit_stack_select_dialog(unit,prompt,dialog_flags);
  if (unit < 0) {
    return;
  }
LAB_0058d58e:
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
#undef human_civ
#undef map_cursor_x
#undef map_cursor_y
#undef moving_units_mode
#undef unit_blink_active
#undef unit

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
  font_init_styled((GameFont *)&dialog_text_font_obj,0,0x10,1);
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
  font_destroy((GameFont *)&dialog_text_font_obj);
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
  font_init((GameFont *)&dialog_title_font_obj,0,0x10);
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
  font_destroy((GameFont *)&dialog_title_font_obj);
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
  font_init((GameFont *)&dialog_list_font_obj,1,0xe);
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
  font_destroy((GameFont *)&dialog_list_font_obj);
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
  font_init((GameFont *)&dialog_plain_font_obj,0,0x10);
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
  font_destroy((GameFont *)&dialog_plain_font_obj);
  return;
}

/* 0059d34e auto */
void __cdecl active_dialog_global_init(void)

{
  active_dialog_static_init();
  return;
}

/* 0059d363 auto */
#define dialog_stack (*(iptr *)((u8 *)&g.d_00635a58))
void __cdecl active_dialog_static_init(void)

{
  active_dialog = dialog_stack;
  return;
}
#undef dialog_stack

/* 0059d37d auto */
#define dialog_timeout_start_i32 (*(i32 *)((u8 *)&g.d_006cec80))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl dialog_edit_on_change(void)

{
  dialog_timeout_start_i32 = timer_ticks();
  return;
}
#undef dialog_timeout_start_i32

/* 0059d397 auto */
#define dialog_timeout_start_i32 (*(i32 *)((u8 *)&g.d_006cec80))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl dialog_radio_on_select(void)

{
  dialog_timeout_start_i32 = timer_ticks();
  return;
}
#undef dialog_timeout_start_i32

/* 0059d3b1 auto */
#define dlg_palette (*(iptr *)((u8 *)&g.d_006359c0))
void __cdecl dlg_set_palette(iptr palette)

{
  dlg_palette = palette;
  return;
}
#undef dlg_palette

/* 0059d3c9 auto */
#define dlg_parent_window (*(iptr *)((u8 *)&g.d_006359c4))
void __cdecl dlg_set_parent_window(iptr window)

{
  dlg_parent_window = window;
  return;
}
#undef dlg_parent_window

/* 0059d3e1 auto */
#define dlg_default_x (*(i32 *)((u8 *)&g.d_006359cc))
#define dlg_default_y (*(i32 *)((u8 *)&g.d_006359d0))
void __cdecl dialog_set_default_offset(i32 x,i32 y)

{
  dlg_default_x = x;
  dlg_default_y = y;
  return;
}
#undef dlg_default_x
#undef dlg_default_y

/* 0059d401 auto */
#define i (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl dialog_load_button_labels(void)

{
  int status;
  i32 label_id;
  i8 *label;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  status = text_open_section((iptr)((u8 *)&g.d_00635ac4),(iptr)((u8 *)&g.d_00635abc));
  if (status == 0) {
    for (i = 0; i < 3; i++) {
      label_id = text_read_line_pooled();
      *(i32 *)(&dialog_button_label_ids + i * 4) = label_id;
      label = (i8 *)label_string(*(i32 *)(&dialog_button_label_ids + i * 4));
      (&dialog_button_labels)[i] = label;
    }
  }
  return;
}
#undef i

/* 0059d487 auto */
#define dlg_bevel_dark_color (*(i8 *)((u8 *)&g.d_00635a0c))
#define dlg_bevel_light_color (*(i8 *)((u8 *)&g.d_00635a08))
#define dlg_bg_color (*(i8 *)((u8 *)&g.d_00635a04))
#define dlg_frame_color (*(i8 *)((u8 *)&g.d_006359f4))
#define dlg_highlight_text_color (*(i8 *)((u8 *)&g.d_00635a00))
#define dlg_text_color (*(i8 *)((u8 *)&g.d_006359fc))
#define dlg_text_shadow_color (*(i8 *)((u8 *)&g.d_006359f8))
#define dlg_title_shadow_color (*(i8 *)((u8 *)&g.d_00635a14))
#define dlg_title_text_color (*(i8 *)((u8 *)&g.d_00635a10))
void __cdecl
dialog_set_colors(i32 text_color,i32 text_shadow,i32 frame_color,i32 highlight_color,
            i32 bg_color,i32 bevel_light,i32 bevel_dark,i32 title_color,
            i32 title_shadow)

{
  dlg_text_color = (i8)text_color;
  dlg_text_shadow_color = (i8)text_shadow;
  dlg_frame_color = (i8)frame_color;
  dlg_highlight_text_color = (i8)highlight_color;
  dlg_bg_color = (i8)bg_color;
  dlg_bevel_light_color = (i8)bevel_light;
  dlg_bevel_dark_color = (i8)bevel_dark;
  dlg_title_text_color = (i8)title_color;
  dlg_title_shadow_color = (i8)title_shadow;
  return;
}
#undef dlg_bevel_dark_color
#undef dlg_bevel_light_color
#undef dlg_bg_color
#undef dlg_frame_color
#undef dlg_highlight_text_color
#undef dlg_text_color
#undef dlg_text_shadow_color
#undef dlg_title_shadow_color
#undef dlg_title_text_color

/* 0059d4df auto */
#define dialog_default_list_color (*(i32 *)((u8 *)&g.d_00635a30))
#define dlg_sel_text_color (*(i32 *)((u8 *)&g.d_00635a28))
#define dlg_sel_text_shadow_color (*(i32 *)((u8 *)&g.d_00635a2c))
#define list_bg_color (*(i32 *)((u8 *)&g.d_00635a18))
#define list_sel_bg_color (*(i32 *)((u8 *)&g.d_00635a24))
#define list_shadow_color (*(i32 *)((u8 *)&g.d_00635a20))
#define list_text_color (*(i32 *)((u8 *)&g.d_00635a1c))
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
#undef dialog_default_list_color
#undef dlg_sel_text_color
#undef dlg_sel_text_shadow_color
#undef list_bg_color
#undef list_sel_bg_color
#undef list_shadow_color
#undef list_text_color

/* 0059d59d auto */
#define dlg_frame_tile_surface (*(iptr *)((u8 *)&g.d_00635aa0))
void __cdecl dialog_set_frame_tile_surface(iptr surface)

{
  dlg_frame_tile_surface = surface;
  return;
}
#undef dlg_frame_tile_surface

/* 0059d5b5 auto */
void __thiscall dialog_reset_string_pool(DialogCore *this,uint size)

{
  memblock_free((iptr)&((DialogTextLineView *)this)->string_pool);
  memblock_init((iptr)&((DialogTextLineView *)this)->string_pool,9,size);
  return;
}

/* 0059d5f5 auto */
#define dialog_default_list_color (*(u32 *)((u8 *)&g.d_00635a30))
#define dlg_bevel_dark_color (*(byte *)((u8 *)&g.d_00635a0c))
#define dlg_bevel_light_color (*(byte *)((u8 *)&g.d_00635a08))
#define dlg_bg_color (*(byte *)((u8 *)&g.d_00635a04))
#define dlg_default_x (*(u32 *)((u8 *)&g.d_006359cc))
#define dlg_default_y (*(u32 *)((u8 *)&g.d_006359d0))
#define dlg_frame_color (*(byte *)((u8 *)&g.d_006359f4))
#define dlg_highlight_text_color (*(byte *)((u8 *)&g.d_00635a00))
#define dlg_scale_den (*(u32 *)((u8 *)&g.d_00635a38))
#define dlg_scale_num (*(u32 *)((u8 *)&g.d_00635a34))
#define dlg_sel_text_color (*(u32 *)((u8 *)&g.d_00635a28))
#define dlg_sel_text_shadow_color (*(u32 *)((u8 *)&g.d_00635a2c))
#define dlg_text_color (*(byte *)((u8 *)&g.d_006359fc))
#define dlg_text_shadow_color (*(byte *)((u8 *)&g.d_006359f8))
#define dlg_title_shadow_color (*(byte *)((u8 *)&g.d_00635a14))
#define dlg_title_text_color (*(byte *)((u8 *)&g.d_00635a10))
#define list_bg_color (*(u32 *)((u8 *)&g.d_00635a18))
#define list_sel_bg_color (*(u32 *)((u8 *)&g.d_00635a24))
#define list_shadow_color (*(u32 *)((u8 *)&g.d_00635a20))
#define list_text_color (*(u32 *)((u8 *)&g.d_00635a1c))
#define i (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall dialog_init_defaults(Dialog *this)

{
  u8 *slot;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  this->surf_wnd = 0;
  this->bg_surface = 0;
  this->pool_valid = '\0';
  this->list_font = 0;
  this->title_font = this->list_font;
  this->body_font = this->title_font;
  this->sprite_count = 0;
  this->option_count = this->sprite_count;
  this->edit_count = this->option_count;
  this->line_count = this->edit_count;
  this->extra_button_count = 0;
  this->std_button_count = this->extra_button_count;
  this->style_flags = 0;
  this->scale_num = dlg_scale_num;
  this->scale_den = dlg_scale_den;
  this->window_y = 0xfffffc19;
  this->window_x = this->window_y;
  this->origin_y = 0;
  this->origin_x = this->origin_y;
  this->wnd_height = 0;
  this->wnd_width = this->wnd_height;
  if ((dlg_default_x == 0) && (dlg_default_y == 0)) {
    this->req_y = 0xfffffc19;
    this->req_x = this->req_y;
  }
  else {
    this->req_x = dlg_default_x;
    this->req_y = dlg_default_y;
  }
  this->min_height = 0;
  this->edit_label_width = 0;
  this->bg_color = (uint)dlg_bg_color;
  this->text_color = (uint)dlg_text_color;
  this->shadow_color = (uint)dlg_text_shadow_color;
  this->frame_color = (uint)dlg_frame_color;
  this->highlight_color = (uint)dlg_highlight_text_color;
  this->bevel_light_color = (uint)dlg_bevel_light_color;
  this->bevel_dark_color = (uint)dlg_bevel_dark_color;
  this->title_color = (uint)dlg_title_text_color;
  this->title_shadow_color = (uint)dlg_title_shadow_color;
  this->list_fill_color = list_bg_color;
  this->list_fg_color = list_text_color;
  this->list_fg_shadow_color = list_shadow_color;
  this->list_sel_fill_color = list_sel_bg_color;
  this->sel_text_color = dlg_sel_text_color;
  this->sel_shadow_color = dlg_sel_text_shadow_color;
  this->list_default_color = dialog_default_list_color;
  for (i = 0; i < 2; i++) {
    slot = this->list_column_counts + i * 4 + 8;
    slot[0] = '\0';
    slot[1] = '\0';
    slot[2] = '\0';
    slot[3] = '\0';
    slot = this->list_column_counts + i * 4 + 0x10;
    slot[0] = '\0';
    slot[1] = '\0';
    slot[2] = '\0';
    slot[3] = '\0';
    slot = this->list_vscroll_rect + i * 4 + 0x40;
    slot[0] = '\0';
    slot[1] = '\0';
    slot[2] = '\0';
    slot[3] = '\0';
  }
  this->cur_pane = 0;
  this->edit_width = 0;
  this->item_width_value = this->edit_width;
  this->max_sprite_width = this->item_width_value;
  this->content_width = this->max_sprite_width;
  this->option_width = this->content_width;
  this->selected_option = 0;
  this->selected_sprite = 0;
  this->option_tail = 0;
  this->option_list = this->option_tail;
  this->line_list = 0;
  this->sprite_list = 0;
  this->edit_field_list = 0;
  this->option_spacing = 0;
  this->pad_y = 2;
  this->pad_x = 2;
  this->section_gap = 4;
  this->sprite_gap = 4;
  this->border_width = 8;
  this->bevel_width = 2;
  this->option_extra_width = 0;
  this->columns = 1;
  this->list2_left_col = 0;
  this->list_left_col = this->list2_left_col;
  this->sprite_zoom = 0;
  this->title_text = 0;
  this->radio_group = 0;
  this->checkboxes = 0;
  this->edit_controls = 0;
  this->button_controls = 0;
  this->listbox2 = 0;
  this->listbox = this->listbox2;
  this->sprite_hotspots = 0;
  this->list2_vscroll = 0;
  this->list_vscroll = this->list2_vscroll;
  this->list2_hscroll = 0;
  this->list_hscroll = this->list2_hscroll;
  this->on_draw_sprite = 0;
  this->on_sprite_click = 0;
  this->on_sprite_dblclick = 0;
  this->on_draw_option = 0;
  this->on_select_change = 0;
  this->on_modal_poll = 0;
  this->result_id = 0;
  this->result_extra = 0;
  return;
}
#undef dialog_default_list_color
#undef dlg_bevel_dark_color
#undef dlg_bevel_light_color
#undef dlg_bg_color
#undef dlg_default_x
#undef dlg_default_y
#undef dlg_frame_color
#undef dlg_highlight_text_color
#undef dlg_scale_den
#undef dlg_scale_num
#undef dlg_sel_text_color
#undef dlg_sel_text_shadow_color
#undef dlg_text_color
#undef dlg_text_shadow_color
#undef dlg_title_shadow_color
#undef dlg_title_text_color
#undef list_bg_color
#undef list_sel_bg_color
#undef list_shadow_color
#undef list_text_color
#undef i

/* 0059db08 auto */
Dialog * __thiscall dialog_ctor(Dialog *this,i32 size)

{
  memblock_ctor((MemBlock *)this->string_pool);
  this->pool_ptr = 0;
  this->pool_handle = this->pool_ptr;
  dialog_init_defaults(this);
  this->pool_size = (u16)size;
  return this;
}

/* 0059db65 auto */
#define dialog_stack (*(i32 *)((u8 *)&g.d_00635a58))
#define dialog_stack_top (*(iptr *)((u8 *)&g.d_006ad678))
#define dlg_parent_window (*(WndBase * *)((u8 *)&g.d_006359c4))
#define main_frame_created (*(int *)((u8 *)&g.d_00634718))
#define dialog_timeout_start_i32 (*(i32 *)((u8 *)&g.d_006cec80))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall dialog_close(Dialog *this)

{
  if (dlg_parent_window == (WndBase *)0x0) {
    if (main_frame_created != 0) {
      wnd_focus_and_raise((WndBase *)&main_frame_wnd);
    }
  }
  else {
    wnd_focus_and_raise(dlg_parent_window);
  }
  if (this->radio_group != 0) {
    if ((RadioGroupDtorView *)this->radio_group != (RadioGroupDtorView *)0x0) {
      radiogrp_scalar_dtor((RadioGroupDtorView *)this->radio_group,1);
    }
    this->radio_group = 0;
  }
  if (this->checkboxes != 0) {
    if ((Checkbox *)this->checkboxes != (Checkbox *)0x0) {
      checkbox_vector_dtor((Checkbox *)this->checkboxes,3);
    }
    this->checkboxes = 0;
  }
  if (this->edit_controls != 0) {
    if ((Control *)this->edit_controls != (Control *)0x0) {
      edit_vector_dtor((Control *)this->edit_controls,3);
    }
    this->edit_controls = 0;
  }
  if (this->button_controls != 0) {
    if ((Control *)this->button_controls != (Control *)0x0) {
      ctrl_vector_dtor((Control *)this->button_controls,3);
    }
    this->button_controls = 0;
  }
  if (this->listbox != 0) {
    if ((ListBoxControl *)this->listbox != (ListBoxControl *)0x0) {
      listbox_scalar_dtor((ListBoxControl *)this->listbox,1);
    }
    this->listbox = 0;
  }
  if (this->listbox2 != 0) {
    if ((ListBoxControl *)this->listbox2 != (ListBoxControl *)0x0) {
      listbox_scalar_dtor((ListBoxControl *)this->listbox2,1);
    }
    this->listbox2 = 0;
  }
  if (this->sprite_hotspots != 0) {
    if ((Hotspot *)this->sprite_hotspots != (Hotspot *)0x0) {
      hotspot_vector_dtor((Hotspot *)this->sprite_hotspots,3);
    }
    this->sprite_hotspots = 0;
  }
  if (this->list_vscroll != 0) {
    if ((Control *)this->list_vscroll != (Control *)0x0) {
      scrollbar_scalar_dtor((Control *)this->list_vscroll,1);
    }
    this->list_vscroll = 0;
  }
  if (this->list2_vscroll != 0) {
    if ((Control *)this->list2_vscroll != (Control *)0x0) {
      scrollbar_scalar_dtor((Control *)this->list2_vscroll,1);
    }
    this->list2_vscroll = 0;
  }
  if (this->list_hscroll != 0) {
    if ((Control *)this->list_hscroll != (Control *)0x0) {
      scrollbar_scalar_dtor((Control *)this->list_hscroll,1);
    }
    this->list_hscroll = 0;
  }
  if (this->list2_hscroll != 0) {
    if ((Control *)this->list2_hscroll != (Control *)0x0) {
      scrollbar_scalar_dtor((Control *)this->list2_hscroll,1);
    }
    this->list2_hscroll = 0;
  }
  if (((this->style_flags & 0x10) == 0) && (this->surf_wnd != 0)) {
    if ((SurfaceWindow *)this->surf_wnd != (SurfaceWindow *)0x0) {
      surfwnd_scalar_dtor((SurfaceWindow *)this->surf_wnd,1);
    }
    this->surf_wnd = 0;
    this->style_flags = this->style_flags | 0x10;
  }
  if (this == (Dialog *)active_dialog) {
    if ((dialog_stack_depth < 1) || (0x10 < dialog_stack_depth)) {
      err_report((ErrorContext *)&err_report_ctx,7,(iptr)((u8 *)&g.d_00635aec),(iptr)((u8 *)&g.d_00635acc),0x19c);
    }
    dialog_stack_depth--;
    dialog_stack_top = (&dialog_stack)[dialog_stack_depth];
    active_dialog = dialog_stack_top;
    dialog_timeout_start_i32 = timer_ticks();
  }
  return;
}
#undef dialog_stack
#undef dialog_stack_top
#undef dlg_parent_window
#undef main_frame_created
#undef dialog_timeout_start_i32

/* 0059df8a auto */
i32 __thiscall dialog_dtor(Dialog *this)

{
  i32 result;
  
  dialog_close(this);
  result = memblock_free((iptr)this->string_pool);
  return result;
}

/* 0059dfb9 auto */
void __thiscall
dialog_init
          (Dialog *this,iptr surface_wnd,iptr background,iptr rect,u32 flags)

{
  i32 size;
  
  if ((this->style_flags & 0x20) == 0) {
    memblock_init((iptr)this->string_pool,9,CONCAT22((short)((uint)this >> 0x10),this->pool_size));
  }
  else {
    dialog_close(this);
    dialog_init_defaults(this);
    dialog_reset_string_pool((DialogCore *)this,(uint)this->pool_size);
  }
  dialog_set_font((DialogTextView *)this,(iptr)dialog_default_text_font);
  dialog_set_title_font((DialogCore *)this,(iptr)dialog_default_title_font);
  dialog_set_list_font((DialogCore *)this,(iptr)dialog_default_list_font);
  this->surf_wnd = surface_wnd;
  this->bg_surface = background;
  this->result_id = 0;
  this->style_flags = flags;
  if (rect == 0) {
    dialog_set_width((DialogWindowView *)this,0x1b8);
  }
  else {
    this->origin_x = *(u32 *)rect;
    this->origin_y = *(u32 *)(rect + 4);
    size = rect_width(rect);
    dialog_set_width((DialogWindowView *)this,size);
    size = rect_height(rect);
    dialog_set_height((DialogCore *)this,size);
  }
  if (surface_wnd != 0) {
    this->style_flags = this->style_flags | 0x10;
  }
  return;
}

/* 0059e0eb auto */
#define line (*(int * *)(frame_ + FRAME_OFF(0)))
i32 __thiscall dialog_set_item_text(void *this,int line_id,iptr text)

{
  size_t len;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (line = *(int **)((int)this + 0x230); (*line != line_id && (line != (int *)0x0));
      line = (int *)line[7]) {
  }
  if (((line != (int *)0x0) && (-1 < line[3])) &&
     (len = _strlen((char *)text), (int)(len + 1) <= line[3])) {
    crt_strcpy(line[2],text);
    return 1;
  }
  return 0;
}
#undef line

/* 0059e18b auto */
#define last (*(int * *)(frame_ + FRAME_OFF(4)))
#define cur (*(int * *)(frame_ + FRAME_OFF(8)))
int * __thiscall
dialog_add_line
          (DialogAddLineView *this,iptr text,int x,int y,int max_len,int color)

{
  int *line;
  size_t len;
  int buffer;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  last = (int *)0x0;
  for (cur = (int *)this->line_list; cur != (int *)0x0; cur = (int *)cur[7]) {
    last = cur;
  }
  line = (int *)memblock_alloc((iptr)(this->line_storage),0x20);
  if (last == (int *)0x0) {
    this->line_list = (uptr)line;
    *line = 1;
  }
  else {
    last[7] = (int)line;
    *line = *last + 1;
  }
  line[7] = 0;
  line[1] = 0;
  if (*(char *)text == '^') {
    if (*(char *)(text + 1) == '^') {
      line[1] = line[1] | 1;
      text += 2;
    }
    else {
      line[1] = line[1] | 2;
      text++;
    }
  }
  if (0 < max_len) {
    len = _strlen((char *)text);
    if ((int)(len + 1) < max_len) {
      buffer = memblock_alloc((iptr)(this->line_storage),max_len + 1);
      line[2] = buffer;
      line[3] = max_len + 1;
      goto LAB_0059e2e4;
    }
  }
  len = _strlen((char *)text);
  buffer = memblock_alloc((iptr)(this->line_storage),len + 1);
  line[2] = buffer;
  len = _strlen((char *)text);
  line[3] = len + 1;
LAB_0059e2e4:
  crt_strcpy(line[2],text);
  line[4] = x;
  line[5] = y;
  line[6] = color;
  this->line_count++;
  return line;
}
#undef last
#undef cur

/* 0059e356 auto */
i32 __thiscall dialog_option_icon_width(DialogCore *this)

{
  return 0x20;
}

/* 0059e376 auto */
#define result (*(int *)(frame_ + FRAME_OFF(4)))
#define icon_width (*(int *)(frame_ + FRAME_OFF(8)))
int __thiscall dialog_option_row_height(DialogCore *this)

{
  int spacing;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  icon_width = dialog_option_icon_width(this);
  spacing = font_line_spacing((GameFont *)this->body_font);
  if (spacing * 5 >> 2 <= icon_width) {
    spacing = font_line_spacing((GameFont *)this->body_font);
    icon_width = spacing * 5 >> 2;
  }
  spacing = font_line_spacing((GameFont *)this->body_font);
  if (spacing < icon_width) {
    result = icon_width;
  }
  else {
    result = font_line_spacing((GameFont *)this->body_font);
  }
  return result;
}
#undef result
#undef icon_width

/* 0059e3fa auto */
u32 __thiscall dialog_list_row_height(DialogTextView *this)

{
  int font_height;
  u32 result;
  
  if ((&((DialogWindowView *)this)->list_row_height_override)[this->cur_pane] == 0) {
    font_height = font_cached_height((GameFont *)this->list_font);
    result = font_height + 1;
  }
  else {
    result = (&((DialogWindowView *)this)->list_row_height_override)[this->cur_pane];
  }
  return result;
}

/* 0059e448 auto */
int __thiscall dialog_edit_row_height(DialogCore *this)

{
  int spacing;
  
  spacing = font_line_spacing((GameFont *)this->body_font);
  return spacing + 10;
}

/* 0059e472 auto */
void __thiscall dialog_set_font(DialogTextView *this,iptr font)

{
  u32 row_height;
  
  this->body_font = font;
  row_height = dialog_option_row_height((DialogCore *)this);
  this->option_row_height = row_height;
  return;
}

/* 0059e4a4 auto */
/* Library Function - Single Match
    public: void __thiscall CArchive::SetObjectSchema(unsigned int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall dialog_set_title_font(DialogCore *this,iptr font)

{
  this->title_font = font;
  return;
}

/* 0059e4c5 auto */
void __thiscall dialog_set_list_font(DialogCore *this,iptr font)

{
  this->list_font = font;
  return;
}

/* 0059e4e6 auto */
void __thiscall dialog_set_columns(DialogButtonsView *this,u32 column_count)

{
  this->columns = column_count;
  return;
}

/* 0059e507 auto */
void __thiscall dialog_set_list_rows(DialogTextView *this,u32 rows)

{
  int row_height;
  
  this->style_flags = this->style_flags | 0x1000;
  (&this->list_rows)[this->cur_pane] = rows;
  if ((this->style_flags & 0x40000) == 0) {
    row_height = dialog_list_row_height(this);
    (&this->list_height)[this->cur_pane] = row_height * rows + 2;
  }
  else {
    row_height = font_cached_height((GameFont *)&default_draw_font_obj);
    (&this->list_height)[this->cur_pane] = row_height * rows + 2;
  }
  return;
}

/* 0059e585 auto */
void __thiscall dialog_set_current_pane(DialogSetCurrentPaneView *this,u32 pane)

{
  if ((pane == 0) || (pane == 1)) {
    this->cur_pane = pane;
  }
  else {
    this->cur_pane = 0;
  }
  return;
}

/* 0059e5c9 auto */
void __thiscall dialog_set_listbox(DialogTextView *this,int rows,u32 width,u32 list_flags)

{
  this->style_flags = this->style_flags | 0x1000;
  (&this->list_width)[this->cur_pane] = width;
  (&((DialogWindowView *)this)->list_x_offset)[this->cur_pane] = list_flags;
  if (rows != 0) {
    dialog_set_list_rows(this,rows);
  }
  return;
}

/* 0059e648 auto */
int __thiscall dialog_line_height(DialogTextView *this)

{
  int spacing;
  
  spacing = font_line_spacing((GameFont *)this->body_font);
  return spacing + 4 + this->pad_y * 2;
}

/* 0059e676 auto */
int __thiscall dialog_button_width_for(DialogButtonWidthForView *this,iptr text)

{
  u32 padding;
  int text_width;
  
  padding = this->button_padding;
  text_width = font_text_width((GameFont *)&dialog_plain_font_obj,text);
  return text_width + 4 + padding * 4;
}

/* 0059e6a9 auto */
void __thiscall dialog_set_title(DialogWindowView *this,iptr title)

{
  size_t len;
  uptr buffer;
  
  len = _strlen((char *)title);
  buffer = memblock_alloc((iptr)&((DialogTextLineView *)this)->string_pool,len + 1);
  this->title_text = buffer;
  crt_strcpy(this->title_text,title);
  return;
}

/* 0059e6ff auto */
void __thiscall dialog_set_width(DialogWindowView *this,u32 width)

{
  if ((this->scale_num != this->scale_den) && ((this->style_flags & 0x80000) == 0)) {
    width = (int)(this->scale_num * width) / (int)this->scale_den;
  }
  this->content_width = width;
  return;
}

/* 0059e762 auto */
/* Library Function - Single Match
    public: void __thiscall ios::delbuf(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall dialog_set_height(DialogCore *this,u32 height)

{
  this->min_height = height;
  return;
}

/* 0059e783 auto */
void __thiscall dialog_set_position(DialogCore *this,u32 x,u32 y)

{
  this->req_x = x;
  this->req_y = y;
  return;
}

/* 0059e7ad auto */
#define cur (*(uptr *)(frame_ + FRAME_OFF(4)))
#define found (*(uptr *)(frame_ + FRAME_OFF(8)))
uptr __thiscall dialog_find_option(DialogOptionList *this,int option_id)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  found = 0;
  cur = this->option_list;
  while ((cur != 0 && (found == 0))) {
    if (*(int *)(cur + 4) == option_id) {
      found = cur;
    }
    cur = *(uptr *)(cur + 0x10);
  }
  return found;
}
#undef cur
#undef found

/* 0059e877 auto */
#define cur (*(int * *)(frame_ + FRAME_OFF(4)))
#define found (*(int * *)(frame_ + FRAME_OFF(8)))
int * __thiscall dialog_find_sprite(DialogOptionList *this,int sprite_id)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  found = (int *)0x0;
  cur = (int *)this->sprite_list;
  while ((cur != (int *)0x0 && (found == (int *)0x0))) {
    if (*cur == sprite_id) {
      found = cur;
    }
    cur = (int *)cur[4];
  }
  return found;
}
#undef cur
#undef found

/* 0059e8db auto */
void __thiscall dialog_set_option_disabled(DialogOptionList *this,iptr option_id,int disabled)

{
  uint *option;
  
  option = (uint *)dialog_find_option(this,option_id);
  if (option != (uint *)0x0) {
    if (disabled == 0) {
      *option = *option & 0xfffffffe;
    }
    else {
      *option = *option | 1;
    }
  }
  return;
}

/* 0059e9f3 auto */
#define checked (*(i32 *)(frame_ + FRAME_OFF(0)))
i32 __thiscall dialog_option_is_checked(DialogOptionList *this,i32 option_id)

{
  byte *option;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  checked = 0;
  option = (byte *)dialog_find_option(this,option_id);
  if (option != (byte *)0x0) {
    if ((*option & 4) == 0) {
      checked = 0;
    }
    else {
      checked = 1;
    }
  }
  return checked;
}
#undef checked

/* 0059ea4d auto */
void __thiscall dialog_set_option_checked(DialogOptionList *this,i32 option_id,int checked)

{
  uint *option;
  
  option = (uint *)dialog_find_option(this,option_id);
  if (option != (uint *)0x0) {
    if (checked == 0) {
      *option = *option & 0xfffffffb;
    }
    else {
      *option = *option | 4;
    }
  }
  return;
}

/* 0059ea99 auto */
void __thiscall dialog_set_default_choice(DialogOptionList *this,iptr choice_id)

{
  uptr entry;
  
  if (this->option_count == 0) {
    entry = dialog_find_sprite(this,choice_id);
    if (entry != 0) {
      this->selected_sprite = entry;
    }
  }
  else {
    entry = dialog_find_option(this,choice_id);
    if (entry != 0) {
      this->selected_option = entry;
    }
  }
  return;
}

/* 0059eb8c auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall dialog_set_sprite_click_fn(DialogOptionList *this,iptr callback)

{
  this->on_sprite_click = callback;
  return;
}

/* 0059ebb0 auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall dialog_set_sprite_dblclick_fn(DialogOptionList *this,iptr callback)

{
  this->on_sprite_dblclick = callback;
  return;
}

/* 0059ebd4 auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall dialog_set_sprite_draw_fn(DialogCore *this,iptr callback)

{
  ((DialogTextLineView *)this)->sprite_draw_callback = callback;
  return;
}

/* 0059ebf8 auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall dialog_set_option_draw_fn(DialogOptionList *this,iptr callback)

{
  this->on_draw_option = callback;
  return;
}

/* 0059ec1c auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall dialog_set_select_change_fn(DialogSelChangeSetView *this,iptr callback)

{
  this->on_select_change = callback;
  return;
}

/* 0059ec64 auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall dialog_set_image_zoom(DialogWindowView *this,u32 zoom)

{
  this->sprite_zoom = zoom;
  return;
}

/* 0059ec88 auto */
#define last (*(uptr *)(frame_ + FRAME_OFF(0)))
#define cur (*(uptr *)(frame_ + FRAME_OFF(4)))
#define entry_width (*(u32 *)(frame_ + FRAME_OFF(8)))
iptr * __thiscall
dialog_add_sprite(DialogOptionList *this,iptr sprite,iptr sprite_id,iptr label)

{
  iptr *entry;
  size_t len;
  iptr label_buf;
  int label_width;
  u32 max_width;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  last = 0;
  for (cur = this->sprite_list; cur != 0; cur = *(uptr *)(cur + 0x10)) {
    last = cur;
  }
  entry = (iptr *)memblock_alloc((iptr)this->string_pool,0x14);
  if (last == 0) {
    this->sprite_list = (uptr)entry;
    if (this->selected_sprite == 0) {
      this->selected_sprite = (uptr)entry;
    }
  }
  else {
    *(iptr **)(last + 0x10) = entry;
  }
  entry[4] = 0;
  entry[1] = 0;
  entry[3] = sprite;
  entry_width = sprite_width((Sprite *)sprite);
  if (label == 0) {
    entry[2] = 0;
  }
  else {
    len = _strlen((char *)label);
    label_buf = memblock_alloc((iptr)this->string_pool,len + 1);
    entry[2] = label_buf;
    crt_strcpy(entry[2],label);
    label_width = font_text_width((GameFont *)this->body_font,entry[2]);
    entry_width = entry_width + this->sprite_gap + label_width;
  }
  *entry = sprite_id;
  max_width = this->max_sprite_width;
  if ((int)this->max_sprite_width <= (int)entry_width) {
    max_width = entry_width;
  }
  this->max_sprite_width = max_width;
  this->sprite_count++;
  return entry;
}
#undef last
#undef cur
#undef entry_width

/* 0059edf0 auto */
#define prev (*(uptr *)(frame_ + FRAME_OFF(0)))
#define cur (*(uptr *)(frame_ + FRAME_OFF(4)))
uint * __thiscall
dialog_add_option(DialogOptionList *this,iptr text,iptr option_id,uint data)

{
  u32 width;
  int cmp;
  uint *option;
  size_t len;
  uint text_buf;
  int icon_width;
  u32 max_width;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  prev = 0;
  cur = this->option_list;
  if (((this->style_flags & 0x800000) == 0) || (cur == 0)) {
    if (cur != 0) {
      for (; cur != 0; cur = *(uptr *)(cur + 0x10)) {
        prev = cur;
      }
    }
  }
  else {
    while ((cur != 0 && (cmp = __strcmpi((char *)text,*(char **)(cur + 8)), 0 < cmp))
          ) {
      prev = cur;
      cur = *(uptr *)(cur + 0x10);
    }
  }
  option = (uint *)memblock_alloc((iptr)this->string_pool,0x18);
  if (prev == 0) {
    option[4] = this->option_list;
    option[5] = 0;
    if (this->option_list == 0) {
      this->option_tail = (u32)option;
    }
    else {
      *(uint **)(this->option_list + 0x14) = option;
    }
    this->option_list = (uptr)option;
    this->selected_option = (uptr)option;
  }
  else {
    option[4] = *(uint *)(prev + 0x10);
    option[5] = prev;
    if (option[4] == 0) {
      this->option_tail = (u32)option;
    }
    else {
      *(uint **)(option[4] + 0x14) = option;
    }
    *(uint **)(prev + 0x10) = option;
  }
  *option = 0;
  len = _strlen((char *)text);
  text_buf = memblock_alloc((iptr)this->string_pool,len + 1);
  option[2] = text_buf;
  crt_strcpy(option[2],text);
  if (*(char *)text == '\0') {
    *option = *option | 1;
  }
  option[1] = option_id;
  option[3] = data;
  cmp = font_text_width((GameFont *)this->body_font,option[2]);
  icon_width = dialog_option_icon_width((DialogCore *)this);
  width = cmp + icon_width + this->option_extra_width + 5;
  max_width = this->option_width;
  if ((int)this->option_width <= (int)width) {
    max_width = width;
  }
  this->option_width = max_width;
  this->option_count++;
  return option;
}
#undef prev
#undef cur

/* 0059f026 auto */
uint * __thiscall
dialog_add_checkbox_option(DialogOptionList *this,iptr text,iptr option_id,int checked)

{
  uint *option;
  
  this->style_flags = this->style_flags | 5;
  option = (uint *)dialog_add_option(this,text,option_id,0);
  if (checked != 0) {
    *option = *option | 4;
  }
  return option;
}

/* 0059f06d auto */
#define last (*(uptr *)(frame_ + FRAME_OFF(4)))
#define cur (*(uptr *)(frame_ + FRAME_OFF(8)))
#define field_width (*(u32 *)(frame_ + FRAME_OFF(16)))
i32 * __thiscall
dialog_add_edit_field(DialogOptionList *this,iptr label,iptr initial_text,size_t max_len)

{
  i32 *field;
  size_t len;
  i32 buffer;
  u32 label_width;
  int char_width;
  u32 max_width;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  last = 0;
  for (cur = this->edit_field_list; cur != 0; cur = *(uptr *)(cur + 0x18)) {
    last = cur;
  }
  field = (i32 *)memblock_alloc((iptr)this->string_pool,0x1c);
  if (last == 0) {
    this->edit_field_list = (u32)field;
  }
  else {
    *(i32 **)(last + 0x18) = field;
  }
  field[6] = 0;
  *field = 0;
  len = _strlen((char *)label);
  buffer = memblock_alloc((iptr)this->string_pool,len + 2);
  field[4] = buffer;
  crt_strcpy(field[4],label);
  label_width = font_text_width((GameFont *)this->body_font,field[4]);
  max_width = this->edit_label_width;
  if ((int)this->edit_label_width <= (int)label_width) {
    max_width = label_width;
  }
  this->edit_label_width = max_width;
  if (0xfe < (int)max_len) {
    max_len = 0xff;
  }
  field[2] = max_len;
  buffer = memblock_alloc((iptr)this->string_pool,0x100);
  field[5] = buffer;
  char_width = font_text_width((GameFont *)ctrl_default_font,(iptr)((u8 *)&g.d_00635b18));
  field[1] = char_width * max_len;
  field_width = field[1] + this->edit_label_width;
  if ((this->content_width != 0) && ((int)this->content_width < (int)field_width)) {
    field[1] -= ((field_width - this->content_width) - 3);
    field_width = field[1] + this->edit_label_width + 3;
  }
  max_width = this->edit_width;
  if ((int)this->edit_width <= (int)field_width) {
    max_width = field_width;
  }
  this->edit_width = max_width;
  if (initial_text == 0) {
    *(i8 *)field[5] = 0;
  }
  else {
    _memset((void *)field[5],0,0x100);
    _strncpy((char *)field[5],(char *)initial_text,max_len);
  }
  field[3] = this->edit_count;
  this->edit_count++;
  return field;
}
#undef last
#undef cur
#undef field_width

/* 0059f2a3 auto */
void __thiscall dialog_add_button(DialogButtonsView *this,iptr label)

{
  size_t len;
  uptr buffer;
  
  if ((int)this->extra_button_count < 6) {
    len = _strlen((char *)label);
    buffer = memblock_alloc((iptr)&((DialogTextLineView *)this)->string_pool,len + 1);
    (&((Dialog *)this)->extra_button_labels)[this->extra_button_count] = buffer;
    crt_strcpy((&((Dialog *)this)->extra_button_labels)[this->extra_button_count],label);
    this->extra_button_count++;
  }
  return;
}

/* 0059f31a auto */
#define normal_color (*(u32 *)(frame_ + FRAME_OFF(0)))
#define alt_color (*(u32 *)(frame_ + FRAME_OFF(4)))
#define hilite_color (*(u32 *)(frame_ + FRAME_OFF(8)))
void __thiscall dialog_set_text_color(DialogTextView *this,int highlighted,int use_alt,int shadow)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (highlighted == 0) {
    if (use_alt == 0) {
      if (shadow == 0) {
        normal_color = this->text_color;
      }
      else {
        normal_color = this->shadow_color;
      }
      gfx_set_text_color_index(normal_color);
    }
    else {
      if (shadow == 0) {
        alt_color = this->frame_color;
      }
      else {
        alt_color = this->shadow_color;
      }
      gfx_set_text_color_index(alt_color);
    }
  }
  else {
    if (shadow == 0) {
      hilite_color = this->highlight_color;
    }
    else {
      hilite_color = this->shadow_color;
    }
    gfx_set_text_color_index(hilite_color);
  }
  return;
}
#undef normal_color
#undef alt_color
#undef hilite_color

/* 0059f3d7 auto */
int __thiscall
dialog_draw_text_shadowed
          (DialogTextView *this,iptr font,char *text,int x,int y,uint flags)

{
  char *underscore;
  i32 use_alt;
  int text_width;
  i32 shadow;
  
  while (underscore = _strchr(text,0x5f), underscore != (char *)0x0) {
    *underscore = ' ';
  }
  if (this->shadow_color != this->text_color) {
    shadow = 1;
    use_alt = dialog_uses_alt_text_color((DialogAltColorView *)this);
    dialog_set_text_color(this,flags & 1,use_alt,shadow);
    surface_draw_text
              ((DibSurface *)this->surf_wnd,font,(iptr)text,x + 1,y + 1,5);
  }
  shadow = 0;
  use_alt = dialog_uses_alt_text_color((DialogAltColorView *)this);
  dialog_set_text_color(this,flags & 1,use_alt,shadow);
  surface_draw_text
            ((DibSurface *)this->surf_wnd,font,(iptr)text,x,y,5);
  text_width = font_text_width((GameFont *)font,(iptr)text);
  return x + text_width;
}

/* 0059f5ba auto */
void __thiscall
dialog_draw_text_line(DialogTextLineView *this,iptr text,int x_offset,i32 y)

{
  dialog_draw_text_default_font
            ((DialogTextView *)this,text,this->text_x + x_offset,y,0);
  return;
}

/* 0059f5f7 auto */
#define line (*(uptr *)(frame_ + FRAME_OFF(0)))
i32 __thiscall dialog_has_text_lines(DialogOptionList *this)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  line = this->line_list;
  while( true ) {
    if (line == 0) {
      return 0;
    }
    if (*(int *)(line + 0x10) < 0) break;
    line = *(uptr *)(line + 0x1c);
  }
  return 1;
}
#undef line

/* 0059f64a auto */
#define line_y (*(u32 *)(frame_ + FRAME_OFF(0)))
#define src (*(char * *)(frame_ + FRAME_OFF(8)))
#define total_height (*(int *)(frame_ + FRAME_OFF(12)))
#define y2 (*(u32 *)(frame_ + FRAME_OFF(20)))
#define x2 (*(int *)(frame_ + FRAME_OFF(28)))
#define line_buf (*(char (*)[256])(frame_ + FRAME_OFF(40)))
#define word_buf (*(char *)(frame_ + FRAME_OFF(296)))
#define word_rest (*(i8 (*)[79])(frame_ + FRAME_OFF(297)))
#define line_width (*(int *)(frame_ + FRAME_OFF(376)))
#define line (*(uptr *)(frame_ + FRAME_OFF(380)))
#define line_height (*(int *)(frame_ + FRAME_OFF(384)))
int __thiscall dialog_draw_wrapped_text(DialogOptionList *this,int draw)

{
  u32 max_width;
  int text_width;
  uptr remaining;
  char *space;
  uptr word_len;
  int buf_width;
  int center_x;
  bool has_shadow;
  i8 frame_[FRAME_OFF(392)] __attribute__((aligned(8)));  /* original stack frame */
  
  has_shadow = this->shadow_color != this->text_color;
  line = this->line_list;
  max_width = this->content_width;
  total_height = 0;
  y2 = this->text_y;
  line_height = font_line_spacing((GameFont *)this->body_font);
  line_buf[0] = '\0';
  line_width = 0;
  for (; center_x = (int)max_width >> 1, line != 0; line = *(uptr *)(line + 0x1c)) {
    if (*(int *)(line + 0x10) < 1) {
      src = *(char **)(line + 8);
      if ((*(byte *)(line + 4) & 3) != 0) {
        if (line_buf[0] != '\0') {
          if (draw != 0) {
            dialog_draw_text_line((DialogTextLineView *)this,(iptr)line_buf,0,y2);
          }
          total_height += line_height;
          y2 += line_height;
          line_buf[0] = '\0';
          line_width = 0;
        }
        if (draw != 0) {
          if ((*(byte *)(line + 4) & 1) == 0) {
            x2 = 0;
          }
          else if (*(int *)(line + 0x18) == 0) {
            text_width = font_text_width((GameFont *)this->body_font,(iptr)src);
            x2 = center_x - ((int)((uint)has_shadow + text_width) >> 1);
          }
          else {
            x2 = *(int *)(line + 0x18);
            text_width = font_text_width((GameFont *)this->body_font,(iptr)src);
            x2 -= ((int)((uint)has_shadow + text_width) >> 1);
          }
          if (*(int *)(line + 0x14) == -1) {
            line_y = y2;
          }
          else {
            line_y = *(u32 *)(line + 0x14);
          }
          dialog_draw_text_line
                    ((DialogTextLineView *)this,(iptr)src,x2,line_y);
        }
        for (; *src != '\0'; src++) {
        }
        if (*(int *)(line + 0x14) < 0) {
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
        word_buf = '\0';
        if (line_buf[0] != '\0') {
          crt_strcat(&word_buf,&dialog_wrap_space_str);
        }
        crt_strcat(&word_buf,src);
        text_width = font_text_width((GameFont *)this->body_font,(iptr)&word_buf);
        if ((int)max_width < (int)((uint)has_shadow + text_width + line_width)) {
          if (draw != 0) {
            if ((this->style_flags & 0x200000) == 0) {
              x2 = 0;
            }
            else {
              buf_width = font_text_width
                                ((GameFont *)this->body_font,(iptr)line_buf);
              x2 = center_x - ((int)((uint)has_shadow + buf_width) >> 1);
            }
            dialog_draw_text_line
                      ((DialogTextLineView *)this,(iptr)line_buf,x2,y2);
          }
          total_height += line_height;
          y2 += line_height;
          while (word_buf == ' ') {
            crt_strcpy(&word_buf,word_rest);
          }
          line_buf[0] = '\0';
          line_width = 0;
        }
        crt_strcat(line_buf,&word_buf);
        line_width += text_width;
        if (space != (char *)0x0) {
          *space = ' ';
        }
        src += word_len;
      }
    }
    else if (draw != 0) {
      dialog_draw_text_default_font
                ((DialogTextView *)this,*(i32 *)(line + 8),*(i32 *)(line + 0x10),
                 *(i32 *)(line + 0x14),*(i32 *)(line + 4));
    }
  }
  if (line_buf[0] != '\0') {
    if (draw != 0) {
      if ((this->style_flags & 0x200000) == 0) {
        x2 = 0;
      }
      else {
        text_width = font_text_width((GameFont *)this->body_font,(iptr)line_buf);
        x2 = center_x - ((int)((uint)has_shadow + text_width) >> 1);
      }
      dialog_draw_text_line((DialogTextLineView *)this,(iptr)line_buf,x2,y2)
      ;
    }
    total_height += line_height;
  }
  return total_height;
}
#undef line_y
#undef src
#undef total_height
#undef y2
#undef x2
#undef line_buf
#undef word_buf
#undef word_rest
#undef line_width
#undef line
#undef line_height

/* 0059fb78 auto */
#define index (*(int *)(frame_ + FRAME_OFF(4)))
#define cur (*(uptr *)(frame_ + FRAME_OFF(8)))
i32 __thiscall dialog_option_group_index(DialogOptionList *this,uptr option)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (this->option_list != 0) {
    index = 0;
    for (cur = this->option_list; cur != 0; cur = *(uptr *)(cur + 0x10)) {
      if ((*(int *)(option + 0xc) == *(int *)(cur + 0xc)) && (option == cur)) {
        return index;
      }
      if (*(int *)(option + 0xc) == *(int *)(cur + 0xc)) {
        index++;
      }
    }
  }
  return 0;
}
#undef index
#undef cur

/* 0059fc19 auto */
#define index (*(int *)(frame_ + FRAME_OFF(4)))
#define cur (*(uptr *)(frame_ + FRAME_OFF(8)))
i32 __thiscall dialog_option_at(DialogOptionList *this,int target_index)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (this->option_list != 0) {
    index = 0;
    for (cur = this->option_list; cur != 0; cur = *(uptr *)(cur + 0x10)) {
      if ((this->cur_pane == *(u32 *)(cur + 0xc)) && (index == target_index)) {
        return cur;
      }
      if (this->cur_pane == *(u32 *)(cur + 0xc)) {
        index++;
      }
    }
  }
  return 0;
}
#undef index
#undef cur

/* 0059fcba auto */
int __thiscall dialog_column_of_option(DialogOptionList *this,uptr option)

{
  int group_index;
  
  group_index = dialog_option_group_index(this,option);
  return group_index / (int)(&this->list_rows)[this->cur_pane];
}

/* 0059fd2a auto */
#define dialog_clamp_overflow (*(int *)((u8 *)&g.d_0062f004))
#define main_frame_created (*(int *)((u8 *)&g.d_00634718))
#define button_x (*(int *)(frame_ + FRAME_OFF(0)))
#define text_height (*(int *)(frame_ + FRAME_OFF(8)))
#define top_index (*(int *)(frame_ + FRAME_OFF(12)))
#define frame_rect2 (*(i8 (*)[12])(frame_ + FRAME_OFF(16)))
#define frame_bottom2 (*(int *)(frame_ + FRAME_OFF(28)))
#define text_width (*(u32 *)(frame_ + FRAME_OFF(32)))
#define screen_rect2 (*(i8 (*)[8])(frame_ + FRAME_OFF(36)))
#define screen_right (*(int *)(frame_ + FRAME_OFF(44)))
#define screen_bottom (*(int *)(frame_ + FRAME_OFF(48)))
#define result (*(i32 *)(frame_ + FRAME_OFF(52)))
#define remainder_acc (*(int *)(frame_ + FRAME_OFF(56)))
#define rows (*(int *)(frame_ + FRAME_OFF(60)))
#define left (*(u32 *)(frame_ + FRAME_OFF(64)))
#define extra_space (*(int *)(frame_ + FRAME_OFF(68)))
#define top (*(u32 *)(frame_ + FRAME_OFF(72)))
#define avail_width (*(u32 *)(frame_ + FRAME_OFF(76)))
#define sprites_height (*(int *)(frame_ + FRAME_OFF(80)))
#define edit_height (*(int *)(frame_ + FRAME_OFF(84)))
#define sprite (*(uptr *)(frame_ + FRAME_OFF(88)))
#define i (*(uptr *)(frame_ + FRAME_OFF(92)))
#define sprite_width2 (*(u32 *)(frame_ + FRAME_OFF(96)))
#define line (*(uptr *)(frame_ + FRAME_OFF(100)))
#define lists_height (*(u32 *)(frame_ + FRAME_OFF(104)))
#define first_option (*(uptr *)(frame_ + FRAME_OFF(108)))
#define content_height (*(int *)(frame_ + FRAME_OFF(112)))
i32 __thiscall dialog_compute_layout(DialogOptionList *this)

{
  u32 pos;
  int value;
  size_t len;
  i32 height;
  u32 tmp;
  uptr column_count;
  i8 frame_[FRAME_OFF(120)] __attribute__((aligned(8)));  /* original stack frame */
  
  result = 1;
  text_height = 0;
  lists_height = 0;
  edit_height = 0;
  if ((this->style_flags & 0x100000) == 0) {
    for (line = this->line_list; line != 0; line = *(uptr *)(line + 0x1c)) {
      if ((*(byte *)(line + 4) & 3) != 0) {
        tmp = this->shadow_color;
        pos = this->text_color;
        value = font_text_width
                          ((GameFont *)this->body_font,*(iptr *)(line + 8));
        text_width = (uint)(tmp != pos) + value;
        tmp = this->content_width;
        if ((int)this->content_width <= (int)text_width) {
          tmp = text_width;
        }
        this->content_width = tmp;
      }
    }
  }
  if (((this->title_text != 0) && (this->title_font != 0)) &&
     (len = _strlen((char *)this->title_text), len != 0)) {
    value = font_text_width((GameFont *)this->title_font,this->title_text);
    text_width = value + 4;
    tmp = this->content_width;
    if ((int)this->content_width <= (int)text_width) {
      tmp = text_width;
    }
    this->content_width = tmp;
  }
  for (sprite = this->sprite_list; sprite != 0; sprite = *(uptr *)(sprite + 0x10)) {
  }
  if ((this->edit_count != 0) && (this->option_count != 0)) {
    this->edit_count = 0;
    this->edit_field_list = 0;
  }
  if ((this->style_flags & 0x10000) == 0) {
    value = font_cached_height((GameFont *)this->title_font);
    this->title_height = value + this->bevel_width * 2 + this->pad_y * 2;
  }
  else {
    this->border_width = 0;
    this->bevel_width = 0;
    this->title_height = 0;
  }
  this->chrome_height = this->title_height;
  this->window_x = this->req_x;
  this->window_y = this->req_y;
  left = this->border_width + this->pad_x;
  top = this->title_height + this->pad_y;
  if ((this->style_flags & 0x100000) == 0) {
    this->wnd_width = left * 2;
    this->wnd_height = this->pad_y * 2 + this->title_height;
    this->text_x = left;
    this->text_y = top;
    this->list_x = left;
    this->list_y = top;
    this->edit_x = left;
    this->edit_y = top;
    this->sprite_x = left;
    this->sprite_y = top;
    tmp = this->option_width;
    if ((int)this->option_width <= (int)this->content_width) {
      tmp = this->content_width;
    }
    if ((int)tmp <= (int)this->edit_width) {
      tmp = this->edit_width;
    }
    this->content_width = tmp;
    this->edit_width = this->content_width;
    this->option_width = this->edit_width;
  }
  this->std_button_count = 0;
  if ((this->style_flags & 0x40) != 0) {
    (&((Dialog *)this)->button_alignment)[this->std_button_count * 2] = 1;
    this->std_button_count++;
  }
  if (((this->style_flags & 8) == 0) && ((this->style_flags & 0x2000000) == 0)) {
    (&((Dialog *)this)->button_alignment)[this->std_button_count * 2] = 0;
    this->std_button_count++;
  }
  if ((this->style_flags & 1) != 0) {
    (&((Dialog *)this)->button_alignment)[this->std_button_count * 2] = 2;
    this->std_button_count++;
  }
  if (this->edit_count + this->option_count + this->sprite_count + this->std_button_count + this->line_count == 0) {
    if (this->surf_wnd != 0) {
      this->text_x += this->origin_x;
      this->text_y += this->origin_y;
    }
  }
  else if ((this->option_count != 0) || ((this->style_flags & 0x1004) == 0)) {
    sprites_height = 0;
    if (this->sprite_list != 0) {
      sprite_width2 = gfx_zoom_scale(this->max_sprite_width,this->sprite_zoom);
      if (*(int *)(this->sprite_list + 8) == 0) {
        this->text_x += sprite_width2;
        this->list_x += sprite_width2;
        this->edit_x += sprite_width2;
        this->wnd_width += sprite_width2;
      }
      else {
        tmp = this->content_width;
        if ((int)this->content_width <= (int)sprite_width2) {
          tmp = sprite_width2;
        }
        this->content_width = tmp;
      }
      for (sprite = this->sprite_list; sprite != 0; sprite = *(uptr *)(sprite + 0x10)) {
        tmp = this->sprite_zoom;
        height = sprite_height(*(Sprite **)(sprite + 0xc));
        value = gfx_zoom_scale(height,tmp);
        sprites_height += value;
        if (*(int *)(sprite + 0x10) != 0) {
          sprites_height += this->section_gap;
        }
      }
    }
    if ((this->line_list != 0) && (value = dialog_has_text_lines(this), value != 0)) {
      text_height = dialog_draw_wrapped_text(this,0);
      this->list_y = this->list_y + this->section_gap + text_height;
      this->edit_y = this->edit_y + this->section_gap + text_height;
    }
    if (this->option_list != 0) {
      column_count = this->columns;
      if ((int)column_count < 2) {
        column_count = 1;
      }
      rows = (int)((this->columns - 1) + this->option_count) / (int)column_count;
      lists_height = this->option_row_height * rows;
      if ((this->style_flags & 0x1000) != 0) {
        this->cur_pane = 0;
        lists_height = this->list_height;
        if ((this->style_flags & 0x40000) == 0) {
          tmp = GetSystemMetrics(2);
          this->list_vscroll_width = tmp;
          tmp = GetSystemMetrics(3);
          this->list_hscroll_height = tmp;
          rect_set_xywh((iptr)&this->pane_left,this->list_x_offset + this->list_x,this->list_y,
                             this->list_width,this->list_height);
          this->pane_inner_left = this->pane_left;
          this->list_client_top = this->pane_top;
          this->list_client_right = this->pane_right;
          this->list_client_bottom = this->pane_bottom;
          if (((int)(this->list_rows * this->columns) < (int)this->option_count) ||
             ((this->style_flags & 0x1000000) != 0)) {
            if (this->columns == 1) {
              rect_set_xywh((iptr)this->list_vscroll_rect,this->pane_right - this->list_vscroll_width,
                                 this->list_y,this->list_vscroll_width,this->list_height);
              this->list_client_right -= this->list_vscroll_width;
            }
            else {
              this->list_height += this->list_hscroll_height;
              this->pane_bottom += this->list_hscroll_height;
              this->list_client_bottom += this->list_hscroll_height;
              lists_height = this->list_height;
              rect_set_xywh((iptr)(this->list_hscroll_rect),this->list_x_offset + this->list_x,
                                 this->pane_bottom - this->list_hscroll_height,this->list_width,this->list_hscroll_height);
              this->list_client_bottom -= this->list_hscroll_height;
            }
          }
          rect_deflate((iptr)&this->pane_inner_left,1,1);
          this->list_origin_x = this->pane_inner_left;
          this->list_origin_y = this->list_client_top;
          value = rect_width((iptr)&this->pane_inner_left);
          this->list_column_width = value / (int)this->columns;
          tmp = dialog_list_row_height((DialogTextView *)this);
          this->list_row_height = tmp;
          first_option = dialog_option_at(this,0);
          top_index = dialog_option_group_index(this,first_option);
          value = dialog_option_group_index(this,this->selected_option);
          while ((int)(this->list_rows * this->columns + top_index) <= value) {
            if (this->columns == 1) {
              top_index++;
            }
            else {
              top_index += this->list_rows;
            }
          }
          tmp = dialog_option_at(this,top_index);
          this->list_top_option = tmp;
        }
        if ((this->style_flags & 0x400000) != 0) {
          this->cur_pane = 1;
          if ((int)lists_height < (int)this->list_height_1) {
            lists_height = this->list_height_1;
          }
          if ((this->style_flags & 0x40000) == 0) {
            tmp = GetSystemMetrics(2);
            this->list2_vscroll_width = tmp;
            tmp = GetSystemMetrics(3);
            this->list2_hscroll_height = tmp;
            rect_set_xywh((iptr)&this->pane1_left,this->list2_x_offset + this->list_x,
                               this->list_y,this->list_width_1,this->list_height_1);
            this->list2_client_rect = this->pane1_left;
            this->list2_client_top = this->pane1_top;
            this->list2_client_right = this->pane1_right;
            this->list2_client_bottom = this->pane1_bottom;
            if (((int)(this->list_rows_1 * this->columns) < (int)this->option_count) ||
               ((this->style_flags & 0x1000000) != 0)) {
              if (this->columns == 1) {
                rect_set_xywh((iptr)(this->list2_vscroll_rect),this->pane1_right - this->list2_vscroll_width,
                                   this->list_y,this->list2_vscroll_width,this->list_height_1);
                this->list2_client_right -= this->list2_vscroll_width;
              }
              else {
                this->list_height_1 += this->list2_hscroll_height;
                this->pane1_bottom += this->list2_hscroll_height;
                this->list2_client_bottom += this->list2_hscroll_height;
                if ((int)lists_height < (int)this->list_height_1) {
                  lists_height = this->list_height_1;
                }
                rect_set_xywh((iptr)(this->list2_hscroll_rect),this->list2_x_offset + this->list_x,
                                   this->pane1_bottom - this->list2_hscroll_height,this->list_width_1,this->list2_hscroll_height)
                ;
                this->list2_client_bottom -= this->list2_hscroll_height;
              }
            }
            rect_deflate((iptr)&this->list2_client_rect,1,1);
            this->list2_origin_x = this->list2_client_rect;
            this->list2_origin_y = this->list2_client_top;
            value = rect_width((iptr)&this->list2_client_rect);
            this->list2_column_width = value / (int)this->columns;
            tmp = dialog_list_row_height((DialogTextView *)this);
            this->list2_row_height = tmp;
            first_option = dialog_option_at(this,0);
            top_index = dialog_option_group_index(this,first_option);
            value = dialog_option_group_index(this,this->selected_option);
            while ((int)(this->list_rows_1 * this->columns + top_index) <= value) {
              if (this->columns == 1) {
                top_index++;
              }
              else {
                top_index += this->list_rows_1;
              }
            }
            tmp = dialog_option_at(this,top_index);
            this->list2_top_option = tmp;
          }
          this->cur_pane = 0;
        }
      }
    }
    if (this->edit_field_list != 0) {
      edit_height = dialog_edit_row_height((DialogCore *)this);
      edit_height = edit_height * this->edit_count;
    }
    content_height = edit_height + lists_height + text_height;
    if (((content_height != 0) && (text_height != 0)) && (edit_height + lists_height != 0)) {
      content_height += this->section_gap;
    }
    if ((this->style_flags & 0x100000) == 0) {
      if ((sprites_height != 0) && (content_height != 0)) {
        this->text_x += this->sprite_gap;
        this->list_x += this->sprite_gap;
        this->edit_x += this->sprite_gap;
      }
      value = sprites_height;
      if (sprites_height <= content_height) {
        value = content_height;
      }
      this->wnd_height += value;
      this->wnd_width += this->content_width;
    }
    if (this->std_button_count + this->extra_button_count == 0) {
      this->wnd_height += this->border_width;
      this->chrome_height += this->border_width;
    }
    else {
      button_x = this->wnd_width - (this->border_width - this->bevel_width);
      this->button_width = 0;
      for (i = 0; (int)i < 3; i++) {
        value = dialog_button_width_for
                          ((DialogButtonWidthForView *)this,(iptr)(&dialog_button_labels)[i]);
        if ((int)this->button_width <= value) {
          tmp = dialog_button_width_for
                            ((DialogButtonWidthForView *)this,(iptr)(&dialog_button_labels)[i]);
          this->button_width = tmp;
        }
      }
      for (i = 0; (int)i < (int)this->extra_button_count; i++) {
        value = dialog_button_width_for((DialogButtonWidthForView *)this,(&(*(u32 *)&((Dialog *)this)->extra_button_labels))[i]);
        if ((int)this->button_width <= value) {
          tmp = dialog_button_width_for((DialogButtonWidthForView *)this,(&(*(u32 *)&((Dialog *)this)->extra_button_labels))[i]);
          this->button_width = tmp;
        }
      }
      value = (this->wnd_width + (this->border_width - this->bevel_width) * -2) -
              (this->std_button_count + this->extra_button_count - 1) * this->pad_x;
      extra_space = value % (int)(this->std_button_count + this->extra_button_count);
      avail_width = value / (int)(this->std_button_count + this->extra_button_count);
      tmp = this->button_width;
      if ((int)this->button_width <= (int)avail_width) {
        tmp = avail_width;
      }
      this->button_width = tmp;
      if (this->button_width != avail_width) {
        extra_space = 0;
      }
      if ((this->style_flags & 0x100000) == 0) {
        if ((sprites_height != 0) || (content_height != 0)) {
          this->wnd_height += this->section_gap * 2;
        }
        value = dialog_line_height((DialogTextView *)this);
        this->wnd_height += value;
        if (this->border_width != 0) {
          if ((sprites_height != 0) || (content_height != 0)) {
            this->chrome_height += this->section_gap * 2;
          }
          value = dialog_line_height((DialogTextView *)this);
          this->chrome_height += value;
        }
      }
      remainder_acc = this->std_button_count + this->extra_button_count - 1;
      tmp = this->std_button_count;
      while (i = tmp - 1, -1 < (int)i) {
        pos = button_x - this->button_width;
        (&((Dialog *)this)->button_layout)[tmp * 2] = pos;
        button_x = pos - this->pad_x;
        for (remainder_acc = remainder_acc + extra_space; tmp = i,
            (int)(this->std_button_count + this->extra_button_count) <= remainder_acc;
            remainder_acc = remainder_acc - (this->std_button_count + this->extra_button_count)) {
          button_x--;
        }
      }
      tmp = this->extra_button_count;
      while (i = tmp - 1, -1 < (int)i) {
        pos = button_x - this->button_width;
        (&((Dialog *)this)->button_layout)[tmp * 2 + this->std_button_count * 2] = pos;
        button_x = pos - this->pad_x;
        for (remainder_acc = remainder_acc + extra_space; tmp = i,
            (int)(this->std_button_count + this->extra_button_count) <= remainder_acc;
            remainder_acc = remainder_acc - (this->std_button_count + this->extra_button_count)) {
          button_x--;
        }
      }
    }
    tmp = this->min_height;
    if ((int)this->min_height <= (int)this->wnd_height) {
      tmp = this->wnd_height;
    }
    this->wnd_height = tmp;
    tmp = this->wnd_height;
    value = dialog_line_height((DialogTextView *)this);
    this->button_y = tmp - (this->bevel_width + value + this->pad_y);
    if ((this->style_flags & 0x100000) == 0) {
      gfx_get_screen_rect((iptr)screen_rect2);
      wnd_get_screen_rect((WndBase *)&main_frame_wnd,(iptr)frame_rect2);
      if (this->window_x == 0xfffffc19) {
        value = rect_width((iptr)screen_rect2);
        this->window_x = (value >> 1) - ((int)this->wnd_width >> 1);
      }
      else if ((((int)this->window_x < 0) &&
               (this->window_x = this->window_x + ((screen_right - 1) - this->wnd_width),
               main_frame_created != 0)) && ((this->style_flags & 0x10000) != 0)) {
        value = wnd_frame_width((WndBase *)&main_frame_wnd);
        this->window_x -= value;
      }
      if (this->window_y == 0xfffffc19) {
        value = rect_height((iptr)screen_rect2);
        this->window_y = (value >> 1) - ((int)this->wnd_height >> 1);
      }
      else if ((int)this->window_y < 0) {
        if (-(screen_bottom - frame_bottom2) < (int)this->window_y) {
          this->window_y -= (screen_bottom - frame_bottom2);
        }
        this->window_y += ((screen_bottom - 1) - this->wnd_height);
        if ((main_frame_created != 0) && ((this->style_flags & 0x10000) != 0)) {
          value = wnd_nonclient_height((WndBase *)&main_frame_wnd);
          this->window_y -= value;
        }
      }
      if ((dialog_clamp_overflow == 0) &&
         (value = rect_width((iptr)screen_rect2), (int)this->wnd_width <= value)) {
        rect_height((iptr)screen_rect2);
      }
      this->list_x += this->origin_x;
      this->list_y += this->origin_y;
      this->text_x += this->origin_x;
      this->text_y += this->origin_y;
      this->edit_x += this->origin_x;
      this->edit_y += this->origin_y;
    }
    this->button_y += this->origin_y;
    for (i = 0; (int)i < (int)(this->std_button_count + this->extra_button_count);
        i = i + 1) {
      (&((Dialog *)this)->button_x_coords)[i * 2] = (&((Dialog *)this)->button_x_coords)[i * 2] + this->origin_x;
    }
    result = 0;
  }
  return result;
}
#undef dialog_clamp_overflow
#undef main_frame_created
#undef button_x
#undef text_height
#undef top_index
#undef frame_rect2
#undef frame_bottom2
#undef text_width
#undef screen_rect2
#undef screen_right
#undef screen_bottom
#undef result
#undef remainder_acc
#undef rows
#undef left
#undef extra_space
#undef top
#undef avail_width
#undef sprites_height
#undef edit_height
#undef sprite
#undef i
#undef sprite_width2
#undef line
#undef lists_height
#undef first_option
#undef content_height

/* 005a0fea auto */
#define shadow_color2 (*(u32 *)(frame_ + FRAME_OFF(4)))
#define fg_color (*(u32 *)(frame_ + FRAME_OFF(8)))
void __thiscall
dialog_draw_option_cell
          (DialogOptionDrawView *this,iptr text,int x,int y,int selected,int disabled)

{
  int col_width;
  int text_width;
  uptr text_len;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  while (*(char *)text != '\0') {
    col_width = *(int *)(((DialogOptionDrawViewExt *)this)->pane_column_widths + this->cur_pane * 4 - 4);
    text_width = font_text_width((GameFont *)this->list_font,text);
    if (text_width <= col_width - 6) break;
    text_len = _strlen((char *)text);
    *(i8 *)((text_len - 1) + text) = 0;
  }
  if (selected == 0) {
    fg_color = this->list_fg_color;
    shadow_color2 = this->list_fg_shadow_color;
  }
  else {
    fg_color = this->sel_text_color;
    shadow_color2 = this->sel_shadow_color;
  }
  if (shadow_color2 != fg_color) {
    gfx_set_text_color_index(shadow_color2);
    surface_draw_text
              ((DibSurface *)this->surface_value,this->list_font,text,x + 2,y + 1,5);
    gfx_set_text_color_index(fg_color);
    surface_draw_text
              ((DibSurface *)this->surface_value,this->list_font,text,x + 1,y,5);
  }
  if (disabled == 0) {
    gfx_set_text_color_index(fg_color);
  }
  else {
    gfx_set_text_color_index(this->highlight_color);
  }
  surface_draw_text
            ((DibSurface *)this->surface_value,this->list_font,text,x,y,5);
  return;
}
#undef shadow_color2
#undef fg_color

/* 005a1148 auto */
#define right_text (*(char * *)(frame_ + FRAME_OFF(0)))
void __thiscall
dialog_draw_option_text
          (DialogOptionDrawView *this,char *text,int x,i32 y,i32 selected,
          i32 disabled)

{
  int col_width;
  char *separator;
  int right_width;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  right_text = (char *)0x0;
  separator = _strchr(text,0x7c);
  if (separator != (char *)0x0) {
    right_text = separator + 1;
    *separator = '\0';
  }
  dialog_draw_option_cell(this,(iptr)text,*(int *)(((DialogOptionDrawViewExt *)this)->pane_column_offsets + this->cur_pane * 4 - 4) + x
                     ,y,selected,disabled);
  if (right_text != (char *)0x0) {
    col_width = *(int *)(((DialogOptionDrawViewExt *)this)->pane_column_widths + this->cur_pane * 4 - 4);
    right_width = font_text_width((GameFont *)this->list_font,(iptr)right_text);
    dialog_draw_option_cell(this,(iptr)right_text,(col_width + x - 4) - right_width,y,selected,disabled);
    *separator = '|';
  }
  return;
}
#undef right_text

/* 005a120b auto */
#define inner_left (*(int *)(frame_ + FRAME_OFF(4)))
#define inner_top (*(i32 *)(frame_ + FRAME_OFF(8)))
#define inner_right (*(i32 *)(frame_ + FRAME_OFF(12)))
#define inner_bottom (*(i32 *)(frame_ + FRAME_OFF(16)))
#define row (*(int *)(frame_ + FRAME_OFF(20)))
#define cell_y (*(int *)(frame_ + FRAME_OFF(24)))
#define col (*(int *)(frame_ + FRAME_OFF(28)))
#define cell_x (*(int *)(frame_ + FRAME_OFF(32)))
#define fill_color (*(u32 *)(frame_ + FRAME_OFF(36)))
#define is_selected (*(uint *)(frame_ + FRAME_OFF(40)))
#define cell_left (*(int *)(frame_ + FRAME_OFF(44)))
#define cell_top (*(i32 *)(frame_ + FRAME_OFF(48)))
#define cell_right (*(i32 *)(frame_ + FRAME_OFF(52)))
#define cell_bottom (*(i32 *)(frame_ + FRAME_OFF(56)))
uint __thiscall dialog_draw_option(DialogOptionList *this,iptr option,int blit)

{
  int rel_index;
  int group_index;
  int visible_count;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (option == 0) {
    is_selected = 0;
  }
  else if (this->option_count == 0) {
    is_selected = 0;
  }
  else {
    rel_index = dialog_option_group_index(this,*(uptr *)(this->list_column_counts + *(int *)(option + 0xc) * 4 + 0x18));
    group_index = dialog_option_group_index(this,option);
    rel_index = group_index - rel_index;
    if ((rel_index < 0) ||
       (visible_count = (&this->list_rows)[*(int *)(option + 0xc)] * this->columns,
       visible_count - rel_index == 0 || visible_count < rel_index)) {
      is_selected = 0;
    }
    else {
      col = rel_index / (int)(&this->list_rows)[*(int *)(option + 0xc)];
      row = rel_index % (int)(&this->list_rows)[*(int *)(option + 0xc)];
      cell_x = *(int *)(this->list_column_counts + *(int *)(option + 0xc) * 4 - 0x10) * col +
                 *(int *)(this->list_column_counts + *(int *)(option + 0xc) * 4 - 0x28);
      cell_y = *(int *)(this->list_column_counts + *(int *)(option + 0xc) * 4 - 8) * row +
                 *(int *)(this->list_column_counts + *(int *)(option + 0xc) * 4 - 0x20);
      rect_set_xywh((iptr)&cell_left,cell_x,cell_y,
                         *(iptr *)(this->list_column_counts + *(int *)(option + 0xc) * 4 - 0x10),
                         *(iptr *)(this->list_column_counts + *(int *)(option + 0xc) * 4 - 8));
      is_selected = (uint)(this->selected_option == option);
      if (is_selected == 0) {
        fill_color = this->list_fill_color;
      }
      else {
        fill_color = this->list_sel_fill_color;
      }
      inner_left = cell_left;
      inner_top = cell_top;
      inner_right = cell_right;
      inner_bottom = cell_bottom;
      if (this != (DialogOptionList *)0xfffffdf8) {
        inner_left = cell_left + *(int *)(this->list_column_counts + *(int *)(option + 0xc) * 4 + 0x10);
      }
      if ((this->on_draw_option == 0) ||
         (group_index = (*(code *)this->on_draw_option)
                            (this,this->surf_wnd,*(i32 *)(option + 4),group_index,cell_x,cell_y
                             ,*(i32 *)(this->list_column_counts + *(int *)(option + 0xc) * 4 - 8)),
         group_index == 0)) {
        if (is_selected != 0) {
          gfx_draw_bevel_rect(this->surf_wnd,(iptr)&inner_left,this->bevel_light_color,this->bevel_dark_color);
          rect_deflate((iptr)&inner_left,1,1);
        }
        gfx_fill_rect(this->surf_wnd,(iptr)&inner_left,fill_color);
        dialog_draw_option_text
                  ((DialogOptionDrawView *)this,*(i32 *)(option + 8),cell_x + 2,cell_y,is_selected,
                   *(uint *)option & 1);
      }
      if (blit != 0) {
        wnd_blit_surface_rect((DibSurface *)this->surf_wnd,(iptr)&cell_left);
      }
    }
  }
  return is_selected;
}
#undef inner_left
#undef inner_top
#undef inner_right
#undef inner_bottom
#undef row
#undef cell_y
#undef col
#undef cell_x
#undef fill_color
#undef is_selected
#undef cell_left
#undef cell_top
#undef cell_right
#undef cell_bottom

/* 005a14d2 auto */
#define group_pos (*(int *)(frame_ + FRAME_OFF(4)))
#define pane_idx (*(u32 *)(frame_ + FRAME_OFF(12)))
#define node2 (*(iptr *)(frame_ + FRAME_OFF(20)))
#define i (*(int *)(frame_ + FRAME_OFF(24)))
#define clip_left2 (*(i32 *)(frame_ + FRAME_OFF(28)))
#define clip_top2 (*(int *)(frame_ + FRAME_OFF(32)))
#define clip_right2 (*(i32 *)(frame_ + FRAME_OFF(36)))
#define clip_bottom2 (*(i32 *)(frame_ + FRAME_OFF(40)))
void __thiscall dialog_draw_option_list(DialogOptionList *this)

{
  u8 *pane_drawn;
  u32 saved_pane;
  u32 pane;
  int first_index;
  iptr option;
  uint drawn;
  i32 no_blit;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  saved_pane = this->cur_pane;
  for (pane_idx = 0; (int)pane_idx < 2; pane_idx++) {
    if ((pane_idx != 1) || ((this->style_flags & 0x400000) != 0)) {
      this->cur_pane = pane_idx;
      pane_drawn = this->list_vscroll_rect + this->cur_pane * 4 + 0x40;
      pane_drawn[0] = '\0';
      pane_drawn[1] = '\0';
      pane_drawn[2] = '\0';
      pane_drawn[3] = '\0';
      pane = this->cur_pane;
      clip_left2 = *(i32 *)(this->list_vscroll_rect + pane * 0x10 - 0x20);
      clip_top2 = *(int *)(this->list_vscroll_rect + pane * 0x10 - 0x1c);
      clip_right2 = *(i32 *)(this->list_vscroll_rect + pane * 0x10 - 0x18);
      clip_bottom2 = *(i32 *)(this->list_vscroll_rect + pane * 0x10 - 0x14);
      if ((1 < (int)this->columns) || ((this->option_count == 0 || (this->on_draw_option != 0)))) {
        gfx_fill_rect(this->surf_wnd,(iptr)(this->list_vscroll_rect + this->cur_pane * 0x10 - 0x20),
                           this->list_fill_color);
      }
      gfx_draw_rect_frame(this->surf_wnd,(iptr)(this->list_vscroll_rect + this->cur_pane * 0x10 - 0x40),
                         this->bevel_dark_color);
      surface_set_clip((DibSurface *)this->surf_wnd,(iptr)&clip_left2);
      if (this->option_count != 0) {
        node2 = *(iptr *)(active_dialog + 0x228);
        first_index = dialog_option_group_index(this,*(uptr *)(this->list_column_counts + this->cur_pane * 4 + 0x18));
        group_pos = 0;
        for (i = 0; (node2 != 0 && (i < (int)this->option_count));
            i = i + 1) {
          if (this->cur_pane == *(u32 *)(node2 + 0xc)) {
            if ((first_index <= group_pos) &&
               (group_pos < (int)((&this->list_rows)[this->cur_pane] * this->columns + first_index))) {
              no_blit = 0;
              option = dialog_option_at(this,group_pos);
              drawn = dialog_draw_option(this,option,no_blit);
              *(uint *)(this->list_vscroll_rect + this->cur_pane * 4 + 0x40) =
                   *(uint *)(this->list_vscroll_rect + this->cur_pane * 4 + 0x40) | drawn;
              clip_top2 += *(int *)(this->list_column_counts + this->cur_pane * 4 - 8);
            }
            group_pos++;
          }
          node2 = *(iptr *)(node2 + 0x10);
        }
        if (((this->columns == 1) && (this->on_draw_option == 0)) &&
           (first_index = rect_height((iptr)&clip_left2), 0 < first_index)) {
          gfx_fill_rect(this->surf_wnd,(iptr)&clip_left2,this->list_fill_color);
        }
      }
      surface_reset_clip((DibSurface *)this->surf_wnd);
      wnd_blit_surface_rect
                ((DibSurface *)this->surf_wnd,
                 (iptr)(this->list_vscroll_rect + this->cur_pane * 0x10 - 0x40));
    }
  }
  this->cur_pane = saved_pane;
  return;
}
#undef group_pos
#undef pane_idx
#undef node2
#undef i
#undef clip_left2
#undef clip_top2
#undef clip_right2
#undef clip_bottom2

/* 005a1766 auto */
int __thiscall dialog_column_of_index(DialogTextView *this,int index)

{
  if (this->columns != 1) {
    index = index / (int)(&this->list_rows)[this->cur_pane];
  }
  return index;
}

/* 005a17a4 auto */
int __thiscall dialog_column_start_index(DialogTextView *this,int index)

{
  if (this->columns != 1) {
    index -= index % (int)(&this->list_rows)[this->cur_pane];
  }
  return index;
}

/* 005a17e9 auto */
#define top_index (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall dialog_select_option(DialogOptionList *this,uptr option,int redraw)

{
  uptr prev_option;
  bool scrolled;
  int option_index;
  i32 top_option;
  iptr scroll_pos;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  scrolled = false;
  if ((option != 0) && (this->selected_option != option)) {
    top_index = dialog_option_group_index(this,*(uptr *)(this->list_column_counts + this->cur_pane * 4 + 0x18));
    option_index = dialog_option_group_index(this,option);
    if (option_index < top_index) {
      scrolled = true;
      top_index = option_index;
    }
    while ((int)((&this->list_rows)[this->cur_pane] * this->columns + top_index) <= option_index) {
      if (this->columns == 1) {
        top_index++;
      }
      else {
        top_index += (&this->list_rows)[this->cur_pane];
      }
      scrolled = true;
    }
    top_option = dialog_column_start_index((DialogTextView *)this,this->option_count - 1);
    top_option = int_clamp_b(top_index,0,top_option);
    top_option = dialog_option_at(this,top_option);
    *(i32 *)(this->list_column_counts + this->cur_pane * 4 + 0x18) = top_option;
    prev_option = this->selected_option;
    this->selected_option = option;
    if ((scrolled) || (redraw == 0)) {
      if ((&((DialogTextLineView *)this)->list_vscroll_controls)[this->cur_pane] != 0) {
        scroll_pos = dialog_option_group_index(this,*(uptr *)(this->list_column_counts + this->cur_pane * 4 + 0x18));
        scrollbar_set_pos
                  ((ClickControl *)(&((DialogTextLineView *)this)->list_vscroll_controls)[this->cur_pane],scroll_pos);
      }
      if ((&((DialogTextLineView *)this)->list_hscroll_controls)[this->cur_pane] != 0) {
        scroll_pos = dialog_column_of_option(this,*(i32 *)(this->list_column_counts + this->cur_pane * 4 + 0x18));
        scrollbar_set_pos
                  ((ClickControl *)(&((DialogTextLineView *)this)->list_hscroll_controls)[this->cur_pane],scroll_pos);
      }
    }
    if (redraw != 0) {
      if (scrolled) {
        dialog_draw_option_list(this);
        if (this->on_select_change != 0) {
          (*(code *)this->on_select_change)(this,*(i32 *)(option + 4));
        }
      }
      else {
        dialog_draw_option(this,prev_option,1);
        dialog_draw_option(this,option,1);
        if (this->on_select_change != 0) {
          (*(code *)this->on_select_change)(this,*(i32 *)(option + 4));
        }
      }
    }
  }
  return;
}
#undef top_index

/* 005a1a7d auto */
i32 __thiscall dialog_option_at_point(DialogOptionList *this,int x,int y)

{
  i32 result;
  int top_index;
  
  dialog_pick_pane_at((DialogWindowView *)this,x,y);
  if ((&((DialogTextLineView *)this)->list_hscroll_controls)[this->cur_pane] != 0) {
    if (x < *(int *)(this->list_vscroll_rect + this->cur_pane * 0x10 - 0x20)) {
      return 0xfffffffd;
    }
    if (*(int *)(this->list_vscroll_rect + this->cur_pane * 0x10 - 0x18) <= x) {
      return 0xfffffffc;
    }
  }
  if (y < *(int *)(this->list_vscroll_rect + this->cur_pane * 0x10 - 0x1c)) {
    result = 0xffffffff;
  }
  else if (y < *(int *)(this->list_vscroll_rect + this->cur_pane * 0x10 - 0x14)) {
    if (x < *(int *)(this->list_vscroll_rect + this->cur_pane * 0x10 - 0x20)) {
      result = 0xfffffffd;
    }
    else if (x < *(int *)(this->list_vscroll_rect + this->cur_pane * 0x10 - 0x18)) {
      top_index = dialog_option_group_index(this,*(uptr *)(this->list_column_counts + this->cur_pane * 4 + 0x18));
      result = int_clamp_b((&this->list_rows)[this->cur_pane] *
                           ((x - *(int *)(this->list_vscroll_rect + this->cur_pane * 0x10 - 0x20)) /
                           *(int *)(this->list_column_counts + this->cur_pane * 4 - 0x10)) +
                           (y - *(int *)(this->list_vscroll_rect + this->cur_pane * 0x10 - 0x1c)) /
                           *(int *)(this->list_column_counts + this->cur_pane * 4 - 8) + top_index,0,
                           this->option_count - 1);
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
#define node2 (*(uptr *)(frame_ + FRAME_OFF(4)))
#define count (*(int *)(frame_ + FRAME_OFF(8)))
int __thiscall dialog_count_group_options(DialogOptionList *this,int group)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  count = 0;
  for (node2 = this->option_list; node2 != 0; node2 = *(uptr *)(node2 + 0x10)) {
    if (*(int *)(node2 + 0xc) == group) {
      count++;
    }
  }
  return count;
}
#undef node2
#undef count

/* 005a1caf auto */
void __thiscall dialog_pick_pane_at(DialogWindowView *this,int x,int y)

{
  u32 prev_pane;
  
  prev_pane = this->cur_pane;
  if ((this->style_flags & 0x400000) == 0) {
    this->cur_pane = 0;
  }
  else {
    this->cur_pane = 0;
    if (((((y < (int)this->pane_top) || ((int)this->pane_bottom < y)) ||
         (x < (int)this->pane_left)) || ((int)this->pane_right < x)) &&
       (((this->cur_pane = 1, y < (int)this->pane1_top || ((int)this->pane1_bottom < y)) ||
        ((x < (int)this->pane1_left || ((int)this->pane1_right < x)))))) {
      this->cur_pane = prev_pane;
    }
  }
  return;
}

/* 005a1da3 auto */
void __cdecl dialog_list_on_vscroll(i32 scroll_pos)

{
  int top_option;
  
  if (active_dialog != 0) {
    *(i32 *)(active_dialog + 0x48) = 0;
    top_option = dialog_option_at((DialogOptionList *)active_dialog,scroll_pos);
    if (*(int *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) != top_option) {
      *(int *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) = top_option;
      dialog_draw_option_list((DialogOptionList *)active_dialog);
    }
  }
  return;
}

/* 005a1e28 auto */
#define dlg_default_idle_callback (*(int *)((u8 *)&g.d_00635a40))
#define dlg_palette (*(i8 * *)((u8 *)&g.d_006359c0))
#define dlg_parent_window (*(i8 * *)((u8 *)&g.d_006359c4))
#define dlg_pending_idle_callback (*(int *)((u8 *)&g.d_00635a3c))
#define main_frame_created (*(int *)((u8 *)&g.d_00634718))
#define surf_wnd2 (*(uptr *)(frame_ + FRAME_OFF(4)))
#define wnd_style (*(i32 *)(frame_ + FRAME_OFF(12)))
#define palette (*(i8 * *)(frame_ + FRAME_OFF(16)))
#define parent2 (*(i8 * *)(frame_ + FRAME_OFF(20)))
#define title (*(i8 * *)(frame_ + FRAME_OFF(24)))
#define empty_title (*(i8 (*)[4])(frame_ + FRAME_OFF(28)))
#define saved_seh (*(i32 *)(frame_ + FRAME_OFF(32)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(36)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(40)))
i32 __thiscall dialog_create_window(DialogWindowView *this)

{
  i32 result;
  SurfaceWindow *this_00;
  int surf_width;
  u32 new_size;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  if (this->surf_wnd == 0) {
    this_00 = operator_new(0x114);
    eh_state = 0;
    if (this_00 == (SurfaceWindow *)0x0) {
      surf_wnd2 = 0;
    }
    else {
      surf_wnd2 = surfwnd_ctor(this_00);
    }
    eh_state = 0xffffffff;
    this->surf_wnd = surf_wnd2;
    empty_title[0] = 0;
    title = (i8 *)this->title_text;
    if (title == (i8 *)0x0) {
      title = empty_title;
    }
    if ((this->style_flags & 0x10000) == 0) {
      wnd_style = 0xc02;
    }
    else {
      wnd_style = 0x842;
    }
    if (dlg_parent_window == (i8 *)0x0) {
      if (main_frame_created == 0) {
        parent2 = (i8 *)0x0;
      }
      else {
        parent2 = &main_frame_wnd;
      }
    }
    else {
      parent2 = dlg_parent_window;
    }
    if (dlg_palette == (i8 *)0x0) {
      palette = &game_palette;
    }
    else {
      palette = dlg_palette;
    }
    if (parent2 == (i8 *)0x0) {
      surface_wnd_create
                ((DibSurface *)this->surf_wnd,(iptr)title,wnd_style,this->window_x,
                 this->window_y,this->wnd_width,this->wnd_height,(iptr)((u8 *)&g.d_006a8c00));
    }
    else {
      wnd_create_with_surface
                ((DibSurface *)this->surf_wnd,(iptr)title,wnd_style,this->window_x,
                 this->window_y,this->wnd_width,this->wnd_height,(iptr)palette,(iptr)parent2);
    }
    if ((this->style_flags & 0x10000) == 0) {
      wnd_set_caption_height((WndBase *)(this->surf_wnd + 0x48),this->title_height);
    }
    surf_width = surface_get_width((DibSurface *)this->surf_wnd);
    if ((int)this->wnd_width <= surf_width) {
      new_size = surface_get_width((DibSurface *)this->surf_wnd);
      this->wnd_width = new_size;
    }
    surf_width = surface_get_height((DibSurface *)this->surf_wnd);
    if ((int)this->wnd_height <= surf_width) {
      new_size = surface_get_height((DibSurface *)this->surf_wnd);
      this->wnd_height = new_size;
    }
    wnd_set_redraw_callback((SurfaceWindow *)this->surf_wnd,(iptr)dialog_on_redraw);
    if (dlg_pending_idle_callback == 0) {
      if (dlg_default_idle_callback != 0) {
        wnd_set_modal_idle_callback((ModalMenuWindow *)(this->surf_wnd + 0x48),dlg_default_idle_callback);
      }
    }
    else {
      wnd_set_modal_idle_callback((ModalMenuWindow *)(this->surf_wnd + 0x48),dlg_pending_idle_callback);
      dlg_pending_idle_callback = 0;
    }
    if (dlg_pending_move_handler != 0) {
      wnd_set_move_handler((WndEventHandlers *)(this->surf_wnd + 0x58),dlg_pending_move_handler);
      dlg_pending_move_handler = 0;
    }
    result = 1;
  }
  else {
    result = 0;
  }
  return result;
}
#undef dlg_default_idle_callback
#undef dlg_palette
#undef dlg_parent_window
#undef dlg_pending_idle_callback
#undef main_frame_created
#undef surf_wnd2
#undef wnd_style
#undef palette
#undef parent2
#undef title
#undef empty_title
#undef saved_seh
#undef seh_handler
#undef eh_state

/* 005a20f4 auto */
void __cdecl dialog_on_redraw(void)

{
  if (active_dialog != 0) {
    dialog_render((Dialog *)active_dialog);
  }
  return;
}

/* 005a211c auto */
#define dialog_clamp_overflow (*(int *)((u8 *)&g.d_0062f004))
#define dialog_stack (*(i32 *)((u8 *)&g.d_00635a58))
#define dialog_stack_top (*(Dialog * *)((u8 *)&g.d_006ad678))
#define parent_198 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define parent_194 (*(int *)(frame_ + FRAME_OFF(4)))
#define parent_190 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define parent_18c (*(iptr *)(frame_ + FRAME_OFF(12)))
#define parent_188 (*(iptr *)(frame_ + FRAME_OFF(16)))
#define parent_184 (*(iptr *)(frame_ + FRAME_OFF(20)))
#define parent_180 (*(iptr *)(frame_ + FRAME_OFF(24)))
#define parent_17c (*(iptr *)(frame_ + FRAME_OFF(28)))
#define parent_178 (*(iptr *)(frame_ + FRAME_OFF(32)))
#define parent_174 (*(iptr *)(frame_ + FRAME_OFF(36)))
#define parent_170 (*(iptr *)(frame_ + FRAME_OFF(40)))
#define buttons (*(int * *)(frame_ + FRAME_OFF(44)))
#define edits (*(u32 * *)(frame_ + FRAME_OFF(52)))
#define hotspots (*(u32 * *)(frame_ + FRAME_OFF(60)))
#define radio_group2 (*(uptr *)(frame_ + FRAME_OFF(68)))
#define checkboxes2 (*(u32 * *)(frame_ + FRAME_OFF(76)))
#define hscroll2 (*(i32 *)(frame_ + FRAME_OFF(84)))
#define vscroll2 (*(i32 *)(frame_ + FRAME_OFF(92)))
#define listbox22 (*(i32 *)(frame_ + FRAME_OFF(100)))
#define hscroll (*(i32 *)(frame_ + FRAME_OFF(108)))
#define vscroll (*(i32 *)(frame_ + FRAME_OFF(116)))
#define listbox3 (*(i32 *)(frame_ + FRAME_OFF(124)))
#define item_index (*(int *)(frame_ + FRAME_OFF(148)))
#define edit_field (*(uptr *)(frame_ + FRAME_OFF(156)))
#define y2 (*(u32 *)(frame_ + FRAME_OFF(160)))
#define label (*(i8 * *)(frame_ + FRAME_OFF(176)))
#define rect (*(i8 (*)[16])(frame_ + FRAME_OFF(180)))
#define label_count2 (*(iptr *)(frame_ + FRAME_OFF(196)))
#define button_id (*(iptr *)(frame_ + FRAME_OFF(200)))
#define is_listbox (*(uint *)(frame_ + FRAME_OFF(204)))
#define option (*(uint * *)(frame_ + FRAME_OFF(208)))
#define sprite (*(uptr *)(frame_ + FRAME_OFF(212)))
#define i (*(int *)(frame_ + FRAME_OFF(216)))
#define unused_flag (*(i8 *)(frame_ + FRAME_OFF(220)))
#define width2 (*(iptr *)(frame_ + FRAME_OFF(224)))
#define labels (*(uint (*)[41])(frame_ + FRAME_OFF(228)))
#define saved_seh (*(i32 *)(frame_ + FRAME_OFF(392)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(396)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(400)))
void __thiscall dialog_create_controls(Dialog *this)

{
  uint is_checkbox;
  Control *pCVar2;
  InputControl *this_00;
  i32 value;
  int count;
  iptr pos;
  u32 x;
  i32 text;
  u32 zoom;
  i8 frame_[FRAME_OFF(408)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  label_count2 = 0;
  if (this != (Dialog *)active_dialog) {
    if ((dialog_stack_depth < 0) || (0xf < dialog_stack_depth)) {
      err_report((ErrorContext *)&err_report_ctx,7,(iptr)((u8 *)&g.d_00635b40),(iptr)((u8 *)&g.d_00635b20),0xc75);
    }
    dialog_stack_depth++;
    dialog_stack_top = this;
    active_dialog = (iptr)this;
    (&dialog_stack)[dialog_stack_depth] = this;
  }
  if ((this->style_flags & 0x200) == 0) {
    unused_flag = 0;
    ctrl_set_pending_font(*(iptr *)(active_dialog + 8));
    ui_set_button_font((iptr)((u8 *)&g.d_006cec90));
    ui_set_ctrl_font(*(iptr *)(active_dialog + 8));
    ui_set_default_font((iptr)((u8 *)&g.d_006cec90));
    is_checkbox = this->style_flags & 4;
    is_listbox = this->style_flags & 0x1000;
    if ((is_checkbox == 0) && (is_listbox == 0)) {
      if (0x28 < (int)this->option_count) {
        if (dialog_clamp_overflow == 0) {
          error_report(0xfffffff2,9,0,0x28,this->option_count);
        }
        else {
          this->option_count = 0x28;
        }
      }
      for (option = (uint *)this->option_list; option != (uint *)0x0;
          option = (uint *)option[4]) {
        labels[label_count2] = option[2];
        label_count2++;
      }
    }
    if (this->option_count != 0) {
      if (is_listbox == 0) {
        if (is_checkbox == 0) {
          this_00 = operator_new(0x50);
          eh_state = 7;
          if (this_00 == (InputControl *)0x0) {
            radio_group2 = 0;
          }
          else {
            radio_group2 = radiogrp_ctor(this_00);
          }
          eh_state = 0xffffffff;
          this->radio_group = radio_group2;
          x = this->columns;
          if ((int)x < 2) {
            x = 1;
          }
          rect_set_xywh((iptr)rect,this->list_x,this->list_y,this->option_width,
                             this->option_row_height *
                             ((int)((this->columns - 1) + this->option_count) / (int)x));
          if (this->surf_wnd == 0) {
            parent_18c = 0;
          }
          else {
            parent_18c = this->surf_wnd + 0x48;
          }
          radiogrp_create
                    ((RadioGroup *)this->radio_group,parent_18c,200,(iptr)rect,this->columns,
                     this->option_count,(iptr)labels);
          option = (uint *)this->option_list;
          item_index = 0;
          for (; option != (uint *)0x0; option = (uint *)option[4]) {
            if ((uint *)this->selected_option == option) {
              radiogrp_set_selected((RadioGroupSetSelView *)this->radio_group,item_index);
            }
            if ((*option & 1) != 0) {
              radiogrp_disable_item((RadioGroupDisableView *)this->radio_group,item_index);
            }
            item_index++;
          }
          radiogrp_set_select_callback((Control *)this->radio_group,(iptr)dialog_radio_on_select);
          radiogrp_set_dblclick_callback((Control *)this->radio_group,(iptr)dialog_radio_on_dblclick);
        }
        else {
          x = this->option_count;
          checkboxes2 = operator_new(x * 0x3c + 4);
          eh_state = 6;
          if (checkboxes2 == (u32 *)0x0) {
            checkboxes2 = (u32 *)0x0;
          }
          else {
            *checkboxes2 = x;
            crt_vector_ctor_iterator(checkboxes2 + 1,0x3c,*checkboxes2,checkbox_elem_ctor,
                         checkbox_dtor);
            checkboxes2++;
          }
          eh_state = 0xffffffff;
          this->checkboxes = (uptr)checkboxes2;
          x = this->list_x;
          y2 = this->list_y;
          i = 0;
          for (option = (uint *)this->option_list; option != (uint *)0x0;
              option = (uint *)option[4]) {
            if (this->surf_wnd == 0) {
              parent_188 = 0;
            }
            else {
              parent_188 = this->surf_wnd + 0x48;
            }
            checkbox_create
                      ((Control *)(this->checkboxes + i * 0x3c),parent_188,i + 200
                       ,x,y2,option[2]);
            checkbox_set_checked
                      ((Control *)(this->checkboxes + i * 0x3c),*option & 4);
            if ((*option & 1) != 0) {
              checkbox_disable((CheckboxDisableView *)(this->checkboxes + i * 0x3c));
            }
            y2 += this->option_row_height;
            i++;
          }
        }
      }
      else {
        this->cur_pane = 0;
        if ((this->style_flags & 0x40000) == 0) {
          if (((int)((&this->list_rows)[this->cur_pane] * this->columns) < (int)this->option_count) ||
             ((this->style_flags & 0x1000000) != 0)) {
            if (this->columns == 1) {
              pCVar2 = operator_new(0x40);
              eh_state = 1;
              if (pCVar2 == (Control *)0x0) {
                vscroll = 0;
              }
              else {
                vscroll = scrollbar_ctor(pCVar2);
              }
              eh_state = 0xffffffff;
              *(i32 *)((u8 *)&this->extra_button_labels + this->cur_pane * 4 - 0x10) = vscroll;
              if (this->surf_wnd == 0) {
                parent_174 = 0;
              }
              else {
                parent_174 = this->surf_wnd + 0x48;
              }
              scrollbar_create
                        (*(Control **)((u8 *)&this->extra_button_labels + this->cur_pane * 4 - 0x10),parent_174,
                         0xb,(iptr)(this->list_vscroll_rect + this->cur_pane * 0x10),1);
              count = dialog_count_group_options((DialogOptionList *)this,this->cur_pane);
              scrollbar_set_range
                        (*(Control **)((u8 *)&this->extra_button_labels + this->cur_pane * 4 - 0x10),0,
                         count - 1);
              pos = dialog_option_group_index
                                ((DialogOptionList *)this,
                                 *(uptr *)(this->list_column_counts + this->cur_pane * 4 + 0x18));
              scrollbar_set_pos
                        (*(ClickControl **)((u8 *)&this->extra_button_labels + this->cur_pane * 4 - 0x10),pos);
              scrollbar_set_page_size
                        (*(Control **)((u8 *)&this->extra_button_labels + this->cur_pane * 4 - 0x10),
                         (&this->list_rows)[this->cur_pane] - 1);
              scrollbar_set_callback
                        (*(Control **)((u8 *)&this->extra_button_labels + this->cur_pane * 4 - 0x10),(iptr)dialog_list_on_vscroll);
              scrollbar_set_track_callback
                        (*(ScrollbarTrackSetView **)((u8 *)&this->extra_button_labels + this->cur_pane * 4 - 0x10),(iptr)dialog_list_on_vscroll);
            }
            else {
              pCVar2 = operator_new(0x40);
              eh_state = 2;
              if (pCVar2 == (Control *)0x0) {
                hscroll = 0;
              }
              else {
                hscroll = scrollbar_ctor(pCVar2);
              }
              eh_state = 0xffffffff;
              *(i32 *)((u8 *)&this->extra_button_labels + this->cur_pane * 4 - 8) = hscroll;
              if (this->surf_wnd == 0) {
                parent_178 = 0;
              }
              else {
                parent_178 = this->surf_wnd + 0x48;
              }
              scrollbar_create
                        (*(Control **)((u8 *)&this->extra_button_labels + this->cur_pane * 4 - 8),parent_178,0xc,
                         (iptr)(this->list_vscroll_rect + this->cur_pane * 0x10 + 0x20),0);
              count = dialog_count_group_options((DialogOptionList *)this,this->cur_pane);
              value = dialog_column_of_index((DialogTextView *)this,count - 1);
              scrollbar_set_range
                        (*(Control **)((u8 *)&this->extra_button_labels + this->cur_pane * 4 - 8),0,value);
              value = dialog_option_group_index
                                ((DialogOptionList *)this,
                                 *(uptr *)(this->list_column_counts + this->cur_pane * 4 + 0x18));
              pos = dialog_column_of_index((DialogTextView *)this,value);
              scrollbar_set_pos
                        (*(ClickControl **)((u8 *)&this->extra_button_labels + this->cur_pane * 4 - 8),pos);
              scrollbar_set_page_size
                        (*(Control **)((u8 *)&this->extra_button_labels + this->cur_pane * 4 - 8),this->columns
                        );
              scrollbar_set_callback
                        (*(Control **)((u8 *)&this->extra_button_labels + this->cur_pane * 4 - 8),(iptr)dialog_list_on_hscroll);
              scrollbar_set_track_callback
                        (*(ScrollbarTrackSetView **)((u8 *)&this->extra_button_labels + this->cur_pane * 4 - 8),(iptr)dialog_list_on_hscroll);
            }
          }
          wnd_set_lbuttondown_handler((WndHandlersMouseSetView *)(this->surf_wnd + 0x58),(iptr)dialog_list_on_lbuttondown);
          wnd_set_lbuttonup_any_handler((WndHandlersMouseSetView *)(this->surf_wnd + 0x58),(iptr)dialog_list_on_lbuttonup);
          wnd_set_mousemove_handler((WndHandlersMouseSetView *)(this->surf_wnd + 0x58),(iptr)dialog_list_on_mousemove);
          wnd_set_dblclick_handler((WndHandlersMouseSetView *)(this->surf_wnd + 0x58),(iptr)dialog_list_on_dblclick);
        }
        else {
          pCVar2 = operator_new(0x3c);
          eh_state = 0;
          if (pCVar2 == (Control *)0x0) {
            listbox3 = 0;
          }
          else {
            listbox3 = checkbox_ctor(pCVar2);
          }
          eh_state = 0xffffffff;
          *(i32 *)(this->control_ptr_slots + this->cur_pane * 4 + 0x14) = listbox3;
          rect_set_xywh((iptr)rect,this->list_x,this->list_y,
                             (&this->list_width)[this->cur_pane],(&this->list_height)[this->cur_pane]);
          if (this->surf_wnd == 0) {
            parent_170 = 0;
          }
          else {
            parent_170 = this->surf_wnd + 0x48;
          }
          listbox_create
                    (*(Control **)(this->control_ptr_slots + this->cur_pane * 4 + 0x14),parent_170,10,
                     (iptr)rect);
          option = (uint *)this->option_list;
          item_index = 0;
          for (; option != (uint *)0x0; option = (uint *)option[4]) {
            if (this->cur_pane == option[3]) {
              listbox_add_string
                        (*(ListBoxAddView **)(this->control_ptr_slots + this->cur_pane * 4 + 0x14),option[2]);
              if ((uint *)this->selected_option == option) {
                listbox_set_cur_sel
                          (*(ListBoxSetSelView **)(this->control_ptr_slots + this->cur_pane * 4 + 0x14),item_index);
              }
              item_index++;
            }
          }
          listbox_set_dblclick_callback
                    (*(ListBoxDblClickSetView **)(this->control_ptr_slots + this->cur_pane * 4 + 0x14),(iptr)dialog_listbox_on_dblclick);
        }
        if ((this->style_flags & 0x400000) != 0) {
          this->cur_pane = 1;
          if ((this->style_flags & 0x40000) == 0) {
            if (((int)((&this->list_rows)[this->cur_pane] * this->columns) < (int)this->option_count) ||
               ((this->style_flags & 0x1000000) != 0)) {
              if (this->columns == 1) {
                pCVar2 = operator_new(0x40);
                eh_state = 4;
                if (pCVar2 == (Control *)0x0) {
                  vscroll2 = 0;
                }
                else {
                  vscroll2 = scrollbar_ctor(pCVar2);
                }
                eh_state = 0xffffffff;
                *(i32 *)((u8 *)&this->extra_button_labels + this->cur_pane * 4 - 0x10) = vscroll2;
                if (this->surf_wnd == 0) {
                  parent_180 = 0;
                }
                else {
                  parent_180 = this->surf_wnd + 0x48;
                }
                scrollbar_create
                          (*(Control **)((u8 *)&this->extra_button_labels + this->cur_pane * 4 - 0x10),parent_180
                           ,0xb,(iptr)(this->list_vscroll_rect + this->cur_pane * 0x10),1);
                count = dialog_count_group_options((DialogOptionList *)this,this->cur_pane);
                scrollbar_set_range
                          (*(Control **)((u8 *)&this->extra_button_labels + this->cur_pane * 4 - 0x10),0,
                           count - 1);
                pos = dialog_option_group_index
                                  ((DialogOptionList *)this,
                                   *(uptr *)(this->list_column_counts + this->cur_pane * 4 + 0x18));
                scrollbar_set_pos
                          (*(ClickControl **)((u8 *)&this->extra_button_labels + this->cur_pane * 4 - 0x10),pos);
                scrollbar_set_page_size
                          (*(Control **)((u8 *)&this->extra_button_labels + this->cur_pane * 4 - 0x10),
                           (&this->list_rows)[this->cur_pane] - 1);
                scrollbar_set_callback
                          (*(Control **)((u8 *)&this->extra_button_labels + this->cur_pane * 4 - 0x10),(iptr)dialog_list2_on_vscroll)
                ;
                scrollbar_set_track_callback
                          (*(ScrollbarTrackSetView **)((u8 *)&this->extra_button_labels + this->cur_pane * 4 - 0x10),(iptr)dialog_list2_on_vscroll);
              }
              else {
                pCVar2 = operator_new(0x40);
                eh_state = 5;
                if (pCVar2 == (Control *)0x0) {
                  hscroll2 = 0;
                }
                else {
                  hscroll2 = scrollbar_ctor(pCVar2);
                }
                eh_state = 0xffffffff;
                *(i32 *)((u8 *)&this->extra_button_labels + this->cur_pane * 4 - 8) = hscroll2;
                if (this->surf_wnd == 0) {
                  parent_184 = 0;
                }
                else {
                  parent_184 = this->surf_wnd + 0x48;
                }
                scrollbar_create
                          (*(Control **)((u8 *)&this->extra_button_labels + this->cur_pane * 4 - 8),parent_184,
                           0xc,(iptr)(this->list_vscroll_rect + this->cur_pane * 0x10 + 0x20),0);
                count = dialog_count_group_options((DialogOptionList *)this,this->cur_pane);
                value = dialog_column_of_index((DialogTextView *)this,count - 1);
                scrollbar_set_range
                          (*(Control **)((u8 *)&this->extra_button_labels + this->cur_pane * 4 - 8),0,value);
                value = dialog_option_group_index
                                  ((DialogOptionList *)this,
                                   *(uptr *)(this->list_column_counts + this->cur_pane * 4 + 0x18));
                pos = dialog_column_of_index((DialogTextView *)this,value);
                scrollbar_set_pos
                          (*(ClickControl **)((u8 *)&this->extra_button_labels + this->cur_pane * 4 - 8),pos);
                scrollbar_set_page_size
                          (*(Control **)((u8 *)&this->extra_button_labels + this->cur_pane * 4 - 8),
                           this->columns);
                scrollbar_set_callback
                          (*(Control **)((u8 *)&this->extra_button_labels + this->cur_pane * 4 - 8),(iptr)dialog_list2_on_hscroll);
                scrollbar_set_track_callback
                          (*(ScrollbarTrackSetView **)((u8 *)&this->extra_button_labels + this->cur_pane * 4 - 8),(iptr)dialog_list2_on_hscroll);
              }
            }
          }
          else {
            pCVar2 = operator_new(0x3c);
            eh_state = 3;
            if (pCVar2 == (Control *)0x0) {
              listbox22 = 0;
            }
            else {
              listbox22 = checkbox_ctor(pCVar2);
            }
            eh_state = 0xffffffff;
            *(i32 *)(this->control_ptr_slots + this->cur_pane * 4 + 0x14) = listbox22;
            rect_set_xywh((iptr)rect,this->list_x,this->list_y,
                               (&this->list_width)[this->cur_pane],(&this->list_height)[this->cur_pane]);
            if (this->surf_wnd == 0) {
              parent_17c = 0;
            }
            else {
              parent_17c = this->surf_wnd + 0x48;
            }
            listbox_create
                      (*(Control **)(this->control_ptr_slots + this->cur_pane * 4 + 0x14),parent_17c,10,
                       (iptr)rect);
            option = (uint *)this->option_list;
            item_index = 0;
            for (; option != (uint *)0x0; option = (uint *)option[4]) {
              if (this->cur_pane == option[3]) {
                listbox_add_string
                          (*(ListBoxAddView **)(this->control_ptr_slots + this->cur_pane * 4 + 0x14),option[2]);
                if ((uint *)this->selected_option == option) {
                  listbox_set_cur_sel
                            (*(ListBoxSetSelView **)(this->control_ptr_slots + this->cur_pane * 4 + 0x14),item_index);
                }
                item_index++;
              }
            }
            listbox_set_dblclick_callback
                      (*(ListBoxDblClickSetView **)(this->control_ptr_slots + this->cur_pane * 4 + 0x14),(iptr)dialog_listbox_on_dblclick);
          }
          this->cur_pane = 0;
        }
      }
    }
    if ((1 < (int)this->sprite_count) && (this->option_count == 0)) {
      x = this->sprite_count;
      hotspots = operator_new(x * 0x40 + 4);
      eh_state = 8;
      if (hotspots == (u32 *)0x0) {
        hotspots = (u32 *)0x0;
      }
      else {
        *hotspots = x;
        crt_vector_ctor_iterator(hotspots + 1,0x40,*hotspots,hotspot_ctor,
                     hotspot_dtor);
        hotspots++;
      }
      eh_state = 0xffffffff;
      this->sprite_hotspots = (uptr)hotspots;
      x = this->sprite_x;
      y2 = this->sprite_y;
      sprite = this->sprite_list;
      i = 0;
      for (; sprite != 0; sprite = *(uptr *)(sprite + 0x10)) {
        width2 = gfx_zoom_scale(this->max_sprite_width,this->sprite_zoom);
        zoom = this->sprite_zoom;
        value = sprite_height(*(Sprite **)(sprite + 0xc));
        count = gfx_zoom_scale(value,zoom);
        rect_set_xywh((iptr)rect,x,y2,width2,count);
        if (this->surf_wnd == 0) {
          parent_190 = 0;
        }
        else {
          parent_190 = this->surf_wnd + 0x48;
        }
        hotspot_create
                  ((ClickControl *)(this->sprite_hotspots + i * 0x40),parent_190,i + 300,
                   (iptr)rect);
        hotspot_set_click_callback((HotspotClickSetView *)(this->sprite_hotspots + i * 0x40),(iptr)dialog_on_sprite_click);
        hotspot_set_dblclick_callback((HotspotDblClickSetView *)(this->sprite_hotspots + i * 0x40),(iptr)dialog_sprite_on_dblclick);
        y2 = y2 + this->section_gap + count;
        i++;
      }
    }
    if (this->edit_field_list != 0) {
      edit_field = this->edit_field_list;
      x = this->edit_count;
      edits = operator_new(x * 0x48 + 4);
      eh_state = 9;
      if (edits == (u32 *)0x0) {
        edits = (u32 *)0x0;
      }
      else {
        *edits = x;
        crt_vector_ctor_iterator(edits + 1,0x48,*edits,edit_ctor,
                     edit_dtor);
        edits++;
      }
      eh_state = 0xffffffff;
      this->edit_controls = (uptr)edits;
      i = 0;
      for (; edit_field != 0; edit_field = *(uptr *)(edit_field + 0x18)) {
        if (this->surf_wnd == 0) {
          parent_194 = 0;
        }
        else {
          parent_194 = this->surf_wnd + 0x48;
        }
        value = *(i32 *)(edit_field + 0x14);
        text = *(i32 *)(edit_field + 4);
        count = dialog_edit_row_height((DialogCore *)this);
        edit_create_at
                  ((EditControl *)(this->edit_controls + i * 0x48),parent_194,0x14,
                   this->edit_x + this->edit_label_width,count * i + this->edit_y,text,value)
        ;
        if (2 < game.multiplayer) {
          edit_set_change_callback((EditChangeSetView *)(this->edit_controls + i * 0x48),(iptr)dialog_edit_on_change)
          ;
        }
        edit_set_max_len
                  ((EditMaxLenView *)(this->edit_controls + i * 0x48),*(i32 *)(edit_field + 8));
        i++;
      }
    }
    if (this->std_button_count + this->extra_button_count != 0) {
      count = this->std_button_count + this->extra_button_count;
      buttons = operator_new(count * 0x3c + 4);
      eh_state = 10;
      if (buttons == (int *)0x0) {
        buttons = (int *)0x0;
      }
      else {
        *buttons = count;
        crt_vector_ctor_iterator(buttons + 1,0x3c,*buttons,button_ctor,
                     ctrl_dtor);
        buttons++;
      }
      eh_state = 0xffffffff;
      this->button_controls = (uptr)buttons;
    }
    for (i = 0; i < (int)(this->std_button_count + this->extra_button_count); i++) {
      if (i < (int)this->std_button_count) {
        button_id = *(iptr *)((u8 *)&this->extra_button_labels + i * 8 + 0x18);
        label = (&dialog_button_labels)[button_id];
      }
      else {
        button_id = -1;
        label = *(i8 **)((int)this + (i - this->std_button_count) * 4 + 0x294);
      }
      pos = dialog_line_height((DialogTextView *)this);
      rect_set_xywh((iptr)rect,*(i32 *)((u8 *)&this->extra_button_labels + i * 8 + 0x1c),
                         this->button_y,this->button_width,pos);
      if (this->surf_wnd == 0) {
        parent_198 = 0;
      }
      else {
        parent_198 = this->surf_wnd + 0x48;
      }
      button_create
                ((Control *)(this->button_controls + i * 0x3c),parent_198,i + 100,
                 (iptr)rect,(iptr)label);
      if ((button_id == 2) || ((button_id == 0 && ((this->style_flags & 1) == 0)))) {
        ctrl_set_cancel_button((Control *)(this->button_controls + i * 0x3c));
      }
      if (button_id == 0) {
        ctrl_set_default_button((Control *)(this->button_controls + i * 0x3c));
      }
      button_set_callback
                ((Control *)(this->button_controls + i * 0x3c),(iptr)dialog_on_button_click);
    }
    wnd_set_keydown_handler((WndEventHandlers *)(this->surf_wnd + 0x58),(iptr)dialog_on_keydown);
    wnd_set_char_handler((WndEventHandlers *)(this->surf_wnd + 0x58),(iptr)dialog_on_char);
    this->style_flags = this->style_flags | 0x200;
  }
  return;
}
#undef dialog_clamp_overflow
#undef dialog_stack
#undef dialog_stack_top
#undef parent_198
#undef parent_194
#undef parent_190
#undef parent_18c
#undef parent_188
#undef parent_184
#undef parent_180
#undef parent_17c
#undef parent_178
#undef parent_174
#undef parent_170
#undef buttons
#undef edits
#undef hotspots
#undef radio_group2
#undef checkboxes2
#undef hscroll2
#undef vscroll2
#undef listbox22
#undef hscroll
#undef vscroll
#undef listbox3
#undef item_index
#undef edit_field
#undef y2
#undef label
#undef rect
#undef label_count2
#undef button_id
#undef is_listbox
#undef option
#undef sprite
#undef i
#undef unused_flag
#undef width2
#undef labels
#undef saved_seh
#undef seh_handler
#undef eh_state

/* 005a3bae auto */
#define found (*(iptr *)(frame_ + FRAME_OFF(0)))
#define index (*(i32 *)(frame_ + FRAME_OFF(4)))
#define node2 (*(iptr *)(frame_ + FRAME_OFF(8)))
void __cdecl dialog_radio_on_dblclick(i32 ctrl_id,int item)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  found = 0;
  if (active_dialog != 0) {
    index = 0;
    for (node2 = *(iptr *)(active_dialog + 0x228); node2 != 0;
        node2 = *(iptr *)(node2 + 0x10)) {
      if (item == index) {
        found = node2;
      }
      index++;
    }
    *(i32 *)(active_dialog + 0xd8) = 0xffffffff;
    if (found != 0) {
      *(i32 *)(active_dialog + 0xd8) = *(i32 *)(found + 4);
    }
    *(uint *)(active_dialog + 0x3c) = *(uint *)(active_dialog + 0x3c) | 0x2000;
    dialog_end_current();
  }
  return;
}
#undef found
#undef index
#undef node2

/* 005a3c58 auto */
void __cdecl dialog_end_current(void)

{
  *(uint *)(active_dialog + 0x3c) = *(uint *)(active_dialog + 0x3c) | 0x400;
  wnd_end_modal_loop((ModalMenuWindow *)(*(int *)active_dialog + 0x48));
  return;
}

/* 005a3c83 auto */
void __cdecl dialog_listbox_on_dblclick(void)

{
  if ((active_dialog != 0) && ((*(byte *)(active_dialog + 0x3d) & 4) == 0)) {
    *(uint *)(active_dialog + 0x3c) = *(uint *)(active_dialog + 0x3c) | 0x2000;
    dialog_end_current();
  }
  return;
}

/* 005a3cca auto */
#define sprite (*(i32 * *)(frame_ + FRAME_OFF(4)))
#define i (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl dialog_on_sprite_click(int ctrl_id)

{
  bool changed;
  int done;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  changed = false;
  sprite = *(i32 **)(active_dialog + 0x234);
  if (sprite != (i32 *)0x0) {
    for (i = 0; i < ctrl_id - 300; i++) {
      sprite = (i32 *)sprite[4];
      if (sprite == (i32 *)0x0) {
        return;
      }
    }
    *(i32 *)(active_dialog + 0xd8) = *sprite;
    if ((*(i32 **)(active_dialog + 0x224) != sprite) &&
       (*(i32 **)(active_dialog + 0x224) = sprite,
       (*(byte *)(active_dialog + 0x3e) & 2) != 0)) {
      changed = true;
    }
    if (*(int *)(active_dialog + 0x23c) == 0) {
      if (changed) {
        dialog_render((Dialog *)active_dialog);
      }
    }
    else {
      done = (*((code **)(active_dialog))[143])(*sprite);
      dialog_render((Dialog *)active_dialog);
      if (done != 0) {
        *(uint *)(active_dialog + 0x3c) = *(uint *)(active_dialog + 0x3c) | 0x2000;
        dialog_end_current();
      }
    }
  }
  return;
}
#undef sprite
#undef i

/* 005a3df3 auto */
void __cdecl dialog_sprite_on_dblclick(void)

{
  int done;
  
  if (*(int *)(active_dialog + 0x240) != 0) {
    done = (*((code **)(active_dialog))[144])(0);
    if (done == 0) {
      dialog_render((Dialog *)active_dialog);
    }
    else {
      *(uint *)(active_dialog + 0x3c) = *(uint *)(active_dialog + 0x3c) | 0x2000;
      dialog_end_current();
    }
  }
  return;
}

/* 005a3e56 auto */
#define dialog_timeout_start_i32 (*(i32 *)((u8 *)&g.d_006cec80))
#define sprite_index (*(int *)(frame_ + FRAME_OFF(0)))
#define found (*(iptr *)(frame_ + FRAME_OFF(4)))
#define button_id (*(int *)(frame_ + FRAME_OFF(8)))
#define index (*(int *)(frame_ + FRAME_OFF(12)))
#define node2 (*(iptr *)(frame_ + FRAME_OFF(20)))
#define sprite (*(iptr *)(frame_ + FRAME_OFF(24)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl dialog_on_button_click(int ctrl_id)

{
  int button_index;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (active_dialog != 0) {
    dialog_timeout_start_i32 = timer_ticks();
    button_index = ctrl_id - 100;
    if (button_index < *(int *)(active_dialog + 0x30)) {
      button_id = *(int *)(active_dialog + 0x2ac + button_index * 8);
    }
    else {
      *(int *)(active_dialog + 0xdc) = (button_index - *(int *)(active_dialog + 0x30)) + 1;
      button_id = 0;
    }
    if (button_id == 1) {
      *(uint *)(active_dialog + 0x3c) = *(uint *)(active_dialog + 0x3c) | 0x80;
    }
    if (((button_id == 0) && ((*(byte *)(active_dialog + 0x3e) & 2) != 0)) &&
       (*(int *)(active_dialog + 0x224) != 0)) {
      sprite = *(iptr *)(active_dialog + 0x234);
      sprite_index = 0;
      for (; (sprite != 0 && (*(int *)(active_dialog + 0x224) != sprite));
          sprite = *(iptr *)(sprite + 0x10)) {
        sprite_index++;
      }
      if (sprite != 0) {
        dialog_on_sprite_click(sprite_index + 300);
      }
    }
    if (button_id == 2) {
      *(i32 *)(active_dialog + 0xd8) = 0xffffffff;
    }
    else {
      if ((*(int *)(active_dialog + 0x2c) < 2) || (*(int *)(active_dialog + 0x28) != 0)) {
        *(i32 *)(active_dialog + 0xd8) = 0;
      }
      if ((*(int *)(active_dialog + 0x28) != 0) && ((*(uint *)(active_dialog + 0x3c) & 0x1004) == 0)
         ) {
        index = 0;
        found = 0;
        node2 = *(iptr *)(active_dialog + 0x228);
        button_index = radiogrp_get_selected(*(RadioGroupGetSelView **)(active_dialog + 0x268));
        for (; node2 != 0; node2 = *(iptr *)(node2 + 0x10)) {
          if (button_index == index) {
            found = node2;
          }
          index++;
        }
        if (found != 0) {
          *(i32 *)(active_dialog + 0xd8) = *(i32 *)(found + 4);
        }
      }
    }
    dialog_end_current();
  }
  return;
}
#undef dialog_timeout_start_i32
#undef sprite_index
#undef found
#undef button_id
#undef index
#undef node2
#undef sprite

/* 005a407f auto */
#define dialog_timeout_start_i32 (*(i32 *)((u8 *)&g.d_006cec80))
#define sprite (*(uptr *)(frame_ + FRAME_OFF(4)))
#define node2 (*(uptr *)(frame_ + FRAME_OFF(8)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl dialog_on_keydown(i32 key)

{
  int count;
  uptr option;
  int index;
  int pos;
  i32 redraw;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (active_dialog == 0) {
    return;
  }
  if (((*(byte *)(active_dialog + 0x3d) & 0x10) == 0) || (*(int *)(active_dialog + 0x24) != 0)) {
    dialog_timeout_start_i32 = timer_ticks();
  }
  if ((*(byte *)(active_dialog + 0x3e) & 2) != 0) {
    switch(key) {
    case 0xa2:
    case 0xc1:
      *(i32 *)(active_dialog + 0x224) =
           *(i32 *)(*(int *)(active_dialog + 0x224) + 0x10);
      if (*(int *)(active_dialog + 0x224) == 0) {
        *(i32 *)(active_dialog + 0x224) = *(i32 *)(active_dialog + 0x234);
      }
      dialog_render((Dialog *)active_dialog);
      break;
    case 0xa8:
    case 0xc0:
      for (sprite = *(uptr *)(active_dialog + 0x234);
          ((sprite != 0 && (*(int *)(sprite + 0x10) != *(int *)(active_dialog + 0x224))) &&
          (*(int *)(sprite + 0x10) != 0)); sprite = *(uptr *)(sprite + 0x10)) {
      }
      *(uptr *)(active_dialog + 0x224) = sprite;
      dialog_render((Dialog *)active_dialog);
      break;
    case 0xd1:
      if (*(int *)(active_dialog + 0x224) != 0) {
        dialog_on_sprite_click(**(i32 **)(active_dialog + 0x224));
      }
    }
  }
  if ((*(uint *)(active_dialog + 0x3c) & 0x41000) != 0x1000) {
    return;
  }
  if (*(int *)(active_dialog + 0x28) == 0) {
    key = 0;
  }
  do {
    switch(key) {
    case 0xa1:
    case 199:
      index = dialog_option_group_index
                        ((DialogOptionList *)active_dialog,*(uptr *)(active_dialog + 0x220));
      pos = dialog_count_group_options
                        ((DialogOptionList *)active_dialog,*(i32 *)(active_dialog + 0x48));
      if (pos - 1 <= index) {
        return;
      }
      index = dialog_count_group_options
                        ((DialogOptionList *)active_dialog,*(i32 *)(active_dialog + 0x48));
      redraw = dialog_option_at((DialogOptionList *)active_dialog,index - 1);
      *(i32 *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) = redraw;
      dialog_select_option
                ((DialogOptionList *)active_dialog,
                 *(uptr *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4),0);
      dialog_draw_option_list((DialogOptionList *)active_dialog);
      return;
    case 0xa2:
    case 0xc1:
      node2 = *(uptr *)(active_dialog + 0x220);
      goto LAB_005a43d9;
    case 0xa3:
    case 0xc6:
      if (*(int *)(active_dialog + 0x38) < 2) {
        pos = dialog_option_group_index
                          ((DialogOptionList *)active_dialog,*(uptr *)(active_dialog + 0x220));
        index = *(int *)(active_dialog + 0x5c + *(int *)(active_dialog + 0x48) * 4);
        count = dialog_count_group_options
                          ((DialogOptionList *)active_dialog,*(i32 *)(active_dialog + 0x48));
        if (index + pos < count) {
          redraw = 1;
          option = dialog_option_at
                            ((DialogOptionList *)active_dialog,
                             pos + *(int *)(active_dialog + 0x5c +
                                             *(int *)(active_dialog + 0x48) * 4));
          dialog_select_option((DialogOptionList *)active_dialog,option,redraw);
          return;
        }
        index = dialog_count_group_options
                          ((DialogOptionList *)active_dialog,*(i32 *)(active_dialog + 0x48));
        redraw = 1;
        option = dialog_option_at((DialogOptionList *)active_dialog,index - 1);
        dialog_select_option((DialogOptionList *)active_dialog,option,redraw);
        return;
      }
      key = 0xc3;
      break;
    case 0xa4:
    case 0xc2:
      if (*(int *)(active_dialog + 0x38) != 1) {
        index = dialog_option_group_index
                          ((DialogOptionList *)active_dialog,*(uptr *)(active_dialog + 0x220));
        pos = dialog_option_group_index
                          ((DialogOptionList *)active_dialog,
                           *(uptr *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4));
        if (*(int *)(active_dialog + 0x5c + *(int *)(active_dialog + 0x48) * 4) + pos <= index) {
          redraw = 1;
          option = dialog_option_at
                            ((DialogOptionList *)active_dialog,
                             index - *(int *)(active_dialog + 0x5c +
                                             *(int *)(active_dialog + 0x48) * 4));
          dialog_select_option((DialogOptionList *)active_dialog,option,redraw);
          return;
        }
        if (index < *(int *)(active_dialog + 0x5c + *(int *)(active_dialog + 0x48) * 4)) {
          return;
        }
        index = dialog_option_group_index
                          ((DialogOptionList *)active_dialog,
                           *(uptr *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4));
        redraw = dialog_option_at
                          ((DialogOptionList *)active_dialog,
                           index - *(int *)(active_dialog + 0x5c +
                                           *(int *)(active_dialog + 0x48) * 4));
        *(i32 *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) = redraw;
        index = dialog_option_group_index
                          ((DialogOptionList *)active_dialog,*(uptr *)(active_dialog + 0x220));
        redraw = 0;
        option = dialog_option_at
                          ((DialogOptionList *)active_dialog,
                           index - *(int *)(active_dialog + 0x5c +
                                           *(int *)(active_dialog + 0x48) * 4));
        dialog_select_option((DialogOptionList *)active_dialog,option,redraw);
        dialog_draw_option_list((DialogOptionList *)active_dialog);
        return;
      }
      key = 0xc0;
      break;
    default:
      return;
    case 0xa6:
    case 0xc3:
      if (*(int *)(active_dialog + 0x38) != 1) {
        pos = dialog_option_group_index
                          ((DialogOptionList *)active_dialog,*(uptr *)(active_dialog + 0x220));
        index = *(int *)(active_dialog + 0x5c + *(int *)(active_dialog + 0x48) * 4);
        count = dialog_count_group_options
                          ((DialogOptionList *)active_dialog,*(i32 *)(active_dialog + 0x48));
        if (count <= index + pos) {
          return;
        }
        redraw = 1;
        option = dialog_option_at
                          ((DialogOptionList *)active_dialog,
                           pos + *(int *)(active_dialog + 0x5c +
                                           *(int *)(active_dialog + 0x48) * 4));
        dialog_select_option((DialogOptionList *)active_dialog,option,redraw);
        return;
      }
      key = 0xc1;
      break;
    case 0xa7:
    case 0xc4:
      index = dialog_option_group_index
                        ((DialogOptionList *)active_dialog,*(uptr *)(active_dialog + 0x220));
      if (index < 1) {
        return;
      }
      redraw = dialog_option_at((DialogOptionList *)active_dialog,0);
      *(i32 *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) = redraw;
      dialog_select_option
                ((DialogOptionList *)active_dialog,
                 *(uptr *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4),0);
      dialog_draw_option_list((DialogOptionList *)active_dialog);
      return;
    case 0xa8:
    case 0xc0:
      node2 = *(uptr *)(active_dialog + 0x220);
      goto LAB_005a4287;
    case 0xa9:
    case 0xc5:
      if (*(int *)(active_dialog + 0x38) < 2) {
        index = dialog_option_group_index
                          ((DialogOptionList *)active_dialog,*(uptr *)(active_dialog + 0x220));
        if (*(int *)(active_dialog + 0x5c + *(int *)(active_dialog + 0x48) * 4) <= index) {
          redraw = 1;
          option = dialog_option_at
                            ((DialogOptionList *)active_dialog,
                             index - *(int *)(active_dialog + 0x5c +
                                             *(int *)(active_dialog + 0x48) * 4));
          dialog_select_option((DialogOptionList *)active_dialog,option,redraw);
          return;
        }
        redraw = 1;
        option = dialog_option_at((DialogOptionList *)active_dialog,0);
        dialog_select_option((DialogOptionList *)active_dialog,option,redraw);
        return;
      }
      key = 0xc2;
    }
  } while( true );
  while (node2 = *(uptr *)(node2 + 0x14),
        *(int *)(active_dialog + 0x48) != *(int *)(node2 + 0xc)) {
LAB_005a4287:
    if (*(int *)(node2 + 0x14) == 0) break;
  }
  if (*(int *)(active_dialog + 0x48) != *(int *)(node2 + 0xc)) {
    return;
  }
  if (*(uptr *)(active_dialog + 0x220) == node2) {
    return;
  }
  if (*(int *)(active_dialog + 0x38) != 1) {
    index = dialog_option_group_index
                      ((DialogOptionList *)active_dialog,
                       *(uptr *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4));
    pos = dialog_option_group_index((DialogOptionList *)active_dialog,node2);
    if (pos < index) {
      index = dialog_option_group_index
                        ((DialogOptionList *)active_dialog,
                         *(uptr *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4));
      redraw = dialog_option_at
                        ((DialogOptionList *)active_dialog,
                         index - *(int *)(active_dialog + 0x5c + *(int *)(active_dialog + 0x48) * 4)
                        );
      *(i32 *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) = redraw;
      dialog_select_option((DialogOptionList *)active_dialog,node2,0);
      dialog_draw_option_list((DialogOptionList *)active_dialog);
      return;
    }
  }
  dialog_select_option((DialogOptionList *)active_dialog,node2,1);
  return;
  while (node2 = *(uptr *)(node2 + 0x10),
        *(int *)(active_dialog + 0x48) != *(int *)(node2 + 0xc)) {
LAB_005a43d9:
    if (*(int *)(node2 + 0x10) == 0) break;
  }
  if ((*(int *)(active_dialog + 0x48) == *(int *)(node2 + 0xc)) &&
     (*(uptr *)(active_dialog + 0x220) != node2)) {
    dialog_select_option((DialogOptionList *)active_dialog,node2,1);
  }
  return;
}
#undef dialog_timeout_start_i32
#undef sprite
#undef node2

/* 005a49c1 auto */
#define dialog_timeout_start_i32 (*(i32 *)((u8 *)&g.d_006cec80))
#define match_index (*(iptr *)(frame_ + FRAME_OFF(4)))
#define match (*(uptr *)(frame_ + FRAME_OFF(8)))
#define node2 (*(uptr *)(frame_ + FRAME_OFF(16)))
#define counter2 (*(iptr *)(frame_ + FRAME_OFF(20)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl dialog_on_char(byte ch)

{
  int target_index;
  uint upper_ch;
  uint first_ch;
  int top_index;
  int bottom_index;
  i32 top_option;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((active_dialog != 0) && (target_index = _isalpha((uint)ch), target_index != 0)) {
    dialog_timeout_start_i32 = timer_ticks();
    upper_ch = crt_toupper((uint)ch);
    if ((*(uint *)(active_dialog + 0x3c) & 0x41000) == 0x1000) {
      node2 = *(uptr *)(active_dialog + 0x220);
      match = 0;
      counter2 = 0;
      do {
        do {
          node2 = *(uptr *)(node2 + 0x10);
          if (node2 == 0) {
            node2 = *(uptr *)(active_dialog + 0x228);
          }
        } while (*(int *)(active_dialog + 0x48) != *(int *)(node2 + 0xc));
        first_ch = crt_toupper((int)**(char **)(node2 + 8));
        if (first_ch == (upper_ch & 0xff)) {
          match = node2;
        }
      } while ((match == 0) && (counter2 = counter2 + 1, counter2 < 2000));
      if (match != 0) {
        target_index = dialog_option_group_index((DialogOptionList *)active_dialog,match);
        counter2 = 0;
        while( true ) {
          top_index = dialog_option_group_index
                            ((DialogOptionList *)active_dialog,
                             *(uptr *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4));
          bottom_index = *(int *)(active_dialog + 0x5c + *(int *)(active_dialog + 0x48) * 4) *
                  *(int *)(active_dialog + 0x38) + top_index;
          if ((*(int *)(active_dialog + 0x38) == 1) || ((top_index <= target_index && (target_index < bottom_index)))) break;
          if (target_index < top_index) {
            top_option = dialog_option_at
                              ((DialogOptionList *)active_dialog,
                               top_index - *(int *)(active_dialog + 0x5c +
                                               *(int *)(active_dialog + 0x48) * 4));
            *(i32 *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) = top_option;
            counter2++;
          }
          else {
            if (target_index < bottom_index) {
              return;
            }
            top_option = dialog_option_at
                              ((DialogOptionList *)active_dialog,
                               top_index + *(int *)(active_dialog + 0x5c +
                                               *(int *)(active_dialog + 0x48) * 4));
            *(i32 *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) = top_option;
            counter2++;
          }
        }
        if (counter2 == 0) {
          dialog_select_option((DialogOptionList *)active_dialog,match,1);
        }
        else {
          dialog_select_option((DialogOptionList *)active_dialog,match,0);
          dialog_draw_option_list((DialogOptionList *)active_dialog);
        }
      }
    }
    else if ((*(byte *)(active_dialog + 0x3e) & 2) == 0) {
      if (*(int *)(active_dialog + 0x34) != 0) {
        match_index = -1;
        for (counter2 = 0; counter2 < *(int *)(active_dialog + 0x34); counter2++) {
          first_ch = crt_toupper((int)**(char **)(active_dialog + 0x294 + counter2 * 4));
          if (first_ch == (upper_ch & 0xff)) {
            match_index = counter2;
            break;
          }
        }
        if (-1 < match_index) {
          ctrl_set_focus
                    ((ControlFocusView *)
                     ((*(int *)(active_dialog + 0x30) + counter2) * 0x3c +
                     *(int *)(active_dialog + 0x274)));
          dialog_on_button_click(*(int *)(active_dialog + 0x30) + counter2 + 100);
          return;
        }
      }
      if (*(int *)(active_dialog + 0x28) != 0) {
        match = 0;
        match_index = 0;
        for (node2 = *(uptr *)(active_dialog + 0x228); node2 != 0;
            node2 = *(uptr *)(node2 + 0x10)) {
          first_ch = crt_toupper((int)**(char **)(node2 + 8));
          if (first_ch == (upper_ch & 0xff)) {
            match = node2;
            break;
          }
          match_index++;
        }
        if (match != 0) {
          if ((*(byte *)(active_dialog + 0x3d) & 0x10) == 0) {
            if ((*(byte *)(active_dialog + 0x3c) & 4) == 0) {
              radiogrp_set_selected(*(RadioGroupSetSelView **)(active_dialog + 0x268),match_index);
            }
          }
          else {
            listbox_set_cur_sel
                      (*(ListBoxSetSelView **)(active_dialog + 0x278 + *(int *)(active_dialog + 0x48) * 4),
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
#undef dialog_timeout_start_i32
#undef match_index
#undef match
#undef node2
#undef counter2

/* 005a4df3 auto */
void __cdecl dialog_list_on_lbuttondown(i32 x,i32 y)

{
  int hit_index;
  uptr option;
  i32 redraw;
  
  if (active_dialog != 0) {
    dialog_pick_pane_at((DialogWindowView *)active_dialog,x,y);
    *(i32 *)(active_dialog + 0x218 + *(int *)(active_dialog + 0x48) * 4) = 0;
    if ((((*(uint *)(active_dialog + 0x3c) & 0x41000) == 0x1000) &&
        (*(int *)(active_dialog + 0x28) != 0)) &&
       (hit_index = dialog_option_at_point((DialogOptionList *)active_dialog,x,y),
       -1 < hit_index)) {
      *(i32 *)(active_dialog + 0x218 + *(int *)(active_dialog + 0x48) * 4) = 1;
      wnd_set_capture((WndBase *)(*(int *)active_dialog + 0x48));
      redraw = 1;
      option = dialog_option_at((DialogOptionList *)active_dialog,hit_index);
      dialog_select_option((DialogOptionList *)active_dialog,option,redraw);
    }
  }
  return;
}

/* 005a4edf auto */
#define sel_index (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl dialog_list_on_mousemove(i32 x,i32 y)

{
  int rows;
  int hit;
  uptr option;
  int top_index;
  int last_col;
  i32 value;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((active_dialog != 0) && ((*(uint *)(active_dialog + 0x3c) & 0x41000) == 0x1000)) &&
     (*(int *)(active_dialog + 0x218 + *(int *)(active_dialog + 0x48) * 4) != 0)) {
    hit = dialog_option_at_point((DialogOptionList *)active_dialog,x,y);
    if (hit < 0) {
      if (*(int *)(active_dialog + 0x5c + *(int *)(active_dialog + 0x48) * 4) *
          *(int *)(active_dialog + 0x38) < *(int *)(active_dialog + 0x28)) {
        top_index = dialog_option_group_index
                          ((DialogOptionList *)active_dialog,
                           *(uptr *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4));
        switch(hit) {
        case -4:
          if ((1 < *(int *)(active_dialog + 0x38)) &&
             (hit = dialog_column_start_index
                                ((DialogTextView *)active_dialog,*(int *)(active_dialog + 0x28) - 1)
             , top_index < hit)) {
            hit = *(int *)(active_dialog + 0x5c + *(int *)(active_dialog + 0x48) * 4);
            rows = *(int *)(active_dialog + 0x5c + *(int *)(active_dialog + 0x48) * 4);
            last_col = dialog_column_of_index
                              ((DialogTextView *)active_dialog,*(int *)(active_dialog + 0x28) - 1);
            hit = int_clamp_b(top_index + hit,0,rows * last_col);
            top_index = dialog_option_group_index
                              ((DialogOptionList *)active_dialog,*(uptr *)(active_dialog + 0x220));
            for (sel_index = top_index % *(int *)(active_dialog + 0x5c +
                                           *(int *)(active_dialog + 0x48) * 4) + hit;
                *(int *)(active_dialog + 0x5c + *(int *)(active_dialog + 0x48) * 4) + sel_index <
                *(int *)(active_dialog + 0x5c + *(int *)(active_dialog + 0x48) * 4) *
                *(int *)(active_dialog + 0x38) + hit;
                sel_index = sel_index + *(int *)(active_dialog + 0x5c +
                                            *(int *)(active_dialog + 0x48) * 4)) {
            }
            value = int_clamp_b(sel_index,0,*(int *)(active_dialog + 0x28) - 1);
            value = dialog_option_at((DialogOptionList *)active_dialog,value);
            *(i32 *)(active_dialog + 0x220) = value;
            value = dialog_option_at((DialogOptionList *)active_dialog,hit);
            *(i32 *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) = value;
            dialog_draw_option_list((DialogOptionList *)active_dialog);
          }
          break;
        case -3:
          if ((1 < *(int *)(active_dialog + 0x38)) && (0 < top_index)) {
            top_index -= *(int *)(active_dialog + 0x5c + *(int *)(active_dialog + 0x48) * 4);
            if (top_index < 1) {
              top_index = 0;
            }
            value = dialog_option_at((DialogOptionList *)active_dialog,top_index);
            *(i32 *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) = value;
            hit = dialog_option_group_index
                              ((DialogOptionList *)active_dialog,*(uptr *)(active_dialog + 0x220));
            value = dialog_option_at
                              ((DialogOptionList *)active_dialog,
                               top_index + hit % *(int *)(active_dialog + 0x5c +
                                                       *(int *)(active_dialog + 0x48) * 4));
            *(i32 *)(active_dialog + 0x220) = value;
            dialog_draw_option_list((DialogOptionList *)active_dialog);
          }
          break;
        case -2:
          if ((top_index < *(int *)(active_dialog + 0x28) - 1) && (*(int *)(active_dialog + 0x38) == 1)
             ) {
            value = dialog_option_at((DialogOptionList *)active_dialog,top_index + 1);
            *(i32 *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) = value;
            value = int_clamp_b(*(int *)(active_dialog + 0x5c + *(int *)(active_dialog + 0x48) * 4)
                                 * *(int *)(active_dialog + 0x38) + top_index + 1 - 1,0,
                                 *(int *)(active_dialog + 0x28) - 1);
            value = dialog_option_at((DialogOptionList *)active_dialog,value);
            *(i32 *)(active_dialog + 0x220) = value;
            dialog_draw_option_list((DialogOptionList *)active_dialog);
          }
          break;
        case -1:
          if ((0 < top_index) && (*(int *)(active_dialog + 0x38) == 1)) {
            value = dialog_option_at((DialogOptionList *)active_dialog,top_index - 1);
            *(i32 *)(active_dialog + 0x220) = value;
            *(i32 *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) =
                 *(i32 *)(active_dialog + 0x220);
            dialog_draw_option_list((DialogOptionList *)active_dialog);
          }
        }
      }
    }
    else {
      value = 1;
      option = dialog_option_at((DialogOptionList *)active_dialog,hit);
      dialog_select_option((DialogOptionList *)active_dialog,option,value);
    }
  }
  return;
}
#undef sel_index

/* 005a535e auto */
void __cdecl dialog_list_on_lbuttonup(i32 x,i32 y)

{
  if (active_dialog != 0) {
    dialog_list_on_mousemove(x,y);
    *(i32 *)(active_dialog + 0x218 + *(int *)(active_dialog + 0x48) * 4) = 0;
    wnd_release_capture((WndBase *)(*(int *)active_dialog + 0x48));
  }
  return;
}

/* 005a53b8 auto */
void __cdecl dialog_list_on_dblclick(i32 x,i32 y)

{
  int hit_index;
  
  if ((((active_dialog != 0) &&
       (dialog_pick_pane_at((DialogWindowView *)active_dialog,x,y),
       (*(uint *)(active_dialog + 0x3c) & 0x41000) == 0x1000)) &&
      (*(int *)(active_dialog + 0x28) != 0)) &&
     (((*(byte *)(active_dialog + 0x3d) & 4) == 0 &&
      (hit_index = dialog_option_at_point((DialogOptionList *)active_dialog,x,y),
      -1 < hit_index)))) {
    *(i32 *)(active_dialog + 0x218 + *(int *)(active_dialog + 0x48) * 4) = 1;
    dialog_list_on_lbuttonup(x,y);
    *(uint *)(active_dialog + 0x3c) = *(uint *)(active_dialog + 0x3c) | 0x2000;
    dialog_end_current();
  }
  return;
}

/* 005a5494 auto */
void __cdecl dialog_list_on_hscroll(int scroll_pos)

{
  int top_option;
  
  if (active_dialog != 0) {
    *(i32 *)(active_dialog + 0x48) = 0;
    top_option = dialog_option_at
                      ((DialogOptionList *)active_dialog,
                       *(int *)(active_dialog + 0x5c + *(int *)(active_dialog + 0x48) * 4) * scroll_pos
                      );
    if (*(int *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) != top_option) {
      *(int *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) = top_option;
      dialog_draw_option_list((DialogOptionList *)active_dialog);
    }
  }
  return;
}

/* 005a552c auto */
void __cdecl dialog_list2_on_vscroll(i32 scroll_pos)

{
  int top_option;
  
  if (active_dialog != 0) {
    *(i32 *)(active_dialog + 0x48) = 1;
    top_option = dialog_option_at((DialogOptionList *)active_dialog,scroll_pos);
    if (*(int *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) != top_option) {
      *(int *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) = top_option;
      dialog_draw_option_list((DialogOptionList *)active_dialog);
    }
  }
  return;
}

/* 005a55b1 auto */
void __cdecl dialog_list2_on_hscroll(int scroll_pos)

{
  int top_option;
  
  if (active_dialog != 0) {
    *(i32 *)(active_dialog + 0x48) = 1;
    top_option = dialog_option_at
                      ((DialogOptionList *)active_dialog,
                       *(int *)(active_dialog + 0x5c + *(int *)(active_dialog + 0x48) * 4) * scroll_pos
                      );
    if (*(int *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) != top_option) {
      *(int *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) = top_option;
      dialog_draw_option_list((DialogOptionList *)active_dialog);
    }
  }
  return;
}

/* 005a5649 auto */
#define dlg_client_tile_surface (*(int *)((u8 *)&g.d_00635aa4))
#define dlg_frame_tile_surface (*(int *)((u8 *)&g.d_00635aa0))
void __thiscall dialog_fill_rect_bg(DialogTextView *this,iptr rect,int area)

{
  i32 height;
  i32 width;
  i32 src_x;
  i32 src_y;
  
  if (this->bg_surface == 0) {
    if ((dlg_frame_tile_surface == 0) || (area != 1)) {
      if ((dlg_client_tile_surface == 0) || (area != 2)) {
        gfx_fill_rect(this->surf_wnd,rect,this->bg_color);
      }
      else {
        src_y = 0;
        src_x = 0;
        height = rect_height(rect);
        width = rect_width(rect);
        gfx_tile_fill(this->surf_wnd,dlg_client_tile_surface,*(i32 *)rect,
                           *(i32 *)(rect + 4),width,height,src_x,src_y);
      }
    }
    else {
      src_y = 0;
      src_x = 0;
      height = rect_height(rect);
      width = rect_width(rect);
      gfx_tile_fill(this->surf_wnd,dlg_frame_tile_surface,*(i32 *)rect,
                         *(i32 *)(rect + 4),width,height,src_x,src_y);
    }
  }
  else {
    height = rect_height(rect);
    width = rect_width(rect);
    gfx_copy_rect_same_pos(this->bg_surface,this->surf_wnd,*(i32 *)rect,
                       *(i32 *)(rect + 4),width,height);
  }
  return;
}
#undef dlg_client_tile_surface
#undef dlg_frame_tile_surface

/* 005a577e auto */
#define sprite_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define pane (*(u32 *)(frame_ + FRAME_OFF(20)))
#define saved_pane (*(u32 *)(frame_ + FRAME_OFF(24)))
#define label_x (*(int *)(frame_ + FRAME_OFF(28)))
#define sprite_h (*(int *)(frame_ + FRAME_OFF(32)))
#define edit_field (*(uptr *)(frame_ + FRAME_OFF(36)))
#define sprite_y2 (*(u32 *)(frame_ + FRAME_OFF(40)))
#define sprite_x2 (*(u32 *)(frame_ + FRAME_OFF(44)))
#define created (*(int *)(frame_ + FRAME_OFF(48)))
#define title_y (*(int *)(frame_ + FRAME_OFF(52)))
#define label_y (*(int *)(frame_ + FRAME_OFF(56)))
#define title_x (*(int *)(frame_ + FRAME_OFF(60)))
#define sprite (*(i32 * *)(frame_ + FRAME_OFF(64)))
#define i (*(int *)(frame_ + FRAME_OFF(68)))
#define sprite_w (*(int *)(frame_ + FRAME_OFF(72)))
#define rect (*(i8 (*)[4])(frame_ + FRAME_OFF(76)))
#define rect_top2 (*(int *)(frame_ + FRAME_OFF(80)))
#define rect_bottom2 (*(int *)(frame_ + FRAME_OFF(88)))
void __thiscall dialog_render(Dialog *this)

{
  int tmp;
  i32 size;
  int row_height;
  int line_spacing;
  u32 zoom;
  i8 frame_[FRAME_OFF(96)] __attribute__((aligned(8)));  /* original stack frame */
  
  created = 0;
  if ((this->style_flags & 0x20) == 0) {
    tmp = dialog_compute_layout((DialogOptionList *)this);
    if (tmp != 0) {
      return;
    }
    created = dialog_create_window((DialogWindowView *)this);
    dialog_create_controls(this);
  }
  if ((this->style_flags & 0x4000) == 0) {
    rect_set_xywh((iptr)rect,this->origin_x,this->origin_y,this->wnd_width,this->wnd_height);
    if (this->border_width != 0) {
      for (i = 0; i < (int)this->bevel_width; i++) {
        gfx_draw_bevel_rect(this->surf_wnd,(iptr)rect,this->bevel_light_color,this->bevel_dark_color);
        rect_deflate((iptr)rect,1,1);
      }
      dialog_fill_rect_bg((DialogTextView *)this,(iptr)rect,1);
      rect_deflate((iptr)rect,this->border_width + this->bevel_width * -2,0);
      rect_top2 = rect_top2 + this->title_height + this->bevel_width * -2;
      rect_bottom2 -= ((this->chrome_height - this->title_height) + this->bevel_width * -2);
      for (i = 0; i < (int)this->bevel_width; i++) {
        gfx_draw_bevel_rect(this->surf_wnd,(iptr)rect,this->bevel_dark_color,this->bevel_light_color);
        rect_deflate((iptr)rect,1,1);
      }
    }
    dialog_fill_rect_bg((DialogTextView *)this,(iptr)rect,2);
  }
  if ((this->title_text != 0) && ((this->style_flags & 0x10000) == 0)) {
    zoom = this->wnd_width;
    tmp = font_text_width((GameFont *)this->title_font,this->title_text);
    title_x = ((int)zoom >> 1) - (tmp + 4 >> 1);
    title_y = this->bevel_width + this->pad_y;
    gfx_set_text_color_index(this->title_shadow_color);
    surface_draw_text
              ((DibSurface *)this->surf_wnd,this->title_font,this->title_text,title_x + 2,
               title_y + 1,5);
    gfx_set_text_color_index(this->title_color);
    surface_draw_text
              ((DibSurface *)this->surf_wnd,this->title_font,this->title_text,title_x + 1,title_y,5)
    ;
    surface_draw_text
              ((DibSurface *)this->surf_wnd,this->title_font,this->title_text,title_x,title_y,5);
  }
  dialog_draw_wrapped_text((DialogOptionList *)this,1);
  if (this->sprite_count != 0) {
    gfx_set_zoom_scale(this->sprite_zoom);
    sprite_x2 = this->sprite_x;
    sprite_y2 = this->sprite_y;
    for (sprite = (i32 *)this->sprite_list; sprite != (i32 *)0x0;
        sprite = (i32 *)sprite[4]) {
      zoom = this->sprite_zoom;
      size = sprite_width((Sprite *)sprite[3]);
      sprite_w = gfx_zoom_scale(size,zoom);
      zoom = this->sprite_zoom;
      size = sprite_height((Sprite *)sprite[3]);
      sprite_h = gfx_zoom_scale(size,zoom);
      if (this->on_draw_sprite == 0) {
        sprite_draw
                  ((Sprite *)sprite[3],(iptr)sprite_rect,this->surf_wnd,sprite_x2,sprite_y2);
      }
      else {
        (*(code *)this->on_draw_sprite)
                  (sprite[3],this->surf_wnd,*sprite,sprite[1],sprite_x2,sprite_y2);
      }
      if (((this->style_flags & 0x20000) != 0) && ((i32 *)this->selected_sprite == sprite)) {
        rect_set((iptr)rect,sprite_x2 - 1,sprite_y2 - 1,sprite_w + sprite_x2,
                           sprite_h + sprite_y2);
        gfx_draw_rect_frame(this->surf_wnd,(iptr)rect,this->frame_color);
      }
      tmp = sprite_h;
      if (sprite[2] != 0) {
        label_x = this->sprite_gap + sprite_w + sprite_x2;
        row_height = font_line_spacing((GameFont *)this->body_font);
        label_y = (tmp - row_height >> 1) + sprite_y2;
        dialog_draw_text_default_font((DialogTextView *)this,sprite[2],label_x,label_y,0);
      }
      sprite_y2 = sprite_y2 + sprite_h + this->section_gap;
    }
    gfx_reset_zoom_scale();
  }
  if (this->edit_count != 0) {
    edit_field = this->edit_field_list;
    i = 0;
    for (; edit_field != 0; edit_field = *(uptr *)(edit_field + 0x18)) {
      gfx_set_text_color_index(this->text_color);
      size = 5;
      tmp = dialog_edit_row_height((DialogCore *)this);
      tmp = tmp * i;
      row_height = dialog_edit_row_height((DialogCore *)this);
      zoom = this->edit_y;
      line_spacing = font_line_spacing((GameFont *)this->body_font);
      surface_draw_text_cur_font
                ((SurfaceTextCurFontView *)this->surf_wnd,*(i32 *)(edit_field + 0x10),this->edit_x,
                 (tmp + (row_height >> 1) + zoom) - (line_spacing >> 1),size);
      i++;
    }
  }
  if ((this->style_flags & 0x41000) == 0x1000) {
    dialog_draw_option_list((DialogOptionList *)this);
  }
  if (created == 0) {
    wnd_blit_surface((DibSurface *)this->surf_wnd);
    if (this->option_count != 0) {
      if ((this->style_flags & 0x1000) == 0) {
        if ((this->style_flags & 4) == 0) {
          radiogrp_show_all((RadioGroupShowView *)this->radio_group);
        }
        else {
          for (i = 0; i < (int)this->option_count; i++) {
            ctrl_show_and_redraw((Control *)(this->checkboxes + i * 0x3c));
          }
        }
      }
      else if ((this->style_flags & 0x40000) == 0) {
        saved_pane = this->cur_pane;
        for (pane = 0; (int)pane < 2; pane++) {
          if ((pane != 1) || ((this->style_flags & 0x400000) != 0)) {
            this->cur_pane = pane;
            if (*(int *)((u8 *)&this->extra_button_labels + this->cur_pane * 4 - 0x10) != 0) {
              ctrl_show_and_redraw
                        (*(Control **)((u8 *)&this->extra_button_labels + this->cur_pane * 4 - 0x10));
            }
            if (*(int *)((u8 *)&this->extra_button_labels + this->cur_pane * 4 - 8) != 0) {
              ctrl_show_and_redraw
                        (*(Control **)((u8 *)&this->extra_button_labels + this->cur_pane * 4 - 8));
            }
          }
        }
        this->cur_pane = saved_pane;
      }
    }
    if (this->edit_count != 0) {
      for (i = 0; i < (int)this->edit_count; i++) {
        ctrl_show_and_redraw((Control *)(i * 0x48 + this->edit_controls));
      }
    }
    if (this->std_button_count + this->extra_button_count != 0) {
      for (i = 0; i < (int)(this->std_button_count + this->extra_button_count); i++)
      {
        ctrl_show_and_redraw((Control *)(this->button_controls + i * 0x3c));
      }
    }
    if ((1 < (int)this->sprite_count) && (this->option_count == 0)) {
      for (i = 0; i < (int)this->sprite_count; i++) {
        ctrl_show_and_redraw((Control *)(this->sprite_hotspots + i * 0x40));
      }
    }
  }
  else {
    window_show((WindowObjectView *)this->surf_wnd);
  }
  this->style_flags = this->style_flags | 0x20;
  return;
}
#undef sprite_rect
#undef pane
#undef saved_pane
#undef label_x
#undef sprite_h
#undef edit_field
#undef sprite_y2
#undef sprite_x2
#undef created
#undef title_y
#undef label_y
#undef title_x
#undef sprite
#undef i
#undef sprite_w
#undef rect
#undef rect_top2
#undef rect_bottom2

/* 005a5f34 auto */
#define game_session_active (*(int *)((u8 *)&g.d_006252c4))
#define dialog_timeout_start_i32 (*(i32 *)((u8 *)&g.d_006cec80))
#define item_text (*(char (*)[132])(frame_ + FRAME_OFF(4)))
#define sel_text (*(char (*)[132])(frame_ + FRAME_OFF(136)))
#define option (*(uint * *)(frame_ + FRAME_OFF(268)))
#define i (*(int *)(frame_ + FRAME_OFF(272)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

u32 __thiscall dialog_run_modal(Dialog *this,iptr out_text,iptr timeout_secs)

{
  iptr main_hwnd;
  BOOL BVar1;
  int result;
  i8 frame_[FRAME_OFF(280)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (dialog_stack_depth != 0x10) {
    if (timeout_secs == 0) {
      dialog_timeout_start_i32 = timer_ticks();
    }
    else {
      dialog_timeout_start_i32 = timer_ticks();
      dialog_timeout_start_i32 = timeout_secs * 0x3c - 0x4b0 + dialog_timeout_start_i32;
    }
    if (game_session_active != 0) {
      main_hwnd = wnd_get_window((WndBase *)&main_frame_wnd);
      BVar1 = IsIconic(*(HWND *)(main_hwnd + 4));
      if (BVar1 != 0) {
        wnd_show_restored((WndBase *)&main_frame_wnd);
      }
    }
    this->style_flags = this->style_flags & 0xffffdfff;
    if ((this->style_flags & 0x4000) != 0) {
      this->style_flags = this->style_flags | 0x10000;
    }
    dialog_render(this);
    if (((this->style_flags & 0x20) != 0) && ((this->style_flags & 8) == 0)) {
      if (this->on_modal_poll == 0) {
        wnd_run_modal_loop((ModalMenuWindow *)(this->surf_wnd + 0x48));
        while ((this->style_flags & 0x400) == 0) {
          win_pump_one_message();
        }
      }
      else {
        while ((this->style_flags & 0x400) == 0) {
          result = (*(code *)this->on_modal_poll)(this);
          if (result != 0) {
            dialog_end_current();
          }
        }
      }
      if ((out_text != 0) && (this->edit_controls != 0)) {
        ctrl_get_text((ControlTextView *)this->edit_controls,out_text);
      }
      if (1 < (int)this->edit_count) {
        for (i = 0; i < (int)this->edit_count; i++) {
          ctrl_get_text
                    ((ControlTextView *)(this->edit_controls + i * 0x48),
                     (iptr)(&text_string_args + i * 0x104));
        }
      }
      if ((this->style_flags & 0x1000) == 0) {
        if ((this->style_flags & 4) != 0) {
          option = (uint *)this->option_list;
          i = 0;
          for (; option != (uint *)0x0; option = (uint *)option[4]) {
            *option = *option & 0xfffffffb;
            result = checkbox_is_checked
                              ((Control *)(this->checkboxes + i * 0x3c));
            if (result != 0) {
              *option = *option | 4;
            }
            i++;
          }
        }
      }
      else if (this->result_id == 0) {
        if ((this->style_flags & 0x40000) == 0) {
          this->result_id = *(u32 *)(this->selected_option + 4);
        }
        else {
          listbox_get_sel_text
                    (*(ListBoxSelTextView **)(this->control_ptr_slots + this->cur_pane * 4 + 0x14),(iptr)sel_text);
          this->result_id = *(u32 *)(this->option_list + 4);
          option = (uint *)this->option_list;
          i = 0;
          for (; option != (uint *)0x0; option = (uint *)option[4]) {
            listbox_get_text
                      (*(ListBoxTextView **)(this->control_ptr_slots + this->cur_pane * 4 + 0x14),i,
                       (iptr)item_text);
            result = _strcmp(sel_text,item_text);
            if (result == 0) {
              this->result_id = option[1];
            }
            i++;
          }
        }
      }
      if ((this->style_flags & 0x800) == 0) {
        dialog_close(this);
        input_flush_events();
        win_flush_pending_msgs();
        wnd_flush_paint();
        win_flush_pending_msgs();
      }
    }
  }
  return this->result_id;
}
#undef game_session_active
#undef dialog_timeout_start_i32
#undef item_text
#undef sel_text
#undef option
#undef i

/* 005a632a auto */
#define expanded (*(i8 (*)[256])(frame_ + FRAME_OFF(4)))
#define mode (*(int *)(frame_ + FRAME_OFF(260)))
#define result (*(i32 *)(frame_ + FRAME_OFF(264)))
#define has_edit (*(uint *)(frame_ + FRAME_OFF(268)))
#define line (*(char * *)(frame_ + FRAME_OFF(272)))
#define edit_text (*(i8 (*)[80])(frame_ + FRAME_OFF(276)))
#define list_rows2 (*(int *)(frame_ + FRAME_OFF(356)))
#define key2 (*(char * *)(frame_ + FRAME_OFF(360)))
#define option (*(uptr *)(frame_ + FRAME_OFF(364)))
#define option_index (*(int *)(frame_ + FRAME_OFF(368)))
#define number (*(int *)(frame_ + FRAME_OFF(372)))
#define edit_buf (*(i8 * *)(frame_ + FRAME_OFF(376)))
i32 __thiscall
dialog_load_text_section
          (Dialog *this,iptr file_name,iptr section,int default_value,iptr edit_default,iptr init_arg1,
          iptr init_arg2,iptr init_arg3,uint flags)

{
  int cmp;
  size_t len;
  u32 coord;
  i8 frame_[FRAME_OFF(384)] __attribute__((aligned(8)));  /* original stack frame */
  
  result = 1;
  mode = 1;
  option_index = 0;
  crt_strcpy(&dialog_section_name,section);
  cmp = text_open_section(file_name,section);
  if (cmp == 0) {
    if ((flags & 0x8000) == 0) {
      dialog_init(this,init_arg1,init_arg2,init_arg3,flags);
    }
    else {
      this->style_flags = this->style_flags | flags;
    }
    has_edit = (uint)(edit_default != 0);
    if (has_edit != 0) {
      crt_strcpy(edit_text,edit_default);
    }
    do {
      line = (char *)text_read_line(1);
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
                      ((DialogAddLineView *)this,(iptr)((u8 *)&g.d_00635b70),0xffffffff,0xffffffff,0xffffffff,0);
          }
        }
        else if (*line == '@') {
          key2 = line + 1;
          cmp = __strcmpi(key2,s_OPTIONS_00635b74);
          if ((cmp == 0) || (cmp = _strcmp(key2,s_PROMPT_00635b7c), cmp == 0)) {
            mode = 2;
          }
          else {
            cmp = __strcmpi(key2,&dlg_key_text_str);
            if (cmp == 0) {
              mode = 1;
            }
            else {
              cmp = __strnicmp(key2,s_TITLE_00635b8c,5);
              if (cmp == 0) {
                for (; (*key2 != '\0' && (*key2 != '=')); key2++) {
                }
                if (*key2 != '\0') {
                  key2++;
                }
                text_expand_vars((iptr)key2,(iptr)expanded);
                dialog_set_title((DialogWindowView *)this,(iptr)expanded);
              }
              else {
                cmp = __strnicmp(key2,s_BUTTON_00635b94,6);
                if (cmp == 0) {
                  for (; (*key2 != '\0' && (*key2 != '=')); key2++) {
                  }
                  if (*key2 != '\0') {
                    key2++;
                  }
                  text_expand_vars((iptr)key2,(iptr)expanded);
                  dialog_add_button((DialogButtonsView *)this,(iptr)expanded);
                }
                else {
                  cmp = __strnicmp(key2,s_COLUMNS_00635b9c,7);
                  if (cmp == 0) {
                    while ((*key2 != '\0' && (cmp = _isdigit((int)*key2), cmp == 0))) {
                      key2++;
                    }
                    number = _atoi(key2);
                    dialog_set_columns((DialogButtonsView *)this,number);
                  }
                  else {
                    cmp = __strnicmp(key2,s_HEIGHT_00635ba4,6);
                    if (cmp == 0) {
                      while ((*key2 != '\0' && (cmp = _isdigit((int)*key2), cmp == 0)))
                      {
                        key2++;
                      }
                      number = _atoi(key2);
                      dialog_set_height((DialogCore *)this,number);
                    }
                    else {
                      cmp = __strcmpi(key2,s_SMALLFONT_00635bac);
                      if (cmp != 0) {
                        cmp = __strnicmp(key2,&dlg_key_y_prefix,1);
                        if ((cmp == 0) && (cmp = _isalpha((int)key2[1]), cmp == 0)) {
                          while (((*key2 != '\0' &&
                                  (cmp = _isdigit((int)*key2), cmp == 0)) &&
                                 (*key2 != '-'))) {
                            key2++;
                          }
                          coord = _atoi(key2);
                          this->req_y = coord;
                        }
                        else {
                          cmp = __strnicmp(key2,&dlg_key_x_prefix,1);
                          if ((cmp == 0) && (cmp = _isalpha((int)key2[1]), cmp == 0)) {
                            while (((*key2 != '\0' &&
                                    (cmp = _isdigit((int)*key2), cmp == 0)) &&
                                   (*key2 != '-'))) {
                              key2++;
                            }
                            coord = _atoi(key2);
                            this->req_x = coord;
                          }
                          else {
                            cmp = __strnicmp(key2,s_WIDTH_00635bc0,5);
                            if (cmp == 0) {
                              while ((*key2 != '\0' &&
                                     (cmp = _isdigit((int)*key2), cmp == 0))) {
                                key2++;
                              }
                              number = _atoi(key2);
                              dialog_set_width((DialogWindowView *)this,number);
                            }
                            else {
                              cmp = __strnicmp(key2,s_LENGTH_00635bc8,6);
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
                                cmp = __strnicmp(key2,s_CHECKBOX_00635bd0,7);
                                if (cmp == 0) {
                                  this->style_flags = this->style_flags | 5;
                                }
                                else {
                                  cmp = __strnicmp(key2,s_LISTBOX_00635bdc,7);
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
                                              ((DialogTextView *)this,list_rows2,this->content_width,0);
                                  }
                                  else {
                                    cmp = __strnicmp(key2,s_SYSTEM_00635be4,6);
                                    if (cmp == 0) {
                                      this->style_flags = this->style_flags | 0x40000;
                                    }
                                    else {
                                      cmp = __strnicmp(key2,s_DEFAULT_00635bec,7);
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
                    ((DialogAddLineView *)this,(iptr)expanded,0xffffffff,0xffffffff,0xffffffff,0);
        }
        else if (mode == 2) {
          text_expand_vars((iptr)line,(iptr)expanded);
          if (has_edit == 0) {
            if ((this->style_flags & 4) == 0) {
              option = dialog_add_option
                                   ((DialogOptionList *)this,(iptr)expanded,option_index,0);
            }
            else {
              option = dialog_add_checkbox_option
                                   ((DialogOptionList *)this,(iptr)expanded,option_index,0);
            }
            if (default_value == option_index) {
              this->selected_option = option;
            }
            option_index++;
          }
          else {
            if (default_value == 0) {
              default_value = 5;
            }
            edit_buf = edit_text;
            if (this->edit_count != 0) {
              edit_buf = &text_string_args + this->edit_count * 0x104;
            }
            dialog_add_edit_field
                      ((DialogOptionList *)this,(iptr)expanded,(iptr)edit_buf,default_value);
          }
        }
      }
    } while (mode < 3);
    result = 0;
  }
  else if ((flags & 0x8000) == 0) {
    dialog_init(this,init_arg1,init_arg2,init_arg3,flags);
  }
  return result;
}
#undef expanded
#undef mode
#undef result
#undef has_edit
#undef line
#undef edit_text
#undef list_rows2
#undef key2
#undef option
#undef option_index
#undef number
#undef edit_buf

/* 005a6c23 auto */
#define dlg_parent_window (*(iptr *)((u8 *)&g.d_006359c4))
void __cdecl dlg_push_parent_window(iptr parent)

{
  dlg_saved_parent_window = dlg_parent_window;
  dlg_parent_window = parent;
  return;
}
#undef dlg_parent_window

/* 005a6c45 auto */
#define dlg_parent_window (*(i32 *)((u8 *)&g.d_006359c4))
void __cdecl dlg_pop_parent_window(void)

{
  dlg_parent_window = dlg_saved_parent_window;
  return;
}
#undef dlg_parent_window

/* 005a9520 auto */
/* Library Function - Multiple Matches With Different Base Names
    public: void * __thiscall CDaoIndexFieldInfo::`vector deleting destructor'(unsigned int)
    public: void * __thiscall CDaoRelationFieldInfo::`vector deleting destructor'(unsigned int)
    public: void * __thiscall CODBCFieldInfo::`vector deleting destructor'(unsigned int)
    public: void * __thiscall CString::`vector deleting destructor'(unsigned int)
   
   Library: Visual Studio 1998 Debug */

Hotspot * __thiscall hotspot_vector_dtor(Hotspot *this,uint flags)

{
  if ((flags & 2) == 0) {
    hotspot_dtor(this);
    if ((flags & 1) != 0) {
      operator_delete(this);
    }
  }
  else {
    crt_vector_dtor_iterator(this,0x40,VECTOR_COUNT(this),hotspot_dtor);
    operator_delete(&VECTOR_COUNT(this));
  }
  return this;
}

/* 005a95b0 auto */
SurfaceWindow * __thiscall surfwnd_scalar_dtor(SurfaceWindow *this,uint flags)

{
  surfwnd_dtor(this);
  if ((flags & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 005a9600 auto */
void __thiscall wnd_get_screen_rect(WndBase *this,iptr rect)

{
  wnd_obj_get_screen_rect(this->native_wnd,rect);
  return;
}

/* 005a96f0 auto */
uint __thiscall dialog_uses_alt_text_color(DialogAltColorView *this)

{
  return (uint)((this->style_flags & 0x100) != 0);
}

/* 005a9730 auto */
void __thiscall
dialog_draw_text_default_font
          (DialogTextView *this,i32 text,i32 x,i32 y,
          i32 flags)

{
  dialog_draw_text_shadowed(this,this->body_font,text,x,y,flags);
  return;
}

/* 005bb4ae auto */
void __thiscall
wnd_create_with_surface
          (DibSurface *this,iptr title,i32 style,i32 x,i32 y
          ,i32 width,i32 height,iptr palette,iptr parent)

{
  iptr hwnd;
  
  wnd_create_framed_child
            ((WndBase *)(this + 1),title,style,x,y,width,height,palette,
             parent);
  surface_create(this,width,height);
  surface_set_palette(this,palette);
  hwnd = wnd_get_window((WndBase *)(this + 1));
  wnd_install_paint_proc((iptr)this,hwnd);
  return;
}

/* 005bb574 auto */
#define wnd_active_child (*(u8 * *)((u8 *)&g.d_00637ea4))
void __thiscall wnd_repaint(SurfaceWindow *this)

{
  if (this == (SurfaceWindow *)0x0) {
    wnd_active_child = (u8 *)0x0;
  }
  else {
    wnd_active_child = this->window_2;
  }
  wnd_call_paint_cb(this);
  wnd_blit_surface((DibSurface *)this);
  return;
}
#undef wnd_active_child

/* 005bb5be auto */
bool __thiscall surfwnd_resize_dib(DibSurface *this,iptr rect)

{
  int result;
  i32 height;
  i32 width;
  
  result = surface_alloc_dib_by_bpp(this,rect);
  if (result == 1) {
    height = rect_height(rect);
    width = rect_width(rect);
    wnd_set_client_size((WndClientSizeView *)(this + 1),width,height);
  }
  return result == 1;
}

/* 005bb621 auto */
#define wnd_active_child (*(u8 * *)((u8 *)&g.d_00637ea4))
#define rect (*(tagRECT *)(frame_ + FRAME_OFF(4)))
void __thiscall surfwnd_on_resize(SurfaceWindow *this,int width,int height)

{
  int cur_size;
  i32 palette;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  cur_size = surface_get_width((DibSurface *)this);
  if ((cur_size == width) &&
     (cur_size = surface_get_height((DibSurface *)this), cur_size == height)) {
    return;
  }
  SetRect(&rect,0,0,width,height);
  (*((code **)(this->vtable))[0])(this,&rect);
  palette = wnd_get_palette_obj((WndPaletteObjView *)this->window_2);
  surface_apply_palette((DibSurface *)this,palette);
  if (this == (SurfaceWindow *)0x0) {
    wnd_active_child = (u8 *)0x0;
  }
  else {
    wnd_active_child = this->window_2;
  }
  wnd_call_paint_cb(this);
  wnd_blit_surface((DibSurface *)this);
  return;
}
#undef wnd_active_child
#undef rect

/* 005bb6c7 auto */
#define min_height2 (*(int *)(frame_ + FRAME_OFF(4)))
#define min_width2 (*(int *)(frame_ + FRAME_OFF(8)))
#define max_height2 (*(int *)(frame_ + FRAME_OFF(12)))
#define max_width2 (*(int *)(frame_ + FRAME_OFF(16)))
void __thiscall wnd_resize_clamped(WindowObjectView *this,int width,int height)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  wnd_get_min_size((WndMinSizeView *)(this + 0x12),(iptr)&min_width2,(iptr)&min_height2);
  wnd_get_max_size((WndMaxSizeView *)(this + 0x12),(iptr)&max_width2,(iptr)&max_height2);
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
  wnd_set_client_size((WndClientSizeView *)(this + 0x12),width,height);
  return;
}
#undef min_height2
#undef min_width2
#undef max_height2
#undef max_width2

/* 005bb8c0 auto */
u32 __thiscall wnd_get_palette_obj(WndPaletteObjView *this)

{
  return this->palette_obj;
}

/* 005bb8e0 auto */
void __thiscall wnd_set_client_size(WndClientSizeView *this,i32 width,i32 height)

{
  wnd_obj_set_client_size(this->native_wnd,width,height);
  return;
}

/* 005bb910 auto */
void __thiscall wnd_get_min_size(WndMinSizeView *this,iptr out_width,iptr out_height)

{
  *(u32 *)out_width = this->min_width;
  *(u32 *)out_height = this->min_height;
  return;
}

/* 005bb950 auto */
void __thiscall wnd_get_max_size(WndMaxSizeView *this,iptr out_width,iptr out_height)

{
  *(u32 *)out_width = this->max_width;
  *(u32 *)out_height = this->max_height;
  return;
}

/* 005bb990 auto */
void __thiscall wnd_call_paint_cb(SurfaceWindow *this)

{
  if (this->on_paint != 0) {
    (*(code *)this->on_paint)();
  }
  return;
}

/* 005bbc10 auto */
#define app_hinstance (*(HINSTANCE *)((u8 *)&g.d_006e4ff0))
#define pos_x2 (*(int *)(frame_ + FRAME_OFF(4)))
#define pos_y2 (*(int *)(frame_ + FRAME_OFF(8)))
#define outer_width (*(int *)(frame_ + FRAME_OFF(12)))
#define outer_height (*(int *)(frame_ + FRAME_OFF(16)))
#define parent_hwnd (*(HWND *)(frame_ + FRAME_OFF(20)))
#define ex_style (*(DWORD *)(frame_ + FRAME_OFF(24)))
#define style2 (*(uint *)(frame_ + FRAME_OFF(32)))
#define caption_height2 (*(int *)(frame_ + FRAME_OFF(36)))
#define frame_height (*(int *)(frame_ + FRAME_OFF(40)))
#define frame_width (*(int *)(frame_ + FRAME_OFF(44)))
i32 * __cdecl
wnd_obj_create(LPCSTR title,uint flags,int x,int y,int width,int height,
            iptr parent)

{
  i32 handle;
  i32 *wnd;
  int metric;
  HWND pHVar4;
  HDC pHVar5;
  HCURSOR pHVar6;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  ex_style = 0;
  handle = mem_handle_alloc(0x4c);
  wnd = (i32 *)mem_handle_lock(handle);
  *wnd = handle;
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
    wnd[0xc] = 0;
  }
  else {
    wnd[0xc] = 1;
  }
  if ((flags & 0x1000) == 0) {
    wnd[0xd] = 0;
  }
  else {
    wnd[0xd] = 1;
  }
  if (parent == 0) {
    parent_hwnd = (HWND)0x0;
  }
  else {
    parent_hwnd = *(HWND *)(parent + 4);
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
  pHVar4 = CreateWindowExA(ex_style,s_MSWindowClass_006366d0,title,style2,pos_x2,pos_y2,
                           outer_width,outer_height,parent_hwnd,(HMENU)0x0,app_hinstance,(LPVOID)0x0);
  wnd[1] = pHVar4;
  wnd_list_add_hwnd(wnd[1]);
  pHVar5 = GetDC((HWND)wnd[1]);
  wnd[2] = pHVar5;
  pHVar6 = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
  wnd[7] = pHVar6;
  wnd[6] = 0;
  wnd[8] = 0;
  wnd[0x11] = 0;
  wnd[5] = 0;
  wnd[3] = 0;
  wnd[9] = 0;
  wnd[10] = 0;
  wnd[0xb] = 0;
  wnd[0x12] = flags;
  wnd[0xe] = 0;
  wnd[0xf] = 0;
  wnd[4] = 0;
  wnd[0x10] = 8;
  return wnd;
}
#undef app_hinstance
#undef pos_x2
#undef pos_y2
#undef outer_width
#undef outer_height
#undef parent_hwnd
#undef ex_style
#undef style2
#undef caption_height2
#undef frame_height
#undef frame_width

/* 005bbfee auto */
void __cdecl wnd_obj_enable(iptr wnd,BOOL enable)

{
  if (wnd != 0) {
    EnableWindow(*(HWND *)(wnd + 4),enable);
  }
  return;
}

/* 005bc0ab auto */
i32 __cdecl wnd_obj_destroy(i32 *wnd)

{
  i32 handle;
  
  if (wnd != (i32 *)0x0) {
    wnd_stack_remove(wnd[1]);
    if (wnd[0x11] == 0) {
      if (wnd[1] != 0) {
        SetWindowLongA((HWND)wnd[1],4,0);
        ShowWindow((HWND)wnd[1],0);
        SetMenu((HWND)wnd[1],(HMENU)0x0);
        DestroyWindow((HWND)wnd[1]);
      }
      wnd[1] = 0;
    }
    if (wnd[5] != 0) {
      DeleteObject((HGDIOBJ)wnd[5]);
    }
    handle = *wnd;
    mem_handle_unlock(handle);
    mem_handle_free(handle);
  }
  return 0;
}

/* 005bc173 auto */
#define i (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl wnd_stack_check_leaks_nop(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (ms_window_stack_count != 0) {
    for (i = 0; i < ms_window_stack_count; i++) {
    }
  }
  return;
}
#undef i

/* 005bc1b5 auto */
void __cdecl wnd_list_add_hwnd(i32 hwnd)

{
  *(i32 *)(&ms_window_stack + ms_window_stack_count * 4) = hwnd;
  ms_window_stack_count++;
  return;
}

/* 005bc1db auto */
#define i (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl wnd_stack_remove(int hwnd)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (i = 0; (i < ms_window_stack_count && (*(int *)(&ms_window_stack + i * 4) != hwnd));
      i = i + 1) {
  }
  if (i < ms_window_stack_count - 1) {
    for (; i < ms_window_stack_count - 1; i++) {
      *(i32 *)(&ms_window_stack + i * 4) = *(i32 *)(&ms_window_stack_elem1 + i * 4);
    }
  }
  ms_window_stack_count--;
  if (ms_window_stack_count < 0) {
    dbg_log((iptr)((u8 *)&g.d_006366e0));
  }
  return;
}
#undef i

/* 005bc280 auto */
#define green (*(i8 (*)[4])(frame_ + FRAME_OFF(4)))
#define wnd_view (*(WndPaletteView * *)(frame_ + FRAME_OFF(8)))
#define red (*(i8 (*)[4])(frame_ + FRAME_OFF(12)))
#define blue (*(i8 (*)[4])(frame_ + FRAME_OFF(16)))
void __cdecl wnd_obj_set_bg_color(iptr wnd,uint color_index)

{
  HBRUSH pHVar1;
  GamePalette *this;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (*(int *)(wnd + 0x14) != 0) {
    DeleteObject(*(HGDIOBJ *)(wnd + 0x14));
  }
  if (gfx_palettized_display == 0) {
    wnd_view = (WndPaletteView *)GetWindowLongA(*(HWND *)(wnd + 4),0);
    this = (GamePalette *)wnd_get_palette(wnd_view);
    palette_get_entry
              (this,color_index & 0xff,(iptr)red,(iptr)green,(iptr)blue);
    pHVar1 = CreateSolidBrush((uint)CONCAT12(blue[0],CONCAT11(green[0],red[0])));
    *(HBRUSH *)(wnd + 0x14) = pHVar1;
  }
  else {
    if (*(int *)(wnd + 0x18) != 0) {
      RealizePalette(*(HDC *)(wnd + 8));
    }
    pHVar1 = CreateSolidBrush(color_index & 0xff | 0x1000000);
    *(HBRUSH *)(wnd + 0x14) = pHVar1;
  }
  InvalidateRect(*(HWND *)(wnd + 4),(RECT *)0x0,0);
  return;
}
#undef green
#undef wnd_view
#undef red
#undef blue

/* 005bc3bf auto */
void __cdecl wnd_obj_set_bg_tile(iptr wnd,i32 tile)

{
  *(i32 *)(wnd + 0x24) = tile;
  return;
}

/* 005bc3f1 auto */
void __cdecl wnd_obj_set_bg_surface(iptr wnd,i32 surface)

{
  *(i32 *)(wnd + 0x2c) = surface;
  return;
}

/* 005bc40a auto */
void __cdecl wnd_obj_show_raise(iptr wnd)

{
  if (wnd != 0) {
    ShowWindow(*(HWND *)(wnd + 4),5);
    if ((*(byte *)(wnd + 0x49) & 2) != 0) {
      BringWindowToTop(*(HWND *)(wnd + 4));
    }
  }
  return;
}

/* 005bc44d auto */
void __cdecl wnd_obj_hide(iptr wnd)

{
  if (wnd != 0) {
    ShowWindow(*(HWND *)(wnd + 4),0);
  }
  return;
}

/* 005bc4a1 auto */
#define rect (*(tagRECT *)(frame_ + FRAME_OFF(4)))
void __cdecl wnd_obj_move_xy(iptr wnd,int x,int y)

{
  int nHeight;
  int nWidth;
  BOOL bRepaint;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (wnd != 0) {
    GetWindowRect(*(HWND *)(wnd + 4),&rect);
    bRepaint = 1;
    nHeight = rect_height((iptr)&rect);
    nWidth = rect_width((iptr)&rect);
    MoveWindow(*(HWND *)(wnd + 4),x,y,nWidth,nHeight,bRepaint);
  }
  return;
}
#undef rect

/* 005bc505 auto */
#define origin (*(tagPOINT *)(frame_ + FRAME_OFF(0)))
#define parent_hwnd (*(HWND *)(frame_ + FRAME_OFF(8)))
#define rect (*(tagRECT *)(frame_ + FRAME_OFF(12)))
void __cdecl wnd_obj_set_client_size(iptr wnd,int width,int height)

{
  int frame_w;
  int frame_h;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (wnd != 0) {
    GetWindowRect(*(HWND *)(wnd + 4),&rect);
    frame_w = wnd_obj_frame_width(wnd);
    frame_h = wnd_obj_frame_height(wnd);
    parent_hwnd = GetParent(*(HWND *)(wnd + 4));
    if ((parent_hwnd != (HWND)0x0) && ((*(byte *)(wnd + 0x49) & 2) != 0)) {
      origin.x = 0;
      origin.y = 0;
      MapWindowPoints(parent_hwnd,(HWND)0x0,&origin,1);
      rect.left -= origin.x;
      rect.top -= origin.y;
    }
    MoveWindow(*(HWND *)(wnd + 4),rect.left,rect.top,width + frame_w,height + frame_h,1);
  }
  return;
}
#undef origin
#undef parent_hwnd
#undef rect

/* 005bc5da auto */
void __cdecl wnd_obj_maximize(iptr wnd)

{
  if (wnd != 0) {
    ShowWindow(*(HWND *)(wnd + 4),3);
  }
  return;
}

/* 005bc636 auto */
void __cdecl wnd_obj_minimize(iptr wnd)

{
  if (wnd != 0) {
    ShowWindow(*(HWND *)(wnd + 4),6);
  }
  return;
}

/* 005bc692 auto */
void __cdecl wnd_obj_show_restored(iptr wnd)

{
  if (wnd != 0) {
    ShowWindow(*(HWND *)(wnd + 4),9);
  }
  return;
}

/* 005bc6bb auto */
void __cdecl wnd_obj_validate_rect(iptr wnd,RECT *rect)

{
  if (wnd != 0) {
    ValidateRect(*(HWND *)(wnd + 4),rect);
  }
  return;
}

/* 005bc713 auto */
void __cdecl wnd_obj_move_to_rect(iptr wnd,int *rect)

{
  int nHeight;
  int nWidth;
  BOOL bRepaint;
  
  if (wnd != 0) {
    bRepaint = 1;
    nHeight = rect_height((iptr)rect);
    nWidth = rect_width((iptr)rect);
    MoveWindow(*(HWND *)(wnd + 4),*rect,rect[1],nWidth,nHeight,bRepaint);
  }
  return;
}

/* 005bc763 auto */
#define wnd_rect (*(tagRECT *)(frame_ + FRAME_OFF(4)))
#define pos_y2 (*(int *)(frame_ + FRAME_OFF(20)))
#define pos_x2 (*(int *)(frame_ + FRAME_OFF(24)))
#define origin (*(tagPOINT *)(frame_ + FRAME_OFF(28)))
#define parent_rect (*(tagRECT *)(frame_ + FRAME_OFF(36)))
void __cdecl wnd_obj_center(iptr wnd,int offset_x,int offset_y)

{
  HWND hWnd;
  int outer_w;
  int outer_h;
  int wnd_w;
  BOOL bRepaint;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (wnd != 0) {
    GetWindowRect(*(HWND *)(wnd + 4),&wnd_rect);
    hWnd = GetParent(*(HWND *)(wnd + 4));
    if (hWnd == (HWND)0x0) {
      outer_w = GetSystemMetrics(0);
      outer_h = GetSystemMetrics(1);
      wnd_w = rect_width((iptr)&wnd_rect);
      pos_x2 = outer_w - wnd_w >> 1;
      outer_w = rect_height((iptr)&wnd_rect);
      pos_y2 = outer_h - outer_w >> 1;
    }
    else if ((*(byte *)(wnd + 0x49) & 2) == 0) {
      GetWindowRect(hWnd,&parent_rect);
      outer_w = rect_width((iptr)&parent_rect);
      outer_h = rect_height((iptr)&parent_rect);
      wnd_w = rect_width((iptr)&wnd_rect);
      pos_x2 = outer_w - wnd_w >> 1;
      outer_w = rect_height((iptr)&wnd_rect);
      pos_y2 = outer_h - outer_w >> 1;
      origin.x = 0;
      origin.y = 0;
      MapWindowPoints(hWnd,(HWND)0x0,&origin,1);
      pos_x2 += parent_rect.left;
      pos_y2 += parent_rect.top;
    }
    else {
      GetClientRect(hWnd,&parent_rect);
      outer_w = rect_width((iptr)&parent_rect);
      outer_h = rect_height((iptr)&parent_rect);
      wnd_w = rect_width((iptr)&wnd_rect);
      pos_x2 = outer_w - wnd_w >> 1;
      outer_w = rect_height((iptr)&wnd_rect);
      pos_y2 = outer_h - outer_w >> 1;
      if (pos_y2 < 0) {
        pos_y2 = 0;
      }
    }
    bRepaint = 1;
    outer_w = rect_height((iptr)&wnd_rect);
    outer_h = rect_width((iptr)&wnd_rect);
    MoveWindow(*(HWND *)(wnd + 4),pos_x2 + offset_x,pos_y2 + offset_y,outer_h,outer_w,bRepaint);
  }
  return;
}
#undef wnd_rect
#undef pos_y2
#undef pos_x2
#undef origin
#undef parent_rect

/* 005bc933 auto */
#define rect (*(tagRECT *)(frame_ + FRAME_OFF(4)))
LONG __cdecl wnd_obj_client_width(iptr wnd)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (wnd == 0) {
    rect.right = 0;
  }
  else {
    GetClientRect(*(HWND *)(wnd + 4),&rect);
  }
  return rect.right;
}
#undef rect

/* 005bc96b auto */
#define rect (*(tagRECT *)(frame_ + FRAME_OFF(4)))
LONG __cdecl wnd_obj_client_height(iptr wnd)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (wnd == 0) {
    rect.bottom = 0;
  }
  else {
    GetClientRect(*(HWND *)(wnd + 4),&rect);
  }
  return rect.bottom;
}
#undef rect

/* 005bc9a3 auto */
void __cdecl wnd_obj_get_screen_rect(iptr wnd,LPRECT rect)

{
  if (wnd != 0) {
    GetWindowRect(*(HWND *)(wnd + 4),rect);
  }
  return;
}

/* 005bc9d3 auto */
#define rect (*(tagRECT *)(frame_ + FRAME_OFF(4)))
int __cdecl wnd_obj_frame_width(iptr wnd)

{
  int result;
  int client_w;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (wnd == 0) {
    result = 0;
  }
  else {
    GetWindowRect(*(HWND *)(wnd + 4),&rect);
    result = rect_width((iptr)&rect);
    GetClientRect(*(HWND *)(wnd + 4),&rect);
    client_w = rect_width((iptr)&rect);
    result -= client_w;
  }
  return result;
}
#undef rect

/* 005bca3d auto */
#define rect (*(tagRECT *)(frame_ + FRAME_OFF(4)))
int __cdecl wnd_obj_frame_height(iptr wnd)

{
  int result;
  int client_h;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (wnd == 0) {
    result = 0;
  }
  else {
    GetWindowRect(*(HWND *)(wnd + 4),&rect);
    result = rect_height((iptr)&rect);
    GetClientRect(*(HWND *)(wnd + 4),&rect);
    client_h = rect_height((iptr)&rect);
    result -= client_h;
  }
  return result;
}
#undef rect

/* 005bcb85 auto */
#define top_left (*(tagPOINT *)(frame_ + FRAME_OFF(4)))
#define right2 (*(LONG *)(frame_ + FRAME_OFF(12)))
#define bottom2 (*(LONG *)(frame_ + FRAME_OFF(16)))
void __cdecl wnd_obj_get_rect_in_parent(iptr wnd,LPRECT rect)

{
  HWND hWndTo;
  tagPOINT *lpPoints;
  UINT cPoints;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (wnd != 0) {
    GetWindowRect(*(HWND *)(wnd + 4),rect);
    top_left.x = rect->left;
    top_left.y = rect->top;
    right2 = rect->right;
    bottom2 = rect->bottom;
    cPoints = 2;
    lpPoints = &top_left;
    hWndTo = GetParent(*(HWND *)(wnd + 4));
    MapWindowPoints((HWND)0x0,hWndTo,lpPoints,cPoints);
    SetRect(rect,top_left.x,top_left.y,right2,bottom2);
  }
  return;
}
#undef top_left
#undef right2
#undef bottom2

/* 005bcdc3 auto */
void __cdecl wnd_obj_select_palette(iptr wnd,HPALETTE palette)

{
  if (gfx_palettized_display == 1) {
    *(HPALETTE *)(wnd + 0x18) = palette;
    SelectPalette(*(HDC *)(wnd + 8),palette,0);
  }
  return;
}

/* 005bcdfc auto */
void __cdecl wnd_obj_attach_menu(iptr wnd,HMENU menu)

{
  int new_height;
  int menu_height;
  i32 width;
  
  if (wnd != 0) {
    SetMenu(*(HWND *)(wnd + 4),menu);
    new_height = wnd_obj_client_height(wnd);
    menu_height = GetSystemMetrics(0xf);
    new_height = new_height + menu_height + 1;
    width = wnd_obj_client_width(wnd);
    wnd_obj_set_client_size(wnd,width,new_height);
  }
  return;
}

/* 005bce5f auto */
#define app_hinstance (*(HINSTANCE *)((u8 *)&g.d_006e4ff0))
void __cdecl wnd_obj_set_icon(iptr wnd,uint icon_id)

{
  HICON pHVar1;
  BOOL BVar2;
  
  if (wnd != 0) {
    if (*(int *)(wnd + 0x20) != 0) {
      DestroyIcon(*(HICON *)(wnd + 0x20));
    }
    pHVar1 = LoadIconA(app_hinstance,(LPCSTR)(icon_id & 0xffff));
    *(HICON *)(wnd + 0x20) = pHVar1;
    BVar2 = IsWindow(*(HWND *)(wnd + 4));
    if ((BVar2 != 0) && (BVar2 = IsIconic(*(HWND *)(wnd + 4)), BVar2 != 0)) {
      InvalidateRect(*(HWND *)(wnd + 4),(RECT *)0x0,0);
    }
  }
  return;
}
#undef app_hinstance

/* 005bcfdd auto */
void __cdecl wnd_obj_set_cursor_now(iptr wnd,i32 cursor_id,int apply_now)

{
  if ((wnd != 0) && (wnd_obj_set_cursor(wnd,cursor_id), apply_now != 0)) {
    SetCursor(*(HCURSOR *)(wnd + 0x1c));
  }
  return;
}

/* 005bd05f auto */
#define app_hinstance (*(HINSTANCE *)((u8 *)&g.d_006e4ff0))
void __cdecl wnd_obj_set_cursor(iptr wnd,uint cursor_id)

{
  HCURSOR pHVar1;
  
  if (wnd != 0) {
    if ((int)cursor_id < 0) {
      if (cursor_id == 0xffffffff) {
        pHVar1 = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
        *(HCURSOR *)(wnd + 0x1c) = pHVar1;
      }
      else if (cursor_id == 0xfffffffe) {
        pHVar1 = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f02);
        *(HCURSOR *)(wnd + 0x1c) = pHVar1;
      }
    }
    else {
      pHVar1 = LoadCursorA(app_hinstance,(LPCSTR)(cursor_id & 0xffff));
      *(HCURSOR *)(wnd + 0x1c) = pHVar1;
    }
  }
  return;
}
#undef app_hinstance

/* 005bd0e7 auto */
void __cdecl wnd_obj_focus_and_raise(iptr wnd)

{
  if (wnd != 0) {
    SetFocus(*(HWND *)(wnd + 4));
    BringWindowToTop(*(HWND *)(wnd + 4));
  }
  return;
}

/* 005bd120 auto */
void __cdecl wnd_obj_set_focus(iptr wnd)

{
  if (wnd != 0) {
    SetFocus(*(HWND *)(wnd + 4));
  }
  return;
}

/* 005bd14c auto */
void __cdecl wnd_obj_disable_owner(iptr wnd,iptr owner)

{
  HWND pHVar1;
  BOOL BVar2;
  
  if ((owner == 0) && (wnd != 0)) {
    pHVar1 = GetParent(*(HWND *)(wnd + 4));
    BVar2 = IsWindow(pHVar1);
    if (BVar2 != 0) {
      BVar2 = 0;
      pHVar1 = GetParent(*(HWND *)(wnd + 4));
      EnableWindow(pHVar1,BVar2);
    }
  }
  else if (owner != 0) {
    EnableWindow(*(HWND *)(owner + 4),0);
  }
  return;
}

/* 005bd1c5 auto */
void __cdecl wnd_obj_enable_owner(iptr wnd,iptr owner)

{
  HWND pHVar1;
  BOOL BVar2;
  
  if ((owner == 0) && (wnd != 0)) {
    pHVar1 = GetParent(*(HWND *)(wnd + 4));
    BVar2 = IsWindow(pHVar1);
    if (BVar2 != 0) {
      BVar2 = 1;
      pHVar1 = GetParent(*(HWND *)(wnd + 4));
      EnableWindow(pHVar1,BVar2);
    }
  }
  else if (owner != 0) {
    EnableWindow(*(HWND *)(owner + 4),1);
  }
  return;
}

/* 005bd248 auto */
void __cdecl wnd_obj_set_caption_height(iptr wnd,i32 height)

{
  if (wnd != 0) {
    *(i32 *)(wnd + 0x38) = height;
  }
  return;
}

/* 005bd270 auto */
void __cdecl wnd_obj_set_resize_border(iptr wnd,i32 border)

{
  if (wnd != 0) {
    *(i32 *)(wnd + 0x3c) = border;
  }
  return;
}

/* 005bd48f auto */
#define pt (*(tagPOINT *)(frame_ + FRAME_OFF(4)))
void __cdecl wnd_obj_get_cursor_pos(iptr wnd,LONG *out_x,LONG *out_y)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  GetCursorPos(&pt);
  ScreenToClient(*(HWND *)(wnd + 4),&pt);
  *out_x = pt.x;
  *out_y = pt.y;
  return;
}
#undef pt

/* 005bd533 auto */
void __cdecl wnd_obj_set_capture(iptr wnd)

{
  SetCapture(*(HWND *)(wnd + 4));
  return;
}

/* 005bd550 auto */
void __cdecl wnd_obj_release_capture(i32 wnd)

{
  ReleaseCapture();
  return;
}

/* 005bd566: written by hand in src/game/retvals.c */

/* 005bd610 auto */
i16 __thiscall wnd_get_style_flags(WndStyleView *this)

{
  return (short)this->style_flags;
}

/* 005c5760 auto */
void __thiscall
wnd_create_framed
          (WndBase *this,iptr title,i32 style,i32 x,i32 y
          ,i32 width,i32 height,iptr palette)

{
  iptr hwnd;
  
  wnd_create_with_cmd_proc(this,title,style,x,y,width,height,palette);
  hwnd = wnd_get_window(this);
  wnd_install_frame_proc((iptr)this,hwnd);
  return;
}

/* 005c57f9 auto */
void __thiscall
wnd_create_framed_child
          (WndBase *this,iptr title,i32 style,i32 x,i32 y
          ,i32 width,i32 height,iptr palette,iptr parent)

{
  iptr hwnd;
  
  wnd_create_with_handlers(this,title,style,x,y,width,height,palette,parent);
  hwnd = wnd_get_window(this);
  wnd_install_frame_proc((iptr)this,hwnd);
  return;
}

/* 005c59c4 auto */
#define last (*(uptr *)(frame_ + FRAME_OFF(0)))
void __thiscall wnd_append_control(WndControlListView *this,iptr ctrl)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  last = this->first_control;
  if (last == 0) {
    this->first_control = ctrl;
  }
  else {
    for (; *(int *)(last + 0x20) != 0; last = *(uptr *)(last + 0x20)) {
    }
    *(iptr *)(last + 0x20) = ctrl;
  }
  return;
}
#undef last

/* 005c5a27 auto */
#define ctrl (*(ControlNextView * *)(frame_ + FRAME_OFF(0)))
void __thiscall wnd_remove_control(WndControlRemoveView *this,int ctrl_id)

{
  int id;
  ControlIdView *this_00;
  ControlNextView *this_01;
  u32 next_next;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (this->first_control != 0) {
    ctrl = (ControlNextView *)this->first_control;
    id = ctrl_get_id((ControlIdView *)ctrl);
    if (id == ctrl_id) {
      this->first_control = ctrl->next_control;
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
#undef ctrl

/* 005c5aeb auto */
#define ctrl (*(ControlIdView * *)(frame_ + FRAME_OFF(0)))
void __thiscall wnd_remove_all_controls(WndControlRemoveView *this)

{
  i32 ctrl_id;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (ctrl = (ControlIdView *)this->first_control; ctrl != (ControlIdView *)0x0;
      ctrl = *(ControlIdView **)((ControlIdViewExt *)ctrl)->next_control) {
    ctrl_id = ctrl_get_id(ctrl);
    wnd_remove_control(this,ctrl_id);
  }
  return;
}
#undef ctrl

/* 005c5b7f auto */
#define ctrl (*(ControlInitialFocusView * *)(frame_ + FRAME_OFF(0)))
void __thiscall wnd_focus_first_control(Wnd *this)

{
  char wants_focus;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  ctrl = (ControlInitialFocusView *)this->control_list;
  while( true ) {
    if (ctrl == (ControlInitialFocusView *)0x0) {
      if ((this->control_list != 0) && ((char)this->keyboard_nav != '\0')) {
        wnd_focus_control((iptr)this,this->control_list);
      }
      return;
    }
    wants_focus = ctrl_get_initial_focus(ctrl);
    if (wants_focus != '\0') break;
    ctrl = (ControlInitialFocusView *)control_get_next((ControlNextView *)ctrl);
  }
  if ((char)this->keyboard_nav == '\0') {
    return;
  }
  wnd_focus_control((iptr)this,(iptr)ctrl);
  return;
}
#undef ctrl

/* 005c5c86 auto */
#define i (*(int *)(frame_ + FRAME_OFF(0)))
#define handled (*(i32 *)(frame_ + FRAME_OFF(12)))
#define ctrl (*(RadioGroupItemsView * *)(frame_ + FRAME_OFF(16)))
#define key_str (*(u8 (*)[4])(frame_ + FRAME_OFF(20)))
#define done (*(char *)(frame_ + FRAME_OFF(24)))
i32 __thiscall wnd_dispatch_hotkey_char(void *this,i32 ch)

{
  u8 key;
  iptr ctrl_type;
  iptr enabled;
  i32 hwnd;
  int value;
  int item_count;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  done = '\0';
  handled = 0;
  key_str[0] = (u8)ch;
  key_str[1] = 0;
  __strlwr((char *)key_str);
  key = key_str[0];
  ctrl = *(RadioGroupItemsView **)((int)this + 0xb8);
  do {
    if (ctrl == (RadioGroupItemsView *)0x0) {
      return handled;
    }
    if (done != '\0') {
      return handled;
    }
    if (*(int *)(ctrl->hotkey_index) < 0) {
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
    ctrl = *(RadioGroupItemsView **)(ctrl->next_control);
  } while( true );
}
#undef i
#undef handled
#undef ctrl
#undef key_str
#undef done

/* 005c5f20 auto */
void __thiscall
wnd_create_with_cmd_proc
          (WndBase *this,iptr title,i32 style,i32 x,i32 y
          ,i32 width,i32 height,iptr palette)

{
  iptr hwnd;
  
  wnd_record_create(this,title,style,x,y,width,height,palette);
  hwnd = wnd_get_window(this);
  wnd_install_command_proc((iptr)this,hwnd);
  wnd_clear_handlers((WndHandlers *)(this + 1));
  return;
}

/* 005c5fc4 auto */
void __thiscall
wnd_create_with_handlers
          (WndBase *this,iptr title,i32 style,i32 x,i32 y
          ,i32 width,i32 height,iptr palette,iptr parent)

{
  iptr hwnd;
  
  wnd_record_create_child(this,title,style,x,y,width,height,palette,parent);
  hwnd = wnd_get_window(this);
  wnd_install_command_proc((iptr)this,hwnd);
  wnd_clear_handlers((WndHandlers *)(this + 1));
  return;
}

/* 005c61b0 auto */
#define owner_after (*(iptr *)(frame_ + FRAME_OFF(4)))
#define owner2 (*(iptr *)(frame_ + FRAME_OFF(8)))
void __thiscall wnd_run_modal_loop(ModalMenuWindow *this)

{
  iptr wnd;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (wnd_modal_depth != 0xf) {
    this->modal_running = 1;
    wnd_modal_depth++;
    (&wnd_modal_stack)[wnd_modal_depth] = this;
    if (wnd_modal_depth == 0) {
      owner2 = 0;
    }
    else {
      owner2 = wnd_get_window((WndBase *)(&wnd_modal_stack_below)[wnd_modal_depth]);
    }
    wnd = wnd_get_window((WndBase *)this);
    wnd_obj_disable_owner(wnd,owner2);
    while (this->modal_running != 0) {
      win_pump_one_message();
      if (this->on_modal_idle != 0) {
        (*(code *)this->on_modal_idle)();
      }
    }
    if (wnd_modal_depth == 0) {
      owner_after = 0;
    }
    else {
      owner_after = wnd_get_window((WndBase *)(&wnd_modal_stack_below)[wnd_modal_depth]);
    }
    wnd = wnd_get_window((WndBase *)this);
    wnd_obj_enable_owner(wnd,owner_after);
    wnd_modal_depth--;
    if (-1 < wnd_modal_depth) {
      this->modal_running = 1;
    }
  }
  return;
}
#undef owner_after
#undef owner2

/* 005c62cb auto */
/* Library Function - Single Match
    public: void __thiscall CRichEditDoc::InvalidateObjectCache(void)
   
   Library: Visual Studio 1998 Debug */

void __thiscall wnd_end_modal_loop(ModalMenuWindow *this)

{
  this->modal_running = 0;
  return;
}

/* 005c62ee auto */
#define wnd_active_child (*(i32 *)((u8 *)&g.d_00637ea4))
i32 __cdecl wnd_get_active_child(void)

{
  return wnd_active_child;
}
#undef wnd_active_child

/* 005c6303 auto */
#define wnd_active_child (*(iptr *)((u8 *)&g.d_00637ea4))
i32 __cdecl wnd_set_active_child(iptr child)

{
  i32 prev;
  
  prev = wnd_active_child;
  wnd_active_child = child;
  return prev;
}
#undef wnd_active_child

/* 005c63af auto */
bool __thiscall wnd_fire_menu_select(WndMenuSelectView *this,i32 item_id)

{
  bool has_handler;
  
  has_handler = this->on_menu_select != 0;
  if (has_handler) {
    (*(code *)this->on_menu_select)(item_id);
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
#define app_hinstance (*(HINSTANCE *)((u8 *)&g.d_006e4ff0))
HWND __cdecl hotspot_create_hwnd(int *rect,iptr ctrl)

{
  WndBase *this;
  iptr parent_wnd;
  iptr height;
  int width;
  HWND pHVar4;
  HMENU hMenu;
  HINSTANCE hInstance;
  LPVOID lpParam;
  
  lpParam = (LPVOID)0x0;
  hMenu = (HMENU)0x0;
  hInstance = app_hinstance;
  this = (WndBase *)ctrl_get_parent((Control *)ctrl);
  parent_wnd = wnd_get_window(this);
  pHVar4 = *(HWND *)(parent_wnd + 4);
  height = rect_height((iptr)rect);
  width = rect_width((iptr)rect);
  pHVar4 = CreateWindowExA(4,s_MSControlClass_00637ca8,&hotspot_wnd_title,0x50000000,*rect,rect[1],
                           width,height,pHVar4,hMenu,hInstance,lpParam);
  width = ctrl_init_block(pHVar4,ctrl);
  *(i32 *)(width + 0x2c) = 1;
  SetWindowLongA(pHVar4,-4,(iptr)hotspot_wndproc);
  return pHVar4;
}
#undef app_hinstance

/* 005c8f70 auto */
void __thiscall hotspot_fire_enter(HotspotEnterView *this,i32 arg)

{
  if (this->on_enter != 0) {
    (*(code *)this->on_enter)(arg);
  }
  return;
}

/* 005c8fb0 auto */
void __thiscall hotspot_fire_leave(HotspotLeaveView *this,i32 event_arg)

{
  if (this->on_leave != 0) {
    (*(code *)this->on_leave)(event_arg);
  }
  return;
}

/* 005c8ff0 auto */
void __thiscall hotspot_fire_click(HotspotClickView *this,i32 event_arg)

{
  if (this->on_click != 0) {
    (*(code *)this->on_click)(event_arg);
  }
  return;
}

/* 005c9030 auto */
void __thiscall hotspot_fire_press(HotspotPressView *this,i32 event_arg)

{
  if (this->on_press != 0) {
    (*(code *)this->on_press)(event_arg);
  }
  return;
}

/* 005c9070 auto */
void __thiscall hotspot_fire_dblclick(HotspotDblClickView *this,i32 event_arg)

{
  if (this->on_dblclick != 0) {
    (*(code *)this->on_dblclick)(event_arg);
  }
  return;
}

/* 005c9563 auto */
LONG __cdecl wnd_from_hwnd(HWND hwnd)

{
  LONG LVar1;
  
  if (hwnd == (HWND)0x0) {
    LVar1 = 0;
  }
  else {
    LVar1 = GetWindowLongA(hwnd,0);
  }
  return LVar1;
}

/* 005c96cc auto */
#define client_rect2 (*(tagRECT *)(frame_ + FRAME_OFF(4)))
void __cdecl wnd_redraw_client(HWND hwnd)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  GetClientRect(hwnd,&client_rect2);
  InvalidateRect(hwnd,&client_rect2,1);
  UpdateWindow(hwnd);
  return;
}
#undef client_rect2

/* 005cbdd0 auto */
u8 __thiscall wnd_keyboard_nav_enabled(WndKeyNavView *this)

{
  return this->keyboard_nav;
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
  font_init_empty((GameFont *)&default_draw_font_obj);
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
  font_destroy((GameFont *)&default_draw_font_obj);
  return;
}

/* 005d2550 auto */
#define ctrl_text_color_index (*(i8 *)((u8 *)&g.d_00637e90))
void __cdecl ui_set_ctrl_text_color(i32 color_index)

{
  ctrl_text_color_index = (i8)color_index;
  return;
}
#undef ctrl_text_color_index

/* 005d2568 auto */
#define ctrl_shadow_color_index (*(i8 *)((u8 *)&g.d_00637e94))
#define ctrl_shadow_dx (*(i8 *)((u8 *)&g.d_00637e98))
#define ctrl_shadow_dy (*(i8 *)((u8 *)&g.d_00637e9c))
void __cdecl ui_set_ctrl_text_shadow(i32 color_index,i32 dx,i32 dy)

{
  ctrl_shadow_color_index = (i8)color_index;
  ctrl_shadow_dx = (i8)dx;
  ctrl_shadow_dy = (i8)dy;
  return;
}
#undef ctrl_shadow_color_index
#undef ctrl_shadow_dx
#undef ctrl_shadow_dy

/* 005d2590 auto */
#define ctrl_disabled_color_index (*(i8 *)((u8 *)&g.d_00637ea0))
void __cdecl ui_set_ctrl_disabled_color(i32 color_index)

{
  ctrl_disabled_color_index = (i8)color_index;
  return;
}
#undef ctrl_disabled_color_index

/* 005d25a8 auto */
void __cdecl ui_set_ctrl_font(iptr font)

{
  checkbox_default_font = (i8 *)font;
  return;
}

/* 005d268e auto */
void __cdecl ui_set_default_font(iptr font)

{
  ctrl_default_font = (i8 *)font;
  return;
}

/* 005d2d4d auto */
void __cdecl hwnd_get_text(HWND hwnd,LPARAM buffer)

{
  LRESULT LVar1;
  
  LVar1 = SendMessageA(hwnd,0xe,0,0);
  SendMessageA(hwnd,0xd,LVar1 + 1,buffer);
  return;
}

/* 005d2d7f auto */
void __cdecl hwnd_send_settext(HWND hwnd,LPARAM text)

{
  SendMessageA(hwnd,0xc,0,text);
  return;
}

/* 005d417f auto */
#define radio_text_color_index (*(i8 *)((u8 *)&g.d_00637e7c))
void __cdecl ui_set_radio_text_color(i32 color_index)

{
  radio_text_color_index = (i8)color_index;
  return;
}
#undef radio_text_color_index

/* 005d4197 auto */
#define radio_disabled_color_index (*(i8 *)((u8 *)&g.d_00637e8c))
void __cdecl ui_set_radio_disabled_color(i32 color_index)

{
  radio_disabled_color_index = (i8)color_index;
  return;
}
#undef radio_disabled_color_index

/* 005d41af auto */
#define radio_shadow_color_index (*(i8 *)((u8 *)&g.d_00637e80))
#define radio_shadow_dx (*(i8 *)((u8 *)&g.d_00637e84))
#define radio_shadow_dy (*(i8 *)((u8 *)&g.d_00637e88))
void __cdecl ui_set_radio_text_shadow(i32 color_index,i32 dx,i32 dy)

{
  radio_shadow_color_index = (i8)color_index;
  radio_shadow_dx = (i8)dx;
  radio_shadow_dy = (i8)dy;
  return;
}
#undef radio_shadow_color_index
#undef radio_shadow_dx
#undef radio_shadow_dy

/* 005d8236 auto */
void __cdecl ui_set_button_font(iptr font)

{
  button_default_font = (i8 *)font;
  return;
}

/* 005db610 auto */
WndBase * __thiscall wnd_record_init(WndBase *this)

{
  this->native_wnd = 0;
  this->wnd_palette = 0;
  this->wnd_record = 0;
  this->style = 0;
  return this;
}

/* 005db650 auto */
void __thiscall wnd_record_destroy(WndDestroyView *this)

{
  u32 destroyed_obj;
  
  destroyed_obj = wnd_obj_destroy(this->wnd_obj);
  this->wnd_obj = destroyed_obj;
  return;
}

/* 005db67b auto */
void __thiscall
wnd_record_create
          (WndBase *this,i32 wnd_kind,u32 style,i32 x,i32 y,
          i32 width,i32 height,iptr palette)

{
  u32 native;
  
  this->style = style;
  if (this->native_wnd != 0) {
    native = wnd_obj_destroy(this->native_wnd);
    this->native_wnd = native;
  }
  native = wnd_obj_create(wnd_kind,style,x,y,width,height,0);
  this->native_wnd = native;
  wnd_set_owner_ptr((iptr)this,this->native_wnd);
  wnd_set_palette(this,palette);
  return;
}

/* 005db893 auto */
void __thiscall
wnd_record_create_child
          (WndBase *this,i32 wnd_kind,u32 style,i32 x,i32 y,
          i32 width,i32 height,iptr palette,WndBase *parent)

{
  u32 native;
  iptr parent_wnd;
  
  this->style = style;
  if (this->native_wnd != 0) {
    native = wnd_obj_destroy(this->native_wnd);
    this->native_wnd = native;
  }
  parent_wnd = wnd_get_window(parent);
  native = wnd_obj_create(wnd_kind,style,x,y,width,height,parent_wnd);
  this->native_wnd = native;
  wnd_set_owner_ptr((iptr)this,this->native_wnd);
  wnd_set_palette(this,palette);
  return;
}

/* 005dba95 auto */
i32 __thiscall wnd_is_shift_down(void *this)

{
  i32 is_down;
  
  is_down = input_poll_modifier(0x100);
  return is_down;
}

/* 005dbab8 auto */
i32 __thiscall wnd_is_ctrl_down(void *this)

{
  i32 is_down;
  
  is_down = input_poll_modifier(0x200);
  return is_down;
}

/* 005dcc10 auto */
GameMenu * __thiscall menu_handle_ctor(GameMenu *this)

{
  this->hmenu = 0;
  return this;
}

/* 005dcc32 auto */
/* Library Function - Single Match
    public: __thiscall _Timevec::~_Timevec(void)
   
   Library: Visual Studio 1998 Debug */

void __thiscall menu_handle_dtor(GameMenu *this)

{
  menu_hmenu_destroy(this->hmenu);
  return;
}

/* 005e00bb auto */
#define choice_dlg_window (*(int *)((u8 *)&g.d_006e5020))
void __cdecl dlg_radio_choice_button_cb(int button_id)

{
  if (button_id == 0x65) {
    wnd_end_modal_loop((ModalMenuWindow *)(choice_dlg_window + 0x48));
  }
  else if (button_id == 0x66) {
    choice_dlg_selection = 0xffffffff;
    wnd_end_modal_loop((ModalMenuWindow *)(choice_dlg_window + 0x48));
  }
  return;
}
#undef choice_dlg_window

/* 005e0863: written by hand in src/game/unwind.c */

/* 005e0ce0 auto */
#define menu_next_item_id (*(HMENU *)((u8 *)&g.d_00638d9c))
#define item_count2 (*(int *)(frame_ + FRAME_OFF(4)))
#define item_id (*(HMENU *)(frame_ + FRAME_OFF(12)))
#define flags2 (*(uint *)(frame_ + FRAME_OFF(16)))
#define label_len (*(size_t *)(frame_ + FRAME_OFF(20)))
iptr __cdecl menu_hmenu_parse_items(HMENU hmenu,iptr spec)

{
  bool done;
  iptr _Source;
  size_t uBytes;
  HLOCAL hMem;
  char *_Dest;
  int cmp;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  done = false;
  item_count2 = 0;
  uBytes = _strlen((char *)spec);
  hMem = LocalAlloc(2,uBytes);
  _Dest = LocalLock(hMem);
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
    cmp = _strcmp(_Dest,&menu_separator_tag);
    if (cmp == 0) {
      flags2 = 0x800;
      *_Dest = '\0';
      item_id = (HMENU)0x0;
    }
    AppendMenuA(hmenu,flags2,(UINT_PTR)item_id,_Dest);
    *_Dest = '\0';
  }
  LocalUnlock(hMem);
  LocalFree(hMem);
  return spec;
}
#undef menu_next_item_id
#undef item_count2
#undef item_id
#undef flags2
#undef label_len

/* 005e0f2a auto */
#define menu_next_item_id (*(int *)((u8 *)&g.d_00638d9c))
#define label_len (*(size_t *)(frame_ + FRAME_OFF(0)))
#define cursor (*(char * *)(frame_ + FRAME_OFF(20)))
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
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  cursor = spec;
  hMenu = CreateMenu();
  base_item_id = menu_next_item_id;
  uBytes = _strlen(spec);
  hMem = LocalAlloc(2,uBytes);
  _Dest = LocalLock(hMem);
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
      AppendMenuA(hMenu,0x10,(UINT_PTR)uIDNewItem,_Dest);
    }
    else {
      AppendMenuA(hMenu,0x13,(UINT_PTR)uIDNewItem,_Dest);
    }
    *_Dest = '\0';
  }
  menu_next_item_id = base_item_id + 100;
  LocalUnlock(hMem);
  LocalFree(hMem);
  return hMenu;
}
#undef menu_next_item_id
#undef label_len
#undef cursor

/* 005e10c7 auto */
void __cdecl menu_hmenu_destroy(HMENU hmenu)

{
  if (hmenu != (HMENU)0x0) {
    DestroyMenu(hmenu);
  }
  return;
}

/* 005e10fb auto */
void __cdecl menu_redraw_bar(iptr wnd)

{
  DrawMenuBar(*(HWND *)(wnd + 4));
  return;
}

/* 005e1118 auto */
BOOL __cdecl menu_hmenu_enable_item(HMENU hmenu,int menu_pos,int item_pos,i32 enable)

{
  BOOL BVar1;
  HMENU hMenu;
  
  if (item_pos == 0) {
    if ((char)enable == '\0') {
      BVar1 = EnableMenuItem(hmenu,menu_pos - 1,0x403);
    }
    else {
      BVar1 = EnableMenuItem(hmenu,menu_pos - 1,0x400);
    }
  }
  else {
    hMenu = GetSubMenu(hmenu,menu_pos - 1);
    if ((char)enable == '\0') {
      BVar1 = EnableMenuItem(hMenu,item_pos - 1,0x403);
    }
    else {
      BVar1 = EnableMenuItem(hMenu,item_pos - 1,0x400);
    }
  }
  return BVar1;
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
#define menu_next_item_id (*(UINT_PTR *)((u8 *)&g.d_00638d9c))
#define item_count2 (*(int *)(frame_ + FRAME_OFF(4)))
#define flags2 (*(uint *)(frame_ + FRAME_OFF(8)))
void __cdecl menu_hmenu_insert_item(HMENU hmenu,int menu_pos,int item_pos,LPCSTR text)

{
  UINT_PTR uIDNewItem;
  HMENU pHVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (hmenu != (HMENU)0x0) {
    pHVar1 = GetSubMenu(hmenu,menu_pos - 1);
    item_count2 = 0;
    if (((pHVar1 != (HMENU)0x0) && (item_pos != -1)) && (menu_pos != -1)) {
      item_count2 = GetMenuItemCount(pHVar1);
    }
    uIDNewItem = menu_next_item_id;
    if ((item_count2 % 0x16 == 0) && (item_count2 != 0)) {
      flags2 = 0x440;
    }
    else {
      flags2 = 0x400;
    }
    if (item_pos == -1) {
      pHVar1 = CreatePopupMenu();
      if (menu_pos == -1) {
        AppendMenuA(hmenu,flags2 | 0x10,(UINT_PTR)pHVar1,text);
      }
      else {
        InsertMenuA(hmenu,menu_pos - 1,flags2 | 0x10,(UINT_PTR)pHVar1,text);
      }
    }
    else {
      menu_next_item_id++;
      InsertMenuA(pHVar1,item_pos - 1,flags2,uIDNewItem,text);
    }
  }
  return;
}
#undef menu_next_item_id
#undef item_count2
#undef flags2

/* 005e14c8 auto */
void __cdecl menu_hmenu_set_item_text(HMENU hmenu,int menu_pos,int item_pos,LPCSTR text)

{
  HMENU hMenu;
  UINT uIDNewItem;
  
  if (hmenu != (HMENU)0x0) {
    hMenu = GetSubMenu(hmenu,menu_pos - 1);
    if (item_pos == -1) {
      ModifyMenuA(hmenu,menu_pos - 1,0x410,(UINT_PTR)hMenu,text);
    }
    else {
      uIDNewItem = GetMenuItemID(hMenu,item_pos - 1);
      ModifyMenuA(hMenu,item_pos - 1,0x400,uIDNewItem,text);
    }
  }
  return;
}

/* 005e1880 auto */
void __cdecl wnd_install_paint_proc(iptr surface,iptr wnd)

{
  SetWindowLongA(*(HWND *)(wnd + 4),0xc,surface);
  SetWindowLongA(*(HWND *)(wnd + 4),-4,(iptr)surfwnd_subclass_wndproc);
  return;
}

/* 005e18ff auto */
#define wnd_active_child (*(u8 * *)((u8 *)&g.d_00637ea4))
#define owner_ptr (*(u8 * *)(frame_ + FRAME_OFF(4)))
#define ps (*(tagPAINTSTRUCT *)(frame_ + FRAME_OFF(16)))
#define hdc (*(HDC *)(frame_ + FRAME_OFF(80)))
#define dest_rect (*(tagRECT *)(frame_ + FRAME_OFF(84)))
#define paint_left (*(LONG *)(frame_ + FRAME_OFF(100)))
#define paint_top (*(LONG *)(frame_ + FRAME_OFF(104)))
#define paint_right (*(LONG *)(frame_ + FRAME_OFF(108)))
#define paint_bottom (*(LONG *)(frame_ + FRAME_OFF(112)))
i32 __stdcall surfwnd_subclass_wndproc(HWND hwnd,int msg,i32 wparam,uint lparam)

{
  SurfaceWindow *this;
  i32 result;
  BOOL BVar2;
  iptr owner_wnd;
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
  i8 frame_[FRAME_OFF(120)] __attribute__((aligned(8)));  /* original stack frame */
  
  this = (SurfaceWindow *)GetWindowLongA(hwnd,0xc);
  if (this == (SurfaceWindow *)0x0) {
    result = wnd_frame_wndproc(hwnd,msg,wparam,lparam);
  }
  else if (msg == 2) {
    surface_create((DibSurface *)this,0,0);
    SetWindowLongA(hwnd,0xc,0);
    result = wnd_frame_wndproc(hwnd,2,wparam,lparam);
  }
  else if (msg == 5) {
    if (this == (SurfaceWindow *)0x0) {
      wnd_active_child = (u8 *)0x0;
    }
    else {
      wnd_active_child = this->window_2;
    }
    BVar2 = IsIconic(hwnd);
    if (BVar2 == 0) {
      surfwnd_on_resize(this,lparam & 0xffff,lparam >> 0x10);
    }
    result = wnd_frame_wndproc(hwnd,5,wparam,lparam);
  }
  else if (msg == 0xf) {
    BVar2 = IsIconic(hwnd);
    if (BVar2 == 0) {
      BVar2 = IsWindowVisible(hwnd);
      if (BVar2 != 0) {
        BeginPaint(hwnd,&ps);
        paint_left = ps.rcPaint.left;
        paint_top = ps.rcPaint.top;
        paint_right = ps.rcPaint.right;
        paint_bottom = ps.rcPaint.bottom;
        if (this == (SurfaceWindow *)0x0) {
          owner_ptr = (u8 *)0x0;
        }
        else {
          owner_ptr = this->window_2;
        }
        surface_blit_to_wnd
                  ((DibSurface *)this,(iptr)owner_ptr,(iptr)&paint_left,(iptr)&paint_left);
        EndPaint(hwnd,&ps);
      }
    }
    else {
      owner_wnd = wnd_get_window((WndBase *)this->window_2);
      if (*(int *)(owner_wnd + 0x20) != 0) {
        result = wnd_base_wndproc(hwnd,0xf,wparam,lparam);
        return result;
      }
      hdc = BeginPaint(hwnd,&ps);
      paint_left = ps.rcPaint.left;
      paint_top = ps.rcPaint.top;
      paint_right = ps.rcPaint.right;
      paint_bottom = ps.rcPaint.bottom;
      SetRect(&dest_rect,0,0,0,0);
      surf_width = surface_get_width((DibSurface *)this);
      src_dim = surface_get_height((DibSurface *)this);
      if (surf_width < src_dim) {
        src_dim = surface_get_width((DibSurface *)this);
        dim_b = rect_width((iptr)&paint_left);
        dest_rect.right = surface_get_height((DibSurface *)this);
        dest_rect.right = (src_dim * dim_b) / dest_rect.right;
        dest_rect.bottom = rect_height((iptr)&paint_left);
      }
      else {
        dest_rect.right = rect_width((iptr)&paint_left);
        src_dim = surface_get_height((DibSurface *)this);
        dim_b = rect_height((iptr)&paint_left);
        dest_rect.bottom = surface_get_width((DibSurface *)this);
        dest_rect.bottom = (src_dim * dim_b) / dest_rect.bottom;
      }
      src_dim = surface_get_dib((DibSurface *)this);
      hdcSrc = *(HDC *)(src_dim + 4);
      rop = 0xcc0020;
      src_dim = surface_get_height((DibSurface *)this);
      dim_b = surface_get_width((DibSurface *)this);
      ySrc = 0;
      xSrc = 0;
      wDest = dest_rect.right;
      hDest = dest_rect.bottom;
      paint_extent = rect_height((iptr)&paint_left);
      dest_extent = rect_height((iptr)&dest_rect);
      yDest = paint_extent - dest_extent >> 1;
      paint_extent = rect_width((iptr)&paint_left);
      dest_extent = rect_width((iptr)&dest_rect);
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
#undef wnd_active_child
#undef owner_ptr
#undef ps
#undef hdc
#undef dest_rect
#undef paint_left
#undef paint_top
#undef paint_right
#undef paint_bottom

/* 005ea7a0 auto */
void __cdecl wnd_install_frame_proc(iptr owner,iptr wnd)

{
  SetWindowLongA(*(HWND *)(wnd + 4),8,owner);
  SetWindowLongA(*(HWND *)(wnd + 4),-4,(iptr)wnd_frame_wndproc);
  return;
}

/* 005ea825 auto */
HWND __cdecl hwnd_next_sibling_wrap(HWND hwnd)

{
  BOOL BVar1;
  HWND pHVar2;
  
  BVar1 = IsWindow(hwnd);
  if (BVar1 == 0) {
    pHVar2 = (HWND)0x0;
  }
  else {
    pHVar2 = GetWindow(hwnd,2);
    if (pHVar2 == (HWND)0x0) {
      pHVar2 = GetWindow(hwnd,0);
    }
  }
  return pHVar2;
}

/* 005ea87c auto */
HWND __cdecl hwnd_prev_sibling_wrap(HWND hwnd)

{
  BOOL BVar1;
  HWND pHVar2;
  
  BVar1 = IsWindow(hwnd);
  if (BVar1 == 0) {
    pHVar2 = (HWND)0x0;
  }
  else {
    pHVar2 = GetWindow(hwnd,3);
    if (pHVar2 == (HWND)0x0) {
      pHVar2 = GetWindow(hwnd,1);
    }
  }
  return pHVar2;
}

/* 005ea8d3 auto */
#define group_hwnd (*(HWND *)(frame_ + FRAME_OFF(0)))
void __cdecl wnd_cycle_control_focus(iptr wnd,HWND hwnd,int direction)

{
  iptr frame_win;
  BOOL BVar1;
  iptr frame_win2;
  HWND pHVar2;
  int result;
  CheckboxEnabledView *this;
  UINT UVar4;
  UINT uCmd;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (hwnd == (HWND)0x0) {
    hwnd = GetFocus();
    pHVar2 = hwnd;
    frame_win = wnd_get_window((WndBase *)wnd);
    BVar1 = IsChild(*(HWND *)(frame_win + 4),pHVar2);
    if (BVar1 == 0) {
      hwnd = (HWND)0x0;
    }
  }
  if (hwnd == (HWND)0x0) {
    if (*(int *)(wnd + 0xb8) == 0) {
      return;
    }
    if (direction == 2) {
      UVar4 = 5;
      frame_win2 = wnd_get_window((WndBase *)wnd);
      hwnd = GetWindow(*(HWND *)(frame_win2 + 4),UVar4);
      pHVar2 = hwnd;
    }
    else {
      uCmd = 1;
      UVar4 = 5;
      result = wnd_get_window((WndBase *)wnd);
      pHVar2 = GetWindow(*(HWND *)(result + 4),UVar4);
      hwnd = GetWindow(pHVar2,uCmd);
      pHVar2 = hwnd;
    }
  }
  else if (direction == 2) {
    hwnd = (HWND)hwnd_next_sibling_wrap(hwnd);
    pHVar2 = hwnd;
  }
  else {
    hwnd = (HWND)hwnd_prev_sibling_wrap(hwnd);
    pHVar2 = hwnd;
  }
  do {
    BVar1 = IsWindow(hwnd);
    if (BVar1 == 0) {
      return;
    }
    BVar1 = IsWindowVisible(hwnd);
    if (BVar1 == 0) {
      if (direction == 2) {
        hwnd = (HWND)hwnd_next_sibling_wrap(hwnd);
      }
      else {
        hwnd = (HWND)hwnd_prev_sibling_wrap(hwnd);
      }
    }
    else {
      result = ctrl_hwnd_is_radio(hwnd);
      if (result != 0) {
        group_hwnd = hwnd;
        while( true ) {
          BVar1 = IsWindow(hwnd);
          if (BVar1 == 0) {
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
            hwnd = (HWND)hwnd_next_sibling_wrap(hwnd);
          }
          else {
            hwnd = (HWND)hwnd_prev_sibling_wrap(hwnd);
          }
        }
        wnd_cycle_control_focus(wnd,group_hwnd,direction);
        return;
      }
      this = (CheckboxEnabledView *)ctrl_list_find_by_hwnd(hwnd,*(i32 *)(wnd + 0xb8));
      if ((this != (CheckboxEnabledView *)0x0) &&
         ((((result = control_get_type((ControlTypeView *)this), result == 6 &&
            (result = ctrl_is_enabled((ControlEnabledView *)this), result != 0)) ||
           ((result = control_get_type((ControlTypeView *)this), result == 2 &&
            (result = checkbox_is_enabled(this), result != 0)))) ||
          (((result = control_get_type((ControlTypeView *)this), result == 4 ||
            (result = control_get_type((ControlTypeView *)this), result == 7)) ||
           (result = control_get_type((ControlTypeView *)this), result == 10)))))) {
        SetFocus(hwnd);
        return;
      }
      if (direction == 2) {
        hwnd = (HWND)hwnd_next_sibling_wrap(hwnd);
      }
      else {
        hwnd = (HWND)hwnd_prev_sibling_wrap(hwnd);
      }
    }
    if (hwnd == pHVar2) {
      return;
    }
  } while( true );
}
#undef group_hwnd

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
void __cdecl wnd_set_owner_ptr(iptr owner,iptr wnd)

{
  SetWindowLongA(*(HWND *)(wnd + 4),0,owner);
  return;
}

/* 005eb393 auto */
void __cdecl wnd_install_command_proc(iptr owner,iptr wnd)

{
  SetWindowLongA(*(HWND *)(wnd + 4),4,owner);
  SetWindowLongA(*(HWND *)(wnd + 4),-4,(iptr)wnd_child_wndproc);
  return;
}

/* 005ec1a1 auto */
#define menu_search_pos (*(i32 *)((u8 *)&g.d_006e5368))
void __cdecl wnd_on_menu_command(HWND hwnd,i32 cmd_id)

{
  char handled;
  WndOnCommandView *this;
  HMENU pHVar2;
  uint pos;
  
  this = (WndOnCommandView *)GetWindowLongA(hwnd,4);
  handled = wnd_call_command(this,cmd_id);
  if (handled == '\0') {
    menu_search_pos = 0;
    pHVar2 = GetMenu(hwnd);
    if (pHVar2 != (HMENU)0x0) {
      pos = menu_find_item_pos(pHVar2,cmd_id);
      wnd_call_menu_pos_command((WndOnMenuPosCommandView *)this,pos & 0xffff,pos >> 0x10);
    }
  }
  return;
}
#undef menu_search_pos

/* 005ec23a auto */
#define menu_search_pos (*(int *)((u8 *)&g.d_006e5368))
#define result (*(i32 *)(frame_ + FRAME_OFF(4)))
#define i (*(int *)(frame_ + FRAME_OFF(8)))
uint __cdecl menu_find_item_pos(HMENU hmenu,UINT item_id)

{
  int item_count;
  UINT UVar2;
  HMENU pHVar3;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  result = 0;
  menu_search_pos++;
  item_count = GetMenuItemCount(hmenu);
  for (i = 0; i < item_count; i++) {
    UVar2 = GetMenuItemID(hmenu,i);
    if (UVar2 == 0xffffffff) {
      pHVar3 = GetSubMenu(hmenu,i);
      result = menu_find_item_pos(pHVar3,item_id);
      if (result != 0) {
        i = item_count + 1;
      }
    }
    else {
      UVar2 = GetMenuItemID(hmenu,i);
      if (item_id == UVar2) {
        result = (i + 1) * 0x10000 | menu_search_pos - 1U;
        i = item_count + 1;
      }
    }
  }
  return result;
}
#undef menu_search_pos
#undef result
#undef i

/* 005ecf50 auto */
void __thiscall wnd_call_mousemove(WndOnMouseMoveView *this,i32 x,i32 y)

{
  if (this->on_mousemove != 0) {
    (*(code *)this->on_mousemove)(x,y);
  }
  return;
}

/* 005ecf90 auto */
void __thiscall wnd_call_lbuttondown(WndOnLButtonDownView *this,iptr x,iptr y)

{
  if (this->on_lbuttondown != 0) {
    (*(code *)this->on_lbuttondown)(x,y);
  }
  return;
}

/* 005ecfd0 auto */
void __thiscall wnd_call_lbuttonup_raw(WndOnLButtonUpRawView *this,iptr x,iptr y)

{
  if (this->on_lbuttonup_raw != 0) {
    (*(code *)this->on_lbuttonup_raw)(x,y);
  }
  return;
}

/* 005ed010 auto */
void __thiscall wnd_call_lbuttonup(WndOnLButtonUpView *this,i32 x,i32 y)

{
  if (this->on_lbuttonup != 0) {
    (*(code *)this->on_lbuttonup)(x,y);
  }
  return;
}

/* 005ed050 auto */
void __thiscall wnd_call_rbuttondown(WndOnRButtonDownView *this,iptr x,iptr y)

{
  if (this->on_rbuttondown != 0) {
    (*(code *)this->on_rbuttondown)(x,y);
  }
  return;
}

/* 005ed090 auto */
void __thiscall wnd_call_rbuttonup_raw(WndOnRButtonUpRawView *this,i32 x,i32 y)

{
  if (this->on_rbuttonup_raw != 0) {
    (*(code *)this->on_rbuttonup_raw)(x,y);
  }
  return;
}

/* 005ed0d0 auto */
void __thiscall wnd_call_rbuttonup(WndOnRButtonUpView *this,i32 x,i32 y)

{
  if (this->on_rbuttonup != 0) {
    (*(code *)this->on_rbuttonup)(x,y);
  }
  return;
}

/* 005ed110 auto */
void __thiscall wnd_call_dblclick(WndOnDblClickView *this,i32 x,i32 y)

{
  if (this->on_dblclick != 0) {
    (*(code *)this->on_dblclick)(x,y);
  }
  return;
}

/* 005ed150 auto */
void __thiscall wnd_call_keydown_pre(WndOnKeyDownPreView *this,i32 key)

{
  if (this->on_keydown_pre != 0) {
    (*(code *)this->on_keydown_pre)(key);
  }
  return;
}

/* 005ed190 auto */
void __thiscall wnd_call_keyup(WndOnKeyUpView *this,i32 key)

{
  if (this->on_keyup != 0) {
    (*(code *)this->on_keyup)(key);
  }
  return;
}

/* 005ed1d0 auto */
void __thiscall wnd_call_keydown(WndOnKeyDownView *this,i32 key)

{
  if (this->on_keydown != 0) {
    (*(code *)this->on_keydown)(key);
  }
  return;
}

/* 005ed210 auto */
void __thiscall wnd_call_char(WndOnCharView *this,i32 ch)

{
  if (this->on_char != 0) {
    (*(code *)this->on_char)(ch);
  }
  return;
}

/* 005ed250 auto */
i32 __thiscall wnd_call_close(WndOnCloseView *this)

{
  i32 result;
  
  if (this->on_close == 0) {
    result = 0;
  }
  else {
    result = (*(code *)this->on_close)();
  }
  return result;
}

/* 005ed290 auto */
void __thiscall wnd_call_minimize(WndOnMinimizeView *this)

{
  if (this->on_minimize != 0) {
    (*(code *)this->on_minimize)();
  }
  return;
}

/* 005ed2c0 auto */
void __thiscall wnd_call_restore(WndOnRestoreView *this)

{
  if (this->on_restore != 0) {
    (*(code *)this->on_restore)();
  }
  return;
}

/* 005ed2f0 auto */
void __thiscall wnd_call_setfocus(WndOnSetFocusView *this)

{
  if (this->on_setfocus != 0) {
    (*(code *)this->on_setfocus)();
  }
  return;
}

/* 005ed320 auto */
void __thiscall wnd_call_size(WndOnSizeView *this,i32 size_type)

{
  if (this->on_size != 0) {
    (*(code *)this->on_size)(size_type);
  }
  return;
}

/* 005ed360 auto */
void __thiscall wnd_call_move(WndOnMoveView *this,i32 x,i32 y)

{
  if (this->on_move != 0) {
    (*(code *)this->on_move)(x,y);
  }
  return;
}

/* 005ed3a0 auto */
void __thiscall wnd_call_msg44(WndOnMsg44View *this,iptr notify_arg)

{
  if (this->on_commnotify != 0) {
    (*(code *)this->on_commnotify)(notify_arg);
  }
  return;
}

/* 005ed3e0 auto */
void __thiscall wnd_call_hscroll(WndOnHScrollView *this,i32 scroll_pos)

{
  if (this->on_hscroll != 0) {
    (*(code *)this->on_hscroll)(scroll_pos);
  }
  return;
}

/* 005ed420 auto */
void __thiscall wnd_call_hscroll_track(WndOnHScrollTrackView *this,i32 scroll_pos)

{
  if (this->on_hscroll_track != 0) {
    (*(code *)this->on_hscroll_track)(scroll_pos);
  }
  return;
}

/* 005ed460 auto */
void __thiscall wnd_call_vscroll(WndOnVScrollView *this,i32 scroll_pos)

{
  if (this->on_vscroll != 0) {
    (*(code *)this->on_vscroll)(scroll_pos);
  }
  return;
}

/* 005ed4a0 auto */
void __thiscall wnd_call_vscroll_track(WndOnVScrollTrackView *this,i32 scroll_pos)

{
  if (this->on_vscroll_track != 0) {
    (*(code *)this->on_vscroll_track)(scroll_pos);
  }
  return;
}

/* 005ed4e0 auto */
void __thiscall wnd_call_msg4c8(WndCallMsg4c8View *this,i32 msg_arg)

{
  if (this->on_msg_4c8 != 0) {
    (*(code *)this->on_msg_4c8)(msg_arg);
  }
  return;
}

/* 005ed520 auto */
void __thiscall wnd_call_entersizemove(WndOnEnterSizeMoveView *this)

{
  if (this->on_entersizemove != 0) {
    (*(code *)this->on_entersizemove)();
  }
  return;
}

/* 005ed550 auto */
void __thiscall wnd_call_exitsizemove(WndOnExitSizeMoveView *this)

{
  if (this->on_exitsizemove != 0) {
    (*(code *)this->on_exitsizemove)();
  }
  return;
}

/* 005ed580 auto */
void __thiscall wnd_on_size_nop(void *this,i32 width,i32 height)

{
  return;
}

/* 005ed5a0 auto */
bool __thiscall wnd_call_menu_pos_command(WndOnMenuPosCommandView *this,i32 menu_pos,i32 item_pos)

{
  bool has_handler;
  
  has_handler = this->on_menu_pos_command != 0;
  if (has_handler) {
    (*(code *)this->on_menu_pos_command)(menu_pos,item_pos);
  }
  return has_handler;
}

/* 005ed5f0 auto */
bool __thiscall wnd_call_command(WndOnCommandView *this,i32 cmd_id)

{
  bool has_handler;
  
  has_handler = this->on_command != 0;
  if (has_handler) {
    (*(code *)this->on_command)(cmd_id);
  }
  return has_handler;
}

/* 005ed640 auto */
/* Library Function - Single Match
    public: int __thiscall CSplitterWnd::IsTracking(void)
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall wnd_get_hscroll_pos(WndHScrollPosView *this)

{
  return this->hscroll_pos;
}

/* 005ed660 auto */
/* Library Function - Single Match
    public: int __thiscall CSplitterWnd::IsTracking(void)
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall wnd_get_vscroll_pos(WndVScrollPosView *this)

{
  return this->vscroll_pos;
}

/* 005ed680 auto */
/* Library Function - Single Match
    public: int __thiscall CSplitterWnd::IsTracking(void)
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall wnd_get_hscroll_page(WndHScrollPageView *this)

{
  return this->hscroll_page;
}

/* 005ed6a0 auto */
/* Library Function - Single Match
    public: int __thiscall CSplitterWnd::IsTracking(void)
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall wnd_get_vscroll_page(WndVScrollPageView *this)

{
  return this->vscroll_page;
}

/* 005ed6c0 auto */
/* Library Function - Single Match
    public: int __thiscall CSplitterWnd::IsTracking(void)
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall wnd_get_mci_device(WndMciDeviceView *this)

{
  return this->mci_device;
}

/* 005ed6e0 auto */
void __thiscall wnd_call_mci_done(WndOnMciDoneView *this)

{
  if (this->on_mci_done != 0) {
    (*(code *)this->on_mci_done)();
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
  DDWindow *this;
  LRESULT LVar2;
  i32 key;
  int can_close;
  uptr DVar5;
  i32 zero_arg;
  
  this = (DDWindow *)GetClassLongA(hwnd,4);
  if (this == (DDWindow *)0x0) {
    LVar2 = DefWindowProcA(hwnd,msg,wparam,lparam);
    return LVar2;
  }
  if (msg < 0x11) {
    if (msg != 0x10) {
      if (msg == 2) {
        DVar5 = GetClassLongA(hwnd,0);
        *(i32 *)(DVar5 + 0x14) = 1;
        LVar2 = DefWindowProcA(hwnd,2,wparam,lparam);
        return LVar2;
      }
      goto switchD_005efc68_default;
    }
    can_close = wnd_call_close((WndOnCloseView *)(this->handlers));
    if (can_close != 0) {
      LVar2 = DefWindowProcA(hwnd,0x10,wparam,lparam);
      return LVar2;
    }
  }
  else if (msg < 0x45) {
    if (msg != 0x44) {
      if (msg != 0x1c) goto switchD_005efc68_default;
      if (wparam != ddwin_last_activate_app) {
        ddwin_call_activate_app((DDWindowActivateView *)this,wparam);
        ddwin_last_activate_app = wparam;
      }
    }
  }
  else if (msg < 0x201) {
    if (msg == 0x200) {
      handled = ddwin_dispatch_ctrl_msg(this,0x200,lparam & 0xffff,lparam >> 0x10);
      if (handled == '\0') {
        wnd_call_mousemove
                  ((WndOnMouseMoveView *)(this->handlers),lparam & 0xffff,lparam >> 0x10);
      }
    }
    else if (msg == 0x100) {
      zero_arg = 0;
      key = input_map_vkey(wparam);
      handled = ddwin_dispatch_ctrl_msg(this,0x100,key,zero_arg);
      if (handled == '\0') {
        key = input_map_vkey(wparam);
        wnd_call_keydown_pre((WndOnKeyDownPreView *)(this->handlers),key);
        key = input_map_vkey(wparam);
        wnd_call_keydown((WndOnKeyDownView *)(this->handlers),key);
      }
    }
    else if (msg == 0x101) {
      key = input_map_vkey(wparam);
      wnd_call_keyup((WndOnKeyUpView *)(this->handlers),key);
    }
    else {
      if (msg != 0x102) goto switchD_005efc68_default;
      handled = ddwin_dispatch_ctrl_msg(this,0x102,wparam & 0xff,0);
      if (handled == '\0') {
        wnd_call_char((WndOnCharView *)(this->handlers),wparam & 0xff);
      }
    }
  }
  else if (msg < 0x211) {
    if (msg == 0x210) {
      if ((wparam & 0xffff) == 0x201) {
        wnd_call_lbuttondown
                  ((WndOnLButtonDownView *)(this->handlers),lparam & 0xffff,lparam >> 0x10);
      }
      else if ((wparam & 0xffff) == 0x204) {
        wnd_call_rbuttondown
                  ((WndOnRButtonDownView *)(this->handlers),lparam & 0xffff,lparam >> 0x10);
      }
    }
    else {
      switch(msg) {
      case 0x201:
        handled = ddwin_dispatch_ctrl_msg(this,msg,lparam & 0xffff,lparam >> 0x10);
        if (handled == '\0') {
          ((DDWindowExt *)this)->lbutton_held[0] = 1;
          ((DDWindowExt *)this)->lbutton_held_byte1[0] = '\0';
          ((DDWindowExt *)this)->lbutton_held_byte2[0] = '\0';
          ((DDWindowExt *)this)->lbutton_held_byte3[0] = '\0';
          wnd_call_lbuttondown
                    ((WndOnLButtonDownView *)(this->handlers),lparam & 0xffff,lparam >> 0x10);
        }
        break;
      case 0x202:
        handled = ddwin_dispatch_ctrl_msg(this,msg,lparam & 0xffff,lparam >> 0x10);
        if (handled == '\0') {
          if (*(int *)((DDWindowExt *)this)->lbutton_held == 1) {
            ((DDWindowExt *)this)->lbutton_held[0] = '\0';
            ((DDWindowExt *)this)->lbutton_held_byte1[0] = '\0';
            ((DDWindowExt *)this)->lbutton_held_byte2[0] = '\0';
            ((DDWindowExt *)this)->lbutton_held_byte3[0] = '\0';
            wnd_call_lbuttonup
                      ((WndOnLButtonUpView *)(this->handlers),lparam & 0xffff,lparam >> 0x10);
          }
          wnd_call_lbuttonup_raw
                    ((WndOnLButtonUpRawView *)(this->handlers),lparam & 0xffff,lparam >> 0x10);
        }
        break;
      case 0x203:
        handled = ddwin_dispatch_ctrl_msg(this,msg,lparam & 0xffff,lparam >> 0x10);
        if (handled == '\0') {
          wnd_call_dblclick
                    ((WndOnDblClickView *)(this->handlers),lparam & 0xffff,lparam >> 0x10);
        }
        break;
      case 0x204:
        handled = ddwin_dispatch_ctrl_msg(this,msg,lparam & 0xffff,lparam >> 0x10);
        if (handled == '\0') {
          ((DDWindowExt *)this)->rbutton_held[0] = 1;
          ((DDWindowExt *)this)->rbutton_held_byte1[0] = '\0';
          ((DDWindowExt *)this)->rbutton_held_byte2[0] = '\0';
          ((DDWindowExt *)this)->rbutton_held_byte3[0] = '\0';
          wnd_call_rbuttondown
                    ((WndOnRButtonDownView *)(this->handlers),lparam & 0xffff,lparam >> 0x10);
        }
        break;
      case 0x205:
        handled = ddwin_dispatch_ctrl_msg(this,msg,lparam & 0xffff,lparam >> 0x10);
        if (handled == '\0') {
          if (*(int *)(((DDWindowExt *)this)->rbutton_held) == 1) {
            ((DDWindowExt *)this)->rbutton_held[0] = '\0';
            ((DDWindowExt *)this)->rbutton_held_byte1[0] = '\0';
            ((DDWindowExt *)this)->rbutton_held_byte2[0] = '\0';
            ((DDWindowExt *)this)->rbutton_held_byte3[0] = '\0';
            wnd_call_rbuttonup
                      ((WndOnRButtonUpView *)(this->handlers),lparam & 0xffff,lparam >> 0x10);
          }
          wnd_call_rbuttonup_raw
                    ((WndOnRButtonUpRawView *)(this->handlers),lparam & 0xffff,lparam >> 0x10);
        }
        break;
      default:
        goto switchD_005efc68_default;
      }
    }
  }
  else {
    if (msg != 0x4c8) {
switchD_005efc68_default:
      LVar2 = DefWindowProcA(hwnd,msg,wparam,lparam);
      return LVar2;
    }
    if (lparam == 0x20d) {
      wnd_call_msg4c8((WndCallMsg4c8View *)(this->handlers),0);
    }
  }
  return 0;
}

/* 005efd70 auto */
void __thiscall ddwin_call_activate_app(DDWindowActivateView *this,i32 active)

{
  if (this->on_activate_app != 0) {
    (*(code *)this->on_activate_app)(active);
  }
  return;
}

/* 005efeb0: written by hand in src/game/unwind.c */

/* 005f029e auto */
#define ctrl (*(i32 *)(frame_ + FRAME_OFF(0)))
void __thiscall ddwin_remove_all_controls(void *this)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  ctrl = ptrlist_first((PtrList *)((int)this + 0xc0));
  while (ctrl != 0) {
    ptrlist_remove_current((PtrList *)((int)this + 0xc0));
    ctrl = ptrlist_first((PtrList *)((int)this + 0xc0));
  }
  return;
}
#undef ctrl

/* 005f0342 auto */
#define ctrl (*(i32 *)(frame_ + FRAME_OFF(0)))
void __thiscall ddwin_deactivate_controls(void *this)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  ctrl = ptrlist_first((PtrList *)((int)this + 0xc0));
  while (ctrl != 0) {
    ddctrl_deactivate(ctrl);
    ctrl = ptrlist_next((PtrList *)((int)this + 0xc0));
  }
  return;
}
#undef ctrl

/* 005f0391 auto */
#define ctrl (*(DDControl * *)(frame_ + FRAME_OFF(0)))
i8 __thiscall ddwin_dispatch_ctrl_msg(DDWindow *this,int msg,int x,int y)

{
  int *rect;
  int handled;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((this->hover_control != 0) && (msg == 0x200)) {
    rect = (int *)ddctrl_get_rect((void *)this->hover_control);
    if ((x < *rect) ||
       (((rect[2] < x || (y < rect[1])) || (rect[3] < y)))) {
      ddctrl_dispatch_msg((DDControl *)this->hover_control,0xfff0,x,y);
      this->hover_control = 0;
    }
  }
  ctrl = (DDControl *)ptrlist_first((PtrList *)(this->child_controls));
  while( true ) {
    if (ctrl == (DDControl *)0x0) {
      return 0;
    }
    handled = ddctrl_dispatch_msg(ctrl,msg,x,y);
    if (handled != 0) break;
    ctrl = (DDControl *)ptrlist_next((PtrList *)(this->child_controls));
  }
  if (msg == 0x200) {
    this->hover_control = (uptr)ctrl;
  }
  return 1;
}
#undef ctrl
