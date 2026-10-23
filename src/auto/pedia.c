/* The game, the Civilopedia: functions translated from the original
 * (tools/gen_c.py, now edited directly), in address order. */
#include "auto_common.h"

/* 00451af0 auto */
#define panel_margin_x (*(int *)((u8 *)&g.d_0062d858))
#define body_rect (*(tagRECT *)(frame_ + FRAME_OFF(0)))
#define body_height (*(int *)(frame_ + FRAME_OFF(16)))
void __thiscall
pedia_draw_category_body(DocumentWindow *this,i32 category,i32 flags)

{
  int xLeft;
  int yTop;
  int col_width;
  int line_height;
  int title_height;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  gfx_set_text_color_index(10);
  xLeft = this->content_left + panel_margin_x;
  yTop = this->content_top + panel_margin_y;
  col_width = rect_width((iptr)&this->content_left);
  col_width = (col_width + panel_margin_x * -2) / 2 - panel_margin_x;
  line_height = font_cached_height((GameFont *)&font_size21);
  title_height = font_cached_height((GameFont *)&font_size24_bold);
  body_height = line_height * 9 + title_height + panel_margin_y * 0xd;
  SetRect(&body_rect,xLeft,yTop,col_width + xLeft,body_height + yTop);
  gfx_set_draw_target(ADDR(0x6a6668, ((u8 *)&g.d_006a6668)));
  pedia_dispatch_category_draw(this,body_rect.left,body_rect.top,body_rect.right,body_rect.bottom,category);
  wnd_blit_surface_rect((DibSurface *)this,(iptr)this->pedia_body_blit_rect);
  return;
}
#undef panel_margin_x
#undef body_rect
#undef body_height

/* 00451bf0 auto */
#define hotspot_parent2 (*(u8 * *)(frame_ + FRAME_OFF(0)))
#define hotspot_parent (*(u8 * *)(frame_ + FRAME_OFF(4)))
#define hotspot2 (*(u32 *)(frame_ + FRAME_OFF(8)))
#define hotspot (*(u32 *)(frame_ + FRAME_OFF(16)))
#define rect_left2 (*(u32 *)(frame_ + FRAME_OFF(32)))
#define rect_top2 (*(u32 *)(frame_ + FRAME_OFF(36)))
#define rect_right2 (*(u32 *)(frame_ + FRAME_OFF(40)))
#define rect_bottom2 (*(u32 *)(frame_ + FRAME_OFF(44)))
#define seh_frame (*(i32 *)(frame_ + FRAME_OFF(48)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(52)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(56)))
void __thiscall pedia_update_controls(MediaWindow *this)

{
  u32 view_mode;
  int scroll_height;
  Control *pCVar3;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  control_hide((Control *)(((PictureWindow *)this)->list_describe_button));
  control_hide((Control *)((u8 *)&((PictureWindow *)this)->list_close_button));
  control_hide((Control *)((u8 *)&((PictureWindow *)this)->detail_back_button));
  control_hide((Control *)(((PictureWindow *)this)->detail_describe_button));
  control_hide((Control *)&((PictureWindow *)this)->detail_close_button);
  control_hide((Control *)(((PictureWindow *)this)->text_back_button));
  control_hide((Control *)&((PictureWindow *)this)->text_close_button);
  control_hide((Control *)&((PictureWindow *)this)->list_scrollbar);
  control_hide((Control *)(u8 *)&((PictureWindow *)this)->concept_list_back_button);
  control_hide((Control *)(((PictureWindow *)this)->advance_list_describe_button));
  control_hide((Control *)(((PictureWindow *)this)->advance_list_tech_tree_button));
  control_hide((Control *)(((PictureWindow *)this)->advance_list_close_button));
  control_hide((Control *)&((PictureWindow *)this)->advance_detail_back_button);
  control_hide((Control *)((u8 *)&((PictureWindow *)this)->advance_detail_tech_tree_button));
  control_hide((Control *)(((PictureWindow *)this)->advance_detail_describe_button));
  control_hide((Control *)&((PictureWindow *)this)->advance_detail_close_button);
  control_hide((Control *)&((PictureWindow *)this)->description_edit);
  ctrl_set_text((ControlTextView *)&((PictureWindow *)this)->description_edit,ADDR(0x626854, ((u8 *)&g.d_00626854)));
  if (((PictureWindow *)this)->list_hotspot != 0) {
    if ((Hotspot *)((PictureWindow *)this)->list_hotspot != (Hotspot *)0x0) {
      hotspot_scalar_dtor((Hotspot *)((PictureWindow *)this)->list_hotspot,1);
    }
    ((PictureWindow *)this)->list_hotspot = 0;
  }
  view_mode = this->border_width;
  if (view_mode == 0) {
    ((PictureWindow *)this)->list_rect = this->content_left;
    ((PictureWindow *)this)->list_rect_top = this->content_top;
    ((PictureWindow *)this)->list_rect_right = this->content_right;
    ((PictureWindow *)this)->list_rect_bottom = this->content_bottom;
    scroll_height = GetSystemMetrics(3);
    ((PictureWindow *)this)->list_rect_bottom -= scroll_height;
    if (this->caption_height == 8) {
      ctrl_show_and_redraw((Control *)(u8 *)&((PictureWindow *)this)->concept_list_back_button);
      ctrl_show_and_redraw((Control *)((u8 *)&((PictureWindow *)this)->list_close_button));
    }
    else if (this->caption_height == 1) {
      ctrl_show_and_redraw((Control *)(((PictureWindow *)this)->advance_list_describe_button));
      ctrl_show_and_redraw((Control *)(((PictureWindow *)this)->advance_list_tech_tree_button));
      ctrl_show_and_redraw((Control *)(((PictureWindow *)this)->advance_list_close_button));
      ctrl_show_and_redraw((Control *)&((PictureWindow *)this)->list_scrollbar);
      if (((PictureWindow *)this)->list_hotspot == 0) {
        rect_left2 = this->content_left;
        rect_top2 = this->content_top;
        rect_right2 = this->content_right;
        rect_bottom2 = this->content_bottom;
        scroll_height = GetSystemMetrics(3);
        rect_bottom2 -= scroll_height;
        pCVar3 = operator_new(0x40);
        seh_state = 0;
        if (pCVar3 == (Control *)0x0) {
          hotspot = 0;
        }
        else {
          hotspot = hotspot_ctor(pCVar3);
        }
        seh_state = 0xffffffff;
        ((PictureWindow *)this)->list_hotspot = hotspot;
        if (this == (MediaWindow *)0x0) {
          hotspot_parent = (u8 *)0x0;
        }
        else {
          hotspot_parent = this->window_2;
        }
        hotspot_create
                  ((ClickControl *)((PictureWindow *)this)->list_hotspot,(iptr)hotspot_parent,0xfa9,(iptr)&rect_left2);
        hotspot_set_click_callback((HotspotClickSetView *)((PictureWindow *)this)->list_hotspot,ADDR(0x402270, pedia_list_on_click));
        hotspot_set_dblclick_callback((HotspotDblClickSetView *)((PictureWindow *)this)->list_hotspot,ADDR(0x40196f, pedia_toggle_describe));
        ctrl_show_and_redraw((Control *)((PictureWindow *)this)->list_hotspot);
      }
    }
    else {
      ctrl_show_and_redraw((Control *)(((PictureWindow *)this)->list_describe_button));
      ctrl_show_and_redraw((Control *)&((PictureWindow *)this)->list_scrollbar);
      ctrl_show_and_redraw((Control *)((u8 *)&((PictureWindow *)this)->list_close_button));
      if (((PictureWindow *)this)->list_hotspot == 0) {
        rect_left2 = this->content_left;
        rect_top2 = this->content_top;
        rect_right2 = this->content_right;
        rect_bottom2 = this->content_bottom;
        scroll_height = GetSystemMetrics(3);
        rect_bottom2 -= scroll_height;
        pCVar3 = operator_new(0x40);
        seh_state = 1;
        if (pCVar3 == (Control *)0x0) {
          hotspot2 = 0;
        }
        else {
          hotspot2 = hotspot_ctor(pCVar3);
        }
        seh_state = 0xffffffff;
        ((PictureWindow *)this)->list_hotspot = hotspot2;
        if (this == (MediaWindow *)0x0) {
          hotspot_parent2 = (u8 *)0x0;
        }
        else {
          hotspot_parent2 = this->window_2;
        }
        hotspot_create
                  ((ClickControl *)((PictureWindow *)this)->list_hotspot,(iptr)hotspot_parent2,0xfa9,(iptr)&rect_left2);
        hotspot_set_click_callback((HotspotClickSetView *)((PictureWindow *)this)->list_hotspot,ADDR(0x402270, pedia_list_on_click));
        hotspot_set_dblclick_callback((HotspotDblClickSetView *)((PictureWindow *)this)->list_hotspot,ADDR(0x40196f, pedia_toggle_describe));
        ctrl_show_and_redraw((Control *)((PictureWindow *)this)->list_hotspot);
      }
    }
  }
  else if (view_mode == 1) {
    if ((this->caption_height == 6) || (this->caption_height == 7)) {
      ctrl_show_and_redraw((Control *)(((PictureWindow *)this)->text_back_button));
      ctrl_show_and_redraw((Control *)&((PictureWindow *)this)->text_close_button);
    }
    else if (this->caption_height == 1) {
      ctrl_show_and_redraw((Control *)&((PictureWindow *)this)->advance_detail_back_button);
      ctrl_show_and_redraw((Control *)((u8 *)&((PictureWindow *)this)->advance_detail_tech_tree_button));
      ctrl_show_and_redraw((Control *)(((PictureWindow *)this)->advance_detail_describe_button));
      ctrl_show_and_redraw((Control *)&((PictureWindow *)this)->advance_detail_close_button);
    }
    else {
      ctrl_show_and_redraw((Control *)((u8 *)&((PictureWindow *)this)->detail_back_button));
      ctrl_show_and_redraw((Control *)(((PictureWindow *)this)->detail_describe_button));
      ctrl_show_and_redraw((Control *)&((PictureWindow *)this)->detail_close_button);
    }
  }
  else if (view_mode == 2) {
    ctrl_show_and_redraw((Control *)(((PictureWindow *)this)->text_back_button));
    ctrl_show_and_redraw((Control *)&((PictureWindow *)this)->text_close_button);
  }
  ui_pump_messages();
  return;
}
#undef hotspot_parent2
#undef hotspot_parent
#undef hotspot2
#undef hotspot
#undef rect_left2
#undef rect_top2
#undef rect_right2
#undef rect_bottom2
#undef seh_frame
#undef seh_handler
#undef seh_state

/* 00452188 auto */
void __thiscall
pedia_dispatch_category_draw
          (DocumentWindow *this,i32 left,i32 top,i32 right,
          i32 bottom,i32 category)

{
  u32 pargs_[5] = {(u32)(uptr)left, (u32)(uptr)top, (u32)(uptr)right, (u32)(uptr)bottom, (u32)(uptr)category};  /* the arguments, contiguous as on the original stack */
#define left (*(i32 *)&pargs_[0])
#define top (*(i32 *)&pargs_[1])
#define right (*(i32 *)&pargs_[2])
#define bottom (*(i32 *)&pargs_[3])
#define category (*(i32 *)&pargs_[4])
  switch(category) {
  case 0:
    break;
  case 1:
    if (this->border_width == 0) {
      pedia_init_advance_list((PediaAdvanceListView *)this,(iptr)&left);
    }
    else {
      pedia_draw_advance_page(this);
    }
    break;
  case 2:
    if (this->border_width == 0) {
      pedia_init_improvement_list(this,(iptr)&left);
    }
    else {
      pedia_draw_improvement_page(this);
    }
    break;
  case 3:
    if (this->border_width == 0) {
      pedia_init_wonder_list((MediaWindow *)this,(iptr)&left);
    }
    else {
      pedia_draw_improvement(this);
    }
    break;
  case 4:
    if (this->border_width == 0) {
      pedia_show_unit_list((MediaWindow *)this,(iptr)&left);
    }
    else {
      pedia_draw_unit_page(this);
    }
    break;
  case 5:
    if (this->border_width == 0) {
      pedia_init_terrain_list((MediaWindow *)this,(iptr)&left);
    }
    break;
  case 6:
    if (this->border_width == 0) {
      pedia_init_government_list((MediaWindow *)this,(iptr)&left);
    }
    break;
  case 7:
    if (this->border_width == 0) {
      pedia_init_concept_list((MediaWindow *)this,(iptr)&left);
    }
    break;
  case 8:
    pedia_draw_advance_tree(this);
  }
  return;
}
#undef left
#undef top
#undef right
#undef bottom
#undef category

/* 00452315: written by hand in src/game/retvals.c */

/* 00452768 auto */
#define topic_id (*(int *)(frame_ + FRAME_OFF(4)))
#define path (*(i8 (*)[260])(frame_ + FRAME_OFF(8)))
void __thiscall pedia_update_describe_button(ListPaneWindow *this,int list_index)

{
  int result;
  i8 frame_[FRAME_OFF(272)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((((game.game_flags & 0x80) != 0) && (this->caption_height != 7)) &&
     (result = _strcmp(&scenario_dir_path,&game_home_dir), result != 0)) {
    __chdir(&scenario_dir_path);
    crt_strcpy(path,s_describe__006268fc);
    crt_strcat(path,&lang_file_ext);
    result = file_exists((iptr)path);
    if (result == 0) {
      ctrl_disable((Control *)(((PictureWindow *)this)->detail_describe_button));
      __chdir(&game_home_dir);
      return;
    }
    __chdir(&game_home_dir);
  }
  switch(this->caption_height) {
  case 1:
    topic_id = *(int *)(((MediaWindow *)this)->advance_topic_view + list_index * 4 + 0x88);
    break;
  case 2:
    topic_id = *(int *)(((DocumentWindow *)this)->improvement_topic_view + list_index * 4 + 0x58);
    break;
  case 3:
    topic_id = *(int *)(((PictureWindow *)this)->wonder_topic_view + list_index * 4 + 0x78);
    break;
  case 4:
    topic_id = *(int *)(((PictureWindow *)this)->unit_topic_slots + list_index * 4 + 0x40);
    break;
  case 5:
    topic_id = *(int *)(((PictureWindow *)this)->government_topic_slots + list_index * 4 + 0x38);
    break;
  case 6:
    topic_id = *(int *)(((PictureWindow *)this)->government_topic_slots + list_index * 4 - 4);
    break;
  case 7:
    topic_id = *(int *)(((PictureWindow *)this)->advisor_code_slots + list_index * 4 + 0x28);
  }
  if (topic_id < 0) {
    if (this->caption_height == 1) {
      ctrl_disable((Control *)(((PictureWindow *)this)->advance_detail_describe_button));
    }
    else {
      ctrl_disable((Control *)(((PictureWindow *)this)->detail_describe_button));
    }
  }
  else if (this->caption_height == 1) {
    ctrl_enable((Control *)(((PictureWindow *)this)->advance_detail_describe_button));
  }
  else {
    ctrl_enable((Control *)(((PictureWindow *)this)->detail_describe_button));
  }
  return;
}
#undef topic_id
#undef path

/* 004529df auto */
#define app_hinstance (*(HINSTANCE *)((u8 *)&g.d_006e4ff0))
#define wnd_class (*(WNDCLASSA *)(frame_ + FRAME_OFF(4)))
void __cdecl hyperlink_register_class(void)

{
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (hyperlink_class_registered == 0) {
    hyperlink_class_registered = 1;
    wnd_class.style = 0x88;
    wnd_class.lpfnWndProc = ctrl_default_wndproc;
    wnd_class.cbClsExtra = 0;
    wnd_class.cbWndExtra = 0x10;
    wnd_class.hInstance = app_hinstance;
    wnd_class.hIcon = (HICON)0x0;
    wnd_class.hCursor = LoadCursorA(app_hinstance,(LPCSTR)0x212);
    wnd_class.hbrBackground = (HBRUSH)0x0;
    wnd_class.lpszMenuName = (LPCSTR)0x0;
    wnd_class.lpszClassName = s_MSHyperTextClass_00626908;
    RegisterClassA(&wnd_class);
  }
  return;
}
#undef app_hinstance
#undef wnd_class

/* 00452a67 auto */
#define seh_frame (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
void __thiscall hyperlink_dtor(HyperlinkDtorView *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0;
  if (this->hwnd != 0) {
    region_dispose(this->hwnd);
  }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 00452ac1 */ { ctrl_base_dtor(*(ControlBase **)((iptr)&this)); }
  return;
}
#undef seh_frame
#undef seh_handler
#undef seh_state

/* 00452ae2 auto */
#define app_hinstance (*(HINSTANCE *)((u8 *)&g.d_006e4ff0))
HWND __cdecl hyperlink_create_hwnd(int *rect,iptr control)

{
  WndBase *this;
  iptr parent_wnd;
  iptr height;
  int width;
  HWND pHVar4;
  HMENU hMenu;
  HINSTANCE hInstance;
  LPVOID lpParam;
  
  hyperlink_register_class();
  lpParam = (LPVOID)0x0;
  hMenu = (HMENU)0x0;
  hInstance = app_hinstance;
  this = (WndBase *)ctrl_get_parent((Control *)control);
  parent_wnd = wnd_get_window(this);
  pHVar4 = *(HWND *)(parent_wnd + 4);
  height = rect_height((iptr)rect);
  width = rect_width((iptr)rect);
  pHVar4 = CreateWindowExA(4,s_MSHyperTextClass_00626920,&hyperlink_window_title_str,0x50000000,*rect,
                           rect[1],width,height,pHVar4,hMenu,hInstance,lpParam);
  width = ctrl_init_block(pHVar4,control);
  *(i32 *)(width + 0x2c) = 1;
  SetWindowLongA(pHVar4,-4,ADDR(0x5c8caf, hotspot_wndproc));
  return pHVar4;
}
#undef app_hinstance

/* 00452b89 auto */
void __thiscall
hyperlink_create(ClickControl *this,iptr parent,i32 control_id,iptr rect)

{
  u32 hwnd;
  
  if (this->hwnd != 0) {
    ctrl_destroy((Control *)this);
  }
  ctrl_init((Control *)this,parent,1,control_id,rect);
  this->is_enabled = 0;
  this->on_click = 0;
  this->on_select = 0;
  this->font = 0;
  this->scroll_pos = 0;
  hwnd = hyperlink_create_hwnd(rect,(iptr)this);
  this->hwnd = hwnd;
  return;
}

/* 00452c14 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define parent_wnd2 (*(u8 * *)(frame_ + FRAME_OFF(4)))
#define link (*(u32 * *)(frame_ + FRAME_OFF(12)))
#define list_index (*(u32 *)(frame_ + FRAME_OFF(20)))
#define link_index (*(int *)(frame_ + FRAME_OFF(28)))
#define last_link (*(iptr *)(frame_ + FRAME_OFF(32)))
#define seh_frame (*(i32 *)(frame_ + FRAME_OFF(40)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(44)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(48)))
void __thiscall
pedia_add_link
          (DocumentWindow *this,iptr item_id,int x,int y,i32 link_kind,
          i32 rect_left,i32 rect_top,i32 rect_right,i32 rect_bottom)

{
  int text_width;
  int max_width;
  uptr len;
  PediaLinkCtorView *pCVar3;
  int underline_y;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  u32 pargs_[4] = {(u32)(uptr)rect_left, (u32)(uptr)rect_top, (u32)(uptr)rect_right, (u32)(uptr)rect_bottom};  /* the arguments, contiguous as on the original stack */
#define rect_left (*(i32 *)&pargs_[0])
#define rect_top (*(i32 *)&pargs_[1])
#define rect_right (*(i32 *)&pargs_[2])
#define rect_bottom (*(i32 *)&pargs_[3])
  
  seh_state = 0xffffffff;
  switch(link_kind) {
  case 0:
    list_index = 0;
    while (((int)list_index < (int)this->pedia_advance_count &&
           (*(int *)(this->advance_sort_keys + list_index * 4 + 400) != item_id))) {
      list_index++;
    }
    if (this->pedia_advance_count == list_index) goto switchD_00452e28_default;
    break;
  case 1:
    list_index = 0;
    while (((int)list_index < (int)this->pedia_improve_count &&
           (*(int *)(this->improvement_sort_keys + list_index * 4 + 0x9c) != item_id))) {
      list_index++;
    }
    if (this->pedia_improve_count == list_index) goto switchD_00452e28_default;
    break;
  case 2:
    for (list_index = 0;
        ((int)list_index < *(int *)(((PictureWindow *)this)->wonder_count) &&
        (*(int *)(((PictureWindow *)this)->pedia_improvement_ids + list_index * 4) != item_id)); list_index++) {
    }
    if (*(u32 *)(((PictureWindow *)this)->wonder_count) == list_index) goto switchD_00452e28_default;
    break;
  case 3:
    list_index = 0;
    while (((int)list_index < *(int *)(((PictureWindow *)this)->pedia_unit_count) &&
           (*(int *)(((PictureWindow *)this)->unit_ids_tail + list_index * 4 - 4) != item_id))) {
      list_index++;
    }
    if (*(u32 *)(((PictureWindow *)this)->pedia_unit_count) == list_index) goto switchD_00452e28_default;
    break;
  case 4:
    list_index = 0;
    while (((int)list_index < (int)((PictureWindow *)this)->pedia_terrain_count_2 &&
           (*(int *)(((PictureWindow *)this)->terrain_key_slots + list_index * 4 + 0x6c) != item_id))) {
      list_index++;
    }
    if (((PictureWindow *)this)->pedia_terrain_count_2 == list_index) goto switchD_00452e28_default;
    break;
  default:
    goto switchD_00452e28_default;
  }
  while( true ) {
    text_width = font_text_width((GameFont *)&font_size21,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    max_width = rect_width((iptr)&rect_left);
    if (text_width <= max_width) break;
    len = _strlen(&text_buffer);
    (&text_buffer_minus1)[len] = 0;
  }
  if ((this->caption_height == 8) && (text_width = civ_has_advance(human_civ,item_id), text_width != 0)) {
    gfx_set_text_color_index(0x6a);
  }
  else {
    gfx_set_text_color_index(0x55);
  }
  text_width = font_cached_height((GameFont *)&font_size21);
  underline_y = y + text_width - 2;
  text_width = font_text_width((GameFont *)&font_size21,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  text_width = x + text_width;
  max_width = font_cached_height((GameFont *)&font_size21);
  surface_draw_line((DibSurface *)this,x,y + max_width - 2,text_width,underline_y);
  gfx_set_text_color_index(10);
  surface_draw_text((DibSurface *)this,ADDR(0x67a798, ((u8 *)&g.d_0067a798)),ADDR(0x679640, ((u8 *)&g.d_00679640)),x + 1,y,5);
  if ((this->caption_height == 8) && (text_width = civ_has_advance(human_civ,item_id), text_width != 0)) {
    gfx_set_text_color_index(0x6a);
  }
  else {
    gfx_set_text_color_index(0x55);
  }
  surface_draw_text((DibSurface *)this,ADDR(0x67a798, ((u8 *)&g.d_0067a798)),ADDR(0x679640, ((u8 *)&g.d_00679640)),x,y,5);
  gfx_set_text_color_index(10);
  pCVar3 = operator_new(0x48);
  seh_state = 0;
  if (pCVar3 == (PediaLinkCtorView *)0x0) {
    link = (u32 *)0x0;
  }
  else {
    link = (u32 *)pedia_link_ctor(pCVar3);
  }
  seh_state = 0xffffffff;
  *link = list_index;
  link[0x11] = 0;
  link_index = 0;
  if (*(int *)(((PictureWindow *)this)->link_list_head) == 0) {
    *(u32 **)(((PictureWindow *)this)->link_list_head) = link;
  }
  else {
    link_index = 1;
    for (last_link = *(iptr *)(((PictureWindow *)this)->link_list_head); *(int *)(last_link + 0x44) != 0;
        last_link = *(iptr *)(last_link + 0x44)) {
      link_index++;
    }
    *(u32 **)(last_link + 0x44) = link;
  }
  if (this == (DocumentWindow *)0x0) {
    parent_wnd2 = (u8 *)0x0;
  }
  else {
    parent_wnd2 = this->window_2;
  }
  hyperlink_create
            ((ClickControl *)(link + 1),(iptr)parent_wnd2,link_index + 0xfb4,(iptr)&rect_left);
  switch(link_kind) {
  case 0:
    hyperlink_set_click_callback((HyperlinkSetClickCallbackView *)(link + 1),ADDR(0x401c76, pedia_link_on_click_advance));
    hyperlink_set_dblclick_callback((HyperlinkSetDblclickCallbackView *)(link + 1),ADDR(0x401c76, pedia_link_on_click_advance));
    break;
  case 1:
    hyperlink_set_click_callback((HyperlinkSetClickCallbackView *)(link + 1),ADDR(0x4019ce, pedia_link_on_click_improvement));
    hyperlink_set_dblclick_callback((HyperlinkSetDblclickCallbackView *)(link + 1),ADDR(0x4019ce, pedia_link_on_click_improvement));
    break;
  case 2:
    hyperlink_set_click_callback((HyperlinkSetClickCallbackView *)(link + 1),ADDR(0x403729, pedia_link_on_click_wonder));
    hyperlink_set_dblclick_callback((HyperlinkSetDblclickCallbackView *)(link + 1),ADDR(0x403729, pedia_link_on_click_wonder));
    break;
  case 3:
    hyperlink_set_click_callback((HyperlinkSetClickCallbackView *)(link + 1),ADDR(0x402333, pedia_link_on_click_unit));
    hyperlink_set_dblclick_callback((HyperlinkSetDblclickCallbackView *)(link + 1),ADDR(0x402333, pedia_link_on_click_unit));
    break;
  case 4:
    hyperlink_set_click_callback((HyperlinkSetClickCallbackView *)(link + 1),ADDR(0x4019b0, pedia_link_on_click_terrain));
    hyperlink_set_dblclick_callback((HyperlinkSetDblclickCallbackView *)(link + 1),ADDR(0x4019b0, pedia_link_on_click_terrain));
  }
  ctrl_show_and_redraw((Control *)(link + 1));
switchD_00452e28_default:
  return;
}
#undef human_civ
#undef text_buffer
#undef parent_wnd2
#undef link
#undef list_index
#undef link_index
#undef last_link
#undef seh_frame
#undef seh_handler
#undef seh_state
#undef rect_left
#undef rect_top
#undef rect_right
#undef rect_bottom

/* 004531b8 auto */
#define pedia_category (*(i32 *)((u8 *)&g.d_006a6780))
#define pedia_page_mode (*(i32 *)((u8 *)&g.d_006a6784))
#define pedia_selected_item (*(i32 *)((u8 *)&g.d_006a85a0))
#define link (*(i32 * *)(frame_ + FRAME_OFF(4)))
#define link_index (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl pedia_link_on_click_advance(int control_id)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  link_index = control_id - 0xfb4;
  for (link = pedia_link_list; (link_index != 0 && (link != (i32 *)0x0));
      link = (i32 *)link[0x11]) {
    link_index--;
  }
  if (link != (i32 *)0x0) {
    pedia_category = 1;
    pedia_page_mode = 0;
    pedia_selected_item = *link;
    pedia_toggle_describe(1);
  }
  return;
}
#undef pedia_category
#undef pedia_page_mode
#undef pedia_selected_item
#undef link
#undef link_index

/* 0045323a auto */
#define pedia_category (*(i32 *)((u8 *)&g.d_006a6780))
#define pedia_page_mode (*(i32 *)((u8 *)&g.d_006a6784))
#define pedia_selected_item (*(i32 *)((u8 *)&g.d_006a85a0))
#define link (*(i32 * *)(frame_ + FRAME_OFF(4)))
#define link_index (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl pedia_link_on_click_improvement(int control_id)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  link_index = control_id - 0xfb4;
  for (link = pedia_link_list; (link_index != 0 && (link != (i32 *)0x0));
      link = (i32 *)link[0x11]) {
    link_index--;
  }
  if (link != (i32 *)0x0) {
    pedia_category = 2;
    pedia_page_mode = 0;
    pedia_selected_item = *link;
    pedia_toggle_describe(1);
  }
  return;
}
#undef pedia_category
#undef pedia_page_mode
#undef pedia_selected_item
#undef link
#undef link_index

/* 004532bc auto */
#define pedia_category (*(i32 *)((u8 *)&g.d_006a6780))
#define pedia_page_mode (*(i32 *)((u8 *)&g.d_006a6784))
#define pedia_selected_item (*(i32 *)((u8 *)&g.d_006a85a0))
#define link (*(i32 * *)(frame_ + FRAME_OFF(4)))
#define link_index (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl pedia_link_on_click_wonder(int control_id)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  link_index = control_id - 0xfb4;
  for (link = pedia_link_list; (link_index != 0 && (link != (i32 *)0x0));
      link = (i32 *)link[0x11]) {
    link_index--;
  }
  if (link != (i32 *)0x0) {
    pedia_category = 3;
    pedia_page_mode = 0;
    pedia_selected_item = *link;
    pedia_toggle_describe(1);
  }
  return;
}
#undef pedia_category
#undef pedia_page_mode
#undef pedia_selected_item
#undef link
#undef link_index

/* 0045333e auto */
#define pedia_category (*(i32 *)((u8 *)&g.d_006a6780))
#define pedia_page_mode (*(i32 *)((u8 *)&g.d_006a6784))
#define pedia_selected_item (*(i32 *)((u8 *)&g.d_006a85a0))
#define link (*(i32 * *)(frame_ + FRAME_OFF(4)))
#define link_index (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl pedia_link_on_click_unit(int control_id)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  link_index = control_id - 0xfb4;
  for (link = pedia_link_list; (link_index != 0 && (link != (i32 *)0x0));
      link = (i32 *)link[0x11]) {
    link_index--;
  }
  if (link != (i32 *)0x0) {
    pedia_category = 4;
    pedia_page_mode = 0;
    pedia_selected_item = *link;
    pedia_toggle_describe(1);
  }
  return;
}
#undef pedia_category
#undef pedia_page_mode
#undef pedia_selected_item
#undef link
#undef link_index

/* 004533c0 auto */
#define pedia_category (*(i32 *)((u8 *)&g.d_006a6780))
#define pedia_page_mode (*(i32 *)((u8 *)&g.d_006a6784))
#define pedia_selected_item (*(i32 *)((u8 *)&g.d_006a85a0))
#define link (*(i32 * *)(frame_ + FRAME_OFF(4)))
#define link_index (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl pedia_link_on_click_terrain(int control_id)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  link_index = control_id - 0xfb4;
  for (link = pedia_link_list; (link_index != 0 && (link != (i32 *)0x0));
      link = (i32 *)link[0x11]) {
    link_index--;
  }
  if (link != (i32 *)0x0) {
    pedia_category = 5;
    pedia_page_mode = 0;
    pedia_selected_item = *link;
    pedia_toggle_describe(1);
  }
  return;
}
#undef pedia_category
#undef pedia_page_mode
#undef pedia_selected_item
#undef link
#undef link_index

/* 00453b10 auto */
#define seh_frame (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
PediaLinkCtorView * __thiscall pedia_link_ctor(PediaLinkCtorView *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  hyperlink_ctor((Control *)(this->link_control));
  return this;
}
#undef seh_frame
#undef seh_handler
#undef seh_state

