/* The game, the space race: functions translated from the original
 * (tools/gen_c.py, now edited directly), in address order. */
#include "auto_common.h"

/* 004d0160 auto */
#define net_host_handoff_stage (*(char *)((u8 *)&g.d_006ad698))
#define _DAT_006a5b08 (*(i32 *)((u8 *)&g.d_006a5b08))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl spaceship_wnd_net_idle(void)

{
  int iVar1;
  
  net_process_messages((NetSession *)&net_session,1,0);
  if ((net_host_handoff_stage == '\0') && (iVar1 = timer_ticks(), iVar1 - _DAT_006a5b08 < 0x4b1)) {
    return;
  }
  wnd_end_modal_loop((C_00408010_b8 *)spaceship_wnd);
  return;
}
#undef net_host_handoff_stage
#undef _DAT_006a5b08

/* 004d01ae auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl spaceship_wnd_load_parts(iptr civ)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; local_8 < 6; local_8++) {
    *(int *)(&spaceship_wnd_part_counts + local_8 * 4) =
         (int)civs[civ].spaceship_parts[local_8];
  }
  return;
}
#undef local_8

/* 004d0208 auto */
#define council_active (*(char *)((u8 *)&g.d_00631ad0))
#define local_2194 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_2188 (*(SpaceshipWindow (*)[2])(frame_ + FRAME_OFF(16)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(8584)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(8588)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8592)))
i32 __cdecl spaceship_wnd_run(iptr param_1)

{
  i32 uVar1;
  int iVar2;
  i32 uStackY_24;
  i8 frame_[FRAME_OFF(8600)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  if (spaceship_wnd == 0) {
    if (council_active == '\0') {
      if (param_1 < 1) {
        local_2194 = ~param_1 + 1;
      }
      else {
        local_2194 = param_1;
      }
      uStackY_24 = 0x4d0293;
      spaceship_wnd_ctor(local_2188,local_2194);
      local_8 = 0;
      iVar2 = spaceship_wnd_init(local_2188);
      if (iVar2 == 0) {
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_004d0314 */ { spaceship_wnd_dtor((SpaceshipWindowDtorView *)((iptr)&local_2188)); }
        uVar1 = 0;
      }
      else {
        if (param_1 < 0) {
          spaceship_wnd_launch_sequence(local_2188);
        }
        else {
          spaceship_wnd_run_modal(local_2188);
        }
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_004d0314 */ { spaceship_wnd_dtor((SpaceshipWindowDtorView *)((iptr)&local_2188)); }
        uVar1 = 1;
      }
    }
    else {
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}
#undef council_active
#undef local_2194
#undef local_2188
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004d0339 auto */
#define council_active (*(char *)((u8 *)&g.d_00631ad0))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define local_2188 (*(SpaceshipWindow (*)[2])(frame_ + FRAME_OFF(0)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(8568)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(8572)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8576)))
i32 __cdecl spaceship_wnd_show_for_civ(iptr param_1)

{
  i32 uVar1;
  int iVar2;
  i32 uStackY_24;
  i8 frame_[FRAME_OFF(8584)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  if (human_civ == param_1) {
    if (spaceship_wnd == 0) {
      if (council_active == '\0') {
        uStackY_24 = 0x4d03b3;
        spaceship_wnd_ctor(local_2188,param_1);
        local_8 = 0;
        iVar2 = spaceship_wnd_init(local_2188);
        if (iVar2 == 0) {
          local_8 = 0xffffffff;
          /* inlined unwind funclet FUN_004d041a */ { spaceship_wnd_dtor((SpaceshipWindowDtorView *)((iptr)&local_2188)); }
          uVar1 = 0;
        }
        else {
          spaceship_wnd_present(local_2188);
          local_8 = 0xffffffff;
          /* inlined unwind funclet FUN_004d041a */ { spaceship_wnd_dtor((SpaceshipWindowDtorView *)((iptr)&local_2188)); }
          uVar1 = 1;
        }
      }
      else {
        uVar1 = 1;
      }
    }
    else {
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}
#undef council_active
#undef human_civ
#undef local_2188
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004d043f auto */
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(4)))
void __cdecl spaceship_wnd_draw_title(iptr civ)

{
  iptr iVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  text_clear();
  iVar1 = civ_name_plural(civ);
  text_append(iVar1);
  text_buffer_char_1 = 0;
  text_append(ADDR(0x62e2d4, ((u8 *)&g.d_0062e2d4)));
  iVar1 = civ_leader_name(civ);
  text_append(iVar1);
  text_append_space();
  text_append(ADDR(0x62e2dc, ((u8 *)&g.d_0062e2dc)));
  iVar1 = civ_get_adjective(civ);
  text_append(iVar1);
  text_append(ADDR(0x62e2e0, ((u8 *)&g.d_0062e2e0)));
  gfx_set_text_color_index(0xfa);
  SetRect(&local_14,0,0,0x27f,0x28);
  surface_draw_text_in_rect
            ((DibSurface *)(spaceship_wnd + 0xb8),spaceship_wnd + 0x8c4,ADDR(0x679640, ((u8 *)&g.d_00679640)),(iptr)&local_14,
             0);
  win_flush_pending_msgs();
  return;
}
#undef local_14

/* 004d0517 auto */
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
SpaceshipWindow * __thiscall spaceship_wnd_ctor(SpaceshipWindow *this,u32 param_1)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  wnd_ctor((C_00408010_b8 *)this);
  local_8 = 0;
  surfwnd_ctor((SurfaceWindow *)&this->control_list);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  dll_handle_init((DllHandle *)(this->pad_1e4 + 0x10));
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  palette_init((GamePalette *)(this->pad_1e4 + 0x14));
  (*(i8 *)((char *)&local_8 + 0)) = 3;
  font_init_empty((GameFont *)this->pad_8c4);
  (*(i8 *)((char *)&local_8 + 0)) = 4;
  font_init_empty((GameFont *)(this->pad_8c4 + 8));
  (*(i8 *)((char *)&local_8 + 0)) = 5;
  font_init_empty((GameFont *)(this->pad_8c4 + 0x10));
  (*(i8 *)((char *)&local_8 + 0)) = 6;
  surface_ctor((DibSurface *)this->pad_8f4);
  (*(i8 *)((char *)&local_8 + 0)) = 7;
  sprite_init((Sprite *)(this->pad_8f4 + 0x48));
  (*(i8 *)((char *)&local_8 + 0)) = 8;
  sprite_init((Sprite *)(this->pad_8f4 + 0x84));
  (*(i8 *)((char *)&local_8 + 0)) = 9;
  sprite_init((Sprite *)(this->pad_8f4 + 0xc0));
  (*(i8 *)((char *)&local_8 + 0)) = 10;
  sprite_init((Sprite *)(this->pad_8f4 + 0xfc));
  (*(i8 *)((char *)&local_8 + 0)) = 0xb;
  sprite_init((Sprite *)(this->pad_8f4 + 0x138));
  (*(i8 *)((char *)&local_8 + 0)) = 0xc;
  sprite_init((Sprite *)(this->pad_8f4 + 0x174));
  (*(i8 *)((char *)&local_8 + 0)) = 0xd;
  sprite_init((Sprite *)(this->pad_8f4 + 0x1b0));
  (*(i8 *)((char *)&local_8 + 0)) = 0xe;
  clickmap_ctor(this->pad_ae4);
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),0xf);
  this->ship_civ = param_1;
  this->anim_timer = 0;
  gfx_get_screen_rect((iptr)&this->frame_left);
  this->type_index = 0;
  spaceship_wnd = (iptr)this;
  font_set_styled((GameFont *)this->pad_8c4,0,0x18,1);
  font_set_styled((GameFont *)(this->pad_8c4 + 8),0,0x14,1);
  font_set_styled((GameFont *)(this->pad_8c4 + 0x10),0,0x10,1);
  this->field_8ec = 0;
  this->launched = 0;
  surface_create((DibSurface *)this->pad_8f4,0x1c9,0x130);
  surface_fill((DibSurface *)this->pad_8f4,9);
  this->flight_timer = 0;
  this->anim_timer = 0;
  this->blink_timer = 0;
  SetRect((LPRECT)this->pad_1e4,10,0x14,300,0x1df);
  this[1].pad_ae4[0x30c] = '\0';
  this[1].pad_ae4[0x30d] = '\0';
  this[1].pad_ae4[0x30e] = '\0';
  this[1].pad_ae4[0x30f] = '\0';
  this->launch_state = 0;
  this[1].pad_ae4[0x310] = '\0';
  this[1].pad_ae4[0x311] = '\0';
  this[1].pad_ae4[0x312] = '\0';
  this[1].pad_ae4[0x313] = '\0';
  this[1].pad_ae4[0x314] = '\0';
  this[1].pad_ae4[0x315] = '\0';
  this[1].pad_ae4[0x316] = '\0';
  this[1].pad_ae4[0x317] = '\0';
  this[1].pad_ae4[0x318] = '\0';
  this[1].pad_ae4[0x319] = '\0';
  this[1].pad_ae4[0x31a] = '\0';
  this[1].pad_ae4[0x31b] = '\0';
  return this;
}
#undef local_10
#undef puStack_c
#undef local_8

/* 004d08b0 auto */
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
i32 __thiscall spaceship_wnd_dtor(SpaceshipWindowDtorView *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xf;
  dll_handle_free((DllHandle *)(this->pad_0 + 500));
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
  (*(i8 *)((char *)&local_8 + 0)) = 0xe;
  /* inlined unwind funclet FUN_004d0a56 */ { clickmap_dtor(*(int *)((iptr)&this) + 0xae4); }
  (*(i8 *)((char *)&local_8 + 0)) = 0xd;
  /* inlined unwind funclet FUN_004d0a65 */ { sprite_destroy((Sprite *)(*(int *)((iptr)&this) + 0xaa4)); }
  (*(i8 *)((char *)&local_8 + 0)) = 0xc;
  /* inlined unwind funclet FUN_004d0a74 */ { sprite_destroy((Sprite *)(*(int *)((iptr)&this) + 0xa68)); }
  (*(i8 *)((char *)&local_8 + 0)) = 0xb;
  /* inlined unwind funclet FUN_004d0a83 */ { sprite_destroy((Sprite *)(*(int *)((iptr)&this) + 0xa2c)); }
  (*(i8 *)((char *)&local_8 + 0)) = 10;
  /* inlined unwind funclet FUN_004d0a92 */ { sprite_destroy((Sprite *)(*(int *)((iptr)&this) + 0x9f0)); }
  (*(i8 *)((char *)&local_8 + 0)) = 9;
  /* inlined unwind funclet FUN_004d0aa1 */ { sprite_destroy((Sprite *)(*(int *)((iptr)&this) + 0x9b4)); }
  (*(i8 *)((char *)&local_8 + 0)) = 8;
  /* inlined unwind funclet FUN_004d0ab0 */ { sprite_destroy((Sprite *)(*(int *)((iptr)&this) + 0x978)); }
  (*(i8 *)((char *)&local_8 + 0)) = 7;
  /* inlined unwind funclet FUN_004d0abf */ { sprite_destroy((Sprite *)(*(int *)((iptr)&this) + 0x93c)); }
  (*(i8 *)((char *)&local_8 + 0)) = 6;
  /* inlined unwind funclet FUN_004d0ace */ { surface_dtor((DibSurface *)(*(int *)((iptr)&this) + 0x8f4)); }
  (*(i8 *)((char *)&local_8 + 0)) = 5;
  /* inlined unwind funclet FUN_004d0add */ { font_destroy((GameFont *)(*(int *)((iptr)&this) + 0x8d4)); }
  (*(i8 *)((char *)&local_8 + 0)) = 4;
  /* inlined unwind funclet FUN_004d0aec */ { font_destroy((GameFont *)(*(int *)((iptr)&this) + 0x8cc)); }
  (*(i8 *)((char *)&local_8 + 0)) = 3;
  /* inlined unwind funclet FUN_004d0afb */ { font_destroy((GameFont *)(*(int *)((iptr)&this) + 0x8c4)); }
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  /* inlined unwind funclet FUN_004d0b0a */ { palette_destroy((GamePalette *)(*(int *)((iptr)&this) + 0x1f8)); }
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  /* inlined unwind funclet FUN_004d0b19 */ { dll_free((DllHandle *)(*(int *)((iptr)&this) + 500)); }
  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
  /* inlined unwind funclet FUN_004d0b28 */ { surfwnd_dtor((SurfaceWindow *)(*(int *)((iptr)&this) + 0xb8)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_004d0b37 */ { wnd_dtor(*(WndBase **)((iptr)&this)); }
  return uStack_10;
}
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004d0b58 auto */
#define spaceship_success_pct (*(int *)((u8 *)&g.d_006ad0ec))
#define local_84 (*(i8 (*)[128])(frame_ + FRAME_OFF(4)))
i32 __thiscall spaceship_wnd_init(SpaceshipWindow *this)

{
  int iVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(136)] __attribute__((aligned(8)));  /* original stack frame */
  
  str_clear((iptr)local_84);
  str_append((iptr)local_84,ADDR(0x62e2e4, ((u8 *)&g.d_0062e2e4)));
  iVar1 = file_resolve_path((iptr)local_84);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    dll_handle_load((DllHandle *)(this->pad_1e4 + 0x10),(iptr)local_84);
    wnd_set_cursor((WndBase *)this,0x1fc);
    spaceship_calc_stats(this->ship_civ,1);
    spaceship_wnd_build_stats_text((C_00408010_6f0 *)this);
    if ((civs[this->ship_civ].spaceship_parts[3] != 0) && (spaceship_success_pct != 0)) {
      this->launch_state = 1;
    }
    iVar1 = civ_spaceship_launched(this->ship_civ);
    if (iVar1 != 0) {
      this->launch_state = 3;
    }
    iVar1 = spaceship_wnd_create((C_00408010_6f0 *)this);
    if (iVar1 == 0) {
      uVar2 = 0;
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
      uVar2 = 1;
    }
  }
  return uVar2;
}
#undef spaceship_success_pct
#undef local_84

/* 004d0d64 auto */
uint __thiscall spaceship_wnd_create(C_00408010_6f0 *this)

{
  int iVar1;
  
  win_flush_pending_msgs();
  wnd_create_with_handlers
            ((WndBase *)this,ADDR(0x62e2ec, ((u8 *)&g.d_0062e2ec)),0x800,this->frame_left,this->frame_top,
             this->frame_right - this->frame_left,(this->frame_bottom - this->frame_top) + 5,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)),
             ADDR(0x6553d8, ((u8 *)&g.d_006553d8)));
  wnd_set_bg_color((WndBase *)this,0);
  wnd_create_with_surface
            ((DibSurface *)&this->control_list,ADDR(0x62e2f0, ((u8 *)&g.d_0062e2f0)),0x800,0,0,0x280,0x1e0,
             (iptr)(this->pad_1e4 + 0x14),(iptr)this);
  iVar1 = surface_load_gif_resource
                    ((DibSurface *)&this->control_list,499,10,0xec,(iptr)(this->pad_1e4 + 0x14));
  if (iVar1 != 0) {
    wnd_center((WndCenterView *)(this->pad_c8 + 0x38));
    wnd_set_keydown_handler((C_00408130 *)(this->pad_c8 + 0x48),ADDR(0x403a35, spaceship_wnd_on_key));
    wnd_set_mousemove_handler((WndHandlersMouseSetView *)(this->pad_c8 + 0x48),ADDR(0x402513, spaceship_wnd_on_mousemove));
    wnd_set_lbuttondown_handler((WndHandlersMouseSetView *)(this->pad_c8 + 0x48),ADDR(0x402d83, spaceship_wnd_on_lbuttondown));
    wnd_set_lbuttonup_any_handler((WndHandlersMouseSetView *)(this->pad_c8 + 0x48),ADDR(0x4038b9, spaceship_wnd_on_lbuttonup));
  }
  return (uint)(iVar1 != 0);
}

