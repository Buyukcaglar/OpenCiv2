/* The game, the space race: functions translated from the original
 * (tools/gen_c.py, now edited directly), in address order. */
#include "auto_common.h"

/* 004d0160 auto */
#define net_host_handoff_stage (*(char *)((u8 *)&g.d_006ad698))
#define spaceship_wnd_open_ticks_i32 (*(i32 *)((u8 *)&g.d_006a5b08))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl spaceship_wnd_net_idle(void)

{
  int now;
  
  net_process_messages((NetSession *)&net_session,1,0);
  if ((net_host_handoff_stage == '\0') && (now = timer_ticks(), now - spaceship_wnd_open_ticks_i32 < 0x4b1)) {
    return;
  }
  wnd_end_modal_loop((ModalMenuWindow *)spaceship_wnd);
  return;
}
#undef net_host_handoff_stage
#undef spaceship_wnd_open_ticks_i32

/* 004d01ae auto */
#define i (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl spaceship_wnd_load_parts(iptr civ)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (i = 0; i < 6; i++) {
    *(int *)(&spaceship_wnd_part_counts + i * 4) =
         (int)civs[civ].spaceship_parts[i];
  }
  return;
}
#undef i

/* 004d0208 auto */
#define council_active (*(char *)((u8 *)&g.d_00631ad0))
#define civ (*(int *)(frame_ + FRAME_OFF(4)))
#define window (*(SpaceshipWindow (*)[2])(frame_ + FRAME_OFF(16)))
#define eh_next (*(i32 *)(frame_ + FRAME_OFF(8584)))
#define eh_handler (*(i8 * *)(frame_ + FRAME_OFF(8588)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(8592)))
i32 __cdecl spaceship_wnd_run(iptr civ_arg)