/* 00453cc0 auto */
#define seh_frame (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
Control * __thiscall hyperlink_ctor(Control *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  ctrl_base_ctor(this);
  return this;
}
#undef seh_frame
#undef seh_handler
#undef seh_state

/* 00453d40 auto */
void __thiscall hyperlink_set_click_callback(HyperlinkSetClickCallbackView *this,iptr callback)

{
  this->on_click = callback;
  return;
}

/* 00453d70 auto */
/* Library Function - Single Match
    public: void __thiscall CDialog::SetHelpID(unsigned int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall hyperlink_set_dblclick_callback(HyperlinkSetDblclickCallbackView *this,iptr callback)

{
  this->on_dblclick = callback;
  return;
}

/* 00490590 auto */
#define i (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall pedia_init_terrain_list(MediaWindow *this,iptr rect)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((int)this->resize_border < 0) || (*(int *)((u8 *)&((PictureWindow *)this)->pedia_terrain_count_2) <= (int)this->resize_border)) {
    this->resize_border = 0;
  }
  *(i32 *)((PictureWindow *)this)->list_item_table = *(i32 *)((u8 *)&((PictureWindow *)this)->pedia_terrain_count_2);
  *(u32 *)(((PictureWindow *)this)->list_selected_index) = this->resize_border;
  *(u32 *)(((PictureWindow *)this)->list_top_index) = this->resize_border;
  while (pedia_list_top % 9 != 0) {
    *(int *)(((PictureWindow *)this)->list_top_index) = *(int *)(((PictureWindow *)this)->list_top_index) - 1;
  }
  for (i = 0; i < *(int *)((u8 *)&((PictureWindow *)this)->pedia_terrain_count_2); i++) {
    *(i32 *)(((PictureWindow *)this)->list_item_table + i * 4 + 4) =
         *(i32 *)(((PictureWindow *)this)->terrain_id_slots + i * 4 + 0x1c);
  }
  scrollbar_set_range
            ((Control *)&((PictureWindow *)this)->list_scrollbar,0,*(int *)((PictureWindow *)this)->list_item_table / 9);
  scrollbar_set_pos
            ((ClickControl *)&((PictureWindow *)this)->list_scrollbar,*(int *)(((PictureWindow *)this)->list_top_index) / 9);
  if (*(int *)((PictureWindow *)this)->list_item_table < 1) {
    ((PictureWindow *)this)->list_top_index[0] = 0xff;
    ((PictureWindow *)this)->list_top_index_byte1[0] = 0xff;
    ((PictureWindow *)this)->list_top_index_byte2[0] = 0xff;
    ((PictureWindow *)this)->list_top_index_byte3[0] = 0xff;
  }
  pedia_update_controls(this);
  wnd_set_focus((WndBase *)&pedia_window_wnd);
  wnd_activate((Wnd *)&pedia_window_wnd);
  pedia_redraw((PediaRedrawView *)&pedia_window);
  return;
}
#undef i

/* 004906fd auto */
#define list_text_color (*(i32 *)((u8 *)&g.d_00635a1c))
#define panel_margin_x (*(int *)((u8 *)&g.d_0062d858))
#define pedia_terrain_names (*(i32 *)((u8 *)&g.d_006a7d58))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define trade_sprite_ctx2 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define shield_sprite_ctx2 (*(i8 (*)[16])(frame_ + FRAME_OFF(16)))
#define food_sprite_ctx2 (*(i8 (*)[16])(frame_ + FRAME_OFF(32)))
#define trade_sprite_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(48)))
#define shield_sprite_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(64)))
#define food_sprite_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(80)))
#define resource_sprite_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(96)))
#define hill_sprite_ctx2 (*(i8 (*)[16])(frame_ + FRAME_OFF(112)))
#define forest_sprite_ctx2 (*(i8 (*)[16])(frame_ + FRAME_OFF(128)))
#define grass_shield_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(144)))
#define mountain_sprite_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(160)))
#define hill_sprite_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(176)))
#define forest_sprite_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(192)))
#define base_sprite_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(208)))
#define format_buf (*(char (*)[256])(frame_ + FRAME_OFF(224)))
#define base_trade2 (*(int *)(frame_ + FRAME_OFF(480)))
#define base_name (*(i8 (*)[40])(frame_ + FRAME_OFF(484)))
#define base_shields (*(int *)(frame_ + FRAME_OFF(524)))
#define special_trade (*(int *)(frame_ + FRAME_OFF(528)))
#define base_food (*(int *)(frame_ + FRAME_OFF(532)))
#define special_shields (*(int *)(frame_ + FRAME_OFF(536)))
#define special_food (*(int *)(frame_ + FRAME_OFF(540)))
#define line_height (*(int *)(frame_ + FRAME_OFF(544)))
#define terrain2 (*(iptr *)(frame_ + FRAME_OFF(548)))
#define half_width (*(int *)(frame_ + FRAME_OFF(552)))
#define link_height (*(int *)(frame_ + FRAME_OFF(556)))
#define terrain3 (*(iptr *)(frame_ + FRAME_OFF(560)))
#define sprite_area_width (*(int *)(frame_ + FRAME_OFF(564)))
#define improve_kind (*(iptr *)(frame_ + FRAME_OFF(568)))
#define sprite_height2 (*(int *)(frame_ + FRAME_OFF(572)))
#define stats_top (*(int *)(frame_ + FRAME_OFF(576)))
#define y2 (*(int *)(frame_ + FRAME_OFF(580)))
#define x2 (*(u32 *)(frame_ + FRAME_OFF(584)))
#define page_width (*(int *)(frame_ + FRAME_OFF(588)))
#define value_x (*(int *)(frame_ + FRAME_OFF(592)))
#define resource_variant (*(uint *)(frame_ + FRAME_OFF(596)))
#define sprite_width2 (*(int *)(frame_ + FRAME_OFF(600)))
#define margin (*(int *)(frame_ + FRAME_OFF(604)))
#define right_col_x (*(int *)(frame_ + FRAME_OFF(608)))
#define text_color2 (*(i32 *)(frame_ + FRAME_OFF(612)))
#define link_width (*(int *)(frame_ + FRAME_OFF(616)))
#define link_rect (*(tagRECT *)(frame_ + FRAME_OFF(620)))
#define scale_den2 (*(i32 *)(frame_ + FRAME_OFF(636)))
#define scale_num2 (*(int *)(frame_ + FRAME_OFF(640)))
#define row_height (*(int *)(frame_ + FRAME_OFF(644)))
#define saved_clip (*(i8 (*)[16])(frame_ + FRAME_OFF(648)))
#define font2 (*(GameFont * *)(frame_ + FRAME_OFF(664)))
void __thiscall pedia_draw_terrain_page(DocumentWindow *this)

{
  u8 shields;
  int measured;
  iptr terrain_index;
  i32 label;
  char *_Format;
  int icon_center_y;
  i8 *name_arg;
  i8 frame_[FRAME_OFF(672)] __attribute__((aligned(8)));  /* original stack frame */
  
  surface_get_clip((DibSurface *)this,(iptr)saved_clip);
  surface_set_clip((DibSurface *)this,(iptr)&this->content_left);
  pedia_update_controls((MediaWindow *)this);
  pedia_fill_background((WindowObjectView *)this,(iptr)&this->content_left,2);
  font2 = (GameFont *)&font_size21;
  x2 = this->content_left;
  margin = 10;
  page_width = rect_width((iptr)&this->content_left);
  half_width = page_width / 2;
  row_height = rect_height((iptr)&this->content_left);
  row_height = row_height / 0xc;
  line_height = font_cached_height(font2);
  y2 = this->content_top + 8;
  terrain2 = *(iptr *)(((PictureWindow *)this)->terrain_key_slots + this->resize_border * 4 + 0x6c);
  gfx_get_scale_ratio((iptr)&scale_num2,(iptr)&scale_den2);
  gfx_set_scale_ratio(scale_num2 * 2,scale_den2);
  sprite_height2 = sprite_get_height((Sprite *)&terrain_base_sprites);
  sprite_width2 = sprite_get_width((Sprite *)&terrain_base_sprites);
  x2 += margin;
  y2 += (row_height / 2 - sprite_height2 / 2);
  terrain3 = terrain2 % 0xb;
  sprite_area_width = sprite_width2 * 2 + panel_margin_x * 2;
  sprite_draw
            ((Sprite *)(&terrain_base_sprites + terrain3 * 0x3c),(iptr)base_sprite_ctx,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),x2,
             y2);
  if (terrain2 < 0xb) {
    if (terrain2 == 3) {
      sprite_draw
                ((Sprite *)&forest_sprites,(iptr)forest_sprite_ctx,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),x2,y2);
    }
    else if (terrain2 == 4) {
      sprite_draw
                ((Sprite *)&hill_sprites,(iptr)hill_sprite_ctx,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),x2,y2);
    }
    else if (terrain2 == 5) {
      sprite_draw
                ((Sprite *)&mountain_sprites,(iptr)mountain_sprite_ctx,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),x2,y2);
    }
  }
  else {
    resource_variant = (uint)(0x15 < terrain2);
    switch(terrain2) {
    case 0xd:
    case 0x18:
      sprite_draw
                ((Sprite *)&grassland_shield_sprite,(iptr)grass_shield_ctx,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),x2,y2);
      goto LAB_00490a7d;
    case 0xe:
    case 0x19:
      sprite_draw
                ((Sprite *)&forest_sprites,(iptr)forest_sprite_ctx2,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),x2,y2);
      break;
    case 0xf:
    case 0x1a:
      sprite_draw
                ((Sprite *)&hill_sprites,(iptr)hill_sprite_ctx2,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),x2,y2);
      break;
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17: ;
    }
    sprite_draw
              ((Sprite *)(&terrain_resource_sprites + terrain3 * 0x78 + resource_variant * 0x3c),(iptr)resource_sprite_ctx,
               ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),x2,y2);
  }
LAB_00490a7d:
  gfx_set_scale_ratio(scale_num2,scale_den2);
  text_color2 = list_text_color;
  gfx_set_text_color_index(list_text_color);
  x2 = this->content_left + margin;
  right_col_x = rect_width((iptr)&this->content_left);
  right_col_x = right_col_x / 2;
  value_x = right_col_x - 100;
  if ((terrain2 < 0) || (10 < terrain2)) {
    x2 = x2 + sprite_area_width + 0x1e;
    y2 += line_height;
    text_clear();
    text_append_label(0x295);
    text_append_colon();
    surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
    measured = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    x2 = x2 + measured + 10;
    text_clear();
    terrain_index = pedia_find_terrain_index(terrain3);
    label = pedia_lookup_text(pedia_terrain_names,terrain_index);
    crt_strcpy(&text_buffer,label);
    link_width = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    link_height = font_line_spacing(font2);
    SetRect(&link_rect,x2,y2,x2 + link_width + 5,y2 + link_height);
    pedia_add_link(this,terrain3,x2,y2,4,link_rect.left,link_rect.top,link_rect.right,
                       link_rect.bottom);
    y2 += ((sprite_height2 * 2 + 10) - line_height);
  }
  else {
    stats_top = y2 + sprite_height2 * 2 + 10;
    y2 = stats_top;
    text_clear();
    text_append_label(0x293);
    text_append_colon();
    surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
    text_clear();
    _sprintf(&text_buffer,&pedia_terrain_move_cost_fmt,(int)(char)terrain_types[terrain2].move_cost);
    surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),value_x,y2,5);
    x2 = this->content_left + margin;
    y2 += line_height;
    text_clear();
    text_append_label(0x294);
    text_append_colon();
    surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
    text_clear();
    if (terrain_types[terrain2].defense == 6) {
      crt_strcpy(&text_buffer,s__200__0062c948);
    }
    else if (terrain_types[terrain2].defense == 3) {
      crt_strcpy(&text_buffer,&pedia_terrain_defense_50_str);
    }
    else if (terrain_types[terrain2].defense == 4) {
      crt_strcpy(&text_buffer,s__100__0062c958);
    }
    else if (terrain_types[terrain2].defense == 5) {
      crt_strcpy(&text_buffer,s__150__0062c960);
    }
    else {
      terrain_index = label_string(*(i32 *)(label_string_ids + 0xb08));
      text_append(terrain_index);
    }
    surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),value_x,y2,5);
  }
  x2 = this->content_left + margin;
  y2 += line_height;
  text_clear();
  text_append_label(0x40);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
  text_clear();
  _sprintf(&text_buffer,&pedia_terrain_food_fmt,(int)(char)terrain_types[terrain2].food);
  surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),value_x,y2,5);
  measured = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  x2 = value_x + measured + 3;
  icon_center_y = y2 + row_height / 2;
  measured = sprite_get_height((Sprite *)&resource_icon_sprites);
  sprite_draw
            ((Sprite *)&resource_icon_sprites,(iptr)food_sprite_ctx,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),x2,
             (icon_center_y - 2) - measured / 2);
  x2 = this->content_left + margin;
  y2 += line_height;
  text_clear();
  text_append_label(0x296);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
  text_clear();
  if (terrain2 == 2) {
    shields = '\0';
  }
  else {
    shields = terrain_types[terrain2].shields;
  }
  _sprintf(&text_buffer,&pedia_terrain_shields_fmt,(int)(char)shields);
  surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),value_x,y2,5);
  measured = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  x2 = value_x + measured + 3;
  icon_center_y = y2 + row_height / 2;
  measured = sprite_get_height((Sprite *)&shield_icon_sprite);
  sprite_draw
            ((Sprite *)&shield_icon_sprite,(iptr)shield_sprite_ctx,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),x2,
             (icon_center_y - 2) - measured / 2);
  x2 = this->content_left + margin;
  y2 += line_height;
  text_clear();
  text_append_label(0x45);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
  text_clear();
  _sprintf(&text_buffer,&pedia_terrain_trade_fmt,(int)(char)terrain_types[terrain2].trade);
  surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),value_x,y2,5);
  measured = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  x2 = value_x + measured + 3;
  icon_center_y = y2 + row_height / 2;
  measured = sprite_get_height((Sprite *)&trade_icon_sprite);
  sprite_draw
            ((Sprite *)&trade_icon_sprite,(iptr)trade_sprite_ctx,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),x2,
             (icon_center_y - 2) - measured / 2);
  if ((terrain2 < 0) || (10 < terrain2)) {
    x2 = this->content_left + margin;
    y2 += line_height * 2;
    terrain_index = pedia_find_terrain_index(terrain3);
    label = pedia_lookup_text(pedia_terrain_names,terrain_index);
    crt_strcpy(base_name,label);
    base_food = (int)(char)terrain_types[terrain3].food;
    if (terrain3 == 2) {
      shields = '\0';
    }
    else {
      shields = terrain_types[terrain3].shields;
    }
    base_shields = (int)(char)shields;
    base_trade2 = (int)(char)terrain_types[terrain3].trade;
    special_food = (int)(char)terrain_types[terrain2].food;
    special_shields = (int)(char)terrain_types[terrain2].shields;
    special_trade = (int)(char)terrain_types[terrain2].trade;
    text_clear();
    if (base_food < special_food) {
      name_arg = base_name;
      measured = base_food;
      icon_center_y = special_food;
      _Format = (char *)label_string(*(i32 *)(label_string_ids + 0xb10));
      _sprintf(&text_buffer,_Format,name_arg,measured,icon_center_y);
    }
    else {
      label = label_string(*(i32 *)(label_string_ids + 0xb14));
      crt_strcpy(&text_buffer,label);
    }
    surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
    y2 += line_height;
    text_clear();
    str_clear((iptr)format_buf);
    if (base_shields < special_shields) {
      label = label_string(*(i32 *)(label_string_ids + 0xb18));
      crt_strcpy(format_buf,label);
      _sprintf(&text_buffer,format_buf,base_shields,special_shields);
      surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
      y2 += line_height;
      text_clear();
      str_clear((iptr)format_buf);
      if (base_trade2 < special_trade) {
        label = label_string(*(i32 *)(label_string_ids + 0xb1c));
        crt_strcat(format_buf,label);
        _sprintf(&text_buffer,format_buf,base_trade2,special_trade);
      }
      else {
        label = label_string(*(i32 *)(label_string_ids + 0xb20));
        crt_strcat(&text_buffer,label);
      }
    }
    else {
      label = label_string(*(i32 *)(label_string_ids + 0xb24));
      crt_strcpy(&text_buffer,label);
      surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
      y2 += line_height;
      text_clear();
      str_clear((iptr)format_buf);
      if (base_trade2 < special_trade) {
        label = label_string(*(i32 *)(label_string_ids + 0xb1c));
        crt_strcat(format_buf,label);
        _sprintf(&text_buffer,format_buf,base_trade2,special_trade);
      }
      else {
        label = label_string(*(i32 *)(label_string_ids + 0xb28));
        crt_strcat(&text_buffer,label);
      }
    }
    surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
  }
  else {
    for (improve_kind = 0; improve_kind < 2; improve_kind++) {
      x2 = this->content_left + margin;
      y2 += line_height;
      text_clear();
      if (improve_kind == 0) {
        text_append_label(0x297);
      }
      else {
        text_append_label(0x299);
      }
      text_append_colon();
      surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
      text_clear();
      if (*(char *)(improve_kind + ADDR(0x627cce, ((u8 *)&terrain_types + 14)) + terrain2 * 0x18) < '\0') {
        if (*(char *)(improve_kind + ADDR(0x627cd0, ((u8 *)&terrain_types + 16)) + terrain2 * 0x18) < 1) {
          text_append_label(0x29b);
          surface_draw_text
                    ((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),value_x,y2,5);
        }
        else {
          _sprintf(&text_buffer,&pedia_terrain_improve_bonus_fmt,(int)*(char *)(improve_kind + ADDR(0x627cd0, ((u8 *)&terrain_types + 16)) + terrain2 * 0x18)
                  );
          surface_draw_text
                    ((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),value_x,y2,5);
          measured = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
          x2 = value_x + measured + 3;
          if (improve_kind == 0) {
            icon_center_y = y2 + row_height / 2;
            measured = sprite_get_height((Sprite *)&resource_icon_sprites);
            sprite_draw
                      ((Sprite *)&resource_icon_sprites,(iptr)food_sprite_ctx2,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),x2,
                       (icon_center_y - 2) - measured / 2);
          }
          else {
            icon_center_y = y2 + row_height / 2;
            measured = sprite_get_height((Sprite *)&shield_icon_sprite);
            sprite_draw
                      ((Sprite *)&shield_icon_sprite,(iptr)shield_sprite_ctx2,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),x2,
                       (icon_center_y - 2) - measured / 2);
          }
        }
      }
      else {
        terrain_index = pedia_find_terrain_index((int)*(char *)(improve_kind + ADDR(0x627cce, ((u8 *)&terrain_types + 14)) + terrain2 * 0x18));
        label = pedia_lookup_text(pedia_terrain_names,terrain_index);
        crt_strcpy(&text_buffer,label);
        link_width = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
        link_height = font_line_spacing(font2);
        SetRect(&link_rect,value_x,y2,link_width + value_x + 5,y2 + link_height);
        pedia_add_link(this,(int)*(char *)(improve_kind + ADDR(0x627cce, ((u8 *)&terrain_types + 14)) + terrain2 * 0x18),value_x,
                           y2,4,link_rect.left,link_rect.top,link_rect.right,link_rect.bottom);
      }
      x2 = this->content_left + margin;
      y2 += line_height;
      text_clear();
      if (improve_kind == 0) {
        text_append_label(0x298);
      }
      else {
        text_append_label(0x29a);
      }
      text_append_colon();
      surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
      text_clear();
      if (*(char *)(improve_kind + ADDR(0x627cd2, ((u8 *)&terrain_types + 18)) + terrain2 * 0x18) < 1) {
        text_append_label(0x29b);
      }
      else {
        _sprintf(&text_buffer,&pedia_terrain_improve_turns_fmt,(int)*(char *)(improve_kind + ADDR(0x627cd2, ((u8 *)&terrain_types + 18)) + terrain2 * 0x18));
      }
      surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),value_x,y2,5);
    }
    x2 = right_col_x;
    text_clear();
    y2 = stats_top;
    text_append_label(0x29c);
    text_append_colon();
    surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
    x2 += 0x14;
    y2 += line_height;
    text_clear();
    if (terrain_types[terrain2].transform_to < '\0') {
      text_append_label(0x29b);
      surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
    }
    else {
      terrain_index = pedia_find_terrain_index((int)terrain_types[terrain2].transform_to);
      label = pedia_lookup_text(pedia_terrain_names,terrain_index);
      crt_strcpy(&text_buffer,label);
      link_width = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
      link_height = font_line_spacing(font2);
      SetRect(&link_rect,x2,y2,x2 + link_width + 5,y2 + link_height);
      pedia_add_link(this,(int)terrain_types[terrain2].transform_to,x2,y2,4,
                         link_rect.left,link_rect.top,link_rect.right,link_rect.bottom);
    }
    if (terrain2 != 10) {
      x2 = right_col_x;
      y2 += line_height;
      text_clear();
      text_append_label(0x29d);
      text_append_colon();
      surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
      text_clear();
      x2 += 0x14;
      y2 += line_height;
      text_append_label(0x293);
      text_append_colon();
      text_append_space();
      terrain_index = label_string(*(i32 *)(label_string_ids + 0xb0c));
      text_append(terrain_index);
      surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
      if (((terrain2 == 0) || (terrain2 == 2)) || (terrain2 == 1)) {
        y2 += line_height;
        text_clear();
        text_append_label(0x45);
        text_append_colon();
        text_append(ADDR(0x62c980, ((u8 *)&g.d_0062c980)));
        surface_draw_text
                  ((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
        measured = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
        x2 = x2 + measured + 3;
        icon_center_y = y2 + row_height / 2;
        measured = sprite_get_height((Sprite *)&trade_icon_sprite);
        sprite_draw
                  ((Sprite *)&trade_icon_sprite,(iptr)trade_sprite_ctx2,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),x2,
                   (icon_center_y - 2) - measured / 2);
      }
    }
    x2 = right_col_x;
    y2 += line_height;
    text_clear();
    text_append_label(0x29e);
    text_append_colon();
    surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
    x2 += 0x14;
    y2 += line_height;
    text_clear();
    terrain_index = pedia_find_terrain_index(terrain2 + 0xb);
    label = pedia_lookup_text(pedia_terrain_names,terrain_index);
    crt_strcpy(&text_buffer,label);
    link_width = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    link_height = font_line_spacing(font2);
    SetRect(&link_rect,x2,y2,x2 + link_width + 5,y2 + link_height);
    pedia_add_link(this,terrain2 + 0xb,x2,y2,4,link_rect.left,link_rect.top,
                       link_rect.right,link_rect.bottom);
    if (terrain2 != 2) {
      text_clear();
      y2 += line_height;
      terrain_index = pedia_find_terrain_index(terrain2 + 0x16);
      label = pedia_lookup_text(pedia_terrain_names,terrain_index);
      crt_strcpy(&text_buffer,label);
      link_width = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
      link_height = font_line_spacing(font2);
      SetRect(&link_rect,x2,y2,x2 + link_width + 5,y2 + link_height);
      pedia_add_link(this,terrain2 + 0x16,x2,y2,4,link_rect.left,link_rect.top,
                         link_rect.right,link_rect.bottom);
    }
  }
  pedia_update_describe_button((ListPaneWindow *)this,this->resize_border);
  surface_set_clip((DibSurface *)this,(iptr)saved_clip);
  wnd_blit_surface_rect((DibSurface *)this,(iptr)&this->content_left);
  return;
}
#undef list_text_color
#undef panel_margin_x
#undef pedia_terrain_names
#undef text_buffer
#undef trade_sprite_ctx2
#undef shield_sprite_ctx2
#undef food_sprite_ctx2
#undef trade_sprite_ctx
#undef shield_sprite_ctx
#undef food_sprite_ctx
#undef resource_sprite_ctx
#undef hill_sprite_ctx2
#undef forest_sprite_ctx2
#undef grass_shield_ctx
#undef mountain_sprite_ctx
#undef hill_sprite_ctx
#undef forest_sprite_ctx
#undef base_sprite_ctx
#undef format_buf
#undef base_trade2
#undef base_name
#undef base_shields
#undef special_trade
#undef base_food
#undef special_shields
#undef special_food
#undef line_height
#undef terrain2
#undef half_width
#undef link_height
#undef terrain3
#undef sprite_area_width
#undef improve_kind
#undef sprite_height2
#undef stats_top
#undef y2
#undef x2
#undef page_width
#undef value_x
#undef resource_variant
#undef sprite_width2
#undef margin
#undef right_col_x
#undef text_color2
#undef link_width
#undef link_rect
#undef scale_den2
#undef scale_num2
#undef row_height
#undef saved_clip
#undef font2

/* 00491c20 auto */
#define pedia_closed (*(int *)((u8 *)&g.d_006a677c))
#define pedia_terrain_names (*(i32 *)((u8 *)&g.d_006a7d58))
#define terrain_idx (*(uptr *)(frame_ + FRAME_OFF(0)))
void __thiscall pedia_show_terrain_modal(DocumentWindow *this,int terrain_id)

{
  i32 name_text;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (pedia_closed != 0) {
    terrain_idx = 0;
    while (((int)terrain_idx < (int)((PictureWindow *)this)->pedia_terrain_count_2 &&
           (*(int *)(((PictureWindow *)this)->terrain_key_slots + terrain_idx * 4 + 0x6c) != terrain_id))) {
      terrain_idx++;
    }
    if (((PictureWindow *)this)->pedia_terrain_count_2 != terrain_idx) {
      pedia_open_category((MediaWindow *)this,5,1);
      this->resize_border = terrain_idx;
      *(uptr *)(((PictureWindow *)this)->list_selected_index) = terrain_idx;
      this->client_x = 1;
      this->border_width = 1;
      pedia_clear_links((WindowObjectView *)this);
      pedia_update_controls((MediaWindow *)this);
      name_text = pedia_lookup_text(pedia_terrain_names,terrain_idx);
      crt_strcpy(this->pedia_title_text_2,name_text);
      pedia_draw_frame((MediaWindow *)this);
      pedia_draw_terrain_page(this);
      wnd_blit_surface((DibSurface *)&pedia_window);
      wnd_activate((Wnd *)&pedia_window_wnd);
      wnd_set_modal_idle_callback((ModalMenuWindow *)&pedia_window_wnd,ADDR(0x401843, pedia_modal_idle));
      wnd_run_modal_loop((ModalMenuWindow *)&pedia_window_wnd);
      wnd_set_modal_idle_callback((ModalMenuWindow *)&pedia_window_wnd,0);
    }
  }
  return;
}
#undef pedia_closed
#undef pedia_terrain_names
#undef terrain_idx

/* 00491d61 auto */
#define index (*(int *)(frame_ + FRAME_OFF(0)))
i32 __cdecl pedia_find_terrain_index(iptr terrain_id)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  index = 0;
  while( true ) {
    if (pedia_terrain_count <= index) {
      return 0xffffffff;
    }
    if (*(int *)(&pedia_terrain_ids + index * 4) == terrain_id) break;
    index++;
  }
  return index;
}
#undef index

/* 004a69b0 auto */
#define i (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall pedia_init_concept_list(MediaWindow *this,iptr unused_arg)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((int)this->resize_border < 0) || ((int)(*(uptr *)&((PictureWindow *)this)->pedia_concept_count) <= (int)this->resize_border)) {
    this->resize_border = 0;
  }
  *(uptr *)((PictureWindow *)this)->list_item_table = (*(uptr *)&((PictureWindow *)this)->pedia_concept_count);
  *(u32 *)(((PictureWindow *)this)->list_selected_index) = this->resize_border;
  *(u32 *)(((PictureWindow *)this)->list_top_index) = this->resize_border;
  while (pedia_list_top % 9 != 0) {
    *(int *)(((PictureWindow *)this)->list_top_index) = *(int *)(((PictureWindow *)this)->list_top_index) - 1;
  }
  for (i = 0; i < (int)(*(uptr *)&((PictureWindow *)this)->pedia_concept_count); i++) {
    *(i32 *)(((PictureWindow *)this)->list_item_table + i * 4 + 4) =
         *(i32 *)(((PictureWindow *)this)->pedia_concept_list_base + i * 4 + 0x40);
  }
  scrollbar_set_range
            ((Control *)&((PictureWindow *)this)->list_scrollbar,0,*(int *)((PictureWindow *)this)->list_item_table / 9);
  scrollbar_set_pos
            ((ClickControl *)&((PictureWindow *)this)->list_scrollbar,*(int *)(((PictureWindow *)this)->list_top_index) / 9);
  if (*(int *)((PictureWindow *)this)->list_item_table < 1) {
    ((PictureWindow *)this)->list_top_index[0] = 0xff;
    ((PictureWindow *)this)->list_top_index_byte1[0] = 0xff;
    ((PictureWindow *)this)->list_top_index_byte2[0] = 0xff;
    ((PictureWindow *)this)->list_top_index_byte3[0] = 0xff;
  }
  pedia_update_controls(this);
  wnd_set_focus((WndBase *)&pedia_window_wnd);
  wnd_activate((Wnd *)&pedia_window_wnd);
  pedia_redraw((PediaRedrawView *)&pedia_window);
  return;
}
#undef i

/* 004f3f80 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl pedia_window_global_init(void)

{
  pedia_window_static_init();
  pedia_window_reg_atexit();
  return;
}

/* 004f3f9a auto */
void __cdecl pedia_window_static_init(void)

{
  pedia_window_ctor((ScaledWindowView *)&pedia_window);
  return;
}

/* 004f3fb4 auto */
void __cdecl pedia_window_reg_atexit(void)

{
  _atexit(pedia_window_static_dtor);
  return;
}

/* 004f3fd1 auto */
void __cdecl pedia_window_static_dtor(void)

{
  pedia_window_dtor((DibSurface *)&pedia_window);
  return;
}

/* 004f3feb auto */
#define i (*(int *)(frame_ + FRAME_OFF(4)))
#define exc_link (*(i32 *)(frame_ + FRAME_OFF(8)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(12)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(16)))
ScaledWindowView * __thiscall pedia_window_ctor(ScaledWindowView *this)

