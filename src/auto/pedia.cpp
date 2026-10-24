/* The game, the Civilopedia: functions translated from the original
 * (tools/gen_c.py, now edited directly), in address order. */
#include "auto_common.h"

/* 00451af0 auto */
void __thiscall
pedia_draw_category_body(DocumentWindow *self,i32 category,i32 flags)

{
  int xLeft;
  int yTop;
  int col_width;
  int line_height;
  int title_height;
  tagRECT body_rect;
  int body_height;
  
  gfx_set_text_color_index(10);
  xLeft = self->content_left + panel_margin_x;
  yTop = self->content_top + panel_margin_y;
  col_width = rect_width((RECT *)&self->content_left);
  col_width = (col_width + panel_margin_x * -2) / 2 - panel_margin_x;
  line_height = font_cached_height((GameFont *)((i8 *)&font_size21));
  title_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
  body_height = line_height * 9 + title_height + panel_margin_y * 0xd;
  SetRect(&body_rect,xLeft,yTop,col_width + xLeft,body_height + yTop);
  gfx_set_draw_target((iptr)&pedia_window_block.pedia_window);
  pedia_dispatch_category_draw(self,body_rect.left,body_rect.top,body_rect.right,body_rect.bottom,category);
  wnd_blit_surface_rect((DibSurface *)self,(iptr)self->pedia_body_blit_rect);
  return;
}

/* 00451bf0 auto */
void __thiscall pedia_update_controls(MediaWindow *self)

{
  u32 view_mode;
  int scroll_height;
  Control *new_ctrl;
  u8 *hotspot_parent2;
  u8 *hotspot_parent;
  Control *hotspot2;
  Control *hotspot;
  struct { u32 left; u32 top; u32 right; u32 bottom; } rect2;
  i32 seh_frame;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0xffffffff;
  control_hide((Control *)(((PictureWindow *)self)->list_describe_button));
  control_hide((Control *)((u8 *)&((PictureWindow *)self)->list_close_button));
  control_hide((Control *)((u8 *)&((PictureWindow *)self)->detail_back_button));
  control_hide((Control *)(((PictureWindow *)self)->detail_describe_button));
  control_hide((Control *)&((PictureWindow *)self)->detail_close_button);
  control_hide((Control *)(((PictureWindow *)self)->text_back_button));
  control_hide((Control *)&((PictureWindow *)self)->text_close_button);
  control_hide((Control *)&((PictureWindow *)self)->list_scrollbar);
  control_hide((Control *)(u8 *)&((PictureWindow *)self)->concept_list_back_button);
  control_hide((Control *)(((PictureWindow *)self)->advance_list_describe_button));
  control_hide((Control *)(((PictureWindow *)self)->advance_list_tech_tree_button));
  control_hide((Control *)(((PictureWindow *)self)->advance_list_close_button));
  control_hide((Control *)&((PictureWindow *)self)->advance_detail_back_button);
  control_hide((Control *)((u8 *)&((PictureWindow *)self)->advance_detail_tech_tree_button));
  control_hide((Control *)(((PictureWindow *)self)->advance_detail_describe_button));
  control_hide((Control *)&((PictureWindow *)self)->advance_detail_close_button);
  control_hide((Control *)&((PictureWindow *)self)->description_edit);
  ctrl_set_text((ControlTextView *)&((PictureWindow *)self)->description_edit,(const char *)&str_empty_73);
  if (((PictureWindow *)self)->list_hotspot != 0) {
    if ((Hotspot *)((PictureWindow *)self)->list_hotspot != (Hotspot *)0x0) {
      hotspot_scalar_dtor((Hotspot *)((PictureWindow *)self)->list_hotspot,1);
    }
    ((PictureWindow *)self)->list_hotspot = 0;
  }
  view_mode = self->border_width;
  if (view_mode == 0) {
    ((PictureWindow *)self)->list_rect = self->content_left;
    ((PictureWindow *)self)->list_rect_top = self->content_top;
    ((PictureWindow *)self)->list_rect_right = self->content_right;
    ((PictureWindow *)self)->list_rect_bottom = self->content_bottom;
    scroll_height = GetSystemMetrics(3);
    ((PictureWindow *)self)->list_rect_bottom -= scroll_height;
    if (self->caption_height == 8) {
      ctrl_show_and_redraw((Control *)(u8 *)&((PictureWindow *)self)->concept_list_back_button);
      ctrl_show_and_redraw((Control *)((u8 *)&((PictureWindow *)self)->list_close_button));
    }
    else if (self->caption_height == 1) {
      ctrl_show_and_redraw((Control *)(((PictureWindow *)self)->advance_list_describe_button));
      ctrl_show_and_redraw((Control *)(((PictureWindow *)self)->advance_list_tech_tree_button));
      ctrl_show_and_redraw((Control *)(((PictureWindow *)self)->advance_list_close_button));
      ctrl_show_and_redraw((Control *)&((PictureWindow *)self)->list_scrollbar);
      if (((PictureWindow *)self)->list_hotspot == 0) {
        rect2.left = self->content_left;
        rect2.top = self->content_top;
        rect2.right = self->content_right;
        rect2.bottom = self->content_bottom;
        scroll_height = GetSystemMetrics(3);
        rect2.bottom -= scroll_height;
        new_ctrl = (Control *)operator_new(0x40);
        seh_state = 0;
        if (new_ctrl == (Control *)0x0) {
          hotspot = 0;
        }
        else {
          hotspot = hotspot_ctor(new_ctrl);
        }
        seh_state = 0xffffffff;
        ((PictureWindow *)self)->list_hotspot = (u32)hotspot;
        if (self == (MediaWindow *)0x0) {
          hotspot_parent = (u8 *)0x0;
        }
        else {
          hotspot_parent = self->window_2;
        }
        hotspot_create
                  ((ClickControl *)((PictureWindow *)self)->list_hotspot,(iptr)hotspot_parent,0xfa9,(iptr)&rect2);
        hotspot_set_click_callback((HotspotClickSetView *)((PictureWindow *)self)->list_hotspot,(iptr)pedia_list_on_click);
        hotspot_set_dblclick_callback((HotspotDblClickSetView *)((PictureWindow *)self)->list_hotspot,(iptr)pedia_toggle_describe);
        ctrl_show_and_redraw((Control *)((PictureWindow *)self)->list_hotspot);
      }
    }
    else {
      ctrl_show_and_redraw((Control *)(((PictureWindow *)self)->list_describe_button));
      ctrl_show_and_redraw((Control *)&((PictureWindow *)self)->list_scrollbar);
      ctrl_show_and_redraw((Control *)((u8 *)&((PictureWindow *)self)->list_close_button));
      if (((PictureWindow *)self)->list_hotspot == 0) {
        rect2.left = self->content_left;
        rect2.top = self->content_top;
        rect2.right = self->content_right;
        rect2.bottom = self->content_bottom;
        scroll_height = GetSystemMetrics(3);
        rect2.bottom -= scroll_height;
        new_ctrl = (Control *)operator_new(0x40);
        seh_state = 1;
        if (new_ctrl == (Control *)0x0) {
          hotspot2 = 0;
        }
        else {
          hotspot2 = hotspot_ctor(new_ctrl);
        }
        seh_state = 0xffffffff;
        ((PictureWindow *)self)->list_hotspot = (u32)hotspot2;
        if (self == (MediaWindow *)0x0) {
          hotspot_parent2 = (u8 *)0x0;
        }
        else {
          hotspot_parent2 = self->window_2;
        }
        hotspot_create
                  ((ClickControl *)((PictureWindow *)self)->list_hotspot,(iptr)hotspot_parent2,0xfa9,(iptr)&rect2);
        hotspot_set_click_callback((HotspotClickSetView *)((PictureWindow *)self)->list_hotspot,(iptr)pedia_list_on_click);
        hotspot_set_dblclick_callback((HotspotDblClickSetView *)((PictureWindow *)self)->list_hotspot,(iptr)pedia_toggle_describe);
        ctrl_show_and_redraw((Control *)((PictureWindow *)self)->list_hotspot);
      }
    }
  }
  else if (view_mode == 1) {
    if ((self->caption_height == 6) || (self->caption_height == 7)) {
      ctrl_show_and_redraw((Control *)(((PictureWindow *)self)->text_back_button));
      ctrl_show_and_redraw((Control *)&((PictureWindow *)self)->text_close_button);
    }
    else if (self->caption_height == 1) {
      ctrl_show_and_redraw((Control *)&((PictureWindow *)self)->advance_detail_back_button);
      ctrl_show_and_redraw((Control *)((u8 *)&((PictureWindow *)self)->advance_detail_tech_tree_button));
      ctrl_show_and_redraw((Control *)(((PictureWindow *)self)->advance_detail_describe_button));
      ctrl_show_and_redraw((Control *)&((PictureWindow *)self)->advance_detail_close_button);
    }
    else {
      ctrl_show_and_redraw((Control *)((u8 *)&((PictureWindow *)self)->detail_back_button));
      ctrl_show_and_redraw((Control *)(((PictureWindow *)self)->detail_describe_button));
      ctrl_show_and_redraw((Control *)&((PictureWindow *)self)->detail_close_button);
    }
  }
  else if (view_mode == 2) {
    ctrl_show_and_redraw((Control *)(((PictureWindow *)self)->text_back_button));
    ctrl_show_and_redraw((Control *)&((PictureWindow *)self)->text_close_button);
  }
  ui_pump_messages();
  return;
}

/* 00452188 auto */
void __thiscall
pedia_dispatch_category_draw
          (DocumentWindow *self,i32 left,i32 top,i32 right,
          i32 bottom,i32 category)

{
  i32 rect[4] = {left, top, right, bottom};  /* the rectangle passed as four arguments */
  switch(category) {
  case 0:
    break;
  case 1:
    if (self->border_width == 0) {
      pedia_init_advance_list((PediaAdvanceListView *)self,(iptr)rect);
    }
    else {
      pedia_draw_advance_page(self);
    }
    break;
  case 2:
    if (self->border_width == 0) {
      pedia_init_improvement_list(self,(iptr)rect);
    }
    else {
      pedia_draw_improvement_page(self);
    }
    break;
  case 3:
    if (self->border_width == 0) {
      pedia_init_wonder_list((MediaWindow *)self,(iptr)rect);
    }
    else {
      pedia_draw_improvement(self);
    }
    break;
  case 4:
    if (self->border_width == 0) {
      pedia_show_unit_list((MediaWindow *)self,(iptr)rect);
    }
    else {
      pedia_draw_unit_page(self);
    }
    break;
  case 5:
    if (self->border_width == 0) {
      pedia_init_terrain_list((MediaWindow *)self,(iptr)rect);
    }
    break;
  case 6:
    if (self->border_width == 0) {
      pedia_init_government_list((MediaWindow *)self,(iptr)rect);
    }
    break;
  case 7:
    if (self->border_width == 0) {
      pedia_init_concept_list((MediaWindow *)self,(iptr)rect);
    }
    break;
  case 8:
    pedia_draw_advance_tree(self);
  }
  return;
}

/* 00452315: written by hand in src/game/retvals.cpp */

/* 00452768 auto */
void __thiscall pedia_update_describe_button(ListPaneWindow *self,int list_index)

{
  int result;
  int topic_id;
  i8 path[260];
  
  if ((((game.game_flags & 0x80) != 0) && (self->caption_height != 7)) &&
     (result = _strcmp(((i8 *)&net_map_lock_slots_block.scenario_dir_path),((i8 *)&civ_saved_cursor_x_block.game_home_dir)), result != 0)) {
    __chdir(((i8 *)&net_map_lock_slots_block.scenario_dir_path));
    crt_strcpy(path,str_describe_2);
    crt_strcat(path,((i8 *)&lang_file_ext));
    result = file_exists((const char *)path);
    if (result == 0) {
      ctrl_disable((Control *)(((PictureWindow *)self)->detail_describe_button));
      __chdir(((i8 *)&civ_saved_cursor_x_block.game_home_dir));
      return;
    }
    __chdir(((i8 *)&civ_saved_cursor_x_block.game_home_dir));
  }
  switch(self->caption_height) {
  case 1:
    topic_id = ((PictureWindow *)self)->pedia_advance_keys[list_index];
    break;
  case 2:
    topic_id = ((PictureWindow *)self)->pedia_improve_keys[list_index];
    break;
  case 3:
    topic_id = ((PictureWindow *)self)->pedia_wonder_keys[list_index];
    break;
  case 4:
    topic_id = ((PictureWindow *)self)->pedia_unit_keys[list_index];
    break;
  case 5:
    topic_id = ((PictureWindow *)self)->pedia_terrain_keys[list_index];
    break;
  case 6:
    topic_id = ((PictureWindow *)self)->pedia_government_keys[list_index];
    break;
  case 7:
    topic_id = ((PictureWindow *)self)->pedia_concept_keys[list_index];
  }
  if (topic_id < 0) {
    if (self->caption_height == 1) {
      ctrl_disable((Control *)(((PictureWindow *)self)->advance_detail_describe_button));
    }
    else {
      ctrl_disable((Control *)(((PictureWindow *)self)->detail_describe_button));
    }
  }
  else if (self->caption_height == 1) {
    ctrl_enable((Control *)(((PictureWindow *)self)->advance_detail_describe_button));
  }
  else {
    ctrl_enable((Control *)(((PictureWindow *)self)->detail_describe_button));
  }
  return;
}

/* 004529df auto */
void __cdecl hyperlink_register_class(void)

{
  WNDCLASSA wnd_class;
  
  if (hyperlink_class_registered == 0) {
    hyperlink_class_registered = 1;
    wnd_class.style = 0x88;
    wnd_class.lpfnWndProc = ctrl_default_wndproc;
    wnd_class.cbClsExtra = 0;
    wnd_class.cbWndExtra = 0x10;
    wnd_class.hInstance = err_report_ctx_block.app_hinstance;
    wnd_class.hIcon = (HICON)0x0;
    wnd_class.hCursor = LoadCursorA(err_report_ctx_block.app_hinstance,(LPCSTR)0x212);
    wnd_class.hbrBackground = (HBRUSH)0x0;
    wnd_class.lpszMenuName = (LPCSTR)0x0;
    wnd_class.lpszClassName = str_mshypertextclass;
    RegisterClassA(&wnd_class);
  }
  return;
}

/* 00452a67 auto */
void __thiscall hyperlink_dtor(HyperlinkDtorView *self)

{
  i32 seh_frame;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0;
  if (self->hwnd != 0) {
    region_dispose(self->hwnd);
  }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 00452ac1 */ { ctrl_base_dtor(*(ControlBase **)&self); }
  return;
}

/* 00452ae2 auto */
HWND __cdecl hyperlink_create_hwnd(int *rect,iptr control)

{
  WndBase *self;
  NativeWindow *parent_wnd;
  iptr height;
  int width;
  HWND link_hwnd;
  HMENU hMenu;
  HINSTANCE hInstance;
  LPVOID lpParam;
  ControlBlock *block;
  
  hyperlink_register_class();
  lpParam = (LPVOID)0x0;
  hMenu = (HMENU)0x0;
  hInstance = err_report_ctx_block.app_hinstance;
  self = (WndBase *)ctrl_get_parent((Control *)control);
  parent_wnd = wnd_get_window(self);
  link_hwnd = parent_wnd->hwnd;
  height = rect_height((RECT *)rect);
  width = rect_width((RECT *)rect);
  link_hwnd = CreateWindowExA(4,str_mshypertextclass_2,((i8 *)&hyperlink_window_title_str),0x50000000,*rect,
                           rect[1],width,height,link_hwnd,hMenu,hInstance,lpParam);
  block = ctrl_init_block(link_hwnd,control);
  block->kind = 1;
  SetWindowLongA(link_hwnd,-4,(iptr)hotspot_wndproc);
  return link_hwnd;
}

/* 00452b89 auto */
void __thiscall
hyperlink_create(ClickControl *self,iptr parent,i32 control_id,iptr rect)

{
  u32 hwnd;
  
  if (self->hwnd != 0) {
    ctrl_destroy((Control *)self);
  }
  ctrl_init((Control *)self,parent,1,control_id,(RECT *)rect);
  self->is_enabled = 0;
  self->on_click = 0;
  self->on_select = 0;
  self->font = 0;
  self->scroll_pos = 0;
  hwnd = hyperlink_create_hwnd((int *)rect,(iptr)self);
  self->hwnd = hwnd;
  return;
}

/* 00452c14 auto */
void __thiscall
pedia_add_link
          (DocumentWindow *self,iptr item_id,int x,int y,i32 link_kind,
          i32 rect_left,i32 rect_top,i32 rect_right,i32 rect_bottom)

{
  i32 rect[4] = {rect_left, rect_top, rect_right, rect_bottom};  /* the rectangle passed as four arguments */
  int text_width;
  int max_width;
  uptr len;
  PediaLinkCtorView *new_link;
  int underline_y;
  u8 *parent_wnd2;
  PediaLink *link;
  u32 list_index;
  int link_index;
  PediaLink *last_link;
  i32 seh_frame;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0xffffffff;
  switch(link_kind) {
  case 0:
    list_index = 0;
    while (((int)list_index < (int)self->pedia_advance_count &&
           (((PictureWindow *)self)->pedia_advance_ids[list_index] != item_id))) {
      list_index++;
    }
    if (self->pedia_advance_count == list_index) goto done;
    break;
  case 1:
    list_index = 0;
    while (((int)list_index < (int)self->pedia_improve_count &&
           (((PictureWindow *)self)->pedia_improve_ids[list_index] != item_id))) {
      list_index++;
    }
    if (self->pedia_improve_count == list_index) goto done;
    break;
  case 2:
    for (list_index = 0;
        ((int)list_index < ((PictureWindow *)self)->pedia_wonder_count &&
        (((PictureWindow *)self)->pedia_wonder_ids[list_index] != item_id)); list_index++) {
    }
    if ((u32)((PictureWindow *)self)->pedia_wonder_count == list_index) goto done;
    break;
  case 3:
    list_index = 0;
    while (((int)list_index < ((PictureWindow *)self)->pedia_unit_count &&
           (((PictureWindow *)self)->pedia_unit_ids[list_index] != item_id))) {
      list_index++;
    }
    if ((u32)((PictureWindow *)self)->pedia_unit_count == list_index) goto done;
    break;
  case 4:
    list_index = 0;
    while (((int)list_index < (int)((PictureWindow *)self)->pedia_terrain_count_2 &&
           (((PictureWindow *)self)->pedia_terrain_ids[list_index] != item_id))) {
      list_index++;
    }
    if (((PictureWindow *)self)->pedia_terrain_count_2 == list_index) goto done;
    break;
  default:
    goto done;
  }
  while( true ) {
    text_width = font_text_width((GameFont *)((i8 *)&font_size21),(const char *)&map_views_block.text_buffer);
    max_width = rect_width((RECT *)rect);
    if (text_width <= max_width) break;
    len = _strlen(((i8 *)&map_views_block.text_buffer));
    (((i8 *)&map_views_block.text_buffer_minus1))[len] = 0;
  }
  if ((self->caption_height == 8) && (text_width = civ_has_advance(human_civ[0],item_id), text_width != 0)) {
    gfx_set_text_color_index(0x6a);
  }
  else {
    gfx_set_text_color_index(0x55);
  }
  text_width = font_cached_height((GameFont *)((i8 *)&font_size21));
  underline_y = y + text_width - 2;
  text_width = font_text_width((GameFont *)((i8 *)&font_size21),(const char *)&map_views_block.text_buffer);
  text_width = x + text_width;
  max_width = font_cached_height((GameFont *)((i8 *)&font_size21));
  surface_draw_line((DibSurface *)self,x,y + max_width - 2,text_width,underline_y);
  gfx_set_text_color_index(10);
  surface_draw_text((DibSurface *)self,(iptr)&font_size21,(const char *)&map_views_block.text_buffer,x + 1,y,5);
  if ((self->caption_height == 8) && (text_width = civ_has_advance(human_civ[0],item_id), text_width != 0)) {
    gfx_set_text_color_index(0x6a);
  }
  else {
    gfx_set_text_color_index(0x55);
  }
  surface_draw_text((DibSurface *)self,(iptr)&font_size21,(const char *)&map_views_block.text_buffer,x,y,5);
  gfx_set_text_color_index(10);
  new_link = (PediaLinkCtorView *)operator_new(0x48);
  seh_state = 0;
  if (new_link == (PediaLinkCtorView *)0x0) {
    link = (PediaLink *)0x0;
  }
  else {
    link = (PediaLink *)pedia_link_ctor(new_link);
  }
  seh_state = 0xffffffff;
  link->topic = list_index;
  link->next = 0;
  link_index = 0;
  if (((PictureWindow *)self)->link_list_head == (PediaLink *)0x0) {
    ((PictureWindow *)self)->link_list_head = link;
  }
  else {
    link_index = 1;
    for (last_link = ((PictureWindow *)self)->link_list_head; last_link->next != (PediaLink *)0x0;
        last_link = last_link->next) {
      link_index++;
    }
    last_link->next = link;
  }
  if (self == (DocumentWindow *)0x0) {
    parent_wnd2 = (u8 *)0x0;
  }
  else {
    parent_wnd2 = self->window_2;
  }
  hyperlink_create
            (&link->control,(iptr)parent_wnd2,link_index + 0xfb4,(iptr)rect);
  switch(link_kind) {
  case 0:
    hyperlink_set_click_callback((HyperlinkSetClickCallbackView *)&link->control,(iptr)pedia_link_on_click_advance);
    hyperlink_set_dblclick_callback((HyperlinkSetDblclickCallbackView *)&link->control,(iptr)pedia_link_on_click_advance);
    break;
  case 1:
    hyperlink_set_click_callback((HyperlinkSetClickCallbackView *)&link->control,(iptr)pedia_link_on_click_improvement);
    hyperlink_set_dblclick_callback((HyperlinkSetDblclickCallbackView *)&link->control,(iptr)pedia_link_on_click_improvement);
    break;
  case 2:
    hyperlink_set_click_callback((HyperlinkSetClickCallbackView *)&link->control,(iptr)pedia_link_on_click_wonder);
    hyperlink_set_dblclick_callback((HyperlinkSetDblclickCallbackView *)&link->control,(iptr)pedia_link_on_click_wonder);
    break;
  case 3:
    hyperlink_set_click_callback((HyperlinkSetClickCallbackView *)&link->control,(iptr)pedia_link_on_click_unit);
    hyperlink_set_dblclick_callback((HyperlinkSetDblclickCallbackView *)&link->control,(iptr)pedia_link_on_click_unit);
    break;
  case 4:
    hyperlink_set_click_callback((HyperlinkSetClickCallbackView *)&link->control,(iptr)pedia_link_on_click_terrain);
    hyperlink_set_dblclick_callback((HyperlinkSetDblclickCallbackView *)&link->control,(iptr)pedia_link_on_click_terrain);
  }
  ctrl_show_and_redraw((Control *)&link->control);
done:
  return;
}

/* 004531b8 auto */
void __cdecl pedia_link_on_click_advance(int control_id)

{
  PediaLink *link;
  int link_index;
  
  link_index = control_id - 0xfb4;
  for (link = pedia_window_block.pedia_link_list; (link_index != 0 && (link != (PediaLink *)0x0));
      link = link->next) {
    link_index--;
  }
  if (link != (PediaLink *)0x0) {
    pedia_window_block.pedia_category = 1;
    pedia_window_block.pedia_page_mode = 0;
    pedia_window_block.pedia_selected_item = link->topic;
    pedia_toggle_describe(1);
  }
  return;
}

/* 0045323a auto */
void __cdecl pedia_link_on_click_improvement(int control_id)

{
  PediaLink *link;
  int link_index;
  
  link_index = control_id - 0xfb4;
  for (link = pedia_window_block.pedia_link_list; (link_index != 0 && (link != (PediaLink *)0x0));
      link = link->next) {
    link_index--;
  }
  if (link != (PediaLink *)0x0) {
    pedia_window_block.pedia_category = 2;
    pedia_window_block.pedia_page_mode = 0;
    pedia_window_block.pedia_selected_item = link->topic;
    pedia_toggle_describe(1);
  }
  return;
}

/* 004532bc auto */
void __cdecl pedia_link_on_click_wonder(int control_id)

{
  PediaLink *link;
  int link_index;
  
  link_index = control_id - 0xfb4;
  for (link = pedia_window_block.pedia_link_list; (link_index != 0 && (link != (PediaLink *)0x0));
      link = link->next) {
    link_index--;
  }
  if (link != (PediaLink *)0x0) {
    pedia_window_block.pedia_category = 3;
    pedia_window_block.pedia_page_mode = 0;
    pedia_window_block.pedia_selected_item = link->topic;
    pedia_toggle_describe(1);
  }
  return;
}

/* 0045333e auto */
void __cdecl pedia_link_on_click_unit(int control_id)

{
  PediaLink *link;
  int link_index;
  
  link_index = control_id - 0xfb4;
  for (link = pedia_window_block.pedia_link_list; (link_index != 0 && (link != (PediaLink *)0x0));
      link = link->next) {
    link_index--;
  }
  if (link != (PediaLink *)0x0) {
    pedia_window_block.pedia_category = 4;
    pedia_window_block.pedia_page_mode = 0;
    pedia_window_block.pedia_selected_item = link->topic;
    pedia_toggle_describe(1);
  }
  return;
}

/* 004533c0 auto */
void __cdecl pedia_link_on_click_terrain(int control_id)

{
  PediaLink *link;
  int link_index;
  
  link_index = control_id - 0xfb4;
  for (link = pedia_window_block.pedia_link_list; (link_index != 0 && (link != (PediaLink *)0x0));
      link = link->next) {
    link_index--;
  }
  if (link != (PediaLink *)0x0) {
    pedia_window_block.pedia_category = 5;
    pedia_window_block.pedia_page_mode = 0;
    pedia_window_block.pedia_selected_item = link->topic;
    pedia_toggle_describe(1);
  }
  return;
}

/* 00453b10 auto */
PediaLinkCtorView * __thiscall pedia_link_ctor(PediaLinkCtorView *self)

{
  i32 seh_frame;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0xffffffff;
  hyperlink_ctor((Control *)self->link_control);
  return self;
}

/* 00453cc0 auto */
Control * __thiscall hyperlink_ctor(Control *self)

{
  i32 seh_frame;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0xffffffff;
  ctrl_base_ctor(self);
  return self;
}

/* 00453d40 auto */
void __thiscall hyperlink_set_click_callback(HyperlinkSetClickCallbackView *self,iptr callback)

{
  self->on_click = callback;
  return;
}

/* 00453d70 auto */
/* Library Function - Single Match
    public: void __thiscall CDialog::SetHelpID(unsigned int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall hyperlink_set_dblclick_callback(HyperlinkSetDblclickCallbackView *self,iptr callback)

{
  self->on_dblclick = callback;
  return;
}

/* 00490590 auto */
void __thiscall pedia_init_terrain_list(MediaWindow *self,iptr rect)