{
  i32 result;
  int init_ok;
  i32 ret_addr;
  i8 frame_[FRAME_OFF(8600)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  if (spaceship_wnd == 0) {
    if (council_active == '\0') {
      if (civ_arg < 1) {
        civ = ~civ_arg + 1;
      }
      else {
        civ = civ_arg;
      }
      ret_addr = 0x4d0293;
      spaceship_wnd_ctor(window,civ);
      eh_state = 0;
      init_ok = spaceship_wnd_init(window);
      if (init_ok == 0) {
        eh_state = 0xffffffff;
        /* inlined unwind funclet 004d0314 */ { spaceship_wnd_dtor((SpaceshipWindowDtorView *)((iptr)&window)); }
        result = 0;
      }
      else {
        if (civ_arg < 0) {
          spaceship_wnd_launch_sequence(window);
        }
        else {
          spaceship_wnd_run_modal(window);
        }
        eh_state = 0xffffffff;
        /* inlined unwind funclet 004d0314 */ { spaceship_wnd_dtor((SpaceshipWindowDtorView *)((iptr)&window)); }
        result = 1;
      }
    }
    else {
      result = 1;
    }
  }
  else {
    result = 1;
  }
  return result;
}
#undef council_active
#undef civ
#undef window
#undef eh_next
#undef eh_handler
#undef eh_state

/* 004d0339 auto */
#define council_active (*(char *)((u8 *)&g.d_00631ad0))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define window (*(SpaceshipWindow (*)[2])(frame_ + FRAME_OFF(0)))
#define eh_next (*(i32 *)(frame_ + FRAME_OFF(8568)))
#define eh_handler (*(i8 * *)(frame_ + FRAME_OFF(8572)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(8576)))
i32 __cdecl spaceship_wnd_show_for_civ(iptr civ)

{
  i32 result;
  int init_ok;
  i32 ret_addr;
  i8 frame_[FRAME_OFF(8584)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  if (human_civ == civ) {
    if (spaceship_wnd == 0) {
      if (council_active == '\0') {
        ret_addr = 0x4d03b3;
        spaceship_wnd_ctor(window,civ);
        eh_state = 0;
        init_ok = spaceship_wnd_init(window);
        if (init_ok == 0) {
          eh_state = 0xffffffff;
          /* inlined unwind funclet 004d041a */ { spaceship_wnd_dtor((SpaceshipWindowDtorView *)((iptr)&window)); }
          result = 0;
        }
        else {
          spaceship_wnd_present(window);
          eh_state = 0xffffffff;
          /* inlined unwind funclet 004d041a */ { spaceship_wnd_dtor((SpaceshipWindowDtorView *)((iptr)&window)); }
          result = 1;
        }
      }
      else {
        result = 1;
      }
    }
    else {
      result = 1;
    }
  }
  else {
    result = 0;
  }
  return result;
}
#undef council_active
#undef human_civ
#undef window
#undef eh_next
#undef eh_handler
#undef eh_state

/* 004d043f auto */
#define rect (*(tagRECT *)(frame_ + FRAME_OFF(4)))
void __cdecl spaceship_wnd_draw_title(iptr civ)

{
  iptr text;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  text_clear();
  text = civ_name_plural(civ);
  text_append(text);
  text_buffer_char_1 = 0;
  text_append((iptr)((u8 *)&g.d_0062e2d4));
  text = civ_leader_name(civ);
  text_append(text);
  text_append_space();
  text_append((iptr)((u8 *)&g.d_0062e2dc));
  text = civ_get_adjective(civ);
  text_append(text);
  text_append((iptr)((u8 *)&g.d_0062e2e0));
  gfx_set_text_color_index(0xfa);
  SetRect(&rect,0,0,0x27f,0x28);
  surface_draw_text_in_rect
            ((DibSurface *)(spaceship_wnd + 0xb8),spaceship_wnd + 0x8c4,(iptr)((u8 *)&g.d_00679640),(iptr)&rect,
             0);
  win_flush_pending_msgs();
  return;
}
#undef rect

/* 004d0517 auto */
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
SpaceshipWindow * __thiscall spaceship_wnd_ctor(SpaceshipWindow *this,u32 civ)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  wnd_ctor((ModalMenuWindow *)this);
  eh_state = 0;
  surfwnd_ctor((SurfaceWindow *)&this->control_list);
  (*(i8 *)((char *)&eh_state + 0)) = 1;
  dll_handle_init((DllHandle *)(this->ship_dll));
  (*(i8 *)((char *)&eh_state + 0)) = 2;
  palette_init((GamePalette *)(this->ship_palette));
  (*(i8 *)((char *)&eh_state + 0)) = 3;
  font_init_empty((GameFont *)this->large_font);
  (*(i8 *)((char *)&eh_state + 0)) = 4;
  font_init_empty((GameFont *)(this->medium_font));
  (*(i8 *)((char *)&eh_state + 0)) = 5;
  font_init_empty((GameFont *)(this->typing_font));
  (*(i8 *)((char *)&eh_state + 0)) = 6;
  surface_ctor((DibSurface *)this->ship_view_surface);
  (*(i8 *)((char *)&eh_state + 0)) = 7;
  sprite_init((Sprite *)(this->ship_image_sprite));
  (*(i8 *)((char *)&eh_state + 0)) = 8;
  sprite_init((Sprite *)(this->close_btn_disabled_sprite));
  (*(i8 *)((char *)&eh_state + 0)) = 9;
  sprite_init((Sprite *)(this->close_btn_normal_sprite));
  (*(i8 *)((char *)&eh_state + 0)) = 10;
  sprite_init((Sprite *)(this->close_btn_pressed_sprite));
  (*(i8 *)((char *)&eh_state + 0)) = 0xb;
  sprite_init((Sprite *)(this->launch_btn_disabled_sprite));
  (*(i8 *)((char *)&eh_state + 0)) = 0xc;
  sprite_init((Sprite *)(this->launch_btn_normal_sprite));
  (*(i8 *)((char *)&eh_state + 0)) = 0xd;
  sprite_init((Sprite *)(this->launch_btn_pressed_sprite));
  (*(i8 *)((char *)&eh_state + 0)) = 0xe;
  clickmap_ctor(this->hotspot_map);
  eh_state = CONCAT31((*(i32 *)((char *)&eh_state + 1)),0xf);
  this->ship_civ = civ;
  this->anim_timer = 0;
  gfx_get_screen_rect((iptr)&this->frame_left);
  this->type_index = 0;
  spaceship_wnd = (iptr)this;
  font_set_styled((GameFont *)this->large_font,0,0x18,1);
  font_set_styled((GameFont *)(this->medium_font),0,0x14,1);
  font_set_styled((GameFont *)(this->typing_font),0,0x10,1);
  this->spaceship_state = 0;
  this->launched = 0;
  surface_create((DibSurface *)this->ship_view_surface,0x1c9,0x130);
  surface_fill((DibSurface *)this->ship_view_surface,9);
  this->flight_timer = 0;
  this->anim_timer = 0;
  this->blink_timer = 0;
  SetRect((LPRECT)this->ship_panel_rect,10,0x14,300,0x1df);
  ((CityViewWindow *)this)->launch_video_player[0] = '\0';
  ((CityViewWindow *)this)->launch_video_player_b1[0] = '\0';
  ((CityViewWindow *)this)->launch_video_player_b2[0] = '\0';
  ((CityViewWindow *)this)->launch_video_player_b3[0] = '\0';
  this->launch_state = 0;
  ((CityViewWindow *)this)->close_btn_pressed[0] = '\0';
  ((CityViewWindow *)this)->close_btn_pressed_b1[0] = '\0';
  ((CityViewWindow *)this)->close_btn_pressed_b2[0] = '\0';
  ((CityViewWindow *)this)->close_btn_pressed_b3[0] = '\0';
  ((CityViewWindow *)this)->launch_btn_pressed[0] = '\0';
  ((CityViewWindow *)this)->launch_btn_pressed_b1[0] = '\0';
  ((CityViewWindow *)this)->launch_btn_pressed_b2[0] = '\0';
  ((CityViewWindow *)this)->launch_btn_pressed_b3[0] = '\0';
  ((CityViewWindow *)this)->typing_label_part[0] = '\0';
  ((CityViewWindow *)this)->typing_label_part_b1[0] = '\0';
  ((CityViewWindow *)this)->typing_label_part_b2[0] = '\0';
  ((CityViewWindow *)this)->typing_label_part_b3[0] = '\0';
  return this;
}
#undef seh_prev
#undef seh_handler
#undef eh_state

/* 004d08b0 auto */
#define ret_value (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define eh_state (*(int *)(frame_ + FRAME_OFF(8)))
i32 __thiscall spaceship_wnd_dtor(SpaceshipWindowDtorView *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xf;
  dll_handle_free((DllHandle *)(this->art_dll_2));
  spaceship_wnd = 0;
  if (this->starfield_timer != 0) {
    game_timer_destroy(this->starfield_timer);
    this->starfield_timer = 0;
  }
  if (this->type_timer != 0) {
    game_timer_destroy(this->type_timer);
    this->type_timer = 0;
  }
  if (this->blink_timer != 0) {
    game_timer_destroy(this->blink_timer);
    this->blink_timer = 0;
  }
  (*(i8 *)((char *)&eh_state + 0)) = 0xe;
  /* inlined unwind funclet 004d0a56 */ { clickmap_dtor(*(int *)((iptr)&this) + 0xae4); }
  (*(i8 *)((char *)&eh_state + 0)) = 0xd;
  /* inlined unwind funclet 004d0a65 */ { sprite_destroy((Sprite *)(*(int *)((iptr)&this) + 0xaa4)); }
  (*(i8 *)((char *)&eh_state + 0)) = 0xc;
  /* inlined unwind funclet 004d0a74 */ { sprite_destroy((Sprite *)(*(int *)((iptr)&this) + 0xa68)); }
  (*(i8 *)((char *)&eh_state + 0)) = 0xb;
  /* inlined unwind funclet 004d0a83 */ { sprite_destroy((Sprite *)(*(int *)((iptr)&this) + 0xa2c)); }
  (*(i8 *)((char *)&eh_state + 0)) = 10;
  /* inlined unwind funclet 004d0a92 */ { sprite_destroy((Sprite *)(*(int *)((iptr)&this) + 0x9f0)); }
  (*(i8 *)((char *)&eh_state + 0)) = 9;
  /* inlined unwind funclet 004d0aa1 */ { sprite_destroy((Sprite *)(*(int *)((iptr)&this) + 0x9b4)); }
  (*(i8 *)((char *)&eh_state + 0)) = 8;
  /* inlined unwind funclet 004d0ab0 */ { sprite_destroy((Sprite *)(*(int *)((iptr)&this) + 0x978)); }
  (*(i8 *)((char *)&eh_state + 0)) = 7;
  /* inlined unwind funclet 004d0abf */ { sprite_destroy((Sprite *)(*(int *)((iptr)&this) + 0x93c)); }
  (*(i8 *)((char *)&eh_state + 0)) = 6;
  /* inlined unwind funclet 004d0ace */ { surface_dtor((DibSurface *)(*(int *)((iptr)&this) + 0x8f4)); }
  (*(i8 *)((char *)&eh_state + 0)) = 5;
  /* inlined unwind funclet 004d0add */ { font_destroy((GameFont *)(*(int *)((iptr)&this) + 0x8d4)); }
  (*(i8 *)((char *)&eh_state + 0)) = 4;
  /* inlined unwind funclet 004d0aec */ { font_destroy((GameFont *)(*(int *)((iptr)&this) + 0x8cc)); }
  (*(i8 *)((char *)&eh_state + 0)) = 3;
  /* inlined unwind funclet 004d0afb */ { font_destroy((GameFont *)(*(int *)((iptr)&this) + 0x8c4)); }
  (*(i8 *)((char *)&eh_state + 0)) = 2;
  /* inlined unwind funclet 004d0b0a */ { palette_destroy((GamePalette *)(*(int *)((iptr)&this) + 0x1f8)); }
  (*(i8 *)((char *)&eh_state + 0)) = 1;
  /* inlined unwind funclet 004d0b19 */ { dll_free((DllHandle *)(*(int *)((iptr)&this) + 500)); }
  eh_state = (uint)(*(i32 *)((char *)&eh_state + 1)) << 8;
  /* inlined unwind funclet 004d0b28 */ { surfwnd_dtor((SurfaceWindow *)(*(int *)((iptr)&this) + 0xb8)); }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 004d0b37 */ { wnd_dtor(*(WndBase **)((iptr)&this)); }
  return ret_value;
}
#undef ret_value
#undef seh_handler
#undef eh_state

/* 004d0b58 auto */
#define spaceship_success_pct (*(int *)((u8 *)&g.d_006ad0ec))
#define dll_path (*(i8 (*)[128])(frame_ + FRAME_OFF(4)))
i32 __thiscall spaceship_wnd_init(SpaceshipWindow *this)

{
  int status;
  i32 result;
  i8 frame_[FRAME_OFF(136)] __attribute__((aligned(8)));  /* original stack frame */
  
  str_clear((iptr)dll_path);
  str_append((iptr)dll_path,(iptr)((u8 *)&g.d_0062e2e4));
  status = file_resolve_path((iptr)dll_path);
  if (status == 0) {
    result = 0;
  }
  else {
    dll_handle_load((DllHandle *)(this->ship_dll),(iptr)dll_path);
    wnd_set_cursor((WndBase *)this,0x1fc);
    spaceship_calc_stats(this->ship_civ,1);
    spaceship_wnd_build_stats_text((PictureFrameWindow *)this);
    if ((civs[this->ship_civ].spaceship_parts[3] != 0) && (spaceship_success_pct != 0)) {
      this->launch_state = 1;
    }
    status = civ_spaceship_launched(this->ship_civ);
    if (status != 0) {
      this->launch_state = 3;
    }
    status = spaceship_wnd_create((PictureFrameWindow *)this);
    if (status == 0) {
      result = 0;
    }
    else {
      spaceship_wnd_make_button_sprites((WndBase *)this);
      if (this->flight_timer != 0) {
        game_timer_destroy(this->flight_timer);
        this->flight_timer = 0;
      }
      if (this->anim_timer != 0) {
        game_timer_destroy(this->anim_timer);
        this->anim_timer = 0;
      }
      if (this->blink_timer != 0) {
        game_timer_destroy(this->blink_timer);
        this->blink_timer = 0;
      }
      this->type_x = 10;
      this->type_y = 0x28;
      spaceship_wnd_setup_hotspots(this);
      result = 1;
    }
  }
  return result;
}
#undef spaceship_success_pct
#undef dll_path

/* 004d0d64 auto */
uint __thiscall spaceship_wnd_create(PictureFrameWindow *this)

{
  int loaded;
  
  win_flush_pending_msgs();
  wnd_create_with_handlers
            ((WndBase *)this,(iptr)((u8 *)&g.d_0062e2ec),0x800,this->frame_left,this->frame_top,
             this->frame_right - this->frame_left,(this->frame_bottom - this->frame_top) + 5,(iptr)((u8 *)&g.d_006a8c00),
             (iptr)((u8 *)&g.d_006553d8));
  wnd_set_bg_color((WndBase *)this,0);
  wnd_create_with_surface
            ((DibSurface *)&this->control_list,(iptr)((u8 *)&g.d_0062e2f0),0x800,0,0,0x280,0x1e0,
             (iptr)(this->ship_palette),(iptr)this);
  loaded = surface_load_gif_resource
                    ((DibSurface *)&this->control_list,499,10,0xec,(iptr)(this->ship_palette));
  if (loaded != 0) {
    wnd_center((WndCenterView *)(this->frame_wnd_base));
    wnd_set_keydown_handler((WndEventHandlers *)(this->frame_handlers),(iptr)spaceship_wnd_on_key);
    wnd_set_mousemove_handler((WndHandlersMouseSetView *)(this->frame_handlers),(iptr)spaceship_wnd_on_mousemove);
    wnd_set_lbuttondown_handler((WndHandlersMouseSetView *)(this->frame_handlers),(iptr)spaceship_wnd_on_lbuttondown);
    wnd_set_lbuttonup_any_handler((WndHandlersMouseSetView *)(this->frame_handlers),(iptr)spaceship_wnd_on_lbuttonup);
  }
  return (uint)(loaded != 0);
}

/* 004d0ea6 auto */
#define spaceship_wnd_open_ticks_i32 (*(i32 *)((u8 *)&g.d_006a5b08))
#define clip_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define launch_sprite (*(Sprite *)(frame_ + FRAME_OFF(20)))
#define launch_surface (*(DibSurface *)(frame_ + FRAME_OFF(80)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(152)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(156)))
#define eh_state (*(int *)(frame_ + FRAME_OFF(160)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall spaceship_wnd_run_modal(SpaceshipWindow *this)

{
  int rendered;
  u32 timer;
  i8 frame_[FRAME_OFF(168)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  surface_ctor(&launch_surface);
  eh_state = 0;
  sprite_init(&launch_sprite);
  (*(i8 *)((char *)&eh_state + 0)) = 1;
  spaceship_wnd_load_parts(this->ship_civ);
  rendered = spaceship_wnd_render_ship(this);
  if (rendered == 0) {
    eh_state = (uint)(*(i32 *)((char *)&eh_state + 1)) << 8;
    /* inlined unwind funclet 004d138b */ { sprite_destroy((Sprite *)((iptr)&launch_sprite)); }
    eh_state = 0xffffffff;
    /* inlined unwind funclet 004d1397 */ { surface_dtor((DibSurface *)((iptr)&launch_surface)); }
  }
  else {
    if (this->launch_state == 3) {
      surface_load_gif_resource
                (&launch_surface,spaceship_wnd_component_count + 19999,10,0xec,(iptr)(this->ship_palette));
      sprite_grab_from_surface
                (&launch_sprite,(iptr)&launch_surface,0xff,
                 *(i32 *)(&spaceship_launch_sprite_xs + (spaceship_wnd_component_count - 1) * 0x10),
                 *(i32 *)(&spaceship_launch_sprite_ys + (spaceship_wnd_component_count - 1) * 0x10),
                 *(i32 *)(&spaceship_launch_sprite_widths + (spaceship_wnd_component_count - 1) * 0x10),
                 *(i32 *)(&spaceship_part_sprite_heights + (spaceship_wnd_component_count - 1) * 0x10));
      sprite_draw
                (&launch_sprite,(iptr)clip_rect,(iptr)&this->control_list,
                 *(i32 *)(&spaceship_launch_sprite_xs + (spaceship_wnd_component_count - 1) * 0x10),
                 *(i32 *)(&spaceship_launch_sprite_ys + (spaceship_wnd_component_count - 1) * 0x10));
    }
    switch(this->launch_state) {
    case 0:
    case 1:
      spaceship_wnd_draw_launch_btn(this,0,1);
      break;
    case 2:
      break;
    case 3:
      spaceship_wnd_init_starfield(this);
      spaceship_wnd_draw_title(this->ship_civ);
    }
    spaceship_wnd_draw_close_btn(this,1,1);
    if (this->anim_timer != 0) {
      game_timer_destroy(this->anim_timer);
    }
    if (this->launch_state == 3) {
      timer = game_timer_create((iptr)spaceship_wnd_starfield_tick,5,0xffffffff);
      this->flight_timer = timer;
    }
    else {
      timer = game_timer_create((iptr)spaceship_wnd_type_tick,0x3c,0xffffffff);
      this->anim_timer = timer;
    }
    wnd_handle_show_raise((WndBase *)this);
    wnd_flush_paint();
    wnd_set_palette((WndBase *)this,(iptr)(this->ship_palette));
    window_show((WindowObjectView *)&this->control_list);
    wnd_flush_paint();
    wnd_set_palette((WndBase *)&main_frame_wnd,(iptr)(this->ship_palette));
    spaceship_wnd_setup_hotspots(this);
    spaceship_wnd_draw_buttons(this);
    if (this->launch_state == 3) {
      this->launched = 1;
    }
    else {
      this->launched = 0;
    }
    ((CityViewWindow *)this)->typing_label_part[0] = 1;
    ((CityViewWindow *)this)->typing_label_part_b1[0] = '\0';
    ((CityViewWindow *)this)->typing_label_part_b2[0] = '\0';
    ((CityViewWindow *)this)->typing_label_part_b3[0] = '\0';
    wnd_set_capture((WndBase *)(this->frame_wnd_base));
    input_flush_events();
    if (2 < game.multiplayer) {
      wnd_set_modal_idle_callback((ModalMenuWindow *)(this->frame_wnd_base),(iptr)spaceship_wnd_net_idle);
    }
    spaceship_wnd_open_ticks_i32 = timer_ticks();
    wnd_run_modal_loop((ModalMenuWindow *)(this->frame_wnd_base));
    wnd_set_modal_idle_callback((ModalMenuWindow *)(this->frame_wnd_base),0);
    wnd_release_capture((WndBase *)(this->frame_wnd_base));
    if (this->flight_timer != 0) {
      game_timer_destroy(this->flight_timer);
      this->flight_timer = 0;
    }
    if (this->anim_timer != 0) {
      game_timer_destroy(this->anim_timer);
      this->anim_timer = 0;
    }
    if (this->blink_timer != 0) {
      game_timer_destroy(this->blink_timer);
      this->blink_timer = 0;
    }
    if (this->launch_state == 2) {
      spaceship_play_launch_video((WndBase *)this);
      this->launch_state = 3;
      spaceship_launch(this->ship_civ);
      spaceship_wnd_run_modal(this);
    }
    else {
      wnd_hide((WndBase *)(this->frame_wnd_base));
      wnd_flush_paint();
    }
    wnd_set_palette((WndBase *)&main_frame_wnd,(iptr)((u8 *)&g.d_006a8c00));
    wnd_set_palette((WndBase *)this,(iptr)((u8 *)&g.d_006a8c00));
    wnd_hide((WndBase *)this);
    wnd_flush_paint();
    eh_state = (uint)(*(i32 *)((char *)&eh_state + 1)) << 8;
    /* inlined unwind funclet 004d138b */ { sprite_destroy((Sprite *)((iptr)&launch_sprite)); }
    eh_state = 0xffffffff;
    /* inlined unwind funclet 004d1397 */ { surface_dtor((DibSurface *)((iptr)&launch_surface)); }
  }
  return;
}
#undef spaceship_wnd_open_ticks_i32
#undef clip_rect
#undef launch_sprite
#undef launch_surface
#undef seh_prev
#undef seh_handler
#undef eh_state

/* 004d13b8 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define spaceship_wnd_open_ticks_i32 (*(i32 *)((u8 *)&g.d_006a5b08))
#define screen_rect2 (*(tagRECT *)(frame_ + FRAME_OFF(4)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall spaceship_wnd_present(SpaceshipWindow *this)

{
  int rendered;
  u32 value;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (this->ship_civ == human_civ) {
    if (this->anim_timer != 0) {
      game_timer_destroy(this->anim_timer);
    }
    if ((this->launch_state != 3) && (rendered = spaceship_wnd_render_ship(this), rendered != 0)) {
      spaceship_wnd_draw_close_btn(this,1,1);
      spaceship_wnd_draw_launch_btn(this,0,1);
      ((CityViewWindow *)this)->typing_label_part[0] = 1;
      ((CityViewWindow *)this)->typing_label_part_b1[0] = '\0';
      ((CityViewWindow *)this)->typing_label_part_b2[0] = '\0';
      ((CityViewWindow *)this)->typing_label_part_b3[0] = '\0';
      wnd_handle_show_raise((WndBase *)this);
      wnd_flush_paint();
      wnd_set_palette((WndBase *)this,(iptr)(this->ship_palette));
      window_show((WindowObjectView *)&this->control_list);
      wnd_flush_paint();
      wnd_set_palette((WndBase *)&main_frame_wnd,(iptr)(this->ship_palette))
      ;
      spaceship_wnd_setup_hotspots(this);
      spaceship_wnd_draw_buttons(this);
      this->launched = 1;
      ((CityViewWindow *)this)->typing_label_part[0] = 1;
      ((CityViewWindow *)this)->typing_label_part_b1[0] = '\0';
      ((CityViewWindow *)this)->typing_label_part_b2[0] = '\0';
      ((CityViewWindow *)this)->typing_label_part_b3[0] = '\0';
      value = this->launch_state;
      this->launch_state = 0;
      this->launch_state = value;
      spaceship_wnd_load_parts(this->ship_civ);
      rendered = spaceship_wnd_render_ship(this);
      if (rendered != 0) {
        spaceship_wnd_draw_close_btn(this,1,0);
        spaceship_wnd_draw_launch_btn(this,0,1);
        SetRect(&screen_rect2,0,0,0x280,0x1e0);
        gfx_dissolve_blit((iptr)&this->control_list,(iptr)&screen_rect2,5,1);
        spaceship_wnd_draw_close_btn(this,1,1);
        value = game_timer_create((iptr)spaceship_wnd_type_tick,10,0xffffffff);
        this->anim_timer = value;
        spaceship_wnd_setup_hotspots(this);
        spaceship_wnd_draw_buttons(this);
        this->launched = 0;
        ((CityViewWindow *)this)->typing_label_part[0] = 1;
        ((CityViewWindow *)this)->typing_label_part_b1[0] = '\0';
        ((CityViewWindow *)this)->typing_label_part_b2[0] = '\0';
        ((CityViewWindow *)this)->typing_label_part_b3[0] = '\0';
        wnd_set_capture((WndBase *)(this->frame_wnd_base));
        input_flush_events();
        if (2 < game.multiplayer) {
          wnd_set_modal_idle_callback((ModalMenuWindow *)(this->frame_wnd_base),(iptr)spaceship_wnd_net_idle);
        }
        spaceship_wnd_open_ticks_i32 = timer_ticks();
        wnd_run_modal_loop((ModalMenuWindow *)(this->frame_wnd_base));
        wnd_set_modal_idle_callback((ModalMenuWindow *)(this->frame_wnd_base),0);
        wnd_release_capture((WndBase *)(this->frame_wnd_base));
        if (this->flight_timer != 0) {
          game_timer_destroy(this->flight_timer);
          this->flight_timer = 0;
        }
        if (this->anim_timer != 0) {
          game_timer_destroy(this->anim_timer);
          this->anim_timer = 0;
        }
        if (this->blink_timer != 0) {
          game_timer_destroy(this->blink_timer);
          this->blink_timer = 0;
        }
        wnd_set_palette((WndBase *)&main_frame_wnd,(iptr)((u8 *)&g.d_006a8c00));
        if (this->launch_state == 2) {
          spaceship_play_launch_video((WndBase *)this);
          this->launch_state = 3;
          spaceship_launch(this->ship_civ);
          spaceship_wnd_run_modal(this);
        }
        else {
          wnd_hide((WndBase *)(this->frame_wnd_base));
          wnd_flush_paint();
        }
        wnd_set_palette((WndBase *)this,(iptr)((u8 *)&g.d_006a8c00));
        wnd_hide((WndBase *)this);
        wnd_flush_paint();
      }
    }
  }
  return;
}
#undef human_civ
#undef spaceship_wnd_open_ticks_i32
#undef screen_rect2

/* 004d1725 auto */
void __thiscall spaceship_wnd_launch_sequence(SpaceshipWindow *this)

{
  wnd_handle_show_raise((WndBase *)this);
  wnd_flush_paint();
  wnd_set_palette((WndBase *)&main_frame_wnd,(iptr)(this->ship_palette));
  wnd_set_palette((WndBase *)this,(iptr)(this->ship_palette));
  this->launch_state = 2;
  spaceship_play_launch_video((WndBase *)this);
  this->launch_state = 3;
  spaceship_wnd_run_modal(this);
  wnd_set_palette((WndBase *)&main_frame_wnd,(iptr)((u8 *)&g.d_006a8c00));
  wnd_set_palette((WndBase *)this,(iptr)((u8 *)&g.d_006a8c00));
  wnd_hide((WndBase *)this);
  wnd_flush_paint();
  return;
}

/* 004d17bf: written by hand in src/game/bigframes.c */

/* 004d4a7b auto */
#define spaceship_energy_pct (*(i32 *)((u8 *)&g.d_006ad0e8))
#define spaceship_fuel_pct (*(i32 *)((u8 *)&g.d_006ad0dc))
#define spaceship_success_pct (*(i32 *)((u8 *)&g.d_006ad0ec))
#define spaceship_support_pct (*(i32 *)((u8 *)&g.d_006ad0f0))
#define part_index (*(int *)(frame_ + FRAME_OFF(4)))
void __thiscall spaceship_wnd_build_stats_text(PictureFrameWindow *this)

{
  short part_count;
  bool over_limit;
  int part_limit;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  over_limit = false;
  str_clear((iptr)this->stats_text);
  for (part_index = 0; part_index < 6; part_index++) {
    part_count = civs[(this->ship_civ)].spaceship_parts[part_index];
    part_limit = spaceship_part_limit(this->ship_civ,part_index);
    if (part_limit < part_count) {
      over_limit = true;
    }
  }
  for (part_index = 0; part_index < 6; part_index++) {
    str_append_string_id((iptr)this->stats_text,
                       *(i32 *)(label_string_ids + *(int *)(&spaceship_part_table + part_index * 0xc) * 4))
    ;
    str_append_colon((iptr)this->stats_text);
    str_append_int((iptr)this->stats_text,
                       (int)civs[(this->ship_civ)].spaceship_parts[part_index]);
    if ((over_limit) && (part_index == 0)) {
      str_append((iptr)this->stats_text,(iptr)((u8 *)&g.d_0062e2f4));
    }
    str_append((iptr)this->stats_text,(iptr)((u8 *)&g.d_0062e2f8));
  }
  str_append_label((iptr)this->stats_text,0x22);
  str_append_colon((iptr)this->stats_text);
  str_append_int((iptr)this->stats_text,(int)civs[this->ship_civ].spaceship_parts[3]);
  str_append((iptr)this->stats_text,(iptr)((u8 *)&g.d_0062e2fc));
  str_append((iptr)this->stats_text,(iptr)((u8 *)&g.d_0062e304));
  str_append_label((iptr)this->stats_text,0x42);
  str_append_colon((iptr)this->stats_text);
  str_append_int((iptr)this->stats_text,spaceship_support_pct);
  str_append_percent((iptr)this->stats_text);
  str_append((iptr)this->stats_text,(iptr)((u8 *)&g.d_0062e308));
  str_append_label((iptr)this->stats_text,0xcd);
  str_append_colon((iptr)this->stats_text);
  str_append_int((iptr)this->stats_text,spaceship_energy_pct);
  str_append_percent((iptr)this->stats_text);
  str_append((iptr)this->stats_text,(iptr)((u8 *)&g.d_0062e30c));
  str_append_label((iptr)this->stats_text,0xce);
  str_append_colon((iptr)this->stats_text);
  str_append_int((iptr)this->stats_text,spaceship_mass / 10);
  str_append((iptr)this->stats_text,(iptr)((u8 *)&g.d_0062e310));
  str_append_int((iptr)this->stats_text,spaceship_mass % 10);
  str_append((iptr)this->stats_text,(iptr)((u8 *)&g.d_0062e314));
  str_append_label((iptr)this->stats_text,0xd1);
  str_append((iptr)this->stats_text,(iptr)((u8 *)&g.d_0062e318));
  str_append_label((iptr)this->stats_text,200);
  str_append_colon((iptr)this->stats_text);
  str_append_int((iptr)this->stats_text,spaceship_fuel_pct);
  str_append_percent((iptr)this->stats_text);
  if ((civs[this->ship_civ].spaceship_flags & 8) != 0) {
    str_append_space((iptr)this->stats_text);
    str_append_lparen((iptr)this->stats_text);
    str_append_label((iptr)this->stats_text,0xeb);
    str_append_rparen((iptr)this->stats_text);
  }
  str_append((iptr)this->stats_text,(iptr)((u8 *)&g.d_0062e31c));
  str_append_label((iptr)this->stats_text,0xcf);
  str_append_colon((iptr)this->stats_text);
  str_append_int((iptr)this->stats_text,spaceship_flight_time / 10);
  str_append((iptr)this->stats_text,(iptr)((u8 *)&g.d_0062e320));
  str_append_int((iptr)this->stats_text,spaceship_flight_time % 10);
  str_append_space((iptr)this->stats_text);
  str_append_label((iptr)this->stats_text,0xd2);
  str_clear((iptr)(((SpaceshipWindow *)this)->success_text));
  str_append_label((iptr)(((SpaceshipWindow *)this)->success_text),0xd0);
  str_append_colon((iptr)(((SpaceshipWindow *)this)->success_text));
  str_append_space((iptr)(((SpaceshipWindow *)this)->success_text));
  str_append_int((iptr)(((SpaceshipWindow *)this)->success_text),spaceship_success_pct);
  str_append_percent((iptr)(((SpaceshipWindow *)this)->success_text));
  win_flush_pending_msgs();
  return;
}
#undef spaceship_energy_pct
#undef spaceship_fuel_pct
#undef spaceship_success_pct
#undef spaceship_support_pct
#undef part_index

/* 004d4fd1 auto */
#define spaceship_success_pct (*(int *)((u8 *)&g.d_006ad0ec))
#define char_buf (*(u8 (*)[4])(frame_ + FRAME_OFF(0)))
#define dirty_rect (*(tagRECT *)(frame_ + FRAME_OFF(4)))
uint __thiscall spaceship_wnd_type_char(SpaceshipWindow *this,int allow_skip)

{
  int metric;
  uint result;
  i32 font_handle;
  int char_width;
  u32 timer;
  u8 *char_ptr;
  int yBottom;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((allow_skip == 0) || (metric = rand_range(0,1), metric == 0)) {
    font_handle = font_get_handle((GameFont *)(this->typing_font));
    metric = font_measure_height(font_handle);
    win_flush_pending_msgs();
    char_buf[0] = this->stats_text[this->type_index];
    char_buf[1] = 0;
    gfx_set_text_color_index(0xf9);
    if (*(int *)(((CityViewWindow *)this)->typing_label_part) == 0) {
      gfx_set_text_color_index(0xfe);
    }
    else {
      gfx_set_text_color_index(0xf9);
    }
    surface_draw_text
              ((DibSurface *)&this->control_list,(iptr)(this->typing_font),(iptr)char_buf,
               this->type_x,this->type_y,1);
    yBottom = this->type_y + metric * 2;
    char_ptr = char_buf;
    font_handle = font_get_handle((GameFont *)(this->typing_font));
    char_width = font_measure_width(font_handle,(iptr)char_ptr);
    SetRect(&dirty_rect,this->type_x,this->type_y - metric,this->type_x + char_width,yBottom);
    char_ptr = char_buf;
    font_handle = font_get_handle((GameFont *)(this->typing_font));
    metric = font_measure_width(font_handle,(iptr)char_ptr);
    this->type_x += metric;
    if (this->stats_text[this->type_index] == ':') {
      ((CityViewWindow *)this)->typing_label_part[0] = '\0';
      ((CityViewWindow *)this)->typing_label_part_b1[0] = '\0';
      ((CityViewWindow *)this)->typing_label_part_b2[0] = '\0';
      ((CityViewWindow *)this)->typing_label_part_b3[0] = '\0';
    }
    this->type_index++;
    while (this->stats_text[this->type_index] == '\n') {
      ((CityViewWindow *)this)->typing_label_part[0] = 1;
      ((CityViewWindow *)this)->typing_label_part_b1[0] = '\0';
      ((CityViewWindow *)this)->typing_label_part_b2[0] = '\0';
      ((CityViewWindow *)this)->typing_label_part_b3[0] = '\0';
      this->type_x = 10;
      font_handle = font_get_handle((GameFont *)(this->typing_font));
      metric = font_measure_height(font_handle);
      this->type_y += metric;
      this->type_index++;
    }
    if (this->stats_text[this->type_index] == '\0') {
      if (this->anim_timer != 0) {
        game_timer_destroy(this->anim_timer);
        this->anim_timer = 0;
      }
      if (this->launch_state != 3) {
        SetRect((LPRECT)(this->status_line_rect),0,0x1c1,0x27f,0x1df);
        rect_offset((iptr)(this->status_line_rect),1,1);
        gfx_set_text_color_index(10);
        surface_draw_text_in_rect
                  ((DibSurface *)&this->control_list,(iptr)(this->medium_font),
                   (iptr)(this->success_text),(iptr)(this->status_line_rect),0);
        rect_offset((iptr)(this->status_line_rect),0xffffffff,0xffffffff);
        if (spaceship_success_pct < 0x28) {
          gfx_set_text_color_index(0xf9);
        }
        else if (spaceship_success_pct < 0x4b) {
          gfx_set_text_color_index(0xfb);
        }
        else {
          gfx_set_text_color_index(0xfa);
        }
        surface_draw_text_in_rect
                  ((DibSurface *)&this->control_list,(iptr)(this->medium_font),
                   (iptr)(this->success_text),(iptr)(this->status_line_rect),0);
        wnd_blit_surface_rect
                  ((DibSurface *)&this->control_list,(iptr)(this->status_line_rect));
        wnd_flush_paint();
      }
      if (this->launch_state == 1) {
        timer = game_timer_create((iptr)spaceship_wnd_blink_launch_btn,500,0xffffffff);
        this->blink_timer = timer;
      }
      this->launched = 1;
    }
    wnd_blit_surface_rect((DibSurface *)&this->control_list,(iptr)&dirty_rect);
    result = (uint)(this->stats_text[this->type_index] != '\0');
  }
  else {
    result = 1;
  }
  return result;
}
#undef spaceship_success_pct
#undef char_buf
#undef dirty_rect

/* 004d53ab: written by hand in src/game/unwind.c */

/* 004d570b auto */
#define clip_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define star (*(int *)(frame_ + FRAME_OFF(16)))
#define star_y (*(int *)(frame_ + FRAME_OFF(20)))
#define star_x (*(int *)(frame_ + FRAME_OFF(24)))
#define fill_rect (*(tagRECT *)(frame_ + FRAME_OFF(28)))
void __thiscall spaceship_wnd_init_starfield(SpaceshipWindow *this)

{
  u8 *star_depth;
  i32 rand_val;
  int value;
  int xRight;
  iptr label;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (star = 0; star < 0x50; star++) {
    rand_val = rand_range(0xffff8300,32000);
    *(i32 *)(((ThroneRoomWindow *)this)->starfield_stars + star * 0xc + 0x31c) = rand_val;
    rand_val = rand_range(0xffffa240,24000);
    *(i32 *)(((ThroneRoomWindow *)this)->starfield_stars + star * 0xc + 800) = rand_val;
    rand_val = rand_range(1,100);
    *(i32 *)(((ThroneRoomWindow *)this)->starfield_stars + star * 0xc + 0x324) = rand_val;
  }
  value = surface_get_height((DibSurface *)&this->control_list);
  xRight = surface_get_width((DibSurface *)&this->control_list);
  SetRect(&fill_rect,0,0x14,xRight,value);
  surface_fill_rect((DibSurface *)&this->control_list,(iptr)&fill_rect,10);
  for (star = 0; star < 0x50; star++) {
    star_x = *(int *)(((ThroneRoomWindow *)this)->starfield_stars + star * 0xc + 0x31c) /
               *(int *)(((ThroneRoomWindow *)this)->starfield_stars + star * 0xc + 0x324) + 0x140;
    star_y = *(int *)(((ThroneRoomWindow *)this)->starfield_stars + star * 0xc + 800) /
               *(int *)(((ThroneRoomWindow *)this)->starfield_stars + star * 0xc + 0x324) + 0xf0;
    if ((((0x280 < star_x) || (star_x < 0)) || (0x1e0 < star_y)) || (star_y < 0)) {
      rand_val = rand_range(0xffff8300,32000);
      *(i32 *)(((ThroneRoomWindow *)this)->starfield_stars + star * 0xc + 0x31c) = rand_val;
      rand_val = rand_range(0xffffa240,24000);
      *(i32 *)(((ThroneRoomWindow *)this)->starfield_stars + star * 0xc + 800) = rand_val;
      star_depth = ((ThroneRoomWindow *)this)->starfield_stars + star * 0xc + 0x324;
      star_depth[0] = 'd';
      star_depth[1] = '\0';
      star_depth[2] = '\0';
      star_depth[3] = '\0';
      star_x = *(int *)(((ThroneRoomWindow *)this)->starfield_stars + star * 0xc + 0x31c) /
                 *(int *)(((ThroneRoomWindow *)this)->starfield_stars + star * 0xc + 0x324) + 0x140;
      star_y = *(int *)(((ThroneRoomWindow *)this)->starfield_stars + star * 0xc + 800) /
                 *(int *)(((ThroneRoomWindow *)this)->starfield_stars + star * 0xc + 0x324) + 0xf0;
    }
    surface_set_pixel((DibSurface *)&this->control_list,star_x,star_y,0x29);
  }
  this->type_index = 0;
  this->type_x = 10;
  this->type_y = 0x73;
  ((CityViewWindow *)this)->typing_label_part[0] = 1;
  ((CityViewWindow *)this)->typing_label_part_b1[0] = '\0';
  ((CityViewWindow *)this)->typing_label_part_b2[0] = '\0';
  ((CityViewWindow *)this)->typing_label_part_b3[0] = '\0';
  do {
    value = spaceship_wnd_type_char(this,0);
  } while (value != 0);
  str_clear((iptr)(this->success_text));
  label = label_string(*(i32 *)(label_string_ids + 0x718));
  str_append((iptr)(this->success_text),label);
  str_append_colon((iptr)(this->success_text));
  str_append_space((iptr)(this->success_text));
  str_append_year((iptr)(this->success_text),(int)civs[this->ship_civ].spaceship_arrival_year
                    );
  SetRect((LPRECT)(this->status_line_rect),0,0x1c1,0x27f,0x1df);
  rect_offset((iptr)(this->status_line_rect),1,1);
  gfx_set_text_color_index(10);
  surface_draw_text_in_rect
            ((DibSurface *)&this->control_list,(iptr)(this->medium_font),
             (iptr)(this->success_text),(iptr)(this->status_line_rect),0);
  rect_offset((iptr)(this->status_line_rect),0xffffffff,0xffffffff);
  gfx_set_text_color_index(0xfa);
  surface_draw_text_in_rect
            ((DibSurface *)&this->control_list,(iptr)(this->medium_font),
             (iptr)(this->success_text),(iptr)(this->status_line_rect),0);
  wnd_blit_surface_rect((DibSurface *)&this->control_list,(iptr)(this->status_line_rect));
  sprite_draw
            ((Sprite *)(this->ship_image_sprite),(iptr)clip_rect,(iptr)&this->control_list,0xaf,99);
  if (this->launch_state == 3) {
    this->type_y = 0x8c;
  }
  return;
}
#undef clip_rect
#undef star
#undef star_y
#undef star_x
#undef fill_rect

/* 004d5b21 auto */
#define player (*(u32 *)(frame_ + FRAME_OFF(4)))
#define video_path (*(i8 (*)[128])(frame_ + FRAME_OFF(12)))
#define open_result (*(int *)(frame_ + FRAME_OFF(140)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(144)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(148)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(152)))
void __thiscall spaceship_play_launch_video(WndBase *this)

{
  DocumentWindow *this_00;
  int found;
  i8 frame_[FRAME_OFF(160)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  snd_cd_stop();
  this_00 = operator_new(0xa28);
  eh_state = 0;
  if (this_00 == (DocumentWindow *)0x0) {
    player = 0;
  }
  else {
    player = mmwnd_ctor(this_00);
  }
  eh_state = 0xffffffff;
  (*(u32 *)&((CityViewWindow *)this)->launch_video_player) = player;
  str_clear((iptr)video_path);
  str_append((iptr)video_path,(iptr)((u8 *)&g.d_0062e334));
  found = file_resolve_path((iptr)video_path);
  if (found != 0) {
    avi_player_create((MediaWindow *)(*(u32 *)&((CityViewWindow *)this)->launch_video_player),(iptr)((u8 *)&g.d_0062e34c),0x800,0,0);
    avi_player_set_double_size((MediaWindow *)(*(u32 *)&((CityViewWindow *)this)->launch_video_player),1);
    open_result = avi_player_open((AviPlayerOpenView *)(*(u32 *)&((CityViewWindow *)this)->launch_video_player),(iptr)video_path);
    if (open_result != 0) {
      if (open_result == -0x7ffbfeac) {
        popup_game((iptr)((u8 *)&g.d_0062e350));
      }
      goto LAB_004d5e33;
    }
    wnd_hide(this + 0x10);
    wnd_flush_paint();
    surface_fill((DibSurface *)(*(u32 *)&((CityViewWindow *)this)->launch_video_player),0);
    wnd_set_lbuttonup_handler((WndEventHandlers *)((*(u32 *)&((CityViewWindow *)this)->launch_video_player) + 0x58),(iptr)spaceship_video_on_lbuttonup);
    wnd_set_keydown_handler((WndEventHandlers *)((*(u32 *)&((CityViewWindow *)this)->launch_video_player) + 0x58),(iptr)spaceship_wnd_on_key);
    avi_player_set_end_callback((AviPlayerEndCbSetView *)(*(u32 *)&((CityViewWindow *)this)->launch_video_player),(iptr)spaceship_video_on_end);
    wnd_center((WndCenterView *)((*(u32 *)&((CityViewWindow *)this)->launch_video_player) + 0x48));
    wnd_blit_surface((DibSurface *)(*(u32 *)&((CityViewWindow *)this)->launch_video_player));
    window_show((WindowObjectView *)(*(u32 *)&((CityViewWindow *)this)->launch_video_player));
    wnd_flush_paint();
    avi_player_play((AviPlayerPlayView *)(*(u32 *)&((CityViewWindow *)this)->launch_video_player));
    input_flush_events();
    wnd_set_capture((WndBase *)((*(u32 *)&((CityViewWindow *)this)->launch_video_player) + 0x48));
    if (2 < game.multiplayer) {
      wnd_set_modal_idle_callback((ModalMenuWindow *)((*(u32 *)&((CityViewWindow *)this)->launch_video_player) + 0x48),(iptr)net_modal_idle_poll);
    }
    wnd_run_modal_loop((ModalMenuWindow *)((*(u32 *)&((CityViewWindow *)this)->launch_video_player) + 0x48));
    wnd_set_modal_idle_callback((ModalMenuWindow *)((*(u32 *)&((CityViewWindow *)this)->launch_video_player) + 0x48),0);
    wnd_release_capture((WndBase *)((*(u32 *)&((CityViewWindow *)this)->launch_video_player) + 0x48));
    wnd_hide((WndBase *)((*(u32 *)&((CityViewWindow *)this)->launch_video_player) + 0x48));
    wnd_flush_paint();
  }
  if ((AviPlayer *)(*(u32 *)&((CityViewWindow *)this)->launch_video_player) != (AviPlayer *)0x0) {
    avi_player_scalar_dtor((AviPlayer *)(*(u32 *)&((CityViewWindow *)this)->launch_video_player),1);
  }
  (*(u32 *)&((CityViewWindow *)this)->launch_video_player) = 0;
  snd_sync_music_option();
LAB_004d5e33:
  return;
}
#undef player
#undef video_path
#undef open_result
#undef seh_prev
#undef seh_handler
#undef eh_state

/* 004d5e41 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
void __thiscall spaceship_wnd_setup_hotspots(SpaceshipWindow *this)

{
  clickmap_clear((ClickMapClearView *)this->hotspot_map);
  if (((this->ship_civ == human_civ) && (this->launch_state != 3)) && (this->launch_state != 0)) {
    clickmap_add_xywh((ClickMap *)this->hotspot_map,0,0x1f5,0x1a1,0x34,0x24);
    clickmap_add_xywh((ClickMap *)this->hotspot_map,1,0x22f,0x1a1,0x43,0x24);
  }
  else {
    clickmap_add_xywh((ClickMap *)this->hotspot_map,0,0x22f,0x1a1,0x43,0x24);
  }
  return;
}
#undef human_civ

/* 004d5ef9 auto */
#define btn_rect (*(tagRECT *)(frame_ + FRAME_OFF(4)))
void __thiscall spaceship_wnd_draw_buttons(SpaceshipWindow *this)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((this->launch_state != 1) && (this->launch_state != 0)) {
    SetRect(&btn_rect,0x1f5,0x1a1,0x229,0x1c5);
    surface_fill_rect((DibSurface *)&this->control_list,(iptr)&btn_rect,0);
  }
  spaceship_wnd_draw_close_btn(this,1,1);
  spaceship_wnd_draw_launch_btn(this,0,1);
  return;
}
#undef btn_rect

/* 004d5f79 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define pressed_clip (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define normal_clip (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
#define disabled_clip (*(i8 (*)[16])(frame_ + FRAME_OFF(36)))
#define btn_rect (*(tagRECT *)(frame_ + FRAME_OFF(52)))
void __thiscall spaceship_wnd_draw_close_btn(SpaceshipWindow *this,int enabled,int raised)

{
  i8 frame_[FRAME_OFF(72)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((this->ship_civ == human_civ) && (this->launch_state != 3)) && (this->launch_state != 0)) {
    SetRect(&btn_rect,0x1f5,0x1a1,0x229,0x1c5);
  }
  else {
    SetRect(&btn_rect,0x22f,0x1a1,0x272,0x1c5);
  }
  if (raised == 0) {
    sprite_draw
              ((Sprite *)(this->close_btn_disabled_sprite),(iptr)disabled_clip,(iptr)&this->control_list,
               btn_rect.left,btn_rect.top);
  }
  else if (enabled == 0) {
    sprite_draw
              ((Sprite *)(this->close_btn_pressed_sprite),(iptr)pressed_clip,(iptr)&this->control_list,
               btn_rect.left,btn_rect.top);
  }
  else {
    sprite_draw
              ((Sprite *)(this->close_btn_normal_sprite),(iptr)normal_clip,(iptr)&this->control_list,
               btn_rect.left,btn_rect.top);
  }
  wnd_blit_surface_rect((DibSurface *)&this->control_list,(iptr)&btn_rect);
  wnd_flush_paint();
  return;
}
#undef human_civ
#undef pressed_clip
#undef normal_clip
#undef disabled_clip
#undef btn_rect

/* 004d60a5 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define pressed_clip (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define normal_clip (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
#define disabled_clip (*(i8 (*)[16])(frame_ + FRAME_OFF(36)))
#define btn_rect (*(tagRECT *)(frame_ + FRAME_OFF(52)))
void __thiscall spaceship_wnd_draw_launch_btn(SpaceshipWindow *this,int enabled,int raised)

{
  i8 frame_[FRAME_OFF(72)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((((this->ship_civ == human_civ) && (this->launch_state != 3)) && (this->launch_state != 0)) &&
     (this->launch_state != 2)) {
    SetRect(&btn_rect,0x22f,0x1a1,0x272,0x1c5);
    if (raised == 0) {
      sprite_draw
                ((Sprite *)(this->launch_btn_disabled_sprite),(iptr)disabled_clip,(iptr)&this->control_list,
                 btn_rect.left,btn_rect.top);
    }
    else if (enabled == 0) {
      sprite_draw
                ((Sprite *)(this->launch_btn_pressed_sprite),(iptr)pressed_clip,(iptr)&this->control_list,
                 btn_rect.left,btn_rect.top);
    }
    else {
      sprite_draw
                ((Sprite *)(this->launch_btn_normal_sprite),(iptr)normal_clip,(iptr)&this->control_list,
                 btn_rect.left,btn_rect.top);
    }
    wnd_blit_surface_rect((DibSurface *)&this->control_list,(iptr)&btn_rect);
    wnd_flush_paint();
  }
  return;
}
#undef human_civ
#undef pressed_clip
#undef normal_clip
#undef disabled_clip
#undef btn_rect

/* 004d61c3 auto */
#define hotspot_id (*(int *)(frame_ + FRAME_OFF(0)))
#define ship_wnd (*(SpaceshipWindow * *)(frame_ + FRAME_OFF(4)))
#define active_wnd (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl spaceship_video_on_lbuttonup(i32 x,i32 y)

{
  int hit;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  active_wnd = wnd_get_active_child();
  if (active_wnd == 0) {
    active_wnd = 0;
  }
  else {
    active_wnd -= 0x48;
  }
  ship_wnd = (SpaceshipWindow *)spaceship_wnd;
  if (*(int *)(spaceship_wnd + 0xae0) == 2) {
    wnd_end_modal_loop((ModalMenuWindow *)(*(int *)(spaceship_wnd + 0x1da8) + 0x48));
  }
  else {
    hit = clickmap_hit_test
                      ((ClickMapHitTestView *)(spaceship_wnd + 0xae4),x,y,(iptr)&hotspot_id,0);
    if (hit != -1) {
      if (hotspot_id == 0) {
        spaceship_wnd_draw_close_btn(ship_wnd,1,0);
        if (ship_wnd->launched == 0) {
          if (ship_wnd->anim_timer != 0) {
            game_timer_destroy(ship_wnd->anim_timer);
            ship_wnd->anim_timer = 0;
          }
          if (ship_wnd->launch_state != 3) {
            do {
              hit = spaceship_wnd_type_char(ship_wnd,0);
            } while (hit != 0);
            ship_wnd->launched = 1;
            spaceship_wnd_draw_close_btn(ship_wnd,1,1);
          }
        }
        else {
          wnd_end_modal_loop((ModalMenuWindow *)(active_wnd + 0x48));
        }
      }
      else if (((hotspot_id == 1) && (ship_wnd->launch_state == 1)) && (ship_wnd->launched != 0)) {
        spaceship_wnd_draw_launch_btn(ship_wnd,1,0);
        ship_wnd->launch_state = 2;
        wnd_end_modal_loop((ModalMenuWindow *)(active_wnd + 0x48));
      }
    }
  }
  return;
}
#undef hotspot_id
#undef ship_wnd
#undef active_wnd

/* 004d6367 auto */
void __cdecl spaceship_wnd_type_tick(void)

{
  spaceship_wnd_type_char((SpaceshipWindow *)spaceship_wnd,1);
  return;
}

/* 004d6384 auto */
void __cdecl spaceship_wnd_blink_launch_btn(void)

{
  iptr this;
  
  this = spaceship_wnd;
  if (*(int *)(spaceship_wnd + 0x8ec) == 0) {
    *(i32 *)(spaceship_wnd + 0x8ec) = 1;
  }
  else {
    *(i32 *)(spaceship_wnd + 0x8ec) = 0;
  }
  if (*(int *)(this + 0x8ec) == 0) {
    spaceship_wnd_draw_launch_btn((SpaceshipWindow *)this,1,1);
  }
  else {
    spaceship_wnd_draw_launch_btn((SpaceshipWindow *)this,0,1);
  }
  return;
}

/* 004d63fb auto */
#define star (*(int *)(frame_ + FRAME_OFF(4)))
#define new_y (*(int *)(frame_ + FRAME_OFF(8)))
#define new_x (*(int *)(frame_ + FRAME_OFF(12)))
void __cdecl spaceship_wnd_starfield_tick(void)

{
  int *coord_ptr;
  int old_x;
  int old_y;
  i32 rand_val;
  int pixel;
  iptr ship_wnd;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  ship_wnd = spaceship_wnd;
  win_flush_pending_msgs();
  for (star = 0; star < 0x50; star++) {
    old_x = *(int *)(ship_wnd + 0x1db8 + star * 0xc) / *(int *)(ship_wnd + 0x1dc0 + star * 0xc) +
            0x140;
    old_y = *(int *)(ship_wnd + 0x1dbc + star * 0xc) / *(int *)(ship_wnd + 0x1dc0 + star * 0xc) +
            0xf0;
    coord_ptr = (int *)(ship_wnd + 0x1db8 + star * 0xc);
    *coord_ptr = *coord_ptr + 0xfa;
    coord_ptr = (int *)(ship_wnd + 0x1dbc + star * 0xc);
    *coord_ptr = *coord_ptr + 300;
    coord_ptr = (int *)(ship_wnd + 0x1dc0 + star * 0xc);
    *coord_ptr = *coord_ptr - 1;
    if (*(int *)(ship_wnd + 0x1dc0 + star * 0xc) == 0) {
      rand_val = rand_range(0xffff8300,32000);
      *(i32 *)(ship_wnd + 0x1db8 + star * 0xc) = rand_val;
      rand_val = rand_range(0xffffa240,24000);
      *(i32 *)(ship_wnd + 0x1dbc + star * 0xc) = rand_val;
      rand_val = rand_range(0x32,100);
      *(i32 *)(ship_wnd + 0x1dc0 + star * 0xc) = rand_val;
    }
    new_x = *(int *)(ship_wnd + 0x1db8 + star * 0xc) / *(int *)(ship_wnd + 0x1dc0 + star * 0xc)
               + 0x140;
    new_y = *(int *)(ship_wnd + 0x1dbc + star * 0xc) / *(int *)(ship_wnd + 0x1dc0 + star * 0xc)
               + 0xf0;
    if ((((0x280 < new_x) || (new_x < 0)) || (0x1e0 < new_y)) || (new_y < 0)) {
      rand_val = rand_range(0xffff8300,32000);
      *(i32 *)(ship_wnd + 0x1db8 + star * 0xc) = rand_val;
      rand_val = rand_range(0xffffa240,24000);
      *(i32 *)(ship_wnd + 0x1dbc + star * 0xc) = rand_val;
      rand_val = rand_range(0x32,100);
      *(i32 *)(ship_wnd + 0x1dc0 + star * 0xc) = rand_val;
      new_x = *(int *)(ship_wnd + 0x1db8 + star * 0xc) /
                 *(int *)(ship_wnd + 0x1dc0 + star * 0xc) + 0x140;
      new_y = *(int *)(ship_wnd + 0x1dbc + star * 0xc) /
                 *(int *)(ship_wnd + 0x1dc0 + star * 0xc) + 0xf0;
    }
    if (((old_x < 0x280) && (0 < old_x)) && ((old_y < 0x1e0 && (0 < old_y)))) {
      pixel = surface_get_pixel((DibSurface *)(ship_wnd + 0xb8),old_x,old_y);
      if (pixel == 0x29) {
        surface_set_pixel((DibSurface *)(ship_wnd + 0xb8),old_x,old_y,10);
      }
    }
    if (((new_x < 0x280) && (0 < new_x)) && ((new_y < 0x1e0 && (0 < new_y)))) {
      old_x = surface_get_pixel((DibSurface *)(ship_wnd + 0xb8),new_x,new_y);
      if (old_x == 10) {
        surface_set_pixel((DibSurface *)(ship_wnd + 0xb8),new_x,new_y,0x29);
      }
    }
  }
  wnd_blit_surface((DibSurface *)(ship_wnd + 0xb8));
  return;
}
#undef star
#undef new_y
#undef new_x

/* 004d6744 auto */
#define active_wnd (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl spaceship_wnd_on_key(int key)

{
  iptr this;
  int more;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  active_wnd = wnd_get_active_child();
  this = spaceship_wnd;
  if (active_wnd == 0) {
    active_wnd = 0;
  }
  else {
    active_wnd -= 0x48;
  }
  if ((0xcf < key) && (key < 0xd3)) {
    if (*(int *)(spaceship_wnd + 0xae0) == 2) {
      wnd_end_modal_loop((ModalMenuWindow *)(*(int *)(spaceship_wnd + 0x1da8) + 0x48));
    }
    else {
      spaceship_wnd_draw_close_btn((SpaceshipWindow *)spaceship_wnd,1,0);
      if (*(int *)(this + 0x8f0) == 0) {
        if (*(int *)(this + 0x62c) != 0) {
          game_timer_destroy(*(i32 *)(this + 0x62c));
          *(i32 *)(this + 0x62c) = 0;
        }
        do {
          more = spaceship_wnd_type_char((SpaceshipWindow *)this,0);
        } while (more != 0);
        *(i32 *)(this + 0x8f0) = 1;
        spaceship_wnd_draw_close_btn((SpaceshipWindow *)this,1,1);
      }
      else {
        wnd_end_modal_loop((ModalMenuWindow *)(active_wnd + 0x48));
      }
    }
  }
  return;
}
#undef active_wnd

/* 004d686b auto */
void __cdecl spaceship_video_on_end(void)

{
  if (*(int *)(spaceship_wnd + 0x1da8) != 0) {
    wnd_end_modal_loop((ModalMenuWindow *)(*(int *)(spaceship_wnd + 0x1da8) + 0x48));
  }
  return;
}

/* 004d68a7 auto */
#define hotspot_id (*(int *)(frame_ + FRAME_OFF(4)))
#define ship_wnd (*(SpaceshipWindow * *)(frame_ + FRAME_OFF(8)))
void __cdecl spaceship_wnd_on_lbuttondown(i32 x,i32 y)

{
  int hit;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  ship_wnd = (SpaceshipWindow *)spaceship_wnd;
  if (((*(int *)(spaceship_wnd + 0x1db0) == 0) && (*(int *)(spaceship_wnd + 0x1dac) == 0)) &&
     (hit = clickmap_hit_test
                        ((ClickMapHitTestView *)(spaceship_wnd + 0xae4),x,y,(iptr)&hotspot_id,0),
     hit != -1)) {
    if (hotspot_id == 0) {
      ((CityViewWindow *)ship_wnd)->close_btn_pressed[0] = 1;
      ((CityViewWindow *)ship_wnd)->close_btn_pressed_b1[0] = '\0';
      ((CityViewWindow *)ship_wnd)->close_btn_pressed_b2[0] = '\0';
      ((CityViewWindow *)ship_wnd)->close_btn_pressed_b3[0] = '\0';
      spaceship_wnd_draw_close_btn(ship_wnd,1,0);
      if ((ship_wnd->launch_state == 1) && (ship_wnd->blink_timer != 0)) {
        game_timer_destroy(ship_wnd->blink_timer);
        ship_wnd->blink_timer = 0;
      }
      wnd_blit_surface((DibSurface *)&ship_wnd->control_list);
    }
    else if (((hotspot_id == 1) && (ship_wnd->launch_state == 1)) && (ship_wnd->launched != 0)) {
      ((CityViewWindow *)ship_wnd)->launch_btn_pressed[0] = 1;
      ((CityViewWindow *)ship_wnd)->launch_btn_pressed_b1[0] = '\0';
      ((CityViewWindow *)ship_wnd)->launch_btn_pressed_b2[0] = '\0';
      ((CityViewWindow *)ship_wnd)->launch_btn_pressed_b3[0] = '\0';
      spaceship_wnd_draw_launch_btn(ship_wnd,1,0);
      if ((ship_wnd->launch_state == 1) && (ship_wnd->blink_timer != 0)) {
        game_timer_destroy(ship_wnd->blink_timer);
        ship_wnd->blink_timer = 0;
      }
      wnd_blit_surface((DibSurface *)&ship_wnd->control_list);
    }
  }
  return;
}
#undef hotspot_id
#undef ship_wnd

/* 004d6a30 auto */
#define hotspot_id (*(int *)(frame_ + FRAME_OFF(0)))
#define ship_wnd (*(SpaceshipWindow * *)(frame_ + FRAME_OFF(4)))
#define active_wnd (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl spaceship_wnd_on_lbuttonup(i32 x,i32 y)

{
  int hit;
  u32 timer;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  ship_wnd = (SpaceshipWindow *)spaceship_wnd;
  active_wnd = wnd_get_active_child();
  if (active_wnd == 0) {
    active_wnd = 0;
  }
  else {
    active_wnd -= 0x48;
  }
  if (ship_wnd->launch_state == 2) {
    wnd_end_modal_loop((ModalMenuWindow *)(*(int *)(((CityViewWindow *)ship_wnd)->launch_video_player) + 0x48));
  }
  else if ((*(int *)(((CityViewWindow *)ship_wnd)->launch_btn_pressed) != 0) ||
          (*(int *)(((CityViewWindow *)ship_wnd)->close_btn_pressed) != 0)) {
    if (*(int *)(((CityViewWindow *)ship_wnd)->close_btn_pressed) != 0) {
      spaceship_wnd_draw_close_btn(ship_wnd,1,1);
    }
    if (*(int *)(((CityViewWindow *)ship_wnd)->launch_btn_pressed) != 0) {
      spaceship_wnd_draw_launch_btn(ship_wnd,1,1);
    }
    hit = clickmap_hit_test
                      ((ClickMapHitTestView *)ship_wnd->hotspot_map,x,y,(iptr)&hotspot_id,0);
    if (hit != -1) {
      if (hotspot_id == 0) {
        if (*(int *)(((CityViewWindow *)ship_wnd)->close_btn_pressed) != 0) {
          if (ship_wnd->launched == 0) {
            if (ship_wnd->anim_timer != 0) {
              game_timer_destroy(ship_wnd->anim_timer);
              ship_wnd->anim_timer = 0;
            }
            if (ship_wnd->launch_state != 3) {
              do {
                hit = spaceship_wnd_type_char(ship_wnd,0);
              } while (hit != 0);
              ship_wnd->launched = 1;
            }
          }
          else {
            wnd_end_modal_loop((ModalMenuWindow *)(active_wnd + 0x48));
          }
        }
      }
      else if ((hotspot_id == 1) && (*(int *)(((CityViewWindow *)ship_wnd)->launch_btn_pressed) != 0)) {
        ship_wnd->launch_state = 2;
        wnd_end_modal_loop((ModalMenuWindow *)(active_wnd + 0x48));
      }
    }
    if (((*(int *)(((CityViewWindow *)ship_wnd)->close_btn_pressed) != 0) &&
        (((CityViewWindow *)ship_wnd)->close_btn_pressed[0] = '\0', ((CityViewWindow *)ship_wnd)->close_btn_pressed_b1[0] = '\0',
        ((CityViewWindow *)ship_wnd)->close_btn_pressed_b2[0] = '\0', ((CityViewWindow *)ship_wnd)->close_btn_pressed_b3[0] = '\0', ship_wnd->launch_state == 1)
        ) && (ship_wnd->blink_timer == 0)) {
      timer = game_timer_create((iptr)spaceship_wnd_blink_launch_btn,500,0xffffffff);
      ship_wnd->blink_timer = timer;
    }
    if (((*(int *)(((CityViewWindow *)ship_wnd)->launch_btn_pressed) != 0) &&
        (((CityViewWindow *)ship_wnd)->launch_btn_pressed[0] = '\0', ((CityViewWindow *)ship_wnd)->launch_btn_pressed_b1[0] = '\0',
        ((CityViewWindow *)ship_wnd)->launch_btn_pressed_b2[0] = '\0', ((CityViewWindow *)ship_wnd)->launch_btn_pressed_b3[0] = '\0', ship_wnd->launch_state == 1)
        ) && (ship_wnd->blink_timer == 0)) {
      timer = game_timer_create((iptr)spaceship_wnd_blink_launch_btn,500,0xffffffff);
      ship_wnd->blink_timer = timer;
    }
  }
  return;
}
#undef hotspot_id
#undef ship_wnd
#undef active_wnd

/* 004d6cbc auto */
#define hotspot_id (*(int *)(frame_ + FRAME_OFF(4)))
#define ship_wnd (*(SpaceshipWindow * *)(frame_ + FRAME_OFF(8)))
void __cdecl spaceship_wnd_on_mousemove(i32 x,i32 y)

{
  int hit;
  u32 timer;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  ship_wnd = (SpaceshipWindow *)spaceship_wnd;
  hit = clickmap_hit_test
                    ((ClickMapHitTestView *)(spaceship_wnd + 0xae4),x,y,(iptr)&hotspot_id,0);
  if (hit == -1) {
    if (((*(int *)(((CityViewWindow *)ship_wnd)->close_btn_pressed) != 0) &&
        (spaceship_wnd_draw_close_btn(ship_wnd,1,1), ship_wnd->launch_state == 1)) &&
       (ship_wnd->blink_timer == 0)) {
      timer = game_timer_create((iptr)spaceship_wnd_blink_launch_btn,500,0xffffffff);
      ship_wnd->blink_timer = timer;
    }
    if (((*(int *)(((CityViewWindow *)ship_wnd)->launch_btn_pressed) != 0) &&
        (spaceship_wnd_draw_launch_btn(ship_wnd,1,1), ship_wnd->launch_state == 1)) &&
       (ship_wnd->blink_timer == 0)) {
      timer = game_timer_create((iptr)spaceship_wnd_blink_launch_btn,500,0xffffffff);
      ship_wnd->blink_timer = timer;
    }
  }
  else if (hotspot_id == 0) {
    if (*(int *)(((CityViewWindow *)ship_wnd)->launch_btn_pressed) == 0) {
      if (((*(int *)(((CityViewWindow *)ship_wnd)->close_btn_pressed) != 0) &&
          (spaceship_wnd_draw_close_btn(ship_wnd,1,0), ship_wnd->launch_state == 1)) &&
         (ship_wnd->blink_timer != 0)) {
        game_timer_destroy(ship_wnd->blink_timer);
        ship_wnd->blink_timer = 0;
      }
    }
    else {
      spaceship_wnd_draw_launch_btn(ship_wnd,1,1);
      if ((ship_wnd->launch_state == 1) && (ship_wnd->blink_timer == 0)) {
        timer = game_timer_create((iptr)spaceship_wnd_blink_launch_btn,500,0xffffffff);
        ship_wnd->blink_timer = timer;
      }
    }
  }
  else if (hotspot_id == 1) {
    if (*(int *)(((CityViewWindow *)ship_wnd)->close_btn_pressed) == 0) {
      if (((*(int *)(((CityViewWindow *)ship_wnd)->launch_btn_pressed) != 0) &&
          (spaceship_wnd_draw_launch_btn(ship_wnd,1,0), ship_wnd->launch_state == 1)) &&
         (ship_wnd->blink_timer != 0)) {
        game_timer_destroy(ship_wnd->blink_timer);
        ship_wnd->blink_timer = 0;
      }
    }
    else {
      spaceship_wnd_draw_close_btn(ship_wnd,1,1);
      if ((ship_wnd->launch_state == 1) && (ship_wnd->blink_timer == 0)) {
        timer = game_timer_create((iptr)spaceship_wnd_blink_launch_btn,500,0xffffffff);
        ship_wnd->blink_timer = timer;
      }
    }
  }
  return;
}
#undef hotspot_id
#undef ship_wnd

/* 00596b00 auto */
#define limit (*(iptr *)(frame_ + FRAME_OFF(0)))
iptr __cdecl spaceship_part_limit(iptr civ,int part)

{
  int structurals;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  limit = (&spaceship_part_max_counts)[part * 3];
  if ((part == 1) || (part == 2)) {
    structurals = (civs[civ].spaceship_parts[0] + 1) - (part * 2 - 2);
    limit = int_clamp(limit,0,(int)(structurals + (structurals >> 0x1f & 3U)) >> 2);
  }
  else if (part != 0) {
    structurals = (civs[civ].spaceship_parts[0] + 1) - (part * 4 - 0xc);
    limit = int_clamp(limit,0,(int)(structurals + (structurals >> 0x1f & 7U)) >> 3);
    if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
      limit = int_clamp(limit,0,1);
    }
    if (limit < 0) {
      limit = 0;
    }
  }
  return limit;
}
#undef limit

/* 00596c08 auto */
i32 __cdecl spaceship_part_count(iptr civ,int part)

{
  short built;
  i32 result;
  
  built = civs[civ].spaceship_parts[part];
  result = spaceship_part_limit(civ,part);
  result = int_clamp((int)built,0,result);
  return result;
}

/* 00596c61 auto */
int __cdecl spaceship_group_limit(iptr civ,int group)

{
  int total;
  int limit_a;
  int limit_b;
  
  if (group == 0) {
    total = spaceship_part_limit(civ,0);
  }
  else if (group == 1) {
    limit_a = spaceship_part_limit(civ,2);
    total = spaceship_part_limit(civ,1);
    total += limit_a;
  }
  else {
    limit_a = spaceship_part_limit(civ,3);
    limit_b = spaceship_part_limit(civ,4);
    total = spaceship_part_limit(civ,5);
    total = total + limit_a + limit_b;
  }
  return total;
}

/* 00596ced auto */
int __cdecl spaceship_group_max(int group)

{
  int max_count;
  
  max_count = spaceship_part_max_counts;
  if (group != 0) {
    if (group == 1) {
      max_count = spaceship_fuel_max + spaceship_propulsion_max;
    }
    else {
      max_count = spaceship_solar_panel_max + spaceship_habitation_max + spaceship_life_support_max;
    }
  }
  return max_count;
}

/* 00596d3c auto */
int __cdecl spaceship_group_count(iptr civ,iptr group)

{
  int count;
  
  if (group == 0) {
    count = (int)civs[civ].spaceship_parts[0];
  }
  else if (group == 1) {
    count = (int)civs[civ].spaceship_parts[1] + (int)civs[civ].spaceship_parts[2];
  }
  else {
    count = (int)civs[civ].spaceship_parts[3] + (int)civs[civ].spaceship_parts[4] +
            (int)civs[civ].spaceship_parts[5];
  }
  return count;
}

/* 00596e06 auto */
int __cdecl spaceship_group_count_clamped(iptr civ,int group)

{
  int total;
  int count_a;
  int count_b;
  
  if (group == 0) {
    total = spaceship_part_count(civ,0);
  }
  else if (group == 1) {
    count_a = spaceship_part_count(civ,2);
    total = spaceship_part_count(civ,1);
    total += count_a;
  }
  else {
    count_a = spaceship_part_count(civ,3);
    count_b = spaceship_part_count(civ,4);
    total = spaceship_part_count(civ,5);
    total = total + count_a + count_b;
  }
  return total;
}

/* 00596e92 auto */
#define i (*(int *)(frame_ + FRAME_OFF(4)))
#define thrust (*(i32 *)(frame_ + FRAME_OFF(8)))
int __cdecl spaceship_component_thrust(int count)

{
  int next_thrust;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  thrust = 0;
  for (i = 0; i < count; i++) {
    next_thrust = thrust + 1;
    if (3 < i) {
      next_thrust = thrust + 2;
    }
    thrust = next_thrust;
    if (5 < i) {
      thrust++;
    }
  }
  return thrust;
}
#undef i
#undef thrust

/* 00596eec auto */
#define spaceship_energy_pct (*(int *)((u8 *)&g.d_006ad0e8))
#define spaceship_fuel_pct (*(int *)((u8 *)&g.d_006ad0dc))
#define spaceship_success_pct (*(int *)((u8 *)&g.d_006ad0ec))
#define spaceship_support_pct (*(int *)((u8 *)&g.d_006ad0f0))
#define part (*(int *)(frame_ + FRAME_OFF(4)))
#define full_mass (*(int *)(frame_ + FRAME_OFF(8)))
#define full_flight_time (*(int *)(frame_ + FRAME_OFF(12)))
#define flight_time (*(int *)(frame_ + FRAME_OFF(16)))
#define paradigm (*(uint *)(frame_ + FRAME_OFF(20)))
#define scale (*(int *)(frame_ + FRAME_OFF(24)))
void __cdecl spaceship_calc_stats(iptr civ,int apply_support)

{
  byte flags;
  int value;
  iptr part_count;
  int divisor;
  int temp;
  i32 arg_a;
  i32 arg_b;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  value = civ_spaceship_launched(civ);
  if (value == 0) {
    value = civ_has_advance(civ,0x20);
    if (value != 0) {
      civs[civ].spaceship_flags = civs[civ].spaceship_flags | 8;
    }
  }
  flags = civs[civ].spaceship_flags;
  spaceship_mass = 0;
  for (part = 0; part < 6; part++) {
    spaceship_mass = spaceship_mass +
                   (int)civs[civ].spaceship_parts[part] *
                   *(int *)(&spaceship_part_masses + part * 0xc);
  }
  full_mass = spaceship_mass;
  for (part = 0; part < 6; part++) {
    if (civs[civ].spaceship_parts[part] == 0) {
      full_mass += *(int *)(&spaceship_part_masses + part * 0xc);
    }
  }
  spaceship_success_pct = 100;
  value = spaceship_part_count(civ,4);
  arg_b = 99;
  arg_a = 1;
  part_count = spaceship_part_count(civ,3);
  divisor = int_clamp(part_count,arg_a,arg_b);
  spaceship_support_pct = (value * 100) / divisor;
  if (apply_support != 0) {
    value = int_clamp(spaceship_support_pct,0,100);
    spaceship_success_pct = (value * spaceship_success_pct) / 100;
  }
  value = spaceship_part_count(civ,5);
  arg_b = 99;
  arg_a = 1;
  divisor = spaceship_part_count(civ,3);
  temp = spaceship_part_count(civ,4);
  divisor = int_clamp(divisor + temp,arg_a,arg_b);
  spaceship_energy_pct = (value * 200) / divisor;
  value = int_clamp(spaceship_energy_pct,0,100);
  spaceship_success_pct = (value * spaceship_success_pct) / 100;
  value = spaceship_part_count(civ,2);
  arg_b = 99;
  arg_a = 1;
  part_count = spaceship_part_count(civ,1);
  divisor = int_clamp(part_count,arg_a,arg_b);
  spaceship_fuel_pct = (value * 100) / divisor;
  paradigm = (uint)cosmic.mass_thrust_paradigm;
  if ((flags & 8) != 0) {
    paradigm = (int)(paradigm * 3) >> 2;
  }
  scale = 1;
  for (; 100 < paradigm; paradigm = (int)paradigm >> 1) {
    scale = scale << 1;
  }
  temp = spaceship_mass * paradigm;
  arg_a = spaceship_part_count(civ,2);
  value = spaceship_component_thrust(arg_a);
  value = value * 10;
  arg_b = 0;
  arg_a = spaceship_part_count(civ,1);
  divisor = spaceship_component_thrust(arg_a);
  value = int_clamp(divisor * 10,arg_b,value);
  spaceship_flight_time = temp / (value + 1);
  arg_a = spaceship_part_count(civ,2);
  value = spaceship_component_thrust(arg_a);
  value = value * 10;
  arg_b = 0;
  arg_a = spaceship_part_count(civ,1);
  divisor = spaceship_component_thrust(arg_a);
  value = int_clamp(divisor * 10,arg_b,value);
  flight_time = (int)(paradigm * full_mass) / (value + 1);
  value = spaceship_component_thrust((int)civs[civ].spaceship_parts[2]);
  value = value * 10;
  arg_a = 0;
  divisor = spaceship_component_thrust((int)civs[civ].spaceship_parts[1]);
  value = int_clamp(divisor * 10,arg_a,value);
  full_flight_time = (int)(paradigm * full_mass) / (value + 1);
  if (1 < scale) {
    spaceship_flight_time = scale * spaceship_flight_time;
    flight_time = scale * flight_time;
    full_flight_time = scale * full_flight_time;
  }
  if (0x96 < spaceship_flight_time) {
    spaceship_success_pct -= (spaceship_flight_time - 0x96) / 10;
  }
  spaceship_success_pct = int_clamp(spaceship_success_pct,0,100);
  value = civ_spaceship_launched(civ);
  if (value == 0) {
    arg_a = spaceship_part_count(civ,3);
    civs[civ].spaceship_population = (i16)arg_a;
    arg_a = game_turn_to_year((int)game.turn);
    civs[civ].spaceship_launch_year = (i16)arg_a;
    arg_a = game_turn_to_year((int)game.turn);
    civs[civ].spaceship_arrival_year = (short)arg_a + (short)(flight_time / 10);
    value = game_turn_to_year((int)game.turn);
    spaceship_projected_arrival_year = value + full_flight_time / 10;
  }
  return;
}
#undef spaceship_energy_pct
#undef spaceship_fuel_pct
#undef spaceship_success_pct
#undef spaceship_support_pct
#undef part
#undef full_mass
#undef full_flight_time
#undef flight_time
#undef paradigm
#undef scale

/* 005973fd auto */
#define city (*(iptr *)(frame_ + FRAME_OFF(4)))
#define civ2 (*(iptr *)(frame_ + FRAME_OFF(8)))
void __cdecl spaceship_launch(iptr civ)

{
  uint *treaty;
  iptr name2;
  int launched;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  civs[civ].spaceship_flags = civs[civ].spaceship_flags | 2;
  if (game.first_launch_turn < 0) {
    game.first_launch_turn = game.turn;
  }
  name2 = civ_name_plural(civ);
  text_set_string_arg(0,name2);
  text_set_number_arg(0,(int)civs[civ].spaceship_arrival_year);
  if (2 < game.multiplayer) {
    net_send_text_args(0xb,0xff,1,1,civ,0);
  }
  if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
    popup_game((iptr)((u8 *)&g.d_00634fa8));
    spaceship_wnd_run(-civ);
  }
  if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
    for (city = 0; city < game.num_cities; city++) {
      if ((cities[city].id != 0) && (cities[city].owner == civ)) {
        city_set_production(city,99);
      }
    }
  }
  else {
    for (civ2 = 1; civ2 < 8; civ2++) {
      if ((((civ2 != civ) && ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) == 0))
          && (launched = civ_spaceship_launched(civ2), launched != 0)) &&
         (civs[civ].spaceship_arrival_year < civs[civ2].spaceship_arrival_year)) {
        if (game.difficulty < 4) {
          if ((game.difficulty < 2) || (civs[civ].reputation == '\0')) {
            diplo_set_treaty_flags(civ,civ2,0x10000);
          }
          else {
            treaty = (uint *)(civ * 4 + (iptr)((u8 *)&civs + 32) + civ2 * 0x594);
            *treaty = *treaty | 0x20;
          }
        }
        else if ((*(byte *)&civs[civ].treaties[civ2] & 8) == 0) {
          treaty = (uint *)(civ * 4 + (iptr)((u8 *)&civs + 32) + civ2 * 0x594);
          *treaty = *treaty & 0xffffffd9;
          treaty = (uint *)(civ * 4 + (iptr)((u8 *)&civs + 32) + civ2 * 0x594);
          *treaty = *treaty | 0x80840;
        }
        else {
          treaty = (uint *)(civ * 4 + (iptr)((u8 *)&civs + 32) + civ2 * 0x594);
          *treaty = *treaty | 0x20;
        }
      }
    }
  }
  return;
}
#undef city
#undef civ2