{
  u8 *slot;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  surfwnd_ctor((SurfaceWindow *)this);
  eh_state = 0;
  button_ctor((Control *)(((PictureWindow *)this)->list_describe_button));
  (*(i8 *)((char *)&eh_state + 0)) = 1;
  button_ctor((Control *)((u8 *)&((PictureWindow *)this)->list_close_button));
  (*(i8 *)((char *)&eh_state + 0)) = 2;
  button_ctor((Control *)&((PictureWindow *)this)->detail_back_button);
  (*(i8 *)((char *)&eh_state + 0)) = 3;
  button_ctor((Control *)(((PictureWindow *)this)->detail_describe_button));
  (*(i8 *)((char *)&eh_state + 0)) = 4;
  button_ctor((Control *)((u8 *)&((PictureWindow *)this)->detail_close_button));
  (*(i8 *)((char *)&eh_state + 0)) = 5;
  button_ctor((Control *)(((PictureWindow *)this)->text_back_button));
  (*(i8 *)((char *)&eh_state + 0)) = 6;
  button_ctor((Control *)((u8 *)&((PictureWindow *)this)->text_close_button));
  (*(i8 *)((char *)&eh_state + 0)) = 7;
  button_ctor((Control *)&((PictureWindow *)this)->concept_list_back_button);
  (*(i8 *)((char *)&eh_state + 0)) = 8;
  button_ctor((Control *)(((PictureWindow *)this)->advance_list_describe_button));
  (*(i8 *)((char *)&eh_state + 0)) = 9;
  button_ctor((Control *)(((PictureWindow *)this)->advance_list_tech_tree_button));
  (*(i8 *)((char *)&eh_state + 0)) = 10;
  button_ctor((Control *)(((PictureWindow *)this)->advance_list_close_button));
  (*(i8 *)((char *)&eh_state + 0)) = 0xb;
  button_ctor((Control *)((u8 *)&((PictureWindow *)this)->advance_detail_back_button));
  (*(i8 *)((char *)&eh_state + 0)) = 0xc;
  button_ctor((Control *)&((PictureWindow *)this)->advance_detail_tech_tree_button);
  (*(i8 *)((char *)&eh_state + 0)) = 0xd;
  button_ctor((Control *)(((PictureWindow *)this)->advance_detail_describe_button));
  (*(i8 *)((char *)&eh_state + 0)) = 0xe;
  button_ctor((Control *)((u8 *)&((PictureWindow *)this)->advance_detail_close_button));
  (*(i8 *)((char *)&eh_state + 0)) = 0xf;
  edit_ctor((InputControl *)((u8 *)&((PictureWindow *)this)->description_edit));
  eh_state = CONCAT31((*(i32 *)((char *)&eh_state + 1)),0x10);
  scrollbar_ctor((Control *)&((PictureWindow *)this)->list_scrollbar);
  this->vtable = (u32)&PTR_FUN_0061d6d0;
  this->style_flags = 1;
  this->border_width = 0;
  this->resize_border = 0;
  this->client_x = 0;
  ((PictureWindow *)this)->close_box_hotspot[0] = '\0';
  ((PictureWindow *)this)->close_box_hotspot_byte1[0] = '\0';
  ((PictureWindow *)this)->close_box_hotspot_byte2[0] = '\0';
  ((PictureWindow *)this)->close_box_hotspot_byte3[0] = '\0';
  ((PictureWindow *)this)->link_list_head[0] = '\0';
  ((PictureWindow *)this)->link_list_head_byte1[0] = '\0';
  ((PictureWindow *)this)->link_list_head_byte2[0] = '\0';
  ((PictureWindow *)this)->link_list_head_byte3_region[0] = '\0';
  this->caption_height = 0;
  for (i = 0; i < 100; i++) {
    slot = ((PediaAdvanceListView *)this)->pedia_list_init_area + i * 4 + 0x38;
    slot[0] = 0xff;
    slot[1] = 0xff;
    slot[2] = 0xff;
    slot[3] = 0xff;
  }
  for (i = 0; i < 0x27; i++) {
    slot = ((DocumentWindow *)this)->improvement_list_init_area + i * 4 - 0x28;
    slot[0] = 0xff;
    slot[1] = 0xff;
    slot[2] = 0xff;
    slot[3] = 0xff;
  }
  for (i = 0; i < 0x1c; i++) {
    slot = ((PictureWindow *)this)->improvement_key_slots + i * 4 - 0x18;
    slot[0] = 0xff;
    slot[1] = 0xff;
    slot[2] = 0xff;
    slot[3] = 0xff;
  }
  for (i = 0; i < 0x3e; i++) {
    slot = ((PictureWindow *)this)->unit_key_init_slots + i * 4 + 0x10;
    slot[0] = 0xff;
    slot[1] = 0xff;
    slot[2] = 0xff;
    slot[3] = 0xff;
  }
  for (i = 0; i < 7; i++) {
    slot = ((PictureWindow *)this)->pedia_key_init_slots + i * 4 + 0x68;
    slot[0] = 0xff;
    slot[1] = 0xff;
    slot[2] = 0xff;
    slot[3] = 0xff;
  }
  for (i = 0; i < 0x21; i++) {
    slot = ((PictureWindow *)this)->pedia_key_init_slots + i * 4 + 0xa4;
    slot[0] = 0xff;
    slot[1] = 0xff;
    slot[2] = 0xff;
    slot[3] = 0xff;
  }
  for (i = 0; i < 0x100; i++) {
    slot = (u8 *)&((PictureWindow *)this)->advisor_opinions + i * 4 + 0x84;
    slot[0] = 0xff;
    slot[1] = 0xff;
    slot[2] = 0xff;
    slot[3] = 0xff;
  }
  ((PictureWindow *)this)->improvements_scrollbar[0] = '\0';
  ((PictureWindow *)this)->improvements_scrollbar_byte1[0] = '\0';
  ((PictureWindow *)this)->improvements_scrollbar_byte2[0] = '\0';
  ((PictureWindow *)this)->improvements_scrollbar_byte3[0] = '\0';
  ((PictureWindow *)this)->pedia_list_head[0] = '\0';
  ((PictureWindow *)this)->pedia_list_head_byte1[0] = '\0';
  ((PictureWindow *)this)->text_list_1_byte2[0] = '\0';
  ((PictureWindow *)this)->text_list_1_byte3[0] = '\0';
  ((PictureWindow *)this)->text_list_2_head[0] = '\0';
  ((PictureWindow *)this)->text_list_2_byte1[0] = '\0';
  ((PictureWindow *)this)->text_list_2_byte2[0] = '\0';
  ((PictureWindow *)this)->text_list_2_byte3[0] = '\0';
  ((PictureWindow *)this)->text_list_3_head[0] = '\0';
  ((PictureWindow *)this)->text_list_3_byte1[0] = '\0';
  ((PictureWindow *)this)->text_list_3_byte2[0] = '\0';
  ((PictureWindow *)this)->text_list_3_byte3[0] = '\0';
  ((PictureWindow *)this)->text_list_4_head[0] = '\0';
  ((PictureWindow *)this)->text_list_4_byte1[0] = '\0';
  ((PictureWindow *)this)->text_list_4_byte2[0] = '\0';
  ((PictureWindow *)this)->text_list_4_byte3[0] = '\0';
  ((PictureWindow *)this)->text_list_5_head[0] = '\0';
  ((PictureWindow *)this)->text_list_5_byte1[0] = '\0';
  ((PictureWindow *)this)->text_list_5_byte2[0] = '\0';
  ((PictureWindow *)this)->text_list_5_byte3[0] = '\0';
  ((PictureWindow *)this)->text_list_6_head[0] = '\0';
  ((PictureWindow *)this)->text_list_6_byte1[0] = '\0';
  ((PictureWindow *)this)->text_list_6_byte2[0] = '\0';
  ((PictureWindow *)this)->text_list_6_byte3[0] = '\0';
  ((PictureWindow *)this)->list_hotspot = 0;
  this->client_y = 0;
  return this;
}
#undef i
#undef exc_link
#undef seh_handler
#undef eh_state

/* 004f44a7 auto */
#define exc_link (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define eh_state (*(int *)(frame_ + FRAME_OFF(8)))
void __thiscall pedia_window_dtor(DibSurface *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  this->vtable = (u32)&PTR_FUN_0061d6d0;
  eh_state = 0x11;
  pedia_free_lists((WindowObjectView *)this);
  pedia_clear_links((WindowObjectView *)this);
  if ((*(u32 *)&((PictureWindow *)this)->close_box_hotspot) != 0) {
    if ((Hotspot *)(*(u32 *)&((PictureWindow *)this)->close_box_hotspot) != (Hotspot *)0x0) {
      hotspot_scalar_dtor((Hotspot *)(*(u32 *)&((PictureWindow *)this)->close_box_hotspot),1);
    }
    (*(u32 *)&((PictureWindow *)this)->close_box_hotspot) = 0;
  }
  if (((PictureWindow *)this)->list_hotspot != 0) {
    if ((Hotspot *)((PictureWindow *)this)->list_hotspot != (Hotspot *)0x0) {
      hotspot_scalar_dtor((Hotspot *)((PictureWindow *)this)->list_hotspot,1);
    }
    ((PictureWindow *)this)->list_hotspot = 0;
  }
  wnd_destroy_with_surface(this);
  (*(i8 *)((char *)&eh_state + 0)) = 0x10;
  /* inlined unwind funclet 004f4673 */ { scrollbar_dtor((Control *)(*(int *)((iptr)&this) + 0x1ae0)); }
  (*(i8 *)((char *)&eh_state + 0)) = 0xf;
  /* inlined unwind funclet 004f4682 */ { edit_dtor((Control *)(*(int *)((iptr)&this) + 0x1a98)); }
  (*(i8 *)((char *)&eh_state + 0)) = 0xe;
  /* inlined unwind funclet 004f4691 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x1a5c)); }
  (*(i8 *)((char *)&eh_state + 0)) = 0xd;
  /* inlined unwind funclet 004f46a0 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x1a20)); }
  (*(i8 *)((char *)&eh_state + 0)) = 0xc;
  /* inlined unwind funclet 004f46af */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x19e4)); }
  (*(i8 *)((char *)&eh_state + 0)) = 0xb;
  /* inlined unwind funclet 004f46be */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x19a8)); }
  (*(i8 *)((char *)&eh_state + 0)) = 10;
  /* inlined unwind funclet 004f46cd */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x196c)); }
  (*(i8 *)((char *)&eh_state + 0)) = 9;
  /* inlined unwind funclet 004f46dc */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x1930)); }
  (*(i8 *)((char *)&eh_state + 0)) = 8;
  /* inlined unwind funclet 004f46eb */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x18f4)); }
  (*(i8 *)((char *)&eh_state + 0)) = 7;
  /* inlined unwind funclet 004f46fa */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x18b8)); }
  (*(i8 *)((char *)&eh_state + 0)) = 6;
  /* inlined unwind funclet 004f4709 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x187c)); }
  (*(i8 *)((char *)&eh_state + 0)) = 5;
  /* inlined unwind funclet 004f4718 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x1840)); }
  (*(i8 *)((char *)&eh_state + 0)) = 4;
  /* inlined unwind funclet 004f4727 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x1804)); }
  (*(i8 *)((char *)&eh_state + 0)) = 3;
  /* inlined unwind funclet 004f4736 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x17c8)); }
  (*(i8 *)((char *)&eh_state + 0)) = 2;
  /* inlined unwind funclet 004f4745 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x178c)); }
  (*(i8 *)((char *)&eh_state + 0)) = 1;
  /* inlined unwind funclet 004f4754 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x1750)); }
  eh_state = (uint)(*(i32 *)((char *)&eh_state + 1)) << 8;
  /* inlined unwind funclet 004f4763 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x1714)); }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 004f4772 */ { surfwnd_dtor(*(SurfaceWindow **)((iptr)&this)); }
  return;
}
#undef exc_link
#undef seh_handler
#undef eh_state

/* 004f4793 auto */
void __thiscall pedia_clear_links(WindowObjectView *this)

{
  u32 next_link;
  
  while ((*(u32 *)&((PictureWindow *)this)->link_list_head) != 0) {
    next_link = *(u32 *)((*(u32 *)&((PictureWindow *)this)->link_list_head) + 0x44);
    if ((void *)(*(u32 *)&((PictureWindow *)this)->link_list_head) != (void *)0x0) {
      pedia_link_scalar_dtor((void *)(*(u32 *)&((PictureWindow *)this)->link_list_head),1);
    }
    (*(u32 *)&((PictureWindow *)this)->link_list_head) = next_link;
  }
  wnd_flush_paint();
  return;
}

/* 004f4809 auto */
void __thiscall pedia_free_lists(WindowObjectView *this)

{
  u32 next_node;
  
  while ((*(u32 *)&((PictureWindow *)this)->improvements_scrollbar) != 0) {
    next_node = *(u32 *)((*(u32 *)&((PictureWindow *)this)->improvements_scrollbar) + 8);
    if (*(int *)(*(u32 *)&((PictureWindow *)this)->improvements_scrollbar) != 0) {
      operator_delete(*(void **)(*(u32 *)&((PictureWindow *)this)->improvements_scrollbar));
    }
    operator_delete((void *)(*(u32 *)&((PictureWindow *)this)->improvements_scrollbar));
    (*(u32 *)&((PictureWindow *)this)->improvements_scrollbar) = next_node;
  }
  while ((*(u32 *)&((PictureWindow *)this)->pedia_list_head) != 0) {
    next_node = *(u32 *)((*(u32 *)&((PictureWindow *)this)->pedia_list_head) + 8);
    if (*(int *)(*(u32 *)&((PictureWindow *)this)->pedia_list_head) != 0) {
      operator_delete(*(void **)(*(u32 *)&((PictureWindow *)this)->pedia_list_head));
    }
    operator_delete((void *)(*(u32 *)&((PictureWindow *)this)->pedia_list_head));
    (*(u32 *)&((PictureWindow *)this)->pedia_list_head) = next_node;
  }
  while ((*(u32 *)&((PictureWindow *)this)->text_list_2_head) != 0) {
    next_node = *(u32 *)((*(u32 *)&((PictureWindow *)this)->text_list_2_head) + 8);
    if (*(int *)(*(u32 *)&((PictureWindow *)this)->text_list_2_head) != 0) {
      operator_delete(*(void **)(*(u32 *)&((PictureWindow *)this)->text_list_2_head));
    }
    operator_delete((void *)(*(u32 *)&((PictureWindow *)this)->text_list_2_head));
    (*(u32 *)&((PictureWindow *)this)->text_list_2_head) = next_node;
  }
  while ((*(u32 *)&((PictureWindow *)this)->text_list_3_head) != 0) {
    next_node = *(u32 *)((*(u32 *)&((PictureWindow *)this)->text_list_3_head) + 8);
    if (*(int *)(*(u32 *)&((PictureWindow *)this)->text_list_3_head) != 0) {
      operator_delete(*(void **)(*(u32 *)&((PictureWindow *)this)->text_list_3_head));
    }
    operator_delete((void *)(*(u32 *)&((PictureWindow *)this)->text_list_3_head));
    (*(u32 *)&((PictureWindow *)this)->text_list_3_head) = next_node;
  }
  while ((*(u32 *)&((PictureWindow *)this)->text_list_4_head) != 0) {
    next_node = *(u32 *)((*(u32 *)&((PictureWindow *)this)->text_list_4_head) + 8);
    if (*(int *)(*(u32 *)&((PictureWindow *)this)->text_list_4_head) != 0) {
      operator_delete(*(void **)(*(u32 *)&((PictureWindow *)this)->text_list_4_head));
    }
    operator_delete((void *)(*(u32 *)&((PictureWindow *)this)->text_list_4_head));
    (*(u32 *)&((PictureWindow *)this)->text_list_4_head) = next_node;
  }
  while ((*(u32 *)&((PictureWindow *)this)->text_list_5_head) != 0) {
    next_node = *(u32 *)((*(u32 *)&((PictureWindow *)this)->text_list_5_head) + 8);
    if (*(int *)(*(u32 *)&((PictureWindow *)this)->text_list_5_head) != 0) {
      operator_delete(*(void **)(*(u32 *)&((PictureWindow *)this)->text_list_5_head));
    }
    operator_delete((void *)(*(u32 *)&((PictureWindow *)this)->text_list_5_head));
    (*(u32 *)&((PictureWindow *)this)->text_list_5_head) = next_node;
  }
  while ((*(u32 *)&((PictureWindow *)this)->text_list_6_head) != 0) {
    next_node = *(u32 *)((*(u32 *)&((PictureWindow *)this)->text_list_6_head) + 8);
    if (*(int *)(*(u32 *)&((PictureWindow *)this)->text_list_6_head) != 0) {
      operator_delete(*(void **)(*(u32 *)&((PictureWindow *)this)->text_list_6_head));
    }
    operator_delete((void *)(*(u32 *)&((PictureWindow *)this)->text_list_6_head));
    (*(u32 *)&((PictureWindow *)this)->text_list_6_head) = next_node;
  }
  return;
}

/* 004f4b9f auto */
#define panel_margin_x (*(int *)((u8 *)&g.d_0062d858))
#define scroll_parent (*(u8 * *)(frame_ + FRAME_OFF(4)))
#define edit_parent (*(u8 * *)(frame_ + FRAME_OFF(8)))
#define parent_16 (*(u8 * *)(frame_ + FRAME_OFF(12)))
#define parent_15 (*(u8 * *)(frame_ + FRAME_OFF(16)))
#define parent_14 (*(u8 * *)(frame_ + FRAME_OFF(20)))
#define parent_13 (*(u8 * *)(frame_ + FRAME_OFF(24)))
#define parent_12 (*(u8 * *)(frame_ + FRAME_OFF(28)))
#define parent_11 (*(u8 * *)(frame_ + FRAME_OFF(32)))
#define parent_10 (*(u8 * *)(frame_ + FRAME_OFF(36)))
#define parent_9 (*(u8 * *)(frame_ + FRAME_OFF(40)))
#define parent_8 (*(u8 * *)(frame_ + FRAME_OFF(44)))
#define parent_7 (*(u8 * *)(frame_ + FRAME_OFF(48)))
#define parent_6 (*(u8 * *)(frame_ + FRAME_OFF(52)))
#define parent_5 (*(u8 * *)(frame_ + FRAME_OFF(56)))
#define parent_4 (*(u8 * *)(frame_ + FRAME_OFF(60)))
#define parent_3 (*(u8 * *)(frame_ + FRAME_OFF(64)))
#define parent_2 (*(u8 * *)(frame_ + FRAME_OFF(68)))
#define close_parent (*(u8 * *)(frame_ + FRAME_OFF(72)))
#define close_hotspot (*(u32 *)(frame_ + FRAME_OFF(76)))
#define rect (*(tagRECT *)(frame_ + FRAME_OFF(108)))
#define btn_height (*(int *)(frame_ + FRAME_OFF(124)))
#define exc_link (*(i32 *)(frame_ + FRAME_OFF(128)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(132)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(136)))
void __thiscall pedia_window_create(DocumentWindow *this)

{
  int left_x;
  int col_width;
  u32 panel_h;
  Control *this_00;
  int avail_width;
  iptr label;
  int yTop;
  i8 frame_[FRAME_OFF(144)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  pedia_free_lists((WindowObjectView *)this);
  pedia_clear_links((WindowObjectView *)this);
  this->client_y = 0;
  if ((*(u32 *)&((PictureWindow *)this)->close_box_hotspot) != 0) {
    if ((Hotspot *)(*(u32 *)&((PictureWindow *)this)->close_box_hotspot) != (Hotspot *)0x0) {
      hotspot_scalar_dtor((Hotspot *)(*(u32 *)&((PictureWindow *)this)->close_box_hotspot),1);
    }
    (*(u32 *)&((PictureWindow *)this)->close_box_hotspot) = 0;
  }
  this->panel_width = 0x280;
  this->panel_height = 400;
  left_x = font_cached_height((GameFont *)&font_size30);
  this->header_height = left_x + panel_bevel_width * 2 + panel_margin_y * 2;
  SetRect((LPRECT)this->pedia_frame_rect,0,0,this->panel_width,this->panel_height);
  panel_h = this->panel_height;
  left_x = this->header_height + panel_margin_y;
  col_width = font_line_spacing((GameFont *)&font_size24);
  SetRect((LPRECT)&this->content_left,0,0,this->panel_width + (panel_padding_x + panel_margin_x) * -2,
          (panel_h - left_x) + ((panel_margin_y * -3 + panel_padding_y * -2) - col_width) + panel_bevel_width * -2);
  OffsetRect((LPRECT)&this->content_left,panel_padding_x + panel_margin_x,this->header_height + panel_margin_y);
  left_x = wnd_client_width((WndBase *)&main_frame_wnd);
  col_width = wnd_client_height((WndBase *)&main_frame_wnd);
  crt_strcpy(this->pedia_title_text_2,&pedia_window_empty_title_str);
  wnd_create_with_surface
            ((DibSurface *)this,0,0xe02,left_x / 2 - (int)this->panel_width / 2,
             col_width / 2 - (int)this->panel_height / 2,this->panel_width,this->panel_height,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)),ADDR(0x6553d8, ((u8 *)&g.d_006553d8)))
  ;
  wnd_set_close_handler((WndEventHandlers *)(this->event_handlers),ADDR(0x401dcf, pedia_close));
  wnd_set_redraw_callback((SurfaceWindow *)this,ADDR(0x40272a, pedia_redraw_page));
  wnd_set_caption_height((WndBase *)this->window_2,this->header_height);
  wnd_set_keydown_handler((WndEventHandlers *)(this->event_handlers),ADDR(0x4026bc, pedia_list_on_key));
  wnd_set_keyboard_nav((Wnd *)this->window_2,0);
  left_x = panel_padding_x;
  ((PictureWindow *)this)->close_box_sprite = (u32)&caption_close_button_sprite;
  ((PictureWindow *)this)->has_close_box = 1;
  panel_h = sprite_width((Sprite *)((PictureWindow *)this)->close_box_sprite);
  ((PictureWindow *)this)->close_box_width = panel_h;
  panel_h = sprite_height((Sprite *)((PictureWindow *)this)->close_box_sprite);
  ((PictureWindow *)this)->close_box_height = panel_h;
  btn_height = (int)(((PictureWindow *)this)->close_box_height * this->header_height) / 0x18;
  col_width = ((int)this->header_height >> 1) - (btn_height >> 1);
  SetRect(&rect,left_x,col_width,(int)(((PictureWindow *)this)->close_box_width * this->header_height) / 0x18 + left_x,
          btn_height + col_width);
  this_00 = operator_new(0x40);
  eh_state = 0;
  if (this_00 == (Control *)0x0) {
    close_hotspot = 0;
  }
  else {
    close_hotspot = hotspot_ctor(this_00);
  }
  eh_state = 0xffffffff;
  (*(u32 *)&((PictureWindow *)this)->close_box_hotspot) = close_hotspot;
  if (this == (DocumentWindow *)0x0) {
    close_parent = (u8 *)0x0;
  }
  else {
    close_parent = this->window_2;
  }
  hotspot_create
            ((ClickControl *)(*(u32 *)&((PictureWindow *)this)->close_box_hotspot),(iptr)close_parent,4000,(iptr)&rect);
  hotspot_set_click_callback((HotspotClickSetView *)(*(u32 *)&((PictureWindow *)this)->close_box_hotspot),ADDR(0x4037fb, pedia_on_close));
  left_x = panel_bevel_width + panel_margin_x + 2;
  panel_h = this->panel_height;
  col_width = font_line_spacing((GameFont *)&font_size24);
  yTop = panel_h - (col_width + (panel_margin_y + panel_padding_y) * 2);
  avail_width = this->panel_width - (panel_margin_x * 2 + panel_bevel_width * 2 + 5);
  btn_height = font_line_spacing((GameFont *)&font_size24);
  btn_height += panel_padding_y * 2;
  col_width = avail_width / 2;
  SetRect(&rect,left_x,yTop,col_width + left_x,btn_height + yTop);
  if (this == (DocumentWindow *)0x0) {
    parent_2 = (u8 *)0x0;
  }
  else {
    parent_2 = this->window_2;
  }
  label = label_string(*(i32 *)(label_string_ids + 0x9c));
  button_create
            ((Control *)((PictureWindow *)this)->list_describe_button,(iptr)parent_2,0xfa1,(iptr)&rect,label);
  button_set_callback((Control *)((PictureWindow *)this)->list_describe_button,ADDR(0x40196f, pedia_toggle_describe));
  SetRect(&rect,col_width + left_x,yTop,col_width * 2 + left_x,btn_height + yTop);
  if (this == (DocumentWindow *)0x0) {
    parent_3 = (u8 *)0x0;
  }
  else {
    parent_3 = this->window_2;
  }
  label = label_string(*(i32 *)(label_string_ids + 0x51c));
  button_create
            ((Control *)&((PictureWindow *)this)->list_close_button,(iptr)parent_3,0xfa2,(iptr)&rect,label);
  ctrl_set_default_button((Control *)&((PictureWindow *)this)->list_close_button);
  ctrl_set_cancel_button((Control *)&((PictureWindow *)this)->list_close_button);
  button_set_callback((Control *)&((PictureWindow *)this)->list_close_button,ADDR(0x4037fb, pedia_on_close));
  SetRect(&rect,left_x,yTop,avail_width / 2 + left_x,btn_height + yTop);
  if (this == (DocumentWindow *)0x0) {
    parent_4 = (u8 *)0x0;
  }
  else {
    parent_4 = this->window_2;
  }
  label = label_string(*(i32 *)(label_string_ids + 0xd58));
  button_create
            ((Control *)((u8 *)&((PictureWindow *)this)->concept_list_back_button),(iptr)parent_4,0xfb2,(iptr)&rect,label);
  button_set_callback((Control *)((u8 *)&((PictureWindow *)this)->concept_list_back_button),ADDR(0x4018ed, pedia_on_back));
  col_width = avail_width / 3;
  SetRect(&rect,left_x,yTop,col_width + left_x,btn_height + yTop);
  if (this == (DocumentWindow *)0x0) {
    parent_5 = (u8 *)0x0;
  }
  else {
    parent_5 = this->window_2;
  }
  label = label_string(*(i32 *)(label_string_ids + 0x9c));
  button_create
            ((Control *)((PictureWindow *)this)->advance_list_describe_button,(iptr)parent_5,0xfab,(iptr)&rect,label);
  button_set_callback((Control *)((PictureWindow *)this)->advance_list_describe_button,ADDR(0x40196f, pedia_toggle_describe));
  SetRect(&rect,col_width + left_x,yTop,col_width * 2 + left_x,btn_height + yTop);
  if (this == (DocumentWindow *)0x0) {
    parent_6 = (u8 *)0x0;
  }
  else {
    parent_6 = this->window_2;
  }
  label = label_string(*(i32 *)(label_string_ids + 0xd80));
  button_create
            ((Control *)(((PictureWindow *)this)->advance_list_tech_tree_button),(iptr)parent_6,0xfac,(iptr)&rect,label);
  button_set_callback((Control *)(((PictureWindow *)this)->advance_list_tech_tree_button),ADDR(0x401ec4, pedia_show_tech_tree));
  SetRect(&rect,col_width * 2 + left_x,yTop,col_width * 3 + left_x,btn_height + yTop);
  if (this == (DocumentWindow *)0x0) {
    parent_7 = (u8 *)0x0;
  }
  else {
    parent_7 = this->window_2;
  }
  label = label_string(*(i32 *)(label_string_ids + 0x51c));
  button_create
            ((Control *)(((PictureWindow *)this)->advance_list_close_button),(iptr)parent_7,0xfad,(iptr)&rect,label);
  ctrl_set_default_button((Control *)(((PictureWindow *)this)->advance_list_close_button));
  ctrl_set_cancel_button((Control *)(((PictureWindow *)this)->advance_list_close_button));
  button_set_callback((Control *)(((PictureWindow *)this)->advance_list_close_button),ADDR(0x4037fb, pedia_on_close));
  col_width = (int)(avail_width + (avail_width >> 0x1f & 3U)) >> 2;
  SetRect(&rect,left_x,yTop,col_width + left_x,btn_height + yTop);
  if (this == (DocumentWindow *)0x0) {
    parent_8 = (u8 *)0x0;
  }
  else {
    parent_8 = this->window_2;
  }
  label = label_string(*(i32 *)(label_string_ids + 0xd58));
  button_create
            ((Control *)((u8 *)&((PictureWindow *)this)->advance_detail_back_button),(iptr)parent_8,0xfae,(iptr)&rect,label);
  button_set_callback((Control *)((u8 *)&((PictureWindow *)this)->advance_detail_back_button),ADDR(0x4018ed, pedia_on_back));
  SetRect(&rect,col_width + left_x,yTop,col_width * 2 + left_x,btn_height + yTop);
  if (this == (DocumentWindow *)0x0) {
    parent_9 = (u8 *)0x0;
  }
  else {
    parent_9 = this->window_2;
  }
  label = label_string(*(i32 *)(label_string_ids + 0xd80));
  button_create
            ((Control *)((u8 *)&((PictureWindow *)this)->advance_detail_tech_tree_button),(iptr)parent_9,0xfaf,(iptr)&rect,label);
  button_set_callback((Control *)((u8 *)&((PictureWindow *)this)->advance_detail_tech_tree_button),ADDR(0x401ec4, pedia_show_tech_tree));
  SetRect(&rect,col_width * 2 + left_x,yTop,col_width * 3 + left_x,btn_height + yTop);
  if (this == (DocumentWindow *)0x0) {
    parent_10 = (u8 *)0x0;
  }
  else {
    parent_10 = this->window_2;
  }
  label = label_string(*(i32 *)(label_string_ids + 0xb04));
  button_create
            ((Control *)(((PictureWindow *)this)->advance_detail_describe_button),(iptr)parent_10,0xfb0,(iptr)&rect,label);
  button_set_callback((Control *)(((PictureWindow *)this)->advance_detail_describe_button),ADDR(0x40196f, pedia_toggle_describe));
  SetRect(&rect,col_width * 3 + left_x,yTop,col_width * 4 + left_x,btn_height + yTop);
  if (this == (DocumentWindow *)0x0) {
    parent_11 = (u8 *)0x0;
  }
  else {
    parent_11 = this->window_2;
  }
  label = label_string(*(i32 *)(label_string_ids + 0x51c));
  button_create
            ((Control *)((u8 *)&((PictureWindow *)this)->advance_detail_close_button),(iptr)parent_11,0xfb1,(iptr)&rect,label);
  ctrl_set_default_button((Control *)((u8 *)&((PictureWindow *)this)->advance_detail_close_button));
  ctrl_set_cancel_button((Control *)((u8 *)&((PictureWindow *)this)->advance_detail_close_button));
  button_set_callback((Control *)((u8 *)&((PictureWindow *)this)->advance_detail_close_button),ADDR(0x4037fb, pedia_on_close));
  col_width = avail_width / 3;
  SetRect(&rect,left_x,yTop,col_width + left_x,btn_height + yTop);
  if (this == (DocumentWindow *)0x0) {
    parent_12 = (u8 *)0x0;
  }
  else {
    parent_12 = this->window_2;
  }
  label = label_string(*(i32 *)(label_string_ids + 0xd58));
  button_create
            ((Control *)&((PictureWindow *)this)->detail_back_button,(iptr)parent_12,0xfa3,(iptr)&rect,label);
  button_set_callback((Control *)&((PictureWindow *)this)->detail_back_button,ADDR(0x4018ed, pedia_on_back));
  SetRect(&rect,col_width + left_x,yTop,col_width * 2 + left_x,btn_height + yTop);
  if (this == (DocumentWindow *)0x0) {
    parent_13 = (u8 *)0x0;
  }
  else {
    parent_13 = this->window_2;
  }
  label = label_string(*(i32 *)(label_string_ids + 0xb04));
  button_create
            ((Control *)(((PictureWindow *)this)->detail_describe_button),(iptr)parent_13,0xfa4,(iptr)&rect,label);
  button_set_callback((Control *)(((PictureWindow *)this)->detail_describe_button),ADDR(0x40196f, pedia_toggle_describe));
  SetRect(&rect,col_width * 2 + left_x,yTop,col_width * 3 + left_x,btn_height + yTop);
  if (this == (DocumentWindow *)0x0) {
    parent_14 = (u8 *)0x0;
  }
  else {
    parent_14 = this->window_2;
  }
  label = label_string(*(i32 *)(label_string_ids + 0x51c));
  button_create
            ((Control *)&((PictureWindow *)this)->detail_close_button,(iptr)parent_14,0xfa5,(iptr)&rect,label);
  button_set_callback((Control *)&((PictureWindow *)this)->detail_close_button,ADDR(0x4037fb, pedia_on_close));
  avail_width = avail_width / 2;
  SetRect(&rect,left_x,yTop,avail_width + left_x,btn_height + yTop);
  if (this == (DocumentWindow *)0x0) {
    parent_15 = (u8 *)0x0;
  }
  else {
    parent_15 = this->window_2;
  }
  label = label_string(*(i32 *)(label_string_ids + 0xd58));
  button_create
            ((Control *)(((PictureWindow *)this)->text_back_button),(iptr)parent_15,0xfa6,(iptr)&rect,label);
  button_set_callback((Control *)(((PictureWindow *)this)->text_back_button),ADDR(0x4018ed, pedia_on_back));
  SetRect(&rect,avail_width + left_x,yTop,avail_width * 2 + left_x,btn_height + yTop);
  if (this == (DocumentWindow *)0x0) {
    parent_16 = (u8 *)0x0;
  }
  else {
    parent_16 = this->window_2;
  }
  label = label_string(*(i32 *)(label_string_ids + 0x51c));
  button_create
            ((Control *)((u8 *)&((PictureWindow *)this)->text_close_button),(iptr)parent_16,0xfa7,(iptr)&rect,label);
  button_set_callback((Control *)((u8 *)&((PictureWindow *)this)->text_close_button),ADDR(0x4037fb, pedia_on_close));
  ui_set_button_font(ADDR(0x68abe0, ((u8 *)&g.d_0068abe0)));
  pedia_clear_links((WindowObjectView *)this);
  ui_set_default_font(ADDR(0x67a798, ((u8 *)&g.d_0067a798)));
  if (this == (DocumentWindow *)0x0) {
    edit_parent = (u8 *)0x0;
  }
  else {
    edit_parent = this->window_2;
  }
  edit_create_styled
            ((EditControl *)((u8 *)&((PictureWindow *)this)->description_edit),(iptr)edit_parent,0xfaa,(iptr)&this->content_left,
             ADDR(0x62f01c, ((u8 *)&g.d_0062f01c)),0x122,0);
  rect.left = this->content_left;
  rect.top = this->content_top;
  rect.right = this->content_right;
  panel_h = this->content_bottom;
  rect.bottom = panel_h;
  left_x = GetSystemMetrics(3);
  rect.top = panel_h - left_x;
  if (this == (DocumentWindow *)0x0) {
    scroll_parent = (u8 *)0x0;
  }
  else {
    scroll_parent = this->window_2;
  }
  scrollbar_create
            ((Control *)((u8 *)&((PictureWindow *)this)->list_scrollbar),(iptr)scroll_parent,0xfa8,(iptr)&rect,0);
  scrollbar_set_callback((Control *)((u8 *)&((PictureWindow *)this)->list_scrollbar),ADDR(0x403c51, pedia_list_on_scroll));
  scrollbar_set_track_callback((ScrollbarTrackSetView *)((u8 *)&((PictureWindow *)this)->list_scrollbar),ADDR(0x403c51, pedia_list_on_scroll));
  scrollbar_set_page_size((Control *)((u8 *)&((PictureWindow *)this)->list_scrollbar),2);
  pedia_load_indexes(this);
  return;
}
#undef panel_margin_x
#undef scroll_parent
#undef edit_parent
#undef parent_16
#undef parent_15
#undef parent_14
#undef parent_13
#undef parent_12
#undef parent_11
#undef parent_10
#undef parent_9
#undef parent_8
#undef parent_7
#undef parent_6
#undef parent_5
#undef parent_4
#undef parent_3
#undef parent_2
#undef close_parent
#undef close_hotspot
#undef rect
#undef btn_height
#undef exc_link
#undef seh_handler
#undef eh_state

