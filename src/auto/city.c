/* The game, cities: growth, production, happiness, the city window and city view: functions translated from the original
 * (tools/gen_c.py, now edited directly), in address order. */
#include "auto_common.h"

/* 0040bdac auto */
void __cdecl
taxrate_balance(iptr param_1,iptr param_2,iptr param_3,iptr param_4,iptr param_5,iptr param_6)

{
  int iVar1;
  
  iVar1 = *(int *)(taxrate_dlg + 0x2dc);
  while (*(int *)param_3 + *(int *)param_2 + *(int *)param_1 < 10) {
    if (((*(int *)param_2 < iVar1) && (*(int *)param_2 < *(int *)param_4)) && (*(int *)param_5 == 0)
       ) {
      *(int *)param_2 = *(int *)param_2 + 1;
    }
    else if ((*(int *)param_3 < iVar1) && (*(int *)param_6 == 0)) {
      *(int *)param_3 = *(int *)param_3 + 1;
    }
    else if ((*(int *)param_2 < iVar1) && (*(int *)param_5 == 0)) {
      *(int *)param_2 = *(int *)param_2 + 1;
    }
    else {
      *(int *)param_1 = *(int *)param_1 + 1;
    }
  }
  while (10 < *(int *)param_3 + *(int *)param_2 + *(int *)param_1) {
    if ((*(int *)param_2 == 0) || (*(int *)param_5 != 0)) {
      if ((*(int *)param_3 == 0) || (*(int *)param_6 != 0)) {
        *(int *)param_1 = *(int *)param_1 - 1;
      }
      else {
        *(int *)param_3 = *(int *)param_3 - 1;
      }
    }
    else {
      *(int *)param_2 = *(int *)param_2 - 1;
    }
  }
  return;
}

/* 0040bed1 auto */
void __cdecl taxrate_dialog_redraw(void)

{
  taxrate_dialog_paint((C_004083b0_430 *)taxrate_dlg);
  return;
}

/* 0040beec auto */
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl taxrate_on_tax_scroll(int param_1)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (*(int *)(taxrate_dlg + 0x2dc) < param_1) {
    *(i32 *)(taxrate_dlg + 0x348) = 1;
  }
  local_8 = param_1;
  local_c = param_1;
  local_8 = int_clamp(param_1,0,*(i32 *)(taxrate_dlg + 0x2dc));
  local_10 = *(int *)(taxrate_dlg + 0x2e8);
  local_14 = *(int *)(taxrate_dlg + 0x2e4);
  taxrate_balance((iptr)&local_8,(iptr)&local_10,(iptr)&local_14,taxrate_dlg + 0x2f4,
                     taxrate_dlg + 0x350,taxrate_dlg + 0x354);
  *(int *)(taxrate_dlg + 0x2e0) = local_8;
  if (local_c != local_8) {
    scrollbar_set_pos((C_0040f380_40 *)(taxrate_dlg + 0x358),local_8);
    ctrl_show_and_redraw((Control *)(taxrate_dlg + 0x358));
  }
  if (*(int *)(taxrate_dlg + 0x2e8) != local_10) {
    *(int *)(taxrate_dlg + 0x2e8) = local_10;
    scrollbar_set_pos((C_0040f380_40 *)(taxrate_dlg + 0x3d8),local_10);
    ctrl_show_and_redraw((Control *)(taxrate_dlg + 0x3d8));
  }
  if (*(int *)(taxrate_dlg + 0x2e4) != local_14) {
    *(int *)(taxrate_dlg + 0x2e4) = local_14;
    scrollbar_set_pos((C_0040f380_40 *)(taxrate_dlg + 0x398),local_14);
    ctrl_show_and_redraw((Control *)(taxrate_dlg + 0x398));
  }
  taxrate_calc_totals((C_004083b0_430 *)taxrate_dlg);
  taxrate_dialog_redraw();
  return;
}
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 0040c07f auto */
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl taxrate_on_science_scroll(int param_1)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (*(int *)(taxrate_dlg + 0x2dc) < param_1) {
    *(i32 *)(taxrate_dlg + 0x348) = 1;
  }
  local_8 = param_1;
  local_c = param_1;
  local_8 = int_clamp(param_1,0,*(i32 *)(taxrate_dlg + 0x2dc));
  local_10 = *(int *)(taxrate_dlg + 0x2e4);
  local_14 = *(int *)(taxrate_dlg + 0x2e0);
  taxrate_balance((iptr)&local_8,(iptr)&local_10,(iptr)&local_14,taxrate_dlg + 0x2f0,
                     taxrate_dlg + 0x354,taxrate_dlg + 0x34c);
  *(int *)(taxrate_dlg + 0x2e8) = local_8;
  if (local_c != local_8) {
    scrollbar_set_pos((C_0040f380_40 *)(taxrate_dlg + 0x3d8),local_8);
    ctrl_show_and_redraw((Control *)(taxrate_dlg + 0x3d8));
  }
  if (*(int *)(taxrate_dlg + 0x2e4) != local_10) {
    *(int *)(taxrate_dlg + 0x2e4) = local_10;
    scrollbar_set_pos((C_0040f380_40 *)(taxrate_dlg + 0x398),local_10);
    ctrl_show_and_redraw((Control *)(taxrate_dlg + 0x398));
  }
  if (*(int *)(taxrate_dlg + 0x2e0) != local_14) {
    *(int *)(taxrate_dlg + 0x2e0) = local_14;
    scrollbar_set_pos((C_0040f380_40 *)(taxrate_dlg + 0x358),local_14);
    ctrl_show_and_redraw((Control *)(taxrate_dlg + 0x358));
  }
  taxrate_calc_totals((C_004083b0_430 *)taxrate_dlg);
  taxrate_dialog_redraw();
  return;
}
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 0040c212 auto */
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl taxrate_on_lux_scroll(int param_1)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (*(int *)(taxrate_dlg + 0x2dc) < param_1) {
    *(i32 *)(taxrate_dlg + 0x348) = 1;
  }
  local_8 = param_1;
  local_c = param_1;
  local_8 = int_clamp(param_1,0,*(i32 *)(taxrate_dlg + 0x2dc));
  local_10 = *(int *)(taxrate_dlg + 0x2e0);
  local_14 = *(int *)(taxrate_dlg + 0x2e8);
  taxrate_balance((iptr)&local_8,(iptr)&local_10,(iptr)&local_14,taxrate_dlg + 0x2ec,
                     taxrate_dlg + 0x34c,taxrate_dlg + 0x350);
  *(int *)(taxrate_dlg + 0x2e4) = local_8;
  if (local_8 != local_c) {
    scrollbar_set_pos((C_0040f380_40 *)(taxrate_dlg + 0x398),local_8);
    ctrl_show_and_redraw((Control *)(taxrate_dlg + 0x398));
  }
  if (*(int *)(taxrate_dlg + 0x2e0) != local_10) {
    *(int *)(taxrate_dlg + 0x2e0) = local_10;
    scrollbar_set_pos((C_0040f380_40 *)(taxrate_dlg + 0x358),local_10);
    ctrl_show_and_redraw((Control *)(taxrate_dlg + 0x358));
  }
  if (*(int *)(taxrate_dlg + 0x2e8) != local_14) {
    *(int *)(taxrate_dlg + 0x2e8) = local_14;
    scrollbar_set_pos((C_0040f380_40 *)(taxrate_dlg + 0x3d8),local_14);
    ctrl_show_and_redraw((Control *)(taxrate_dlg + 0x3d8));
  }
  taxrate_calc_totals((C_004083b0_430 *)taxrate_dlg);
  taxrate_dialog_redraw();
  return;
}
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 0040c3a5 auto */
#define taxrate_dialog_active (*(i32 *)((u8 *)&g.d_0063cbb0))
void __cdecl taxrate_on_ok_clicked(void)

{
  taxrate_dialog_active = 0;
  wnd_end_modal_loop((C_00408010_b8 *)(taxrate_dlg + 0x48));
  return;
}
#undef taxrate_dialog_active

/* 0040c3cd auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl taxrate_on_lock_toggled(int param_1,int param_2)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  *(int *)(taxrate_dlg + 0x34c + (param_1 - 300) * 4) = param_2;
  if (param_2 != 0) {
    for (local_8 = 0; local_8 < 3; local_8++) {
      if (param_1 - 300 != local_8) {
        *(i32 *)(taxrate_dlg + 0x34c + local_8 * 4) = 0;
        checkbox_set_checked
                  ((Control *)(local_8 * 0x3c + 0x418 + taxrate_dlg),0);
        ctrl_show_and_redraw((Control *)(local_8 * 0x3c + 0x418 + taxrate_dlg))
        ;
      }
    }
  }
  return;
}
#undef local_8

/* 0040c480 auto */
#define improvement (*(iptr *)(frame_ + FRAME_OFF(4)))
#define city (*(iptr *)(frame_ + FRAME_OFF(8)))
#define aiStack_a0 (*(int (*)[39])(frame_ + FRAME_OFF(24)))
void __thiscall taxrate_calc_totals(C_004083b0_430 *this)

{
  u8 uVar1;
  u8 uVar2;
  int iVar3;
  uptr civ;
  i8 frame_[FRAME_OFF(184)] __attribute__((aligned(8)));  /* original stack frame */
  
  this->total_tax = 0;
  this->field_310 = 0;
  this->total_science = 0;
  civ = this->field_2d8;
  for (improvement = 0; improvement < 0x27; improvement++) {
    aiStack_a0[improvement] = 0;
  }
  uVar1 = civs[civ].science_rate;
  uVar2 = civs[civ].tax_rate;
  civs[civ].tax_rate = (u8)this->field_2e0;
  civs[civ].science_rate = (u8)this->field_2e8;
  for (city = 0; city < game.num_cities; city++) {
    if ((cities[city].id != 0) && ((int)cities[city].owner == civ)) {
      city_split_trade(city,(int)cities[city].trade,1,0);
      for (improvement = 0; improvement < 0x27; improvement++) {
        iVar3 = city_has_improvement(city,improvement);
        if (iVar3 != 0) {
          aiStack_a0[improvement]++;
        }
      }
      if ((cities[city].flags & 1) == 0) {
        this->total_tax += (int)cities[city].tax;
        this->total_science += (int)cities[city].science;
      }
    }
  }
  for (improvement = 0; improvement < 0x27; improvement++) {
    if ((aiStack_a0[improvement] != 0) && (iVar3 = civ_improvement_upkeep(civ,improvement), iVar3 != 0)) {
      this->field_310 += aiStack_a0[improvement] * iVar3;
    }
  }
  civs[civ].tax_rate = uVar2;
  civs[civ].science_rate = uVar1;
  return;
}
#undef improvement
#undef city
#undef aiStack_a0

/* 0040c7d0 auto */
#define taxrate_bg_surface (*(int *)((u8 *)&g.d_00624f1c))
#define taxrate_dialog_active (*(int *)((u8 *)&g.d_0063cbb0))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
void __thiscall taxrate_dialog_paint(C_004083b0_430 *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  frame_wnd_draw_caption((FrameWindow *)this);
  if ((taxrate_bg_surface == 0) || (taxrate_dialog_active == 0)) {
    gfx_fill_rect((iptr)this,(iptr)&this->client_rect,0x1d);
  }
  else {
    gfx_copy_rect_xywh(taxrate_bg_surface,(iptr)this,0,0,this->client_x,this->client_y,this->field_2f8,
                       this->field_2fc);
  }
  text_set_surface((iptr)this);
  text_set_font(ADDR(0x6ab1a0, ((u8 *)&g.d_006ab1a0)));
  if (this->field_348 == 0) {
    text_set_colors(0x25,0x12,1,1);
  }
  else {
    text_set_colors(0x6a,10,1,1);
    this->field_348 = 0;
  }
  text_clear();
  text_append_label(0x98);
  text_append_colon();
  text_append_string_id(government_names[civs[this->field_2d8].government]);
  text_append_space();
  text_append_space();
  text_append_space();
  text_append_label(0x100);
  text_append_colon();
  text_append_int(this->field_2dc * 10);
  text_append_percent();
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),this->field_300,this->field_33c,this->field_31c);
  text_set_colors(0x25,0x12,1,1);
  text_clear();
  text_append_int(0);
  text_append_percent();
  text_draw_shadowed((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),this->field_300,this->field_330);
  text_draw_shadowed((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),this->field_300,this->field_338);
  text_draw_shadowed((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),this->field_300,this->field_334);
  text_clear();
  text_append_int(100);
  text_append_percent();
  text_draw_right_aligned((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),this->field_300,this->field_330,this->field_31c);
  text_draw_right_aligned((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),this->field_300,this->field_338,this->field_31c);
  text_draw_right_aligned((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),this->field_300,this->field_334,this->field_31c);
  text_clear();
  text_append_label(0x102);
  text_draw_shadowed((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),
                     this->field_31c + this->field_314 + this->field_314 + this->client_x,
                     this->field_330);
  text_clear();
  text_append_label(0x59);
  text_append_colon();
  text_append_int(this->field_2e0 * 10);
  text_append_percent();
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),this->field_300,this->field_330,this->field_31c);
  text_clear();
  text_append_label(0x5b);
  text_append_colon();
  text_append_int(this->field_2e8 * 10);
  text_append_percent();
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),this->field_300,this->field_338,this->field_31c);
  text_clear();
  text_append_label(0x5a);
  text_append_colon();
  text_append_int(this->field_2e4 * 10);
  text_append_percent();
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),this->field_300,this->field_334,this->field_31c);
  text_clear();
  text_append_label(0x88);
  text_append_colon();
  text_append_int(this->total_tax);
  text_append_space();
  text_append_space();
  text_append_space();
  text_append_label(0x87);
  text_append_colon();
  text_append_int(this->field_310);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),this->field_300,this->field_340,this->field_31c);
  text_clear();
  text_append_label(0x89);
  text_append_colon();
  local_c = civ_research_cost(this->field_2d8);
  if (local_c < 1) {
    local_c = 1;
  }
  if ((int)this->total_science < 1) {
    this->total_science = 1;
  }
  text_append_int((int)((this->total_science - 1) + local_c) / (int)this->total_science);
  text_append_space();
  text_append_label(0x2c);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),this->field_300,this->field_344,this->field_31c);
  wnd_blit_surface((DibSurface *)this);
  return;
}
#undef taxrate_bg_surface
#undef taxrate_dialog_active
#undef local_c

/* 0040cd64 auto */
#define SCHAR_00h_0064bc1a (*(i8 *)((u8 *)&g.d_0064bc1a))
#define SCHAR_00h_0064bc1c (*(i8 *)((u8 *)&g.d_0064bc1c))
#define taxrate_bg_surface (*(DibSurface * *)((u8 *)&g.d_00624f1c))
#define taxrate_dialog_active (*(int *)((u8 *)&g.d_0063cbb0))
#define ui_large_screen (*(int *)((u8 *)&g.d_00633584))
#define _SCHAR_00h_0064bc1a (*(i16 *)((u8 *)&g.d_0064bc1a))
#define _SCHAR_00h_0064bc1c (*(i16 *)((u8 *)&g.d_0064bc1c))
#define local_4a0 (*(u8 * *)(frame_ + FRAME_OFF(0)))
#define local_49c (*(u8 * *)(frame_ + FRAME_OFF(4)))
#define local_498 (*(u8 * *)(frame_ + FRAME_OFF(8)))
#define local_494 (*(u8 * *)(frame_ + FRAME_OFF(12)))
#define local_490 (*(u8 * *)(frame_ + FRAME_OFF(16)))
#define local_484 (*(DibSurface * *)(frame_ + FRAME_OFF(28)))
#define city (*(iptr *)(frame_ + FRAME_OFF(36)))
#define local_470 (*(iptr *)(frame_ + FRAME_OFF(48)))
#define local_468 (*(int *)(frame_ + FRAME_OFF(56)))
#define local_464 (*(int *)(frame_ + FRAME_OFF(60)))
#define local_460 (*(int *)(frame_ + FRAME_OFF(64)))
#define local_45c (*(int *)(frame_ + FRAME_OFF(68)))
#define local_458 (*(i8 (*)[16])(frame_ + FRAME_OFF(72)))
#define local_448 (*(int *)(frame_ + FRAME_OFF(88)))
#define local_444 (*(GamePalette *)(frame_ + FRAME_OFF(92)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1168)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1172)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(1176)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall taxrate_dialog_run(C_004083b0_430 *this,uptr civ)

{
  uptr uVar1;
  u32 uVar2;
  u32 uVar3;
  DibSurface *this_00;
  u32 uVar4;
  iptr iVar5;
  i32 uVar6;
  int iVar7;
  u32 uVar8;
  int iVar9;
  i32 uVar10;
  i32 uVar11;
  i32 uVar12;
  i32 uVar13;
  i32 uVar14;
  i32 uVar15;
  i8 frame_[FRAME_OFF(1184)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  local_464 = 0;
  palette_init(&local_444);
  local_8 = 0;
  taxrate_dlg = (iptr)this;
  this->field_2d8 = civ;
  taxrate_dialog_active = 1;
  this_00 = operator_new(0x48);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  if (this_00 == (DibSurface *)0x0) {
    local_484 = (DibSurface *)0x0;
  }
  else {
    local_484 = (DibSurface *)surface_ctor(this_00);
  }
  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
  taxrate_bg_surface = local_484;
  uVar4 = civ_max_tax_rate(civ);
  this->field_2dc = uVar4;
  this->field_348 = 0;
  while ((int)this->field_2dc < (int)(uint)civs[civ].tax_rate) {
    civs[civ].tax_rate += 0xff;
    if ((int)(uint)civs[civ].science_rate < (int)this->field_2dc) {
      civs[civ].science_rate++;
    }
    this->field_348 = 1;
  }
  while ((int)this->field_2dc < (int)(uint)civs[civ].science_rate) {
    civs[civ].science_rate += 0xff;
    if ((int)(uint)civs[civ].tax_rate < (int)this->field_2dc) {
      civs[civ].tax_rate++;
    }
    this->field_348 = 1;
  }
  while ((int)this->field_2dc <
         (int)(10 - ((uint)civs[civ].science_rate + (uint)civs[civ].tax_rate))) {
    if ((int)(uint)civs[civ].tax_rate < (int)this->field_2dc) {
      civs[civ].tax_rate++;
    }
    else {
      civs[civ].science_rate++;
    }
    this->field_348 = 1;
  }
  this->field_2ec = (uint)civs[civ].tax_rate;
  this->field_2f4 = (uint)civs[civ].science_rate;
  this->field_2f0 = 10 - ((uint)civs[civ].science_rate + (uint)civs[civ].tax_rate);
  taxrate_balance((iptr)&this->field_2ec,(iptr)&this->field_2f4,(iptr)&this->field_2f0,
                     (iptr)&this->field_2f4,(iptr)&local_464,(iptr)&local_464);
  this->field_2e0 = this->field_2ec;
  this->field_2e8 = this->field_2f4;
  this->field_2e4 = this->field_2f0;
  this->field_2f8 = 400;
  this->field_2fc = 0x100;
  this->field_314 = 10;
  this->field_318 = 6;
  uVar4 = GetSystemMetrics(3);
  this->field_320 = uVar4;
  local_470 = 0x41;
  if (0 < ui_large_screen) {
    this->field_2f8 = (int)(this->field_2f8 * 3) / 2;
    this->field_2fc = (int)(this->field_2fc * 3) / 2;
    this->field_320 = (int)(this->field_320 * 3) / 2;
    this->field_314 = (int)(this->field_314 * 3) / 2;
    this->field_318 = (int)(this->field_318 * 3) / 2;
    local_470 = 0x42;
  }
  surface_load_gif_resource(taxrate_bg_surface,local_470,10,0xc0,(iptr)&local_444);
  uVar4 = font_cached_height((GameFont *)&ui_text_font);
  this->field_32c = uVar4;
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x408));
  local_460 = font_text_width((GameFont *)&ui_text_font,iVar5);
  this->field_31c = (this->field_2f8 + this->field_314 * -2) - (this->field_314 + local_460);
  uVar15 = 0;
  uVar14 = 0;
  uVar13 = 0;
  uVar4 = this->field_2fc;
  uVar8 = this->field_2f8;
  uVar12 = 0;
  uVar11 = 0;
  uVar10 = 0xd;
  uVar6 = label_string(*(i32 *)(label_string_ids + 0x404));
  frame_wnd_create
            ((FrameWindow *)this,uVar6,uVar10,uVar11,uVar12,uVar8,uVar4,uVar13,uVar14,uVar15);
  local_448 = this->field_31c + this->field_314 + this->field_314 + this->client_x;
  iVar7 = (local_460 >> 1) + local_448;
  uVar8 = this->field_314 + this->client_x;
  this->field_300 = uVar8;
  uVar4 = this->field_318 + this->client_y;
  this->field_304 = uVar4;
  this->field_33c = uVar4;
  uVar1 = uVar4 + this->field_32c + this->field_32c;
  this->field_340 = uVar1;
  uVar1 += this->field_32c;
  this->field_344 = uVar1;
  uVar4 = uVar1 + this->field_32c + this->field_32c;
  this->field_330 = uVar4;
  iVar9 = uVar4 + this->field_32c;
  local_45c = ((int)this->field_320 >> 1) + iVar9 - 0x10;
  rect_set_xywh((iptr)local_458,uVar8,iVar9,this->field_31c,this->field_320);
  if (this == (C_004083b0_430 *)0x0) {
    local_490 = (u8 *)0x0;
  }
  else {
    local_490 = this->pad_48;
  }
  scrollbar_create
            ((Control *)&this->field_358,(iptr)local_490,0x65,(iptr)local_458,0);
  scrollbar_set_range((Control *)&this->field_358,0,10);
  scrollbar_set_pos((C_0040f380_40 *)&this->field_358,this->field_2e0);
  scrollbar_set_callback((Control *)&this->field_358,ADDR(0x40385f, taxrate_on_tax_scroll));
  uVar4 = iVar9 + this->field_318 + this->field_320;
  this->field_338 = uVar4;
  iVar9 = uVar4 + this->field_32c;
  rect_set_xywh((iptr)local_458,uVar8,iVar9,this->field_31c,this->field_320);
  if (this == (C_004083b0_430 *)0x0) {
    local_494 = (u8 *)0x0;
  }
  else {
    local_494 = this->pad_48;
  }
  scrollbar_create
            ((Control *)(this->pad_3c0 + 0x18),(iptr)local_494,0x66,(iptr)local_458,0);
  scrollbar_set_range((Control *)(this->pad_3c0 + 0x18),0,10);
  scrollbar_set_pos((C_0040f380_40 *)(this->pad_3c0 + 0x18),this->field_2e8);
  scrollbar_set_callback((Control *)(this->pad_3c0 + 0x18),ADDR(0x40289c, taxrate_on_science_scroll));
  uVar4 = iVar9 + this->field_318 + this->field_320;
  this->field_334 = uVar4;
  rect_set_xywh((iptr)local_458,uVar8,uVar4 + this->field_32c,this->field_31c,this->field_320);
  if (this == (C_004083b0_430 *)0x0) {
    local_498 = (u8 *)0x0;
  }
  else {
    local_498 = this->pad_48;
  }
  scrollbar_create
            ((Control *)(this->pad_364 + 0x34),(iptr)local_498,0x67,(iptr)local_458,0);
  scrollbar_set_range((Control *)(this->pad_364 + 0x34),0,10);
  scrollbar_set_pos((C_0040f380_40 *)(this->pad_364 + 0x34),this->field_2e4);
  scrollbar_set_callback((Control *)(this->pad_364 + 0x34),ADDR(0x4020f4, taxrate_on_lux_scroll));
  iVar9 = font_line_spacing((GameFont *)dialog_font_ptr);
  this->field_328 = iVar9 + 8;
  this->field_324 = this->client_width - 4;
  uVar4 = this->client_y;
  uVar8 = this->client_height;
  uVar2 = this->field_328;
  uVar3 = this->client_x;
  wnd_set_keyboard_nav((Wnd *)this->pad_48,0);
  rect_set_xywh((iptr)local_458,uVar3 + 2,(uVar4 + uVar8) - (uVar2 + 2),this->field_324,
                     this->field_328);
  if (this == (C_004083b0_430 *)0x0) {
    local_49c = (u8 *)0x0;
  }
  else {
    local_49c = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x3f8));
  button_create
            ((Control *)(this[1].pad_48 + 0x54),(iptr)local_49c,0xc9,(iptr)local_458,iVar5);
  button_set_callback((Control *)(this[1].pad_48 + 0x54),ADDR(0x402a18, taxrate_on_ok_clicked));
  ctrl_set_cancel_button((Control *)(this[1].pad_48 + 0x54));
  ctrl_set_default_button((Control *)(this[1].pad_48 + 0x54));
  if (ui_large_screen < 1) {
    local_45c += 6;
  }
  for (local_468 = 0; local_468 < 3; local_468++) {
    *(i32 *)(this->pad_364 + local_468 * 4 - 0x18) =
         *(i32 *)(&taxrate_lock_flags + local_468 * 4);
    if (this == (C_004083b0_430 *)0x0) {
      local_4a0 = (u8 *)0x0;
    }
    else {
      local_4a0 = this->pad_48;
    }
    checkbox_create
              ((Control *)(this->pad_3c0 + local_468 * 0x3c + 0x58),(iptr)local_4a0,
               local_468 + 300,iVar7 - 0x10,local_45c,ADDR(0x624f20, ((u8 *)&g.d_00624f20)));
    checkbox_set_checked
              ((Control *)(this->pad_3c0 + local_468 * 0x3c + 0x58),
               *(i32 *)(this->pad_364 + local_468 * 4 - 0x18));
    checkbox_set_callback((CheckboxCallbackSetView *)(this->pad_3c0 + local_468 * 0x3c + 0x58),ADDR(0x40375b, taxrate_on_lock_toggled))
    ;
    local_45c = local_45c + this->field_318 + this->field_320 + this->field_32c;
  }
  taxrate_calc_totals(this);
  wnd_set_redraw_callback((SurfaceWindow *)this,ADDR(0x402cf7, taxrate_dialog_redraw));
  wnd_repaint((SurfaceWindow *)this);
  window_show((C_004083b0_4 *)this);
  if (2 < game.multiplayer) {
    wnd_set_modal_idle_callback((C_00408010_b8 *)this->pad_48,ADDR(0x403585, net_modal_idle_poll));
  }
  wnd_run_modal_loop((C_00408010_b8 *)this->pad_48);
  wnd_set_modal_idle_callback((C_00408010_b8 *)this->pad_48,0);
  while (taxrate_dialog_active != 0) {
    win_pump_one_message();
  }
  if (taxrate_bg_surface != (DibSurface *)0x0) {
    surface_delete(taxrate_bg_surface,1);
  }
  taxrate_bg_surface = (DibSurface *)0x0;
  for (local_468 = 0; local_468 < 3; local_468++) {
    *(i32 *)(&taxrate_lock_flags + local_468 * 4) =
         *(i32 *)(this->pad_364 + local_468 * 4 - 0x18);
  }
  if (((uint)civs[civ].tax_rate != this->field_2e0) ||
     ((uint)civs[civ].science_rate != this->field_2e8)) {
    local_464 = 1;
  }
  civs[civ].tax_rate = (u8)this->field_2e0;
  civs[civ].science_rate = (u8)this->field_2e8;
  if ((game.turn < 0xb) && (civs[civ].government < 2)) {
    _SCHAR_00h_0064bc1a = (ushort)civs[civ].science_rate;
    _SCHAR_00h_0064bc1c = (ushort)civs[civ].tax_rate;
    prefs_save_civ2dat();
  }
  if (local_464 != 0) {
    game.field_06 = game.field_06 & 0xfffb;
    for (city = 0; city < game.num_cities; city++) {
      if ((cities[city].id != 0) && ((int)cities[city].owner == civ)) {
        city_recalc(city,1);
      }
    }
  }
  city_window_recalc_redraw((C_004083b0_4 *)&city_window,0);
  status_redraw(1);
  advisor_refresh_if_open(4);
  advisor_refresh_if_open(5);
  advisor_refresh_if_open(6);
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_0040dda0 */ { palette_destroy((GamePalette *)((iptr)&local_444)); }
  return;
}
#undef SCHAR_00h_0064bc1a
#undef SCHAR_00h_0064bc1c
#undef taxrate_bg_surface
#undef taxrate_dialog_active
#undef ui_large_screen
#undef _SCHAR_00h_0064bc1a
#undef _SCHAR_00h_0064bc1c
#undef local_4a0
#undef local_49c
#undef local_498
#undef local_494
#undef local_490
#undef local_484
#undef city
#undef local_470
#undef local_468
#undef local_464
#undef local_460
#undef local_45c
#undef local_458
#undef local_448
#undef local_444
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0040ddc6 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define local_518 (*(C_004083b0_430 *)(frame_ + FRAME_OFF(0)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1288)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1292)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1296)))
void __cdecl taxrate_dialog_show(iptr civ)

{
  i8 frame_[FRAME_OFF(1304)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  taxrate_dialog_ctor(&local_518);
  local_8 = 0;
  if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_0040dea8 */ { taxrate_dialog_dtor((TaxRateDialog *)((iptr)&local_518)); }
  }
  else {
    if ((game.multiplayer < 3) || (human_civ == civ)) {
      taxrate_dialog_run(&local_518,civ);
      city_window_refresh((FrameWindow *)&city_window);
    }
    else {
      net_send_message(0x9d,*(i32 *)
                               (&net_player_slots + *(int *)(&net_civ_slots + civ * 4) * 0x54),0,0,0,
                         0,0,0,0,0);
    }
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_0040dea8 */ { taxrate_dialog_dtor((TaxRateDialog *)((iptr)&local_518)); }
  }
  return;
}
#undef human_civ
#undef local_518
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0040decc auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
void __cdecl taxrate_enforce_max_rate(iptr civ)

{
  int iVar1;
  
  if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) {
    if ((game.multiplayer < 3) || (human_civ == civ)) {
      iVar1 = civ_max_tax_rate(civ);
      if (iVar1 < (int)(uint)civs[civ].tax_rate) {
        taxrate_dialog_show(civ);
      }
      if (iVar1 < (int)(10 - ((uint)civs[civ].science_rate + (uint)civs[civ].tax_rate))) {
        taxrate_dialog_show(civ);
      }
      if (iVar1 < (int)(uint)civs[civ].science_rate) {
        taxrate_dialog_show(civ);
      }
    }
    else {
      net_send_message(0x9e,*(i32 *)
                               (&net_player_slots + *(int *)(&net_civ_slots + civ * 4) * 0x54),0,0,0,
                         0,0,0,0,0);
    }
  }
  return;
}
#undef human_civ

/* 0040f060 auto */
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
C_004083b0_430 * __thiscall taxrate_dialog_ctor(C_004083b0_430 *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  frame_wnd_ctor((SurfaceWindow *)this);
  local_8 = 0;
  scrollbar_ctor((Control *)&this->field_358);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  scrollbar_ctor((Control *)(this->pad_364 + 0x34));
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  scrollbar_ctor((Control *)(this->pad_3c0 + 0x18));
  (*(i8 *)((char *)&local_8 + 0)) = 3;
  FUN_005f2620(this->pad_3c0 + 0x58,0x3c,3,checkbox_elem_ctor,
               checkbox_dtor);
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),4);
  button_ctor((Control *)(this[1].pad_48 + 0x54));
  this->vtable = (u32)&PTR_FUN_0061c054;
  return this;
}
#undef local_10
#undef puStack_c
#undef local_8

/* 0040f1e0 auto */
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __thiscall taxrate_dialog_dtor(void *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  (*(i32 *)((char *)&local_8 + 1)) = 0;
  (*(i8 *)((char *)&local_8 + 0)) = 4;
  /* inlined unwind funclet FUN_0040f25f */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x4cc)); }
  (*(i8 *)((char *)&local_8 + 0)) = 3;
  /* inlined unwind funclet FUN_0040f26e */ { FUN_005f2490(*(int *)((iptr)&this) + 0x418,0x3c,3,checkbox_dtor); }
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  /* inlined unwind funclet FUN_0040f286 */ { scrollbar_dtor((Control *)(*(int *)((iptr)&this) + 0x3d8)); }
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  /* inlined unwind funclet FUN_0040f295 */ { scrollbar_dtor((Control *)(*(int *)((iptr)&this) + 0x398)); }
  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
  /* inlined unwind funclet FUN_0040f2a4 */ { scrollbar_dtor((Control *)(*(int *)((iptr)&this) + 0x358)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_0040f2b3 */ { frame_wnd_dtor(*(DibSurface **)((iptr)&this)); }
  return;
}
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004100cf auto */
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
#define local_350 (*(uptr *)(frame_ + FRAME_OFF(0)))
#define local_34c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_344 (*(Dialog *)(frame_ + FRAME_OFF(12)))
#define local_50 (*(Sprite *)(frame_ + FRAME_OFF(768)))
#define local_14 (*(uptr *)(frame_ + FRAME_OFF(828)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(832)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(836)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(840)))
void __cdecl city_info_popup(iptr city)

{
  iptr iVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(848)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  sprite_init(&local_50);
  local_8 = 0;
  dialog_ctor(&local_344,0x4000);
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),1);
  sprite_create_solid(&local_50,0x40,0x30,0);
  text_set_string_arg(0,(iptr)&cities[city].name);
  text_clear();
  iVar1 = civ_get_adjective((int)cities[city].owner);
  text_append(iVar1);
  if (((game.game_flags & 0x80) != 0) && ((scenario_flags & 2) != 0)) {
    iVar2 = city_objective_value(city);
    if (iVar2 != 0) {
      text_append_space();
      text_append_label(0x1b0);
      if (1 < iVar2) {
        text_append(ADDR(0x624f68, ((u8 *)&g.d_00624f68)));
        text_append_int(iVar2);
      }
    }
  }
  text_set_string_arg(1,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  for (local_34c = 0; local_34c < 3; local_34c++) {
    local_14 = (uptr)*(char *)&cities[city].demands[local_34c];
    text_clear();
    if ((int)local_14 < 0) {
      text_append_lparen();
    }
    if ((int)local_14 < 1) {
      local_350 = ~local_14 + 1;
    }
    else {
      local_350 = local_14;
    }
    text_append_string_id(commodity_names[local_350]);
    if ((int)local_14 < 0) {
      text_append_rparen();
    }
    text_set_string_arg(local_34c + 2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  }
  popup_game_with_city(ADDR(0x624f6c, ((u8 *)&g.d_00624f6c)),city);
  local_8 = local_8 & 0xffffff00;
  /* inlined unwind funclet FUN_004102d5 */ { dialog_dtor((Dialog *)((iptr)&local_344)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_004102e1 */ { sprite_destroy((Sprite *)((iptr)&local_50)); }
  return;
}
#undef scenario_flags
#undef local_350
#undef local_34c
#undef local_344
#undef local_50
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00414e00 auto */
/* Library Function - Single Match
    public: int __thiscall CSplitterWnd::IsTracking(void)
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall city_window_is_closed(C_004083b0_4 *this)

{
  return this[0x569].field_0;
}

/* 00428d00 auto */
void __cdecl city_editor_request_redraw(void)

{
  city_editor_draw((C_004083b0_430 *)active_editor_wnd);
  return;
}

/* 00428d1b auto */
#define editor_running (*(i32 *)((u8 *)&g.d_006a1d7c))
void __cdecl city_editor_on_ok(void)

{
  editor_running = 0;
  wnd_end_modal_loop((C_00408010_b8 *)(active_editor_wnd + 0x48));
  menu_update_states();
  return;
}
#undef editor_running

/* 00428d48 auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
void __cdecl city_editor_on_help(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (active_editor_wnd == 0) {
    local_8 = 0;
  }
  else {
    local_8 = active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(local_8);
  popup_text(ADDR(0x625e90, ((u8 *)&g.d_00625e90)),ADDR(0x625e88, ((u8 *)&g.d_00625e88)));
  dlg_set_parent_window(0);
  return;
}
#undef local_8

/* 00428da7 auto */
#define editor_running (*(i32 *)((u8 *)&g.d_006a1d7c))
void __cdecl city_editor_on_cancel(void)

{
  editor_running = 0;
  wnd_end_modal_loop((C_00408010_b8 *)(active_editor_wnd + 0x48));
  return;
}
#undef editor_running

/* 00428dcf auto */
void __cdecl city_editor_on_edit_icon(void)

{
  i32 uVar1;
  i32 uVar2;
  i8 *puVar3;
  
  puVar3 = ((void *)ADDR(0x0040123a, sprite_sheet_save_cities));
  uVar2 = 1;
  uVar1 = label_string(*(i32 *)(label_string_ids + 0x7d8));
  sprite_editor_run((iptr)(&city_sprites +
                           *(int *)(active_editor_wnd + 0x2f4) * 0x3c +
                           *(int *)(active_editor_wnd + 0x2ec) * 0x1e0 +
                           *(int *)(active_editor_wnd + 0x2f0) * 0x78),uVar1,uVar2,(iptr)puVar3);
  city_editor_request_redraw();
  return;
}

/* 00428e50 auto */
#define local_14 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(i8 * *)(frame_ + FRAME_OFF(8)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(16)))
void __cdecl city_editor_on_edit_misc(void)

{
  int iVar1;
  i32 uVar2;
  i8 *puVar3;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 2;
  if (active_editor_wnd == 0) {
    local_14 = 0;
  }
  else {
    local_14 = active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(local_14);
  iVar1 = popup_text_flags(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x625e98, ((u8 *)&g.d_00625e98)),1);
  if (iVar1 != -1) {
    switch(iVar1) {
    case 0:
      local_10 = &fortify_overlay_sprites;
      break;
    case 1:
      local_10 = &airbase_sprites;
      break;
    default:
      if (iVar1 < 10) {
        local_10 = &civ_flag_sprites + (iVar1 * 8 - 0x10) * 0xf;
      }
      else {
        local_10 = &civ_flag_dark_sprites + (iVar1 * 8 - 0x60) * 0xf;
      }
      local_8 = 3;
      break;
    case 10:
      local_10 = &fortress_sprite;
      break;
    case 0xb:
      local_10 = &airbase_occupied_sprite;
    }
    if (local_10 != (i8 *)0x0) {
      puVar3 = ((void *)ADDR(0x0040123a, sprite_sheet_save_cities));
      uVar2 = label_string(*(i32 *)(label_string_ids + 0x7d8));
      sprite_editor_run((iptr)local_10,uVar2,local_8,(iptr)puVar3);
    }
  }
  dlg_set_parent_window(0);
  return;
}
#undef local_14
#undef local_10
#undef local_8

/* 00428fd2 auto */
void __cdecl city_editor_on_combo_change(i32 param_1)

{
  i32 uVar1;
  
  uVar1 = combo_get_cur_sel((ComboBoxGetSelView *)(active_editor_wnd + 0x2fc));
  *(i32 *)(active_editor_wnd + 0x2ec) = uVar1;
  uVar1 = combo_get_cur_sel((ComboBoxGetSelView *)(active_editor_wnd + 0x334));
  *(i32 *)(active_editor_wnd + 0x2f0) = uVar1;
  uVar1 = combo_get_cur_sel((ComboBoxGetSelView *)(active_editor_wnd + 0x36c));
  *(i32 *)(active_editor_wnd + 0x2f4) = uVar1;
  city_editor_request_redraw();
  return;
}

/* 0042903e auto */
#define city_editor_combo_x_table (*(i32 *)((u8 *)&g.d_00625e70))
#define city_editor_combo_y_table (*(i32 *)((u8 *)&g.d_00625e74))
#define editor_next_ctrl_id (*(int *)((u8 *)&g.d_006a1d80))
#define local_24 (*(u8 * *)(frame_ + FRAME_OFF(4)))
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
void __thiscall city_editor_create_combo(C_004083b0_430 *this,int param_1)

{
  int iVar1;
  iptr iVar2;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  rect_set_xywh((iptr)local_14,(&city_editor_combo_x_table)[param_1 * 2] + this->client_x - 0x1e,
                     (&city_editor_combo_y_table)[param_1 * 2] + this->client_y,0xa0,this->field_2e8 << 3);
  iVar1 = editor_next_ctrl_id;
  editor_next_ctrl_id++;
  if (this == (C_004083b0_430 *)0x0) {
    local_24 = (u8 *)0x0;
  }
  else {
    local_24 = this->pad_48;
  }
  combo_create
            ((Control *)(this->pad_2d4 + param_1 * 0x38 + 0x28),(iptr)local_24,iVar1,
             (iptr)local_14);
  combo_set_font((ComboBoxFontView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),ADDR(0x6a4f90, ((u8 *)&g.d_006a4f90)));
  combo_set_callback((ComboBoxCallbackSetView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),ADDR(0x4036f7, city_editor_on_combo_change));
  if (param_1 == 0) {
    iVar2 = label_string(*(i32 *)(label_string_ids + 0x834));
    combo_add_string((ComboBoxAddView *)&this->field_2fc,iVar2);
    iVar2 = label_string(*(i32 *)(label_string_ids + 0x838));
    combo_add_string((ComboBoxAddView *)&this->field_2fc,iVar2);
    iVar2 = label_string(*(i32 *)(label_string_ids + 0x83c));
    combo_add_string((ComboBoxAddView *)&this->field_2fc,iVar2);
    iVar2 = label_string(*(i32 *)(label_string_ids + 0x840));
    combo_add_string((ComboBoxAddView *)&this->field_2fc,iVar2);
    iVar2 = label_string(*(i32 *)(label_string_ids + 0x844));
    combo_add_string((ComboBoxAddView *)&this->field_2fc,iVar2);
    iVar2 = label_string(*(i32 *)(label_string_ids + 0x848));
    combo_add_string((ComboBoxAddView *)&this->field_2fc,iVar2);
  }
  else if (param_1 == 1) {
    iVar2 = label_string(*(i32 *)(label_string_ids + 0x84c));
    combo_add_string((ComboBoxAddView *)&this->field_334,iVar2);
    iVar2 = label_string(*(i32 *)(label_string_ids + 0x850));
    combo_add_string((ComboBoxAddView *)&this->field_334,iVar2);
    iVar2 = label_string(*(i32 *)(label_string_ids + 0x854));
    combo_add_string((ComboBoxAddView *)&this->field_334,iVar2);
    iVar2 = label_string(*(i32 *)(label_string_ids + 0x858));
    combo_add_string((ComboBoxAddView *)&this->field_334,iVar2);
  }
  else if (param_1 == 2) {
    iVar2 = label_string(*(i32 *)(label_string_ids + 0x85c));
    combo_add_string((ComboBoxAddView *)(this->pad_364 + 8),iVar2);
    iVar2 = label_string(*(i32 *)(label_string_ids + 0x860));
    combo_add_string((ComboBoxAddView *)(this->pad_364 + 8),iVar2);
  }
  return;
}
#undef city_editor_combo_x_table
#undef city_editor_combo_y_table
#undef editor_next_ctrl_id
#undef local_24
#undef local_14

/* 004293a8 auto */
#define city_editor_combo_x_table (*(int *)((u8 *)&g.d_00625e70))
#define city_editor_combo_y_table (*(int *)((u8 *)&g.d_00625e74))
#define editor_bg_surface (*(int *)((u8 *)&g.d_0062e018))
#define editor_running (*(int *)((u8 *)&g.d_006a1d7c))
#define local_28 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_18 (*(Sprite * *)(frame_ + FRAME_OFF(16)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(20)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_c (*(int *)(frame_ + FRAME_OFF(28)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(32)))
void __thiscall city_editor_draw(C_004083b0_430 *this)

{
  byte bVar1;
  iptr iVar2;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  frame_wnd_draw_caption((FrameWindow *)this);
  if ((editor_bg_surface == 0) || (editor_running == 0)) {
    gfx_fill_rect((iptr)this,(iptr)&this->client_rect,0x1d);
  }
  else {
    gfx_copy_rect_xywh(editor_bg_surface,(iptr)this,0,0,this->client_x,this->client_y,this->field_2d8,
                       this->field_2dc);
  }
  local_8 = this->client_x + 0x20;
  local_c = this->client_y + 0x20;
  local_18 = (Sprite *)
             (&city_sprites +
             this->field_2f4 * 0x3c + this->field_2ec * 0x1e0 + this->field_2f0 * 0x78);
  bVar1 = sprite_get_key_color(local_18);
  gfx_fill_rect_xywh((iptr)this,local_8,local_c,0x40,0x40,(uint)bVar1);
  sprite_draw_keyed(local_18,(iptr)local_28,(iptr)this,0,local_8,local_c + 8);
  gfx_draw_tiled_frame((iptr)this,local_8,local_c,0x40,0x40,6);
  text_set_surface((iptr)this);
  text_set_font(ADDR(0x6a4f90, ((u8 *)&g.d_006a4f90)));
  text_set_colors(0x29,0x12,1,1);
  local_10 = city_editor_combo_x_table + this->client_x + 0x32;
  local_14 = ((city_editor_combo_y_table + this->client_y) - this->field_2e8) - 2;
  text_clear();
  iVar2 = label_string(*(i32 *)(label_string_ids + 0x864));
  text_append_str(iVar2);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = city_editor_combo2_x + this->client_x + 0x32;
  local_14 = ((city_editor_combo2_y + this->client_y) - this->field_2e8) - 2;
  text_clear();
  iVar2 = label_string(*(i32 *)(label_string_ids + 0x868));
  text_append_str(iVar2);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = city_editor_combo3_x + this->client_x + 0x32;
  local_14 = ((city_editor_combo3_y + this->client_y) - this->field_2e8) - 2;
  text_clear();
  iVar2 = label_string(*(i32 *)(label_string_ids + 0x86c));
  text_append_str(iVar2);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  wnd_blit_surface((DibSurface *)this);
  return;
}
#undef city_editor_combo_x_table
#undef city_editor_combo_y_table
#undef editor_bg_surface
#undef editor_running
#undef local_28
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 00429671 auto */
#define editor_bg_surface (*(DibSurface * *)((u8 *)&g.d_0062e018))
#define editor_next_ctrl_id (*(i32 *)((u8 *)&g.d_006a1d80))
#define editor_running (*(int *)((u8 *)&g.d_006a1d7c))
#define local_484 (*(u8 * *)(frame_ + FRAME_OFF(4)))
#define local_480 (*(u8 * *)(frame_ + FRAME_OFF(8)))
#define local_47c (*(u8 * *)(frame_ + FRAME_OFF(12)))
#define local_478 (*(u8 * *)(frame_ + FRAME_OFF(16)))
#define local_474 (*(u8 * *)(frame_ + FRAME_OFF(20)))
#define local_468 (*(DibSurface * *)(frame_ + FRAME_OFF(32)))
#define local_460 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_454 (*(i8 (*)[16])(frame_ + FRAME_OFF(52)))
#define local_444 (*(GamePalette *)(frame_ + FRAME_OFF(68)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1144)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1148)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(1152)))
void __thiscall city_editor_open_window(C_004083b0_430 *this)

{
  DibSurface *this_00;
  uptr uVar1;
  i32 uVar2;
  int iVar3;
  int iVar4;
  iptr iVar5;
  i32 uVar6;
  i32 uVar7;
  i32 uVar8;
  u32 uVar9;
  u32 uVar10;
  i32 uVar11;
  i32 uVar12;
  i32 uVar13;
  i8 frame_[FRAME_OFF(1160)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  palette_init(&local_444);
  local_8 = 0;
  editor_running = 1;
  active_editor_wnd = (iptr)this;
  this_00 = operator_new(0x48);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  if (this_00 == (DibSurface *)0x0) {
    local_468 = (DibSurface *)0x0;
  }
  else {
    local_468 = (DibSurface *)surface_ctor(this_00);
  }
  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
  editor_bg_surface = local_468;
  font_set((GameFont *)&editor_font,0,editor_font_size);
  ui_set_default_font(ADDR(0x6a4f90, ((u8 *)&g.d_006a4f90)));
  ui_set_ctrl_font(ADDR(0x6a4f90, ((u8 *)&g.d_006a4f90)));
  ui_set_ctrl_text_color(0x29);
  ui_set_ctrl_text_shadow(0x12,1,1);
  ui_set_ctrl_disabled_color(0x25);
  this->field_2d8 = 0x230;
  this->field_2dc = 0x17c;
  this->field_2ec = 0;
  editor_next_ctrl_id = 0xc9;
  surface_load_gif_file(editor_bg_surface,ADDR(0x625ea4, ((u8 *)&g.d_00625ea4)),10,0xc0,(iptr)&local_444);
  uVar1 = font_cached_height((GameFont *)&editor_font);
  this->field_2e8 = uVar1;
  uVar13 = 0;
  uVar12 = 0;
  uVar11 = 0;
  uVar10 = this->field_2dc;
  uVar9 = this->field_2d8;
  uVar8 = 0;
  uVar7 = 0;
  uVar6 = 0xd;
  uVar2 = label_string(*(i32 *)(label_string_ids + 0x738));
  frame_wnd_create
            ((FrameWindow *)this,uVar2,uVar6,uVar7,uVar8,uVar9,uVar10,uVar11,uVar12,uVar13);
  for (local_460 = 0; local_460 < 3; local_460++) {
    city_editor_create_combo(this,local_460);
  }
  iVar3 = font_line_spacing((GameFont *)dialog_font_ptr);
  this->field_2e4 = iVar3 + 8;
  this->field_2e0 = (int)(this->client_width - 8) / 3;
  iVar4 = (this->client_y + this->client_height) - (this->field_2e4 + 2);
  iVar3 = this->client_x + 2;
  rect_set_xywh((iptr)local_454,iVar3,iVar4,this->field_2e0,this->field_2e4);
  if (this == (C_004083b0_430 *)0x0) {
    local_474 = (u8 *)0x0;
  }
  else {
    local_474 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x3f8));
  button_create
            ((Control *)&this[1].field_2a4,(iptr)local_474,0x65,(iptr)local_454,iVar5);
  button_set_callback((Control *)&this[1].field_2a4,ADDR(0x40317f, city_editor_on_ok));
  iVar3 = iVar3 + this->field_2e0 + 2;
  rect_set_xywh((iptr)local_454,iVar3,iVar4,this->field_2e0,this->field_2e4);
  if (this == (C_004083b0_430 *)0x0) {
    local_478 = (u8 *)0x0;
  }
  else {
    local_478 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x8ec));
  button_create
            ((Control *)&this[1].field_2e0,(iptr)local_478,0x66,(iptr)local_454,iVar5);
  button_set_callback((Control *)&this[1].field_2e0,ADDR(0x402888, city_editor_on_help));
  rect_set_xywh((iptr)local_454,iVar3 + this->field_2e0 + 2,iVar4,this->field_2e0,
                     this->field_2e4);
  if (this == (C_004083b0_430 *)0x0) {
    local_47c = (u8 *)0x0;
  }
  else {
    local_47c = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x3fc));
  button_create
            ((Control *)&this[1].field_31c,(iptr)local_47c,0x66,(iptr)local_454,iVar5);
  button_set_callback((Control *)&this[1].field_31c,ADDR(0x403706, city_editor_on_cancel));
  ctrl_set_cancel_button((Control *)&this[1].field_31c);
  this->field_2e0 = 0x4d;
  iVar3 = font_line_spacing((GameFont *)dialog_font_ptr);
  this->field_2e4 = iVar3 + 8;
  iVar3 = this->client_x + 0x19;
  iVar4 = this->client_y + 0x68;
  rect_set_xywh((iptr)local_454,iVar3,iVar4,this->field_2e0,this->field_2e4);
  if (this == (C_004083b0_430 *)0x0) {
    local_480 = (u8 *)0x0;
  }
  else {
    local_480 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x7cc));
  button_create
            ((Control *)(this[1].pad_364 + 0x30),(iptr)local_480,0x65,(iptr)local_454,iVar5);
  button_set_callback((Control *)(this[1].pad_364 + 0x30),ADDR(0x401c21, city_editor_on_edit_icon));
  rect_set_xywh((iptr)local_454,iVar3,iVar4 + this->field_2e4 + 2,this->field_2e0,
                     this->field_2e4);
  if (this == (C_004083b0_430 *)0x0) {
    local_484 = (u8 *)0x0;
  }
  else {
    local_484 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x8f0));
  button_create
            ((Control *)(this[1].pad_3c0 + 0x10),(iptr)local_484,0x65,(iptr)local_454,iVar5);
  button_set_callback((Control *)(this[1].pad_3c0 + 0x10),ADDR(0x40120d, city_editor_on_edit_misc));
  wnd_set_keyboard_nav((Wnd *)this->pad_48,0);
  this->field_2f4 = 0;
  this->field_2f0 = this->field_2f4;
  combo_set_cur_sel((ComboBoxSetSelView *)&this->field_2fc,this->field_2ec);
  combo_set_cur_sel((ComboBoxSetSelView *)&this->field_334,this->field_2f0);
  combo_set_cur_sel((ComboBoxSetSelView *)(this->pad_364 + 8),this->field_2f4);
  this->field_2f8 = 3;
  wnd_set_move_handler((C_00408130 *)(this->pad_48 + 0x10),ADDR(0x4019d8, editor_wnd_on_move_close_dropdowns));
  wnd_set_redraw_callback((SurfaceWindow *)this,ADDR(0x403ae9, city_editor_request_redraw));
  city_editor_on_combo_change(0xc9);
  wnd_repaint((SurfaceWindow *)this);
  window_show((C_004083b0_4 *)this);
  wnd_run_modal_loop((C_00408010_b8 *)this->pad_48);
  while (editor_running != 0) {
    win_pump_one_message();
  }
  if (editor_bg_surface != (DibSurface *)0x0) {
    surface_delete(editor_bg_surface,1);
  }
  editor_bg_surface = (DibSurface *)0x0;
  this->field_2f8 = 0;
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_00429e53 */ { palette_destroy((GamePalette *)((iptr)&local_444)); }
  return;
}
#undef editor_bg_surface
#undef editor_next_ctrl_id
#undef editor_running
#undef local_484
#undef local_480
#undef local_47c
#undef local_478
#undef local_474
#undef local_468
#undef local_460
#undef local_454
#undef local_444
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00429e77 auto */
#define local_b58 (*(C_004083b0_a28 *)(frame_ + FRAME_OFF(0)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(2888)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(2892)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(2896)))
void __cdecl city_editor_run(void)

{
  i8 frame_[FRAME_OFF(2904)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  editor_wnd_ctor(&local_b58);
  local_8 = 0;
  city_editor_open_window((C_004083b0_430 *)&local_b58);
  wnd_repaint((SurfaceWindow *)&map_views);
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_00429ed0 */ { editor_wnd_dtor((EditorWindow *)((iptr)&local_b58)); }
  return;
}
#undef local_b58
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0042b824 auto */
#define local_320 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define city (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_318 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_314 (*(int *)(frame_ + FRAME_OFF(12)))
#define local_30c (*(Dialog *)(frame_ + FRAME_OFF(20)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(776)))
#define local_14 (*(iptr *)(frame_ + FRAME_OFF(780)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(784)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(788)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(792)))
i32 __cdecl trade_commodity_cities_dialog(iptr civ,iptr param_2)

{
  bool bVar1;
  int iVar2;
  iptr iVar3;
  i8 frame_[FRAME_OFF(800)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_30c,0x4000);
  local_8 = 0;
  text_set_label_arg(0,commodity_names[param_2]);
  dlg_load_game_section(&local_30c,ADDR(0x625ef0, ((u8 *)&g.d_00625ef0)),0x40001);
  local_314 = 0;
  for (local_18 = 0; local_18 < 2; local_18++) {
    local_318 = 0;
    for (city = 0; city < game.num_cities; city++) {
      if ((cities[city].id != 0) &&
         ((cities[city].owner == civ ||
          (((local_18 == 0 &&
            ((*(char *)&cities[city].revealed_size[civ] != '\0' ||
             (iVar2 = city_has_improvement(city,1), iVar2 != 0)))) || (game.reveal_map != '\0')))
          ))) {
        bVar1 = false;
        for (local_14 = 0; local_14 < 3; local_14++) {
          if (local_18 == 0) {
            if (*(char *)&cities[city].demands[local_14] == param_2) {
              bVar1 = true;
            }
          }
          else if (*(char *)&cities[city].supplies[local_14] == param_2) {
            bVar1 = true;
          }
        }
        if (bVar1) {
          text_clear();
          text_append(city * 0x58 + ADDR(0x64f360, ((u8 *)&cities + 32)));
          text_append_lparen();
          if (cities[city].owner == civ) {
            text_append_int((int)cities[city].size);
          }
          else {
            iVar3 = civ_get_adjective((int)cities[city].owner);
            text_append(iVar3);
            text_append_comma();
            if (((game.reveal_map == '\0') && (iVar2 = city_has_improvement(city,1), iVar2 == 0))
               && (*(char *)&cities[city].revealed_size[civ] != '\0')) {
              text_append_int((int)*(char *)&cities[city].revealed_size[civ]);
            }
            else {
              text_append_int((int)cities[city].size);
            }
          }
          text_append_rparen();
          text_append_space();
          text_append_label((local_18 == 0) + 0x56);
          text_append_space();
          text_append_string_id(commodity_names[param_2]);
          dialog_add_option((DialogOptionList *)&local_30c,ADDR(0x679640, ((u8 *)&g.d_00679640)),city,0);
          local_314++;
          local_318++;
        }
      }
    }
    if (local_318 != 0) {
      dialog_add_option((DialogOptionList *)&local_30c,ADDR(0x625efc, ((u8 *)&g.d_00625efc)),-1,0);
    }
  }
  if (local_314 == 0) {
    local_320 = popup_game_flags(ADDR(0x625f00, ((u8 *)&g.d_00625f00)),1);
  }
  else {
    local_320 = dlg_show_modal(&local_30c,0);
  }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_0042bc22 */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
  return local_320;
}
#undef local_320
#undef city
#undef local_318
#undef local_314
#undef local_30c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0042bc47 auto */
#define local_308 (*(Dialog *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(iptr *)(frame_ + FRAME_OFF(756)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(760)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(764)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(768)))
void __cdecl trade_supply_search_dialog(iptr civ)

{
  int iVar1;
  iptr iVar2;
  i32 uVar3;
  iptr iVar3;
  i8 frame_[FRAME_OFF(776)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_308,0x4000);
  local_8 = 0;
  iVar1 = civ_has_advance(civ,0x54);
  if (iVar1 == 0) {
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_0042bd6b */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
  }
  else {
    do {
      dlg_load_game_section(&local_308,ADDR(0x625f0c, ((u8 *)&g.d_00625f0c)),0x40001);
      for (local_14 = 0; local_14 < 0x10; local_14++) {
        uVar3 = 0;
        iVar3 = local_14;
        iVar2 = label_string(commodity_names[local_14]);
        dialog_add_option((DialogOptionList *)&local_308,iVar2,iVar3,uVar3);
      }
      iVar1 = dlg_show_modal(&local_308,0);
      if (iVar1 < 0) {
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0042bd6b */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
        goto LAB_0042bd81;
      }
      iVar1 = trade_commodity_cities_dialog(civ,iVar1);
    } while (-1 < iVar1);
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_0042bd6b */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
  }
LAB_0042bd81:
  return;
}
#undef local_308
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0042bd8f auto */
#define advisor_client_width (*(i32 *)((u8 *)&g.d_0063ec3c))
#define advisor_client_x (*(int *)((u8 *)&g.d_0063ec34))
#define advisor_first_row (*(uint *)((u8 *)&g.d_0063ef70))
#define advisor_row_height (*(i32 *)((u8 *)&g.d_0063ef80))
#define _DAT_0063ef68 (*(i32 *)((u8 *)&g.d_0063ef68))
#define _DAT_0063ef78 (*(i32 *)((u8 *)&g.d_0063ef78))
#define _DAT_0063ef7c (*(i32 *)((u8 *)&g.d_0063ef7c))
#define local_18c (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_17c (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
#define local_16c (*(i8 (*)[16])(frame_ + FRAME_OFF(36)))
#define local_15c (*(i8 (*)[16])(frame_ + FRAME_OFF(52)))
#define local_14c (*(i8 (*)[16])(frame_ + FRAME_OFF(68)))
#define local_13c (*(i8 (*)[16])(frame_ + FRAME_OFF(84)))
#define local_12c (*(i8 (*)[16])(frame_ + FRAME_OFF(100)))
#define civ (*(iptr *)(frame_ + FRAME_OFF(116)))
#define local_118 (*(int *)(frame_ + FRAME_OFF(120)))
#define local_114 (*(int *)(frame_ + FRAME_OFF(124)))
#define city2 (*(iptr *)(frame_ + FRAME_OFF(128)))
#define local_10c (*(int *)(frame_ + FRAME_OFF(132)))
#define local_108 (*(int *)(frame_ + FRAME_OFF(136)))
#define local_104 (*(uint *)(frame_ + FRAME_OFF(140)))
#define local_100 (*(int *)(frame_ + FRAME_OFF(144)))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(148)))
#define local_f8 (*(int *)(frame_ + FRAME_OFF(152)))
#define local_f4 (*(int *)(frame_ + FRAME_OFF(156)))
#define local_f0 (*(uint *)(frame_ + FRAME_OFF(160)))
#define city (*(iptr *)(frame_ + FRAME_OFF(164)))
#define local_e8 (*(int *)(frame_ + FRAME_OFF(168)))
#define local_e4 (*(int *)(frame_ + FRAME_OFF(172)))
#define local_e0 (*(int *)(frame_ + FRAME_OFF(176)))
#define local_dc (*(int *)(frame_ + FRAME_OFF(180)))
#define local_d8 (*(int *)(frame_ + FRAME_OFF(184)))
#define local_d4 (*(int *)(frame_ + FRAME_OFF(188)))
#define local_d0 (*(int *)(frame_ + FRAME_OFF(192)))
#define local_cc (*(int *)(frame_ + FRAME_OFF(196)))
#define aiStack_c8 (*(int (*)[39])(frame_ + FRAME_OFF(200)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(356)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(360)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(364)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(368)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(372)))
#define local_18 (*(i8 (*)[16])(frame_ + FRAME_OFF(376)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(392)))
/* WARNING: Removing unreachable block (ram,0x0042cc50) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl trade_advisor_draw(void)

{
  iptr iVar1;
  int iVar2;
  i32 uVar3;
  i8 frame_[FRAME_OFF(400)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ = advisor_report_civ;
  frame_wnd_layout((FrameWindow *)&advisor_window);
  frame_wnd_draw_caption((FrameWindow *)&advisor_window);
  picwnd_blit((C_004083b0_4c4 *)&advisor_window);
  local_f4 = advisor_client_y + 2;
  local_10c = advisor_client_y + 0x174;
  local_20 = font_line_spacing((GameFont *)&advisor_font);
  text_set_surface(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)));
  text_set_font(ADDR(0x63eac0, ((u8 *)&g.d_0063eac0)));
  text_set_colors(0x25,0x12,2,1);
  text_clear();
  iVar1 = label_string(*(i32 *)(label_string_ids + 0x548));
  text_append(iVar1);
  gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,local_f4,advisor_client_width);
  local_f4 += local_20;
  text_clear();
  local_108 = int_clamp(civs[civ].government - 1,0,4);
  text_append_label(local_108 + 0x148);
  text_append_space();
  text_append_label(0x8c);
  text_append_space();
  iVar1 = civ_name_plural(civ);
  text_append(iVar1);
  gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,local_f4,advisor_client_width);
  local_f4 += local_20;
  text_clear();
  iVar1 = civ_leader_title(civ);
  text_append(iVar1);
  text_append_space();
  iVar1 = civ_leader_name(civ);
  text_append(iVar1);
  text_append_colon();
  text_append_year((int)game.year);
  gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,local_f4,advisor_client_width);
  _DAT_0063ef78 = local_f4 + local_20;
  local_f4 = _DAT_0063ef78 + 4;
  local_20 = 0x18;
  advisor_row_height = 0x18;
  _DAT_0063ef78 += 0xc;
  _DAT_0063ef7c = local_10c - local_f4;
  advisor_rows_per_page = int_clamp((local_10c - local_f4) / 0x18,1,99);
  local_8 = advisor_rows_per_page;
  for (improvement = 0; improvement < 0x27; improvement++) {
    aiStack_c8[improvement] = 0;
  }
  local_d8 = 0;
  local_1c = 0;
  local_114 = 0;
  local_cc = 0;
  local_e0 = 0;
  for (city = 0; city < game.num_cities; city++) {
    if ((cities[city].id != 0) && (cities[city].owner == civ)) {
      local_e0++;
      for (improvement = 0; improvement < 0x27; improvement++) {
        local_e8 = civ_improvement_upkeep(civ,improvement);
        if ((local_e8 != 0) && (iVar2 = city_has_improvement(city,improvement), iVar2 != 0)) {
          aiStack_c8[improvement]++;
        }
      }
      if ((cities[city].flags & 1) == 0) {
        local_cc += cities[city].tax;
        local_114 += cities[city].science;
      }
    }
  }
  for (improvement = 0; improvement < 0x27; improvement++) {
    if (aiStack_c8[improvement] != 0) {
      iVar2 = civ_improvement_upkeep(civ,improvement);
      local_1c += iVar2 * aiStack_c8[improvement];
      local_d8++;
    }
  }
  local_28 = local_e0 + 6;
  local_f8 = local_d8 + 3;
  local_24 = local_f8;
  if (local_f8 <= local_28) {
    local_24 = local_28;
  }
  _DAT_0063ef68 = int_clamp((local_8 - 1 + local_24) / local_8,1,99);
  uVar3 = int_clamp(local_24 - 1,0,999);
  advisor_first_row = int_clamp(advisor_first_row,0,uVar3);
  local_118 = local_f4;
  local_104 = advisor_first_row;
  local_f0 = advisor_first_row;
  do {
    if ((int)(local_104 + local_8) <= (int)local_f0) {
      if (advisor_controls_created == 0) {
        rect_set((iptr)local_18,(advisor_client_right - advisor_vscroll_width) - 2,local_f4,
                           advisor_client_right - 2,local_10c);
        scrollbar_create
                  ((Control *)&advisor_scrollbar,ADDR(0x63eb58, ((u8 *)&g.d_0063eb58)),200,(iptr)local_18,1);
        uVar3 = int_clamp(local_24 - 1,0,999);
        scrollbar_set_range((Control *)&advisor_scrollbar,0,uVar3);
        scrollbar_set_pos((C_0040f380_40 *)&advisor_scrollbar,advisor_first_row);
        scrollbar_set_page_size((Control *)&advisor_scrollbar,advisor_rows_per_page);
        scrollbar_set_callback((Control *)&advisor_scrollbar,ADDR(0x40268f, trade_advisor_on_scroll));
        ctrl_show_and_redraw((Control *)&advisor_scrollbar);
        advisor_controls_created = 1;
      }
      wnd_blit_surface((DibSurface *)&advisor_window);
      return;
    }
    if ((int)local_f0 < local_24) {
      local_100 = advisor_client_x + 2;
      local_d0 = advisor_client_x + 0x14f;
      if (local_f0 == 0) {
        local_e4 = local_118 + 10;
        text_clear();
        iVar1 = label_string(*(i32 *)(label_string_ids + 0x5b0));
        text_append(iVar1);
        text_set_font(ADDR(0x63eac0, ((u8 *)&g.d_0063eac0)));
        text_set_colors(0x29,10,1,1);
        gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_100 + 0x8a,local_e4);
        text_clear();
        iVar1 = label_string(*(i32 *)(label_string_ids + 0x5b4));
        text_append(iVar1);
        gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_d0,local_e4);
        local_118 += local_20;
      }
      else {
        local_e4 = local_118 + 9;
        local_d4 = local_f0 - 1;
        if (local_d4 < local_e0) {
          local_2c = 0;
          city2 = -1;
          for (city = 0; city < game.num_cities; city++) {
            if ((cities[city].id != 0) && (cities[city].owner == civ)) {
              if (local_d4 == local_2c) {
                city2 = city;
                break;
              }
              local_2c++;
            }
          }
          if (-1 < city2) {
            city = city2;
            local_dc = (local_f0 & 1) * 0x40 + local_100;
            gfx_draw_city(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),city2,0,local_dc,local_118,0);
            text_set_font(ADDR(0x63eab8, ((u8 *)&g.d_0063eab8)));
            text_set_colors(0x25,0x12,1,1);
            local_100 += 0x8a;
            gfx_draw_text((iptr)&cities[city].name,local_100,local_e4);
            local_100 += 0x69;
            local_dc = local_100;
            if ((cities[city].flags & 1) == 0) {
              text_clear();
              text_append_int((int)cities[city].tax);
              local_dc = gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_dc,local_e4);
              local_dc += 2;
              sprite_draw
                        ((Sprite *)&gold_coin_icon_sprite,(iptr)local_12c,ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),local_dc,
                         local_e4 + 2);
              local_dc += 0x12;
              text_clear();
              text_append_int((int)cities[city].science);
              local_dc = gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_dc,local_e4);
              local_dc += 2;
              sprite_draw
                        ((Sprite *)&science_icon_sprite,(iptr)local_13c,ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),local_dc,
                         local_e4 + 2);
              local_dc += 0x12;
            }
            else {
              text_clear();
              text_append_label(0x86);
              text_set_colors(0x6a,0x12,1,1);
              gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_dc,local_e4);
            }
          }
        }
        else if (local_e0 + 1 == local_d4) {
          text_set_font(ADDR(0x63eab8, ((u8 *)&g.d_0063eab8)));
          text_set_colors(0x29,10,1,1);
          text_clear();
          text_append_label(0x87);
          text_append_colon();
          text_append_int(local_1c);
          local_dc = gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_100 + 0x8a,local_e4);
          sprite_draw
                    ((Sprite *)&gold_coin_icon_sprite,(iptr)local_14c,ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),local_dc,local_e4 + 2);
        }
        else if (local_e0 + 2 == local_d4) {
          text_clear();
          text_append_label(0x88);
          text_append_colon();
          text_append_long(local_cc);
          text_set_font(ADDR(0x63eab8, ((u8 *)&g.d_0063eab8)));
          text_set_colors(0x29,10,1,1);
          local_dc = gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_100 + 0x8a,local_e4);
          sprite_draw
                    ((Sprite *)&gold_coin_icon_sprite,(iptr)local_15c,ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),local_dc,local_e4 + 2);
        }
        else if (local_e0 + 3 == local_d4) {
          text_clear();
          text_append_label(0x16e);
          text_append_colon();
          text_append_int(local_114);
          text_set_font(ADDR(0x63eab8, ((u8 *)&g.d_0063eab8)));
          text_set_colors(0x29,10,1,1);
          local_dc = gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_100 + 0x8a,local_e4);
          sprite_draw
                    ((Sprite *)&science_icon_sprite,(iptr)local_16c,ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),local_dc,local_e4 + 2);
        }
        else if (local_e0 + 4 == local_d4) {
          text_clear();
          text_append_label(0x89);
          text_append_colon();
          local_e8 = civ_research_cost(civ);
          if (local_e8 < 2) {
            local_e8 = 1;
          }
          if (local_114 < 2) {
            local_114 = 1;
          }
          text_append_int((local_114 - 1 + local_e8) / local_114);
          text_append_space();
          text_append_label(0x2c);
          text_set_font(ADDR(0x63eab8, ((u8 *)&g.d_0063eab8)));
          text_set_colors(0x29,10,1,1);
          gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_100 + 0x8a,local_e4);
        }
        if (local_d4 < local_d8) {
          city2 = -1;
          local_2c = 0;
          for (improvement = 0; improvement < 0x27; improvement++) {
            if (aiStack_c8[improvement] != 0) {
              if (local_d4 == local_2c) {
                city2 = improvement;
                break;
              }
              local_2c++;
            }
          }
          if (-1 < city2) {
            text_set_font(ADDR(0x63eab8, ((u8 *)&g.d_0063eab8)));
            improvement = city2;
            text_clear();
            text_append_int(aiStack_c8[improvement]);
            text_append_space();
            text_append_string_id(improvements[improvement].name);
            text_append_space();
            text_append_lparen();
            text_append_label(0x84);
            text_append_colon();
            iVar2 = civ_improvement_upkeep(civ,improvement);
            text_append_int(iVar2 * aiStack_c8[improvement]);
            text_set_colors(0x7a,10,1,1);
            local_dc = gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_d0,local_e4);
            sprite_draw
                      ((Sprite *)&gold_coin_icon_sprite,(iptr)local_17c,ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),local_dc,local_e4 + 2
                      );
            local_dc += 0xe;
            text_clear();
            text_append_rparen();
            local_dc = gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_dc,local_e4);
          }
        }
        else if (local_d8 + 1 == local_d4) {
          text_set_font(ADDR(0x63eab8, ((u8 *)&g.d_0063eab8)));
          text_set_colors(0x7a,10,1,1);
          text_clear();
          text_append_label(0x87);
          text_append_colon();
          text_append_int(local_1c);
          local_dc = gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_d0,local_e4);
          sprite_draw
                    ((Sprite *)&gold_coin_icon_sprite,(iptr)local_18c,ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),local_dc,local_e4 + 2);
        }
        local_118 += local_20;
      }
    }
    local_f0++;
  } while( true );
}
#undef advisor_client_width
#undef advisor_client_x
#undef advisor_first_row
#undef advisor_row_height
#undef _DAT_0063ef68
#undef _DAT_0063ef78
#undef _DAT_0063ef7c
#undef local_18c
#undef local_17c
#undef local_16c
#undef local_15c
#undef local_14c
#undef local_13c
#undef local_12c
#undef civ
#undef local_118
#undef local_114
#undef city2
#undef local_10c
#undef local_108
#undef local_104
#undef local_100
#undef improvement
#undef local_f8
#undef local_f4
#undef local_f0
#undef city
#undef local_e8
#undef local_e4
#undef local_e0
#undef local_dc
#undef local_d8
#undef local_d4
#undef local_d0
#undef local_cc
#undef aiStack_c8
#undef local_2c
#undef local_28
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_8

/* 0042ccf4 auto */
#define advisor_first_row (*(i32 *)((u8 *)&g.d_0063ef70))
void __cdecl trade_advisor_on_scroll(i32 param_1)

{
  advisor_first_row = param_1;
  trade_advisor_draw();
  return;
}
#undef advisor_first_row

/* 0042cd11 auto */
void __cdecl trade_advisor_on_supply_clicked(void)

{
  trade_supply_search_dialog(advisor_report_civ);
  return;
}

/* 0042cd2f auto */
#define advisor_client_x (*(i32 *)((u8 *)&g.d_0063ec34))
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
/* WARNING: Removing unreachable block (ram,0x0042cddd) */
/* WARNING: Removing unreachable block (ram,0x0042ce68) */

void __cdecl trade_advisor_show(iptr param_1)

{
  int iVar1;
  int iVar2;
  iptr iVar3;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  picwnd_open((C_004083b0_4c4 *)&advisor_window,5,5,0,600,400,0,0);
  advisor_report_civ = param_1;
  rect_set_xywh((iptr)local_14,2,0,0x129,0x18);
  iVar1 = advisor_client_y;
  iVar2 = rect_height((iptr)local_14);
  rect_offset((iptr)local_14,advisor_client_x,(iVar1 - iVar2) + 0x18e);
  rect_offset((iptr)local_14,299,0);
  iVar3 = label_string(*(i32 *)(label_string_ids + 0x51c));
  button_create
            ((Control *)&advisor_close_button,ADDR(0x63eb58, ((u8 *)&g.d_0063eb58)),100,(iptr)local_14,iVar3);
  button_set_callback((Control *)&advisor_close_button,ADDR(0x401235, advisor_on_close_clicked));
  ctrl_set_default_button((Control *)&advisor_close_button);
  ctrl_set_cancel_button((Control *)&advisor_close_button);
  rect_offset((iptr)local_14,0xfffffed5,0);
  iVar3 = label_string(*(i32 *)(label_string_ids + 0x5bc));
  button_create
            ((Control *)&advisor_toggle_button,ADDR(0x63eb58, ((u8 *)&g.d_0063eb58)),0x65,(iptr)local_14,iVar3);
  button_set_callback((Control *)&advisor_toggle_button,ADDR(0x402ca2, trade_advisor_on_supply_clicked));
  wnd_set_redraw_callback((SurfaceWindow *)&advisor_window,ADDR(0x401857, trade_advisor_draw));
  wnd_repaint((SurfaceWindow *)&advisor_window);
  window_show((C_004083b0_4 *)&advisor_window);
  return;
}
#undef advisor_client_x
#undef local_14

/* 0042ced6 auto */
#define advisor_client_width (*(i32 *)((u8 *)&g.d_0063ec3c))
#define advisor_client_x (*(int *)((u8 *)&g.d_0063ec34))
#define advisor_first_row (*(iptr *)((u8 *)&g.d_0063ef70))
#define advisor_row_height (*(i32 *)((u8 *)&g.d_0063ef80))
#define _DAT_0063ef68 (*(i32 *)((u8 *)&g.d_0063ef68))
#define _DAT_0063ef78 (*(i32 *)((u8 *)&g.d_0063ef78))
#define _DAT_0063ef7c (*(i32 *)((u8 *)&g.d_0063ef7c))
#define local_6c (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define civ (*(iptr *)(frame_ + FRAME_OFF(20)))
#define local_58 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_54 (*(int *)(frame_ + FRAME_OFF(28)))
#define local_50 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_4c (*(int *)(frame_ + FRAME_OFF(36)))
#define local_48 (*(int *)(frame_ + FRAME_OFF(40)))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(44)))
#define local_40 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_3c (*(uint *)(frame_ + FRAME_OFF(52)))
#define city (*(iptr *)(frame_ + FRAME_OFF(56)))
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(60)))
#define local_30 (*(uint *)(frame_ + FRAME_OFF(64)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(68)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(72)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(76)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(80)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(84)))
#define local_18 (*(i8 (*)[16])(frame_ + FRAME_OFF(88)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(104)))
/* WARNING: Removing unreachable block (ram,0x0042d56a) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl city_status_draw(void)

{
  uint uVar1;
  iptr iVar2;
  i32 uVar3;
  i8 frame_[FRAME_OFF(112)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ = advisor_report_civ;
  frame_wnd_layout((FrameWindow *)&advisor_window);
  frame_wnd_draw_caption((FrameWindow *)&advisor_window);
  picwnd_blit((C_004083b0_4c4 *)&advisor_window);
  local_40 = advisor_client_y + 2;
  local_54 = advisor_client_y + 0x174;
  local_1c = font_line_spacing((GameFont *)&advisor_font);
  text_set_surface(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)));
  text_set_font(ADDR(0x63eac0, ((u8 *)&g.d_0063eac0)));
  text_set_colors(0x25,0x12,2,1);
  text_clear();
  iVar2 = label_string(*(i32 *)(label_string_ids + 0x538));
  text_append(iVar2);
  gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,local_40,advisor_client_width);
  local_40 += local_1c;
  text_clear();
  local_50 = int_clamp(civs[civ].government - 1,0,4);
  text_append_label(local_50 + 0x148);
  text_append_space();
  text_append_label(0x8c);
  text_append_space();
  iVar2 = civ_name_plural(civ);
  text_append(iVar2);
  gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,local_40,advisor_client_width);
  local_40 += local_1c;
  text_clear();
  iVar2 = civ_leader_title(civ);
  text_append(iVar2);
  text_append_space();
  iVar2 = civ_leader_name(civ);
  text_append(iVar2);
  text_append_colon();
  text_append_year((int)game.year);
  gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,local_40,advisor_client_width);
  _DAT_0063ef78 = local_40 + local_1c;
  local_40 = _DAT_0063ef78 + 2;
  local_1c = 0x18;
  advisor_row_height = 0x18;
  _DAT_0063ef78 += 10;
  _DAT_0063ef7c = local_54 - local_40;
  advisor_rows_per_page = int_clamp((local_54 - local_40) / 0x18,1,99);
  local_28 = 0;
  for (city = 0; city < game.num_cities; city++) {
    if ((cities[city].id != 0) && (cities[city].owner == civ)) {
      local_28++;
    }
  }
  local_8 = advisor_rows_per_page;
  _DAT_0063ef68 = int_clamp((advisor_rows_per_page - 1 + local_28) / advisor_rows_per_page,1,99);
  uVar3 = int_clamp(local_28 - 1,0,999);
  advisor_first_row = int_clamp(advisor_first_row,0,uVar3);
  local_3c = 0;
  local_58 = local_40;
  local_4c = advisor_first_row;
  for (city = 0; city < game.num_cities; city++) {
    uVar1 = local_3c;
    if ((((cities[city].id != 0) && (cities[city].owner == civ)) &&
        (uVar1 = local_3c + 1, local_4c <= (int)local_3c)) && ((int)local_3c < local_4c + local_8))
    {
      local_48 = (uVar1 & 1) * 0x40 + advisor_client_x + 2;
      local_3c = uVar1;
      gfx_draw_city(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),city,0,local_48,local_58,0);
      text_set_font(ADDR(0x63eab8, ((u8 *)&g.d_0063eab8)));
      text_set_colors(0x25,0x12,1,1);
      local_2c = local_58 + 9;
      local_48 = advisor_client_x + 0x8c;
      gfx_draw_text((iptr)&cities[city].name,local_48,local_2c);
      local_48 += 0x69;
      local_24 = local_48;
      for (local_20 = 0; local_20 < 3; local_20++) {
        text_clear();
        if (local_20 == 0) {
          text_append_int((uint)cities[city].total_food);
        }
        else if (local_20 == 1) {
          text_append_int((uint)cities[city].total_shields);
        }
        else {
          text_append_int((int)cities[city].trade);
        }
        local_24 = gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_24,local_2c);
        local_24 += 2;
        sprite_draw
                  ((Sprite *)(&resource_icon_sprites + local_20 * 0x78),(iptr)local_6c,ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),
                   local_24,local_2c);
        local_24 += 0x12;
      }
      local_48 += 0x78;
      local_24 = local_48;
      text_clear();
      if (cities[city].building < '\0') {
        improvement = -(int)cities[city].building;
        text_append_string_id(improvements[-(int)cities[city].building].name);
        text_append_space();
        if (0x26 < improvement) {
          text_set_colors(0x5e,10,0xffffffff,0xffffffff);
        }
        local_30 = (uint)improvements[improvement].cost;
      }
      else {
        text_set_colors(0x7a,10,0xffffffff,0xffffffff);
        unit_type = (iptr)cities[city].building;
        text_append_string_id(unit_types[unit_type].name);
        text_append_space();
        local_30 = (uint)(char)unit_types[unit_type].cost;
      }
      local_24 = gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_24,local_2c);
      local_24 += 4;
      text_clear();
      text_append_lparen();
      text_append_int((int)cities[city].shield_box);
      text_append(ADDR(0x625f1c, ((u8 *)&g.d_00625f1c)));
      text_append_int(cosmic.shield_box_rows * local_30);
      text_append_rparen();
      text_set_colors(0x21,0x12,0xffffffff,0xffffffff);
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_24,local_2c);
      local_58 += local_1c;
      uVar1 = local_3c;
    }
    local_3c = uVar1;
  }
  if (advisor_controls_created == 0) {
    rect_set((iptr)local_18,(advisor_client_right - advisor_vscroll_width) - 2,local_40,advisor_client_right - 2,
                       local_54);
    scrollbar_create((Control *)&advisor_scrollbar,ADDR(0x63eb58, ((u8 *)&g.d_0063eb58)),200,(iptr)local_18,1);
    uVar3 = int_clamp(local_28 - 1,0,999);
    scrollbar_set_range((Control *)&advisor_scrollbar,0,uVar3);
    scrollbar_set_pos((C_0040f380_40 *)&advisor_scrollbar,advisor_first_row);
    scrollbar_set_page_size((Control *)&advisor_scrollbar,advisor_rows_per_page);
    scrollbar_set_callback((Control *)&advisor_scrollbar,ADDR(0x403314, city_status_on_scroll));
    ctrl_show_and_redraw((Control *)&advisor_scrollbar);
    wnd_set_lbuttonup_handler((C_00408130 *)&advisor_wnd_events,ADDR(0x402437, city_status_on_click));
    advisor_controls_created = 1;
  }
  wnd_blit_surface((DibSurface *)&advisor_window);
  return;
}
#undef advisor_client_width
#undef advisor_client_x
#undef advisor_first_row
#undef advisor_row_height
#undef _DAT_0063ef68
#undef _DAT_0063ef78
#undef _DAT_0063ef7c
#undef local_6c
#undef civ
#undef local_58
#undef local_54
#undef local_50
#undef local_4c
#undef local_48
#undef improvement
#undef local_40
#undef local_3c
#undef city
#undef unit_type
#undef local_30
#undef local_2c
#undef local_28
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_8

/* 0042d618 auto */
#define advisor_first_row (*(i32 *)((u8 *)&g.d_0063ef70))
void __cdecl city_status_on_scroll(i32 param_1)

{
  advisor_first_row = param_1;
  city_status_draw();
  return;
}
#undef advisor_first_row

/* 0042d635 auto */
#define advisor_first_row (*(int *)((u8 *)&g.d_0063ef70))
#define advisor_row_height (*(int *)((u8 *)&g.d_0063ef80))
#define _DAT_0063ef78 (*(i32 *)((u8 *)&g.d_0063ef78))
#define city (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl city_status_on_click(i32 param_1,int param_2)

{
  int iVar1;
  bool bVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((-1 < param_2 - _DAT_0063ef78) &&
     (iVar1 = (param_2 - _DAT_0063ef78) / advisor_row_height, iVar1 < advisor_rows_per_page)) {
    local_8 = 0;
    for (city = 0; city < game.num_cities; city++) {
      if (((cities[city].id != 0) && (cities[city].owner == advisor_report_civ)) &&
         (bVar2 = local_8 == iVar1 + advisor_first_row, local_8 = local_8 + 1, bVar2)) {
        city_window_open((C_004083b0_12c *)&city_window,city);
        return;
      }
    }
  }
  return;
}
#undef advisor_first_row
#undef advisor_row_height
#undef _DAT_0063ef78
#undef city
#undef local_8

/* 0042d71e auto */
void __cdecl city_status_show(iptr param_1)

{
  picwnd_open((C_004083b0_4c4 *)&advisor_window,1,1,0,600,400,0,0);
  advisor_report_civ = param_1;
  advisor_add_close_button((C_004083b0_430 *)&advisor_window);
  wnd_set_redraw_callback((SurfaceWindow *)&advisor_window,ADDR(0x4029f5, city_status_draw));
  wnd_repaint((SurfaceWindow *)&advisor_window);
  window_show((C_004083b0_4 *)&advisor_window);
  return;
}

/* 00431573 auto */
#define advisor_client_width (*(int *)((u8 *)&g.d_0063ec3c))
#define advisor_client_x (*(int *)((u8 *)&g.d_0063ec34))
#define advisor_first_row (*(iptr *)((u8 *)&g.d_0063ef70))
#define advisor_row_height (*(i32 *)((u8 *)&g.d_0063ef80))
#define text_draw_font (*(GameFont * *)((u8 *)&g.d_006366ac))
#define _DAT_0063ef68 (*(i32 *)((u8 *)&g.d_0063ef68))
#define _DAT_0063ef78 (*(i32 *)((u8 *)&g.d_0063ef78))
#define _DAT_0063ef7c (*(i32 *)((u8 *)&g.d_0063ef7c))
#define local_88 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define local_84 (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_74 (*(iptr *)(frame_ + FRAME_OFF(20)))
#define local_70 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_6c (*(int *)(frame_ + FRAME_OFF(28)))
#define local_68 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_64 (*(int *)(frame_ + FRAME_OFF(36)))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(40)))
#define local_5c (*(int *)(frame_ + FRAME_OFF(44)))
#define local_58 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_54 (*(int *)(frame_ + FRAME_OFF(52)))
#define city (*(iptr *)(frame_ + FRAME_OFF(56)))
#define local_4c (*(int *)(frame_ + FRAME_OFF(60)))
#define local_48 (*(int *)(frame_ + FRAME_OFF(64)))
#define local_44 (*(int *)(frame_ + FRAME_OFF(68)))
#define local_40 (*(int *)(frame_ + FRAME_OFF(72)))
#define local_3c (*(iptr *)(frame_ + FRAME_OFF(76)))
#define civ (*(int *)(frame_ + FRAME_OFF(80)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(84)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(88)))
#define local_2c (*(iptr *)(frame_ + FRAME_OFF(92)))
#define local_28 (*(i8 (*)[16])(frame_ + FRAME_OFF(96)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(112)))
#define aiStack_14 (*(int (*)[4])(frame_ + FRAME_OFF(116)))
/* WARNING: Removing unreachable block (ram,0x00431bb2) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl wonders_report_draw(void)

{
  iptr iVar1;
  i32 uVar2;
  int iVar3;
  i32 uVar4;
  i32 uVar5;
  i32 uVar6;
  i8 frame_[FRAME_OFF(136)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_74 = advisor_report_civ;
  frame_wnd_layout((FrameWindow *)&advisor_window);
  frame_wnd_draw_caption((FrameWindow *)&advisor_window);
  picwnd_blit((C_004083b0_4c4 *)&advisor_window);
  local_58 = advisor_client_y + 2;
  local_6c = advisor_client_y + 0x174;
  local_30 = font_line_spacing((GameFont *)&advisor_font);
  text_set_surface(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)));
  text_set_font(ADDR(0x63eac0, ((u8 *)&g.d_0063eac0)));
  text_set_colors(0x29,0x12,2,1);
  for (local_2c = 0; local_2c < 4; local_2c++) {
    aiStack_14[local_2c] = 0;
  }
  local_34 = 0;
  for (local_3c = 0; local_3c < 0x1c; local_3c++) {
    if (game.wonder_city[local_3c] != -1) {
      local_2c = local_3c / 7;
      iVar3 = local_34 + 1;
      if (aiStack_14[local_2c] == 0) {
        iVar3 = local_34 + 2;
      }
      local_34 = iVar3;
      aiStack_14[local_2c]++;
    }
  }
  if (local_34 == 0) {
    text_clear();
    iVar1 = label_string(*(i32 *)(label_string_ids + 0x550));
    text_append(iVar1);
    gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,local_58,advisor_client_width);
    local_58 = local_58 + local_30 + 4;
    text_clear();
    text_append(ADDR(0x626000, ((u8 *)&g.d_00626000)));
    text_append_label(0x125);
    text_append(ADDR(0x626004, ((u8 *)&g.d_00626004)));
    gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,local_58,advisor_client_width);
    local_58 += local_30;
  }
  local_30 = 0x28;
  advisor_row_height = 0x28;
  _DAT_0063ef78 = local_58;
  _DAT_0063ef7c = local_6c - local_58;
  advisor_rows_per_page = int_clamp((local_6c - local_58) / 0x28,1,99);
  local_18 = advisor_rows_per_page;
  _DAT_0063ef68 = int_clamp((advisor_rows_per_page - 1 + local_34) / advisor_rows_per_page,1,99);
  uVar2 = int_clamp(local_34 - 1,0,999);
  advisor_first_row = int_clamp(advisor_first_row,0,uVar2);
  local_70 = local_58;
  local_54 = 0;
  for (local_2c = 0; local_2c < 4; local_2c++) {
    aiStack_14[local_2c] = 0;
  }
  local_68 = advisor_first_row;
  for (local_3c = 0; local_3c < 0x1c; local_3c++) {
    if (game.wonder_city[local_3c] != -1) {
      improvement = local_3c + 0x27;
      local_2c = local_3c / 7;
      if (aiStack_14[local_2c] == 0) {
        aiStack_14[local_2c]++;
        if ((local_68 <= local_54) && (local_54 < local_68 + local_18)) {
          iVar3 = text_read_section_line(ADDR(0x6558e8, ((u8 *)&g.d_006558e8)),ADDR(0x626008, ((u8 *)&g.d_00626008)),local_2c);
          if (iVar3 == 0) {
            local_40 = local_70 + 0xf;
            text_set_colors(0x29,0x12,1,1);
            gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,local_40,advisor_client_width - (advisor_vscroll_width + 2));
          }
          local_70 += local_30;
        }
        local_54++;
      }
      if ((local_68 <= local_54) && (local_54 < local_68 + local_18)) {
        local_4c = local_70 + 2;
        text_clear();
        if (((local_2c == 0) || ((local_3c == 0x13 || (local_3c == 0x14)))) && (game_language == 0))
        {
          text_append_label(0xd7);
          text_append_space();
        }
        text_append_string_id(improvements[improvement].name);
        text_append_space();
        if (game.wonder_city[local_3c] < 0) {
          text_append_lparen();
          text_append_label(0xac);
          text_append_rparen();
          civ = 0;
        }
        else {
          if ((local_2c == 0) && (game_language == 0)) {
            local_88 = 0xad;
          }
          else {
            local_88 = 0xd8;
          }
          text_append_label(local_88);
          text_append_space();
          city = (iptr)game.wonder_city[local_3c];
          text_append(city * 0x58 + ADDR(0x64f360, ((u8 *)&cities + 32)));
          text_append_space();
          text_append_lparen();
          iVar1 = civ_get_adjective((int)cities[city].owner);
          text_append(iVar1);
          text_append_rparen();
          civ = (int)cities[city].owner;
        }
        text_set_font(ADDR(0x63eac0, ((u8 *)&g.d_0063eac0)));
        uVar6 = 1;
        uVar5 = 1;
        uVar4 = 0x12;
        uVar2 = civ_color_secondary(civ);
        text_set_colors(uVar2,uVar4,uVar5,uVar6);
        local_48 = font_text_width(text_draw_font,ADDR(0x679640, ((u8 *)&g.d_00679640)));
        local_48 += 0x43;
        local_44 = advisor_client_width - (advisor_vscroll_width + 2);
        local_64 = ((local_44 >> 1) + advisor_client_x) - (local_48 >> 1);
        sprite_draw
                  ((Sprite *)(&wonder_icon_sprites + local_3c * 0x3c),(iptr)local_84,ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),
                   local_64,local_70 + 10);
        local_64 += 0x42;
        local_40 = local_70 + 8;
        gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_64,local_40);
        local_70 += local_30;
        local_5c = local_70 - 2;
        rect_set((iptr)local_28,advisor_client_x + 2,local_4c,
                           ((advisor_client_width + advisor_client_x) - advisor_vscroll_width) - 4,local_5c);
        uVar2 = civ_color_primary(civ);
        gfx_draw_rect_frame(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),(iptr)local_28,uVar2);
      }
      local_54++;
    }
  }
  if (advisor_controls_created == 0) {
    rect_set((iptr)local_28,(advisor_client_right - advisor_vscroll_width) - 2,local_58,advisor_client_right - 2,
                       local_6c);
    scrollbar_create((Control *)&advisor_scrollbar,ADDR(0x63eb58, ((u8 *)&g.d_0063eb58)),200,(iptr)local_28,1);
    uVar2 = int_clamp(local_34 - 1,0,999);
    scrollbar_set_range((Control *)&advisor_scrollbar,0,uVar2);
    scrollbar_set_pos((C_0040f380_40 *)&advisor_scrollbar,advisor_first_row);
    scrollbar_set_page_size((Control *)&advisor_scrollbar,advisor_rows_per_page);
    scrollbar_set_callback((Control *)&advisor_scrollbar,ADDR(0x402d1a, wonders_report_on_scroll));
    ctrl_show_and_redraw((Control *)&advisor_scrollbar);
    advisor_controls_created = 1;
  }
  wnd_blit_surface((DibSurface *)&advisor_window);
  return;
}
#undef advisor_client_width
#undef advisor_client_x
#undef advisor_first_row
#undef advisor_row_height
#undef text_draw_font
#undef _DAT_0063ef68
#undef _DAT_0063ef78
#undef _DAT_0063ef7c
#undef local_88
#undef local_84
#undef local_74
#undef local_70
#undef local_6c
#undef local_68
#undef local_64
#undef improvement
#undef local_5c
#undef local_58
#undef local_54
#undef city
#undef local_4c
#undef local_48
#undef local_44
#undef local_40
#undef local_3c
#undef civ
#undef local_34
#undef local_30
#undef local_2c
#undef local_28
#undef local_18
#undef aiStack_14

/* 00431c56 auto */
#define advisor_first_row (*(i32 *)((u8 *)&g.d_0063ef70))
void __cdecl wonders_report_on_scroll(i32 param_1)

{
  advisor_first_row = param_1;
  wonders_report_draw();
  return;
}
#undef advisor_first_row

/* 00431c73 auto */
#define _DAT_00625ec0 (*(i32 *)((u8 *)&g.d_00625ec0))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl wonders_report_show(iptr param_1)

{
  picwnd_open((C_004083b0_4c4 *)&advisor_window,7,7,1,600,400,0,0);
  advisor_report_civ = param_1;
  advisor_add_close_button((C_004083b0_430 *)&advisor_window);
  wnd_set_redraw_callback((SurfaceWindow *)&advisor_window,ADDR(0x401b45, wonders_report_draw));
  wnd_repaint((SurfaceWindow *)&advisor_window);
  window_show((C_004083b0_4 *)&advisor_window);
  if (2 < game.multiplayer) {
    wnd_set_modal_idle_callback((C_00408010_b8 *)&advisor_wnd,ADDR(0x402789, advisor_mp_idle));
  }
  _DAT_00625ec0 = timer_ticks();
  wnd_run_modal_loop((C_00408010_b8 *)&advisor_wnd);
  wnd_set_modal_idle_callback((C_00408010_b8 *)&advisor_wnd,0);
  picwnd_close((C_004083b0_488 *)&advisor_window);
  return;
}
#undef _DAT_00625ec0

/* 0043cc00 auto */
void __cdecl city_reveal_to_civ(iptr city,iptr param_2)

{
  if (-1 < param_2) {
    cities[city].known_to = cities[city].known_to | (byte)(1 << ((byte)param_2 & 0x1f));
    *(i8 *)&cities[city].revealed_size[param_2] = cities[city].size;
  }
  return;
}

/* 0043cc7e auto */
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
int __cdecl city_population_units(iptr city)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 0;
  for (local_8 = 1; local_8 <= cities[city].size; local_8++) {
    local_c += local_8;
  }
  if (local_c < 2) {
    local_c = 1;
  }
  return local_c;
}
#undef local_c
#undef local_8

/* 0043cef9 auto */
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
#define local_c (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(8)))
uint __cdecl city_objective_value(iptr city)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = (uint)((cities[city].flags & 0x4000000) != 0);
  if ((scenario_flags & 4) != 0) {
    for (local_8 = 0; local_8 < 0x1c; local_8++) {
      if (game.wonder_city[local_8] == city) {
        local_c++;
      }
    }
  }
  return local_c;
}
#undef scenario_flags
#undef local_c
#undef local_8

/* 0043cf76 auto */
#define city (*(iptr *)(frame_ + FRAME_OFF(0)))
i32 __cdecl city_at(int x,iptr y)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = map_in_bounds(x,y);
  if ((iVar1 != 0) && (iVar1 = tile_city_owner(x,y), -1 < iVar1)) {
    for (city = 0; city < game.num_cities; city++) {
      if (((cities[city].id != 0) && (cities[city].x == x)) &&
         (cities[city].y == y)) {
        return city;
      }
    }
  }
  return 0xffffffff;
}
#undef city

/* 0043d07a auto */
#define local_18 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define city (*(iptr *)(frame_ + FRAME_OFF(16)))
iptr __cdecl city_find_nearest(iptr x,iptr y,iptr param_3,int param_4,iptr civ)

{
  short x2;
  short y2;
  int iVar3;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_14 = -1;
  nearest_city_dist = 9999;
  if ((-1 < param_4) && (local_18 = tile_land_landmass(x,y), local_18 < 0)) {
    param_4 = -1;
  }
  for (city = 0; city < game.num_cities; city++) {
    if (cities[city].id != 0) {
      x2 = cities[city].x;
      y2 = cities[city].y;
      if (((((param_4 < 0) || (local_18 == param_4)) &&
           (((param_3 < 0 || ((int)cities[city].owner == (param_3 & 0xffU))) ||
            ((-1 < civ && (cities[city].owner == civ)))))) &&
          ((param_4 != -2 || (iVar3 = city_has_improvement(city,0x22), iVar3 != 0)))) &&
         (iVar3 = map_distance_diag(x,y,(int)x2,(int)y2), iVar3 <= nearest_city_dist))
      {
        local_14 = city;
        nearest_city_dist = iVar3;
      }
    }
  }
  return local_14;
}
#undef local_18
#undef local_14
#undef city

/* 0043d20a auto */
#define improvement (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_c (*(byte (*)[4])(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
i32 __cdecl city_has_improvement(iptr city,iptr param_2)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  if (((0 < param_2) && (param_2 < 0x23)) &&
     (bit_index_split(param_2,(iptr)&improvement,(iptr)local_c),
     (local_c[0] & cities[city].improvements[improvement]) != 0)) {
    local_8 = 1;
  }
  return local_8;
}
#undef improvement
#undef local_c
#undef local_8

/* 0043d289: written by hand in src/game/regargs.c */

/* 0043d400 auto */
#define _DAT_0063f54c (*(i32 *)((u8 *)&g.d_0063f54c))
#define _DAT_0063f550 (*(i32 *)((u8 *)&g.d_0063f550))
#define _DAT_0063f560 (*(i32 *)((u8 *)&g.d_0063f560))
#define _DAT_0063f570 (*(i32 *)((u8 *)&g.d_0063f570))
#define _DAT_0063f66c (*(i32 *)((u8 *)&g.d_0063f66c))
#define x4 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_138 (*(int *)(frame_ + FRAME_OFF(8)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(16)))
#define local_12c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_128 (*(int (*)[11])(frame_ + FRAME_OFF(24)))
#define local_fc (*(iptr (*)[16])(frame_ + FRAME_OFF(68)))
#define local_bc (*(int *)(frame_ + FRAME_OFF(132)))
#define local_b8 (*(iptr *)(frame_ + FRAME_OFF(136)))
#define local_b4 (*(int *)(frame_ + FRAME_OFF(140)))
#define local_b0 (*(int *)(frame_ + FRAME_OFF(144)))
#define local_ac (*(int *)(frame_ + FRAME_OFF(148)))
#define local_a8 (*(uint *)(frame_ + FRAME_OFF(152)))
#define local_a4 (*(uint *)(frame_ + FRAME_OFF(156)))
#define local_a0 (*(int *)(frame_ + FRAME_OFF(160)))
#define local_9c (*(int *)(frame_ + FRAME_OFF(164)))
#define y3 (*(int *)(frame_ + FRAME_OFF(168)))
#define local_94 (*(uint *)(frame_ + FRAME_OFF(172)))
#define x3 (*(int *)(frame_ + FRAME_OFF(176)))
#define local_8c (*(uint *)(frame_ + FRAME_OFF(180)))
#define local_88 (*(int *)(frame_ + FRAME_OFF(184)))
#define local_84 (*(iptr *)(frame_ + FRAME_OFF(188)))
#define y2 (*(int *)(frame_ + FRAME_OFF(192)))
#define local_7c (*(iptr *)(frame_ + FRAME_OFF(196)))
#define local_78 (*(uptr *)(frame_ + FRAME_OFF(200)))
#define local_74 (*(iptr *)(frame_ + FRAME_OFF(204)))
#define x2 (*(iptr *)(frame_ + FRAME_OFF(208)))
#define local_6c (*(uint *)(frame_ + FRAME_OFF(212)))
#define local_68 (*(iptr *)(frame_ + FRAME_OFF(216)))
#define local_64 (*(uint *)(frame_ + FRAME_OFF(220)))
#define local_60 (*(uint *)(frame_ + FRAME_OFF(224)))
#define local_5c (*(iptr (*)[16])(frame_ + FRAME_OFF(228)))
#define local_1c (*(iptr *)(frame_ + FRAME_OFF(292)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(296)))
#define local_14 (*(uint *)(frame_ + FRAME_OFF(300)))
#define local_c (*(uint *)(frame_ + FRAME_OFF(308)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(312)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl city_calc_commodity_demand(uptr city)

{
  iptr *piVar1;
  char cVar2;
  iptr iVar6;
  byte bVar7;
  iptr civ;
  iptr iVar5;
  int city2;
  byte *pbVar9;
  uint uVar10;
  i32 uVar11;
  int iVar12;
  iptr iVar3;
  i8 frame_[FRAME_OFF(320)] __attribute__((aligned(8)));  /* original stack frame */
  local_12c = 0;  /* stale stack the original reads (FRAME_PRESETS) */
  
  if ((((cities[city].flags & 0x20000) != 0) || (game.reveal_map != '\0')) ||
     (((int)game.turn + city & 0xf) == 0)) {
    cities[city].flags = cities[city].flags & 0xfffdffff;
    x3 = (int)cities[city].x;
    y3 = (int)cities[city].y;
    civ = (iptr)cities[city].owner;
    local_a4 = tile_landmass(x3,y3);
    local_b0 = (cities[city].size + 2) / 5;
    local_8c = (uint)civs[cities[city].owner].num_advances;
    local_14 = y3 - ((int)map.height >> 1);
    local_6c = x3 - ((int)map.width >> 1);
    local_ac = 0;
    local_64 = 0;
    local_94 = 0;
    local_a0 = 0;
    if ((int)local_14 < 0) {
      local_a0 = ~local_14 + 1;
    }
    if (0 < (int)local_14) {
      local_94 = local_14;
    }
    if (0 < (int)local_6c) {
      local_64 = local_6c;
    }
    if ((int)local_6c < 0) {
      local_ac = ~local_6c + 1;
    }
    if ((int)local_14 < 1) {
      local_14 = ~local_14 + 1;
    }
    if ((int)local_6c < 1) {
      local_6c = ~local_6c + 1;
    }
    local_b4 = 0;
    for (local_68 = 0; local_68 < 0xb; local_68++) {
      local_128[local_68] = 0;
    }
    for (local_68 = 0; local_68 < 0x10; local_68++) {
      (&city_commodity_demand_scores)[local_68] = 0;
      (&city_commodity_supply_scores)[local_68] = (&city_commodity_demand_scores)[local_68];
      local_5c[local_68] = local_68;
      local_fc[local_68] = local_5c[local_68];
    }
    for (local_68 = 0; local_68 < 0x15; local_68++) {
      x2 = map_wrap_x((char)(&city_tile_dx_table)[local_68] + x3);
      y2 = (char)(&city_tile_dy_table)[local_68] + y3;
      iVar5 = map_in_bounds(x2,y2);
      if (iVar5 != 0) {
        bVar7 = tile_terrain(x2,y2);
        local_78 = (uint)bVar7;
        local_128[bVar7]++;
        city2 = tile_resource(x2,y2);
        if (city2 != 0) {
          local_128[local_78] += 3;
        }
        pbVar9 = (byte *)tile_at(x2,y2);
        if ((*pbVar9 & 0x80) != 0) {
          local_b4++;
        }
        uVar10 = tile_improvements(x2,y2);
        if ((uVar10 & 0x10) != 0) {
          local_12c++;
        }
      }
    }
    local_128[6] += local_128[7];
    local_128[7] = 0;
    city_commodity_supply_scores = local_128[9] * 3 + local_128[6] * 6 + local_128[3] * 4 + local_b4 * 3;
    if ((int)local_8c < 0x10) {
      city_commodity_supply_scores = city_commodity_supply_scores * 2;
    }
    if ((int)local_8c < 0x18) {
      city_commodity_supply_scores = city_commodity_supply_scores << 1;
    }
    if ((int)local_8c < 0x31) {
      if (cities[city].size < 3) {
        city_commodity_supply_scores = city_commodity_supply_scores << 1;
      }
    }
    else {
      city_commodity_supply_scores = city_commodity_supply_scores / 2;
    }
    if (7 < cities[city].size) {
      city_commodity_supply_scores = city_commodity_supply_scores / 2;
    }
    local_bc = local_128[6] + 2;
    if ((int)map.height / 3 < (int)local_14) {
      local_bc = local_128[6] + 3;
    }
    _DAT_0063f66c = (local_b4 / 2 + local_128[4] * 2 + local_128[2]) * local_bc;
    supply_score_beads = local_128[10] * 8 - local_14;
    if ('\t' < cities[city].size) {
      supply_score_beads = supply_score_beads >> 1;
    }
    if (0x20 < (int)local_8c) {
      supply_score_beads = supply_score_beads >> 1;
    }
    iVar12 = (local_128[1] * 3 + local_128[0]) - local_b4;
    city2 = int_clamp((int)local_8c / 10,1,2);
    supply_score_cloth = iVar12 * city2;
    city2 = civ_has_advance(civ,0x25);
    if (city2 != 0) {
      supply_score_cloth = supply_score_cloth * 3 >> 1;
    }
    if ((int)local_8c < 8) {
      supply_score_cloth = supply_score_cloth >> 1;
    }
    if ((int)local_8c < 0x10) {
      supply_score_cloth = supply_score_cloth >> 1;
    }
    supply_score_salt = (local_128[10] * 3 + local_128[0] * 4 + local_128[8] * 2) - (int)local_8c / 6;
    city2 = civ_has_advance(civ,0x41);
    if (city2 == 0) {
      supply_score_salt = supply_score_salt / 3;
    }
    city2 = city_has_improvement(city,9);
    if (city2 != 0) {
      supply_score_salt += (supply_score_salt >> 1);
    }
    if (((local_a4 & 1) != 0) && ((int)local_a4 < 6)) {
      supply_score_salt += (supply_score_salt >> 1);
    }
    supply_score_coal = (local_128[9] + local_128[1] + local_128[3] + local_128[8] + 1) * local_128[4] *
                   5;
    city2 = local_b0 / 2;
    if (1 < city2) {
      city2 = 2;
    }
    supply_score_coal = int_shift_signed(supply_score_coal,city2 - 1);
    if (((local_a4 & 1) != 0) && (1 < (int)local_a4)) {
      supply_score_coal += (supply_score_coal >> 1);
    }
    if ((int)local_8c < 0x14) {
      supply_score_coal = supply_score_coal >> 1;
    }
    supply_score_copper = local_128[5] * 5 + local_128[4] * 5;
    if ((local_a4 != 0) && ((local_a4 & 1) == 0)) {
      supply_score_copper = supply_score_copper * 2;
    }
    city2 = (local_128[2] * 5 - local_128[1]) + local_b4;
    supply_score_dye = city2 * 2;
    if ((local_a4 != 0) && ((local_a4 & 3) == 0)) {
      supply_score_dye = city2 * 4;
    }
    local_8 = local_b4 * 5 - local_128[2];
    local_1c = local_128[1] << 2;
    local_8 = int_clamp(local_8,0,local_1c);
    local_1c = int_clamp(local_1c,0,local_8);
    supply_score_wine = local_1c + (int)(((int)map.width >> 1) - local_6c) / 2 + local_8;
    if (local_94 != 0) {
      supply_score_wine = supply_score_wine >> 1;
    }
    uVar11 = int_clamp(local_b0 - 1,0xfffffffe,1);
    supply_score_wine = int_shift_signed(supply_score_wine,uVar11);
    if ((local_a4 - 2 & 3) == 0) {
      supply_score_wine += (supply_score_wine >> 1);
    }
    if (civs[civ].tribe == 9) {
      supply_score_wine = supply_score_wine << 1;
    }
    if ('\n' < cities[city].size) {
      supply_score_wine = supply_score_wine >> 1;
    }
    supply_score_silk = (local_128[3] * 2 + local_128[9] + 1) * (local_128[4] + 1);
    if (((supply_score_silk != 0) && (supply_score_silk = supply_score_silk + local_64 * 2, local_a4 != 0)) &&
       ((int)local_a4 % 5 == 0)) {
      supply_score_silk = supply_score_silk * 2;
    }
    if (civs[civ].tribe == 0xb) {
      supply_score_silk = supply_score_silk << 1;
    }
    supply_score_silver = local_128[5] * 8;
    if (supply_score_silver != 0) {
      supply_score_silver = supply_score_silver + local_128[4] + local_6c;
      city2 = civ_has_advance(civ,0x27);
      if (city2 == 0) {
        supply_score_silver = supply_score_silver >> 1;
      }
      if (8 < (int)local_a4) {
        supply_score_silver += (supply_score_silver >> 1);
      }
      if (cities[city].size < 5) {
        supply_score_silver = supply_score_silver >> 1;
      }
    }
    if (civs[civ].tribe == 10) {
      supply_score_silk = supply_score_silk << 1;
    }
    supply_score_spice = (local_128[9] * 3 + local_128[8] * 2 + local_128[0] * 2) *
                   ((local_128[10] + local_b4) / 2);
    if (supply_score_spice != 0) {
      if ((int)local_14 < 10) {
        supply_score_spice = supply_score_spice * 2;
      }
      supply_score_spice -= local_14;
      if (*(short *)(&landmass_table + local_a4 * 0x10) < 0x1a) {
        supply_score_spice += (supply_score_spice >> 1);
      }
      if (300 < *(short *)(&landmass_table + local_a4 * 0x10)) {
        supply_score_spice = supply_score_spice >> 1;
      }
      if (local_a4 == 1) {
        supply_score_spice = supply_score_spice >> 1;
      }
    }
    supply_score_gems = (local_128[5] + 1) * (local_128[8] + 1) * (local_128[0] + 1) + local_128[1];
    if (supply_score_gems != 0) {
      city2 = int_clamp(local_b0,1,4);
      supply_score_gems = (city2 * supply_score_gems) / 2;
      if (local_a4 == 7) {
        supply_score_gems += (supply_score_gems >> 1);
      }
    }
    supply_score_gold = (local_128[5] + local_128[4] / 2 + 1) * (local_b4 + 2);
    if (2 < local_128[5]) {
      supply_score_gold = supply_score_gold * 2;
    }
    if (4 < cities[city].size) {
      supply_score_gold = supply_score_gold << 1;
    }
    if ('\t' < cities[city].size) {
      supply_score_gold = supply_score_gold << 1;
    }
    supply_score_oil = local_128[6] * 8 + local_128[0] * 10 + local_128[8] * 6 + local_128[7] * 0xc;
    if (game.advance_known_by[0xe] == '\0') {
      supply_score_oil = supply_score_oil >> 3;
    }
    if (supply_score_oil == 0) {
      supply_score_oil = -1;
    }
    else {
      if (local_a4 == 0x11) {
        supply_score_oil = supply_score_oil * 3;
      }
      else if ((1 < (int)local_a4) && ((local_a4 - 1 & 7) == 0)) {
        supply_score_oil += (supply_score_oil >> 1);
      }
      city2 = int_clamp(local_b0 / 2 - 2,1,2);
      supply_score_oil = city2 * supply_score_oil;
    }
    supply_score_uranium = (local_128[6] + local_128[0] + 1) * (local_128[4] + local_b4 + 1) *
                   (local_128[5] + 1);
    city2 = civ_has_advance(civ,0x3a);
    if (city2 == 0) {
      supply_score_uranium = 0;
    }
    if (supply_score_uranium == 0) {
      supply_score_uranium = -1;
    }
    else {
      if ((local_a4 != 0) && ((int)local_a4 % 10 == 0)) {
        supply_score_uranium += (supply_score_uranium >> 1);
      }
      city2 = local_b0;
      if (5 < local_b0) {
        city2 = 6;
      }
      supply_score_uranium = (supply_score_uranium * city2) / 6;
    }
    city_commodity_demand_scores = (local_128[6] + local_128[7]) * 5 + (int)(local_14 * 3) / 2 + local_128[5] * 2 +
                   local_128[3];
    city2 = ((int)local_8c / 10) * city_commodity_demand_scores;
    _DAT_0063f54c = local_128[4] * 4 + local_128[3] * 4 + ((int)(city2 + (city2 >> 0x1f & 7U)) >> 3)
    ;
    if (cities[city].size < 3) {
      city_commodity_demand_scores = city_commodity_demand_scores * 2;
    }
    city2 = civ_has_advance(civ,0x25);
    if (city2 != 0) {
      city_commodity_demand_scores = city_commodity_demand_scores / 3;
    }
    city2 = civ_has_advance(civ,0x30);
    if (city2 != 0) {
      city_commodity_demand_scores = 1;
    }
    if ((int)local_8c < 10) {
      city_commodity_demand_scores = city_commodity_demand_scores << 1;
    }
    if ((int)local_8c < 0x14) {
      city_commodity_demand_scores = city_commodity_demand_scores << 1;
    }
    if (0x2f < (int)local_8c) {
      city_commodity_demand_scores = city_commodity_demand_scores / 2;
    }
    if ((int)map.height >> 2 == local_14 || (int)(((int)map.height >> 2) - local_14) < 0) {
      local_138 = ~(((int)map.height >> 2) - local_14) + 1;
    }
    else {
      local_138 = ((int)map.height >> 2) - local_14;
    }
    city_wool_demand_score = local_138 * 2 + local_128[1] * 2 + local_128[3];
    city2 = civ_has_advance(civ,0x25);
    if (city2 != 0) {
      city_wool_demand_score = city_wool_demand_score << 1;
    }
    demand_score_beads = local_14 + ((0x15 - local_128[10]) * 3) / 2;
    if (cities[city].size < 4) {
      demand_score_beads += (demand_score_beads >> 1);
    }
    if (11 < cities[city].size) {
      demand_score_beads = demand_score_beads / 2;
    }
    if (0x2f < (int)local_8c) {
      demand_score_beads = demand_score_beads / 2;
    }
    local_18 = 8;
    for (local_88 = (int)cities[city].size; (local_18 != 0 && (0 < local_88));
        local_88 = local_88 - local_9c) {
      local_9c = int_clamp(local_88,0,5);
      _DAT_0063f550 += local_9c * local_18;
      local_18 = local_18 / 2;
    }
    _DAT_0063f550 -= (int)local_8c / 2;
    demand_score_coal = (local_14 + 10) * local_b0 + local_8c;
    if (cities[city].size < 5) {
      demand_score_coal = 0;
    }
    if (cities[city].size < 8) {
      demand_score_coal = demand_score_coal >> 1;
    }
    city2 = civ_has_advance(civ,0x25);
    if (city2 != 0) {
      demand_score_coal = demand_score_coal << 1;
    }
    city2 = civ_has_advance(civ,0x17);
    if (city2 != 0) {
      demand_score_coal = demand_score_coal << 1;
    }
    city2 = city_has_improvement(city,0x13);
    if (city2 != 0) {
      demand_score_coal = demand_score_coal << 1;
    }
    city2 = city_has_improvement(city,0x14);
    if (((city2 != 0) || (city2 = city_has_improvement(city,0x15), city2 != 0)) ||
       (city2 = city_has_improvement(city,0x1d), city2 != 0)) {
      demand_score_coal = demand_score_coal >> 3;
    }
    demand_score_copper = (local_b4 + local_12c + 1) * local_b0;
    if (demand_score_copper <= supply_score_copper) {
      demand_score_copper = demand_score_copper >> 1;
    }
    city2 = city_has_improvement(city,5);
    if (city2 != 0) {
      demand_score_copper += (demand_score_copper >> 1);
    }
    city2 = city_has_improvement(city,10);
    if (city2 != 0) {
      demand_score_copper += (demand_score_copper >> 1);
    }
    city2 = civ_has_advance(civ,0x17);
    if (city2 != 0) {
      demand_score_copper += (demand_score_copper >> 1);
    }
    city2 = civ_has_advance(civ,0x10);
    if (city2 != 0) {
      demand_score_copper = (int)(demand_score_copper + (demand_score_copper >> 0x1f & 3U)) >> 2;
    }
    if (cities[city].size < 5) {
      demand_score_copper = demand_score_copper >> 1;
    }
    demand_score_dye = supply_score_cloth + local_12c;
    city2 = civ_has_advance(civ,10);
    if (city2 != 0) {
      demand_score_dye = demand_score_dye / 2;
    }
    city2 = civ_has_advance(civ,0x30);
    if (city2 != 0) {
      demand_score_dye = demand_score_dye / 2;
    }
    if ((int)cities[city].x == (int)cities[city].y ||
        (int)cities[city].x - (int)cities[city].y < 0) {
      x4 = ~((int)cities[city].x - (int)cities[city].y) + 1;
    }
    else {
      x4 = (int)cities[city].x - (int)cities[city].y;
    }
    _DAT_0063f560 = local_b0 * 4 + 4 + x4;
    demand_score_silk = ((((int)map.height >> 1) - local_14) * 2 - local_6c) + ((int)map.width >> 1) +
                   local_128[9] * 4 + local_128[1] / 2 + local_128[8] * 2 + local_128[0] * 4;
    uVar11 = int_clamp(local_b0 - 1,0xffffffff,1);
    demand_score_silk = int_shift_signed(demand_score_silk,uVar11);
    if ((local_a4 == 1) && ((city & 2) != 0)) {
      demand_score_silk += (demand_score_silk >> 1);
    }
    if (cities[city].size < 7) {
      demand_score_silk = demand_score_silk >> 1;
    }
    demand_score_silver = (int)cities[city].size << 3;
    demand_score_gold = 0;
    _DAT_0063f570 = 0;
    local_84 = 10;
    city2 = ((int)cities[city].y + (int)cities[city].x) % 3;
    if (city2 == 1) {
      local_84 = 0xc;
      _DAT_0063f570 = demand_score_silver;
    }
    else if (city2 == 2) {
      local_84 = 0xd;
      demand_score_gold = demand_score_silver;
    }
    city2 = city_has_improvement(city,0xb);
    if ((city2 != 0) || (city2 = civ_has_wonder(civ,10), city2 != 0)) {
      (&city_commodity_demand_scores)[local_84] = (&city_commodity_demand_scores)[local_84] * 3 >> 1;
    }
    city2 = city_has_improvement(city,10);
    if (city2 != 0) {
      (&city_commodity_demand_scores)[local_84] = (&city_commodity_demand_scores)[local_84] * 3 >> 1;
    }
    city2 = civ_has_advance(civ,0x16);
    if (city2 != 0) {
      (&city_commodity_demand_scores)[local_84] = (&city_commodity_demand_scores)[local_84] >> 1;
    }
    city2 = civ_has_advance(civ,0x10);
    if (city2 != 0) {
      (&city_commodity_demand_scores)[local_84] = (&city_commodity_demand_scores)[local_84] >> 1;
    }
    if (civs[civ].tribe == 0x11) {
      (&city_commodity_demand_scores)[local_84] = (&city_commodity_demand_scores)[local_84] << 1;
    }
    city2 = local_8c - 0xc;
    if (city2 < 1) {
      city2 = 0;
    }
    demand_score_spice = (int)*(short *)(&landmass_table + local_a4 * 0x10) / 10 - city2;
    if (cities[city].size < 4) {
      demand_score_spice = demand_score_spice / 2;
    }
    if (400 < *(short *)(&landmass_table + local_a4 * 0x10)) {
      if (7 < cities[city].size) {
        demand_score_spice = demand_score_spice << 1;
      }
      if ((-(int)cities[city].x - (int)cities[city].y & 3U) == 0) {
        demand_score_spice = 0;
      }
    }
    city2 = civ_has_advance(civ,0x46);
    if (city2 != 0) {
      demand_score_spice = demand_score_spice >> 1;
    }
    city2 = civ_has_advance(civ,0x25);
    if (city2 == 0) {
      demand_score_oil = -1;
    }
    else {
      demand_score_oil = ((int)local_8c / 3) * (local_b0 + 2);
      if (demand_score_oil <= supply_score_oil) {
        demand_score_oil = demand_score_oil >> 1;
      }
      city2 = city_has_improvement(city,0xf);
      if (city2 == 0) {
        if (cities[city].size < 5) {
          demand_score_oil = demand_score_oil >> 1;
        }
        if (cities[city].size < '\n') {
          demand_score_oil = demand_score_oil >> 1;
        }
        if (cities[city].size < 20) {
          demand_score_oil = demand_score_oil >> 1;
        }
      }
      else {
        demand_score_oil = (demand_score_oil * 3) / 2;
      }
      city2 = civ_has_advance(civ,5);
      if (city2 != 0) {
        demand_score_oil = demand_score_oil * 3;
      }
      city2 = city_has_improvement(city,0x19);
      if (city2 != 0) {
        demand_score_oil = demand_score_oil << 1;
      }
      city2 = city_has_improvement(city,0xd);
      if (city2 != 0) {
        demand_score_oil = demand_score_oil >> 1;
      }
      city2 = city_has_improvement(city,0x12);
      if (city2 != 0) {
        demand_score_oil = demand_score_oil >> 1;
      }
    }
    city2 = civ_has_advance(civ,0x3a);
    if (city2 == 0) {
      demand_score_uranium = -1;
    }
    else {
      demand_score_uranium = local_8c * local_8c;
      uVar11 = int_clamp(local_b0 - 3,0xfffffffd,0);
      demand_score_uranium = int_shift_signed(demand_score_uranium,uVar11);
      city2 = city_has_improvement(city,0x15);
      if ((city2 != 0) || (city2 = city_has_improvement(city,0x11), city2 != 0)) {
        demand_score_uranium = demand_score_uranium << 1;
      }
    }
    for (local_68 = 0; local_68 < 0x10; local_68++) {
      if ((&city_commodity_supply_scores)[local_68] < (&city_commodity_demand_scores)[local_68]) {
        if (0 < (&city_commodity_supply_scores)[local_68]) {
          (&city_commodity_supply_scores)[local_68] = 0;
        }
      }
      else if (0 < (&city_commodity_demand_scores)[local_68]) {
        (&city_commodity_demand_scores)[local_68] = 0;
      }
    }
    int_pairs_bubble_sort(0x10,(iptr)local_fc,ADDR(0x63f668, ((u8 *)&g.d_0063f668)));
    int_pairs_bubble_sort(0x10,(iptr)local_5c,ADDR(0x63f540, ((u8 *)&g.d_0063f540)));
    local_b8 = 0xf;
    for (local_68 = 0; local_68 < 3; local_68++) {
      do {
        piVar1 = local_fc + local_b8;
        local_74 = *piVar1;
        iVar3 = local_74;
        local_b8--;
      } while (*(int *)(&supply_score_wool + local_b8 * 4) < 0);
      (*(i8 *)((char *)&local_74 + 0)) = (i8)*piVar1;
      *(i8 *)&cities[city].supplies[local_68] = (i8)local_74;
      local_74 = iVar3;
    }
    local_b8 = 0xf;
    for (local_68 = 0; local_68 < 3; local_68++) {
      do {
        piVar1 = local_5c + local_b8;
        local_74 = *piVar1;
        iVar6 = local_74;
        local_b8--;
      } while ((&city_wool_demand_score)[local_b8] < 0);
      (*(i8 *)((char *)&local_74 + 0)) = (i8)*piVar1;
      *(i8 *)&cities[city].demands[local_68] = (i8)local_74;
      local_74 = iVar6;
    }
    if ((int)local_8c < 0x20) {
      local_60 = (cities[city].y * 5 + cities[city].x * 3) % 0xe;
      local_c = (cities[city].y * 7 + cities[city].x * 0xd) % 0xe;
    }
    else {
      local_60 = (cities[city].y * 5 + cities[city].x * 3) % 9 + 5;
      local_c = (cities[city].y * 7 + cities[city].x * 0xd) % 9 + 5;
    }
    if (local_c == local_60) {
      local_c = 0xfffffffe;
    }
    local_a8 = 0;
    for (local_68 = 0; local_68 < 3; local_68++) {
      if ('\r' < *(char *)&cities[city].demands[local_68]) {
        local_a8 = local_a8 | 1;
      }
      if ('\r' < *(char *)&cities[city].supplies[local_68]) {
        local_a8 = local_a8 | 2;
      }
      if (((int)*(char *)&cities[city].supplies[local_68] == local_60) ||
         ((int)*(char *)&cities[city].demands[local_68] == local_60)) {
        local_60 = 0xfffffffe;
      }
      if (((int)*(char *)&cities[city].supplies[local_68] == local_c) ||
         ((int)*(char *)&cities[city].demands[local_68] == local_c)) {
        local_c = 0xfffffffe;
      }
    }
    if (((int)local_60 < 0) && ((local_a8 & 1) == 0)) {
      city2 = civ_has_advance(civ,0x25);
      if ((city2 == 0) || ((local_60 & 1) == 0)) {
        city2 = civ_has_advance(civ,0x3a);
        if ((city2 != 0) && ((local_60 & 1) == 0)) {
          local_60 = 0xf;
        }
      }
      else {
        local_60 = 0xe;
      }
    }
    if (-1 < (int)local_60) {
      cities[city].demands[1] = (u8)local_60;
    }
    if (((int)local_c < 0) && ((local_a8 & 2) == 0)) {
      local_c = (local_c & 1) + 0xe;
      if ((local_c == 0xe) && (city2 = civ_has_advance(civ,0x25), city2 == 0)) {
        local_c = 0xffffffff;
      }
      if ((local_c == 0xf) && (city2 = civ_has_advance(civ,0x3a), city2 == 0)) {
        local_c = 0xffffffff;
      }
    }
    if (-1 < (int)local_c) {
      cities[city].supplies[1] = (u8)local_c;
    }
    for (local_68 = 0; local_68 < (char)cities[city].trade_routes; local_68++) {
      cVar2 = *(char *)&cities[city].route_goods[local_68];
      if (-1 < cVar2) {
        for (local_7c = 0; local_7c < 3; local_7c++) {
          if (*(char *)&cities[city].supplies[local_7c] == cVar2) {
            *(char *)&cities[city].supplies[local_7c] =
                 -*(char *)&cities[city].supplies[local_7c];
          }
        }
        city2 = (int)cities[city].route_partner[local_68];
        local_74 = -1;
        for (local_7c = 0; local_7c < (char)cities[city2].trade_routes; local_7c++) {
          if ((int)cities[city2].route_partner[local_7c] == city) {
            local_74 = (iptr)*(char *)&cities[city2].route_goods[local_7c];
          }
        }
        if (-1 < local_74) {
          for (local_7c = 0; local_7c < 3; local_7c++) {
            if (*(char *)&cities[city].demands[local_7c] == local_74) {
              *(char *)&cities[city].demands[local_7c] =
                   -*(char *)&cities[city].demands[local_7c];
            }
          }
        }
      }
    }
    for (unit = 0; unit < game.num_units; unit++) {
      if ((((units[unit].id != 0) && ((byte)units[unit].home_city == city)) &&
          (unit_types[units[unit].type].role == 7)) && (-1 < (char)units[unit].counter)
         ) {
        for (local_68 = 0; local_68 < 3; local_68++) {
          if (cities[city].supplies[local_68] == units[unit].counter) {
            *(char *)&cities[city].supplies[local_68] =
                 -*(char *)&cities[city].supplies[local_68];
          }
        }
      }
    }
  }
  return;
}
#undef _DAT_0063f54c
#undef _DAT_0063f550
#undef _DAT_0063f560
#undef _DAT_0063f570
#undef _DAT_0063f66c
#undef x4
#undef local_138
#undef unit
#undef local_12c
#undef local_128
#undef local_fc
#undef local_bc
#undef local_b8
#undef local_b4
#undef local_b0
#undef local_ac
#undef local_a8
#undef local_a4
#undef local_a0
#undef local_9c
#undef y3
#undef local_94
#undef x3
#undef local_8c
#undef local_88
#undef local_84
#undef y2
#undef local_7c
#undef local_78
#undef local_74
#undef x2
#undef local_6c
#undef local_68
#undef local_64
#undef local_60
#undef local_5c
#undef local_1c
#undef local_18
#undef local_14
#undef local_c
#undef local_8

/* 0043f493 auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define local_2c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_24 (*(uint *)(frame_ + FRAME_OFF(12)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_1c (*(i8 (*)[24])(frame_ + FRAME_OFF(20)))
void __cdecl city_assign_default_name(iptr city)

{
  char civ;
  int iVar2;
  size_t sVar3;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_20 = 0;
  civ = cities[city].owner;
  str_clear((iptr)local_1c);
  if (leaders[civs[civ].tribe].plural < 1) {
    local_2c = ~(int)leaders[civs[civ].tribe].plural + 1;
  }
  else {
    local_2c = (int)leaders[civs[civ].tribe].plural;
  }
  str_append_string_id((iptr)local_1c,local_2c);
LAB_0043f557:
  do {
    local_20++;
    if (2 < local_20) {
LAB_0043f78e:
      text_close_file();
      return;
    }
    leaders[civs[civ].tribe].city_name_index = leaders[civs[civ].tribe].city_name_index + 1
    ;
    local_24 = (uint)leaders[civs[civ].tribe].city_name_index;
    __chdir(&scenario_dir_path);
    iVar2 = text_open_section(ADDR(0x626258, ((u8 *)&g.d_00626258)),(iptr)local_1c);
    if (iVar2 != 0) {
      __chdir(&game_home_dir);
      iVar2 = text_open_section(ADDR(0x626260, ((u8 *)&g.d_00626260)),(iptr)local_1c);
      if (iVar2 != 0) goto LAB_0043f78e;
    }
    __chdir(&game_home_dir);
    for (; 0 < (int)local_24; local_24--) {
      text_read_line(1);
      sVar3 = _strlen(&text_buffer);
      if ((sVar3 == 0) || (iVar2 = __strnicmp(&text_buffer,s__STOP_00626268,5), iVar2 == 0)) break;
    }
    if ((int)local_24 < 1) {
LAB_0043f714:
      if ((int)local_24 < 1) {
        _memset(cities[city].name,0,0x10);
        _strncpy(cities[city].name,&text_buffer,0xf);
        goto LAB_0043f78e;
      }
      leaders[civs[civ].tribe].city_name_index = '\0';
      goto LAB_0043f557;
    }
    iVar2 = text_open_section(0,ADDR(0x626270, ((u8 *)&g.d_00626270)));
    if (iVar2 == 0) {
      for (; 0 < (int)local_24; local_24--) {
        text_read_line(1);
        sVar3 = _strlen(&text_buffer);
        if ((sVar3 == 0) || (iVar2 = __strnicmp(&text_buffer,s__STOP_00626278,5), iVar2 == 0))
        break;
      }
      goto LAB_0043f714;
    }
    leaders[civs[civ].tribe].city_name_index = '\0';
  } while( true );
}
#undef text_buffer
#undef local_2c
#undef local_24
#undef local_20
#undef local_1c

/* 0043f7a7 auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl city_refresh_area_tiles(iptr city)

{
  char civ;
  short x2;
  short y2;
  iptr x;
  int y;
  int iVar6;
  uint uVar7;
  iptr iVar8;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  x2 = cities[city].x;
  y2 = cities[city].y;
  civ = cities[city].owner;
  net_batch_begin();
  for (local_8 = 0; local_8 < 0x2d; local_8++) {
    x = map_wrap_x((int)(char)(&city_tile_dx_table)[local_8] + (int)x2);
    y = (int)(char)(&city_tile_dy_table)[local_8] + (int)y2;
    iVar6 = map_in_bounds(x,y);
    if (iVar6 != 0) {
      iVar8 = 1;
      uVar7 = tile_get_fertility(x,y);
      tile_set_fertility(x,y,uVar7 & 7,iVar8);
      if (local_8 < 0x15) {
        tile_set_radius_civ(x,y,(int)civ,1);
      }
    }
  }
  net_batch_flush();
  return;
}
#undef local_8

/* 0043f8b0 auto */
#define city_create_busy (*(i32 *)((u8 *)&g.d_006ad8c4))
#define game_loop_active (*(i8 *)((u8 *)&g.d_00628044))
#define local_2c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define city (*(uptr *)(frame_ + FRAME_OFF(8)))
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_14 (*(iptr *)(frame_ + FRAME_OFF(28)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_c (*(int *)(frame_ + FRAME_OFF(36)))
uptr __cdecl city_create(iptr x,iptr y,iptr civ)

{
  char *pcVar1;
  char cVar2;
  byte terrain;
  iptr iVar4;
  iptr iVar5;
  iptr iVar6;
  iptr x2;
  int y2;
  iptr iVar8;
  int iVar10;
  i32 uVar11;
  byte *pbVar12;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  city_create_busy = 1;
  if ((game.multiplayer < 3) || (cVar2 = net_is_host(&net_session), cVar2 != '\0')) {
    for (city = 0; ((int)city < (int)game.num_cities && (cities[city].id != 0));
        city = city + 1) {
    }
    if ((int)game.num_cities == city) {
      if (0xfe < game.num_cities) {
        if (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) &&
           (game.multiplayer < 3)) {
          popup_debug_text(ADDR(0x6262c4, ((u8 *)&g.d_006262c4)));
        }
        city_create_busy = 0;
        return 0xffffffff;
      }
      game.num_cities++;
    }
    civs[civ].num_cities++;
    civs[civ].last_city_turn = game.turn;
    tile_set_improvements(x,y,2,1,1);
    tile_set_improvements(x,y,0x40,0,1);
    cities[city].x = (i16)x;
    cities[city].y = (i16)y;
    cities[city].owner = (byte)civ;
    cities[city].id = next_city_id;
    next_city_id++;
    cities[city].founder = (byte)civ;
    cities[city].turns_captured = '\0';
    cities[city].flags = 0x20000;
    cities[city].size = 1;
    if (game.wonder_city[0x19] < 0) {
      cities[city].known_to = '\0';
      for (local_2c = 0; local_2c < 8; local_2c++) {
        *(i8 *)&cities[city].revealed_size[local_2c] = 0;
      }
    }
    else {
      cities[city].known_to = 0xff;
      for (local_2c = 0; local_2c < 8; local_2c++) {
        *(i8 *)&cities[city].revealed_size[local_2c] = 1;
      }
      tile_set_visible(x,y,0xff,1,1);
      for (local_2c = 1; local_2c < 8; local_2c++) {
        tile_update_known(x,y,local_2c);
      }
    }
    cities[city].specialists = 0;
    cities[city].building = '\0';
    local_10 = 0;
    for (unit_type = 2; unit_type < 0x3e; unit_type++) {
      if ((unit_types[unit_type].role == 1) &&
         (iVar6 = civ_can_build_unit(civ,city,unit_type), iVar6 != 0)) {
        local_c = ((int)(char)unit_types[unit_type].defense << 3) /
                  (int)(char)unit_types[unit_type].cost;
        if ((unit_types[unit_type].flags & 0x400) != 0) {
          local_c++;
        }
        if (local_10 <= local_c) {
          local_10 = local_c;
          cities[city].building = (i8)unit_type;
        }
      }
    }
    pcVar1 = (char *)(cities[city].building + ADDR(0x64c7f4, ((u8 *)&civs + 340)) + civ * 0x594);
    *pcVar1 = *pcVar1 + 1;
    cities[city].food_box = 0;
    cities[city].shield_box = 0;
    cities[city].base_trade = 0;
    cities[city].name[0] = '\0';
    city_assign_default_name(city);
    cities[city].worked_tiles = 0;
    _memset(cities[city].improvements,0,5);
    if (civs[civ].num_cities == 1) {
      city_set_improvement(city,1,1);
      civs[civ].capital_x = (i16)x;
      if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
        net_batch_begin();
        for (local_14 = 0; local_14 < 0x14; local_14++) {
          x2 = map_wrap_x((char)(&city_tile_dx_table)[local_14] + x);
          y2 = (char)(&city_tile_dy_table)[local_14] + y;
          iVar8 = map_in_bounds(x2,y2);
          if ((((iVar8 != 0) &&
               (tile_set_visible(x2,y2,1 << ((byte)civ & 0x1f),1,1), 0x27 < game.turn)) &&
              (local_14 < 8)) &&
             ((iVar10 = tile_at(x2,y2), (game.human_players & *(byte *)(iVar10 + 4)) == 0 &&
              (terrain = tile_terrain(x2,y2), terrain_types[terrain].irrigate_to == -2)))) {
            tile_set_improvements(x2,y2,4,1,1);
          }
        }
        net_batch_flush();
        if ((0x28 < game.turn) &&
           (y2 = tile_at(x,y), (game.human_players & *(byte *)(y2 + 4)) == 0)) {
          uVar11 = int_clamp((game.turn - 0x14) / 0x14,2,10);
          cities[city].size = (i8)uVar11;
          city_set_improvement(city,4,1);
          city_set_improvement(city,5,1);
          city_set_improvement(city,6,1);
        }
        if ((0x28 < game.turn) && (cities[city].building != '\0')) {
          unit_create((int)cities[city].building,civ,x,y);
        }
      }
    }
    cities[city].trade_routes = '\0';
    _memset(cities[city].route_partner,0,3);
    _memset(cities[city].route_goods,0,3);
    for (local_14 = 0; local_14 < 9; local_14++) {
      x2 = map_wrap_x((char)(&dir_dx_table)[local_14] + x);
      y2 = (char)(&dir_dy_table)[local_14] + y;
      iVar10 = map_in_bounds(x2,y2);
      if (iVar10 != 0) {
        iVar10 = tile_is_ocean(x2,y2);
        if (iVar10 != 0) {
          iVar10 = tile_landmass(x2,y2);
          if ((1 < *(short *)(&water_body_sizes + iVar10 * 0x10)) &&
             ((iVar10 < 0x3f || ((cities[city].flags & 0x80) != 0)))) {
            cities[city].flags = cities[city].flags | 0x200000;
          }
          cities[city].flags = cities[city].flags | 0x80;
        }
        pbVar12 = (byte *)tile_at(x2,y2);
        if (((*pbVar12 & 0x80) != 0) || (cVar2 = tile_terrain(x2,y2), cVar2 == 5)) {
          cities[city].flags = cities[city].flags | 0x800;
        }
      }
    }
    city_refresh_area_tiles(city);
    city_calc_commodity_demand(city);
    cities[city].science = 0;
    cities[city].tax = 0;
    cities[city].trade = 0;
    cities[city].total_food = '\0';
    cities[city].total_shields = '\0';
    cities[city].happy = '\0';
    cities[city].unhappy = '\0';
    if (2 < game.multiplayer) {
      net_send_state_diff(0xff,2,0,0,0);
      XD_FlushSendBuffer(5000);
    }
    city_create_busy = 0;
  }
  else {
    city_create_busy = 0;
    nm_city_created_result = 0xfffffffe;
    net_send_message(0x3b,0,x,y,civ,0,0,0,0,0);
    iVar4 = timer_ticks();
    while ((nm_city_created_result == 0xfffffffe && (iVar5 = timer_ticks(), iVar5 - iVar4 < 0xe10))) {
      net_process_messages((NetSession *)&net_session,1,1);
    }
    if (nm_city_created_result == 0xfffffffe) {
      dbg_log(ADDR(0x626280, ((u8 *)&g.d_00626280)));
      popup_game_with_sprite(ADDR(0x6262b0, ((u8 *)&g.d_006262b0)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      game_loop_active = 0;
    }
    while ((net_msgq_priority_count != 0 || (city = nm_city_created_result, net_msgq_normal_count != 0))) {
      net_process_messages((NetSession *)&net_session,1,0);
    }
  }
  return city;
}
#undef city_create_busy
#undef game_loop_active
#undef local_2c
#undef city
#undef unit_type
#undef local_14
#undef local_10
#undef local_c

/* 00440325 auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl city_remove_trade_route(iptr city,iptr param_2)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = param_2; local_8 < (char)cities[city].trade_routes - 1; local_8++)
  {
    cities[city].route_partner[local_8] =
         cities[city].route_partner[local_8 + 1];
    *(i8 *)&cities[city].route_goods[local_8] =
         *(i8 *)&cities[city].route_goods[local_8 + 1];
  }
  cities[city].trade_routes += 0xff;
  cities[city].flags = cities[city].flags | 0x20000;
  return;
}
#undef local_8

/* 004403ec auto */
void __cdecl city_set_trade_route_slot(iptr city,iptr param_2,iptr param_3,iptr param_4)

{
  i32 uVar1;
  
  cities[city].route_partner[param_2] = (short)param_3;
  uVar1 = int_clamp(param_4,0xffffffff,0xf);
  *(char *)&cities[city].route_goods[param_2] = (char)uVar1;
  cities[city].flags = cities[city].flags | 0x20000;
  return;
}

/* 00440453 auto */
#define local_20 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(12)))
#define local_10 (*(iptr *)(frame_ + FRAME_OFF(16)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(24)))
void __cdecl city_add_trade_route(uptr city,uptr city2,iptr param_3)

{
  u8 uVar1;
  iptr city3;
  int iVar3;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_10 = 0; local_10 < (char)cities[city].trade_routes; local_10++) {
    if (((int)cities[city].route_partner[local_10] == city2) &&
       (*(char *)&cities[city].route_goods[local_10] == param_3)) {
      return;
    }
  }
  if ((char)cities[city].trade_routes < 3) {
    uVar1 = cities[city].trade_routes;
    cities[city].trade_routes++;
    city_set_trade_route_slot(city,(int)(char)uVar1,city2,param_3);
    city_calc_commodity_demand(city);
    city_calc_commodity_demand(city2);
  }
  else {
    local_1c = 9999;
    for (local_10 = 0; local_10 < (char)cities[city].trade_routes; local_10++) {
      if ((*(char *)&cities[city].route_goods[local_10] < '\0') && (param_3 < 0)) {
        return;
      }
      city3 = (iptr)cities[city].route_partner[local_10];
      local_8 = (int)cities[city3].base_trade;
      local_14 = map_road_connection((int)cities[city].owner,(int)cities[city].x,
                                    (int)cities[city].y,(int)cities[city3].x,(int)cities[city3].y
                                   );
      iVar3 = city_has_improvement(city,0x20);
      if (((iVar3 != 0) && (iVar3 = city_has_improvement(city3,0x20), iVar3 != 0)) && (local_14 < 2))
      {
        local_14 = 1;
      }
      if (local_14 != 0) {
        local_8 += (local_14 * local_8 >> 1);
      }
      if (cities[city].owner == cities[city3].owner) {
        local_8 = local_8 >> 1;
      }
      if (local_8 < local_1c) {
        local_1c = local_8;
        local_20 = local_10;
      }
    }
    if (local_1c <= cities[city2].base_trade) {
      city_set_trade_route_slot(city,local_20,city2,param_3);
      city_calc_commodity_demand(city);
      city_calc_commodity_demand(city2);
    }
  }
  return;
}
#undef local_20
#undef local_1c
#undef local_14
#undef local_10
#undef local_8

/* 004413d1 auto */
#define city_delete_busy (*(i32 *)((u8 *)&g.d_006ad8c8))
#define city_window_refresh_locked (*(int *)((u8 *)&g.d_006aa760))
#define game_loop_active (*(i8 *)((u8 *)&g.d_00628044))
#define net_city_deleted_ack (*(int *)((u8 *)&g.d_006c90c8))
#define unit (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_28 (*(uint *)(frame_ + FRAME_OFF(8)))
#define city3 (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_14 (*(byte *)(frame_ + FRAME_OFF(28)))
#define city2 (*(iptr *)(frame_ + FRAME_OFF(32)))
#define local_c (*(i8 *)(frame_ + FRAME_OFF(36)))
void __cdecl city_delete(uptr city,i32 param_2)

{
  char cVar1;
  int iVar2;
  int x2;
  int y2;
  iptr civ;
  uptr city4;
  int y;
  iptr x;
  int iVar8;
  uint uVar9;
  iptr iVar10;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((-1 < (int)city) && (cities[city].id != 0)) {
    city_delete_busy = 1;
    if ((game.multiplayer < 3) || (cVar1 = net_is_host(&net_session), cVar1 != '\0')) {
      iVar2 = city_window_refresh_locked;
      city_window_refresh_locked = 1;
      x2 = (int)cities[city].x;
      y2 = (int)cities[city].y;
      civ = (iptr)cities[city].owner;
      civs[civ].num_cities--;
      do {
        unit = (iptr)game.num_units;
        while( true ) {
          while( true ) {
            do {
              unit--;
              if (unit < 0) {
                cities[city].id = 0;
                if ((int)game.num_cities - 1U == city) {
                  game.num_cities--;
                }
                for (city2 = 0; city2 < game.num_cities; city2++) {
                  if (cities[city2].id != 0) {
                    unit = (iptr)(char)cities[city2].trade_routes;
                    while (unit = unit - 1, -1 < unit) {
                      if ((int)cities[city2].route_partner[unit] == city) {
                        city_remove_trade_route(city2,unit);
                      }
                    }
                  }
                }
                for (city2 = 0; city2 < 0x1c; city2++) {
                  if ((int)game.wonder_city[city2] == city) {
                    game.wonder_city[city2] = -2;
                  }
                }
                local_28 = 0;
                net_batch_begin();
                tile_set_improvements(x2,y2,2,0,1);
                for (city2 = 0; city2 < 0x2d; city2++) {
                  x = map_wrap_x((char)(&city_tile_dx_table)[city2] + x2);
                  y = (char)(&city_tile_dy_table)[city2] + y2;
                  iVar8 = map_in_bounds(x,y);
                  if ((iVar8 != 0) && (iVar8 = tile_is_ocean(x,y), iVar8 == 0)) {
                    iVar10 = 1;
                    uVar9 = tile_get_fertility(x,y);
                    tile_set_fertility(x,y,uVar9 | 8,iVar10);
                    if (city2 < 0x15) {
                      iVar8 = tile_radius_civ(x,y);
                      if (iVar8 == civ) {
                        tile_set_radius_civ(x,y,0,1);
                      }
                      y = tile_city_or_unit_owner(x,y);
                      if ((0 < y) && (y != civ)) {
                        local_14 = (byte)y;
                        local_28 = local_28 | 1 << (local_14 & 0x1f);
                      }
                    }
                  }
                }
                net_batch_flush();
                if (local_28 != 0) {
                  for (unit = tile_first_unit(x2,y2); -1 < unit;
                      unit = unit_next_in_stack(unit)) {
                    units[unit].visibility = units[unit].visibility | (byte)local_28;
                  }
                }
                for (city3 = 0; city3 < game.num_cities; city3++) {
                  if (cities[city3].id != 0) {
                    city_refresh_area_tiles(city3);
                  }
                }
                city_window_close_if_city((C_004083b0_4 *)&city_window,city);
                city_window_refresh_locked = iVar2;
                if (iVar2 == 0) {
                  city_window_refresh((FrameWindow *)&city_window);
                }
                if (((char)param_2 == '\0') && (2 < game.multiplayer)) {
                  net_send_state_diff(0xff,2,0,0,0);
                  net_send_message(0x89,0xff,city,0,0,0,0,0,0,0);
                  net_send_message(0x8a,0xff,0,0,0,0,0,0,0,0);
                  XD_FlushSendBuffer(5000);
                }
                city_delete_busy = 0;
                return;
              }
            } while ((units[unit].id == 0) || ((byte)units[unit].home_city != city));
            if (units[unit].type != '\t') break;
            units[unit].home_city = -1;
          }
          if (((((uint)game.human_players & 1 << (units[unit].owner & 0x1fU)) != 0) ||
              (city4 = city_at((int)units[unit].x,(int)units[unit].y),
              (int)city4 < 0)) || (city == city4)) goto LAB_004416ab;
          if ((unit_types[units[unit].type].role != 1) ||
             (y = unit_stack_count_role(unit,1), y != 1)) break;
          local_c = (i8)city4;
          units[unit].home_city = local_c;
        }
        cities[city4].flags = cities[city4].flags | 0x20;
LAB_004416ab:
        unit_destroy_redraw(unit,1);
      } while( true );
    }
    city_delete_busy = 0;
    net_city_deleted_ack = -2;
    net_send_message(0x39,0,city,0,0,0,0,0,0,0);
    iVar2 = timer_ticks();
    while ((net_city_deleted_ack == -2 && (x2 = timer_ticks(), x2 - iVar2 < 0xe10))) {
      net_process_messages((NetSession *)&net_session,1,1);
    }
    if (net_city_deleted_ack == -2) {
      dbg_log(ADDR(0x626330, ((u8 *)&g.d_00626330)));
      popup_game_with_sprite(ADDR(0x626360, ((u8 *)&g.d_00626360)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      game_loop_active = 0;
    }
    while ((net_msgq_priority_count != 0 || (net_msgq_normal_count != 0))) {
      net_process_messages((NetSession *)&net_session,1,0);
    }
  }
  return;
}
#undef city_delete_busy
#undef city_window_refresh_locked
#undef game_loop_active
#undef net_city_deleted_ack
#undef unit
#undef local_28
#undef city3
#undef local_14
#undef city2
#undef local_c

/* 00441a79 auto */
i32 __cdecl city_needed_size_improvement(iptr city)

{
  int iVar1;
  
  if (((int)(uint)cosmic.aqueduct_size <= (int)cities[city].size) &&
     (iVar1 = city_has_improvement(city,9), iVar1 == 0)) {
    return 9;
  }
  if (((int)(uint)cosmic.sewer_size <= (int)cities[city].size) &&
     (iVar1 = city_has_improvement(city,0x17), iVar1 == 0)) {
    return 0x17;
  }
  return 0;
}

/* 00441b11 auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define civ_turn_in_progress (*(int *)((u8 *)&g.d_0062c5b8))
#define improvement2 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_330 (*(int *)(frame_ + FRAME_OFF(8)))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(16)))
#define local_324 (*(iptr *)(frame_ + FRAME_OFF(20)))
#define local_320 (*(Dialog *)(frame_ + FRAME_OFF(24)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(780)))
#define local_28 (*(iptr *)(frame_ + FRAME_OFF(784)))
#define civ3 (*(int *)(frame_ + FRAME_OFF(788)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(792)))
#define city3 (*(iptr *)(frame_ + FRAME_OFF(796)))
#define local_18 (*(iptr *)(frame_ + FRAME_OFF(800)))
#define city2 (*(iptr *)(frame_ + FRAME_OFF(804)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(808)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(812)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(816)))
void __cdecl city_set_production(iptr city,int param_2)

{
  char *pcVar1;
  char cVar2;
  byte civ2;
  int civ;
  i32 uVar5;
  iptr iVar6;
  int iVar7;
  i8 frame_[FRAME_OFF(824)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_320,0x4000);
  local_8 = 0;
  cVar2 = cities[city].building;
  civ2 = cities[city].owner;
  civ = (int)(char)civ2;
  if ((-1 < cities[city].building) && (cities[city].building < '>')) {
    pcVar1 = (char *)(cities[city].building + ADDR(0x64c7f4, ((u8 *)&civs + 340)) + civ * 0x594);
    *pcVar1 = *pcVar1 - 1;
  }
  if (0x62 < param_2) {
    param_2 = city_choose_production(city,0,0);
  }
  if (param_2 < 99) {
    if (((1 << (civ2 & 0x1f) & (uint)game.human_players) != 0) && (civ_turn_in_progress == 0)) {
      uVar5 = city_shields_after_change(city,param_2);
      cities[city].shield_box = (i16)uVar5;
    }
    cities[city].building = (i8)param_2;
  }
  if ((cities[city].building != cVar2) && ((1 << (civ2 & 0x1f) & (uint)game.human_players) == 0)
     ) {
    if ((cities[city].building < -0x26) || (cVar2 < -0x26)) {
      local_330 = 0;
      local_2c = 0;
      for (city2 = 0; city2 < game.num_cities; city2++) {
        if (((cities[city2].id != 0) && (cities[city].owner == cities[city2].owner)) &&
           (city2 != city)) {
          if (cities[city2].building == cVar2) {
            local_330++;
          }
          if (cities[city].building == cities[city2].building) {
            local_2c++;
          }
        }
      }
    }
    if (cities[city].building < -0x26) {
      if (-0x27 < cVar2) {
        cities[city].shield_box = cities[city].shield_box / 2;
      }
      if (cities[city].building < 1) {
        improvement = ~(int)cities[city].building + 1;
      }
      else {
        improvement = (iptr)cities[city].building;
      }
      local_28 = improvement - 0x27;
      if (cVar2 < -0x26) {
        local_324 = -0x27 - cVar2;
      }
      else {
        local_324 = 0;
      }
      iVar6 = civ_name_plural(civ);
      text_set_string_arg(1,iVar6);
      if (local_2c == 0) {
        if ((cVar2 < -0x26) && ((local_330 == 0 || (game.wonder_city[local_324] != -1)))) {
          if (local_330 != 0) {
            for (city3 = 0; city3 < game.num_cities; city3++) {
              if (((cities[city3].id != 0) && (cities[city3].owner == civ)) &&
                 (cities[city3].building == cVar2)) {
                cities[city3].building = cities[city].building;
              }
            }
          }
          if (autoplay_active == 0) {
            if (cVar2 < 1) {
              improvement2 = ~(int)cVar2 + 1;
            }
            else {
              improvement2 = (iptr)cVar2;
            }
            text_set_label_arg(2,improvements[improvement2].name);
            text_set_label_arg(3,improvements[improvement].name);
            dialog_load_game_text(&local_320,ADDR(0x626380, ((u8 *)&g.d_00626380)));
            dialog_add_sprite
                      ((DialogOptionList *)&local_320,(iptr)(&improvement_icon_sprites + improvement * 0x3c),0,0);
            dialog_set_image_zoom((DialogWindowView *)&local_320,8);
            if (2 < game.multiplayer) {
              net_send_text_args(0x13,0xff,4,0,improvement,8);
            }
            dlg_show_modal(&local_320,0);
          }
        }
        else if ((((&wonder_notice_flags)[civ * 0x1c + local_28] & 1) == 0) &&
                ((&wonder_notice_flags)[civ * 0x1c + local_28] =
                      (&wonder_notice_flags)[civ * 0x1c + local_28] | 1, autoplay_active == 0)) {
          text_set_label_arg(2,improvements[improvement].name);
          dialog_load_game_text(&local_320,ADDR(0x626374, ((u8 *)&g.d_00626374)));
          dialog_add_sprite
                    ((DialogOptionList *)&local_320,(iptr)(&improvement_icon_sprites + improvement * 0x3c),0,0);
          dialog_set_image_zoom((DialogWindowView *)&local_320,8);
          if (2 < game.multiplayer) {
            net_send_text_args(0x12,0xff,3,0,improvement,8);
          }
          dlg_show_modal(&local_320,0);
        }
      }
      if ((cities[city].shield_box == 0) &&
         (local_18 = (improvement - 0x27) / 7, *(char *)&civs[civ].wonders_by_group[local_18] == '\0'
         )) {
        local_20 = 1;
        for (civ3 = 1; civ3 < 8; civ3++) {
          if ((1 << ((byte)civ3 & 0x1f) & (uint)game.human_players) != 0) {
            if ((local_20 == 0) || (*(char *)&civs[civ3].wonders_by_group[local_18] == '\0')) {
              local_20 = 0;
            }
            else {
              local_20 = 1;
            }
          }
        }
        if (local_20 != 0) {
          iVar7 = (uint)game.difficulty + (uint)civs[civ].wonders_by_group[local_18] * -2;
          if (iVar7 < 1) {
            iVar7 = 0;
          }
          cities[city].shield_box =
               (short)iVar7 * (ushort)improvements[improvement].cost + cities[city].shield_box;
        }
      }
    }
    else if ((cVar2 < -0x26) && (local_330 == 0)) {
      if (cVar2 < 1) {
        improvement = ~(int)cVar2 + 1;
      }
      else {
        improvement = (iptr)cVar2;
      }
      local_28 = improvement - 0x27;
      if (((game.wonder_city[improvement - 0x27] != city) &&
          (iVar7 = civ_has_wonder(civ,improvement - 0x27), iVar7 == 0)) &&
         ((((&wonder_notice_flags)[civ * 0x1c + local_28] & 2) == 0 &&
          ((&wonder_notice_flags)[civ * 0x1c + local_28] = (&wonder_notice_flags)[civ * 0x1c + local_28] | 2,
          autoplay_active == 0)))) {
        iVar6 = civ_name_plural(civ);
        text_set_string_arg(1,iVar6);
        text_set_label_arg(2,improvements[improvement].name);
        dialog_load_game_text(&local_320,ADDR(0x626390, ((u8 *)&g.d_00626390)));
        dialog_add_sprite
                  ((DialogOptionList *)&local_320,(iptr)(&improvement_icon_sprites + improvement * 0x3c),0,0);
        dialog_set_image_zoom((DialogWindowView *)&local_320,8);
        if (2 < game.multiplayer) {
          net_send_text_args(0x14,0xff,3,0,improvement,8);
        }
        dlg_show_modal(&local_320,0);
      }
    }
  }
  if ((-1 < cities[city].building) && (cities[city].building < '>')) {
    pcVar1 = (char *)(cities[city].building + ADDR(0x64c7f4, ((u8 *)&civs + 340)) + civ * 0x594);
    *pcVar1 = *pcVar1 + 1;
  }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_0044251d */ { dialog_dtor((Dialog *)((iptr)&local_320)); }
  return;
}
#undef autoplay_active
#undef civ_turn_in_progress
#undef improvement2
#undef local_330
#undef improvement
#undef local_324
#undef local_320
#undef local_2c
#undef local_28
#undef civ3
#undef local_20
#undef city3
#undef local_18
#undef city2
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0044263f auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
i32 __cdecl city_adjacent_to_body(iptr city,iptr param_2)

{
  iptr x;
  int y;
  int iVar3;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_2 < 0x3f) {
    for (local_8 = 0; local_8 < 8; local_8++) {
      x = map_wrap_x((int)cities[city].x + (int)(char)(&dir_dx_table)[local_8]);
      y = (int)cities[city].y + (int)(char)(&dir_dy_table)[local_8];
      iVar3 = map_in_bounds(x,y);
      if (((iVar3 != 0) && (iVar3 = tile_is_ocean(x,y), iVar3 != 0)) &&
         (y = tile_landmass(x,y), y == param_2)) {
        return 1;
      }
    }
  }
  return 0;
}
#undef local_8

/* 0044272d auto */
#define local_24 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_c (*(uptr *)(frame_ + FRAME_OFF(28)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(32)))
int __cdecl city_adjacent_sea_info(iptr city,int *param_2,uptr *param_3)

{
  short x2;
  short y2;
  iptr x;
  int y;
  int iVar5;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  local_20 = 0;
  x2 = cities[city].x;
  y2 = cities[city].y;
  for (local_c = 0; (int)local_c < 8; local_c++) {
    x = map_wrap_x((int)(char)(&dir_dx_table)[local_c] + (int)x2);
    y = (int)(char)(&dir_dy_table)[local_c] + (int)y2;
    iVar5 = map_in_bounds(x,y);
    if ((iVar5 != 0) && (iVar5 = tile_is_ocean(x,y), iVar5 != 0)) {
      local_20 = tile_landmass(x,y);
      local_24 = (int)*(short *)(&water_body_sizes + local_20 * 0x10);
      if (0x3e < local_20) {
        local_24 = 1;
      }
      if (local_8 <= local_24) {
        local_8 = local_24;
      }
      local_c += (2 - (local_c & 1));
    }
  }
  if (param_2 != (int *)0x0) {
    *param_2 = local_8;
  }
  if (param_3 != (uptr *)0x0) {
    *param_3 = local_c;
  }
  return local_20;
}
#undef local_24
#undef local_20
#undef local_c
#undef local_8

/* 004429af auto */
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(8)))
i32 __cdecl cities_share_ocean(iptr city,iptr city2)

{
  iptr x;
  int y;
  int iVar3;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = -1;
  local_8 = 0;
  while( true ) {
    if (7 < local_8) {
      return 0;
    }
    x = map_wrap_x((int)cities[city].x + (int)(char)(&dir_dx_table)[local_8]);
    y = (int)cities[city].y + (int)(char)(&dir_dy_table)[local_8];
    iVar3 = map_in_bounds(x,y);
    if ((((iVar3 != 0) && (iVar3 = tile_is_ocean(x,y), iVar3 != 0)) &&
        (y = tile_landmass(x,y), y != local_c)) &&
       (iVar3 = city_adjacent_to_body(city2,y), local_c = y, iVar3 != 0)) break;
    local_8++;
  }
  return 1;
}
#undef local_c
#undef local_8

/* 00447e53 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl city_down_arrow_sprite_global_init(void)

{
  city_down_arrow_sprite_static_init();
  city_down_arrow_sprite_reg_atexit();
  return;
}

/* 00447e6d auto */
void __cdecl city_down_arrow_sprite_static_init(void)

{
  sprite_init((Sprite *)&city_down_arrow_sprite);
  return;
}

/* 00447e87 auto */
void __cdecl city_down_arrow_sprite_reg_atexit(void)

{
  _atexit(city_down_arrow_sprite_static_dtor);
  return;
}

/* 00447ea4 auto */
void __cdecl city_down_arrow_sprite_static_dtor(void)

{
  sprite_destroy((Sprite *)&city_down_arrow_sprite);
  return;
}

/* 0044816e auto */
void __cdecl city_sprites_global_init(void)

{
  city_sprites_static_init();
  city_sprites_reg_atexit();
  return;
}

/* 00448188 auto */
void __cdecl city_sprites_static_init(void)

{
  FUN_005f2620(&city_sprites,0x3c,0x30,sprite_init,sprite_destroy);
  return;
}

/* 004481b0 auto */
void __cdecl city_sprites_reg_atexit(void)

{
  _atexit(city_sprites_static_dtor);
  return;
}

/* 004481cd auto */
void __cdecl city_sprites_static_dtor(void)

{
  FUN_005f2490(&city_sprites,0x3c,0x30,sprite_destroy);
  return;
}

/* 00448376 auto */
void __cdecl citizen_sprites_global_init(void)

{
  citizen_sprites_static_init();
  citizen_sprites_reg_atexit();
  return;
}

/* 00448390 auto */
void __cdecl citizen_sprites_static_init(void)

{
  FUN_005f2620(&citizen_sprites,0x3c,0x2c,sprite_init,sprite_destroy);
  return;
}

/* 004483b8 auto */
void __cdecl citizen_sprites_reg_atexit(void)

{
  _atexit(citizen_sprites_static_dtor);
  return;
}

/* 004483d5 auto */
void __cdecl citizen_sprites_static_dtor(void)

{
  FUN_005f2490(&citizen_sprites,0x3c,0x2c,sprite_destroy);
  return;
}

/* 004484fc auto */
void __cdecl tax_rate_icon_sprites_global_init(void)

{
  tax_rate_icon_sprites_static_init();
  tax_rate_icon_sprites_reg_atexit();
  return;
}

/* 00448516 auto */
void __cdecl tax_rate_icon_sprites_static_init(void)

{
  FUN_005f2620(&tax_rate_icon_sprites,0x3c,3,sprite_init,sprite_destroy);
  return;
}

/* 0044853e auto */
void __cdecl tax_rate_icon_sprites_reg_atexit(void)

{
  _atexit(tax_rate_icon_sprites_static_dtor);
  return;
}

/* 0044855b auto */
void __cdecl tax_rate_icon_sprites_static_dtor(void)

{
  FUN_005f2490(&tax_rate_icon_sprites,0x3c,3,sprite_destroy);
  return;
}

/* 00448600 auto */
void __cdecl lux_tax_sci_icon_sprites_global_init(void)

{
  lux_tax_sci_icon_sprites_static_init();
  lux_tax_sci_icon_sprites_reg_atexit();
  return;
}

/* 0044861a auto */
void __cdecl lux_tax_sci_icon_sprites_static_init(void)

{
  FUN_005f2620(&lux_tax_sci_icon_sprites,0x3c,3,sprite_init,sprite_destroy);
  return;
}

/* 00448642 auto */
void __cdecl lux_tax_sci_icon_sprites_reg_atexit(void)

{
  _atexit(lux_tax_sci_icon_sprites_static_dtor);
  return;
}

/* 0044865f auto */
void __cdecl lux_tax_sci_icon_sprites_static_dtor(void)

{
  FUN_005f2490(&lux_tax_sci_icon_sprites,0x3c,3,sprite_destroy);
  return;
}

/* 004486ed auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl unhappy_suppressed_icon_sprite_global_init(void)

{
  unhappy_suppressed_icon_sprite_static_init();
  unhappy_suppressed_icon_sprite_reg_atexit();
  return;
}

/* 00448707 auto */
void __cdecl unhappy_suppressed_icon_sprite_static_init(void)

{
  sprite_init((Sprite *)&unhappy_suppressed_icon_sprite);
  return;
}

/* 00448721 auto */
void __cdecl unhappy_suppressed_icon_sprite_reg_atexit(void)

{
  _atexit(unhappy_suppressed_icon_sprite_static_dtor);
  return;
}

/* 0044873e auto */
void __cdecl unhappy_suppressed_icon_sprite_static_dtor(void)

{
  sprite_destroy((Sprite *)&unhappy_suppressed_icon_sprite);
  return;
}

/* 00448949 auto */
void __cdecl improvement_icon_sprites_global_init(void)

{
  improvement_icon_sprites_static_init();
  improvement_icon_sprites_reg_atexit();
  return;
}

/* 00448963 auto */
void __cdecl improvement_icon_sprites_static_init(void)

{
  FUN_005f2620(&improvement_icon_sprites,0x3c,0x43,sprite_init,sprite_destroy);
  return;
}

/* 0044898b auto */
void __cdecl improvement_icon_sprites_reg_atexit(void)

{
  _atexit(improvement_icon_sprites_static_dtor);
  return;
}

/* 004489a8 auto */
void __cdecl improvement_icon_sprites_static_dtor(void)

{
  FUN_005f2490(&improvement_icon_sprites,0x3c,0x43,sprite_destroy);
  return;
}

/* 0044ac3e auto */
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
void __cdecl city_sprite_scan_flag_offset(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  *(i32 *)(&city_flag_x_offsets + param_3 * 4 + param_1 * 0x20 + param_2 * 8) = 0;
  *(i32 *)(&city_flag_y_offsets + param_3 * 4 + param_1 * 0x20 + param_2 * 8) = 0;
  for (local_c = 0; local_c < 0x40; local_c++) {
    iVar1 = surface_get_pixel
                      ((DibSurface *)&gfx_sheet_surface,local_c + param_4 - 1 + 1,param_5 - 1);
    if (iVar1 == 4) {
      *(int *)(&city_flag_x_offsets + param_3 * 4 + param_1 * 0x20 + param_2 * 8) = local_c - 1;
    }
  }
  for (local_14 = 0; local_14 < 0x30; local_14++) {
    iVar1 = surface_get_pixel
                      ((DibSurface *)&gfx_sheet_surface,param_4 - 1,local_14 + param_5 - 1 + 1);
    if (iVar1 == 4) {
      *(int *)(&city_flag_y_offsets + param_3 * 4 + param_1 * 0x20 + param_2 * 8) = local_14 - 0xf;
    }
  }
  return;
}
#undef local_14
#undef local_c

/* 0044ad47 auto */
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
void __cdecl city_sprite_scan_size_box_offset(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  *(i32 *)(&city_size_box_x_offsets + param_2 * 8 + param_1 * 0x20 + param_3 * 4) = 0;
  *(i32 *)(&city_label_y_offsets + param_2 * 8 + param_1 * 0x20 + param_3 * 4) = 0;
  for (local_c = 0; local_c < 0x40; local_c++) {
    iVar1 = surface_get_pixel
                      ((DibSurface *)&gfx_sheet_surface,local_c + param_4 - 1 + 1,param_5 - 1);
    if (iVar1 == 3) {
      *(int *)(&city_size_box_x_offsets + param_2 * 8 + param_1 * 0x20 + param_3 * 4) = local_c;
    }
  }
  for (local_14 = 0; local_14 < 0x30; local_14++) {
    iVar1 = surface_get_pixel
                      ((DibSurface *)&gfx_sheet_surface,param_4 - 1,local_14 + param_5 - 1 + 1);
    if (iVar1 == 3) {
      *(int *)(&city_label_y_offsets + param_2 * 8 + param_1 * 0x20 + param_3 * 4) = local_14;
    }
  }
  return;
}
#undef local_14
#undef local_c

/* 00453da0 auto */
#define civ (*(int *)(frame_ + FRAME_OFF(0)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
i32 __cdecl wonder_is_expired(iptr param_1)

{
  char cVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  cVar1 = wonder_expires[param_1];
  if (cVar1 < 0) {
    local_8 = 0;
  }
  else {
    for (civ = 1; civ < 8; civ++) {
      iVar2 = civ_has_advance(civ,(int)cVar1);
      if (iVar2 != 0) {
        local_8 = 1;
      }
    }
  }
  return local_8;
}
#undef civ
#undef local_8

/* 00453e18 auto */
int __cdecl wonder_get_city(iptr param_1)

{
  int iVar1;
  
  iVar1 = wonder_is_expired(param_1);
  if (iVar1 == 0) {
    iVar1 = (int)game.wonder_city[param_1];
  }
  else {
    iVar1 = -1;
  }
  return iVar1;
}

/* 00453edf auto */
int __cdecl wonder_get_owner(iptr param_1)

{
  iptr city;
  int civ;
  
  city = wonder_get_city(param_1);
  if (city < 0) {
    civ = -1;
  }
  else {
    civ = (int)cities[city].owner;
  }
  return civ;
}

/* 00454260 auto */
#define this2 (*(CityViewWindow * *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(16)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(24)))
void __cdecl cityview_open(uptr city)

{
  C_00408010_6f0 *this;
  int iVar1;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  this = operator_new(0x1cb4);
  local_8 = 0;
  if (this == (C_00408010_6f0 *)0x0) {
    this2 = (CityViewWindow *)0x0;
  }
  else {
    this2 = (CityViewWindow *)cityview_ctor(this);
  }
  local_8 = 0xffffffff;
  if (this2 != (CityViewWindow *)0x0) {
    iVar1 = cityview_load(this2,city);
    if (iVar1 != 0) {
      cityview_run_modal((Wnd *)this2);
    }
    if (this2 != (CityViewWindow *)0x0) {
      cityview_scalar_dtor(this2,1);
    }
  }
  return;
}
#undef this2
#undef local_10
#undef puStack_c
#undef local_8

/* 00454354 auto */
#define cityview_wnd (*(C_00408010_6f0 * *)((u8 *)&g.d_00626a04))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(8)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(16)))
C_00408010_6f0 * __thiscall cityview_ctor(C_00408010_6f0 *this)

{
  u8 *puVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  wnd_ctor((C_00408010_b8 *)this);
  local_8 = 0;
  surfwnd_ctor((SurfaceWindow *)&this->control_list);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  surface_ctor((DibSurface *)&this->ship_civ);
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  palette_init((GamePalette *)(this->pad_1e4 + 0x30));
  (*(i8 *)((char *)&local_8 + 0)) = 3;
  surface_ctor((DibSurface *)(this->pad_638 + 0x10));
  (*(i8 *)((char *)&local_8 + 0)) = 4;
  surface_ctor((DibSurface *)(this->pad_638 + 0x58));
  (*(i8 *)((char *)&local_8 + 0)) = 5;
  dll_handle_init((DllHandle *)&this->resource_dll);
  (*(i8 *)((char *)&local_8 + 0)) = 6;
  FUN_005f2620(this->pad_6dc,0x3c,0x3c,sprite_init,sprite_destroy);
  (*(i8 *)((char *)&local_8 + 0)) = 7;
  FUN_005f2620(this[3].pad_c8 + 0x44,0x3c,4,sprite_init,sprite_destroy)
  ;
  (*(i8 *)((char *)&local_8 + 0)) = 8;
  FUN_005f2620(this[3].pad_1e4 + 0x18,0x3c,4,sprite_init,sprite_destroy
              );
  (*(i8 *)((char *)&local_8 + 0)) = 9;
  FUN_005f2620(this[3].pad_1e4 + 0x108,0x3c,4,sprite_init,
               sprite_destroy);
  (*(i8 *)((char *)&local_8 + 0)) = 10;
  FUN_005f2620(this[3].pad_1e4 + 0x1f8,0x3c,4,sprite_init,
               sprite_destroy);
  (*(i8 *)((char *)&local_8 + 0)) = 0xb;
  surface_ctor((DibSurface *)(this[3].pad_1e4 + 0x2e8));
  (*(i8 *)((char *)&local_8 + 0)) = 0xc;
  font_init_empty((GameFont *)(this[4].pad_c8 + 0x20));
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),0xd);
  gfx_get_screen_rect(ADDR(0x64b0d0, ((u8 *)&g.d_0064b0d0)));
  cityview_scroll_x = (0x500 - screen_rect_right) / 2;
  mem_copy_src_dst(ADDR(0x61cce0, ((u8 *)&g.d_0061cce0)),(iptr)(this[3].pad_504 + 0x24),0x174);
  mem_copy_src_dst(ADDR(0x61ce58, ((u8 *)&g.d_0061ce58)),(iptr)(this[3].pad_638 + 100),0x120);
  cityview_wnd = this;
  for (local_14 = 0; local_14 < 0x3c; local_14++) {
    puVar1 = this[3].pad_10 + local_14 * 4 + 0xc;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
  }
  font_set_styled((GameFont *)(this[4].pad_c8 + 0x20),0,0x24,1);
  SetRect((LPRECT)(this[4].pad_c8 + 0x10),0,0,screen_rect_right,0x28);
  return this;
}
#undef cityview_wnd
#undef local_14
#undef local_10
#undef puStack_c
#undef local_8

/* 00454699 auto */
#define cityview_wnd (*(i32 *)((u8 *)&g.d_00626a04))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __thiscall cityview_dtor(void *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  (*(i32 *)((char *)&local_8 + 1)) = 0;
  (*(i8 *)((char *)&local_8 + 0)) = 0xd;
  cityview_wnd = 0;
  dll_handle_free((DllHandle *)((int)this + 0x6d8));
  (*(i8 *)((char *)&local_8 + 0)) = 0xc;
  /* inlined unwind funclet FUN_00454798 */ { font_destroy((GameFont *)(*(int *)((iptr)&this) + 0x1ca8)); }
  (*(i8 *)((char *)&local_8 + 0)) = 0xb;
  /* inlined unwind funclet FUN_004547a7 */ { surface_dtor((DibSurface *)(*(int *)((iptr)&this) + 0x199c)); }
  (*(i8 *)((char *)&local_8 + 0)) = 10;
  /* inlined unwind funclet FUN_004547b6 */ { FUN_005f2490(*(int *)((iptr)&this) + 0x18ac,0x3c,4,sprite_destroy); }
  (*(i8 *)((char *)&local_8 + 0)) = 9;
  /* inlined unwind funclet FUN_004547ce */ { FUN_005f2490(*(int *)((iptr)&this) + 0x17bc,0x3c,4,sprite_destroy); }
  (*(i8 *)((char *)&local_8 + 0)) = 8;
  /* inlined unwind funclet FUN_004547e6 */ { FUN_005f2490(*(int *)((iptr)&this) + 0x16cc,0x3c,4,sprite_destroy); }
  (*(i8 *)((char *)&local_8 + 0)) = 7;
  /* inlined unwind funclet FUN_004547fe */ { FUN_005f2490(*(int *)((iptr)&this) + 0x15dc,0x3c,4,sprite_destroy); }
  (*(i8 *)((char *)&local_8 + 0)) = 6;
  /* inlined unwind funclet FUN_00454816 */ { FUN_005f2490(*(int *)((iptr)&this) + 0x6dc,0x3c,0x3c,sprite_destroy); }
  (*(i8 *)((char *)&local_8 + 0)) = 5;
  /* inlined unwind funclet FUN_0045482e */ { dll_free((DllHandle *)(*(int *)((iptr)&this) + 0x6d8)); }
  (*(i8 *)((char *)&local_8 + 0)) = 4;
  /* inlined unwind funclet FUN_0045483d */ { surface_dtor((DibSurface *)(*(int *)((iptr)&this) + 0x690)); }
  (*(i8 *)((char *)&local_8 + 0)) = 3;
  /* inlined unwind funclet FUN_0045484c */ { surface_dtor((DibSurface *)(*(int *)((iptr)&this) + 0x648)); }
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  /* inlined unwind funclet FUN_0045485b */ { palette_destroy((GamePalette *)(*(int *)((iptr)&this) + 0x214)); }
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  /* inlined unwind funclet FUN_0045486a */ { surface_dtor((DibSurface *)(*(int *)((iptr)&this) + 0x1cc)); }
  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
  /* inlined unwind funclet FUN_00454879 */ { surfwnd_dtor((SurfaceWindow *)(*(int *)((iptr)&this) + 0xb8)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_00454888 */ { wnd_dtor(*(WndBase **)((iptr)&this)); }
  return;
}
#undef cityview_wnd
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004548a9 auto */
#define local_e4 (*(DibSurface *)(frame_ + FRAME_OFF(4)))
#define local_9c (*(int *)(frame_ + FRAME_OFF(76)))
#define local_98 (*(int *)(frame_ + FRAME_OFF(80)))
#define local_94 (*(int *)(frame_ + FRAME_OFF(84)))
#define local_90 (*(i8 (*)[128])(frame_ + FRAME_OFF(88)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(216)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(220)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(224)))
i32 __thiscall cityview_load(CityViewWindow *this,uptr city)

{
  int iVar1;
  u32 uVar2;
  i32 uVar3;
  i8 frame_[FRAME_OFF(232)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  surface_ctor(&local_e4);
  local_8 = 0;
  this->city_id = city;
  str_clear((iptr)local_90);
  str_append((iptr)local_90,ADDR(0x626a08, ((u8 *)&g.d_00626a08)));
  iVar1 = file_resolve_path((iptr)local_90);
  if (iVar1 == 0) {
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_00454e8b */ { surface_dtor((DibSurface *)((iptr)&local_e4)); }
    uVar3 = 0;
  }
  else {
    dll_handle_load((DllHandle *)&this->resource_dll,(iptr)local_90);
    cityview_classify_site(this);
    uVar2 = civ_city_art_era((int)cities[city].owner);
    this->art_era = uVar2;
    if (screen_rect_right < 0x500) {
      surface_create((DibSurface *)&this->ship_civ,screen_rect_right,0x1e0);
    }
    else {
      surface_create((DibSurface *)&this->ship_civ,0x500,0x1e0);
    }
    iVar1 = surface_load_gif_resource
                      ((DibSurface *)(this->pad_638 + 0x10),300,10,0xec,
                       (iptr)(this->pad_1e4 + 0x30));
    if (iVar1 == 0) {
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_00454e8b */ { surface_dtor((DibSurface *)((iptr)&local_e4)); }
      uVar3 = 0;
    }
    else {
      iVar1 = surface_load_gif_resource
                        ((DibSurface *)(this->pad_638 + 0x58),0x131,10,0xec,
                         (iptr)(this->pad_1e4 + 0x30));
      if (iVar1 == 0) {
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_00454e8b */ { surface_dtor((DibSurface *)((iptr)&local_e4)); }
        uVar3 = 0;
      }
      else {
        iVar1 = surface_load_gif_resource(&local_e4,0x136,10,0xec,(iptr)(this->pad_1e4 + 0x30));
        if (iVar1 == 0) {
          local_8 = 0xffffffff;
          /* inlined unwind funclet FUN_00454e8b */ { surface_dtor((DibSurface *)((iptr)&local_e4)); }
          uVar3 = 0;
        }
        else {
          local_94 = 1;
          local_9c = 1;
          for (local_98 = 0; local_98 < 4; local_98++) {
            sprite_grab_from_surface
                      ((Sprite *)(this->pad_1089 + local_98 * 0x3c + 0x733),(iptr)&local_e4,9
                       ,local_94,local_9c,0x9e,0x72);
            sprite_replace_color
                      ((Sprite *)(this->pad_1089 + local_98 * 0x3c + 0x733),7,9);
            local_94 += 0x9f;
          }
          local_94 = 1;
          local_9c = 0x74;
          iVar1 = civ_city_style_era((int)cities[city].owner);
          if (1 < iVar1) {
            local_9c += 0x73;
          }
          for (local_98 = 0; local_98 < 4; local_98++) {
            sprite_grab_from_surface
                      ((Sprite *)(this->pad_1089 + local_98 * 0x3c + 0x823),(iptr)&local_e4,9
                       ,local_94,local_9c,0x9e,0x72);
            sprite_replace_color
                      ((Sprite *)(this->pad_1089 + local_98 * 0x3c + 0x823),7,9);
            local_94 += 0x9f;
          }
          local_94 = 1;
          local_9c = 0x15a;
          for (local_98 = 0; local_98 < 4; local_98++) {
            sprite_grab_from_surface
                      ((Sprite *)(this->pad_1089 + local_98 * 0x3c + 0x553),(iptr)&local_e4,9
                       ,local_94,local_9c,0x7b,0x52);
            sprite_replace_color
                      ((Sprite *)(this->pad_1089 + local_98 * 0x3c + 0x553),7,9);
            local_94 += 0x7c;
          }
          local_94 = 1;
          local_9c = 0x1ad;
          iVar1 = civ_city_style_era((int)cities[city].owner);
          if (1 < iVar1) {
            local_9c += 0x53;
          }
          for (local_98 = 0; local_98 < 4; local_98++) {
            sprite_grab_from_surface
                      ((Sprite *)(this->pad_1089 + local_98 * 0x3c + 0x643),(iptr)&local_e4,9
                       ,local_94,local_9c,0x7b,0x52);
            sprite_replace_color
                      ((Sprite *)(this->pad_1089 + local_98 * 0x3c + 0x643),7,9);
            local_94 += 0x7c;
          }
          iVar1 = cityview_load_icon_surface((WndBase *)this);
          if (iVar1 == 0) {
            local_8 = 0xffffffff;
            /* inlined unwind funclet FUN_00454e8b */ { surface_dtor((DibSurface *)((iptr)&local_e4)); }
            uVar3 = 0;
          }
          else {
            iVar1 = cityview_create_windows(this);
            if (iVar1 == 0) {
              local_8 = 0xffffffff;
              /* inlined unwind funclet FUN_00454e8b */ { surface_dtor((DibSurface *)((iptr)&local_e4)); }
              uVar3 = 0;
            }
            else {
              iVar1 = cityview_layout_buildings(this);
              if (iVar1 == 0) {
                local_8 = 0xffffffff;
                /* inlined unwind funclet FUN_00454e8b */ { surface_dtor((DibSurface *)((iptr)&local_e4)); }
                uVar3 = 0;
              }
              else {
                cityview_draw_buildings(this);
                local_8 = 0xffffffff;
                /* inlined unwind funclet FUN_00454e8b */ { surface_dtor((DibSurface *)((iptr)&local_e4)); }
                uVar3 = 1;
              }
            }
          }
        }
      }
    }
  }
  return uVar3;
}
#undef local_e4
#undef local_9c
#undef local_98
#undef local_94
#undef local_90
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00454eb2 auto */
void __thiscall cityview_run_modal(Wnd *this)

{
  wnd_handle_show_raise((WndBase *)this);
  wnd_flush_paint();
  wnd_set_palette((WndBase *)this,(iptr)&this[2].field_7c);
  window_show((C_004083b0_4 *)&this->control_list);
  wnd_flush_paint();
  wnd_set_capture((WndBase *)(this[1].pad_10 + 0x24));
  if (2 < game.multiplayer) {
    wnd_set_modal_idle_callback((C_00408010_b8 *)(this[1].pad_10 + 0x24),ADDR(0x403585, net_modal_idle_poll));
  }
  wnd_run_modal_loop((C_00408010_b8 *)(this[1].pad_10 + 0x24));
  wnd_set_modal_idle_callback((C_00408010_b8 *)(this[1].pad_10 + 0x24),0);
  wnd_release_capture((WndBase *)(this[1].pad_10 + 0x24));
  wnd_hide((WndBase *)(this[1].pad_10 + 0x24));
  wnd_flush_paint();
  wnd_set_palette((WndBase *)this,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
  wnd_hide((WndBase *)this);
  wnd_flush_paint();
  return;
}

/* 00454f83 auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __thiscall cityview_classify_site(CityViewWindow *this)

{
  short x2;
  short y2;
  iptr x;
  int y;
  int iVar5;
  byte *pbVar6;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  x2 = cities[this->city_id].x;
  y2 = cities[this->city_id].y;
  if ((cities[this->city_id].flags & 0x80) == 0) {
    for (local_8 = 0; local_8 < 9; local_8++) {
      x = map_wrap_x((int)(char)(&dir_dx_table)[local_8] + (int)x2);
      y = (int)(char)(&dir_dy_table)[local_8] + (int)y2;
      iVar5 = map_in_bounds(x,y);
      if ((iVar5 != 0) && (pbVar6 = (byte *)tile_at(x,y), (*pbVar6 & 0x80) != 0)) {
        this->slot_count = 0x39;
        this->terrain_kind = 1;
        this->wonder_slots_left = 0x18;
        this->improvement_slots_left = 0x1b;
        return;
      }
    }
    this->slot_count = 0x3c;
    this->terrain_kind = 2;
    this->wonder_slots_left = 0x18;
    this->improvement_slots_left = 0x1f;
  }
  else {
    this->slot_count = 0x3c;
    this->terrain_kind = 0;
    this->wonder_slots_left = 0x18;
    this->improvement_slots_left = 0x1b;
  }
  return;
}
#undef local_8

/* 0045512b auto */
uint __thiscall cityview_load_icon_surface(WndBase *this)

{
  int iVar1;
  
  surface_create((DibSurface *)&this[0x199].field_c,0x20,0x20);
  iVar1 = surface_load_gif_resource((DibSurface *)&this[0x199].field_c,399,10,0x20,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
  return (uint)(iVar1 != 0);
}

/* 00455183 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
uint __thiscall cityview_create_windows(CityViewWindow *this)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  wnd_create_with_handlers
            ((WndBase *)this,ADDR(0x626a10, ((u8 *)&g.d_00626a10)),0x800,cityview_screen_rect,cityview_screen_rect_top,
             screen_rect_right - cityview_screen_rect,(cityview_screen_rect_bottom - cityview_screen_rect_top) + 5,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)),ADDR(0x6553d8, ((u8 *)&g.d_006553d8)));
  wnd_set_bg_color((WndBase *)this,0);
  wnd_create_with_surface
            ((DibSurface *)&this->control_list,ADDR(0x626a14, ((u8 *)&g.d_00626a14)),0x800,0,cityview_screen_rect_bottom - 0x1e0 >> 1,
             screen_rect_right - cityview_screen_rect,0x1e0,(iptr)(this->pad_1e4 + 0x30),(iptr)this);
  iVar1 = city_has_improvement(this->city_id,0x19);
  if (iVar1 == 0) {
    local_8 = civ_city_art_era((int)cities[this->city_id].owner);
  }
  else {
    local_8 = 3;
  }
  iVar1 = surface_load_gif_resource
                    ((DibSurface *)&this->ship_civ,this->terrain_kind * 5 + local_8 + 0x154,10,
                     0xec,(iptr)(this->pad_1e4 + 0x30));
  if (iVar1 != 0) {
    wnd_set_keydown_handler((C_00408130 *)(this->pad_c8 + 0x48),ADDR(0x40271b, cityview_on_key));
    wnd_set_lbuttonup_handler((C_00408130 *)(this->pad_c8 + 0x48),ADDR(0x402a77, cityview_on_lbuttonup));
    wnd_set_keydown_pre_handler((C_00456ee0 *)(this->pad_c8 + 0x48),ADDR(0x402e05, cityview_on_key_pre));
    wnd_set_mousemove_handler((WndHandlersMouseSetView *)(this->pad_c8 + 0x48),ADDR(0x403189, cityview_on_mousemove));
    cityview_redraw_scrolled(this);
  }
  return (uint)(iVar1 != 0);
}
#undef local_8

/* 00455314 auto */
#define local_c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(8)))
i32 __thiscall cityview_layout_buildings(CityViewWindow *this)

{
  u32 uVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  this->houses_left = (int)cities[this->city_id].size + 2;
  rng_set_seed(cities[this->city_id].x * 0x100 + (int)cities[this->city_id].y +
                     (uint)map.seed);
  for (local_8 = 1; local_8 < 0x23; local_8++) {
    this->field_1c8c = 0;
    uVar1 = this->terrain_kind;
    if (uVar1 == 0) {
      switch(local_8) {
      case 8:
        this->field_1c8c = 1;
        local_c = 0x35;
        break;
      default:
        local_c = cityview_take_improvement_slot((ThroneRoomWindow *)this);
joined_r0x00455451:
        if (local_c == -1) goto LAB_0045539c;
        break;
      case 0x1c:
        local_c = 0x23;
        break;
      case 0x1e:
        this->field_1c8c = 1;
        local_c = 0x36;
        break;
      case 0x1f:
        this->field_1c8c = 1;
        local_c = 0x39;
        break;
      case 0x22:
        this->field_1c8c = 1;
        local_c = 0x37;
      }
LAB_00455628:
      iVar2 = city_has_improvement(this->city_id,local_8);
      if (iVar2 == 0) {
        if (this->houses_left == 0) {
          cityview_place_empty_lot(this,local_c);
        }
        else {
          cityview_place_small_house(this,local_c);
        }
      }
      else {
        cityview_place_improvement((WndBase *)this,local_c,local_8);
        rand_range(0,0);
      }
    }
    else {
      if (uVar1 != 1) {
        if (uVar1 == 2) {
          switch(local_8) {
          case 8:
            this->field_1c8c = 1;
            local_c = 0x34;
            break;
          default:
            local_c = cityview_take_improvement_slot((ThroneRoomWindow *)this);
            goto joined_r0x00455451;
          case 0x1c:
          case 0x1e:
          case 0x1f:
          case 0x22:
            goto LAB_0045539c;
          }
        }
        goto LAB_00455628;
      }
      switch(local_8) {
      case 8:
        this->field_1c8c = 1;
        local_c = 0x35;
        goto LAB_00455628;
      default:
        local_c = cityview_take_improvement_slot((ThroneRoomWindow *)this);
        if (local_c != -1) goto LAB_00455628;
        break;
      case 0x1c:
      case 0x1e:
      case 0x1f:
      case 0x22: ;
      }
    }
LAB_0045539c: ;
  }
  while (iVar2 = cityview_take_improvement_slot((ThroneRoomWindow *)this), iVar2 != -1) {
    if (this->houses_left == 0) {
      cityview_place_empty_lot(this,iVar2);
    }
    else {
      cityview_place_small_house(this,iVar2);
    }
  }
  this->houses_left = (int)cities[this->city_id].size + 2;
  local_8 = 0;
  local_c = -1;
  do {
    if (0x1b < local_8) {
      while (iVar2 = cityview_take_wonder_slot((ThroneRoomWindow *)this), iVar2 != -1) {
        if (this->houses_left == 0) {
          cityview_place_large_empty_lot(this,iVar2);
        }
        else {
          cityview_place_large_house(this,iVar2);
        }
      }
      surface_release((DibSurface *)(this->pad_638 + 0x58));
      surface_release((DibSurface *)(this->pad_638 + 0x10));
      return 1;
    }
    this->field_1c8c = 0;
    uVar1 = this->terrain_kind;
    if (uVar1 != 0) {
      if (uVar1 == 1) {
        switch(local_8) {
        case 2:
          this->field_1c8c = 1;
          local_c = 0x36;
          break;
        case 3:
          this->field_1c8c = 1;
          local_c = 4;
          break;
        default:
          local_c = cityview_take_wonder_slot((ThroneRoomWindow *)this);
          goto joined_r0x004557ba;
        case 6:
          this->field_1c8c = 1;
          local_c = 1;
          break;
        case 0x13:
          this->field_1c8c = 1;
          local_c = 0x37;
        }
      }
      else if (uVar1 == 2) {
        switch(local_8) {
        case 2:
          this->field_1c8c = 1;
          local_c = 0x36;
          break;
        case 3:
          this->field_1c8c = 1;
          local_c = 3;
          break;
        default:
          local_c = cityview_take_wonder_slot((ThroneRoomWindow *)this);
          if (local_c == -1) goto LAB_00455711;
          break;
        case 6:
          this->field_1c8c = 1;
          local_c = 0;
          break;
        case 0x13:
          this->field_1c8c = 1;
          local_c = 0x39;
        }
      }
      goto LAB_004559fe;
    }
    switch(local_8) {
    case 2:
      this->field_1c8c = 1;
      local_c = 0x3a;
      break;
    case 3:
      this->field_1c8c = 1;
      local_c = 0x3b;
      break;
    default:
      local_c = cityview_take_wonder_slot((ThroneRoomWindow *)this);
joined_r0x004557ba:
      if (local_c != -1) break;
      goto LAB_00455711;
    case 6:
      this->field_1c8c = 1;
      local_c = 1;
      break;
    case 0x13:
      this->field_1c8c = 1;
      local_c = 0x38;
    }
LAB_004559fe:
    if ((int)game.wonder_city[local_8] == this->city_id) {
      cityview_place_wonder((WndBase *)this,local_c,local_8);
      rand_range(0,0);
    }
    else if (this->houses_left == 0) {
      cityview_place_large_empty_lot(this,local_c);
    }
    else {
      cityview_place_large_house(this,local_c);
    }
LAB_00455711:
    local_8++;
  } while( true );
}
#undef local_c
#undef local_8

/* 00455add auto */
#define local_18 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
void __thiscall cityview_draw_buildings(CityViewWindow *this)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; local_8 < (int)this->slot_count; local_8++) {
    if (*(int *)(this->pad_1089 + local_8 * 4 + 0x463) != 0) {
      sprite_draw
                (*(Sprite **)(this->pad_1089 + local_8 * 4 + 0x463),(iptr)local_18,
                 (iptr)&this->ship_civ,
                 *(i32 *)(&cityview_slot_x_table + local_8 * 8 + this->terrain_kind * 0x1e0),
                 *(i32 *)(&cityview_slot_y_table + local_8 * 8 + this->terrain_kind * 0x1e0));
    }
  }
  cityview_redraw_scrolled(this);
  return;
}
#undef local_18
#undef local_8

/* 00455b8e auto */
i32 __thiscall cityview_take_wonder_slot(ThroneRoomWindow *this)

{
  i32 uVar1;
  int iVar2;
  
  if (this->wonder_slots_left == 0) {
    uVar1 = 0xffffffff;
  }
  else {
    iVar2 = this->wonder_slots_left * 3 - 3;
    iVar2 = rand_range((int)(iVar2 + (iVar2 >> 0x1f & 3U)) >> 2,this->wonder_slots_left - 1);
    uVar1 = *(i32 *)(this->pad_19f8 + this->terrain_kind * 0x60 + iVar2 * 4 + 0x174);
    this->wonder_slots_left--;
    *(i32 *)(this->pad_19f8 + this->terrain_kind * 0x60 + iVar2 * 4 + 0x174) =
         *(i32 *)(this->pad_19f8 + this->terrain_kind * 0x60 + this->wonder_slots_left * 4 + 0x174);
  }
  return uVar1;
}

/* 00455c5d auto */
i32 __thiscall cityview_take_improvement_slot(ThroneRoomWindow *this)

{
  i32 uVar1;
  int iVar2;
  
  if (this->improvement_slots_left == 0) {
    uVar1 = 0xffffffff;
  }
  else {
    iVar2 = this->improvement_slots_left * 3 - 3;
    iVar2 = rand_range((int)(iVar2 + (iVar2 >> 0x1f & 3U)) >> 2,this->improvement_slots_left - 1);
    uVar1 = *(i32 *)(this->pad_19f8 + iVar2 * 4 + this->terrain_kind * 0x7c);
    this->improvement_slots_left--;
    *(i32 *)(this->pad_19f8 + iVar2 * 4 + this->terrain_kind * 0x7c) =
         *(i32 *)(this->pad_19f8 + this->terrain_kind * 0x7c + this->improvement_slots_left * 4);
  }
  return uVar1;
}

/* 00455d38 auto */
void __thiscall cityview_place_improvement(WndBase *this,iptr param_1,iptr param_2)

{
  if (-1 < param_1) {
    sprite_grab_from_surface
              ((Sprite *)(param_1 * 0x3c + 0x6dc + (int)this),(iptr)&this[100].field_8,9,
               *(i32 *)(&cityview_improvement_art_x + (param_2 - 1) * 0x10),
               *(i32 *)(&cityview_improvement_art_y + (param_2 - 1) * 0x10),
               *(i32 *)(&cityview_improvement_art_w + (param_2 - 1) * 0x10),
               *(i32 *)(&cityview_improvement_art_h + (param_2 - 1) * 0x10));
    sprite_replace_color((Sprite *)(param_1 * 0x3c + 0x6dc + (int)this),7,9);
    (&this[0x14e].field_c)[param_1] = (int)this + param_1 * 0x3c + 0x6dc;
  }
  return;
}

/* 00455dfd auto */
void __thiscall cityview_place_wonder(WndBase *this,iptr param_1,iptr param_2)

{
  if (-1 < param_1) {
    sprite_grab_from_surface
              ((Sprite *)(param_1 * 0x3c + 0x6dc + (int)this),(iptr)(this + 0x69),9,
               *(i32 *)(&cityview_wonder_art_x + param_2 * 0x10),
               *(i32 *)(&cityview_wonder_art_y + param_2 * 0x10),
               *(i32 *)(&cityview_wonder_art_w + param_2 * 0x10),
               *(i32 *)(&cityview_wonder_art_h + param_2 * 0x10));
    sprite_replace_color((Sprite *)(param_1 * 0x3c + 0x6dc + (int)this),7,9);
    (&this[0x14e].field_c)[param_1] = (int)this + param_1 * 0x3c + 0x6dc;
  }
  return;
}

/* 00455ebe auto */
void __thiscall cityview_place_large_house(CityViewWindow *this,iptr param_1)

{
  int iVar1;
  
  iVar1 = rand_range(0,3);
  if ((this->field_1c8c == 0) && (this->houses_left = this->houses_left - 1, param_1 != -1)) {
    *(u8 **)(this->pad_1089 + param_1 * 4 + 0x463) = this->pad_1089 + iVar1 * 0x3c + 0x823;
  }
  return;
}

/* 00455f2e auto */
void __thiscall cityview_place_small_house(CityViewWindow *this,iptr param_1)

{
  int iVar1;
  
  iVar1 = rand_range(0,3);
  if ((this->field_1c8c == 0) && (this->houses_left = this->houses_left - 1, param_1 != -1)) {
    *(u8 **)(this->pad_1089 + param_1 * 4 + 0x463) = this->pad_1089 + iVar1 * 0x3c + 0x643;
  }
  return;
}

/* 00455f9e auto */
void __thiscall cityview_place_large_empty_lot(CityViewWindow *this,iptr param_1)

{
  int iVar1;
  
  iVar1 = rand_range(0,3);
  if ((this->field_1c8c == 0) && (param_1 != -1)) {
    *(u8 **)(this->pad_1089 + param_1 * 4 + 0x463) = this->pad_1089 + iVar1 * 0x3c + 0x733;
  }
  return;
}

/* 00456005 auto */
void __thiscall cityview_place_empty_lot(CityViewWindow *this,iptr param_1)

{
  int iVar1;
  
  iVar1 = rand_range(0,3);
  if ((this->field_1c8c == 0) && (param_1 != -1)) {
    *(u8 **)(this->pad_1089 + param_1 * 4 + 0x463) = this->pad_1089 + iVar1 * 0x3c + 0x553;
  }
  return;
}

/* 0045606c auto */
#define local_24 (*(tagRECT *)(frame_ + FRAME_OFF(4)))
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(20)))
void __thiscall cityview_redraw_scrolled(CityViewWindow *this)

{
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  SetRect(&local_24,0,0,screen_rect_right,0x1e0);
  SetRect(&local_14,cityview_scroll_x,0,screen_rect_right + cityview_scroll_x,0x1e0);
  surface_blit
            ((DibSurface *)&this->ship_civ,(iptr)&this->control_list,(iptr)&local_14,(iptr)&local_24
            );
  cityview_draw_title(this);
  wnd_repaint((SurfaceWindow *)&this->control_list);
  wnd_flush_paint();
  return;
}
#undef local_24
#undef local_14

/* 004560f8 auto */
void __thiscall cityview_draw_title(CityViewWindow *this)

{
  text_clear();
  text_append(this->city_id * 0x58 + ADDR(0x64f360, ((u8 *)&cities + 32)));
  text_append_colon();
  text_append_space();
  text_append_year((int)game.year);
  gfx_set_text_color_index(10);
  OffsetRect((LPRECT)this->pad_1c98,1,1);
  surface_draw_text_in_rect
            ((DibSurface *)&this->control_list,(iptr)(this->pad_1c98 + 0x10),ADDR(0x679640, ((u8 *)&g.d_00679640)),
             (iptr)this->pad_1c98,0);
  gfx_set_text_color_index(0x1a);
  OffsetRect((LPRECT)this->pad_1c98,-1,-1);
  surface_draw_text_in_rect
            ((DibSurface *)&this->control_list,(iptr)(this->pad_1c98 + 0x10),ADDR(0x679640, ((u8 *)&g.d_00679640)),
             (iptr)this->pad_1c98,0);
  return;
}

/* 004561d9 auto */
#define cityview_wnd (*(CityViewWindow * *)((u8 *)&g.d_00626a04))
void __cdecl cityview_on_mousemove(int param_1)

{
  if (screen_rect_right * 7 >> 3 < param_1) {
    cityview_scroll_right(cityview_wnd);
  }
  if (param_1 < screen_rect_right >> 3) {
    cityview_scroll_left(cityview_wnd);
  }
  return;
}
#undef cityview_wnd

/* 00456228 auto */
#define cityview_wnd (*(C_00408010_b8 * *)((u8 *)&g.d_00626a04))
void __cdecl cityview_on_key(int param_1)

{
  if (param_1 == 0xd2) {
    wnd_end_modal_loop(cityview_wnd);
  }
  return;
}
#undef cityview_wnd

/* 0045626d auto */
#define cityview_wnd (*(int *)((u8 *)&g.d_00626a04))
void __cdecl cityview_on_lbuttonup(void)

{
  if (cityview_wnd != 0) {
    wnd_end_modal_loop((C_00408010_b8 *)(cityview_wnd + 0x100));
  }
  return;
}
#undef cityview_wnd

/* 0045629b auto */
#define cityview_wnd (*(CityViewWindow * *)((u8 *)&g.d_00626a04))
void __cdecl cityview_on_key_pre(i32 param_1)

{
  switch(param_1) {
  case 0xa4:
  case 0xc2:
    if (screen_rect_right < 0x500) {
      cityview_scroll_left(cityview_wnd);
    }
    break;
  case 0xa6:
  case 0xc3:
    if (screen_rect_right < 0x500) {
      cityview_scroll_right(cityview_wnd);
    }
    break;
  case 0xd0:
  case 0xd1:
  case 0xd2:
    if (cityview_wnd != (CityViewWindow *)0x0) {
      wnd_end_modal_loop((C_00408010_b8 *)(cityview_wnd->pad_c8 + 0x38));
    }
  }
  return;
}
#undef cityview_wnd

/* 0045638b auto */
#define local_30 (*(tagPOINT *)(frame_ + FRAME_OFF(0)))
#define local_28 (*(tagRECT *)(frame_ + FRAME_OFF(8)))
#define local_18 (*(tagRECT *)(frame_ + FRAME_OFF(24)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(40)))
void __thiscall cityview_scroll_right(CityViewWindow *this)

{
  SHORT SVar1;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 4;
  SetRect(&local_28,0,0,screen_rect_right,0x1e0);
  SetRect(&local_18,cityview_scroll_x,0,screen_rect_right + cityview_scroll_x,0x1e0);
  GetCursorPos(&local_30);
  while( true ) {
    if (0x500 - screen_rect_right < cityview_scroll_x) {
      return;
    }
    SVar1 = GetAsyncKeyState(0x66);
    if ((((char)((ushort)SVar1 >> 8) == '\0') &&
        (SVar1 = GetAsyncKeyState(0x27), (char)((ushort)SVar1 >> 8) == '\0')) &&
       (local_30.x <= screen_rect_right * 7 >> 3)) break;
    surface_blit
              ((DibSurface *)&this->ship_civ,(iptr)&this->control_list,(iptr)&local_18,
               (iptr)&local_28);
    cityview_draw_title(this);
    wnd_blit_surface((DibSurface *)&this->control_list);
    cityview_scroll_x += local_8;
    OffsetRect(&local_18,local_8,0);
    GetCursorPos(&local_30);
  }
  return;
}
#undef local_30
#undef local_28
#undef local_18
#undef local_8

/* 004564a8 auto */
#define local_30 (*(tagPOINT *)(frame_ + FRAME_OFF(0)))
#define local_28 (*(tagRECT *)(frame_ + FRAME_OFF(8)))
#define local_18 (*(tagRECT *)(frame_ + FRAME_OFF(24)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(40)))
void __thiscall cityview_scroll_left(CityViewWindow *this)

{
  SHORT SVar1;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 4;
  SetRect(&local_28,0,0,screen_rect_right,0x1e0);
  SetRect(&local_18,cityview_scroll_x,0,screen_rect_right + cityview_scroll_x,0x1e0);
  GetCursorPos(&local_30);
  while( true ) {
    if (cityview_scroll_x < 0) {
      return;
    }
    SVar1 = GetAsyncKeyState(100);
    if ((((char)((ushort)SVar1 >> 8) == '\0') &&
        (SVar1 = GetAsyncKeyState(0x25), (char)((ushort)SVar1 >> 8) == '\0')) &&
       (screen_rect_right >> 3 <= local_30.x)) break;
    surface_blit
              ((DibSurface *)&this->ship_civ,(iptr)&this->control_list,(iptr)&local_18,
               (iptr)&local_28);
    cityview_draw_title(this);
    wnd_blit_surface((DibSurface *)&this->control_list);
    cityview_scroll_x -= local_8;
    OffsetRect(&local_18,-local_8,0);
    GetCursorPos(&local_30);
  }
  return;
}
#undef local_30
#undef local_28
#undef local_18
#undef local_8

/* 00456e90 auto */
void * __thiscall cityview_scalar_dtor(void *this,uint param_1)

{
  cityview_dtor(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 00490560 auto */
/* Library Function - Single Match
    public: int __thiscall CSplitterWnd::IsTracking(void)
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall citywnd_get_city(C_004083b0_4 *this)

{
  return this[0x567].field_0;
}

/* 00498d40 auto */
#define citypref_no_defend (*(i32 *)((u8 *)&g.d_0062ccc4))
#define text_token_buf (*(i8 *)((u8 *)&g.d_00673e10))
#define local_10 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(4)))
void __cdecl city_load_citypref(void)

{
  int iVar1;
  char *_Str1;
  char *_Str2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  citypref_count = 0;
  iVar1 = text_open_section(ADDR(0x62ccd4, ((u8 *)&g.d_0062ccd4)),ADDR(0x62ccc8, ((u8 *)&g.d_0062ccc8)));
  if (iVar1 == 0) {
    citypref_no_defend = 1;
  }
  text_close_file();
  iVar1 = text_open_section(ADDR(0x62ccf0, ((u8 *)&g.d_0062ccf0)),ADDR(0x62cce4, ((u8 *)&g.d_0062cce4)));
  if (iVar1 == 0) {
    do {
      iVar1 = text_read_line(1);
      if (iVar1 == 0) break;
      text_next_token();
      local_10 = -1;
      for (improvement = 1; improvement < 0x27; improvement++) {
        _Str2 = &text_token_buf;
        _Str1 = (char *)label_string(improvements[improvement].name);
        iVar1 = __strcmpi(_Str1,_Str2);
        if (iVar1 == 0) {
          local_10 = improvement;
          break;
        }
      }
      if (0 < local_10) {
        (&citypref_improvements)[citypref_count] = local_10;
        citypref_count++;
      }
    } while (citypref_count < 0x20 && 0 < local_10);
    text_close_file();
  }
  return;
}
#undef citypref_no_defend
#undef text_token_buf
#undef local_10
#undef improvement

/* 00498e8b auto */
#define city_aggressive_units (*(uint *)((u8 *)&g.d_006a65e4))
#define city_happy_count (*(int *)((u8 *)&g.d_006a6550))
#define city_shield_rows (*(int *)((u8 *)&g.d_006a657c))
#define city_shield_support (*(int *)((u8 *)&g.d_006a6568))
#define city_support_unit_count (*(int *)((u8 *)&g.d_006a660c))
#define city_total_shields (*(int *)((u8 *)&g.d_006a65cc))
#define city_total_trade (*(int *)((u8 *)&g.d_006a65d0))
#define city_trade_corruption (*(int *)((u8 *)&g.d_006a6580))
#define city_unhappy_count (*(int *)((u8 *)&g.d_006a65a8))
#define city_yield_totals (*(int *)((u8 *)&g.d_006a65c8))
#define citypref_no_defend (*(int *)((u8 *)&g.d_0062ccc4))
#define settler_food_cost (*(int *)((u8 *)&g.d_006a6608))
#define local_380 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_378 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_374 (*(int *)(frame_ + FRAME_OFF(12)))
#define local_370 (*(int *)(frame_ + FRAME_OFF(16)))
#define aiStack_364 (*(int (*)[62])(frame_ + FRAME_OFF(28)))
#define local_26c (*(int *)(frame_ + FRAME_OFF(276)))
#define local_268 (*(int *)(frame_ + FRAME_OFF(280)))
#define local_264 (*(int *)(frame_ + FRAME_OFF(284)))
#define local_260 (*(int *)(frame_ + FRAME_OFF(288)))
#define local_25c (*(int *)(frame_ + FRAME_OFF(292)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(296)))
#define local_254 (*(iptr *)(frame_ + FRAME_OFF(300)))
#define local_250 (*(int *)(frame_ + FRAME_OFF(304)))
#define local_24c (*(int *)(frame_ + FRAME_OFF(308)))
#define local_248 (*(int *)(frame_ + FRAME_OFF(312)))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(316)))
#define local_240 (*(iptr *)(frame_ + FRAME_OFF(320)))
#define local_23c (*(int *)(frame_ + FRAME_OFF(324)))
#define local_238 (*(int *)(frame_ + FRAME_OFF(328)))
#define local_234 (*(int *)(frame_ + FRAME_OFF(332)))
#define local_230 (*(int *)(frame_ + FRAME_OFF(336)))
#define local_22c (*(int *)(frame_ + FRAME_OFF(340)))
#define civ3 (*(iptr *)(frame_ + FRAME_OFF(344)))
#define city2 (*(iptr *)(frame_ + FRAME_OFF(348)))
#define local_220 (*(int *)(frame_ + FRAME_OFF(352)))
#define local_21c (*(int (*)[62])(frame_ + FRAME_OFF(356)))
#define local_124 (*(int *)(frame_ + FRAME_OFF(604)))
#define local_120 (*(int *)(frame_ + FRAME_OFF(608)))
#define local_11c (*(int *)(frame_ + FRAME_OFF(612)))
#define local_118 (*(iptr *)(frame_ + FRAME_OFF(616)))
#define local_114 (*(int *)(frame_ + FRAME_OFF(620)))
#define local_110 (*(iptr *)(frame_ + FRAME_OFF(624)))
#define local_10c (*(int *)(frame_ + FRAME_OFF(628)))
#define local_108 (*(uint *)(frame_ + FRAME_OFF(632)))
#define local_104 (*(int *)(frame_ + FRAME_OFF(636)))
#define local_100 (*(int *)(frame_ + FRAME_OFF(640)))
#define local_fc (*(iptr *)(frame_ + FRAME_OFF(644)))
#define local_f8 (*(uint *)(frame_ + FRAME_OFF(648)))
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(652)))
#define local_f0 (*(int *)(frame_ + FRAME_OFF(656)))
#define y2 (*(int *)(frame_ + FRAME_OFF(660)))
#define local_e8 (*(uint *)(frame_ + FRAME_OFF(664)))
#define local_e4 (*(int *)(frame_ + FRAME_OFF(668)))
#define local_e0 (*(int *)(frame_ + FRAME_OFF(672)))
#define x2 (*(iptr *)(frame_ + FRAME_OFF(676)))
#define local_d8 (*(int *)(frame_ + FRAME_OFF(680)))
#define local_d4 (*(int *)(frame_ + FRAME_OFF(684)))
#define local_d0 (*(uint *)(frame_ + FRAME_OFF(688)))
#define auStack_cc (*(i8 (*)[28])(frame_ + FRAME_OFF(692)))
#define local_b0 (*(uint *)(frame_ + FRAME_OFF(720)))
#define local_ac (*(int *)(frame_ + FRAME_OFF(724)))
#define local_a8 (*(int *)(frame_ + FRAME_OFF(728)))
#define local_a4 (*(int *)(frame_ + FRAME_OFF(732)))
#define local_a0 (*(iptr *)(frame_ + FRAME_OFF(736)))
#define local_9c (*(int *)(frame_ + FRAME_OFF(740)))
#define local_98 (*(int *)(frame_ + FRAME_OFF(744)))
#define local_94 (*(int *)(frame_ + FRAME_OFF(748)))
#define local_90 (*(uint *)(frame_ + FRAME_OFF(752)))
#define local_8c (*(int *)(frame_ + FRAME_OFF(756)))
#define local_88 (*(int *)(frame_ + FRAME_OFF(760)))
#define unit3 (*(iptr *)(frame_ + FRAME_OFF(764)))
#define local_80 (*(int *)(frame_ + FRAME_OFF(768)))
#define terrain2 (*(uptr *)(frame_ + FRAME_OFF(772)))
#define local_78 (*(int *)(frame_ + FRAME_OFF(776)))
#define local_74 (*(iptr *)(frame_ + FRAME_OFF(780)))
#define civ2 (*(uptr *)(frame_ + FRAME_OFF(784)))
#define local_6c (*(int *)(frame_ + FRAME_OFF(788)))
#define local_68 (*(int *)(frame_ + FRAME_OFF(792)))
#define local_64 (*(int *)(frame_ + FRAME_OFF(796)))
#define local_60 (*(int *)(frame_ + FRAME_OFF(800)))
#define local_5c (*(iptr *)(frame_ + FRAME_OFF(804)))
#define local_58 (*(iptr *)(frame_ + FRAME_OFF(808)))
#define local_54 (*(int *)(frame_ + FRAME_OFF(812)))
#define unit_type2 (*(iptr *)(frame_ + FRAME_OFF(816)))
#define local_4c (*(int *)(frame_ + FRAME_OFF(820)))
#define local_48 (*(int *)(frame_ + FRAME_OFF(824)))
#define civ4 (*(uptr *)(frame_ + FRAME_OFF(828)))
#define local_40 (*(int *)(frame_ + FRAME_OFF(832)))
#define local_3c (*(int *)(frame_ + FRAME_OFF(836)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(840)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(844)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(848)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(852)))
#define local_28 (*(iptr *)(frame_ + FRAME_OFF(856)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(860)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(864)))
#define local_1c (*(uint *)(frame_ + FRAME_OFF(868)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(872)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(876)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(880)))
#define local_c (*(int *)(frame_ + FRAME_OFF(884)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(888)))
/* WARNING: Type propagation algorithm not settling */

iptr __cdecl city_choose_production(iptr city,iptr param_2,iptr param_3)

{
  byte civ5;
  char cVar2;
  iptr iVar3;
  byte bVar4;
  uptr civ;
  iptr iVar5;
  iptr iVar4;
  int iVar6;
  i32 uVar7;
  uint uVar8;
  byte *pbVar9;
  int iVar10;
  iptr unit2;
  i8 frame_[FRAME_OFF(896)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_100 = 0;
  if (param_2 != 0) {
    *(i32 *)param_2 = 999;
  }
  if (param_3 != 0) {
    *(i32 *)param_3 = 999;
  }
  city_recalc(city,0);
  civ5 = cities[city].owner;
  civ = (uptr)(char)civ5;
  local_fc = tile_landmass((int)cities[city].x,(int)cities[city].y);
  local_f8 = (uint)civs[civ].continent_policy[local_fc];
  if ((local_f8 == 0) || (local_f8 == 1)) {
    local_b0 = 1;
  }
  else {
    local_b0 = 0;
  }
  if (((game.game_flags & 1) != 0) && (local_f8 == 4)) {
    local_b0 = 1;
  }
  iVar5 = ai_spaceship_race_behind(civ);
  local_54 = spaceship_race_active();
  local_54 = iVar5 + local_54;
  local_114 = 0;
  for (city2 = 0; city2 < game.num_cities; city2++) {
    if ((((cities[city2].id != 0) && ((int)cities[city2].founder == civ)) &&
        ((int)cities[city2].owner != civ)) &&
       ((iVar4 = tile_landmass((int)cities[city2].x,(int)cities[city2].y), iVar4 == local_fc
        && (((uint)game.human_players & 1 << (cities[city2].owner & 0x1fU)) != 0)))) {
      local_114++;
    }
  }
  if (leaders[civs[civ].tribe].attack + 1 < local_114) {
    local_b0 = 1;
  }
  local_220 = (city_yield_totals - (int)cities[city].size * (uint)cosmic.food_per_citizen) -
              city_settlers_supported * settler_food_cost;
  local_60 = 0;
  local_48 = city_total_shields * 2 - city_shield_support;
  local_98 = city_total_trade - city_trade_corruption;
  if ((cities[city].building < -0x26) && (0x27 < cities[city].shield_box)) {
    local_78 = 1;
  }
  else {
    local_78 = 0;
  }
  local_8c = 0;
  local_18 = 0;
  for (local_74 = 0; local_74 < 0x1c; local_74++) {
    auStack_cc[local_74] = 0;
    iVar6 = wonder_get_city(local_74);
    if (iVar6 == city) {
      local_8c++;
    }
    iVar6 = civ_has_wonder(civ,local_74);
    if (iVar6 != 0) {
      local_18++;
    }
  }
  if (((cities[city].flags & 1) == 0) && (((byte)(cities[city].flags >> 8) & 0xc0) != 0xc0)) {
    if (city_unhappy_count == city_happy_count) {
      local_d8 = 1;
    }
    else {
      local_d8 = 0;
    }
  }
  else {
    local_d8 = 2;
  }
  city_find_nearest((int)cities[city].x,(int)cities[city].y,civ,0xfffffffe,-1);
  local_ac = nearest_city_dist;
  local_5c = -1;
  local_24c = 0;
  if ((((local_220 == 0) && ((1 << (civ5 & 0x1f) & (uint)game.human_players) == 0)) &&
      ((cities[city].flags & 0x40) == 0)) && (city_settlers_supported == 0)) {
    local_24c = 1;
  }
  local_d4 = 0;
  local_24 = 0;
  for (unit_type2 = 0; unit_type2 < 0x14; unit_type2++) {
    x2 = map_wrap_x((int)cities[city].x + (int)(char)(&city_tile_dx_table)[unit_type2]);
    y2 = (int)cities[city].y + (int)(char)(&city_tile_dy_table)[unit_type2];
    iVar6 = map_in_bounds(x2,y2);
    if (iVar6 != 0) {
      bVar4 = tile_terrain(x2,y2);
      terrain2 = (uptr)bVar4;
      if (terrain2 == 10) {
        local_60++;
        iVar6 = city_tile_worked(city,unit_type2);
        if (iVar6 != 0) {
          local_60 += 3;
        }
      }
      civ2 = tile_unit_owner(x2,y2);
      if (((-1 < (int)civ2) && (civ2 != civ)) &&
         ((unit = tile_first_unit(x2,y2), -1 < unit &&
          ((int)units[unit].owner != civ)))) {
        iVar6 = unit_stack_sum(unit,2);
        local_d4 += iVar6;
      }
      uVar7 = tile_improvements(x2,y2);
      if (((byte)uVar7 & 0xc) == 0xc) {
        local_24++;
      }
      if (((local_24c != 0) && (iVar6 = ai_tile_improve_choice(civ,x2,y2), iVar6 == 1)) &&
         ((uVar8 = tile_improvements(x2,y2), (uVar8 & 4) == 0 &&
          (terrain_types[terrain2].irrigate_to < '\0')))) {
        local_5c = unit_type2;
        iVar6 = tile_resource(x2,y2);
        if ((iVar6 != 0) && (terrain2 == 1)) {
          local_24c = 0;
        }
      }
    }
  }
  if (-1 < local_5c) {
    x2 = map_wrap_x((int)cities[city].x + (int)(char)(&city_tile_dx_table)[local_5c]);
    y2 = (int)cities[city].y + (int)(char)(&city_tile_dy_table)[local_5c];
    iVar6 = tile_at(x2,y2);
    if ((game.human_players & *(byte *)(iVar6 + 4)) == 0) {
      local_d0 = 4;
      pbVar9 = (byte *)tile_at(x2,y2);
      if ((*pbVar9 & 0x80) == 0) {
        local_d0 = local_d0 | 0x10;
      }
      tile_set_improvements(x2,y2,local_d0,1,1);
      local_220++;
    }
  }
  for (unit_type = 0; unit_type < 0x3e; unit_type++) {
    local_21c[unit_type] = 0;
    aiStack_364[unit_type] = 0;
  }
  local_238 = 0;
  local_6c = 0;
  local_e0 = 0;
  local_124 = 0;
  iVar6 = civ_has_wonder(civ,7);
  if (iVar6 == 0) {
    local_268 = 0;
  }
  else {
    local_268 = 4;
  }
  local_260 = 0;
  local_f0 = 0;
  local_a4 = 0;
  local_40 = 0;
  local_64 = 0;
  local_234 = 0;
  local_104 = 0;
  for (city2 = 0; city2 < game.num_cities; city2++) {
    if (cities[city2].id != 0) {
      if ((int)cities[city2].owner == civ) {
        iVar6 = city_has_improvement(city2,1);
        if (((iVar6 != 0) || (cities[city2].building == -1)) &&
           (local_234 = local_234 + 1, local_104 < cities[city2].size)) {
          local_104 = (int)cities[city2].size;
        }
        if (city2 != city) {
          if ((cities[city].building == cities[city2].building) &&
             (local_f0 = local_f0 + 1,
             cities[city].total_shields < cities[city2].total_shields)) {
            local_260++;
          }
          if ((-0x26 < cities[city2].building) && (cities[city2].building < -0x22)) {
            local_40++;
          }
          iVar6 = tile_landmass((int)cities[city2].x,(int)cities[city2].y);
          if (iVar6 == local_fc) {
            iVar6 = city_has_improvement(city2,2);
            if (iVar6 != 0) {
              local_268++;
            }
            iVar6 = city_has_improvement(city2,0x20);
            if (iVar6 != 0) {
              local_6c++;
            }
            iVar6 = city_has_improvement(city2,0x22);
            if (iVar6 != 0) {
              local_e0++;
            }
            if (cities[city2].building == -2) {
              local_268++;
            }
            if (cities[city2].building < -0x26) {
              local_238++;
              if (cities[city].total_shields < cities[city2].total_shields) {
                *(byte *)((int)&unit_type + (1 - cities[city2].building)) =
                     *(byte *)((int)&unit_type + (1 - cities[city2].building)) |
                     (byte)(1 << (civ5 & 0x1f));
              }
              iVar6 = (uint)improvements[-(int)cities[city2].building].cost * city_shield_rows;
              if (iVar6 - cities[city2].shield_box == 0 || iVar6 < cities[city2].shield_box)
              {
                *(byte *)((int)&unit_type + (1 - cities[city2].building)) =
                     *(byte *)((int)&unit_type + (1 - cities[city2].building)) | 1;
              }
            }
            if (-1 < cities[city2].building) {
              local_21c[cities[city2].building] = local_21c[cities[city2].building] + 1;
            }
          }
        }
      }
      else {
        if (cities[city].building == cities[city2].building) {
          local_a4++;
        }
        if (cities[city2].building < -0x26) {
          *(byte *)((int)&unit_type + (1 - cities[city2].building)) =
               *(byte *)((int)&unit_type + (1 - cities[city2].building)) |
               (byte)(1 << (cities[city2].owner & 0x1fU));
        }
        if (((((uint)game.human_players & 1 << (cities[city2].owner & 0x1fU)) != 0) &&
            (-0x26 < cities[city2].building)) && (cities[city2].building < -0x22)) {
          local_64++;
        }
      }
    }
  }
  local_120 = 0;
  local_4c = 0;
  for (unit = 0; unit < game.num_units; unit++) {
    if ((units[unit].id != 0) && ((int)units[unit].owner == civ)) {
      local_124++;
      if (unit_types[unit_type].role == 5) {
        if ((units[unit].flags & 0x200) != 0) {
          local_120++;
        }
        if (units[unit].home_city == -1) {
          local_4c++;
          goto LAB_00499ca3;
        }
      }
      iVar6 = tile_landmass((int)units[unit].x,(int)units[unit].y);
      if (iVar6 == local_fc) {
        aiStack_364[units[unit].type] = aiStack_364[units[unit].type] + 1;
      }
    }
LAB_00499ca3: ;
  }
  if ((((cities[city].flags & 0x80040) == 0x80000) && (local_d4 == 0)) &&
     ((city_settlers_supported == 0 && ((local_f8 != 1 && (2 < cities[city].size)))))) {
    local_30 = 9999;
    for (city2 = 0; city2 < game.num_cities; city2++) {
      if ((((cities[city2].id != 0) && (city2 != city)) &&
          ((int)cities[city2].owner == civ)) &&
         (local_68 = map_distance((int)cities[city].x,(int)cities[city].y,
                                        (int)cities[city2].x,(int)cities[city2].y),
         local_68 < local_30)) {
        local_30 = local_68;
      }
    }
    if (8 < local_30) {
      local_100 = 1;
    }
    if (((6 < cities[city].size) && (4 < civs[civ].government)) &&
       ((0 < local_220 && (local_f8 != 0)))) {
      local_100++;
    }
  }
  local_3c = 0;
  for (unit_type2 = 0; unit_type2 < 0x10; unit_type2++) {
    if ((civs[civ].ai_standing_goals[unit_type2].role == 1) &&
       (iVar6 = tile_landmass((int)civs[civ].ai_standing_goals[unit_type2].x,
                              (int)civs[civ].ai_standing_goals[unit_type2].y),
       iVar6 == local_fc)) {
      local_3c++;
    }
  }
  if (local_b0 != 0) {
    local_3c += (local_3c >> 1);
  }
  if ((((local_124 == 0) && ((1 << (civ5 & 0x1f) & (uint)game.human_players) == 0)) &&
      (civs[civ].government < 2)) && ((param_2 == 0 && (param_3 == 0)))) {
    for (unit_type = 0x3d; -1 < unit_type; unit_type--) {
      if (((unit_types[unit_type].role == 1) && ((unit_types[unit_type].flags & 0x100) == 0)) &&
         (iVar6 = civ_can_build_unit(civ,city,unit_type), iVar6 != 0)) {
        return unit_type;
      }
    }
  }
  if (civ == 0) {
    if (cities[city].building < 1) {
      if (game.advance_known_by[0x1c] != '\0') {
        return 0x13;
      }
      return 5;
    }
    unit_type = (iptr)cities[city].building;
    local_118 = (iptr)unit_types[unit_type].obsolete_by;
    if (local_118 < 0) {
      return unit_type;
    }
    if (game.difficulty == '\0') {
      return unit_type;
    }
    iVar6 = bits_count8((int)(char)game.advance_known_by[local_118]);
    if (iVar6 < 2) {
      return unit_type;
    }
    if (((game.human_players & game.advance_known_by[local_118]) == 0) && (game.difficulty < 4)) {
      return unit_type;
    }
    unit_type2 = 0;
    while( true ) {
      if (0x3d < unit_type2) {
        return unit_type;
      }
      if ((unit_types[unit_type2].prerequisite == local_118) &&
         (unit_types[unit_type].role == unit_types[unit_type2].role)) break;
      unit_type2++;
    }
    return unit_type2;
  }
  local_34 = 0;
  if (local_f8 == 4) {
    for (civ2 = 1; (int)civ2 < 8; civ2++) {
      if (((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 0x20) != 0) &&
         (*(char *)&civs[civ2].continent_cities[local_fc] == '\0')) {
        local_34 = 1;
      }
    }
  }
  local_250 = 0;
  local_264 = 0;
  local_80 = 0;
  unit = tile_first_unit((int)cities[city].x,(int)cities[city].y);
  local_a8 = unit_stack_count_role(unit,1);
  iVar6 = unit_stack_count_role(unit,4);
  local_22c = unit_stack_count_role(unit,2);
  local_22c = (iVar6 >> 1) + local_22c;
  if (local_a8 < 1) {
    local_264 = 2;
    local_80 = 2;
  }
  else {
    if ((local_250 == 0) &&
       (iVar6 = tile_zoc_unit_adjacent((int)cities[city].x,(int)cities[city].y,civ), iVar6 == 0)
       ) {
      local_14 = 4;
    }
    else {
      local_14 = 3;
    }
    iVar6 = city_has_improvement(city,1);
    if (iVar6 == 0) {
      if ((local_f8 == 5) && (local_250 == 0)) {
        local_14++;
      }
    }
    else {
      local_14--;
    }
    if ((local_b0 == 0) && (*(char *)&civs[civ].continent_flags[local_fc] == '\0')) {
      local_370 = 0;
    }
    else {
      local_370 = 1;
    }
    local_108 = local_370 + (int)cities[city].size / local_14;
    iVar6 = city_has_improvement(city,1);
    uVar8 = local_108;
    if (iVar6 != 0) {
      local_d0 = 1;
      if (3 < cities[city].size) {
        local_d0 = 2;
      }
      if (7 < civs[civ].num_cities) {
        local_d0 = 3;
      }
      if (0xb < civs[civ].num_cities) {
        local_d0 = 4;
      }
      uVar8 = local_d0;
      if ((int)local_d0 <= (int)local_108) {
        uVar8 = local_108;
      }
    }
    local_108 = uVar8;
    if ((local_a8 < (int)local_108) && (local_80 = 1, local_a8 + 1 < (int)local_108)) {
      local_264 = 1;
    }
  }
  if ((1 << (civ5 & 0x1f) & (uint)game.human_players) == 0) {
    iVar6 = civ_has_wonder(civ,0);
    if ((iVar6 != 0) && (iVar6 = city_has_improvement(city,3), iVar6 != 0)) {
      city_set_improvement(city,3,0);
      civs[civ].gold += (uint)improvements[3].cost * city_shield_rows;
    }
    iVar6 = civ_has_wonder(civ,0x1a);
    if ((iVar6 != 0) && (iVar6 = city_has_improvement(city,0x1a), iVar6 != 0)) {
      city_set_improvement(city,0x1a,0);
      civs[civ].gold += (uint)improvements[0x1a].cost * city_shield_rows;
    }
    iVar6 = civ_has_wonder(civ,0x15);
    if ((iVar6 != 0) && (iVar6 = city_has_improvement(city,0x21), iVar6 != 0)) {
      city_set_improvement(city,0x21,0);
      civs[civ].gold += (uint)improvements[0x21].cost * city_shield_rows;
    }
    iVar6 = civ_has_wonder(civ,10);
    if ((iVar6 != 0) && (iVar6 = city_has_improvement(city,0xb), iVar6 != 0)) {
      city_set_improvement(city,0xb,0);
      civs[civ].gold += (uint)improvements[0xb].cost * city_shield_rows;
    }
    iVar6 = city_has_improvement(city,0x20);
    if ((((iVar6 != 0) && ((int)game.turn_civ == civ)) && ((cities[city].flags & 0x10000) == 0)
        ) && ((local_f8 != 4 && (local_f8 != 5)))) {
      for (city2 = 0; city2 < game.num_cities; city2++) {
        if (((cities[city2].id != 0) && ((int)cities[city2].owner == civ)) &&
           ((city2 != city &&
            (((iVar6 = city_has_improvement(city2,0x20), iVar6 != 0 &&
              ((cities[city2].flags & 0x10000) == 0)) &&
             (iVar6 = tile_adjacent_nonallied_unit((int)cities[city2].x,(int)cities[city2].y,civ),
             iVar6 == 0)))))) {
          iVar6 = tile_landmass((int)cities[city2].x,(int)cities[city2].y);
          if (iVar6 == local_fc) {
            if (1 < local_80) {
LAB_0049a9d5:
              unit = tile_first_unit((int)cities[city2].x,(int)cities[city2].y);
              if (((-1 < unit) &&
                  ((local_f8 != 1 || (iVar10 = unit_stack_count_role(unit,1), 1 < iVar10)))) &&
                 (cVar2 = *(char *)&civs[civ].continent_policy[iVar6],
                 iVar6 = unit_stack_sum(unit,2),
                 (int)(3 - (uint)(cVar2 == 4)) <= iVar6)) goto LAB_0049aab5;
            }
          }
          else if (civs[civ].continent_policy[iVar6] != local_f8) goto LAB_0049a9d5;
        }
      }
    }
  }
  goto LAB_0049ae3e;
LAB_0049aab5:
  while ((-1 < unit && ((int)(char)unit_types[units[unit].type].role != local_f8))) {
    unit = unit_next_in_stack(unit);
  }
  if (-1 < unit) {
    cities[city].flags = cities[city].flags | 0x10000;
    cities[city2].flags = cities[city2].flags | 0x10000;
    unit_exhaust_moves(unit);
    unit_relocate(unit,(int)cities[city].x,(int)cities[city].y,1);
    unit3 = unit;
    local_230 = 0;
    for (unit = 0; unit < game.num_units; unit++) {
      if ((((units[unit].id != 0) && (unit_types[units[unit].type].role == 3)) &&
          (((uint)game.human_players & 1 << (units[unit].owner & 0x1fU)) != 0)) &&
         ((*(byte *)(civ * 4 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + units[unit].owner * 0x594) & 0x20) != 0)) {
        iVar6 = map_distance((int)cities[city].x,(int)cities[city].y,
                                   (int)units[unit].x,(int)units[unit].y);
        iVar10 = unit_max_moves(unit);
        if (iVar10 / (int)(uint)cosmic.road_move_mult < iVar6) {
          iVar6 = map_distance((int)cities[city2].x,(int)cities[city2].y,
                                     (int)units[unit].x,(int)units[unit].y);
          iVar10 = unit_max_moves(unit);
          if (iVar10 / (int)(uint)cosmic.road_move_mult < iVar6) goto LAB_0049aba3;
        }
        iVar6 = rand_range(0,(-(uint)((units[unit].flags & 0x2000) == 0) & 2) + 3);
        if (iVar6 == 0) {
          unit_delete(unit3,1);
          unit3 = -1;
          break;
        }
        local_230++;
      }
LAB_0049aba3: ;
    }
    if (unit3 < 0) {
      text_set_string_arg(0,(iptr)&cities[city].name);
      popup_game(ADDR(0x62cd00, ((u8 *)&g.d_0062cd00)));
    }
    else if (local_230 != 0) {
      text_set_string_arg(0,(iptr)&cities[city].name);
      popup_game(ADDR(0x62cd08, ((u8 *)&g.d_0062cd08)));
    }
  }
LAB_0049ae3e:
  local_20 = 999;
  local_26c = 999;
  local_30 = 999;
  local_254 = 999;
  local_240 = 999;
  local_58 = 999;
  for (improvement = 1; improvement < 0x27; improvement++) {
    iVar6 = city_can_build_improvement(civ,city,improvement);
    if (iVar6 != 0) {
      local_1c = 999;
      local_90 = 0;
      if (improvement - 1U < 0x23) {
        iVar6 = local_220 >> 1;
        switch(improvement) {
        case 1:
          if ((((local_234 == 0) || ((1 << (civ5 & 0x1f) & (uint)game.human_players) == 0)) &&
              ((local_234 == 0 ||
               ((local_234 == 1 && (local_104 * 2 < (int)cities[city2].size)))))) &&
             ((local_f8 == 4 || (((local_f8 == 5 || (local_f8 == 0)) || (3 < city_shield_waste)))))) {
            local_1c = 2;
            if ('\t' < cities[city2].size) {
              local_1c = 1;
            }
            if (14 < cities[city2].size) {
              local_1c--;
            }
            if (3 < city_shield_waste) {
              local_90 = local_b0;
            }
          }
          break;
        case 2:
          local_1c = (leaders[civs[civ].tribe].civilize + local_268 + 4) -
                     (int)leaders[civs[civ].tribe].attack;
          if (((leaders[civs[civ].tribe].attack < '\0') ||
              ('\0' < leaders[civs[civ].tribe].civilize)) &&
             ((int)leaders[civs[civ].tribe].civilize + (int)leaders[civs[civ].tribe].attack != 0
             )) {
            local_1c += local_268;
          }
          local_90 = 1;
          if ((1 << (civ5 & 0x1f) & (uint)game.human_players) != 0) {
            if (game.difficulty == 3) {
              local_1c = (int)(local_1c * 3) / 2;
            }
            if (3 < game.difficulty) {
              local_1c = local_1c << 1;
            }
          }
          break;
        case 3:
          iVar6 = civ_has_wonder(civ,0);
          if (iVar6 == 0) {
            if (city_total_shields < 3) {
              local_1c = 8;
            }
            else {
              local_1c = 4;
            }
            if (city_happy_count <= city_unhappy_count) {
              local_1c += 2;
            }
            if (((1 << (civ5 & 0x1f) & (uint)game.human_players) != 0) &&
               (local_d0 = (game.difficulty + 4) - (int)cities[city2].size, 0 < (int)local_d0))
            {
              local_1c += local_d0;
            }
          }
          break;
        case 4:
          if (local_d8 == 1) {
            local_1c = 9;
          }
          if (local_d8 == 2) {
            local_1c = 0xfffffffb;
          }
          break;
        case 5:
          local_1c = int_clamp(10 - (local_98 >> 1),1,10);
          if (local_d8 == 1) {
            local_1c--;
          }
          if (local_d8 == 2) {
            local_1c = 0xfffffffc;
          }
          break;
        case 6:
          local_1c = int_clamp(10 - local_98 / 3,1,10);
          break;
        case 7:
          local_1c = 0xe - (city_shield_waste * 2 + city_trade_corruption);
          if (civs[civ].government == 6) {
            if (local_d8 == 2) {
              local_1c = 0xffffffff;
            }
          }
          else if ((1 << (civ5 & 0x1f) & (uint)game.human_players) == 0) {
            local_1c -= (int)civs[game.field_138].field_1c / 2;
          }
          break;
        case 8:
          iVar6 = civ_has_wonder(civ,6);
          if (iVar6 == 0) {
            local_1c = 10 - ((int)cities[city].size >> 1);
            for (civ3 = 1; civ3 < 8; civ3++) {
              if ((1 << ((byte)civ3 & 0x1f) & (uint)game.human_players) != 0) {
                if ((civs[civ].treaties[civ3] & 0x2010) != 0) {
                  local_1c -= 2;
                }
                if (*(char *)&civs[civ3].continent_cities[local_fc] != '\0') {
                  local_1c--;
                }
              }
            }
            if (game.advance_known_by[0x48] != '\0') {
              local_1c += 2;
            }
            if (game.advance_known_by[0] != '\0') {
              local_1c += 2;
            }
            if (game.advance_known_by[0x49] != '\0') {
              local_1c += 2;
            }
            local_1c = int_clamp(local_1c,1,10);
            iVar6 = city_has_improvement(city,1);
            if (iVar6 != 0) {
              local_1c -= 4;
            }
            local_90 = 1;
          }
          break;
        case 9:
          if ((int)((uint)cosmic.aqueduct_size - iVar6) <= (int)cities[city].size) {
            local_1c = ((cosmic.aqueduct_size + 4) - (int)cities[city].size) - iVar6;
            local_1c = int_clamp(local_1c,1,0x14);
          }
          break;
        case 10:
          local_1c = int_clamp(10 - local_98 / 3,1,10);
          if (local_d8 == 1) {
            local_1c--;
          }
          if (local_d8 == 2) {
            local_1c = 0;
          }
          break;
        case 0xb:
          iVar6 = civ_has_wonder(civ,10);
          if (iVar6 == 0) {
            if (local_d8 == 1) {
              local_1c = 8;
            }
            if (local_d8 == 2) {
              local_1c = 0xfffffffd;
            }
          }
          break;
        case 0xc:
          if ((civs[civ].science_rate != '\0') &&
             ((local_54 == 0 || (iVar6 = civ_has_advance(civ,0x4c), iVar6 == 0)))) {
            local_1c = int_clamp(10 - (local_98 >> 2),2,10);
          }
          break;
        case 0xd:
          break;
        case 0xe:
          if (local_d8 == 2) {
            local_1c = 0xfffffffe;
          }
          break;
        case 0xf:
        case 0x14:
          local_1c = int_clamp(0xe - city_total_shields,1,0xe);
          break;
        default:
          local_1c = int_clamp(0xc - ((int)(city_total_shields + (city_total_shields >> 0x1f & 3U)) >>
                                              2),2,0xc);
          break;
        case 0x11:
          if (local_d8 < 2) {
            iVar6 = int_clamp(0xf - cities[city].size,1,0xf);
            local_1c = (iVar6 + 1) / 2;
            if (game.wonder_city[0x17] == -1) {
              local_1c = local_1c << 1;
            }
            if (civs[game.field_138].units_active[0x2d] == '\0') {
              local_1c = local_1c << 1;
            }
            if ('\t' < cities[city].size) {
              local_1c--;
            }
            iVar6 = city_has_improvement(city,1);
            if (iVar6 != 0) {
              local_1c = 0;
            }
          }
          local_90 = 1;
          break;
        case 0x13:
          local_1c = int_clamp(0xc - city_total_shields / 5,2,0xe);
          break;
        case 0x16:
          if ((local_d8 != 0) || (local_54 < 2)) {
            local_1c = int_clamp(0xb - (local_98 >> 2),2,0xb);
            if (local_d8 == 1) {
              local_1c--;
            }
            if (local_d8 == 2) {
              local_1c = 0;
            }
          }
          break;
        case 0x17:
          if ((local_54 < 2) &&
             ((int)((uint)cosmic.sewer_size - iVar6) <= (int)cities[city].size)) {
            local_1c = ((cosmic.sewer_size + 4) - (int)cities[city].size) - iVar6;
            local_1c = int_clamp(local_1c,1,0x14);
          }
          break;
        case 0x18:
          local_1c = (0xe - ((int)cities[city].size >> 1)) + local_24 * -2 + local_54 * 2 + iVar6
          ;
          local_1c = int_clamp(local_1c,2,0xe);
          break;
        case 0x19:
          local_1c = (0xf - ((int)cities[city].size >> 1)) + local_54 * 6;
          local_1c = int_clamp(local_1c,2,0xf);
          break;
        case 0x1a:
          if (((local_54 == 0) || (iVar6 = civ_has_advance(civ,0x4c), iVar6 == 0)) &&
             (civs[civ].science_rate != '\0')) {
            local_1c = int_clamp(0xb - (local_98 >> 2),2,10);
          }
          break;
        case 0x1b:
          local_10 = ((uint)civs[game.field_138].units_active[0x1f] * 2 +
                      (uint)civs[game.field_138].units_active[0x1c] * 2 +
                      (uint)civs[game.field_138].units_active[0x2c] +
                     (uint)civs[game.field_138].units_active[0x1d]) * 2;
          if ((1 << (civ5 & 0x1f) & (uint)game.human_players) != 0) {
            local_10 = 0;
            for (civ2 = 1; (int)civ2 < 8; civ2++) {
              if (civ2 != civ) {
                local_d0 = (uint)civs[civ2].units_active[0x2c] +
                           (uint)civs[civ2].units_active[0x1c] +
                           (uint)civs[civ2].units_active[0x1d] +
                           (uint)civs[civ2].units_active[0x1f];
                if (((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 0x20) == 0) &&
                   ((*(byte *)&civs[civ2].treaties[civ] & 0x10) == 0)) {
                  local_d0 = local_d0 / 2;
                }
                local_10 += local_d0;
              }
            }
          }
          local_1c = 0xc - local_10;
          local_1c = int_clamp(local_1c,1,0xc);
          if ((cities[city].flags & 0x40000) != 0) {
            local_1c -= 3;
          }
          local_90 = 1;
          for (civ3 = 1; civ3 < 8; civ3++) {
            if (((1 << ((byte)civ3 & 0x1f) & (uint)game.human_players) != 0) &&
               ((4 < civs[civ3].reputation ||
                ((*(byte *)(civ3 * 4 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ * 0x594) & 0x20) != 0)))) {
              local_90 = (uint)(local_b0 != 0);
              break;
            }
          }
          break;
        case 0x1c:
          iVar6 = city_adjacent_to_body(city,1);
          if (iVar6 != 0) {
            local_10 = (uint)civs[game.field_138].units_active[0x26] * 3 +
                       (uint)civs[game.field_138].units_active[0x27] * 3 +
                       (uint)civs[game.field_138].units_active[0x28] * 5 +
                       (uint)civs[game.field_138].units_active[0x24] +
                       (uint)civs[game.field_138].units_active[0x25];
            if ((1 << (civ5 & 0x1f) & (uint)game.human_players) != 0) {
              local_10 = 0;
              for (civ2 = 1; (int)civ2 < 8; civ2++) {
                if (civ2 != civ) {
                  local_d0 = ((int)(uint)civs[civ2].units_active[0x24] >> 1) +
                             ((int)(uint)civs[civ2].units_active[0x25] >> 1) +
                             (uint)civs[civ2].units_active[0x28] * 2 +
                             (uint)civs[civ2].units_active[0x26] +
                             (uint)civs[civ2].units_active[0x27];
                  if (((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 0x20) == 0) &&
                     ((*(byte *)&civs[civ2].treaties[civ] & 0x10) == 0)) {
                    local_d0 = local_d0 / 2;
                  }
                  local_10 += local_d0;
                }
              }
            }
            local_1c = 0xc - local_10;
            local_1c = int_clamp(local_1c,1,0xc);
            local_90 = 1;
            for (civ3 = 1; civ3 < 8; civ3++) {
              if (((1 << ((byte)civ3 & 0x1f) & (uint)game.human_players) != 0) &&
                 ((4 < civs[civ3].reputation ||
                  ((*(byte *)(civ3 * 4 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ * 0x594) & 0x20) != 0)))) {
                local_90 = (uint)(local_b0 != 0);
                break;
              }
            }
          }
          break;
        case 0x1d:
          break;
        case 0x1e:
          if ((local_d8 < 2) &&
             (local_1c = int_clamp(0x10 - local_60,2,0x10), local_220 < 1)) {
            local_1c = (int)local_1c / 2;
          }
          break;
        case 0x1f:
          if (local_d8 < 2) {
            local_1c = 0x10 - local_60;
            local_1c = int_clamp(local_1c,2,0x10);
            if (0 < (int)local_1c) {
              iVar6 = city_has_improvement(city,0xf);
              if (iVar6 != 0) {
                local_1c = (int)local_1c / 2;
              }
              iVar6 = city_has_improvement(city,0x10);
              if (iVar6 != 0) {
                local_1c = (int)local_1c / 2;
              }
            }
            if (((city_total_shields - city_shield_support <= city_total_shields / 3) ||
                (city_total_shields < (int)cities[city2].size / 2)) &&
               ((int)cities[city2].size / 2 <= (int)(local_60 + (local_60 >> 0x1f & 3U)) >> 2))
            {
              local_1c -= 2;
            }
          }
          break;
        case 0x20:
          local_1c = (local_6c * 4 + 4) - (int)leaders[civs[civ].tribe].attack;
          if (*(char *)&civs[civ].continent_policy[local_fc] == 4) {
            local_1c = (int)local_1c / 2;
          }
          iVar6 = civ_has_advance(civ,0);
          if (iVar6 == 0) {
            local_1c = local_1c << 1;
          }
          if (((*(char *)&civs[civ].continent_cities[local_fc] == 1) ||
              (((civs[civ].continent_flags[local_fc] & 0x10) != 0 && (local_6c == 0))))
             && ((int)(uint)civs[civ].continent_cities[local_fc] < (int)local_1c)) {
            local_1c = (uint)civs[civ].continent_cities[local_fc];
          }
          iVar6 = city_has_improvement(city,1);
          if ((iVar6 != 0) && (-1 < (int)local_1c)) {
            local_1c = 0;
          }
          local_90 = local_b0;
          break;
        case 0x21:
          iVar6 = civ_has_wonder(civ,0x15);
          if (iVar6 == 0) {
            local_d0 = city_aggressive_units;
            if (5 < civs[civ].government) {
              local_d0 = city_aggressive_units << 1;
            }
            if (((4 < civs[civ].government) && (local_d0 != 0)) &&
               (city_happy_count - city_unhappy_count < 2)) {
              local_d0 += 2;
            }
            local_1c = 10 - local_d0;
          }
          break;
        case 0x22:
          iVar6 = city_adjacent_to_body(city,1);
          if (iVar6 != 0) {
            iVar6 = local_ac;
            if (0x27 < local_ac) {
              iVar6 = 0x28;
            }
            local_1c = (0xb - (iVar6 >> 2)) + local_22c * -5 +
                       (local_e0 * 2 - (int)leaders[civs[civ].tribe].attack) +
                       (int)leaders[civs[civ].tribe].civilize;
            local_1c = int_clamp(local_1c,2,0xf);
            if (leaders[civs[civ].tribe].attack < '\0') {
              local_1c += local_e0;
            }
          }
          break;
        case 0x23:
          iVar6 = civ_spaceship_launched(civ);
          if (((iVar6 == 0) && ((game.game_flags & 2) == 0)) &&
             ((iVar6 = spaceship_choose_part_group(civ,0), -1 < iVar6 &&
              (((1 << (civ5 & 0x1f) & (uint)game.human_players) == 0 ||
               (civs[civ].spaceship_parts[0] < 0x26)))))) {
            local_1c = 4;
            for (civ3 = 1; civ3 < 8; civ3++) {
              if (((1 << ((byte)civ3 & 0x1f) & (uint)game.human_players) != 0) &&
                 (iVar6 = civ_spaceship_exists(civ3), iVar6 != 0)) {
                local_1c = 2;
                break;
              }
            }
            if ((local_f8 != 0) && ((civs[civ].continent_flags[local_fc] & 0x10) == 0)) {
              local_90 = local_b0;
            }
            local_248 = 0;
            if ((game.game_flags & 2) == 0) {
              for (civ3 = 1; civ3 < 8; civ3++) {
                if (((1 << ((byte)civ3 & 0x1f) & (uint)game.human_players) != 0) &&
                   (iVar6 = civ_spaceship_launched(civ3), iVar6 != 0)) {
                  local_248 = 1;
                  break;
                }
              }
            }
            if ((1 < local_54) && (game.difficulty != '\0')) {
              uVar8 = local_1c - 1;
              if (local_248 != 0) {
                uVar8 = local_1c - 2;
              }
              local_1c = uVar8;
              if (local_264 == 0) {
                local_90 = local_b0;
              }
            }
            local_88 = 0;
            local_10c = 0;
            for (local_94 = 0; local_94 < 6; local_94++) {
              local_110 = int_clamp((local_94 + 1) / 2,0,2);
              local_10c = local_10c +
                          (int)civs[civ].spaceship_parts[local_94] *
                          (uint)improvements[local_110 + 0x23].cost;
              local_88 = local_88 +
                         (int)civs[((uint)game.field_138)].spaceship_parts[local_94] *
                         (uint)improvements[local_110 + 0x23].cost;
            }
            if (((local_40 == 0) ||
                (((local_40 <= local_64 && (local_10c <= local_88)) || (local_248 != 0)))) &&
               ((((cities[city].flags & 1) == 0 && (game.difficulty != '\0')) &&
                (((int)civs[civ].field_3d2 >> 1 <= local_48 || (0x13 < local_48)))))) {
              local_30 = 999;
            }
          }
        }
      }
      if ((int)local_1c < 400) {
        local_1c = (int)(((-(uint)(local_b0 == local_90) & 0xfffffff6) + 0x14) * local_1c * 3) /
                   (leaders[civs[civ].tribe].civilize + 3);
      }
      else {
        local_1c = 0x3fff;
      }
      iVar6 = city_has_improvement(city,2);
      if (iVar6 != 0) {
        local_1c += (int)local_1c / ((local_268 >> 1) + 3);
      }
      iVar6 = wonder_get_city(0xd);
      if (iVar6 == city) {
        local_1c += (int)local_1c / 3;
      }
      if ((int)local_1c < local_30) {
        local_30 = local_1c;
        local_58 = -improvement;
      }
      if ((int)local_1c < local_20) {
        local_20 = local_1c;
        local_254 = -improvement;
      }
    }
  }
  if (((1 << (civ5 & 0x1f) & (uint)game.human_players) != 0) && (citypref_count != 0)) {
    for (unit_type2 = 0; unit_type2 < citypref_count; unit_type2++) {
      improvement = (&citypref_improvements)[unit_type2];
      iVar6 = city_has_improvement(city,improvement);
      if ((iVar6 == 0) && (iVar6 = city_can_build_improvement(civ,city,improvement), iVar6 != 0)) {
        local_254 = -improvement;
        local_58 = -improvement;
        goto LAB_0049ea4a;
      }
    }
  }
  if ((local_78 != 0) ||
     (((((civs[civ].continent_flags[local_fc] & 0x10) == 0 &&
        (2 < cities[city].size)) && (((byte)(cities[city].flags >> 8) & 0xc0) != 0xc0))
      && ((4 - leaders[civs[civ].tribe].civilize <=
           (int)(uint)civs[civ].continent_cities[local_fc] ||
          ((*(char *)&civs[civ].continent_flags[local_fc] == '\0' &&
           (4 - leaders[civs[civ].tribe].civilize <= (int)civs[civ].num_cities)))))))) {
    for (local_74 = 0; local_74 < 0x1c; local_74++) {
      improvement = local_74 + 0x27;
      iVar6 = city_can_build_improvement(civ,city,improvement);
      if (iVar6 != 0) {
        local_90 = 0;
        if (local_f8 == 4) {
          local_90 = local_b0;
        }
        iVar6 = (local_18 + local_8c + 8) - civs[civ].gold / 200;
        if (iVar6 < 2) {
          iVar6 = 1;
        }
        local_28 = local_74 / 7;
        local_1c = iVar6 + (uint)civs[civ].wonders_by_group[local_28];
        if ((byte)(&human_wonders_by_group_min)[local_28] < civs[civ].wonders_by_group[local_28]) {
          local_1c += 2;
        }
        if (civs[civ].wonders_by_group[local_28] <
            civs[((uint)game.field_139)].wonders_by_group[local_28]) {
          local_1c--;
        }
        if ((((local_78 == 0) || ((int)cities[city].building == -improvement)) ||
            ((((game.human_players & *(byte *)((int)&unit_type + (1 - cities[city].building))) ==
               0 || ((*(short *)((int)&game + cities[city].building * -2 + 0xb0) != -1 ||
                     ((int)cities[city].shield_box <
                      (int)((uint)improvements[-(int)cities[city].building].cost * city_shield_rows)
                      / 2)))) &&
             ((*(byte *)((int)&unit_type + (1 - cities[city].building)) & 1) == 0)))) &&
           (((1 < game.difficulty || (local_a0 = (iptr)improvements[improvement].preq, local_a0 < 0))
            || ((game.human_players & game.advance_known_by[local_a0]) != 0)))) {
          if (local_74 != 0x17) {
            if (game.difficulty < 2) {
              for (city2 = 0; city2 < game.num_cities; city2++) {
                if (((cities[city2].id != 0) &&
                    (((uint)game.human_players & 1 << (cities[city2].owner & 0x1fU)) != 0)) &&
                   ((int)cities[city2].building == -improvement)) {
                  local_1c = 999;
                }
              }
              if (local_1c == 999) goto LAB_0049cadf;
            }
            iVar6 = civ_has_advance(civ,0x49);
            if ((iVar6 != 0) && ((game.human_players & game.advance_known_by[0x49]) == 0))
            goto LAB_0049cadf;
          }
          uVar8 = local_1c;
          switch(local_74) {
          case 0:
            uVar8 = local_1c - (leaders[civs[civ].tribe].civilize * 3 + 2);
            break;
          case 1:
            uVar8 = local_1c - ((int)civs[civ].num_cities / 3 + 1);
            break;
          case 2:
            iVar6 = city_has_improvement(city,1);
            if (iVar6 != 0) {
              local_1c--;
            }
            iVar6 = city_has_improvement(city,5);
            if (iVar6 != 0) {
              local_1c--;
            }
            uVar8 = local_1c - (int)cities[city].size / 3;
            break;
          case 3:
            uVar8 = local_1c -
                    ((int)(civs[civ].units_active[0x21] + 2 + (uint)civs[civ].units_active[0x20]
                          ) >> 2);
            break;
          case 4:
            for (civ4 = 1; uVar8 = local_1c, (int)civ4 < 8; civ4++) {
              if (civs[civ4].num_advances < civs[civ].num_advances) {
                if ((1 << ((byte)civ4 & 0x1f) & (uint)game.human_players) != 0) {
                  uVar8 = local_1c + 1;
                }
              }
              else {
                uVar8 = local_1c - 1;
                if (((1 << ((byte)civ4 & 0x1f) & (uint)game.human_players) != 0) &&
                   (civs[civ].num_advances + 5 < (uint)civs[civ4].num_advances)) {
                  uVar8 = local_1c - 3;
                }
              }
              local_1c = uVar8;
            }
            break;
          case 5:
            uVar8 = local_1c -
                    (((int)((int)civs[civ].num_cities + ((int)civs[civ].num_cities >> 0x1f & 3U)
                           ) >> 2) - (int)game.turn / 0x19);
            break;
          case 6:
            uVar8 = local_1c + leaders[civs[civ].tribe].civilize * -2;
            break;
          case 7:
            uVar8 = local_1c -
                    (leaders[civs[civ].tribe].attack * 3 + (int)leaders[civs[civ].tribe].expand
                     + leaders[civs[civ].tribe].civilize * -2 + 1);
            break;
          case 8:
            iVar6 = int_clamp((city_total_shields * 2) / 3,0,3);
            uVar8 = local_1c - iVar6;
            break;
          case 9:
            for (civ3 = 1; uVar8 = local_1c, civ3 < 8; civ3++) {
              if ((1 << ((byte)civ3 & 0x1f) & (uint)game.human_players) != 0) {
                if ((*(byte *)&civs[civ].treaties[civ3] & 8) != 0) {
                  local_1c--;
                }
                if ((*(byte *)&civs[civ].treaties[civ3] & 6) != 0) {
                  local_1c--;
                }
              }
            }
            break;
          case 10:
            uVar8 = local_1c -
                    ((int)((int)civs[civ].num_cities + ((int)civs[civ].num_cities >> 0x1f & 3U))
                    >> 2);
            break;
          case 0xb:
            local_1c = (local_1c - ((int)(local_98 + (local_98 >> 0x1f & 7U)) >> 3)) - 1;
            iVar6 = city_has_improvement(city,1);
            uVar8 = local_1c;
            if (iVar6 != 0) {
              uVar8 = local_1c - 1;
            }
            break;
          case 0xc:
            local_2c = 0;
            for (unit_type = 0; unit_type < 0x3e; unit_type++) {
              if (unit_types[unit_type].domain == 2) {
                local_2c += (uint)civs[civ].units_active[unit_type];
              }
            }
            uVar8 = local_1c - ((int)(local_2c + 3 + (local_2c + 3 >> 0x1f & 3U)) >> 2);
            break;
          case 0xd:
            uVar8 = local_1c - (int)cities[city].size / 5;
            break;
          case 0xe:
            local_90 = local_b0;
            uVar8 = local_1c - 4;
            break;
          case 0xf:
            local_1c -= ((int)(uint)civs[civ].continent_city_size[local_fc] >> 4);
            iVar6 = city_has_improvement(city,1);
            uVar8 = local_1c;
            if (iVar6 != 0) {
              uVar8 = local_1c - 1;
            }
            break;
          case 0x10:
            local_1c -= (int)cities[city].size / 6;
            iVar6 = city_has_improvement(city,1);
            uVar8 = local_1c;
            if (iVar6 != 0) {
              uVar8 = local_1c - 1;
            }
            break;
          case 0x11:
            uVar8 = local_1c -
                    ((int)((int)civs[civ].num_cities + ((int)civs[civ].num_cities >> 0x1f & 3U))
                    >> 2);
            break;
          case 0x12:
            uVar8 = local_1c - 3;
            break;
          case 0x13:
            iVar6 = civ_has_advance(civ,0xf);
            if (iVar6 == 0) {
              uVar8 = local_1c - 2;
            }
            else {
              uVar8 = local_1c - 1;
            }
            break;
          case 0x14:
            if (((uint)game.human_players & 1 << (game.civ_by_rank[7] & 0x1f)) != 0) {
              uVar8 = local_1c - 1;
              if (3 < civs[game.civ_by_rank[7]].reputation) {
                uVar8 = local_1c - 2;
              }
              local_1c = uVar8;
              uVar8 = local_1c;
              if ((7 < civs[game.civ_by_rank[7]].num_cities) &&
                 (uVar8 = local_1c - 1, game.power_rank[civ] == 6)) {
                uVar8 = local_1c - 2;
              }
            }
            break;
          case 0x15:
            uVar8 = local_1c - 1;
            if (((-1 < leaders[civs[civ].tribe].expand) &&
                (-1 < leaders[civs[civ].tribe].civilize)) &&
               (-1 < leaders[civs[civ].tribe].attack)) {
              uVar8 = local_1c - 2;
            }
            local_1c = uVar8;
            if (0 < civs[civ].government_score[5]) {
              local_1c--;
            }
            if (4 < civs[civ].government) {
              local_1c--;
            }
            uVar8 = local_1c;
            if (5 < civs[civ].government) {
              uVar8 = local_1c - 1;
            }
            break;
          case 0x16:
            uVar8 = local_1c - civs[civ].continent_city_size[local_fc] / 0x14;
            break;
          case 0x17:
            iVar6 = civ_has_advance(civ,0x49);
            if (iVar6 != 0) {
              local_d0 = 0;
              for (civ3 = 1; civ3 < 8; civ3++) {
                if ((((1 << ((byte)civ3 & 0x1f) & (uint)game.human_players) != 0) &&
                    (iVar6 = civ_has_advance(civ3,0x49), iVar6 != 0)) &&
                   (civs[civ3].military_strength < civs[civ].military_strength)) {
                  local_d0 = 1;
                  break;
                }
              }
              if (local_d0 == 0) {
                if (((uint)game.human_players & 1 << (game.civ_by_rank[7] & 0x1f)) != 0) {
                  local_1c--;
                  iVar6 = civ_has_advance((uint)game.civ_by_rank[7],0x49);
                  if (iVar6 == 0) {
                    local_1c--;
                  }
                }
                uVar8 = local_1c +
                        (leaders[civs[civ].tribe].civilize * 2 -
                        (int)leaders[civs[civ].tribe].attack);
                break;
              }
            }
            goto LAB_0049cadf;
          case 0x18:
            uVar8 = local_1c -
                    ((int)leaders[civs[civ].tribe].civilize +
                    leaders[civs[civ].tribe].attack * -2);
            if (game.power_rank[civ] == 7) {
              uVar8--;
            }
            break;
          case 0x19:
            uVar8 = local_1c -
                    (leaders[civs[civ].tribe].civilize * 3 +
                    leaders[civs[civ].tribe].attack * -2);
            break;
          case 0x1a:
            uVar8 = local_1c - (leaders[civs[civ].tribe].civilize * 2 + 2);
            break;
          case 0x1b:
            uVar8 = local_1c - (leaders[civs[civ].tribe].attack + 2);
          }
          local_1c = uVar8;
          local_9c = wonder_is_expired(local_74);
          if (local_9c != 0) {
            local_1c = local_1c * 3 + (uint)game.difficulty * 0x32;
          }
          local_1c += local_238 * 5;
          if (((local_238 == 0) || (local_78 != 0)) &&
             (*(char *)&civs[civ].wonders_by_group[local_28] == '\0')) {
            local_1c -= 2;
          }
          if (local_f8 == 1) {
            local_1c = local_1c + local_d4 + 1;
          }
          else {
            local_1c += local_d4 / 2;
          }
          if ((int)cities[city].building == -improvement) {
            if (local_a4 != 0) {
              local_1c = (int)local_1c / 2;
            }
            local_1c = (local_260 + 1) * local_1c + local_260;
          }
          else if ((1 << (civ5 & 0x1f) &
                   (uint)*(byte *)((int)&unit_type + (1 - cities[city].building))) != 0) {
            local_1c = local_1c * 2 + 1;
          }
          local_c = local_1c;
          local_e4 = (uint)improvements[improvement].cost * city_shield_rows + 1;
          if (((local_78 != 0) && (local_264 == 0)) && (local_9c == 0)) {
            if (local_238 == 0) {
              if (local_b0 == local_90) {
                local_1c = (int)local_1c / 2;
              }
              else {
                local_90 = local_b0;
              }
            }
            if ((int)(local_e4 * 3 + (local_e4 * 3 >> 0x1f & 3U)) >> 2 <=
                (int)cities[city].shield_box) {
              local_90 = local_b0;
            }
            if (((local_b0 != local_90) && (local_e4 / 2 <= (int)cities[city].shield_box)) &&
               (local_238 < 3)) {
              local_90 = local_b0;
            }
          }
          if (local_78 == 0) {
            if ((int)civs[civ].field_3d2 >> 1 < local_48) {
              if ((((1 << (civ5 & 0x1f) & (uint)game.human_players) != 0) &&
                  (civs[civ].field_3d2 != local_48)) && (local_48 < 6)) {
                local_1c = local_1c << 1;
              }
            }
            else {
              local_1c = local_1c << 1;
            }
          }
          if (civs[civ].field_3d2 == local_48) {
            local_1c -= (int)local_1c / 3;
          }
          local_1c = (int)(((-(uint)(local_b0 == local_90) & 0xfffffff6) + 0x14) * local_1c * 3) /
                     (leaders[civs[civ].tribe].civilize + 3);
          iVar6 = city_has_improvement(city,2);
          if (iVar6 != 0) {
            local_1c += (int)local_1c / ((local_268 >> 1) + 3);
          }
          iVar6 = city_has_improvement(city,1);
          if ((iVar6 != 0) &&
             ((local_1c = local_1c - (int)local_1c / 3, local_8c == 0 ||
              (*(char *)&civs[civ].wonders_by_group[local_28] == '\0')))) {
            local_1c = (int)local_1c / 2;
          }
          if ((cities[city].flags & 0x100) == 0) {
            if ((local_78 != 0) && (local_9c == 0)) {
              local_1c = (((local_e4 - cities[city].shield_box) *
                          ((int)(local_1c * 3 + ((int)(local_1c * 3) >> 0x1f & 3U)) >> 2)) /
                          local_e4 + ((int)(local_1c + ((int)local_1c >> 0x1f & 3U)) >> 2)) / 3;
            }
          }
          else {
            local_1c = local_1c * 3;
          }
          if (local_58 < -0x26) {
            if (local_c < local_8) {
              local_8 = local_c;
              local_58 = -improvement;
              local_254 = -improvement;
              if ((int)local_1c < local_30) {
                local_30 = local_1c;
              }
              if ((int)local_1c < local_20) {
                local_20 = local_1c;
              }
            }
          }
          else {
            if ((int)local_1c < local_30) {
              local_8 = local_c;
              local_30 = local_1c;
              local_58 = -improvement;
            }
            if ((int)local_1c < local_20) {
              local_20 = local_1c;
              local_254 = -improvement;
            }
          }
        }
      }
LAB_0049cadf: ;
    }
  }
  if (civs[civ].num_military_units < 0x200) {
    for (unit_type = 0; unit_type < 0x3e; unit_type++) {
      if ((5 < (char)unit_types[unit_type].role) &&
         (iVar6 = civ_can_build_unit(civ,city,unit_type), iVar6 != 0)) {
        local_1c = 999;
        local_90 = 0;
        if (unit_types[unit_type].role == 6) {
          local_23c = ai_spaceship_race_behind(civ);
          if (local_23c != 0) {
            iVar6 = civ_has_advance(civ,0x4c);
            if ((((iVar6 != 0) &&
                 (iVar6 = civ_has_advance(civ,(int)improvements[0x24].preq), iVar6 != 0)) &&
                (iVar6 = civ_has_advance(civ,(int)improvements[0x25].preq), iVar6 != 0)) &&
               (iVar6 = civ_has_advance(civ,0x20), iVar6 != 0)) {
              local_23c = 0;
            }
            if ((local_264 != 0) || ((cities[city].flags & 1) != 0)) {
              local_23c = 0;
            }
            if (game.difficulty < 2) {
              local_23c = 0;
            }
          }
          if (((1 << (civ5 & 0x1f) & (uint)game.human_players) == 0) ||
             ((cities[city].flags & 0x10) == 0)) {
            if ((local_21c[unit_type] <= local_23c) &&
               (aiStack_364[unit_type] < (int)(uint)civs[civ].continent_cities[local_fc]))
            {
              local_1c = 0xb;
              civ4 = 0xffffffff;
              for (civ2 = 1; (int)civ2 < 8; civ2++) {
                if (((civ2 != civ) &&
                    (((*(byte *)&civs[civ].treaties[civ2] & 6) == 0 ||
                     (((((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0 &&
                        ((game.power_rank[civ] <= game.power_rank[civ2] || (local_23c != 0))))
                       && ((unit_type == 0x2f ||
                           (((7 < (int)((uint)civs[civ2].num_advances -
                                       (uint)civs[civ].num_advances) || (local_23c != 0)) ||
                            (game.power_rank[civ2] == 7)))))) &&
                      ((((*(byte *)&civs[civ].treaties[civ2] & 8) != 0 ||
                        (local_23c != 0)) ||
                       ((civs[civ2].government < 5 ||
                        ((civs[civ2].continent_attack[local_fc] <=
                          civs[civ].continent_military[local_fc] ||
                         (*(char *)&civs[civ].continent_cities[local_fc] == '\0')))))))))))) &&
                   (*(char *)&civs[civ2].continent_cities[local_fc] != '\0')) {
                  civ4 = civ2;
                }
              }
              if ((int)civ4 < 0) {
                civ4 = (uint)game.field_138;
                if ((local_f8 == 4) && (game.difficulty != '\0')) {
                  local_90 = local_b0;
                  local_1c = 8;
                  iVar6 = civs[civ].num_cities + 3;
                  if ((int)((uint)civs[civ].units_active[unit_type] +
                           (uint)civs[civ].units_in_production[unit_type]) <
                      (int)(iVar6 + (iVar6 >> 0x1f & 3U)) >> 2) {
                    if (civs[game.field_138].gold < civs[civ].gold) {
                      local_1c = 7;
                    }
                    if (civs[game.field_138].gold * 2 < civs[civ].gold) {
                      local_1c--;
                    }
                    if (civs[civ].num_advances < civs[game.field_138].num_advances) {
                      if (aiStack_364[unit_type] + local_21c[unit_type] == 0) {
                        local_1c -= 3;
                      }
                      local_1c = local_1c -
                                 ((uint)civs[game.field_138].num_advances -
                                 (uint)civs[civ].num_advances);
                    }
                    local_1c = int_clamp(local_1c,civs[civ].units_active[unit_type] + 1,10);
                  }
                }
                if (local_23c != 0) {
                  local_1c = (int)local_1c / 2;
                }
                if (aiStack_364[unit_type] != 0) {
                  local_1c = 999;
                }
              }
              else {
                local_1c = int_clamp(10 - ((uint)civs[civ4].num_advances -
                                                   (uint)civs[civ].num_advances),2,10);
                if ((((*(byte *)&civs[civ].treaties[civ2] & 6) != 0) &&
                    (local_1c = local_1c + 1, aiStack_364[unit_type] != 0)) && (local_23c == 0)) {
                  local_1c = 999;
                }
                if (civs[civ4].military_strength <= civs[civ].military_strength) {
                  local_90 = local_b0;
                }
              }
              if (civs[civ].government == 3) {
                local_1c--;
              }
              if ((local_23c != 0) && ((int)local_1c < 0x14)) {
                for (improvement = 0x23; improvement < 0x26; improvement++) {
                  iVar6 = civ_has_advance(civ,(int)improvements[improvement].preq);
                  if ((iVar6 == 0) &&
                     (iVar6 = civ_has_advance(civ4,(int)improvements[improvement].preq),
                     iVar6 != 0)) {
                    local_90 = local_b0;
                    uVar8 = local_21c[unit_type] * 2 + 1;
                    if ((int)local_1c <= (int)uVar8) {
                      uVar8 = local_1c;
                    }
                    local_1c = uVar8;
                    if ((((local_21c[unit_type] == 0) &&
                         (*(char *)&civs[civ].units_active[unit_type] == '\0')) &&
                        (local_1c = uVar8 - 1, -0x26 < local_58)) && (local_58 < -0x22)) {
                      local_58 = unit_type;
                    }
                  }
                }
              }
            }
            goto LAB_0049e97a;
          }
        }
        else if (unit_types[unit_type].role == 7) {
          if ((cities[city].flags & 0x1000) == 0) {
            local_1c = 10;
            if ((char)cities[city].trade_routes < 3) {
              local_1c = 10 - ((5 - leaders[civs[civ].tribe].expand) * city_total_trade) / 10;
            }
            iVar6 = local_1c + (char)cities[city].trade_routes * 2;
            if (iVar6 < 3) {
              iVar6 = 2;
            }
            local_1c = iVar6 + (uint)civs[civ].continent_trade_units[local_fc];
            if (((1 << (civ5 & 0x1f) & (uint)game.human_players) == 0) ||
               ((cities[city].flags & 0x10) == 0)) goto LAB_0049e97a;
          }
        }
        else {
LAB_0049e97a:
          if ((int)local_1c < 400) {
            local_1c = (int)(((-(uint)(local_b0 == local_90) & 0xfffffff6) + 0x14) * local_1c * 3) /
                       (leaders[civs[civ].tribe].civilize + 3);
          }
          else {
            local_1c = 0x3fff;
          }
          iVar6 = city_has_improvement(city,2);
          if (iVar6 != 0) {
            local_1c += ((int)(local_1c + ((int)local_1c >> 0x1f & 3U)) >> 2);
          }
          if ((int)local_1c < local_30) {
            local_30 = local_1c;
            local_58 = unit_type;
          }
          if ((int)local_1c < local_20) {
            local_20 = local_1c;
            local_254 = unit_type;
          }
        }
      }
    }
LAB_0049ea4a:
    if (civs[civ].num_military_units < 0x200) {
      for (unit_type = 0; unit_type < 0x3e; unit_type++) {
        local_e8 = (uint)(char)unit_types[unit_type].role;
        if (((((((int)local_e8 < 6) &&
               (iVar6 = civ_can_build_unit(civ,city,unit_type), iVar6 != 0)) &&
              (unit_type != 0x2a)) &&
             ((local_e8 != 5 ||
              (((settler_food_cost <= local_220 ||
                (((city_settlers_supported == 0 &&
                  ((uint)civs[civ].units_active[0] + (uint)civs[civ].units_active[1] ==
                   local_120)) && (local_21c[1] + local_21c[0] < 2)))) &&
               (1 < cities[city].size)))))) &&
            (((unit_type != 2 || (civs[civ].government < 2)) &&
             (((char)unit_types[unit_type].attack < 'c' ||
              ((civs[civ].units_active[unit_type] < 4 &&
               (civs[civ].units_in_production[unit_type] < 2)))))))) &&
           ((local_e8 != 3 ||
            (((uint)civs[civ].units_active[0x1b] + (uint)civs[civ].units_in_production[0x1b] +
              (uint)civs[civ].units_active[0x1e] + (uint)civs[civ].units_in_production[0x1e] <
              (uint)civs[game.field_138].units_active[0x1c] +
              (uint)civs[game.field_138].units_active[0x1d] +
              (uint)civs[game.field_138].units_active[0x1f] + 2 &&
             (((*(byte *)&civs[civ].treaties[((uint)game.field_138)] & 4) == 0 ||
              ((uint)civs[civ].units_active[unit_type] +
               (uint)civs[civ].units_in_production[unit_type] == 0)))))))) {
          if ((1 << (civ5 & 0x1f) & (uint)game.human_players) != 0) {
            if (unit_type == 2) {
              iVar6 = civ_has_advance(civ,(int)unit_types[3].prerequisite);
            }
            else if (unit_type == 4) {
              iVar6 = civ_has_advance(civ,(int)unit_types[5].prerequisite);
            }
            else {
              if (unit_type != 0xf) goto LAB_0049eee7;
              iVar6 = civ_has_advance(civ,(int)unit_types[0x10].prerequisite);
              if (iVar6 != 0) goto LAB_0049ea9e;
              iVar6 = civ_has_advance(civ,(int)unit_types[0x11].prerequisite);
            }
            if (iVar6 != 0) goto LAB_0049ea9e;
          }
LAB_0049eee7:
          if (unit_type == 0x10) {
            iVar6 = civ_has_advance(civ,(int)unit_types[0x13].prerequisite);
            if (iVar6 == 0) {
              iVar6 = civ_has_advance(civ,(int)unit_types[0x12].prerequisite);
              goto joined_r0x0049ef35;
            }
          }
          else {
            if (unit_type == 0x11) {
              iVar6 = civ_has_advance(civ,(int)unit_types[0x13].prerequisite);
joined_r0x0049ef35:
              if (iVar6 != 0) goto LAB_0049ea9e;
            }
            if (unit_types[unit_type].domain == '\0') {
              local_1c = local_21c[unit_type] * 2 + aiStack_364[unit_type];
              if ((1 << (civ5 & 0x1f) & (uint)game.human_players) != 0) {
                local_1c = (int)local_1c / 2;
                if (((unit_type == 0xc) || (unit_type == 10)) || (unit_type == 9)) {
                  local_1c += 2;
                }
              }
              if (unit_type == 4) {
                local_1c = local_1c + local_21c[5] * 2 + aiStack_364[5];
              }
              if (leaders[civs[civ].tribe].attack < '\0') {
                if (unit_type == 0x13) {
                  local_1c = local_1c + local_21c[0x12] * 2 + aiStack_364[0x12];
                }
              }
              else if (unit_type == 0x12) {
                local_1c = local_1c + local_21c[0x13] * 2 + aiStack_364[0x13];
              }
              if ((unit_types[unit_type].role == '\0') && (unit_types[unit_type].attack == '\0')) {
                if ((local_f8 != 0) && (local_f8 != 1)) {
                  if (local_f8 == 4) {
                    local_374 = 1;
                  }
                  else {
                    local_374 = (*(short *)(&landmass_table + local_fc * 0x10) + 199) / 200;
                  }
                  if ((local_21c[unit_type] * 2 + aiStack_364[unit_type] <= local_374) &&
                     (civs[civ].units_active[unit_type] < 2)) goto LAB_0049f199;
                }
              }
              else {
LAB_0049f199:
                if (local_f8 == 4) {
                  local_d0 = 1 - (int)leaders[civs[civ].tribe].expand;
                  if (unit_types[unit_type].role != 5) {
                    local_d0 = local_d0 * 2;
                  }
                  if (local_34 != 0) {
                    local_d0 = (int)local_d0 / 2;
                  }
                  local_1c += local_d0;
                  if ((local_34 != 0) && (unit_types[unit_type].role == '\0')) {
                    local_d0 = (int)leaders[civs[civ].tribe].attack + 1;
                    iVar6 = civ_has_advance(civ,(int)unit_types[0x2b].prerequisite);
                    if (iVar6 != 0) {
                      local_d0 = local_d0 << 1;
                    }
                    local_1c = int_clamp(local_1c - local_d0,0,99);
                  }
                }
LAB_0049f3ea:
                if ((unit_types[unit_type].flags & 0x100) != 0) {
                  local_e8 = 0;
                }
                if ((local_80 != 0) &&
                   (((1 << (civ5 & 0x1f) & (uint)game.human_players) == 0 || (citypref_no_defend == 0))))
                {
                  if (local_e8 == 1) {
                    local_1c = (uint)(2 / (longlong)local_80);
                    if ((local_80 == 2) && (local_d8 < 2)) {
                      local_1c = -1;
                    }
                  }
                  else if (local_80 == 2) goto LAB_0049ea9e;
                }
                uVar8 = local_1c;
                if (((local_e8 != 1) && (local_e8 != 5)) &&
                   (uVar8 = local_1c << 1, local_f8 != local_e8)) {
                  uVar8 = local_1c << 2;
                }
                local_1c = uVar8;
                if (((unit_type != 9) ||
                    ((local_80 == 0 &&
                     ((civs[civ].continent_flags[local_fc] & 0x10) != 0)))) &&
                   ((unit_types[unit_type].domain != 2 ||
                    ((((iVar6 = city_adjacent_sea_info(city,0,0), iVar6 != 0x3f &&
                       ((cities[city].flags & 0x80) != 0)) && (iVar6 != 0)) &&
                     ((iVar10 = landmass_count_bordering(iVar6), 1 < iVar10 ||
                      (((local_e8 != 4 && (0x2f < *(short *)(&water_body_sizes + iVar6 * 0x10))) &&
                       (iVar6 < 0x3f)))))))))) {
                  if (local_e8 == 4) {
                    if (local_f8 == 4) {
                      local_1c = (int)(local_1c * 3) / 2;
                    }
                    else {
                      if ((local_f8 == 1) ||
                         (*(char *)&civs[civ].units_active[unit_type] != '\0'))
                      goto LAB_0049ea9e;
                      if (unit_type != 0x2b) {
                        local_1c = local_1c * 2 << ((byte)local_b0 & 0x1f);
                      }
                    }
                  }
                  if (local_e8 == 5) {
                    iVar6 = city_has_improvement(city,3);
                    if ((iVar6 == 0) && (iVar6 = civ_has_wonder(civ,0), iVar6 == 0)) {
                      local_378 = 6;
                    }
                    else {
                      local_378 = 4;
                    }
                    iVar3 = unit_type;
                    if (aiStack_364[unit_type] < (int)((civs[civ].government + 1) / 2)) {
                      cVar2 = leaders[civs[civ].tribe].civilize;
                    }
                    else {
                      cVar2 = leaders[civs[civ].tribe].expand;
                    }
                    local_1c = ((local_378 - cVar2) - local_100) * local_1c;
                    if (city_settlers_supported != 0) {
                      local_11c = 8;
                      if (cities[city].size < 4) {
                        local_11c = 0x10;
                      }
                      for (unit_type2 = 0; unit_type2 < city_settlers_supported; unit_type2++) {
                        local_1c += (unit_type2 + 1) * local_11c;
                      }
                    }
                    if (cities[city].size < 2) {
                      local_1c = local_1c << 1;
                    }
                    if ((aiStack_364[unit_type] == 0) && (settler_food_cost == local_220)) {
                      local_1c -= (int)local_1c / 2;
                    }
                    if (local_80 < 2) {
                      if (local_21c[unit_type] == 0) {
                        if (civs[civ].government < 5) {
                          if (1 < civs[civ].government) {
                            iVar6 = int_clamp((int)(uint)civs[civ].continent_cities[local_fc] >> 1,1,3);
                            if (aiStack_364[unit_type] < iVar6) {
                              local_1c = (int)local_1c / 2;
                            }
                            if (aiStack_364[unit_type] <
                                (int)(civs[civ].continent_cities[local_fc] / 5)) {
                              local_1c = (int)local_1c / 2;
                            }
                          }
                        }
                        else {
                          iVar6 = int_clamp(civs[civ].continent_cities[local_fc]
                                                     - 1,1,6);
                          if (aiStack_364[iVar3] < iVar6) {
                            local_1c = (int)local_1c / 2;
                          }
                          if (aiStack_364[unit_type] <
                              (int)(uint)civs[civ].continent_cities[local_fc] >> 2) {
                            local_1c = (int)local_1c / 2;
                          }
                        }
                      }
                      if (((aiStack_364[unit_type] == 0) && (local_21c[unit_type] == 0)) &&
                         (local_1c = (int)local_1c / 2, local_f8 != 4)) {
                        local_10 = leaders[civs[civ].tribe].expand + 3;
                        if (local_f8 == 1) {
                          local_10 = leaders[civs[civ].tribe].expand + 2;
                        }
                        if (local_f8 == 5) {
                          local_10++;
                        }
                        if ((int)(uint)civs[civ].continent_cities[local_fc] < local_10) {
                          local_1c = 0;
                        }
                      }
                    }
                  }
                  else {
                    local_1c = local_1c << 4;
                  }
                  local_1c = ((char)unit_types[unit_type].cost + 2) * local_1c;
                  if ((unit_types[unit_type].attack == '\0') &&
                     (unit_types[unit_type].defense == '\0')) {
                    local_1c = 0;
                  }
                  else {
                    if ((game.rules & 0x10) == 0) {
                      local_38 = 2;
                    }
                    else {
                      local_38 = int_clamp((int)(char)unit_types[unit_type].hit_points / 10
                                                    + (int)(char)unit_types[unit_type].firepower,2,4)
                      ;
                    }
                    local_25c = ((int)(char)unit_types[unit_type].attack +
                                (int)(char)unit_types[unit_type].defense) * local_38;
                    if ((unit_types[unit_type].flags & 0x400) != 0) {
                      local_25c++;
                    }
                    if (unit_type == 9) {
                      local_25c++;
                    }
                    local_1c = (int)local_1c /
                               ((((int)(char)unit_types[unit_type].move /
                                  (int)(uint)cosmic.road_move_mult + 1) * local_25c) / 2);
                  }
                  if (local_e8 == 2) {
                    if ((game.game_flags & 4) != 0) {
                      local_1c -= ((int)(local_1c + ((int)local_1c >> 0x1f & 3U)) >> 2);
                    }
                    if ((local_f8 == 4) && (0 < (int)local_1c)) {
                      local_1c -= ((int)(local_1c + ((int)local_1c >> 0x1f & 3U)) >> 2);
                    }
                    if (local_b0 == 0) {
                      local_1c = local_1c << 1;
                    }
                    else {
                      local_1c = local_1c << 2;
                    }
                    iVar6 = city_has_improvement(city,0x22);
                    if (iVar6 != 0) {
                      local_1c -= ((int)(local_1c + ((int)local_1c >> 0x1f & 3U)) >> 2);
                    }
                  }
                  if (unit_types[unit_type].domain == 1) {
                    local_1c = local_1c << 1;
                    iVar6 = city_has_improvement(city,0x20);
                    if (iVar6 != 0) {
                      local_1c -= ((int)(local_1c + ((int)local_1c >> 0x1f & 3U)) >> 2);
                    }
                  }
                  if (local_e8 == 1) {
                    local_1c -= (local_3c + 1 >> 1);
                  }
                  if (0x77 < local_124) {
                    local_1c = local_1c << 2;
                  }
                  if ((local_80 == 0) && ((int)local_e8 < 6)) {
                    local_11c = 0;
                    if ((city_shield_support != 0) && (city_total_shields != 0)) {
                      local_11c = (int)((3 - local_b0) * (city_shield_support + 1) * local_1c) /
                                  city_total_shields;
                    }
                    if (local_e8 == 5) {
                      if ((((uint)civs[civ].units_active[unit_type] - local_4c) +
                           local_21c[unit_type] == 0) &&
                         (3 - leaders[civs[civ].tribe].expand < (int)cities[city].size)) {
                        local_11c = 0;
                        if (city_total_shields <=
                            (int)((uint)(-1 < leaders[civs[civ].tribe].expand) + city_shield_support * 2)
                           ) {
                          local_1c -= (int)local_1c / 3;
                        }
                      }
                      else {
                        local_11c = local_11c / 2;
                      }
                    }
                    else if (((local_b0 == 0) && (city_total_shields <= city_support_unit_count)) ||
                            ((civs[civ].flags & 2) == 0)) {
                      local_1c = local_1c << 1;
                    }
                    local_1c += local_11c;
                  }
                  if (((local_e8 == 1) && ((1 << (civ5 & 0x1f) & (uint)game.human_players) != 0))
                     && (citypref_no_defend != 0)) {
                    local_1c = 999;
                  }
                  if (((int)local_1c < local_30) ||
                     (((local_58 < 0 && ((cities[city].flags & 1) == 0)) &&
                      ((1 < local_80 ||
                       (((local_264 != 0 && (local_d8 < 2)) &&
                        ((civs[civ].continent_flags[local_fc] & 0x10) != 0)))))))) {
                    local_30 = local_1c;
                    local_58 = unit_type;
                  }
                  if ((int)local_1c < local_26c) {
                    local_26c = local_1c;
                    local_240 = unit_type;
                  }
                }
              }
            }
            else if ((ushort)(((civs[civ].continent_cities[local_fc] < 2) - 1 & 4) + 4) <=
                     civs[civ].continent_military[local_fc]) {
              local_1c = (int)(((uint)civs[civ].units_active[unit_type] +
                               (uint)civs[civ].units_in_production[unit_type] * 2) *
                              (uint)civs[civ].continent_military[local_fc]) /
                         (local_124 + 1);
              if (((unit_types[unit_type].flags & 0x4000) != 0) &&
                 (local_1c = local_1c - civs[game.field_138].units_active[0x29], (int)local_1c < 1))
              {
                local_1c = 0;
              }
              goto LAB_0049f3ea;
            }
          }
        }
LAB_0049ea9e: ;
      }
    }
    else if (local_58 == 999) {
      local_58 = -0x26;
    }
  }
  else if (local_58 == 999) {
    local_58 = -0x26;
  }
  if (param_3 != 0) {
    *(iptr *)param_3 = local_254;
  }
  if (param_2 != 0) {
    *(iptr *)param_2 = local_240;
  }
  if (((1 << (civ5 & 0x1f) & (uint)game.human_players) == 0) ||
     ((cities[city].flags & 0x10) == 0)) {
    if (((1 << (civ5 & 0x1f) & (uint)game.human_players) == 0) && (cities[city].building == -1))
    {
      local_58 = -1;
    }
    else if ((local_58 < -0x26) && (iVar6 = city_has_improvement(city,4), iVar6 == 0)) {
      local_58 = -4;
    }
    else if ((cities[city].building < -0x26) &&
            (((local_f0 == 0 && (-0x27 < local_58)) && ((cities[city].flags & 0x2000) == 0)))) {
      if (cities[city].building < 1) {
        local_380 = ~(int)cities[city].building + 1;
      }
      else {
        local_380 = (iptr)cities[city].building;
      }
      local_74 = local_380 - 0x27;
      if (((local_80 < 2) && (iVar6 = wonder_is_expired(local_74), iVar6 == 0)) &&
         ((game.wonder_city[local_74] == -1 &&
          ((local_264 == 0 || ((cities[city].flags & 0x20) == 0)))))) {
        uVar7 = 1;
        unit2 = tile_first_unit((int)cities[city].x,(int)cities[city].y);
        iVar6 = unit_stack_count_role(unit2,uVar7);
        if (1 < iVar6) {
          local_58 = (iptr)cities[city].building;
        }
      }
    }
  }
  else if ((cities[city].flags & 0x1000000) == 0) {
    if ((cities[city].flags & 0x2000000) == 0) {
      if (500 < local_30) {
        local_58 = 99;
      }
    }
    else if ((0x62 < local_254) || (local_58 = local_254, 500 < local_20)) {
      local_58 = 99;
    }
  }
  else if ((0x62 < local_240) || (local_58 = local_240, 500 < local_26c)) {
    local_58 = 99;
  }
  return local_58;
}
#undef city_aggressive_units
#undef city_happy_count
#undef city_shield_rows
#undef city_shield_support
#undef city_support_unit_count
#undef city_total_shields
#undef city_total_trade
#undef city_trade_corruption
#undef city_unhappy_count
#undef city_yield_totals
#undef citypref_no_defend
#undef settler_food_cost
#undef local_380
#undef local_378
#undef local_374
#undef local_370
#undef aiStack_364
#undef local_26c
#undef local_268
#undef local_264
#undef local_260
#undef local_25c
#undef unit
#undef local_254
#undef local_250
#undef local_24c
#undef local_248
#undef improvement
#undef local_240
#undef local_23c
#undef local_238
#undef local_234
#undef local_230
#undef local_22c
#undef civ3
#undef city2
#undef local_220
#undef local_21c
#undef local_124
#undef local_120
#undef local_11c
#undef local_118
#undef local_114
#undef local_110
#undef local_10c
#undef local_108
#undef local_104
#undef local_100
#undef local_fc
#undef local_f8
#undef unit_type
#undef local_f0
#undef y2
#undef local_e8
#undef local_e4
#undef local_e0
#undef x2
#undef local_d8
#undef local_d4
#undef local_d0
#undef auStack_cc
#undef local_b0
#undef local_ac
#undef local_a8
#undef local_a4
#undef local_a0
#undef local_9c
#undef local_98
#undef local_94
#undef local_90
#undef local_8c
#undef local_88
#undef unit3
#undef local_80
#undef terrain2
#undef local_78
#undef local_74
#undef civ2
#undef local_6c
#undef local_68
#undef local_64
#undef local_60
#undef local_5c
#undef local_58
#undef local_54
#undef unit_type2
#undef local_4c
#undef local_48
#undef civ4
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

/* 004bb8e0 auto */
#define unit_blink_active (*(i8 *)((u8 *)&g.d_0062804c))
#define local_1190 (*(C_004083b0_430 (*)[4])(frame_ + FRAME_OFF(0)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(4480)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4484)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(4488)))
void __cdecl wonder_show_movie(iptr param_1)

{
  i32 uStackY_24;
  i8 frame_[FRAME_OFF(4496)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  snd_wave_stop_all();
  wonder_movie_wnd_ctor((FrameWindow *)local_1190);
  local_8 = 0;
  unit_blink_active = 0;
  snd_cd_stop();
  uStackY_24 = 0x4bb937;
  wonder_movie_wnd_create((FrameWindow *)local_1190,param_1);
  wonder_movie_wnd_play(local_1190);
  snd_wave_stop_all();
  snd_sync_music_option();
  if (game_language != 0) {
    uStackY_24 = 0x4bb96a;
    pedia_show_improvement_modal((C_004083b0_a28 *)&pedia_window,param_1 + 0x27);
  }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_004bb97b */ { wonder_movie_wnd_dtor((WonderMovieWindow *)((iptr)&local_1190)); }
  return;
}
#undef unit_blink_active
#undef local_1190
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004bb99f auto */
#define wonder_movie_wnd (*(FrameWindow * *)((u8 *)&g.d_006a1864))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
FrameWindow * __thiscall wonder_movie_wnd_ctor(FrameWindow *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  frame_wnd_ctor((SurfaceWindow *)this);
  local_8 = 0;
  mmwnd_ctor((C_004083b0_a28 *)&this->field_2d8);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  surface_ctor((DibSurface *)(this[4].pad_15c + 0x18));
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),2);
  palette_init((GamePalette *)this[4].pad_1bc);
  this->vtable = (u32)&PTR_FUN_0061d6c8;
  wonder_movie_wnd = this;
  return this;
}
#undef wonder_movie_wnd
#undef local_10
#undef puStack_c
#undef local_8

/* 004bba79 auto */
#define wonder_movie_wnd (*(i32 *)((u8 *)&g.d_006a1864))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __thiscall wonder_movie_wnd_dtor(WonderMovieWindow *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  *(i8 ***)this->pad_0 = &PTR_FUN_0061d6c8;
  (*(i32 *)((char *)&local_8 + 1)) = 0;
  wonder_movie_wnd = 0;
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  /* inlined unwind funclet FUN_004bbaf1 */ { palette_destroy((GamePalette *)(*(int *)((iptr)&this) + 0xd4c)); }
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  /* inlined unwind funclet FUN_004bbb00 */ { surface_dtor((DibSurface *)(*(int *)((iptr)&this) + 0xd04)); }
  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
  /* inlined unwind funclet FUN_004bbb0f */ { avi_player_dtor((AviPlayer *)(*(int *)((iptr)&this) + 0x2d8)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_004bbb1e */ { frame_wnd_dtor(*(DibSurface **)((iptr)&this)); }
  return;
}
#undef wonder_movie_wnd
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004bbb3f auto */
#define local_134 (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_124 (*(DllHandle *)(frame_ + FRAME_OFF(20)))
#define local_120 (*(DibSurface *)(frame_ + FRAME_OFF(24)))
#define local_d8 (*(i32 *)(frame_ + FRAME_OFF(96)))
#define local_d4 (*(SIZE_T *)(frame_ + FRAME_OFF(100)))
#define local_d0 (*(Sprite *)(frame_ + FRAME_OFF(104)))
#define local_94 (*(i8 (*)[128])(frame_ + FRAME_OFF(164)))
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(292)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(296)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(300)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(304)))
void __thiscall wonder_movie_wnd_create(FrameWindow *this,int param_1)

{
  int iVar1;
  i32 uVar2;
  iptr iVar3;
  i32 uVar4;
  i32 uVar5;
  i32 uVar6;
  i32 uVar7;
  i32 uVar8;
  i32 uVar9;
  i32 uVar10;
  i32 uVar11;
  i8 frame_[FRAME_OFF(312)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  local_14 = 0x140;
  local_d8 = 0xf0;
  sprite_init(&local_d0);
  local_8 = 0;
  surface_ctor(&local_120);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  local_d4 = GlobalCompact(0x100000);
  str_clear((iptr)local_94);
  str_append((iptr)local_94,ADDR(0x62da84, ((u8 *)&g.d_0062da84)));
  iVar1 = file_resolve_path((iptr)local_94);
  if (iVar1 == 0) {
    surface_create((DibSurface *)(this[4].pad_15c + 0x18),0x40,0x20);
    surface_fill((DibSurface *)(this[4].pad_15c + 0x18),0x21);
  }
  else {
    resource_dll_load(&local_124,(iptr)local_94);
    local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),2);
    iVar1 = surface_load_gif_resource(&local_120,param_1 + 20000,10,0xec,(iptr)this[4].pad_1bc);
    if (iVar1 == 0) {
      MessageBoxA((HWND)0x0,s_Failed_to_load_civ2art_gif_0062da9c,s_NOTICE_0062da94,0x40);
    }
    else {
      sprite_grab_from_surface(&local_d0,(iptr)&local_120,2,1,1,0x40,0x20);
      surface_create((DibSurface *)(this[4].pad_15c + 0x18),0x40,0x20);
      sprite_draw(&local_d0,(iptr)local_134,(iptr)(this[4].pad_15c + 0x18),0,0);
      sprite_free(&local_d0);
      surface_release(&local_120);
    }
    dll_handle_free(&local_124);
    (*(i8 *)((char *)&local_8 + 0)) = 1;
    /* inlined unwind funclet FUN_004bbdbd */ { dll_free((DllHandle *)((iptr)&local_124)); }
  }
  *(int *)(this[4].pad_15c + 0x14) = param_1;
  uVar10 = 0;
  uVar9 = 0;
  uVar8 = 0;
  uVar6 = 0;
  uVar5 = 0;
  uVar4 = 0xc;
  uVar11 = local_14;
  uVar7 = local_d8;
  uVar2 = label_string(improvements[*(int *)(this[4].pad_15c + 0x14) + 0x27].name);
  frame_wnd_create(this,uVar2,uVar4,uVar5,uVar6,uVar11,uVar7,uVar8,uVar9,uVar10);
  wnd_set_palette((WndBase *)this->pad_48,(iptr)this[4].pad_1bc);
  uVar11 = 0;
  iVar3 = surface_get_rect((DibSurface *)this);
  surface_fill_rect((DibSurface *)this,iVar3,uVar11);
  wonder_movie_wnd_draw_caption(this);
  wnd_repaint((SurfaceWindow *)this);
  wnd_center((WndCenterView *)this->pad_48);
  wnd_set_lbuttonup_handler((C_00408130 *)(this->pad_48 + 0x10),ADDR(0x4025bd, wonder_movie_on_lbuttonup));
  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
  /* inlined unwind funclet FUN_004bbdc9 */ { surface_dtor((DibSurface *)((iptr)&local_120)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_004bbdd5 */ { sprite_destroy((Sprite *)((iptr)&local_d0)); }
  return;
}
#undef local_134
#undef local_124
#undef local_120
#undef local_d8
#undef local_d4
#undef local_d0
#undef local_94
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004bbdfb auto */
#define local_88 (*(i8 (*)[128])(frame_ + FRAME_OFF(0)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(128)))
void __thiscall wonder_movie_wnd_play(C_004083b0_430 *this)

{
  int iVar1;
  i8 frame_[FRAME_OFF(136)] __attribute__((aligned(8)));  /* original stack frame */
  
  wonder_movie_wnd_resize((FrameWindow *)this);
  if (((game.game_flags & 0x40) == 0) && ((game.game_flags & 0x80) == 0)) {
    str_clear((iptr)local_88);
    str_append((iptr)local_88,ADDR(0x62dab8, ((u8 *)&g.d_0062dab8)));
    if (*(int *)(this[3].pad_48 + 0x28) < 10) {
      str_append_int((iptr)local_88,0);
    }
    str_append_int((iptr)local_88,*(i32 *)(this[3].pad_48 + 0x28));
    str_concat((iptr)local_88,ADDR(0x62dacc, ((u8 *)&g.d_0062dacc)));
    iVar1 = file_resolve_path((iptr)local_88);
    if (iVar1 != 0) {
      wnd_set_lbuttonup_handler((C_00408130 *)(this->pad_48 + 0x10),ADDR(0x4025bd, wonder_movie_on_lbuttonup));
      wnd_set_keydown_handler((C_00408130 *)(this->pad_48 + 0x10),ADDR(0x40392c, wonder_movie_on_key));
      avi_player_create_child
                ((C_004083b0_61c *)&this->field_2d8,ADDR(0x62dad4, ((u8 *)&g.d_0062dad4)),0x200,this->border_width,this->caption_height,
                 (iptr)this);
      local_8 = avi_player_open((AviPlayerOpenView *)&this->field_2d8,(iptr)local_88);
      if (local_8 == 0) {
        avi_player_set_end_callback((AviPlayerEndCbSetView *)&this->field_2d8,ADDR(0x402e46, wonder_movie_on_video_end));
        wnd_set_lbuttonup_handler((C_00408130 *)&this->field_330,ADDR(0x4025bd, wonder_movie_on_lbuttonup));
        avi_player_set_palette((DibSurface *)&this->field_2d8,(iptr)(this[3].pad_48 + 0x74))
        ;
        wnd_set_palette
                  ((WndBase *)&this->field_320,(iptr)(this[3].pad_48 + 0x74));
        screen_fade_out();
        wnd_set_palette
                  ((WndBase *)&main_frame_wnd,(iptr)(this[3].pad_48 + 0x74));
        window_show((C_004083b0_4 *)this);
        window_show((C_004083b0_4 *)&this->field_2d8);
        wnd_flush_paint();
        avi_player_play((AviPlayerPlayView *)&this->field_2d8);
        if (2 < game.multiplayer) {
          wnd_set_modal_idle_callback((C_00408010_b8 *)this->pad_48,ADDR(0x403585, net_modal_idle_poll));
        }
        wnd_run_modal_loop((C_00408010_b8 *)this->pad_48);
        wnd_set_modal_idle_callback((C_00408010_b8 *)this->pad_48,0);
        snd_wave_stop_all();
        wnd_hide((WndBase *)&this->field_320);
        wnd_flush_paint();
        wnd_set_palette((WndBase *)&main_frame_wnd,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
        wnd_hide((WndBase *)this->pad_48);
        wnd_flush_paint();
        screen_fade_in();
      }
      else if (local_8 == -0x7ffbfeac) {
        popup_game(ADDR(0x62dad8, ((u8 *)&g.d_0062dad8)));
      }
    }
  }
  return;
}
#undef local_88
#undef local_8

/* 004bc0d3 auto */
void __thiscall wonder_movie_wnd_draw_caption(FrameWindow *this)

{
  frame_set_border_tile((iptr)(this[4].pad_15c + 0x18));
  frame_wnd_draw_caption(this);
  frame_set_border_tile(ADDR(0x647f18, ((u8 *)&g.d_00647f18)));
  return;
}

/* 004bc10f auto */
void __thiscall wonder_movie_wnd_resize(FrameWindow *this)

{
  iptr iVar1;
  i32 uVar2;
  
  wnd_resize_clamped
            ((C_004083b0_4 *)this,this->border_width * 2 + 0x140,
             this->caption_height + this->border_width + 0xf0);
  frame_wnd_layout(this);
  uVar2 = 0;
  iVar1 = surface_get_rect((DibSurface *)this);
  surface_fill_rect((DibSurface *)this,iVar1,uVar2);
  wnd_repaint((SurfaceWindow *)this);
  wnd_center((WndCenterView *)this->pad_48);
  wnd_flush_paint();
  return;
}

/* 004bc193 auto */
#define wonder_movie_wnd (*(int *)((u8 *)&g.d_006a1864))
void __cdecl wonder_movie_on_video_end(void)

{
  wnd_end_modal_loop((C_00408010_b8 *)(wonder_movie_wnd + 0x48));
  return;
}
#undef wonder_movie_wnd

/* 004bc1b1 auto */
#define wonder_movie_wnd (*(int *)((u8 *)&g.d_006a1864))
void __cdecl wonder_movie_on_lbuttonup(void)

{
  wnd_end_modal_loop((C_00408010_b8 *)(wonder_movie_wnd + 0x48));
  return;
}
#undef wonder_movie_wnd

/* 004bc1cf auto */
#define wonder_movie_wnd (*(int *)((u8 *)&g.d_006a1864))
void __cdecl wonder_movie_on_key(int param_1)

{
  if ((0xcf < param_1) && (param_1 < 0xd3)) {
    wnd_end_modal_loop((C_00408010_b8 *)(wonder_movie_wnd + 0x48));
  }
  return;
}
#undef wonder_movie_wnd

/* 004c03ae auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
i32 __cdecl city_can_build_improvement(iptr civ,iptr city,iptr improvement)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  if (improvement < 0x27) {
    iVar1 = civ_has_advance(civ,(int)improvements[improvement].preq);
    if (iVar1 != 0) {
      if (city < 0) {
        local_8 = 1;
      }
      else {
        iVar1 = city_has_improvement(city,improvement);
        if (((((iVar1 == 0) &&
              (((improvement != 0x1e && (improvement != 0x1f)) || ((cities[city].flags & 0x80) != 0))))
             && (((improvement != 0x22 && (improvement != 0x1c)) ||
                 (((cities[city].flags & 0x200000) != 0 && ((cities[city].flags & 0x80) != 0))
                 )))) &&
            ((((improvement != 3 || (iVar1 = civ_has_wonder(civ,0), iVar1 == 0)) &&
              ((improvement != 0xb || (iVar1 = civ_has_wonder(civ,10), iVar1 == 0)))) &&
             ((improvement != 7 || (iVar1 = city_has_improvement(city,1), iVar1 == 0)))))) &&
           (((((improvement != 10 ||
               ((iVar1 = city_has_improvement(city,5), iVar1 != 0 &&
                (iVar1 = civ_has_advance(civ,(int)improvements[5].preq), iVar1 != 0)))) &&
              ((improvement != 0x16 ||
               ((iVar1 = city_has_improvement(city,10), iVar1 != 0 &&
                (iVar1 = civ_has_advance(civ,(int)improvements[10].preq), iVar1 != 0)))))) &&
             (((improvement != 0xc ||
               ((iVar1 = city_has_improvement(city,6), iVar1 != 0 &&
                (iVar1 = civ_has_advance(civ,(int)improvements[6].preq), iVar1 != 0)))) &&
              (((improvement != 0x1a ||
                (((iVar1 = civ_has_wonder(civ,0x1a), iVar1 == 0 &&
                  (iVar1 = city_has_improvement(city,0xc), iVar1 != 0)) &&
                 (iVar1 = civ_has_advance(civ,(int)improvements[0xc].preq), iVar1 != 0)))) &&
               ((improvement != 0x17 || (iVar1 = city_has_improvement(city,9), iVar1 != 0)))))))) &&
            ((((improvement != 0x21 || (iVar1 = civ_has_wonder(civ,0x15), iVar1 == 0)) &&
              ((((improvement != 0x10 ||
                 ((iVar1 = city_has_improvement(city,0xf), iVar1 != 0 &&
                  (iVar1 = civ_has_advance(civ,(int)improvements[0xf].preq), iVar1 != 0))))
                && ((improvement != 0x14 || ((cities[city].flags & 0x800) != 0)))) &&
               (((((improvement != 0x13 && (improvement != 0x14)) && (improvement != 0x1d)) && (improvement != 0x15)
                 ) || (((iVar1 = city_has_improvement(city,0xf), iVar1 != 0 ||
                        (iVar1 = city_has_improvement(city,0x10), iVar1 != 0)) &&
                       ((improvement == 0x1d ||
                        ((((iVar1 = civ_has_wonder(civ,0x16), iVar1 == 0 &&
                           (iVar1 = city_has_improvement(city,0x14), iVar1 == 0)) &&
                          ((iVar1 = city_has_improvement(city,0x15), iVar1 == 0 ||
                           (improvement == 0x14)))) &&
                         (iVar1 = city_has_improvement(city,0x1d), iVar1 == 0)))))))))))) &&
             (((improvement < 0x23 || (0x25 < improvement)) ||
              ((((game.rules & 0x80) == 0 && (game.wonder_city[0x19] != -1)) &&
               (((0 < game.year || ((game.game_flags & 0x80) != 0)) &&
                (iVar1 = civ_spaceship_launched(civ), iVar1 == 0)))))))))))) {
          local_8 = 1;
        }
      }
    }
  }
  else {
    local_8 = civ_can_build_wonder(civ,improvement - 0x27);
  }
  return local_8;
}
#undef local_8

/* 004c66ba auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define unit (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(24)))
void __cdecl city_incite_transfer(iptr city,iptr civ,i32 param_3)

{
  char *pcVar1;
  byte civ3;
  short x2;
  short y2;
  int civ2;
  iptr x;
  int y;
  int iVar8;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ3 = cities[city].owner;
  civ2 = (int)(char)civ3;
  x2 = cities[city].x;
  y2 = cities[city].y;
  if (-1 < civ) {
    net_batch_begin();
    for (local_8 = 0; local_8 < 0x15; local_8++) {
      x = map_wrap_x((int)(char)(&city_tile_dx_table)[local_8] + (int)x2);
      y = (int)(char)(&city_tile_dy_table)[local_8] + (int)y2;
      iVar8 = map_in_bounds(x,y);
      if (iVar8 != 0) {
        tile_set_visible(x,y,1 << ((byte)civ & 0x1f),1,1);
        tile_update_known(x,y,civ);
      }
    }
    net_batch_flush();
    if ((autoplay_active == 0) &&
       (((((((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0 ||
            ((1 << (civ3 & 0x1f) & (uint)game.human_players) != 0)) ||
           ((*(byte *)&civs[human_civ].treaties[civ] & 0x80) != 0)) ||
          ((y = civ_has_wonder(human_civ,0x18), y != 0 ||
           (y = civ_has_wonder(human_civ,9), y != 0)))) ||
         (((*(byte *)&civs[human_civ].treaties[civ2] & 0x80) != 0 ||
          ((y = civ_has_wonder(human_civ,0x18), y != 0 ||
           (y = civ_has_wonder(human_civ,9), y != 0)))))) ||
        (game.reveal_map != '\0')))) {
      if (((game.reveal_map != '\0') ||
          ((1 << ((byte)human_civ & 0x1f) & (int)(char)cities[city].known_to) != 0)) ||
         ((int)cities[city].owner == (human_civ & 0xffU))) {
        mapviews_ensure_visible((int)cities[city].x,(int)cities[city].y,(int)cities[city].owner)
        ;
      }
      x = civ_name_plural(civ2);
      text_set_string_arg(0,x);
      text_set_string_arg(1,(iptr)&cities[city].name);
      x = civ_get_adjective(civ);
      text_set_string_arg(2,x);
      popup_game(ADDR(0x62dd84, ((u8 *)&g.d_0062dd84)));
      if (((1 << (civ3 & 0x1f) & (uint)game.human_players) != 0) && (2 < game.multiplayer)) {
        net_send_text_args(0x5e,*(i32 *)
                                 (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),3,0,0,
                           0);
      }
    }
    unit = (iptr)game.num_units;
    while (unit = unit - 1, -1 < unit) {
      if (((units[unit].id != 0) && (units[unit].owner == civ2)) &&
         ((y = map_distance_diag((int)units[unit].x,(int)units[unit].y,(int)x2,
                                      (int)y2), y < 2 &&
          ((y == 0 ||
           (iVar8 = tile_city_owner((int)units[unit].x,(int)units[unit].y), iVar8 < 0))))))
      {
        pcVar1 = (char *)(units[unit].type + ADDR(0x64c778, ((u8 *)&civs + 216)) + civ2 * 0x594);
        *pcVar1 = *pcVar1 - 1;
        pcVar1 = (char *)(units[unit].type + ADDR(0x64c778, ((u8 *)&civs + 216)) + civ * 0x594);
        *pcVar1 = *pcVar1 + 1;
        units[unit].owner = (byte)civ;
        units[unit].home_city = (i8)city;
        units[unit].moves_used = '\0';
        if ((units[unit].orders != 1) && (units[unit].orders != 2)) {
          units[unit].orders = -1;
        }
        tile_set_owner((int)units[unit].x,(int)units[unit].y,civ,1);
        if (y != 0) {
          map_redraw_tile_all_views((int)units[unit].x,(int)units[unit].y);
        }
      }
    }
    city_capture_aftermath(city,civ,param_3);
  }
  return;
}
#undef autoplay_active
#undef human_civ
#undef unit
#undef local_8

/* 004d8bc0 auto */
#define improvement (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl impr_editor_load_rules(void)

{
  char *_Source;
  size_t _Count;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (improvement = 0; improvement < 0x43; improvement++) {
    _Count = 0x28;
    _Source = (char *)label_string(improvements[improvement].name);
    _strncpy(&editor_item_names + improvement * 0x28,_Source,_Count);
    (&editor_item_name_ends)[improvement * 0x28] = 0;
    *(uint *)(&editor_items + improvement * 0x58) = (uint)improvements[improvement].cost;
    *(uint *)(&editor_item_field1 + improvement * 0x58) = (uint)improvements[improvement].upkeep;
    *(int *)(&editor_item_field2 + improvement * 0x58) = (int)improvements[improvement].preq;
    if (0x27 < improvement) {
      *(int *)(&editor_item_field3 + improvement * 0x58) = (int)(char)(&wonder_expires_by_impr)[improvement];
    }
  }
  return;
}
#undef improvement

/* 004d8caa auto */
#define improvement (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl impr_editor_store_rules(void)

{
  char *_Dest;
  char *_Source;
  size_t _Count;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (improvement = 0; improvement < 0x43; improvement++) {
    _Count = 0x19;
    _Source = &editor_item_names + improvement * 0x28;
    _Dest = (char *)label_string(improvements[improvement].name);
    _strncpy(_Dest,_Source,_Count);
    improvements[improvement].cost = (&editor_items)[improvement * 0x58];
    improvements[improvement].upkeep = (&editor_item_field1)[improvement * 0x58];
    improvements[improvement].preq = (&editor_item_field2)[improvement * 0x58];
    if (0x27 < improvement) {
      (&wonder_expires_by_impr)[improvement] = (&editor_item_field3)[improvement * 0x58];
    }
  }
  return;
}
#undef improvement

/* 004d8d80 auto */
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(char (*)[8])(frame_ + FRAME_OFF(8)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl impr_editor_load_controls(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_14 = 1; local_14 < 5; local_14++) {
    if (*(int *)(&impr_editor_ctrl_kinds + local_14 * 8) == 9) {
      iVar1 = ctrl_get_id
                        ((ControlIdView *)
                         (*(int *)(&impr_editor_ctrl_slots + local_14 * 8) * 0x48 + 0x44c + active_editor_wnd));
      _sprintf(local_10,&impr_editor_value_fmt,
               *(i32 *)(&editor_ctrl_values + iVar1 * 4 + *(int *)(active_editor_wnd + 0x2ec) * 0x58));
      ctrl_set_text
                ((ControlTextView *)
                 (*(int *)(&impr_editor_ctrl_slots + local_14 * 8) * 0x48 + 0x44c + active_editor_wnd),
                 (iptr)local_10);
    }
    else if (*(int *)(&impr_editor_ctrl_kinds + local_14 * 8) == 0xc) {
      iVar1 = ctrl_get_id
                        ((ControlIdView *)
                         (active_editor_wnd + 0x2fc + *(int *)(&impr_editor_ctrl_slots + local_14 * 8) * 0x38));
      local_8 = *(int *)(&editor_ctrl_values + iVar1 * 4 + *(int *)(active_editor_wnd + 0x2ec) * 0x58) + 2;
      combo_set_cur_sel
                ((ComboBoxSetSelView *)
                 (active_editor_wnd + 0x2fc + *(int *)(&impr_editor_ctrl_slots + local_14 * 8) * 0x38),local_8);
    }
  }
  return;
}
#undef local_14
#undef local_10
#undef local_8

/* 004d8ed6 auto */
#define local_18 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(char (*)[8])(frame_ + FRAME_OFF(8)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
int __cdecl impr_editor_save_controls(void)

{
  int iVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_14 = 0;
  for (local_18 = 1; local_18 < 5; local_18++) {
    if (*(int *)(&impr_editor_ctrl_kinds + local_18 * 8) == 9) {
      ctrl_get_text
                ((ControlTextView *)
                 (*(int *)(&impr_editor_ctrl_slots + local_18 * 8) * 0x48 + 0x44c + active_editor_wnd),
                 (iptr)local_10);
      iVar1 = ctrl_get_id
                        ((ControlIdView *)
                         (*(int *)(&impr_editor_ctrl_slots + local_18 * 8) * 0x48 + 0x44c + active_editor_wnd));
      iVar1 -= 0xca;
      local_8 = _atoi(local_10);
      uVar2 = int_clamp(local_8,*(i32 *)(&impr_editor_field_min_table + iVar1 * 4),
                                 *(i32 *)(&impr_editor_field_max_table + iVar1 * 4));
      *(i32 *)(&editor_items + *(int *)(active_editor_wnd + 0x2ec) * 0x58 + iVar1 * 4) = uVar2;
      if (*(int *)(&editor_items + *(int *)(active_editor_wnd + 0x2ec) * 0x58 + iVar1 * 4) != local_8) {
        local_14++;
      }
    }
    else if (*(int *)(&impr_editor_ctrl_kinds + local_18 * 8) == 0xc) {
      local_8 = combo_get_cur_sel
                          ((ComboBoxGetSelView *)
                           (active_editor_wnd + 0x2fc + *(int *)(&impr_editor_ctrl_slots + local_18 * 8) * 0x38));
      local_8 -= 2;
      iVar1 = ctrl_get_id
                        ((ControlIdView *)
                         (active_editor_wnd + 0x2fc + *(int *)(&impr_editor_ctrl_slots + local_18 * 8) * 0x38));
      *(int *)(&editor_ctrl_values + *(int *)(active_editor_wnd + 0x2ec) * 0x58 + iVar1 * 4) = local_8;
    }
  }
  return local_14;
}
#undef local_18
#undef local_14
#undef local_10
#undef local_8

/* 004d9095 auto */
void __cdecl impr_editor_redraw(void)

{
  impr_editor_paint((C_004083b0_430 *)active_editor_wnd);
  return;
}

/* 004d90b0 auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define local_c (*(size_t *)(frame_ + FRAME_OFF(4)))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(8)))
i32 __cdecl impr_editor_write_section(FILE *param_1)

{
  char *pcVar1;
  size_t sVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (improvement = 0; improvement < 0x43; improvement++) {
    text_clear();
    text_append_string_id(improvements[improvement].name);
    FUN_005f22e0(&text_buffer,&rules_improve_name_sep_str);
    pcVar1 = (char *)label_string(improvements[improvement].name);
    sVar2 = _strlen(pcVar1);
    if (sVar2 < 0x19) {
      pcVar1 = (char *)label_string(improvements[improvement].name);
      local_c = _strlen(pcVar1);
    }
    else {
      local_c = 0x19;
    }
    text_append_spaces(0x19 - local_c);
    text_append_int_2d((uint)improvements[improvement].cost);
    FUN_005f22e0(&text_buffer,&rules_improve_cost_sep_str);
    text_append_int_2d((uint)improvements[improvement].upkeep);
    FUN_005f22e0(&text_buffer,s___0062e404);
    text_append_advance_abbrev((int)improvements[improvement].preq,1);
    FUN_005f22e0(&text_buffer,&rules_improve_line_end_str);
    _fputs(&text_buffer,param_1);
  }
  return 1;
}
#undef text_buffer
#undef local_c
#undef improvement

/* 004d91f8 auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(0)))
i32 __cdecl impr_editor_write_endwonder(FILE *param_1)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (improvement = 0x27; improvement < 0x43; improvement++) {
    text_clear();
    text_append_advance_abbrev((int)(char)(&wonder_expires_by_impr)[improvement],1);
    text_append_spaces(8);
    FUN_005f22e0(&text_buffer,&rules_endwonder_comment_sep_str);
    text_append_string_id(improvements[improvement].name);
    FUN_005f22e0(&text_buffer,&rules_endwonder_line_end_str);
    _fputs(&text_buffer,param_1);
  }
  return 1;
}
#undef text_buffer
#undef improvement

/* 004d929a auto */
#define editor_running (*(i32 *)((u8 *)&g.d_006a1d7c))
#define local_28 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_24 (*(char (*)[32])(frame_ + FRAME_OFF(4)))
void __cdecl impr_editor_on_ok(void)

{
  iptr iVar1;
  HWND hWnd;
  iptr iVar2;
  int iVar3;
  char *lpText;
  char *lpCaption;
  UINT uType;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = impr_editor_save_controls();
  if (iVar1 == 0) {
    impr_editor_store_rules();
    rules_edit_set_section(ADDR(0x62e420, ((u8 *)&g.d_0062e420)),ADDR(0x4016f9, impr_editor_write_section));
    rules_edit_add_section(ADDR(0x62e428, ((u8 *)&g.d_0062e428)),ADDR(0x402ef5, impr_editor_write_endwonder));
    iVar2 = rules_write_sections();
    if (iVar2 == 0) {
      _sprintf(local_24,s_Error_updating_RULES__s_0062e434,&lang_file_ext);
      uType = 0x10;
      lpCaption = s_File_I_O_Error_0062e44c;
      lpText = local_24;
      iVar3 = wnd_get_window((WndBase *)(active_editor_wnd + 0x48));
      MessageBoxA(*(HWND *)(iVar3 + 4),lpText,lpCaption,uType);
    }
    editor_running = 0;
    wnd_end_modal_loop((C_00408010_b8 *)(active_editor_wnd + 0x48));
    menu_update_states();
  }
  else {
    impr_editor_load_controls();
    impr_editor_redraw();
    if (active_editor_wnd == 0) {
      local_28 = 0;
    }
    else {
      local_28 = active_editor_wnd + 0x48;
    }
    dlg_set_parent_window(local_28);
    popup_text(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x62e418, ((u8 *)&g.d_0062e418)));
    dlg_set_parent_window(0);
    hWnd = (HWND)control_get_hwnd((ControlHwndView *)(active_editor_wnd + 0x2fc));
    SetFocus(hWnd);
  }
  return;
}
#undef editor_running
#undef local_28
#undef local_24

/* 004d93b9 auto */
#define local_12c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_128 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_124 (*(char (*)[20])(frame_ + FRAME_OFF(12)))
#define local_110 (*(char (*)[4])(frame_ + FRAME_OFF(32)))
#define local_10c (*(i8 *)(frame_ + FRAME_OFF(36)))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(292)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(296)))
void __cdecl impr_editor_on_rename(void)

{
  int iVar1;
  size_t sVar2;
  i8 frame_[FRAME_OFF(304)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = *(int *)(active_editor_wnd + 0x2ec);
  _strncpy(local_124,&editor_item_names + iVar1 * 0x28,0x19);
  local_10c = 0;
  do {
    if (active_editor_wnd == 0) {
      local_12c = 0;
    }
    else {
      local_12c = active_editor_wnd + 0x48;
    }
    dlg_push_parent_window(local_12c);
    local_8 = dlg_text_input(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x62e45c, ((u8 *)&g.d_0062e45c)),0x18,(iptr)local_124,(iptr)local_110);
    dlg_pop_parent_window();
    if (local_8 == -1) break;
    sVar2 = _strlen(local_110);
  } while (sVar2 == 0);
  if (-1 < local_8) {
    FUN_005f22d0(&editor_item_names + iVar1 * 0x28,local_110);
    local_c = combo_get_cur_sel((ComboBoxGetSelView *)(active_editor_wnd + 0x2fc));
    combo_clear((ComboBoxClearView *)(active_editor_wnd + 0x2fc));
    for (local_128 = 0; local_128 < 0x43; local_128++) {
      combo_add_string
                ((ComboBoxAddView *)(active_editor_wnd + 0x2fc),(iptr)(&editor_item_names + local_128 * 0x28));
    }
    combo_set_cur_sel((ComboBoxSetSelView *)(active_editor_wnd + 0x2fc),local_c);
    impr_editor_redraw();
  }
  return;
}
#undef local_12c
#undef local_128
#undef local_124
#undef local_110
#undef local_10c
#undef local_c
#undef local_8

/* 004d953f auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
void __cdecl impr_editor_on_help(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (active_editor_wnd == 0) {
    local_8 = 0;
  }
  else {
    local_8 = active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(local_8);
  popup_text(ADDR(0x62e478, ((u8 *)&g.d_0062e478)),ADDR(0x62e468, ((u8 *)&g.d_0062e468)));
  dlg_set_parent_window(0);
  return;
}
#undef local_8

/* 004d959e auto */
#define editor_running (*(i32 *)((u8 *)&g.d_006a1d7c))
void __cdecl impr_editor_on_cancel(void)

{
  editor_running = 0;
  wnd_end_modal_loop((C_00408010_b8 *)(active_editor_wnd + 0x48));
  return;
}
#undef editor_running

/* 004d95c6 auto */
void __cdecl impr_editor_edit_icon(void)

{
  i32 uVar1;
  i32 uVar2;
  i8 *puVar3;
  
  puVar3 = ((void *)ADDR(0x00402e19, sprite_sheet_save_building_icons));
  uVar2 = 4;
  uVar1 = label_string(*(i32 *)(label_string_ids + 0x7d8));
  sprite_editor_run((iptr)(&improvement_icon_sprites + *(int *)(active_editor_wnd + 0x2ec) * 0x3c),uVar1,uVar2,
                     (iptr)puVar3);
  impr_editor_redraw();
  return;
}

/* 004d9619 auto */
#define local_14 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(i8 * *)(frame_ + FRAME_OFF(8)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(16)))
void __cdecl impr_editor_edit_misc_icon(void)

{
  int iVar1;
  i32 uVar2;
  i8 *puVar3;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (active_editor_wnd == 0) {
    local_14 = 0;
  }
  else {
    local_14 = active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(local_14);
  iVar1 = popup_text_flags(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x62e480, ((u8 *)&g.d_0062e480)),1);
  if (iVar1 != -1) {
    if (iVar1 == 0) {
      local_10 = &map_cursor_sprite;
      local_8 = 5;
    }
    else {
      local_10 = &explosion_sprites + (iVar1 * 4 - 4) * 0xf;
      local_8 = 6;
    }
    if (local_10 != (i8 *)0x0) {
      puVar3 = ((void *)ADDR(0x00402e19, sprite_sheet_save_building_icons));
      uVar2 = label_string(*(i32 *)(label_string_ids + 0x7d8));
      sprite_editor_run((iptr)local_10,uVar2,local_8,(iptr)puVar3);
    }
  }
  dlg_set_parent_window(0);
  return;
}
#undef local_14
#undef local_10
#undef local_8

/* 004d9718 auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
void __cdecl impr_editor_on_select(int param_1)

{
  int iVar1;
  HWND hWnd;
  i32 uVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 == 0xc9) {
    iVar1 = impr_editor_save_controls();
    if (iVar1 == 0) {
      uVar2 = combo_get_cur_sel((ComboBoxGetSelView *)(active_editor_wnd + 0x2fc));
      *(i32 *)(active_editor_wnd + 0x2ec) = uVar2;
      if (*(int *)(active_editor_wnd + 0x2ec) == 0) {
        ctrl_disable((Control *)(active_editor_wnd + 0x7c4));
      }
      else {
        ctrl_enable((Control *)(active_editor_wnd + 0x7c4));
      }
      if (*(int *)(active_editor_wnd + 0x2ec) < 0x27) {
        control_hide((Control *)(active_editor_wnd + 0x36c));
      }
      else {
        ctrl_show_and_redraw((Control *)(active_editor_wnd + 0x36c));
      }
      impr_editor_load_controls();
      impr_editor_redraw();
    }
    else {
      combo_set_cur_sel
                ((ComboBoxSetSelView *)(active_editor_wnd + 0x2fc),*(iptr *)(active_editor_wnd + 0x2ec));
      impr_editor_load_controls();
      impr_editor_redraw();
      if (active_editor_wnd == 0) {
        local_8 = 0;
      }
      else {
        local_8 = active_editor_wnd + 0x48;
      }
      dlg_set_parent_window(local_8);
      popup_text(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x62e48c, ((u8 *)&g.d_0062e48c)));
      dlg_set_parent_window(0);
      hWnd = (HWND)control_get_hwnd((ControlHwndView *)(active_editor_wnd + 0x2fc));
      SetFocus(hWnd);
    }
  }
  return;
}
#undef local_8

/* 004d986e auto */
#define editor_next_ctrl_id (*(int *)((u8 *)&g.d_006a1d80))
#define local_2c (*(u8 * *)(frame_ + FRAME_OFF(4)))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(12)))
#define advance (*(iptr *)(frame_ + FRAME_OFF(16)))
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(28)))
void __thiscall impr_editor_create_combo(C_004083b0_430 *this,int param_1)

{
  int iVar1;
  iptr iVar2;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  rect_set_xywh((iptr)local_14,*(int *)(&impr_editor_combo_x_table + param_1 * 8) + this->client_x - 0x32,
                     *(int *)(&impr_editor_combo_y_table + param_1 * 8) + this->client_y,200,
                     this->field_2e8 << 3);
  iVar1 = editor_next_ctrl_id;
  editor_next_ctrl_id++;
  if (this == (C_004083b0_430 *)0x0) {
    local_2c = (u8 *)0x0;
  }
  else {
    local_2c = this->pad_48;
  }
  combo_create
            ((Control *)(this->pad_2d4 + param_1 * 0x38 + 0x28),(iptr)local_2c,iVar1,
             (iptr)local_14);
  combo_set_font((ComboBoxFontView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),ADDR(0x6a4f90, ((u8 *)&g.d_006a4f90)));
  combo_set_callback((ComboBoxCallbackSetView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),ADDR(0x40257c, impr_editor_on_select));
  if (param_1 == 0) {
    for (improvement = 0; improvement < 0x43; improvement++) {
      iVar2 = label_string(improvements[improvement].name);
      combo_add_string((ComboBoxAddView *)&this->field_2fc,iVar2);
    }
  }
  else if ((0 < param_1) && (param_1 < 3)) {
    iVar2 = label_string(*(i32 *)(label_string_ids + 0x7c0));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar2);
    iVar2 = label_string(*(i32 *)(label_string_ids + 0x7c4));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar2);
    for (advance = 0; advance < 100; advance++) {
      iVar2 = label_string(advances[advance].name);
      combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar2);
    }
  }
  return;
}
#undef editor_next_ctrl_id
#undef local_2c
#undef improvement
#undef advance
#undef local_14

/* 004d9a9f auto */
#define editor_next_ctrl_id (*(int *)((u8 *)&g.d_006a1d80))
#define impr_editor_edit_x_table (*(i32 *)((u8 *)&g.d_0062e3b0))
#define impr_editor_edit_y_table (*(i32 *)((u8 *)&g.d_0062e3b4))
#define local_24 (*(u8 * *)(frame_ + FRAME_OFF(4)))
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
void __thiscall impr_editor_create_edit(C_004083b0_430 *this,int param_1)

{
  int iVar1;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  rect_set_xywh((iptr)local_14,(&impr_editor_edit_x_table)[param_1 * 2] + this->client_x,
                     (&impr_editor_edit_y_table)[param_1 * 2] + this->client_y,0x30,this->field_2e8 + 6);
  iVar1 = editor_next_ctrl_id;
  editor_next_ctrl_id++;
  if (this == (C_004083b0_430 *)0x0) {
    local_24 = (u8 *)0x0;
  }
  else {
    local_24 = this->pad_48;
  }
  edit_create
            ((EditControl *)(this[1].pad_48 + param_1 * 0x48 - 0x2c),(iptr)local_24,iVar1,
             (iptr)local_14,ADDR(0x62e494, ((u8 *)&g.d_0062e494)));
  edit_set_max_len((EditMaxLenView *)(this[1].pad_48 + param_1 * 0x48 - 0x2c),3);
  edit_set_callback((EditCallbackSetView *)(this[1].pad_48 + param_1 * 0x48 - 0x2c),ADDR(0x401019, editor_numeric_edit_filter));
  return;
}
#undef editor_next_ctrl_id
#undef impr_editor_edit_x_table
#undef impr_editor_edit_y_table
#undef local_24
#undef local_14

/* 004d9b93 auto */
#define editor_bg_surface (*(int *)((u8 *)&g.d_0062e018))
#define editor_running (*(int *)((u8 *)&g.d_006a1d7c))
#define impr_editor_edit_x_table (*(int *)((u8 *)&g.d_0062e3b0))
#define impr_editor_edit_y_table (*(int *)((u8 *)&g.d_0062e3b4))
#define local_2c (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_1c (*(Sprite * *)(frame_ + FRAME_OFF(20)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_14 (*(char * *)(frame_ + FRAME_OFF(28)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_c (*(int *)(frame_ + FRAME_OFF(36)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(40)))
void __thiscall impr_editor_paint(C_004083b0_430 *this)

{
  byte bVar1;
  int iVar2;
  char *pcVar3;
  size_t sVar4;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  frame_wnd_draw_caption((FrameWindow *)this);
  if ((editor_bg_surface == 0) || (editor_running == 0)) {
    gfx_fill_rect((iptr)this,(iptr)&this->client_rect,0x1d);
  }
  else {
    gfx_copy_rect_xywh(editor_bg_surface,(iptr)this,0,0,this->client_x,this->client_y,this->field_2d8,
                       this->field_2dc);
  }
  local_8 = this->client_x + 0x20;
  local_c = this->client_y + 0x20;
  if ((int)this->field_2ec < 0x27) {
    local_1c = (Sprite *)(&improvement_icon_sprites + this->field_2ec * 0x3c);
  }
  else {
    local_1c = (Sprite *)(&wonder_icon_sprites + (this->field_2ec * 4 - 0x9c) * 0xf);
  }
  if (this->field_2ec == 0) {
    gfx_fill_rect_xywh((iptr)this,local_8,local_c,0x48,0x28,10);
  }
  else {
    bVar1 = sprite_get_key_color(local_1c);
    gfx_fill_rect_xywh((iptr)this,local_8,local_c,0x48,0x28,(uint)bVar1);
    gfx_set_scale_ratio(2,1);
    sprite_draw(local_1c,(iptr)local_2c,(iptr)this,local_8,local_c);
    gfx_set_scale_ratio(1,1);
  }
  gfx_draw_tiled_frame((iptr)this,local_8,local_c,0x48,0x28,6);
  text_set_surface((iptr)this);
  text_set_font(ADDR(0x6a4f90, ((u8 *)&g.d_006a4f90)));
  text_set_colors(10,10,0,0);
  gfx_fill_rect_xywh((iptr)this,this->client_x + 0x32,this->client_y + 0xe8,0x1cc,0x6e,0x29);
  gfx_draw_frame_rect((iptr)this,this->client_x + 0x32,this->client_y + 0xe8,0x1cc,0x6e,10);
  local_10 = this->client_x + 0x40;
  local_18 = this->client_y + 0xee;
  text_clear();
  text_append(ADDR(0x62e498, ((u8 *)&g.d_0062e498)));
  text_append_int(this->field_2ec);
  iVar2 = text_open_section(ADDR(0x62e4a8, ((u8 *)&g.d_0062e4a8)),ADDR(0x679640, ((u8 *)&g.d_00679640)));
  if (iVar2 == 0) {
    do {
      local_14 = (char *)text_read_line(1);
      if (*local_14 == '^') {
        local_14++;
      }
      pcVar3 = _strstr(local_14,&impr_editor_help_percent_str);
      if (pcVar3 != (char *)0x0) {
        pcVar3 = _strstr(local_14,&impr_editor_help_percent2_str);
        pcVar3[1] = ' ';
      }
      text_draw_shadowed((iptr)this,(iptr)local_14,local_10,local_18);
      local_18 += this->field_2e8;
      sVar4 = _strlen(local_14);
    } while (1 < sVar4);
  }
  text_set_colors(0x29,0x12,1,1);
  local_10 = this->client_x + (int)this->field_2d8 / 2;
  local_18 = (this->client_y - this->field_2e8) + 0xe6;
  text_clear();
  text_append_label(0x1ea);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_18,0);
  local_10 = this->client_x + (int)this->field_2d8 / 2;
  local_18 = impr_editor_combo1_y + this->client_y + this->field_2e8 * -2 - 2;
  text_clear();
  text_append_label(0x1e9);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_18,0);
  local_10 = impr_editor_combo1_x + this->client_x + 0x32;
  local_18 = ((impr_editor_combo1_y + this->client_y) - this->field_2e8) - 2;
  text_clear();
  text_append_label(0x7e);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_18,0);
  local_10 = impr_editor_combo2_x + this->client_x + 0x32;
  local_18 = ((impr_editor_combo2_y + this->client_y) - this->field_2e8) - 2;
  text_clear();
  text_append_label(0x1de);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_18,0);
  local_10 = impr_editor_edit_x_table + this->client_x + 0x18;
  local_18 = ((impr_editor_edit_y_table + this->client_y) - this->field_2e8) - 2;
  text_clear();
  text_append_label(0x1e1);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_18,0);
  local_10 = impr_editor_edit1_x + this->client_x + 0x18;
  local_18 = ((impr_editor_edit1_y + this->client_y) - this->field_2e8) - 2;
  text_clear();
  text_append_label(0x9e);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_18,0);
  wnd_blit_surface((DibSurface *)this);
  return;
}
#undef editor_bg_surface
#undef editor_running
#undef impr_editor_edit_x_table
#undef impr_editor_edit_y_table
#undef local_2c
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 004da107 auto */
#define editor_bg_surface (*(DibSurface * *)((u8 *)&g.d_0062e018))
#define editor_next_ctrl_id (*(i32 *)((u8 *)&g.d_006a1d80))
#define editor_running (*(int *)((u8 *)&g.d_006a1d7c))
#define local_488 (*(u8 * *)(frame_ + FRAME_OFF(0)))
#define local_484 (*(u8 * *)(frame_ + FRAME_OFF(4)))
#define local_480 (*(u8 * *)(frame_ + FRAME_OFF(8)))
#define local_47c (*(u8 * *)(frame_ + FRAME_OFF(12)))
#define local_478 (*(u8 * *)(frame_ + FRAME_OFF(16)))
#define local_474 (*(u8 * *)(frame_ + FRAME_OFF(20)))
#define local_468 (*(DibSurface * *)(frame_ + FRAME_OFF(32)))
#define local_460 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_454 (*(i8 (*)[16])(frame_ + FRAME_OFF(52)))
#define local_444 (*(GamePalette *)(frame_ + FRAME_OFF(68)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1144)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1148)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(1152)))
void __thiscall impr_editor_window_run(C_004083b0_430 *this)

{
  DibSurface *this_00;
  uptr uVar1;
  i32 uVar2;
  int iVar3;
  int iVar4;
  iptr iVar5;
  i32 uVar6;
  i32 uVar7;
  i32 uVar8;
  u32 uVar9;
  u32 uVar10;
  i32 uVar11;
  i32 uVar12;
  i32 uVar13;
  i8 frame_[FRAME_OFF(1160)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  palette_init(&local_444);
  local_8 = 0;
  editor_running = 1;
  active_editor_wnd = (iptr)this;
  this_00 = operator_new(0x48);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  if (this_00 == (DibSurface *)0x0) {
    local_468 = (DibSurface *)0x0;
  }
  else {
    local_468 = (DibSurface *)surface_ctor(this_00);
  }
  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
  editor_bg_surface = local_468;
  font_set((GameFont *)&editor_font,0,editor_font_size);
  ui_set_default_font(ADDR(0x6a4f90, ((u8 *)&g.d_006a4f90)));
  ui_set_ctrl_font(ADDR(0x6a4f90, ((u8 *)&g.d_006a4f90)));
  ui_set_ctrl_text_color(0x29);
  ui_set_ctrl_text_shadow(0x12,1,1);
  ui_set_ctrl_disabled_color(0x25);
  this->field_2d8 = 0x230;
  this->field_2dc = 0x17c;
  this->field_2ec = 1;
  editor_next_ctrl_id = 0xc9;
  surface_load_gif_file(editor_bg_surface,ADDR(0x62e4b8, ((u8 *)&g.d_0062e4b8)),10,0xc0,(iptr)&local_444);
  uVar1 = font_cached_height((GameFont *)&editor_font);
  this->field_2e8 = uVar1;
  uVar13 = 0;
  uVar12 = 0;
  uVar11 = 0;
  uVar10 = this->field_2dc;
  uVar9 = this->field_2d8;
  uVar8 = 0;
  uVar7 = 0;
  uVar6 = 0xd;
  uVar2 = label_string(*(i32 *)(label_string_ids + 0x730));
  frame_wnd_create
            ((FrameWindow *)this,uVar2,uVar6,uVar7,uVar8,uVar9,uVar10,uVar11,uVar12,uVar13);
  for (local_460 = 0; local_460 < 5; local_460++) {
    if (*(int *)(&impr_editor_ctrl_kinds + local_460 * 8) == 9) {
      impr_editor_create_edit(this,*(i32 *)(&impr_editor_ctrl_slots + local_460 * 8));
    }
    else if (*(int *)(&impr_editor_ctrl_kinds + local_460 * 8) == 0xc) {
      impr_editor_create_combo(this,*(i32 *)(&impr_editor_ctrl_slots + local_460 * 8));
    }
  }
  iVar3 = font_line_spacing((GameFont *)dialog_font_ptr);
  this->field_2e4 = iVar3 + 8;
  iVar3 = this->client_width - 10;
  this->field_2e0 = (int)(iVar3 + (iVar3 >> 0x1f & 3U)) >> 2;
  iVar4 = (this->client_y + this->client_height) - (this->field_2e4 + 2);
  iVar3 = this->client_x + 2;
  rect_set_xywh((iptr)local_454,iVar3,iVar4,this->field_2e0,this->field_2e4);
  if (this == (C_004083b0_430 *)0x0) {
    local_474 = (u8 *)0x0;
  }
  else {
    local_474 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x3f8));
  button_create
            ((Control *)&this[1].field_2a4,(iptr)local_474,0x65,(iptr)local_454,iVar5);
  button_set_callback((Control *)&this[1].field_2a4,ADDR(0x40187f, impr_editor_on_ok));
  iVar3 = iVar3 + this->field_2e0 + 2;
  rect_set_xywh((iptr)local_454,iVar3,iVar4,this->field_2e0,this->field_2e4);
  if (this == (C_004083b0_430 *)0x0) {
    local_478 = (u8 *)0x0;
  }
  else {
    local_478 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0xa8));
  button_create
            ((Control *)&this[1].field_358,(iptr)local_478,0x66,(iptr)local_454,iVar5);
  button_set_callback((Control *)&this[1].field_358,ADDR(0x40178a, impr_editor_on_rename));
  iVar3 = iVar3 + this->field_2e0 + 2;
  rect_set_xywh((iptr)local_454,iVar3,iVar4,this->field_2e0,this->field_2e4);
  if (this == (C_004083b0_430 *)0x0) {
    local_47c = (u8 *)0x0;
  }
  else {
    local_47c = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x8ec));
  button_create
            ((Control *)&this[1].field_2e0,(iptr)local_47c,0x66,(iptr)local_454,iVar5);
  button_set_callback((Control *)&this[1].field_2e0,ADDR(0x402c75, impr_editor_on_help));
  rect_set_xywh((iptr)local_454,iVar3 + this->field_2e0 + 2,iVar4,this->field_2e0,
                     this->field_2e4);
  if (this == (C_004083b0_430 *)0x0) {
    local_480 = (u8 *)0x0;
  }
  else {
    local_480 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x3fc));
  button_create
            ((Control *)&this[1].field_31c,(iptr)local_480,0x66,(iptr)local_454,iVar5);
  button_set_callback((Control *)&this[1].field_31c,ADDR(0x402072, impr_editor_on_cancel));
  ctrl_set_cancel_button((Control *)&this[1].field_31c);
  this->field_2e0 = 0x55;
  iVar3 = font_line_spacing((GameFont *)dialog_font_ptr);
  this->field_2e4 = iVar3 + 8;
  iVar3 = this->client_x + 0x19;
  iVar4 = this->client_y + 0x50;
  rect_set_xywh((iptr)local_454,iVar3,iVar4,this->field_2e0,this->field_2e4);
  if (this == (C_004083b0_430 *)0x0) {
    local_484 = (u8 *)0x0;
  }
  else {
    local_484 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x7cc));
  button_create
            ((Control *)(this[1].pad_364 + 0x30),(iptr)local_484,0x65,(iptr)local_454,iVar5);
  button_set_callback((Control *)(this[1].pad_364 + 0x30),ADDR(0x402388, impr_editor_edit_icon));
  rect_set_xywh((iptr)local_454,iVar3,iVar4 + this->field_2e4 + 2,this->field_2e0,
                     this->field_2e4);
  if (this == (C_004083b0_430 *)0x0) {
    local_488 = (u8 *)0x0;
  }
  else {
    local_488 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x8f0));
  button_create
            ((Control *)(this[1].pad_3c0 + 0x10),(iptr)local_488,0x65,(iptr)local_454,iVar5);
  button_set_callback((Control *)(this[1].pad_3c0 + 0x10),ADDR(0x401cad, impr_editor_edit_misc_icon));
  wnd_set_keyboard_nav((Wnd *)this->pad_48,0);
  impr_editor_load_rules();
  combo_set_cur_sel((ComboBoxSetSelView *)&this->field_2fc,this->field_2ec);
  impr_editor_load_controls();
  this->field_2f8 = 3;
  wnd_set_move_handler((C_00408130 *)(this->pad_48 + 0x10),ADDR(0x4019d8, editor_wnd_on_move_close_dropdowns));
  wnd_set_redraw_callback((SurfaceWindow *)this,ADDR(0x401302, impr_editor_redraw));
  impr_editor_on_select(0xc9);
  wnd_repaint((SurfaceWindow *)this);
  window_show((C_004083b0_4 *)this);
  wnd_run_modal_loop((C_00408010_b8 *)this->pad_48);
  while (editor_running != 0) {
    win_pump_one_message();
  }
  if (editor_bg_surface != (DibSurface *)0x0) {
    surface_delete(editor_bg_surface,1);
  }
  editor_bg_surface = (DibSurface *)0x0;
  this->field_2f8 = 0;
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_004da9be */ { palette_destroy((GamePalette *)((iptr)&local_444)); }
  return;
}
#undef editor_bg_surface
#undef editor_next_ctrl_id
#undef editor_running
#undef local_488
#undef local_484
#undef local_480
#undef local_47c
#undef local_478
#undef local_474
#undef local_468
#undef local_460
#undef local_454
#undef local_444
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004da9e2 auto */
#define local_b58 (*(C_004083b0_a28 *)(frame_ + FRAME_OFF(0)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(2888)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(2892)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(2896)))
void __cdecl impr_editor_run(void)

{
  i8 frame_[FRAME_OFF(2904)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  editor_wnd_ctor(&local_b58);
  local_8 = 0;
  impr_editor_window_run((C_004083b0_430 *)&local_b58);
  wnd_repaint((SurfaceWindow *)&map_views);
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_004daa3b */ { editor_wnd_dtor((EditorWindow *)((iptr)&local_b58)); }
  return;
}
#undef local_b58
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004e7270 auto */
#define city_acquire_wonder_busy (*(i32 *)((u8 *)&g.d_006ad8e8))
#define nm_wonder_acquired_result (*(int *)((u8 *)&g.d_006c9100))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
int __cdecl city_acquire_wonder(iptr param_1,iptr city,iptr param_3,iptr param_4,iptr param_5)

{
  char cVar1;
  int iVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 0;
  city_acquire_wonder_busy = 1;
  if ((game.multiplayer < 3) || (cVar1 = net_is_host(&net_session), cVar1 != '\0')) {
    if (game.wonder_city[param_3] == -1) {
      local_c = 1;
      game.wonder_city[param_3] = (i16)city;
      cities[city].flags = cities[city].flags | 0x100;
      city_set_improvement(city,param_5,1);
      if (((1 << ((byte)param_1 & 0x1f) & (uint)game.human_players) != 0) || (0x22 < param_5)) {
        cities[city].shield_box = 0;
      }
    }
    if ((2 < game.multiplayer) && (local_c != 0)) {
      net_send_state_diff(0xff,2,0,0,0);
      XD_FlushSendBuffer(5000);
    }
    city_acquire_wonder_busy = 0;
  }
  else {
    city_acquire_wonder_busy = 0;
    nm_wonder_acquired_result = -2;
    net_send_message(0x47,0,param_1,city,param_3,param_4,param_5,0,0,0);
    iVar2 = timer_ticks();
    while ((nm_wonder_acquired_result == -2 && (iVar3 = timer_ticks(), iVar3 - iVar2 < 0xe10))) {
      net_process_messages((NetSession *)&net_session,1,1);
    }
    if (nm_wonder_acquired_result == -2) {
      dbg_log(ADDR(0x62ee10, ((u8 *)&g.d_0062ee10)));
      local_c = 0;
    }
    else {
      while ((net_msgq_priority_count != 0 || (local_c = nm_wonder_acquired_result, net_msgq_normal_count != 0))) {
        net_process_messages((NetSession *)&net_session,1,0);
      }
    }
  }
  return local_c;
}
#undef city_acquire_wonder_busy
#undef nm_wonder_acquired_result
#undef local_c

/* 004e7458 auto */
i32 __cdecl city_production_category(iptr param_1,int param_2)

{
  i32 uVar1;
  
  if (param_2 < 0) {
    if (param_2 < -0x22) {
      uVar1 = 2;
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

/* 004e7492 auto */
#define city_saved_build_category (*(i32 *)((u8 *)&g.d_006a65a4))
#define city_saved_shield_box (*(int *)((u8 *)&g.d_006a6528))
void __cdecl city_save_build_state(iptr city)

{
  city_saved_build_category = city_production_category(city,(int)cities[city].building);
  city_saved_shield_box = (int)cities[city].shield_box;
  return;
}
#undef city_saved_build_category
#undef city_saved_shield_box

/* 004e74df auto */
#define city_saved_build_category (*(int *)((u8 *)&g.d_006a65a4))
#define city_saved_shield_box (*(uint *)((u8 *)&g.d_006a6528))
uint __cdecl city_shields_after_change(iptr param_1,iptr param_2)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = city_saved_shield_box;
  if ((game.difficulty != '\0') &&
     (iVar1 = city_production_category(param_1,param_2), uVar2 = city_saved_shield_box, iVar1 != city_saved_build_category)) {
    uVar2 = city_saved_shield_box - ((uint)cosmic.change_penalty * (city_saved_shield_box & 0xffff)) / 100;
  }
  return uVar2;
}
#undef city_saved_build_category
#undef city_saved_shield_box

/* 004e7549 auto */
void __cdecl city_set_specialist_type(iptr city,int param_2,int param_3)

{
  byte bVar1;
  
  if (param_2 < 0x10) {
    bVar1 = (char)param_2 * 2;
    cities[city].specialists = cities[city].specialists & ~(3 << (bVar1 & 0x1f));
    cities[city].specialists = cities[city].specialists | param_3 << (bVar1 & 0x1f);
  }
  return;
}

/* 004e75a6 auto */
uint __cdecl city_specialist_type(iptr city,int param_2)

{
  uint uVar1;
  
  if (param_2 < 0x10) {
    uVar1 = (int)cities[city].specialists >> ((char)param_2 * 2 & 0x1fU) & 3;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

/* 004e75ea auto */
#define local_c (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
int __cdecl city_count_specialists(iptr city,int param_2)

{
  int iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 0;
  for (local_8 = 0; local_8 < 0x10; local_8++) {
    iVar1 = city_specialist_type(city,local_8);
    if (iVar1 == param_2) {
      local_c++;
    }
  }
  return local_c;
}
#undef local_c
#undef local_8

/* 004e7641 auto */
#define city_turn_processing (*(int *)((u8 *)&g.d_0062edf8))
#define unit (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(16)))
void __cdecl city_calc_tile_flags(iptr city)

{
  byte civ2;
  int civ;
  iptr x;
  int y;
  byte *pbVar5;
  int iVar6;
  uint uVar7;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ2 = cities[city].owner;
  civ = (int)(char)civ2;
  local_8 = 0;
  do {
    if (0x18 < local_8) {
      return;
    }
    x = map_wrap_x((int)(char)(&city_tile_dx_table)[local_8] + (int)cities[city].x);
    y = (int)cities[city].y + (int)(char)(&city_tile_dy_table)[local_8];
    pbVar5 = &city_tile_flags + local_8;
    *pbVar5 = 0;
    iVar6 = map_in_bounds(x,y);
    if ((iVar6 == 0) || (0x14 < local_8)) {
      *pbVar5 = *pbVar5 | 1;
    }
    else {
      iVar6 = tile_visible_to(x,y,civ);
      if (iVar6 == 0) {
        *pbVar5 = *pbVar5 | 1;
      }
      else {
        if ((((1 << (civ2 & 0x1f) & (uint)game.human_players) == 0) && (city_turn_processing != 0)) &&
           (uVar7 = tile_improvements(x,y), (uVar7 & 0x80) != 0)) {
          game.field_28++;
        }
        unit = tile_first_unit(x,y);
        while( true ) {
          if (((unit < 0) || (units[unit].owner == civ)) ||
             ((iVar6 = tile_is_ocean(x,y), iVar6 != 0 ||
              ((*(byte *)&civs[civ].treaties[units[unit].owner] & 8) != 0))))
          goto LAB_004e7898;
          if (unit_types[units[unit].type].attack != '\0') break;
          unit = unit_next_in_stack(unit);
        }
        *pbVar5 = *pbVar5 | 4;
        if (((uint)game.human_players & 1 << (units[unit].owner & 0x1fU)) != 0) {
          *pbVar5 = *pbVar5 | 0x20;
        }
LAB_004e7898:
        y = tile_city_owner(x,y);
        if (-1 < y) {
          *pbVar5 = *pbVar5 | 8;
        }
      }
    }
    local_8++;
  } while( true );
}
#undef city_turn_processing
#undef unit
#undef local_8

/* 004e78ce auto */
uint __cdecl city_tile_worked(iptr city,iptr param_2)

{
  return (uint)((cities[city].worked_tiles & 1 << ((byte)param_2 & 0x1f)) != 0);
}

/* 004e790c auto */
void __cdecl city_set_tile_worked(iptr city,iptr param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = 1 << ((byte)param_2 & 0x1f);
  if (param_3 == 0) {
    cities[city].worked_tiles = cities[city].worked_tiles & ~uVar1;
  }
  else {
    cities[city].worked_tiles = cities[city].worked_tiles | uVar1;
  }
  return;
}

/* 004e7967 auto */
#define city_capital_link (*(uint *)((u8 *)&g.d_006a6574))
#define city2 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_1c (*(iptr *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(40)))
void __cdecl city_calc_capital_link(iptr city)

{
  short x2;
  short y2;
  int x;
  int y;
  int x3;
  int y3;
  int iVar7;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  x = (int)cities[city].x;
  y = (int)cities[city].y;
  x3 = city_has_improvement(city,1);
  if (x3 == 0) {
    city_capital_distance = 0x20;
  }
  else {
    city_capital_distance = 0;
  }
  city_capital_nearest = -1;
  for (city2 = 0; city2 < game.num_cities; city2++) {
    if ((cities[city2].id != 0) && (city2 != city)) {
      x3 = map_distance_diag((int)cities[city].x,(int)cities[city].y,
                                 (int)cities[city2].x,(int)cities[city2].y);
      if ((cities[city2].owner == cities[city].owner) &&
         (y3 = city_has_improvement(city2,1), y3 != 0)) {
        if ((x3 < city_capital_distance) || (city_capital_nearest < 0)) {
          city_capital_nearest = city2;
        }
        if (x3 < city_capital_distance) {
          city_capital_distance = x3;
        }
      }
      if (x3 < 6) {
        for (local_8 = 0; local_8 < 0x15; local_8++) {
          x3 = city_tile_worked(city2,local_8);
          if ((x3 != 0) || (local_8 == 0x14)) {
            x3 = (int)cities[city2].x + (int)(char)(&city_tile_dx_table)[local_8];
            y3 = (int)cities[city2].y + (int)(char)(&city_tile_dy_table)[local_8];
            iVar7 = map_distance_diag(x,y,x3,y3);
            if (iVar7 < 3) {
              for (local_1c = 0; local_1c < 0x14; local_1c++) {
                if (((int)(char)(&city_tile_dx_table)[local_1c] == x3 - x) &&
                   ((int)(char)(&city_tile_dy_table)[local_1c] == y3 - y)) {
                  (&city_tile_flags)[local_1c] = (&city_tile_flags)[local_1c] | 0x10;
                }
              }
            }
          }
        }
      }
    }
  }
  city_capital_link = (uint)(city_capital_distance == 0);
  if ((city_capital_link != 0) &&
     (x3 = civ_has_advance((int)cities[city].owner,0x43), x3 != 0)) {
    city_capital_link++;
  }
  if ((-1 < city_capital_nearest) && (city != city_capital_nearest)) {
    x3 = city_has_improvement(city,0x20);
    if ((x3 != 0) && (x3 = city_has_improvement(city_capital_nearest,0x20), x3 != 0)) {
      city_capital_link = 1;
    }
    x3 = tile_landmass(x,y);
    x2 = cities[city_capital_nearest].x;
    y2 = cities[city_capital_nearest].y;
    y3 = tile_landmass((int)x2,(int)y2);
    if (y3 == x3) {
      city_capital_link = map_road_connection((int)cities[city].owner,x,y,(int)x2,(int)y2
                                       );
    }
  }
  return;
}
#undef city_capital_link
#undef city2
#undef local_1c
#undef local_8

/* 004e7d7f auto */
#define city_shield_support (*(int *)((u8 *)&g.d_006a6568))
#define city_support_unit_count (*(int *)((u8 *)&g.d_006a660c))
i32 __cdecl city_count_unit_support(iptr city,iptr unit,i32 param_3)

{
  city_support_unit_count++;
  switch(param_3) {
  case 0:
  case 1:
    if (cities[city].size < city_support_unit_count) {
      city_shield_support++;
      return city_shield_support;
    }
    break;
  case 2:
    if ((int)(uint)cosmic.monarchy_free_support < city_support_unit_count) {
      city_shield_support++;
      return city_shield_support;
    }
    break;
  case 3:
    if ((int)(uint)cosmic.communism_free_support < city_support_unit_count) {
      city_shield_support++;
      return city_shield_support;
    }
    break;
  case 4:
    if (((unit_types[units[unit].type].flags & 0x800) == 0) &&
       ((int)(uint)cosmic.fundamentalism_free_support < city_support_unit_count)) {
      city_shield_support++;
      return city_shield_support;
    }
    break;
  default:
    city_shield_support++;
    return city_shield_support;
  }
  return 0;
}
#undef city_shield_support
#undef city_support_unit_count

/* 004e7eb1 auto */
#define city_food_box_rows (*(uint *)((u8 *)&g.d_006a6560))
#define settler_food_cost (*(uint *)((u8 *)&g.d_006a6608))
#define local_c (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl city_calc_food_box_rows(iptr param_1,iptr civ)

{
  byte bVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  bVar1 = cosmic.settler_food_low;
  if (2 < civs[civ].government) {
    bVar1 = cosmic.settler_food_high;
  }
  local_c = (uint)bVar1;
  settler_food_cost = local_c;
  city_food_box_rows = (uint)cosmic.food_box_rows;
  if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
    city_food_box_rows = -(uint)game.difficulty + 0xd;
    if (game.difficulty < 3) {
      city_food_box_rows = -(uint)game.difficulty + 0xe;
    }
    if (game.difficulty == '\0') {
      city_food_box_rows++;
    }
    if (((200 < game.turn) && (1 < game.difficulty)) &&
       (((uint)game.human_players & 1 << (game.civ_by_rank[7] & 0x1f)) != 0)) {
      local_8 = 2;
      if (((game.wonder_city[0x17] != -1) &&
          ((~(uint)game.human_players & (int)(char)game.advance_known_by[0x49]) != 0)) &&
         ((local_8 = 1, (game.human_players & game.advance_known_by[0x49]) == 0 ||
          ((game.human_players & game.advance_known_by[0x3a]) == 0)))) {
        local_8 = 0;
      }
      iVar2 = local_8;
      if (((game.wonder_city[0x19] != -1) &&
          ((~(uint)game.human_players & (int)(char)game.advance_known_by[0x4c]) != 0)) &&
         (iVar2 = local_8 - 1, (game.human_players & game.advance_known_by[0x4c]) == 0)) {
        iVar2 = local_8 - 2;
      }
      local_8 = iVar2;
      iVar2 = int_clamp(local_8,0,2);
      city_food_box_rows -= iVar2;
    }
    if ((cosmic.food_box_rows != '\n') &&
       (city_food_box_rows = (int)(cosmic.food_box_rows * city_food_box_rows) / 10, (city_food_box_rows & 1) != 0)) {
      city_food_box_rows++;
    }
  }
  return;
}
#undef city_food_box_rows
#undef settler_food_cost
#undef local_c
#undef local_8

/* 004e80b1 auto */
#define city_aggressive_units (*(int *)((u8 *)&g.d_006a65e4))
#define city_shield_rows (*(uint *)((u8 *)&g.d_006a657c))
#define city_shield_support (*(i32 *)((u8 *)&g.d_006a6568))
#define city_support_unit_count (*(i32 *)((u8 *)&g.d_006a660c))
#define unit (*(iptr *)(frame_ + FRAME_OFF(0)))
#define city2 (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl city_calc_unit_support(uptr city)

{
  byte civ2;
  byte bVar2;
  iptr civ;
  int iVar4;
  int iVar5;
  i32 uVar6;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ2 = cities[city].owner;
  civ = (iptr)(char)civ2;
  bVar2 = civs[civ].government;
  city_calc_food_box_rows(city,civ);
  city_shield_rows = (uint)cosmic.shield_box_rows;
  if ((1 << (civ2 & 0x1f) & (uint)game.human_players) == 0) {
    city_shield_rows = 0xd - game.difficulty;
    if (game.difficulty == '\0') {
      city_shield_rows = 0xe;
    }
    if (game.difficulty < 3) {
      city_shield_rows++;
    }
    if (((199 < game.turn) && (1 < game.difficulty)) &&
       (((uint)game.human_players & 1 << (game.civ_by_rank[7] & 0x1f)) != 0)) {
      local_8 = 2;
      if (((game.wonder_city[0x17] != -1) &&
          ((~(uint)game.human_players & (int)(char)game.advance_known_by[0x49]) != 0)) &&
         ((local_8 = 1, (game.human_players & game.advance_known_by[0x49]) == 0 ||
          ((game.human_players & game.advance_known_by[0x3a]) == 0)))) {
        local_8 = 0;
      }
      iVar4 = local_8;
      if (((game.wonder_city[0x19] != -1) &&
          ((~(uint)game.human_players & (int)(char)game.advance_known_by[0x4c]) != 0)) &&
         (iVar4 = local_8 - 1, (game.human_players & game.advance_known_by[0x4c]) == 0)) {
        iVar4 = local_8 - 2;
      }
      local_8 = iVar4;
      iVar4 = int_clamp(local_8,0,2);
      city_shield_rows -= iVar4;
    }
    if ((cosmic.shield_box_rows != '\n') &&
       (city_shield_rows = (int)(cosmic.shield_box_rows * city_shield_rows) / 10, (city_shield_rows & 1) != 0))
    {
      city_shield_rows++;
    }
  }
  city_shield_support = 0;
  city_support_unit_count = 0;
  city_settlers_supported = 0;
  city_aggressive_units = 0;
  city_home_attack_units = 0;
  unit = 0;
  do {
    if (game.num_units <= unit) {
      return;
    }
    if ((((units[unit].id != 0) && (units[unit].owner == civ)) &&
        ((byte)units[unit].home_city == city)) &&
       (units[unit].flags = units[unit].flags & 0xf3ff,
       (char)unit_types[units[unit].type].role < 6)) {
      iVar4 = city_count_unit_support(city,unit,(uint)bVar2);
      if (iVar4 != 0) {
        units[unit].flags = units[unit].flags | 0x800;
      }
      iVar4 = city_aggressive_units;
      if (unit_types[units[unit].type].attack != '\0') {
        if (unit_types[units[unit].type].domain == 1) {
          if (unit_types[units[unit].type].role != 3) {
            city_aggressive_units++;
          }
          if ((units[unit].x == cities[city].x) || (units[unit].y == cities[city].y))
          {
            city_home_attack_units++;
          }
        }
        else if ((units[unit].x == cities[city].x) &&
                (units[unit].y == cities[city].y)) {
          city_home_attack_units++;
        }
        else {
          iVar5 = tile_city_owner((int)units[unit].x,(int)units[unit].y);
          if (iVar5 < 0) {
            city_aggressive_units++;
            uVar6 = tile_improvements((int)units[unit].x,(int)units[unit].y);
            if (((byte)uVar6 & 0x42) == 0x40) {
              for (city2 = 0; city2 < game.num_cities; city2++) {
                if (((cities[city2].id != 0) && (cities[city2].owner == civ)) &&
                   (iVar5 = map_distance((int)units[unit].x,(int)units[unit].y,
                                               (int)cities[city2].x,(int)cities[city2].y),
                   iVar5 < 4)) {
                  city_aggressive_units--;
                  break;
                }
              }
            }
          }
        }
      }
      if (city_aggressive_units != iVar4) {
        units[unit].flags = units[unit].flags | 0x400;
      }
      if (unit_types[units[unit].type].role == 5) {
        city_settlers_supported++;
      }
    }
    unit++;
  } while( true );
}
#undef city_aggressive_units
#undef city_shield_rows
#undef city_shield_support
#undef city_support_unit_count
#undef unit
#undef city2
#undef local_8

/* 004e868f auto */
#define city_tile_job_found (*(i32 *)((u8 *)&g.d_0062ee0c))
#define city_tile_job_priority (*(int *)((u8 *)&g.d_006a65d4))
#define city_tile_job_x (*(iptr *)((u8 *)&g.d_006a65e0))
#define city_tile_job_y (*(int *)((u8 *)&g.d_006a65e8))
#define city_turn_processing (*(int *)((u8 *)&g.d_0062edf8))
#define mp_double_production (*(short *)((u8 *)&g.d_00654fac))
#define local_10 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_8 (*(byte *)(frame_ + FRAME_OFF(8)))
int __cdecl city_tile_yield(iptr city,iptr param_2,iptr param_3)

{
  byte bVar1;
  iptr civ;
  iptr x;
  int y;
  int iVar5;
  uint uVar6;
  byte *pbVar7;
  uptr terrain;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ = (iptr)cities[city].owner;
  x = map_wrap_x((int)cities[city].x + (int)(char)(&city_tile_dx_table)[param_2]);
  y = (int)cities[city].y + (int)(char)(&city_tile_dy_table)[param_2];
  iVar5 = map_in_bounds(x,y);
  if (iVar5 == 0) {
    local_10 = 0;
  }
  else {
    if (city_yield_tile_worked != 0) {
      tile_set_radius_civ(x,y,civ,1);
      iVar5 = tile_city_or_unit_owner(x,y);
      if (iVar5 < 0) {
        tile_set_owner(x,y,civ,1);
      }
    }
    bVar1 = tile_terrain(x,y);
    terrain = (uptr)bVar1;
    iVar5 = tile_resource(x,y);
    local_10 = (int)*(char *)(param_3 + ADDR(0x627cca, ((u8 *)&terrain_types + 10)) + (iVar5 * 0xb + terrain) * 0x18);
    if ((game.multiplayer != '\0') && (mp_double_production != 0)) {
      local_10 = local_10 << 1;
    }
    uVar6 = tile_improvements(x,y);
    local_8 = (byte)uVar6;
    if (terrain == 10) {
      if ((param_3 == 0) && (iVar5 = city_has_improvement(city,0x1e), iVar5 != 0)) {
        local_10++;
      }
      if ((param_3 == 1) && (iVar5 = city_has_improvement(city,0x1f), iVar5 != 0)) {
        local_10++;
      }
      if ((param_3 == 2) && (iVar5 = wonder_get_city(2), iVar5 == city)) {
        local_10++;
      }
    }
    else if (param_3 == 0) {
      if ((uVar6 & 6) == 0) {
        city_note_terraform_job(city,civ,0,x,y);
      }
      else {
        local_10 += (char)terrain_types[terrain].irrigate_bonus;
        iVar5 = city_has_improvement(city,0x18);
        if (iVar5 != 0) {
          if ((uVar6 & 10) == 0) {
            city_note_terraform_job(city,civ,0,x,y);
          }
          else {
            local_10 += (local_10 >> 1);
          }
        }
      }
    }
    else if (param_3 == 1) {
      if (((local_8 & 0xc) == 8) ||
         (((uVar6 & 2) != 0 && (terrain_types[terrain].irrigate_bonus == '\0')))) {
        local_10 += (char)terrain_types[terrain].mine_bonus;
      }
      else if ((uVar6 & 0xc) == 0) {
        city_note_terraform_job(city,civ,1,x,y);
      }
      if ((terrain == 2) && (iVar5 = tile_grassland_has_shield(x,y), iVar5 == 0)) {
        local_10 = 0;
      }
      if ((param_2 == 0x14) && (local_10 == 0)) {
        local_10 = 1;
      }
    }
    else if (param_3 == 2) {
      pbVar7 = (byte *)tile_at(x,y);
      if ((*pbVar7 & 0x80) != 0) {
        local_10++;
      }
      if ((uVar6 & 0x12) == 0) {
        if ((terrain < 3) || (local_10 != 0)) {
          city_note_road_job(city,civ,x,y);
        }
      }
      else if ((terrain < 3) || (local_10 != 0)) {
        local_10++;
      }
      if ((local_10 != 0) && (iVar5 = wonder_get_city(2), iVar5 == city)) {
        local_10++;
      }
    }
    if ((param_3 == 1) && (iVar5 = wonder_get_city(8), iVar5 == city)) {
      local_10++;
    }
    if (param_3 == 1) {
      if (((uVar6 & 0x20) == 0) &&
         (((uVar6 & 2) == 0 || (iVar5 = civ_has_advance(civ,0x43), iVar5 == 0)))) {
        if ((((uVar6 & 0x22) == 0) && (iVar5 = civ_has_advance(civ,0x43), iVar5 != 0)) &&
           (terrain != 10)) {
          city_note_road_job(city,civ,x,y);
        }
      }
      else {
        local_10 += (local_10 >> 1);
      }
    }
    if ((2 < local_10) && ((cities[city].flags & 2) == 0)) {
      if (city_turn_processing != 0) {
        civs[civ].government_score[1]--;
      }
      if (civs[civ].government < 2) {
        local_10--;
      }
    }
    if ((local_10 != 0) && (param_3 == 2)) {
      if (city_turn_processing != 0) {
        civs[civ].government_score[5]++;
        civs[civ].government_score[6]++;
      }
      if ((byte)((-((cities[city].flags & 2) == 0) & 3U) + 2) <= civs[civ].government) {
        local_10++;
      }
    }
    if (((param_3 == 2) && ((uVar6 & 0x12) != 0)) &&
       (iVar5 = city_has_improvement(city,0x19), iVar5 != 0)) {
      local_10 += local_10 / 2;
    }
    if ((uVar6 & 0x80) != 0) {
      local_10 = local_10 + 1 >> 1;
      city_tile_job_priority++;
      city_tile_job_found = 1;
      city_tile_job_x = x;
      city_tile_job_y = y;
    }
    if (local_10 < 1) {
      local_10 = 0;
    }
  }
  return local_10;
}
#undef city_tile_job_found
#undef city_tile_job_priority
#undef city_tile_job_x
#undef city_tile_job_y
#undef city_turn_processing
#undef mp_double_production
#undef local_10
#undef local_8

/* 004e8c8c auto */
#define city_tile_job_found (*(int *)((u8 *)&g.d_0062ee0c))
#define city_tile_job_priority (*(int *)((u8 *)&g.d_006a65d4))
#define city_tile_job_x (*(i32 *)((u8 *)&g.d_006a65e0))
#define city_tile_job_y (*(i32 *)((u8 *)&g.d_006a65e8))
#define city_turn_processing (*(int *)((u8 *)&g.d_0062edf8))
void __cdecl
city_note_terraform_job(iptr param_1,iptr civ,iptr param_3,i32 x,i32 y)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  if (((city_yield_tile_worked != 0) && (city_turn_processing != 0)) && (city_tile_job_found == 0)) {
    bVar1 = tile_terrain(x,y);
    uVar3 = (uint)bVar1;
    if (((*(char *)(param_3 + ADDR(0x627cce, ((u8 *)&terrain_types + 14)) + uVar3 * 0x18) != -1) &&
        (*(char *)(param_3 + ADDR(0x627cd4, ((u8 *)&terrain_types + 20)) + uVar3 * 0x18) != '\0')) &&
       ((param_3 != 0 || (iVar2 = tile_has_irrigation_source(x,y), iVar2 != 0)))) {
      uVar4 = (uint)civs[civ].government;
      if (civs[civ].government < 2) {
        uVar4 = 1;
      }
      if ((int)*(char *)(param_3 + ADDR(0x627cd4, ((u8 *)&terrain_types + 20)) + uVar3 * 0x18) <= (int)uVar4) {
        city_tile_job_priority++;
        city_tile_job_found = 1;
        city_tile_job_x = x;
        city_tile_job_y = y;
      }
    }
  }
  return;
}
#undef city_tile_job_found
#undef city_tile_job_priority
#undef city_tile_job_x
#undef city_tile_job_y
#undef city_turn_processing

/* 004e8db5 auto */
#define city_tile_job_found (*(int *)((u8 *)&g.d_0062ee0c))
#define city_tile_job_x (*(iptr *)((u8 *)&g.d_006a65e0))
#define city_tile_job_y (*(iptr *)((u8 *)&g.d_006a65e8))
#define city_turn_processing (*(int *)((u8 *)&g.d_0062edf8))
void __cdecl city_note_road_job(iptr param_1,iptr civ,iptr x,iptr y)

{
  byte *pbVar1;
  int iVar2;
  
  if ((((city_yield_tile_worked != 0) && (city_turn_processing != 0)) && (city_tile_job_found == 0)) &&
     ((pbVar1 = (byte *)tile_at(x,y), (*pbVar1 & 0x80) == 0 ||
      (iVar2 = civ_has_advance(civ,7), iVar2 != 0)))) {
    city_tile_job_found = 1;
    city_tile_job_x = x;
    city_tile_job_y = y;
  }
  return;
}
#undef city_tile_job_found
#undef city_tile_job_x
#undef city_tile_job_y
#undef city_turn_processing

/* 004e8e4d auto */
#define city_tile_yields (*(i32 *)((u8 *)&g.d_006a65b8))
#define city_yield_totals (*(int *)((u8 *)&g.d_006a65c8))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl city_calc_tile_yields(iptr city,iptr param_2,int param_3)

{
  i32 uVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  city_yield_tile_worked = param_3;
  for (local_8 = 0; local_8 < 3; local_8++) {
    uVar1 = city_tile_yield(city,param_2,local_8);
    (&city_tile_yields)[local_8] = uVar1;
    if (city_yield_tile_worked != 0) {
      (&city_yield_totals)[local_8] = (&city_yield_totals)[local_8] + (&city_tile_yields)[local_8];
    }
  }
  city_yield_tile_worked = 0;
  return;
}
#undef city_tile_yields
#undef city_yield_totals
#undef local_8

/* 004e8ecf auto */
#define local_c (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
uint __cdecl city_release_blocked_tiles(iptr city)

{
  uint uVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 0;
  for (local_8 = 0; local_8 < 0x14; local_8++) {
    uVar1 = city_tile_status_flags(city,local_8);
    local_c = local_c | uVar1 & 0x20;
    if (uVar1 != 0) {
      city_set_tile_worked(city,local_8,0);
    }
  }
  return local_c;
}
#undef local_c
#undef local_8

/* 004e8f42 auto */
#define city_shield_support (*(int *)((u8 *)&g.d_006a6568))
#define city_tile_yields (*(int *)((u8 *)&g.d_006a65b8))
#define city_total_shields (*(int *)((u8 *)&g.d_006a65cc))
#define city_total_trade (*(iptr *)((u8 *)&g.d_006a65d0))
#define city_turn_worker_realloc (*(int *)((u8 *)&g.d_0062edfc))
#define city_unassigned_citizens (*(uint *)((u8 *)&g.d_006a654c))
#define city_workers_overflow (*(i32 *)((u8 *)&g.d_006a65dc))
#define city_yield_totals (*(int *)((u8 *)&g.d_006a65c8))
#define settler_food_cost (*(int *)((u8 *)&g.d_006a6608))
#define local_80 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_7c (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_6c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_68 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_64 (*(iptr *)(frame_ + FRAME_OFF(28)))
#define local_60 (*(uint *)(frame_ + FRAME_OFF(32)))
#define local_5c (*(iptr *)(frame_ + FRAME_OFF(36)))
#define aiStack_58 (*(int (*)[20])(frame_ + FRAME_OFF(40)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(120)))
void __cdecl city_assign_workers(iptr city)

{
  byte civ;
  char cVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  i8 frame_[FRAME_OFF(128)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_7c = 0;
  city_workers_overflow = 0;
  civ = cities[city].owner;
  city_unassigned_citizens = (int)cities[city].size + 1;
  local_60 = cities[city].worked_tiles >> 0x1a;
  if ((1 << (civ & 0x1f) & (uint)game.human_players) == 0) {
    if ((cities[city].flags & 1) == 0) {
      if ((city_turn_worker_realloc != 0) && (local_60 != 0)) {
        if ((cities[city].flags & 0x4000) == 0) {
          local_60--;
        }
        else {
          cities[city].flags = cities[city].flags | 0x8000;
        }
      }
    }
    else {
      cities[city].worked_tiles = 0;
    }
  }
  if (local_60 == 0) {
    cities[city].flags = cities[city].flags & 0xffff7fff;
  }
  iVar4 = city_release_blocked_tiles(city);
  for (local_64 = 0; local_64 < 3; local_64++) {
    (&city_yield_totals)[local_64] = 0;
  }
  for (local_64 = 0; local_64 < 0x14; local_64++) {
    iVar5 = city_tile_status_flags(city,local_64);
    aiStack_58[local_64] = iVar5;
  }
  local_8 = 0;
  if (((((1 << (civ & 0x1f) & (uint)game.human_players) != 0) || ((game.turn + city & 3U) != 0)
       ) || ((cities[city].flags & 1) != 0)) || (iVar4 != 0)) {
    for (local_64 = 0; local_64 < 0x15; local_64++) {
      iVar4 = city_tile_worked(city,local_64);
      if (iVar4 != 0) {
        city_unassigned_citizens--;
      }
    }
    if ((int)city_unassigned_citizens < 0) {
      city_workers_overflow = 1;
      city_unassigned_citizens = (int)cities[city].size + 1;
    }
    else {
      city_unassigned_citizens = (int)cities[city].size + 1;
      for (local_64 = 0; local_64 < 0x15; local_64++) {
        if (local_64 == 0) {
          local_80 = 0x14;
        }
        else {
          local_80 = local_64 - 1;
        }
        iVar4 = city_tile_worked(city,local_80);
        if (iVar4 != 0) {
          city_calc_tile_yields(city,local_80,1);
          aiStack_58[local_80] = 1;
          local_7c = local_7c | 1 << ((byte)local_80 & 0x1f);
          city_unassigned_citizens--;
          if (city_unassigned_citizens == 0) break;
        }
      }
    }
    if ((city_unassigned_citizens == local_60) || (city_unassigned_citizens == 0)) goto LAB_004e9651;
  }
  if ((0 < (int)city_unassigned_citizens) && (local_8 == 0)) {
    local_7c = local_7c | 0x100000;
    city_calc_tile_yields(city,0x14,1);
    local_8 = 1;
    city_unassigned_citizens--;
  }
  local_5c = 0;
  bVar3 = cosmic.food_per_citizen;
  if (cosmic.food_per_citizen < 2) {
    bVar3 = 1;
  }
  while (((city_yield_totals + (int)city_unassigned_citizens / (int)(uint)bVar3 <
           (int)((int)cities[city].size * (uint)cosmic.food_per_citizen +
                city_settlers_supported * settler_food_cost) || (cities[city].size < 3)) &&
         ((city_unassigned_citizens != local_60 && -1 < (int)(city_unassigned_citizens - local_60) && (-1 < local_5c))))) {
    local_5c = -1;
    local_6c = 0;
    local_68 = 0;
    for (local_64 = 0; local_64 < 0x14; local_64++) {
      if (aiStack_58[local_64] == 0) {
        iVar4 = city_tile_yield(city,local_64,0);
        iVar5 = city_tile_yield(city,local_64,1);
        if (((city_unassigned_citizens != 1) || (city_total_shields != 0)) || (iVar5 * 2 != 0)) {
          iVar6 = city_tile_yield(city,local_64,2);
          iVar6 = iVar5 * 2 + iVar6;
          if ((local_68 < iVar4) || ((iVar4 == local_68 && (local_6c < iVar6)))) {
            local_5c = local_64;
            local_6c = iVar6;
            local_68 = iVar4;
          }
        }
      }
    }
    if (-1 < local_5c) {
      aiStack_58[local_5c] = 1;
      city_calc_tile_yields(city,local_5c,1);
      local_7c = local_7c | 1 << ((byte)local_5c & 0x1f);
      city_unassigned_citizens--;
    }
  }
  if ((((1 << (civ & 0x1f) & (uint)game.human_players) == 0) && ((cities[city].flags & 1) != 0)
      ) && (city_turn_worker_realloc != 0)) {
    cities[city].flags = cities[city].flags | 0x8000;
    local_60++;
  }
  for (; city_unassigned_citizens != local_60 && -1 < (int)(city_unassigned_citizens - local_60);
      city_unassigned_citizens = city_unassigned_citizens - 1) {
    local_5c = -1;
    local_6c = 0;
    for (local_64 = 0; local_64 < 0x14; local_64++) {
      if (aiStack_58[local_64] == 0) {
        city_calc_tile_yields(city,local_64,0);
        iVar4 = int_clamp((city_yield_totals -
                                   (int)cities[city].size * (uint)cosmic.food_per_citizen) -
                                   city_settlers_supported * settler_food_cost,1,99);
        iVar4 = (int)(0x10 / (longlong)iVar4) * city_tile_yields;
        cVar2 = cities[city].size;
        iVar5 = int_clamp(city_total_shields - city_shield_support,1,99);
        iVar5 = ((cVar2 * 3) / iVar5) * city_tile_shields;
        cVar2 = cities[city].size;
        iVar6 = int_clamp(city_total_trade,1,99);
        iVar4 = iVar4 + iVar5 + ((cVar2 * 2) / iVar6) * city_tile_trade;
        if (local_6c < iVar4) {
          local_5c = local_64;
          local_6c = iVar4;
        }
      }
    }
    if (local_5c < 0) break;
    aiStack_58[local_5c] = 1;
    city_calc_tile_yields(city,local_5c,1);
    local_7c = local_7c | 1 << ((byte)local_5c & 0x1f);
  }
LAB_004e9651:
  cities[city].worked_tiles = city_unassigned_citizens * 0x4000000 + local_7c;
  if (city_yield_totals <
      (int)((int)cities[city].size * (uint)cosmic.food_per_citizen + city_settlers_supported * settler_food_cost)
     ) {
    if (cities[city].food_box == 0) {
      cities[city].food_box--;
    }
  }
  else if (cities[city].food_box < 0) {
    cities[city].food_box = 0;
  }
  return;
}
#undef city_shield_support
#undef city_tile_yields
#undef city_total_shields
#undef city_total_trade
#undef city_turn_worker_realloc
#undef city_unassigned_citizens
#undef city_workers_overflow
#undef city_yield_totals
#undef settler_food_cost
#undef local_80
#undef local_7c
#undef local_6c
#undef local_68
#undef local_64
#undef local_60
#undef local_5c
#undef aiStack_58
#undef local_8

/* 004e9719 auto */
void __cdecl city_adjust_specialists(iptr city,int param_2)

{
  if (param_2 < 0) {
    for (; param_2 != 0; param_2++) {
      if (0x3ffffff < cities[city].worked_tiles) {
        cities[city].worked_tiles += 0xfc000000;
      }
    }
  }
  else {
    for (; param_2 != 0; param_2--) {
      cities[city].worked_tiles += 0x4000000;
    }
  }
  return;
}

/* 004e97ae auto */
#define city_specialist_count (*(int *)((u8 *)&g.d_006a6604))
#define city_unassigned_citizens (*(int *)((u8 *)&g.d_006a654c))
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl city_fill_specialists(iptr city)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  city_specialist_count = city_unassigned_citizens;
  for (local_8 = 0; local_8 < city_specialist_count; local_8++) {
    iVar1 = city_specialist_type(city,local_8);
    if (iVar1 == 0) {
      city_set_specialist_type(city,local_8,1);
    }
  }
  for (local_8 = city_specialist_count; local_8 < 0x10; local_8++) {
    city_set_specialist_type(city,local_8,0);
  }
  return;
}
#undef city_specialist_count
#undef city_unassigned_citizens
#undef local_8

/* 004e9849 auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
int __cdecl city_corruption_divisor(iptr param_1,int param_2)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 4;
  if (0 < param_2) {
    local_8 = 5;
  }
  if (1 < param_2) {
    local_8++;
  }
  if (2 < param_2) {
    local_8++;
  }
  if (4 < param_2) {
    local_8++;
  }
  return local_8;
}
#undef local_8

/* 004e989a auto */
#define city_turn_processing (*(int *)((u8 *)&g.d_0062edf8))
#define local_28 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_20 (*(uint *)(frame_ + FRAME_OFF(8)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_c (*(int *)(frame_ + FRAME_OFF(28)))
int __cdecl city_calc_corruption(iptr city,int param_2,int param_3,int param_4)

{
  byte civ2;
  iptr civ;
  int iVar3;
  uint uVar4;
  bool bVar5;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_2 < 1) {
    local_c = 0;
  }
  else {
    civ2 = cities[city].owner;
    civ = (iptr)(char)civ2;
    local_20 = (uint)civs[civ].government;
    bVar5 = local_20 == 3;
    if ((cities[city].flags & 2) != 0) {
      local_20++;
    }
    if (((city_turn_processing != 0) && (param_4 != 0)) || (!bVar5)) {
      local_18 = city_capital_distance;
      if ((param_3 != 0) && (0x10 < city_capital_distance)) {
        local_18 = 0x10;
      }
      local_1c = local_18;
      if (((local_20 < 2) && (local_18 != 0)) &&
         ((1 << (civ2 & 0x1f) & (uint)game.human_players) != 0)) {
        local_1c = int_clamp((uint)game.difficulty + local_18,0,0x20);
      }
      iVar3 = city_corruption_divisor(city,local_20);
      local_10 = (local_1c * param_2 * 3) / (iVar3 * 0x14);
    }
    if (((city_turn_processing != 0) && (param_4 != 0)) || (bVar5)) {
      uVar4 = (uint)cosmic.communism_palace_dist;
      iVar3 = city_corruption_divisor(city,local_20);
      local_24 = (int)(uVar4 * param_2 * 3) / (iVar3 * 0x14);
    }
    if (bVar5) {
      local_c = local_24;
    }
    else {
      local_c = local_10;
    }
    local_c = int_clamp(local_c,0,param_2);
    iVar3 = city_has_improvement(city,7);
    if ((iVar3 != 0) || (iVar3 = city_has_improvement(city,1), iVar3 != 0)) {
      local_c = local_c >> 1;
    }
    if ((city_turn_processing != 0) && (param_4 != 0)) {
      for (local_28 = 1; local_28 < 6; local_28++) {
        local_20 = local_28;
        if (local_28 == 3) {
          civs[civ].government_score[3] -= (short)local_24;
        }
        else if (local_28 != 4) {
          if ((cities[city].flags & 2) != 0) {
            local_20 = local_28 + 1;
          }
          local_1c = local_18;
          if ((((int)local_20 < 2) && (local_18 != 0)) &&
             ((1 << (civ2 & 0x1f) & (uint)game.human_players) != 0)) {
            local_1c = int_clamp((uint)game.difficulty + local_18,0,0x20);
          }
          iVar3 = city_corruption_divisor(city,local_20);
          civs[civ].government_score[local_28] =
               civs[civ].government_score[local_28] -
               (short)((local_1c * param_2 * 3) / (iVar3 * 0x14));
        }
      }
    }
  }
  return local_c;
}
#undef city_turn_processing
#undef local_28
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_10
#undef local_c

/* 004e9c14 auto */
#define city_capital_link (*(int *)((u8 *)&g.d_006a6574))
#define city_shield_support (*(int *)((u8 *)&g.d_006a6568))
#define city_total_shields (*(int *)((u8 *)&g.d_006a65cc))
#define local_c (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(8)))
void __cdecl city_calc_shields_pollution(iptr city)

{
  iptr civ;
  int iVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  local_c = 0;
  civ = (iptr)cities[city].owner;
  city_pollution_divisor = 1;
  iVar2 = city_has_improvement(city,0xf);
  if (iVar2 != 0) {
    local_8 = 2;
  }
  iVar2 = city_has_improvement(city,0x10);
  if (iVar2 != 0) {
    local_8 += 2;
  }
  iVar2 = city_has_improvement(city,0x13);
  if (iVar2 != 0) {
    local_c = 2;
  }
  iVar2 = city_has_improvement(city,0x14);
  if (iVar2 == 0) {
    iVar2 = city_has_improvement(city,0x15);
    if (iVar2 == 0) {
      iVar2 = civ_has_wonder((int)cities[city].owner,0x16);
      if (iVar2 != 0) {
        local_c = 2;
        city_pollution_divisor = 2;
      }
      goto LAB_004e9d15;
    }
  }
  local_c = 2;
  city_pollution_divisor = 2;
LAB_004e9d15:
  iVar2 = city_has_improvement(city,0x12);
  if (iVar2 != 0) {
    city_pollution_divisor = 3;
  }
  iVar2 = city_has_improvement(city,0x1d);
  if (iVar2 != 0) {
    local_c = 2;
    city_pollution_divisor = 3;
  }
  if (local_8 <= local_c) {
    local_c = local_8;
  }
  city_total_shields = city_total_shields +
                 ((int)(city_total_shields * local_8) >> 2) + ((int)(city_total_shields * local_c) >> 2);
  city_pop_pollution_factor = 0;
  iVar2 = city_has_improvement(city,0xd);
  if (iVar2 == 0) {
    iVar2 = civ_has_advance(civ,0x25);
    if (iVar2 != 0) {
      city_pop_pollution_factor++;
    }
    iVar2 = civ_has_advance(civ,5);
    if (iVar2 != 0) {
      city_pop_pollution_factor++;
    }
    iVar2 = civ_has_advance(civ,0x30);
    if (iVar2 != 0) {
      city_pop_pollution_factor++;
    }
    iVar2 = civ_has_advance(civ,0x3e);
    if (iVar2 != 0) {
      city_pop_pollution_factor++;
    }
    if (city_pop_pollution_factor != 0) {
      iVar2 = civ_has_advance(civ,0x4a);
      if (iVar2 == 0) {
        city_pop_pollution_factor++;
      }
    }
    if (city_pop_pollution_factor != 0) {
      iVar2 = civ_has_advance(civ,0x1a);
      if (iVar2 != 0) {
        city_pop_pollution_factor--;
      }
    }
    if (city_pop_pollution_factor != 0) {
      iVar2 = city_has_improvement(city,0x1d);
      if (iVar2 != 0) {
        city_pop_pollution_factor--;
      }
    }
  }
  city_pollution = city_total_shields / city_pollution_divisor - 0x14;
  iVar2 = city_has_improvement(city,0x1d);
  if (iVar2 != 0) {
    city_pollution = 0;
  }
  city_pollution += (cities[city].size * city_pop_pollution_factor >> 2);
  iVar2 = city_calc_corruption(city,city_total_shields - city_shield_support,1,1);
  iVar2 = (((3 - city_capital_link) * iVar2) / 3) / (((int)(uint)civs[civ].government >> 1) + 1);
  city_shield_waste = city_total_shields - (city_shield_support + 1);
  if (iVar2 <= city_shield_waste) {
    city_shield_waste = iVar2;
  }
  if (city_shield_waste < 1) {
    city_shield_waste = 0;
  }
  if ((((civ == 0) || (civs[civ].government == 6)) || (civs[civ].government == 4))
     || ((cities[city].building == -1 && (city_capital_nearest < 0)))) {
    city_shield_waste = 0;
  }
  city_total_shields -= city_shield_waste;
  return;
}
#undef city_capital_link
#undef city_shield_support
#undef city_total_shields
#undef local_c
#undef local_8

/* 004ea031 auto */
#define city_angry_count (*(i8 *)((u8 *)&g.d_006a659c))
#define city_happy_count (*(i8 *)((u8 *)&g.d_006a6550))
#define city_unassigned_citizens (*(int *)((u8 *)&g.d_006a654c))
#define city_unhappy_count (*(i8 *)((u8 *)&g.d_006a65a8))
void __cdecl city_happy_clamp_stage(iptr city,iptr param_2)

{
  int iVar1;
  
  city_happy_count = int_clamp(city_happy_count,0,(int)cities[city].size);
  for (; (city_angry_count != 0 && (city_unhappy_count < city_angry_count)); city_unhappy_count++) {
    city_angry_count--;
  }
  city_unhappy_count = int_clamp(city_unhappy_count,0,(int)cities[city].size);
  while( true ) {
    iVar1 = int_clamp(cities[city].size - city_unassigned_citizens,0,99);
    if (city_unhappy_count + city_happy_count <= iVar1) break;
    if (city_angry_count == 0) {
      city_happy_count--;
      city_happy_count = int_clamp(city_happy_count,0,(int)cities[city].size);
    }
    else {
      city_angry_count--;
    }
    city_unhappy_count--;
    city_unhappy_count = int_clamp(city_unhappy_count,0,(int)cities[city].size);
  }
  for (; (city_angry_count != 0 && (city_unhappy_count + city_happy_count < cities[city].size - city_unassigned_citizens));
      city_unhappy_count = city_unhappy_count + 1) {
    city_angry_count--;
  }
  if (-1 < param_2) {
    (&city_happy_by_stage)[param_2] = (i8)city_happy_count;
    (&city_unhappy_by_stage)[param_2] = (i8)city_unhappy_count;
    (&city_angry_by_stage)[param_2] = (i8)city_angry_count;
  }
  return;
}
#undef city_angry_count
#undef city_happy_count
#undef city_unassigned_citizens
#undef city_unhappy_count

/* 004ea1f6 auto */
#define city_building_content (*(int *)((u8 *)&g.d_006a6618))
#define city_science_total (*(int *)((u8 *)&g.d_006a6578))
#define city_shield_support (*(int *)((u8 *)&g.d_006a6568))
#define city_tax_total (*(int *)((u8 *)&g.d_006a6554))
#define city_total_shields (*(int *)((u8 *)&g.d_006a65cc))
#define city_turn_processing (*(int *)((u8 *)&g.d_0062edf8))
#define local_18 (*(uint *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(16)))
void __cdecl city_split_trade(iptr city,int param_2,int param_3,int param_4)

{
  byte civ2;
  iptr civ;
  int iVar3;
  int iVar4;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((param_3 == 1) && (cities[city].building == -0x26)) {
    local_c = param_2;
    param_2 = (int)cities[city].trade;
  }
  civ2 = cities[city].owner;
  civ = (iptr)(char)civ2;
  local_18 = (uint)civs[civ].science_rate;
  if ((civs[civ].government == 4) && (cosmic.fund_max_science < local_18)) {
    local_18 = (uint)cosmic.fund_max_science;
  }
  city_lux_total = int_clamp((int)(param_2 * (10 - ((uint)civs[civ].science_rate +
                                                          (uint)civs[civ].tax_rate)) + 4) / 10,0,
                                    param_2);
  city_science_total = int_clamp((int)(param_2 * local_18 + 4) / 10,0,param_2 - city_lux_total);
  city_tax_total = param_2 - (city_science_total + city_lux_total);
  if (city_turn_processing != 0) {
    civs[civ].government_score[4] += (short)(city_lux_total / 2);
    iVar3 = (leaders[civs[civ].tribe].civilize + 3) * city_science_total;
    civs[civ].government_score[4] =
         civs[civ].government_score[4] - (short)((int)(iVar3 + (iVar3 >> 0x1f & 3U)) >> 2);
  }
  if (((1 << (civ2 & 0x1f) & (uint)game.human_players) == 0) && (civs[civ].government == 4))
  {
    city_science_total += city_lux_total;
    city_lux_total = 0;
  }
  iVar3 = city_count_specialists(city,1);
  city_lux_total += iVar3 * 2;
  iVar3 = city_count_specialists(city,2);
  city_tax_total += iVar3 * 3;
  iVar3 = city_count_specialists(city,3);
  city_science_total += iVar3 * 3;
  if (civs[civ].government == 4) {
    city_science_total -= (int)((uint)cosmic.fund_science_loss * city_science_total) / 100;
  }
  city_building_content = 0;
  iVar3 = city_has_improvement(city,4);
  if (iVar3 != 0) {
    iVar3 = civ_has_advance(civ,0x38);
    if (iVar3 != 0) {
      city_building_content++;
    }
    iVar3 = civ_has_advance(civ,9);
    if (iVar3 != 0) {
      city_building_content++;
    }
    iVar3 = civ_has_wonder(civ,5);
    if (iVar3 != 0) {
      city_building_content = city_building_content << 1;
    }
  }
  iVar3 = city_has_improvement(city,0xe);
  if (iVar3 != 0) {
    city_building_content += 3;
    iVar3 = civ_has_advance(civ,0x18);
    if (iVar3 != 0) {
      city_building_content++;
    }
  }
  iVar3 = civ_has_advance(civ,0x37);
  if ((iVar3 != 0) &&
     ((iVar3 = city_has_improvement(city,0xb), iVar3 != 0 ||
      (iVar3 = civ_has_wonder(civ,10), iVar3 != 0)))) {
    iVar3 = civ_has_advance(civ,0xf);
    iVar4 = civ_has_advance(civ,0x52);
    city_building_content = city_building_content + (uint)(iVar3 == 0) + (3 - (uint)(iVar4 == 0));
  }
  iVar3 = civ_has_wonder(civ,0xf);
  if (iVar3 != 0) {
    city_building_content += 2;
  }
  if (civs[civ].government == 4) {
    city_tax_total += city_building_content;
  }
  iVar3 = city_has_improvement(city,5);
  local_8 = (uint)(iVar3 != 0);
  iVar3 = city_has_improvement(city,10);
  if (iVar3 != 0) {
    local_8++;
  }
  iVar3 = city_has_improvement(city,0x16);
  if (iVar3 != 0) {
    local_8++;
  }
  city_lux_total += ((int)(city_lux_total * local_8) >> 1);
  city_tax_total += ((int)(city_tax_total * local_8) >> 1);
  if (city_turn_processing != 0) {
    civs[civ].government_score[4] =
         civs[civ].government_score[4] + (short)((int)((local_8 + 2) * city_building_content) >> 1);
  }
  iVar3 = city_has_improvement(city,6);
  local_8 = (uint)(iVar3 != 0);
  iVar3 = city_has_improvement(city,0xc);
  if (iVar3 != 0) {
    local_8++;
  }
  iVar3 = city_has_improvement(city,0x1a);
  if ((iVar3 != 0) || (iVar3 = civ_has_wonder(civ,0x1a), iVar3 != 0)) {
    local_8++;
  }
  local_14 = city_science_total * local_8;
  iVar3 = wonder_get_city(0x10);
  if (iVar3 != city) {
    local_14 = local_14 >> 1;
  }
  city_science_total += local_14;
  iVar3 = wonder_get_city(0xb);
  if (iVar3 == city) {
    city_science_total = city_science_total << 1;
  }
  if (cities[city].building == -0x26) {
    if (param_3 == 0) {
      if (city_shield_support < city_total_shields) {
        city_tax_total += (city_total_shields - city_shield_support);
      }
    }
    else {
      if (param_3 == 1) {
        city_split_trade(city,local_c,2,cities[city].tax - city_tax_total);
        return;
      }
      if (param_3 == 2) {
        city_tax_total += param_4;
      }
    }
  }
  cities[city].science = (i16)city_science_total;
  cities[city].tax = (i16)city_tax_total;
  cities[city].trade = (i16)param_2;
  return;
}
#undef city_building_content
#undef city_science_total
#undef city_shield_support
#undef city_tax_total
#undef city_total_shields
#undef city_turn_processing
#undef local_18
#undef local_14
#undef local_c
#undef local_8

/* 004ea8e4 auto */
#define city_aggressive_units (*(int *)((u8 *)&g.d_006a65e4))
#define city_angry_count (*(int *)((u8 *)&g.d_006a659c))
#define city_happy_count (*(i8 *)((u8 *)&g.d_006a6550))
#define city_science_total (*(i32 *)((u8 *)&g.d_006a6578))
#define city_tax_total (*(i32 *)((u8 *)&g.d_006a6554))
#define city_total_shields (*(i8 *)((u8 *)&g.d_006a65cc))
#define city_total_trade (*(int *)((u8 *)&g.d_006a65d0))
#define city_trade_corruption (*(int *)((u8 *)&g.d_006a6580))
#define city_unhappy_count (*(i8 *)((u8 *)&g.d_006a65a8))
#define city_yield_totals (*(i8 *)((u8 *)&g.d_006a65c8))
#define unit (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_1c (*(uint *)(frame_ + FRAME_OFF(12)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(20)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(32)))
int __cdecl city_calc_trade_happiness(uptr city)

{
  byte civ2;
  char cVar2;
  iptr civ;
  iptr city2;
  int iVar5;
  int iVar6;
  int iVar7;
  uptr uVar8;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ2 = cities[city].owner;
  civ = (iptr)(char)civ2;
  city_trade_corruption = city_calc_corruption(city,city_total_trade,0,0);
  if (civs[civ].government == 4) {
    city_trade_corruption = 0;
  }
  if (civs[civ].government == 6) {
    city_trade_corruption = 0;
  }
  cities[city].base_trade = (short)city_total_trade - (short)city_trade_corruption;
  city_calc_commodity_demand(city);
  for (local_8 = 0; local_8 < (char)cities[city].trade_routes; local_8++) {
    city2 = (iptr)cities[city].route_partner[local_8];
    local_18 = (int)cities[city].base_trade + (int)cities[city2].base_trade + 4 >> 3;
    cVar2 = *(char *)&cities[city].route_goods[local_8];
    local_14 = map_road_connection((int)cities[city].owner,(int)cities[city].x,
                                  (int)cities[city].y,(int)cities[city2].x,(int)cities[city2].y);
    iVar5 = city_has_improvement(city,0x20);
    if (((iVar5 != 0) && (iVar5 = city_has_improvement(city2,0x20), iVar5 != 0)) && (local_14 < 2)) {
      local_14 = 1;
    }
    iVar5 = city_has_improvement(city,0x19);
    if (iVar5 != 0) {
      local_14++;
    }
    if (local_14 != 0) {
      local_18 += (local_14 * local_18 >> 1);
    }
    if (cVar2 < '\0') {
      local_18 = 0;
    }
    if (cities[city2].owner == civ) {
      local_18 = local_18 >> 1;
    }
    *(int *)(&city_route_trade_values + local_8 * 4) = local_18;
    city_total_trade += local_18;
  }
  city_trade_corruption = city_calc_corruption(city,city_total_trade,0,1);
  if (civs[civ].government == 4) {
    city_trade_corruption = 0;
  }
  if (civs[civ].government == 6) {
    city_trade_corruption = 0;
  }
  iVar5 = city_total_trade - city_trade_corruption;
  city_split_trade(city,iVar5,0,0);
  city_happy_count = 0;
  if ((1 << (civ2 & 0x1f) & (uint)game.human_players) == 0) {
    city_unhappy_count = (cities[city].size - 1) - (cosmic.unhappy_size - 5);
  }
  else {
    local_1c = (uint)cosmic.riot_factor + (uint)game.difficulty * -2;
    if ((game.game_flags & 4) != 0) {
      local_1c += 2;
    }
    iVar6 = (int)((((int)(uint)civs[civ].government >> 1) + 2) * local_1c) / 2;
    if (iVar6 < 2) {
      iVar6 = 1;
    }
    local_20 = (uint)cosmic.unhappy_size - (uint)game.difficulty;
    if (((local_20 < 3) && (iVar7 = city_has_improvement(city,1), iVar7 != 0)) &&
       ((city_aggressive_units == 0 && (city_home_attack_units == 0)))) {
      local_20 = 2;
    }
    city_unhappy_count = (cities[city].size - 1) - (local_20 - 2);
    if (civs[civ].government != 3) {
      city_unhappy_count = city_unhappy_count +
                     ((civs[civ].num_cities - iVar6) + (int)city % iVar6) / iVar6;
    }
  }
  city_angry_count = 0;
  if (cities[city].size < city_unhappy_count) {
    city_angry_count = city_unhappy_count - cities[city].size;
    city_unhappy_count = (int)cities[city].size;
  }
  city_happy_clamp_stage(city,0);
  city_happy_count = city_lux_total >> 1;
  city_happy_clamp_stage(city,1);
  iVar6 = city_has_improvement(city,0xe);
  if (iVar6 != 0) {
    city_unhappy_count -= 3;
    iVar6 = civ_has_advance(civ,0x18);
    if (iVar6 != 0) {
      city_unhappy_count--;
    }
  }
  iVar6 = civ_has_advance(civ,0x37);
  if ((iVar6 != 0) &&
     ((iVar6 = city_has_improvement(city,0xb), iVar6 != 0 ||
      (iVar6 = civ_has_wonder(civ,10), iVar6 != 0)))) {
    iVar6 = civ_has_advance(civ,0xf);
    iVar7 = civ_has_advance(civ,0x52);
    city_unhappy_count -= ((uint)(iVar6 == 0) + (3 - (uint)(iVar7 == 0)));
  }
  iVar6 = city_has_improvement(city,4);
  if (iVar6 != 0) {
    iVar6 = civ_has_advance(civ,0x38);
    local_1c = (uint)(iVar6 != 0);
    iVar6 = civ_has_advance(civ,9);
    if (iVar6 != 0) {
      local_1c++;
    }
    iVar6 = civ_has_wonder(civ,5);
    if (iVar6 != 0) {
      local_1c = local_1c << 1;
    }
    city_unhappy_count -= local_1c;
  }
  iVar6 = city_has_improvement(city,7);
  if (((iVar6 != 0) || (iVar6 = city_has_improvement(city,1), iVar6 != 0)) &&
     (civs[civ].government == 6)) {
    city_happy_count++;
  }
  city_happy_clamp_stage(city,2);
  if (civs[civ].government == 4) {
    city_angry_count = 0;
    city_unhappy_count = 0;
  }
  else if (civs[civ].government < 5) {
    city_martial_law_units = 0;
    for (unit = tile_first_unit((int)cities[city].x,(int)cities[city].y);
        iVar6 = city_martial_law_units, -1 < unit; unit = unit_next_in_stack(unit)) {
      if ((unit_types[units[unit].type].attack != '\0') &&
         (city_martial_law_units = city_martial_law_units + 1, civs[civ].government == 3)) {
        city_martial_law_units = iVar6 + 2;
      }
    }
    local_1c = 3;
    if (civs[civ].government == 3) {
      local_1c = 6;
    }
    if ((int)local_1c <= (int)city_martial_law_units) {
      city_martial_law_units = local_1c;
    }
    iVar6 = int_clamp(city_martial_law_units,0,city_unhappy_count);
    city_unhappy_count -= iVar6;
  }
  else {
    iVar6 = civ_has_wonder(civ,0x15);
    if ((iVar6 == 0) && (iVar6 = city_has_improvement(city,0x21), iVar6 == 0)) {
      local_10 = 1;
    }
    else {
      local_10 = 0;
    }
    if (civs[civ].government == 6) {
      local_10++;
    }
    if (local_10 != 0) {
      local_1c = city_aggressive_units;
      if ((city_aggressive_units != 0) && (civs[civ].government == 5)) {
        local_1c = city_aggressive_units - 1;
      }
      city_unhappy_count += local_10 * local_1c;
    }
  }
  city_happy_clamp_stage(city,3);
  iVar6 = civ_has_wonder(civ,1);
  if (iVar6 != 0) {
    city_happy_count++;
    uVar8 = wonder_get_city(1);
    if (uVar8 == city) {
      city_happy_count += 2;
    }
  }
  iVar6 = civ_has_wonder(civ,0x1b);
  if (iVar6 != 0) {
    city_happy_count++;
  }
  uVar8 = wonder_get_city(0xd);
  if (uVar8 == city) {
    city_unhappy_count = 0;
  }
  iVar6 = civ_has_wonder(civ,0xf);
  if (iVar6 != 0) {
    city_unhappy_count -= 2;
  }
  city_happy_clamp_stage(city,4);
  cities[city].science = (i16)city_science_total;
  cities[city].tax = (i16)city_tax_total;
  cities[city].trade = (i16)iVar5;
  cities[city].total_food = (u8)city_yield_totals;
  cities[city].total_shields = (u8)city_total_shields;
  cities[city].happy = (u8)city_happy_count;
  cities[city].unhappy = (u8)city_unhappy_count;
  return city_happy_count - city_unhappy_count;
}
#undef city_aggressive_units
#undef city_angry_count
#undef city_happy_count
#undef city_science_total
#undef city_tax_total
#undef city_total_shields
#undef city_total_trade
#undef city_trade_corruption
#undef city_unhappy_count
#undef city_yield_totals
#undef unit
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_8

/* 004eb327 auto */
#define city_yield_totals (*(int *)((u8 *)&g.d_006a65c8))
#define city2 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(8)))
void __cdecl city_count_food_routes(iptr city)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  city_food_routes_out = 0;
  city_food_routes_in = 0;
  city_food_route_partner = -1;
  for (local_8 = 0; local_8 < (char)cities[city].trade_routes; local_8++) {
    if (*(char *)&cities[city].route_goods[local_8] < '\0') {
      city_food_routes_out++;
      city_food_route_partner = (int)cities[city].route_partner[local_8];
    }
  }
  city_yield_totals -= city_food_routes_out;
  for (city2 = 0; city2 < game.num_cities; city2++) {
    if (cities[city2].id != 0) {
      for (local_8 = 0; local_8 < (char)cities[city2].trade_routes; local_8++) {
        if ((cities[city2].route_partner[local_8] == city) &&
           (*(char *)&cities[city2].route_goods[local_8] < '\0')) {
          city_yield_totals++;
          city_food_routes_in++;
        }
      }
    }
  }
  return;
}
#undef city_yield_totals
#undef city2
#undef local_8

/* 004eb4a1 auto */
void __cdecl city_calc_all_stats(iptr city)

{
  city_assign_workers(city);
  city_count_food_routes(city);
  city_fill_specialists(city);
  city_calc_shields_pollution(city);
  city_calc_trade_happiness(city);
  return;
}

/* 004eb4ed: written by hand in src/game/retvals.c */

/* 004eb571 auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define city_notify_enabled (*(int *)((u8 *)&g.d_006a65ac))
#define city_zoom_requested (*(int *)((u8 *)&g.d_006a65a0))
#define local_304 (*(Dialog *)(frame_ + FRAME_OFF(4)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(760)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(764)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(768)))
int __cdecl city_notify_dialog_ex(iptr param_1,iptr city,int param_3,iptr param_4)

{
  int iVar1;
  iptr iVar2;
  iptr iVar3;
  i32 uVar4;
  i8 frame_[FRAME_OFF(776)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_304,0x4000);
  local_8 = 0;
  if (autoplay_active == 0) {
    if ((city_notify_enabled == 0) && (param_3 == 0)) {
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_004eb7e5 */ { dialog_dtor((Dialog *)((iptr)&local_304)); }
      iVar1 = 0;
    }
    else {
      text_set_string_arg_b(0,(iptr)&cities[city].name);
      text_clear();
      text_append(param_1);
      iVar1 = _strcmp((char *)param_1,s_BUILT_0062ee40);
      if ((iVar1 == 0) && ((cities[city].flags & 0x10) != 0)) {
        text_append(ADDR(0x62ee48, ((u8 *)&g.d_0062ee48)));
      }
      dialog_load_game_text(&local_304,ADDR(0x679640, ((u8 *)&g.d_00679640)));
      mapviews_ensure_visible((int)cities[city].x,(int)cities[city].y,(int)cities[city].owner);
      if (city_zoom_requested == 0) {
        uVar4 = 0;
        iVar3 = 1;
        iVar2 = label_string(*(i32 *)(label_string_ids + 0x80));
        dialog_add_option((DialogOptionList *)&local_304,iVar2,iVar3,uVar4);
        uVar4 = 0;
        iVar3 = 0;
        iVar2 = label_string(*(i32 *)(label_string_ids + 0x84));
        dialog_add_option((DialogOptionList *)&local_304,iVar2,iVar3,uVar4);
        if ((game.message_options & 0x400) == 0) {
          dialog_set_default_choice((DialogOptionList *)&local_304,0);
        }
        else {
          dialog_set_default_choice((DialogOptionList *)&local_304,1);
        }
      }
      if (param_4 != 0) {
        dialog_add_sprite((DialogOptionList *)&local_304,param_4,0,0);
        dialog_set_image_zoom((DialogWindowView *)&local_304,8);
      }
      iVar1 = dlg_show_modal(&local_304,0);
      if (0 < iVar1) {
        city_zoom_requested = 1;
      }
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_004eb7e5 */ { dialog_dtor((Dialog *)((iptr)&local_304)); }
    }
  }
  else {
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_004eb7e5 */ { dialog_dtor((Dialog *)((iptr)&local_304)); }
    iVar1 = 0;
  }
  return iVar1;
}
#undef autoplay_active
#undef city_notify_enabled
#undef city_zoom_requested
#undef local_304
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004ebbde auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define city_food_box_rows (*(int *)((u8 *)&g.d_006a6560))
#define city_turn_window_dirty (*(i32 *)((u8 *)&g.d_0062ee04))
#define city_turn_window_shown (*(int *)((u8 *)&g.d_0062ee00))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define unit2 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(4)))
#define y2 (*(int *)(frame_ + FRAME_OFF(12)))
#define x2 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_1c (*(i8 (*)[6])(frame_ + FRAME_OFF(20)))
#define local_16 (*(i8 *)(frame_ + FRAME_OFF(26)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(40)))
i32 __cdecl city_process_food(uptr city)

{
  int iVar1;
  byte civ2;
  iptr civ;
  iptr iVar3;
  iptr improvement;
  iptr iVar4;
  int iVar6;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ2 = cities[city].owner;
  civ = (iptr)(char)civ2;
  city_calc_food_box_rows(city,civ);
  if (cities[city].food_box < 0) {
    unit2 = -1;
    for (unit = 0; unit < game.num_units; unit++) {
      if (((units[unit].id != 0) && (unit_types[units[unit].type].role == 5)) &&
         ((byte)units[unit].home_city == city)) {
        unit2 = unit;
        break;
      }
    }
    FUN_005f22d0(local_1c,s_FAMINE0_0062ee4c);
    if (unit2 < 0) {
      local_16 = 0x31;
    }
    else {
      text_set_label_arg(1,unit_types[units[unit2].type].name);
    }
    if (-1 < city_food_route_partner) {
      local_16 = 0x32;
      text_set_string_arg(1,(iptr)&cities[city_food_route_partner].name);
    }
    if (autoplay_active == 0) {
      city_notify_dialog_ex((iptr)local_1c,city,0,0);
    }
    if (city_food_routes_out < 1) {
      if (unit2 < 0) {
        cities[city].size--;
        x2 = (int)cities[city].x;
        y2 = (int)cities[city].y;
        if (cities[city].size < 1) {
          city_delete(city,0);
          civ_check_destroyed(civ,0);
          return 1;
        }
      }
      else if (((1 << (civ2 & 0x1f) & (uint)game.human_players) != 0) ||
              ((game.human_players & cities[city].known_to) != 0)) {
        unit_delete_with_cargo(unit2,1);
      }
    }
    else {
      iVar6 = (int)(char)cities[city].trade_routes;
      while (local_8 = iVar6 - 1, -1 < local_8) {
        iVar1 = iVar6 + ADDR(0x64f380, ((u8 *)&cities + 64));
        iVar6 = local_8;
        if ((*(char *)(iVar1 + city * 0x58) < '\0') &&
           (cities[city].route_partner[local_8] == city_food_route_partner)) {
          city_remove_trade_route(city,local_8);
          iVar6 = local_8;
        }
      }
    }
    cities[city].food_box = 0;
    map_redraw_area_all_views(x2,y2,0,human_civ,1);
    if (city_turn_window_shown != 0) {
      city_turn_window_dirty = 1;
    }
  }
  else {
    iVar3 = (cities[city].size + 1) * city_food_box_rows;
    if (iVar3 - cities[city].food_box == 0 || iVar3 < cities[city].food_box) {
      if (city_turn_window_shown != 0) {
        city_window_draw_food_box((C_004083b0_12c *)&city_window,1);
      }
      improvement = city_needed_size_improvement(city);
      cities[city].size++;
      iVar4 = city_has_improvement(city,3);
      if ((iVar4 == 0) && (iVar6 = civ_has_wonder(civ,0), iVar6 == 0)) {
        cities[city].food_box = 0;
      }
      else {
        cities[city].food_box =
             (cities[city].size + 1) * (short)((int)(uint)cosmic.food_box_rows >> 1);
      }
      if (improvement != 0) {
        cities[city].size--;
        text_set_label_arg(1,improvements[improvement].name);
        if (((((1 << (civ2 & 0x1f) & (uint)game.human_players) == 0) ||
             (((*(i8 *)((char *)&game.game_options + 1)) & 1) == 0)) || ((game.field_0c & 8) != 0)) || (improvement != 9)) {
          if (((int)cities[city].building != -improvement) && ((game.message_options & 1) == 0)) {
            city_notify_dialog(ADDR(0x62ee60, ((u8 *)&g.d_0062ee60)),city,(iptr)(&improvement_icon_sprites + improvement * 0x3c));
          }
        }
        else {
          text_set_number_arg_u8(0,(uint)CONCAT11((char)(game.field_0c >> 8),cosmic.aqueduct_size));
          city_notify_dialog(ADDR(0x62ee54, ((u8 *)&g.d_0062ee54)),city,ADDR(0x64537c, ((u8 *)&g.d_006451d8 + 420)));
          game.field_0c = game.field_0c | 8;
        }
      }
      if (((1 << (civ2 & 0x1f) & (uint)game.human_players) == 0) &&
         (cities[city].size == 2)) {
        city_set_production(city,99);
      }
      if (city_turn_window_shown != 0) {
        city_window_draw_food_box((C_004083b0_12c *)&city_window,1);
        city_window_draw_citizens((FrameWindow *)&city_window,1,0);
        city_turn_window_dirty = 1;
      }
    }
    map_redraw_area_all_views((int)cities[city].x,(int)cities[city].y,0,human_civ,1);
  }
  return 0;
}
#undef autoplay_active
#undef city_food_box_rows
#undef city_turn_window_dirty
#undef city_turn_window_shown
#undef human_civ
#undef unit2
#undef unit
#undef y2
#undef x2
#undef local_1c
#undef local_16
#undef local_8

/* 004ec3fe auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define city_notify_enabled (*(int *)((u8 *)&g.d_006a65ac))
#define city_shield_rows (*(int *)((u8 *)&g.d_006a657c))
#define city_shield_support (*(int *)((u8 *)&g.d_006a6568))
#define city_total_shields (*(int *)((u8 *)&g.d_006a65cc))
#define city_turn_window_shown (*(int *)((u8 *)&g.d_0062ee00))
#define city_zoom_requested (*(i32 *)((u8 *)&g.d_006a65a0))
#define dlg_help_pressed (*(int *)((u8 *)&g.d_00631edc))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define _DAT_006a6610 (*(i32 *)((u8 *)&g.d_006a6610))
#define local_978 (*(uint *)(frame_ + FRAME_OFF(0)))
#define local_974 (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_970 (*(i8 * *)(frame_ + FRAME_OFF(8)))
#define local_96c (*(i8 * *)(frame_ + FRAME_OFF(12)))
#define local_968 (*(char *)(frame_ + FRAME_OFF(16)))
#define local_964 (*(int *)(frame_ + FRAME_OFF(20)))
#define local_960 (*(Dialog *)(frame_ + FRAME_OFF(24)))
#define local_66c (*(Dialog *)(frame_ + FRAME_OFF(780)))
#define local_378 (*(Dialog *)(frame_ + FRAME_OFF(1536)))
#define civ (*(uptr *)(frame_ + FRAME_OFF(2292)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(2296)))
#define local_7c (*(uptr *)(frame_ + FRAME_OFF(2300)))
#define local_78 (*(iptr *)(frame_ + FRAME_OFF(2304)))
#define civ3 (*(int *)(frame_ + FRAME_OFF(2308)))
#define improvement2 (*(iptr *)(frame_ + FRAME_OFF(2312)))
#define city2 (*(uptr *)(frame_ + FRAME_OFF(2316)))
#define local_68 (*(int *)(frame_ + FRAME_OFF(2320)))
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(2324)))
#define local_60 (*(iptr *)(frame_ + FRAME_OFF(2328)))
#define local_5c (*(int *)(frame_ + FRAME_OFF(2332)))
#define local_58 (*(int *)(frame_ + FRAME_OFF(2336)))
#define y2 (*(int *)(frame_ + FRAME_OFF(2340)))
#define x2 (*(int *)(frame_ + FRAME_OFF(2344)))
#define city3 (*(uptr *)(frame_ + FRAME_OFF(2348)))
#define local_48 (*(iptr *)(frame_ + FRAME_OFF(2352)))
#define local_44 (*(int *)(frame_ + FRAME_OFF(2356)))
#define local_40 (*(iptr *)(frame_ + FRAME_OFF(2360)))
#define local_3c (*(iptr *)(frame_ + FRAME_OFF(2364)))
#define local_38 (*(uint *)(frame_ + FRAME_OFF(2368)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(2372)))
#define civ2 (*(uptr *)(frame_ + FRAME_OFF(2376)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(2380)))
#define unit2 (*(iptr *)(frame_ + FRAME_OFF(2384)))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(2388)))
#define unit_type2 (*(iptr *)(frame_ + FRAME_OFF(2392)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(2396)))
#define local_18 (*(iptr *)(frame_ + FRAME_OFF(2400)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(2404)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(2408)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(2412)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(2416)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl city_process_production(uptr city)

{
  byte bVar1;
  iptr iVar2;
  int iVar3;
  int iVar4;
  iptr iVar5;
  iptr iVar7;
  i32 uVar8;
  iptr iVar6;
  i8 frame_[FRAME_OFF(2424)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  improvement = -1;
  local_14 = 0;
  _DAT_006a6610 = -1;
  civ = (uptr)cities[city].owner;
  local_2c = city_total_shields - city_shield_support;
  if ((cities[city].flags & 1) != 0) {
    local_2c = 0;
  }
  if (local_2c < 1) {
    local_2c = 0;
  }
  if (cities[city].building != -0x26) {
    cities[city].shield_box += (short)local_2c;
  }
  if (((civ == 0) &&
      (local_60 = tile_landmass((int)cities[city].x,(int)cities[city].y),
      0x10 < civs[civ].continent_military[local_60])) &&
     (iVar2 = tile_unit_owner((int)cities[city].x,(int)cities[city].y), -1 < iVar2)) {
    cities[city].shield_box = 0;
  }
  if (cities[city].building < '\0') {
    if (cities[city].building < 1) {
      improvement = ~(int)cities[city].building + 1;
    }
    else {
      improvement = (iptr)cities[city].building;
    }
    local_3c = -1;
    local_58 = (uint)improvements[improvement].cost * city_shield_rows;
    if (0x26 < improvement) {
      local_3c = improvement - 0x27;
    }
    if ((autoplay_active == 0) &&
       ((((-1 < local_3c && (game.wonder_city[local_3c] != -1)) ||
         ((local_3c < 0 && (iVar3 = city_has_improvement(city,improvement), iVar3 != 0)))) &&
        (text_set_label_arg(1,improvements[improvement].name), (game.message_options & 8) == 0)))) {
      if (local_3c < 0) {
        local_96c = &improvement_icon_sprites + improvement * 0x3c;
      }
      else {
        local_96c = &wonder_icon_sprites + local_3c * 0x3c;
      }
      city_notify_dialog(ADDR(0x62eec4, ((u8 *)&g.d_0062eec4)),city,(iptr)local_96c);
    }
    if (((improvement < 0x23) || (0x25 < improvement)) ||
       (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0 ||
        ((iVar3 = civ_spaceship_launched(civ), iVar3 == 0 &&
         (iVar3 = civ_spaceship_part_maxed(civ,improvement), iVar3 == 0)))))) {
      if ((local_58 <= cities[city].shield_box) && (improvement != 0x26)) {
        cities[city].flags = cities[city].flags & 0xfffffeff;
        local_14 = 0;
        if (local_3c < 0) {
          iVar3 = city_has_improvement(city,improvement);
          if (iVar3 != 0) {
            improvement = -1;
          }
        }
        else {
          if ((game.wonder_city[local_3c] == -1) &&
             ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0)) {
            for (city2 = 0; (int)city2 < (int)game.num_cities; city2++) {
              if ((((cities[city2].id != 0) &&
                   (((uint)game.human_players & 1 << (cities[city2].owner & 0x1fU)) != 0)) &&
                  (cities[city2].building == cities[city].building)) &&
                 (iVar3 = (uint)improvements[improvement].cost * (uint)cosmic.shield_box_rows,
                 iVar3 - cities[city2].shield_box == 0 || iVar3 < cities[city2].shield_box))
              goto LAB_004eef15;
            }
          }
          if (((game.multiplayer < 3) && (game.wonder_city[local_3c] == -1)) ||
             ((2 < game.multiplayer &&
              (local_14 = city_acquire_wonder(civ,city,local_3c,local_58,improvement),
              local_14 != 0)))) {
            if (game.multiplayer < 3) {
              game.wonder_city[local_3c] = (i16)city;
              cities[city].flags = cities[city].flags | 0x100;
            }
          }
          else {
            local_3c = -1;
            improvement = -1;
            if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
              city_set_production(city,99);
            }
          }
        }
        if (((improvement < 0x23) || (0x25 < improvement)) ||
           ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) {
LAB_004eda9a:
          if (-1 < improvement) {
            if (city_turn_window_shown != 0) {
              city_window_draw_production((FrameWindow *)&city_window,1);
            }
            if (local_3c == 0x17) {
              for (civ2 = 1; (int)civ2 < 8; civ2++) {
                uVar8 = int_clamp((civs[civ2].reputation + 1) / 2,0,6);
                civs[civ2].reputation = (u8)uVar8;
              }
              if (autoplay_active == 0) {
                for (civ2 = 1; (int)civ2 < 8; civ2++) {
                  if ((((1 << ((byte)civ2 & 0x1f) & (uint)game.civs_alive) != 0) &&
                      ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0)) &&
                     (((1 << ((byte)civ2 & 0x1f) & (int)(char)cities[city].known_to) != 0 ||
                      ((int)cities[city].owner == (civ2 & 0xff))))) {
                    if (human_civ == civ2) {
                      snd_play_effect(0x23,1,0,0);
                      city_notify_dialog(ADDR(0x62eedc, ((u8 *)&g.d_0062eedc)),city,ADDR(0x645fe8, ((u8 *)&g.d_00645fe8)));
                    }
                    else if (2 < game.multiplayer) {
                      net_send_text_args(0x46,*(i32 *)
                                               (&net_player_slots +
                                               *(int *)(&net_civ_slots + civ2 * 4) * 0x54),1,0,
                                         city,0);
                    }
                  }
                }
              }
            }
            if (local_14 == 0) {
              city_set_improvement(city,improvement,1);
              cities[city].shield_box -= (short)local_58;
            }
            if (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) &&
               (improvement < 0x23)) {
              if (improvement == 1) {
                cities[city].building--;
              }
              city_set_production(city,99);
            }
            else {
              if ((human_civ == civ) || (0x22 < improvement)) {
                local_5c = 1;
              }
              else {
                local_5c = 0;
              }
              if (autoplay_active != 0) {
                local_5c = 0;
              }
              if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
                cities[city].known_to = 0xff;
              }
              text_set_label_arg(1,improvements[improvement].name);
              iVar5 = civ_get_adjective(civ);
              text_set_string_arg(2,iVar5);
              city3 = 0xbb;
              if (local_3c == 0x1b) {
                city3 = 0xb8;
              }
              if ((((local_3c == 9) || (local_3c == 7)) || (local_3c == 8)) || (local_3c == 0xe)) {
                city3 = 0xba;
              }
              if ((local_3c == 0x12) || (local_3c == 0xc)) {
                city3 = 0xba;
              }
              if (local_3c == 0x15) {
                city3 = 0xb9;
              }
              text_set_label_arg(3,*(i32 *)(label_string_ids + city3 * 4));
              if (local_5c != 0) {
                if (local_3c < 0) {
                  if ((improvement < 0x23) || (0x25 < improvement)) {
                    switch(improvement) {
                    case 2:
                      local_40 = 5;
                      break;
                    default:
                      local_40 = 2;
                      break;
                    case 9:
                      local_40 = 4;
                      break;
                    case 10:
                      local_40 = 0x2f;
                      break;
                    case 0xb:
                      local_40 = 0xb;
                      break;
                    case 0xc:
                      local_40 = 0x37;
                      break;
                    case 0x16:
                      local_40 = 0x45;
                    }
                    snd_play_effect(local_40,1,0,0);
                  }
                  else {
                    snd_play_effect(8,1,0,0);
                  }
                }
                else {
                  snd_play_effect(0x30,1,0,0);
                }
              }
              if ((human_civ == civ) && (autoplay_active == 0)) {
                if ((2 < game.multiplayer) && (0x22 < improvement)) {
                  text_set_string_arg(0,(iptr)&cities[city].name);
                  net_send_text_args(0x47,0xff,4,0,local_3c,improvement);
                }
                if ((game.message_options & 2) == 0) {
                  if (local_3c < 0) {
                    local_970 = &improvement_icon_sprites + improvement * 0x3c;
                  }
                  else {
                    local_970 = &wonder_icon_sprites + local_3c * 0x3c;
                  }
                  city_notify_dialog_ex(ADDR(0x62eee8, ((u8 *)&g.d_0062eee8)),city,1,(iptr)local_970);
                }
              }
              else if (local_5c != 0) {
                text_set_string_arg(0,(iptr)&cities[city].name);
                if ((autoplay_active == 0) && (2 < game.multiplayer)) {
                  net_send_text_args(0x47,0xff,4,0,local_3c,improvement);
                }
                dialog_ctor(&local_66c,0x4000);
                local_8 = 1;
                dialog_load_game_text(&local_66c,ADDR(0x62eef0, ((u8 *)&g.d_0062eef0)));
                if (local_3c < 0) {
                  local_974 = &improvement_icon_sprites + improvement * 0x3c;
                }
                else {
                  local_974 = &wonder_icon_sprites + local_3c * 0x3c;
                }
                dialog_add_sprite((DialogOptionList *)&local_66c,(iptr)local_974,0,0)
                ;
                dialog_set_image_zoom((DialogWindowView *)&local_66c,8);
                dlg_show_modal(&local_66c,0);
                local_8 = 0xffffffff;
                /* inlined unwind funclet FUN_004eeef3 */ { dialog_dtor((Dialog *)((iptr)&local_66c)); }
              }
              if ((((local_5c != 0) && (-1 < local_3c)) && (human_civ == civ)) &&
                 ((autoplay_active == 0 && (((*(i8 *)((char *)&game.game_options + 2)) & 1) != 0)))) {
                wonder_show_movie(local_3c);
              }
              if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) {
                _DAT_006a6610 = improvement;
              }
              if (local_14 == 0) {
                cities[city].shield_box = 0;
              }
              if (((cities[city].flags & 0x10) != 0) ||
                 ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0)) {
                city_set_production(city,99);
              }
            }
            if ((0x22 < improvement) && (improvement < 0x26)) {
              local_48 = improvement - 0x23;
              local_48 = spaceship_add_part(civ,local_48);
              if (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) &&
                 ((iVar3 = civ_spaceship_launched(civ), iVar3 == 0 && (local_48 < 0)))) {
                text_set_label_arg(1,improvements[improvement].name);
                city_notify_dialog(ADDR(0x62eef8, ((u8 *)&g.d_0062eef8)),city,(iptr)(&improvement_icon_sprites + improvement * 0x3c));
              }
            }
            if (improvement == 1) {
              for (city2 = 0; (int)city2 < (int)game.num_cities; city2++) {
                if ((cities[city2].id != 0) && ((int)cities[city2].owner == civ)) {
                  city_set_improvement(city2,1,0);
                }
              }
              city_set_improvement(city,1,1);
              civs[civ].capital_x = cities[city].x;
              if (autoplay_active == 0) {
                text_set_string_arg(0,(iptr)&cities[city].name);
                iVar5 = civ_adjective(civ);
                text_set_string_arg(1,iVar5);
                if ((autoplay_active == 0) && (2 < game.multiplayer)) {
                  net_send_text_args(0x48,0xff,2,0,0,0);
                }
                popup_game(ADDR(0x62ef04, ((u8 *)&g.d_0062ef04)));
              }
            }
            if (local_3c == 0x12) {
              civ_research_complete(civ,0);
              civ_research_complete(civ,0);
            }
            if (local_3c == 0xe) {
              civ_leonardo_upgrade(civ);
            }
            if (local_3c == 0x14) {
              civ_apply_eiffel_tower(civ);
            }
            if (local_3c == 0x19) {
              wonder_apollo_reveal_map();
            }
            if (city_turn_window_shown != 0) {
              city_window_draw_production((FrameWindow *)&city_window,1);
              city_window_draw_improvements((FrameWindow *)&city_window,1);
            }
            if (-1 < local_3c) {
              city3 = city;
              for (city2 = 0; (int)city2 < (int)game.num_cities; city2++) {
                if ((((cities[city2].id != 0) && (city2 != city3)) &&
                    (((uint)game.human_players & 1 << (cities[city2].owner & 0x1fU)) == 0)) &&
                   ((int)cities[city2].building == -improvement)) {
                  city_set_production(city2,99);
                }
              }
              city_recalc(city3,0);
            }
          }
        }
        else {
          iVar3 = civ_spaceship_launched(civ);
          if (iVar3 == 0) {
            local_48 = spaceship_choose_part_group(civ,improvement - 0x23);
            if (local_48 < 0) {
              city_set_production(city,99);
            }
            else {
              improvement2 = local_48 + 0x23;
              cities[city].building = -(char)improvement2;
              local_58 = (uint)improvements[improvement2].cost * city_shield_rows;
              improvement = improvement2;
              if (local_58 <= cities[city].shield_box) goto LAB_004eda9a;
            }
          }
          else {
            city_set_production(city,99);
          }
        }
      }
    }
    else {
      text_set_label_arg(1,improvements[improvement].name);
      city_notify_dialog(ADDR(0x62eed0, ((u8 *)&g.d_0062eed0)),city,(iptr)(&improvement_icon_sprites + improvement * 0x3c));
    }
  }
  else {
    unit_type = (iptr)cities[city].building;
    if ((-1 < unit_types[unit_type].obsolete_by) &&
       (iVar3 = civ_has_advance(civ,(int)unit_types[unit_type].obsolete_by), iVar3 != 0)) {
      for (unit_type2 = 0; unit_type2 < 0x3e; unit_type2++) {
        if ((unit_types[unit_type2].prerequisite == unit_types[unit_type].obsolete_by) &&
           (unit_types[unit_type2].role == unit_types[unit_type].role)) {
          if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) {
            text_set_label_arg(1,unit_types[unit_type].name);
            text_set_label_arg(2,unit_types[unit_type2].name);
            city_notify_dialog(ADDR(0x62ee70, ((u8 *)&g.d_0062ee70)),city,(iptr)(&unit_sprites + unit_type2 * 0x3c));
          }
          unit_type = unit_type2;
          iVar5 = unit_type;
          (*(i8 *)((char *)&unit_type + 0)) = (i8)unit_type2;
          cities[city].building = (i8)unit_type;
          unit_type = iVar5;
          break;
        }
      }
    }
    local_58 = (char)unit_types[unit_type].cost * city_shield_rows;
    if (local_58 <= cities[city].shield_box) {
      cities[city].flags = cities[city].flags & 0xfffffeff;
      if (city_turn_window_shown != 0) {
        city_window_draw_production((FrameWindow *)&city_window,1);
      }
      if (((unit_types[unit_type].role == 5) && (cities[city].size == 1)) &&
         (game.difficulty == '\0')) goto LAB_004eef15;
      cities[city].shield_box -= (short)local_58;
      if (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) ||
         (unit_types[unit_type].role != 6)) {
        unit = unit_create(unit_type,civ,(int)cities[city].x,
                                      (int)cities[city].y);
        if (unit < 0) goto LAB_004ee539;
        if ((unit_types[unit_type].role == 6) && (civs[civ].government == 3)) {
          units[unit].flags = units[unit].flags | 0x2000;
        }
        else if ((unit_types[unit_type].domain == '\0') || ((game.rules & 0x10) == 0)) {
          iVar3 = city_has_improvement(city,2);
          if ((((iVar3 != 0) || (iVar3 = civ_has_wonder(civ,7), iVar3 != 0)) &&
              ((char)unit_types[unit_type].role < 6)) &&
             ((unit_types[unit_type].flags & 0x1000) == 0)) {
            units[unit].flags = units[unit].flags | 0x2000;
          }
        }
        else if (unit_types[unit_type].domain == 2) {
          iVar3 = city_has_improvement(city,0x22);
          if (((iVar3 != 0) || (iVar3 = civ_has_wonder(civ,3), iVar3 != 0)) &&
             ((unit_types[unit_type].flags & 0x1000) == 0)) {
            units[unit].flags = units[unit].flags | 0x2000;
          }
        }
        else if (((unit_types[unit_type].domain == 1) &&
                 (iVar3 = city_has_improvement(city,0x20), iVar3 != 0)) &&
                ((unit_types[unit_type].flags & 0x1000) == 0)) {
          units[unit].flags = units[unit].flags | 0x2000;
        }
        if (unit_types[unit_type].role == 4) {
          units[unit].counter = 0xff - ((byte)city & 0x3f);
        }
      }
      if (unit_types[unit_type].role == 5) {
        if ((cities[city].size == 1) && (civs[civ].num_cities == 1)) goto LAB_004eef15;
        if ((cities[city].size == 1) &&
           ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) {
          text_set_string_arg(0,(iptr)&cities[city].name);
          text_set_label_arg(1,unit_types[unit_type].name);
          if ((autoplay_active != 0) || (iVar3 = popup_game(ADDR(0x62ee7c, ((u8 *)&g.d_0062ee7c))), iVar3 == 0)) {
            unit_delete(unit,1);
            goto LAB_004eef15;
          }
        }
        cities[city].size--;
        if (cities[city].size < 1) {
          x2 = (int)cities[city].x;
          y2 = (int)cities[city].y;
          text_set_string_arg(0,(iptr)&cities[city].name);
          text_set_label_arg(1,unit_types[unit_type].name);
          text_set_label_arg(3,*(i32 *)(label_string_ids + 0x2ec));
          city_delete(city,0);
          iVar3 = civ_check_destroyed(civ,0);
          if (((iVar3 == 0) &&
              (unit_create(unit_type,civ,x2,y2),
              (game.message_options & 4) == 0)) && (city_notify_enabled != 0)) {
            popup_game(ADDR(0x62ee88, ((u8 *)&g.d_0062ee88)));
          }
          city_turn_window_shown = 0;
          city_notify_enabled = 0;
          map_redraw_tile_all_views(x2,y2);
          goto LAB_004eef15;
        }
      }
      if (city_turn_window_shown != 0) {
        city_window_draw_supported_units((FrameWindow *)&city_window,1);
        city_window_draw_info_panel((FrameWindow *)&city_window,1);
      }
      if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
        if (unit_types[unit_type].role == 7) {
          unit_pick_caravan_commodity(city,unit);
        }
        if (unit_types[unit_type].role == 6) {
          local_7c = 0xffffffff;
          local_1c = 0x7fff;
          local_68 = 0;
          for (city2 = 0; (int)city2 < (int)game.num_cities; city2++) {
            if (((cities[city2].id != 0) && ((int)cities[city2].owner != civ)) &&
               ((*(byte *)&civs[civ].treaties[cities[city2].owner] & 6) == 0)) {
              unit = unit_find_nearest((int)cities[city2].x,(int)cities[city2].y,civ
                                            ,-1);
              if (unit_nearest_dist == 3 || unit_nearest_dist - 3 < 0) {
                unit_nearest_dist = ~(unit_nearest_dist - 3U) + 1;
              }
              else {
                unit_nearest_dist -= 3;
              }
              if (-1 < unit) {
                if (((cities[city2].flags & 8) != 0) && (unit_nearest_dist < 4)) {
                  unit_nearest_dist = 3;
                }
                if (unit_nearest_dist <= local_1c) {
                  if (local_1c == unit_nearest_dist) {
                    if (local_68 + 1 == 1 || local_68 < 0) {
                      local_964 = 0;
                      local_68++;
                    }
                    else {
                      local_68 += 2;
                      local_964 = _rand();
                      local_964 = local_964 % local_68;
                    }
                    if (local_964 != 0) goto LAB_004ecd0c;
                  }
                  iVar3 = tile_is_ocean((int)units[unit].x,(int)units[unit].y);
                  if (iVar3 == 0) {
                    iVar3 = tile_landmass((int)cities[city2].x,(int)cities[city2].y);
                    iVar4 = tile_landmass((int)units[unit].x,(int)units[unit].y);
                    if (iVar3 == iVar4) {
                      if (local_1c < unit_nearest_dist) {
                        local_68 = 1;
                        local_1c = unit_nearest_dist;
                      }
                      local_7c = city2;
                      unit2 = unit;
                    }
                  }
                }
              }
            }
LAB_004ecd0c: ;
          }
          if ((local_1c < 4) && (iVar3 = _rand(), iVar3 % 10 <= (int)(uint)game.difficulty)) {
            city2 = local_7c;
            unit = unit2;
            unit = unit_create(unit_type,civ,(int)units[unit2].x,
                                          (int)units[unit2].y);
          }
          else {
            unit = unit_create(unit_type,civ,(int)cities[city].x,
                                          (int)cities[city].y);
          }
          if (civs[civ].government == 3) {
            units[unit].flags = units[unit].flags | 0x2000;
          }
        }
        if (('b' < (char)unit_types[unit_type].attack) &&
           (*(char *)&civs[civ].units_active[unit_type] == 1)) {
          for (civ3 = 1; civ3 < 8; civ3++) {
            civs[civ3].last_treaty_turn[civ] = 0xffff;
          }
        }
        city_set_production(city,99);
      }
      else {
        if ((unit_types[unit_type].role == 5) || (5 < (char)unit_types[unit_type].role)) {
          text_set_label_arg(1,unit_types[unit_type].name);
          if (unit_types[unit_type].role == 7) {
            dialog_ctor(&local_378,0x4000);
            local_8 = 0;
            mapviews_ensure_visible((int)cities[city].x,(int)cities[city].y,
                               (int)cities[city].owner);
            do {
              text_set_string_arg(0,(iptr)&cities[city].name);
              dialog_load_game_text(&local_378,ADDR(0x62ee90, ((u8 *)&g.d_0062ee90)));
              for (unit_type2 = 0; unit_type2 < 3; unit_type2++) {
                if (-1 < *(char *)&cities[city].supplies[unit_type2]) {
                  uVar8 = 0;
                  iVar6 = unit_type2;
                  iVar5 = label_string(commodity_names
                                             [*(char *)&cities[city].supplies[unit_type2]]);
                  dialog_add_option((DialogOptionList *)&local_378,iVar5,iVar6,uVar8)
                  ;
                }
              }
              uVar8 = 0;
              iVar7 = 3;
              iVar5 = label_string(*(i32 *)(label_string_ids + 0x300));
              dialog_add_option((DialogOptionList *)&local_378,iVar5,iVar7,uVar8);
              local_78 = dlg_show_modal(&local_378,0);
              if (local_378.field_dc == 0) {
                if (local_78 < 3) {
                  text_set_label_arg(0,commodity_names
                                       [*(char *)&cities[city].supplies[local_78]]);
                }
                else {
                  iVar5 = label_string(*(i32 *)(label_string_ids + 0x300));
                  text_set_string_arg(0,iVar5);
                }
                iVar3 = popup_game(ADDR(0x62eeb0, ((u8 *)&g.d_0062eeb0)));
                if (iVar3 != 0) {
                  local_378.field_dc = 1;
                }
              }
              else if (local_78 < 3) {
                trade_commodity_cities_dialog(civ,(int)*(char *)&cities[city].supplies[local_78]);
              }
              else {
                popup_game(ADDR(0x62eea0, ((u8 *)&g.d_0062eea0)));
              }
            } while (local_378.field_dc != 0);
            if (dlg_help_pressed != 0) {
              city_zoom_requested = 1;
            }
            if (local_78 < 3) {
              if (*(char *)&cities[city].supplies[local_78] < 1) {
                units[unit].counter = ~cities[city].supplies[local_78] + 1;
              }
              else {
                units[unit].counter = cities[city].supplies[local_78];
              }
              if (*(char *)&cities[city].supplies[local_78] < 1) {
                local_968 = ~cities[city].supplies[local_78] + 1;
              }
              else {
                local_968 = *(char *)&cities[city].supplies[local_78];
              }
              *(char *)&cities[city].supplies[local_78] = -local_968;
            }
            else {
              units[unit].counter = 0xff;
            }
            local_8 = 0xffffffff;
            /* inlined unwind funclet FUN_004eeeff */ { dialog_dtor((Dialog *)((iptr)&local_378)); }
          }
          else {
            if (unit_types[unit_type].role == 7) {
              iVar3 = _rand();
              bVar1 = (byte)(iVar3 >> 0x1f);
              units[unit].counter = (((byte)iVar3 ^ bVar1) - bVar1 & 0xf ^ bVar1) - bVar1;
            }
            if ((game.message_options & 4) == 0) {
              city3 = 0xbb;
              if (unit_types[unit_type].role == 6) {
                city3 = 0xb6;
              }
              if (unit_types[unit_type].role == 7) {
                city3 = 0xbc;
              }
              text_set_label_arg(3,*(i32 *)(label_string_ids + city3 * 4));
              city_notify_dialog(ADDR(0x62eebc, ((u8 *)&g.d_0062eebc)),city,(iptr)(&unit_sprites + unit_type * 0x3c));
            }
          }
        }
        cities[city].shield_box = 0;
        if ((cities[city].flags & 0x10) != 0) {
          city_set_production(city,99);
        }
        if (city_turn_window_shown != 0) {
          city_window_draw_production((FrameWindow *)&city_window,1);
        }
      }
    }
  }
LAB_004ee539:
  if (((((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) &&
       ((cities[city].flags & 0x10) != 0)) &&
      ((cities[city].shield_box == 0 || ((cities[city].building < '\0' && (improvement < 0))))))
     && (city_set_production(city,99), cities[city].building == 'c')) {
    cities[city].flags = cities[city].flags & 0xfcffffef;
  }
  if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
    if (((cities[city].flags & 0x20) != 0) ||
       (iVar3 = tile_unit_owner((int)cities[city].x,(int)cities[city].y), iVar3 < 0)) {
      city_set_production(city,99);
    }
    local_34 = 0;
    if (cities[city].building < '\0') {
      if (cities[city].building < 1) {
        improvement = ~(int)cities[city].building + 1;
      }
      else {
        improvement = (iptr)cities[city].building;
      }
    }
    else {
      improvement = 0;
    }
    if (improvement == 0) {
      bVar1 = unit_types[cities[city].building].cost;
    }
    else {
      bVar1 = improvements[improvement].cost;
    }
    local_978 = (uint)bVar1;
    local_58 = local_978 * city_shield_rows;
    local_60 = tile_land_landmass((int)cities[city].x,(int)cities[city].y);
    if (local_60 < 0) {
      local_38 = 0;
    }
    else {
      local_38 = (uint)civs[civ].continent_policy[local_60];
    }
    if (((((local_38 == 0) || (local_38 == 1)) || (local_38 == 4)) &&
        ((local_2c != 0 && (-1 < cities[city].building)))) &&
       ((int)(char)unit_types[cities[city].building].role == local_38)) {
      local_34 = civs[civ].gold >> 6;
    }
    if (0x26 < improvement) {
      local_18 = (improvement - 0x27) / 7;
      if ((*(char *)&civs[civ].wonders_by_group[local_18] == '\0') ||
         (civs[civ].wonders_by_group[local_18] < (byte)(&human_wonders_by_group_min)[local_18])) {
        local_34 = civs[civ].gold >> 6;
      }
      else if ((byte)(&human_wonders_by_group_max)[local_18] + 1 <
               (uint)civs[civ].wonders_by_group[local_18]) {
        local_34 = civs[civ].gold >> 8;
      }
      else {
        local_34 = civs[civ].gold >> 7;
      }
      if (0x9c3 < civs[civ].gold) {
        local_34 = local_34 << 1;
      }
    }
    if ((0x22 < improvement) && (improvement < 0x27)) {
      for (civ3 = 1; civ3 < 8; civ3++) {
        if (((1 << ((byte)civ3 & 0x1f) & (uint)game.human_players) != 0) &&
           (iVar3 = civ_spaceship_exists(civ3), iVar3 != 0)) {
          local_34 = civs[civ].gold >> 7;
          break;
        }
      }
      iVar3 = ai_spaceship_race_behind(civ);
      if (iVar3 != 0) {
        local_34 = local_34 << 1;
      }
    }
    if ((((cities[city].flags & 1) != 0) && (improvement != 0)) && (cities[city].shield_box != 0)
       ) {
      local_34 = civs[civ].gold >> 3;
    }
    iVar3 = tile_unit_owner((int)cities[city].x,(int)cities[city].y);
    if (((iVar3 < 0) || ((cities[city].flags & 0x20) != 0)) &&
       ((-1 < cities[city].building && (cities[city].shield_box != 0)))) {
      local_34 = civs[civ].gold >> 3;
    }
    if ((improvement == 1) && (cities[city].shield_box != 0)) {
      local_34 = civs[civ].gold >> 3;
    }
    if (((cities[city].building == '-') && (civs[civ].units_active[0x2d] == '\0')) &&
       (cities[city].shield_box != 0)) {
      local_34 = civs[civ].gold >> 4;
    }
    if (2000 < civs[civ].gold) {
      local_34 += (civs[civ].gold >> 9);
    }
    local_34 = int_clamp(0,local_34,local_58 - cities[city].shield_box);
    cities[city].shield_box += (short)local_34;
    local_44 = ((int)((uint)game.difficulty * local_34) / 10) /
               (int)(8 - (uint)game.power_rank[game.field_138]);
    if (civs[game.field_139].gold < civs[civ].gold) {
      if (999 < civs[civ].gold) {
        local_44 = local_44 / 2;
      }
      if (1999 < civs[civ].gold) {
        local_44 = 0;
      }
    }
    civs[civ].gold -= (local_34 - local_44);
    if (cities[city].building < -0x26) {
      if (cities[city].building < 1) {
        improvement2 = ~(int)cities[city].building + 1;
      }
      else {
        improvement2 = (iptr)cities[city].building;
      }
      local_58 = (uint)improvements[improvement2].cost * city_shield_rows;
      if (((local_58 <= (cities[city].shield_box + city_total_shields) - city_shield_support) &&
          (game.wonder_city[improvement2 - 0x27] == -1)) && (autoplay_active == 0)) {
        iVar5 = civ_name_plural(civ);
        text_set_string_arg(1,iVar5);
        text_set_label_arg(2,improvements[improvement2].name);
        if ((autoplay_active == 0) && (2 < game.multiplayer)) {
          net_send_text_args(0x4a,0xff,3,0,improvement2,0);
        }
        dialog_ctor(&local_960,0x4000);
        local_8 = 2;
        dialog_load_game_text(&local_960,ADDR(0x62ef10, ((u8 *)&g.d_0062ef10)));
        dialog_add_sprite
                  ((DialogOptionList *)&local_960,(iptr)(&improvement_icon_sprites + improvement2 * 0x3c),0,0);
        dialog_set_image_zoom((DialogWindowView *)&local_960,8);
        dlg_show_modal(&local_960,0);
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_004eeee7 */ { dialog_dtor((Dialog *)((iptr)&local_960)); }
      }
    }
  }
  cities[city].flags = cities[city].flags & 0xffffffdf;
LAB_004eef15:
  return;
}
#undef autoplay_active
#undef city_notify_enabled
#undef city_shield_rows
#undef city_shield_support
#undef city_total_shields
#undef city_turn_window_shown
#undef city_zoom_requested
#undef dlg_help_pressed
#undef human_civ
#undef _DAT_006a6610
#undef local_978
#undef local_974
#undef local_970
#undef local_96c
#undef local_968
#undef local_964
#undef local_960
#undef local_66c
#undef local_378
#undef civ
#undef unit
#undef local_7c
#undef local_78
#undef civ3
#undef improvement2
#undef city2
#undef local_68
#undef unit_type
#undef local_60
#undef local_5c
#undef local_58
#undef y2
#undef x2
#undef city3
#undef local_48
#undef local_44
#undef local_40
#undef local_3c
#undef local_38
#undef local_34
#undef civ2
#undef local_2c
#undef unit2
#undef improvement
#undef unit_type2
#undef local_1c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004eef23 auto */
#define city_shield_rows (*(int *)((u8 *)&g.d_006a657c))
#define city_shield_support (*(int *)((u8 *)&g.d_006a6568))
#define city_support_unit_count (*(i32 *)((u8 *)&g.d_006a660c))
#define city_total_shields (*(int *)((u8 *)&g.d_006a65cc))
#define city_turn_window_shown (*(int *)((u8 *)&g.d_0062ee00))
#define unit (*(iptr *)(frame_ + FRAME_OFF(0)))
#define city2 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(20)))
#define unit2 (*(iptr *)(frame_ + FRAME_OFF(32)))
void __cdecl city_disband_unsupported_units(uptr city)

{
  byte civ2;
  byte bVar2;
  bool bVar3;
  bool bVar4;
  iptr civ;
  int iVar7;
  i32 uVar5;
  iptr city3;
  iptr iVar5;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ2 = cities[city].owner;
  civ = (iptr)(char)civ2;
  bVar2 = civs[civ].government;
LAB_004eef5f:
  city_support_unit_count = 0;
  city_shield_support = 0;
  unit = 0;
  do {
    iVar5 = unit;
    if (game.num_units <= unit) {
      return;
    }
    if (((((units[unit].id != 0) && (units[unit].owner == civ)) &&
         ((byte)units[unit].home_city == city)) &&
        ((char)unit_types[units[unit].type].role < 6)) &&
       ((city_count_unit_support(city,unit,(uint)bVar2), city_total_shields < city_shield_support ||
        ((((cities[city].flags & 1) != 0 && ((game.turn + unit & 7U) == 0)) &&
         (((1 << (civ2 & 0x1f) & (uint)game.human_players) == 0 && (4 < bVar2)))))))) {
      bVar3 = city_shield_support <= city_total_shields;
      local_14 = -1;
      unit2 = -1;
      for (unit = 0; unit < game.num_units; unit++) {
        if (((units[unit].id != 0) && ((byte)units[unit].home_city == city)) &&
           ((char)unit_types[units[unit].type].role < 6)) {
          if (bVar3) {
            if ((4 < (char)unit_types[units[unit].type].role) ||
               (iVar7 = tile_city_owner((int)units[unit].x,(int)units[unit].y), -1 < iVar7))
            goto LAB_004ef0c3;
            uVar5 = tile_improvements((int)units[unit].x,(int)units[unit].y);
            if (((byte)uVar5 & 0x42) == 0x40) {
              bVar4 = false;
              for (city2 = 0; city2 < game.num_cities; city2++) {
                if (((cities[city2].id != 0) && (cities[city2].owner == cities[city].owner)
                    ) && (iVar7 = map_distance((int)units[unit].x,(int)units[unit].y,
                                                     (int)cities[city2].x,(int)cities[city2].y
                                                    ), iVar7 < 4)) {
                  bVar4 = true;
                  break;
                }
              }
              if (bVar4) goto LAB_004ef0c3;
            }
          }
          iVar7 = map_distance_diag((int)units[unit].x,(int)units[unit].y,
                                     (int)cities[city].x,(int)cities[city].y);
          if (local_14 < iVar7) {
            unit2 = unit;
            local_14 = iVar7;
          }
        }
LAB_004ef0c3: ;
      }
      if (city_total_shields < city_shield_support) {
        if (-1 < local_14) break;
      }
      else if (((game.game_flags & 1) == 0) ||
              (civs[game.field_138].num_advances <= civs[civ].num_advances)) {
        if ((0 < local_14) && (unit_types[units[unit2].type].domain == '\0')) {
          city3 = city_at((int)units[unit2].x,(int)units[unit2].y);
          if (-1 < city3) {
            cities[city3].shield_box =
                 (short)(((char)unit_types[units[unit2].type].cost * city_shield_rows) / 2) +
                 cities[city3].shield_box;
          }
          unit_delete(unit2,1);
          cities[city].flags = cities[city].flags & 0xffefdffe;
          goto LAB_004eef5f;
        }
      }
      else {
        civs[civ].government_score[6] = -999;
        civs[civ].government_score[5] = -999;
      }
    }
    unit = iVar5 + 1;
  } while( true );
  if ((1 << (civ2 & 0x1f) & (uint)game.human_players) != 0) {
    text_set_label_arg(1,unit_types[units[unit2].type].name);
    city_notify_dialog(ADDR(0x62ef20, ((u8 *)&g.d_0062ef20)),city,(iptr)(&unit_sprites + (uint)units[unit2].type * 0x3c));
  }
  unit_destroy_redraw(unit2,1);
  if (city_turn_window_shown != 0) {
    city_window_draw_supported_units((FrameWindow *)&city_window,1);
    city_window_draw_info_panel((FrameWindow *)&city_window,1);
  }
  goto LAB_004eef5f;
}
#undef city_shield_rows
#undef city_shield_support
#undef city_support_unit_count
#undef city_total_shields
#undef city_turn_window_shown
#undef unit
#undef city2
#undef local_14
#undef unit2

/* 004ef578 auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define city_happy_count (*(int *)((u8 *)&g.d_006a6550))
#define city_notify_enabled (*(int *)((u8 *)&g.d_006a65ac))
#define city_shield_support (*(int *)((u8 *)&g.d_006a6568))
#define city_tax_total (*(int *)((u8 *)&g.d_006a6554))
#define city_total_shields (*(int *)((u8 *)&g.d_006a65cc))
#define city_unhappy_count (*(int *)((u8 *)&g.d_006a65a8))
#define city_yield_totals (*(int *)((u8 *)&g.d_006a65c8))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
#define settler_food_cost (*(int *)((u8 *)&g.d_006a6608))
void __cdecl city_process_disorder(iptr city)

{
  byte civ2;
  iptr civ;
  int iVar3;
  iptr iVar4;
  
  civ2 = cities[city].owner;
  civ = (iptr)(char)civ2;
  if (civ != 0) {
    iVar3 = city_happy_count - city_unhappy_count;
    if (iVar3 < 0) {
      if (((human_civ == civ) && (autoplay_active == 0)) && ((game.message_options & 0x10) == 0))
      {
        snd_play_effect(0xe,1,0,0);
        popup_city_picture_zoom(ADDR(0x62ef28, ((u8 *)&g.d_0062ef28)),city,0x48,0,0);
      }
      if ((cities[city].flags & 1) == 0) {
        cities[city].flags = cities[city].flags | 0x4001;
        if ((1 << (civ2 & 0x1f) & (uint)game.human_players) == 0) {
          city_set_production(city,99);
        }
        map_redraw_area_all_views((int)cities[city].x,(int)cities[city].y,0,human_civ,1);
      }
      else {
        if ((1 << (civ2 & 0x1f) & (uint)game.human_players) == 0) {
          city_set_production(city,99);
        }
        if ((cities[city].flags & 0x2000) != 0) {
          cities[city].flags = cities[city].flags | 0x100000;
        }
        cities[city].flags = cities[city].flags | 0x2000;
        if ((((1 << (civ2 & 0x1f) & (uint)game.human_players) != 0) &&
            (civs[civ].government == 6)) &&
           (((game.game_flags & 0x80) == 0 || ((scenario_flags & 0x10) == 0)))) {
          city_notify_dialog(ADDR(0x62ef34, ((u8 *)&g.d_0062ef34)),city,ADDR(0x6469e0, ((u8 *)&g.d_006469e0)));
          civs[civ].flags = civs[civ].flags & 0xfffe;
          civ_change_government(civ,0);
          civs[civ].flags = civs[civ].flags | 1;
        }
      }
    }
    else {
      if (((city_happy_count == city_unhappy_count) && (0 < city_total_shields - city_shield_support)) &&
         (-1 < city_food_surplus)) {
        cities[city].flags = cities[city].flags | 0x4000;
      }
      else {
        cities[city].flags = cities[city].flags & 0xffffbfff;
      }
      if ((-1 < iVar3) && ((cities[city].flags & 1) != 0)) {
        cities[city].flags = cities[city].flags & 0xffefdffe;
        if ((1 << (civ2 & 0x1f) & (uint)game.human_players) == 0) {
          city_set_production(city,99);
        }
        else if ((game.message_options & 0x20) == 0) {
          city_notify_dialog_ex(ADDR(0x62ef3c, ((u8 *)&g.d_0062ef3c)),city,0,0);
        }
        map_redraw_area_all_views((int)cities[city].x,(int)cities[city].y,0,human_civ,1);
      }
      if (civs[civ].government != '\0') {
        civs[civ].gold += city_tax_total;
      }
    }
    if ((((city_unhappy_count == 0) && (2 < cities[city].size)) &&
        (cities[city].size + 1 >> 1 <= city_happy_count)) && (civs[civ].government != '\0')) {
      if ((cities[city].flags & 2) == 0) {
        if ((1 << (civ2 & 0x1f) & (uint)game.human_players) != 0) {
          iVar4 = civ_leader_title(civ);
          text_set_string_arg_b(1,iVar4);
          if ((game.message_options & 0x40) == 0) {
            if (city_notify_enabled != 0) {
              music_play_track(3,0);
            }
            popup_city_picture_zoom(ADDR(0x62ef48, ((u8 *)&g.d_0062ef48)),city,0x4a,0,0);
          }
        }
        cities[city].flags = cities[city].flags | 2;
      }
      else if (((4 < civs[civ].government) &&
               ((int)((int)cities[city].size * (uint)cosmic.food_per_citizen +
                     city_settlers_supported * settler_food_cost) < city_yield_totals)) &&
              (iVar3 = city_needed_size_improvement(city), iVar3 == 0)) {
        cities[city].size++;
      }
    }
    else if ((cities[city].flags & 2) != 0) {
      if ((((1 << (civ2 & 0x1f) & (uint)game.human_players) != 0) &&
          (civs[civ].government != '\0')) && ((cities[city].flags & 1) == 0)) {
        iVar4 = civ_leader_title(civ);
        text_set_string_arg_b(1,iVar4);
        if ((game.message_options & 0x40) == 0) {
          city_notify_dialog_ex(ADDR(0x62ef54, ((u8 *)&g.d_0062ef54)),city,0,0);
        }
      }
      cities[city].flags = cities[city].flags & 0xfffffffd;
    }
  }
  return;
}
#undef autoplay_active
#undef city_happy_count
#undef city_notify_enabled
#undef city_shield_support
#undef city_tax_total
#undef city_total_shields
#undef city_unhappy_count
#undef city_yield_totals
#undef human_civ
#undef scenario_flags
#undef settler_food_cost

/* 004efbc6 auto */
#define city_science_total (*(int *)((u8 *)&g.d_006a6578))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl city_add_science(iptr city)

{
  byte civ2;
  uptr civ;
  int iVar3;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ2 = cities[city].owner;
  civ = (uptr)(char)civ2;
  if ((((-1 < civs[civ].researching) && ((1 << (civ2 & 0x1f) & (uint)game.human_players) != 0))
      && (game.difficulty == '\0')) &&
     ((civs[civ].researching != 0x59 && (game.first_discoverer[civs[civ].researching] != '\0')))
     ) {
    city_science_total = city_science_total << 1;
  }
  if (((1 << (civ2 & 0x1f) & (uint)game.human_players) == 0) && (1 < game.difficulty)) {
    iVar3 = ai_spaceship_race_behind(civ);
    if (iVar3 != 0) {
      for (improvement = 0x23; improvement < 0x26; improvement++) {
        iVar3 = civ_has_advance(civ,(int)improvements[improvement].preq);
        if (iVar3 == 0) {
          city_science_total = city_science_total << 1;
          break;
        }
      }
    }
  }
  if (civs[civ].government != '\0') {
    civ_add_research_points(civ,city_science_total);
  }
  return;
}
#undef city_science_total
#undef improvement

/* 004efd44: written by hand in src/game/retvals.c */

/* 004f0221 auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define city_shield_rows (*(int *)((u8 *)&g.d_006a657c))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl city_pay_improvement_upkeep(iptr city)

{
  iptr civ;
  int iVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ = (iptr)cities[city].owner;
  if (civs[civ].government != '\0') {
    for (improvement = 1; improvement < 0x27; improvement++) {
      iVar2 = city_has_improvement(city,improvement);
      if (iVar2 != 0) {
        iVar2 = civ_improvement_upkeep(civ,improvement);
        civs[civ].gold -= iVar2;
        if (civs[civ].gold < 0) {
          civs[civ].gold = 0;
          city_set_improvement(city,improvement,0);
          if (autoplay_active == 0) {
            text_set_label_arg(1,improvements[improvement].name);
            text_set_number_arg(0,(uint)improvements[improvement].cost * city_shield_rows);
            city_notify_dialog(ADDR(0x62ef7c, ((u8 *)&g.d_0062ef7c)),city,(iptr)(&improvement_icon_sprites + improvement * 0x3c));
          }
          civs[civ].gold += (uint)improvements[improvement].cost * city_shield_rows;
        }
      }
    }
  }
  return;
}
#undef autoplay_active
#undef city_shield_rows
#undef improvement

/* 004f080d auto */
#define city_tile_job_found (*(int *)((u8 *)&g.d_0062ee0c))
#define city_tile_job_priority (*(int *)((u8 *)&g.d_006a65d4))
#define city_tile_job_x (*(i32 *)((u8 *)&g.d_006a65e0))
#define city_tile_job_y (*(i32 *)((u8 *)&g.d_006a65e8))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl city_add_terraform_goals(iptr city)

{
  byte civ2;
  bool bVar2;
  int civ;
  iptr x;
  int y;
  int iVar6;
  uint uVar7;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  bVar2 = false;
  civ2 = cities[city].owner;
  civ = (int)(char)civ2;
  for (local_8 = 0; local_8 < 0x14; local_8++) {
    x = map_wrap_x((int)(char)(&city_tile_dx_table)[local_8] + (int)cities[city].x);
    y = (int)cities[city].y + (int)(char)(&city_tile_dy_table)[local_8];
    iVar6 = map_in_bounds(x,y);
    if ((iVar6 != 0) && (uVar7 = tile_improvements(x,y), (uVar7 & 0x80) != 0)) {
      civ_add_ai_goal(civ,x,y,0x15,6);
      cities[city].flags = cities[city].flags | 0x80000;
      bVar2 = true;
    }
  }
  if (!bVar2) {
    y = civ_has_advance(civ,0x43);
    if ((y != 0) &&
       (((1 << (civ2 & 0x1f) & (uint)game.human_players) == 0 || (city_tile_job_found == 0)))) {
      if (city_tile_job_priority < 4) {
        city_tile_job_priority = 3;
      }
      ai_find_road_link_tile(city);
      if (city_tile_job_found == 0) {
        return;
      }
    }
    city_tile_job_priority += 2;
    if (city_tile_job_found == 0) {
      city_tile_job_priority = 2;
      ai_find_road_link_tile(city);
    }
    if (city_tile_job_found == 0) {
      cities[city].flags = cities[city].flags & 0xfff7ffff;
    }
    else {
      if (2 < city_tile_job_priority) {
        if (4 < cities[city].size) {
          city_tile_job_priority++;
        }
        y = city_has_improvement(city,1);
        if (y != 0) {
          city_tile_job_priority++;
        }
      }
      if (cities[city].size < 4) {
        city_tile_job_priority--;
      }
      civ_add_ai_goal(civ,city_tile_job_x,city_tile_job_y,0x15,city_tile_job_priority);
      cities[city].flags = cities[city].flags | 0x80000;
    }
  }
  return;
}
#undef city_tile_job_found
#undef city_tile_job_priority
#undef city_tile_job_x
#undef city_tile_job_y
#undef local_8

/* 004f0a9c auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define city_aggressive_units (*(int *)((u8 *)&g.d_006a65e4))
#define city_calc_cached_id (*(i32 *)((u8 *)&g.d_0062ee08))
#define city_happy_count (*(int *)((u8 *)&g.d_006a6550))
#define city_notify_enabled (*(i32 *)((u8 *)&g.d_006a65ac))
#define city_shield_support (*(int *)((u8 *)&g.d_006a6568))
#define city_support_unit_count (*(int *)((u8 *)&g.d_006a660c))
#define city_tile_job_found (*(i32 *)((u8 *)&g.d_0062ee0c))
#define city_tile_job_priority (*(i32 *)((u8 *)&g.d_006a65d4))
#define city_total_shields (*(int *)((u8 *)&g.d_006a65cc))
#define city_turn_processing (*(i32 *)((u8 *)&g.d_0062edf8))
#define city_turn_window_dirty (*(int *)((u8 *)&g.d_0062ee04))
#define city_turn_window_shown (*(uint *)((u8 *)&g.d_0062ee00))
#define city_turn_worker_realloc (*(i32 *)((u8 *)&g.d_0062edfc))
#define city_unhappy_count (*(int *)((u8 *)&g.d_006a65a8))
#define city_window_refresh_locked (*(i32 *)((u8 *)&g.d_006aa760))
#define city_workers_overflow (*(int *)((u8 *)&g.d_006a65dc))
#define city_yield_totals (*(int *)((u8 *)&g.d_006a65c8))
#define city_zoom_requested (*(int *)((u8 *)&g.d_006a65a0))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define settler_food_cost (*(int *)((u8 *)&g.d_006a6608))
#define local_24 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_1c (*(uint *)(frame_ + FRAME_OFF(12)))
#define local_c (*(short *)(frame_ + FRAME_OFF(28)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(32)))
int __cdecl city_process_turn(uptr city)

{
  byte civ2;
  char cVar2;
  short sVar3;
  iptr civ;
  uptr uVar4;
  int iVar5;
  i32 uVar6;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  city_window_refresh_locked = 1;
  civ2 = cities[city].owner;
  civ = (iptr)(char)civ2;
  if (((cities[city].turns_captured - 1 ^ (int)game.turn & 0x3fU) & 0x3f) == 0) {
    cities[city].founder = civ2;
  }
  if ((human_civ == civ) && ((1 << (civ2 & 0x1f) & (uint)game.human_players) != 0)) {
    city_notify_enabled = 1;
  }
  else {
    city_notify_enabled = 0;
  }
  if (autoplay_active != 0) {
    city_notify_enabled = 0;
  }
  city_zoom_requested = 0;
  cities[city].flags = cities[city].flags & 0xffbfffbb;
  uVar4 = citywnd_get_city((C_004083b0_4 *)&city_window);
  city_turn_window_shown = (uint)(uVar4 == city);
  city_turn_window_dirty = 0;
  sVar3 = cities[city].food_box;
  iVar5 = city_process_food(city);
  if (iVar5 == 0) {
    city_recalc(city,1);
    if ((city_turn_window_shown != 0) && (city_turn_window_dirty != 0)) {
      city_window_refresh((FrameWindow *)&city_window);
    }
    if ((city_workers_overflow != 0) && (autoplay_active == 0)) {
      city_notify_dialog_ex(ADDR(0x62ef84, ((u8 *)&g.d_0062ef84)),city,0,0);
    }
    city_food_surplus = (city_yield_totals - (int)cities[city].size * (uint)cosmic.food_per_citizen) -
                   city_settlers_supported * settler_food_cost;
    cities[city].food_box += (short)city_food_surplus;
    if ((((0 < sVar3) && (cities[city].food_box < sVar3)) &&
        ((int)cities[city].food_box + city_food_surplus * 3 < 0)) &&
       (((game.message_options & 0x80) == 0 && (autoplay_active == 0)))) {
      city_notify_dialog_ex(ADDR(0x62ef90, ((u8 *)&g.d_0062ef90)),city,0,0);
    }
    city_process_production(city);
    city_disband_unsupported_units(city);
    city_turn_worker_realloc = 1;
    city_turn_processing = 1;
    city_tile_job_found = 0;
    city_tile_job_priority = 0;
    city_recalc(city,1);
    city_turn_worker_realloc = 0;
    if (city_total_shields < city_shield_support) {
      civs[civ].government_score[0] =
           civs[civ].government_score[0] + ((short)city_shield_support - (short)city_total_shields) * 5;
    }
    uVar6 = int_clamp(city_support_unit_count - (uint)cosmic.monarchy_free_support,0,
                               (int)cities[city].size);
    civs[civ].government_score[0] = (short)uVar6 + civs[civ].government_score[0];
    for (local_24 = 1; local_24 < 7; local_24++) {
      local_1c = 0;
      switch(local_24) {
      case 1:
        local_1c = (uint)cities[city].size;
        break;
      case 2:
        local_1c = (uint)cosmic.monarchy_free_support;
        break;
      case 3:
        local_1c = (uint)cosmic.communism_free_support;
        break;
      case 4:
        local_1c = (uint)cosmic.fundamentalism_free_support;
      }
      if ((int)local_1c < city_support_unit_count) {
        civs[civ].government_score[local_24] =
             civs[civ].government_score[local_24] -
             ((short)city_support_unit_count - (short)local_1c);
      }
    }
    iVar5 = civ_has_wonder(civ,0x15);
    if ((iVar5 == 0) && (iVar5 = city_has_improvement(city,0x21), iVar5 == 0)) {
      local_8 = 0;
    }
    else {
      local_8 = 1;
    }
    cVar2 = leaders[civs[civ].tribe].civilize;
    local_c = -(short)cVar2 + 7;
    iVar5 = city_has_improvement(city,5);
    if (iVar5 != 0) {
      local_c = -(short)cVar2 + 5;
    }
    iVar5 = city_has_improvement(city,10);
    if (iVar5 != 0) {
      local_c--;
    }
    iVar5 = city_has_improvement(city,4);
    if ((iVar5 != 0) &&
       ((iVar5 = city_has_improvement(city,0xb), iVar5 != 0 ||
        (iVar5 = civ_has_wonder(civ,10), iVar5 != 0)))) {
      local_c--;
    }
    uVar4 = wonder_get_city(0xd);
    if (uVar4 != city) {
      iVar5 = leaders[civs[civ].tribe].attack + city_aggressive_units;
      sVar3 = civs[civ].government_score[6];
      uVar6 = int_clamp((2 - local_8) * (iVar5 + 1),0,99);
      civs[civ].government_score[6] = sVar3 - (short)uVar6 * local_c;
      sVar3 = civs[civ].government_score[5];
      uVar6 = int_clamp(iVar5 * (1 - local_8),0,99);
      civs[civ].government_score[5] = sVar3 - (short)uVar6 * local_c;
    }
    city_process_disorder(city);
    city_add_science(city);
    if ((1 << (civ2 & 0x1f) & (uint)game.human_players) != 0) {
      city_process_pollution(city);
      city_pay_improvement_upkeep(city);
    }
    city_add_terraform_goals(city);
    iVar5 = city_total_shields * 2 - city_shield_support;
    if (civs[civ].field_3d2 <= iVar5) {
      civs[civ].field_3d2 = (i16)iVar5;
    }
    city_window_refresh_locked = 0;
    city_calc_cached_id = 0xffffffff;
    if (city_turn_window_shown != 0) {
      city_save_build_state(city);
      city_window_refresh((FrameWindow *)&city_window);
    }
    if (city_zoom_requested != 0) {
      city_window_open((C_004083b0_12c *)&city_window,city);
    }
    city_turn_processing = 0;
    iVar5 = city_happy_count - city_unhappy_count;
  }
  else {
    iVar5 = -999;
  }
  return iVar5;
}
#undef autoplay_active
#undef city_aggressive_units
#undef city_calc_cached_id
#undef city_happy_count
#undef city_notify_enabled
#undef city_shield_support
#undef city_support_unit_count
#undef city_tile_job_found
#undef city_tile_job_priority
#undef city_total_shields
#undef city_turn_processing
#undef city_turn_window_dirty
#undef city_turn_window_shown
#undef city_turn_worker_realloc
#undef city_unhappy_count
#undef city_window_refresh_locked
#undef city_workers_overflow
#undef city_yield_totals
#undef city_zoom_requested
#undef human_civ
#undef settler_food_cost
#undef local_24
#undef local_1c
#undef local_c
#undef local_8

/* 004f1220 auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define net_tile_sync_enabled (*(i8 *)((u8 *)&g.d_006ad699))
#define y2 (*(uint *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define city (*(iptr *)(frame_ + FRAME_OFF(8)))
#define x2 (*(uint *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
void __cdecl wonder_apollo_reveal_map(void)

{
  iptr iVar1;
  i32 uVar1;
  i32 uVar2;
  iptr iVar2;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((game.multiplayer < 3) || (net_host_flag != '\0')) {
    y2 = 0;
    x2 = 0;
    net_batch_begin();
    for (local_8 = 0; local_8 < map.area; local_8++) {
      tile_set_visible(x2,y2,0xff,1,1);
      for (local_14 = 1; local_14 < 8; local_14++) {
        uVar2 = 1;
        uVar1 = 0;
        iVar2 = local_14;
        iVar1 = tile_at(x2,y2);
        known_set(x2,y2,CONCAT31((int3)((uint)iVar1 >> 8),*(i8 *)(iVar1 + 1)),
                  iVar2,uVar1,uVar2);
      }
      x2 += 2;
      if ((int)map.width <= (int)x2) {
        y2++;
        x2 = y2 & 1;
      }
    }
    for (city = 0; city < game.num_cities; city++) {
      if (cities[city].id != 0) {
        cities[city].known_to = 0xff;
        for (local_14 = 0; local_14 < 8; local_14++) {
          *(i8 *)&cities[city].revealed_size[local_14] = cities[city].size;
        }
        tile_set_visible((int)cities[city].x,(int)cities[city].y,0xff,1,1);
      }
    }
    net_batch_flush();
    if (2 < game.multiplayer) {
      net_tile_sync_enabled = 1;
      net_send_state_diff(0xff,2,0,0,0);
      net_send_message(0x74,0xff,0,0,0,0,0,0,0,0);
      if (autoplay_active == 0) {
        net_send_text_args(0x49,0xff,0,0,0,0);
      }
    }
    map_redraw_all_views(human_civ,1);
    if (autoplay_active == 0) {
      popup_game(ADDR(0x62efa0, ((u8 *)&g.d_0062efa0)));
    }
  }
  else {
    net_send_message(0x58,0,0,0,0,0,0,0,0,0);
  }
  return;
}
#undef autoplay_active
#undef human_civ
#undef net_host_flag
#undef net_tile_sync_enabled
#undef y2
#undef local_14
#undef city
#undef x2
#undef local_8

/* 004f3d30 auto */
uint __cdecl city_tile_status_flags(iptr param_1,iptr param_2)

{
  return (uint)(byte)(&city_tile_flags)[param_2];
}

/* 004f3d60 auto */
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
C_004083b0_430 * __thiscall city_picture_popup_ctor(C_004083b0_430 *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  picwnd_ctor(this);
  local_8 = 0;
  dialog_ctor((Dialog *)(this[1].pad_48 + 0x2c),0x4000);
  this->vtable = (u32)&PTR_FUN_0061d6cc;
  return this;
}
#undef local_10
#undef puStack_c
#undef local_8

/* 004f3e20 auto */
void * __thiscall city_picture_popup_scalar_dtor(void *this,uint param_1)

{
  city_picture_popup_dtor(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 004f3e70: written by hand in src/game/unwind.c */

/* 004f3f30 auto */
void __cdecl city_notify_dialog(iptr param_1,iptr city,iptr param_3)

{
  city_notify_dialog_ex(param_1,city,0,param_3);
  return;
}

/* 00500e00 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E41
    _$E46
    _$E51
    _$E56
     6 names - too many to list
   
   Library: Visual Studio 1998 Debug */

void __cdecl city_window_font_global_init(void)

{
  city_window_font_static_init();
  city_window_font_reg_atexit();
  return;
}

/* 00500e1a auto */
void __cdecl city_window_font_static_init(void)

{
  font_init((GameFont *)&city_window_font,0,0x10);
  return;
}

/* 00500e38 auto */
void __cdecl city_window_font_reg_atexit(void)

{
  _atexit(city_window_font_atexit_dtor);
  return;
}

/* 00500e55 auto */
void __cdecl city_window_font_atexit_dtor(void)

{
  font_destroy((GameFont *)&city_window_font);
  return;
}

/* 00500e6f auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E41
    _$E46
    _$E51
    _$E56
     6 names - too many to list
   
   Library: Visual Studio 1998 Debug */

void __cdecl city_window_small_font_global_init(void)

{
  city_window_small_font_static_init();
  city_window_small_font_reg_atexit();
  return;
}

/* 00500e89 auto */
void __cdecl city_window_small_font_static_init(void)

{
  font_init((GameFont *)&city_window_small_font,0,10);
  return;
}

/* 00500ea7 auto */
void __cdecl city_window_small_font_reg_atexit(void)

{
  _atexit(city_window_small_font_atexit_dtor);
  return;
}

/* 00500ec4 auto */
void __cdecl city_window_small_font_atexit_dtor(void)

{
  font_destroy((GameFont *)&city_window_small_font);
  return;
}

/* 00500ede auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl city_window_global_init(void)

{
  city_window_static_init();
  city_window_reg_atexit();
  return;
}

/* 00500ef8 auto */
void __cdecl city_window_static_init(void)

{
  city_window_ctor((FrameWindow *)&city_window);
  return;
}

/* 00500f12 auto */
void __cdecl city_window_reg_atexit(void)

{
  _atexit(city_window_atexit_dtor);
  return;
}

/* 00500f2f auto */
void __cdecl city_window_atexit_dtor(void)

{
  city_window_dtor((FrameWindow *)&city_window);
  return;
}

/* 00500f49 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl city_window_bg_surface_global_init(void)

{
  city_window_bg_surface_static_init();
  city_window_bg_surface_reg_atexit();
  return;
}

/* 00500f63 auto */
void __cdecl city_window_bg_surface_static_init(void)

{
  surface_ctor((DibSurface *)&city_window_bg_surface);
  return;
}

/* 00500f7d auto */
void __cdecl city_window_bg_surface_reg_atexit(void)

{
  _atexit(city_window_bg_surface_atexit_dtor);
  return;
}

/* 00500f9a auto */
void __cdecl city_window_bg_surface_atexit_dtor(void)

{
  surface_dtor((DibSurface *)&city_window_bg_surface);
  return;
}

/* 00500fb4 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl city_tile_pick_surface_global_init(void)

{
  city_tile_pick_surface_static_init();
  city_tile_pick_surface_reg_atexit();
  return;
}

/* 00500fce auto */
void __cdecl city_tile_pick_surface_static_init(void)

{
  surface_ctor((DibSurface *)&city_tile_pick_surface);
  return;
}

/* 00500fe8 auto */
void __cdecl city_tile_pick_surface_reg_atexit(void)

{
  _atexit(city_tile_pick_surface_atexit_dtor);
  return;
}

/* 00501005 auto */
void __cdecl city_tile_pick_surface_atexit_dtor(void)

{
  surface_dtor((DibSurface *)&city_tile_pick_surface);
  return;
}

/* 0050101f auto */
#define city_window_size_level (*(int *)((u8 *)&g.d_006aa78c))
#define local_4d8 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_4c8 (*(DibSurface *)(frame_ + FRAME_OFF(16)))
#define local_480 (*(GamePalette *)(frame_ + FRAME_OFF(88)))
#define local_4c (*(Sprite *)(frame_ + FRAME_OFF(1164)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1224)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1228)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(1232)))
void __cdecl city_window_load_background(void)

{
  i32 uVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(1240)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  surface_ctor(&local_4c8);
  local_8 = 0;
  sprite_init(&local_4c);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  palette_init(&local_480);
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  if (city_window_size_level == city_window_bg_size_level) {
    (*(i8 *)((char *)&local_8 + 0)) = 1;
    /* inlined unwind funclet FUN_0050117b */ { palette_destroy((GamePalette *)((iptr)&local_480)); }
    local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
    /* inlined unwind funclet FUN_00501187 */ { sprite_destroy((Sprite *)((iptr)&local_4c)); }
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_00501190 */ { surface_dtor((DibSurface *)((iptr)&local_4c8)); }
  }
  else {
    city_window_bg_size_level = city_window_size_level;
    surface_release((DibSurface *)&city_window_bg_surface);
    surface_load_gif_file(&local_4c8,ADDR(0x630d6c, ((u8 *)&g.d_00630d6c)),10,0xc0,(iptr)&local_480);
    sprite_grab_from_surface(&local_4c,(iptr)&local_4c8,7,0,0,0x27c,0x1a5);
    surface_release(&local_4c8);
    uVar1 = city_window_scale((C_004083b0_4 *)&city_window,0x1a5);
    uVar2 = city_window_scale((C_004083b0_4 *)&city_window,0x27c);
    surface_create((DibSurface *)&city_window_bg_surface,uVar2,uVar1);
    gfx_set_zoom_scale(city_window_bg_size_level * 4 - 8);
    sprite_draw(&local_4c,(iptr)local_4d8,ADDR(0x6a9170, ((u8 *)&g.d_006a9170)),0,0);
    gfx_reset_zoom_scale();
    (*(i8 *)((char *)&local_8 + 0)) = 1;
    /* inlined unwind funclet FUN_0050117b */ { palette_destroy((GamePalette *)((iptr)&local_480)); }
    local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
    /* inlined unwind funclet FUN_00501187 */ { sprite_destroy((Sprite *)((iptr)&local_4c)); }
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_00501190 */ { surface_dtor((DibSurface *)((iptr)&local_4c8)); }
  }
  return;
}
#undef city_window_size_level
#undef local_4d8
#undef local_4c8
#undef local_480
#undef local_4c
#undef uStack_10
#undef puStack_c
#undef local_8

/* 005013bc auto */
#define dlg_help_pressed (*(int *)((u8 *)&g.d_00631edc))
void __cdecl city_window_modal_notice(void)

{
  if (city_modal_notice_active == '\0') {
    city_modal_notice_active = 1;
    text_clear();
    text_append(ADDR(0x630d78, ((u8 *)&g.d_00630d78)));
    text_append_int((city_window_open_mode == 2) + 1);
    popup_game(ADDR(0x679640, ((u8 *)&g.d_00679640)));
    if (dlg_help_pressed != 0) {
      city_window_exit_clicked(0);
    }
    city_modal_notice_active = '\0';
  }
  return;
}
#undef dlg_help_pressed

/* 00501440 auto */
void __thiscall city_window_reset_state(FrameWindow *this)

{
  clickmap_clear((ClickMapClearView *)&this->field_2d8);
  this[7].pad_15c[0xc] = 1;
  this[7].pad_15c[0xd] = '\0';
  this[7].pad_15c[0xe] = '\0';
  this[7].pad_15c[0xf] = '\0';
  this[7].pad_15c[8] = '\0';
  this[7].pad_15c[9] = '\0';
  this[7].pad_15c[10] = '\0';
  this[7].pad_15c[0xb] = '\0';
  this[7].pad_15c[0x10] = '\0';
  this[7].pad_15c[0x11] = '\0';
  this[7].pad_15c[0x12] = '\0';
  this[7].pad_15c[0x13] = '\0';
  this[7].pad_15c[4] = 0xff;
  this[7].pad_15c[5] = 0xff;
  this[7].pad_15c[6] = 0xff;
  this[7].pad_15c[7] = 0xff;
  this[7].pad_15c[0x1c] = '\0';
  this[7].pad_15c[0x1d] = '\0';
  this[7].pad_15c[0x1e] = '\0';
  this[7].pad_15c[0x1f] = '\0';
  this[7].pad_15c[0x20] = 1;
  this[7].pad_15c[0x21] = '\0';
  this[7].pad_15c[0x22] = '\0';
  this[7].pad_15c[0x23] = '\0';
  this[7].pad_274[0xc] = '\0';
  this[7].pad_274[0xd] = '\0';
  this[7].pad_274[0xe] = '\0';
  this[7].pad_274[0xf] = '\0';
  return;
}

/* 005014bf auto */
/* Library Function - Single Match
    public: void __thiscall CMiniDockFrameWnd::OnClose(void)
   
   Library: Visual Studio 1998 Debug */

void __thiscall city_window_remove_citizen_hotspots(FrameWindow *this)

{
  clickmap_remove_by_id((ClickMapRemoveView *)&this->field_2d8,2);
  return;
}

/* 005014e5 auto */
void __thiscall city_window_remove_panel_hotspots(FrameWindow *this)

{
  clickmap_remove_by_id((ClickMapRemoveView *)&this->field_2d8,1);
  clickmap_remove_by_id((ClickMapRemoveView *)&this->field_2d8,3);
  clickmap_remove_by_id((ClickMapRemoveView *)&this->field_2d8,4);
  return;
}

/* 0050152b auto */
void __thiscall city_window_remove_hotspots(FrameWindow *this)

{
  city_window_remove_panel_hotspots(this);
  city_window_remove_citizen_hotspots(this);
  return;
}

/* 00501551 auto */
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
FrameWindow * __thiscall city_window_ctor(FrameWindow *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  frame_wnd_ctor((SurfaceWindow *)this);
  local_8 = 0;
  clickmap_ctor(&this->field_2d8);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  font_init_empty((GameFont *)&this[7].field_270);
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),2);
  this->vtable = (u32)&PTR_FUN_0061d6d4;
  city_window_reset_state(this);
  return this;
}
#undef local_10
#undef puStack_c
#undef local_8

/* 0050160a auto */
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __thiscall city_window_dtor(FrameWindow *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  this->vtable = (u32)&PTR_FUN_0061d6d4;
  (*(i32 *)((char *)&local_8 + 1)) = 0;
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  city_window_remove_hotspots(this);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  /* inlined unwind funclet FUN_00501673 */ { font_destroy((GameFont *)(*(int *)((iptr)&this) + 0x16ac)); }
  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
  /* inlined unwind funclet FUN_00501682 */ { clickmap_dtor(*(int *)((iptr)&this) + 0x2d8); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_00501691 */ { frame_wnd_dtor(*(DibSurface **)((iptr)&this)); }
  return;
}
#undef uStack_10
#undef puStack_c
#undef local_8

/* 005016b2 auto */
void __thiscall city_window_blit_bg_rect(C_004083b0_12c *this,int *param_1)

{
  i32 uVar1;
  i32 uVar2;
  
  uVar1 = rect_height((iptr)param_1);
  uVar2 = rect_width((iptr)param_1);
  gfx_copy_rect_xywh(ADDR(0x6a9170, ((u8 *)&g.d_006a9170)),(iptr)this,
                     (*param_1 - *(int *)(this[0x12].pad_48 + 100)) - this->client_x,
                     (param_1[1] - *(int *)(this[0x12].pad_48 + 0x68)) - this->client_y,*param_1,
                     param_1[1],uVar2,uVar1);
  return;
}

/* 00501733 auto */
void __thiscall city_window_begin_draw(C_004083b0_12c *this,iptr param_1)

{
  gfx_set_draw_target((iptr)this);
  text_set_surface((iptr)this);
  text_set_font((iptr)(this[0x13].pad_48 + 0x20));
  city_window_blit_bg_rect(this,param_1);
  return;
}

/* 00501780 auto */
void __thiscall city_window_recalc_redraw(C_004083b0_4 *this,i32 param_1)

{
  if ((((this[0x569].field_0 == 0) && (this[0x568].field_0 == 0)) && (this[0x56a].field_0 == 0)) &&
     (-1 < (int)this[0x567].field_0)) {
    city_recalc(this[0x567].field_0,1);
    city_window_draw_citizens((FrameWindow *)&city_window,1,param_1);
    city_window_draw_resource_map((FrameWindow *)&city_window,1);
    city_window_draw_info_panel((FrameWindow *)&city_window,1);
  }
  return;
}

/* 00501819 auto */
#define city_specialist_count (*(int *)((u8 *)&g.d_006a6604))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define local_10 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl city_window_cycle_specialist(int param_1)

{
  iptr city3;
  iptr city;
  iptr city4;
  int city2;
  int iVar5;
  short sVar6;
  i32 uVar7;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  city3 = citywnd_get_city((C_004083b0_4 *)&city_window);
  if ((cities[city3].owner == human_civ) || (game.reveal_map != '\0')) {
    uVar7 = 0;
    city = citywnd_get_city((C_004083b0_4 *)&city_window);
    city_recalc(city,uVar7);
    citywnd_get_city((C_004083b0_4 *)&city_window);
    city4 = citywnd_get_city((C_004083b0_4 *)&city_window);
    if (cities[city4].size - city_specialist_count <= (int)(short)param_1) {
      city2 = citywnd_get_city((C_004083b0_4 *)&city_window);
      sVar6 = (short)param_1 - ((short)cities[city2].size - (short)city_specialist_count);
      if (sVar6 < city_specialist_count) {
        iVar5 = (int)sVar6;
        city2 = iVar5;
        city = citywnd_get_city((C_004083b0_4 *)&city_window);
        local_10 = city_specialist_type(city,city2);
        city2 = citywnd_get_city((C_004083b0_4 *)&city_window);
        if (cities[city2].size < 5) {
          if (local_10 == 1) {
            city = citywnd_get_city((C_004083b0_4 *)&city_window);
            popup_game_with_city(ADDR(0x630d84, ((u8 *)&g.d_00630d84)),city);
            return;
          }
          local_10 = 1;
        }
        else {
          local_10++;
          if (3 < local_10) {
            local_10 = 1;
          }
        }
        city = citywnd_get_city((C_004083b0_4 *)&city_window);
        city_set_specialist_type(city,iVar5,local_10);
        city_window_recalc_redraw((C_004083b0_4 *)&city_window,1);
      }
    }
  }
  return;
}
#undef city_specialist_count
#undef human_civ
#undef local_10

/* 005019c1 auto */
#define city_specialist_count (*(int *)((u8 *)&g.d_006a6604))
#define local_94 (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_84 (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
#define local_74 (*(i8 (*)[16])(frame_ + FRAME_OFF(36)))
#define local_64 (*(i8 (*)[16])(frame_ + FRAME_OFF(52)))
#define local_54 (*(i8 (*)[16])(frame_ + FRAME_OFF(68)))
#define local_44 (*(i8 (*)[16])(frame_ + FRAME_OFF(84)))
#define local_34 (*(i8 (*)[16])(frame_ + FRAME_OFF(100)))
#define local_24 (*(i8 (*)[16])(frame_ + FRAME_OFF(116)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(132)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(136)))
#define local_c (*(int *)(frame_ + FRAME_OFF(140)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(144)))
int __thiscall
city_window_draw_citizen_row
          (C_004083b0_4 *this,int param_1,int param_2,i32 param_3,int param_4,int param_5,
          int param_6)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  i8 *puVar5;
  C_004083b0_4 *pCVar6;
  iptr iVar7;
  iptr iVar8;
  i32 uVar9;
  i8 frame_[FRAME_OFF(152)] __attribute__((aligned(8)));  /* original stack frame */
  
  gfx_set_zoom_scale(this[0x575].field_0 * 4 - 8);
  iVar8 = 0;
  iVar7 = 0;
  iVar1 = city_window_scale(this,0x1b);
  local_10 = ui_calc_item_spacing((int)cities[this[0x567].field_0].size,iVar1 + 1,param_3,iVar7,iVar8)
  ;
  local_8 = 0;
  for (local_c = 0; local_c < param_4; local_c++) {
    uVar9 = 10;
    iVar1 = param_2 + 1;
    iVar2 = param_1 + 1;
    puVar5 = local_24;
    pCVar6 = this;
    iVar3 = civ_city_style_era((int)cities[this[0x567].field_0].owner);
    sprite_draw_silhouette
              ((Sprite *)(&citizen_sprites + iVar3 * 0x294 + (local_8 & 1) * 0x3c),(iptr)puVar5,
               (iptr)pCVar6,iVar2,iVar1,uVar9);
    puVar5 = local_34;
    pCVar6 = this;
    iVar1 = param_1;
    iVar2 = param_2;
    iVar3 = civ_city_style_era((int)cities[this[0x567].field_0].owner);
    sprite_draw
              ((Sprite *)(&citizen_sprites + iVar3 * 0x294 + (local_8 & 1) * 0x3c),(iptr)puVar5,
               (iptr)pCVar6,iVar1,iVar2);
    param_1 += local_10;
    local_8++;
  }
  for (local_c = 0;
      local_c < (int)cities[this[0x567].field_0].size - (param_5 + param_4 + city_specialist_count);
      local_c = local_c + 1) {
    uVar9 = 10;
    iVar1 = param_2 + 1;
    iVar2 = param_1 + 1;
    puVar5 = local_44;
    pCVar6 = this;
    iVar3 = civ_city_style_era((int)cities[this[0x567].field_0].owner);
    sprite_draw_silhouette
              ((Sprite *)(&citizen_sprites + iVar3 * 0x294 + ((local_8 & 1) * 4 + 8) * 0xf),
               (iptr)puVar5,(iptr)pCVar6,iVar2,iVar1,uVar9);
    puVar5 = local_54;
    pCVar6 = this;
    iVar1 = param_1;
    iVar2 = param_2;
    iVar3 = civ_city_style_era((int)cities[this[0x567].field_0].owner);
    sprite_draw
              ((Sprite *)(&citizen_sprites + iVar3 * 0x294 + ((local_8 & 1) * 4 + 8) * 0xf),
               (iptr)puVar5,(iptr)pCVar6,iVar1,iVar2);
    param_1 += local_10;
    local_8++;
  }
  for (local_c = 0; local_c < param_5; local_c++) {
    if (local_c < param_5 - param_6) {
      local_14 = 4;
    }
    else {
      local_14 = 6;
    }
    uVar9 = 10;
    iVar1 = param_2 + 1;
    iVar2 = param_1 + 1;
    puVar5 = local_64;
    pCVar6 = this;
    iVar3 = civ_city_style_era((int)cities[this[0x567].field_0].owner);
    sprite_draw_silhouette
              ((Sprite *)(&citizen_sprites + iVar3 * 0x294 + ((local_8 & 1) + local_14) * 0x3c),
               (iptr)puVar5,(iptr)pCVar6,iVar2,iVar1,uVar9);
    puVar5 = local_74;
    pCVar6 = this;
    iVar1 = param_1;
    iVar2 = param_2;
    iVar3 = civ_city_style_era((int)cities[this[0x567].field_0].owner);
    sprite_draw
              ((Sprite *)(&citizen_sprites + iVar3 * 0x294 + ((local_8 & 1) + local_14) * 0x3c),
               (iptr)puVar5,(iptr)pCVar6,iVar1,iVar2);
    param_1 += local_10;
    local_8++;
  }
  for (local_c = 0; local_c < city_specialist_count; local_c++) {
    uVar9 = 10;
    iVar1 = param_2 + 1;
    iVar2 = param_1 + 1;
    puVar5 = local_84;
    pCVar6 = this;
    iVar3 = civ_city_style_era((int)cities[this[0x567].field_0].owner);
    iVar4 = city_specialist_type(this[0x567].field_0,local_c);
    sprite_draw_silhouette
              ((Sprite *)(&citizen_sprites + iVar3 * 0x294 + (iVar4 * 4 + 0x1c) * 0xf),
               (iptr)puVar5,(iptr)pCVar6,iVar2,iVar1,uVar9);
    puVar5 = local_94;
    pCVar6 = this;
    iVar1 = param_1;
    iVar2 = param_2;
    iVar3 = civ_city_style_era((int)cities[this[0x567].field_0].owner);
    iVar4 = city_specialist_type(this[0x567].field_0,local_c);
    sprite_draw
              ((Sprite *)(&citizen_sprites + iVar3 * 0x294 + (iVar4 * 4 + 0x1c) * 0xf),
               (iptr)puVar5,(iptr)pCVar6,iVar1,iVar2);
    param_1 += local_10;
  }
  gfx_reset_zoom_scale();
  return local_10;
}
#undef city_specialist_count
#undef local_94
#undef local_84
#undef local_74
#undef local_64
#undef local_54
#undef local_44
#undef local_34
#undef local_24
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 00501e63 auto */
#define city_specialist_count (*(int *)((u8 *)&g.d_006a6604))
#define local_54 (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_44 (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
#define local_34 (*(i8 (*)[16])(frame_ + FRAME_OFF(36)))
#define local_24 (*(i8 (*)[16])(frame_ + FRAME_OFF(52)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(68)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(72)))
#define local_c (*(int *)(frame_ + FRAME_OFF(76)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(80)))
int __thiscall
city_happy_draw_citizen_row
          (C_004083b0_4 *this,int param_1,i32 param_2,i32 param_3,int param_4,
          int param_5,int param_6)

{
  int iVar1;
  int iVar2;
  i8 *puVar3;
  C_004083b0_4 *pCVar4;
  iptr iVar5;
  iptr iVar6;
  i32 uVar7;
  i8 frame_[FRAME_OFF(88)] __attribute__((aligned(8)));  /* original stack frame */
  
  gfx_set_zoom_scale(this[0x575].field_0 * 4 - 8);
  iVar6 = 0;
  iVar5 = 0;
  iVar1 = city_window_scale(this,0xf);
  local_10 = ui_calc_item_spacing((int)cities[this[0x567].field_0].size,iVar1 + 1,param_3,iVar5,iVar6)
  ;
  local_8 = 0;
  for (local_c = 0; local_c < param_4; local_c++) {
    sprite_draw
              ((Sprite *)(&small_citizen_sprites + (local_8 & 1) * 0x3c),(iptr)local_24,(iptr)this,
               param_1,param_2);
    param_1 += local_10;
    local_8++;
  }
  for (local_c = 0;
      local_c < (int)cities[this[0x567].field_0].size - (param_5 + param_4 + city_specialist_count);
      local_c = local_c + 1) {
    sprite_draw
              ((Sprite *)(&small_citizen_sprites + ((local_8 & 1) * 4 + 8) * 0xf),(iptr)local_34,
               (iptr)this,param_1,param_2);
    param_1 += local_10;
    local_8++;
  }
  for (local_c = 0; local_c < param_5; local_c++) {
    if (local_c < param_5 - param_6) {
      local_14 = 4;
    }
    else {
      local_14 = 6;
    }
    sprite_draw
              ((Sprite *)(&small_citizen_sprites + ((local_8 & 1) + local_14) * 0x3c),(iptr)local_44,
               (iptr)this,param_1,param_2);
    param_1 += local_10;
    local_8++;
  }
  for (local_c = 0; local_c < city_specialist_count; local_c++) {
    puVar3 = local_54;
    pCVar4 = this;
    iVar1 = param_1;
    uVar7 = param_2;
    iVar2 = city_specialist_type(this[0x567].field_0,local_c);
    sprite_draw
              ((Sprite *)(&small_citizen_sprites + (iVar2 * 4 + 0x1c) * 0xf),(iptr)puVar3,(iptr)pCVar4
               ,iVar1,uVar7);
    param_1 += local_10;
  }
  gfx_reset_zoom_scale();
  return local_10;
}
#undef city_specialist_count
#undef local_54
#undef local_44
#undef local_34
#undef local_24
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 0050207f auto */
#define city_angry_count (*(i32 *)((u8 *)&g.d_006a659c))
#define city_happy_count (*(i32 *)((u8 *)&g.d_006a6550))
#define city_unhappy_count (*(i32 *)((u8 *)&g.d_006a65a8))
#define local_28 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
void __thiscall city_window_draw_citizens(FrameWindow *this,int param_1,i32 param_2)

{
  int iVar1;
  i32 uVar2;
  int iVar3;
  int iVar4;
  i32 uVar5;
  iptr iVar6;
  i32 uVar7;
  i32 uVar8;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((((*(int *)(this[7].pad_15c + 0xc) == 0) && (*(int *)(this[7].pad_15c + 8) == 0)) &&
      (*(int *)(this[7].pad_15c + 0x10) == 0)) && (-1 < *(int *)(this[7].pad_15c + 4))) {
    city_window_begin_draw((C_004083b0_12c *)this,(iptr)(this[7].pad_15c + 0x44));
    clickmap_remove_by_id((ClickMapRemoveView *)&this->field_2d8,2);
    local_28 = *(int *)(this[7].pad_15c + 0x44);
    iVar1 = *(int *)(this[7].pad_15c + 0x48);
    text_set_colors(0x7c,0x12,1,1);
    text_clear();
    text_append_label(0x193);
    uVar2 = city_window_scale((C_004083b0_4 *)this,0xc6);
    iVar3 = city_window_scale((C_004083b0_4 *)this,0x2e);
    iVar3 = iVar1 + iVar3;
    iVar4 = city_window_scale((C_004083b0_4 *)this,2);
    gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_28 + iVar4,iVar3,uVar2);
    text_clear();
    text_append_label(0x3f);
    uVar2 = city_window_scale((C_004083b0_4 *)this,0xee);
    iVar3 = city_window_scale((C_004083b0_4 *)this,0x2e);
    iVar3 = iVar1 + iVar3;
    iVar4 = city_window_scale((C_004083b0_4 *)this,199);
    gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_28 + iVar4,iVar3,uVar2);
    uVar2 = city_happy_count;
    uVar7 = city_unhappy_count;
    uVar8 = city_angry_count;
    uVar5 = city_window_scale((C_004083b0_4 *)this,0x1a6);
    iVar3 = city_window_scale((C_004083b0_4 *)this,9);
    iVar3 = iVar1 + iVar3;
    iVar4 = city_window_scale((C_004083b0_4 *)this,5);
    iVar3 = city_window_draw_citizen_row
                      ((C_004083b0_4 *)this,local_28 + iVar4,iVar3,uVar5,uVar2,uVar7,uVar8);
    iVar4 = city_window_scale((C_004083b0_4 *)this,5);
    local_28 += iVar4;
    iVar4 = city_window_scale((C_004083b0_4 *)this,9);
    for (local_18 = 0; local_18 < cities[*(int *)(this[7].pad_15c + 4)].size;
        local_18 = local_18 + 1) {
      iVar6 = city_window_scale((C_004083b0_4 *)this,0x1e);
      rect_set_xywh((iptr)local_14,local_28,iVar1 + iVar4,iVar3,iVar6);
      hotspot_add_rect((ClickMap *)&this->field_2d8,local_18,2,(iptr)local_14);
      local_28 += iVar3;
    }
    if (param_1 != 0) {
      wnd_blit_surface_rect((DibSurface *)this,(iptr)(this[7].pad_15c + 0x44));
    }
  }
  return;
}
#undef city_angry_count
#undef city_happy_count
#undef city_unhappy_count
#undef local_28
#undef local_18
#undef local_14

/* 005022c0 auto */
#define city_specialist_count (*(int *)((u8 *)&g.d_006a6604))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define local_20 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_1c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_14 (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(20)))
void __cdecl city_window_toggle_worked_tile(int param_1,int param_2)

{
  iptr city3;
  iptr city;
  iptr iVar2;
  int city2;
  int iVar5;
  int iVar6;
  iptr city5;
  iptr city4;
  i32 uVar9;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_1c = -1;
  city3 = citywnd_get_city((C_004083b0_4 *)&city_window);
  if ((cities[city3].owner == human_civ) || (game.reveal_map != '\0')) {
    uVar9 = 0;
    city = citywnd_get_city((C_004083b0_4 *)&city_window);
    city_recalc(city,uVar9);
    iVar2 = gfx_zoom_scale(0x40,city_window_map_zoom);
    city2 = gfx_zoom_scale(0x20,city_window_map_zoom);
    iVar5 = city_window_scale((C_004083b0_4 *)&city_window,5);
    iVar5 = city_window_map_rect + iVar5;
    iVar6 = city_window_scale((C_004083b0_4 *)&city_window,0xb);
    iVar5 = param_1 - iVar5;
    iVar6 = param_2 - (city_window_map_rect_top + iVar6 + (city2 >> 1));
    if ((-1 < iVar5) && (((iVar5 < iVar2 * 4 && (-1 < iVar6)) && (iVar6 < city2 * 4)))) {
      local_18 = (iVar5 / iVar2) * 2 - 3;
      local_20 = (iVar6 / city2) * 2 - 3;
      if ((iVar5 % iVar2 < 0) || (iVar6 % city2 < 0)) {
        local_14 = 0;
      }
      else {
        city2 = surface_get_pixel
                          ((DibSurface *)&city_tile_pick_surface,iVar5 % iVar2,iVar6 % city2);
        local_14 = city2 - 10 >> 4;
      }
      if (local_14 != 0) {
        local_18 += (char)(&pick_quadrant_dx_table)[local_14];
        local_20 += (char)(&pick_quadrant_dy_table)[local_14];
      }
      for (local_c = 0; local_c < 0x15; local_c++) {
        if (((char)(&city_tile_dx_table)[local_c] == local_18) &&
           ((char)(&city_tile_dy_table)[local_c] == local_20)) {
          local_1c = local_c;
          break;
        }
      }
      if (-1 < local_1c) {
        if (local_1c == 0x14) {
          city2 = citywnd_get_city((C_004083b0_4 *)&city_window);
          cities[city2].worked_tiles = 0;
        }
        else {
          city = local_1c;
          city5 = citywnd_get_city((C_004083b0_4 *)&city_window);
          city2 = city_tile_worked(city5,city);
          if (city2 == 0) {
            if ((&city_tile_flags)[local_1c] != '\0') {
              return;
            }
            if (city_specialist_count == 0) {
              city2 = citywnd_get_city((C_004083b0_4 *)&city_window);
              cities[city2].worked_tiles = 0;
            }
            else {
              uVar9 = 1;
              city = citywnd_get_city((C_004083b0_4 *)&city_window);
              city_set_tile_worked(city,local_1c,uVar9);
              uVar9 = 0xffffffff;
              city = citywnd_get_city((C_004083b0_4 *)&city_window);
              city_adjust_specialists(city,uVar9);
            }
          }
          else {
            uVar9 = 0;
            city4 = citywnd_get_city((C_004083b0_4 *)&city_window);
            city_set_tile_worked(city4,local_1c,uVar9);
            uVar9 = 1;
            city = citywnd_get_city((C_004083b0_4 *)&city_window);
            city_adjust_specialists(city,uVar9);
          }
        }
        city_window_recalc_redraw((C_004083b0_4 *)&city_window,0);
      }
    }
  }
  return;
}
#undef city_specialist_count
#undef human_civ
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef local_c

/* 005025d5 auto */
#define city_building_content (*(int *)((u8 *)&g.d_006a6618))
#define city_science_total (*(int *)((u8 *)&g.d_006a6578))
#define city_shield_support (*(int *)((u8 *)&g.d_006a6568))
#define city_tax_total (*(int *)((u8 *)&g.d_006a6554))
#define city_tile_yields (*(i32 *)((u8 *)&g.d_006a65b8))
#define city_total_shields (*(int *)((u8 *)&g.d_006a65cc))
#define city_total_trade (*(int *)((u8 *)&g.d_006a65d0))
#define city_trade_corruption (*(uint *)((u8 *)&g.d_006a6580))
#define city_yield_totals (*(int *)((u8 *)&g.d_006a65c8))
#define settler_food_cost (*(int *)((u8 *)&g.d_006a6608))
#define local_20c (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_208 (*(uint *)(frame_ + FRAME_OFF(8)))
#define local_204 (*(uint *)(frame_ + FRAME_OFF(12)))
#define local_200 (*(uint *)(frame_ + FRAME_OFF(16)))
#define local_1fc (*(uint *)(frame_ + FRAME_OFF(20)))
#define local_1f8 (*(uint *)(frame_ + FRAME_OFF(24)))
#define local_1f4 (*(uint *)(frame_ + FRAME_OFF(28)))
#define local_1f0 (*(i8 (*)[16])(frame_ + FRAME_OFF(32)))
#define local_1e0 (*(i8 (*)[16])(frame_ + FRAME_OFF(48)))
#define local_1d0 (*(i8 (*)[16])(frame_ + FRAME_OFF(64)))
#define local_1c0 (*(i8 (*)[16])(frame_ + FRAME_OFF(80)))
#define local_1b0 (*(i8 (*)[16])(frame_ + FRAME_OFF(96)))
#define local_1a0 (*(i8 (*)[16])(frame_ + FRAME_OFF(112)))
#define local_190 (*(i8 (*)[16])(frame_ + FRAME_OFF(128)))
#define local_180 (*(i8 (*)[16])(frame_ + FRAME_OFF(144)))
#define local_170 (*(i8 (*)[16])(frame_ + FRAME_OFF(160)))
#define local_160 (*(i8 (*)[16])(frame_ + FRAME_OFF(176)))
#define local_150 (*(i8 (*)[16])(frame_ + FRAME_OFF(192)))
#define local_140 (*(i8 (*)[16])(frame_ + FRAME_OFF(208)))
#define local_130 (*(i8 (*)[16])(frame_ + FRAME_OFF(224)))
#define local_120 (*(i8 (*)[16])(frame_ + FRAME_OFF(240)))
#define local_110 (*(i8 (*)[16])(frame_ + FRAME_OFF(256)))
#define local_100 (*(int *)(frame_ + FRAME_OFF(272)))
#define x2 (*(int *)(frame_ + FRAME_OFF(276)))
#define civ (*(iptr *)(frame_ + FRAME_OFF(280)))
#define local_f4 (*(int *)(frame_ + FRAME_OFF(284)))
#define local_f0 (*(int *)(frame_ + FRAME_OFF(288)))
#define local_ec (*(int *)(frame_ + FRAME_OFF(292)))
#define local_e8 (*(int *)(frame_ + FRAME_OFF(296)))
#define local_e4 (*(int *)(frame_ + FRAME_OFF(300)))
#define local_e0 (*(int *)(frame_ + FRAME_OFF(304)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(308)))
#define local_d8 (*(int *)(frame_ + FRAME_OFF(312)))
#define local_d4 (*(int *)(frame_ + FRAME_OFF(316)))
#define local_d0 (*(int *)(frame_ + FRAME_OFF(320)))
#define local_cc (*(int *)(frame_ + FRAME_OFF(324)))
#define local_c8 (*(int *)(frame_ + FRAME_OFF(328)))
#define local_c4 (*(iptr *)(frame_ + FRAME_OFF(332)))
#define city (*(int *)(frame_ + FRAME_OFF(336)))
#define local_bc (*(int *)(frame_ + FRAME_OFF(340)))
#define local_b8 (*(int *)(frame_ + FRAME_OFF(344)))
#define local_b4 (*(int *)(frame_ + FRAME_OFF(348)))
#define local_b0 (*(int *)(frame_ + FRAME_OFF(352)))
#define local_ac (*(int *)(frame_ + FRAME_OFF(356)))
#define local_a8 (*(int *)(frame_ + FRAME_OFF(360)))
#define local_a4 (*(int *)(frame_ + FRAME_OFF(364)))
#define local_a0 (*(int *)(frame_ + FRAME_OFF(368)))
#define local_9c (*(int *)(frame_ + FRAME_OFF(372)))
#define local_98 (*(int *)(frame_ + FRAME_OFF(376)))
#define local_94 (*(iptr *)(frame_ + FRAME_OFF(380)))
#define local_90 (*(int *)(frame_ + FRAME_OFF(384)))
#define local_8c (*(int *)(frame_ + FRAME_OFF(388)))
#define local_88 (*(int *)(frame_ + FRAME_OFF(392)))
#define local_84 (*(int *)(frame_ + FRAME_OFF(396)))
#define local_80 (*(int *)(frame_ + FRAME_OFF(400)))
#define local_7c (*(int *)(frame_ + FRAME_OFF(404)))
#define local_78 (*(int *)(frame_ + FRAME_OFF(408)))
#define local_74 (*(int *)(frame_ + FRAME_OFF(412)))
#define local_70 (*(int *)(frame_ + FRAME_OFF(416)))
#define local_6c (*(int *)(frame_ + FRAME_OFF(420)))
#define local_68 (*(int *)(frame_ + FRAME_OFF(424)))
#define local_64 (*(int *)(frame_ + FRAME_OFF(428)))
#define local_60 (*(int *)(frame_ + FRAME_OFF(432)))
#define local_5c (*(iptr *)(frame_ + FRAME_OFF(436)))
#define local_58 (*(int *)(frame_ + FRAME_OFF(440)))
#define local_54 (*(int *)(frame_ + FRAME_OFF(444)))
#define local_50 (*(int *)(frame_ + FRAME_OFF(448)))
#define y2 (*(iptr *)(frame_ + FRAME_OFF(452)))
#define local_48 (*(int *)(frame_ + FRAME_OFF(456)))
#define local_44 (*(int *)(frame_ + FRAME_OFF(460)))
#define local_40 (*(uint *)(frame_ + FRAME_OFF(464)))
#define local_3c (*(iptr *)(frame_ + FRAME_OFF(468)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(472)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(476)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(480)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(484)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(488)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(492)))
#define local_20 (*(i8 (*)[16])(frame_ + FRAME_OFF(496)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(512)))
#define local_c (*(uint *)(frame_ + FRAME_OFF(516)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(520)))
void __thiscall city_window_draw_resource_map(FrameWindow *this,int param_1)

{
  u32 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  i32 uVar5;
  int iVar6;
  iptr iVar7;
  iptr iVar8;
  i32 uVar9;
  i32 uVar10;
  i8 frame_[FRAME_OFF(528)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((((*(int *)(this[7].pad_15c + 0xc) == 0) && (*(int *)(this[7].pad_15c + 8) == 0)) &&
      (*(int *)(this[7].pad_15c + 0x10) == 0)) && (-1 < *(int *)(this[7].pad_15c + 4))) {
    city_window_begin_draw((C_004083b0_12c *)this,(iptr)(this[7].pad_15c + 0x54));
    local_90 = *(int *)(this[7].pad_15c + 0x54);
    local_a0 = *(int *)(this[7].pad_15c + 0x58);
    local_e0 = gfx_zoom_scale(0x40,*(i32 *)(this[7].pad_15c + 0x40));
    local_100 = gfx_zoom_scale(0x20,*(i32 *)(this[7].pad_15c + 0x40));
    local_80 = local_e0 >> 1;
    local_50 = local_100 >> 1;
    local_58 = city_window_scale((C_004083b0_4 *)this,5);
    local_58 = local_90 + local_58;
    local_a8 = city_window_scale((C_004083b0_4 *)this,0xb);
    local_a8 = local_a0 + local_a8;
    clickmap_remove_by_id((ClickMapRemoveView *)&this->field_2d8,1);
    rect_set_xywh((iptr)local_20,local_58,local_50 + local_a8,local_e0 << 2,local_100 << 2);
    hotspot_add_rect((ClickMap *)&this->field_2d8,0,1,(iptr)local_20);
    local_b4 = local_80 * 3 + local_58;
    local_8c = local_50 * 4 + local_a8;
    for (local_3c = 0; local_3c < 0x15; local_3c++) {
      x2 = map_wrap_x((int)cities[*(int *)(this[7].pad_15c + 4)].x +
                            (int)(char)(&city_resmap_draw_dx_table)[local_3c]);
      y2 = (int)cities[*(int *)(this[7].pad_15c + 4)].y + (int)(char)(&city_resmap_draw_dy_table)[local_3c]
      ;
      local_cc = (char)(&city_resmap_draw_dx_table)[local_3c] * local_80 + local_b4;
      local_e4 = (char)(&city_resmap_draw_dy_table)[local_3c] * local_50 + local_8c;
      local_9c = local_e4 - local_50;
      local_94 = 0;
      for (local_5c = 0; local_5c < 0x15; local_5c++) {
        if (((&city_tile_dx_table)[local_5c] == (&city_resmap_draw_dx_table)[local_3c]) &&
           ((&city_tile_dy_table)[local_5c] == (&city_resmap_draw_dy_table)[local_3c])) {
          local_94 = local_5c;
          break;
        }
      }
      mapview_draw_tile_terrain
                ((C_004083b0_430 *)&map_views,(iptr)this,local_cc,local_e4,x2,y2,
                 (int)cities[*(int *)(this[7].pad_15c + 4)].owner,
                 *(i32 *)(this[7].pad_15c + 0x40),local_94);
      if (local_3c < 0x15) {
        if (((&city_tile_flags)[local_94] & 8) == 0) {
          if (((&city_tile_flags)[local_94] & 4) == 0) {
            if (((&city_tile_flags)[local_94] & 2) != 0) {
              gfx_set_zoom_scale(*(i32 *)(this[7].pad_15c + 0x40));
              sprite_draw
                        ((Sprite *)&hut_sprite,(iptr)local_110,(iptr)this,local_cc,local_e4
                        );
              gfx_reset_zoom_scale();
            }
          }
          else {
            unit = tile_first_unit(x2,y2);
            while ((-1 < unit && (unit_types[units[unit].type].attack == '\0'))) {
              unit = unit_next_in_stack(unit);
            }
            if (-1 < unit) {
              gfx_draw_unit((iptr)this,unit,7,local_cc,local_9c,
                                 *(i32 *)(this[7].pad_15c + 0x40),0);
            }
          }
        }
        else {
          city = city_at(x2,y2);
          if (-1 < city) {
            local_8 = 1;
            gfx_draw_city((iptr)this,city,1,local_cc,local_9c,
                               *(i32 *)(this[7].pad_15c + 0x40));
          }
        }
        if ((((&city_tile_flags)[local_94] & 0x10) != 0) && (((&city_tile_flags)[local_94] & 9) == 0)) {
          gfx_set_zoom_scale(*(i32 *)(this[7].pad_15c + 0x40));
          sprite_draw
                    ((Sprite *)&map_cursor_sprite,(iptr)local_120,(iptr)this,local_cc,local_e4);
          gfx_reset_zoom_scale();
        }
      }
    }
    for (local_3c = 0; local_3c < 0x15; local_3c++) {
      x2 = map_wrap_x((int)cities[*(int *)(this[7].pad_15c + 4)].x +
                            (int)(char)(&city_resmap_draw_dx_table)[local_3c]);
      y2 = (int)cities[*(int *)(this[7].pad_15c + 4)].y + (int)(char)(&city_resmap_draw_dy_table)[local_3c]
      ;
      local_cc = (char)(&city_resmap_draw_dx_table)[local_3c] * local_80 + local_b4;
      local_e4 = (char)(&city_resmap_draw_dy_table)[local_3c] * local_50 + local_8c;
      local_9c = local_e4 - local_50;
      local_94 = 0;
      for (local_5c = 0; local_5c < 0x15; local_5c++) {
        if (((&city_tile_dx_table)[local_5c] == (&city_resmap_draw_dx_table)[local_3c]) &&
           ((&city_tile_dy_table)[local_5c] == (&city_resmap_draw_dy_table)[local_3c])) {
          local_94 = local_5c;
          break;
        }
      }
      iVar2 = city_tile_worked(*(iptr *)(this[7].pad_15c + 4),local_94);
      if (iVar2 != 0) {
        gfx_set_zoom_scale(*(int *)(this[7].pad_15c + 0x3c) * 4 - 8);
        local_e8 = 0;
        city_calc_tile_yields(*(iptr *)(this[7].pad_15c + 4),local_94,0);
        iVar2 = local_e0;
        local_7c = city_tile_shields + city_tile_trade + city_tile_yields;
        if (local_7c == 0) {
          local_7c = 1;
          local_e8 = 1;
        }
        iVar8 = 0;
        iVar7 = 0;
        iVar3 = city_window_scale((C_004083b0_4 *)this,8);
        iVar2 += iVar3 * -2;
        iVar3 = city_window_scale((C_004083b0_4 *)this,10);
        local_70 = ui_calc_item_spacing(local_7c,iVar3 + 1,iVar2,iVar7,iVar8);
        iVar2 = local_e0;
        iVar3 = city_window_scale((C_004083b0_4 *)this,8);
        iVar4 = city_window_scale((C_004083b0_4 *)this,10);
        local_74 = (iVar2 + iVar3 * -2) / (iVar4 + 1);
        if (local_7c <= local_74) {
          local_7c = local_74;
        }
        local_c4 = 0;
        local_6c = 0;
        local_78 = city_window_scale((C_004083b0_4 *)this,8);
        local_78 = local_cc + local_78;
        iVar3 = local_50 + local_e4;
        iVar2 = city_window_scale((C_004083b0_4 *)this,10);
        local_88 = iVar3 - (iVar2 >> 1);
        for (; local_c4 < 3; local_c4++) {
          while ((&city_tile_yields)[local_c4] != 0) {
            sprite_draw
                      ((Sprite *)(&small_resource_icon_sprites + local_c4 * 0x3c),(iptr)local_130,(iptr)this
                       ,local_78,local_88);
            local_6c++;
            if (local_6c < local_7c) {
              local_78 += local_70;
            }
            else {
              local_6c = 0;
              local_78 = city_window_scale((C_004083b0_4 *)this,8);
              local_78 = local_cc + local_78;
              iVar2 = city_window_scale((C_004083b0_4 *)this,0xb);
              local_88 += iVar2;
            }
            (&city_tile_yields)[local_c4] = (&city_tile_yields)[local_c4] - 1;
          }
        }
        if (local_e8 != 0) {
          sprite_draw
                    ((Sprite *)&small_unhappy_icon_sprite,(iptr)local_140,(iptr)this,local_78,local_88);
        }
        gfx_reset_zoom_scale();
      }
    }
    text_set_font((iptr)&this[7].field_270);
    gfx_set_zoom_scale(*(int *)(this[7].pad_15c + 0x3c) * 4 - 8);
    text_clear();
    text_append_label(0x1c2);
    text_set_colors(0x7c,0x39,1,1);
    uVar5 = rect_width((iptr)&this[7].field_220);
    uVar1 = this[7].field_22c;
    iVar2 = city_window_scale((C_004083b0_4 *)this,0xe);
    gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),this[7].field_220,uVar1 - iVar2,uVar5);
    text_set_colors(0x29,10,1,1);
    local_40 = (uint)(*(int *)(this[7].pad_15c + 0x3c) == 3);
    local_f0 = (int)cities[*(int *)(this[7].pad_15c + 4)].size * (uint)cosmic.food_per_citizen +
               city_settlers_supported * settler_food_cost;
    local_48 = city_yield_totals;
    local_c = city_yield_totals - local_f0;
    local_ec = local_f0;
    if (local_f0 <= city_yield_totals) {
      local_ec = city_yield_totals;
    }
    local_98 = local_f0;
    if ((int)local_c < 0) {
      local_98 = city_yield_totals;
    }
    local_38 = local_f0;
    iVar2 = city_window_scale((C_004083b0_4 *)this,0xe2);
    local_2c = city_window_scale((C_004083b0_4 *)this,2);
    local_2c = iVar2 - local_2c;
    local_c8 = city_window_scale((C_004083b0_4 *)this,0xe);
    local_c8++;
    if ((((int)local_c < 0) && (local_48 != 0)) || ((0 < (int)local_c && (local_f0 != 0)))) {
      iVar2 = city_window_scale((C_004083b0_4 *)this,4);
      local_2c = (local_2c - iVar2) - local_c8;
      local_ec--;
    }
    local_70 = ui_calc_item_spacing(local_ec,local_c8,local_2c,(iptr)&local_30,0);
    while (local_30 < local_ec) {
      local_ec--;
      if (local_48 < local_38) {
        local_38--;
      }
      else if (local_38 == local_48) {
        local_48--;
        local_38--;
        local_98--;
      }
      else {
        local_48--;
        local_98--;
      }
    }
    if ((local_c == 0) || (local_48 != 0)) {
      if (local_c == 0) {
        local_68 = 0;
      }
      else {
        if ((int)local_c < 1) {
          local_1f4 = ~local_c + 1;
        }
        else {
          local_1f4 = local_c;
        }
        iVar2 = city_window_scale((C_004083b0_4 *)this,2);
        iVar3 = city_window_scale((C_004083b0_4 *)this,1);
        local_68 = iVar2 + iVar3 + (local_1f4 - 1) * local_70 + local_c8;
      }
    }
    else {
      local_68 = city_window_scale((C_004083b0_4 *)this,0xe2);
    }
    local_f4 = city_window_scale((C_004083b0_4 *)this,0xe2);
    local_f4 -= local_68;
    local_10 = city_window_scale((C_004083b0_4 *)this,0xcd);
    local_10 = local_90 + local_10;
    local_a4 = local_f4 + local_10;
    iVar2 = city_window_scale((C_004083b0_4 *)this,0xe);
    iVar3 = city_window_scale((C_004083b0_4 *)this,2);
    *(int *)(this[7].pad_15c + 0x28) = iVar2 + iVar3;
    y2 = city_window_scale((C_004083b0_4 *)this,0xe);
    y2 = local_a0 + y2;
    if (*(int *)(this[7].pad_15c + 0x3c) == 3) {
      y2--;
    }
    if ((int)local_c < 0) {
      local_f4 += local_68;
      local_68 = 0;
    }
    if (local_f4 != 0) {
      gfx_target_fill_rect(local_10,y2,local_f4,*(i32 *)(this[7].pad_15c + 0x28),0x2d);
    }
    if (local_68 != 0) {
      uVar9 = 0x30;
      uVar5 = *(i32 *)(this[7].pad_15c + 0x28);
      iVar2 = city_window_scale((C_004083b0_4 *)this,6);
      gfx_target_fill_rect(local_a4,y2,local_68 + iVar2,uVar5,uVar9);
    }
    iVar2 = city_window_scale((C_004083b0_4 *)this,1);
    y2 = y2 + local_40 + iVar2;
    if (0 < local_98) {
      x2 = city_window_scale((C_004083b0_4 *)this,1);
      x2 = local_10 + x2;
      for (local_3c = 0; local_3c < local_98; local_3c++) {
        sprite_draw
                  ((Sprite *)&resource_icon_sprites,(iptr)local_150,(iptr)this,x2,y2);
        x2 += local_70;
      }
    }
    if (local_c != 0) {
      x2 = local_a4;
      if (local_98 < 1) {
        iVar2 = city_window_scale((C_004083b0_4 *)this,1);
        x2 += iVar2;
      }
      else {
        iVar2 = city_window_scale((C_004083b0_4 *)this,4);
        x2 += (iVar2 >> 1);
      }
      local_3c = 0;
      while( true ) {
        if ((int)local_c < 1) {
          local_1f8 = ~local_c + 1;
        }
        else {
          local_1f8 = local_c;
        }
        if ((int)local_1f8 <= local_3c) break;
        sprite_draw
                  ((Sprite *)(&resource_shortage_icon_sprites + (uint)(0 < (int)local_c) * 0x3c),
                   (iptr)local_160,(iptr)this,x2,y2);
        x2 += local_70;
        local_3c++;
      }
    }
    local_84 = city_window_scale((C_004083b0_4 *)this,0xcd);
    local_84 = local_90 + local_84;
    iVar2 = city_window_scale((C_004083b0_4 *)this,0xe2);
    local_60 = local_84 + iVar2 - 1;
    iVar2 = city_window_scale((C_004083b0_4 *)this,0xe);
    iVar2 = local_a0 + iVar2;
    y2 = city_window_scale((C_004083b0_4 *)this,0xe);
    y2 = iVar2 - y2;
    text_clear();
    text_append_label(0x40);
    text_set_colors(0x2a,10,1,1);
    text_append_colon();
    text_append_int(city_food_routes_out + local_98);
    if (city_food_routes_in != city_food_routes_out) {
      text_append_space();
      text_append_lparen();
      text_append_int(city_food_routes_in - city_food_routes_out);
      text_append_space();
      text_append_label(0xa9);
      text_append_rparen();
    }
    gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_84,y2);
    text_clear();
    if ((int)local_c < 0) {
      text_append_label(0x4a);
      text_set_colors(0xb,0x1d,1,1);
    }
    else {
      text_append_label(0x41);
      text_set_colors(0x2e,10,1,1);
    }
    text_append_colon();
    if ((int)local_c < 1) {
      local_1fc = ~local_c + 1;
    }
    else {
      local_1fc = local_c;
    }
    text_append_int(local_1fc);
    gfx_draw_text_right(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_60,y2,0);
    local_b8 = city_shield_support;
    local_48 = city_total_shields + city_shield_waste;
    local_c = city_total_shields - city_shield_support;
    local_54 = city_shield_support;
    if (city_shield_support <= local_48) {
      local_54 = local_48;
    }
    local_28 = local_48;
    if (-1 < (int)local_c) {
      local_28 = city_shield_support;
    }
    iVar2 = city_window_scale((C_004083b0_4 *)this,0xe2);
    local_2c = city_window_scale((C_004083b0_4 *)this,2);
    local_2c = iVar2 - local_2c;
    local_c8 = city_window_scale((C_004083b0_4 *)this,0xe);
    local_c8++;
    if ((((int)local_c < 0) && (local_48 != 0)) || ((0 < (int)local_c && (city_shield_support != 0)))) {
      iVar2 = city_window_scale((C_004083b0_4 *)this,4);
      local_2c = (local_2c - iVar2) - local_c8;
      local_54--;
    }
    if (city_shield_waste != 0) {
      iVar2 = city_window_scale((C_004083b0_4 *)this,4);
      local_2c = (local_2c - iVar2) - local_c8;
      local_54--;
    }
    local_70 = ui_calc_item_spacing(local_54,local_c8,local_2c,(iptr)&local_d4,0);
    while (local_d4 < local_54) {
      local_54--;
      if (local_48 - city_shield_waste < local_b8) {
        local_b8--;
      }
      else {
        if (local_48 == city_shield_waste) break;
        if (local_48 - city_shield_waste == local_b8) {
          local_48--;
          local_b8--;
          local_28--;
        }
        else {
          local_48--;
          local_28--;
        }
      }
    }
    local_d8 = 0;
    if (city_shield_waste != 0) {
      local_d8 = (city_shield_waste - 1) * local_70 + local_c8;
      if (local_c != 0) {
        iVar2 = city_window_scale((C_004083b0_4 *)this,4);
        local_d8 += (iVar2 >> 1);
      }
      if (local_48 != city_shield_waste) {
        iVar2 = city_window_scale((C_004083b0_4 *)this,4);
        local_d8 += (iVar2 >> 1);
      }
    }
    if ((local_c == 0) || (local_48 != 0)) {
      if (local_c == 0) {
        local_68 = 0;
      }
      else {
        if ((int)local_c < 1) {
          local_200 = ~local_c + 1;
        }
        else {
          local_200 = local_c;
        }
        iVar2 = city_window_scale((C_004083b0_4 *)this,2);
        iVar3 = city_window_scale((C_004083b0_4 *)this,1);
        local_68 = iVar2 + iVar3 + (local_200 - 1) * local_70 + local_c8;
      }
    }
    else {
      local_68 = city_window_scale((C_004083b0_4 *)this,0xe2);
    }
    local_f4 = city_window_scale((C_004083b0_4 *)this,0xe2);
    local_f4 -= (local_d8 + local_68);
    if (local_d8 != 0) {
      if (city_shield_support == 0) {
        local_f4 = 0;
      }
      else {
        iVar2 = city_window_scale((C_004083b0_4 *)this,2);
        iVar3 = city_window_scale((C_004083b0_4 *)this,1);
        local_f4 = iVar2 + iVar3 + (city_shield_support - 1) * local_70 + local_c8;
      }
      local_d8 = city_window_scale((C_004083b0_4 *)this,0xe2);
      local_d8 -= (local_68 + local_f4);
    }
    local_10 = city_window_scale((C_004083b0_4 *)this,0xcd);
    local_10 = local_90 + local_10;
    local_34 = local_f4 + local_10;
    local_a4 = local_d8 + local_34;
    if (local_d8 != 0) {
      local_bc = ((local_d8 >> 1) + local_34) - ((city_shield_waste - 1) * local_70 + local_c8 >> 1);
    }
    iVar2 = city_window_scale((C_004083b0_4 *)this,0xe);
    iVar3 = city_window_scale((C_004083b0_4 *)this,2);
    *(int *)(this[7].pad_15c + 0x28) = iVar2 + iVar3;
    y2 = city_window_scale((C_004083b0_4 *)this,0x78);
    y2 = local_a0 + y2;
    if (*(int *)(this[7].pad_15c + 0x3c) == 3) {
      y2--;
    }
    if ((int)local_c < 0) {
      local_f4 += local_68;
      local_68 = 0;
    }
    if (local_f4 != 0) {
      gfx_target_fill_rect(local_10,y2,local_f4,*(i32 *)(this[7].pad_15c + 0x28),0x54);
    }
    if (local_d8 != 0) {
      gfx_target_fill_rect(local_34,y2,local_d8,*(i32 *)(this[7].pad_15c + 0x28),0xb);
    }
    if (local_68 != 0) {
      uVar9 = 0x5c;
      uVar5 = *(i32 *)(this[7].pad_15c + 0x28);
      iVar2 = city_window_scale((C_004083b0_4 *)this,6);
      gfx_target_fill_rect(local_a4,y2,local_68 + iVar2,uVar5,uVar9);
    }
    iVar2 = city_window_scale((C_004083b0_4 *)this,1);
    y2 = y2 + local_40 + iVar2;
    if (0 < local_28) {
      x2 = city_window_scale((C_004083b0_4 *)this,1);
      x2 = local_10 + x2;
      for (local_3c = 0; local_3c < local_28; local_3c++) {
        sprite_draw
                  ((Sprite *)&shield_icon_sprite,(iptr)local_170,(iptr)this,x2,y2);
        x2 += local_70;
      }
    }
    if (0 < city_shield_waste) {
      x2 = city_window_scale((C_004083b0_4 *)this,2);
      x2 = local_bc + x2;
      for (local_3c = 0; local_3c < city_shield_waste; local_3c++) {
        sprite_draw
                  ((Sprite *)&shield_shortage_icon_sprite,(iptr)local_180,(iptr)this,x2,y2);
        x2 += local_70;
      }
    }
    if (local_c != 0) {
      x2 = local_a4;
      if (local_28 < 1) {
        iVar2 = city_window_scale((C_004083b0_4 *)this,1);
        x2 += iVar2;
      }
      else {
        iVar2 = city_window_scale((C_004083b0_4 *)this,4);
        x2 += (iVar2 >> 1);
      }
      local_3c = 0;
      while( true ) {
        if ((int)local_c < 1) {
          local_204 = ~local_c + 1;
        }
        else {
          local_204 = local_c;
        }
        if ((int)local_204 <= local_3c) break;
        if (cities[*(int *)(this[7].pad_15c + 4)].building == -0x26) {
          sprite_draw
                    ((Sprite *)&gold_coin_icon_sprite,(iptr)local_190,(iptr)this,x2,y2);
        }
        else {
          sprite_draw
                    ((Sprite *)(&shield_shortage_icon_sprite + (uint)(0 < (int)local_c) * 0x3c),
                     (iptr)local_1a0,(iptr)this,x2,y2);
        }
        x2 += local_70;
        local_3c++;
      }
    }
    local_84 = city_window_scale((C_004083b0_4 *)this,0xcd);
    local_84 = local_90 + local_84;
    iVar2 = city_window_scale((C_004083b0_4 *)this,0xe2);
    local_60 = local_84 + iVar2 - 1;
    iVar2 = city_window_scale((C_004083b0_4 *)this,0xe);
    iVar3 = city_window_scale((C_004083b0_4 *)this,2);
    iVar4 = city_window_scale((C_004083b0_4 *)this,0x78);
    iVar6 = city_window_scale((C_004083b0_4 *)this,0xffffffff);
    y2 = iVar2 + iVar3 + iVar4 + iVar6 + local_a0;
    text_clear();
    text_append_label(0xcc);
    text_append_colon();
    iVar2 = city_shield_support;
    if (local_48 <= city_shield_support) {
      iVar2 = local_48;
    }
    text_append_int(iVar2);
    text_set_colors(0x54,10,1,1);
    gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_84,y2);
    if (city_shield_waste != 0) {
      text_clear();
      text_append_label(0x43);
      text_append_colon();
      text_append_int(city_shield_waste);
      text_set_colors(0xb,0x1d,1,1);
      uVar5 = city_window_scale((C_004083b0_4 *)this,0xe2);
      gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_84,y2,uVar5);
    }
    text_clear();
    if ((int)local_c < 0) {
      text_append_label(0x4b);
      text_set_colors(0xb,0x1d,1,1);
    }
    else {
      text_append_label(0x44);
      text_set_colors(0x5c,10,1,1);
    }
    text_append_colon();
    if ((int)local_c < 1) {
      local_208 = ~local_c + 1;
    }
    else {
      local_208 = local_c;
    }
    text_append_int(local_208);
    gfx_draw_text_right(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_60,y2,0);
    local_48 = city_total_trade;
    local_54 = city_total_trade;
    iVar2 = city_window_scale((C_004083b0_4 *)this,0xe2);
    local_2c = city_window_scale((C_004083b0_4 *)this,2);
    local_2c = iVar2 - local_2c;
    local_c8 = city_window_scale((C_004083b0_4 *)this,0xe);
    local_c8++;
    if (city_trade_corruption != 0) {
      iVar2 = city_window_scale((C_004083b0_4 *)this,4);
      local_2c = (local_2c - iVar2) - local_c8;
      local_54--;
    }
    local_70 = ui_calc_item_spacing(local_54,local_c8,local_2c,(iptr)&local_d4,0);
    for (; local_d4 < local_54; local_54--) {
      local_48--;
    }
    local_68 = 0;
    if (city_trade_corruption != 0) {
      if ((int)city_trade_corruption < 1) {
        local_20c = ~city_trade_corruption + 1;
      }
      else {
        local_20c = city_trade_corruption;
      }
      iVar2 = city_window_scale((C_004083b0_4 *)this,2);
      iVar3 = city_window_scale((C_004083b0_4 *)this,1);
      local_68 = iVar2 + iVar3 + (local_20c - 1) * local_70 + local_c8;
    }
    local_f4 = city_window_scale((C_004083b0_4 *)this,0xe2);
    local_f4 -= local_68;
    local_10 = city_window_scale((C_004083b0_4 *)this,0xcd);
    local_10 = local_90 + local_10;
    local_a4 = local_f4 + local_10;
    iVar2 = city_window_scale((C_004083b0_4 *)this,0xe);
    iVar3 = city_window_scale((C_004083b0_4 *)this,2);
    *(int *)(this[7].pad_15c + 0x28) = iVar2 + iVar3;
    y2 = city_window_scale((C_004083b0_4 *)this,0x37);
    y2 = local_a0 + y2;
    if ((int)local_c < 0) {
      local_f4 += local_68;
      local_68 = 0;
    }
    if (local_f4 != 0) {
      gfx_target_fill_rect(local_10,y2,local_f4,*(i32 *)(this[7].pad_15c + 0x28),0x76);
    }
    if (local_68 != 0) {
      gfx_target_fill_rect(local_a4,y2,local_68,*(i32 *)(this[7].pad_15c + 0x28),0x79);
    }
    iVar2 = city_window_scale((C_004083b0_4 *)this,1);
    y2 = y2 + local_40 + iVar2;
    if (0 < (int)(city_total_trade - city_trade_corruption)) {
      x2 = local_10 + 1;
      for (local_3c = 0; local_3c < (int)(city_total_trade - city_trade_corruption); local_3c++) {
        sprite_draw
                  ((Sprite *)&trade_icon_sprite,(iptr)local_1b0,(iptr)this,x2,y2);
        x2 += local_70;
      }
    }
    if (city_trade_corruption != 0) {
      x2 = local_a4;
      iVar2 = city_window_scale((C_004083b0_4 *)this,4);
      x2 += (iVar2 >> 1);
      for (local_3c = 0; local_3c < (int)city_trade_corruption; local_3c++) {
        sprite_draw
                  ((Sprite *)&trade_corruption_icon_sprite,(iptr)local_1c0,(iptr)this,x2,y2);
        x2 += local_70;
      }
    }
    local_84 = city_window_scale((C_004083b0_4 *)this,0xcd);
    local_84 = local_90 + local_84;
    iVar2 = city_window_scale((C_004083b0_4 *)this,0xe2);
    local_60 = local_84 + iVar2 - 1;
    iVar2 = city_window_scale((C_004083b0_4 *)this,0x37);
    iVar2 = local_a0 + iVar2;
    y2 = city_window_scale((C_004083b0_4 *)this,0xe);
    y2 = iVar2 - y2;
    text_clear();
    text_append_label(0x45);
    text_set_colors(0x76,10,1,1);
    text_append_colon();
    text_append_int(city_total_trade - city_trade_corruption);
    local_d0 = gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_84,y2);
    if ((civs[cities[*(int *)(this[7].pad_15c + 4)].owner].government == 4) &&
       (city_building_content != 0)) {
      iVar2 = city_window_scale((C_004083b0_4 *)this,4);
      local_d0 += iVar2;
      text_clear();
      text_append_label(0x5d);
      text_append_colon();
      text_append(ADDR(0x630d90, ((u8 *)&g.d_00630d90)));
      text_append_int(city_building_content);
      text_set_colors(0x79,10,1,1);
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_d0,y2);
    }
    text_clear();
    text_append_label(0x46);
    text_set_colors(0x79,10,1,1);
    text_append_colon();
    text_append_int(city_trade_corruption);
    gfx_draw_text_right(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_60,y2,0);
    local_48 = city_total_trade;
    local_b0 = city_tax_total;
    local_64 = city_lux_total;
    local_44 = city_science_total;
    local_54 = city_science_total + city_lux_total + city_tax_total;
    local_24 = (uint)(0 < city_science_total) + (uint)(0 < city_lux_total) + (uint)(0 < city_tax_total);
    iVar2 = city_window_scale((C_004083b0_4 *)this,0xe2);
    local_2c = city_window_scale((C_004083b0_4 *)this,2);
    local_2c = iVar2 - local_2c;
    local_c8 = city_window_scale((C_004083b0_4 *)this,0xe);
    local_c8++;
    for (; 1 < local_24; local_24--) {
      iVar2 = city_window_scale((C_004083b0_4 *)this,4);
      local_2c -= (local_c8 + iVar2);
      local_54--;
    }
    local_70 = ui_calc_item_spacing(local_54,local_c8,local_2c,(iptr)&local_d4,0);
    for (; local_d4 < local_54; local_d4++) {
      if ((local_64 < local_b0) && (local_44 < local_b0)) {
        local_b0--;
      }
      else if (local_64 < local_44) {
        local_44--;
      }
      else {
        local_64--;
      }
    }
    local_f4 = 0;
    local_10 = city_window_scale((C_004083b0_4 *)this,0xcd);
    local_10 = local_90 + local_10;
    if (local_b0 != 0) {
      iVar2 = city_window_scale((C_004083b0_4 *)this,1);
      local_f4 = iVar2 + (local_b0 - 1) * local_70 + local_c8;
    }
    local_68 = 0;
    if (local_44 != 0) {
      iVar2 = city_window_scale((C_004083b0_4 *)this,1);
      local_68 = iVar2 + (local_44 - 1) * local_70 + local_c8;
    }
    iVar2 = city_window_scale((C_004083b0_4 *)this,0xe2);
    iVar3 = city_window_scale((C_004083b0_4 *)this,0xcd);
    local_a4 = (iVar2 + iVar3 + local_90) - local_68;
    local_d8 = city_window_scale((C_004083b0_4 *)this,0xe2);
    local_d8 -= (local_68 + local_f4);
    local_34 = city_window_scale((C_004083b0_4 *)this,0xcd);
    local_34 = local_90 + local_34;
    if (local_f4 != 0) {
      iVar2 = city_window_scale((C_004083b0_4 *)this,4);
      local_d8 -= iVar2;
      iVar2 = city_window_scale((C_004083b0_4 *)this,4);
      local_34 = local_34 + local_f4 + iVar2;
    }
    if (local_68 != 0) {
      iVar2 = city_window_scale((C_004083b0_4 *)this,4);
      local_d8 -= iVar2;
    }
    local_bc = local_34;
    local_34 += (local_d8 >> 1);
    if (local_64 != 0) {
      local_34 -= ((local_64 - 1) * local_70 + local_c8 >> 1);
    }
    local_ac = 0;
    if ((local_64 == 0) || (local_b0 != 0)) {
      if ((local_64 != 0) && (local_44 == 0)) {
        local_ac = 2;
        iVar2 = city_window_scale((C_004083b0_4 *)this,1);
        local_24 = iVar2 + (local_64 - 1) * local_70 + local_c8;
        iVar2 = city_window_scale((C_004083b0_4 *)this,0xe2);
        iVar3 = city_window_scale((C_004083b0_4 *)this,0xcd);
        local_34 = (iVar2 + iVar3 + local_90) - local_24;
      }
    }
    else {
      local_ac = 1;
      local_34 = local_10;
    }
    iVar2 = city_window_scale((C_004083b0_4 *)this,0xe);
    iVar3 = city_window_scale((C_004083b0_4 *)this,2);
    *(int *)(this[7].pad_15c + 0x28) = iVar2 + iVar3;
    y2 = city_window_scale((C_004083b0_4 *)this,0x4f);
    y2 = local_a0 + y2;
    uVar10 = 0x79;
    uVar5 = *(i32 *)(this[7].pad_15c + 0x28);
    uVar9 = city_window_scale((C_004083b0_4 *)this,0xe2);
    gfx_target_fill_rect(local_10,y2,uVar9,uVar5,uVar10);
    iVar2 = city_window_scale((C_004083b0_4 *)this,1);
    y2 = y2 + local_40 + iVar2;
    if (0 < local_b0) {
      x2 = city_window_scale((C_004083b0_4 *)this,1);
      x2 = local_10 + x2;
      for (local_3c = 0; local_3c < local_b0; local_3c++) {
        sprite_draw
                  ((Sprite *)&gold_coin_icon_sprite,(iptr)local_1d0,(iptr)this,x2,y2);
        x2 += local_70;
      }
    }
    if (local_64 != 0) {
      x2 = local_34;
      for (local_3c = 0; local_3c < local_64; local_3c++) {
        sprite_draw
                  ((Sprite *)&tax_rate_icon_sprites,(iptr)local_1e0,(iptr)this,x2,y2);
        x2 += local_70;
      }
    }
    if (local_44 != 0) {
      x2 = local_a4;
      for (local_3c = 0; local_3c < local_44; local_3c++) {
        sprite_draw
                  ((Sprite *)&science_icon_sprite,(iptr)local_1f0,(iptr)this,x2,y2);
        x2 += local_70;
      }
    }
    local_84 = city_window_scale((C_004083b0_4 *)this,0xcd);
    local_84 = local_90 + local_84;
    iVar2 = city_window_scale((C_004083b0_4 *)this,0xe2);
    local_60 = local_84 + iVar2 - 1;
    iVar2 = city_window_scale((C_004083b0_4 *)this,0x4f);
    iVar3 = city_window_scale((C_004083b0_4 *)this,0xe);
    iVar4 = city_window_scale((C_004083b0_4 *)this,2);
    iVar6 = city_window_scale((C_004083b0_4 *)this,0);
    y2 = iVar2 + iVar3 + iVar4 + iVar6 + local_a0;
    civ = (iptr)cities[*(int *)(this[7].pad_15c + 4)].owner;
    text_clear();
    text_append_int((uint)civs[civ].tax_rate * 10);
    text_append_percent();
    text_append_space();
    text_append_label(0x47);
    text_append_colon();
    text_append_int(city_tax_total);
    text_set_colors(0x76,10,1,1);
    if (local_ac == 1) {
      uVar5 = city_window_scale((C_004083b0_4 *)this,0xe2);
      gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_84,y2,uVar5);
    }
    else {
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_84,y2);
    }
    text_clear();
    text_append_int((10 - ((uint)civs[civ].tax_rate + (uint)civs[civ].science_rate)) *
                       10);
    text_append_percent();
    text_append_space();
    text_append_label(0x48);
    text_append_colon();
    text_append_int(city_lux_total);
    text_set_colors(0x29,10,1,1);
    if (local_ac == 1) {
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_84,y2);
    }
    else if (local_ac == 2) {
      gfx_draw_text_right(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_60,y2,0);
    }
    else {
      uVar5 = city_window_scale((C_004083b0_4 *)this,0xe2);
      gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_84,y2,uVar5);
    }
    text_clear();
    text_append_int((uint)civs[civ].science_rate * 10);
    text_append_percent();
    text_append_space();
    text_append_label(0x49);
    text_append_colon();
    text_append_int(city_science_total);
    text_set_colors(0x5e,10,1,1);
    if (local_ac == 2) {
      uVar5 = city_window_scale((C_004083b0_4 *)this,0xe2);
      gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_84,y2,uVar5);
    }
    else {
      gfx_draw_text_right(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_60,y2,0);
    }
    gfx_reset_zoom_scale();
    if (param_1 != 0) {
      wnd_blit_surface_rect((DibSurface *)this,(iptr)(this[7].pad_15c + 0x54));
    }
  }
  return;
}
#undef city_building_content
#undef city_science_total
#undef city_shield_support
#undef city_tax_total
#undef city_tile_yields
#undef city_total_shields
#undef city_total_trade
#undef city_trade_corruption
#undef city_yield_totals
#undef settler_food_cost
#undef local_20c
#undef local_208
#undef local_204
#undef local_200
#undef local_1fc
#undef local_1f8
#undef local_1f4
#undef local_1f0
#undef local_1e0
#undef local_1d0
#undef local_1c0
#undef local_1b0
#undef local_1a0
#undef local_190
#undef local_180
#undef local_170
#undef local_160
#undef local_150
#undef local_140
#undef local_130
#undef local_120
#undef local_110
#undef local_100
#undef x2
#undef civ
#undef local_f4
#undef local_f0
#undef local_ec
#undef local_e8
#undef local_e4
#undef local_e0
#undef unit
#undef local_d8
#undef local_d4
#undef local_d0
#undef local_cc
#undef local_c8
#undef local_c4
#undef city
#undef local_bc
#undef local_b8
#undef local_b4
#undef local_b0
#undef local_ac
#undef local_a8
#undef local_a4
#undef local_a0
#undef local_9c
#undef local_98
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
#undef local_60
#undef local_5c
#undef local_58
#undef local_54
#undef local_50
#undef y2
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
#undef local_10
#undef local_c
#undef local_8

/* 00504c05 auto */
#define city_food_box_rows (*(int *)((u8 *)&g.d_006a6560))
#define local_2c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(12)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(28)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_c (*(int *)(frame_ + FRAME_OFF(36)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(40)))
void __thiscall city_window_draw_food_box(C_004083b0_12c *this,int param_1)

{
  i32 uVar1;
  iptr iVar2;
  iptr iVar3;
  i32 uVar4;
  i32 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((((*(int *)(this[0x12].pad_48 + 0x44) == 0) && (*(int *)(this[0x12].pad_48 + 0x40) == 0)) &&
      (*(int *)(this[0x12].pad_48 + 0x48) == 0)) && (-1 < *(int *)(this[0x12].pad_48 + 0x3c))) {
    city_window_begin_draw(this,(iptr)(this[0x12].pad_48 + 0x9c));
    text_set_colors(0x2c,10,1,1);
    uVar1 = rect_width((iptr)(this[0x12].pad_48 + 0x9c));
    uVar4 = *(i32 *)(this[0x12].pad_48 + 0xa0);
    uVar5 = *(i32 *)(this[0x12].pad_48 + 0x9c);
    iVar2 = label_string(*(i32 *)(label_string_ids + 0xac));
    gfx_draw_text_centered(iVar2,uVar5,uVar4,uVar1);
    iVar2 = city_window_scale((C_004083b0_4 *)this,0xb7);
    iVar3 = city_window_scale((C_004083b0_4 *)this,0x93);
    uVar4 = city_window_scale((C_004083b0_4 *)this,0xf);
    uVar5 = city_window_scale((C_004083b0_4 *)this,6);
    rect_set_xywh((iptr)&local_14,uVar5,uVar4,iVar2,iVar3);
    rect_offset((iptr)&local_14,*(i32 *)(this[0x12].pad_48 + 0x9c),
                       *(i32 *)(this[0x12].pad_48 + 0xa0));
    uVar4 = city_window_scale((C_004083b0_4 *)this,3);
    uVar5 = city_window_scale((C_004083b0_4 *)this,3);
    rect_deflate((iptr)&local_14,uVar5,uVar4);
    iVar3 = 0;
    iVar2 = 0;
    uVar4 = rect_width((iptr)&local_14);
    uVar5 = city_window_scale((C_004083b0_4 *)this,0x11);
    iVar6 = ui_calc_item_spacing(cities[*(int *)(this[0x12].pad_48 + 0x3c)].size + 1,uVar5,uVar4,iVar2
                               ,iVar3);
    iVar3 = 0;
    iVar2 = 0;
    uVar4 = rect_height((iptr)&local_14);
    uVar5 = city_window_scale((C_004083b0_4 *)this,0xe);
    iVar7 = ui_calc_item_spacing(city_food_box_rows,uVar5,uVar4,iVar2,iVar3);
    iVar6 = (cities[*(int *)(this[0x12].pad_48 + 0x3c)].size + 1) * iVar6;
    iVar8 = rect_width((iptr)&local_14);
    if (iVar6 < iVar8) {
      uVar4 = 0;
      iVar8 = rect_width((iptr)&local_14);
      rect_deflate((iptr)&local_14,iVar8 - iVar6 >> 1,uVar4);
    }
    iVar6 = iVar7 * city_food_box_rows;
    iVar8 = rect_height((iptr)&local_14);
    if (iVar6 < iVar8) {
      iVar8 = rect_height((iptr)&local_14);
      local_8 -= (iVar8 - iVar6);
    }
    rect_inflate((iptr)&local_14,3,3);
    city_draw_bevel_rect((iptr)&local_14,0x2c,0x39);
    rect_deflate((iptr)&local_14,1,1);
    rect_deflate((iptr)&local_14,2,2);
    iVar6 = local_14;
    local_1c = 0;
    local_24 = (int)cities[*(int *)(this[0x12].pad_48 + 0x3c)].food_box;
    local_2c = local_10;
    gfx_set_zoom_scale(*(int *)(this[0x12].pad_48 + 0x74) * 4 - 8);
    for (; (0 < local_24 && (local_1c < city_food_box_rows)); local_1c++) {
      iVar8 = cities[*(int *)(this[0x12].pad_48 + 0x3c)].size + 1;
      if (local_24 <= iVar8) {
        iVar8 = local_24;
      }
      uVar1 = 1;
      uVar4 = rect_width((iptr)&local_14);
      uVar5 = city_window_scale((C_004083b0_4 *)this,0x11);
      city_window_draw_icon_row(ADDR(0x644f3c, ((u8 *)&g.d_00644f3c)),iVar6,local_2c,iVar8,
                         cities[*(int *)(this[0x12].pad_48 + 0x3c)].size + 1,uVar5,uVar4,uVar1);
      local_24 -= iVar8;
      local_2c += iVar7;
    }
    gfx_reset_zoom_scale();
    iVar6 = city_has_improvement(*(iptr *)(this[0x12].pad_48 + 0x3c),3);
    if ((iVar6 != 0) ||
       (iVar6 = civ_has_wonder((int)cities[*(int *)(this[0x12].pad_48 + 0x3c)].owner,0),
       iVar6 != 0)) {
      iVar8 = city_food_box_rows >> 1;
      iVar6 = city_window_scale((C_004083b0_4 *)this,1);
      iVar7 = local_10 + (iVar8 * iVar7 - iVar6);
      uVar4 = 0x2a;
      iVar6 = city_window_scale((C_004083b0_4 *)this,2);
      iVar6 = (local_c - 1) - iVar6;
      iVar8 = city_window_scale((C_004083b0_4 *)this,2);
      city_draw_hline(local_14 + iVar8,iVar6,iVar7,uVar4);
    }
    if (param_1 != 0) {
      wnd_blit_surface_rect((DibSurface *)this,(iptr)(this[0x12].pad_48 + 0x9c));
    }
  }
  return;
}
#undef city_food_box_rows
#undef local_2c
#undef local_24
#undef local_1c
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 0050503e auto */
#define city_shield_rows (*(uint *)((u8 *)&g.d_006a657c))
#define local_6c (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_5c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_58 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_54 (*(int *)(frame_ + FRAME_OFF(28)))
#define local_50 (*(iptr *)(frame_ + FRAME_OFF(32)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(36)))
#define local_48 (*(i32 *)(frame_ + FRAME_OFF(40)))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(44)))
#define local_40 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_3c (*(iptr *)(frame_ + FRAME_OFF(52)))
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(56)))
#define local_34 (*(uint *)(frame_ + FRAME_OFF(60)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(64)))
#define local_2c (*(uint *)(frame_ + FRAME_OFF(68)))
#define local_28 (*(i32 *)(frame_ + FRAME_OFF(72)))
#define local_24 (*(uint *)(frame_ + FRAME_OFF(76)))
#define local_20 (*(uint *)(frame_ + FRAME_OFF(80)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(84)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(88)))
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(92)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(96)))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(100)))
#define local_8 (*(u32 *)(frame_ + FRAME_OFF(104)))
void __thiscall city_window_draw_production(FrameWindow *this,int param_1)

{
  int iVar1;
  int iVar2;
  i32 uVar3;
  iptr iVar4;
  int *piVar5;
  i32 uVar6;
  iptr iVar7;
  i32 uVar8;
  i8 frame_[FRAME_OFF(112)] __attribute__((aligned(8)));  /* original stack frame */
  
  improvement = -1;
  unit_type = -1;
  if ((((*(int *)(this[7].pad_15c + 0xc) == 0) && (*(int *)(this[7].pad_15c + 8) == 0)) &&
      (*(int *)(this[7].pad_15c + 0x10) == 0)) && (-1 < *(int *)(this[7].pad_15c + 4))) {
    city_window_begin_draw((C_004083b0_12c *)this,(iptr)(this[7].pad_1bc + 0x14));
    local_3c = city_window_scale((C_004083b0_4 *)this,0xb7);
    local_50 = city_window_scale((C_004083b0_4 *)this,0x92);
    local_14 = *(i32 *)(this[7].pad_1bc + 0x14);
    local_10 = *(int *)(this[7].pad_1bc + 0x18);
    local_c = *(i32 *)(this[7].pad_1bc + 0x1c);
    local_8 = this[7].field_1dc;
    iVar1 = city_window_scale((C_004083b0_4 *)this,0x28);
    local_8 = local_10 + iVar1;
    clickmap_remove_by_id((ClickMapRemoveView *)&this->field_2d8,5);
    hotspot_add_rect((ClickMap *)&this->field_2d8,0,5,(iptr)&local_14);
    if (cities[*(int *)(this[7].pad_15c + 4)].building < '\0') {
      if (cities[*(int *)(this[7].pad_15c + 4)].building < 1) {
        improvement = ~(int)cities[*(int *)(this[7].pad_15c + 4)].building + 1;
      }
      else {
        improvement = (iptr)cities[*(int *)(this[7].pad_15c + 4)].building;
      }
      local_34 = (uint)improvements[improvement].cost;
      text_set_colors(0x54,10,1,1);
      uVar8 = rect_width((iptr)(this[7].pad_1bc + 0x14));
      uVar3 = *(i32 *)(this[7].pad_1bc + 0x18);
      uVar6 = *(i32 *)(this[7].pad_1bc + 0x14);
      iVar4 = label_string(improvements[improvement].name);
      gfx_draw_text_centered(iVar4,uVar6,uVar3,uVar8);
      gfx_set_zoom_scale(*(int *)(this[7].pad_15c + 0x3c) * 4 - 8);
      iVar1 = city_window_scale((C_004083b0_4 *)this,0x10);
      iVar1 = *(int *)(this[7].pad_1bc + 0x18) + iVar1;
      iVar2 = city_window_scale((C_004083b0_4 *)this,0x50);
      sprite_draw
                ((Sprite *)(&improvement_icon_sprites + improvement * 0x3c),(iptr)local_6c,ADDR(0x6a91b8, ((u8 *)&g.d_006a91b8)),
                 *(int *)(this[7].pad_1bc + 0x14) + iVar2,iVar1);
      gfx_reset_zoom_scale();
    }
    else {
      unit_type = (iptr)cities[*(int *)(this[7].pad_15c + 4)].building;
      local_34 = (uint)(char)unit_types[unit_type].cost;
      unit = unit_make_dummy(unit_type,(int)cities[*(int *)(this[7].pad_15c + 4)].owner);
      local_48 = 0xffffffff;
      if (*(int *)(this[7].pad_15c + 0x3c) == 1) {
        local_48 = 0xfffffffb;
      }
      if (*(int *)(this[7].pad_15c + 0x3c) == 3) {
        local_48 = 1;
      }
      uVar6 = 0;
      uVar3 = local_48;
      iVar1 = city_window_scale((C_004083b0_4 *)this,1);
      iVar1 = *(int *)(this[7].pad_1bc + 0x18) + iVar1;
      iVar2 = city_window_scale((C_004083b0_4 *)this,0x49);
      gfx_draw_unit(ADDR(0x6a91b8, ((u8 *)&g.d_006a91b8)),unit,0,*(int *)(this[7].pad_1bc + 0x14) + iVar2,iVar1,uVar3,
                         uVar6);
    }
    if (cities[*(int *)(this[7].pad_15c + 4)].building != -0x26) {
      iVar4 = local_3c;
      iVar7 = local_50;
      uVar3 = city_window_scale((C_004083b0_4 *)this,0x28);
      uVar6 = city_window_scale((C_004083b0_4 *)this,6);
      rect_set_xywh((iptr)&local_14,uVar6,uVar3,iVar4,iVar7);
      rect_offset((iptr)&local_14,*(i32 *)(this[7].pad_1bc + 0x14),
                         *(i32 *)(this[7].pad_1bc + 0x18));
      uVar3 = city_window_scale((C_004083b0_4 *)this,3);
      uVar6 = city_window_scale((C_004083b0_4 *)this,3);
      rect_deflate((iptr)&local_14,uVar6,uVar3);
      iVar7 = 0;
      iVar4 = 0;
      uVar3 = rect_height((iptr)&local_14);
      uVar6 = city_window_scale((C_004083b0_4 *)this,0xe);
      local_5c = ui_calc_item_spacing(10,uVar6,uVar3,iVar4,iVar7);
      local_2c = local_34;
      if ((int)local_34 < 10) {
        local_2c = city_shield_rows;
        local_8 -= (10 - local_34) * local_5c;
      }
      iVar4 = 0;
      piVar5 = &local_58;
      uVar3 = rect_width((iptr)&local_14);
      uVar6 = city_window_scale((C_004083b0_4 *)this,0x11);
      local_54 = ui_calc_item_spacing(city_shield_rows,uVar6,uVar3,(iptr)piVar5,iVar4);
      local_18 = local_54 * city_shield_rows + local_58;
      local_40 = 0;
      iVar1 = rect_width((iptr)&local_14);
      if (local_18 < iVar1) {
        iVar1 = rect_width((iptr)&local_14);
        local_40 = iVar1 - local_18 >> 1;
      }
      rect_inflate((iptr)&local_14,3,3);
      city_draw_bevel_rect((iptr)&local_14,0x51,0x5d);
      rect_deflate((iptr)&local_14,1,1);
      rect_deflate((iptr)&local_14,local_40 + 2,2);
      local_1c = 0;
      local_24 = (uint)cities[*(int *)(this[7].pad_15c + 4)].shield_box;
      local_28 = local_14;
      local_30 = local_10;
      gfx_set_zoom_scale(*(int *)(this[7].pad_15c + 0x3c) * 4 - 8);
      for (; (0 < (int)local_24 && (local_1c < 10)); local_1c++) {
        local_20 = local_24;
        if ((int)local_2c <= (int)local_24) {
          local_20 = local_2c;
        }
        uVar8 = 1;
        uVar3 = rect_width((iptr)&local_14);
        uVar6 = city_window_scale((C_004083b0_4 *)this,0x11);
        city_window_draw_icon_row(ADDR(0x644fb4, ((u8 *)&g.d_00644fb4)),local_28,local_30,local_20,local_2c,uVar6,uVar3,uVar8);
        local_24 -= local_20;
        local_30 += local_5c;
      }
      gfx_reset_zoom_scale();
    }
    if (param_1 != 0) {
      wnd_blit_surface_rect((DibSurface *)this,(iptr)(this[7].pad_1bc + 0x14));
    }
  }
  return;
}
#undef city_shield_rows
#undef local_6c
#undef local_5c
#undef local_58
#undef local_54
#undef local_50
#undef unit
#undef local_48
#undef improvement
#undef local_40
#undef local_3c
#undef unit_type
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

/* 005055dd auto */
void __thiscall city_window_draw_button_area(C_004083b0_12c *this,int param_1)

{
  if ((((*(int *)(this[0x12].pad_48 + 0x44) == 0) && (*(int *)(this[0x12].pad_48 + 0x40) == 0)) &&
      (*(int *)(this[0x12].pad_48 + 0x48) == 0)) &&
     ((-1 < *(int *)(this[0x12].pad_48 + 0x3c) &&
      (city_window_begin_draw(this,(iptr)this[0x12].pad_104), param_1 != 0)))) {
    wnd_blit_surface_rect((DibSurface *)this,(iptr)this[0x12].pad_104);
  }
  return;
}

/* 00505666 auto */
#define settler_food_cost (*(int *)((u8 *)&g.d_006a6608))
#define local_c0 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_b0 (*(i8 (*)[16])(frame_ + FRAME_OFF(16)))
#define local_a0 (*(i8 (*)[16])(frame_ + FRAME_OFF(32)))
#define local_90 (*(i8 (*)[16])(frame_ + FRAME_OFF(48)))
#define local_80 (*(int *)(frame_ + FRAME_OFF(64)))
#define civ (*(iptr *)(frame_ + FRAME_OFF(68)))
#define local_78 (*(int *)(frame_ + FRAME_OFF(72)))
#define local_74 (*(int *)(frame_ + FRAME_OFF(76)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(80)))
#define local_6c (*(int *)(frame_ + FRAME_OFF(84)))
#define local_68 (*(int *)(frame_ + FRAME_OFF(88)))
#define local_64 (*(uint *)(frame_ + FRAME_OFF(92)))
#define local_60 (*(int *)(frame_ + FRAME_OFF(96)))
#define local_5c (*(int *)(frame_ + FRAME_OFF(100)))
#define local_58 (*(int *)(frame_ + FRAME_OFF(104)))
#define local_54 (*(u32 *)(frame_ + FRAME_OFF(108)))
#define local_50 (*(int *)(frame_ + FRAME_OFF(112)))
#define local_4c (*(u32 *)(frame_ + FRAME_OFF(116)))
#define local_48 (*(int *)(frame_ + FRAME_OFF(120)))
#define local_44 (*(int *)(frame_ + FRAME_OFF(124)))
#define local_40 (*(int *)(frame_ + FRAME_OFF(128)))
#define local_3c (*(int *)(frame_ + FRAME_OFF(132)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(136)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(140)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(144)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(148)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(152)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(156)))
#define local_20 (*(i32 *)(frame_ + FRAME_OFF(160)))
#define local_1c (*(iptr *)(frame_ + FRAME_OFF(164)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(168)))
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(172)))
void __thiscall city_window_draw_supported_units(FrameWindow *this,int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  i32 uVar4;
  iptr iVar5;
  iptr iVar6;
  iptr iVar7;
  i8 frame_[FRAME_OFF(192)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((((*(int *)(this[7].pad_15c + 0xc) == 0) && (*(int *)(this[7].pad_15c + 8) == 0)) &&
      (*(int *)(this[7].pad_15c + 0x10) == 0)) && (-1 < *(int *)(this[7].pad_15c + 4))) {
    city_window_begin_draw((C_004083b0_12c *)this,(iptr)&this[7].field_1f0);
    local_4c = this[7].field_1f0;
    local_54 = this[7].field_1f4;
    local_20 = 0xfffffffd;
    if (*(int *)(this[7].pad_15c + 0x3c) == 1) {
      local_20 = 0xfffffffa;
    }
    if (*(int *)(this[7].pad_15c + 0x3c) == 3) {
      local_20 = 0;
    }
    local_48 = gfx_zoom_scale(0x45,local_20);
    local_78 = gfx_zoom_scale(0x34,local_20);
    local_18 = city_window_scale((C_004083b0_4 *)this,0xc0);
    local_18 = local_18 / local_48;
    local_28 = city_window_scale((C_004083b0_4 *)this,0x4e);
    local_28 = local_28 / local_78;
    iVar1 = city_window_scale((C_004083b0_4 *)this,0xc0);
    iVar2 = local_48 * local_18;
    iVar3 = gfx_zoom_scale(5,local_20);
    local_5c = (iVar1 - iVar2) + iVar3 >> 1;
    iVar1 = city_window_scale((C_004083b0_4 *)this,0x4e);
    iVar2 = local_78 * local_28;
    iVar3 = gfx_zoom_scale(4,local_20);
    local_58 = (iVar1 - iVar2) + iVar3 >> 1;
    local_3c = gfx_zoom_scale(0x20,local_20);
    local_40 = 0;
    for (unit = 0; unit < game.num_units; unit++) {
      if ((units[unit].id != 0) &&
         ((uint)(byte)units[unit].home_city == *(uint *)(this[7].pad_15c + 4))) {
        local_40++;
      }
    }
    if (local_40 <= local_18) {
      iVar1 = city_window_scale((C_004083b0_4 *)this,0x4e);
      iVar2 = gfx_zoom_scale(0x30,local_20);
      local_58 = iVar1 - iVar2 >> 1;
      text_clear();
      text_append_label(0x1bf);
      text_set_colors(0x7c,0x12,1,1);
      uVar4 = rect_width((iptr)(this[7].pad_23c + 4));
      iVar1 = city_window_scale((C_004083b0_4 *)this,1);
      gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),*(i32 *)(this[7].pad_23c + 4),
                         *(int *)(this[7].pad_23c + 8) + iVar1,uVar4);
    }
    local_1c = gfx_zoom_scale(0x40,local_20);
    local_6c = local_5c + local_4c;
    local_74 = local_58 + local_54;
    local_34 = 0;
    local_60 = 0;
    civ = (iptr)cities[*(int *)(this[7].pad_15c + 4)].owner;
    local_64 = (uint)civs[civ].government;
    local_30 = 0;
    clickmap_remove_by_id((ClickMapRemoveView *)&this->field_2d8,6);
    for (unit = 0; unit < game.num_units; unit++) {
      if ((units[unit].id != 0) &&
         ((uint)(byte)units[unit].home_city == *(uint *)(this[7].pad_15c + 4))) {
        local_38 = local_3c + local_74;
        gfx_draw_unit((iptr)this,unit,4,local_6c,local_74,local_20,0);
        local_68 = 0;
        local_2c = 0;
        if (unit_types[units[unit].type].role == 5) {
          local_68 = settler_food_cost;
        }
        if ((units[unit].flags & 0x800) != 0) {
          local_68++;
        }
        if (((units[unit].flags & 0x400) != 0) && (4 < (int)local_64)) {
          iVar1 = civ_has_wonder(civ,0x15);
          if ((iVar1 == 0) &&
             (iVar1 = city_has_improvement(*(iptr *)(this[7].pad_15c + 4),0x21), iVar1 == 0)) {
            local_44 = 1;
          }
          else {
            local_44 = 0;
          }
          if (local_64 == 6) {
            local_44++;
          }
          else if ((local_44 != 0) && (local_30 == 0)) {
            local_44 = 0;
          }
          if (local_44 == 0) {
            local_44 = 1;
            local_2c = 2;
          }
          else {
            local_2c = 1;
          }
          local_68 += local_44;
          local_30++;
        }
        gfx_set_zoom_scale(*(int *)(this[7].pad_15c + 0x3c) * 4 - 8);
        iVar7 = 0;
        iVar6 = 0;
        iVar5 = local_1c;
        uVar4 = city_window_scale((C_004083b0_4 *)this,10);
        local_50 = ui_calc_item_spacing(local_68,uVar4,iVar5,iVar6,iVar7);
        local_80 = local_6c;
        if (unit_types[units[unit].type].role == 5) {
          for (local_24 = 0; local_24 < settler_food_cost; local_24++) {
            sprite_draw
                      ((Sprite *)&small_resource_icon_sprites,(iptr)local_90,(iptr)this,local_80,local_38);
            local_80 += local_50;
          }
        }
        if ((units[unit].flags & 0x800) != 0) {
          sprite_draw
                    ((Sprite *)&small_shield_icon_sprite,(iptr)local_a0,(iptr)this,local_80,local_38);
          local_80 += local_50;
        }
        if (local_2c != 0) {
          for (local_24 = 0; local_24 < local_44; local_24++) {
            if (local_2c == 1) {
              sprite_draw
                        ((Sprite *)&small_unhappy_icon_sprite,(iptr)local_b0,(iptr)this,local_80,local_38)
              ;
            }
            else {
              sprite_draw
                        ((Sprite *)&unhappy_suppressed_icon_sprite,(iptr)local_c0,(iptr)this,local_80,local_38)
              ;
            }
            local_80 += local_50;
          }
        }
        gfx_reset_zoom_scale();
        rect_set_xywh((iptr)local_14,local_6c,local_74,local_1c,local_1c);
        hotspot_add_rect((ClickMap *)&this->field_2d8,unit,6,(iptr)local_14);
        local_60++;
        local_6c += local_48;
        if (local_18 <= local_60) {
          local_60 = 0;
          local_6c = local_5c + local_4c;
          local_34++;
          local_74 += local_78;
          if (local_28 <= local_34) break;
        }
      }
    }
    if (param_1 != 0) {
      wnd_blit_surface_rect((DibSurface *)this,(iptr)&this[7].field_1f0);
    }
  }
  return;
}
#undef settler_food_cost
#undef local_c0
#undef local_b0
#undef local_a0
#undef local_90
#undef local_80
#undef civ
#undef local_78
#undef local_74
#undef unit
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

/* 00505d3d auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define local_14 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
void __cdecl city_window_sell_improvement(i32 param_1)

{
  short sVar1;
  iptr city3;
  iptr city4;
  iptr city2;
  int city;
  int iVar6;
  i32 uVar7;
  iptr iVar7;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 0;
  improvement = -1;
  city3 = citywnd_get_city((C_004083b0_4 *)&city_window);
  if ((cities[city3].owner == human_civ) || (game.reveal_map != '\0')) {
    city4 = citywnd_get_city((C_004083b0_4 *)&city_window);
    if (((cities[city4].flags & 4) == 0) ||
       ((game.reveal_map != '\0' && ((game.game_flags & 0x80) != 0)))) {
      uVar7 = 0;
      city2 = citywnd_get_city((C_004083b0_4 *)&city_window);
      city_recalc(city2,uVar7);
      sVar1 = (short)city_improvement_list_top;
      for (local_14 = 1; local_14 < 0x27; local_14++) {
        iVar7 = local_14;
        city2 = citywnd_get_city((C_004083b0_4 *)&city_window);
        city = city_has_improvement(city2,iVar7);
        if ((city != 0) && (local_c = local_c + 1, (short)(sVar1 + (short)param_1 + 1) == local_c))
        {
          improvement = local_14;
          break;
        }
      }
      if (-1 < improvement) {
        if ((local_14 == 1) && ((game.reveal_map == '\0' || ((game.game_flags & 0x80) == 0)))) {
          snd_play_effect(0x69,0,0,0);
          popup_game_with_improvement(ADDR(0x630da0, ((u8 *)&g.d_00630da0)),1,8);
        }
        else {
          iVar6 = (uint)improvements[improvement].cost * (uint)cosmic.shield_box_rows;
          text_set_label_arg(0,improvements[improvement].name);
          text_set_number_arg(0,iVar6);
          city = popup_game_with_improvement(ADDR(0x630db0, ((u8 *)&g.d_00630db0)),improvement,8);
          if (city == 0) {
            snd_play_effect(0x6e,0,0,0);
            uVar7 = 0;
            city2 = citywnd_get_city((C_004083b0_4 *)&city_window);
            city_set_improvement(city2,improvement,uVar7);
            city = citywnd_get_city((C_004083b0_4 *)&city_window);
            civs[cities[city].owner].gold = civs[cities[city].owner].gold + iVar6;
            city = citywnd_get_city((C_004083b0_4 *)&city_window);
            cities[city].flags = cities[city].flags | 4;
            city_window_refresh((FrameWindow *)&city_window);
            status_draw_info(1);
            advisor_refresh_if_open(5);
            advisor_refresh_if_open(4);
            advisor_refresh_if_open(6);
          }
        }
      }
    }
    else {
      snd_play_effect(0x69,0,0,0);
      city2 = citywnd_get_city((C_004083b0_4 *)&city_window);
      popup_game_with_city(ADDR(0x630d94, ((u8 *)&g.d_00630d94)),city2);
    }
  }
  return;
}
#undef human_civ
#undef local_14
#undef improvement
#undef local_c

/* 00505ffa auto */
#define _DAT_006aa770 (*(i32 *)((u8 *)&g.d_006aa770))
#define local_78 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_68 (*(i8 (*)[16])(frame_ + FRAME_OFF(16)))
#define local_58 (*(i8 (*)[16])(frame_ + FRAME_OFF(32)))
#define local_48 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_44 (*(int *)(frame_ + FRAME_OFF(52)))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(56)))
#define local_3c (*(int *)(frame_ + FRAME_OFF(60)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(64)))
#define local_34 (*(uptr *)(frame_ + FRAME_OFF(68)))
#define local_30 (*(u32 *)(frame_ + FRAME_OFF(72)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(76)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(80)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(84)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(88)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(92)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(96)))
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(100)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall city_window_draw_improvements(FrameWindow *this,int param_1)

{
  u32 uVar1;
  i32 uVar2;
  int iVar3;
  int iVar4;
  iptr iVar5;
  i8 frame_[FRAME_OFF(120)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((((*(int *)(this[7].pad_15c + 0xc) == 0) && (*(int *)(this[7].pad_15c + 8) == 0)) &&
      (*(int *)(this[7].pad_15c + 0x10) == 0)) && (-1 < *(int *)(this[7].pad_15c + 4))) {
    city_window_begin_draw((C_004083b0_12c *)this,(iptr)this[7].pad_200);
    clickmap_remove_by_id((ClickMapRemoveView *)&this->field_2d8,4);
    local_30 = this[7].field_230;
    local_34 = this[7].field_234;
    text_clear();
    text_append_label(0x1c0);
    text_set_colors(0x7c,0x12,1,1);
    uVar2 = rect_width((iptr)this[7].pad_200);
    iVar4 = *(int *)(this[7].pad_200 + 4);
    iVar3 = city_window_scale((C_004083b0_4 *)this,1);
    gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),*(i32 *)this[7].pad_200,iVar4 - iVar3,uVar2);
    local_3c = city_window_scale((C_004083b0_4 *)this,2);
    local_3c = local_30 + local_3c;
    local_44 = city_window_scale((C_004083b0_4 *)this,1);
    local_44 = local_34 + local_44;
    iVar4 = rect_height((iptr)&this[7].field_230);
    iVar3 = city_window_scale((C_004083b0_4 *)this,1);
    local_20 = city_window_scale((C_004083b0_4 *)this,0xc);
    local_20 = (iVar4 - (iVar3 >> 1)) / local_20;
    local_18 = *(int *)(this[7].pad_15c + 0x3c) * 2 - 8;
    for (local_1c = 0; local_1c < local_20; local_1c++) {
      iVar5 = city_window_scale((C_004083b0_4 *)this,0xc);
      iVar4 = city_window_scale((C_004083b0_4 *)this,0xc0);
      iVar3 = city_window_scale((C_004083b0_4 *)this,4);
      rect_set_xywh((iptr)local_14,local_3c,local_44,iVar4 - iVar3,iVar5);
      hotspot_add_rect((ClickMap *)&this->field_2d8,local_1c,4,(iptr)local_14);
      iVar4 = city_window_scale((C_004083b0_4 *)this,0xc);
      local_44 += iVar4;
    }
    local_44 = local_34 + 1;
    local_38 = 0;
    for (improvement = 0; improvement < 0x43; improvement++) {
      if (improvement < 0x27) {
        local_48 = city_has_improvement(*(iptr *)(this[7].pad_15c + 4),improvement);
        local_24 = -1;
      }
      else {
        local_24 = improvement - 0x27;
        if ((int)game.wonder_city[improvement - 0x27] == *(int *)(this[7].pad_15c + 4)) {
          local_48 = 1;
        }
        else {
          local_48 = 0;
        }
      }
      if (((local_48 != 0) &&
          (local_38 = local_38 + 1, *(int *)(this[7].pad_15c + 0x1c) + 1 <= local_38)) &&
         (local_38 <= *(int *)(this[7].pad_15c + 0x1c) + local_20)) {
        gfx_set_zoom_scale(local_18);
        if (local_24 < 0) {
          sprite_draw
                    ((Sprite *)(&improvement_icon_sprites + improvement * 0x3c),(iptr)local_68,(iptr)this,
                     local_3c,local_44);
        }
        else {
          sprite_draw
                    ((Sprite *)(&wonder_icon_sprites + local_24 * 0x3c),(iptr)local_58,(iptr)this,
                     local_3c,local_44);
        }
        gfx_reset_zoom_scale();
        local_28 = city_window_scale((C_004083b0_4 *)this,0x18);
        local_28 = local_3c + local_28;
        local_2c = local_44 - 1;
        text_clear();
        text_append_string_id(improvements[improvement].name);
        text_set_colors(0x29,10,1,0);
        gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_28,local_2c - 1);
        uVar1 = this[7].field_238;
        iVar4 = city_window_scale((C_004083b0_4 *)this,0xe);
        local_28 = city_window_scale((C_004083b0_4 *)this,4);
        local_28 = (uVar1 - iVar4) - local_28;
        if (local_24 < 0) {
          gfx_set_zoom_scale(*(int *)(this[7].pad_15c + 0x3c) * 3 - 7);
          sprite_draw
                    ((Sprite *)&gold_coin_icon_sprite,(iptr)local_78,(iptr)this,local_28,local_2c);
          gfx_reset_zoom_scale();
        }
        iVar4 = city_window_scale((C_004083b0_4 *)this,0xc);
        local_44 += iVar4;
      }
    }
    _DAT_006aa770 = local_38;
    scrollbar_set_range((Control *)this[7].field_2a0,0,local_38 - 1);
    scrollbar_set_page_size((Control *)this[7].field_2a0,local_20 - 1);
    scrollbar_set_pos
              ((C_0040f380_40 *)this[7].field_2a0,*(iptr *)(this[7].pad_15c + 0x1c));
    if (param_1 != 0) {
      wnd_blit_surface_rect((DibSurface *)this,(iptr)this[7].pad_200);
    }
  }
  return;
}
#undef _DAT_006aa770
#undef local_78
#undef local_68
#undef local_58
#undef local_48
#undef local_44
#undef improvement
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

/* 00506637 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define moving_units_mode (*(i32 *)((u8 *)&g.d_006d1da8))
#define local_340 (*(Dialog *)(frame_ + FRAME_OFF(0)))
#define local_4c (*(Sprite *)(frame_ + FRAME_OFF(756)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(816)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(820)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(824)))
void __cdecl city_window_supported_unit_menu(iptr unit)

{
  iptr city3;
  iptr city2;
  iptr iVar2;
  int city;
  int iVar5;
  iptr iVar6;
  i32 uVar7;
  i8 frame_[FRAME_OFF(832)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_340,0x4000);
  local_8 = 0;
  sprite_init(&local_4c);
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),1);
  if (city_unit_dialog_busy == 0) {
    city_unit_dialog_busy = 1;
    city3 = citywnd_get_city((C_004083b0_4 *)&city_window);
    if ((cities[city3].owner == human_civ) || (game.reveal_map != '\0')) {
      uVar7 = 0;
      city2 = citywnd_get_city((C_004083b0_4 *)&city_window);
      city_recalc(city2,uVar7);
      dlg_unit_sprite_zoom = 8;
      sprite_create_solid(&local_4c,0x40,0x20,0);
      text_set_unit_info_args(unit);
      dlg_load_game_section(&local_340,ADDR(0x630dbc, ((u8 *)&g.d_00630dbc)),1);
      dialog_set_sprite_draw_fn((C_0040bc40_28 *)&local_340,ADDR(0x402059, unit_dlg_draw_sprite_cb));
      dialog_set_image_zoom((DialogWindowView *)&local_340,8);
      dialog_add_sprite((DialogOptionList *)&local_340,(iptr)&local_4c,unit,0);
      uVar7 = 0;
      iVar6 = 4;
      city2 = label_string(*(i32 *)(label_string_ids + 0x4c8));
      dialog_add_option((DialogOptionList *)&local_340,city2,iVar6,uVar7);
      iVar2 = dlg_show_modal(&local_340,0);
      if (0 < iVar2) {
        if (iVar2 == 3) {
          units[unit].orders = 11;
          city = citywnd_get_city((C_004083b0_4 *)&city_window);
          units[unit].goto_x = cities[city].x;
          city = citywnd_get_city((C_004083b0_4 *)&city_window);
          units[unit].goto_y = cities[city].y;
        }
        else if (iVar2 == 4) {
          city = city_at((int)units[unit].x,(int)units[unit].y);
          if (-1 < city) {
            cities[city].shield_box =
                 (short)((int)((int)(char)unit_types[units[unit].type].cost *
                              (uint)cosmic.shield_box_rows) / 2) + cities[city].shield_box;
            iVar5 = citywnd_get_city((C_004083b0_4 *)&city_window);
            if (iVar5 == city) {
              city2 = citywnd_get_city((C_004083b0_4 *)&city_window);
              city_save_build_state(city2);
            }
          }
          unit_destroy_redraw(unit,1);
          city_window_refresh((FrameWindow *)&city_window);
        }
        else {
          city = map_in_bounds((int)units[unit].x,(int)units[unit].y);
          if (city != 0) {
            city = unit_is_selectable(unit);
            if (city == 0) {
              ui_redraw_all_maps(0);
              map_set_cursor_pos((int)units[unit].x,(int)units[unit].y);
              mapview_center_on
                        ((C_004083b0_430 *)&map_views,(int)units[unit].x,(int)units[unit].y
                        );
            }
            else {
              game.active_unit = (i16)unit;
              units[unit].orders = -1;
              moving_units_mode = 0;
              ui_focus_active_unit(0);
            }
            if (iVar2 == 2) {
              city_window_close();
            }
          }
        }
      }
    }
    city_unit_dialog_busy = 0;
    local_8 = local_8 & 0xffffff00;
    /* inlined unwind funclet FUN_00506a15 */ { sprite_destroy((Sprite *)((iptr)&local_4c)); }
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_00506a1e */ { dialog_dtor((Dialog *)((iptr)&local_340)); }
  }
  else {
    local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
    /* inlined unwind funclet FUN_00506a15 */ { sprite_destroy((Sprite *)((iptr)&local_4c)); }
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_00506a1e */ { dialog_dtor((Dialog *)((iptr)&local_340)); }
  }
  return;
}
#undef human_civ
#undef moving_units_mode
#undef local_340
#undef local_4c
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00506a42 auto */
#define city_info_panel_mode (*(int *)((u8 *)&g.d_006aa768))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define moving_units_mode (*(i32 *)((u8 *)&g.d_006d1da8))
#define local_340 (*(Dialog *)(frame_ + FRAME_OFF(0)))
#define local_4c (*(Sprite *)(frame_ + FRAME_OFF(756)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(816)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(820)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(824)))
void __cdecl city_window_present_unit_menu(int param_1)

{
  iptr city3;
  iptr city;
  iptr iVar2;
  iptr city4;
  iptr y;
  iptr city5;
  int unit;
  uint city6;
  int city2;
  iptr iVar10;
  i32 unit2;
  i8 frame_[FRAME_OFF(832)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_340,0x4000);
  local_8 = 0;
  sprite_init(&local_4c);
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),1);
  if (city_unit_dialog_busy != 0) {
    local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
    /* inlined unwind funclet FUN_005070b8 */ { sprite_destroy((Sprite *)((iptr)&local_4c)); }
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_005070c1 */ { dialog_dtor((Dialog *)((iptr)&local_340)); }
    goto LAB_005070d7;
  }
  city_unit_dialog_busy = 1;
  sprite_create_solid(&local_4c,0x40,0x20,0);
  city3 = citywnd_get_city((C_004083b0_4 *)&city_window);
  if ((cities[city3].owner != human_civ) && (game.reveal_map == '\0')) goto LAB_0050708f;
  unit2 = 0;
  city = citywnd_get_city((C_004083b0_4 *)&city_window);
  city_recalc(city,unit2);
  if (city_info_panel_mode != 0) goto LAB_0050708f;
  iVar2 = (iptr)(short)param_1;
  city4 = citywnd_get_city((C_004083b0_4 *)&city_window);
  y = (iptr)cities[city4].y;
  city5 = citywnd_get_city((C_004083b0_4 *)&city_window);
  unit2 = tile_first_unit((int)cities[city5].x,y);
  unit = unit_stack_nth(unit2,iVar2);
  if (unit < 0) goto LAB_0050708f;
  text_set_unit_info_args(unit);
  dlg_load_game_section(&local_340,ADDR(0x630dc8, ((u8 *)&g.d_00630dc8)),1);
  dlg_unit_sprite_zoom = 8;
  dialog_set_sprite_draw_fn((C_0040bc40_28 *)&local_340,ADDR(0x402059, unit_dlg_draw_sprite_cb));
  dialog_set_image_zoom((DialogWindowView *)&local_340,8);
  dialog_add_sprite((DialogOptionList *)&local_340,(iptr)&local_4c,unit,0);
  unit2 = 0;
  iVar10 = 0;
  city = label_string(*(i32 *)(label_string_ids + 0x144));
  dialog_add_option((DialogOptionList *)&local_340,city,iVar10,unit2);
  if (units[unit].orders != -1) {
    unit2 = 0;
    iVar10 = 1;
    city = label_string(*(i32 *)(label_string_ids + 0x148));
    dialog_add_option((DialogOptionList *)&local_340,city,iVar10,unit2);
    dialog_set_default_choice((DialogOptionList *)&local_340,1);
  }
  if (units[unit].orders != 3) {
    unit2 = 0;
    iVar10 = 2;
    city = label_string(*(i32 *)(label_string_ids + 0x14c));
    dialog_add_option((DialogOptionList *)&local_340,city,iVar10,unit2);
  }
  if ((units[unit].orders != 1) && (units[unit].orders != 2)) {
    unit2 = 0;
    iVar10 = 3;
    city = label_string(*(i32 *)(label_string_ids + 0x150));
    dialog_add_option((DialogOptionList *)&local_340,city,iVar10,unit2);
  }
  city6 = citywnd_get_city((C_004083b0_4 *)&city_window);
  if (city6 != (byte)units[unit].home_city) {
    unit2 = 0;
    iVar10 = 5;
    city = label_string(*(i32 *)(label_string_ids + 0x2cc));
    dialog_add_option((DialogOptionList *)&local_340,city,iVar10,unit2);
    if (units[unit].home_city != -1) {
      unit2 = 0;
      iVar10 = 6;
      city = label_string(*(i32 *)(label_string_ids + 0x2f4));
      dialog_add_option((DialogOptionList *)&local_340,city,iVar10,unit2);
    }
  }
  unit2 = 0;
  iVar10 = 7;
  city = label_string(*(i32 *)(label_string_ids + 0x2d0));
  dialog_add_option((DialogOptionList *)&local_340,city,iVar10,unit2);
  if (((((uint)game.human_players & 1 << (units[unit].owner & 0x1fU)) != 0) &&
      (game.turn_civ != '\0')) && (city2 = unit_moves_left(unit), city2 != 0)) {
    unit2 = 0;
    iVar10 = 8;
    city = label_string(*(i32 *)(label_string_ids + 0x2f8));
    dialog_add_option((DialogOptionList *)&local_340,city,iVar10,unit2);
    unit2 = 0;
    iVar10 = 9;
    city = label_string(*(i32 *)(label_string_ids + 0x2fc));
    dialog_add_option((DialogOptionList *)&local_340,city,iVar10,unit2);
  }
  unit2 = dlg_show_modal(&local_340,0);
  switch(unit2) {
  case 1:
    units[unit].orders = -1;
    break;
  case 2:
    unit_set_sleep(unit);
    break;
  case 3:
    units[unit].orders = 1;
    unit_exhaust_moves(unit);
    break;
  case 4:
    unit_relocate_in_place(unit,1);
    break;
  case 5:
    unit2 = citywnd_get_city((C_004083b0_4 *)&city_window);
    units[unit].home_city = (i8)unit2;
    city_window_refresh((FrameWindow *)&city_window);
    goto LAB_0050708f;
  case 6:
    city_window_open
              ((C_004083b0_12c *)&city_window,(uint)(byte)units[unit].home_city);
    goto LAB_0050708f;
  case 7:
    city2 = citywnd_get_city((C_004083b0_4 *)&city_window);
    cities[city2].shield_box =
         (short)((int)((int)(char)unit_types[units[unit].type].cost * (uint)cosmic.shield_box_rows)
                / 2) + cities[city2].shield_box;
    city = citywnd_get_city((C_004083b0_4 *)&city_window);
    city_save_build_state(city);
    unit_destroy_redraw(unit,1);
    city_window_refresh((FrameWindow *)&city_window);
    goto LAB_0050708f;
  case 8:
    game.active_unit = (i16)unit;
    units[unit].orders = -1;
    moving_units_mode = 0;
    ui_focus_active_unit(0);
    break;
  case 9:
    game.active_unit = (i16)unit;
    units[unit].orders = -1;
    moving_units_mode = 0;
    ui_focus_active_unit(0);
    city_window_close();
    goto LAB_0050708f;
  }
  unit2 = 0;
  city = citywnd_get_city((C_004083b0_4 *)&city_window);
  city_recalc(city,unit2);
  city_window_draw_info_panel((FrameWindow *)&city_window,1);
LAB_0050708f:
  city_unit_dialog_busy = 0;
  local_8 = local_8 & 0xffffff00;
  /* inlined unwind funclet FUN_005070b8 */ { sprite_destroy((Sprite *)((iptr)&local_4c)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_005070c1 */ { dialog_dtor((Dialog *)((iptr)&local_340)); }
LAB_005070d7:
  return;
}
#undef city_info_panel_mode
#undef human_civ
#undef moving_units_mode
#undef local_340
#undef local_4c
#undef uStack_10
#undef puStack_c
#undef local_8

/* 005070e5 auto */
#define local_a4 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_a0 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_9c (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_98 (*(i8 (*)[16])(frame_ + FRAME_OFF(16)))
#define local_88 (*(i8 (*)[16])(frame_ + FRAME_OFF(32)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(48)))
#define local_74 (*(int *)(frame_ + FRAME_OFF(52)))
#define local_70 (*(int *)(frame_ + FRAME_OFF(56)))
#define local_6c (*(iptr *)(frame_ + FRAME_OFF(60)))
#define local_68 (*(int *)(frame_ + FRAME_OFF(64)))
#define local_64 (*(int *)(frame_ + FRAME_OFF(68)))
#define local_60 (*(uint *)(frame_ + FRAME_OFF(72)))
#define local_5c (*(int *)(frame_ + FRAME_OFF(76)))
#define local_58 (*(u32 *)(frame_ + FRAME_OFF(80)))
#define local_54 (*(u32 *)(frame_ + FRAME_OFF(84)))
#define local_50 (*(int *)(frame_ + FRAME_OFF(88)))
#define local_4c (*(int *)(frame_ + FRAME_OFF(92)))
#define local_48 (*(int *)(frame_ + FRAME_OFF(96)))
#define local_44 (*(int *)(frame_ + FRAME_OFF(100)))
#define local_40 (*(int *)(frame_ + FRAME_OFF(104)))
#define local_3c (*(int *)(frame_ + FRAME_OFF(108)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(112)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(116)))
#define local_30 (*(iptr *)(frame_ + FRAME_OFF(120)))
#define local_2c (*(i32 *)(frame_ + FRAME_OFF(124)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(128)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(132)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(136)))
#define local_1c (*(i8 (*)[16])(frame_ + FRAME_OFF(140)))
#define local_c (*(int *)(frame_ + FRAME_OFF(156)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(160)))
void __thiscall city_window_draw_units_present(FrameWindow *this)

{
  int iVar1;
  i32 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  i32 uVar7;
  i8 frame_[FRAME_OFF(168)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_54 = this[7].field_210;
  local_58 = this[7].field_214;
  local_2c = *(i32 *)(this[7].pad_15c + 0x40);
  local_6c = gfx_zoom_scale(0x40,local_2c);
  local_28 = gfx_zoom_scale(0x30,local_2c);
  local_c = gfx_zoom_scale(0x40,local_2c);
  local_64 = gfx_zoom_scale(0x34,local_2c);
  local_50 = city_window_scale((C_004083b0_4 *)this,0xf4);
  local_50 = local_50 / local_c;
  iVar1 = city_window_scale((C_004083b0_4 *)this,0xf4);
  local_8 = (iVar1 - local_c * local_50) / 2;
  local_20 = gfx_zoom_scale(4,local_2c);
  local_3c = local_50 << 2;
  clickmap_remove_by_id((ClickMapRemoveView *)&this->field_2d8,3);
  unit = tile_first_unit((int)cities[*(int *)(this[7].pad_15c + 4)].x,
                                (int)cities[*(int *)(this[7].pad_15c + 4)].y);
  local_68 = 0;
  local_38 = 0;
  local_44 = local_54 + local_8;
  local_5c = unit_stack_sum(unit,2);
  if (local_5c <= local_50) {
    local_20 += (local_64 >> 1);
    text_clear();
    text_append_label(0x1c3);
    text_set_colors(0x7c,0x12,1,1);
    uVar2 = rect_width((iptr)(this[7].pad_23c + 0x14));
    iVar1 = city_window_scale((C_004083b0_4 *)this,1);
    gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),*(i32 *)(this[7].pad_23c + 0x14),this[7].field_254 + iVar1,
                       uVar2);
  }
  local_70 = local_44;
  local_74 = local_58 + local_20;
  text_set_surface((iptr)this);
  text_set_font((iptr)&this[7].field_270);
  local_48 = local_50;
  for (; -1 < unit; unit = unit_next_in_stack(unit)) {
    gfx_draw_unit((iptr)this,unit,4,local_70,local_74,local_2c,0);
    if (local_38 < 2) {
      iVar1 = city_window_scale((C_004083b0_4 *)this,0);
      local_34 = local_74 + iVar1 + local_28;
      text_clear();
      if (units[unit].home_city == -1) {
        text_append_label(0xe);
      }
      else {
        text_append((uint)(byte)units[unit].home_city * 0x58 + ADDR(0x64f360, ((u8 *)&cities + 32)));
      }
      text_buffer_char_3 = 0;
      text_set_colors(10,0x1a,1,1);
      gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_70,local_34,local_6c);
    }
    local_68++;
    local_70 += local_c;
    if (local_50 <= local_68) {
      local_70 = local_44;
      local_74 += local_64;
      local_38++;
      local_68 = 0;
      if (local_38 == 2) {
        local_70 = (local_c >> 1) + local_54 + local_8;
        local_74 = (local_64 >> 1) + local_58 + local_20;
        local_50--;
        local_44 = local_70;
      }
      else if (local_38 == 4) break;
    }
  }
  local_68 = 0;
  local_38 = 0;
  local_50 = local_48;
  local_70 = local_54 + local_8;
  local_74 = local_58 + local_20;
  local_44 = local_70;
  for (local_40 = 0; local_40 < local_3c; local_40++) {
    if (local_38 == 0) {
      local_9c = local_28 - 3;
    }
    else {
      local_9c = local_28;
    }
    rect_set_xywh((iptr)local_1c,local_70,local_74,local_6c,local_9c);
    hotspot_add_rect((ClickMap *)&this->field_2d8,local_40,3,(iptr)local_1c);
    local_68++;
    local_70 += local_c;
    if (local_50 <= local_68) {
      local_68 = 0;
      local_38++;
      local_70 = local_44;
      local_74 += local_64;
      if (local_38 == 2) {
        local_70 = (local_c >> 1) + local_54 + local_8;
        local_74 = (local_64 >> 1) + local_58 + local_20;
        local_50--;
        local_44 = local_70;
      }
      else if (local_38 == 4) break;
    }
  }
  if (city_pollution != 0) {
    gfx_set_zoom_scale(*(int *)(this[7].pad_15c + 0x3c) * 4 - 8);
    uVar7 = 0;
    iVar3 = rect_width((iptr)&this[7].field_210);
    iVar1 = city_window_scale((C_004083b0_4 *)this,0xe);
    iVar3 -= iVar1;
    uVar2 = city_window_scale((C_004083b0_4 *)this,0x40);
    iVar1 = city_pollution;
    iVar6 = city_pollution;
    iVar4 = city_window_scale((C_004083b0_4 *)this,100);
    iVar4 = local_58 + iVar4;
    iVar5 = city_window_scale((C_004083b0_4 *)this,7);
    city_window_draw_icon_row(ADDR(0x6466c8, ((u8 *)&g.d_006466c8)),local_54 + iVar5,iVar4,iVar1,iVar6,uVar2,iVar3,uVar7);
    gfx_reset_zoom_scale();
  }
  local_70 = city_window_scale((C_004083b0_4 *)this,7);
  local_70 = local_54 + local_70;
  local_44 = local_70;
  local_74 = city_window_scale((C_004083b0_4 *)this,0x85);
  local_74 = local_58 + local_74;
  local_24 = font_line_spacing((GameFont *)&this[7].field_270);
  local_24 -= 2;
  text_set_colors(0x79,0x12,1,1);
  iVar1 = civ_has_advance((int)cities[*(int *)(this[7].pad_15c + 4)].owner,0x54);
  if (iVar1 != 0) {
    text_clear();
    text_append_label(0x56);
    text_append_colon();
    for (local_30 = 0; local_30 < 3; local_30++) {
      local_60 = (uint)(*(char *)&cities[(*(int *)(this[7].pad_15c + 4))].supplies[local_30] < '\0'
                       );
      if (local_60 != 0) {
        text_append_lparen();
      }
      if (*(char *)&cities[(*(int *)(this[7].pad_15c + 4))].supplies[local_30] < 1) {
        local_a0 = ~(int)*(char *)&cities[(*(int *)(this[7].pad_15c + 4))].supplies[local_30] + 1;
      }
      else {
        local_a0 = (iptr)*(char *)&cities[(*(int *)(this[7].pad_15c + 4))].supplies[local_30];
      }
      text_append_string_id(commodity_names[local_a0]);
      if (local_60 != 0) {
        text_append_rparen();
      }
      if (local_30 < 2) {
        text_append_comma();
      }
    }
    gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_70,local_74);
    local_74 += local_24;
    text_clear();
    text_append_label(0x57);
    text_append_colon();
    for (local_30 = 0; local_30 < 3; local_30++) {
      local_60 = (uint)(*(char *)&cities[(*(int *)(this[7].pad_15c + 4))].demands[local_30] < '\0'
                       );
      if (local_60 != 0) {
        text_append_lparen();
      }
      if (*(char *)&cities[(*(int *)(this[7].pad_15c + 4))].demands[local_30] < 1) {
        local_a4 = ~(int)*(char *)&cities[(*(int *)(this[7].pad_15c + 4))].demands[local_30] + 1;
      }
      else {
        local_a4 = (iptr)*(char *)&cities[(*(int *)(this[7].pad_15c + 4))].demands[local_30];
      }
      text_append_string_id(commodity_names[local_a4]);
      if (local_60 != 0) {
        text_append_rparen();
      }
      if (local_30 < 2) {
        text_append_comma();
      }
    }
    gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_70,local_74);
    local_74 += local_24;
  }
  iVar1 = city_window_scale((C_004083b0_4 *)this,2);
  local_74 += iVar1;
  for (local_30 = 0; local_30 < (char)cities[*(int *)(this[7].pad_15c + 4)].trade_routes;
      local_30 = local_30 + 1) {
    text_clear();
    text_append(cities[(*(int *)(this[7].pad_15c + 4))].route_partner[local_30] *
                       0x58 + ADDR(0x64f360, ((u8 *)&cities + 32)));
    text_append_space();
    if (*(char *)&cities[(*(int *)(this[7].pad_15c + 4))].route_goods[local_30] < '\0') {
      text_append_label(0xc0);
    }
    else {
      text_append_string_id(commodity_names
                         [*(char *)&cities[(*(int *)(this[7].pad_15c + 4))].route_goods[local_30]]);
    }
    text_append_colon();
    if (*(char *)&cities[(*(int *)(this[7].pad_15c + 4))].route_goods[local_30] < '\0') {
      text_append(ADDR(0x630dd4, ((u8 *)&g.d_00630dd4)));
      iVar1 = gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_70,local_74);
      local_4c = city_window_scale((C_004083b0_4 *)this,2);
      local_4c = iVar1 + local_4c;
      gfx_set_zoom_scale(*(int *)(this[7].pad_15c + 0x3c) * 4 - 8);
      iVar1 = city_window_scale((C_004083b0_4 *)this,3);
      sprite_draw
                ((Sprite *)&small_resource_icon_sprites,(iptr)local_98,(iptr)this,local_4c,local_74 + iVar1)
      ;
      gfx_reset_zoom_scale();
    }
    else {
      text_append_plus();
      text_append_int(*(iptr *)(&city_route_trade_values + local_30 * 4));
      iVar1 = gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_70,local_74);
      local_4c = city_window_scale((C_004083b0_4 *)this,2);
      local_4c = iVar1 + local_4c;
      gfx_set_zoom_scale(*(int *)(this[7].pad_15c + 0x3c) * 4 - 8);
      iVar1 = city_window_scale((C_004083b0_4 *)this,3);
      sprite_draw
                ((Sprite *)&small_trade_icon_sprite,(iptr)local_88,(iptr)this,local_4c,local_74 + iVar1)
      ;
      gfx_reset_zoom_scale();
    }
    local_74 += local_24;
  }
  return;
}
#undef local_a4
#undef local_a0
#undef local_9c
#undef local_98
#undef local_88
#undef unit
#undef local_74
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
#undef local_38
#undef local_34
#undef local_30
#undef local_2c
#undef local_28
#undef local_24
#undef local_20
#undef local_1c
#undef local_c
#undef local_8

/* 00507b69 auto */
#define unit (*(iptr *)(frame_ + FRAME_OFF(4)))
#define y2 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(48)))
void __thiscall city_window_draw_support_map(C_004083b0_4 *this)

{
  char civ;
  i32 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  iptr x;
  int iVar7;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ = cities[this[0x567].field_0].owner;
  text_clear();
  text_append_label(0x1c4);
  text_set_colors(0x7c,0x12,1,1);
  uVar2 = rect_width((iptr)(this + 0x5a3));
  iVar3 = city_window_scale(this,1);
  gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),this[0x5a3].field_0,this[0x5a4].field_0 + iVar3,uVar2);
  iVar3 = rect_width((iptr)(this + 0x593));
  iVar4 = rect_height((iptr)(this + 0x593));
  iVar5 = int_clamp((iVar3 - 4) / (int)map.width,1,(iVar4 - 4) / (int)map.height);
  iVar3 = ((iVar3 - 4) - map.width * iVar5 >> 1) + 2 + this[0x593].field_0;
  iVar4 = ((iVar4 - 4) - map.height * iVar5 >> 1) + 2 + this[0x594].field_0;
  local_8 = (int)civs[civ].capital_x - ((int)map.width >> 1);
  if ((game.rules & 0x8000) != 0) {
    local_8 = 0;
  }
  for (y2 = 0; y2 < map.height; y2++) {
    for (local_20 = 0; local_20 < map.width; local_20++) {
      x = map_wrap_x(local_20 + local_8);
      iVar7 = map_in_bounds(x,y2);
      if ((iVar7 != 0) &&
         ((iVar7 = tile_visible_to(x,y2,(int)civ), iVar7 != 0 ||
          (game.reveal_map != '\0')))) {
        iVar7 = tile_is_ocean(x,y2);
        gfx_target_fill_rect(local_20 * iVar5 + iVar3,y2 * iVar5 + iVar4,iVar5,iVar5,
                           (-(uint)(iVar7 == 0) & 0xffffffd3) + 0x5d);
      }
    }
  }
  for (unit = 0; unit < game.num_units; unit++) {
    if ((units[unit].id != 0) && ((uint)(byte)units[unit].home_city == this[0x567].field_0))
    {
      iVar7 = map_wrap_x(units[unit].x - local_8);
      gfx_target_fill_rect(iVar7 * iVar5 + iVar3,units[unit].y * iVar5 + iVar4,iVar5,iVar5,0x1d);
    }
  }
  iVar7 = map_wrap_x(cities[this[0x567].field_0].x - local_8);
  gfx_target_fill_rect(iVar7 * iVar5 + iVar3,cities[this[0x567].field_0].y * iVar5 + iVar4,iVar5,iVar5
                     ,0x29);
  return;
}
#undef unit
#undef y2
#undef local_20
#undef local_8

/* 00507f31 auto */
#define local_28 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_18 (*(iptr *)(frame_ + FRAME_OFF(16)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(20)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_c (*(int *)(frame_ + FRAME_OFF(28)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(32)))
void __thiscall city_happy_draw_building_icons(C_004083b0_4 *this,iptr param_1,int param_2,int param_3)

{
  int iVar1;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_10 = 0;
  iVar1 = city_window_scale(this,0x14);
  local_14 = ((param_3 >> 1) + param_2) - (iVar1 >> 1);
  local_c = 0;
  do {
    if (3 < local_c) {
      return;
    }
    local_8 = 0;
    switch(local_c) {
    case 0:
      local_18 = 0xe;
      break;
    case 1:
      local_18 = 0xb;
      iVar1 = civ_has_advance((int)cities[this[0x567].field_0].owner,0x37);
      if (iVar1 != 0) {
        iVar1 = civ_has_wonder((int)cities[this[0x567].field_0].owner,10);
        if (iVar1 != 0) {
          local_8 = 1;
          local_18 = 0x31;
        }
        break;
      }
      goto LAB_00507f6b;
    case 2:
      local_18 = 4;
      break;
    case 3:
      iVar1 = city_has_improvement(this[0x567].field_0,1);
      if (iVar1 == 0) {
        local_18 = 7;
      }
      else {
        local_18 = 1;
      }
      if (civs[cities[this[0x567].field_0].owner].government != 6) goto LAB_00507f6b;
    }
    iVar1 = city_has_improvement(this[0x567].field_0,local_18);
    if ((iVar1 != 0) || (local_8 != 0)) {
      if (2 < local_10) {
        return;
      }
      if (local_10 != 0) {
        iVar1 = city_window_scale(this,2);
        *(int *)param_1 = *(int *)param_1 - iVar1;
      }
      local_10++;
      iVar1 = city_window_scale(this,0x24);
      *(int *)param_1 = *(int *)param_1 - iVar1;
      gfx_set_zoom_scale(this[0x575].field_0 * 4 - 8);
      sprite_draw
                ((Sprite *)(&improvement_icon_sprites + local_18 * 0x3c),(iptr)local_28,(iptr)this,
                 *(i32 *)param_1,local_14);
      gfx_reset_zoom_scale();
    }
LAB_00507f6b:
    local_c++;
  } while( true );
}
#undef local_28
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 00508177 auto */
#define city_aggressive_units (*(int *)((u8 *)&g.d_006a65e4))
#define unit (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(36)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_c (*(u32 *)(frame_ + FRAME_OFF(44)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(48)))
void __thiscall
city_happy_draw_unit_effects(C_004083b0_4 *this,iptr param_1,int param_2,int param_3,int param_4)

{
  byte bVar1;
  bool bVar2;
  iptr civ;
  int iVar4;
  iptr iVar5;
  i32 uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  i32 uVar11;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  bVar2 = false;
  civ = (iptr)cities[this[0x567].field_0].owner;
  bVar1 = civs[civ].government;
  local_c = this[0x576].field_0;
  iVar4 = gfx_zoom_scale(0x40,local_c);
  local_8 = gfx_zoom_scale(0x30,local_c);
  iVar9 = param_3 >> 1;
  if (bVar1 == 4) {
    iVar4 = font_line_spacing((GameFont *)(this + 0x5ab));
    iVar4 = (iVar9 + param_2) - (iVar4 >> 1);
    text_set_colors(0x29,10,1,0);
    uVar11 = 0;
    uVar6 = *(i32 *)param_1;
    iVar5 = label_string(government_names[4]);
    uVar6 = gfx_draw_text_right(iVar5,uVar6,iVar4,uVar11);
    *(i32 *)param_1 = uVar6;
  }
  else if (bVar1 < 5) {
    local_28 = 0;
    for (unit = 0; unit < game.num_units; unit++) {
      if ((((units[unit].id != 0) &&
           (iVar8 = local_8 >> 1, cities[this[0x567].field_0].x == units[unit].x)) &&
          (cities[this[0x567].field_0].y == units[unit].y)) &&
         (unit_types[units[unit].type].attack != '\0')) {
        local_28++;
        if (3 < local_28) {
          return;
        }
        *(int *)param_1 = *(int *)param_1 - iVar4;
        if (bVar2) {
          iVar7 = city_window_scale(this,2);
          *(int *)param_1 = *(int *)param_1 - iVar7;
        }
        else {
          bVar2 = true;
        }
        gfx_draw_unit((iptr)this,unit,4,*(i32 *)param_1,(iVar9 + param_2) - iVar8,
                           local_c,0);
      }
    }
  }
  else {
    iVar4 = city_window_scale(this,10);
    iVar8 = civ_has_wonder(civ,0x15);
    if ((iVar8 == 0) && (iVar8 = city_has_improvement(this[0x567].field_0,0x21), iVar8 == 0)) {
      local_18 = 1;
    }
    else {
      local_18 = 0;
    }
    if (civs[civ].government == 6) {
      local_18++;
    }
    if (local_18 != 0) {
      local_20 = city_aggressive_units;
      if ((city_aggressive_units != 0) && (civs[civ].government == 5)) {
        local_20 = city_aggressive_units - 1;
      }
      local_14 = local_20 * local_18;
      if (local_14 != 0) {
        iVar8 = city_window_scale(this,2);
        iVar8 = param_4 - iVar8;
        iVar5 = 0;
        piVar10 = &local_14;
        local_10 = iVar8;
        iVar7 = city_window_scale(this,10);
        iVar8 = ui_calc_item_spacing(local_14,iVar7 + 1,iVar8,(iptr)piVar10,iVar5);
        local_10 = city_window_scale(this,10);
        local_10 += (local_14 - 1) * iVar8;
        *(int *)param_1 = *(int *)param_1 - local_10;
        gfx_set_zoom_scale(this[0x575].field_0 * 4 - 8);
        uVar6 = 0;
        iVar8 = local_10;
        iVar7 = city_window_scale(this,10);
        city_window_draw_icon_row(ADDR(0x646598, ((u8 *)&g.d_00646598)),*(i32 *)param_1,(iVar9 + param_2) - (iVar4 >> 1),local_14
                           ,local_14,iVar7 + 1,iVar8,uVar6);
        gfx_reset_zoom_scale();
      }
    }
  }
  return;
}
#undef city_aggressive_units
#undef unit
#undef local_28
#undef local_20
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 00508552 auto */
#define city_building_content (*(iptr *)((u8 *)&g.d_006a6618))
#define local_64 (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_54 (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
#define civ (*(iptr *)(frame_ + FRAME_OFF(36)))
#define local_40 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_3c (*(int *)(frame_ + FRAME_OFF(44)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(52)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(56)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(60)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(64)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(68)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(72)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(76)))
#define local_18 (*(iptr *)(frame_ + FRAME_OFF(80)))
#define local_14 (*(iptr *)(frame_ + FRAME_OFF(84)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(88)))
#define local_c (*(int *)(frame_ + FRAME_OFF(92)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(96)))
void __thiscall city_window_draw_happiness(C_004083b0_4 *this)

{
  i32 uVar1;
  int iVar2;
  iptr iVar3;
  int iVar4;
  int iVar5;
  i8 frame_[FRAME_OFF(104)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ = (iptr)cities[this[0x567].field_0].owner;
  text_clear();
  text_append_label(0x1c5);
  text_set_colors(0x7c,0x12,1,1);
  uVar1 = rect_width((iptr)(this + 0x5a3));
  iVar2 = city_window_scale(this,1);
  gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),this[0x5a3].field_0,this[0x5a4].field_0 + iVar2,uVar1);
  local_20 = this[0x5a3].field_0 + 2;
  iVar2 = city_window_scale(this,0xe);
  local_34 = this[0x5a4].field_0 + iVar2 + 2;
  local_30 = rect_width((iptr)(this + 0x5a3));
  local_30 -= 4;
  local_3c = rect_height((iptr)(this + 0x5a3));
  local_3c -= 4;
  local_10 = local_3c / 5;
  local_38 = local_20;
  local_40 = local_34;
  iVar5 = local_10 >> 1;
  iVar2 = city_window_scale(this,0x1e);
  local_24 = iVar5 - (iVar2 >> 1);
  local_14 = 0;
  local_18 = 0;
  do {
    if (4 < local_18) {
      return;
    }
    if (local_18 != 0) {
      city_draw_hline(this[0x5a3].field_0,this[0x5a5].field_0 - 1,local_40,0x7c);
    }
    local_c = local_30 >> 1;
    local_2c = local_38 + local_30;
    switch(local_18) {
    case 0:
      break;
    case 1:
      if ((uint)(byte)(&city_happy_by_stage)[local_14] - (uint)(byte)(&city_unhappy_by_stage)[local_14] !=
          (uint)city_happy_after_lux - (uint)city_unhappy_after_lux) {
        local_14 = 1;
        local_8 = city_window_scale(this,0xe);
        local_2c -= local_8;
        iVar5 = (local_10 >> 1) + local_40;
        iVar2 = city_window_scale(this,0xe);
        local_1c = iVar5 - (iVar2 >> 1);
        gfx_set_zoom_scale(this[0x575].field_0 * 4 - 8);
        sprite_draw
                  ((Sprite *)&tax_rate_icon_sprites,(iptr)local_54,(iptr)this,local_2c,local_1c);
        gfx_reset_zoom_scale();
        break;
      }
      goto LAB_00508678;
    case 2:
      iVar2 = city_has_improvement(this[0x567].field_0,4);
      if (((((iVar2 == 0) && (iVar2 = city_has_improvement(this[0x567].field_0,0xe), iVar2 == 0)) &&
           (iVar2 = city_has_improvement(this[0x567].field_0,0xb), iVar2 == 0)) &&
          (iVar2 = civ_has_wonder(civ,10), iVar2 == 0)) &&
         (((iVar2 = city_has_improvement(this[0x567].field_0,7), iVar2 == 0 &&
           (iVar2 = city_has_improvement(this[0x567].field_0,1), iVar2 == 0)) ||
          (civs[civ].government != 6)))) goto LAB_00508678;
      local_14 = 2;
      city_happy_draw_building_icons(this,(iptr)&local_2c,local_40,local_10);
      break;
    case 3:
      if ((uint)(byte)(&city_happy_by_stage)[local_14] - (uint)(byte)(&city_unhappy_by_stage)[local_14] ==
          (uint)city_happy_after_units - (uint)city_unhappy_after_units) goto LAB_00508678;
      city_happy_draw_unit_effects(this,(iptr)&local_2c,local_40,local_10,local_30);
      break;
    case 4:
      if ((uint)city_happy_after_units - (uint)city_unhappy_after_units == (uint)city_happy_after_wonders - (uint)city_unhappy_after_wonders)
      goto LAB_00508678;
      iVar5 = (local_10 >> 1) + local_40;
      iVar2 = font_line_spacing((GameFont *)(this + 0x5ab));
      local_1c = iVar5 - (iVar2 >> 1);
      text_set_colors(0x29,10,1,0);
      uVar1 = 0;
      iVar2 = local_2c;
      iVar5 = local_1c;
      iVar3 = label_string(*(i32 *)(label_string_ids + 0x160));
      local_2c = gfx_draw_text_right(iVar3,iVar2,iVar5,uVar1);
    }
    iVar2 = city_window_scale(this,2);
    local_2c -= iVar2;
    local_28 = local_2c - local_38;
    iVar2 = local_28;
    if (local_c <= local_28) {
      iVar2 = local_c;
    }
    local_c = iVar2;
    if ((local_18 == 2) && (civs[civ].government == 4)) {
      iVar5 = (local_10 >> 1) + local_40;
      iVar2 = font_line_spacing((GameFont *)(this + 0x5ab));
      local_1c = iVar5 - (iVar2 >> 1);
      text_set_colors(0x29,10,1,0);
      text_clear();
      text_append_label(0x5d);
      text_append_colon();
      text_append_int(city_building_content);
      iVar5 = (local_10 >> 1) + local_40;
      iVar2 = city_window_scale(this,0xe);
      local_1c = iVar5 - (iVar2 >> 1);
      sprite_draw
                ((Sprite *)&gold_coin_icon_sprite,(iptr)local_64,(iptr)this,local_38,local_1c);
      iVar2 = local_1c;
      iVar5 = city_window_scale(this,0xe);
      iVar4 = city_window_scale(this,3);
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar5 + iVar4 + local_38,iVar2);
    }
    else {
      city_happy_draw_citizen_row(this,local_38,local_40 + local_24,iVar2,
                         (uint)(byte)(&city_happy_by_stage)[local_18],(uint)(byte)(&city_unhappy_by_stage)[local_18]
                         ,(uint)(byte)(&city_angry_by_stage)[local_18]);
    }
    local_40 += local_10;
LAB_00508678:
    local_18++;
  } while( true );
}
#undef city_building_content
#undef local_64
#undef local_54
#undef civ
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

/* 00508adc auto */
void __thiscall city_window_draw_info_panel(FrameWindow *this,int param_1)

{
  int iVar1;
  
  if ((((*(int *)(this[7].pad_15c + 0xc) == 0) && (*(int *)(this[7].pad_15c + 8) == 0)) &&
      (*(int *)(this[7].pad_15c + 0x10) == 0)) && (-1 < *(int *)(this[7].pad_15c + 4))) {
    city_window_begin_draw((C_004083b0_12c *)this,(iptr)&this[7].field_210);
    iVar1 = *(int *)(this[7].pad_15c + 0x18);
    if (iVar1 == 0) {
      city_window_draw_units_present(this);
    }
    else if (iVar1 == 1) {
      city_window_draw_support_map((C_004083b0_4 *)this);
    }
    else if (iVar1 == 2) {
      city_window_draw_happiness((C_004083b0_4 *)this);
    }
    if (param_1 != 0) {
      wnd_blit_surface_rect((DibSurface *)this,(iptr)&this[7].field_210);
    }
  }
  return;
}

/* 00508bc5 auto */
void __thiscall city_window_draw_all(FrameWindow *this,i32 param_1)

{
  if ((((*(int *)(this[7].pad_15c + 0xc) == 0) && (*(int *)(this[7].pad_15c + 8) == 0)) &&
      (*(int *)(this[7].pad_15c + 0x10) == 0)) && (-1 < *(int *)(this[7].pad_15c + 4))) {
    city_window_draw_citizens(this,param_1,0);
    city_window_draw_resource_map(this,param_1);
    city_window_draw_food_box((C_004083b0_12c *)this,param_1);
    city_window_draw_production(this,param_1);
    city_window_draw_button_area((C_004083b0_12c *)this,param_1);
    city_window_draw_supported_units(this,param_1);
    city_window_draw_improvements(this,param_1);
    city_window_draw_info_panel(this,param_1);
  }
  return;
}

/* 00508c84 auto */
void __thiscall
city_window_set_scaled_rect
          (C_004083b0_12c *this,iptr param_1,int param_2,int param_3,int param_4,int param_5)

{
  rect_set_xywh(param_1,*(int *)(this[0x12].pad_48 + 100) +
                             (*(int *)(this[0x12].pad_48 + 0x74) * param_2 + 1) / 2 +
                             this->client_x,
                     this->client_y + (*(int *)(this[0x12].pad_48 + 0x74) * param_3 + 1) / 2 +
                     *(int *)(this[0x12].pad_48 + 0x68),
                     (*(int *)(this[0x12].pad_48 + 0x74) * param_4 + 1) / 2,
                     (*(int *)(this[0x12].pad_48 + 0x74) * param_5 + 1) / 2);
  return;
}

/* 00508d24 auto */
void __thiscall city_window_layout_rects(C_004083b0_12c *this)

{
  city_window_set_scaled_rect(this,(iptr)(this[0x12].pad_48 + 0x7c),0,0,0x1b4,0x3d);
  city_window_set_scaled_rect(this,(iptr)(this[0x12].pad_48 + 0x8c),0,0x3d,0x1b4,0x99);
  city_window_set_scaled_rect(this,(iptr)&this[0x13].field_18,7,0x41,0xbc,0x89);
  city_window_set_scaled_rect(this,(iptr)(this[0x12].pad_48 + 0x9c),0x1b4,0,200,0xa7);
  city_window_set_scaled_rect(this,(iptr)(this[0x12].pad_48 + 0xac),0x1b4,0xa7,200,0xbd);
  city_window_set_scaled_rect(this,(iptr)this[0x12].pad_104,0x1b4,0x164,200,0x41);
  city_window_set_scaled_rect(this,(iptr)&this[0x12].field_114,0,0xd4,0xc0,0x4e);
  city_window_set_scaled_rect(this,(iptr)&this[0x13].field_38,7,0xd8,0xb5,0x45);
  city_window_set_scaled_rect(this,(iptr)&this[0x12].field_124,0,0x122,0xc0,0x83);
  city_window_set_scaled_rect(this,(iptr)&this[0x13].field_28,6,0x132,0xa6,0x6c);
  city_window_set_scaled_rect(this,(iptr)&this[0x13].field_8,0xc0,0xd4,0xf4,0xd1);
  city_window_set_scaled_rect(this,(iptr)this[0x13].pad_48,0xc5,0xd8,0xe9,0xc6);
  return;
}

/* 00508ec6 auto */
void __thiscall city_window_fill_margins(C_004083b0_12c *this)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  u32 uVar5;
  i32 uVar6;
  i32 uVar7;
  
  iVar4 = *(int *)(this[0x12].pad_48 + 100);
  iVar1 = *(int *)(this[0x12].pad_48 + 0x68);
  if (0 < iVar4) {
    iVar3 = *(int *)(this[0x12].pad_48 + 0x5c);
    iVar2 = city_window_scale((C_004083b0_4 *)this,0x27c);
    iVar3 -= (iVar4 + iVar2);
    gfx_target_fill_rect(this->client_x,this->client_y,*(i32 *)(this[0x12].pad_48 + 100),
                       *(i32 *)(this[0x12].pad_48 + 0x60),10);
    uVar7 = 10;
    uVar6 = *(i32 *)(this[0x12].pad_48 + 0x60);
    uVar5 = this->client_y;
    iVar2 = city_window_scale((C_004083b0_4 *)this,0x27c);
    gfx_target_fill_rect(this->client_x + iVar2 + iVar4,uVar5,iVar3,uVar6,uVar7);
  }
  if (0 < iVar1) {
    iVar4 = *(int *)(this[0x12].pad_48 + 0x60);
    iVar3 = city_window_scale((C_004083b0_4 *)this,0x1a5);
    iVar4 -= (iVar1 + iVar3);
    gfx_target_fill_rect(this->client_x,this->client_y,*(i32 *)(this[0x12].pad_48 + 0x5c),
                       *(i32 *)(this[0x12].pad_48 + 0x68),10);
    uVar7 = 10;
    uVar6 = *(i32 *)(this[0x12].pad_48 + 0x5c);
    iVar3 = city_window_scale((C_004083b0_4 *)this,0x1a5);
    gfx_target_fill_rect(this->client_x,this->client_y + iVar3 + iVar1,uVar6,iVar4,uVar7);
  }
  return;
}

/* 00509028 auto */
#define local_10 (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall city_window_apply_size(FrameWindow *this)

{
  int iVar1;
  int iVar2;
  u32 uVar3;
  i32 uVar4;
  uint uVar5;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  uVar3 = this->border_width;
  iVar1 = surface_get_height((DibSurface *)this);
  iVar2 = surface_get_width((DibSurface *)this);
  this[7].pad_15c[0x3c] = 2;
  this[7].pad_15c[0x3d] = '\0';
  this[7].pad_15c[0x3e] = '\0';
  this[7].pad_15c[0x3f] = '\0';
  if (((int)(uVar3 + 0x297) <= iVar1) && ((int)(uVar3 * 2 + 0x3b6) <= iVar2)) {
    this[7].pad_15c[0x3c] = 3;
    this[7].pad_15c[0x3d] = '\0';
    this[7].pad_15c[0x3e] = '\0';
    this[7].pad_15c[0x3f] = '\0';
  }
  if ((iVar1 < (int)(uVar3 + 0x1b9)) || (iVar2 < (int)(uVar3 * 2 + 0x278))) {
    this[7].pad_15c[0x3c] = 1;
    this[7].pad_15c[0x3d] = '\0';
    this[7].pad_15c[0x3e] = '\0';
    this[7].pad_15c[0x3f] = '\0';
  }
  if (*(int *)(this[7].pad_15c + 0x3c) < 2) {
    local_10 = 0xc;
    this->caption_height = 0x12;
  }
  else {
    local_10 = city_window_scale((C_004083b0_4 *)this,0x10);
    uVar3 = city_window_scale((C_004083b0_4 *)this,0x18);
    this->caption_height = uVar3;
  }
  font_set((GameFont *)&city_window_font,0,local_10);
  font_set((GameFont *)&city_window_small_font,0,(local_10 * 2) / 3);
  frame_wnd_layout(this);
  *(u32 *)(this[7].pad_15c + 0x24) = this->client_width;
  *(u32 *)(this[7].pad_15c + 0x28) = this->client_height;
  city_window_load_background();
  iVar1 = city_window_scale((C_004083b0_4 *)this,0x27c);
  iVar2 = city_window_scale((C_004083b0_4 *)this,0x1a5);
  if (iVar1 < *(int *)(this[7].pad_15c + 0x24)) {
    *(int *)(this[7].pad_15c + 0x2c) = *(int *)(this[7].pad_15c + 0x24) - iVar1 >> 1;
  }
  else {
    this[7].pad_15c[0x2c] = '\0';
    this[7].pad_15c[0x2d] = '\0';
    this[7].pad_15c[0x2e] = '\0';
    this[7].pad_15c[0x2f] = '\0';
  }
  if (iVar2 < *(int *)(this[7].pad_15c + 0x28)) {
    *(int *)(this[7].pad_15c + 0x30) = *(int *)(this[7].pad_15c + 0x28) - iVar2 >> 1;
  }
  else {
    this[7].pad_15c[0x30] = '\0';
    this[7].pad_15c[0x31] = '\0';
    this[7].pad_15c[0x32] = '\0';
    this[7].pad_15c[0x33] = '\0';
  }
  uVar5 = (uint)(*(int *)(this[7].pad_15c + 0x3c) < 3);
  uVar4 = city_window_scale((C_004083b0_4 *)this,0xc);
  font_set_styled((GameFont *)&this[7].field_270,1,uVar4,uVar5);
  if ((*(int *)(this[7].pad_15c + 0x2c) == *(int *)(this[7].pad_15c + 0x34)) &&
     (*(int *)(this[7].pad_15c + 0x30) == *(int *)(this[7].pad_15c + 0x38))) {
    if (*(int *)(this[7].pad_15c + 0x34) < 0) {
      city_window_create_controls((C_004083b0_12c *)this);
    }
  }
  else {
    city_window_create_controls((C_004083b0_12c *)this);
  }
  *(i32 *)(this[7].pad_15c + 0x34) = *(i32 *)(this[7].pad_15c + 0x2c);
  *(i32 *)(this[7].pad_15c + 0x38) = *(i32 *)(this[7].pad_15c + 0x30);
  return;
}
#undef local_10

/* 005092af auto */
#define city_window_size_level (*(int *)((u8 *)&g.d_006aa78c))
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
void __thiscall city_window_update_title(FrameWindow *this)

{
  int iVar1;
  
  text_clear();
  text_append_label(0x1f);
  text_append_space();
  text_append_str(*(int *)(this[7].pad_15c + 4) * 0x58 + ADDR(0x64f360, ((u8 *)&cities + 32)));
  if (1 < city_window_size_level) {
    text_append_comma();
    text_append_year((int)game.year);
    if ((game.game_flags & 0x80) == 0) {
      text_append_comma();
      text_append_label(0x22);
      text_append_space();
      text_append_city_population(*(i32 *)(this[7].pad_15c + 4));
    }
    else if (((scenario_flags & 2) != 0) &&
            (iVar1 = city_objective_value(*(iptr *)(this[7].pad_15c + 4)), iVar1 != 0)) {
      text_append_comma();
      text_append_label(0x1b0);
      if (1 < iVar1) {
        text_append(ADDR(0x630dd8, ((u8 *)&g.d_00630dd8)));
        text_append_int(iVar1);
      }
    }
    text_append_space();
    text_append_lparen();
    text_append_label(0x9a);
    text_append_colon();
    text_append_gold(civs[cities[*(int *)(this[7].pad_15c + 4)].owner].gold);
    text_append_rparen();
  }
  frame_wnd_set_caption(this,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  return;
}
#undef city_window_size_level
#undef scenario_flags

/* 00509429 auto */
#define game_loop_active (*(char *)((u8 *)&g.d_00628044))
void __thiscall city_window_refresh(FrameWindow *this)

{
  if ((((-1 < *(int *)(this[7].pad_15c + 4)) &&
       (*(int *)(this[7].pad_15c + 4) < (int)game.num_cities)) &&
      (cities[*(int *)(this[7].pad_15c + 4)].id != 0)) && (game_loop_active != '\0')) {
    if ((*(int *)(this[7].pad_15c + 8) == 0) && (*(int *)(this[7].pad_15c + 0xc) == 0)) {
      city_recalc(*(iptr *)(this[7].pad_15c + 4),1);
      city_window_apply_size(this);
      city_window_update_title(this);
      gfx_set_draw_target((iptr)this);
      frame_wnd_draw_caption(this);
      city_window_fill_margins((C_004083b0_12c *)this);
      city_window_layout_rects((C_004083b0_12c *)this);
      city_window_draw_all(this,0);
      wnd_blit_surface((DibSurface *)this);
    }
    else {
      city_window_update_title(this);
    }
  }
  return;
}
#undef game_loop_active

/* 00509545 auto */
void __thiscall city_window_bring_to_top(C_004083b0_4 *this)

{
  iptr iVar1;
  
  if ((this[0x569].field_0 == 0) && (this[0x568].field_0 == 0)) {
    iVar1 = wnd_get_window((WndBase *)(this + 0x12));
    BringWindowToTop(*(HWND *)(iVar1 + 4));
  }
  return;
}

/* 00509590 auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define city_acquire_wonder_busy (*(int *)((u8 *)&g.d_006ad8e8))
#define city_create_busy (*(int *)((u8 *)&g.d_006ad8c4))
#define city_delete_busy (*(int *)((u8 *)&g.d_006ad8c8))
#define city_turn_processing (*(int *)((u8 *)&g.d_0062edf8))
#define city_window_exit_btn_pending (*(char *)((u8 *)&g.d_00630d20))
#define city_window_exit_requested (*(int *)((u8 *)&g.d_00630d18))
#define civ_check_destroyed_busy (*(int *)((u8 *)&g.d_006ad8f4))
#define civ_create_busy (*(int *)((u8 *)&g.d_006ad8f0))
#define civ_eliminate_busy (*(int *)((u8 *)&g.d_006ad8ec))
#define dlg_help_pressed (*(int *)((u8 *)&g.d_00631edc))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define net_lock_map_busy (*(int *)((u8 *)&g.d_006ad8cc))
#define net_unlock_map_busy (*(int *)((u8 *)&g.d_006ad8d0))
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
void __thiscall city_window_open(C_004083b0_12c *this,iptr city)

{
  int iVar1;
  
  if ((city_turn_processing == 0) ||
     ((((((iVar1 = XD_InFlushSendBuffer(), iVar1 == 0 && (unit_create_busy == 0)) && (unit_delete_busy == 0)
         ) && (((city_create_busy == 0 && (city_delete_busy == 0)) &&
               ((net_lock_map_busy == 0 && ((net_unlock_map_busy == 0 && (unit_stack_unlink_busy == 0)))))))) &&
       ((unit_stack_link_busy == 0 && (((unit_stack_bottom_busy == 0 && (unit_relocate_busy == 0)) && (city_acquire_wonder_busy == 0))))
       )) && (((civ_eliminate_busy == 0 && (civ_create_busy == 0)) &&
              ((((civ_check_destroyed_busy == 0 && ((unit_gather_cargo_busy == 0 && (unit_lift_off_map_busy == 0)))) &&
                (unit_delete_cargo_busy == 0)) && (unit_destroy_redraw_busy == 0)))))))) {
    game.field_06 = game.field_06 | 2;
    *(iptr *)(this[0x12].pad_48 + 0x3c) = city;
    city_save_build_state(*(iptr *)(this[0x12].pad_48 + 0x3c));
    if (*(int *)(this[0x12].pad_48 + 0x44) != 0) {
      this[0x12].pad_48[0x50] = '\0';
      this[0x12].pad_48[0x51] = '\0';
      this[0x12].pad_48[0x52] = '\0';
      this[0x12].pad_48[0x53] = '\0';
      this[0x12].pad_48[0x54] = '\0';
      this[0x12].pad_48[0x55] = '\0';
      this[0x12].pad_48[0x56] = '\0';
      this[0x12].pad_48[0x57] = '\0';
      this[0x12].pad_48[0x58] = 1;
      this[0x12].pad_48[0x59] = '\0';
      this[0x12].pad_48[0x5a] = '\0';
      this[0x12].pad_48[0x5b] = '\0';
      if (*(int *)(this[0x12].pad_48 + 0x40) != 0) {
        window_show((C_004083b0_4 *)this);
      }
    }
    this[0x12].pad_48[0x44] = '\0';
    this[0x12].pad_48[0x45] = '\0';
    this[0x12].pad_48[0x46] = '\0';
    this[0x12].pad_48[0x47] = '\0';
    this[0x12].pad_48[0x48] = '\0';
    this[0x12].pad_48[0x49] = '\0';
    this[0x12].pad_48[0x4a] = '\0';
    this[0x12].pad_48[0x4b] = '\0';
    if (*(int *)(this[0x12].pad_48 + 0x40) == 0) {
      wnd_repaint((SurfaceWindow *)this);
      window_show((C_004083b0_4 *)this);
    }
    else {
      wnd_show_restored((WndBase *)this->pad_48);
    }
    if (city_window_exit_btn_pending != '\0') {
      city_window_create_exit_button(this,1);
      city_window_exit_btn_pending = '\0';
    }
    city_window_create_change_button(this,1);
    city_window_exit_requested = 0;
    if (city_turn_processing == 0) {
      if ((((((*(i8 *)((char *)&game.game_options + 1)) & 1) != 0) && (3 < cities[city].size)) &&
          ((game.field_0c & 1) == 0)) && (cities[city].owner != human_civ)) {
        popup_text((iptr)PTR_s_TUTORIAL_00627678,ADDR(0x630e00, ((u8 *)&g.d_00630e00)));
        game.field_0c = game.field_0c | 1;
      }
    }
    else {
      if (((((((*(i8 *)((char *)&game.game_options + 1)) & 1) != 0) && ((cities[city].flags & 1) != 0)) ||
           (((cities[city].flags & 0x100000) != 0 && (game.difficulty < 3)))) &&
          ((cities[city].owner == human_civ && (autoplay_active == 0)))) &&
         (popup_text((iptr)PTR_s_TUTORIAL_00627678,ADDR(0x630ddc, ((u8 *)&g.d_00630ddc))), dlg_help_pressed != 0)) {
        popup_text((iptr)PTR_s_TUTORIAL_00627678,ADDR(0x630de8, ((u8 *)&g.d_00630de8)));
        popup_text((iptr)PTR_s_TUTORIAL_00627678,ADDR(0x630df4, ((u8 *)&g.d_00630df4)));
      }
      while (((*(int *)(this[0x12].pad_48 + 0x40) == 0 && (*(int *)(this[0x12].pad_48 + 0x44) == 0))
             && (city_window_exit_requested == 0))) {
        win_pump_one_message();
      }
    }
  }
  return;
}
#undef autoplay_active
#undef city_acquire_wonder_busy
#undef city_create_busy
#undef city_delete_busy
#undef city_turn_processing
#undef city_window_exit_btn_pending
#undef city_window_exit_requested
#undef civ_check_destroyed_busy
#undef civ_create_busy
#undef civ_eliminate_busy
#undef dlg_help_pressed
#undef human_civ
#undef net_lock_map_busy
#undef net_unlock_map_busy
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

/* 00509935 auto */
void __cdecl city_window_on_redraw(void)

{
  city_window_refresh((FrameWindow *)&city_window);
  return;
}

/* 0050994f auto */
#define city_window_closed (*(i32 *)((u8 *)&g.d_006aa75c))
#define _DAT_006aa754 (*(i32 *)((u8 *)&g.d_006aa754))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __cdecl city_window_close(void)

{
  city_window_closed = 1;
  wnd_hide((WndBase *)&city_window_wnd);
  _DAT_006aa754 = 0xffffffff;
  wnd_focus_and_raise((WndBase *)&main_frame_wnd);
  ui_flush_input();
  return 0;
}
#undef city_window_closed
#undef _DAT_006aa754

/* 0050998f auto */
#define _DAT_006aa784 (*(i32 *)((u8 *)&g.d_006aa784))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl city_window_calc_rect(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = city_window_scale((C_004083b0_4 *)&city_window,0x27c);
  iVar2 = city_window_scale((C_004083b0_4 *)&city_window,0x1a5);
  iVar3 = city_window_scale((C_004083b0_4 *)&city_window,0x18);
  iVar2 = iVar2 + iVar3 + 8;
  iVar3 = wnd_client_width((WndBase *)&main_frame_wnd);
  iVar4 = wnd_client_height((WndBase *)&main_frame_wnd);
  _DAT_006aa784 = 0xffffffff;
  rect_set_xywh(ADDR(0x655344, ((u8 *)&g.d_00655344)),(iVar3 >> 1) - (iVar1 + 0x10 >> 1),(iVar4 >> 1) - (iVar2 >> 1),
                     iVar1 + 0x10 + sys_dlgframe_w2,iVar2 + sys_dlgframe_h2);
  return;
}
#undef _DAT_006aa784

/* 00509a49 auto */
#define city_window_size_level (*(i32 *)((u8 *)&g.d_006aa78c))
void __cdecl city_window_init_size(void)

{
  city_window_size_level = 2;
  if (999 < screen_width) {
    city_window_size_level = 3;
  }
  city_window_calc_rect();
  return;
}
#undef city_window_size_level

/* 00509a82 auto */
#define _DAT_006aa758 (*(i32 *)((u8 *)&g.d_006aa758))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl city_window_on_minimize(void)

{
  _DAT_006aa758 = 1;
  return;
}
#undef _DAT_006aa758

/* 00509a9c auto */
#define _DAT_006aa758 (*(i32 *)((u8 *)&g.d_006aa758))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl city_window_on_restore(void)

{
  _DAT_006aa758 = 0;
  city_window_refresh((FrameWindow *)&city_window);
  return;
}
#undef _DAT_006aa758

/* 00509ac0 auto */
#define city_shield_rows (*(int *)((u8 *)&g.d_006a657c))
#define city_shield_support (*(int *)((u8 *)&g.d_006a6568))
#define city_total_shields (*(int *)((u8 *)&g.d_006a65cc))
void __cdecl city_text_append_build_turns(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  i32 uVar3;
  i32 uVar4;
  
  uVar4 = 999;
  uVar3 = 1;
  iVar2 = param_1 * city_shield_rows;
  iVar1 = int_clamp_c(city_total_shields - city_shield_support,1,99);
  iVar1 = int_clamp_c(((iVar2 - 1) - param_2) / iVar1 + 1,uVar3,uVar4);
  text_append_int(iVar1);
  text_append_space();
  if (iVar1 == 1) {
    text_append_label(0x2d);
  }
  else {
    text_append_label(0x2c);
  }
  return;
}
#undef city_shield_rows
#undef city_shield_support
#undef city_total_shields

/* 00509b48 auto */
#define blocked_input_kind (*(i32 *)((u8 *)&g.d_006c31ac))
#define city_acquire_wonder_busy (*(int *)((u8 *)&g.d_006ad8e8))
#define city_create_busy (*(int *)((u8 *)&g.d_006ad8c4))
#define city_delete_busy (*(int *)((u8 *)&g.d_006ad8c8))
#define city_window_closed (*(int *)((u8 *)&g.d_006aa75c))
#define civ_check_destroyed_busy (*(int *)((u8 *)&g.d_006ad8f4))
#define civ_create_busy (*(int *)((u8 *)&g.d_006ad8f0))
#define civ_eliminate_busy (*(int *)((u8 *)&g.d_006ad8ec))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define net_lock_map_busy (*(int *)((u8 *)&g.d_006ad8cc))
#define net_unlock_map_busy (*(int *)((u8 *)&g.d_006ad8d0))
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
#define _DAT_006c31b0 (*(i32 *)((u8 *)&g.d_006c31b0))
#define _DAT_006c31b4 (*(i32 *)((u8 *)&g.d_006c31b4))
#define _DAT_006c31b8 (*(i32 *)((u8 *)&g.d_006c31b8))
#define local_368 (*(uint *)(frame_ + FRAME_OFF(0)))
#define local_35c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_354 (*(Dialog *)(frame_ + FRAME_OFF(20)))
#define local_60 (*(i8 (*)[8])(frame_ + FRAME_OFF(776)))
#define local_58 (*(i8 *)(frame_ + FRAME_OFF(784)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(856)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(860)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(864)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl city_button_buy(i32 param_1)

{
  bool bVar1;
  iptr iVar2;
  iptr iVar3;
  int civ;
  iptr city2;
  iptr city3;
  iptr unit_type;
  iptr city4;
  int iVar11;
  iptr city5;
  iptr city6;
  int city;
  uint uVar13;
  i32 uVar14;
  i32 uVar15;
  i8 frame_[FRAME_OFF(872)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_354,0x4000);
  local_8 = 0;
  iVar2 = citywnd_get_city((C_004083b0_4 *)&city_window);
  if (iVar2 == -1) {
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_0050a1b2 */ { dialog_dtor((Dialog *)((iptr)&local_354)); }
  }
  else {
    iVar3 = XD_InFlushSendBuffer();
    if (((((((iVar3 == 0) && (unit_create_busy == 0)) && (unit_delete_busy == 0)) &&
          ((city_create_busy == 0 && (city_delete_busy == 0)))) &&
         (((net_lock_map_busy == 0 && ((net_unlock_map_busy == 0 && (unit_stack_unlink_busy == 0)))) &&
          (unit_stack_link_busy == 0)))) &&
        ((((unit_stack_bottom_busy == 0 && (unit_relocate_busy == 0)) && (city_acquire_wonder_busy == 0)) &&
         (((civ_eliminate_busy == 0 && (civ_create_busy == 0)) &&
          ((civ_check_destroyed_busy == 0 && ((unit_gather_cargo_busy == 0 && (unit_lift_off_map_busy == 0)))))))))) &&
       ((unit_delete_cargo_busy == 0 && (unit_destroy_redraw_busy == 0)))) {
      uVar14 = 0;
      city2 = citywnd_get_city((C_004083b0_4 *)&city_window);
      city_recalc(city2,uVar14);
      civ = citywnd_get_city((C_004083b0_4 *)&city_window);
      civ = (int)cities[civ].owner;
      city3 = citywnd_get_city((C_004083b0_4 *)&city_window);
      unit_type = (iptr)cities[city3].building;
      city4 = citywnd_get_city((C_004083b0_4 *)&city_window);
      iVar11 = (int)cities[city4].building;
      if ((human_civ == civ) || (game.reveal_map != '\0')) {
        if (-iVar11 == 0x26) {
          local_8 = 0xffffffff;
          /* inlined unwind funclet FUN_0050a1b2 */ { dialog_dtor((Dialog *)((iptr)&local_354)); }
        }
        else {
          city5 = citywnd_get_city((C_004083b0_4 *)&city_window);
          if (cities[city5].building < '\0') {
            local_368 = (uint)improvements[-iVar11].cost;
            uVar15 = 999;
            uVar14 = 0;
            uVar13 = (uint)cosmic.shield_box_rows;
            city = citywnd_get_city((C_004083b0_4 *)&city_window);
            city = int_clamp(uVar13 * local_368 - (int)cities[city].shield_box,uVar14,
                                        uVar15);
            local_35c = city * 2;
            if (0x22 < -iVar11) {
              local_35c = city << 2;
            }
            text_set_label_arg(0,improvements[-iVar11].name);
          }
          else {
            local_368 = (uint)(char)unit_types[unit_type].cost;
            uVar15 = 999;
            uVar14 = 0;
            uVar13 = (uint)cosmic.shield_box_rows;
            city6 = citywnd_get_city((C_004083b0_4 *)&city_window);
            city = int_clamp(uVar13 * local_368 - (int)cities[city6].shield_box,uVar14,
                                        uVar15);
            local_35c = (city * city) / 0x14 + city * 2;
            text_set_label_arg(0,unit_types[unit_type].name);
          }
          city = citywnd_get_city((C_004083b0_4 *)&city_window);
          if (cities[city].shield_box == 0) {
            local_35c = local_35c << 1;
          }
          text_set_number_arg(0,local_35c);
          text_set_number_arg_v(1,civs[civ].gold);
          FUN_005f22d0(local_60,s_COMPLETE0_00630e54);
          bVar1 = local_35c <= civs[civ].gold;
          if (bVar1) {
            local_58 = 0x31;
          }
          city = citywnd_get_city((C_004083b0_4 *)&city_window);
          if ((-1 < cities[city].building) &&
             (city = citywnd_get_city((C_004083b0_4 *)&city_window),
             (cities[city].flags & 1) != 0)) {
            local_58 = 0x32;
            bVar1 = false;
          }
          dialog_load_game_text(&local_354,(iptr)local_60);
          city = citywnd_get_city((C_004083b0_4 *)&city_window);
          if (cities[city].building < '\0') {
            dialog_add_sprite
                      ((DialogOptionList *)&local_354,(iptr)(&improvement_icon_sprites + iVar11 * -0x3c),0,0);
          }
          else {
            dialog_add_sprite
                      ((DialogOptionList *)&local_354,(iptr)(&unit_sprites + unit_type * 0x3c),0,0);
          }
          dialog_set_image_zoom((DialogWindowView *)&local_354,8);
          if (bVar1) {
            dialog_set_default_choice((DialogOptionList *)&local_354,1);
          }
          iVar11 = dlg_show_modal(&local_354,0);
          if (bVar1) {
            if ((iVar11 == 0) && (city_window_closed != 1)) {
              civs[civ].gold -= local_35c;
              civ = citywnd_get_city((C_004083b0_4 *)&city_window);
              cities[civ].shield_box = (ushort)cosmic.shield_box_rows * (short)local_368;
              city2 = citywnd_get_city((C_004083b0_4 *)&city_window);
              city_save_build_state(city2);
              snd_play_effect(0x68,1,0,0);
              uVar14 = 1;
              city2 = citywnd_get_city((C_004083b0_4 *)&city_window);
              city_recalc(city2,uVar14);
              city_window_draw_production((FrameWindow *)&city_window,1);
              city_window_update_title((FrameWindow *)&city_window);
              status_draw_info(1);
            }
            local_8 = 0xffffffff;
            /* inlined unwind funclet FUN_0050a1b2 */ { dialog_dtor((Dialog *)((iptr)&local_354)); }
          }
          else {
            local_8 = 0xffffffff;
            /* inlined unwind funclet FUN_0050a1b2 */ { dialog_dtor((Dialog *)((iptr)&local_354)); }
          }
        }
      }
      else {
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0050a1b2 */ { dialog_dtor((Dialog *)((iptr)&local_354)); }
      }
    }
    else {
      dbg_log(ADDR(0x630e0c, ((u8 *)&g.d_00630e0c)));
      blocked_input_kind = 7;
      _DAT_006c31b0 = citywnd_get_city((C_004083b0_4 *)&city_window);
      civ = citywnd_get_city((C_004083b0_4 *)&city_window);
      _DAT_006c31b4 = (int)cities[civ].owner;
      _DAT_006c31b8 = param_1;
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_0050a1b2 */ { dialog_dtor((Dialog *)((iptr)&local_354)); }
    }
  }
  return;
}
#undef blocked_input_kind
#undef city_acquire_wonder_busy
#undef city_create_busy
#undef city_delete_busy
#undef city_window_closed
#undef civ_check_destroyed_busy
#undef civ_create_busy
#undef civ_eliminate_busy
#undef human_civ
#undef net_lock_map_busy
#undef net_unlock_map_busy
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
#undef _DAT_006c31b0
#undef _DAT_006c31b4
#undef _DAT_006c31b8
#undef local_368
#undef local_35c
#undef local_354
#undef local_60
#undef local_58
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0050a1d6 auto */
#define local_40 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_30 (*(i8 (*)[16])(frame_ + FRAME_OFF(16)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_1c (*(i32 *)(frame_ + FRAME_OFF(36)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(44)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_c (*(int *)(frame_ + FRAME_OFF(52)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(56)))
i32 __cdecl
city_change_draw_option_icon(i32 param_1,iptr param_2,int param_3,byte param_4,int param_5,int param_6,
            int param_7)

{
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_18 = -1;
  local_20 = -1;
  local_1c = 0xfffffffe;
  if (param_3 < 0x3e) {
    local_18 = param_3;
  }
  else {
    local_20 = param_3 - 0x3e;
  }
  local_10 = param_5;
  if ((param_4 & 1) != 0) {
    local_10 = param_5 + 0x26;
  }
  if (-1 < local_18) {
    local_14 = param_6;
    local_8 = gfx_zoom_scale(0x30,0xfffffffe);
    local_c = (local_8 - param_7) / 2;
    local_14 -= local_c;
    gfx_set_zoom_scale(local_1c);
    sprite_draw
              ((Sprite *)(&unit_sprites + local_18 * 0x3c),(iptr)local_30,param_2,local_10,
               local_14);
    gfx_reset_zoom_scale();
  }
  if (-1 < local_20) {
    local_c = (0x14 - param_7) / 2;
    local_14 = param_6 - local_c;
    sprite_draw
              ((Sprite *)(&improvement_icon_sprites + local_20 * 0x3c),(iptr)local_40,param_2,local_10,
               local_14);
  }
  return 0;
}
#undef local_40
#undef local_30
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 0050a473 auto */
#define blocked_input_kind (*(i32 *)((u8 *)&g.d_006c31ac))
#define city_acquire_wonder_busy (*(int *)((u8 *)&g.d_006ad8e8))
#define city_create_busy (*(int *)((u8 *)&g.d_006ad8c4))
#define city_delete_busy (*(int *)((u8 *)&g.d_006ad8c8))
#define city_dlg_close_pending (*(i8 *)((u8 *)&g.d_00630d30))
#define civ_check_destroyed_busy (*(int *)((u8 *)&g.d_006ad8f4))
#define civ_create_busy (*(int *)((u8 *)&g.d_006ad8f0))
#define civ_eliminate_busy (*(int *)((u8 *)&g.d_006ad8ec))
#define dlg_pending_idle_callback (*(i8 * *)((u8 *)&g.d_00635a3c))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define net_lock_map_busy (*(int *)((u8 *)&g.d_006ad8cc))
#define net_unlock_map_busy (*(int *)((u8 *)&g.d_006ad8d0))
#define ui_large_screen (*(int *)((u8 *)&g.d_00633584))
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
#define _DAT_006c31b0 (*(i32 *)((u8 *)&g.d_006c31b0))
#define _DAT_006c31b4 (*(i32 *)((u8 *)&g.d_006c31b4))
#define _DAT_006c31b8 (*(i32 *)((u8 *)&g.d_006c31b8))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(4)))
#define unit_type3 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_954 (*(Dialog *)(frame_ + FRAME_OFF(12)))
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(768)))
#define local_65c (*(int *)(frame_ + FRAME_OFF(772)))
#define local_658 (*(iptr *)(frame_ + FRAME_OFF(776)))
#define local_654 (*(Dialog *)(frame_ + FRAME_OFF(780)))
#define local_360 (*(Dialog *)(frame_ + FRAME_OFF(1536)))
#define local_6c (*(int *)(frame_ + FRAME_OFF(2292)))
#define local_68 (*(int *)(frame_ + FRAME_OFF(2296)))
#define local_64 (*(i8 (*)[80])(frame_ + FRAME_OFF(2300)))
#define unit_type2 (*(iptr *)(frame_ + FRAME_OFF(2380)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(2384)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(2388)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(2392)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl city_button_change(i32 param_1)

{
  char *pcVar1;
  byte civ;
  iptr iVar3;
  iptr iVar4;
  int city2;
  iptr city3;
  iptr city5;
  int city;
  iptr city6;
  iptr city4;
  iptr city7;
  iptr city8;
  iptr *piVar13;
  i32 uVar14;
  iptr *piVar15;
  i8 frame_[FRAME_OFF(2400)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_654,0x8000);
  local_8 = 0;
  dialog_ctor(&local_954,0x4000);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  dialog_ctor(&local_360,0x4000);
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  iVar3 = citywnd_get_city((C_004083b0_4 *)&city_window);
  if (iVar3 == -1) {
    (*(i8 *)((char *)&local_8 + 0)) = 1;
    /* inlined unwind funclet FUN_0050b638 */ { dialog_dtor((Dialog *)((iptr)&local_360)); }
    local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
    /* inlined unwind funclet FUN_0050b644 */ { dialog_dtor((Dialog *)((iptr)&local_954)); }
    local_8 = 0xffffffff;
    /* inlined unwind funclet FUN_0050b650 */ { dialog_dtor((Dialog *)((iptr)&local_654)); }
  }
  else {
    iVar4 = XD_InFlushSendBuffer();
    if (((((((iVar4 == 0) && (unit_create_busy == 0)) && (unit_delete_busy == 0)) &&
          ((city_create_busy == 0 && (city_delete_busy == 0)))) &&
         (((net_lock_map_busy == 0 && ((net_unlock_map_busy == 0 && (unit_stack_unlink_busy == 0)))) &&
          (unit_stack_link_busy == 0)))) &&
        ((((unit_stack_bottom_busy == 0 && (unit_relocate_busy == 0)) && (city_acquire_wonder_busy == 0)) &&
         (((civ_eliminate_busy == 0 && (civ_create_busy == 0)) &&
          ((civ_check_destroyed_busy == 0 && ((unit_gather_cargo_busy == 0 && (unit_lift_off_map_busy == 0)))))))))) &&
       ((unit_delete_cargo_busy == 0 && (unit_destroy_redraw_busy == 0)))) {
      uVar14 = 0;
      city3 = citywnd_get_city((C_004083b0_4 *)&city_window);
      city_recalc(city3,uVar14);
      city2 = citywnd_get_city((C_004083b0_4 *)&city_window);
      civ = cities[city2].owner;
      city2 = (int)(char)civ;
      if ((human_civ == city2) || (game.reveal_map != '\0')) {
        city5 = citywnd_get_city((C_004083b0_4 *)&city_window);
        local_658 = (iptr)cities[city5].building;
        while (city = citywnd_get_city((C_004083b0_4 *)&city_window),
              city != -1) {
          if (((*(i8 *)((char *)&game.game_options + 1)) & 2) != 0) {
            piVar15 = &improvement;
            piVar13 = &unit_type;
            city6 = citywnd_get_city((C_004083b0_4 *)&city_window);
            city_choose_production(city6,(iptr)piVar13,(iptr)piVar15);
            if (unit_type != 999) {
              text_set_label_arg(0,unit_types[unit_type].name);
              dialog_load_text(&local_954,ADDR(0x630eb8, ((u8 *)&g.d_00630eb8)),ADDR(0x630eac, ((u8 *)&g.d_00630eac)),8);
              str_clear((iptr)local_64);
              str_append((iptr)local_64,ADDR(0x630ec0, ((u8 *)&g.d_00630ec0)));
              str_append_string_id((iptr)local_64,unit_types[unit_type].name);
              dialog_add_sprite
                        ((DialogOptionList *)&local_954,(iptr)(&unit_sprites + unit_type * 0x3c),0,0);
              city = dialog_load_text(&local_954,ADDR(0x630ec4, ((u8 *)&g.d_00630ec4)),(iptr)local_64,0x8000)
              ;
              if (city != 0) {
                dialog_load_text(&local_954,ADDR(0x630ed8, ((u8 *)&g.d_00630ed8)),ADDR(0x630ecc, ((u8 *)&g.d_00630ecc)),0x8000);
              }
              dialog_run_modal(&local_954,0,300);
            }
            if (improvement != 999) {
              str_clear((iptr)local_64);
              str_append((iptr)local_64,ADDR(0x630ee0, ((u8 *)&g.d_00630ee0)));
              dialog_load_text(&local_360,ADDR(0x630ef0, ((u8 *)&g.d_00630ef0)),ADDR(0x630ee4, ((u8 *)&g.d_00630ee4)),8);
              if (improvement < 0) {
                city = -improvement;
                improvement = -improvement;
                text_set_label_arg(0,improvements[city].name);
                if (improvement < 0x27) {
                  str_append_string_id((iptr)local_64,improvements[improvement].name);
                  dialog_add_sprite
                            ((DialogOptionList *)&local_360,(iptr)(&improvement_icon_sprites + improvement * 0x3c),
                             (ui_large_screen == 0) - 1 & 8,0);
                }
                else {
                  str_append((iptr)local_64,ADDR(0x630ef8, ((u8 *)&g.d_00630ef8)));
                  dialog_add_sprite
                            ((DialogOptionList *)&local_360,
                             (iptr)(&wonder_icon_sprites + (improvement * 4 - 0x9c) * 0xf),
                             (ui_large_screen == 0) - 1 & 8,0);
                }
              }
              else {
                unit_type = improvement;
                text_set_label_arg(0,unit_types[improvement].name);
                str_append_string_id((iptr)local_64,unit_types[unit_type].name);
                dialog_add_sprite
                          ((DialogOptionList *)&local_360,(iptr)(&unit_sprites + unit_type * 0x3c),0,0
                          );
              }
              city = dialog_load_text(&local_360,ADDR(0x630f00, ((u8 *)&g.d_00630f00)),(iptr)local_64,0x8000)
              ;
              if (city != 0) {
                dialog_load_text(&local_360,ADDR(0x630f14, ((u8 *)&g.d_00630f14)),ADDR(0x630f08, ((u8 *)&g.d_00630f08)),0x8000);
              }
              dialog_run_modal(&local_360,0,300);
            }
          }
          city = citywnd_get_city((C_004083b0_4 *)&city_window);
          text_set_string_arg(0,(iptr)&cities[city].name);
          dialog_load_game_text(&local_654,ADDR(0x630f1c, ((u8 *)&g.d_00630f1c)));
          dialog_set_option_draw_fn((DialogOptionList *)&local_654,ADDR(0x401537, city_change_draw_option_icon));
          dialog_set_list_indent((C_0040bc40_28 *)&local_654,0x4b,0);
          local_65c = 0;
          for (unit_type = 0; unit_type < 0x3e; unit_type++) {
            city3 = unit_type;
            city4 = citywnd_get_city((C_004083b0_4 *)&city_window);
            city = civ_can_build_unit(city2,city4,city3);
            if (city != 0) {
              text_clear();
              text_append_string_id(unit_types[unit_type].name);
              text_append_space();
              text_append(ADDR(0x630f28, ((u8 *)&g.d_00630f28)));
              text_append_lparen();
              city3 = unit_type;
              city4 = citywnd_get_city((C_004083b0_4 *)&city_window);
              uVar14 = city_shields_after_change(city4,city3);
              city_text_append_build_turns((int)(char)unit_types[unit_type].cost,uVar14);
              text_append_comma();
              text_append_label(0xaa);
              text_append_colon();
              text_append_int((int)(char)unit_types[unit_type].attack);
              text_append(ADDR(0x630f2c, ((u8 *)&g.d_00630f2c)));
              text_append_int((int)(char)unit_types[unit_type].defense);
              if ((unit_types[unit_type].flags & 0x400) != 0) {
                text_append(ADDR(0x630f30, ((u8 *)&g.d_00630f30)));
              }
              text_append(ADDR(0x630f34, ((u8 *)&g.d_00630f34)));
              text_append_int((int)(char)unit_types[unit_type].move /
                                 (int)(uint)cosmic.road_move_mult);
              text_append_space();
              text_append_label(0xab);
              text_append_colon();
              text_append_int((int)(char)unit_types[unit_type].hit_points / 10);
              text_append(ADDR(0x630f38, ((u8 *)&g.d_00630f38)));
              text_append_int((int)(char)unit_types[unit_type].firepower);
              text_append_rparen();
              dialog_add_option((DialogOptionList *)&local_654,ADDR(0x679640, ((u8 *)&g.d_00679640)),unit_type,0);
              if (local_658 == unit_type) {
                dialog_set_default_choice((DialogOptionList *)&local_654,unit_type);
              }
              local_65c++;
            }
          }
          for (improvement = 1; improvement < 0x27; improvement++) {
            city3 = improvement;
            city4 = citywnd_get_city((C_004083b0_4 *)&city_window);
            city = city_can_build_improvement(city2,city4,city3);
            if (city != 0) {
              text_clear();
              text_append_string_id(improvements[improvement].name);
              text_append_space();
              text_append(ADDR(0x630f3c, ((u8 *)&g.d_00630f3c)));
              text_append_lparen();
              city = -improvement;
              city3 = citywnd_get_city((C_004083b0_4 *)&city_window);
              uVar14 = city_shields_after_change(city3,city);
              city_text_append_build_turns((uint)improvements[improvement].cost,uVar14);
              text_append_rparen();
              dialog_add_option
                        ((DialogOptionList *)&local_654,ADDR(0x679640, ((u8 *)&g.d_00679640)),improvement + 0x3e,0);
              if (-local_658 == improvement) {
                dialog_set_default_choice((DialogOptionList *)&local_654,improvement + 0x3e);
              }
              local_65c++;
            }
          }
          for (local_6c = 0; local_6c < 0x1c; local_6c++) {
            city = civ_can_build_wonder(city2,local_6c);
            if (city != 0) {
              improvement = local_6c + 0x27;
              text_clear();
              city = wonder_is_expired(local_6c);
              if (city != 0) {
                text_append_str(ADDR(0x630f40, ((u8 *)&g.d_00630f40)));
              }
              text_append_string_id(improvements[improvement].name);
              text_append_space();
              text_append(ADDR(0x630f44, ((u8 *)&g.d_00630f44)));
              text_append_lparen();
              city = -improvement;
              city3 = citywnd_get_city((C_004083b0_4 *)&city_window);
              uVar14 = city_shields_after_change(city3,city);
              city_text_append_build_turns((uint)improvements[improvement].cost,uVar14);
              text_append_rparen();
              dialog_add_option
                        ((DialogOptionList *)&local_654,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_6c + 0x65,0);
              if (-local_658 == improvement) {
                dialog_set_default_choice((DialogOptionList *)&local_654,improvement + 0x3e);
              }
              local_65c++;
            }
          }
          if ((((*(i8 *)((char *)&game.game_options + 1)) & 0x80) != 0) && (game.multiplayer == '\0')) {
            city3 = label_string(*(i32 *)(label_string_ids + 0x130));
            dialog_add_button((C_0040bc40_3c *)&local_654,city3);
          }
          if (((*(i8 *)((char *)&game.game_options + 1)) & 2) != 0) {
            if (0xb < local_65c) {
              local_65c = 0xc;
            }
            dialog_set_position((C_0040bc40_28 *)&local_654,0xfffffc19,0xfffffffb);
          }
          if (local_65c < 0x10) {
            city = local_65c + 1;
            if (city < 9) {
              city = 8;
            }
            dialog_set_list_rows((DialogTextView *)&local_654,city);
          }
          city_dlg_close_pending = 0;
          dlg_pending_idle_callback = ((void *)ADDR(0x00402815, city_change_idle_autoclose));
          unit_type3 = dialog_run_modal(&local_654,0,300);
          city_dlg_close_pending = 0;
          if ((unit_type3 < 0) ||
             (city = citywnd_get_city((C_004083b0_4 *)&city_window), city == -1
             )) {
LAB_0050b609:
            city_window_create_change_button((C_004083b0_12c *)&city_window,1);
            (*(i8 *)((char *)&local_8 + 0)) = 1;
            /* inlined unwind funclet FUN_0050b638 */ { dialog_dtor((Dialog *)((iptr)&local_360)); }
            local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
            /* inlined unwind funclet FUN_0050b644 */ { dialog_dtor((Dialog *)((iptr)&local_954)); }
            local_8 = 0xffffffff;
            /* inlined unwind funclet FUN_0050b650 */ { dialog_dtor((Dialog *)((iptr)&local_654)); }
            goto LAB_0050b666;
          }
          if (((*(i8 *)((char *)&game.game_options + 1)) & 2) != 0) {
            dialog_close(&local_360);
            dialog_close(&local_954);
            ui_flush_input();
          }
          city = citywnd_get_city((C_004083b0_4 *)&city_window);
          cities[city].flags = cities[city].flags & 0xfcffffef;
          if (local_654.field_dc == 0) {
            if (unit_type3 < 0x3e) {
              unit_type2 = unit_type3;
            }
            else {
              unit_type2 = -(unit_type3 - 0x3e);
            }
            city3 = unit_type2;
            city4 = citywnd_get_city((C_004083b0_4 *)&city_window);
            local_68 = city_shields_after_change(city4,city3);
            city = citywnd_get_city((C_004083b0_4 *)&city_window);
            if ((local_68 < cities[city].shield_box) && ((game.message_options & 0x200) == 0)) {
              text_set_number_arg_u8(0,(uint)CONCAT11((char)(game.message_options >> 8),
                                                  cosmic.change_penalty));
              city = citywnd_get_city((C_004083b0_4 *)&city_window);
              if (cities[city].building < '\0') {
                city = citywnd_get_city((C_004083b0_4 *)&city_window);
                text_set_label_arg(0,improvements[-(int)cities[city].building].name);
              }
              else {
                city = citywnd_get_city((C_004083b0_4 *)&city_window);
                text_set_label_arg(0,unit_types[cities[city].building].name);
              }
              if (unit_type2 < 0) {
                text_set_label_arg(1,improvements[-unit_type2].name);
              }
              else {
                text_set_label_arg(1,unit_types[unit_type2].name);
              }
              city = popup_game(ADDR(0x630f5c, ((u8 *)&g.d_00630f5c)));
              if (city == 0) goto LAB_0050b5dc;
            }
            city = citywnd_get_city((C_004083b0_4 *)&city_window);
            if (-1 < cities[city].building) {
              city = citywnd_get_city((C_004083b0_4 *)&city_window);
              pcVar1 = (char *)(cities[city].building + ADDR(0x64c7f4, ((u8 *)&civs + 340)) + city2 * 0x594);
              *pcVar1 = *pcVar1 - 1;
            }
            city = citywnd_get_city((C_004083b0_4 *)&city_window);
            cities[city].building = (i8)unit_type2;
            city = citywnd_get_city((C_004083b0_4 *)&city_window);
            if (-1 < cities[city].building) {
              city = citywnd_get_city((C_004083b0_4 *)&city_window);
              pcVar1 = (char *)(cities[city].building + ADDR(0x64c7f4, ((u8 *)&civs + 340)) + city2 * 0x594);
              *pcVar1 = *pcVar1 + 1;
            }
            city2 = citywnd_get_city((C_004083b0_4 *)&city_window);
            cities[city2].shield_box = (i16)local_68;
            advisor_refresh_if_open(1);
            advisor_refresh_if_open(2);
LAB_0050b5dc:
            uVar14 = 1;
            city3 = citywnd_get_city((C_004083b0_4 *)&city_window);
            city_recalc(city3,uVar14);
            city_window_draw_production((FrameWindow *)&city_window,1);
            city_window_draw_resource_map((FrameWindow *)&city_window,1);
            goto LAB_0050b609;
          }
          if (local_654.field_dc == 1) {
            if ((1 << (civ & 0x1f) & (uint)game.human_players) != 0) {
              city_load_citypref();
              uVar14 = citywnd_get_city((C_004083b0_4 *)&city_window);
              unit_type3 = popup_game_with_city_flags(ADDR(0x630f48, ((u8 *)&g.d_00630f48)),1,uVar14);
              if (unit_type3 < 0) goto LAB_0050b609;
              city2 = citywnd_get_city((C_004083b0_4 *)&city_window);
              cities[city2].flags = cities[city2].flags | 0x10;
              if (unit_type3 == 1) {
                city2 = citywnd_get_city((C_004083b0_4 *)&city_window);
                cities[city2].flags = cities[city2].flags | 0x1000000;
              }
              if (unit_type3 == 2) {
                city2 = citywnd_get_city((C_004083b0_4 *)&city_window);
                cities[city2].flags = cities[city2].flags | 0x2000000;
              }
            }
            uVar14 = 99;
            city3 = citywnd_get_city((C_004083b0_4 *)&city_window);
            city_set_production(city3,uVar14);
            city_window_draw_production((FrameWindow *)&city_window,1);
            goto LAB_0050b609;
          }
          if (local_654.field_dc != 2) {
            if (local_654.field_dc == 3) {
              if (unit_type3 < 0x3e) {
                city2 = citywnd_get_city((C_004083b0_4 *)&city_window);
                city2 = (int)cities[city2].y;
                city7 = citywnd_get_city((C_004083b0_4 *)&city_window);
                city = (int)cities[city7].x;
                city8 = citywnd_get_city((C_004083b0_4 *)&city_window);
                unit_create(unit_type3,(int)cities[city8].owner,city,city2);
                city2 = unit_type3;
              }
              else {
                city2 = unit_type3 - 0x3e;
                if (city2 < 0x23) {
                  uVar14 = 1;
                  unit_type3 = city2;
                  city3 = citywnd_get_city((C_004083b0_4 *)&city_window);
                  city_set_improvement(city3,city2,uVar14);
                  city2 = unit_type3;
                }
                else if (city2 < 0x27) {
                  if ((0x22 < city2) && (city2 < 0x26)) {
                    city = unit_type3 - 0x61;
                    unit_type3 = city2;
                    city2 = citywnd_get_city((C_004083b0_4 *)&city_window);
                    spaceship_add_part((int)cities[city2].owner,city);
                    city2 = unit_type3;
                  }
                }
                else {
                  unit_type3 -= 0x65;
                  uVar14 = citywnd_get_city((C_004083b0_4 *)&city_window);
                  game.wonder_city[unit_type3] = (i16)uVar14;
                  city2 = unit_type3;
                }
              }
              unit_type3 = city2;
              city_window_refresh((FrameWindow *)&city_window);
              popup_debug_text(ADDR(0x630f54, ((u8 *)&g.d_00630f54)));
            }
            goto LAB_0050b5dc;
          }
          if (unit_type3 < 0x3e) {
            pedia_show_unit_modal((C_004083b0_a28 *)&pedia_window,unit_type3);
            local_658 = unit_type3;
          }
          else {
            unit_type3 -= 0x3e;
            pedia_show_improvement_modal((C_004083b0_a28 *)&pedia_window,unit_type3);
            local_658 = -unit_type3;
          }
        }
        dialog_close(&local_654);
        dialog_close(&local_954);
        dialog_close(&local_360);
        (*(i8 *)((char *)&local_8 + 0)) = 1;
        /* inlined unwind funclet FUN_0050b638 */ { dialog_dtor((Dialog *)((iptr)&local_360)); }
        local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
        /* inlined unwind funclet FUN_0050b644 */ { dialog_dtor((Dialog *)((iptr)&local_954)); }
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0050b650 */ { dialog_dtor((Dialog *)((iptr)&local_654)); }
      }
      else {
        (*(i8 *)((char *)&local_8 + 0)) = 1;
        /* inlined unwind funclet FUN_0050b638 */ { dialog_dtor((Dialog *)((iptr)&local_360)); }
        local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
        /* inlined unwind funclet FUN_0050b644 */ { dialog_dtor((Dialog *)((iptr)&local_954)); }
        local_8 = 0xffffffff;
        /* inlined unwind funclet FUN_0050b650 */ { dialog_dtor((Dialog *)((iptr)&local_654)); }
      }
    }
    else {
      dbg_log(ADDR(0x630e60, ((u8 *)&g.d_00630e60)));
      blocked_input_kind = 8;
      _DAT_006c31b0 = citywnd_get_city((C_004083b0_4 *)&city_window);
      city2 = citywnd_get_city((C_004083b0_4 *)&city_window);
      _DAT_006c31b4 = (int)cities[city2].owner;
      _DAT_006c31b8 = param_1;
      (*(i8 *)((char *)&local_8 + 0)) = 1;
      /* inlined unwind funclet FUN_0050b638 */ { dialog_dtor((Dialog *)((iptr)&local_360)); }
      local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
      /* inlined unwind funclet FUN_0050b644 */ { dialog_dtor((Dialog *)((iptr)&local_954)); }
      local_8 = 0xffffffff;
      /* inlined unwind funclet FUN_0050b650 */ { dialog_dtor((Dialog *)((iptr)&local_654)); }
    }
  }
LAB_0050b666:
  return;
}
#undef blocked_input_kind
#undef city_acquire_wonder_busy
#undef city_create_busy
#undef city_delete_busy
#undef city_dlg_close_pending
#undef civ_check_destroyed_busy
#undef civ_create_busy
#undef civ_eliminate_busy
#undef dlg_pending_idle_callback
#undef human_civ
#undef net_lock_map_busy
#undef net_unlock_map_busy
#undef ui_large_screen
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
#undef _DAT_006c31b0
#undef _DAT_006c31b4
#undef _DAT_006c31b8
#undef improvement
#undef unit_type3
#undef local_954
#undef unit_type
#undef local_65c
#undef local_658
#undef local_654
#undef local_360
#undef local_6c
#undef local_68
#undef local_64
#undef unit_type2
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0050b674 auto */
#define city_dlg_close_pending (*(char *)((u8 *)&g.d_00630d30))
#define dialog_stack_top (*(int * *)((u8 *)&g.d_006ad678))
#define mp_turn_seconds_left (*(int *)((u8 *)&g.d_00633a78))
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
void __cdecl city_change_idle_autoclose(void)

{
  int iVar1;
  
  if (((mp_turn_timer_handle != 0) && (mp_turn_seconds_left < 1)) ||
     (iVar1 = citywnd_get_city((C_004083b0_4 *)&city_window), iVar1 == -1)) {
    if (net_host_flag == '\0') {
      dialog_stack_top[0xf] = dialog_stack_top[0xf] | 0x400;
      wnd_end_modal_loop((C_00408010_b8 *)(*dialog_stack_top + 0x48));
    }
    else if (city_dlg_close_pending == '\0') {
      city_dlg_close_pending = 1;
      city_dlg_close_start_ticks = timer_ticks();
    }
    else {
      iVar1 = timer_ticks();
      if (city_dlg_close_start_ticks + 0x4b0 < iVar1) {
        city_dlg_close_pending = '\0';
        dialog_stack_top[0xf] = dialog_stack_top[0xf] | 0x400;
        wnd_end_modal_loop((C_00408010_b8 *)(*dialog_stack_top + 0x48));
      }
    }
  }
  net_process_messages((NetSession *)&net_session,1,0);
  return;
}
#undef city_dlg_close_pending
#undef dialog_stack_top
#undef mp_turn_seconds_left
#undef net_host_flag

/* 0050b74e auto */
#define blocked_input_kind (*(i32 *)((u8 *)&g.d_006c31ac))
#define city_acquire_wonder_busy (*(int *)((u8 *)&g.d_006ad8e8))
#define city_create_busy (*(int *)((u8 *)&g.d_006ad8c4))
#define city_delete_busy (*(int *)((u8 *)&g.d_006ad8c8))
#define city_dlg_close_pending (*(i8 *)((u8 *)&g.d_00630d30))
#define civ_check_destroyed_busy (*(int *)((u8 *)&g.d_006ad8f4))
#define civ_create_busy (*(int *)((u8 *)&g.d_006ad8f0))
#define civ_eliminate_busy (*(int *)((u8 *)&g.d_006ad8ec))
#define dlg_pending_idle_callback (*(i8 * *)((u8 *)&g.d_00635a3c))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define net_lock_map_busy (*(int *)((u8 *)&g.d_006ad8cc))
#define net_unlock_map_busy (*(int *)((u8 *)&g.d_006ad8d0))
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
#define _DAT_006c31b0 (*(i32 *)((u8 *)&g.d_006c31b0))
#define _DAT_006c31b4 (*(i32 *)((u8 *)&g.d_006c31b4))
#define _DAT_006c31b8 (*(i32 *)((u8 *)&g.d_006c31b8))
#define local_108 (*(i8 (*)[260])(frame_ + FRAME_OFF(0)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl city_button_rename(i32 param_1)

{
  iptr iVar1;
  iptr city2;
  int city;
  i8 *puVar4;
  i8 frame_[FRAME_OFF(264)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = citywnd_get_city((C_004083b0_4 *)&city_window);
  if ((iVar1 != -1) &&
     (city2 = citywnd_get_city((C_004083b0_4 *)&city_window),
     cities[city2].owner == human_civ)) {
    city = XD_InFlushSendBuffer();
    if (((((city == 0) &&
          ((((unit_create_busy == 0 && (unit_delete_busy == 0)) && (city_create_busy == 0)) &&
           ((city_delete_busy == 0 && (net_lock_map_busy == 0)))))) &&
         ((net_unlock_map_busy == 0 &&
          ((((unit_stack_unlink_busy == 0 && (unit_stack_link_busy == 0)) &&
            ((unit_stack_bottom_busy == 0 &&
             (((unit_relocate_busy == 0 && (city_acquire_wonder_busy == 0)) && (civ_eliminate_busy == 0)))))) &&
           ((civ_create_busy == 0 && (civ_check_destroyed_busy == 0)))))))) && (unit_gather_cargo_busy == 0)) &&
       (((unit_lift_off_map_busy == 0 && (unit_delete_cargo_busy == 0)) && (unit_destroy_redraw_busy == 0)))) {
      city_dlg_close_pending = 0;
      dlg_pending_idle_callback = ((void *)ADDR(0x00402815, city_change_idle_autoclose));
      puVar4 = local_108;
      city = citywnd_get_city((C_004083b0_4 *)&city_window);
      city = dlg_game_text_input(ADDR(0x630fb4, ((u8 *)&g.d_00630fb4)),0xf,(iptr)&cities[city].name,(iptr)puVar4);
      if ((city == 0) &&
         (city = citywnd_get_city((C_004083b0_4 *)&city_window), city != -1)) {
        snd_play_effect(0x68,0,0,0);
        puVar4 = local_108;
        city = citywnd_get_city((C_004083b0_4 *)&city_window);
        FUN_005f22d0((iptr)&cities[city].name,puVar4);
        city_window_refresh((FrameWindow *)&city_window);
        map_redraw_all_views(human_civ,1);
      }
      city_dlg_close_pending = 0;
    }
    else {
      dbg_log(ADDR(0x630f68, ((u8 *)&g.d_00630f68)));
      blocked_input_kind = 10;
      _DAT_006c31b0 = citywnd_get_city((C_004083b0_4 *)&city_window);
      city = citywnd_get_city((C_004083b0_4 *)&city_window);
      _DAT_006c31b4 = (int)cities[city].owner;
      _DAT_006c31b8 = param_1;
    }
  }
  return;
}
#undef blocked_input_kind
#undef city_acquire_wonder_busy
#undef city_create_busy
#undef city_delete_busy
#undef city_dlg_close_pending
#undef civ_check_destroyed_busy
#undef civ_create_busy
#undef civ_eliminate_busy
#undef dlg_pending_idle_callback
#undef human_civ
#undef net_lock_map_busy
#undef net_unlock_map_busy
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
#undef _DAT_006c31b0
#undef _DAT_006c31b4
#undef _DAT_006c31b8
#undef local_108

/* 0050b9a4 auto */
#define city_info_panel_mode (*(i32 *)((u8 *)&g.d_006aa768))
void __cdecl city_button_info(i32 param_1)

{
  int iVar1;
  iptr city;
  i32 uVar3;
  
  iVar1 = citywnd_get_city((C_004083b0_4 *)&city_window);
  if (iVar1 != -1) {
    city_info_panel_mode = 0;
    uVar3 = 0;
    city = citywnd_get_city((C_004083b0_4 *)&city_window);
    city_recalc(city,uVar3);
    city_window_draw_info_panel((FrameWindow *)&city_window,1);
    snd_play_effect(99,0,0,0);
  }
  return;
}
#undef city_info_panel_mode

/* 0050ba07 auto */
#define city_info_panel_mode (*(i32 *)((u8 *)&g.d_006aa768))
void __cdecl city_button_map(i32 param_1)

{
  int iVar1;
  iptr city;
  i32 uVar3;
  
  iVar1 = citywnd_get_city((C_004083b0_4 *)&city_window);
  if (iVar1 != -1) {
    city_info_panel_mode = 1;
    uVar3 = 0;
    city = citywnd_get_city((C_004083b0_4 *)&city_window);
    city_recalc(city,uVar3);
    city_window_draw_info_panel((FrameWindow *)&city_window,1);
    snd_play_effect(99,0,0,0);
  }
  return;
}
#undef city_info_panel_mode

/* 0050ba6a auto */
#define city_info_panel_mode (*(i32 *)((u8 *)&g.d_006aa768))
void __cdecl city_button_happy(i32 param_1)

{
  int iVar1;
  iptr city;
  i32 uVar3;
  
  iVar1 = citywnd_get_city((C_004083b0_4 *)&city_window);
  if (iVar1 != -1) {
    city_info_panel_mode = 2;
    uVar3 = 0;
    city = citywnd_get_city((C_004083b0_4 *)&city_window);
    city_recalc(city,uVar3);
    city_window_draw_info_panel((FrameWindow *)&city_window,1);
    snd_play_effect(99,0,0,0);
  }
  return;
}
#undef city_info_panel_mode

/* 0050bacd auto */
#define blocked_input_kind (*(i32 *)((u8 *)&g.d_006c31ac))
#define city_acquire_wonder_busy (*(int *)((u8 *)&g.d_006ad8e8))
#define city_create_busy (*(int *)((u8 *)&g.d_006ad8c4))
#define city_delete_busy (*(int *)((u8 *)&g.d_006ad8c8))
#define civ_check_destroyed_busy (*(int *)((u8 *)&g.d_006ad8f4))
#define civ_create_busy (*(int *)((u8 *)&g.d_006ad8f0))
#define civ_eliminate_busy (*(int *)((u8 *)&g.d_006ad8ec))
#define net_lock_map_busy (*(int *)((u8 *)&g.d_006ad8cc))
#define net_unlock_map_busy (*(int *)((u8 *)&g.d_006ad8d0))
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
#define _DAT_006c31b0 (*(i32 *)((u8 *)&g.d_006c31b0))
#define _DAT_006c31b4 (*(i32 *)((u8 *)&g.d_006c31b4))
#define _DAT_006c31b8 (*(i32 *)((u8 *)&g.d_006c31b8))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl city_button_view(i32 param_1)

{
  iptr iVar1;
  iptr iVar2;
  int city;
  i32 city2;
  
  iVar1 = citywnd_get_city((C_004083b0_4 *)&city_window);
  if (iVar1 != -1) {
    iVar2 = XD_InFlushSendBuffer();
    if (((((((iVar2 == 0) && (unit_create_busy == 0)) && (unit_delete_busy == 0)) &&
          ((city_create_busy == 0 && (city_delete_busy == 0)))) &&
         ((net_lock_map_busy == 0 && ((net_unlock_map_busy == 0 && (unit_stack_unlink_busy == 0)))))) &&
        (unit_stack_link_busy == 0)) &&
       (((((unit_stack_bottom_busy == 0 && (unit_relocate_busy == 0)) && (city_acquire_wonder_busy == 0)) &&
         (((civ_eliminate_busy == 0 && (civ_create_busy == 0)) &&
          ((civ_check_destroyed_busy == 0 && ((unit_gather_cargo_busy == 0 && (unit_lift_off_map_busy == 0)))))))) &&
        ((unit_delete_cargo_busy == 0 && (unit_destroy_redraw_busy == 0)))))) {
      city2 = citywnd_get_city((C_004083b0_4 *)&city_window);
      cityview_open(city2);
    }
    else {
      dbg_log(ADDR(0x630fc0, ((u8 *)&g.d_00630fc0)));
      blocked_input_kind = 9;
      _DAT_006c31b0 = citywnd_get_city((C_004083b0_4 *)&city_window);
      city = citywnd_get_city((C_004083b0_4 *)&city_window);
      _DAT_006c31b4 = (int)cities[city].owner;
      _DAT_006c31b8 = param_1;
    }
  }
  return;
}
#undef blocked_input_kind
#undef city_acquire_wonder_busy
#undef city_create_busy
#undef city_delete_busy
#undef civ_check_destroyed_busy
#undef civ_create_busy
#undef civ_eliminate_busy
#undef net_lock_map_busy
#undef net_unlock_map_busy
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
#undef _DAT_006c31b0
#undef _DAT_006c31b4
#undef _DAT_006c31b8

/* 0050bc4f auto */
#define city_window_exit_requested (*(i32 *)((u8 *)&g.d_00630d18))
void __cdecl city_window_exit_clicked(i32 param_1)

{
  int iVar1;
  
  iVar1 = citywnd_get_city((C_004083b0_4 *)&city_window);
  if (iVar1 != -1) {
    snd_play_effect(99,0,0,0);
    if (city_window_open_mode == 2) {
      city_window_exit_requested = 1;
    }
    else {
      city_window_close();
    }
    advisor_refresh_if_open(1);
    advisor_refresh_if_open(2);
    advisor_refresh_if_open(4);
    advisor_refresh_if_open(5);
    advisor_refresh_if_open(6);
  }
  return;
}
#undef city_window_exit_requested

/* 0050bcda auto */
void __cdecl city_window_on_improvement_scroll(i32 param_1)

{
  iptr city;
  i32 uVar2;
  
  city_improvement_list_top = param_1;
  uVar2 = 0;
  city = citywnd_get_city((C_004083b0_4 *)&city_window);
  city_recalc(city,uVar2);
  city_window_draw_improvements((FrameWindow *)&city_window,1);
  return;
}

/* 0050bd13 auto */
#define city_turn_processing (*(int *)((u8 *)&g.d_0062edf8))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define local_b4 (*(char (*)[80])(frame_ + FRAME_OFF(4)))
#define city (*(iptr *)(frame_ + FRAME_OFF(84)))
#define local_60 (*(char (*)[80])(frame_ + FRAME_OFF(88)))
#define city4 (*(iptr *)(frame_ + FRAME_OFF(168)))
#define city5 (*(iptr *)(frame_ + FRAME_OFF(172)))
#define city2 (*(iptr *)(frame_ + FRAME_OFF(176)))
void __cdecl city_button_next_city(i32 param_1)

{
  iptr iVar1;
  iptr city3;
  int iVar3;
  i8 frame_[FRAME_OFF(184)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = citywnd_get_city((C_004083b0_4 *)&city_window);
  if ((iVar1 != -1) &&
     ((city3 = citywnd_get_city((C_004083b0_4 *)&city_window),
      cities[city3].owner == human_civ || (game.reveal_map != '\0')))) {
    if (city_turn_processing == 0) {
      city5 = citywnd_get_city((C_004083b0_4 *)&city_window);
      city4 = -1;
      city2 = city5;
      FUN_005f22d0(local_60,s__00631008);
      FUN_005f22d0(local_b4,(iptr)&cities[city2].name);
      for (city = 0; city < game.num_cities; city++) {
        if ((cities[city].id != 0) && (cities[city2].owner == cities[city].owner)) {
          iVar3 = __strcmpi(cities[city].name,local_60);
          if ((0 < iVar3) &&
             (iVar3 = __strcmpi(cities[city].name,cities[city2].name), iVar3 < 0)) {
            city4 = city;
            FUN_005f22d0(local_60,(iptr)&cities[city].name);
          }
          iVar3 = __strcmpi(cities[city].name,local_b4);
          if (0 < iVar3) {
            city5 = city;
            FUN_005f22d0(local_b4,(iptr)&cities[city].name);
          }
        }
      }
      if (city4 < 0) {
        if (city2 != city5) {
          city_window_open((C_004083b0_12c *)&city_window,city5);
        }
      }
      else {
        city_window_open((C_004083b0_12c *)&city_window,city4);
      }
    }
    else {
      city_window_modal_notice();
    }
  }
  return;
}
#undef city_turn_processing
#undef human_civ
#undef local_b4
#undef city
#undef local_60
#undef city4
#undef city5
#undef city2

/* 0050bf72 auto */
#define city_turn_processing (*(int *)((u8 *)&g.d_0062edf8))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define local_b4 (*(char (*)[80])(frame_ + FRAME_OFF(4)))
#define city (*(iptr *)(frame_ + FRAME_OFF(84)))
#define local_60 (*(char (*)[80])(frame_ + FRAME_OFF(88)))
#define city4 (*(iptr *)(frame_ + FRAME_OFF(168)))
#define city5 (*(iptr *)(frame_ + FRAME_OFF(172)))
#define city2 (*(iptr *)(frame_ + FRAME_OFF(176)))
void __cdecl city_button_prev_city(i32 param_1)

{
  iptr iVar1;
  iptr city3;
  int iVar3;
  i8 frame_[FRAME_OFF(184)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = citywnd_get_city((C_004083b0_4 *)&city_window);
  if ((iVar1 != -1) &&
     ((city3 = citywnd_get_city((C_004083b0_4 *)&city_window),
      cities[city3].owner == human_civ || (game.reveal_map != '\0')))) {
    if (city_turn_processing == 0) {
      city5 = citywnd_get_city((C_004083b0_4 *)&city_window);
      city4 = -1;
      city2 = city5;
      FUN_005f22d0(local_60,s_zzzzzzzzzzzzzzzzzzzzzzzzz_00631024);
      FUN_005f22d0(local_b4,(iptr)&cities[city2].name);
      for (city = 0; city < game.num_cities; city++) {
        if ((cities[city].id != 0) && (cities[city2].owner == cities[city].owner)) {
          iVar3 = __strcmpi(cities[city].name,local_60);
          if ((iVar3 < 0) &&
             (iVar3 = __strcmpi(cities[city].name,cities[city2].name), 0 < iVar3)) {
            city4 = city;
            FUN_005f22d0(local_60,(iptr)&cities[city].name);
          }
          iVar3 = __strcmpi(cities[city].name,local_b4);
          if (iVar3 < 0) {
            city5 = city;
            FUN_005f22d0(local_b4,(iptr)&cities[city].name);
          }
        }
      }
      if (city4 < 0) {
        if (city5 != city2) {
          city_window_open((C_004083b0_12c *)&city_window,city5);
        }
      }
      else {
        city_window_open((C_004083b0_12c *)&city_window,city4);
      }
    }
    else {
      city_window_modal_notice();
    }
  }
  return;
}
#undef city_turn_processing
#undef human_civ
#undef local_b4
#undef city
#undef local_60
#undef city4
#undef city5
#undef city2

/* 0050c1d1 auto */
#define blocked_input_kind (*(i32 *)((u8 *)&g.d_006c31ac))
#define city_acquire_wonder_busy (*(int *)((u8 *)&g.d_006ad8e8))
#define city_create_busy (*(int *)((u8 *)&g.d_006ad8c4))
#define city_delete_busy (*(int *)((u8 *)&g.d_006ad8c8))
#define civ_check_destroyed_busy (*(int *)((u8 *)&g.d_006ad8f4))
#define civ_create_busy (*(int *)((u8 *)&g.d_006ad8f0))
#define civ_eliminate_busy (*(int *)((u8 *)&g.d_006ad8ec))
#define net_lock_map_busy (*(int *)((u8 *)&g.d_006ad8cc))
#define net_unlock_map_busy (*(int *)((u8 *)&g.d_006ad8d0))
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
#define _DAT_006c31b0 (*(i32 *)((u8 *)&g.d_006c31b0))
#define _DAT_006c31b4 (*(i32 *)((u8 *)&g.d_006c31b4))
#define _DAT_006c31b8 (*(i32 *)((u8 *)&g.d_006c31b8))
#define _DAT_006c31bc (*(i32 *)((u8 *)&g.d_006c31bc))
#define _DAT_006c31c0 (*(i32 *)((u8 *)&g.d_006c31c0))
#define unit (*(int *)(frame_ + FRAME_OFF(0)))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl city_window_on_mouse(i32 param_1,i32 param_2,i32 param_3)

{
  iptr iVar1;
  iptr city;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = XD_InFlushSendBuffer();
  if (((((((iVar1 == 0) && (unit_create_busy == 0)) && (unit_delete_busy == 0)) &&
        ((city_create_busy == 0 && (city_delete_busy == 0)))) &&
       ((net_lock_map_busy == 0 && ((net_unlock_map_busy == 0 && (unit_stack_unlink_busy == 0)))))) && (unit_stack_link_busy == 0)
      ) && (((((unit_stack_bottom_busy == 0 && (unit_relocate_busy == 0)) && (city_acquire_wonder_busy == 0)) &&
             (((civ_eliminate_busy == 0 && (civ_create_busy == 0)) &&
              ((civ_check_destroyed_busy == 0 && ((unit_gather_cargo_busy == 0 && (unit_lift_off_map_busy == 0)))))))) &&
            ((unit_delete_cargo_busy == 0 && (unit_destroy_redraw_busy == 0)))))) {
    local_c = clickmap_hit_test
                        ((ClickMapHitTestView *)&city_window_clickmap,param_1,param_2,(iptr)&unit,(iptr)&local_8)
    ;
    if (-1 < local_c) {
      switch(local_8) {
      case 1:
        city_window_toggle_worked_tile(param_1,param_2);
        break;
      case 2:
        city_window_cycle_specialist(unit);
        break;
      case 3:
        city_window_present_unit_menu(unit);
        break;
      case 4:
        city_window_sell_improvement(unit);
        break;
      case 5:
        break;
      case 6:
        city_window_supported_unit_menu(unit);
      }
    }
  }
  else {
    dbg_log(ADDR(0x631040, ((u8 *)&g.d_00631040)));
    blocked_input_kind = 6;
    _DAT_006c31b0 = citywnd_get_city((C_004083b0_4 *)&city_window);
    city = citywnd_get_city((C_004083b0_4 *)&city_window);
    _DAT_006c31b4 = (int)cities[city].owner;
    _DAT_006c31b8 = param_1;
    _DAT_006c31bc = param_2;
    _DAT_006c31c0 = param_3;
  }
  return;
}
#undef blocked_input_kind
#undef city_acquire_wonder_busy
#undef city_create_busy
#undef city_delete_busy
#undef civ_check_destroyed_busy
#undef civ_create_busy
#undef civ_eliminate_busy
#undef net_lock_map_busy
#undef net_unlock_map_busy
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
#undef _DAT_006c31b0
#undef _DAT_006c31b4
#undef _DAT_006c31b8
#undef _DAT_006c31bc
#undef _DAT_006c31c0
#undef unit
#undef local_c
#undef local_8

/* 0050c405 auto */
void __cdecl city_window_on_lbuttonup(i32 param_1,i32 param_2)

{
  city_window_on_mouse(param_1,param_2,0);
  return;
}

/* 0050c427 auto */
void __cdecl city_window_on_rbuttonup(i32 param_1,i32 param_2)

{
  city_window_on_mouse(param_1,param_2,1);
  return;
}

/* 0050c449 auto */
void __thiscall city_window_close_if_city(C_004083b0_4 *this,iptr param_1)

{
  if (((int)this[0x567].field_0 <= param_1) && (param_1 <= (int)this[0x567].field_0)) {
    city_window_close();
  }
  return;
}

/* 0050c494 auto */
void __thiscall
city_window_on_unit_change(FrameWindow *this,iptr unit,iptr param_2,iptr param_3)

{
  if ((((*(int *)(this[7].pad_15c + 0xc) == 0) && (*(int *)(this[7].pad_15c + 8) == 0)) &&
      (*(int *)(this[7].pad_15c + 0x10) == 0)) && (-1 < *(int *)(this[7].pad_15c + 4))) {
    if (unit < 0) {
      if ((cities[*(int *)(this[7].pad_15c + 4)].x == param_2) &&
         (cities[*(int *)(this[7].pad_15c + 4)].y == param_3)) {
        city_recalc(*(iptr *)(this[7].pad_15c + 4),0);
        city_window_draw_info_panel(this,1);
        city_window_draw_production(this,1);
      }
    }
    else if (((cities[*(int *)(this[7].pad_15c + 4)].x == units[unit].x) &&
             (cities[*(int *)(this[7].pad_15c + 4)].y == units[unit].y)) ||
            ((cities[*(int *)(this[7].pad_15c + 4)].x == param_2 &&
             (cities[*(int *)(this[7].pad_15c + 4)].y == param_3)))) {
      city_recalc(*(iptr *)(this[7].pad_15c + 4),0);
      city_window_draw_info_panel(this,1);
      city_window_draw_production(this,1);
      if ((uint)(byte)units[unit].home_city == *(uint *)(this[7].pad_15c + 4)) {
        city_recalc(*(iptr *)(this[7].pad_15c + 4),1);
        city_window_draw_supported_units(this,1);
        city_window_recalc_redraw((C_004083b0_4 *)this,0);
      }
    }
  }
  return;
}

/* 0050c679 auto */
void __thiscall city_window_refresh_if_city(FrameWindow *this,iptr param_1)

{
  if ((((*(int *)(this[7].pad_15c + 0xc) == 0) && (*(int *)(this[7].pad_15c + 8) == 0)) &&
      (*(int *)(this[7].pad_15c + 0x10) == 0)) &&
     ((*(int *)(this[7].pad_15c + 4) == param_1 && (-1 < param_1)))) {
    city_window_refresh(this);
  }
  return;
}

/* 0050c6ef auto */
void __thiscall city_window_refresh_if_near(C_004083b0_4 *this,i32 param_1,i32 param_2)

{
  int iVar1;
  
  if ((((this[0x569].field_0 == 0) && (this[0x568].field_0 == 0)) && (this[0x56a].field_0 == 0)) &&
     ((-1 < (int)this[0x567].field_0 &&
      (iVar1 = map_distance_diag(param_1,param_2,(int)cities[this[0x567].field_0].x,
                                  (int)cities[this[0x567].field_0].y), iVar1 < 3)))) {
    city_window_recalc_redraw(this,0);
  }
  return;
}

/* 0050c7a3 auto */
void __thiscall city_window_clear_controls(C_004083b0_4 *this)

{
  this[0x5ad].field_0 = 0;
  this[0x5ae].field_0 = 0;
  this[0x5af].field_0 = 0;
  this[0x5b0].field_0 = this[0x5af].field_0;
  this[0x5b2].field_0 = this[0x5b0].field_0;
  this[0x5b4].field_0 = this[0x5b2].field_0;
  this[0x5b3].field_0 = this[0x5b4].field_0;
  this[0x5b1].field_0 = this[0x5b3].field_0;
  this[0x5b6].field_0 = 0;
  this[0x5b5].field_0 = this[0x5b6].field_0;
  return;
}

/* 0050c859 auto */
void __thiscall city_window_destroy_controls(C_004083b0_4 *this)

{
  if (this[0x5ad].field_0 != 0) {
    wnd_remove_all_controls((WndControlRemoveView *)(this + 0x12));
    if ((Control *)this[0x5ad].field_0 != (Control *)0x0) {
      ctrl_scalar_dtor((Control *)this[0x5ad].field_0,1);
    }
    if ((Control *)this[0x5ae].field_0 != (Control *)0x0) {
      ctrl_scalar_dtor((Control *)this[0x5ae].field_0,1);
    }
    if ((Control *)this[0x5b1].field_0 != (Control *)0x0) {
      ctrl_scalar_dtor((Control *)this[0x5b1].field_0,1);
    }
    if ((Control *)this[0x5b3].field_0 != (Control *)0x0) {
      ctrl_scalar_dtor((Control *)this[0x5b3].field_0,1);
    }
    if ((Control *)this[0x5b4].field_0 != (Control *)0x0) {
      ctrl_scalar_dtor((Control *)this[0x5b4].field_0,1);
    }
    if ((Control *)this[0x5b2].field_0 != (Control *)0x0) {
      ctrl_scalar_dtor((Control *)this[0x5b2].field_0,1);
    }
    if ((Control *)this[0x5b0].field_0 != (Control *)0x0) {
      ctrl_scalar_dtor((Control *)this[0x5b0].field_0,1);
    }
    if (this[0x5af].field_0 != 0) {
      if ((Control *)this[0x5af].field_0 != (Control *)0x0) {
        ctrl_scalar_dtor((Control *)this[0x5af].field_0,1);
      }
      this[0x5af].field_0 = 0;
    }
    if ((C_00511560 *)this[0x5b5].field_0 != (C_00511560 *)0x0) {
      spritebtn_scalar_dtor((C_00511560 *)this[0x5b5].field_0,1);
    }
    if ((C_00511560 *)this[0x5b6].field_0 != (C_00511560 *)0x0) {
      spritebtn_scalar_dtor((C_00511560 *)this[0x5b6].field_0,1);
    }
    if ((Control *)this[0x5b7].field_0 != (Control *)0x0) {
      scrollbar_scalar_dtor((Control *)this[0x5b7].field_0,1);
    }
    city_window_clear_controls(this);
  }
  return;
}

/* 0050ca8d auto */
#define local_30 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define local_20 (*(i8 (*)[16])(frame_ + FRAME_OFF(16)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(32)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(36)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(40)))
/* WARNING: Removing unreachable block (ram,0x0050cc02) */

void __thiscall city_window_create_exit_button(C_004083b0_12c *this,int param_1)

{
  Control *this_00;
  iptr iVar1;
  iptr iVar2;
  int iVar3;
  i32 uVar4;
  int iVar5;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  if (*(int *)(this[0x13].pad_48 + 0x30) != 0) {
    if (*(Control **)(this[0x13].pad_48 + 0x30) != (Control *)0x0) {
      ctrl_scalar_dtor(*(Control **)(this[0x13].pad_48 + 0x30),1);
    }
    this[0x13].pad_48[0x30] = '\0';
    this[0x13].pad_48[0x31] = '\0';
    this[0x13].pad_48[0x32] = '\0';
    this[0x13].pad_48[0x33] = '\0';
  }
  this_00 = operator_new(0x3c);
  local_8 = 0;
  if (this_00 == (Control *)0x0) {
    local_30 = 0;
  }
  else {
    local_30 = button_ctor(this_00);
  }
  local_8 = 0xffffffff;
  *(i32 *)(this[0x13].pad_48 + 0x30) = local_30;
  ui_set_button_font((iptr)(this[0x13].pad_48 + 0x20));
  iVar1 = city_window_scale((C_004083b0_4 *)this,0x18);
  iVar2 = city_window_scale((C_004083b0_4 *)this,0x39);
  iVar3 = city_window_scale((C_004083b0_4 *)this,0x16c);
  iVar5 = *(int *)(this[0x12].pad_48 + 0x68) + iVar3 + this->client_y;
  iVar3 = city_window_scale((C_004083b0_4 *)this,0x1cb);
  rect_set_xywh((iptr)local_20,this->client_x + iVar3 + *(int *)(this[0x12].pad_48 + 100),
                     iVar5,iVar2,iVar1);
  uVar4 = city_window_scale((C_004083b0_4 *)this,0x19);
  iVar3 = city_window_scale((C_004083b0_4 *)this,0x3a);
  iVar5 = city_window_scale((C_004083b0_4 *)this,0x3a);
  rect_offset((iptr)local_20,iVar3 + iVar5,uVar4);
  iVar1 = label_string(*(i32 *)
                              (label_string_ids + 0x94 +
                              (-(uint)(*(int *)(this[0x12].pad_48 + 0x4c) == 2) & 0xcc) * 4));
  button_create
            (*(Control **)(this[0x13].pad_48 + 0x30),ADDR(0x6a9200, ((u8 *)&g.d_006a9200)),8,(iptr)local_20,iVar1);
  ctrl_set_cancel_button(*(Control **)(this[0x13].pad_48 + 0x30));
  button_set_callback(*(Control **)(this[0x13].pad_48 + 0x30),ADDR(0x4034e5, city_window_exit_clicked));
  if (param_1 != 0) {
    ctrl_show_and_redraw(*(Control **)(this[0x13].pad_48 + 0x30));
  }
  return;
}
#undef local_30
#undef local_20
#undef local_10
#undef puStack_c
#undef local_8

/* 0050ccb3 auto */
#define city_change_button_variant (*(char *)((u8 *)&g.d_00630d24))
#define local_3c (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_24 (*(i8 (*)[16])(frame_ + FRAME_OFF(28)))
#define local_14 (*(char *)(frame_ + FRAME_OFF(44)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(48)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(52)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(56)))
/* WARNING: Removing unreachable block (ram,0x0050ce6a) */

void __thiscall city_window_create_change_button(C_004083b0_12c *this,int param_1)

{
  int iVar1;
  u32 uVar2;
  u32 uVar3;
  Control *this_00;
  iptr iVar4;
  iptr iVar5;
  int iVar6;
  int iVar7;
  i32 uVar8;
  i32 uVar9;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  local_14 = (cities[*(int *)(this[0x12].pad_48 + 0x3c)].flags & 0x10) != 0;
  if (city_change_button_variant != local_14) {
    city_change_button_variant = local_14;
    if (*(int *)(this[0x13].pad_48 + 0x2c) != 0) {
      if (*(Control **)(this[0x13].pad_48 + 0x2c) != (Control *)0x0) {
        ctrl_scalar_dtor(*(Control **)(this[0x13].pad_48 + 0x2c),1);
      }
      this[0x13].pad_48[0x2c] = '\0';
      this[0x13].pad_48[0x2d] = '\0';
      this[0x13].pad_48[0x2e] = '\0';
      this[0x13].pad_48[0x2f] = '\0';
    }
    this_00 = operator_new(0x3c);
    local_8 = 0;
    if (this_00 == (Control *)0x0) {
      local_3c = 0;
    }
    else {
      local_3c = button_ctor(this_00);
    }
    local_8 = 0xffffffff;
    *(i32 *)(this[0x13].pad_48 + 0x2c) = local_3c;
    ui_set_button_font((iptr)(this[0x13].pad_48 + 0x20));
    iVar1 = *(int *)(this[0x12].pad_48 + 100);
    uVar2 = this->client_x;
    uVar3 = this->client_y;
    iVar7 = *(int *)(this[0x12].pad_48 + 0x68);
    iVar4 = city_window_scale((C_004083b0_4 *)this,0x18);
    iVar5 = city_window_scale((C_004083b0_4 *)this,0x44);
    iVar6 = city_window_scale((C_004083b0_4 *)this,0xb5);
    iVar6 = uVar3 + iVar7 + iVar6;
    iVar7 = city_window_scale((C_004083b0_4 *)this,0x1ba);
    rect_set_xywh((iptr)local_24,iVar1 + uVar2 + iVar7,iVar6,iVar5,iVar4);
    uVar9 = 0;
    uVar8 = city_window_scale((C_004083b0_4 *)this,0x73);
    rect_offset((iptr)local_24,uVar8,uVar9);
    iVar4 = label_string(*(i32 *)
                                (label_string_ids + 0x510 +
                                (-(uint)(local_14 == '\0') & 0xfffffee0) * 4));
    button_create
              (*(Control **)(this[0x13].pad_48 + 0x2c),ADDR(0x6a9200, ((u8 *)&g.d_006a9200)),2,(iptr)local_24,iVar4);
    button_set_callback(*(Control **)(this[0x13].pad_48 + 0x2c),ADDR(0x4021d5, city_button_change));
    if (param_1 != 0) {
      ctrl_show_and_redraw(*(Control **)(this[0x13].pad_48 + 0x2c));
    }
  }
  return;
}
#undef city_change_button_variant
#undef local_3c
#undef local_24
#undef local_14
#undef local_10
#undef puStack_c
#undef local_8

/* 0050cf06 auto */
#define city_change_button_variant (*(i8 *)((u8 *)&g.d_00630d24))
#define local_90 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_80 (*(i32 *)(frame_ + FRAME_OFF(16)))
#define local_7c (*(Control * *)(frame_ + FRAME_OFF(20)))
#define local_78 (*(i32 *)(frame_ + FRAME_OFF(24)))
#define local_74 (*(SpriteButton * *)(frame_ + FRAME_OFF(28)))
#define local_70 (*(i32 *)(frame_ + FRAME_OFF(32)))
#define local_6c (*(SpriteButton * *)(frame_ + FRAME_OFF(36)))
#define local_68 (*(i32 *)(frame_ + FRAME_OFF(40)))
#define local_64 (*(Control * *)(frame_ + FRAME_OFF(44)))
#define local_60 (*(i32 *)(frame_ + FRAME_OFF(48)))
#define local_5c (*(Control * *)(frame_ + FRAME_OFF(52)))
#define local_58 (*(i32 *)(frame_ + FRAME_OFF(56)))
#define local_54 (*(Control * *)(frame_ + FRAME_OFF(60)))
#define local_50 (*(i32 *)(frame_ + FRAME_OFF(64)))
#define local_4c (*(Control * *)(frame_ + FRAME_OFF(68)))
#define local_48 (*(i32 *)(frame_ + FRAME_OFF(72)))
#define local_44 (*(Control * *)(frame_ + FRAME_OFF(76)))
#define local_40 (*(i32 *)(frame_ + FRAME_OFF(80)))
#define local_3c (*(Control * *)(frame_ + FRAME_OFF(84)))
#define local_38 (*(i32 *)(frame_ + FRAME_OFF(88)))
#define local_34 (*(Control * *)(frame_ + FRAME_OFF(92)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(96)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(100)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(104)))
#define local_24 (*(i8 *)(frame_ + FRAME_OFF(108)))
#define local_23 (*(i8 *)(frame_ + FRAME_OFF(109)))
#define local_20 (*(i8 (*)[16])(frame_ + FRAME_OFF(112)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(128)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(132)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(136)))
/* WARNING: Removing unreachable block (ram,0x0050d785) */
/* WARNING: Removing unreachable block (ram,0x0050d64a) */
/* WARNING: Removing unreachable block (ram,0x0050d52c) */
/* WARNING: Removing unreachable block (ram,0x0050d3ea) */
/* WARNING: Removing unreachable block (ram,0x0050d307) */
/* WARNING: Removing unreachable block (ram,0x0050d471) */
/* WARNING: Removing unreachable block (ram,0x0050d5bb) */
/* WARNING: Removing unreachable block (ram,0x0050d6f6) */
/* WARNING: Removing unreachable block (ram,0x0050d871) */

void __thiscall city_window_create_controls(C_004083b0_12c *this)

{
  iptr iVar1;
  iptr iVar2;
  int iVar3;
  int iVar4;
  i32 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  i32 uVar9;
  i8 frame_[FRAME_OFF(144)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  wnd_set_keyboard_nav((Wnd *)this->pad_48,0);
  city_window_destroy_controls((C_004083b0_4 *)this);
  local_34 = operator_new(0x3c);
  local_8 = 0;
  if (local_34 == (Control *)0x0) {
    local_38 = 0;
  }
  else {
    local_38 = button_ctor(local_34);
  }
  local_8 = 0xffffffff;
  *(i32 *)(this[0x13].pad_48 + 0x28) = local_38;
  local_3c = operator_new(0x3c);
  local_8 = 1;
  if (local_3c == (Control *)0x0) {
    local_40 = 0;
  }
  else {
    local_40 = button_ctor(local_3c);
  }
  local_8 = 0xffffffff;
  *(i32 *)(this[0x13].pad_48 + 0x2c) = local_40;
  local_44 = operator_new(0x3c);
  local_8 = 2;
  if (local_44 == (Control *)0x0) {
    local_48 = 0;
  }
  else {
    local_48 = button_ctor(local_44);
  }
  local_8 = 0xffffffff;
  *(i32 *)(this[0x13].pad_48 + 0x38) = local_48;
  local_4c = operator_new(0x3c);
  local_8 = 3;
  if (local_4c == (Control *)0x0) {
    local_50 = 0;
  }
  else {
    local_50 = button_ctor(local_4c);
  }
  local_8 = 0xffffffff;
  *(i32 *)(this[0x13].pad_48 + 0x40) = local_50;
  local_54 = operator_new(0x3c);
  local_8 = 4;
  if (local_54 == (Control *)0x0) {
    local_58 = 0;
  }
  else {
    local_58 = button_ctor(local_54);
  }
  local_8 = 0xffffffff;
  *(i32 *)(this[0x13].pad_48 + 0x44) = local_58;
  local_5c = operator_new(0x3c);
  local_8 = 5;
  if (local_5c == (Control *)0x0) {
    local_60 = 0;
  }
  else {
    local_60 = button_ctor(local_5c);
  }
  local_8 = 0xffffffff;
  *(i32 *)(this[0x13].pad_48 + 0x3c) = local_60;
  local_64 = operator_new(0x3c);
  local_8 = 6;
  if (local_64 == (Control *)0x0) {
    local_68 = 0;
  }
  else {
    local_68 = button_ctor(local_64);
  }
  local_8 = 0xffffffff;
  *(i32 *)(this[0x13].pad_48 + 0x34) = local_68;
  local_6c = operator_new(0xcc);
  local_8 = 7;
  if (local_6c == (SpriteButton *)0x0) {
    local_70 = 0;
  }
  else {
    local_70 = spritebtn_ctor(local_6c);
  }
  local_8 = 0xffffffff;
  *(i32 *)(this[0x13].pad_48 + 0x48) = local_70;
  local_74 = operator_new(0xcc);
  local_8 = 8;
  if (local_74 == (SpriteButton *)0x0) {
    local_78 = 0;
  }
  else {
    local_78 = spritebtn_ctor(local_74);
  }
  local_8 = 0xffffffff;
  *(i32 *)(this[0x13].pad_48 + 0x4c) = local_78;
  local_7c = operator_new(0x40);
  local_8 = 9;
  if (local_7c == (Control *)0x0) {
    local_80 = 0;
  }
  else {
    local_80 = scrollbar_ctor(local_7c);
  }
  local_8 = 0xffffffff;
  *(i32 *)(this[0x13].pad_48 + 0x50) = local_80;
  local_28 = *(int *)(this[0x12].pad_48 + 100) + this->client_x;
  local_2c = this->client_y + *(int *)(this[0x12].pad_48 + 0x68);
  ui_set_button_font((iptr)(this[0x13].pad_48 + 0x20));
  city_window_create_exit_button(this,0);
  iVar1 = city_window_scale((C_004083b0_4 *)this,0x18);
  iVar2 = city_window_scale((C_004083b0_4 *)this,0x44);
  iVar3 = city_window_scale((C_004083b0_4 *)this,0xb5);
  iVar3 = local_2c + iVar3;
  iVar4 = city_window_scale((C_004083b0_4 *)this,0x1ba);
  rect_set_xywh((iptr)local_20,local_28 + iVar4,iVar3,iVar2,iVar1);
  iVar1 = label_string(*(i32 *)(label_string_ids + 0x8c));
  button_create
            (*(Control **)(this[0x13].pad_48 + 0x28),ADDR(0x6a9200, ((u8 *)&g.d_006a9200)),1,(iptr)local_20,iVar1);
  button_set_callback(*(Control **)(this[0x13].pad_48 + 0x28),ADDR(0x402c57, city_button_buy));
  city_change_button_variant = 0xff;
  city_window_create_change_button(this,0);
  iVar1 = city_window_scale((C_004083b0_4 *)this,0x18);
  iVar2 = city_window_scale((C_004083b0_4 *)this,0x15);
  iVar3 = city_window_scale((C_004083b0_4 *)this,0x16c);
  iVar3 = local_2c + iVar3;
  iVar4 = city_window_scale((C_004083b0_4 *)this,0x1b5);
  rect_set_xywh((iptr)local_20,local_28 + iVar4,iVar3,iVar2,iVar1);
  local_23 = 0;
  local_24 = 0x5e;
  spritebtn_create_icon_button(ADDR(0x6a9200, ((u8 *)&g.d_006a9200)),9,*(i32 *)(this[0x13].pad_48 + 0x48),ADDR(0x644770, ((u8 *)&g.d_00644770)),(iptr)local_20);
  spritebtn_set_click_handler(*(C_005117f0 **)(this[0x13].pad_48 + 0x48),ADDR(0x40370b, city_button_prev_city));
  uVar5 = city_window_scale((C_004083b0_4 *)this,0x19);
  rect_offset((iptr)local_20,0,uVar5);
  local_24 = 0x76;
  spritebtn_create_icon_button(ADDR(0x6a9200, ((u8 *)&g.d_006a9200)),10,*(i32 *)(this[0x13].pad_48 + 0x4c),ADDR(0x6480d8, ((u8 *)&g.d_006480d8)),(iptr)local_20);
  spritebtn_set_click_handler(*(C_005117f0 **)(this[0x13].pad_48 + 0x4c),ADDR(0x402964, city_button_next_city));
  iVar1 = city_window_scale((C_004083b0_4 *)this,0x18);
  iVar2 = city_window_scale((C_004083b0_4 *)this,0x39);
  iVar3 = city_window_scale((C_004083b0_4 *)this,0x16c);
  iVar3 = local_2c + iVar3;
  iVar4 = city_window_scale((C_004083b0_4 *)this,0x1cb);
  rect_set_xywh((iptr)local_20,local_28 + iVar4,iVar3,iVar2,iVar1);
  iVar1 = label_string(*(i32 *)(label_string_ids + 0x9c));
  button_create
            (*(Control **)(this[0x13].pad_48 + 0x38),ADDR(0x6a9200, ((u8 *)&g.d_006a9200)),3,(iptr)local_20,iVar1);
  button_set_callback(*(Control **)(this[0x13].pad_48 + 0x38),ADDR(0x402482, city_button_info));
  uVar9 = 0;
  uVar5 = city_window_scale((C_004083b0_4 *)this,0x3a);
  rect_offset((iptr)local_20,uVar5,uVar9);
  iVar1 = label_string(*(i32 *)(label_string_ids + 0xa4));
  button_create
            (*(Control **)(this[0x13].pad_48 + 0x40),ADDR(0x6a9200, ((u8 *)&g.d_006a9200)),4,(iptr)local_20,iVar1);
  button_set_callback(*(Control **)(this[0x13].pad_48 + 0x40),ADDR(0x401217, city_button_map));
  uVar9 = 0;
  uVar5 = city_window_scale((C_004083b0_4 *)this,0x3a);
  rect_offset((iptr)local_20,uVar5,uVar9);
  iVar1 = label_string(*(i32 *)(label_string_ids + 0xa8));
  button_create
            (*(Control **)(this[0x13].pad_48 + 0x44),ADDR(0x6a9200, ((u8 *)&g.d_006a9200)),5,(iptr)local_20,iVar1);
  button_set_callback(*(Control **)(this[0x13].pad_48 + 0x44),ADDR(0x401e97, city_button_rename));
  uVar5 = city_window_scale((C_004083b0_4 *)this,0x19);
  iVar3 = city_window_scale((C_004083b0_4 *)this,0xffffffc6);
  iVar4 = city_window_scale((C_004083b0_4 *)this,0xffffffc6);
  rect_offset((iptr)local_20,iVar3 + iVar4,uVar5);
  iVar1 = label_string(*(i32 *)(label_string_ids + 0xa0));
  button_create
            (*(Control **)(this[0x13].pad_48 + 0x3c),ADDR(0x6a9200, ((u8 *)&g.d_006a9200)),6,(iptr)local_20,iVar1);
  button_set_callback(*(Control **)(this[0x13].pad_48 + 0x3c),ADDR(0x40304e, city_button_happy));
  uVar9 = 0;
  uVar5 = city_window_scale((C_004083b0_4 *)this,0x3a);
  rect_offset((iptr)local_20,uVar5,uVar9);
  iVar1 = label_string(*(i32 *)(label_string_ids + 0x98));
  button_create
            (*(Control **)(this[0x13].pad_48 + 0x34),ADDR(0x6a9200, ((u8 *)&g.d_006a9200)),7,(iptr)local_20,iVar1);
  button_set_callback(*(Control **)(this[0x13].pad_48 + 0x34),ADDR(0x402ec3, city_button_view));
  local_30 = GetSystemMetrics(2);
  iVar4 = city_window_scale((C_004083b0_4 *)this,0x83);
  iVar4 -= 2;
  iVar3 = local_30;
  iVar6 = city_window_scale((C_004083b0_4 *)this,0x122);
  iVar8 = local_2c + iVar6 + 1;
  iVar6 = city_window_scale((C_004083b0_4 *)this,0xc0);
  iVar7 = city_window_scale((C_004083b0_4 *)this,0);
  rect_set_xywh((iptr)(this[0x13].pad_48 + 0x10),(iVar6 + iVar7 + local_28) - (local_30 + 1),
                     iVar8,iVar3,iVar4);
  scrollbar_create
            (*(Control **)(this[0x13].pad_48 + 0x50),ADDR(0x6a9200, ((u8 *)&g.d_006a9200)),99,
             (iptr)(this[0x13].pad_48 + 0x10),1);
  iVar3 = rect_height((iptr)&this[0x13].field_28);
  iVar4 = city_window_scale((C_004083b0_4 *)this,1);
  iVar6 = city_window_scale((C_004083b0_4 *)this,0xc);
  scrollbar_set_page_size
            (*(Control **)(this[0x13].pad_48 + 0x50),(iVar3 - (iVar4 >> 1)) / iVar6);
  scrollbar_set_callback(*(Control **)(this[0x13].pad_48 + 0x50),ADDR(0x402f4f, city_window_on_improvement_scroll));
  scrollbar_set_track_callback(*(ScrollbarTrackSetView **)(this[0x13].pad_48 + 0x50),ADDR(0x402f4f, city_window_on_improvement_scroll));
  iVar3 = *(int *)(this[0x12].pad_48 + 0x74);
  if (iVar3 == 1) {
    this[0x12].pad_48[0x78] = 0xfb;
    this[0x12].pad_48[0x79] = 0xff;
    this[0x12].pad_48[0x7a] = 0xff;
    this[0x12].pad_48[0x7b] = 0xff;
  }
  else if (iVar3 == 2) {
    this[0x12].pad_48[0x78] = 0xfe;
    this[0x12].pad_48[0x79] = 0xff;
    this[0x12].pad_48[0x7a] = 0xff;
    this[0x12].pad_48[0x7b] = 0xff;
  }
  else if (iVar3 == 3) {
    this[0x12].pad_48[0x78] = 1;
    this[0x12].pad_48[0x79] = '\0';
    this[0x12].pad_48[0x7a] = '\0';
    this[0x12].pad_48[0x7b] = '\0';
  }
  if (*(int *)(this[0x12].pad_48 + 0x78) != city_tile_pick_zoom_cached) {
    city_tile_pick_zoom_cached = *(int *)(this[0x12].pad_48 + 0x78);
    uVar5 = gfx_zoom_scale(0x20,*(i32 *)(this[0x12].pad_48 + 0x78));
    uVar9 = gfx_zoom_scale(0x40,*(i32 *)(this[0x12].pad_48 + 0x78));
    surface_create((DibSurface *)&city_tile_pick_surface,uVar9,uVar5);
    gfx_set_zoom_scale(*(i32 *)(this[0x12].pad_48 + 0x78));
    sprite_draw((Sprite *)&tile_pick_mask_sprite,(iptr)local_90,ADDR(0x6a9120, ((u8 *)&g.d_006a9120)),0,0);
    gfx_reset_zoom_scale();
  }
  return;
}
#undef city_change_button_variant
#undef local_90
#undef local_80
#undef local_7c
#undef local_78
#undef local_74
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
#undef local_38
#undef local_34
#undef local_30
#undef local_2c
#undef local_28
#undef local_24
#undef local_23
#undef local_20
#undef local_10
#undef puStack_c
#undef local_8

/* 0050dada auto */
#define city_window_exit_btn_pending (*(i8 *)((u8 *)&g.d_00630d20))
void __thiscall city_window_begin_notice(C_004083b0_4 *this)

{
  if (this[0x569].field_0 == 0) {
    this[0x56b].field_0 = 2;
  }
  else {
    this[0x56b].field_0 = 1;
  }
  if (this[0x569].field_0 == 0) {
    city_window_exit_btn_pending = 1;
  }
  return;
}
#undef city_window_exit_btn_pending

/* 0050db36 auto */
#define city_window_exit_btn_pending (*(i8 *)((u8 *)&g.d_00630d20))
void __thiscall city_window_end_notice(C_004083b0_12c *this)

{
  int iVar1;
  
  iVar1 = *(int *)(this[0x12].pad_48 + 0x4c);
  this[0x12].pad_48[0x4c] = '\0';
  this[0x12].pad_48[0x4d] = '\0';
  this[0x12].pad_48[0x4e] = '\0';
  this[0x12].pad_48[0x4f] = '\0';
  if (iVar1 == 2) {
    city_window_create_exit_button(this,1);
  }
  city_window_exit_btn_pending = 0;
  return;
}
#undef city_window_exit_btn_pending

/* 0050db92 auto */
void __cdecl city_window_on_size(void)

{
  wnd_get_rect_in_parent((WndBase *)&city_window_wnd,ADDR(0x655344, ((u8 *)&g.d_00655344)));
  return;
}

/* 0050dbb8 auto */
void __cdecl city_window_on_move(void)

{
  wnd_get_rect_in_parent((WndBase *)&city_window_wnd,ADDR(0x655344, ((u8 *)&g.d_00655344)));
  return;
}

/* 0050dbde auto */
#define city_window_size_level (*(int *)((u8 *)&g.d_006aa78c))
void __cdecl city_window_on_caption_button(int param_1)

{
  if (param_1 == 1) {
    city_window_exit_clicked(0);
  }
  else if (param_1 == 2) {
    if (1 < city_window_size_level) {
      city_window_size_level--;
      city_window_calc_rect();
      wnd_move_to_rect((WndBase *)&city_window_wnd,ADDR(0x655344, ((u8 *)&g.d_00655344)));
    }
  }
  else if ((param_1 == 3) && ((city_window_size_level < 2 || ((city_window_size_level < 3 && (999 < screen_width)))))) {
    city_window_size_level++;
    city_window_calc_rect();
    wnd_move_to_rect((WndBase *)&city_window_wnd,ADDR(0x655344, ((u8 *)&g.d_00655344)));
  }
  return;
}
#undef city_window_size_level

/* 0050dcb6 auto */
#define saved_layout_valid (*(int *)((u8 *)&g.d_00655280))
#define turn_resume_civ (*(char *)((u8 *)&g.d_00628048))
void __thiscall city_window_create(FrameWindow *this)

{
  int iVar1;
  int iVar2;
  i32 uVar3;
  i32 uVar4;
  i32 uVar5;
  i32 uVar6;
  i32 uVar7;
  i32 uVar8;
  i32 uVar9;
  
  city_window_reset_state(this);
  this[7].pad_15c[0x14] = '\0';
  this[7].pad_15c[0x15] = '\0';
  this[7].pad_15c[0x16] = '\0';
  this[7].pad_15c[0x17] = '\0';
  this[7].pad_15c[0x30] = '\0';
  this[7].pad_15c[0x31] = '\0';
  this[7].pad_15c[0x32] = '\0';
  this[7].pad_15c[0x33] = '\0';
  *(i32 *)(this[7].pad_15c + 0x2c) = *(i32 *)(this[7].pad_15c + 0x30);
  this[7].pad_15c[0x38] = 0xff;
  this[7].pad_15c[0x39] = 0xff;
  this[7].pad_15c[0x3a] = 0xff;
  this[7].pad_15c[0x3b] = 0xff;
  *(i32 *)(this[7].pad_15c + 0x34) = *(i32 *)(this[7].pad_15c + 0x38);
  this[7].pad_15c[8] = '\0';
  this[7].pad_15c[9] = '\0';
  this[7].pad_15c[10] = '\0';
  this[7].pad_15c[0xb] = '\0';
  if ((turn_resume_civ == '\0') || (saved_layout_valid == 0)) {
    city_window_init_size();
  }
  uVar9 = 8;
  uVar8 = 0x18;
  uVar7 = 0;
  iVar1 = rect_height(ADDR(0x655344, ((u8 *)&g.d_00655344)));
  iVar1 -= sys_dlgframe_h2;
  iVar2 = rect_width(ADDR(0x655344, ((u8 *)&g.d_00655344)));
  iVar2 -= sys_dlgframe_w2;
  uVar4 = 2;
  uVar5 = city_wnd_rect;
  uVar6 = city_wnd_rect_top;
  uVar3 = label_string(*(i32 *)(label_string_ids + 0x1c));
  frame_wnd_create(this,uVar3,uVar4,uVar5,uVar6,iVar2,iVar1,uVar7,uVar8,uVar9);
  frame_wnd_set_title_font(this,ADDR(0x6aa898, ((u8 *)&g.d_006aa898)));
  frame_wnd_set_title_small_font(this,ADDR(0x6a9168, ((u8 *)&g.d_006a9168)));
  frame_wnd_add_caption_button((C_004083b0_208 *)this,ADDR(0x645120, ((u8 *)&g.d_00645120)),1);
  frame_wnd_add_caption_button((C_004083b0_208 *)this,ADDR(0x648820, ((u8 *)&g.d_00648820)),2);
  frame_wnd_add_caption_button((C_004083b0_208 *)this,ADDR(0x647788, ((u8 *)&g.d_00647788)),3);
  wnd_set_caption_button_handler(this,ADDR(0x40205e, city_window_on_caption_button));
  city_window_clear_controls((C_004083b0_4 *)this);
  wnd_set_close_handler((C_00408130 *)(this->pad_48 + 0x10),ADDR(0x401bae, city_window_close));
  wnd_set_redraw_callback((SurfaceWindow *)this,ADDR(0x402abd, city_window_on_redraw));
  wnd_set_minimize_handler((C_00408130 *)(this->pad_48 + 0x10),ADDR(0x4014ec, city_window_on_minimize));
  wnd_set_restore_handler((C_00408130 *)(this->pad_48 + 0x10),ADDR(0x401780, city_window_on_restore));
  wnd_set_lbuttonup_handler((C_00408130 *)(this->pad_48 + 0x10),ADDR(0x4031ac, city_window_on_lbuttonup));
  wnd_set_rbuttonup_handler((C_00408130 *)(this->pad_48 + 0x10),ADDR(0x4021c6, city_window_on_rbuttonup));
  wnd_set_keydown_handler((C_00408130 *)(this->pad_48 + 0x10),ADDR(0x402cd4, map_window_key));
  wnd_set_char_handler((C_00408130 *)(this->pad_48 + 0x10),ADDR(0x401e56, map_window_ascii));
  wnd_set_size_handler((C_00408130 *)(this->pad_48 + 0x10),ADDR(0x401d7a, city_window_on_size));
  wnd_set_move_handler((C_00408130 *)(this->pad_48 + 0x10),ADDR(0x403bbb, city_window_on_move));
  return;
}
#undef saved_layout_valid
#undef turn_resume_civ

/* 0050dea8 auto */
void __thiscall city_window_destroy(DibSurface *this)

{
  this[0x4c].field_40 = 1;
  city_window_destroy_controls((C_004083b0_4 *)this);
  wnd_destroy_with_surface(this);
  return;
}

/* 005113b0 auto */
#define gfx_draw_target (*(iptr *)((u8 *)&g.d_00635c64))
void __cdecl
city_draw_hline(i32 param_1,i32 param_2,i32 param_3,i32 param_4)

{
  gfx_draw_hline(gfx_draw_target,param_1,param_2,param_3,param_4);
  return;
}
#undef gfx_draw_target

/* 005113f0 auto */
#define gfx_draw_target (*(iptr *)((u8 *)&g.d_00635c64))
void __cdecl city_draw_bevel_rect(iptr param_1,i32 param_2,i32 param_3)

{
  gfx_draw_bevel_rect(gfx_draw_target,param_1,param_2,param_3);
  return;
}
#undef gfx_draw_target

/* 005114d0 auto */
#define gfx_draw_target (*(iptr *)((u8 *)&g.d_00635c64))
void __cdecl
city_window_draw_icon_row(iptr param_1,i32 param_2,i32 param_3,i32 param_4,
            i32 param_5,i32 param_6,i32 param_7,i32 param_8)

{
  sprite_draw_spaced_row(gfx_draw_target,param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return;
}
#undef gfx_draw_target

/* 00511690 auto */
int __thiscall city_window_scale(C_004083b0_4 *this,int param_1)

{
  if (this[0x575].field_0 != 2) {
    param_1 = (int)(this[0x575].field_0 * param_1) / 2;
  }
  return param_1;
}

/* 00579dbb auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
int __cdecl city_treasury_share(iptr city)

{
  char civ;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ = cities[city].owner;
  if (civs[civ].gold < (int)(32000 / (longlong)(int)cities[city].size)) {
    local_8 = ((int)cities[city].size * civs[civ].gold) / (civs[civ].total_city_size + 1);
  }
  else {
    local_8 = (civs[civ].gold / (civs[civ].total_city_size + 1)) * (int)cities[city].size;
  }
  if (local_8 < 0) {
    local_8 = 32000;
  }
  return local_8;
}
#undef local_8

/* 0057a7e9 auto */
void __cdecl city_transfer_for_civil_war(iptr city,iptr civ2,iptr civ)

{
  civs[civ2].num_cities--;
  civs[civ].num_cities++;
  civs[civ2].total_city_size -= (short)cities[city].size;
  civs[civ].total_city_size = (short)cities[city].size + civs[civ].total_city_size;
  cities[city].owner = (i8)civ;
  tile_set_owner((int)cities[city].x,(int)cities[city].y,civ,1);
  return;
}

/* 0057b5df auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define city_turn_processing (*(i32 *)((u8 *)&g.d_0062edf8))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define net_can_escape_reply (*(int *)((u8 *)&g.d_006acb38))
#define scenario_events_loaded (*(int *)((u8 *)&g.d_00627670))
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
#define local_3ec (*(int *)(frame_ + FRAME_OFF(4)))
#define local_3e8 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_3e4 (*(int *)(frame_ + FRAME_OFF(12)))
#define improvement4 (*(iptr *)(frame_ + FRAME_OFF(16)))
#define civ3 (*(int *)(frame_ + FRAME_OFF(24)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(36)))
#define city3 (*(uptr *)(frame_ + FRAME_OFF(40)))
#define local_3c4 (*(int *)(frame_ + FRAME_OFF(44)))
#define improvement3 (*(iptr *)(frame_ + FRAME_OFF(48)))
#define civ4 (*(int *)(frame_ + FRAME_OFF(52)))
#define local_3b4 (*(int *)(frame_ + FRAME_OFF(60)))
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(64)))
#define city4 (*(iptr *)(frame_ + FRAME_OFF(88)))
#define local_394 (*(int *)(frame_ + FRAME_OFF(92)))
#define y3 (*(iptr *)(frame_ + FRAME_OFF(96)))
#define local_38c (*(Dialog *)(frame_ + FRAME_OFF(100)))
#define x3 (*(iptr *)(frame_ + FRAME_OFF(856)))
#define local_94 (*(int *)(frame_ + FRAME_OFF(860)))
#define local_90 (*(int *)(frame_ + FRAME_OFF(864)))
#define local_8c (*(iptr *)(frame_ + FRAME_OFF(868)))
#define local_88 (*(uint *)(frame_ + FRAME_OFF(872)))
#define civ2 (*(iptr *)(frame_ + FRAME_OFF(876)))
#define y2 (*(iptr *)(frame_ + FRAME_OFF(880)))
#define local_7c (*(uint *)(frame_ + FRAME_OFF(884)))
#define local_78 (*(int *)(frame_ + FRAME_OFF(888)))
#define local_74 (*(iptr *)(frame_ + FRAME_OFF(892)))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(896)))
#define local_6c (*(i8 (*)[80])(frame_ + FRAME_OFF(900)))
#define city2 (*(uptr *)(frame_ + FRAME_OFF(980)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(984)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(988)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(992)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(996)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1000)))
void __cdecl city_capture_aftermath(uptr city,iptr civ,int param_3)

{
  uint *puVar1;
  char *pcVar2;
  char cVar3;
  bool bVar4;
  byte terrain;
  int x2;
  int y;
  iptr iVar8;
  iptr iVar9;
  int improvement2;
  int iVar11;
  iptr x;
  uptr uVar13;
  uint uVar14;
  i32 uVar15;
  uint uVar16;
  i8 frame_[FRAME_OFF(1008)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_38c,0x4000);
  local_8 = 0;
  civ2 = (iptr)cities[city].owner;
  x2 = (int)cities[city].x;
  y = (int)cities[city].y;
  if (param_3 < 2) {
    diplo_force_war(civ,civ2);
  }
  local_7c = (uint)(cities[city].founder == civ);
  FUN_005f22d0(local_6c,(iptr)&cities[city].name);
  if ((((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) ||
      ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0)) &&
     (((iVar8 = civ_spaceship_launched(civ2), iVar8 == 0 &&
       (iVar9 = civ_spaceship_launched(civ), iVar9 == 0)) || (game.difficulty < 2)))) {
    diplo_set_treaty_flags(civ,civ2,0x10000);
    if ((((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) ||
        (civs[civ].government != 6)) || (game.power_rank[civ] != 7)) {
      if (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) &&
         (game.power_rank[civ2] < game.power_rank[civ])) {
        local_88 = 0;
        for (city2 = 0; (int)city2 < (int)game.num_cities; city2++) {
          if (((cities[city2].id != 0) && (city2 != city)) &&
             ((cities[city2].founder == civ2 && (cities[city2].owner == civ)))) {
            local_88++;
          }
        }
        if ((1 < (int)local_88) && ((local_88 & 1) == 0)) {
          puVar1 = (uint *)(civ2 * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ * 4);
          *puVar1 = *puVar1 | 0x400000;
        }
      }
    }
    else {
      puVar1 = (uint *)(civ2 * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ * 4);
      *puVar1 = *puVar1 | 0x400000;
    }
  }
  diplo_clear_treaty_flags(civ,civ2,0x800);
  if ((((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) == 0) &&
      (14 < cities[city].size)) && (local_7c == 0)) {
    puVar1 = (uint *)(civ2 * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ * 4);
    *puVar1 = *puVar1 | 0x10;
  }
  city4 = -1;
  if ((((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) == 0) &&
      (improvement2 = city_has_improvement(city,1), improvement2 != 0)) && (4 < civs[civ2].num_cities)) {
    if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
      if (game.power_rank[game.field_139] < game.power_rank[civ2]) {
        bVar4 = true;
      }
      else {
        bVar4 = false;
      }
    }
    else {
      bVar4 = game.power_rank[civ] < game.power_rank[civ2];
    }
    if ((bVar4) && (improvement2 = civ_civil_war(civ2), improvement2 == 0)) {
      cities[city].owner = -1;
      city4 = civ_find_central_city(civ2);
      cities[city].owner = (byte)civ2;
    }
  }
  local_74 = city_treasury_share(city);
  improvement2 = city_has_improvement(city,1);
  if (improvement2 != 0) {
    local_18 = -999;
    city3 = 0xffffffff;
    for (city2 = 0; (int)city2 < (int)game.num_cities; city2++) {
      if ((((cities[city2].id != 0) && (cities[city2].owner == civ2)) &&
          (city2 != city)) &&
         (((int)cities[city].size / 2 <= (int)cities[city2].size &&
          (7 < cities[city2].size)))) {
        cVar3 = cities[city2].size;
        local_14 = map_distance_diag((int)cities[city2].x,(int)cities[city2].y,x2,y);
        local_14 = cVar3 * 3 - local_14;
        unit = tile_first_unit((int)cities[city2].x,(int)cities[city2].y);
        improvement2 = unit_stack_sum(unit,2);
        local_14 += improvement2 * 4;
        improvement2 = city_has_improvement(city2,0x1b);
        if (improvement2 != 0) {
          local_14 = (local_14 * 3) / 2;
        }
        improvement2 = city_has_improvement(city2,8);
        if ((improvement2 != 0) || (improvement2 = civ_has_wonder(civ2,6), improvement2 != 0)) {
          local_14 = local_14 << 1;
        }
        improvement2 = city_has_improvement(city2,0x11);
        if (improvement2 != 0) {
          local_14 = local_14 * 3;
        }
        improvement2 = tile_landmass((int)cities[city2].x,(int)cities[city2].y);
        iVar11 = tile_landmass(x2,y);
        if (improvement2 != iVar11) {
          local_14 = local_14 / 2;
        }
        if (local_18 < local_14) {
          local_18 = local_14;
          city3 = city2;
        }
      }
    }
    local_3c4 = 0;
    if (((999 < civs[civ2].gold) && (0 < (int)city3)) && (city4 < 0)) {
      city2 = city3;
      text_set_string_arg(1,(iptr)&cities[city3].name);
      x = civ_get_adjective(civ2);
      text_set_string_arg(2,x);
      text_set_number_arg(0,1000);
      if ((((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) == 0) ||
          (human_civ != civ2)) || (autoplay_active != 0)) {
        if ((((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) == 0) ||
            (game.multiplayer < 3)) || (autoplay_active != 0)) {
          if ((2 < game.difficulty) &&
             (((improvement2 = civ_spaceship_exists(civ2), improvement2 != 0 ||
               (0xb < civs[civ2].num_cities)) || (1999 < civs[civ2].gold)))) {
            local_3c4 = 1;
          }
        }
        else {
          net_can_escape_reply = -1;
          net_send_text_args(0x17,*(i32 *)
                                   (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),3
                             ,1,human_civ,0);
          improvement2 = timer_ticks();
          while ((iVar11 = timer_ticks(), iVar11 - improvement2 < 0xe10 && (net_can_escape_reply == -1))) {
            net_process_messages((NetSession *)&net_session,1,0);
          }
          if (net_can_escape_reply == -1) {
            local_3c4 = 0;
            improvement2 = civ_spaceship_exists(civ2);
            if (((improvement2 != 0) || (0xb < civs[civ2].num_cities)) || (1999 < civs[civ2].gold)
               ) {
              local_3c4 = 1;
            }
          }
        }
      }
      else {
        local_3c4 = popup_game_with_sprite(ADDR(0x634398, ((u8 *)&g.d_00634398)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      }
    }
    if (local_3c4 == 1) {
      civs[civ2].gold -= 1000;
      city_set_improvement(city2,1,1);
      if ((((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) == 0) ||
          (game.multiplayer < 3)) || (human_civ == civ2)) {
        popup_game_with_city(ADDR(0x6343a4, ((u8 *)&g.d_006343a4)),city2);
      }
      else {
        net_send_text_args(0x18,*(i32 *)
                                 (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),3,0
                           ,city2,0);
      }
      if ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) == 0) {
        city_set_production(city3,99);
      }
    }
    else {
      civ_spaceship_lost_notify(civ2);
      if (-1 < city4) {
        cities[city4].building = -1;
      }
    }
  }
  if ((cities[city].building < -0x26) && (autoplay_active == 0)) {
    if (cities[city].building < 1) {
      improvement3 = ~(int)cities[city].building + 1;
    }
    else {
      improvement3 = (iptr)cities[city].building;
    }
    local_94 = 0;
    for (city2 = 0; (int)city2 < (int)game.num_cities; city2++) {
      if (((cities[city2].id != 0) && (city2 != city)) &&
         ((cities[city2].owner == civ2 &&
          (cities[city2].building == cities[city].building)))) {
        local_94++;
      }
    }
    x = civ_name_plural(civ2);
    text_set_string_arg(1,x);
    text_set_label_arg(2,improvements[improvement3].name);
    text_set_number_arg(0,local_94);
    if (local_94 == 0) {
      dialog_load_game_text(&local_38c,ADDR(0x6343ac, ((u8 *)&g.d_006343ac)));
      if (2 < game.multiplayer) {
        net_send_text_args(0x14,0xff,3,0,improvement3,8);
      }
    }
    else {
      text_clear();
      text_append(ADDR(0x6343bc, ((u8 *)&g.d_006343bc)));
      x = int_clamp(local_94,1,2);
      text_append_int(x);
      dialog_load_game_text(&local_38c,ADDR(0x679640, ((u8 *)&g.d_00679640)));
      improvement2 = int_clamp(local_94,1,2);
      if (improvement2 == 1) {
        if (game.multiplayer < 3) {
          net_send_text_args(0x4c,0xff,3,0,improvement3,0);
        }
        else {
          net_send_text_args(0x4b,0xff,3,0,improvement3,0);
        }
      }
    }
    dialog_add_sprite
              ((DialogOptionList *)&local_38c,(iptr)(&improvement_icon_sprites + improvement3 * 0x3c),0,0);
    dialog_set_image_zoom((DialogWindowView *)&local_38c,8);
    dlg_show_modal(&local_38c,0);
  }
  if ((((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) ||
      ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0)) && (autoplay_active == 0)) {
    for (local_8c = 0; local_8c < 0x1c; local_8c++) {
      uVar13 = wonder_get_city(local_8c);
      if (uVar13 == city) {
        improvement2 = local_8c + 0x27;
        text_set_label_arg(1,improvements[improvement2].name);
        text_clear();
        if (((local_8c < 7) || (local_8c == 0x13)) || ((local_8c == 0x14 || (0x16 < local_8c)))) {
          text_append_label(0xf3);
          text_append_space();
        }
        text_set_string_arg(2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
        if ((((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) &&
            (2 < game.multiplayer)) && (human_civ != civ2)) {
          net_send_text_args(0x1a,*(i32 *)
                                   (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),3
                             ,0,improvement2,0);
        }
        if ((human_civ == civ) && (autoplay_active == 0)) {
          dialog_load_game_text(&local_38c,ADDR(0x6343c8, ((u8 *)&g.d_006343c8)));
          dialog_add_sprite
                    ((DialogOptionList *)&local_38c,(iptr)(&improvement_icon_sprites + improvement2 * 0x3c),0,0);
          dialog_set_image_zoom((DialogWindowView *)&local_38c,8);
          dlg_show_modal(&local_38c,0);
        }
        else if ((human_civ == civ2) && (autoplay_active == 0)) {
          dialog_load_game_text(&local_38c,ADDR(0x6343d8, ((u8 *)&g.d_006343d8)));
          dialog_add_sprite
                    ((DialogOptionList *)&local_38c,(iptr)(&improvement_icon_sprites + improvement2 * 0x3c),0,0);
          dialog_set_image_zoom((DialogWindowView *)&local_38c,8);
          dlg_show_modal(&local_38c,0);
        }
        if (local_8c == 0x14) {
          civ_apply_eiffel_tower(civ);
        }
      }
    }
  }
  local_74 = int_clamp(local_74,0,civs[civ2].gold);
  civs[civ2].gold -= local_74;
  if (civ != 0) {
    civs[civ].gold += local_74;
  }
  if ((human_civ == civ) || (human_civ == civ2)) {
    status_draw_info(1);
  }
  cities[city].shield_box = 0;
  cities[city].flags = cities[city].flags & 0xffffffc4;
  if (-1 < cities[city].building) {
    pcVar2 = (char *)(cities[city].building + ADDR(0x64c7f4, ((u8 *)&civs + 340)) + civ2 * 0x594);
    *pcVar2 = *pcVar2 - 1;
  }
  if (local_7c == 0) {
    city_set_improvement(city,1,0);
    city_set_improvement(city,4,0);
    city_set_improvement(city,0xb,0);
    city_set_improvement(city,7,0);
  }
  if ((param_3 == 0) && (local_7c == 0)) {
    improvement2 = _rand();
    terrain = (byte)(improvement2 >> 0x1f);
    for (improvement = 0; improvement < 5; improvement++) {
      cities[city].improvements[improvement] =
           cities[city].improvements[improvement] &
           (byte)(0xaa >> ((((byte)improvement2 ^ terrain) - terrain & 1 ^ terrain) - terrain & 0x1f));
    }
  }
  if (((param_3 == 0) && (local_7c == 0)) || (1 < cities[city].size)) {
    local_78 = 0;
    if (civ == 0) {
      improvement2 = tile_landmass(x2,y);
      for (civ4 = 1; civ4 < 8; civ4++) {
        if (((1 << ((byte)civ4 & 0x1f) & (uint)game.human_players) != 0) &&
           (*(char *)&civs[civ4].continent_cities[improvement2] != '\0')) {
          local_78 = 1;
        }
      }
    }
    if ((cities[city].size < 2) &&
       (((((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0 &&
          ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) == 0)) ||
         ((civ == 0 && ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0)))) &&
        ((((civ != 0 || (local_78 != 0)) &&
          ((game.human_players & cities[city].known_to) == 0)) &&
         (game.power_rank[civ] != 7)))))) {
      if (game.power_rank[game.field_139] < game.power_rank[civ]) {
        uVar14 = _rand();
        uVar16 = (int)uVar14 >> 0x1f;
        if (((uVar14 ^ uVar16) - uVar16 & 1 ^ uVar16) != uVar16) goto LAB_0057c990;
      }
    }
    else {
LAB_0057c990:
      cities[city].size--;
    }
    if (cities[city].size == '\0') {
      city_delete(city,0);
      city = 0xffffffff;
    }
  }
  if (-1 < (int)city) {
    civs[civ].last_city_turn = game.turn;
    civ_clear_standing_goals_near(civ,5,x2,y,4);
    net_batch_begin();
    for (improvement = 0; improvement < 0x15; improvement++) {
      x = map_wrap_x((char)(&city_tile_dx_table)[improvement] + x2);
      y2 = (char)(&city_tile_dy_table)[improvement] + y;
      improvement2 = map_in_bounds(x,y2);
      if ((improvement2 != 0) && (tile_set_radius_civ(x,y2,civ,1), civ == 0)) {
        tile_set_visible(x,y2,1,1,1);
      }
    }
    net_batch_flush();
    cities[city].owner = (byte)civ;
    city_reveal_to_civ(city,civ2);
    if (scenario_events_loaded != 0) {
      events_check_city_taken
                ((ScenarioEvents *)&scenario_events,(iptr)&cities[city].name,civ,civ2);
    }
  }
  tile_set_owner(x2,y,civ,1);
  if ((human_civ == civ) || (human_civ == civ2)) {
    snd_play_effect(5,0,0,0);
  }
  text_set_string_arg(0,(iptr)local_6c);
  text_set_label_arg(3,*(i32 *)(label_string_ids + 700 + (uint)(local_7c == 0) * -4));
  text_set_label_arg(4,*(i32 *)(label_string_ids + 0x2c4 + (uint)(local_7c == 0) * -4));
  tile_update_known(x2,y,civ);
  tile_update_known(x2,y,civ2);
  if (2 < game.multiplayer) {
    net_send_state_diff(0xff,2,0,0,0);
    net_send_message(0x78,0xff,0,0,0,0,0,0,0,0);
    XD_FlushSendBuffer(5000);
  }
  if ((((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) &&
      ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) == 0)) || (autoplay_active != 0)) {
    if (autoplay_active == 0) {
      for (civ3 = 1; civ3 < 8; civ3++) {
        if (((1 << ((byte)civ3 & 0x1f) & (uint)game.civs_alive) != 0) &&
           ((1 << ((byte)civ3 & 0x1f) & (uint)game.human_players) != 0)) {
          if (human_civ == civ3) {
            map_redraw_tile_all_views(x2,y);
          }
          else if (2 < game.multiplayer) {
            net_send_message(0x72,*(i32 *)
                                     (&net_player_slots + *(int *)(&net_civ_slots + civ3 * 4) * 0x54
                                     ),x2,y,0,0,0,0,0,0);
          }
          if (((*(byte *)&civs[civ3].treaties[civ] & 8) == 0) &&
             (((*(byte *)(civ3 * 4 + ADDR(0x64c6c2, ((u8 *)&civs + 34)) + civ * 0x594) & 0x10) == 0 ||
              ((*(byte *)(civ2 * 4 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ * 0x594) & 8) == 0)))) {
            if (((*(byte *)&civs[civ3].treaties[civ2] & 8) == 0) &&
               (((*(byte *)(civ3 * 4 + ADDR(0x64c6c2, ((u8 *)&civs + 34)) + civ2 * 0x594) & 0x10) == 0 ||
                ((*(byte *)(civ * 4 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 0x594) & 8) == 0)))) {
              if (((((*(byte *)&civs[civ3].treaties[civ] & 0x80) != 0) ||
                   (improvement2 = civ_has_wonder(civ3,0x18), improvement2 != 0)) ||
                  (improvement2 = civ_has_wonder(civ3,9), improvement2 != 0)) ||
                 ((((*(byte *)&civs[civ3].treaties[civ2] & 0x80) != 0 ||
                   (improvement2 = civ_has_wonder(civ3,0x18), improvement2 != 0)) ||
                  (improvement2 = civ_has_wonder(civ3,9), improvement2 != 0)))) {
                x = civ_name_plural(civ);
                text_set_string_arg(1,x);
                x = civ_get_adjective(civ2);
                text_set_string_arg(2,x);
                if (human_civ == civ3) {
                  popup_city_picture_zoom(ADDR(0x63440c, ((u8 *)&g.d_0063440c)),city,0x46,1,civ);
                }
                else if (2 < game.multiplayer) {
                  net_send_text_args(0x1e,*(i32 *)
                                           (&net_player_slots +
                                           *(int *)(&net_civ_slots + civ3 * 4) * 0x54),4,1,
                                     civ,city);
                }
              }
            }
            else {
              x = civ_name_plural(civ);
              text_set_string_arg(1,x);
              x = civ_name_plural(civ2);
              text_set_string_arg(2,x);
              if (human_civ == civ3) {
                popup_city_picture_zoom(ADDR(0x6343fc, ((u8 *)&g.d_006343fc)),city,0x46,1,civ);
              }
              else if (2 < game.multiplayer) {
                net_send_text_args(0x1d,*(i32 *)
                                         (&net_player_slots +
                                         *(int *)(&net_civ_slots + civ3 * 4) * 0x54),4,1,civ
                                   ,city);
              }
            }
          }
          else {
            x = civ_name_plural(civ);
            text_set_string_arg(1,x);
            x = civ_get_adjective(civ2);
            text_set_string_arg(2,x);
            if (human_civ == civ3) {
              popup_city_picture_zoom(ADDR(0x6343f0, ((u8 *)&g.d_006343f0)),city,0x46,1,civ);
            }
            else if (2 < game.multiplayer) {
              net_send_text_args(0x1c,*(i32 *)
                                       (&net_player_slots +
                                       *(int *)(&net_civ_slots + civ3 * 4) * 0x54),5,1,civ,
                                 city);
            }
          }
        }
      }
    }
  }
  else {
    x = civ_name_plural(civ);
    text_set_string_arg(1,x);
    text_set_number_arg(0,local_74);
    if ((human_civ == civ) || (human_civ == civ2)) {
      mapviews_ensure_visible(x2,y,civ);
      map_redraw_tile_all_views(x2,y);
      popup_city_picture_zoom(ADDR(0x6343e4, ((u8 *)&g.d_006343e4)),city,0x46,1,civ);
    }
    if ((((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) && (2 < game.multiplayer))
       && (human_civ != civ2)) {
      net_send_message(0x89,*(i32 *)
                               (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),
                         city,0,0,0,0,0,0,0);
      net_send_message(0x8a,*(i32 *)
                               (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),0,0,0
                         ,0,0,0,0,0);
      net_send_message(0x71,*(i32 *)
                               (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),x2
                         ,y,civ,0,0,0,0,0);
      net_send_message(0x72,*(i32 *)
                               (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),x2
                         ,y,0,0,0,0,0,0);
      net_send_text_args(0x1b,*(i32 *)
                               (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),4,1,
                         civ,city);
    }
    if ((((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) && (2 < game.multiplayer))
       && (human_civ != civ)) {
      net_send_message(0x89,*(i32 *)
                               (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),
                         city,0,0,0,0,0,0,0);
      net_send_message(0x8a,*(i32 *)
                               (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),0,0,0
                         ,0,0,0,0,0);
      net_send_message(0x71,*(i32 *)
                               (&net_player_slots + *(int *)(&net_civ_slots + civ * 4) * 0x54),x2,
                         y,civ,0,0,0,0,0);
      net_send_message(0x72,*(i32 *)
                               (&net_player_slots + *(int *)(&net_civ_slots + civ * 4) * 0x54),x2,
                         y,0,0,0,0,0,0);
      net_send_text_args(0x1b,*(i32 *)
                               (&net_player_slots + *(int *)(&net_civ_slots + civ * 4) * 0x54),4,1,
                         civ,city);
    }
  }
  if (((game.game_flags & 0x80) == 0) || ((scenario_flags & 0x20) == 0)) {
    civ_steal_advance(civ,civ2);
  }
  if ((int)city < 0) goto LAB_0057da76;
  unit = (iptr)game.num_units;
LAB_0057d48e:
  unit--;
  if (-1 < unit) {
    if (((units[unit].id != 0) && (units[unit].owner == civ2)) &&
       ((byte)units[unit].home_city == city)) {
      if (units[unit].type != '\t') {
        if ((((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) == 0) &&
            (city2 = city_at((int)units[unit].x,(int)units[unit].y),
            -1 < (int)city2)) && (city2 != city)) {
          if ((unit_types[units[unit].type].role == 1) &&
             (improvement2 = unit_stack_count_role(unit,1), improvement2 == 1)) {
            units[unit].home_city = (i8)city2;
            goto LAB_0057d48e;
          }
          cities[city2].flags = cities[city2].flags | 0x20;
        }
        unit_destroy_redraw(unit,1);
        unit = (iptr)game.num_units;
        goto LAB_0057d48e;
      }
      units[unit].home_city = -1;
    }
    goto LAB_0057d48e;
  }
  if (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) &&
     (((4 < civs[civ].government || (4 < civs[civ2].government)) &&
      (game.difficulty != '\0')))) {
    cities[city].flags = cities[city].flags | 1;
  }
  if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
    cities[city].building = '\0';
    if (civ == 0) {
      cities[city].building = 5;
      unit = tile_first_unit(x2,y);
      if (-1 < unit) {
        cities[city].building = units[unit].type;
      }
    }
    pcVar2 = (char *)(cities[city].building + ADDR(0x64c7f4, ((u8 *)&civs + 340)) + civ * 0x594);
    *pcVar2 = *pcVar2 + 1;
    city_set_production(city,99);
    goto LAB_0057da76;
  }
  map_redraw_neighbors_all_views((int)cities[city].x,(int)cities[city].y);
  if ((cities[city].building < '\0') ||
     (improvement2 = civ_can_build_unit(civ,city,(int)cities[city].building), improvement2 != 0)) {
    if (cities[city].building < '\0') {
      if (cities[city].building < 1) {
        improvement4 = ~(int)cities[city].building + 1;
      }
      else {
        improvement4 = (iptr)cities[city].building;
      }
      improvement2 = city_can_build_improvement(civ,city,improvement4);
      if (improvement2 == 0) goto LAB_0057d7a9;
    }
  }
  else {
LAB_0057d7a9:
    cities[city].building = '\0';
    local_18 = 0;
    for (unit_type = 0x3e; -1 < unit_type; unit_type--) {
      if ((unit_types[unit_type].role == 1) &&
         (improvement2 = civ_can_build_unit(civ,city,unit_type), improvement2 != 0)) {
        local_14 = ((int)(char)unit_types[unit_type].defense << 3) /
                   (int)(char)unit_types[unit_type].cost;
        if ((unit_types[unit_type].flags & 0x400) != 0) {
          local_14++;
        }
        if (local_18 < local_14) {
          local_18 = local_14;
          cities[city].building = (i8)unit_type;
        }
        break;
      }
    }
  }
  net_batch_begin();
  for (improvement = 0; improvement < 8; improvement++) {
    x = map_wrap_x((char)(&dir_dx_table)[improvement] + x2);
    y2 = (char)(&dir_dy_table)[improvement] + y;
    improvement2 = map_in_bounds(x,y2);
    if ((improvement2 != 0) &&
       (improvement2 = tile_at(x,y2),
       (1 << ((byte)civ & 0x1f) & (uint)*(byte *)(improvement2 + 4)) == 0)) {
      tile_set_visible(x,y2,1 << ((byte)civ & 0x1f),1,1);
      map_redraw_tile_all_views(x,y2);
    }
  }
  net_batch_flush();
  city_turn_processing = 1;
  city_window_begin_notice((C_004083b0_4 *)&city_window);
  city_window_open((C_004083b0_12c *)&city_window,city);
  city_window_end_notice((C_004083b0_12c *)&city_window);
  city_turn_processing = 0;
LAB_0057da76:
  improvement2 = civ_check_destroyed(civ2,civ);
  if ((((improvement2 == 0) && (-1 < (int)city)) && (local_7c == 0)) &&
     (((civs[civ2].government == 3 || (civs[civ2].government == 6)) ||
      ((game.first_discoverer[0x22] != '\0' ||
       (improvement2 = civ_has_advance(civ2,0xf), improvement2 != 0)))))) {
    if ((uint)civs[civ2].government == (uint)civs[civ].government ||
        (int)((uint)civs[civ2].government - (uint)civs[civ].government) < 0) {
      local_3e4 = ~((uint)civs[civ2].government - (uint)civs[civ].government) + 1;
    }
    else {
      local_3e4 = (uint)civs[civ2].government - (uint)civs[civ].government;
    }
    if ((uint)game.power_rank[civ2] == (uint)game.power_rank[civ] ||
        (int)((uint)game.power_rank[civ2] - (uint)game.power_rank[civ]) < 0) {
      local_3e8 = ~((uint)game.power_rank[civ2] - (uint)game.power_rank[civ]) + 1;
    }
    else {
      local_3e8 = (uint)game.power_rank[civ2] - (uint)game.power_rank[civ];
    }
    improvement2 = cities[city].size + 5;
    local_3b4 = (((int)(improvement2 + (improvement2 >> 0x1f & 7U)) >> 3) * (local_3e4 + local_3e8 + 1)) / 2;
    if (param_3 != 0) {
      local_3b4 = local_3b4 / 2;
    }
    improvement2 = civ_has_advance(civ2,0x11);
    if (improvement2 == 0) {
      local_3b4--;
    }
    improvement2 = civ_has_advance(civ2,0x22);
    if (improvement2 == 0) {
      improvement2 = civ_has_advance(civ2,0xf);
      if (improvement2 == 0) {
        local_3b4 = 0;
      }
      improvement2 = civ_has_advance(civ2,0x23);
      if (improvement2 == 0) {
        local_3b4 = 0;
      }
    }
    else {
      improvement2 = civ_has_advance(civ,0x22);
      if (improvement2 == 0) {
        local_3b4 = local_3b4 << 1;
      }
      else {
        local_3b4++;
      }
    }
    improvement2 = (((civs[civ2].treaties[civ] & 0x10) == 0) - 1 & 2) +
             (civs[civ].reputation - 4);
    if (improvement2 < 1) {
      improvement2 = 0;
    }
    local_394 = 0;
    for (local_90 = 0; local_90 < local_3b4; local_90++) {
      local_18 = 0;
      for (improvement = 0; improvement < 0x14; improvement++) {
        x = map_wrap_x((char)(&city_tile_dx_table)[improvement] + x2);
        y2 = (char)(&city_tile_dy_table)[improvement] + y;
        iVar11 = map_in_bounds(x,y2);
        if (((iVar11 != 0) && (iVar11 = tile_is_ocean(x,y2), iVar11 == 0)) &&
           (iVar11 = tile_city_or_unit_owner(x,y2), iVar11 < 0)) {
          terrain = tile_terrain(x,y2);
          local_14 = (char)terrain_types[terrain].defense * 2;
          uVar14 = tile_improvements(x,y2);
          if ((uVar14 & 0x10) != 0) {
            local_14++;
          }
          uVar14 = tile_improvements(x,y2);
          if ((uVar14 & 0x20) != 0) {
            local_14++;
          }
          uVar15 = tile_improvements(x,y2);
          if (((byte)uVar15 & 0x42) == 0x40) {
            local_14 = local_14 << 1;
          }
          if (local_18 < local_14) {
            local_18 = local_14;
            y3 = y2;
            x3 = x;
          }
        }
      }
      if ((local_18 != 0) &&
         (unit = unit_create(9,civ2,x3,y3), -1 < unit)) {
        if (local_394 == 0) {
          if ((human_civ == civ) || (human_civ == civ2)) {
            snd_play_effect(0x22,1,0,0);
          }
          if (((2 < game.multiplayer) &&
              ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0)) &&
             (human_civ != civ2)) {
            net_send_message(0x7a,*(i32 *)
                                     (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54)
                               ,0x22,1,0,0,0,0,0,0);
          }
        }
        local_394++;
        units[unit].orders = 2;
        if (improvement2 != 0) {
          if (improvement2 < 1) {
            local_3ec = 0;
          }
          else {
            local_3ec = _rand();
            local_3ec = local_3ec % (improvement2 + 1);
          }
          if (local_3ec != 0) {
            units[unit].flags = units[unit].flags | 0x2000;
          }
        }
        unit_set_seen_by(unit,civ);
        map_redraw_tile_all_views(x3,y3);
        if ((human_civ == civ) || (human_civ == civ2)) {
          ui_delay_ticks(1);
        }
      }
    }
    if (((local_394 != 0) &&
        (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0 ||
         ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0)))) && (autoplay_active == 0))
    {
      x = civ_get_adjective(civ2);
      text_set_string_arg(0,x);
      text_set_string_arg(1,(iptr)local_6c);
      if ((human_civ == civ) || (human_civ == civ2)) {
        dlg_game_txt_with_unit(ADDR(0x63441c, ((u8 *)&g.d_0063441c)),unit);
      }
      if ((((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) &&
          (2 < game.multiplayer)) && (human_civ != civ2)) {
        net_send_text_args(0x1f,*(i32 *)
                                 (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),2,0
                           ,unit,0);
      }
    }
  }
  if (-1 < (int)city) {
    cities[city].founder = (byte)civ2;
    cities[city].turns_captured = (u8)game.turn;
    uVar13 = wonder_get_city(0xe);
    if (uVar13 == city) {
      civ_leonardo_upgrade(civ);
    }
  }
  if (2 < game.multiplayer) {
    net_send_state_diff(0xff,2,0,0,0);
    net_send_message(0x78,0xff,0,0,0,0,0,0,0,0);
    XD_FlushSendBuffer(5000);
  }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_0057e29f */ { dialog_dtor((Dialog *)((iptr)&local_38c)); }
  return;
}
#undef autoplay_active
#undef city_turn_processing
#undef human_civ
#undef net_can_escape_reply
#undef scenario_events_loaded
#undef scenario_flags
#undef local_3ec
#undef local_3e8
#undef local_3e4
#undef improvement4
#undef civ3
#undef unit
#undef city3
#undef local_3c4
#undef improvement3
#undef civ4
#undef local_3b4
#undef unit_type
#undef city4
#undef local_394
#undef y3
#undef local_38c
#undef x3
#undef local_94
#undef local_90
#undef local_8c
#undef local_88
#undef civ2
#undef y2
#undef local_7c
#undef local_78
#undef local_74
#undef improvement
#undef local_6c
#undef city2
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8