/* 0059772c auto */
#define spaceship_energy_pct (*(iptr *)((u8 *)&g.d_006ad0e8))
#define spaceship_fuel_pct (*(iptr *)((u8 *)&g.d_006ad0dc))
#define spaceship_success_pct (*(iptr *)((u8 *)&g.d_006ad0ec))
#define spaceship_support_pct (*(iptr *)((u8 *)&g.d_006ad0f0))
#define dlg (*(Dialog *)(frame_ + FRAME_OFF(4)))
#define part (*(int *)(frame_ + FRAME_OFF(760)))
#define over_limit (*(int *)(frame_ + FRAME_OFF(764)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(768)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(772)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(776)))
void __cdecl spaceship_status_dialog(iptr civ,int allow_launch)

{
  short part_count;
  iptr str;
  int result;
  i8 frame_[FRAME_OFF(784)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  dialog_ctor(&dlg,0x2000);
  eh_state = 0;
  over_limit = 0;
  spaceship_calc_stats(civ,1);
  if (civs[civ].spaceship_parts[3] == 0) {
    allow_launch = 0;
  }
  str = civ_get_adjective(civ);
  text_set_string_arg(2,str);
  str = civ_leader_name(civ);
  text_set_string_arg(1,str);
  str = civ_name_plural(civ);
  text_set_string_arg(0,str);
  text_string_args_plus1 = 0;
  __strupr(&text_string_args);
  dialog_load_game_text(&dlg,(iptr)((u8 *)&g.d_00634fb4));
  for (part = 0; part < 6; part++) {
    part_count = civs[civ].spaceship_parts[part];
    result = spaceship_part_limit(civ,part);
    if (result < part_count) {
      over_limit = 1;
    }
  }
  for (part = 0; part < 6; part++) {
    text_clear();
    text_append_string_id(*(i32 *)(label_string_ids + *(int *)(&spaceship_part_table + part * 0xc) * 4)
                      );
    text_append_colon();
    text_append_int((int)civs[civ].spaceship_parts[part]);
    if ((over_limit != 0) && (part == 0)) {
      text_append((iptr)((u8 *)&g.d_00634fc0));
    }
    dialog_add_option((DialogOptionList *)&dlg,(iptr)((u8 *)&g.d_00679640),0,0);
  }
  text_clear();
  dialog_add_option((DialogOptionList *)&dlg,(iptr)((u8 *)&g.d_00679640),0,0);
  text_clear();
  text_append_label(0x22);
  text_append_colon();
  text_append_int((int)civs[civ].spaceship_parts[3]);
  text_append((iptr)((u8 *)&g.d_00634fc4));
  dialog_add_option((DialogOptionList *)&dlg,(iptr)((u8 *)&g.d_00679640),0,0);
  text_clear();
  text_append_label(0x42);
  text_append_colon();
  text_append_int(spaceship_support_pct);
  text_append_percent();
  dialog_add_option((DialogOptionList *)&dlg,(iptr)((u8 *)&g.d_00679640),0,0);
  text_clear();
  text_append_label(0xcd);
  text_append_colon();
  text_append_int(spaceship_energy_pct);
  text_append_percent();
  dialog_add_option((DialogOptionList *)&dlg,(iptr)((u8 *)&g.d_00679640),0,0);
  text_clear();
  text_append_label(0xce);
  text_append_colon();
  text_append_int(spaceship_mass / 10);
  text_append((iptr)((u8 *)&g.d_00634fcc));
  text_append_int(spaceship_mass % 10);
  text_append((iptr)((u8 *)&g.d_00634fd0));
  text_append_label(0xd1);
  dialog_add_option((DialogOptionList *)&dlg,(iptr)((u8 *)&g.d_00679640),0,0);
  text_clear();
  text_append_label(200);
  text_append_colon();
  text_append_int(spaceship_fuel_pct);
  text_append_percent();
  if ((civs[civ].spaceship_flags & 8) != 0) {
    text_append_space();
    text_append_lparen();
    text_append_label(0xeb);
    text_append_rparen();
  }
  dialog_add_option((DialogOptionList *)&dlg,(iptr)((u8 *)&g.d_00679640),0,0);
  text_clear();
  text_append_label(0xcf);
  text_append_colon();
  text_append_int(spaceship_flight_time / 10);
  text_append((iptr)((u8 *)&g.d_00634fd4));
  text_append_int(spaceship_flight_time % 10);
  text_append_space();
  text_append_label(0xd2);
  dialog_add_option((DialogOptionList *)&dlg,(iptr)((u8 *)&g.d_00679640),0,0);
  text_clear();
  text_append_label(0xd0);
  text_append_colon();
  text_append((iptr)((u8 *)&g.d_00634fd8));
  text_append_int(spaceship_success_pct);
  text_append_percent();
  text_append((iptr)((u8 *)&g.d_00634fe0));
  dialog_add_option((DialogOptionList *)&dlg,(iptr)((u8 *)&g.d_00679640),0,0);
  result = civ_spaceship_launched(civ);
  if (result == 0) {
    if ((((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) && (allow_launch != 0)) &&
       (spaceship_success_pct != 0)) {
      str = label_string(*(i32 *)(label_string_ids + 0x354));
      dialog_add_button((DialogButtonsView *)&dlg,str);
    }
  }
  else {
    text_clear();
    text_append((iptr)((u8 *)&g.d_00634fe8));
    if (civs[civ].spaceship_arrival_year < game.year) {
      text_append_label(0xd4);
    }
    else {
      text_append_label(0xd3);
      text_append((iptr)((u8 *)&g.d_00634ff0));
      text_append_label(0xda);
      text_append_space();
      text_append_int((int)civs[civ].spaceship_arrival_year);
    }
    text_append((iptr)((u8 *)&g.d_00634ff4));
    dialog_add_option((DialogOptionList *)&dlg,(iptr)((u8 *)&g.d_00679640),0,0);
  }
  dlg_show_modal(&dlg,0);
  if (dlg.result_extra != 0) {
    text_set_number_arg(0,spaceship_success_pct);
    result = popup_game((iptr)((u8 *)&g.d_00634ffc));
    if (result != 0) {
      spaceship_launch(civ);
    }
  }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 00597d4b */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
  return;
}
#undef spaceship_energy_pct
#undef spaceship_fuel_pct
#undef spaceship_success_pct
#undef spaceship_support_pct
#undef dlg
#undef part
#undef over_limit
#undef seh_prev
#undef seh_handler
#undef eh_state

/* 00597d6f auto */
#define civ2 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define grp (*(int *)(frame_ + FRAME_OFF(4)))
iptr __cdecl spaceship_choose_part_group(iptr civ,iptr group)

{
  short earliest_arrival;
  bool race_close;
  bool chosen;
  int count;
  int limit;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  spaceship_calc_stats(civ,0);
  count = civ_spaceship_launched(civ);
  if (count != 0) {
    return 0xffffffff;
  }
  earliest_arrival = 9999;
  for (civ2 = 1; civ2 < 8; civ2++) {
    if ((((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) &&
        (0 < civs[civ2].spaceship_arrival_year)) &&
       (civs[civ2].spaceship_arrival_year < earliest_arrival)) {
      earliest_arrival = civs[civ2].spaceship_arrival_year;
    }
  }
  if (((civs[civ].spaceship_arrival_year == 0) ||
      (0xe < (int)civs[civ].spaceship_arrival_year - (int)game.year)) ||
     (earliest_arrival <= civs[civ].spaceship_arrival_year)) {
    race_close = false;
  }
  else {
    race_close = true;
  }
  chosen = false;
  if (group == 0) {
    count = spaceship_group_count_clamped(civ,2);
    limit = spaceship_group_limit(civ,2);
    if (count < limit) {
      chosen = true;
    }
    else if (!race_close) {
      count = spaceship_group_count_clamped(civ,1);
      limit = spaceship_group_limit(civ,1);
      if (count < limit) {
        chosen = true;
      }
    }
  }
  if ((!chosen) && ((group != 1 || (!race_close)))) {
    count = spaceship_group_count_clamped(civ,group);
    limit = spaceship_group_limit(civ,group);
    if ((count < limit) && (count = spaceship_group_can_build(civ,group), count != 0))
    goto LAB_0059803b;
  }
  for (grp = 2; (int)(uint)(group == 0) <= grp; grp--) {
    count = spaceship_group_can_build(civ,grp);
    if ((count != 0) && ((grp != 1 || (!race_close)))) {
      count = spaceship_group_count_clamped(civ,grp);
      limit = spaceship_group_limit(civ,grp);
      if (count < limit) {
        group = grp;
        break;
      }
    }
  }
LAB_0059803b:
  if (group == 0) {
    for (civ2 = 1; civ2 < 8; civ2++) {
      if (((((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) &&
           (count = civ_spaceship_launched(civ2), count != 0)) &&
          (civs[civ2].spaceship_arrival_year <= spaceship_projected_arrival_year)) &&
         ((count = spaceship_group_full(civ,1), count == 0 &&
          (count = civ_has_advance(civ,(int)improvements[0x24].preq), count != 0)))) {
        earliest_arrival = civs[civ].spaceship_parts[1];
        count = spaceship_part_limit(civ,1);
        if (earliest_arrival <= count) {
          return 1;
        }
        earliest_arrival = civs[civ].spaceship_parts[2];
        count = spaceship_part_limit(civ,2);
        if (earliest_arrival <= count) {
          return 1;
        }
      }
    }
  }
  count = spaceship_group_can_build(civ,group);
  if (count == 0) {
    group = -2;
  }
  return group;
}
#undef civ2
#undef grp

/* 00598197 auto */
#define spaceship_success_pct (*(int *)((u8 *)&g.d_006ad0ec))
#define civ2 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define part (*(int *)(frame_ + FRAME_OFF(8)))
#define civ3 (*(iptr *)(frame_ + FRAME_OFF(12)))
#define p (*(int *)(frame_ + FRAME_OFF(16)))
#define civ4 (*(iptr *)(frame_ + FRAME_OFF(20)))
int __cdecl spaceship_add_part(iptr civ,iptr group)

{
  short *part_ptr;
  short min_count;
  bool should_launch;
  int result;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  part = -1;
  spaceship_calc_stats(civ,0);
  result = civ_spaceship_launched(civ);
  if (result == 0) {
    while( true ) {
      if (group == 0) {
        if (spaceship_part_max_counts <= civs[civ].spaceship_parts[0]) {
          return part;
        }
        part = 0;
      }
      else if (group == 1) {
        if ((spaceship_propulsion_max <= civs[civ].spaceship_parts[1]) &&
           (spaceship_fuel_max <= civs[civ].spaceship_parts[2])) {
          return part;
        }
        if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
          if (civs[civ].spaceship_parts[1] < civs[civ].spaceship_parts[2]) {
            part = 1;
          }
          else {
            part = 2;
          }
        }
        else {
          text_set_number_arg(0,(int)civs[civ].spaceship_parts[1]);
          text_set_number_arg(1,(int)civs[civ].spaceship_parts[2]);
          part = popup_game((iptr)((u8 *)&g.d_00635004));
          part++;
        }
      }
      else {
        if (((spaceship_habitation_max <= civs[civ].spaceship_parts[3]) &&
            (spaceship_life_support_max <= civs[civ].spaceship_parts[4])) &&
           (spaceship_solar_panel_max <= civs[civ].spaceship_parts[5])) {
          return part;
        }
        if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
          min_count = 999;
          for (p = 3; p < 6; p++) {
            if (civs[civ].spaceship_parts[p] < min_count) {
              min_count = civs[civ].spaceship_parts[p];
              part = p;
            }
          }
        }
        else {
          text_set_number_arg(0,(int)civs[civ].spaceship_parts[3]);
          text_set_number_arg(1,(int)civs[civ].spaceship_parts[4]);
          text_set_number_arg(2,(int)civs[civ].spaceship_parts[5]);
          part = popup_game((iptr)((u8 *)&g.d_00635010));
          part += 3;
        }
      }
      if (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) ||
         ((int)civs[civ].spaceship_parts[part] < (&spaceship_part_max_counts)[part * 3]
         )) break;
      text_set_label_arg(0,*(i32 *)
                            (label_string_ids + *(int *)(&spaceship_part_table + part * 0xc) * 4));
      popup_game((iptr)((u8 *)&g.d_00635018));
    }
    result = civ_spaceship_exists(civ);
    if (result == 0) {
      civs[civ].spaceship_flags = civs[civ].spaceship_flags | 1;
      for (civ2 = 1; civ2 < 8; civ2++) {
        if (((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) &&
           ((civ2 == civ || (result = civ_spaceship_exists(civ2), result == 0)))) {
          for (civ3 = 1; civ3 < 8; civ3++) {
            civs[civ2].last_treaty_turn[civ3] = 0;
          }
        }
      }
    }
    part_ptr = (short *)(civ * 0x594 + (iptr)((u8 *)&civs + 1032) + part * 2);
    *part_ptr = *part_ptr + 1;
    spaceship_calc_stats(civ,0);
    if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
      should_launch = true;
      for (part = 0; part < 3; part++) {
        if ((int)civs[civ].spaceship_parts[part] <
            (&spaceship_part_max_counts)[part * 3]) {
          should_launch = false;
        }
      }
      result = civ_spaceship_launched(civ);
      if ((result == 0) && (0x27 < spaceship_success_pct)) {
        if (should_launch) {
          spaceship_launch(civ);
        }
        else {
          civ4 = 0;
          for (civ2 = 1; civ2 < 8; civ2++) {
            if (((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) &&
               (result = civ_spaceship_launched(civ2), result != 0)) {
              if (civ4 == 0) {
                civ4 = civ2;
              }
              else if (civs[civ2].spaceship_arrival_year < civs[civ4].spaceship_arrival_year)
              {
                civ4 = civ2;
              }
            }
          }
          if ((civ4 == 0) && (3 < game.difficulty)) {
            for (civ3 = 1; civ3 < 8; civ3++) {
              if ((((civ3 != civ) &&
                   ((1 << ((byte)civ3 & 0x1f) & (uint)game.human_players) == 0)) &&
                  (result = civ_spaceship_launched(civ3), result != 0)) &&
                 (civs[civ3].spaceship_arrival_year < civs[0].spaceship_arrival_year)) {
                return part;
              }
            }
          }
          if (civ4 == 0) {
            should_launch = 0x4b < spaceship_success_pct;
            if (!should_launch) {
              for (civ2 = 1; civ2 < 8; civ2++) {
                if ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) {
                  if (game.power_rank[civ] < game.power_rank[civ2]) {
                    should_launch = true;
                    break;
                  }
                  result = civ_spaceship_exists(civ2);
                  if ((result != 0) && (999 < civs[civ2].gold)) {
                    should_launch = true;
                    break;
                  }
                }
              }
            }
            if (should_launch) {
              spaceship_launch(civ);
            }
          }
          else if (civs[civ].spaceship_arrival_year < civs[civ4].spaceship_arrival_year) {
            spaceship_launch(civ);
          }
        }
      }
    }
  }
  return part;
}
#undef spaceship_success_pct
#undef civ2
#undef part
#undef civ3
#undef p
#undef civ4

/* 00598b4e auto */
#define civ2 (*(int *)(frame_ + FRAME_OFF(4)))
#define dlg (*(Dialog *)(frame_ + FRAME_OFF(12)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(768)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(772)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(776)))
void __cdecl spaceship_select_view_dialog(iptr unused)

{
  bool any_ship;
  int civ;
  iptr name2;
  int shown;
  i32 flags;
  i8 frame_[FRAME_OFF(784)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  dialog_ctor(&dlg,0x4000);
  eh_state = 0;
  dlg_load_game_section(&dlg,(iptr)((u8 *)&g.d_00635024),1);
  any_ship = false;
  for (civ2 = 1; civ2 < 8; civ2++) {
    civ = civ_spaceship_exists(civ2);
    if (civ != 0) {
      flags = 0;
      civ = civ2;
      name2 = civ_name_plural(civ2);
      dialog_add_option((DialogOptionList *)&dlg,name2,civ,flags);
      any_ship = true;
    }
  }
  if (any_ship) {
    civ = dlg_show_modal(&dlg,0);
    if (civ < 0) {
      eh_state = 0xffffffff;
      /* inlined unwind funclet 00598cc7 */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
    }
    else {
      spaceship_wnd_load_parts(civ);
      shown = spaceship_wnd_run(civ);
      if (shown == 0) {
        (*(i8 *)((char *)&civ2 + 0)) = (byte)civ;
        spaceship_status_dialog(civ,(uint)game.human_players & 1 << ((byte)civ2 & 0x1f));
      }
      eh_state = 0xffffffff;
      /* inlined unwind funclet 00598cc7 */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
    }
  }
  else {
    popup_game((iptr)((u8 *)&g.d_00635030));
    eh_state = 0xffffffff;
    /* inlined unwind funclet 00598cc7 */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
  }
  return;
}
#undef civ2
#undef dlg
#undef seh_prev
#undef seh_handler
#undef eh_state

/* 00598ceb auto */
i32 __cdecl spaceship_race_active(void)

{
  i32 active;
  
  if ((game.rules & 0x80) == 0) {
    if ((game.wonder_city[0x19] == -1) && ((game.human_players & game.advance_known_by[0x4c]) == 0))
    {
      active = 0;
    }
    else {
      active = 1;
    }
  }
  else {
    active = 0;
  }
  return active;
}

/* 005998b0 auto */
uint __cdecl spaceship_group_full(iptr civ,iptr group)

{
  int max_count;
  int count;
  
  max_count = spaceship_group_max(group);
  count = spaceship_group_count(civ,group);
  return (uint)(max_count <= count);
}

/* 00599910 auto */
i32 __cdecl spaceship_group_can_build(iptr civ,iptr group)

{
  int result;
  
  result = spaceship_group_at_limit(civ,group);
  if ((((result == 0) || (result = spaceship_group_count(civ,group), result == 0)) &&
      (result = spaceship_group_full(civ,group), result == 0)) &&
     (result = civ_has_advance(civ,(int)improvements[group + 0x23].preq), result != 0)) {
    return 1;
  }
  return 0;
}

/* 005999c0 auto */
uint __cdecl spaceship_group_at_limit(iptr civ,iptr group)

{
  int count;
  int limit;
  
  count = spaceship_group_count(civ,group);
  limit = spaceship_group_limit(civ,group);
  return (uint)(limit <= count);
}