/* 004f5b24 auto */
#define pedia_history_count (*(i32 *)((u8 *)&g.d_006a6790))
void __cdecl pedia_on_close(void)

{
  if (pedia_modal_active == 1) {
    wnd_end_modal_loop((ModalMenuWindow *)&pedia_window_wnd);
    pedia_modal_active = 0;
  }
  pedia_clear_links((WindowObjectView *)&pedia_window);
  pedia_history_count = 0;
  pedia_close();
  return;
}
#undef pedia_history_count

/* 004f5b6f auto */
#define pedia_back_topic (*(i32 *)((u8 *)&g.d_0062f010))
#define pedia_category (*(int *)((u8 *)&g.d_006a6780))
#define pedia_going_back (*(i32 *)((u8 *)&g.d_0062f00c))
#define pedia_history_count (*(int *)((u8 *)&g.d_006a6790))
#define pedia_page_mode (*(int *)((u8 *)&g.d_006a6784))
#define pedia_selected_item (*(int *)((u8 *)&g.d_006a85a0))
#define pedia_topic (*(int *)((u8 *)&g.d_006a6788))
void __cdecl pedia_on_back(void)

{
  if (pedia_history_count != 0) {
    do {
      pedia_history_count--;
      if (((pedia_history_count == 0) || (*(int *)(&pedia_history_categories + pedia_history_count * 4) != pedia_category)) ||
         (*(int *)(&pedia_history_page_modes + pedia_history_count * 4) != pedia_page_mode)) break;
    } while (*(int *)(&pedia_history_topics + pedia_history_count * 4) == pedia_topic);
    if (pedia_history_count != 0) {
      pedia_going_back = 1;
      pedia_back_topic = *(i32 *)(&pedia_history_topics + pedia_history_count * 4);
      pedia_popped_page_mode = *(i32 *)(&pedia_history_page_modes + pedia_history_count * 4);
      pedia_popped_category = *(i32 *)(&pedia_history_categories + pedia_history_count * 4);
    }
    if (*(int *)(&pedia_history_page_modes + pedia_history_count * 4) != 0) {
      pedia_category = *(int *)(&pedia_history_categories + pedia_history_count * 4);
      pedia_page_mode = *(int *)(&pedia_history_page_modes + pedia_history_count * 4) - 1;
      pedia_topic = *(int *)(&pedia_history_topics + pedia_history_count * 4);
      pedia_selected_item = pedia_topic;
      pedia_toggle_describe(1);
      return;
    }
    pedia_category = *(int *)(&pedia_history_categories + pedia_history_count * 4);
    pedia_page_mode = 1;
    pedia_topic = *(int *)(&pedia_history_topics + pedia_history_count * 4);
    pedia_selected_item = pedia_topic;
  }
  if (pedia_page_mode == 0) {
    if (pedia_modal_active == 1) {
      wnd_end_modal_loop((ModalMenuWindow *)&pedia_window_wnd);
      pedia_modal_active = 0;
    }
    pedia_close();
  }
  else {
    if (pedia_page_mode == 1) {
      pedia_page_mode = 0;
      pedia_update_controls((MediaWindow *)&pedia_window);
      pedia_redraw_page();
      pedia_selected_item = pedia_topic;
      pedia_redraw((PediaRedrawView *)&pedia_window);
    }
    else if ((pedia_category == 6) || (pedia_category == 7)) {
      pedia_page_mode = 0;
      pedia_update_controls((MediaWindow *)&pedia_window);
      pedia_redraw_page();
      pedia_selected_item = pedia_topic;
      pedia_redraw((PediaRedrawView *)&pedia_window);
    }
    else {
      pedia_page_mode = 0;
      pedia_toggle_describe(1);
    }
    pedia_history_push((ScaledWindowView *)&pedia_window);
  }
  return;
}
#undef pedia_back_topic
#undef pedia_category
#undef pedia_going_back
#undef pedia_history_count
#undef pedia_page_mode
#undef pedia_selected_item
#undef pedia_topic

/* 004f5dd1 auto */
#define pedia_closed (*(i32 *)((u8 *)&g.d_006a677c))
#define pedia_history_count (*(i32 *)((u8 *)&g.d_006a6790))
i32 __cdecl pedia_close(void)

{
  pedia_closed = 1;
  pedia_history_count = 0;
  if (pedia_close_hotspot != (Hotspot *)0x0) {
    if (pedia_close_hotspot != (Hotspot *)0x0) {
      hotspot_scalar_dtor(pedia_close_hotspot,1);
    }
    pedia_close_hotspot = (Hotspot *)0x0;
  }
  wnd_hide((WndBase *)&pedia_window_wnd);
  wnd_focus_and_raise((WndBase *)&main_frame_wnd);
  ui_flush_input();
  return 0;
}
#undef pedia_closed
#undef pedia_history_count

/* 004f5e52 auto */
#define pedia_category (*(i32 *)((u8 *)&g.d_006a6780))
#define pedia_closed (*(int *)((u8 *)&g.d_006a677c))
#define pedia_page_mode (*(int *)((u8 *)&g.d_006a6784))
void __cdecl pedia_redraw_page(void)

{
  if (pedia_closed == 0) {
    if (pedia_page_mode == 0) {
      pedia_set_category_title((WindowObjectView *)&pedia_window,pedia_category);
    }
    pedia_clear_links((WindowObjectView *)&pedia_window);
    gfx_set_draw_target(ADDR(0x6a6668, ((u8 *)&g.d_006a6668)));
    pedia_draw_frame((MediaWindow *)&pedia_window);
    pedia_draw_category_body((DocumentWindow *)&pedia_window,pedia_category,pedia_page_mode);
    wnd_blit_surface((DibSurface *)&pedia_window);
  }
  return;
}
#undef pedia_category
#undef pedia_closed
#undef pedia_page_mode

/* 004f5ed2 auto */
#define pedia_category (*(i32 *)((u8 *)&g.d_006a6780))
#define pedia_page_mode (*(i32 *)((u8 *)&g.d_006a6784))
#define pedia_selected_item (*(i32 *)((u8 *)&g.d_006a85a0))
#define pedia_topic (*(i32 *)((u8 *)&g.d_006a6788))
void __cdecl pedia_show_tech_tree(void)

{
  pedia_page_mode = 0;
  pedia_category = 8;
  pedia_update_controls((MediaWindow *)&pedia_window);
  pedia_redraw_page();
  pedia_selected_item = pedia_topic;
  pedia_redraw((PediaRedrawView *)&pedia_window);
  pedia_history_push((ScaledWindowView *)&pedia_window);
  return;
}
#undef pedia_category
#undef pedia_page_mode
#undef pedia_selected_item
#undef pedia_topic

/* 004f5f23 auto */
#define pedia_advance_names (*(i32 *)((u8 *)&g.d_006a7d44))
#define pedia_category (*(i32 *)((u8 *)&g.d_006a6780))
#define pedia_concept_names (*(i32 *)((u8 *)&g.d_006a7d5c))
#define pedia_government_names (*(i32 *)((u8 *)&g.d_006a7d54))
#define pedia_improvement_names (*(i32 *)((u8 *)&g.d_006a7d48))
#define pedia_page_mode (*(int *)((u8 *)&g.d_006a6784))
#define pedia_selected_item (*(uptr *)((u8 *)&g.d_006a85a0))
#define pedia_terrain_names (*(i32 *)((u8 *)&g.d_006a7d58))
#define pedia_topic (*(uptr *)((u8 *)&g.d_006a6788))
#define pedia_unit_names (*(i32 *)((u8 *)&g.d_006a7d50))
#define pedia_wonder_names (*(i32 *)((u8 *)&g.d_006a7d4c))
void __cdecl pedia_toggle_describe(i32 unused_arg)

{
  i32 title;
  uptr item;
  
  item = pedia_selected_item;
  if (pedia_page_mode == 0) {
    pedia_topic = pedia_selected_item;
    pedia_page_mode = 1;
    pedia_clear_links((WindowObjectView *)&pedia_window);
    pedia_update_controls((MediaWindow *)&pedia_window);
    switch(pedia_category) {
    case 1:
    case 8:
      title = pedia_lookup_text(pedia_advance_names,item);
      crt_strcpy(&pedia_title_text,title);
      pedia_draw_frame((MediaWindow *)&pedia_window);
      pedia_draw_advance_page((DocumentWindow *)&pedia_window);
      break;
    case 2:
      title = pedia_lookup_text(pedia_improvement_names,item);
      crt_strcpy(&pedia_title_text,title);
      pedia_draw_frame((MediaWindow *)&pedia_window);
      pedia_draw_improvement_page((DocumentWindow *)&pedia_window);
      break;
    case 3:
      title = pedia_lookup_text(pedia_wonder_names,item);
      crt_strcpy(&pedia_title_text,title);
      pedia_draw_frame((MediaWindow *)&pedia_window);
      pedia_draw_improvement((DocumentWindow *)&pedia_window);
      break;
    case 4:
      title = pedia_lookup_text(pedia_unit_names,item);
      crt_strcpy(&pedia_title_text,title);
      pedia_draw_frame((MediaWindow *)&pedia_window);
      pedia_draw_unit_page((DocumentWindow *)&pedia_window);
      break;
    case 5:
      title = pedia_lookup_text(pedia_terrain_names,item);
      crt_strcpy(&pedia_title_text,title);
      pedia_draw_frame((MediaWindow *)&pedia_window);
      pedia_draw_terrain_page((DocumentWindow *)&pedia_window);
      break;
    case 6:
      pedia_page_mode = 2;
      title = pedia_lookup_text(pedia_government_names,item);
      crt_strcpy(&pedia_title_text,title);
      pedia_draw_frame((MediaWindow *)&pedia_window);
      pedia_fill_background((WindowObjectView *)&pedia_window,ADDR(0x6a6c60, ((u8 *)&g.d_006a6c60)),1);
      pedia_load_description((WindowObjectView *)&pedia_window,item);
      break;
    case 7:
      pedia_page_mode = 2;
      title = pedia_lookup_text(pedia_concept_names,item);
      crt_strcpy(&pedia_title_text,title);
      pedia_draw_frame((MediaWindow *)&pedia_window);
      pedia_fill_background((WindowObjectView *)&pedia_window,ADDR(0x6a6c60, ((u8 *)&g.d_006a6c60)),1);
      pedia_load_description((WindowObjectView *)&pedia_window,item);
      break;
    default:
      text_append(ADDR(0x62f020, ((u8 *)&g.d_0062f020)));
    }
    wnd_blit_surface((DibSurface *)&pedia_window);
  }
  else if (pedia_page_mode == 1) {
    pedia_page_mode = 2;
    pedia_clear_links((WindowObjectView *)&pedia_window);
    pedia_update_controls((MediaWindow *)&pedia_window);
    pedia_draw_frame((MediaWindow *)&pedia_window);
    pedia_fill_background((WindowObjectView *)&pedia_window,ADDR(0x6a6c60, ((u8 *)&g.d_006a6c60)),0);
    pedia_load_description((WindowObjectView *)&pedia_window,item);
  }
  pedia_history_push((ScaledWindowView *)&pedia_window);
  return;
}
#undef pedia_advance_names
#undef pedia_category
#undef pedia_concept_names
#undef pedia_government_names
#undef pedia_improvement_names
#undef pedia_page_mode
#undef pedia_selected_item
#undef pedia_terrain_names
#undef pedia_topic
#undef pedia_unit_names
#undef pedia_wonder_names

/* 004f6244 auto */
#define dlg_bevel_dark_color (*(byte *)((u8 *)&g.d_00635a0c))
#define dlg_bevel_light_color (*(byte *)((u8 *)&g.d_00635a08))
#define panel_margin_x (*(i32 *)((u8 *)&g.d_0062d858))
#define sprite_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define y2 (*(int *)(frame_ + FRAME_OFF(20)))
#define x2 (*(int *)(frame_ + FRAME_OFF(24)))
#define font2 (*(i8 * *)(frame_ + FRAME_OFF(28)))
#define i (*(int *)(frame_ + FRAME_OFF(32)))
#define rect (*(tagRECT *)(frame_ + FRAME_OFF(36)))
void __thiscall pedia_draw_frame(MediaWindow *this)

{
  int tmp_a;
  int tmp_b;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  surface_reset_clip((DibSurface *)this);
  crt_memcpy(&rect,this->pedia_frame_rect,0x10);
  for (i = 0; i < panel_bevel_width; i++) {
    gfx_draw_bevel_rect((iptr)this,(iptr)&rect,(uint)dlg_bevel_light_color,(uint)dlg_bevel_dark_color);
    rect_deflate((iptr)&rect,1,1);
  }
  pedia_fill_background((WindowObjectView *)this,(iptr)&rect,1);
  rect_deflate((iptr)&rect,panel_padding_x + panel_bevel_width * -2,0);
  rect.top = rect.top + this->header_height + panel_bevel_width * -2;
  tmp_a = rect_height((iptr)this->pedia_frame_rect);
  tmp_b = font_line_spacing((GameFont *)&font_size24);
  rect.bottom = tmp_a + ((panel_margin_y * -3 + panel_padding_y * -2) - tmp_b);
  for (i = 0; i < panel_bevel_width; i++) {
    gfx_draw_bevel_rect((iptr)this,(iptr)&rect,(uint)dlg_bevel_dark_color,(uint)dlg_bevel_light_color);
    rect_deflate((iptr)&rect,1,1);
  }
  pedia_fill_background((WindowObjectView *)this,(iptr)&rect,2);
  tmp_a = panel_padding_x;
  x2 = panel_padding_x;
  this->panel_width = (int)(*(int *)((u8 *)&((PictureWindow *)this)->close_box_width) * this->header_height) / 0x18;
  this->panel_height = (int)(*(int *)((u8 *)&((PictureWindow *)this)->close_box_height) * this->header_height) / 0x18;
  y2 = ((int)this->header_height >> 1) - ((int)this->panel_height >> 1);
  SetRect(&rect,tmp_a,y2,this->panel_width + tmp_a,this->panel_height + y2);
  gfx_set_scale_ratio(this->header_height,0x18);
  sprite_draw
            (*(Sprite **)((u8 *)&((PictureWindow *)this)->close_box_sprite),(iptr)sprite_ctx,(iptr)this,x2,y2
            );
  gfx_reset_zoom_scale();
  x2 += this->panel_width;
  font2 = &font_size30;
  tmp_a = (this->frame_rect_right - x2) - panel_padding_x;
  tmp_b = font_text_width
                    ((GameFont *)&font_size30,(iptr)(this->pedia_title_text_2));
  x2 += (tmp_a / 2 - (tmp_b >> 1));
  y2 = panel_bevel_width + panel_margin_y;
  gfx_set_text_color_index(10);
  surface_draw_text
            ((DibSurface *)this,(iptr)font2,(iptr)(this->pedia_title_text_2),x2 + 2,
             y2 + 1,5);
  gfx_set_text_color_index(0x1a);
  surface_draw_text
            ((DibSurface *)this,(iptr)font2,(iptr)(this->pedia_title_text_2),x2 + 1,y2
             ,5);
  surface_draw_text
            ((DibSurface *)this,(iptr)font2,(iptr)(this->pedia_title_text_2),x2,y2,5);
  surface_set_clip((DibSurface *)this,(iptr)&this->content_left);
  return;
}
#undef dlg_bevel_dark_color
#undef dlg_bevel_light_color
#undef panel_margin_x
#undef sprite_ctx
#undef y2
#undef x2
#undef font2
#undef i
#undef rect

/* 004f6564 auto */
#define dlg_bg_color (*(byte *)((u8 *)&g.d_00635a04))
#define dlg_client_tile_surface (*(int *)((u8 *)&g.d_00635aa4))
#define dlg_frame_tile_surface (*(int *)((u8 *)&g.d_00635aa0))
void __thiscall pedia_fill_background(WindowObjectView *this,iptr rect,int style)

{
  i32 height;
  i32 width;
  i32 offset_x;
  i32 offset_y;
  
  if ((dlg_frame_tile_surface == 0) || (style != 1)) {
    if ((dlg_client_tile_surface == 0) || (style != 2)) {
      gfx_fill_rect((iptr)this,rect,(uint)dlg_bg_color);
    }
    else {
      offset_y = 0;
      offset_x = 0;
      height = rect_height(rect);
      width = rect_width(rect);
      gfx_tile_fill((iptr)this,dlg_client_tile_surface,*(i32 *)rect,*(i32 *)(rect + 4)
                         ,width,height,offset_x,offset_y);
    }
  }
  else {
    offset_y = 0;
    offset_x = 0;
    height = rect_height(rect);
    width = rect_width(rect);
    gfx_tile_fill((iptr)this,dlg_frame_tile_surface,*(i32 *)rect,*(i32 *)(rect + 4),
                       width,height,offset_x,offset_y);
  }
  return;
}
#undef dlg_bg_color
#undef dlg_client_tile_surface
#undef dlg_frame_tile_surface

/* 004f6646 auto */
void __thiscall pedia_redraw(PediaRedrawView *this)

{
  u32 page_mode;
  
  page_mode = this->border_width;
  if (page_mode == 0) {
    if (this->caption_height != 8) {
      pedia_draw_item_list((ListPaneWindow *)this);
    }
  }
  else if ((page_mode != 1) && (page_mode != 2)) {
    pedia_close();
  }
  return;
}

/* 004f66c6 auto */
#define dlg_sel_text_color (*(int *)((u8 *)&g.d_00635a28))
#define dlg_sel_text_shadow_color (*(int *)((u8 *)&g.d_00635a2c))
#define list_bg_color (*(i32 *)((u8 *)&g.d_00635a18))
#define list_sel_bg_color (*(i32 *)((u8 *)&g.d_00635a24))
#define list_shadow_color (*(int *)((u8 *)&g.d_00635a20))
#define list_text_color (*(int *)((u8 *)&g.d_00635a1c))
#define panel_margin_x (*(int *)((u8 *)&g.d_0062d858))
#define pedia_advance_names (*(i32 *)((u8 *)&g.d_006a7d44))
#define pedia_concept_names (*(i32 *)((u8 *)&g.d_006a7d5c))
#define pedia_government_names (*(i32 *)((u8 *)&g.d_006a7d54))
#define pedia_improvement_names (*(i32 *)((u8 *)&g.d_006a7d48))
#define pedia_selected_item (*(int *)((u8 *)&g.d_006a85a0))
#define pedia_terrain_names (*(i32 *)((u8 *)&g.d_006a7d58))
#define pedia_unit_names (*(i32 *)((u8 *)&g.d_006a7d50))
#define pedia_wonder_names (*(i32 *)((u8 *)&g.d_006a7d4c))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define fill_color_e (*(i32 *)(frame_ + FRAME_OFF(4)))
#define fill_color_d (*(i32 *)(frame_ + FRAME_OFF(8)))
#define shield_x (*(int *)(frame_ + FRAME_OFF(12)))
#define fill_color_c (*(i32 *)(frame_ + FRAME_OFF(16)))
#define icon_x2 (*(int *)(frame_ + FRAME_OFF(20)))
#define fill_color_b (*(i32 *)(frame_ + FRAME_OFF(24)))
#define fill_color_a (*(i32 *)(frame_ + FRAME_OFF(28)))
#define terrain_fill_color (*(i32 *)(frame_ + FRAME_OFF(32)))
#define shield_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(36)))
#define icon_ctx2 (*(i8 (*)[16])(frame_ + FRAME_OFF(52)))
#define icon_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(68)))
#define resource_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(84)))
#define hill_ctx2 (*(i8 (*)[16])(frame_ + FRAME_OFF(100)))
#define forest_ctx2 (*(i8 (*)[16])(frame_ + FRAME_OFF(116)))
#define grass_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(132)))
#define mountain_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(148)))
#define hill_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(164)))
#define forest_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(180)))
#define base_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(196)))
#define text_y_off (*(int *)(frame_ + FRAME_OFF(212)))
#define advance (*(iptr *)(frame_ + FRAME_OFF(216)))
#define col_width (*(int *)(frame_ + FRAME_OFF(220)))
#define base_terrain (*(int *)(frame_ + FRAME_OFF(224)))
#define icon_x (*(int *)(frame_ + FRAME_OFF(228)))
#define scale_num2 (*(i32 *)(frame_ + FRAME_OFF(232)))
#define col (*(int *)(frame_ + FRAME_OFF(236)))
#define col_base (*(int *)(frame_ + FRAME_OFF(240)))
#define row (*(int *)(frame_ + FRAME_OFF(244)))
#define row_y (*(int *)(frame_ + FRAME_OFF(248)))
#define scale_den2 (*(i32 *)(frame_ + FRAME_OFF(252)))
#define col_x (*(int *)(frame_ + FRAME_OFF(256)))
#define list_width2 (*(int *)(frame_ + FRAME_OFF(260)))
#define shadow_color2 (*(int *)(frame_ + FRAME_OFF(264)))
#define resource_variant (*(uint *)(frame_ + FRAME_OFF(268)))
#define text_x_off (*(int *)(frame_ + FRAME_OFF(272)))
#define icon_mode (*(int *)(frame_ + FRAME_OFF(276)))
#define icon_sprite (*(Sprite * *)(frame_ + FRAME_OFF(280)))
#define text_color2 (*(int *)(frame_ + FRAME_OFF(284)))
#define is_selected (*(uint *)(frame_ + FRAME_OFF(288)))
#define row_rect (*(tagRECT *)(frame_ + FRAME_OFF(292)))
#define row_height (*(int *)(frame_ + FRAME_OFF(308)))
#define saved_clip (*(i8 (*)[16])(frame_ + FRAME_OFF(312)))
#define font2 (*(GameFont * *)(frame_ + FRAME_OFF(328)))
void __thiscall pedia_draw_item_list(ListPaneWindow *this)

{
  int dim_a;
  int dim_b;
  int dim_c;
  i32 name_text;
  i8 frame_[FRAME_OFF(336)] __attribute__((aligned(8)));  /* original stack frame */
  
  icon_mode = 0;
  pedia_history_push((ScaledWindowView *)&pedia_window);
  surface_get_clip((DibSurface *)this,(iptr)saved_clip);
  surface_set_clip((DibSurface *)this,(iptr)((u8 *)&((PictureWindow *)this)->list_rect));
  surface_fill_rect((DibSurface *)this,(iptr)((u8 *)&((PictureWindow *)this)->list_rect),list_bg_color);
  font2 = (GameFont *)&font_size21;
  col_x = *(int *)((u8 *)&((PictureWindow *)this)->list_rect);
  list_width2 = rect_width((iptr)((u8 *)&((PictureWindow *)this)->list_rect));
  col_width = list_width2 / 2;
  row_height = rect_height((iptr)((u8 *)&((PictureWindow *)this)->list_rect));
  row_height = row_height / 9;
  dim_a = row_height / 2;
  dim_b = font_cached_height(font2);
  text_y_off = dim_a - dim_b / 2;
  col = 0;
  do {
    if (1 < col) {
      surface_set_clip((DibSurface *)this,(iptr)saved_clip);
      ctrl_show_and_redraw(*(Control **)((u8 *)&((PictureWindow *)this)->list_hotspot));
      return;
    }
    col_base = col * 9;
    for (row = 0; row < 9; row++) {
      row_y = *(int *)((u8 *)&((PictureWindow *)this)->list_rect_top) + row_height * row;
      SetRect(&row_rect,col_x,row_y,col_width + col_x - 2,row_height + row_y);
      if (((*(u32 *)&((PictureWindow *)this)->list_top_index) != 0xffffffff) &&
         ((int)((*(u32 *)&((PictureWindow *)this)->list_top_index) + col_base + row) < *(int *)(((PictureWindow *)this)->list_item_table))) {
        advance = *(iptr *)(((PictureWindow *)this)->list_scrollbar_body +
                            ((*(u32 *)&((PictureWindow *)this)->list_top_index) + col_base + row) * 4 + 0x50);
        is_selected = (uint)((*(u32 *)&((PictureWindow *)this)->list_top_index) + col_base + row == pedia_selected_item);
        if (is_selected == 0) {
          text_color2 = list_text_color;
          shadow_color2 = list_shadow_color;
        }
        else {
          text_color2 = dlg_sel_text_color;
          shadow_color2 = dlg_sel_text_shadow_color;
        }
        gfx_get_scale_ratio((iptr)&scale_num2,(iptr)&scale_den2);
        switch(this->caption_height) {
        case 1:
          icon_sprite = (Sprite *)
                     (&advance_category_icon_sprites +
                     (char)advances[advance].epoch * 0x3c +
                     (char)advances[advance].category * 0xf0);
          gfx_set_scale_ratio(3,2);
          icon_mode = 3;
          break;
        case 2:
          icon_sprite = (Sprite *)(&improvement_icon_sprites + advance * 0x3c);
          gfx_set_scale_ratio(3,2);
          icon_mode = 3;
          break;
        case 3:
          icon_sprite = (Sprite *)(&improvement_icon_sprites + advance * 0x3c);
          gfx_set_scale_ratio(3,2);
          icon_mode = 3;
          break;
        case 4:
          icon_sprite = (Sprite *)(&unit_sprites + advance * 0x3c);
          break;
        case 5:
          icon_mode = -5;
          base_terrain = advance % 0xb;
          if (((*(u32 *)&((PictureWindow *)this)->list_top_index) + col_base + row & 1) == 0) {
            icon_x = panel_margin_x;
          }
          else {
            dim_a = sprite_width((Sprite *)&forest_sprites);
            icon_x = panel_margin_x + dim_a / 2;
          }
          dim_a = sprite_width((Sprite *)&forest_sprites);
          text_x_off = panel_margin_x + (dim_a * 3) / 2 + 2;
          row_rect.left += text_x_off;
          if (is_selected == 0) {
            terrain_fill_color = list_bg_color;
          }
          else {
            terrain_fill_color = list_sel_bg_color;
          }
          surface_fill_rect((DibSurface *)this,(iptr)&row_rect,terrain_fill_color);
          sprite_draw
                    ((Sprite *)(&terrain_base_sprites + base_terrain * 0x3c),(iptr)base_ctx,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),
                     icon_x + col_x,row_y);
          if (advance < 0xb) {
            if (advance == 3) {
              sprite_draw
                        ((Sprite *)&forest_sprites,(iptr)forest_ctx,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),icon_x + col_x,
                         row_y);
            }
            else if (advance == 4) {
              sprite_draw
                        ((Sprite *)&hill_sprites,(iptr)hill_ctx,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),icon_x + col_x,
                         row_y);
            }
            else if (advance == 5) {
              sprite_draw
                        ((Sprite *)&mountain_sprites,(iptr)mountain_ctx,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),icon_x + col_x,
                         row_y);
            }
          }
          else {
            resource_variant = (uint)(0x15 < advance);
            switch(advance) {
            case 0xd:
            case 0x18:
              sprite_draw
                        ((Sprite *)&grassland_shield_sprite,(iptr)grass_ctx,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),icon_x + col_x,
                         row_y);
              goto LAB_004f6d04;
            case 0xe:
            case 0x19:
              sprite_draw
                        ((Sprite *)&forest_sprites,(iptr)forest_ctx2,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),icon_x + col_x,
                         row_y);
              break;
            case 0xf:
            case 0x1a:
              sprite_draw
                        ((Sprite *)&hill_sprites,(iptr)hill_ctx2,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),icon_x + col_x,
                         row_y);
              break;
            case 0x10:
            case 0x11:
            case 0x12:
            case 0x13:
            case 0x14:
            case 0x15:
            case 0x16:
            case 0x17: ;
            }
            sprite_draw
                      ((Sprite *)(&terrain_resource_sprites + base_terrain * 0x78 + resource_variant * 0x3c),
                       (iptr)resource_ctx,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),icon_x + col_x,row_y);
          }
          break;
        case 6:
        case 7:
          icon_mode = -2;
          break;
        default:
          text_append(ADDR(0x62f03c, ((u8 *)&g.d_0062f03c)));
        }