{
  int i;
  
  if (((int)self->resize_border < 0) || (((PictureWindow *)self)->pedia_terrain_count <= (int)self->resize_border)) {
    self->resize_border = 0;
  }
  ((PictureWindow *)self)->list_count = ((PictureWindow *)self)->pedia_terrain_count;
  ((PictureWindow *)self)->list_selected_index = self->resize_border;
  ((PictureWindow *)self)->list_top_index = self->resize_border;
  while (pedia_window_block.pedia_list_top % 9 != 0) {
    ((PictureWindow *)self)->list_top_index = ((PictureWindow *)self)->list_top_index - 1;
  }
  for (i = 0; i < ((PictureWindow *)self)->pedia_terrain_count; i++) {
    ((PictureWindow *)self)->list_items[i] =
         ((PictureWindow *)self)->pedia_terrain_ids[i];
  }
  scrollbar_set_range
            ((Control *)&((PictureWindow *)self)->list_scrollbar,0,((PictureWindow *)self)->list_count / 9);
  scrollbar_set_pos
            ((ClickControl *)&((PictureWindow *)self)->list_scrollbar,((PictureWindow *)self)->list_top_index / 9);
  if (((PictureWindow *)self)->list_count < 1) {
    ((PictureWindow *)self)->list_top_index = -1;
  }
  pedia_update_controls(self);
  wnd_set_focus((WndBase *)((i8 *)&pedia_window_block.pedia_window_wnd));
  wnd_activate((Wnd *)((i8 *)&pedia_window_block.pedia_window_wnd));
  pedia_redraw((PediaRedrawView *)((i8 *)&pedia_window_block.pedia_window));
  return;
}

/* 004906fd auto */
void __thiscall pedia_draw_terrain_page(DocumentWindow *self)

