/* The game, the advisors, the High Council and the reports: functions translated from the original
 * (tools/gen_c.py, now edited directly), in address order. */
#include "auto_common.h"

/* 00419ed3 auto */
#define local_10 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define leader (*(iptr *)(frame_ + FRAME_OFF(8)))
void __cdecl leaders_fixup_names(void)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (leader = 0; leader < 0x15; leader++) {
    leaders[leader].leader_name =
         leaders[leader].names[((uint)leaders[leader].female)];
    if (leaders[leader].plural < 1) {
      leaders[leader].plural = ~leaders[leader].plural + 1;
    }
    if (leaders[leader].adjective < 1) {
      leaders[leader].adjective = ~leaders[leader].adjective + 1;
    }
    for (local_10 = 0; local_10 < 7; local_10++) {
      for (local_c = 0; local_c < 2; local_c++) {
        if (leaders[leader].titles[local_10][local_c] < 1) {
          *(ushort *)&leaders[leader].titles[local_10][local_c] =
               ~*(ushort *)&leaders[leader].titles[local_10][local_c] + 1;
        }
      }
    }
  }
  return;
}
#undef local_10
#undef local_c
#undef leader

/* 0042a380 auto */
void __cdecl credits_font_global_init(void)

{
  credits_font_static_init();
  credits_font_reg_atexit();
  return;
}

/* 0042a39a auto */
void __cdecl credits_font_static_init(void)

{
  font_init_styled((GameFont *)&credits_font,0,0x18,1);
  return;
}

/* 0042a3ba auto */
void __cdecl credits_font_reg_atexit(void)

{
  _atexit(credits_font_static_dtor);
  return;
}

/* 0042a3d7 auto */
void __cdecl credits_font_static_dtor(void)

{
  font_destroy((GameFont *)&credits_font);
  return;
}

/* 0042a3f1 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E41
    _$E46
    _$E51
    _$E56
     6 names - too many to list
   
   Library: Visual Studio 1998 Debug */

void __cdecl advisor_font_global_init(void)

{
  advisor_font_static_init();
  advisor_font_reg_atexit();
  return;
}

/* 0042a40b auto */
void __cdecl advisor_font_static_init(void)

{
  font_init((GameFont *)&advisor_font,0,0x12);
  return;
}

/* 0042a429 auto */
void __cdecl advisor_font_reg_atexit(void)

{
  _atexit(advisor_font_static_dtor);
  return;
}

/* 0042a446 auto */
void __cdecl advisor_font_static_dtor(void)

{
  font_destroy((GameFont *)&advisor_font);
  return;
}

/* 0042a460 auto */
void __cdecl hall_of_fame_font_global_init(void)

{
  hall_of_fame_font_static_init();
  hall_of_fame_font_reg_atexit();
  return;
}

/* 0042a47a auto */
void __cdecl hall_of_fame_font_static_init(void)

{
  font_init_styled((GameFont *)&hall_of_fame_font,0,0x10,1);
  return;
}

/* 0042a49a auto */
void __cdecl hall_of_fame_font_reg_atexit(void)

{
  _atexit(hall_of_fame_font_static_dtor);
  return;
}

/* 0042a4b7 auto */
void __cdecl hall_of_fame_font_static_dtor(void)

{
  font_destroy((GameFont *)&hall_of_fame_font);
  return;
}

/* 0042a4d1 auto */
void __cdecl advisor_bold_font_global_init(void)

{
  advisor_bold_font_static_init();
  advisor_bold_font_reg_atexit();
  return;
}

/* 0042a4eb auto */
void __cdecl advisor_bold_font_static_init(void)

{
  font_init_styled((GameFont *)&advisor_bold_font,0,0xe,1);
  return;
}

/* 0042a50b auto */
void __cdecl advisor_bold_font_reg_atexit(void)

{
  _atexit(advisor_bold_font_static_dtor);
  return;
}

/* 0042a528 auto */
void __cdecl advisor_bold_font_static_dtor(void)

{
  font_destroy((GameFont *)&advisor_bold_font);
  return;
}

/* 0042a5b3 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E41
    _$E46
    _$E51
    _$E56
     6 names - too many to list
   
   Library: Visual Studio 1998 Debug */

void __cdecl advisor_button_font_global_init(void)

{
  advisor_button_font_static_init();
  advisor_button_font_reg_atexit();
  return;
}

/* 0042a5cd auto */
void __cdecl advisor_button_font_static_init(void)

{
  font_init((GameFont *)&advisor_button_font,0,0x10);
  return;
}

/* 0042a5eb auto */
void __cdecl advisor_button_font_reg_atexit(void)

{
  _atexit(advisor_button_font_static_dtor);
  return;
}

/* 0042a608 auto */
void __cdecl advisor_button_font_static_dtor(void)

{
  font_destroy((GameFont *)&advisor_button_font);
  return;
}

/* 0042a622 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl advisor_window_global_init(void)

{
  advisor_window_static_init();
  advisor_window_reg_atexit();
  return;
}

/* 0042a63c auto */
void __cdecl advisor_window_static_init(void)

{
  picwnd_ctor((ViewWindow *)&advisor_window);
  return;
}

/* 0042a656 auto */
void __cdecl advisor_window_reg_atexit(void)

{
  _atexit(advisor_window_static_dtor);
  return;
}

/* 0042a673 auto */
void __cdecl advisor_window_static_dtor(void)

{
  picwnd_dtor((WindowObjectView *)&advisor_window);
  return;
}

/* 0042a68d auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl casualty_window_global_init(void)

{
  casualty_window_static_init();
  casualty_window_reg_atexit();
  return;
}

/* 0042a6a7 auto */
void __cdecl casualty_window_static_init(void)

{
  picwnd_ctor((ViewWindow *)&casualty_window);
  return;
}

/* 0042a6c1 auto */
void __cdecl casualty_window_reg_atexit(void)

{
  _atexit(casualty_window_static_dtor);
  return;
}

/* 0042a6de auto */
void __cdecl casualty_window_static_dtor(void)

{
  picwnd_dtor((WindowObjectView *)&casualty_window);
  return;
}

/* 0042ac4e auto */
#define local_8 (*(PictureWindowCore * *)(frame_ + FRAME_OFF(0)))
void __cdecl advisor_on_close_clicked(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = (PictureWindowCore *)0x0;
  }
  else {
    local_8 = (PictureWindowCore *)(iVar1 - 0x48);
  }
  if (local_8[1].field_18 == 0) {
    picwnd_close(local_8);
  }
  else {
    wnd_end_modal_loop((ModalMenuWindow *)local_8->pad_48);
  }
  return;
}
#undef local_8

/* 0042acb0 auto */
#define local_18 (*(u8 * *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
void __thiscall advisor_add_close_button(ViewWindow *this)

{
  u32 uVar1;
  int iVar2;
  iptr iVar3;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  rect_set_xywh((iptr)local_14,2,0,0x254,0x18);
  uVar1 = this->client_y;
  iVar2 = rect_height((iptr)local_14);
  rect_offset((iptr)local_14,this->client_x,(uVar1 - iVar2) + 0x18e);
  if (this == (ViewWindow *)0x0) {
    local_18 = (u8 *)0x0;
  }
  else {
    local_18 = this->pad_48;
  }
  iVar3 = label_string(*(i32 *)(label_string_ids + 0x51c));
  button_create
            ((Control *)&this->field_320,(iptr)local_18,100,(iptr)local_14,iVar3);
  button_set_callback((Control *)&this->field_320,ADDR(0x401235, advisor_on_close_clicked));
  ctrl_set_default_button((Control *)&this->field_320);
  ctrl_set_cancel_button((Control *)&this->field_320);
  return;
}
#undef local_18
#undef local_14

/* 0042d781 auto */
#define city_specialist_count (*(uint *)((u8 *)&g.d_006a6604))
#define local_54 (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_44 (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
#define local_34 (*(i8 (*)[16])(frame_ + FRAME_OFF(36)))
#define local_24 (*(i8 (*)[16])(frame_ + FRAME_OFF(52)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(68)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(72)))
#define local_c (*(int *)(frame_ + FRAME_OFF(76)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(80)))
int __cdecl
advisor_draw_city_citizens(iptr city,int param_2,i32 param_3,i32 param_4,int param_5,int param_6,
            int param_7)

{
  int iVar1;
  int iVar2;
  i8 *puVar3;
  i8 *puVar4;
  int iVar5;
  i32 uVar6;
  i8 frame_[FRAME_OFF(88)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_10 = ui_calc_item_spacing((int)cities[city].size,0x1c,param_4,0,0);
  local_8 = 0;
  city_specialist_count = cities[city].worked_tiles >> 0x1a;
  for (local_c = 0; local_c < param_5; local_c++) {
    puVar4 = &advisor_window;
    puVar3 = local_24;
    iVar5 = param_2;
    uVar6 = param_3;
    iVar1 = civ_city_style_era((int)cities[city].owner);
    sprite_draw
              ((Sprite *)(&citizen_sprites + iVar1 * 0x294 + (local_8 & 1) * 0x3c),(iptr)puVar3,
               (iptr)puVar4,iVar5,uVar6);
    param_2 += local_10;
    local_8++;
  }
  for (local_c = 0; local_c < (int)((int)cities[city].size - (param_6 + city_specialist_count + param_5));
      local_c = local_c + 1) {
    puVar4 = &advisor_window;
    puVar3 = local_34;
    iVar5 = param_2;
    uVar6 = param_3;
    iVar1 = civ_city_style_era((int)cities[city].owner);
    sprite_draw
              ((Sprite *)(&citizen_sprites + iVar1 * 0x294 + ((local_8 & 1) * 4 + 8) * 0xf),
               (iptr)puVar3,(iptr)puVar4,iVar5,uVar6);
    param_2 += local_10;
    local_8++;
  }
  for (local_c = 0; local_c < param_6; local_c++) {
    if (local_c < param_6 - param_7) {
      local_14 = 4;
    }
    else {
      local_14 = 6;
    }
    puVar4 = &advisor_window;
    puVar3 = local_44;
    iVar5 = param_2;
    uVar6 = param_3;
    iVar1 = civ_city_style_era((int)cities[city].owner);
    sprite_draw
              ((Sprite *)(&citizen_sprites + iVar1 * 0x294 + ((local_8 & 1) + local_14) * 0x3c),
               (iptr)puVar3,(iptr)puVar4,iVar5,uVar6);
    param_2 += local_10;
    local_8++;
  }
  for (local_c = 0; local_c < (int)city_specialist_count; local_c++) {
    puVar4 = &advisor_window;
    puVar3 = local_54;
    iVar5 = param_2;
    uVar6 = param_3;
    iVar1 = civ_city_style_era((int)cities[city].owner);
    iVar2 = city_specialist_type(city,local_c);
    sprite_draw
              ((Sprite *)(&citizen_sprites + iVar1 * 0x294 + (iVar2 * 4 + 0x1c) * 0xf),
               (iptr)puVar3,(iptr)puVar4,iVar5,uVar6);
    param_2 += local_10;
  }
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

/* 0042da1d auto */
#define advisor_client_width (*(i32 *)((u8 *)&g.d_0063ec3c))
#define advisor_client_x (*(int *)((u8 *)&g.d_0063ec34))
#define advisor_first_row (*(int *)((u8 *)&g.d_0063ef70))
#define advisor_row_height (*(i32 *)((u8 *)&g.d_0063ef80))
#define advisor_page_count_i32 (*(i32 *)((u8 *)&g.d_0063ef68))
#define advisor_list_top_i32 (*(i32 *)((u8 *)&g.d_0063ef78))
#define advisor_list_height_i32 (*(i32 *)((u8 *)&g.d_0063ef7c))
#define local_50 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_38 (*(uint *)(frame_ + FRAME_OFF(24)))
#define city (*(iptr *)(frame_ + FRAME_OFF(28)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(44)))
#define local_18 (*(i8 (*)[16])(frame_ + FRAME_OFF(56)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(72)))
/* WARNING: Removing unreachable block (ram,0x0042dfd1) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl attitude_advisor_draw(void)

{
  uint uVar1;
  ushort uVar2;
  int iVar4;
  int iVar5;
  int iVar6;
  iptr iVar7;
  int iVar8;
  i32 uVar9;
  iptr civ;
  i8 frame_[FRAME_OFF(80)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ = advisor_report_civ;
  uVar2 = game.field_06 & 4;
  game.field_06 = game.field_06 & 0xfffb;
  frame_wnd_layout((FrameWindow *)&advisor_window);
  frame_wnd_draw_caption((FrameWindow *)&advisor_window);
  picwnd_blit((PictureWindow *)&advisor_window);
  iVar4 = advisor_client_y + 2;
  iVar5 = advisor_client_y + 0x174;
  iVar6 = font_line_spacing((GameFont *)&advisor_font);
  text_set_surface(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)));
  text_set_font(ADDR(0x63eac0, ((u8 *)&g.d_0063eac0)));
  text_set_colors(0x25,0x12,2,1);
  text_clear();
  iVar7 = label_string(*(i32 *)(label_string_ids + 0x544));
  text_append(iVar7);
  gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,iVar4,advisor_client_width);
  iVar4 += iVar6;
  text_clear();
  iVar8 = int_clamp(civs[civ].government - 1,0,4);
  text_append_label(iVar8 + 0x148);
  text_append_space();
  text_append_label(0x8c);
  text_append_space();
  iVar7 = civ_name_plural(civ);
  text_append(iVar7);
  gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,iVar4,advisor_client_width);
  iVar4 += iVar6;
  text_clear();
  iVar7 = civ_leader_title(civ);
  text_append(iVar7);
  text_append_space();
  iVar7 = civ_leader_name(civ);
  text_append(iVar7);
  text_append_colon();
  text_append_year((int)game.year);
  gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,iVar4,advisor_client_width);
  iVar4 = iVar4 + iVar6 + 2;
  advisor_row_height = 0x20;
  advisor_list_height_i32 = iVar5 - iVar4;
  advisor_list_top_i32 = iVar4;
  advisor_rows_per_page = int_clamp((iVar5 - iVar4) / 0x20,1,99);
  local_24 = 0;
  for (city = 0; city < game.num_cities; city++) {
    if ((cities[city].id != 0) && (cities[city].owner == civ)) {
      local_24++;
    }
  }
  local_8 = advisor_rows_per_page;
  advisor_page_count_i32 = int_clamp((advisor_rows_per_page - 1 + local_24) / advisor_rows_per_page,1,99);
  uVar9 = int_clamp(local_24 - 1,0,999);
  iVar6 = int_clamp(advisor_first_row,0,uVar9);
  local_38 = 0;
  advisor_first_row = iVar6;
  local_50 = iVar4;
  for (city = 0; city < game.num_cities; city++) {
    uVar1 = local_38;
    if ((((cities[city].id != 0) && (cities[city].owner == civ)) &&
        (uVar1 = local_38 + 1, iVar6 <= (int)local_38)) && ((int)local_38 < iVar6 + local_8)) {
      if ((uVar2 != 0) && (4 < civs[civ].government)) {
        city_recalc(city,1);
      }
      gfx_draw_city(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),city,0,(uVar1 & 1) * 0x40 + advisor_client_x + 2,local_50,0);
      text_set_font(ADDR(0x63eab8, ((u8 *)&g.d_0063eab8)));
      text_set_colors(0x25,0x12,1,1);
      if ((cities[city].unhappy == '\0') &&
         ((int)cities[city].size - (int)(char)cities[city].happy <=
          (int)cities[city].size >> 1)) {
        text_set_colors(0x29,0x12,0xffffffff,0xffffffff);
      }
      if ((char)cities[city].happy < (char)cities[city].unhappy) {
        text_set_colors(0x6a,0x12,0xffffffff,0xffffffff);
      }
      iVar8 = advisor_client_x;
      gfx_draw_text((iptr)&cities[city].name,advisor_client_x + 0x8c,local_50 + 9);
      advisor_draw_city_citizens(city,iVar8 + 0xf5,local_50 + 3,
                         ((advisor_client_right - advisor_vscroll_width) - 0x20) - (iVar8 + 0xf5),
                         (int)(char)cities[city].happy,(int)(char)cities[city].unhappy,0);
      local_50 += 0x20;
    }
    local_38 = uVar1;
  }
  if (advisor_controls_created == 0) {
    rect_set((iptr)local_18,(advisor_client_right - advisor_vscroll_width) - 2,iVar4,advisor_client_right - 2,
                       iVar5);
    scrollbar_create((Control *)&advisor_scrollbar,ADDR(0x63eb58, ((u8 *)&g.d_0063eb58)),200,(iptr)local_18,1);
    uVar9 = int_clamp(local_24 - 1,0,999);
    scrollbar_set_range((Control *)&advisor_scrollbar,0,uVar9);
    scrollbar_set_pos((ClickControl *)&advisor_scrollbar,advisor_first_row);
    scrollbar_set_page_size((Control *)&advisor_scrollbar,advisor_rows_per_page);
    scrollbar_set_callback((Control *)&advisor_scrollbar,ADDR(0x4032fb, attitude_advisor_on_scroll));
    ctrl_show_and_redraw((Control *)&advisor_scrollbar);
    wnd_set_lbuttonup_handler((WndEventHandlers *)&advisor_wnd_events,ADDR(0x4019fb, attitude_advisor_on_click));
    advisor_controls_created = 1;
  }
  wnd_blit_surface((DibSurface *)&advisor_window);
  return;
}
#undef advisor_client_width
#undef advisor_client_x
#undef advisor_first_row
#undef advisor_row_height
#undef advisor_page_count_i32
#undef advisor_list_top_i32
#undef advisor_list_height_i32
#undef local_50
#undef local_38
#undef city
#undef local_24
#undef local_18
#undef local_8

/* 0042e07f auto */
#define advisor_first_row (*(i32 *)((u8 *)&g.d_0063ef70))
void __cdecl attitude_advisor_on_scroll(i32 param_1)

{
  advisor_first_row = param_1;
  attitude_advisor_draw();
  return;
}
#undef advisor_first_row

/* 0042e09c auto */
#define advisor_first_row (*(int *)((u8 *)&g.d_0063ef70))
#define advisor_row_height (*(int *)((u8 *)&g.d_0063ef80))
#define advisor_list_top_i32 (*(i32 *)((u8 *)&g.d_0063ef78))
#define city (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl attitude_advisor_on_click(i32 param_1,int param_2)

{
  int iVar1;
  bool bVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((-1 < param_2 - advisor_list_top_i32) &&
     (iVar1 = (param_2 - advisor_list_top_i32) / advisor_row_height, iVar1 < advisor_rows_per_page)) {
    local_8 = 0;
    for (city = 0; city < game.num_cities; city++) {
      if (((cities[city].id != 0) && (cities[city].owner == advisor_report_civ)) &&
         (bVar2 = local_8 == iVar1 + advisor_first_row, local_8 = local_8 + 1, bVar2)) {
        city_window_open((ScaledWindowView *)&city_window,city);
        return;
      }
    }
  }
  return;
}
#undef advisor_first_row
#undef advisor_row_height
#undef advisor_list_top_i32
#undef city
#undef local_8

/* 0042e185 auto */
void __cdecl attitude_advisor_show(iptr param_1)

{
  picwnd_open((PictureWindow *)&advisor_window,4,4,0,600,400,0,0);
  advisor_report_civ = param_1;
  advisor_add_close_button((ViewWindow *)&advisor_window);
  wnd_set_redraw_callback((SurfaceWindow *)&advisor_window,ADDR(0x402838, attitude_advisor_draw));
  wnd_repaint((SurfaceWindow *)&advisor_window);
  window_show((WindowObjectView *)&advisor_window);
  return;
}

/* 0042e1e8 auto */
#define unit_ability_list_nonempty (*(int *)((u8 *)&g.d_0063e4f4))
void __cdecl defense_append_ability_label(i32 param_1)

{
  if (unit_ability_list_nonempty != 0) {
    text_append_comma();
  }
  unit_ability_list_nonempty = 1;
  text_append_label(param_1);
  return;
}
#undef unit_ability_list_nonempty

/* 0042e220 auto */
#define advisor_client_width (*(i32 *)((u8 *)&g.d_0063ec3c))
#define advisor_client_x (*(int *)((u8 *)&g.d_0063ec34))
#define advisor_first_row (*(int *)((u8 *)&g.d_0063ef70))
#define advisor_report_param (*(int *)((u8 *)&g.d_0063efac))
#define advisor_row_height (*(i32 *)((u8 *)&g.d_0063ef80))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define unit_ability_list_nonempty (*(uint *)((u8 *)&g.d_0063e4f4))
#define advisor_page_count_i32 (*(i32 *)((u8 *)&g.d_0063ef68))
#define advisor_list_top_i32 (*(i32 *)((u8 *)&g.d_0063ef78))
#define advisor_list_height_i32 (*(i32 *)((u8 *)&g.d_0063ef7c))
#define local_94 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_78 (*(uint *)(frame_ + FRAME_OFF(32)))
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(36)))
#define acStack_70 (*(char (*)[64])(frame_ + FRAME_OFF(40)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(104)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(108)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(112)))
#define civ2 (*(int *)(frame_ + FRAME_OFF(116)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(120)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(124)))
#define local_18 (*(i8 (*)[16])(frame_ + FRAME_OFF(128)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(144)))
/* WARNING: Removing unreachable block (ram,0x0042ef32) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl defense_minister_draw(void)

{
  uint uVar1;
  int iVar3;
  int iVar4;
  iptr unit;
  int iVar6;
  i32 uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  bool bVar11;
  i32 uVar12;
  i32 uVar13;
  i32 uVar14;
  iptr civ;
  i8 frame_[FRAME_OFF(152)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ = advisor_report_civ;
  frame_wnd_layout((FrameWindow *)&advisor_window);
  frame_wnd_draw_caption((FrameWindow *)&advisor_window);
  picwnd_blit((PictureWindow *)&advisor_window);
  iVar3 = advisor_client_y + 2;
  iVar4 = advisor_client_y + 0x174;
  local_1c = font_line_spacing((GameFont *)&advisor_font);
  text_set_surface(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)));
  text_set_font(ADDR(0x63eac0, ((u8 *)&g.d_0063eac0)));
  text_set_colors(0x25,0x12,2,1);
  text_clear();
  unit = label_string(*(i32 *)(label_string_ids + 0x53c));
  text_append(unit);
  text_append_colon();
  if (advisor_report_param == 0) {
    unit = label_string(*(i32 *)(label_string_ids + 0x560));
    text_append(unit);
  }
  else {
    unit = label_string(*(i32 *)(label_string_ids + 0x564));
    text_append(unit);
  }
  gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,iVar3,advisor_client_width);
  iVar3 += local_1c;
  text_clear();
  iVar6 = int_clamp(civs[civ].government - 1,0,4);
  text_append_label(iVar6 + 0x148);
  text_append_space();
  text_append_label(0x8c);
  text_append_space();
  unit = civ_name_plural(civ);
  text_append(unit);
  gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,iVar3,advisor_client_width);
  iVar3 += local_1c;
  text_clear();
  unit = civ_leader_title(civ);
  text_append(unit);
  text_append_space();
  unit = civ_leader_name(civ);
  text_append(unit);
  text_append_colon();
  text_append_year((int)game.year);
  gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,iVar3,advisor_client_width);
  iVar3 += local_1c;
  iVar6 = iVar3 + 2;
  local_1c = 0x18;
  advisor_row_height = 0x18;
  advisor_list_top_i32 = iVar3 + 0x1a;
  advisor_list_height_i32 = iVar4 - iVar6;
  advisor_rows_per_page = int_clamp((iVar4 - iVar6) / 0x18,1,99);
  local_8 = advisor_rows_per_page;
  local_2c = 0;
  unit_type = 0;
  do {
    if (0x3d < unit_type) {
      advisor_page_count_i32 = int_clamp((local_8 - 1 + local_2c) / local_8,1,99);
      uVar7 = int_clamp(local_2c - 1,0,999);
      iVar3 = int_clamp(advisor_first_row,0,uVar7);
      local_78 = 0;
      advisor_first_row = iVar3;
      local_94 = iVar6;
      for (unit_type = 0; unit_type < 0x3e; unit_type++) {
        uVar1 = local_78;
        if (((acStack_70[unit_type] != '\0') && (uVar1 = local_78 + 1, iVar3 <= (int)local_78)) &&
           ((int)local_78 < iVar3 + local_8)) {
          iVar8 = (uVar1 & 1) * 0x40 + advisor_client_x;
          unit = unit_make_dummy(unit_type,civ);
          gfx_draw_unit(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),unit,0,iVar8 + 2,local_94,0,0);
          text_set_font(ADDR(0x63eab8, ((u8 *)&g.d_0063eab8)));
          text_set_colors(0x25,0x12,1,1);
          iVar8 = advisor_client_x;
          iVar9 = local_94 + 0x11;
          iVar10 = advisor_client_x + 0x8c;
          local_30 = iVar9;
          unit = label_string(unit_types[unit_type].name);
          gfx_draw_text(unit,iVar10,iVar9);
          local_28 = iVar8 + 0xec;
          if (advisor_report_param == 0) {
            text_clear();
            text_append_int((int)(char)unit_types[unit_type].attack);
            text_append(ADDR(0x625f20, ((u8 *)&g.d_00625f20)));
            text_append_int((int)(char)unit_types[unit_type].defense);
            if ((unit_types[unit_type].flags & 0x400) != 0) {
              text_append(ADDR(0x625f24, ((u8 *)&g.d_00625f24)));
            }
            text_append(ADDR(0x625f28, ((u8 *)&g.d_00625f28)));
            text_append_int((int)(char)unit_types[unit_type].move /
                               (int)(uint)cosmic.road_move_mult);
            gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_28,local_30);
            local_28 = iVar8 + 0x123;
            text_clear();
            text_append_int((int)(char)unit_types[unit_type].hit_points / 10);
            text_append(ADDR(0x625f2c, ((u8 *)&g.d_00625f2c)));
            text_append_int((int)(char)unit_types[unit_type].firepower);
            gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_28,local_30);
            local_28 = iVar8 + 0x143;
            if (*(char *)&civs[civ].units_active[unit_type] != '\0') {
              text_set_colors(0x7a,10,0xffffffff,0xffffffff);
              text_clear();
              text_append_int((uint)civs[civ].units_active[unit_type]);
              text_append_space();
              text_append_label(0x15a);
              gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_28,local_30);
            }
            local_28 = iVar8 + 0x180;
            if (*(char *)&civs[civ].units_in_production[unit_type] != '\0') {
              text_set_colors(0x5e,10,0xffffffff,0xffffffff);
              text_clear();
              text_append_int((uint)civs[civ].units_in_production[unit_type]);
              text_append_space();
              text_append_label(0x15b);
              gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_28,local_30);
            }
            local_28 = iVar8 + 0x1c1;
            text_clear();
            text_set_colors(0x7a,10,0xffffffff,0xffffffff);
            unit_ability_list_nonempty = 0;
            bVar11 = unit_types[unit_type].hold != '\0';
            if (bVar11) {
              text_append_label(0x15c);
              text_append_space();
              text_append_int((int)(char)unit_types[unit_type].hold);
            }
            unit_ability_list_nonempty = (uint)bVar11;
            if ((unit_types[unit_type].flags & 0x10) == 0) {
              if (unit_types[unit_type].domain == 1) {
                defense_append_ability_label(0x15d);
              }
            }
            else {
              defense_append_ability_label(0x15e);
            }
            if ((unit_types[unit_type].flags & 1) != 0) {
              defense_append_ability_label(0x15f);
            }
            if ((unit_types[unit_type].flags & 2) != 0) {
              defense_append_ability_label(0x160);
            }
            if ((unit_types[unit_type].flags & 0x40) != 0) {
              defense_append_ability_label(0x161);
            }
            if ((unit_types[unit_type].flags & 4) != 0) {
              defense_append_ability_label(0x162);
            }
            if ((unit_types[unit_type].flags & 8) != 0) {
              defense_append_ability_label(0x163);
            }
            if ((unit_types[unit_type].flags & 0x80) != 0) {
              defense_append_ability_label(0x164);
            }
            if ((unit_types[unit_type].flags & 0x100) != 0) {
              defense_append_ability_label(0x165);
            }
            if ((unit_types[unit_type].flags & 0x200) != 0) {
              defense_append_ability_label(0x166);
            }
            if ((unit_types[unit_type].flags & 0x400) != 0) {
              defense_append_ability_label(0x167);
            }
            if ((unit_types[unit_type].flags & 0x2000) != 0) {
              defense_append_ability_label(0x168);
            }
            if ((unit_types[unit_type].flags & 0x20) != 0) {
              defense_append_ability_label(0x169);
            }
            if ((unit_types[unit_type].flags & 0x800) != 0) {
              defense_append_ability_label(0x16a);
            }
            if ((unit_types[unit_type].flags & 0x4000) != 0) {
              defense_append_ability_label(0x16b);
            }
            if (unit_ability_list_nonempty != 0) {
              gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_28,local_30);
            }
          }
          else {
            iVar8 += 0x100;
            local_28 = iVar8;
            if (*(char *)&civs[civ].units_lost[unit_type] != '\0') {
              uVar14 = 0xffffffff;
              uVar13 = 0xffffffff;
              uVar12 = 0x12;
              uVar7 = civ_color_secondary(civ);
              text_set_colors(uVar7,uVar12,uVar13,uVar14);
              text_clear();
              text_append_int((uint)civs[civ].units_lost[unit_type]);
              gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_28,local_30);
            }
            local_28 += 0x1e;
            for (civ2 = 1; civ2 < 8; civ2++) {
              if ((civ2 != civ) &&
                 ((((*(byte *)&civs[human_civ].treaties[civ2] & 0x80) != 0 ||
                   (iVar9 = civ_has_wonder(human_civ,0x18), iVar9 != 0)) ||
                  ((iVar9 = civ_has_wonder(human_civ,9), iVar9 != 0 ||
                   ((iVar9 = civ_has_wonder(civ,9), iVar9 != 0 ||
                    (iVar9 = civ_has_wonder(civ,0x18), iVar9 != 0)))))))) {
                if (*(char *)&civs[civ2].units_lost[unit_type] != '\0') {
                  uVar14 = 0xffffffff;
                  uVar13 = 0xffffffff;
                  uVar12 = 0x12;
                  uVar7 = civ_color_secondary(civ2);
                  text_set_colors(uVar7,uVar12,uVar13,uVar14);
                  text_clear();
                  text_append_int((uint)civs[civ2].units_lost[unit_type]);
                  gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_28,local_30);
                }
                local_28 += 0x1e;
              }
            }
            local_20 = iVar8;
          }
          local_94 += local_1c;
        }
        local_78 = uVar1;
      }
      if (advisor_report_param != 0) {
        rect_set((iptr)local_18,local_20 - 8,iVar6,local_20 + 0x10,iVar4);
        uVar7 = civ_color_primary(civ);
        gfx_draw_rect_frame(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),(iptr)local_18,uVar7);
      }
      if (advisor_controls_created == 0) {
        rect_set((iptr)local_18,(advisor_client_right - advisor_vscroll_width) - 2,iVar6,advisor_client_right - 2
                           ,iVar4);
        scrollbar_create
                  ((Control *)&advisor_scrollbar,ADDR(0x63eb58, ((u8 *)&g.d_0063eb58)),200,(iptr)local_18,1);
        scrollbar_set_callback((Control *)&advisor_scrollbar,ADDR(0x403abc, defense_minister_on_scroll));
      }
      uVar7 = int_clamp(local_2c - 1,0,999);
      scrollbar_set_range((Control *)&advisor_scrollbar,0,uVar7);
      scrollbar_set_pos((ClickControl *)&advisor_scrollbar,advisor_first_row);
      scrollbar_set_page_size((Control *)&advisor_scrollbar,advisor_rows_per_page);
      if (advisor_controls_created == 0) {
        ctrl_show_and_redraw((Control *)&advisor_scrollbar);
        advisor_controls_created = 1;
      }
      wnd_blit_surface((DibSurface *)&advisor_window);
      return;
    }
    if (advisor_report_param == 0) {
      if ((*(char *)&civs[civ].units_active[unit_type] == '\0') &&
         (*(char *)&civs[civ].units_in_production[unit_type] == '\0')) {
        acStack_70[unit_type] = '\0';
      }
      else {
        acStack_70[unit_type] = 1;
      }
      if (acStack_70[unit_type] != '\0') {
        local_2c++;
      }
    }
    else {
      acStack_70[unit_type] = '\0';
      for (civ2 = 1; civ2 < 8; civ2++) {
        if ((*(char *)&civs[civ2].units_lost[unit_type] != '\0') &&
           (((((civ2 == civ ||
               ((*(byte *)&civs[human_civ].treaties[civ2] & 0x80) != 0)) ||
              (iVar3 = civ_has_wonder(human_civ,0x18), iVar3 != 0)) ||
             ((iVar3 = civ_has_wonder(human_civ,9), iVar3 != 0 ||
              (iVar3 = civ_has_wonder(civ,9), iVar3 != 0)))) ||
            (iVar3 = civ_has_wonder(civ,0x18), iVar3 != 0)))) {
          acStack_70[unit_type] = 1;
          local_2c++;
          break;
        }
      }
    }
    unit_type++;
  } while( true );
}
#undef advisor_client_width
#undef advisor_client_x
#undef advisor_first_row
#undef advisor_report_param
#undef advisor_row_height
#undef human_civ
#undef unit_ability_list_nonempty
#undef advisor_page_count_i32
#undef advisor_list_top_i32
#undef advisor_list_height_i32
#undef local_94
#undef local_78
#undef unit_type
#undef acStack_70
#undef local_30
#undef local_2c
#undef local_28
#undef civ2
#undef local_20
#undef local_1c
#undef local_18
#undef local_8

/* 0042efe3 auto */
#define advisor_first_row (*(i32 *)((u8 *)&g.d_0063ef70))
void __cdecl defense_minister_on_scroll(i32 param_1)

{
  advisor_first_row = param_1;
  defense_minister_draw();
  return;
}
#undef advisor_first_row

/* 0042f000 auto */
#define advisor_report_param (*(uint *)((u8 *)&g.d_0063efac))
void __cdecl defense_minister_on_toggle_view(void)

{
  advisor_report_param = (uint)(advisor_report_param == 0);
  if (advisor_report_param == 0) {
    control_hide((Control *)&advisor_alt_toggle_button);
    ctrl_show_and_redraw((Control *)&advisor_toggle_button);
  }
  else {
    control_hide((Control *)&advisor_toggle_button);
    ctrl_show_and_redraw((Control *)&advisor_alt_toggle_button);
  }
  defense_minister_draw();
  return;
}
#undef advisor_report_param

/* 0042f079 auto */
#define advisor_client_x (*(i32 *)((u8 *)&g.d_0063ec34))
#define advisor_report_param (*(i32 *)((u8 *)&g.d_0063efac))
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
/* WARNING: Removing unreachable block (ram,0x0042f1bc) */
/* WARNING: Removing unreachable block (ram,0x0042f131) */
/* WARNING: Removing unreachable block (ram,0x0042f21a) */

void __cdecl defense_minister_show(iptr param_1)

{
  int iVar1;
  int iVar2;
  iptr iVar3;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  picwnd_open((PictureWindow *)&advisor_window,2,2,0,600,400,0,0);
  advisor_report_civ = param_1;
  advisor_report_param = 0;
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
  iVar3 = label_string(*(i32 *)(label_string_ids + 0x564));
  button_create
            ((Control *)&advisor_toggle_button,ADDR(0x63eb58, ((u8 *)&g.d_0063eb58)),0x65,(iptr)local_14,iVar3);
  button_set_callback((Control *)&advisor_toggle_button,ADDR(0x403c1a, defense_minister_on_toggle_view));
  iVar3 = label_string(*(i32 *)(label_string_ids + 0x560));
  button_create
            ((Control *)&advisor_alt_toggle_button,ADDR(0x63eb58, ((u8 *)&g.d_0063eb58)),0x66,(iptr)local_14,iVar3);
  button_set_callback((Control *)&advisor_alt_toggle_button,ADDR(0x403c1a, defense_minister_on_toggle_view));
  control_hide((Control *)&advisor_alt_toggle_button);
  wnd_set_redraw_callback((SurfaceWindow *)&advisor_window,ADDR(0x403332, defense_minister_draw));
  wnd_repaint((SurfaceWindow *)&advisor_window);
  window_show((WindowObjectView *)&advisor_window);
  return;
}
#undef advisor_client_x
#undef advisor_report_param
#undef local_14

/* 0042f293 auto */
#define advisor_client_width (*(int *)((u8 *)&g.d_0063ec3c))
#define advisor_client_x (*(int *)((u8 *)&g.d_0063ec34))
#define advisor_first_row (*(iptr *)((u8 *)&g.d_0063ef70))
#define advisor_report_param (*(iptr *)((u8 *)&g.d_0063efac))
#define advisor_row_height (*(i32 *)((u8 *)&g.d_0063ef80))
#define diplo_cur_attitude (*(i32 *)((u8 *)&g.d_0064b114))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define advisor_page_count_i32 (*(i32 *)((u8 *)&g.d_0063ef68))
#define advisor_list_top_i32 (*(i32 *)((u8 *)&g.d_0063ef78))
#define advisor_list_height_i32 (*(i32 *)((u8 *)&g.d_0063ef7c))
#define advisor_list_left_i32 (*(i32 *)((u8 *)&g.d_0063ef90))
#define local_d0 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define civ3 (*(iptr *)(frame_ + FRAME_OFF(16)))
#define local_bc (*(int *)(frame_ + FRAME_OFF(20)))
#define local_b8 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_b4 (*(iptr *)(frame_ + FRAME_OFF(28)))
#define local_b0 (*(int *)(frame_ + FRAME_OFF(32)))
#define civ2 (*(int *)(frame_ + FRAME_OFF(36)))
#define local_a8 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_a4 (*(int *)(frame_ + FRAME_OFF(44)))
#define city (*(iptr *)(frame_ + FRAME_OFF(48)))
#define advance (*(iptr *)(frame_ + FRAME_OFF(52)))
#define local_98 (*(int *)(frame_ + FRAME_OFF(56)))
#define city2 (*(iptr *)(frame_ + FRAME_OFF(60)))
#define local_90 (*(iptr *)(frame_ + FRAME_OFF(64)))
#define leader (*(iptr *)(frame_ + FRAME_OFF(68)))
#define local_88 (*(int *)(frame_ + FRAME_OFF(72)))
#define local_84 (*(int *)(frame_ + FRAME_OFF(76)))
#define local_80 (*(int *)(frame_ + FRAME_OFF(80)))
#define local_7c (*(int *)(frame_ + FRAME_OFF(84)))
#define local_78 (*(int *)(frame_ + FRAME_OFF(88)))
#define civ (*(iptr *)(frame_ + FRAME_OFF(92)))
#define local_70 (*(int *)(frame_ + FRAME_OFF(96)))
#define local_6c (*(char (*)[80])(frame_ + FRAME_OFF(100)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(180)))
#define local_18 (*(i8 (*)[16])(frame_ + FRAME_OFF(184)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(200)))
/* WARNING: Removing unreachable block (ram,0x004301aa) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl intel_report_draw(void)

{
  iptr iVar1;
  i32 uVar2;
  int iVar3;
  int iVar4;
  i32 uVar5;
  i32 uVar6;
  i32 uVar7;
  i8 frame_[FRAME_OFF(208)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ3 = advisor_report_civ;
  civ = advisor_report_param;
  frame_wnd_layout((FrameWindow *)&advisor_window);
  frame_wnd_draw_caption((FrameWindow *)&advisor_window);
  picwnd_blit((PictureWindow *)&advisor_window);
  local_a8 = advisor_client_y + 2;
  local_b8 = advisor_client_y + 0x174;
  local_1c = font_line_spacing((GameFont *)&advisor_font);
  text_set_surface(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)));
  text_set_font(ADDR(0x63eac0, ((u8 *)&g.d_0063eac0)));
  text_set_colors(0x25,0x12,2,1);
  text_clear();
  iVar1 = label_string(*(i32 *)(label_string_ids + 0x540));
  text_append(iVar1);
  gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,local_a8,advisor_client_width);
  local_a8 += local_1c;
  text_clear();
  iVar1 = civ_leader_title(civ);
  text_append(iVar1);
  text_append_space();
  iVar1 = civ_leader_name(civ);
  text_append(iVar1);
  text_append_space();
  text_append_label(0x8c);
  text_append_space();
  iVar1 = civ_name_plural(civ);
  text_append(iVar1);
  text_append_space();
  diplo_eval_ai_stance(civ3,civ);
  local_90 = diplo_attitude_level(diplo_cur_attitude);
  text_append_lparen();
  text_append_string_id(attitude_names[local_90]);
  if ((*(byte *)(civ * 4 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ3 * 0x594) & 0x20) == 0) {
    if ((*(byte *)&civs[civ3].treaties[civ] & 8) == 0) {
      if ((*(byte *)&civs[civ3].treaties[civ] & 4) == 0) {
        if ((*(byte *)&civs[civ3].treaties[civ] & 2) != 0) {
          text_append_comma();
          text_append_label(0x8f);
        }
      }
      else {
        text_append_comma();
        text_append_label(0x8e);
      }
    }
    else {
      text_append_comma();
      text_append_label(0x8d);
    }
  }
  else {
    text_append_comma();
    text_append_label(0x90);
  }
  text_append_rparen();
  uVar7 = 0xffffffff;
  uVar6 = 0xffffffff;
  uVar5 = 0x12;
  uVar2 = civ_color_secondary(civ);
  text_set_colors(uVar2,uVar5,uVar6,uVar7);
  gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,local_a8,advisor_client_width);
  local_a8 += local_1c;
  text_clear();
  leader = (iptr)civs[civ].tribe;
  if (leaders[leader].attack == 1) {
    text_append_label(0x92);
    text_append_space();
  }
  if (leaders[leader].attack == -1) {
    text_append_label(0x93);
    text_append_space();
  }
  if (leaders[leader].civilize == 1) {
    text_append_label(0x96);
    text_append_space();
  }
  if (leaders[leader].civilize == -1) {
    text_append_label(0x97);
    text_append_space();
  }
  if (leaders[leader].expand == 1) {
    text_append_label(0x94);
    text_append_space();
  }
  if (leaders[leader].expand == -1) {
    text_append_label(0x95);
    text_append_space();
  }
  gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,local_a8,advisor_client_width);
  local_a8 = local_a8 + local_1c + 6;
  local_84 = advisor_client_x + 2;
  local_88 = advisor_client_width + advisor_client_x - 4;
  text_set_font(ADDR(0x63eab8, ((u8 *)&g.d_0063eab8)));
  local_1c = font_line_spacing((GameFont *)&advisor_bold_font);
  text_clear();
  text_append_label(0x98);
  text_append_colon();
  text_set_colors(0x7a,0x12,0xffffffff,0xffffffff);
  local_7c = gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_84,local_a8);
  text_clear();
  text_append_string_id(government_names[civs[civ].government]);
  text_set_colors(0x25,0x12,0xffffffff,0xffffffff);
  gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_7c,local_a8);
  city2 = -1;
  for (city = 0; city < game.num_cities; city++) {
    if (((cities[city].id != 0) && (cities[city].owner == civ)) &&
       (iVar3 = city_has_improvement(city,1), iVar3 != 0)) {
      city2 = city;
      break;
    }
  }
  text_clear();
  text_append_label(0x99);
  text_append_colon();
  text_append_city_name(city2);
  iVar3 = local_88;
  local_7c = font_text_width((GameFont *)&advisor_bold_font,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  local_7c = iVar3 - local_7c;
  text_clear();
  text_append_label(0x99);
  text_append_colon();
  text_set_colors(0x7a,0x12,0xffffffff,0xffffffff);
  local_7c = gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_7c,local_a8);
  text_clear();
  text_append_city_name(city2);
  text_set_colors(0x25,0x12,0xffffffff,0xffffffff);
  gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_7c,local_a8);
  local_a8 += local_1c;
  text_clear();
  text_append_label(0x9a);
  text_append_colon();
  text_set_colors(0x7a,0x12,0xffffffff,0xffffffff);
  local_7c = gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_84,local_a8);
  text_clear();
  text_append_gold(civs[civ].gold);
  text_set_colors(0x25,0x12,0xffffffff,0xffffffff);
  local_7c = gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_7c,local_a8);
  if (game.difficulty < 2) {
    local_7c += 6;
    text_clear();
    text_append_label(0x9b);
    text_append_colon();
    text_set_colors(0x7a,0x12,0xffffffff,0xffffffff);
    local_7c = gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_7c,local_a8);
    text_clear();
    text_append_int((int)civs[civ].num_military_units);
    text_append_space();
    text_append_label(0x19);
    text_set_colors(0x25,0x12,0xffffffff,0xffffffff);
    local_7c = gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_7c,local_a8);
  }
  text_clear();
  text_append_label(0xec);
  text_append_colon();
  str_clear((iptr)local_6c);
  if (civs[civ].researching < 0) {
    str_append_label((iptr)local_6c,0xe);
  }
  else {
    str_append_string_id((iptr)local_6c,advances[civs[civ].researching].name);
  }
  text_append((iptr)local_6c);
  iVar3 = local_88;
  local_7c = font_text_width((GameFont *)&advisor_bold_font,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  local_7c = iVar3 - local_7c;
  text_clear();
  text_append_label(0xec);
  text_append_colon();
  text_set_colors(0x7a,0x12,0xffffffff,0xffffffff);
  local_7c = gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_7c,local_a8);
  text_set_colors(0x25,0x12,0xffffffff,0xffffffff);
  local_7c = gfx_draw_text((iptr)local_6c,local_7c,local_a8);
  local_a8 = local_a8 + local_1c + 6;
  for (civ2 = 1; civ2 < 8; civ2++) {
    if (((civ2 != civ) && ((1 << ((byte)civ2 & 0x1f) & (uint)game.civs_alive) != 0)) &&
       ((*(byte *)&civs[civ].treaties[civ2] & 1) != 0)) {
      text_clear();
      str_clear((iptr)local_6c);
      if ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 0x20) == 0) {
        if ((*(byte *)&civs[civ].treaties[civ2] & 8) == 0) {
          if ((*(byte *)&civs[civ].treaties[civ2] & 4) == 0) {
            if ((*(byte *)&civs[civ].treaties[civ2] & 2) == 0) {
              str_append_label((iptr)local_6c,0x9d);
            }
            else {
              str_append_label((iptr)local_6c,0x8f);
            }
          }
          else {
            text_append_label(0x9c);
            text_append_space();
            str_append_label((iptr)local_6c,0x8e);
          }
        }
        else {
          str_append_label((iptr)local_6c,0x8d);
        }
      }
      else {
        text_append_label(0x9c);
        text_append_space();
        str_append_label((iptr)local_6c,0x90);
      }
      __strupr(local_6c);
      text_append((iptr)local_6c);
      text_append_space();
      text_append_label(0x7b);
      text_append_space();
      iVar1 = civ_leader_title(civ2);
      text_append(iVar1);
      text_append_space();
      iVar1 = civ_leader_name(civ2);
      text_append(iVar1);
      text_append_space();
      text_append_label(0x8c);
      text_append_space();
      iVar1 = civ_name_plural(civ2);
      text_append(iVar1);
      uVar7 = 0xffffffff;
      uVar6 = 0xffffffff;
      uVar5 = 0x12;
      uVar2 = civ_color_secondary(civ2);
      text_set_colors(uVar2,uVar5,uVar6,uVar7);
      gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,local_a8,advisor_client_width);
      local_a8 += local_1c;
    }
  }
  local_a8 += 6;
  local_98 = GetSystemMetrics(3);
  local_b8 -= (local_98 + 2);
  local_1c = 0x16;
  advisor_row_height = 0x16;
  advisor_list_top_i32 = local_a8;
  advisor_list_height_i32 = local_b8 - local_a8;
  advisor_rows_per_page = int_clamp((local_b8 - local_a8) / 0x16,0,99);
  local_8 = advisor_rows_per_page;
  if (0 < advisor_rows_per_page) {
    advisor_list_left_i32 = advisor_client_x + 2;
    local_88 = advisor_client_width + advisor_client_x - 2;
    advisor_list_width = local_88 - advisor_list_left_i32;
    advisor_column_width = advisor_list_width / 3;
    advisor_items_per_page = advisor_rows_per_page * 3;
    local_80 = 0;
    local_84 = advisor_list_left_i32;
    for (advance = 0; advance < 100; advance++) {
      iVar3 = civ_has_advance(civ,advance);
      if (iVar3 != 0) {
        local_80++;
      }
    }
    advisor_page_count_i32 = int_clamp((local_8 - 1 + local_80) / local_8,1,99);
    uVar2 = int_clamp(local_80 - 1,0,999);
    advisor_first_row = int_clamp(advisor_first_row,0,uVar2);
    local_a4 = 0;
    local_78 = 0;
    local_70 = 0;
    local_bc = local_a8;
    local_b4 = advisor_first_row;
    text_set_font(ADDR(0x63eab8, ((u8 *)&g.d_0063eab8)));
    for (advance = 0; advance < 100; advance++) {
      iVar4 = civ_has_advance(civ,advance);
      iVar3 = local_a4;
      if (((iVar4 != 0) && (iVar3 = local_a4 + 1, local_b4 <= local_a4)) &&
         (local_a4 < advisor_items_per_page + local_b4)) {
        local_bc = local_1c * local_70 + local_a8;
        local_b0 = advisor_column_width * local_78 + local_84;
        local_a4 = iVar3;
        sprite_draw
                  ((Sprite *)
                   (&advance_category_icon_sprites +
                   (char)advances[advance].epoch * 0x3c + (char)advances[advance].category * 0xf0)
                   ,(iptr)local_d0,ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),local_b0,local_bc);
        local_7c = local_b0 + 0x26;
        uVar6 = 1;
        uVar5 = 1;
        uVar2 = 0x12;
        iVar3 = civ_has_advance(human_civ,advance);
        text_set_colors((-(uint)(iVar3 == 0) & 0xffffffcb) + 0x5e,uVar2,uVar5,uVar6);
        iVar4 = local_bc + 2;
        iVar3 = local_7c;
        iVar1 = label_string(advances[advance].name);
        gfx_draw_text(iVar1,iVar3,iVar4);
        local_70++;
        iVar3 = local_a4;
        if (local_8 <= local_70) {
          local_70 = 0;
          local_78++;
          if (2 < local_78) break;
        }
      }
      local_a4 = iVar3;
    }
    if (advisor_controls_created == 0) {
      rect_set((iptr)local_18,local_84,local_b8,local_88,local_b8 + local_98);
      scrollbar_create
                ((Control *)&advisor_scrollbar,ADDR(0x63eb58, ((u8 *)&g.d_0063eb58)),200,(iptr)local_18,0);
      uVar2 = int_clamp((local_8 - 1 + local_80) / local_8 - 1,0,999);
      scrollbar_set_range((Control *)&advisor_scrollbar,0,uVar2);
      scrollbar_set_pos((ClickControl *)&advisor_scrollbar,advisor_first_row);
      scrollbar_set_page_size((Control *)&advisor_scrollbar,1);
      scrollbar_set_callback((Control *)&advisor_scrollbar,ADDR(0x403d23, intel_report_on_scroll));
      ctrl_show_and_redraw((Control *)&advisor_scrollbar);
      wnd_set_lbuttonup_handler((WndEventHandlers *)&advisor_wnd_events,ADDR(0x4036f2, intel_report_on_click));
      advisor_controls_created = 1;
    }
  }
  wnd_blit_surface((DibSurface *)&advisor_window);
  return;
}
#undef advisor_client_width
#undef advisor_client_x
#undef advisor_first_row
#undef advisor_report_param
#undef advisor_row_height
#undef diplo_cur_attitude
#undef human_civ
#undef advisor_page_count_i32
#undef advisor_list_top_i32
#undef advisor_list_height_i32
#undef advisor_list_left_i32
#undef local_d0
#undef civ3
#undef local_bc
#undef local_b8
#undef local_b4
#undef local_b0
#undef civ2
#undef local_a8
#undef local_a4
#undef city
#undef advance
#undef local_98
#undef city2
#undef local_90
#undef leader
#undef local_88
#undef local_84
#undef local_80
#undef local_7c
#undef local_78
#undef civ
#undef local_70
#undef local_6c
#undef local_1c
#undef local_18
#undef local_8

/* 00430267 auto */
#define advisor_first_row (*(int *)((u8 *)&g.d_0063ef70))
void __cdecl intel_report_on_scroll(int param_1)

{
  advisor_first_row = advisor_rows_per_page * param_1;
  intel_report_draw();
  return;
}
#undef advisor_first_row

/* 0043028a auto */
#define advisor_first_row (*(int *)((u8 *)&g.d_0063ef70))
#define advisor_report_param (*(iptr *)((u8 *)&g.d_0063efac))
#define advisor_row_height (*(int *)((u8 *)&g.d_0063ef80))
#define intel_report_reopen (*(i32 *)((u8 *)&g.d_00625ec4))
#define advisor_list_top_i32 (*(i32 *)((u8 *)&g.d_0063ef78))
#define local_18 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl intel_report_on_click(int param_1,int param_2)

{
  iptr civ;
  int iVar2;
  int iVar3;
  int iVar4;
  bool bVar5;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ = advisor_report_param;
  if ((((-1 < param_2 - advisor_list_top_i32) &&
       (iVar2 = (param_2 - advisor_list_top_i32) / advisor_row_height, iVar2 < advisor_rows_per_page)) &&
      (-1 < param_1 - 2)) && (iVar3 = (param_1 - 2) / advisor_column_width, iVar3 < 3)) {
    iVar3 = advisor_rows_per_page * iVar3 + advisor_first_row;
    local_14 = 0;
    for (local_18 = 0; local_18 < 100; local_18++) {
      iVar4 = civ_has_advance(civ,local_18);
      if ((iVar4 != 0) && (bVar5 = local_14 == iVar3 + iVar2, local_14 = local_14 + 1, bVar5)) {
        pedia_show_topic_modal((DocumentWindow *)&pedia_window,local_18);
        wnd_end_modal_loop((ModalMenuWindow *)&advisor_wnd);
        intel_report_reopen = 1;
        return;
      }
    }
  }
  return;
}
#undef advisor_first_row
#undef advisor_report_param
#undef advisor_row_height
#undef intel_report_reopen
#undef advisor_list_top_i32
#undef local_18
#undef local_14

/* 0043039d auto */
#define advisor_report_param (*(iptr *)((u8 *)&g.d_0063efac))
#define intel_report_reopen (*(i32 *)((u8 *)&g.d_00625ec4))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(0)))
#define city (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_308 (*(Dialog *)(frame_ + FRAME_OFF(8)))
#define civ (*(iptr *)(frame_ + FRAME_OFF(764)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(768)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(772)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(776)))
void __cdecl intel_report_on_cities_clicked(void)

{
  iptr iVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(784)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_308,0x4000);
  local_8 = 0;
  civ = advisor_report_param;
  iVar1 = civ_name_plural(advisor_report_param);
  text_set_string_arg(0,iVar1);
  dialog_load_game_text(&local_308,ADDR(0x625f30, ((u8 *)&g.d_00625f30)));
  for (city = 0; city < game.num_cities; city++) {
    if ((cities[city].id != 0) && (cities[city].owner == civ)) {
      text_clear();
      text_append(city * 0x58 + ADDR(0x64f360, ((u8 *)&cities + 32)));
      iVar2 = city_has_improvement(city,1);
      if (iVar2 != 0) {
        text_append_space();
        text_append_lparen();
        text_append_label(0x99);
        text_append_rparen();
      }
      if (cities[city].building < -0x26) {
        if (cities[city].building < 1) {
          improvement = ~(int)cities[city].building + 1;
        }
        else {
          improvement = (iptr)cities[city].building;
        }
        text_append_space();
        text_append_lparen();
        text_append_label(0xf4);
        text_append_space();
        text_append_string_id(improvements[improvement].name);
        text_append_rparen();
      }
      dialog_add_option((DialogOptionList *)&local_308,ADDR(0x679640, ((u8 *)&g.d_00679640)),city,0);
    }
  }
  wnd_disable((WndBase *)&advisor_wnd);
  dlg_show_modal(&local_308,0);
  wnd_enable((WndBase *)&advisor_wnd);
  wnd_end_modal_loop((ModalMenuWindow *)&advisor_wnd);
  intel_report_reopen = 1;
  local_8 = 0xffffffff;
  /* inlined unwind funclet 004305e7 */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
  return;
}
#undef advisor_report_param
#undef intel_report_reopen
#undef improvement
#undef city
#undef local_308
#undef civ
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0043060b auto */
#define advisor_client_x (*(i32 *)((u8 *)&g.d_0063ec34))
#define advisor_report_param (*(iptr *)((u8 *)&g.d_0063efac))
#define intel_report_reopen (*(int *)((u8 *)&g.d_00625ec4))
#define advisor_modal_start_ticks_i32 (*(i32 *)((u8 *)&g.d_00625ec0))
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
/* WARNING: Removing unreachable block (ram,0x004306c1) */
/* WARNING: Removing unreachable block (ram,0x0043074c) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl intel_report_show(iptr param_1,iptr param_2)

{
  int iVar1;
  int iVar2;
  iptr iVar3;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  picwnd_open((PictureWindow *)&advisor_window,3,3,1,600,400,0,0);
  advisor_report_civ = param_1;
  advisor_report_param = param_2;
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
  iVar3 = label_string(*(i32 *)(label_string_ids + 0x314));
  button_create
            ((Control *)&advisor_toggle_button,ADDR(0x63eb58, ((u8 *)&g.d_0063eb58)),0x65,(iptr)local_14,iVar3);
  button_set_callback((Control *)&advisor_toggle_button,ADDR(0x402261, intel_report_on_cities_clicked));
  wnd_set_redraw_callback((SurfaceWindow *)&advisor_window,ADDR(0x402766, intel_report_draw));
  wnd_repaint((SurfaceWindow *)&advisor_window);
  window_show((WindowObjectView *)&advisor_window);
  do {
    intel_report_reopen = 0;
    if (2 < game.multiplayer) {
      wnd_set_modal_idle_callback((ModalMenuWindow *)&advisor_wnd,ADDR(0x402789, advisor_mp_idle));
    }
    advisor_modal_start_ticks_i32 = timer_ticks();
    wnd_run_modal_loop((ModalMenuWindow *)&advisor_wnd);
    wnd_set_modal_idle_callback((ModalMenuWindow *)&advisor_wnd,0);
  } while (intel_report_reopen != 0);
  picwnd_close((PictureWindowCore *)&advisor_window);
  return;
}
#undef advisor_client_x
#undef advisor_report_param
#undef intel_report_reopen
#undef advisor_modal_start_ticks_i32
#undef local_14

/* 004308ae auto */
#define diplo_cur_attitude (*(i32 *)((u8 *)&g.d_0064b114))
#define dlg_pending_idle_callback (*(i8 * *)((u8 *)&g.d_00635a3c))
#define mp_meeting_pending (*(i32 *)((u8 *)&g.d_00626a2c))
#define mp_meeting_reply (*(int *)((u8 *)&g.d_0063f278))
#define mp_show_human_starts (*(short *)((u8 *)&g.d_00654c78))
#define net_host_handoff_stage (*(char *)((u8 *)&g.d_006ad698))
#define nm_parley_cancel_count (*(int *)((u8 *)&g.d_006c91e4))
#define parley_other_civ (*(iptr *)((u8 *)&g.d_0067a8c0))
#define scenario_events_loaded (*(int *)((u8 *)&g.d_00627670))
#define mp_meeting_wait_start_i32 (*(i32 *)((u8 *)&g.d_0063e4e8))
#define local_330 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_32c (*(byte (*)[12])(frame_ + FRAME_OFF(4)))
#define local_320 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_31c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_318 (*(iptr *)(frame_ + FRAME_OFF(24)))
#define local_314 (*(int *)(frame_ + FRAME_OFF(28)))
#define local_310 (*(Dialog *)(frame_ + FRAME_OFF(32)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(788)))
#define civ2 (*(iptr *)(frame_ + FRAME_OFF(792)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(796)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(800)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(804)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(808)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl foreign_minister_show(iptr civ)

{
  iptr iVar1;
  int iVar2;
  iptr iVar3;
  i32 uVar4;
  iptr iVar4;
  i8 frame_[FRAME_OFF(816)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_310,0x4000);
  local_8 = 0;
  if ((game.multiplayer < 3) || (parley_wnd_closed != 0)) {
    while( true ) {
      while( true ) {
        iVar2 = int_clamp((uint)game.power_rank[civ],1,7);
        text_set_label_arg(0,*(i32 *)(label_string_ids + 0x38c + iVar2 * 4));
        iVar2 = int_clamp((uint)civs[civ].reputation,0,7);
        text_set_label_arg(1,*(i32 *)(label_string_ids + 0x370 + iVar2 * 4));
        if (game.multiplayer == '\0') {
          dlg_load_game_section(&local_310,ADDR(0x625f3c, ((u8 *)&g.d_00625f3c)),0x2000001);
        }
        else {
          dlg_load_game_section(&local_310,ADDR(0x625f4c, ((u8 *)&g.d_00625f4c)),0x2000001);
        }
        dialog_set_option_draw_fn((DialogOptionList *)&local_310,ADDR(0x402e91, foreign_minister_draw_civ_city));
        dialog_set_list_indent((DialogCore *)&local_310,0x4b,0);
        local_314 = 0;
        iVar2 = civ_has_wonder(civ,0x18);
        if ((iVar2 == 0) && (iVar2 = civ_has_wonder(civ,9), iVar2 == 0)) {
          local_31c = 0;
        }
        else {
          local_31c = 1;
        }
        if (((game.wonder_city[0x18] == -1) && (iVar2 = civ_has_wonder(civ,9), iVar2 == 0))
           && (game.reveal_map == '\0')) {
          local_14 = 0;
        }
        else {
          local_14 = 1;
        }
        for (civ2 = 1; civ2 < 8; civ2++) {
          if ((civ2 != civ) && ((1 << ((byte)civ2 & 0x1f) & (uint)game.civs_alive) != 0)
             ) {
            if ((((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) ||
                ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) == 0)) ||
               ((mp_show_human_starts == 0 && (game.difficulty != '\0')))) {
              local_1c = 0;
            }
            else {
              local_1c = 1;
            }
            if (((local_14 != 0) || (local_1c != 0)) ||
               ((*(byte *)&civs[civ].treaties[civ2] & 1) != 0)) {
              local_314++;
              text_clear();
              iVar3 = civ_leader_title(civ2);
              text_append(iVar3);
              text_append_space();
              iVar3 = civ_leader_name(civ2);
              text_append(iVar3);
              text_append_space();
              text_append_label(0x8c);
              text_append_space();
              iVar3 = civ_name_plural(civ2);
              text_append(iVar3);
              text_append_space();
              diplo_eval_ai_stance(civ,civ2);
              local_318 = diplo_attitude_level(diplo_cur_attitude);
              text_append_lparen();
              text_append_string_id(attitude_names[local_318]);
              if ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 0x20) == 0) {
                if ((*(byte *)&civs[civ].treaties[civ2] & 8) == 0) {
                  if ((*(byte *)&civs[civ].treaties[civ2] & 4) == 0) {
                    if ((*(byte *)&civs[civ].treaties[civ2] & 2) != 0) {
                      text_append_comma();
                      text_append_label(0x8f);
                    }
                  }
                  else {
                    text_append_comma();
                    text_append_label(0x8e);
                  }
                }
                else {
                  text_append_comma();
                  text_append_label(0x8d);
                }
              }
              else {
                text_append_comma();
                text_append_label(0x90);
              }
              if (((*(byte *)&civs[civ].treaties[civ2] & 0x80) == 0) &&
                 (local_31c == 0)) {
                text_append_comma();
                text_append_label(0x91);
              }
              else {
                text_append_comma();
                text_append_gold(civs[civ2].gold);
                if (game.difficulty < 2) {
                  text_append_comma();
                  text_append_int((int)civs[civ2].num_military_units);
                  text_append_space();
                  text_append_label(0x19);
                }
              }
              text_append_rparen();
              dialog_add_option((DialogOptionList *)&local_310,ADDR(0x679640, ((u8 *)&g.d_00679640)),civ2,0);
            }
          }
        }
        if (local_314 == 0) {
          popup_game(ADDR(0x625f60, ((u8 *)&g.d_00625f60)));
          local_8 = 0xffffffff;
          /* inlined unwind funclet 0043154f */ { dialog_dtor((Dialog *)((iptr)&local_310)); }
          goto LAB_00431565;
        }
        civ2 = dlg_show_modal(&local_310,0);
        if (((*(i8 *)((char *)&local_310.field_3c + 1)) & 0x20) != 0) {
          local_310.field_dc = 2;
        }
        if (local_310.field_dc == 0) {
          local_8 = 0xffffffff;
          /* inlined unwind funclet 0043154f */ { dialog_dtor((Dialog *)((iptr)&local_310)); }
          goto LAB_00431565;
        }
        if (local_310.field_dc != 1) break;
        if ((((*(byte *)&civs[civ].treaties[civ2] & 0x80) == 0) &&
            (local_31c == 0)) && (game.reveal_map == '\0')) {
          popup_game_with_sprite(ADDR(0x625ff8, ((u8 *)&g.d_00625ff8)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        }
        else {
          intel_report_show(civ,civ2);
        }
      }
      if (local_310.field_dc == 2) break;
      if (local_310.field_dc != 3) goto LAB_0043153e;
      text_clear();
      iVar3 = civ_leader_title(civ2);
      text_append(iVar3);
      text_append_space();
      iVar3 = civ_leader_name(civ2);
      text_append(iVar3);
      text_append_space();
      text_append_label(0x8c);
      text_append_space();
      iVar3 = civ_name_plural(civ2);
      text_append(iVar3);
      text_set_string_arg(0,ADDR(0x679640, ((u8 *)&g.d_00679640)));
      local_318 = dialog_load_text(&local_310,ADDR(0x625f7c, ((u8 *)&g.d_00625f7c)),ADDR(0x625f6c, ((u8 *)&g.d_00625f6c)),1);
      if (local_318 == 0) {
        dialog_set_columns((DialogButtonsView *)&local_310,3);
        for (local_318 = 0; local_318 < 9; local_318++) {
          uVar4 = 0;
          iVar4 = local_318;
          iVar3 = label_string(attitude_names[local_318]);
          dialog_add_option((DialogOptionList *)&local_310,iVar3,iVar4,uVar4);
        }
        if (*(char *)&civs[civ].attitude[civ2] == '\0') {
          local_330 = 0;
        }
        else {
          local_330 = diplo_attitude_level((uint)civs[civ].attitude[civ2]);
        }
        dialog_set_default_choice((DialogOptionList *)&local_310,local_330);
        local_318 = dlg_show_modal(&local_310,0);
        if (-1 < local_318) {
          local_32c[0] = 0;
          local_32c[1] = 5;
          local_32c[2] = 0x11;
          local_32c[3] = 0x1f;
          local_32c[4] = 0x32;
          local_32c[5] = 0x44;
          local_32c[6] = 0x52;
          local_32c[7] = 0x5f;
          local_32c[8] = 100;
          civs[civ].attitude[civ2] = local_32c[local_318];
          net_send_message(0x98,0xff,civ,civ2,(uint)local_32c[local_318],0,0,0,0,0);
        }
      }
    }
    if ((scenario_events_loaded == 0) ||
       (iVar2 = events_check_negotiation((ScenarioEvents *)&scenario_events,civ,civ2)
       , iVar2 != 0)) {
      if ((((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) ||
          ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0)) &&
         (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0 || (2 < game.multiplayer)))
         ) {
        if ((((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) &&
            ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0)) &&
           (2 < game.multiplayer)) {
          diplo_set_treaty_flags(civ,civ2,0x401);
          mp_meeting_reply = -1;
          mp_meeting_pending = 1;
          net_send_text_args(0x3d,*(i32 *)
                                   (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),0
                             ,0,civ,0);
          iVar3 = civ_leader_name(civ2);
          text_set_string_arg(1,iVar3);
          iVar3 = civ_name_plural(civ2);
          text_set_string_arg(2,iVar3);
          dlg_pending_idle_callback = ((void *)ADDR(0x0040326a, mp_meeting_wait_idle));
          mp_meeting_wait_start_i32 = timer_ticks();
          local_320 = popup_game_sprite_flags(ADDR(0x625f94, ((u8 *)&g.d_00625f94)),0x2000001,ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
          if (nm_parley_cancel_count == 0) {
            if (local_320 == -1) {
              net_send_message(0x81,*(i32 *)
                                       (&net_player_slots +
                                       *(int *)(&net_civ_slots + civ2 * 4) * 0x54),0,0,0,0,0,0,0,
                                 0);
              parley_other_civ = -1;
              mp_meeting_pending = 0;
            }
            else if (mp_meeting_reply < 1) {
              dlg_pending_idle_callback = ((void *)ADDR(0x00403c74, turn_popup_timeout_idle));
              popup_game_with_sprite(ADDR(0x625fb4, ((u8 *)&g.d_00625fb4)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
              mp_meeting_pending = 0;
            }
            else if (mp_meeting_reply == 1) {
              mp_meeting_reply = -1;
              parley_other_civ = civ2;
              dlg_pending_idle_callback = ((void *)ADDR(0x0040326a, mp_meeting_wait_idle));
              mp_meeting_wait_start_i32 = timer_ticks();
              iVar3 = civ_name_plural(civ);
              text_set_string_arg(0,iVar3);
              popup_game_with_sprite(ADDR(0x625fc4, ((u8 *)&g.d_00625fc4)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
              if (net_host_handoff_stage == '\0') {
                if (nm_parley_cancel_count == 0) {
                  parley_wnd_open((ViewWindow *)&parley_wnd,civ2,3);
                }
                else {
                  parley_other_civ = -1;
                  nm_parley_cancel_count = 0;
                  iVar3 = civ_name_plural(civ2);
                  text_set_string_arg(0,iVar3);
                  dlg_pending_idle_callback = ((void *)ADDR(0x00403c74, turn_popup_timeout_idle));
                  popup_game_with_sprite(ADDR(0x625fdc, ((u8 *)&g.d_00625fdc)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
                  mp_meeting_pending = 0;
                }
              }
              else {
                parley_other_civ = -1;
                dlg_pending_idle_callback = ((void *)ADDR(0x00403c74, turn_popup_timeout_idle));
                popup_game_with_sprite(ADDR(0x625fd0, ((u8 *)&g.d_00625fd0)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
                mp_meeting_pending = 0;
              }
            }
            else {
              dlg_pending_idle_callback = ((void *)ADDR(0x00403c74, turn_popup_timeout_idle));
              popup_game_with_sprite(ADDR(0x625fec, ((u8 *)&g.d_00625fec)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
              mp_meeting_pending = 0;
            }
          }
          else {
            nm_parley_cancel_count = 0;
            iVar3 = civ_name_plural(civ2);
            text_set_string_arg(0,iVar3);
            dlg_pending_idle_callback = ((void *)ADDR(0x00403c74, turn_popup_timeout_idle));
            popup_game_with_sprite(ADDR(0x625fa4, ((u8 *)&g.d_00625fa4)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
            parley_other_civ = -1;
            mp_meeting_pending = 0;
          }
        }
      }
      else {
        diplo_set_treaty_flags(civ,civ2,0x401);
        diplo_ai_meet_player(civ,civ2,0xffffffff,0xffffffff,1);
      }
    }
    else {
      popup_game(ADDR(0x625f84, ((u8 *)&g.d_00625f84)));
    }
LAB_0043153e:
    local_8 = 0xffffffff;
    /* inlined unwind funclet 0043154f */ { dialog_dtor((Dialog *)((iptr)&local_310)); }
  }
  else {
    iVar1 = wnd_get_window((WndBase *)&parley_wnd_frame);
    BringWindowToTop(*(HWND *)(iVar1 + 4));
    local_8 = 0xffffffff;
    /* inlined unwind funclet 0043154f */ { dialog_dtor((Dialog *)((iptr)&local_310)); }
  }
LAB_00431565:
  return;
}
#undef diplo_cur_attitude
#undef dlg_pending_idle_callback
#undef mp_meeting_pending
#undef mp_meeting_reply
#undef mp_show_human_starts
#undef net_host_handoff_stage
#undef nm_parley_cancel_count
#undef parley_other_civ
#undef scenario_events_loaded
#undef mp_meeting_wait_start_i32
#undef local_330
#undef local_32c
#undef local_320
#undef local_31c
#undef local_318
#undef local_314
#undef local_310
#undef local_1c
#undef civ2
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00431d22 auto */
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
#define local_650 (*(GamePalette * *)(frame_ + FRAME_OFF(0)))
#define local_648 (*(DibSurface * *)(frame_ + FRAME_OFF(8)))
#define civ (*(iptr *)(frame_ + FRAME_OFF(16)))
#define local_63c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_638 (*(GameFont *)(frame_ + FRAME_OFF(24)))
#define local_630 (*(u32 *)(frame_ + FRAME_OFF(32)))
#define local_62c (*(int *)(frame_ + FRAME_OFF(36)))
#define local_628 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_624 (*(int *)(frame_ + FRAME_OFF(44)))
#define local_620 (*(i8 (*)[736])(frame_ + FRAME_OFF(48)))
#define local_340 (*(Dialog *)(frame_ + FRAME_OFF(784)))
#define local_4c (*(i32 *)(frame_ + FRAME_OFF(1540)))
#define local_48 (*(i32 *)(frame_ + FRAME_OFF(1544)))
#define local_44 (*(int *)(frame_ + FRAME_OFF(1548)))
#define local_40 (*(int *)(frame_ + FRAME_OFF(1552)))
#define local_3c (*(int *)(frame_ + FRAME_OFF(1556)))
#define local_38 (*(u32 *)(frame_ + FRAME_OFF(1560)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(1564)))
#define local_30 (*(iptr *)(frame_ + FRAME_OFF(1568)))
#define local_2c (*(u32 *)(frame_ + FRAME_OFF(1572)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(1576)))
#define local_24 (*(u8 (*)[4])(frame_ + FRAME_OFF(1580)))
#define local_20 (*(u8 (*)[4])(frame_ + FRAME_OFF(1584)))
#define local_1c (*(uint *)(frame_ + FRAME_OFF(1588)))
#define local_18 (*(DibSurface * *)(frame_ + FRAME_OFF(1592)))
#define local_14 (*(GamePalette * *)(frame_ + FRAME_OFF(1596)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1600)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1604)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(1608)))
void __cdecl powergraph_show(void)

{
  int iVar1;
  DibSurface *this;
  GamePalette *this_00;
  i32 uVar2;
  int iVar3;
  int iVar4;
  iptr iVar5;
  i32 uVar6;
  i32 uVar7;
  i32 uVar8;
  i32 uVar9;
  i32 uVar10;
  i32 uVar11;
  i32 uVar12;
  i32 uVar13;
  i8 frame_[FRAME_OFF(1616)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  frame_wnd_ctor((SurfaceWindow *)local_620);
  local_8 = 0;
  font_init_empty((GameFont *)(local_620 + 0x2d8));
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  font_init_empty(&local_638);
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  dialog_ctor(&local_340,0x4000);
  (*(i8 *)((char *)&local_8 + 0)) = 3;
  local_18 = (DibSurface *)0x0;
  local_14 = (GamePalette *)0x0;
  font_set_styled((GameFont *)(local_620 + 0x2d8),0,0xc,1);
  font_set_styled(&local_638,0,0xe,1);
  this = operator_new(0x48);
  (*(i8 *)((char *)&local_8 + 0)) = 4;
  if (this == (DibSurface *)0x0) {
    local_648 = (DibSurface *)0x0;
  }
  else {
    local_648 = (DibSurface *)surface_ctor(this);
  }
  (*(i8 *)((char *)&local_8 + 0)) = 3;
  local_18 = local_648;
  this_00 = operator_new(0x434);
  (*(i8 *)((char *)&local_8 + 0)) = 5;
  if (this_00 == (GamePalette *)0x0) {
    local_650 = (GamePalette *)0x0;
  }
  else {
    local_650 = (GamePalette *)palette_init(this_00);
  }
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),3);
  local_14 = local_650;
  surface_load_gif_resource(local_18,0x33,10,0xc0,(iptr)local_650);
  uVar13 = 0;
  uVar12 = 0;
  uVar11 = 0;
  uVar10 = 0x1a9;
  uVar9 = 600;
  uVar8 = 0x14;
  uVar7 = 0;
  uVar6 = 0xd;
  uVar2 = label_string(*(i32 *)(label_string_ids + 0x358));
  frame_wnd_create
            ((FrameWindow *)local_620,uVar2,uVar6,uVar7,uVar8,uVar9,uVar10,uVar11,uVar12,uVar13);
  text_set_surface((iptr)local_620);
  text_set_font((iptr)(local_620 + 0x2d8));
  local_630 = (*(i32 *)((char *)&local_620 + 292));
  local_38 = (*(i32 *)((char *)&local_620 + 296));
  frame_wnd_layout((FrameWindow *)local_620);
  frame_wnd_draw_caption((FrameWindow *)local_620);
  gfx_copy_rect_xywh((iptr)local_18,(iptr)local_620,0,0,local_630,local_38,600,400);
  local_2c = (*(i32 *)((char *)&local_620 + 700));
  local_24[0] = local_620[0x2c4];
  local_24[1] = local_620[0x2c5];
  local_24[2] = local_620[0x2c6];
  local_24[3] = local_620[0x2c7];
  local_20[0] = local_620[0x2c8];
  local_20[1] = local_620[0x2c9];
  local_20[2] = local_620[0x2ca];
  local_20[3] = local_620[0x2cb];
  local_28 = (*(i32 *)((char *)&local_620 + 704)) + 400;
  gfx_fill_rect((iptr)local_620,(iptr)&local_2c,0x14);
  rect_set_xywh((iptr)&local_2c,local_630 + 8,local_38 + 2,0x248,0x16e);
  gfx_draw_rect_frame((iptr)local_620,(iptr)&local_2c,10);
  if (((game.game_flags & 0x80) == 0) || ((scenario_flags & 2) == 0)) {
    local_30 = (int)((int)game.turn + ((int)game.turn >> 0x1f & 3U)) >> 2;
  }
  else {
    local_30 = (int)game.turn / 2;
  }
  local_30 = int_clamp(local_30,0,0x96);
  if (((game.game_flags & 0x80) == 0) || ((scenario_flags & 2) == 0)) {
    local_34 = 0x32;
  }
  else {
    local_34 = 0x19;
  }
  local_1c = 0x32;
  for (civ = 1; civ < 8; civ++) {
    for (local_3c = 0; local_3c < local_30; local_3c++) {
      if (local_1c < (byte)(&power_graph_history)[local_3c * 8 + civ]) {
        local_1c = (uint)(byte)(&power_graph_history)[local_3c * 8 + civ];
      }
    }
  }
  for (local_3c = 0; (local_3c <= game.turn && (local_3c < 0x259)); local_3c += local_34)
  {
    if (((game.game_flags & 0x80) == 0) || ((scenario_flags & 2) == 0)) {
      local_624 = local_3c;
    }
    else {
      local_624 = local_3c * 2;
    }
    gfx_draw_line_color((iptr)local_620,local_624 + local_630 + 8,local_38 + 2,
                       local_624 + local_630 + 8,local_38 + 0x170,10);
    if (local_3c % (local_34 * 2) == 0) {
      local_4c = game_turn_to_year(local_3c + 1);
      text_clear();
      text_append_year(local_4c);
      text_set_colors(0x25,10,2,1);
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_624 + local_630,local_38 + 0x172);
    }
  }
  surface_set_clip((DibSurface *)local_620,(iptr)&local_2c);
  for (civ = 1; civ < 8; civ++) {
    if (((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0) ||
       ((1 << ((byte)civ & 0x1f) & (uint)game.civs_at_start) != 0)) {
      local_628 = 0;
      local_62c = 0;
      for (local_3c = 0; (local_3c < local_30 && (local_3c < 0x96)); local_3c++) {
        local_40 = local_3c * 4;
        local_44 = (int)((uint)(byte)(&power_graph_history)[local_3c * 8 + civ] * 0x168) /
                   (int)local_1c;
        gfx_draw_line_color((iptr)local_620,local_628 + local_630 + 9,(local_38 - local_62c) + 0x171,
                           local_40 + local_630 + 9,(local_38 - local_44) + 0x171,0x12);
        local_628 = local_40;
        local_62c = local_44;
      }
    }
  }
  surface_set_clip((DibSurface *)local_620,(iptr)(local_620 + 700));
  text_set_font((iptr)&local_638);
  local_63c = 0;
  for (civ = 1; civ < 8; civ++) {
    if (((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0) ||
       ((1 << ((byte)civ & 0x1f) & (uint)game.civs_at_start) != 0)) {
      local_48 = civ_color_primary(civ);
      text_set_colors(local_48,10,2,1);
      iVar1 = local_63c + 1;
      iVar3 = local_63c * 0xe + local_38 + 1;
      iVar4 = local_630 + 10;
      iVar5 = civ_name_plural(civ);
      gfx_draw_text(iVar5,iVar4,iVar3);
      local_628 = 0;
      local_62c = 0;
      for (local_3c = 0; (local_63c = iVar1, local_3c < local_30 && (local_3c < 0x96));
          local_3c = local_3c + 1) {
        local_40 = local_3c * 4;
        local_44 = (int)((uint)(byte)(&power_graph_history)[local_3c * 8 + civ] * 0x168) /
                   (int)local_1c;
        gfx_draw_line_color((iptr)local_620,local_628 + local_630 + 8,(local_38 + 0x170) - local_62c,
                           local_40 + local_630 + 8,(local_38 + 0x170) - local_44,local_48);
        local_628 = local_40;
        local_62c = local_44;
      }
    }
  }
  window_show((WindowObjectView *)local_620);
  dialog_init(&local_340,(iptr)local_620,0,0,0x114000);
  local_340.field_40 = (*(i32 *)((char *)&local_620 + 300));
  local_340.field_44 = (*(i32 *)((char *)&local_620 + 304));
  local_340.field_e8 = (*(i32 *)((char *)&local_620 + 292));
  local_340.field_ec = (*(i32 *)((char *)&local_620 + 296));
  dlg_show_modal(&local_340,0);
  if (local_18 != (DibSurface *)0x0) {
    surface_delete(local_18,1);
  }
  if (local_14 != (GamePalette *)0x0) {
    palette_scalar_dtor(local_14,1);
  }
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  /* inlined unwind funclet 004325c9 */ { dialog_dtor((Dialog *)((iptr)&local_340)); }
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  /* inlined unwind funclet 004325d5 */ { font_destroy((GameFont *)((iptr)&local_638)); }
  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
  /* inlined unwind funclet 004325e1 */ { font_destroy((GameFont *)((iptr)((u8 *)&local_620 + 0x2d8))); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet 004325ed */ { frame_wnd_dtor((DibSurface *)((iptr)&local_620)); }
  return;
}
#undef scenario_flags
#undef local_650
#undef local_648
#undef civ
#undef local_63c
#undef local_638
#undef local_630
#undef local_62c
#undef local_628
#undef local_624
#undef local_620
#undef local_340
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
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00432611 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define civ (*(iptr *)(frame_ + FRAME_OFF(4)))
#define civ2 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_38c (*(int *)(frame_ + FRAME_OFF(12)))
#define city (*(iptr *)(frame_ + FRAME_OFF(16)))
#define local_384 (*(int *)(frame_ + FRAME_OFF(20)))
#define local_380 (*(Dialog *)(frame_ + FRAME_OFF(24)))
#define local_8c (*(int *)(frame_ + FRAME_OFF(780)))
#define local_88 (*(int *)(frame_ + FRAME_OFF(784)))
#define local_84 (*(i8 (*)[80])(frame_ + FRAME_OFF(788)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(868)))
#define aiStack_30 (*(int (*)[8])(frame_ + FRAME_OFF(872)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(904)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(908)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(912)))
void __cdecl historian_report_show(void)

{
  int iVar1;
  int iVar2;
  iptr iVar3;
  i8 frame_[FRAME_OFF(920)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_380,0x2000);
  local_8 = 0;
  iVar1 = text_open_section(ADDR(0x6558e8, ((u8 *)&g.d_006558e8)),ADDR(0x626010, ((u8 *)&g.d_00626010)));
  if (iVar1 == 0) {
    text_read_line(1);
    iVar1 = _atoi(&text_buffer);
    if (iVar1 != 0) {
      local_8c = rand_range(0,iVar1 - 1);
      for (local_38c = 0; local_38c <= local_8c; local_38c++) {
        text_read_line(1);
      }
      text_set_string_arg(1,ADDR(0x679640, ((u8 *)&g.d_00679640)));
      iVar1 = rand_range(0,4);
      text_read_section_line(ADDR(0x6558e8, ((u8 *)&g.d_006558e8)),ADDR(0x62601c, ((u8 *)&g.d_0062601c)),iVar1);
      text_set_string_arg(2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
      dlg_load_game_section(&local_380,ADDR(0x626028, ((u8 *)&g.d_00626028)),0x40000);
      dialog_add_line
                ((DialogAddLineView *)&local_380,ADDR(0x626030, ((u8 *)&g.d_00626030)),0xffffffff,0xffffffff,0xffffffff,0);
      for (civ = 0; civ < 8; civ++) {
        aiStack_30[civ] = 0;
      }
      for (city = 0; city < game.num_cities; city++) {
        if (cities[city].id != 0) {
          if (iVar1 == 3) {
            aiStack_30[cities[city].owner] =
                 aiStack_30[cities[city].owner] +
                 (((int)cities[city].size + (int)(char)cities[city].happy) -
                 (int)(char)cities[city].unhappy);
          }
          else if (iVar1 == 4) {
            aiStack_30[cities[city].owner] =
                 aiStack_30[cities[city].owner] + (int)cities[city].size;
          }
        }
      }
      for (civ = 0; civ < 8; civ++) {
        if (iVar1 == 0) {
          aiStack_30[civ] += civs[civ].gold;
        }
        else if (iVar1 == 1) {
          aiStack_30[civ] += (uint)civs[civ].military_strength;
        }
        else if (iVar1 == 2) {
          for (local_384 = 0; local_384 < 100; local_384++) {
            iVar2 = civ_has_advance(civ,local_384);
            if (iVar2 != 0) {
              aiStack_30[civ]++;
            }
          }
        }
      }
      iVar1 = text_open_section(ADDR(0x6558e8, ((u8 *)&g.d_006558e8)),ADDR(0x626034, ((u8 *)&g.d_00626034)));
      if (iVar1 == 0) {
        for (local_88 = 1; local_88 < 8; local_88++) {
          text_read_line(1);
          crt_strcpy(local_84,&text_buffer);
          civ2 = -1;
          local_34 = 0;
          for (civ = 1; civ < 8; civ++) {
            if ((local_34 <= aiStack_30[civ]) &&
               ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0)) {
              local_34 = aiStack_30[civ];
              civ2 = civ;
            }
          }
          if (civ2 < 0) break;
          aiStack_30[civ2] = -1;
          text_clear();
          text_append(ADDR(0x626040, ((u8 *)&g.d_00626040)));
          text_append_int(local_88);
          text_append_period();
          text_append_label(0x174);
          text_append_space();
          text_append((iptr)local_84);
          text_append_space();
          text_append_label(0xd9);
          if (game_language == 2) {
            text_append_colon();
          }
          else {
            text_append_space();
            text_append_label(0x8c);
            text_append_space();
          }
          iVar3 = civ_name_plural(civ2);
          text_append(iVar3);
          if (((human_civ == civ2) ||
              ((*(byte *)&civs[human_civ].treaties[civ2] & 1) != 0)) ||
             (game.difficulty == '\0')) {
            dialog_add_line
                      ((DialogAddLineView *)&local_380,ADDR(0x679640, ((u8 *)&g.d_00679640)),0xffffffff,0xffffffff,0xffffffff,0);
          }
        }
        dlg_show_modal(&local_380,0);
      }
    }
  }
  local_8 = 0xffffffff;
  /* inlined unwind funclet 00432bf8 */ { dialog_dtor((Dialog *)((iptr)&local_380)); }
  return;
}
#undef human_civ
#undef text_buffer
#undef civ
#undef civ2
#undef local_38c
#undef city
#undef local_384
#undef local_380
#undef local_8c
#undef local_88
#undef local_84
#undef local_34
#undef aiStack_30
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00432c1c auto */
#define advisor_client_width (*(int *)((u8 *)&g.d_0063ec3c))
#define advisor_client_x (*(int *)((u8 *)&g.d_0063ec34))
#define advisor_row_height (*(i32 *)((u8 *)&g.d_0063ef80))
#define advisor_list_top_i32 (*(i32 *)((u8 *)&g.d_0063ef78))
#define advisor_list_height_i32 (*(i32 *)((u8 *)&g.d_0063ef7c))
#define local_8c (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define aiStack_7c (*(iptr (*)[5])(frame_ + FRAME_OFF(20)))
#define local_68 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_64 (*(int *)(frame_ + FRAME_OFF(44)))
#define local_60 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_5c (*(int *)(frame_ + FRAME_OFF(52)))
#define city (*(iptr *)(frame_ + FRAME_OFF(56)))
#define local_54 (*(int *)(frame_ + FRAME_OFF(60)))
#define local_50 (*(int *)(frame_ + FRAME_OFF(64)))
#define local_4c (*(int *)(frame_ + FRAME_OFF(68)))
#define local_48 (*(int *)(frame_ + FRAME_OFF(72)))
#define local_44 (*(int *)(frame_ + FRAME_OFF(76)))
#define local_40 (*(int *)(frame_ + FRAME_OFF(80)))
#define local_3c (*(iptr *)(frame_ + FRAME_OFF(84)))
#define local_38 (*(iptr *)(frame_ + FRAME_OFF(88)))
#define local_34 (*(iptr *)(frame_ + FRAME_OFF(92)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(96)))
#define iStack_2c (*(iptr *)(frame_ + FRAME_OFF(100)))
#define aiStack_28 (*(int (*)[4])(frame_ + FRAME_OFF(104)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(120)))
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(124)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl top_cities_draw(void)

{
  iptr iVar1;
  i32 uVar2;
  i32 uVar3;
  i32 uVar4;
  i32 uVar5;
  i8 frame_[FRAME_OFF(144)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_34 = 0; local_34 < 5; local_34++) {
    aiStack_7c[local_34] = -1;
    (&iStack_2c)[local_34] = aiStack_7c[local_34];
  }
  city = 0;
  while( true ) {
    if (game.num_cities <= city) {
      frame_wnd_layout((FrameWindow *)&advisor_window);
      frame_wnd_draw_caption((FrameWindow *)&advisor_window);
      picwnd_blit((PictureWindow *)&advisor_window);
      local_5c = advisor_client_y + 2;
      local_68 = advisor_client_y + 0x174;
      local_30 = font_line_spacing((GameFont *)&advisor_font);
      text_set_surface(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)));
      text_set_font(ADDR(0x63eac0, ((u8 *)&g.d_0063eac0)));
      text_set_colors(0x25,0x12,2,1);
      text_clear();
      iVar1 = label_string(*(i32 *)(label_string_ids + 0x554));
      text_append(iVar1);
      gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,local_5c,advisor_client_width);
      advisor_list_top_i32 = local_5c + local_30;
      local_5c = advisor_list_top_i32 + 10;
      local_30 = 0x18;
      advisor_row_height = 0x18;
      advisor_list_top_i32 += 0x12;
      advisor_list_height_i32 = local_68 - local_5c;
      for (local_34 = 0; local_34 < 5; local_34++) {
        city = aiStack_7c[local_34];
        if (-1 < aiStack_7c[local_34]) {
          local_54 = local_5c;
          text_clear();
          text_append_int(local_34 + 1);
          text_append_period();
          text_append(city * 0x58 + ADDR(0x64f360, ((u8 *)&cities + 32)));
          text_append_space();
          text_append_lparen();
          iVar1 = civ_get_adjective((int)cities[city].owner);
          text_append(iVar1);
          text_append_rparen();
          text_set_font(ADDR(0x63eac0, ((u8 *)&g.d_0063eac0)));
          uVar5 = 1;
          uVar4 = 1;
          uVar3 = 0x12;
          uVar2 = civ_color_secondary((int)cities[city].owner);
          text_set_colors(uVar2,uVar3,uVar4,uVar5);
          gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,local_5c,advisor_client_width);
          local_5c += local_30;
          local_64 = advisor_client_x + 5;
          gfx_draw_city(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),city,0x1000,local_64,local_5c - 0xf,0);
          local_44 = local_64 + 0x42;
          local_48 = advisor_client_width + advisor_client_x - 5;
          local_4c = local_48 - local_44;
          local_50 = (local_4c >> 1) + local_44;
          advisor_draw_city_citizens(city,local_44,local_5c,(local_50 - 2) - local_44,
                             (int)(char)cities[city].happy,(int)(char)cities[city].unhappy,0
                            );
          local_40 = local_50;
          for (local_38 = 0; local_38 < 0x1c; local_38++) {
            if ((game.wonder_city[local_38] == city) && (0x23 < local_48 - local_40)) {
              sprite_draw
                        ((Sprite *)(&wonder_icon_sprites + local_38 * 0x3c),(iptr)local_8c,ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),
                         local_40,local_5c + 6);
              local_40 += 0x26;
            }
          }
          local_60 = local_5c + 0x20;
          local_5c = local_60;
          rect_set((iptr)local_14,advisor_client_x + 3,local_54,
                             advisor_client_width + advisor_client_x - 3,local_60);
          uVar2 = civ_color_primary((int)cities[city].owner);
          gfx_draw_rect_frame(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),(iptr)local_14,uVar2);
          local_5c += 6;
        }
      }
      wnd_blit_surface((DibSurface *)&advisor_window);
      return;
    }
    if (cities[city].id != 0) break;
LAB_00432c6b:
    city++;
  }
  local_18 = ((int)cities[city].size + (int)(char)cities[city].happy) -
             (int)(char)cities[city].unhappy;
  for (local_38 = 0; local_38 < 0x1c; local_38++) {
    if (game.wonder_city[local_38] == city) {
      local_18 += 10;
    }
  }
  local_34 = 0;
LAB_00432d26:
  if (local_34 < 5) {
    if (local_18 <= (&iStack_2c)[local_34]) goto LAB_00432d23;
    for (local_3c = 3; local_34 <= local_3c; local_3c--) {
      (&iStack_2c)[local_3c + 1] = (&iStack_2c)[local_3c];
      aiStack_7c[local_3c + 1] = aiStack_7c[local_3c];
    }
    (&iStack_2c)[local_34] = local_18;
    aiStack_7c[local_34] = city;
  }
  goto LAB_00432c6b;
LAB_00432d23:
  local_34++;
  goto LAB_00432d26;
}
#undef advisor_client_width
#undef advisor_client_x
#undef advisor_row_height
#undef advisor_list_top_i32
#undef advisor_list_height_i32
#undef local_8c
#undef aiStack_7c
#undef local_68
#undef local_64
#undef local_60
#undef local_5c
#undef city
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
#undef iStack_2c
#undef aiStack_28
#undef local_18
#undef local_14

/* 00433122 auto */
#define advisor_modal_start_ticks_i32 (*(i32 *)((u8 *)&g.d_00625ec0))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl top_cities_show(iptr param_1)

{
  picwnd_open((PictureWindow *)&advisor_window,8,8,1,600,400,0,0);
  advisor_report_civ = param_1;
  advisor_add_close_button((ViewWindow *)&advisor_window);
  wnd_set_redraw_callback((SurfaceWindow *)&advisor_window,ADDR(0x401bef, top_cities_draw));
  wnd_repaint((SurfaceWindow *)&advisor_window);
  window_show((WindowObjectView *)&advisor_window);
  if (2 < game.multiplayer) {
    wnd_set_modal_idle_callback((ModalMenuWindow *)&advisor_wnd,ADDR(0x402789, advisor_mp_idle));
  }
  advisor_modal_start_ticks_i32 = timer_ticks();
  wnd_run_modal_loop((ModalMenuWindow *)&advisor_wnd);
  wnd_set_modal_idle_callback((ModalMenuWindow *)&advisor_wnd,0);
  picwnd_close((PictureWindowCore *)&advisor_window);
  return;
}
#undef advisor_modal_start_ticks_i32

/* 004331d1 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define local_14 (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
#define civ2 (*(iptr *)(frame_ + FRAME_OFF(16)))
void __cdecl
demographics_draw_rank(iptr param_1,iptr civ,uint param_3,iptr param_4,int param_5,int param_6)

{
  int iVar1;
  iptr iVar2;
  i32 uVar3;
  i32 uVar4;
  i32 uVar5;
  i32 uVar6;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_10 = 1;
  local_14 = 0xffffd8f1;
  civ2 = civ;
  if ((int)param_3 < 0) {
    *(int *)(param_1 + civ * 4) = -*(int *)(param_1 + civ * 4);
  }
  for (local_c = 1; local_c < 8; local_c++) {
    if ((1 << ((byte)local_c & 0x1f) & (uint)game.civs_alive) != 0) {
      if (((int)param_3 < 0) && (civ != local_c)) {
        *(int *)(param_1 + local_c * 4) = -*(int *)(param_1 + local_c * 4);
      }
      if (*(int *)(param_1 + civ * 4) < *(int *)(param_1 + local_c * 4)) {
        local_10++;
      }
      if ((int)local_14 < *(int *)(param_1 + local_c * 4)) {
        local_14 = *(uint *)(param_1 + local_c * 4);
        civ2 = local_c;
      }
    }
  }
  if ((int)param_3 < 1) {
    param_3 = ~param_3 + 1;
  }
  if ((int)local_14 < 1) {
    local_14 = ~local_14 + 1;
  }
  text_clear();
  text_append_label(local_10 + 0x189);
  gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),param_5,param_3);
  if ((civ != civ2) &&
     (((((*(byte *)&civs[human_civ].treaties[civ2] & 0x80) != 0 ||
        (iVar1 = civ_has_wonder(human_civ,0x18), iVar1 != 0)) ||
       (iVar1 = civ_has_wonder(human_civ,9), iVar1 != 0)) ||
      (((game.reveal_map != '\0' || (iVar1 = civ_has_wonder(civ,9), iVar1 != 0)) ||
       (iVar1 = civ_has_wonder(civ,0x18), iVar1 != 0)))))) {
    text_clear();
    text_append_lparen();
    iVar2 = civ_name_plural(civ2);
    text_append(iVar2);
    text_append(ADDR(0x626044, ((u8 *)&g.d_00626044)));
    text_append_long(local_14);
    text_append(param_4);
    text_append_rparen();
    uVar6 = 1;
    uVar5 = 1;
    uVar4 = 0x12;
    uVar3 = civ_color_secondary(civ2);
    text_set_colors(uVar3,uVar4,uVar5,uVar6);
    gfx_draw_text_right(ADDR(0x679640, ((u8 *)&g.d_00679640)),param_5,param_3,param_6 - param_5);
  }
  return;
}
#undef human_civ
#undef local_14
#undef local_10
#undef local_c
#undef civ2

/* 00433434 auto */
#define advisor_client_width (*(int *)((u8 *)&g.d_0063ec3c))
#define advisor_client_x (*(int *)((u8 *)&g.d_0063ec34))
#define advisor_row_height (*(i32 *)((u8 *)&g.d_0063ef80))
#define city_happy_count (*(int *)((u8 *)&g.d_006a6550))
#define city_tax_total (*(int *)((u8 *)&g.d_006a6554))
#define city_total_shields (*(int *)((u8 *)&g.d_006a65cc))
#define city_total_trade (*(int *)((u8 *)&g.d_006a65d0))
#define city_unhappy_count (*(int *)((u8 *)&g.d_006a65a8))
#define city_yield_totals (*(int *)((u8 *)&g.d_006a65c8))
#define advisor_list_top_i32 (*(i32 *)((u8 *)&g.d_0063ef78))
#define advisor_list_height_i32 (*(i32 *)((u8 *)&g.d_0063ef7c))
#define aiStack_1f0 (*(int (*)[8])(frame_ + FRAME_OFF(0)))
#define aiStack_1d0 (*(int (*)[8])(frame_ + FRAME_OFF(32)))
#define local_1b0 (*(int *)(frame_ + FRAME_OFF(64)))
#define local_1ac (*(int *)(frame_ + FRAME_OFF(68)))
#define local_1a8 (*(int *)(frame_ + FRAME_OFF(72)))
#define city (*(iptr *)(frame_ + FRAME_OFF(76)))
#define local_1a0 (*(int *)(frame_ + FRAME_OFF(80)))
#define aiStack_19c (*(int (*)[8])(frame_ + FRAME_OFF(84)))
#define local_17c (*(int *)(frame_ + FRAME_OFF(116)))
#define local_178 (*(int *)(frame_ + FRAME_OFF(120)))
#define aiStack_174 (*(int (*)[8])(frame_ + FRAME_OFF(124)))
#define aiStack_154 (*(int (*)[8])(frame_ + FRAME_OFF(156)))
#define local_134 (*(int *)(frame_ + FRAME_OFF(188)))
#define local_130 (*(u8 * *)(frame_ + FRAME_OFF(192)))
#define aiStack_12c (*(int (*)[8])(frame_ + FRAME_OFF(196)))
#define aiStack_10c (*(int (*)[8])(frame_ + FRAME_OFF(228)))
#define local_ec (*(i32 *)(frame_ + FRAME_OFF(260)))
#define civ2 (*(uptr *)(frame_ + FRAME_OFF(264)))
#define local_e4 (*(int (*)[8])(frame_ + FRAME_OFF(268)))
#define local_c4 (*(int *)(frame_ + FRAME_OFF(300)))
#define local_c0 (*(i8 (*)[80])(frame_ + FRAME_OFF(304)))
#define local_70 (*(int *)(frame_ + FRAME_OFF(384)))
#define aiStack_6c (*(int (*)[8])(frame_ + FRAME_OFF(388)))
#define aiStack_4c (*(int (*)[8])(frame_ + FRAME_OFF(420)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(452)))
#define aiStack_28 (*(int (*)[8])(frame_ + FRAME_OFF(456)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(488)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl demographics_draw(void)

{
  int iVar2;
  iptr iVar3;
  int iVar4;
  int iVar5;
  iptr civ;
  i8 frame_[FRAME_OFF(496)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ = advisor_report_civ;
  for (civ2 = 0; (int)civ2 < 8; civ2++) {
    aiStack_4c[civ2] = 0;
    aiStack_1f0[civ2] = aiStack_4c[civ2];
    aiStack_19c[civ2] = aiStack_1f0[civ2];
    aiStack_174[civ2] = 0;
    aiStack_1d0[civ2] = aiStack_174[civ2];
    aiStack_12c[civ2] = aiStack_1d0[civ2];
    aiStack_28[civ2] = aiStack_12c[civ2];
    aiStack_10c[civ2] = 0;
    aiStack_154[civ2] = aiStack_10c[civ2];
    aiStack_6c[civ2] = 1;
  }
  local_130 = &map_tiles->owner;
  for (local_c4 = 0; local_c4 < map.area; local_c4++) {
    civ2 = (int)(uint)*local_130 >> 4;
    if (civ2 < 8) {
      aiStack_1d0[civ2]++;
    }
    local_130 += 6;
  }
  for (city = 0; city < game.num_cities; city++) {
    if (cities[city].id != 0) {
      civ2 = (uptr)cities[city].owner;
      city_recalc(city,1);
      aiStack_6c[civ2] += (int)cities[city].size;
      aiStack_19c[civ2] =
           aiStack_19c[civ2] + ((cities[city].size + city_happy_count) - city_unhappy_count);
      aiStack_12c[civ2] = aiStack_12c[civ2] + city_lux_total * 2 + city_tax_total;
      aiStack_174[civ2] = aiStack_174[civ2] + city_yield_totals + cities[city].size * -2;
      aiStack_10c[civ2] = aiStack_10c[civ2] + city_total_shields + city_total_trade + city_yield_totals;
      aiStack_154[civ2] += city_total_shields;
      if (city_pollution_divisor < 2) {
        city_pollution_divisor = 1;
      }
      iVar2 = cities[city].size * city_pop_pollution_factor;
      local_134 = city_total_shields / city_pollution_divisor - 0x14 + ((int)(iVar2 + (iVar2 >> 0x1f & 3U)) >> 2);
      if (0 < local_134) {
        aiStack_1f0[civ2] += local_134;
      }
      iVar2 = city_has_improvement(city,3);
      if ((iVar2 != 0) || (iVar2 = civ_has_wonder(civ2,0), iVar2 != 0)) {
        aiStack_4c[civ2] += (int)cities[city].size;
      }
      iVar2 = city_has_improvement(city,9);
      if (iVar2 != 0) {
        aiStack_4c[civ2] += (int)cities[city].size;
      }
      iVar2 = city_has_improvement(city,0x17);
      if (iVar2 != 0) {
        aiStack_4c[civ2] += (int)cities[city].size;
      }
      iVar2 = city_has_improvement(city,6);
      if (iVar2 != 0) {
        aiStack_28[civ2] += (int)cities[city].size;
      }
      iVar2 = city_has_improvement(city,0xc);
      if (iVar2 != 0) {
        aiStack_28[civ2] += (int)cities[city].size;
      }
    }
  }
  frame_wnd_layout((FrameWindow *)&advisor_window);
  frame_wnd_draw_caption((FrameWindow *)&advisor_window);
  picwnd_blit((PictureWindow *)&advisor_window);
  local_1a8 = advisor_client_y + 2;
  local_1b0 = advisor_client_y + 0x174;
  local_70 = font_line_spacing((GameFont *)&advisor_font);
  text_set_surface(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)));
  text_set_font(ADDR(0x63eac0, ((u8 *)&g.d_0063eac0)));
  text_set_colors(0x25,0x12,2,1);
  text_clear();
  if (game_language == 0) {
    iVar3 = civ_get_adjective(civ);
    text_append(iVar3);
    text_append_space();
  }
  iVar3 = label_string(*(i32 *)(label_string_ids + 0x558));
  text_append(iVar3);
  gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,local_1a8,advisor_client_width);
  iVar2 = local_1a8 + local_70 + 10;
  local_70 = 0x19;
  advisor_row_height = 0x19;
  advisor_list_height_i32 = local_1b0 - iVar2;
  local_ec = 0x25;
  local_178 = advisor_client_x + 2;
  local_17c = advisor_client_x + 0xb4;
  local_1a0 = advisor_client_x + 0x142;
  local_1ac = advisor_client_width + local_178 - 4;
  local_2c = advisor_client_x + 2;
  local_8 = advisor_client_width + advisor_client_x - 2;
  advisor_list_top_i32 = iVar2;
  local_1a8 = iVar2;
  text_set_colors(0x25,0x12,0xffffffff,0xffffffff);
  iVar4 = local_178;
  iVar5 = iVar2;
  iVar3 = label_string(*(i32 *)(label_string_ids + 0x5d4));
  gfx_draw_text(iVar3,iVar4,iVar5);
  for (civ2 = 1; (int)civ2 < 8; civ2++) {
    iVar4 = aiStack_6c[civ2];
    if (iVar4 < 2) {
      iVar4 = 1;
    }
    local_e4[civ2] = (aiStack_19c[civ2] * 0x32) / iVar4;
    if (civ2 == civ) {
      text_clear();
      text_append_long(local_e4[civ2]);
      text_append_percent();
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_17c,iVar2);
    }
  }
  demographics_draw_rank((iptr)local_e4,civ,iVar2,ADDR(0x626048, ((u8 *)&g.d_00626048)),local_1a0,local_1ac);
  gfx_draw_hline(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),local_2c,local_8,iVar2 + local_70 - 2,99);
  iVar2 += local_70;
  text_set_colors(local_ec,0x12,0xffffffff,0xffffffff);
  iVar4 = local_178;
  iVar5 = iVar2;
  iVar3 = label_string(*(i32 *)(label_string_ids + 0x5d8));
  gfx_draw_text(iVar3,iVar4,iVar5);
  for (civ2 = 1; (int)civ2 < 8; civ2++) {
    iVar4 = civ_total_population(civ2);
    local_e4[civ2] = iVar4;
    if (civ2 == civ) {
      text_clear();
      text_append_population(civ2,0xffffffff);
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_17c,iVar2);
    }
  }
  demographics_draw_rank((iptr)local_e4,civ,iVar2,ADDR(0x62604c, ((u8 *)&g.d_0062604c)),local_1a0,local_1ac);
  gfx_draw_hline(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),local_2c,local_8,iVar2 + local_70 - 2,99);
  iVar2 += local_70;
  text_set_colors(local_ec,0x12,0xffffffff,0xffffffff);
  iVar4 = local_178;
  iVar5 = iVar2;
  iVar3 = label_string(*(i32 *)(label_string_ids + 0x5dc));
  gfx_draw_text(iVar3,iVar4,iVar5);
  for (civ2 = 1; (int)civ2 < 8; civ2++) {
    local_e4[civ2] = aiStack_12c[civ2];
    if (civ2 == civ) {
      text_clear();
      text_append_long(local_e4[civ2]);
      text_append_space();
      text_append_label(0x188);
      text_append_space();
      text_append(ADDR(0x626054, ((u8 *)&g.d_00626054)));
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_17c,iVar2);
    }
  }
  demographics_draw_rank((iptr)local_e4,civ,iVar2,ADDR(0x626058, ((u8 *)&g.d_00626058)),local_1a0,local_1ac);
  gfx_draw_hline(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),local_2c,local_8,iVar2 + local_70 - 2,99);
  iVar2 += local_70;
  text_set_colors(local_ec,0x12,0xffffffff,0xffffffff);
  iVar4 = local_178;
  iVar5 = iVar2;
  iVar3 = label_string(*(i32 *)(label_string_ids + 0x5e0));
  gfx_draw_text(iVar3,iVar4,iVar5);
  for (civ2 = 1; (int)civ2 < 8; civ2++) {
    local_e4[civ2] = aiStack_154[civ2];
    if (civ2 == civ) {
      text_clear();
      text_append_long(local_e4[civ2]);
      text_append_space();
      text_append_label(0x182);
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_17c,iVar2);
    }
  }
  str_clear((iptr)local_c0);
  str_append_label((iptr)local_c0,0x182);
  demographics_draw_rank((iptr)local_e4,civ,iVar2,(iptr)local_c0,local_1a0,local_1ac);
  gfx_draw_hline(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),local_2c,local_8,iVar2 + local_70 - 2,99);
  iVar2 += local_70;
  text_set_colors(local_ec,0x12,0xffffffff,0xffffffff);
  iVar4 = local_178;
  iVar5 = iVar2;
  iVar3 = label_string(*(i32 *)(label_string_ids + 0x5e4));
  gfx_draw_text(iVar3,iVar4,iVar5);
  for (civ2 = 1; (int)civ2 < 8; civ2++) {
    local_e4[civ2] = aiStack_1d0[civ2];
    if (civ2 == civ) {
      text_clear();
      text_append_long(local_e4[civ2]);
      text_append(ADDR(0x62605c, ((u8 *)&g.d_0062605c)));
      text_append_label(0x183);
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_17c,iVar2);
    }
  }
  demographics_draw_rank((iptr)local_e4,civ,iVar2,ADDR(0x626064, ((u8 *)&g.d_00626064)),local_1a0,local_1ac);
  gfx_draw_hline(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),local_2c,local_8,iVar2 + local_70 - 2,99);
  iVar2 += local_70;
  text_set_colors(local_ec,0x12,0xffffffff,0xffffffff);
  iVar4 = local_178;
  iVar5 = iVar2;
  iVar3 = label_string(*(i32 *)(label_string_ids + 0x5e8));
  gfx_draw_text(iVar3,iVar4,iVar5);
  for (civ2 = 1; (int)civ2 < 8; civ2++) {
    local_e4[civ2] =
         ((aiStack_6c[civ2] * 2 + aiStack_28[civ2]) * 2) / aiStack_6c[civ2];
    iVar4 = civ_has_advance(civ2,1);
    if (iVar4 != 0) {
      local_e4[civ2] = local_e4[civ2] << 1;
    }
    iVar4 = civ_has_advance(civ2,0x58);
    if (iVar4 != 0) {
      local_e4[civ2] = local_e4[civ2] << 1;
    }
    iVar4 = civ_has_advance(civ2,0x2b);
    if (iVar4 != 0) {
      local_e4[civ2] = local_e4[civ2] << 1;
    }
    iVar4 = civ_has_advance(civ2,0x55);
    if (iVar4 != 0) {
      local_e4[civ2] = local_e4[civ2] << 1;
    }
    iVar4 = int_clamp(local_e4[civ2],0,100);
    local_e4[civ2] = iVar4;
    if (civ2 == civ) {
      text_clear();
      text_append_long(local_e4[civ2]);
      text_append_percent();
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_17c,iVar2);
    }
  }
  demographics_draw_rank((iptr)local_e4,civ,iVar2,ADDR(0x62606c, ((u8 *)&g.d_0062606c)),local_1a0,local_1ac);
  gfx_draw_hline(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),local_2c,local_8,iVar2 + local_70 - 2,99);
  iVar2 += local_70;
  text_set_colors(local_ec,0x12,0xffffffff,0xffffffff);
  iVar4 = local_178;
  iVar5 = iVar2;
  iVar3 = label_string(*(i32 *)(label_string_ids + 0x5ec));
  gfx_draw_text(iVar3,iVar4,iVar5);
  for (civ2 = 1; (int)civ2 < 8; civ2++) {
    local_e4[civ2] =
         (aiStack_6c[civ2] * 0x32) / (aiStack_4c[civ2] + aiStack_6c[civ2]);
    iVar4 = civ_has_advance(civ2,0x32);
    if (iVar4 != 0) {
      local_e4[civ2] = local_e4[civ2] / 2;
    }
    iVar4 = civ_has_wonder(civ2,0x1b);
    if (iVar4 != 0) {
      local_e4[civ2] = local_e4[civ2] / 2;
    }
    aiStack_4c[civ2] = (int)(0x708 / (longlong)(local_e4[civ2] + 0x14));
    if (civ2 == civ) {
      text_clear();
      text_append_long(local_e4[civ2]);
      text_append_percent();
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_17c,iVar2);
    }
  }
  demographics_draw_rank((iptr)local_e4,civ,-iVar2,ADDR(0x626070, ((u8 *)&g.d_00626070)),local_1a0,local_1ac);
  gfx_draw_hline(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),local_2c,local_8,iVar2 + local_70 - 2,99);
  iVar2 += local_70;
  text_set_colors(local_ec,0x12,0xffffffff,0xffffffff);
  iVar4 = local_178;
  iVar5 = iVar2;
  iVar3 = label_string(*(i32 *)(label_string_ids + 0x5f0));
  gfx_draw_text(iVar3,iVar4,iVar5);
  for (civ2 = 1; (int)civ2 < 8; civ2++) {
    local_e4[civ2] = aiStack_1f0[civ2];
    aiStack_4c[civ2] =
         aiStack_4c[civ2] - (aiStack_1f0[civ2] * 10) / aiStack_6c[civ2];
    if (civ2 == civ) {
      text_clear();
      text_append_long(local_e4[civ2]);
      text_append(ADDR(0x626074, ((u8 *)&g.d_00626074)));
      text_append_label(0x184);
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_17c,iVar2);
    }
  }
  str_clear((iptr)local_c0);
  str_append((iptr)local_c0,ADDR(0x626078, ((u8 *)&g.d_00626078)));
  str_append_label((iptr)local_c0,0x184);
  demographics_draw_rank((iptr)local_e4,civ,-iVar2,(iptr)local_c0,local_1a0,local_1ac);
  gfx_draw_hline(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),local_2c,local_8,iVar2 + local_70 - 2,99);
  iVar2 += local_70;
  text_set_colors(local_ec,0x12,0xffffffff,0xffffffff);
  iVar4 = local_178;
  iVar5 = iVar2;
  iVar3 = label_string(*(i32 *)(label_string_ids + 0x5f4));
  gfx_draw_text(iVar3,iVar4,iVar5);
  for (civ2 = 1; (int)civ2 < 8; civ2++) {
    iVar4 = int_clamp(aiStack_4c[civ2],0x14,99);
    local_e4[civ2] = iVar4;
    if (civ2 == civ) {
      text_clear();
      text_append_long(local_e4[civ2]);
      text_append_space();
      text_append_label(0x185);
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_17c,iVar2);
    }
  }
  str_clear((iptr)local_c0);
  str_append_label((iptr)local_c0,0x186);
  demographics_draw_rank((iptr)local_e4,civ,iVar2,(iptr)local_c0,local_1a0,local_1ac);
  gfx_draw_hline(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),local_2c,local_8,iVar2 + local_70 - 2,99);
  iVar2 += local_70;
  text_set_colors(local_ec,0x12,0xffffffff,0xffffffff);
  iVar4 = local_178;
  iVar5 = iVar2;
  iVar3 = label_string(*(i32 *)(label_string_ids + 0x5f8));
  gfx_draw_text(iVar3,iVar4,iVar5);
  for (civ2 = 1; (int)civ2 < 8; civ2++) {
    local_e4[civ2] = (aiStack_174[civ2] * 0x28) / aiStack_6c[civ2] + 0x14;
    if (civ2 == civ) {
      text_clear();
      text_append_long(local_e4[civ2] / 10);
      text_append(ADDR(0x62607c, ((u8 *)&g.d_0062607c)));
      text_append_long(local_e4[civ2] % 10);
      text_append_space();
      text_append_label(0x187);
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_17c,iVar2);
    }
    local_e4[civ2] = local_e4[civ2] / 10;
  }
  demographics_draw_rank((iptr)local_e4,civ,iVar2,ADDR(0x626080, ((u8 *)&g.d_00626080)),local_1a0,local_1ac);
  gfx_draw_hline(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),local_2c,local_8,iVar2 + local_70 - 2,99);
  iVar2 += local_70;
  text_set_colors(local_ec,0x12,0xffffffff,0xffffffff);
  iVar4 = local_178;
  iVar5 = iVar2;
  iVar3 = label_string(*(i32 *)(label_string_ids + 0x5fc));
  gfx_draw_text(iVar3,iVar4,iVar5);
  for (civ2 = 1; (int)civ2 < 8; civ2++) {
    local_e4[civ2] = (civs[civ2].num_military_units * 10) / aiStack_6c[civ2];
    if (civ2 == civ) {
      text_clear();
      text_append_long(local_e4[civ2]);
      text_append_space();
      text_append_label(0x185);
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_17c,iVar2);
    }
  }
  demographics_draw_rank((iptr)local_e4,civ,iVar2,(iptr)local_c0,local_1a0,local_1ac);
  gfx_draw_hline(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),local_2c,local_8,iVar2 + local_70 - 2,99);
  iVar2 += local_70;
  text_set_colors(local_ec,0x12,0xffffffff,0xffffffff);
  iVar4 = local_178;
  iVar5 = iVar2;
  iVar3 = label_string(*(i32 *)(label_string_ids + 0x600));
  gfx_draw_text(iVar3,iVar4,iVar5);
  for (civ2 = 1; (int)civ2 < 8; civ2++) {
    if (aiStack_12c[civ2] <
        (int)(30000 / (ulonglong)(longlong)(int)(civs[civ2].num_advances + 1))) {
      local_e4[civ2] =
           (int)((uint)civs[civ2].num_advances * aiStack_12c[civ2]) / aiStack_6c[civ2];
    }
    else {
      local_e4[civ2] =
           (aiStack_12c[civ2] / aiStack_6c[civ2]) * (uint)civs[civ2].num_advances;
    }
    if (civ2 == civ) {
      text_clear();
      text_append_long(local_e4[civ2]);
      text_append(ADDR(0x626084, ((u8 *)&g.d_00626084)));
      text_append_label(0x189);
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_17c,iVar2);
    }
  }
  demographics_draw_rank((iptr)local_e4,civ,iVar2,ADDR(0x626088, ((u8 *)&g.d_00626088)),local_1a0,local_1ac);
  gfx_draw_hline(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),local_2c,local_8,iVar2 + local_70 - 2,99);
  iVar2 += local_70;
  text_set_colors(local_ec,0x12,0xffffffff,0xffffffff);
  iVar4 = local_178;
  iVar5 = iVar2;
  iVar3 = label_string(*(i32 *)(label_string_ids + 0x604));
  gfx_draw_text(iVar3,iVar4,iVar5);
  for (civ2 = 1; (int)civ2 < 8; civ2++) {
    local_e4[civ2] = (aiStack_10c[civ2] * 10) / aiStack_6c[civ2];
    if (civ2 == civ) {
      text_clear();
      text_append_long(local_e4[civ2]);
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_17c,iVar2);
    }
  }
  demographics_draw_rank((iptr)local_e4,civ,iVar2,ADDR(0x62608c, ((u8 *)&g.d_0062608c)),local_1a0,local_1ac);
  wnd_blit_surface((DibSurface *)&advisor_window);
  return;
}
#undef advisor_client_width
#undef advisor_client_x
#undef advisor_row_height
#undef city_happy_count
#undef city_tax_total
#undef city_total_shields
#undef city_total_trade
#undef city_unhappy_count
#undef city_yield_totals
#undef advisor_list_top_i32
#undef advisor_list_height_i32
#undef aiStack_1f0
#undef aiStack_1d0
#undef local_1b0
#undef local_1ac
#undef local_1a8
#undef city
#undef local_1a0
#undef aiStack_19c
#undef local_17c
#undef local_178
#undef aiStack_174
#undef aiStack_154
#undef local_134
#undef local_130
#undef aiStack_12c
#undef aiStack_10c
#undef local_ec
#undef civ2
#undef local_e4
#undef local_c4
#undef local_c0
#undef local_70
#undef aiStack_6c
#undef aiStack_4c
#undef local_2c
#undef aiStack_28
#undef local_8

/* 00434d8a auto */
#define advisor_modal_start_ticks_i32 (*(i32 *)((u8 *)&g.d_00625ec0))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl demographics_show(iptr param_1)

{
  picwnd_open((PictureWindow *)&advisor_window,9,9,1,600,400,0,0);
  advisor_report_civ = param_1;
  advisor_add_close_button((ViewWindow *)&advisor_window);
  wnd_set_redraw_callback((SurfaceWindow *)&advisor_window,ADDR(0x401cda, demographics_draw));
  wnd_repaint((SurfaceWindow *)&advisor_window);
  window_show((WindowObjectView *)&advisor_window);
  if (2 < game.multiplayer) {
    wnd_set_modal_idle_callback((ModalMenuWindow *)&advisor_wnd,ADDR(0x402789, advisor_mp_idle));
  }
  advisor_modal_start_ticks_i32 = timer_ticks();
  wnd_run_modal_loop((ModalMenuWindow *)&advisor_wnd);
  wnd_set_modal_idle_callback((ModalMenuWindow *)&advisor_wnd,0);
  picwnd_close((PictureWindowCore *)&advisor_window);
  return;
}
#undef advisor_modal_start_ticks_i32

/* 00436287 auto */
void __cdecl advisor_refresh_if_open(iptr param_1)

{
  if (param_1 == 0xc) {
    if (casualty_window_report_id == 0xc) {
      wnd_repaint((SurfaceWindow *)&casualty_window);
    }
  }
  else if (advisor_report_id == param_1) {
    wnd_repaint((SurfaceWindow *)&advisor_window);
  }
  return;
}

/* 004362e2 auto */
#define advisor_client_width (*(i32 *)((u8 *)&g.d_0063ec3c))
#define advisor_client_x (*(i32 *)((u8 *)&g.d_0063ec34))
#define advisor_report_param (*(int *)((u8 *)&g.d_0063efac))
#define advisor_row_height (*(int *)((u8 *)&g.d_0063ef80))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define advisor_list_top_i32 (*(i32 *)((u8 *)&g.d_0063ef78))
#define advisor_list_height_i32 (*(i32 *)((u8 *)&g.d_0063ef7c))
#define local_118 (*(uint *)(frame_ + FRAME_OFF(0)))
#define local_114 (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_110 (*(uint *)(frame_ + FRAME_OFF(8)))
#define local_10c (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_108 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_104 (*(int *)(frame_ + FRAME_OFF(20)))
#define local_fc (*(int *)(frame_ + FRAME_OFF(28)))
#define local_ec (*(int *)(frame_ + FRAME_OFF(44)))
#define local_e4 (*(int *)(frame_ + FRAME_OFF(52)))
#define local_e0 (*(i8 (*)[80])(frame_ + FRAME_OFF(56)))
#define local_90 (*(int *)(frame_ + FRAME_OFF(136)))
#define local_8c (*(int *)(frame_ + FRAME_OFF(140)))
#define local_88 (*(i8 (*)[132])(frame_ + FRAME_OFF(144)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl hall_of_fame_draw(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  iptr iVar4;
  int iVar5;
  i8 frame_[FRAME_OFF(280)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = advisor_report_param;
  frame_wnd_layout((FrameWindow *)&advisor_window);
  frame_wnd_draw_caption((FrameWindow *)&advisor_window);
  picwnd_blit((PictureWindow *)&advisor_window);
  iVar2 = advisor_client_y + 1;
  iVar3 = advisor_client_y + 0x174;
  local_90 = font_line_spacing((GameFont *)&advisor_font);
  local_90 -= 2;
  text_set_surface(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)));
  text_set_font(ADDR(0x63eac0, ((u8 *)&g.d_0063eac0)));
  text_set_colors(0x25,0x12,2,1);
  text_clear();
  iVar4 = label_string(*(i32 *)(label_string_ids + 0x6e8));
  text_append(iVar4);
  gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,iVar2,advisor_client_width);
  iVar2 += local_90;
  text_set_font(ADDR(0x63f030, ((u8 *)&g.d_0063f030)));
  iVar5 = font_line_spacing((GameFont *)&hall_of_fame_font);
  advisor_row_height = iVar5 - 3;
  advisor_list_top_i32 = iVar2 + 6;
  advisor_list_height_i32 = iVar3 - advisor_list_top_i32;
  local_fc = advisor_list_top_i32;
  local_90 = advisor_row_height;
  for (local_ec = 0; local_ec < 6; local_ec++) {
    if (((local_ec != 5) || (iVar1 == 5)) && (-1 < *(short *)(&hall_of_fame_entries + local_ec * 0x48))) {
      if (*(short *)(&hof_entry_leader_female + local_ec * 0x48) == 0) {
        crt_strcpy(local_e0,s_MALEFAME_006260f0);
      }
      else {
        crt_strcpy(local_e0,s_FEMALEFAME_006260e4);
      }
      local_8c = text_open_section(ADDR(0x6558e8, ((u8 *)&g.d_006558e8)),(iptr)local_e0);
      text_set_string_arg(0,local_ec * 0x48 + ADDR(0x63f0e0, ((u8 *)&g.d_0063f0de + 2)));
      for (local_e4 = 0; local_e4 <= *(short *)(&hof_entry_title_index + local_ec * 0x48);
          local_e4 = local_e4 + 1) {
        if (local_8c == 0) {
          text_read_line(1);
          crt_strcpy(local_e0,&text_buffer);
        }
        else if (*(short *)(&hof_entry_title_index + local_ec * 0x48) == local_e4) {
          crt_strcpy(local_e0,s__STRING0_006260fc);
        }
        else {
          crt_strcpy(local_e0,s_Error_00626108);
        }
        text_expand_vars((iptr)local_e0,(iptr)local_88);
      }
      text_clear();
      text_append_int(local_ec + 1);
      text_append(ADDR(0x626110, ((u8 *)&g.d_00626110)));
      text_append((iptr)local_88);
      text_append_space();
      text_append_label(0x8c);
      text_append_space();
      text_append(local_ec * 0x48 + ADDR(0x63f0f8, ((u8 *)&g.d_0063f0de + 26)));
      text_append_space();
      text_append_lparen();
      text_append_label(0x1bb);
      text_append_space();
      if ((*(short *)(&hof_entry_is_scenario + local_ec * 0x48) == 0) ||
         (-1 < *(short *)(&hof_entry_year_increment + local_ec * 0x48))) {
        local_118 = (uint)*(short *)(&hof_entry_year + local_ec * 0x48);
        if ((int)local_118 < 0) {
          if ((int)local_118 < 1) {
            local_118 = ~local_118 + 1;
          }
          text_append_int(local_118);
          text_append_space();
          text_append_label(0);
        }
        else if (game_language == 0) {
          text_append_label(1);
          text_append_space();
          local_110 = local_118;
          if ((int)local_118 < 1) {
            local_110 = ~local_118 + 1;
          }
          text_append_int(local_110);
        }
        else {
          local_114 = local_118;
          if ((int)local_118 < 1) {
            local_114 = ~local_118 + 1;
          }
          text_append_int(local_114);
          text_append_space();
          text_append_label(1);
        }
      }
      else {
        if (*(short *)(&hof_entry_year_increment + local_ec * 0x48) < 1) {
          local_104 = ~(int)*(short *)(&hof_entry_year_increment + local_ec * 0x48) + 1;
        }
        else {
          local_104 = (int)*(short *)(&hof_entry_year_increment + local_ec * 0x48);
        }
        local_10c = *(short *)(&hof_entry_turn + local_ec * 0x48) * local_104 +
                    (int)*(short *)(&hof_entry_start_year + local_ec * 0x48) - 1;
        if (local_10c % 0xc < 1) {
          local_108 = ~(local_10c % 0xc) + 1;
        }
        else {
          local_108 = local_10c % 0xc;
        }
        text_append_label(local_108 + 0x1a4);
        text_append_space();
        if (local_10c / 0xc < 1) {
          local_10c = ~(local_10c / 0xc) + 1;
        }
        else {
          local_10c = local_10c / 0xc;
        }
        text_append_int(local_10c);
      }
      text_append_rparen();
      if (iVar1 == local_ec) {
        text_set_colors(0x7a,0x12,0xffffffff,0xffffffff);
      }
      else {
        text_set_colors(0xaf,0x12,0xffffffff,0xffffffff);
      }
      gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,local_fc,advisor_client_width);
      local_fc += local_90;
      text_clear();
      if ((*(short *)(&hof_entry_is_scenario + local_ec * 0x48) == 0) ||
         (*(short *)(&hof_entry_objective_score + local_ec * 0x48) < 0)) {
        text_append_label(0x22);
        text_append_colon();
        str_append_population(ADDR(0x679640, ((u8 *)&g.d_00679640)),0,(int)*(short *)(&hof_entry_population + local_ec * 0x48));
      }
      else {
        text_append_label(0x1b2);
        text_append_colon();
        text_append_int((int)*(short *)(&hof_entry_objective_score + local_ec * 0x48));
      }
      text_append_space();
      text_append_space();
      text_append_label(0x1bc);
      text_append_colon();
      text_append_int((int)*(short *)(&hall_of_fame_entries + local_ec * 0x48));
      text_append_space();
      text_append_lparen();
      text_append_string_id(difficulty_names[(int)*(short *)(&hof_entry_difficulty + local_ec * 0x48) & 0xf]);
      if (*(short *)(&hof_entry_is_scenario + local_ec * 0x48) != 0) {
        text_append_colon();
        text_append_label(0x1a2);
      }
      if ((*(ushort *)(&hof_entry_difficulty + local_ec * 0x48) & 0x80) != 0) {
        text_append_colon();
        text_append_label(0x19a);
      }
      text_append_rparen();
      gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,local_fc,advisor_client_width);
      local_fc += local_90;
      text_clear();
      text_append(ADDR(0x626114, ((u8 *)&g.d_00626114)));
      text_append_label(0x1bd);
      text_append_colon();
      text_append_int((int)*(short *)(&hall_of_fame_entry_rating + local_ec * 0x48));
      text_append(ADDR(0x626118, ((u8 *)&g.d_00626118)));
      text_set_colors(0x25,0x12,0xffffffff,0xffffffff);
      gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,local_fc,advisor_client_width);
      local_fc = local_fc + local_90 + 6;
    }
  }
  wnd_blit_surface((DibSurface *)&advisor_window);
  return;
}
#undef advisor_client_width
#undef advisor_client_x
#undef advisor_report_param
#undef advisor_row_height
#undef text_buffer
#undef advisor_list_top_i32
#undef advisor_list_height_i32
#undef local_118
#undef local_114
#undef local_110
#undef local_10c
#undef local_108
#undef local_104
#undef local_fc
#undef local_ec
#undef local_e4
#undef local_e0
#undef local_90
#undef local_8c
#undef local_88

/* 00436b92 auto */
void __cdecl hall_of_fame_on_clear_clicked(void)

{
  advisor_report_civ = 1;
  wnd_end_modal_loop((ModalMenuWindow *)&advisor_wnd);
  return;
}

/* 00436bb7 auto */
#define advisor_client_x (*(i32 *)((u8 *)&g.d_0063ec34))
#define advisor_report_param (*(int *)((u8 *)&g.d_0063efac))
#define advisor_modal_start_ticks_i32 (*(i32 *)((u8 *)&g.d_00625ec0))
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
/* WARNING: Removing unreachable block (ram,0x00436c7e) */
/* WARNING: Removing unreachable block (ram,0x00436d09) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

iptr __cdecl hall_of_fame_show(int param_1)

{
  int iVar1;
  int iVar2;
  iptr iVar3;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  hall_of_fame_load();
  picwnd_open((PictureWindow *)&advisor_window,8,8,1,600,400,0,0);
  advisor_report_param = param_1;
  advisor_report_civ = 0;
  if (param_1 < 0) {
    advisor_add_close_button((ViewWindow *)&advisor_window);
  }
  else {
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
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x6f8));
    button_create
              ((Control *)&advisor_toggle_button,ADDR(0x63eb58, ((u8 *)&g.d_0063eb58)),0x65,(iptr)local_14,iVar3);
    button_set_callback((Control *)&advisor_toggle_button,ADDR(0x402c61, hall_of_fame_on_clear_clicked));
  }
  wnd_set_redraw_callback((SurfaceWindow *)&advisor_window,ADDR(0x402f4a, hall_of_fame_draw));
  wnd_repaint((SurfaceWindow *)&advisor_window);
  window_show((WindowObjectView *)&advisor_window);
  if (2 < game.multiplayer) {
    wnd_set_modal_idle_callback((ModalMenuWindow *)&advisor_wnd,ADDR(0x402789, advisor_mp_idle));
  }
  advisor_modal_start_ticks_i32 = timer_ticks();
  wnd_run_modal_loop((ModalMenuWindow *)&advisor_wnd);
  wnd_set_modal_idle_callback((ModalMenuWindow *)&advisor_wnd,0);
  picwnd_close((PictureWindowCore *)&advisor_window);
  return advisor_report_civ;
}
#undef advisor_client_x
#undef advisor_report_param
#undef advisor_modal_start_ticks_i32
#undef local_14

/* 00436dd7 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl hall_of_fame_clear(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; local_8 < 6; local_8++) {
    *(i16 *)(&hall_of_fame_entries + local_8 * 0x48) = 0xffff;
    *(i16 *)(&hall_of_fame_entry_rating + local_8 * 0x48) = 0xffff;
  }
  return;
}
#undef local_8

/* 00436e28 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl hall_of_fame_load(void)

{
  bool bVar1;
  FILE *_File;
  size_t sVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  hall_of_fame_clear();
  _File = _fopen(s_HALLFAME_DAT_00626124,&hall_of_fame_read_mode);
  if (_File != (FILE *)0x0) {
    bVar1 = false;
    for (local_8 = 0; local_8 < 6; local_8++) {
      sVar2 = _fread(&hall_of_fame_entries + local_8 * 0x48,0x48,1,_File);
      if (sVar2 == 0) {
        bVar1 = true;
        break;
      }
    }
    if (bVar1) {
      hall_of_fame_clear();
    }
    _fclose(_File);
  }
  return;
}
#undef local_8

/* 00436ed2 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl hall_of_fame_save(void)

{
  FILE *_File;
  size_t sVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  _File = _fopen(s_HALLFAME_DAT_00626138,&hall_of_fame_write_mode);
  if (_File != (FILE *)0x0) {
    local_8 = 0;
    while ((local_8 < 6 &&
           (sVar1 = _fwrite(&hall_of_fame_entries + local_8 * 0x48,0x48,1,_File), sVar1 != 0))) {
      local_8++;
    }
    _fclose(_File);
  }
  return;
}
#undef local_8

/* 00436f5a auto */
#define civ_rating_percent (*(i32 *)((u8 *)&g.d_0063ea18))
#define civ_rating_title_index (*(i32 *)((u8 *)&g.d_0063e4ec))
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
#define scenario_start_year (*(i16 *)((u8 *)&g.d_0064bcb6))
#define scenario_year_increment (*(i16 *)((u8 *)&g.d_0064bcb4))
#define score_civ_objective_value (*(i32 *)((u8 *)&g.d_00673f80))
#define hall_of_fame_new_entry_i16 (*(i16 *)((u8 *)&g.d_0063eac8))
#define hof_new_turn_i16 (*(i16 *)((u8 *)&g.d_0063eacc))
#define hof_new_year_i16 (*(i16 *)((u8 *)&g.d_0063eace))
#define hof_new_population_i16 (*(i16 *)((u8 *)&g.d_0063ead0))
#define hof_new_objective_score_i16 (*(i16 *)((u8 *)&g.d_0063ead2))
#define hof_new_year_increment_i16 (*(i16 *)((u8 *)&g.d_0063ead4))
#define hof_new_start_year_i16 (*(i16 *)((u8 *)&g.d_0063ead6))
#define hof_new_is_scenario_i16 (*(i16 *)((u8 *)&g.d_0063ead8))
#define hof_new_leader_female_i16 (*(i16 *)((u8 *)&g.d_0063eadc))
#define hof_new_title_index_i16 (*(i16 *)((u8 *)&g.d_0063eade))
#define hof_last_entry_score_i16 (*(i16 *)((u8 *)&g.d_0063f230))
#define hof_last_entry_rating_i16 (*(i16 *)((u8 *)&g.d_0063f242))
#define local_10 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl hall_of_fame_add_entry(iptr civ)

{
  i32 uVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = -1;
  iVar2 = score_total;
  if (score_total <= score_conquest_bonus) {
    iVar2 = score_conquest_bonus;
  }
  hall_of_fame_new_entry_i16 = (i16)iVar2;
  hof_new_difficulty = (ushort)game.difficulty;
  if ((game.game_flags & 0x10) != 0) {
    hof_new_difficulty = hof_new_difficulty | 0x80;
  }
  hof_new_turn_i16 = game.turn;
  hof_new_year_i16 = game.year;
  uVar1 = civ_total_population(civ);
  hof_new_population_i16 = (i16)uVar1;
  if (((game.game_flags & 0x80) == 0) || ((scenario_flags & 2) == 0)) {
    hof_new_objective_score_i16 = 0xffff;
  }
  else {
    hof_new_objective_score_i16 = (i16)score_civ_objective_value;
  }
  hof_new_year_increment_i16 = scenario_year_increment;
  hof_new_start_year_i16 = scenario_start_year;
  hof_new_is_scenario_i16 = game.game_flags & 0x80;
  hof_new_rating = (short)civ_rating_percent;
  hof_new_leader_female_i16 = (ushort)leaders[civs[civ].tribe].female;
  hof_new_title_index_i16 = (i16)civ_rating_title_index;
  uVar1 = civ_leader_name(civ);
  crt_strcpy(&hof_new_leader_name,uVar1);
  uVar1 = civ_name_plural(civ);
  crt_strcpy(&hof_new_civ_name,uVar1);
  hall_of_fame_load();
  hof_last_entry_score_i16 = 0xffff;
  hof_last_entry_rating_i16 = 0xffff;
  do {
    local_8 = 0;
    while( true ) {
      if (5 < local_8) goto LAB_00437186;
      if (*(short *)(&hall_of_fame_entry_rating + local_8 * 0x48) < hof_new_rating) break;
      local_8++;
    }
    for (local_10 = 5; local_8 < local_10; local_10--) {
      crt_memcpy(&hall_of_fame_entries + local_10 * 0x48,&hall_of_fame_entries + (local_10 * 8 - 8) * 9,0x48);
    }
    crt_memcpy(&hall_of_fame_entries + local_8 * 0x48,&hall_of_fame_new_entry,0x48);
    local_c = local_8;
LAB_00437186:
    hall_of_fame_save();
    iVar2 = hall_of_fame_show(local_c);
    if (iVar2 == 0) {
      return;
    }
    hall_of_fame_clear();
  } while( true );
}
#undef civ_rating_percent
#undef civ_rating_title_index
#undef scenario_flags
#undef scenario_start_year
#undef scenario_year_increment
#undef score_civ_objective_value
#undef hall_of_fame_new_entry_i16
#undef hof_new_turn_i16
#undef hof_new_year_i16
#undef hof_new_population_i16
#undef hof_new_objective_score_i16
#undef hof_new_year_increment_i16
#undef hof_new_start_year_i16
#undef hof_new_is_scenario_i16
#undef hof_new_leader_female_i16
#undef hof_new_title_index_i16
#undef hof_last_entry_score_i16
#undef hof_last_entry_rating_i16
#undef local_10
#undef local_c
#undef local_8

/* 004371b3 auto */
void __cdecl credits_text_global_init(void)

{
  credits_text_static_init();
  return;
}

/* 004371c8 auto */
void __cdecl credits_text_static_init(void)

{
  memblock_ctor((MemBlock *)&credits_text_block);
  return;
}

/* 004371e2 auto */
#define credits_line_count (*(i32 *)((u8 *)&g.d_00625ec8))
void __cdecl credits_text_init(uint param_1)

{
  memblock_init(ADDR(0x63f038, ((u8 *)&g.d_0063f038)),2,param_1);
  credits_line_count = 0;
  return;
}
#undef credits_line_count

/* 0043720f auto */
void __cdecl credits_text_free(void)

{
  memblock_free(ADDR(0x63f038, ((u8 *)&g.d_0063f038)));
  return;
}

/* 0043722c auto */
#define credits_line_count (*(int *)((u8 *)&g.d_00625ec8))
int __cdecl credits_add_line(char *param_1)

{
  int iVar1;
  size_t sVar2;
  i32 uVar3;
  
  sVar2 = _strlen(param_1);
  uVar3 = memblock_alloc(ADDR(0x63f038, ((u8 *)&g.d_0063f038)),sVar2 + 1);
  crt_strcpy(uVar3,param_1);
  iVar1 = credits_line_count;
  credits_line_count++;
  return iVar1;
}
#undef credits_line_count

/* 00437284 auto */
#define local_8 (*(char * *)(frame_ + FRAME_OFF(0)))
char * __cdecl credits_get_line(int param_1)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = credits_text_data;
  for (; param_1 != 0; param_1--) {
    for (; *local_8 != '\0'; local_8++) {
    }
    local_8++;
  }
  return local_8;
}
#undef local_8

/* 004372cd auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
i32 __cdecl credits_load_section(i32 param_1)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 1;
  switch(param_1) {
  case 0:
    iVar1 = text_open_section(ADDR(0x626150, ((u8 *)&g.d_00626150)),ADDR(0x626148, ((u8 *)&g.d_00626148)));
    break;
  case 1:
    iVar1 = text_open_section(ADDR(0x626160, ((u8 *)&g.d_00626160)),ADDR(0x626158, ((u8 *)&g.d_00626158)));
    break;
  case 2:
    iVar1 = text_open_section(ADDR(0x626174, ((u8 *)&g.d_00626174)),ADDR(0x62616c, ((u8 *)&g.d_0062616c)));
    goto joined_r0x00437377;
  case 3:
    iVar1 = text_open_section(ADDR(0x626188, ((u8 *)&g.d_00626188)),ADDR(0x626180, ((u8 *)&g.d_00626180)));
joined_r0x00437377:
    if (iVar1 != 0) {
      return 1;
    }
    goto LAB_004373c4;
  default:
    goto switchD_004373ad_default;
  }
  if (iVar1 == 0) {
LAB_004373c4:
    while ((iVar1 = text_read_line(1), iVar1 != 0 && (text_buffer != '@'))) {
      credits_add_line(&text_buffer);
    }
    local_8 = 0;
  }
switchD_004373ad_default:
  return local_8;
}
#undef text_buffer
#undef local_8

/* 0043742f auto */
#define advisor_client_width (*(int *)((u8 *)&g.d_0063ec3c))
#define advisor_client_x (*(int *)((u8 *)&g.d_0063ec34))
#define advisor_row_height (*(int *)((u8 *)&g.d_0063ef80))
#define credits_line_count (*(int *)((u8 *)&g.d_00625ec8))
#define credits_partial_redraw_ok (*(uint *)((u8 *)&g.d_00625ed0))
#define credits_scroll_pos (*(int *)((u8 *)&g.d_00625ecc))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define advisor_list_top_i32 (*(i32 *)((u8 *)&g.d_0063ef78))
#define advisor_list_height_i32 (*(i32 *)((u8 *)&g.d_0063ef7c))
#define local_94 (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_84 (*(DibSurface * *)(frame_ + FRAME_OFF(20)))
#define local_80 (*(DibSurface * *)(frame_ + FRAME_OFF(24)))
#define local_7c (*(i32 *)(frame_ + FRAME_OFF(28)))
#define local_78 (*(Sprite * *)(frame_ + FRAME_OFF(32)))
#define local_74 (*(DibSurface * *)(frame_ + FRAME_OFF(36)))
#define local_70 (*(DibSurface * *)(frame_ + FRAME_OFF(40)))
#define local_6c (*(Sprite * *)(frame_ + FRAME_OFF(44)))
#define local_68 (*(Sprite * *)(frame_ + FRAME_OFF(48)))
#define local_64 (*(int *)(frame_ + FRAME_OFF(52)))
#define local_60 (*(int *)(frame_ + FRAME_OFF(56)))
#define local_5c (*(int *)(frame_ + FRAME_OFF(60)))
#define local_58 (*(int *)(frame_ + FRAME_OFF(64)))
#define local_54 (*(int *)(frame_ + FRAME_OFF(68)))
#define local_50 (*(int *)(frame_ + FRAME_OFF(72)))
#define local_4c (*(int *)(frame_ + FRAME_OFF(76)))
#define local_48 (*(int *)(frame_ + FRAME_OFF(80)))
#define local_44 (*(int *)(frame_ + FRAME_OFF(84)))
#define local_40 (*(int *)(frame_ + FRAME_OFF(88)))
#define local_3c (*(int *)(frame_ + FRAME_OFF(92)))
#define local_38 (*(char * *)(frame_ + FRAME_OFF(96)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(100)))
#define local_30 (*(DibSurface * *)(frame_ + FRAME_OFF(104)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(108)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(112)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(116)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(120)))
#define local_1c (*(i32 *)(frame_ + FRAME_OFF(124)))
#define local_18 (*(i32 *)(frame_ + FRAME_OFF(128)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(132)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(136)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(140)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(144)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl credits_draw_scroll(int param_1)

{
  i32 uVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(152)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  if (credits_partial_redraw_ok == 0) {
    param_1 = 1;
  }
  if (param_1 == 0) {
    uVar1 = rect_height(ADDR(0x63eaa8, ((u8 *)&g.d_0063eaa8)));
    uVar2 = rect_width(ADDR(0x63eaa8, ((u8 *)&g.d_0063eaa8)));
    picwnd_blit_at
              ((FrameWindow *)&advisor_window,credits_drawn_rect - advisor_client_x,
               credits_drawn_rect_top - advisor_client_y,uVar2,uVar1);
  }
  else {
    frame_wnd_layout((FrameWindow *)&advisor_window);
    picwnd_blit((PictureWindow *)&advisor_window);
  }
  local_54 = advisor_client_y;
  local_5c = advisor_client_y + 0x176;
  local_28 = font_line_spacing((GameFont *)&credits_font);
  text_set_surface(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)));
  text_set_font(ADDR(0x63ea20, ((u8 *)&g.d_0063ea20)));
  text_set_colors(0x25,0x12,2,1);
  advisor_row_height = local_28;
  advisor_list_top_i32 = local_54;
  advisor_list_height_i32 = local_5c - local_54;
  local_58 = advisor_client_x + 2;
  local_60 = local_54;
  local_64 = credits_scroll_pos;
  local_50 = credits_scroll_pos / (local_28 / 2);
  if (local_50 < credits_line_count) {
    local_60 = local_54 + (credits_scroll_pos % (local_28 / 2)) * -2;
    for (local_2c = 0; local_2c < 0x1e; local_2c++) {
      if ((-1 < *(int *)(&credits_slot_lines + local_2c * 4)) &&
         (*(int *)(&credits_slot_lines + local_2c * 4) < local_50)) {
        local_6c = *(Sprite **)(&credits_slot_sprites + local_2c * 4);
        local_68 = local_6c;
        if (local_6c != (Sprite *)0x0) {
          sprite_scalar_dtor(local_6c,1);
        }
        *(i32 *)(&credits_slot_sprites + local_2c * 4) = 0;
        *(i32 *)(&credits_slot_lines + local_2c * 4) = 0xffffffff;
      }
    }
    local_3c = 2;
    for (; (local_60 < local_5c && (local_50 < credits_line_count)); local_50++) {
      local_38 = (char *)credits_get_line(local_50);
      local_14 = -1;
      local_34 = -1;
      for (local_2c = 0; local_2c < 0x1e; local_2c++) {
        if (*(int *)(&credits_slot_lines + local_2c * 4) == local_50) {
          local_14 = local_2c;
          break;
        }
        if ((*(int *)(&credits_slot_lines + local_2c * 4) < 0) && (local_34 < 0)) {
          local_34 = local_2c;
        }
      }
      if (local_14 < 0) {
        if (local_34 < 0) goto LAB_00437a02;
        if (*local_38 == '^') {
          local_38++;
          text_clear();
          text_append((iptr)local_38);
          local_38 = &text_buffer;
          text_set_colors(0xba,0x12,0xffffffff,0xffffffff);
        }
        else {
          text_set_colors(0xbe,0x12,0xffffffff,0xffffffff);
        }
        local_4c = font_text_width((GameFont *)&credits_font,(iptr)local_38);
        local_70 = operator_new(0x48);
        local_8 = 0;
        if (local_70 == (DibSurface *)0x0) {
          local_74 = (DibSurface *)0x0;
        }
        else {
          local_74 = (DibSurface *)surface_ctor(local_70);
        }
        local_8 = 0xffffffff;
        local_30 = local_74;
        if (local_4c != 0) {
          surface_create(local_74,local_4c,local_28);
          surface_set_palette(local_30,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
          text_set_surface((iptr)local_30);
          surface_fill(local_30,0xfa);
          gfx_draw_text((iptr)local_38,0,0);
        }
        local_78 = operator_new(0x3c);
        local_8 = 1;
        if (local_78 == (Sprite *)0x0) {
          local_7c = 0;
        }
        else {
          local_7c = sprite_init(local_78);
        }
        local_8 = 0xffffffff;
        *(i32 *)(&credits_slot_sprites + local_34 * 4) = local_7c;
        if (local_4c != 0) {
          sprite_grab_from_surface
                    (*(Sprite **)(&credits_slot_sprites + local_34 * 4),(iptr)local_30,0xfa,0,0,
                     local_4c,local_28);
        }
        local_84 = local_30;
        local_80 = local_30;
        if (local_30 != (DibSurface *)0x0) {
          surface_delete(local_30,1);
        }
        *(int *)(&credits_slot_lines + local_34 * 4) = local_50;
        *(int *)(&credits_slot_x + local_34 * 4) =
             ((advisor_client_width >> 1) + advisor_client_x) - (local_4c >> 1);
        *(int *)(&credits_slot_widths + local_34 * 4) = local_4c;
        local_14 = local_34;
      }
      local_4c = *(int *)(&credits_slot_widths + local_14 * 4);
      if (local_4c != 0) {
        sprite_draw
                  (*(Sprite **)(&credits_slot_sprites + local_14 * 4),(iptr)local_94,ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),
                   *(i32 *)(&credits_slot_x + local_14 * 4),local_60);
      }
      if (local_3c <= local_4c) {
        local_3c = local_4c;
      }
      local_60 += local_28;
    }
    local_3c += 2;
    local_48 = (advisor_client_width >> 1) + advisor_client_x;
    local_40 = local_48 - (local_3c >> 1);
    local_44 = local_3c + local_40;
    rect_set((iptr)&local_24,local_40,local_54,local_44,local_5c);
    credits_drawn_rect = local_24;
    credits_drawn_rect_top = local_20;
    credits_drawn_rect_right = local_1c;
    credits_drawn_rect_bottom = local_18;
    if (advisor_client_width <= local_3c) {
      param_1 = 1;
    }
    credits_partial_redraw_ok = (uint)(advisor_client_width > local_3c);
    if (param_1 == 0) {
      wnd_blit_surface_rect((DibSurface *)&advisor_window,(iptr)&local_24);
    }
    else {
      frame_wnd_draw_caption((FrameWindow *)&advisor_window);
      wnd_blit_surface((DibSurface *)&advisor_window);
    }
  }
  else {
    wnd_end_modal_loop((ModalMenuWindow *)&advisor_wnd);
  }
LAB_00437a02:
  return;
}
#undef advisor_client_width
#undef advisor_client_x
#undef advisor_row_height
#undef credits_line_count
#undef credits_partial_redraw_ok
#undef credits_scroll_pos
#undef text_buffer
#undef advisor_list_top_i32
#undef advisor_list_height_i32
#undef local_94
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
#undef puStack_c
#undef local_8

/* 00437a10 auto */
void __cdecl credits_on_redraw(void)

{
  credits_draw_scroll(1);
  return;
}

/* 00437a2a auto */
#define credits_scroll_pos (*(int *)((u8 *)&g.d_00625ecc))
void __cdecl credits_on_timer(void)

{
  credits_scroll_pos++;
  credits_draw_scroll(0);
  return;
}
#undef credits_scroll_pos

/* 00437a4a auto */
#define credits_partial_redraw_ok (*(i32 *)((u8 *)&g.d_00625ed0))
#define credits_scroll_pos (*(i32 *)((u8 *)&g.d_00625ecc))
#define advisor_modal_start_ticks_i32 (*(i32 *)((u8 *)&g.d_00625ec0))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl credits_show(int param_1)

{
  int iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = -1;
  credits_text_init(0x1000);
  for (local_8 = 0; local_8 < 0x1e; local_8++) {
    *(i32 *)(&credits_slot_sprites + local_8 * 4) = 0;
    *(i32 *)(&credits_slot_lines + local_8 * 4) = 0xffffffff;
  }
  iVar1 = credits_load_section(param_1);
  if (iVar1 == 0) {
    credits_scroll_pos = 0;
    credits_partial_redraw_ok = 0;
    advisor_report_civ = 0;
    if (param_1 == 3) {
      picwnd_open((PictureWindow *)&advisor_window,10000,8,1,600,400,0,0);
    }
    else {
      picwnd_open((PictureWindow *)&advisor_window,0xffffffa1,8,1,600,400,0,0)
      ;
    }
    advisor_add_close_button((ViewWindow *)&advisor_window);
    wnd_set_redraw_callback((SurfaceWindow *)&advisor_window,ADDR(0x401c6c, credits_on_redraw));
    music_play_track(3,0);
    wnd_repaint((SurfaceWindow *)&advisor_window);
    window_show((WindowObjectView *)&advisor_window);
    ui_flush_input();
    local_c = game_timer_create(ADDR(0x4010f0, credits_on_timer),0x32,0xffffffff);
    if (2 < game.multiplayer) {
      wnd_set_modal_idle_callback((ModalMenuWindow *)&advisor_wnd,ADDR(0x402789, advisor_mp_idle));
    }
    advisor_modal_start_ticks_i32 = timer_ticks();
    wnd_run_modal_loop((ModalMenuWindow *)&advisor_wnd);
    wnd_set_modal_idle_callback((ModalMenuWindow *)&advisor_wnd,0);
    picwnd_close((PictureWindowCore *)&advisor_window);
  }
  for (local_8 = 0; local_8 < 0x1e; local_8++) {
    if (-1 < *(int *)(&credits_slot_lines + local_8 * 4)) {
      if (*(Sprite **)(&credits_slot_sprites + local_8 * 4) != (Sprite *)0x0) {
        sprite_scalar_dtor(*(Sprite **)(&credits_slot_sprites + local_8 * 4),1);
      }
      *(i32 *)(&credits_slot_sprites + local_8 * 4) = 0;
      *(i32 *)(&credits_slot_lines + local_8 * 4) = 0xffffffff;
    }
  }
  if (-1 < local_c) {
    game_timer_destroy(local_c);
  }
  credits_text_free();
  return;
}
#undef credits_partial_redraw_ok
#undef credits_scroll_pos
#undef advisor_modal_start_ticks_i32
#undef local_c
#undef local_8

/* 00437c6f auto */
void __cdecl intel_report_end_modal(void)

{
  wnd_end_modal_loop((ModalMenuWindow *)&advisor_wnd);
  return;
}

/* 00437c8a auto */
#define advisor_modal_start_ticks_i32 (*(i32 *)((u8 *)&g.d_00625ec0))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl advisor_mp_idle(void)

{
  int iVar1;
  
  net_process_messages((NetSession *)&net_session,1,0);
  iVar1 = timer_ticks();
  if (0x4b0 < iVar1 - advisor_modal_start_ticks_i32) {
    intel_report_end_modal();
    advisor_modal_start_ticks_i32 = timer_ticks();
  }
  return;
}
#undef advisor_modal_start_ticks_i32

/* 00437ccd auto */
#define casualty_scroll_pos (*(i32 *)((u8 *)&g.d_0063e958))
void __cdecl casualty_scrollbar_on_scroll(i32 param_1)

{
  casualty_scroll_pos = param_1;
  casualty_timeline_draw();
  return;
}
#undef casualty_scroll_pos

/* 00437cea auto */
#define casualty_client_x (*(int *)((u8 *)&g.d_0063e61c))
#define casualty_row_height (*(i32 *)((u8 *)&g.d_0063e968))
#define casualty_scroll_pos (*(int *)((u8 *)&g.d_0063e958))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define casualty_page_count_i32 (*(i32 *)((u8 *)&g.d_0063e950))
#define casualty_list_height_i32 (*(i32 *)((u8 *)&g.d_0063e964))
#define casualty_vscroll_width_i32 (*(i32 *)((u8 *)&g.d_0063e98c))
#define local_50 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(44)))
#define local_18 (*(i8 (*)[16])(frame_ + FRAME_OFF(56)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(72)))
/* WARNING: Removing unreachable block (ram,0x004384ab) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl casualty_timeline_draw(void)

{
  int iVar2;
  int iVar3;
  int iVar4;
  iptr unit;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uptr sVar10;
  uptr sVar11;
  size_t sVar12;
  i32 uVar13;
  iptr civ;
  i8 frame_[FRAME_OFF(80)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ = casualty_window_civ;
  frame_wnd_layout((FrameWindow *)&casualty_window);
  frame_wnd_draw_caption((FrameWindow *)&casualty_window);
  picwnd_blit((PictureWindow *)&casualty_window);
  iVar2 = casualty_client_y + 2;
  iVar3 = casualty_client_y + 0x174;
  iVar4 = font_line_spacing((GameFont *)&advisor_font);
  text_set_surface(ADDR(0x63e4f8, ((u8 *)&g.d_0063e4f8)));
  text_set_font(ADDR(0x63eac0, ((u8 *)&g.d_0063eac0)));
  text_set_colors(0x25,0x12,2,1);
  text_clear();
  unit = label_string(*(i32 *)(label_string_ids + 0x53c));
  text_append(unit);
  text_append_colon();
  unit = label_string(*(i32 *)(label_string_ids + 0xda0));
  text_append(unit);
  gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),casualty_client_x,iVar2,casualty_client_width);
  iVar2 += iVar4;
  text_clear();
  iVar6 = int_clamp(civs[civ].government - 1,0,4);
  text_append_label(iVar6 + 0x148);
  text_append_space();
  text_append_label(0x8c);
  text_append_space();
  unit = civ_name_plural(civ);
  text_append(unit);
  gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),casualty_client_x,iVar2,casualty_client_width);
  iVar2 += iVar4;
  text_clear();
  unit = civ_leader_title(civ);
  text_append(unit);
  text_append_space();
  unit = civ_leader_name(civ);
  text_append(unit);
  text_append_colon();
  text_append_year((int)game.year);
  gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),casualty_client_x,iVar2,casualty_client_width);
  iVar2 += iVar4;
  iVar4 = iVar2 + 2;
  casualty_row_height = 0x18;
  casualty_first_row_y = iVar2 + 0x1a;
  casualty_list_height_i32 = iVar3 - iVar4;
  casualty_rows_per_page = int_clamp((iVar3 - iVar4) / 0x18,1,99);
  local_24 = 0;
  if (*(int *)(&casualty_log_first + civ * 4) < *(int *)(&casualty_log_next + civ * 4)) {
    local_24 = *(int *)(&casualty_log_next + civ * 4) - *(int *)(&casualty_log_first + civ * 4);
  }
  else if (*(int *)(&casualty_log_first + civ * 4) < *(int *)(&casualty_log_next + civ * 4)) {
    local_24 = 300;
  }
  local_8 = casualty_rows_per_page;
  if (local_24 != 0) {
    casualty_page_count_i32 = int_clamp((casualty_rows_per_page - 1 + local_24) / casualty_rows_per_page,1,99);
    uVar13 = int_clamp(local_24 - 1,0,999);
    iVar2 = int_clamp(casualty_scroll_pos,0,uVar13);
    local_30 = 1;
    local_38 = (*(int *)(&casualty_log_next + civ * 4) - 1) - iVar2;
    casualty_scroll_pos = iVar2;
    local_50 = iVar4;
    if (local_38 < 0) {
      local_38 += 300;
    }
    while (((local_30 <= *(int *)(&casualty_counts + civ * 4) && (local_30 - 1 < iVar2 + local_8))
           && ((*(int *)(&casualty_log_first + civ * 4) != 0 ||
               (local_38 < *(int *)(&casualty_log_next + civ * 4)))))) {
      iVar6 = (local_30 + 1U & 1) * 0x40 + casualty_client_x;
      unit = unit_make_dummy((int)*(short *)(&casualty_log_unit_types + civ * 0x27d8 + local_38 * 0x22),
                                 civ);
      gfx_draw_unit(ADDR(0x63e4f8, ((u8 *)&g.d_0063e4f8)),unit,0,iVar6 + 2,local_50,0,0);
      text_set_font(ADDR(0x63eab8, ((u8 *)&g.d_0063eab8)));
      text_set_colors(0x25,0x12,1,1);
      iVar6 = casualty_client_x;
      iVar7 = local_50 + 0x11;
      iVar8 = casualty_client_x + 0x8c;
      text_clear();
      unit = label_string(unit_types
                                 [*(short *)(&casualty_log_unit_types + civ * 0x27d8 + local_38 * 0x22)].name
                                );
      text_append(unit);
      while (iVar9 = font_text_width((GameFont *)&advisor_bold_font,ADDR(0x679640, ((u8 *)&g.d_00679640))),
            0x60 < iVar9) {
        sVar10 = _strlen(&text_buffer);
        (&text_buffer_minus1)[sVar10] = 0;
      }
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar8,iVar7);
      text_clear();
      text_append_year((int)*(short *)(&casualty_log_years + civ * 0x27d8 + local_38 * 0x22));
      while (iVar8 = font_text_width((GameFont *)&advisor_bold_font,ADDR(0x679640, ((u8 *)&g.d_00679640))),
            0x4c < iVar8) {
        sVar11 = _strlen(&text_buffer);
        (&text_buffer_minus1)[sVar11] = 0;
      }
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar6 + 0xec,iVar7);
      text_set_colors(0x5e,10,0xffffffff,0xffffffff);
      text_clear();
      text_append_int((int)*(short *)(&casualty_log_x + civ * 0x27d8 + local_38 * 0x22));
      text_append(ADDR(0x626194, ((u8 *)&g.d_00626194)));
      text_append_int((int)*(short *)(&casualty_log_y + civ * 0x27d8 + local_38 * 0x22));
      iVar8 = city_find_nearest((int)*(short *)(&casualty_log_x + civ * 0x27d8 + local_38 * 0x22),
                                 (int)*(short *)(&casualty_log_y + civ * 0x27d8 + local_38 * 0x22),
                                 -1,0xffffffff,-1);
      if (-1 < iVar8) {
        text_append(ADDR(0x626198, ((u8 *)&g.d_00626198)));
        text_append(iVar8 * 0x58 + ADDR(0x64f360, ((u8 *)&cities + 32)));
        text_append(ADDR(0x6261a0, ((u8 *)&g.d_006261a0)));
      }
      while (iVar8 = font_text_width((GameFont *)&advisor_bold_font,ADDR(0x679640, ((u8 *)&g.d_00679640))),
            0xaa < iVar8) {
        sVar12 = _strlen(&text_buffer);
        (&text_buffer_minus1)[sVar12] = 0;
      }
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar6 + 0x138,iVar7);
      text_set_colors((int)*(short *)(&casualty_log_killer_colors + civ * 0x27d8 + local_38 * 0x22),0x12,
                         0xffffffff,0xffffffff);
      text_clear();
      text_append(local_38 * 0x22 + civ * 0x27d8 + ADDR(0x6af2aa, ((u8 *)&g.d_006af2a8 + 2)));
      while (iVar9 = casualty_client_right - casualty_vscroll_width_i32,
            iVar8 = font_text_width((GameFont *)&advisor_bold_font,ADDR(0x679640, ((u8 *)&g.d_00679640))),
            (iVar9 - 2) - (iVar6 + 0x1e2) < iVar8) {
        sVar12 = _strlen(&text_buffer);
        (&text_buffer_minus1)[sVar12] = 0;
      }
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar6 + 0x1e2,iVar7);
      local_30++;
      local_38--;
      if (local_38 < 0) {
        local_38 = 299;
      }
      local_50 += 0x18;
    }
  }
  if (casualty_controls_created == 0) {
    rect_set((iptr)local_18,(casualty_client_right - casualty_vscroll_width_i32) - 2,iVar4,casualty_client_right - 2,
                       iVar3);
    scrollbar_create((Control *)&casualty_scrollbar,ADDR(0x63e540, ((u8 *)&g.d_0063e540)),200,(iptr)local_18,1);
    scrollbar_set_callback((Control *)&casualty_scrollbar,ADDR(0x401398, casualty_scrollbar_on_scroll));
    wnd_set_dblclick_handler((WndHandlersMouseSetView *)&casualty_wnd_events,ADDR(0x40320b, casualty_timeline_on_dblclick));
  }
  uVar13 = int_clamp(local_24 - 1,0,999);
  scrollbar_set_range((Control *)&casualty_scrollbar,0,uVar13);
  scrollbar_set_pos((ClickControl *)&casualty_scrollbar,casualty_scroll_pos);
  scrollbar_set_page_size((Control *)&casualty_scrollbar,casualty_rows_per_page);
  if (casualty_controls_created == 0) {
    ctrl_show_and_redraw((Control *)&casualty_scrollbar);
    casualty_controls_created = 1;
  }
  wnd_blit_surface((DibSurface *)&casualty_window);
  return;
}
#undef casualty_client_x
#undef casualty_row_height
#undef casualty_scroll_pos
#undef text_buffer
#undef casualty_page_count_i32
#undef casualty_list_height_i32
#undef casualty_vscroll_width_i32
#undef local_50
#undef local_38
#undef local_30
#undef local_24
#undef local_18
#undef local_8

/* 0043856b auto */
#define casualty_client_x (*(i32 *)((u8 *)&g.d_0063e61c))
#define casualty_report_param_i32 (*(i32 *)((u8 *)&g.d_0063e994))
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
/* WARNING: Removing unreachable block (ram,0x00438634) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl casualty_timeline_show(iptr param_1)

{
  int iVar1;
  int iVar2;
  iptr iVar3;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (casualty_window_report_id < 0) {
    picwnd_open((PictureWindow *)&casualty_window,2,0xc,0,600,400,0,0);
    casualty_window_civ = param_1;
    casualty_report_param_i32 = 0;
    rect_set_xywh((iptr)local_14,2,0,0x254,0x18);
    iVar1 = casualty_client_y;
    iVar2 = rect_height((iptr)local_14);
    rect_offset((iptr)local_14,casualty_client_x,(iVar1 - iVar2) + 0x18e);
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x51c));
    button_create
              ((Control *)&casualty_close_button,ADDR(0x63e540, ((u8 *)&g.d_0063e540)),100,(iptr)local_14,iVar3);
    button_set_callback((Control *)&casualty_close_button,ADDR(0x401235, advisor_on_close_clicked));
    ctrl_set_default_button((Control *)&casualty_close_button);
    ctrl_set_cancel_button((Control *)&casualty_close_button);
    wnd_set_redraw_callback((SurfaceWindow *)&casualty_window,ADDR(0x4022cf, casualty_timeline_draw));
    wnd_repaint((SurfaceWindow *)&casualty_window);
    window_show((WindowObjectView *)&casualty_window);
  }
  else {
    wnd_repaint((SurfaceWindow *)&casualty_window);
    window_show((WindowObjectView *)&casualty_window);
  }
  return;
}
#undef casualty_client_x
#undef casualty_report_param_i32
#undef local_14

/* 004386b8 auto */
#define casualty_row_height (*(int *)((u8 *)&g.d_0063e968))
#define casualty_scroll_pos (*(int *)((u8 *)&g.d_0063e958))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
void __cdecl casualty_timeline_on_dblclick(i32 param_1,int param_2)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  param_2 -= (casualty_first_row_y - casualty_row_height / 2);
  if ((-1 < param_2) && (param_2 = param_2 / casualty_row_height, param_2 < casualty_rows_per_page)) {
    local_c = ((*(int *)(&casualty_log_next + casualty_window_civ * 4) - 1) - casualty_scroll_pos) - param_2;
    if (local_c < 0) {
      local_c += 300;
    }
    if ((*(int *)(&casualty_log_next + casualty_window_civ * 4) != local_c) &&
       (((*(int *)(&casualty_log_first + casualty_window_civ * 4) != 0 ||
         (0x12a < *(int *)(&casualty_counts + casualty_window_civ * 4))) ||
        (local_c < *(int *)(&casualty_log_next + casualty_window_civ * 4))))) {
      mapview_center_on
                ((ViewWindow *)&map_views,
                 (int)*(short *)(&casualty_log_x + casualty_window_civ * 0x27d8 + local_c * 0x22),
                 (int)*(short *)(&casualty_log_y + casualty_window_civ * 0x27d8 + local_c * 0x22));
    }
  }
  return;
}
#undef casualty_row_height
#undef casualty_scroll_pos
#undef local_c

/* 0044ce16 auto */
#define local_14 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(8)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(16)))
ThroneRoomWindow * __thiscall throneroom_ctor(ThroneRoomWindow *this,iptr param_1)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  wnd_ctor((ModalMenuWindow *)this);
  local_8 = 0;
  palette_init((GamePalette *)&this->control_list);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  dll_handle_init((DllHandle *)this->pad_4fc);
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  surfwnd_ctor((SurfaceWindow *)this->pad_504);
  (*(i8 *)((char *)&local_8 + 0)) = 3;
  surface_ctor((DibSurface *)(this->pad_504 + 0x114));
  (*(i8 *)((char *)&local_8 + 0)) = 4;
  clickmap_ctor(this->pad_638 + 0x28);
  (*(i8 *)((char *)&local_8 + 0)) = 5;
  dialog_ctor((Dialog *)this->pad_1930,0x4000);
  (*(i8 *)((char *)&local_8 + 0)) = 6;
  font_init_empty((GameFont *)(this->pad_19f8 + 0x23c));
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),7);
  gfx_get_screen_rect((iptr)(this->pad_1e4 + 0x308));
  this->throne_civ = param_1;
  throneroom_wnd = (iptr)this;
  this->throne_complete = 1;
  for (local_14 = 0; local_14 < 8; local_14++) {
    if (civs[(this->throne_civ)].throne_room[local_14] < 4) {
      this->throne_complete = 0;
    }
  }
  SetRect((LPRECT)(this->pad_19f8 + 0x22c),0,0x1c2,0x280,0x1e0);
  font_set_styled((GameFont *)(this->pad_19f8 + 0x23c),0,0x12,3);
  return this;
}
#undef local_14
#undef local_10
#undef puStack_c
#undef local_8

/* 0044d027 auto */
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __thiscall throneroom_dtor(ThroneRoomDtorView *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  (*(i32 *)((char *)&local_8 + 1)) = 0;
  (*(i8 *)((char *)&local_8 + 0)) = 7;
  throneroom_wnd = 0;
  dll_handle_free((DllHandle *)(this->pad_0 + 0x4fc));
  (*(i8 *)((char *)&local_8 + 0)) = 6;
  /* inlined unwind funclet 0044d0d8 */ { font_destroy((GameFont *)(*(int *)((iptr)&this) + 0x1c34)); }
  (*(i8 *)((char *)&local_8 + 0)) = 5;
  /* inlined unwind funclet 0044d0e7 */ { dialog_dtor((Dialog *)(*(int *)((iptr)&this) + 0x1930)); }
  (*(i8 *)((char *)&local_8 + 0)) = 4;
  /* inlined unwind funclet 0044d0f6 */ { clickmap_dtor(*(int *)((iptr)&this) + 0x660); }
  (*(i8 *)((char *)&local_8 + 0)) = 3;
  /* inlined unwind funclet 0044d105 */ { surface_dtor((DibSurface *)(*(int *)((iptr)&this) + 0x618)); }
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  /* inlined unwind funclet 0044d114 */ { surfwnd_dtor((SurfaceWindow *)(*(int *)((iptr)&this) + 0x504)); }
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  /* inlined unwind funclet 0044d123 */ { dll_free((DllHandle *)(*(int *)((iptr)&this) + 0x4fc)); }
  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
  /* inlined unwind funclet 0044d132 */ { palette_destroy((GamePalette *)(*(int *)((iptr)&this) + 0xb8)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet 0044d141 */ { wnd_dtor(*(WndBase **)((iptr)&this)); }
  return;
}
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0044d162 auto */
#define local_84 (*(i8 (*)[128])(frame_ + FRAME_OFF(4)))
uint __thiscall throneroom_create_windows(PictureFrameWindow *this)

{
  int iVar1;
  i8 frame_[FRAME_OFF(136)] __attribute__((aligned(8)));  /* original stack frame */
  
  str_clear((iptr)local_84);
  str_append((iptr)local_84,ADDR(0x626814, ((u8 *)&g.d_00626814)));
  iVar1 = file_resolve_path((iptr)local_84);
  if (iVar1 != 0) {
    dll_handle_load((DllHandle *)this->pad_4fc,(iptr)local_84);
    wnd_create_with_handlers
              ((WndBase *)this,ADDR(0x62681c, ((u8 *)&g.d_0062681c)),0x800,0,0,this->throne_width,this->throne_height + 5,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00))
               ,ADDR(0x6553d8, ((u8 *)&g.d_006553d8)));
    wnd_set_bg_color((WndBase *)this,0);
    wnd_create_with_surface
              ((DibSurface *)this->pad_504,ADDR(0x626820, ((u8 *)&g.d_00626820)),0x800,0,0,0x280,0x1e0,(iptr)&this->control_list,
               (iptr)this);
    wnd_center((WndCenterView *)(this->pad_504 + 0x48));
    wnd_set_lbuttonup_handler((WndEventHandlers *)(this->pad_504 + 0x58),ADDR(0x4034bd, throneroom_on_click));
    wnd_set_keydown_handler((WndEventHandlers *)(this->pad_504 + 0x58),ADDR(0x401fe6, throneroom_on_key));
  }
  return (uint)(iVar1 != 0);
}
#undef local_84

/* 0044d296 auto */
#define text_line_cursor (*(iptr *)((u8 *)&g.d_00673f14))
#define local_428 (*(GameFont *)(frame_ + FRAME_OFF(0)))
#define local_420 (*(i8 (*)[1024])(frame_ + FRAME_OFF(8)))
#define local_20 (*(tagRECT *)(frame_ + FRAME_OFF(1032)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1048)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1052)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1056)))
void __thiscall throneroom_run_upgrade(ThroneRoomWindow *this)

{
  int iVar1;
  char *pcVar2;
  i8 frame_[FRAME_OFF(1064)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  iVar1 = throneroom_create_windows((PictureFrameWindow *)this);
  if ((iVar1 != 0) && (iVar1 = throneroom_render(this), iVar1 != 0)) {
    surface_create((DibSurface *)(this->pad_504 + 0x114),0x280,0x1e0);
    SetRect(&local_20,0,0,0x280,0x1e0);
    surface_blit
              ((DibSurface *)this->pad_504,(iptr)(this->pad_504 + 0x114),(iptr)&local_20,
               (iptr)&local_20);
    font_init(&local_428,1,0x18);
    local_8 = 0;
    iVar1 = text_open_section(ADDR(0x6558e8, ((u8 *)&g.d_006558e8)),ADDR(0x626824, ((u8 *)&g.d_00626824)));
    if (iVar1 == 0) {
      str_clear((iptr)local_420);
      while (pcVar2 = (char *)text_read_line(1), *pcVar2 != '@') {
        str_append((iptr)local_420,text_line_cursor);
        str_append((iptr)local_420,ADDR(0x62682c, ((u8 *)&g.d_0062682c)));
      }
      SetRect(&local_20,100,0x78,0x21c,0x1c2);
      gfx_set_text_color_index(0);
      surface_draw_text_rect
                ((DibSurface *)this->pad_504,(iptr)&local_428,(iptr)local_420,(iptr)&local_20,0);
      OffsetRect(&local_20,2,2);
      gfx_set_text_color_index(0xff);
      surface_draw_text_rect
                ((DibSurface *)this->pad_504,(iptr)&local_428,(iptr)local_420,(iptr)&local_20,0);
      text_close_file();
      SetRect(&local_20,0,0,0x280,0x1e0);
    }
    throneroom_draw_click_prompt((WndBase *)this);
    this->choosing_item = 0;
    wnd_handle_show_raise((WndBase *)this);
    wnd_flush_paint();
    wnd_set_palette((WndBase *)this,(iptr)&this->control_list);
    window_show((WindowObjectView *)this->pad_504);
    wnd_flush_paint();
    input_flush_events();
    wnd_set_capture((WndBase *)(this->pad_504 + 0x48));
    if (2 < game.multiplayer) {
      wnd_set_modal_idle_callback((ModalMenuWindow *)(this->pad_504 + 0x48),ADDR(0x403585, net_modal_idle_poll));
    }
    wnd_run_modal_loop((ModalMenuWindow *)(this->pad_504 + 0x48));
    wnd_set_modal_idle_callback((ModalMenuWindow *)(this->pad_504 + 0x48),0);
    wnd_release_capture((WndBase *)(this->pad_504 + 0x48));
    iVar1 = throneroom_render_choices(this);
    if (iVar1 == 0) {
      local_8 = 0xffffffff;
      /* inlined unwind funclet 0044d99d */ { font_destroy((GameFont *)((iptr)&local_428)); }
    }
    else {
      iVar1 = text_open_section(ADDR(0x6558e8, ((u8 *)&g.d_006558e8)),ADDR(0x626830, ((u8 *)&g.d_00626830)));
      if (iVar1 == 0) {
        str_clear((iptr)local_420);
        while (pcVar2 = (char *)text_read_line(1), *pcVar2 != '@') {
          str_append((iptr)local_420,text_line_cursor);
          str_append((iptr)local_420,ADDR(0x62683c, ((u8 *)&g.d_0062683c)));
        }
        SetRect(&local_20,100,0x78,0x21c,0x1c2);
        gfx_set_text_color_index(0);
        surface_draw_text_rect
                  ((DibSurface *)this->pad_504,(iptr)&local_428,(iptr)local_420,(iptr)&local_20,0
                  );
        OffsetRect(&local_20,2,2);
        gfx_set_text_color_index(0xff);
        surface_draw_text_rect
                  ((DibSurface *)this->pad_504,(iptr)&local_428,(iptr)local_420,(iptr)&local_20,0
                  );
        text_close_file();
        SetRect(&local_20,0,0,0x280,0x1e0);
      }
      throneroom_draw_click_prompt((WndBase *)this);
      this->choosing_item = 1;
      SetRect(&local_20,0,0,0x280,0x1e0);
      gfx_dissolve_blit((iptr)this->pad_504,(iptr)&local_20,8,4);
      wnd_blit_surface((DibSurface *)this->pad_504);
      input_flush_events();
      wnd_set_capture((WndBase *)(this->pad_504 + 0x48));
      if (2 < game.multiplayer) {
        wnd_set_modal_idle_callback((ModalMenuWindow *)(this->pad_504 + 0x48),ADDR(0x403585, net_modal_idle_poll));
      }
      wnd_run_modal_loop((ModalMenuWindow *)(this->pad_504 + 0x48));
      wnd_set_modal_idle_callback((ModalMenuWindow *)(this->pad_504 + 0x48),0);
      wnd_release_capture((WndBase *)(this->pad_504 + 0x48));
      snd_play_effect(0xd,1,0,0);
      SetRect(&local_20,0,0,0x280,0x1e0);
      surface_blit
                ((DibSurface *)(this->pad_504 + 0x114),(iptr)this->pad_504,(iptr)&local_20,
                 (iptr)&local_20);
      win_flush_pending_msgs();
      gfx_dissolve_blit((iptr)this->pad_504,(iptr)&local_20,8,3);
      wnd_blit_surface((DibSurface *)this->pad_504);
      wnd_flush_paint();
      if (this->throne_complete == 0) {
        pcVar2 = (char *)(this->chosen_item + ADDR(0x64ca93, ((u8 *)&civs + 1011)) + this->throne_civ * 0x594);
        *pcVar2 = *pcVar2 + 1;
      }
      else {
        civs[this->throne_civ].throne_room[8] =
             civs[this->throne_civ].throne_room[8] | (byte)(1 << ((byte)this->chosen_item & 0x1f));
      }
      iVar1 = throneroom_render(this);
      if (iVar1 != 0) {
        snd_play_effect(0xd,1,0,0);
        SetRect(&local_20,0,0,0x280,0x1e0);
        gfx_dissolve_blit((iptr)this->pad_504,(iptr)&local_20,4,1);
        throneroom_draw_click_prompt((WndBase *)this);
        wnd_blit_surface((DibSurface *)this->pad_504);
        this->choosing_item = 0;
        wnd_set_capture((WndBase *)(this->pad_504 + 0x48));
        if (2 < game.multiplayer) {
          wnd_set_modal_idle_callback((ModalMenuWindow *)(this->pad_504 + 0x48),ADDR(0x403585, net_modal_idle_poll));
        }
        wnd_run_modal_loop((ModalMenuWindow *)(this->pad_504 + 0x48));
        wnd_set_modal_idle_callback((ModalMenuWindow *)(this->pad_504 + 0x48),0);
        wnd_release_capture((WndBase *)(this->pad_504 + 0x48));
        wnd_hide((WndBase *)(this->pad_504 + 0x48));
        wnd_flush_paint();
      }
      wnd_set_palette((WndBase *)this,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
      wnd_hide((WndBase *)this);
      wnd_flush_paint();
      local_8 = 0xffffffff;
      /* inlined unwind funclet 0044d99d */ { font_destroy((GameFont *)((iptr)&local_428)); }
    }
  }
  return;
}
#undef text_line_cursor
#undef local_428
#undef local_420
#undef local_20
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0044d9c1 auto */
void __thiscall throneroom_run_view(ThroneRoomWindow *this)

{
  int iVar1;
  
  iVar1 = throneroom_create_windows((PictureFrameWindow *)this);
  if ((iVar1 != 0) && (iVar1 = throneroom_render(this), iVar1 != 0)) {
    throneroom_draw_click_prompt((WndBase *)this);
    this->choosing_item = 0;
    wnd_handle_show_raise((WndBase *)this);
    wnd_flush_paint();
    wnd_set_palette((WndBase *)this,(iptr)&this->control_list);
    window_show((WindowObjectView *)this->pad_504);
    wnd_flush_paint();
    if (2 < game.multiplayer) {
      wnd_set_modal_idle_callback((ModalMenuWindow *)(this->pad_504 + 0x48),ADDR(0x403585, net_modal_idle_poll));
    }
    wnd_run_modal_loop((ModalMenuWindow *)(this->pad_504 + 0x48));
    wnd_set_modal_idle_callback((ModalMenuWindow *)(this->pad_504 + 0x48),0);
    wnd_hide((WndBase *)(this->pad_504 + 0x48));
    wnd_flush_paint();
    wnd_set_palette((WndBase *)this,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
    wnd_hide((WndBase *)this);
    wnd_flush_paint();
  }
  return;
}

/* 0044dab5 auto */
void __thiscall throneroom_draw_click_prompt(WndBase *this)

{
  iptr iVar1;
  
  text_clear();
  text_append(ADDR(0x626840, ((u8 *)&g.d_00626840)));
  iVar1 = label_string(*(i32 *)(label_string_ids + 0x720));
  text_append(iVar1);
  text_append(ADDR(0x626844, ((u8 *)&g.d_00626844)));
  gfx_set_text_color_index(0);
  surface_draw_text_in_rect
            ((DibSurface *)&this[0x50].field_4,(iptr)&this[0x1c3].field_4,ADDR(0x679640, ((u8 *)&g.d_00679640)),
             (iptr)&this[0x1c2].field_4,0);
  OffsetRect((LPRECT)&this[0x1c2].field_4,-1,-1);
  gfx_set_text_color_index(0xff);
  surface_draw_text_in_rect
            ((DibSurface *)&this[0x50].field_4,(iptr)&this[0x1c3].field_4,ADDR(0x679640, ((u8 *)&g.d_00679640)),
             (iptr)&this[0x1c2].field_4,0);
  OffsetRect((LPRECT)&this[0x1c2].field_4,1,1);
  return;
}

/* 0044db92 auto */
#define local_150 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_140 (*(i32 *)(frame_ + FRAME_OFF(16)))
#define local_13c (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
#define local_12c (*(i32 *)(frame_ + FRAME_OFF(36)))
#define local_128 (*(i8 (*)[16])(frame_ + FRAME_OFF(40)))
#define local_118 (*(i32 *)(frame_ + FRAME_OFF(56)))
#define local_114 (*(i8 (*)[16])(frame_ + FRAME_OFF(60)))
#define local_104 (*(i32 *)(frame_ + FRAME_OFF(76)))
#define local_100 (*(i8 (*)[16])(frame_ + FRAME_OFF(80)))
#define local_f0 (*(i32 *)(frame_ + FRAME_OFF(96)))
#define local_ec (*(i8 (*)[16])(frame_ + FRAME_OFF(100)))
#define local_dc (*(i32 *)(frame_ + FRAME_OFF(116)))
#define local_d8 (*(i8 (*)[16])(frame_ + FRAME_OFF(120)))
#define local_c8 (*(i32 *)(frame_ + FRAME_OFF(136)))
#define local_c4 (*(i8 (*)[16])(frame_ + FRAME_OFF(140)))
#define local_b4 (*(i32 *)(frame_ + FRAME_OFF(156)))
#define local_b0 (*(i8 (*)[16])(frame_ + FRAME_OFF(160)))
#define local_a0 (*(i32 *)(frame_ + FRAME_OFF(176)))
#define local_9c (*(DibSurface *)(frame_ + FRAME_OFF(180)))
#define local_54 (*(iptr *)(frame_ + FRAME_OFF(252)))
#define local_50 (*(int *)(frame_ + FRAME_OFF(256)))
#define local_4c (*(Sprite *)(frame_ + FRAME_OFF(260)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(320)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(324)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(328)))
i32 __thiscall throneroom_render(ThroneRoomWindow *this)

{
  int iVar1;
  i8 frame_[FRAME_OFF(336)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  surface_ctor(&local_9c);
  local_8 = 0;
  sprite_init(&local_4c);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  for (local_54 = 0; local_54 < 3; local_54++) {
    win_flush_pending_msgs();
    if (*(char *)&civs[(this->throne_civ)].throne_room[local_54] != '\0') {
      local_50 = civs[(this->throne_civ)].throne_room[local_54] - 1;
      iVar1 = surface_load_gif_resource
                        (&local_9c,local_54 * 5 + local_50 + 0x69,10,0xec,(iptr)&this->control_list);
      if (iVar1 == 0) {
        local_a0 = 0;
        local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
        /* inlined unwind funclet 0044e762 */ { sprite_destroy((Sprite *)((iptr)&local_4c)); }
        local_8 = 0xffffffff;
        /* inlined unwind funclet 0044e76b */ { surface_dtor((DibSurface *)((iptr)&local_9c)); }
        goto LAB_0044e781;
      }
      sprite_grab_from_surface
                (&local_4c,(iptr)&local_9c,9,
                 *(i32 *)(&throneroom_piece_rect_x + local_50 * 0x10 + local_54 * 0x40),
                 *(i32 *)(&throneroom_piece_rect_y + local_50 * 0x10 + local_54 * 0x40),
                 *(i32 *)(&throneroom_piece_rect_w + local_50 * 0x10 + local_54 * 0x40),
                 *(i32 *)(&throneroom_piece_rect_h + local_50 * 0x10 + local_54 * 0x40));
      sprite_replace_color(&local_4c,7,9);
      sprite_draw
                (&local_4c,(iptr)local_b0,(iptr)this->pad_504,
                 *(int *)(&throneroom_piece_rect_x + local_50 * 0x10 + local_54 * 0x40) - 1,
                 *(int *)(&throneroom_piece_rect_y + local_50 * 0x10 + local_54 * 0x40) - 1);
    }
  }
  win_flush_pending_msgs();
  if ((this->throne_complete != 0) && ((civs[this->throne_civ].throne_room[8] & 1) != 0)) {
    iVar1 = surface_load_gif_resource(&local_9c,0xa0,10,0xec,(iptr)&this->control_list);
    if (iVar1 == 0) {
      local_b4 = 0;
      local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
      /* inlined unwind funclet 0044e762 */ { sprite_destroy((Sprite *)((iptr)&local_4c)); }
      local_8 = 0xffffffff;
      /* inlined unwind funclet 0044e76b */ { surface_dtor((DibSurface *)((iptr)&local_9c)); }
      local_a0 = local_b4;
      goto LAB_0044e781;
    }
    sprite_grab_from_surface
              (&local_4c,(iptr)&local_9c,9,throneroom_bonus_rect_x,throneroom_bonus_rect_y,throneroom_bonus_rect_w,throneroom_bonus_rect_h);
    sprite_replace_color(&local_4c,7,9);
    sprite_draw
              (&local_4c,(iptr)local_c4,(iptr)this->pad_504,throneroom_bonus_rect_x - 1,throneroom_bonus_rect_y - 1);
  }
  win_flush_pending_msgs();
  if (civs[this->throne_civ].throne_room[3] != '\0') {
    local_50 = civs[this->throne_civ].throne_room[3] - 1;
    iVar1 = surface_load_gif_resource
                      (&local_9c,civs[this->throne_civ].throne_room[3] + 0x77,10,0xec,
                       (iptr)&this->control_list);
    if (iVar1 == 0) {
      local_c8 = 0;
      local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
      /* inlined unwind funclet 0044e762 */ { sprite_destroy((Sprite *)((iptr)&local_4c)); }
      local_8 = 0xffffffff;
      /* inlined unwind funclet 0044e76b */ { surface_dtor((DibSurface *)((iptr)&local_9c)); }
      local_a0 = local_c8;
      goto LAB_0044e781;
    }
    sprite_grab_from_surface
              (&local_4c,(iptr)&local_9c,9,
               *(i32 *)(&throneroom_piece_rect_x + local_50 * 0x10 + local_54 * 0x40),
               *(i32 *)(&throneroom_piece_rect_y + local_50 * 0x10 + local_54 * 0x40),
               *(i32 *)(&throneroom_piece_rect_w + local_50 * 0x10 + local_54 * 0x40),
               *(i32 *)(&throneroom_piece_rect_h + local_50 * 0x10 + local_54 * 0x40));
    sprite_replace_color(&local_4c,7,9);
    sprite_draw
              (&local_4c,(iptr)local_d8,(iptr)this->pad_504,
               *(int *)(&throneroom_piece3_rect_x + local_50 * 0x10) - 1,
               *(int *)(&throneroom_piece3_rect_y + local_50 * 0x10) - 1);
  }
  win_flush_pending_msgs();
  if (this->throne_complete != 0) {
    for (local_54 = 1; local_54 < 3; local_54++) {
      if ((1 << ((byte)local_54 & 0x1f) & (uint)civs[this->throne_civ].throne_room[8]) != 0) {
        iVar1 = surface_load_gif_resource(&local_9c,local_54 + 0xa0,10,0xec,(iptr)&this->control_list)
        ;
        if (iVar1 == 0) {
          local_dc = 0;
          local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
          /* inlined unwind funclet 0044e762 */ { sprite_destroy((Sprite *)((iptr)&local_4c)); }
          local_8 = 0xffffffff;
          /* inlined unwind funclet 0044e76b */ { surface_dtor((DibSurface *)((iptr)&local_9c)); }
          local_a0 = local_dc;
          goto LAB_0044e781;
        }
        sprite_grab_from_surface
                  (&local_4c,(iptr)&local_9c,9,(&throneroom_bonus_rect_x)[local_54 * 4],
                   (&throneroom_bonus_rect_y)[local_54 * 4],(&throneroom_bonus_rect_w)[local_54 * 4],
                   (&throneroom_bonus_rect_h)[local_54 * 4]);
        sprite_replace_color(&local_4c,7,9);
        sprite_draw
                  (&local_4c,(iptr)local_ec,(iptr)this->pad_504,(&throneroom_bonus_rect_x)[local_54 * 4] - 1,
                   (&throneroom_bonus_rect_y)[local_54 * 4] - 1);
      }
    }
  }
  win_flush_pending_msgs();
  if (civs[this->throne_civ].throne_room[4] != '\0') {
    local_50 = civs[this->throne_civ].throne_room[4] - 1;
    iVar1 = surface_load_gif_resource
                      (&local_9c,civs[this->throne_civ].throne_room[4] + 0x7c,10,0xec,
                       (iptr)&this->control_list);
    if (iVar1 == 0) {
      local_f0 = 0;
      local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
      /* inlined unwind funclet 0044e762 */ { sprite_destroy((Sprite *)((iptr)&local_4c)); }
      local_8 = 0xffffffff;
      /* inlined unwind funclet 0044e76b */ { surface_dtor((DibSurface *)((iptr)&local_9c)); }
      local_a0 = local_f0;
      goto LAB_0044e781;
    }
    sprite_grab_from_surface
              (&local_4c,(iptr)&local_9c,9,*(i32 *)(&throneroom_piece4_rect_x + local_50 * 0x10),
               *(i32 *)(&throneroom_piece4_rect_y + local_50 * 0x10),
               *(i32 *)(&throneroom_piece4_rect_w + local_50 * 0x10),
               *(i32 *)(&throneroom_piece4_rect_h + local_50 * 0x10));
    sprite_replace_color(&local_4c,7,9);
    sprite_draw
              (&local_4c,(iptr)local_100,(iptr)this->pad_504,
               *(int *)(&throneroom_piece4_rect_x + local_50 * 0x10) - 1,
               *(int *)(&throneroom_piece4_rect_y + local_50 * 0x10) - 1);
  }
  win_flush_pending_msgs();
  if ((this->throne_complete != 0) && ((civs[this->throne_civ].throne_room[8] & 8) != 0)) {
    iVar1 = surface_load_gif_resource(&local_9c,0xa3,10,0xec,(iptr)&this->control_list);
    if (iVar1 == 0) {
      local_104 = 0;
      local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
      /* inlined unwind funclet 0044e762 */ { sprite_destroy((Sprite *)((iptr)&local_4c)); }
      local_8 = 0xffffffff;
      /* inlined unwind funclet 0044e76b */ { surface_dtor((DibSurface *)((iptr)&local_9c)); }
      local_a0 = local_104;
      goto LAB_0044e781;
    }
    sprite_grab_from_surface
              (&local_4c,(iptr)&local_9c,9,throneroom_bonus3_rect_x,throneroom_bonus3_rect_y,throneroom_bonus3_rect_w,throneroom_bonus3_rect_h);
    sprite_replace_color(&local_4c,7,9);
    sprite_draw
              (&local_4c,(iptr)local_114,(iptr)this->pad_504,throneroom_bonus3_rect_x - 1,throneroom_bonus3_rect_y - 1);
  }
  win_flush_pending_msgs();
  for (local_54 = 5; local_54 < 7; local_54++) {
    if (*(char *)&civs[(this->throne_civ)].throne_room[local_54] != '\0') {
      local_50 = civs[(this->throne_civ)].throne_room[local_54] - 1;
      iVar1 = surface_load_gif_resource
                        (&local_9c,local_54 * 5 + local_50 + 0x69,10,0xec,(iptr)&this->control_list);
      if (iVar1 == 0) {
        local_118 = 0;
        local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
        /* inlined unwind funclet 0044e762 */ { sprite_destroy((Sprite *)((iptr)&local_4c)); }
        local_8 = 0xffffffff;
        /* inlined unwind funclet 0044e76b */ { surface_dtor((DibSurface *)((iptr)&local_9c)); }
        local_a0 = local_118;
        goto LAB_0044e781;
      }
      sprite_grab_from_surface
                (&local_4c,(iptr)&local_9c,9,
                 *(i32 *)(&throneroom_piece_rect_x + local_50 * 0x10 + local_54 * 0x40),
                 *(i32 *)(&throneroom_piece_rect_y + local_50 * 0x10 + local_54 * 0x40),
                 *(i32 *)(&throneroom_piece_rect_w + local_50 * 0x10 + local_54 * 0x40),
                 *(i32 *)(&throneroom_piece_rect_h + local_50 * 0x10 + local_54 * 0x40));
      sprite_replace_color(&local_4c,7,9);
      sprite_draw
                (&local_4c,(iptr)local_128,(iptr)this->pad_504,
                 *(int *)(&throneroom_piece_rect_x + local_50 * 0x10 + local_54 * 0x40) - 1,
                 *(int *)(&throneroom_piece_rect_y + local_50 * 0x10 + local_54 * 0x40) - 1);
    }
  }
  win_flush_pending_msgs();
  if (this->throne_complete != 0) {
    for (local_54 = 4; local_54 < 7; local_54++) {
      if ((1 << ((byte)local_54 & 0x1f) & (uint)civs[this->throne_civ].throne_room[8]) != 0) {
        iVar1 = surface_load_gif_resource(&local_9c,local_54 + 0xa0,10,0xec,(iptr)&this->control_list)
        ;
        if (iVar1 == 0) {
          local_12c = 0;
          local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
          /* inlined unwind funclet 0044e762 */ { sprite_destroy((Sprite *)((iptr)&local_4c)); }
          local_8 = 0xffffffff;
          /* inlined unwind funclet 0044e76b */ { surface_dtor((DibSurface *)((iptr)&local_9c)); }
          local_a0 = local_12c;
          goto LAB_0044e781;
        }
        sprite_grab_from_surface
                  (&local_4c,(iptr)&local_9c,9,(&throneroom_bonus_rect_x)[local_54 * 4],
                   (&throneroom_bonus_rect_y)[local_54 * 4],(&throneroom_bonus_rect_w)[local_54 * 4],
                   (&throneroom_bonus_rect_h)[local_54 * 4]);
        sprite_replace_color(&local_4c,7,9);
        sprite_draw
                  (&local_4c,(iptr)local_13c,(iptr)this->pad_504,(&throneroom_bonus_rect_x)[local_54 * 4] - 1,
                   (&throneroom_bonus_rect_y)[local_54 * 4] - 1);
      }
    }
  }
  win_flush_pending_msgs();
  if (civs[this->throne_civ].throne_room[7] != '\0') {
    local_50 = civs[this->throne_civ].throne_room[7] - 1;
    iVar1 = surface_load_gif_resource
                      (&local_9c,civs[this->throne_civ].throne_room[7] + 0x8b,10,0xec,
                       (iptr)&this->control_list);
    if (iVar1 == 0) {
      local_140 = 0;
      local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
      /* inlined unwind funclet 0044e762 */ { sprite_destroy((Sprite *)((iptr)&local_4c)); }
      local_8 = 0xffffffff;
      /* inlined unwind funclet 0044e76b */ { surface_dtor((DibSurface *)((iptr)&local_9c)); }
      local_a0 = local_140;
      goto LAB_0044e781;
    }
    sprite_grab_from_surface
              (&local_4c,(iptr)&local_9c,9,*(i32 *)(&throneroom_piece7_rect_x + local_50 * 0x10),
               *(i32 *)(&throneroom_piece7_rect_y + local_50 * 0x10),
               *(i32 *)(&throneroom_piece7_rect_w + local_50 * 0x10),
               *(i32 *)(&throneroom_piece7_rect_h + local_50 * 0x10));
    sprite_replace_color(&local_4c,7,9);
    sprite_draw
              (&local_4c,(iptr)local_150,(iptr)this->pad_504,
               *(int *)(&throneroom_piece7_rect_x + local_50 * 0x10) - 1,
               *(int *)(&throneroom_piece7_rect_y + local_50 * 0x10) - 1);
  }
  win_flush_pending_msgs();
  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
  /* inlined unwind funclet 0044e762 */ { sprite_destroy((Sprite *)((iptr)&local_4c)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet 0044e76b */ { surface_dtor((DibSurface *)((iptr)&local_9c)); }
  local_a0 = 1;
LAB_0044e781:
  return local_a0;
}
#undef local_150
#undef local_140
#undef local_13c
#undef local_12c
#undef local_128
#undef local_118
#undef local_114
#undef local_104
#undef local_100
#undef local_f0
#undef local_ec
#undef local_dc
#undef local_d8
#undef local_c8
#undef local_c4
#undef local_b4
#undef local_b0
#undef local_a0
#undef local_9c
#undef local_54
#undef local_50
#undef local_4c
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0044e790 auto */
#define local_460 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_450 (*(i32 *)(frame_ + FRAME_OFF(16)))
#define local_44c (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
#define local_43c (*(i32 *)(frame_ + FRAME_OFF(36)))
#define local_438 (*(i32 *)(frame_ + FRAME_OFF(40)))
#define local_434 (*(DibSurface *)(frame_ + FRAME_OFF(44)))
#define local_3ec (*(i32 (*)[34])(frame_ + FRAME_OFF(116)))
#define local_364 (*(iptr *)(frame_ + FRAME_OFF(252)))
#define local_360 (*(int (*)[60])(frame_ + FRAME_OFF(256)))
#define local_270 (*(Sprite *)(frame_ + FRAME_OFF(496)))
#define local_234 (*(i32 (*)[136])(frame_ + FRAME_OFF(556)))
#define local_14 (*(byte *)(frame_ + FRAME_OFF(1100)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1104)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1108)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(1112)))
i32 __thiscall throneroom_render_choices(ThroneRoomWindow *this)

{
  int iVar1;
  i8 frame_[FRAME_OFF(1120)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  surface_ctor(&local_434);
  local_8 = 0;
  sprite_init(&local_270);
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),1);
  local_360[0] = 0xd4;
  local_360[1] = 1;
  local_360[2] = 0xb3;
  local_360[3] = 0x127;
  local_360[4] = 0x13;
  local_360[5] = 0x11b;
  local_360[6] = 0x24f;
  local_360[7] = 0xc6;
  local_360[8] = 0xc6;
  local_360[9] = 0x12f;
  local_360[10] = 0xd7;
  local_360[0xb] = 0xb1;
  local_360[0xc] = 0xb;
  local_360[0xd] = 1;
  local_360[0xe] = 0x25f;
  local_360[0xf] = 0x11e;
  local_360[0x10] = 0xbc;
  local_360[0x11] = 0x12;
  local_360[0x12] = 0xe6;
  local_360[0x13] = 0x11b;
  local_360[0x14] = 1;
  local_360[0x15] = 1;
  local_360[0x16] = 0x260;
  local_360[0x17] = 0x137;
  local_360[0x18] = 0x11c;
  local_360[0x19] = 0x102;
  local_360[0x1a] = 0x27;
  local_360[0x1b] = 0x39;
  local_360[0x1c] = 1;
  local_360[0x1d] = 1;
  local_360[0x1e] = 0x280;
  local_360[0x1f] = 0x1e0;
  local_360[0x20] = 0x14;
  local_360[0x21] = 0x13a;
  local_360[0x22] = 0x24f;
  local_360[0x23] = 0x28;
  local_360[0x24] = 0x5f;
  local_360[0x25] = 0x6d;
  local_360[0x26] = 0x1a3;
  local_360[0x27] = 0x5f;
  local_360[0x28] = 0x12;
  local_360[0x29] = 0x103;
  local_360[0x2a] = 0x252;
  local_360[0x2b] = 0x2d;
  local_360[0x2c] = 0xde;
  local_360[0x2d] = 0xd4;
  local_360[0x2e] = 0xa2;
  local_360[0x2f] = 0x54;
  local_360[0x30] = 0x7b;
  local_360[0x31] = 0x125;
  local_360[0x32] = 0x162;
  local_360[0x33] = 0x23;
  local_360[0x34] = 0x48;
  local_360[0x35] = 0x125;
  local_360[0x36] = 0x1c8;
  local_360[0x37] = 0x27;
  local_360[0x38] = 0x16;
  local_360[0x39] = 0x16e;
  local_360[0x3a] = 0x249;
  local_360[0x3b] = 0x47;
  local_234[0] = 1;
  local_234[1] = 2;
  local_234[2] = 0x16;
  local_234[3] = 0x19c;
  local_234[4] = 2;
  local_234[5] = 0x194;
  local_234[6] = 0x36;
  local_234[7] = 0x48;
  local_234[8] = 0x25c;
  local_234[9] = 1;
  local_234[10] = 0x23;
  local_234[0xb] = 0x197;
  local_234[0xc] = 0x23c;
  local_234[0xd] = 0x195;
  local_234[0xe] = 0x44;
  local_234[0xf] = 0x49;
  local_234[0x10] = 0x21d;
  local_234[0x11] = 0x16d;
  local_234[0x12] = 0x41;
  local_234[0x13] = 0x46;
  local_234[0x14] = 0x1c;
  local_234[0x15] = 0x16e;
  local_234[0x16] = 0x47;
  local_234[0x17] = 0x44;
  local_234[0x18] = 0x47;
  local_234[0x19] = 0x124;
  local_234[0x1a] = 100;
  local_234[0x1b] = 0x27;
  local_234[0x1c] = 0x1ad;
  local_234[0x1d] = 0x124;
  local_234[0x1e] = 99;
  local_234[0x1f] = 0x27;
  local_234[0x20] = 0x47;
  local_234[0x21] = 0x124;
  local_234[0x22] = 100;
  local_234[0x23] = 0x27;
  local_234[0x24] = 0x1ad;
  local_234[0x25] = 0x124;
  local_234[0x26] = 99;
  local_234[0x27] = 0x27;
  local_234[0x28] = 0x11c;
  local_234[0x29] = 0x102;
  local_234[0x2a] = 0x27;
  local_234[0x2b] = 0x39;
  local_234[0x2c] = 0x25;
  local_234[0x2d] = 0x12;
  local_234[0x2e] = 0x2d;
  local_234[0x2f] = 0x120;
  local_234[0x30] = 0x93;
  local_234[0x31] = 0x12;
  local_234[0x32] = 0x2c;
  local_234[0x33] = 0x124;
  local_234[0x34] = 0x19d;
  local_234[0x35] = 0x14;
  local_234[0x36] = 0x31;
  local_234[0x37] = 0x121;
  local_234[0x38] = 0x20b;
  local_234[0x39] = 0x14;
  local_234[0x3a] = 0x2f;
  local_234[0x3b] = 0x11e;
  local_234[0x3c] = 0xe;
  local_234[0x3d] = 3;
  local_234[0x3e] = 0xcf;
  local_234[0x3f] = 0xc;
  local_234[0x40] = 0x17f;
  local_234[0x41] = 1;
  local_234[0x42] = 0xd3;
  local_234[0x43] = 0xe;
  local_234[0x44] = 0xe3;
  local_234[0x45] = 0xd4;
  local_234[0x46] = 0xe;
  local_234[0x47] = 0x51;
  local_234[0x48] = 0x16f;
  local_234[0x49] = 0xd5;
  local_234[0x4a] = 0xb;
  local_234[0x4b] = 0x52;
  local_234[0x4c] = 0xbe;
  local_234[0x4d] = 0x11;
  local_234[0x4e] = 0x15;
  local_234[0x4f] = 0x11a;
  local_234[0x50] = 0x185;
  local_234[0x51] = 0x12;
  local_234[0x52] = 0x1a;
  local_234[0x53] = 0x119;
  local_234[0x54] = 0xde;
  local_234[0x55] = 0x24;
  local_234[0x56] = 0x96;
  local_234[0x57] = 0x55;
  local_234[0x58] = 0x11;
  local_234[0x59] = 0x114;
  local_234[0x5a] = 0xc1;
  local_234[0x5b] = 0x19;
  local_234[0x5c] = 400;
  local_234[0x5d] = 0x107;
  local_234[0x5e] = 0xd0;
  local_234[0x5f] = 0x26;
  local_234[0x60] = 0x5e;
  local_234[0x61] = 0x75;
  local_234[0x62] = 0x36;
  local_234[99] = 0x47;
  local_234[100] = 0x10b;
  local_234[0x65] = 0x6c;
  local_234[0x66] = 0x46;
  local_234[0x67] = 0x5e;
  local_234[0x68] = 0x1cc;
  local_234[0x69] = 0x75;
  local_234[0x6a] = 0x33;
  local_234[0x6b] = 0x49;
  local_234[0x6c] = 0xb;
  local_234[0x6d] = 2;
  local_234[0x6e] = 0x93;
  local_234[0x6f] = 0x11b;
  local_234[0x70] = 0x1c2;
  local_234[0x71] = 2;
  local_234[0x72] = 0xa7;
  local_234[0x73] = 0x11b;
  local_234[0x74] = 0x14;
  local_234[0x75] = 0x13c;
  local_234[0x76] = 0xb8;
  local_234[0x77] = 0x22;
  local_234[0x78] = 0x193;
  local_234[0x79] = 0x13d;
  local_234[0x7a] = 0xcc;
  local_234[0x7b] = 0x23;
  local_234[0x7c] = 0xde;
  local_234[0x7d] = 0x12f;
  local_234[0x7e] = 0xa8;
  local_234[0x7f] = 0xaf;
  local_234[0x80] = 0x13;
  local_234[0x81] = 0x123;
  local_234[0x82] = 0x250;
  local_234[0x83] = 0xbd;
  local_234[0x84] = 0xd4;
  local_234[0x85] = 1;
  local_234[0x86] = 0xb3;
  local_234[0x87] = 0x127;
  local_3ec[0] = 7;
  local_3ec[1] = 7;
  local_3ec[2] = 7;
  local_3ec[3] = 7;
  local_3ec[4] = 0x10;
  local_3ec[5] = 0x10;
  local_3ec[6] = 0xf;
  local_3ec[7] = 0xf;
  local_3ec[8] = 0xe;
  local_3ec[9] = 0xe;
  local_3ec[10] = 6;
  local_3ec[0xb] = 5;
  local_3ec[0xc] = 5;
  local_3ec[0xd] = 5;
  local_3ec[0xe] = 5;
  local_3ec[0xf] = 5;
  local_3ec[0x10] = 5;
  local_3ec[0x11] = 0xd;
  local_3ec[0x12] = 0xd;
  local_3ec[0x13] = 4;
  local_3ec[0x14] = 4;
  local_3ec[0x15] = 4;
  local_3ec[0x16] = 0xc;
  local_3ec[0x17] = 0xc;
  local_3ec[0x18] = 0xb;
  local_3ec[0x19] = 0xb;
  local_3ec[0x1a] = 0xb;
  local_3ec[0x1b] = 3;
  local_3ec[0x1c] = 3;
  local_3ec[0x1d] = 10;
  local_3ec[0x1e] = 10;
  local_3ec[0x1f] = 2;
  local_3ec[0x20] = 1;
  local_3ec[0x21] = 0;
  clickmap_clear((ClickMapClearView *)(this->pad_638 + 0x28));
  for (local_364 = 0; local_364 < 0x22; local_364++) {
    clickmap_add
              ((ClickMap *)(this->pad_638 + 0x28),local_364,local_3ec[local_364],
               local_234[local_364 * 4],local_234[local_364 * 4 + 1],local_234[local_364 * 4 + 2],
               local_234[local_364 * 4 + 3]);
  }
  iVar1 = surface_load_gif_resource
                    ((DibSurface *)this->pad_504,100,10,0xec,(iptr)&this->control_list);
  if (iVar1 == 0) {
    local_438 = 0;
    local_8 = local_8 & 0xffffff00;
    /* inlined unwind funclet 0044f498 */ { sprite_destroy((Sprite *)((iptr)&local_270)); }
    local_8 = 0xffffffff;
    /* inlined unwind funclet 0044f4a4 */ { surface_dtor((DibSurface *)((iptr)&local_434)); }
  }
  else {
    if (this->throne_complete == 0) {
      for (local_364 = 0; local_364 < 8; local_364++) {
        win_flush_pending_msgs();
        if (civs[(this->throne_civ)].throne_room[local_364] < 4) {
          iVar1 = surface_load_gif_resource
                            (&local_434,local_364 + 0xaa,10,0xec,(iptr)&this->control_list);
          if (iVar1 == 0) {
            local_43c = 0;
            local_8 = local_8 & 0xffffff00;
            /* inlined unwind funclet 0044f498 */ { sprite_destroy((Sprite *)((iptr)&local_270)); }
            local_8 = 0xffffffff;
            /* inlined unwind funclet 0044f4a4 */ { surface_dtor((DibSurface *)((iptr)&local_434)); }
            local_438 = local_43c;
            goto LAB_0044f4ba;
          }
          sprite_grab_from_surface
                    (&local_270,(iptr)&local_434,9,local_360[local_364 * 4],
                     local_360[local_364 * 4 + 1],local_360[local_364 * 4 + 2],
                     local_360[local_364 * 4 + 3]);
          sprite_replace_color(&local_270,7,9);
          sprite_draw
                    (&local_270,(iptr)local_44c,(iptr)this->pad_504,local_360[local_364 * 4] - 1,
                     local_360[local_364 * 4 + 1] - 1);
        }
      }
    }
    else {
      local_14 = civs[this->throne_civ].throne_room[8];
      for (local_364 = 0; local_364 < 7; local_364++) {
        win_flush_pending_msgs();
        if ((1 << ((byte)local_364 & 0x1f) & (uint)local_14) == 0) {
          iVar1 = surface_load_gif_resource
                            (&local_434,local_364 + 0xb2,10,0xec,(iptr)&this->control_list);
          if (iVar1 == 0) {
            local_450 = 0;
            local_8 = local_8 & 0xffffff00;
            /* inlined unwind funclet 0044f498 */ { sprite_destroy((Sprite *)((iptr)&local_270)); }
            local_8 = 0xffffffff;
            /* inlined unwind funclet 0044f4a4 */ { surface_dtor((DibSurface *)((iptr)&local_434)); }
            local_438 = local_450;
            goto LAB_0044f4ba;
          }
          sprite_grab_from_surface
                    (&local_270,(iptr)&local_434,9,local_360[local_364 * 4 + 0x20],
                     local_360[local_364 * 4 + 0x21],local_360[local_364 * 4 + 0x22],
                     local_360[local_364 * 4 + 0x23]);
          sprite_replace_color(&local_270,7,9);
          sprite_draw
                    (&local_270,(iptr)local_460,(iptr)this->pad_504,
                     local_360[local_364 * 4 + 0x20] - 1,local_360[local_364 * 4 + 0x21] - 1);
        }
      }
    }
    local_8 = local_8 & 0xffffff00;
    /* inlined unwind funclet 0044f498 */ { sprite_destroy((Sprite *)((iptr)&local_270)); }
    local_8 = 0xffffffff;
    /* inlined unwind funclet 0044f4a4 */ { surface_dtor((DibSurface *)((iptr)&local_434)); }
    local_438 = 1;
  }
LAB_0044f4ba:
  return local_438;
}
#undef local_460
#undef local_450
#undef local_44c
#undef local_43c
#undef local_438
#undef local_434
#undef local_3ec
#undef local_364
#undef local_360
#undef local_270
#undef local_234
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0044f4c9 auto */
#define local_10 (*(i8 (*)[4])(frame_ + FRAME_OFF(0)))
#define local_c (*(byte *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(8)))
void __cdecl throneroom_on_click(i32 param_1,i32 param_2)

{
  int iVar2;
  iptr civ;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = throneroom_wnd;
  civ = *(iptr *)(throneroom_wnd + 0x500);
  if (*(int *)(throneroom_wnd + 0x1924) == 0) {
    wnd_end_modal_loop((ModalMenuWindow *)(throneroom_wnd + 0x54c));
  }
  else {
    iVar2 = clickmap_hit_test
                      ((ClickMapHitTestView *)(throneroom_wnd + 0x660),param_1,param_2,(iptr)local_10,
                       throneroom_wnd + 0x192c);
    if (iVar2 < 0) {
      *(i32 *)(local_8 + 0x192c) = 0;
      snd_play_effect(0x5e,1,0,0);
    }
    else {
      if (*(int *)(local_8 + 0x1928) == 0) {
        if (9 < *(int *)(local_8 + 0x192c)) {
          snd_play_effect(0x5e,1,0,0);
          return;
        }
        if (3 < civs[civ].throne_room[(*(int *)(local_8 + 0x192c))]) {
          snd_play_effect(0x5e,1,0,0);
          return;
        }
      }
      else {
        if (*(int *)(local_8 + 0x192c) < 10) {
          snd_play_effect(0x5e,1,0,0);
          return;
        }
        *(int *)(local_8 + 0x192c) = *(int *)(local_8 + 0x192c) - 10;
        local_c = civs[civ].throne_room[8];
        if ((*(int *)(local_8 + 0x192c) == 4) || (*(int *)(local_8 + 0x192c) == 5)) {
          if (((local_c & 0x10) != 0) && ((local_c & 0x20) != 0)) {
            snd_play_effect(0x5e,1,0,0);
            return;
          }
          if (*(int *)(local_8 + 0x192c) == 4) {
            if ((local_c & 0x10) != 0) {
              *(i32 *)(local_8 + 0x192c) = 5;
            }
          }
          else if ((local_c & 0x20) != 0) {
            *(i32 *)(local_8 + 0x192c) = 4;
          }
        }
        if ((1 << (*(byte *)(local_8 + 0x192c) & 0x1f) & (uint)civs[civ].throne_room[8]) != 0) {
          snd_play_effect(0x5e,1,0,0);
          return;
        }
      }
      wnd_end_modal_loop((ModalMenuWindow *)(local_8 + 0x54c));
    }
  }
  return;
}
#undef local_10
#undef local_c
#undef local_8

/* 0044f717 auto */
void __cdecl throneroom_on_key(int param_1)

{
  if (*(int *)(throneroom_wnd + 0x1924) == 0) {
    if ((0xcf < param_1) && (param_1 < 0xd3)) {
      wnd_end_modal_loop((ModalMenuWindow *)(throneroom_wnd + 0x54c));
    }
  }
  else {
    snd_play_effect(0x5e,1,0,0);
  }
  return;
}

/* 0044f799 auto */
void __cdecl throneroom_close(void)

{
  if ((throneroom_wnd != 0) && (*(int *)(throneroom_wnd + 0x1924) == 0)) {
    wnd_end_modal_loop((ModalMenuWindow *)(throneroom_wnd + 0x54c));
  }
  return;
}

/* 004702e0 auto */
#define endgame_movie_window (*(SpaceshipWindow * *)((u8 *)&g.d_0062b804))
#define local_18 (*(SpaceshipWindow * *)(frame_ + FRAME_OFF(0)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(8)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(16)))
void __cdecl endgame_defeat_movie(iptr param_1)

{
  SpaceshipWindow *this;
  int iVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  this = operator_new(0x137c);
  local_8 = 0;
  if (this == (SpaceshipWindow *)0x0) {
    local_18 = (SpaceshipWindow *)0x0;
  }
  else {
    local_18 = (SpaceshipWindow *)defeat_movie_wnd_ctor(this);
  }
  local_8 = 0xffffffff;
  endgame_movie_window = local_18;
  if (local_18 != (SpaceshipWindow *)0x0) {
    iVar1 = defeat_movie_wnd_create(local_18,param_1);
    if (iVar1 != 0) {
      defeat_movie_wnd_play(endgame_movie_window);
    }
    if (endgame_movie_window != (SpaceshipWindow *)0x0) {
      defeat_movie_wnd_scalar_dtor((WndBase *)endgame_movie_window,1);
    }
    endgame_movie_window = (SpaceshipWindow *)0x0;
  }
  return;
}
#undef endgame_movie_window
#undef local_18
#undef local_10
#undef puStack_c
#undef local_8

/* 004703d4 auto */
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
SpaceshipWindow * __thiscall defeat_movie_wnd_ctor(SpaceshipWindow *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  wnd_ctor((ModalMenuWindow *)this);
  local_8 = 0;
  palette_init((GamePalette *)&this->control_list);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  mmwnd_ctor((DocumentWindow *)(this->pad_1e4 + 0x308));
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  dll_handle_init((DllHandle *)(this->pad_ae4 + 0x430));
  (*(i8 *)((char *)&local_8 + 0)) = 3;
  font_init_empty((GameFont *)this->pad_f1c);
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),4);
  surface_ctor((DibSurface *)(this[1].pad_1e4 + 0x188));
  this->advance_civ = 0;
  return this;
}
#undef local_10
#undef puStack_c
#undef local_8

/* 004704ec auto */
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __thiscall defeat_movie_wnd_dtor(void *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  (*(i32 *)((char *)&local_8 + 1)) = 0;
  (*(i8 *)((char *)&local_8 + 0)) = 4;
  /* inlined unwind funclet 0047056b */ { surface_dtor((DibSurface *)(*(int *)((iptr)&this) + 0x1324)); }
  (*(i8 *)((char *)&local_8 + 0)) = 3;
  /* inlined unwind funclet 0047057a */ { font_destroy((GameFont *)(*(int *)((iptr)&this) + 0xf1c)); }
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  /* inlined unwind funclet 00470589 */ { dll_free((DllHandle *)(*(int *)((iptr)&this) + 0xf14)); }
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  /* inlined unwind funclet 00470598 */ { avi_player_dtor((AviPlayer *)(*(int *)((iptr)&this) + 0x4ec)); }
  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
  /* inlined unwind funclet 004705a7 */ { palette_destroy((GamePalette *)(*(int *)((iptr)&this) + 0xb8)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet 004705b6 */ { wnd_dtor(*(WndBase **)((iptr)&this)); }
  return;
}
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004705d7 auto */
#define local_1a0 (*(CHAR (*)[128])(frame_ + FRAME_OFF(0)))
#define local_120 (*(_OFSTRUCT *)(frame_ + FRAME_OFF(128)))
#define local_98 (*(int *)(frame_ + FRAME_OFF(264)))
#define local_94 (*(int *)(frame_ + FRAME_OFF(268)))
#define local_90 (*(int *)(frame_ + FRAME_OFF(272)))
#define local_8c (*(int *)(frame_ + FRAME_OFF(276)))
#define local_88 (*(int *)(frame_ + FRAME_OFF(280)))
#define local_84 (*(CHAR (*)[128])(frame_ + FRAME_OFF(284)))
i32 __thiscall defeat_movie_wnd_create(SpaceshipWindow *this,uint param_1)

{
  HFILE HVar1;
  i32 uVar2;
  i32 uVar3;
  i8 frame_[FRAME_OFF(416)] __attribute__((aligned(8)));  /* original stack frame */
  
  gfx_get_screen_rect((iptr)&local_98);
  str_clear((iptr)local_84);
  str_append((iptr)local_84,ADDR(0x655020, ((u8 *)&g.d_00655020)));
  str_append((iptr)local_84,ADDR(0x62b808, ((u8 *)&g.d_0062b808)));
  HVar1 = OpenFile(local_84,&local_120,0x4000);
  if (HVar1 == -1) {
    uVar2 = 0;
  }
  else {
    str_clear((iptr)local_1a0);
    str_append((iptr)local_1a0,ADDR(0x655020, ((u8 *)&g.d_00655020)));
    str_append((iptr)local_1a0,ADDR(0x62b814, ((u8 *)&g.d_0062b814)));
    HVar1 = OpenFile(local_1a0,&local_120,0x4000);
    if (HVar1 == -1) {
      uVar2 = 0;
    }
    else {
      dll_handle_load((DllHandle *)(this->pad_ae4 + 0x430),(iptr)local_1a0);
      if ((int)param_1 < 1) {
        this->advance_civ = ~param_1 + 1;
      }
      else {
        this->advance_civ = param_1;
      }
      wnd_create_with_handlers
                ((WndBase *)this,ADDR(0x62b824, ((u8 *)&g.d_0062b824)),0x800,local_98,local_94,local_90 - local_98,
                 (local_8c - local_94) + 5,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)),ADDR(0x6553d8, ((u8 *)&g.d_006553d8)));
      wnd_set_bg_color((WndBase *)this,0);
      surface_load_gif_resource
                ((DibSurface *)(this->pad_1e4 + 0x308),4000,10,0xec,(iptr)&this->control_list);
      avi_player_create((MediaWindow *)(this->pad_1e4 + 0x308),ADDR(0x62b828, ((u8 *)&g.d_0062b828)),0x800,0,0);
      avi_player_set_double_size((MediaWindow *)(this->pad_1e4 + 0x308),1);
      local_88 = avi_player_open((AviPlayerOpenView *)(this->pad_1e4 + 0x308),(iptr)local_84);
      if (local_88 == 0) {
        surface_fill((DibSurface *)(this->pad_1e4 + 0x308),0);
        wnd_center((WndCenterView *)(this->pad_504 + 0x30));
        avi_player_set_end_callback((AviPlayerEndCbSetView *)(this->pad_1e4 + 0x308),ADDR(0x402630, defeat_movie_on_video_end));
        SetRect((LPRECT)(this[1].pad_1e4 + 0x1d0),0x28,100,600,0x1e0);
        uVar2 = surface_get_height((DibSurface *)(this->pad_1e4 + 0x308));
        uVar3 = surface_get_width((DibSurface *)(this->pad_1e4 + 0x308));
        surface_create((DibSurface *)(this[1].pad_1e4 + 0x188),uVar3,uVar2);
        avi_player_draw_to
                  ((DibSurface *)(this->pad_1e4 + 0x308),(iptr)(this[1].pad_1e4 + 0x188),0,0);
        font_set_styled((GameFont *)this->pad_f1c,0,0x12,2);
        dll_handle_free((DllHandle *)(this->pad_ae4 + 0x430));
        uVar2 = 1;
      }
      else {
        if (local_88 == -0x7ffbfeac) {
          popup_game(ADDR(0x62b82c, ((u8 *)&g.d_0062b82c)));
        }
        uVar2 = 0;
      }
    }
  }
  return uVar2;
}
#undef local_1a0
#undef local_120
#undef local_98
#undef local_94
#undef local_90
#undef local_8c
#undef local_88
#undef local_84

/* 004708db auto */
#define text_line_cursor (*(iptr *)((u8 *)&g.d_00673f14))
#define advance (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __thiscall defeat_movie_wnd_play(SpaceshipWindow *this)

{
  int iVar1;
  iptr iVar2;
  char *pcVar3;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  music_play_track(2,1);
  wnd_handle_show_raise((WndBase *)this);
  wnd_flush_paint();
  wnd_set_palette((WndBase *)this,(iptr)&this->control_list);
  window_show((WindowObjectView *)(this->pad_1e4 + 0x308));
  wnd_flush_paint();
  wnd_set_capture((WndBase *)(this->pad_504 + 0x30));
  gfx_set_text_color_index(0xff);
  advance = 0;
  while ((advance < 100 && (iVar1 = civ_has_advance(this->advance_civ,advance), iVar1 == 0))) {
    advance++;
  }
  iVar2 = label_string(advances[advance].name);
  text_set_string_arg(0,iVar2);
  CharLowerA(&text_string_args);
  iVar2 = civ_leader_name(this->advance_civ);
  text_set_string_arg(1,iVar2);
  for (local_8 = 0; local_8 < 3; local_8++) {
    str_clear((iptr)(this->pad_f1c + 8));
    text_clear();
    text_append(ADDR(0x62b840, ((u8 *)&g.d_0062b840)));
    text_append_int(local_8);
    iVar1 = text_open_section(ADDR(0x6558e8, ((u8 *)&g.d_006558e8)),ADDR(0x679640, ((u8 *)&g.d_00679640)));
    if (iVar1 == 0) {
      while (pcVar3 = (char *)text_read_line(1), *pcVar3 != '@') {
        str_append((iptr)(this->pad_f1c + 8),text_line_cursor);
        str_append((iptr)(this->pad_f1c + 8),ADDR(0x62b850, ((u8 *)&g.d_0062b850)));
      }
      text_clear();
      text_expand_vars((iptr)(this->pad_f1c + 8),ADDR(0x679640, ((u8 *)&g.d_00679640)));
      surface_blit
                ((DibSurface *)(this[1].pad_1e4 + 0x188),(iptr)(this->pad_1e4 + 0x308),
                 (iptr)(this[1].pad_1e4 + 0x1d0),(iptr)(this[1].pad_1e4 + 0x1d0));
      OffsetRect((LPRECT)(this[1].pad_1e4 + 0x1d0),1,1);
      gfx_set_text_color_index(0);
      surface_draw_text_rect
                ((DibSurface *)(this->pad_1e4 + 0x308),(iptr)this->pad_f1c,ADDR(0x679640, ((u8 *)&g.d_00679640)),
                 (iptr)(this[1].pad_1e4 + 0x1d0),0);
      OffsetRect((LPRECT)(this[1].pad_1e4 + 0x1d0),-1,-1);
      gfx_set_text_color_index(0xff);
      surface_draw_text_rect
                ((DibSurface *)(this->pad_1e4 + 0x308),(iptr)this->pad_f1c,ADDR(0x679640, ((u8 *)&g.d_00679640)),
                 (iptr)(this[1].pad_1e4 + 0x1d0),0);
      gfx_dissolve_blit((iptr)(this->pad_1e4 + 0x308),(iptr)(this[1].pad_1e4 + 0x1d0),4,5);
      text_close_file();
      ui_delay_ticks(0x168);
    }
  }
  avi_player_play((AviPlayerPlayView *)(this->pad_1e4 + 0x308));
  if (2 < game.multiplayer) {
    wnd_set_modal_idle_callback((ModalMenuWindow *)(this->pad_504 + 0x30),ADDR(0x403585, net_modal_idle_poll));
  }
  wnd_run_modal_loop((ModalMenuWindow *)(this->pad_504 + 0x30));
  wnd_set_modal_idle_callback((ModalMenuWindow *)(this->pad_504 + 0x30),0);
  wnd_release_capture((WndBase *)(this->pad_504 + 0x30));
  wnd_hide((WndBase *)(this->pad_504 + 0x30));
  wnd_flush_paint();
  wnd_set_palette((WndBase *)&main_frame_wnd,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
  wnd_hide((WndBase *)this);
  wnd_flush_paint();
  return;
}
#undef text_line_cursor
#undef advance
#undef local_8

/* 00470c1c auto */
#define endgame_movie_window (*(int *)((u8 *)&g.d_0062b804))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define text_line_cursor (*(iptr *)((u8 *)&g.d_00673f14))
void __cdecl defeat_movie_on_video_end(void)

{
  int iVar1;
  char *pcVar2;
  
  str_clear(endgame_movie_window + 0xf24);
  text_clear();
  iVar1 = text_open_section(ADDR(0x6558e8, ((u8 *)&g.d_006558e8)),ADDR(0x62b854, ((u8 *)&g.d_0062b854)));
  if (iVar1 == 0) {
    while( true ) {
      pcVar2 = (char *)text_read_line(1);
      if (*pcVar2 == '@') break;
      str_append(endgame_movie_window + 0xf24,text_line_cursor);
      str_append(endgame_movie_window + 0xf24,ADDR(0x62b864, ((u8 *)&g.d_0062b864)));
    }
    text_expand_vars(endgame_movie_window + 0xf24,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    CharUpperA(&text_buffer);
    rect_set_xywh(endgame_movie_window + 0x136c,0xe5,0x4c,200,0x85);
    gfx_set_text_color_index(0);
    surface_draw_text_rect
              ((DibSurface *)(endgame_movie_window + 0x4ec),endgame_movie_window + 0xf1c,ADDR(0x679640, ((u8 *)&g.d_00679640)),
               endgame_movie_window + 0x136c,0);
    gfx_dissolve_blit(endgame_movie_window + 0x4ec,endgame_movie_window + 0x136c,4,5);
    text_close_file();
  }
  ui_delay_ticks(0x168);
  wnd_end_modal_loop((ModalMenuWindow *)(endgame_movie_window + 0x534));
  return;
}
#undef endgame_movie_window
#undef text_buffer
#undef text_line_cursor

/* 00471020 auto */
WndBase * __thiscall defeat_movie_wnd_scalar_dtor(WndBase *this,uint param_1)

{
  defeat_movie_wnd_dtor(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 004710d0 auto */
#define local_30c (*(SpaceshipWindow * *)(frame_ + FRAME_OFF(4)))
#define local_304 (*(Dialog *)(frame_ + FRAME_OFF(12)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(768)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(772)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(776)))
void __cdecl endgame_spaceship_arrival(iptr civ)

{
  SpaceshipWindow *this;
  int iVar1;
  iptr iVar2;
  i8 frame_[FRAME_OFF(784)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  if (civ < 0) {
    endgame_show_centauri_beaten(civ);
  }
  else {
    snd_cd_stop();
    this = operator_new(0x137c);
    local_8 = 0;
    if (this == (SpaceshipWindow *)0x0) {
      local_30c = (SpaceshipWindow *)0x0;
    }
    else {
      local_30c = (SpaceshipWindow *)arrival_movie_wnd_ctor(this);
    }
    local_8 = 0xffffffff;
    spaceship_arrival_window = (iptr)local_30c;
    if (local_30c != (SpaceshipWindow *)0x0) {
      iVar1 = arrival_movie_wnd_create(local_30c,civ);
      if (iVar1 == 0) {
        text_clear();
        text_append_year((int)civs[civ].spaceship_launch_year);
        text_set_string_arg(0,ADDR(0x679640, ((u8 *)&g.d_00679640)));
        text_clear();
        text_append_int((int)civs[civ].spaceship_population);
        text_append(ADDR(0x62b880, ((u8 *)&g.d_0062b880)));
        text_set_string_arg(1,ADDR(0x679640, ((u8 *)&g.d_00679640)));
        iVar2 = civ_get_adjective(civ);
        text_set_string_arg(2,iVar2);
        text_clear();
        text_append_year((int)civs[civ].spaceship_arrival_year);
        text_set_number_arg(3,(int)civs[civ].spaceship_arrival_year);
        iVar2 = civ_leader_name(civ);
        text_set_string_arg(4,iVar2);
        dialog_ctor(&local_304,0x4000);
        local_8 = 1;
        dialog_load_game_text(&local_304,ADDR(0x62b888, ((u8 *)&g.d_0062b888)));
        dialog_add_sprite((DialogOptionList *)&local_304,ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0,0);
        dlg_show_modal(&local_304,0);
        local_8 = 0xffffffff;
        /* inlined unwind funclet 0047132e */ { dialog_dtor((Dialog *)((iptr)&local_304)); }
      }
      else {
        arrival_movie_wnd_play((SpaceshipWindow *)spaceship_arrival_window);
      }
      if (spaceship_arrival_window != 0) {
        arrival_movie_wnd_scalar_dtor((void *)spaceship_arrival_window,1);
      }
      spaceship_arrival_window = 0;
    }
  }
  return;
}
#undef local_30c
#undef local_304
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00471362 auto */
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
SpaceshipWindow * __thiscall arrival_movie_wnd_ctor(SpaceshipWindow *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  wnd_ctor((ModalMenuWindow *)this);
  local_8 = 0;
  palette_init((GamePalette *)&this->control_list);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  mmwnd_ctor((DocumentWindow *)(this->pad_1e4 + 0x308));
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  dll_handle_init((DllHandle *)(this->pad_ae4 + 0x430));
  (*(i8 *)((char *)&local_8 + 0)) = 3;
  font_init_empty((GameFont *)this->pad_f1c);
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),4);
  surface_ctor((DibSurface *)(this[1].pad_1e4 + 0x188));
  this->advance_civ = 0;
  return this;
}
#undef local_10
#undef puStack_c
#undef local_8

/* 0047147a auto */
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __thiscall arrival_movie_wnd_dtor(void *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  (*(i32 *)((char *)&local_8 + 1)) = 0;
  (*(i8 *)((char *)&local_8 + 0)) = 4;
  /* inlined unwind funclet 004714f9 */ { surface_dtor((DibSurface *)(*(int *)((iptr)&this) + 0x1324)); }
  (*(i8 *)((char *)&local_8 + 0)) = 3;
  /* inlined unwind funclet 00471508 */ { font_destroy((GameFont *)(*(int *)((iptr)&this) + 0xf1c)); }
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  /* inlined unwind funclet 00471517 */ { dll_free((DllHandle *)(*(int *)((iptr)&this) + 0xf14)); }
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  /* inlined unwind funclet 00471526 */ { avi_player_dtor((AviPlayer *)(*(int *)((iptr)&this) + 0x4ec)); }
  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
  /* inlined unwind funclet 00471535 */ { palette_destroy((GamePalette *)(*(int *)((iptr)&this) + 0xb8)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet 00471544 */ { wnd_dtor(*(WndBase **)((iptr)&this)); }
  return;
}
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00471565 auto */
#define local_118 (*(i8 (*)[128])(frame_ + FRAME_OFF(0)))
#define local_98 (*(int *)(frame_ + FRAME_OFF(128)))
#define local_94 (*(int *)(frame_ + FRAME_OFF(132)))
#define local_90 (*(int *)(frame_ + FRAME_OFF(136)))
#define local_8c (*(int *)(frame_ + FRAME_OFF(140)))
#define local_88 (*(int *)(frame_ + FRAME_OFF(144)))
#define local_84 (*(i8 (*)[128])(frame_ + FRAME_OFF(148)))
i32 __thiscall arrival_movie_wnd_create(SpaceshipWindow *this,iptr param_1)

{
  int iVar1;
  i32 uVar2;
  i32 uVar3;
  i8 frame_[FRAME_OFF(280)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 < 1) {
    this->advance_civ = ~param_1 + 1;
  }
  else {
    this->advance_civ = param_1;
  }
  gfx_get_screen_rect((iptr)&local_98);
  file_require_cdrom(ADDR(0x62b894, ((u8 *)&g.d_0062b894)));
  str_clear((iptr)local_84);
  str_append((iptr)local_84,ADDR(0x62b8a4, ((u8 *)&g.d_0062b8a4)));
  iVar1 = file_resolve_path((iptr)local_84);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    str_clear((iptr)local_118);
    str_append((iptr)local_118,ADDR(0x62b8bc, ((u8 *)&g.d_0062b8bc)));
    iVar1 = file_resolve_path((iptr)local_118);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      dll_handle_load((DllHandle *)(this->pad_ae4 + 0x430),(iptr)local_118);
      wnd_create_with_handlers
                ((WndBase *)this,ADDR(0x62b8d0, ((u8 *)&g.d_0062b8d0)),0x800,local_98,local_94,local_90 - local_98,
                 (local_8c - local_94) + 5,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)),ADDR(0x6553d8, ((u8 *)&g.d_006553d8)));
      wnd_set_bg_color((WndBase *)this,0);
      surface_load_gif_resource
                ((DibSurface *)(this->pad_1e4 + 0x308),2000,10,0xec,(iptr)&this->control_list);
      avi_player_create((MediaWindow *)(this->pad_1e4 + 0x308),ADDR(0x62b8d4, ((u8 *)&g.d_0062b8d4)),0x800,0,0);
      avi_player_set_double_size((MediaWindow *)(this->pad_1e4 + 0x308),1);
      local_88 = avi_player_open((AviPlayerOpenView *)(this->pad_1e4 + 0x308),(iptr)local_84);
      if (local_88 == 0) {
        surface_fill((DibSurface *)(this->pad_1e4 + 0x308),0);
        wnd_center((WndCenterView *)(this->pad_504 + 0x30));
        avi_player_set_end_callback((AviPlayerEndCbSetView *)(this->pad_1e4 + 0x308),ADDR(0x4031c0, arrival_movie_on_video_end));
        avi_player_set_frame_callback((AviPlayerSetFrameCallbackView *)(this->pad_1e4 + 0x308),ADDR(0x401d43, arrival_movie_on_frame),0x2ab);
        SetRect((LPRECT)(this[1].pad_1e4 + 0x1d0),2,100,0x27e,0x1e0);
        uVar2 = surface_get_height((DibSurface *)(this->pad_1e4 + 0x308));
        uVar3 = surface_get_width((DibSurface *)(this->pad_1e4 + 0x308));
        surface_create((DibSurface *)(this[1].pad_1e4 + 0x188),uVar3,uVar2);
        avi_player_draw_to
                  ((DibSurface *)(this->pad_1e4 + 0x308),(iptr)(this[1].pad_1e4 + 0x188),0,0);
        font_set_styled((GameFont *)this->pad_f1c,0,0x12,3);
        dll_handle_free((DllHandle *)(this->pad_ae4 + 0x430));
        uVar2 = 1;
      }
      else {
        if (local_88 == -0x7ffbfeac) {
          popup_game(ADDR(0x62b8d8, ((u8 *)&g.d_0062b8d8)));
        }
        uVar2 = 0;
      }
    }
  }
  return uVar2;
}
#undef local_118
#undef local_98
#undef local_94
#undef local_90
#undef local_8c
#undef local_88
#undef local_84

/* 00471856 auto */
#define text_line_cursor (*(iptr *)((u8 *)&g.d_00673f14))
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall arrival_movie_wnd_play(SpaceshipWindow *this)

{
  iptr iVar1;
  int iVar2;
  char *pcVar3;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  wnd_handle_show_raise((WndBase *)this);
  wnd_flush_paint();
  wnd_set_palette((WndBase *)this,(iptr)&this->control_list);
  window_show((WindowObjectView *)(this->pad_1e4 + 0x308));
  wnd_flush_paint();
  wnd_set_capture((WndBase *)(this->pad_504 + 0x30));
  gfx_set_text_color_index(0xff);
  str_clear((iptr)(this->pad_f1c + 8));
  text_clear();
  text_append_year((int)civs[this->advance_civ].spaceship_launch_year);
  text_set_string_arg(0,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  text_clear();
  text_append_int((int)civs[this->advance_civ].spaceship_population);
  text_append(ADDR(0x62b8ec, ((u8 *)&g.d_0062b8ec)));
  text_set_string_arg(1,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  iVar1 = civ_get_adjective(this->advance_civ);
  text_set_string_arg(2,iVar1);
  text_clear();
  text_append_year((int)civs[this->advance_civ].spaceship_arrival_year);
  text_set_string_arg(3,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  iVar1 = civ_leader_name(this->advance_civ);
  text_set_string_arg(4,iVar1);
  for (local_8 = 0; local_8 < 3; local_8++) {
    str_clear((iptr)(this->pad_f1c + 8));
    text_clear();
    text_append(ADDR(0x62b8f4, ((u8 *)&g.d_0062b8f4)));
    text_append_int(local_8);
    iVar2 = text_open_section(ADDR(0x6558e8, ((u8 *)&g.d_006558e8)),ADDR(0x679640, ((u8 *)&g.d_00679640)));
    if (iVar2 == 0) {
      while( true ) {
        pcVar3 = (char *)text_read_line(1);
        if (*pcVar3 == '@') break;
        str_append((iptr)(this->pad_f1c + 8),text_line_cursor);
        str_append((iptr)(this->pad_f1c + 8),ADDR(0x62b900, ((u8 *)&g.d_0062b900)));
      }
      text_clear();
      text_expand_vars((iptr)(this->pad_f1c + 8),ADDR(0x679640, ((u8 *)&g.d_00679640)));
      surface_blit
                ((DibSurface *)(this[1].pad_1e4 + 0x188),(iptr)(this->pad_1e4 + 0x308),
                 (iptr)(this[1].pad_1e4 + 0x1d0),(iptr)(this[1].pad_1e4 + 0x1d0));
      OffsetRect((LPRECT)(this[1].pad_1e4 + 0x1d0),1,1);
      gfx_set_text_color_index(0);
      surface_draw_text_rect
                ((DibSurface *)(this->pad_1e4 + 0x308),(iptr)this->pad_f1c,ADDR(0x679640, ((u8 *)&g.d_00679640)),
                 (iptr)(this[1].pad_1e4 + 0x1d0),0);
      OffsetRect((LPRECT)(this[1].pad_1e4 + 0x1d0),-1,-1);
      gfx_set_text_color_index(0xf1);
      surface_draw_text_rect
                ((DibSurface *)(this->pad_1e4 + 0x308),(iptr)this->pad_f1c,ADDR(0x679640, ((u8 *)&g.d_00679640)),
                 (iptr)(this[1].pad_1e4 + 0x1d0),0);
      gfx_dissolve_blit((iptr)(this->pad_1e4 + 0x308),(iptr)(this[1].pad_1e4 + 0x1d0),4,5);
      text_close_file();
      ui_delay_ticks(0x168);
    }
  }
  avi_player_play((AviPlayerPlayView *)(this->pad_1e4 + 0x308));
  if (2 < game.multiplayer) {
    wnd_set_modal_idle_callback((ModalMenuWindow *)(this->pad_504 + 0x30),ADDR(0x403585, net_modal_idle_poll));
  }
  wnd_run_modal_loop((ModalMenuWindow *)(this->pad_504 + 0x30));
  wnd_set_modal_idle_callback((ModalMenuWindow *)(this->pad_504 + 0x30),0);
  wnd_release_capture((WndBase *)(this->pad_504 + 0x30));
  wnd_hide((WndBase *)(this->pad_504 + 0x30));
  wnd_flush_paint();
  wnd_hide((WndBase *)this);
  wnd_set_palette((WndBase *)&main_frame_wnd,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
  wnd_flush_paint();
  return;
}
#undef text_line_cursor
#undef local_8

/* 00471c2a auto */
#define text_line_cursor (*(iptr *)((u8 *)&g.d_00673f14))
#define local_1c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(12)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(16)))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(24)))
void __cdecl arrival_movie_on_frame(void)

{
  int iVar1;
  char *pcVar2;
  i32 uVar3;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  *(i32 *)(spaceship_arrival_window + 0xa98) = 0;
  str_clear(spaceship_arrival_window + 0xf24);
  text_clear();
  iVar1 = text_open_section(ADDR(0x6558e8, ((u8 *)&g.d_006558e8)),ADDR(0x62b904, ((u8 *)&g.d_0062b904)));
  if (iVar1 == 0) {
    local_1c = 0xc;
    text_set_font(spaceship_arrival_window + 0xf1c);
    text_set_surface(spaceship_arrival_window + 0x4ec);
    text_set_colors(0xff,0,1,1);
    while( true ) {
      pcVar2 = (char *)text_read_line(1);
      if (*pcVar2 == '@') break;
      str_clear(spaceship_arrival_window + 0xf24);
      str_append(spaceship_arrival_window + 0xf24,text_line_cursor);
      text_expand_vars(spaceship_arrival_window + 0xf24,ADDR(0x679640, ((u8 *)&g.d_00679640)));
      uVar3 = rect_width(spaceship_arrival_window + 0x136c);
      gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),*(i32 *)(spaceship_arrival_window + 0x136c),local_1c,uVar3);
      iVar1 = font_line_spacing((GameFont *)(spaceship_arrival_window + 0xf1c));
      local_1c += iVar1;
    }
    local_14 = *(i32 *)(spaceship_arrival_window + 0x136c);
    local_c = *(i32 *)(spaceship_arrival_window + 0x1374);
    local_10 = 0xc;
    local_8 = local_1c;
    gfx_dissolve_blit(spaceship_arrival_window + 0x4ec,(iptr)&local_14,4,5);
    text_close_file();
  }
  return;
}
#undef text_line_cursor
#undef local_1c
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 00471db7 auto */
void __cdecl arrival_movie_on_video_end(void)

{
  wnd_end_modal_loop((ModalMenuWindow *)(spaceship_arrival_window + 0x534));
  return;
}

/* 00471dd8 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define text_line_cursor (*(iptr *)((u8 *)&g.d_00673f14))
#define local_808 (*(i8 (*)[276])(frame_ + FRAME_OFF(0)))
#define local_6f4 (*(ModalMenuWindow *)(frame_ + FRAME_OFF(276)))
#define local_63c (*(tagRECT *)(frame_ + FRAME_OFF(460)))
#define local_62c (*(int *)(frame_ + FRAME_OFF(476)))
#define local_628 (*(DibSurface *)(frame_ + FRAME_OFF(480)))
#define local_5e0 (*(GameFont *)(frame_ + FRAME_OFF(552)))
#define local_5d8 (*(i8 (*)[256])(frame_ + FRAME_OFF(560)))
#define local_4d8 (*(DllHandle *)(frame_ + FRAME_OFF(816)))
#define local_4d4 (*(int *)(frame_ + FRAME_OFF(820)))
#define local_4d0 (*(int *)(frame_ + FRAME_OFF(824)))
#define local_4cc (*(int *)(frame_ + FRAME_OFF(828)))
#define local_4c8 (*(int *)(frame_ + FRAME_OFF(832)))
#define local_4c4 (*(i8 (*)[128])(frame_ + FRAME_OFF(836)))
#define local_444 (*(GamePalette *)(frame_ + FRAME_OFF(964)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(2040)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(2044)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(2048)))
void __cdecl endgame_show_centauri_beaten(uptr civ)

{
  int iVar1;
  iptr iVar2;
  char *pcVar3;
  i8 frame_[FRAME_OFF(2056)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  surfwnd_ctor((SurfaceWindow *)local_808);
  local_8 = 0;
  dll_handle_init(&local_4d8);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  wnd_ctor(&local_6f4);
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  palette_init(&local_444);
  (*(i8 *)((char *)&local_8 + 0)) = 3;
  surface_ctor(&local_628);
  (*(i8 *)((char *)&local_8 + 0)) = 4;
  font_init_empty(&local_5e0);
  (*(i8 *)((char *)&local_8 + 0)) = 5;
  if ((int)civ < 1) {
    civ = ~civ + 1;
  }
  font_set_styled(&local_5e0,0,0x12,3);
  str_clear((iptr)local_4c4);
  str_append((iptr)local_4c4,ADDR(0x62b910, ((u8 *)&g.d_0062b910)));
  iVar1 = file_resolve_path((iptr)local_4c4);
  if (iVar1 == 0) {
    (*(i8 *)((char *)&local_8 + 0)) = 4;
    /* inlined unwind funclet 00472393 */ { font_destroy((GameFont *)((iptr)&local_5e0)); }
    (*(i8 *)((char *)&local_8 + 0)) = 3;
    /* inlined unwind funclet 0047239f */ { surface_dtor((DibSurface *)((iptr)&local_628)); }
    (*(i8 *)((char *)&local_8 + 0)) = 2;
    /* inlined unwind funclet 004723ab */ { palette_destroy((GamePalette *)((iptr)&local_444)); }
    (*(i8 *)((char *)&local_8 + 0)) = 1;
    /* inlined unwind funclet 004723b7 */ { wnd_dtor((WndBase *)((iptr)&local_6f4)); }
    local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
    /* inlined unwind funclet 004723c3 */ { dll_free((DllHandle *)((iptr)&local_4d8)); }
    local_8 = 0xffffffff;
    /* inlined unwind funclet 004723cf */ { surfwnd_dtor((SurfaceWindow *)((iptr)&local_808)); }
  }
  else {
    dll_handle_load(&local_4d8,(iptr)local_4c4);
    gfx_get_screen_rect((iptr)&local_4d4);
    SetRect(&local_63c,0,0,0x280,0xf0);
    InflateRect(&local_63c,-10,0);
    wnd_create_with_handlers
              ((WndBase *)&local_6f4,ADDR(0x62b924, ((u8 *)&g.d_0062b924)),0x800,local_4d4,local_4d0,local_4cc - local_4d4,
               (local_4c8 - local_4d0) + 5,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)),ADDR(0x6553d8, ((u8 *)&g.d_006553d8)));
    wnd_set_bg_color((WndBase *)&local_6f4,0);
    surface_wnd_create
              ((DibSurface *)local_808,ADDR(0x62b928, ((u8 *)&g.d_0062b928)),0x800,0,0,0x280,0xf0,(iptr)&local_444);
    surface_load_gif_resource((DibSurface *)local_808,30000,10,0xec,(iptr)&local_444);
    wnd_center((WndCenterView *)(local_808 + 0x48));
    surface_create(&local_628,0x280,0xf0);
    surface_blit
              ((DibSurface *)local_808,(iptr)&local_628,(iptr)&local_63c,(iptr)&local_63c);
    surface_set_palette(&local_628,(iptr)&local_444);
    wnd_handle_show_raise((WndBase *)&local_6f4);
    wnd_flush_paint();
    wnd_set_palette((WndBase *)&local_6f4,(iptr)&local_444);
    window_show((WindowObjectView *)local_808);
    wnd_flush_paint();
    wnd_set_capture((WndBase *)(local_808 + 0x48));
    gfx_set_text_color_index(0xff);
    text_clear();
    text_append_year((int)civs[civ].spaceship_launch_year);
    text_set_string_arg(0,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    text_clear();
    text_append_int((int)civs[civ].spaceship_population);
    text_append(ADDR(0x62b92c, ((u8 *)&g.d_0062b92c)));
    text_set_string_arg(1,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    iVar2 = civ_get_adjective(civ);
    text_set_string_arg(2,iVar2);
    text_clear();
    text_append_year((int)civs[civ].spaceship_arrival_year);
    text_set_string_arg(3,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    iVar2 = civ_leader_name(human_civ);
    text_set_string_arg(4,iVar2);
    iVar1 = font_cached_height(&local_5e0);
    local_63c.top = local_63c.bottom + iVar1 * -2 >> 1;
    for (local_62c = 0; local_62c < 5; local_62c++) {
      str_clear((iptr)local_5d8);
      text_clear();
      text_append(ADDR(0x62b934, ((u8 *)&g.d_0062b934)));
      text_append_int(local_62c);
      iVar1 = text_open_section(ADDR(0x6558e8, ((u8 *)&g.d_006558e8)),ADDR(0x679640, ((u8 *)&g.d_00679640)));
      if (iVar1 == 0) {
        while (pcVar3 = (char *)text_read_line(1), *pcVar3 != '@') {
          str_append((iptr)local_5d8,text_line_cursor);
          str_append((iptr)local_5d8,ADDR(0x62b944, ((u8 *)&g.d_0062b944)));
        }
        text_clear();
        text_expand_vars((iptr)local_5d8,ADDR(0x679640, ((u8 *)&g.d_00679640)));
        surface_blit(&local_628,(iptr)local_808,(iptr)&local_63c,(iptr)&local_63c);
        OffsetRect(&local_63c,1,1);
        gfx_set_text_color_index(0);
        surface_draw_text_rect
                  ((DibSurface *)local_808,(iptr)&local_5e0,ADDR(0x679640, ((u8 *)&g.d_00679640)),(iptr)&local_63c,0);
        OffsetRect(&local_63c,-1,-1);
        gfx_set_text_color_index(0xff);
        surface_draw_text_rect
                  ((DibSurface *)local_808,(iptr)&local_5e0,ADDR(0x679640, ((u8 *)&g.d_00679640)),(iptr)&local_63c,0);
        gfx_dissolve_blit((iptr)local_808,(iptr)&local_63c,4,5);
        text_close_file();
        ui_delay_ticks(0x168);
      }
    }
    wnd_release_capture((WndBase *)(local_808 + 0x48));
    wnd_hide((WndBase *)(local_808 + 0x48));
    wnd_flush_paint();
    wnd_set_palette((WndBase *)&local_6f4,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
    wnd_hide((WndBase *)&local_6f4);
    wnd_flush_paint();
    dll_handle_free(&local_4d8);
    (*(i8 *)((char *)&local_8 + 0)) = 4;
    /* inlined unwind funclet 00472393 */ { font_destroy((GameFont *)((iptr)&local_5e0)); }
    (*(i8 *)((char *)&local_8 + 0)) = 3;
    /* inlined unwind funclet 0047239f */ { surface_dtor((DibSurface *)((iptr)&local_628)); }
    (*(i8 *)((char *)&local_8 + 0)) = 2;
    /* inlined unwind funclet 004723ab */ { palette_destroy((GamePalette *)((iptr)&local_444)); }
    (*(i8 *)((char *)&local_8 + 0)) = 1;
    /* inlined unwind funclet 004723b7 */ { wnd_dtor((WndBase *)((iptr)&local_6f4)); }
    local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
    /* inlined unwind funclet 004723c3 */ { dll_free((DllHandle *)((iptr)&local_4d8)); }
    local_8 = 0xffffffff;
    /* inlined unwind funclet 004723cf */ { surfwnd_dtor((SurfaceWindow *)((iptr)&local_808)); }
  }
  return;
}
#undef human_civ
#undef text_line_cursor
#undef local_808
#undef local_6f4
#undef local_63c
#undef local_62c
#undef local_628
#undef local_5e0
#undef local_5d8
#undef local_4d8
#undef local_4d4
#undef local_4d0
#undef local_4cc
#undef local_4c8
#undef local_4c4
#undef local_444
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004728c0 auto */
void * __thiscall arrival_movie_wnd_scalar_dtor(void *this,uint param_1)

{
  arrival_movie_wnd_dtor(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 004a76f5 auto */
#define destroyed_civ_count (*(i16 *)((u8 *)&g.d_00655128))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl destroyed_civs_clear(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  destroyed_civ_count = 0;
  for (local_8 = 0; local_8 < 0xc; local_8++) {
    *(i16 *)(&destroyed_civ_turns + local_8 * 2) = 0;
    (&destroyed_civ_killers)[local_8] = 0;
    (&destroyed_civ_names)[local_8 * 0x18] = 0;
  }
  return;
}
#undef destroyed_civ_count
#undef local_8

/* 004bc480 auto */
#define local_70 (*(int *)(frame_ + FRAME_OFF(0)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(4)))
#define aiStack_68 (*(int (*)[8])(frame_ + FRAME_OFF(8)))
#define local_48 (*(int *)(frame_ + FRAME_OFF(40)))
#define city2 (*(iptr *)(frame_ + FRAME_OFF(44)))
#define city (*(iptr *)(frame_ + FRAME_OFF(48)))
#define local_3c (*(int *)(frame_ + FRAME_OFF(52)))
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(56)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(60)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(64)))
#define civ2 (*(iptr *)(frame_ + FRAME_OFF(68)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(72)))
#define aiStack_24 (*(int (*)[8])(frame_ + FRAME_OFF(76)))
i32 __cdecl council_military_advice(iptr civ,i32 param_2)

{
  int iVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(112)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_70 = 0;
  local_48 = 0;
  city2 = -1;
  for (city = 0; city < game.num_cities; city++) {
    if ((cities[city].id != 0) && (cities[city].owner == civ)) {
      iVar1 = city_has_improvement(city,2);
      if (iVar1 != 0) {
        local_70++;
      }
      iVar1 = city_has_improvement(city,1);
      if (iVar1 != 0) {
        city2 = city;
      }
      local_48++;
    }
  }
  if (local_48 < 2) {
    local_48 = 1;
  }
  local_34 = 0;
  for (unit = 0; unit < game.num_units; unit++) {
    if ((units[unit].id != 0) && (units[unit].owner == civ)) {
      local_34++;
    }
  }
  if ((local_48 - 1 + local_34) / local_48 < (int)((civs[civ].government < 5) + 2)) {
    uVar2 = 1;
  }
  else {
    for (civ2 = 0; civ2 < 8; civ2++) {
      aiStack_68[civ2] = 0;
      aiStack_24[civ2] = aiStack_68[civ2];
    }
    for (civ2 = 1; civ2 < 8; civ2++) {
      iVar1 = civ_has_advance(civ2,0x4b);
      if (iVar1 != 0) {
        aiStack_68[civ2]++;
      }
      iVar1 = civ_has_advance(civ2,0x3b);
      if (iVar1 != 0) {
        aiStack_68[civ2]++;
      }
      for (unit_type = 0; unit_type < 0x3e; unit_type++) {
        iVar1 = civ_has_advance(civ2,(int)unit_types[unit_type].prerequisite);
        if (iVar1 != 0) {
          if (unit_types[unit_type].domain == 2) {
            aiStack_68[civ2]++;
          }
          else if ((unit_types[unit_type].role == '\0') || (unit_types[unit_type].role == 1)) {
            aiStack_24[civ2]++;
          }
        }
      }
    }
    local_3c = 0;
    local_28 = 0;
    local_30 = 0;
    for (civ2 = 1; civ2 < 8; civ2++) {
      if (civ != civ2) {
        if ((*(byte *)(civ2 * 4 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ * 0x594) & 0x20) != 0) {
          local_30++;
        }
        if (aiStack_68[civ] < aiStack_68[civ2]) {
          local_28++;
        }
        if (aiStack_24[civ] < aiStack_24[civ2]) {
          local_3c++;
        }
      }
    }
    iVar1 = bits_count8((uint)game.civs_alive);
    if ((iVar1 - 1) / 2 < local_3c) {
      uVar2 = 2;
    }
    else {
      iVar1 = bits_count8((uint)game.civs_alive);
      if ((iVar1 - 1) / 2 < local_28) {
        uVar2 = 3;
      }
      else {
        iVar1 = civ_has_advance(civ,0x2f);
        if ((((iVar1 == 0) || (city2 < 0)) ||
            (iVar1 = city_has_improvement(city2,8), iVar1 != 0)) ||
           (iVar1 = civ_has_wonder(civ,6), iVar1 != 0)) {
          if (local_70 == 0) {
            uVar2 = 4;
          }
          else if ((local_30 == 0) && (4 < game.power_rank[civ])) {
            uVar2 = 7;
          }
          else {
            uVar2 = 6;
          }
        }
        else {
          uVar2 = 5;
        }
      }
    }
  }
  return uVar2;
}
#undef local_70
#undef unit
#undef aiStack_68
#undef local_48
#undef city2
#undef city
#undef local_3c
#undef unit_type
#undef local_34
#undef local_30
#undef civ2
#undef local_28
#undef aiStack_24

/* 004bc8aa auto */
#define local_20 (*(int *)(frame_ + FRAME_OFF(0)))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(4)))
#define city (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(12)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(16)))
#define civ2 (*(iptr *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(24)))
i32 __cdecl council_science_advice(iptr civ,int param_2)

{
  i32 uVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_10 = 0;
  for (civ2 = 1; civ2 < 8; civ2++) {
    if ((civ2 != civ) && (civs[civ].num_advances <= civs[civ2].num_advances)) {
      local_10++;
    }
  }
  if (local_10 == 0) {
    uVar1 = 7;
  }
  else {
    if (civs[civ].government < 5) {
      if ((civs[civ].government != 4) && (civs[civ].science_rate < 6)) {
        return 2;
      }
    }
    else if (civs[civ].science_rate < 4) {
      return 2;
    }
    local_20 = 0;
    local_14 = 0;
    local_8 = (uint)civs[civ].units_active[0x30] + (uint)civs[civ].units_active[0x31];
    if (param_2 == 0) {
      improvement = 6;
    }
    else if (param_2 == 1) {
      improvement = 0xc;
    }
    else {
      improvement = 0x1a;
    }
    for (city = 0; city < game.num_cities; city++) {
      if ((cities[city].id != 0) && (cities[city].owner == civ)) {
        local_20++;
        iVar2 = city_has_improvement(city,improvement);
        if (iVar2 != 0) {
          local_14++;
        }
        local_8 += (char)cities[city].trade_routes;
      }
    }
    iVar2 = civ_has_advance(civ,(int)improvements[improvement].preq);
    if ((iVar2 == 0) || (local_20 / 2 <= local_14)) {
      iVar2 = civ_has_advance(civ,0x54);
      if ((iVar2 == 0) || ((int)(local_20 + (local_20 >> 0x1f & 3U)) >> 2 <= local_8)) {
        iVar2 = bits_count8((uint)game.civs_alive);
        if (local_10 < iVar2 / 2) {
          uVar1 = 5;
        }
        else {
          uVar1 = 1;
        }
      }
      else {
        uVar1 = 4;
      }
    }
    else {
      uVar1 = 3;
    }
  }
  return uVar1;
}
#undef local_20
#undef improvement
#undef city
#undef local_14
#undef local_10
#undef civ2
#undef local_8

/* 004bcb9b auto */
#define local_d0 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_c8 (*(int *)(frame_ + FRAME_OFF(8)))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(12)))
#define city (*(iptr *)(frame_ + FRAME_OFF(16)))
#define local_bc (*(iptr *)(frame_ + FRAME_OFF(20)))
#define local_b4 (*(int *)(frame_ + FRAME_OFF(28)))
#define local_b0 (*(int *)(frame_ + FRAME_OFF(32)))
#define aiStack_ac (*(int (*)[39])(frame_ + FRAME_OFF(36)))
#define local_10 (*(iptr *)(frame_ + FRAME_OFF(192)))
#define local_c (*(int *)(frame_ + FRAME_OFF(196)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(200)))
i32 __cdecl council_trade_advice(iptr civ,int param_2)

{
  int iVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(208)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_b0 = 0;
  local_b4 = 0;
  local_d0 = 0;
  local_c8 = 0;
  local_8 = (uint)civs[civ].units_active[0x30] + (uint)civs[civ].units_active[0x31];
  if (param_2 == 0) {
    local_bc = 0x14;
    local_10 = 5;
    local_c = 2;
  }
  else if (param_2 == 1) {
    local_bc = 6;
    local_10 = 10;
    local_c = 3;
  }
  else {
    local_bc = 0x16;
    local_10 = 0x16;
    local_c = 4;
  }
  for (improvement = 0; improvement < 0x27; improvement++) {
    aiStack_ac[improvement] = 0;
  }
  for (city = 0; city < game.num_cities; city++) {
    if ((cities[city].id != 0) && (cities[city].owner == civ)) {
      local_c8++;
      local_8 += (char)cities[city].trade_routes;
      city_split_trade(city,(int)cities[city].trade,1,0);
      for (improvement = 0; improvement < 0x27; improvement++) {
        iVar1 = city_has_improvement(city,improvement);
        if (iVar1 != 0) {
          aiStack_ac[improvement]++;
        }
      }
      iVar1 = city_has_improvement(city,local_10);
      if (iVar1 != 0) {
        local_d0++;
      }
      if ((cities[city].flags & 1) == 0) {
        local_b0 += cities[city].tax;
      }
    }
  }
  for (improvement = 0; improvement < 0x27; improvement++) {
    if ((aiStack_ac[improvement] != 0) && (iVar1 = civ_improvement_upkeep(civ,improvement), iVar1 != 0)) {
      local_b4 += aiStack_ac[improvement] * iVar1;
    }
  }
  if ((local_b0 < local_b4) && (civs[civ].gold < 100)) {
    uVar2 = 1;
  }
  else {
    iVar1 = civ_has_advance(civ,local_bc);
    if (iVar1 == 0) {
      uVar2 = 2;
    }
    else if (local_d0 < local_c8 / local_c) {
      uVar2 = 3;
    }
    else {
      iVar1 = civ_has_advance(civ,0x54);
      if (iVar1 == 0) {
        uVar2 = 4;
      }
      else if (local_8 < (int)(local_c8 + (local_c8 >> 0x1f & 3U)) >> 2) {
        uVar2 = 5;
      }
      else if (local_b0 - local_b4 < 6) {
        uVar2 = 6;
      }
      else {
        uVar2 = 7;
      }
    }
  }
  return uVar2;
}
#undef local_d0
#undef local_c8
#undef improvement
#undef city
#undef local_bc
#undef local_b4
#undef local_b0
#undef aiStack_ac
#undef local_10
#undef local_c
#undef local_8

/* 004bcfcf auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define local_1c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(12)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(24)))
i32 __cdecl council_foreign_advice(iptr civ,int param_2)

{
  int iVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_14 = 0;
  local_1c = 0;
  local_10 = 0;
  local_8 = 0;
  for (local_c = 1; local_c < 8; local_c++) {
    if (local_c != civ) {
      if ((*(byte *)&civs[civ].treaties[local_c] & 1) != 0) {
        local_8++;
      }
      if ((*(byte *)&civs[civ].treaties[local_c] & 8) != 0) {
        local_10++;
      }
      if ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + local_c * 4) & 0x20) != 0) {
        local_14++;
      }
      if ((((*(byte *)&civs[human_civ].treaties[local_c] & 0x80) != 0) ||
          (iVar1 = civ_has_wonder(human_civ,0x18), iVar1 != 0)) ||
         (iVar1 = civ_has_wonder(human_civ,9), iVar1 != 0)) {
        local_1c++;
      }
    }
  }
  if (local_8 == 0) {
    uVar2 = 1;
  }
  else {
    if (param_2 == 2) {
      local_18 = 0x1b;
    }
    else {
      local_18 = 0x58;
    }
    iVar1 = civ_has_advance(civ,local_18);
    if (iVar1 == 0) {
      uVar2 = 3;
    }
    else if ((((local_8 < 2) || (1 < civs[civ].reputation)) || (local_10 != 0)) ||
            (((civs[civ].flags & 0x100) != 0 || (6 < game.power_rank[civ])))) {
      if (civs[civ].reputation < 3) {
        if ((local_14 == local_8) && (1 < civs[civ].reputation)) {
          uVar2 = 4;
        }
        else if ((civs[civ].flags & 0x80) == 0) {
          uVar2 = 6;
        }
        else if ((local_1c == 0) || ((local_14 == local_8 && (local_1c < local_8)))) {
          uVar2 = 5;
        }
        else if (local_14 == local_8) {
          uVar2 = 6;
        }
        else {
          uVar2 = 7;
        }
      }
      else {
        uVar2 = 4;
      }
    }
    else {
      uVar2 = 2;
    }
  }
  return uVar2;
}
#undef human_civ
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 004bd2a3 auto */
#define city (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(12)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_c (*(int *)(frame_ + FRAME_OFF(20)))
i32 __cdecl council_attitude_advice(iptr civ,i32 param_2)

{
  bool bVar1;
  ushort uVar2;
  i32 uVar3;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  uVar2 = game.field_06 & 4;
  game.field_06 = game.field_06 & 0xfffb;
  local_18 = 0;
  local_c = 0;
  local_14 = 0;
  local_10 = 0;
  for (city = 0; city < game.num_cities; city++) {
    if ((cities[city].id != 0) && (cities[city].owner == civ)) {
      if ((uVar2 != 0) && (4 < civs[civ].government)) {
        city_recalc(city,1);
      }
      if ((char)cities[city].happy < (char)cities[city].unhappy) {
        local_10++;
        if ((cities[city].flags & 1) != 0) {
          local_c++;
        }
      }
      else if (cities[city].happy == cities[city].unhappy) {
        local_18++;
      }
      if ((cities[city].flags & 2) != 0) {
        local_14++;
      }
    }
  }
  if (civs[civ].government < 5) {
    bVar1 = true;
    if ((((local_10 == 0) && (local_18 != 0)) && (local_14 == 0)) &&
       ((uint)civs[civ].science_rate + (uint)civs[civ].tax_rate == 10)) {
      bVar1 = false;
    }
  }
  else {
    bVar1 = (uint)civs[civ].science_rate + (uint)civs[civ].tax_rate < 9;
  }
  if (local_10 == 0) {
    if (bVar1) {
      if (local_14 == 0) {
        uVar3 = 5;
      }
      else {
        uVar3 = 6;
      }
    }
    else {
      uVar3 = 4;
    }
  }
  else if (bVar1) {
    if ((local_c == 0) || (civs[civ].government != 6)) {
      uVar3 = 3;
    }
    else {
      uVar3 = 1;
    }
  }
  else {
    uVar3 = 2;
  }
  return uVar3;
}
#undef city
#undef local_18
#undef local_14
#undef local_10
#undef local_c

/* 0050a2f7 auto */
#define city2 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define city (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_c (*(int *)(frame_ + FRAME_OFF(28)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(32)))
i32 __cdecl
foreign_minister_draw_civ_city(i32 param_1,iptr param_2,int civ,byte param_4,int param_5,int param_6,
            int param_7)

{
  int iVar1;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 0;
  city2 = -1;
  for (city = 0; city < game.num_cities; city++) {
    if ((cities[city].id != 0) && (cities[city].owner == civ)) {
      local_8 = (int)cities[city].size;
      iVar1 = city_has_improvement(city,1);
      if (iVar1 != 0) {
        local_8 += 200;
      }
      if (cities[city].building == -1) {
        local_8 += 100;
      }
      if (local_c < local_8) {
        local_c = local_8;
        city2 = city;
      }
    }
  }
  if (-1 < city2) {
    local_18 = param_5;
    if ((param_4 & 1) != 0) {
      local_18 = param_5 + 0x26;
    }
    iVar1 = gfx_zoom_scale(0x30,0xfffffffe);
    gfx_draw_city(param_2,city2,0,local_18,param_6 - (iVar1 - param_7) / 2,0xfffffffe);
  }
  return 0;
}
#undef city2
#undef city
#undef local_18
#undef local_c
#undef local_8

/* 00514e10 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl destroyed_civs_text_bg_global_init(void)

{
  destroyed_civs_text_bg_static_init();
  destroyed_civs_text_bg_reg_atexit();
  return;
}

/* 00514e2a auto */
void __cdecl destroyed_civs_text_bg_static_init(void)

{
  surface_ctor((DibSurface *)&destroyed_civs_text_bg);
  return;
}

/* 00514e44 auto */
void __cdecl destroyed_civs_text_bg_reg_atexit(void)

{
  _atexit(destroyed_civs_text_bg_atexit_dtor);
  return;
}

/* 00514e61 auto */
void __cdecl destroyed_civs_text_bg_atexit_dtor(void)

{
  surface_dtor((DibSurface *)&destroyed_civs_text_bg);
  return;
}

/* 00514e7b auto */
#define local_718 (*(i8 (*)[1808])(frame_ + FRAME_OFF(0)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1808)))
void __cdecl destroyed_civs_show(iptr param_1)

{
  int iVar1;
  i8 frame_[FRAME_OFF(1816)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  (*(i32 *)((char *)&local_718 + 1804)) = &LAB_00514efe;
  destroyed_civs_wnd_ctor((DestroyedCivsWindow *)local_718);
  local_8 = 0;
  iVar1 = destroyed_civs_wnd_create((DestroyedCivsWindow *)local_718,param_1);
  if (iVar1 == 0) {
    local_8 = 0xffffffff;
    /* inlined unwind funclet 00514ef2 */ { destroyed_civs_wnd_dtor((DestroyedCivsWindowCore *)((iptr)&local_718)); }
  }
  else {
    destroyed_civs_run((DestroyedCivsWindow *)local_718);
    local_8 = 0xffffffff;
    /* inlined unwind funclet 00514ef2 */ { destroyed_civs_wnd_dtor((DestroyedCivsWindowCore *)((iptr)&local_718)); }
  }
  return;
}
#undef local_718
#undef local_8

/* 00514f16 auto */
#define victory_screen_wnd (*(DestroyedCivsWindow * *)((u8 *)&g.d_00631a98))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
DestroyedCivsWindow * __thiscall destroyed_civs_wnd_ctor(DestroyedCivsWindow *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  wnd_ctor((ModalMenuWindow *)this);
  local_8 = 0;
  palette_init((GamePalette *)&this->control_list);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  surfwnd_ctor((SurfaceWindow *)(this->pad_1e4 + 0x308));
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  surface_ctor((DibSurface *)(this->pad_504 + 0xfc));
  (*(i8 *)((char *)&local_8 + 0)) = 3;
  dll_handle_init((DllHandle *)(this->pad_638 + 0x10));
  (*(i8 *)((char *)&local_8 + 0)) = 4;
  sprite_init((Sprite *)(this->pad_638 + 0x14));
  (*(i8 *)((char *)&local_8 + 0)) = 5;
  sprite_init((Sprite *)(this->pad_638 + 0x50));
  (*(i8 *)((char *)&local_8 + 0)) = 6;
  font_init_empty((GameFont *)this->pad_700);
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),7);
  this->killer_civ = 0;
  victory_screen_wnd = this;
  this->slide_y = 0;
  SetRect((LPRECT)&this->panel_clip_rect,0xd0,0x39,0x1b1,0x14c);
  font_set_styled((GameFont *)this->pad_700,0,0x18,1);
  return this;
}
#undef victory_screen_wnd
#undef local_10
#undef puStack_c
#undef local_8

/* 005150b9 auto */
#define victory_screen_wnd (*(i32 *)((u8 *)&g.d_00631a98))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __thiscall destroyed_civs_wnd_dtor(DestroyedCivsWindowCore *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  (*(i32 *)((char *)&local_8 + 1)) = 0;
  (*(i8 *)((char *)&local_8 + 0)) = 7;
  dll_handle_free((DllHandle *)(this->pad_0 + 0x648));
  victory_screen_wnd = 0;
  (*(i8 *)((char *)&local_8 + 0)) = 6;
  /* inlined unwind funclet 0051516a */ { font_destroy((GameFont *)(*(int *)((iptr)&this) + 0x700)); }
  (*(i8 *)((char *)&local_8 + 0)) = 5;
  /* inlined unwind funclet 00515179 */ { sprite_destroy((Sprite *)(*(int *)((iptr)&this) + 0x688)); }
  (*(i8 *)((char *)&local_8 + 0)) = 4;
  /* inlined unwind funclet 00515188 */ { sprite_destroy((Sprite *)(*(int *)((iptr)&this) + 0x64c)); }
  (*(i8 *)((char *)&local_8 + 0)) = 3;
  /* inlined unwind funclet 00515197 */ { dll_free((DllHandle *)(*(int *)((iptr)&this) + 0x648)); }
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  /* inlined unwind funclet 005151a6 */ { surface_dtor((DibSurface *)(*(int *)((iptr)&this) + 0x600)); }
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  /* inlined unwind funclet 005151b5 */ { surfwnd_dtor((SurfaceWindow *)(*(int *)((iptr)&this) + 0x4ec)); }
  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
  /* inlined unwind funclet 005151c4 */ { palette_destroy((GamePalette *)(*(int *)((iptr)&this) + 0xb8)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet 005151d3 */ { wnd_dtor(*(WndBase **)((iptr)&this)); }
  return;
}
#undef victory_screen_wnd
#undef uStack_10
#undef puStack_c
#undef local_8

/* 005151f4 auto */
#define destroyed_civs_show_date (*(i32 *)((u8 *)&g.d_00631a9c))
#define local_a8 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_a4 (*(i8 (*)[128])(frame_ + FRAME_OFF(4)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(132)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(136)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(140)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(144)))
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(148)))
i32 __thiscall destroyed_civs_wnd_create(DestroyedCivsWindow *this,uint param_1)

{
  int iVar1;
  i32 uVar2;
  i32 uVar3;
  i8 frame_[FRAME_OFF(168)] __attribute__((aligned(8)));  /* original stack frame */
  
  gfx_get_screen_rect((iptr)&local_24);
  str_clear((iptr)local_a4);
  str_append((iptr)local_a4,ADDR(0x631aa0, ((u8 *)&g.d_00631aa0)));
  iVar1 = file_resolve_path((iptr)local_a4);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    dll_handle_load((DllHandle *)(this->pad_638 + 0x10),(iptr)local_a4);
    this->killer_civ = param_1;
    wnd_create_with_handlers
              ((WndBase *)this,ADDR(0x631aac, ((u8 *)&g.d_00631aac)),0x800,local_24,local_20,local_1c - local_24,
               (local_18 - local_20) + 5,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)),ADDR(0x6553d8, ((u8 *)&g.d_006553d8)));
    wnd_set_bg_color((WndBase *)this,0);
    wnd_create_with_surface
              ((DibSurface *)(this->pad_1e4 + 0x308),ADDR(0x631ab0, ((u8 *)&g.d_00631ab0)),0x800,0,0,0x280,0x1e0,
               (iptr)&this->control_list,(iptr)this);
    wnd_center((WndCenterView *)(this->pad_504 + 0x30));
    surface_load_gif_resource
              ((DibSurface *)(this->pad_504 + 0xfc),0x2711,10,0xec,(iptr)&this->control_list);
    sprite_grab_from_surface
              ((Sprite *)(this->pad_638 + 0x14),(iptr)(this->pad_504 + 0xfc),8,0,0,0x129,0xad
              );
    surface_load_gif_resource
              ((DibSurface *)(this->pad_504 + 0xfc),10000,10,0xec,(iptr)&this->control_list);
    SetRect(&local_14,0,0,0x280,0x1e0);
    surface_blit
              ((DibSurface *)(this->pad_504 + 0xfc),(iptr)(this->pad_1e4 + 0x308),(iptr)&local_14
               ,(iptr)&local_14);
    SetRect((LPRECT)this->pad_6dc,0xc1,0x173,0x1c0,0x1cd);
    uVar2 = surface_height((DibSurface *)(this->pad_504 + 0xfc));
    uVar3 = surface_width((DibSurface *)(this->pad_504 + 0xfc));
    surface_create((DibSurface *)&destroyed_civs_text_bg,uVar3,uVar2);
    surface_blit
              ((DibSurface *)(this->pad_504 + 0xfc),ADDR(0x6aad58, ((u8 *)&g.d_006aad58)),(iptr)this->pad_6dc,
               (iptr)this->pad_6dc);
    for (local_a8 = 0;
        (local_a8 < 0xc && ((uint)(byte)(&destroyed_civ_killers)[local_a8] != (param_1 & 0xff)));
        local_a8 = local_a8 + 1) {
    }
    destroyed_civs_show_date = 0;
    destroyed_civs_draw_entry((WndBase *)this,local_a8);
    this->slide_y = 0x133;
    SetRect((LPRECT)&this->slide_rect,0xab,this->slide_y,0x1d4,this->slide_y + 0xad);
    destroyed_civs_slide_step(this,0);
    uVar2 = 1;
  }
  return uVar2;
}
#undef destroyed_civs_show_date
#undef local_a8
#undef local_a4
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14

/* 00515516 auto */
#define destroyed_civs_show_date (*(i32 *)((u8 *)&g.d_00631a9c))
#define text_line_cursor (*(iptr *)((u8 *)&g.d_00673f14))
#define local_120 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_11c (*(i8 (*)[256])(frame_ + FRAME_OFF(4)))
#define local_1c (*(DWORD *)(frame_ + FRAME_OFF(260)))
#define local_18 (*(GameFont *)(frame_ + FRAME_OFF(264)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(272)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(276)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(280)))
void __thiscall destroyed_civs_run(DestroyedCivsWindow *this)

{
  DWORD DVar1;
  int iVar2;
  char *pcVar3;
  i32 uVar4;
  i8 frame_[FRAME_OFF(288)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  font_init_empty(&local_18);
  local_8 = 0;
  wnd_handle_show_raise((WndBase *)this);
  wnd_flush_paint();
  wnd_set_palette((WndBase *)this,(iptr)&this->control_list);
  window_show((WindowObjectView *)(this->pad_1e4 + 0x308));
  wnd_flush_paint();
  wnd_set_capture((WndBase *)(this->pad_504 + 0x30));
  for (local_120 = 0; local_120 < 0xc; local_120++) {
    if ((&destroyed_civ_killers)[local_120] == (char)this->killer_civ) {
      destroyed_civs_draw_entry((WndBase *)this,local_120);
      destroyed_civs_show_date = 1;
      destroyed_civs_draw_portrait((PictureFrameWindow *)this,local_120);
      DVar1 = timeGetTime();
      snd_play_effect(((uint)(byte)(&destroyed_civ_portraits)[local_120] + (uint)map.seed & 7) + 0x53,1,0,0)
      ;
      destroyed_civs_slide_up(this);
      ui_delay_ticks(0x3c);
      do {
        win_flush_pending_msgs();
        local_1c = timeGetTime();
        if (2 < game.multiplayer) {
          net_process_messages((NetSession *)&net_session,1,0);
        }
      } while ((int)(local_1c - DVar1) < 7000);
      destroyed_civs_draw_entry((WndBase *)this,local_120);
      destroyed_civs_slide_down(this);
    }
  }
  ui_delay_ticks(0x3c);
  surface_fill((DibSurface *)(this->pad_1e4 + 0x308),0);
  SetRect((LPRECT)this->pad_6dc,0,0,0x280,0x1e0);
  gfx_dissolve_blit((iptr)(this->pad_1e4 + 0x308),(iptr)this->pad_6dc,4,4);
  surface_load_gif_resource
            ((DibSurface *)(this->pad_1e4 + 0x308),0x2712,10,0xec,(iptr)&this->control_list);
  text_set_font((iptr)this->pad_700);
  text_set_colors(0x7c,0x81,1,1);
  text_clear();
  str_clear((iptr)local_11c);
  iVar2 = text_open_section(ADDR(0x6558e8, ((u8 *)&g.d_006558e8)),ADDR(0x631ab4, ((u8 *)&g.d_00631ab4)));
  if (iVar2 == 0) {
    while (pcVar3 = (char *)text_read_line(1), *pcVar3 != '@') {
      str_append((iptr)local_11c,text_line_cursor);
      str_append((iptr)local_11c,ADDR(0x631abc, ((u8 *)&g.d_00631abc)));
    }
    text_draw_centered((iptr)(this->pad_1e4 + 0x308),(iptr)local_11c,0,0x48,0x280);
  }
  gfx_dissolve_blit((iptr)(this->pad_1e4 + 0x308),(iptr)this->pad_6dc,4,3);
  text_clear();
  text_append_label(0x1c8);
  font_set_styled(&local_18,0,0x10,3);
  text_set_font((iptr)&local_18);
  uVar4 = 0x280;
  iVar2 = font_line_spacing(&local_18);
  text_draw_centered((iptr)(this->pad_1e4 + 0x308),ADDR(0x679640, ((u8 *)&g.d_00679640)),0,0x1dc - iVar2,uVar4);
  wnd_blit_surface_rect((DibSurface *)(this->pad_1e4 + 0x308),(iptr)this->pad_6dc);
  wnd_set_keydown_handler((WndEventHandlers *)(this->pad_504 + 0x40),ADDR(0x401a1e, victory_screen_on_key));
  wnd_set_lbuttonup_handler((WndEventHandlers *)(this->pad_504 + 0x40),ADDR(0x401334, victory_screen_on_click));
  if (2 < game.multiplayer) {
    wnd_set_modal_idle_callback((ModalMenuWindow *)(this->pad_504 + 0x30),ADDR(0x403585, net_modal_idle_poll));
  }
  wnd_run_modal_loop((ModalMenuWindow *)(this->pad_504 + 0x30));
  wnd_set_modal_idle_callback((ModalMenuWindow *)(this->pad_504 + 0x30),0);
  wnd_release_capture((WndBase *)(this->pad_504 + 0x30));
  wnd_hide((WndBase *)(this->pad_504 + 0x30));
  wnd_flush_paint();
  wnd_set_palette((WndBase *)this,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
  wnd_hide((WndBase *)this);
  wnd_flush_paint();
  local_8 = 0xffffffff;
  /* inlined unwind funclet 00515978 */ { font_destroy((GameFont *)((iptr)&local_18)); }
  return;
}
#undef destroyed_civs_show_date
#undef text_line_cursor
#undef local_120
#undef local_11c
#undef local_1c
#undef local_18
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00515999 auto */
#define destroyed_civs_show_date (*(int *)((u8 *)&g.d_00631a9c))
void __thiscall destroyed_civs_draw_entry(WndBase *this,iptr param_1)

{
  iptr iVar1;
  i32 uVar2;
  
  if (destroyed_civs_show_date == 0) {
    surface_blit
              ((DibSurface *)&destroyed_civs_text_bg,(iptr)(this + 0x60),(iptr)&this[0x6d].field_c,
               (iptr)&this[0x6d].field_c);
    text_clear();
    text_append((iptr)(&destroyed_civ_names + param_1 * 0x18));
    gfx_set_text_color_index(0x21);
    OffsetRect((LPRECT)&this[0x6d].field_c,1,1);
    surface_draw_text_rect
              ((DibSurface *)(this + 0x60),(iptr)(this + 0x70),ADDR(0x679640, ((u8 *)&g.d_00679640)),(iptr)&this[0x6d].field_c
               ,0);
    gfx_set_text_color_index(0x10);
    OffsetRect((LPRECT)&this[0x6d].field_c,-1,-1);
    surface_draw_text_rect
              ((DibSurface *)(this + 0x60),(iptr)(this + 0x70),ADDR(0x679640, ((u8 *)&g.d_00679640)),(iptr)&this[0x6d].field_c
               ,0);
  }
  else {
    surface_blit
              ((DibSurface *)&destroyed_civs_text_bg,(iptr)(this + 0x60),(iptr)&this[0x6d].field_c,
               (iptr)&this[0x6d].field_c);
    text_clear();
    text_append((iptr)(&destroyed_civ_names + param_1 * 0x18));
    text_append_colon();
    text_append_space();
    iVar1 = label_string(*(i32 *)(label_string_ids + 0x71c));
    text_append(iVar1);
    text_append_space();
    uVar2 = game_turn_to_year((int)*(short *)(&destroyed_civ_turns + param_1 * 2));
    text_append_year(uVar2);
    gfx_set_text_color_index(0x21);
    OffsetRect((LPRECT)&this[0x6d].field_c,1,1);
    surface_draw_text_rect
              ((DibSurface *)(this + 0x60),(iptr)(this + 0x70),ADDR(0x679640, ((u8 *)&g.d_00679640)),(iptr)&this[0x6d].field_c
               ,0);
    gfx_set_text_color_index(0x10);
    OffsetRect((LPRECT)&this[0x6d].field_c,-1,-1);
    surface_draw_text_rect
              ((DibSurface *)(this + 0x60),(iptr)(this + 0x70),ADDR(0x679640, ((u8 *)&g.d_00679640)),(iptr)&this[0x6d].field_c
               ,0);
    surface_blit
              ((DibSurface *)(this + 0x60),(iptr)&this[0x4e].field_c,(iptr)&this[0x6d].field_c,
               (iptr)&this[0x6d].field_c);
    wnd_blit_surface_rect
              ((DibSurface *)&this[0x4e].field_c,(iptr)&this[0x6d].field_c);
    destroyed_civs_show_date = 0;
  }
  surface_blit
            ((DibSurface *)(this + 0x60),(iptr)&this[0x4e].field_c,(iptr)&this[0x6d].field_c,
             (iptr)&this[0x6d].field_c);
  return;
}
#undef destroyed_civs_show_date

/* 00515c15 auto */
#define local_55c (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_54c (*(DibSurface *)(frame_ + FRAME_OFF(20)))
#define local_504 (*(i8 (*)[192])(frame_ + FRAME_OFF(92)))
#define local_444 (*(GamePalette *)(frame_ + FRAME_OFF(284)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1360)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1364)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(1368)))
void __thiscall destroyed_civs_draw_portrait(PictureFrameWindow *this,iptr param_1)

{
  i8 frame_[FRAME_OFF(1376)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  surface_ctor(&local_54c);
  local_8 = 0;
  palette_init(&local_444);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  surface_blit
            ((DibSurface *)(this->pad_504 + 0xfc),(iptr)(this->pad_1e4 + 0x308),
             (iptr)&this->panel_clip_rect,(iptr)&this->panel_clip_rect);
  surface_load_gif_resource
            (&local_54c,(byte)(&destroyed_civ_portraits)[param_1] + 0xdc,10,0xec,(iptr)&local_444);
  palette_get_rgb(&local_444,(iptr)local_504,0x2a,0x40);
  palette_set_rgb((GamePalette *)&this->control_list,0x2a,0x40,(iptr)local_504);
  surface_set_palette(&local_54c,(iptr)&this->control_list);
  sprite_grab_from_surface
            ((Sprite *)(this->pad_638 + 0x50),(iptr)&local_54c,9,1,1,0xe1,0x113);
  sprite_draw
            ((Sprite *)(this->pad_638 + 0x50),(iptr)local_55c,(iptr)(this->pad_1e4 + 0x308),
             0xd0,0x39);
  SetRect((LPRECT)&this->panel_clip_rect,0xd0,0x39,0x1b1,0x14c);
  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
  /* inlined unwind funclet 00515d96 */ { palette_destroy((GamePalette *)((iptr)&local_444)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet 00515da2 */ { surface_dtor((DibSurface *)((iptr)&local_54c)); }
  return;
}
#undef local_55c
#undef local_54c
#undef local_504
#undef local_444
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00515dc8 auto */
#define local_44 (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_34 (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
#define local_24 (*(u32 *)(frame_ + FRAME_OFF(36)))
#define local_20 (*(u32 *)(frame_ + FRAME_OFF(40)))
#define local_1c (*(u32 *)(frame_ + FRAME_OFF(44)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_14 (*(u32 *)(frame_ + FRAME_OFF(52)))
#define local_10 (*(u32 *)(frame_ + FRAME_OFF(56)))
#define local_c (*(u32 *)(frame_ + FRAME_OFF(60)))
#define local_8 (*(u32 *)(frame_ + FRAME_OFF(64)))
void __thiscall destroyed_civs_slide_step(DestroyedCivsWindow *this,int param_1)

{
  i8 frame_[FRAME_OFF(72)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_14 = this->slide_rect;
  local_10 = this->slide_top;
  local_c = this->slide_right;
  local_8 = this->resource_dll;
  if (param_1 < 0) {
    local_10 -= param_1;
  }
  else {
    local_8 += param_1;
  }
  surface_blit
            ((DibSurface *)(this->pad_504 + 0xfc),(iptr)(this->pad_1e4 + 0x308),(iptr)&local_14,
             (iptr)&local_14);
  sprite_draw
            ((Sprite *)(this->pad_638 + 0x50),(iptr)local_34,(iptr)(this->pad_1e4 + 0x308),
             0xd0,0x39);
  if (0 < param_1) {
    local_24 = this->panel_clip_rect;
    local_1c = this->panel_clip_right;
    local_20 = this->slide_y;
    local_18 = this->slide_y + param_1;
    surface_blit
              ((DibSurface *)(this->pad_504 + 0xfc),(iptr)(this->pad_1e4 + 0x308),(iptr)&local_24
               ,(iptr)&local_24);
  }
  sprite_draw
            ((Sprite *)(this->pad_638 + 0x14),(iptr)local_44,(iptr)(this->pad_1e4 + 0x308),
             0xab,this->slide_y + param_1);
  OffsetRect((LPRECT)&this->slide_rect,0,param_1);
  if ((int)local_10 < 1) {
    local_10 = 0;
  }
  wnd_blit_surface_rect((DibSurface *)(this->pad_1e4 + 0x308),(iptr)&local_14);
  this->slide_y += param_1;
  return;
}
#undef local_44
#undef local_34
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 00515f3c auto */
#define local_10 (*(DWORD *)(frame_ + FRAME_OFF(0)))
void __thiscall destroyed_civs_slide_down(DestroyedCivsWindow *this)

{
  DWORD DVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  surface_blit
            ((DibSurface *)(this->pad_504 + 0xfc),(iptr)(this->pad_1e4 + 0x308),
             (iptr)&this->panel_clip_rect,(iptr)&this->panel_clip_rect);
  snd_wave_stop_all();
  snd_play_effect(0x6f,1,0,0);
  DVar1 = timeGetTime();
  while (local_10 = DVar1, (int)this->slide_y < 0x133) {
    destroyed_civs_slide_step(this,0xf);
    do {
      win_flush_pending_msgs();
      DVar1 = timeGetTime();
      if (2 < game.multiplayer) {
        net_process_messages((NetSession *)&net_session,1,0);
      }
    } while ((int)(DVar1 - local_10) < 0x16);
  }
  return;
}
#undef local_10

/* 00516005 auto */
void __thiscall destroyed_civs_slide_up(DestroyedCivsWindow *this)

{
  while (-0xad < (int)this->slide_y) {
    win_flush_pending_msgs();
    destroyed_civs_slide_step(this,0xfffffffc);
  }
  return;
}

/* 00516042 auto */
#define victory_screen_wnd (*(int *)((u8 *)&g.d_00631a98))
void __cdecl victory_screen_on_click(void)

{
  wnd_end_modal_loop((ModalMenuWindow *)(victory_screen_wnd + 0x534));
  return;
}
#undef victory_screen_wnd

/* 00516063 auto */
#define victory_screen_wnd (*(int *)((u8 *)&g.d_00631a98))
void __cdecl victory_screen_on_key(int param_1)

{
  if ((0xcf < param_1) && (param_1 < 0xd3)) {
    wnd_end_modal_loop((ModalMenuWindow *)(victory_screen_wnd + 0x534));
  }
  return;
}
#undef victory_screen_wnd

/* 00516570 auto */
#define council_active (*(i8 *)((u8 *)&g.d_00631ad0))
#define local_1338 (*(ListPaneWindow (*)[17])(frame_ + FRAME_OFF(0)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(4904)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4908)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(4912)))
void __cdecl council_show(iptr param_1,i32 param_2)

{
  int iVar1;
  i32 uStackY_28;
  i8 frame_[FRAME_OFF(4920)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  council_active = 1;
  council_wnd_ctor(local_1338);
  local_8 = 0;
  snd_cd_stop();
  uStackY_28 = 0x5165c6;
  iVar1 = council_wnd_init(local_1338,param_1,param_2);
  if (iVar1 != 0) {
    council_wnd_run_modal(local_1338);
  }
  snd_sync_music_option();
  council_active = 0;
  local_8 = 0xffffffff;
  /* inlined unwind funclet 005165f6 */ { council_wnd_dtor((CouncilWindow *)((iptr)&local_1338)); }
  return;
}
#undef council_active
#undef local_1338
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0051661a auto */
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
ListPaneWindow * __thiscall council_wnd_ctor(ListPaneWindow *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  surfwnd_ctor((SurfaceWindow *)this);
  local_8 = 0;
  mmwnd_ctor((DocumentWindow *)&this->style_flags);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  dialog_ctor((Dialog *)&this[10].field_24,0x4000);
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  dll_handle_init((DllHandle *)(this[0xc].pad_48 + 0x98));
  (*(i8 *)((char *)&local_8 + 0)) = 3;
  button_ctor((Control *)(this + 0x10));
  (*(i8 *)((char *)&local_8 + 0)) = 4;
  button_ctor((Control *)&this[0x10].field_3c);
  (*(i8 *)((char *)&local_8 + 0)) = 5;
  button_ctor((Control *)(this[0x10].pad_48 + 0x30));
  (*(i8 *)((char *)&local_8 + 0)) = 6;
  button_ctor((Control *)(this[0x10].pad_48 + 0x6c));
  (*(i8 *)((char *)&local_8 + 0)) = 7;
  button_ctor((Control *)(this[0x10].pad_48 + 0xa8));
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),8);
  button_ctor((Control *)&this[0x11].field_10);
  this->vtable = (u32)&PTR_FUN_0061d6d8;
  this[0xf].pad_104[4] = 0xb0;
  this[0xf].pad_104[5] = '\0';
  this[0xf].pad_104[6] = '\0';
  this[0xf].pad_104[7] = '\0';
  this[0xd].field_4 = 0;
  council_wnd = (iptr)this;
  return this;
}
#undef local_10
#undef puStack_c
#undef local_8

/* 005167d9 auto */
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __thiscall council_wnd_dtor(CouncilWindow *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  *(i8 ***)this->pad_0 = &PTR_FUN_0061d6d8;
  (*(i32 *)((char *)&local_8 + 1)) = 0;
  council_wnd = 0;
  (*(i8 *)((char *)&local_8 + 0)) = 8;
  /* inlined unwind funclet 0051689f */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x12ec)); }
  (*(i8 *)((char *)&local_8 + 0)) = 7;
  /* inlined unwind funclet 005168ae */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x12b0)); }
  (*(i8 *)((char *)&local_8 + 0)) = 6;
  /* inlined unwind funclet 005168bd */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x1274)); }
  (*(i8 *)((char *)&local_8 + 0)) = 5;
  /* inlined unwind funclet 005168cc */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x1238)); }
  (*(i8 *)((char *)&local_8 + 0)) = 4;
  /* inlined unwind funclet 005168db */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x11fc)); }
  (*(i8 *)((char *)&local_8 + 0)) = 3;
  /* inlined unwind funclet 005168ea */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x11c0)); }
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  /* inlined unwind funclet 005168f9 */ { dll_free((DllHandle *)(*(int *)((iptr)&this) + 0xe30)); }
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  /* inlined unwind funclet 00516908 */ { dialog_dtor((Dialog *)(*(int *)((iptr)&this) + 0xb3c)); }
  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
  /* inlined unwind funclet 00516917 */ { avi_player_dtor((AviPlayer *)(*(int *)((iptr)&this) + 0x114)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet 00516926 */ { surfwnd_dtor(*(SurfaceWindow **)((iptr)&this)); }
  return;
}
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00516947 auto */
#define dlg_help_pressed (*(int *)((u8 *)&g.d_00631edc))
#define frame_border_width (*(int *)((u8 *)&g.d_0063359c))
#define frame_caption_height (*(int *)((u8 *)&g.d_00633598))
#define local_90 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_8c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_88 (*(i8 (*)[128])(frame_ + FRAME_OFF(8)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(136)))
i32 __thiscall council_wnd_init(ListPaneWindow *this,u32 param_1,int param_2)

{
  bool bVar1;
  i32 uVar2;
  int iVar3;
  int iVar4;
  i8 frame_[FRAME_OFF(144)] __attribute__((aligned(8)));  /* original stack frame */
  
  this[0xd].field_0 = param_1;
  uVar2 = civ_city_art_era(this[0xd].field_0);
  *(i32 *)this[0xc].pad_104 = uVar2;
  wnd_create_with_surface
            ((DibSurface *)this,ADDR(0x631ad4, ((u8 *)&g.d_00631ad4)),0xc02,0,0,frame_border_width * 6 + 0x1c2,
             frame_caption_height * 2 + frame_bevel_width + 0xfc,ADDR(0x6ab6a8, ((u8 *)&g.d_006ab6a8)),ADDR(0x6553d8, ((u8 *)&g.d_006553d8)));
  wnd_set_caption_height((WndBase *)this->pad_48,frame_caption_height);
  ui_set_button_font(ADDR(0x6cec90, ((u8 *)&g.d_006cec90)));
  council_create_buttons((DibSurface *)this);
  council_draw_background((DibSurface *)this);
  wnd_repaint((SurfaceWindow *)this);
  for (local_90 = 0; local_90 < 5; local_90++) {
    uVar2 = council_advisor_opinion(this[0xd].field_0,local_90);
    *(i32 *)(this[0xc].pad_104 + local_90 * 4 + 4) = uVar2;
  }
  if (param_2 != 0) {
    while( true ) {
      iVar3 = popup_game(ADDR(0x631ad8, ((u8 *)&g.d_00631ad8)));
      iVar4 = dlg_help_pressed;
      if ((iVar3 != 0) || (dlg_help_pressed == 0)) goto LAB_00516b87;
      if (dlg_help_pressed == 6) break;
      bVar1 = false;
      while (!bVar1) {
        iVar3 = dlg_input_number_game(ADDR(0x631ae8, ((u8 *)&g.d_00631ae8)),0,(iptr)&local_8c);
        if (iVar3 != 0) {
          return 0;
        }
        if (((0 < local_8c) && (local_8c < 8)) && ((iVar4 != 5 || (local_8c < 7)))) {
          *(int *)(this[0xc].pad_104 + iVar4 * 4) = local_8c;
          bVar1 = true;
        }
      }
    }
    this[0xd].field_4 = 1;
LAB_00516b87:
    bVar1 = false;
    while ((!bVar1 && (iVar4 = dlg_input_number_game(ADDR(0x631af8, ((u8 *)&g.d_00631af8)),0,(iptr)&local_8c), iVar4 == 0))) {
      if ((-1 < local_8c) && (local_8c < 3)) {
        *(int *)this[0xc].pad_104 = local_8c;
        bVar1 = true;
      }
    }
  }
  if (civs[this[0xd].field_0].government == '\0') {
    this[0xd].field_4 = 1;
  }
  else {
    for (local_90 = 0; local_90 < 5; local_90++) {
      str_clear((iptr)(this[0xd].pad_48 + local_90 * 3 - 0x40));
    }
    str_append((iptr)&this[0xd].field_8,ADDR(0x631b08, ((u8 *)&g.d_00631b08)));
    str_append((iptr)((int)&this[0xd].field_8 + 3),ADDR(0x631b0c, ((u8 *)&g.d_00631b0c)));
    str_append((iptr)((int)&this[0xd].field_c + 2),ADDR(0x631b10, ((u8 *)&g.d_00631b10)));
    str_append((iptr)((int)&this[0xd].field_10 + 1),ADDR(0x631b14, ((u8 *)&g.d_00631b14)));
    str_append((iptr)&this[0xd].field_14,ADDR(0x631b18, ((u8 *)&g.d_00631b18)));
    for (local_90 = 0; local_90 < 5; local_90++) {
      str_append_int((iptr)(this[0xd].pad_48 + local_90 * 3 - 0x40),
                         *(i32 *)(this[0xc].pad_104 + local_90 * 4 + 4));
    }
  }
  if (this[0xd].field_4 != 0) {
    ctrl_disable((Control *)(this + 0x10));
    ctrl_disable((Control *)&this[0x10].field_3c);
    ctrl_disable((Control *)(this[0x10].pad_48 + 0x30));
    ctrl_disable((Control *)(this[0x10].pad_48 + 0x6c));
    ctrl_disable((Control *)(this[0x10].pad_48 + 0xa8));
  }
  str_clear((iptr)(this[0xc].pad_48 + 0x9c));
  text_clear();
  if (this[0xd].field_4 == 0) {
    text_append(ADDR(0x631b1c, ((u8 *)&g.d_00631b1c)));
  }
  else {
    text_append(ADDR(0x631b24, ((u8 *)&g.d_00631b24)));
  }
  text_append_int(*(iptr *)this[0xc].pad_104);
  str_append((iptr)(this[0xc].pad_48 + 0x9c),ADDR(0x679640, ((u8 *)&g.d_00679640)));
  if ((this[0xd].field_4 == 0) &&
     (iVar4 = council_load_speech((WindowObjectView *)this,0), iVar4 == 0)) {
    uVar2 = 0;
  }
  else {
    dialog_init
              ((Dialog *)&this[10].field_24,(iptr)this,(iptr)this,
               (iptr)(this[0xf].pad_104 + 8),0x84008);
    avi_player_create_child((MediaWindow *)&this->style_flags,ADDR(0x631b2c, ((u8 *)&g.d_00631b2c)),0x200,0,0,(iptr)this);
    str_clear((iptr)local_88);
    str_append((iptr)local_88,ADDR(0x631b30, ((u8 *)&g.d_00631b30)));
    str_append((iptr)local_88,(iptr)(this[0xc].pad_48 + 0x9c));
    str_append((iptr)local_88,ADDR(0x631b3c, ((u8 *)&g.d_00631b3c)));
    iVar4 = file_resolve_path((iptr)local_88);
    if (iVar4 == 0) {
      uVar2 = 0;
    }
    else {
      local_8 = avi_player_open((AviPlayerOpenView *)&this->style_flags,(iptr)local_88);
      if (local_8 == 0) {
        avi_player_set_palette((DibSurface *)&this->style_flags,ADDR(0x6ab6a8, ((u8 *)&g.d_006ab6a8)));
        wnd_set_palette((WndBase *)&this[1].field_40,ADDR(0x6ab6a8, ((u8 *)&g.d_006ab6a8)));
        avi_player_set_end_callback((AviPlayerEndCbSetView *)&this->style_flags,ADDR(0x40188e, council_on_video_end));
        council_draw_advisor_frames(this);
        uVar2 = 1;
      }
      else {
        if (local_8 == -0x7ffbfeac) {
          popup_game(ADDR(0x631b44, ((u8 *)&g.d_00631b44)));
        }
        uVar2 = 0;
      }
    }
  }
  return uVar2;
}
#undef dlg_help_pressed
#undef frame_border_width
#undef frame_caption_height
#undef local_90
#undef local_8c
#undef local_88
#undef local_8

/* 00516fd4 auto */
#define frame_border_width (*(int *)((u8 *)&g.d_0063359c))
#define frame_caption_height (*(int *)((u8 *)&g.d_00633598))
void __thiscall council_wnd_run_modal(ListPaneWindow *this)

{
  dlg_set_palette(ADDR(0x6ab6a8, ((u8 *)&g.d_006ab6a8)));
  screen_fade_out();
  wnd_set_palette((WndBase *)&main_frame_wnd,ADDR(0x6ab6a8, ((u8 *)&g.d_006ab6a8)));
  wnd_center((WndCenterView *)this->pad_48);
  ctrl_show_and_redraw((Control *)&this[0x10].field_3c);
  ctrl_show_and_redraw((Control *)(this[0x10].pad_48 + 0x30));
  ctrl_show_and_redraw((Control *)(this[0x10].pad_48 + 0xa8));
  ctrl_show_and_redraw((Control *)(this[0x10].pad_48 + 0x6c));
  ctrl_show_and_redraw((Control *)(this + 0x10));
  ctrl_show_and_redraw((Control *)&this[0x11].field_10);
  dlg_show_modal((Dialog *)&this[10].field_24,0);
  window_show((WindowObjectView *)this);
  wnd_flush_paint();
  if (this[0xd].field_4 != 0) {
    wnd_move_xy
              ((WndMoveView *)&this[1].field_40,frame_border_width + 1,frame_caption_height + 1);
    window_show((WindowObjectView *)&this->style_flags);
    wnd_flush_paint();
    avi_player_play((AviPlayerPlayView *)&this->style_flags);
  }
  if (2 < game.multiplayer) {
    wnd_set_modal_idle_callback((ModalMenuWindow *)this->pad_48,ADDR(0x403585, net_modal_idle_poll));
  }
  wnd_run_modal_loop((ModalMenuWindow *)this->pad_48);
  wnd_set_modal_idle_callback((ModalMenuWindow *)this->pad_48,0);
  snd_wave_stop_all();
  council_draw_background((DibSurface *)this);
  wnd_hide((WndBase *)this->pad_48);
  wnd_flush_paint();
  dialog_close((Dialog *)&this[10].field_24);
  wnd_set_palette((WndBase *)&main_frame_wnd,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
  screen_fade_in();
  dlg_set_palette(ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)));
  return;
}
#undef frame_border_width
#undef frame_caption_height

/* 00517158 auto */
#define frame_border_width (*(int *)((u8 *)&g.d_0063359c))
#define frame_caption_height (*(int *)((u8 *)&g.d_00633598))
#define local_20 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(12)))
void __thiscall council_draw_background(DibSurface *this)

{
  int iVar1;
  i32 uVar2;
  int iVar3;
  int iVar4;
  RECT *lprcSrc;
  iptr iVar5;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = frame_caption_height + frame_bevel_width * -2;
  uVar2 = surface_get_width(this);
  gfx_tile_fill((iptr)this,ADDR(0x6abae0, ((u8 *)&g.d_006abae0)),0,frame_bevel_width,uVar2,iVar1,0,frame_bevel_width);
  iVar3 = frame_bevel_width + frame_caption_height + 0x7a;
  gfx_tile_fill((iptr)this,ADDR(0x6abae0, ((u8 *)&g.d_006abae0)),0,iVar3,uVar2,iVar1,0,iVar3);
  iVar1 = surface_get_height(this);
  iVar1 -= (frame_bevel_width + 0x1e);
  gfx_tile_fill((iptr)this,ADDR(0x6abae0, ((u8 *)&g.d_006abae0)),0,iVar1,uVar2,0x1e,0,iVar1);
  uVar2 = surface_get_height(this);
  iVar3 = frame_border_width + frame_bevel_width * -2;
  gfx_tile_fill((iptr)this,ADDR(0x6abae0, ((u8 *)&g.d_006abae0)),frame_bevel_width,0,iVar3,uVar2,frame_bevel_width,0);
  iVar1 = surface_get_width(this);
  iVar1 -= (frame_bevel_width + iVar3);
  gfx_tile_fill((iptr)this,ADDR(0x6abae0, ((u8 *)&g.d_006abae0)),iVar1,0,iVar3,uVar2,iVar1,0);
  iVar1 = frame_bevel_width * 2;
  local_1c = frame_bevel_width + frame_border_width + 0x5a;
  iVar4 = frame_caption_height - frame_bevel_width;
  for (local_20 = 0; local_20 < 4; local_20++) {
    gfx_tile_fill((iptr)this,ADDR(0x6abae0, ((u8 *)&g.d_006abae0)),local_1c,iVar4,iVar3,iVar1 + 0x7a,local_1c,iVar4);
    local_1c = local_1c + frame_border_width + 0x5a;
  }
  SetRect(&local_14,frame_border_width - frame_bevel_width,iVar4,
          frame_bevel_width * 2 + (frame_border_width - frame_bevel_width) + 0x5a,frame_bevel_width * 2 + iVar4 + 0x7a);
  for (local_20 = 0; local_20 < 5; local_20++) {
    for (local_18 = 0; local_18 < frame_bevel_width; local_18++) {
      gfx_draw_bevel_rect((iptr)this,(iptr)&local_14,frame_shadow_color,frame_highlight_color);
      InflateRect(&local_14,-1,-1);
    }
    surface_fill_rect(this,(iptr)&local_14,10);
    InflateRect(&local_14,frame_bevel_width,frame_bevel_width);
    OffsetRect(&local_14,frame_border_width + 0x5a,0);
  }
  iVar1 = surface_get_height(this);
  iVar1 = (iVar1 - 0x1e) - frame_bevel_width;
  iVar3 = surface_get_width(this);
  iVar3 = (iVar3 - frame_border_width) + frame_bevel_width;
  iVar4 = surface_get_height(this);
  SetRect((LPRECT)&this[0x3e].field_40,frame_border_width - frame_bevel_width,iVar4 - 0x82 + frame_bevel_width * -3
          ,iVar3,iVar1);
  for (local_18 = 0; local_18 < frame_bevel_width; local_18++) {
    gfx_draw_bevel_rect((iptr)this,(iptr)&this[0x3e].field_40,frame_shadow_color,frame_highlight_color);
    InflateRect((LPRECT)&this[0x3e].field_40,-1,-1);
  }
  surface_fill_rect(this,(iptr)&this[0x3e].field_40,0x1d);
  InflateRect((LPRECT)&this[0x3e].field_40,-2,-2);
  lprcSrc = (RECT *)surface_get_rect(this);
  CopyRect(&local_14,lprcSrc);
  for (local_18 = 0; local_18 < frame_bevel_width; local_18++) {
    gfx_draw_bevel_rect((iptr)this,(iptr)&local_14,frame_highlight_color,frame_shadow_color);
    InflateRect(&local_14,-1,-1);
  }
  text_clear();
  if (game_language == 1) {
    iVar5 = label_string(*(i32 *)(label_string_ids + 0x4ac));
    text_append(iVar5);
    text_append_space();
    iVar5 = civ_get_adjective(this[0x33].field_14);
    text_append(iVar5);
  }
  else {
    iVar5 = civ_get_adjective(this[0x33].field_14);
    text_append(iVar5);
    if (game_language == 2) {
      text_append(ADDR(0x631b58, ((u8 *)&g.d_00631b58)));
    }
    text_append_space();
    iVar5 = label_string(*(i32 *)(label_string_ids + 0x4ac));
    text_append(iVar5);
  }
  iVar3 = surface_get_width(this);
  iVar4 = font_text_width((GameFont *)&caption_font,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  iVar1 = frame_bevel_width;
  iVar3 = (iVar3 - iVar4) / 2;
  iVar4 = frame_bevel_width + 1;
  gfx_set_text_color_index(10);
  surface_draw_text(this,ADDR(0x6ab190, ((u8 *)&g.d_006ab190)),ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar3 + 1,iVar1 + 2,5);
  gfx_set_text_color_index(0x1a);
  surface_draw_text(this,ADDR(0x6ab190, ((u8 *)&g.d_006ab190)),ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar3,iVar4,5);
  return;
}
#undef frame_border_width
#undef frame_caption_height
#undef local_20
#undef local_1c
#undef local_18
#undef local_14

/* 00517673 auto */
#define frame_border_width (*(int *)((u8 *)&g.d_0063359c))
#define frame_caption_height (*(int *)((u8 *)&g.d_00633598))
#define local_34 (*(DibSurface * *)(frame_ + FRAME_OFF(4)))
#define local_30 (*(DibSurface * *)(frame_ + FRAME_OFF(8)))
#define local_2c (*(DibSurface * *)(frame_ + FRAME_OFF(12)))
#define local_28 (*(DibSurface * *)(frame_ + FRAME_OFF(16)))
#define local_24 (*(DibSurface * *)(frame_ + FRAME_OFF(20)))
#define local_20 (*(DibSurface * *)(frame_ + FRAME_OFF(24)))
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(36)))
void __thiscall council_create_buttons(DibSurface *this)

{
  int iVar1;
  iptr iVar2;
  int iVar3;
  int iVar4;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = (frame_caption_height - 0x16 >> 1) + frame_caption_height;
  SetRect(&local_14,frame_border_width + 7,iVar1 + 0x79,frame_border_width + 0x52,iVar1 + 0x8f);
  if (this == (DibSurface *)0x0) {
    local_20 = (DibSurface *)0x0;
  }
  else {
    local_20 = this + 1;
  }
  iVar2 = label_string(*(i32 *)(label_string_ids + 0x26c));
  button_create_with_callback
            ((Control *)&this[0x42].field_20,(iptr)local_20,0,(iptr)&local_14,0x21,iVar2);
  button_set_callback((Control *)&this[0x42].field_20,ADDR(0x401b22, council_on_advisor_button));
  OffsetRect(&local_14,frame_border_width + 0x5a,0);
  if (this == (DibSurface *)0x0) {
    local_24 = (DibSurface *)0x0;
  }
  else {
    local_24 = this + 1;
  }
  iVar2 = label_string(*(i32 *)(label_string_ids + 0x16c));
  button_create_with_callback
            ((Control *)&this[0x3f].field_8,(iptr)local_24,1,(iptr)&local_14,0x21,iVar2);
  button_set_callback((Control *)&this[0x3f].field_8,ADDR(0x401b22, council_on_advisor_button));
  OffsetRect(&local_14,frame_border_width + 0x5a,0);
  if (this == (DibSurface *)0x0) {
    local_28 = (DibSurface *)0x0;
  }
  else {
    local_28 = this + 1;
  }
  iVar2 = label_string(*(i32 *)(label_string_ids + 0x114));
  button_create_with_callback
            ((Control *)&this[0x41].field_2c,(iptr)local_28,2,(iptr)&local_14,0x21,iVar2);
  button_set_callback((Control *)&this[0x41].field_2c,ADDR(0x401b22, council_on_advisor_button));
  OffsetRect(&local_14,frame_border_width + 0x5a,0);
  if (this == (DibSurface *)0x0) {
    local_2c = (DibSurface *)0x0;
  }
  else {
    local_2c = this + 1;
  }
  iVar2 = label_string(*(i32 *)(label_string_ids + 0x6e0));
  button_create_with_callback
            ((Control *)&this[0x40].field_38,(iptr)local_2c,3,(iptr)&local_14,0x21,iVar2);
  button_set_callback((Control *)&this[0x40].field_38,ADDR(0x401b22, council_on_advisor_button));
  OffsetRect(&local_14,frame_border_width + 0x5a,0);
  if (this == (DibSurface *)0x0) {
    local_30 = (DibSurface *)0x0;
  }
  else {
    local_30 = this + 1;
  }
  iVar2 = label_string(*(i32 *)(label_string_ids + 0x6e4));
  button_create_with_callback
            ((Control *)&this[0x3f].field_44,(iptr)local_30,4,(iptr)&local_14,0x21,iVar2);
  button_set_callback((Control *)&this[0x3f].field_44,ADDR(0x401b22, council_on_advisor_button));
  iVar1 = surface_get_height(this);
  iVar1 = (iVar1 - frame_bevel_width) - 1;
  iVar3 = surface_get_width(this);
  iVar3 -= frame_border_width;
  iVar4 = surface_get_height(this);
  SetRect(&local_14,frame_border_width,iVar4 - 0x1d,iVar3,iVar1);
  if (this == (DibSurface *)0x0) {
    local_34 = (DibSurface *)0x0;
  }
  else {
    local_34 = this + 1;
  }
  iVar2 = label_string(*(i32 *)(label_string_ids + 0x3fc));
  button_create_with_callback
            ((Control *)&this[0x43].field_14,(iptr)local_34,0xca,(iptr)&local_14,0x21,iVar2);
  button_set_callback((Control *)&this[0x43].field_14,ADDR(0x401b22, council_on_advisor_button));
  return;
}
#undef frame_border_width
#undef frame_caption_height
#undef local_34
#undef local_30
#undef local_2c
#undef local_28
#undef local_24
#undef local_20
#undef local_14

/* 005179a3 auto */
#define text_line_cursor (*(char * *)((u8 *)&g.d_00673f14))
#define local_1c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_10 (*(uint *)(frame_ + FRAME_OFF(16)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(24)))
i32 __thiscall council_load_speech(WindowObjectView *this,uptr param_1)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  u32 uVar4;
  i8 *puVar5;
  int iVar6;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_10 = 0;
  local_8 = 0;
  if (4 < (int)param_1) {
    return 0;
  }
  iVar3 = text_open_section((iptr)(this + 0x38d),(int)&this[0x39d].field_0 + param_1 * 3);
  if (iVar3 != 0) {
    return 0;
  }
  iVar3 = text_read_line(1);
  if (iVar3 != 0) {
    for (local_1c = 0; local_1c < 5; local_1c++) {
      this[local_1c + 0x3a1].field_0 = 0;
    }
    this[0x3a1].field_0 = param_1;
    uVar4 = text_next_int();
    this[0x3a4].field_0 = uVar4;
    uVar4 = text_next_int();
    this[0x3a7].field_0 = uVar4;
    str_clear((iptr)(this + 0x3aa));
    str_trim((iptr)text_line_cursor);
    str_append((iptr)(this + 0x3aa),(iptr)text_line_cursor);
    local_18 = 1;
    bVar2 = true;
    bVar1 = false;
LAB_00517ae5:
    if ((2 < local_18) || (this[local_18 + 0x3a1].field_0 == 0xffffffff)) goto LAB_00517dae;
    if ((!bVar1) && (iVar3 = text_read_line(1), iVar3 == 0)) goto LAB_00517db5;
    bVar1 = false;
    puVar5 = (i8 *)text_next_token();
    switch(*puVar5) {
    case 0x23:
      bVar1 = bVar2;
      goto LAB_00517ae5;
    case 0x3b:
      goto LAB_00517ae5;
    case 0x41:
    case 0x61:
      param_1 = 4;
      break;
    case 0x45:
    case 0x65:
      this[local_18 + 0x3a1].field_0 = 0xffffffff;
      goto LAB_00517ae5;
    case 0x46:
    case 0x66:
      param_1 = 3;
      break;
    case 0x4d:
    case 0x6d:
      param_1 = 0;
      break;
    case 0x52:
    case 0x72:
      goto switchD_00517c0c_caseD_52;
    case 0x53:
    case 0x73:
      param_1 = 1;
      break;
    case 0x54:
    case 0x74:
      param_1 = 2;
    }
    if ((local_10 & 1 << ((byte)param_1 & 0x1f)) == 0) {
      if ((puVar5[1] == '\0') || (uVar4 = _atoi(puVar5 + 1), uVar4 == this[param_1 + 0x396].field_0)
         ) {
        this[local_18 + 0x3a1].field_0 = param_1;
        uVar4 = text_next_int();
        this[local_18 + 0x3a4].field_0 = uVar4;
        uVar4 = text_next_int();
        this[local_18 + 0x3a7].field_0 = uVar4;
        str_clear((int)this + local_18 * 0xff + 0xea8);
        str_trim((iptr)text_line_cursor);
        if (*text_line_cursor != '*') {
          str_append((int)this + local_18 * 0xff + 0xea8,(iptr)text_line_cursor);
        }
        local_18++;
        bVar2 = true;
        local_10 = local_10 | 1 << ((byte)param_1 & 0x1f);
      }
      else {
        bVar2 = false;
      }
    }
    else {
      bVar2 = false;
    }
    goto LAB_00517ae5;
  }
LAB_00517db5:
  text_close_file();
  return local_8;
LAB_00517dae:
  local_8 = 1;
  goto LAB_00517db5;
switchD_00517c0c_caseD_52:
  iVar3 = _atoi(puVar5 + 1);
  iVar6 = rand_range(1,10);
  if (iVar6 <= iVar3) {
    bVar2 = false;
  }
  bVar1 = iVar6 > iVar3;
  goto LAB_00517ae5;
}
#undef text_line_cursor
#undef local_1c
#undef local_18
#undef local_10
#undef local_8

/* 00517dd3 auto */
#define local_28 (*(GameFont *)(frame_ + FRAME_OFF(0)))
#define local_20 (*(tagRECT *)(frame_ + FRAME_OFF(8)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(24)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(28)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(32)))
void __thiscall council_draw_speech(SurfaceWindow *this,int param_1)

{
  int iVar1;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  font_init(&local_28,0,0xe);
  local_8 = 0;
  if ((*(int *)(this[0x10].pad_48 + 0x20) < 0) || (2 < *(int *)(this[0x10].pad_48 + 0x20))) {
    local_8 = 0xffffffff;
    /* inlined unwind funclet 00517fe4 */ { font_destroy((GameFont *)((iptr)&local_28)); }
  }
  else {
    if (param_1 != 1) {
      surface_fill_rect((DibSurface *)this,(iptr)(this[0x10].pad_48 + 0x28),0x1d);
      this[0x10].pad_48[0x24] = 2;
      this[0x10].pad_48[0x25] = '\0';
      this[0x10].pad_48[0x26] = '\0';
      this[0x10].pad_48[0x27] = '\0';
    }
    if (param_1 == -1) {
      wnd_repaint(this);
      local_8 = 0xffffffff;
      /* inlined unwind funclet 00517fe4 */ { font_destroy((GameFont *)((iptr)&local_28)); }
    }
    else {
      local_20.bottom = *(LONG *)(this[0x10].pad_48 + 0x34);
      local_20.left = *(int *)(this[0x10].pad_48 + 0x28) + 2;
      local_20.right = *(int *)(this[0x10].pad_48 + 0x30) - 2;
      local_20.top = *(int *)(this[0x10].pad_48 + 0x2c) + *(int *)(this[0x10].pad_48 + 0x24);
      dialog_set_font((DialogTextView *)(this[10].pad_48 + 0x2c),(iptr)&local_28);
      if (this[0xd].pad_48[*(int *)(this[0x10].pad_48 + 0x20) * 0xff + 0x5c] != '\0') {
        OffsetRect(&local_20,1,1);
        gfx_set_text_color_index(0x25);
        surface_draw_text_rect
                  ((DibSurface *)this,(iptr)&local_28,
                   (iptr)(this[0xd].pad_48 + *(int *)(this[0x10].pad_48 + 0x20) * 0xff + 0x5c),
                   (iptr)&local_20,1);
        OffsetRect(&local_20,-1,-1);
        gfx_set_text_color_index(10);
        surface_draw_text_rect
                  ((DibSurface *)this,(iptr)&local_28,
                   (iptr)(this[0xd].pad_48 + *(int *)(this[0x10].pad_48 + 0x20) * 0xff + 0x5c),
                   (iptr)&local_20,1);
        iVar1 = font_line_spacing(&local_28);
        *(int *)(this[0x10].pad_48 + 0x24) = *(int *)(this[0x10].pad_48 + 0x24) + iVar1;
        iVar1 = font_text_width
                          (&local_28,
                           (iptr)(this[0xd].pad_48 +
                                 *(int *)(this[0x10].pad_48 + 0x20) * 0xff + 0x5c));
        if (local_20.right - local_20.left < iVar1) {
          iVar1 = font_line_spacing(&local_28);
          *(int *)(this[0x10].pad_48 + 0x24) = *(int *)(this[0x10].pad_48 + 0x24) + iVar1;
        }
      }
      wnd_repaint(this);
      wnd_flush_paint();
      local_8 = 0xffffffff;
      /* inlined unwind funclet 00517fe4 */ { font_destroy((GameFont *)((iptr)&local_28)); }
    }
  }
  return;
}
#undef local_28
#undef local_20
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00518007 auto */
#define frame_border_width (*(int *)((u8 *)&g.d_0063359c))
#define frame_caption_height (*(int *)((u8 *)&g.d_00633598))
#define local_98 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_94 (*(DibSurface *)(frame_ + FRAME_OFF(4)))
#define local_4c (*(Sprite *)(frame_ + FRAME_OFF(76)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(136)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(140)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(144)))
void __thiscall council_draw_advisor_frames(ListPaneWindow *this)

{
  int iVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(152)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  surface_ctor(&local_94);
  local_8 = 0;
  sprite_init(&local_4c);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  if (this[0xd].field_4 == 0) {
    for (local_98 = 0; local_98 < 5; local_98++) {
      iVar1 = text_open_section((iptr)(this[0xc].pad_48 + 0x9c),
                                 (iptr)(this[0xd].pad_48 + local_98 * 3 - 0x40));
      if (iVar1 != 0) {
        local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
        /* inlined unwind funclet 005181ab */ { sprite_destroy((Sprite *)((iptr)&local_4c)); }
        local_8 = 0xffffffff;
        /* inlined unwind funclet 005181b4 */ { surface_dtor((DibSurface *)((iptr)&local_94)); }
        goto LAB_005181ca;
      }
      iVar1 = text_read_line(1);
      if (iVar1 == 0) {
        local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
        /* inlined unwind funclet 005181ab */ { sprite_destroy((Sprite *)((iptr)&local_4c)); }
        local_8 = 0xffffffff;
        /* inlined unwind funclet 005181b4 */ { surface_dtor((DibSurface *)((iptr)&local_94)); }
        goto LAB_005181ca;
      }
      uVar2 = text_next_int();
      avi_player_show_frame(&this->style_flags,uVar2);
      avi_player_draw_to
                ((DibSurface *)&this->style_flags,(iptr)this,
                 (frame_border_width + 0x5a) * local_98 + frame_border_width + 1,frame_caption_height + 1);
      text_close_file();
    }
  }
  else {
    avi_player_show_frame(&this->style_flags,1);
    avi_player_draw_to
              ((DibSurface *)&this->style_flags,(iptr)this,frame_border_width + 2,frame_caption_height + 2);
  }
  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
  /* inlined unwind funclet 005181ab */ { sprite_destroy((Sprite *)((iptr)&local_4c)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet 005181b4 */ { surface_dtor((DibSurface *)((iptr)&local_94)); }
LAB_005181ca:
  return;
}
#undef frame_border_width
#undef frame_caption_height
#undef local_98
#undef local_94
#undef local_4c
#undef uStack_10
#undef puStack_c
#undef local_8

/* 005181d8 auto */
#define council_video_busy_i32 (*(i32 *)((u8 *)&g.d_00631ac8))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl council_on_advisor_button(uptr param_1)

{
  iptr this;
  int iVar1;
  
  this = council_wnd;
  council_video_busy_i32 = 1;
  snd_wave_stop_all();
  avi_player_pause((AviPlayerPauseView *)(this + 0x114));
  if (param_1 == 0xca) {
    council_draw_speech((SurfaceWindow *)this,0xffffffff);
    wnd_flush_paint();
    wnd_end_modal_loop((ModalMenuWindow *)(this + 0x48));
  }
  else if (*(int *)(this + 0xe70) == 0) {
    council_draw_speech((SurfaceWindow *)this,0xffffffff);
    *(i32 *)(this + 0x11a8) = 0;
    iVar1 = council_load_speech((WindowObjectView *)this,param_1);
    if (iVar1 == 0) {
      council_draw_speech((SurfaceWindow *)this,0xffffffff);
      wnd_flush_paint();
      wnd_end_modal_loop((ModalMenuWindow *)(this + 0x48));
    }
    else {
      wnd_hide((WndBase *)(this + 0x15c));
      council_move_video_to_slot((void *)this,param_1);
      if ((int)param_1 < 5) {
        council_draw_speech((SurfaceWindow *)this,0);
        avi_player_show_frame((void *)(this + 0x114),
                     *(i32 *)(this + 0xe90 + *(int *)(this + 0x11a8) * 4));
        window_show((WindowObjectView *)(this + 0x114));
        avi_player_play_range
                  ((AviPlayerRangeView *)(this + 0x114),
                   *(i32 *)(this + 0xe90 + *(int *)(this + 0x11a8) * 4),
                   *(i32 *)(this + 0xe9c + *(int *)(this + 0x11a8) * 4));
        *(int *)(this + 0x11a8) = *(int *)(this + 0x11a8) + 1;
      }
      council_video_busy_i32 = 0;
    }
  }
  return;
}
#undef council_video_busy_i32

/* 00518342 auto */
#define frame_border_width (*(int *)((u8 *)&g.d_0063359c))
#define frame_caption_height (*(int *)((u8 *)&g.d_00633598))
void __thiscall council_move_video_to_slot(void *this,iptr param_1)

{
  if (param_1 < 5) {
    wnd_move_xy
              ((WndMoveView *)((int)this + 0x15c),(frame_border_width + 0x5a) * param_1 + frame_border_width + 1,
               frame_caption_height + 1);
  }
  return;
}
#undef frame_border_width
#undef frame_caption_height

/* 00518392 auto */
i32 __thiscall council_advisor_from_letter(void *this,i8 *param_1)

{
  i32 uVar1;
  
  switch(*param_1) {
  case 0x41:
  case 0x61:
    uVar1 = 4;
    break;
  default:
    uVar1 = 0xffffffff;
    break;
  case 0x46:
  case 0x66:
    uVar1 = 3;
    break;
  case 0x4d:
  case 0x6d:
    uVar1 = 0;
    break;
  case 0x53:
  case 0x73:
    uVar1 = 1;
    break;
  case 0x54:
  case 0x74:
    uVar1 = 2;
  }
  return uVar1;
}

/* 00518471 auto */
#define council_video_busy_i32 (*(i32 *)((u8 *)&g.d_00631ac8))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl council_on_video_end(void)

{
  iptr this;
  
  this = council_wnd;
  council_video_busy_i32 = 1;
  if (*(int *)(council_wnd + 0xe70) == 0) {
    wnd_hide((WndBase *)(council_wnd + 0x15c));
    if ((*(int *)(this + 0x11a8) < 3) && (-1 < *(int *)(this + 0xe84 + *(int *)(this + 0x11a8) * 4))
       ) {
      council_move_video_to_slot((void *)this,*(iptr *)(this + 0xe84 + *(int *)(this + 0x11a8) * 4));
      council_draw_speech((SurfaceWindow *)this,1);
      avi_player_show_frame((void *)(this + 0x114),
                   *(i32 *)(this + 0xe90 + *(int *)(this + 0x11a8) * 4));
      window_show((WindowObjectView *)(this + 0x114));
      avi_player_play_range
                ((AviPlayerRangeView *)(this + 0x114),
                 *(i32 *)(this + 0xe90 + *(int *)(this + 0x11a8) * 4),
                 *(i32 *)(this + 0xe9c + *(int *)(this + 0x11a8) * 4));
      *(int *)(this + 0x11a8) = *(int *)(this + 0x11a8) + 1;
    }
  }
  wnd_flush_paint();
  council_video_busy_i32 = 0;
  return;
}
#undef council_video_busy_i32

/* 00518582 auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
i32 __cdecl council_advisor_opinion(iptr civ,i32 param_2)

{
  i32 uVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (council_wnd != 0) {
    local_8 = *(i32 *)(council_wnd + 0xe54);
  }
  switch(param_2) {
  case 0:
    uVar1 = council_military_advice(civ,local_8);
    break;
  case 1:
    uVar1 = council_science_advice(civ,local_8);
    break;
  case 2:
    uVar1 = council_trade_advice(civ,local_8);
    break;
  case 3:
    uVar1 = council_foreign_advice(civ,local_8);
    break;
  default:
    uVar1 = council_attitude_advice(civ,local_8);
  }
  return uVar1;
}
#undef local_8

/* 00522dfa auto */
#define leader (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl leaders_reset_custom_names(void)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (leader = 0; leader < 0x15; leader++) {
    if (leaders[leader].leader_name < 1) {
      leaders[leader].leader_name = ~leaders[leader].leader_name + 1;
    }
    if (leaders[leader].plural < 1) {
      leaders[leader].plural = ~leaders[leader].plural + 1;
    }
    if (leaders[leader].adjective < 1) {
      leaders[leader].adjective = ~leaders[leader].adjective + 1;
    }
    for (local_8 = 0; local_8 < 7; local_8++) {
      if (leaders[leader].titles[local_8][0] < 1) {
        *(ushort *)&leaders[leader].titles[local_8][0] =
             ~*(ushort *)&leaders[leader].titles[local_8][0] + 1;
      }
      if (leaders[leader].titles[local_8][1] < 1) {
        *(ushort *)&leaders[leader].titles[local_8][1] =
             ~*(ushort *)&leaders[leader].titles[local_8][1] + 1;
      }
    }
  }
  return;
}
#undef leader
#undef local_8

/* 0059c575 auto */
void __cdecl casualty_log_add(iptr unit,iptr unit2,iptr param_3,iptr param_4,i32 param_5)

{
  i32 uVar1;
  char *_Source;
  size_t _Count;
  
  *(ushort *)
   (&casualty_log_unit_types +
   units[unit].owner * 0x27d8 + *(int *)(&casualty_log_next + units[unit].owner * 4) * 0x22) =
       (ushort)units[unit].type;
  *(short *)(&casualty_log_x +
            units[unit].owner * 0x27d8 +
            *(int *)(&casualty_log_next + units[unit].owner * 4) * 0x22) = (short)param_4;
  *(i16 *)
   (&casualty_log_y +
   units[unit].owner * 0x27d8 + *(int *)(&casualty_log_next + units[unit].owner * 4) * 0x22) =
       (i16)param_5;
  *(short *)(&casualty_log_years +
            units[unit].owner * 0x27d8 +
            *(int *)(&casualty_log_next + units[unit].owner * 4) * 0x22) = (short)param_3;
  uVar1 = civ_color_secondary((int)units[unit2].owner);
  *(short *)(&casualty_log_killer_colors +
            units[unit].owner * 0x27d8 +
            *(int *)(&casualty_log_next + units[unit].owner * 4) * 0x22) = (short)uVar1;
  _Count = 0x18;
  _Source = (char *)civ_name_plural((int)units[unit2].owner);
  _strncpy((char *)(*(int *)(&casualty_log_next + units[unit].owner * 4) * 0x22 +
                    units[unit].owner * 0x27d8 + ADDR(0x6af2aa, ((u8 *)&g.d_006af2a8 + 2))),_Source,_Count);
  (&casualty_log_killer_name_ends)
  [units[unit].owner * 0x27d8 + *(int *)(&casualty_log_next + units[unit].owner * 4) * 0x22] = 0;
  *(int *)(&casualty_log_next + units[unit].owner * 4) =
       *(int *)(&casualty_log_next + units[unit].owner * 4) + 1;
  if (*(int *)(&casualty_log_next + units[unit].owner * 4) == 300) {
    *(i32 *)(&casualty_log_next + units[unit].owner * 4) = 0;
  }
  if (*(int *)(&casualty_log_next + units[unit].owner * 4) ==
      *(int *)(&casualty_log_first + units[unit].owner * 4)) {
    *(int *)(&casualty_log_first + units[unit].owner * 4) =
         *(int *)(&casualty_log_first + units[unit].owner * 4) + 1;
    if (*(int *)(&casualty_log_first + units[unit].owner * 4) == 300) {
      *(i32 *)(&casualty_log_first + units[unit].owner * 4) = 0;
    }
  }
  else {
    *(int *)(&casualty_counts + units[unit].owner * 4) =
         *(int *)(&casualty_counts + units[unit].owner * 4) + 1;
  }
  if (-1 < casualty_window_report_id) {
    wnd_repaint((SurfaceWindow *)&casualty_window);
  }
  return;
}