LAB_004f6d04:
        if (icon_mode == 3) {
          dim_a = sprite_width(icon_sprite);
          text_x_off = (dim_a * 3) / 2 + panel_margin_x * 2;
          row_rect.left += text_x_off;
          if (is_selected == 0) {
            fill_color_a = list_bg_color;
          }
          else {
            fill_color_a = list_sel_bg_color;
          }
          surface_fill_rect((DibSurface *)this,(iptr)&row_rect,fill_color_a);
          sprite_draw
                    (icon_sprite,(iptr)icon_ctx,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),panel_margin_x + col_x,row_rect.top + 1);
        }
        else if (icon_mode == 0) {
          dim_a = sprite_width(icon_sprite);
          text_x_off = panel_margin_x * 3 + dim_a * 2;
          row_rect.left += text_x_off;
          if (is_selected == 0) {
            fill_color_b = list_bg_color;
          }
          else {
            fill_color_b = list_sel_bg_color;
          }
          surface_fill_rect((DibSurface *)this,(iptr)&row_rect,fill_color_b);
          icon_x = sprite_width(icon_sprite);
          icon_x += panel_margin_x * 2;
          icon_x2 = icon_x;
          if (((*(u32 *)&((PictureWindow *)this)->list_top_index) + col_base + row & 1) == 0) {
            icon_x2 = panel_margin_x;
          }
          dim_b = row_y + row_height / 2;
          dim_a = sprite_get_height(icon_sprite);
          sprite_draw
                    (icon_sprite,(iptr)icon_ctx2,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),col_x + icon_x2,dim_b - dim_a / 2);
        }
        else if (icon_mode == 2) {
          dim_a = sprite_width(icon_sprite);
          text_x_off = panel_margin_x * 3 + dim_a * 2;
          row_rect.left += text_x_off;
          if (is_selected == 0) {
            fill_color_c = list_bg_color;
          }
          else {
            fill_color_c = list_sel_bg_color;
          }
          surface_fill_rect((DibSurface *)this,(iptr)&row_rect,fill_color_c);
          dim_a = sprite_width(icon_sprite);
          dim_b = sprite_width(icon_sprite);
          dim_c = sprite_width(icon_sprite);
          icon_x = ((int)(dim_a + (dim_a >> 0x1f & 3U)) >> 2) + dim_b / 6 + dim_c +
                     panel_margin_x * 2;
          icon_sprite = (Sprite *)&shield_icon_sprite;
          shield_x = icon_x;
          if (((*(u32 *)&((PictureWindow *)this)->list_top_index) + col_base + row & 1) == 0) {
            shield_x = panel_margin_x;
          }
          dim_b = row_y + row_height / 2;
          dim_a = sprite_get_height((Sprite *)&shield_icon_sprite);
          sprite_draw
                    (icon_sprite,(iptr)shield_ctx,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),col_x + shield_x,dim_b - dim_a / 2);
        }
        else if (icon_mode == -1) {
          dim_a = sprite_width(icon_sprite);
          text_x_off = panel_margin_x * 3 + dim_a * 2;
          row_rect.left += text_x_off;
          if (is_selected == 0) {
            fill_color_d = list_bg_color;
          }
          else {
            fill_color_d = list_sel_bg_color;
          }
          surface_fill_rect((DibSurface *)this,(iptr)&row_rect,fill_color_d);
        }
        else if (icon_mode != -5) {
          text_x_off = panel_margin_x * 5 + 2;
          row_rect.left += text_x_off;
          if (is_selected == 0) {
            fill_color_e = list_bg_color;
          }
          else {
            fill_color_e = list_sel_bg_color;
          }
          surface_fill_rect((DibSurface *)this,(iptr)&row_rect,fill_color_e);
        }
        icon_mode = 0;
        gfx_set_scale_ratio(scale_num2,scale_den2);
        text_clear();
        advance = (*(u32 *)&((PictureWindow *)this)->list_top_index) + col_base + row;
        switch(this->caption_height) {
        case 1:
          name_text = pedia_lookup_text(pedia_advance_names,advance);
          crt_strcpy(&text_buffer,name_text);
          break;
        case 2:
          name_text = pedia_lookup_text(pedia_improvement_names,advance);
          crt_strcpy(&text_buffer,name_text);
          break;
        case 3:
          name_text = pedia_lookup_text(pedia_wonder_names,advance);
          crt_strcpy(&text_buffer,name_text);
          break;
        case 4:
          name_text = pedia_lookup_text(pedia_unit_names,advance);
          crt_strcpy(&text_buffer,name_text);
          break;
        case 5:
          name_text = pedia_lookup_text(pedia_terrain_names,advance);
          crt_strcpy(&text_buffer,name_text);
          break;
        case 6:
          name_text = pedia_lookup_text(pedia_government_names,advance);
          crt_strcpy(&text_buffer,name_text);
          break;
        case 7:
          name_text = pedia_lookup_text(pedia_concept_names,advance);
          crt_strcpy(&text_buffer,name_text);
          break;
        default:
          text_append(ADDR(0x62f058, ((u8 *)&g.d_0062f058)));
        }
        surface_set_clip((DibSurface *)this,(iptr)&row_rect);
        if (shadow_color2 != text_color2) {
          gfx_set_text_color_index(shadow_color2);
          surface_draw_text
                    ((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),text_x_off + col_x + 2,
                     text_y_off + row_y + 1,5);
          gfx_set_text_color_index(text_color2);
          surface_draw_text
                    ((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),text_x_off + col_x + 1,
                     text_y_off + row_y,5);
        }
        gfx_set_text_color_index(text_color2);
        surface_draw_text
                  ((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),text_x_off + col_x,
                   text_y_off + row_y,5);
        surface_set_clip((DibSurface *)this,(iptr)((u8 *)&((PictureWindow *)this)->list_rect));
      }
    }
    col_x = *(int *)((u8 *)&((PictureWindow *)this)->list_rect) + (col + 1) * col_width;
    col++;
  } while( true );
}
#undef dlg_sel_text_color
#undef dlg_sel_text_shadow_color
#undef list_bg_color
#undef list_sel_bg_color
#undef list_shadow_color
#undef list_text_color
#undef panel_margin_x
#undef pedia_advance_names
#undef pedia_concept_names
#undef pedia_government_names
#undef pedia_improvement_names
#undef pedia_selected_item
#undef pedia_terrain_names
#undef pedia_unit_names
#undef pedia_wonder_names
#undef text_buffer
#undef fill_color_e
#undef fill_color_d
#undef shield_x
#undef fill_color_c
#undef icon_x2
#undef fill_color_b
#undef fill_color_a
#undef terrain_fill_color
#undef shield_ctx
#undef icon_ctx2
#undef icon_ctx
#undef resource_ctx
#undef hill_ctx2
#undef forest_ctx2
#undef grass_ctx
#undef mountain_ctx
#undef hill_ctx
#undef forest_ctx
#undef base_ctx
#undef text_y_off
#undef advance
#undef col_width
#undef base_terrain
#undef icon_x
#undef scale_num2
#undef col
#undef col_base
#undef row
#undef row_y
#undef scale_den2
#undef col_x
#undef list_width2
#undef shadow_color2
#undef resource_variant
#undef text_x_off
#undef icon_mode
#undef icon_sprite
#undef text_color2
#undef is_selected
#undef row_rect
#undef row_height
#undef saved_clip
#undef font2

/* 004f7313 auto */
void __cdecl pedia_list_on_scroll(int scroll_pos)

{
  if (pedia_list_top != scroll_pos * 9) {
    pedia_list_top = scroll_pos * 9;
    pedia_draw_item_list((ListPaneWindow *)&pedia_window);
  }
  return;
}

/* 004f734a auto */
#define result (*(int *)(frame_ + FRAME_OFF(4)))
#define column (*(uint *)(frame_ + FRAME_OFF(12)))
int __cdecl pedia_list_hit_test(int x,int y)

{
  int dim;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (y < pedia_list_rect_top) {
    result = -1;
  }
  else if (y < pedia_list_rect_bottom) {
    if (x < pedia_list_rect) {
      result = -3;
    }
    else if (x < pedia_list_rect_right) {
      dim = rect_width(ADDR(0x6a818c, ((u8 *)&g.d_006a818c)));
      column = (uint)(pedia_list_rect + dim / 2 <= x);
      dim = rect_height(ADDR(0x6a818c, ((u8 *)&g.d_006a818c)));
      result = (y - pedia_list_rect_top) / (dim / 9) + column * 9 + pedia_list_top;
      if (pedia_list_count <= result) {
        result = -5;
      }
    }
    else {
      result = -4;
    }
  }
  else {
    result = -2;
  }
  return result;
}
#undef result
#undef column

/* 004f7454 auto */
void __thiscall pedia_scroll_to_item(WindowObjectView *this,int item)

{
  if (item < pedia_list_top) {
    for (pedia_list_top = item; pedia_list_top % 9 != 0; pedia_list_top--) {
    }
  }
  else if (pedia_list_top + 0x12 <= item) {
    for (pedia_list_top = item; pedia_list_top % 9 != 0; pedia_list_top--) {
    }
  }
  pedia_redraw((PediaRedrawView *)&pedia_window);
  return;
}

/* 004f74eb auto */
#define pedia_advance_names (*(i32 * *)((u8 *)&g.d_006a7d44))
#define pedia_category (*(i32 *)((u8 *)&g.d_006a6780))
#define pedia_concept_names (*(i32 * *)((u8 *)&g.d_006a7d5c))
#define pedia_government_names (*(i32 * *)((u8 *)&g.d_006a7d54))
#define pedia_improvement_names (*(i32 * *)((u8 *)&g.d_006a7d48))
#define pedia_selected_item (*(int *)((u8 *)&g.d_006a85a0))
#define pedia_terrain_names (*(i32 * *)((u8 *)&g.d_006a7d58))
#define pedia_unit_names (*(i32 * *)((u8 *)&g.d_006a7d50))
#define pedia_wonder_names (*(i32 * *)((u8 *)&g.d_006a7d4c))
#define remaining (*(int *)(frame_ + FRAME_OFF(4)))
#define list_head (*(i32 * *)(frame_ + FRAME_OFF(8)))
#define index (*(int *)(frame_ + FRAME_OFF(12)))
#define node2 (*(i32 * *)(frame_ + FRAME_OFF(16)))
int __cdecl pedia_find_item_by_key(int key)

{
  int first_char;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  switch(pedia_category) {
  case 1:
    list_head = pedia_advance_names;
    remaining = pedia_advance_entry_count;
    break;
  case 2:
    list_head = pedia_improvement_names;
    remaining = pedia_improvement_entry_count;
    break;
  case 3:
    list_head = pedia_wonder_names;
    remaining = pedia_wonder_entry_count;
    break;
  case 4:
    list_head = pedia_unit_names;
    remaining = pedia_unit_entry_count;
    break;
  case 5:
    list_head = pedia_terrain_names;
    remaining = pedia_terrain_count;
    break;
  case 6:
    list_head = pedia_government_names;
    remaining = pedia_government_entry_count;
    break;
  case 7:
    list_head = pedia_concept_names;
    remaining = pedia_concept_entry_count;
    break;
  default:
    return 0xffffffff;
  }
  node2 = list_head;
  index = pedia_selected_item + 1;
  if (pedia_list_count <= index) {
    index = 0;
  }
  for (; index != 0; index--) {
    if (node2[2] == 0) {
      node2 = list_head;
    }
    else {
      node2 = (i32 *)node2[2];
    }
  }
  index = pedia_selected_item + 1;
  if (pedia_list_count <= index) {
    index = 0;
  }
  while ((remaining != 0 && (first_char = crt_toupper((int)*(char *)*node2), first_char != key))) {
    if (node2[2] == 0) {
      node2 = list_head;
      index = 0;
    }
    else {
      node2 = (i32 *)node2[2];
      index++;
    }
    remaining--;
  }
  if (remaining == 0) {
    index = -1;
  }
  return index;
}
#undef pedia_advance_names
#undef pedia_category
#undef pedia_concept_names
#undef pedia_government_names
#undef pedia_improvement_names
#undef pedia_selected_item
#undef pedia_terrain_names
#undef pedia_unit_names
#undef pedia_wonder_names
#undef remaining
#undef list_head
#undef index
#undef node2

/* 004f76ce auto */
#define pedia_page_mode (*(int *)((u8 *)&g.d_006a6784))
#define pedia_selected_item (*(int *)((u8 *)&g.d_006a85a0))
#define pedia_topic (*(int *)((u8 *)&g.d_006a6788))
void __cdecl pedia_list_on_key(i32 key)

{
  int key_upper;
  int item;
  
  item = pedia_selected_item;
  if (pedia_page_mode == 0) {
    key_upper = crt_toupper(key);
    if ((key_upper < 0x41) || (0x5a < key_upper)) {
      switch(key_upper) {
      case 0xa1:
      case 199:
        pedia_topic = pedia_list_count - 1;
        for (pedia_list_top = pedia_topic; pedia_list_top % 9 != 0; pedia_list_top--) {
        }
        pedia_selected_item = pedia_topic;
        pedia_redraw((PediaRedrawView *)&pedia_window);
        scrollbar_set_pos((ClickControl *)&pedia_list_scrollbar,pedia_list_top / 9);
        break;
      case 0xa2:
      case 0xc1:
        item++;
        if (item < pedia_list_count) {
          pedia_topic = item;
          pedia_selected_item = item;
          pedia_scroll_to_item((WindowObjectView *)&pedia_window,item);
          scrollbar_set_pos((ClickControl *)&pedia_list_scrollbar,pedia_list_top / 9);
        }
        break;
      case 0xa3:
      case 0xa6:
      case 0xc3:
      case 0xc6:
        item += 9;
        if (item < pedia_list_count) {
          pedia_topic = item;
          pedia_selected_item = item;
          pedia_scroll_to_item((WindowObjectView *)&pedia_window,item);
          scrollbar_set_pos((ClickControl *)&pedia_list_scrollbar,pedia_list_top / 9);
        }
        break;
      case 0xa4:
      case 0xa9:
      case 0xc2:
      case 0xc5:
        item -= 9;
        if (-1 < item) {
          pedia_topic = item;
          pedia_selected_item = item;
          pedia_scroll_to_item((WindowObjectView *)&pedia_window,item);
          scrollbar_set_pos((ClickControl *)&pedia_list_scrollbar,pedia_list_top / 9);
        }
        break;
      case 0xa7:
      case 0xc4:
        pedia_topic = 0;
        pedia_selected_item = 0;
        pedia_list_top = 0;
        scrollbar_set_pos((ClickControl *)&pedia_list_scrollbar,0);
        pedia_redraw((PediaRedrawView *)&pedia_window);
        break;
      case 0xa8:
      case 0xc0:
        item--;
        if (-1 < item) {
          pedia_topic = item;
          pedia_selected_item = item;
          pedia_scroll_to_item((WindowObjectView *)&pedia_window,item);
          scrollbar_set_pos((ClickControl *)&pedia_list_scrollbar,pedia_list_top / 9);
        }
        break;
      case 0xd0: ;
      }
    }
    else {
      item = pedia_find_item_by_key(key_upper);
      if (-1 < item) {
        pedia_topic = item;
        pedia_selected_item = item;
        pedia_scroll_to_item((WindowObjectView *)&pedia_window,item);
        scrollbar_set_pos((ClickControl *)&pedia_list_scrollbar,pedia_list_top / 9);
      }
    }
  }
  return;
}
#undef pedia_page_mode
#undef pedia_selected_item
#undef pedia_topic

/* 004f7a30 auto */
#define pedia_page_mode (*(int *)((u8 *)&g.d_006a6784))
#define pedia_selected_item (*(int *)((u8 *)&g.d_006a85a0))
#define pedia_topic (*(int *)((u8 *)&g.d_006a6788))
#define cursor_y (*(i32 *)(frame_ + FRAME_OFF(4)))
#define cursor_x (*(i32 *)(frame_ + FRAME_OFF(8)))
void __cdecl pedia_list_on_click(void)

{
  int hit_item;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((((pedia_page_mode == 0) &&
       (wnd_get_cursor_pos
                  ((WndBase *)&pedia_window_wnd,(iptr)&cursor_x,(iptr)&cursor_y), pedia_list_count != 0)
       ) && (hit_item = pedia_list_hit_test(cursor_x,cursor_y), -1 < hit_item)) && (hit_item < pedia_list_count)) {
    pedia_topic = hit_item;
    pedia_selected_item = hit_item;
    pedia_redraw((PediaRedrawView *)&pedia_window);
  }
  return;
}
#undef pedia_page_mode
#undef pedia_selected_item
#undef pedia_topic
#undef cursor_y
#undef cursor_x

/* 004f7ac7 auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
void __thiscall pedia_set_category_title(WindowObjectView *this,i32 category)

{
  text_clear();
  switch(category) {
  case 1:
  case 8:
    text_append_label(0x29f);
    break;
  case 2:
    text_append_label(0x2a0);
    break;
  case 3:
    text_append_label(0x2a1);
    break;
  case 4:
    text_append_label(0x2a2);
    break;
  case 5:
    text_append_label(0x2a3);
    break;
  case 6:
    text_append_label(0x2a4);
    break;
  case 7:
    text_append_label(0x2a5);
    break;
  default:
    text_append(ADDR(0x62f078, ((u8 *)&g.d_0062f078)));
  }
  crt_strcpy(this + 0x186,&text_buffer);
  return;
}
#undef text_buffer

/* 004f7bd1 auto */
#define pedia_back_topic (*(i32 *)((u8 *)&g.d_0062f010))
#define pedia_going_back (*(i32 *)((u8 *)&g.d_0062f00c))
void __thiscall pedia_open_category(MediaWindow *this,u32 category,int show)

{
  this->style_flags = 0;
  this->border_width = 0;
  this->resize_border = 0;
  this->caption_height = category;
  this->client_y = 0;
  pedia_back_topic = 0xffffffff;
  pedia_going_back = 0;
  pedia_set_category_title((WindowObjectView *)this,category);
  pedia_update_controls(this);
  this->caption_height = category;
  wnd_repaint((SurfaceWindow *)this);
  if (show != 0) {
    window_show((WindowObjectView *)this);
  }
  wnd_set_keyboard_nav((Wnd *)&pedia_window_wnd,0);
  wnd_activate((Wnd *)&pedia_window_wnd);
  pedia_history_push((ScaledWindowView *)&pedia_window);
  return;
}
#undef pedia_back_topic
#undef pedia_going_back

/* 004f7c99 auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define text_buffer_plus2 (*(i8 *)((u8 *)&g.d_00679642))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(4)))
#define i (*(int *)(frame_ + FRAME_OFF(8)))
#define sort_key (*(int *)(frame_ + FRAME_OFF(12)))
#define line_prefix (*(char (*)[2])(frame_ + FRAME_OFF(16)))
#define prefix_nul (*(i8 *)(frame_ + FRAME_OFF(18)))
#define node2 (*(i32 * *)(frame_ + FRAME_OFF(20)))
#define prev_node2 (*(i32 * *)(frame_ + FRAME_OFF(24)))
void __thiscall pedia_load_indexes(DocumentWindow *this)

{
  u8 *slot;
  bool reading;
  int status;
  char *name_str;
  size_t name_len;
  void *name_buf;
  i32 name_text;
  iptr terrain_label;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (i = 0; i < 100; i++) {
    slot = this->advance_sort_keys + i * 4;
    slot[0] = 0xff;
    slot[1] = 0xff;
    slot[2] = 0xff;
    slot[3] = 0xff;
  }
  for (i = 0; i < 0x27; i++) {
    slot = this->improvement_sort_keys + i * 4;
    slot[0] = 0xff;
    slot[1] = 0xff;
    slot[2] = 0xff;
    slot[3] = 0xff;
  }
  for (i = 0; i < 0x1c; i++) {
    slot = ((PictureWindow *)this)->wonder_sort_keys_view + i * 4 + 0x4c;
    slot[0] = 0xff;
    slot[1] = 0xff;
    slot[2] = 0xff;
    slot[3] = 0xff;
  }
  for (i = 0; i < 0x3e; i++) {
    slot = ((PictureWindow *)this)->unit_key_slots + i * 4 + 0x1c;
    slot[0] = 0xff;
    slot[1] = 0xff;
    slot[2] = 0xff;
    slot[3] = 0xff;
  }
  for (i = 0; i < 7; i++) {
    slot = ((PictureWindow *)this)->government_key_slots + i * 4 + 8;
    slot[0] = 0xff;
    slot[1] = 0xff;
    slot[2] = 0xff;
    slot[3] = 0xff;
  }
  for (i = 0; i < 0x21; i++) {
    slot = ((PictureWindow *)this)->terrain_key_slots + i * 4 - 0x18;
    slot[0] = 0xff;
    slot[1] = 0xff;
    slot[2] = 0xff;
    slot[3] = 0xff;
  }
  for (i = 0; i < 0x100; i++) {
    slot = ((PictureWindow *)this)->concept_key_slots + i * 4 + 0x10;
    slot[0] = 0xff;
    slot[1] = 0xff;
    slot[2] = 0xff;
    slot[3] = 0xff;
  }
  pedia_free_lists((WindowObjectView *)this);
  status = text_open_section(ADDR(0x62f094, ((u8 *)&g.d_0062f094)),ADDR(0x62f0a0, ((u8 *)&g.d_0062f0a0)));
  if (status == 0) {
    text_read_line(1);
    sort_key = text_next_int();
    this->pedia_advance_count = 0;
    improvement = 0;
    while (sort_key != -2) {
      if (advances[improvement].enabled != '\0') {
        *(int *)(this->advance_sort_keys + this->pedia_advance_count * 4) = sort_key;
        *(iptr *)(this->advance_sort_keys + this->pedia_advance_count * 4 + 400) = improvement;
        node2 = operator_new(0xc);
        node2[1] = this->pedia_advance_count;
        if ((*(u32 *)&((PictureWindow *)this)->improvements_scrollbar) == 0) {
          (*(u32 *)&((PictureWindow *)this)->improvements_scrollbar) = (u32)node2;
        }
        else {
          prev_node2[2] = node2;
        }
        node2[2] = 0;
        name_str = (char *)label_string(advances[improvement].name);
        name_len = _strlen(name_str);
        name_buf = operator_new(name_len + 1);
        *node2 = name_buf;
        name_text = label_string(advances[improvement].name);
        crt_strcpy(*node2,name_text);
        prev_node2 = node2;
        this->pedia_advance_count++;
      }
      improvement++;
      text_read_line(1);
      sort_key = text_next_int();
    }
    text_close_file();
    if ((*(u32 *)&((PictureWindow *)this)->improvements_scrollbar) != 0) {
      pedia_sort_list(this,(*(u32 *)&((PictureWindow *)this)->improvements_scrollbar),(iptr)this->advance_sort_keys,(iptr)(this->advance_list_items),
                         this->pedia_advance_count);
    }
  }
  status = text_open_section(ADDR(0x62f094, ((u8 *)&g.d_0062f094)),ADDR(0x62f0b0, ((u8 *)&g.d_0062f0b0)));
  if (status == 0) {
    text_read_line(1);
    text_read_line(1);
    sort_key = text_next_int();
    this->pedia_improve_count = 0;
    improvement = 1;
    while (sort_key != -2) {
      if (-2 < improvements[improvement].preq) {
        *(int *)(this->improvement_sort_keys + this->pedia_improve_count * 4) = sort_key;
        *(iptr *)(this->improvement_sort_keys + this->pedia_improve_count * 4 + 0x9c) = improvement;
        node2 = operator_new(0xc);
        node2[1] = this->pedia_improve_count;
        if ((*(uptr *)&((PictureWindow *)this)->pedia_list_head) == 0) {
          (*(uptr *)&((PictureWindow *)this)->pedia_list_head) = (uptr)node2;
        }
        else {
          prev_node2[2] = node2;
        }
        node2[2] = 0;
        name_str = (char *)label_string(improvements[improvement].name);
        name_len = _strlen(name_str);
        name_buf = operator_new(name_len + 1);
        *node2 = name_buf;
        name_text = label_string(improvements[improvement].name);
        crt_strcpy(*node2,name_text);
        prev_node2 = node2;
        this->pedia_improve_count++;
      }
      improvement++;
      text_read_line(1);
      sort_key = text_next_int();
    }
    text_close_file();
    if ((*(uptr *)&((PictureWindow *)this)->pedia_list_head) != 0) {
      pedia_sort_list(this,(*(uptr *)&((PictureWindow *)this)->pedia_list_head),(iptr)this->improvement_sort_keys,(iptr)&this->edit_action_button,
                         this->pedia_improve_count);
    }
  }
  status = text_open_section(ADDR(0x62f094, ((u8 *)&g.d_0062f094)),ADDR(0x62f0c4, ((u8 *)&g.d_0062f0c4)));
  if (status == 0) {
    text_read_line(1);
    sort_key = text_next_int();
    ((PictureWindow *)this)->wonder_count[0] = '\0';
    ((PictureWindow *)this)->wonder_count_byte1[0] = '\0';
    ((PictureWindow *)this)->wonder_count_byte2[0] = '\0';
    ((PictureWindow *)this)->wonder_count_byte3[0] = '\0';
    improvement = 0x27;
    while (sort_key != -2) {
      if (-2 < improvements[improvement].preq) {
        *(int *)(((PictureWindow *)this)->wonder_sort_keys_view + *(int *)(((PictureWindow *)this)->wonder_count) * 4 + 0x4c) = sort_key;
        *(iptr *)(((PictureWindow *)this)->pedia_improvement_ids + *(int *)(((PictureWindow *)this)->wonder_count) * 4) = improvement;
        node2 = operator_new(0xc);
        node2[1] = *(i32 *)(((PictureWindow *)this)->wonder_count);
        if ((*(uptr *)&((PictureWindow *)this)->text_list_2_head) == 0) {
          (*(uptr *)&((PictureWindow *)this)->text_list_2_head) = (uptr)node2;
        }
        else {
          prev_node2[2] = node2;
        }
        node2[2] = 0;
        name_str = (char *)label_string(improvements[improvement].name);
        name_len = _strlen(name_str);
        name_buf = operator_new(name_len + 1);
        *node2 = name_buf;
        name_text = label_string(improvements[improvement].name);
        crt_strcpy(*node2,name_text);
        prev_node2 = node2;
        *(int *)(((PictureWindow *)this)->wonder_count) = *(int *)(((PictureWindow *)this)->wonder_count) + 1;
      }
      improvement++;
      text_read_line(1);
      sort_key = text_next_int();
    }
    text_close_file();
    if ((*(uptr *)&((PictureWindow *)this)->text_list_2_head) != 0) {
      pedia_sort_list(this,(*(uptr *)&((PictureWindow *)this)->text_list_2_head),(iptr)(((PictureWindow *)this)->wonder_sort_keys),(iptr)((PictureWindow *)this)->pedia_improvement_ids,
                         *(iptr *)(((PictureWindow *)this)->wonder_count));
    }
  }
  status = text_open_section(ADDR(0x62f094, ((u8 *)&g.d_0062f094)),ADDR(0x62f0d4, ((u8 *)&g.d_0062f0d4)));
  if (status == 0) {
    text_read_line(1);
    sort_key = text_next_int();
    ((PictureWindow *)this)->pedia_unit_count[0] = '\0';
    ((PictureWindow *)this)->pedia_unit_count_byte1[0] = '\0';
    ((PictureWindow *)this)->pedia_unit_count_byte2[0] = '\0';
    ((PictureWindow *)this)->pedia_unit_count_byte3[0] = '\0';
    improvement = 0;
    while (sort_key != -2) {
      if (-2 < unit_types[improvement].prerequisite) {
        *(int *)(((PictureWindow *)this)->unit_key_slots + *(int *)(((PictureWindow *)this)->pedia_unit_count) * 4 + 0x1c) = sort_key;
        *(iptr *)(((PictureWindow *)this)->unit_ids_tail + *(int *)(((PictureWindow *)this)->pedia_unit_count) * 4 - 4) = improvement;
        node2 = operator_new(0xc);
        node2[1] = *(i32 *)(((PictureWindow *)this)->pedia_unit_count);
        if ((*(uptr *)&((PictureWindow *)this)->text_list_3_head) == 0) {
          (*(uptr *)&((PictureWindow *)this)->text_list_3_head) = (uptr)node2;
        }
        else {
          prev_node2[2] = node2;
        }
        node2[2] = 0;
        name_str = (char *)label_string(unit_types[improvement].name);
        name_len = _strlen(name_str);
        name_buf = operator_new(name_len + 1);
        *node2 = name_buf;
        name_text = label_string(unit_types[improvement].name);
        crt_strcpy(*node2,name_text);
        prev_node2 = node2;
        *(int *)(((PictureWindow *)this)->pedia_unit_count) = *(int *)(((PictureWindow *)this)->pedia_unit_count) + 1;
      }
      improvement++;
      text_read_line(1);
      sort_key = text_next_int();
    }
    text_close_file();
    if ((*(uptr *)&((PictureWindow *)this)->text_list_3_head) != 0) {
      pedia_sort_list(this,(*(uptr *)&((PictureWindow *)this)->text_list_3_head),(iptr)(((PictureWindow *)this)->pedia_unit_sort_keys),
                         (iptr)&((PictureWindow *)this)->pedia_unit_ids,*(iptr *)(((PictureWindow *)this)->pedia_unit_count));
    }
  }
  status = text_open_section(ADDR(0x62f094, ((u8 *)&g.d_0062f094)),ADDR(0x62f0e0, ((u8 *)&g.d_0062f0e0)));
  if (status == 0) {
    text_read_line(1);
    sort_key = text_next_int();
    ((PictureWindow *)this)->pedia_government_count[0] = '\0';
    ((PictureWindow *)this)->pedia_government_count_byte1[0] = '\0';
    ((PictureWindow *)this)->pedia_government_count_byte2[0] = '\0';
    ((PictureWindow *)this)->pedia_government_count_byte3[0] = '\0';
    improvement = 0;
    while (sort_key != -2) {
      *(int *)(((PictureWindow *)this)->government_key_slots + *(int *)(((PictureWindow *)this)->pedia_government_count) * 4 + 8) = sort_key;
      *(iptr *)(((PictureWindow *)this)->government_key_slots + *(int *)(((PictureWindow *)this)->pedia_government_count) * 4 + 0x24) = improvement;
      node2 = operator_new(0xc);
      node2[1] = *(i32 *)(((PictureWindow *)this)->pedia_government_count);
      if ((*(uptr *)&((PictureWindow *)this)->text_list_4_head) == 0) {
        (*(uptr *)&((PictureWindow *)this)->text_list_4_head) = (uptr)node2;
      }
      else {
        prev_node2[2] = node2;
      }
      node2[2] = 0;
      name_str = (char *)label_string(government_names[improvement]);
      name_len = _strlen(name_str);
      name_buf = operator_new(name_len + 1);
      *node2 = name_buf;
      name_text = label_string(government_names[improvement]);
      crt_strcpy(*node2,name_text);
      prev_node2 = node2;
      *(int *)(((PictureWindow *)this)->pedia_government_count) = *(int *)(((PictureWindow *)this)->pedia_government_count) + 1;
      improvement++;
      text_read_line(1);
      sort_key = text_next_int();
    }
    text_close_file();
    if ((*(uptr *)&((PictureWindow *)this)->text_list_4_head) != 0) {
      pedia_sort_list(this,(*(uptr *)&((PictureWindow *)this)->text_list_4_head),(iptr)(((PictureWindow *)this)->pedia_government_sort_keys),
                         (iptr)(((PictureWindow *)this)->pedia_government_ids),*(iptr *)(((PictureWindow *)this)->pedia_government_count));
    }
  }
  status = text_open_section(ADDR(0x62f094, ((u8 *)&g.d_0062f094)),ADDR(0x62f0f4, ((u8 *)&g.d_0062f0f4)));
  if (status == 0) {
    text_read_line(1);
    sort_key = text_next_int();
    ((PictureWindow *)this)->pedia_terrain_count_2 = 0;
    improvement = 0;
    while (sort_key != -2) {
      if (improvement != 0x18) {
        *(int *)(((PictureWindow *)this)->terrain_key_slots + ((PictureWindow *)this)->pedia_terrain_count_2 * 4 - 0x18) = sort_key;
        *(iptr *)(((PictureWindow *)this)->terrain_key_slots + ((PictureWindow *)this)->pedia_terrain_count_2 * 4 + 0x6c) = improvement;
        node2 = operator_new(0xc);
        node2[1] = ((PictureWindow *)this)->pedia_terrain_count_2;
        if ((*(uptr *)&((PictureWindow *)this)->text_list_5_head) == 0) {
          (*(uptr *)&((PictureWindow *)this)->text_list_5_head) = (uptr)node2;
        }
        else {
          prev_node2[2] = node2;
        }
        node2[2] = 0;
        text_clear();
        terrain_label = label_string(terrain_types[improvement].name);
        text_append(terrain_label);
        if ((0xc < improvement) &&
           (status = _strcmp(terrain_types[improvement].abbrev,&pedia_grassland_shield_abbrev_str), status == 0)) {
          text_append_space();
          name_text = label_string(*(i32 *)(label_string_ids + 0xb00));
          crt_strcat(&text_buffer,name_text);
        }
        name_len = _strlen(&text_buffer);
        name_buf = operator_new(name_len + 1);
        *node2 = name_buf;
        crt_strcpy(*node2,&text_buffer);
        prev_node2 = node2;
        ((PictureWindow *)this)->pedia_terrain_count_2++;
      }
      improvement++;
      text_read_line(1);
      sort_key = text_next_int();
    }
    text_close_file();
    if ((*(uptr *)&((PictureWindow *)this)->text_list_5_head) != 0) {
      pedia_sort_list(this,(*(uptr *)&((PictureWindow *)this)->text_list_5_head),(iptr)&((PictureWindow *)this)->pedia_terrain_sort_keys,
                         (iptr)(((PictureWindow *)this)->pedia_terrain_ids_2),((PictureWindow *)this)->pedia_terrain_count_2);
    }
  }
  status = text_open_section(ADDR(0x62f094, ((u8 *)&g.d_0062f094)),ADDR(0x62f108, ((u8 *)&g.d_0062f108)));
  if (status == 0) {
    reading = true;
    ((PictureWindow *)this)->pedia_concept_count[0] = '\0';
    ((PictureWindow *)this)->pedia_concept_count_byte1[0] = '\0';
    ((PictureWindow *)this)->pedia_concept_count_byte2[0] = '\0';
    ((PictureWindow *)this)->pedia_concept_count_byte3[0] = '\0';
    prefix_nul = 0;
    improvement = 0;
    while (reading) {
      text_read_line(1);
      _strncpy(line_prefix,&text_buffer,2);
      status = _strcmp(line_prefix,&pedia_index_marker_str);
      if (status == 0) {
        *(i32 *)(((PictureWindow *)this)->concept_key_slots + *(int *)(((PictureWindow *)this)->pedia_concept_count) * 4 + 0x10) =
             *(i32 *)(((PictureWindow *)this)->pedia_concept_count);
        *(iptr *)(((PictureWindow *)this)->pedia_entry_lists + *(int *)(((PictureWindow *)this)->pedia_concept_count) * 4 + 600) = improvement;
        node2 = operator_new(0xc);
        node2[1] = *(i32 *)(((PictureWindow *)this)->pedia_concept_count);
        if ((*(uptr *)&((PictureWindow *)this)->text_list_6_head) == 0) {
          (*(uptr *)&((PictureWindow *)this)->text_list_6_head) = (uptr)node2;
        }
        else {
          prev_node2[2] = node2;
        }
        node2[2] = 0;
        name_len = _strlen(&text_buffer_plus2);
        name_buf = operator_new(name_len + 1);
        *node2 = name_buf;
        crt_strcpy(*node2,&text_buffer_plus2);
        prev_node2 = node2;
        improvement++;
        *(int *)(((PictureWindow *)this)->pedia_concept_count) = *(int *)(((PictureWindow *)this)->pedia_concept_count) + 1;
      }
      else if (line_prefix[0] == '@') {
        reading = false;
      }
    }
    if ((*(uptr *)&((PictureWindow *)this)->text_list_6_head) != 0) {
      pedia_sort_list(this,(*(uptr *)&((PictureWindow *)this)->text_list_6_head),(iptr)(((PictureWindow *)this)->pedia_concept_sort_keys),
                         (iptr)(((PictureWindow *)this)->pedia_sorted_entries),*(iptr *)(((PictureWindow *)this)->pedia_concept_count));
    }
  }
  return;
}
#undef text_buffer
#undef text_buffer_plus2
#undef improvement
#undef i
#undef sort_key
#undef line_prefix
#undef prefix_nul
#undef node2
#undef prev_node2

/* 004f896a auto */
#define j (*(int *)(frame_ + FRAME_OFF(0)))
#define i (*(int *)(frame_ + FRAME_OFF(4)))
#define other_node (*(i32 * *)(frame_ + FRAME_OFF(12)))
#define node2 (*(i32 * *)(frame_ + FRAME_OFF(16)))
void __thiscall pedia_sort_list(void *this,iptr list_head,iptr keys,iptr ids,iptr count)

