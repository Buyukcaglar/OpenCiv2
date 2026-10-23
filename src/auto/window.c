/* The game, windows, dialogs and menus: functions translated from the original
 * (tools/gen_c.py, now edited directly), in address order. */
#include "auto_common.h"

/* 00408010 auto */
void __thiscall wnd_set_cursor(WndBase *this,i32 param_1)

{
  wnd_obj_set_cursor(this->native_wnd,param_1);
  return;
}

/* 00408050 auto */
void __thiscall wnd_set_icon(WndBase *this,i32 param_1)

{
  wnd_obj_set_icon(this->native_wnd,param_1);
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
  i32 uVar1;
  
  uVar1 = wnd_obj_client_width(this->native_wnd);
  return uVar1;
}

/* 004080f0 auto */
void __thiscall wnd_get_rect_in_parent(WndBase *this,iptr param_1)

{
  wnd_obj_get_rect_in_parent(this->native_wnd,param_1);
  return;
}

/* 00408130 auto */
u32 __thiscall wnd_set_lbuttonup_handler(WndEventHandlers *this,iptr param_1)

{
  u32 uVar1;
  
  uVar1 = this->on_lbuttonup;
  this->on_lbuttonup = param_1;
  return uVar1;
}

/* 00408170 auto */
u32 __thiscall wnd_set_rbuttonup_handler(WndEventHandlers *this,iptr param_1)

{
  u32 uVar1;
  
  uVar1 = this->on_rbuttonup;
  this->on_rbuttonup = param_1;
  return uVar1;
}

/* 004081b0 auto */
/* Library Function - Single Match
    public: virtual int __thiscall COleControlSite::SetDlgCtrlID(int)
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall wnd_set_keydown_handler(WndEventHandlers *this,iptr param_1)

{
  u32 uVar1;
  
  uVar1 = this->on_keydown;
  this->on_keydown = param_1;
  return uVar1;
}

/* 004081f0 auto */
/* Library Function - Multiple Matches With Same Base Name
    public: class basic_ostream<char,struct char_traits<char> > * __thiscall basic_ios<char,struct
   char_traits<char> >::tie(class basic_ostream<char,struct char_traits<char> > *)
    public: class basic_ostream<unsigned short,struct char_traits<unsigned short> > * __thiscall
   basic_ios<unsigned short,struct char_traits<unsigned short> >::tie(class basic_ostream<unsigned
   short,struct char_traits<unsigned short> > *)
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall wnd_set_char_handler(WndEventHandlers *this,iptr param_1)

{
  u32 uVar1;
  
  uVar1 = this->on_char;
  this->on_char = param_1;
  return uVar1;
}

/* 00408230 auto */
u32 __thiscall wnd_set_close_handler(WndEventHandlers *this,iptr param_1)

{
  u32 uVar1;
  
  uVar1 = this->on_close;
  this->on_close = param_1;
  return uVar1;
}

/* 00408270 auto */
u32 __thiscall wnd_set_minimize_handler(WndEventHandlers *this,iptr param_1)

{
  u32 uVar1;
  
  uVar1 = this->on_minimize;
  this->on_minimize = param_1;
  return uVar1;
}

/* 004082b0 auto */
u32 __thiscall wnd_set_restore_handler(WndEventHandlers *this,iptr param_1)

{
  u32 uVar1;
  
  uVar1 = this->on_restore;
  this->on_restore = param_1;
  return uVar1;
}

/* 004082f0 auto */
u32 __thiscall wnd_set_size_handler(WndEventHandlers *this,iptr param_1)

{
  u32 uVar1;
  
  uVar1 = this->on_size;
  this->on_size = param_1;
  return uVar1;
}

/* 00408330 auto */
u32 __thiscall wnd_set_move_handler(WndEventHandlers *this,iptr param_1)

{
  u32 uVar1;
  
  uVar1 = this->on_move;
  this->on_move = param_1;
  return uVar1;
}

/* 00408370 auto */
void __thiscall wnd_set_min_size(ModalMenuWindow *this,u32 param_1,u32 param_2)

{
  this->min_width = param_1;
  this->min_height = param_2;
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
  u32 uVar1;
  
  uVar1 = wnd_obj_destroy(this->native_wnd);
  this->native_wnd = uVar1;
  return;
}

/* 00408460 auto */
void __thiscall wnd_blit_surface(DibSurface *this)

{
  wnd_blit_surface_rect(this,0);
  return;
}

/* 00408490 auto */
#define local_c (*(DibSurface * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(DibSurface * *)(frame_ + FRAME_OFF(8)))
void __thiscall wnd_blit_surface_rect(DibSurface *this,iptr param_1)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 == 0) {
    if (this == (DibSurface *)0x0) {
      local_c = (DibSurface *)0x0;
    }
    else {
      local_c = this + 1;
    }
    surface_blit_to_wnd(this,(iptr)local_c,(iptr)&this->bounds_rect,(iptr)&this->bounds_rect);
    wnd_view_validate_rect((WndValidateRectView *)(this + 1),(iptr)&this->bounds_rect);
  }
  else {
    if (this == (DibSurface *)0x0) {
      local_8 = (DibSurface *)0x0;
    }
    else {
      local_8 = this + 1;
    }
    surface_blit_to_wnd(this,(iptr)local_8,param_1,param_1);
    wnd_view_validate_rect((WndValidateRectView *)(this + 1),param_1);
  }
  return;
}
#undef local_c
#undef local_8

/* 00408580 auto */
void __thiscall wnd_view_validate_rect(WndValidateRectView *this,iptr param_1)

{
  wnd_obj_validate_rect(this->wnd_obj,param_1);
  return;
}

/* 004085c0 auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall wnd_set_redraw_callback(SurfaceWindow *this,iptr param_1)

{
  this->on_paint = param_1;
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
void __thiscall dlg_reset(Dialog *this,i32 param_1)

{
  dialog_init(this,0,0,0,param_1);
  return;
}

/* 0040bc80 auto */
i32 __thiscall dlg_show_modal(Dialog *this,iptr param_1)

{
  i32 uVar1;
  
  uVar1 = dialog_run_modal(this,0,param_1);
  return uVar1;
}

/* 0040e017 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
#define local_31c (*(byte *)(frame_ + FRAME_OFF(4)))
#define city (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_310 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_308 (*(Dialog *)(frame_ + FRAME_OFF(24)))
#define civ (*(int *)(frame_ + FRAME_OFF(780)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(784)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(788)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(792)))
void __cdecl menu_find_city(void)

{
  bool bVar1;
  iptr iVar3;
  iptr iVar4;
  iptr city2;
  iptr civ2;
  i8 frame_[FRAME_OFF(800)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_308,0x4000);
  civ2 = human_civ;
  local_8 = 0;
  local_310 = 0;
  dlg_load_game_section(&local_308,ADDR(0x624f24, ((u8 *)&g.d_00624f24)),0x800001);
  for (city = 0; city < game.num_cities; city++) {
    if (cities[city].id != 0) {
      bVar1 = false;
      civ = (int)cities[city].owner;
      if ((game.reveal_map != '\0') ||
         (((game.game_flags & 0x80) != 0 && ((scenario_flags & 8) != 0)))) {
        bVar1 = true;
      }
      if (civ == civ2) {
        bVar1 = true;
      }
      local_31c = (byte)civ2;
      if (((1 << (local_31c & 0x1f) & (int)(char)cities[city].known_to) != 0) ||
         ((int)cities[city].owner == (civ2 & 0xffU))) {
        bVar1 = true;
      }
      if (bVar1) {
        text_clear();
        text_append(city * 0x58 + ADDR(0x64f360, ((u8 *)&cities + 32)));
        if (civ != civ2) {
          text_append_space();
          text_append_lparen();
          iVar3 = civ_adjective(civ);
          text_append(iVar3);
          text_append_rparen();
        }
        if ((((game.game_flags & 0x80) != 0) && ((scenario_flags & 2) != 0)) &&
           (iVar4 = city_objective_value(city), iVar4 != 0)) {
          text_append_space();
          text_append_lparen();
          text_append_label(0x1b0);
          if (1 < iVar4) {
            text_append(ADDR(0x624f30, ((u8 *)&g.d_00624f30)));
            text_append_int(iVar4);
          }
          text_append_rparen();
        }
        dialog_add_option((DialogOptionList *)&local_308,ADDR(0x679640, ((u8 *)&g.d_00679640)),city,0);
        local_310++;
      }
    }
  }
  if (local_310 == 0) {
    local_8 = 0xffffffff;
    /* inlined unwind funclet 0040e38d */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
  }
  else {
    city2 = dlg_show_modal(&local_308,0);
    if (city2 < 0) {
      local_8 = 0xffffffff;
      /* inlined unwind funclet 0040e38d */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
    }
    else {
      mapview_center_on
                ((ViewWindow *)&map_views,(int)cities[city2].x,(int)cities[city2].y);
      if ((local_308.field_dc != 0) && ((cities[city2].owner == civ2 || (game.reveal_map != '\0')))
         ) {
        city_window_open((ScaledWindowView *)&city_window,city2);
      }
      local_8 = 0xffffffff;
      /* inlined unwind funclet 0040e38d */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
    }
  }
  return;
}
#undef human_civ
#undef scenario_flags
#undef local_31c
#undef city
#undef local_310
#undef local_308
#undef civ
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0040e3b1 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
#define ui_large_screen (*(int *)((u8 *)&g.d_00633584))
void __cdecl menu_revolution(void)

{
  iptr iVar2;
  int iVar3;
  iptr civ;
  
  civ = human_civ;
  if (((game.game_flags & 0x80) == 0) || ((scenario_flags & 0x10) == 0)) {
    if ((civs[human_civ].flags & 8) == 0) {
      if (civs[human_civ].government != '\0') {
        iVar2 = civ_get_adjective(human_civ);
        text_set_string_arg(0,iVar2);
        text_set_label_arg(1,government_names[civs[civ].government]);
        iVar3 = popup_game_with_sprite(ADDR(0x624f34, ((u8 *)&g.d_00624f34)),(iptr)(&government_sprites +
                                                  (uint)civs[civ].government * 0x3c),
                                   (ui_large_screen == 0) - 1 & 8);
        if (iVar3 == 0) {
          snd_play_effect(0x3e,1,0,0);
          iVar2 = civ_name_plural(civ);
          text_set_string_arg(0,iVar2);
          popup_game_with_sprite(ADDR(0x624f40, ((u8 *)&g.d_00624f40)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
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

void __thiscall wnd_set_modal_idle_callback(ModalMenuWindow *this,iptr param_1)

{
  this->on_modal_idle = param_1;
  return;
}

/* 0040f350 auto */
void __thiscall wnd_set_keyboard_nav(Wnd *this,i32 param_1)

{
  *(i8 *)&this->keyboard_nav = (i8)param_1;
  return;
}

/* 0040ffa0 auto */
i32 __thiscall
dlg_load_game_section(Dialog *this,iptr param_1,i32 param_2)

{
  i32 uVar1;
  
  uVar1 = dialog_load_text_ex(this,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),param_1,0,param_2);
  return uVar1;
}

/* 0040ffe0 auto */
i32 __thiscall
dialog_load_text_ex
          (Dialog *this,iptr param_1,iptr param_2,i32 param_3,i32 param_4)

{
  i32 uVar1;
  
  uVar1 = dialog_load_text_section(this,param_1,param_2,param_3,0,0,0,0,param_4);
  return uVar1;
}

/* 00410030 auto */
i32 __cdecl popup_game_with_sprite(iptr param_1,iptr param_2,i32 param_3)

{
  i32 uVar1;
  
  uVar1 = popup_text_with_sprite(ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),param_1,0,param_2,param_3);
  return uVar1;
}

/* 00410e0a auto */
#define mapview_cursor_id (*(int *)((u8 *)&g.d_0066cb00))
i32 __cdecl ui_paradrop_cursor_active(void)

{
  i32 uVar1;
  
  if ((mapview_cursor_id == 0x202) || (mapview_cursor_id == 0x203)) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}
#undef mapview_cursor_id

/* 00414b70 auto */
void __thiscall wnd_set_cursor_now(WndCursorView *this,iptr param_1,i32 param_2)

{
  wnd_obj_set_cursor_now(this->native_wnd,param_1,param_2);
  return;
}

/* 00414bb0 auto */
i32 __thiscall wnd_client_height(WndBase *this)

{
  i32 uVar1;
  
  uVar1 = wnd_obj_client_height(this->native_wnd);
  return uVar1;
}

/* 00414be0 auto */
u32 __thiscall wnd_set_mousemove_handler(WndHandlersMouseSetView *this,iptr param_1)

{
  u32 uVar1;
  
  uVar1 = this->on_mouse_move;
  this->on_mouse_move = param_1;
  return uVar1;
}

/* 00414c20 auto */
u32 __thiscall wnd_set_lbuttondown_handler(WndHandlersMouseSetView *this,iptr param_1)

{
  u32 uVar1;
  
  uVar1 = this->on_lbutton_down;
  this->on_lbutton_down = param_1;
  return uVar1;
}

/* 00414c60 auto */
u32 __thiscall wnd_set_lbuttonup_any_handler(WndHandlersMouseSetView *this,iptr param_1)

{
  u32 uVar1;
  
  uVar1 = this[1].field_0;
  this[1].field_0 = param_1;
  return uVar1;
}

/* 00414ca0 auto */
u32 __thiscall wnd_set_dblclick_handler(WndHandlersMouseSetView *this,iptr param_1)

{
  u32 uVar1;
  
  uVar1 = this[3].field_4;
  this[3].field_4 = param_1;
  return uVar1;
}

/* 00414ce0 auto */
void __thiscall wnd_set_capture(WndBase *this)

{
  iptr iVar1;
  
  iVar1 = wnd_get_window(this);
  wnd_obj_set_capture(iVar1);
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
  i32 uVar1;
  
  uVar1 = wnd_get_window(this);
  wnd_obj_release_capture(uVar1);
  return;
}

/* 00414da0 auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall wnd_set_caption_button_handler(FrameWindow *this,iptr param_1)

{
  this->on_caption_button = param_1;
  return;
}

/* 00414dd0 auto */
i32 __cdecl popup_game_with_city(iptr param_1,iptr param_2)

{
  i32 uVar1;
  
  uVar1 = popup_text_with_city(ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),param_1,0,param_2);
  return uVar1;
}

/* 004190d0 auto */
i32 __cdecl popup_text(iptr param_1,iptr param_2)

{
  i32 uVar1;
  
  uVar1 = popup_text_flags(param_1,param_2,0);
  return uVar1;
}

/* 00419100 auto */
i32 __cdecl popup_text_flags(iptr param_1,iptr param_2,i32 param_3)

{
  i32 uVar1;
  
  uVar1 = popup_text_ex(param_1,param_2,0,param_3);
  return uVar1;
}

/* 00419130 auto */
i32 __cdecl popup_text_ex(iptr param_1,iptr param_2,i32 param_3,i32 param_4)

{
  i32 uVar1;
  
  uVar1 = popup_text_run(param_1,param_2,param_3,0,0,0,param_4);
  return uVar1;
}

/* 00419b80 auto */
void __cdecl wnd_flush_paint(void)

{
  win_dispatch_all_paints();
  return;
}

/* 00419ba0 auto */
void __thiscall wnd_set_bg_color(WndBase *this,i32 param_1)

{
  wnd_obj_set_bg_color(this->native_wnd,param_1);
  return;
}

/* 00419be0 auto */
void __thiscall wnd_set_bg_surface(WndBase *this,iptr param_1)

{
  wnd_obj_set_bg_surface(this->native_wnd,param_1);
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
dialog_load_text(Dialog *this,iptr param_1,iptr param_2,i32 param_3)

{
  i32 uVar1;
  
  uVar1 = dialog_load_text_ex(this,param_1,param_2,0,param_3);
  return uVar1;
}

/* 00421e40 auto */
#define dlg_scale_den (*(i32 *)((u8 *)&g.d_00635a38))
#define dlg_scale_num (*(i32 *)((u8 *)&g.d_00635a34))
void __cdecl dlg_set_scale(i32 param_1,i32 param_2)

{
  dlg_scale_num = param_1;
  dlg_scale_den = param_2;
  return;
}
#undef dlg_scale_den
#undef dlg_scale_num

/* 00421e70 auto */
i32 __cdecl popup_game_flags(iptr param_1,i32 param_2)

{
  i32 uVar1;
  
  uVar1 = popup_text_flags(ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),param_1,param_2);
  return uVar1;
}

/* 00421ea0 auto */
i32 __cdecl popup_game(iptr param_1)

{
  i32 uVar1;
  
  uVar1 = popup_text(ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),param_1);
  return uVar1;
}

/* 00421ed0 auto */
i32 __cdecl dlg_game_text_input(iptr param_1,i32 param_2,iptr param_3,iptr param_4)

{
  i32 uVar1;
  
  uVar1 = dlg_text_input(ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),param_1,param_2,param_3,param_4);
  return uVar1;
}

/* 00426f30 auto */
Dialog * __thiscall dialog_scalar_dtor(Dialog *this,uint param_1)

{
  dialog_dtor(this);
  if ((param_1 & 1) != 0) {
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
i32 __cdecl popup_game_sprite_flags(iptr param_1,i32 param_2,iptr param_3,i32 param_4)

{
  i32 uVar1;
  
  uVar1 = popup_text_with_sprite(ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),param_1,param_2,param_3,param_4);
  return uVar1;
}

/* 0042a768 auto */
void __thiscall picwnd_close(PictureWindowCore *this)

{
  if (-1 < (int)this->report_id) {
    this->report_id = 0xffffffff;
    wnd_remove_all_controls((WndControlRemoveView *)this->pad_48);
    surface_release((DibSurface *)&this->field_2d8);
    frame_wnd_close((DibSurface *)this);
  }
  return;
}

/* 0042a7bc auto */
#define frame_border_width (*(int *)((u8 *)&g.d_0063359c))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define local_444 (*(GamePalette *)(frame_ + FRAME_OFF(4)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1080)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1084)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1088)))
void __thiscall
picwnd_open
          (PictureWindow *this,uint param_1,u32 param_2,u32 param_3,u32 param_4,u32 param_5,
          u32 param_6,u32 param_7)

{
  u32 uVar1;
  int iVar2;
  int iVar3;
  u32 uVar4;
  int iVar5;
  i8 frame_[FRAME_OFF(1096)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  palette_init(&local_444);
  local_8 = 0;
  picwnd_close((PictureWindowCore *)&advisor_window);
  ui_set_button_font(ADDR(0x63eaa0, ((u8 *)&g.d_0063eaa0)));
  this->controls_created = 0;
  this->field_454 = 0;
  this->page_count = 1;
  this->first_row = 0;
  this->report_civ = 1;
  this->report_param = 0;
  this->report_id = param_2;
  this->field_4a0 = param_3;
  uVar4 = GetSystemMetrics(2);
  this->vscroll_width = uVar4;
  iVar2 = frame_border_width;
  if ((int)param_1 < 0) {
    param_1 = ~param_1 + 1;
  }
  else if (param_1 != 10000) {
    param_1 += 0x31;
  }
  this->image_width = param_4;
  this->image_height = param_5;
  win_flush_pending_msgs();
  if (param_1 == 10000) {
    surface_load_gif_file((DibSurface *)&this->field_2d8,ADDR(0x625ee0, ((u8 *)&g.d_00625ee0)),10,0xc0,(iptr)&local_444)
    ;
  }
  else {
    surface_load_gif_resource((DibSurface *)&this->field_2d8,param_1,10,0xc0,(iptr)&local_444);
  }
  win_flush_pending_msgs();
  if ((int)param_4 < 1) {
    uVar4 = surface_width((DibSurface *)&this->field_2d8);
    this->image_width = uVar4;
  }
  if ((int)param_5 < 1) {
    uVar4 = surface_height((DibSurface *)&this->field_2d8);
    this->image_height = uVar4;
  }
  this->window_width = param_6;
  this->window_height = param_7;
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
  iVar3 = screen_height;
  uVar4 = this->window_width;
  uVar1 = this->window_height;
  iVar5 = wnd_nonclient_height((WndBase *)&main_frame_wnd);
  frame_wnd_create
            ((FrameWindow *)this,0,(this->field_4a0 == 0) - 1 & 8,
             (screen_width >> 1) - ((int)(uVar4 + iVar2 * 2) >> 1),
             (iVar3 - iVar5 >> 1) - ((int)(uVar1 + iVar2 * 2) >> 1),this->image_width,this->image_height,
             0,iVar2,iVar2);
  local_8 = 0xffffffff;
  /* inlined unwind funclet 0042ab9b */ { palette_destroy((GamePalette *)((iptr)&local_444)); }
  return;
}
#undef frame_border_width
#undef screen_height
#undef local_444
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0042abc1 auto */
void __thiscall
picwnd_blit_at
          (FrameWindow *this,int param_1,int param_2,i32 param_3,i32 param_4)

{
  gfx_copy_rect_xywh((iptr)&this->field_2d8,(iptr)this,param_1,param_2,this->client_x + param_1,
                     this->client_y + param_2,param_3,param_4);
  return;
}

/* 0042ac18 auto */
void __thiscall picwnd_blit(PictureWindow *this)

{
  picwnd_blit_at((FrameWindow *)this,0,0,this->image_width,this->image_height);
  return;
}

/* 0043c110 auto */
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    public: __thiscall CDaoFieldInfo::~CDaoFieldInfo(void)
   
   Library: Visual Studio 1998 Debug */

void __thiscall picwnd_dtor(void *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  (*(i32 *)((char *)&local_8 + 1)) = 0;
  (*(i8 *)((char *)&local_8 + 0)) = 5;
  /* inlined unwind funclet 0043c19c */ { scrollbar_dtor((Control *)(*(int *)((iptr)&this) + 0x410)); }
  (*(i8 *)((char *)&local_8 + 0)) = 4;
  /* inlined unwind funclet 0043c1ab */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x3d4)); }
  (*(i8 *)((char *)&local_8 + 0)) = 3;
  /* inlined unwind funclet 0043c1ba */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x398)); }
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  /* inlined unwind funclet 0043c1c9 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x35c)); }
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  /* inlined unwind funclet 0043c1d8 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 800)); }
  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
  /* inlined unwind funclet 0043c1e7 */ { surface_dtor((DibSurface *)(*(int *)((iptr)&this) + 0x2d8)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet 0043c1f6 */ { frame_wnd_dtor(*(DibSurface **)((iptr)&this)); }
  return;
}
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0043c260 auto */
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
ViewWindow * __thiscall picwnd_ctor(ViewWindow *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  frame_wnd_ctor((SurfaceWindow *)this);
  local_8 = 0;
  surface_ctor((DibSurface *)&this->field_2d8);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  button_ctor((Control *)&this->field_320);
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  button_ctor((Control *)&this->field_35c);
  (*(i8 *)((char *)&local_8 + 0)) = 3;
  button_ctor((Control *)(this->pad_364 + 0x34));
  (*(i8 *)((char *)&local_8 + 0)) = 4;
  button_ctor((Control *)(this->pad_3c0 + 0x14));
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),5);
  scrollbar_ctor((Control *)(this->pad_3c0 + 0x50));
  this->vtable = (u32)&PTR_FUN_0061c05c;
  return this;
}
#undef local_10
#undef puStack_c
#undef local_8

/* 0043c5c0 auto */
i32 __thiscall wnd_nonclient_height(WndBase *this)

{
  i32 uVar1;
  
  uVar1 = wnd_obj_frame_height(this->native_wnd);
  return uVar1;
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
void __thiscall dialog_set_list_indent(DialogCore *this,uptr param_1,iptr param_2)

{
  (&this[0xd].field_0)[param_2] = param_1;
  return;
}

/* 0043c9d0 auto */
void __thiscall dialog_load_game_text(Dialog *this,iptr param_1)

{
  dialog_load_text_noflags(this,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),param_1);
  return;
}

/* 0043ca10 auto */
void __thiscall dialog_load_text_noflags(Dialog *this,iptr param_1,iptr param_2)

{
  dialog_load_text(this,param_1,param_2,0);
  return;
}

/* 00444270 auto */
i32 __cdecl popup_debug_text(iptr param_1)

{
  i32 uVar1;
  
  uVar1 = popup_text(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),param_1);
  return uVar1;
}

/* 004442a0 auto */
i32 __cdecl dlg_game_txt_with_unit_flags(iptr param_1,iptr param_2,i32 param_3)

{
  i32 uVar1;
  
  uVar1 = popup_text_with_unit_sprite(ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),param_1,0,param_2,param_3);
  return uVar1;
}

/* 004442e0 auto */
i32 __cdecl dlg_game_txt_with_unit(iptr param_1,iptr param_2)

{
  i32 uVar1;
  
  uVar1 = popup_text_with_unit(ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),param_1,0,param_2);
  return uVar1;
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
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
SurfaceWindow * __thiscall surfwnd_ctor(SurfaceWindow *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  surface_ctor((DibSurface *)this);
  local_8 = 0;
  surfwnd_wnd_ctor((Wnd *)this->pad_48);
  this->vtable = (u32)&PTR_FUN_0061c060;
  this->field_100 = 0;
  this->on_paint = 0;
  return this;
}
#undef local_10
#undef puStack_c
#undef local_8

/* 0044c670 auto */
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
Wnd * __thiscall surfwnd_wnd_ctor(Wnd *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  wnd_ctor((ModalMenuWindow *)this);
  this->control_list = 0;
  this->field_bc = 0;
  this->field_c0 = 0;
  *(i8 *)&this->keyboard_nav = 1;
  return this;
}
#undef local_10
#undef puStack_c
#undef local_8

/* 0044c730 auto */
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
ModalMenuWindow * __thiscall wnd_ctor(ModalMenuWindow *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  wnd_record_init((WndBase *)this);
  local_8 = 0;
  wnd_handlers_ctor((WndHandlers *)this->pad_10);
  this->menu = 0;
  this->on_menu_pos_command = 0;
  this->on_command = 0;
  this->min_width = 0;
  this->min_height = 0;
  this->max_width = 0x4000;
  this->max_height = 0x4000;
  this->field_a8 = 0;
  this->field_ac = 0;
  this->modal_running = 0;
  this->hscroll_step = 1;
  this->vscroll_step = 1;
  this->on_menu_select = 0;
  this->on_modal_idle = 0;
  return this;
}
#undef local_10
#undef puStack_c
#undef local_8

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
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
i32 __thiscall surfwnd_wnd_dtor(void *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  /* inlined unwind funclet 0044cb5e */ { wnd_dtor(*(WndBase **)((iptr)&this)); }
  return uStack_10;
}
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0044cba0: written by hand in src/game/unwind.c */

/* 0044cc80: written by hand in src/game/throneroom.c */

/* 0044cd9b: written by hand in src/game/throneroom.c */

/* 00450390 auto */
void __thiscall wnd_set_palette(WndBase *this,iptr param_1)

{
  this->wnd_palette = param_1;
  wnd_apply_palette_handle(this,param_1);
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
void __thiscall wnd_apply_palette_handle(WndBase *this,iptr param_1)

{
  wnd_obj_select_palette(this->native_wnd,*(i32 *)(param_1 + 0x404));
  return;
}

/* 00451890 auto */
void __thiscall wnd_get_cursor_pos(WndBase *this,iptr param_1,iptr param_2)

{
  iptr iVar1;
  
  iVar1 = wnd_get_window(this);
  wnd_obj_get_cursor_pos(iVar1,param_1,param_2);
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
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
Control * __thiscall hotspot_ctor(Control *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  ctrl_base_ctor(this);
  return this;
}
#undef local_10
#undef puStack_c
#undef local_8

/* 004519b0 auto */
void __thiscall
hotspot_create(ClickControl *this,iptr param_1,iptr param_2,iptr param_3)

{
  u32 uVar1;
  
  if (this->hwnd != 0) {
    ctrl_destroy((Control *)this);
  }
  ctrl_init((Control *)this,param_1,1,param_2,param_3);
  this->is_enabled = 0;
  this->on_click = 0;
  this->on_select = 0;
  this->font = 0;
  this->scroll_pos = 0;
  uVar1 = hotspot_create_hwnd(param_3,(iptr)this);
  this->hwnd = uVar1;
  return;
}

/* 00451a60 auto */
void __thiscall hotspot_set_click_callback(HotspotClickSetView *this,iptr param_1)

{
  this->on_click = param_1;
  return;
}

/* 00451a90 auto */
/* Library Function - Single Match
    public: void __thiscall CDialog::SetHelpID(unsigned int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall hotspot_set_dblclick_callback(HotspotDblClickSetView *this,iptr param_1)

{
  this->on_dblclick = param_1;
  return;
}

/* 00453aa0 auto */
Hotspot * __thiscall hotspot_scalar_dtor(Hotspot *this,uint param_1)

{
  hotspot_dtor(this);
  if ((param_1 & 1) != 0) {
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
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
void __thiscall hotspot_dtor(Hotspot *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  if (this->hwnd != 0) {
    region_dispose(this->hwnd);
  }
  local_8 = 0xffffffff;
  /* inlined unwind funclet 00453bfa */ { ctrl_base_dtor(*(ControlBase **)((iptr)&this)); }
  return;
}
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00456ee0 auto */
/* Library Function - Single Match
    public: class ostream * __thiscall ios::tie(class ostream *)
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall wnd_set_keydown_pre_handler(WndSetKeydownPreHandlerView *this,iptr param_1)

{
  u32 uVar1;
  
  uVar1 = this->tied_stream;
  this->tied_stream = param_1;
  return uVar1;
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
void __cdecl ui_delay_ticks(int param_1)

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
  } while ((int)(DVar2 - DVar1) < (param_1 * 0x32) / 3);
  return;
}

/* 0046f18f auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl ui_blit_all_windows(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; local_8 < 8; local_8++) {
    if ((local_8 == 0) || (*(short *)(&map_view_open_flags + local_8 * 0x3f0) != 0)) {
      wnd_blit_surface((DibSurface *)(&map_views + local_8 * 0x3f0));
    }
  }
  wnd_blit_surface((DibSurface *)&minimap_window);
  wnd_blit_surface((DibSurface *)&status_window);
  wnd_blit_surface((DibSurface *)&city_window);
  wnd_flush_paint();
  return;
}
#undef local_8

/* 004731d2 auto */
#define local_58 (*(char *)(frame_ + FRAME_OFF(0)))
#define local_54 (*(DWORD *)(frame_ + FRAME_OFF(4)))
#define local_50 (*(HWND *)(frame_ + FRAME_OFF(8)))
#define local_48 (*(LPCSTR *)(frame_ + FRAME_OFF(16)))
#define local_3c (*(DWORD *)(frame_ + FRAME_OFF(28)))
#define local_38 (*(LPSTR *)(frame_ + FRAME_OFF(32)))
#define local_34 (*(DWORD *)(frame_ + FRAME_OFF(36)))
#define local_24 (*(LPCSTR *)(frame_ + FRAME_OFF(52)))
#define local_20 (*(DWORD *)(frame_ + FRAME_OFF(56)))
#define local_18 (*(LPCSTR *)(frame_ + FRAME_OFF(64)))
uint __cdecl
ui_file_name_dialog(iptr param_1,iptr param_2,iptr param_3,iptr param_4,iptr param_5,int param_6,
            int param_7)

{
  iptr iVar1;
  BOOL BVar1;
  i8 frame_[FRAME_OFF(88)] __attribute__((aligned(8)));  /* original stack frame */
  
  _memset(&local_54,0,0x4c);
  local_54 = 0x4c;
  local_50 = (HWND)0x0;
  if (param_1 != 0) {
    iVar1 = wnd_get_window((WndBase *)param_1);
    local_50 = *(HWND *)(iVar1 + 4);
  }
  local_48 = (LPCSTR)param_4;
  local_3c = 1;
  local_38 = (LPSTR)param_3;
  local_34 = 0x100;
  local_24 = (LPCSTR)param_2;
  local_18 = (LPCSTR)param_5;
  if (param_6 == 0) {
    local_20 = 0x80e;
  }
  else {
    local_20 = 0x180e;
  }
  if (param_7 == 0) {
    BVar1 = GetOpenFileNameA((LPOPENFILENAMEA)&local_54);
    local_58 = (char)BVar1;
  }
  else {
    BVar1 = GetSaveFileNameA((LPOPENFILENAMEA)&local_54);
    local_58 = (char)BVar1;
  }
  if (local_58 != 1) {
    CommDlgExtendedError();
  }
  return (uint)(local_58 == 1);
}
#undef local_58
#undef local_54
#undef local_50
#undef local_48
#undef local_3c
#undef local_38
#undef local_34
#undef local_24
#undef local_20
#undef local_18

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
void __cdecl ui_redraw_all_maps(int param_1)

{
  if ((moving_units_mode != 0) || (param_1 != 0)) {
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

void __cdecl ui_focus_active_unit(int param_1)

{
  iptr iVar1;
  iptr unit;
  int iVar3;
  bool bVar4;
  
  bVar4 = moving_units_mode != 1;
  if (bVar4) {
    unit_blink_phase = 0;
    unit_blink_skip_tick = 1;
    mapviews_redraw_cursor();
    moving_units_mode = 1;
    unit_blink_active = 0;
  }
  iVar1 = unit_is_selectable((int)game.active_unit);
  if (iVar1 == 0) {
    unit_activate_next(param_1);
  }
  bVar4 = iVar1 != 0 && bVar4;
  unit = (iptr)game.active_unit;
  if ((((-1 < unit) && (unit < game.num_units)) && (units[unit].id != 0)) &&
     ((iVar3 = unit_is_selectable(unit), iVar3 != 0 &&
      (((game.multiplayer < 3 || (mp_simultaneous_moves != '\0')) ||
       ((param_1 == 0 || (mp_turn_civ_i32 == human_civ)))))))) {
    if (bVar4) {
      status_redraw(1);
    }
    map_cursor_x = units[unit].x;
    map_cursor_y = units[unit].y;
    if (bVar4) {
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
void __cdecl popup_file_with_sprite(iptr param_1,iptr param_2,iptr param_3,i32 param_4)

{
  popup_text_with_sprite(param_1,param_2,0,param_3,param_4);
  return;
}

/* 00490500 auto */
void __cdecl popup_text_with_city_noflags(iptr param_1,iptr param_2,i32 param_3)

{
  popup_text_with_city(param_1,param_2,0,param_3);
  return;
}

/* 00490530 auto */
void __cdecl popup_text_with_unit_noflags(iptr param_1,iptr param_2,iptr param_3)

{
  popup_text_with_unit(param_1,param_2,0,param_3);
  return;
}

/* 004923c0 auto */
void __thiscall wnd_set_focus(WndBase *this)

{
  wnd_obj_set_focus(this->native_wnd);
  return;
}

/* 00497cc0 auto */
void __thiscall wnd_set_bg_tile(DiploLeaderView *this,iptr param_1)

{
  wnd_obj_set_bg_tile(this->field_8,param_1);
  return;
}

/* 00497d00 auto */
void __thiscall wnd_set_caption_height(WndBase *this,i32 param_1)

{
  wnd_obj_set_caption_height(this->native_wnd,param_1);
  return;
}

/* 004a6b80 auto */
void __cdecl
popup_text_with_advance(iptr param_1,iptr param_2,i32 param_3,iptr advance,i32 param_5)

{
  popup_text_with_sprite(param_1,param_2,param_3,
                     (iptr)(&advance_category_icon_sprites +
                           (char)advances[advance].category * 0xf0 +
                           (char)advances[advance].epoch * 0x3c),param_5);
  return;
}

/* 004a6bdc auto */
#define local_8 (*(i8 * *)(frame_ + FRAME_OFF(0)))
i32 __cdecl
popup_text_with_improvement(iptr param_1,iptr param_2,i32 param_3,int param_4,i32 param_5)

{
  i32 uVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_4 < 0x27) {
    local_8 = &improvement_icon_sprites + param_4 * 0x3c;
  }
  else {
    local_8 = &wonder_icon_sprites + (param_4 * 4 - 0x9c) * 0xf;
  }
  uVar1 = popup_text_with_sprite(param_1,param_2,param_3,(iptr)local_8,param_5);
  return uVar1;
}
#undef local_8

/* 004a6c4b auto */
i32 __cdecl
popup_text_with_unit_sprite(iptr param_1,iptr param_2,i32 param_3,int param_4,i32 param_5)

{
  i32 uVar1;
  
  uVar1 = popup_text_with_sprite(param_1,param_2,param_3,(iptr)(&unit_sprites + param_4 * 0x3c),param_5)
  ;
  return uVar1;
}

/* 004a6c85 auto */
#define ui_large_screen (*(int *)((u8 *)&g.d_00633584))
void __cdecl
popup_city_sprite_draw_cb(i32 param_1,iptr param_2,iptr city,i32 param_4,int param_5,
            i32 param_6)

{
  gfx_draw_city(param_2,city,0,param_5 + 2,param_6,(ui_large_screen == 0) - 1 & 8);
  return;
}
#undef ui_large_screen

/* 004a6cc5 auto */
#define dlg_help_pressed (*(u32 *)((u8 *)&g.d_00631edc))
#define ui_large_screen (*(int *)((u8 *)&g.d_00633584))
#define local_340 (*(Dialog *)(frame_ + FRAME_OFF(0)))
#define local_4c (*(Sprite *)(frame_ + FRAME_OFF(756)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(816)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(820)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(824)))
i32 __cdecl popup_text_with_city(iptr param_1,iptr param_2,i32 param_3,iptr param_4)

{
  i32 uVar1;
  i8 frame_[FRAME_OFF(832)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_340,0x4000);
  local_8 = 0;
  sprite_init(&local_4c);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  sprite_create_solid
            (&local_4c,(2 - (uint)(ui_large_screen == 0)) * 0x40,(2 - (uint)(ui_large_screen == 0)) * 0x30
             ,0);
  dialog_load_text(&local_340,param_1,param_2,param_3);
  dialog_set_sprite_draw_fn((DialogCore *)&local_340,ADDR(0x40238d, popup_city_sprite_draw_cb));
  dialog_set_image_zoom((DialogWindowView *)&local_340,0);
  dialog_add_sprite((DialogOptionList *)&local_340,(iptr)&local_4c,param_4,0);
  uVar1 = dlg_show_modal(&local_340,0);
  dlg_help_pressed = local_340.field_dc;
  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
  /* inlined unwind funclet 004a6dc9 */ { sprite_destroy((Sprite *)((iptr)&local_4c)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet 004a6dd2 */ { dialog_dtor((Dialog *)((iptr)&local_340)); }
  return uVar1;
}
#undef dlg_help_pressed
#undef ui_large_screen
#undef local_340
#undef local_4c
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004a6df7 auto */
#define ui_large_screen (*(int *)((u8 *)&g.d_00633584))
void __cdecl
popup_unit_sprite_draw_cb(i32 param_1,iptr param_2,iptr unit,i32 param_4,int param_5,
            i32 param_6)

{
  gfx_draw_unit(param_2,unit,4,param_5 + 2,param_6,(ui_large_screen == 0) - 1 & 8,0);
  return;
}
#undef ui_large_screen

/* 004a6e39 auto */
#define dlg_help_pressed (*(u32 *)((u8 *)&g.d_00631edc))
#define ui_large_screen (*(int *)((u8 *)&g.d_00633584))
#define local_340 (*(Dialog *)(frame_ + FRAME_OFF(0)))
#define local_4c (*(Sprite *)(frame_ + FRAME_OFF(756)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(816)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(820)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(824)))
i32 __cdecl popup_text_with_unit(iptr param_1,iptr param_2,i32 param_3,iptr param_4)

{
  i32 uVar1;
  i8 frame_[FRAME_OFF(832)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_340,0x4000);
  local_8 = 0;
  sprite_init(&local_4c);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  sprite_create_solid
            (&local_4c,(2 - (uint)(ui_large_screen == 0)) * 0x40,(2 - (uint)(ui_large_screen == 0)) * 0x30
             ,0);
  dialog_load_text(&local_340,param_1,param_2,param_3);
  dialog_set_sprite_draw_fn((DialogCore *)&local_340,ADDR(0x402649, popup_unit_sprite_draw_cb));
  dialog_set_image_zoom((DialogWindowView *)&local_340,0);
  dialog_add_sprite((DialogOptionList *)&local_340,(iptr)&local_4c,param_4,0);
  uVar1 = dlg_show_modal(&local_340,0);
  dlg_help_pressed = local_340.field_dc;
  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
  /* inlined unwind funclet 004a6f3d */ { sprite_destroy((Sprite *)((iptr)&local_4c)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet 004a6f46 */ { dialog_dtor((Dialog *)((iptr)&local_340)); }
  return uVar1;
}
#undef dlg_help_pressed
#undef ui_large_screen
#undef local_340
#undef local_4c
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004a93b3 auto */
#define local_30 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_10 (*(iptr *)(frame_ + FRAME_OFF(32)))
#define local_c (*(uint *)(frame_ + FRAME_OFF(36)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(40)))
void __cdecl accel_start_develop_city(iptr city,int param_2)

{
  byte civ;
  i8 uVar2;
  char cVar3;
  int x2;
  int y2;
  iptr x;
  int y;
  int iVar8;
  int iVar9;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  x2 = (int)cities[city].x;
  y2 = (int)cities[city].y;
  net_batch_begin();
  for (local_18 = 0; local_18 < param_2; local_18++) {
    local_c = 0;
    local_30 = -1;
    for (local_10 = 0; local_10 < 0x14; local_10++) {
      x = map_wrap_x((char)(&city_tile_dx_table)[local_10] + x2);
      y = (char)(&city_tile_dy_table)[local_10] + y2;
      iVar8 = map_in_bounds(x,y);
      if ((iVar8 != 0) && (iVar8 = tile_improvements(x,y), iVar8 == 0)) {
        local_8 = 0;
        uVar2 = tile_terrain(x,y);
        switch(uVar2) {
        case 0:
          local_8 = 1;
          break;
        case 1:
          local_8 = 4;
          break;
        case 2:
          iVar8 = tile_grassland_has_shield(x,y);
          if (iVar8 == 0) {
            local_8 = 3;
          }
          else {
            local_8 = 5;
          }
          break;
        case 4:
          local_8 = 2;
        }
        if (local_8 != 0) {
          if (local_10 < 8) {
            local_8++;
          }
          y = tile_resource(x,y);
          if (y != 0) {
            local_8 += 3;
          }
          if (local_c < local_8) {
            local_c = local_8;
            local_30 = local_10;
          }
        }
      }
    }
    if (local_30 < 0) break;
    x = map_wrap_x((char)(&city_tile_dx_table)[local_30] + x2);
    y = (char)(&city_tile_dy_table)[local_30] + y2;
    cVar3 = tile_terrain(x,y);
    tile_at(x,y);
    tile_set_improvements(x,y,0x10,1,1);
    if (cVar3 == 4) {
      tile_set_improvements(x,y,8,1,1);
    }
    else {
      tile_set_improvements(x,y,4,1,1);
    }
    tile_update_known(x,y,(int)cities[city].owner);
  }
  civ = cities[city].owner;
  for (local_10 = 0; local_10 < 0x2d; local_10++) {
    x = map_wrap_x((char)(&city_tile_dx_table)[local_10] + x2);
    y = (char)(&city_tile_dy_table)[local_10] + y2;
    iVar8 = map_in_bounds(x,y);
    if ((iVar8 != 0) && (iVar8 = tile_is_ocean(x,y), iVar8 == 0)) {
      iVar8 = tile_landmass((int)cities[city].x,(int)cities[city].y);
      iVar9 = tile_landmass(x,y);
      if (iVar8 == iVar9) {
        tile_set_visible(x,y,1 << (civ & 0x1f) & 0xff,1,1);
      }
    }
  }
  net_batch_flush();
  return;
}
#undef local_30
#undef local_18
#undef local_10
#undef local_c
#undef local_8

/* 004bb570 auto */
void __thiscall wnd_move_to_rect(WndBase *this,iptr param_1)

{
  wnd_obj_move_to_rect(this->native_wnd,param_1);
  return;
}

/* 004c4240 auto */
void __cdecl popup_game_with_advance(iptr param_1,iptr advance,i32 param_3)

{
  popup_text_with_advance(ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),param_1,0,advance,param_3);
  return;
}

/* 004cc870 auto */
i32 __cdecl popup_game_with_improvement(iptr param_1,iptr param_2,i32 param_3)

{
  i32 uVar1;
  
  uVar1 = popup_text_with_improvement(ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),param_1,0,param_2,param_3);
  return uVar1;
}

/* 004cc8b0 auto */
i32 __cdecl popup_game_with_unit(iptr param_1,i32 param_2,iptr param_3)

{
  i32 uVar1;
  
  uVar1 = popup_text_with_unit(ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),param_1,param_2,param_3);
  return uVar1;
}

/* 004cff70 auto */
void __thiscall wnd_set_resize_border(WndBase *this,i32 param_1)

{
  wnd_obj_set_resize_border(this->native_wnd,param_1);
  return;
}

/* 004e01b0 auto */
#define local_30c (*(Dialog *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(iptr *)(frame_ + FRAME_OFF(760)))
#define local_14 (*(iptr *)(frame_ + FRAME_OFF(764)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(768)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(772)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(776)))
void __cdecl menu_wonder_movies(void)

{
  iptr iVar1;
  i32 uVar2;
  iptr iVar2;
  i8 frame_[FRAME_OFF(784)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_30c,0x4000);
  local_8 = 0;
  local_14 = 0;
  while( true ) {
    dlg_reset(&local_30c,0x1001);
    dialog_set_width((DialogWindowView *)&local_30c,0x1b8);
    dialog_set_listbox((DialogTextView *)&local_30c,0x10,0x1b8,0);
    for (local_18 = 0; local_18 < 0x1c; local_18++) {
      uVar2 = 0;
      iVar2 = local_18;
      iVar1 = label_string(improvements[local_18 + 0x27].name);
      dialog_add_option((DialogOptionList *)&local_30c,iVar1,iVar2,uVar2);
    }
    dialog_set_default_choice((DialogOptionList *)&local_30c,local_14);
    local_18 = dlg_show_modal(&local_30c,0);
    local_14 = local_18;
    if (local_18 < 0) break;
    wonder_show_movie(local_18);
  }
  local_8 = 0xffffffff;
  /* inlined unwind funclet 004e02cb */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
  return;
}
#undef local_30c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004e02ef auto */
#define minimap_hidden (*(i8 *)((u8 *)&g.d_00624ee0))
#define panel_margin_x (*(int *)((u8 *)&g.d_0062d858))
#define status_wnd_hidden (*(i8 *)((u8 *)&g.d_00633e00))
#define local_20 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(24)))
void __cdecl ui_reset_window_layout(void)

{
  int iVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  wnd_maximize((WndBase *)&main_frame_wnd);
  city_window_init_size();
  wnd_show_restored((WndBase *)&city_window_wnd);
  wnd_move_to_rect((WndBase *)&city_window_wnd,ADDR(0x655344, ((u8 *)&g.d_00655344)));
  city_window_close();
  minimap_calc_rect();
  wnd_show_restored((WndBase *)&minimap_wnd);
  minimap_hidden = 0;
  wnd_move_to_rect((WndBase *)&minimap_wnd,ADDR(0x655324, ((u8 *)&g.d_00655324)));
  wnd_repaint((SurfaceWindow *)&minimap_window);
  status_calc_wnd_rect();
  wnd_show_restored((WndBase *)&status_window_wnd);
  status_wnd_hidden = 0;
  wnd_move_to_rect((WndBase *)&status_window_wnd,ADDR(0x655334, ((u8 *)&g.d_00655334)));
  wnd_repaint((SurfaceWindow *)&status_window);
  if (parley_large_layout == 0) {
    local_14 = 0x208;
    local_18 = 0x14f;
    local_1c = font_cached_height((GameFont *)&font_size20);
  }
  else {
    local_14 = 800;
    local_18 = 0x1cc;
    local_1c = font_cached_height((GameFont *)&font_size30);
  }
  parley_caption_height = panel_margin_y * 2 + panel_bevel_width * 2 + local_1c;
  local_14 = local_14 + (panel_padding_x + panel_margin_x) * 2 + 6;
  local_18 = local_18 + panel_margin_y * 2 + parley_caption_height * 2 + 0xe;
  iVar1 = wnd_client_width((WndBase *)&main_frame_wnd);
  iVar1 = (iVar1 >> 1) - (local_14 >> 1);
  parley_wnd_x = iVar1;
  iVar2 = wnd_client_height((WndBase *)&main_frame_wnd);
  parley_wnd_y = (iVar2 >> 1) - (local_18 >> 1);
  SetRect(parley_wnd_rect_ptr,iVar1,parley_wnd_y,iVar1 + local_14,parley_wnd_y + local_18);
  wnd_move_to_rect((WndBase *)&parley_wnd_frame,(iptr)parley_wnd_rect_ptr);
  if (chat_wnd_large_layout == 0) {
    local_14 = 0x208;
    local_18 = 0x14f;
    local_20 = font_cached_height((GameFont *)&font_size20);
  }
  else {
    local_14 = 800;
    local_18 = 0x1cc;
    local_20 = font_cached_height((GameFont *)&font_size30);
  }
  chat_wnd_row_height = panel_margin_y * 2 + panel_bevel_width * 2 + local_20;
  local_14 = local_14 + (panel_padding_x + panel_margin_x) * 2 + 6;
  local_18 = local_18 + panel_margin_y * 2 + chat_wnd_row_height * 2 + 0xe;
  iVar1 = wnd_client_width((WndBase *)&main_frame_wnd);
  iVar1 = (iVar1 >> 1) - (local_14 >> 1);
  chat_wnd_x = iVar1;
  iVar2 = wnd_client_height((WndBase *)&main_frame_wnd);
  chat_wnd_y = (iVar2 >> 1) - (local_18 >> 1);
  SetRect(chat_wnd_init_rect,iVar1,chat_wnd_y,iVar1 + local_14,chat_wnd_y + local_18);
  wnd_move_to_rect((WndBase *)&chat_wnd_frame,(iptr)chat_wnd_init_rect);
  for (local_8 = 1; local_8 < 8; local_8++) {
    if (*(short *)(&map_view_open_flags + local_8 * 0x3f0) != 0) {
      *(i16 *)(&map_view_open_flags + local_8 * 0x3f0) = 0;
      wnd_destroy_with_surface((DibSurface *)(&map_views + local_8 * 0x3f0));
    }
  }
  mapview_calc_rect();
  wnd_show_restored((WndBase *)&map_view_wnds);
  wnd_move_to_rect((WndBase *)&map_view_wnds,ADDR(0x6552a4, ((u8 *)&g.d_006552a4)));
  wnd_repaint((SurfaceWindow *)&map_views);
  ui_flush_input();
  return;
}
#undef minimap_hidden
#undef panel_margin_x
#undef status_wnd_hidden
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef local_8

/* 004e068d auto */
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define minimap_hidden (*(i8 *)((u8 *)&g.d_00624ee0))
#define moving_units_mode (*(i32 *)((u8 *)&g.d_006d1da8))
#define mp_turn_time_limit_ms (*(int *)((u8 *)&g.d_00654b70))
#define saved_layout_valid (*(int *)((u8 *)&g.d_00655280))
#define saved_turn_civ (*(byte *)((u8 *)&g.d_00654fa4))
#define status_wnd_hidden (*(i8 *)((u8 *)&g.d_00633e00))
#define turn_resume_civ (*(byte *)((u8 *)&g.d_00628048))
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl menu_load_game(void)

{
  byte bVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  mp_turn_timer_stop(1);
  city_window_close();
  parley_wnd_close();
  chat_wnd_close();
  pedia_close();
  picwnd_close((PictureWindowCore *)&advisor_window);
  picwnd_close((PictureWindowCore *)&casualty_window);
  bVar1 = (byte)game.game_options & 8;
  iVar2 = game_load_dialog(0,0,0);
  if (iVar2 == 0) {
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
      if (bVar1 == 0) {
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
      wnd_move_to_rect((WndBase *)&map_view_wnds,ADDR(0x6552a4, ((u8 *)&g.d_006552a4)));
      mapview_update_title((FrameWindow *)&map_views);
      wnd_repaint((SurfaceWindow *)&map_views);
      for (local_8 = 1; local_8 < 8; local_8++) {
        if (*(short *)(&map_view_open_flags + local_8 * 0x3f0) != 0) {
          mapview_create((ViewWindow *)(&map_views + local_8 * 0x3f0));
          wnd_move_to_rect
                    ((WndBase *)(&map_view_wnds + local_8 * 0x3f0),
                     (iptr)(&map_view_saved_rects + local_8 * 0x10));
          mapview_update_title((FrameWindow *)(&map_views + local_8 * 0x3f0));
          wnd_repaint((SurfaceWindow *)(&map_views + local_8 * 0x3f0));
        }
      }
    }
    else {
      wnd_maximize((WndBase *)&main_frame_wnd);
      wnd_show_restored((WndBase *)&city_window_wnd);
      wnd_move_to_rect((WndBase *)&city_window_wnd,ADDR(0x655344, ((u8 *)&g.d_00655344)));
      city_window_close();
      wnd_show_restored((WndBase *)&minimap_wnd);
      minimap_hidden = 0;
      wnd_move_to_rect((WndBase *)&minimap_wnd,ADDR(0x655324, ((u8 *)&g.d_00655324)));
      wnd_repaint((SurfaceWindow *)&minimap_window);
      wnd_show_restored((WndBase *)&status_window_wnd);
      status_wnd_hidden = 0;
      wnd_move_to_rect((WndBase *)&status_window_wnd,ADDR(0x655334, ((u8 *)&g.d_00655334)));
      wnd_repaint((SurfaceWindow *)&status_window);
      wnd_show_restored((WndBase *)&map_view_wnds);
      wnd_move_to_rect((WndBase *)&map_view_wnds,ADDR(0x6552a4, ((u8 *)&g.d_006552a4)));
      mapview_update_title((FrameWindow *)&map_views);
      wnd_repaint((SurfaceWindow *)&map_views);
      for (local_8 = 1; local_8 < 8; local_8++) {
        if (*(short *)(&map_view_open_flags + local_8 * 0x3f0) != 0) {
          mapview_create((ViewWindow *)(&map_views + local_8 * 0x3f0));
          wnd_move_to_rect
                    ((WndBase *)(&map_view_wnds + local_8 * 0x3f0),
                     (iptr)(&map_view_saved_rects + local_8 * 0x10));
          mapview_update_title((FrameWindow *)(&map_views + local_8 * 0x3f0));
          wnd_repaint((SurfaceWindow *)(&map_views + local_8 * 0x3f0));
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
#undef local_8

/* 004e0a8c auto */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __cdecl dlg_check_set_bool(i32 param_1,int param_2)

{
  dlg_check_set(param_1,(uint)(param_2 != 0));
  return;
}

/* 004e0ab0 auto */
#define prefs_game_options (*(u32 *)((u8 *)&g.d_0064bc1e))
void __cdecl menu_game_options(void)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = game.game_options & 8;
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
  iVar2 = popup_game_flags(ADDR(0x62eb38, ((u8 *)&g.d_0062eb38)),1);
  if (iVar2 == 0) {
    game.game_options = game.game_options & 0xffff8027;
    iVar2 = dlg_check_get(0);
    if (iVar2 != 0) {
      game.game_options = game.game_options | 0x10;
    }
    iVar2 = dlg_check_get(1);
    if (iVar2 == 0) {
      snd_cd_stop();
    }
    else {
      game.game_options = game.game_options | 8;
      if (uVar1 == 0) {
        snd_cd_mci_stop();
        snd_cd_close();
        snd_cd_open();
        snd_cd_detect_layout();
      }
      snd_sync_music_option();
    }
    iVar2 = dlg_check_get(2);
    if (iVar2 != 0) {
      game.game_options = game.game_options | 0x4000;
    }
    iVar2 = dlg_check_get(3);
    if (iVar2 != 0) {
      game.game_options = game.game_options | 0x2000;
    }
    iVar2 = dlg_check_get(4);
    if (iVar2 != 0) {
      game.game_options = game.game_options | 0x1000;
    }
    iVar2 = dlg_check_get(5);
    if (iVar2 != 0) {
      game.game_options = game.game_options | 0x800;
    }
    iVar2 = dlg_check_get(6);
    if (iVar2 != 0) {
      game.game_options = game.game_options | 0x400;
    }
    iVar2 = dlg_check_get(7);
    if (iVar2 != 0) {
      game.game_options = game.game_options | 0x200;
    }
    iVar2 = dlg_check_get(8);
    if (iVar2 != 0) {
      game.game_options = game.game_options | 0x100;
    }
    iVar2 = dlg_check_get(9);
    if (iVar2 != 0) {
      game.game_options = game.game_options | 0x80;
    }
    iVar2 = dlg_check_get(10);
    if (iVar2 != 0) {
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
  uint uVar1;
  int iVar2;
  
  uVar1 = game.game_options & 0x200000;
  dlg_checks_clear();
  dlg_check_set_bool(0,game.game_options & 0x20000);
  dlg_check_set_bool(1,game.game_options & 0x40000);
  dlg_check_set_bool(2,game.game_options & 0x200000);
  dlg_check_set_bool(3,game.game_options & 0x80000);
  dlg_check_set_bool(4,game.game_options & 0x100000);
  dlg_check_set_bool(5,game.game_options & 0x10000);
  iVar2 = popup_game_flags(ADDR(0x62eb44, ((u8 *)&g.d_0062eb44)),1);
  if (iVar2 == 0) {
    game.game_options = game.game_options & 0xffc0ffff;
    iVar2 = dlg_check_get(0);
    if (iVar2 != 0) {
      game.game_options = game.game_options | 0x20000;
    }
    iVar2 = dlg_check_get(1);
    if (iVar2 != 0) {
      game.game_options = game.game_options | 0x40000;
    }
    iVar2 = dlg_check_get(2);
    if (iVar2 != 0) {
      if (uVar1 == 0) {
        iVar2 = mem_check_available(0x800000);
        if (iVar2 == 0) {
          popup_game(ADDR(0x62eb54, ((u8 *)&g.d_0062eb54)));
        }
      }
      game.game_options = game.game_options | 0x200000;
    }
    iVar2 = dlg_check_get(3);
    if (iVar2 != 0) {
      game.game_options = game.game_options | 0x80000;
    }
    iVar2 = dlg_check_get(4);
    if (iVar2 != 0) {
      game.game_options = game.game_options | 0x100000;
    }
    iVar2 = dlg_check_get(5);
    if (iVar2 != 0) {
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
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl menu_multiplayer_options(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  dlg_checks_clear();
  dlg_check_set_bool(0,(int)(short)prefs_clear_chat_on_new_game);
  dlg_check_set_bool(1,(int)(short)prefs_clear_chat_on_boot);
  if (net_host_flag != '\0') {
    dlg_check_set_bool(2,(int)(short)mp_double_production);
    dlg_check_set_bool(3,(int)(short)mp_double_moves);
  }
  if (((game.multiplayer < 3) || (net_host_flag == '\0')) && (2 < game.multiplayer)) {
    local_8 = popup_game_flags(ADDR(0x62eb74, ((u8 *)&g.d_0062eb74)),1);
  }
  else {
    local_8 = popup_game_flags(ADDR(0x62eb60, ((u8 *)&g.d_0062eb60)),1);
  }
  if (local_8 == 0) {
    iVar1 = dlg_check_get(0);
    prefs_clear_chat_on_new_game = (ushort)(iVar1 != 0);
    iVar1 = dlg_check_get(1);
    prefs_clear_chat_on_boot = (ushort)(iVar1 != 0);
    prefs_save_civ2dat();
    if (((2 < game.multiplayer) && (net_host_flag != '\0')) || (game.multiplayer < 3)) {
      iVar1 = dlg_check_get(2);
      prefs_mp_double_production = (ushort)(iVar1 != 0);
      iVar1 = dlg_check_get(3);
      prefs_mp_double_moves = (ushort)(iVar1 != 0);
      if ((mp_double_production != prefs_mp_double_production) || (mp_double_moves != prefs_mp_double_moves)) {
        if ((2 < game.multiplayer) && (1 < net_player_count)) {
          crt_strcpy(&text_string_args,&net_local_player_name);
          str_clear(ADDR(0x63cd4c, ((u8 *)&g.d_0063cd4c)));
          str_append_label(ADDR(0x63cd4c, ((u8 *)&g.d_0063cd4c)),0x350 - (uint)(prefs_mp_double_production == 0));
          crt_strcat(&text_string_arg1,&mp_options_vote_sep_str);
          str_append_label(ADDR(0x63cd4c, ((u8 *)&g.d_0063cd4c)),0x352 - (uint)(prefs_mp_double_moves == 0));
          net_vote_replies_pending = net_player_count - 1;
          net_vote_status = 0;
          net_send_text_args(0x43,0xff,2,0,0,0);
          dlg_pending_idle_callback = ((void *)ADDR(0x004019b5, net_vote_wait_idle_cb));
          dialog_timeout_start_i32 = timer_ticks();
          iVar1 = popup_game_sprite_flags(ADDR(0x62eb8c, ((u8 *)&g.d_0062eb8c)),0x2000001,ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
          if (((iVar1 < 0) || (net_vote_status == -1)) || (net_vote_replies_pending != 0)) {
            prefs_mp_double_production = mp_double_production;
            prefs_mp_double_moves = mp_double_moves;
            net_send_text_args(0x44,0xff,0,0,0,0);
            popup_game_with_sprite(ADDR(0x62eb9c, ((u8 *)&g.d_0062eb9c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
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
          popup_game_with_sprite(ADDR(0x62eba8, ((u8 *)&g.d_0062eba8)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
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
#undef local_8

/* 004e1452 auto */
#define prefs_message_options (*(u16 *)((u8 *)&g.d_0064bc22))
void __cdecl menu_message_options(void)

{
  int iVar1;
  
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
  iVar1 = popup_game_flags(ADDR(0x62ebb4, ((u8 *)&g.d_0062ebb4)),1);
  if (iVar1 == 0) {
    game.message_options = 0;
    iVar1 = dlg_check_get(0);
    if (iVar1 == 0) {
      game.message_options = game.message_options | 1;
    }
    iVar1 = dlg_check_get(1);
    if (iVar1 == 0) {
      game.message_options = game.message_options | 2;
    }
    iVar1 = dlg_check_get(2);
    if (iVar1 == 0) {
      game.message_options = game.message_options | 4;
    }
    iVar1 = dlg_check_get(3);
    if (iVar1 == 0) {
      game.message_options = game.message_options | 8;
    }
    iVar1 = dlg_check_get(4);
    if (iVar1 == 0) {
      game.message_options = game.message_options | 0x10;
    }
    iVar1 = dlg_check_get(5);
    if (iVar1 == 0) {
      game.message_options = game.message_options | 0x20;
    }
    iVar1 = dlg_check_get(6);
    if (iVar1 == 0) {
      game.message_options = game.message_options | 0x40;
    }
    iVar1 = dlg_check_get(7);
    if (iVar1 == 0) {
      game.message_options = game.message_options | 0x80;
    }
    iVar1 = dlg_check_get(8);
    if (iVar1 == 0) {
      game.message_options = game.message_options | 0x100;
    }
    iVar1 = dlg_check_get(9);
    if (iVar1 == 0) {
      game.message_options = game.message_options | 0x200;
    }
    iVar1 = dlg_check_get(10);
    if (iVar1 == 0) {
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
  popup_game(ADDR(0x62ec5c, ((u8 *)&g.d_0062ec5c)));
  map_show_hidden_terrain = 0;
  map_redraw_all_views(human_civ,1);
  return;
}
#undef human_civ
#undef map_show_hidden_terrain
#undef unit_blink_active

/* 004e25ef auto */
#define cd_music_current_track (*(int *)((u8 *)&g.d_0062b428))
#define local_30c (*(Dialog *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(760)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(764)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(768)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(772)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(776)))
void __cdecl menu_select_music(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(784)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_30c,0x4000);
  local_8 = 0;
  local_14 = 0;
  while (local_14 < 5) {
    local_14++;
    local_18 = snd_cd_get_track_count();
    if ((((local_18 == 0x18) || (local_18 == 0x12)) || (local_18 == 0xc)) || (local_18 == 10))
    break;
    if (local_18 == -1) {
      snd_cd_close();
    }
    Sleep(200);
  }
  if (local_18 == -1) {
    popup_game(ADDR(0x62ec6c, ((u8 *)&g.d_0062ec6c)));
    local_8 = 0xffffffff;
    /* inlined unwind funclet 004e27df */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
  }
  else {
    if (local_18 == 0x18) {
      dlg_load_game_section(&local_30c,ADDR(0x62ec7c, ((u8 *)&g.d_0062ec7c)),1);
    }
    else if (local_18 == 0x12) {
      dlg_load_game_section(&local_30c,ADDR(0x62ec90, ((u8 *)&g.d_0062ec90)),1);
    }
    else if (local_18 == 0xc) {
      dlg_load_game_section(&local_30c,ADDR(0x62eca4, ((u8 *)&g.d_0062eca4)),1);
    }
    else {
      if (local_18 != 10) {
        popup_game(ADDR(0x62ecc0, ((u8 *)&g.d_0062ecc0)));
        local_8 = 0xffffffff;
        /* inlined unwind funclet 004e27df */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
        goto LAB_004e27f5;
      }
      dlg_load_game_section(&local_30c,ADDR(0x62ecb4, ((u8 *)&g.d_0062ecb4)),1);
    }
    if (1 < cd_music_current_track) {
      dialog_set_default_choice((DialogOptionList *)&local_30c,cd_music_current_track - 2);
    }
    iVar1 = dlg_show_modal(&local_30c,0);
    if (iVar1 < 0) {
      local_8 = 0xffffffff;
      /* inlined unwind funclet 004e27df */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
    }
    else {
      music_play_track(iVar1 + 2,1);
      local_8 = 0xffffffff;
      /* inlined unwind funclet 004e27df */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
    }
  }
LAB_004e27f5:
  return;
}
#undef cd_music_current_track
#undef local_30c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

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

void __cdecl menu_command(i32 param_1,int param_2)

{
  SHORT SVar1;
  int iVar2;
  
  iVar2 = XD_InFlushSendBuffer();
  if ((((((((iVar2 == 0) && (unit_create_busy == 0)) && (unit_delete_busy == 0)) &&
         ((city_create_busy == 0 && (city_delete_busy == 0)))) && (net_lock_map_busy == 0)) &&
       (((net_unlock_map_busy == 0 && (unit_stack_unlink_busy == 0)) &&
        ((unit_stack_link_busy == 0 && (((unit_stack_bottom_busy == 0 && (unit_relocate_busy == 0)) && (city_acquire_wonder_busy == 0)))
         ))))) && ((civ_eliminate_busy == 0 && (civ_create_busy == 0)))) &&
     ((civ_check_destroyed_busy == 0 &&
      (((unit_gather_cargo_busy == 0 && (unit_lift_off_map_busy == 0)) && ((unit_delete_cargo_busy == 0 && (unit_destroy_redraw_busy == 0)))))
      ))) {
    if (city_turn_processing == 0) {
      iVar2 = ui_paradrop_cursor_active();
      if ((iVar2 == 0) || (mapviews_reset_cursor(), param_2 != 0x441)) {
        if (param_2 < 0x111) {
          if (param_2 == 0x110) {
            game_save_dialog(0);
          }
          else {
            switch(param_2) {
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
        else if (param_2 < 0x131) {
          if (param_2 == 0x130) {
            game_join_dialog();
          }
          else if (param_2 == 0x120) {
            menu_load_game();
          }
        }
        else if (param_2 < 0x1f1) {
          if (param_2 == 0x1f0) {
            game_quit_or_retire(1);
          }
          else if (param_2 == 0x131) {
            civ_change_password_dialog(human_civ);
          }
          else if (param_2 == 0x132) {
            mp_cmd_change_timer();
          }
        }
        else if (param_2 < 0x202) {
          if (param_2 == 0x201) {
            taxrate_dialog_show(human_civ);
          }
          else if (param_2 == 0x1f1) {
            game_quit_or_retire(0);
          }
          else if ((param_2 == 0x1f2) && (game.multiplayer == 1)) {
            iVar2 = popup_game_with_sprite(ADDR(0x62ed14, ((u8 *)&g.d_0062ed14)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
            if (iVar2 == 0) {
              return;
            }
            snd_cd_stop();
            map_display_disable();
            return;
          }
        }
        else if (param_2 < 0x211) {
          if (param_2 == 0x210) {
            menu_find_city();
          }
          else if (param_2 == 0x205) {
            throneroom_show(human_civ);
          }
        }
        else if (param_2 < 0x302) {
          if (param_2 == 0x301) {
            ui_focus_active_unit(1);
          }
          else if (param_2 == 0x220) {
            menu_revolution();
          }
        }
        else if (param_2 < 0x311) {
          if (param_2 == 0x310) {
            if (mapview_zoom < 8) {
              mapview_zoom++;
              mapview_redraw((ViewWindow *)&map_views,human_civ,1);
            }
          }
          else if (param_2 == 0x302) {
            ui_redraw_all_maps(0);
          }
        }
        else if (param_2 < 0x321) {
          if (param_2 == 800) {
            mapview_zoom = 8;
            mapview_redraw((ViewWindow *)&map_views,human_civ,1);
          }
          else if ((param_2 == 0x311) && (-7 < mapview_zoom)) {
            mapview_zoom--;
            mapview_redraw((ViewWindow *)&map_views,human_civ,1);
          }
        }
        else if (param_2 < 0x331) {
          if (param_2 == 0x330) {
            menu_show_hidden_terrain();
          }
          else {
            switch(param_2) {
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
        else if (param_2 < 0x402) {
          if (param_2 == 0x401) {
            unit_cmd_build_city();
          }
          else if (param_2 == 0x340) {
            mapview_center_on
                      ((ViewWindow *)&map_views,(int)map_cursor_x,(int)map_cursor_y);
          }
        }
        else if (param_2 < 0x431) {
          if (param_2 == 0x430) {
            unit_cmd_unload();
          }
          else {
            switch(param_2) {
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
        else if (param_2 < 0x451) {
          if (param_2 == 0x450) {
            unit_cmd_fortify();
          }
          else {
            switch(param_2) {
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
        else if (param_2 < 0x461) {
          if (param_2 == 0x460) {
            unit_cmd_disband();
          }
          else if (param_2 == 0x451) {
            unit_cmd_sleep();
          }
        }
        else if (param_2 < 0x471) {
          if (param_2 == 0x470) {
            unit_cmd_wait();
          }
          else if (param_2 == 0x468) {
            ui_pick_unit_from_stack();
          }
        }
        else if (param_2 < 0x491) {
          if (param_2 == 0x490) {
            cmd_end_player_turn();
          }
          else if (param_2 == 0x480) {
            cmd_unit_skip_turn();
          }
        }
        else if (param_2 < 0x602) {
          if (param_2 == 0x601) {
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
            switch(param_2) {
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
        else if (param_2 < 0x702) {
          if (param_2 == 0x701) {
            if ((game.multiplayer == '\0') || (mp_cheat_menu_allowed != 0)) {
              cheat_toggle_mode();
            }
          }
          else {
            switch(param_2) {
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
        else if (param_2 < 0x722) {
          if (param_2 == 0x721) {
            if (((game.game_options & 0x8000) != 0) && (game.multiplayer == '\0')) {
              cheat_set_game_year();
            }
          }
          else if (param_2 == 0x711) {
            if (((game.game_options & 0x8000) != 0) && (game.multiplayer == '\0')) {
              cheat_create_unit();
            }
          }
          else if (param_2 == 0x712) {
            if (((game.game_options & 0x8000) != 0) && (game.multiplayer == '\0')) {
              cheat_reveal_map();
            }
          }
          else if (((param_2 == 0x713) && ((game.game_options & 0x8000) != 0)) &&
                  (game.multiplayer == '\0')) {
            cheat_set_human_player();
          }
        }
        else if (param_2 < 0x732) {
          if (param_2 == 0x731) {
            if (((game.game_options & 0x8000) != 0) && (game.multiplayer == '\0')) {
              cheat_tech_advance();
            }
          }
          else if (((param_2 == 0x722) && ((game.game_options & 0x8000) != 0)) &&
                  (game.multiplayer == '\0')) {
            cheat_kill_civ();
          }
        }
        else if (param_2 < 0x741) {
          if (param_2 == 0x740) {
            if (((game.game_options & 0x8000) != 0) && (game.multiplayer == '\0')) {
              cheat_force_government();
            }
          }
          else if (((param_2 == 0x732) && ((game.game_options & 0x8000) != 0)) &&
                  (game.multiplayer == '\0')) {
            cheat_edit_technologies();
          }
        }
        else if (param_2 < 0x751) {
          if (param_2 == 0x750) {
            if (((game.game_options & 0x8000) != 0) && (game.multiplayer == '\0')) {
              cheat_destroy_units_at_cursor();
              ui_focus_active_unit(0);
            }
          }
          else if (((param_2 == 0x748) && ((game.game_options & 0x8000) != 0)) &&
                  (game.multiplayer == '\0')) {
            cheat_terrain_saved_bits = 0xffffffff;
            cheat_change_terrain();
          }
        }
        else if (param_2 < 0x756) {
          if (param_2 == 0x755) {
            if (((game.game_options & 0x8000) != 0) && (game.multiplayer == '\0')) {
              cheat_edit_unit();
            }
          }
          else if (((param_2 == 0x752) && ((game.game_options & 0x8000) != 0)) &&
                  (game.multiplayer == '\0')) {
            cheat_change_money();
          }
        }
        else if (param_2 < 0x766) {
          if (param_2 == 0x765) {
            if (((game.game_options & 0x8000) != 0) && (game.multiplayer == '\0')) {
              cheat_edit_king();
            }
          }
          else if (((param_2 == 0x760) && ((game.game_options & 0x8000) != 0)) &&
                  (game.multiplayer == '\0')) {
            cheat_edit_city();
          }
        }
        else if (param_2 < 0x771) {
          if (param_2 == 0x770) {
            if (((game.game_options & 0x8000) != 0) && (game.multiplayer == '\0')) {
              cheat_save_as_scenario();
            }
          }
          else if (((param_2 == 0x768) && ((game.game_options & 0x8000) != 0)) &&
                  (game.multiplayer == '\0')) {
            cheat_scenario_params();
          }
        }
        else if (param_2 < 0x902) {
          if (param_2 == 0x901) {
            pedia_open_category((MediaWindow *)&pedia_window,1,1);
          }
          else {
            switch(param_2) {
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
          switch(param_2) {
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
            if ((param_2 == 0x905) &&
               (SVar1 = GetAsyncKeyState(0x10), (char)((ushort)SVar1 >> 8) != '\0')) {
              menu_wonder_movies();
            }
            else {
              pedia_open_category((MediaWindow *)&pedia_window,7,1);
            }
            break;
          case 0x9f0:
            if (game.multiplayer < 3) {
              iVar2 = popup_game_flags(ADDR(0x62ed20, ((u8 *)&g.d_0062ed20)),1);
              if (-1 < iVar2) {
                credits_show(iVar2);
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
    dbg_log(ADDR(0x62ecd0, ((u8 *)&g.d_0062ecd0)));
    blocked_input_kind = 5;
    blocked_input_arg1_i32 = param_1;
    blocked_input_arg2_i32 = param_2;
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
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(8)))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(16)))
void __cdecl menu_build_main(void)

{
  int iVar1;
  i32 uVar2;
  iptr iVar3;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  menu_reset((GameMenu *)&main_menu,0x1bbc);
  iVar1 = text_open_section(ADDR(0x62ed34, ((u8 *)&g.d_0062ed34)),ADDR(0x62ed2c, ((u8 *)&g.d_0062ed2c)));
  if (iVar1 == 0) {
    uVar2 = text_read_line(1);
    menu_add_menu((GameMenu *)&main_menu,1,uVar2);
    uVar2 = 0;
    iVar3 = text_read_line(1);
    menu_add_item((GameMenu *)&main_menu,1,0x101,iVar3,uVar2);
    uVar2 = 0;
    iVar3 = text_read_line(1);
    menu_add_item((GameMenu *)&main_menu,1,0x102,iVar3,uVar2);
    uVar2 = 0;
    iVar3 = text_read_line(1);
    menu_add_item((GameMenu *)&main_menu,1,0x103,iVar3,uVar2);
    uVar2 = 0;
    iVar3 = text_read_line(1);
    menu_add_item((GameMenu *)&main_menu,1,0x104,iVar3,uVar2);
    uVar2 = 0;
    iVar3 = text_read_line(1);
    menu_add_item((GameMenu *)&main_menu,1,0x105,iVar3,uVar2);
    menu_add_item((GameMenu *)&main_menu,1,0,0,0);
    uVar2 = 0;
    iVar3 = text_read_line(1);
    menu_add_item((GameMenu *)&main_menu,1,0x106,iVar3,uVar2);
    menu_add_item((GameMenu *)&main_menu,1,0,0,0);
    uVar2 = 0;
    iVar3 = text_read_line(1);
    menu_add_item((GameMenu *)&main_menu,1,0x110,iVar3,uVar2);
    uVar2 = 0;
    iVar3 = text_read_line(1);
    menu_add_item((GameMenu *)&main_menu,1,0x120,iVar3,uVar2);
    uVar2 = 0;
    iVar3 = text_read_line(1);
    menu_add_item((GameMenu *)&main_menu,1,0x130,iVar3,uVar2);
    menu_add_item((GameMenu *)&main_menu,1,0,0,0);
    uVar2 = 0;
    iVar3 = text_read_line(1);
    menu_add_item((GameMenu *)&main_menu,1,0x131,iVar3,uVar2);
    uVar2 = 0;
    iVar3 = text_read_line(1);
    menu_add_item((GameMenu *)&main_menu,1,0x132,iVar3,uVar2);
    menu_add_item((GameMenu *)&main_menu,1,0,0,0);
    uVar2 = 0;
    iVar3 = text_read_line(1);
    menu_add_item((GameMenu *)&main_menu,1,0x1f0,iVar3,uVar2);
    uVar2 = 0;
    iVar3 = text_read_line(1);
    menu_add_item((GameMenu *)&main_menu,1,0x1f1,iVar3,uVar2);
    iVar1 = text_open_section(0,ADDR(0x62ed3c, ((u8 *)&g.d_0062ed3c)));
    if (iVar1 == 0) {
      uVar2 = text_read_line(1);
      menu_add_menu((GameMenu *)&main_menu,2,uVar2);
      uVar2 = 0;
      iVar3 = text_read_line(1);
      menu_add_item((GameMenu *)&main_menu,2,0x201,iVar3,uVar2);
      menu_add_item((GameMenu *)&main_menu,2,0,0,0);
      uVar2 = 0;
      iVar3 = text_read_line(1);
      menu_add_item((GameMenu *)&main_menu,2,0x205,iVar3,uVar2);
      uVar2 = 0;
      iVar3 = text_read_line(1);
      menu_add_item((GameMenu *)&main_menu,2,0x210,iVar3,uVar2);
      menu_add_item((GameMenu *)&main_menu,2,0,0,0);
      uVar2 = 0;
      iVar3 = text_read_line(1);
      menu_add_item((GameMenu *)&main_menu,2,0x220,iVar3,uVar2);
      iVar1 = text_open_section(0,ADDR(0x62ed44, ((u8 *)&g.d_0062ed44)));
      if (iVar1 == 0) {
        uVar2 = text_read_line(1);
        menu_add_menu((GameMenu *)&main_menu,3,uVar2);
        uVar2 = 0;
        iVar3 = text_read_line(1);
        menu_add_item((GameMenu *)&main_menu,3,0x301,iVar3,uVar2);
        uVar2 = 0;
        iVar3 = text_read_line(1);
        menu_add_item((GameMenu *)&main_menu,3,0x302,iVar3,uVar2);
        menu_add_item((GameMenu *)&main_menu,3,0,0,0);
        uVar2 = 0;
        iVar3 = text_read_line(1);
        menu_add_item((GameMenu *)&main_menu,3,0x310,iVar3,uVar2);
        uVar2 = 0;
        iVar3 = text_read_line(1);
        menu_add_item((GameMenu *)&main_menu,3,0x311,iVar3,uVar2);
        menu_add_item((GameMenu *)&main_menu,3,0,0,0);
        uVar2 = 0;
        iVar3 = text_read_line(1);
        menu_add_item((GameMenu *)&main_menu,3,800,iVar3,uVar2);
        uVar2 = 0;
        iVar3 = text_read_line(1);
        menu_add_item((GameMenu *)&main_menu,3,0x321,iVar3,uVar2);
        uVar2 = 0;
        iVar3 = text_read_line(1);
        menu_add_item((GameMenu *)&main_menu,3,0x322,iVar3,uVar2);
        uVar2 = 0;
        iVar3 = text_read_line(1);
        menu_add_item((GameMenu *)&main_menu,3,0x324,iVar3,uVar2);
        menu_add_item((GameMenu *)&main_menu,3,0,0,0);
        uVar2 = 0;
        iVar3 = text_read_line(1);
        menu_add_item((GameMenu *)&main_menu,3,0x327,iVar3,uVar2);
        uVar2 = 0;
        iVar3 = text_read_line(1);
        menu_add_item((GameMenu *)&main_menu,3,0x328,iVar3,uVar2);
        uVar2 = 0;
        iVar3 = text_read_line(1);
        menu_add_item((GameMenu *)&main_menu,3,0x330,iVar3,uVar2);
        uVar2 = 0;
        iVar3 = text_read_line(1);
        menu_add_item((GameMenu *)&main_menu,3,0x340,iVar3,uVar2);
        menu_set_item_checked
                  ((GameMenu *)&main_menu,0x327,(game.game_options & 0x20) >> 5);
        iVar1 = text_open_section(0,ADDR(0x62ed4c, ((u8 *)&g.d_0062ed4c)));
        if (iVar1 == 0) {
          uVar2 = text_read_line(1);
          menu_add_menu((GameMenu *)&main_menu,4,uVar2);
          uVar2 = 0x3c;
          iVar3 = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x401,iVar3,uVar2);
          uVar2 = 0x3c;
          iVar3 = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x410,iVar3,uVar2);
          uVar2 = 0x3c;
          iVar3 = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x411,iVar3,uVar2);
          uVar2 = 0x3c;
          iVar3 = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x412,iVar3,uVar2);
          uVar2 = 0x3c;
          iVar3 = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x413,iVar3,uVar2);
          menu_add_item((GameMenu *)&main_menu,4,0,0,0);
          uVar2 = 0;
          iVar3 = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x417,iVar3,uVar2);
          uVar2 = 0;
          iVar3 = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x418,iVar3,uVar2);
          uVar2 = 0;
          iVar3 = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x41b,iVar3,uVar2);
          uVar2 = 0;
          iVar3 = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x420,iVar3,uVar2);
          uVar2 = 0;
          iVar3 = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x421,iVar3,uVar2);
          menu_add_item((GameMenu *)&main_menu,4,0,0,0);
          uVar2 = 0;
          iVar3 = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x430,iVar3,uVar2);
          uVar2 = 0;
          iVar3 = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x440,iVar3,uVar2);
          uVar2 = 0;
          iVar3 = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x441,iVar3,uVar2);
          uVar2 = 0;
          iVar3 = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x442,iVar3,uVar2);
          uVar2 = 0x3c;
          iVar3 = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x445,iVar3,uVar2);
          menu_add_item((GameMenu *)&main_menu,4,0,0,0);
          uVar2 = 0;
          iVar3 = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x450,iVar3,uVar2);
          uVar2 = 0;
          iVar3 = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x451,iVar3,uVar2);
          menu_add_item((GameMenu *)&main_menu,4,0,0,0);
          uVar2 = 0;
          iVar3 = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x460,iVar3,uVar2);
          uVar2 = 0;
          iVar3 = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x468,iVar3,uVar2);
          uVar2 = 0;
          iVar3 = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x470,iVar3,uVar2);
          uVar2 = 0;
          iVar3 = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x480,iVar3,uVar2);
          menu_add_item((GameMenu *)&main_menu,4,0,0,0);
          uVar2 = 0;
          iVar3 = text_read_line(1);
          menu_add_item((GameMenu *)&main_menu,4,0x490,iVar3,uVar2);
          iVar1 = text_open_section(0,ADDR(0x62ed54, ((u8 *)&g.d_0062ed54)));
          if (iVar1 == 0) {
            uVar2 = text_read_line(1);
            menu_add_menu((GameMenu *)&main_menu,5,uVar2);
            uVar2 = 0;
            iVar3 = text_read_line(1);
            menu_add_item((GameMenu *)&main_menu,5,0x507,iVar3,uVar2);
            uVar2 = 0;
            iVar3 = text_read_line(1);
            menu_add_item((GameMenu *)&main_menu,5,0x500,iVar3,uVar2);
            menu_add_item((GameMenu *)&main_menu,5,0,0,0);
            uVar2 = 0;
            iVar3 = text_read_line(1);
            menu_add_item((GameMenu *)&main_menu,5,0x501,iVar3,uVar2);
            uVar2 = 0;
            iVar3 = text_read_line(1);
            menu_add_item((GameMenu *)&main_menu,5,0x502,iVar3,uVar2);
            uVar2 = 0;
            iVar3 = text_read_line(1);
            menu_add_item((GameMenu *)&main_menu,5,0x503,iVar3,uVar2);
            menu_add_item((GameMenu *)&main_menu,5,0,0,0);
            uVar2 = 0;
            iVar3 = text_read_line(1);
            menu_add_item((GameMenu *)&main_menu,5,0x504,iVar3,uVar2);
            uVar2 = 0;
            iVar3 = text_read_line(1);
            menu_add_item((GameMenu *)&main_menu,5,0x505,iVar3,uVar2);
            uVar2 = 0;
            iVar3 = text_read_line(1);
            menu_add_item((GameMenu *)&main_menu,5,0x506,iVar3,uVar2);
            menu_add_item((GameMenu *)&main_menu,5,0,0,0);
            uVar2 = 0;
            iVar3 = text_read_line(1);
            menu_add_item((GameMenu *)&main_menu,5,0x508,iVar3,uVar2);
            iVar1 = text_open_section(0,ADDR(0x62ed60, ((u8 *)&g.d_0062ed60)));
            if (iVar1 == 0) {
              uVar2 = text_read_line(1);
              menu_add_menu((GameMenu *)&main_menu,6,uVar2);
              uVar2 = 0;
              iVar3 = text_read_line(1);
              menu_add_item((GameMenu *)&main_menu,6,0x601,iVar3,uVar2);
              uVar2 = 0;
              iVar3 = text_read_line(1);
              menu_add_item((GameMenu *)&main_menu,6,0x602,iVar3,uVar2);
              uVar2 = 0;
              iVar3 = text_read_line(1);
              menu_add_item((GameMenu *)&main_menu,6,0x603,iVar3,uVar2);
              menu_add_item((GameMenu *)&main_menu,6,0,0,0);
              uVar2 = 0;
              iVar3 = text_read_line(1);
              menu_add_item((GameMenu *)&main_menu,6,0x605,iVar3,uVar2);
              uVar2 = 0;
              iVar3 = text_read_line(1);
              menu_add_item((GameMenu *)&main_menu,6,0x606,iVar3,uVar2);
              iVar1 = text_open_section(0,ADDR(0x62ed68, ((u8 *)&g.d_0062ed68)));
              if (iVar1 == 0) {
                uVar2 = text_read_line(1);
                menu_add_menu((GameMenu *)&main_menu,7,uVar2);
                uVar2 = 0;
                iVar3 = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x701,iVar3,uVar2);
                menu_add_item((GameMenu *)&main_menu,7,0,0,0);
                uVar2 = 0;
                iVar3 = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x711,iVar3,uVar2);
                uVar2 = 0;
                iVar3 = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x712,iVar3,uVar2);
                uVar2 = 0;
                iVar3 = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x713,iVar3,uVar2);
                menu_add_item((GameMenu *)&main_menu,7,0,0,0);
                uVar2 = 0;
                iVar3 = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x721,iVar3,uVar2);
                uVar2 = 0;
                iVar3 = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x722,iVar3,uVar2);
                menu_add_item((GameMenu *)&main_menu,7,0,0,0);
                uVar2 = 0;
                iVar3 = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x731,iVar3,uVar2);
                uVar2 = 0;
                iVar3 = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x732,iVar3,uVar2);
                uVar2 = 0;
                iVar3 = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x740,iVar3,uVar2);
                uVar2 = 0;
                iVar3 = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x748,iVar3,uVar2);
                uVar2 = 0;
                iVar3 = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x750,iVar3,uVar2);
                uVar2 = 0;
                iVar3 = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x752,iVar3,uVar2);
                menu_add_item((GameMenu *)&main_menu,7,0,0,0);
                uVar2 = 0;
                iVar3 = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x755,iVar3,uVar2);
                uVar2 = 0;
                iVar3 = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x760,iVar3,uVar2);
                uVar2 = 0;
                iVar3 = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x765,iVar3,uVar2);
                menu_add_item((GameMenu *)&main_menu,7,0,0,0);
                uVar2 = 0;
                iVar3 = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x768,iVar3,uVar2);
                uVar2 = 0;
                iVar3 = text_read_line(1);
                menu_add_item((GameMenu *)&main_menu,7,0x770,iVar3,uVar2);
                if (((game.game_options & 0x8000) == 0) || (game.multiplayer != '\0')) {
                  local_8 = 1;
                }
                else {
                  local_8 = 0;
                }
                menu_set_menu_enabled((GameMenu *)&main_menu,7,local_8);
                if (((game.game_options & 0x8000) == 0) || (game.multiplayer != '\0')) {
                  local_c = 0;
                }
                else {
                  local_c = 1;
                }
                menu_set_item_checked((GameMenu *)&main_menu,0x701,local_c);
                menu_set_item_enabled
                          ((GameMenu *)&main_menu,0x701,
                           (uint)(game.multiplayer != '\0' && mp_cheat_menu_allowed == 0));
                iVar1 = text_open_section(0,ADDR(0x62ed70, ((u8 *)&g.d_0062ed70)));
                if (iVar1 == 0) {
                  uVar2 = text_read_line(1);
                  menu_add_menu((GameMenu *)&main_menu,8,uVar2);
                  uVar2 = 0;
                  iVar3 = text_read_line(1);
                  menu_add_item((GameMenu *)&main_menu,8,0x801,iVar3,uVar2);
                  menu_add_item((GameMenu *)&main_menu,8,0,0,0);
                  uVar2 = 0;
                  iVar3 = text_read_line(1);
                  menu_add_item((GameMenu *)&main_menu,8,0x802,iVar3,uVar2);
                  uVar2 = 0;
                  iVar3 = text_read_line(1);
                  menu_add_item((GameMenu *)&main_menu,8,0x803,iVar3,uVar2);
                  uVar2 = 0;
                  iVar3 = text_read_line(1);
                  menu_add_item((GameMenu *)&main_menu,8,0x804,iVar3,uVar2);
                  uVar2 = 0;
                  iVar3 = text_read_line(1);
                  menu_add_item((GameMenu *)&main_menu,8,0x805,iVar3,uVar2);
                  uVar2 = 0;
                  iVar3 = text_read_line(1);
                  menu_add_item((GameMenu *)&main_menu,8,0x806,iVar3,uVar2);
                  uVar2 = 0;
                  iVar3 = text_read_line(1);
                  menu_add_item((GameMenu *)&main_menu,8,0x807,iVar3,uVar2);
                  uVar2 = 0;
                  iVar3 = text_read_line(1);
                  menu_add_item((GameMenu *)&main_menu,8,0x808,iVar3,uVar2);
                  uVar2 = 0;
                  iVar3 = text_read_line(1);
                  menu_add_item((GameMenu *)&main_menu,8,0x809,iVar3,uVar2);
                  if (((((game.game_options & 0x8000) == 0) || (game.multiplayer != '\0')) ||
                      ((game.game_flags & 0x80) == 0)) ||
                     (iVar1 = _strcmp(&scenario_dir_path,&game_home_dir), iVar1 == 0)) {
                    local_10 = 0;
                  }
                  else {
                    local_10 = 1;
                  }
                  menu_set_item_checked((GameMenu *)&main_menu,0x801,local_10);
                  if ((((game.game_options & 0x8000) == 0) || (game.multiplayer != '\0')) ||
                     (((game.game_flags & 0x80) == 0 ||
                      (iVar1 = _strcmp(&scenario_dir_path,&game_home_dir), iVar1 == 0)))) {
                    local_14 = 1;
                  }
                  else {
                    local_14 = 0;
                  }
                  menu_set_menu_enabled((GameMenu *)&main_menu,8,local_14);
                  menu_set_item_enabled
                            ((GameMenu *)&main_menu,0x801,(uint)(game.multiplayer != '\0'));
                  iVar1 = text_open_section(0,ADDR(0x62ed78, ((u8 *)&g.d_0062ed78)));
                  if (iVar1 == 0) {
                    uVar2 = text_read_line(1);
                    menu_add_menu((GameMenu *)&main_menu,9,uVar2);
                    uVar2 = 0;
                    iVar3 = text_read_line(1);
                    menu_add_item((GameMenu *)&main_menu,9,0x901,iVar3,uVar2);
                    uVar2 = 0;
                    iVar3 = text_read_line(1);
                    menu_add_item((GameMenu *)&main_menu,9,0x903,iVar3,uVar2);
                    uVar2 = 0;
                    iVar3 = text_read_line(1);
                    menu_add_item((GameMenu *)&main_menu,9,0x905,iVar3,uVar2);
                    uVar2 = 0;
                    iVar3 = text_read_line(1);
                    menu_add_item((GameMenu *)&main_menu,9,0x907,iVar3,uVar2);
                    menu_add_item((GameMenu *)&main_menu,9,0,0,0);
                    uVar2 = 0;
                    iVar3 = text_read_line(1);
                    menu_add_item((GameMenu *)&main_menu,9,0x909,iVar3,uVar2);
                    uVar2 = 0;
                    iVar3 = text_read_line(1);
                    menu_add_item((GameMenu *)&main_menu,9,0x90b,iVar3,uVar2);
                    menu_add_item((GameMenu *)&main_menu,9,0,0,0);
                    uVar2 = 0;
                    iVar3 = text_read_line(1);
                    menu_add_item((GameMenu *)&main_menu,9,0x90d,iVar3,uVar2);
                    menu_add_item((GameMenu *)&main_menu,9,0,0,0);
                    uVar2 = 0;
                    iVar3 = text_read_line(1);
                    menu_add_item((GameMenu *)&main_menu,9,0x9f0,iVar3,uVar2);
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
  menu_rebuild((GameMenu *)&main_menu,ADDR(0x6553d8, ((u8 *)&g.d_006553d8)));
  menu_set_command_handler((GameMenu *)&main_menu,ADDR(0x40385a, menu_command));
  return;
}
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 004e4c92 auto */
#define local_54 (*(i8 (*)[80])(frame_ + FRAME_OFF(4)))
void __cdecl menu_set_item_label(i32 param_1,i32 param_2,i32 param_3)

{
  i8 frame_[FRAME_OFF(88)] __attribute__((aligned(8)));  /* original stack frame */
  
  text_clear();
  text_append_label(param_2);
  text_expand_vars(ADDR(0x679640, ((u8 *)&g.d_00679640)),(iptr)local_54);
  menu_set_item_text((GameMenu *)&main_menu,param_1,(iptr)local_54);
  menu_set_item_enabled((GameMenu *)&main_menu,param_1,param_3);
  return;
}
#undef local_54

/* 004e4ceb auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define moving_units_mode (*(int *)((u8 *)&g.d_006d1da8))
#define mp_open_game (*(short *)((u8 *)&g.d_00654c74))
#define mp_turn_civ (*(i8 *)((u8 *)&g.d_006ad578))
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
#define mp_turn_civ_i32 (*(i32 *)((u8 *)&g.d_006ad578))
#define local_70 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define local_6c (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_68 (*(i32 *)(frame_ + FRAME_OFF(8)))
#define local_64 (*(i32 *)(frame_ + FRAME_OFF(12)))
#define local_60 (*(i32 *)(frame_ + FRAME_OFF(16)))
#define local_5c (*(i32 *)(frame_ + FRAME_OFF(20)))
#define local_58 (*(i32 *)(frame_ + FRAME_OFF(24)))
#define local_54 (*(i32 *)(frame_ + FRAME_OFF(28)))
#define local_50 (*(i32 *)(frame_ + FRAME_OFF(32)))
#define local_4c (*(i32 *)(frame_ + FRAME_OFF(36)))
#define local_48 (*(i32 *)(frame_ + FRAME_OFF(40)))
#define local_44 (*(i32 *)(frame_ + FRAME_OFF(44)))
#define local_40 (*(i32 *)(frame_ + FRAME_OFF(48)))
#define local_3c (*(i32 *)(frame_ + FRAME_OFF(52)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(104)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl menu_update_states(void)

{
  u8 uVar1;
  char cVar2;
  bool bVar3;
  byte bVar4;
  int unit;
  int x;
  int y;
  int civ;
  iptr iVar8;
  iptr iVar9;
  int city;
  iptr x2;
  uint uVar17;
  i32 uVar18;
  iptr iVar11;
  iptr iVar12;
  int terrain2;
  byte *pbVar20;
  iptr iVar13;
  iptr iVar14;
  uptr terrain;
  bool bVar21;
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
    local_3c = 0;
  }
  else {
    local_3c = 1;
  }
  menu_set_item_enabled((GameMenu *)&main_menu,0x220,local_3c);
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
    bVar4 = tile_terrain(x,y);
    terrain = (uptr)bVar4;
    bVar21 = terrain == 10;
    uVar1 = unit_types[units[unit].type].role;
    menu_set_menu_enabled((GameMenu *)&main_menu,4,0);
    menu_set_item_hidden((GameMenu *)&main_menu,0x401,(uint)(uVar1 != 5));
    menu_set_item_label(0x401,0x32,(uint)(uVar1 != 5));
    menu_set_item_label(0x410,0x34,(uint)(uVar1 != 5));
    menu_set_item_label(0x411,0x36,(uint)(uVar1 != 5));
    menu_set_item_label(0x412,0x38,(uint)(uVar1 != 5));
    menu_set_item_hidden((GameMenu *)&main_menu,0x450,(uint)(uVar1 == 5));
    if ((uVar1 == 5) && (iVar8 = civ_has_advance(civ,0x12), iVar8 != 0)) {
      local_40 = 0;
    }
    else {
      local_40 = 1;
    }
    menu_set_item_hidden((GameMenu *)&main_menu,0x418,local_40);
    if ((uVar1 == 5) && (iVar9 = civ_has_advance(civ,0x42), iVar9 != 0)) {
      local_44 = 0;
    }
    else {
      local_44 = 1;
    }
    menu_set_item_hidden((GameMenu *)&main_menu,0x417,local_44);
    menu_set_item_hidden((GameMenu *)&main_menu,0x430,(uint)(uVar1 == 5));
    menu_set_item_hidden((GameMenu *)&main_menu,0x41b,(uint)(uVar1 != 5));
    city = civ_has_advance(civ,0xd);
    if ((city == 0) && ((unit_types[units[unit].type].flags & 0x100) == 0)) {
      local_48 = 1;
    }
    else {
      local_48 = 0;
    }
    menu_set_item_hidden((GameMenu *)&main_menu,0x441,local_48);
    menu_set_item_enabled
              ((GameMenu *)&main_menu,0x441,
               (uint)((unit_types[units[unit].type].flags & 0x100) == 0));
    city = civ_has_advance(civ,0x42);
    menu_set_item_hidden((GameMenu *)&main_menu,0x442,(uint)(city == 0));
    city = tile_city_owner(x,y);
    menu_set_item_enabled((GameMenu *)&main_menu,0x442,(uint)(city < 0));
    if (uVar1 == 5) {
      bVar3 = true;
      for (local_8 = 0; local_8 < 8; local_8++) {
        x2 = map_wrap_x((char)(&dir_dx_table)[local_8] + x);
        cVar2 = (&dir_dy_table)[local_8];
        city = map_in_bounds(x2,cVar2 + y);
        if ((city != 0) && (city = tile_city_owner(x2,cVar2 + y), -1 < city)) {
          bVar3 = false;
        }
      }
      city = city_at(x,y);
      if (city < 0) {
        terrain2 = tile_is_ocean(x,y);
        if ((terrain2 == 0) && (bVar3)) {
          local_4c = 0;
        }
        else {
          local_4c = 1;
        }
        menu_set_item_enabled((GameMenu *)&main_menu,0x401,local_4c);
      }
      else {
        menu_set_item_label(0x401,0x33,(uint)('\t' < cities[city].size));
      }
      uVar17 = tile_improvements(x,y);
      if ((uVar17 & 0x80) == 0) {
        menu_set_item_enabled((GameMenu *)&main_menu,0x420,1);
      }
      uVar18 = tile_improvements(x,y);
      if ((((((byte)uVar18 & 0x42) == 0x40) ||
           (iVar11 = tile_airbase_owner(x,y), -1 < iVar11)) || (bVar21)) || (-1 < city)) {
        menu_set_item_enabled((GameMenu *)&main_menu,0x418,1);
      }
      uVar18 = tile_improvements(x,y);
      if (((((byte)uVar18 & 0x42) == 0x40) ||
          (iVar12 = tile_airbase_owner(x,y), -1 < iVar12)) || ((bVar21 || (-1 < city)))) {
        menu_set_item_enabled((GameMenu *)&main_menu,0x417,1);
      }
      uVar17 = tile_improvements(x,y);
      if (((uVar17 & 0x10) == 0) || (terrain2 = civ_has_advance(civ,0x43), terrain2 == 0)) {
        if (((bVar21) ||
            ((-1 < city || (uVar17 = tile_improvements(x,y), (uVar17 & 0x10) != 0)))) ||
           ((pbVar20 = (byte *)tile_at(x,y), (*pbVar20 & 0x80) != 0 &&
            (terrain2 = civ_has_advance(civ,7), terrain2 == 0)))) {
          local_54 = 1;
        }
        else {
          local_54 = 0;
        }
        menu_set_item_enabled((GameMenu *)&main_menu,0x410,local_54);
      }
      else {
        uVar17 = tile_improvements(x,y);
        if ((((uVar17 & 0x20) != 0) || (-1 < city)) || (bVar21)) {
          local_50 = 1;
        }
        else {
          local_50 = 0;
        }
        menu_set_item_label(0x410,0x35,local_50);
      }
      terrain2 = (int)terrain_types[terrain].irrigate_to;
      if (terrain2 < 0) {
        uVar17 = tile_improvements(x,y);
        if ((uVar17 & 4) == 0) {
          if (((terrain2 == -1) || (bVar21)) || (-1 < city)) {
            local_5c = 1;
          }
          else {
            local_5c = 0;
          }
          menu_set_item_enabled((GameMenu *)&main_menu,0x411,local_5c);
        }
        else {
          terrain2 = civ_has_advance(civ,0x46);
          if (((terrain2 == 0) || (bVar21)) || (-1 < city)) {
            local_58 = 1;
          }
          else {
            local_58 = 0;
          }
          menu_set_item_label(0x411,0x3d,local_58);
        }
      }
      else {
        text_set_label_arg(0,terrain_types[terrain2].name);
        menu_set_item_label(0x411,0x37,0);
      }
      terrain2 = (int)terrain_types[terrain].mine_to;
      if (terrain2 < 0) {
        if (((terrain2 == -1) || (bVar21)) || (-1 < city)) {
          local_60 = 1;
        }
        else {
          local_60 = 0;
        }
        menu_set_item_enabled((GameMenu *)&main_menu,0x412,local_60);
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
    menu_set_item_hidden((GameMenu *)&main_menu,0x421,(uint)(uVar1 == 5));
    if ((unit_types[units[unit].type].attack == '\0') ||
       (unit_types[units[unit].type].domain != '\0')) {
      menu_set_item_enabled((GameMenu *)&main_menu,0x421,1);
    }
  }
  if ((((*(i8 *)((char *)&game.game_options + 1)) & 0x80) == 0) || (game.multiplayer != '\0')) {
    local_64 = 1;
  }
  else {
    local_64 = 0;
  }
  menu_set_menu_enabled((GameMenu *)&main_menu,7,local_64);
  if ((((*(i8 *)((char *)&game.game_options + 1)) & 0x80) == 0) || (game.multiplayer != '\0')) {
    local_68 = 0;
  }
  else {
    local_68 = 1;
  }
  menu_set_item_checked((GameMenu *)&main_menu,0x701,local_68);
  menu_set_item_enabled
            ((GameMenu *)&main_menu,0x701,(uint)(game.multiplayer != '\0' && mp_cheat_menu_allowed == 0)
            );
  if ((2 < game.multiplayer) && (mp_turn_civ_i32 != human_civ)) {
    menu_set_menu_enabled((GameMenu *)&main_menu,4,1);
  }
  if ((((((*(i8 *)((char *)&game.game_options + 1)) & 0x80) == 0) || (game.multiplayer != '\0')) ||
      ((game.game_flags & 0x80) == 0)) ||
     (iVar13 = _strcmp(&scenario_dir_path,&game_home_dir), iVar13 == 0)) {
    local_6c = 0;
  }
  else {
    local_6c = 1;
  }
  menu_set_item_checked((GameMenu *)&main_menu,0x801,local_6c);
  if (((((*(i8 *)((char *)&game.game_options + 1)) & 0x80) == 0) || (game.multiplayer != '\0')) ||
     (((game.game_flags & 0x80) == 0 || (iVar14 = _strcmp(&scenario_dir_path,&game_home_dir), iVar14 == 0)
      ))) {
    local_70 = 1;
  }
  else {
    local_70 = 0;
  }
  menu_set_menu_enabled((GameMenu *)&main_menu,8,local_70);
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
#undef local_70
#undef local_6c
#undef local_68
#undef local_64
#undef local_60
#undef local_5c
#undef local_58
#undef local_54
#undef local_50
#undef local_4c
#undef local_48
#undef local_44
#undef local_40
#undef local_3c
#undef local_8

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
#define local_4a8 (*(uint *)(frame_ + FRAME_OFF(0)))
#define local_498 (*(void * *)(frame_ + FRAME_OFF(16)))
#define local_484 (*(Sprite *)(frame_ + FRAME_OFF(36)))
#define local_448 (*(void * *)(frame_ + FRAME_OFF(96)))
#define local_444 (*(GamePalette *)(frame_ + FRAME_OFF(100)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1176)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1180)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(1184)))
int __cdecl popup_city_picture_zoom(iptr param_1,iptr city,uint param_3,int param_4,iptr civ)

{
  ViewWindow *this;
  int iVar1;
  i32 uVar2;
  i32 uVar3;
  iptr iVar4;
  iptr iVar5;
  i8 frame_[FRAME_OFF(1192)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  palette_init(&local_444);
  local_8 = 0;
  sprite_init(&local_484);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  if (autoplay_active == 0) {
    if (param_4 == 0) {
      if (city_notify_enabled == 0) {
        local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
        /* inlined unwind funclet 004ebbad */ { sprite_destroy((Sprite *)((iptr)&local_484)); }
        local_8 = 0xffffffff;
        /* inlined unwind funclet 004ebbb9 */ { palette_destroy((GamePalette *)((iptr)&local_444)); }
        iVar1 = 0;
        goto LAB_004ebbcf;
      }
      civ = (iptr)cities[city].owner;
      mapviews_ensure_visible((int)cities[city].x,(int)cities[city].y,civ);
      text_set_string_arg_b(0,(iptr)&cities[city].name);
    }
    this = operator_new(0x798);
    (*(i8 *)((char *)&local_8 + 0)) = 2;
    if (this == (ViewWindow *)0x0) {
      local_498 = (void *)0x0;
    }
    else {
      local_498 = (void *)city_picture_popup_ctor(this);
    }
    local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),1);
    local_448 = local_498;
    iVar1 = civ_has_advance(civ,0x25);
    if (iVar1 != 0) {
      param_3++;
    }
    if ((int)param_3 < 1) {
      local_4a8 = ~param_3 + 1;
    }
    else {
      local_4a8 = param_3;
    }
    surface_load_gif_resource
              ((DibSurface *)((int)local_448 + 0x2d8),local_4a8,10,0xc0,(iptr)&local_444);
    uVar2 = surface_height((DibSurface *)((int)local_448 + 0x2d8));
    uVar3 = surface_width((DibSurface *)((int)local_448 + 0x2d8));
    sprite_grab_from_surface(&local_484,(int)local_448 + 0x2d8,7,0,0,uVar3,uVar2);
    dialog_load_game_text((Dialog *)((int)local_448 + 0x4a4),param_1);
    dialog_add_sprite
              ((DialogOptionList *)((int)local_448 + 0x4a4),(iptr)&local_484,0,0);
    if ((param_4 == 0) && (city_zoom_requested == 0)) {
      uVar2 = 0;
      iVar5 = 1;
      iVar4 = label_string(*(i32 *)(label_string_ids + 0x80));
      dialog_add_option
                ((DialogOptionList *)((int)local_448 + 0x4a4),iVar4,iVar5,uVar2);
      uVar2 = 0;
      iVar5 = 0;
      iVar4 = label_string(*(i32 *)(label_string_ids + 0x84));
      dialog_add_option
                ((DialogOptionList *)((int)local_448 + 0x4a4),iVar4,iVar5,uVar2);
      if ((game.message_options & 0x400) == 0) {
        dialog_set_default_choice((DialogOptionList *)((int)local_448 + 0x4a4),0);
      }
      else {
        dialog_set_default_choice((DialogOptionList *)((int)local_448 + 0x4a4),1);
      }
    }
    iVar1 = dlg_show_modal((Dialog *)((int)local_448 + 0x4a4),0);
    if ((param_4 == 0) && (0 < iVar1)) {
      city_zoom_requested = 1;
    }
    if (local_448 != (void *)0x0) {
      city_picture_popup_scalar_dtor(local_448,1);
    }
    local_8 = local_8 & 0xffffff00;
    /* inlined unwind funclet 004ebbad */ { sprite_destroy((Sprite *)((iptr)&local_484)); }
    local_8 = 0xffffffff;
    /* inlined unwind funclet 004ebbb9 */ { palette_destroy((GamePalette *)((iptr)&local_444)); }
  }
  else {
    local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
    /* inlined unwind funclet 004ebbad */ { sprite_destroy((Sprite *)((iptr)&local_484)); }
    local_8 = 0xffffffff;
    /* inlined unwind funclet 004ebbb9 */ { palette_destroy((GamePalette *)((iptr)&local_444)); }
    iVar1 = 0;
  }
LAB_004ebbcf:
  return iVar1;
}
#undef autoplay_active
#undef city_notify_enabled
#undef city_zoom_requested
#undef local_4a8
#undef local_498
#undef local_484
#undef local_448
#undef local_444
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00511320 auto */
u32 __thiscall wnd_get_palette(WndPaletteView *this)

{
  return this->wnd_palette;
}

/* 00511460 auto */
void __thiscall
hotspot_add_rect(ClickMap *this,iptr param_1,i32 param_2,iptr param_3)

{
  clickmap_add(this,param_1,param_2,*(i32 *)param_3,*(i32 *)(param_3 + 4),
                     *(int *)(param_3 + 8) - *(int *)param_3,
                     *(int *)(param_3 + 0xc) - *(int *)(param_3 + 4));
  return;
}

/* 00511520 auto */
i32 __cdecl popup_game_with_city_flags(iptr param_1,i32 param_2,i32 param_3)

{
  i32 uVar1;
  
  uVar1 = popup_text_with_city(ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),param_1,param_2,param_3);
  return uVar1;
}

/* 00511820 auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall frame_wnd_set_title_font(FrameWindow *this,iptr param_1)

{
  this->title_font = param_1;
  return;
}

/* 00511850 auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall frame_wnd_set_title_small_font(FrameWindow *this,iptr param_1)

{
  this->title_small_font = param_1;
  return;
}

/* 00518e80 auto */
void __thiscall wnd_move_xy(WndMoveView *this,i32 param_1,i32 param_2)

{
  wnd_obj_move_xy(this->native_wnd,param_1,param_2);
  return;
}

/* 00518ec0 auto */
i32 __cdecl dlg_input_number_game(iptr param_1,i32 param_2,iptr param_3)

{
  i32 uVar1;
  
  uVar1 = dlg_input_number(ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),param_1,param_2,param_3);
  return uVar1;
}

/* 0051d3e0 auto */
#define dlg_check_bits (*(uint *)((u8 *)&g.d_00631ed8))
#define dlg_help_pressed (*(u32 *)((u8 *)&g.d_00631edc))
#define local_308 (*(Dialog *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(756)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(760)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(764)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(768)))
i32 __cdecl
popup_text_run(iptr param_1,iptr param_2,i32 param_3,i32 param_4,i32 param_5,
            i32 param_6,i32 param_7)

{
  int iVar1;
  i8 frame_[FRAME_OFF(776)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_308,0x4000);
  local_8 = 0;
  iVar1 = dialog_load_text_section
                    (&local_308,param_1,param_2,param_3,0,param_4,param_5,param_6,param_7);
  if (iVar1 == 0) {
    if (((byte)local_308.field_3c & 4) != 0) {
      for (local_14 = 0; local_14 < (int)local_308.field_28; local_14++) {
        dialog_set_option_checked
                  ((DialogOptionList *)&local_308,local_14,1 << ((byte)local_14 & 0x1f) & dlg_check_bits
                  );
      }
    }
    param_3 = dlg_show_modal(&local_308,0);
    dlg_help_pressed = local_308.field_dc;
    if (((byte)local_308.field_3c & 4) != 0) {
      dlg_check_bits = 0;
      for (local_14 = 0; local_14 < (int)local_308.field_28; local_14++) {
        iVar1 = dialog_option_is_checked((DialogOptionList *)&local_308,local_14);
        if (iVar1 != 0) {
          dlg_check_bits = dlg_check_bits | 1 << ((byte)local_14 & 0x1f);
        }
      }
    }
  }
  local_8 = 0xffffffff;
  /* inlined unwind funclet 0051d53f */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
  return param_3;
}
#undef dlg_check_bits
#undef dlg_help_pressed
#undef local_308
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0051d564 auto */
#define dlg_help_pressed (*(u32 *)((u8 *)&g.d_00631edc))
#define local_304 (*(Dialog *)(frame_ + FRAME_OFF(4)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(760)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(764)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(768)))
i32 __cdecl
popup_text_with_sprite(iptr param_1,iptr param_2,i32 param_3,iptr param_4,i32 param_5)

{
  i32 uVar1;
  i8 frame_[FRAME_OFF(776)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_304,0x4000);
  local_8 = 0;
  dialog_load_text(&local_304,param_1,param_2,param_3);
  dialog_add_sprite((DialogOptionList *)&local_304,param_4,0,0);
  dialog_set_image_zoom((DialogWindowView *)&local_304,param_5);
  uVar1 = dlg_show_modal(&local_304,0);
  dlg_help_pressed = local_304.field_dc;
  local_8 = 0xffffffff;
  /* inlined unwind funclet 0051d616 */ { dialog_dtor((Dialog *)((iptr)&local_304)); }
  return uVar1;
}
#undef dlg_help_pressed
#undef local_304
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0051d63b auto */
#define local_30c (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_308 (*(Dialog *)(frame_ + FRAME_OFF(8)))
#define local_14 (*(char * *)(frame_ + FRAME_OFF(764)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(768)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(772)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(776)))
i32 __cdecl
dlg_text_input(iptr param_1,iptr param_2,i32 param_3,iptr param_4,iptr param_5)

{
  int iVar1;
  i8 frame_[FRAME_OFF(784)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  local_30c = 0;
  dialog_ctor(&local_308,0x4000);
  local_8 = 0;
  str_clear(param_5);
  iVar1 = dialog_load_text_section(&local_308,param_1,param_2,param_3,param_4,0,0,0,1);
  if (iVar1 == 0) {
    local_30c = dialog_run_modal(&local_308,param_5,0);
    for (local_14 = (char *)param_5;
        (*local_14 != '\0' && ((*local_14 == ' ' || (*local_14 == '\t')))); local_14++)
    {
      *local_14 = '_';
    }
  }
  local_8 = 0xffffffff;
  /* inlined unwind funclet 0051d738 */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
  return local_30c;
}
#undef local_30c
#undef local_308
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0051d75d auto */
#define local_120 (*(char (*)[260])(frame_ + FRAME_OFF(0)))
#define local_1c (*(char (*)[20])(frame_ + FRAME_OFF(260)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(280)))
i32 __cdecl dlg_input_number(iptr param_1,iptr param_2,int param_3,iptr param_4)

{
  long lVar1;
  i8 frame_[FRAME_OFF(288)] __attribute__((aligned(8)));  /* original stack frame */
  
  __itoa(param_3,local_1c,10);
  local_8 = dlg_text_input(param_1,param_2,5,(iptr)local_1c,(iptr)local_120);
  lVar1 = _atol(local_120);
  *(long *)param_4 = lVar1;
  return local_8;
}
#undef local_120
#undef local_1c
#undef local_8

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
void __cdecl dlg_check_set(i32 param_1,int param_2)

{
  if (param_2 == 0) {
    dlg_check_bits = dlg_check_bits & ~(1 << ((byte)param_1 & 0x1f));
  }
  else {
    dlg_check_bits = dlg_check_bits | 1 << ((byte)param_1 & 0x1f);
  }
  return;
}
#undef dlg_check_bits

/* 0051d817 auto */
#define dlg_check_bits (*(uint *)((u8 *)&g.d_00631ed8))
uint __cdecl dlg_check_get(i32 param_1)

{
  return 1 << ((byte)param_1 & 0x1f) & dlg_check_bits;
}
#undef dlg_check_bits

/* 0052182c auto */
#define local_84 (*(char (*)[128])(frame_ + FRAME_OFF(4)))
void __cdecl dialog_prepend_title_label(iptr param_1,i32 param_2)

{
  size_t sVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(136)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_84[0] = '\0';
  str_append_label((iptr)local_84,param_2);
  if (*(int *)(param_1 + 0x134) != 0) {
    crt_strcat(local_84,&dialog_title_label_space_str);
    crt_strcat(local_84,*(i32 *)(param_1 + 0x134));
  }
  sVar1 = _strlen(local_84);
  uVar2 = memblock_alloc(param_1 + 0x254,sVar1 + 1);
  *(i32 *)(param_1 + 0x134) = uVar2;
  crt_strcpy(*(i32 *)(param_1 + 0x134),local_84);
  return;
}
#undef local_84

/* 00548b70 auto */
int __cdecl ui_calc_item_spacing(int param_1,int param_2,int param_3,iptr param_4,iptr param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (param_2 < 2) {
    param_2 = 1;
  }
  if (param_1 < 2) {
    param_1 = 1;
  }
  iVar3 = param_2;
  if (param_1 == 1) {
    if (param_5 != 0) {
      *(i32 *)param_5 = 0;
    }
    if (param_4 != 0) {
      *(i32 *)param_4 = 1;
    }
  }
  else {
    iVar1 = param_3 - param_2;
    iVar2 = iVar1 / (param_1 - 1);
    if (param_5 != 0) {
      *(int *)param_5 = iVar1 % (param_1 - 1);
    }
    if (param_4 != 0) {
      *(int *)param_4 = param_1;
    }
    if ((iVar2 < param_2) && (iVar3 = iVar2, iVar2 < 1)) {
      if (param_5 != 0) {
        *(i32 *)param_5 = 0;
      }
      if (param_4 != 0) {
        *(int *)param_4 = (iVar1 - param_2) + 1;
      }
      iVar3 = 1;
    }
  }
  return iVar3;
}

/* 00551e20 auto */
i32 __cdecl popup_game_ex(iptr param_1,i32 param_2,i32 param_3)

{
  i32 uVar1;
  
  uVar1 = popup_text_ex(ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),param_1,param_2,param_3);
  return uVar1;
}

/* 00551e60 auto */
i32 __cdecl popup_debug_ex(iptr param_1,i32 param_2,i32 param_3)

{
  i32 uVar1;
  
  uVar1 = popup_text_ex(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),param_1,param_2,param_3);
  return uVar1;
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
  int iVar1;
  
  gfx_get_screen_rect(ADDR(0x6ab180, ((u8 *)&g.d_006ab180)));
  screen_width = rect_width(ADDR(0x6ab180, ((u8 *)&g.d_006ab180)));
  screen_height = rect_height(ADDR(0x6ab180, ((u8 *)&g.d_006ab180)));
  ui_font_height = 0x10;
  if (999 < screen_width) {
    ui_font_height = 0x18;
  }
  ui_large_screen = (uint)(999 < screen_width);
  font_set((GameFont *)&caption_font,0,ui_font_height);
  font_set((GameFont *)&caption_small_font,0,(ui_font_height * 2) / 3);
  font_set((GameFont *)&ui_text_font,0,ui_font_height);
  iVar1 = font_cached_height((GameFont *)&caption_font);
  frame_caption_height = iVar1 + frame_padding * 2 + frame_bevel_width * 2;
  frame_border_width = frame_bevel_width * 2 + frame_padding * 2;
  iVar1 = GetSystemMetrics(7);
  sys_dlgframe_w2 = iVar1 * 2;
  iVar1 = GetSystemMetrics(8);
  sys_dlgframe_h2 = iVar1 * 2;
  return;
}
#undef frame_border_width
#undef frame_caption_height
#undef screen_height
#undef ui_large_screen

/* 005520fa auto */
void __cdecl frame_set_border_tile(iptr param_1)

{
  frame_border_tile = param_1;
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
#define local_168 (*(u32 *)(frame_ + FRAME_OFF(0)))
#define local_164 (*(u32 *)(frame_ + FRAME_OFF(4)))
#define local_160 (*(i8 (*)[16])(frame_ + FRAME_OFF(8)))
#define local_150 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_14c (*(int *)(frame_ + FRAME_OFF(28)))
#define local_148 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_144 (*(int *)(frame_ + FRAME_OFF(36)))
#define local_140 (*(i32 *)(frame_ + FRAME_OFF(40)))
#define local_13c (*(int *)(frame_ + FRAME_OFF(44)))
#define local_138 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_134 (*(int *)(frame_ + FRAME_OFF(52)))
#define local_130 (*(int *)(frame_ + FRAME_OFF(56)))
#define local_12c (*(int *)(frame_ + FRAME_OFF(60)))
#define local_128 (*(GameFont * *)(frame_ + FRAME_OFF(64)))
#define local_124 (*(int *)(frame_ + FRAME_OFF(68)))
#define local_120 (*(i32 *)(frame_ + FRAME_OFF(72)))
#define local_11c (*(int *)(frame_ + FRAME_OFF(76)))
#define local_118 (*(int *)(frame_ + FRAME_OFF(80)))
#define local_114 (*(char (*)[256])(frame_ + FRAME_OFF(84)))
#define local_14 (*(u32 *)(frame_ + FRAME_OFF(340)))
#define local_10 (*(u32 *)(frame_ + FRAME_OFF(344)))
#define local_c (*(u32 *)(frame_ + FRAME_OFF(348)))
#define local_8 (*(u32 *)(frame_ + FRAME_OFF(352)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall frame_wnd_draw_caption(FrameWindow *this)

{
  i32 uVar1;
  int iVar2;
  int iVar3;
  uptr sVar4;
  uptr sVar5;
  i8 frame_[FRAME_OFF(360)] __attribute__((aligned(8)));  /* original stack frame */
  
  surface_reset_clip((DibSurface *)this);
  local_120 = frame_highlight_color;
  local_140 = frame_shadow_color;
  local_144 = frame_bevel_width;
  if (this->caption_height == 0) {
    local_164 = this->border_width;
  }
  else {
    local_164 = this->caption_height;
  }
  local_148 = local_164 + frame_bevel_width * -2;
  local_138 = rect_width((iptr)&this->frame_rect);
  gfx_tile_fill((iptr)this,frame_border_tile,0,local_144,local_138,local_148,0,local_144);
  local_148 = this->border_width + local_144 * -2;
  local_12c = rect_height((iptr)&this->frame_rect);
  local_12c -= (local_144 + local_148);
  gfx_tile_fill((iptr)this,frame_border_tile,0,local_12c,local_138,local_148,0,local_12c);
  local_138 = this->border_width + local_144 * -2;
  local_148 = rect_height((iptr)&this->frame_rect);
  gfx_tile_fill((iptr)this,frame_border_tile,local_144,0,local_138,local_148,local_144,0);
  local_12c = rect_width((iptr)&this->frame_rect);
  local_12c -= (local_144 + local_138);
  gfx_tile_fill((iptr)this,frame_border_tile,local_12c,0,local_138,local_148,local_12c,0);
  local_14 = this->frame_rect;
  local_10 = this->frame_top;
  local_c = this->frame_right;
  local_8 = this->frame_bottom;
  for (local_118 = 0; local_118 < local_144; local_118++) {
    gfx_draw_bevel_rect((iptr)this,(iptr)&local_14,local_120,local_140);
    rect_deflate((iptr)&local_14,1,1);
  }
  rect_deflate((iptr)&local_14,this->border_width + local_144 * -2,0);
  if (this->caption_height == 0) {
    local_168 = this->border_width;
  }
  else {
    local_168 = this->caption_height;
  }
  local_10 = local_10 + local_168 + local_144 * -2;
  local_8 -= (this->border_width + local_144 * -2);
  for (local_118 = 0; local_118 < local_144; local_118++) {
    gfx_draw_bevel_rect((iptr)this,(iptr)&local_14,local_140,local_120);
    rect_deflate((iptr)&local_14,1,1);
  }
  local_130 = frame_border_width;
  for (local_118 = 0; local_118 < (int)this->caption_button_count; local_118++) {
    local_138 = (int)(*(int *)(this->pad_200 + local_118 * 0x1c + 0xc) * this->caption_height) / 0x18;
    local_148 = (int)(*(int *)(this->pad_200 + local_118 * 0x1c + 0x10) * this->caption_height) / 0x18;
    local_134 = ((int)this->caption_height >> 1) - (local_148 >> 1);
    rect_set_xywh((iptr)&local_14,local_130,local_134,local_138,local_148);
    gfx_set_scale_ratio(this->caption_height,0x18);
    sprite_draw
              (*(Sprite **)(this->pad_200 + local_118 * 0x1c + 0x14),(iptr)local_160,
               (iptr)this,local_130,local_134);
    gfx_reset_zoom_scale();
    local_130 = local_130 + local_138 + frame_padding;
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
      local_150 = (int)(this->timer_last_value - 1) / 0x3c;
      local_14c = (this->timer_last_value - 1) + local_150 * -0x3c;
      if (local_150 < 10) {
        this->timer_text = '0';
        __itoa(local_150,(char *)this->pad_1b9,10);
      }
      else {
        __itoa(local_150,(char *)&this->timer_text,10);
      }
      this->timer_colon = ':';
      if (local_14c < 10) {
        if (local_14c < 0) {
          local_14c = 0;
        }
        this->timer_seconds_text = '0';
        __itoa(local_14c,(char *)this->pad_1bc,10);
      }
      else {
        __itoa(local_14c,(char *)&this->timer_seconds_text,10);
      }
    }
  }
  else if ((int)autoplay_turns_left != this->timer_last_value) {
    this->timer_last_value = (int)autoplay_turns_left;
    __itoa((int)autoplay_turns_left,(char *)&this->timer_text,10);
  }
  crt_strcpy(local_114,this->pad_134);
  if (((this->show_turn_status == 0) || (game.multiplayer == '\0')) || (mp_simultaneous_moves != '\0')) {
    if (((this->show_turn_status != 0) && (game.multiplayer != '\0')) && (mp_simultaneous_moves != '\0')) {
      if ((1 << (mp_turn_civ & 0x1f) & (uint)game.human_players) == 0) {
        crt_strcat(local_114,&caption_simul_open_paren_str);
        if (game_language == 1) {
          crt_strcat(local_114,&caption_simul_ai_fr_str);
        }
        else {
          crt_strcat(local_114,&caption_simul_ai_str);
        }
        crt_strcat(local_114,&caption_simul_space_str);
        str_append_label((iptr)local_114,0x369);
        if (this->timer_text != '\0') {
          crt_strcat(local_114,&caption_simul_timer_sep_str);
          crt_strcat(local_114,&this->timer_text);
        }
        crt_strcat(local_114,&caption_simul_close_paren_str);
      }
      else if (this->timer_text != '\0') {
        crt_strcat(local_114,&caption_timer_open_paren_str);
        crt_strcat(local_114,&this->timer_text);
        crt_strcat(local_114,&caption_timer_close_paren_str);
      }
    }
  }
  else {
    crt_strcat(local_114,&caption_status_open_paren_str);
    if ((((*(byte *)&civs[human_civ].treaties[mp_turn_civ_i32] & 1) == 0) &&
        (mp_turn_civ_i32 != human_civ)) &&
       ((game.multiplayer != 1 || ((1 << (mp_turn_civ & 0x1f) & (uint)hotseat_human_players) == 0)))) {
      if ((1 << (mp_turn_civ & 0x1f) & (uint)game.human_players) == 0) {
        if (game_language == 1) {
          crt_strcat(local_114,&caption_ai_fr_str);
        }
        else {
          crt_strcat(local_114,&caption_ai_str);
        }
        if (autoplay_active == 0) {
          this->timer_text = '\0';
        }
      }
      else {
        crt_strcat(local_114,&net_slot_player_names + *(int *)(&net_civ_slots + mp_turn_civ_i32 * 4) * 0x54);
      }
    }
    else {
      uVar1 = civ_adjective(mp_turn_civ_i32);
      crt_strcat(local_114,uVar1);
      if (((1 << (mp_turn_civ & 0x1f) & (uint)game.human_players) == 0) && (autoplay_active == 0)) {
        this->timer_text = '\0';
      }
    }
    crt_strcat(local_114,&caption_moves_space_str);
    str_append_label((iptr)local_114,0x369);
    if (this->timer_text != '\0') {
      crt_strcat(local_114,&caption_timer_sep_str);
      crt_strcat(local_114,&this->timer_text);
    }
    crt_strcat(local_114,&caption_close_paren_str);
  }
  local_138 = rect_width((iptr)&this->frame_rect);
  local_13c = font_text_width((GameFont *)this->title_font,(iptr)local_114);
  local_13c += 4;
  local_11c = (local_138 >> 1) - (local_13c >> 1);
  local_124 = local_144 + 1;
  local_128 = (GameFont *)this->title_font;
  if (local_11c < local_130) {
    local_11c = local_130;
  }
  if (local_138 < local_13c + local_11c) {
    local_128 = (GameFont *)this->title_small_font;
    local_13c = font_text_width(local_128,(iptr)local_114);
    local_13c += 4;
    local_11c = (local_138 >> 1) - (local_13c >> 1);
    if (local_11c < local_130) {
      local_11c = local_130;
    }
    iVar2 = font_cached_height((GameFont *)this->title_font);
    iVar3 = font_cached_height(local_128);
    local_124 += (iVar2 - iVar3 >> 1);
    while ((sVar4 = _strlen(local_114), sVar4 != 0 &&
           (iVar2 = font_text_width(local_128,(iptr)local_114),
           local_138 < local_11c + iVar2 + 4))) {
      sVar5 = _strlen(local_114);
      local_114[sVar5 - 1] = '\0';
    }
  }
  gfx_set_text_color_index(10);
  surface_draw_text
            ((DibSurface *)this,(iptr)local_128,(iptr)local_114,local_11c + 2,local_124 + 1,5);
  gfx_set_text_color_index(0x1a);
  surface_draw_text
            ((DibSurface *)this,(iptr)local_128,(iptr)local_114,local_11c + 1,local_124,5);
  surface_draw_text
            ((DibSurface *)this,(iptr)local_128,(iptr)local_114,local_11c,local_124,5);
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
#undef local_168
#undef local_164
#undef local_160
#undef local_150
#undef local_14c
#undef local_148
#undef local_144
#undef local_140
#undef local_13c
#undef local_138
#undef local_134
#undef local_130
#undef local_12c
#undef local_128
#undef local_124
#undef local_120
#undef local_11c
#undef local_118
#undef local_114
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 00552e5b auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl frame_wnd_on_caption_button_click(int param_1)

{
  iptr iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar1 - 0x48;
  }
  if (*(int *)(local_8 + 0x2a8) != 0) {
    (*((code **)(local_8))[170])(*(i32 *)(local_8 + 0x200 + (param_1 - 1000) * 0x1c));
  }
  return;
}
#undef local_8

/* 00552ed2 auto */
#define frame_border_width (*(int *)((u8 *)&g.d_0063359c))
#define local_40 (*(u8 * *)(frame_ + FRAME_OFF(0)))
#define local_3c (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(28)))
#define local_20 (*(i8 (*)[16])(frame_ + FRAME_OFF(32)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(48)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(52)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(56)))
void __thiscall frame_wnd_layout(FrameWindow *this)

{
  int iVar1;
  int iVar2;
  u32 uVar3;
  Control *this_00;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  iVar1 = surface_get_width((DibSurface *)this);
  iVar2 = surface_get_height((DibSurface *)this);
  rect_set_xywh((iptr)&this->frame_rect,0,0,iVar1,iVar2);
  rect_set_xywh((iptr)&this->client_rect,0,0,iVar1 + this->border_width * -2,
                     iVar2 - (this->caption_height + this->border_width));
  rect_offset((iptr)&this->client_rect,this->border_width,this->caption_height);
  this->client_x = this->client_rect;
  this->client_y = this->client_top;
  uVar3 = rect_width((iptr)&this->client_rect);
  this->client_width = uVar3;
  uVar3 = rect_height((iptr)&this->client_rect);
  this->client_height = uVar3;
  frame_wnd_destroy_caption_buttons((WindowObjectView *)this);
  local_28 = frame_border_width;
  for (local_24 = 0; local_24 < (int)this->caption_button_count; local_24++) {
    iVar1 = (int)(*(int *)(this->pad_200 + local_24 * 0x1c + 0xc) * this->caption_height) / 0x18;
    iVar2 = (int)(*(int *)(this->pad_200 + local_24 * 0x1c + 0x10) * this->caption_height) / 0x18;
    rect_set_xywh((iptr)local_20,local_28,((int)this->caption_height >> 1) - (iVar2 >> 1),iVar1,
                       iVar2);
    this_00 = operator_new(0x40);
    local_8 = 0;
    if (this_00 == (Control *)0x0) {
      local_3c = 0;
    }
    else {
      local_3c = hotspot_ctor(this_00);
    }
    local_8 = 0xffffffff;
    *(i32 *)(this->pad_200 + local_24 * 0x1c + 0x18) = local_3c;
    if (this == (FrameWindow *)0x0) {
      local_40 = (u8 *)0x0;
    }
    else {
      local_40 = this->pad_48;
    }
    hotspot_create
              (*(ClickControl **)(this->pad_200 + local_24 * 0x1c + 0x18),(iptr)local_40,
               local_24 + 1000,(iptr)local_20);
    hotspot_set_click_callback
              (*(HotspotClickSetView **)(this->pad_200 + local_24 * 0x1c + 0x18),ADDR(0x401b68, frame_wnd_on_caption_button_click));
    local_28 = local_28 + iVar1 + frame_padding;
  }
  return;
}
#undef frame_border_width
#undef local_40
#undef local_3c
#undef local_28
#undef local_24
#undef local_20
#undef local_10
#undef puStack_c
#undef local_8

/* 0055318c auto */
void __thiscall frame_wnd_add_caption_button(PortraitDialog *this,iptr param_1,i32 param_2)

{
  u8 *puVar1;
  u32 uVar2;
  i32 uVar3;
  
  if ((int)this->caption_button_count < 6) {
    uVar2 = this->caption_button_count;
    this->caption_button_count++;
    *(iptr *)(this[1].pad_48 + uVar2 * 0x1c - 0x3c) = param_1;
    *(i32 *)(this->pad_200 + uVar2 * 0x1c) = param_2;
    uVar3 = sprite_width((Sprite *)param_1);
    *(i32 *)(this[1].pad_48 + uVar2 * 0x1c - 0x44) = uVar3;
    uVar3 = sprite_height((Sprite *)param_1);
    *(i32 *)(this[1].pad_48 + uVar2 * 0x1c - 0x40) = uVar3;
    puVar1 = this[1].pad_48 + uVar2 * 0x1c - 0x38;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
  }
  return;
}

/* 0055324c auto */
#define local_14 (*(u32 *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(u32 *)(frame_ + FRAME_OFF(8)))
#define local_c (*(u32 *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(u32 *)(frame_ + FRAME_OFF(16)))
void __thiscall frame_wnd_set_caption(FrameWindow *this,iptr param_1)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  _memset(this->pad_134,0,0x84);
  _strncpy((char *)this->pad_134,(char *)param_1,0x83);
  frame_wnd_draw_caption(this);
  local_14 = this->frame_rect;
  local_10 = this->frame_top;
  local_c = this->frame_right;
  local_8 = this->client_top;
  wnd_blit_surface_rect((DibSurface *)this,(iptr)&local_14);
  return;
}
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 005532d7 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall frame_wnd_destroy_caption_buttons(WindowObjectView *this)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; local_8 < 6; local_8++) {
    if (this[local_8 * 7 + 0x86].field_0 != 0) {
      if ((Hotspot *)this[local_8 * 7 + 0x86].field_0 != (Hotspot *)0x0) {
        hotspot_scalar_dtor((Hotspot *)this[local_8 * 7 + 0x86].field_0,1);
      }
      this[local_8 * 7 + 0x86].field_0 = 0;
    }
  }
  return;
}
#undef local_8

/* 00553379 auto */
void __thiscall frame_wnd_close(DibSurface *this)

{
  frame_wnd_destroy_caption_buttons((WindowObjectView *)this);
  wnd_destroy_with_surface(this);
  return;
}

/* 0055339f auto */
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(8)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(16)))
SurfaceWindow * __thiscall frame_wnd_ctor(SurfaceWindow *this)

{
  u8 *puVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  surfwnd_ctor(this);
  this->vtable = (u32)&PTR_FUN_0061d6dc;
  for (local_14 = 0; local_14 < 6; local_14++) {
    puVar1 = this[1].pad_104 + local_14 * 0x1c;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
  }
  return this;
}
#undef local_14
#undef local_10
#undef puStack_c
#undef local_8

/* 00553444 auto */
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    public: virtual __thiscall COleCntrFrameWnd::~COleCntrFrameWnd(void)
   
   Library: Visual Studio 1998 Debug */

void __thiscall frame_wnd_dtor(DibSurface *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  this->vtable = (u32)&PTR_FUN_0061d6dc;
  local_8 = 0;
  frame_wnd_destroy_caption_buttons((WindowObjectView *)this);
  wnd_destroy_with_surface(this);
  local_8 = 0xffffffff;
  /* inlined unwind funclet 0055349b */ { surfwnd_dtor(*(SurfaceWindow **)((iptr)&this)); }
  return;
}
#undef uStack_10
#undef puStack_c
#undef local_8

/* 005534bc auto */
#define frame_border_width (*(u32 *)((u8 *)&g.d_0063359c))
#define frame_caption_height (*(u32 *)((u8 *)&g.d_00633598))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(0)))
void __thiscall
frame_wnd_create
          (FrameWindow *this,int param_1,uint param_2,int param_3,int param_4,int param_5,
          int param_6,u32 param_7,u32 param_8,u32 param_9)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 == 0) {
    crt_strcpy(this->pad_134,&frame_default_title_str);
  }
  else {
    crt_strcpy(this->pad_134,param_1);
  }
  *(i8 **)this->pad_2d4 = &ui_text_font;
  this->title_font = (uptr)&caption_font;
  this->title_small_font = (uptr)&caption_small_font;
  this->show_turn_timer = 0;
  this->show_turn_status = 0;
  this->style_flags = param_2;
  this->caption_height = param_8;
  this->border_width = param_9;
  this->resize_border = param_7;
  this->caption_button_count = 0;
  this->on_caption_button = 0;
  if ((param_2 & 4) != 0) {
    this->caption_height = frame_caption_height;
    this->border_width = frame_border_width;
  }
  if ((param_2 & 8) == 0) {
    local_8 = 0x202;
  }
  else {
    local_8 = 0x802;
  }
  if (this->caption_height != 0) {
    local_8 = local_8 | 0x400;
  }
  if (this->resize_border != 0) {
    local_8 = local_8 | 0x1000;
  }
  if ((param_2 & 2) == 0) {
    param_5 += this->border_width * 2;
    param_6 = param_6 + this->caption_height + this->border_width;
  }
  if ((param_2 & 1) != 0) {
    param_3 = (screen_width >> 1) - (param_5 >> 1);
    param_4 = (screen_height >> 1) - (param_6 >> 1);
  }
  wnd_create_with_surface
            ((DibSurface *)this,0,local_8,param_3,param_4,param_5,param_6,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)),ADDR(0x6553d8, ((u8 *)&g.d_006553d8)));
  if (this->caption_height != 0) {
    wnd_set_caption_height((WndBase *)this->pad_48,this->caption_height);
  }
  if (this->resize_border != 0) {
    wnd_set_resize_border((WndBase *)this->pad_48,this->resize_border);
  }
  frame_wnd_layout(this);
  wnd_set_drag_begin_callback((WndDragBeginSetView *)(this->pad_48 + 0x10),ADDR(0x402a1d, mp_window_drag_begin));
  wnd_set_drag_end_callback((WndDragEndSetView *)(this->pad_48 + 0x10),ADDR(0x401401, mp_window_drag_end));
  return;
}
#undef frame_border_width
#undef frame_caption_height
#undef screen_height
#undef local_8

/* 00553d30 auto */
u32 __thiscall wnd_set_drag_begin_callback(WndDragBeginSetView *this,iptr param_1)

{
  u32 uVar1;
  
  uVar1 = this->on_drag_begin;
  this->on_drag_begin = param_1;
  return uVar1;
}

/* 00553d70 auto */
u32 __thiscall wnd_set_drag_end_callback(WndDragEndSetView *this,iptr param_1)

{
  u32 uVar1;
  
  uVar1 = this->on_drag_end;
  this->on_drag_end = param_1;
  return uVar1;
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
#define local_128 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_118 (*(DllHandle *)(frame_ + FRAME_OFF(16)))
#define local_114 (*(DibSurface *)(frame_ + FRAME_OFF(20)))
#define local_cc (*(i8 (*)[128])(frame_ + FRAME_OFF(92)))
#define local_4c (*(Sprite *)(frame_ + FRAME_OFF(220)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(280)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(284)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(288)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl frame_texture_load(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(296)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  gfx_build_grey_remap();
  surface_ctor(&local_114);
  local_8 = 0;
  sprite_init(&local_4c);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  frame_texture_loaded_i32 = 1;
  str_clear((iptr)local_cc);
  str_append((iptr)local_cc,ADDR(0x633db0, ((u8 *)&g.d_00633db0)));
  iVar1 = file_resolve_path((iptr)local_cc);
  if (iVar1 == 0) {
    surface_create((DibSurface *)&frame_texture_surface,0x40,0x20);
    surface_fill((DibSurface *)&frame_texture_surface,0x21);
  }
  else {
    resource_dll_load(&local_118,(iptr)local_cc);
    local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),2);
    iVar1 = surface_load_gif_resource(&local_114,999,10,0xec,ADDR(0x6ab6a8, ((u8 *)&g.d_006ab6a8)));
    if (iVar1 == 0) {
      MessageBoxA((HWND)0x0,s_Failed_to_load_civ2art_gif_00633dcc,s_NOTICE_00633dc4,0x40);
    }
    else {
      sprite_grab_from_surface(&local_4c,(iptr)&local_114,2,1,1,0x40,0x20);
      surface_create((DibSurface *)&frame_texture_surface,0x40,0x20);
      sprite_draw(&local_4c,(iptr)local_128,ADDR(0x6abae0, ((u8 *)&g.d_006abae0)),0,0);
      sprite_free(&local_4c);
      surface_release(&local_114);
    }
    dll_handle_free(&local_118);
    (*(i8 *)((char *)&local_8 + 0)) = 1;
    /* inlined unwind funclet 00568348 */ { dll_free((DllHandle *)((iptr)&local_118)); }
  }
  frame_texture_load_hook_nop();
  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
  /* inlined unwind funclet 00568354 */ { sprite_destroy((Sprite *)((iptr)&local_4c)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet 0056835d */ { surface_dtor((DibSurface *)((iptr)&local_114)); }
  return;
}
#undef frame_texture_loaded_i32
#undef local_128
#undef local_118
#undef local_114
#undef local_cc
#undef local_4c
#undef uStack_10
#undef puStack_c
#undef local_8

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

u32 __thiscall wnd_set_rbuttondown_handler(WndHandlersMouseSetView *this,iptr param_1)

{
  u32 uVar1;
  
  uVar1 = this[2].field_0;
  this[2].field_0 = param_1;
  return uVar1;
}

/* 00578610 auto */
/* Library Function - Single Match
    public: int __thiscall ios_base::width(int)
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall wnd_set_rbuttonup_any_handler(WndHandlersMouseSetView *this,iptr param_1)

{
  u32 uVar1;
  
  uVar1 = this[2].field_4;
  this[2].field_4 = param_1;
  return uVar1;
}

/* 00578650 auto */
void __thiscall menu_storage_reinit(GameMenu *this,uint param_1)

{
  memblock_free((iptr)this->pad_4);
  memblock_init((iptr)this->pad_4,0xb,param_1);
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
void __thiscall menu_reset(GameMenu *this,i32 param_1)

{
  memblock_detach((iptr)this->pad_4);
  menu_clear_lists(this);
  menu_storage_reinit(this,param_1);
  return;
}

/* 005786f1 auto */
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
GameMenu * __thiscall menu_ctor(GameMenu *this,i32 param_1)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  menu_handle_ctor(this);
  local_8 = 0;
  memblock_ctor((MemBlock *)this->pad_4);
  menu_reset(this,param_1);
  return this;
}
#undef local_10
#undef puStack_c
#undef local_8

/* 00578770 auto */
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
void __thiscall menu_dtor(GameMenu *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  memblock_free((iptr)this->pad_4);
  local_8 = 0xffffffff;
  /* inlined unwind funclet 005787bd */ { menu_handle_dtor(*(GameMenu **)((iptr)&this)); }
  return;
}
#undef uStack_10
#undef puStack_c
#undef local_8

/* 005787de auto */
#define local_c (*(uptr *)(frame_ + FRAME_OFF(4)))
i32 __thiscall menu_find_menu(GameMenu *this,int param_1)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = this->menus;
  while( true ) {
    if (local_c == 0) {
      return 0;
    }
    if (*(int *)(local_c + 4) == param_1) break;
    local_c = *(uptr *)(local_c + 0x10);
  }
  return local_c;
}
#undef local_c

/* 00578840 auto */
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(uptr *)(frame_ + FRAME_OFF(8)))
int __thiscall menu_visible_index(GameMenu *this,uptr param_1)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 1;
  for (local_8 = this->menus; (local_8 != 0 && (param_1 != local_8));
      local_8 = *(uptr *)(local_8 + 0x10)) {
    if ((*(byte *)(local_8 + 8) & 2) == 0) {
      local_c++;
    }
  }
  return local_c;
}
#undef local_c
#undef local_8

/* 005788a9 auto */
#define local_10 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_c (*(uptr *)(frame_ + FRAME_OFF(4)))
i32 __thiscall menu_id_at_visible_index(GameMenu *this,int param_1)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_10 = 1;
  local_c = this->menus;
  do {
    if (local_c == 0) {
      return 0xffffffff;
    }
    if ((*(byte *)(local_c + 8) & 2) == 0) {
      if (local_10 == param_1) {
        return *(i32 *)(local_c + 4);
      }
      local_10++;
    }
    local_c = *(uptr *)(local_c + 0x10);
  } while( true );
}
#undef local_10
#undef local_c

/* 00578922 auto */
#define local_10 (*(uptr *)(frame_ + FRAME_OFF(0)))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(8)))
iptr __thiscall menu_find_item(GameMenu *this,int param_1)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  local_10 = this->menus;
  do {
    if (local_10 == 0) {
      return local_8;
    }
    for (local_c = *(iptr *)(local_10 + 0x18); local_c != 0; local_c = *(iptr *)(local_c + 0x10)) {
      if (*(int *)(local_c + 4) == param_1) {
        local_8 = local_c;
        break;
      }
    }
    local_10 = *(uptr *)(local_10 + 0x10);
  } while( true );
}
#undef local_10
#undef local_c
#undef local_8

/* 005789aa auto */
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(8)))
int __thiscall menu_item_visible_index(GameMenu *this,iptr param_1)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 1;
  for (local_8 = *(iptr *)(*(int *)(param_1 + 0x18) + 0x18); (local_8 != 0 && (param_1 != local_8));
      local_8 = *(iptr *)(local_8 + 0x10)) {
    if ((*(byte *)(local_8 + 8) & 2) == 0) {
      local_c++;
    }
  }
  return local_c;
}
#undef local_c
#undef local_8

/* 00578a1c auto */
#define local_10 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(4)))
i32 __thiscall menu_item_id_at_visible_index(GameMenu *this,i32 param_1,int param_2)

{
  iptr iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_10 = 1;
  iVar1 = menu_find_menu(this,param_1);
  if (iVar1 != 0) {
    for (local_c = *(iptr *)(iVar1 + 0x18); local_c != 0; local_c = *(iptr *)(local_c + 0x10)) {
      if ((*(byte *)(local_c + 8) & 2) == 0) {
        if (local_10 == param_2) {
          return *(i32 *)(local_c + 4);
        }
        local_10++;
      }
    }
  }
  return 0xffffffff;
}
#undef local_10
#undef local_c

/* 00578b06 auto */
#define local_c (*(uptr *)(frame_ + FRAME_OFF(4)))
i32 * __thiscall menu_add_menu(GameMenu *this,i32 param_1,char *param_2)

{
  i32 *puVar1;
  size_t sVar2;
  i32 uVar3;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  puVar1 = (i32 *)memblock_alloc((iptr)this->pad_4,0x1c);
  if (this->menus == 0) {
    this->menus = (uptr)puVar1;
    puVar1[5] = 0;
  }
  else {
    for (local_c = this->menus; *(int *)(local_c + 0x10) != 0;
        local_c = *(uptr *)(local_c + 0x10)) {
    }
    *(i32 **)(local_c + 0x10) = puVar1;
    puVar1[5] = local_c;
  }
  puVar1[4] = 0;
  puVar1[6] = 0;
  puVar1[2] = 0;
  puVar1[1] = param_1;
  puVar1[3] = 0;
  sVar2 = _strlen(param_2);
  uVar3 = memblock_alloc((iptr)this->pad_4,sVar2 + 1);
  *puVar1 = uVar3;
  crt_strcpy(*puVar1,param_2);
  str_pipes_to_tabs(*puVar1);
  this->menu_flags = this->menu_flags & 0xffff7fff;
  return puVar1;
}
#undef local_c

/* 00578c12 auto */
#define local_10 (*(size_t *)(frame_ + FRAME_OFF(0)))
#define local_c (*(i32 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(8)))
i32 * __thiscall
menu_add_item
          (GameMenu *this,i32 param_1,i32 param_2,iptr param_3,size_t param_4)

{
  iptr iVar1;
  size_t sVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = (i32 *)0x0;
  iVar1 = menu_find_menu(this,param_1);
  if (iVar1 != 0) {
    local_c = (i32 *)memblock_alloc((iptr)this->pad_4,0x1c);
    if (*(int *)(iVar1 + 0x18) == 0) {
      *(i32 **)(iVar1 + 0x18) = local_c;
      local_c[5] = 0;
    }
    else {
      for (local_8 = *(iptr *)(iVar1 + 0x18); *(int *)(local_8 + 0x10) != 0;
          local_8 = *(iptr *)(local_8 + 0x10)) {
      }
      *(i32 **)(local_8 + 0x10) = local_c;
      local_c[5] = local_8;
    }
    local_c[6] = iVar1;
    local_c[4] = 0;
    local_c[2] = 0;
    local_c[1] = param_2;
    local_c[3] = 0;
    if (param_3 == 0) {
      *local_c = 0;
    }
    else {
      sVar1 = _strlen((char *)param_3);
      if ((int)sVar1 < (int)param_4) {
        local_10 = param_4;
      }
      else {
        local_10 = _strlen((char *)param_3);
      }
      uVar2 = memblock_alloc((iptr)this->pad_4,local_10 + 1);
      *local_c = uVar2;
      crt_strcpy(*local_c,param_3);
      str_pipes_to_tabs(*local_c);
    }
    this->menu_flags = this->menu_flags & 0xffff7fff;
  }
  return local_c;
}
#undef local_10
#undef local_c
#undef local_8

/* 00578d8a auto */
#define menu_command_callback (*(code * *)((u8 *)&g.d_0063430c))
void __cdecl menu_dispatch_command(i32 param_1,i32 param_2)

{
  i32 uVar1;
  i32 uVar2;
  
  if (menu_command_callback != (code *)0x0) {
    uVar1 = menu_id_at_visible_index(menu_active_object,param_1);
    uVar2 = menu_item_id_at_visible_index(menu_active_object,uVar1,param_2);
    (*menu_command_callback)(uVar1,uVar2);
  }
  return;
}
#undef menu_command_callback

/* 00578de8 auto */
void __thiscall menu_attach_to_window(GameMenu *this,ModalMenuWindow *param_1)

{
  if (param_1 != (ModalMenuWindow *)0x0) {
    menu_owner_window = param_1;
    menu_active_object = this;
    wnd_attach_menu(param_1,(iptr)this);
    wnd_set_menu_callback((WndMenuCbSetView *)param_1,ADDR(0x40341d, menu_dispatch_command));
  }
  return;
}

/* 00578e38 auto */
#define menu_command_callback (*(iptr *)((u8 *)&g.d_0063430c))
void __thiscall menu_set_command_handler(GameMenu *this,iptr param_1)

{
  menu_active_object = this;
  menu_command_callback = param_1;
  return;
}
#undef menu_command_callback

/* 00578e60 auto */
i32 __thiscall menu_apply_item_enabled(GameMenu *this,i32 param_1)

{
  iptr iVar1;
  uint uVar1;
  i32 uVar2;
  i32 uVar3;
  
  iVar1 = menu_find_item(this,param_1);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar1 = ~*(uint *)(iVar1 + 8) & 1;
    uVar2 = menu_item_visible_index(this,iVar1);
    uVar3 = menu_visible_index(this,*(i32 *)(iVar1 + 0x18));
    uVar2 = menu_native_enable(this,uVar3,uVar2,uVar1);
  }
  return uVar2;
}

/* 00578ec7 auto */
void __thiscall menu_apply_item_checked(GameMenu *this,i32 param_1)

{
  iptr iVar1;
  uint uVar1;
  i32 uVar2;
  i32 uVar3;
  
  iVar1 = menu_find_item(this,param_1);
  if (iVar1 != 0) {
    uVar1 = *(uint *)(iVar1 + 8) & 4;
    uVar2 = menu_item_visible_index(this,iVar1);
    uVar3 = menu_visible_index(this,*(i32 *)(iVar1 + 0x18));
    menu_native_check(this,uVar3,uVar2,uVar1);
  }
  return;
}

/* 00578f2c auto */
#define local_118 (*(i32 * *)(frame_ + FRAME_OFF(0)))
#define local_114 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_110 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_10c (*(i32 * *)(frame_ + FRAME_OFF(12)))
#define local_108 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_104 (*(i8 (*)[256])(frame_ + FRAME_OFF(20)))
void __thiscall menu_rebuild(GameMenu *this,iptr param_1)

{
  i8 frame_[FRAME_OFF(280)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((this->menu_flags & 0x8000) == 0) {
    local_104[0] = 0;
    local_118 = (i32 *)this->menus;
    local_114 = 1;
    for (; local_118 != (i32 *)0x0; local_118 = (i32 *)local_118[4]) {
      if ((*(byte *)(local_118 + 2) & 2) == 0) {
        crt_strcat(local_104,*local_118);
        crt_strcat(local_104,&menu_title_sep_str);
      }
      if (param_1 == 0) {
        for (local_108 = 0x1e; 0 < local_108; local_108--) {
          menu_native_delete(this,local_114,local_108);
        }
        local_118[3] = 0;
      }
      local_114++;
    }
    if (param_1 != 0) {
      menu_native_build(this,(iptr)local_104);
    }
    local_118 = (i32 *)this->menus;
    local_114 = 1;
    for (; local_118 != (i32 *)0x0; local_118 = *(i32 **)((int)local_118 + 0x10)) {
      if ((*(byte *)((int)local_118 + 8) & 2) == 0) {
        if (param_1 != 0) {
          menu_native_delete(this,local_114,1);
        }
        local_10c = *(i32 **)((int)local_118 + 0x18);
        local_110 = 1;
        for (; local_10c != (i32 *)0x0; local_10c = (i32 *)local_10c[4]) {
          if ((*(byte *)(local_10c + 2) & 2) == 0) {
            *(int *)((int)local_118 + 0xcU) = *(int *)((int)local_118 + 0xcU) + 1;
            menu_native_insert(this,local_114,local_110,*local_10c);
            if ((*(byte *)(local_10c + 2) & 1) != 0) {
              menu_apply_item_enabled(this,local_10c[1]);
            }
            if ((*(byte *)(local_10c + 2) & 4) != 0) {
              menu_apply_item_checked(this,local_10c[1]);
            }
            local_110++;
          }
        }
        local_114++;
      }
    }
    this->menu_flags = this->menu_flags | 0x8000;
    menu_attach_to_window(this,param_1);
  }
  if (menu_owner_window != (ModalMenuWindow *)0x0) {
    wnd_redraw_menu_bar(menu_owner_window);
  }
  return;
}
#undef local_118
#undef local_114
#undef local_110
#undef local_10c
#undef local_108
#undef local_104

/* 00579260 auto */
void __thiscall menu_set_item_hidden(GameMenu *this,i32 param_1,int param_2)

{
  iptr iVar1;
  
  iVar1 = menu_find_item(this,param_1);
  if (iVar1 != 0) {
    if (param_2 == 0) {
      if ((*(byte *)(iVar1 + 8) & 2) != 0) {
        this->menu_flags = this->menu_flags & 0xffff7fff;
      }
      *(uint *)(iVar1 + 8) = *(uint *)(iVar1 + 8) & 0xfffffffd;
    }
    else {
      if ((*(byte *)(iVar1 + 8) & 2) == 0) {
        this->menu_flags = this->menu_flags & 0xffff7fff;
      }
      *(uint *)(iVar1 + 8) = *(uint *)(iVar1 + 8) | 2;
    }
  }
  return;
}

/* 005792e1 auto */
#define local_c (*(GameMenu * *)(frame_ + FRAME_OFF(4)))
GameMenu * __thiscall
menu_set_item_enabled(GameMenu *this,i32 param_1,GameMenu *param_2)

{
  GameMenu *pCVar1;
  GameMenu *pCVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  pCVar1 = (GameMenu *)menu_find_item(this,param_1);
  pCVar2 = pCVar1;
  if (pCVar1 != (GameMenu *)0x0) {
    param_2 = (GameMenu *)(uint)(param_2 != (GameMenu *)0x0);
    local_c = (GameMenu *)(uint)((pCVar1->pad_4[4] & 1) != 0);
    if (param_2 == (GameMenu *)0x0) {
      *(uint *)(pCVar1->pad_4 + 4) = *(uint *)(pCVar1->pad_4 + 4) & 0xfffffffe;
    }
    else {
      *(uint *)(pCVar1->pad_4 + 4) = *(uint *)(pCVar1->pad_4 + 4) | 1;
    }
    pCVar2 = this;
    if ((((this->menu_flags & 0x8000) != 0) && (pCVar2 = pCVar1, (pCVar1->pad_4[4] & 2) == 0)) &&
       (pCVar2 = param_2, local_c != param_2)) {
      pCVar2 = (GameMenu *)menu_apply_item_enabled(this,param_1);
    }
  }
  return pCVar2;
}
#undef local_c

/* 005793a3 auto */
void __thiscall menu_remove_item(GameMenu *this,i32 param_1)

{
  iptr iVar1;
  i32 uVar1;
  i32 uVar2;
  
  iVar1 = menu_find_item(this,param_1);
  if (iVar1 != 0) {
    uVar1 = menu_item_visible_index(this,iVar1);
    uVar2 = menu_visible_index(this,*(i32 *)(iVar1 + 0x18));
    menu_native_delete(this,uVar2,uVar1);
    *(i32 *)(*(int *)(iVar1 + 0x14) + 0x10) = *(i32 *)(iVar1 + 0x10);
  }
  return;
}

/* 0057940d auto */
void __thiscall menu_set_item_checked(GameMenu *this,i32 param_1,int param_2)

{
  byte bVar1;
  iptr iVar2;
  
  iVar2 = menu_find_item(this,param_1);
  if (iVar2 != 0) {
    bVar1 = *(byte *)(iVar2 + 8);
    if (param_2 != 0) {
      *(uint *)(iVar2 + 8) = *(uint *)(iVar2 + 8) | 4;
    }
    else {
      *(uint *)(iVar2 + 8) = *(uint *)(iVar2 + 8) & 0xfffffffb;
    }
    if ((((this->menu_flags & 0x8000) != 0) && ((*(byte *)(iVar2 + 8) & 2) == 0)) &&
       (((bVar1 & 4) != 0) != (param_2 != 0))) {
      menu_apply_item_checked(this,param_1);
    }
  }
  return;
}

/* 005794cf auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __thiscall menu_set_menu_enabled(GameMenu *this,i32 param_1,i32 param_2)

{
  iptr iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = menu_find_menu(this,param_1);
  if (iVar1 != 0) {
    for (local_8 = *(iptr *)(iVar1 + 0x18); local_8 != 0; local_8 = *(iptr *)(local_8 + 0x10)) {
      menu_set_item_enabled(this,*(i32 *)(local_8 + 4),param_2);
    }
  }
  return;
}
#undef local_8

/* 0057953e auto */
void __thiscall menu_set_item_text(GameMenu *this,i32 param_1,iptr param_2)

{
  i32 *puVar1;
  i32 uVar2;
  i32 uVar3;
  i32 uVar4;
  
  puVar1 = (i32 *)menu_find_item(this,param_1);
  if (puVar1 != (i32 *)0x0) {
    crt_strcpy(*puVar1,param_2);
    str_pipes_to_tabs(*puVar1);
    if (((this->menu_flags & 0x8000) != 0) && ((*(byte *)(puVar1 + 2) & 2) == 0)) {
      uVar4 = *puVar1;
      uVar2 = menu_item_visible_index(this,(iptr)puVar1);
      uVar3 = menu_visible_index(this,puVar1[6]);
      menu_native_set_text(this,uVar3,uVar2,uVar4);
    }
  }
  return;
}

/* 005799c0 auto */
void __thiscall menu_native_build(GameMenu *this,iptr param_1)

{
  u32 uVar1;
  
  uVar1 = menu_hmenu_build_from_spec(param_1);
  this->hmenu = uVar1;
  return;
}

/* 00579a00 auto */
void __thiscall
menu_native_insert(GameMenu *this,i32 param_1,i32 param_2,i32 param_3)

{
  menu_hmenu_insert_item(this->hmenu,param_1,param_2,param_3);
  return;
}

/* 00579a40 auto */
void __thiscall menu_native_delete(GameMenu *this,i32 param_1,i32 param_2)

{
  menu_hmenu_delete_item(this->hmenu,param_1,param_2);
  return;
}

/* 00579a80 auto */
void __thiscall
menu_native_set_text(GameMenu *this,i32 param_1,i32 param_2,i32 param_3)

{
  menu_hmenu_set_item_text(this->hmenu,param_1,param_2,param_3);
  return;
}

/* 00579ac0 auto */
i32 __thiscall
menu_native_enable(GameMenu *this,i32 param_1,i32 param_2,i32 param_3)

{
  i32 uVar1;
  
  uVar1 = menu_hmenu_enable_item(this->hmenu,param_1,param_2,param_3);
  return uVar1;
}

/* 00579b00 auto */
void __thiscall
menu_native_check(GameMenu *this,i32 param_1,i32 param_2,i32 param_3)

{
  menu_hmenu_check_item(this->hmenu,param_1,param_2,param_3);
  return;
}

/* 00579b40 auto */
void __thiscall wnd_attach_menu(ModalMenuWindow *this,iptr param_1)

{
  i32 uVar1;
  iptr iVar2;
  
  uVar1 = menu_get_hmenu((MenuHandleView *)param_1);
  iVar2 = wnd_get_window((WndBase *)this);
  wnd_obj_attach_menu(iVar2,uVar1);
  this->menu = param_1;
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

void __thiscall wnd_set_menu_callback(WndMenuCbSetView *this,iptr param_1)

{
  this->on_menu = param_1;
  return;
}

/* 00579bf0 auto */
void __thiscall wnd_redraw_menu_bar(ModalMenuWindow *this)

{
  iptr iVar1;
  
  if (this->menu != 0) {
    iVar1 = wnd_get_window((WndBase *)this);
    menu_redraw_bar(iVar1);
  }
  return;
}

/* 00589d50 auto */
i32 __thiscall wnd_frame_width(WndBase *this)

{
  i32 uVar1;
  
  uVar1 = wnd_obj_frame_width(this->native_wnd);
  return uVar1;
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
  int iVar1;
  iptr iVar2;
  i32 uVar3;
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
    iVar1 = unit_stack_sum(unit,2);
    if (iVar1 == 1) {
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
    iVar1 = unit_stack_sum(unit,2);
    if (iVar1 == 1) goto LAB_0058d58e;
  }
  uVar3 = 1;
  iVar2 = label_string(*(i32 *)(label_string_ids + 0xf8));
  unit = unit_stack_select_dialog(unit,iVar2,uVar3);
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
void __cdecl dlg_set_palette(iptr param_1)

{
  dlg_palette = param_1;
  return;
}
#undef dlg_palette

/* 0059d3c9 auto */
#define dlg_parent_window (*(iptr *)((u8 *)&g.d_006359c4))
void __cdecl dlg_set_parent_window(iptr param_1)

{
  dlg_parent_window = param_1;
  return;
}
#undef dlg_parent_window

/* 0059d3e1 auto */
#define dlg_default_x (*(i32 *)((u8 *)&g.d_006359cc))
#define dlg_default_y (*(i32 *)((u8 *)&g.d_006359d0))
void __cdecl dialog_set_default_offset(i32 param_1,i32 param_2)

{
  dlg_default_x = param_1;
  dlg_default_y = param_2;
  return;
}
#undef dlg_default_x
#undef dlg_default_y

/* 0059d401 auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl dialog_load_button_labels(void)

{
  int iVar1;
  i32 uVar2;
  i8 *puVar3;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = text_open_section(ADDR(0x635ac4, ((u8 *)&g.d_00635ac4)),ADDR(0x635abc, ((u8 *)&g.d_00635abc)));
  if (iVar1 == 0) {
    for (local_8 = 0; local_8 < 3; local_8++) {
      uVar2 = text_read_line_pooled();
      *(i32 *)(&dialog_button_label_ids + local_8 * 4) = uVar2;
      puVar3 = (i8 *)label_string(*(i32 *)(&dialog_button_label_ids + local_8 * 4));
      (&dialog_button_labels)[local_8] = puVar3;
    }
  }
  return;
}
#undef local_8

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
dialog_set_colors(i32 param_1,i32 param_2,i32 param_3,i32 param_4,
            i32 param_5,i32 param_6,i32 param_7,i32 param_8,
            i32 param_9)

{
  dlg_text_color = (i8)param_1;
  dlg_text_shadow_color = (i8)param_2;
  dlg_frame_color = (i8)param_3;
  dlg_highlight_text_color = (i8)param_4;
  dlg_bg_color = (i8)param_5;
  dlg_bevel_light_color = (i8)param_6;
  dlg_bevel_dark_color = (i8)param_7;
  dlg_title_text_color = (i8)param_8;
  dlg_title_shadow_color = (i8)param_9;
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
dialog_set_list_colors(i32 param_1,i32 param_2,i32 param_3,i32 param_4,
            i32 param_5,i32 param_6,i32 param_7)

{
  list_bg_color = param_1;
  list_text_color = param_2;
  list_shadow_color = param_3;
  list_sel_bg_color = param_4;
  dlg_sel_text_color = param_5;
  dlg_sel_text_shadow_color = param_6;
  dialog_default_list_color = param_7;
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
void __cdecl dialog_set_frame_tile_surface(iptr param_1)

{
  dlg_frame_tile_surface = param_1;
  return;
}
#undef dlg_frame_tile_surface

/* 0059d5b5 auto */
void __thiscall dialog_reset_string_pool(DialogCore *this,uint param_1)

{
  memblock_free((iptr)&this[0xe].field_24);
  memblock_init((iptr)&this[0xe].field_24,9,param_1);
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
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall dialog_init_defaults(Dialog *this)

{
  u8 *puVar1;
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
  this->field_a8 = dialog_default_list_color;
  for (local_8 = 0; local_8 < 2; local_8++) {
    puVar1 = this->pad_1f8 + local_8 * 4 + 8;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
    puVar1 = this->pad_1f8 + local_8 * 4 + 0x10;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
    puVar1 = this->pad_178 + local_8 * 4 + 0x40;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
  }
  this->cur_pane = 0;
  this->edit_width = 0;
  this->field_124 = this->edit_width;
  this->max_sprite_width = this->field_124;
  this->content_width = this->max_sprite_width;
  this->option_width = this->content_width;
  this->selected_option = 0;
  this->selected_sprite = 0;
  this->option_tail = 0;
  this->option_list = this->option_tail;
  this->line_list = 0;
  this->sprite_list = 0;
  this->edit_field_list = 0;
  this->field_b0 = 0;
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
  this->field_dc = 0;
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
#undef local_8

/* 0059db08 auto */
Dialog * __thiscall dialog_ctor(Dialog *this,i32 param_1)

{
  memblock_ctor((MemBlock *)this->pad_254);
  this->pool_ptr = 0;
  this->pool_handle = this->pool_ptr;
  dialog_init_defaults(this);
  this->pool_size = (u16)param_1;
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
      err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x635aec, ((u8 *)&g.d_00635aec)),ADDR(0x635acc, ((u8 *)&g.d_00635acc)),0x19c);
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
  i32 uVar1;
  
  dialog_close(this);
  uVar1 = memblock_free((iptr)this->pad_254);
  return uVar1;
}

/* 0059dfb9 auto */
void __thiscall
dialog_init
          (Dialog *this,iptr param_1,iptr param_2,iptr param_3,u32 param_4)

{
  i32 uVar1;
  
  if ((this->style_flags & 0x20) == 0) {
    memblock_init((iptr)this->pad_254,9,CONCAT22((short)((uint)this >> 0x10),this->pool_size));
  }
  else {
    dialog_close(this);
    dialog_init_defaults(this);
    dialog_reset_string_pool((DialogCore *)this,(uint)this->pool_size);
  }
  dialog_set_font((DialogTextView *)this,(iptr)dialog_default_text_font);
  dialog_set_title_font((DialogCore *)this,(iptr)dialog_default_title_font);
  dialog_set_list_font((DialogCore *)this,(iptr)dialog_default_list_font);
  this->surf_wnd = param_1;
  this->bg_surface = param_2;
  this->result_id = 0;
  this->style_flags = param_4;
  if (param_3 == 0) {
    dialog_set_width((DialogWindowView *)this,0x1b8);
  }
  else {
    this->origin_x = *(u32 *)param_3;
    this->origin_y = *(u32 *)(param_3 + 4);
    uVar1 = rect_width(param_3);
    dialog_set_width((DialogWindowView *)this,uVar1);
    uVar1 = rect_height(param_3);
    dialog_set_height((DialogCore *)this,uVar1);
  }
  if (param_1 != 0) {
    this->style_flags = this->style_flags | 0x10;
  }
  return;
}

/* 0059e0eb auto */
#define local_8 (*(int * *)(frame_ + FRAME_OFF(0)))
i32 __thiscall dialog_set_item_text(void *this,int param_1,iptr param_2)

{
  size_t sVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = *(int **)((int)this + 0x230); (*local_8 != param_1 && (local_8 != (int *)0x0));
      local_8 = (int *)local_8[7]) {
  }
  if (((local_8 != (int *)0x0) && (-1 < local_8[3])) &&
     (sVar1 = _strlen((char *)param_2), (int)(sVar1 + 1) <= local_8[3])) {
    crt_strcpy(local_8[2],param_2);
    return 1;
  }
  return 0;
}
#undef local_8

/* 0059e18b auto */
#define local_c (*(int * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int * *)(frame_ + FRAME_OFF(8)))
int * __thiscall
dialog_add_line
          (DialogAddLineView *this,iptr param_1,int param_2,int param_3,int param_4,int param_5)

{
  int *piVar1;
  size_t sVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = (int *)0x0;
  for (local_8 = (int *)this->field_230; local_8 != (int *)0x0; local_8 = (int *)local_8[7]) {
    local_c = local_8;
  }
  piVar1 = (int *)memblock_alloc((iptr)(this->pad_234 + 0x20),0x20);
  if (local_c == (int *)0x0) {
    this->field_230 = (uptr)piVar1;
    *piVar1 = 1;
  }
  else {
    local_c[7] = (int)piVar1;
    *piVar1 = *local_c + 1;
  }
  piVar1[7] = 0;
  piVar1[1] = 0;
  if (*(char *)param_1 == '^') {
    if (*(char *)(param_1 + 1) == '^') {
      piVar1[1] = piVar1[1] | 1;
      param_1 += 2;
    }
    else {
      piVar1[1] = piVar1[1] | 2;
      param_1++;
    }
  }
  if (0 < param_4) {
    sVar2 = _strlen((char *)param_1);
    if ((int)(sVar2 + 1) < param_4) {
      iVar3 = memblock_alloc((iptr)(this->pad_234 + 0x20),param_4 + 1);
      piVar1[2] = iVar3;
      piVar1[3] = param_4 + 1;
      goto LAB_0059e2e4;
    }
  }
  sVar2 = _strlen((char *)param_1);
  iVar3 = memblock_alloc((iptr)(this->pad_234 + 0x20),sVar2 + 1);
  piVar1[2] = iVar3;
  sVar2 = _strlen((char *)param_1);
  piVar1[3] = sVar2 + 1;
LAB_0059e2e4:
  crt_strcpy(piVar1[2],param_1);
  piVar1[4] = param_2;
  piVar1[5] = param_3;
  piVar1[6] = param_5;
  this->field_20++;
  return piVar1;
}
#undef local_c
#undef local_8

/* 0059e356 auto */
i32 __thiscall dialog_option_icon_width(DialogCore *this)

{
  return 0x20;
}

/* 0059e376 auto */
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
int __thiscall dialog_option_row_height(DialogCore *this)

{
  int iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = dialog_option_icon_width(this);
  iVar1 = font_line_spacing((GameFont *)this->body_font);
  if (iVar1 * 5 >> 2 <= local_8) {
    iVar1 = font_line_spacing((GameFont *)this->body_font);
    local_8 = iVar1 * 5 >> 2;
  }
  iVar1 = font_line_spacing((GameFont *)this->body_font);
  if (iVar1 < local_8) {
    local_c = local_8;
  }
  else {
    local_c = font_line_spacing((GameFont *)this->body_font);
  }
  return local_c;
}
#undef local_c
#undef local_8

/* 0059e3fa auto */
u32 __thiscall dialog_list_row_height(DialogTextView *this)

{
  int iVar1;
  u32 uVar2;
  
  if ((&this[2].field_50)[this->cur_pane] == 0) {
    iVar1 = font_cached_height((GameFont *)this->list_font);
    uVar2 = iVar1 + 1;
  }
  else {
    uVar2 = (&this[2].field_50)[this->cur_pane];
  }
  return uVar2;
}

/* 0059e448 auto */
int __thiscall dialog_edit_row_height(DialogCore *this)

{
  int iVar1;
  
  iVar1 = font_line_spacing((GameFont *)this->body_font);
  return iVar1 + 10;
}

/* 0059e472 auto */
void __thiscall dialog_set_font(DialogTextView *this,iptr param_1)

{
  u32 uVar1;
  
  this->body_font = param_1;
  uVar1 = dialog_option_row_height((DialogCore *)this);
  this->option_row_height = uVar1;
  return;
}

/* 0059e4a4 auto */
/* Library Function - Single Match
    public: void __thiscall CArchive::SetObjectSchema(unsigned int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall dialog_set_title_font(DialogCore *this,iptr param_1)

{
  this->title_font = param_1;
  return;
}

/* 0059e4c5 auto */
void __thiscall dialog_set_list_font(DialogCore *this,iptr param_1)

{
  this->list_font = param_1;
  return;
}

/* 0059e4e6 auto */
void __thiscall dialog_set_columns(DialogButtonsView *this,u32 param_1)

{
  this->columns = param_1;
  return;
}

/* 0059e507 auto */
void __thiscall dialog_set_list_rows(DialogTextView *this,u32 param_1)

{
  int iVar1;
  
  this->style_flags = this->style_flags | 0x1000;
  (&this->list_rows)[this->cur_pane] = param_1;
  if ((this->style_flags & 0x40000) == 0) {
    iVar1 = dialog_list_row_height(this);
    (&this->list_height)[this->cur_pane] = iVar1 * param_1 + 2;
  }
  else {
    iVar1 = font_cached_height((GameFont *)&default_draw_font_obj);
    (&this->list_height)[this->cur_pane] = iVar1 * param_1 + 2;
  }
  return;
}

/* 0059e585 auto */
void __thiscall dialog_set_current_pane(DialogSetCurrentPaneView *this,u32 param_1)

{
  if ((param_1 == 0) || (param_1 == 1)) {
    this->cur_pane = param_1;
  }
  else {
    this->cur_pane = 0;
  }
  return;
}

/* 0059e5c9 auto */
void __thiscall dialog_set_listbox(DialogTextView *this,int param_1,u32 param_2,u32 param_3)

{
  this->style_flags = this->style_flags | 0x1000;
  (&this->list_width)[this->cur_pane] = param_2;
  (&this[2].field_30)[this->cur_pane] = param_3;
  if (param_1 != 0) {
    dialog_set_list_rows(this,param_1);
  }
  return;
}

/* 0059e648 auto */
int __thiscall dialog_line_height(DialogTextView *this)

{
  int iVar1;
  
  iVar1 = font_line_spacing((GameFont *)this->body_font);
  return iVar1 + 4 + this->pad_y * 2;
}

/* 0059e676 auto */
int __thiscall dialog_button_width_for(DialogButtonWidthForView *this,iptr param_1)

{
  u32 uVar1;
  int iVar2;
  
  uVar1 = this->field_c4;
  iVar2 = font_text_width((GameFont *)&dialog_plain_font_obj,param_1);
  return iVar2 + 4 + uVar1 * 4;
}

/* 0059e6a9 auto */
void __thiscall dialog_set_title(DialogWindowView *this,iptr param_1)

{
  size_t sVar1;
  uptr uVar2;
  
  sVar1 = _strlen((char *)param_1);
  uVar2 = memblock_alloc((iptr)&this[1].field_2c,sVar1 + 1);
  this->title_text = uVar2;
  crt_strcpy(this->title_text,param_1);
  return;
}

/* 0059e6ff auto */
void __thiscall dialog_set_width(DialogWindowView *this,u32 param_1)

{
  if ((this->scale_num != this->scale_den) && ((this->style_flags & 0x80000) == 0)) {
    param_1 = (int)(this->scale_num * param_1) / (int)this->scale_den;
  }
  this->content_width = param_1;
  return;
}

/* 0059e762 auto */
/* Library Function - Single Match
    public: void __thiscall ios::delbuf(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall dialog_set_height(DialogCore *this,u32 param_1)

{
  this->min_height = param_1;
  return;
}

/* 0059e783 auto */
void __thiscall dialog_set_position(DialogCore *this,u32 param_1,u32 param_2)

{
  this->req_x = param_1;
  this->req_y = param_2;
  return;
}

/* 0059e7ad auto */
#define local_c (*(uptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(uptr *)(frame_ + FRAME_OFF(8)))
uptr __thiscall dialog_find_option(DialogOptionList *this,int param_1)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  local_c = this->option_list;
  while ((local_c != 0 && (local_8 == 0))) {
    if (*(int *)(local_c + 4) == param_1) {
      local_8 = local_c;
    }
    local_c = *(uptr *)(local_c + 0x10);
  }
  return local_8;
}
#undef local_c
#undef local_8

/* 0059e877 auto */
#define local_c (*(int * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int * *)(frame_ + FRAME_OFF(8)))
int * __thiscall dialog_find_sprite(DialogOptionList *this,int param_1)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = (int *)0x0;
  local_c = (int *)this->sprite_list;
  while ((local_c != (int *)0x0 && (local_8 == (int *)0x0))) {
    if (*local_c == param_1) {
      local_8 = local_c;
    }
    local_c = (int *)local_c[4];
  }
  return local_8;
}
#undef local_c
#undef local_8

/* 0059e8db auto */
void __thiscall dialog_set_option_disabled(DialogOptionList *this,iptr param_1,int param_2)

{
  uint *puVar1;
  
  puVar1 = (uint *)dialog_find_option(this,param_1);
  if (puVar1 != (uint *)0x0) {
    if (param_2 == 0) {
      *puVar1 = *puVar1 & 0xfffffffe;
    }
    else {
      *puVar1 = *puVar1 | 1;
    }
  }
  return;
}

/* 0059e9f3 auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
i32 __thiscall dialog_option_is_checked(DialogOptionList *this,i32 param_1)

{
  byte *pbVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  pbVar1 = (byte *)dialog_find_option(this,param_1);
  if (pbVar1 != (byte *)0x0) {
    if ((*pbVar1 & 4) == 0) {
      local_8 = 0;
    }
    else {
      local_8 = 1;
    }
  }
  return local_8;
}
#undef local_8

/* 0059ea4d auto */
void __thiscall dialog_set_option_checked(DialogOptionList *this,i32 param_1,int param_2)

{
  uint *puVar1;
  
  puVar1 = (uint *)dialog_find_option(this,param_1);
  if (puVar1 != (uint *)0x0) {
    if (param_2 == 0) {
      *puVar1 = *puVar1 & 0xfffffffb;
    }
    else {
      *puVar1 = *puVar1 | 4;
    }
  }
  return;
}

/* 0059ea99 auto */
void __thiscall dialog_set_default_choice(DialogOptionList *this,iptr param_1)

{
  uptr uVar1;
  
  if (this->option_count == 0) {
    uVar1 = dialog_find_sprite(this,param_1);
    if (uVar1 != 0) {
      this->selected_sprite = uVar1;
    }
  }
  else {
    uVar1 = dialog_find_option(this,param_1);
    if (uVar1 != 0) {
      this->selected_option = uVar1;
    }
  }
  return;
}

/* 0059eb8c auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall dialog_set_sprite_click_fn(DialogOptionList *this,iptr param_1)

{
  this->on_sprite_click = param_1;
  return;
}

/* 0059ebb0 auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall dialog_set_sprite_dblclick_fn(DialogOptionList *this,iptr param_1)

{
  this->on_sprite_dblclick = param_1;
  return;
}

/* 0059ebd4 auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall dialog_set_sprite_draw_fn(DialogCore *this,iptr param_1)

{
  this[0xe].field_14 = param_1;
  return;
}

/* 0059ebf8 auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall dialog_set_option_draw_fn(DialogOptionList *this,iptr param_1)

{
  this->on_draw_option = param_1;
  return;
}

/* 0059ec1c auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall dialog_set_select_change_fn(DialogSelChangeSetView *this,iptr param_1)

{
  this->on_select_change = param_1;
  return;
}

/* 0059ec64 auto */
/* Library Function - Single Match
    public: void __thiscall CPropertySheet::EnableStackedTabs(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall dialog_set_image_zoom(DialogWindowView *this,u32 param_1)

{
  this->sprite_zoom = param_1;
  return;
}

/* 0059ec88 auto */
#define local_10 (*(uptr *)(frame_ + FRAME_OFF(0)))
#define local_c (*(uptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(u32 *)(frame_ + FRAME_OFF(8)))
iptr * __thiscall
dialog_add_sprite(DialogOptionList *this,iptr param_1,iptr param_2,iptr param_3)

{
  iptr *piVar1;
  size_t sVar2;
  iptr iVar3;
  int iVar4;
  u32 uVar5;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_10 = 0;
  for (local_c = this->sprite_list; local_c != 0; local_c = *(uptr *)(local_c + 0x10)) {
    local_10 = local_c;
  }
  piVar1 = (iptr *)memblock_alloc((iptr)this->pad_254,0x14);
  if (local_10 == 0) {
    this->sprite_list = (uptr)piVar1;
    if (this->selected_sprite == 0) {
      this->selected_sprite = (uptr)piVar1;
    }
  }
  else {
    *(iptr **)(local_10 + 0x10) = piVar1;
  }
  piVar1[4] = 0;
  piVar1[1] = 0;
  piVar1[3] = param_1;
  local_8 = sprite_width((Sprite *)param_1);
  if (param_3 == 0) {
    piVar1[2] = 0;
  }
  else {
    sVar2 = _strlen((char *)param_3);
    iVar3 = memblock_alloc((iptr)this->pad_254,sVar2 + 1);
    piVar1[2] = iVar3;
    crt_strcpy(piVar1[2],param_3);
    iVar4 = font_text_width((GameFont *)this->body_font,piVar1[2]);
    local_8 = local_8 + this->sprite_gap + iVar4;
  }
  *piVar1 = param_2;
  uVar5 = this->max_sprite_width;
  if ((int)this->max_sprite_width <= (int)local_8) {
    uVar5 = local_8;
  }
  this->max_sprite_width = uVar5;
  this->sprite_count++;
  return piVar1;
}
#undef local_10
#undef local_c
#undef local_8

/* 0059edf0 auto */
#define local_10 (*(uptr *)(frame_ + FRAME_OFF(0)))
#define local_c (*(uptr *)(frame_ + FRAME_OFF(4)))
uint * __thiscall
dialog_add_option(DialogOptionList *this,iptr param_1,iptr param_2,uint param_3)

{
  u32 uVar1;
  int iVar2;
  uint *puVar3;
  size_t sVar4;
  uint uVar5;
  int iVar6;
  u32 uVar7;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_10 = 0;
  local_c = this->option_list;
  if (((this->style_flags & 0x800000) == 0) || (local_c == 0)) {
    if (local_c != 0) {
      for (; local_c != 0; local_c = *(uptr *)(local_c + 0x10)) {
        local_10 = local_c;
      }
    }
  }
  else {
    while ((local_c != 0 && (iVar2 = __strcmpi((char *)param_1,*(char **)(local_c + 8)), 0 < iVar2))
          ) {
      local_10 = local_c;
      local_c = *(uptr *)(local_c + 0x10);
    }
  }
  puVar3 = (uint *)memblock_alloc((iptr)this->pad_254,0x18);
  if (local_10 == 0) {
    puVar3[4] = this->option_list;
    puVar3[5] = 0;
    if (this->option_list == 0) {
      this->option_tail = (u32)puVar3;
    }
    else {
      *(uint **)(this->option_list + 0x14) = puVar3;
    }
    this->option_list = (uptr)puVar3;
    this->selected_option = (uptr)puVar3;
  }
  else {
    puVar3[4] = *(uint *)(local_10 + 0x10);
    puVar3[5] = local_10;
    if (puVar3[4] == 0) {
      this->option_tail = (u32)puVar3;
    }
    else {
      *(uint **)(puVar3[4] + 0x14) = puVar3;
    }
    *(uint **)(local_10 + 0x10) = puVar3;
  }
  *puVar3 = 0;
  sVar4 = _strlen((char *)param_1);
  uVar5 = memblock_alloc((iptr)this->pad_254,sVar4 + 1);
  puVar3[2] = uVar5;
  crt_strcpy(puVar3[2],param_1);
  if (*(char *)param_1 == '\0') {
    *puVar3 = *puVar3 | 1;
  }
  puVar3[1] = param_2;
  puVar3[3] = param_3;
  iVar2 = font_text_width((GameFont *)this->body_font,puVar3[2]);
  iVar6 = dialog_option_icon_width((DialogCore *)this);
  uVar1 = iVar2 + iVar6 + this->option_extra_width + 5;
  uVar7 = this->option_width;
  if ((int)this->option_width <= (int)uVar1) {
    uVar7 = uVar1;
  }
  this->option_width = uVar7;
  this->option_count++;
  return puVar3;
}
#undef local_10
#undef local_c

/* 0059f026 auto */
uint * __thiscall
dialog_add_checkbox_option(DialogOptionList *this,iptr param_1,iptr param_2,int param_3)

{
  uint *puVar1;
  
  this->style_flags = this->style_flags | 5;
  puVar1 = (uint *)dialog_add_option(this,param_1,param_2,0);
  if (param_3 != 0) {
    *puVar1 = *puVar1 | 4;
  }
  return puVar1;
}

/* 0059f06d auto */
#define local_14 (*(uptr *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(uptr *)(frame_ + FRAME_OFF(8)))
#define local_8 (*(u32 *)(frame_ + FRAME_OFF(16)))
i32 * __thiscall
dialog_add_edit_field(DialogOptionList *this,iptr param_1,iptr param_2,size_t param_3)

{
  i32 *puVar1;
  size_t sVar2;
  i32 uVar3;
  u32 uVar4;
  int iVar5;
  u32 uVar6;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_14 = 0;
  for (local_10 = this->edit_field_list; local_10 != 0; local_10 = *(uptr *)(local_10 + 0x18)) {
    local_14 = local_10;
  }
  puVar1 = (i32 *)memblock_alloc((iptr)this->pad_254,0x1c);
  if (local_14 == 0) {
    this->edit_field_list = (u32)puVar1;
  }
  else {
    *(i32 **)(local_14 + 0x18) = puVar1;
  }
  puVar1[6] = 0;
  *puVar1 = 0;
  sVar2 = _strlen((char *)param_1);
  uVar3 = memblock_alloc((iptr)this->pad_254,sVar2 + 2);
  puVar1[4] = uVar3;
  crt_strcpy(puVar1[4],param_1);
  uVar4 = font_text_width((GameFont *)this->body_font,puVar1[4]);
  uVar6 = this->edit_label_width;
  if ((int)this->edit_label_width <= (int)uVar4) {
    uVar6 = uVar4;
  }
  this->edit_label_width = uVar6;
  if (0xfe < (int)param_3) {
    param_3 = 0xff;
  }
  puVar1[2] = param_3;
  uVar3 = memblock_alloc((iptr)this->pad_254,0x100);
  puVar1[5] = uVar3;
  iVar5 = font_text_width((GameFont *)ctrl_default_font,ADDR(0x635b18, ((u8 *)&g.d_00635b18)));
  puVar1[1] = iVar5 * param_3;
  local_8 = puVar1[1] + this->edit_label_width;
  if ((this->content_width != 0) && ((int)this->content_width < (int)local_8)) {
    puVar1[1] -= ((local_8 - this->content_width) - 3);
    local_8 = puVar1[1] + this->edit_label_width + 3;
  }
  uVar6 = this->edit_width;
  if ((int)this->edit_width <= (int)local_8) {
    uVar6 = local_8;
  }
  this->edit_width = uVar6;
  if (param_2 == 0) {
    *(i8 *)puVar1[5] = 0;
  }
  else {
    _memset((void *)puVar1[5],0,0x100);
    _strncpy((char *)puVar1[5],(char *)param_2,param_3);
  }
  puVar1[3] = this->edit_count;
  this->edit_count++;
  return puVar1;
}
#undef local_14
#undef local_10
#undef local_8

/* 0059f2a3 auto */
void __thiscall dialog_add_button(DialogButtonsView *this,iptr param_1)

{
  size_t sVar1;
  uptr uVar2;
  
  if ((int)this->extra_button_count < 6) {
    sVar1 = _strlen((char *)param_1);
    uVar2 = memblock_alloc((iptr)&this[9].field_38,sVar1 + 1);
    (&this[0xb].field_0)[this->extra_button_count] = uVar2;
    crt_strcpy((&this[0xb].field_0)[this->extra_button_count],param_1);
    this->extra_button_count++;
  }
  return;
}

/* 0059f31a auto */
#define local_10 (*(u32 *)(frame_ + FRAME_OFF(0)))
#define local_c (*(u32 *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(u32 *)(frame_ + FRAME_OFF(8)))
void __thiscall dialog_set_text_color(DialogTextView *this,int param_1,int param_2,int param_3)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 == 0) {
    if (param_2 == 0) {
      if (param_3 == 0) {
        local_10 = this->text_color;
      }
      else {
        local_10 = this->shadow_color;
      }
      gfx_set_text_color_index(local_10);
    }
    else {
      if (param_3 == 0) {
        local_c = this->frame_color;
      }
      else {
        local_c = this->shadow_color;
      }
      gfx_set_text_color_index(local_c);
    }
  }
  else {
    if (param_3 == 0) {
      local_8 = this->highlight_color;
    }
    else {
      local_8 = this->shadow_color;
    }
    gfx_set_text_color_index(local_8);
  }
  return;
}
#undef local_10
#undef local_c
#undef local_8

/* 0059f3d7 auto */
int __thiscall
dialog_draw_text_shadowed
          (DialogTextView *this,iptr param_1,char *param_2,int param_3,int param_4,uint param_5)

{
  char *pcVar1;
  i32 uVar2;
  int iVar3;
  i32 uVar4;
  
  while (pcVar1 = _strchr(param_2,0x5f), pcVar1 != (char *)0x0) {
    *pcVar1 = ' ';
  }
  if (this->shadow_color != this->text_color) {
    uVar4 = 1;
    uVar2 = dialog_uses_alt_text_color((DialogAltColorView *)this);
    dialog_set_text_color(this,param_5 & 1,uVar2,uVar4);
    surface_draw_text
              ((DibSurface *)this->surf_wnd,param_1,(iptr)param_2,param_3 + 1,param_4 + 1,5);
  }
  uVar4 = 0;
  uVar2 = dialog_uses_alt_text_color((DialogAltColorView *)this);
  dialog_set_text_color(this,param_5 & 1,uVar2,uVar4);
  surface_draw_text
            ((DibSurface *)this->surf_wnd,param_1,(iptr)param_2,param_3,param_4,5);
  iVar3 = font_text_width((GameFont *)param_1,(iptr)param_2);
  return param_3 + iVar3;
}

/* 0059f5ba auto */
void __thiscall
dialog_draw_text_line(DialogTextLineView *this,iptr param_1,int param_2,i32 param_3)

{
  dialog_draw_text_default_font
            ((DialogTextView *)this,param_1,this->text_x + param_2,param_3,0);
  return;
}

/* 0059f5f7 auto */
#define local_8 (*(uptr *)(frame_ + FRAME_OFF(0)))
i32 __thiscall dialog_has_text_lines(DialogOptionList *this)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = this->line_list;
  while( true ) {
    if (local_8 == 0) {
      return 0;
    }
    if (*(int *)(local_8 + 0x10) < 0) break;
    local_8 = *(uptr *)(local_8 + 0x1c);
  }
  return 1;
}
#undef local_8

/* 0059f64a auto */
#define local_188 (*(u32 *)(frame_ + FRAME_OFF(0)))
#define local_180 (*(char * *)(frame_ + FRAME_OFF(8)))
#define local_17c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_174 (*(u32 *)(frame_ + FRAME_OFF(20)))
#define local_16c (*(int *)(frame_ + FRAME_OFF(28)))
#define local_160 (*(char (*)[256])(frame_ + FRAME_OFF(40)))
#define local_60 (*(char *)(frame_ + FRAME_OFF(296)))
#define local_5f (*(i8 (*)[79])(frame_ + FRAME_OFF(297)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(376)))
#define local_c (*(uptr *)(frame_ + FRAME_OFF(380)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(384)))
int __thiscall dialog_draw_wrapped_text(DialogOptionList *this,int param_1)

{
  u32 uVar1;
  int iVar2;
  uptr sVar3;
  char *pcVar3;
  uptr sVar4;
  int iVar4;
  int iVar5;
  bool bVar6;
  i8 frame_[FRAME_OFF(392)] __attribute__((aligned(8)));  /* original stack frame */
  
  bVar6 = this->shadow_color != this->text_color;
  local_c = this->line_list;
  uVar1 = this->content_width;
  local_17c = 0;
  local_174 = this->text_y;
  local_8 = font_line_spacing((GameFont *)this->body_font);
  local_160[0] = '\0';
  local_10 = 0;
  for (; iVar5 = (int)uVar1 >> 1, local_c != 0; local_c = *(uptr *)(local_c + 0x1c)) {
    if (*(int *)(local_c + 0x10) < 1) {
      local_180 = *(char **)(local_c + 8);
      if ((*(byte *)(local_c + 4) & 3) != 0) {
        if (local_160[0] != '\0') {
          if (param_1 != 0) {
            dialog_draw_text_line((DialogTextLineView *)this,(iptr)local_160,0,local_174);
          }
          local_17c += local_8;
          local_174 += local_8;
          local_160[0] = '\0';
          local_10 = 0;
        }
        if (param_1 != 0) {
          if ((*(byte *)(local_c + 4) & 1) == 0) {
            local_16c = 0;
          }
          else if (*(int *)(local_c + 0x18) == 0) {
            iVar2 = font_text_width((GameFont *)this->body_font,(iptr)local_180);
            local_16c = iVar5 - ((int)((uint)bVar6 + iVar2) >> 1);
          }
          else {
            local_16c = *(int *)(local_c + 0x18);
            iVar2 = font_text_width((GameFont *)this->body_font,(iptr)local_180);
            local_16c -= ((int)((uint)bVar6 + iVar2) >> 1);
          }
          if (*(int *)(local_c + 0x14) == -1) {
            local_188 = local_174;
          }
          else {
            local_188 = *(u32 *)(local_c + 0x14);
          }
          dialog_draw_text_line
                    ((DialogTextLineView *)this,(iptr)local_180,local_16c,local_188);
        }
        for (; *local_180 != '\0'; local_180++) {
        }
        if (*(int *)(local_c + 0x14) < 0) {
          local_17c += local_8;
          local_174 += local_8;
        }
      }
      while (sVar3 = _strlen(local_180), sVar3 != 0) {
        for (; *local_180 == ' '; local_180++) {
        }
        pcVar3 = _strchr(local_180,0x20);
        if (pcVar3 != (char *)0x0) {
          *pcVar3 = '\0';
        }
        sVar4 = _strlen(local_180);
        local_60 = '\0';
        if (local_160[0] != '\0') {
          crt_strcat(&local_60,&dialog_wrap_space_str);
        }
        crt_strcat(&local_60,local_180);
        iVar2 = font_text_width((GameFont *)this->body_font,(iptr)&local_60);
        if ((int)uVar1 < (int)((uint)bVar6 + iVar2 + local_10)) {
          if (param_1 != 0) {
            if ((this->style_flags & 0x200000) == 0) {
              local_16c = 0;
            }
            else {
              iVar4 = font_text_width
                                ((GameFont *)this->body_font,(iptr)local_160);
              local_16c = iVar5 - ((int)((uint)bVar6 + iVar4) >> 1);
            }
            dialog_draw_text_line
                      ((DialogTextLineView *)this,(iptr)local_160,local_16c,local_174);
          }
          local_17c += local_8;
          local_174 += local_8;
          while (local_60 == ' ') {
            crt_strcpy(&local_60,local_5f);
          }
          local_160[0] = '\0';
          local_10 = 0;
        }
        crt_strcat(local_160,&local_60);
        local_10 += iVar2;
        if (pcVar3 != (char *)0x0) {
          *pcVar3 = ' ';
        }
        local_180 += sVar4;
      }
    }
    else if (param_1 != 0) {
      dialog_draw_text_default_font
                ((DialogTextView *)this,*(i32 *)(local_c + 8),*(i32 *)(local_c + 0x10),
                 *(i32 *)(local_c + 0x14),*(i32 *)(local_c + 4));
    }
  }
  if (local_160[0] != '\0') {
    if (param_1 != 0) {
      if ((this->style_flags & 0x200000) == 0) {
        local_16c = 0;
      }
      else {
        iVar2 = font_text_width((GameFont *)this->body_font,(iptr)local_160);
        local_16c = iVar5 - ((int)((uint)bVar6 + iVar2) >> 1);
      }
      dialog_draw_text_line((DialogTextLineView *)this,(iptr)local_160,local_16c,local_174)
      ;
    }
    local_17c += local_8;
  }
  return local_17c;
}
#undef local_188
#undef local_180
#undef local_17c
#undef local_174
#undef local_16c
#undef local_160
#undef local_60
#undef local_5f
#undef local_10
#undef local_c
#undef local_8

/* 0059fb78 auto */
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(uptr *)(frame_ + FRAME_OFF(8)))
i32 __thiscall dialog_option_group_index(DialogOptionList *this,uptr param_1)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (this->option_list != 0) {
    local_c = 0;
    for (local_8 = this->option_list; local_8 != 0; local_8 = *(uptr *)(local_8 + 0x10)) {
      if ((*(int *)(param_1 + 0xc) == *(int *)(local_8 + 0xc)) && (param_1 == local_8)) {
        return local_c;
      }
      if (*(int *)(param_1 + 0xc) == *(int *)(local_8 + 0xc)) {
        local_c++;
      }
    }
  }
  return 0;
}
#undef local_c
#undef local_8

/* 0059fc19 auto */
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(uptr *)(frame_ + FRAME_OFF(8)))
i32 __thiscall dialog_option_at(DialogOptionList *this,int param_1)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (this->option_list != 0) {
    local_c = 0;
    for (local_8 = this->option_list; local_8 != 0; local_8 = *(uptr *)(local_8 + 0x10)) {
      if ((this->cur_pane == *(u32 *)(local_8 + 0xc)) && (local_c == param_1)) {
        return local_8;
      }
      if (this->cur_pane == *(u32 *)(local_8 + 0xc)) {
        local_c++;
      }
    }
  }
  return 0;
}
#undef local_c
#undef local_8

/* 0059fcba auto */
int __thiscall dialog_column_of_option(DialogOptionList *this,uptr param_1)

{
  int iVar1;
  
  iVar1 = dialog_option_group_index(this,param_1);
  return iVar1 / (int)(&this->list_rows)[this->cur_pane];
}

/* 0059fd2a auto */
#define dialog_clamp_overflow (*(int *)((u8 *)&g.d_0062f004))
#define main_frame_created (*(int *)((u8 *)&g.d_00634718))
#define local_78 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_70 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_6c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_68 (*(i8 (*)[12])(frame_ + FRAME_OFF(16)))
#define local_5c (*(int *)(frame_ + FRAME_OFF(28)))
#define local_58 (*(u32 *)(frame_ + FRAME_OFF(32)))
#define local_54 (*(i8 (*)[8])(frame_ + FRAME_OFF(36)))
#define local_4c (*(int *)(frame_ + FRAME_OFF(44)))
#define local_48 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_44 (*(i32 *)(frame_ + FRAME_OFF(52)))
#define local_40 (*(int *)(frame_ + FRAME_OFF(56)))
#define local_3c (*(int *)(frame_ + FRAME_OFF(60)))
#define local_38 (*(u32 *)(frame_ + FRAME_OFF(64)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(68)))
#define local_30 (*(u32 *)(frame_ + FRAME_OFF(72)))
#define local_2c (*(u32 *)(frame_ + FRAME_OFF(76)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(80)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(84)))
#define local_20 (*(uptr *)(frame_ + FRAME_OFF(88)))
#define local_1c (*(uptr *)(frame_ + FRAME_OFF(92)))
#define local_18 (*(u32 *)(frame_ + FRAME_OFF(96)))
#define local_14 (*(uptr *)(frame_ + FRAME_OFF(100)))
#define local_10 (*(u32 *)(frame_ + FRAME_OFF(104)))
#define local_c (*(uptr *)(frame_ + FRAME_OFF(108)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(112)))
i32 __thiscall dialog_compute_layout(DialogOptionList *this)

{
  u32 uVar1;
  int iVar2;
  size_t sVar3;
  i32 uVar4;
  u32 uVar6;
  uptr uVar5;
  i8 frame_[FRAME_OFF(120)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_44 = 1;
  local_70 = 0;
  local_10 = 0;
  local_24 = 0;
  if ((this->style_flags & 0x100000) == 0) {
    for (local_14 = this->line_list; local_14 != 0; local_14 = *(uptr *)(local_14 + 0x1c)) {
      if ((*(byte *)(local_14 + 4) & 3) != 0) {
        uVar6 = this->shadow_color;
        uVar1 = this->text_color;
        iVar2 = font_text_width
                          ((GameFont *)this->body_font,*(iptr *)(local_14 + 8));
        local_58 = (uint)(uVar6 != uVar1) + iVar2;
        uVar6 = this->content_width;
        if ((int)this->content_width <= (int)local_58) {
          uVar6 = local_58;
        }
        this->content_width = uVar6;
      }
    }
  }
  if (((this->title_text != 0) && (this->title_font != 0)) &&
     (sVar3 = _strlen((char *)this->title_text), sVar3 != 0)) {
    iVar2 = font_text_width((GameFont *)this->title_font,this->title_text);
    local_58 = iVar2 + 4;
    uVar6 = this->content_width;
    if ((int)this->content_width <= (int)local_58) {
      uVar6 = local_58;
    }
    this->content_width = uVar6;
  }
  for (local_20 = this->sprite_list; local_20 != 0; local_20 = *(uptr *)(local_20 + 0x10)) {
  }
  if ((this->edit_count != 0) && (this->option_count != 0)) {
    this->edit_count = 0;
    this->edit_field_list = 0;
  }
  if ((this->style_flags & 0x10000) == 0) {
    iVar2 = font_cached_height((GameFont *)this->title_font);
    this->title_height = iVar2 + this->bevel_width * 2 + this->pad_y * 2;
  }
  else {
    this->border_width = 0;
    this->bevel_width = 0;
    this->title_height = 0;
  }
  this->chrome_height = this->title_height;
  this->window_x = this->req_x;
  this->window_y = this->req_y;
  local_38 = this->border_width + this->pad_x;
  local_30 = this->title_height + this->pad_y;
  if ((this->style_flags & 0x100000) == 0) {
    this->wnd_width = local_38 * 2;
    this->wnd_height = this->pad_y * 2 + this->title_height;
    this->text_x = local_38;
    this->text_y = local_30;
    this->list_x = local_38;
    this->list_y = local_30;
    this->edit_x = local_38;
    this->edit_y = local_30;
    this->sprite_x = local_38;
    this->sprite_y = local_30;
    uVar6 = this->option_width;
    if ((int)this->option_width <= (int)this->content_width) {
      uVar6 = this->content_width;
    }
    if ((int)uVar6 <= (int)this->edit_width) {
      uVar6 = this->edit_width;
    }
    this->content_width = uVar6;
    this->edit_width = this->content_width;
    this->option_width = this->edit_width;
  }
  this->std_button_count = 0;
  if ((this->style_flags & 0x40) != 0) {
    (&this[1].field_44)[this->std_button_count * 2] = 1;
    this->std_button_count++;
  }
  if (((this->style_flags & 8) == 0) && ((this->style_flags & 0x2000000) == 0)) {
    (&this[1].field_44)[this->std_button_count * 2] = 0;
    this->std_button_count++;
  }
  if ((this->style_flags & 1) != 0) {
    (&this[1].field_44)[this->std_button_count * 2] = 2;
    this->std_button_count++;
  }
  if (this->edit_count + this->option_count + this->sprite_count + this->std_button_count + this->line_count == 0) {
    if (this->surf_wnd != 0) {
      this->text_x += this->origin_x;
      this->text_y += this->origin_y;
    }
  }
  else if ((this->option_count != 0) || ((this->style_flags & 0x1004) == 0)) {
    local_28 = 0;
    if (this->sprite_list != 0) {
      local_18 = gfx_zoom_scale(this->max_sprite_width,this->sprite_zoom);
      if (*(int *)(this->sprite_list + 8) == 0) {
        this->text_x += local_18;
        this->list_x += local_18;
        this->edit_x += local_18;
        this->wnd_width += local_18;
      }
      else {
        uVar6 = this->content_width;
        if ((int)this->content_width <= (int)local_18) {
          uVar6 = local_18;
        }
        this->content_width = uVar6;
      }
      for (local_20 = this->sprite_list; local_20 != 0; local_20 = *(uptr *)(local_20 + 0x10)) {
        uVar6 = this->sprite_zoom;
        uVar4 = sprite_height(*(Sprite **)(local_20 + 0xc));
        iVar2 = gfx_zoom_scale(uVar4,uVar6);
        local_28 += iVar2;
        if (*(int *)(local_20 + 0x10) != 0) {
          local_28 += this->section_gap;
        }
      }
    }
    if ((this->line_list != 0) && (iVar2 = dialog_has_text_lines(this), iVar2 != 0)) {
      local_70 = dialog_draw_wrapped_text(this,0);
      this->list_y = this->list_y + this->section_gap + local_70;
      this->edit_y = this->edit_y + this->section_gap + local_70;
    }
    if (this->option_list != 0) {
      uVar5 = this->columns;
      if ((int)uVar5 < 2) {
        uVar5 = 1;
      }
      local_3c = (int)((this->columns - 1) + this->option_count) / (int)uVar5;
      local_10 = this->option_row_height * local_3c;
      if ((this->style_flags & 0x1000) != 0) {
        this->cur_pane = 0;
        local_10 = this->list_height;
        if ((this->style_flags & 0x40000) == 0) {
          uVar6 = GetSystemMetrics(2);
          this->list_vscroll_width = uVar6;
          uVar6 = GetSystemMetrics(3);
          this->list_hscroll_height = uVar6;
          rect_set_xywh((iptr)&this->pane_left,this->list_x_offset + this->list_x,this->list_y,
                             this->list_width,this->list_height);
          this->pane_inner_left = this->pane_left;
          this->list_client_top = this->pane_top;
          this->list_client_right = this->pane_right;
          this->list_client_bottom = this->pane_bottom;
          if (((int)(this->list_rows * this->columns) < (int)this->option_count) ||
             ((this->style_flags & 0x1000000) != 0)) {
            if (this->columns == 1) {
              rect_set_xywh((iptr)this->pad_178,this->pane_right - this->list_vscroll_width,
                                 this->list_y,this->list_vscroll_width,this->list_height);
              this->list_client_right -= this->list_vscroll_width;
            }
            else {
              this->list_height += this->list_hscroll_height;
              this->pane_bottom += this->list_hscroll_height;
              this->list_client_bottom += this->list_hscroll_height;
              local_10 = this->list_height;
              rect_set_xywh((iptr)(this->pad_178 + 0x20),this->list_x_offset + this->list_x,
                                 this->pane_bottom - this->list_hscroll_height,this->list_width,this->list_hscroll_height);
              this->list_client_bottom -= this->list_hscroll_height;
            }
          }
          rect_deflate((iptr)&this->pane_inner_left,1,1);
          this->list_origin_x = this->pane_inner_left;
          this->list_origin_y = this->list_client_top;
          iVar2 = rect_width((iptr)&this->pane_inner_left);
          this->list_column_width = iVar2 / (int)this->columns;
          uVar6 = dialog_list_row_height((DialogTextView *)this);
          this->list_row_height = uVar6;
          local_c = dialog_option_at(this,0);
          local_6c = dialog_option_group_index(this,local_c);
          iVar2 = dialog_option_group_index(this,this->selected_option);
          while ((int)(this->list_rows * this->columns + local_6c) <= iVar2) {
            if (this->columns == 1) {
              local_6c++;
            }
            else {
              local_6c += this->list_rows;
            }
          }
          uVar6 = dialog_option_at(this,local_6c);
          this->list_top_option = uVar6;
        }
        if ((this->style_flags & 0x400000) != 0) {
          this->cur_pane = 1;
          if ((int)local_10 < (int)this->list_height_1) {
            local_10 = this->list_height_1;
          }
          if ((this->style_flags & 0x40000) == 0) {
            uVar6 = GetSystemMetrics(2);
            this->list2_vscroll_width = uVar6;
            uVar6 = GetSystemMetrics(3);
            this->list2_hscroll_height = uVar6;
            rect_set_xywh((iptr)&this->pane1_left,this->list2_x_offset + this->list_x,
                               this->list_y,this->list_width_1,this->list_height_1);
            this->list2_client_rect = this->pane1_left;
            this->list2_client_top = this->pane1_top;
            this->list2_client_right = this->pane1_right;
            this->list2_client_bottom = this->pane1_bottom;
            if (((int)(this->list_rows_1 * this->columns) < (int)this->option_count) ||
               ((this->style_flags & 0x1000000) != 0)) {
              if (this->columns == 1) {
                rect_set_xywh((iptr)(this->pad_178 + 0x10),this->pane1_right - this->list2_vscroll_width,
                                   this->list_y,this->list2_vscroll_width,this->list_height_1);
                this->list2_client_right -= this->list2_vscroll_width;
              }
              else {
                this->list_height_1 += this->list2_hscroll_height;
                this->pane1_bottom += this->list2_hscroll_height;
                this->list2_client_bottom += this->list2_hscroll_height;
                if ((int)local_10 < (int)this->list_height_1) {
                  local_10 = this->list_height_1;
                }
                rect_set_xywh((iptr)(this->pad_178 + 0x30),this->list2_x_offset + this->list_x,
                                   this->pane1_bottom - this->list2_hscroll_height,this->list_width_1,this->list2_hscroll_height)
                ;
                this->list2_client_bottom -= this->list2_hscroll_height;
              }
            }
            rect_deflate((iptr)&this->list2_client_rect,1,1);
            this->list2_origin_x = this->list2_client_rect;
            this->list2_origin_y = this->list2_client_top;
            iVar2 = rect_width((iptr)&this->list2_client_rect);
            this->list2_column_width = iVar2 / (int)this->columns;
            uVar6 = dialog_list_row_height((DialogTextView *)this);
            this->list2_row_height = uVar6;
            local_c = dialog_option_at(this,0);
            local_6c = dialog_option_group_index(this,local_c);
            iVar2 = dialog_option_group_index(this,this->selected_option);
            while ((int)(this->list_rows_1 * this->columns + local_6c) <= iVar2) {
              if (this->columns == 1) {
                local_6c++;
              }
              else {
                local_6c += this->list_rows_1;
              }
            }
            uVar6 = dialog_option_at(this,local_6c);
            this->list2_top_option = uVar6;
          }
          this->cur_pane = 0;
        }
      }
    }
    if (this->edit_field_list != 0) {
      local_24 = dialog_edit_row_height((DialogCore *)this);
      local_24 = local_24 * this->edit_count;
    }
    local_8 = local_24 + local_10 + local_70;
    if (((local_8 != 0) && (local_70 != 0)) && (local_24 + local_10 != 0)) {
      local_8 += this->section_gap;
    }
    if ((this->style_flags & 0x100000) == 0) {
      if ((local_28 != 0) && (local_8 != 0)) {
        this->text_x += this->sprite_gap;
        this->list_x += this->sprite_gap;
        this->edit_x += this->sprite_gap;
      }
      iVar2 = local_28;
      if (local_28 <= local_8) {
        iVar2 = local_8;
      }
      this->wnd_height += iVar2;
      this->wnd_width += this->content_width;
    }
    if (this->std_button_count + this->extra_button_count == 0) {
      this->wnd_height += this->border_width;
      this->chrome_height += this->border_width;
    }
    else {
      local_78 = this->wnd_width - (this->border_width - this->bevel_width);
      this->button_width = 0;
      for (local_1c = 0; (int)local_1c < 3; local_1c++) {
        iVar2 = dialog_button_width_for
                          ((DialogButtonWidthForView *)this,(iptr)(&dialog_button_labels)[local_1c]);
        if ((int)this->button_width <= iVar2) {
          uVar6 = dialog_button_width_for
                            ((DialogButtonWidthForView *)this,(iptr)(&dialog_button_labels)[local_1c]);
          this->button_width = uVar6;
        }
      }
      for (local_1c = 0; (int)local_1c < (int)this->extra_button_count; local_1c++) {
        iVar2 = dialog_button_width_for((DialogButtonWidthForView *)this,(&this[1].field_2c)[local_1c]);
        if ((int)this->button_width <= iVar2) {
          uVar6 = dialog_button_width_for((DialogButtonWidthForView *)this,(&this[1].field_2c)[local_1c]);
          this->button_width = uVar6;
        }
      }
      iVar2 = (this->wnd_width + (this->border_width - this->bevel_width) * -2) -
              (this->std_button_count + this->extra_button_count - 1) * this->pad_x;
      local_34 = iVar2 % (int)(this->std_button_count + this->extra_button_count);
      local_2c = iVar2 / (int)(this->std_button_count + this->extra_button_count);
      uVar6 = this->button_width;
      if ((int)this->button_width <= (int)local_2c) {
        uVar6 = local_2c;
      }
      this->button_width = uVar6;
      if (this->button_width != local_2c) {
        local_34 = 0;
      }
      if ((this->style_flags & 0x100000) == 0) {
        if ((local_28 != 0) || (local_8 != 0)) {
          this->wnd_height += this->section_gap * 2;
        }
        iVar2 = dialog_line_height((DialogTextView *)this);
        this->wnd_height += iVar2;
        if (this->border_width != 0) {
          if ((local_28 != 0) || (local_8 != 0)) {
            this->chrome_height += this->section_gap * 2;
          }
          iVar2 = dialog_line_height((DialogTextView *)this);
          this->chrome_height += iVar2;
        }
      }
      local_40 = this->std_button_count + this->extra_button_count - 1;
      uVar6 = this->std_button_count;
      while (local_1c = uVar6 - 1, -1 < (int)local_1c) {
        uVar1 = local_78 - this->button_width;
        (&this[1].field_40)[uVar6 * 2] = uVar1;
        local_78 = uVar1 - this->pad_x;
        for (local_40 = local_40 + local_34; uVar6 = local_1c,
            (int)(this->std_button_count + this->extra_button_count) <= local_40;
            local_40 = local_40 - (this->std_button_count + this->extra_button_count)) {
          local_78--;
        }
      }
      uVar6 = this->extra_button_count;
      while (local_1c = uVar6 - 1, -1 < (int)local_1c) {
        uVar1 = local_78 - this->button_width;
        (&this[1].field_40)[uVar6 * 2 + this->std_button_count * 2] = uVar1;
        local_78 = uVar1 - this->pad_x;
        for (local_40 = local_40 + local_34; uVar6 = local_1c,
            (int)(this->std_button_count + this->extra_button_count) <= local_40;
            local_40 = local_40 - (this->std_button_count + this->extra_button_count)) {
          local_78--;
        }
      }
    }
    uVar6 = this->min_height;
    if ((int)this->min_height <= (int)this->wnd_height) {
      uVar6 = this->wnd_height;
    }
    this->wnd_height = uVar6;
    uVar6 = this->wnd_height;
    iVar2 = dialog_line_height((DialogTextView *)this);
    this->button_y = uVar6 - (this->bevel_width + iVar2 + this->pad_y);
    if ((this->style_flags & 0x100000) == 0) {
      gfx_get_screen_rect((iptr)local_54);
      wnd_get_screen_rect((WndBase *)&main_frame_wnd,(iptr)local_68);
      if (this->window_x == 0xfffffc19) {
        iVar2 = rect_width((iptr)local_54);
        this->window_x = (iVar2 >> 1) - ((int)this->wnd_width >> 1);
      }
      else if ((((int)this->window_x < 0) &&
               (this->window_x = this->window_x + ((local_4c - 1) - this->wnd_width),
               main_frame_created != 0)) && ((this->style_flags & 0x10000) != 0)) {
        iVar2 = wnd_frame_width((WndBase *)&main_frame_wnd);
        this->window_x -= iVar2;
      }
      if (this->window_y == 0xfffffc19) {
        iVar2 = rect_height((iptr)local_54);
        this->window_y = (iVar2 >> 1) - ((int)this->wnd_height >> 1);
      }
      else if ((int)this->window_y < 0) {
        if (-(local_48 - local_5c) < (int)this->window_y) {
          this->window_y -= (local_48 - local_5c);
        }
        this->window_y += ((local_48 - 1) - this->wnd_height);
        if ((main_frame_created != 0) && ((this->style_flags & 0x10000) != 0)) {
          iVar2 = wnd_nonclient_height((WndBase *)&main_frame_wnd);
          this->window_y -= iVar2;
        }
      }
      if ((dialog_clamp_overflow == 0) &&
         (iVar2 = rect_width((iptr)local_54), (int)this->wnd_width <= iVar2)) {
        rect_height((iptr)local_54);
      }
      this->list_x += this->origin_x;
      this->list_y += this->origin_y;
      this->text_x += this->origin_x;
      this->text_y += this->origin_y;
      this->edit_x += this->origin_x;
      this->edit_y += this->origin_y;
    }
    this->button_y += this->origin_y;
    for (local_1c = 0; (int)local_1c < (int)(this->std_button_count + this->extra_button_count);
        local_1c = local_1c + 1) {
      (&this[1].field_48)[local_1c * 2] = (&this[1].field_48)[local_1c * 2] + this->origin_x;
    }
    local_44 = 0;
  }
  return local_44;
}
#undef dialog_clamp_overflow
#undef main_frame_created
#undef local_78
#undef local_70
#undef local_6c
#undef local_68
#undef local_5c
#undef local_58
#undef local_54
#undef local_4c
#undef local_48
#undef local_44
#undef local_40
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

/* 005a0fea auto */
#define local_c (*(u32 *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(u32 *)(frame_ + FRAME_OFF(8)))
void __thiscall
dialog_draw_option_cell
          (DialogOptionDrawView *this,iptr param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  uptr sVar3;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  while (*(char *)param_1 != '\0') {
    iVar1 = *(int *)(this[2].pad_9c + this->field_48 * 4 - 4);
    iVar2 = font_text_width((GameFont *)this->field_10,param_1);
    if (iVar2 <= iVar1 - 6) break;
    sVar3 = _strlen((char *)param_1);
    *(i8 *)((sVar3 - 1) + param_1) = 0;
  }
  if (param_4 == 0) {
    local_8 = this->field_94;
    local_c = this->field_98;
  }
  else {
    local_8 = this->field_a0;
    local_c = this->field_a4;
  }
  if (local_c != local_8) {
    gfx_set_text_color_index(local_c);
    surface_draw_text
              ((DibSurface *)this->field_0,this->field_10,param_1,param_2 + 2,param_3 + 1,5);
    gfx_set_text_color_index(local_8);
    surface_draw_text
              ((DibSurface *)this->field_0,this->field_10,param_1,param_2 + 1,param_3,5);
  }
  if (param_5 == 0) {
    gfx_set_text_color_index(local_8);
  }
  else {
    gfx_set_text_color_index(this->field_6c);
  }
  surface_draw_text
            ((DibSurface *)this->field_0,this->field_10,param_1,param_2,param_3,5);
  return;
}
#undef local_c
#undef local_8

/* 005a1148 auto */
#define local_8 (*(char * *)(frame_ + FRAME_OFF(0)))
void __thiscall
dialog_draw_option_text
          (DialogOptionDrawView *this,char *param_1,int param_2,i32 param_3,i32 param_4,
          i32 param_5)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = (char *)0x0;
  pcVar2 = _strchr(param_1,0x7c);
  if (pcVar2 != (char *)0x0) {
    local_8 = pcVar2 + 1;
    *pcVar2 = '\0';
  }
  dialog_draw_option_cell(this,(iptr)param_1,*(int *)(this[3].pad_14 + this->field_48 * 4 - 4) + param_2
                     ,param_3,param_4,param_5);
  if (local_8 != (char *)0x0) {
    iVar1 = *(int *)(this[2].pad_9c + this->field_48 * 4 - 4);
    iVar3 = font_text_width((GameFont *)this->field_10,(iptr)local_8);
    dialog_draw_option_cell(this,(iptr)local_8,(iVar1 + param_2 - 4) - iVar3,param_3,param_4,param_5);
    *pcVar2 = '|';
  }
  return;
}
#undef local_8

/* 005a120b auto */
#define local_3c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_38 (*(i32 *)(frame_ + FRAME_OFF(8)))
#define local_34 (*(i32 *)(frame_ + FRAME_OFF(12)))
#define local_30 (*(i32 *)(frame_ + FRAME_OFF(16)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(28)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_1c (*(u32 *)(frame_ + FRAME_OFF(36)))
#define local_18 (*(uint *)(frame_ + FRAME_OFF(40)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(44)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(48)))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(52)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(56)))
uint __thiscall dialog_draw_option(DialogOptionList *this,iptr param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 == 0) {
    local_18 = 0;
  }
  else if (this->option_count == 0) {
    local_18 = 0;
  }
  else {
    iVar1 = dialog_option_group_index(this,*(uptr *)(this->pad_1f8 + *(int *)(param_1 + 0xc) * 4 + 0x18));
    iVar2 = dialog_option_group_index(this,param_1);
    iVar1 = iVar2 - iVar1;
    if ((iVar1 < 0) ||
       (iVar3 = (&this->list_rows)[*(int *)(param_1 + 0xc)] * this->columns,
       iVar3 - iVar1 == 0 || iVar3 < iVar1)) {
      local_18 = 0;
    }
    else {
      local_24 = iVar1 / (int)(&this->list_rows)[*(int *)(param_1 + 0xc)];
      local_2c = iVar1 % (int)(&this->list_rows)[*(int *)(param_1 + 0xc)];
      local_20 = *(int *)(this->pad_1f8 + *(int *)(param_1 + 0xc) * 4 - 0x10) * local_24 +
                 *(int *)(this->pad_1f8 + *(int *)(param_1 + 0xc) * 4 - 0x28);
      local_28 = *(int *)(this->pad_1f8 + *(int *)(param_1 + 0xc) * 4 - 8) * local_2c +
                 *(int *)(this->pad_1f8 + *(int *)(param_1 + 0xc) * 4 - 0x20);
      rect_set_xywh((iptr)&local_14,local_20,local_28,
                         *(iptr *)(this->pad_1f8 + *(int *)(param_1 + 0xc) * 4 - 0x10),
                         *(iptr *)(this->pad_1f8 + *(int *)(param_1 + 0xc) * 4 - 8));
      local_18 = (uint)(this->selected_option == param_1);
      if (local_18 == 0) {
        local_1c = this->list_fill_color;
      }
      else {
        local_1c = this->list_sel_fill_color;
      }
      local_3c = local_14;
      local_38 = local_10;
      local_34 = local_c;
      local_30 = local_8;
      if (this != (DialogOptionList *)0xfffffdf8) {
        local_3c = local_14 + *(int *)(this->pad_1f8 + *(int *)(param_1 + 0xc) * 4 + 0x10);
      }
      if ((this->on_draw_option == 0) ||
         (iVar2 = (*(code *)this->on_draw_option)
                            (this,this->surf_wnd,*(i32 *)(param_1 + 4),iVar2,local_20,local_28
                             ,*(i32 *)(this->pad_1f8 + *(int *)(param_1 + 0xc) * 4 - 8)),
         iVar2 == 0)) {
        if (local_18 != 0) {
          gfx_draw_bevel_rect(this->surf_wnd,(iptr)&local_3c,this->bevel_light_color,this->bevel_dark_color);
          rect_deflate((iptr)&local_3c,1,1);
        }
        gfx_fill_rect(this->surf_wnd,(iptr)&local_3c,local_1c);
        dialog_draw_option_text
                  ((DialogOptionDrawView *)this,*(i32 *)(param_1 + 8),local_20 + 2,local_28,local_18,
                   *(uint *)param_1 & 1);
      }
      if (param_2 != 0) {
        wnd_blit_surface_rect((DibSurface *)this->surf_wnd,(iptr)&local_14);
      }
    }
  }
  return local_18;
}
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

/* 005a14d2 auto */
#define local_2c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_24 (*(u32 *)(frame_ + FRAME_OFF(12)))
#define local_1c (*(iptr *)(frame_ + FRAME_OFF(20)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(28)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(36)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(40)))
void __thiscall dialog_draw_option_list(DialogOptionList *this)

{
  u8 *puVar1;
  u32 uVar2;
  u32 uVar3;
  int iVar4;
  iptr iVar5;
  uint uVar6;
  i32 uVar7;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  uVar2 = this->cur_pane;
  for (local_24 = 0; (int)local_24 < 2; local_24++) {
    if ((local_24 != 1) || ((this->style_flags & 0x400000) != 0)) {
      this->cur_pane = local_24;
      puVar1 = this->pad_178 + this->cur_pane * 4 + 0x40;
      puVar1[0] = '\0';
      puVar1[1] = '\0';
      puVar1[2] = '\0';
      puVar1[3] = '\0';
      uVar3 = this->cur_pane;
      local_14 = *(i32 *)(this->pad_178 + uVar3 * 0x10 - 0x20);
      local_10 = *(int *)(this->pad_178 + uVar3 * 0x10 - 0x1c);
      local_c = *(i32 *)(this->pad_178 + uVar3 * 0x10 - 0x18);
      local_8 = *(i32 *)(this->pad_178 + uVar3 * 0x10 - 0x14);
      if ((1 < (int)this->columns) || ((this->option_count == 0 || (this->on_draw_option != 0)))) {
        gfx_fill_rect(this->surf_wnd,(iptr)(this->pad_178 + this->cur_pane * 0x10 - 0x20),
                           this->list_fill_color);
      }
      gfx_draw_rect_frame(this->surf_wnd,(iptr)(this->pad_178 + this->cur_pane * 0x10 - 0x40),
                         this->bevel_dark_color);
      surface_set_clip((DibSurface *)this->surf_wnd,(iptr)&local_14);
      if (this->option_count != 0) {
        local_1c = *(iptr *)(active_dialog + 0x228);
        iVar4 = dialog_option_group_index(this,*(uptr *)(this->pad_1f8 + this->cur_pane * 4 + 0x18));
        local_2c = 0;
        for (local_18 = 0; (local_1c != 0 && (local_18 < (int)this->option_count));
            local_18 = local_18 + 1) {
          if (this->cur_pane == *(u32 *)(local_1c + 0xc)) {
            if ((iVar4 <= local_2c) &&
               (local_2c < (int)((&this->list_rows)[this->cur_pane] * this->columns + iVar4))) {
              uVar7 = 0;
              iVar5 = dialog_option_at(this,local_2c);
              uVar6 = dialog_draw_option(this,iVar5,uVar7);
              *(uint *)(this->pad_178 + this->cur_pane * 4 + 0x40) =
                   *(uint *)(this->pad_178 + this->cur_pane * 4 + 0x40) | uVar6;
              local_10 += *(int *)(this->pad_1f8 + this->cur_pane * 4 - 8);
            }
            local_2c++;
          }
          local_1c = *(iptr *)(local_1c + 0x10);
        }
        if (((this->columns == 1) && (this->on_draw_option == 0)) &&
           (iVar4 = rect_height((iptr)&local_14), 0 < iVar4)) {
          gfx_fill_rect(this->surf_wnd,(iptr)&local_14,this->list_fill_color);
        }
      }
      surface_reset_clip((DibSurface *)this->surf_wnd);
      wnd_blit_surface_rect
                ((DibSurface *)this->surf_wnd,
                 (iptr)(this->pad_178 + this->cur_pane * 0x10 - 0x40));
    }
  }
  this->cur_pane = uVar2;
  return;
}
#undef local_2c
#undef local_24
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 005a1766 auto */
int __thiscall dialog_column_of_index(DialogTextView *this,int param_1)

{
  if (this->columns != 1) {
    param_1 = param_1 / (int)(&this->list_rows)[this->cur_pane];
  }
  return param_1;
}

/* 005a17a4 auto */
int __thiscall dialog_column_start_index(DialogTextView *this,int param_1)

{
  if (this->columns != 1) {
    param_1 -= param_1 % (int)(&this->list_rows)[this->cur_pane];
  }
  return param_1;
}

/* 005a17e9 auto */
#define local_10 (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall dialog_select_option(DialogOptionList *this,uptr param_1,int param_2)

{
  uptr uVar1;
  bool bVar2;
  int iVar3;
  i32 uVar4;
  iptr iVar5;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  bVar2 = false;
  if ((param_1 != 0) && (this->selected_option != param_1)) {
    local_10 = dialog_option_group_index(this,*(uptr *)(this->pad_1f8 + this->cur_pane * 4 + 0x18));
    iVar3 = dialog_option_group_index(this,param_1);
    if (iVar3 < local_10) {
      bVar2 = true;
      local_10 = iVar3;
    }
    while ((int)((&this->list_rows)[this->cur_pane] * this->columns + local_10) <= iVar3) {
      if (this->columns == 1) {
        local_10++;
      }
      else {
        local_10 += (&this->list_rows)[this->cur_pane];
      }
      bVar2 = true;
    }
    uVar4 = dialog_column_start_index((DialogTextView *)this,this->option_count - 1);
    uVar4 = int_clamp_b(local_10,0,uVar4);
    uVar4 = dialog_option_at(this,uVar4);
    *(i32 *)(this->pad_1f8 + this->cur_pane * 4 + 0x18) = uVar4;
    uVar1 = this->selected_option;
    this->selected_option = param_1;
    if ((bVar2) || (param_2 == 0)) {
      if ((&this[1].field_1c)[this->cur_pane] != 0) {
        iVar5 = dialog_option_group_index(this,*(uptr *)(this->pad_1f8 + this->cur_pane * 4 + 0x18));
        scrollbar_set_pos
                  ((ClickControl *)(&this[1].field_1c)[this->cur_pane],iVar5);
      }
      if ((&this[1].field_24)[this->cur_pane] != 0) {
        iVar5 = dialog_column_of_option(this,*(i32 *)(this->pad_1f8 + this->cur_pane * 4 + 0x18));
        scrollbar_set_pos
                  ((ClickControl *)(&this[1].field_24)[this->cur_pane],iVar5);
      }
    }
    if (param_2 != 0) {
      if (bVar2) {
        dialog_draw_option_list(this);
        if (this->on_select_change != 0) {
          (*(code *)this->on_select_change)(this,*(i32 *)(param_1 + 4));
        }
      }
      else {
        dialog_draw_option(this,uVar1,1);
        dialog_draw_option(this,param_1,1);
        if (this->on_select_change != 0) {
          (*(code *)this->on_select_change)(this,*(i32 *)(param_1 + 4));
        }
      }
    }
  }
  return;
}
#undef local_10

/* 005a1a7d auto */
i32 __thiscall dialog_option_at_point(DialogOptionList *this,int param_1,int param_2)

{
  i32 uVar1;
  int iVar2;
  
  dialog_pick_pane_at((DialogWindowView *)this,param_1,param_2);
  if ((&this[1].field_24)[this->cur_pane] != 0) {
    if (param_1 < *(int *)(this->pad_178 + this->cur_pane * 0x10 - 0x20)) {
      return 0xfffffffd;
    }
    if (*(int *)(this->pad_178 + this->cur_pane * 0x10 - 0x18) <= param_1) {
      return 0xfffffffc;
    }
  }
  if (param_2 < *(int *)(this->pad_178 + this->cur_pane * 0x10 - 0x1c)) {
    uVar1 = 0xffffffff;
  }
  else if (param_2 < *(int *)(this->pad_178 + this->cur_pane * 0x10 - 0x14)) {
    if (param_1 < *(int *)(this->pad_178 + this->cur_pane * 0x10 - 0x20)) {
      uVar1 = 0xfffffffd;
    }
    else if (param_1 < *(int *)(this->pad_178 + this->cur_pane * 0x10 - 0x18)) {
      iVar2 = dialog_option_group_index(this,*(uptr *)(this->pad_1f8 + this->cur_pane * 4 + 0x18));
      uVar1 = int_clamp_b((&this->list_rows)[this->cur_pane] *
                           ((param_1 - *(int *)(this->pad_178 + this->cur_pane * 0x10 - 0x20)) /
                           *(int *)(this->pad_1f8 + this->cur_pane * 4 - 0x10)) +
                           (param_2 - *(int *)(this->pad_178 + this->cur_pane * 0x10 - 0x1c)) /
                           *(int *)(this->pad_1f8 + this->cur_pane * 4 - 8) + iVar2,0,
                           this->option_count - 1);
    }
    else {
      uVar1 = 0xfffffffc;
    }
  }
  else {
    uVar1 = 0xfffffffe;
  }
  return uVar1;
}

/* 005a1c52 auto */
#define local_c (*(uptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
int __thiscall dialog_count_group_options(DialogOptionList *this,int param_1)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  for (local_c = this->option_list; local_c != 0; local_c = *(uptr *)(local_c + 0x10)) {
    if (*(int *)(local_c + 0xc) == param_1) {
      local_8++;
    }
  }
  return local_8;
}
#undef local_c
#undef local_8

/* 005a1caf auto */
void __thiscall dialog_pick_pane_at(DialogWindowView *this,int param_1,int param_2)

{
  u32 uVar1;
  
  uVar1 = this->cur_pane;
  if ((this->style_flags & 0x400000) == 0) {
    this->cur_pane = 0;
  }
  else {
    this->cur_pane = 0;
    if (((((param_2 < (int)this->pane_top) || ((int)this->pane_bottom < param_2)) ||
         (param_1 < (int)this->pane_left)) || ((int)this->pane_right < param_1)) &&
       (((this->cur_pane = 1, param_2 < (int)this->pane1_top || ((int)this->pane1_bottom < param_2)) ||
        ((param_1 < (int)this->pane1_left || ((int)this->pane1_right < param_1)))))) {
      this->cur_pane = uVar1;
    }
  }
  return;
}

/* 005a1da3 auto */
void __cdecl dialog_list_on_vscroll(i32 param_1)

{
  int iVar1;
  
  if (active_dialog != 0) {
    *(i32 *)(active_dialog + 0x48) = 0;
    iVar1 = dialog_option_at((DialogOptionList *)active_dialog,param_1);
    if (*(int *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) != iVar1) {
      *(int *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) = iVar1;
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
#define local_2c (*(uptr *)(frame_ + FRAME_OFF(4)))
#define local_24 (*(i32 *)(frame_ + FRAME_OFF(12)))
#define local_20 (*(i8 * *)(frame_ + FRAME_OFF(16)))
#define local_1c (*(i8 * *)(frame_ + FRAME_OFF(20)))
#define local_18 (*(i8 * *)(frame_ + FRAME_OFF(24)))
#define local_14 (*(i8 (*)[4])(frame_ + FRAME_OFF(28)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(32)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(36)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(40)))
i32 __thiscall dialog_create_window(DialogWindowView *this)

{
  i32 uVar1;
  SurfaceWindow *this_00;
  int iVar2;
  u32 uVar3;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  if (this->surf_wnd == 0) {
    this_00 = operator_new(0x114);
    local_8 = 0;
    if (this_00 == (SurfaceWindow *)0x0) {
      local_2c = 0;
    }
    else {
      local_2c = surfwnd_ctor(this_00);
    }
    local_8 = 0xffffffff;
    this->surf_wnd = local_2c;
    local_14[0] = 0;
    local_18 = (i8 *)this->title_text;
    if (local_18 == (i8 *)0x0) {
      local_18 = local_14;
    }
    if ((this->style_flags & 0x10000) == 0) {
      local_24 = 0xc02;
    }
    else {
      local_24 = 0x842;
    }
    if (dlg_parent_window == (i8 *)0x0) {
      if (main_frame_created == 0) {
        local_1c = (i8 *)0x0;
      }
      else {
        local_1c = &main_frame_wnd;
      }
    }
    else {
      local_1c = dlg_parent_window;
    }
    if (dlg_palette == (i8 *)0x0) {
      local_20 = &game_palette;
    }
    else {
      local_20 = dlg_palette;
    }
    if (local_1c == (i8 *)0x0) {
      surface_wnd_create
                ((DibSurface *)this->surf_wnd,(iptr)local_18,local_24,this->window_x,
                 this->window_y,this->wnd_width,this->wnd_height,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
    }
    else {
      wnd_create_with_surface
                ((DibSurface *)this->surf_wnd,(iptr)local_18,local_24,this->window_x,
                 this->window_y,this->wnd_width,this->wnd_height,(iptr)local_20,(iptr)local_1c);
    }
    if ((this->style_flags & 0x10000) == 0) {
      wnd_set_caption_height((WndBase *)(this->surf_wnd + 0x48),this->title_height);
    }
    iVar2 = surface_get_width((DibSurface *)this->surf_wnd);
    if ((int)this->wnd_width <= iVar2) {
      uVar3 = surface_get_width((DibSurface *)this->surf_wnd);
      this->wnd_width = uVar3;
    }
    iVar2 = surface_get_height((DibSurface *)this->surf_wnd);
    if ((int)this->wnd_height <= iVar2) {
      uVar3 = surface_get_height((DibSurface *)this->surf_wnd);
      this->wnd_height = uVar3;
    }
    wnd_set_redraw_callback((SurfaceWindow *)this->surf_wnd,ADDR(0x5a20f4, dialog_on_redraw));
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
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}
#undef dlg_default_idle_callback
#undef dlg_palette
#undef dlg_parent_window
#undef dlg_pending_idle_callback
#undef main_frame_created
#undef local_2c
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef puStack_c
#undef local_8

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
#define local_198 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_194 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_190 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_18c (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_188 (*(iptr *)(frame_ + FRAME_OFF(16)))
#define local_184 (*(iptr *)(frame_ + FRAME_OFF(20)))
#define local_180 (*(iptr *)(frame_ + FRAME_OFF(24)))
#define local_17c (*(iptr *)(frame_ + FRAME_OFF(28)))
#define local_178 (*(iptr *)(frame_ + FRAME_OFF(32)))
#define local_174 (*(iptr *)(frame_ + FRAME_OFF(36)))
#define local_170 (*(iptr *)(frame_ + FRAME_OFF(40)))
#define local_16c (*(int * *)(frame_ + FRAME_OFF(44)))
#define local_164 (*(u32 * *)(frame_ + FRAME_OFF(52)))
#define local_15c (*(u32 * *)(frame_ + FRAME_OFF(60)))
#define local_154 (*(uptr *)(frame_ + FRAME_OFF(68)))
#define local_14c (*(u32 * *)(frame_ + FRAME_OFF(76)))
#define local_144 (*(i32 *)(frame_ + FRAME_OFF(84)))
#define local_13c (*(i32 *)(frame_ + FRAME_OFF(92)))
#define local_134 (*(i32 *)(frame_ + FRAME_OFF(100)))
#define local_12c (*(i32 *)(frame_ + FRAME_OFF(108)))
#define local_124 (*(i32 *)(frame_ + FRAME_OFF(116)))
#define local_11c (*(i32 *)(frame_ + FRAME_OFF(124)))
#define local_104 (*(int *)(frame_ + FRAME_OFF(148)))
#define local_fc (*(uptr *)(frame_ + FRAME_OFF(156)))
#define local_f8 (*(u32 *)(frame_ + FRAME_OFF(160)))
#define local_e8 (*(i8 * *)(frame_ + FRAME_OFF(176)))
#define local_e4 (*(i8 (*)[16])(frame_ + FRAME_OFF(180)))
#define local_d4 (*(iptr *)(frame_ + FRAME_OFF(196)))
#define local_d0 (*(iptr *)(frame_ + FRAME_OFF(200)))
#define local_cc (*(uint *)(frame_ + FRAME_OFF(204)))
#define local_c8 (*(uint * *)(frame_ + FRAME_OFF(208)))
#define local_c4 (*(uptr *)(frame_ + FRAME_OFF(212)))
#define local_c0 (*(int *)(frame_ + FRAME_OFF(216)))
#define local_bc (*(i8 *)(frame_ + FRAME_OFF(220)))
#define local_b8 (*(iptr *)(frame_ + FRAME_OFF(224)))
#define local_b4 (*(uint (*)[41])(frame_ + FRAME_OFF(228)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(392)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(396)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(400)))
void __thiscall dialog_create_controls(Dialog *this)

{
  uint uVar1;
  Control *pCVar2;
  InputControl *this_00;
  i32 uVar3;
  int iVar4;
  iptr iVar5;
  u32 uVar6;
  i32 uVar7;
  u32 uVar8;
  i8 frame_[FRAME_OFF(408)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  local_d4 = 0;
  if (this != (Dialog *)active_dialog) {
    if ((dialog_stack_depth < 0) || (0xf < dialog_stack_depth)) {
      err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x635b40, ((u8 *)&g.d_00635b40)),ADDR(0x635b20, ((u8 *)&g.d_00635b20)),0xc75);
    }
    dialog_stack_depth++;
    dialog_stack_top = this;
    active_dialog = (iptr)this;
    (&dialog_stack)[dialog_stack_depth] = this;
  }
  if ((this->style_flags & 0x200) == 0) {
    local_bc = 0;
    ctrl_set_pending_font(*(iptr *)(active_dialog + 8));
    ui_set_button_font(ADDR(0x6cec90, ((u8 *)&g.d_006cec90)));
    ui_set_ctrl_font(*(iptr *)(active_dialog + 8));
    ui_set_default_font(ADDR(0x6cec90, ((u8 *)&g.d_006cec90)));
    uVar1 = this->style_flags & 4;
    local_cc = this->style_flags & 0x1000;
    if ((uVar1 == 0) && (local_cc == 0)) {
      if (0x28 < (int)this->option_count) {
        if (dialog_clamp_overflow == 0) {
          error_report(0xfffffff2,9,0,0x28,this->option_count);
        }
        else {
          this->option_count = 0x28;
        }
      }
      for (local_c8 = (uint *)this->option_list; local_c8 != (uint *)0x0;
          local_c8 = (uint *)local_c8[4]) {
        local_b4[local_d4] = local_c8[2];
        local_d4++;
      }
    }
    if (this->option_count != 0) {
      if (local_cc == 0) {
        if (uVar1 == 0) {
          this_00 = operator_new(0x50);
          local_8 = 7;
          if (this_00 == (InputControl *)0x0) {
            local_154 = 0;
          }
          else {
            local_154 = radiogrp_ctor(this_00);
          }
          local_8 = 0xffffffff;
          this->radio_group = local_154;
          uVar6 = this->columns;
          if ((int)uVar6 < 2) {
            uVar6 = 1;
          }
          rect_set_xywh((iptr)local_e4,this->list_x,this->list_y,this->option_width,
                             this->option_row_height *
                             ((int)((this->columns - 1) + this->option_count) / (int)uVar6));
          if (this->surf_wnd == 0) {
            local_18c = 0;
          }
          else {
            local_18c = this->surf_wnd + 0x48;
          }
          radiogrp_create
                    ((RadioGroup *)this->radio_group,local_18c,200,(iptr)local_e4,this->columns,
                     this->option_count,(iptr)local_b4);
          local_c8 = (uint *)this->option_list;
          local_104 = 0;
          for (; local_c8 != (uint *)0x0; local_c8 = (uint *)local_c8[4]) {
            if ((uint *)this->selected_option == local_c8) {
              radiogrp_set_selected((RadioGroupSetSelView *)this->radio_group,local_104);
            }
            if ((*local_c8 & 1) != 0) {
              radiogrp_disable_item((RadioGroupDisableView *)this->radio_group,local_104);
            }
            local_104++;
          }
          radiogrp_set_select_callback((Control *)this->radio_group,ADDR(0x4012ad, dialog_radio_on_select));
          radiogrp_set_dblclick_callback((Control *)this->radio_group,ADDR(0x5a3bae, dialog_radio_on_dblclick));
        }
        else {
          uVar6 = this->option_count;
          local_14c = operator_new(uVar6 * 0x3c + 4);
          local_8 = 6;
          if (local_14c == (u32 *)0x0) {
            local_14c = (u32 *)0x0;
          }
          else {
            *local_14c = uVar6;
            crt_vector_ctor_iterator(local_14c + 1,0x3c,*local_14c,checkbox_elem_ctor,
                         checkbox_dtor);
            local_14c++;
          }
          local_8 = 0xffffffff;
          this->checkboxes = (uptr)local_14c;
          uVar6 = this->list_x;
          local_f8 = this->list_y;
          local_c0 = 0;
          for (local_c8 = (uint *)this->option_list; local_c8 != (uint *)0x0;
              local_c8 = (uint *)local_c8[4]) {
            if (this->surf_wnd == 0) {
              local_188 = 0;
            }
            else {
              local_188 = this->surf_wnd + 0x48;
            }
            checkbox_create
                      ((Control *)(this->checkboxes + local_c0 * 0x3c),local_188,local_c0 + 200
                       ,uVar6,local_f8,local_c8[2]);
            checkbox_set_checked
                      ((Control *)(this->checkboxes + local_c0 * 0x3c),*local_c8 & 4);
            if ((*local_c8 & 1) != 0) {
              checkbox_disable((CheckboxDisableView *)(this->checkboxes + local_c0 * 0x3c));
            }
            local_f8 += this->option_row_height;
            local_c0++;
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
              local_8 = 1;
              if (pCVar2 == (Control *)0x0) {
                local_124 = 0;
              }
              else {
                local_124 = scrollbar_ctor(pCVar2);
              }
              local_8 = 0xffffffff;
              *(i32 *)(this->pad_294 + this->cur_pane * 4 - 0x10) = local_124;
              if (this->surf_wnd == 0) {
                local_174 = 0;
              }
              else {
                local_174 = this->surf_wnd + 0x48;
              }
              scrollbar_create
                        (*(Control **)(this->pad_294 + this->cur_pane * 4 - 0x10),local_174,
                         0xb,(iptr)(this->pad_178 + this->cur_pane * 0x10),1);
              iVar4 = dialog_count_group_options((DialogOptionList *)this,this->cur_pane);
              scrollbar_set_range
                        (*(Control **)(this->pad_294 + this->cur_pane * 4 - 0x10),0,
                         iVar4 - 1);
              iVar5 = dialog_option_group_index
                                ((DialogOptionList *)this,
                                 *(uptr *)(this->pad_1f8 + this->cur_pane * 4 + 0x18));
              scrollbar_set_pos
                        (*(ClickControl **)(this->pad_294 + this->cur_pane * 4 - 0x10),iVar5);
              scrollbar_set_page_size
                        (*(Control **)(this->pad_294 + this->cur_pane * 4 - 0x10),
                         (&this->list_rows)[this->cur_pane] - 1);
              scrollbar_set_callback
                        (*(Control **)(this->pad_294 + this->cur_pane * 4 - 0x10),ADDR(0x4036c0, dialog_list_on_vscroll));
              scrollbar_set_track_callback
                        (*(ScrollbarTrackSetView **)(this->pad_294 + this->cur_pane * 4 - 0x10),ADDR(0x4036c0, dialog_list_on_vscroll));
            }
            else {
              pCVar2 = operator_new(0x40);
              local_8 = 2;
              if (pCVar2 == (Control *)0x0) {
                local_12c = 0;
              }
              else {
                local_12c = scrollbar_ctor(pCVar2);
              }
              local_8 = 0xffffffff;
              *(i32 *)(this->pad_294 + this->cur_pane * 4 - 8) = local_12c;
              if (this->surf_wnd == 0) {
                local_178 = 0;
              }
              else {
                local_178 = this->surf_wnd + 0x48;
              }
              scrollbar_create
                        (*(Control **)(this->pad_294 + this->cur_pane * 4 - 8),local_178,0xc,
                         (iptr)(this->pad_178 + this->cur_pane * 0x10 + 0x20),0);
              iVar4 = dialog_count_group_options((DialogOptionList *)this,this->cur_pane);
              uVar3 = dialog_column_of_index((DialogTextView *)this,iVar4 - 1);
              scrollbar_set_range
                        (*(Control **)(this->pad_294 + this->cur_pane * 4 - 8),0,uVar3);
              uVar3 = dialog_option_group_index
                                ((DialogOptionList *)this,
                                 *(uptr *)(this->pad_1f8 + this->cur_pane * 4 + 0x18));
              iVar5 = dialog_column_of_index((DialogTextView *)this,uVar3);
              scrollbar_set_pos
                        (*(ClickControl **)(this->pad_294 + this->cur_pane * 4 - 8),iVar5);
              scrollbar_set_page_size
                        (*(Control **)(this->pad_294 + this->cur_pane * 4 - 8),this->columns
                        );
              scrollbar_set_callback
                        (*(Control **)(this->pad_294 + this->cur_pane * 4 - 8),ADDR(0x5a5494, dialog_list_on_hscroll));
              scrollbar_set_track_callback
                        (*(ScrollbarTrackSetView **)(this->pad_294 + this->cur_pane * 4 - 8),ADDR(0x5a5494, dialog_list_on_hscroll));
            }
          }
          wnd_set_lbuttondown_handler((WndHandlersMouseSetView *)(this->surf_wnd + 0x58),ADDR(0x5a4df3, dialog_list_on_lbuttondown));
          wnd_set_lbuttonup_any_handler((WndHandlersMouseSetView *)(this->surf_wnd + 0x58),ADDR(0x5a535e, dialog_list_on_lbuttonup));
          wnd_set_mousemove_handler((WndHandlersMouseSetView *)(this->surf_wnd + 0x58),ADDR(0x5a4edf, dialog_list_on_mousemove));
          wnd_set_dblclick_handler((WndHandlersMouseSetView *)(this->surf_wnd + 0x58),ADDR(0x5a53b8, dialog_list_on_dblclick));
        }
        else {
          pCVar2 = operator_new(0x3c);
          local_8 = 0;
          if (pCVar2 == (Control *)0x0) {
            local_11c = 0;
          }
          else {
            local_11c = checkbox_ctor(pCVar2);
          }
          local_8 = 0xffffffff;
          *(i32 *)(this->pad_264 + this->cur_pane * 4 + 0x14) = local_11c;
          rect_set_xywh((iptr)local_e4,this->list_x,this->list_y,
                             (&this->list_width)[this->cur_pane],(&this->list_height)[this->cur_pane]);
          if (this->surf_wnd == 0) {
            local_170 = 0;
          }
          else {
            local_170 = this->surf_wnd + 0x48;
          }
          listbox_create
                    (*(Control **)(this->pad_264 + this->cur_pane * 4 + 0x14),local_170,10,
                     (iptr)local_e4);
          local_c8 = (uint *)this->option_list;
          local_104 = 0;
          for (; local_c8 != (uint *)0x0; local_c8 = (uint *)local_c8[4]) {
            if (this->cur_pane == local_c8[3]) {
              listbox_add_string
                        (*(ListBoxAddView **)(this->pad_264 + this->cur_pane * 4 + 0x14),local_c8[2]);
              if ((uint *)this->selected_option == local_c8) {
                listbox_set_cur_sel
                          (*(ListBoxSetSelView **)(this->pad_264 + this->cur_pane * 4 + 0x14),local_104);
              }
              local_104++;
            }
          }
          listbox_set_dblclick_callback
                    (*(ListBoxDblClickSetView **)(this->pad_264 + this->cur_pane * 4 + 0x14),ADDR(0x5a3c83, dialog_listbox_on_dblclick));
        }
        if ((this->style_flags & 0x400000) != 0) {
          this->cur_pane = 1;
          if ((this->style_flags & 0x40000) == 0) {
            if (((int)((&this->list_rows)[this->cur_pane] * this->columns) < (int)this->option_count) ||
               ((this->style_flags & 0x1000000) != 0)) {
              if (this->columns == 1) {
                pCVar2 = operator_new(0x40);
                local_8 = 4;
                if (pCVar2 == (Control *)0x0) {
                  local_13c = 0;
                }
                else {
                  local_13c = scrollbar_ctor(pCVar2);
                }
                local_8 = 0xffffffff;
                *(i32 *)(this->pad_294 + this->cur_pane * 4 - 0x10) = local_13c;
                if (this->surf_wnd == 0) {
                  local_180 = 0;
                }
                else {
                  local_180 = this->surf_wnd + 0x48;
                }
                scrollbar_create
                          (*(Control **)(this->pad_294 + this->cur_pane * 4 - 0x10),local_180
                           ,0xb,(iptr)(this->pad_178 + this->cur_pane * 0x10),1);
                iVar4 = dialog_count_group_options((DialogOptionList *)this,this->cur_pane);
                scrollbar_set_range
                          (*(Control **)(this->pad_294 + this->cur_pane * 4 - 0x10),0,
                           iVar4 - 1);
                iVar5 = dialog_option_group_index
                                  ((DialogOptionList *)this,
                                   *(uptr *)(this->pad_1f8 + this->cur_pane * 4 + 0x18));
                scrollbar_set_pos
                          (*(ClickControl **)(this->pad_294 + this->cur_pane * 4 - 0x10),iVar5);
                scrollbar_set_page_size
                          (*(Control **)(this->pad_294 + this->cur_pane * 4 - 0x10),
                           (&this->list_rows)[this->cur_pane] - 1);
                scrollbar_set_callback
                          (*(Control **)(this->pad_294 + this->cur_pane * 4 - 0x10),ADDR(0x5a552c, dialog_list2_on_vscroll))
                ;
                scrollbar_set_track_callback
                          (*(ScrollbarTrackSetView **)(this->pad_294 + this->cur_pane * 4 - 0x10),ADDR(0x5a552c, dialog_list2_on_vscroll));
              }
              else {
                pCVar2 = operator_new(0x40);
                local_8 = 5;
                if (pCVar2 == (Control *)0x0) {
                  local_144 = 0;
                }
                else {
                  local_144 = scrollbar_ctor(pCVar2);
                }
                local_8 = 0xffffffff;
                *(i32 *)(this->pad_294 + this->cur_pane * 4 - 8) = local_144;
                if (this->surf_wnd == 0) {
                  local_184 = 0;
                }
                else {
                  local_184 = this->surf_wnd + 0x48;
                }
                scrollbar_create
                          (*(Control **)(this->pad_294 + this->cur_pane * 4 - 8),local_184,
                           0xc,(iptr)(this->pad_178 + this->cur_pane * 0x10 + 0x20),0);
                iVar4 = dialog_count_group_options((DialogOptionList *)this,this->cur_pane);
                uVar3 = dialog_column_of_index((DialogTextView *)this,iVar4 - 1);
                scrollbar_set_range
                          (*(Control **)(this->pad_294 + this->cur_pane * 4 - 8),0,uVar3);
                uVar3 = dialog_option_group_index
                                  ((DialogOptionList *)this,
                                   *(uptr *)(this->pad_1f8 + this->cur_pane * 4 + 0x18));
                iVar5 = dialog_column_of_index((DialogTextView *)this,uVar3);
                scrollbar_set_pos
                          (*(ClickControl **)(this->pad_294 + this->cur_pane * 4 - 8),iVar5);
                scrollbar_set_page_size
                          (*(Control **)(this->pad_294 + this->cur_pane * 4 - 8),
                           this->columns);
                scrollbar_set_callback
                          (*(Control **)(this->pad_294 + this->cur_pane * 4 - 8),ADDR(0x5a55b1, dialog_list2_on_hscroll));
                scrollbar_set_track_callback
                          (*(ScrollbarTrackSetView **)(this->pad_294 + this->cur_pane * 4 - 8),ADDR(0x5a55b1, dialog_list2_on_hscroll));
              }
            }
          }
          else {
            pCVar2 = operator_new(0x3c);
            local_8 = 3;
            if (pCVar2 == (Control *)0x0) {
              local_134 = 0;
            }
            else {
              local_134 = checkbox_ctor(pCVar2);
            }
            local_8 = 0xffffffff;
            *(i32 *)(this->pad_264 + this->cur_pane * 4 + 0x14) = local_134;
            rect_set_xywh((iptr)local_e4,this->list_x,this->list_y,
                               (&this->list_width)[this->cur_pane],(&this->list_height)[this->cur_pane]);
            if (this->surf_wnd == 0) {
              local_17c = 0;
            }
            else {
              local_17c = this->surf_wnd + 0x48;
            }
            listbox_create
                      (*(Control **)(this->pad_264 + this->cur_pane * 4 + 0x14),local_17c,10,
                       (iptr)local_e4);
            local_c8 = (uint *)this->option_list;
            local_104 = 0;
            for (; local_c8 != (uint *)0x0; local_c8 = (uint *)local_c8[4]) {
              if (this->cur_pane == local_c8[3]) {
                listbox_add_string
                          (*(ListBoxAddView **)(this->pad_264 + this->cur_pane * 4 + 0x14),local_c8[2]);
                if ((uint *)this->selected_option == local_c8) {
                  listbox_set_cur_sel
                            (*(ListBoxSetSelView **)(this->pad_264 + this->cur_pane * 4 + 0x14),local_104);
                }
                local_104++;
              }
            }
            listbox_set_dblclick_callback
                      (*(ListBoxDblClickSetView **)(this->pad_264 + this->cur_pane * 4 + 0x14),ADDR(0x5a3c83, dialog_listbox_on_dblclick));
          }
          this->cur_pane = 0;
        }
      }
    }
    if ((1 < (int)this->sprite_count) && (this->option_count == 0)) {
      uVar6 = this->sprite_count;
      local_15c = operator_new(uVar6 * 0x40 + 4);
      local_8 = 8;
      if (local_15c == (u32 *)0x0) {
        local_15c = (u32 *)0x0;
      }
      else {
        *local_15c = uVar6;
        crt_vector_ctor_iterator(local_15c + 1,0x40,*local_15c,hotspot_ctor,
                     hotspot_dtor);
        local_15c++;
      }
      local_8 = 0xffffffff;
      this->sprite_hotspots = (uptr)local_15c;
      uVar6 = this->sprite_x;
      local_f8 = this->sprite_y;
      local_c4 = this->sprite_list;
      local_c0 = 0;
      for (; local_c4 != 0; local_c4 = *(uptr *)(local_c4 + 0x10)) {
        local_b8 = gfx_zoom_scale(this->max_sprite_width,this->sprite_zoom);
        uVar8 = this->sprite_zoom;
        uVar3 = sprite_height(*(Sprite **)(local_c4 + 0xc));
        iVar4 = gfx_zoom_scale(uVar3,uVar8);
        rect_set_xywh((iptr)local_e4,uVar6,local_f8,local_b8,iVar4);
        if (this->surf_wnd == 0) {
          local_190 = 0;
        }
        else {
          local_190 = this->surf_wnd + 0x48;
        }
        hotspot_create
                  ((ClickControl *)(this->sprite_hotspots + local_c0 * 0x40),local_190,local_c0 + 300,
                   (iptr)local_e4);
        hotspot_set_click_callback((HotspotClickSetView *)(this->sprite_hotspots + local_c0 * 0x40),ADDR(0x5a3cca, dialog_on_sprite_click));
        hotspot_set_dblclick_callback((HotspotDblClickSetView *)(this->sprite_hotspots + local_c0 * 0x40),ADDR(0x5a3df3, dialog_sprite_on_dblclick));
        local_f8 = local_f8 + this->section_gap + iVar4;
        local_c0++;
      }
    }
    if (this->edit_field_list != 0) {
      local_fc = this->edit_field_list;
      uVar6 = this->edit_count;
      local_164 = operator_new(uVar6 * 0x48 + 4);
      local_8 = 9;
      if (local_164 == (u32 *)0x0) {
        local_164 = (u32 *)0x0;
      }
      else {
        *local_164 = uVar6;
        crt_vector_ctor_iterator(local_164 + 1,0x48,*local_164,edit_ctor,
                     edit_dtor);
        local_164++;
      }
      local_8 = 0xffffffff;
      this->edit_controls = (uptr)local_164;
      local_c0 = 0;
      for (; local_fc != 0; local_fc = *(uptr *)(local_fc + 0x18)) {
        if (this->surf_wnd == 0) {
          local_194 = 0;
        }
        else {
          local_194 = this->surf_wnd + 0x48;
        }
        uVar3 = *(i32 *)(local_fc + 0x14);
        uVar7 = *(i32 *)(local_fc + 4);
        iVar4 = dialog_edit_row_height((DialogCore *)this);
        edit_create_at
                  ((EditControl *)(this->edit_controls + local_c0 * 0x48),local_194,0x14,
                   this->edit_x + this->edit_label_width,iVar4 * local_c0 + this->edit_y,uVar7,uVar3)
        ;
        if (2 < game.multiplayer) {
          edit_set_change_callback((EditChangeSetView *)(this->edit_controls + local_c0 * 0x48),ADDR(0x402793, dialog_edit_on_change))
          ;
        }
        edit_set_max_len
                  ((EditMaxLenView *)(this->edit_controls + local_c0 * 0x48),*(i32 *)(local_fc + 8));
        local_c0++;
      }
    }
    if (this->std_button_count + this->extra_button_count != 0) {
      iVar4 = this->std_button_count + this->extra_button_count;
      local_16c = operator_new(iVar4 * 0x3c + 4);
      local_8 = 10;
      if (local_16c == (int *)0x0) {
        local_16c = (int *)0x0;
      }
      else {
        *local_16c = iVar4;
        crt_vector_ctor_iterator(local_16c + 1,0x3c,*local_16c,button_ctor,
                     ctrl_dtor);
        local_16c++;
      }
      local_8 = 0xffffffff;
      this->button_controls = (uptr)local_16c;
    }
    for (local_c0 = 0; local_c0 < (int)(this->std_button_count + this->extra_button_count); local_c0++) {
      if (local_c0 < (int)this->std_button_count) {
        local_d0 = *(iptr *)(this->pad_294 + local_c0 * 8 + 0x18);
        local_e8 = (&dialog_button_labels)[local_d0];
      }
      else {
        local_d0 = -1;
        local_e8 = *(i8 **)((int)this + (local_c0 - this->std_button_count) * 4 + 0x294);
      }
      iVar5 = dialog_line_height((DialogTextView *)this);
      rect_set_xywh((iptr)local_e4,*(i32 *)(this->pad_294 + local_c0 * 8 + 0x1c),
                         this->button_y,this->button_width,iVar5);
      if (this->surf_wnd == 0) {
        local_198 = 0;
      }
      else {
        local_198 = this->surf_wnd + 0x48;
      }
      button_create
                ((Control *)(this->button_controls + local_c0 * 0x3c),local_198,local_c0 + 100,
                 (iptr)local_e4,(iptr)local_e8);
      if ((local_d0 == 2) || ((local_d0 == 0 && ((this->style_flags & 1) == 0)))) {
        ctrl_set_cancel_button((Control *)(this->button_controls + local_c0 * 0x3c));
      }
      if (local_d0 == 0) {
        ctrl_set_default_button((Control *)(this->button_controls + local_c0 * 0x3c));
      }
      button_set_callback
                ((Control *)(this->button_controls + local_c0 * 0x3c),ADDR(0x5a3e56, dialog_on_button_click));
    }
    wnd_set_keydown_handler((WndEventHandlers *)(this->surf_wnd + 0x58),ADDR(0x5a407f, dialog_on_keydown));
    wnd_set_char_handler((WndEventHandlers *)(this->surf_wnd + 0x58),ADDR(0x5a49c1, dialog_on_char));
    this->style_flags = this->style_flags | 0x200;
  }
  return;
}
#undef dialog_clamp_overflow
#undef dialog_stack
#undef dialog_stack_top
#undef local_198
#undef local_194
#undef local_190
#undef local_18c
#undef local_188
#undef local_184
#undef local_180
#undef local_17c
#undef local_178
#undef local_174
#undef local_170
#undef local_16c
#undef local_164
#undef local_15c
#undef local_154
#undef local_14c
#undef local_144
#undef local_13c
#undef local_134
#undef local_12c
#undef local_124
#undef local_11c
#undef local_104
#undef local_fc
#undef local_f8
#undef local_e8
#undef local_e4
#undef local_d4
#undef local_d0
#undef local_cc
#undef local_c8
#undef local_c4
#undef local_c0
#undef local_bc
#undef local_b8
#undef local_b4
#undef local_10
#undef puStack_c
#undef local_8

/* 005a3bae auto */
#define local_10 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(8)))
void __cdecl dialog_radio_on_dblclick(i32 param_1,int param_2)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_10 = 0;
  if (active_dialog != 0) {
    local_c = 0;
    for (local_8 = *(iptr *)(active_dialog + 0x228); local_8 != 0;
        local_8 = *(iptr *)(local_8 + 0x10)) {
      if (param_2 == local_c) {
        local_10 = local_8;
      }
      local_c++;
    }
    *(i32 *)(active_dialog + 0xd8) = 0xffffffff;
    if (local_10 != 0) {
      *(i32 *)(active_dialog + 0xd8) = *(i32 *)(local_10 + 4);
    }
    *(uint *)(active_dialog + 0x3c) = *(uint *)(active_dialog + 0x3c) | 0x2000;
    dialog_end_current();
  }
  return;
}
#undef local_10
#undef local_c
#undef local_8

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
#define local_c (*(i32 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl dialog_on_sprite_click(int param_1)

{
  bool bVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  bVar1 = false;
  local_c = *(i32 **)(active_dialog + 0x234);
  if (local_c != (i32 *)0x0) {
    for (local_8 = 0; local_8 < param_1 - 300; local_8++) {
      local_c = (i32 *)local_c[4];
      if (local_c == (i32 *)0x0) {
        return;
      }
    }
    *(i32 *)(active_dialog + 0xd8) = *local_c;
    if ((*(i32 **)(active_dialog + 0x224) != local_c) &&
       (*(i32 **)(active_dialog + 0x224) = local_c,
       (*(byte *)(active_dialog + 0x3e) & 2) != 0)) {
      bVar1 = true;
    }
    if (*(int *)(active_dialog + 0x23c) == 0) {
      if (bVar1) {
        dialog_render((Dialog *)active_dialog);
      }
    }
    else {
      iVar2 = (*((code **)(active_dialog))[143])(*local_c);
      dialog_render((Dialog *)active_dialog);
      if (iVar2 != 0) {
        *(uint *)(active_dialog + 0x3c) = *(uint *)(active_dialog + 0x3c) | 0x2000;
        dialog_end_current();
      }
    }
  }
  return;
}
#undef local_c
#undef local_8

/* 005a3df3 auto */
void __cdecl dialog_sprite_on_dblclick(void)

{
  int iVar1;
  
  if (*(int *)(active_dialog + 0x240) != 0) {
    iVar1 = (*((code **)(active_dialog))[144])(0);
    if (iVar1 == 0) {
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
#define local_20 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_1c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(12)))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(24)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl dialog_on_button_click(int param_1)

{
  int iVar1;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (active_dialog != 0) {
    dialog_timeout_start_i32 = timer_ticks();
    iVar1 = param_1 - 100;
    if (iVar1 < *(int *)(active_dialog + 0x30)) {
      local_18 = *(int *)(active_dialog + 0x2ac + iVar1 * 8);
    }
    else {
      *(int *)(active_dialog + 0xdc) = (iVar1 - *(int *)(active_dialog + 0x30)) + 1;
      local_18 = 0;
    }
    if (local_18 == 1) {
      *(uint *)(active_dialog + 0x3c) = *(uint *)(active_dialog + 0x3c) | 0x80;
    }
    if (((local_18 == 0) && ((*(byte *)(active_dialog + 0x3e) & 2) != 0)) &&
       (*(int *)(active_dialog + 0x224) != 0)) {
      local_8 = *(iptr *)(active_dialog + 0x234);
      local_20 = 0;
      for (; (local_8 != 0 && (*(int *)(active_dialog + 0x224) != local_8));
          local_8 = *(iptr *)(local_8 + 0x10)) {
        local_20++;
      }
      if (local_8 != 0) {
        dialog_on_sprite_click(local_20 + 300);
      }
    }
    if (local_18 == 2) {
      *(i32 *)(active_dialog + 0xd8) = 0xffffffff;
    }
    else {
      if ((*(int *)(active_dialog + 0x2c) < 2) || (*(int *)(active_dialog + 0x28) != 0)) {
        *(i32 *)(active_dialog + 0xd8) = 0;
      }
      if ((*(int *)(active_dialog + 0x28) != 0) && ((*(uint *)(active_dialog + 0x3c) & 0x1004) == 0)
         ) {
        local_14 = 0;
        local_1c = 0;
        local_c = *(iptr *)(active_dialog + 0x228);
        iVar1 = radiogrp_get_selected(*(RadioGroupGetSelView **)(active_dialog + 0x268));
        for (; local_c != 0; local_c = *(iptr *)(local_c + 0x10)) {
          if (iVar1 == local_14) {
            local_1c = local_c;
          }
          local_14++;
        }
        if (local_1c != 0) {
          *(i32 *)(active_dialog + 0xd8) = *(i32 *)(local_1c + 4);
        }
      }
    }
    dialog_end_current();
  }
  return;
}
#undef dialog_timeout_start_i32
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef local_c
#undef local_8

/* 005a407f auto */
#define dialog_timeout_start_i32 (*(i32 *)((u8 *)&g.d_006cec80))
#define local_c (*(uptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(uptr *)(frame_ + FRAME_OFF(8)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl dialog_on_keydown(i32 param_1)

{
  int iVar1;
  uptr uVar2;
  int iVar3;
  int iVar4;
  i32 uVar5;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (active_dialog == 0) {
    return;
  }
  if (((*(byte *)(active_dialog + 0x3d) & 0x10) == 0) || (*(int *)(active_dialog + 0x24) != 0)) {
    dialog_timeout_start_i32 = timer_ticks();
  }
  if ((*(byte *)(active_dialog + 0x3e) & 2) != 0) {
    switch(param_1) {
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
      for (local_c = *(uptr *)(active_dialog + 0x234);
          ((local_c != 0 && (*(int *)(local_c + 0x10) != *(int *)(active_dialog + 0x224))) &&
          (*(int *)(local_c + 0x10) != 0)); local_c = *(uptr *)(local_c + 0x10)) {
      }
      *(uptr *)(active_dialog + 0x224) = local_c;
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
    param_1 = 0;
  }
  do {
    switch(param_1) {
    case 0xa1:
    case 199:
      iVar3 = dialog_option_group_index
                        ((DialogOptionList *)active_dialog,*(uptr *)(active_dialog + 0x220));
      iVar4 = dialog_count_group_options
                        ((DialogOptionList *)active_dialog,*(i32 *)(active_dialog + 0x48));
      if (iVar4 - 1 <= iVar3) {
        return;
      }
      iVar3 = dialog_count_group_options
                        ((DialogOptionList *)active_dialog,*(i32 *)(active_dialog + 0x48));
      uVar5 = dialog_option_at((DialogOptionList *)active_dialog,iVar3 - 1);
      *(i32 *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) = uVar5;
      dialog_select_option
                ((DialogOptionList *)active_dialog,
                 *(uptr *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4),0);
      dialog_draw_option_list((DialogOptionList *)active_dialog);
      return;
    case 0xa2:
    case 0xc1:
      local_8 = *(uptr *)(active_dialog + 0x220);
      goto LAB_005a43d9;
    case 0xa3:
    case 0xc6:
      if (*(int *)(active_dialog + 0x38) < 2) {
        iVar4 = dialog_option_group_index
                          ((DialogOptionList *)active_dialog,*(uptr *)(active_dialog + 0x220));
        iVar3 = *(int *)(active_dialog + 0x5c + *(int *)(active_dialog + 0x48) * 4);
        iVar1 = dialog_count_group_options
                          ((DialogOptionList *)active_dialog,*(i32 *)(active_dialog + 0x48));
        if (iVar3 + iVar4 < iVar1) {
          uVar5 = 1;
          uVar2 = dialog_option_at
                            ((DialogOptionList *)active_dialog,
                             iVar4 + *(int *)(active_dialog + 0x5c +
                                             *(int *)(active_dialog + 0x48) * 4));
          dialog_select_option((DialogOptionList *)active_dialog,uVar2,uVar5);
          return;
        }
        iVar3 = dialog_count_group_options
                          ((DialogOptionList *)active_dialog,*(i32 *)(active_dialog + 0x48));
        uVar5 = 1;
        uVar2 = dialog_option_at((DialogOptionList *)active_dialog,iVar3 - 1);
        dialog_select_option((DialogOptionList *)active_dialog,uVar2,uVar5);
        return;
      }
      param_1 = 0xc3;
      break;
    case 0xa4:
    case 0xc2:
      if (*(int *)(active_dialog + 0x38) != 1) {
        iVar3 = dialog_option_group_index
                          ((DialogOptionList *)active_dialog,*(uptr *)(active_dialog + 0x220));
        iVar4 = dialog_option_group_index
                          ((DialogOptionList *)active_dialog,
                           *(uptr *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4));
        if (*(int *)(active_dialog + 0x5c + *(int *)(active_dialog + 0x48) * 4) + iVar4 <= iVar3) {
          uVar5 = 1;
          uVar2 = dialog_option_at
                            ((DialogOptionList *)active_dialog,
                             iVar3 - *(int *)(active_dialog + 0x5c +
                                             *(int *)(active_dialog + 0x48) * 4));
          dialog_select_option((DialogOptionList *)active_dialog,uVar2,uVar5);
          return;
        }
        if (iVar3 < *(int *)(active_dialog + 0x5c + *(int *)(active_dialog + 0x48) * 4)) {
          return;
        }
        iVar3 = dialog_option_group_index
                          ((DialogOptionList *)active_dialog,
                           *(uptr *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4));
        uVar5 = dialog_option_at
                          ((DialogOptionList *)active_dialog,
                           iVar3 - *(int *)(active_dialog + 0x5c +
                                           *(int *)(active_dialog + 0x48) * 4));
        *(i32 *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) = uVar5;
        iVar3 = dialog_option_group_index
                          ((DialogOptionList *)active_dialog,*(uptr *)(active_dialog + 0x220));
        uVar5 = 0;
        uVar2 = dialog_option_at
                          ((DialogOptionList *)active_dialog,
                           iVar3 - *(int *)(active_dialog + 0x5c +
                                           *(int *)(active_dialog + 0x48) * 4));
        dialog_select_option((DialogOptionList *)active_dialog,uVar2,uVar5);
        dialog_draw_option_list((DialogOptionList *)active_dialog);
        return;
      }
      param_1 = 0xc0;
      break;
    default:
      return;
    case 0xa6:
    case 0xc3:
      if (*(int *)(active_dialog + 0x38) != 1) {
        iVar4 = dialog_option_group_index
                          ((DialogOptionList *)active_dialog,*(uptr *)(active_dialog + 0x220));
        iVar3 = *(int *)(active_dialog + 0x5c + *(int *)(active_dialog + 0x48) * 4);
        iVar1 = dialog_count_group_options
                          ((DialogOptionList *)active_dialog,*(i32 *)(active_dialog + 0x48));
        if (iVar1 <= iVar3 + iVar4) {
          return;
        }
        uVar5 = 1;
        uVar2 = dialog_option_at
                          ((DialogOptionList *)active_dialog,
                           iVar4 + *(int *)(active_dialog + 0x5c +
                                           *(int *)(active_dialog + 0x48) * 4));
        dialog_select_option((DialogOptionList *)active_dialog,uVar2,uVar5);
        return;
      }
      param_1 = 0xc1;
      break;
    case 0xa7:
    case 0xc4:
      iVar3 = dialog_option_group_index
                        ((DialogOptionList *)active_dialog,*(uptr *)(active_dialog + 0x220));
      if (iVar3 < 1) {
        return;
      }
      uVar5 = dialog_option_at((DialogOptionList *)active_dialog,0);
      *(i32 *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) = uVar5;
      dialog_select_option
                ((DialogOptionList *)active_dialog,
                 *(uptr *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4),0);
      dialog_draw_option_list((DialogOptionList *)active_dialog);
      return;
    case 0xa8:
    case 0xc0:
      local_8 = *(uptr *)(active_dialog + 0x220);
      goto LAB_005a4287;
    case 0xa9:
    case 0xc5:
      if (*(int *)(active_dialog + 0x38) < 2) {
        iVar3 = dialog_option_group_index
                          ((DialogOptionList *)active_dialog,*(uptr *)(active_dialog + 0x220));
        if (*(int *)(active_dialog + 0x5c + *(int *)(active_dialog + 0x48) * 4) <= iVar3) {
          uVar5 = 1;
          uVar2 = dialog_option_at
                            ((DialogOptionList *)active_dialog,
                             iVar3 - *(int *)(active_dialog + 0x5c +
                                             *(int *)(active_dialog + 0x48) * 4));
          dialog_select_option((DialogOptionList *)active_dialog,uVar2,uVar5);
          return;
        }
        uVar5 = 1;
        uVar2 = dialog_option_at((DialogOptionList *)active_dialog,0);
        dialog_select_option((DialogOptionList *)active_dialog,uVar2,uVar5);
        return;
      }
      param_1 = 0xc2;
    }
  } while( true );
  while (local_8 = *(uptr *)(local_8 + 0x14),
        *(int *)(active_dialog + 0x48) != *(int *)(local_8 + 0xc)) {
LAB_005a4287:
    if (*(int *)(local_8 + 0x14) == 0) break;
  }
  if (*(int *)(active_dialog + 0x48) != *(int *)(local_8 + 0xc)) {
    return;
  }
  if (*(uptr *)(active_dialog + 0x220) == local_8) {
    return;
  }
  if (*(int *)(active_dialog + 0x38) != 1) {
    iVar3 = dialog_option_group_index
                      ((DialogOptionList *)active_dialog,
                       *(uptr *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4));
    iVar4 = dialog_option_group_index((DialogOptionList *)active_dialog,local_8);
    if (iVar4 < iVar3) {
      iVar3 = dialog_option_group_index
                        ((DialogOptionList *)active_dialog,
                         *(uptr *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4));
      uVar5 = dialog_option_at
                        ((DialogOptionList *)active_dialog,
                         iVar3 - *(int *)(active_dialog + 0x5c + *(int *)(active_dialog + 0x48) * 4)
                        );
      *(i32 *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) = uVar5;
      dialog_select_option((DialogOptionList *)active_dialog,local_8,0);
      dialog_draw_option_list((DialogOptionList *)active_dialog);
      return;
    }
  }
  dialog_select_option((DialogOptionList *)active_dialog,local_8,1);
  return;
  while (local_8 = *(uptr *)(local_8 + 0x10),
        *(int *)(active_dialog + 0x48) != *(int *)(local_8 + 0xc)) {
LAB_005a43d9:
    if (*(int *)(local_8 + 0x10) == 0) break;
  }
  if ((*(int *)(active_dialog + 0x48) == *(int *)(local_8 + 0xc)) &&
     (*(uptr *)(active_dialog + 0x220) != local_8)) {
    dialog_select_option((DialogOptionList *)active_dialog,local_8,1);
  }
  return;
}
#undef dialog_timeout_start_i32
#undef local_c
#undef local_8

/* 005a49c1 auto */
#define dialog_timeout_start_i32 (*(i32 *)((u8 *)&g.d_006cec80))
#define local_1c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(uptr *)(frame_ + FRAME_OFF(8)))
#define local_10 (*(uptr *)(frame_ + FRAME_OFF(16)))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(20)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl dialog_on_char(byte param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  i32 uVar6;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((active_dialog != 0) && (iVar1 = _isalpha((uint)param_1), iVar1 != 0)) {
    dialog_timeout_start_i32 = timer_ticks();
    uVar2 = crt_toupper((uint)param_1);
    if ((*(uint *)(active_dialog + 0x3c) & 0x41000) == 0x1000) {
      local_10 = *(uptr *)(active_dialog + 0x220);
      local_18 = 0;
      local_c = 0;
      do {
        do {
          local_10 = *(uptr *)(local_10 + 0x10);
          if (local_10 == 0) {
            local_10 = *(uptr *)(active_dialog + 0x228);
          }
        } while (*(int *)(active_dialog + 0x48) != *(int *)(local_10 + 0xc));
        uVar3 = crt_toupper((int)**(char **)(local_10 + 8));
        if (uVar3 == (uVar2 & 0xff)) {
          local_18 = local_10;
        }
      } while ((local_18 == 0) && (local_c = local_c + 1, local_c < 2000));
      if (local_18 != 0) {
        iVar1 = dialog_option_group_index((DialogOptionList *)active_dialog,local_18);
        local_c = 0;
        while( true ) {
          iVar4 = dialog_option_group_index
                            ((DialogOptionList *)active_dialog,
                             *(uptr *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4));
          iVar5 = *(int *)(active_dialog + 0x5c + *(int *)(active_dialog + 0x48) * 4) *
                  *(int *)(active_dialog + 0x38) + iVar4;
          if ((*(int *)(active_dialog + 0x38) == 1) || ((iVar4 <= iVar1 && (iVar1 < iVar5)))) break;
          if (iVar1 < iVar4) {
            uVar6 = dialog_option_at
                              ((DialogOptionList *)active_dialog,
                               iVar4 - *(int *)(active_dialog + 0x5c +
                                               *(int *)(active_dialog + 0x48) * 4));
            *(i32 *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) = uVar6;
            local_c++;
          }
          else {
            if (iVar1 < iVar5) {
              return;
            }
            uVar6 = dialog_option_at
                              ((DialogOptionList *)active_dialog,
                               iVar4 + *(int *)(active_dialog + 0x5c +
                                               *(int *)(active_dialog + 0x48) * 4));
            *(i32 *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) = uVar6;
            local_c++;
          }
        }
        if (local_c == 0) {
          dialog_select_option((DialogOptionList *)active_dialog,local_18,1);
        }
        else {
          dialog_select_option((DialogOptionList *)active_dialog,local_18,0);
          dialog_draw_option_list((DialogOptionList *)active_dialog);
        }
      }
    }
    else if ((*(byte *)(active_dialog + 0x3e) & 2) == 0) {
      if (*(int *)(active_dialog + 0x34) != 0) {
        local_1c = -1;
        for (local_c = 0; local_c < *(int *)(active_dialog + 0x34); local_c++) {
          uVar3 = crt_toupper((int)**(char **)(active_dialog + 0x294 + local_c * 4));
          if (uVar3 == (uVar2 & 0xff)) {
            local_1c = local_c;
            break;
          }
        }
        if (-1 < local_1c) {
          ctrl_set_focus
                    ((ControlFocusView *)
                     ((*(int *)(active_dialog + 0x30) + local_c) * 0x3c +
                     *(int *)(active_dialog + 0x274)));
          dialog_on_button_click(*(int *)(active_dialog + 0x30) + local_c + 100);
          return;
        }
      }
      if (*(int *)(active_dialog + 0x28) != 0) {
        local_18 = 0;
        local_1c = 0;
        for (local_10 = *(uptr *)(active_dialog + 0x228); local_10 != 0;
            local_10 = *(uptr *)(local_10 + 0x10)) {
          uVar3 = crt_toupper((int)**(char **)(local_10 + 8));
          if (uVar3 == (uVar2 & 0xff)) {
            local_18 = local_10;
            break;
          }
          local_1c++;
        }
        if (local_18 != 0) {
          if ((*(byte *)(active_dialog + 0x3d) & 0x10) == 0) {
            if ((*(byte *)(active_dialog + 0x3c) & 4) == 0) {
              radiogrp_set_selected(*(RadioGroupSetSelView **)(active_dialog + 0x268),local_1c);
            }
          }
          else {
            listbox_set_cur_sel
                      (*(ListBoxSetSelView **)(active_dialog + 0x278 + *(int *)(active_dialog + 0x48) * 4),
                       local_1c);
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
#undef local_1c
#undef local_18
#undef local_10
#undef local_c

/* 005a4df3 auto */
void __cdecl dialog_list_on_lbuttondown(i32 param_1,i32 param_2)

{
  int iVar1;
  uptr uVar2;
  i32 uVar3;
  
  if (active_dialog != 0) {
    dialog_pick_pane_at((DialogWindowView *)active_dialog,param_1,param_2);
    *(i32 *)(active_dialog + 0x218 + *(int *)(active_dialog + 0x48) * 4) = 0;
    if ((((*(uint *)(active_dialog + 0x3c) & 0x41000) == 0x1000) &&
        (*(int *)(active_dialog + 0x28) != 0)) &&
       (iVar1 = dialog_option_at_point((DialogOptionList *)active_dialog,param_1,param_2),
       -1 < iVar1)) {
      *(i32 *)(active_dialog + 0x218 + *(int *)(active_dialog + 0x48) * 4) = 1;
      wnd_set_capture((WndBase *)(*(int *)active_dialog + 0x48));
      uVar3 = 1;
      uVar2 = dialog_option_at((DialogOptionList *)active_dialog,iVar1);
      dialog_select_option((DialogOptionList *)active_dialog,uVar2,uVar3);
    }
  }
  return;
}

/* 005a4edf auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl dialog_list_on_mousemove(i32 param_1,i32 param_2)

{
  int iVar1;
  int iVar2;
  uptr uVar3;
  int iVar4;
  int iVar5;
  i32 uVar6;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((active_dialog != 0) && ((*(uint *)(active_dialog + 0x3c) & 0x41000) == 0x1000)) &&
     (*(int *)(active_dialog + 0x218 + *(int *)(active_dialog + 0x48) * 4) != 0)) {
    iVar2 = dialog_option_at_point((DialogOptionList *)active_dialog,param_1,param_2);
    if (iVar2 < 0) {
      if (*(int *)(active_dialog + 0x5c + *(int *)(active_dialog + 0x48) * 4) *
          *(int *)(active_dialog + 0x38) < *(int *)(active_dialog + 0x28)) {
        iVar4 = dialog_option_group_index
                          ((DialogOptionList *)active_dialog,
                           *(uptr *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4));
        switch(iVar2) {
        case -4:
          if ((1 < *(int *)(active_dialog + 0x38)) &&
             (iVar2 = dialog_column_start_index
                                ((DialogTextView *)active_dialog,*(int *)(active_dialog + 0x28) - 1)
             , iVar4 < iVar2)) {
            iVar2 = *(int *)(active_dialog + 0x5c + *(int *)(active_dialog + 0x48) * 4);
            iVar1 = *(int *)(active_dialog + 0x5c + *(int *)(active_dialog + 0x48) * 4);
            iVar5 = dialog_column_of_index
                              ((DialogTextView *)active_dialog,*(int *)(active_dialog + 0x28) - 1);
            iVar2 = int_clamp_b(iVar4 + iVar2,0,iVar1 * iVar5);
            iVar4 = dialog_option_group_index
                              ((DialogOptionList *)active_dialog,*(uptr *)(active_dialog + 0x220));
            for (local_8 = iVar4 % *(int *)(active_dialog + 0x5c +
                                           *(int *)(active_dialog + 0x48) * 4) + iVar2;
                *(int *)(active_dialog + 0x5c + *(int *)(active_dialog + 0x48) * 4) + local_8 <
                *(int *)(active_dialog + 0x5c + *(int *)(active_dialog + 0x48) * 4) *
                *(int *)(active_dialog + 0x38) + iVar2;
                local_8 = local_8 + *(int *)(active_dialog + 0x5c +
                                            *(int *)(active_dialog + 0x48) * 4)) {
            }
            uVar6 = int_clamp_b(local_8,0,*(int *)(active_dialog + 0x28) - 1);
            uVar6 = dialog_option_at((DialogOptionList *)active_dialog,uVar6);
            *(i32 *)(active_dialog + 0x220) = uVar6;
            uVar6 = dialog_option_at((DialogOptionList *)active_dialog,iVar2);
            *(i32 *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) = uVar6;
            dialog_draw_option_list((DialogOptionList *)active_dialog);
          }
          break;
        case -3:
          if ((1 < *(int *)(active_dialog + 0x38)) && (0 < iVar4)) {
            iVar4 -= *(int *)(active_dialog + 0x5c + *(int *)(active_dialog + 0x48) * 4);
            if (iVar4 < 1) {
              iVar4 = 0;
            }
            uVar6 = dialog_option_at((DialogOptionList *)active_dialog,iVar4);
            *(i32 *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) = uVar6;
            iVar2 = dialog_option_group_index
                              ((DialogOptionList *)active_dialog,*(uptr *)(active_dialog + 0x220));
            uVar6 = dialog_option_at
                              ((DialogOptionList *)active_dialog,
                               iVar4 + iVar2 % *(int *)(active_dialog + 0x5c +
                                                       *(int *)(active_dialog + 0x48) * 4));
            *(i32 *)(active_dialog + 0x220) = uVar6;
            dialog_draw_option_list((DialogOptionList *)active_dialog);
          }
          break;
        case -2:
          if ((iVar4 < *(int *)(active_dialog + 0x28) - 1) && (*(int *)(active_dialog + 0x38) == 1)
             ) {
            uVar6 = dialog_option_at((DialogOptionList *)active_dialog,iVar4 + 1);
            *(i32 *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) = uVar6;
            uVar6 = int_clamp_b(*(int *)(active_dialog + 0x5c + *(int *)(active_dialog + 0x48) * 4)
                                 * *(int *)(active_dialog + 0x38) + iVar4 + 1 - 1,0,
                                 *(int *)(active_dialog + 0x28) - 1);
            uVar6 = dialog_option_at((DialogOptionList *)active_dialog,uVar6);
            *(i32 *)(active_dialog + 0x220) = uVar6;
            dialog_draw_option_list((DialogOptionList *)active_dialog);
          }
          break;
        case -1:
          if ((0 < iVar4) && (*(int *)(active_dialog + 0x38) == 1)) {
            uVar6 = dialog_option_at((DialogOptionList *)active_dialog,iVar4 - 1);
            *(i32 *)(active_dialog + 0x220) = uVar6;
            *(i32 *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) =
                 *(i32 *)(active_dialog + 0x220);
            dialog_draw_option_list((DialogOptionList *)active_dialog);
          }
        }
      }
    }
    else {
      uVar6 = 1;
      uVar3 = dialog_option_at((DialogOptionList *)active_dialog,iVar2);
      dialog_select_option((DialogOptionList *)active_dialog,uVar3,uVar6);
    }
  }
  return;
}
#undef local_8

/* 005a535e auto */
void __cdecl dialog_list_on_lbuttonup(i32 param_1,i32 param_2)

{
  if (active_dialog != 0) {
    dialog_list_on_mousemove(param_1,param_2);
    *(i32 *)(active_dialog + 0x218 + *(int *)(active_dialog + 0x48) * 4) = 0;
    wnd_release_capture((WndBase *)(*(int *)active_dialog + 0x48));
  }
  return;
}

/* 005a53b8 auto */
void __cdecl dialog_list_on_dblclick(i32 param_1,i32 param_2)

{
  int iVar1;
  
  if ((((active_dialog != 0) &&
       (dialog_pick_pane_at((DialogWindowView *)active_dialog,param_1,param_2),
       (*(uint *)(active_dialog + 0x3c) & 0x41000) == 0x1000)) &&
      (*(int *)(active_dialog + 0x28) != 0)) &&
     (((*(byte *)(active_dialog + 0x3d) & 4) == 0 &&
      (iVar1 = dialog_option_at_point((DialogOptionList *)active_dialog,param_1,param_2),
      -1 < iVar1)))) {
    *(i32 *)(active_dialog + 0x218 + *(int *)(active_dialog + 0x48) * 4) = 1;
    dialog_list_on_lbuttonup(param_1,param_2);
    *(uint *)(active_dialog + 0x3c) = *(uint *)(active_dialog + 0x3c) | 0x2000;
    dialog_end_current();
  }
  return;
}

/* 005a5494 auto */
void __cdecl dialog_list_on_hscroll(int param_1)

{
  int iVar1;
  
  if (active_dialog != 0) {
    *(i32 *)(active_dialog + 0x48) = 0;
    iVar1 = dialog_option_at
                      ((DialogOptionList *)active_dialog,
                       *(int *)(active_dialog + 0x5c + *(int *)(active_dialog + 0x48) * 4) * param_1
                      );
    if (*(int *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) != iVar1) {
      *(int *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) = iVar1;
      dialog_draw_option_list((DialogOptionList *)active_dialog);
    }
  }
  return;
}

/* 005a552c auto */
void __cdecl dialog_list2_on_vscroll(i32 param_1)

{
  int iVar1;
  
  if (active_dialog != 0) {
    *(i32 *)(active_dialog + 0x48) = 1;
    iVar1 = dialog_option_at((DialogOptionList *)active_dialog,param_1);
    if (*(int *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) != iVar1) {
      *(int *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) = iVar1;
      dialog_draw_option_list((DialogOptionList *)active_dialog);
    }
  }
  return;
}

/* 005a55b1 auto */
void __cdecl dialog_list2_on_hscroll(int param_1)

{
  int iVar1;
  
  if (active_dialog != 0) {
    *(i32 *)(active_dialog + 0x48) = 1;
    iVar1 = dialog_option_at
                      ((DialogOptionList *)active_dialog,
                       *(int *)(active_dialog + 0x5c + *(int *)(active_dialog + 0x48) * 4) * param_1
                      );
    if (*(int *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) != iVar1) {
      *(int *)(active_dialog + 0x210 + *(int *)(active_dialog + 0x48) * 4) = iVar1;
      dialog_draw_option_list((DialogOptionList *)active_dialog);
    }
  }
  return;
}

/* 005a5649 auto */
#define dlg_client_tile_surface (*(int *)((u8 *)&g.d_00635aa4))
#define dlg_frame_tile_surface (*(int *)((u8 *)&g.d_00635aa0))
void __thiscall dialog_fill_rect_bg(DialogTextView *this,iptr param_1,int param_2)

{
  i32 uVar1;
  i32 uVar2;
  i32 uVar3;
  i32 uVar4;
  
  if (this->bg_surface == 0) {
    if ((dlg_frame_tile_surface == 0) || (param_2 != 1)) {
      if ((dlg_client_tile_surface == 0) || (param_2 != 2)) {
        gfx_fill_rect(this->surf_wnd,param_1,this->bg_color);
      }
      else {
        uVar4 = 0;
        uVar3 = 0;
        uVar1 = rect_height(param_1);
        uVar2 = rect_width(param_1);
        gfx_tile_fill(this->surf_wnd,dlg_client_tile_surface,*(i32 *)param_1,
                           *(i32 *)(param_1 + 4),uVar2,uVar1,uVar3,uVar4);
      }
    }
    else {
      uVar4 = 0;
      uVar3 = 0;
      uVar1 = rect_height(param_1);
      uVar2 = rect_width(param_1);
      gfx_tile_fill(this->surf_wnd,dlg_frame_tile_surface,*(i32 *)param_1,
                         *(i32 *)(param_1 + 4),uVar2,uVar1,uVar3,uVar4);
    }
  }
  else {
    uVar1 = rect_height(param_1);
    uVar2 = rect_width(param_1);
    gfx_copy_rect_same_pos(this->bg_surface,this->surf_wnd,*(i32 *)param_1,
                       *(i32 *)(param_1 + 4),uVar2,uVar1);
  }
  return;
}
#undef dlg_client_tile_surface
#undef dlg_frame_tile_surface

/* 005a577e auto */
#define local_5c (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_4c (*(u32 *)(frame_ + FRAME_OFF(20)))
#define local_48 (*(u32 *)(frame_ + FRAME_OFF(24)))
#define local_44 (*(int *)(frame_ + FRAME_OFF(28)))
#define local_40 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_3c (*(uptr *)(frame_ + FRAME_OFF(36)))
#define local_38 (*(u32 *)(frame_ + FRAME_OFF(40)))
#define local_34 (*(u32 *)(frame_ + FRAME_OFF(44)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(52)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(56)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(60)))
#define local_20 (*(i32 * *)(frame_ + FRAME_OFF(64)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(68)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(72)))
#define local_14 (*(i8 (*)[4])(frame_ + FRAME_OFF(76)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(80)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(88)))
void __thiscall dialog_render(Dialog *this)

{
  int iVar1;
  i32 uVar2;
  int iVar3;
  int iVar4;
  u32 uVar5;
  i8 frame_[FRAME_OFF(96)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_30 = 0;
  if ((this->style_flags & 0x20) == 0) {
    iVar1 = dialog_compute_layout((DialogOptionList *)this);
    if (iVar1 != 0) {
      return;
    }
    local_30 = dialog_create_window((DialogWindowView *)this);
    dialog_create_controls(this);
  }
  if ((this->style_flags & 0x4000) == 0) {
    rect_set_xywh((iptr)local_14,this->origin_x,this->origin_y,this->wnd_width,this->wnd_height);
    if (this->border_width != 0) {
      for (local_1c = 0; local_1c < (int)this->bevel_width; local_1c++) {
        gfx_draw_bevel_rect(this->surf_wnd,(iptr)local_14,this->bevel_light_color,this->bevel_dark_color);
        rect_deflate((iptr)local_14,1,1);
      }
      dialog_fill_rect_bg((DialogTextView *)this,(iptr)local_14,1);
      rect_deflate((iptr)local_14,this->border_width + this->bevel_width * -2,0);
      local_10 = local_10 + this->title_height + this->bevel_width * -2;
      local_8 -= ((this->chrome_height - this->title_height) + this->bevel_width * -2);
      for (local_1c = 0; local_1c < (int)this->bevel_width; local_1c++) {
        gfx_draw_bevel_rect(this->surf_wnd,(iptr)local_14,this->bevel_dark_color,this->bevel_light_color);
        rect_deflate((iptr)local_14,1,1);
      }
    }
    dialog_fill_rect_bg((DialogTextView *)this,(iptr)local_14,2);
  }
  if ((this->title_text != 0) && ((this->style_flags & 0x10000) == 0)) {
    uVar5 = this->wnd_width;
    iVar1 = font_text_width((GameFont *)this->title_font,this->title_text);
    local_24 = ((int)uVar5 >> 1) - (iVar1 + 4 >> 1);
    local_2c = this->bevel_width + this->pad_y;
    gfx_set_text_color_index(this->title_shadow_color);
    surface_draw_text
              ((DibSurface *)this->surf_wnd,this->title_font,this->title_text,local_24 + 2,
               local_2c + 1,5);
    gfx_set_text_color_index(this->title_color);
    surface_draw_text
              ((DibSurface *)this->surf_wnd,this->title_font,this->title_text,local_24 + 1,local_2c,5)
    ;
    surface_draw_text
              ((DibSurface *)this->surf_wnd,this->title_font,this->title_text,local_24,local_2c,5);
  }
  dialog_draw_wrapped_text((DialogOptionList *)this,1);
  if (this->sprite_count != 0) {
    gfx_set_zoom_scale(this->sprite_zoom);
    local_34 = this->sprite_x;
    local_38 = this->sprite_y;
    for (local_20 = (i32 *)this->sprite_list; local_20 != (i32 *)0x0;
        local_20 = (i32 *)local_20[4]) {
      uVar5 = this->sprite_zoom;
      uVar2 = sprite_width((Sprite *)local_20[3]);
      local_18 = gfx_zoom_scale(uVar2,uVar5);
      uVar5 = this->sprite_zoom;
      uVar2 = sprite_height((Sprite *)local_20[3]);
      local_40 = gfx_zoom_scale(uVar2,uVar5);
      if (this->on_draw_sprite == 0) {
        sprite_draw
                  ((Sprite *)local_20[3],(iptr)local_5c,this->surf_wnd,local_34,local_38);
      }
      else {
        (*(code *)this->on_draw_sprite)
                  (local_20[3],this->surf_wnd,*local_20,local_20[1],local_34,local_38);
      }
      if (((this->style_flags & 0x20000) != 0) && ((i32 *)this->selected_sprite == local_20)) {
        rect_set((iptr)local_14,local_34 - 1,local_38 - 1,local_18 + local_34,
                           local_40 + local_38);
        gfx_draw_rect_frame(this->surf_wnd,(iptr)local_14,this->frame_color);
      }
      iVar1 = local_40;
      if (local_20[2] != 0) {
        local_44 = this->sprite_gap + local_18 + local_34;
        iVar3 = font_line_spacing((GameFont *)this->body_font);
        local_28 = (iVar1 - iVar3 >> 1) + local_38;
        dialog_draw_text_default_font((DialogTextView *)this,local_20[2],local_44,local_28,0);
      }
      local_38 = local_38 + local_40 + this->section_gap;
    }
    gfx_reset_zoom_scale();
  }
  if (this->edit_count != 0) {
    local_3c = this->edit_field_list;
    local_1c = 0;
    for (; local_3c != 0; local_3c = *(uptr *)(local_3c + 0x18)) {
      gfx_set_text_color_index(this->text_color);
      uVar2 = 5;
      iVar1 = dialog_edit_row_height((DialogCore *)this);
      iVar1 = iVar1 * local_1c;
      iVar3 = dialog_edit_row_height((DialogCore *)this);
      uVar5 = this->edit_y;
      iVar4 = font_line_spacing((GameFont *)this->body_font);
      surface_draw_text_cur_font
                ((SurfaceTextCurFontView *)this->surf_wnd,*(i32 *)(local_3c + 0x10),this->edit_x,
                 (iVar1 + (iVar3 >> 1) + uVar5) - (iVar4 >> 1),uVar2);
      local_1c++;
    }
  }
  if ((this->style_flags & 0x41000) == 0x1000) {
    dialog_draw_option_list((DialogOptionList *)this);
  }
  if (local_30 == 0) {
    wnd_blit_surface((DibSurface *)this->surf_wnd);
    if (this->option_count != 0) {
      if ((this->style_flags & 0x1000) == 0) {
        if ((this->style_flags & 4) == 0) {
          radiogrp_show_all((RadioGroupShowView *)this->radio_group);
        }
        else {
          for (local_1c = 0; local_1c < (int)this->option_count; local_1c++) {
            ctrl_show_and_redraw((Control *)(this->checkboxes + local_1c * 0x3c));
          }
        }
      }
      else if ((this->style_flags & 0x40000) == 0) {
        local_48 = this->cur_pane;
        for (local_4c = 0; (int)local_4c < 2; local_4c++) {
          if ((local_4c != 1) || ((this->style_flags & 0x400000) != 0)) {
            this->cur_pane = local_4c;
            if (*(int *)(this->pad_294 + this->cur_pane * 4 - 0x10) != 0) {
              ctrl_show_and_redraw
                        (*(Control **)(this->pad_294 + this->cur_pane * 4 - 0x10));
            }
            if (*(int *)(this->pad_294 + this->cur_pane * 4 - 8) != 0) {
              ctrl_show_and_redraw
                        (*(Control **)(this->pad_294 + this->cur_pane * 4 - 8));
            }
          }
        }
        this->cur_pane = local_48;
      }
    }
    if (this->edit_count != 0) {
      for (local_1c = 0; local_1c < (int)this->edit_count; local_1c++) {
        ctrl_show_and_redraw((Control *)(local_1c * 0x48 + this->edit_controls));
      }
    }
    if (this->std_button_count + this->extra_button_count != 0) {
      for (local_1c = 0; local_1c < (int)(this->std_button_count + this->extra_button_count); local_1c++)
      {
        ctrl_show_and_redraw((Control *)(this->button_controls + local_1c * 0x3c));
      }
    }
    if ((1 < (int)this->sprite_count) && (this->option_count == 0)) {
      for (local_1c = 0; local_1c < (int)this->sprite_count; local_1c++) {
        ctrl_show_and_redraw((Control *)(this->sprite_hotspots + local_1c * 0x40));
      }
    }
  }
  else {
    window_show((WindowObjectView *)this->surf_wnd);
  }
  this->style_flags = this->style_flags | 0x20;
  return;
}
#undef local_5c
#undef local_4c
#undef local_48
#undef local_44
#undef local_40
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
#undef local_8

/* 005a5f34 auto */
#define game_session_active (*(int *)((u8 *)&g.d_006252c4))
#define dialog_timeout_start_i32 (*(i32 *)((u8 *)&g.d_006cec80))
#define local_114 (*(char (*)[132])(frame_ + FRAME_OFF(4)))
#define local_90 (*(char (*)[132])(frame_ + FRAME_OFF(136)))
#define local_c (*(uint * *)(frame_ + FRAME_OFF(268)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(272)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

u32 __thiscall dialog_run_modal(Dialog *this,iptr param_1,iptr param_2)

{
  iptr iVar1;
  BOOL BVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(280)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (dialog_stack_depth != 0x10) {
    if (param_2 == 0) {
      dialog_timeout_start_i32 = timer_ticks();
    }
    else {
      dialog_timeout_start_i32 = timer_ticks();
      dialog_timeout_start_i32 = param_2 * 0x3c - 0x4b0 + dialog_timeout_start_i32;
    }
    if (game_session_active != 0) {
      iVar1 = wnd_get_window((WndBase *)&main_frame_wnd);
      BVar1 = IsIconic(*(HWND *)(iVar1 + 4));
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
          iVar2 = (*(code *)this->on_modal_poll)(this);
          if (iVar2 != 0) {
            dialog_end_current();
          }
        }
      }
      if ((param_1 != 0) && (this->edit_controls != 0)) {
        ctrl_get_text((ControlTextView *)this->edit_controls,param_1);
      }
      if (1 < (int)this->edit_count) {
        for (local_8 = 0; local_8 < (int)this->edit_count; local_8++) {
          ctrl_get_text
                    ((ControlTextView *)(this->edit_controls + local_8 * 0x48),
                     (iptr)(&text_string_args + local_8 * 0x104));
        }
      }
      if ((this->style_flags & 0x1000) == 0) {
        if ((this->style_flags & 4) != 0) {
          local_c = (uint *)this->option_list;
          local_8 = 0;
          for (; local_c != (uint *)0x0; local_c = (uint *)local_c[4]) {
            *local_c = *local_c & 0xfffffffb;
            iVar2 = checkbox_is_checked
                              ((Control *)(this->checkboxes + local_8 * 0x3c));
            if (iVar2 != 0) {
              *local_c = *local_c | 4;
            }
            local_8++;
          }
        }
      }
      else if (this->result_id == 0) {
        if ((this->style_flags & 0x40000) == 0) {
          this->result_id = *(u32 *)(this->selected_option + 4);
        }
        else {
          listbox_get_sel_text
                    (*(ListBoxSelTextView **)(this->pad_264 + this->cur_pane * 4 + 0x14),(iptr)local_90);
          this->result_id = *(u32 *)(this->option_list + 4);
          local_c = (uint *)this->option_list;
          local_8 = 0;
          for (; local_c != (uint *)0x0; local_c = (uint *)local_c[4]) {
            listbox_get_text
                      (*(ListBoxTextView **)(this->pad_264 + this->cur_pane * 4 + 0x14),local_8,
                       (iptr)local_114);
            iVar2 = _strcmp(local_90,local_114);
            if (iVar2 == 0) {
              this->result_id = local_c[1];
            }
            local_8++;
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
#undef local_114
#undef local_90
#undef local_c
#undef local_8

/* 005a632a auto */
#define local_17c (*(i8 (*)[256])(frame_ + FRAME_OFF(4)))
#define local_7c (*(int *)(frame_ + FRAME_OFF(260)))
#define local_78 (*(i32 *)(frame_ + FRAME_OFF(264)))
#define local_74 (*(uint *)(frame_ + FRAME_OFF(268)))
#define local_70 (*(char * *)(frame_ + FRAME_OFF(272)))
#define local_6c (*(i8 (*)[80])(frame_ + FRAME_OFF(276)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(356)))
#define local_18 (*(char * *)(frame_ + FRAME_OFF(360)))
#define local_14 (*(uptr *)(frame_ + FRAME_OFF(364)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(368)))
#define local_c (*(int *)(frame_ + FRAME_OFF(372)))
#define local_8 (*(i8 * *)(frame_ + FRAME_OFF(376)))
i32 __thiscall
dialog_load_text_section
          (Dialog *this,iptr param_1,iptr param_2,int param_3,iptr param_4,iptr param_5,
          iptr param_6,iptr param_7,uint param_8)

{
  int iVar1;
  size_t sVar2;
  u32 uVar3;
  i8 frame_[FRAME_OFF(384)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_78 = 1;
  local_7c = 1;
  local_10 = 0;
  crt_strcpy(&dialog_section_name,param_2);
  iVar1 = text_open_section(param_1,param_2);
  if (iVar1 == 0) {
    if ((param_8 & 0x8000) == 0) {
      dialog_init(this,param_5,param_6,param_7,param_8);
    }
    else {
      this->style_flags = this->style_flags | param_8;
    }
    local_74 = (uint)(param_4 != 0);
    if (local_74 != 0) {
      crt_strcpy(local_6c,param_4);
    }
    do {
      local_70 = (char *)text_read_line(1);
      if (local_70 == (char *)0x0) {
        local_7c = 3;
      }
      else {
        sVar2 = _strlen(local_70);
        if (sVar2 == 0) {
          if ((param_8 & 0x4000000) == 0) {
            local_7c++;
          }
          else {
            dialog_add_line
                      ((DialogAddLineView *)this,ADDR(0x635b70, ((u8 *)&g.d_00635b70)),0xffffffff,0xffffffff,0xffffffff,0);
          }
        }
        else if (*local_70 == '@') {
          local_18 = local_70 + 1;
          iVar1 = __strcmpi(local_18,s_OPTIONS_00635b74);
          if ((iVar1 == 0) || (iVar1 = _strcmp(local_18,s_PROMPT_00635b7c), iVar1 == 0)) {
            local_7c = 2;
          }
          else {
            iVar1 = __strcmpi(local_18,&dlg_key_text_str);
            if (iVar1 == 0) {
              local_7c = 1;
            }
            else {
              iVar1 = __strnicmp(local_18,s_TITLE_00635b8c,5);
              if (iVar1 == 0) {
                for (; (*local_18 != '\0' && (*local_18 != '=')); local_18++) {
                }
                if (*local_18 != '\0') {
                  local_18++;
                }
                text_expand_vars((iptr)local_18,(iptr)local_17c);
                dialog_set_title((DialogWindowView *)this,(iptr)local_17c);
              }
              else {
                iVar1 = __strnicmp(local_18,s_BUTTON_00635b94,6);
                if (iVar1 == 0) {
                  for (; (*local_18 != '\0' && (*local_18 != '=')); local_18++) {
                  }
                  if (*local_18 != '\0') {
                    local_18++;
                  }
                  text_expand_vars((iptr)local_18,(iptr)local_17c);
                  dialog_add_button((DialogButtonsView *)this,(iptr)local_17c);
                }
                else {
                  iVar1 = __strnicmp(local_18,s_COLUMNS_00635b9c,7);
                  if (iVar1 == 0) {
                    while ((*local_18 != '\0' && (iVar1 = _isdigit((int)*local_18), iVar1 == 0))) {
                      local_18++;
                    }
                    local_c = _atoi(local_18);
                    dialog_set_columns((DialogButtonsView *)this,local_c);
                  }
                  else {
                    iVar1 = __strnicmp(local_18,s_HEIGHT_00635ba4,6);
                    if (iVar1 == 0) {
                      while ((*local_18 != '\0' && (iVar1 = _isdigit((int)*local_18), iVar1 == 0)))
                      {
                        local_18++;
                      }
                      local_c = _atoi(local_18);
                      dialog_set_height((DialogCore *)this,local_c);
                    }
                    else {
                      iVar1 = __strcmpi(local_18,s_SMALLFONT_00635bac);
                      if (iVar1 != 0) {
                        iVar1 = __strnicmp(local_18,&dlg_key_y_prefix,1);
                        if ((iVar1 == 0) && (iVar1 = _isalpha((int)local_18[1]), iVar1 == 0)) {
                          while (((*local_18 != '\0' &&
                                  (iVar1 = _isdigit((int)*local_18), iVar1 == 0)) &&
                                 (*local_18 != '-'))) {
                            local_18++;
                          }
                          uVar3 = _atoi(local_18);
                          this->req_y = uVar3;
                        }
                        else {
                          iVar1 = __strnicmp(local_18,&dlg_key_x_prefix,1);
                          if ((iVar1 == 0) && (iVar1 = _isalpha((int)local_18[1]), iVar1 == 0)) {
                            while (((*local_18 != '\0' &&
                                    (iVar1 = _isdigit((int)*local_18), iVar1 == 0)) &&
                                   (*local_18 != '-'))) {
                              local_18++;
                            }
                            uVar3 = _atoi(local_18);
                            this->req_x = uVar3;
                          }
                          else {
                            iVar1 = __strnicmp(local_18,s_WIDTH_00635bc0,5);
                            if (iVar1 == 0) {
                              while ((*local_18 != '\0' &&
                                     (iVar1 = _isdigit((int)*local_18), iVar1 == 0))) {
                                local_18++;
                              }
                              local_c = _atoi(local_18);
                              dialog_set_width((DialogWindowView *)this,local_c);
                            }
                            else {
                              iVar1 = __strnicmp(local_18,s_LENGTH_00635bc8,6);
                              if (iVar1 == 0) {
                                while ((*local_18 != '\0' &&
                                       (iVar1 = _isdigit((int)*local_18), iVar1 == 0))) {
                                  local_18++;
                                }
                                if (param_3 == 0) {
                                  param_3 = _atoi(local_18);
                                }
                              }
                              else {
                                iVar1 = __strnicmp(local_18,s_CHECKBOX_00635bd0,7);
                                if (iVar1 == 0) {
                                  this->style_flags = this->style_flags | 5;
                                }
                                else {
                                  iVar1 = __strnicmp(local_18,s_LISTBOX_00635bdc,7);
                                  if (iVar1 == 0) {
                                    while ((*local_18 != '\0' &&
                                           (iVar1 = _isdigit((int)*local_18), iVar1 == 0))) {
                                      local_18++;
                                    }
                                    local_1c = _atoi(local_18);
                                    if (local_1c == 0) {
                                      local_1c = 0x10;
                                    }
                                    dialog_set_listbox
                                              ((DialogTextView *)this,local_1c,this->content_width,0);
                                  }
                                  else {
                                    iVar1 = __strnicmp(local_18,s_SYSTEM_00635be4,6);
                                    if (iVar1 == 0) {
                                      this->style_flags = this->style_flags | 0x40000;
                                    }
                                    else {
                                      iVar1 = __strnicmp(local_18,s_DEFAULT_00635bec,7);
                                      if (iVar1 == 0) {
                                        if (local_74 == 0) {
                                          while ((*local_18 != '\0' &&
                                                 (iVar1 = _isdigit((int)*local_18), iVar1 == 0))) {
                                            local_18++;
                                          }
                                          if (param_3 == 0) {
                                            param_3 = _atoi(local_18);
                                          }
                                        }
                                        else {
                                          for (; (*local_18 != '\0' && (*local_18 != '='));
                                              local_18 = local_18 + 1) {
                                          }
                                          if (*local_18 != '\0') {
                                            local_18++;
                                          }
                                          sVar2 = _strlen((char *)param_4);
                                          if (sVar2 == 0) {
                                            crt_strcpy(local_6c,local_18);
                                          }
                                        }
                                      }
                                      else if (*local_18 != '@') {
                                        local_7c = 3;
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
        else if (local_7c == 1) {
          text_expand_vars((iptr)local_70,(iptr)local_17c);
          dialog_add_line
                    ((DialogAddLineView *)this,(iptr)local_17c,0xffffffff,0xffffffff,0xffffffff,0);
        }
        else if (local_7c == 2) {
          text_expand_vars((iptr)local_70,(iptr)local_17c);
          if (local_74 == 0) {
            if ((this->style_flags & 4) == 0) {
              local_14 = dialog_add_option
                                   ((DialogOptionList *)this,(iptr)local_17c,local_10,0);
            }
            else {
              local_14 = dialog_add_checkbox_option
                                   ((DialogOptionList *)this,(iptr)local_17c,local_10,0);
            }
            if (param_3 == local_10) {
              this->selected_option = local_14;
            }
            local_10++;
          }
          else {
            if (param_3 == 0) {
              param_3 = 5;
            }
            local_8 = local_6c;
            if (this->edit_count != 0) {
              local_8 = &text_string_args + this->edit_count * 0x104;
            }
            dialog_add_edit_field
                      ((DialogOptionList *)this,(iptr)local_17c,(iptr)local_8,param_3);
          }
        }
      }
    } while (local_7c < 3);
    local_78 = 0;
  }
  else if ((param_8 & 0x8000) == 0) {
    dialog_init(this,param_5,param_6,param_7,param_8);
  }
  return local_78;
}
#undef local_17c
#undef local_7c
#undef local_78
#undef local_74
#undef local_70
#undef local_6c
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 005a6c23 auto */
#define dlg_parent_window (*(iptr *)((u8 *)&g.d_006359c4))
void __cdecl dlg_push_parent_window(iptr param_1)

{
  dlg_saved_parent_window = dlg_parent_window;
  dlg_parent_window = param_1;
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

Hotspot * __thiscall hotspot_vector_dtor(Hotspot *this,uint param_1)

{
  if ((param_1 & 2) == 0) {
    hotspot_dtor(this);
    if ((param_1 & 1) != 0) {
      operator_delete(this);
    }
  }
  else {
    crt_vector_dtor_iterator(this,0x40,this[-1].field_1c,hotspot_dtor);
    operator_delete(&this[-1].field_1c);
  }
  return this;
}

/* 005a95b0 auto */
SurfaceWindow * __thiscall surfwnd_scalar_dtor(SurfaceWindow *this,uint param_1)

{
  surfwnd_dtor(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 005a9600 auto */
void __thiscall wnd_get_screen_rect(WndBase *this,iptr param_1)

{
  wnd_obj_get_screen_rect(this->native_wnd,param_1);
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
          (DialogTextView *this,i32 param_1,i32 param_2,i32 param_3,
          i32 param_4)

{
  dialog_draw_text_shadowed(this,this->body_font,param_1,param_2,param_3,param_4);
  return;
}

/* 005bb4ae auto */
void __thiscall
wnd_create_with_surface
          (DibSurface *this,iptr param_1,i32 param_2,i32 param_3,i32 param_4
          ,i32 param_5,i32 param_6,iptr param_7,iptr param_8)

{
  iptr iVar1;
  
  wnd_create_framed_child
            ((WndBase *)(this + 1),param_1,param_2,param_3,param_4,param_5,param_6,param_7,
             param_8);
  surface_create(this,param_5,param_6);
  surface_set_palette(this,param_7);
  iVar1 = wnd_get_window((WndBase *)(this + 1));
  wnd_install_paint_proc((iptr)this,iVar1);
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
    wnd_active_child = this->pad_48;
  }
  wnd_call_paint_cb(this);
  wnd_blit_surface((DibSurface *)this);
  return;
}
#undef wnd_active_child

/* 005bb5be auto */
bool __thiscall surfwnd_resize_dib(DibSurface *this,iptr param_1)

{
  int iVar1;
  i32 uVar2;
  i32 uVar3;
  
  iVar1 = surface_alloc_dib_by_bpp(this,param_1);
  if (iVar1 == 1) {
    uVar2 = rect_height(param_1);
    uVar3 = rect_width(param_1);
    wnd_set_client_size((WndClientSizeView *)(this + 1),uVar3,uVar2);
  }
  return iVar1 == 1;
}

/* 005bb621 auto */
#define wnd_active_child (*(u8 * *)((u8 *)&g.d_00637ea4))
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(4)))
void __thiscall surfwnd_on_resize(SurfaceWindow *this,int param_1,int param_2)

{
  int iVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = surface_get_width((DibSurface *)this);
  if ((iVar1 == param_1) &&
     (iVar1 = surface_get_height((DibSurface *)this), iVar1 == param_2)) {
    return;
  }
  SetRect(&local_14,0,0,param_1,param_2);
  (*((code **)(this->vtable))[0])(this,&local_14);
  uVar2 = wnd_get_palette_obj((WndPaletteObjView *)this->pad_48);
  surface_apply_palette((DibSurface *)this,uVar2);
  if (this == (SurfaceWindow *)0x0) {
    wnd_active_child = (u8 *)0x0;
  }
  else {
    wnd_active_child = this->pad_48;
  }
  wnd_call_paint_cb(this);
  wnd_blit_surface((DibSurface *)this);
  return;
}
#undef wnd_active_child
#undef local_14

/* 005bb6c7 auto */
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
void __thiscall wnd_resize_clamped(WindowObjectView *this,int param_1,int param_2)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  wnd_get_min_size((WndMinSizeView *)(this + 0x12),(iptr)&local_10,(iptr)&local_14);
  wnd_get_max_size((WndMaxSizeView *)(this + 0x12),(iptr)&local_8,(iptr)&local_c);
  if (param_1 < local_10) {
    param_1 = local_10;
  }
  if (local_8 < param_1) {
    param_1 = local_8;
  }
  if (param_2 < local_14) {
    param_2 = local_14;
  }
  if (local_c < param_2) {
    param_2 = local_c;
  }
  wnd_set_client_size((WndClientSizeView *)(this + 0x12),param_1,param_2);
  return;
}
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 005bb8c0 auto */
u32 __thiscall wnd_get_palette_obj(WndPaletteObjView *this)

{
  return this->palette_obj;
}

/* 005bb8e0 auto */
void __thiscall wnd_set_client_size(WndClientSizeView *this,i32 param_1,i32 param_2)

{
  wnd_obj_set_client_size(this->native_wnd,param_1,param_2);
  return;
}

/* 005bb910 auto */
void __thiscall wnd_get_min_size(WndMinSizeView *this,iptr param_1,iptr param_2)

{
  *(u32 *)param_1 = this->min_width;
  *(u32 *)param_2 = this->min_height;
  return;
}

/* 005bb950 auto */
void __thiscall wnd_get_max_size(WndMaxSizeView *this,iptr param_1,iptr param_2)

{
  *(u32 *)param_1 = this->max_width;
  *(u32 *)param_2 = this->max_height;
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
#define local_34 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_24 (*(HWND *)(frame_ + FRAME_OFF(20)))
#define local_20 (*(DWORD *)(frame_ + FRAME_OFF(24)))
#define local_18 (*(uint *)(frame_ + FRAME_OFF(32)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(36)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_c (*(int *)(frame_ + FRAME_OFF(44)))
i32 * __cdecl
wnd_obj_create(LPCSTR param_1,uint param_2,int param_3,int param_4,int param_5,int param_6,
            iptr param_7)

{
  i32 uVar1;
  i32 *puVar2;
  int iVar3;
  HWND pHVar4;
  HDC pHVar5;
  HCURSOR pHVar6;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_20 = 0;
  uVar1 = mem_handle_alloc(0x4c);
  puVar2 = (i32 *)mem_handle_lock(uVar1);
  *puVar2 = uVar1;
  local_c = 0;
  local_10 = 0;
  local_14 = GetSystemMetrics(4);
  local_18 = 0x2000000;
  if ((param_2 & 4) == 0) {
    if (((param_2 & 2) == 0) || ((param_2 & 0x40) != 0)) {
      if (((param_2 & 2) == 0) || ((param_2 & 0x40) == 0)) {
        if ((param_2 & 1) != 0) {
          local_18 = 0x2800000;
          local_c = GetSystemMetrics(7);
          local_c = local_c * 2;
          local_10 = GetSystemMetrics(8);
          local_10 = local_10 * 2;
          local_14++;
        }
      }
      else {
        local_18 = 0x2800000;
        local_c = GetSystemMetrics(7);
        local_c = local_c * 2;
        local_10 = GetSystemMetrics(8);
        local_10 = local_10 * 2;
      }
    }
    else {
      local_18 = 0x2400000;
      local_c = GetSystemMetrics(7);
      local_c = local_c * 2;
      local_10 = GetSystemMetrics(8);
      local_10 = local_10 * 2;
    }
  }
  else {
    local_18 = 0x2040000;
    local_c = GetSystemMetrics(0x20);
    local_c = local_c * 2;
    local_10 = GetSystemMetrics(0x21);
    local_10 = local_10 * 2;
  }
  if ((param_2 & 8) != 0) {
    local_18 = local_18 | 0x20000;
    param_2 = param_2 | 0x40;
  }
  if ((param_2 & 0x10) != 0) {
    local_18 = local_18 | 0x10000;
    param_2 = param_2 | 0x40;
  }
  if ((param_2 & 0x20) != 0) {
    local_18 = local_18 | 0x80000;
    param_2 = param_2 | 0x40;
  }
  if ((param_2 & 0x40) == 0) {
    local_14 = 0;
  }
  else {
    local_18 = local_18 | 0xc00000;
  }
  if ((param_2 & 0x80) != 0) {
    local_18 = local_18 | 0x200000;
    iVar3 = GetSystemMetrics(2);
    local_c = local_c + iVar3 - 1;
  }
  if ((param_2 & 0x100) != 0) {
    local_18 = local_18 | 0x100000;
    iVar3 = GetSystemMetrics(3);
    local_10 = local_10 + iVar3 - 1;
  }
  if (((param_2 & 0x200) != 0) && (param_7 != 0)) {
    local_18 = local_18 | 0x44000000;
    local_20 = 4;
  }
  if ((param_2 & 0x800) != 0) {
    local_18 = local_18 & 0xbfffffff | 0x80000000;
  }
  if ((param_2 & 0x400) == 0) {
    puVar2[0xc] = 0;
  }
  else {
    puVar2[0xc] = 1;
  }
  if ((param_2 & 0x1000) == 0) {
    puVar2[0xd] = 0;
  }
  else {
    puVar2[0xd] = 1;
  }
  if (param_7 == 0) {
    local_24 = (HWND)0x0;
  }
  else {
    local_24 = *(HWND *)(param_7 + 4);
  }
  if (param_6 == -1) {
    local_28 = -0x80000000;
  }
  else {
    local_28 = local_10 + local_14 + param_6 - 1;
  }
  if (param_5 == -1) {
    local_2c = -0x80000000;
  }
  else {
    local_2c = local_c + param_5;
  }
  if (param_4 == -1) {
    local_30 = -0x80000000;
  }
  else {
    local_30 = param_4;
  }
  if (param_3 == -1) {
    local_34 = -0x80000000;
  }
  else {
    local_34 = param_3;
  }
  pHVar4 = CreateWindowExA(local_20,s_MSWindowClass_006366d0,param_1,local_18,local_34,local_30,
                           local_2c,local_28,local_24,(HMENU)0x0,app_hinstance,(LPVOID)0x0);
  puVar2[1] = pHVar4;
  wnd_list_add_hwnd(puVar2[1]);
  pHVar5 = GetDC((HWND)puVar2[1]);
  puVar2[2] = pHVar5;
  pHVar6 = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
  puVar2[7] = pHVar6;
  puVar2[6] = 0;
  puVar2[8] = 0;
  puVar2[0x11] = 0;
  puVar2[5] = 0;
  puVar2[3] = 0;
  puVar2[9] = 0;
  puVar2[10] = 0;
  puVar2[0xb] = 0;
  puVar2[0x12] = param_2;
  puVar2[0xe] = 0;
  puVar2[0xf] = 0;
  puVar2[4] = 0;
  puVar2[0x10] = 8;
  return puVar2;
}
#undef app_hinstance
#undef local_34
#undef local_30
#undef local_2c
#undef local_28
#undef local_24
#undef local_20
#undef local_18
#undef local_14
#undef local_10
#undef local_c

/* 005bbfee auto */
void __cdecl wnd_obj_enable(iptr param_1,BOOL param_2)

{
  if (param_1 != 0) {
    EnableWindow(*(HWND *)(param_1 + 4),param_2);
  }
  return;
}

/* 005bc0ab auto */
i32 __cdecl wnd_obj_destroy(i32 *param_1)

{
  i32 uVar1;
  
  if (param_1 != (i32 *)0x0) {
    wnd_stack_remove(param_1[1]);
    if (param_1[0x11] == 0) {
      if (param_1[1] != 0) {
        SetWindowLongA((HWND)param_1[1],4,0);
        ShowWindow((HWND)param_1[1],0);
        SetMenu((HWND)param_1[1],(HMENU)0x0);
        DestroyWindow((HWND)param_1[1]);
      }
      param_1[1] = 0;
    }
    if (param_1[5] != 0) {
      DeleteObject((HGDIOBJ)param_1[5]);
    }
    uVar1 = *param_1;
    mem_handle_unlock(uVar1);
    mem_handle_free(uVar1);
  }
  return 0;
}

/* 005bc173 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl wnd_stack_check_leaks_nop(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (ms_window_stack_count != 0) {
    for (local_8 = 0; local_8 < ms_window_stack_count; local_8++) {
    }
  }
  return;
}
#undef local_8

/* 005bc1b5 auto */
void __cdecl wnd_list_add_hwnd(i32 param_1)

{
  *(i32 *)(&ms_window_stack + ms_window_stack_count * 4) = param_1;
  ms_window_stack_count++;
  return;
}

/* 005bc1db auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl wnd_stack_remove(int param_1)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; (local_8 < ms_window_stack_count && (*(int *)(&ms_window_stack + local_8 * 4) != param_1));
      local_8 = local_8 + 1) {
  }
  if (local_8 < ms_window_stack_count - 1) {
    for (; local_8 < ms_window_stack_count - 1; local_8++) {
      *(i32 *)(&ms_window_stack + local_8 * 4) = *(i32 *)(&ms_window_stack_elem1 + local_8 * 4);
    }
  }
  ms_window_stack_count--;
  if (ms_window_stack_count < 0) {
    dbg_log(ADDR(0x6366e0, ((u8 *)&g.d_006366e0)));
  }
  return;
}
#undef local_8

/* 005bc280 auto */
#define local_14 (*(i8 (*)[4])(frame_ + FRAME_OFF(4)))
#define local_10 (*(WndPaletteView * *)(frame_ + FRAME_OFF(8)))
#define local_c (*(i8 (*)[4])(frame_ + FRAME_OFF(12)))
#define local_8 (*(i8 (*)[4])(frame_ + FRAME_OFF(16)))
void __cdecl wnd_obj_set_bg_color(iptr param_1,uint param_2)

{
  HBRUSH pHVar1;
  GamePalette *this;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (*(int *)(param_1 + 0x14) != 0) {
    DeleteObject(*(HGDIOBJ *)(param_1 + 0x14));
  }
  if (gfx_palettized_display == 0) {
    local_10 = (WndPaletteView *)GetWindowLongA(*(HWND *)(param_1 + 4),0);
    this = (GamePalette *)wnd_get_palette(local_10);
    palette_get_entry
              (this,param_2 & 0xff,(iptr)local_c,(iptr)local_14,(iptr)local_8);
    pHVar1 = CreateSolidBrush((uint)CONCAT12(local_8[0],CONCAT11(local_14[0],local_c[0])));
    *(HBRUSH *)(param_1 + 0x14) = pHVar1;
  }
  else {
    if (*(int *)(param_1 + 0x18) != 0) {
      RealizePalette(*(HDC *)(param_1 + 8));
    }
    pHVar1 = CreateSolidBrush(param_2 & 0xff | 0x1000000);
    *(HBRUSH *)(param_1 + 0x14) = pHVar1;
  }
  InvalidateRect(*(HWND *)(param_1 + 4),(RECT *)0x0,0);
  return;
}
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 005bc3bf auto */
void __cdecl wnd_obj_set_bg_tile(iptr param_1,i32 param_2)

{
  *(i32 *)(param_1 + 0x24) = param_2;
  return;
}

/* 005bc3f1 auto */
void __cdecl wnd_obj_set_bg_surface(iptr param_1,i32 param_2)

{
  *(i32 *)(param_1 + 0x2c) = param_2;
  return;
}

/* 005bc40a auto */
void __cdecl wnd_obj_show_raise(iptr param_1)

{
  if (param_1 != 0) {
    ShowWindow(*(HWND *)(param_1 + 4),5);
    if ((*(byte *)(param_1 + 0x49) & 2) != 0) {
      BringWindowToTop(*(HWND *)(param_1 + 4));
    }
  }
  return;
}

/* 005bc44d auto */
void __cdecl wnd_obj_hide(iptr param_1)

{
  if (param_1 != 0) {
    ShowWindow(*(HWND *)(param_1 + 4),0);
  }
  return;
}

/* 005bc4a1 auto */
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(4)))
void __cdecl wnd_obj_move_xy(iptr param_1,int param_2,int param_3)

{
  int nHeight;
  int nWidth;
  BOOL bRepaint;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 != 0) {
    GetWindowRect(*(HWND *)(param_1 + 4),&local_14);
    bRepaint = 1;
    nHeight = rect_height((iptr)&local_14);
    nWidth = rect_width((iptr)&local_14);
    MoveWindow(*(HWND *)(param_1 + 4),param_2,param_3,nWidth,nHeight,bRepaint);
  }
  return;
}
#undef local_14

/* 005bc505 auto */
#define local_20 (*(tagPOINT *)(frame_ + FRAME_OFF(0)))
#define local_18 (*(HWND *)(frame_ + FRAME_OFF(8)))
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(12)))
void __cdecl wnd_obj_set_client_size(iptr param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 != 0) {
    GetWindowRect(*(HWND *)(param_1 + 4),&local_14);
    iVar1 = wnd_obj_frame_width(param_1);
    iVar2 = wnd_obj_frame_height(param_1);
    local_18 = GetParent(*(HWND *)(param_1 + 4));
    if ((local_18 != (HWND)0x0) && ((*(byte *)(param_1 + 0x49) & 2) != 0)) {
      local_20.x = 0;
      local_20.y = 0;
      MapWindowPoints(local_18,(HWND)0x0,&local_20,1);
      local_14.left -= local_20.x;
      local_14.top -= local_20.y;
    }
    MoveWindow(*(HWND *)(param_1 + 4),local_14.left,local_14.top,param_2 + iVar1,param_3 + iVar2,1);
  }
  return;
}
#undef local_20
#undef local_18
#undef local_14

/* 005bc5da auto */
void __cdecl wnd_obj_maximize(iptr param_1)

{
  if (param_1 != 0) {
    ShowWindow(*(HWND *)(param_1 + 4),3);
  }
  return;
}

/* 005bc636 auto */
void __cdecl wnd_obj_minimize(iptr param_1)

{
  if (param_1 != 0) {
    ShowWindow(*(HWND *)(param_1 + 4),6);
  }
  return;
}

/* 005bc692 auto */
void __cdecl wnd_obj_show_restored(iptr param_1)

{
  if (param_1 != 0) {
    ShowWindow(*(HWND *)(param_1 + 4),9);
  }
  return;
}

/* 005bc6bb auto */
void __cdecl wnd_obj_validate_rect(iptr param_1,RECT *param_2)

{
  if (param_1 != 0) {
    ValidateRect(*(HWND *)(param_1 + 4),param_2);
  }
  return;
}

/* 005bc713 auto */
void __cdecl wnd_obj_move_to_rect(iptr param_1,int *param_2)

{
  int nHeight;
  int nWidth;
  BOOL bRepaint;
  
  if (param_1 != 0) {
    bRepaint = 1;
    nHeight = rect_height((iptr)param_2);
    nWidth = rect_width((iptr)param_2);
    MoveWindow(*(HWND *)(param_1 + 4),*param_2,param_2[1],nWidth,nHeight,bRepaint);
  }
  return;
}

/* 005bc763 auto */
#define local_34 (*(tagRECT *)(frame_ + FRAME_OFF(4)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(20)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_1c (*(tagPOINT *)(frame_ + FRAME_OFF(28)))
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(36)))
void __cdecl wnd_obj_center(iptr param_1,int param_2,int param_3)

{
  HWND hWnd;
  int iVar1;
  int iVar2;
  int iVar3;
  BOOL bRepaint;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 != 0) {
    GetWindowRect(*(HWND *)(param_1 + 4),&local_34);
    hWnd = GetParent(*(HWND *)(param_1 + 4));
    if (hWnd == (HWND)0x0) {
      iVar1 = GetSystemMetrics(0);
      iVar2 = GetSystemMetrics(1);
      iVar3 = rect_width((iptr)&local_34);
      local_20 = iVar1 - iVar3 >> 1;
      iVar1 = rect_height((iptr)&local_34);
      local_24 = iVar2 - iVar1 >> 1;
    }
    else if ((*(byte *)(param_1 + 0x49) & 2) == 0) {
      GetWindowRect(hWnd,&local_14);
      iVar1 = rect_width((iptr)&local_14);
      iVar2 = rect_height((iptr)&local_14);
      iVar3 = rect_width((iptr)&local_34);
      local_20 = iVar1 - iVar3 >> 1;
      iVar1 = rect_height((iptr)&local_34);
      local_24 = iVar2 - iVar1 >> 1;
      local_1c.x = 0;
      local_1c.y = 0;
      MapWindowPoints(hWnd,(HWND)0x0,&local_1c,1);
      local_20 += local_14.left;
      local_24 += local_14.top;
    }
    else {
      GetClientRect(hWnd,&local_14);
      iVar1 = rect_width((iptr)&local_14);
      iVar2 = rect_height((iptr)&local_14);
      iVar3 = rect_width((iptr)&local_34);
      local_20 = iVar1 - iVar3 >> 1;
      iVar1 = rect_height((iptr)&local_34);
      local_24 = iVar2 - iVar1 >> 1;
      if (local_24 < 0) {
        local_24 = 0;
      }
    }
    bRepaint = 1;
    iVar1 = rect_height((iptr)&local_34);
    iVar2 = rect_width((iptr)&local_34);
    MoveWindow(*(HWND *)(param_1 + 4),local_20 + param_2,local_24 + param_3,iVar2,iVar1,bRepaint);
  }
  return;
}
#undef local_34
#undef local_24
#undef local_20
#undef local_1c
#undef local_14

/* 005bc933 auto */
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(4)))
LONG __cdecl wnd_obj_client_width(iptr param_1)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 == 0) {
    local_14.right = 0;
  }
  else {
    GetClientRect(*(HWND *)(param_1 + 4),&local_14);
  }
  return local_14.right;
}
#undef local_14

/* 005bc96b auto */
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(4)))
LONG __cdecl wnd_obj_client_height(iptr param_1)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 == 0) {
    local_14.bottom = 0;
  }
  else {
    GetClientRect(*(HWND *)(param_1 + 4),&local_14);
  }
  return local_14.bottom;
}
#undef local_14

/* 005bc9a3 auto */
void __cdecl wnd_obj_get_screen_rect(iptr param_1,LPRECT param_2)

{
  if (param_1 != 0) {
    GetWindowRect(*(HWND *)(param_1 + 4),param_2);
  }
  return;
}

/* 005bc9d3 auto */
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(4)))
int __cdecl wnd_obj_frame_width(iptr param_1)

{
  int iVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 == 0) {
    iVar1 = 0;
  }
  else {
    GetWindowRect(*(HWND *)(param_1 + 4),&local_14);
    iVar1 = rect_width((iptr)&local_14);
    GetClientRect(*(HWND *)(param_1 + 4),&local_14);
    iVar2 = rect_width((iptr)&local_14);
    iVar1 -= iVar2;
  }
  return iVar1;
}
#undef local_14

/* 005bca3d auto */
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(4)))
int __cdecl wnd_obj_frame_height(iptr param_1)

{
  int iVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 == 0) {
    iVar1 = 0;
  }
  else {
    GetWindowRect(*(HWND *)(param_1 + 4),&local_14);
    iVar1 = rect_height((iptr)&local_14);
    GetClientRect(*(HWND *)(param_1 + 4),&local_14);
    iVar2 = rect_height((iptr)&local_14);
    iVar1 -= iVar2;
  }
  return iVar1;
}
#undef local_14

/* 005bcb85 auto */
#define local_14 (*(tagPOINT *)(frame_ + FRAME_OFF(4)))
#define local_c (*(LONG *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(LONG *)(frame_ + FRAME_OFF(16)))
void __cdecl wnd_obj_get_rect_in_parent(iptr param_1,LPRECT param_2)

{
  HWND hWndTo;
  tagPOINT *lpPoints;
  UINT cPoints;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 != 0) {
    GetWindowRect(*(HWND *)(param_1 + 4),param_2);
    local_14.x = param_2->left;
    local_14.y = param_2->top;
    local_c = param_2->right;
    local_8 = param_2->bottom;
    cPoints = 2;
    lpPoints = &local_14;
    hWndTo = GetParent(*(HWND *)(param_1 + 4));
    MapWindowPoints((HWND)0x0,hWndTo,lpPoints,cPoints);
    SetRect(param_2,local_14.x,local_14.y,local_c,local_8);
  }
  return;
}
#undef local_14
#undef local_c
#undef local_8

/* 005bcdc3 auto */
void __cdecl wnd_obj_select_palette(iptr param_1,HPALETTE param_2)

{
  if (gfx_palettized_display == 1) {
    *(HPALETTE *)(param_1 + 0x18) = param_2;
    SelectPalette(*(HDC *)(param_1 + 8),param_2,0);
  }
  return;
}

/* 005bcdfc auto */
void __cdecl wnd_obj_attach_menu(iptr param_1,HMENU param_2)

{
  int iVar1;
  int iVar2;
  i32 uVar3;
  
  if (param_1 != 0) {
    SetMenu(*(HWND *)(param_1 + 4),param_2);
    iVar1 = wnd_obj_client_height(param_1);
    iVar2 = GetSystemMetrics(0xf);
    iVar1 = iVar1 + iVar2 + 1;
    uVar3 = wnd_obj_client_width(param_1);
    wnd_obj_set_client_size(param_1,uVar3,iVar1);
  }
  return;
}

/* 005bce5f auto */
#define app_hinstance (*(HINSTANCE *)((u8 *)&g.d_006e4ff0))
void __cdecl wnd_obj_set_icon(iptr param_1,uint param_2)

{
  HICON pHVar1;
  BOOL BVar2;
  
  if (param_1 != 0) {
    if (*(int *)(param_1 + 0x20) != 0) {
      DestroyIcon(*(HICON *)(param_1 + 0x20));
    }
    pHVar1 = LoadIconA(app_hinstance,(LPCSTR)(param_2 & 0xffff));
    *(HICON *)(param_1 + 0x20) = pHVar1;
    BVar2 = IsWindow(*(HWND *)(param_1 + 4));
    if ((BVar2 != 0) && (BVar2 = IsIconic(*(HWND *)(param_1 + 4)), BVar2 != 0)) {
      InvalidateRect(*(HWND *)(param_1 + 4),(RECT *)0x0,0);
    }
  }
  return;
}
#undef app_hinstance

/* 005bcfdd auto */
void __cdecl wnd_obj_set_cursor_now(iptr param_1,i32 param_2,int param_3)

{
  if ((param_1 != 0) && (wnd_obj_set_cursor(param_1,param_2), param_3 != 0)) {
    SetCursor(*(HCURSOR *)(param_1 + 0x1c));
  }
  return;
}

/* 005bd05f auto */
#define app_hinstance (*(HINSTANCE *)((u8 *)&g.d_006e4ff0))
void __cdecl wnd_obj_set_cursor(iptr param_1,uint param_2)

{
  HCURSOR pHVar1;
  
  if (param_1 != 0) {
    if ((int)param_2 < 0) {
      if (param_2 == 0xffffffff) {
        pHVar1 = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
        *(HCURSOR *)(param_1 + 0x1c) = pHVar1;
      }
      else if (param_2 == 0xfffffffe) {
        pHVar1 = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f02);
        *(HCURSOR *)(param_1 + 0x1c) = pHVar1;
      }
    }
    else {
      pHVar1 = LoadCursorA(app_hinstance,(LPCSTR)(param_2 & 0xffff));
      *(HCURSOR *)(param_1 + 0x1c) = pHVar1;
    }
  }
  return;
}
#undef app_hinstance

/* 005bd0e7 auto */
void __cdecl wnd_obj_focus_and_raise(iptr param_1)

{
  if (param_1 != 0) {
    SetFocus(*(HWND *)(param_1 + 4));
    BringWindowToTop(*(HWND *)(param_1 + 4));
  }
  return;
}

/* 005bd120 auto */
void __cdecl wnd_obj_set_focus(iptr param_1)

{
  if (param_1 != 0) {
    SetFocus(*(HWND *)(param_1 + 4));
  }
  return;
}

/* 005bd14c auto */
void __cdecl wnd_obj_disable_owner(iptr param_1,iptr param_2)

{
  HWND pHVar1;
  BOOL BVar2;
  
  if ((param_2 == 0) && (param_1 != 0)) {
    pHVar1 = GetParent(*(HWND *)(param_1 + 4));
    BVar2 = IsWindow(pHVar1);
    if (BVar2 != 0) {
      BVar2 = 0;
      pHVar1 = GetParent(*(HWND *)(param_1 + 4));
      EnableWindow(pHVar1,BVar2);
    }
  }
  else if (param_2 != 0) {
    EnableWindow(*(HWND *)(param_2 + 4),0);
  }
  return;
}

/* 005bd1c5 auto */
void __cdecl wnd_obj_enable_owner(iptr param_1,iptr param_2)

{
  HWND pHVar1;
  BOOL BVar2;
  
  if ((param_2 == 0) && (param_1 != 0)) {
    pHVar1 = GetParent(*(HWND *)(param_1 + 4));
    BVar2 = IsWindow(pHVar1);
    if (BVar2 != 0) {
      BVar2 = 1;
      pHVar1 = GetParent(*(HWND *)(param_1 + 4));
      EnableWindow(pHVar1,BVar2);
    }
  }
  else if (param_2 != 0) {
    EnableWindow(*(HWND *)(param_2 + 4),1);
  }
  return;
}

/* 005bd248 auto */
void __cdecl wnd_obj_set_caption_height(iptr param_1,i32 param_2)

{
  if (param_1 != 0) {
    *(i32 *)(param_1 + 0x38) = param_2;
  }
  return;
}

/* 005bd270 auto */
void __cdecl wnd_obj_set_resize_border(iptr param_1,i32 param_2)

{
  if (param_1 != 0) {
    *(i32 *)(param_1 + 0x3c) = param_2;
  }
  return;
}

/* 005bd48f auto */
#define local_c (*(tagPOINT *)(frame_ + FRAME_OFF(4)))
void __cdecl wnd_obj_get_cursor_pos(iptr param_1,LONG *param_2,LONG *param_3)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  GetCursorPos(&local_c);
  ScreenToClient(*(HWND *)(param_1 + 4),&local_c);
  *param_2 = local_c.x;
  *param_3 = local_c.y;
  return;
}
#undef local_c

/* 005bd533 auto */
void __cdecl wnd_obj_set_capture(iptr param_1)

{
  SetCapture(*(HWND *)(param_1 + 4));
  return;
}

/* 005bd550 auto */
void __cdecl wnd_obj_release_capture(i32 param_1)

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
          (WndBase *this,iptr param_1,i32 param_2,i32 param_3,i32 param_4
          ,i32 param_5,i32 param_6,iptr param_7)

{
  iptr iVar1;
  
  wnd_create_with_cmd_proc(this,param_1,param_2,param_3,param_4,param_5,param_6,param_7);
  iVar1 = wnd_get_window(this);
  wnd_install_frame_proc((iptr)this,iVar1);
  return;
}

/* 005c57f9 auto */
void __thiscall
wnd_create_framed_child
          (WndBase *this,iptr param_1,i32 param_2,i32 param_3,i32 param_4
          ,i32 param_5,i32 param_6,iptr param_7,iptr param_8)

{
  iptr iVar1;
  
  wnd_create_with_handlers(this,param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  iVar1 = wnd_get_window(this);
  wnd_install_frame_proc((iptr)this,iVar1);
  return;
}

/* 005c59c4 auto */
#define local_8 (*(uptr *)(frame_ + FRAME_OFF(0)))
void __thiscall wnd_append_control(WndControlListView *this,iptr param_1)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = this->first_control;
  if (local_8 == 0) {
    this->first_control = param_1;
  }
  else {
    for (; *(int *)(local_8 + 0x20) != 0; local_8 = *(uptr *)(local_8 + 0x20)) {
    }
    *(iptr *)(local_8 + 0x20) = param_1;
  }
  return;
}
#undef local_8

/* 005c5a27 auto */
#define local_8 (*(ControlNextView * *)(frame_ + FRAME_OFF(0)))
void __thiscall wnd_remove_control(WndControlRemoveView *this,int param_1)

{
  int iVar1;
  ControlIdView *this_00;
  ControlNextView *this_01;
  u32 uVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (this->first_control != 0) {
    local_8 = (ControlNextView *)this->first_control;
    iVar1 = ctrl_get_id((ControlIdView *)local_8);
    if (iVar1 == param_1) {
      this->first_control = local_8->field_20;
    }
    else {
      while( true ) {
        if (local_8 == (ControlNextView *)0x0) {
          return;
        }
        iVar1 = control_get_next(local_8);
        if (iVar1 == 0) {
          return;
        }
        this_00 = (ControlIdView *)control_get_next(local_8);
        iVar1 = ctrl_get_id(this_00);
        if (iVar1 == param_1) break;
        local_8 = (ControlNextView *)control_get_next(local_8);
      }
      this_01 = (ControlNextView *)control_get_next(local_8);
      uVar2 = control_get_next(this_01);
      local_8->field_20 = uVar2;
    }
  }
  return;
}
#undef local_8

/* 005c5aeb auto */
#define local_8 (*(ControlIdView * *)(frame_ + FRAME_OFF(0)))
void __thiscall wnd_remove_all_controls(WndControlRemoveView *this)

{
  i32 uVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = (ControlIdView *)this->first_control; local_8 != (ControlIdView *)0x0;
      local_8 = *(ControlIdView **)local_8[4].pad_0) {
    uVar1 = ctrl_get_id(local_8);
    wnd_remove_control(this,uVar1);
  }
  return;
}
#undef local_8

/* 005c5b7f auto */
#define local_8 (*(ControlInitialFocusView * *)(frame_ + FRAME_OFF(0)))
void __thiscall wnd_focus_first_control(Wnd *this)

{
  char cVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = (ControlInitialFocusView *)this->control_list;
  while( true ) {
    if (local_8 == (ControlInitialFocusView *)0x0) {
      if ((this->control_list != 0) && ((char)this->keyboard_nav != '\0')) {
        wnd_focus_control((iptr)this,this->control_list);
      }
      return;
    }
    cVar1 = ctrl_get_initial_focus(local_8);
    if (cVar1 != '\0') break;
    local_8 = (ControlInitialFocusView *)control_get_next((ControlNextView *)local_8);
  }
  if ((char)this->keyboard_nav == '\0') {
    return;
  }
  wnd_focus_control((iptr)this,(iptr)local_8);
  return;
}
#undef local_8

/* 005c5c86 auto */
#define local_20 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(12)))
#define local_10 (*(RadioGroupItemsView * *)(frame_ + FRAME_OFF(16)))
#define local_c (*(u8 (*)[4])(frame_ + FRAME_OFF(20)))
#define local_8 (*(char *)(frame_ + FRAME_OFF(24)))
i32 __thiscall wnd_dispatch_hotkey_char(void *this,i32 param_1)

{
  u8 uVar1;
  iptr iVar2;
  iptr iVar3;
  i32 uVar2;
  int iVar4;
  int iVar5;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = '\0';
  local_14 = 0;
  local_c[0] = (u8)param_1;
  local_c[1] = 0;
  __strlwr((char *)local_c);
  uVar1 = local_c[0];
  local_10 = *(RadioGroupItemsView **)((int)this + 0xb8);
  do {
    if (local_10 == (RadioGroupItemsView *)0x0) {
      return local_14;
    }
    if (local_8 != '\0') {
      return local_14;
    }
    if (*(int *)(local_10->pad_0 + 0x28) < 0) {
      iVar4 = control_get_type((ControlTypeView *)local_10);
      if (iVar4 == 3) {
        iVar4 = radiogrp_get_items(local_10);
        iVar5 = radiogrp_item_count((RadioGroupCountView *)local_10);
        for (local_20 = 0; local_20 < iVar5; local_20++) {
          if ((-1 < *(int *)(iVar4 + 0xa0 + local_20 * 0xa4)) &&
             (*(u8 *)(iVar4 + 0x9c + local_20 * 0xa4) == uVar1)) {
            radiogrp_item_activate(*(i32 *)(iVar4 + local_20 * 0xa4));
            local_14 = 1;
            local_8 = 1;
            break;
          }
        }
      }
    }
    else if (local_10->pad_0[0x25] == uVar1) {
      iVar2 = control_get_type((ControlTypeView *)local_10);
      if ((iVar2 == 6) &&
         (iVar3 = ctrl_is_enabled((ControlEnabledView *)local_10), iVar3 != 0)) {
        uVar2 = control_get_hwnd((ControlHwndView *)local_10);
        button_press_animated(uVar2);
        return 1;
      }
      iVar4 = control_get_type((ControlTypeView *)local_10);
      if ((iVar4 == 2) && (iVar4 = checkbox_is_enabled((CheckboxEnabledView *)local_10), iVar4 != 0)) {
        uVar2 = control_get_hwnd((ControlHwndView *)local_10);
        checkbox_toggle_by_hotkey(uVar2);
        return 1;
      }
    }
    local_10 = *(RadioGroupItemsView **)(local_10->pad_0 + 0x20);
  } while( true );
}
#undef local_20
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 005c5f20 auto */
void __thiscall
wnd_create_with_cmd_proc
          (WndBase *this,iptr param_1,i32 param_2,i32 param_3,i32 param_4
          ,i32 param_5,i32 param_6,iptr param_7)

{
  iptr iVar1;
  
  wnd_record_create(this,param_1,param_2,param_3,param_4,param_5,param_6,param_7);
  iVar1 = wnd_get_window(this);
  wnd_install_command_proc((iptr)this,iVar1);
  wnd_clear_handlers((WndHandlers *)(this + 1));
  return;
}

/* 005c5fc4 auto */
void __thiscall
wnd_create_with_handlers
          (WndBase *this,iptr param_1,i32 param_2,i32 param_3,i32 param_4
          ,i32 param_5,i32 param_6,iptr param_7,iptr param_8)

{
  iptr iVar1;
  
  wnd_record_create_child(this,param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  iVar1 = wnd_get_window(this);
  wnd_install_command_proc((iptr)this,iVar1);
  wnd_clear_handlers((WndHandlers *)(this + 1));
  return;
}

/* 005c61b0 auto */
#define local_c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(8)))
void __thiscall wnd_run_modal_loop(ModalMenuWindow *this)

{
  iptr iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (wnd_modal_depth != 0xf) {
    this->modal_running = 1;
    wnd_modal_depth++;
    (&wnd_modal_stack)[wnd_modal_depth] = this;
    if (wnd_modal_depth == 0) {
      local_8 = 0;
    }
    else {
      local_8 = wnd_get_window((WndBase *)(&wnd_modal_stack_below)[wnd_modal_depth]);
    }
    iVar1 = wnd_get_window((WndBase *)this);
    wnd_obj_disable_owner(iVar1,local_8);
    while (this->modal_running != 0) {
      win_pump_one_message();
      if (this->on_modal_idle != 0) {
        (*(code *)this->on_modal_idle)();
      }
    }
    if (wnd_modal_depth == 0) {
      local_c = 0;
    }
    else {
      local_c = wnd_get_window((WndBase *)(&wnd_modal_stack_below)[wnd_modal_depth]);
    }
    iVar1 = wnd_get_window((WndBase *)this);
    wnd_obj_enable_owner(iVar1,local_c);
    wnd_modal_depth--;
    if (-1 < wnd_modal_depth) {
      this->modal_running = 1;
    }
  }
  return;
}
#undef local_c
#undef local_8

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
i32 __cdecl wnd_set_active_child(iptr param_1)

{
  i32 uVar1;
  
  uVar1 = wnd_active_child;
  wnd_active_child = param_1;
  return uVar1;
}
#undef wnd_active_child

/* 005c63af auto */
bool __thiscall wnd_fire_menu_select(WndMenuSelectView *this,i32 param_1)

{
  bool bVar1;
  
  bVar1 = this->on_menu_select != 0;
  if (bVar1) {
    (*(code *)this->on_menu_select)(param_1);
  }
  return bVar1;
}

/* 005c8b00 auto */
void __cdecl wnd_invalidate(HWND param_1)

{
  if (param_1 != (HWND)0x0) {
    InvalidateRect(param_1,(RECT *)0x0,0);
  }
  return;
}

/* 005c8b2d auto */
void __cdecl hwnd_show(HWND param_1)

{
  if (param_1 != (HWND)0x0) {
    ShowWindow(param_1,5);
  }
  return;
}

/* 005c8b58 auto */
void __cdecl hwnd_hide(HWND param_1)

{
  if (param_1 != (HWND)0x0) {
    ShowWindow(param_1,0);
  }
  return;
}

/* 005c8be1 auto */
#define app_hinstance (*(HINSTANCE *)((u8 *)&g.d_006e4ff0))
HWND __cdecl hotspot_create_hwnd(int *param_1,iptr param_2)

{
  WndBase *this;
  iptr iVar1;
  iptr iVar2;
  int iVar3;
  HWND pHVar4;
  HMENU hMenu;
  HINSTANCE hInstance;
  LPVOID lpParam;
  
  lpParam = (LPVOID)0x0;
  hMenu = (HMENU)0x0;
  hInstance = app_hinstance;
  this = (WndBase *)ctrl_get_parent((Control *)param_2);
  iVar1 = wnd_get_window(this);
  pHVar4 = *(HWND *)(iVar1 + 4);
  iVar2 = rect_height((iptr)param_1);
  iVar3 = rect_width((iptr)param_1);
  pHVar4 = CreateWindowExA(4,s_MSControlClass_00637ca8,&hotspot_wnd_title,0x50000000,*param_1,param_1[1],
                           iVar3,iVar2,pHVar4,hMenu,hInstance,lpParam);
  iVar3 = ctrl_init_block(pHVar4,param_2);
  *(i32 *)(iVar3 + 0x2c) = 1;
  SetWindowLongA(pHVar4,-4,ADDR(0x5c8caf, hotspot_wndproc));
  return pHVar4;
}
#undef app_hinstance

/* 005c8f70 auto */
void __thiscall hotspot_fire_enter(HotspotEnterView *this,i32 param_1)

{
  if (this->on_enter != 0) {
    (*(code *)this->on_enter)(param_1);
  }
  return;
}

/* 005c8fb0 auto */
void __thiscall hotspot_fire_leave(HotspotLeaveView *this,i32 param_1)

{
  if (this->on_leave != 0) {
    (*(code *)this->on_leave)(param_1);
  }
  return;
}

/* 005c8ff0 auto */
void __thiscall hotspot_fire_click(HotspotClickView *this,i32 param_1)

{
  if (this->on_click != 0) {
    (*(code *)this->on_click)(param_1);
  }
  return;
}

/* 005c9030 auto */
void __thiscall hotspot_fire_press(HotspotPressView *this,i32 param_1)

{
  if (this->on_press != 0) {
    (*(code *)this->on_press)(param_1);
  }
  return;
}

/* 005c9070 auto */
void __thiscall hotspot_fire_dblclick(HotspotDblClickView *this,i32 param_1)

{
  if (this->on_dblclick != 0) {
    (*(code *)this->on_dblclick)(param_1);
  }
  return;
}

/* 005c9563 auto */
LONG __cdecl wnd_from_hwnd(HWND param_1)

{
  LONG LVar1;
  
  if (param_1 == (HWND)0x0) {
    LVar1 = 0;
  }
  else {
    LVar1 = GetWindowLongA(param_1,0);
  }
  return LVar1;
}

/* 005c96cc auto */
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(4)))
void __cdecl wnd_redraw_client(HWND param_1)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  GetClientRect(param_1,&local_14);
  InvalidateRect(param_1,&local_14,1);
  UpdateWindow(param_1);
  return;
}
#undef local_14

/* 005cbdd0 auto */
u8 __thiscall wnd_keyboard_nav_enabled(WndKeyNavView *this)

{
  return this->keyboard_nav;
}

/* 005cbeb0 auto */
void __cdecl ui_wait_ticks(i32 param_1)

{
  timer_busy_wait_ticks(param_1);
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
void __cdecl ui_set_ctrl_text_color(i32 param_1)

{
  ctrl_text_color_index = (i8)param_1;
  return;
}
#undef ctrl_text_color_index

/* 005d2568 auto */
#define ctrl_shadow_color_index (*(i8 *)((u8 *)&g.d_00637e94))
#define ctrl_shadow_dx (*(i8 *)((u8 *)&g.d_00637e98))
#define ctrl_shadow_dy (*(i8 *)((u8 *)&g.d_00637e9c))
void __cdecl ui_set_ctrl_text_shadow(i32 param_1,i32 param_2,i32 param_3)

{
  ctrl_shadow_color_index = (i8)param_1;
  ctrl_shadow_dx = (i8)param_2;
  ctrl_shadow_dy = (i8)param_3;
  return;
}
#undef ctrl_shadow_color_index
#undef ctrl_shadow_dx
#undef ctrl_shadow_dy

/* 005d2590 auto */
#define ctrl_disabled_color_index (*(i8 *)((u8 *)&g.d_00637ea0))
void __cdecl ui_set_ctrl_disabled_color(i32 param_1)

{
  ctrl_disabled_color_index = (i8)param_1;
  return;
}
#undef ctrl_disabled_color_index

/* 005d25a8 auto */
void __cdecl ui_set_ctrl_font(iptr param_1)

{
  checkbox_default_font = (i8 *)param_1;
  return;
}

/* 005d268e auto */
void __cdecl ui_set_default_font(iptr param_1)

{
  ctrl_default_font = (i8 *)param_1;
  return;
}

/* 005d2d4d auto */
void __cdecl hwnd_get_text(HWND param_1,LPARAM param_2)

{
  LRESULT LVar1;
  
  LVar1 = SendMessageA(param_1,0xe,0,0);
  SendMessageA(param_1,0xd,LVar1 + 1,param_2);
  return;
}

/* 005d2d7f auto */
void __cdecl hwnd_send_settext(HWND param_1,LPARAM param_2)

{
  SendMessageA(param_1,0xc,0,param_2);
  return;
}

/* 005d417f auto */
#define radio_text_color_index (*(i8 *)((u8 *)&g.d_00637e7c))
void __cdecl ui_set_radio_text_color(i32 param_1)

{
  radio_text_color_index = (i8)param_1;
  return;
}
#undef radio_text_color_index

/* 005d4197 auto */
#define radio_disabled_color_index (*(i8 *)((u8 *)&g.d_00637e8c))
void __cdecl ui_set_radio_disabled_color(i32 param_1)

{
  radio_disabled_color_index = (i8)param_1;
  return;
}
#undef radio_disabled_color_index

/* 005d41af auto */
#define radio_shadow_color_index (*(i8 *)((u8 *)&g.d_00637e80))
#define radio_shadow_dx (*(i8 *)((u8 *)&g.d_00637e84))
#define radio_shadow_dy (*(i8 *)((u8 *)&g.d_00637e88))
void __cdecl ui_set_radio_text_shadow(i32 param_1,i32 param_2,i32 param_3)

{
  radio_shadow_color_index = (i8)param_1;
  radio_shadow_dx = (i8)param_2;
  radio_shadow_dy = (i8)param_3;
  return;
}
#undef radio_shadow_color_index
#undef radio_shadow_dx
#undef radio_shadow_dy

/* 005d8236 auto */
void __cdecl ui_set_button_font(iptr param_1)

{
  button_default_font = (i8 *)param_1;
  return;
}

/* 005db610 auto */
WndBase * __thiscall wnd_record_init(WndBase *this)

{
  this->native_wnd = 0;
  this->wnd_palette = 0;
  this->field_c = 0;
  this->style = 0;
  return this;
}

/* 005db650 auto */
void __thiscall wnd_record_destroy(WndDestroyView *this)

{
  u32 uVar1;
  
  uVar1 = wnd_obj_destroy(this->wnd_obj);
  this->wnd_obj = uVar1;
  return;
}

/* 005db67b auto */
void __thiscall
wnd_record_create
          (WndBase *this,i32 param_1,u32 param_2,i32 param_3,i32 param_4,
          i32 param_5,i32 param_6,iptr param_7)

{
  u32 uVar1;
  
  this->style = param_2;
  if (this->native_wnd != 0) {
    uVar1 = wnd_obj_destroy(this->native_wnd);
    this->native_wnd = uVar1;
  }
  uVar1 = wnd_obj_create(param_1,param_2,param_3,param_4,param_5,param_6,0);
  this->native_wnd = uVar1;
  wnd_set_owner_ptr((iptr)this,this->native_wnd);
  wnd_set_palette(this,param_7);
  return;
}

/* 005db893 auto */
void __thiscall
wnd_record_create_child
          (WndBase *this,i32 param_1,u32 param_2,i32 param_3,i32 param_4,
          i32 param_5,i32 param_6,iptr param_7,WndBase *param_8)

{
  u32 uVar1;
  iptr iVar2;
  
  this->style = param_2;
  if (this->native_wnd != 0) {
    uVar1 = wnd_obj_destroy(this->native_wnd);
    this->native_wnd = uVar1;
  }
  iVar2 = wnd_get_window(param_8);
  uVar1 = wnd_obj_create(param_1,param_2,param_3,param_4,param_5,param_6,iVar2);
  this->native_wnd = uVar1;
  wnd_set_owner_ptr((iptr)this,this->native_wnd);
  wnd_set_palette(this,param_7);
  return;
}

/* 005dba95 auto */
i32 __thiscall wnd_is_shift_down(void *this)

{
  i32 uVar1;
  
  uVar1 = input_poll_modifier(0x100);
  return uVar1;
}

/* 005dbab8 auto */
i32 __thiscall wnd_is_ctrl_down(void *this)

{
  i32 uVar1;
  
  uVar1 = input_poll_modifier(0x200);
  return uVar1;
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
void __cdecl dlg_radio_choice_button_cb(int param_1)

{
  if (param_1 == 0x65) {
    wnd_end_modal_loop((ModalMenuWindow *)(choice_dlg_window + 0x48));
  }
  else if (param_1 == 0x66) {
    choice_dlg_selection = 0xffffffff;
    wnd_end_modal_loop((ModalMenuWindow *)(choice_dlg_window + 0x48));
  }
  return;
}
#undef choice_dlg_window

/* 005e0863: written by hand in src/game/unwind.c */

/* 005e0ce0 auto */
#define menu_next_item_id (*(HMENU *)((u8 *)&g.d_00638d9c))
#define local_1c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_14 (*(HMENU *)(frame_ + FRAME_OFF(12)))
#define local_10 (*(uint *)(frame_ + FRAME_OFF(16)))
#define local_c (*(size_t *)(frame_ + FRAME_OFF(20)))
iptr __cdecl menu_hmenu_parse_items(HMENU param_1,iptr param_2)

{
  bool bVar1;
  iptr _Source;
  size_t uBytes;
  HLOCAL hMem;
  char *_Dest;
  int iVar2;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  bVar1 = false;
  local_1c = 0;
  uBytes = _strlen((char *)param_2);
  hMem = LocalAlloc(2,uBytes);
  _Dest = LocalLock(hMem);
  *_Dest = '\0';
  for (; *(char *)param_2 == ' '; param_2++) {
  }
  while (!bVar1) {
    if (*(char *)param_2 == '!') {
      local_10 = 3;
      param_2++;
    }
    else {
      local_10 = 0;
    }
    if (*(char *)param_2 == '*') {
      local_10 = local_10 | 8;
      param_2++;
    }
    _Source = param_2;
    local_c = 0;
    for (; ((*(char *)param_2 != '}' && (*(char *)param_2 != '_')) && (*(char *)param_2 != '{'));
        param_2 = param_2 + 1) {
      local_c++;
    }
    _strncat(_Dest,(char *)_Source,local_c);
    if ((*(char *)param_2 == '_') || (*(char *)param_2 == '}')) {
      if (*(char *)param_2 == '}') {
        bVar1 = true;
      }
      local_14 = menu_next_item_id;
      menu_next_item_id = (HMENU)((iptr)menu_next_item_id + 1);
      do {
        param_2++;
      } while (*(char *)param_2 == ' ');
    }
    else if (*(char *)param_2 == '{') {
      local_14 = CreateMenu();
      param_2 = menu_hmenu_parse_items(local_14,param_2 + 1);
      local_10 = local_10 | 0x10;
      for (; *(char *)param_2 == ' '; param_2++) {
      }
      if (*(char *)param_2 == '}') {
        bVar1 = true;
        param_2++;
      }
    }
    local_1c++;
    if (0x16 < local_1c) {
      local_1c = 0;
      local_10 = local_10 | 0x40;
    }
    iVar2 = _strcmp(_Dest,&menu_separator_tag);
    if (iVar2 == 0) {
      local_10 = 0x800;
      *_Dest = '\0';
      local_14 = (HMENU)0x0;
    }
    AppendMenuA(param_1,local_10,(UINT_PTR)local_14,_Dest);
    *_Dest = '\0';
  }
  LocalUnlock(hMem);
  LocalFree(hMem);
  return param_2;
}
#undef menu_next_item_id
#undef local_1c
#undef local_14
#undef local_10
#undef local_c

/* 005e0f2a auto */
#define menu_next_item_id (*(int *)((u8 *)&g.d_00638d9c))
#define local_28 (*(size_t *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(char * *)(frame_ + FRAME_OFF(20)))
HMENU __cdecl menu_hmenu_build_from_spec(char *param_1)

{
  char cVar1;
  int iVar2;
  char *_Source;
  HMENU hMenu;
  size_t uBytes;
  HLOCAL hMem;
  char *_Dest;
  HMENU uIDNewItem;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_14 = param_1;
  hMenu = CreateMenu();
  iVar2 = menu_next_item_id;
  uBytes = _strlen(param_1);
  hMem = LocalAlloc(2,uBytes);
  _Dest = LocalLock(hMem);
  *_Dest = '\0';
  while (*local_14 != '\0') {
    for (; *local_14 == ' '; local_14++) {
    }
    cVar1 = *local_14;
    if (cVar1 == '!') {
      local_14++;
    }
    _Source = local_14;
    local_28 = 0;
    for (; *local_14 != '{'; local_14++) {
      local_28++;
    }
    _strncat(_Dest,_Source,local_28);
    do {
      local_14++;
    } while (*local_14 == ' ');
    uIDNewItem = CreateMenu();
    local_14 = (char *)menu_hmenu_parse_items(uIDNewItem,(iptr)local_14);
    if (cVar1 != '!') {
      AppendMenuA(hMenu,0x10,(UINT_PTR)uIDNewItem,_Dest);
    }
    else {
      AppendMenuA(hMenu,0x13,(UINT_PTR)uIDNewItem,_Dest);
    }
    *_Dest = '\0';
  }
  menu_next_item_id = iVar2 + 100;
  LocalUnlock(hMem);
  LocalFree(hMem);
  return hMenu;
}
#undef menu_next_item_id
#undef local_28
#undef local_14

/* 005e10c7 auto */
void __cdecl menu_hmenu_destroy(HMENU param_1)

{
  if (param_1 != (HMENU)0x0) {
    DestroyMenu(param_1);
  }
  return;
}

/* 005e10fb auto */
void __cdecl menu_redraw_bar(iptr param_1)

{
  DrawMenuBar(*(HWND *)(param_1 + 4));
  return;
}

/* 005e1118 auto */
BOOL __cdecl menu_hmenu_enable_item(HMENU param_1,int param_2,int param_3,i32 param_4)

{
  BOOL BVar1;
  HMENU hMenu;
  
  if (param_3 == 0) {
    if ((char)param_4 == '\0') {
      BVar1 = EnableMenuItem(param_1,param_2 - 1,0x403);
    }
    else {
      BVar1 = EnableMenuItem(param_1,param_2 - 1,0x400);
    }
  }
  else {
    hMenu = GetSubMenu(param_1,param_2 - 1);
    if ((char)param_4 == '\0') {
      BVar1 = EnableMenuItem(hMenu,param_3 - 1,0x403);
    }
    else {
      BVar1 = EnableMenuItem(hMenu,param_3 - 1,0x400);
    }
  }
  return BVar1;
}

/* 005e11be auto */
void __cdecl menu_hmenu_check_item(HMENU param_1,int param_2,int param_3,i32 param_4)

{
  HMENU hMenu;
  
  if (param_1 != (HMENU)0x0) {
    hMenu = GetSubMenu(param_1,param_2 - 1);
    if ((char)param_4 == '\0') {
      CheckMenuItem(hMenu,param_3 - 1,0x400);
    }
    else {
      CheckMenuItem(hMenu,param_3 - 1,0x408);
    }
  }
  return;
}

/* 005e1226 auto */
void __cdecl menu_hmenu_delete_item(HMENU param_1,int param_2,int param_3)

{
  HMENU hMenu;
  
  if (param_1 != (HMENU)0x0) {
    hMenu = GetSubMenu(param_1,param_2 - 1);
    if (param_3 == -1) {
      RemoveMenu(param_1,param_2 - 1,0x400);
    }
    else {
      DeleteMenu(hMenu,param_3 - 1,0x400);
    }
  }
  return;
}

/* 005e128c auto */
#define menu_next_item_id (*(UINT_PTR *)((u8 *)&g.d_00638d9c))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(8)))
void __cdecl menu_hmenu_insert_item(HMENU param_1,int param_2,int param_3,LPCSTR param_4)

{
  UINT_PTR uIDNewItem;
  HMENU pHVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 != (HMENU)0x0) {
    pHVar1 = GetSubMenu(param_1,param_2 - 1);
    local_c = 0;
    if (((pHVar1 != (HMENU)0x0) && (param_3 != -1)) && (param_2 != -1)) {
      local_c = GetMenuItemCount(pHVar1);
    }
    uIDNewItem = menu_next_item_id;
    if ((local_c % 0x16 == 0) && (local_c != 0)) {
      local_8 = 0x440;
    }
    else {
      local_8 = 0x400;
    }
    if (param_3 == -1) {
      pHVar1 = CreatePopupMenu();
      if (param_2 == -1) {
        AppendMenuA(param_1,local_8 | 0x10,(UINT_PTR)pHVar1,param_4);
      }
      else {
        InsertMenuA(param_1,param_2 - 1,local_8 | 0x10,(UINT_PTR)pHVar1,param_4);
      }
    }
    else {
      menu_next_item_id++;
      InsertMenuA(pHVar1,param_3 - 1,local_8,uIDNewItem,param_4);
    }
  }
  return;
}
#undef menu_next_item_id
#undef local_c
#undef local_8

/* 005e14c8 auto */
void __cdecl menu_hmenu_set_item_text(HMENU param_1,int param_2,int param_3,LPCSTR param_4)

{
  HMENU hMenu;
  UINT uIDNewItem;
  
  if (param_1 != (HMENU)0x0) {
    hMenu = GetSubMenu(param_1,param_2 - 1);
    if (param_3 == -1) {
      ModifyMenuA(param_1,param_2 - 1,0x410,(UINT_PTR)hMenu,param_4);
    }
    else {
      uIDNewItem = GetMenuItemID(hMenu,param_3 - 1);
      ModifyMenuA(hMenu,param_3 - 1,0x400,uIDNewItem,param_4);
    }
  }
  return;
}

/* 005e1880 auto */
void __cdecl wnd_install_paint_proc(iptr param_1,iptr param_2)

{
  SetWindowLongA(*(HWND *)(param_2 + 4),0xc,param_1);
  SetWindowLongA(*(HWND *)(param_2 + 4),-4,ADDR(0x5e18ff, surfwnd_subclass_wndproc));
  return;
}

/* 005e18ff auto */
#define wnd_active_child (*(u8 * *)((u8 *)&g.d_00637ea4))
#define local_74 (*(u8 * *)(frame_ + FRAME_OFF(4)))
#define local_68 (*(tagPAINTSTRUCT *)(frame_ + FRAME_OFF(16)))
#define local_28 (*(HDC *)(frame_ + FRAME_OFF(80)))
#define local_24 (*(tagRECT *)(frame_ + FRAME_OFF(84)))
#define local_14 (*(LONG *)(frame_ + FRAME_OFF(100)))
#define local_10 (*(LONG *)(frame_ + FRAME_OFF(104)))
#define local_c (*(LONG *)(frame_ + FRAME_OFF(108)))
#define local_8 (*(LONG *)(frame_ + FRAME_OFF(112)))
i32 __stdcall surfwnd_subclass_wndproc(HWND param_1,int param_2,i32 param_3,uint param_4)

{
  SurfaceWindow *this;
  i32 uVar1;
  BOOL BVar2;
  iptr iVar3;
  iptr iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int yDest;
  LONG wDest;
  LONG hDest;
  HDC hdcSrc;
  int xSrc;
  int ySrc;
  DWORD rop;
  i8 frame_[FRAME_OFF(120)] __attribute__((aligned(8)));  /* original stack frame */
  
  this = (SurfaceWindow *)GetWindowLongA(param_1,0xc);
  if (this == (SurfaceWindow *)0x0) {
    uVar1 = wnd_frame_wndproc(param_1,param_2,param_3,param_4);
  }
  else if (param_2 == 2) {
    surface_create((DibSurface *)this,0,0);
    SetWindowLongA(param_1,0xc,0);
    uVar1 = wnd_frame_wndproc(param_1,2,param_3,param_4);
  }
  else if (param_2 == 5) {
    if (this == (SurfaceWindow *)0x0) {
      wnd_active_child = (u8 *)0x0;
    }
    else {
      wnd_active_child = this->pad_48;
    }
    BVar2 = IsIconic(param_1);
    if (BVar2 == 0) {
      surfwnd_on_resize(this,param_4 & 0xffff,param_4 >> 0x10);
    }
    uVar1 = wnd_frame_wndproc(param_1,5,param_3,param_4);
  }
  else if (param_2 == 0xf) {
    BVar2 = IsIconic(param_1);
    if (BVar2 == 0) {
      BVar2 = IsWindowVisible(param_1);
      if (BVar2 != 0) {
        BeginPaint(param_1,&local_68);
        local_14 = local_68.rcPaint.left;
        local_10 = local_68.rcPaint.top;
        local_c = local_68.rcPaint.right;
        local_8 = local_68.rcPaint.bottom;
        if (this == (SurfaceWindow *)0x0) {
          local_74 = (u8 *)0x0;
        }
        else {
          local_74 = this->pad_48;
        }
        surface_blit_to_wnd
                  ((DibSurface *)this,(iptr)local_74,(iptr)&local_14,(iptr)&local_14);
        EndPaint(param_1,&local_68);
      }
    }
    else {
      iVar3 = wnd_get_window((WndBase *)this->pad_48);
      if (*(int *)(iVar3 + 0x20) != 0) {
        uVar1 = wnd_base_wndproc(param_1,0xf,param_3,param_4);
        return uVar1;
      }
      local_28 = BeginPaint(param_1,&local_68);
      local_14 = local_68.rcPaint.left;
      local_10 = local_68.rcPaint.top;
      local_c = local_68.rcPaint.right;
      local_8 = local_68.rcPaint.bottom;
      SetRect(&local_24,0,0,0,0);
      iVar4 = surface_get_width((DibSurface *)this);
      iVar5 = surface_get_height((DibSurface *)this);
      if (iVar4 < iVar5) {
        iVar5 = surface_get_width((DibSurface *)this);
        iVar6 = rect_width((iptr)&local_14);
        local_24.right = surface_get_height((DibSurface *)this);
        local_24.right = (iVar5 * iVar6) / local_24.right;
        local_24.bottom = rect_height((iptr)&local_14);
      }
      else {
        local_24.right = rect_width((iptr)&local_14);
        iVar5 = surface_get_height((DibSurface *)this);
        iVar6 = rect_height((iptr)&local_14);
        local_24.bottom = surface_get_width((DibSurface *)this);
        local_24.bottom = (iVar5 * iVar6) / local_24.bottom;
      }
      iVar5 = surface_get_dib((DibSurface *)this);
      hdcSrc = *(HDC *)(iVar5 + 4);
      rop = 0xcc0020;
      iVar5 = surface_get_height((DibSurface *)this);
      iVar6 = surface_get_width((DibSurface *)this);
      ySrc = 0;
      xSrc = 0;
      wDest = local_24.right;
      hDest = local_24.bottom;
      iVar7 = rect_height((iptr)&local_14);
      iVar8 = rect_height((iptr)&local_24);
      yDest = iVar7 - iVar8 >> 1;
      iVar7 = rect_width((iptr)&local_14);
      iVar8 = rect_width((iptr)&local_24);
      StretchBlt(local_28,iVar7 - iVar8 >> 1,yDest,wDest,hDest,hdcSrc,xSrc,ySrc,iVar6,iVar5,rop);
      EndPaint(param_1,&local_68);
    }
    uVar1 = 0;
  }
  else {
    uVar1 = wnd_frame_wndproc(param_1,param_2,param_3,param_4);
  }
  return uVar1;
}
#undef wnd_active_child
#undef local_74
#undef local_68
#undef local_28
#undef local_24
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 005ea7a0 auto */
void __cdecl wnd_install_frame_proc(iptr param_1,iptr param_2)

{
  SetWindowLongA(*(HWND *)(param_2 + 4),8,param_1);
  SetWindowLongA(*(HWND *)(param_2 + 4),-4,ADDR(0x5eacc0, wnd_frame_wndproc));
  return;
}

/* 005ea825 auto */
HWND __cdecl hwnd_next_sibling_wrap(HWND param_1)

{
  BOOL BVar1;
  HWND pHVar2;
  
  BVar1 = IsWindow(param_1);
  if (BVar1 == 0) {
    pHVar2 = (HWND)0x0;
  }
  else {
    pHVar2 = GetWindow(param_1,2);
    if (pHVar2 == (HWND)0x0) {
      pHVar2 = GetWindow(param_1,0);
    }
  }
  return pHVar2;
}

/* 005ea87c auto */
HWND __cdecl hwnd_prev_sibling_wrap(HWND param_1)

{
  BOOL BVar1;
  HWND pHVar2;
  
  BVar1 = IsWindow(param_1);
  if (BVar1 == 0) {
    pHVar2 = (HWND)0x0;
  }
  else {
    pHVar2 = GetWindow(param_1,3);
    if (pHVar2 == (HWND)0x0) {
      pHVar2 = GetWindow(param_1,1);
    }
  }
  return pHVar2;
}

/* 005ea8d3 auto */
#define local_10 (*(HWND *)(frame_ + FRAME_OFF(0)))
void __cdecl wnd_cycle_control_focus(iptr param_1,HWND param_2,int param_3)

{
  iptr iVar1;
  BOOL BVar1;
  iptr iVar2;
  HWND pHVar2;
  int iVar3;
  CheckboxEnabledView *this;
  UINT UVar4;
  UINT uCmd;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_2 == (HWND)0x0) {
    param_2 = GetFocus();
    pHVar2 = param_2;
    iVar1 = wnd_get_window((WndBase *)param_1);
    BVar1 = IsChild(*(HWND *)(iVar1 + 4),pHVar2);
    if (BVar1 == 0) {
      param_2 = (HWND)0x0;
    }
  }
  if (param_2 == (HWND)0x0) {
    if (*(int *)(param_1 + 0xb8) == 0) {
      return;
    }
    if (param_3 == 2) {
      UVar4 = 5;
      iVar2 = wnd_get_window((WndBase *)param_1);
      param_2 = GetWindow(*(HWND *)(iVar2 + 4),UVar4);
      pHVar2 = param_2;
    }
    else {
      uCmd = 1;
      UVar4 = 5;
      iVar3 = wnd_get_window((WndBase *)param_1);
      pHVar2 = GetWindow(*(HWND *)(iVar3 + 4),UVar4);
      param_2 = GetWindow(pHVar2,uCmd);
      pHVar2 = param_2;
    }
  }
  else if (param_3 == 2) {
    param_2 = (HWND)hwnd_next_sibling_wrap(param_2);
    pHVar2 = param_2;
  }
  else {
    param_2 = (HWND)hwnd_prev_sibling_wrap(param_2);
    pHVar2 = param_2;
  }
  do {
    BVar1 = IsWindow(param_2);
    if (BVar1 == 0) {
      return;
    }
    BVar1 = IsWindowVisible(param_2);
    if (BVar1 == 0) {
      if (param_3 == 2) {
        param_2 = (HWND)hwnd_next_sibling_wrap(param_2);
      }
      else {
        param_2 = (HWND)hwnd_prev_sibling_wrap(param_2);
      }
    }
    else {
      iVar3 = ctrl_hwnd_is_radio(param_2);
      if (iVar3 != 0) {
        local_10 = param_2;
        while( true ) {
          BVar1 = IsWindow(param_2);
          if (BVar1 == 0) {
            return;
          }
          iVar3 = radiogrp_hwnds_same_group(local_10,param_2);
          if (iVar3 == 0) break;
          iVar3 = radiogrp_hwnd_is_selected(param_2);
          if (iVar3 != 0) {
            SetFocus(param_2);
            return;
          }
          local_10 = param_2;
          if (param_3 == 2) {
            param_2 = (HWND)hwnd_next_sibling_wrap(param_2);
          }
          else {
            param_2 = (HWND)hwnd_prev_sibling_wrap(param_2);
          }
        }
        wnd_cycle_control_focus(param_1,local_10,param_3);
        return;
      }
      this = (CheckboxEnabledView *)ctrl_list_find_by_hwnd(param_2,*(i32 *)(param_1 + 0xb8));
      if ((this != (CheckboxEnabledView *)0x0) &&
         ((((iVar3 = control_get_type((ControlTypeView *)this), iVar3 == 6 &&
            (iVar3 = ctrl_is_enabled((ControlEnabledView *)this), iVar3 != 0)) ||
           ((iVar3 = control_get_type((ControlTypeView *)this), iVar3 == 2 &&
            (iVar3 = checkbox_is_enabled(this), iVar3 != 0)))) ||
          (((iVar3 = control_get_type((ControlTypeView *)this), iVar3 == 4 ||
            (iVar3 = control_get_type((ControlTypeView *)this), iVar3 == 7)) ||
           (iVar3 = control_get_type((ControlTypeView *)this), iVar3 == 10)))))) {
        SetFocus(param_2);
        return;
      }
      if (param_3 == 2) {
        param_2 = (HWND)hwnd_next_sibling_wrap(param_2);
      }
      else {
        param_2 = (HWND)hwnd_prev_sibling_wrap(param_2);
      }
    }
    if (param_2 == pHVar2) {
      return;
    }
  } while( true );
}
#undef local_10

/* 005eabcc auto */
void __cdecl wnd_focus_control(iptr param_1,iptr param_2)

{
  char cVar1;
  int iVar2;
  i32 *puVar3;
  i32 uVar4;
  
  cVar1 = wnd_keyboard_nav_enabled((WndKeyNavView *)param_1);
  if (cVar1 != '\0') {
    iVar2 = control_get_type((ControlTypeView *)param_2);
    if (iVar2 == 3) {
      puVar3 = (i32 *)radiogrp_get_items((RadioGroupItemsView *)param_2);
      uVar4 = hwnd_prev_sibling_wrap(*puVar3);
      wnd_cycle_control_focus(param_1,uVar4,2);
    }
    else {
      uVar4 = control_get_hwnd((ControlHwndView *)param_2);
      uVar4 = hwnd_prev_sibling_wrap(uVar4);
      wnd_cycle_control_focus(param_1,uVar4,2);
    }
  }
  return;
}

/* 005eb370 auto */
void __cdecl wnd_set_owner_ptr(iptr param_1,iptr param_2)

{
  SetWindowLongA(*(HWND *)(param_2 + 4),0,param_1);
  return;
}

/* 005eb393 auto */
void __cdecl wnd_install_command_proc(iptr param_1,iptr param_2)

{
  SetWindowLongA(*(HWND *)(param_2 + 4),4,param_1);
  SetWindowLongA(*(HWND *)(param_2 + 4),-4,ADDR(0x5eb447, wnd_child_wndproc));
  return;
}

/* 005ec1a1 auto */
#define menu_search_pos (*(i32 *)((u8 *)&g.d_006e5368))
void __cdecl wnd_on_menu_command(HWND param_1,i32 param_2)

{
  char cVar1;
  WndOnCommandView *this;
  HMENU pHVar2;
  uint uVar3;
  
  this = (WndOnCommandView *)GetWindowLongA(param_1,4);
  cVar1 = wnd_call_command(this,param_2);
  if (cVar1 == '\0') {
    menu_search_pos = 0;
    pHVar2 = GetMenu(param_1);
    if (pHVar2 != (HMENU)0x0) {
      uVar3 = menu_find_item_pos(pHVar2,param_2);
      wnd_call_menu_pos_command((WndOnMenuPosCommandView *)this,uVar3 & 0xffff,uVar3 >> 0x10);
    }
  }
  return;
}
#undef menu_search_pos

/* 005ec23a auto */
#define menu_search_pos (*(int *)((u8 *)&g.d_006e5368))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
uint __cdecl menu_find_item_pos(HMENU param_1,UINT param_2)

{
  int iVar1;
  UINT UVar2;
  HMENU pHVar3;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 0;
  menu_search_pos++;
  iVar1 = GetMenuItemCount(param_1);
  for (local_8 = 0; local_8 < iVar1; local_8++) {
    UVar2 = GetMenuItemID(param_1,local_8);
    if (UVar2 == 0xffffffff) {
      pHVar3 = GetSubMenu(param_1,local_8);
      local_c = menu_find_item_pos(pHVar3,param_2);
      if (local_c != 0) {
        local_8 = iVar1 + 1;
      }
    }
    else {
      UVar2 = GetMenuItemID(param_1,local_8);
      if (param_2 == UVar2) {
        local_c = (local_8 + 1) * 0x10000 | menu_search_pos - 1U;
        local_8 = iVar1 + 1;
      }
    }
  }
  return local_c;
}
#undef menu_search_pos
#undef local_c
#undef local_8

/* 005ecf50 auto */
void __thiscall wnd_call_mousemove(WndOnMouseMoveView *this,i32 param_1,i32 param_2)

{
  if (this->on_mousemove != 0) {
    (*(code *)this->on_mousemove)(param_1,param_2);
  }
  return;
}

/* 005ecf90 auto */
void __thiscall wnd_call_lbuttondown(WndOnLButtonDownView *this,iptr param_1,iptr param_2)

{
  if (this->on_lbuttondown != 0) {
    (*(code *)this->on_lbuttondown)(param_1,param_2);
  }
  return;
}

/* 005ecfd0 auto */
void __thiscall wnd_call_lbuttonup_raw(WndOnLButtonUpRawView *this,iptr param_1,iptr param_2)

{
  if (this->on_lbuttonup_raw != 0) {
    (*(code *)this->on_lbuttonup_raw)(param_1,param_2);
  }
  return;
}

/* 005ed010 auto */
void __thiscall wnd_call_lbuttonup(WndOnLButtonUpView *this,i32 param_1,i32 param_2)

{
  if (this->on_lbuttonup != 0) {
    (*(code *)this->on_lbuttonup)(param_1,param_2);
  }
  return;
}

/* 005ed050 auto */
void __thiscall wnd_call_rbuttondown(WndOnRButtonDownView *this,iptr param_1,iptr param_2)

{
  if (this->on_rbuttondown != 0) {
    (*(code *)this->on_rbuttondown)(param_1,param_2);
  }
  return;
}

/* 005ed090 auto */
void __thiscall wnd_call_rbuttonup_raw(WndOnRButtonUpRawView *this,i32 param_1,i32 param_2)

{
  if (this->on_rbuttonup_raw != 0) {
    (*(code *)this->on_rbuttonup_raw)(param_1,param_2);
  }
  return;
}

/* 005ed0d0 auto */
void __thiscall wnd_call_rbuttonup(WndOnRButtonUpView *this,i32 param_1,i32 param_2)

{
  if (this->on_rbuttonup != 0) {
    (*(code *)this->on_rbuttonup)(param_1,param_2);
  }
  return;
}

/* 005ed110 auto */
void __thiscall wnd_call_dblclick(WndOnDblClickView *this,i32 param_1,i32 param_2)

{
  if (this->on_dblclick != 0) {
    (*(code *)this->on_dblclick)(param_1,param_2);
  }
  return;
}

/* 005ed150 auto */
void __thiscall wnd_call_keydown_pre(WndOnKeyDownPreView *this,i32 param_1)

{
  if (this->on_keydown_pre != 0) {
    (*(code *)this->on_keydown_pre)(param_1);
  }
  return;
}

/* 005ed190 auto */
void __thiscall wnd_call_keyup(WndOnKeyUpView *this,i32 param_1)

{
  if (this->on_keyup != 0) {
    (*(code *)this->on_keyup)(param_1);
  }
  return;
}

/* 005ed1d0 auto */
void __thiscall wnd_call_keydown(WndOnKeyDownView *this,i32 param_1)

{
  if (this->on_keydown != 0) {
    (*(code *)this->on_keydown)(param_1);
  }
  return;
}

/* 005ed210 auto */
void __thiscall wnd_call_char(WndOnCharView *this,i32 param_1)

{
  if (this->on_char != 0) {
    (*(code *)this->on_char)(param_1);
  }
  return;
}

/* 005ed250 auto */
i32 __thiscall wnd_call_close(WndOnCloseView *this)

{
  i32 uVar1;
  
  if (this->on_close == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = (*(code *)this->on_close)();
  }
  return uVar1;
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
void __thiscall wnd_call_size(WndOnSizeView *this,i32 param_1)

{
  if (this->on_size != 0) {
    (*(code *)this->on_size)(param_1);
  }
  return;
}

/* 005ed360 auto */
void __thiscall wnd_call_move(WndOnMoveView *this,i32 param_1,i32 param_2)

{
  if (this->on_move != 0) {
    (*(code *)this->on_move)(param_1,param_2);
  }
  return;
}

/* 005ed3a0 auto */
void __thiscall wnd_call_msg44(WndOnMsg44View *this,iptr param_1)

{
  if (this->on_commnotify != 0) {
    (*(code *)this->on_commnotify)(param_1);
  }
  return;
}

/* 005ed3e0 auto */
void __thiscall wnd_call_hscroll(WndOnHScrollView *this,i32 param_1)

{
  if (this->on_hscroll != 0) {
    (*(code *)this->on_hscroll)(param_1);
  }
  return;
}

/* 005ed420 auto */
void __thiscall wnd_call_hscroll_track(WndOnHScrollTrackView *this,i32 param_1)

{
  if (this->on_hscroll_track != 0) {
    (*(code *)this->on_hscroll_track)(param_1);
  }
  return;
}

/* 005ed460 auto */
void __thiscall wnd_call_vscroll(WndOnVScrollView *this,i32 param_1)

{
  if (this->on_vscroll != 0) {
    (*(code *)this->on_vscroll)(param_1);
  }
  return;
}

/* 005ed4a0 auto */
void __thiscall wnd_call_vscroll_track(WndOnVScrollTrackView *this,i32 param_1)

{
  if (this->on_vscroll_track != 0) {
    (*(code *)this->on_vscroll_track)(param_1);
  }
  return;
}

/* 005ed4e0 auto */
void __thiscall wnd_call_msg4c8(WndCallMsg4c8View *this,i32 param_1)

{
  if (this->on_msg_4c8 != 0) {
    (*(code *)this->on_msg_4c8)(param_1);
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
void __thiscall wnd_on_size_nop(void *this,i32 param_1,i32 param_2)

{
  return;
}

/* 005ed5a0 auto */
bool __thiscall wnd_call_menu_pos_command(WndOnMenuPosCommandView *this,i32 param_1,i32 param_2)

{
  bool bVar1;
  
  bVar1 = this->on_menu_pos_command != 0;
  if (bVar1) {
    (*(code *)this->on_menu_pos_command)(param_1,param_2);
  }
  return bVar1;
}

/* 005ed5f0 auto */
bool __thiscall wnd_call_command(WndOnCommandView *this,i32 param_1)

{
  bool bVar1;
  
  bVar1 = this->on_command != 0;
  if (bVar1) {
    (*(code *)this->on_command)(param_1);
  }
  return bVar1;
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
i32 __cdecl ddwin_destroy_native(i32 *param_1)

{
  i32 uVar1;
  
  if (param_1 != (i32 *)0x0) {
    if (param_1[5] == 0) {
      if (param_1[1] != 0) {
        ShowWindow((HWND)param_1[1],0);
        DestroyWindow((HWND)param_1[1]);
      }
      param_1[1] = 0;
    }
    uVar1 = *param_1;
    mem_handle_unlock(uVar1);
    mem_handle_free(uVar1);
  }
  return 0;
}

/* 005ef6cb auto */
LRESULT __stdcall ddwin_native_wndproc(HWND param_1,uint param_2,uint param_3,uint param_4)

{
  char cVar1;
  DDWindow *this;
  LRESULT LVar2;
  i32 uVar3;
  int iVar4;
  uptr DVar5;
  i32 uVar5;
  
  this = (DDWindow *)GetClassLongA(param_1,4);
  if (this == (DDWindow *)0x0) {
    LVar2 = DefWindowProcA(param_1,param_2,param_3,param_4);
    return LVar2;
  }
  if (param_2 < 0x11) {
    if (param_2 != 0x10) {
      if (param_2 == 2) {
        DVar5 = GetClassLongA(param_1,0);
        *(i32 *)(DVar5 + 0x14) = 1;
        LVar2 = DefWindowProcA(param_1,2,param_3,param_4);
        return LVar2;
      }
      goto switchD_005efc68_default;
    }
    iVar4 = wnd_call_close((WndOnCloseView *)(this->pad_0 + 0x44));
    if (iVar4 != 0) {
      LVar2 = DefWindowProcA(param_1,0x10,param_3,param_4);
      return LVar2;
    }
  }
  else if (param_2 < 0x45) {
    if (param_2 != 0x44) {
      if (param_2 != 0x1c) goto switchD_005efc68_default;
      if (param_3 != ddwin_last_activate_app) {
        ddwin_call_activate_app((DDWindowActivateView *)this,param_3);
        ddwin_last_activate_app = param_3;
      }
    }
  }
  else if (param_2 < 0x201) {
    if (param_2 == 0x200) {
      cVar1 = ddwin_dispatch_ctrl_msg(this,0x200,param_4 & 0xffff,param_4 >> 0x10);
      if (cVar1 == '\0') {
        wnd_call_mousemove
                  ((WndOnMouseMoveView *)(this->pad_0 + 0x44),param_4 & 0xffff,param_4 >> 0x10);
      }
    }
    else if (param_2 == 0x100) {
      uVar5 = 0;
      uVar3 = input_map_vkey(param_3);
      cVar1 = ddwin_dispatch_ctrl_msg(this,0x100,uVar3,uVar5);
      if (cVar1 == '\0') {
        uVar3 = input_map_vkey(param_3);
        wnd_call_keydown_pre((WndOnKeyDownPreView *)(this->pad_0 + 0x44),uVar3);
        uVar3 = input_map_vkey(param_3);
        wnd_call_keydown((WndOnKeyDownView *)(this->pad_0 + 0x44),uVar3);
      }
    }
    else if (param_2 == 0x101) {
      uVar3 = input_map_vkey(param_3);
      wnd_call_keyup((WndOnKeyUpView *)(this->pad_0 + 0x44),uVar3);
    }
    else {
      if (param_2 != 0x102) goto switchD_005efc68_default;
      cVar1 = ddwin_dispatch_ctrl_msg(this,0x102,param_3 & 0xff,0);
      if (cVar1 == '\0') {
        wnd_call_char((WndOnCharView *)(this->pad_0 + 0x44),param_3 & 0xff);
      }
    }
  }
  else if (param_2 < 0x211) {
    if (param_2 == 0x210) {
      if ((param_3 & 0xffff) == 0x201) {
        wnd_call_lbuttondown
                  ((WndOnLButtonDownView *)(this->pad_0 + 0x44),param_4 & 0xffff,param_4 >> 0x10);
      }
      else if ((param_3 & 0xffff) == 0x204) {
        wnd_call_rbuttondown
                  ((WndOnRButtonDownView *)(this->pad_0 + 0x44),param_4 & 0xffff,param_4 >> 0x10);
      }
    }
    else {
      switch(param_2) {
      case 0x201:
        cVar1 = ddwin_dispatch_ctrl_msg(this,param_2,param_4 & 0xffff,param_4 >> 0x10);
        if (cVar1 == '\0') {
          this[1].pad_0[0] = 1;
          this[1].pad_0[1] = '\0';
          this[1].pad_0[2] = '\0';
          this[1].pad_0[3] = '\0';
          wnd_call_lbuttondown
                    ((WndOnLButtonDownView *)(this->pad_0 + 0x44),param_4 & 0xffff,param_4 >> 0x10);
        }
        break;
      case 0x202:
        cVar1 = ddwin_dispatch_ctrl_msg(this,param_2,param_4 & 0xffff,param_4 >> 0x10);
        if (cVar1 == '\0') {
          if (*(int *)this[1].pad_0 == 1) {
            this[1].pad_0[0] = '\0';
            this[1].pad_0[1] = '\0';
            this[1].pad_0[2] = '\0';
            this[1].pad_0[3] = '\0';
            wnd_call_lbuttonup
                      ((WndOnLButtonUpView *)(this->pad_0 + 0x44),param_4 & 0xffff,param_4 >> 0x10);
          }
          wnd_call_lbuttonup_raw
                    ((WndOnLButtonUpRawView *)(this->pad_0 + 0x44),param_4 & 0xffff,param_4 >> 0x10);
        }
        break;
      case 0x203:
        cVar1 = ddwin_dispatch_ctrl_msg(this,param_2,param_4 & 0xffff,param_4 >> 0x10);
        if (cVar1 == '\0') {
          wnd_call_dblclick
                    ((WndOnDblClickView *)(this->pad_0 + 0x44),param_4 & 0xffff,param_4 >> 0x10);
        }
        break;
      case 0x204:
        cVar1 = ddwin_dispatch_ctrl_msg(this,param_2,param_4 & 0xffff,param_4 >> 0x10);
        if (cVar1 == '\0') {
          this[1].pad_0[4] = 1;
          this[1].pad_0[5] = '\0';
          this[1].pad_0[6] = '\0';
          this[1].pad_0[7] = '\0';
          wnd_call_rbuttondown
                    ((WndOnRButtonDownView *)(this->pad_0 + 0x44),param_4 & 0xffff,param_4 >> 0x10);
        }
        break;
      case 0x205:
        cVar1 = ddwin_dispatch_ctrl_msg(this,param_2,param_4 & 0xffff,param_4 >> 0x10);
        if (cVar1 == '\0') {
          if (*(int *)(this[1].pad_0 + 4) == 1) {
            this[1].pad_0[4] = '\0';
            this[1].pad_0[5] = '\0';
            this[1].pad_0[6] = '\0';
            this[1].pad_0[7] = '\0';
            wnd_call_rbuttonup
                      ((WndOnRButtonUpView *)(this->pad_0 + 0x44),param_4 & 0xffff,param_4 >> 0x10);
          }
          wnd_call_rbuttonup_raw
                    ((WndOnRButtonUpRawView *)(this->pad_0 + 0x44),param_4 & 0xffff,param_4 >> 0x10);
        }
        break;
      default:
        goto switchD_005efc68_default;
      }
    }
  }
  else {
    if (param_2 != 0x4c8) {
switchD_005efc68_default:
      LVar2 = DefWindowProcA(param_1,param_2,param_3,param_4);
      return LVar2;
    }
    if (param_4 == 0x20d) {
      wnd_call_msg4c8((WndCallMsg4c8View *)(this->pad_0 + 0x44),0);
    }
  }
  return 0;
}

/* 005efd70 auto */
void __thiscall ddwin_call_activate_app(DDWindowActivateView *this,i32 param_1)

{
  if (this->on_activate_app != 0) {
    (*(code *)this->on_activate_app)(param_1);
  }
  return;
}

/* 005efeb0: written by hand in src/game/unwind.c */

/* 005f029e auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
void __thiscall ddwin_remove_all_controls(void *this)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = ptrlist_first((PtrList *)((int)this + 0xc0));
  while (local_8 != 0) {
    ptrlist_remove_current((PtrList *)((int)this + 0xc0));
    local_8 = ptrlist_first((PtrList *)((int)this + 0xc0));
  }
  return;
}
#undef local_8

/* 005f0342 auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
void __thiscall ddwin_deactivate_controls(void *this)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = ptrlist_first((PtrList *)((int)this + 0xc0));
  while (local_8 != 0) {
    ddctrl_deactivate(local_8);
    local_8 = ptrlist_next((PtrList *)((int)this + 0xc0));
  }
  return;
}
#undef local_8

/* 005f0391 auto */
#define local_8 (*(DDControl * *)(frame_ + FRAME_OFF(0)))
i8 __thiscall ddwin_dispatch_ctrl_msg(DDWindow *this,int param_1,int param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((this->hover_control != 0) && (param_1 == 0x200)) {
    piVar1 = (int *)ddctrl_get_rect((void *)this->hover_control);
    if ((param_2 < *piVar1) ||
       (((piVar1[2] < param_2 || (param_3 < piVar1[1])) || (piVar1[3] < param_3)))) {
      ddctrl_dispatch_msg((DDControl *)this->hover_control,0xfff0,param_2,param_3);
      this->hover_control = 0;
    }
  }
  local_8 = (DDControl *)ptrlist_first((PtrList *)(this->pad_0 + 0xc0));
  while( true ) {
    if (local_8 == (DDControl *)0x0) {
      return 0;
    }
    iVar2 = ddctrl_dispatch_msg(local_8,param_1,param_2,param_3);
    if (iVar2 != 0) break;
    local_8 = (DDControl *)ptrlist_next((PtrList *)(this->pad_0 + 0xc0));
  }
  if (param_1 == 0x200) {
    this->hover_control = (uptr)local_8;
  }
  return 1;
}
#undef local_8