/* 004d0ea6 auto */
#define _DAT_006a5b08 (*(i32 *)((u8 *)&g.d_006a5b08))
#define local_a4 (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_94 (*(Sprite *)(frame_ + FRAME_OFF(20)))
#define local_58 (*(DibSurface *)(frame_ + FRAME_OFF(80)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(152)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(156)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(160)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall spaceship_wnd_run_modal(SpaceshipWindow *this)

{
  int iVar1;
  u32 uVar2;
  i8 frame_[FRAME_OFF(168)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  surface_ctor(&local_58);
  local_8 = 0;
  sprite_init(&local_94);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  spaceship_wnd_load_parts(this->ship_civ);
  iVar1 = spaceship_wnd_render_ship(this);
  if (iVar1 == 0) {
    local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
    /* inlined unwind funclet FUN_004d138b */ { sprite_destroy((Sprite *)((iptr)&local_94)); }
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_004d1397 */ { surface_dtor((DibSurface *)((iptr)&local_58)); }
  }
  else {
    if (this->launch_state == 3) {
      surface_load_gif_resource
                (&local_58,spaceship_wnd_component_count + 19999,10,0xec,(iptr)(this->pad_1e4 + 0x14));
      sprite_grab_from_surface
                (&local_94,(iptr)&local_58,0xff,
                 *(i32 *)(&spaceship_launch_sprite_xs + (spaceship_wnd_component_count - 1) * 0x10),
                 *(i32 *)(&spaceship_launch_sprite_ys + (spaceship_wnd_component_count - 1) * 0x10),
                 *(i32 *)(&spaceship_launch_sprite_widths + (spaceship_wnd_component_count - 1) * 0x10),
                 *(i32 *)(&spaceship_part_sprite_heights + (spaceship_wnd_component_count - 1) * 0x10));
      sprite_draw
                (&local_94,(iptr)local_a4,(iptr)&this->control_list,
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
      uVar2 = game_timer_create(ADDR(0x401af5, spaceship_wnd_starfield_tick),5,0xffffffff);
      this->flight_timer = uVar2;
    }
    else {
      uVar2 = game_timer_create(ADDR(0x403a7b, spaceship_wnd_type_tick),0x3c,0xffffffff);
      this->anim_timer = uVar2;
    }
    wnd_handle_show_raise((WndBase *)this);
    wnd_flush_paint();
    wnd_set_palette((WndBase *)this,(iptr)(this->pad_1e4 + 0x14));
    window_show((C_004083b0_4 *)&this->control_list);
    wnd_flush_paint();
    wnd_set_palette((WndBase *)&main_frame_wnd,(iptr)(this->pad_1e4 + 0x14));
    spaceship_wnd_setup_hotspots(this);
    spaceship_wnd_draw_buttons(this);
    if (this->launch_state == 3) {
      this->launched = 1;
    }
    else {
      this->launched = 0;
    }
    this[1].pad_ae4[0x318] = 1;
    this[1].pad_ae4[0x319] = '\0';
    this[1].pad_ae4[0x31a] = '\0';
    this[1].pad_ae4[0x31b] = '\0';
    wnd_set_capture((WndBase *)(this->pad_c8 + 0x38));
    input_flush_events();
    if (2 < game.multiplayer) {
      wnd_set_modal_idle_callback((C_00408010_b8 *)(this->pad_c8 + 0x38),ADDR(0x4014d3, spaceship_wnd_net_idle));
    }
    _DAT_006a5b08 = timer_ticks();
    wnd_run_modal_loop((C_00408010_b8 *)(this->pad_c8 + 0x38));
    wnd_set_modal_idle_callback((C_00408010_b8 *)(this->pad_c8 + 0x38),0);
    wnd_release_capture((WndBase *)(this->pad_c8 + 0x38));
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
      wnd_hide((WndBase *)(this->pad_c8 + 0x38));
      wnd_flush_paint();
    }
    wnd_set_palette((WndBase *)&main_frame_wnd,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
    wnd_set_palette((WndBase *)this,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
    wnd_hide((WndBase *)this);
    wnd_flush_paint();
    local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
    /* inlined unwind funclet FUN_004d138b */ { sprite_destroy((Sprite *)((iptr)&local_94)); }
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_004d1397 */ { surface_dtor((DibSurface *)((iptr)&local_58)); }
  }
  return;
}
#undef _DAT_006a5b08
#undef local_a4
#undef local_94
#undef local_58
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004d13b8 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define _DAT_006a5b08 (*(i32 *)((u8 *)&g.d_006a5b08))
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(4)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall spaceship_wnd_present(SpaceshipWindow *this)

{
  int iVar1;
  u32 uVar2;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (this->ship_civ == human_civ) {
    if (this->anim_timer != 0) {
      game_timer_destroy(this->anim_timer);
    }
    if ((this->launch_state != 3) && (iVar1 = spaceship_wnd_render_ship(this), iVar1 != 0)) {
      spaceship_wnd_draw_close_btn(this,1,1);
      spaceship_wnd_draw_launch_btn(this,0,1);
      this[1].pad_ae4[0x318] = 1;
      this[1].pad_ae4[0x319] = '\0';
      this[1].pad_ae4[0x31a] = '\0';
      this[1].pad_ae4[0x31b] = '\0';
      wnd_handle_show_raise((WndBase *)this);
      wnd_flush_paint();
      wnd_set_palette((WndBase *)this,(iptr)(this->pad_1e4 + 0x14));
      window_show((C_004083b0_4 *)&this->control_list);
      wnd_flush_paint();
      wnd_set_palette((WndBase *)&main_frame_wnd,(iptr)(this->pad_1e4 + 0x14))
      ;
      spaceship_wnd_setup_hotspots(this);
      spaceship_wnd_draw_buttons(this);
      this->launched = 1;
      this[1].pad_ae4[0x318] = 1;
      this[1].pad_ae4[0x319] = '\0';
      this[1].pad_ae4[0x31a] = '\0';
      this[1].pad_ae4[0x31b] = '\0';
      uVar2 = this->launch_state;
      this->launch_state = 0;
      this->launch_state = uVar2;
      spaceship_wnd_load_parts(this->ship_civ);
      iVar1 = spaceship_wnd_render_ship(this);
      if (iVar1 != 0) {
        spaceship_wnd_draw_close_btn(this,1,0);
        spaceship_wnd_draw_launch_btn(this,0,1);
        SetRect(&local_14,0,0,0x280,0x1e0);
        gfx_dissolve_blit((iptr)&this->control_list,(iptr)&local_14,5,1);
        spaceship_wnd_draw_close_btn(this,1,1);
        uVar2 = game_timer_create(ADDR(0x403a7b, spaceship_wnd_type_tick),10,0xffffffff);
        this->anim_timer = uVar2;
        spaceship_wnd_setup_hotspots(this);
        spaceship_wnd_draw_buttons(this);
        this->launched = 0;
        this[1].pad_ae4[0x318] = 1;
        this[1].pad_ae4[0x319] = '\0';
        this[1].pad_ae4[0x31a] = '\0';
        this[1].pad_ae4[0x31b] = '\0';
        wnd_set_capture((WndBase *)(this->pad_c8 + 0x38));
        input_flush_events();
        if (2 < game.multiplayer) {
          wnd_set_modal_idle_callback((C_00408010_b8 *)(this->pad_c8 + 0x38),ADDR(0x4014d3, spaceship_wnd_net_idle));
        }
        _DAT_006a5b08 = timer_ticks();
        wnd_run_modal_loop((C_00408010_b8 *)(this->pad_c8 + 0x38));
        wnd_set_modal_idle_callback((C_00408010_b8 *)(this->pad_c8 + 0x38),0);
        wnd_release_capture((WndBase *)(this->pad_c8 + 0x38));
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
        wnd_set_palette((WndBase *)&main_frame_wnd,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
        if (this->launch_state == 2) {
          spaceship_play_launch_video((WndBase *)this);
          this->launch_state = 3;
          spaceship_launch(this->ship_civ);
          spaceship_wnd_run_modal(this);
        }
        else {
          wnd_hide((WndBase *)(this->pad_c8 + 0x38));
          wnd_flush_paint();
        }
        wnd_set_palette((WndBase *)this,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
        wnd_hide((WndBase *)this);
        wnd_flush_paint();
      }
    }
  }
  return;
}
#undef human_civ
#undef _DAT_006a5b08
#undef local_14

/* 004d1725 auto */
void __thiscall spaceship_wnd_launch_sequence(SpaceshipWindow *this)

{
  wnd_handle_show_raise((WndBase *)this);
  wnd_flush_paint();
  wnd_set_palette((WndBase *)&main_frame_wnd,(iptr)(this->pad_1e4 + 0x14));
  wnd_set_palette((WndBase *)this,(iptr)(this->pad_1e4 + 0x14));
  this->launch_state = 2;
  spaceship_play_launch_video((WndBase *)this);
  this->launch_state = 3;
  spaceship_wnd_run_modal(this);
  wnd_set_palette((WndBase *)&main_frame_wnd,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
  wnd_set_palette((WndBase *)this,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
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
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
void __thiscall spaceship_wnd_build_stats_text(C_00408010_6f0 *this)

{
  short sVar1;
  bool bVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  bVar2 = false;
  str_clear((iptr)this->pad_638);
  for (local_c = 0; local_c < 6; local_c++) {
    sVar1 = civs[(this->ship_civ)].spaceship_parts[local_c];
    iVar3 = spaceship_part_limit(this->ship_civ,local_c);
    if (iVar3 < sVar1) {
      bVar2 = true;
    }
  }
  for (local_c = 0; local_c < 6; local_c++) {
    str_append_string_id((iptr)this->pad_638,
                       *(i32 *)(label_string_ids + *(int *)(&spaceship_part_table + local_c * 0xc) * 4))
    ;
    str_append_colon((iptr)this->pad_638);
    str_append_int((iptr)this->pad_638,
                       (int)civs[(this->ship_civ)].spaceship_parts[local_c]);
    if ((bVar2) && (local_c == 0)) {
      str_append((iptr)this->pad_638,ADDR(0x62e2f4, ((u8 *)&g.d_0062e2f4)));
    }
    str_append((iptr)this->pad_638,ADDR(0x62e2f8, ((u8 *)&g.d_0062e2f8)));
  }
  str_append_label((iptr)this->pad_638,0x22);
  str_append_colon((iptr)this->pad_638);
  str_append_int((iptr)this->pad_638,(int)civs[this->ship_civ].spaceship_parts[3]);
  str_append((iptr)this->pad_638,ADDR(0x62e2fc, ((u8 *)&g.d_0062e2fc)));
  str_append((iptr)this->pad_638,ADDR(0x62e304, ((u8 *)&g.d_0062e304)));
  str_append_label((iptr)this->pad_638,0x42);
  str_append_colon((iptr)this->pad_638);
  str_append_int((iptr)this->pad_638,spaceship_support_pct);
  str_append_percent((iptr)this->pad_638);
  str_append((iptr)this->pad_638,ADDR(0x62e308, ((u8 *)&g.d_0062e308)));
  str_append_label((iptr)this->pad_638,0xcd);
  str_append_colon((iptr)this->pad_638);
  str_append_int((iptr)this->pad_638,spaceship_energy_pct);
  str_append_percent((iptr)this->pad_638);
  str_append((iptr)this->pad_638,ADDR(0x62e30c, ((u8 *)&g.d_0062e30c)));
  str_append_label((iptr)this->pad_638,0xce);
  str_append_colon((iptr)this->pad_638);
  str_append_int((iptr)this->pad_638,spaceship_mass / 10);
  str_append((iptr)this->pad_638,ADDR(0x62e310, ((u8 *)&g.d_0062e310)));
  str_append_int((iptr)this->pad_638,spaceship_mass % 10);
  str_append((iptr)this->pad_638,ADDR(0x62e314, ((u8 *)&g.d_0062e314)));
  str_append_label((iptr)this->pad_638,0xd1);
  str_append((iptr)this->pad_638,ADDR(0x62e318, ((u8 *)&g.d_0062e318)));
  str_append_label((iptr)this->pad_638,200);
  str_append_colon((iptr)this->pad_638);
  str_append_int((iptr)this->pad_638,spaceship_fuel_pct);
  str_append_percent((iptr)this->pad_638);
  if ((civs[this->ship_civ].spaceship_flags & 8) != 0) {
    str_append_space((iptr)this->pad_638);
    str_append_lparen((iptr)this->pad_638);
    str_append_label((iptr)this->pad_638,0xeb);
    str_append_rparen((iptr)this->pad_638);
  }
  str_append((iptr)this->pad_638,ADDR(0x62e31c, ((u8 *)&g.d_0062e31c)));
  str_append_label((iptr)this->pad_638,0xcf);
  str_append_colon((iptr)this->pad_638);
  str_append_int((iptr)this->pad_638,spaceship_flight_time / 10);
  str_append((iptr)this->pad_638,ADDR(0x62e320, ((u8 *)&g.d_0062e320)));
  str_append_int((iptr)this->pad_638,spaceship_flight_time % 10);
  str_append_space((iptr)this->pad_638);
  str_append_label((iptr)this->pad_638,0xd2);
  str_clear((iptr)(this[1].pad_c8 + 0x80));
  str_append_label((iptr)(this[1].pad_c8 + 0x80),0xd0);
  str_append_colon((iptr)(this[1].pad_c8 + 0x80));
  str_append_space((iptr)(this[1].pad_c8 + 0x80));
  str_append_int((iptr)(this[1].pad_c8 + 0x80),spaceship_success_pct);
  str_append_percent((iptr)(this[1].pad_c8 + 0x80));
  win_flush_pending_msgs();
  return;
}
#undef spaceship_energy_pct
#undef spaceship_fuel_pct
#undef spaceship_success_pct
#undef spaceship_support_pct
#undef local_c

/* 004d4fd1 auto */
#define spaceship_success_pct (*(int *)((u8 *)&g.d_006ad0ec))
#define local_18 (*(u8 (*)[4])(frame_ + FRAME_OFF(0)))
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(4)))
uint __thiscall spaceship_wnd_type_char(SpaceshipWindow *this,int param_1)

{
  int iVar1;
  uint uVar2;
  i32 uVar3;
  int iVar4;
  u32 uVar5;
  u8 *puVar6;
  int yBottom;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((param_1 == 0) || (iVar1 = rand_range(0,1), iVar1 == 0)) {
    uVar3 = font_get_handle((GameFont *)(this->pad_8c4 + 0x10));
    iVar1 = font_measure_height(uVar3);
    win_flush_pending_msgs();
    local_18[0] = this->pad_638[this->type_index];
    local_18[1] = 0;
    gfx_set_text_color_index(0xf9);
    if (*(int *)(this[1].pad_ae4 + 0x318) == 0) {
      gfx_set_text_color_index(0xfe);
    }
    else {
      gfx_set_text_color_index(0xf9);
    }
    surface_draw_text
              ((DibSurface *)&this->control_list,(iptr)(this->pad_8c4 + 0x10),(iptr)local_18,
               this->type_x,this->type_y,1);
    yBottom = this->type_y + iVar1 * 2;
    puVar6 = local_18;
    uVar3 = font_get_handle((GameFont *)(this->pad_8c4 + 0x10));
    iVar4 = font_measure_width(uVar3,(iptr)puVar6);
    SetRect(&local_14,this->type_x,this->type_y - iVar1,this->type_x + iVar4,yBottom);
    puVar6 = local_18;
    uVar3 = font_get_handle((GameFont *)(this->pad_8c4 + 0x10));
    iVar1 = font_measure_width(uVar3,(iptr)puVar6);
    this->type_x += iVar1;
    if (this->pad_638[this->type_index] == ':') {
      this[1].pad_ae4[0x318] = '\0';
      this[1].pad_ae4[0x319] = '\0';
      this[1].pad_ae4[0x31a] = '\0';
      this[1].pad_ae4[0x31b] = '\0';
    }
    this->type_index++;
    while (this->pad_638[this->type_index] == '\n') {
      this[1].pad_ae4[0x318] = 1;
      this[1].pad_ae4[0x319] = '\0';
      this[1].pad_ae4[0x31a] = '\0';
      this[1].pad_ae4[0x31b] = '\0';
      this->type_x = 10;
      uVar3 = font_get_handle((GameFont *)(this->pad_8c4 + 0x10));
      iVar1 = font_measure_height(uVar3);
      this->type_y += iVar1;
      this->type_index++;
    }
    if (this->pad_638[this->type_index] == '\0') {
      if (this->anim_timer != 0) {
        game_timer_destroy(this->anim_timer);
        this->anim_timer = 0;
      }
      if (this->launch_state != 3) {
        SetRect((LPRECT)(this->pad_8c4 + 0x18),0,0x1c1,0x27f,0x1df);
        rect_offset((iptr)(this->pad_8c4 + 0x18),1,1);
        gfx_set_text_color_index(10);
        surface_draw_text_in_rect
                  ((DibSurface *)&this->control_list,(iptr)(this->pad_8c4 + 8),
                   (iptr)(this->pad_700 + 0x138),(iptr)(this->pad_8c4 + 0x18),0);
        rect_offset((iptr)(this->pad_8c4 + 0x18),0xffffffff,0xffffffff);
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
                  ((DibSurface *)&this->control_list,(iptr)(this->pad_8c4 + 8),
                   (iptr)(this->pad_700 + 0x138),(iptr)(this->pad_8c4 + 0x18),0);
        wnd_blit_surface_rect
                  ((DibSurface *)&this->control_list,(iptr)(this->pad_8c4 + 0x18));
        wnd_flush_paint();
      }
      if (this->launch_state == 1) {
        uVar5 = game_timer_create(ADDR(0x403a53, spaceship_wnd_blink_launch_btn),500,0xffffffff);
        this->blink_timer = uVar5;
      }
      this->launched = 1;
    }
    wnd_blit_surface_rect((DibSurface *)&this->control_list,(iptr)&local_14);
    uVar2 = (uint)(this->pad_638[this->type_index] != '\0');
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}
#undef spaceship_success_pct
#undef local_18
#undef local_14

/* 004d53ab: written by hand in src/game/unwind.c */

/* 004d570b auto */
#define local_30 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(28)))
void __thiscall spaceship_wnd_init_starfield(SpaceshipWindow *this)

{
  u8 *puVar1;
  i32 uVar2;
  int iVar3;
  int xRight;
  iptr iVar4;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_20 = 0; local_20 < 0x50; local_20++) {
    uVar2 = rand_range(0xffff8300,32000);
    *(i32 *)(this[1].pad_ae4 + local_20 * 0xc + 0x31c) = uVar2;
    uVar2 = rand_range(0xffffa240,24000);
    *(i32 *)(this[1].pad_ae4 + local_20 * 0xc + 800) = uVar2;
    uVar2 = rand_range(1,100);
    *(i32 *)(this[1].pad_ae4 + local_20 * 0xc + 0x324) = uVar2;
  }
  iVar3 = surface_get_height((DibSurface *)&this->control_list);
  xRight = surface_get_width((DibSurface *)&this->control_list);
  SetRect(&local_14,0,0x14,xRight,iVar3);
  surface_fill_rect((DibSurface *)&this->control_list,(iptr)&local_14,10);
  for (local_20 = 0; local_20 < 0x50; local_20++) {
    local_18 = *(int *)(this[1].pad_ae4 + local_20 * 0xc + 0x31c) /
               *(int *)(this[1].pad_ae4 + local_20 * 0xc + 0x324) + 0x140;
    local_1c = *(int *)(this[1].pad_ae4 + local_20 * 0xc + 800) /
               *(int *)(this[1].pad_ae4 + local_20 * 0xc + 0x324) + 0xf0;
    if ((((0x280 < local_18) || (local_18 < 0)) || (0x1e0 < local_1c)) || (local_1c < 0)) {
      uVar2 = rand_range(0xffff8300,32000);
      *(i32 *)(this[1].pad_ae4 + local_20 * 0xc + 0x31c) = uVar2;
      uVar2 = rand_range(0xffffa240,24000);
      *(i32 *)(this[1].pad_ae4 + local_20 * 0xc + 800) = uVar2;
      puVar1 = this[1].pad_ae4 + local_20 * 0xc + 0x324;
      puVar1[0] = 'd';
      puVar1[1] = '\0';
      puVar1[2] = '\0';
      puVar1[3] = '\0';
      local_18 = *(int *)(this[1].pad_ae4 + local_20 * 0xc + 0x31c) /
                 *(int *)(this[1].pad_ae4 + local_20 * 0xc + 0x324) + 0x140;
      local_1c = *(int *)(this[1].pad_ae4 + local_20 * 0xc + 800) /
                 *(int *)(this[1].pad_ae4 + local_20 * 0xc + 0x324) + 0xf0;
    }
    surface_set_pixel((DibSurface *)&this->control_list,local_18,local_1c,0x29);
  }
  this->type_index = 0;
  this->type_x = 10;
  this->type_y = 0x73;
  this[1].pad_ae4[0x318] = 1;
  this[1].pad_ae4[0x319] = '\0';
  this[1].pad_ae4[0x31a] = '\0';
  this[1].pad_ae4[0x31b] = '\0';
  do {
    iVar3 = spaceship_wnd_type_char(this,0);
  } while (iVar3 != 0);
  str_clear((iptr)(this->pad_700 + 0x138));
  iVar4 = label_string(*(i32 *)(label_string_ids + 0x718));
  str_append((iptr)(this->pad_700 + 0x138),iVar4);
  str_append_colon((iptr)(this->pad_700 + 0x138));
  str_append_space((iptr)(this->pad_700 + 0x138));
  str_append_year((iptr)(this->pad_700 + 0x138),(int)civs[this->ship_civ].spaceship_arrival_year
                    );
  SetRect((LPRECT)(this->pad_8c4 + 0x18),0,0x1c1,0x27f,0x1df);
  rect_offset((iptr)(this->pad_8c4 + 0x18),1,1);
  gfx_set_text_color_index(10);
  surface_draw_text_in_rect
            ((DibSurface *)&this->control_list,(iptr)(this->pad_8c4 + 8),
             (iptr)(this->pad_700 + 0x138),(iptr)(this->pad_8c4 + 0x18),0);
  rect_offset((iptr)(this->pad_8c4 + 0x18),0xffffffff,0xffffffff);
  gfx_set_text_color_index(0xfa);
  surface_draw_text_in_rect
            ((DibSurface *)&this->control_list,(iptr)(this->pad_8c4 + 8),
             (iptr)(this->pad_700 + 0x138),(iptr)(this->pad_8c4 + 0x18),0);
  wnd_blit_surface_rect((DibSurface *)&this->control_list,(iptr)(this->pad_8c4 + 0x18));
  sprite_draw
            ((Sprite *)(this->pad_8f4 + 0x48),(iptr)local_30,(iptr)&this->control_list,0xaf,99);
  if (this->launch_state == 3) {
    this->type_y = 0x8c;
  }
  return;
}
#undef local_30
#undef local_20
#undef local_1c
#undef local_18
#undef local_14

/* 004d5b21 auto */
#define local_9c (*(u32 *)(frame_ + FRAME_OFF(4)))
#define local_94 (*(i8 (*)[128])(frame_ + FRAME_OFF(12)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(140)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(144)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(148)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(152)))
void __thiscall spaceship_play_launch_video(WndBase *this)

{
  C_004083b0_a28 *this_00;
  int iVar1;
  i8 frame_[FRAME_OFF(160)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  snd_cd_stop();
  this_00 = operator_new(0xa28);
  local_8 = 0;
  if (this_00 == (C_004083b0_a28 *)0x0) {
    local_9c = 0;
  }
  else {
    local_9c = mmwnd_ctor(this_00);
  }
  local_8 = 0xffffffff;
  this[0x1da].field_8 = local_9c;
  str_clear((iptr)local_94);
  str_append((iptr)local_94,ADDR(0x62e334, ((u8 *)&g.d_0062e334)));
  iVar1 = file_resolve_path((iptr)local_94);
  if (iVar1 != 0) {
    avi_player_create((C_004083b0_61c *)this[0x1da].field_8,ADDR(0x62e34c, ((u8 *)&g.d_0062e34c)),0x800,0,0);
    avi_player_set_double_size((C_004083b0_61c *)this[0x1da].field_8,1);
    local_14 = avi_player_open((AviPlayerOpenView *)this[0x1da].field_8,(iptr)local_94);
    if (local_14 != 0) {
      if (local_14 == -0x7ffbfeac) {
        popup_game(ADDR(0x62e350, ((u8 *)&g.d_0062e350)));
      }
      goto LAB_004d5e33;
    }
    wnd_hide(this + 0x10);
    wnd_flush_paint();
    surface_fill((DibSurface *)this[0x1da].field_8,0);
    wnd_set_lbuttonup_handler((C_00408130 *)(this[0x1da].field_8 + 0x58),ADDR(0x40308f, spaceship_video_on_lbuttonup));
    wnd_set_keydown_handler((C_00408130 *)(this[0x1da].field_8 + 0x58),ADDR(0x403a35, spaceship_wnd_on_key));
    avi_player_set_end_callback((AviPlayerEndCbSetView *)this[0x1da].field_8,ADDR(0x402d2e, spaceship_video_on_end));
    wnd_center((WndCenterView *)(this[0x1da].field_8 + 0x48));
    wnd_blit_surface((DibSurface *)this[0x1da].field_8);
    window_show((C_004083b0_4 *)this[0x1da].field_8);
    wnd_flush_paint();
    avi_player_play((AviPlayerPlayView *)this[0x1da].field_8);
    input_flush_events();
    wnd_set_capture((WndBase *)(this[0x1da].field_8 + 0x48));
    if (2 < game.multiplayer) {
      wnd_set_modal_idle_callback((C_00408010_b8 *)(this[0x1da].field_8 + 0x48),ADDR(0x403585, net_modal_idle_poll));
    }
    wnd_run_modal_loop((C_00408010_b8 *)(this[0x1da].field_8 + 0x48));
    wnd_set_modal_idle_callback((C_00408010_b8 *)(this[0x1da].field_8 + 0x48),0);
    wnd_release_capture((WndBase *)(this[0x1da].field_8 + 0x48));
    wnd_hide((WndBase *)(this[0x1da].field_8 + 0x48));
    wnd_flush_paint();
  }
  if ((AviPlayer *)this[0x1da].field_8 != (AviPlayer *)0x0) {
    avi_player_scalar_dtor((AviPlayer *)this[0x1da].field_8,1);
  }
  this[0x1da].field_8 = 0;
  snd_sync_music_option();
LAB_004d5e33:
  return;
}
#undef local_9c
#undef local_94
#undef local_14
#undef local_10
#undef puStack_c
#undef local_8

/* 004d5e41 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
void __thiscall spaceship_wnd_setup_hotspots(SpaceshipWindow *this)

{
  clickmap_clear((ClickMapClearView *)this->pad_ae4);
  if (((this->ship_civ == human_civ) && (this->launch_state != 3)) && (this->launch_state != 0)) {
    clickmap_add_xywh((ClickMap *)this->pad_ae4,0,0x1f5,0x1a1,0x34,0x24);
    clickmap_add_xywh((ClickMap *)this->pad_ae4,1,0x22f,0x1a1,0x43,0x24);
  }
  else {
    clickmap_add_xywh((ClickMap *)this->pad_ae4,0,0x22f,0x1a1,0x43,0x24);
  }
  return;
}
#undef human_civ

/* 004d5ef9 auto */
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(4)))
void __thiscall spaceship_wnd_draw_buttons(SpaceshipWindow *this)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((this->launch_state != 1) && (this->launch_state != 0)) {
    SetRect(&local_14,0x1f5,0x1a1,0x229,0x1c5);
    surface_fill_rect((DibSurface *)&this->control_list,(iptr)&local_14,0);
  }
  spaceship_wnd_draw_close_btn(this,1,1);
  spaceship_wnd_draw_launch_btn(this,0,1);
  return;
}
#undef local_14

/* 004d5f79 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define local_44 (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_34 (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
#define local_24 (*(i8 (*)[16])(frame_ + FRAME_OFF(36)))
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(52)))
void __thiscall spaceship_wnd_draw_close_btn(SpaceshipWindow *this,int param_1,int param_2)

{
  i8 frame_[FRAME_OFF(72)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((this->ship_civ == human_civ) && (this->launch_state != 3)) && (this->launch_state != 0)) {
    SetRect(&local_14,0x1f5,0x1a1,0x229,0x1c5);
  }
  else {
    SetRect(&local_14,0x22f,0x1a1,0x272,0x1c5);
  }
  if (param_2 == 0) {
    sprite_draw
              ((Sprite *)(this->pad_8f4 + 0x84),(iptr)local_24,(iptr)&this->control_list,
               local_14.left,local_14.top);
  }
  else if (param_1 == 0) {
    sprite_draw
              ((Sprite *)(this->pad_8f4 + 0xfc),(iptr)local_44,(iptr)&this->control_list,
               local_14.left,local_14.top);
  }
  else {
    sprite_draw
              ((Sprite *)(this->pad_8f4 + 0xc0),(iptr)local_34,(iptr)&this->control_list,
               local_14.left,local_14.top);
  }
  wnd_blit_surface_rect((DibSurface *)&this->control_list,(iptr)&local_14);
  wnd_flush_paint();
  return;
}
#undef human_civ
#undef local_44
#undef local_34
#undef local_24
#undef local_14

/* 004d60a5 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define local_44 (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_34 (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
#define local_24 (*(i8 (*)[16])(frame_ + FRAME_OFF(36)))
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(52)))
void __thiscall spaceship_wnd_draw_launch_btn(SpaceshipWindow *this,int param_1,int param_2)

{
  i8 frame_[FRAME_OFF(72)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((((this->ship_civ == human_civ) && (this->launch_state != 3)) && (this->launch_state != 0)) &&
     (this->launch_state != 2)) {
    SetRect(&local_14,0x22f,0x1a1,0x272,0x1c5);
    if (param_2 == 0) {
      sprite_draw
                ((Sprite *)(this->pad_8f4 + 0x138),(iptr)local_24,(iptr)&this->control_list,
                 local_14.left,local_14.top);
    }
    else if (param_1 == 0) {
      sprite_draw
                ((Sprite *)(this->pad_8f4 + 0x1b0),(iptr)local_44,(iptr)&this->control_list,
                 local_14.left,local_14.top);
    }
    else {
      sprite_draw
                ((Sprite *)(this->pad_8f4 + 0x174),(iptr)local_34,(iptr)&this->control_list,
                 local_14.left,local_14.top);
    }
    wnd_blit_surface_rect((DibSurface *)&this->control_list,(iptr)&local_14);
    wnd_flush_paint();
  }
  return;
}
#undef human_civ
#undef local_44
#undef local_34
#undef local_24
#undef local_14

/* 004d61c3 auto */
#define local_10 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_c (*(SpaceshipWindow * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl spaceship_video_on_lbuttonup(i32 param_1,i32 param_2)

{
  int iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = wnd_get_active_child();
  if (local_8 == 0) {
    local_8 = 0;
  }
  else {
    local_8 -= 0x48;
  }
  local_c = (SpaceshipWindow *)spaceship_wnd;
  if (*(int *)(spaceship_wnd + 0xae0) == 2) {
    wnd_end_modal_loop((C_00408010_b8 *)(*(int *)(spaceship_wnd + 0x1da8) + 0x48));
  }
  else {
    iVar1 = clickmap_hit_test
                      ((ClickMapHitTestView *)(spaceship_wnd + 0xae4),param_1,param_2,(iptr)&local_10,0);
    if (iVar1 != -1) {
      if (local_10 == 0) {
        spaceship_wnd_draw_close_btn(local_c,1,0);
        if (local_c->field_8f0 == 0) {
          if (local_c->field_62c != 0) {
            game_timer_destroy(local_c->field_62c);
            local_c->field_62c = 0;
          }
          if (local_c->field_ae0 != 3) {
            do {
              iVar1 = spaceship_wnd_type_char(local_c,0);
            } while (iVar1 != 0);
            local_c->field_8f0 = 1;
            spaceship_wnd_draw_close_btn(local_c,1,1);
          }
        }
        else {
          wnd_end_modal_loop((C_00408010_b8 *)(local_8 + 0x48));
        }
      }
      else if (((local_10 == 1) && (local_c->field_ae0 == 1)) && (local_c->field_8f0 != 0)) {
        spaceship_wnd_draw_launch_btn(local_c,1,0);
        local_c->field_ae0 = 2;
        wnd_end_modal_loop((C_00408010_b8 *)(local_8 + 0x48));
      }
    }
  }
  return;
}
#undef local_10
#undef local_c
#undef local_8

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
#define local_1c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(12)))
void __cdecl spaceship_wnd_starfield_tick(void)

{
  int *piVar1;
  int iVar3;
  int iVar4;
  i32 uVar5;
  int iVar6;
  iptr iVar2;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar2 = spaceship_wnd;
  win_flush_pending_msgs();
  for (local_1c = 0; local_1c < 0x50; local_1c++) {
    iVar3 = *(int *)(iVar2 + 0x1db8 + local_1c * 0xc) / *(int *)(iVar2 + 0x1dc0 + local_1c * 0xc) +
            0x140;
    iVar4 = *(int *)(iVar2 + 0x1dbc + local_1c * 0xc) / *(int *)(iVar2 + 0x1dc0 + local_1c * 0xc) +
            0xf0;
    piVar1 = (int *)(iVar2 + 0x1db8 + local_1c * 0xc);
    *piVar1 = *piVar1 + 0xfa;
    piVar1 = (int *)(iVar2 + 0x1dbc + local_1c * 0xc);
    *piVar1 = *piVar1 + 300;
    piVar1 = (int *)(iVar2 + 0x1dc0 + local_1c * 0xc);
    *piVar1 = *piVar1 - 1;
    if (*(int *)(iVar2 + 0x1dc0 + local_1c * 0xc) == 0) {
      uVar5 = rand_range(0xffff8300,32000);
      *(i32 *)(iVar2 + 0x1db8 + local_1c * 0xc) = uVar5;
      uVar5 = rand_range(0xffffa240,24000);
      *(i32 *)(iVar2 + 0x1dbc + local_1c * 0xc) = uVar5;
      uVar5 = rand_range(0x32,100);
      *(i32 *)(iVar2 + 0x1dc0 + local_1c * 0xc) = uVar5;
    }
    local_14 = *(int *)(iVar2 + 0x1db8 + local_1c * 0xc) / *(int *)(iVar2 + 0x1dc0 + local_1c * 0xc)
               + 0x140;
    local_18 = *(int *)(iVar2 + 0x1dbc + local_1c * 0xc) / *(int *)(iVar2 + 0x1dc0 + local_1c * 0xc)
               + 0xf0;
    if ((((0x280 < local_14) || (local_14 < 0)) || (0x1e0 < local_18)) || (local_18 < 0)) {
      uVar5 = rand_range(0xffff8300,32000);
      *(i32 *)(iVar2 + 0x1db8 + local_1c * 0xc) = uVar5;
      uVar5 = rand_range(0xffffa240,24000);
      *(i32 *)(iVar2 + 0x1dbc + local_1c * 0xc) = uVar5;
      uVar5 = rand_range(0x32,100);
      *(i32 *)(iVar2 + 0x1dc0 + local_1c * 0xc) = uVar5;
      local_14 = *(int *)(iVar2 + 0x1db8 + local_1c * 0xc) /
                 *(int *)(iVar2 + 0x1dc0 + local_1c * 0xc) + 0x140;
      local_18 = *(int *)(iVar2 + 0x1dbc + local_1c * 0xc) /
                 *(int *)(iVar2 + 0x1dc0 + local_1c * 0xc) + 0xf0;
    }
    if (((iVar3 < 0x280) && (0 < iVar3)) && ((iVar4 < 0x1e0 && (0 < iVar4)))) {
      iVar6 = surface_get_pixel((DibSurface *)(iVar2 + 0xb8),iVar3,iVar4);
      if (iVar6 == 0x29) {
        surface_set_pixel((DibSurface *)(iVar2 + 0xb8),iVar3,iVar4,10);
      }
    }
    if (((local_14 < 0x280) && (0 < local_14)) && ((local_18 < 0x1e0 && (0 < local_18)))) {
      iVar3 = surface_get_pixel((DibSurface *)(iVar2 + 0xb8),local_14,local_18);
      if (iVar3 == 10) {
        surface_set_pixel((DibSurface *)(iVar2 + 0xb8),local_14,local_18,0x29);
      }
    }
  }
  wnd_blit_surface((DibSurface *)(iVar2 + 0xb8));
  return;
}
#undef local_1c
#undef local_18
#undef local_14

/* 004d6744 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl spaceship_wnd_on_key(int param_1)

{
  iptr this;
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = wnd_get_active_child();
  this = spaceship_wnd;
  if (local_8 == 0) {
    local_8 = 0;
  }
  else {
    local_8 -= 0x48;
  }
  if ((0xcf < param_1) && (param_1 < 0xd3)) {
    if (*(int *)(spaceship_wnd + 0xae0) == 2) {
      wnd_end_modal_loop((C_00408010_b8 *)(*(int *)(spaceship_wnd + 0x1da8) + 0x48));
    }
    else {
      spaceship_wnd_draw_close_btn((SpaceshipWindow *)spaceship_wnd,1,0);
      if (*(int *)(this + 0x8f0) == 0) {
        if (*(int *)(this + 0x62c) != 0) {
          game_timer_destroy(*(i32 *)(this + 0x62c));
          *(i32 *)(this + 0x62c) = 0;
        }
        do {
          iVar1 = spaceship_wnd_type_char((SpaceshipWindow *)this,0);
        } while (iVar1 != 0);
        *(i32 *)(this + 0x8f0) = 1;
        spaceship_wnd_draw_close_btn((SpaceshipWindow *)this,1,1);
      }
      else {
        wnd_end_modal_loop((C_00408010_b8 *)(local_8 + 0x48));
      }
    }
  }
  return;
}
#undef local_8

/* 004d686b auto */
void __cdecl spaceship_video_on_end(void)

{
  if (*(int *)(spaceship_wnd + 0x1da8) != 0) {
    wnd_end_modal_loop((C_00408010_b8 *)(*(int *)(spaceship_wnd + 0x1da8) + 0x48));
  }
  return;
}

/* 004d68a7 auto */
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(SpaceshipWindow * *)(frame_ + FRAME_OFF(8)))
void __cdecl spaceship_wnd_on_lbuttondown(i32 param_1,i32 param_2)

{
  int iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = (SpaceshipWindow *)spaceship_wnd;
  if (((*(int *)(spaceship_wnd + 0x1db0) == 0) && (*(int *)(spaceship_wnd + 0x1dac) == 0)) &&
     (iVar1 = clickmap_hit_test
                        ((ClickMapHitTestView *)(spaceship_wnd + 0xae4),param_1,param_2,(iptr)&local_c,0),
     iVar1 != -1)) {
    if (local_c == 0) {
      local_8[1].pad_ae4[0x310] = 1;
      local_8[1].pad_ae4[0x311] = '\0';
      local_8[1].pad_ae4[0x312] = '\0';
      local_8[1].pad_ae4[0x313] = '\0';
      spaceship_wnd_draw_close_btn(local_8,1,0);
      if ((local_8->field_ae0 == 1) && (local_8->field_630 != 0)) {
        game_timer_destroy(local_8->field_630);
        local_8->field_630 = 0;
      }
      wnd_blit_surface((DibSurface *)&local_8->field_b8);
    }
    else if (((local_c == 1) && (local_8->field_ae0 == 1)) && (local_8->field_8f0 != 0)) {
      local_8[1].pad_ae4[0x314] = 1;
      local_8[1].pad_ae4[0x315] = '\0';
      local_8[1].pad_ae4[0x316] = '\0';
      local_8[1].pad_ae4[0x317] = '\0';
      spaceship_wnd_draw_launch_btn(local_8,1,0);
      if ((local_8->field_ae0 == 1) && (local_8->field_630 != 0)) {
        game_timer_destroy(local_8->field_630);
        local_8->field_630 = 0;
      }
      wnd_blit_surface((DibSurface *)&local_8->field_b8);
    }
  }
  return;
}
#undef local_c
#undef local_8

/* 004d6a30 auto */
#define local_10 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_c (*(SpaceshipWindow * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl spaceship_wnd_on_lbuttonup(i32 param_1,i32 param_2)

{
  int iVar1;
  u32 uVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = (SpaceshipWindow *)spaceship_wnd;
  local_8 = wnd_get_active_child();
  if (local_8 == 0) {
    local_8 = 0;
  }
  else {
    local_8 -= 0x48;
  }
  if (local_c->field_ae0 == 2) {
    wnd_end_modal_loop((C_00408010_b8 *)(*(int *)(local_c[1].pad_ae4 + 0x30c) + 0x48));
  }
  else if ((*(int *)(local_c[1].pad_ae4 + 0x314) != 0) ||
          (*(int *)(local_c[1].pad_ae4 + 0x310) != 0)) {
    if (*(int *)(local_c[1].pad_ae4 + 0x310) != 0) {
      spaceship_wnd_draw_close_btn(local_c,1,1);
    }
    if (*(int *)(local_c[1].pad_ae4 + 0x314) != 0) {
      spaceship_wnd_draw_launch_btn(local_c,1,1);
    }
    iVar1 = clickmap_hit_test
                      ((ClickMapHitTestView *)local_c->pad_ae4,param_1,param_2,(iptr)&local_10,0);
    if (iVar1 != -1) {
      if (local_10 == 0) {
        if (*(int *)(local_c[1].pad_ae4 + 0x310) != 0) {
          if (local_c->field_8f0 == 0) {
            if (local_c->field_62c != 0) {
              game_timer_destroy(local_c->field_62c);
              local_c->field_62c = 0;
            }
            if (local_c->field_ae0 != 3) {
              do {
                iVar1 = spaceship_wnd_type_char(local_c,0);
              } while (iVar1 != 0);
              local_c->field_8f0 = 1;
            }
          }
          else {
            wnd_end_modal_loop((C_00408010_b8 *)(local_8 + 0x48));
          }
        }
      }
      else if ((local_10 == 1) && (*(int *)(local_c[1].pad_ae4 + 0x314) != 0)) {
        local_c->field_ae0 = 2;
        wnd_end_modal_loop((C_00408010_b8 *)(local_8 + 0x48));
      }
    }
    if (((*(int *)(local_c[1].pad_ae4 + 0x310) != 0) &&
        (local_c[1].pad_ae4[0x310] = '\0', local_c[1].pad_ae4[0x311] = '\0',
        local_c[1].pad_ae4[0x312] = '\0', local_c[1].pad_ae4[0x313] = '\0', local_c->field_ae0 == 1)
        ) && (local_c->field_630 == 0)) {
      uVar2 = game_timer_create(ADDR(0x403a53, spaceship_wnd_blink_launch_btn),500,0xffffffff);
      local_c->field_630 = uVar2;
    }
    if (((*(int *)(local_c[1].pad_ae4 + 0x314) != 0) &&
        (local_c[1].pad_ae4[0x314] = '\0', local_c[1].pad_ae4[0x315] = '\0',
        local_c[1].pad_ae4[0x316] = '\0', local_c[1].pad_ae4[0x317] = '\0', local_c->field_ae0 == 1)
        ) && (local_c->field_630 == 0)) {
      uVar2 = game_timer_create(ADDR(0x403a53, spaceship_wnd_blink_launch_btn),500,0xffffffff);
      local_c->field_630 = uVar2;
    }
  }
  return;
}
#undef local_10
#undef local_c
#undef local_8

/* 004d6cbc auto */
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(SpaceshipWindow * *)(frame_ + FRAME_OFF(8)))
void __cdecl spaceship_wnd_on_mousemove(i32 param_1,i32 param_2)

{
  int iVar1;
  u32 uVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = (SpaceshipWindow *)spaceship_wnd;
  iVar1 = clickmap_hit_test
                    ((ClickMapHitTestView *)(spaceship_wnd + 0xae4),param_1,param_2,(iptr)&local_c,0);
  if (iVar1 == -1) {
    if (((*(int *)(local_8[1].pad_ae4 + 0x310) != 0) &&
        (spaceship_wnd_draw_close_btn(local_8,1,1), local_8->field_ae0 == 1)) &&
       (local_8->field_630 == 0)) {
      uVar2 = game_timer_create(ADDR(0x403a53, spaceship_wnd_blink_launch_btn),500,0xffffffff);
      local_8->field_630 = uVar2;
    }
    if (((*(int *)(local_8[1].pad_ae4 + 0x314) != 0) &&
        (spaceship_wnd_draw_launch_btn(local_8,1,1), local_8->field_ae0 == 1)) &&
       (local_8->field_630 == 0)) {
      uVar2 = game_timer_create(ADDR(0x403a53, spaceship_wnd_blink_launch_btn),500,0xffffffff);
      local_8->field_630 = uVar2;
    }
  }
  else if (local_c == 0) {
    if (*(int *)(local_8[1].pad_ae4 + 0x314) == 0) {
      if (((*(int *)(local_8[1].pad_ae4 + 0x310) != 0) &&
          (spaceship_wnd_draw_close_btn(local_8,1,0), local_8->field_ae0 == 1)) &&
         (local_8->field_630 != 0)) {
        game_timer_destroy(local_8->field_630);
        local_8->field_630 = 0;
      }
    }
    else {
      spaceship_wnd_draw_launch_btn(local_8,1,1);
      if ((local_8->field_ae0 == 1) && (local_8->field_630 == 0)) {
        uVar2 = game_timer_create(ADDR(0x403a53, spaceship_wnd_blink_launch_btn),500,0xffffffff);
        local_8->field_630 = uVar2;
      }
    }
  }
  else if (local_c == 1) {
    if (*(int *)(local_8[1].pad_ae4 + 0x310) == 0) {
      if (((*(int *)(local_8[1].pad_ae4 + 0x314) != 0) &&
          (spaceship_wnd_draw_launch_btn(local_8,1,0), local_8->field_ae0 == 1)) &&
         (local_8->field_630 != 0)) {
        game_timer_destroy(local_8->field_630);
        local_8->field_630 = 0;
      }
    }
    else {
      spaceship_wnd_draw_close_btn(local_8,1,1);
      if ((local_8->field_ae0 == 1) && (local_8->field_630 == 0)) {
        uVar2 = game_timer_create(ADDR(0x403a53, spaceship_wnd_blink_launch_btn),500,0xffffffff);
        local_8->field_630 = uVar2;
      }
    }
  }
  return;
}
#undef local_c
#undef local_8

/* 00596b00 auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
iptr __cdecl spaceship_part_limit(iptr civ,int param_2)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = (&spaceship_part_max_counts)[param_2 * 3];
  if ((param_2 == 1) || (param_2 == 2)) {
    iVar1 = (civs[civ].spaceship_parts[0] + 1) - (param_2 * 2 - 2);
    local_8 = int_clamp(local_8,0,(int)(iVar1 + (iVar1 >> 0x1f & 3U)) >> 2);
  }
  else if (param_2 != 0) {
    iVar1 = (civs[civ].spaceship_parts[0] + 1) - (param_2 * 4 - 0xc);
    local_8 = int_clamp(local_8,0,(int)(iVar1 + (iVar1 >> 0x1f & 7U)) >> 3);
    if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
      local_8 = int_clamp(local_8,0,1);
    }
    if (local_8 < 0) {
      local_8 = 0;
    }
  }
  return local_8;
}
#undef local_8

/* 00596c08 auto */
i32 __cdecl spaceship_part_count(iptr civ,int param_2)

{
  short sVar1;
  i32 uVar2;
  
  sVar1 = civs[civ].spaceship_parts[param_2];
  uVar2 = spaceship_part_limit(civ,param_2);
  uVar2 = int_clamp((int)sVar1,0,uVar2);
  return uVar2;
}

/* 00596c61 auto */
int __cdecl spaceship_group_limit(iptr civ,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (param_2 == 0) {
    iVar1 = spaceship_part_limit(civ,0);
  }
  else if (param_2 == 1) {
    iVar2 = spaceship_part_limit(civ,2);
    iVar1 = spaceship_part_limit(civ,1);
    iVar1 += iVar2;
  }
  else {
    iVar2 = spaceship_part_limit(civ,3);
    iVar3 = spaceship_part_limit(civ,4);
    iVar1 = spaceship_part_limit(civ,5);
    iVar1 = iVar1 + iVar2 + iVar3;
  }
  return iVar1;
}

/* 00596ced auto */
int __cdecl spaceship_group_max(int param_1)

{
  int iVar1;
  
  iVar1 = spaceship_part_max_counts;
  if (param_1 != 0) {
    if (param_1 == 1) {
      iVar1 = spaceship_fuel_max + spaceship_propulsion_max;
    }
    else {
      iVar1 = spaceship_solar_panel_max + spaceship_habitation_max + spaceship_life_support_max;
    }
  }
  return iVar1;
}

/* 00596d3c auto */
int __cdecl spaceship_group_count(iptr civ,iptr param_2)

{
  int iVar1;
  
  if (param_2 == 0) {
    iVar1 = (int)civs[civ].spaceship_parts[0];
  }
  else if (param_2 == 1) {
    iVar1 = (int)civs[civ].spaceship_parts[1] + (int)civs[civ].spaceship_parts[2];
  }
  else {
    iVar1 = (int)civs[civ].spaceship_parts[3] + (int)civs[civ].spaceship_parts[4] +
            (int)civs[civ].spaceship_parts[5];
  }
  return iVar1;
}

/* 00596e06 auto */
int __cdecl spaceship_group_count_clamped(iptr civ,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (param_2 == 0) {
    iVar1 = spaceship_part_count(civ,0);
  }
  else if (param_2 == 1) {
    iVar2 = spaceship_part_count(civ,2);
    iVar1 = spaceship_part_count(civ,1);
    iVar1 += iVar2;
  }
  else {
    iVar2 = spaceship_part_count(civ,3);
    iVar3 = spaceship_part_count(civ,4);
    iVar1 = spaceship_part_count(civ,5);
    iVar1 = iVar1 + iVar2 + iVar3;
  }
  return iVar1;
}

/* 00596e92 auto */
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
int __cdecl spaceship_component_thrust(int param_1)

{
  int iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  for (local_c = 0; local_c < param_1; local_c++) {
    iVar1 = local_8 + 1;
    if (3 < local_c) {
      iVar1 = local_8 + 2;
    }
    local_8 = iVar1;
    if (5 < local_c) {
      local_8++;
    }
  }
  return local_8;
}
#undef local_c
#undef local_8

/* 00596eec auto */
#define spaceship_energy_pct (*(int *)((u8 *)&g.d_006ad0e8))
#define spaceship_fuel_pct (*(int *)((u8 *)&g.d_006ad0dc))
#define spaceship_success_pct (*(int *)((u8 *)&g.d_006ad0ec))
#define spaceship_support_pct (*(int *)((u8 *)&g.d_006ad0f0))
#define local_1c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(12)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_c (*(uint *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(24)))
void __cdecl spaceship_calc_stats(iptr civ,int param_2)

{
  byte bVar1;
  int iVar2;
  iptr iVar3;
  int iVar4;
  int iVar5;
  i32 uVar6;
  i32 uVar7;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar2 = civ_spaceship_launched(civ);
  if (iVar2 == 0) {
    iVar2 = civ_has_advance(civ,0x20);
    if (iVar2 != 0) {
      civs[civ].spaceship_flags = civs[civ].spaceship_flags | 8;
    }
  }
  bVar1 = civs[civ].spaceship_flags;
  spaceship_mass = 0;
  for (local_1c = 0; local_1c < 6; local_1c++) {
    spaceship_mass = spaceship_mass +
                   (int)civs[civ].spaceship_parts[local_1c] *
                   *(int *)(&spaceship_part_masses + local_1c * 0xc);
  }
  local_18 = spaceship_mass;
  for (local_1c = 0; local_1c < 6; local_1c++) {
    if (civs[civ].spaceship_parts[local_1c] == 0) {
      local_18 += *(int *)(&spaceship_part_masses + local_1c * 0xc);
    }
  }
  spaceship_success_pct = 100;
  iVar2 = spaceship_part_count(civ,4);
  uVar7 = 99;
  uVar6 = 1;
  iVar3 = spaceship_part_count(civ,3);
  iVar4 = int_clamp(iVar3,uVar6,uVar7);
  spaceship_support_pct = (iVar2 * 100) / iVar4;
  if (param_2 != 0) {
    iVar2 = int_clamp(spaceship_support_pct,0,100);
    spaceship_success_pct = (iVar2 * spaceship_success_pct) / 100;
  }
  iVar2 = spaceship_part_count(civ,5);
  uVar7 = 99;
  uVar6 = 1;
  iVar4 = spaceship_part_count(civ,3);
  iVar5 = spaceship_part_count(civ,4);
  iVar4 = int_clamp(iVar4 + iVar5,uVar6,uVar7);
  spaceship_energy_pct = (iVar2 * 200) / iVar4;
  iVar2 = int_clamp(spaceship_energy_pct,0,100);
  spaceship_success_pct = (iVar2 * spaceship_success_pct) / 100;
  iVar2 = spaceship_part_count(civ,2);
  uVar7 = 99;
  uVar6 = 1;
  iVar3 = spaceship_part_count(civ,1);
  iVar4 = int_clamp(iVar3,uVar6,uVar7);
  spaceship_fuel_pct = (iVar2 * 100) / iVar4;
  local_c = (uint)cosmic.mass_thrust_paradigm;
  if ((bVar1 & 8) != 0) {
    local_c = (int)(local_c * 3) >> 2;
  }
  local_8 = 1;
  for (; 100 < local_c; local_c = (int)local_c >> 1) {
    local_8 = local_8 << 1;
  }
  iVar5 = spaceship_mass * local_c;
  uVar6 = spaceship_part_count(civ,2);
  iVar2 = spaceship_component_thrust(uVar6);
  iVar2 = iVar2 * 10;
  uVar7 = 0;
  uVar6 = spaceship_part_count(civ,1);
  iVar4 = spaceship_component_thrust(uVar6);
  iVar2 = int_clamp(iVar4 * 10,uVar7,iVar2);
  spaceship_flight_time = iVar5 / (iVar2 + 1);
  uVar6 = spaceship_part_count(civ,2);
  iVar2 = spaceship_component_thrust(uVar6);
  iVar2 = iVar2 * 10;
  uVar7 = 0;
  uVar6 = spaceship_part_count(civ,1);
  iVar4 = spaceship_component_thrust(uVar6);
  iVar2 = int_clamp(iVar4 * 10,uVar7,iVar2);
  local_10 = (int)(local_c * local_18) / (iVar2 + 1);
  iVar2 = spaceship_component_thrust((int)civs[civ].spaceship_parts[2]);
  iVar2 = iVar2 * 10;
  uVar6 = 0;
  iVar4 = spaceship_component_thrust((int)civs[civ].spaceship_parts[1]);
  iVar2 = int_clamp(iVar4 * 10,uVar6,iVar2);
  local_14 = (int)(local_c * local_18) / (iVar2 + 1);
  if (1 < local_8) {
    spaceship_flight_time = local_8 * spaceship_flight_time;
    local_10 = local_8 * local_10;
    local_14 = local_8 * local_14;
  }
  if (0x96 < spaceship_flight_time) {
    spaceship_success_pct -= (spaceship_flight_time - 0x96) / 10;
  }
  spaceship_success_pct = int_clamp(spaceship_success_pct,0,100);
  iVar2 = civ_spaceship_launched(civ);
  if (iVar2 == 0) {
    uVar6 = spaceship_part_count(civ,3);
    civs[civ].spaceship_population = (i16)uVar6;
    uVar6 = game_turn_to_year((int)game.turn);
    civs[civ].spaceship_launch_year = (i16)uVar6;
    uVar6 = game_turn_to_year((int)game.turn);
    civs[civ].spaceship_arrival_year = (short)uVar6 + (short)(local_10 / 10);
    iVar2 = game_turn_to_year((int)game.turn);
    spaceship_projected_arrival_year = iVar2 + local_14 / 10;
  }
  return;
}
#undef spaceship_energy_pct
#undef spaceship_fuel_pct
#undef spaceship_success_pct
#undef spaceship_support_pct
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 005973fd auto */
#define city (*(iptr *)(frame_ + FRAME_OFF(4)))
#define civ2 (*(iptr *)(frame_ + FRAME_OFF(8)))
void __cdecl spaceship_launch(iptr civ)

{
  uint *puVar1;
  iptr iVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  civs[civ].spaceship_flags = civs[civ].spaceship_flags | 2;
  if (game.first_launch_turn < 0) {
    game.first_launch_turn = game.turn;
  }
  iVar2 = civ_name_plural(civ);
  text_set_string_arg(0,iVar2);
  text_set_number_arg(0,(int)civs[civ].spaceship_arrival_year);
  if (2 < game.multiplayer) {
    net_send_text_args(0xb,0xff,1,1,civ,0);
  }
  if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
    popup_game(ADDR(0x634fa8, ((u8 *)&g.d_00634fa8)));
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
          && (iVar3 = civ_spaceship_launched(civ2), iVar3 != 0)) &&
         (civs[civ].spaceship_arrival_year < civs[civ2].spaceship_arrival_year)) {
        if (game.difficulty < 4) {
          if ((game.difficulty < 2) || (civs[civ].reputation == '\0')) {
            diplo_set_treaty_flags(civ,civ2,0x10000);
          }
          else {
            puVar1 = (uint *)(civ * 4 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ2 * 0x594);
            *puVar1 = *puVar1 | 0x20;
          }
        }
        else if ((*(byte *)&civs[civ].treaties[civ2] & 8) == 0) {
          puVar1 = (uint *)(civ * 4 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ2 * 0x594);
          *puVar1 = *puVar1 & 0xffffffd9;
          puVar1 = (uint *)(civ * 4 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ2 * 0x594);
          *puVar1 = *puVar1 | 0x80840;
        }
        else {
          puVar1 = (uint *)(civ * 4 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ2 * 0x594);
          *puVar1 = *puVar1 | 0x20;
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
#define local_30c (*(Dialog *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(760)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(764)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(768)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(772)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(776)))
void __cdecl spaceship_status_dialog(iptr civ,int param_2)

{
  short sVar1;
  iptr iVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(784)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_30c,0x2000);
  local_8 = 0;
  local_14 = 0;
  spaceship_calc_stats(civ,1);
  if (civs[civ].spaceship_parts[3] == 0) {
    param_2 = 0;
  }
  iVar2 = civ_get_adjective(civ);
  text_set_string_arg(2,iVar2);
  iVar2 = civ_leader_name(civ);
  text_set_string_arg(1,iVar2);
  iVar2 = civ_name_plural(civ);
  text_set_string_arg(0,iVar2);
  text_string_args_plus1 = 0;
  __strupr(&text_string_args);
  dialog_load_game_text(&local_30c,ADDR(0x634fb4, ((u8 *)&g.d_00634fb4)));
  for (local_18 = 0; local_18 < 6; local_18++) {
    sVar1 = civs[civ].spaceship_parts[local_18];
    iVar3 = spaceship_part_limit(civ,local_18);
    if (iVar3 < sVar1) {
      local_14 = 1;
    }
  }
  for (local_18 = 0; local_18 < 6; local_18++) {
    text_clear();
    text_append_string_id(*(i32 *)(label_string_ids + *(int *)(&spaceship_part_table + local_18 * 0xc) * 4)
                      );
    text_append_colon();
    text_append_int((int)civs[civ].spaceship_parts[local_18]);
    if ((local_14 != 0) && (local_18 == 0)) {
      text_append(ADDR(0x634fc0, ((u8 *)&g.d_00634fc0)));
    }
    dialog_add_option((DialogOptionList *)&local_30c,ADDR(0x679640, ((u8 *)&g.d_00679640)),0,0);
  }
  text_clear();
  dialog_add_option((DialogOptionList *)&local_30c,ADDR(0x679640, ((u8 *)&g.d_00679640)),0,0);
  text_clear();
  text_append_label(0x22);
  text_append_colon();
  text_append_int((int)civs[civ].spaceship_parts[3]);
  text_append(ADDR(0x634fc4, ((u8 *)&g.d_00634fc4)));
  dialog_add_option((DialogOptionList *)&local_30c,ADDR(0x679640, ((u8 *)&g.d_00679640)),0,0);
  text_clear();
  text_append_label(0x42);
  text_append_colon();
  text_append_int(spaceship_support_pct);
  text_append_percent();
  dialog_add_option((DialogOptionList *)&local_30c,ADDR(0x679640, ((u8 *)&g.d_00679640)),0,0);
  text_clear();
  text_append_label(0xcd);
  text_append_colon();
  text_append_int(spaceship_energy_pct);
  text_append_percent();
  dialog_add_option((DialogOptionList *)&local_30c,ADDR(0x679640, ((u8 *)&g.d_00679640)),0,0);
  text_clear();
  text_append_label(0xce);
  text_append_colon();
  text_append_int(spaceship_mass / 10);
  text_append(ADDR(0x634fcc, ((u8 *)&g.d_00634fcc)));
  text_append_int(spaceship_mass % 10);
  text_append(ADDR(0x634fd0, ((u8 *)&g.d_00634fd0)));
  text_append_label(0xd1);
  dialog_add_option((DialogOptionList *)&local_30c,ADDR(0x679640, ((u8 *)&g.d_00679640)),0,0);
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
  dialog_add_option((DialogOptionList *)&local_30c,ADDR(0x679640, ((u8 *)&g.d_00679640)),0,0);
  text_clear();
  text_append_label(0xcf);
  text_append_colon();
  text_append_int(spaceship_flight_time / 10);
  text_append(ADDR(0x634fd4, ((u8 *)&g.d_00634fd4)));
  text_append_int(spaceship_flight_time % 10);
  text_append_space();
  text_append_label(0xd2);
  dialog_add_option((DialogOptionList *)&local_30c,ADDR(0x679640, ((u8 *)&g.d_00679640)),0,0);
  text_clear();
  text_append_label(0xd0);
  text_append_colon();
  text_append(ADDR(0x634fd8, ((u8 *)&g.d_00634fd8)));
  text_append_int(spaceship_success_pct);
  text_append_percent();
  text_append(ADDR(0x634fe0, ((u8 *)&g.d_00634fe0)));
  dialog_add_option((DialogOptionList *)&local_30c,ADDR(0x679640, ((u8 *)&g.d_00679640)),0,0);
  iVar3 = civ_spaceship_launched(civ);
  if (iVar3 == 0) {
    if ((((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) && (param_2 != 0)) &&
       (spaceship_success_pct != 0)) {
      iVar2 = label_string(*(i32 *)(label_string_ids + 0x354));
      dialog_add_button((C_0040bc40_3c *)&local_30c,iVar2);
    }
  }
  else {
    text_clear();
    text_append(ADDR(0x634fe8, ((u8 *)&g.d_00634fe8)));
    if (civs[civ].spaceship_arrival_year < game.year) {
      text_append_label(0xd4);
    }
    else {
      text_append_label(0xd3);
      text_append(ADDR(0x634ff0, ((u8 *)&g.d_00634ff0)));
      text_append_label(0xda);
      text_append_space();
      text_append_int((int)civs[civ].spaceship_arrival_year);
    }
    text_append(ADDR(0x634ff4, ((u8 *)&g.d_00634ff4)));
    dialog_add_option((DialogOptionList *)&local_30c,ADDR(0x679640, ((u8 *)&g.d_00679640)),0,0);
  }
  dlg_show_modal(&local_30c,0);
  if (local_30c.field_dc != 0) {
    text_set_number_arg(0,spaceship_success_pct);
    iVar3 = popup_game(ADDR(0x634ffc, ((u8 *)&g.d_00634ffc)));
    if (iVar3 != 0) {
      spaceship_launch(civ);
    }
  }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_00597d4b */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
  return;
}
#undef spaceship_energy_pct
#undef spaceship_fuel_pct
#undef spaceship_success_pct
#undef spaceship_support_pct
#undef local_30c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00597d6f auto */
#define civ2 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
iptr __cdecl spaceship_choose_part_group(iptr civ,iptr param_2)

{
  short sVar1;
  bool bVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  spaceship_calc_stats(civ,0);
  iVar4 = civ_spaceship_launched(civ);
  if (iVar4 != 0) {
    return 0xffffffff;
  }
  sVar1 = 9999;
  for (civ2 = 1; civ2 < 8; civ2++) {
    if ((((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) &&
        (0 < civs[civ2].spaceship_arrival_year)) &&
       (civs[civ2].spaceship_arrival_year < sVar1)) {
      sVar1 = civs[civ2].spaceship_arrival_year;
    }
  }
  if (((civs[civ].spaceship_arrival_year == 0) ||
      (0xe < (int)civs[civ].spaceship_arrival_year - (int)game.year)) ||
     (sVar1 <= civs[civ].spaceship_arrival_year)) {
    bVar2 = false;
  }
  else {
    bVar2 = true;
  }
  bVar3 = false;
  if (param_2 == 0) {
    iVar4 = spaceship_group_count_clamped(civ,2);
    iVar5 = spaceship_group_limit(civ,2);
    if (iVar4 < iVar5) {
      bVar3 = true;
    }
    else if (!bVar2) {
      iVar4 = spaceship_group_count_clamped(civ,1);
      iVar5 = spaceship_group_limit(civ,1);
      if (iVar4 < iVar5) {
        bVar3 = true;
      }
    }
  }
  if ((!bVar3) && ((param_2 != 1 || (!bVar2)))) {
    iVar4 = spaceship_group_count_clamped(civ,param_2);
    iVar5 = spaceship_group_limit(civ,param_2);
    if ((iVar4 < iVar5) && (iVar4 = spaceship_group_can_build(civ,param_2), iVar4 != 0))
    goto LAB_0059803b;
  }
  for (local_c = 2; (int)(uint)(param_2 == 0) <= local_c; local_c--) {
    iVar4 = spaceship_group_can_build(civ,local_c);
    if ((iVar4 != 0) && ((local_c != 1 || (!bVar2)))) {
      iVar4 = spaceship_group_count_clamped(civ,local_c);
      iVar5 = spaceship_group_limit(civ,local_c);
      if (iVar4 < iVar5) {
        param_2 = local_c;
        break;
      }
    }
  }
LAB_0059803b:
  if (param_2 == 0) {
    for (civ2 = 1; civ2 < 8; civ2++) {
      if (((((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) &&
           (iVar4 = civ_spaceship_launched(civ2), iVar4 != 0)) &&
          (civs[civ2].spaceship_arrival_year <= spaceship_projected_arrival_year)) &&
         ((iVar4 = spaceship_group_full(civ,1), iVar4 == 0 &&
          (iVar4 = civ_has_advance(civ,(int)improvements[0x24].preq), iVar4 != 0)))) {
        sVar1 = civs[civ].spaceship_parts[1];
        iVar4 = spaceship_part_limit(civ,1);
        if (sVar1 <= iVar4) {
          return 1;
        }
        sVar1 = civs[civ].spaceship_parts[2];
        iVar4 = spaceship_part_limit(civ,2);
        if (sVar1 <= iVar4) {
          return 1;
        }
      }
    }
  }
  iVar4 = spaceship_group_can_build(civ,param_2);
  if (iVar4 == 0) {
    param_2 = -2;
  }
  return param_2;
}
#undef civ2
#undef local_c

/* 00598197 auto */
#define spaceship_success_pct (*(int *)((u8 *)&g.d_006ad0ec))
#define civ2 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(8)))
#define civ3 (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(16)))
#define civ4 (*(iptr *)(frame_ + FRAME_OFF(20)))
int __cdecl spaceship_add_part(iptr civ,iptr param_2)

{
  short *psVar1;
  short sVar2;
  bool bVar3;
  int iVar4;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_18 = -1;
  spaceship_calc_stats(civ,0);
  iVar4 = civ_spaceship_launched(civ);
  if (iVar4 == 0) {
    while( true ) {
      if (param_2 == 0) {
        if (spaceship_part_max_counts <= civs[civ].spaceship_parts[0]) {
          return local_18;
        }
        local_18 = 0;
      }
      else if (param_2 == 1) {
        if ((spaceship_propulsion_max <= civs[civ].spaceship_parts[1]) &&
           (spaceship_fuel_max <= civs[civ].spaceship_parts[2])) {
          return local_18;
        }
        if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
          if (civs[civ].spaceship_parts[1] < civs[civ].spaceship_parts[2]) {
            local_18 = 1;
          }
          else {
            local_18 = 2;
          }
        }
        else {
          text_set_number_arg(0,(int)civs[civ].spaceship_parts[1]);
          text_set_number_arg(1,(int)civs[civ].spaceship_parts[2]);
          local_18 = popup_game(ADDR(0x635004, ((u8 *)&g.d_00635004)));
          local_18++;
        }
      }
      else {
        if (((spaceship_habitation_max <= civs[civ].spaceship_parts[3]) &&
            (spaceship_life_support_max <= civs[civ].spaceship_parts[4])) &&
           (spaceship_solar_panel_max <= civs[civ].spaceship_parts[5])) {
          return local_18;
        }
        if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
          sVar2 = 999;
          for (local_10 = 3; local_10 < 6; local_10++) {
            if (civs[civ].spaceship_parts[local_10] < sVar2) {
              sVar2 = civs[civ].spaceship_parts[local_10];
              local_18 = local_10;
            }
          }
        }
        else {
          text_set_number_arg(0,(int)civs[civ].spaceship_parts[3]);
          text_set_number_arg(1,(int)civs[civ].spaceship_parts[4]);
          text_set_number_arg(2,(int)civs[civ].spaceship_parts[5]);
          local_18 = popup_game(ADDR(0x635010, ((u8 *)&g.d_00635010)));
          local_18 += 3;
        }
      }
      if (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) ||
         ((int)civs[civ].spaceship_parts[local_18] < (&spaceship_part_max_counts)[local_18 * 3]
         )) break;
      text_set_label_arg(0,*(i32 *)
                            (label_string_ids + *(int *)(&spaceship_part_table + local_18 * 0xc) * 4));
      popup_game(ADDR(0x635018, ((u8 *)&g.d_00635018)));
    }
    iVar4 = civ_spaceship_exists(civ);
    if (iVar4 == 0) {
      civs[civ].spaceship_flags = civs[civ].spaceship_flags | 1;
      for (civ2 = 1; civ2 < 8; civ2++) {
        if (((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) &&
           ((civ2 == civ || (iVar4 = civ_spaceship_exists(civ2), iVar4 == 0)))) {
          for (civ3 = 1; civ3 < 8; civ3++) {
            civs[civ2].last_treaty_turn[civ3] = 0;
          }
        }
      }
    }
    psVar1 = (short *)(civ * 0x594 + ADDR(0x64caa8, ((u8 *)&civs + 1032)) + local_18 * 2);
    *psVar1 = *psVar1 + 1;
    spaceship_calc_stats(civ,0);
    if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
      bVar3 = true;
      for (local_18 = 0; local_18 < 3; local_18++) {
        if ((int)civs[civ].spaceship_parts[local_18] <
            (&spaceship_part_max_counts)[local_18 * 3]) {
          bVar3 = false;
        }
      }
      iVar4 = civ_spaceship_launched(civ);
      if ((iVar4 == 0) && (0x27 < spaceship_success_pct)) {
        if (bVar3) {
          spaceship_launch(civ);
        }
        else {
          civ4 = 0;
          for (civ2 = 1; civ2 < 8; civ2++) {
            if (((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) &&
               (iVar4 = civ_spaceship_launched(civ2), iVar4 != 0)) {
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
                  (iVar4 = civ_spaceship_launched(civ3), iVar4 != 0)) &&
                 (civs[civ3].spaceship_arrival_year < civs[0].spaceship_arrival_year)) {
                return local_18;
              }
            }
          }
          if (civ4 == 0) {
            bVar3 = 0x4b < spaceship_success_pct;
            if (!bVar3) {
              for (civ2 = 1; civ2 < 8; civ2++) {
                if ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) {
                  if (game.power_rank[civ] < game.power_rank[civ2]) {
                    bVar3 = true;
                    break;
                  }
                  iVar4 = civ_spaceship_exists(civ2);
                  if ((iVar4 != 0) && (999 < civs[civ2].gold)) {
                    bVar3 = true;
                    break;
                  }
                }
              }
            }
            if (bVar3) {
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
  return local_18;
}
#undef spaceship_success_pct
#undef civ2
#undef local_18
#undef civ3
#undef local_10
#undef civ4

/* 00598b4e auto */
#define civ2 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_304 (*(Dialog *)(frame_ + FRAME_OFF(12)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(768)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(772)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(776)))
void __cdecl spaceship_select_view_dialog(iptr param_1)

{
  bool bVar1;
  int civ;
  iptr iVar3;
  int iVar4;
  i32 uVar5;
  i8 frame_[FRAME_OFF(784)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_304,0x4000);
  local_8 = 0;
  dlg_load_game_section(&local_304,ADDR(0x635024, ((u8 *)&g.d_00635024)),1);
  bVar1 = false;
  for (civ2 = 1; civ2 < 8; civ2++) {
    civ = civ_spaceship_exists(civ2);
    if (civ != 0) {
      uVar5 = 0;
      civ = civ2;
      iVar3 = civ_name_plural(civ2);
      dialog_add_option((DialogOptionList *)&local_304,iVar3,civ,uVar5);
      bVar1 = true;
    }
  }
  if (bVar1) {
    civ = dlg_show_modal(&local_304,0);
    if (civ < 0) {
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_00598cc7 */ { dialog_dtor((Dialog *)((iptr)&local_304)); }
    }
    else {
      spaceship_wnd_load_parts(civ);
      iVar4 = spaceship_wnd_run(civ);
      if (iVar4 == 0) {
        (*(i8 *)((char *)&civ2 + 0)) = (byte)civ;
        spaceship_status_dialog(civ,(uint)game.human_players & 1 << ((byte)civ2 & 0x1f));
      }
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_00598cc7 */ { dialog_dtor((Dialog *)((iptr)&local_304)); }
    }
  }
  else {
    popup_game(ADDR(0x635030, ((u8 *)&g.d_00635030)));
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_00598cc7 */ { dialog_dtor((Dialog *)((iptr)&local_304)); }
  }
  return;
}
#undef civ2
#undef local_304
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00598ceb auto */
i32 __cdecl spaceship_race_active(void)

{
  i32 uVar1;
  
  if ((game.rules & 0x80) == 0) {
    if ((game.wonder_city[0x19] == -1) && ((game.human_players & game.advance_known_by[0x4c]) == 0))
    {
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

/* 005998b0 auto */
uint __cdecl spaceship_group_full(iptr civ,iptr param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = spaceship_group_max(param_2);
  iVar2 = spaceship_group_count(civ,param_2);
  return (uint)(iVar1 <= iVar2);
}

/* 00599910 auto */
i32 __cdecl spaceship_group_can_build(iptr civ,iptr param_2)

{
  int iVar1;
  
  iVar1 = spaceship_group_at_limit(civ,param_2);
  if ((((iVar1 == 0) || (iVar1 = spaceship_group_count(civ,param_2), iVar1 == 0)) &&
      (iVar1 = spaceship_group_full(civ,param_2), iVar1 == 0)) &&
     (iVar1 = civ_has_advance(civ,(int)improvements[param_2 + 0x23].preq), iVar1 != 0)) {
    return 1;
  }
  return 0;
}

/* 005999c0 auto */
uint __cdecl spaceship_group_at_limit(iptr civ,iptr param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = spaceship_group_count(civ,param_2);
  iVar2 = spaceship_group_limit(civ,param_2);
  return (uint)(iVar2 <= iVar1);
}