{
  i32 swap_tmp;
  int cmp;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  other_node = (i32 *)list_head;
  node2 = (i32 *)list_head;
  for (i = 0; i < count - 1; i++) {
    j = i;
    if (node2[2] != 0) {
      other_node = (i32 *)node2[2];
    }
    while (j = j + 1, j < count) {
      cmp = _strcmp((char *)*node2,(char *)*other_node);
      if (0 < cmp) {
        swap_tmp = *(i32 *)(keys + i * 4);
        *(i32 *)(keys + i * 4) = *(i32 *)(keys + j * 4);
        *(i32 *)(keys + j * 4) = swap_tmp;
        swap_tmp = *(i32 *)(ids + i * 4);
        *(i32 *)(ids + i * 4) = *(i32 *)(ids + j * 4);
        *(i32 *)(ids + j * 4) = swap_tmp;
        swap_tmp = *node2;
        *node2 = *other_node;
        *other_node = swap_tmp;
      }
      if (other_node[2] != 0) {
        other_node = (i32 *)other_node[2];
      }
    }
    if (node2[2] != 0) {
      node2 = (i32 *)node2[2];
    }
  }
  return;
}
#undef j
#undef i
#undef other_node
#undef node2

/* 004f8a9b auto */
#define node2 (*(i32 * *)(frame_ + FRAME_OFF(0)))
i8 * __cdecl pedia_lookup_text(i32 *list_head,iptr item_id)

{
  i8 *text;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (node2 = list_head; (node2 != (i32 *)0x0 && (node2[1] != item_id));
      node2 = (i32 *)node2[2]) {
  }
  text = pedia_missing_text;
  if (node2 != (i32 *)0x0) {
    text = (i8 *)*node2;
  }
  return text;
}
#undef node2

/* 004f8af9 auto */
#define pedia_back_topic (*(int *)((u8 *)&g.d_0062f010))
#define pedia_going_back (*(int *)((u8 *)&g.d_0062f00c))
#define pedia_history_count (*(int *)((u8 *)&g.d_006a6790))
void __thiscall pedia_history_push(ScaledWindowView *this)

{
  if (((int)this->client_y < 99) && (pedia_going_back == 0)) {
    if (((this->client_y == 0) ||
        (((*(u32 *)(((PediaRedrawView *)this)->pedia_history_modes + this->client_y * 4 + 0x18) != this->border_width ||
          (*(int *)(((PediaRedrawView *)this)->pedia_history_modes + this->client_y * 4 + 0x18) != 0)) ||
         (*(int *)((u8 *)&((ViewWindow *)this)->advance_pane_rect_bottom + this->client_y * 4 + 0x7c) == 8)))) || (this->caption_height == 8))
    {
      if (((this->client_y == 0) ||
          (*(u32 *)((u8 *)&((ViewWindow *)this)->advance_pane_rect_bottom + this->client_y * 4 + 0x7c) != this->caption_height)) ||
         ((*(u32 *)(((PediaRedrawView *)this)->pedia_history_modes + this->client_y * 4 + 0x18) != this->border_width ||
          (*(u32 *)(this->pedia_history_base + pedia_history_count * 4 + 0x24) != this->resize_border)))) {
        if (-1 < pedia_back_topic) {
          *(int *)(((PortraitDialog *)this)->topic_history_area + this->client_y * 4 - 0x48) = pedia_back_topic;
          *(i32 *)(((PediaRedrawView *)this)->pedia_history_modes + this->client_y * 4 + 0x1c) = pedia_popped_page_mode;
          *(i32 *)((u8 *)&((ViewWindow *)this)->advance_pane_rect_bottom + this->client_y * 4 + 0x80) = pedia_popped_category;
          this->client_y++;
        }
        *(u32 *)(((PortraitDialog *)this)->topic_history_area + this->client_y * 4 - 0x48) = this->resize_border;
        *(u32 *)(((PediaRedrawView *)this)->pedia_history_modes + this->client_y * 4 + 0x1c) = this->border_width;
        *(u32 *)((u8 *)&((ViewWindow *)this)->advance_pane_rect_bottom + this->client_y * 4 + 0x80) = this->caption_height;
        this->client_y++;
      }
    }
    else {
      *(u32 *)(this->pedia_history_base + this->client_y * 4 + 0x24) = this->resize_border;
    }
  }
  pedia_back_topic = 0xffffffff;
  pedia_going_back = 0;
  return;
}
#undef pedia_back_topic
#undef pedia_going_back
#undef pedia_history_count

/* 004f8d04 auto */
#define pedia_closed (*(int *)((u8 *)&g.d_006a677c))
void __cdecl pedia_modal_idle(void)

{
  net_process_messages((NetSession *)&net_session,1,0);
  if ((pedia_modal_active == 0) || (pedia_closed == 1)) {
    wnd_end_modal_loop((ModalMenuWindow *)&pedia_window_wnd);
    pedia_modal_active = 0;
  }
  return;
}
#undef pedia_closed

/* 004f8d51 auto */
void __cdecl pedia_end_modal(void)

{
  wnd_end_modal_loop((ModalMenuWindow *)&pedia_window_wnd);
  return;
}

/* 004fa0f0 auto */
/* Library Function - Multiple Matches With Different Base Names
    public: void * __thiscall CControlBarInfo::`scalar deleting destructor'(unsigned int)
    public: virtual void * __thiscall __non_rtti_object::`scalar deleting destructor'(unsigned int)
    public: virtual void * __thiscall bad_cast::`scalar deleting destructor'(unsigned int)
    public: virtual void * __thiscall bad_typeid::`scalar deleting destructor'(unsigned int)
     9 names - too many to list
   
   Library: Visual Studio 1998 Debug */

void * __thiscall pedia_link_scalar_dtor(void *this,uint flags)

{
  pedia_link_dtor(this);
  if ((flags & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 004fa140 auto */
#define exc_link (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define eh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
/* Library Function - Single Match
    public: __thiscall CControlBarInfo::~CControlBarInfo(void)
   
   Library: Visual Studio 1998 Debug */

void __thiscall pedia_link_dtor(void *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  eh_state = 0xffffffff;
  /* inlined unwind funclet 004fa17e */ { hyperlink_dtor((HyperlinkDtorView *)(*(int *)((iptr)&this) + 4)); }
  return;
}
#undef exc_link
#undef seh_handler
#undef eh_state

/* 00518f00 auto */
#define i (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall pedia_init_government_list(MediaWindow *this,iptr unused_arg)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((int)this->resize_border < 0) || ((int)(*(u32 *)&((PictureWindow *)this)->pedia_government_count) <= (int)this->resize_border)) {
    this->resize_border = 0;
  }
  *(u32 *)((PictureWindow *)this)->list_item_table = (*(u32 *)&((PictureWindow *)this)->pedia_government_count);
  *(u32 *)(((PictureWindow *)this)->list_selected_index) = this->resize_border;
  *(u32 *)(((PictureWindow *)this)->list_top_index) = this->resize_border;
  while (pedia_list_top % 9 != 0) {
    *(int *)(((PictureWindow *)this)->list_top_index) = *(int *)(((PictureWindow *)this)->list_top_index) - 1;
  }
  for (i = 0; i < (int)(*(u32 *)&((PictureWindow *)this)->pedia_government_count); i++) {
    *(i32 *)(((PictureWindow *)this)->list_item_table + i * 4 + 4) =
         *(i32 *)(((PictureWindow *)this)->pedia_government_sort_keys + i * 4 + 0x1c);
  }
  scrollbar_set_range
            ((Control *)&((PictureWindow *)this)->list_scrollbar,0,*(int *)((PictureWindow *)this)->list_item_table / 9);
  scrollbar_set_pos
            ((ClickControl *)&((PictureWindow *)this)->list_scrollbar,*(int *)(((PictureWindow *)this)->list_top_index) / 9);
  if (*(int *)((PictureWindow *)this)->list_item_table < 1) {
    ((PictureWindow *)this)->list_top_index[0] = 0xff;
    ((PictureWindow *)this)->list_top_index_byte1[0] = 0xff;
    ((PictureWindow *)this)->list_top_index_byte2[0] = 0xff;
    ((PictureWindow *)this)->list_top_index_byte3[0] = 0xff;
  }
  pedia_update_controls(this);
  wnd_set_focus((WndBase *)&pedia_window_wnd);
  wnd_activate((Wnd *)&pedia_window_wnd);
  pedia_redraw((PediaRedrawView *)&pedia_window);
  return;
}
#undef i

/* 005190d0 auto */
void __cdecl notice_dlg_global_init(void)

{
  notice_dlg_static_init();
  notice_dlg_reg_atexit();
  return;
}

/* 005190ea auto */
void __cdecl notice_dlg_static_init(void)

{
  dialog_ctor((Dialog *)&game_section_dialog,0x4000);
  return;
}

/* 00519109 auto */
void __cdecl notice_dlg_reg_atexit(void)

{
  _atexit(notice_dlg_static_dtor);
  return;
}

/* 00519126 auto */
void __cdecl notice_dlg_static_dtor(void)

{
  dialog_dtor((Dialog *)&game_section_dialog);
  return;
}

/* 005261a0 auto */
#define i (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall pedia_init_wonder_list(MediaWindow *this,iptr unused_arg)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((int)this->resize_border < 0) || ((int)(*(u32 *)&((PictureWindow *)this)->wonder_count) <= (int)this->resize_border)) {
    this->resize_border = 0;
  }
  *(u32 *)((PictureWindow *)this)->list_item_table = (*(u32 *)&((PictureWindow *)this)->wonder_count);
  *(u32 *)(((PictureWindow *)this)->list_selected_index) = this->resize_border;
  *(u32 *)(((PictureWindow *)this)->list_top_index) = this->resize_border;
  while (pedia_list_top % 9 != 0) {
    *(int *)(((PictureWindow *)this)->list_top_index) = *(int *)(((PictureWindow *)this)->list_top_index) - 1;
  }
  for (i = 0; i < (int)(*(u32 *)&((PictureWindow *)this)->wonder_count); i++) {
    *(i32 *)(((PictureWindow *)this)->list_item_table + i * 4 + 4) =
         *(i32 *)(((PictureWindow *)this)->wonder_items_view + i * 4 + 0x6c);
  }
  scrollbar_set_range
            ((Control *)&((PictureWindow *)this)->list_scrollbar,0,*(int *)((PictureWindow *)this)->list_item_table / 9);
  scrollbar_set_pos
            ((ClickControl *)&((PictureWindow *)this)->list_scrollbar,*(int *)(((PictureWindow *)this)->list_top_index) / 9);
  if (*(int *)((PictureWindow *)this)->list_item_table < 1) {
    ((PictureWindow *)this)->list_top_index[0] = 0xff;
    ((PictureWindow *)this)->list_top_index_byte1[0] = 0xff;
    ((PictureWindow *)this)->list_top_index_byte2[0] = 0xff;
    ((PictureWindow *)this)->list_top_index_byte3[0] = 0xff;
  }
  pedia_update_controls(this);
  wnd_set_focus((WndBase *)&pedia_window_wnd);
  wnd_activate((Wnd *)&pedia_window_wnd);
  pedia_redraw((PediaRedrawView *)&pedia_window);
  return;
}
#undef i

/* 0052630d auto */
#define list_text_color (*(i32 *)((u8 *)&g.d_00635a1c))
#define panel_margin_x (*(int *)((u8 *)&g.d_0062d858))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define shield_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define icon_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(16)))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(32)))
#define text_rect (*(tagRECT *)(frame_ + FRAME_OFF(36)))
#define line_height (*(int *)(frame_ + FRAME_OFF(52)))
#define icon_width (*(int *)(frame_ + FRAME_OFF(56)))
#define scale_num2 (*(i32 *)(frame_ + FRAME_OFF(60)))
#define y2 (*(int *)(frame_ + FRAME_OFF(64)))
#define scale_den2 (*(i32 *)(frame_ + FRAME_OFF(68)))
#define x2 (*(int *)(frame_ + FRAME_OFF(72)))
#define content_width2 (*(int *)(frame_ + FRAME_OFF(76)))
#define value_x (*(int *)(frame_ + FRAME_OFF(80)))
#define unused_flag (*(i32 *)(frame_ + FRAME_OFF(84)))
#define link_rect (*(tagRECT *)(frame_ + FRAME_OFF(88)))
#define text_width (*(int *)(frame_ + FRAME_OFF(104)))
#define row_height (*(int *)(frame_ + FRAME_OFF(108)))
#define saved_clip (*(i8 (*)[16])(frame_ + FRAME_OFF(112)))
#define font2 (*(GameFont * *)(frame_ + FRAME_OFF(128)))
/* WARNING: Removing unreachable block (ram,0x0052661a) */

void __thiscall pedia_draw_improvement(DocumentWindow *this)

{
  int measure;
  iptr label;
  size_t text_len;
  int center_y;
  u32 yBottom;
  i8 frame_[FRAME_OFF(136)] __attribute__((aligned(8)));  /* original stack frame */
  
  unused_flag = 0;
  surface_get_clip((DibSurface *)this,(iptr)saved_clip);
  surface_set_clip((DibSurface *)this,(iptr)&this->content_left);
  pedia_update_controls((MediaWindow *)this);
  pedia_fill_background((WindowObjectView *)this,(iptr)&this->content_left,2);
  font2 = (GameFont *)&font_size21;
  x2 = this->content_left + 10;
  content_width2 = rect_width((iptr)&this->content_left);
  row_height = font_cached_height(font2);
  y2 = this->content_top + 8;
  value_x = content_width2 / 2 - 100;
  improvement = *(iptr *)(((PictureWindow *)this)->pedia_improvement_ids + this->resize_border * 4);
  gfx_get_scale_ratio((iptr)&scale_num2,(iptr)&scale_den2);
  gfx_set_scale_ratio(2,1);
  icon_width = sprite_get_width((Sprite *)(&improvement_icon_sprites + improvement * 0x3c));
  icon_width += panel_margin_x * 2;
  sprite_draw
            ((Sprite *)(&improvement_icon_sprites + improvement * 0x3c),(iptr)icon_ctx,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),x2,
             y2);
  gfx_set_scale_ratio(scale_num2,scale_den2);
  gfx_set_text_color_index(list_text_color);
  x2 = this->content_left + 10;
  measure = sprite_height((Sprite *)(&improvement_icon_sprites + improvement * 0x3c));
  y2 = y2 + measure * 2 + 5;
  text_clear();
  text_append_label(0x79);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
  measure = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  x2 = x2 + measure + 5;
  text_clear();
  if (improvements[improvement].preq < '\0') {
    text_append_label(0xe);
    surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
  }
  else {
    text_append_string_id(advances[improvements[improvement].preq].name);
    text_width = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    line_height = font_line_spacing(font2);
    SetRect(&link_rect,x2,y2,x2 + text_width + 5,y2 + line_height);
    pedia_add_link(this,(int)improvements[improvement].preq,x2,y2,0,link_rect.left,
                       link_rect.top,link_rect.right,link_rect.bottom);
  }
  value_x = x2;
  x2 = this->content_left + 10;
  y2 += row_height;
  text_clear();
  text_append_label(0x84);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
  text_clear();
  _sprintf(&text_buffer,&pedia_improvement_cost_fmt,(uint)improvements[improvement].cost * 10);
  surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),value_x,y2,5);
  measure = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  x2 = value_x + measure + 3;
  center_y = y2 + row_height / 2;
  measure = sprite_get_height((Sprite *)&shield_icon_sprite);
  sprite_draw
            ((Sprite *)&shield_icon_sprite,(iptr)shield_ctx,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),x2,center_y - measure / 2);
  x2 = this->content_left + 10;
  y2 += row_height;
  text_clear();
  text_append_label(0x9f);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
  text_clear();
  if (improvement < 0x17) {
    text_append_label(0xe);
    surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),value_x,y2,5);
  }
  else if ((char)(&wonder_expires_by_impr)[improvement] < 1) {
    text_append_label(0xe);
    surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),value_x,y2,5);
  }
  else {
    label = label_string(advances[(char)(&wonder_expires_by_impr)[improvement]].name);
    text_append(label);
    text_width = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    line_height = font_line_spacing(font2);
    SetRect(&link_rect,value_x,y2,value_x + text_width + 5,y2 + line_height);
    pedia_add_link(this,(int)(char)(&wonder_expires_by_impr)[improvement],value_x,y2,0,link_rect.left,
                       link_rect.top,link_rect.right,link_rect.bottom);
  }
  x2 = this->content_left + 10;
  y2 += row_height * 2;
  pedia_load_improvement_text((WindowObjectView *)this,improvement);
  text_len = _strlen(&text_buffer);
  if (text_len != 0) {
    yBottom = this->content_bottom;
    measure = rect_width((iptr)&this->content_left);
    SetRect(&text_rect,x2,y2,measure - 10 + x2,yBottom);
    surface_draw_text_rect((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),(iptr)&text_rect,5);
  }
  pedia_update_describe_button((ListPaneWindow *)this,this->resize_border);
  surface_set_clip((DibSurface *)this,(iptr)saved_clip);
  wnd_blit_surface_rect((DibSurface *)this,(iptr)&this->content_left);
  return;
}
#undef list_text_color
#undef panel_margin_x
#undef text_buffer
#undef shield_ctx
#undef icon_ctx
#undef improvement
#undef text_rect
#undef line_height
#undef icon_width
#undef scale_num2
#undef y2
#undef scale_den2
#undef x2
#undef content_width2
#undef value_x
#undef unused_flag
#undef link_rect
#undef text_width
#undef row_height
#undef saved_clip
#undef font2

/* 00526913 auto */
#define map_redraw_busy (*(int *)((u8 *)&g.d_006ad908))
#define pedia_closed (*(int *)((u8 *)&g.d_006a677c))
#define pedia_wonder_names (*(i32 *)((u8 *)&g.d_006a7d4c))
#define wonder_idx (*(u32 *)(frame_ + FRAME_OFF(0)))
void __thiscall pedia_show_wonder_modal(DocumentWindow *this,int wonder_id)

{
  i32 name_text;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((pedia_closed != 0) && (map_redraw_busy == 0)) {
    for (wonder_idx = 0;
        ((int)wonder_idx < *(int *)(((PictureWindow *)this)->wonder_count) &&
        (*(int *)(((PictureWindow *)this)->pedia_improvement_ids + wonder_idx * 4) != wonder_id)); wonder_idx++) {
    }
    if (*(u32 *)(((PictureWindow *)this)->wonder_count) != wonder_idx) {
      pedia_open_category((MediaWindow *)this,3,1);
      this->resize_border = wonder_idx;
      *(u32 *)(((PictureWindow *)this)->list_selected_index) = wonder_idx;
      this->client_x = 1;
      this->border_width = 1;
      pedia_clear_links((WindowObjectView *)this);
      pedia_update_controls((MediaWindow *)this);
      name_text = pedia_lookup_text(pedia_wonder_names,wonder_idx);
      crt_strcpy(this->pedia_title_text_2,name_text);
      pedia_draw_frame((MediaWindow *)this);
      pedia_draw_improvement(this);
      wnd_blit_surface((DibSurface *)&pedia_window);
      wnd_activate((Wnd *)&pedia_window_wnd);
      wnd_set_modal_idle_callback((ModalMenuWindow *)&pedia_window_wnd,ADDR(0x401843, pedia_modal_idle));
      wnd_run_modal_loop((ModalMenuWindow *)&pedia_window_wnd);
      wnd_set_modal_idle_callback((ModalMenuWindow *)&pedia_window_wnd,0);
    }
  }
  return;
}
#undef map_redraw_busy
#undef pedia_closed
#undef pedia_wonder_names
#undef wonder_idx

/* 00564d00 auto */
#define i (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall pedia_init_advance_list(PediaAdvanceListView *this,iptr unused_arg)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((int)this->resize_border < 0) || ((int)this->pedia_advance_count <= (int)this->resize_border)) {
    this->resize_border = 0;
  }
  *(u32 *)(((PictureWindow *)this)->list_item_table) = this->pedia_advance_count;
  *(u32 *)(((PictureWindow *)this)->list_selected_index) = this->resize_border;
  *(u32 *)(((PictureWindow *)this)->list_top_index) = this->resize_border;
  while (pedia_list_top % 9 != 0) {
    *(int *)(((PictureWindow *)this)->list_top_index) = *(int *)(((PictureWindow *)this)->list_top_index) - 1;
  }
  for (i = 0; i < (int)this->pedia_advance_count; i++) {
    *(i32 *)((u8 *)&((PictureWindow *)this)->list_rect_right + i * 4 + 0xc) =
         *(i32 *)(((DocumentWindow *)this)->advance_items_view + i * 4 + 0xc);
  }
  scrollbar_set_range
            ((Control *)((u8 *)&((PictureWindow *)this)->list_scrollbar),0,*(int *)(((PictureWindow *)this)->list_item_table) / 9);
  scrollbar_set_pos
            ((ClickControl *)((u8 *)&((PictureWindow *)this)->list_scrollbar),*(int *)(((PictureWindow *)this)->list_top_index) / 9);
  if (*(int *)(((PictureWindow *)this)->list_item_table) < 1) {
    ((PictureWindow *)this)->list_top_index[0] = 0xff;
    ((PictureWindow *)this)->list_top_index_byte1[0] = 0xff;
    ((PictureWindow *)this)->list_top_index_byte2[0] = 0xff;
    ((PictureWindow *)this)->list_top_index_byte3[0] = 0xff;
  }
  pedia_update_controls((MediaWindow *)this);
  wnd_set_focus((WndBase *)&pedia_window_wnd);
  wnd_activate((Wnd *)&pedia_window_wnd);
  pedia_redraw((PediaRedrawView *)&pedia_window);
  return;
}
#undef i

/* 00564e6d auto */
#define list_text_color (*(i32 *)((u8 *)&g.d_00635a1c))
#define panel_margin_x (*(int *)((u8 *)&g.d_0062d858))
#define unit_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define impr_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
#define icon_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(36)))
#define wonder (*(iptr *)(frame_ + FRAME_OFF(52)))
#define is_child (*(int *)(frame_ + FRAME_OFF(56)))
#define advance3 (*(iptr *)(frame_ + FRAME_OFF(60)))
#define prev_unit_height (*(int *)(frame_ + FRAME_OFF(64)))
#define advance (*(iptr *)(frame_ + FRAME_OFF(68)))
#define pedia_file (*(char * *)(frame_ + FRAME_OFF(72)))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(76)))
#define line_height (*(int *)(frame_ + FRAME_OFF(80)))
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(84)))
#define y2 (*(int *)(frame_ + FRAME_OFF(88)))
#define x2 (*(u32 *)(frame_ + FRAME_OFF(92)))
#define line (*(char * *)(frame_ + FRAME_OFF(96)))
#define advance2 (*(iptr *)(frame_ + FRAME_OFF(100)))
#define unit_text_y (*(int *)(frame_ + FRAME_OFF(104)))
#define has_pedia (*(int *)(frame_ + FRAME_OFF(108)))
#define link_rect (*(tagRECT *)(frame_ + FRAME_OFF(112)))
#define text_width (*(int *)(frame_ + FRAME_OFF(128)))
#define related_count (*(int *)(frame_ + FRAME_OFF(132)))
#define line_buf (*(char *)(frame_ + FRAME_OFF(136)))
#define line_rest (*(char (*)[259])(frame_ + FRAME_OFF(137)))
#define row_height (*(int *)(frame_ + FRAME_OFF(396)))
#define list_x2 (*(int *)(frame_ + FRAME_OFF(400)))
#define saved_clip (*(i8 (*)[16])(frame_ + FRAME_OFF(404)))
#define font2 (*(GameFont * *)(frame_ + FRAME_OFF(420)))
#define in_right_col (*(uint *)(frame_ + FRAME_OFF(424)))
void __thiscall pedia_draw_advance_page(DocumentWindow *this)