{
  u8 shields;
  int measured;
  iptr terrain_index;
  char *label;
  char *_Format;
  int icon_center_y;
  i8 *name_arg;
  i8 trade_sprite_ctx2[16];
  i8 shield_sprite_ctx2[16];
  i8 food_sprite_ctx2[16];
  i8 trade_sprite_ctx[16];
  i8 shield_sprite_ctx[16];
  i8 food_sprite_ctx[16];
  i8 resource_sprite_ctx[16];
  i8 hill_sprite_ctx2[16];
  i8 forest_sprite_ctx2[16];
  i8 grass_shield_ctx[16];
  i8 mountain_sprite_ctx[16];
  i8 hill_sprite_ctx[16];
  i8 forest_sprite_ctx[16];
  i8 base_sprite_ctx[16];
  char format_buf[256];
  int base_trade2;
  i8 base_name[40];
  int base_shields;
  int special_trade;
  int base_food;
  int special_shields;
  int special_food;
  int line_height;
  iptr terrain2;
  int half_width;
  int link_height;
  iptr terrain3;
  int sprite_area_width;
  iptr improve_kind;
  int sprite_height2;
  int stats_top;
  int y2;
  u32 x2;
  int page_width;
  int value_x;
  uint resource_variant;
  int sprite_width2;
  int margin;
  int right_col_x;
  i32 text_color2;
  int link_width;
  tagRECT link_rect;
  i32 scale_den2;
  int scale_num2;
  int row_height;
  i8 saved_clip[16];
  GameFont *font2;
  
  surface_get_clip((DibSurface *)self,(RECT *)saved_clip);
  surface_set_clip((DibSurface *)self,(RECT *)&self->content_left);
  pedia_update_controls((MediaWindow *)self);
  pedia_fill_background((WindowObjectView *)self,(RECT *)&self->content_left,2);
  font2 = (GameFont *)((i8 *)&font_size21);
  x2 = self->content_left;
  margin = 10;
  page_width = rect_width((RECT *)&self->content_left);
  half_width = page_width / 2;
  row_height = rect_height((RECT *)&self->content_left);
  row_height = row_height / 0xc;
  line_height = font_cached_height(font2);
  y2 = self->content_top + 8;
  terrain2 = ((PictureWindow *)self)->pedia_terrain_ids[self->resize_border];
  gfx_get_scale_ratio((iptr)&scale_num2,(iptr)&scale_den2);
  gfx_set_scale_ratio(scale_num2 * 2,scale_den2);
  sprite_height2 = sprite_get_height((Sprite *)((i8 *)&terrain_base_sprites_block.terrain_base_sprites));
  sprite_width2 = sprite_get_width((Sprite *)((i8 *)&terrain_base_sprites_block.terrain_base_sprites));
  x2 += margin;
  y2 += (row_height / 2 - sprite_height2 / 2);
  terrain3 = terrain2 % 0xb;
  sprite_area_width = sprite_width2 * 2 + panel_margin_x * 2;
  sprite_draw
            ((Sprite *)(((i8 *)&terrain_base_sprites_block.terrain_base_sprites) + terrain3 * 0x3c),(iptr)base_sprite_ctx,(iptr)&pedia_window_block.pedia_window,x2,
             y2);
  if (terrain2 < 0xb) {
    if (terrain2 == 3) {
      sprite_draw
                ((Sprite *)((i8 *)&forest_sprites),(iptr)forest_sprite_ctx,(iptr)&pedia_window_block.pedia_window,x2,y2);
    }
    else if (terrain2 == 4) {
      sprite_draw
                ((Sprite *)((i8 *)&hill_sprites_block.hill_sprites),(iptr)hill_sprite_ctx,(iptr)&pedia_window_block.pedia_window,x2,y2);
    }
    else if (terrain2 == 5) {
      sprite_draw
                ((Sprite *)((i8 *)&mountain_sprites),(iptr)mountain_sprite_ctx,(iptr)&pedia_window_block.pedia_window,x2,y2);
    }
  }
  else {
    resource_variant = (uint)(0x15 < terrain2);
    switch(terrain2) {
    case 0xd:
    case 0x18:
      sprite_draw
                ((Sprite *)((i8 *)&grassland_shield_sprite),(iptr)grass_shield_ctx,(iptr)&pedia_window_block.pedia_window,x2,y2);
      goto restore_scale_draw_text;
    case 0xe:
    case 0x19:
      sprite_draw
                ((Sprite *)((i8 *)&forest_sprites),(iptr)forest_sprite_ctx2,(iptr)&pedia_window_block.pedia_window,x2,y2);
      break;
    case 0xf:
    case 0x1a:
      sprite_draw
                ((Sprite *)((i8 *)&hill_sprites_block.hill_sprites),(iptr)hill_sprite_ctx2,(iptr)&pedia_window_block.pedia_window,x2,y2);
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
              ((Sprite *)(((i8 *)&city_down_arrow_sprite_block.terrain_resource_sprites) + terrain3 * 0x78 + resource_variant * 0x3c),(iptr)resource_sprite_ctx,
               (iptr)&pedia_window_block.pedia_window,x2,y2);
  }
restore_scale_draw_text:
  gfx_set_scale_ratio(scale_num2,scale_den2);
  text_color2 = list_text_color;
  gfx_set_text_color_index(list_text_color);
  x2 = self->content_left + margin;
  right_col_x = rect_width((RECT *)&self->content_left);
  right_col_x = right_col_x / 2;
  value_x = right_col_x - 100;
  if ((terrain2 < 0) || (10 < terrain2)) {
    x2 = x2 + sprite_area_width + 0x1e;
    y2 += line_height;
    text_clear();
    text_append_label(0x295);
    text_append_colon();
    surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
    measured = font_text_width(font2,(const char *)&map_views_block.text_buffer);
    x2 = x2 + measured + 10;
    text_clear();
    terrain_index = pedia_find_terrain_index(terrain3);
    label = pedia_lookup_text(pedia_window_block.pedia_terrain_names,terrain_index);
    crt_strcpy(((i8 *)&map_views_block.text_buffer),label);
    link_width = font_text_width(font2,(const char *)&map_views_block.text_buffer);
    link_height = font_line_spacing(font2);
    SetRect(&link_rect,x2,y2,x2 + link_width + 5,y2 + link_height);
    pedia_add_link(self,terrain3,x2,y2,4,link_rect.left,link_rect.top,link_rect.right,
                       link_rect.bottom);
    y2 += ((sprite_height2 * 2 + 10) - line_height);
  }
  else {
    stats_top = y2 + sprite_height2 * 2 + 10;
    y2 = stats_top;
    text_clear();
    text_append_label(0x293);
    text_append_colon();
    surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
    text_clear();
    _sprintf(((i8 *)&map_views_block.text_buffer),((i8 *)&pedia_terrain_move_cost_fmt),(int)(char)terrain_types[terrain2].move_cost);
    surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,value_x,y2,5);
    x2 = self->content_left + margin;
    y2 += line_height;
    text_clear();
    text_append_label(0x294);
    text_append_colon();
    surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
    text_clear();
    if (terrain_types[terrain2].defense == 6) {
      crt_strcpy(((i8 *)&map_views_block.text_buffer),str_200);
    }
    else if (terrain_types[terrain2].defense == 3) {
      crt_strcpy(((i8 *)&map_views_block.text_buffer),((i8 *)&pedia_terrain_defense_50_str));
    }
    else if (terrain_types[terrain2].defense == 4) {
      crt_strcpy(((i8 *)&map_views_block.text_buffer),str_100);
    }
    else if (terrain_types[terrain2].defense == 5) {
      crt_strcpy(((i8 *)&map_views_block.text_buffer),str_150);
    }
    else {
      terrain_index = (iptr)label_string(label_string_ids[0x2c2]);
      text_append((const char *)terrain_index);
    }
    surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,value_x,y2,5);
  }
  x2 = self->content_left + margin;
  y2 += line_height;
  text_clear();
  text_append_label(0x40);
  text_append_colon();
  surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
  text_clear();
  _sprintf(((i8 *)&map_views_block.text_buffer),((i8 *)&pedia_terrain_food_fmt),(int)(char)terrain_types[terrain2].food);
  surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,value_x,y2,5);
  measured = font_text_width(font2,(const char *)&map_views_block.text_buffer);
  x2 = value_x + measured + 3;
  icon_center_y = y2 + row_height / 2;
  measured = sprite_get_height((Sprite *)((i8 *)&war_icon_sprite_block.resource_icon_sprites));
  sprite_draw
            ((Sprite *)((i8 *)&war_icon_sprite_block.resource_icon_sprites),(iptr)food_sprite_ctx,(iptr)&pedia_window_block.pedia_window,x2,
             (icon_center_y - 2) - measured / 2);
  x2 = self->content_left + margin;
  y2 += line_height;
  text_clear();
  text_append_label(0x296);
  text_append_colon();
  surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
  text_clear();
  if (terrain2 == 2) {
    shields = '\0';
  }
  else {
    shields = terrain_types[terrain2].shields;
  }
  _sprintf(((i8 *)&map_views_block.text_buffer),((i8 *)&pedia_terrain_shields_fmt),(int)(char)shields);
  surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,value_x,y2,5);
  measured = font_text_width(font2,(const char *)&map_views_block.text_buffer);
  x2 = value_x + measured + 3;
  icon_center_y = y2 + row_height / 2;
  measured = sprite_get_height((Sprite *)((i8 *)&war_icon_sprite_block.shield_icon_sprite));
  sprite_draw
            ((Sprite *)((i8 *)&war_icon_sprite_block.shield_icon_sprite),(iptr)shield_sprite_ctx,(iptr)&pedia_window_block.pedia_window,x2,
             (icon_center_y - 2) - measured / 2);
  x2 = self->content_left + margin;
  y2 += line_height;
  text_clear();
  text_append_label(0x45);
  text_append_colon();
  surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
  text_clear();
  _sprintf(((i8 *)&map_views_block.text_buffer),((i8 *)&pedia_terrain_trade_fmt),(int)(char)terrain_types[terrain2].trade);
  surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,value_x,y2,5);
  measured = font_text_width(font2,(const char *)&map_views_block.text_buffer);
  x2 = value_x + measured + 3;
  icon_center_y = y2 + row_height / 2;
  measured = sprite_get_height((Sprite *)((i8 *)&war_icon_sprite_block.trade_icon_sprite));
  sprite_draw
            ((Sprite *)((i8 *)&war_icon_sprite_block.trade_icon_sprite),(iptr)trade_sprite_ctx,(iptr)&pedia_window_block.pedia_window,x2,
             (icon_center_y - 2) - measured / 2);
  if ((terrain2 < 0) || (10 < terrain2)) {
    x2 = self->content_left + margin;
    y2 += line_height * 2;
    terrain_index = pedia_find_terrain_index(terrain3);
    label = pedia_lookup_text(pedia_window_block.pedia_terrain_names,terrain_index);
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
      _Format = label_string(label_string_ids[0x2c4]);
      _sprintf(((i8 *)&map_views_block.text_buffer),_Format,name_arg,measured,icon_center_y);
    }
    else {
      label = label_string(label_string_ids[0x2c5]);
      crt_strcpy(((i8 *)&map_views_block.text_buffer),label);
    }
    surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
    y2 += line_height;
    text_clear();
    str_clear((char *)format_buf);
    if (base_shields < special_shields) {
      label = label_string(label_string_ids[0x2c6]);
      crt_strcpy(format_buf,label);
      _sprintf(((i8 *)&map_views_block.text_buffer),format_buf,base_shields,special_shields);
      surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
      y2 += line_height;
      text_clear();
      str_clear((char *)format_buf);
      if (base_trade2 < special_trade) {
        label = label_string(label_string_ids[0x2c7]);
        crt_strcat(format_buf,label);
        _sprintf(((i8 *)&map_views_block.text_buffer),format_buf,base_trade2,special_trade);
      }
      else {
        label = label_string(label_string_ids[0x2c8]);
        crt_strcat(((i8 *)&map_views_block.text_buffer),label);
      }
    }
    else {
      label = label_string(label_string_ids[0x2c9]);
      crt_strcpy(((i8 *)&map_views_block.text_buffer),label);
      surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
      y2 += line_height;
      text_clear();
      str_clear((char *)format_buf);
      if (base_trade2 < special_trade) {
        label = label_string(label_string_ids[0x2c7]);
        crt_strcat(format_buf,label);
        _sprintf(((i8 *)&map_views_block.text_buffer),format_buf,base_trade2,special_trade);
      }
      else {
        label = label_string(label_string_ids[0x2ca]);
        crt_strcat(((i8 *)&map_views_block.text_buffer),label);
      }
    }
    surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
  }
  else {
    for (improve_kind = 0; improve_kind < 2; improve_kind++) {
      x2 = self->content_left + margin;
      y2 += line_height;
      text_clear();
      if (improve_kind == 0) {
        text_append_label(0x297);
      }
      else {
        text_append_label(0x299);
      }
      text_append_colon();
      surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
      text_clear();
      if (terrain_types[terrain2].improve_to[improve_kind] < '\0') {
        if ((char)terrain_types[terrain2].improve_bonus[improve_kind] < 1) {
          text_append_label(0x29b);
          surface_draw_text
                    ((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,value_x,y2,5);
        }
        else {
          _sprintf(((i8 *)&map_views_block.text_buffer),((i8 *)&pedia_terrain_improve_bonus_fmt),(int)(char)terrain_types[terrain2].improve_bonus[improve_kind]
                  );
          surface_draw_text
                    ((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,value_x,y2,5);
          measured = font_text_width(font2,(const char *)&map_views_block.text_buffer);
          x2 = value_x + measured + 3;
          if (improve_kind == 0) {
            icon_center_y = y2 + row_height / 2;
            measured = sprite_get_height((Sprite *)((i8 *)&war_icon_sprite_block.resource_icon_sprites));
            sprite_draw
                      ((Sprite *)((i8 *)&war_icon_sprite_block.resource_icon_sprites),(iptr)food_sprite_ctx2,(iptr)&pedia_window_block.pedia_window,x2,
                       (icon_center_y - 2) - measured / 2);
          }
          else {
            icon_center_y = y2 + row_height / 2;
            measured = sprite_get_height((Sprite *)((i8 *)&war_icon_sprite_block.shield_icon_sprite));
            sprite_draw
                      ((Sprite *)((i8 *)&war_icon_sprite_block.shield_icon_sprite),(iptr)shield_sprite_ctx2,(iptr)&pedia_window_block.pedia_window,x2,
                       (icon_center_y - 2) - measured / 2);
          }
        }
      }
      else {
        terrain_index = pedia_find_terrain_index((int)terrain_types[terrain2].improve_to[improve_kind]);
        label = pedia_lookup_text(pedia_window_block.pedia_terrain_names,terrain_index);
        crt_strcpy(((i8 *)&map_views_block.text_buffer),label);
        link_width = font_text_width(font2,(const char *)&map_views_block.text_buffer);
        link_height = font_line_spacing(font2);
        SetRect(&link_rect,value_x,y2,link_width + value_x + 5,y2 + link_height);
        pedia_add_link(self,(int)terrain_types[terrain2].improve_to[improve_kind],value_x,
                           y2,4,link_rect.left,link_rect.top,link_rect.right,link_rect.bottom);
      }
      x2 = self->content_left + margin;
      y2 += line_height;
      text_clear();
      if (improve_kind == 0) {
        text_append_label(0x298);
      }
      else {
        text_append_label(0x29a);
      }
      text_append_colon();
      surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
      text_clear();
      if ((char)terrain_types[terrain2].improve_turns[improve_kind] < 1) {
        text_append_label(0x29b);
      }
      else {
        _sprintf(((i8 *)&map_views_block.text_buffer),((i8 *)&pedia_terrain_improve_turns_fmt),(int)(char)terrain_types[terrain2].improve_turns[improve_kind]);
      }
      surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,value_x,y2,5);
    }
    x2 = right_col_x;
    text_clear();
    y2 = stats_top;
    text_append_label(0x29c);
    text_append_colon();
    surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
    x2 += 0x14;
    y2 += line_height;
    text_clear();
    if (terrain_types[terrain2].transform_to < '\0') {
      text_append_label(0x29b);
      surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
    }
    else {
      terrain_index = pedia_find_terrain_index((int)terrain_types[terrain2].transform_to);
      label = pedia_lookup_text(pedia_window_block.pedia_terrain_names,terrain_index);
      crt_strcpy(((i8 *)&map_views_block.text_buffer),label);
      link_width = font_text_width(font2,(const char *)&map_views_block.text_buffer);
      link_height = font_line_spacing(font2);
      SetRect(&link_rect,x2,y2,x2 + link_width + 5,y2 + link_height);
      pedia_add_link(self,(int)terrain_types[terrain2].transform_to,x2,y2,4,
                         link_rect.left,link_rect.top,link_rect.right,link_rect.bottom);
    }
    if (terrain2 != 10) {
      x2 = right_col_x;
      y2 += line_height;
      text_clear();
      text_append_label(0x29d);
      text_append_colon();
      surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
      text_clear();
      x2 += 0x14;
      y2 += line_height;
      text_append_label(0x293);
      text_append_colon();
      text_append_space();
      terrain_index = (iptr)label_string(label_string_ids[0x2c3]);
      text_append((const char *)terrain_index);
      surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
      if (((terrain2 == 0) || (terrain2 == 2)) || (terrain2 == 1)) {
        y2 += line_height;
        text_clear();
        text_append_label(0x45);
        text_append_colon();
        text_append((const char *)&str_1_4);
        surface_draw_text
                  ((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
        measured = font_text_width(font2,(const char *)&map_views_block.text_buffer);
        x2 = x2 + measured + 3;
        icon_center_y = y2 + row_height / 2;
        measured = sprite_get_height((Sprite *)((i8 *)&war_icon_sprite_block.trade_icon_sprite));
        sprite_draw
                  ((Sprite *)((i8 *)&war_icon_sprite_block.trade_icon_sprite),(iptr)trade_sprite_ctx2,(iptr)&pedia_window_block.pedia_window,x2,
                   (icon_center_y - 2) - measured / 2);
      }
    }
    x2 = right_col_x;
    y2 += line_height;
    text_clear();
    text_append_label(0x29e);
    text_append_colon();
    surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
    x2 += 0x14;
    y2 += line_height;
    text_clear();
    terrain_index = pedia_find_terrain_index(terrain2 + 0xb);
    label = pedia_lookup_text(pedia_window_block.pedia_terrain_names,terrain_index);
    crt_strcpy(((i8 *)&map_views_block.text_buffer),label);
    link_width = font_text_width(font2,(const char *)&map_views_block.text_buffer);
    link_height = font_line_spacing(font2);
    SetRect(&link_rect,x2,y2,x2 + link_width + 5,y2 + link_height);
    pedia_add_link(self,terrain2 + 0xb,x2,y2,4,link_rect.left,link_rect.top,
                       link_rect.right,link_rect.bottom);
    if (terrain2 != 2) {
      text_clear();
      y2 += line_height;
      terrain_index = pedia_find_terrain_index(terrain2 + 0x16);
      label = pedia_lookup_text(pedia_window_block.pedia_terrain_names,terrain_index);
      crt_strcpy(((i8 *)&map_views_block.text_buffer),label);
      link_width = font_text_width(font2,(const char *)&map_views_block.text_buffer);
      link_height = font_line_spacing(font2);
      SetRect(&link_rect,x2,y2,x2 + link_width + 5,y2 + link_height);
      pedia_add_link(self,terrain2 + 0x16,x2,y2,4,link_rect.left,link_rect.top,
                         link_rect.right,link_rect.bottom);
    }
  }
  pedia_update_describe_button((ListPaneWindow *)self,self->resize_border);
  surface_set_clip((DibSurface *)self,(RECT *)saved_clip);
  wnd_blit_surface_rect((DibSurface *)self,(iptr)&self->content_left);
  return;
}

/* 00491c20 auto */
void __thiscall pedia_show_terrain_modal(DocumentWindow *self,int terrain_id)

{
  char *name_text;
  uptr terrain_idx;
  
  if (pedia_window_block.pedia_closed != 0) {
    terrain_idx = 0;
    while (((int)terrain_idx < (int)((PictureWindow *)self)->pedia_terrain_count_2 &&
           (((PictureWindow *)self)->pedia_terrain_ids[terrain_idx] != terrain_id))) {
      terrain_idx++;
    }
    if (((PictureWindow *)self)->pedia_terrain_count_2 != terrain_idx) {
      pedia_open_category((MediaWindow *)self,5,1);
      self->resize_border = terrain_idx;
      ((PictureWindow *)self)->list_selected_index = terrain_idx;
      self->client_x = 1;
      self->border_width = 1;
      pedia_clear_links((WindowObjectView *)self);
      pedia_update_controls((MediaWindow *)self);
      name_text = pedia_lookup_text(pedia_window_block.pedia_terrain_names,terrain_idx);
      crt_strcpy((char *)self->pedia_title_text_2,name_text);
      pedia_draw_frame((MediaWindow *)self);
      pedia_draw_terrain_page(self);
      wnd_blit_surface((DibSurface *)((i8 *)&pedia_window_block.pedia_window));
      wnd_activate((Wnd *)((i8 *)&pedia_window_block.pedia_window_wnd));
      wnd_set_modal_idle_callback((ModalMenuWindow *)((i8 *)&pedia_window_block.pedia_window_wnd),(iptr)pedia_modal_idle);
      wnd_run_modal_loop((ModalMenuWindow *)((i8 *)&pedia_window_block.pedia_window_wnd));
      wnd_set_modal_idle_callback((ModalMenuWindow *)((i8 *)&pedia_window_block.pedia_window_wnd),0);
    }
  }
  return;
}

/* 00491d61 auto */
i32 __cdecl pedia_find_terrain_index(iptr terrain_id)

{
  int index;
  
  index = 0;
  while( true ) {
    if (pedia_window_block.pedia_terrain_count <= index) {
      return 0xffffffff;
    }
    if (pedia_window_block.pedia_terrain_ids[index] == terrain_id) break;
    index++;
  }
  return index;
}

/* 004a69b0 auto */
void __thiscall pedia_init_concept_list(MediaWindow *self,iptr unused_arg)

{
  int i;
  
  if (((int)self->resize_border < 0) || ((int)((uptr)((PictureWindow *)self)->pedia_concept_count) <= (int)self->resize_border)) {
    self->resize_border = 0;
  }
  ((PictureWindow *)self)->list_count = ((uptr)((PictureWindow *)self)->pedia_concept_count);
  ((PictureWindow *)self)->list_selected_index = self->resize_border;
  ((PictureWindow *)self)->list_top_index = self->resize_border;
  while (pedia_window_block.pedia_list_top % 9 != 0) {
    ((PictureWindow *)self)->list_top_index = ((PictureWindow *)self)->list_top_index - 1;
  }
  for (i = 0; i < (int)((uptr)((PictureWindow *)self)->pedia_concept_count); i++) {
    ((PictureWindow *)self)->list_items[i] =
         ((PictureWindow *)self)->pedia_concept_ids[i];
  }
  scrollbar_set_range
            ((Control *)&((PictureWindow *)self)->list_scrollbar,0,((PictureWindow *)self)->list_count / 9);
  scrollbar_set_pos
            ((ClickControl *)&((PictureWindow *)self)->list_scrollbar,((PictureWindow *)self)->list_top_index / 9);
  if (((PictureWindow *)self)->list_count < 1) {
    ((PictureWindow *)self)->list_top_index = -1;
  }
  pedia_update_controls(self);
  wnd_set_focus((WndBase *)((i8 *)&pedia_window_block.pedia_window_wnd));
  wnd_activate((Wnd *)((i8 *)&pedia_window_block.pedia_window_wnd));
  pedia_redraw((PediaRedrawView *)((i8 *)&pedia_window_block.pedia_window));
  return;
}

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
  pedia_window_ctor((ScaledWindowView *)((i8 *)&pedia_window_block.pedia_window));
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
  pedia_window_dtor((DibSurface *)((i8 *)&pedia_window_block.pedia_window));
  return;
}

/* 004f3feb auto */
ScaledWindowView * __thiscall pedia_window_ctor(ScaledWindowView *self)

{
  u8 *slot;
  int i;
  i32 exc_link;
  i8 *seh_handler;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  surfwnd_ctor((SurfaceWindow *)self);
  eh_state = 0;
  button_ctor((Control *)(((PictureWindow *)self)->list_describe_button));
  (*((char *)&eh_state + 0)) = 1;
  button_ctor((Control *)((u8 *)&((PictureWindow *)self)->list_close_button));
  (*((char *)&eh_state + 0)) = 2;
  button_ctor((Control *)&((PictureWindow *)self)->detail_back_button);
  (*((char *)&eh_state + 0)) = 3;
  button_ctor((Control *)(((PictureWindow *)self)->detail_describe_button));
  (*((char *)&eh_state + 0)) = 4;
  button_ctor((Control *)((u8 *)&((PictureWindow *)self)->detail_close_button));
  (*((char *)&eh_state + 0)) = 5;
  button_ctor((Control *)(((PictureWindow *)self)->text_back_button));
  (*((char *)&eh_state + 0)) = 6;
  button_ctor((Control *)((u8 *)&((PictureWindow *)self)->text_close_button));
  (*((char *)&eh_state + 0)) = 7;
  button_ctor((Control *)&((PictureWindow *)self)->concept_list_back_button);
  (*((char *)&eh_state + 0)) = 8;
  button_ctor((Control *)(((PictureWindow *)self)->advance_list_describe_button));
  (*((char *)&eh_state + 0)) = 9;
  button_ctor((Control *)(((PictureWindow *)self)->advance_list_tech_tree_button));
  (*((char *)&eh_state + 0)) = 10;
  button_ctor((Control *)(((PictureWindow *)self)->advance_list_close_button));
  (*((char *)&eh_state + 0)) = 0xb;
  button_ctor((Control *)((u8 *)&((PictureWindow *)self)->advance_detail_back_button));
  (*((char *)&eh_state + 0)) = 0xc;
  button_ctor((Control *)&((PictureWindow *)self)->advance_detail_tech_tree_button);
  (*((char *)&eh_state + 0)) = 0xd;
  button_ctor((Control *)(((PictureWindow *)self)->advance_detail_describe_button));
  (*((char *)&eh_state + 0)) = 0xe;
  button_ctor((Control *)((u8 *)&((PictureWindow *)self)->advance_detail_close_button));
  (*((char *)&eh_state + 0)) = 0xf;
  edit_ctor((InputControl *)((u8 *)&((PictureWindow *)self)->description_edit));
  eh_state = (eh_state & 0xffffff00 | (byte)(0x10));
  scrollbar_ctor((Control *)&((PictureWindow *)self)->list_scrollbar);
  self->vtable = (u32)((pointer *)&leader_anim_frame_starts_block.ptr_fun_3 + 4);
  self->style_flags = 1;
  self->border_width = 0;
  self->resize_border = 0;
  self->client_x = 0;
  ((PictureWindow *)self)->close_box_hotspot = (Hotspot *)0x0;
  ((PictureWindow *)self)->link_list_head = (PediaLink *)0x0;
  self->caption_height = 0;
  for (i = 0; i < 100; i++) {
    slot = ((PediaAdvanceListView *)self)->pedia_list_init_area + i * 4 + 0x38;
    slot[0] = 0xff;
    slot[1] = 0xff;
    slot[2] = 0xff;
    slot[3] = 0xff;
  }
  for (i = 0; i < 0x27; i++) {
    slot = ((DocumentWindow *)self)->improvement_list_init_area + i * 4 - 0x28;
    slot[0] = 0xff;
    slot[1] = 0xff;
    slot[2] = 0xff;
    slot[3] = 0xff;
  }
  for (i = 0; i < 0x1c; i++) {
    slot = ((PictureWindow *)self)->improvement_key_slots + i * 4 - 0x18;
    slot[0] = 0xff;
    slot[1] = 0xff;
    slot[2] = 0xff;
    slot[3] = 0xff;
  }
  for (i = 0; i < 0x3e; i++) {
    slot = ((PictureWindow *)self)->unit_key_init_slots + i * 4 + 0x10;
    slot[0] = 0xff;
    slot[1] = 0xff;
    slot[2] = 0xff;
    slot[3] = 0xff;
  }
  for (i = 0; i < 7; i++) {
    slot = ((PictureWindow *)self)->pedia_key_init_slots + i * 4 + 0x68;
    slot[0] = 0xff;
    slot[1] = 0xff;
    slot[2] = 0xff;
    slot[3] = 0xff;
  }
  for (i = 0; i < 0x21; i++) {
    slot = ((PictureWindow *)self)->pedia_key_init_slots + i * 4 + 0xa4;
    slot[0] = 0xff;
    slot[1] = 0xff;
    slot[2] = 0xff;
    slot[3] = 0xff;
  }
  for (i = 0; i < 0x100; i++) {
    slot = (u8 *)&((PictureWindow *)self)->advisor_opinions + i * 4 + 0x84;
    slot[0] = 0xff;
    slot[1] = 0xff;
    slot[2] = 0xff;
    slot[3] = 0xff;
  }
  ((PictureWindow *)self)->pedia_advance_names = (PediaListNode *)0x0;
  ((PictureWindow *)self)->pedia_improve_names = (PediaListNode *)0x0;
  ((PictureWindow *)self)->pedia_wonder_names = (PediaListNode *)0x0;
  ((PictureWindow *)self)->pedia_unit_names = (PediaListNode *)0x0;
  ((PictureWindow *)self)->pedia_government_names = (PediaListNode *)0x0;
  ((PictureWindow *)self)->pedia_terrain_names = (PediaListNode *)0x0;
  ((PictureWindow *)self)->pedia_concept_names = (PediaListNode *)0x0;
  ((PictureWindow *)self)->list_hotspot = 0;
  self->client_y = 0;
  return self;
}

/* 004f44a7 auto */
void __thiscall pedia_window_dtor(DibSurface *self)

{
  i32 exc_link;
  i8 *seh_handler;
  int eh_state;
  
  self->vtable = (u32)((pointer *)&leader_anim_frame_starts_block.ptr_fun_3 + 4);
  eh_state = 0x11;
  pedia_free_lists((WindowObjectView *)self);
  pedia_clear_links((WindowObjectView *)self);
  if (((PictureWindow *)self)->close_box_hotspot != (Hotspot *)0x0) {
    if (((PictureWindow *)self)->close_box_hotspot != (Hotspot *)0x0) {
      hotspot_scalar_dtor(((PictureWindow *)self)->close_box_hotspot,1);
    }
    ((PictureWindow *)self)->close_box_hotspot = (Hotspot *)0x0;
  }
  if (((PictureWindow *)self)->list_hotspot != 0) {
    if ((Hotspot *)((PictureWindow *)self)->list_hotspot != (Hotspot *)0x0) {
      hotspot_scalar_dtor((Hotspot *)((PictureWindow *)self)->list_hotspot,1);
    }
    ((PictureWindow *)self)->list_hotspot = 0;
  }
  wnd_destroy_with_surface(self);
  (*((char *)&eh_state + 0)) = 0x10;
  /* inlined unwind funclet 004f4673 */ { scrollbar_dtor((Control *)(*(int *)&self + 0x1ae0)); }
  (*((char *)&eh_state + 0)) = 0xf;
  /* inlined unwind funclet 004f4682 */ { edit_dtor((Control *)(*(int *)&self + 0x1a98)); }
  (*((char *)&eh_state + 0)) = 0xe;
  /* inlined unwind funclet 004f4691 */ { ctrl_dtor((Control *)(*(int *)&self + 0x1a5c)); }
  (*((char *)&eh_state + 0)) = 0xd;
  /* inlined unwind funclet 004f46a0 */ { ctrl_dtor((Control *)(*(int *)&self + 0x1a20)); }
  (*((char *)&eh_state + 0)) = 0xc;
  /* inlined unwind funclet 004f46af */ { ctrl_dtor((Control *)(*(int *)&self + 0x19e4)); }
  (*((char *)&eh_state + 0)) = 0xb;
  /* inlined unwind funclet 004f46be */ { ctrl_dtor((Control *)(*(int *)&self + 0x19a8)); }
  (*((char *)&eh_state + 0)) = 10;
  /* inlined unwind funclet 004f46cd */ { ctrl_dtor((Control *)(*(int *)&self + 0x196c)); }
  (*((char *)&eh_state + 0)) = 9;
  /* inlined unwind funclet 004f46dc */ { ctrl_dtor((Control *)(*(int *)&self + 0x1930)); }
  (*((char *)&eh_state + 0)) = 8;
  /* inlined unwind funclet 004f46eb */ { ctrl_dtor((Control *)(*(int *)&self + 0x18f4)); }
  (*((char *)&eh_state + 0)) = 7;
  /* inlined unwind funclet 004f46fa */ { ctrl_dtor((Control *)(*(int *)&self + 0x18b8)); }
  (*((char *)&eh_state + 0)) = 6;
  /* inlined unwind funclet 004f4709 */ { ctrl_dtor((Control *)(*(int *)&self + 0x187c)); }
  (*((char *)&eh_state + 0)) = 5;
  /* inlined unwind funclet 004f4718 */ { ctrl_dtor((Control *)(*(int *)&self + 0x1840)); }
  (*((char *)&eh_state + 0)) = 4;
  /* inlined unwind funclet 004f4727 */ { ctrl_dtor((Control *)(*(int *)&self + 0x1804)); }
  (*((char *)&eh_state + 0)) = 3;
  /* inlined unwind funclet 004f4736 */ { ctrl_dtor((Control *)(*(int *)&self + 0x17c8)); }
  (*((char *)&eh_state + 0)) = 2;
  /* inlined unwind funclet 004f4745 */ { ctrl_dtor((Control *)(*(int *)&self + 0x178c)); }
  (*((char *)&eh_state + 0)) = 1;
  /* inlined unwind funclet 004f4754 */ { ctrl_dtor((Control *)(*(int *)&self + 0x1750)); }
  eh_state = eh_state & 0xffffff00;
  /* inlined unwind funclet 004f4763 */ { ctrl_dtor((Control *)(*(int *)&self + 0x1714)); }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 004f4772 */ { surfwnd_dtor(*(SurfaceWindow **)&self); }
  return;
}

/* 004f4793 auto */
void __thiscall pedia_clear_links(WindowObjectView *self)

{
  PediaLink *next_link;
  
  while (((PictureWindow *)self)->link_list_head != (PediaLink *)0x0) {
    next_link = ((PictureWindow *)self)->link_list_head->next;
    if ((void *)((PictureWindow *)self)->link_list_head != (void *)0x0) {
      pedia_link_scalar_dtor((void *)((PictureWindow *)self)->link_list_head,1);
    }
    ((PictureWindow *)self)->link_list_head = next_link;
  }
  wnd_flush_paint();
  return;
}

/* 004f4809 auto */
void __thiscall pedia_free_lists(WindowObjectView *self)

{
  PediaListNode *next_node;
  
  while (((PictureWindow *)self)->pedia_advance_names != (PediaListNode *)0x0) {
    next_node = ((PictureWindow *)self)->pedia_advance_names->next;
    if (((PictureWindow *)self)->pedia_advance_names->name != (char *)0x0) {
      operator_delete(((PictureWindow *)self)->pedia_advance_names->name);
    }
    operator_delete(((PictureWindow *)self)->pedia_advance_names);
    ((PictureWindow *)self)->pedia_advance_names = next_node;
  }
  while (((PictureWindow *)self)->pedia_improve_names != (PediaListNode *)0x0) {
    next_node = ((PictureWindow *)self)->pedia_improve_names->next;
    if (((PictureWindow *)self)->pedia_improve_names->name != (char *)0x0) {
      operator_delete(((PictureWindow *)self)->pedia_improve_names->name);
    }
    operator_delete(((PictureWindow *)self)->pedia_improve_names);
    ((PictureWindow *)self)->pedia_improve_names = next_node;
  }
  while (((PictureWindow *)self)->pedia_wonder_names != (PediaListNode *)0x0) {
    next_node = ((PictureWindow *)self)->pedia_wonder_names->next;
    if (((PictureWindow *)self)->pedia_wonder_names->name != (char *)0x0) {
      operator_delete(((PictureWindow *)self)->pedia_wonder_names->name);
    }
    operator_delete(((PictureWindow *)self)->pedia_wonder_names);
    ((PictureWindow *)self)->pedia_wonder_names = next_node;
  }
  while (((PictureWindow *)self)->pedia_unit_names != (PediaListNode *)0x0) {
    next_node = ((PictureWindow *)self)->pedia_unit_names->next;
    if (((PictureWindow *)self)->pedia_unit_names->name != (char *)0x0) {
      operator_delete(((PictureWindow *)self)->pedia_unit_names->name);
    }
    operator_delete(((PictureWindow *)self)->pedia_unit_names);
    ((PictureWindow *)self)->pedia_unit_names = next_node;
  }
  while (((PictureWindow *)self)->pedia_government_names != (PediaListNode *)0x0) {
    next_node = ((PictureWindow *)self)->pedia_government_names->next;
    if (((PictureWindow *)self)->pedia_government_names->name != (char *)0x0) {
      operator_delete(((PictureWindow *)self)->pedia_government_names->name);
    }
    operator_delete(((PictureWindow *)self)->pedia_government_names);
    ((PictureWindow *)self)->pedia_government_names = next_node;
  }
  while (((PictureWindow *)self)->pedia_terrain_names != (PediaListNode *)0x0) {
    next_node = ((PictureWindow *)self)->pedia_terrain_names->next;
    if (((PictureWindow *)self)->pedia_terrain_names->name != (char *)0x0) {
      operator_delete(((PictureWindow *)self)->pedia_terrain_names->name);
    }
    operator_delete(((PictureWindow *)self)->pedia_terrain_names);
    ((PictureWindow *)self)->pedia_terrain_names = next_node;
  }
  while (((PictureWindow *)self)->pedia_concept_names != (PediaListNode *)0x0) {
    next_node = ((PictureWindow *)self)->pedia_concept_names->next;
    if (((PictureWindow *)self)->pedia_concept_names->name != (char *)0x0) {
      operator_delete(((PictureWindow *)self)->pedia_concept_names->name);
    }
    operator_delete(((PictureWindow *)self)->pedia_concept_names);
    ((PictureWindow *)self)->pedia_concept_names = next_node;
  }
  return;
}

/* 004f4b9f auto */
void __thiscall pedia_window_create(DocumentWindow *self)

{
  int left_x;
  int col_width;
  u32 panel_h;
  Control *this_00;
  int avail_width;
  iptr label;
  int yTop;
  u8 *scroll_parent;
  u8 *edit_parent;
  u8 *parent_16;
  u8 *parent_15;
  u8 *parent_14;
  u8 *parent_13;
  u8 *parent_12;
  u8 *parent_11;
  u8 *parent_10;
  u8 *parent_9;
  u8 *parent_8;
  u8 *parent_7;
  u8 *parent_6;
  u8 *parent_5;
  u8 *parent_4;
  u8 *parent_3;
  u8 *parent_2;
  u8 *close_parent;
  Control *close_hotspot;
  tagRECT rect;
  int btn_height;
  i32 exc_link;
  i8 *seh_handler;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  pedia_free_lists((WindowObjectView *)self);
  pedia_clear_links((WindowObjectView *)self);
  self->client_y = 0;
  if (((PictureWindow *)self)->close_box_hotspot != (Hotspot *)0x0) {
    if (((PictureWindow *)self)->close_box_hotspot != (Hotspot *)0x0) {
      hotspot_scalar_dtor(((PictureWindow *)self)->close_box_hotspot,1);
    }
    ((PictureWindow *)self)->close_box_hotspot = (Hotspot *)0x0;
  }
  self->panel_width = 0x280;
  self->panel_height = 400;
  left_x = font_cached_height((GameFont *)((i8 *)&font_size30));
  self->header_height = left_x + panel_bevel_width * 2 + panel_margin_y * 2;
  SetRect((LPRECT)self->pedia_frame_rect,0,0,self->panel_width,self->panel_height);
  panel_h = self->panel_height;
  left_x = self->header_height + panel_margin_y;
  col_width = font_line_spacing((GameFont *)((i8 *)&font_size24));
  SetRect((LPRECT)&self->content_left,0,0,self->panel_width + (panel_padding_x + panel_margin_x) * -2,
          (panel_h - left_x) + ((panel_margin_y * -3 + panel_padding_y * -2) - col_width) + panel_bevel_width * -2);
  OffsetRect((LPRECT)&self->content_left,panel_padding_x + panel_margin_x,self->header_height + panel_margin_y);
  left_x = wnd_client_width((WndBase *)((i8 *)&main_frame_wnd_block.main_frame_wnd));
  col_width = wnd_client_height((WndBase *)((i8 *)&main_frame_wnd_block.main_frame_wnd));
  crt_strcpy((char *)self->pedia_title_text_2,((i8 *)&pedia_window_empty_title_str));
  wnd_create_with_surface
            ((DibSurface *)self,0,0xe02,left_x / 2 - (int)self->panel_width / 2,
             col_width / 2 - (int)self->panel_height / 2,self->panel_width,self->panel_height,(iptr)&game_palette_block.game_palette,(iptr)&main_frame_wnd_block.main_frame_wnd)
  ;
  wnd_set_close_handler((WndEventHandlers *)self->event_handlers,(iptr)pedia_close);
  wnd_set_redraw_callback((SurfaceWindow *)self,(iptr)pedia_redraw_page);
  wnd_set_caption_height((WndBase *)self->window_2,self->header_height);
  wnd_set_keydown_handler((WndEventHandlers *)self->event_handlers,(iptr)pedia_list_on_key);
  wnd_set_keyboard_nav((Wnd *)self->window_2,0);
  left_x = panel_padding_x;
  ((PictureWindow *)self)->close_box_sprite = (u32)((i8 *)&caption_close_button_sprite_block.caption_close_button_sprite);
  ((PictureWindow *)self)->has_close_box = 1;
  panel_h = sprite_width((Sprite *)((PictureWindow *)self)->close_box_sprite);
  ((PictureWindow *)self)->close_box_width = panel_h;
  panel_h = sprite_height((Sprite *)((PictureWindow *)self)->close_box_sprite);
  ((PictureWindow *)self)->close_box_height = panel_h;
  btn_height = (int)(((PictureWindow *)self)->close_box_height * self->header_height) / 0x18;
  col_width = ((int)self->header_height >> 1) - (btn_height >> 1);
  SetRect(&rect,left_x,col_width,(int)(((PictureWindow *)self)->close_box_width * self->header_height) / 0x18 + left_x,
          btn_height + col_width);
  this_00 = (Control *)operator_new(0x40);
  eh_state = 0;
  if (this_00 == (Control *)0x0) {
    close_hotspot = 0;
  }
  else {
    close_hotspot = hotspot_ctor(this_00);
  }
  eh_state = 0xffffffff;
  ((PictureWindow *)self)->close_box_hotspot = (Hotspot *)close_hotspot;
  if (self == (DocumentWindow *)0x0) {
    close_parent = (u8 *)0x0;
  }
  else {
    close_parent = self->window_2;
  }
  hotspot_create
            ((ClickControl *)((PictureWindow *)self)->close_box_hotspot,(iptr)close_parent,4000,(iptr)&rect);
  hotspot_set_click_callback((HotspotClickSetView *)((PictureWindow *)self)->close_box_hotspot,(iptr)pedia_on_close);
  left_x = panel_bevel_width + panel_margin_x + 2;
  panel_h = self->panel_height;
  col_width = font_line_spacing((GameFont *)((i8 *)&font_size24));
  yTop = panel_h - (col_width + (panel_margin_y + panel_padding_y) * 2);
  avail_width = self->panel_width - (panel_margin_x * 2 + panel_bevel_width * 2 + 5);
  btn_height = font_line_spacing((GameFont *)((i8 *)&font_size24));
  btn_height += panel_padding_y * 2;
  col_width = avail_width / 2;
  SetRect(&rect,left_x,yTop,col_width + left_x,btn_height + yTop);
  if (self == (DocumentWindow *)0x0) {
    parent_2 = (u8 *)0x0;
  }
  else {
    parent_2 = self->window_2;
  }
  label = (iptr)label_string(label_string_ids[0x27]);
  button_create
            ((Control *)((PictureWindow *)self)->list_describe_button,(iptr)parent_2,0xfa1,(iptr)&rect,(const char *)label);
  button_set_callback((Control *)((PictureWindow *)self)->list_describe_button,(iptr)pedia_toggle_describe);
  SetRect(&rect,col_width + left_x,yTop,col_width * 2 + left_x,btn_height + yTop);
  if (self == (DocumentWindow *)0x0) {
    parent_3 = (u8 *)0x0;
  }
  else {
    parent_3 = self->window_2;
  }
  label = (iptr)label_string(label_string_ids[0x147]);
  button_create
            ((Control *)&((PictureWindow *)self)->list_close_button,(iptr)parent_3,0xfa2,(iptr)&rect,(const char *)label);
  ctrl_set_default_button((Control *)&((PictureWindow *)self)->list_close_button);
  ctrl_set_cancel_button((Control *)&((PictureWindow *)self)->list_close_button);
  button_set_callback((Control *)&((PictureWindow *)self)->list_close_button,(iptr)pedia_on_close);
  SetRect(&rect,left_x,yTop,avail_width / 2 + left_x,btn_height + yTop);
  if (self == (DocumentWindow *)0x0) {
    parent_4 = (u8 *)0x0;
  }
  else {
    parent_4 = self->window_2;
  }
  label = (iptr)label_string(label_string_ids[0x356]);
  button_create
            ((Control *)((u8 *)&((PictureWindow *)self)->concept_list_back_button),(iptr)parent_4,0xfb2,(iptr)&rect,(const char *)label);
  button_set_callback((Control *)((u8 *)&((PictureWindow *)self)->concept_list_back_button),(iptr)pedia_on_back);
  col_width = avail_width / 3;
  SetRect(&rect,left_x,yTop,col_width + left_x,btn_height + yTop);
  if (self == (DocumentWindow *)0x0) {
    parent_5 = (u8 *)0x0;
  }
  else {
    parent_5 = self->window_2;
  }
  label = (iptr)label_string(label_string_ids[0x27]);
  button_create
            ((Control *)((PictureWindow *)self)->advance_list_describe_button,(iptr)parent_5,0xfab,(iptr)&rect,(const char *)label);
  button_set_callback((Control *)((PictureWindow *)self)->advance_list_describe_button,(iptr)pedia_toggle_describe);
  SetRect(&rect,col_width + left_x,yTop,col_width * 2 + left_x,btn_height + yTop);
  if (self == (DocumentWindow *)0x0) {
    parent_6 = (u8 *)0x0;
  }
  else {
    parent_6 = self->window_2;
  }
  label = (iptr)label_string(label_string_ids[0x360]);
  button_create
            ((Control *)(((PictureWindow *)self)->advance_list_tech_tree_button),(iptr)parent_6,0xfac,(iptr)&rect,(const char *)label);
  button_set_callback((Control *)(((PictureWindow *)self)->advance_list_tech_tree_button),(iptr)pedia_show_tech_tree);
  SetRect(&rect,col_width * 2 + left_x,yTop,col_width * 3 + left_x,btn_height + yTop);
  if (self == (DocumentWindow *)0x0) {
    parent_7 = (u8 *)0x0;
  }
  else {
    parent_7 = self->window_2;
  }
  label = (iptr)label_string(label_string_ids[0x147]);
  button_create
            ((Control *)(((PictureWindow *)self)->advance_list_close_button),(iptr)parent_7,0xfad,(iptr)&rect,(const char *)label);
  ctrl_set_default_button((Control *)(((PictureWindow *)self)->advance_list_close_button));
  ctrl_set_cancel_button((Control *)(((PictureWindow *)self)->advance_list_close_button));
  button_set_callback((Control *)(((PictureWindow *)self)->advance_list_close_button),(iptr)pedia_on_close);
  col_width = (int)(avail_width + (avail_width >> 0x1f & 3U)) >> 2;
  SetRect(&rect,left_x,yTop,col_width + left_x,btn_height + yTop);
  if (self == (DocumentWindow *)0x0) {
    parent_8 = (u8 *)0x0;
  }
  else {
    parent_8 = self->window_2;
  }
  label = (iptr)label_string(label_string_ids[0x356]);
  button_create
            ((Control *)((u8 *)&((PictureWindow *)self)->advance_detail_back_button),(iptr)parent_8,0xfae,(iptr)&rect,(const char *)label);
  button_set_callback((Control *)((u8 *)&((PictureWindow *)self)->advance_detail_back_button),(iptr)pedia_on_back);
  SetRect(&rect,col_width + left_x,yTop,col_width * 2 + left_x,btn_height + yTop);
  if (self == (DocumentWindow *)0x0) {
    parent_9 = (u8 *)0x0;
  }
  else {
    parent_9 = self->window_2;
  }
  label = (iptr)label_string(label_string_ids[0x360]);
  button_create
            ((Control *)((u8 *)&((PictureWindow *)self)->advance_detail_tech_tree_button),(iptr)parent_9,0xfaf,(iptr)&rect,(const char *)label);
  button_set_callback((Control *)((u8 *)&((PictureWindow *)self)->advance_detail_tech_tree_button),(iptr)pedia_show_tech_tree);
  SetRect(&rect,col_width * 2 + left_x,yTop,col_width * 3 + left_x,btn_height + yTop);
  if (self == (DocumentWindow *)0x0) {
    parent_10 = (u8 *)0x0;
  }
  else {
    parent_10 = self->window_2;
  }
  label = (iptr)label_string(label_string_ids[0x2c1]);
  button_create
            ((Control *)(((PictureWindow *)self)->advance_detail_describe_button),(iptr)parent_10,0xfb0,(iptr)&rect,(const char *)label);
  button_set_callback((Control *)(((PictureWindow *)self)->advance_detail_describe_button),(iptr)pedia_toggle_describe);
  SetRect(&rect,col_width * 3 + left_x,yTop,col_width * 4 + left_x,btn_height + yTop);
  if (self == (DocumentWindow *)0x0) {
    parent_11 = (u8 *)0x0;
  }
  else {
    parent_11 = self->window_2;
  }
  label = (iptr)label_string(label_string_ids[0x147]);
  button_create
            ((Control *)((u8 *)&((PictureWindow *)self)->advance_detail_close_button),(iptr)parent_11,0xfb1,(iptr)&rect,(const char *)label);
  ctrl_set_default_button((Control *)((u8 *)&((PictureWindow *)self)->advance_detail_close_button));
  ctrl_set_cancel_button((Control *)((u8 *)&((PictureWindow *)self)->advance_detail_close_button));
  button_set_callback((Control *)((u8 *)&((PictureWindow *)self)->advance_detail_close_button),(iptr)pedia_on_close);
  col_width = avail_width / 3;
  SetRect(&rect,left_x,yTop,col_width + left_x,btn_height + yTop);
  if (self == (DocumentWindow *)0x0) {
    parent_12 = (u8 *)0x0;
  }
  else {
    parent_12 = self->window_2;
  }
  label = (iptr)label_string(label_string_ids[0x356]);
  button_create
            ((Control *)&((PictureWindow *)self)->detail_back_button,(iptr)parent_12,0xfa3,(iptr)&rect,(const char *)label);
  button_set_callback((Control *)&((PictureWindow *)self)->detail_back_button,(iptr)pedia_on_back);
  SetRect(&rect,col_width + left_x,yTop,col_width * 2 + left_x,btn_height + yTop);
  if (self == (DocumentWindow *)0x0) {
    parent_13 = (u8 *)0x0;
  }
  else {
    parent_13 = self->window_2;
  }
  label = (iptr)label_string(label_string_ids[0x2c1]);
  button_create
            ((Control *)(((PictureWindow *)self)->detail_describe_button),(iptr)parent_13,0xfa4,(iptr)&rect,(const char *)label);
  button_set_callback((Control *)(((PictureWindow *)self)->detail_describe_button),(iptr)pedia_toggle_describe);
  SetRect(&rect,col_width * 2 + left_x,yTop,col_width * 3 + left_x,btn_height + yTop);
  if (self == (DocumentWindow *)0x0) {
    parent_14 = (u8 *)0x0;
  }
  else {
    parent_14 = self->window_2;
  }
  label = (iptr)label_string(label_string_ids[0x147]);
  button_create
            ((Control *)&((PictureWindow *)self)->detail_close_button,(iptr)parent_14,0xfa5,(iptr)&rect,(const char *)label);
  button_set_callback((Control *)&((PictureWindow *)self)->detail_close_button,(iptr)pedia_on_close);
  avail_width = avail_width / 2;
  SetRect(&rect,left_x,yTop,avail_width + left_x,btn_height + yTop);
  if (self == (DocumentWindow *)0x0) {
    parent_15 = (u8 *)0x0;
  }
  else {
    parent_15 = self->window_2;
  }
  label = (iptr)label_string(label_string_ids[0x356]);
  button_create
            ((Control *)(((PictureWindow *)self)->text_back_button),(iptr)parent_15,0xfa6,(iptr)&rect,(const char *)label);
  button_set_callback((Control *)(((PictureWindow *)self)->text_back_button),(iptr)pedia_on_back);
  SetRect(&rect,avail_width + left_x,yTop,avail_width * 2 + left_x,btn_height + yTop);
  if (self == (DocumentWindow *)0x0) {
    parent_16 = (u8 *)0x0;
  }
  else {
    parent_16 = self->window_2;
  }
  label = (iptr)label_string(label_string_ids[0x147]);
  button_create
            ((Control *)((u8 *)&((PictureWindow *)self)->text_close_button),(iptr)parent_16,0xfa7,(iptr)&rect,(const char *)label);
  button_set_callback((Control *)((u8 *)&((PictureWindow *)self)->text_close_button),(iptr)pedia_on_close);
  ui_set_button_font((iptr)&font_size24);
  pedia_clear_links((WindowObjectView *)self);
  ui_set_default_font((iptr)&font_size21);
  if (self == (DocumentWindow *)0x0) {
    edit_parent = (u8 *)0x0;
  }
  else {
    edit_parent = self->window_2;
  }
  edit_create_styled
            ((EditControl *)((u8 *)&((PictureWindow *)self)->description_edit),(iptr)edit_parent,0xfaa,(iptr)&self->content_left,
             (const char *)&str_empty_143,0x122,0);
  rect.left = self->content_left;
  rect.top = self->content_top;
  rect.right = self->content_right;
  panel_h = self->content_bottom;
  rect.bottom = panel_h;
  left_x = GetSystemMetrics(3);
  rect.top = panel_h - left_x;
  if (self == (DocumentWindow *)0x0) {
    scroll_parent = (u8 *)0x0;
  }
  else {
    scroll_parent = self->window_2;
  }
  scrollbar_create
            ((Control *)((u8 *)&((PictureWindow *)self)->list_scrollbar),(iptr)scroll_parent,0xfa8,(iptr)&rect,0);
  scrollbar_set_callback((Control *)((u8 *)&((PictureWindow *)self)->list_scrollbar),(iptr)pedia_list_on_scroll);
  scrollbar_set_track_callback((ScrollbarTrackSetView *)((u8 *)&((PictureWindow *)self)->list_scrollbar),(iptr)pedia_list_on_scroll);
  scrollbar_set_page_size((Control *)((u8 *)&((PictureWindow *)self)->list_scrollbar),2);
  pedia_load_indexes(self);
  return;
}

/* 004f5b24 auto */
void __cdecl pedia_on_close(void)

{
  if (pedia_window_block.pedia_modal_active == 1) {
    wnd_end_modal_loop((ModalMenuWindow *)((i8 *)&pedia_window_block.pedia_window_wnd));
    pedia_window_block.pedia_modal_active = 0;
  }
  pedia_clear_links((WindowObjectView *)((i8 *)&pedia_window_block.pedia_window));
  pedia_window_block.pedia_history_count = 0;
  pedia_close();
  return;
}

/* 004f5b6f auto */
void __cdecl pedia_on_back(void)

{
  if (pedia_window_block.pedia_history_count != 0) {
    do {
      pedia_window_block.pedia_history_count--;
      if (((pedia_window_block.pedia_history_count == 0) || (pedia_window_block.pedia_history_categories[pedia_window_block.pedia_history_count] != pedia_window_block.pedia_category)) ||
         (pedia_window_block.pedia_history_page_modes[pedia_window_block.pedia_history_count] != pedia_window_block.pedia_page_mode)) break;
    } while (pedia_window_block.pedia_history_topics[pedia_window_block.pedia_history_count] == pedia_window_block.pedia_topic);
    if (pedia_window_block.pedia_history_count != 0) {
      pedia_going_back = 1;
      pedia_back_topic = pedia_window_block.pedia_history_topics[pedia_window_block.pedia_history_count];
      pedia_window_block.pedia_popped_page_mode = pedia_window_block.pedia_history_page_modes[pedia_window_block.pedia_history_count];
      pedia_window_block.pedia_popped_category = pedia_window_block.pedia_history_categories[pedia_window_block.pedia_history_count];
    }
    if (pedia_window_block.pedia_history_page_modes[pedia_window_block.pedia_history_count] != 0) {
      pedia_window_block.pedia_category = pedia_window_block.pedia_history_categories[pedia_window_block.pedia_history_count];
      pedia_window_block.pedia_page_mode = pedia_window_block.pedia_history_page_modes[pedia_window_block.pedia_history_count] - 1;
      pedia_window_block.pedia_topic = pedia_window_block.pedia_history_topics[pedia_window_block.pedia_history_count];
      pedia_window_block.pedia_selected_item = pedia_window_block.pedia_topic;
      pedia_toggle_describe(1);
      return;
    }
    pedia_window_block.pedia_category = pedia_window_block.pedia_history_categories[pedia_window_block.pedia_history_count];
    pedia_window_block.pedia_page_mode = 1;
    pedia_window_block.pedia_topic = pedia_window_block.pedia_history_topics[pedia_window_block.pedia_history_count];
    pedia_window_block.pedia_selected_item = pedia_window_block.pedia_topic;
  }
  if (pedia_window_block.pedia_page_mode == 0) {
    if (pedia_window_block.pedia_modal_active == 1) {
      wnd_end_modal_loop((ModalMenuWindow *)((i8 *)&pedia_window_block.pedia_window_wnd));
      pedia_window_block.pedia_modal_active = 0;
    }
    pedia_close();
  }
  else {
    if (pedia_window_block.pedia_page_mode == 1) {
      pedia_window_block.pedia_page_mode = 0;
      pedia_update_controls((MediaWindow *)((i8 *)&pedia_window_block.pedia_window));
      pedia_redraw_page();
      pedia_window_block.pedia_selected_item = pedia_window_block.pedia_topic;
      pedia_redraw((PediaRedrawView *)((i8 *)&pedia_window_block.pedia_window));
    }
    else if ((pedia_window_block.pedia_category == 6) || (pedia_window_block.pedia_category == 7)) {
      pedia_window_block.pedia_page_mode = 0;
      pedia_update_controls((MediaWindow *)((i8 *)&pedia_window_block.pedia_window));
      pedia_redraw_page();
      pedia_window_block.pedia_selected_item = pedia_window_block.pedia_topic;
      pedia_redraw((PediaRedrawView *)((i8 *)&pedia_window_block.pedia_window));
    }
    else {
      pedia_window_block.pedia_page_mode = 0;
      pedia_toggle_describe(1);
    }
    pedia_history_push((ScaledWindowView *)((i8 *)&pedia_window_block.pedia_window));
  }
  return;
}

/* 004f5dd1 auto */
i32 __cdecl pedia_close(void)

{
  pedia_window_block.pedia_closed = 1;
  pedia_window_block.pedia_history_count = 0;
  if (pedia_window_block.pedia_close_hotspot != (Hotspot *)0x0) {
    if (pedia_window_block.pedia_close_hotspot != (Hotspot *)0x0) {
      hotspot_scalar_dtor(pedia_window_block.pedia_close_hotspot,1);
    }
    pedia_window_block.pedia_close_hotspot = (Hotspot *)0x0;
  }
  wnd_hide((WndBase *)((i8 *)&pedia_window_block.pedia_window_wnd));
  wnd_focus_and_raise((WndBase *)((i8 *)&main_frame_wnd_block.main_frame_wnd));
  ui_flush_input();
  return 0;
}

/* 004f5e52 auto */
void __cdecl pedia_redraw_page(void)

{
  if (pedia_window_block.pedia_closed == 0) {
    if (pedia_window_block.pedia_page_mode == 0) {
      pedia_set_category_title((WindowObjectView *)((i8 *)&pedia_window_block.pedia_window),pedia_window_block.pedia_category);
    }
    pedia_clear_links((WindowObjectView *)((i8 *)&pedia_window_block.pedia_window));
    gfx_set_draw_target((iptr)&pedia_window_block.pedia_window);
    pedia_draw_frame((MediaWindow *)((i8 *)&pedia_window_block.pedia_window));
    pedia_draw_category_body((DocumentWindow *)((i8 *)&pedia_window_block.pedia_window),pedia_window_block.pedia_category,pedia_window_block.pedia_page_mode);
    wnd_blit_surface((DibSurface *)((i8 *)&pedia_window_block.pedia_window));
  }
  return;
}

/* 004f5ed2 auto */
void __cdecl pedia_show_tech_tree(void)

{
  pedia_window_block.pedia_page_mode = 0;
  pedia_window_block.pedia_category = 8;
  pedia_update_controls((MediaWindow *)((i8 *)&pedia_window_block.pedia_window));
  pedia_redraw_page();
  pedia_window_block.pedia_selected_item = pedia_window_block.pedia_topic;
  pedia_redraw((PediaRedrawView *)((i8 *)&pedia_window_block.pedia_window));
  pedia_history_push((ScaledWindowView *)((i8 *)&pedia_window_block.pedia_window));
  return;
}

/* 004f5f23 auto */
void __cdecl pedia_toggle_describe(i32 unused_arg)

{
  char *title;
  uptr item;
  
  item = (*(uptr *)&pedia_window_block.pedia_selected_item);
  if (pedia_window_block.pedia_page_mode == 0) {
    (*(uptr *)&pedia_window_block.pedia_topic) = (*(uptr *)&pedia_window_block.pedia_selected_item);
    pedia_window_block.pedia_page_mode = 1;
    pedia_clear_links((WindowObjectView *)((i8 *)&pedia_window_block.pedia_window));
    pedia_update_controls((MediaWindow *)((i8 *)&pedia_window_block.pedia_window));
    switch(pedia_window_block.pedia_category) {
    case 1:
    case 8:
      title = pedia_lookup_text(pedia_window_block.pedia_advance_names,item);
      crt_strcpy(((i8 *)&pedia_window_block.pedia_title_text),title);
      pedia_draw_frame((MediaWindow *)((i8 *)&pedia_window_block.pedia_window));
      pedia_draw_advance_page((DocumentWindow *)((i8 *)&pedia_window_block.pedia_window));
      break;
    case 2:
      title = pedia_lookup_text(pedia_window_block.pedia_improvement_names,item);
      crt_strcpy(((i8 *)&pedia_window_block.pedia_title_text),title);
      pedia_draw_frame((MediaWindow *)((i8 *)&pedia_window_block.pedia_window));
      pedia_draw_improvement_page((DocumentWindow *)((i8 *)&pedia_window_block.pedia_window));
      break;
    case 3:
      title = pedia_lookup_text(pedia_window_block.pedia_wonder_names,item);
      crt_strcpy(((i8 *)&pedia_window_block.pedia_title_text),title);
      pedia_draw_frame((MediaWindow *)((i8 *)&pedia_window_block.pedia_window));
      pedia_draw_improvement((DocumentWindow *)((i8 *)&pedia_window_block.pedia_window));
      break;
    case 4:
      title = pedia_lookup_text(pedia_window_block.pedia_unit_names,item);
      crt_strcpy(((i8 *)&pedia_window_block.pedia_title_text),title);
      pedia_draw_frame((MediaWindow *)((i8 *)&pedia_window_block.pedia_window));
      pedia_draw_unit_page((DocumentWindow *)((i8 *)&pedia_window_block.pedia_window));
      break;
    case 5:
      title = pedia_lookup_text(pedia_window_block.pedia_terrain_names,item);
      crt_strcpy(((i8 *)&pedia_window_block.pedia_title_text),title);
      pedia_draw_frame((MediaWindow *)((i8 *)&pedia_window_block.pedia_window));
      pedia_draw_terrain_page((DocumentWindow *)((i8 *)&pedia_window_block.pedia_window));
      break;
    case 6:
      pedia_window_block.pedia_page_mode = 2;
      title = pedia_lookup_text(pedia_window_block.pedia_government_names,item);
      crt_strcpy(((i8 *)&pedia_window_block.pedia_title_text),title);
      pedia_draw_frame((MediaWindow *)((i8 *)&pedia_window_block.pedia_window));
      pedia_fill_background((WindowObjectView *)((i8 *)&pedia_window_block.pedia_window),(RECT *)&pedia_window_block.pedia_describe_rect,1);
      pedia_load_description((WindowObjectView *)((i8 *)&pedia_window_block.pedia_window),item);
      break;
    case 7:
      pedia_window_block.pedia_page_mode = 2;
      title = pedia_lookup_text(pedia_window_block.pedia_concept_names,item);
      crt_strcpy(((i8 *)&pedia_window_block.pedia_title_text),title);
      pedia_draw_frame((MediaWindow *)((i8 *)&pedia_window_block.pedia_window));
      pedia_fill_background((WindowObjectView *)((i8 *)&pedia_window_block.pedia_window),(RECT *)&pedia_window_block.pedia_describe_rect,1);
      pedia_load_description((WindowObjectView *)((i8 *)&pedia_window_block.pedia_window),item);
      break;
    default:
      text_append((const char *)&str_this_should_not_happen);
    }
    wnd_blit_surface((DibSurface *)((i8 *)&pedia_window_block.pedia_window));
  }
  else if (pedia_window_block.pedia_page_mode == 1) {
    pedia_window_block.pedia_page_mode = 2;
    pedia_clear_links((WindowObjectView *)((i8 *)&pedia_window_block.pedia_window));
    pedia_update_controls((MediaWindow *)((i8 *)&pedia_window_block.pedia_window));
    pedia_draw_frame((MediaWindow *)((i8 *)&pedia_window_block.pedia_window));
    pedia_fill_background((WindowObjectView *)((i8 *)&pedia_window_block.pedia_window),(RECT *)&pedia_window_block.pedia_describe_rect,0);
    pedia_load_description((WindowObjectView *)((i8 *)&pedia_window_block.pedia_window),item);
  }
  pedia_history_push((ScaledWindowView *)((i8 *)&pedia_window_block.pedia_window));
  return;
}

/* 004f6244 auto */
void __thiscall pedia_draw_frame(MediaWindow *self)

{
  int tmp_a;
  int tmp_b;
  i8 sprite_ctx[16];
  int y2;
  int x2;
  i8 *font2;
  int i;
  tagRECT rect;
  
  surface_reset_clip((DibSurface *)self);
  crt_memcpy(&rect,self->pedia_frame_rect,0x10);
  for (i = 0; i < panel_bevel_width; i++) {
    gfx_draw_bevel_rect((iptr)self,&rect,(uint)dlg_bevel_light_color,(uint)dlg_bevel_dark_color);
    rect_deflate((iptr)&rect,1,1);
  }
  pedia_fill_background((WindowObjectView *)self,&rect,1);
  rect_deflate((iptr)&rect,panel_padding_x + panel_bevel_width * -2,0);
  rect.top = rect.top + self->header_height + panel_bevel_width * -2;
  tmp_a = rect_height((RECT *)self->pedia_frame_rect);
  tmp_b = font_line_spacing((GameFont *)((i8 *)&font_size24));
  rect.bottom = tmp_a + ((panel_margin_y * -3 + panel_padding_y * -2) - tmp_b);
  for (i = 0; i < panel_bevel_width; i++) {
    gfx_draw_bevel_rect((iptr)self,&rect,(uint)dlg_bevel_dark_color,(uint)dlg_bevel_light_color);
    rect_deflate((iptr)&rect,1,1);
  }
  pedia_fill_background((WindowObjectView *)self,&rect,2);
  tmp_a = panel_padding_x;
  x2 = panel_padding_x;
  self->panel_width = (int)((int)((PictureWindow *)self)->close_box_width * self->header_height) / 0x18;
  self->panel_height = (int)((int)((PictureWindow *)self)->close_box_height * self->header_height) / 0x18;
  y2 = ((int)self->header_height >> 1) - ((int)self->panel_height >> 1);
  SetRect(&rect,tmp_a,y2,self->panel_width + tmp_a,self->panel_height + y2);
  gfx_set_scale_ratio(self->header_height,0x18);
  sprite_draw
            ((Sprite *)((PictureWindow *)self)->close_box_sprite,(iptr)sprite_ctx,(iptr)self,x2,y2
            );
  gfx_reset_zoom_scale();
  x2 += self->panel_width;
  font2 = ((i8 *)&font_size30);
  tmp_a = (self->frame_rect_right - x2) - panel_padding_x;
  tmp_b = font_text_width
                    ((GameFont *)((i8 *)&font_size30),(const char *)self->pedia_title_text_2);
  x2 += (tmp_a / 2 - (tmp_b >> 1));
  y2 = panel_bevel_width + panel_margin_y;
  gfx_set_text_color_index(10);
  surface_draw_text
            ((DibSurface *)self,(iptr)font2,(const char *)self->pedia_title_text_2,x2 + 2,
             y2 + 1,5);
  gfx_set_text_color_index(0x1a);
  surface_draw_text
            ((DibSurface *)self,(iptr)font2,(const char *)self->pedia_title_text_2,x2 + 1,y2
             ,5);
  surface_draw_text
            ((DibSurface *)self,(iptr)font2,(const char *)self->pedia_title_text_2,x2,y2,5);
  surface_set_clip((DibSurface *)self,(RECT *)&self->content_left);
  return;
}

/* 004f6564 auto */
void __thiscall pedia_fill_background(WindowObjectView *self,RECT *rect,int style)

{
  i32 height;
  i32 width;
  i32 offset_x;
  i32 offset_y;
  
  if ((dlg_frame_tile_surface == 0) || (style != 1)) {
    if ((dlg_client_tile_surface == 0) || (style != 2)) {
      gfx_fill_rect((iptr)self,rect,(uint)dlg_bg_color);
    }
    else {
      offset_y = 0;
      offset_x = 0;
      height = rect_height(rect);
      width = rect_width(rect);
      gfx_tile_fill((iptr)self,dlg_client_tile_surface,rect->left,rect->top
                         ,width,height,offset_x,offset_y);
    }
  }
  else {
    offset_y = 0;
    offset_x = 0;
    height = rect_height(rect);
    width = rect_width(rect);
    gfx_tile_fill((iptr)self,dlg_frame_tile_surface,rect->left,rect->top,
                       width,height,offset_x,offset_y);
  }
  return;
}

/* 004f6646 auto */
void __thiscall pedia_redraw(PediaRedrawView *self)

{
  u32 page_mode;
  
  page_mode = self->border_width;
  if (page_mode == 0) {
    if (self->caption_height != 8) {
      pedia_draw_item_list((ListPaneWindow *)self);
    }
  }
  else if ((page_mode != 1) && (page_mode != 2)) {
    pedia_close();
  }
  return;
}

/* 004f66c6 auto */
void __thiscall pedia_draw_item_list(ListPaneWindow *self)

{
  int dim_a;
  int dim_b;
  int dim_c;
  char *name_text;
  i32 fill_color_e;
  i32 fill_color_d;
  int shield_x;
  i32 fill_color_c;
  int icon_x2;
  i32 fill_color_b;
  i32 fill_color_a;
  i32 terrain_fill_color;
  i8 shield_ctx[16];
  i8 icon_ctx2[16];
  i8 icon_ctx[16];
  i8 resource_ctx[16];
  i8 hill_ctx2[16];
  i8 forest_ctx2[16];
  i8 grass_ctx[16];
  i8 mountain_ctx[16];
  i8 hill_ctx[16];
  i8 forest_ctx[16];
  i8 base_ctx[16];
  int text_y_off;
  iptr advance;
  int col_width;
  int base_terrain;
  int icon_x;
  i32 scale_num2;
  int col;
  int col_base;
  int row;
  int row_y;
  i32 scale_den2;
  int col_x;
  int list_width2;
  int shadow_color2;
  uint resource_variant;
  int text_x_off;
  int icon_mode;
  Sprite *icon_sprite;
  int text_color2;
  uint is_selected;
  tagRECT row_rect;
  int row_height;
  i8 saved_clip[16];
  GameFont *font2;
  
  icon_mode = 0;
  pedia_history_push((ScaledWindowView *)((i8 *)&pedia_window_block.pedia_window));
  surface_get_clip((DibSurface *)self,(RECT *)saved_clip);
  surface_set_clip((DibSurface *)self,(RECT *)(iptr)((u8 *)&((PictureWindow *)self)->list_rect));
  surface_fill_rect((DibSurface *)self,(iptr)((u8 *)&((PictureWindow *)self)->list_rect),list_bg_color);
  font2 = (GameFont *)((i8 *)&font_size21);
  col_x = (int)((PictureWindow *)self)->list_rect;
  list_width2 = rect_width((RECT *)(iptr)((u8 *)&((PictureWindow *)self)->list_rect));
  col_width = list_width2 / 2;
  row_height = rect_height((RECT *)(iptr)((u8 *)&((PictureWindow *)self)->list_rect));
  row_height = row_height / 9;
  dim_a = row_height / 2;
  dim_b = font_cached_height(font2);
  text_y_off = dim_a - dim_b / 2;
  col = 0;
  do {
    if (1 < col) {
      surface_set_clip((DibSurface *)self,(RECT *)saved_clip);
      ctrl_show_and_redraw((Control *)((PictureWindow *)self)->list_hotspot);
      return;
    }
    col_base = col * 9;
    for (row = 0; row < 9; row++) {
      row_y = (int)((PictureWindow *)self)->list_rect_top + row_height * row;
      SetRect(&row_rect,col_x,row_y,col_width + col_x - 2,row_height + row_y);
      if ((((u32)((PictureWindow *)self)->list_top_index) != 0xffffffff) &&
         ((int)(((u32)((PictureWindow *)self)->list_top_index) + col_base + row) < ((PictureWindow *)self)->list_count)) {
        advance = ((PictureWindow *)self)->list_items[(((u32)((PictureWindow *)self)->list_top_index) + col_base + row)];
        is_selected = (uint)(((u32)((PictureWindow *)self)->list_top_index) + col_base + row == pedia_window_block.pedia_selected_item);
        if (is_selected == 0) {
          text_color2 = list_text_color;
          shadow_color2 = list_shadow_color;
        }
        else {
          text_color2 = dlg_sel_text_color;
          shadow_color2 = dlg_sel_text_shadow_color;
        }
        gfx_get_scale_ratio((iptr)&scale_num2,(iptr)&scale_den2);
        switch(self->caption_height) {
        case 1:
          icon_sprite = (Sprite *)
                     (((i8 *)&government_sprites_block.advance_category_icon_sprites) +
                     (char)advances[advance].epoch * 0x3c +
                     (char)advances[advance].category * 0xf0);
          gfx_set_scale_ratio(3,2);
          icon_mode = 3;
          break;
        case 2:
          icon_sprite = (Sprite *)(((i8 *)&caption_close_button_sprite_block.improvement_icon_sprites) + advance * 0x3c);
          gfx_set_scale_ratio(3,2);
          icon_mode = 3;
          break;
        case 3:
          icon_sprite = (Sprite *)(((i8 *)&caption_close_button_sprite_block.improvement_icon_sprites) + advance * 0x3c);
          gfx_set_scale_ratio(3,2);
          icon_mode = 3;
          break;
        case 4:
          icon_sprite = (Sprite *)(((i8 *)&pollution_sprite_block.unit_sprites) + advance * 0x3c);
          break;
        case 5:
          icon_mode = -5;
          base_terrain = advance % 0xb;
          if ((((u32)((PictureWindow *)self)->list_top_index) + col_base + row & 1) == 0) {
            icon_x = panel_margin_x;
          }
          else {
            dim_a = sprite_width((Sprite *)((i8 *)&forest_sprites));
            icon_x = panel_margin_x + dim_a / 2;
          }
          dim_a = sprite_width((Sprite *)((i8 *)&forest_sprites));
          text_x_off = panel_margin_x + (dim_a * 3) / 2 + 2;
          row_rect.left += text_x_off;
          if (is_selected == 0) {
            terrain_fill_color = list_bg_color;
          }
          else {
            terrain_fill_color = list_sel_bg_color;
          }
          surface_fill_rect((DibSurface *)self,(iptr)&row_rect,terrain_fill_color);
          sprite_draw
                    ((Sprite *)(((i8 *)&terrain_base_sprites_block.terrain_base_sprites) + base_terrain * 0x3c),(iptr)base_ctx,(iptr)&pedia_window_block.pedia_window,
                     icon_x + col_x,row_y);
          if (advance < 0xb) {
            if (advance == 3) {
              sprite_draw
                        ((Sprite *)((i8 *)&forest_sprites),(iptr)forest_ctx,(iptr)&pedia_window_block.pedia_window,icon_x + col_x,
                         row_y);
            }
            else if (advance == 4) {
              sprite_draw
                        ((Sprite *)((i8 *)&hill_sprites_block.hill_sprites),(iptr)hill_ctx,(iptr)&pedia_window_block.pedia_window,icon_x + col_x,
                         row_y);
            }
            else if (advance == 5) {
              sprite_draw
                        ((Sprite *)((i8 *)&mountain_sprites),(iptr)mountain_ctx,(iptr)&pedia_window_block.pedia_window,icon_x + col_x,
                         row_y);
            }
          }
          else {
            resource_variant = (uint)(0x15 < advance);
            switch(advance) {
            case 0xd:
            case 0x18:
              sprite_draw
                        ((Sprite *)((i8 *)&grassland_shield_sprite),(iptr)grass_ctx,(iptr)&pedia_window_block.pedia_window,icon_x + col_x,
                         row_y);
              goto draw_row_text;
            case 0xe:
            case 0x19:
              sprite_draw
                        ((Sprite *)((i8 *)&forest_sprites),(iptr)forest_ctx2,(iptr)&pedia_window_block.pedia_window,icon_x + col_x,
                         row_y);
              break;
            case 0xf:
            case 0x1a:
              sprite_draw
                        ((Sprite *)((i8 *)&hill_sprites_block.hill_sprites),(iptr)hill_ctx2,(iptr)&pedia_window_block.pedia_window,icon_x + col_x,
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
                      ((Sprite *)(((i8 *)&city_down_arrow_sprite_block.terrain_resource_sprites) + base_terrain * 0x78 + resource_variant * 0x3c),
                       (iptr)resource_ctx,(iptr)&pedia_window_block.pedia_window,icon_x + col_x,row_y);
          }
          break;
        case 6:
        case 7:
          icon_mode = -2;
          break;
        default:
          text_append((const char *)&str_this_should_not_happen_2);
        }
draw_row_text:
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
          surface_fill_rect((DibSurface *)self,(iptr)&row_rect,fill_color_a);
          sprite_draw
                    (icon_sprite,(iptr)icon_ctx,(iptr)&pedia_window_block.pedia_window,panel_margin_x + col_x,row_rect.top + 1);
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
          surface_fill_rect((DibSurface *)self,(iptr)&row_rect,fill_color_b);
          icon_x = sprite_width(icon_sprite);
          icon_x += panel_margin_x * 2;
          icon_x2 = icon_x;
          if ((((u32)((PictureWindow *)self)->list_top_index) + col_base + row & 1) == 0) {
            icon_x2 = panel_margin_x;
          }
          dim_b = row_y + row_height / 2;
          dim_a = sprite_get_height(icon_sprite);
          sprite_draw
                    (icon_sprite,(iptr)icon_ctx2,(iptr)&pedia_window_block.pedia_window,col_x + icon_x2,dim_b - dim_a / 2);
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
          surface_fill_rect((DibSurface *)self,(iptr)&row_rect,fill_color_c);
          dim_a = sprite_width(icon_sprite);
          dim_b = sprite_width(icon_sprite);
          dim_c = sprite_width(icon_sprite);
          icon_x = ((int)(dim_a + (dim_a >> 0x1f & 3U)) >> 2) + dim_b / 6 + dim_c +
                     panel_margin_x * 2;
          icon_sprite = (Sprite *)((i8 *)&war_icon_sprite_block.shield_icon_sprite);
          shield_x = icon_x;
          if ((((u32)((PictureWindow *)self)->list_top_index) + col_base + row & 1) == 0) {
            shield_x = panel_margin_x;
          }
          dim_b = row_y + row_height / 2;
          dim_a = sprite_get_height((Sprite *)((i8 *)&war_icon_sprite_block.shield_icon_sprite));
          sprite_draw
                    (icon_sprite,(iptr)shield_ctx,(iptr)&pedia_window_block.pedia_window,col_x + shield_x,dim_b - dim_a / 2);
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
          surface_fill_rect((DibSurface *)self,(iptr)&row_rect,fill_color_d);
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
          surface_fill_rect((DibSurface *)self,(iptr)&row_rect,fill_color_e);
        }
        icon_mode = 0;
        gfx_set_scale_ratio(scale_num2,scale_den2);
        text_clear();
        advance = ((u32)((PictureWindow *)self)->list_top_index) + col_base + row;
        switch(self->caption_height) {
        case 1:
          name_text = pedia_lookup_text(pedia_window_block.pedia_advance_names,advance);
          crt_strcpy(((i8 *)&map_views_block.text_buffer),name_text);
          break;
        case 2:
          name_text = pedia_lookup_text(pedia_window_block.pedia_improvement_names,advance);
          crt_strcpy(((i8 *)&map_views_block.text_buffer),name_text);
          break;
        case 3:
          name_text = pedia_lookup_text(pedia_window_block.pedia_wonder_names,advance);
          crt_strcpy(((i8 *)&map_views_block.text_buffer),name_text);
          break;
        case 4:
          name_text = pedia_lookup_text(pedia_window_block.pedia_unit_names,advance);
          crt_strcpy(((i8 *)&map_views_block.text_buffer),name_text);
          break;
        case 5:
          name_text = pedia_lookup_text(pedia_window_block.pedia_terrain_names,advance);
          crt_strcpy(((i8 *)&map_views_block.text_buffer),name_text);
          break;
        case 6:
          name_text = pedia_lookup_text(pedia_window_block.pedia_government_names,advance);
          crt_strcpy(((i8 *)&map_views_block.text_buffer),name_text);
          break;
        case 7:
          name_text = pedia_lookup_text(pedia_window_block.pedia_concept_names,advance);
          crt_strcpy(((i8 *)&map_views_block.text_buffer),name_text);
          break;
        default:
          text_append((const char *)&str_this_should_never_be_seen);
        }
        surface_set_clip((DibSurface *)self,&row_rect);
        if (shadow_color2 != text_color2) {
          gfx_set_text_color_index(shadow_color2);
          surface_draw_text
                    ((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,text_x_off + col_x + 2,
                     text_y_off + row_y + 1,5);
          gfx_set_text_color_index(text_color2);
          surface_draw_text
                    ((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,text_x_off + col_x + 1,
                     text_y_off + row_y,5);
        }
        gfx_set_text_color_index(text_color2);
        surface_draw_text
                  ((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,text_x_off + col_x,
                   text_y_off + row_y,5);
        surface_set_clip((DibSurface *)self,(RECT *)(iptr)((u8 *)&((PictureWindow *)self)->list_rect));
      }
    }
    col_x = (int)((PictureWindow *)self)->list_rect + (col + 1) * col_width;
    col++;
  } while( true );
}

/* 004f7313 auto */
void __cdecl pedia_list_on_scroll(int scroll_pos)

{
  if (pedia_window_block.pedia_list_top != scroll_pos * 9) {
    pedia_window_block.pedia_list_top = scroll_pos * 9;
    pedia_draw_item_list((ListPaneWindow *)((i8 *)&pedia_window_block.pedia_window));
  }
  return;
}

/* 004f734a auto */
int __cdecl pedia_list_hit_test(int x,int y)

{
  int dim;
  int result;
  uint column;
  
  if (y < pedia_window_block.pedia_list_rect_top) {
    result = -1;
  }
  else if (y < pedia_window_block.pedia_list_rect_bottom) {
    if (x < pedia_window_block.pedia_list_rect) {
      result = -3;
    }
    else if (x < pedia_window_block.pedia_list_rect_right) {
      dim = rect_width((RECT *)&pedia_window_block.pedia_list_rect);
      column = (uint)(pedia_window_block.pedia_list_rect + dim / 2 <= x);
      dim = rect_height((RECT *)&pedia_window_block.pedia_list_rect);
      result = (y - pedia_window_block.pedia_list_rect_top) / (dim / 9) + column * 9 + pedia_window_block.pedia_list_top;
      if (pedia_window_block.pedia_list_count <= result) {
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

/* 004f7454 auto */
void __thiscall pedia_scroll_to_item(WindowObjectView *self,int item)

{
  if (item < pedia_window_block.pedia_list_top) {
    for (pedia_window_block.pedia_list_top = item; pedia_window_block.pedia_list_top % 9 != 0; pedia_window_block.pedia_list_top--) {
    }
  }
  else if (pedia_window_block.pedia_list_top + 0x12 <= item) {
    for (pedia_window_block.pedia_list_top = item; pedia_window_block.pedia_list_top % 9 != 0; pedia_window_block.pedia_list_top--) {
    }
  }
  pedia_redraw((PediaRedrawView *)((i8 *)&pedia_window_block.pedia_window));
  return;
}

/* 004f74eb auto */
int __cdecl pedia_find_item_by_key(int key)

{
  int first_char;
  int remaining;
  PediaListNode *list_head;
  int index;
  PediaListNode *node2;
  
  switch(pedia_window_block.pedia_category) {
  case 1:
    list_head = pedia_window_block.pedia_advance_names;
    remaining = pedia_window_block.pedia_advance_entry_count;
    break;
  case 2:
    list_head = pedia_window_block.pedia_improvement_names;
    remaining = pedia_window_block.pedia_improvement_entry_count;
    break;
  case 3:
    list_head = pedia_window_block.pedia_wonder_names;
    remaining = pedia_window_block.pedia_wonder_entry_count;
    break;
  case 4:
    list_head = pedia_window_block.pedia_unit_names;
    remaining = pedia_window_block.pedia_unit_entry_count;
    break;
  case 5:
    list_head = pedia_window_block.pedia_terrain_names;
    remaining = pedia_window_block.pedia_terrain_count;
    break;
  case 6:
    list_head = pedia_window_block.pedia_government_names;
    remaining = pedia_window_block.pedia_government_entry_count;
    break;
  case 7:
    list_head = pedia_window_block.pedia_concept_names;
    remaining = pedia_window_block.pedia_concept_entry_count;
    break;
  default:
    return 0xffffffff;
  }
  node2 = list_head;
  index = pedia_window_block.pedia_selected_item + 1;
  if (pedia_window_block.pedia_list_count <= index) {
    index = 0;
  }
  for (; index != 0; index--) {
    if (node2->next == 0) {
      node2 = list_head;
    }
    else {
      node2 = node2->next;
    }
  }
  index = pedia_window_block.pedia_selected_item + 1;
  if (pedia_window_block.pedia_list_count <= index) {
    index = 0;
  }
  while ((remaining != 0 && (first_char = crt_toupper((int)*node2->name), first_char != key))) {
    if (node2->next == 0) {
      node2 = list_head;
      index = 0;
    }
    else {
      node2 = node2->next;
      index++;
    }
    remaining--;
  }
  if (remaining == 0) {
    index = -1;
  }
  return index;
}

/* 004f76ce auto */
void __cdecl pedia_list_on_key(i32 key)

{
  int key_upper;
  int item;
  
  item = pedia_window_block.pedia_selected_item;
  if (pedia_window_block.pedia_page_mode == 0) {
    key_upper = crt_toupper(key);
    if ((key_upper < 0x41) || (0x5a < key_upper)) {
      switch(key_upper) {
      case 0xa1:
      case 199:
        pedia_window_block.pedia_topic = pedia_window_block.pedia_list_count - 1;
        for (pedia_window_block.pedia_list_top = pedia_window_block.pedia_topic; pedia_window_block.pedia_list_top % 9 != 0; pedia_window_block.pedia_list_top--) {
        }
        pedia_window_block.pedia_selected_item = pedia_window_block.pedia_topic;
        pedia_redraw((PediaRedrawView *)((i8 *)&pedia_window_block.pedia_window));
        scrollbar_set_pos((ClickControl *)((i8 *)&pedia_window_block.pedia_list_scrollbar),pedia_window_block.pedia_list_top / 9);
        break;
      case 0xa2:
      case 0xc1:
        item++;
        if (item < pedia_window_block.pedia_list_count) {
          pedia_window_block.pedia_topic = item;
          pedia_window_block.pedia_selected_item = item;
          pedia_scroll_to_item((WindowObjectView *)((i8 *)&pedia_window_block.pedia_window),item);
          scrollbar_set_pos((ClickControl *)((i8 *)&pedia_window_block.pedia_list_scrollbar),pedia_window_block.pedia_list_top / 9);
        }
        break;
      case 0xa3:
      case 0xa6:
      case 0xc3:
      case 0xc6:
        item += 9;
        if (item < pedia_window_block.pedia_list_count) {
          pedia_window_block.pedia_topic = item;
          pedia_window_block.pedia_selected_item = item;
          pedia_scroll_to_item((WindowObjectView *)((i8 *)&pedia_window_block.pedia_window),item);
          scrollbar_set_pos((ClickControl *)((i8 *)&pedia_window_block.pedia_list_scrollbar),pedia_window_block.pedia_list_top / 9);
        }
        break;
      case 0xa4:
      case 0xa9:
      case 0xc2:
      case 0xc5:
        item -= 9;
        if (-1 < item) {
          pedia_window_block.pedia_topic = item;
          pedia_window_block.pedia_selected_item = item;
          pedia_scroll_to_item((WindowObjectView *)((i8 *)&pedia_window_block.pedia_window),item);
          scrollbar_set_pos((ClickControl *)((i8 *)&pedia_window_block.pedia_list_scrollbar),pedia_window_block.pedia_list_top / 9);
        }
        break;
      case 0xa7:
      case 0xc4:
        pedia_window_block.pedia_topic = 0;
        pedia_window_block.pedia_selected_item = 0;
        pedia_window_block.pedia_list_top = 0;
        scrollbar_set_pos((ClickControl *)((i8 *)&pedia_window_block.pedia_list_scrollbar),0);
        pedia_redraw((PediaRedrawView *)((i8 *)&pedia_window_block.pedia_window));
        break;
      case 0xa8:
      case 0xc0:
        item--;
        if (-1 < item) {
          pedia_window_block.pedia_topic = item;
          pedia_window_block.pedia_selected_item = item;
          pedia_scroll_to_item((WindowObjectView *)((i8 *)&pedia_window_block.pedia_window),item);
          scrollbar_set_pos((ClickControl *)((i8 *)&pedia_window_block.pedia_list_scrollbar),pedia_window_block.pedia_list_top / 9);
        }
        break;
      case 0xd0: ;
      }
    }
    else {
      item = pedia_find_item_by_key(key_upper);
      if (-1 < item) {
        pedia_window_block.pedia_topic = item;
        pedia_window_block.pedia_selected_item = item;
        pedia_scroll_to_item((WindowObjectView *)((i8 *)&pedia_window_block.pedia_window),item);
        scrollbar_set_pos((ClickControl *)((i8 *)&pedia_window_block.pedia_list_scrollbar),pedia_window_block.pedia_list_top / 9);
      }
    }
  }
  return;
}

/* 004f7a30 auto */
void __cdecl pedia_list_on_click(void)

{
  int hit_item;
  i32 cursor_y;
  i32 cursor_x;
  
  if ((((pedia_window_block.pedia_page_mode == 0) &&
       (wnd_get_cursor_pos
                  ((WndBase *)((i8 *)&pedia_window_block.pedia_window_wnd),(iptr)&cursor_x,(iptr)&cursor_y), pedia_window_block.pedia_list_count != 0)
       ) && (hit_item = pedia_list_hit_test(cursor_x,cursor_y), -1 < hit_item)) && (hit_item < pedia_window_block.pedia_list_count)) {
    pedia_window_block.pedia_topic = hit_item;
    pedia_window_block.pedia_selected_item = hit_item;
    pedia_redraw((PediaRedrawView *)((i8 *)&pedia_window_block.pedia_window));
  }
  return;
}

/* 004f7ac7 auto */
void __thiscall pedia_set_category_title(WindowObjectView *self,i32 category)

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
    text_append((const char *)&str_this_should_not_happen_3);
  }
  crt_strcpy((char *)(self + 0x186),((i8 *)&map_views_block.text_buffer));
  return;
}

/* 004f7bd1 auto */
void __thiscall pedia_open_category(MediaWindow *self,u32 category,int show)

{
  self->style_flags = 0;
  self->border_width = 0;
  self->resize_border = 0;
  self->caption_height = category;
  self->client_y = 0;
  pedia_back_topic = 0xffffffff;
  pedia_going_back = 0;
  pedia_set_category_title((WindowObjectView *)self,category);
  pedia_update_controls(self);
  self->caption_height = category;
  wnd_repaint((SurfaceWindow *)self);
  if (show != 0) {
    window_show((WindowObjectView *)self);
  }
  wnd_set_keyboard_nav((Wnd *)((i8 *)&pedia_window_block.pedia_window_wnd),0);
  wnd_activate((Wnd *)((i8 *)&pedia_window_block.pedia_window_wnd));
  pedia_history_push((ScaledWindowView *)((i8 *)&pedia_window_block.pedia_window));
  return;
}

/* 004f7c99 auto */
void __thiscall pedia_load_indexes(DocumentWindow *self)

{
  u8 *slot;
  bool reading;
  int status;
  char *name_str;
  size_t name_len;
  void *name_buf;
  char *name_text;
  iptr terrain_label;
  iptr improvement;
  int i;
  int sort_key;
  char line_prefix[3];
  PediaListNode *node2;
  PediaListNode *prev_node2;
  
  for (i = 0; i < 100; i++) {
    slot = self->advance_sort_keys + i * 4;
    slot[0] = 0xff;
    slot[1] = 0xff;
    slot[2] = 0xff;
    slot[3] = 0xff;
  }
  for (i = 0; i < 0x27; i++) {
    slot = self->improvement_sort_keys + i * 4;
    slot[0] = 0xff;
    slot[1] = 0xff;
    slot[2] = 0xff;
    slot[3] = 0xff;
  }
  for (i = 0; i < 0x1c; i++) {
    slot = ((PictureWindow *)self)->wonder_sort_keys_view + i * 4 + 0x4c;
    slot[0] = 0xff;
    slot[1] = 0xff;
    slot[2] = 0xff;
    slot[3] = 0xff;
  }
  for (i = 0; i < 0x3e; i++) {
    slot = ((PictureWindow *)self)->unit_key_slots + i * 4 + 0x1c;
    slot[0] = 0xff;
    slot[1] = 0xff;
    slot[2] = 0xff;
    slot[3] = 0xff;
  }
  for (i = 0; i < 7; i++) {
    slot = ((PictureWindow *)self)->government_key_slots + i * 4 + 8;
    slot[0] = 0xff;
    slot[1] = 0xff;
    slot[2] = 0xff;
    slot[3] = 0xff;
  }
  for (i = 0; i < 0x21; i++) {
    slot = ((PictureWindow *)self)->terrain_key_slots + i * 4 - 0x18;
    slot[0] = 0xff;
    slot[1] = 0xff;
    slot[2] = 0xff;
    slot[3] = 0xff;
  }
  for (i = 0; i < 0x100; i++) {
    slot = ((PictureWindow *)self)->concept_key_slots + i * 4 + 0x10;
    slot[0] = 0xff;
    slot[1] = 0xff;
    slot[2] = 0xff;
    slot[3] = 0xff;
  }
  pedia_free_lists((WindowObjectView *)self);
  status = text_open_section((const char *)&str_describe_3,(const char *)&str_advance_index_2);
  if (status == 0) {
    text_read_line(1);
    sort_key = text_next_int();
    self->pedia_advance_count = 0;
    improvement = 0;
    while (sort_key != -2) {
      if (advances[improvement].enabled != '\0') {
        ((PictureWindow *)self)->pedia_advance_keys[self->pedia_advance_count] = sort_key;
        ((PictureWindow *)self)->pedia_advance_ids[self->pedia_advance_count] = improvement;
        node2 = (PediaListNode *)operator_new(0xc);
        node2->index = self->pedia_advance_count;
        if (((PictureWindow *)self)->pedia_advance_names == (PediaListNode *)0x0) {
          ((PictureWindow *)self)->pedia_advance_names = node2;
        }
        else {
          prev_node2->next = node2;
        }
        node2->next = 0;
        name_str = label_string(advances[improvement].name);
        name_len = _strlen(name_str);
        name_buf = operator_new(name_len + 1);
        node2->name = (char *)name_buf;
        name_text = label_string(advances[improvement].name);
        crt_strcpy((char *)((void *)node2->name),name_text);
        prev_node2 = node2;
        self->pedia_advance_count++;
      }
      improvement++;
      text_read_line(1);
      sort_key = text_next_int();
    }
    text_close_file();
    if (((PictureWindow *)self)->pedia_advance_names != (PediaListNode *)0x0) {
      pedia_sort_list(self,((PictureWindow *)self)->pedia_advance_names,((PictureWindow *)self)->pedia_advance_keys,((PictureWindow *)self)->pedia_advance_ids,
                         self->pedia_advance_count);
    }
  }
  status = text_open_section((const char *)&str_describe_3,(const char *)&str_improvement_index_2);
  if (status == 0) {
    text_read_line(1);
    text_read_line(1);
    sort_key = text_next_int();
    self->pedia_improve_count = 0;
    improvement = 1;
    while (sort_key != -2) {
      if (-2 < improvements[improvement].preq) {
        ((PictureWindow *)self)->pedia_improve_keys[self->pedia_improve_count] = sort_key;
        ((PictureWindow *)self)->pedia_improve_ids[self->pedia_improve_count] = improvement;
        node2 = (PediaListNode *)operator_new(0xc);
        node2->index = self->pedia_improve_count;
        if (((PictureWindow *)self)->pedia_improve_names == (PediaListNode *)0x0) {
          ((PictureWindow *)self)->pedia_improve_names = node2;
        }
        else {
          prev_node2->next = node2;
        }
        node2->next = 0;
        name_str = label_string(improvements[improvement].name);
        name_len = _strlen(name_str);
        name_buf = operator_new(name_len + 1);
        node2->name = (char *)name_buf;
        name_text = label_string(improvements[improvement].name);
        crt_strcpy((char *)((void *)node2->name),name_text);
        prev_node2 = node2;
        self->pedia_improve_count++;
      }
      improvement++;
      text_read_line(1);
      sort_key = text_next_int();
    }
    text_close_file();
    if (((PictureWindow *)self)->pedia_improve_names != (PediaListNode *)0x0) {
      pedia_sort_list(self,((PictureWindow *)self)->pedia_improve_names,((PictureWindow *)self)->pedia_improve_keys,((PictureWindow *)self)->pedia_improve_ids,
                         self->pedia_improve_count);
    }
  }
  status = text_open_section((const char *)&str_describe_3,(const char *)&str_wonder_index_2);
  if (status == 0) {
    text_read_line(1);
    sort_key = text_next_int();
    ((PictureWindow *)self)->pedia_wonder_count = 0;
    improvement = 0x27;
    while (sort_key != -2) {
      if (-2 < improvements[improvement].preq) {
        ((PictureWindow *)self)->pedia_wonder_keys[((PictureWindow *)self)->pedia_wonder_count] = sort_key;
        ((PictureWindow *)self)->pedia_wonder_ids[((PictureWindow *)self)->pedia_wonder_count] = improvement;
        node2 = (PediaListNode *)operator_new(0xc);
        node2->index = ((PictureWindow *)self)->pedia_wonder_count;
        if (((PictureWindow *)self)->pedia_wonder_names == (PediaListNode *)0x0) {
          ((PictureWindow *)self)->pedia_wonder_names = node2;
        }
        else {
          prev_node2->next = node2;
        }
        node2->next = 0;
        name_str = label_string(improvements[improvement].name);
        name_len = _strlen(name_str);
        name_buf = operator_new(name_len + 1);
        node2->name = (char *)name_buf;
        name_text = label_string(improvements[improvement].name);
        crt_strcpy((char *)((void *)node2->name),name_text);
        prev_node2 = node2;
        ((PictureWindow *)self)->pedia_wonder_count = ((PictureWindow *)self)->pedia_wonder_count + 1;
      }
      improvement++;
      text_read_line(1);
      sort_key = text_next_int();
    }
    text_close_file();
    if (((PictureWindow *)self)->pedia_wonder_names != (PediaListNode *)0x0) {
      pedia_sort_list(self,((PictureWindow *)self)->pedia_wonder_names,((PictureWindow *)self)->pedia_wonder_keys,((PictureWindow *)self)->pedia_wonder_ids,
                         ((PictureWindow *)self)->pedia_wonder_count);
    }
  }
  status = text_open_section((const char *)&str_describe_3,(const char *)&str_unit_index_2);
  if (status == 0) {
    text_read_line(1);
    sort_key = text_next_int();
    ((PictureWindow *)self)->pedia_unit_count = 0;
    improvement = 0;
    while (sort_key != -2) {
      if (-2 < unit_types[improvement].prerequisite) {
        ((PictureWindow *)self)->pedia_unit_keys[((PictureWindow *)self)->pedia_unit_count] = sort_key;
        ((PictureWindow *)self)->pedia_unit_ids[((PictureWindow *)self)->pedia_unit_count] = improvement;
        node2 = (PediaListNode *)operator_new(0xc);
        node2->index = ((PictureWindow *)self)->pedia_unit_count;
        if (((PictureWindow *)self)->pedia_unit_names == (PediaListNode *)0x0) {
          ((PictureWindow *)self)->pedia_unit_names = node2;
        }
        else {
          prev_node2->next = node2;
        }
        node2->next = 0;
        name_str = label_string(unit_types[improvement].name);
        name_len = _strlen(name_str);
        name_buf = operator_new(name_len + 1);
        node2->name = (char *)name_buf;
        name_text = label_string(unit_types[improvement].name);
        crt_strcpy((char *)((void *)node2->name),name_text);
        prev_node2 = node2;
        ((PictureWindow *)self)->pedia_unit_count = ((PictureWindow *)self)->pedia_unit_count + 1;
      }
      improvement++;
      text_read_line(1);
      sort_key = text_next_int();
    }
    text_close_file();
    if (((PictureWindow *)self)->pedia_unit_names != (PediaListNode *)0x0) {
      pedia_sort_list(self,((PictureWindow *)self)->pedia_unit_names,((PictureWindow *)self)->pedia_unit_keys,((PictureWindow *)self)->pedia_unit_ids,((PictureWindow *)self)->pedia_unit_count);
    }
  }
  status = text_open_section((const char *)&str_describe_3,(const char *)&str_government_index_2);
  if (status == 0) {
    text_read_line(1);
    sort_key = text_next_int();
    ((PictureWindow *)self)->pedia_government_count = 0;
    improvement = 0;
    while (sort_key != -2) {
      ((PictureWindow *)self)->pedia_government_keys[((PictureWindow *)self)->pedia_government_count] = sort_key;
      ((PictureWindow *)self)->pedia_government_ids[((PictureWindow *)self)->pedia_government_count] = improvement;
      node2 = (PediaListNode *)operator_new(0xc);
      node2->index = ((PictureWindow *)self)->pedia_government_count;
      if (((PictureWindow *)self)->pedia_government_names == (PediaListNode *)0x0) {
        ((PictureWindow *)self)->pedia_government_names = node2;
      }
      else {
        prev_node2->next = node2;
      }
      node2->next = 0;
      name_str = label_string(government_names[improvement]);
      name_len = _strlen(name_str);
      name_buf = operator_new(name_len + 1);
      node2->name = (char *)name_buf;
      name_text = label_string(government_names[improvement]);
      crt_strcpy((char *)((void *)node2->name),name_text);
      prev_node2 = node2;
      ((PictureWindow *)self)->pedia_government_count = ((PictureWindow *)self)->pedia_government_count + 1;
      improvement++;
      text_read_line(1);
      sort_key = text_next_int();
    }
    text_close_file();
    if (((PictureWindow *)self)->pedia_government_names != (PediaListNode *)0x0) {
      pedia_sort_list(self,((PictureWindow *)self)->pedia_government_names,((PictureWindow *)self)->pedia_government_keys,((PictureWindow *)self)->pedia_government_ids,((PictureWindow *)self)->pedia_government_count);
    }
  }
  status = text_open_section((const char *)&str_describe_3,(const char *)&str_terrain_index_2);
  if (status == 0) {
    text_read_line(1);
    sort_key = text_next_int();
    ((PictureWindow *)self)->pedia_terrain_count_2 = 0;
    improvement = 0;
    while (sort_key != -2) {
      if (improvement != 0x18) {
        ((PictureWindow *)self)->pedia_terrain_keys[((PictureWindow *)self)->pedia_terrain_count_2] = sort_key;
        ((PictureWindow *)self)->pedia_terrain_ids[((PictureWindow *)self)->pedia_terrain_count_2] = improvement;
        node2 = (PediaListNode *)operator_new(0xc);
        node2->index = ((PictureWindow *)self)->pedia_terrain_count_2;
        if (((PictureWindow *)self)->pedia_terrain_names == (PediaListNode *)0x0) {
          ((PictureWindow *)self)->pedia_terrain_names = node2;
        }
        else {
          prev_node2->next = node2;
        }
        node2->next = 0;
        text_clear();
        terrain_label = (iptr)label_string(terrain_types[improvement].name);
        text_append((const char *)terrain_label);
        if ((0xc < improvement) &&
           (status = _strcmp(terrain_types[improvement].abbrev,((i8 *)&pedia_grassland_shield_abbrev_str)), status == 0)) {
          text_append_space();
          name_text = label_string(label_string_ids[0x2c0]);
          crt_strcat(((i8 *)&map_views_block.text_buffer),name_text);
        }
        name_len = _strlen(((i8 *)&map_views_block.text_buffer));
        name_buf = operator_new(name_len + 1);
        node2->name = (char *)name_buf;
        crt_strcpy((char *)((void *)node2->name),((i8 *)&map_views_block.text_buffer));
        prev_node2 = node2;
        ((PictureWindow *)self)->pedia_terrain_count_2++;
      }
      improvement++;
      text_read_line(1);
      sort_key = text_next_int();
    }
    text_close_file();
    if (((PictureWindow *)self)->pedia_terrain_names != (PediaListNode *)0x0) {
      pedia_sort_list(self,((PictureWindow *)self)->pedia_terrain_names,((PictureWindow *)self)->pedia_terrain_keys,((PictureWindow *)self)->pedia_terrain_ids,((PictureWindow *)self)->pedia_terrain_count_2);
    }
  }
  status = text_open_section((const char *)&str_describe_3,(const char *)&str_concept_descriptions_2);
  if (status == 0) {
    reading = true;
    ((PictureWindow *)self)->pedia_concept_count = 0;
    line_prefix[2] = 0;
    improvement = 0;
    while (reading) {
      text_read_line(1);
      _strncpy(line_prefix,((i8 *)&map_views_block.text_buffer),2);
      status = _strcmp(line_prefix,((i8 *)&pedia_index_marker_str));
      if (status == 0) {
        ((PictureWindow *)self)->pedia_concept_keys[((PictureWindow *)self)->pedia_concept_count] =
             ((PictureWindow *)self)->pedia_concept_count;
        ((PictureWindow *)self)->pedia_concept_ids[((PictureWindow *)self)->pedia_concept_count] = improvement;
        node2 = (PediaListNode *)operator_new(0xc);
        node2->index = ((PictureWindow *)self)->pedia_concept_count;
        if (((PictureWindow *)self)->pedia_concept_names == (PediaListNode *)0x0) {
          ((PictureWindow *)self)->pedia_concept_names = node2;
        }
        else {
          prev_node2->next = node2;
        }
        node2->next = 0;
        name_len = _strlen(((i8 *)&map_views_block.text_buffer_plus2));
        name_buf = operator_new(name_len + 1);
        node2->name = (char *)name_buf;
        crt_strcpy((char *)((void *)node2->name),((i8 *)&map_views_block.text_buffer_plus2));
        prev_node2 = node2;
        improvement++;
        ((PictureWindow *)self)->pedia_concept_count = ((PictureWindow *)self)->pedia_concept_count + 1;
      }
      else if (line_prefix[0] == '@') {
        reading = false;
      }
    }
    if (((PictureWindow *)self)->pedia_concept_names != (PediaListNode *)0x0) {
      pedia_sort_list(self,((PictureWindow *)self)->pedia_concept_names,((PictureWindow *)self)->pedia_concept_keys,((PictureWindow *)self)->pedia_concept_ids,((PictureWindow *)self)->pedia_concept_count);
    }
  }
  return;
}

/* 004f896a auto */
void __thiscall pedia_sort_list(void *self,PediaListNode *list_head,i32 *keys,i32 *ids,iptr count)

{
  i32 swap_tmp;
  int cmp;
  int j;
  int i;
  PediaListNode *other_node;
  PediaListNode *node2;
  
  other_node = list_head;
  node2 = list_head;
  for (i = 0; i < count - 1; i++) {
    j = i;
    if (node2->next != 0) {
      other_node = node2->next;
    }
    while (j = j + 1, j < count) {
      cmp = _strcmp(node2->name,other_node->name);
      if (0 < cmp) {
        swap_tmp = keys[i];
        keys[i] = keys[j];
        keys[j] = swap_tmp;
        swap_tmp = ids[i];
        ids[i] = ids[j];
        ids[j] = swap_tmp;
        swap_tmp = (i32)node2->name;
        node2->name = other_node->name;
        other_node->name = (char *)swap_tmp;
      }
      if (other_node->next != 0) {
        other_node = other_node->next;
      }
    }
    if (node2->next != 0) {
      node2 = node2->next;
    }
  }
  return;
}

/* 004f8a9b auto */
i8 * __cdecl pedia_lookup_text(PediaListNode *list_head,iptr item_id)

{
  i8 *text;
  PediaListNode *node2;
  
  for (node2 = list_head; (node2 != (PediaListNode *)0x0 && (node2->index != item_id));
      node2 = node2->next) {
  }
  text = pedia_missing_text;
  if (node2 != (PediaListNode *)0x0) {
    text = node2->name;
  }
  return text;
}

/* 004f8af9 auto */
void __thiscall pedia_history_push(ScaledWindowView *self)

{
  if (((int)self->client_y < 99) && (pedia_going_back == 0)) {
    if (((self->client_y == 0) ||
        ((((u32)((PictureWindow *)self)->pedia_history_page_modes[self->client_y - 1] != self->border_width ||
          (((PictureWindow *)self)->pedia_history_page_modes[self->client_y - 1] != 0)) ||
         (((PictureWindow *)self)->pedia_history_categories[self->client_y - 1] == 8)))) || (self->caption_height == 8))
    {
      if (((self->client_y == 0) ||
          ((u32)((PictureWindow *)self)->pedia_history_categories[self->client_y - 1] != self->caption_height)) ||
         (((u32)((PictureWindow *)self)->pedia_history_page_modes[self->client_y - 1] != self->border_width ||
          ((u32)((PictureWindow *)self)->pedia_history_topics[pedia_window_block.pedia_history_count - 1] != self->resize_border)))) {
        if (-1 < pedia_back_topic) {
          ((PictureWindow *)self)->pedia_history_topics[self->client_y] = pedia_back_topic;
          ((PictureWindow *)self)->pedia_history_page_modes[self->client_y] = pedia_window_block.pedia_popped_page_mode;
          ((PictureWindow *)self)->pedia_history_categories[self->client_y] = pedia_window_block.pedia_popped_category;
          self->client_y++;
        }
        ((PictureWindow *)self)->pedia_history_topics[self->client_y] = self->resize_border;
        ((PictureWindow *)self)->pedia_history_page_modes[self->client_y] = self->border_width;
        ((PictureWindow *)self)->pedia_history_categories[self->client_y] = self->caption_height;
        self->client_y++;
      }
    }
    else {
      ((PictureWindow *)self)->pedia_history_topics[self->client_y - 1] = self->resize_border;
    }
  }
  pedia_back_topic = 0xffffffff;
  pedia_going_back = 0;
  return;
}

/* 004f8d04 auto */
void __cdecl pedia_modal_idle(void)

{
  net_process_messages(&net_session_block,1,0);
  if ((pedia_window_block.pedia_modal_active == 0) || (pedia_window_block.pedia_closed == 1)) {
    wnd_end_modal_loop((ModalMenuWindow *)((i8 *)&pedia_window_block.pedia_window_wnd));
    pedia_window_block.pedia_modal_active = 0;
  }
  return;
}

/* 004f8d51 auto */
void __cdecl pedia_end_modal(void)

{
  wnd_end_modal_loop((ModalMenuWindow *)((i8 *)&pedia_window_block.pedia_window_wnd));
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

void * __thiscall pedia_link_scalar_dtor(void *self,uint flags)

{
  pedia_link_dtor(self);
  if ((flags & 1) != 0) {
    operator_delete(self);
  }
  return self;
}

/* 004fa140 auto */
/* Library Function - Single Match
    public: __thiscall CControlBarInfo::~CControlBarInfo(void)
   
   Library: Visual Studio 1998 Debug */

void __thiscall pedia_link_dtor(void *self)

{
  i32 exc_link;
  i8 *seh_handler;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  /* inlined unwind funclet 004fa17e */ { hyperlink_dtor((HyperlinkDtorView *)(*(int *)&self + 4)); }
  return;
}

/* 00518f00 auto */
void __thiscall pedia_init_government_list(MediaWindow *self,iptr unused_arg)

{
  int i;
  
  if (((int)self->resize_border < 0) || ((int)((u32)((PictureWindow *)self)->pedia_government_count) <= (int)self->resize_border)) {
    self->resize_border = 0;
  }
  ((PictureWindow *)self)->list_count = ((u32)((PictureWindow *)self)->pedia_government_count);
  ((PictureWindow *)self)->list_selected_index = self->resize_border;
  ((PictureWindow *)self)->list_top_index = self->resize_border;
  while (pedia_window_block.pedia_list_top % 9 != 0) {
    ((PictureWindow *)self)->list_top_index = ((PictureWindow *)self)->list_top_index - 1;
  }
  for (i = 0; i < (int)((u32)((PictureWindow *)self)->pedia_government_count); i++) {
    ((PictureWindow *)self)->list_items[i] =
         ((PictureWindow *)self)->pedia_government_ids[i];
  }
  scrollbar_set_range
            ((Control *)&((PictureWindow *)self)->list_scrollbar,0,((PictureWindow *)self)->list_count / 9);
  scrollbar_set_pos
            ((ClickControl *)&((PictureWindow *)self)->list_scrollbar,((PictureWindow *)self)->list_top_index / 9);
  if (((PictureWindow *)self)->list_count < 1) {
    ((PictureWindow *)self)->list_top_index = -1;
  }
  pedia_update_controls(self);
  wnd_set_focus((WndBase *)((i8 *)&pedia_window_block.pedia_window_wnd));
  wnd_activate((Wnd *)((i8 *)&pedia_window_block.pedia_window_wnd));
  pedia_redraw((PediaRedrawView *)((i8 *)&pedia_window_block.pedia_window));
  return;
}

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
  dialog_ctor((Dialog *)((i8 *)&game_section_dialog_block.game_section_dialog),0x4000);
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
  dialog_dtor((Dialog *)((i8 *)&game_section_dialog_block.game_section_dialog));
  return;
}

/* 005261a0 auto */
void __thiscall pedia_init_wonder_list(MediaWindow *self,iptr unused_arg)

{
  int i;
  
  if (((int)self->resize_border < 0) || ((int)((u32)((PictureWindow *)self)->pedia_wonder_count) <= (int)self->resize_border)) {
    self->resize_border = 0;
  }
  ((PictureWindow *)self)->list_count = ((u32)((PictureWindow *)self)->pedia_wonder_count);
  ((PictureWindow *)self)->list_selected_index = self->resize_border;
  ((PictureWindow *)self)->list_top_index = self->resize_border;
  while (pedia_window_block.pedia_list_top % 9 != 0) {
    ((PictureWindow *)self)->list_top_index = ((PictureWindow *)self)->list_top_index - 1;
  }
  for (i = 0; i < (int)((u32)((PictureWindow *)self)->pedia_wonder_count); i++) {
    ((PictureWindow *)self)->list_items[i] =
         ((PictureWindow *)self)->pedia_wonder_ids[i];
  }
  scrollbar_set_range
            ((Control *)&((PictureWindow *)self)->list_scrollbar,0,((PictureWindow *)self)->list_count / 9);
  scrollbar_set_pos
            ((ClickControl *)&((PictureWindow *)self)->list_scrollbar,((PictureWindow *)self)->list_top_index / 9);
  if (((PictureWindow *)self)->list_count < 1) {
    ((PictureWindow *)self)->list_top_index = -1;
  }
  pedia_update_controls(self);
  wnd_set_focus((WndBase *)((i8 *)&pedia_window_block.pedia_window_wnd));
  wnd_activate((Wnd *)((i8 *)&pedia_window_block.pedia_window_wnd));
  pedia_redraw((PediaRedrawView *)((i8 *)&pedia_window_block.pedia_window));
  return;
}

/* 0052630d auto */
/* WARNING: Removing unreachable block (ram,0x0052661a) */

void __thiscall pedia_draw_improvement(DocumentWindow *self)

{
  int measure;
  iptr label;
  size_t text_len;
  int center_y;
  u32 yBottom;
  i8 shield_ctx[16];
  i8 icon_ctx[16];
  iptr improvement;
  tagRECT text_rect;
  int line_height;
  int icon_width;
  i32 scale_num2;
  int y2;
  i32 scale_den2;
  int x2;
  int content_width2;
  int value_x;
  i32 unused_flag;
  tagRECT link_rect;
  int text_width;
  int row_height;
  i8 saved_clip[16];
  GameFont *font2;
  
  unused_flag = 0;
  surface_get_clip((DibSurface *)self,(RECT *)saved_clip);
  surface_set_clip((DibSurface *)self,(RECT *)&self->content_left);
  pedia_update_controls((MediaWindow *)self);
  pedia_fill_background((WindowObjectView *)self,(RECT *)&self->content_left,2);
  font2 = (GameFont *)((i8 *)&font_size21);
  x2 = self->content_left + 10;
  content_width2 = rect_width((RECT *)&self->content_left);
  row_height = font_cached_height(font2);
  y2 = self->content_top + 8;
  value_x = content_width2 / 2 - 100;
  improvement = ((PictureWindow *)self)->pedia_wonder_ids[self->resize_border];
  gfx_get_scale_ratio((iptr)&scale_num2,(iptr)&scale_den2);
  gfx_set_scale_ratio(2,1);
  icon_width = sprite_get_width((Sprite *)(((i8 *)&caption_close_button_sprite_block.improvement_icon_sprites) + improvement * 0x3c));
  icon_width += panel_margin_x * 2;
  sprite_draw
            ((Sprite *)(((i8 *)&caption_close_button_sprite_block.improvement_icon_sprites) + improvement * 0x3c),(iptr)icon_ctx,(iptr)&pedia_window_block.pedia_window,x2,
             y2);
  gfx_set_scale_ratio(scale_num2,scale_den2);
  gfx_set_text_color_index(list_text_color);
  x2 = self->content_left + 10;
  measure = sprite_height((Sprite *)(((i8 *)&caption_close_button_sprite_block.improvement_icon_sprites) + improvement * 0x3c));
  y2 = y2 + measure * 2 + 5;
  text_clear();
  text_append_label(0x79);
  text_append_colon();
  surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
  measure = font_text_width(font2,(const char *)&map_views_block.text_buffer);
  x2 = x2 + measure + 5;
  text_clear();
  if (improvements[improvement].preq < '\0') {
    text_append_label(0xe);
    surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
  }
  else {
    text_append_string_id(advances[improvements[improvement].preq].name);
    text_width = font_text_width(font2,(const char *)&map_views_block.text_buffer);
    line_height = font_line_spacing(font2);
    SetRect(&link_rect,x2,y2,x2 + text_width + 5,y2 + line_height);
    pedia_add_link(self,(int)improvements[improvement].preq,x2,y2,0,link_rect.left,
                       link_rect.top,link_rect.right,link_rect.bottom);
  }
  value_x = x2;
  x2 = self->content_left + 10;
  y2 += row_height;
  text_clear();
  text_append_label(0x84);
  text_append_colon();
  surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
  text_clear();
  _sprintf(((i8 *)&map_views_block.text_buffer),((i8 *)&pedia_improvement_cost_fmt),(uint)improvements[improvement].cost * 10);
  surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,value_x,y2,5);
  measure = font_text_width(font2,(const char *)&map_views_block.text_buffer);
  x2 = value_x + measure + 3;
  center_y = y2 + row_height / 2;
  measure = sprite_get_height((Sprite *)((i8 *)&war_icon_sprite_block.shield_icon_sprite));
  sprite_draw
            ((Sprite *)((i8 *)&war_icon_sprite_block.shield_icon_sprite),(iptr)shield_ctx,(iptr)&pedia_window_block.pedia_window,x2,center_y - measure / 2);
  x2 = self->content_left + 10;
  y2 += row_height;
  text_clear();
  text_append_label(0x9f);
  text_append_colon();
  surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
  text_clear();
  if (improvement < 0x17) {
    text_append_label(0xe);
    surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,value_x,y2,5);
  }
  else if (wonder_expires[improvement - 0x27] < 1) {
    text_append_label(0xe);
    surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,value_x,y2,5);
  }
  else {
    label = (iptr)label_string(advances[wonder_expires[improvement - 0x27]].name);
    text_append((const char *)label);
    text_width = font_text_width(font2,(const char *)&map_views_block.text_buffer);
    line_height = font_line_spacing(font2);
    SetRect(&link_rect,value_x,y2,value_x + text_width + 5,y2 + line_height);
    pedia_add_link(self,(int)wonder_expires[improvement - 0x27],value_x,y2,0,link_rect.left,
                       link_rect.top,link_rect.right,link_rect.bottom);
  }
  x2 = self->content_left + 10;
  y2 += row_height * 2;
  pedia_load_improvement_text((WindowObjectView *)self,improvement);
  text_len = _strlen(((i8 *)&map_views_block.text_buffer));
  if (text_len != 0) {
    yBottom = self->content_bottom;
    measure = rect_width((RECT *)&self->content_left);
    SetRect(&text_rect,x2,y2,measure - 10 + x2,yBottom);
    surface_draw_text_rect((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,(iptr)&text_rect,5);
  }
  pedia_update_describe_button((ListPaneWindow *)self,self->resize_border);
  surface_set_clip((DibSurface *)self,(RECT *)saved_clip);
  wnd_blit_surface_rect((DibSurface *)self,(iptr)&self->content_left);
  return;
}

/* 00526913 auto */
void __thiscall pedia_show_wonder_modal(DocumentWindow *self,int wonder_id)

{
  char *name_text;
  u32 wonder_idx;
  
  if ((pedia_window_block.pedia_closed != 0) && (net_session_block.map_redraw_busy == 0)) {
    for (wonder_idx = 0;
        ((int)wonder_idx < ((PictureWindow *)self)->pedia_wonder_count &&
        (((PictureWindow *)self)->pedia_wonder_ids[wonder_idx] != wonder_id)); wonder_idx++) {
    }
    if ((u32)((PictureWindow *)self)->pedia_wonder_count != wonder_idx) {
      pedia_open_category((MediaWindow *)self,3,1);
      self->resize_border = wonder_idx;
      ((PictureWindow *)self)->list_selected_index = wonder_idx;
      self->client_x = 1;
      self->border_width = 1;
      pedia_clear_links((WindowObjectView *)self);
      pedia_update_controls((MediaWindow *)self);
      name_text = pedia_lookup_text(pedia_window_block.pedia_wonder_names,wonder_idx);
      crt_strcpy((char *)self->pedia_title_text_2,name_text);
      pedia_draw_frame((MediaWindow *)self);
      pedia_draw_improvement(self);
      wnd_blit_surface((DibSurface *)((i8 *)&pedia_window_block.pedia_window));
      wnd_activate((Wnd *)((i8 *)&pedia_window_block.pedia_window_wnd));
      wnd_set_modal_idle_callback((ModalMenuWindow *)((i8 *)&pedia_window_block.pedia_window_wnd),(iptr)pedia_modal_idle);
      wnd_run_modal_loop((ModalMenuWindow *)((i8 *)&pedia_window_block.pedia_window_wnd));
      wnd_set_modal_idle_callback((ModalMenuWindow *)((i8 *)&pedia_window_block.pedia_window_wnd),0);
    }
  }
  return;
}

/* 00564d00 auto */
void __thiscall pedia_init_advance_list(PediaAdvanceListView *self,iptr unused_arg)

{
  int i;
  
  if (((int)self->resize_border < 0) || ((int)self->pedia_advance_count <= (int)self->resize_border)) {
    self->resize_border = 0;
  }
  ((PictureWindow *)self)->list_count = self->pedia_advance_count;
  ((PictureWindow *)self)->list_selected_index = self->resize_border;
  ((PictureWindow *)self)->list_top_index = self->resize_border;
  while (pedia_window_block.pedia_list_top % 9 != 0) {
    ((PictureWindow *)self)->list_top_index = ((PictureWindow *)self)->list_top_index - 1;
  }
  for (i = 0; i < (int)self->pedia_advance_count; i++) {
    ((PictureWindow *)self)->list_items[i] =
         ((PictureWindow *)self)->pedia_advance_ids[i];
  }
  scrollbar_set_range
            ((Control *)((u8 *)&((PictureWindow *)self)->list_scrollbar),0,((PictureWindow *)self)->list_count / 9);
  scrollbar_set_pos
            ((ClickControl *)((u8 *)&((PictureWindow *)self)->list_scrollbar),((PictureWindow *)self)->list_top_index / 9);
  if (((PictureWindow *)self)->list_count < 1) {
    ((PictureWindow *)self)->list_top_index = -1;
  }
  pedia_update_controls((MediaWindow *)self);
  wnd_set_focus((WndBase *)((i8 *)&pedia_window_block.pedia_window_wnd));
  wnd_activate((Wnd *)((i8 *)&pedia_window_block.pedia_window_wnd));
  pedia_redraw((PediaRedrawView *)((i8 *)&pedia_window_block.pedia_window));
  return;
}

/* 00564e6d auto */
void __thiscall pedia_draw_advance_page(DocumentWindow *self)

{
  int measure;
  iptr label;
  size_t rest_len;
  int center_y;
  bool was_right;
  i8 unit_ctx[16];
  i8 impr_ctx[16];
  i8 icon_ctx[16];
  iptr wonder;
  int is_child;
  iptr advance3;
  int prev_unit_height;
  iptr advance;
  char *pedia_file;
  iptr improvement;
  int line_height;
  iptr unit_type;
  int y2;
  u32 x2;
  char *line;
  iptr advance2;
  int unit_text_y;
  int has_pedia;
  tagRECT link_rect;
  int text_width;
  int related_count;
  char line_buf[260];
  int row_height;
  int list_x2;
  i8 saved_clip[16];
  GameFont *font2;
  uint in_right_col;
  
  surface_get_clip((DibSurface *)self,(RECT *)saved_clip);
  surface_set_clip((DibSurface *)self,(RECT *)&self->content_left);
  pedia_update_controls((MediaWindow *)self);
  pedia_fill_background((WindowObjectView *)self,(RECT *)&self->content_left,2);
  font2 = (GameFont *)((i8 *)&font_size21);
  x2 = self->content_left;
  row_height = font_cached_height((GameFont *)((i8 *)&font_size21));
  y2 = self->content_top + 5;
  advance = ((PictureWindow *)self)->pedia_advance_ids[self->resize_border];
  sprite_draw
            ((Sprite *)
             (((i8 *)&government_sprites_block.advance_category_icon_sprites) +
             (char)advances[advance].epoch * 0x3c + (char)advances[advance].category * 0xf0),
             (iptr)icon_ctx,(iptr)&pedia_window_block.pedia_window,panel_margin_x + x2,y2);
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
  x2 = self->content_left + 0x32;
  text_clear();
  text_append_label(0x79);
  text_append_colon();
  surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
  measure = font_text_width(font2,(const char *)&map_views_block.text_buffer);
  x2 = x2 + measure + 5;
  text_clear();
  if ((advances[advance].preq[0] < '\0') && (advances[advance].preq[1] < '\0')) {
    text_append_label(0xe);
    surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
  }
  else {
    if (-1 < advances[advance].preq[0]) {
      text_append_string_id(advances[advances[advance].preq[0]].name);
      text_width = font_text_width(font2,(const char *)&map_views_block.text_buffer);
      line_height = font_line_spacing(font2);
      SetRect(&link_rect,x2,y2,text_width + x2 + 5,line_height + y2);
      pedia_add_link(self,(int)advances[advance].preq[0],x2,y2,0,link_rect.left,
                         link_rect.top,link_rect.right,link_rect.bottom);
    }
    if (-1 < advances[advance].preq[1]) {
      if (-1 < advances[advance].preq[0]) {
        x2 = x2 + text_width + 3;
        text_clear();
        text_append_comma();
        surface_draw_text
                  ((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
        text_width = font_text_width(font2,(const char *)&map_views_block.text_buffer);
        text_width += 4;
        x2 += text_width;
      }
      text_clear();
      text_append_string_id(advances[advances[advance].preq[1]].name);
      text_width = font_text_width(font2,(const char *)&map_views_block.text_buffer);
      line_height = font_line_spacing(font2);
      SetRect(&link_rect,x2,y2,text_width + x2 + 5,line_height + y2);
      pedia_add_link(self,(int)advances[advance].preq[1],x2,y2,0,link_rect.left,
                         link_rect.top,link_rect.right,link_rect.bottom);
    }
  }
  y2 += row_height;
  x2 = self->content_left + 2;
  text_clear();
  text_append_label(0x7a);
  text_append_colon();
  measure = font_text_width(font2,(const char *)&map_views_block.text_buffer);
  list_x2 = x2 + measure + 2;
  if (related_count != 0) {
    surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
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
      text_width = font_text_width(font2,(const char *)&map_views_block.text_buffer);
      line_height = font_line_spacing(font2);
      SetRect(&link_rect,x2,y2,text_width + x2 + 2,line_height + y2);
      pedia_add_link(self,advance2,x2,y2,0,link_rect.left,link_rect.top,
                         link_rect.right,link_rect.bottom);
      measure = font_text_width(font2,(const char *)&map_views_block.text_buffer);
      x2 = x2 + measure + 2;
      if (-1 < advance3) {
        text_clear();
        text_append_space();
        text_append_lparen();
        text_append_label(0x7b);
        text_append_space();
        surface_draw_text
                  ((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
        measure = font_text_width(font2,(const char *)&map_views_block.text_buffer);
        x2 = x2 + measure + 2;
        text_clear();
        text_append_string_id(advances[advance3].name);
        text_width = font_text_width(font2,(const char *)&map_views_block.text_buffer);
        line_height = font_line_spacing(font2);
        SetRect(&link_rect,x2,y2,text_width + x2 + 2,line_height + y2);
        pedia_add_link(self,advance3,x2,y2,0,link_rect.left,link_rect.top,
                           link_rect.right,link_rect.bottom);
        measure = font_text_width(font2,(const char *)&map_views_block.text_buffer);
        x2 = x2 + measure + 2;
        text_clear();
        text_append_rparen();
        surface_draw_text
                  ((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
      }
      y2 += row_height;
    }
  }
  in_right_col = 0;
  x2 = list_x2;
  for (improvement = 1; improvement < 0x43; improvement++) {
    if (improvements[improvement].preq == advance) {
      sprite_draw
                ((Sprite *)(((i8 *)&caption_close_button_sprite_block.improvement_icon_sprites) + improvement * 0x3c),(iptr)impr_ctx,(iptr)&pedia_window_block.pedia_window,
                 x2,y2);
      measure = sprite_get_width((Sprite *)(((i8 *)&caption_close_button_sprite_block.improvement_icon_sprites) + improvement * 0x3c))
      ;
      x2 = x2 + measure + 5;
      text_clear();
      text_append_string_id(improvements[improvement].name);
      text_width = font_text_width(font2,(const char *)&map_views_block.text_buffer);
      line_height = font_line_spacing(font2);
      if ((in_right_col == 0) &&
         (measure = rect_width((RECT *)&self->content_left),
         measure / 2 <= (int)(text_width + x2 + 5))) {
        measure = rect_width((RECT *)&self->content_left);
        text_width = (measure / 2 - 5) - x2;
      }
      SetRect(&link_rect,x2,y2,text_width + x2 + 5,line_height + y2);
      if (improvement < 0x27) {
        pedia_add_link(self,improvement,x2,y2,1,link_rect.left,link_rect.top,
                           link_rect.right,link_rect.bottom);
      }
      else {
        pedia_add_link(self,improvement,x2,y2,2,link_rect.left,link_rect.top,
                           link_rect.right,link_rect.bottom);
      }
      was_right = in_right_col != 0;
      if (was_right) {
        y2 += row_height;
        x2 = list_x2;
      }
      else {
        measure = rect_width((RECT *)&self->content_left);
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
                          ((Sprite *)(((i8 *)&pollution_sprite_block.unit_sprites) + unit_type * 0x3c));
        center_y = y2 + measure / 2;
        measure = sprite_get_height
                          ((Sprite *)(((i8 *)&pollution_sprite_block.unit_sprites) + unit_type * 0x3c));
        sprite_draw
                  ((Sprite *)(((i8 *)&pollution_sprite_block.unit_sprites) + unit_type * 0x3c),(iptr)unit_ctx,(iptr)&pedia_window_block.pedia_window,
                   x2,center_y - measure / 2);
        measure = sprite_width
                          ((Sprite *)(((i8 *)&pollution_sprite_block.unit_sprites) + unit_type * 0x3c));
        x2 = x2 + measure + 5;
        measure = sprite_height
                          ((Sprite *)(((i8 *)&pollution_sprite_block.unit_sprites) + unit_type * 0x3c));
        center_y = font_line_spacing(font2);
        unit_text_y = (measure / 2 - center_y / 2) + y2;
      }
      else {
        unit_text_y = y2;
      }
      text_clear();
      label = (iptr)label_string(unit_types[unit_type].name);
      text_append((const char *)label);
      text_width = font_text_width(font2,(const char *)&map_views_block.text_buffer);
      line_height = font_line_spacing(font2);
      SetRect(&link_rect,x2,unit_text_y,text_width + x2 + 5,line_height + unit_text_y);
      pedia_add_link(self,unit_type,x2,unit_text_y,3,link_rect.left,link_rect.top,
                         link_rect.right,link_rect.bottom);
      if (in_right_col == 0) {
        measure = rect_width((RECT *)&self->content_left);
        x2 = measure / 2;
        in_right_col = 1;
        prev_unit_height = sprite_get_height
                              ((Sprite *)(((i8 *)&pollution_sprite_block.unit_sprites) + unit_type * 0x3c));
      }
      else {
        x2 = list_x2;
        in_right_col = 0;
        if (related_count < 0xb) {
          measure = sprite_get_height
                            ((Sprite *)(((i8 *)&pollution_sprite_block.unit_sprites) + unit_type * 0x3c));
          if (measure < prev_unit_height) {
            y2 += prev_unit_height;
          }
          else {
            measure = sprite_get_height
                              ((Sprite *)(((i8 *)&pollution_sprite_block.unit_sprites) + unit_type * 0x3c));
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
    measure = sprite_get_height((Sprite *)(((i8 *)&pollution_sprite_block.unit_sprites) + unit_type * 0x3c));
    if (measure < prev_unit_height) {
      y2 += prev_unit_height;
    }
    else {
      measure = sprite_get_height((Sprite *)(((i8 *)&pollution_sprite_block.unit_sprites) + unit_type * 0x3c))
      ;
      y2 += measure;
    }
  }
  pedia_file = str_pedia_3;
  measure = _strcmp(((i8 *)&net_map_lock_slots_block.scenario_dir_path),((i8 *)&civ_saved_cursor_x_block.game_home_dir));
  if (measure != 0) {
    __chdir(((i8 *)&net_map_lock_slots_block.scenario_dir_path));
    crt_strcpy(line_buf,str_describe_4);
    crt_strcat(line_buf,((i8 *)&lang_file_ext));
    measure = file_exists((const char *)line_buf);
    if (measure == 0) {
      ctrl_disable((Control *)(((PictureWindow *)self)->advance_detail_describe_button));
      __chdir(((i8 *)&civ_saved_cursor_x_block.game_home_dir));
      return;
    }
    __chdir(((i8 *)&civ_saved_cursor_x_block.game_home_dir));
  }
  has_pedia = _strcmp(((i8 *)&net_map_lock_slots_block.scenario_dir_path),((i8 *)&civ_saved_cursor_x_block.game_home_dir));
  if (has_pedia != 0) {
    __chdir(((i8 *)&net_map_lock_slots_block.scenario_dir_path));
    crt_strcpy(line_buf,str_pedia_4);
    crt_strcat(line_buf,((i8 *)&lang_file_ext));
    measure = file_exists((const char *)line_buf);
    if (measure == 0) {
      has_pedia = 0;
    }
    __chdir(((i8 *)&civ_saved_cursor_x_block.game_home_dir));
  }
  str_clear((char *)line_buf);
  measure = text_open_section((const char *)pedia_file,(const char *)&str_pediacivfacts);
  if (measure == 0) {
    line = text_read_line(1);
    if ((has_pedia == 0) &&
       ((((advance == 0x36 || (advance == 0xf)) || (advance == 0x1f)) ||
        ((advance == 0x47 || (advance == 0x15)))))) {
      surface_draw_text
                ((DibSurface *)self,(iptr)font2,(const char *)(line + (*line == '^')),
                 x2,y2,5);
      y2 += row_height;
    }
    line = text_read_line(1);
    if ((has_pedia == 0) && (advance == 0x12)) {
      surface_draw_text
                ((DibSurface *)self,(iptr)font2,(const char *)(line + (*line == '^')),
                 x2,y2,5);
      y2 += row_height;
    }
    line = text_read_line(1);
    if ((has_pedia == 0) && (advance == 0x42)) {
      surface_draw_text
                ((DibSurface *)self,(iptr)font2,(const char *)(line + (*line == '^')),
                 x2,y2,5);
      y2 += row_height;
    }
    line = text_read_line(1);
    if ((has_pedia == 0) && (advance == 0x43)) {
      surface_draw_text
                ((DibSurface *)self,(iptr)font2,(const char *)(line + (*line == '^')),
                 x2,y2,5);
      y2 += row_height;
    }
    line = text_read_line(1);
    if ((has_pedia == 0) && (advance == 0x46)) {
      surface_draw_text
                ((DibSurface *)self,(iptr)font2,(const char *)(line + (*line == '^')),
                 x2,y2,5);
      y2 += row_height;
    }
    line = text_read_line(1);
    if ((has_pedia == 0) && (advance == 0x38)) {
      surface_draw_text
                ((DibSurface *)self,(iptr)font2,(const char *)(line + (*line == '^')),
                 x2,y2,5);
      y2 += row_height;
    }
    line = text_read_line(1);
    if ((has_pedia == 0) && (advance == 0x18)) {
      surface_draw_text
                ((DibSurface *)self,(iptr)font2,(const char *)(line + (*line == '^')),
                 x2,y2,5);
      y2 += row_height;
    }
    line = text_read_line(1);
    if ((has_pedia == 0) && (advance == 0x59)) {
      surface_draw_text
                ((DibSurface *)self,(iptr)font2,(const char *)(line + (*line == '^')),
                 x2,y2,5);
      y2 += row_height;
    }
    line = text_read_line(1);
    if ((has_pedia == 0) && (advance == 0x3b)) {
      surface_draw_text
                ((DibSurface *)self,(iptr)font2,(const char *)(line + (*line == '^')),
                 x2,y2,5);
      y2 += row_height;
    }
    line = text_read_line(1);
    if ((has_pedia == 0) && (advance == 0x20)) {
      surface_draw_text
                ((DibSurface *)self,(iptr)font2,(const char *)(line + (*line == '^')),
                 x2,y2,5);
      y2 += row_height;
    }
    line = text_read_line(1);
    if ((has_pedia == 0) && (advance == 0x3c)) {
      surface_draw_text
                ((DibSurface *)self,(iptr)font2,(const char *)(line + (*line == '^')),
                 x2,y2,5);
      y2 += row_height;
    }
    line = text_read_line(1);
    if ((has_pedia == 0) && (advance == 0xf)) {
      surface_draw_text
                ((DibSurface *)self,(iptr)font2,(const char *)(line + (*line == '^')),
                 x2,y2,5);
      y2 += row_height;
    }
    line = text_read_line(1);
    str_append_space((iptr)line);
    crt_strcpy(line_buf,line);
    if (line_buf[0] == '^') {
      rest_len = _strlen((line_buf + 1));
      crt_memmove(line_buf,(line_buf + 1),rest_len);
    }
    for (wonder = 0; wonder < 0x1c; wonder++) {
      if (wonder_expires[wonder] == advance) {
        surface_draw_text
                  ((DibSurface *)self,(iptr)font2,(const char *)line_buf,x2,y2,5);
        measure = font_text_width(font2,(const char *)line_buf);
        x2 += measure;
        text_clear();
        text_append_string_id(improvements[wonder + 0x27].name);
        text_width = font_text_width(font2,(const char *)&map_views_block.text_buffer);
        line_height = font_line_spacing(font2);
        SetRect(&link_rect,x2,y2,text_width + x2,line_height + y2);
        pedia_add_link(self,wonder + 0x27,x2,y2,2,link_rect.left,link_rect.top,
                           link_rect.right,link_rect.bottom);
        measure = font_text_width(font2,(const char *)&map_views_block.text_buffer);
        x2 = x2 + measure + 2;
        text_clear();
        text_append_period();
        surface_draw_text
                  ((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
        x2 = list_x2;
        y2 += row_height;
      }
    }
  }
  pedia_update_describe_button((ListPaneWindow *)self,self->resize_border);
  surface_set_clip((DibSurface *)self,(RECT *)saved_clip);
  wnd_blit_surface_rect((DibSurface *)self,(iptr)&self->content_left);
  return;
}

/* 00566584 auto */
void __thiscall pedia_show_topic_modal(DocumentWindow *self,iptr advance_id)

{
  char *name_text;
  u32 advance_idx;
  
  if ((pedia_window_block.pedia_closed != 0) && (net_session_block.map_redraw_busy == 0)) {
    advance_idx = 0;
    while (((int)advance_idx < (int)self->pedia_advance_count &&
           (((PictureWindow *)self)->pedia_advance_ids[advance_idx] != advance_id))) {
      advance_idx++;
    }
    if (self->pedia_advance_count != advance_idx) {
      pedia_open_category((MediaWindow *)self,1,0);
      self->resize_border = advance_idx;
      ((PictureWindow *)self)->list_selected_index = advance_idx;
      self->client_x = 1;
      self->border_width = 1;
      pedia_clear_links((WindowObjectView *)self);
      pedia_update_controls((MediaWindow *)self);
      name_text = pedia_lookup_text(pedia_window_block.pedia_advance_names,advance_idx);
      crt_strcpy((char *)self->pedia_title_text_2,name_text);
      pedia_draw_frame((MediaWindow *)self);
      pedia_draw_advance_page(self);
      window_show((WindowObjectView *)self);
      wnd_blit_surface((DibSurface *)((i8 *)&pedia_window_block.pedia_window));
      wnd_activate((Wnd *)((i8 *)&pedia_window_block.pedia_window_wnd));
      wnd_set_modal_idle_callback((ModalMenuWindow *)((i8 *)&pedia_window_block.pedia_window_wnd),(iptr)pedia_modal_idle);
      wnd_run_modal_loop((ModalMenuWindow *)((i8 *)&pedia_window_block.pedia_window_wnd));
      wnd_set_modal_idle_callback((ModalMenuWindow *)((i8 *)&pedia_window_block.pedia_window_wnd),0);
    }
  }
  return;
}

/* 005666da auto */
void __thiscall pedia_draw_advance_tree(DocumentWindow *self)

{
  int measure;
  int *icon_rect;
  int measure2;
  int icon_w;
  int gp_line_y;
  int grand_line_y;
  int parent_line_y;
  i8 gp_ctx[16];
  i8 grand_ctx[16];
  i8 parent_ctx[16];
  i8 root_ctx[16];
  iptr advance;
  int line_height;
  int tier2_anchor_y[8];
  Sprite *icon;
  int tier2_anchor_x[8];
  int tier3_step;
  iptr j;
  int y2;
  iptr i;
  int tier3_ids[8];
  int x2;
  int icon_width;
  int tier1_anchors[4];  /* y of the two tier-1 boxes' anchors */
  int root_anchor_y[2];
  int tier1_anchor_x[4];
  RECT icon_box;
  int root_anchor_x[3];
  tagRECT link_rect;
  int tier2_ids[4];
  i8 saved_clip[16];
  GameFont *font2;
  int parent_ids[2];
  
  surface_get_clip((DibSurface *)self,(RECT *)saved_clip);
  surface_set_clip((DibSurface *)self,(RECT *)&self->content_left);
  pedia_clear_links((WindowObjectView *)self);
  pedia_update_controls((MediaWindow *)self);
  pedia_fill_background((WindowObjectView *)self,(RECT *)&self->content_left,2);
  font2 = (GameFont *)((i8 *)&font_size21);
  advance = ((PictureWindow *)self)->pedia_advance_ids[self->resize_border];
  text_clear();
  text_append_string_id(advances[advance].name);
  root_anchor_x[2] = font_text_width(font2,(const char *)&map_views_block.text_buffer);
  line_height = font_line_spacing(font2);
  icon = (Sprite *)
             (((i8 *)&government_sprites_block.advance_category_icon_sprites) +
             (char)advances[advance].category * 0xf0 + (char)advances[advance].epoch * 0x3c);
  icon_width = sprite_get_width(icon);
  icon_width += 3;
  x2 = (self->content_right - 3) - (icon_width + root_anchor_x[2]);
  measure = rect_height((RECT *)&self->content_left);
  y2 = (self->content_top + measure / 2) - line_height / 2;
  icon_rect = (int *)sprite_draw(icon,(iptr)root_ctx,(iptr)&pedia_window_block.pedia_window,x2,y2);
  icon_box.left = *icon_rect;
  icon_box.top = icon_rect[1];
  icon_box.right = icon_rect[2];
  icon_box.bottom = icon_rect[3];
  x2 += icon_width;
  SetRect(&link_rect,x2 - icon_width,y2,root_anchor_x[2] + x2 + 5,line_height + y2);
  pedia_add_link(self,advance,x2,y2,0,link_rect.left,link_rect.top,link_rect.right,
                     link_rect.bottom);
  parent_ids[0] = (int)advances[advance].preq[0];
  parent_ids[1] = (int)advances[advance].preq[1];
  root_anchor_x[1] = icon_box.left;
  root_anchor_x[0] = icon_box.left;
  measure = rect_height(&icon_box);
  root_anchor_y[0] = icon_box.top + measure / 2;
  root_anchor_y[1] = root_anchor_y[0];
  line_height = font_line_spacing(font2);
  measure = rect_height((RECT *)&self->content_left);
  y2 = (self->content_top + ((int)(measure + (measure >> 0x1f & 3U)) >> 2)) - line_height / 2;
  for (i = 0; i < 2; i++) {
    tier2_ids[i * 2] = -1;
    tier2_ids[i * 2 + 1] = -1;
    if (-1 < parent_ids[i]) {
      text_clear();
      text_append_string_id(advances[parent_ids[i]].name);
      root_anchor_x[2] = font_text_width(font2,(const char *)&map_views_block.text_buffer);
      icon = (Sprite *)
                 (((i8 *)&government_sprites_block.advance_category_icon_sprites) +
                 (char)advances[parent_ids[i]].category * 0xf0 +
                 (char)advances[parent_ids[i]].epoch * 0x3c);
      icon_width = sprite_get_width(icon);
      icon_width += 3;
      measure = rect_width((RECT *)&self->content_left);
      measure2 = rect_width((RECT *)&self->content_left);
      x2 = ((int)(measure * 2 + (measure * 2 >> 0x1f & 3U)) >> 2) +
                 ((int)(measure2 + (measure2 >> 0x1f & 7U)) >> 3) + self->content_left;
      icon_rect = (int *)sprite_draw
                                (icon,(iptr)parent_ctx,(iptr)&pedia_window_block.pedia_window,x2,y2);
      icon_box.left = *icon_rect;
      icon_box.top = icon_rect[1];
      icon_box.right = icon_rect[2];
      parent_line_y = icon_rect[3];
      icon_box.bottom = parent_line_y;
      if (i != 0) {
        parent_line_y = icon_rect[1] - 1;
      }
      measure = root_anchor_y[i];
      measure2 = root_anchor_x[i];
      icon_w = rect_width(&icon_box);
      pedia_draw_tree_connector
                ((DibSurface *)self,icon_box.left + icon_w / 2,parent_line_y,measure2,measure);
      x2 += icon_width;
      tier2_ids[i * 2] = (int)advances[parent_ids[i]].preq[0];
      tier2_ids[i * 2 + 1] = (int)advances[parent_ids[i]].preq[1];
      tier1_anchor_x[i * 2 + 1] = icon_box.left;
      tier1_anchor_x[i * 2] = tier1_anchor_x[i * 2 + 1];
      measure = rect_height(&icon_box);
      tier1_anchors[i * 2 + 1] = icon_box.top + measure / 2;
      tier1_anchors[i * 2] = tier1_anchors[i * 2 + 1];
      SetRect(&link_rect,x2 - icon_width,y2,root_anchor_x[2] + x2 + 5,line_height + y2
             );
      pedia_add_link(self,parent_ids[i],x2,y2,0,link_rect.left,link_rect.top,
                         link_rect.right,link_rect.bottom);
    }
    measure = rect_height((RECT *)&self->content_left);
    y2 += measure / 2;
  }
  line_height = font_line_spacing(font2);
  measure = rect_height((RECT *)&self->content_left);
  y2 = (self->content_top + ((int)(measure + (measure >> 0x1f & 7U)) >> 3)) - line_height / 2;
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++) {
      tier3_ids[(i * 2 + j) * 2] = -1;
      tier3_ids[(i * 2 + j) * 2 + 1] = -1;
      if (-1 < tier2_ids[i * 2 + j]) {
        text_clear();
        text_append_string_id(advances[tier2_ids[i * 2 + j]].name);
        root_anchor_x[2] = font_text_width(font2,(const char *)&map_views_block.text_buffer);
        icon = (Sprite *)
                   (((i8 *)&government_sprites_block.advance_category_icon_sprites) +
                   (char)advances[tier2_ids[i * 2 + j]].epoch * 0x3c +
                   (char)advances[tier2_ids[i * 2 + j]].category * 0xf0);
        icon_width = sprite_get_width(icon);
        icon_width += 3;
        measure = rect_width((RECT *)&self->content_left);
        measure2 = rect_width((RECT *)&self->content_left);
        x2 = ((int)(measure + (measure >> 0x1f & 3U)) >> 2) +
                   ((int)(measure2 + (measure2 >> 0x1f & 7U)) >> 3) + self->content_left;
        icon_rect = (int *)sprite_draw
                                  (icon,(iptr)grand_ctx,(iptr)&pedia_window_block.pedia_window,x2,y2);
        icon_box.left = *icon_rect;
        icon_box.top = icon_rect[1];
        icon_box.right = icon_rect[2];
        grand_line_y = icon_rect[3];
        icon_box.bottom = grand_line_y;
        if (j != 0) {
          grand_line_y = icon_rect[1] - 1;
        }
        measure = tier1_anchors[i * 2 + j];
        measure2 = tier1_anchor_x[i * 2 + j];
        icon_w = rect_width(&icon_box);
        pedia_draw_tree_connector
                  ((DibSurface *)self,icon_box.left + icon_w / 2,grand_line_y,measure2,measure);
        x2 += icon_width;
        tier3_ids[(i * 2 + j) * 2] =
             (int)advances[tier2_ids[i * 2 + j]].preq[0];
        tier3_ids[(i * 2 + j) * 2 + 1] =
             (int)advances[tier2_ids[i * 2 + j]].preq[1];
        tier2_anchor_x[(i * 2 + j) * 2 + 1] = icon_box.left;
        tier2_anchor_x[(i * 2 + j) * 2] = tier2_anchor_x[(i * 2 + j) * 2 + 1];
        measure = rect_height(&icon_box);
        tier2_anchor_y[(i * 2 + j) * 2 + 1] = icon_box.top + measure / 2;
        tier2_anchor_y[(i * 2 + j) * 2] = tier2_anchor_y[(i * 2 + j) * 2 + 1];
        SetRect(&link_rect,x2 - icon_width,y2,root_anchor_x[2] + x2 + 5,
                line_height + y2);
        pedia_add_link(self,tier2_ids[i * 2 + j],x2,y2,0,
                           link_rect.left,link_rect.top,link_rect.right,link_rect.bottom);
      }
      measure = rect_height((RECT *)&self->content_left);
      y2 += ((int)(measure + (measure >> 0x1f & 3U)) >> 2);
    }
  }
  measure = rect_height((RECT *)&self->content_left);
  tier3_step = (int)(measure + (measure >> 0x1f & 7U)) >> 3;
  line_height = font_line_spacing(font2);
  x2 = self->content_left + 2;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 2; j++) {
      y2 = ((i * 2 + j) * tier3_step + self->content_top + tier3_step / 2) -
                 line_height / 2;
      if (-1 < tier3_ids[i * 2 + j]) {
        text_clear();
        text_append_string_id(advances[tier3_ids[i * 2 + j]].name);
        root_anchor_x[2] = font_text_width(font2,(const char *)&map_views_block.text_buffer);
        icon = (Sprite *)
                   (((i8 *)&government_sprites_block.advance_category_icon_sprites) +
                   (char)advances[tier3_ids[i * 2 + j]].category * 0xf0 +
                   (char)advances[tier3_ids[i * 2 + j]].epoch * 0x3c);
        icon_width = sprite_get_width(icon);
        icon_width += 3;
        icon_rect = (int *)sprite_draw
                                  (icon,(iptr)gp_ctx,(iptr)&pedia_window_block.pedia_window,x2,y2);
        icon_box.left = *icon_rect;
        icon_box.top = icon_rect[1];
        icon_box.right = icon_rect[2];
        gp_line_y = icon_rect[3];
        icon_box.bottom = gp_line_y;
        if (j != 0) {
          gp_line_y = icon_rect[1] - 1;
        }
        measure = tier2_anchor_y[i * 2 + j];
        measure2 = tier2_anchor_x[i * 2 + j];
        icon_w = rect_width(&icon_box);
        pedia_draw_tree_connector
                  ((DibSurface *)self,icon_box.left + icon_w / 2,gp_line_y,measure2,measure);
        if ((-1 < advances[tier3_ids[i * 2 + j]].preq[0]) ||
           (-1 < advances[tier3_ids[i * 2 + j]].preq[1])) {
          measure = rect_height(&icon_box);
          pedia_draw_tree_stub((MediaWindow *)self,icon_box.left,icon_box.top + measure / 2);
        }
        SetRect(&link_rect,x2,y2,icon_width + root_anchor_x[2] + x2 + 5,
                line_height + y2);
        pedia_add_link(self,tier3_ids[i * 2 + j],icon_width + x2,y2,0,
                           link_rect.left,link_rect.top,link_rect.right,link_rect.bottom);
      }
      measure = rect_height((RECT *)&self->content_left);
      y2 += ((int)(measure + (measure >> 0x1f & 7U)) >> 3);
    }
  }
  surface_set_clip((DibSurface *)self,(RECT *)saved_clip);
  wnd_blit_surface_rect((DibSurface *)self,(iptr)&self->content_left);
  return;
}

/* 005674b9 auto */
void __thiscall
pedia_draw_tree_connector(DibSurface *self,int x,int y_from,int x_to,int y_to)

{
  if (y_to < y_from) {
    y_from++;
  }
  else {
    y_from--;
  }
  gfx_set_text_color_index(10);
  surface_draw_line(self,x - 1,y_from,x - 1,y_to);
  surface_draw_line(self,x + 1,y_from,x + 1,y_to);
  gfx_set_text_color_index(0x7a);
  surface_draw_line(self,x,y_from,x,y_to);
  if (x < x_to) {
    gfx_set_text_color_index(10);
    surface_draw_line(self,x + 1,y_to - 1,x_to,y_to - 1);
    surface_draw_line(self,x + 1,y_to + 1,x_to,y_to + 1);
    gfx_set_text_color_index(0x7a);
    surface_draw_line(self,x + 1,y_to,x_to,y_to);
  }
  return;
}

/* 005675b7 auto */
void __thiscall pedia_draw_tree_stub(MediaWindow *self,i32 x,int y)

{
  gfx_set_text_color_index(10);
  surface_draw_line
            ((DibSurface *)self,x,y - 1,self->content_left,y - 1);
  surface_draw_line((DibSurface *)self,x,y + 1,self->content_left,y + 1)
  ;
  gfx_set_text_color_index(0x7a);
  surface_draw_line((DibSurface *)self,x,y,self->content_left,y);
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
  palette_init((GamePalette *)((i8 *)&art_palette));
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
  palette_destroy((GamePalette *)((i8 *)&art_palette));
  return;
}

/* 00599a20 auto */
void __thiscall pedia_init_improvement_list(DocumentWindow *self,iptr unused_arg)

{
  int i;
  
  if (((int)self->resize_border < 0) || ((int)self->pedia_improve_count <= (int)self->resize_border)) {
    self->resize_border = 0;
  }
  ((PictureWindow *)self)->list_count = self->pedia_improve_count;
  ((PictureWindow *)self)->list_selected_index = self->resize_border;
  ((PictureWindow *)self)->list_top_index = self->resize_border;
  while (pedia_window_block.pedia_list_top % 9 != 0) {
    ((PictureWindow *)self)->list_top_index = ((PictureWindow *)self)->list_top_index - 1;
  }
  for (i = 0; i < (int)self->pedia_improve_count; i++) {
    ((PictureWindow *)self)->list_items[i] =
         ((PictureWindow *)self)->pedia_improve_ids[i];
  }
  scrollbar_set_range
            ((Control *)((u8 *)&((PictureWindow *)self)->list_scrollbar),0,((PictureWindow *)self)->list_count / 9);
  scrollbar_set_pos
            ((ClickControl *)((u8 *)&((PictureWindow *)self)->list_scrollbar),((PictureWindow *)self)->list_top_index / 9);
  if (((PictureWindow *)self)->list_count < 1) {
    ((PictureWindow *)self)->list_top_index = -1;
  }
  pedia_update_controls((MediaWindow *)self);
  wnd_set_focus((WndBase *)((i8 *)&pedia_window_block.pedia_window_wnd));
  wnd_activate((Wnd *)((i8 *)&pedia_window_block.pedia_window_wnd));
  pedia_redraw((PediaRedrawView *)((i8 *)&pedia_window_block.pedia_window));
  return;
}

/* 00599b8d auto */
/* WARNING: Removing unreachable block (ram,0x00599e9a) */
/* WARNING: Removing unreachable block (ram,0x00599fc4) */

void __thiscall pedia_draw_improvement_page(DocumentWindow *self)

{
  int measure;
  size_t text_len;
  int center_y;
  u32 yBottom;
  i8 coin_ctx[16];
  i8 shield_ctx[16];
  i8 icon_ctx[16];
  iptr improvement;
  tagRECT text_rect;
  int line_height;
  int icon_width;
  i32 scale_num2;
  int y2;
  i32 scale_den2;
  int x2;
  int content_width2;
  int value_x;
  i32 unused_flag;
  tagRECT link_rect;
  int text_width;
  int row_height;
  i8 saved_clip[16];
  GameFont *font2;
  
  unused_flag = 0;
  surface_get_clip((DibSurface *)self,(RECT *)saved_clip);
  surface_set_clip((DibSurface *)self,(RECT *)&self->content_left);
  pedia_update_controls((MediaWindow *)self);
  pedia_fill_background((WindowObjectView *)self,(RECT *)&self->content_left,2);
  font2 = (GameFont *)((i8 *)&font_size21);
  x2 = self->content_left + 10;
  content_width2 = rect_width((RECT *)&self->content_left);
  row_height = font_cached_height(font2);
  y2 = self->content_top + 8;
  value_x = content_width2 / 2 - 100;
  improvement = ((PictureWindow *)self)->pedia_improve_ids[self->resize_border];
  gfx_get_scale_ratio((iptr)&scale_num2,(iptr)&scale_den2);
  gfx_set_scale_ratio(2,1);
  icon_width = sprite_get_width((Sprite *)(((i8 *)&caption_close_button_sprite_block.improvement_icon_sprites) + improvement * 0x3c));
  icon_width += panel_margin_x * 2;
  sprite_draw
            ((Sprite *)(((i8 *)&caption_close_button_sprite_block.improvement_icon_sprites) + improvement * 0x3c),(iptr)icon_ctx,(iptr)&pedia_window_block.pedia_window,x2,
             y2);
  gfx_set_scale_ratio(scale_num2,scale_den2);
  gfx_set_text_color_index(list_text_color);
  x2 = self->content_left + 10;
  measure = sprite_height((Sprite *)(((i8 *)&caption_close_button_sprite_block.improvement_icon_sprites) + improvement * 0x3c));
  y2 = y2 + measure * 2 + 5;
  text_clear();
  text_append_label(0x79);
  text_append_colon();
  surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
  measure = font_text_width(font2,(const char *)&map_views_block.text_buffer);
  x2 = x2 + measure + 5;
  text_clear();
  if (improvements[improvement].preq < '\0') {
    text_append_label(0xe);
    surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
  }
  else {
    text_append_string_id(advances[improvements[improvement].preq].name);
    text_width = font_text_width(font2,(const char *)&map_views_block.text_buffer);
    line_height = font_line_spacing(font2);
    SetRect(&link_rect,x2,y2,x2 + text_width + 5,y2 + line_height);
    pedia_add_link(self,(int)improvements[improvement].preq,x2,y2,0,link_rect.left,
                       link_rect.top,link_rect.right,link_rect.bottom);
  }
  value_x = x2;
  x2 = self->content_left + 10;
  y2 += row_height;
  text_clear();
  text_append_label(0x84);
  text_append_colon();
  surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
  text_clear();
  _sprintf(((i8 *)&map_views_block.text_buffer),((i8 *)&pedia_improve_cost_fmt),(uint)improvements[improvement].cost * 10);
  surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,value_x,y2,5);
  measure = font_text_width(font2,(const char *)&map_views_block.text_buffer);
  x2 = value_x + measure + 3;
  center_y = y2 + row_height / 2;
  measure = sprite_get_height((Sprite *)((i8 *)&war_icon_sprite_block.shield_icon_sprite));
  sprite_draw
            ((Sprite *)((i8 *)&war_icon_sprite_block.shield_icon_sprite),(iptr)shield_ctx,(iptr)&pedia_window_block.pedia_window,x2,center_y - measure / 2);
  x2 = self->content_left + 10;
  y2 += row_height;
  text_clear();
  text_append_label(0x9e);
  text_append_colon();
  surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
  text_clear();
  _sprintf(((i8 *)&map_views_block.text_buffer),((i8 *)&pedia_improve_upkeep_fmt),(uint)improvements[improvement].upkeep);
  surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,value_x,y2,5);
  measure = font_text_width(font2,(const char *)&map_views_block.text_buffer);
  x2 = value_x + measure + 3;
  center_y = y2 + row_height / 2;
  measure = sprite_get_height((Sprite *)((i8 *)&tax_rate_icon_sprites_block.gold_coin_icon_sprite));
  sprite_draw
            ((Sprite *)((i8 *)&tax_rate_icon_sprites_block.gold_coin_icon_sprite),(iptr)coin_ctx,(iptr)&pedia_window_block.pedia_window,x2,center_y - measure / 2);
  x2 = self->content_left + 10;
  y2 += row_height * 2;
  pedia_load_improvement_text((WindowObjectView *)self,improvement);
  text_len = _strlen(((i8 *)&map_views_block.text_buffer));
  if (text_len != 0) {
    yBottom = self->content_bottom;
    measure = rect_width((RECT *)&self->content_left);
    SetRect(&text_rect,x2,y2,measure - 10 + x2,yBottom);
    surface_draw_text_rect((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,(iptr)&text_rect,5);
  }
  pedia_update_describe_button((ListPaneWindow *)self,self->resize_border);
  surface_set_clip((DibSurface *)self,(RECT *)saved_clip);
  wnd_blit_surface_rect((DibSurface *)self,(iptr)&self->content_left);
  return;
}

/* 0059a15d auto */
void __thiscall pedia_load_improvement_text(WindowObjectView *self,iptr improvement_id)

{
  int status;
  char *_Str;
  size_t len;
  i32 ret_addr;
  char desc_buf[4096];
  i8 line_buf[256];
  i8 section_name[32];
  str_clear((char *)desc_buf);
  ret_addr = 0x59a190;
  crt_strcpy(section_name,str_pediaimprove_2);
  ret_addr = 0x59a1a0;
  str_append_int((iptr)section_name,improvement_id);
  ret_addr = 0x59a1b1;
  status = text_open_section((const char *)&str_pedia_5,(const char *)section_name);
  if (status == 0) {
    text_clear();
    while (_Str = text_read_line(1), *_Str != '@') {
      if ((*_Str != ';') && (len = _strlen(_Str), len != 0)) {
        while ((*_Str == '^' || (*_Str == '*'))) {
          ret_addr = 0x59a253;
          crt_strcpy(line_buf,_Str + 1);
          ret_addr = 0x59a269;
          crt_strcpy(_Str,line_buf);
        }
        str_trim(_Str);
        len = _strlen(desc_buf);
        if (len != 0) {
          ret_addr = 0x59a2a8;
          crt_strcat(desc_buf,((i8 *)&pedia_improve_text_space_str));
        }
        ret_addr = 0x59a2be;
        crt_strcat(desc_buf,_Str);
      }
    }
  }
  ret_addr = 0x59a2d7;
  crt_strcpy(((i8 *)&map_views_block.text_buffer),desc_buf);
  return;
}

/* 0059a2e6 auto */
void __thiscall pedia_show_improvement_modal(DocumentWindow *self,iptr improvement_id)

{
  char *name_text;
  u32 improve_idx;
  
  if ((pedia_window_block.pedia_closed != 0) && (net_session_block.map_redraw_busy == 0)) {
    if (improvement_id < 0x27) {
      improve_idx = 0;
      while (((int)improve_idx < (int)self->pedia_improve_count &&
             (((PictureWindow *)self)->pedia_improve_ids[improve_idx] != improvement_id))) {
        improve_idx++;
      }
      if (self->pedia_improve_count != improve_idx) {
        pedia_open_category((MediaWindow *)self,2,0);
        self->resize_border = improve_idx;
        ((PictureWindow *)self)->list_selected_index = improve_idx;
        self->client_x = 1;
        self->border_width = 1;
        pedia_clear_links((WindowObjectView *)self);
        pedia_update_controls((MediaWindow *)self);
        name_text = pedia_lookup_text(pedia_window_block.pedia_improvement_names,improve_idx);
        crt_strcpy((char *)self->pedia_title_text_2,name_text);
        pedia_draw_frame((MediaWindow *)self);
        pedia_draw_improvement_page(self);
        window_show((WindowObjectView *)self);
        wnd_blit_surface((DibSurface *)((i8 *)&pedia_window_block.pedia_window));
        wnd_activate((Wnd *)((i8 *)&pedia_window_block.pedia_window_wnd));
        wnd_set_modal_idle_callback((ModalMenuWindow *)((i8 *)&pedia_window_block.pedia_window_wnd),(iptr)pedia_modal_idle);
        wnd_run_modal_loop((ModalMenuWindow *)((i8 *)&pedia_window_block.pedia_window_wnd));
        wnd_set_modal_idle_callback((ModalMenuWindow *)((i8 *)&pedia_window_block.pedia_window_wnd),0);
      }
    }
    else {
      pedia_show_wonder_modal(self,improvement_id);
    }
  }
  return;
}

/* 005ac840 auto */
void __thiscall pedia_show_unit_list(MediaWindow *self,iptr unused_arg)

{
  int i;
  
  if (((int)self->resize_border < 0) || (((PictureWindow *)self)->pedia_unit_count <= (int)self->resize_border)) {
    self->resize_border = 0;
  }
  ((PictureWindow *)self)->list_count = ((PictureWindow *)self)->pedia_unit_count;
  ((PictureWindow *)self)->list_selected_index = self->resize_border;
  ((PictureWindow *)self)->list_top_index = self->resize_border;
  while (pedia_window_block.pedia_list_top % 9 != 0) {
    ((PictureWindow *)self)->list_top_index = ((PictureWindow *)self)->list_top_index - 1;
  }
  for (i = 0; i < ((PictureWindow *)self)->pedia_unit_count; i++) {
    ((PictureWindow *)self)->list_items[i] =
         ((PictureWindow *)self)->pedia_unit_ids[i];
  }
  scrollbar_set_range
            ((Control *)&((PictureWindow *)self)->list_scrollbar,0,((PictureWindow *)self)->list_count / 9);
  scrollbar_set_pos
            ((ClickControl *)&((PictureWindow *)self)->list_scrollbar,((PictureWindow *)self)->list_top_index / 9);
  if (((PictureWindow *)self)->list_count < 1) {
    ((PictureWindow *)self)->list_top_index = -1;
  }
  pedia_update_controls(self);
  wnd_set_focus((WndBase *)((i8 *)&pedia_window_block.pedia_window_wnd));
  wnd_activate((Wnd *)((i8 *)&pedia_window_block.pedia_window_wnd));
  pedia_redraw((PediaRedrawView *)((i8 *)&pedia_window_block.pedia_window));
  return;
}

/* 005ac9ad auto */
void __thiscall pedia_draw_unit_page(DocumentWindow *self)

{
  int measure;
  size_t text_len;
  int center_y;
  u32 yBottom;
  i8 shield_ctx[16];
  i8 unit_ctx[16];
  tagRECT desc_rect;
  int has_text;
  int line_height;
  tagRECT link_rect;
  int text_width;
  int row_height;
  iptr unit_type;
  char *pedia_file;
  int half_width;
  i32 unused_a;
  int icon_width;
  char desc_buf[1000];
  i32 unused_d;
  int y2;
  u32 x2;
  int content_width2;
  int value_x;
  int line;
  i32 unused_b;
  int margin;
  i32 text_color2;
  i32 unused_c;
  i32 scale_den2;
  i32 scale_num2;
  int slot_height;
  i8 saved_clip[16];
  GameFont *font2;
  
  surface_get_clip((DibSurface *)self,(RECT *)saved_clip);
  surface_set_clip((DibSurface *)self,(RECT *)&self->content_left);
  pedia_update_controls((MediaWindow *)self);
  pedia_fill_background((WindowObjectView *)self,(RECT *)&self->content_left,2);
  font2 = (GameFont *)((i8 *)&font_size21);
  x2 = self->content_left;
  margin = 10;
  content_width2 = rect_width((RECT *)&self->content_left);
  half_width = content_width2 / 2;
  slot_height = rect_height((RECT *)&self->content_left);
  slot_height = slot_height / 0xc;
  row_height = font_cached_height(font2);
  y2 = self->content_top + 0xf;
  unit_type = ((PictureWindow *)self)->pedia_unit_ids[self->resize_border];
  x2 += margin;
  gfx_get_scale_ratio((iptr)&scale_num2,(iptr)&scale_den2);
  gfx_set_scale_ratio(2,1);
  icon_width = sprite_get_width((Sprite *)(((i8 *)&pollution_sprite_block.unit_sprites) + unit_type * 0x3c))
  ;
  icon_width += panel_margin_x * 2;
  center_y = y2 + slot_height / 2;
  measure = sprite_get_height((Sprite *)(((i8 *)&pollution_sprite_block.unit_sprites) + unit_type * 0x3c));
  sprite_draw
            ((Sprite *)(((i8 *)&pollution_sprite_block.unit_sprites) + unit_type * 0x3c),(iptr)unit_ctx,(iptr)&pedia_window_block.pedia_window,x2,
             center_y - measure / 2);
  gfx_set_scale_ratio(scale_num2,scale_den2);
  text_color2 = list_text_color;
  gfx_set_text_color_index(list_text_color);
  measure = sprite_get_width((Sprite *)(((i8 *)&pollution_sprite_block.unit_sprites) + unit_type * 0x3c));
  x2 = x2 + icon_width + measure + 0x32;
  y2 = sprite_get_height((Sprite *)(((i8 *)&pollution_sprite_block.unit_sprites) + unit_type * 0x3c));
  y2 = self->content_top + y2;
  text_clear();
  text_append_label(0x79);
  text_append_colon();
  surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
  measure = font_text_width(font2,(const char *)&map_views_block.text_buffer);
  x2 = x2 + measure + 5;
  text_clear();
  if (unit_types[unit_type].prerequisite < '\0') {
    text_append_label(0xe);
    surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
  }
  else {
    text_append_string_id(advances[unit_types[unit_type].prerequisite].name);
    text_width = font_text_width(font2,(const char *)&map_views_block.text_buffer);
    line_height = font_line_spacing(font2);
    SetRect(&link_rect,x2,y2,text_width + x2 + 5,line_height + y2);
    pedia_add_link(self,(int)unit_types[unit_type].prerequisite,x2,y2,0,
                       link_rect.left,link_rect.top,link_rect.right,link_rect.bottom);
  }
  value_x = half_width - 0x4b;
  x2 = self->content_left + margin;
  measure = sprite_get_height((Sprite *)(((i8 *)&pollution_sprite_block.unit_sprites) + unit_type * 0x3c));
  y2 = measure * 2 + self->content_top + row_height;
  text_clear();
  text_append_label(0x84);
  text_append_colon();
  surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
  text_clear();
  if ((char)unit_types[unit_type].cost < '\0') {
    text_append_label(0xe);
    surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,value_x,y2,5);
  }
  else {
    _sprintf(((i8 *)&map_views_block.text_buffer),((i8 *)&pedia_unit_cost_fmt),(char)unit_types[unit_type].cost * 10);
    surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,value_x,y2,5);
    measure = font_text_width(font2,(const char *)&map_views_block.text_buffer);
    x2 = value_x + measure + 5;
    center_y = y2 + slot_height / 2;
    measure = sprite_get_height((Sprite *)((i8 *)&war_icon_sprite_block.shield_icon_sprite));
    sprite_draw
              ((Sprite *)((i8 *)&war_icon_sprite_block.shield_icon_sprite),(iptr)shield_ctx,(iptr)&pedia_window_block.pedia_window,x2,
               (center_y - 2) - measure / 2);
  }
  x2 = self->content_left + margin;
  y2 += row_height;
  text_clear();
  text_append_label(0x7f);
  text_append_colon();
  surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
  text_clear();
  _sprintf(((i8 *)&map_views_block.text_buffer),((i8 *)&pedia_unit_attack_fmt),(int)(char)unit_types[unit_type].attack);
  surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,value_x,y2,5);
  y2 += row_height;
  text_clear();
  text_append_label(0x80);
  text_append_colon();
  surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
  text_clear();
  _sprintf(((i8 *)&map_views_block.text_buffer),((i8 *)&pedia_unit_defense_fmt),(int)(char)unit_types[unit_type].defense);
  surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,value_x,y2,5);
  y2 += row_height;
  text_clear();
  text_append_label(0x82);
  text_append_colon();
  surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
  text_clear();
  _sprintf(((i8 *)&map_views_block.text_buffer),((i8 *)&pedia_unit_hp_fmt),(int)(char)unit_types[unit_type].hit_points / 10);
  surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,value_x,y2,5);
  y2 += row_height;
  text_clear();
  text_append_label(0x83);
  text_append_colon();
  surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
  text_clear();
  _sprintf(((i8 *)&map_views_block.text_buffer),((i8 *)&pedia_unit_firepower_fmt),(int)(char)unit_types[unit_type].firepower);
  surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,value_x,y2,5);
  y2 += row_height;
  text_clear();
  text_append_label(0x81);
  text_append_colon();
  surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,x2,y2,5);
  text_clear();
  _sprintf(((i8 *)&map_views_block.text_buffer),((i8 *)&pedia_unit_move_fmt),(int)(char)unit_types[unit_type].move / 3);
  surface_draw_text((DibSurface *)self,(iptr)font2,(const char *)&map_views_block.text_buffer,value_x,y2,5);
  pedia_file = str_pedia_6;
  text_clear();
  text_append_int(unit_type);
  unused_a = 0;
  unused_b = 0;
  unused_c = 7;
  unused_d = 0;
  measure = text_open_section((const char *)pedia_file,(const char *)&str_pediaunitfacts);
  if (measure == 0) {
    has_text = 0;
    str_clear((char *)desc_buf);
    line = (int)text_read_line(1);
    if ((unit_types[unit_type].flags & 1) != 0) {
      if (has_text == 0) {
        crt_strcpy(desc_buf,(char *)(line + 1));
        has_text = 1;
      }
      else {
        crt_strcat(desc_buf,(char *)(line + 1));
      }
      str_append_space((iptr)desc_buf);
    }
    line = (int)text_read_line(1);
    if ((unit_types[unit_type].flags & 2) != 0) {
      if (has_text == 0) {
        crt_strcpy(desc_buf,(char *)(line + 1));
        has_text = 1;
      }
      else {
        crt_strcat(desc_buf,(char *)(line + 1));
      }
      str_append_space((iptr)desc_buf);
    }
    line = (int)text_read_line(1);
    if ((unit_types[unit_type].flags & 4) != 0) {
      if (has_text == 0) {
        crt_strcpy(desc_buf,(char *)(line + 1));
        has_text = 1;
      }
      else {
        crt_strcat(desc_buf,(char *)(line + 1));
      }
      str_append_space((iptr)desc_buf);
    }
    line = (int)text_read_line(1);
    if ((unit_types[unit_type].flags & 8) != 0) {
      if (has_text == 0) {
        crt_strcpy(desc_buf,(char *)(line + 1));
        has_text = 1;
      }
      else {
        crt_strcat(desc_buf,(char *)(line + 1));
      }
      str_append_space((iptr)desc_buf);
    }
    line = (int)text_read_line(1);
    if ((unit_types[unit_type].flags & 0x10) != 0) {
      if (has_text == 0) {
        crt_strcpy(desc_buf,(char *)(line + 1));
        has_text = 1;
      }
      else {
        crt_strcat(desc_buf,(char *)(line + 1));
      }
      str_append_space((iptr)desc_buf);
    }
    line = (int)text_read_line(1);
    if ((unit_types[unit_type].flags & 0x20) != 0) {
      if (has_text == 0) {
        crt_strcpy(desc_buf,(char *)(line + 1));
        has_text = 1;
      }
      else {
        crt_strcat(desc_buf,(char *)(line + 1));
      }
      str_append_space((iptr)desc_buf);
    }
    line = (int)text_read_line(1);
    if ((unit_types[unit_type].flags & 0x40) != 0) {
      if (has_text == 0) {
        crt_strcpy(desc_buf,(char *)(line + 1));
        has_text = 1;
      }
      else {
        crt_strcat(desc_buf,(char *)(line + 1));
      }
      str_append_space((iptr)desc_buf);
    }
    line = (int)text_read_line(1);
    if ((unit_types[unit_type].flags & 0x80) != 0) {
      if (has_text == 0) {
        crt_strcpy(desc_buf,(char *)(line + 1));
        has_text = 1;
      }
      else {
        crt_strcat(desc_buf,(char *)(line + 1));
      }
      str_append_space((iptr)desc_buf);
    }
    line = (int)text_read_line(1);
    if ((unit_types[unit_type].flags & 0x100) != 0) {
      if (has_text == 0) {
        crt_strcpy(desc_buf,(char *)(line + 1));
        has_text = 1;
      }
      else {
        crt_strcat(desc_buf,(char *)(line + 1));
      }
      str_append_space((iptr)desc_buf);
    }
    line = (int)text_read_line(1);
    if ((unit_types[unit_type].flags & 0x200) != 0) {
      if (has_text == 0) {
        crt_strcpy(desc_buf,(char *)(line + 1));
        has_text = 1;
      }
      else {
        crt_strcat(desc_buf,(char *)(line + 1));
      }
      str_append_space((iptr)desc_buf);
    }
    line = (int)text_read_line(1);
    if ((unit_types[unit_type].flags & 0x400) != 0) {
      if (has_text == 0) {
        crt_strcpy(desc_buf,(char *)(line + 1));
        has_text = 1;
      }
      else {
        crt_strcat(desc_buf,(char *)(line + 1));
      }
      str_append_space((iptr)desc_buf);
    }
    line = (int)text_read_line(1);
    if ((unit_types[unit_type].flags & 0x800) != 0) {
      if (has_text == 0) {
        crt_strcpy(desc_buf,(char *)(line + 1));
        has_text = 1;
      }
      else {
        crt_strcat(desc_buf,(char *)(line + 1));
      }
      str_append_space((iptr)desc_buf);
    }
    line = (int)text_read_line(1);
    if ((unit_types[unit_type].flags & 0x1000) != 0) {
      if (has_text == 0) {
        crt_strcpy(desc_buf,(char *)(line + 1));
        has_text = 1;
      }
      else {
        crt_strcat(desc_buf,(char *)(line + 1));
      }
      str_append_space((iptr)desc_buf);
    }
    line = (int)text_read_line(1);
    if ((unit_types[unit_type].flags & 0x2000) != 0) {
      if (has_text == 0) {
        crt_strcpy(desc_buf,(char *)(line + 1));
        has_text = 1;
      }
      else {
        crt_strcat(desc_buf,(char *)(line + 1));
      }
      str_append_space((iptr)desc_buf);
    }
    line = (int)text_read_line(1);
    if ((unit_types[unit_type].flags & 0x4000) != 0) {
      if (has_text == 0) {
        crt_strcpy(desc_buf,(char *)(line + 1));
        has_text = 1;
      }
      else {
        crt_strcat(desc_buf,(char *)(line + 1));
      }
      str_append_space((iptr)desc_buf);
    }
    text_close_file();
    x2 = self->content_left + half_width;
    measure = sprite_get_height((Sprite *)(((i8 *)&pollution_sprite_block.unit_sprites) + unit_type * 0x3c));
    y2 = measure * 2 + self->content_top + row_height;
    text_len = _strlen(desc_buf);
    if (text_len != 0) {
      yBottom = self->content_bottom;
      measure = rect_width((RECT *)&self->content_left);
      SetRect(&desc_rect,x2,y2,x2 + measure / 2,yBottom);
      surface_draw_text_rect
                ((DibSurface *)self,(iptr)font2,(const char *)desc_buf,(iptr)&desc_rect,5);
    }
  }
  pedia_update_describe_button((ListPaneWindow *)self,self->resize_border);
  surface_set_clip((DibSurface *)self,(RECT *)saved_clip);
  wnd_blit_surface_rect((DibSurface *)self,(iptr)&self->content_left);
  return;
}

/* 005ad998 auto */
void __thiscall pedia_show_unit_modal(DocumentWindow *self,iptr unit_type)

{
  char *name_text;
  u32 unit_index;
  
  if ((pedia_window_block.pedia_closed != 0) && (net_session_block.map_redraw_busy == 0)) {
    unit_index = 0;
    while (((int)unit_index < ((PictureWindow *)self)->pedia_unit_count &&
           (((PictureWindow *)self)->pedia_unit_ids[unit_index] != unit_type))) {
      unit_index++;
    }
    if ((u32)((PictureWindow *)self)->pedia_unit_count != unit_index) {
      pedia_open_category((MediaWindow *)self,4,0);
      self->resize_border = unit_index;
      ((PictureWindow *)self)->list_selected_index = unit_index;
      self->client_x = 1;
      self->border_width = 1;
      pedia_clear_links((WindowObjectView *)self);
      pedia_update_controls((MediaWindow *)self);
      name_text = pedia_lookup_text(pedia_window_block.pedia_unit_names,unit_index);
      crt_strcpy((char *)self->pedia_title_text_2,name_text);
      pedia_draw_frame((MediaWindow *)self);
      pedia_draw_unit_page(self);
      window_show((WindowObjectView *)self);
      wnd_blit_surface((DibSurface *)((i8 *)&pedia_window_block.pedia_window));
      wnd_activate((Wnd *)((i8 *)&pedia_window_block.pedia_window_wnd));
      wnd_set_modal_idle_callback((ModalMenuWindow *)((i8 *)&pedia_window_block.pedia_window_wnd),(iptr)pedia_modal_idle);
      wnd_run_modal_loop((ModalMenuWindow *)((i8 *)&pedia_window_block.pedia_window_wnd));
      wnd_set_modal_idle_callback((ModalMenuWindow *)((i8 *)&pedia_window_block.pedia_window_wnd),0);
    }
  }
  return;
}
