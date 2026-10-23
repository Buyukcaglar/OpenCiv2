/* The game, the advisors, the High Council and the reports: functions translated from the original
 * (tools/gen_c.py, now edited directly), in address order. */
#include "auto_common.h"

/* 00419ed3 auto */
#define i (*(int *)(frame_ + FRAME_OFF(0)))
#define j (*(int *)(frame_ + FRAME_OFF(4)))
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
    for (i = 0; i < 7; i++) {
      for (j = 0; j < 2; j++) {
        if (leaders[leader].titles[i][j] < 1) {
          *(ushort *)&leaders[leader].titles[i][j] =
               ~*(ushort *)&leaders[leader].titles[i][j] + 1;
        }
      }
    }
  }
  return;
}
#undef i
#undef j
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
#define window (*(PictureWindowCore * *)(frame_ + FRAME_OFF(0)))
void __cdecl advisor_on_close_clicked(void)

{
  int active_child;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  active_child = wnd_get_active_child();
  if (active_child == 0) {
    window = (PictureWindowCore *)0x0;
  }
  else {
    window = (PictureWindowCore *)(active_child - 0x48);
  }
  if (window[1].clip_top == 0) {
    picwnd_close(window);
  }
  else {
    wnd_end_modal_loop((ModalMenuWindow *)window->window_2);
  }
  return;
}
#undef window

/* 0042acb0 auto */
#define parent_wnd2 (*(u8 * *)(frame_ + FRAME_OFF(0)))
#define button_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
void __thiscall advisor_add_close_button(ViewWindow *this)

{
  u32 top_y;
  int rect_h;
  iptr label;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  rect_set_xywh((iptr)button_rect,2,0,0x254,0x18);
  top_y = this->client_y;
  rect_h = rect_height((iptr)button_rect);
  rect_offset((iptr)button_rect,this->client_x,(top_y - rect_h) + 0x18e);
  if (this == (ViewWindow *)0x0) {
    parent_wnd2 = (u8 *)0x0;
  }
  else {
    parent_wnd2 = this->window_2;
  }
  label = label_string(*(i32 *)(label_string_ids + 0x51c));
  button_create
            ((Control *)&this->bar_height,(iptr)parent_wnd2,100,(iptr)button_rect,label);
  button_set_callback((Control *)&this->bar_height,(iptr)advisor_on_close_clicked);
  ctrl_set_default_button((Control *)&this->bar_height);
  ctrl_set_cancel_button((Control *)&this->bar_height);
  return;
}
#undef parent_wnd2
#undef button_rect

/* 0042d781 auto */
#define city_specialist_count (*(uint *)((u8 *)&g.d_006a6604))
#define specialist_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define unhappy_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
#define content_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(36)))
#define happy_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(52)))
#define sprite_row (*(int *)(frame_ + FRAME_OFF(68)))
#define spacing (*(int *)(frame_ + FRAME_OFF(72)))
#define i (*(int *)(frame_ + FRAME_OFF(76)))
#define citizen_index (*(uint *)(frame_ + FRAME_OFF(80)))
int __cdecl
advisor_draw_city_citizens(iptr city,int x,i32 y,i32 width,int happy_count,int unhappy_count,
            int angry_count)

{
  int era;
  int specialist;
  i8 *clip_rect;
  i8 *surface;
  int draw_x;
  i32 draw_y;
  i8 frame_[FRAME_OFF(88)] __attribute__((aligned(8)));  /* original stack frame */
  
  spacing = ui_calc_item_spacing((int)cities[city].size,0x1c,width,0,0);
  citizen_index = 0;
  city_specialist_count = cities[city].worked_tiles >> 0x1a;
  for (i = 0; i < happy_count; i++) {
    surface = &advisor_window;
    clip_rect = happy_rect;
    draw_x = x;
    draw_y = y;
    era = civ_city_style_era((int)cities[city].owner);
    sprite_draw
              ((Sprite *)(&citizen_sprites + era * 0x294 + (citizen_index & 1) * 0x3c),(iptr)clip_rect,
               (iptr)surface,draw_x,draw_y);
    x += spacing;
    citizen_index++;
  }
  for (i = 0; i < (int)((int)cities[city].size - (unhappy_count + city_specialist_count + happy_count));
      i = i + 1) {
    surface = &advisor_window;
    clip_rect = content_rect;
    draw_x = x;
    draw_y = y;
    era = civ_city_style_era((int)cities[city].owner);
    sprite_draw
              ((Sprite *)(&citizen_sprites + era * 0x294 + ((citizen_index & 1) * 4 + 8) * 0xf),
               (iptr)clip_rect,(iptr)surface,draw_x,draw_y);
    x += spacing;
    citizen_index++;
  }
  for (i = 0; i < unhappy_count; i++) {
    if (i < unhappy_count - angry_count) {
      sprite_row = 4;
    }
    else {
      sprite_row = 6;
    }
    surface = &advisor_window;
    clip_rect = unhappy_rect;
    draw_x = x;
    draw_y = y;
    era = civ_city_style_era((int)cities[city].owner);
    sprite_draw
              ((Sprite *)(&citizen_sprites + era * 0x294 + ((citizen_index & 1) + sprite_row) * 0x3c),
               (iptr)clip_rect,(iptr)surface,draw_x,draw_y);
    x += spacing;
    citizen_index++;
  }
  for (i = 0; i < (int)city_specialist_count; i++) {
    surface = &advisor_window;
    clip_rect = specialist_rect;
    draw_x = x;
    draw_y = y;
    era = civ_city_style_era((int)cities[city].owner);
    specialist = city_specialist_type(city,i);
    sprite_draw
              ((Sprite *)(&citizen_sprites + era * 0x294 + (specialist * 4 + 0x1c) * 0xf),
               (iptr)clip_rect,(iptr)surface,draw_x,draw_y);
    x += spacing;
  }
  return spacing;
}
#undef city_specialist_count
#undef specialist_rect
#undef unhappy_rect
#undef content_rect
#undef happy_rect
#undef sprite_row
#undef spacing
#undef i
#undef citizen_index

/* 0042da1d auto */
#define advisor_client_width (*(i32 *)((u8 *)&g.d_0063ec3c))
#define advisor_client_x (*(int *)((u8 *)&g.d_0063ec34))
#define advisor_first_row (*(int *)((u8 *)&g.d_0063ef70))
#define advisor_row_height (*(i32 *)((u8 *)&g.d_0063ef80))
#define advisor_page_count_i32 (*(i32 *)((u8 *)&g.d_0063ef68))
#define advisor_list_top_i32 (*(i32 *)((u8 *)&g.d_0063ef78))
#define advisor_list_height_i32 (*(i32 *)((u8 *)&g.d_0063ef7c))
#define row_y (*(int *)(frame_ + FRAME_OFF(0)))
#define row_index (*(uint *)(frame_ + FRAME_OFF(24)))
#define city (*(iptr *)(frame_ + FRAME_OFF(28)))
#define city_count (*(int *)(frame_ + FRAME_OFF(44)))
#define scroll_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(56)))
#define rows_per_page (*(int *)(frame_ + FRAME_OFF(72)))
/* WARNING: Removing unreachable block (ram,0x0042dfd1) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl attitude_advisor_draw(void)

{
  uint next_row;
  ushort recalc_flag;
  int y;
  int bottom;
  int line_height;
  iptr text;
  int gov_index;
  i32 max_row;
  iptr civ;
  i8 frame_[FRAME_OFF(80)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ = advisor_report_civ;
  recalc_flag = game.transient_flags & 4;
  game.transient_flags = game.transient_flags & 0xfffb;
  frame_wnd_layout((FrameWindow *)&advisor_window);
  frame_wnd_draw_caption((FrameWindow *)&advisor_window);
  picwnd_blit((PictureWindow *)&advisor_window);
  y = advisor_client_y + 2;
  bottom = advisor_client_y + 0x174;
  line_height = font_line_spacing((GameFont *)&advisor_font);
  text_set_surface((iptr)((u8 *)&g.d_0063eb10));
  text_set_font((iptr)((u8 *)&g.d_0063eac0));
  text_set_colors(0x25,0x12,2,1);
  text_clear();
  text = label_string(*(i32 *)(label_string_ids + 0x544));
  text_append(text);
  gfx_draw_text_centered((iptr)((u8 *)&g.d_00679640),advisor_client_x,y,advisor_client_width);
  y += line_height;
  text_clear();
  gov_index = int_clamp(civs[civ].government - 1,0,4);
  text_append_label(gov_index + 0x148);
  text_append_space();
  text_append_label(0x8c);
  text_append_space();
  text = civ_name_plural(civ);
  text_append(text);
  gfx_draw_text_centered((iptr)((u8 *)&g.d_00679640),advisor_client_x,y,advisor_client_width);
  y += line_height;
  text_clear();
  text = civ_leader_title(civ);
  text_append(text);
  text_append_space();
  text = civ_leader_name(civ);
  text_append(text);
  text_append_colon();
  text_append_year((int)game.year);
  gfx_draw_text_centered((iptr)((u8 *)&g.d_00679640),advisor_client_x,y,advisor_client_width);
  y = y + line_height + 2;
  advisor_row_height = 0x20;
  advisor_list_height_i32 = bottom - y;
  advisor_list_top_i32 = y;
  advisor_rows_per_page = int_clamp((bottom - y) / 0x20,1,99);
  city_count = 0;
  for (city = 0; city < game.num_cities; city++) {
    if ((cities[city].id != 0) && (cities[city].owner == civ)) {
      city_count++;
    }
  }
  rows_per_page = advisor_rows_per_page;
  advisor_page_count_i32 = int_clamp((advisor_rows_per_page - 1 + city_count) / advisor_rows_per_page,1,99);
  max_row = int_clamp(city_count - 1,0,999);
  line_height = int_clamp(advisor_first_row,0,max_row);
  row_index = 0;
  advisor_first_row = line_height;
  row_y = y;
  for (city = 0; city < game.num_cities; city++) {
    next_row = row_index;
    if ((((cities[city].id != 0) && (cities[city].owner == civ)) &&
        (next_row = row_index + 1, line_height <= (int)row_index)) && ((int)row_index < line_height + rows_per_page)) {
      if ((recalc_flag != 0) && (4 < civs[civ].government)) {
        city_recalc(city,1);
      }
      gfx_draw_city((iptr)((u8 *)&g.d_0063eb10),city,0,(next_row & 1) * 0x40 + advisor_client_x + 2,row_y,0);
      text_set_font((iptr)((u8 *)&g.d_0063eab8));
      text_set_colors(0x25,0x12,1,1);
      if ((cities[city].unhappy == '\0') &&
         ((int)cities[city].size - (int)(char)cities[city].happy <=
          (int)cities[city].size >> 1)) {
        text_set_colors(0x29,0x12,0xffffffff,0xffffffff);
      }
      if ((char)cities[city].happy < (char)cities[city].unhappy) {
        text_set_colors(0x6a,0x12,0xffffffff,0xffffffff);
      }
      gov_index = advisor_client_x;
      gfx_draw_text((iptr)&cities[city].name,advisor_client_x + 0x8c,row_y + 9);
      advisor_draw_city_citizens(city,gov_index + 0xf5,row_y + 3,
                         ((advisor_client_right - advisor_vscroll_width) - 0x20) - (gov_index + 0xf5),
                         (int)(char)cities[city].happy,(int)(char)cities[city].unhappy,0);
      row_y += 0x20;
    }
    row_index = next_row;
  }
  if (advisor_controls_created == 0) {
    rect_set((iptr)scroll_rect,(advisor_client_right - advisor_vscroll_width) - 2,y,advisor_client_right - 2,
                       bottom);
    scrollbar_create((Control *)&advisor_scrollbar,(iptr)((u8 *)&g.d_0063eb58),200,(iptr)scroll_rect,1);
    max_row = int_clamp(city_count - 1,0,999);
    scrollbar_set_range((Control *)&advisor_scrollbar,0,max_row);
    scrollbar_set_pos((ClickControl *)&advisor_scrollbar,advisor_first_row);
    scrollbar_set_page_size((Control *)&advisor_scrollbar,advisor_rows_per_page);
    scrollbar_set_callback((Control *)&advisor_scrollbar,(iptr)attitude_advisor_on_scroll);
    ctrl_show_and_redraw((Control *)&advisor_scrollbar);
    wnd_set_lbuttonup_handler((WndEventHandlers *)&advisor_wnd_events,(iptr)attitude_advisor_on_click);
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
#undef row_y
#undef row_index
#undef city
#undef city_count
#undef scroll_rect
#undef rows_per_page

/* 0042e07f auto */
#define advisor_first_row (*(i32 *)((u8 *)&g.d_0063ef70))
void __cdecl attitude_advisor_on_scroll(i32 scroll_pos)

{
  advisor_first_row = scroll_pos;
  attitude_advisor_draw();
  return;
}
#undef advisor_first_row

/* 0042e09c auto */
#define advisor_first_row (*(int *)((u8 *)&g.d_0063ef70))
#define advisor_row_height (*(int *)((u8 *)&g.d_0063ef80))
#define advisor_list_top_i32 (*(i32 *)((u8 *)&g.d_0063ef78))
#define city (*(iptr *)(frame_ + FRAME_OFF(4)))
#define row_index (*(int *)(frame_ + FRAME_OFF(8)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl attitude_advisor_on_click(i32 click_x,int click_y)

{
  int row;
  bool is_match;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((-1 < click_y - advisor_list_top_i32) &&
     (row = (click_y - advisor_list_top_i32) / advisor_row_height, row < advisor_rows_per_page)) {
    row_index = 0;
    for (city = 0; city < game.num_cities; city++) {
      if (((cities[city].id != 0) && (cities[city].owner == advisor_report_civ)) &&
         (is_match = row_index == row + advisor_first_row, row_index = row_index + 1, is_match)) {
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
#undef row_index

/* 0042e185 auto */
void __cdecl attitude_advisor_show(iptr report_civ)

{
  picwnd_open((PictureWindow *)&advisor_window,4,4,0,600,400,0,0);
  advisor_report_civ = report_civ;
  advisor_add_close_button((ViewWindow *)&advisor_window);
  wnd_set_redraw_callback((SurfaceWindow *)&advisor_window,(iptr)attitude_advisor_draw);
  wnd_repaint((SurfaceWindow *)&advisor_window);
  window_show((WindowObjectView *)&advisor_window);
  return;
}

/* 0042e1e8 auto */
#define unit_ability_list_nonempty (*(int *)((u8 *)&g.d_0063e4f4))
void __cdecl defense_append_ability_label(i32 label_id)

{
  if (unit_ability_list_nonempty != 0) {
    text_append_comma();
  }
  unit_ability_list_nonempty = 1;
  text_append_label(label_id);
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
#define row_y (*(int *)(frame_ + FRAME_OFF(4)))
#define row_index (*(uint *)(frame_ + FRAME_OFF(32)))
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(36)))
#define type_listed (*(char (*)[64])(frame_ + FRAME_OFF(40)))
#define text_y2 (*(int *)(frame_ + FRAME_OFF(104)))
#define type_count (*(int *)(frame_ + FRAME_OFF(108)))
#define col_x (*(int *)(frame_ + FRAME_OFF(112)))
#define civ2 (*(int *)(frame_ + FRAME_OFF(116)))
#define lost_x (*(int *)(frame_ + FRAME_OFF(120)))
#define line_height (*(int *)(frame_ + FRAME_OFF(124)))
#define frame_rect2 (*(i8 (*)[16])(frame_ + FRAME_OFF(128)))
#define rows_per_page (*(int *)(frame_ + FRAME_OFF(144)))
/* WARNING: Removing unreachable block (ram,0x0042ef32) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl defense_minister_draw(void)

{
  uint next_row;
  int y;
  int bottom;
  iptr unit;
  int list_top;
  i32 value;
  int row_x;
  int name_y;
  int name_x;
  bool has_hold;
  i32 bg_color;
  i32 shadow_color;
  i32 shadow_color2;
  iptr civ;
  i8 frame_[FRAME_OFF(152)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ = advisor_report_civ;
  frame_wnd_layout((FrameWindow *)&advisor_window);
  frame_wnd_draw_caption((FrameWindow *)&advisor_window);
  picwnd_blit((PictureWindow *)&advisor_window);
  y = advisor_client_y + 2;
  bottom = advisor_client_y + 0x174;
  line_height = font_line_spacing((GameFont *)&advisor_font);
  text_set_surface((iptr)((u8 *)&g.d_0063eb10));
  text_set_font((iptr)((u8 *)&g.d_0063eac0));
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
  gfx_draw_text_centered((iptr)((u8 *)&g.d_00679640),advisor_client_x,y,advisor_client_width);
  y += line_height;
  text_clear();
  list_top = int_clamp(civs[civ].government - 1,0,4);
  text_append_label(list_top + 0x148);
  text_append_space();
  text_append_label(0x8c);
  text_append_space();
  unit = civ_name_plural(civ);
  text_append(unit);
  gfx_draw_text_centered((iptr)((u8 *)&g.d_00679640),advisor_client_x,y,advisor_client_width);
  y += line_height;
  text_clear();
  unit = civ_leader_title(civ);
  text_append(unit);
  text_append_space();
  unit = civ_leader_name(civ);
  text_append(unit);
  text_append_colon();
  text_append_year((int)game.year);
  gfx_draw_text_centered((iptr)((u8 *)&g.d_00679640),advisor_client_x,y,advisor_client_width);
  y += line_height;
  list_top = y + 2;
  line_height = 0x18;
  advisor_row_height = 0x18;
  advisor_list_top_i32 = y + 0x1a;
  advisor_list_height_i32 = bottom - list_top;
  advisor_rows_per_page = int_clamp((bottom - list_top) / 0x18,1,99);
  rows_per_page = advisor_rows_per_page;
  type_count = 0;
  unit_type = 0;
  do {
    if (0x3d < unit_type) {
      advisor_page_count_i32 = int_clamp((rows_per_page - 1 + type_count) / rows_per_page,1,99);
      value = int_clamp(type_count - 1,0,999);
      y = int_clamp(advisor_first_row,0,value);
      row_index = 0;
      advisor_first_row = y;
      row_y = list_top;
      for (unit_type = 0; unit_type < 0x3e; unit_type++) {
        next_row = row_index;
        if (((type_listed[unit_type] != '\0') && (next_row = row_index + 1, y <= (int)row_index)) &&
           ((int)row_index < y + rows_per_page)) {
          row_x = (next_row & 1) * 0x40 + advisor_client_x;
          unit = unit_make_dummy(unit_type,civ);
          gfx_draw_unit((iptr)((u8 *)&g.d_0063eb10),unit,0,row_x + 2,row_y,0,0);
          text_set_font((iptr)((u8 *)&g.d_0063eab8));
          text_set_colors(0x25,0x12,1,1);
          row_x = advisor_client_x;
          name_y = row_y + 0x11;
          name_x = advisor_client_x + 0x8c;
          text_y2 = name_y;
          unit = label_string(unit_types[unit_type].name);
          gfx_draw_text(unit,name_x,name_y);
          col_x = row_x + 0xec;
          if (advisor_report_param == 0) {
            text_clear();
            text_append_int((int)(char)unit_types[unit_type].attack);
            text_append((iptr)((u8 *)&g.d_00625f20));
            text_append_int((int)(char)unit_types[unit_type].defense);
            if ((unit_types[unit_type].flags & 0x400) != 0) {
              text_append((iptr)((u8 *)&g.d_00625f24));
            }
            text_append((iptr)((u8 *)&g.d_00625f28));
            text_append_int((int)(char)unit_types[unit_type].move /
                               (int)(uint)cosmic.road_move_mult);
            gfx_draw_text((iptr)((u8 *)&g.d_00679640),col_x,text_y2);
            col_x = row_x + 0x123;
            text_clear();
            text_append_int((int)(char)unit_types[unit_type].hit_points / 10);
            text_append((iptr)((u8 *)&g.d_00625f2c));
            text_append_int((int)(char)unit_types[unit_type].firepower);
            gfx_draw_text((iptr)((u8 *)&g.d_00679640),col_x,text_y2);
            col_x = row_x + 0x143;
            if (*(char *)&civs[civ].units_active[unit_type] != '\0') {
              text_set_colors(0x7a,10,0xffffffff,0xffffffff);
              text_clear();
              text_append_int((uint)civs[civ].units_active[unit_type]);
              text_append_space();
              text_append_label(0x15a);
              gfx_draw_text((iptr)((u8 *)&g.d_00679640),col_x,text_y2);
            }
            col_x = row_x + 0x180;
            if (*(char *)&civs[civ].units_in_production[unit_type] != '\0') {
              text_set_colors(0x5e,10,0xffffffff,0xffffffff);
              text_clear();
              text_append_int((uint)civs[civ].units_in_production[unit_type]);
              text_append_space();
              text_append_label(0x15b);
              gfx_draw_text((iptr)((u8 *)&g.d_00679640),col_x,text_y2);
            }
            col_x = row_x + 0x1c1;
            text_clear();
            text_set_colors(0x7a,10,0xffffffff,0xffffffff);
            unit_ability_list_nonempty = 0;
            has_hold = unit_types[unit_type].hold != '\0';
            if (has_hold) {
              text_append_label(0x15c);
              text_append_space();
              text_append_int((int)(char)unit_types[unit_type].hold);
            }
            unit_ability_list_nonempty = (uint)has_hold;
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
              gfx_draw_text((iptr)((u8 *)&g.d_00679640),col_x,text_y2);
            }
          }
          else {
            row_x += 0x100;
            col_x = row_x;
            if (*(char *)&civs[civ].units_lost[unit_type] != '\0') {
              shadow_color2 = 0xffffffff;
              shadow_color = 0xffffffff;
              bg_color = 0x12;
              value = civ_color_secondary(civ);
              text_set_colors(value,bg_color,shadow_color,shadow_color2);
              text_clear();
              text_append_int((uint)civs[civ].units_lost[unit_type]);
              gfx_draw_text((iptr)((u8 *)&g.d_00679640),col_x,text_y2);
            }
            col_x += 0x1e;
            for (civ2 = 1; civ2 < 8; civ2++) {
              if ((civ2 != civ) &&
                 ((((*(byte *)&civs[human_civ].treaties[civ2] & 0x80) != 0 ||
                   (name_y = civ_has_wonder(human_civ,0x18), name_y != 0)) ||
                  ((name_y = civ_has_wonder(human_civ,9), name_y != 0 ||
                   ((name_y = civ_has_wonder(civ,9), name_y != 0 ||
                    (name_y = civ_has_wonder(civ,0x18), name_y != 0)))))))) {
                if (*(char *)&civs[civ2].units_lost[unit_type] != '\0') {
                  shadow_color2 = 0xffffffff;
                  shadow_color = 0xffffffff;
                  bg_color = 0x12;
                  value = civ_color_secondary(civ2);
                  text_set_colors(value,bg_color,shadow_color,shadow_color2);
                  text_clear();
                  text_append_int((uint)civs[civ2].units_lost[unit_type]);
                  gfx_draw_text((iptr)((u8 *)&g.d_00679640),col_x,text_y2);
                }
                col_x += 0x1e;
              }
            }
            lost_x = row_x;
          }
          row_y += line_height;
        }
        row_index = next_row;
      }
      if (advisor_report_param != 0) {
        rect_set((iptr)frame_rect2,lost_x - 8,list_top,lost_x + 0x10,bottom);
        value = civ_color_primary(civ);
        gfx_draw_rect_frame((iptr)((u8 *)&g.d_0063eb10),(iptr)frame_rect2,value);
      }
      if (advisor_controls_created == 0) {
        rect_set((iptr)frame_rect2,(advisor_client_right - advisor_vscroll_width) - 2,list_top,advisor_client_right - 2
                           ,bottom);
        scrollbar_create
                  ((Control *)&advisor_scrollbar,(iptr)((u8 *)&g.d_0063eb58),200,(iptr)frame_rect2,1);
        scrollbar_set_callback((Control *)&advisor_scrollbar,(iptr)defense_minister_on_scroll);
      }
      value = int_clamp(type_count - 1,0,999);
      scrollbar_set_range((Control *)&advisor_scrollbar,0,value);
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
        type_listed[unit_type] = '\0';
      }
      else {
        type_listed[unit_type] = 1;
      }
      if (type_listed[unit_type] != '\0') {
        type_count++;
      }
    }
    else {
      type_listed[unit_type] = '\0';
      for (civ2 = 1; civ2 < 8; civ2++) {
        if ((*(char *)&civs[civ2].units_lost[unit_type] != '\0') &&
           (((((civ2 == civ ||
               ((*(byte *)&civs[human_civ].treaties[civ2] & 0x80) != 0)) ||
              (y = civ_has_wonder(human_civ,0x18), y != 0)) ||
             ((y = civ_has_wonder(human_civ,9), y != 0 ||
              (y = civ_has_wonder(civ,9), y != 0)))) ||
            (y = civ_has_wonder(civ,0x18), y != 0)))) {
          type_listed[unit_type] = 1;
          type_count++;
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
#undef row_y
#undef row_index
#undef unit_type
#undef type_listed
#undef text_y2
#undef type_count
#undef col_x
#undef civ2
#undef lost_x
#undef line_height
#undef frame_rect2
#undef rows_per_page

/* 0042efe3 auto */
#define advisor_first_row (*(i32 *)((u8 *)&g.d_0063ef70))
void __cdecl defense_minister_on_scroll(i32 scroll_pos)

{
  advisor_first_row = scroll_pos;
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
#define button_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
/* WARNING: Removing unreachable block (ram,0x0042f1bc) */
/* WARNING: Removing unreachable block (ram,0x0042f131) */
/* WARNING: Removing unreachable block (ram,0x0042f21a) */

void __cdecl defense_minister_show(iptr report_civ)

{
  int client_y;
  int rect_h;
  iptr label;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  picwnd_open((PictureWindow *)&advisor_window,2,2,0,600,400,0,0);
  advisor_report_civ = report_civ;
  advisor_report_param = 0;
  rect_set_xywh((iptr)button_rect,2,0,0x129,0x18);
  client_y = advisor_client_y;
  rect_h = rect_height((iptr)button_rect);
  rect_offset((iptr)button_rect,advisor_client_x,(client_y - rect_h) + 0x18e);
  rect_offset((iptr)button_rect,299,0);
  label = label_string(*(i32 *)(label_string_ids + 0x51c));
  button_create
            ((Control *)&advisor_close_button,(iptr)((u8 *)&g.d_0063eb58),100,(iptr)button_rect,label);
  button_set_callback((Control *)&advisor_close_button,(iptr)advisor_on_close_clicked);
  ctrl_set_default_button((Control *)&advisor_close_button);
  ctrl_set_cancel_button((Control *)&advisor_close_button);
  rect_offset((iptr)button_rect,0xfffffed5,0);
  label = label_string(*(i32 *)(label_string_ids + 0x564));
  button_create
            ((Control *)&advisor_toggle_button,(iptr)((u8 *)&g.d_0063eb58),0x65,(iptr)button_rect,label);
  button_set_callback((Control *)&advisor_toggle_button,(iptr)defense_minister_on_toggle_view);
  label = label_string(*(i32 *)(label_string_ids + 0x560));
  button_create
            ((Control *)&advisor_alt_toggle_button,(iptr)((u8 *)&g.d_0063eb58),0x66,(iptr)button_rect,label);
  button_set_callback((Control *)&advisor_alt_toggle_button,(iptr)defense_minister_on_toggle_view);
  control_hide((Control *)&advisor_alt_toggle_button);
  wnd_set_redraw_callback((SurfaceWindow *)&advisor_window,(iptr)defense_minister_draw);
  wnd_repaint((SurfaceWindow *)&advisor_window);
  window_show((WindowObjectView *)&advisor_window);
  return;
}
#undef advisor_client_x
#undef advisor_report_param
#undef button_rect

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
#define icon_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define civ3 (*(iptr *)(frame_ + FRAME_OFF(16)))
#define item_y (*(int *)(frame_ + FRAME_OFF(20)))
#define list_bottom (*(int *)(frame_ + FRAME_OFF(24)))
#define first_item (*(iptr *)(frame_ + FRAME_OFF(28)))
#define item_x (*(int *)(frame_ + FRAME_OFF(32)))
#define civ2 (*(int *)(frame_ + FRAME_OFF(36)))
#define y2 (*(int *)(frame_ + FRAME_OFF(40)))
#define item_index (*(int *)(frame_ + FRAME_OFF(44)))
#define city (*(iptr *)(frame_ + FRAME_OFF(48)))
#define advance (*(iptr *)(frame_ + FRAME_OFF(52)))
#define scroll_height (*(int *)(frame_ + FRAME_OFF(56)))
#define city2 (*(iptr *)(frame_ + FRAME_OFF(60)))
#define attitude_level (*(iptr *)(frame_ + FRAME_OFF(64)))
#define leader (*(iptr *)(frame_ + FRAME_OFF(68)))
#define right_x (*(int *)(frame_ + FRAME_OFF(72)))
#define left_x (*(int *)(frame_ + FRAME_OFF(76)))
#define advance_count (*(int *)(frame_ + FRAME_OFF(80)))
#define text_x2 (*(int *)(frame_ + FRAME_OFF(84)))
#define column (*(int *)(frame_ + FRAME_OFF(88)))
#define civ (*(iptr *)(frame_ + FRAME_OFF(92)))
#define row (*(int *)(frame_ + FRAME_OFF(96)))
#define buf (*(char (*)[80])(frame_ + FRAME_OFF(100)))
#define line_height (*(int *)(frame_ + FRAME_OFF(180)))
#define scroll_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(184)))
#define rows_per_page (*(int *)(frame_ + FRAME_OFF(200)))
/* WARNING: Removing unreachable block (ram,0x004301aa) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl intel_report_draw(void)

{
  iptr text;
  i32 color;
  int value;
  int has_adv;
  i32 bg_color;
  i32 shadow_color;
  i32 shadow_color2;
  i8 frame_[FRAME_OFF(208)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ3 = advisor_report_civ;
  civ = advisor_report_param;
  frame_wnd_layout((FrameWindow *)&advisor_window);
  frame_wnd_draw_caption((FrameWindow *)&advisor_window);
  picwnd_blit((PictureWindow *)&advisor_window);
  y2 = advisor_client_y + 2;
  list_bottom = advisor_client_y + 0x174;
  line_height = font_line_spacing((GameFont *)&advisor_font);
  text_set_surface((iptr)((u8 *)&g.d_0063eb10));
  text_set_font((iptr)((u8 *)&g.d_0063eac0));
  text_set_colors(0x25,0x12,2,1);
  text_clear();
  text = label_string(*(i32 *)(label_string_ids + 0x540));
  text_append(text);
  gfx_draw_text_centered((iptr)((u8 *)&g.d_00679640),advisor_client_x,y2,advisor_client_width);
  y2 += line_height;
  text_clear();
  text = civ_leader_title(civ);
  text_append(text);
  text_append_space();
  text = civ_leader_name(civ);
  text_append(text);
  text_append_space();
  text_append_label(0x8c);
  text_append_space();
  text = civ_name_plural(civ);
  text_append(text);
  text_append_space();
  diplo_eval_ai_stance(civ3,civ);
  attitude_level = diplo_attitude_level(diplo_cur_attitude);
  text_append_lparen();
  text_append_string_id(attitude_names[attitude_level]);
  if ((*(byte *)(civ * 4 + (iptr)((u8 *)&civs + 33) + civ3 * 0x594) & 0x20) == 0) {
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
  shadow_color2 = 0xffffffff;
  shadow_color = 0xffffffff;
  bg_color = 0x12;
  color = civ_color_secondary(civ);
  text_set_colors(color,bg_color,shadow_color,shadow_color2);
  gfx_draw_text_centered((iptr)((u8 *)&g.d_00679640),advisor_client_x,y2,advisor_client_width);
  y2 += line_height;
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
  gfx_draw_text_centered((iptr)((u8 *)&g.d_00679640),advisor_client_x,y2,advisor_client_width);
  y2 = y2 + line_height + 6;
  left_x = advisor_client_x + 2;
  right_x = advisor_client_width + advisor_client_x - 4;
  text_set_font((iptr)((u8 *)&g.d_0063eab8));
  line_height = font_line_spacing((GameFont *)&advisor_bold_font);
  text_clear();
  text_append_label(0x98);
  text_append_colon();
  text_set_colors(0x7a,0x12,0xffffffff,0xffffffff);
  text_x2 = gfx_draw_text((iptr)((u8 *)&g.d_00679640),left_x,y2);
  text_clear();
  text_append_string_id(government_names[civs[civ].government]);
  text_set_colors(0x25,0x12,0xffffffff,0xffffffff);
  gfx_draw_text((iptr)((u8 *)&g.d_00679640),text_x2,y2);
  city2 = -1;
  for (city = 0; city < game.num_cities; city++) {
    if (((cities[city].id != 0) && (cities[city].owner == civ)) &&
       (value = city_has_improvement(city,1), value != 0)) {
      city2 = city;
      break;
    }
  }
  text_clear();
  text_append_label(0x99);
  text_append_colon();
  text_append_city_name(city2);
  value = right_x;
  text_x2 = font_text_width((GameFont *)&advisor_bold_font,(iptr)((u8 *)&g.d_00679640));
  text_x2 = value - text_x2;
  text_clear();
  text_append_label(0x99);
  text_append_colon();
  text_set_colors(0x7a,0x12,0xffffffff,0xffffffff);
  text_x2 = gfx_draw_text((iptr)((u8 *)&g.d_00679640),text_x2,y2);
  text_clear();
  text_append_city_name(city2);
  text_set_colors(0x25,0x12,0xffffffff,0xffffffff);
  gfx_draw_text((iptr)((u8 *)&g.d_00679640),text_x2,y2);
  y2 += line_height;
  text_clear();
  text_append_label(0x9a);
  text_append_colon();
  text_set_colors(0x7a,0x12,0xffffffff,0xffffffff);
  text_x2 = gfx_draw_text((iptr)((u8 *)&g.d_00679640),left_x,y2);
  text_clear();
  text_append_gold(civs[civ].gold);
  text_set_colors(0x25,0x12,0xffffffff,0xffffffff);
  text_x2 = gfx_draw_text((iptr)((u8 *)&g.d_00679640),text_x2,y2);
  if (game.difficulty < 2) {
    text_x2 += 6;
    text_clear();
    text_append_label(0x9b);
    text_append_colon();
    text_set_colors(0x7a,0x12,0xffffffff,0xffffffff);
    text_x2 = gfx_draw_text((iptr)((u8 *)&g.d_00679640),text_x2,y2);
    text_clear();
    text_append_int((int)civs[civ].num_military_units);
    text_append_space();
    text_append_label(0x19);
    text_set_colors(0x25,0x12,0xffffffff,0xffffffff);
    text_x2 = gfx_draw_text((iptr)((u8 *)&g.d_00679640),text_x2,y2);
  }
  text_clear();
  text_append_label(0xec);
  text_append_colon();
  str_clear((iptr)buf);
  if (civs[civ].researching < 0) {
    str_append_label((iptr)buf,0xe);
  }
  else {
    str_append_string_id((iptr)buf,advances[civs[civ].researching].name);
  }
  text_append((iptr)buf);
  value = right_x;
  text_x2 = font_text_width((GameFont *)&advisor_bold_font,(iptr)((u8 *)&g.d_00679640));
  text_x2 = value - text_x2;
  text_clear();
  text_append_label(0xec);
  text_append_colon();
  text_set_colors(0x7a,0x12,0xffffffff,0xffffffff);
  text_x2 = gfx_draw_text((iptr)((u8 *)&g.d_00679640),text_x2,y2);
  text_set_colors(0x25,0x12,0xffffffff,0xffffffff);
  text_x2 = gfx_draw_text((iptr)buf,text_x2,y2);
  y2 = y2 + line_height + 6;
  for (civ2 = 1; civ2 < 8; civ2++) {
    if (((civ2 != civ) && ((1 << ((byte)civ2 & 0x1f) & (uint)game.civs_alive) != 0)) &&
       ((*(byte *)&civs[civ].treaties[civ2] & 1) != 0)) {
      text_clear();
      str_clear((iptr)buf);
      if ((*(byte *)(civ * 0x594 + (iptr)((u8 *)&civs + 33) + civ2 * 4) & 0x20) == 0) {
        if ((*(byte *)&civs[civ].treaties[civ2] & 8) == 0) {
          if ((*(byte *)&civs[civ].treaties[civ2] & 4) == 0) {
            if ((*(byte *)&civs[civ].treaties[civ2] & 2) == 0) {
              str_append_label((iptr)buf,0x9d);
            }
            else {
              str_append_label((iptr)buf,0x8f);
            }
          }
          else {
            text_append_label(0x9c);
            text_append_space();
            str_append_label((iptr)buf,0x8e);
          }
        }
        else {
          str_append_label((iptr)buf,0x8d);
        }
      }
      else {
        text_append_label(0x9c);
        text_append_space();
        str_append_label((iptr)buf,0x90);
      }
      __strupr(buf);
      text_append((iptr)buf);
      text_append_space();
      text_append_label(0x7b);
      text_append_space();
      text = civ_leader_title(civ2);
      text_append(text);
      text_append_space();
      text = civ_leader_name(civ2);
      text_append(text);
      text_append_space();
      text_append_label(0x8c);
      text_append_space();
      text = civ_name_plural(civ2);
      text_append(text);
      shadow_color2 = 0xffffffff;
      shadow_color = 0xffffffff;
      bg_color = 0x12;
      color = civ_color_secondary(civ2);
      text_set_colors(color,bg_color,shadow_color,shadow_color2);
      gfx_draw_text_centered((iptr)((u8 *)&g.d_00679640),advisor_client_x,y2,advisor_client_width);
      y2 += line_height;
    }
  }
  y2 += 6;
  scroll_height = GetSystemMetrics(3);
  list_bottom -= (scroll_height + 2);
  line_height = 0x16;
  advisor_row_height = 0x16;
  advisor_list_top_i32 = y2;
  advisor_list_height_i32 = list_bottom - y2;
  advisor_rows_per_page = int_clamp((list_bottom - y2) / 0x16,0,99);
  rows_per_page = advisor_rows_per_page;
  if (0 < advisor_rows_per_page) {
    advisor_list_left_i32 = advisor_client_x + 2;
    right_x = advisor_client_width + advisor_client_x - 2;
    advisor_list_width = right_x - advisor_list_left_i32;
    advisor_column_width = advisor_list_width / 3;
    advisor_items_per_page = advisor_rows_per_page * 3;
    advance_count = 0;
    left_x = advisor_list_left_i32;
    for (advance = 0; advance < 100; advance++) {
      value = civ_has_advance(civ,advance);
      if (value != 0) {
        advance_count++;
      }
    }
    advisor_page_count_i32 = int_clamp((rows_per_page - 1 + advance_count) / rows_per_page,1,99);
    color = int_clamp(advance_count - 1,0,999);
    advisor_first_row = int_clamp(advisor_first_row,0,color);
    item_index = 0;
    column = 0;
    row = 0;
    item_y = y2;
    first_item = advisor_first_row;
    text_set_font((iptr)((u8 *)&g.d_0063eab8));
    for (advance = 0; advance < 100; advance++) {
      has_adv = civ_has_advance(civ,advance);
      value = item_index;
      if (((has_adv != 0) && (value = item_index + 1, first_item <= item_index)) &&
         (item_index < advisor_items_per_page + first_item)) {
        item_y = line_height * row + y2;
        item_x = advisor_column_width * column + left_x;
        item_index = value;
        sprite_draw
                  ((Sprite *)
                   (&advance_category_icon_sprites +
                   (char)advances[advance].epoch * 0x3c + (char)advances[advance].category * 0xf0)
                   ,(iptr)icon_rect,(iptr)((u8 *)&g.d_0063eb10),item_x,item_y);
        text_x2 = item_x + 0x26;
        shadow_color = 1;
        bg_color = 1;
        color = 0x12;
        value = civ_has_advance(human_civ,advance);
        text_set_colors((-(uint)(value == 0) & 0xffffffcb) + 0x5e,color,bg_color,shadow_color);
        has_adv = item_y + 2;
        value = text_x2;
        text = label_string(advances[advance].name);
        gfx_draw_text(text,value,has_adv);
        row++;
        value = item_index;
        if (rows_per_page <= row) {
          row = 0;
          column++;
          if (2 < column) break;
        }
      }
      item_index = value;
    }
    if (advisor_controls_created == 0) {
      rect_set((iptr)scroll_rect,left_x,list_bottom,right_x,list_bottom + scroll_height);
      scrollbar_create
                ((Control *)&advisor_scrollbar,(iptr)((u8 *)&g.d_0063eb58),200,(iptr)scroll_rect,0);
      color = int_clamp((rows_per_page - 1 + advance_count) / rows_per_page - 1,0,999);
      scrollbar_set_range((Control *)&advisor_scrollbar,0,color);
      scrollbar_set_pos((ClickControl *)&advisor_scrollbar,advisor_first_row);
      scrollbar_set_page_size((Control *)&advisor_scrollbar,1);
      scrollbar_set_callback((Control *)&advisor_scrollbar,(iptr)intel_report_on_scroll);
      ctrl_show_and_redraw((Control *)&advisor_scrollbar);
      wnd_set_lbuttonup_handler((WndEventHandlers *)&advisor_wnd_events,(iptr)intel_report_on_click);
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
#undef icon_rect
#undef civ3
#undef item_y
#undef list_bottom
#undef first_item
#undef item_x
#undef civ2
#undef y2
#undef item_index
#undef city
#undef advance
#undef scroll_height
#undef city2
#undef attitude_level
#undef leader
#undef right_x
#undef left_x
#undef advance_count
#undef text_x2
#undef column
#undef civ
#undef row
#undef buf
#undef line_height
#undef scroll_rect
#undef rows_per_page

/* 00430267 auto */
#define advisor_first_row (*(int *)((u8 *)&g.d_0063ef70))
void __cdecl intel_report_on_scroll(int scroll_pos)

{
  advisor_first_row = advisor_rows_per_page * scroll_pos;
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
#define advance_id (*(int *)(frame_ + FRAME_OFF(0)))
#define item_index (*(int *)(frame_ + FRAME_OFF(4)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl intel_report_on_click(int click_x,int click_y)

{
  iptr civ;
  int row;
  int column;
  int has_adv;
  bool is_match;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ = advisor_report_param;
  if ((((-1 < click_y - advisor_list_top_i32) &&
       (row = (click_y - advisor_list_top_i32) / advisor_row_height, row < advisor_rows_per_page)) &&
      (-1 < click_x - 2)) && (column = (click_x - 2) / advisor_column_width, column < 3)) {
    column = advisor_rows_per_page * column + advisor_first_row;
    item_index = 0;
    for (advance_id = 0; advance_id < 100; advance_id++) {
      has_adv = civ_has_advance(civ,advance_id);
      if ((has_adv != 0) && (is_match = item_index == column + row, item_index = item_index + 1, is_match)) {
        pedia_show_topic_modal((DocumentWindow *)&pedia_window,advance_id);
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
#undef advance_id
#undef item_index

/* 0043039d auto */
#define advisor_report_param (*(iptr *)((u8 *)&g.d_0063efac))
#define intel_report_reopen (*(i32 *)((u8 *)&g.d_00625ec4))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(0)))
#define city (*(iptr *)(frame_ + FRAME_OFF(4)))
#define dialog2 (*(Dialog *)(frame_ + FRAME_OFF(8)))
#define civ (*(iptr *)(frame_ + FRAME_OFF(764)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(768)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(772)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(776)))
void __cdecl intel_report_on_cities_clicked(void)

{
  iptr civ_name;
  int has_palace;
  i8 frame_[FRAME_OFF(784)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  dialog_ctor(&dialog2,0x4000);
  seh_state = 0;
  civ = advisor_report_param;
  civ_name = civ_name_plural(advisor_report_param);
  text_set_string_arg(0,civ_name);
  dialog_load_game_text(&dialog2,(iptr)((u8 *)&g.d_00625f30));
  for (city = 0; city < game.num_cities; city++) {
    if ((cities[city].id != 0) && (cities[city].owner == civ)) {
      text_clear();
      text_append(city * 0x58 + (iptr)((u8 *)&cities + 32));
      has_palace = city_has_improvement(city,1);
      if (has_palace != 0) {
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
      dialog_add_option((DialogOptionList *)&dialog2,(iptr)((u8 *)&g.d_00679640),city,0);
    }
  }
  wnd_disable((WndBase *)&advisor_wnd);
  dlg_show_modal(&dialog2,0);
  wnd_enable((WndBase *)&advisor_wnd);
  wnd_end_modal_loop((ModalMenuWindow *)&advisor_wnd);
  intel_report_reopen = 1;
  seh_state = 0xffffffff;
  /* inlined unwind funclet 004305e7 */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
  return;
}
#undef advisor_report_param
#undef intel_report_reopen
#undef improvement
#undef city
#undef dialog2
#undef civ
#undef seh_prev
#undef seh_handler
#undef seh_state

/* 0043060b auto */
#define advisor_client_x (*(i32 *)((u8 *)&g.d_0063ec34))
#define advisor_report_param (*(iptr *)((u8 *)&g.d_0063efac))
#define intel_report_reopen (*(int *)((u8 *)&g.d_00625ec4))
#define advisor_modal_start_ticks_i32 (*(i32 *)((u8 *)&g.d_00625ec0))
#define button_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
/* WARNING: Removing unreachable block (ram,0x004306c1) */
/* WARNING: Removing unreachable block (ram,0x0043074c) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl intel_report_show(iptr report_civ,iptr target_civ)

{
  int client_y;
  int rect_h;
  iptr label;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  picwnd_open((PictureWindow *)&advisor_window,3,3,1,600,400,0,0);
  advisor_report_civ = report_civ;
  advisor_report_param = target_civ;
  rect_set_xywh((iptr)button_rect,2,0,0x129,0x18);
  client_y = advisor_client_y;
  rect_h = rect_height((iptr)button_rect);
  rect_offset((iptr)button_rect,advisor_client_x,(client_y - rect_h) + 0x18e);
  rect_offset((iptr)button_rect,299,0);
  label = label_string(*(i32 *)(label_string_ids + 0x51c));
  button_create
            ((Control *)&advisor_close_button,(iptr)((u8 *)&g.d_0063eb58),100,(iptr)button_rect,label);
  button_set_callback((Control *)&advisor_close_button,(iptr)advisor_on_close_clicked);
  ctrl_set_default_button((Control *)&advisor_close_button);
  ctrl_set_cancel_button((Control *)&advisor_close_button);
  rect_offset((iptr)button_rect,0xfffffed5,0);
  label = label_string(*(i32 *)(label_string_ids + 0x314));
  button_create
            ((Control *)&advisor_toggle_button,(iptr)((u8 *)&g.d_0063eb58),0x65,(iptr)button_rect,label);
  button_set_callback((Control *)&advisor_toggle_button,(iptr)intel_report_on_cities_clicked);
  wnd_set_redraw_callback((SurfaceWindow *)&advisor_window,(iptr)intel_report_draw);
  wnd_repaint((SurfaceWindow *)&advisor_window);
  window_show((WindowObjectView *)&advisor_window);
  do {
    intel_report_reopen = 0;
    if (2 < game.multiplayer) {
      wnd_set_modal_idle_callback((ModalMenuWindow *)&advisor_wnd,(iptr)advisor_mp_idle);
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
#undef button_rect

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
#define cur_level (*(iptr *)(frame_ + FRAME_OFF(0)))
#define attitude_values (*(byte (*)[12])(frame_ + FRAME_OFF(4)))
#define popup_result (*(int *)(frame_ + FRAME_OFF(16)))
#define has_embassy_wonder (*(int *)(frame_ + FRAME_OFF(20)))
#define choice (*(iptr *)(frame_ + FRAME_OFF(24)))
#define contact_count (*(int *)(frame_ + FRAME_OFF(28)))
#define dialog2 (*(Dialog *)(frame_ + FRAME_OFF(32)))
#define both_human (*(int *)(frame_ + FRAME_OFF(788)))
#define civ2 (*(iptr *)(frame_ + FRAME_OFF(792)))
#define sees_all (*(int *)(frame_ + FRAME_OFF(796)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(800)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(804)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(808)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl foreign_minister_show(iptr civ)

{
  iptr parley_hwnd_obj;
  int value;
  iptr text;
  i32 option_flags;
  iptr option_id;
  i8 frame_[FRAME_OFF(816)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  dialog_ctor(&dialog2,0x4000);
  seh_state = 0;
  if ((game.multiplayer < 3) || (parley_wnd_closed != 0)) {
    while( true ) {
      while( true ) {
        value = int_clamp((uint)game.power_rank[civ],1,7);
        text_set_label_arg(0,*(i32 *)(label_string_ids + 0x38c + value * 4));
        value = int_clamp((uint)civs[civ].reputation,0,7);
        text_set_label_arg(1,*(i32 *)(label_string_ids + 0x370 + value * 4));
        if (game.multiplayer == '\0') {
          dlg_load_game_section(&dialog2,(iptr)((u8 *)&g.d_00625f3c),0x2000001);
        }
        else {
          dlg_load_game_section(&dialog2,(iptr)((u8 *)&g.d_00625f4c),0x2000001);
        }
        dialog_set_option_draw_fn((DialogOptionList *)&dialog2,(iptr)foreign_minister_draw_civ_city);
        dialog_set_list_indent((DialogCore *)&dialog2,0x4b,0);
        contact_count = 0;
        value = civ_has_wonder(civ,0x18);
        if ((value == 0) && (value = civ_has_wonder(civ,9), value == 0)) {
          has_embassy_wonder = 0;
        }
        else {
          has_embassy_wonder = 1;
        }
        if (((game.wonder_city[0x18] == -1) && (value = civ_has_wonder(civ,9), value == 0))
           && (game.reveal_map == '\0')) {
          sees_all = 0;
        }
        else {
          sees_all = 1;
        }
        for (civ2 = 1; civ2 < 8; civ2++) {
          if ((civ2 != civ) && ((1 << ((byte)civ2 & 0x1f) & (uint)game.civs_alive) != 0)
             ) {
            if ((((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) ||
                ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) == 0)) ||
               ((mp_show_human_starts == 0 && (game.difficulty != '\0')))) {
              both_human = 0;
            }
            else {
              both_human = 1;
            }
            if (((sees_all != 0) || (both_human != 0)) ||
               ((*(byte *)&civs[civ].treaties[civ2] & 1) != 0)) {
              contact_count++;
              text_clear();
              text = civ_leader_title(civ2);
              text_append(text);
              text_append_space();
              text = civ_leader_name(civ2);
              text_append(text);
              text_append_space();
              text_append_label(0x8c);
              text_append_space();
              text = civ_name_plural(civ2);
              text_append(text);
              text_append_space();
              diplo_eval_ai_stance(civ,civ2);
              choice = diplo_attitude_level(diplo_cur_attitude);
              text_append_lparen();
              text_append_string_id(attitude_names[choice]);
              if ((*(byte *)(civ * 0x594 + (iptr)((u8 *)&civs + 33) + civ2 * 4) & 0x20) == 0) {
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
                 (has_embassy_wonder == 0)) {
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
              dialog_add_option((DialogOptionList *)&dialog2,(iptr)((u8 *)&g.d_00679640),civ2,0);
            }
          }
        }
        if (contact_count == 0) {
          popup_game((iptr)((u8 *)&g.d_00625f60));
          seh_state = 0xffffffff;
          /* inlined unwind funclet 0043154f */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
          goto LAB_00431565;
        }
        civ2 = dlg_show_modal(&dialog2,0);
        if (((*(i8 *)((char *)&dialog2.style_flags + 1)) & 0x20) != 0) {
          dialog2.result_extra = 2;
        }
        if (dialog2.result_extra == 0) {
          seh_state = 0xffffffff;
          /* inlined unwind funclet 0043154f */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
          goto LAB_00431565;
        }
        if (dialog2.result_extra != 1) break;
        if ((((*(byte *)&civs[civ].treaties[civ2] & 0x80) == 0) &&
            (has_embassy_wonder == 0)) && (game.reveal_map == '\0')) {
          popup_game_with_sprite((iptr)((u8 *)&g.d_00625ff8),(iptr)((u8 *)&g.d_0063fc58),0);
        }
        else {
          intel_report_show(civ,civ2);
        }
      }
      if (dialog2.result_extra == 2) break;
      if (dialog2.result_extra != 3) goto LAB_0043153e;
      text_clear();
      text = civ_leader_title(civ2);
      text_append(text);
      text_append_space();
      text = civ_leader_name(civ2);
      text_append(text);
      text_append_space();
      text_append_label(0x8c);
      text_append_space();
      text = civ_name_plural(civ2);
      text_append(text);
      text_set_string_arg(0,(iptr)((u8 *)&g.d_00679640));
      choice = dialog_load_text(&dialog2,(iptr)((u8 *)&g.d_00625f7c),(iptr)((u8 *)&g.d_00625f6c),1);
      if (choice == 0) {
        dialog_set_columns((DialogButtonsView *)&dialog2,3);
        for (choice = 0; choice < 9; choice++) {
          option_flags = 0;
          option_id = choice;
          text = label_string(attitude_names[choice]);
          dialog_add_option((DialogOptionList *)&dialog2,text,option_id,option_flags);
        }
        if (*(char *)&civs[civ].attitude[civ2] == '\0') {
          cur_level = 0;
        }
        else {
          cur_level = diplo_attitude_level((uint)civs[civ].attitude[civ2]);
        }
        dialog_set_default_choice((DialogOptionList *)&dialog2,cur_level);
        choice = dlg_show_modal(&dialog2,0);
        if (-1 < choice) {
          attitude_values[0] = 0;
          attitude_values[1] = 5;
          attitude_values[2] = 0x11;
          attitude_values[3] = 0x1f;
          attitude_values[4] = 0x32;
          attitude_values[5] = 0x44;
          attitude_values[6] = 0x52;
          attitude_values[7] = 0x5f;
          attitude_values[8] = 100;
          civs[civ].attitude[civ2] = attitude_values[choice];
          net_send_message(0x98,0xff,civ,civ2,(uint)attitude_values[choice],0,0,0,0,0);
        }
      }
    }
    if ((scenario_events_loaded == 0) ||
       (value = events_check_negotiation((ScenarioEvents *)&scenario_events,civ,civ2)
       , value != 0)) {
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
          text = civ_leader_name(civ2);
          text_set_string_arg(1,text);
          text = civ_name_plural(civ2);
          text_set_string_arg(2,text);
          dlg_pending_idle_callback = ((void *)(iptr)mp_meeting_wait_idle);
          mp_meeting_wait_start_i32 = timer_ticks();
          popup_result = popup_game_sprite_flags((iptr)((u8 *)&g.d_00625f94),0x2000001,(iptr)((u8 *)&g.d_0063fc58),0);
          if (nm_parley_cancel_count == 0) {
            if (popup_result == -1) {
              net_send_message(0x81,*(i32 *)
                                       (&net_player_slots +
                                       *(int *)(&net_civ_slots + civ2 * 4) * 0x54),0,0,0,0,0,0,0,
                                 0);
              parley_other_civ = -1;
              mp_meeting_pending = 0;
            }
            else if (mp_meeting_reply < 1) {
              dlg_pending_idle_callback = ((void *)(iptr)turn_popup_timeout_idle);
              popup_game_with_sprite((iptr)((u8 *)&g.d_00625fb4),(iptr)((u8 *)&g.d_0063fc58),0);
              mp_meeting_pending = 0;
            }
            else if (mp_meeting_reply == 1) {
              mp_meeting_reply = -1;
              parley_other_civ = civ2;
              dlg_pending_idle_callback = ((void *)(iptr)mp_meeting_wait_idle);
              mp_meeting_wait_start_i32 = timer_ticks();
              text = civ_name_plural(civ);
              text_set_string_arg(0,text);
              popup_game_with_sprite((iptr)((u8 *)&g.d_00625fc4),(iptr)((u8 *)&g.d_0063fc58),0);
              if (net_host_handoff_stage == '\0') {
                if (nm_parley_cancel_count == 0) {
                  parley_wnd_open((ViewWindow *)&parley_wnd,civ2,3);
                }
                else {
                  parley_other_civ = -1;
                  nm_parley_cancel_count = 0;
                  text = civ_name_plural(civ2);
                  text_set_string_arg(0,text);
                  dlg_pending_idle_callback = ((void *)(iptr)turn_popup_timeout_idle);
                  popup_game_with_sprite((iptr)((u8 *)&g.d_00625fdc),(iptr)((u8 *)&g.d_0063fc58),0);
                  mp_meeting_pending = 0;
                }
              }
              else {
                parley_other_civ = -1;
                dlg_pending_idle_callback = ((void *)(iptr)turn_popup_timeout_idle);
                popup_game_with_sprite((iptr)((u8 *)&g.d_00625fd0),(iptr)((u8 *)&g.d_0063fc58),0);
                mp_meeting_pending = 0;
              }
            }
            else {
              dlg_pending_idle_callback = ((void *)(iptr)turn_popup_timeout_idle);
              popup_game_with_sprite((iptr)((u8 *)&g.d_00625fec),(iptr)((u8 *)&g.d_0063fc58),0);
              mp_meeting_pending = 0;
            }
          }
          else {
            nm_parley_cancel_count = 0;
            text = civ_name_plural(civ2);
            text_set_string_arg(0,text);
            dlg_pending_idle_callback = ((void *)(iptr)turn_popup_timeout_idle);
            popup_game_with_sprite((iptr)((u8 *)&g.d_00625fa4),(iptr)((u8 *)&g.d_0063fc58),0);
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
      popup_game((iptr)((u8 *)&g.d_00625f84));
    }
LAB_0043153e:
    seh_state = 0xffffffff;
    /* inlined unwind funclet 0043154f */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
  }
  else {
    parley_hwnd_obj = wnd_get_window((WndBase *)&parley_wnd_frame);
    BringWindowToTop(*(HWND *)(parley_hwnd_obj + 4));
    seh_state = 0xffffffff;
    /* inlined unwind funclet 0043154f */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
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
#undef cur_level
#undef attitude_values
#undef popup_result
#undef has_embassy_wonder
#undef choice
#undef contact_count
#undef dialog2
#undef both_human
#undef civ2
#undef sees_all
#undef seh_prev
#undef seh_handler
#undef seh_state

/* 00431d22 auto */
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
#define palette (*(GamePalette * *)(frame_ + FRAME_OFF(0)))
#define surface (*(DibSurface * *)(frame_ + FRAME_OFF(8)))
#define civ (*(iptr *)(frame_ + FRAME_OFF(16)))
#define legend_row (*(int *)(frame_ + FRAME_OFF(20)))
#define legend_font (*(GameFont *)(frame_ + FRAME_OFF(24)))
#define origin_x2 (*(u32 *)(frame_ + FRAME_OFF(32)))
#define prev_y (*(int *)(frame_ + FRAME_OFF(36)))
#define prev_x (*(int *)(frame_ + FRAME_OFF(40)))
#define grid_x (*(int *)(frame_ + FRAME_OFF(44)))
#define graph_wnd (*(i8 (*)[736])(frame_ + FRAME_OFF(48)))
#define dialog2 (*(Dialog *)(frame_ + FRAME_OFF(784)))
#define year2 (*(i32 *)(frame_ + FRAME_OFF(1540)))
#define civ_color (*(i32 *)(frame_ + FRAME_OFF(1544)))
#define point_y (*(int *)(frame_ + FRAME_OFF(1548)))
#define point_x (*(int *)(frame_ + FRAME_OFF(1552)))
#define sample (*(int *)(frame_ + FRAME_OFF(1556)))
#define origin_y2 (*(u32 *)(frame_ + FRAME_OFF(1560)))
#define grid_step (*(int *)(frame_ + FRAME_OFF(1564)))
#define sample_count (*(iptr *)(frame_ + FRAME_OFF(1568)))
#define rect_left2 (*(u32 *)(frame_ + FRAME_OFF(1572)))
#define rect_top2 (*(int *)(frame_ + FRAME_OFF(1576)))
#define rect_right2 (*(u8 (*)[4])(frame_ + FRAME_OFF(1580)))
#define rect_bottom2 (*(u8 (*)[4])(frame_ + FRAME_OFF(1584)))
#define max_power (*(uint *)(frame_ + FRAME_OFF(1588)))
#define bg_surface2 (*(DibSurface * *)(frame_ + FRAME_OFF(1592)))
#define bg_palette (*(GamePalette * *)(frame_ + FRAME_OFF(1596)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(1600)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(1604)))
#define seh_state (*(int *)(frame_ + FRAME_OFF(1608)))
void __cdecl powergraph_show(void)

{
  int next_row;
  DibSurface *this;
  GamePalette *this_00;
  i32 title;
  int text_y;
  int text_x;
  iptr civ_name;
  i32 wnd_style;
  i32 wnd_x;
  i32 wnd_y;
  i32 wnd_width;
  i32 wnd_height;
  i32 wnd_arg6;
  i32 wnd_arg7;
  i32 wnd_arg8;
  i8 frame_[FRAME_OFF(1616)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  frame_wnd_ctor((SurfaceWindow *)graph_wnd);
  seh_state = 0;
  font_init_empty((GameFont *)(graph_wnd + 0x2d8));
  (*(i8 *)((char *)&seh_state + 0)) = 1;
  font_init_empty(&legend_font);
  (*(i8 *)((char *)&seh_state + 0)) = 2;
  dialog_ctor(&dialog2,0x4000);
  (*(i8 *)((char *)&seh_state + 0)) = 3;
  bg_surface2 = (DibSurface *)0x0;
  bg_palette = (GamePalette *)0x0;
  font_set_styled((GameFont *)(graph_wnd + 0x2d8),0,0xc,1);
  font_set_styled(&legend_font,0,0xe,1);
  this = operator_new(0x48);
  (*(i8 *)((char *)&seh_state + 0)) = 4;
  if (this == (DibSurface *)0x0) {
    surface = (DibSurface *)0x0;
  }
  else {
    surface = (DibSurface *)surface_ctor(this);
  }
  (*(i8 *)((char *)&seh_state + 0)) = 3;
  bg_surface2 = surface;
  this_00 = operator_new(0x434);
  (*(i8 *)((char *)&seh_state + 0)) = 5;
  if (this_00 == (GamePalette *)0x0) {
    palette = (GamePalette *)0x0;
  }
  else {
    palette = (GamePalette *)palette_init(this_00);
  }
  seh_state = CONCAT31((*(i32 *)((char *)&seh_state + 1)),3);
  bg_palette = palette;
  surface_load_gif_resource(bg_surface2,0x33,10,0xc0,(iptr)palette);
  wnd_arg8 = 0;
  wnd_arg7 = 0;
  wnd_arg6 = 0;
  wnd_height = 0x1a9;
  wnd_width = 600;
  wnd_y = 0x14;
  wnd_x = 0;
  wnd_style = 0xd;
  title = label_string(*(i32 *)(label_string_ids + 0x358));
  frame_wnd_create
            ((FrameWindow *)graph_wnd,title,wnd_style,wnd_x,wnd_y,wnd_width,wnd_height,wnd_arg6,wnd_arg7,wnd_arg8);
  text_set_surface((iptr)graph_wnd);
  text_set_font((iptr)(graph_wnd + 0x2d8));
  origin_x2 = (*(i32 *)((char *)&graph_wnd + 292));
  origin_y2 = (*(i32 *)((char *)&graph_wnd + 296));
  frame_wnd_layout((FrameWindow *)graph_wnd);
  frame_wnd_draw_caption((FrameWindow *)graph_wnd);
  gfx_copy_rect_xywh((iptr)bg_surface2,(iptr)graph_wnd,0,0,origin_x2,origin_y2,600,400);
  rect_left2 = (*(i32 *)((char *)&graph_wnd + 700));
  rect_right2[0] = graph_wnd[0x2c4];
  rect_right2[1] = graph_wnd[0x2c5];
  rect_right2[2] = graph_wnd[0x2c6];
  rect_right2[3] = graph_wnd[0x2c7];
  rect_bottom2[0] = graph_wnd[0x2c8];
  rect_bottom2[1] = graph_wnd[0x2c9];
  rect_bottom2[2] = graph_wnd[0x2ca];
  rect_bottom2[3] = graph_wnd[0x2cb];
  rect_top2 = (*(i32 *)((char *)&graph_wnd + 704)) + 400;
  gfx_fill_rect((iptr)graph_wnd,(iptr)&rect_left2,0x14);
  rect_set_xywh((iptr)&rect_left2,origin_x2 + 8,origin_y2 + 2,0x248,0x16e);
  gfx_draw_rect_frame((iptr)graph_wnd,(iptr)&rect_left2,10);
  if (((game.game_flags & 0x80) == 0) || ((scenario_flags & 2) == 0)) {
    sample_count = (int)((int)game.turn + ((int)game.turn >> 0x1f & 3U)) >> 2;
  }
  else {
    sample_count = (int)game.turn / 2;
  }
  sample_count = int_clamp(sample_count,0,0x96);
  if (((game.game_flags & 0x80) == 0) || ((scenario_flags & 2) == 0)) {
    grid_step = 0x32;
  }
  else {
    grid_step = 0x19;
  }
  max_power = 0x32;
  for (civ = 1; civ < 8; civ++) {
    for (sample = 0; sample < sample_count; sample++) {
      if (max_power < (byte)(&power_graph_history)[sample * 8 + civ]) {
        max_power = (uint)(byte)(&power_graph_history)[sample * 8 + civ];
      }
    }
  }
  for (sample = 0; (sample <= game.turn && (sample < 0x259)); sample += grid_step)
  {
    if (((game.game_flags & 0x80) == 0) || ((scenario_flags & 2) == 0)) {
      grid_x = sample;
    }
    else {
      grid_x = sample * 2;
    }
    gfx_draw_line_color((iptr)graph_wnd,grid_x + origin_x2 + 8,origin_y2 + 2,
                       grid_x + origin_x2 + 8,origin_y2 + 0x170,10);
    if (sample % (grid_step * 2) == 0) {
      year2 = game_turn_to_year(sample + 1);
      text_clear();
      text_append_year(year2);
      text_set_colors(0x25,10,2,1);
      gfx_draw_text((iptr)((u8 *)&g.d_00679640),grid_x + origin_x2,origin_y2 + 0x172);
    }
  }
  surface_set_clip((DibSurface *)graph_wnd,(iptr)&rect_left2);
  for (civ = 1; civ < 8; civ++) {
    if (((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0) ||
       ((1 << ((byte)civ & 0x1f) & (uint)game.civs_at_start) != 0)) {
      prev_x = 0;
      prev_y = 0;
      for (sample = 0; (sample < sample_count && (sample < 0x96)); sample++) {
        point_x = sample * 4;
        point_y = (int)((uint)(byte)(&power_graph_history)[sample * 8 + civ] * 0x168) /
                   (int)max_power;
        gfx_draw_line_color((iptr)graph_wnd,prev_x + origin_x2 + 9,(origin_y2 - prev_y) + 0x171,
                           point_x + origin_x2 + 9,(origin_y2 - point_y) + 0x171,0x12);
        prev_x = point_x;
        prev_y = point_y;
      }
    }
  }
  surface_set_clip((DibSurface *)graph_wnd,(iptr)(graph_wnd + 700));
  text_set_font((iptr)&legend_font);
  legend_row = 0;
  for (civ = 1; civ < 8; civ++) {
    if (((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0) ||
       ((1 << ((byte)civ & 0x1f) & (uint)game.civs_at_start) != 0)) {
      civ_color = civ_color_primary(civ);
      text_set_colors(civ_color,10,2,1);
      next_row = legend_row + 1;
      text_y = legend_row * 0xe + origin_y2 + 1;
      text_x = origin_x2 + 10;
      civ_name = civ_name_plural(civ);
      gfx_draw_text(civ_name,text_x,text_y);
      prev_x = 0;
      prev_y = 0;
      for (sample = 0; (legend_row = next_row, sample < sample_count && (sample < 0x96));
          sample = sample + 1) {
        point_x = sample * 4;
        point_y = (int)((uint)(byte)(&power_graph_history)[sample * 8 + civ] * 0x168) /
                   (int)max_power;
        gfx_draw_line_color((iptr)graph_wnd,prev_x + origin_x2 + 8,(origin_y2 + 0x170) - prev_y,
                           point_x + origin_x2 + 8,(origin_y2 + 0x170) - point_y,civ_color);
        prev_x = point_x;
        prev_y = point_y;
      }
    }
  }
  window_show((WindowObjectView *)graph_wnd);
  dialog_init(&dialog2,(iptr)graph_wnd,0,0,0x114000);
  dialog2.wnd_width = (*(i32 *)((char *)&graph_wnd + 300));
  dialog2.wnd_height = (*(i32 *)((char *)&graph_wnd + 304));
  dialog2.origin_x = (*(i32 *)((char *)&graph_wnd + 292));
  dialog2.origin_y = (*(i32 *)((char *)&graph_wnd + 296));
  dlg_show_modal(&dialog2,0);
  if (bg_surface2 != (DibSurface *)0x0) {
    surface_delete(bg_surface2,1);
  }
  if (bg_palette != (GamePalette *)0x0) {
    palette_scalar_dtor(bg_palette,1);
  }
  (*(i8 *)((char *)&seh_state + 0)) = 2;
  /* inlined unwind funclet 004325c9 */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
  (*(i8 *)((char *)&seh_state + 0)) = 1;
  /* inlined unwind funclet 004325d5 */ { font_destroy((GameFont *)((iptr)&legend_font)); }
  seh_state = (uint)(*(i32 *)((char *)&seh_state + 1)) << 8;
  /* inlined unwind funclet 004325e1 */ { font_destroy((GameFont *)((iptr)((u8 *)&graph_wnd + 0x2d8))); }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 004325ed */ { frame_wnd_dtor((DibSurface *)((iptr)&graph_wnd)); }
  return;
}
#undef scenario_flags
#undef palette
#undef surface
#undef civ
#undef legend_row
#undef legend_font
#undef origin_x2
#undef prev_y
#undef prev_x
#undef grid_x
#undef graph_wnd
#undef dialog2
#undef year2
#undef civ_color
#undef point_y
#undef point_x
#undef sample
#undef origin_y2
#undef grid_step
#undef sample_count
#undef rect_left2
#undef rect_top2
#undef rect_right2
#undef rect_bottom2
#undef max_power
#undef bg_surface2
#undef bg_palette
#undef seh_prev
#undef seh_handler
#undef seh_state

/* 00432611 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define civ (*(iptr *)(frame_ + FRAME_OFF(4)))
#define civ2 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define i (*(int *)(frame_ + FRAME_OFF(12)))
#define city (*(iptr *)(frame_ + FRAME_OFF(16)))
#define advance (*(int *)(frame_ + FRAME_OFF(20)))
#define dialog2 (*(Dialog *)(frame_ + FRAME_OFF(24)))
#define quote_index (*(int *)(frame_ + FRAME_OFF(780)))
#define rank (*(int *)(frame_ + FRAME_OFF(784)))
#define title_buf (*(i8 (*)[80])(frame_ + FRAME_OFF(788)))
#define best_score (*(int *)(frame_ + FRAME_OFF(868)))
#define scores (*(int (*)[8])(frame_ + FRAME_OFF(872)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(904)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(908)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(912)))
void __cdecl historian_report_show(void)

{
  int category;
  int has_adv;
  iptr civ_name;
  i8 frame_[FRAME_OFF(920)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  dialog_ctor(&dialog2,0x2000);
  seh_state = 0;
  category = text_open_section((iptr)((u8 *)&g.d_006558e8),(iptr)((u8 *)&g.d_00626010));
  if (category == 0) {
    text_read_line(1);
    category = _atoi(&text_buffer);
    if (category != 0) {
      quote_index = rand_range(0,category - 1);
      for (i = 0; i <= quote_index; i++) {
        text_read_line(1);
      }
      text_set_string_arg(1,(iptr)((u8 *)&g.d_00679640));
      category = rand_range(0,4);
      text_read_section_line((iptr)((u8 *)&g.d_006558e8),(iptr)((u8 *)&g.d_0062601c),category);
      text_set_string_arg(2,(iptr)((u8 *)&g.d_00679640));
      dlg_load_game_section(&dialog2,(iptr)((u8 *)&g.d_00626028),0x40000);
      dialog_add_line
                ((DialogAddLineView *)&dialog2,(iptr)((u8 *)&g.d_00626030),0xffffffff,0xffffffff,0xffffffff,0);
      for (civ = 0; civ < 8; civ++) {
        scores[civ] = 0;
      }
      for (city = 0; city < game.num_cities; city++) {
        if (cities[city].id != 0) {
          if (category == 3) {
            scores[cities[city].owner] =
                 scores[cities[city].owner] +
                 (((int)cities[city].size + (int)(char)cities[city].happy) -
                 (int)(char)cities[city].unhappy);
          }
          else if (category == 4) {
            scores[cities[city].owner] =
                 scores[cities[city].owner] + (int)cities[city].size;
          }
        }
      }
      for (civ = 0; civ < 8; civ++) {
        if (category == 0) {
          scores[civ] += civs[civ].gold;
        }
        else if (category == 1) {
          scores[civ] += (uint)civs[civ].military_strength;
        }
        else if (category == 2) {
          for (advance = 0; advance < 100; advance++) {
            has_adv = civ_has_advance(civ,advance);
            if (has_adv != 0) {
              scores[civ]++;
            }
          }
        }
      }
      category = text_open_section((iptr)((u8 *)&g.d_006558e8),(iptr)((u8 *)&g.d_00626034));
      if (category == 0) {
        for (rank = 1; rank < 8; rank++) {
          text_read_line(1);
          crt_strcpy(title_buf,&text_buffer);
          civ2 = -1;
          best_score = 0;
          for (civ = 1; civ < 8; civ++) {
            if ((best_score <= scores[civ]) &&
               ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0)) {
              best_score = scores[civ];
              civ2 = civ;
            }
          }
          if (civ2 < 0) break;
          scores[civ2] = -1;
          text_clear();
          text_append((iptr)((u8 *)&g.d_00626040));
          text_append_int(rank);
          text_append_period();
          text_append_label(0x174);
          text_append_space();
          text_append((iptr)title_buf);
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
          civ_name = civ_name_plural(civ2);
          text_append(civ_name);
          if (((human_civ == civ2) ||
              ((*(byte *)&civs[human_civ].treaties[civ2] & 1) != 0)) ||
             (game.difficulty == '\0')) {
            dialog_add_line
                      ((DialogAddLineView *)&dialog2,(iptr)((u8 *)&g.d_00679640),0xffffffff,0xffffffff,0xffffffff,0);
          }
        }
        dlg_show_modal(&dialog2,0);
      }
    }
  }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 00432bf8 */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
  return;
}
#undef human_civ
#undef text_buffer
#undef civ
#undef civ2
#undef i
#undef city
#undef advance
#undef dialog2
#undef quote_index
#undef rank
#undef title_buf
#undef best_score
#undef scores
#undef seh_prev
#undef seh_handler
#undef seh_state

/* 00432c1c auto */
#define advisor_client_width (*(int *)((u8 *)&g.d_0063ec3c))
#define advisor_client_x (*(int *)((u8 *)&g.d_0063ec34))
#define advisor_row_height (*(i32 *)((u8 *)&g.d_0063ef80))
#define advisor_list_top_i32 (*(i32 *)((u8 *)&g.d_0063ef78))
#define advisor_list_height_i32 (*(i32 *)((u8 *)&g.d_0063ef7c))
#define icon_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define top_cities (*(iptr (*)[5])(frame_ + FRAME_OFF(20)))
#define bottom (*(int *)(frame_ + FRAME_OFF(40)))
#define city_x (*(int *)(frame_ + FRAME_OFF(44)))
#define box_bottom (*(int *)(frame_ + FRAME_OFF(48)))
#define y2 (*(int *)(frame_ + FRAME_OFF(52)))
#define city (*(iptr *)(frame_ + FRAME_OFF(56)))
#define box_top (*(int *)(frame_ + FRAME_OFF(60)))
#define mid_x (*(int *)(frame_ + FRAME_OFF(64)))
#define span_width (*(int *)(frame_ + FRAME_OFF(68)))
#define right_x (*(int *)(frame_ + FRAME_OFF(72)))
#define citizens_x (*(int *)(frame_ + FRAME_OFF(76)))
#define wonder_x (*(int *)(frame_ + FRAME_OFF(80)))
#define shift (*(iptr *)(frame_ + FRAME_OFF(84)))
#define wonder (*(iptr *)(frame_ + FRAME_OFF(88)))
#define rank (*(iptr *)(frame_ + FRAME_OFF(92)))
#define line_height (*(int *)(frame_ + FRAME_OFF(96)))
#define top_scores (*(iptr *)(frame_ + FRAME_OFF(100)))
#define top_scores_rest (*(int (*)[4])(frame_ + FRAME_OFF(104)))
#define score (*(int *)(frame_ + FRAME_OFF(120)))
#define box_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(124)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl top_cities_draw(void)

{
  iptr text;
  i32 color;
  i32 bg_color;
  i32 shadow_color;
  i32 shadow_color2;
  i8 frame_[FRAME_OFF(144)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (rank = 0; rank < 5; rank++) {
    top_cities[rank] = -1;
    (&top_scores)[rank] = top_cities[rank];
  }
  city = 0;
  while( true ) {
    if (game.num_cities <= city) {
      frame_wnd_layout((FrameWindow *)&advisor_window);
      frame_wnd_draw_caption((FrameWindow *)&advisor_window);
      picwnd_blit((PictureWindow *)&advisor_window);
      y2 = advisor_client_y + 2;
      bottom = advisor_client_y + 0x174;
      line_height = font_line_spacing((GameFont *)&advisor_font);
      text_set_surface((iptr)((u8 *)&g.d_0063eb10));
      text_set_font((iptr)((u8 *)&g.d_0063eac0));
      text_set_colors(0x25,0x12,2,1);
      text_clear();
      text = label_string(*(i32 *)(label_string_ids + 0x554));
      text_append(text);
      gfx_draw_text_centered((iptr)((u8 *)&g.d_00679640),advisor_client_x,y2,advisor_client_width);
      advisor_list_top_i32 = y2 + line_height;
      y2 = advisor_list_top_i32 + 10;
      line_height = 0x18;
      advisor_row_height = 0x18;
      advisor_list_top_i32 += 0x12;
      advisor_list_height_i32 = bottom - y2;
      for (rank = 0; rank < 5; rank++) {
        city = top_cities[rank];
        if (-1 < top_cities[rank]) {
          box_top = y2;
          text_clear();
          text_append_int(rank + 1);
          text_append_period();
          text_append(city * 0x58 + (iptr)((u8 *)&cities + 32));
          text_append_space();
          text_append_lparen();
          text = civ_get_adjective((int)cities[city].owner);
          text_append(text);
          text_append_rparen();
          text_set_font((iptr)((u8 *)&g.d_0063eac0));
          shadow_color2 = 1;
          shadow_color = 1;
          bg_color = 0x12;
          color = civ_color_secondary((int)cities[city].owner);
          text_set_colors(color,bg_color,shadow_color,shadow_color2);
          gfx_draw_text_centered((iptr)((u8 *)&g.d_00679640),advisor_client_x,y2,advisor_client_width);
          y2 += line_height;
          city_x = advisor_client_x + 5;
          gfx_draw_city((iptr)((u8 *)&g.d_0063eb10),city,0x1000,city_x,y2 - 0xf,0);
          citizens_x = city_x + 0x42;
          right_x = advisor_client_width + advisor_client_x - 5;
          span_width = right_x - citizens_x;
          mid_x = (span_width >> 1) + citizens_x;
          advisor_draw_city_citizens(city,citizens_x,y2,(mid_x - 2) - citizens_x,
                             (int)(char)cities[city].happy,(int)(char)cities[city].unhappy,0
                            );
          wonder_x = mid_x;
          for (wonder = 0; wonder < 0x1c; wonder++) {
            if ((game.wonder_city[wonder] == city) && (0x23 < right_x - wonder_x)) {
              sprite_draw
                        ((Sprite *)(&wonder_icon_sprites + wonder * 0x3c),(iptr)icon_rect,(iptr)((u8 *)&g.d_0063eb10),
                         wonder_x,y2 + 6);
              wonder_x += 0x26;
            }
          }
          box_bottom = y2 + 0x20;
          y2 = box_bottom;
          rect_set((iptr)box_rect,advisor_client_x + 3,box_top,
                             advisor_client_width + advisor_client_x - 3,box_bottom);
          color = civ_color_primary((int)cities[city].owner);
          gfx_draw_rect_frame((iptr)((u8 *)&g.d_0063eb10),(iptr)box_rect,color);
          y2 += 6;
        }
      }
      wnd_blit_surface((DibSurface *)&advisor_window);
      return;
    }
    if (cities[city].id != 0) break;
LAB_00432c6b:
    city++;
  }
  score = ((int)cities[city].size + (int)(char)cities[city].happy) -
             (int)(char)cities[city].unhappy;
  for (wonder = 0; wonder < 0x1c; wonder++) {
    if (game.wonder_city[wonder] == city) {
      score += 10;
    }
  }
  rank = 0;
LAB_00432d26:
  if (rank < 5) {
    if (score <= (&top_scores)[rank]) goto LAB_00432d23;
    for (shift = 3; rank <= shift; shift--) {
      (&top_scores)[shift + 1] = (&top_scores)[shift];
      top_cities[shift + 1] = top_cities[shift];
    }
    (&top_scores)[rank] = score;
    top_cities[rank] = city;
  }
  goto LAB_00432c6b;
LAB_00432d23:
  rank++;
  goto LAB_00432d26;
}
#undef advisor_client_width
#undef advisor_client_x
#undef advisor_row_height
#undef advisor_list_top_i32
#undef advisor_list_height_i32
#undef icon_rect
#undef top_cities
#undef bottom
#undef city_x
#undef box_bottom
#undef y2
#undef city
#undef box_top
#undef mid_x
#undef span_width
#undef right_x
#undef citizens_x
#undef wonder_x
#undef shift
#undef wonder
#undef rank
#undef line_height
#undef top_scores
#undef top_scores_rest
#undef score
#undef box_rect

/* 00433122 auto */
#define advisor_modal_start_ticks_i32 (*(i32 *)((u8 *)&g.d_00625ec0))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl top_cities_show(iptr report_civ)

{
  picwnd_open((PictureWindow *)&advisor_window,8,8,1,600,400,0,0);
  advisor_report_civ = report_civ;
  advisor_add_close_button((ViewWindow *)&advisor_window);
  wnd_set_redraw_callback((SurfaceWindow *)&advisor_window,(iptr)top_cities_draw);
  wnd_repaint((SurfaceWindow *)&advisor_window);
  window_show((WindowObjectView *)&advisor_window);
  if (2 < game.multiplayer) {
    wnd_set_modal_idle_callback((ModalMenuWindow *)&advisor_wnd,(iptr)advisor_mp_idle);
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
#define best_value (*(uint *)(frame_ + FRAME_OFF(4)))
#define rank (*(int *)(frame_ + FRAME_OFF(8)))
#define rival (*(int *)(frame_ + FRAME_OFF(12)))
#define civ2 (*(iptr *)(frame_ + FRAME_OFF(16)))
void __cdecl
demographics_draw_rank(iptr values,iptr civ,uint y,iptr unit_suffix,int left_x,int right_x)

{
  int has_wonder;
  iptr civ_name;
  i32 color;
  i32 bg_color;
  i32 shadow_color;
  i32 shadow_color2;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  rank = 1;
  best_value = 0xffffd8f1;
  civ2 = civ;
  if ((int)y < 0) {
    *(int *)(values + civ * 4) = -*(int *)(values + civ * 4);
  }
  for (rival = 1; rival < 8; rival++) {
    if ((1 << ((byte)rival & 0x1f) & (uint)game.civs_alive) != 0) {
      if (((int)y < 0) && (civ != rival)) {
        *(int *)(values + rival * 4) = -*(int *)(values + rival * 4);
      }
      if (*(int *)(values + civ * 4) < *(int *)(values + rival * 4)) {
        rank++;
      }
      if ((int)best_value < *(int *)(values + rival * 4)) {
        best_value = *(uint *)(values + rival * 4);
        civ2 = rival;
      }
    }
  }
  if ((int)y < 1) {
    y = ~y + 1;
  }
  if ((int)best_value < 1) {
    best_value = ~best_value + 1;
  }
  text_clear();
  text_append_label(rank + 0x189);
  gfx_draw_text((iptr)((u8 *)&g.d_00679640),left_x,y);
  if ((civ != civ2) &&
     (((((*(byte *)&civs[human_civ].treaties[civ2] & 0x80) != 0 ||
        (has_wonder = civ_has_wonder(human_civ,0x18), has_wonder != 0)) ||
       (has_wonder = civ_has_wonder(human_civ,9), has_wonder != 0)) ||
      (((game.reveal_map != '\0' || (has_wonder = civ_has_wonder(civ,9), has_wonder != 0)) ||
       (has_wonder = civ_has_wonder(civ,0x18), has_wonder != 0)))))) {
    text_clear();
    text_append_lparen();
    civ_name = civ_name_plural(civ2);
    text_append(civ_name);
    text_append((iptr)((u8 *)&g.d_00626044));
    text_append_long(best_value);
    text_append(unit_suffix);
    text_append_rparen();
    shadow_color2 = 1;
    shadow_color = 1;
    bg_color = 0x12;
    color = civ_color_secondary(civ2);
    text_set_colors(color,bg_color,shadow_color,shadow_color2);
    gfx_draw_text_right((iptr)((u8 *)&g.d_00679640),left_x,y,right_x - left_x);
  }
  return;
}
#undef human_civ
#undef best_value
#undef rank
#undef rival
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
#define pollution (*(int (*)[8])(frame_ + FRAME_OFF(0)))
#define land_area (*(int (*)[8])(frame_ + FRAME_OFF(32)))
#define bottom (*(int *)(frame_ + FRAME_OFF(64)))
#define right_x (*(int *)(frame_ + FRAME_OFF(68)))
#define y2 (*(int *)(frame_ + FRAME_OFF(72)))
#define city (*(iptr *)(frame_ + FRAME_OFF(76)))
#define rank_x (*(int *)(frame_ + FRAME_OFF(80)))
#define approval (*(int (*)[8])(frame_ + FRAME_OFF(84)))
#define value_x (*(int *)(frame_ + FRAME_OFF(116)))
#define label_x (*(int *)(frame_ + FRAME_OFF(120)))
#define food_surplus (*(int (*)[8])(frame_ + FRAME_OFF(124)))
#define shields2 (*(int (*)[8])(frame_ + FRAME_OFF(156)))
#define city_pollution2 (*(int *)(frame_ + FRAME_OFF(188)))
#define tile_owner2 (*(u8 * *)(frame_ + FRAME_OFF(192)))
#define income (*(int (*)[8])(frame_ + FRAME_OFF(196)))
#define gnp (*(int (*)[8])(frame_ + FRAME_OFF(228)))
#define label_color (*(i32 *)(frame_ + FRAME_OFF(260)))
#define civ2 (*(uptr *)(frame_ + FRAME_OFF(264)))
#define values (*(int (*)[8])(frame_ + FRAME_OFF(268)))
#define tile (*(int *)(frame_ + FRAME_OFF(300)))
#define suffix_buf (*(i8 (*)[80])(frame_ + FRAME_OFF(304)))
#define row_height (*(int *)(frame_ + FRAME_OFF(384)))
#define population (*(int (*)[8])(frame_ + FRAME_OFF(388)))
#define life_expect (*(int (*)[8])(frame_ + FRAME_OFF(420)))
#define line_left (*(int *)(frame_ + FRAME_OFF(452)))
#define literacy (*(int (*)[8])(frame_ + FRAME_OFF(456)))
#define line_right (*(int *)(frame_ + FRAME_OFF(488)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl demographics_draw(void)

{
  int row_y;
  iptr label;
  int value;
  int text_y;
  iptr civ;
  i8 frame_[FRAME_OFF(496)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ = advisor_report_civ;
  for (civ2 = 0; (int)civ2 < 8; civ2++) {
    life_expect[civ2] = 0;
    pollution[civ2] = life_expect[civ2];
    approval[civ2] = pollution[civ2];
    food_surplus[civ2] = 0;
    land_area[civ2] = food_surplus[civ2];
    income[civ2] = land_area[civ2];
    literacy[civ2] = income[civ2];
    gnp[civ2] = 0;
    shields2[civ2] = gnp[civ2];
    population[civ2] = 1;
  }
  tile_owner2 = &map_tiles->owner;
  for (tile = 0; tile < map.area; tile++) {
    civ2 = (int)(uint)*tile_owner2 >> 4;
    if (civ2 < 8) {
      land_area[civ2]++;
    }
    tile_owner2 += 6;
  }
  for (city = 0; city < game.num_cities; city++) {
    if (cities[city].id != 0) {
      civ2 = (uptr)cities[city].owner;
      city_recalc(city,1);
      population[civ2] += (int)cities[city].size;
      approval[civ2] =
           approval[civ2] + ((cities[city].size + city_happy_count) - city_unhappy_count);
      income[civ2] = income[civ2] + city_lux_total * 2 + city_tax_total;
      food_surplus[civ2] = food_surplus[civ2] + city_yield_totals + cities[city].size * -2;
      gnp[civ2] = gnp[civ2] + city_total_shields + city_total_trade + city_yield_totals;
      shields2[civ2] += city_total_shields;
      if (city_pollution_divisor < 2) {
        city_pollution_divisor = 1;
      }
      row_y = cities[city].size * city_pop_pollution_factor;
      city_pollution2 = city_total_shields / city_pollution_divisor - 0x14 + ((int)(row_y + (row_y >> 0x1f & 3U)) >> 2);
      if (0 < city_pollution2) {
        pollution[civ2] += city_pollution2;
      }
      row_y = city_has_improvement(city,3);
      if ((row_y != 0) || (row_y = civ_has_wonder(civ2,0), row_y != 0)) {
        life_expect[civ2] += (int)cities[city].size;
      }
      row_y = city_has_improvement(city,9);
      if (row_y != 0) {
        life_expect[civ2] += (int)cities[city].size;
      }
      row_y = city_has_improvement(city,0x17);
      if (row_y != 0) {
        life_expect[civ2] += (int)cities[city].size;
      }
      row_y = city_has_improvement(city,6);
      if (row_y != 0) {
        literacy[civ2] += (int)cities[city].size;
      }
      row_y = city_has_improvement(city,0xc);
      if (row_y != 0) {
        literacy[civ2] += (int)cities[city].size;
      }
    }
  }
  frame_wnd_layout((FrameWindow *)&advisor_window);
  frame_wnd_draw_caption((FrameWindow *)&advisor_window);
  picwnd_blit((PictureWindow *)&advisor_window);
  y2 = advisor_client_y + 2;
  bottom = advisor_client_y + 0x174;
  row_height = font_line_spacing((GameFont *)&advisor_font);
  text_set_surface((iptr)((u8 *)&g.d_0063eb10));
  text_set_font((iptr)((u8 *)&g.d_0063eac0));
  text_set_colors(0x25,0x12,2,1);
  text_clear();
  if (game_language == 0) {
    label = civ_get_adjective(civ);
    text_append(label);
    text_append_space();
  }
  label = label_string(*(i32 *)(label_string_ids + 0x558));
  text_append(label);
  gfx_draw_text_centered((iptr)((u8 *)&g.d_00679640),advisor_client_x,y2,advisor_client_width);
  row_y = y2 + row_height + 10;
  row_height = 0x19;
  advisor_row_height = 0x19;
  advisor_list_height_i32 = bottom - row_y;
  label_color = 0x25;
  label_x = advisor_client_x + 2;
  value_x = advisor_client_x + 0xb4;
  rank_x = advisor_client_x + 0x142;
  right_x = advisor_client_width + label_x - 4;
  line_left = advisor_client_x + 2;
  line_right = advisor_client_width + advisor_client_x - 2;
  advisor_list_top_i32 = row_y;
  y2 = row_y;
  text_set_colors(0x25,0x12,0xffffffff,0xffffffff);
  value = label_x;
  text_y = row_y;
  label = label_string(*(i32 *)(label_string_ids + 0x5d4));
  gfx_draw_text(label,value,text_y);
  for (civ2 = 1; (int)civ2 < 8; civ2++) {
    value = population[civ2];
    if (value < 2) {
      value = 1;
    }
    values[civ2] = (approval[civ2] * 0x32) / value;
    if (civ2 == civ) {
      text_clear();
      text_append_long(values[civ2]);
      text_append_percent();
      gfx_draw_text((iptr)((u8 *)&g.d_00679640),value_x,row_y);
    }
  }
  demographics_draw_rank((iptr)values,civ,row_y,(iptr)((u8 *)&g.d_00626048),rank_x,right_x);
  gfx_draw_hline((iptr)((u8 *)&g.d_0063eb10),line_left,line_right,row_y + row_height - 2,99);
  row_y += row_height;
  text_set_colors(label_color,0x12,0xffffffff,0xffffffff);
  value = label_x;
  text_y = row_y;
  label = label_string(*(i32 *)(label_string_ids + 0x5d8));
  gfx_draw_text(label,value,text_y);
  for (civ2 = 1; (int)civ2 < 8; civ2++) {
    value = civ_total_population(civ2);
    values[civ2] = value;
    if (civ2 == civ) {
      text_clear();
      text_append_population(civ2,0xffffffff);
      gfx_draw_text((iptr)((u8 *)&g.d_00679640),value_x,row_y);
    }
  }
  demographics_draw_rank((iptr)values,civ,row_y,(iptr)((u8 *)&g.d_0062604c),rank_x,right_x);
  gfx_draw_hline((iptr)((u8 *)&g.d_0063eb10),line_left,line_right,row_y + row_height - 2,99);
  row_y += row_height;
  text_set_colors(label_color,0x12,0xffffffff,0xffffffff);
  value = label_x;
  text_y = row_y;
  label = label_string(*(i32 *)(label_string_ids + 0x5dc));
  gfx_draw_text(label,value,text_y);
  for (civ2 = 1; (int)civ2 < 8; civ2++) {
    values[civ2] = income[civ2];
    if (civ2 == civ) {
      text_clear();
      text_append_long(values[civ2]);
      text_append_space();
      text_append_label(0x188);
      text_append_space();
      text_append((iptr)((u8 *)&g.d_00626054));
      gfx_draw_text((iptr)((u8 *)&g.d_00679640),value_x,row_y);
    }
  }
  demographics_draw_rank((iptr)values,civ,row_y,(iptr)((u8 *)&g.d_00626058),rank_x,right_x);
  gfx_draw_hline((iptr)((u8 *)&g.d_0063eb10),line_left,line_right,row_y + row_height - 2,99);
  row_y += row_height;
  text_set_colors(label_color,0x12,0xffffffff,0xffffffff);
  value = label_x;
  text_y = row_y;
  label = label_string(*(i32 *)(label_string_ids + 0x5e0));
  gfx_draw_text(label,value,text_y);
  for (civ2 = 1; (int)civ2 < 8; civ2++) {
    values[civ2] = shields2[civ2];
    if (civ2 == civ) {
      text_clear();
      text_append_long(values[civ2]);
      text_append_space();
      text_append_label(0x182);
      gfx_draw_text((iptr)((u8 *)&g.d_00679640),value_x,row_y);
    }
  }
  str_clear((iptr)suffix_buf);
  str_append_label((iptr)suffix_buf,0x182);
  demographics_draw_rank((iptr)values,civ,row_y,(iptr)suffix_buf,rank_x,right_x);
  gfx_draw_hline((iptr)((u8 *)&g.d_0063eb10),line_left,line_right,row_y + row_height - 2,99);
  row_y += row_height;
  text_set_colors(label_color,0x12,0xffffffff,0xffffffff);
  value = label_x;
  text_y = row_y;
  label = label_string(*(i32 *)(label_string_ids + 0x5e4));
  gfx_draw_text(label,value,text_y);
  for (civ2 = 1; (int)civ2 < 8; civ2++) {
    values[civ2] = land_area[civ2];
    if (civ2 == civ) {
      text_clear();
      text_append_long(values[civ2]);
      text_append((iptr)((u8 *)&g.d_0062605c));
      text_append_label(0x183);
      gfx_draw_text((iptr)((u8 *)&g.d_00679640),value_x,row_y);
    }
  }
  demographics_draw_rank((iptr)values,civ,row_y,(iptr)((u8 *)&g.d_00626064),rank_x,right_x);
  gfx_draw_hline((iptr)((u8 *)&g.d_0063eb10),line_left,line_right,row_y + row_height - 2,99);
  row_y += row_height;
  text_set_colors(label_color,0x12,0xffffffff,0xffffffff);
  value = label_x;
  text_y = row_y;
  label = label_string(*(i32 *)(label_string_ids + 0x5e8));
  gfx_draw_text(label,value,text_y);
  for (civ2 = 1; (int)civ2 < 8; civ2++) {
    values[civ2] =
         ((population[civ2] * 2 + literacy[civ2]) * 2) / population[civ2];
    value = civ_has_advance(civ2,1);
    if (value != 0) {
      values[civ2] = values[civ2] << 1;
    }
    value = civ_has_advance(civ2,0x58);
    if (value != 0) {
      values[civ2] = values[civ2] << 1;
    }
    value = civ_has_advance(civ2,0x2b);
    if (value != 0) {
      values[civ2] = values[civ2] << 1;
    }
    value = civ_has_advance(civ2,0x55);
    if (value != 0) {
      values[civ2] = values[civ2] << 1;
    }
    value = int_clamp(values[civ2],0,100);
    values[civ2] = value;
    if (civ2 == civ) {
      text_clear();
      text_append_long(values[civ2]);
      text_append_percent();
      gfx_draw_text((iptr)((u8 *)&g.d_00679640),value_x,row_y);
    }
  }
  demographics_draw_rank((iptr)values,civ,row_y,(iptr)((u8 *)&g.d_0062606c),rank_x,right_x);
  gfx_draw_hline((iptr)((u8 *)&g.d_0063eb10),line_left,line_right,row_y + row_height - 2,99);
  row_y += row_height;
  text_set_colors(label_color,0x12,0xffffffff,0xffffffff);
  value = label_x;
  text_y = row_y;
  label = label_string(*(i32 *)(label_string_ids + 0x5ec));
  gfx_draw_text(label,value,text_y);
  for (civ2 = 1; (int)civ2 < 8; civ2++) {
    values[civ2] =
         (population[civ2] * 0x32) / (life_expect[civ2] + population[civ2]);
    value = civ_has_advance(civ2,0x32);
    if (value != 0) {
      values[civ2] = values[civ2] / 2;
    }
    value = civ_has_wonder(civ2,0x1b);
    if (value != 0) {
      values[civ2] = values[civ2] / 2;
    }
    life_expect[civ2] = (int)(0x708 / (longlong)(values[civ2] + 0x14));
    if (civ2 == civ) {
      text_clear();
      text_append_long(values[civ2]);
      text_append_percent();
      gfx_draw_text((iptr)((u8 *)&g.d_00679640),value_x,row_y);
    }
  }
  demographics_draw_rank((iptr)values,civ,-row_y,(iptr)((u8 *)&g.d_00626070),rank_x,right_x);
  gfx_draw_hline((iptr)((u8 *)&g.d_0063eb10),line_left,line_right,row_y + row_height - 2,99);
  row_y += row_height;
  text_set_colors(label_color,0x12,0xffffffff,0xffffffff);
  value = label_x;
  text_y = row_y;
  label = label_string(*(i32 *)(label_string_ids + 0x5f0));
  gfx_draw_text(label,value,text_y);
  for (civ2 = 1; (int)civ2 < 8; civ2++) {
    values[civ2] = pollution[civ2];
    life_expect[civ2] =
         life_expect[civ2] - (pollution[civ2] * 10) / population[civ2];
    if (civ2 == civ) {
      text_clear();
      text_append_long(values[civ2]);
      text_append((iptr)((u8 *)&g.d_00626074));
      text_append_label(0x184);
      gfx_draw_text((iptr)((u8 *)&g.d_00679640),value_x,row_y);
    }
  }
  str_clear((iptr)suffix_buf);
  str_append((iptr)suffix_buf,(iptr)((u8 *)&g.d_00626078));
  str_append_label((iptr)suffix_buf,0x184);
  demographics_draw_rank((iptr)values,civ,-row_y,(iptr)suffix_buf,rank_x,right_x);
  gfx_draw_hline((iptr)((u8 *)&g.d_0063eb10),line_left,line_right,row_y + row_height - 2,99);
  row_y += row_height;
  text_set_colors(label_color,0x12,0xffffffff,0xffffffff);
  value = label_x;
  text_y = row_y;
  label = label_string(*(i32 *)(label_string_ids + 0x5f4));
  gfx_draw_text(label,value,text_y);
  for (civ2 = 1; (int)civ2 < 8; civ2++) {
    value = int_clamp(life_expect[civ2],0x14,99);
    values[civ2] = value;
    if (civ2 == civ) {
      text_clear();
      text_append_long(values[civ2]);
      text_append_space();
      text_append_label(0x185);
      gfx_draw_text((iptr)((u8 *)&g.d_00679640),value_x,row_y);
    }
  }
  str_clear((iptr)suffix_buf);
  str_append_label((iptr)suffix_buf,0x186);
  demographics_draw_rank((iptr)values,civ,row_y,(iptr)suffix_buf,rank_x,right_x);
  gfx_draw_hline((iptr)((u8 *)&g.d_0063eb10),line_left,line_right,row_y + row_height - 2,99);
  row_y += row_height;
  text_set_colors(label_color,0x12,0xffffffff,0xffffffff);
  value = label_x;
  text_y = row_y;
  label = label_string(*(i32 *)(label_string_ids + 0x5f8));
  gfx_draw_text(label,value,text_y);
  for (civ2 = 1; (int)civ2 < 8; civ2++) {
    values[civ2] = (food_surplus[civ2] * 0x28) / population[civ2] + 0x14;
    if (civ2 == civ) {
      text_clear();
      text_append_long(values[civ2] / 10);
      text_append((iptr)((u8 *)&g.d_0062607c));
      text_append_long(values[civ2] % 10);
      text_append_space();
      text_append_label(0x187);
      gfx_draw_text((iptr)((u8 *)&g.d_00679640),value_x,row_y);
    }
    values[civ2] = values[civ2] / 10;
  }
  demographics_draw_rank((iptr)values,civ,row_y,(iptr)((u8 *)&g.d_00626080),rank_x,right_x);
  gfx_draw_hline((iptr)((u8 *)&g.d_0063eb10),line_left,line_right,row_y + row_height - 2,99);
  row_y += row_height;
  text_set_colors(label_color,0x12,0xffffffff,0xffffffff);
  value = label_x;
  text_y = row_y;
  label = label_string(*(i32 *)(label_string_ids + 0x5fc));
  gfx_draw_text(label,value,text_y);
  for (civ2 = 1; (int)civ2 < 8; civ2++) {
    values[civ2] = (civs[civ2].num_military_units * 10) / population[civ2];
    if (civ2 == civ) {
      text_clear();
      text_append_long(values[civ2]);
      text_append_space();
      text_append_label(0x185);
      gfx_draw_text((iptr)((u8 *)&g.d_00679640),value_x,row_y);
    }
  }
  demographics_draw_rank((iptr)values,civ,row_y,(iptr)suffix_buf,rank_x,right_x);
  gfx_draw_hline((iptr)((u8 *)&g.d_0063eb10),line_left,line_right,row_y + row_height - 2,99);
  row_y += row_height;
  text_set_colors(label_color,0x12,0xffffffff,0xffffffff);
  value = label_x;
  text_y = row_y;
  label = label_string(*(i32 *)(label_string_ids + 0x600));
  gfx_draw_text(label,value,text_y);
  for (civ2 = 1; (int)civ2 < 8; civ2++) {
    if (income[civ2] <
        (int)(30000 / (ulonglong)(longlong)(int)(civs[civ2].num_advances + 1))) {
      values[civ2] =
           (int)((uint)civs[civ2].num_advances * income[civ2]) / population[civ2];
    }
    else {
      values[civ2] =
           (income[civ2] / population[civ2]) * (uint)civs[civ2].num_advances;
    }
    if (civ2 == civ) {
      text_clear();
      text_append_long(values[civ2]);
      text_append((iptr)((u8 *)&g.d_00626084));
      text_append_label(0x189);
      gfx_draw_text((iptr)((u8 *)&g.d_00679640),value_x,row_y);
    }
  }
  demographics_draw_rank((iptr)values,civ,row_y,(iptr)((u8 *)&g.d_00626088),rank_x,right_x);
  gfx_draw_hline((iptr)((u8 *)&g.d_0063eb10),line_left,line_right,row_y + row_height - 2,99);
  row_y += row_height;
  text_set_colors(label_color,0x12,0xffffffff,0xffffffff);
  value = label_x;
  text_y = row_y;
  label = label_string(*(i32 *)(label_string_ids + 0x604));
  gfx_draw_text(label,value,text_y);
  for (civ2 = 1; (int)civ2 < 8; civ2++) {
    values[civ2] = (gnp[civ2] * 10) / population[civ2];
    if (civ2 == civ) {
      text_clear();
      text_append_long(values[civ2]);
      gfx_draw_text((iptr)((u8 *)&g.d_00679640),value_x,row_y);
    }
  }
  demographics_draw_rank((iptr)values,civ,row_y,(iptr)((u8 *)&g.d_0062608c),rank_x,right_x);
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
#undef pollution
#undef land_area
#undef bottom
#undef right_x
#undef y2
#undef city
#undef rank_x
#undef approval
#undef value_x
#undef label_x
#undef food_surplus
#undef shields2
#undef city_pollution2
#undef tile_owner2
#undef income
#undef gnp
#undef label_color
#undef civ2
#undef values
#undef tile
#undef suffix_buf
#undef row_height
#undef population
#undef life_expect
#undef line_left
#undef literacy
#undef line_right

/* 00434d8a auto */
#define advisor_modal_start_ticks_i32 (*(i32 *)((u8 *)&g.d_00625ec0))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl demographics_show(iptr report_civ)

{
  picwnd_open((PictureWindow *)&advisor_window,9,9,1,600,400,0,0);
  advisor_report_civ = report_civ;
  advisor_add_close_button((ViewWindow *)&advisor_window);
  wnd_set_redraw_callback((SurfaceWindow *)&advisor_window,(iptr)demographics_draw);
  wnd_repaint((SurfaceWindow *)&advisor_window);
  window_show((WindowObjectView *)&advisor_window);
  if (2 < game.multiplayer) {
    wnd_set_modal_idle_callback((ModalMenuWindow *)&advisor_wnd,(iptr)advisor_mp_idle);
  }
  advisor_modal_start_ticks_i32 = timer_ticks();
  wnd_run_modal_loop((ModalMenuWindow *)&advisor_wnd);
  wnd_set_modal_idle_callback((ModalMenuWindow *)&advisor_wnd,0);
  picwnd_close((PictureWindowCore *)&advisor_window);
  return;
}
#undef advisor_modal_start_ticks_i32

/* 00436287 auto */
void __cdecl advisor_refresh_if_open(iptr report_id)

{
  if (report_id == 0xc) {
    if (casualty_window_report_id == 0xc) {
      wnd_repaint((SurfaceWindow *)&casualty_window);
    }
  }
  else if (advisor_report_id == report_id) {
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
#define year2 (*(uint *)(frame_ + FRAME_OFF(0)))
#define abs_year (*(uint *)(frame_ + FRAME_OFF(4)))
#define abs_year2 (*(uint *)(frame_ + FRAME_OFF(8)))
#define month_index (*(iptr *)(frame_ + FRAME_OFF(12)))
#define month (*(int *)(frame_ + FRAME_OFF(16)))
#define year_step (*(int *)(frame_ + FRAME_OFF(20)))
#define entry_y (*(int *)(frame_ + FRAME_OFF(28)))
#define entry (*(int *)(frame_ + FRAME_OFF(44)))
#define line (*(int *)(frame_ + FRAME_OFF(52)))
#define line_buf (*(i8 (*)[80])(frame_ + FRAME_OFF(56)))
#define line_height (*(int *)(frame_ + FRAME_OFF(136)))
#define open_err (*(int *)(frame_ + FRAME_OFF(140)))
#define title_buf (*(i8 (*)[132])(frame_ + FRAME_OFF(144)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl hall_of_fame_draw(void)

{
  int highlight;
  int y;
  int bottom;
  iptr text;
  int font_height;
  i8 frame_[FRAME_OFF(280)] __attribute__((aligned(8)));  /* original stack frame */
  
  highlight = advisor_report_param;
  frame_wnd_layout((FrameWindow *)&advisor_window);
  frame_wnd_draw_caption((FrameWindow *)&advisor_window);
  picwnd_blit((PictureWindow *)&advisor_window);
  y = advisor_client_y + 1;
  bottom = advisor_client_y + 0x174;
  line_height = font_line_spacing((GameFont *)&advisor_font);
  line_height -= 2;
  text_set_surface((iptr)((u8 *)&g.d_0063eb10));
  text_set_font((iptr)((u8 *)&g.d_0063eac0));
  text_set_colors(0x25,0x12,2,1);
  text_clear();
  text = label_string(*(i32 *)(label_string_ids + 0x6e8));
  text_append(text);
  gfx_draw_text_centered((iptr)((u8 *)&g.d_00679640),advisor_client_x,y,advisor_client_width);
  y += line_height;
  text_set_font((iptr)((u8 *)&g.d_0063f030));
  font_height = font_line_spacing((GameFont *)&hall_of_fame_font);
  advisor_row_height = font_height - 3;
  advisor_list_top_i32 = y + 6;
  advisor_list_height_i32 = bottom - advisor_list_top_i32;
  entry_y = advisor_list_top_i32;
  line_height = advisor_row_height;
  for (entry = 0; entry < 6; entry++) {
    if (((entry != 5) || (highlight == 5)) && (-1 < *(short *)(&hall_of_fame_entries + entry * 0x48))) {
      if (*(short *)(&hof_entry_leader_female + entry * 0x48) == 0) {
        crt_strcpy(line_buf,s_MALEFAME_006260f0);
      }
      else {
        crt_strcpy(line_buf,s_FEMALEFAME_006260e4);
      }
      open_err = text_open_section((iptr)((u8 *)&g.d_006558e8),(iptr)line_buf);
      text_set_string_arg(0,entry * 0x48 + (iptr)((u8 *)&g.d_0063f0de + 2));
      for (line = 0; line <= *(short *)(&hof_entry_title_index + entry * 0x48);
          line = line + 1) {
        if (open_err == 0) {
          text_read_line(1);
          crt_strcpy(line_buf,&text_buffer);
        }
        else if (*(short *)(&hof_entry_title_index + entry * 0x48) == line) {
          crt_strcpy(line_buf,s__STRING0_006260fc);
        }
        else {
          crt_strcpy(line_buf,s_Error_00626108);
        }
        text_expand_vars((iptr)line_buf,(iptr)title_buf);
      }
      text_clear();
      text_append_int(entry + 1);
      text_append((iptr)((u8 *)&g.d_00626110));
      text_append((iptr)title_buf);
      text_append_space();
      text_append_label(0x8c);
      text_append_space();
      text_append(entry * 0x48 + (iptr)((u8 *)&g.d_0063f0de + 26));
      text_append_space();
      text_append_lparen();
      text_append_label(0x1bb);
      text_append_space();
      if ((*(short *)(&hof_entry_is_scenario + entry * 0x48) == 0) ||
         (-1 < *(short *)(&hof_entry_year_increment + entry * 0x48))) {
        year2 = (uint)*(short *)(&hof_entry_year + entry * 0x48);
        if ((int)year2 < 0) {
          if ((int)year2 < 1) {
            year2 = ~year2 + 1;
          }
          text_append_int(year2);
          text_append_space();
          text_append_label(0);
        }
        else if (game_language == 0) {
          text_append_label(1);
          text_append_space();
          abs_year2 = year2;
          if ((int)year2 < 1) {
            abs_year2 = ~year2 + 1;
          }
          text_append_int(abs_year2);
        }
        else {
          abs_year = year2;
          if ((int)year2 < 1) {
            abs_year = ~year2 + 1;
          }
          text_append_int(abs_year);
          text_append_space();
          text_append_label(1);
        }
      }
      else {
        if (*(short *)(&hof_entry_year_increment + entry * 0x48) < 1) {
          year_step = ~(int)*(short *)(&hof_entry_year_increment + entry * 0x48) + 1;
        }
        else {
          year_step = (int)*(short *)(&hof_entry_year_increment + entry * 0x48);
        }
        month_index = *(short *)(&hof_entry_turn + entry * 0x48) * year_step +
                    (int)*(short *)(&hof_entry_start_year + entry * 0x48) - 1;
        if (month_index % 0xc < 1) {
          month = ~(month_index % 0xc) + 1;
        }
        else {
          month = month_index % 0xc;
        }
        text_append_label(month + 0x1a4);
        text_append_space();
        if (month_index / 0xc < 1) {
          month_index = ~(month_index / 0xc) + 1;
        }
        else {
          month_index = month_index / 0xc;
        }
        text_append_int(month_index);
      }
      text_append_rparen();
      if (highlight == entry) {
        text_set_colors(0x7a,0x12,0xffffffff,0xffffffff);
      }
      else {
        text_set_colors(0xaf,0x12,0xffffffff,0xffffffff);
      }
      gfx_draw_text_centered((iptr)((u8 *)&g.d_00679640),advisor_client_x,entry_y,advisor_client_width);
      entry_y += line_height;
      text_clear();
      if ((*(short *)(&hof_entry_is_scenario + entry * 0x48) == 0) ||
         (*(short *)(&hof_entry_objective_score + entry * 0x48) < 0)) {
        text_append_label(0x22);
        text_append_colon();
        str_append_population((iptr)((u8 *)&g.d_00679640),0,(int)*(short *)(&hof_entry_population + entry * 0x48));
      }
      else {
        text_append_label(0x1b2);
        text_append_colon();
        text_append_int((int)*(short *)(&hof_entry_objective_score + entry * 0x48));
      }
      text_append_space();
      text_append_space();
      text_append_label(0x1bc);
      text_append_colon();
      text_append_int((int)*(short *)(&hall_of_fame_entries + entry * 0x48));
      text_append_space();
      text_append_lparen();
      text_append_string_id(difficulty_names[(int)*(short *)(&hof_entry_difficulty + entry * 0x48) & 0xf]);
      if (*(short *)(&hof_entry_is_scenario + entry * 0x48) != 0) {
        text_append_colon();
        text_append_label(0x1a2);
      }
      if ((*(ushort *)(&hof_entry_difficulty + entry * 0x48) & 0x80) != 0) {
        text_append_colon();
        text_append_label(0x19a);
      }
      text_append_rparen();
      gfx_draw_text_centered((iptr)((u8 *)&g.d_00679640),advisor_client_x,entry_y,advisor_client_width);
      entry_y += line_height;
      text_clear();
      text_append((iptr)((u8 *)&g.d_00626114));
      text_append_label(0x1bd);
      text_append_colon();
      text_append_int((int)*(short *)(&hall_of_fame_entry_rating + entry * 0x48));
      text_append((iptr)((u8 *)&g.d_00626118));
      text_set_colors(0x25,0x12,0xffffffff,0xffffffff);
      gfx_draw_text_centered((iptr)((u8 *)&g.d_00679640),advisor_client_x,entry_y,advisor_client_width);
      entry_y = entry_y + line_height + 6;
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
#undef year2
#undef abs_year
#undef abs_year2
#undef month_index
#undef month
#undef year_step
#undef entry_y
#undef entry
#undef line
#undef line_buf
#undef line_height
#undef open_err
#undef title_buf

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
#define button_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
/* WARNING: Removing unreachable block (ram,0x00436c7e) */
/* WARNING: Removing unreachable block (ram,0x00436d09) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

iptr __cdecl hall_of_fame_show(int highlight)

{
  int client_y;
  int rect_h;
  iptr label;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  hall_of_fame_load();
  picwnd_open((PictureWindow *)&advisor_window,8,8,1,600,400,0,0);
  advisor_report_param = highlight;
  advisor_report_civ = 0;
  if (highlight < 0) {
    advisor_add_close_button((ViewWindow *)&advisor_window);
  }
  else {
    rect_set_xywh((iptr)button_rect,2,0,0x129,0x18);
    client_y = advisor_client_y;
    rect_h = rect_height((iptr)button_rect);
    rect_offset((iptr)button_rect,advisor_client_x,(client_y - rect_h) + 0x18e);
    rect_offset((iptr)button_rect,299,0);
    label = label_string(*(i32 *)(label_string_ids + 0x51c));
    button_create
              ((Control *)&advisor_close_button,(iptr)((u8 *)&g.d_0063eb58),100,(iptr)button_rect,label);
    button_set_callback((Control *)&advisor_close_button,(iptr)advisor_on_close_clicked);
    ctrl_set_default_button((Control *)&advisor_close_button);
    ctrl_set_cancel_button((Control *)&advisor_close_button);
    rect_offset((iptr)button_rect,0xfffffed5,0);
    label = label_string(*(i32 *)(label_string_ids + 0x6f8));
    button_create
              ((Control *)&advisor_toggle_button,(iptr)((u8 *)&g.d_0063eb58),0x65,(iptr)button_rect,label);
    button_set_callback((Control *)&advisor_toggle_button,(iptr)hall_of_fame_on_clear_clicked);
  }
  wnd_set_redraw_callback((SurfaceWindow *)&advisor_window,(iptr)hall_of_fame_draw);
  wnd_repaint((SurfaceWindow *)&advisor_window);
  window_show((WindowObjectView *)&advisor_window);
  if (2 < game.multiplayer) {
    wnd_set_modal_idle_callback((ModalMenuWindow *)&advisor_wnd,(iptr)advisor_mp_idle);
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
#undef button_rect

/* 00436dd7 auto */
#define i (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl hall_of_fame_clear(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (i = 0; i < 6; i++) {
    *(i16 *)(&hall_of_fame_entries + i * 0x48) = 0xffff;
    *(i16 *)(&hall_of_fame_entry_rating + i * 0x48) = 0xffff;
  }
  return;
}
#undef i

/* 00436e28 auto */
#define i (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl hall_of_fame_load(void)

{
  bool read_failed;
  FILE *_File;
  size_t read_count;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  hall_of_fame_clear();
  _File = _fopen(s_HALLFAME_DAT_00626124,&hall_of_fame_read_mode);
  if (_File != (FILE *)0x0) {
    read_failed = false;
    for (i = 0; i < 6; i++) {
      read_count = _fread(&hall_of_fame_entries + i * 0x48,0x48,1,_File);
      if (read_count == 0) {
        read_failed = true;
        break;
      }
    }
    if (read_failed) {
      hall_of_fame_clear();
    }
    _fclose(_File);
  }
  return;
}
#undef i

/* 00436ed2 auto */
#define i (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl hall_of_fame_save(void)

{
  FILE *_File;
  size_t written;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  _File = _fopen(s_HALLFAME_DAT_00626138,&hall_of_fame_write_mode);
  if (_File != (FILE *)0x0) {
    i = 0;
    while ((i < 6 &&
           (written = _fwrite(&hall_of_fame_entries + i * 0x48,0x48,1,_File), written != 0))) {
      i++;
    }
    _fclose(_File);
  }
  return;
}
#undef i

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
#define slot (*(int *)(frame_ + FRAME_OFF(0)))
#define new_rank (*(int *)(frame_ + FRAME_OFF(4)))
#define insert_pos (*(int *)(frame_ + FRAME_OFF(8)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl hall_of_fame_add_entry(iptr civ)

{
  i32 value;
  int score;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  new_rank = -1;
  score = score_total;
  if (score_total <= score_conquest_bonus) {
    score = score_conquest_bonus;
  }
  hall_of_fame_new_entry_i16 = (i16)score;
  hof_new_difficulty = (ushort)game.difficulty;
  if ((game.game_flags & 0x10) != 0) {
    hof_new_difficulty = hof_new_difficulty | 0x80;
  }
  hof_new_turn_i16 = game.turn;
  hof_new_year_i16 = game.year;
  value = civ_total_population(civ);
  hof_new_population_i16 = (i16)value;
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
  value = civ_leader_name(civ);
  crt_strcpy(&hof_new_leader_name,value);
  value = civ_name_plural(civ);
  crt_strcpy(&hof_new_civ_name,value);
  hall_of_fame_load();
  hof_last_entry_score_i16 = 0xffff;
  hof_last_entry_rating_i16 = 0xffff;
  do {
    insert_pos = 0;
    while( true ) {
      if (5 < insert_pos) goto LAB_00437186;
      if (*(short *)(&hall_of_fame_entry_rating + insert_pos * 0x48) < hof_new_rating) break;
      insert_pos++;
    }
    for (slot = 5; insert_pos < slot; slot--) {
      crt_memcpy(&hall_of_fame_entries + slot * 0x48,&hall_of_fame_entries + (slot * 8 - 8) * 9,0x48);
    }
    crt_memcpy(&hall_of_fame_entries + insert_pos * 0x48,&hall_of_fame_new_entry,0x48);
    new_rank = insert_pos;
LAB_00437186:
    hall_of_fame_save();
    score = hall_of_fame_show(new_rank);
    if (score == 0) {
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
#undef slot
#undef new_rank
#undef insert_pos

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
void __cdecl credits_text_init(uint capacity)

{
  memblock_init((iptr)((u8 *)&g.d_0063f038),2,capacity);
  credits_line_count = 0;
  return;
}
#undef credits_line_count

/* 0043720f auto */
void __cdecl credits_text_free(void)

{
  memblock_free((iptr)((u8 *)&g.d_0063f038));
  return;
}

/* 0043722c auto */
#define credits_line_count (*(int *)((u8 *)&g.d_00625ec8))
int __cdecl credits_add_line(char *line)

{
  int line_index;
  size_t len;
  i32 dest;
  
  len = _strlen(line);
  dest = memblock_alloc((iptr)((u8 *)&g.d_0063f038),len + 1);
  crt_strcpy(dest,line);
  line_index = credits_line_count;
  credits_line_count++;
  return line_index;
}
#undef credits_line_count

/* 00437284 auto */
#define cursor (*(char * *)(frame_ + FRAME_OFF(0)))
char * __cdecl credits_get_line(int line_index)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  cursor = credits_text_data;
  for (; line_index != 0; line_index--) {
    for (; *cursor != '\0'; cursor++) {
    }
    cursor++;
  }
  return cursor;
}
#undef cursor

/* 004372cd auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define result (*(i32 *)(frame_ + FRAME_OFF(0)))
i32 __cdecl credits_load_section(i32 section)

{
  int status;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  result = 1;
  switch(section) {
  case 0:
    status = text_open_section((iptr)((u8 *)&g.d_00626150),(iptr)((u8 *)&g.d_00626148));
    break;
  case 1:
    status = text_open_section((iptr)((u8 *)&g.d_00626160),(iptr)((u8 *)&g.d_00626158));
    break;
  case 2:
    status = text_open_section((iptr)((u8 *)&g.d_00626174),(iptr)((u8 *)&g.d_0062616c));
    goto joined_r0x00437377;
  case 3:
    status = text_open_section((iptr)((u8 *)&g.d_00626188),(iptr)((u8 *)&g.d_00626180));
joined_r0x00437377:
    if (status != 0) {
      return 1;
    }
    goto LAB_004373c4;
  default:
    goto switchD_004373ad_default;
  }
  if (status == 0) {
LAB_004373c4:
    while ((status = text_read_line(1), status != 0 && (text_buffer != '@'))) {
      credits_add_line(&text_buffer);
    }
    result = 0;
  }
switchD_004373ad_default:
  return result;
}
#undef text_buffer
#undef result

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
#define clip_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define dead_surface (*(DibSurface * *)(frame_ + FRAME_OFF(20)))
#define dead_surface2 (*(DibSurface * *)(frame_ + FRAME_OFF(24)))
#define new_sprite (*(i32 *)(frame_ + FRAME_OFF(28)))
#define sprite_mem (*(Sprite * *)(frame_ + FRAME_OFF(32)))
#define new_surface (*(DibSurface * *)(frame_ + FRAME_OFF(36)))
#define surface_mem (*(DibSurface * *)(frame_ + FRAME_OFF(40)))
#define old_sprite (*(Sprite * *)(frame_ + FRAME_OFF(44)))
#define old_sprite2 (*(Sprite * *)(frame_ + FRAME_OFF(48)))
#define saved_scroll (*(int *)(frame_ + FRAME_OFF(52)))
#define y2 (*(int *)(frame_ + FRAME_OFF(56)))
#define bottom (*(int *)(frame_ + FRAME_OFF(60)))
#define left_x (*(int *)(frame_ + FRAME_OFF(64)))
#define top (*(int *)(frame_ + FRAME_OFF(68)))
#define line (*(int *)(frame_ + FRAME_OFF(72)))
#define text_width (*(int *)(frame_ + FRAME_OFF(76)))
#define center_x (*(int *)(frame_ + FRAME_OFF(80)))
#define drawn_right (*(int *)(frame_ + FRAME_OFF(84)))
#define drawn_left (*(int *)(frame_ + FRAME_OFF(88)))
#define max_width2 (*(int *)(frame_ + FRAME_OFF(92)))
#define line_text (*(char * *)(frame_ + FRAME_OFF(96)))
#define free_slot (*(int *)(frame_ + FRAME_OFF(100)))
#define line_surface (*(DibSurface * *)(frame_ + FRAME_OFF(104)))
#define slot (*(int *)(frame_ + FRAME_OFF(108)))
#define line_height (*(int *)(frame_ + FRAME_OFF(112)))
#define rect_left2 (*(int *)(frame_ + FRAME_OFF(116)))
#define rect_top2 (*(int *)(frame_ + FRAME_OFF(120)))
#define rect_right2 (*(i32 *)(frame_ + FRAME_OFF(124)))
#define rect_bottom2 (*(i32 *)(frame_ + FRAME_OFF(128)))
#define found_slot (*(int *)(frame_ + FRAME_OFF(132)))
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(136)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(140)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(144)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl credits_draw_scroll(int full_redraw)

{
  i32 rect_h;
  i32 rect_w;
  i8 frame_[FRAME_OFF(152)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  if (credits_partial_redraw_ok == 0) {
    full_redraw = 1;
  }
  if (full_redraw == 0) {
    rect_h = rect_height((iptr)((u8 *)&g.d_0063eaa8));
    rect_w = rect_width((iptr)((u8 *)&g.d_0063eaa8));
    picwnd_blit_at
              ((FrameWindow *)&advisor_window,credits_drawn_rect - advisor_client_x,
               credits_drawn_rect_top - advisor_client_y,rect_w,rect_h);
  }
  else {
    frame_wnd_layout((FrameWindow *)&advisor_window);
    picwnd_blit((PictureWindow *)&advisor_window);
  }
  top = advisor_client_y;
  bottom = advisor_client_y + 0x176;
  line_height = font_line_spacing((GameFont *)&credits_font);
  text_set_surface((iptr)((u8 *)&g.d_0063eb10));
  text_set_font((iptr)((u8 *)&g.d_0063ea20));
  text_set_colors(0x25,0x12,2,1);
  advisor_row_height = line_height;
  advisor_list_top_i32 = top;
  advisor_list_height_i32 = bottom - top;
  left_x = advisor_client_x + 2;
  y2 = top;
  saved_scroll = credits_scroll_pos;
  line = credits_scroll_pos / (line_height / 2);
  if (line < credits_line_count) {
    y2 = top + (credits_scroll_pos % (line_height / 2)) * -2;
    for (slot = 0; slot < 0x1e; slot++) {
      if ((-1 < *(int *)(&credits_slot_lines + slot * 4)) &&
         (*(int *)(&credits_slot_lines + slot * 4) < line)) {
        old_sprite = *(Sprite **)(&credits_slot_sprites + slot * 4);
        old_sprite2 = old_sprite;
        if (old_sprite != (Sprite *)0x0) {
          sprite_scalar_dtor(old_sprite,1);
        }
        *(i32 *)(&credits_slot_sprites + slot * 4) = 0;
        *(i32 *)(&credits_slot_lines + slot * 4) = 0xffffffff;
      }
    }
    max_width2 = 2;
    for (; (y2 < bottom && (line < credits_line_count)); line++) {
      line_text = (char *)credits_get_line(line);
      found_slot = -1;
      free_slot = -1;
      for (slot = 0; slot < 0x1e; slot++) {
        if (*(int *)(&credits_slot_lines + slot * 4) == line) {
          found_slot = slot;
          break;
        }
        if ((*(int *)(&credits_slot_lines + slot * 4) < 0) && (free_slot < 0)) {
          free_slot = slot;
        }
      }
      if (found_slot < 0) {
        if (free_slot < 0) goto LAB_00437a02;
        if (*line_text == '^') {
          line_text++;
          text_clear();
          text_append((iptr)line_text);
          line_text = &text_buffer;
          text_set_colors(0xba,0x12,0xffffffff,0xffffffff);
        }
        else {
          text_set_colors(0xbe,0x12,0xffffffff,0xffffffff);
        }
        text_width = font_text_width((GameFont *)&credits_font,(iptr)line_text);
        surface_mem = operator_new(0x48);
        seh_state = 0;
        if (surface_mem == (DibSurface *)0x0) {
          new_surface = (DibSurface *)0x0;
        }
        else {
          new_surface = (DibSurface *)surface_ctor(surface_mem);
        }
        seh_state = 0xffffffff;
        line_surface = new_surface;
        if (text_width != 0) {
          surface_create(new_surface,text_width,line_height);
          surface_set_palette(line_surface,(iptr)((u8 *)&g.d_006a8c00));
          text_set_surface((iptr)line_surface);
          surface_fill(line_surface,0xfa);
          gfx_draw_text((iptr)line_text,0,0);
        }
        sprite_mem = operator_new(0x3c);
        seh_state = 1;
        if (sprite_mem == (Sprite *)0x0) {
          new_sprite = 0;
        }
        else {
          new_sprite = sprite_init(sprite_mem);
        }
        seh_state = 0xffffffff;
        *(i32 *)(&credits_slot_sprites + free_slot * 4) = new_sprite;
        if (text_width != 0) {
          sprite_grab_from_surface
                    (*(Sprite **)(&credits_slot_sprites + free_slot * 4),(iptr)line_surface,0xfa,0,0,
                     text_width,line_height);
        }
        dead_surface = line_surface;
        dead_surface2 = line_surface;
        if (line_surface != (DibSurface *)0x0) {
          surface_delete(line_surface,1);
        }
        *(int *)(&credits_slot_lines + free_slot * 4) = line;
        *(int *)(&credits_slot_x + free_slot * 4) =
             ((advisor_client_width >> 1) + advisor_client_x) - (text_width >> 1);
        *(int *)(&credits_slot_widths + free_slot * 4) = text_width;
        found_slot = free_slot;
      }
      text_width = *(int *)(&credits_slot_widths + found_slot * 4);
      if (text_width != 0) {
        sprite_draw
                  (*(Sprite **)(&credits_slot_sprites + found_slot * 4),(iptr)clip_rect,(iptr)((u8 *)&g.d_0063eb10),
                   *(i32 *)(&credits_slot_x + found_slot * 4),y2);
      }
      if (max_width2 <= text_width) {
        max_width2 = text_width;
      }
      y2 += line_height;
    }
    max_width2 += 2;
    center_x = (advisor_client_width >> 1) + advisor_client_x;
    drawn_left = center_x - (max_width2 >> 1);
    drawn_right = max_width2 + drawn_left;
    rect_set((iptr)&rect_left2,drawn_left,top,drawn_right,bottom);
    credits_drawn_rect = rect_left2;
    credits_drawn_rect_top = rect_top2;
    credits_drawn_rect_right = rect_right2;
    credits_drawn_rect_bottom = rect_bottom2;
    if (advisor_client_width <= max_width2) {
      full_redraw = 1;
    }
    credits_partial_redraw_ok = (uint)(advisor_client_width > max_width2);
    if (full_redraw == 0) {
      wnd_blit_surface_rect((DibSurface *)&advisor_window,(iptr)&rect_left2);
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
#undef clip_rect
#undef dead_surface
#undef dead_surface2
#undef new_sprite
#undef sprite_mem
#undef new_surface
#undef surface_mem
#undef old_sprite
#undef old_sprite2
#undef saved_scroll
#undef y2
#undef bottom
#undef left_x
#undef top
#undef line
#undef text_width
#undef center_x
#undef drawn_right
#undef drawn_left
#undef max_width2
#undef line_text
#undef free_slot
#undef line_surface
#undef slot
#undef line_height
#undef rect_left2
#undef rect_top2
#undef rect_right2
#undef rect_bottom2
#undef found_slot
#undef seh_prev
#undef seh_handler
#undef seh_state

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
#define timer_id (*(int *)(frame_ + FRAME_OFF(4)))
#define slot (*(int *)(frame_ + FRAME_OFF(8)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl credits_show(int section)

{
  int load_failed;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  timer_id = -1;
  credits_text_init(0x1000);
  for (slot = 0; slot < 0x1e; slot++) {
    *(i32 *)(&credits_slot_sprites + slot * 4) = 0;
    *(i32 *)(&credits_slot_lines + slot * 4) = 0xffffffff;
  }
  load_failed = credits_load_section(section);
  if (load_failed == 0) {
    credits_scroll_pos = 0;
    credits_partial_redraw_ok = 0;
    advisor_report_civ = 0;
    if (section == 3) {
      picwnd_open((PictureWindow *)&advisor_window,10000,8,1,600,400,0,0);
    }
    else {
      picwnd_open((PictureWindow *)&advisor_window,0xffffffa1,8,1,600,400,0,0)
      ;
    }
    advisor_add_close_button((ViewWindow *)&advisor_window);
    wnd_set_redraw_callback((SurfaceWindow *)&advisor_window,(iptr)credits_on_redraw);
    music_play_track(3,0);
    wnd_repaint((SurfaceWindow *)&advisor_window);
    window_show((WindowObjectView *)&advisor_window);
    ui_flush_input();
    timer_id = game_timer_create((iptr)credits_on_timer,0x32,0xffffffff);
    if (2 < game.multiplayer) {
      wnd_set_modal_idle_callback((ModalMenuWindow *)&advisor_wnd,(iptr)advisor_mp_idle);
    }
    advisor_modal_start_ticks_i32 = timer_ticks();
    wnd_run_modal_loop((ModalMenuWindow *)&advisor_wnd);
    wnd_set_modal_idle_callback((ModalMenuWindow *)&advisor_wnd,0);
    picwnd_close((PictureWindowCore *)&advisor_window);
  }
  for (slot = 0; slot < 0x1e; slot++) {
    if (-1 < *(int *)(&credits_slot_lines + slot * 4)) {
      if (*(Sprite **)(&credits_slot_sprites + slot * 4) != (Sprite *)0x0) {
        sprite_scalar_dtor(*(Sprite **)(&credits_slot_sprites + slot * 4),1);
      }
      *(i32 *)(&credits_slot_sprites + slot * 4) = 0;
      *(i32 *)(&credits_slot_lines + slot * 4) = 0xffffffff;
    }
  }
  if (-1 < timer_id) {
    game_timer_destroy(timer_id);
  }
  credits_text_free();
  return;
}
#undef credits_partial_redraw_ok
#undef credits_scroll_pos
#undef advisor_modal_start_ticks_i32
#undef timer_id
#undef slot

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
  int now_ticks;
  
  net_process_messages((NetSession *)&net_session,1,0);
  now_ticks = timer_ticks();
  if (0x4b0 < now_ticks - advisor_modal_start_ticks_i32) {
    intel_report_end_modal();
    advisor_modal_start_ticks_i32 = timer_ticks();
  }
  return;
}
#undef advisor_modal_start_ticks_i32

/* 00437ccd auto */
#define casualty_scroll_pos (*(i32 *)((u8 *)&g.d_0063e958))
void __cdecl casualty_scrollbar_on_scroll(i32 scroll_pos)

{
  casualty_scroll_pos = scroll_pos;
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
#define row_y (*(int *)(frame_ + FRAME_OFF(0)))
#define log_index (*(int *)(frame_ + FRAME_OFF(24)))
#define entry (*(int *)(frame_ + FRAME_OFF(32)))
#define entry_count2 (*(int *)(frame_ + FRAME_OFF(44)))
#define scroll_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(56)))
#define rows_per_page (*(int *)(frame_ + FRAME_OFF(72)))
/* WARNING: Removing unreachable block (ram,0x004384ab) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl casualty_timeline_draw(void)

{
  int y;
  int bottom;
  int line_height;
  iptr unit;
  int row_x;
  int text_y;
  int name_x;
  int text_width;
  uptr len;
  uptr len2;
  size_t len3;
  i32 max_row;
  iptr civ;
  i8 frame_[FRAME_OFF(80)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ = casualty_window_civ;
  frame_wnd_layout((FrameWindow *)&casualty_window);
  frame_wnd_draw_caption((FrameWindow *)&casualty_window);
  picwnd_blit((PictureWindow *)&casualty_window);
  y = casualty_client_y + 2;
  bottom = casualty_client_y + 0x174;
  line_height = font_line_spacing((GameFont *)&advisor_font);
  text_set_surface((iptr)((u8 *)&g.d_0063e4f8));
  text_set_font((iptr)((u8 *)&g.d_0063eac0));
  text_set_colors(0x25,0x12,2,1);
  text_clear();
  unit = label_string(*(i32 *)(label_string_ids + 0x53c));
  text_append(unit);
  text_append_colon();
  unit = label_string(*(i32 *)(label_string_ids + 0xda0));
  text_append(unit);
  gfx_draw_text_centered((iptr)((u8 *)&g.d_00679640),casualty_client_x,y,casualty_client_width);
  y += line_height;
  text_clear();
  row_x = int_clamp(civs[civ].government - 1,0,4);
  text_append_label(row_x + 0x148);
  text_append_space();
  text_append_label(0x8c);
  text_append_space();
  unit = civ_name_plural(civ);
  text_append(unit);
  gfx_draw_text_centered((iptr)((u8 *)&g.d_00679640),casualty_client_x,y,casualty_client_width);
  y += line_height;
  text_clear();
  unit = civ_leader_title(civ);
  text_append(unit);
  text_append_space();
  unit = civ_leader_name(civ);
  text_append(unit);
  text_append_colon();
  text_append_year((int)game.year);
  gfx_draw_text_centered((iptr)((u8 *)&g.d_00679640),casualty_client_x,y,casualty_client_width);
  y += line_height;
  line_height = y + 2;
  casualty_row_height = 0x18;
  casualty_first_row_y = y + 0x1a;
  casualty_list_height_i32 = bottom - line_height;
  casualty_rows_per_page = int_clamp((bottom - line_height) / 0x18,1,99);
  entry_count2 = 0;
  if (*(int *)(&casualty_log_first + civ * 4) < *(int *)(&casualty_log_next + civ * 4)) {
    entry_count2 = *(int *)(&casualty_log_next + civ * 4) - *(int *)(&casualty_log_first + civ * 4);
  }
  else if (*(int *)(&casualty_log_first + civ * 4) < *(int *)(&casualty_log_next + civ * 4)) {
    entry_count2 = 300;
  }
  rows_per_page = casualty_rows_per_page;
  if (entry_count2 != 0) {
    casualty_page_count_i32 = int_clamp((casualty_rows_per_page - 1 + entry_count2) / casualty_rows_per_page,1,99);
    max_row = int_clamp(entry_count2 - 1,0,999);
    y = int_clamp(casualty_scroll_pos,0,max_row);
    entry = 1;
    log_index = (*(int *)(&casualty_log_next + civ * 4) - 1) - y;
    casualty_scroll_pos = y;
    row_y = line_height;
    if (log_index < 0) {
      log_index += 300;
    }
    while (((entry <= *(int *)(&casualty_counts + civ * 4) && (entry - 1 < y + rows_per_page))
           && ((*(int *)(&casualty_log_first + civ * 4) != 0 ||
               (log_index < *(int *)(&casualty_log_next + civ * 4)))))) {
      row_x = (entry + 1U & 1) * 0x40 + casualty_client_x;
      unit = unit_make_dummy((int)*(short *)(&casualty_log_unit_types + civ * 0x27d8 + log_index * 0x22),
                                 civ);
      gfx_draw_unit((iptr)((u8 *)&g.d_0063e4f8),unit,0,row_x + 2,row_y,0,0);
      text_set_font((iptr)((u8 *)&g.d_0063eab8));
      text_set_colors(0x25,0x12,1,1);
      row_x = casualty_client_x;
      text_y = row_y + 0x11;
      name_x = casualty_client_x + 0x8c;
      text_clear();
      unit = label_string(unit_types
                                 [*(short *)(&casualty_log_unit_types + civ * 0x27d8 + log_index * 0x22)].name
                                );
      text_append(unit);
      while (text_width = font_text_width((GameFont *)&advisor_bold_font,(iptr)((u8 *)&g.d_00679640)),
            0x60 < text_width) {
        len = _strlen(&text_buffer);
        (&text_buffer_minus1)[len] = 0;
      }
      gfx_draw_text((iptr)((u8 *)&g.d_00679640),name_x,text_y);
      text_clear();
      text_append_year((int)*(short *)(&casualty_log_years + civ * 0x27d8 + log_index * 0x22));
      while (name_x = font_text_width((GameFont *)&advisor_bold_font,(iptr)((u8 *)&g.d_00679640)),
            0x4c < name_x) {
        len2 = _strlen(&text_buffer);
        (&text_buffer_minus1)[len2] = 0;
      }
      gfx_draw_text((iptr)((u8 *)&g.d_00679640),row_x + 0xec,text_y);
      text_set_colors(0x5e,10,0xffffffff,0xffffffff);
      text_clear();
      text_append_int((int)*(short *)(&casualty_log_x + civ * 0x27d8 + log_index * 0x22));
      text_append((iptr)((u8 *)&g.d_00626194));
      text_append_int((int)*(short *)(&casualty_log_y + civ * 0x27d8 + log_index * 0x22));
      name_x = city_find_nearest((int)*(short *)(&casualty_log_x + civ * 0x27d8 + log_index * 0x22),
                                 (int)*(short *)(&casualty_log_y + civ * 0x27d8 + log_index * 0x22),
                                 -1,0xffffffff,-1);
      if (-1 < name_x) {
        text_append((iptr)((u8 *)&g.d_00626198));
        text_append(name_x * 0x58 + (iptr)((u8 *)&cities + 32));
        text_append((iptr)((u8 *)&g.d_006261a0));
      }
      while (name_x = font_text_width((GameFont *)&advisor_bold_font,(iptr)((u8 *)&g.d_00679640)),
            0xaa < name_x) {
        len3 = _strlen(&text_buffer);
        (&text_buffer_minus1)[len3] = 0;
      }
      gfx_draw_text((iptr)((u8 *)&g.d_00679640),row_x + 0x138,text_y);
      text_set_colors((int)*(short *)(&casualty_log_killer_colors + civ * 0x27d8 + log_index * 0x22),0x12,
                         0xffffffff,0xffffffff);
      text_clear();
      text_append(log_index * 0x22 + civ * 0x27d8 + (iptr)((u8 *)&g.d_006af2a8 + 2));
      while (text_width = casualty_client_right - casualty_vscroll_width_i32,
            name_x = font_text_width((GameFont *)&advisor_bold_font,(iptr)((u8 *)&g.d_00679640)),
            (text_width - 2) - (row_x + 0x1e2) < name_x) {
        len3 = _strlen(&text_buffer);
        (&text_buffer_minus1)[len3] = 0;
      }
      gfx_draw_text((iptr)((u8 *)&g.d_00679640),row_x + 0x1e2,text_y);
      entry++;
      log_index--;
      if (log_index < 0) {
        log_index = 299;
      }
      row_y += 0x18;
    }
  }
  if (casualty_controls_created == 0) {
    rect_set((iptr)scroll_rect,(casualty_client_right - casualty_vscroll_width_i32) - 2,line_height,casualty_client_right - 2,
                       bottom);
    scrollbar_create((Control *)&casualty_scrollbar,(iptr)((u8 *)&g.d_0063e540),200,(iptr)scroll_rect,1);
    scrollbar_set_callback((Control *)&casualty_scrollbar,(iptr)casualty_scrollbar_on_scroll);
    wnd_set_dblclick_handler((WndHandlersMouseSetView *)&casualty_wnd_events,(iptr)casualty_timeline_on_dblclick);
  }
  max_row = int_clamp(entry_count2 - 1,0,999);
  scrollbar_set_range((Control *)&casualty_scrollbar,0,max_row);
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
#undef row_y
#undef log_index
#undef entry
#undef entry_count2
#undef scroll_rect
#undef rows_per_page

/* 0043856b auto */
#define casualty_client_x (*(i32 *)((u8 *)&g.d_0063e61c))
#define casualty_report_param_i32 (*(i32 *)((u8 *)&g.d_0063e994))
#define button_rect (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
/* WARNING: Removing unreachable block (ram,0x00438634) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl casualty_timeline_show(iptr civ)

{
  int client_y;
  int rect_h;
  iptr label;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (casualty_window_report_id < 0) {
    picwnd_open((PictureWindow *)&casualty_window,2,0xc,0,600,400,0,0);
    casualty_window_civ = civ;
    casualty_report_param_i32 = 0;
    rect_set_xywh((iptr)button_rect,2,0,0x254,0x18);
    client_y = casualty_client_y;
    rect_h = rect_height((iptr)button_rect);
    rect_offset((iptr)button_rect,casualty_client_x,(client_y - rect_h) + 0x18e);
    label = label_string(*(i32 *)(label_string_ids + 0x51c));
    button_create
              ((Control *)&casualty_close_button,(iptr)((u8 *)&g.d_0063e540),100,(iptr)button_rect,label);
    button_set_callback((Control *)&casualty_close_button,(iptr)advisor_on_close_clicked);
    ctrl_set_default_button((Control *)&casualty_close_button);
    ctrl_set_cancel_button((Control *)&casualty_close_button);
    wnd_set_redraw_callback((SurfaceWindow *)&casualty_window,(iptr)casualty_timeline_draw);
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
#undef button_rect

/* 004386b8 auto */
#define casualty_row_height (*(int *)((u8 *)&g.d_0063e968))
#define casualty_scroll_pos (*(int *)((u8 *)&g.d_0063e958))
#define log_index (*(int *)(frame_ + FRAME_OFF(4)))
void __cdecl casualty_timeline_on_dblclick(i32 click_x,int click_y)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  click_y -= (casualty_first_row_y - casualty_row_height / 2);
  if ((-1 < click_y) && (click_y = click_y / casualty_row_height, click_y < casualty_rows_per_page)) {
    log_index = ((*(int *)(&casualty_log_next + casualty_window_civ * 4) - 1) - casualty_scroll_pos) - click_y;
    if (log_index < 0) {
      log_index += 300;
    }
    if ((*(int *)(&casualty_log_next + casualty_window_civ * 4) != log_index) &&
       (((*(int *)(&casualty_log_first + casualty_window_civ * 4) != 0 ||
         (0x12a < *(int *)(&casualty_counts + casualty_window_civ * 4))) ||
        (log_index < *(int *)(&casualty_log_next + casualty_window_civ * 4))))) {
      mapview_center_on
                ((ViewWindow *)&map_views,
                 (int)*(short *)(&casualty_log_x + casualty_window_civ * 0x27d8 + log_index * 0x22),
                 (int)*(short *)(&casualty_log_y + casualty_window_civ * 0x27d8 + log_index * 0x22));
    }
  }
  return;
}
#undef casualty_row_height
#undef casualty_scroll_pos
#undef log_index

/* 0044ce16 auto */
#define i (*(iptr *)(frame_ + FRAME_OFF(4)))
#define seh_next (*(i32 *)(frame_ + FRAME_OFF(8)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(12)))
#define try_level (*(i32 *)(frame_ + FRAME_OFF(16)))
ThroneRoomWindow * __thiscall throneroom_ctor(ThroneRoomWindow *this,iptr civ)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  try_level = 0xffffffff;
  wnd_ctor((ModalMenuWindow *)this);
  try_level = 0;
  palette_init((GamePalette *)&this->control_list);
  (*(i8 *)((char *)&try_level + 0)) = 1;
  dll_handle_init((DllHandle *)this->throne_dll);
  (*(i8 *)((char *)&try_level + 0)) = 2;
  surfwnd_ctor((SurfaceWindow *)this->throne_surface_wnd);
  (*(i8 *)((char *)&try_level + 0)) = 3;
  surface_ctor((DibSurface *)(this->throne_backbuffer));
  (*(i8 *)((char *)&try_level + 0)) = 4;
  clickmap_ctor(this->choice_clickmap);
  (*(i8 *)((char *)&try_level + 0)) = 5;
  dialog_ctor((Dialog *)this->choice_dialog_2,0x4000);
  (*(i8 *)((char *)&try_level + 0)) = 6;
  font_init_empty((GameFont *)((u8 *)&this->click_prompt_font));
  try_level = CONCAT31((*(i32 *)((char *)&try_level + 1)),7);
  gfx_get_screen_rect((iptr)(this->media_wnd));
  this->throne_civ = civ;
  throneroom_wnd = (iptr)this;
  this->throne_complete = 1;
  for (i = 0; i < 8; i++) {
    if (civs[(this->throne_civ)].throne_room[i] < 4) {
      this->throne_complete = 0;
    }
  }
  SetRect((LPRECT)((u8 *)&this->click_prompt_rect),0,0x1c2,0x280,0x1e0);
  font_set_styled((GameFont *)((u8 *)&this->click_prompt_font),0,0x12,3);
  return this;
}
#undef i
#undef seh_next
#undef seh_handler
#undef try_level

/* 0044d027 auto */
#define seh_next (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define try_level (*(int *)(frame_ + FRAME_OFF(8)))
void __thiscall throneroom_dtor(ThroneRoomDtorView *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  (*(i32 *)((char *)&try_level + 1)) = 0;
  (*(i8 *)((char *)&try_level + 0)) = 7;
  throneroom_wnd = 0;
  dll_handle_free((DllHandle *)(this->graphics_dll));
  (*(i8 *)((char *)&try_level + 0)) = 6;
  /* inlined unwind funclet 0044d0d8 */ { font_destroy((GameFont *)(*(int *)((iptr)&this) + 0x1c34)); }
  (*(i8 *)((char *)&try_level + 0)) = 5;
  /* inlined unwind funclet 0044d0e7 */ { dialog_dtor((Dialog *)(*(int *)((iptr)&this) + 0x1930)); }
  (*(i8 *)((char *)&try_level + 0)) = 4;
  /* inlined unwind funclet 0044d0f6 */ { clickmap_dtor(*(int *)((iptr)&this) + 0x660); }
  (*(i8 *)((char *)&try_level + 0)) = 3;
  /* inlined unwind funclet 0044d105 */ { surface_dtor((DibSurface *)(*(int *)((iptr)&this) + 0x618)); }
  (*(i8 *)((char *)&try_level + 0)) = 2;
  /* inlined unwind funclet 0044d114 */ { surfwnd_dtor((SurfaceWindow *)(*(int *)((iptr)&this) + 0x504)); }
  (*(i8 *)((char *)&try_level + 0)) = 1;
  /* inlined unwind funclet 0044d123 */ { dll_free((DllHandle *)(*(int *)((iptr)&this) + 0x4fc)); }
  try_level = (uint)(*(i32 *)((char *)&try_level + 1)) << 8;
  /* inlined unwind funclet 0044d132 */ { palette_destroy((GamePalette *)(*(int *)((iptr)&this) + 0xb8)); }
  try_level = 0xffffffff;
  /* inlined unwind funclet 0044d141 */ { wnd_dtor(*(WndBase **)((iptr)&this)); }
  return;
}
#undef seh_next
#undef seh_handler
#undef try_level

/* 0044d162 auto */
#define path (*(i8 (*)[128])(frame_ + FRAME_OFF(4)))
uint __thiscall throneroom_create_windows(PictureFrameWindow *this)

{
  int found;
  i8 frame_[FRAME_OFF(136)] __attribute__((aligned(8)));  /* original stack frame */
  
  str_clear((iptr)path);
  str_append((iptr)path,(iptr)((u8 *)&g.d_00626814));
  found = file_resolve_path((iptr)path);
  if (found != 0) {
    dll_handle_load((DllHandle *)this->throne_dll,(iptr)path);
    wnd_create_with_handlers
              ((WndBase *)this,(iptr)((u8 *)&g.d_0062681c),0x800,0,0,this->throne_width,this->throne_height + 5,(iptr)((u8 *)&g.d_006a8c00)
               ,(iptr)((u8 *)&g.d_006553d8));
    wnd_set_bg_color((WndBase *)this,0);
    wnd_create_with_surface
              ((DibSurface *)(u8 *)&this->throne_surface_wnd,(iptr)((u8 *)&g.d_00626820),0x800,0,0,0x280,0x1e0,(iptr)&this->control_list,
               (iptr)this);
    wnd_center((WndCenterView *)(this->throne_wnd_base));
    wnd_set_lbuttonup_handler((WndEventHandlers *)(this->throne_handlers),(iptr)throneroom_on_click);
    wnd_set_keydown_handler((WndEventHandlers *)(this->throne_handlers),(iptr)throneroom_on_key);
  }
  return (uint)(found != 0);
}
#undef path

/* 0044d296 auto */
#define text_line_cursor (*(iptr *)((u8 *)&g.d_00673f14))
#define font2 (*(GameFont *)(frame_ + FRAME_OFF(0)))
#define text_buf (*(i8 (*)[1024])(frame_ + FRAME_OFF(8)))
#define rect (*(tagRECT *)(frame_ + FRAME_OFF(1032)))
#define seh_next (*(i32 *)(frame_ + FRAME_OFF(1048)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(1052)))
#define try_level (*(i32 *)(frame_ + FRAME_OFF(1056)))
void __thiscall throneroom_run_upgrade(ThroneRoomWindow *this)

{
  int result;
  char *line;
  i8 frame_[FRAME_OFF(1064)] __attribute__((aligned(8)));  /* original stack frame */
  
  try_level = 0xffffffff;
  result = throneroom_create_windows((PictureFrameWindow *)this);
  if ((result != 0) && (result = throneroom_render(this), result != 0)) {
    surface_create((DibSurface *)(this->throne_backbuffer),0x280,0x1e0);
    SetRect(&rect,0,0,0x280,0x1e0);
    surface_blit
              ((DibSurface *)this->throne_surface_wnd,(iptr)(this->throne_backbuffer),(iptr)&rect,
               (iptr)&rect);
    font_init(&font2,1,0x18);
    try_level = 0;
    result = text_open_section((iptr)((u8 *)&g.d_006558e8),(iptr)((u8 *)&g.d_00626824));
    if (result == 0) {
      str_clear((iptr)text_buf);
      while (line = (char *)text_read_line(1), *line != '@') {
        str_append((iptr)text_buf,text_line_cursor);
        str_append((iptr)text_buf,(iptr)((u8 *)&g.d_0062682c));
      }
      SetRect(&rect,100,0x78,0x21c,0x1c2);
      gfx_set_text_color_index(0);
      surface_draw_text_rect
                ((DibSurface *)this->throne_surface_wnd,(iptr)&font2,(iptr)text_buf,(iptr)&rect,0);
      OffsetRect(&rect,2,2);
      gfx_set_text_color_index(0xff);
      surface_draw_text_rect
                ((DibSurface *)this->throne_surface_wnd,(iptr)&font2,(iptr)text_buf,(iptr)&rect,0);
      text_close_file();
      SetRect(&rect,0,0,0x280,0x1e0);
    }
    throneroom_draw_click_prompt((WndBase *)this);
    this->choosing_item = 0;
    wnd_handle_show_raise((WndBase *)this);
    wnd_flush_paint();
    wnd_set_palette((WndBase *)this,(iptr)&this->control_list);
    window_show((WindowObjectView *)this->throne_surface_wnd);
    wnd_flush_paint();
    input_flush_events();
    wnd_set_capture((WndBase *)(this->throne_wnd_base));
    if (2 < game.multiplayer) {
      wnd_set_modal_idle_callback((ModalMenuWindow *)(this->throne_wnd_base),(iptr)net_modal_idle_poll);
    }
    wnd_run_modal_loop((ModalMenuWindow *)(this->throne_wnd_base));
    wnd_set_modal_idle_callback((ModalMenuWindow *)(this->throne_wnd_base),0);
    wnd_release_capture((WndBase *)(this->throne_wnd_base));
    result = throneroom_render_choices(this);
    if (result == 0) {
      try_level = 0xffffffff;
      /* inlined unwind funclet 0044d99d */ { font_destroy((GameFont *)((iptr)&font2)); }
    }
    else {
      result = text_open_section((iptr)((u8 *)&g.d_006558e8),(iptr)((u8 *)&g.d_00626830));
      if (result == 0) {
        str_clear((iptr)text_buf);
        while (line = (char *)text_read_line(1), *line != '@') {
          str_append((iptr)text_buf,text_line_cursor);
          str_append((iptr)text_buf,(iptr)((u8 *)&g.d_0062683c));
        }
        SetRect(&rect,100,0x78,0x21c,0x1c2);
        gfx_set_text_color_index(0);
        surface_draw_text_rect
                  ((DibSurface *)this->throne_surface_wnd,(iptr)&font2,(iptr)text_buf,(iptr)&rect,0
                  );
        OffsetRect(&rect,2,2);
        gfx_set_text_color_index(0xff);
        surface_draw_text_rect
                  ((DibSurface *)this->throne_surface_wnd,(iptr)&font2,(iptr)text_buf,(iptr)&rect,0
                  );
        text_close_file();
        SetRect(&rect,0,0,0x280,0x1e0);
      }
      throneroom_draw_click_prompt((WndBase *)this);
      this->choosing_item = 1;
      SetRect(&rect,0,0,0x280,0x1e0);
      gfx_dissolve_blit((iptr)this->throne_surface_wnd,(iptr)&rect,8,4);
      wnd_blit_surface((DibSurface *)this->throne_surface_wnd);
      input_flush_events();
      wnd_set_capture((WndBase *)(this->throne_wnd_base));
      if (2 < game.multiplayer) {
        wnd_set_modal_idle_callback((ModalMenuWindow *)(this->throne_wnd_base),(iptr)net_modal_idle_poll);
      }
      wnd_run_modal_loop((ModalMenuWindow *)(this->throne_wnd_base));
      wnd_set_modal_idle_callback((ModalMenuWindow *)(this->throne_wnd_base),0);
      wnd_release_capture((WndBase *)(this->throne_wnd_base));
      snd_play_effect(0xd,1,0,0);
      SetRect(&rect,0,0,0x280,0x1e0);
      surface_blit
                ((DibSurface *)(this->throne_backbuffer),(iptr)this->throne_surface_wnd,(iptr)&rect,
                 (iptr)&rect);
      win_flush_pending_msgs();
      gfx_dissolve_blit((iptr)this->throne_surface_wnd,(iptr)&rect,8,3);
      wnd_blit_surface((DibSurface *)this->throne_surface_wnd);
      wnd_flush_paint();
      if (this->throne_complete == 0) {
        line = (char *)(this->chosen_item + (iptr)((u8 *)&civs + 1011) + this->throne_civ * 0x594);
        *line = *line + 1;
      }
      else {
        civs[this->throne_civ].throne_room[8] =
             civs[this->throne_civ].throne_room[8] | (byte)(1 << ((byte)this->chosen_item & 0x1f));
      }
      result = throneroom_render(this);
      if (result != 0) {
        snd_play_effect(0xd,1,0,0);
        SetRect(&rect,0,0,0x280,0x1e0);
        gfx_dissolve_blit((iptr)this->throne_surface_wnd,(iptr)&rect,4,1);
        throneroom_draw_click_prompt((WndBase *)this);
        wnd_blit_surface((DibSurface *)this->throne_surface_wnd);
        this->choosing_item = 0;
        wnd_set_capture((WndBase *)(this->throne_wnd_base));
        if (2 < game.multiplayer) {
          wnd_set_modal_idle_callback((ModalMenuWindow *)(this->throne_wnd_base),(iptr)net_modal_idle_poll);
        }
        wnd_run_modal_loop((ModalMenuWindow *)(this->throne_wnd_base));
        wnd_set_modal_idle_callback((ModalMenuWindow *)(this->throne_wnd_base),0);
        wnd_release_capture((WndBase *)(this->throne_wnd_base));
        wnd_hide((WndBase *)(this->throne_wnd_base));
        wnd_flush_paint();
      }
      wnd_set_palette((WndBase *)this,(iptr)((u8 *)&g.d_006a8c00));
      wnd_hide((WndBase *)this);
      wnd_flush_paint();
      try_level = 0xffffffff;
      /* inlined unwind funclet 0044d99d */ { font_destroy((GameFont *)((iptr)&font2)); }
    }
  }
  return;
}
#undef text_line_cursor
#undef font2
#undef text_buf
#undef rect
#undef seh_next
#undef seh_handler
#undef try_level

/* 0044d9c1 auto */
void __thiscall throneroom_run_view(ThroneRoomWindow *this)

{
  int ok;
  
  ok = throneroom_create_windows((PictureFrameWindow *)this);
  if ((ok != 0) && (ok = throneroom_render(this), ok != 0)) {
    throneroom_draw_click_prompt((WndBase *)this);
    this->choosing_item = 0;
    wnd_handle_show_raise((WndBase *)this);
    wnd_flush_paint();
    wnd_set_palette((WndBase *)this,(iptr)&this->control_list);
    window_show((WindowObjectView *)this->throne_surface_wnd);
    wnd_flush_paint();
    if (2 < game.multiplayer) {
      wnd_set_modal_idle_callback((ModalMenuWindow *)(this->throne_wnd_base),(iptr)net_modal_idle_poll);
    }
    wnd_run_modal_loop((ModalMenuWindow *)(this->throne_wnd_base));
    wnd_set_modal_idle_callback((ModalMenuWindow *)(this->throne_wnd_base),0);
    wnd_hide((WndBase *)(this->throne_wnd_base));
    wnd_flush_paint();
    wnd_set_palette((WndBase *)this,(iptr)((u8 *)&g.d_006a8c00));
    wnd_hide((WndBase *)this);
    wnd_flush_paint();
  }
  return;
}

/* 0044dab5 auto */
void __thiscall throneroom_draw_click_prompt(WndBase *this)

{
  iptr label;
  
  text_clear();
  text_append((iptr)((u8 *)&g.d_00626840));
  label = label_string(*(i32 *)(label_string_ids + 0x720));
  text_append(label);
  text_append((iptr)((u8 *)&g.d_00626844));
  gfx_set_text_color_index(0);
  surface_draw_text_in_rect
            ((DibSurface *)&((PictureFrameWindow *)this)->throne_surface_wnd,(iptr)&((ThroneRoomWindow *)this)->click_prompt_font,(iptr)((u8 *)&g.d_00679640),
             (iptr)&((ThroneRoomWindow *)this)->click_prompt_rect,0);
  OffsetRect((LPRECT)&((ThroneRoomWindow *)this)->click_prompt_rect,-1,-1);
  gfx_set_text_color_index(0xff);
  surface_draw_text_in_rect
            ((DibSurface *)&((PictureFrameWindow *)this)->throne_surface_wnd,(iptr)&((ThroneRoomWindow *)this)->click_prompt_font,(iptr)((u8 *)&g.d_00679640),
             (iptr)&((ThroneRoomWindow *)this)->click_prompt_rect,0);
  OffsetRect((LPRECT)&((ThroneRoomWindow *)this)->click_prompt_rect,1,1);
  return;
}

/* 0044db92 auto */
#define draw_tmp9 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define fail8 (*(i32 *)(frame_ + FRAME_OFF(16)))
#define draw_tmp8 (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
#define fail7 (*(i32 *)(frame_ + FRAME_OFF(36)))
#define draw_tmp7 (*(i8 (*)[16])(frame_ + FRAME_OFF(40)))
#define fail6 (*(i32 *)(frame_ + FRAME_OFF(56)))
#define draw_tmp6 (*(i8 (*)[16])(frame_ + FRAME_OFF(60)))
#define fail5 (*(i32 *)(frame_ + FRAME_OFF(76)))
#define draw_tmp5 (*(i8 (*)[16])(frame_ + FRAME_OFF(80)))
#define fail4 (*(i32 *)(frame_ + FRAME_OFF(96)))
#define draw_tmp4 (*(i8 (*)[16])(frame_ + FRAME_OFF(100)))
#define fail3 (*(i32 *)(frame_ + FRAME_OFF(116)))
#define draw_tmp3 (*(i8 (*)[16])(frame_ + FRAME_OFF(120)))
#define fail2 (*(i32 *)(frame_ + FRAME_OFF(136)))
#define draw_tmp2 (*(i8 (*)[16])(frame_ + FRAME_OFF(140)))
#define fail1 (*(i32 *)(frame_ + FRAME_OFF(156)))
#define draw_tmp1 (*(i8 (*)[16])(frame_ + FRAME_OFF(160)))
#define result (*(i32 *)(frame_ + FRAME_OFF(176)))
#define surface (*(DibSurface *)(frame_ + FRAME_OFF(180)))
#define slot (*(iptr *)(frame_ + FRAME_OFF(252)))
#define level (*(int *)(frame_ + FRAME_OFF(256)))
#define sprite (*(Sprite *)(frame_ + FRAME_OFF(260)))
#define seh_next (*(i32 *)(frame_ + FRAME_OFF(320)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(324)))
#define try_level (*(int *)(frame_ + FRAME_OFF(328)))
i32 __thiscall throneroom_render(ThroneRoomWindow *this)

{
  int loaded;
  i8 frame_[FRAME_OFF(336)] __attribute__((aligned(8)));  /* original stack frame */
  
  try_level = 0xffffffff;
  surface_ctor(&surface);
  try_level = 0;
  sprite_init(&sprite);
  (*(i8 *)((char *)&try_level + 0)) = 1;
  for (slot = 0; slot < 3; slot++) {
    win_flush_pending_msgs();
    if (*(char *)&civs[(this->throne_civ)].throne_room[slot] != '\0') {
      level = civs[(this->throne_civ)].throne_room[slot] - 1;
      loaded = surface_load_gif_resource
                        (&surface,slot * 5 + level + 0x69,10,0xec,(iptr)&this->control_list);
      if (loaded == 0) {
        result = 0;
        try_level = (uint)(*(i32 *)((char *)&try_level + 1)) << 8;
        /* inlined unwind funclet 0044e762 */ { sprite_destroy((Sprite *)((iptr)&sprite)); }
        try_level = 0xffffffff;
        /* inlined unwind funclet 0044e76b */ { surface_dtor((DibSurface *)((iptr)&surface)); }
        goto LAB_0044e781;
      }
      sprite_grab_from_surface
                (&sprite,(iptr)&surface,9,
                 *(i32 *)(&throneroom_piece_rect_x + level * 0x10 + slot * 0x40),
                 *(i32 *)(&throneroom_piece_rect_y + level * 0x10 + slot * 0x40),
                 *(i32 *)(&throneroom_piece_rect_w + level * 0x10 + slot * 0x40),
                 *(i32 *)(&throneroom_piece_rect_h + level * 0x10 + slot * 0x40));
      sprite_replace_color(&sprite,7,9);
      sprite_draw
                (&sprite,(iptr)draw_tmp1,(iptr)this->throne_surface_wnd,
                 *(int *)(&throneroom_piece_rect_x + level * 0x10 + slot * 0x40) - 1,
                 *(int *)(&throneroom_piece_rect_y + level * 0x10 + slot * 0x40) - 1);
    }
  }
  win_flush_pending_msgs();
  if ((this->throne_complete != 0) && ((civs[this->throne_civ].throne_room[8] & 1) != 0)) {
    loaded = surface_load_gif_resource(&surface,0xa0,10,0xec,(iptr)&this->control_list);
    if (loaded == 0) {
      fail1 = 0;
      try_level = (uint)(*(i32 *)((char *)&try_level + 1)) << 8;
      /* inlined unwind funclet 0044e762 */ { sprite_destroy((Sprite *)((iptr)&sprite)); }
      try_level = 0xffffffff;
      /* inlined unwind funclet 0044e76b */ { surface_dtor((DibSurface *)((iptr)&surface)); }
      result = fail1;
      goto LAB_0044e781;
    }
    sprite_grab_from_surface
              (&sprite,(iptr)&surface,9,throneroom_bonus_rect_x,throneroom_bonus_rect_y,throneroom_bonus_rect_w,throneroom_bonus_rect_h);
    sprite_replace_color(&sprite,7,9);
    sprite_draw
              (&sprite,(iptr)draw_tmp2,(iptr)this->throne_surface_wnd,throneroom_bonus_rect_x - 1,throneroom_bonus_rect_y - 1);
  }
  win_flush_pending_msgs();
  if (civs[this->throne_civ].throne_room[3] != '\0') {
    level = civs[this->throne_civ].throne_room[3] - 1;
    loaded = surface_load_gif_resource
                      (&surface,civs[this->throne_civ].throne_room[3] + 0x77,10,0xec,
                       (iptr)&this->control_list);
    if (loaded == 0) {
      fail2 = 0;
      try_level = (uint)(*(i32 *)((char *)&try_level + 1)) << 8;
      /* inlined unwind funclet 0044e762 */ { sprite_destroy((Sprite *)((iptr)&sprite)); }
      try_level = 0xffffffff;
      /* inlined unwind funclet 0044e76b */ { surface_dtor((DibSurface *)((iptr)&surface)); }
      result = fail2;
      goto LAB_0044e781;
    }
    sprite_grab_from_surface
              (&sprite,(iptr)&surface,9,
               *(i32 *)(&throneroom_piece_rect_x + level * 0x10 + slot * 0x40),
               *(i32 *)(&throneroom_piece_rect_y + level * 0x10 + slot * 0x40),
               *(i32 *)(&throneroom_piece_rect_w + level * 0x10 + slot * 0x40),
               *(i32 *)(&throneroom_piece_rect_h + level * 0x10 + slot * 0x40));
    sprite_replace_color(&sprite,7,9);
    sprite_draw
              (&sprite,(iptr)draw_tmp3,(iptr)this->throne_surface_wnd,
               *(int *)(&throneroom_piece3_rect_x + level * 0x10) - 1,
               *(int *)(&throneroom_piece3_rect_y + level * 0x10) - 1);
  }
  win_flush_pending_msgs();
  if (this->throne_complete != 0) {
    for (slot = 1; slot < 3; slot++) {
      if ((1 << ((byte)slot & 0x1f) & (uint)civs[this->throne_civ].throne_room[8]) != 0) {
        loaded = surface_load_gif_resource(&surface,slot + 0xa0,10,0xec,(iptr)&this->control_list)
        ;
        if (loaded == 0) {
          fail3 = 0;
          try_level = (uint)(*(i32 *)((char *)&try_level + 1)) << 8;
          /* inlined unwind funclet 0044e762 */ { sprite_destroy((Sprite *)((iptr)&sprite)); }
          try_level = 0xffffffff;
          /* inlined unwind funclet 0044e76b */ { surface_dtor((DibSurface *)((iptr)&surface)); }
          result = fail3;
          goto LAB_0044e781;
        }
        sprite_grab_from_surface
                  (&sprite,(iptr)&surface,9,(&throneroom_bonus_rect_x)[slot * 4],
                   (&throneroom_bonus_rect_y)[slot * 4],(&throneroom_bonus_rect_w)[slot * 4],
                   (&throneroom_bonus_rect_h)[slot * 4]);
        sprite_replace_color(&sprite,7,9);
        sprite_draw
                  (&sprite,(iptr)draw_tmp4,(iptr)this->throne_surface_wnd,(&throneroom_bonus_rect_x)[slot * 4] - 1,
                   (&throneroom_bonus_rect_y)[slot * 4] - 1);
      }
    }
  }
  win_flush_pending_msgs();
  if (civs[this->throne_civ].throne_room[4] != '\0') {
    level = civs[this->throne_civ].throne_room[4] - 1;
    loaded = surface_load_gif_resource
                      (&surface,civs[this->throne_civ].throne_room[4] + 0x7c,10,0xec,
                       (iptr)&this->control_list);
    if (loaded == 0) {
      fail4 = 0;
      try_level = (uint)(*(i32 *)((char *)&try_level + 1)) << 8;
      /* inlined unwind funclet 0044e762 */ { sprite_destroy((Sprite *)((iptr)&sprite)); }
      try_level = 0xffffffff;
      /* inlined unwind funclet 0044e76b */ { surface_dtor((DibSurface *)((iptr)&surface)); }
      result = fail4;
      goto LAB_0044e781;
    }
    sprite_grab_from_surface
              (&sprite,(iptr)&surface,9,*(i32 *)(&throneroom_piece4_rect_x + level * 0x10),
               *(i32 *)(&throneroom_piece4_rect_y + level * 0x10),
               *(i32 *)(&throneroom_piece4_rect_w + level * 0x10),
               *(i32 *)(&throneroom_piece4_rect_h + level * 0x10));
    sprite_replace_color(&sprite,7,9);
    sprite_draw
              (&sprite,(iptr)draw_tmp5,(iptr)this->throne_surface_wnd,
               *(int *)(&throneroom_piece4_rect_x + level * 0x10) - 1,
               *(int *)(&throneroom_piece4_rect_y + level * 0x10) - 1);
  }
  win_flush_pending_msgs();
  if ((this->throne_complete != 0) && ((civs[this->throne_civ].throne_room[8] & 8) != 0)) {
    loaded = surface_load_gif_resource(&surface,0xa3,10,0xec,(iptr)&this->control_list);
    if (loaded == 0) {
      fail5 = 0;
      try_level = (uint)(*(i32 *)((char *)&try_level + 1)) << 8;
      /* inlined unwind funclet 0044e762 */ { sprite_destroy((Sprite *)((iptr)&sprite)); }
      try_level = 0xffffffff;
      /* inlined unwind funclet 0044e76b */ { surface_dtor((DibSurface *)((iptr)&surface)); }
      result = fail5;
      goto LAB_0044e781;
    }
    sprite_grab_from_surface
              (&sprite,(iptr)&surface,9,throneroom_bonus3_rect_x,throneroom_bonus3_rect_y,throneroom_bonus3_rect_w,throneroom_bonus3_rect_h);
    sprite_replace_color(&sprite,7,9);
    sprite_draw
              (&sprite,(iptr)draw_tmp6,(iptr)this->throne_surface_wnd,throneroom_bonus3_rect_x - 1,throneroom_bonus3_rect_y - 1);
  }
  win_flush_pending_msgs();
  for (slot = 5; slot < 7; slot++) {
    if (*(char *)&civs[(this->throne_civ)].throne_room[slot] != '\0') {
      level = civs[(this->throne_civ)].throne_room[slot] - 1;
      loaded = surface_load_gif_resource
                        (&surface,slot * 5 + level + 0x69,10,0xec,(iptr)&this->control_list);
      if (loaded == 0) {
        fail6 = 0;
        try_level = (uint)(*(i32 *)((char *)&try_level + 1)) << 8;
        /* inlined unwind funclet 0044e762 */ { sprite_destroy((Sprite *)((iptr)&sprite)); }
        try_level = 0xffffffff;
        /* inlined unwind funclet 0044e76b */ { surface_dtor((DibSurface *)((iptr)&surface)); }
        result = fail6;
        goto LAB_0044e781;
      }
      sprite_grab_from_surface
                (&sprite,(iptr)&surface,9,
                 *(i32 *)(&throneroom_piece_rect_x + level * 0x10 + slot * 0x40),
                 *(i32 *)(&throneroom_piece_rect_y + level * 0x10 + slot * 0x40),
                 *(i32 *)(&throneroom_piece_rect_w + level * 0x10 + slot * 0x40),
                 *(i32 *)(&throneroom_piece_rect_h + level * 0x10 + slot * 0x40));
      sprite_replace_color(&sprite,7,9);
      sprite_draw
                (&sprite,(iptr)draw_tmp7,(iptr)this->throne_surface_wnd,
                 *(int *)(&throneroom_piece_rect_x + level * 0x10 + slot * 0x40) - 1,
                 *(int *)(&throneroom_piece_rect_y + level * 0x10 + slot * 0x40) - 1);
    }
  }
  win_flush_pending_msgs();
  if (this->throne_complete != 0) {
    for (slot = 4; slot < 7; slot++) {
      if ((1 << ((byte)slot & 0x1f) & (uint)civs[this->throne_civ].throne_room[8]) != 0) {
        loaded = surface_load_gif_resource(&surface,slot + 0xa0,10,0xec,(iptr)&this->control_list)
        ;
        if (loaded == 0) {
          fail7 = 0;
          try_level = (uint)(*(i32 *)((char *)&try_level + 1)) << 8;
          /* inlined unwind funclet 0044e762 */ { sprite_destroy((Sprite *)((iptr)&sprite)); }
          try_level = 0xffffffff;
          /* inlined unwind funclet 0044e76b */ { surface_dtor((DibSurface *)((iptr)&surface)); }
          result = fail7;
          goto LAB_0044e781;
        }
        sprite_grab_from_surface
                  (&sprite,(iptr)&surface,9,(&throneroom_bonus_rect_x)[slot * 4],
                   (&throneroom_bonus_rect_y)[slot * 4],(&throneroom_bonus_rect_w)[slot * 4],
                   (&throneroom_bonus_rect_h)[slot * 4]);
        sprite_replace_color(&sprite,7,9);
        sprite_draw
                  (&sprite,(iptr)draw_tmp8,(iptr)this->throne_surface_wnd,(&throneroom_bonus_rect_x)[slot * 4] - 1,
                   (&throneroom_bonus_rect_y)[slot * 4] - 1);
      }
    }
  }
  win_flush_pending_msgs();
  if (civs[this->throne_civ].throne_room[7] != '\0') {
    level = civs[this->throne_civ].throne_room[7] - 1;
    loaded = surface_load_gif_resource
                      (&surface,civs[this->throne_civ].throne_room[7] + 0x8b,10,0xec,
                       (iptr)&this->control_list);
    if (loaded == 0) {
      fail8 = 0;
      try_level = (uint)(*(i32 *)((char *)&try_level + 1)) << 8;
      /* inlined unwind funclet 0044e762 */ { sprite_destroy((Sprite *)((iptr)&sprite)); }
      try_level = 0xffffffff;
      /* inlined unwind funclet 0044e76b */ { surface_dtor((DibSurface *)((iptr)&surface)); }
      result = fail8;
      goto LAB_0044e781;
    }
    sprite_grab_from_surface
              (&sprite,(iptr)&surface,9,*(i32 *)(&throneroom_piece7_rect_x + level * 0x10),
               *(i32 *)(&throneroom_piece7_rect_y + level * 0x10),
               *(i32 *)(&throneroom_piece7_rect_w + level * 0x10),
               *(i32 *)(&throneroom_piece7_rect_h + level * 0x10));
    sprite_replace_color(&sprite,7,9);
    sprite_draw
              (&sprite,(iptr)draw_tmp9,(iptr)this->throne_surface_wnd,
               *(int *)(&throneroom_piece7_rect_x + level * 0x10) - 1,
               *(int *)(&throneroom_piece7_rect_y + level * 0x10) - 1);
  }
  win_flush_pending_msgs();
  try_level = (uint)(*(i32 *)((char *)&try_level + 1)) << 8;
  /* inlined unwind funclet 0044e762 */ { sprite_destroy((Sprite *)((iptr)&sprite)); }
  try_level = 0xffffffff;
  /* inlined unwind funclet 0044e76b */ { surface_dtor((DibSurface *)((iptr)&surface)); }
  result = 1;
LAB_0044e781:
  return result;
}
#undef draw_tmp9
#undef fail8
#undef draw_tmp8
#undef fail7
#undef draw_tmp7
#undef fail6
#undef draw_tmp6
#undef fail5
#undef draw_tmp5
#undef fail4
#undef draw_tmp4
#undef fail3
#undef draw_tmp3
#undef fail2
#undef draw_tmp2
#undef fail1
#undef draw_tmp1
#undef result
#undef surface
#undef slot
#undef level
#undef sprite
#undef seh_next
#undef seh_handler
#undef try_level

/* 0044e790 auto */
#define draw_tmp2 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define fail2 (*(i32 *)(frame_ + FRAME_OFF(16)))
#define draw_tmp1 (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
#define fail1 (*(i32 *)(frame_ + FRAME_OFF(36)))
#define result (*(i32 *)(frame_ + FRAME_OFF(40)))
#define surface (*(DibSurface *)(frame_ + FRAME_OFF(44)))
#define region_cursors (*(i32 (*)[34])(frame_ + FRAME_OFF(116)))
#define idx (*(iptr *)(frame_ + FRAME_OFF(252)))
#define piece_rects (*(int (*)[60])(frame_ + FRAME_OFF(256)))
#define sprite (*(Sprite *)(frame_ + FRAME_OFF(496)))
#define region_rects (*(i32 (*)[136])(frame_ + FRAME_OFF(556)))
#define bonus_bits (*(byte *)(frame_ + FRAME_OFF(1100)))
#define seh_next (*(i32 *)(frame_ + FRAME_OFF(1104)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(1108)))
#define try_level (*(uint *)(frame_ + FRAME_OFF(1112)))
i32 __thiscall throneroom_render_choices(ThroneRoomWindow *this)

{
  int loaded;
  i8 frame_[FRAME_OFF(1120)] __attribute__((aligned(8)));  /* original stack frame */
  
  try_level = 0xffffffff;
  surface_ctor(&surface);
  try_level = 0;
  sprite_init(&sprite);
  try_level = CONCAT31((*(i32 *)((char *)&try_level + 1)),1);
  piece_rects[0] = 0xd4;
  piece_rects[1] = 1;
  piece_rects[2] = 0xb3;
  piece_rects[3] = 0x127;
  piece_rects[4] = 0x13;
  piece_rects[5] = 0x11b;
  piece_rects[6] = 0x24f;
  piece_rects[7] = 0xc6;
  piece_rects[8] = 0xc6;
  piece_rects[9] = 0x12f;
  piece_rects[10] = 0xd7;
  piece_rects[0xb] = 0xb1;
  piece_rects[0xc] = 0xb;
  piece_rects[0xd] = 1;
  piece_rects[0xe] = 0x25f;
  piece_rects[0xf] = 0x11e;
  piece_rects[0x10] = 0xbc;
  piece_rects[0x11] = 0x12;
  piece_rects[0x12] = 0xe6;
  piece_rects[0x13] = 0x11b;
  piece_rects[0x14] = 1;
  piece_rects[0x15] = 1;
  piece_rects[0x16] = 0x260;
  piece_rects[0x17] = 0x137;
  piece_rects[0x18] = 0x11c;
  piece_rects[0x19] = 0x102;
  piece_rects[0x1a] = 0x27;
  piece_rects[0x1b] = 0x39;
  piece_rects[0x1c] = 1;
  piece_rects[0x1d] = 1;
  piece_rects[0x1e] = 0x280;
  piece_rects[0x1f] = 0x1e0;
  piece_rects[0x20] = 0x14;
  piece_rects[0x21] = 0x13a;
  piece_rects[0x22] = 0x24f;
  piece_rects[0x23] = 0x28;
  piece_rects[0x24] = 0x5f;
  piece_rects[0x25] = 0x6d;
  piece_rects[0x26] = 0x1a3;
  piece_rects[0x27] = 0x5f;
  piece_rects[0x28] = 0x12;
  piece_rects[0x29] = 0x103;
  piece_rects[0x2a] = 0x252;
  piece_rects[0x2b] = 0x2d;
  piece_rects[0x2c] = 0xde;
  piece_rects[0x2d] = 0xd4;
  piece_rects[0x2e] = 0xa2;
  piece_rects[0x2f] = 0x54;
  piece_rects[0x30] = 0x7b;
  piece_rects[0x31] = 0x125;
  piece_rects[0x32] = 0x162;
  piece_rects[0x33] = 0x23;
  piece_rects[0x34] = 0x48;
  piece_rects[0x35] = 0x125;
  piece_rects[0x36] = 0x1c8;
  piece_rects[0x37] = 0x27;
  piece_rects[0x38] = 0x16;
  piece_rects[0x39] = 0x16e;
  piece_rects[0x3a] = 0x249;
  piece_rects[0x3b] = 0x47;
  region_rects[0] = 1;
  region_rects[1] = 2;
  region_rects[2] = 0x16;
  region_rects[3] = 0x19c;
  region_rects[4] = 2;
  region_rects[5] = 0x194;
  region_rects[6] = 0x36;
  region_rects[7] = 0x48;
  region_rects[8] = 0x25c;
  region_rects[9] = 1;
  region_rects[10] = 0x23;
  region_rects[0xb] = 0x197;
  region_rects[0xc] = 0x23c;
  region_rects[0xd] = 0x195;
  region_rects[0xe] = 0x44;
  region_rects[0xf] = 0x49;
  region_rects[0x10] = 0x21d;
  region_rects[0x11] = 0x16d;
  region_rects[0x12] = 0x41;
  region_rects[0x13] = 0x46;
  region_rects[0x14] = 0x1c;
  region_rects[0x15] = 0x16e;
  region_rects[0x16] = 0x47;
  region_rects[0x17] = 0x44;
  region_rects[0x18] = 0x47;
  region_rects[0x19] = 0x124;
  region_rects[0x1a] = 100;
  region_rects[0x1b] = 0x27;
  region_rects[0x1c] = 0x1ad;
  region_rects[0x1d] = 0x124;
  region_rects[0x1e] = 99;
  region_rects[0x1f] = 0x27;
  region_rects[0x20] = 0x47;
  region_rects[0x21] = 0x124;
  region_rects[0x22] = 100;
  region_rects[0x23] = 0x27;
  region_rects[0x24] = 0x1ad;
  region_rects[0x25] = 0x124;
  region_rects[0x26] = 99;
  region_rects[0x27] = 0x27;
  region_rects[0x28] = 0x11c;
  region_rects[0x29] = 0x102;
  region_rects[0x2a] = 0x27;
  region_rects[0x2b] = 0x39;
  region_rects[0x2c] = 0x25;
  region_rects[0x2d] = 0x12;
  region_rects[0x2e] = 0x2d;
  region_rects[0x2f] = 0x120;
  region_rects[0x30] = 0x93;
  region_rects[0x31] = 0x12;
  region_rects[0x32] = 0x2c;
  region_rects[0x33] = 0x124;
  region_rects[0x34] = 0x19d;
  region_rects[0x35] = 0x14;
  region_rects[0x36] = 0x31;
  region_rects[0x37] = 0x121;
  region_rects[0x38] = 0x20b;
  region_rects[0x39] = 0x14;
  region_rects[0x3a] = 0x2f;
  region_rects[0x3b] = 0x11e;
  region_rects[0x3c] = 0xe;
  region_rects[0x3d] = 3;
  region_rects[0x3e] = 0xcf;
  region_rects[0x3f] = 0xc;
  region_rects[0x40] = 0x17f;
  region_rects[0x41] = 1;
  region_rects[0x42] = 0xd3;
  region_rects[0x43] = 0xe;
  region_rects[0x44] = 0xe3;
  region_rects[0x45] = 0xd4;
  region_rects[0x46] = 0xe;
  region_rects[0x47] = 0x51;
  region_rects[0x48] = 0x16f;
  region_rects[0x49] = 0xd5;
  region_rects[0x4a] = 0xb;
  region_rects[0x4b] = 0x52;
  region_rects[0x4c] = 0xbe;
  region_rects[0x4d] = 0x11;
  region_rects[0x4e] = 0x15;
  region_rects[0x4f] = 0x11a;
  region_rects[0x50] = 0x185;
  region_rects[0x51] = 0x12;
  region_rects[0x52] = 0x1a;
  region_rects[0x53] = 0x119;
  region_rects[0x54] = 0xde;
  region_rects[0x55] = 0x24;
  region_rects[0x56] = 0x96;
  region_rects[0x57] = 0x55;
  region_rects[0x58] = 0x11;
  region_rects[0x59] = 0x114;
  region_rects[0x5a] = 0xc1;
  region_rects[0x5b] = 0x19;
  region_rects[0x5c] = 400;
  region_rects[0x5d] = 0x107;
  region_rects[0x5e] = 0xd0;
  region_rects[0x5f] = 0x26;
  region_rects[0x60] = 0x5e;
  region_rects[0x61] = 0x75;
  region_rects[0x62] = 0x36;
  region_rects[99] = 0x47;
  region_rects[100] = 0x10b;
  region_rects[0x65] = 0x6c;
  region_rects[0x66] = 0x46;
  region_rects[0x67] = 0x5e;
  region_rects[0x68] = 0x1cc;
  region_rects[0x69] = 0x75;
  region_rects[0x6a] = 0x33;
  region_rects[0x6b] = 0x49;
  region_rects[0x6c] = 0xb;
  region_rects[0x6d] = 2;
  region_rects[0x6e] = 0x93;
  region_rects[0x6f] = 0x11b;
  region_rects[0x70] = 0x1c2;
  region_rects[0x71] = 2;
  region_rects[0x72] = 0xa7;
  region_rects[0x73] = 0x11b;
  region_rects[0x74] = 0x14;
  region_rects[0x75] = 0x13c;
  region_rects[0x76] = 0xb8;
  region_rects[0x77] = 0x22;
  region_rects[0x78] = 0x193;
  region_rects[0x79] = 0x13d;
  region_rects[0x7a] = 0xcc;
  region_rects[0x7b] = 0x23;
  region_rects[0x7c] = 0xde;
  region_rects[0x7d] = 0x12f;
  region_rects[0x7e] = 0xa8;
  region_rects[0x7f] = 0xaf;
  region_rects[0x80] = 0x13;
  region_rects[0x81] = 0x123;
  region_rects[0x82] = 0x250;
  region_rects[0x83] = 0xbd;
  region_rects[0x84] = 0xd4;
  region_rects[0x85] = 1;
  region_rects[0x86] = 0xb3;
  region_rects[0x87] = 0x127;
  region_cursors[0] = 7;
  region_cursors[1] = 7;
  region_cursors[2] = 7;
  region_cursors[3] = 7;
  region_cursors[4] = 0x10;
  region_cursors[5] = 0x10;
  region_cursors[6] = 0xf;
  region_cursors[7] = 0xf;
  region_cursors[8] = 0xe;
  region_cursors[9] = 0xe;
  region_cursors[10] = 6;
  region_cursors[0xb] = 5;
  region_cursors[0xc] = 5;
  region_cursors[0xd] = 5;
  region_cursors[0xe] = 5;
  region_cursors[0xf] = 5;
  region_cursors[0x10] = 5;
  region_cursors[0x11] = 0xd;
  region_cursors[0x12] = 0xd;
  region_cursors[0x13] = 4;
  region_cursors[0x14] = 4;
  region_cursors[0x15] = 4;
  region_cursors[0x16] = 0xc;
  region_cursors[0x17] = 0xc;
  region_cursors[0x18] = 0xb;
  region_cursors[0x19] = 0xb;
  region_cursors[0x1a] = 0xb;
  region_cursors[0x1b] = 3;
  region_cursors[0x1c] = 3;
  region_cursors[0x1d] = 10;
  region_cursors[0x1e] = 10;
  region_cursors[0x1f] = 2;
  region_cursors[0x20] = 1;
  region_cursors[0x21] = 0;
  clickmap_clear((ClickMapClearView *)(this->choice_clickmap));
  for (idx = 0; idx < 0x22; idx++) {
    clickmap_add
              ((ClickMap *)(this->choice_clickmap),idx,region_cursors[idx],
               region_rects[idx * 4],region_rects[idx * 4 + 1],region_rects[idx * 4 + 2],
               region_rects[idx * 4 + 3]);
  }
  loaded = surface_load_gif_resource
                    ((DibSurface *)this->throne_surface_wnd,100,10,0xec,(iptr)&this->control_list);
  if (loaded == 0) {
    result = 0;
    try_level = try_level & 0xffffff00;
    /* inlined unwind funclet 0044f498 */ { sprite_destroy((Sprite *)((iptr)&sprite)); }
    try_level = 0xffffffff;
    /* inlined unwind funclet 0044f4a4 */ { surface_dtor((DibSurface *)((iptr)&surface)); }
  }
  else {
    if (this->throne_complete == 0) {
      for (idx = 0; idx < 8; idx++) {
        win_flush_pending_msgs();
        if (civs[(this->throne_civ)].throne_room[idx] < 4) {
          loaded = surface_load_gif_resource
                            (&surface,idx + 0xaa,10,0xec,(iptr)&this->control_list);
          if (loaded == 0) {
            fail1 = 0;
            try_level = try_level & 0xffffff00;
            /* inlined unwind funclet 0044f498 */ { sprite_destroy((Sprite *)((iptr)&sprite)); }
            try_level = 0xffffffff;
            /* inlined unwind funclet 0044f4a4 */ { surface_dtor((DibSurface *)((iptr)&surface)); }
            result = fail1;
            goto LAB_0044f4ba;
          }
          sprite_grab_from_surface
                    (&sprite,(iptr)&surface,9,piece_rects[idx * 4],
                     piece_rects[idx * 4 + 1],piece_rects[idx * 4 + 2],
                     piece_rects[idx * 4 + 3]);
          sprite_replace_color(&sprite,7,9);
          sprite_draw
                    (&sprite,(iptr)draw_tmp1,(iptr)this->throne_surface_wnd,piece_rects[idx * 4] - 1,
                     piece_rects[idx * 4 + 1] - 1);
        }
      }
    }
    else {
      bonus_bits = civs[this->throne_civ].throne_room[8];
      for (idx = 0; idx < 7; idx++) {
        win_flush_pending_msgs();
        if ((1 << ((byte)idx & 0x1f) & (uint)bonus_bits) == 0) {
          loaded = surface_load_gif_resource
                            (&surface,idx + 0xb2,10,0xec,(iptr)&this->control_list);
          if (loaded == 0) {
            fail2 = 0;
            try_level = try_level & 0xffffff00;
            /* inlined unwind funclet 0044f498 */ { sprite_destroy((Sprite *)((iptr)&sprite)); }
            try_level = 0xffffffff;
            /* inlined unwind funclet 0044f4a4 */ { surface_dtor((DibSurface *)((iptr)&surface)); }
            result = fail2;
            goto LAB_0044f4ba;
          }
          sprite_grab_from_surface
                    (&sprite,(iptr)&surface,9,piece_rects[idx * 4 + 0x20],
                     piece_rects[idx * 4 + 0x21],piece_rects[idx * 4 + 0x22],
                     piece_rects[idx * 4 + 0x23]);
          sprite_replace_color(&sprite,7,9);
          sprite_draw
                    (&sprite,(iptr)draw_tmp2,(iptr)this->throne_surface_wnd,
                     piece_rects[idx * 4 + 0x20] - 1,piece_rects[idx * 4 + 0x21] - 1);
        }
      }
    }
    try_level = try_level & 0xffffff00;
    /* inlined unwind funclet 0044f498 */ { sprite_destroy((Sprite *)((iptr)&sprite)); }
    try_level = 0xffffffff;
    /* inlined unwind funclet 0044f4a4 */ { surface_dtor((DibSurface *)((iptr)&surface)); }
    result = 1;
  }
LAB_0044f4ba:
  return result;
}
#undef draw_tmp2
#undef fail2
#undef draw_tmp1
#undef fail1
#undef result
#undef surface
#undef region_cursors
#undef idx
#undef piece_rects
#undef sprite
#undef region_rects
#undef bonus_bits
#undef seh_next
#undef seh_handler
#undef try_level

/* 0044f4c9 auto */
#define hit_buf (*(i8 (*)[4])(frame_ + FRAME_OFF(0)))
#define bonus_bits (*(byte *)(frame_ + FRAME_OFF(4)))
#define wnd2 (*(iptr *)(frame_ + FRAME_OFF(8)))
void __cdecl throneroom_on_click(i32 x,i32 y)

{
  int hit;
  iptr civ;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  wnd2 = throneroom_wnd;
  civ = *(iptr *)(throneroom_wnd + 0x500);
  if (*(int *)(throneroom_wnd + 0x1924) == 0) {
    wnd_end_modal_loop((ModalMenuWindow *)(throneroom_wnd + 0x54c));
  }
  else {
    hit = clickmap_hit_test
                      ((ClickMapHitTestView *)(throneroom_wnd + 0x660),x,y,(iptr)hit_buf,
                       throneroom_wnd + 0x192c);
    if (hit < 0) {
      *(i32 *)(wnd2 + 0x192c) = 0;
      snd_play_effect(0x5e,1,0,0);
    }
    else {
      if (*(int *)(wnd2 + 0x1928) == 0) {
        if (9 < *(int *)(wnd2 + 0x192c)) {
          snd_play_effect(0x5e,1,0,0);
          return;
        }
        if (3 < civs[civ].throne_room[(*(int *)(wnd2 + 0x192c))]) {
          snd_play_effect(0x5e,1,0,0);
          return;
        }
      }
      else {
        if (*(int *)(wnd2 + 0x192c) < 10) {
          snd_play_effect(0x5e,1,0,0);
          return;
        }
        *(int *)(wnd2 + 0x192c) = *(int *)(wnd2 + 0x192c) - 10;
        bonus_bits = civs[civ].throne_room[8];
        if ((*(int *)(wnd2 + 0x192c) == 4) || (*(int *)(wnd2 + 0x192c) == 5)) {
          if (((bonus_bits & 0x10) != 0) && ((bonus_bits & 0x20) != 0)) {
            snd_play_effect(0x5e,1,0,0);
            return;
          }
          if (*(int *)(wnd2 + 0x192c) == 4) {
            if ((bonus_bits & 0x10) != 0) {
              *(i32 *)(wnd2 + 0x192c) = 5;
            }
          }
          else if ((bonus_bits & 0x20) != 0) {
            *(i32 *)(wnd2 + 0x192c) = 4;
          }
        }
        if ((1 << (*(byte *)(wnd2 + 0x192c) & 0x1f) & (uint)civs[civ].throne_room[8]) != 0) {
          snd_play_effect(0x5e,1,0,0);
          return;
        }
      }
      wnd_end_modal_loop((ModalMenuWindow *)(wnd2 + 0x54c));
    }
  }
  return;
}
#undef hit_buf
#undef bonus_bits
#undef wnd2

/* 0044f717 auto */
void __cdecl throneroom_on_key(int key)

{
  if (*(int *)(throneroom_wnd + 0x1924) == 0) {
    if ((0xcf < key) && (key < 0xd3)) {
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
#define window (*(SpaceshipWindow * *)(frame_ + FRAME_OFF(0)))
#define seh_next (*(i32 *)(frame_ + FRAME_OFF(8)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(12)))
#define try_level (*(i32 *)(frame_ + FRAME_OFF(16)))
void __cdecl endgame_defeat_movie(iptr civ)

{
  SpaceshipWindow *this;
  int created;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  try_level = 0xffffffff;
  this = operator_new(0x137c);
  try_level = 0;
  if (this == (SpaceshipWindow *)0x0) {
    window = (SpaceshipWindow *)0x0;
  }
  else {
    window = (SpaceshipWindow *)defeat_movie_wnd_ctor(this);
  }
  try_level = 0xffffffff;
  endgame_movie_window = window;
  if (window != (SpaceshipWindow *)0x0) {
    created = defeat_movie_wnd_create(window,civ);
    if (created != 0) {
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
#undef window
#undef seh_next
#undef seh_handler
#undef try_level

/* 004703d4 auto */
#define seh_next (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define try_level (*(i32 *)(frame_ + FRAME_OFF(8)))
SpaceshipWindow * __thiscall defeat_movie_wnd_ctor(SpaceshipWindow *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  try_level = 0xffffffff;
  wnd_ctor((ModalMenuWindow *)this);
  try_level = 0;
  palette_init((GamePalette *)&this->control_list);
  (*(i8 *)((char *)&try_level + 0)) = 1;
  mmwnd_ctor((DocumentWindow *)(this->media_wnd));
  (*(i8 *)((char *)&try_level + 0)) = 2;
  dll_handle_init((DllHandle *)(this->movie_dll));
  (*(i8 *)((char *)&try_level + 0)) = 3;
  font_init_empty((GameFont *)this->movie_caption_font);
  try_level = CONCAT31((*(i32 *)((char *)&try_level + 1)),4);
  surface_ctor((DibSurface *)(((ThroneRoomWindow *)this)->movie_frame_surface));
  this->advance_civ = 0;
  return this;
}
#undef seh_next
#undef seh_handler
#undef try_level

/* 004704ec auto */
#define seh_next (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define try_level (*(int *)(frame_ + FRAME_OFF(8)))
void __thiscall defeat_movie_wnd_dtor(void *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  (*(i32 *)((char *)&try_level + 1)) = 0;
  (*(i8 *)((char *)&try_level + 0)) = 4;
  /* inlined unwind funclet 0047056b */ { surface_dtor((DibSurface *)(*(int *)((iptr)&this) + 0x1324)); }
  (*(i8 *)((char *)&try_level + 0)) = 3;
  /* inlined unwind funclet 0047057a */ { font_destroy((GameFont *)(*(int *)((iptr)&this) + 0xf1c)); }
  (*(i8 *)((char *)&try_level + 0)) = 2;
  /* inlined unwind funclet 00470589 */ { dll_free((DllHandle *)(*(int *)((iptr)&this) + 0xf14)); }
  (*(i8 *)((char *)&try_level + 0)) = 1;
  /* inlined unwind funclet 00470598 */ { avi_player_dtor((AviPlayer *)(*(int *)((iptr)&this) + 0x4ec)); }
  try_level = (uint)(*(i32 *)((char *)&try_level + 1)) << 8;
  /* inlined unwind funclet 004705a7 */ { palette_destroy((GamePalette *)(*(int *)((iptr)&this) + 0xb8)); }
  try_level = 0xffffffff;
  /* inlined unwind funclet 004705b6 */ { wnd_dtor(*(WndBase **)((iptr)&this)); }
  return;
}
#undef seh_next
#undef seh_handler
#undef try_level

/* 004705d7 auto */
#define dll_path (*(CHAR (*)[128])(frame_ + FRAME_OFF(0)))
#define of_struct (*(_OFSTRUCT *)(frame_ + FRAME_OFF(128)))
#define screen_left (*(int *)(frame_ + FRAME_OFF(264)))
#define screen_top (*(int *)(frame_ + FRAME_OFF(268)))
#define screen_right (*(int *)(frame_ + FRAME_OFF(272)))
#define screen_bottom (*(int *)(frame_ + FRAME_OFF(276)))
#define open_err (*(int *)(frame_ + FRAME_OFF(280)))
#define avi_path (*(CHAR (*)[128])(frame_ + FRAME_OFF(284)))
i32 __thiscall defeat_movie_wnd_create(SpaceshipWindow *this,uint civ)

{
  HFILE HVar1;
  i32 result;
  i32 width;
  i8 frame_[FRAME_OFF(416)] __attribute__((aligned(8)));  /* original stack frame */
  
  gfx_get_screen_rect((iptr)&screen_left);
  str_clear((iptr)avi_path);
  str_append((iptr)avi_path,(iptr)((u8 *)&g.d_00655020));
  str_append((iptr)avi_path,(iptr)((u8 *)&g.d_0062b808));
  HVar1 = OpenFile(avi_path,&of_struct,0x4000);
  if (HVar1 == -1) {
    result = 0;
  }
  else {
    str_clear((iptr)dll_path);
    str_append((iptr)dll_path,(iptr)((u8 *)&g.d_00655020));
    str_append((iptr)dll_path,(iptr)((u8 *)&g.d_0062b814));
    HVar1 = OpenFile(dll_path,&of_struct,0x4000);
    if (HVar1 == -1) {
      result = 0;
    }
    else {
      dll_handle_load((DllHandle *)(this->movie_dll),(iptr)dll_path);
      if ((int)civ < 1) {
        this->advance_civ = ~civ + 1;
      }
      else {
        this->advance_civ = civ;
      }
      wnd_create_with_handlers
                ((WndBase *)this,(iptr)((u8 *)&g.d_0062b824),0x800,screen_left,screen_top,screen_right - screen_left,
                 (screen_bottom - screen_top) + 5,(iptr)((u8 *)&g.d_006a8c00),(iptr)((u8 *)&g.d_006553d8));
      wnd_set_bg_color((WndBase *)this,0);
      surface_load_gif_resource
                ((DibSurface *)(this->media_wnd),4000,10,0xec,(iptr)&this->control_list);
      avi_player_create((MediaWindow *)(this->media_wnd),(iptr)((u8 *)&g.d_0062b828),0x800,0,0);
      avi_player_set_double_size((MediaWindow *)(this->media_wnd),1);
      open_err = avi_player_open((AviPlayerOpenView *)(this->media_wnd),(iptr)avi_path);
      if (open_err == 0) {
        surface_fill((DibSurface *)(this->media_wnd),0);
        wnd_center((WndCenterView *)(this->movie_wnd_base));
        avi_player_set_end_callback((AviPlayerEndCbSetView *)(this->media_wnd),(iptr)defeat_movie_on_video_end);
        SetRect((LPRECT)(((ThroneRoomWindow *)this)->movie_caption_rect),0x28,100,600,0x1e0);
        result = surface_get_height((DibSurface *)(this->media_wnd));
        width = surface_get_width((DibSurface *)(this->media_wnd));
        surface_create((DibSurface *)(((ThroneRoomWindow *)this)->movie_frame_surface),width,result);
        avi_player_draw_to
                  ((DibSurface *)(this->media_wnd),(iptr)(((ThroneRoomWindow *)this)->movie_frame_surface),0,0);
        font_set_styled((GameFont *)this->movie_caption_font,0,0x12,2);
        dll_handle_free((DllHandle *)(this->movie_dll));
        result = 1;
      }
      else {
        if (open_err == -0x7ffbfeac) {
          popup_game((iptr)((u8 *)&g.d_0062b82c));
        }
        result = 0;
      }
    }
  }
  return result;
}
#undef dll_path
#undef of_struct
#undef screen_left
#undef screen_top
#undef screen_right
#undef screen_bottom
#undef open_err
#undef avi_path

/* 004708db auto */
#define text_line_cursor (*(iptr *)((u8 *)&g.d_00673f14))
#define advance (*(iptr *)(frame_ + FRAME_OFF(4)))
#define page (*(int *)(frame_ + FRAME_OFF(8)))
void __thiscall defeat_movie_wnd_play(SpaceshipWindow *this)

{
  int status;
  iptr str;
  char *line;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  music_play_track(2,1);
  wnd_handle_show_raise((WndBase *)this);
  wnd_flush_paint();
  wnd_set_palette((WndBase *)this,(iptr)&this->control_list);
  window_show((WindowObjectView *)(this->media_wnd));
  wnd_flush_paint();
  wnd_set_capture((WndBase *)(this->movie_wnd_base));
  gfx_set_text_color_index(0xff);
  advance = 0;
  while ((advance < 100 && (status = civ_has_advance(this->advance_civ,advance), status == 0))) {
    advance++;
  }
  str = label_string(advances[advance].name);
  text_set_string_arg(0,str);
  CharLowerA(&text_string_args);
  str = civ_leader_name(this->advance_civ);
  text_set_string_arg(1,str);
  for (page = 0; page < 3; page++) {
    str_clear((iptr)(this->movie_caption_text));
    text_clear();
    text_append((iptr)((u8 *)&g.d_0062b840));
    text_append_int(page);
    status = text_open_section((iptr)((u8 *)&g.d_006558e8),(iptr)((u8 *)&g.d_00679640));
    if (status == 0) {
      while (line = (char *)text_read_line(1), *line != '@') {
        str_append((iptr)(this->movie_caption_text),text_line_cursor);
        str_append((iptr)(this->movie_caption_text),(iptr)((u8 *)&g.d_0062b850));
      }
      text_clear();
      text_expand_vars((iptr)(this->movie_caption_text),(iptr)((u8 *)&g.d_00679640));
      surface_blit
                ((DibSurface *)(((ThroneRoomWindow *)this)->movie_frame_surface),(iptr)(this->media_wnd),
                 (iptr)(((ThroneRoomWindow *)this)->movie_caption_rect),(iptr)(((ThroneRoomWindow *)this)->movie_caption_rect));
      OffsetRect((LPRECT)(((ThroneRoomWindow *)this)->movie_caption_rect),1,1);
      gfx_set_text_color_index(0);
      surface_draw_text_rect
                ((DibSurface *)(this->media_wnd),(iptr)this->movie_caption_font,(iptr)((u8 *)&g.d_00679640),
                 (iptr)(((ThroneRoomWindow *)this)->movie_caption_rect),0);
      OffsetRect((LPRECT)(((ThroneRoomWindow *)this)->movie_caption_rect),-1,-1);
      gfx_set_text_color_index(0xff);
      surface_draw_text_rect
                ((DibSurface *)(this->media_wnd),(iptr)this->movie_caption_font,(iptr)((u8 *)&g.d_00679640),
                 (iptr)(((ThroneRoomWindow *)this)->movie_caption_rect),0);
      gfx_dissolve_blit((iptr)(this->media_wnd),(iptr)(((ThroneRoomWindow *)this)->movie_caption_rect),4,5);
      text_close_file();
      ui_delay_ticks(0x168);
    }
  }
  avi_player_play((AviPlayerPlayView *)(this->media_wnd));
  if (2 < game.multiplayer) {
    wnd_set_modal_idle_callback((ModalMenuWindow *)(this->movie_wnd_base),(iptr)net_modal_idle_poll);
  }
  wnd_run_modal_loop((ModalMenuWindow *)(this->movie_wnd_base));
  wnd_set_modal_idle_callback((ModalMenuWindow *)(this->movie_wnd_base),0);
  wnd_release_capture((WndBase *)(this->movie_wnd_base));
  wnd_hide((WndBase *)(this->movie_wnd_base));
  wnd_flush_paint();
  wnd_set_palette((WndBase *)&main_frame_wnd,(iptr)((u8 *)&g.d_006a8c00));
  wnd_hide((WndBase *)this);
  wnd_flush_paint();
  return;
}
#undef text_line_cursor
#undef advance
#undef page

/* 00470c1c auto */
#define endgame_movie_window (*(int *)((u8 *)&g.d_0062b804))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define text_line_cursor (*(iptr *)((u8 *)&g.d_00673f14))
void __cdecl defeat_movie_on_video_end(void)

{
  int status;
  char *line;
  
  str_clear(endgame_movie_window + 0xf24);
  text_clear();
  status = text_open_section((iptr)((u8 *)&g.d_006558e8),(iptr)((u8 *)&g.d_0062b854));
  if (status == 0) {
    while( true ) {
      line = (char *)text_read_line(1);
      if (*line == '@') break;
      str_append(endgame_movie_window + 0xf24,text_line_cursor);
      str_append(endgame_movie_window + 0xf24,(iptr)((u8 *)&g.d_0062b864));
    }
    text_expand_vars(endgame_movie_window + 0xf24,(iptr)((u8 *)&g.d_00679640));
    CharUpperA(&text_buffer);
    rect_set_xywh(endgame_movie_window + 0x136c,0xe5,0x4c,200,0x85);
    gfx_set_text_color_index(0);
    surface_draw_text_rect
              ((DibSurface *)(endgame_movie_window + 0x4ec),endgame_movie_window + 0xf1c,(iptr)((u8 *)&g.d_00679640),
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
WndBase * __thiscall defeat_movie_wnd_scalar_dtor(WndBase *this,uint flags)

{
  defeat_movie_wnd_dtor(this);
  if ((flags & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 004710d0 auto */
#define window (*(SpaceshipWindow * *)(frame_ + FRAME_OFF(4)))
#define dialog2 (*(Dialog *)(frame_ + FRAME_OFF(12)))
#define seh_next (*(i32 *)(frame_ + FRAME_OFF(768)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(772)))
#define try_level (*(i32 *)(frame_ + FRAME_OFF(776)))
void __cdecl endgame_spaceship_arrival(iptr civ)

{
  SpaceshipWindow *this;
  int created;
  iptr str;
  i8 frame_[FRAME_OFF(784)] __attribute__((aligned(8)));  /* original stack frame */
  
  try_level = 0xffffffff;
  if (civ < 0) {
    endgame_show_centauri_beaten(civ);
  }
  else {
    snd_cd_stop();
    this = operator_new(0x137c);
    try_level = 0;
    if (this == (SpaceshipWindow *)0x0) {
      window = (SpaceshipWindow *)0x0;
    }
    else {
      window = (SpaceshipWindow *)arrival_movie_wnd_ctor(this);
    }
    try_level = 0xffffffff;
    spaceship_arrival_window = (iptr)window;
    if (window != (SpaceshipWindow *)0x0) {
      created = arrival_movie_wnd_create(window,civ);
      if (created == 0) {
        text_clear();
        text_append_year((int)civs[civ].spaceship_launch_year);
        text_set_string_arg(0,(iptr)((u8 *)&g.d_00679640));
        text_clear();
        text_append_int((int)civs[civ].spaceship_population);
        text_append((iptr)((u8 *)&g.d_0062b880));
        text_set_string_arg(1,(iptr)((u8 *)&g.d_00679640));
        str = civ_get_adjective(civ);
        text_set_string_arg(2,str);
        text_clear();
        text_append_year((int)civs[civ].spaceship_arrival_year);
        text_set_number_arg(3,(int)civs[civ].spaceship_arrival_year);
        str = civ_leader_name(civ);
        text_set_string_arg(4,str);
        dialog_ctor(&dialog2,0x4000);
        try_level = 1;
        dialog_load_game_text(&dialog2,(iptr)((u8 *)&g.d_0062b888));
        dialog_add_sprite((DialogOptionList *)&dialog2,(iptr)((u8 *)&g.d_0063fc58),0,0);
        dlg_show_modal(&dialog2,0);
        try_level = 0xffffffff;
        /* inlined unwind funclet 0047132e */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
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
#undef window
#undef dialog2
#undef seh_next
#undef seh_handler
#undef try_level

/* 00471362 auto */
#define seh_next (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define try_level (*(i32 *)(frame_ + FRAME_OFF(8)))
SpaceshipWindow * __thiscall arrival_movie_wnd_ctor(SpaceshipWindow *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  try_level = 0xffffffff;
  wnd_ctor((ModalMenuWindow *)this);
  try_level = 0;
  palette_init((GamePalette *)&this->control_list);
  (*(i8 *)((char *)&try_level + 0)) = 1;
  mmwnd_ctor((DocumentWindow *)(this->media_wnd));
  (*(i8 *)((char *)&try_level + 0)) = 2;
  dll_handle_init((DllHandle *)(this->movie_dll));
  (*(i8 *)((char *)&try_level + 0)) = 3;
  font_init_empty((GameFont *)this->movie_caption_font);
  try_level = CONCAT31((*(i32 *)((char *)&try_level + 1)),4);
  surface_ctor((DibSurface *)(((ThroneRoomWindow *)this)->movie_frame_surface));
  this->advance_civ = 0;
  return this;
}
#undef seh_next
#undef seh_handler
#undef try_level

/* 0047147a auto */
#define seh_next (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define try_level (*(int *)(frame_ + FRAME_OFF(8)))
void __thiscall arrival_movie_wnd_dtor(void *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  (*(i32 *)((char *)&try_level + 1)) = 0;
  (*(i8 *)((char *)&try_level + 0)) = 4;
  /* inlined unwind funclet 004714f9 */ { surface_dtor((DibSurface *)(*(int *)((iptr)&this) + 0x1324)); }
  (*(i8 *)((char *)&try_level + 0)) = 3;
  /* inlined unwind funclet 00471508 */ { font_destroy((GameFont *)(*(int *)((iptr)&this) + 0xf1c)); }
  (*(i8 *)((char *)&try_level + 0)) = 2;
  /* inlined unwind funclet 00471517 */ { dll_free((DllHandle *)(*(int *)((iptr)&this) + 0xf14)); }
  (*(i8 *)((char *)&try_level + 0)) = 1;
  /* inlined unwind funclet 00471526 */ { avi_player_dtor((AviPlayer *)(*(int *)((iptr)&this) + 0x4ec)); }
  try_level = (uint)(*(i32 *)((char *)&try_level + 1)) << 8;
  /* inlined unwind funclet 00471535 */ { palette_destroy((GamePalette *)(*(int *)((iptr)&this) + 0xb8)); }
  try_level = 0xffffffff;
  /* inlined unwind funclet 00471544 */ { wnd_dtor(*(WndBase **)((iptr)&this)); }
  return;
}
#undef seh_next
#undef seh_handler
#undef try_level

/* 00471565 auto */
#define dll_path (*(i8 (*)[128])(frame_ + FRAME_OFF(0)))
#define screen_left (*(int *)(frame_ + FRAME_OFF(128)))
#define screen_top (*(int *)(frame_ + FRAME_OFF(132)))
#define screen_right (*(int *)(frame_ + FRAME_OFF(136)))
#define screen_bottom (*(int *)(frame_ + FRAME_OFF(140)))
#define open_err (*(int *)(frame_ + FRAME_OFF(144)))
#define avi_path (*(i8 (*)[128])(frame_ + FRAME_OFF(148)))
i32 __thiscall arrival_movie_wnd_create(SpaceshipWindow *this,iptr civ)

{
  int found;
  i32 result;
  i32 width;
  i8 frame_[FRAME_OFF(280)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (civ < 1) {
    this->advance_civ = ~civ + 1;
  }
  else {
    this->advance_civ = civ;
  }
  gfx_get_screen_rect((iptr)&screen_left);
  file_require_cdrom((iptr)((u8 *)&g.d_0062b894));
  str_clear((iptr)avi_path);
  str_append((iptr)avi_path,(iptr)((u8 *)&g.d_0062b8a4));
  found = file_resolve_path((iptr)avi_path);
  if (found == 0) {
    result = 0;
  }
  else {
    str_clear((iptr)dll_path);
    str_append((iptr)dll_path,(iptr)((u8 *)&g.d_0062b8bc));
    found = file_resolve_path((iptr)dll_path);
    if (found == 0) {
      result = 0;
    }
    else {
      dll_handle_load((DllHandle *)(this->movie_dll),(iptr)dll_path);
      wnd_create_with_handlers
                ((WndBase *)this,(iptr)((u8 *)&g.d_0062b8d0),0x800,screen_left,screen_top,screen_right - screen_left,
                 (screen_bottom - screen_top) + 5,(iptr)((u8 *)&g.d_006a8c00),(iptr)((u8 *)&g.d_006553d8));
      wnd_set_bg_color((WndBase *)this,0);
      surface_load_gif_resource
                ((DibSurface *)(this->media_wnd),2000,10,0xec,(iptr)&this->control_list);
      avi_player_create((MediaWindow *)(this->media_wnd),(iptr)((u8 *)&g.d_0062b8d4),0x800,0,0);
      avi_player_set_double_size((MediaWindow *)(this->media_wnd),1);
      open_err = avi_player_open((AviPlayerOpenView *)(this->media_wnd),(iptr)avi_path);
      if (open_err == 0) {
        surface_fill((DibSurface *)(this->media_wnd),0);
        wnd_center((WndCenterView *)(this->movie_wnd_base));
        avi_player_set_end_callback((AviPlayerEndCbSetView *)(this->media_wnd),(iptr)arrival_movie_on_video_end);
        avi_player_set_frame_callback((AviPlayerSetFrameCallbackView *)(this->media_wnd),(iptr)arrival_movie_on_frame,0x2ab);
        SetRect((LPRECT)(((ThroneRoomWindow *)this)->movie_caption_rect),2,100,0x27e,0x1e0);
        result = surface_get_height((DibSurface *)(this->media_wnd));
        width = surface_get_width((DibSurface *)(this->media_wnd));
        surface_create((DibSurface *)(((ThroneRoomWindow *)this)->movie_frame_surface),width,result);
        avi_player_draw_to
                  ((DibSurface *)(this->media_wnd),(iptr)(((ThroneRoomWindow *)this)->movie_frame_surface),0,0);
        font_set_styled((GameFont *)this->movie_caption_font,0,0x12,3);
        dll_handle_free((DllHandle *)(this->movie_dll));
        result = 1;
      }
      else {
        if (open_err == -0x7ffbfeac) {
          popup_game((iptr)((u8 *)&g.d_0062b8d8));
        }
        result = 0;
      }
    }
  }
  return result;
}
#undef dll_path
#undef screen_left
#undef screen_top
#undef screen_right
#undef screen_bottom
#undef open_err
#undef avi_path

/* 00471856 auto */
#define text_line_cursor (*(iptr *)((u8 *)&g.d_00673f14))
#define page (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall arrival_movie_wnd_play(SpaceshipWindow *this)

{
  iptr str;
  int status;
  char *line;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  wnd_handle_show_raise((WndBase *)this);
  wnd_flush_paint();
  wnd_set_palette((WndBase *)this,(iptr)&this->control_list);
  window_show((WindowObjectView *)(this->media_wnd));
  wnd_flush_paint();
  wnd_set_capture((WndBase *)(this->movie_wnd_base));
  gfx_set_text_color_index(0xff);
  str_clear((iptr)(this->movie_caption_text));
  text_clear();
  text_append_year((int)civs[this->advance_civ].spaceship_launch_year);
  text_set_string_arg(0,(iptr)((u8 *)&g.d_00679640));
  text_clear();
  text_append_int((int)civs[this->advance_civ].spaceship_population);
  text_append((iptr)((u8 *)&g.d_0062b8ec));
  text_set_string_arg(1,(iptr)((u8 *)&g.d_00679640));
  str = civ_get_adjective(this->advance_civ);
  text_set_string_arg(2,str);
  text_clear();
  text_append_year((int)civs[this->advance_civ].spaceship_arrival_year);
  text_set_string_arg(3,(iptr)((u8 *)&g.d_00679640));
  str = civ_leader_name(this->advance_civ);
  text_set_string_arg(4,str);
  for (page = 0; page < 3; page++) {
    str_clear((iptr)(this->movie_caption_text));
    text_clear();
    text_append((iptr)((u8 *)&g.d_0062b8f4));
    text_append_int(page);
    status = text_open_section((iptr)((u8 *)&g.d_006558e8),(iptr)((u8 *)&g.d_00679640));
    if (status == 0) {
      while( true ) {
        line = (char *)text_read_line(1);
        if (*line == '@') break;
        str_append((iptr)(this->movie_caption_text),text_line_cursor);
        str_append((iptr)(this->movie_caption_text),(iptr)((u8 *)&g.d_0062b900));
      }
      text_clear();
      text_expand_vars((iptr)(this->movie_caption_text),(iptr)((u8 *)&g.d_00679640));
      surface_blit
                ((DibSurface *)(((ThroneRoomWindow *)this)->movie_frame_surface),(iptr)(this->media_wnd),
                 (iptr)(((ThroneRoomWindow *)this)->movie_caption_rect),(iptr)(((ThroneRoomWindow *)this)->movie_caption_rect));
      OffsetRect((LPRECT)(((ThroneRoomWindow *)this)->movie_caption_rect),1,1);
      gfx_set_text_color_index(0);
      surface_draw_text_rect
                ((DibSurface *)(this->media_wnd),(iptr)this->movie_caption_font,(iptr)((u8 *)&g.d_00679640),
                 (iptr)(((ThroneRoomWindow *)this)->movie_caption_rect),0);
      OffsetRect((LPRECT)(((ThroneRoomWindow *)this)->movie_caption_rect),-1,-1);
      gfx_set_text_color_index(0xf1);
      surface_draw_text_rect
                ((DibSurface *)(this->media_wnd),(iptr)this->movie_caption_font,(iptr)((u8 *)&g.d_00679640),
                 (iptr)(((ThroneRoomWindow *)this)->movie_caption_rect),0);
      gfx_dissolve_blit((iptr)(this->media_wnd),(iptr)(((ThroneRoomWindow *)this)->movie_caption_rect),4,5);
      text_close_file();
      ui_delay_ticks(0x168);
    }
  }
  avi_player_play((AviPlayerPlayView *)(this->media_wnd));
  if (2 < game.multiplayer) {
    wnd_set_modal_idle_callback((ModalMenuWindow *)(this->movie_wnd_base),(iptr)net_modal_idle_poll);
  }
  wnd_run_modal_loop((ModalMenuWindow *)(this->movie_wnd_base));
  wnd_set_modal_idle_callback((ModalMenuWindow *)(this->movie_wnd_base),0);
  wnd_release_capture((WndBase *)(this->movie_wnd_base));
  wnd_hide((WndBase *)(this->movie_wnd_base));
  wnd_flush_paint();
  wnd_hide((WndBase *)this);
  wnd_set_palette((WndBase *)&main_frame_wnd,(iptr)((u8 *)&g.d_006a8c00));
  wnd_flush_paint();
  return;
}
#undef text_line_cursor
#undef page

/* 00471c2a auto */
#define text_line_cursor (*(iptr *)((u8 *)&g.d_00673f14))
#define text_y2 (*(int *)(frame_ + FRAME_OFF(4)))
#define dirty_left (*(i32 *)(frame_ + FRAME_OFF(12)))
#define dirty_top (*(i32 *)(frame_ + FRAME_OFF(16)))
#define dirty_right (*(i32 *)(frame_ + FRAME_OFF(20)))
#define dirty_bottom (*(int *)(frame_ + FRAME_OFF(24)))
void __cdecl arrival_movie_on_frame(void)

{
  int status;
  char *line;
  i32 width;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  *(i32 *)(spaceship_arrival_window + 0xa98) = 0;
  str_clear(spaceship_arrival_window + 0xf24);
  text_clear();
  status = text_open_section((iptr)((u8 *)&g.d_006558e8),(iptr)((u8 *)&g.d_0062b904));
  if (status == 0) {
    text_y2 = 0xc;
    text_set_font(spaceship_arrival_window + 0xf1c);
    text_set_surface(spaceship_arrival_window + 0x4ec);
    text_set_colors(0xff,0,1,1);
    while( true ) {
      line = (char *)text_read_line(1);
      if (*line == '@') break;
      str_clear(spaceship_arrival_window + 0xf24);
      str_append(spaceship_arrival_window + 0xf24,text_line_cursor);
      text_expand_vars(spaceship_arrival_window + 0xf24,(iptr)((u8 *)&g.d_00679640));
      width = rect_width(spaceship_arrival_window + 0x136c);
      gfx_draw_text_centered((iptr)((u8 *)&g.d_00679640),*(i32 *)(spaceship_arrival_window + 0x136c),text_y2,width);
      status = font_line_spacing((GameFont *)(spaceship_arrival_window + 0xf1c));
      text_y2 += status;
    }
    dirty_left = *(i32 *)(spaceship_arrival_window + 0x136c);
    dirty_right = *(i32 *)(spaceship_arrival_window + 0x1374);
    dirty_top = 0xc;
    dirty_bottom = text_y2;
    gfx_dissolve_blit(spaceship_arrival_window + 0x4ec,(iptr)&dirty_left,4,5);
    text_close_file();
  }
  return;
}
#undef text_line_cursor
#undef text_y2
#undef dirty_left
#undef dirty_top
#undef dirty_right
#undef dirty_bottom

/* 00471db7 auto */
void __cdecl arrival_movie_on_video_end(void)

{
  wnd_end_modal_loop((ModalMenuWindow *)(spaceship_arrival_window + 0x534));
  return;
}

/* 00471dd8 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define text_line_cursor (*(iptr *)((u8 *)&g.d_00673f14))
#define surface_wnd (*(i8 (*)[276])(frame_ + FRAME_OFF(0)))
#define frame_wnd (*(ModalMenuWindow *)(frame_ + FRAME_OFF(276)))
#define text_rect (*(tagRECT *)(frame_ + FRAME_OFF(460)))
#define page (*(int *)(frame_ + FRAME_OFF(476)))
#define backup_surface (*(DibSurface *)(frame_ + FRAME_OFF(480)))
#define font2 (*(GameFont *)(frame_ + FRAME_OFF(552)))
#define text_buf (*(i8 (*)[256])(frame_ + FRAME_OFF(560)))
#define dll (*(DllHandle *)(frame_ + FRAME_OFF(816)))
#define screen_left (*(int *)(frame_ + FRAME_OFF(820)))
#define screen_top (*(int *)(frame_ + FRAME_OFF(824)))
#define screen_right (*(int *)(frame_ + FRAME_OFF(828)))
#define screen_bottom (*(int *)(frame_ + FRAME_OFF(832)))
#define dll_path (*(i8 (*)[128])(frame_ + FRAME_OFF(836)))
#define palette (*(GamePalette *)(frame_ + FRAME_OFF(964)))
#define seh_next (*(i32 *)(frame_ + FRAME_OFF(2040)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(2044)))
#define try_level (*(int *)(frame_ + FRAME_OFF(2048)))
void __cdecl endgame_show_centauri_beaten(uptr civ)

{
  int status;
  iptr str;
  char *line;
  i8 frame_[FRAME_OFF(2056)] __attribute__((aligned(8)));  /* original stack frame */
  
  try_level = 0xffffffff;
  surfwnd_ctor((SurfaceWindow *)surface_wnd);
  try_level = 0;
  dll_handle_init(&dll);
  (*(i8 *)((char *)&try_level + 0)) = 1;
  wnd_ctor(&frame_wnd);
  (*(i8 *)((char *)&try_level + 0)) = 2;
  palette_init(&palette);
  (*(i8 *)((char *)&try_level + 0)) = 3;
  surface_ctor(&backup_surface);
  (*(i8 *)((char *)&try_level + 0)) = 4;
  font_init_empty(&font2);
  (*(i8 *)((char *)&try_level + 0)) = 5;
  if ((int)civ < 1) {
    civ = ~civ + 1;
  }
  font_set_styled(&font2,0,0x12,3);
  str_clear((iptr)dll_path);
  str_append((iptr)dll_path,(iptr)((u8 *)&g.d_0062b910));
  status = file_resolve_path((iptr)dll_path);
  if (status == 0) {
    (*(i8 *)((char *)&try_level + 0)) = 4;
    /* inlined unwind funclet 00472393 */ { font_destroy((GameFont *)((iptr)&font2)); }
    (*(i8 *)((char *)&try_level + 0)) = 3;
    /* inlined unwind funclet 0047239f */ { surface_dtor((DibSurface *)((iptr)&backup_surface)); }
    (*(i8 *)((char *)&try_level + 0)) = 2;
    /* inlined unwind funclet 004723ab */ { palette_destroy((GamePalette *)((iptr)&palette)); }
    (*(i8 *)((char *)&try_level + 0)) = 1;
    /* inlined unwind funclet 004723b7 */ { wnd_dtor((WndBase *)((iptr)&frame_wnd)); }
    try_level = (uint)(*(i32 *)((char *)&try_level + 1)) << 8;
    /* inlined unwind funclet 004723c3 */ { dll_free((DllHandle *)((iptr)&dll)); }
    try_level = 0xffffffff;
    /* inlined unwind funclet 004723cf */ { surfwnd_dtor((SurfaceWindow *)((iptr)&surface_wnd)); }
  }
  else {
    dll_handle_load(&dll,(iptr)dll_path);
    gfx_get_screen_rect((iptr)&screen_left);
    SetRect(&text_rect,0,0,0x280,0xf0);
    InflateRect(&text_rect,-10,0);
    wnd_create_with_handlers
              ((WndBase *)&frame_wnd,(iptr)((u8 *)&g.d_0062b924),0x800,screen_left,screen_top,screen_right - screen_left,
               (screen_bottom - screen_top) + 5,(iptr)((u8 *)&g.d_006a8c00),(iptr)((u8 *)&g.d_006553d8));
    wnd_set_bg_color((WndBase *)&frame_wnd,0);
    surface_wnd_create
              ((DibSurface *)surface_wnd,(iptr)((u8 *)&g.d_0062b928),0x800,0,0,0x280,0xf0,(iptr)&palette);
    surface_load_gif_resource((DibSurface *)surface_wnd,30000,10,0xec,(iptr)&palette);
    wnd_center((WndCenterView *)(surface_wnd + 0x48));
    surface_create(&backup_surface,0x280,0xf0);
    surface_blit
              ((DibSurface *)surface_wnd,(iptr)&backup_surface,(iptr)&text_rect,(iptr)&text_rect);
    surface_set_palette(&backup_surface,(iptr)&palette);
    wnd_handle_show_raise((WndBase *)&frame_wnd);
    wnd_flush_paint();
    wnd_set_palette((WndBase *)&frame_wnd,(iptr)&palette);
    window_show((WindowObjectView *)surface_wnd);
    wnd_flush_paint();
    wnd_set_capture((WndBase *)(surface_wnd + 0x48));
    gfx_set_text_color_index(0xff);
    text_clear();
    text_append_year((int)civs[civ].spaceship_launch_year);
    text_set_string_arg(0,(iptr)((u8 *)&g.d_00679640));
    text_clear();
    text_append_int((int)civs[civ].spaceship_population);
    text_append((iptr)((u8 *)&g.d_0062b92c));
    text_set_string_arg(1,(iptr)((u8 *)&g.d_00679640));
    str = civ_get_adjective(civ);
    text_set_string_arg(2,str);
    text_clear();
    text_append_year((int)civs[civ].spaceship_arrival_year);
    text_set_string_arg(3,(iptr)((u8 *)&g.d_00679640));
    str = civ_leader_name(human_civ);
    text_set_string_arg(4,str);
    status = font_cached_height(&font2);
    text_rect.top = text_rect.bottom + status * -2 >> 1;
    for (page = 0; page < 5; page++) {
      str_clear((iptr)text_buf);
      text_clear();
      text_append((iptr)((u8 *)&g.d_0062b934));
      text_append_int(page);
      status = text_open_section((iptr)((u8 *)&g.d_006558e8),(iptr)((u8 *)&g.d_00679640));
      if (status == 0) {
        while (line = (char *)text_read_line(1), *line != '@') {
          str_append((iptr)text_buf,text_line_cursor);
          str_append((iptr)text_buf,(iptr)((u8 *)&g.d_0062b944));
        }
        text_clear();
        text_expand_vars((iptr)text_buf,(iptr)((u8 *)&g.d_00679640));
        surface_blit(&backup_surface,(iptr)surface_wnd,(iptr)&text_rect,(iptr)&text_rect);
        OffsetRect(&text_rect,1,1);
        gfx_set_text_color_index(0);
        surface_draw_text_rect
                  ((DibSurface *)surface_wnd,(iptr)&font2,(iptr)((u8 *)&g.d_00679640),(iptr)&text_rect,0);
        OffsetRect(&text_rect,-1,-1);
        gfx_set_text_color_index(0xff);
        surface_draw_text_rect
                  ((DibSurface *)surface_wnd,(iptr)&font2,(iptr)((u8 *)&g.d_00679640),(iptr)&text_rect,0);
        gfx_dissolve_blit((iptr)surface_wnd,(iptr)&text_rect,4,5);
        text_close_file();
        ui_delay_ticks(0x168);
      }
    }
    wnd_release_capture((WndBase *)(surface_wnd + 0x48));
    wnd_hide((WndBase *)(surface_wnd + 0x48));
    wnd_flush_paint();
    wnd_set_palette((WndBase *)&frame_wnd,(iptr)((u8 *)&g.d_006a8c00));
    wnd_hide((WndBase *)&frame_wnd);
    wnd_flush_paint();
    dll_handle_free(&dll);
    (*(i8 *)((char *)&try_level + 0)) = 4;
    /* inlined unwind funclet 00472393 */ { font_destroy((GameFont *)((iptr)&font2)); }
    (*(i8 *)((char *)&try_level + 0)) = 3;
    /* inlined unwind funclet 0047239f */ { surface_dtor((DibSurface *)((iptr)&backup_surface)); }
    (*(i8 *)((char *)&try_level + 0)) = 2;
    /* inlined unwind funclet 004723ab */ { palette_destroy((GamePalette *)((iptr)&palette)); }
    (*(i8 *)((char *)&try_level + 0)) = 1;
    /* inlined unwind funclet 004723b7 */ { wnd_dtor((WndBase *)((iptr)&frame_wnd)); }
    try_level = (uint)(*(i32 *)((char *)&try_level + 1)) << 8;
    /* inlined unwind funclet 004723c3 */ { dll_free((DllHandle *)((iptr)&dll)); }
    try_level = 0xffffffff;
    /* inlined unwind funclet 004723cf */ { surfwnd_dtor((SurfaceWindow *)((iptr)&surface_wnd)); }
  }
  return;
}
#undef human_civ
#undef text_line_cursor
#undef surface_wnd
#undef frame_wnd
#undef text_rect
#undef page
#undef backup_surface
#undef font2
#undef text_buf
#undef dll
#undef screen_left
#undef screen_top
#undef screen_right
#undef screen_bottom
#undef dll_path
#undef palette
#undef seh_next
#undef seh_handler
#undef try_level

/* 004728c0 auto */
void * __thiscall arrival_movie_wnd_scalar_dtor(void *this,uint flags)

{
  arrival_movie_wnd_dtor(this);
  if ((flags & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 004a76f5 auto */
#define destroyed_civ_count (*(i16 *)((u8 *)&g.d_00655128))
#define i (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl destroyed_civs_clear(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  destroyed_civ_count = 0;
  for (i = 0; i < 0xc; i++) {
    *(i16 *)(&destroyed_civ_turns + i * 2) = 0;
    (&destroyed_civ_killers)[i] = 0;
    (&destroyed_civ_names)[i * 0x18] = 0;
  }
  return;
}
#undef destroyed_civ_count
#undef i

/* 004bc480 auto */
#define barracks_count (*(int *)(frame_ + FRAME_OFF(0)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(4)))
#define air_strength (*(int (*)[8])(frame_ + FRAME_OFF(8)))
#define city_count (*(int *)(frame_ + FRAME_OFF(40)))
#define city2 (*(iptr *)(frame_ + FRAME_OFF(44)))
#define city (*(iptr *)(frame_ + FRAME_OFF(48)))
#define land_rivals (*(int *)(frame_ + FRAME_OFF(52)))
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(56)))
#define unit_count (*(int *)(frame_ + FRAME_OFF(60)))
#define war_count (*(int *)(frame_ + FRAME_OFF(64)))
#define civ2 (*(iptr *)(frame_ + FRAME_OFF(68)))
#define air_rivals (*(int *)(frame_ + FRAME_OFF(72)))
#define land_strength (*(int (*)[8])(frame_ + FRAME_OFF(76)))
i32 __cdecl council_military_advice(iptr civ,i32 era)

{
  int has;
  i32 result;
  i8 frame_[FRAME_OFF(112)] __attribute__((aligned(8)));  /* original stack frame */
  
  barracks_count = 0;
  city_count = 0;
  city2 = -1;
  for (city = 0; city < game.num_cities; city++) {
    if ((cities[city].id != 0) && (cities[city].owner == civ)) {
      has = city_has_improvement(city,2);
      if (has != 0) {
        barracks_count++;
      }
      has = city_has_improvement(city,1);
      if (has != 0) {
        city2 = city;
      }
      city_count++;
    }
  }
  if (city_count < 2) {
    city_count = 1;
  }
  unit_count = 0;
  for (unit = 0; unit < game.num_units; unit++) {
    if ((units[unit].id != 0) && (units[unit].owner == civ)) {
      unit_count++;
    }
  }
  if ((city_count - 1 + unit_count) / city_count < (int)((civs[civ].government < 5) + 2)) {
    result = 1;
  }
  else {
    for (civ2 = 0; civ2 < 8; civ2++) {
      air_strength[civ2] = 0;
      land_strength[civ2] = air_strength[civ2];
    }
    for (civ2 = 1; civ2 < 8; civ2++) {
      has = civ_has_advance(civ2,0x4b);
      if (has != 0) {
        air_strength[civ2]++;
      }
      has = civ_has_advance(civ2,0x3b);
      if (has != 0) {
        air_strength[civ2]++;
      }
      for (unit_type = 0; unit_type < 0x3e; unit_type++) {
        has = civ_has_advance(civ2,(int)unit_types[unit_type].prerequisite);
        if (has != 0) {
          if (unit_types[unit_type].domain == 2) {
            air_strength[civ2]++;
          }
          else if ((unit_types[unit_type].role == '\0') || (unit_types[unit_type].role == 1)) {
            land_strength[civ2]++;
          }
        }
      }
    }
    land_rivals = 0;
    air_rivals = 0;
    war_count = 0;
    for (civ2 = 1; civ2 < 8; civ2++) {
      if (civ != civ2) {
        if ((*(byte *)(civ2 * 4 + (iptr)((u8 *)&civs + 33) + civ * 0x594) & 0x20) != 0) {
          war_count++;
        }
        if (air_strength[civ] < air_strength[civ2]) {
          air_rivals++;
        }
        if (land_strength[civ] < land_strength[civ2]) {
          land_rivals++;
        }
      }
    }
    has = bits_count8((uint)game.civs_alive);
    if ((has - 1) / 2 < land_rivals) {
      result = 2;
    }
    else {
      has = bits_count8((uint)game.civs_alive);
      if ((has - 1) / 2 < air_rivals) {
        result = 3;
      }
      else {
        has = civ_has_advance(civ,0x2f);
        if ((((has == 0) || (city2 < 0)) ||
            (has = city_has_improvement(city2,8), has != 0)) ||
           (has = civ_has_wonder(civ,6), has != 0)) {
          if (barracks_count == 0) {
            result = 4;
          }
          else if ((war_count == 0) && (4 < game.power_rank[civ])) {
            result = 7;
          }
          else {
            result = 6;
          }
        }
        else {
          result = 5;
        }
      }
    }
  }
  return result;
}
#undef barracks_count
#undef unit
#undef air_strength
#undef city_count
#undef city2
#undef city
#undef land_rivals
#undef unit_type
#undef unit_count
#undef war_count
#undef civ2
#undef air_rivals
#undef land_strength

/* 004bc8aa auto */
#define city_count (*(int *)(frame_ + FRAME_OFF(0)))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(4)))
#define city (*(iptr *)(frame_ + FRAME_OFF(8)))
#define built_count (*(int *)(frame_ + FRAME_OFF(12)))
#define rivals_ahead (*(int *)(frame_ + FRAME_OFF(16)))
#define civ2 (*(iptr *)(frame_ + FRAME_OFF(20)))
#define route_total (*(int *)(frame_ + FRAME_OFF(24)))
i32 __cdecl council_science_advice(iptr civ,int era)

{
  i32 result;
  int has;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  rivals_ahead = 0;
  for (civ2 = 1; civ2 < 8; civ2++) {
    if ((civ2 != civ) && (civs[civ].num_advances <= civs[civ2].num_advances)) {
      rivals_ahead++;
    }
  }
  if (rivals_ahead == 0) {
    result = 7;
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
    city_count = 0;
    built_count = 0;
    route_total = (uint)civs[civ].units_active[0x30] + (uint)civs[civ].units_active[0x31];
    if (era == 0) {
      improvement = 6;
    }
    else if (era == 1) {
      improvement = 0xc;
    }
    else {
      improvement = 0x1a;
    }
    for (city = 0; city < game.num_cities; city++) {
      if ((cities[city].id != 0) && (cities[city].owner == civ)) {
        city_count++;
        has = city_has_improvement(city,improvement);
        if (has != 0) {
          built_count++;
        }
        route_total += (char)cities[city].trade_routes;
      }
    }
    has = civ_has_advance(civ,(int)improvements[improvement].preq);
    if ((has == 0) || (city_count / 2 <= built_count)) {
      has = civ_has_advance(civ,0x54);
      if ((has == 0) || ((int)(city_count + (city_count >> 0x1f & 3U)) >> 2 <= route_total)) {
        has = bits_count8((uint)game.civs_alive);
        if (rivals_ahead < has / 2) {
          result = 5;
        }
        else {
          result = 1;
        }
      }
      else {
        result = 4;
      }
    }
    else {
      result = 3;
    }
  }
  return result;
}
#undef city_count
#undef improvement
#undef city
#undef built_count
#undef rivals_ahead
#undef civ2
#undef route_total

/* 004bcb9b auto */
#define built_count (*(int *)(frame_ + FRAME_OFF(0)))
#define city_count (*(int *)(frame_ + FRAME_OFF(8)))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(12)))
#define city (*(iptr *)(frame_ + FRAME_OFF(16)))
#define needed_advance (*(iptr *)(frame_ + FRAME_OFF(20)))
#define upkeep_total (*(int *)(frame_ + FRAME_OFF(28)))
#define tax_total (*(int *)(frame_ + FRAME_OFF(32)))
#define improvement_counts (*(int (*)[39])(frame_ + FRAME_OFF(36)))
#define target_improvement (*(iptr *)(frame_ + FRAME_OFF(192)))
#define ratio_divisor (*(int *)(frame_ + FRAME_OFF(196)))
#define route_total (*(int *)(frame_ + FRAME_OFF(200)))
i32 __cdecl council_trade_advice(iptr civ,int era)

{
  int value;
  i32 result;
  i8 frame_[FRAME_OFF(208)] __attribute__((aligned(8)));  /* original stack frame */
  
  tax_total = 0;
  upkeep_total = 0;
  built_count = 0;
  city_count = 0;
  route_total = (uint)civs[civ].units_active[0x30] + (uint)civs[civ].units_active[0x31];
  if (era == 0) {
    needed_advance = 0x14;
    target_improvement = 5;
    ratio_divisor = 2;
  }
  else if (era == 1) {
    needed_advance = 6;
    target_improvement = 10;
    ratio_divisor = 3;
  }
  else {
    needed_advance = 0x16;
    target_improvement = 0x16;
    ratio_divisor = 4;
  }
  for (improvement = 0; improvement < 0x27; improvement++) {
    improvement_counts[improvement] = 0;
  }
  for (city = 0; city < game.num_cities; city++) {
    if ((cities[city].id != 0) && (cities[city].owner == civ)) {
      city_count++;
      route_total += (char)cities[city].trade_routes;
      city_split_trade(city,(int)cities[city].trade,1,0);
      for (improvement = 0; improvement < 0x27; improvement++) {
        value = city_has_improvement(city,improvement);
        if (value != 0) {
          improvement_counts[improvement]++;
        }
      }
      value = city_has_improvement(city,target_improvement);
      if (value != 0) {
        built_count++;
      }
      if ((cities[city].flags & 1) == 0) {
        tax_total += cities[city].tax;
      }
    }
  }
  for (improvement = 0; improvement < 0x27; improvement++) {
    if ((improvement_counts[improvement] != 0) && (value = civ_improvement_upkeep(civ,improvement), value != 0)) {
      upkeep_total += improvement_counts[improvement] * value;
    }
  }
  if ((tax_total < upkeep_total) && (civs[civ].gold < 100)) {
    result = 1;
  }
  else {
    value = civ_has_advance(civ,needed_advance);
    if (value == 0) {
      result = 2;
    }
    else if (built_count < city_count / ratio_divisor) {
      result = 3;
    }
    else {
      value = civ_has_advance(civ,0x54);
      if (value == 0) {
        result = 4;
      }
      else if (route_total < (int)(city_count + (city_count >> 0x1f & 3U)) >> 2) {
        result = 5;
      }
      else if (tax_total - upkeep_total < 6) {
        result = 6;
      }
      else {
        result = 7;
      }
    }
  }
  return result;
}
#undef built_count
#undef city_count
#undef improvement
#undef city
#undef needed_advance
#undef upkeep_total
#undef tax_total
#undef improvement_counts
#undef target_improvement
#undef ratio_divisor
#undef route_total

/* 004bcfcf auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define embassy_count (*(int *)(frame_ + FRAME_OFF(4)))
#define needed_advance (*(iptr *)(frame_ + FRAME_OFF(8)))
#define war_count (*(int *)(frame_ + FRAME_OFF(12)))
#define alliance_count (*(int *)(frame_ + FRAME_OFF(16)))
#define other_civ (*(int *)(frame_ + FRAME_OFF(20)))
#define contact_count (*(int *)(frame_ + FRAME_OFF(24)))
i32 __cdecl council_foreign_advice(iptr civ,int era)

{
  int has;
  i32 result;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  war_count = 0;
  embassy_count = 0;
  alliance_count = 0;
  contact_count = 0;
  for (other_civ = 1; other_civ < 8; other_civ++) {
    if (other_civ != civ) {
      if ((*(byte *)&civs[civ].treaties[other_civ] & 1) != 0) {
        contact_count++;
      }
      if ((*(byte *)&civs[civ].treaties[other_civ] & 8) != 0) {
        alliance_count++;
      }
      if ((*(byte *)(civ * 0x594 + (iptr)((u8 *)&civs + 33) + other_civ * 4) & 0x20) != 0) {
        war_count++;
      }
      if ((((*(byte *)&civs[human_civ].treaties[other_civ] & 0x80) != 0) ||
          (has = civ_has_wonder(human_civ,0x18), has != 0)) ||
         (has = civ_has_wonder(human_civ,9), has != 0)) {
        embassy_count++;
      }
    }
  }
  if (contact_count == 0) {
    result = 1;
  }
  else {
    if (era == 2) {
      needed_advance = 0x1b;
    }
    else {
      needed_advance = 0x58;
    }
    has = civ_has_advance(civ,needed_advance);
    if (has == 0) {
      result = 3;
    }
    else if ((((contact_count < 2) || (1 < civs[civ].reputation)) || (alliance_count != 0)) ||
            (((civs[civ].flags & 0x100) != 0 || (6 < game.power_rank[civ])))) {
      if (civs[civ].reputation < 3) {
        if ((war_count == contact_count) && (1 < civs[civ].reputation)) {
          result = 4;
        }
        else if ((civs[civ].flags & 0x80) == 0) {
          result = 6;
        }
        else if ((embassy_count == 0) || ((war_count == contact_count && (embassy_count < contact_count)))) {
          result = 5;
        }
        else if (war_count == contact_count) {
          result = 6;
        }
        else {
          result = 7;
        }
      }
      else {
        result = 4;
      }
    }
    else {
      result = 2;
    }
  }
  return result;
}
#undef human_civ
#undef embassy_count
#undef needed_advance
#undef war_count
#undef alliance_count
#undef other_civ
#undef contact_count

/* 004bd2a3 auto */
#define city (*(iptr *)(frame_ + FRAME_OFF(0)))
#define content_count (*(int *)(frame_ + FRAME_OFF(8)))
#define celebrate_count (*(int *)(frame_ + FRAME_OFF(12)))
#define unhappy_count (*(int *)(frame_ + FRAME_OFF(16)))
#define disorder_count (*(int *)(frame_ + FRAME_OFF(20)))
i32 __cdecl council_attitude_advice(iptr civ,i32 era)

{
  bool rates_off;
  ushort recalc_flag;
  i32 result;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  recalc_flag = game.transient_flags & 4;
  game.transient_flags = game.transient_flags & 0xfffb;
  content_count = 0;
  disorder_count = 0;
  celebrate_count = 0;
  unhappy_count = 0;
  for (city = 0; city < game.num_cities; city++) {
    if ((cities[city].id != 0) && (cities[city].owner == civ)) {
      if ((recalc_flag != 0) && (4 < civs[civ].government)) {
        city_recalc(city,1);
      }
      if ((char)cities[city].happy < (char)cities[city].unhappy) {
        unhappy_count++;
        if ((cities[city].flags & 1) != 0) {
          disorder_count++;
        }
      }
      else if (cities[city].happy == cities[city].unhappy) {
        content_count++;
      }
      if ((cities[city].flags & 2) != 0) {
        celebrate_count++;
      }
    }
  }
  if (civs[civ].government < 5) {
    rates_off = true;
    if ((((unhappy_count == 0) && (content_count != 0)) && (celebrate_count == 0)) &&
       ((uint)civs[civ].science_rate + (uint)civs[civ].tax_rate == 10)) {
      rates_off = false;
    }
  }
  else {
    rates_off = (uint)civs[civ].science_rate + (uint)civs[civ].tax_rate < 9;
  }
  if (unhappy_count == 0) {
    if (rates_off) {
      if (celebrate_count == 0) {
        result = 5;
      }
      else {
        result = 6;
      }
    }
    else {
      result = 4;
    }
  }
  else if (rates_off) {
    if ((disorder_count == 0) || (civs[civ].government != 6)) {
      result = 3;
    }
    else {
      result = 1;
    }
  }
  else {
    result = 2;
  }
  return result;
}
#undef city
#undef content_count
#undef celebrate_count
#undef unhappy_count
#undef disorder_count

/* 0050a2f7 auto */
#define city2 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define city (*(iptr *)(frame_ + FRAME_OFF(8)))
#define draw_x (*(int *)(frame_ + FRAME_OFF(16)))
#define best_score (*(int *)(frame_ + FRAME_OFF(28)))
#define score (*(int *)(frame_ + FRAME_OFF(32)))
i32 __cdecl
foreign_minister_draw_civ_city(i32 ctx,iptr surface,int civ,byte flags,int x,int y,
            int height)

{
  int value;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  best_score = 0;
  city2 = -1;
  for (city = 0; city < game.num_cities; city++) {
    if ((cities[city].id != 0) && (cities[city].owner == civ)) {
      score = (int)cities[city].size;
      value = city_has_improvement(city,1);
      if (value != 0) {
        score += 200;
      }
      if (cities[city].building == -1) {
        score += 100;
      }
      if (best_score < score) {
        best_score = score;
        city2 = city;
      }
    }
  }
  if (-1 < city2) {
    draw_x = x;
    if ((flags & 1) != 0) {
      draw_x = x + 0x26;
    }
    value = gfx_zoom_scale(0x30,0xfffffffe);
    gfx_draw_city(surface,city2,0,draw_x,y - (value - height) / 2,0xfffffffe);
  }
  return 0;
}
#undef city2
#undef city
#undef draw_x
#undef best_score
#undef score

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
#define window (*(i8 (*)[1808])(frame_ + FRAME_OFF(0)))
#define try_level (*(i32 *)(frame_ + FRAME_OFF(1808)))
void __cdecl destroyed_civs_show(iptr killer_civ)

{
  int created;
  i8 frame_[FRAME_OFF(1816)] __attribute__((aligned(8)));  /* original stack frame */
  
  try_level = 0xffffffff;
  (*(i32 *)((char *)&window + 1804)) = &LAB_00514efe;
  destroyed_civs_wnd_ctor((DestroyedCivsWindow *)window);
  try_level = 0;
  created = destroyed_civs_wnd_create((DestroyedCivsWindow *)window,killer_civ);
  if (created == 0) {
    try_level = 0xffffffff;
    /* inlined unwind funclet 00514ef2 */ { destroyed_civs_wnd_dtor((DestroyedCivsWindowCore *)((iptr)&window)); }
  }
  else {
    destroyed_civs_run((DestroyedCivsWindow *)window);
    try_level = 0xffffffff;
    /* inlined unwind funclet 00514ef2 */ { destroyed_civs_wnd_dtor((DestroyedCivsWindowCore *)((iptr)&window)); }
  }
  return;
}
#undef window
#undef try_level

/* 00514f16 auto */
#define victory_screen_wnd (*(DestroyedCivsWindow * *)((u8 *)&g.d_00631a98))
#define seh_next (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define try_level (*(i32 *)(frame_ + FRAME_OFF(8)))
DestroyedCivsWindow * __thiscall destroyed_civs_wnd_ctor(DestroyedCivsWindow *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  try_level = 0xffffffff;
  wnd_ctor((ModalMenuWindow *)this);
  try_level = 0;
  palette_init((GamePalette *)&this->control_list);
  (*(i8 *)((char *)&try_level + 0)) = 1;
  surfwnd_ctor((SurfaceWindow *)(this->media_wnd));
  (*(i8 *)((char *)&try_level + 0)) = 2;
  surface_ctor((DibSurface *)(this->civs_art_surface));
  (*(i8 *)((char *)&try_level + 0)) = 3;
  dll_handle_init((DllHandle *)(this->improvement_art_surface));
  (*(i8 *)((char *)&try_level + 0)) = 4;
  sprite_init((Sprite *)(this->panel_sprite));
  (*(i8 *)((char *)&try_level + 0)) = 5;
  sprite_init((Sprite *)(this->portrait_sprite));
  (*(i8 *)((char *)&try_level + 0)) = 6;
  font_init_empty((GameFont *)this->caption_font_2);
  try_level = CONCAT31((*(i32 *)((char *)&try_level + 1)),7);
  this->killer_civ = 0;
  victory_screen_wnd = this;
  this->slide_y = 0;
  SetRect((LPRECT)&this->panel_clip_rect,0xd0,0x39,0x1b1,0x14c);
  font_set_styled((GameFont *)this->caption_font_2,0,0x18,1);
  return this;
}
#undef victory_screen_wnd
#undef seh_next
#undef seh_handler
#undef try_level

/* 005150b9 auto */
#define victory_screen_wnd (*(i32 *)((u8 *)&g.d_00631a98))
#define seh_next (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define try_level (*(int *)(frame_ + FRAME_OFF(8)))
void __thiscall destroyed_civs_wnd_dtor(DestroyedCivsWindowCore *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  (*(i32 *)((char *)&try_level + 1)) = 0;
  (*(i8 *)((char *)&try_level + 0)) = 7;
  dll_handle_free((DllHandle *)(this->art_dll_2));
  victory_screen_wnd = 0;
  (*(i8 *)((char *)&try_level + 0)) = 6;
  /* inlined unwind funclet 0051516a */ { font_destroy((GameFont *)(*(int *)((iptr)&this) + 0x700)); }
  (*(i8 *)((char *)&try_level + 0)) = 5;
  /* inlined unwind funclet 00515179 */ { sprite_destroy((Sprite *)(*(int *)((iptr)&this) + 0x688)); }
  (*(i8 *)((char *)&try_level + 0)) = 4;
  /* inlined unwind funclet 00515188 */ { sprite_destroy((Sprite *)(*(int *)((iptr)&this) + 0x64c)); }
  (*(i8 *)((char *)&try_level + 0)) = 3;
  /* inlined unwind funclet 00515197 */ { dll_free((DllHandle *)(*(int *)((iptr)&this) + 0x648)); }
  (*(i8 *)((char *)&try_level + 0)) = 2;
  /* inlined unwind funclet 005151a6 */ { surface_dtor((DibSurface *)(*(int *)((iptr)&this) + 0x600)); }
  (*(i8 *)((char *)&try_level + 0)) = 1;
  /* inlined unwind funclet 005151b5 */ { surfwnd_dtor((SurfaceWindow *)(*(int *)((iptr)&this) + 0x4ec)); }
  try_level = (uint)(*(i32 *)((char *)&try_level + 1)) << 8;
  /* inlined unwind funclet 005151c4 */ { palette_destroy((GamePalette *)(*(int *)((iptr)&this) + 0xb8)); }
  try_level = 0xffffffff;
  /* inlined unwind funclet 005151d3 */ { wnd_dtor(*(WndBase **)((iptr)&this)); }
  return;
}
#undef victory_screen_wnd
#undef seh_next
#undef seh_handler
#undef try_level

/* 005151f4 auto */
#define destroyed_civs_show_date (*(i32 *)((u8 *)&g.d_00631a9c))
#define entry (*(iptr *)(frame_ + FRAME_OFF(0)))
#define dll_path (*(i8 (*)[128])(frame_ + FRAME_OFF(4)))
#define screen_left (*(int *)(frame_ + FRAME_OFF(132)))
#define screen_top (*(int *)(frame_ + FRAME_OFF(136)))
#define screen_right (*(int *)(frame_ + FRAME_OFF(140)))
#define screen_bottom (*(int *)(frame_ + FRAME_OFF(144)))
#define rect (*(tagRECT *)(frame_ + FRAME_OFF(148)))
i32 __thiscall destroyed_civs_wnd_create(DestroyedCivsWindow *this,uint killer)

{
  int found;
  i32 result;
  i32 width;
  i8 frame_[FRAME_OFF(168)] __attribute__((aligned(8)));  /* original stack frame */
  
  gfx_get_screen_rect((iptr)&screen_left);
  str_clear((iptr)dll_path);
  str_append((iptr)dll_path,(iptr)((u8 *)&g.d_00631aa0));
  found = file_resolve_path((iptr)dll_path);
  if (found == 0) {
    result = 0;
  }
  else {
    dll_handle_load((DllHandle *)(this->improvement_art_surface),(iptr)dll_path);
    this->killer_civ = killer;
    wnd_create_with_handlers
              ((WndBase *)this,(iptr)((u8 *)&g.d_00631aac),0x800,screen_left,screen_top,screen_right - screen_left,
               (screen_bottom - screen_top) + 5,(iptr)((u8 *)&g.d_006a8c00),(iptr)((u8 *)&g.d_006553d8));
    wnd_set_bg_color((WndBase *)this,0);
    wnd_create_with_surface
              ((DibSurface *)(this->media_wnd),(iptr)((u8 *)&g.d_00631ab0),0x800,0,0,0x280,0x1e0,
               (iptr)&this->control_list,(iptr)this);
    wnd_center((WndCenterView *)(this->movie_wnd_base));
    surface_load_gif_resource
              ((DibSurface *)(this->civs_art_surface),0x2711,10,0xec,(iptr)&this->control_list);
    sprite_grab_from_surface
              ((Sprite *)(this->panel_sprite),(iptr)(this->civs_art_surface),8,0,0,0x129,0xad
              );
    surface_load_gif_resource
              ((DibSurface *)(this->civs_art_surface),10000,10,0xec,(iptr)&this->control_list);
    SetRect(&rect,0,0,0x280,0x1e0);
    surface_blit
              ((DibSurface *)(this->civs_art_surface),(iptr)(this->media_wnd),(iptr)&rect
               ,(iptr)&rect);
    SetRect((LPRECT)this->slot_sprites,0xc1,0x173,0x1c0,0x1cd);
    result = surface_height((DibSurface *)(this->civs_art_surface));
    width = surface_width((DibSurface *)(this->civs_art_surface));
    surface_create((DibSurface *)&destroyed_civs_text_bg,width,result);
    surface_blit
              ((DibSurface *)(this->civs_art_surface),(iptr)((u8 *)&g.d_006aad58),(iptr)this->slot_sprites,
               (iptr)this->slot_sprites);
    for (entry = 0;
        (entry < 0xc && ((uint)(byte)(&destroyed_civ_killers)[entry] != (killer & 0xff)));
        entry = entry + 1) {
    }
    destroyed_civs_show_date = 0;
    destroyed_civs_draw_entry((WndBase *)this,entry);
    this->slide_y = 0x133;
    SetRect((LPRECT)&this->slide_rect,0xab,this->slide_y,0x1d4,this->slide_y + 0xad);
    destroyed_civs_slide_step(this,0);
    result = 1;
  }
  return result;
}
#undef destroyed_civs_show_date
#undef entry
#undef dll_path
#undef screen_left
#undef screen_top
#undef screen_right
#undef screen_bottom
#undef rect

/* 00515516 auto */
#define destroyed_civs_show_date (*(i32 *)((u8 *)&g.d_00631a9c))
#define text_line_cursor (*(iptr *)((u8 *)&g.d_00673f14))
#define entry (*(iptr *)(frame_ + FRAME_OFF(0)))
#define text_buf (*(i8 (*)[256])(frame_ + FRAME_OFF(4)))
#define now (*(DWORD *)(frame_ + FRAME_OFF(260)))
#define font2 (*(GameFont *)(frame_ + FRAME_OFF(264)))
#define seh_next (*(i32 *)(frame_ + FRAME_OFF(272)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(276)))
#define try_level (*(i32 *)(frame_ + FRAME_OFF(280)))
void __thiscall destroyed_civs_run(DestroyedCivsWindow *this)

{
  DWORD DVar1;
  int status;
  char *line;
  i32 width;
  i8 frame_[FRAME_OFF(288)] __attribute__((aligned(8)));  /* original stack frame */
  
  try_level = 0xffffffff;
  font_init_empty(&font2);
  try_level = 0;
  wnd_handle_show_raise((WndBase *)this);
  wnd_flush_paint();
  wnd_set_palette((WndBase *)this,(iptr)&this->control_list);
  window_show((WindowObjectView *)(this->media_wnd));
  wnd_flush_paint();
  wnd_set_capture((WndBase *)(this->movie_wnd_base));
  for (entry = 0; entry < 0xc; entry++) {
    if ((&destroyed_civ_killers)[entry] == (char)this->killer_civ) {
      destroyed_civs_draw_entry((WndBase *)this,entry);
      destroyed_civs_show_date = 1;
      destroyed_civs_draw_portrait((PictureFrameWindow *)this,entry);
      DVar1 = timeGetTime();
      snd_play_effect(((uint)(byte)(&destroyed_civ_portraits)[entry] + (uint)map.seed & 7) + 0x53,1,0,0)
      ;
      destroyed_civs_slide_up(this);
      ui_delay_ticks(0x3c);
      do {
        win_flush_pending_msgs();
        now = timeGetTime();
        if (2 < game.multiplayer) {
          net_process_messages((NetSession *)&net_session,1,0);
        }
      } while ((int)(now - DVar1) < 7000);
      destroyed_civs_draw_entry((WndBase *)this,entry);
      destroyed_civs_slide_down(this);
    }
  }
  ui_delay_ticks(0x3c);
  surface_fill((DibSurface *)(this->media_wnd),0);
  SetRect((LPRECT)this->slot_sprites,0,0,0x280,0x1e0);
  gfx_dissolve_blit((iptr)(this->media_wnd),(iptr)this->slot_sprites,4,4);
  surface_load_gif_resource
            ((DibSurface *)(this->media_wnd),0x2712,10,0xec,(iptr)&this->control_list);
  text_set_font((iptr)this->caption_font_2);
  text_set_colors(0x7c,0x81,1,1);
  text_clear();
  str_clear((iptr)text_buf);
  status = text_open_section((iptr)((u8 *)&g.d_006558e8),(iptr)((u8 *)&g.d_00631ab4));
  if (status == 0) {
    while (line = (char *)text_read_line(1), *line != '@') {
      str_append((iptr)text_buf,text_line_cursor);
      str_append((iptr)text_buf,(iptr)((u8 *)&g.d_00631abc));
    }
    text_draw_centered((iptr)(this->media_wnd),(iptr)text_buf,0,0x48,0x280);
  }
  gfx_dissolve_blit((iptr)(this->media_wnd),(iptr)this->slot_sprites,4,3);
  text_clear();
  text_append_label(0x1c8);
  font_set_styled(&font2,0,0x10,3);
  text_set_font((iptr)&font2);
  width = 0x280;
  status = font_line_spacing(&font2);
  text_draw_centered((iptr)(this->media_wnd),(iptr)((u8 *)&g.d_00679640),0,0x1dc - status,width);
  wnd_blit_surface_rect((DibSurface *)(this->media_wnd),(iptr)this->slot_sprites);
  wnd_set_keydown_handler((WndEventHandlers *)(this->destroyed_civs_handlers),(iptr)victory_screen_on_key);
  wnd_set_lbuttonup_handler((WndEventHandlers *)(this->destroyed_civs_handlers),(iptr)victory_screen_on_click);
  if (2 < game.multiplayer) {
    wnd_set_modal_idle_callback((ModalMenuWindow *)(this->movie_wnd_base),(iptr)net_modal_idle_poll);
  }
  wnd_run_modal_loop((ModalMenuWindow *)(this->movie_wnd_base));
  wnd_set_modal_idle_callback((ModalMenuWindow *)(this->movie_wnd_base),0);
  wnd_release_capture((WndBase *)(this->movie_wnd_base));
  wnd_hide((WndBase *)(this->movie_wnd_base));
  wnd_flush_paint();
  wnd_set_palette((WndBase *)this,(iptr)((u8 *)&g.d_006a8c00));
  wnd_hide((WndBase *)this);
  wnd_flush_paint();
  try_level = 0xffffffff;
  /* inlined unwind funclet 00515978 */ { font_destroy((GameFont *)((iptr)&font2)); }
  return;
}
#undef destroyed_civs_show_date
#undef text_line_cursor
#undef entry
#undef text_buf
#undef now
#undef font2
#undef seh_next
#undef seh_handler
#undef try_level

/* 00515999 auto */
#define destroyed_civs_show_date (*(int *)((u8 *)&g.d_00631a9c))
void __thiscall destroyed_civs_draw_entry(WndBase *this,iptr entry)

{
  iptr label;
  i32 year;
  
  if (destroyed_civs_show_date == 0) {
    surface_blit
              ((DibSurface *)&destroyed_civs_text_bg,(iptr)(this + 0x60),(iptr)&((PictureFrameWindow *)this)->slot_sprites,
               (iptr)&((PictureFrameWindow *)this)->slot_sprites);
    text_clear();
    text_append((iptr)(&destroyed_civ_names + entry * 0x18));
    gfx_set_text_color_index(0x21);
    OffsetRect((LPRECT)&((PictureFrameWindow *)this)->slot_sprites,1,1);
    surface_draw_text_rect
              ((DibSurface *)(this + 0x60),(iptr)(this + 0x70),(iptr)((u8 *)&g.d_00679640),(iptr)&((PictureFrameWindow *)this)->slot_sprites
               ,0);
    gfx_set_text_color_index(0x10);
    OffsetRect((LPRECT)&((PictureFrameWindow *)this)->slot_sprites,-1,-1);
    surface_draw_text_rect
              ((DibSurface *)(this + 0x60),(iptr)(this + 0x70),(iptr)((u8 *)&g.d_00679640),(iptr)&((PictureFrameWindow *)this)->slot_sprites
               ,0);
  }
  else {
    surface_blit
              ((DibSurface *)&destroyed_civs_text_bg,(iptr)(this + 0x60),(iptr)&((PictureFrameWindow *)this)->slot_sprites,
               (iptr)&((PictureFrameWindow *)this)->slot_sprites);
    text_clear();
    text_append((iptr)(&destroyed_civ_names + entry * 0x18));
    text_append_colon();
    text_append_space();
    label = label_string(*(i32 *)(label_string_ids + 0x71c));
    text_append(label);
    text_append_space();
    year = game_turn_to_year((int)*(short *)(&destroyed_civ_turns + entry * 2));
    text_append_year(year);
    gfx_set_text_color_index(0x21);
    OffsetRect((LPRECT)&((PictureFrameWindow *)this)->slot_sprites,1,1);
    surface_draw_text_rect
              ((DibSurface *)(this + 0x60),(iptr)(this + 0x70),(iptr)((u8 *)&g.d_00679640),(iptr)&((PictureFrameWindow *)this)->slot_sprites
               ,0);
    gfx_set_text_color_index(0x10);
    OffsetRect((LPRECT)&((PictureFrameWindow *)this)->slot_sprites,-1,-1);
    surface_draw_text_rect
              ((DibSurface *)(this + 0x60),(iptr)(this + 0x70),(iptr)((u8 *)&g.d_00679640),(iptr)&((PictureFrameWindow *)this)->slot_sprites
               ,0);
    surface_blit
              ((DibSurface *)(this + 0x60),(iptr)&((PictureFrameWindow *)this)->media_wnd,(iptr)&((PictureFrameWindow *)this)->slot_sprites,
               (iptr)&((PictureFrameWindow *)this)->slot_sprites);
    wnd_blit_surface_rect
              ((DibSurface *)&((PictureFrameWindow *)this)->media_wnd,(iptr)&((PictureFrameWindow *)this)->slot_sprites);
    destroyed_civs_show_date = 0;
  }
  surface_blit
            ((DibSurface *)(this + 0x60),(iptr)&((PictureFrameWindow *)this)->media_wnd,(iptr)&((PictureFrameWindow *)this)->slot_sprites,
             (iptr)&((PictureFrameWindow *)this)->slot_sprites);
  return;
}
#undef destroyed_civs_show_date

/* 00515c15 auto */
#define draw_tmp (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define portrait_surface (*(DibSurface *)(frame_ + FRAME_OFF(20)))
#define rgb_buf (*(i8 (*)[192])(frame_ + FRAME_OFF(92)))
#define palette (*(GamePalette *)(frame_ + FRAME_OFF(284)))
#define seh_next (*(i32 *)(frame_ + FRAME_OFF(1360)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(1364)))
#define try_level (*(int *)(frame_ + FRAME_OFF(1368)))
void __thiscall destroyed_civs_draw_portrait(PictureFrameWindow *this,iptr entry)

{
  i8 frame_[FRAME_OFF(1376)] __attribute__((aligned(8)));  /* original stack frame */
  
  try_level = 0xffffffff;
  surface_ctor(&portrait_surface);
  try_level = 0;
  palette_init(&palette);
  (*(i8 *)((char *)&try_level + 0)) = 1;
  surface_blit
            ((DibSurface *)(this->civs_art_surface),(iptr)((u8 *)&this->media_wnd),
             (iptr)&this->panel_clip_rect,(iptr)&this->panel_clip_rect);
  surface_load_gif_resource
            (&portrait_surface,(byte)(&destroyed_civ_portraits)[entry] + 0xdc,10,0xec,(iptr)&palette);
  palette_get_rgb(&palette,(iptr)rgb_buf,0x2a,0x40);
  palette_set_rgb((GamePalette *)&this->control_list,0x2a,0x40,(iptr)rgb_buf);
  surface_set_palette(&portrait_surface,(iptr)&this->control_list);
  sprite_grab_from_surface
            ((Sprite *)(this->portrait_sprite),(iptr)&portrait_surface,9,1,1,0xe1,0x113);
  sprite_draw
            ((Sprite *)(this->portrait_sprite),(iptr)draw_tmp,(iptr)((u8 *)&this->media_wnd),
             0xd0,0x39);
  SetRect((LPRECT)&this->panel_clip_rect,0xd0,0x39,0x1b1,0x14c);
  try_level = (uint)(*(i32 *)((char *)&try_level + 1)) << 8;
  /* inlined unwind funclet 00515d96 */ { palette_destroy((GamePalette *)((iptr)&palette)); }
  try_level = 0xffffffff;
  /* inlined unwind funclet 00515da2 */ { surface_dtor((DibSurface *)((iptr)&portrait_surface)); }
  return;
}
#undef draw_tmp
#undef portrait_surface
#undef rgb_buf
#undef palette
#undef seh_next
#undef seh_handler
#undef try_level

/* 00515dc8 auto */
#define draw_tmp2 (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define draw_tmp1 (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
#define gap_left (*(u32 *)(frame_ + FRAME_OFF(36)))
#define gap_top (*(u32 *)(frame_ + FRAME_OFF(40)))
#define gap_right (*(u32 *)(frame_ + FRAME_OFF(44)))
#define gap_bottom (*(int *)(frame_ + FRAME_OFF(48)))
#define dirty_left (*(u32 *)(frame_ + FRAME_OFF(52)))
#define dirty_top (*(u32 *)(frame_ + FRAME_OFF(56)))
#define dirty_right (*(u32 *)(frame_ + FRAME_OFF(60)))
#define dirty_bottom (*(u32 *)(frame_ + FRAME_OFF(64)))
void __thiscall destroyed_civs_slide_step(DestroyedCivsWindow *this,int delta)

{
  i8 frame_[FRAME_OFF(72)] __attribute__((aligned(8)));  /* original stack frame */
  
  dirty_left = this->slide_rect;
  dirty_top = this->slide_top;
  dirty_right = this->slide_right;
  dirty_bottom = this->resource_dll;
  if (delta < 0) {
    dirty_top -= delta;
  }
  else {
    dirty_bottom += delta;
  }
  surface_blit
            ((DibSurface *)(this->civs_art_surface),(iptr)(this->media_wnd),(iptr)&dirty_left,
             (iptr)&dirty_left);
  sprite_draw
            ((Sprite *)(this->portrait_sprite),(iptr)draw_tmp1,(iptr)(this->media_wnd),
             0xd0,0x39);
  if (0 < delta) {
    gap_left = this->panel_clip_rect;
    gap_right = this->panel_clip_right;
    gap_top = this->slide_y;
    gap_bottom = this->slide_y + delta;
    surface_blit
              ((DibSurface *)(this->civs_art_surface),(iptr)(this->media_wnd),(iptr)&gap_left
               ,(iptr)&gap_left);
  }
  sprite_draw
            ((Sprite *)(this->panel_sprite),(iptr)draw_tmp2,(iptr)(this->media_wnd),
             0xab,this->slide_y + delta);
  OffsetRect((LPRECT)&this->slide_rect,0,delta);
  if ((int)dirty_top < 1) {
    dirty_top = 0;
  }
  wnd_blit_surface_rect((DibSurface *)(this->media_wnd),(iptr)&dirty_left);
  this->slide_y += delta;
  return;
}
#undef draw_tmp2
#undef draw_tmp1
#undef gap_left
#undef gap_top
#undef gap_right
#undef gap_bottom
#undef dirty_left
#undef dirty_top
#undef dirty_right
#undef dirty_bottom

/* 00515f3c auto */
#define start_time (*(DWORD *)(frame_ + FRAME_OFF(0)))
void __thiscall destroyed_civs_slide_down(DestroyedCivsWindow *this)

{
  DWORD DVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  surface_blit
            ((DibSurface *)(this->civs_art_surface),(iptr)(this->media_wnd),
             (iptr)&this->panel_clip_rect,(iptr)&this->panel_clip_rect);
  snd_wave_stop_all();
  snd_play_effect(0x6f,1,0,0);
  DVar1 = timeGetTime();
  while (start_time = DVar1, (int)this->slide_y < 0x133) {
    destroyed_civs_slide_step(this,0xf);
    do {
      win_flush_pending_msgs();
      DVar1 = timeGetTime();
      if (2 < game.multiplayer) {
        net_process_messages((NetSession *)&net_session,1,0);
      }
    } while ((int)(DVar1 - start_time) < 0x16);
  }
  return;
}
#undef start_time

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
void __cdecl victory_screen_on_key(int key)

{
  if ((0xcf < key) && (key < 0xd3)) {
    wnd_end_modal_loop((ModalMenuWindow *)(victory_screen_wnd + 0x534));
  }
  return;
}
#undef victory_screen_wnd

/* 00516570 auto */
#define council_active (*(i8 *)((u8 *)&g.d_00631ad0))
#define council (*(ListPaneWindow (*)[17])(frame_ + FRAME_OFF(0)))
#define seh_next (*(i32 *)(frame_ + FRAME_OFF(4904)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4908)))
#define try_level (*(i32 *)(frame_ + FRAME_OFF(4912)))
void __cdecl council_show(iptr civ,i32 cheat_mode)

{
  int ok;
  i32 ret_addr;
  i8 frame_[FRAME_OFF(4920)] __attribute__((aligned(8)));  /* original stack frame */
  
  try_level = 0xffffffff;
  council_active = 1;
  council_wnd_ctor(council);
  try_level = 0;
  snd_cd_stop();
  ret_addr = 0x5165c6;
  ok = council_wnd_init(council,civ,cheat_mode);
  if (ok != 0) {
    council_wnd_run_modal(council);
  }
  snd_sync_music_option();
  council_active = 0;
  try_level = 0xffffffff;
  /* inlined unwind funclet 005165f6 */ { council_wnd_dtor((CouncilWindow *)((iptr)&council)); }
  return;
}
#undef council_active
#undef council
#undef seh_next
#undef seh_handler
#undef try_level

/* 0051661a auto */
#define seh_next (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define try_level (*(i32 *)(frame_ + FRAME_OFF(8)))
ListPaneWindow * __thiscall council_wnd_ctor(ListPaneWindow *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  try_level = 0xffffffff;
  surfwnd_ctor((SurfaceWindow *)this);
  try_level = 0;
  mmwnd_ctor((DocumentWindow *)&this->style_flags);
  (*(i8 *)((char *)&try_level + 0)) = 1;
  dialog_ctor((Dialog *)&((PictureWindow *)this)->council_dialog,0x4000);
  (*(i8 *)((char *)&try_level + 0)) = 2;
  dll_handle_init((DllHandle *)(((PictureWindow *)this)->council_dll_handle));
  (*(i8 *)((char *)&try_level + 0)) = 3;
  button_ctor((Control *)(this + 0x10));
  (*(i8 *)((char *)&try_level + 0)) = 4;
  button_ctor((Control *)&((PictureWindow *)this)->advisor_button_4);
  (*(i8 *)((char *)&try_level + 0)) = 5;
  button_ctor((Control *)((u8 *)&((PictureWindow *)this)->advisor_button_3));
  (*(i8 *)((char *)&try_level + 0)) = 6;
  button_ctor((Control *)((u8 *)&((PictureWindow *)this)->advisor_button_2));
  (*(i8 *)((char *)&try_level + 0)) = 7;
  button_ctor((Control *)((u8 *)&((PictureWindow *)this)->advisor_button_0));
  try_level = CONCAT31((*(i32 *)((char *)&try_level + 1)),8);
  button_ctor((Control *)&((PictureWindow *)this)->council_close_button);
  this->vtable = (u32)&PTR_FUN_0061d6d8;
  ((PictureWindow *)this)->speech_line_y[0] = 0xb0;
  ((PictureWindow *)this)->speech_line_y_b1[0] = '\0';
  ((PictureWindow *)this)->speech_line_y_b2[0] = '\0';
  ((PictureWindow *)this)->speech_line_y_b3[0] = '\0';
  ((PictureWindow *)this)->council_active_2 = 0;
  council_wnd = (iptr)this;
  return this;
}
#undef seh_next
#undef seh_handler
#undef try_level

/* 005167d9 auto */
#define seh_next (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define try_level (*(int *)(frame_ + FRAME_OFF(8)))
void __thiscall council_wnd_dtor(CouncilWindow *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  *(i8 ***)this->window_base = &PTR_FUN_0061d6d8;
  (*(i32 *)((char *)&try_level + 1)) = 0;
  council_wnd = 0;
  (*(i8 *)((char *)&try_level + 0)) = 8;
  /* inlined unwind funclet 0051689f */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x12ec)); }
  (*(i8 *)((char *)&try_level + 0)) = 7;
  /* inlined unwind funclet 005168ae */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x12b0)); }
  (*(i8 *)((char *)&try_level + 0)) = 6;
  /* inlined unwind funclet 005168bd */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x1274)); }
  (*(i8 *)((char *)&try_level + 0)) = 5;
  /* inlined unwind funclet 005168cc */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x1238)); }
  (*(i8 *)((char *)&try_level + 0)) = 4;
  /* inlined unwind funclet 005168db */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x11fc)); }
  (*(i8 *)((char *)&try_level + 0)) = 3;
  /* inlined unwind funclet 005168ea */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x11c0)); }
  (*(i8 *)((char *)&try_level + 0)) = 2;
  /* inlined unwind funclet 005168f9 */ { dll_free((DllHandle *)(*(int *)((iptr)&this) + 0xe30)); }
  (*(i8 *)((char *)&try_level + 0)) = 1;
  /* inlined unwind funclet 00516908 */ { dialog_dtor((Dialog *)(*(int *)((iptr)&this) + 0xb3c)); }
  try_level = (uint)(*(i32 *)((char *)&try_level + 1)) << 8;
  /* inlined unwind funclet 00516917 */ { avi_player_dtor((AviPlayer *)(*(int *)((iptr)&this) + 0x114)); }
  try_level = 0xffffffff;
  /* inlined unwind funclet 00516926 */ { surfwnd_dtor(*(SurfaceWindow **)((iptr)&this)); }
  return;
}
#undef seh_next
#undef seh_handler
#undef try_level

/* 00516947 auto */
#define dlg_help_pressed (*(int *)((u8 *)&g.d_00631edc))
#define frame_border_width (*(int *)((u8 *)&g.d_0063359c))
#define frame_caption_height (*(int *)((u8 *)&g.d_00633598))
#define advisor (*(int *)(frame_ + FRAME_OFF(0)))
#define number (*(int *)(frame_ + FRAME_OFF(4)))
#define avi_path (*(i8 (*)[128])(frame_ + FRAME_OFF(8)))
#define open_err (*(int *)(frame_ + FRAME_OFF(136)))
i32 __thiscall council_wnd_init(ListPaneWindow *this,u32 civ,int cheat_mode)

{
  bool valid;
  i32 result;
  int cancelled;
  int choice;
  i8 frame_[FRAME_OFF(144)] __attribute__((aligned(8)));  /* original stack frame */
  
  ((PictureWindow *)this)->council_civ = civ;
  result = civ_city_art_era(((PictureWindow *)this)->council_civ);
  *(i32 *)((PictureWindow *)this)->pedia_terrain_ids_2 = result;
  wnd_create_with_surface
            ((DibSurface *)this,(iptr)((u8 *)&g.d_00631ad4),0xc02,0,0,frame_border_width * 6 + 0x1c2,
             frame_caption_height * 2 + frame_bevel_width + 0xfc,(iptr)((u8 *)&g.d_006ab6a8),(iptr)((u8 *)&g.d_006553d8));
  wnd_set_caption_height((WndBase *)this->window_2,frame_caption_height);
  ui_set_button_font((iptr)((u8 *)&g.d_006cec90));
  council_create_buttons((DibSurface *)this);
  council_draw_background((DibSurface *)this);
  wnd_repaint((SurfaceWindow *)this);
  for (advisor = 0; advisor < 5; advisor++) {
    result = council_advisor_opinion(((PictureWindow *)this)->council_civ,advisor);
    *(i32 *)(((PictureWindow *)this)->pedia_terrain_ids_2 + advisor * 4 + 4) = result;
  }
  if (cheat_mode != 0) {
    while( true ) {
      cancelled = popup_game((iptr)((u8 *)&g.d_00631ad8));
      choice = dlg_help_pressed;
      if ((cancelled != 0) || (dlg_help_pressed == 0)) goto LAB_00516b87;
      if (dlg_help_pressed == 6) break;
      valid = false;
      while (!valid) {
        cancelled = dlg_input_number_game((iptr)((u8 *)&g.d_00631ae8),0,(iptr)&number);
        if (cancelled != 0) {
          return 0;
        }
        if (((0 < number) && (number < 8)) && ((choice != 5 || (number < 7)))) {
          *(int *)(((PictureWindow *)this)->pedia_terrain_ids_2 + choice * 4) = number;
          valid = true;
        }
      }
    }
    ((PictureWindow *)this)->council_active_2 = 1;
LAB_00516b87:
    valid = false;
    while ((!valid && (choice = dlg_input_number_game((iptr)((u8 *)&g.d_00631af8),0,(iptr)&number), choice == 0))) {
      if ((-1 < number) && (number < 3)) {
        *(int *)((PictureWindow *)this)->pedia_terrain_ids_2 = number;
        valid = true;
      }
    }
  }
  if (civs[((PictureWindow *)this)->council_civ].government == '\0') {
    ((PictureWindow *)this)->council_active_2 = 1;
  }
  else {
    for (advisor = 0; advisor < 5; advisor++) {
      str_clear((iptr)(((PictureWindow *)this)->advisor_code_slots + advisor * 3 - 0x40));
    }
    str_append((iptr)&((PictureWindow *)this)->advisor_codes,(iptr)((u8 *)&g.d_00631b08));
    str_append((iptr)((int)&((PictureWindow *)this)->advisor_codes + 3),(iptr)((u8 *)&g.d_00631b0c));
    str_append((iptr)((int)&((PictureWindow *)this)->advisor_codes_part2 + 2),(iptr)((u8 *)&g.d_00631b10));
    str_append((iptr)((int)&((PictureWindow *)this)->advisor_codes_part3 + 1),(iptr)((u8 *)&g.d_00631b14));
    str_append((iptr)&((PictureWindow *)this)->advisor_codes_part4,(iptr)((u8 *)&g.d_00631b18));
    for (advisor = 0; advisor < 5; advisor++) {
      str_append_int((iptr)(((PictureWindow *)this)->advisor_code_slots + advisor * 3 - 0x40),
                         *(i32 *)(((PictureWindow *)this)->pedia_terrain_ids_2 + advisor * 4 + 4));
    }
  }
  if (((PictureWindow *)this)->council_active_2 != 0) {
    ctrl_disable((Control *)(this + 0x10));
    ctrl_disable((Control *)&((PictureWindow *)this)->advisor_button_4);
    ctrl_disable((Control *)((u8 *)&((PictureWindow *)this)->advisor_button_3));
    ctrl_disable((Control *)((u8 *)&((PictureWindow *)this)->advisor_button_2));
    ctrl_disable((Control *)((u8 *)&((PictureWindow *)this)->advisor_button_0));
  }
  str_clear((iptr)(((PictureWindow *)this)->council_text_file));
  text_clear();
  if (((PictureWindow *)this)->council_active_2 == 0) {
    text_append((iptr)((u8 *)&g.d_00631b1c));
  }
  else {
    text_append((iptr)((u8 *)&g.d_00631b24));
  }
  text_append_int(*(iptr *)((PictureWindow *)this)->pedia_terrain_ids_2);
  str_append((iptr)(((PictureWindow *)this)->council_text_file),(iptr)((u8 *)&g.d_00679640));
  if ((((PictureWindow *)this)->council_active_2 == 0) &&
     (choice = council_load_speech((WindowObjectView *)this,0), choice == 0)) {
    result = 0;
  }
  else {
    dialog_init
              ((Dialog *)&((PictureWindow *)this)->council_dialog,(iptr)this,(iptr)this,
               (iptr)((u8 *)&((PictureWindow *)this)->speech_rect),0x84008);
    avi_player_create_child((MediaWindow *)&this->style_flags,(iptr)((u8 *)&g.d_00631b2c),0x200,0,0,(iptr)this);
    str_clear((iptr)avi_path);
    str_append((iptr)avi_path,(iptr)((u8 *)&g.d_00631b30));
    str_append((iptr)avi_path,(iptr)(((PictureWindow *)this)->council_text_file));
    str_append((iptr)avi_path,(iptr)((u8 *)&g.d_00631b3c));
    choice = file_resolve_path((iptr)avi_path);
    if (choice == 0) {
      result = 0;
    }
    else {
      open_err = avi_player_open((AviPlayerOpenView *)&this->style_flags,(iptr)avi_path);
      if (open_err == 0) {
        avi_player_set_palette((DibSurface *)&this->style_flags,(iptr)((u8 *)&g.d_006ab6a8));
        wnd_set_palette((WndBase *)&((ParleyWindowLayout *)this)->parley_title,(iptr)((u8 *)&g.d_006ab6a8));
        avi_player_set_end_callback((AviPlayerEndCbSetView *)&this->style_flags,(iptr)council_on_video_end);
        council_draw_advisor_frames(this);
        result = 1;
      }
      else {
        if (open_err == -0x7ffbfeac) {
          popup_game((iptr)((u8 *)&g.d_00631b44));
        }
        result = 0;
      }
    }
  }
  return result;
}
#undef dlg_help_pressed
#undef frame_border_width
#undef frame_caption_height
#undef advisor
#undef number
#undef avi_path
#undef open_err

/* 00516fd4 auto */
#define frame_border_width (*(int *)((u8 *)&g.d_0063359c))
#define frame_caption_height (*(int *)((u8 *)&g.d_00633598))
void __thiscall council_wnd_run_modal(ListPaneWindow *this)

{
  dlg_set_palette((iptr)((u8 *)&g.d_006ab6a8));
  screen_fade_out();
  wnd_set_palette((WndBase *)&main_frame_wnd,(iptr)((u8 *)&g.d_006ab6a8));
  wnd_center((WndCenterView *)this->window_2);
  ctrl_show_and_redraw((Control *)&((PictureWindow *)this)->advisor_button_4);
  ctrl_show_and_redraw((Control *)((u8 *)&((PictureWindow *)this)->advisor_button_3));
  ctrl_show_and_redraw((Control *)((u8 *)&((PictureWindow *)this)->advisor_button_0));
  ctrl_show_and_redraw((Control *)((u8 *)&((PictureWindow *)this)->advisor_button_2));
  ctrl_show_and_redraw((Control *)(this + 0x10));
  ctrl_show_and_redraw((Control *)&((PictureWindow *)this)->council_close_button);
  dlg_show_modal((Dialog *)&((PictureWindow *)this)->council_dialog,0);
  window_show((WindowObjectView *)this);
  wnd_flush_paint();
  if (((PictureWindow *)this)->council_active_2 != 0) {
    wnd_move_xy
              ((WndMoveView *)&((ParleyWindowLayout *)this)->parley_title,frame_border_width + 1,frame_caption_height + 1);
    window_show((WindowObjectView *)&this->style_flags);
    wnd_flush_paint();
    avi_player_play((AviPlayerPlayView *)&this->style_flags);
  }
  if (2 < game.multiplayer) {
    wnd_set_modal_idle_callback((ModalMenuWindow *)this->window_2,(iptr)net_modal_idle_poll);
  }
  wnd_run_modal_loop((ModalMenuWindow *)this->window_2);
  wnd_set_modal_idle_callback((ModalMenuWindow *)this->window_2,0);
  snd_wave_stop_all();
  council_draw_background((DibSurface *)this);
  wnd_hide((WndBase *)this->window_2);
  wnd_flush_paint();
  dialog_close((Dialog *)&((PictureWindow *)this)->council_dialog);
  wnd_set_palette((WndBase *)&main_frame_wnd,(iptr)((u8 *)&g.d_006a8c00));
  screen_fade_in();
  dlg_set_palette((iptr)((u8 *)&g.d_006a8c00));
  return;
}
#undef frame_border_width
#undef frame_caption_height

/* 00517158 auto */
#define frame_border_width (*(int *)((u8 *)&g.d_0063359c))
#define frame_caption_height (*(int *)((u8 *)&g.d_00633598))
#define i (*(int *)(frame_ + FRAME_OFF(0)))
#define panel_x (*(int *)(frame_ + FRAME_OFF(4)))
#define j (*(int *)(frame_ + FRAME_OFF(8)))
#define rect (*(tagRECT *)(frame_ + FRAME_OFF(12)))
void __thiscall council_draw_background(DibSurface *this)

{
  int extent;
  i32 size;
  int offset;
  int inner_top;
  RECT *lprcSrc;
  iptr str;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  extent = frame_caption_height + frame_bevel_width * -2;
  size = surface_get_width(this);
  gfx_tile_fill((iptr)this,(iptr)((u8 *)&g.d_006abae0),0,frame_bevel_width,size,extent,0,frame_bevel_width);
  offset = frame_bevel_width + frame_caption_height + 0x7a;
  gfx_tile_fill((iptr)this,(iptr)((u8 *)&g.d_006abae0),0,offset,size,extent,0,offset);
  extent = surface_get_height(this);
  extent -= (frame_bevel_width + 0x1e);
  gfx_tile_fill((iptr)this,(iptr)((u8 *)&g.d_006abae0),0,extent,size,0x1e,0,extent);
  size = surface_get_height(this);
  offset = frame_border_width + frame_bevel_width * -2;
  gfx_tile_fill((iptr)this,(iptr)((u8 *)&g.d_006abae0),frame_bevel_width,0,offset,size,frame_bevel_width,0);
  extent = surface_get_width(this);
  extent -= (frame_bevel_width + offset);
  gfx_tile_fill((iptr)this,(iptr)((u8 *)&g.d_006abae0),extent,0,offset,size,extent,0);
  extent = frame_bevel_width * 2;
  panel_x = frame_bevel_width + frame_border_width + 0x5a;
  inner_top = frame_caption_height - frame_bevel_width;
  for (i = 0; i < 4; i++) {
    gfx_tile_fill((iptr)this,(iptr)((u8 *)&g.d_006abae0),panel_x,inner_top,offset,extent + 0x7a,panel_x,inner_top);
    panel_x = panel_x + frame_border_width + 0x5a;
  }
  SetRect(&rect,frame_border_width - frame_bevel_width,inner_top,
          frame_bevel_width * 2 + (frame_border_width - frame_bevel_width) + 0x5a,frame_bevel_width * 2 + inner_top + 0x7a);
  for (i = 0; i < 5; i++) {
    for (j = 0; j < frame_bevel_width; j++) {
      gfx_draw_bevel_rect((iptr)this,(iptr)&rect,frame_shadow_color,frame_highlight_color);
      InflateRect(&rect,-1,-1);
    }
    surface_fill_rect(this,(iptr)&rect,10);
    InflateRect(&rect,frame_bevel_width,frame_bevel_width);
    OffsetRect(&rect,frame_border_width + 0x5a,0);
  }
  extent = surface_get_height(this);
  extent = (extent - 0x1e) - frame_bevel_width;
  offset = surface_get_width(this);
  offset = (offset - frame_border_width) + frame_bevel_width;
  inner_top = surface_get_height(this);
  SetRect((LPRECT)&((PictureWindow *)this)->speech_rect,frame_border_width - frame_bevel_width,inner_top - 0x82 + frame_bevel_width * -3
          ,offset,extent);
  for (j = 0; j < frame_bevel_width; j++) {
    gfx_draw_bevel_rect((iptr)this,(iptr)&((PictureWindow *)this)->speech_rect,frame_shadow_color,frame_highlight_color);
    InflateRect((LPRECT)&((PictureWindow *)this)->speech_rect,-1,-1);
  }
  surface_fill_rect(this,(iptr)&((PictureWindow *)this)->speech_rect,0x1d);
  InflateRect((LPRECT)&((PictureWindow *)this)->speech_rect,-2,-2);
  lprcSrc = (RECT *)surface_get_rect(this);
  CopyRect(&rect,lprcSrc);
  for (j = 0; j < frame_bevel_width; j++) {
    gfx_draw_bevel_rect((iptr)this,(iptr)&rect,frame_highlight_color,frame_shadow_color);
    InflateRect(&rect,-1,-1);
  }
  text_clear();
  if (game_language == 1) {
    str = label_string(*(i32 *)(label_string_ids + 0x4ac));
    text_append(str);
    text_append_space();
    str = civ_get_adjective(((PictureWindow *)this)->council_civ);
    text_append(str);
  }
  else {
    str = civ_get_adjective(((PictureWindow *)this)->council_civ);
    text_append(str);
    if (game_language == 2) {
      text_append((iptr)((u8 *)&g.d_00631b58));
    }
    text_append_space();
    str = label_string(*(i32 *)(label_string_ids + 0x4ac));
    text_append(str);
  }
  offset = surface_get_width(this);
  inner_top = font_text_width((GameFont *)&caption_font,(iptr)((u8 *)&g.d_00679640));
  extent = frame_bevel_width;
  offset = (offset - inner_top) / 2;
  inner_top = frame_bevel_width + 1;
  gfx_set_text_color_index(10);
  surface_draw_text(this,(iptr)((u8 *)&g.d_006ab190),(iptr)((u8 *)&g.d_00679640),offset + 1,extent + 2,5);
  gfx_set_text_color_index(0x1a);
  surface_draw_text(this,(iptr)((u8 *)&g.d_006ab190),(iptr)((u8 *)&g.d_00679640),offset,inner_top,5);
  return;
}
#undef frame_border_width
#undef frame_caption_height
#undef i
#undef panel_x
#undef j
#undef rect

/* 00517673 auto */
#define frame_border_width (*(int *)((u8 *)&g.d_0063359c))
#define frame_caption_height (*(int *)((u8 *)&g.d_00633598))
#define parent6 (*(DibSurface * *)(frame_ + FRAME_OFF(4)))
#define parent5 (*(DibSurface * *)(frame_ + FRAME_OFF(8)))
#define parent4 (*(DibSurface * *)(frame_ + FRAME_OFF(12)))
#define parent3 (*(DibSurface * *)(frame_ + FRAME_OFF(16)))
#define parent2 (*(DibSurface * *)(frame_ + FRAME_OFF(20)))
#define parent1 (*(DibSurface * *)(frame_ + FRAME_OFF(24)))
#define rect (*(tagRECT *)(frame_ + FRAME_OFF(36)))
void __thiscall council_create_buttons(DibSurface *this)

{
  int y;
  iptr label;
  int right;
  int height;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  y = (frame_caption_height - 0x16 >> 1) + frame_caption_height;
  SetRect(&rect,frame_border_width + 7,y + 0x79,frame_border_width + 0x52,y + 0x8f);
  if (this == (DibSurface *)0x0) {
    parent1 = (DibSurface *)0x0;
  }
  else {
    parent1 = this + 1;
  }
  label = label_string(*(i32 *)(label_string_ids + 0x26c));
  button_create_with_callback
            ((Control *)&((PictureWindow *)this)->advisor_button_0,(iptr)parent1,0,(iptr)&rect,0x21,label);
  button_set_callback((Control *)&((PictureWindow *)this)->advisor_button_0,(iptr)council_on_advisor_button);
  OffsetRect(&rect,frame_border_width + 0x5a,0);
  if (this == (DibSurface *)0x0) {
    parent2 = (DibSurface *)0x0;
  }
  else {
    parent2 = this + 1;
  }
  label = label_string(*(i32 *)(label_string_ids + 0x16c));
  button_create_with_callback
            ((Control *)&((PictureWindow *)this)->advisor_button_1,(iptr)parent2,1,(iptr)&rect,0x21,label);
  button_set_callback((Control *)&((PictureWindow *)this)->advisor_button_1,(iptr)council_on_advisor_button);
  OffsetRect(&rect,frame_border_width + 0x5a,0);
  if (this == (DibSurface *)0x0) {
    parent3 = (DibSurface *)0x0;
  }
  else {
    parent3 = this + 1;
  }
  label = label_string(*(i32 *)(label_string_ids + 0x114));
  button_create_with_callback
            ((Control *)&((PictureWindow *)this)->advisor_button_2,(iptr)parent3,2,(iptr)&rect,0x21,label);
  button_set_callback((Control *)&((PictureWindow *)this)->advisor_button_2,(iptr)council_on_advisor_button);
  OffsetRect(&rect,frame_border_width + 0x5a,0);
  if (this == (DibSurface *)0x0) {
    parent4 = (DibSurface *)0x0;
  }
  else {
    parent4 = this + 1;
  }
  label = label_string(*(i32 *)(label_string_ids + 0x6e0));
  button_create_with_callback
            ((Control *)&((PictureWindow *)this)->advisor_button_3,(iptr)parent4,3,(iptr)&rect,0x21,label);
  button_set_callback((Control *)&((PictureWindow *)this)->advisor_button_3,(iptr)council_on_advisor_button);
  OffsetRect(&rect,frame_border_width + 0x5a,0);
  if (this == (DibSurface *)0x0) {
    parent5 = (DibSurface *)0x0;
  }
  else {
    parent5 = this + 1;
  }
  label = label_string(*(i32 *)(label_string_ids + 0x6e4));
  button_create_with_callback
            ((Control *)&((PictureWindow *)this)->advisor_button_4,(iptr)parent5,4,(iptr)&rect,0x21,label);
  button_set_callback((Control *)&((PictureWindow *)this)->advisor_button_4,(iptr)council_on_advisor_button);
  y = surface_get_height(this);
  y = (y - frame_bevel_width) - 1;
  right = surface_get_width(this);
  right -= frame_border_width;
  height = surface_get_height(this);
  SetRect(&rect,frame_border_width,height - 0x1d,right,y);
  if (this == (DibSurface *)0x0) {
    parent6 = (DibSurface *)0x0;
  }
  else {
    parent6 = this + 1;
  }
  label = label_string(*(i32 *)(label_string_ids + 0x3fc));
  button_create_with_callback
            ((Control *)&((PictureWindow *)this)->council_close_button,(iptr)parent6,0xca,(iptr)&rect,0x21,label);
  button_set_callback((Control *)&((PictureWindow *)this)->council_close_button,(iptr)council_on_advisor_button);
  return;
}
#undef frame_border_width
#undef frame_caption_height
#undef parent6
#undef parent5
#undef parent4
#undef parent3
#undef parent2
#undef parent1
#undef rect

/* 005179a3 auto */
#define text_line_cursor (*(char * *)((u8 *)&g.d_00673f14))
#define i (*(iptr *)(frame_ + FRAME_OFF(4)))
#define line_idx (*(iptr *)(frame_ + FRAME_OFF(8)))
#define used_mask (*(uint *)(frame_ + FRAME_OFF(16)))
#define result (*(i32 *)(frame_ + FRAME_OFF(24)))
i32 __thiscall council_load_speech(WindowObjectView *this,uptr advisor)

{
  bool skip_read;
  bool matched;
  int status;
  u32 value;
  i8 *token;
  int roll;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  used_mask = 0;
  result = 0;
  if (4 < (int)advisor) {
    return 0;
  }
  status = text_open_section((iptr)(this + 0x38d),(int)&((PictureWindow *)this)->advisor_codes + advisor * 3);
  if (status != 0) {
    return 0;
  }
  status = text_read_line(1);
  if (status != 0) {
    for (i = 0; i < 5; i++) {
      ((u32 *)&((PictureWindow *)this)->speech_line_advisors)[i] = 0;
    }
    ((PictureWindow *)this)->speech_line_advisors[0] = advisor;
    value = text_next_int();
    ((PictureWindow *)this)->speech_line_values[0] = value;
    value = text_next_int();
    ((PictureWindow *)this)->speech_line_params[0] = value;
    str_clear((iptr)(this + 0x3aa));
    str_trim((iptr)text_line_cursor);
    str_append((iptr)(this + 0x3aa),(iptr)text_line_cursor);
    line_idx = 1;
    matched = true;
    skip_read = false;
LAB_00517ae5:
    if ((2 < line_idx) || (((u32 *)&((PictureWindow *)this)->speech_line_advisors)[line_idx] == 0xffffffff)) goto LAB_00517dae;
    if ((!skip_read) && (status = text_read_line(1), status == 0)) goto LAB_00517db5;
    skip_read = false;
    token = (i8 *)text_next_token();
    switch(*token) {
    case 0x23:
      skip_read = matched;
      goto LAB_00517ae5;
    case 0x3b:
      goto LAB_00517ae5;
    case 0x41:
    case 0x61:
      advisor = 4;
      break;
    case 0x45:
    case 0x65:
      ((u32 *)&((PictureWindow *)this)->speech_line_advisors)[line_idx] = 0xffffffff;
      goto LAB_00517ae5;
    case 0x46:
    case 0x66:
      advisor = 3;
      break;
    case 0x4d:
    case 0x6d:
      advisor = 0;
      break;
    case 0x52:
    case 0x72:
      goto switchD_00517c0c_caseD_52;
    case 0x53:
    case 0x73:
      advisor = 1;
      break;
    case 0x54:
    case 0x74:
      advisor = 2;
    }
    if ((used_mask & 1 << ((byte)advisor & 0x1f)) == 0) {
      if ((token[1] == '\0') || (value = _atoi(token + 1), value == ((u32 *)&((PictureWindow *)this)->advisor_opinions)[advisor])
         ) {
        ((u32 *)&((PictureWindow *)this)->speech_line_advisors)[line_idx] = advisor;
        value = text_next_int();
        ((u32 *)&((PictureWindow *)this)->speech_line_values)[line_idx] = value;
        value = text_next_int();
        ((u32 *)&((PictureWindow *)this)->speech_line_params)[line_idx] = value;
        str_clear((int)this + line_idx * 0xff + 0xea8);
        str_trim((iptr)text_line_cursor);
        if (*text_line_cursor != '*') {
          str_append((int)this + line_idx * 0xff + 0xea8,(iptr)text_line_cursor);
        }
        line_idx++;
        matched = true;
        used_mask = used_mask | 1 << ((byte)advisor & 0x1f);
      }
      else {
        matched = false;
      }
    }
    else {
      matched = false;
    }
    goto LAB_00517ae5;
  }
LAB_00517db5:
  text_close_file();
  return result;
LAB_00517dae:
  result = 1;
  goto LAB_00517db5;
switchD_00517c0c_caseD_52:
  status = _atoi(token + 1);
  roll = rand_range(1,10);
  if (roll <= status) {
    matched = false;
  }
  skip_read = roll > status;
  goto LAB_00517ae5;
}
#undef text_line_cursor
#undef i
#undef line_idx
#undef used_mask
#undef result

/* 00517dd3 auto */
#define font2 (*(GameFont *)(frame_ + FRAME_OFF(0)))
#define rect (*(tagRECT *)(frame_ + FRAME_OFF(8)))
#define seh_next (*(i32 *)(frame_ + FRAME_OFF(24)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(28)))
#define try_level (*(i32 *)(frame_ + FRAME_OFF(32)))
void __thiscall council_draw_speech(SurfaceWindow *this,int mode)

{
  int spacing;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  try_level = 0xffffffff;
  font_init(&font2,0,0xe);
  try_level = 0;
  if ((*(int *)(((PictureWindow *)this)->speech_advisor_index) < 0) || (2 < *(int *)(((PictureWindow *)this)->speech_advisor_index))) {
    try_level = 0xffffffff;
    /* inlined unwind funclet 00517fe4 */ { font_destroy((GameFont *)((iptr)&font2)); }
  }
  else {
    if (mode != 1) {
      surface_fill_rect((DibSurface *)this,(iptr)((u8 *)&((PictureWindow *)this)->speech_rect),0x1d);
      ((PictureWindow *)this)->speech_line_y[0] = 2;
      ((PictureWindow *)this)->speech_line_y_b1[0] = '\0';
      ((PictureWindow *)this)->speech_line_y_b2[0] = '\0';
      ((PictureWindow *)this)->speech_line_y_b3[0] = '\0';
    }
    if (mode == -1) {
      wnd_repaint(this);
      try_level = 0xffffffff;
      /* inlined unwind funclet 00517fe4 */ { font_destroy((GameFont *)((iptr)&font2)); }
    }
    else {
      rect.bottom = *(LONG *)(((PictureWindow *)this)->speech_rect_bottom);
      rect.left = *(int *)((u8 *)&((PictureWindow *)this)->speech_rect) + 2;
      rect.right = *(int *)(((PictureWindow *)this)->speech_rect_right) - 2;
      rect.top = *(int *)(((PictureWindow *)this)->speech_rect_top) + *(int *)(((PictureWindow *)this)->speech_line_y);
      dialog_set_font((DialogTextView *)((u8 *)&((PictureWindow *)this)->council_dialog),(iptr)&font2);
      if (((PictureWindow *)this)->council_speech_lines[*(int *)(((PictureWindow *)this)->speech_advisor_index) * 0xff + 0x5c] != '\0') {
        OffsetRect(&rect,1,1);
        gfx_set_text_color_index(0x25);
        surface_draw_text_rect
                  ((DibSurface *)this,(iptr)&font2,
                   (iptr)(((PictureWindow *)this)->council_speech_lines + *(int *)(((PictureWindow *)this)->speech_advisor_index) * 0xff + 0x5c),
                   (iptr)&rect,1);
        OffsetRect(&rect,-1,-1);
        gfx_set_text_color_index(10);
        surface_draw_text_rect
                  ((DibSurface *)this,(iptr)&font2,
                   (iptr)(((PictureWindow *)this)->council_speech_lines + *(int *)(((PictureWindow *)this)->speech_advisor_index) * 0xff + 0x5c),
                   (iptr)&rect,1);
        spacing = font_line_spacing(&font2);
        *(int *)(((PictureWindow *)this)->speech_line_y) = *(int *)(((PictureWindow *)this)->speech_line_y) + spacing;
        spacing = font_text_width
                          (&font2,
                           (iptr)(((PictureWindow *)this)->council_speech_lines +
                                 *(int *)(((PictureWindow *)this)->speech_advisor_index) * 0xff + 0x5c));
        if (rect.right - rect.left < spacing) {
          spacing = font_line_spacing(&font2);
          *(int *)(((PictureWindow *)this)->speech_line_y) = *(int *)(((PictureWindow *)this)->speech_line_y) + spacing;
        }
      }
      wnd_repaint(this);
      wnd_flush_paint();
      try_level = 0xffffffff;
      /* inlined unwind funclet 00517fe4 */ { font_destroy((GameFont *)((iptr)&font2)); }
    }
  }
  return;
}
#undef font2
#undef rect
#undef seh_next
#undef seh_handler
#undef try_level

/* 00518007 auto */
#define frame_border_width (*(int *)((u8 *)&g.d_0063359c))
#define frame_caption_height (*(int *)((u8 *)&g.d_00633598))
#define advisor (*(int *)(frame_ + FRAME_OFF(0)))
#define surface (*(DibSurface *)(frame_ + FRAME_OFF(4)))
#define sprite (*(Sprite *)(frame_ + FRAME_OFF(76)))
#define seh_next (*(i32 *)(frame_ + FRAME_OFF(136)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(140)))
#define try_level (*(int *)(frame_ + FRAME_OFF(144)))
void __thiscall council_draw_advisor_frames(ListPaneWindow *this)

{
  int status;
  i32 frame_no;
  i8 frame_[FRAME_OFF(152)] __attribute__((aligned(8)));  /* original stack frame */
  
  try_level = 0xffffffff;
  surface_ctor(&surface);
  try_level = 0;
  sprite_init(&sprite);
  (*(i8 *)((char *)&try_level + 0)) = 1;
  if (((PictureWindow *)this)->council_active_2 == 0) {
    for (advisor = 0; advisor < 5; advisor++) {
      status = text_open_section((iptr)(((PictureWindow *)this)->council_text_file),
                                 (iptr)(((PictureWindow *)this)->advisor_code_slots + advisor * 3 - 0x40));
      if (status != 0) {
        try_level = (uint)(*(i32 *)((char *)&try_level + 1)) << 8;
        /* inlined unwind funclet 005181ab */ { sprite_destroy((Sprite *)((iptr)&sprite)); }
        try_level = 0xffffffff;
        /* inlined unwind funclet 005181b4 */ { surface_dtor((DibSurface *)((iptr)&surface)); }
        goto LAB_005181ca;
      }
      status = text_read_line(1);
      if (status == 0) {
        try_level = (uint)(*(i32 *)((char *)&try_level + 1)) << 8;
        /* inlined unwind funclet 005181ab */ { sprite_destroy((Sprite *)((iptr)&sprite)); }
        try_level = 0xffffffff;
        /* inlined unwind funclet 005181b4 */ { surface_dtor((DibSurface *)((iptr)&surface)); }
        goto LAB_005181ca;
      }
      frame_no = text_next_int();
      avi_player_show_frame(&this->style_flags,frame_no);
      avi_player_draw_to
                ((DibSurface *)&this->style_flags,(iptr)this,
                 (frame_border_width + 0x5a) * advisor + frame_border_width + 1,frame_caption_height + 1);
      text_close_file();
    }
  }
  else {
    avi_player_show_frame(&this->style_flags,1);
    avi_player_draw_to
              ((DibSurface *)&this->style_flags,(iptr)this,frame_border_width + 2,frame_caption_height + 2);
  }
  try_level = (uint)(*(i32 *)((char *)&try_level + 1)) << 8;
  /* inlined unwind funclet 005181ab */ { sprite_destroy((Sprite *)((iptr)&sprite)); }
  try_level = 0xffffffff;
  /* inlined unwind funclet 005181b4 */ { surface_dtor((DibSurface *)((iptr)&surface)); }
LAB_005181ca:
  return;
}
#undef frame_border_width
#undef frame_caption_height
#undef advisor
#undef surface
#undef sprite
#undef seh_next
#undef seh_handler
#undef try_level

/* 005181d8 auto */
#define council_video_busy_i32 (*(i32 *)((u8 *)&g.d_00631ac8))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl council_on_advisor_button(uptr button_id)

{
  iptr this;
  int loaded;
  
  this = council_wnd;
  council_video_busy_i32 = 1;
  snd_wave_stop_all();
  avi_player_pause((AviPlayerPauseView *)(this + 0x114));
  if (button_id == 0xca) {
    council_draw_speech((SurfaceWindow *)this,0xffffffff);
    wnd_flush_paint();
    wnd_end_modal_loop((ModalMenuWindow *)(this + 0x48));
  }
  else if (*(int *)(this + 0xe70) == 0) {
    council_draw_speech((SurfaceWindow *)this,0xffffffff);
    *(i32 *)(this + 0x11a8) = 0;
    loaded = council_load_speech((WindowObjectView *)this,button_id);
    if (loaded == 0) {
      council_draw_speech((SurfaceWindow *)this,0xffffffff);
      wnd_flush_paint();
      wnd_end_modal_loop((ModalMenuWindow *)(this + 0x48));
    }
    else {
      wnd_hide((WndBase *)(this + 0x15c));
      council_move_video_to_slot((void *)this,button_id);
      if ((int)button_id < 5) {
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
void __thiscall council_move_video_to_slot(void *this,iptr slot)

{
  if (slot < 5) {
    wnd_move_xy
              ((WndMoveView *)((int)this + 0x15c),(frame_border_width + 0x5a) * slot + frame_border_width + 1,
               frame_caption_height + 1);
  }
  return;
}
#undef frame_border_width
#undef frame_caption_height

/* 00518392 auto */
i32 __thiscall council_advisor_from_letter(void *this,i8 *token)

{
  i32 advisor;
  
  switch(*token) {
  case 0x41:
  case 0x61:
    advisor = 4;
    break;
  default:
    advisor = 0xffffffff;
    break;
  case 0x46:
  case 0x66:
    advisor = 3;
    break;
  case 0x4d:
  case 0x6d:
    advisor = 0;
    break;
  case 0x53:
  case 0x73:
    advisor = 1;
    break;
  case 0x54:
  case 0x74:
    advisor = 2;
  }
  return advisor;
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
#define era (*(i32 *)(frame_ + FRAME_OFF(0)))
i32 __cdecl council_advisor_opinion(iptr civ,i32 advisor)

{
  i32 opinion;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (council_wnd != 0) {
    era = *(i32 *)(council_wnd + 0xe54);
  }
  switch(advisor) {
  case 0:
    opinion = council_military_advice(civ,era);
    break;
  case 1:
    opinion = council_science_advice(civ,era);
    break;
  case 2:
    opinion = council_trade_advice(civ,era);
    break;
  case 3:
    opinion = council_foreign_advice(civ,era);
    break;
  default:
    opinion = council_attitude_advice(civ,era);
  }
  return opinion;
}
#undef era

/* 00522dfa auto */
#define leader (*(iptr *)(frame_ + FRAME_OFF(4)))
#define i (*(int *)(frame_ + FRAME_OFF(8)))
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
    for (i = 0; i < 7; i++) {
      if (leaders[leader].titles[i][0] < 1) {
        *(ushort *)&leaders[leader].titles[i][0] =
             ~*(ushort *)&leaders[leader].titles[i][0] + 1;
      }
      if (leaders[leader].titles[i][1] < 1) {
        *(ushort *)&leaders[leader].titles[i][1] =
             ~*(ushort *)&leaders[leader].titles[i][1] + 1;
      }
    }
  }
  return;
}
#undef leader
#undef i

/* 0059c575 auto */
void __cdecl casualty_log_add(iptr unit,iptr unit2,iptr year,iptr x,i32 y)

{
  i32 color;
  char *_Source;
  size_t _Count;
  
  *(ushort *)
   (&casualty_log_unit_types +
   units[unit].owner * 0x27d8 + *(int *)(&casualty_log_next + units[unit].owner * 4) * 0x22) =
       (ushort)units[unit].type;
  *(short *)(&casualty_log_x +
            units[unit].owner * 0x27d8 +
            *(int *)(&casualty_log_next + units[unit].owner * 4) * 0x22) = (short)x;
  *(i16 *)
   (&casualty_log_y +
   units[unit].owner * 0x27d8 + *(int *)(&casualty_log_next + units[unit].owner * 4) * 0x22) =
       (i16)y;
  *(short *)(&casualty_log_years +
            units[unit].owner * 0x27d8 +
            *(int *)(&casualty_log_next + units[unit].owner * 4) * 0x22) = (short)year;
  color = civ_color_secondary((int)units[unit2].owner);
  *(short *)(&casualty_log_killer_colors +
            units[unit].owner * 0x27d8 +
            *(int *)(&casualty_log_next + units[unit].owner * 4) * 0x22) = (short)color;
  _Count = 0x18;
  _Source = (char *)civ_name_plural((int)units[unit2].owner);
  _strncpy((char *)(*(int *)(&casualty_log_next + units[unit].owner * 4) * 0x22 +
                    units[unit].owner * 0x27d8 + (iptr)((u8 *)&g.d_006af2a8 + 2)),_Source,_Count);
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