{
  int measure;
  iptr label;
  size_t rest_len;
  int center_y;
  bool was_right;
  i8 frame_[FRAME_OFF(432)] __attribute__((aligned(8)));  /* original stack frame */
  
  surface_get_clip((DibSurface *)this,(iptr)saved_clip);
  surface_set_clip((DibSurface *)this,(iptr)&this->content_left);
  pedia_update_controls((MediaWindow *)this);
  pedia_fill_background((WindowObjectView *)this,(iptr)&this->content_left,2);
  font2 = (GameFont *)&font_size21;
  x2 = this->content_left;
  row_height = font_cached_height((GameFont *)&font_size21);
  y2 = this->content_top + 5;
  advance = *(iptr *)(this->advance_sort_keys + this->resize_border * 4 + 400);
  sprite_draw
            ((Sprite *)
             (&advance_category_icon_sprites +
             (char)advances[advance].epoch * 0x3c + (char)advances[advance].category * 0xf0),
             (iptr)icon_ctx,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),panel_margin_x + x2,y2);
  gfx_set_text_color_index(list_text_color);
  related_count = 0;
  for (advance2 = 0; advance2 < 100; advance2++) {
    if ((advances[advance2].preq[0] == advance) || (advances[advance2].preq[1] == advance)) {
      related_count++;
    }
  }
  for (improvement = 1; improvement < 0x43; improvement++) {
    if (improvements[improvement].preq == advance) {
      related_count++;
    }
  }
  for (unit_type = 0; unit_type < 0x3e; unit_type++) {
    if (unit_types[unit_type].prerequisite == advance) {
      related_count++;
    }
  }
  x2 = this->content_left + 0x32;
  text_clear();
  text_append_label(0x79);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
  measure = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  x2 = x2 + measure + 5;
  text_clear();
  if ((advances[advance].preq[0] < '\0') && (advances[advance].preq[1] < '\0')) {
    text_append_label(0xe);
    surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
  }
  else {
    if (-1 < advances[advance].preq[0]) {
      text_append_string_id(advances[advances[advance].preq[0]].name);
      text_width = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
      line_height = font_line_spacing(font2);
      SetRect(&link_rect,x2,y2,text_width + x2 + 5,line_height + y2);
      pedia_add_link(this,(int)advances[advance].preq[0],x2,y2,0,link_rect.left,
                         link_rect.top,link_rect.right,link_rect.bottom);
    }
    if (-1 < advances[advance].preq[1]) {
      if (-1 < advances[advance].preq[0]) {
        x2 = x2 + text_width + 3;
        text_clear();
        text_append_comma();
        surface_draw_text
                  ((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
        text_width = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
        text_width += 4;
        x2 += text_width;
      }
      text_clear();
      text_append_string_id(advances[advances[advance].preq[1]].name);
      text_width = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
      line_height = font_line_spacing(font2);
      SetRect(&link_rect,x2,y2,text_width + x2 + 5,line_height + y2);
      pedia_add_link(this,(int)advances[advance].preq[1],x2,y2,0,link_rect.left,
                         link_rect.top,link_rect.right,link_rect.bottom);
    }
  }
  y2 += row_height;
  x2 = this->content_left + 2;
  text_clear();
  text_append_label(0x7a);
  text_append_colon();
  measure = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  list_x2 = x2 + measure + 2;
  if (related_count != 0) {
    surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
  }
  text_clear();
  for (advance2 = 0; advance2 < 100; advance2++) {
    is_child = 0;
    advance3 = -1;
    if (advances[advance2].preq[0] == advance) {
      is_child = 1;
      advance3 = (iptr)advances[advance2].preq[1];
    }
    else if (advances[advance2].preq[1] == advance) {
      is_child = 1;
      advance3 = (iptr)advances[advance2].preq[0];
    }
    if (is_child != 0) {
      x2 = list_x2;
      text_clear();
      text_append_string_id(advances[advance2].name);
      text_width = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
      line_height = font_line_spacing(font2);
      SetRect(&link_rect,x2,y2,text_width + x2 + 2,line_height + y2);
      pedia_add_link(this,advance2,x2,y2,0,link_rect.left,link_rect.top,
                         link_rect.right,link_rect.bottom);
      measure = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
      x2 = x2 + measure + 2;
      if (-1 < advance3) {
        text_clear();
        text_append_space();
        text_append_lparen();
        text_append_label(0x7b);
        text_append_space();
        surface_draw_text
                  ((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
        measure = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
        x2 = x2 + measure + 2;
        text_clear();
        text_append_string_id(advances[advance3].name);
        text_width = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
        line_height = font_line_spacing(font2);
        SetRect(&link_rect,x2,y2,text_width + x2 + 2,line_height + y2);
        pedia_add_link(this,advance3,x2,y2,0,link_rect.left,link_rect.top,
                           link_rect.right,link_rect.bottom);
        measure = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
        x2 = x2 + measure + 2;
        text_clear();
        text_append_rparen();
        surface_draw_text
                  ((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
      }
      y2 += row_height;
    }
  }
  in_right_col = 0;
  x2 = list_x2;
  for (improvement = 1; improvement < 0x43; improvement++) {
    if (improvements[improvement].preq == advance) {
      sprite_draw
                ((Sprite *)(&improvement_icon_sprites + improvement * 0x3c),(iptr)impr_ctx,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),
                 x2,y2);
      measure = sprite_get_width((Sprite *)(&improvement_icon_sprites + improvement * 0x3c))
      ;
      x2 = x2 + measure + 5;
      text_clear();
      text_append_string_id(improvements[improvement].name);
      text_width = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
      line_height = font_line_spacing(font2);
      if ((in_right_col == 0) &&
         (measure = rect_width((iptr)&this->content_left),
         measure / 2 <= (int)(text_width + x2 + 5))) {
        measure = rect_width((iptr)&this->content_left);
        text_width = (measure / 2 - 5) - x2;
      }
      SetRect(&link_rect,x2,y2,text_width + x2 + 5,line_height + y2);
      if (improvement < 0x27) {
        pedia_add_link(this,improvement,x2,y2,1,link_rect.left,link_rect.top,
                           link_rect.right,link_rect.bottom);
      }
      else {
        pedia_add_link(this,improvement,x2,y2,2,link_rect.left,link_rect.top,
                           link_rect.right,link_rect.bottom);
      }
      was_right = in_right_col != 0;
      if (was_right) {
        y2 += row_height;
        x2 = list_x2;
      }
      else {
        measure = rect_width((iptr)&this->content_left);
        x2 = measure / 2;
      }
      in_right_col = (uint)!was_right;
    }
  }
  x2 = list_x2;
  if (in_right_col == 1) {
    y2 += row_height;
  }
  in_right_col = 0;
  for (unit_type = 0; unit_type < 0x3e; unit_type++) {
    if (unit_types[unit_type].prerequisite == advance) {
      if (related_count < 0xb) {
        measure = sprite_height
                          ((Sprite *)(&unit_sprites + unit_type * 0x3c));
        center_y = y2 + measure / 2;
        measure = sprite_get_height
                          ((Sprite *)(&unit_sprites + unit_type * 0x3c));
        sprite_draw
                  ((Sprite *)(&unit_sprites + unit_type * 0x3c),(iptr)unit_ctx,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),
                   x2,center_y - measure / 2);
        measure = sprite_width
                          ((Sprite *)(&unit_sprites + unit_type * 0x3c));
        x2 = x2 + measure + 5;
        measure = sprite_height
                          ((Sprite *)(&unit_sprites + unit_type * 0x3c));
        center_y = font_line_spacing(font2);
        unit_text_y = (measure / 2 - center_y / 2) + y2;
      }
      else {
        unit_text_y = y2;
      }
      text_clear();
      label = label_string(unit_types[unit_type].name);
      text_append(label);
      text_width = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
      line_height = font_line_spacing(font2);
      SetRect(&link_rect,x2,unit_text_y,text_width + x2 + 5,line_height + unit_text_y);
      pedia_add_link(this,unit_type,x2,unit_text_y,3,link_rect.left,link_rect.top,
                         link_rect.right,link_rect.bottom);
      if (in_right_col == 0) {
        measure = rect_width((iptr)&this->content_left);
        x2 = measure / 2;
        in_right_col = 1;
        prev_unit_height = sprite_get_height
                              ((Sprite *)(&unit_sprites + unit_type * 0x3c));
      }
      else {
        x2 = list_x2;
        in_right_col = 0;
        if (related_count < 0xb) {
          measure = sprite_get_height
                            ((Sprite *)(&unit_sprites + unit_type * 0x3c));
          if (measure < prev_unit_height) {
            y2 += prev_unit_height;
          }
          else {
            measure = sprite_get_height
                              ((Sprite *)(&unit_sprites + unit_type * 0x3c));
            y2 += measure;
          }
        }
        else {
          y2 += row_height;
        }
      }
    }
  }
  x2 = list_x2;
  if (in_right_col == 1) {
    measure = sprite_get_height((Sprite *)(&unit_sprites + unit_type * 0x3c));
    if (measure < prev_unit_height) {
      y2 += prev_unit_height;
    }
    else {
      measure = sprite_get_height((Sprite *)(&unit_sprites + unit_type * 0x3c))
      ;
      y2 += measure;
    }
  }
  pedia_file = s_PEDIA_00633d74;
  measure = _strcmp(&scenario_dir_path,&game_home_dir);
  if (measure != 0) {
    __chdir(&scenario_dir_path);
    crt_strcpy(&line_buf,s_describe__00633d7c);
    crt_strcat(&line_buf,&lang_file_ext);
    measure = file_exists((iptr)&line_buf);
    if (measure == 0) {
      ctrl_disable((Control *)(((PictureWindow *)this)->advance_detail_describe_button));
      __chdir(&game_home_dir);
      return;
    }
    __chdir(&game_home_dir);
  }
  has_pedia = _strcmp(&scenario_dir_path,&game_home_dir);
  if (has_pedia != 0) {
    __chdir(&scenario_dir_path);
    crt_strcpy(&line_buf,s_pedia__00633d88);
    crt_strcat(&line_buf,&lang_file_ext);
    measure = file_exists((iptr)&line_buf);
    if (measure == 0) {
      has_pedia = 0;
    }
    __chdir(&game_home_dir);
  }
  str_clear((iptr)&line_buf);
  measure = text_open_section((iptr)pedia_file,ADDR(0x633d90, ((u8 *)&g.d_00633d90)));
  if (measure == 0) {
    line = (char *)text_read_line(1);
    if ((has_pedia == 0) &&
       ((((advance == 0x36 || (advance == 0xf)) || (advance == 0x1f)) ||
        ((advance == 0x47 || (advance == 0x15)))))) {
      surface_draw_text
                ((DibSurface *)this,(iptr)font2,(iptr)(line + (*line == '^')),
                 x2,y2,5);
      y2 += row_height;
    }
    line = (char *)text_read_line(1);
    if ((has_pedia == 0) && (advance == 0x12)) {
      surface_draw_text
                ((DibSurface *)this,(iptr)font2,(iptr)(line + (*line == '^')),
                 x2,y2,5);
      y2 += row_height;
    }
    line = (char *)text_read_line(1);
    if ((has_pedia == 0) && (advance == 0x42)) {
      surface_draw_text
                ((DibSurface *)this,(iptr)font2,(iptr)(line + (*line == '^')),
                 x2,y2,5);
      y2 += row_height;
    }
    line = (char *)text_read_line(1);
    if ((has_pedia == 0) && (advance == 0x43)) {
      surface_draw_text
                ((DibSurface *)this,(iptr)font2,(iptr)(line + (*line == '^')),
                 x2,y2,5);
      y2 += row_height;
    }
    line = (char *)text_read_line(1);
    if ((has_pedia == 0) && (advance == 0x46)) {
      surface_draw_text
                ((DibSurface *)this,(iptr)font2,(iptr)(line + (*line == '^')),
                 x2,y2,5);
      y2 += row_height;
    }
    line = (char *)text_read_line(1);
    if ((has_pedia == 0) && (advance == 0x38)) {
      surface_draw_text
                ((DibSurface *)this,(iptr)font2,(iptr)(line + (*line == '^')),
                 x2,y2,5);
      y2 += row_height;
    }
    line = (char *)text_read_line(1);
    if ((has_pedia == 0) && (advance == 0x18)) {
      surface_draw_text
                ((DibSurface *)this,(iptr)font2,(iptr)(line + (*line == '^')),
                 x2,y2,5);
      y2 += row_height;
    }
    line = (char *)text_read_line(1);
    if ((has_pedia == 0) && (advance == 0x59)) {
      surface_draw_text
                ((DibSurface *)this,(iptr)font2,(iptr)(line + (*line == '^')),
                 x2,y2,5);
      y2 += row_height;
    }
    line = (char *)text_read_line(1);
    if ((has_pedia == 0) && (advance == 0x3b)) {
      surface_draw_text
                ((DibSurface *)this,(iptr)font2,(iptr)(line + (*line == '^')),
                 x2,y2,5);
      y2 += row_height;
    }
    line = (char *)text_read_line(1);
    if ((has_pedia == 0) && (advance == 0x20)) {
      surface_draw_text
                ((DibSurface *)this,(iptr)font2,(iptr)(line + (*line == '^')),
                 x2,y2,5);
      y2 += row_height;
    }
    line = (char *)text_read_line(1);
    if ((has_pedia == 0) && (advance == 0x3c)) {
      surface_draw_text
                ((DibSurface *)this,(iptr)font2,(iptr)(line + (*line == '^')),
                 x2,y2,5);
      y2 += row_height;
    }
    line = (char *)text_read_line(1);
    if ((has_pedia == 0) && (advance == 0xf)) {
      surface_draw_text
                ((DibSurface *)this,(iptr)font2,(iptr)(line + (*line == '^')),
                 x2,y2,5);
      y2 += row_height;
    }
    line = (char *)text_read_line(1);
    str_append_space((iptr)line);
    crt_strcpy(&line_buf,line);
    if (line_buf == '^') {
      rest_len = _strlen(line_rest);
      crt_memmove(&line_buf,line_rest,rest_len);
    }
    for (wonder = 0; wonder < 0x1c; wonder++) {
      if (wonder_expires[wonder] == advance) {
        surface_draw_text
                  ((DibSurface *)this,(iptr)font2,(iptr)&line_buf,x2,y2,5);
        measure = font_text_width(font2,(iptr)&line_buf);
        x2 += measure;
        text_clear();
        text_append_string_id(improvements[wonder + 0x27].name);
        text_width = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
        line_height = font_line_spacing(font2);
        SetRect(&link_rect,x2,y2,text_width + x2,line_height + y2);
        pedia_add_link(this,wonder + 0x27,x2,y2,2,link_rect.left,link_rect.top,
                           link_rect.right,link_rect.bottom);
        measure = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
        x2 = x2 + measure + 2;
        text_clear();
        text_append_period();
        surface_draw_text
                  ((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
        x2 = list_x2;
        y2 += row_height;
      }
    }
  }
  pedia_update_describe_button((ListPaneWindow *)this,this->resize_border);
  surface_set_clip((DibSurface *)this,(iptr)saved_clip);
  wnd_blit_surface_rect((DibSurface *)this,(iptr)&this->content_left);
  return;
}
#undef list_text_color
#undef panel_margin_x
#undef unit_ctx
#undef impr_ctx
#undef icon_ctx
#undef wonder
#undef is_child
#undef advance3
#undef prev_unit_height
#undef advance
#undef pedia_file
#undef improvement
#undef line_height
#undef unit_type
#undef y2
#undef x2
#undef line
#undef advance2
#undef unit_text_y
#undef has_pedia
#undef link_rect
#undef text_width
#undef related_count
#undef line_buf
#undef line_rest
#undef row_height
#undef list_x2
#undef saved_clip
#undef font2
#undef in_right_col

/* 00566584 auto */
#define map_redraw_busy (*(int *)((u8 *)&g.d_006ad908))
#define pedia_advance_names (*(i32 *)((u8 *)&g.d_006a7d44))
#define pedia_closed (*(int *)((u8 *)&g.d_006a677c))
#define advance_idx (*(u32 *)(frame_ + FRAME_OFF(0)))
void __thiscall pedia_show_topic_modal(DocumentWindow *this,iptr advance_id)

{
  i32 name_text;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((pedia_closed != 0) && (map_redraw_busy == 0)) {
    advance_idx = 0;
    while (((int)advance_idx < (int)this->pedia_advance_count &&
           (*(int *)(this->advance_sort_keys + advance_idx * 4 + 400) != advance_id))) {
      advance_idx++;
    }
    if (this->pedia_advance_count != advance_idx) {
      pedia_open_category((MediaWindow *)this,1,0);
      this->resize_border = advance_idx;
      *(u32 *)(((PictureWindow *)this)->list_selected_index) = advance_idx;
      this->client_x = 1;
      this->border_width = 1;
      pedia_clear_links((WindowObjectView *)this);
      pedia_update_controls((MediaWindow *)this);
      name_text = pedia_lookup_text(pedia_advance_names,advance_idx);
      crt_strcpy(this->pedia_title_text_2,name_text);
      pedia_draw_frame((MediaWindow *)this);
      pedia_draw_advance_page(this);
      window_show((WindowObjectView *)this);
      wnd_blit_surface((DibSurface *)&pedia_window);
      wnd_activate((Wnd *)&pedia_window_wnd);
      wnd_set_modal_idle_callback((ModalMenuWindow *)&pedia_window_wnd,ADDR(0x401843, pedia_modal_idle));
      wnd_run_modal_loop((ModalMenuWindow *)&pedia_window_wnd);
      wnd_set_modal_idle_callback((ModalMenuWindow *)&pedia_window_wnd,0);
    }
  }
  return;
}
#undef map_redraw_busy
#undef pedia_advance_names
#undef pedia_closed
#undef advance_idx

/* 005666da auto */
#define gp_line_y (*(int *)(frame_ + FRAME_OFF(4)))
#define grand_line_y (*(int *)(frame_ + FRAME_OFF(8)))
#define parent_line_y (*(int *)(frame_ + FRAME_OFF(12)))
#define gp_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(16)))
#define grand_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(32)))
#define parent_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(48)))
#define root_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(64)))
#define advance (*(iptr *)(frame_ + FRAME_OFF(80)))
#define line_height (*(int *)(frame_ + FRAME_OFF(84)))
#define tier2_anchor_y (*(int (*)[8])(frame_ + FRAME_OFF(88)))
#define icon (*(Sprite * *)(frame_ + FRAME_OFF(120)))
#define tier2_anchor_x (*(int (*)[8])(frame_ + FRAME_OFF(124)))
#define tier3_step (*(int *)(frame_ + FRAME_OFF(156)))
#define j (*(iptr *)(frame_ + FRAME_OFF(160)))
#define y2 (*(int *)(frame_ + FRAME_OFF(164)))
#define i (*(iptr *)(frame_ + FRAME_OFF(168)))
#define tier3_ids (*(int (*)[8])(frame_ + FRAME_OFF(172)))
#define x2 (*(int *)(frame_ + FRAME_OFF(204)))
#define icon_width (*(int *)(frame_ + FRAME_OFF(208)))
#define tier1_anchors (*(int (*)[4])(frame_ + FRAME_OFF(212)))
#define root_anchor_y (*(int *)(frame_ + FRAME_OFF(228)))
#define root_anchor_y2 (*(int *)(frame_ + FRAME_OFF(232)))
#define icon_left (*(int *)(frame_ + FRAME_OFF(252)))
#define icon_top (*(int *)(frame_ + FRAME_OFF(256)))
#define icon_right (*(int *)(frame_ + FRAME_OFF(260)))
#define icon_bottom (*(int *)(frame_ + FRAME_OFF(264)))
#define root_anchor_x (*(int (*)[3])(frame_ + FRAME_OFF(268)))
#define link_rect (*(tagRECT *)(frame_ + FRAME_OFF(280)))
#define tier2_ids (*(int (*)[4])(frame_ + FRAME_OFF(296)))
#define saved_clip (*(i8 (*)[16])(frame_ + FRAME_OFF(312)))
#define font2 (*(GameFont * *)(frame_ + FRAME_OFF(328)))
#define parent_ids (*(int (*)[2])(frame_ + FRAME_OFF(332)))
void __thiscall pedia_draw_advance_tree(DocumentWindow *this)

{
  int measure;
  int *icon_rect;
  int measure2;
  int icon_w;
  i8 frame_[FRAME_OFF(344)] __attribute__((aligned(8)));  /* original stack frame */
  
  surface_get_clip((DibSurface *)this,(iptr)saved_clip);
  surface_set_clip((DibSurface *)this,(iptr)&this->content_left);
  pedia_clear_links((WindowObjectView *)this);
  pedia_update_controls((MediaWindow *)this);
  pedia_fill_background((WindowObjectView *)this,(iptr)&this->content_left,2);
  font2 = (GameFont *)&font_size21;
  advance = *(iptr *)(this->advance_sort_keys + this->resize_border * 4 + 400);
  text_clear();
  text_append_string_id(advances[advance].name);
  root_anchor_x[2] = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  line_height = font_line_spacing(font2);
  icon = (Sprite *)
             (&advance_category_icon_sprites +
             (char)advances[advance].category * 0xf0 + (char)advances[advance].epoch * 0x3c);
  icon_width = sprite_get_width(icon);
  icon_width += 3;
  x2 = (this->content_right - 3) - (icon_width + root_anchor_x[2]);
  measure = rect_height((iptr)&this->content_left);
  y2 = (this->content_top + measure / 2) - line_height / 2;
  icon_rect = (int *)sprite_draw(icon,(iptr)root_ctx,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),x2,y2);
  icon_left = *icon_rect;
  icon_top = icon_rect[1];
  icon_right = icon_rect[2];
  icon_bottom = icon_rect[3];
  x2 += icon_width;
  SetRect(&link_rect,x2 - icon_width,y2,root_anchor_x[2] + x2 + 5,line_height + y2);
  pedia_add_link(this,advance,x2,y2,0,link_rect.left,link_rect.top,link_rect.right,
                     link_rect.bottom);
  parent_ids[0] = (int)advances[advance].preq[0];
  parent_ids[1] = (int)advances[advance].preq[1];
  root_anchor_x[1] = icon_left;
  root_anchor_x[0] = icon_left;
  measure = rect_height((iptr)(tier1_anchors + 10));
  root_anchor_y = icon_top + measure / 2;
  root_anchor_y2 = root_anchor_y;
  line_height = font_line_spacing(font2);
  measure = rect_height((iptr)&this->content_left);
  y2 = (this->content_top + ((int)(measure + (measure >> 0x1f & 3U)) >> 2)) - line_height / 2;
  for (i = 0; i < 2; i++) {
    tier2_ids[i * 2] = -1;
    tier2_ids[i * 2 + 1] = -1;
    if (-1 < parent_ids[i]) {
      text_clear();
      text_append_string_id(advances[parent_ids[i]].name);
      root_anchor_x[2] = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
      icon = (Sprite *)
                 (&advance_category_icon_sprites +
                 (char)advances[parent_ids[i]].category * 0xf0 +
                 (char)advances[parent_ids[i]].epoch * 0x3c);
      icon_width = sprite_get_width(icon);
      icon_width += 3;
      measure = rect_width((iptr)&this->content_left);
      measure2 = rect_width((iptr)&this->content_left);
      x2 = ((int)(measure * 2 + (measure * 2 >> 0x1f & 3U)) >> 2) +
                 ((int)(measure2 + (measure2 >> 0x1f & 7U)) >> 3) + this->content_left;
      icon_rect = (int *)sprite_draw
                                (icon,(iptr)parent_ctx,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),x2,y2);
      icon_left = *icon_rect;
      icon_top = icon_rect[1];
      icon_right = icon_rect[2];
      parent_line_y = icon_rect[3];
      icon_bottom = parent_line_y;
      if (i != 0) {
        parent_line_y = icon_rect[1] - 1;
      }
      measure = tier1_anchors[i + 4];
      measure2 = root_anchor_x[i];
      icon_w = rect_width((iptr)(tier1_anchors + 10));
      pedia_draw_tree_connector
                ((DibSurface *)this,icon_left + icon_w / 2,parent_line_y,measure2,measure);
      x2 += icon_width;
      tier2_ids[i * 2] = (int)advances[parent_ids[i]].preq[0];
      tier2_ids[i * 2 + 1] = (int)advances[parent_ids[i]].preq[1];
      tier1_anchors[i * 2 + 7] = icon_left;
      tier1_anchors[i * 2 + 6] = tier1_anchors[i * 2 + 7];
      measure = rect_height((iptr)(tier1_anchors + 10));
      tier1_anchors[i * 2 + 1] = icon_top + measure / 2;
      tier1_anchors[i * 2] = tier1_anchors[i * 2 + 1];
      SetRect(&link_rect,x2 - icon_width,y2,root_anchor_x[2] + x2 + 5,line_height + y2
             );
      pedia_add_link(this,parent_ids[i],x2,y2,0,link_rect.left,link_rect.top,
                         link_rect.right,link_rect.bottom);
    }
    measure = rect_height((iptr)&this->content_left);
    y2 += measure / 2;
  }
  line_height = font_line_spacing(font2);
  measure = rect_height((iptr)&this->content_left);
  y2 = (this->content_top + ((int)(measure + (measure >> 0x1f & 7U)) >> 3)) - line_height / 2;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++) {
      tier3_ids[(i * 2 + j) * 2] = -1;
      tier3_ids[(i * 2 + j) * 2 + 1] = -1;
      if (-1 < tier2_ids[i * 2 + j]) {
        text_clear();
        text_append_string_id(advances[tier2_ids[i * 2 + j]].name);
        root_anchor_x[2] = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
        icon = (Sprite *)
                   (&advance_category_icon_sprites +
                   (char)advances[tier2_ids[i * 2 + j]].epoch * 0x3c +
                   (char)advances[tier2_ids[i * 2 + j]].category * 0xf0);
        icon_width = sprite_get_width(icon);
        icon_width += 3;
        measure = rect_width((iptr)&this->content_left);
        measure2 = rect_width((iptr)&this->content_left);
        x2 = ((int)(measure + (measure >> 0x1f & 3U)) >> 2) +
                   ((int)(measure2 + (measure2 >> 0x1f & 7U)) >> 3) + this->content_left;
        icon_rect = (int *)sprite_draw
                                  (icon,(iptr)grand_ctx,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),x2,y2);
        icon_left = *icon_rect;
        icon_top = icon_rect[1];
        icon_right = icon_rect[2];
        grand_line_y = icon_rect[3];
        icon_bottom = grand_line_y;
        if (j != 0) {
          grand_line_y = icon_rect[1] - 1;
        }
        measure = tier1_anchors[i * 2 + j];
        measure2 = tier1_anchors[i * 2 + j + 6];
        icon_w = rect_width((iptr)(tier1_anchors + 10));
        pedia_draw_tree_connector
                  ((DibSurface *)this,icon_left + icon_w / 2,grand_line_y,measure2,measure);
        x2 += icon_width;
        tier3_ids[(i * 2 + j) * 2] =
             (int)advances[tier2_ids[i * 2 + j]].preq[0];
        tier3_ids[(i * 2 + j) * 2 + 1] =
             (int)advances[tier2_ids[i * 2 + j]].preq[1];
        tier2_anchor_x[(i * 2 + j) * 2 + 1] = icon_left;
        tier2_anchor_x[(i * 2 + j) * 2] = tier2_anchor_x[(i * 2 + j) * 2 + 1];
        measure = rect_height((iptr)(tier1_anchors + 10));
        tier2_anchor_y[(i * 2 + j) * 2 + 1] = icon_top + measure / 2;
        tier2_anchor_y[(i * 2 + j) * 2] = tier2_anchor_y[(i * 2 + j) * 2 + 1];
        SetRect(&link_rect,x2 - icon_width,y2,root_anchor_x[2] + x2 + 5,
                line_height + y2);
        pedia_add_link(this,tier2_ids[i * 2 + j],x2,y2,0,
                           link_rect.left,link_rect.top,link_rect.right,link_rect.bottom);
      }
      measure = rect_height((iptr)&this->content_left);
      y2 += ((int)(measure + (measure >> 0x1f & 3U)) >> 2);
    }
  }
  measure = rect_height((iptr)&this->content_left);
  tier3_step = (int)(measure + (measure >> 0x1f & 7U)) >> 3;
  line_height = font_line_spacing(font2);
  x2 = this->content_left + 2;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 2; j++) {
      y2 = ((i * 2 + j) * tier3_step + this->content_top + tier3_step / 2) -
                 line_height / 2;
      if (-1 < tier3_ids[i * 2 + j]) {
        text_clear();
        text_append_string_id(advances[tier3_ids[i * 2 + j]].name);
        root_anchor_x[2] = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
        icon = (Sprite *)
                   (&advance_category_icon_sprites +
                   (char)advances[tier3_ids[i * 2 + j]].category * 0xf0 +
                   (char)advances[tier3_ids[i * 2 + j]].epoch * 0x3c);
        icon_width = sprite_get_width(icon);
        icon_width += 3;
        icon_rect = (int *)sprite_draw
                                  (icon,(iptr)gp_ctx,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),x2,y2);
        icon_left = *icon_rect;
        icon_top = icon_rect[1];
        icon_right = icon_rect[2];
        gp_line_y = icon_rect[3];
        icon_bottom = gp_line_y;
        if (j != 0) {
          gp_line_y = icon_rect[1] - 1;
        }
        measure = tier2_anchor_y[i * 2 + j];
        measure2 = tier2_anchor_x[i * 2 + j];
        icon_w = rect_width((iptr)(tier1_anchors + 10));
        pedia_draw_tree_connector
                  ((DibSurface *)this,icon_left + icon_w / 2,gp_line_y,measure2,measure);
        if ((-1 < advances[tier3_ids[i * 2 + j]].preq[0]) ||
           (-1 < advances[tier3_ids[i * 2 + j]].preq[1])) {
          measure = rect_height((iptr)(tier1_anchors + 10));
          pedia_draw_tree_stub((MediaWindow *)this,icon_left,icon_top + measure / 2);
        }
        SetRect(&link_rect,x2,y2,icon_width + root_anchor_x[2] + x2 + 5,
                line_height + y2);
        pedia_add_link(this,tier3_ids[i * 2 + j],icon_width + x2,y2,0,
                           link_rect.left,link_rect.top,link_rect.right,link_rect.bottom);
      }
      measure = rect_height((iptr)&this->content_left);
      y2 += ((int)(measure + (measure >> 0x1f & 7U)) >> 3);
    }
  }
  surface_set_clip((DibSurface *)this,(iptr)saved_clip);
  wnd_blit_surface_rect((DibSurface *)this,(iptr)&this->content_left);
  return;
}
#undef gp_line_y
#undef grand_line_y
#undef parent_line_y
#undef gp_ctx
#undef grand_ctx
#undef parent_ctx
#undef root_ctx
#undef advance
#undef line_height
#undef tier2_anchor_y
#undef icon
#undef tier2_anchor_x
#undef tier3_step
#undef j
#undef y2
#undef i
#undef tier3_ids
#undef x2
#undef icon_width
#undef tier1_anchors
#undef root_anchor_y
#undef root_anchor_y2
#undef icon_left
#undef icon_top
#undef icon_right
#undef icon_bottom
#undef root_anchor_x
#undef link_rect
#undef tier2_ids
#undef saved_clip
#undef font2
#undef parent_ids

/* 005674b9 auto */
void __thiscall
pedia_draw_tree_connector(DibSurface *this,int x,int y_from,int x_to,int y_to)

{
  if (y_to < y_from) {
    y_from++;
  }
  else {
    y_from--;
  }
  gfx_set_text_color_index(10);
  surface_draw_line(this,x - 1,y_from,x - 1,y_to);
  surface_draw_line(this,x + 1,y_from,x + 1,y_to);
  gfx_set_text_color_index(0x7a);
  surface_draw_line(this,x,y_from,x,y_to);
  if (x < x_to) {
    gfx_set_text_color_index(10);
    surface_draw_line(this,x + 1,y_to - 1,x_to,y_to - 1);
    surface_draw_line(this,x + 1,y_to + 1,x_to,y_to + 1);
    gfx_set_text_color_index(0x7a);
    surface_draw_line(this,x + 1,y_to,x_to,y_to);
  }
  return;
}

/* 005675b7 auto */
void __thiscall pedia_draw_tree_stub(MediaWindow *this,i32 x,int y)

{
  gfx_set_text_color_index(10);
  surface_draw_line
            ((DibSurface *)this,x,y - 1,this->content_left,y - 1);
  surface_draw_line((DibSurface *)this,x,y + 1,this->content_left,y + 1)
  ;
  gfx_set_text_color_index(0x7a);
  surface_draw_line((DibSurface *)this,x,y,this->content_left,y);
  return;
}

/* 005680a0 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl shared_palette_global_init(void)

{
  shared_palette_static_init();
  shared_palette_reg_atexit();
  return;
}

/* 005680ba auto */
void __cdecl shared_palette_static_init(void)

{
  palette_init((GamePalette *)&art_palette);
  return;
}

/* 005680d4 auto */
void __cdecl shared_palette_reg_atexit(void)

{
  _atexit(shared_palette_static_dtor);
  return;
}

/* 005680f1 auto */
void __cdecl shared_palette_static_dtor(void)

{
  palette_destroy((GamePalette *)&art_palette);
  return;
}

/* 00599a20 auto */
#define i (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall pedia_init_improvement_list(DocumentWindow *this,iptr unused_arg)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((int)this->resize_border < 0) || ((int)this->pedia_improve_count <= (int)this->resize_border)) {
    this->resize_border = 0;
  }
  *(u32 *)(((PictureWindow *)this)->list_item_table) = this->pedia_improve_count;
  *(u32 *)(((PictureWindow *)this)->list_selected_index) = this->resize_border;
  *(u32 *)(((PictureWindow *)this)->list_top_index) = this->resize_border;
  while (pedia_list_top % 9 != 0) {
    *(int *)(((PictureWindow *)this)->list_top_index) = *(int *)(((PictureWindow *)this)->list_top_index) - 1;
  }
  for (i = 0; i < (int)this->pedia_improve_count; i++) {
    *(i32 *)(((PictureWindow *)this)->description_edit_body + i * 4 + 0x8c) =
         *(i32 *)(this->improvement_sort_keys + i * 4 + 0x9c);
  }
  scrollbar_set_range
            ((Control *)((u8 *)&((PictureWindow *)this)->list_scrollbar),0,*(int *)(((PictureWindow *)this)->list_item_table) / 9);
  scrollbar_set_pos
            ((ClickControl *)((u8 *)&((PictureWindow *)this)->list_scrollbar),*(int *)(((PictureWindow *)this)->list_top_index) / 9);
  if (*(int *)(((PictureWindow *)this)->list_item_table) < 1) {
    ((PictureWindow *)this)->list_top_index[0] = 0xff;
    ((PictureWindow *)this)->list_top_index_byte1[0] = 0xff;
    ((PictureWindow *)this)->list_top_index_byte2[0] = 0xff;
    ((PictureWindow *)this)->list_top_index_byte3[0] = 0xff;
  }
  pedia_update_controls((MediaWindow *)this);
  wnd_set_focus((WndBase *)&pedia_window_wnd);
  wnd_activate((Wnd *)&pedia_window_wnd);
  pedia_redraw((PediaRedrawView *)&pedia_window);
  return;
}
#undef i

/* 00599b8d auto */
#define list_text_color (*(i32 *)((u8 *)&g.d_00635a1c))
#define panel_margin_x (*(int *)((u8 *)&g.d_0062d858))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define coin_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define shield_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(16)))
#define icon_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(32)))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(48)))
#define text_rect (*(tagRECT *)(frame_ + FRAME_OFF(52)))
#define line_height (*(int *)(frame_ + FRAME_OFF(68)))
#define icon_width (*(int *)(frame_ + FRAME_OFF(72)))
#define scale_num2 (*(i32 *)(frame_ + FRAME_OFF(76)))
#define y2 (*(int *)(frame_ + FRAME_OFF(80)))
#define scale_den2 (*(i32 *)(frame_ + FRAME_OFF(84)))
#define x2 (*(int *)(frame_ + FRAME_OFF(88)))
#define content_width2 (*(int *)(frame_ + FRAME_OFF(92)))
#define value_x (*(int *)(frame_ + FRAME_OFF(96)))
#define unused_flag (*(i32 *)(frame_ + FRAME_OFF(100)))
#define link_rect (*(tagRECT *)(frame_ + FRAME_OFF(104)))
#define text_width (*(int *)(frame_ + FRAME_OFF(120)))
#define row_height (*(int *)(frame_ + FRAME_OFF(124)))
#define saved_clip (*(i8 (*)[16])(frame_ + FRAME_OFF(128)))
#define font2 (*(GameFont * *)(frame_ + FRAME_OFF(144)))
/* WARNING: Removing unreachable block (ram,0x00599e9a) */
/* WARNING: Removing unreachable block (ram,0x00599fc4) */

void __thiscall pedia_draw_improvement_page(DocumentWindow *this)

{
  int measure;
  size_t text_len;
  int center_y;
  u32 yBottom;
  i8 frame_[FRAME_OFF(152)] __attribute__((aligned(8)));  /* original stack frame */
  
  unused_flag = 0;
  surface_get_clip((DibSurface *)this,(iptr)saved_clip);
  surface_set_clip((DibSurface *)this,(iptr)&this->content_left);
  pedia_update_controls((MediaWindow *)this);
  pedia_fill_background((WindowObjectView *)this,(iptr)&this->content_left,2);
  font2 = (GameFont *)&font_size21;
  x2 = this->content_left + 10;
  content_width2 = rect_width((iptr)&this->content_left);
  row_height = font_cached_height(font2);
  y2 = this->content_top + 8;
  value_x = content_width2 / 2 - 100;
  improvement = *(iptr *)(this->improvement_sort_keys + this->resize_border * 4 + 0x9c);
  gfx_get_scale_ratio((iptr)&scale_num2,(iptr)&scale_den2);
  gfx_set_scale_ratio(2,1);
  icon_width = sprite_get_width((Sprite *)(&improvement_icon_sprites + improvement * 0x3c));
  icon_width += panel_margin_x * 2;
  sprite_draw
            ((Sprite *)(&improvement_icon_sprites + improvement * 0x3c),(iptr)icon_ctx,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),x2,
             y2);
  gfx_set_scale_ratio(scale_num2,scale_den2);
  gfx_set_text_color_index(list_text_color);
  x2 = this->content_left + 10;
  measure = sprite_height((Sprite *)(&improvement_icon_sprites + improvement * 0x3c));
  y2 = y2 + measure * 2 + 5;
  text_clear();
  text_append_label(0x79);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
  measure = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  x2 = x2 + measure + 5;
  text_clear();
  if (improvements[improvement].preq < '\0') {
    text_append_label(0xe);
    surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
  }
  else {
    text_append_string_id(advances[improvements[improvement].preq].name);
    text_width = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    line_height = font_line_spacing(font2);
    SetRect(&link_rect,x2,y2,x2 + text_width + 5,y2 + line_height);
    pedia_add_link(this,(int)improvements[improvement].preq,x2,y2,0,link_rect.left,
                       link_rect.top,link_rect.right,link_rect.bottom);
  }
  value_x = x2;
  x2 = this->content_left + 10;
  y2 += row_height;
  text_clear();
  text_append_label(0x84);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
  text_clear();
  _sprintf(&text_buffer,&pedia_improve_cost_fmt,(uint)improvements[improvement].cost * 10);
  surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),value_x,y2,5);
  measure = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  x2 = value_x + measure + 3;
  center_y = y2 + row_height / 2;
  measure = sprite_get_height((Sprite *)&shield_icon_sprite);
  sprite_draw
            ((Sprite *)&shield_icon_sprite,(iptr)shield_ctx,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),x2,center_y - measure / 2);
  x2 = this->content_left + 10;
  y2 += row_height;
  text_clear();
  text_append_label(0x9e);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
  text_clear();
  _sprintf(&text_buffer,&pedia_improve_upkeep_fmt,(uint)improvements[improvement].upkeep);
  surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),value_x,y2,5);
  measure = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  x2 = value_x + measure + 3;
  center_y = y2 + row_height / 2;
  measure = sprite_get_height((Sprite *)&gold_coin_icon_sprite);
  sprite_draw
            ((Sprite *)&gold_coin_icon_sprite,(iptr)coin_ctx,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),x2,center_y - measure / 2);
  x2 = this->content_left + 10;
  y2 += row_height * 2;
  pedia_load_improvement_text((WindowObjectView *)this,improvement);
  text_len = _strlen(&text_buffer);
  if (text_len != 0) {
    yBottom = this->content_bottom;
    measure = rect_width((iptr)&this->content_left);
    SetRect(&text_rect,x2,y2,measure - 10 + x2,yBottom);
    surface_draw_text_rect((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),(iptr)&text_rect,5);
  }
  pedia_update_describe_button((ListPaneWindow *)this,this->resize_border);
  surface_set_clip((DibSurface *)this,(iptr)saved_clip);
  wnd_blit_surface_rect((DibSurface *)this,(iptr)&this->content_left);
  return;
}
#undef list_text_color
#undef panel_margin_x
#undef text_buffer
#undef coin_ctx
#undef shield_ctx
#undef icon_ctx
#undef improvement
#undef text_rect
#undef line_height
#undef icon_width
#undef scale_num2
#undef y2
#undef scale_den2
#undef x2
#undef content_width2
#undef value_x
#undef unused_flag
#undef link_rect
#undef text_width
#undef row_height
#undef saved_clip
#undef font2

/* 0059a15d auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define desc_buf (*(char (*)[4096])(frame_ + FRAME_OFF(4)))
#define line_buf (*(i8 (*)[256])(frame_ + FRAME_OFF(4100)))
#define section_name (*(i8 (*)[8])(frame_ + FRAME_OFF(4356)))
void __thiscall pedia_load_improvement_text(WindowObjectView *this,iptr improvement_id)

{
  int status;
  char *_Str;
  size_t len;
  i32 ret_addr;
  i8 frame_[FRAME_OFF(4392)] __attribute__((aligned(8)));  /* original stack frame */
  str_clear((iptr)desc_buf);
  ret_addr = 0x59a190;
  crt_strcpy(section_name,s_PEDIAIMPROVE_00635074);
  ret_addr = 0x59a1a0;
  str_append_int((iptr)section_name,improvement_id);
  ret_addr = 0x59a1b1;
  status = text_open_section(ADDR(0x635084, ((u8 *)&g.d_00635084)),(iptr)section_name);
  if (status == 0) {
    text_clear();
    while (_Str = (char *)text_read_line(1), *_Str != '@') {
      if ((*_Str != ';') && (len = _strlen(_Str), len != 0)) {
        while ((*_Str == '^' || (*_Str == '*'))) {
          ret_addr = 0x59a253;
          crt_strcpy(line_buf,_Str + 1);
          ret_addr = 0x59a269;
          crt_strcpy(_Str,line_buf);
        }
        str_trim((iptr)_Str);
        len = _strlen(desc_buf);
        if (len != 0) {
          ret_addr = 0x59a2a8;
          crt_strcat(desc_buf,&pedia_improve_text_space_str);
        }
        ret_addr = 0x59a2be;
        crt_strcat(desc_buf,_Str);
      }
    }
  }
  ret_addr = 0x59a2d7;
  crt_strcpy(&text_buffer,desc_buf);
  return;
}
#undef text_buffer
#undef desc_buf
#undef line_buf
#undef section_name

/* 0059a2e6 auto */
#define map_redraw_busy (*(int *)((u8 *)&g.d_006ad908))
#define pedia_closed (*(int *)((u8 *)&g.d_006a677c))
#define pedia_improvement_names (*(i32 *)((u8 *)&g.d_006a7d48))
#define improve_idx (*(u32 *)(frame_ + FRAME_OFF(0)))
void __thiscall pedia_show_improvement_modal(DocumentWindow *this,iptr improvement_id)

{
  i32 name_text;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((pedia_closed != 0) && (map_redraw_busy == 0)) {
    if (improvement_id < 0x27) {
      improve_idx = 0;
      while (((int)improve_idx < (int)this->pedia_improve_count &&
             (*(int *)(this->improvement_sort_keys + improve_idx * 4 + 0x9c) != improvement_id))) {
        improve_idx++;
      }
      if (this->pedia_improve_count != improve_idx) {
        pedia_open_category((MediaWindow *)this,2,0);
        this->resize_border = improve_idx;
        *(u32 *)(((PictureWindow *)this)->list_selected_index) = improve_idx;
        this->client_x = 1;
        this->border_width = 1;
        pedia_clear_links((WindowObjectView *)this);
        pedia_update_controls((MediaWindow *)this);
        name_text = pedia_lookup_text(pedia_improvement_names,improve_idx);
        crt_strcpy(this->pedia_title_text_2,name_text);
        pedia_draw_frame((MediaWindow *)this);
        pedia_draw_improvement_page(this);
        window_show((WindowObjectView *)this);
        wnd_blit_surface((DibSurface *)&pedia_window);
        wnd_activate((Wnd *)&pedia_window_wnd);
        wnd_set_modal_idle_callback((ModalMenuWindow *)&pedia_window_wnd,ADDR(0x401843, pedia_modal_idle));
        wnd_run_modal_loop((ModalMenuWindow *)&pedia_window_wnd);
        wnd_set_modal_idle_callback((ModalMenuWindow *)&pedia_window_wnd,0);
      }
    }
    else {
      pedia_show_wonder_modal(this,improvement_id);
    }
  }
  return;
}
#undef map_redraw_busy
#undef pedia_closed
#undef pedia_improvement_names
#undef improve_idx

/* 005ac840 auto */
#define i (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall pedia_show_unit_list(MediaWindow *this,iptr unused_arg)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((int)this->resize_border < 0) || (*(int *)(((PictureWindow *)this)->pedia_unit_count) <= (int)this->resize_border)) {
    this->resize_border = 0;
  }
  *(i32 *)((PictureWindow *)this)->list_item_table = *(i32 *)(((PictureWindow *)this)->pedia_unit_count);
  *(u32 *)(((PictureWindow *)this)->list_selected_index) = this->resize_border;
  *(u32 *)(((PictureWindow *)this)->list_top_index) = this->resize_border;
  while (pedia_list_top % 9 != 0) {
    *(int *)(((PictureWindow *)this)->list_top_index) = *(int *)(((PictureWindow *)this)->list_top_index) - 1;
  }
  for (i = 0; i < *(int *)(((PictureWindow *)this)->pedia_unit_count); i++) {
    *(i32 *)(((PictureWindow *)this)->list_item_table + i * 4 + 4) =
         *(i32 *)(((PictureWindow *)this)->unit_id_slots + i * 4 + 0x18);
  }
  scrollbar_set_range
            ((Control *)&((PictureWindow *)this)->list_scrollbar,0,*(int *)((PictureWindow *)this)->list_item_table / 9);
  scrollbar_set_pos
            ((ClickControl *)&((PictureWindow *)this)->list_scrollbar,*(int *)(((PictureWindow *)this)->list_top_index) / 9);
  if (*(int *)((PictureWindow *)this)->list_item_table < 1) {
    ((PictureWindow *)this)->list_top_index[0] = 0xff;
    ((PictureWindow *)this)->list_top_index_byte1[0] = 0xff;
    ((PictureWindow *)this)->list_top_index_byte2[0] = 0xff;
    ((PictureWindow *)this)->list_top_index_byte3[0] = 0xff;
  }
  pedia_update_controls(this);
  wnd_set_focus((WndBase *)&pedia_window_wnd);
  wnd_activate((Wnd *)&pedia_window_wnd);
  pedia_redraw((PediaRedrawView *)&pedia_window);
  return;
}
#undef i

/* 005ac9ad auto */
#define list_text_color (*(i32 *)((u8 *)&g.d_00635a1c))
#define panel_margin_x (*(int *)((u8 *)&g.d_0062d858))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define shield_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define unit_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(16)))
#define desc_rect (*(tagRECT *)(frame_ + FRAME_OFF(32)))
#define has_text (*(int *)(frame_ + FRAME_OFF(48)))
#define line_height (*(int *)(frame_ + FRAME_OFF(52)))
#define link_rect (*(tagRECT *)(frame_ + FRAME_OFF(56)))
#define text_width (*(int *)(frame_ + FRAME_OFF(72)))
#define row_height (*(int *)(frame_ + FRAME_OFF(76)))
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(80)))
#define pedia_file (*(char * *)(frame_ + FRAME_OFF(84)))
#define half_width (*(int *)(frame_ + FRAME_OFF(88)))
#define unused_a (*(i32 *)(frame_ + FRAME_OFF(92)))
#define icon_width (*(int *)(frame_ + FRAME_OFF(96)))
#define desc_buf (*(char (*)[1000])(frame_ + FRAME_OFF(100)))
#define unused_d (*(i32 *)(frame_ + FRAME_OFF(1100)))
#define y2 (*(int *)(frame_ + FRAME_OFF(1104)))
#define x2 (*(u32 *)(frame_ + FRAME_OFF(1108)))
#define content_width2 (*(int *)(frame_ + FRAME_OFF(1112)))
#define value_x (*(int *)(frame_ + FRAME_OFF(1116)))
#define line (*(int *)(frame_ + FRAME_OFF(1120)))
#define unused_b (*(i32 *)(frame_ + FRAME_OFF(1124)))
#define margin (*(int *)(frame_ + FRAME_OFF(1128)))
#define text_color2 (*(i32 *)(frame_ + FRAME_OFF(1132)))
#define unused_c (*(i32 *)(frame_ + FRAME_OFF(1136)))
#define scale_den2 (*(i32 *)(frame_ + FRAME_OFF(1140)))
#define scale_num2 (*(i32 *)(frame_ + FRAME_OFF(1144)))
#define slot_height (*(int *)(frame_ + FRAME_OFF(1148)))
#define saved_clip (*(i8 (*)[16])(frame_ + FRAME_OFF(1152)))
#define font2 (*(GameFont * *)(frame_ + FRAME_OFF(1168)))
void __thiscall pedia_draw_unit_page(DocumentWindow *this)

{
  int measure;
  size_t text_len;
  int center_y;
  u32 yBottom;
  i8 frame_[FRAME_OFF(1176)] __attribute__((aligned(8)));  /* original stack frame */
  
  surface_get_clip((DibSurface *)this,(iptr)saved_clip);
  surface_set_clip((DibSurface *)this,(iptr)&this->content_left);
  pedia_update_controls((MediaWindow *)this);
  pedia_fill_background((WindowObjectView *)this,(iptr)&this->content_left,2);
  font2 = (GameFont *)&font_size21;
  x2 = this->content_left;
  margin = 10;
  content_width2 = rect_width((iptr)&this->content_left);
  half_width = content_width2 / 2;
  slot_height = rect_height((iptr)&this->content_left);
  slot_height = slot_height / 0xc;
  row_height = font_cached_height(font2);
  y2 = this->content_top + 0xf;
  unit_type = *(iptr *)(((PictureWindow *)this)->unit_ids_tail + this->resize_border * 4 - 4);
  x2 += margin;
  gfx_get_scale_ratio((iptr)&scale_num2,(iptr)&scale_den2);
  gfx_set_scale_ratio(2,1);
  icon_width = sprite_get_width((Sprite *)(&unit_sprites + unit_type * 0x3c))
  ;
  icon_width += panel_margin_x * 2;
  center_y = y2 + slot_height / 2;
  measure = sprite_get_height((Sprite *)(&unit_sprites + unit_type * 0x3c));
  sprite_draw
            ((Sprite *)(&unit_sprites + unit_type * 0x3c),(iptr)unit_ctx,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),x2,
             center_y - measure / 2);
  gfx_set_scale_ratio(scale_num2,scale_den2);
  text_color2 = list_text_color;
  gfx_set_text_color_index(list_text_color);
  measure = sprite_get_width((Sprite *)(&unit_sprites + unit_type * 0x3c));
  x2 = x2 + icon_width + measure + 0x32;
  y2 = sprite_get_height((Sprite *)(&unit_sprites + unit_type * 0x3c));
  y2 = this->content_top + y2;
  text_clear();
  text_append_label(0x79);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
  measure = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  x2 = x2 + measure + 5;
  text_clear();
  if (unit_types[unit_type].prerequisite < '\0') {
    text_append_label(0xe);
    surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
  }
  else {
    text_append_string_id(advances[unit_types[unit_type].prerequisite].name);
    text_width = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    line_height = font_line_spacing(font2);
    SetRect(&link_rect,x2,y2,text_width + x2 + 5,line_height + y2);
    pedia_add_link(this,(int)unit_types[unit_type].prerequisite,x2,y2,0,
                       link_rect.left,link_rect.top,link_rect.right,link_rect.bottom);
  }
  value_x = half_width - 0x4b;
  x2 = this->content_left + margin;
  measure = sprite_get_height((Sprite *)(&unit_sprites + unit_type * 0x3c));
  y2 = measure * 2 + this->content_top + row_height;
  text_clear();
  text_append_label(0x84);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
  text_clear();
  if ((char)unit_types[unit_type].cost < '\0') {
    text_append_label(0xe);
    surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),value_x,y2,5);
  }
  else {
    _sprintf(&text_buffer,&pedia_unit_cost_fmt,(char)unit_types[unit_type].cost * 10);
    surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),value_x,y2,5);
    measure = font_text_width(font2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    x2 = value_x + measure + 5;
    center_y = y2 + slot_height / 2;
    measure = sprite_get_height((Sprite *)&shield_icon_sprite);
    sprite_draw
              ((Sprite *)&shield_icon_sprite,(iptr)shield_ctx,ADDR(0x6a6668, ((u8 *)&g.d_006a6668)),x2,
               (center_y - 2) - measure / 2);
  }
  x2 = this->content_left + margin;
  y2 += row_height;
  text_clear();
  text_append_label(0x7f);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
  text_clear();
  _sprintf(&text_buffer,&pedia_unit_attack_fmt,(int)(char)unit_types[unit_type].attack);
  surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),value_x,y2,5);
  y2 += row_height;
  text_clear();
  text_append_label(0x80);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
  text_clear();
  _sprintf(&text_buffer,&pedia_unit_defense_fmt,(int)(char)unit_types[unit_type].defense);
  surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),value_x,y2,5);
  y2 += row_height;
  text_clear();
  text_append_label(0x82);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
  text_clear();
  _sprintf(&text_buffer,&pedia_unit_hp_fmt,(int)(char)unit_types[unit_type].hit_points / 10);
  surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),value_x,y2,5);
  y2 += row_height;
  text_clear();
  text_append_label(0x83);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
  text_clear();
  _sprintf(&text_buffer,&pedia_unit_firepower_fmt,(int)(char)unit_types[unit_type].firepower);
  surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),value_x,y2,5);
  y2 += row_height;
  text_clear();
  text_append_label(0x81);
  text_append_colon();
  surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),x2,y2,5);
  text_clear();
  _sprintf(&text_buffer,&pedia_unit_move_fmt,(int)(char)unit_types[unit_type].move / 3);
  surface_draw_text((DibSurface *)this,(iptr)font2,ADDR(0x679640, ((u8 *)&g.d_00679640)),value_x,y2,5);
  pedia_file = s_PEDIA_00635dac;
  text_clear();
  text_append_int(unit_type);
  unused_a = 0;
  unused_b = 0;
  unused_c = 7;
  unused_d = 0;
  measure = text_open_section((iptr)pedia_file,ADDR(0x635db4, ((u8 *)&g.d_00635db4)));
  if (measure == 0) {
    has_text = 0;
    str_clear((iptr)desc_buf);
    line = text_read_line(1);
    if ((unit_types[unit_type].flags & 1) != 0) {
      if (has_text == 0) {
        crt_strcpy(desc_buf,line + 1);
        has_text = 1;
      }
      else {
        crt_strcat(desc_buf,line + 1);
      }
      str_append_space((iptr)desc_buf);
    }
    line = text_read_line(1);
    if ((unit_types[unit_type].flags & 2) != 0) {
      if (has_text == 0) {
        crt_strcpy(desc_buf,line + 1);
        has_text = 1;
      }
      else {
        crt_strcat(desc_buf,line + 1);
      }
      str_append_space((iptr)desc_buf);
    }
    line = text_read_line(1);
    if ((unit_types[unit_type].flags & 4) != 0) {
      if (has_text == 0) {
        crt_strcpy(desc_buf,line + 1);
        has_text = 1;
      }
      else {
        crt_strcat(desc_buf,line + 1);
      }
      str_append_space((iptr)desc_buf);
    }
    line = text_read_line(1);
    if ((unit_types[unit_type].flags & 8) != 0) {
      if (has_text == 0) {
        crt_strcpy(desc_buf,line + 1);
        has_text = 1;
      }
      else {
        crt_strcat(desc_buf,line + 1);
      }
      str_append_space((iptr)desc_buf);
    }
    line = text_read_line(1);
    if ((unit_types[unit_type].flags & 0x10) != 0) {
      if (has_text == 0) {
        crt_strcpy(desc_buf,line + 1);
        has_text = 1;
      }
      else {
        crt_strcat(desc_buf,line + 1);
      }
      str_append_space((iptr)desc_buf);
    }
    line = text_read_line(1);
    if ((unit_types[unit_type].flags & 0x20) != 0) {
      if (has_text == 0) {
        crt_strcpy(desc_buf,line + 1);
        has_text = 1;
      }
      else {
        crt_strcat(desc_buf,line + 1);
      }
      str_append_space((iptr)desc_buf);
    }
    line = text_read_line(1);
    if ((unit_types[unit_type].flags & 0x40) != 0) {
      if (has_text == 0) {
        crt_strcpy(desc_buf,line + 1);
        has_text = 1;
      }
      else {
        crt_strcat(desc_buf,line + 1);
      }
      str_append_space((iptr)desc_buf);
    }
    line = text_read_line(1);
    if ((unit_types[unit_type].flags & 0x80) != 0) {
      if (has_text == 0) {
        crt_strcpy(desc_buf,line + 1);
        has_text = 1;
      }
      else {
        crt_strcat(desc_buf,line + 1);
      }
      str_append_space((iptr)desc_buf);
    }
    line = text_read_line(1);
    if ((unit_types[unit_type].flags & 0x100) != 0) {
      if (has_text == 0) {
        crt_strcpy(desc_buf,line + 1);
        has_text = 1;
      }
      else {
        crt_strcat(desc_buf,line + 1);
      }
      str_append_space((iptr)desc_buf);
    }
    line = text_read_line(1);
    if ((unit_types[unit_type].flags & 0x200) != 0) {
      if (has_text == 0) {
        crt_strcpy(desc_buf,line + 1);
        has_text = 1;
      }
      else {
        crt_strcat(desc_buf,line + 1);
      }
      str_append_space((iptr)desc_buf);
    }
    line = text_read_line(1);
    if ((unit_types[unit_type].flags & 0x400) != 0) {
      if (has_text == 0) {
        crt_strcpy(desc_buf,line + 1);
        has_text = 1;
      }
      else {
        crt_strcat(desc_buf,line + 1);
      }
      str_append_space((iptr)desc_buf);
    }
    line = text_read_line(1);
    if ((unit_types[unit_type].flags & 0x800) != 0) {
      if (has_text == 0) {
        crt_strcpy(desc_buf,line + 1);
        has_text = 1;
      }
      else {
        crt_strcat(desc_buf,line + 1);
      }
      str_append_space((iptr)desc_buf);
    }
    line = text_read_line(1);
    if ((unit_types[unit_type].flags & 0x1000) != 0) {
      if (has_text == 0) {
        crt_strcpy(desc_buf,line + 1);
        has_text = 1;
      }
      else {
        crt_strcat(desc_buf,line + 1);
      }
      str_append_space((iptr)desc_buf);
    }
    line = text_read_line(1);
    if ((unit_types[unit_type].flags & 0x2000) != 0) {
      if (has_text == 0) {
        crt_strcpy(desc_buf,line + 1);
        has_text = 1;
      }
      else {
        crt_strcat(desc_buf,line + 1);
      }
      str_append_space((iptr)desc_buf);
    }
    line = text_read_line(1);
    if ((unit_types[unit_type].flags & 0x4000) != 0) {
      if (has_text == 0) {
        crt_strcpy(desc_buf,line + 1);
        has_text = 1;
      }
      else {
        crt_strcat(desc_buf,line + 1);
      }
      str_append_space((iptr)desc_buf);
    }
    text_close_file();
    x2 = this->content_left + half_width;
    measure = sprite_get_height((Sprite *)(&unit_sprites + unit_type * 0x3c));
    y2 = measure * 2 + this->content_top + row_height;
    text_len = _strlen(desc_buf);
    if (text_len != 0) {
      yBottom = this->content_bottom;
      measure = rect_width((iptr)&this->content_left);
      SetRect(&desc_rect,x2,y2,x2 + measure / 2,yBottom);
      surface_draw_text_rect
                ((DibSurface *)this,(iptr)font2,(iptr)desc_buf,(iptr)&desc_rect,5);
    }
  }
  pedia_update_describe_button((ListPaneWindow *)this,this->resize_border);
  surface_set_clip((DibSurface *)this,(iptr)saved_clip);
  wnd_blit_surface_rect((DibSurface *)this,(iptr)&this->content_left);
  return;
}
#undef list_text_color
#undef panel_margin_x
#undef text_buffer
#undef shield_ctx
#undef unit_ctx
#undef desc_rect
#undef has_text
#undef line_height
#undef link_rect
#undef text_width
#undef row_height
#undef unit_type
#undef pedia_file
#undef half_width
#undef unused_a
#undef icon_width
#undef desc_buf
#undef unused_d
#undef y2
#undef x2
#undef content_width2
#undef value_x
#undef line
#undef unused_b
#undef margin
#undef text_color2
#undef unused_c
#undef scale_den2
#undef scale_num2
#undef slot_height
#undef saved_clip
#undef font2

/* 005ad998 auto */
#define map_redraw_busy (*(int *)((u8 *)&g.d_006ad908))
#define pedia_closed (*(int *)((u8 *)&g.d_006a677c))
#define pedia_unit_names (*(i32 *)((u8 *)&g.d_006a7d50))
#define unit_index (*(u32 *)(frame_ + FRAME_OFF(0)))
void __thiscall pedia_show_unit_modal(DocumentWindow *this,iptr unit_type)

{
  i32 name_text;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((pedia_closed != 0) && (map_redraw_busy == 0)) {
    unit_index = 0;
    while (((int)unit_index < *(int *)(((PictureWindow *)this)->pedia_unit_count) &&
           (*(int *)(((PictureWindow *)this)->unit_ids_tail + unit_index * 4 - 4) != unit_type))) {
      unit_index++;
    }
    if (*(u32 *)(((PictureWindow *)this)->pedia_unit_count) != unit_index) {
      pedia_open_category((MediaWindow *)this,4,0);
      this->resize_border = unit_index;
      *(u32 *)(((PictureWindow *)this)->list_selected_index) = unit_index;
      this->client_x = 1;
      this->border_width = 1;
      pedia_clear_links((WindowObjectView *)this);
      pedia_update_controls((MediaWindow *)this);
      name_text = pedia_lookup_text(pedia_unit_names,unit_index);
      crt_strcpy(this->pedia_title_text_2,name_text);
      pedia_draw_frame((MediaWindow *)this);
      pedia_draw_unit_page(this);
      window_show((WindowObjectView *)this);
      wnd_blit_surface((DibSurface *)&pedia_window);
      wnd_activate((Wnd *)&pedia_window_wnd);
      wnd_set_modal_idle_callback((ModalMenuWindow *)&pedia_window_wnd,ADDR(0x401843, pedia_modal_idle));
      wnd_run_modal_loop((ModalMenuWindow *)&pedia_window_wnd);
      wnd_set_modal_idle_callback((ModalMenuWindow *)&pedia_window_wnd,0);
    }
  }
  return;
}
#undef map_redraw_busy
#undef pedia_closed
#undef pedia_unit_names
#undef unit_index
