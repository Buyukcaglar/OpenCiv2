/* The game, controls: buttons, lists, combo and check boxes, edit fields, scroll bars: functions translated from the original
 * (tools/gen_c.py, now edited directly), in address order. */
#include "auto_common.h"

/* 0040f380 auto */
void __thiscall ctrl_show_and_redraw(Control *self)

{
  if (self->hwnd != 0) {
    hwnd_show(self->hwnd);
    wnd_invalidate(self->hwnd);
  }
  return;
}

/* 0040f3e0 auto */
Button * __thiscall button_ctor(Button *self)

{
  i32 seh_prev;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0xffffffff;
  ctrl_base_ctor(self);
  self->hotkey_char = '\0';
  self->on_select = 0xffffffff;
  return self;
}

/* 0040f480 auto */
Control * __thiscall ctrl_base_ctor(Control *self)

{
  self->ctrl_id = 0;
  self->parent = 0;
  SetRect((LPRECT)&self->rect_left,0,0,0,0);
  self->hwnd = 0;
  self->next_ctrl = 0;
  self->wants_initial_focus = '\0';
  self->hotkey_char = '\0';
  self->hotkey_pos = 0xffffffff;
  return self;
}

/* 0040f510 auto */
i32 __thiscall ctrl_base_dtor(Control *self)

{
  i32 result;
  
  if (self->parent != 0) {
    wnd_remove_control((Wnd *)self->parent,self->ctrl_id);
  }
  self->next_ctrl = 0;
  result = ctrl_destroy_hwnd((iptr)self);
  return result;
}

/* 0040f570 auto */
i32 __thiscall ctrl_dtor(Button *self)

{
  i32 seh_prev;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0;
  if (self->hwnd != 0) {
    ctrl_destroy(self);
  }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 0040f5c3 */ { ctrl_base_dtor(self); }
  return seh_prev;
}

/* 0040f610 auto */
void __thiscall ctrl_destroy(Control *self)

{
  if (self->hwnd != 0) {
    if (self->parent != 0) {
      wnd_remove_control((Wnd *)self->parent,self->ctrl_id);
    }
    self->next_ctrl = 0;
    ctrl_destroy_hwnd((iptr)self);
  }
  return;
}

/* 0040f680 auto */
void __thiscall
button_create
          (Button *self,iptr parent,i32 ctrl_id,iptr rect,const char *label)

{
  u32 new_hwnd;
  
  if (self->hwnd != 0) {
    ctrl_destroy(self);
  }
  self->font = (u32)(*(i8 * *)draw_current_font_rest);
  ctrl_init(self,parent,6,ctrl_id,(RECT *)rect);
  self->on_click = 0;
  new_hwnd = button_create_hwnd((int *)rect,(iptr)self,label,1,(GameFont *)self->font);
  self->hwnd = new_hwnd;
  self->is_enabled = 1;
  return;
}

/* 0040f730 auto */
void __thiscall
ctrl_init(Control *self,iptr parent_wnd,u32 type_code,u32 id,RECT *rect)

{
  self->parent = parent_wnd;
  self->ctrl_type = type_code;
  self->ctrl_id = id;
  self->rect_left = (u32)rect->left;
  self->rect_top = (u32)rect->top;
  self->rect_right = (u32)rect->right;
  self->rect_bottom = (u32)rect->bottom;
  self->next_ctrl = 0;
  self->hwnd = 0;
  self->wants_initial_focus = '\0';
  wnd_append_control((Wnd *)parent_wnd,(iptr)self);
  return;
}

/* 0040f7d0 auto */
void __thiscall ctrl_set_default_button(Button *self)

{
  iptr parent;
  
  parent = ctrl_get_parent(self);
  *(Button **)(parent + 0xbc) = self;
  return;
}

/* 0040f810 auto */
uptr __thiscall ctrl_get_parent(Control *self)

{
  return self->parent;
}

/* 0040f840 auto */
void __thiscall ctrl_set_cancel_button(Button *self)

{
  iptr parent;
  
  parent = ctrl_get_parent(self);
  *(Button **)(parent + 0xc0) = self;
  return;
}

/* 0040f880 auto */
void __thiscall button_set_callback(Button *self,CtrlNotifyFn callback)

{
  self->on_click = callback;
  return;
}

/* 0040f8b0 auto */
Checkbox * __thiscall checkbox_elem_ctor(Checkbox *self)

{
  i32 seh_prev;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0xffffffff;
  ctrl_base_ctor(self);
  return self;
}

/* 0040f930 auto */
void __thiscall checkbox_dtor(Checkbox *self)

{
  i32 seh_prev;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0;
  if (self->hwnd != 0) {
    checkbox_destroy_hwnd(self->hwnd);
  }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 0040f98a */ { ctrl_base_dtor(self); }
  return;
}

/* 0040f9d0 auto */
void __thiscall
checkbox_create
          (Checkbox *self,iptr parent,i32 ctrl_id,i32 x,i32 y
          ,const char *label)

{
  u32 new_hwnd;
  i8 rect[16];
  
  self->font = (u32)(*(i8 * *)(draw_current_font_rest + 8));
  checkbox_calc_rect((char *)label,x,y,(iptr)rect,(GameFont *)self->font);
  if (self->hwnd != 0) {
    ctrl_destroy(self);
  }
  ctrl_init(self,parent,2,ctrl_id,(RECT *)rect);
  self->on_toggle = 0;
  self->is_enabled = 1;
  self->checked = 0;
  new_hwnd = checkbox_create_hwnd((RECT *)rect,(iptr)self,(char *)label,1);
  self->hwnd = new_hwnd;
  return;
}

/* 0040faa0 auto */
void __thiscall checkbox_set_callback(Checkbox *self,CheckboxToggleFn callback)

{
  self->on_toggle = callback;
  return;
}

/* 0040fad0 auto */
void __thiscall checkbox_set_checked(Checkbox *self,u32 checked)

{
  self->checked = checked;
  return;
}

/* 0040fb00 auto */
Scrollbar * __thiscall scrollbar_ctor(Scrollbar *self)

{
  i32 seh_prev;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0xffffffff;
  ctrl_base_ctor(self);
  self->page_size = 1;
  self->on_change = 0;
  self->on_track = 0;
  return self;
}

/* 0040fbb0 auto */
void __thiscall scrollbar_dtor(Scrollbar *self)

{
  i32 seh_prev;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0;
  if (self->hwnd != 0) {
    scrollbar_destroy_hwnd(self->hwnd);
  }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 0040fc0a */ { ctrl_base_dtor(self); }
  return;
}

/* 0040fc50 auto */
void __thiscall
scrollbar_create
          (Scrollbar *self,iptr parent,iptr ctrl_id,iptr rect,i32 style)

{
  u32 new_hwnd;
  
  if (self->hwnd != 0) {
    ctrl_destroy(self);
  }
  ctrl_init(self,parent,8,ctrl_id,(RECT *)rect);
  new_hwnd = scrollbar_create_hwnd((int *)rect,(iptr)self,style,1);
  self->hwnd = new_hwnd;
  scrollbar_hwnd_set_range(self->hwnd,1,100);
  self->field_38 = 1;
  return;
}

/* 0040fcf0 auto */
void __thiscall scrollbar_set_pos(Scrollbar *self,iptr pos)

{
  self->cur_pos = pos;
  scrollbar_hwnd_set_pos(self->hwnd,pos);
  return;
}

/* 0040fd40 auto */
void __thiscall
scrollbar_set_range(Scrollbar *self,i32 min_value,i32 max_value)

{
  scrollbar_hwnd_set_range(self->hwnd,min_value,max_value);
  return;
}

/* 0040fd80 auto */
void __thiscall scrollbar_set_callback(Scrollbar *self,ScrollFn callback)

{
  self->on_change = callback;
  return;
}

/* 00418740 auto */
u32 __thiscall ctrl_get_id(Control *self)

{
  return self->ctrl_id;
}

/* 00418770 auto */
u32 __thiscall control_get_hwnd(Control *self)

{
  return self->hwnd;
}

/* 004187a0 auto */
EditControl * __thiscall edit_ctor(EditControl *self)

{
  i32 seh_prev;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0xffffffff;
  ctrl_base_ctor(self);
  self->on_maxtext = 0;
  self->on_change = 0;
  self->field_44 = 0;
  self->on_key = 0;
  self->keep_sel = 0;
  self->field_39 = 0;
  return self;
}

/* 00418870 auto */
void __thiscall edit_dtor(EditControl *self)

{
  i32 seh_prev;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0;
  if (self->hwnd != 0) {
    edit_hwnd_cleanup_stub(self->hwnd);
  }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 004188ca */ { ctrl_base_dtor(self); }
  return;
}

/* 00418910 auto */
void __thiscall
edit_create
          (EditControl *self,iptr parent,i32 ctrl_id,iptr rect,const char *text)

{
  u32 new_hwnd;
  
  if (self->hwnd != 0) {
    ctrl_destroy(self);
  }
  self->edit_font = (u32)(*(i8 * *)(draw_current_font_rest + 12));
  ctrl_init(self,parent,4,ctrl_id,(RECT *)rect);
  new_hwnd = edit_create_window((int *)rect,(iptr)self,1,1,(GameFont *)self->edit_font);
  self->hwnd = new_hwnd;
  hwnd_send_settext(self->hwnd,(LPARAM)(text));
  return;
}

/* 004189c0 auto */
void __thiscall edit_set_max_len(EditControl *self,i32 max_len)

{
  edit_hwnd_limit_text(self->hwnd,max_len);
  return;
}

/* 00418a00 auto */
void __thiscall edit_set_callback(EditControl *self,EditKeyFn callback)

{
  self->on_key = callback;
  return;
}

/* 00418a30 auto */
void __thiscall ctrl_set_text(Control *self,const char *text)

{
  hwnd_send_settext(self->hwnd,(LPARAM)(text));
  return;
}

/* 00418a70 auto */
void __thiscall ctrl_get_text(Control *self,char *buffer)

{
  hwnd_get_text(self->hwnd,(LPARAM)(buffer));
  return;
}

/* 00418ab0 auto */
ComboBox * __thiscall combo_ctor(ComboBox *self)

{
  i32 seh_prev;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0xffffffff;
  ctrl_base_ctor(self);
  self->on_dblclick = 0;
  self->on_select = 0;
  return self;
}

/* 00418b50 auto */
void __thiscall combo_dtor(ComboBox *self)

{
  i32 seh_prev;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0;
  if (self->hwnd != 0) {
    combo_hwnd_cleanup_stub(self->hwnd);
  }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 00418baa */ { ctrl_base_dtor(self); }
  return;
}

/* 00418bf0 auto */
void __thiscall
combo_create(ComboBox *self,iptr parent,i32 ctrl_id,iptr rect)

{
  u32 new_hwnd;
  
  if (self->hwnd != 0) {
    ctrl_destroy(self);
  }
  ctrl_init(self,parent,10,ctrl_id,(RECT *)rect);
  new_hwnd = combo_create_window((int *)rect,(iptr)self,1);
  self->hwnd = new_hwnd;
  self->item_count = 0;
  return;
}

/* 00418c70 auto */
void __thiscall combo_set_font(ComboBox *self,iptr font)

{
  i32 hfont;
  
  hfont = font_get_hfont((GameFont *)font);
  combo_hwnd_set_font(self->hwnd,hfont);
  return;
}

/* 00418ce0 auto */
void __thiscall combo_add_string(ComboBox *self,const char *text)

{
  combo_hwnd_add_string(self->hwnd,(LPARAM)(text));
  self->item_count++;
  return;
}

/* 00418d20 auto */
void __thiscall combo_clear(ComboBox *self)

{
  combo_hwnd_clear(self->hwnd);
  self->item_count = 0;
  return;
}

/* 00418d60 auto */
i32 __thiscall combo_get_cur_sel(ComboBox *self)

{
  i32 sel;
  
  sel = combo_hwnd_get_cur_sel(self->hwnd);
  return sel;
}

/* 00418d90 auto */
void __thiscall combo_set_cur_sel(ComboBox *self,iptr index)

{
  combo_hwnd_set_cur_sel(self->hwnd,index);
  return;
}

/* 00418dd0 auto */
void __thiscall combo_set_callback(ComboBox *self,CtrlNotifyFn callback)

{
  self->on_select = callback;
  return;
}

/* 00418e00 auto */
ListBox * __thiscall listbox_ctor(ListBox *self)

{
  i32 seh_prev;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0xffffffff;
  ctrl_base_ctor(self);
  self->on_dblclick = 0;
  self->on_select = 0;
  return self;
}

/* 00418ea0 auto */
void __thiscall listbox_dtor(ListBox *self)

{
  i32 seh_prev;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0;
  if (self->hwnd != 0) {
    listbox_hwnd_cleanup_stub(self->hwnd);
  }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 00418efa */ { ctrl_base_dtor(self); }
  return;
}

/* 00418f40 auto */
void __thiscall
listbox_create(ListBox *self,iptr parent,i32 ctrl_id,iptr rect)

{
  u32 new_hwnd;
  
  if (self->hwnd != 0) {
    ctrl_destroy(self);
  }
  self->font = (u32)(*(i8 * *)(draw_current_font_rest + 16));
  ctrl_init(self,parent,7,ctrl_id,(RECT *)rect);
  new_hwnd = listbox_create_hwnd((int *)rect,(iptr)self,1,0,(GameFont *)self->font);
  self->hwnd = new_hwnd;
  self->item_count = 0;
  return;
}

/* 00418fe0 auto */
void __thiscall listbox_set_font(ListBox *self,iptr font)

{
  i32 hfont;
  
  hfont = font_get_hfont((GameFont *)font);
  listbox_hwnd_set_font(self->hwnd,hfont);
  return;
}

/* 00419020 auto */
void __thiscall listbox_add_string(ListBox *self,const char *text)

{
  listbox_hwnd_add_string(self->hwnd,(LPARAM)(text));
  self->item_count++;
  return;
}

/* 00419060 auto */
void __thiscall listbox_clear(ListBox *self)

{
  listbox_hwnd_clear(self->hwnd);
  self->item_count = 0;
  return;
}

/* 00421bd0 auto */
void __cdecl input_flush_events(void)

{
  win_drain_input_msgs();
  return;
}

/* 00421ca0 auto */
void __thiscall radiogrp_enable_item(RadioGroup *self,iptr index)

{
  if ((index < (int)self->item_count) && (-1 < index)) {
    ((RadioItem *)self->items)[index].enabled = 1;
    radiogrp_hwnd_invalidate((i32)((RadioItem *)self->items)[index].hwnd);
  }
  return;
}

/* 0043c5f0 auto */
void __thiscall control_hide(Control *self)

{
  if (self->hwnd != 0) {
    hwnd_hide(self->hwnd);
  }
  return;
}

/* 00447210 auto */
void __thiscall radiogrp_disable_item(RadioGroup *self,iptr index)

{
  if ((index < (int)self->item_count) && (-1 < index)) {
    if (self->selected == index) {
      self->selected = 0xffffffff;
    }
    ((RadioItem *)self->items)[index].enabled = 0;
    radiogrp_hwnd_invalidate((i32)((RadioItem *)self->items)[index].hwnd);
  }
  return;
}

/* 004472c0 auto */
/* Library Function - Single Match
    public: unsigned int __thiscall CCheckListBox::GetCheckStyle(void)
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall radiogrp_get_selected(RadioGroup *self)

{
  return self->selected;
}

/* 004472f0 auto */
void __thiscall radiogrp_set_selected(RadioGroup *self,u32 value)

{
  self->selected = value;
  return;
}

/* 00451ac0 auto */
void __thiscall scrollbar_set_track_callback(Scrollbar *self,ScrollFn callback)

{
  self->on_track = callback;
  return;
}

/* 00453c40 auto */
void __thiscall ctrl_disable(Button *self)

{
  self->is_enabled = 0;
  wnd_invalidate(self->hwnd);
  return;
}

/* 00453c80 auto */
void __thiscall ctrl_enable(Button *self)

{
  self->is_enabled = 1;
  wnd_invalidate(self->hwnd);
  return;
}

/* 00479da8 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl scrollbar_66c728_global_init(void)

{
  scrollbar_66c728_static_init();
  scrollbar_66c728_reg_atexit();
  return;
}

/* 00479dc2 auto */
void __cdecl scrollbar_66c728_static_init(void)

{
  scrollbar_ctor((Scrollbar *)((i8 *)&static_scrollbar_1));
  return;
}

/* 00479ddc auto */
void __cdecl scrollbar_66c728_reg_atexit(void)

{
  _atexit(scrollbar_66c728_atexit_dtor);
  return;
}

/* 00479df9 auto */
void __cdecl scrollbar_66c728_atexit_dtor(void)

{
  scrollbar_dtor((Scrollbar *)((i8 *)&static_scrollbar_1));
  return;
}

/* 00479e13 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl scrollbar_66c768_global_init(void)

{
  scrollbar_66c768_static_init();
  scrollbar_66c768_reg_atexit();
  return;
}

/* 00479e2d auto */
void __cdecl scrollbar_66c768_static_init(void)

{
  scrollbar_ctor((Scrollbar *)((i8 *)&static_scrollbar_2));
  return;
}

/* 00479e47 auto */
void __cdecl scrollbar_66c768_reg_atexit(void)

{
  _atexit(scrollbar_66c768_atexit_dtor);
  return;
}

/* 00479e64 auto */
void __cdecl scrollbar_66c768_atexit_dtor(void)

{
  scrollbar_dtor((Scrollbar *)((i8 *)&static_scrollbar_2));
  return;
}

/* 00492ab0 auto */
i32 __thiscall edit_get_sel_end(EditControl *self)

{
  i32 sel_end;
  
  sel_end = edit_ctl_get_sel_end(self->hwnd);
  return sel_end;
}

/* 00492ae0 auto */
void __thiscall edit_replace_sel(EditControl *self,const char *text)

{
  edit_hwnd_replace_sel(self->hwnd,(LPARAM)(text));
  return;
}

/* 00492b20 auto */
void __thiscall edit_set_sel(EditControl *self,i32 sel_start,i32 sel_end)

{
  edit_hwnd_set_sel(self->hwnd,sel_start,sel_end);
  return;
}

/* 00497d40 auto */
void __thiscall
button_create_with_callback
          (Button *self,iptr parent,i32 ctrl_id,iptr rect,u32 callback,const char *label)

{
  self->on_select = callback;
  self->font = (u32)(*(i8 * *)draw_current_font_rest);
  button_create(self,parent,ctrl_id,rect,label);
  return;
}

/* 004bb3b0 auto */
Button * __thiscall ctrl_scalar_dtor(Button *self,uint flags)

{
  ctrl_dtor(self);
  if ((flags & 1) != 0) {
    operator_delete(self);
  }
  return self;
}

/* 004bb400 auto */
EditControl * __thiscall edit_scalar_dtor(EditControl *self,uint flags)

{
  edit_dtor(self);
  if ((flags & 1) != 0) {
    operator_delete(self);
  }
  return self;
}

/* 004bb450 auto */
Checkbox * __thiscall checkbox_scalar_dtor(Checkbox *self,uint flags)

{
  checkbox_dtor(self);
  if ((flags & 1) != 0) {
    operator_delete(self);
  }
  return self;
}

/* 004bb4a0 auto */
RadioGroup * __thiscall radiogrp_scalar_dtor(RadioGroup *self,uint flags)

{
  radiogrp_dtor(self);
  if ((flags & 1) != 0) {
    operator_delete(self);
  }
  return self;
}

/* 004bb4f0 auto */
Scrollbar * __thiscall scrollbar_scalar_dtor(Scrollbar *self,uint flags)

{
  scrollbar_dtor(self);
  if ((flags & 1) != 0) {
    operator_delete(self);
  }
  return self;
}

/* 004bb5b0 auto */
void __thiscall ctrl_set_initial_focus(Control *self)

{
  self->wants_initial_focus = 1;
  return;
}

/* 004bb5e0 auto */
void __thiscall ctrl_set_focus(Control *self)

{
  if (self->hwnd != 0) {
    ctrl_hwnd_set_focus(self->hwnd);
  }
  return;
}

/* 004bb620 auto */
void __thiscall
edit_create_styled
          (EditControl *self,iptr parent,i32 ctrl_id,iptr rect,const char *text,
          i32 multiline,i32 style)

{
  u32 new_hwnd;
  
  if (self->hwnd != 0) {
    ctrl_destroy(self);
  }
  self->edit_font = (u32)(*(i8 * *)(draw_current_font_rest + 12));
  ctrl_init(self,parent,4,ctrl_id,(RECT *)rect);
  new_hwnd = edit_create_window((int *)rect,(iptr)self,multiline,style,(GameFont *)self->edit_font);
  self->hwnd = new_hwnd;
  hwnd_send_settext(self->hwnd,(LPARAM)(text));
  return;
}

/* 004bb6d0 auto */
void __thiscall edit_set_caret(EditControl *self,i32 pos)

{
  edit_hwnd_set_caret(self->hwnd,pos);
  return;
}

/* 004bb710 auto */
i32 __thiscall edit_get_text_end(EditControl *self)

{
  i32 text_end;
  
  text_end = edit_hwnd_get_text_end(self->hwnd);
  return text_end;
}

/* 004bb740 auto */
void __thiscall radiogrp_dtor(RadioGroup *self)

{
  i32 seh_prev;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0;
  if (self->items_handle != 0) {
    mem_handle_unlock(self->items_handle);
    radiogrp_destroy_items(self->item_count,self->items_handle);
  }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 004bb7b0 */ { ctrl_base_dtor(self); }
  return;
}

/* 004cffb0 auto */
i32 __thiscall
edit_get_line(EditControl *self,i32 line,char *buffer,i32 max_len)

{
  i32 length;
  
  length = edit_hwnd_get_line(self->hwnd,line,(short *)buffer,max_len);
  return length;
}

/* 005011b4 auto */
void __cdecl
spritebtn_create_icon_button(iptr parent,i32 ctrl_id,SpriteButton *button,iptr sprite,RECT *rect)

{
  int *surf_rect;
  int size;
  WndBase *parent_wnd;
  iptr palette;
  int center;
  i8 shadow_ctx[16];
  i8 draw_ctx[16];
  i32 height2;
  RECT rect2;
  RECT inner_rect;
  i32 width2;
  int icon_y;
  int icon_x;
  
  width2 = rect_width(rect);
  height2 = rect_height(rect);
  spritebtn_init_from_sprite
            (button,(WndBase *)parent,ctrl_id,rect->left,rect->top,width2,
             height2,sprite,0x17);
  surf_rect = (int *)surface_get_rect((DibSurface *)&button->on_select);
  rect2.left = *surf_rect;
  rect2.top = surf_rect[1];
  rect2.right = surf_rect[2];
  rect2.bottom = surf_rect[3];
  size = rect_width(&rect2);
  center = rect2.left + size / 2;
  size = sprite_width((Sprite *)sprite);
  icon_x = center - size / 2;
  size = rect_height(&rect2);
  center = rect2.top + size / 2;
  size = sprite_height((Sprite *)sprite);
  icon_y = center - size / 2;
  sprite_draw
            ((Sprite *)sprite,(iptr)draw_ctx,(iptr)&button->on_select,icon_x,icon_y);
  sprite_draw
            ((Sprite *)sprite,(iptr)shadow_ctx,(iptr)(button->button_surface),icon_x + 2,
             icon_y + 2);
  gfx_draw_rect_frame((iptr)&button->on_select,&rect2,10);
  gfx_draw_rect_frame((iptr)(button->button_surface),&rect2,10);
  inner_rect.left = rect2.left;
  inner_rect.top = rect2.top;
  inner_rect.right = rect2.right;
  inner_rect.bottom = rect2.bottom;
  rect_deflate((iptr)&inner_rect,1,1);
  gfx_draw_bevel_rect((iptr)&button->on_select,&inner_rect,0x1f,0xf);
  gfx_draw_bevel_rect((iptr)(button->button_surface),&inner_rect,0xf,10);
  rect_deflate((iptr)&inner_rect,1,1);
  gfx_draw_bevel_rect((iptr)&button->on_select,&inner_rect,0x1f,0xf);
  gfx_draw_bevel_rect((iptr)(button->button_surface),&inner_rect,0xf,10);
  parent_wnd = (WndBase *)ctrl_get_parent(button);
  palette = wnd_get_palette(parent_wnd);
  surface_set_palette((DibSurface *)button->button_surface,palette);
  parent_wnd = (WndBase *)ctrl_get_parent(button);
  palette = wnd_get_palette(parent_wnd);
  surface_set_palette((DibSurface *)&button->on_select,palette);
  return;
}

/* 00511560 auto */
SpriteButton * __thiscall spritebtn_scalar_dtor(SpriteButton *self,uint flags)

{
  spritebtn_dtor(self);
  if ((flags & 1) != 0) {
    operator_delete(self);
  }
  return self;
}

/* 005115b0 auto */
void __thiscall spritebtn_dtor(SpriteButton *self)

{
  i32 seh_prev;
  i8 *seh_handler;
  int seh_state;
  
  seh_state = seh_state & 0xff;
  (*((char *)&seh_state + 0)) = 2;
  if (self->hwnd != 0) {
    spritebtn_hwnd_cleanup_stub(self->hwnd);
  }
  (*((char *)&seh_state + 0)) = 1;
  /* inlined unwind funclet 00511624 */ { surface_dtor((DibSurface *)(*(int *)&self + 0x7c)); }
  seh_state = seh_state & 0xffffff00;
  /* inlined unwind funclet 00511630 */ { surface_dtor((DibSurface *)(*(int *)&self + 0x34)); }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 0051163c */ { ctrl_base_dtor(self); }
  return;
}

/* 00511720 auto */
SpriteButton * __thiscall spritebtn_ctor(SpriteButton *self)

{
  i32 seh_prev;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0xffffffff;
  ctrl_base_ctor(self);
  seh_state = 0;
  surface_ctor((DibSurface *)&self->on_select);
  seh_state = (seh_state & 0xffffff00 | (byte)(1));
  surface_ctor((DibSurface *)self->button_surface);
  self->pressed_state = '\0';
  return self;
}

/* 005117f0 auto */
void __thiscall spritebtn_set_click_handler(SpriteButton *self,CtrlNotifyFn callback)

{
  self->on_click = callback;
  return;
}

/* 00530e80 auto */
/* Library Function - Single Match
    protected: char * __thiscall streambuf::egptr(void)const 
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall ctrl_is_enabled(Button *self)

{
  return self->is_enabled;
}

/* 00530eb0 auto */
void __thiscall edit_set_change_callback(EditControl *self,CtrlNotifyFn callback)

{
  self->on_change = callback;
  return;
}

/* 00530ee0 auto */
void __thiscall
checkbox_create_fixed
          (Checkbox *self,iptr parent,i32 ctrl_id,i32 x,i32 y
          ,i32 width,const char *label)

{
  u32 hwnd;
  i8 rect[16];
  
  self->font = (u32)(*(i8 * *)(draw_current_font_rest + 8));
  checkbox_calc_rect_fixed(x,y,width,(iptr)rect,(GameFont *)self->font);
  if (self->hwnd != 0) {
    ctrl_destroy(self);
  }
  ctrl_init(self,parent,2,ctrl_id,(RECT *)rect);
  self->on_toggle = 0;
  self->is_enabled = 1;
  self->checked = 0;
  hwnd = checkbox_create_hwnd((RECT *)rect,(iptr)self,(char *)label,1);
  self->hwnd = hwnd;
  return;
}

/* 00530fb0 auto */
void __thiscall checkbox_enable(Checkbox *self)

{
  self->is_enabled = 1;
  return;
}

/* 00530fe0 auto */
/* Library Function - Single Match
    public: int __thiscall ios::width(void)const 
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall checkbox_is_checked(Checkbox *self)

{
  return self->checked;
}

/* 00531010 auto */
RadioGroup * __thiscall radiogrp_ctor(RadioGroup *self)

{
  i32 seh_prev;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0xffffffff;
  ctrl_base_ctor(self);
  self->items_handle = 0;
  return self;
}

/* 005310a0 auto */
void __thiscall
radiogrp_create
          (RadioGroup *self,iptr parent,i32 ctrl_id,iptr rect,u32 columns,u32 item_count,
          iptr labels)

{
  u32 handle;
  
  if (self->items_handle != 0) {
    ctrl_destroy(self);
  }
  self->radio_font = (u32)(*(i8 * *)(draw_current_font_rest + 4));
  ctrl_init(self,parent,3,ctrl_id,(RECT *)rect);
  self->on_select = 0;
  self->on_dblclick = 0;
  self->on_rclick = 0;
  self->item_count = item_count;
  self->columns = columns;
  self->selected = 0;
  handle = radiogrp_create_items((iptr)&self->item_count,(int *)rect,columns,(iptr)self,item_count,labels,1,
                       self->radio_font);
  self->items_handle = handle;
  handle = (u32)mem_handle_lock(self->items_handle);
  self->items = handle;
  return;
}

/* 005311b0 auto */
void __thiscall radiogrp_set_select_callback(RadioGroup *self,RadioNotifyFn callback)

{
  self->on_select = callback;
  return;
}

/* 005311e0 auto */
void __thiscall radiogrp_set_dblclick_callback(RadioGroup *self,RadioNotifyFn callback)

{
  self->on_dblclick = callback;
  return;
}

/* 00551d20 auto */
/* Library Function - Single Match
    protected: char * __thiscall streambuf::egptr(void)const 
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall listbox_get_count(ListBox *self)

{
  return self->item_count;
}

/* 00551d50 auto */
i32 __thiscall listbox_get_cur_sel(ListBox *self)

{
  i32 cur_sel;
  
  cur_sel = listbox_hwnd_get_cur_sel(self->hwnd);
  return cur_sel;
}

/* 00551d80 auto */
void __thiscall listbox_set_cur_sel(ListBox *self,i32 index)

{
  listbox_hwnd_set_cur_sel(self->hwnd,index);
  return;
}

/* 00551dc0 auto */
void __thiscall listbox_set_dblclick_callback(ListBox *self,CtrlNotifyFn callback)

{
  self->on_dblclick = callback;
  return;
}

/* 00551df0 auto */
void __thiscall listbox_set_select_callback(ListBox *self,CtrlNotifyFn callback)

{
  self->on_select = callback;
  return;
}

/* 005a9320 auto */
/* Library Function - Multiple Matches With Different Base Names
    public: void * __thiscall CDaoIndexFieldInfo::`vector deleting destructor'(unsigned int)
    public: void * __thiscall CDaoRelationFieldInfo::`vector deleting destructor'(unsigned int)
    public: void * __thiscall CODBCFieldInfo::`vector deleting destructor'(unsigned int)
    public: void * __thiscall CString::`vector deleting destructor'(unsigned int)
   
   Library: Visual Studio 1998 Debug */

Checkbox * __thiscall checkbox_vector_dtor(Checkbox *self,uint flags)

{
  if ((flags & 2) == 0) {
    checkbox_dtor(self);
    if ((flags & 1) != 0) {
      operator_delete(self);
    }
  }
  else {
    crt_vector_dtor_iterator(self,0x3c,VECTOR_COUNT(self),checkbox_dtor);
    operator_delete(&VECTOR_COUNT(self));
  }
  return self;
}

/* 005a93b0 auto */
/* Library Function - Multiple Matches With Different Base Names
    public: void * __thiscall CDaoIndexFieldInfo::`vector deleting destructor'(unsigned int)
    public: void * __thiscall CDaoRelationFieldInfo::`vector deleting destructor'(unsigned int)
    public: void * __thiscall CODBCFieldInfo::`vector deleting destructor'(unsigned int)
    public: void * __thiscall CString::`vector deleting destructor'(unsigned int)
   
   Library: Visual Studio 1998 Debug */

EditControl * __thiscall edit_vector_dtor(EditControl *self,uint flags)

{
  if ((flags & 2) == 0) {
    edit_dtor(self);
    if ((flags & 1) != 0) {
      operator_delete(self);
    }
  }
  else {
    crt_vector_dtor_iterator(self,0x48,VECTOR_COUNT(self),edit_dtor);
    operator_delete(&VECTOR_COUNT(self));
  }
  return self;
}

/* 005a9440 auto */
/* Library Function - Multiple Matches With Different Base Names
    public: void * __thiscall CDaoIndexFieldInfo::`vector deleting destructor'(unsigned int)
    public: void * __thiscall CDaoRelationFieldInfo::`vector deleting destructor'(unsigned int)
    public: void * __thiscall CODBCFieldInfo::`vector deleting destructor'(unsigned int)
    public: void * __thiscall CString::`vector deleting destructor'(unsigned int)
   
   Library: Visual Studio 1998 Debug */

Button * __thiscall ctrl_vector_dtor(Button *self,uint flags)

{
  if ((flags & 2) == 0) {
    ctrl_dtor(self);
    if ((flags & 1) != 0) {
      operator_delete(self);
    }
  }
  else {
    crt_vector_dtor_iterator(self,0x3c,VECTOR_COUNT(self),ctrl_dtor);
    operator_delete(&VECTOR_COUNT(self));
  }
  return self;
}

/* 005a94d0 auto */
ListBox * __thiscall listbox_scalar_dtor(ListBox *self,uint flags)

{
  listbox_dtor(self);
  if ((flags & 1) != 0) {
    operator_delete(self);
  }
  return self;
}

/* 005a9640 auto */
void __thiscall checkbox_disable(Checkbox *self)

{
  self->is_enabled = 0;
  return;
}

/* 005a9670 auto */
void __thiscall listbox_get_text(ListBox *self,i32 index,char *buffer)

{
  listbox_hwnd_get_text(self->hwnd,index,(LPARAM)(buffer));
  return;
}

/* 005a96b0 auto */
void __thiscall listbox_get_sel_text(ListBox *self,char *buffer)

{
  listbox_hwnd_get_sel_text(self->hwnd,buffer);
  return;
}

/* 005bd39e auto */
int __cdecl input_poll_modifier(int modifier)

{
  SHORT key_state;
  BOOL has_msg;
  tagMSG msg;
  char pressed;
  
  pressed = '\0';
  if (modifier == 0x200) {
    key_state = GetKeyState(0x11);
    pressed = ((int)key_state & 0x8000U) != 0;
  }
  else if (modifier == 0x100) {
    key_state = GetKeyState(0x10);
    pressed = ((int)key_state & 0x8000U) != 0;
  }
  else if (modifier == 0x400) {
    while (has_msg = PeekMessageA(&msg,(HWND)0x0,0,0,1), has_msg != 0) {
      if (((msg.message == 0x106) || (msg.message == 0x104)) ||
         (msg.message == 0x105)) {
        pressed = 1;
      }
      else {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
      }
    }
  }
  return (int)pressed;
}

/* 005bd4cd auto */
uint __cdecl input_lbutton_down(void)

{
  SHORT key_state;
  
  key_state = GetAsyncKeyState(1);
  return (uint)((char)((ushort)key_state >> 8) != '\0');
}

/* 005c5e60 auto */
u32 __thiscall control_get_type(Control *self)

{
  return self->ctrl_type;
}

/* 005c5e80 auto */
u32 __thiscall control_get_next(Control *self)

{
  return self->next_ctrl;
}

/* 005c5ea0 auto */
u8 __thiscall ctrl_get_initial_focus(Control *self)

{
  return self->wants_initial_focus;
}

/* 005c5ec0 auto */
u32 __thiscall checkbox_is_enabled(Checkbox *self)

{
  return self->is_enabled;
}

/* 005c5ee0 auto */
u32 __thiscall radiogrp_get_items(RadioGroup *self)

{
  return self->items;
}

/* 005c5f00 auto */
u32 __thiscall radiogrp_item_count(RadioGroup *self)

{
  return self->item_count;
}

/* 005c8f50 auto */
int __thiscall ctrl_get_rect(Control *self)

{
  return (int)&self->rect_left;
}

/* 005c90b0 auto */
void __cdecl ctrl_hwnd_set_focus(HWND hwnd)

{
  SetFocus(hwnd);
  return;
}

/* 005c90ca auto */
void __cdecl ctrl_paint_parent_bkgnd(iptr paint,HWND hwnd)

{
  LONG own_data;
  DibSurface *self;
  WndBase *parent_wnd;
  NativeWindow *window;
  iptr height;
  int value;
  HDC hdcSrc;
  LONG y1;
  DWORD rop;
  tagPOINT origin;
  GdiDib *dib2;
  HWND parent_hwnd;
  
  parent_hwnd = GetParent(hwnd);
  own_data = GetWindowLongA(parent_hwnd,0xc);
  if (own_data == 0) {
    parent_wnd = (WndBase *)GetWindowLongA(parent_hwnd,0);
    value = (int)wnd_get_window(parent_wnd);
    if ((int)((NativeWindow *)value)->bg_brush != 0) {
      FillRect(*(HDC *)paint,(RECT *)(paint + 8),((NativeWindow *)value)->bg_brush);
    }
  }
  else {
    self = (DibSurface *)GetWindowLongA(parent_hwnd,0xc);
    parent_wnd = (WndBase *)GetWindowLongA(parent_hwnd,0);
    window = wnd_get_window(parent_wnd);
    dib2 = surface_get_dib(self);
    origin.x = *(int *)(paint + 8);
    origin.y = *(int *)(paint + 0xc);
    MapWindowPoints(hwnd,window->hwnd,&origin,1);
    if ((window->palette != 0) && (gfx_palettized_display == 1)) {
      SelectPalette(*(HDC *)paint,window->palette,0);
      RealizePalette(*(HDC *)paint);
    }
    rop = 0xcc0020;
    hdcSrc = dib2->hdc;
    own_data = origin.x;
    y1 = origin.y;
    height = rect_height((RECT *)(paint + 8));
    value = rect_width((RECT *)(paint + 8));
    BitBlt(*(HDC *)paint,*(int *)(paint + 8),*(int *)(paint + 0xc),value,height,hdcSrc,own_data,y1
           ,rop);
  }
  return;
}

/* 005c9222 auto */
void __cdecl ctrl_parse_hotkey(iptr ctrl,const char *text)

{
  size_t len;
  uptr pos;
  char *cursor;
  char hotkey[4];
  
  cursor = (char *)text;
  *(i32 *)(ctrl + 0x28) = 0;
  while( true ) {
    if (*cursor == '\0') goto store_hotkey;
    if (*cursor == '~') break;
    *(int *)(ctrl + 0x28) = *(int *)(ctrl + 0x28) + 1;
    cursor++;
  }
  for (pos = *(uptr *)(ctrl + 0x28); len = _strlen((char *)text), pos < len;
      pos = pos + 1) {
    *(i8 *)(pos + text) = *(i8 *)(pos + 1 + text);
  }
store_hotkey:
  len = _strlen((char *)text);
  if (*(uint *)(ctrl + 0x28) < len) {
    hotkey[0] = *(char *)(*(int *)(ctrl + 0x28) + text);
    hotkey[1] = 0;
    __strlwr(hotkey);
    *(char *)(ctrl + 0x25) = hotkey[0];
  }
  else {
    *(i32 *)(ctrl + 0x28) = 0xffffffff;
  }
  return;
}

/* 005c9307 auto */
LRESULT __stdcall ctrl_default_wndproc(HWND hwnd,uint msg,WPARAM wparam,LPARAM lparam)

{
  HWND hWnd;
  ControlBlock *block;
  LRESULT result;
  tagPAINTSTRUCT ps;
  
  if (msg < 0x10) {
    if (msg == 0xf) {
      BeginPaint(hwnd,&ps);
      ctrl_paint_parent_bkgnd((iptr)&ps,hwnd);
      EndPaint(hwnd,&ps);
      return 0;
    }
    if (msg == 2) {
      block = wnd_from_hwnd(hwnd);
      if (block != 0) {
        if (block->kind == 3) {
          *(i32 *)block->data = 0;
        }
        else {
          control_set_hwnd((Control *)block->owner,0);
        }
        ctrl_hwnd_free_block(hwnd);
      }
      result = DefWindowProcA(hwnd,2,wparam,lparam);
      return result;
    }
  }
  else if ((0xff < msg) && (msg < 0x103)) {
    hWnd = GetParent(hwnd);
    SendMessageA(hWnd,msg,wparam,lparam);
    return 0;
  }
  result = DefWindowProcA(hwnd,msg,wparam,lparam);
  return result;
}

/* 005c944b auto */
int __cdecl ctrl_destroy_hwnd(iptr ctrl)

{
  int result;
  int hwnd_val;
  HWND hWnd;
  
  result = control_get_type((Control *)ctrl);
  if (result != 3) {
    hwnd_val = control_get_hwnd((Control *)ctrl);
    result = 0;
    if (hwnd_val != 0) {
      hWnd = control_get_hwnd((Control *)ctrl);
      result = DestroyWindow(hWnd);
    }
  }
  return result;
}

/* 005c9499 auto */
ControlBlock * __cdecl ctrl_init_block(HWND hwnd,iptr owner)

{
  i32 handle;
  ControlBlock *block;
  
  block = (ControlBlock *)0x0;
  if (hwnd == (HWND)0x0) {
    dbg_log((const char *)&str_error_tried_to_initialize_null_control_i);
  }
  else {
    handle = mem_handle_alloc(0x30);
    block = (ControlBlock *)mem_handle_lock(handle);
    block->shared_bitmaps = 0;
    block->bitmaps[2] = 0;
    block->bitmaps[1] = (i32)block->bitmaps[2];
    block->bitmaps[0] = (i32)block->bitmaps[1];
    block->mem_handle = handle;
    block->owner = owner;
    block->pressed = 0;
    block->tracking = 0;
    block->field_20 = 0;
    block->kind = 0;
    SetWindowLongA(hwnd,0,(LONG)block);
  }
  return block;
}

/* 005c9595 auto */
void __cdecl ctrl_hwnd_free_block(HWND hwnd)

{
  i32 handle;
  ControlBlock *block;
  
  if (hwnd == (HWND)0x0) {
    dbg_log((const char *)&str_error_tried_to_dispose_null_control_in_d);
  }
  else {
    block = (ControlBlock *)GetWindowLongA(hwnd,0);
    if (block != (ControlBlock *)0x0) {
      if (block->shared_bitmaps == 0) {
        if (block->bitmaps[0] != 0) {
          DeleteObject((HGDIOBJ)(i32)block->bitmaps[0]);
          block->bitmaps[0] = 0;
        }
        if (block->bitmaps[1] != 0) {
          DeleteObject((HGDIOBJ)(i32)block->bitmaps[1]);
          block->bitmaps[1] = 0;
        }
        if (block->bitmaps[2] != 0) {
          DeleteObject((HGDIOBJ)(i32)block->bitmaps[2]);
          block->bitmaps[2] = 0;
        }
      }
      if (block->kind == 2) {
        operator_delete((void *)block->data);
        block->data = 0;
      }
      handle = block->mem_handle;
      mem_handle_unlock(handle);
      mem_handle_free(handle);
      SetWindowLongA(hwnd,-4,(iptr)ctrl_default_wndproc);
      SetWindowLongA(hwnd,0,0);
    }
  }
  return;
}

/* 005c9710 auto */
/* Library Function - Single Match
    public: void __thiscall ios::delbuf(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall control_set_hwnd(Control *self,u32 hwnd)

{
  self->hwnd = hwnd;
  return;
}

/* 005c9740 auto */
HWND __cdecl
button_create_hwnd(int *rect,iptr ctrl,const char *label,int visible,GameFont *font)

{
  WndBase *self;
  NativeWindow *window;
  iptr height;
  int value;
  HDC hdc;
  int value2;
  HBITMAP h;
  HBITMAP h_00;
  WndBase *parent_wnd;
  PaletteHandleView *this_00;
  HPALETTE hPal;
  GamePalette *this_01;
  GamePalette *logpal;
  HPEN h_01;
  HPEN h_02;
  i32 font_handle;
  i32 *font_data;
  HGDIOBJ h_03;
  HGDIOBJ h_04;
  size_t len;
  HWND hWndParent;
  u32 color_index;
  HMENU hMenu;
  i8 *red_out;
  LONG text_top;
  HINSTANCE hInstance;
  i8 *green_out;
  tagRECT *draw_rect;
  LPVOID lpParam;
  BOOL bForceBkgd;
  i8 *blue_out;
  UINT draw_flags;
  LONG text_bottom;
  DWORD style2;
  char label_text[256];
  int line_y;
  i8 green[4];
  Button *button;
  int text_width;
  HBITMAP bmp_disabled;
  HDC mem_dc;
  i8 red[4];
  i8 blue[4];
  int underline_end;
  HWND hwnd2;
  tagRECT bounds;
  HGDIOBJ old_obj;
  char prefix[256];
  int saved_left;
  int saved_top;
  int saved_right;
  int saved_bottom;
  int underline_start;
  tagRECT text_rect;
  HPEN bg_pen;
  int orig_left;
  int orig_top;
  int orig_right;
  int orig_bottom;
  
  crt_strcpy((char *)((void *)label_text),(const char *)((void *)label));
  button = (Button *)ctrl;
  style2 = 0x40810000;
  if (visible != 0) {
    style2 = 0x50810000;
  }
  lpParam = (LPVOID)0x0;
  hMenu = (HMENU)0x0;
  hInstance = err_report_ctx_block.app_hinstance;
  self = (WndBase *)ctrl_get_parent((Control *)ctrl);
  window = wnd_get_window(self);
  hWndParent = window->hwnd;
  height = rect_height((RECT *)rect);
  value = rect_width((RECT *)rect);
  hwnd2 = CreateWindowExA(4,str_mscontrolclass_2,((i8 *)&button_wnd_title),style2,*rect,
                              rect[1],value,height,hWndParent,hMenu,hInstance,lpParam);
  ctrl_parse_hotkey((iptr)button,(const char *)label_text);
  bounds.left = *rect;
  bounds.top = rect[1];
  bounds.right = rect[2];
  bounds.bottom = rect[3];
  OffsetRect(&bounds,-bounds.left,-bounds.top);
  bounds.right -= 2;
  bounds.bottom -= 2;
  hdc = GetDC(hwnd2);
  value = rect_height(&bounds);
  value2 = rect_width(&bounds);
  h = CreateCompatibleBitmap(hdc,value2,value);
  if (h == (HBITMAP)0x0) {
    dbg_log((const char *)&str_could_not_create_bitmap_in_msinitbutton);
    DestroyWindow(hwnd2);
    hwnd2 = (HWND)0x0;
  }
  else {
    value = rect_height(&bounds);
    value2 = rect_width(&bounds);
    h_00 = CreateCompatibleBitmap(hdc,value2,value);
    if (h_00 == (HBITMAP)0x0) {
      dbg_log((const char *)&str_could_not_create_bitmap_in_msinitbutton_2);
      DestroyWindow(hwnd2);
      hwnd2 = (HWND)0x0;
    }
    else {
      value = rect_height(&bounds);
      value2 = rect_width(&bounds);
      bmp_disabled = CreateCompatibleBitmap(hdc,value2,value);
      if (bmp_disabled == (HBITMAP)0x0) {
        dbg_log((const char *)&str_could_not_create_bitmap_in_msinitbutton_3);
        DestroyWindow(hwnd2);
        hwnd2 = (HWND)0x0;
      }
      else {
        mem_dc = CreateCompatibleDC(hdc);
        ReleaseDC(hwnd2,hdc);
        SetBkMode(mem_dc,1);
        if (button->on_select == 0xffffffff) {
          bg_pen = GetStockObject(1);
        }
        else {
          if (gfx_palettized_display == 1) {
            bForceBkgd = 0;
            parent_wnd = (WndBase *)ctrl_get_parent(button);
            this_00 = (PaletteHandleView *)wnd_get_palette(parent_wnd);
            hPal = palette_get_hpalette(this_00);
            SelectPalette(mem_dc,hPal,bForceBkgd);
            RealizePalette(mem_dc);
          }
          blue_out = blue;
          green_out = green;
          red_out = red;
          color_index = button->on_select;
          parent_wnd = (WndBase *)ctrl_get_parent(button);
          this_01 = (GamePalette *)wnd_get_palette(parent_wnd);
          logpal = palette_get_logpalette(this_01);
          palette_get_entry_rgb((GameLogPalette *)logpal,color_index,(iptr)red_out,(iptr)green_out,(iptr)blue_out);
          bg_pen = CreatePen(0,1,CONCAT12(blue[0],CONCAT11(green[0],red[0])))
          ;
        }
        h_01 = CreatePen(0,1,0xffffff);
        h_02 = CreatePen(0,1,0x808080);
        font_handle = font_get_handle(font);
        font_data = (i32 *)mem_handle_lock(font_handle);
        h_03 = SelectObject(mem_dc,(HGDIOBJ)*font_data);
        font_handle = font_get_handle(font);
        mem_handle_unlock(font_handle);
        h_04 = SelectObject(mem_dc,h);
        orig_left = bounds.left;
        orig_top = bounds.top;
        orig_right = bounds.right;
        orig_bottom = bounds.bottom;
        if (button->on_select == 0xffffffff) {
          FillRect(mem_dc,&bounds,bg_pen);
        }
        else {
          old_obj = SelectObject(mem_dc,bg_pen);
          for (line_y = bounds.top; line_y < bounds.bottom; line_y++) {
            MoveToEx(mem_dc,bounds.left,line_y,(LPPOINT)0x0);
            LineTo(mem_dc,bounds.right,line_y);
          }
          SelectObject(mem_dc,old_obj);
        }
        old_obj = SelectObject(mem_dc,h_01);
        MoveToEx(mem_dc,bounds.left,bounds.bottom,(LPPOINT)0x0);
        LineTo(mem_dc,bounds.left,bounds.top);
        LineTo(mem_dc,bounds.right,bounds.top);
        MoveToEx(mem_dc,bounds.left + 1,bounds.bottom - 1,(LPPOINT)0x0);
        LineTo(mem_dc,bounds.left + 1,bounds.top + 1);
        LineTo(mem_dc,bounds.right - 1,bounds.top + 1);
        SelectObject(mem_dc,h_02);
        MoveToEx(mem_dc,bounds.left + 1,bounds.bottom - 1,(LPPOINT)0x0);
        LineTo(mem_dc,bounds.right - 1,bounds.bottom - 1);
        LineTo(mem_dc,bounds.right - 1,bounds.top);
        MoveToEx(mem_dc,bounds.left + 2,bounds.bottom - 2,(LPPOINT)0x0);
        LineTo(mem_dc,bounds.right - 2,bounds.bottom - 2);
        LineTo(mem_dc,bounds.right - 2,bounds.top + 1);
        SelectObject(mem_dc,old_obj);
        text_rect.left = bounds.left;
        text_rect.top = bounds.top;
        text_rect.right = bounds.right;
        text_rect.bottom = bounds.bottom;
        draw_flags = 0x424;
        draw_rect = &text_rect;
        len = _strlen(label_text);
        DrawTextA(mem_dc,label_text,len,draw_rect,draw_flags);
        text_width = rect_width(&text_rect);
        text_bottom = bounds.bottom;
        value = rect_width(&bounds);
        value2 = ((bounds.left + value / 2) - text_width / 2) + text_width;
        text_top = bounds.top;
        value = rect_width(&bounds);
        SetRect(&text_rect,(bounds.left + value / 2) - text_width / 2,text_top,value2,text_bottom);
        draw_flags = 0x24;
        draw_rect = &text_rect;
        len = _strlen(label_text);
        DrawTextA(mem_dc,label_text,len,draw_rect,draw_flags);
        saved_left = text_rect.left;
        saved_top = text_rect.top;
        saved_right = text_rect.right;
        saved_bottom = text_rect.bottom;
        if (-1 < (int)button->hotkey_pos) {
          crt_strcpy(prefix,label_text);
          prefix[button->hotkey_pos] = '\0';
          len = _strlen(prefix);
          if (len == 0) {
            underline_start = text_rect.left;
          }
          else {
            text_rect.left = saved_left;
            text_rect.top = saved_top;
            text_rect.right = saved_right;
            text_rect.bottom = saved_bottom;
            draw_flags = 0x424;
            draw_rect = &text_rect;
            len = _strlen(prefix);
            DrawTextA(mem_dc,prefix,len,draw_rect,draw_flags);
            underline_start = text_rect.right - 1;
          }
          crt_strcpy(prefix,label_text);
          prefix[button->hotkey_pos + 1] = '\0';
          text_rect.left = saved_left;
          text_rect.top = saved_top;
          text_rect.right = saved_right;
          text_rect.bottom = saved_bottom;
          draw_flags = 0x424;
          draw_rect = &text_rect;
          len = _strlen(prefix);
          DrawTextA(mem_dc,prefix,len,draw_rect,draw_flags);
          text_width = (text_rect.right + 1) - underline_start;
          underline_start = underline_start + (text_width >> 1) - 5;
          underline_end = underline_start + 10;
          SelectObject(mem_dc,h_02);
          MoveToEx(mem_dc,underline_start,text_rect.bottom - 2,(LPPOINT)0x0);
          LineTo(mem_dc,underline_end,text_rect.bottom - 2);
          MoveToEx(mem_dc,underline_start,text_rect.bottom - 1,(LPPOINT)0x0);
          LineTo(mem_dc,underline_end,text_rect.bottom - 1);
          SelectObject(mem_dc,old_obj);
        }
        SelectObject(mem_dc,h_00);
        if (button->on_select == 0xffffffff) {
          FillRect(mem_dc,&bounds,bg_pen);
        }
        else {
          old_obj = SelectObject(mem_dc,bg_pen);
          for (line_y = bounds.top; line_y < bounds.bottom; line_y++) {
            MoveToEx(mem_dc,bounds.left,line_y,(LPPOINT)0x0);
            LineTo(mem_dc,bounds.right,line_y);
          }
          SelectObject(mem_dc,old_obj);
        }
        old_obj = SelectObject(mem_dc,h_02);
        MoveToEx(mem_dc,bounds.left,bounds.bottom,(LPPOINT)0x0);
        LineTo(mem_dc,bounds.left,bounds.top);
        LineTo(mem_dc,bounds.right,bounds.top);
        MoveToEx(mem_dc,bounds.left + 1,bounds.bottom - 1,(LPPOINT)0x0);
        LineTo(mem_dc,bounds.left + 1,bounds.top + 1);
        LineTo(mem_dc,bounds.right - 1,bounds.top + 1);
        SelectObject(mem_dc,old_obj);
        bounds.left += 2;
        bounds.top += 2;
        text_rect.right = bounds.right;
        text_rect.bottom = bounds.bottom;
        draw_flags = 0x424;
        draw_rect = &text_rect;
        text_rect.left = bounds.left;
        text_rect.top = bounds.top;
        len = _strlen(label_text);
        DrawTextA(mem_dc,label_text,len,draw_rect,draw_flags);
        text_width = rect_width(&text_rect);
        text_bottom = bounds.bottom;
        value = rect_width(&bounds);
        value = (((value >> 1) + bounds.left) - (text_width >> 1)) + text_width;
        text_top = bounds.top;
        value2 = rect_width(&bounds);
        SetRect(&text_rect,((value2 >> 1) + bounds.left) - (text_width >> 1),text_top,value,text_bottom);
        draw_flags = 0x24;
        draw_rect = &text_rect;
        len = _strlen(label_text);
        DrawTextA(mem_dc,label_text,len,draw_rect,draw_flags);
        saved_left = text_rect.left;
        saved_top = text_rect.top;
        saved_right = text_rect.right;
        saved_bottom = text_rect.bottom;
        if (-1 < (int)button->hotkey_pos) {
          crt_strcpy(prefix,label_text);
          prefix[button->hotkey_pos] = '\0';
          len = _strlen(prefix);
          if (len == 0) {
            underline_start = text_rect.left;
          }
          else {
            text_rect.left = saved_left;
            text_rect.top = saved_top;
            text_rect.right = saved_right;
            text_rect.bottom = saved_bottom;
            draw_flags = 0x424;
            draw_rect = &text_rect;
            len = _strlen(prefix);
            DrawTextA(mem_dc,prefix,len,draw_rect,draw_flags);
            underline_start = text_rect.right - 1;
          }
          crt_strcpy(prefix,label_text);
          prefix[button->hotkey_pos + 1] = '\0';
          text_rect.left = saved_left;
          text_rect.top = saved_top;
          text_rect.right = saved_right;
          text_rect.bottom = saved_bottom;
          draw_flags = 0x424;
          draw_rect = &text_rect;
          len = _strlen(prefix);
          DrawTextA(mem_dc,prefix,len,draw_rect,draw_flags);
          text_width = (text_rect.right + 1) - underline_start;
          underline_start = underline_start + (text_width >> 1) - 5;
          underline_end = underline_start + 10;
          SelectObject(mem_dc,h_02);
          MoveToEx(mem_dc,underline_start,text_rect.bottom - 2,(LPPOINT)0x0);
          LineTo(mem_dc,underline_end,text_rect.bottom - 2);
          MoveToEx(mem_dc,underline_start,text_rect.bottom - 1,(LPPOINT)0x0);
          LineTo(mem_dc,underline_end,text_rect.bottom - 1);
          SelectObject(mem_dc,old_obj);
        }
        SelectObject(mem_dc,bmp_disabled);
        bounds.left = orig_left;
        bounds.top = orig_top;
        bounds.right = orig_right;
        bounds.bottom = orig_bottom;
        if (button->on_select == 0xffffffff) {
          FillRect(mem_dc,&bounds,bg_pen);
        }
        else {
          old_obj = SelectObject(mem_dc,bg_pen);
          for (line_y = bounds.top; line_y < bounds.bottom; line_y++) {
            MoveToEx(mem_dc,bounds.left,line_y,(LPPOINT)0x0);
            LineTo(mem_dc,bounds.right,line_y);
          }
          SelectObject(mem_dc,old_obj);
        }
        old_obj = SelectObject(mem_dc,h_01);
        MoveToEx(mem_dc,bounds.left,bounds.bottom,(LPPOINT)0x0);
        LineTo(mem_dc,bounds.left,bounds.top);
        LineTo(mem_dc,bounds.right,bounds.top);
        MoveToEx(mem_dc,bounds.left + 1,bounds.bottom - 1,(LPPOINT)0x0);
        LineTo(mem_dc,bounds.left + 1,bounds.top + 1);
        LineTo(mem_dc,bounds.right - 1,bounds.top + 1);
        SelectObject(mem_dc,h_02);
        MoveToEx(mem_dc,bounds.left + 1,bounds.bottom - 1,(LPPOINT)0x0);
        LineTo(mem_dc,bounds.right - 1,bounds.bottom - 1);
        LineTo(mem_dc,bounds.right - 1,bounds.top);
        MoveToEx(mem_dc,bounds.left + 2,bounds.bottom - 2,(LPPOINT)0x0);
        LineTo(mem_dc,bounds.right - 2,bounds.bottom - 2);
        LineTo(mem_dc,bounds.right - 2,bounds.top + 1);
        SelectObject(mem_dc,old_obj);
        text_rect.left = bounds.left;
        text_rect.top = bounds.top;
        text_rect.right = bounds.right;
        text_rect.bottom = bounds.bottom;
        draw_flags = 0x424;
        draw_rect = &text_rect;
        len = _strlen(label_text);
        DrawTextA(mem_dc,label_text,len,draw_rect,draw_flags);
        text_width = rect_width(&text_rect);
        text_bottom = bounds.bottom;
        value = rect_width(&bounds);
        value = (((value >> 1) + bounds.left) - (text_width >> 1)) + text_width;
        text_top = bounds.top;
        value2 = rect_width(&bounds);
        SetRect(&text_rect,((value2 >> 1) + bounds.left) - (text_width >> 1),text_top,value,text_bottom);
        SetTextColor(mem_dc,0xffffff);
        draw_flags = 0x24;
        draw_rect = &text_rect;
        len = _strlen(label_text);
        DrawTextA(mem_dc,label_text,len,draw_rect,draw_flags);
        OffsetRect(&text_rect,-1,-1);
        SetTextColor(mem_dc,0x808080);
        draw_flags = 0x24;
        draw_rect = &text_rect;
        len = _strlen(label_text);
        DrawTextA(mem_dc,label_text,len,draw_rect,draw_flags);
        OffsetRect(&text_rect,1,1);
        saved_left = text_rect.left;
        saved_top = text_rect.top;
        saved_right = text_rect.right;
        saved_bottom = text_rect.bottom;
        if (-1 < (int)button->hotkey_pos) {
          crt_strcpy(prefix,label_text);
          prefix[button->hotkey_pos] = '\0';
          len = _strlen(prefix);
          if (len == 0) {
            underline_start = text_rect.left;
          }
          else {
            text_rect.left = saved_left;
            text_rect.top = saved_top;
            text_rect.right = saved_right;
            text_rect.bottom = saved_bottom;
            draw_flags = 0x424;
            draw_rect = &text_rect;
            len = _strlen(prefix);
            DrawTextA(mem_dc,prefix,len,draw_rect,draw_flags);
            underline_start = text_rect.right - 1;
          }
          crt_strcpy(prefix,label_text);
          prefix[button->hotkey_pos + 1] = '\0';
          text_rect.left = saved_left;
          text_rect.top = saved_top;
          text_rect.right = saved_right;
          text_rect.bottom = saved_bottom;
          draw_flags = 0x424;
          draw_rect = &text_rect;
          len = _strlen(prefix);
          DrawTextA(mem_dc,prefix,len,draw_rect,draw_flags);
          text_width = (text_rect.right + 1) - underline_start;
          underline_start = underline_start + (text_width >> 1) - 5;
          underline_end = underline_start + 10;
          SelectObject(mem_dc,h_02);
          MoveToEx(mem_dc,underline_start,text_rect.bottom - 2,(LPPOINT)0x0);
          LineTo(mem_dc,underline_end,text_rect.bottom - 2);
          MoveToEx(mem_dc,underline_start,text_rect.bottom - 1,(LPPOINT)0x0);
          LineTo(mem_dc,underline_end,text_rect.bottom - 1);
          SelectObject(mem_dc,old_obj);
        }
        SelectObject(mem_dc,h_04);
        SelectObject(mem_dc,h_03);
        DeleteObject(h_01);
        if (button->on_select != 0xffffffff) {
          DeleteObject(bg_pen);
        }
        DeleteObject(h_02);
        DeleteDC(mem_dc);
        value = (iptr)ctrl_init_block(hwnd2,ctrl);
        *(HBITMAP *)(value + 0xc) = h;
        *(HBITMAP *)(value + 0x10) = h_00;
        *(HBITMAP *)(value + 0x14) = bmp_disabled;
        *(i32 *)(value + 0x2c) = 6;
        SetWindowLongA(hwnd2,-4,(iptr)button_wndproc);
      }
    }
  }
  return hwnd2;
}

/* 005cac22 auto */
void __cdecl button_press_animated(HWND hwnd)

{
  Button *self;
  ControlBlock *block;
  int enabled;
  i32 ctrl_id;
  
  block = wnd_from_hwnd(hwnd);
  if (block != 0) {
    self = (Button *)block->owner;
    enabled = ctrl_is_enabled(self);
    if (enabled != 0) {
      SetFocus(hwnd);
      block->pressed = 1;
      wnd_redraw_client(hwnd);
      block->pressed = 0;
      ui_pump_messages();
      ui_wait_ticks(8);
      wnd_redraw_client(hwnd);
      wnd_active_child = ctrl_get_parent(self);
      ctrl_id = ctrl_get_id(self);
      button_fire_callback(self,ctrl_id);
    }
  }
  return;
}

/* 005cacd4: written by hand in src/game/fixups.cpp */

/* 005cb601 auto */
HWND __cdecl spritebtn_create_hwnd(int x,int y,int width,int height,iptr ctrl,int visible)

{
  WndBase *self;
  NativeWindow *window;
  iptr rect_h;
  int value;
  HWND hWndParent;
  HMENU hMenu;
  HINSTANCE hInstance;
  LPVOID lpParam;
  DWORD style2;
  tagRECT rect;
  iptr owner2;
  HWND hwnd2;
  
  style2 = 0x40810000;
  if (visible != 0) {
    style2 = 0x50810000;
  }
  owner2 = ctrl;
  SetRect(&rect,x,y,x + width,y + height);
  lpParam = (LPVOID)0x0;
  hMenu = (HMENU)0x0;
  hInstance = err_report_ctx_block.app_hinstance;
  self = (WndBase *)ctrl_get_parent((Control *)ctrl);
  window = wnd_get_window(self);
  hWndParent = window->hwnd;
  rect_h = rect_height(&rect);
  value = rect_width(&rect);
  hwnd2 = CreateWindowExA(4,str_mscontrolclass_3,((i8 *)&spritebtn_wnd_title),style2,x,y,value
                            ,rect_h,hWndParent,hMenu,hInstance,lpParam);
  value = (iptr)ctrl_init_block(hwnd2,ctrl);
  *(i32 *)(value + 0x2c) = 5;
  SetWindowLongA(hwnd2,-4,(iptr)spritebtn_wndproc);
  return hwnd2;
}

/* 005cb6db auto */
void __cdecl spritebtn_hwnd_cleanup_stub(i32 hwnd)

{
  return;
}

/* 005cb6eb: written by hand in src/game/fixups.cpp */

/* 005cbdf0 auto */
void __thiscall button_fire_callback(Button *self,i32 ctrl_id)

{
  if (self->on_click != 0) {
    self->on_click(ctrl_id);
  }
  return;
}

/* 005cbe30 auto */
void __thiscall spritebtn_fire_click(SpriteButton *self,i32 ctrl_id)

{
  if (self->on_click != 0) {
    self->on_click(ctrl_id);
  }
  return;
}

/* 005cbe70 auto */
void __thiscall spritebtn_fire_rclick(SpriteButton *self,i32 ctrl_id)

{
  if (self->on_rclick != 0) {
    self->on_rclick(ctrl_id);
  }
  return;
}

/* 005cbf40 auto */
void __cdecl checkbox_calc_rect(char *label,int x,int y,iptr out_rect,GameFont *font)

{
  HDC hdc;
  HDC hdc_00;
  i32 font_handle;
  HGDIOBJ h;
  size_t c;
  tagSIZE *lpsz;
  int height2;
  tagSIZE text_size;
  tagTEXTMETRICA metrics;
  int width2;
  i32 *font_data;
  
  hdc = GetDC((HWND)0x0);
  hdc_00 = CreateCompatibleDC(hdc);
  ReleaseDC((HWND)0x0,hdc);
  font_handle = font_get_handle(font);
  font_data = (i32 *)mem_handle_lock(font_handle);
  h = SelectObject(hdc_00,(HGDIOBJ)*font_data);
  font_handle = font_get_handle(font);
  mem_handle_unlock(font_handle);
  GetTextMetricsA(hdc_00,&metrics);
  height2 = metrics.tmHeight;
  lpsz = &text_size;
  c = _strlen(label);
  GetTextExtentPointA(hdc_00,label,c,lpsz);
  width2 = text_size.cx;
  SelectObject(hdc_00,h);
  DeleteDC(hdc_00);
  width2 += 0x25;
  if (metrics.tmHeight < 0x14) {
    height2 = 0x14;
  }
  SetRect((LPRECT)out_rect,x,y,width2 + x,height2 + y);
  return;
}

/* 005cc035 auto */
void __cdecl checkbox_calc_rect_fixed(int x,int y,int width,iptr out_rect,GameFont *font)

{
  HDC hdc;
  HDC hdc_00;
  i32 font_handle;
  int height2;
  tagTEXTMETRICA metrics;
  i32 *font_data;
  
  hdc = GetDC((HWND)0x0);
  hdc_00 = CreateCompatibleDC(hdc);
  ReleaseDC((HWND)0x0,hdc);
  font_handle = font_get_handle(font);
  font_data = (i32 *)mem_handle_lock(font_handle);
  SelectObject(hdc_00,(HGDIOBJ)*font_data);
  font_handle = font_get_handle(font);
  mem_handle_unlock(font_handle);
  GetTextMetricsA(hdc_00,&metrics);
  height2 = metrics.tmHeight;
  DeleteDC(hdc_00);
  if (metrics.tmHeight < 0x14) {
    height2 = 0x14;
  }
  SetRect((LPRECT)out_rect,x,y,width + x,height2 + y);
  return;
}

/* 005cc0f0 auto */
HWND __cdecl checkbox_create_hwnd(RECT *rect,iptr ctrl,char *label,int visible)

{
  size_t len;
  void *label_copy;
  WndBase *self;
  NativeWindow *window;
  iptr height;
  int value;
  HWND check_hwnd;
  HBITMAP bmp_unchecked;
  HBITMAP bmp_checked;
  HBITMAP bmp_focus;
  HMENU hMenu;
  HINSTANCE hInstance;
  LPVOID lpParam;
  DWORD style2;
  
  len = _strlen(label);
  label_copy = operator_new(len + 1);
  crt_strcpy((char *)label_copy,label);
  style2 = 0x40010000;
  if (visible != 0) {
    style2 = 0x50010000;
  }
  lpParam = (LPVOID)0x0;
  hMenu = (HMENU)0x0;
  hInstance = err_report_ctx_block.app_hinstance;
  self = (WndBase *)ctrl_get_parent((Control *)ctrl);
  window = wnd_get_window(self);
  check_hwnd = window->hwnd;
  height = rect_height(rect);
  value = rect_width(rect);
  check_hwnd = CreateWindowExA(4,str_mscontrolclass_4,((i8 *)&wnd_modal_stack_below_block.checkbox_wnd_title),style2,rect->left,
                           rect->top,value,height,check_hwnd,hMenu,hInstance,lpParam);
  ctrl_parse_hotkey(ctrl,(const char *)label_copy);
  bmp_unchecked = LoadBitmapA(err_report_ctx_block.app_hinstance,(LPCSTR)0x132);
  bmp_checked = LoadBitmapA(err_report_ctx_block.app_hinstance,(LPCSTR)0x131);
  bmp_focus = LoadBitmapA(err_report_ctx_block.app_hinstance,(LPCSTR)0x130);
  value = (iptr)ctrl_init_block(check_hwnd,ctrl);
  *(HBITMAP *)(value + 0xc) = bmp_unchecked;
  *(HBITMAP *)(value + 0x10) = bmp_checked;
  *(HBITMAP *)(value + 0x14) = bmp_focus;
  *(i32 *)(value + 0x2c) = 2;
  *(void **)(value + 0x24) = label_copy;
  SetWindowLongA(check_hwnd,-4,(iptr)checkbox_wndproc);
  return check_hwnd;
}

/* 005cc248 auto */
void __cdecl checkbox_destroy_hwnd(int hwnd)

{
  if (hwnd == 0) {
    dbg_log((const char *)&str_error_tried_to_dispose_null_checkbox_in);
  }
  return;
}

/* 005cc274 auto */
void __cdecl checkbox_toggle_by_hotkey(HWND hwnd)

{
  Button *self;
  ControlBlock *block;
  int checked;
  i32 is_checked;
  i32 ctrl_id;
  
  block = wnd_from_hwnd(hwnd);
  if (block != 0) {
    self = (Button *)block->owner;
    SetFocus(hwnd);
    checked = checkbox_is_checked((Checkbox *)self);
    if (checked == 0) {
      checkbox_set_checked((Checkbox *)self,1);
    }
    else {
      checkbox_set_checked((Checkbox *)self,0);
    }
    SetCapture(hwnd);
    InvalidateRect(hwnd,(RECT *)0x0,0);
    wnd_active_child = ctrl_get_parent(self);
    is_checked = checkbox_is_checked((Checkbox *)self);
    ctrl_id = ctrl_get_id(self);
    checkbox_fire_callback((Checkbox *)self,ctrl_id,is_checked);
  }
  return;
}

/* 005cc320 auto */
i32 __stdcall checkbox_wndproc(HWND hwnd,uint msg,WPARAM wparam,LPARAM lparam)

{
  char nav_enabled;
  i32 ctrl_id;
  iptr enabled;
  iptr checked;
  int *ctrl_rect;
  int value;
  uint color_index;
  WndBase *parent_wnd;
  GamePalette *game_palette2;
  size_t len;
  WndBase *parent_base;
  iptr logpal;
  HWND hwnd_tmp;
  Wnd *nav_wnd;
  i32 result;
  i8 *red_out;
  i8 *green_out;
  tagRECT *draw_rect;
  i8 *blue_out;
  UINT draw_flags;
  tagRECT rect;
  HBITMAP bitmap;
  ControlBlock *block;
  Checkbox *checkbox;
  tagPAINTSTRUCT ps;
  HGDIOBJ old_font;
  tagSIZE bmp_size;
  i8 green[4];
  HDC hdc;
  char *label;
  int underline_end;
  int underline_start;
  int box_left;
  int box_top;
  int box_right;
  int box_bottom;
  i8 red[4];
  i8 blue[4];
  HBRUSH brush;
  i32 *font_data;
  char prefix[256];
  tagRECT text_rect;
  
  block = wnd_from_hwnd(hwnd);
  checkbox = (Checkbox *)block->owner;
  if (msg < 0x10) {
    if (msg == 0xf) {
      enabled = checkbox_is_enabled(checkbox);
      if (enabled == 0) {
        hwnd_tmp = GetFocus();
        if (hwnd_tmp == hwnd) {
          SetFocus((HWND)0x0);
        }
        bitmap = block->bitmaps[0];
      }
      else {
        checked = checkbox_is_checked(checkbox);
        if (checked == 0) {
          bitmap = block->bitmaps[1];
        }
        else {
          bitmap = block->bitmaps[2];
        }
      }
      GetBitmapDimensionEx(bitmap,&bmp_size);
      ctrl_rect = (int *)ctrl_get_rect(checkbox);
      rect.left = *ctrl_rect;
      rect.top = ctrl_rect[1];
      rect.right = ctrl_rect[2];
      rect.bottom = ctrl_rect[3];
      box_left = rect.left;
      box_top = rect.top;
      box_right = rect.right;
      box_bottom = rect.bottom;
      if (wnd_modal_stack_below_block.checkbox_mouse_pressed != 0) {
        box_right = rect.left + 0x20;
        value = rect_height(&rect);
        box_top = value - 0x14 + rect.top >> 1;
        box_bottom = rect.top + 0x14;
      }
      OffsetRect(&rect,-rect.left,-rect.top);
      hdc = BeginPaint(hwnd,&ps);
      ctrl_paint_parent_bkgnd((iptr)&ps,hwnd);
      result = font_get_handle((GameFont *)checkbox->font);
      font_data = (i32 *)mem_handle_lock(result);
      old_font = SelectObject(hdc,(HGDIOBJ)*font_data);
      result = font_get_handle((GameFont *)checkbox->font);
      mem_handle_unlock(result);
      SetBkMode(hdc,1);
      gdi_blit_transparent(hdc,bitmap,rect.left,rect.bottom - 0x14 >> 1,0x20,0x14,0,7);
      rect.left += 0x25;
      label = (char *)block->data;
      if ((ctrl_shadow_dx != 0) || (ctrl_shadow_dy != 0)) {
        OffsetRect(&rect,(uint)ctrl_shadow_dx,(uint)ctrl_shadow_dy);
        blue_out = blue;
        green_out = green;
        red_out = red;
        color_index = (uint)ctrl_shadow_color_index;
        parent_wnd = (WndBase *)ctrl_get_parent(checkbox);
        game_palette2 = (GamePalette *)wnd_get_palette(parent_wnd);
        palette_get_entry(game_palette2,color_index,(iptr)red_out,(iptr)green_out,(iptr)blue_out);
        SetTextColor(hdc,CONCAT12(blue[0],CONCAT11(green[0],red[0])));
        draw_flags = 0x24;
        draw_rect = &rect;
        len = _strlen(label);
        DrawTextA(hdc,label,len,draw_rect,draw_flags);
        OffsetRect(&rect,-(uint)ctrl_shadow_dx,-(uint)ctrl_shadow_dy);
      }
      value = checkbox_is_enabled(checkbox);
      if (value == 1) {
        parent_base = (WndBase *)ctrl_get_parent(checkbox);
        value = (int)wnd_get_window(parent_base);
        if (((NativeWindow *)value)->field_40 == 8) {
          if (ctrl_text_color_index == 0) {
            SetTextColor(hdc,0);
          }
          else {
            blue_out = blue;
            green_out = green;
            red_out = red;
            color_index = (uint)ctrl_text_color_index;
            parent_wnd = (WndBase *)ctrl_get_parent(checkbox);
            game_palette2 = (GamePalette *)wnd_get_palette(parent_wnd);
            logpal = (iptr)palette_get_logpalette(game_palette2);
            palette_get_entry_rgb((GameLogPalette *)logpal,color_index,(iptr)red_out,(iptr)green_out,(iptr)blue_out);
            SetTextColor(hdc,CONCAT12(blue[0],CONCAT11(green[0],red[0])))
            ;
          }
        }
        else if (wnd_modal_stack_below_block.ctrl_text_rgb_set == '\0') {
          SetTextColor(hdc,0);
        }
        else {
          SetTextColor(hdc,CONCAT12(wnd_modal_stack_below_block.ctrl_text_rgb_b,CONCAT11(wnd_modal_stack_below_block.ctrl_text_rgb_g,wnd_modal_stack_below_block.ctrl_text_rgb_r)));
        }
      }
      else {
        value = checkbox_is_enabled(checkbox);
        if (value == 0) {
          parent_base = (WndBase *)ctrl_get_parent(checkbox);
          value = (int)wnd_get_window(parent_base);
          if (((NativeWindow *)value)->field_40 == 8) {
            if (ctrl_disabled_color_index == 0) {
              SetTextColor(hdc,0x404040);
            }
            else {
              blue_out = blue;
              green_out = green;
              red_out = red;
              color_index = (uint)ctrl_disabled_color_index;
              parent_wnd = (WndBase *)ctrl_get_parent(checkbox);
              game_palette2 = (GamePalette *)wnd_get_palette(parent_wnd);
              logpal = (iptr)palette_get_logpalette(game_palette2);
              palette_get_entry_rgb((GameLogPalette *)logpal,color_index,(iptr)red_out,(iptr)green_out,(iptr)blue_out);
              SetTextColor(hdc,
                           CONCAT12(blue[0],CONCAT11(green[0],red[0])));
            }
          }
          else if (wnd_modal_stack_below_block.ctrl_disabled_rgb_set == '\0') {
            SetTextColor(hdc,0x404040);
          }
          else {
            SetTextColor(hdc,CONCAT12(wnd_modal_stack_below_block.ctrl_disabled_rgb_b,CONCAT11(wnd_modal_stack_below_block.ctrl_disabled_rgb_g,wnd_modal_stack_below_block.ctrl_disabled_rgb_r)))
            ;
          }
        }
      }
      draw_flags = 0x24;
      draw_rect = &rect;
      len = _strlen(label);
      DrawTextA(hdc,label,len,draw_rect,draw_flags);
      if (checkbox->hotkey_pos != 0xffffffff) {
        crt_strcpy(prefix,label);
        prefix[checkbox->hotkey_pos] = '\0';
        text_rect.left = rect.left;
        text_rect.top = rect.top;
        text_rect.right = rect.right;
        text_rect.bottom = rect.bottom;
        len = _strlen(prefix);
        if (len == 0) {
          underline_start = text_rect.left;
        }
        else {
          draw_flags = 0x424;
          draw_rect = &text_rect;
          len = _strlen(prefix);
          DrawTextA(hdc,prefix,len,draw_rect,draw_flags);
          underline_start = text_rect.right - 1;
        }
        crt_strcpy(prefix,label);
        prefix[checkbox->hotkey_pos + 1] = '\0';
        text_rect.left = rect.left;
        text_rect.top = rect.top;
        text_rect.right = rect.right;
        text_rect.bottom = rect.bottom;
        draw_flags = 0x424;
        draw_rect = &text_rect;
        len = _strlen(prefix);
        DrawTextA(hdc,prefix,len,draw_rect,draw_flags);
        underline_start = underline_start + ((text_rect.right + 1) - underline_start >> 1) - 5;
        underline_end = underline_start + 10;
        brush = GetStockObject(3);
        SelectObject(hdc,brush);
        MoveToEx(hdc,underline_start,rect.bottom - 3,(LPPOINT)0x0);
        LineTo(hdc,underline_end,rect.bottom - 3);
        MoveToEx(hdc,underline_start,rect.bottom - 2,(LPPOINT)0x0);
        LineTo(hdc,underline_end,rect.bottom - 2);
      }
      SelectObject(hdc,old_font);
      EndPaint(hwnd,&ps);
      hwnd_tmp = GetFocus();
      if (hwnd_tmp != hwnd) {
        return 0;
      }
    }
    else if (msg != 7) {
      if (msg == 8) {
        wnd_redraw_client(hwnd);
        return 0;
      }
default_proc:
      result = ctrl_default_wndproc(hwnd,msg,wparam,lparam);
      return result;
    }
    nav_wnd = (Wnd *)ctrl_get_parent(checkbox);
    nav_enabled = wnd_keyboard_nav_enabled(nav_wnd);
    if (nav_enabled == '\0') {
      result = ctrl_default_wndproc(hwnd,msg,wparam,lparam);
      return result;
    }
    hdc = GetDC(hwnd);
    brush = GetStockObject(3);
    GetClientRect(hwnd,&rect);
    SelectObject(hdc,brush);
    rect.left += 0x20;
    FrameRect(hdc,&rect,brush);
    DeleteObject(brush);
    ReleaseDC(hwnd,hdc);
  }
  else if (msg == 0x100) {
    if (wparam == 9) {
      hwnd_tmp = GetParent(hwnd);
      SendMessageA(hwnd_tmp,msg,wparam,lparam);
    }
    else {
      if (wparam == 0x20) {
        nav_wnd = (Wnd *)ctrl_get_parent(checkbox);
        nav_enabled = wnd_keyboard_nav_enabled(nav_wnd);
        if (nav_enabled != '\0') {
          SendMessageA(hwnd,0x201,0,0);
          SendMessageA(hwnd,0x202,0,0);
          return 0;
        }
      }
      hwnd_tmp = GetParent(hwnd);
      SendMessageA(hwnd_tmp,msg,wparam,lparam);
    }
  }
  else if (msg == 0x201) {
    value = checkbox_is_enabled(checkbox);
    if ((value != 0) && (wnd_modal_stack_below_block.checkbox_mouse_pressed == 0)) {
      SetFocus(hwnd);
      value = checkbox_is_checked(checkbox);
      if (value == 0) {
        checkbox_set_checked(checkbox,1);
      }
      else {
        checkbox_set_checked(checkbox,0);
      }
      wnd_modal_stack_below_block.checkbox_mouse_pressed = 1;
      SetCapture(hwnd);
      InvalidateRect(hwnd,(RECT *)0x0,0);
      logpal = ctrl_get_parent(checkbox);
      wnd_set_active_child(logpal);
      result = checkbox_is_checked(checkbox);
      ctrl_id = ctrl_get_id(checkbox);
      checkbox_fire_callback(checkbox,ctrl_id,result);
    }
  }
  else {
    if (msg != 0x202) goto default_proc;
    value = checkbox_is_enabled(checkbox);
    if (value != 0) {
      ReleaseCapture();
      wnd_modal_stack_below_block.checkbox_mouse_pressed = 0;
    }
  }
  return 0;
}

/* 005cce40 auto */
void __thiscall checkbox_fire_callback(Checkbox *self,i32 ctrl_id,i32 checked)

{
  if (self->on_toggle != 0) {
    self->on_toggle(ctrl_id,checked);
  }
  return;
}

/* 005cce80 auto */
void __stdcall control_subclass_wndproc(HWND hwnd,int msg,i32 wparam,i32 lparam)

{
  DWORD class_extra;
  WNDPROC base_proc;
  Control *self;
  
  class_extra = GetClassLongA(hwnd,-0x12);
  base_proc = (WNDPROC)GetWindowLongA(hwnd,class_extra - 4);
  if ((msg == 2) &&
     (self = (Control *)GetWindowLongA(hwnd,class_extra - 8), self != (Control *)0x0)) {
    control_set_hwnd(self,0);
  }
  (*base_proc)(hwnd,msg,wparam,lparam);
  return;
}

/* 005ccf17 auto */
HWND __cdecl scrollbar_create_hwnd(int *rect,iptr ctrl,uint style_flags,int visible)

{
  WndBase *parent_wnd;
  NativeWindow *window;
  iptr height;
  int value;
  int nWidth;
  HWND parent_hwnd;
  HMENU menu;
  HINSTANCE hinst;
  LPVOID create_param;
  uint style2;
  WNDCLASSA wc;
  HWND hwnd2;
  
  style2 = 0x40000000;
  if (visible != 0) {
    style2 = 0x50000000;
  }
  if (style_flags != 0) {
    style2 = style2 | 1;
  }
  if (visible != 0) {
    style_flags = style_flags | 0x10000000;
  }
  if (scrollbar_class_registered == 0) {
    create_param = (LPVOID)0x0;
    menu = (HMENU)0x0;
    hinst = err_report_ctx_block.app_hinstance;
    parent_wnd = (WndBase *)ctrl_get_parent((Control *)ctrl);
    window = wnd_get_window(parent_wnd);
    parent_hwnd = window->hwnd;
    height = rect_height((RECT *)rect);
    value = rect_width((RECT *)rect);
    hwnd2 = CreateWindowExA(4,str_scrollbar,((i8 *)&scrollbar_probe_wnd_title),style_flags | 0x40000000,*rect,
                              rect[1],value,height,parent_hwnd,menu,hinst,create_param);
    default_draw_font_obj_block.scrollbar_base_wndproc = (WNDPROC)GetWindowLongA(hwnd2,-4);
    style2 = GetWindowLongA(hwnd2,-0x10);
    wc.style = 0x8b;
    wc.lpfnWndProc = default_draw_font_obj_block.scrollbar_base_wndproc;
    wc.cbClsExtra = 0;
    default_draw_font_obj_block.scrollbar_base_wnd_extra = GetClassLongA(hwnd2,-0x12);
    wc.cbWndExtra = default_draw_font_obj_block.scrollbar_base_wnd_extra + 8;
    wc.hInstance = err_report_ctx_block.app_hinstance;
    wc.hIcon = (HICON)0x0;
    wc.hCursor = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
    wc.hbrBackground = GetStockObject(1);
    wc.lpszMenuName = (LPCSTR)0x0;
    wc.lpszClassName = str_msscrollbarclass;
    RegisterClassA(&wc);
    scrollbar_class_registered = 1;
    DestroyWindow(hwnd2);
  }
  create_param = (LPVOID)0x0;
  menu = (HMENU)0x0;
  hinst = err_report_ctx_block.app_hinstance;
  parent_wnd = (WndBase *)ctrl_get_parent((Control *)ctrl);
  value = (int)wnd_get_window(parent_wnd);
  parent_hwnd = ((NativeWindow *)value)->hwnd;
  value = rect_height((RECT *)rect);
  nWidth = rect_width((RECT *)rect);
  hwnd2 = CreateWindowExA(4,str_msscrollbarclass_2,((i8 *)&scrollbar_wnd_title),style2,*rect,rect[1]
                            ,nWidth,value,parent_hwnd,menu,hinst,create_param);
  SetWindowLongA(hwnd2,-4,(iptr)control_subclass_wndproc);
  SetWindowLongA(hwnd2,default_draw_font_obj_block.scrollbar_base_wnd_extra,ctrl);
  SetWindowLongA(hwnd2,default_draw_font_obj_block.scrollbar_base_wnd_extra + 4,(LONG)default_draw_font_obj_block.scrollbar_base_wndproc);
  ShowScrollBar(hwnd2,2,1);
  scrollbar_hwnd_set_range(hwnd2,1,100);
  return hwnd2;
}

/* 005cd139 auto */
void __cdecl scrollbar_destroy_hwnd(i32 hwnd)

{
  return;
}

/* 005cd149 auto */
void __cdecl scrollbar_hwnd_handle_msg(HWND hwnd,uint msg,uint wparam,int lparam)

{
  short thumb_pos;
  DWORD class_extra;
  Scrollbar *self;
  iptr cur_pos;
  iptr parent;
  WPARAM *rect_ptr;
  iptr page_size;
  int value;
  u32 new_pos;
  LPARAM pos_lparam;
  
  class_extra = GetClassLongA(hwnd,-0x12);
  self = (Scrollbar *)GetWindowLongA(hwnd,class_extra - 8);
  cur_pos = scrollbar_get_cur_pos(self);
  if (msg == 0x111) {
    if (wparam == 0x7f) {
      SetScrollPos(hwnd,2,lparam,1);
      new_pos = GetScrollPos(hwnd,2);
      self->cur_pos = new_pos;
    }
  }
  else if ((0x113 < msg) && (msg < 0x116)) {
    thumb_pos = (short)(wparam >> 0x10);
    switch(wparam & 0xffff) {
    case 0:
      value = input_lbutton_down();
      if (value == 0) {
        value = ctrl_get_rect(self);
        pos_lparam = *(LPARAM *)(value + 4);
        rect_ptr = (WPARAM *)ctrl_get_rect(self);
        PostMessageA(hwnd,0x202,*rect_ptr,pos_lparam);
      }
      else {
        SetScrollPos(hwnd,2,cur_pos - 1,1);
        new_pos = GetScrollPos(hwnd,2);
        parent = ctrl_get_parent(self);
        wnd_set_active_child(parent);
        self->cur_pos = new_pos;
        scrollbar_fire_change(self,new_pos);
      }
      break;
    case 1:
      value = input_lbutton_down();
      if (value == 0) {
        value = ctrl_get_rect(self);
        pos_lparam = *(LPARAM *)(value + 4);
        rect_ptr = (WPARAM *)ctrl_get_rect(self);
        PostMessageA(hwnd,0x202,*rect_ptr,pos_lparam);
      }
      else {
        SetScrollPos(hwnd,2,cur_pos + 1,1);
        new_pos = GetScrollPos(hwnd,2);
        parent = ctrl_get_parent(self);
        wnd_set_active_child(parent);
        self->cur_pos = new_pos;
        scrollbar_fire_change(self,new_pos);
      }
      break;
    case 2:
      value = scrollbar_get_page_size(self);
      SetScrollPos(hwnd,2,cur_pos - value,1);
      new_pos = GetScrollPos(hwnd,2);
      parent = ctrl_get_parent(self);
      wnd_set_active_child(parent);
      self->cur_pos = new_pos;
      scrollbar_fire_change(self,new_pos);
      break;
    case 3:
      page_size = scrollbar_get_page_size(self);
      SetScrollPos(hwnd,2,cur_pos + page_size,1);
      new_pos = GetScrollPos(hwnd,2);
      parent = ctrl_get_parent(self);
      wnd_set_active_child(parent);
      self->cur_pos = new_pos;
      scrollbar_fire_change(self,new_pos);
      break;
    case 4:
      SetScrollPos(hwnd,2,(int)thumb_pos,1);
      parent = ctrl_get_parent(self);
      wnd_set_active_child(parent);
      self->cur_pos = (int)thumb_pos;
      scrollbar_fire_change(self,self->cur_pos);
      break;
    case 5:
      parent = ctrl_get_parent(self);
      wnd_set_active_child(parent);
      scrollbar_fire_track(self,(int)thumb_pos);
    }
  }
  return;
}

/* 005cd4c7 auto */
void __cdecl scrollbar_hwnd_set_range(HWND hwnd,int min_pos,int max_pos)

{
  SetScrollRange(hwnd,2,min_pos,max_pos,1);
  scrollbar_hwnd_set_pos(hwnd,min_pos);
  return;
}

/* 005cd535 auto */
void __cdecl scrollbar_hwnd_get_range(HWND hwnd,LPINT min_out,LPINT max_out)

{
  GetScrollRange(hwnd,2,min_out,max_out);
  return;
}

/* 005cd559 auto */
void __cdecl scrollbar_hwnd_set_pos(i32 hwnd,i32 pos)

{
  scrollbar_hwnd_handle_msg(hwnd,0x111,0x7f,pos);
  return;
}

/* 005cd620 auto */
u32 __thiscall scrollbar_get_cur_pos(Scrollbar *self)

{
  return self->cur_pos;
}

/* 005cd640 auto */
void __thiscall scrollbar_fire_change(Scrollbar *self,i32 pos)

{
  if (self->on_change != 0) {
    self->on_change(pos);
  }
  return;
}

/* 005cd680 auto */
void __thiscall scrollbar_fire_track(Scrollbar *self,i32 pos)

{
  if (self->on_track != 0) {
    self->on_track(pos);
  }
  return;
}

/* 005cd6c0 auto */
u32 __thiscall scrollbar_get_page_size(Scrollbar *self)

{
  return self->page_size;
}

/* 005d25c0 auto */
void __thiscall
edit_create_at
          (EditControl *self,iptr parent,i32 ctrl_id,int x,int y,int width,
          const char *text)

{
  tagRECT rect;
  
  self->edit_font = (u32)(*(i8 * *)(draw_current_font_rest + 12));
  self->on_change = 0;
  SetRect(&rect,x,y,width + x,y + 0x1e);
  edit_create(self,parent,ctrl_id,(iptr)&rect,text);
  return;
}

/* 005d2740 auto */
HWND __cdecl edit_create_window(int *rect,iptr ctrl,uint flags,int visible,GameFont *font)

{
  WndBase *parent_wnd;
  NativeWindow *window;
  iptr height;
  int value;
  int nWidth;
  i32 font_handle;
  WPARAM *font_ptr;
  HWND parent_hwnd;
  HMENU menu;
  HINSTANCE hinst;
  LPVOID create_param;
  WNDCLASSA wc;
  HWND hwnd2;
  uint style2;
  
  style2 = 0x40800000;
  if (visible != 0) {
    style2 = 0x50800000;
  }
  if ((flags & 1) != 0) {
    style2 = style2 | 0x80;
  }
  if (((flags & 2) != 0) || ((flags & 0x200) != 0)) {
    style2 = style2 | 4;
    *(i8 *)(ctrl + 0x38) = 1;
    if ((flags & 0x200) != 0) {
      *(i8 *)(ctrl + 0x39) = 1;
    }
  }
  if ((flags & 4) != 0) {
    style2 = style2 | 0xa0;
  }
  if ((flags & 8) != 0) {
    style2 = style2 | 8;
  }
  if ((flags & 0x10) != 0) {
    style2 = style2 | 0x10;
  }
  if ((flags & 0x20) != 0) {
    style2 = style2 | 0x200040;
  }
  if ((flags & 0x40) != 0) {
    style2 = style2 | 0x100080;
  }
  if ((flags & 0x80) != 0) {
    style2 = style2 | 0x1000;
  }
  if ((flags & 0x100) != 0) {
    style2 = style2 | 0x800;
  }
  *(uint *)(ctrl + 0x3c) = style2;
  if (editbox_class_registered == 0) {
    create_param = (LPVOID)0x0;
    menu = (HMENU)0x0;
    hinst = err_report_ctx_block.app_hinstance;
    parent_wnd = (WndBase *)ctrl_get_parent((Control *)ctrl);
    window = wnd_get_window(parent_wnd);
    parent_hwnd = window->hwnd;
    height = rect_height((RECT *)rect);
    value = rect_width((RECT *)rect);
    hwnd2 = CreateWindowExA(4,((i8 *)&editbox_native_class_name),((i8 *)&editbox_probe_wnd_title),style2,*rect,rect[1],value,height,
                              parent_hwnd,menu,hinst,create_param);
    default_draw_font_obj_block.edit_base_wndproc = (WNDPROC)GetWindowLongA(hwnd2,-4);
    wc.style = 0x88;
    wc.cbClsExtra = 0;
    wc.lpfnWndProc = default_draw_font_obj_block.edit_base_wndproc;
    default_draw_font_obj_block.edit_base_wnd_extra = GetClassLongA(hwnd2,-0x12);
    wc.cbWndExtra = default_draw_font_obj_block.edit_base_wnd_extra + 8;
    wc.hInstance = err_report_ctx_block.app_hinstance;
    wc.hIcon = (HICON)0x0;
    wc.hCursor = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f01);
    wc.hbrBackground = (HBRUSH)0x0;
    wc.lpszMenuName = (LPCSTR)0x0;
    wc.lpszClassName = str_mseditboxclass;
    RegisterClassA(&wc);
    editbox_class_registered = 1;
    DestroyWindow(hwnd2);
  }
  create_param = (LPVOID)0x0;
  menu = (HMENU)0x0;
  hinst = err_report_ctx_block.app_hinstance;
  parent_wnd = (WndBase *)ctrl_get_parent((Control *)ctrl);
  value = (int)wnd_get_window(parent_wnd);
  parent_hwnd = ((NativeWindow *)value)->hwnd;
  value = rect_height((RECT *)rect);
  nWidth = rect_width((RECT *)rect);
  hwnd2 = CreateWindowExA(4,str_mseditboxclass_2,((i8 *)&editbox_wnd_title),style2 | 0x40800000,*rect,
                            rect[1],nWidth,value,parent_hwnd,menu,hinst,create_param);
  font_handle = font_get_handle(font);
  font_ptr = (WPARAM *)mem_handle_lock(font_handle);
  SendMessageA(hwnd2,0x30,*font_ptr,0);
  font_handle = font_get_handle(font);
  mem_handle_unlock(font_handle);
  SetWindowLongA(hwnd2,-4,(iptr)edit_subclass_wndproc);
  SetWindowLongA(hwnd2,default_draw_font_obj_block.edit_base_wnd_extra,(LONG)default_draw_font_obj_block.edit_base_wndproc);
  SetWindowLongA(hwnd2,default_draw_font_obj_block.edit_base_wnd_extra + 4,ctrl);
  return hwnd2;
}

/* 005d2a01 auto */
LRESULT __stdcall edit_subclass_wndproc(HWND hwnd,uint msg,WPARAM wparam,LPARAM lparam)

{
  Button *self;
  DWORD class_extra;
  WNDPROC lpPrevWndFunc;
  iptr key;
  HWND parent_hwnd;
  iptr parent;
  WndBase *this_00;
  NativeWindow *window;
  LRESULT result;
  iptr long_index;
  int pass_through;
  
  self = (Button *)GetWindowLongA(hwnd,10);
  class_extra = GetClassLongA(hwnd,-0x12);
  lpPrevWndFunc = (WNDPROC)GetWindowLongA(hwnd,class_extra - 8);
  if (msg < 8) {
    if (msg == 7) {
      parent = ctrl_get_parent(self);
      wnd_set_active_child(parent);
      if ((char)self->font == '\0') {
        edit_hwnd_set_sel(hwnd,0,0xffffffff);
      }
      result = CallWindowProcA(lpPrevWndFunc,hwnd,7,wparam,lparam);
      return result;
    }
    if (msg == 2) {
      if (self != (Button *)0x0) {
        control_set_hwnd(self,0);
      }
      result = CallWindowProcA(lpPrevWndFunc,hwnd,2,wparam,lparam);
      return result;
    }
  }
  else if (msg < 0x202) {
    if (msg == 0x201) {
click_focus_parent:
      long_index = 0;
      parent_hwnd = GetParent(hwnd);
      this_00 = (WndBase *)GetWindowLongA(parent_hwnd,long_index);
      window = wnd_get_window(this_00);
      if ((window->flags_bytes[1] & 2) != 0) {
        parent_hwnd = GetParent(hwnd);
        SetFocus(parent_hwnd);
        parent_hwnd = GetParent(hwnd);
        BringWindowToTop(parent_hwnd);
      }
      result = CallWindowProcA(lpPrevWndFunc,hwnd,msg,wparam,lparam);
      return result;
    }
    if (msg == 0x100) {
      if (((wparam != 9) && (wparam != 0xd)) && (wparam != 0x1b)) {
        result = CallWindowProcA(lpPrevWndFunc,hwnd,0x100,wparam,lparam);
        return result;
      }
      parent_hwnd = GetParent(hwnd);
      SendMessageA(parent_hwnd,msg,wparam,lparam);
      return 1;
    }
    if (msg == 0x101) {
      parent = ctrl_get_parent(self);
      wnd_set_active_child(parent);
      key = input_map_vkey(wparam);
      if ((0x2af < key) && (key < 0x2b5)) {
        edit_fire_key_callback((EditControl *)self,key);
      }
      result = CallWindowProcA(lpPrevWndFunc,hwnd,0x101,wparam,lparam);
      return result;
    }
    if (msg == 0x102) {
      parent = ctrl_get_parent(self);
      wnd_set_active_child(parent);
      pass_through = 0;
      if (wparam != 9) {
        parent = input_map_vkey(wparam);
        pass_through = edit_fire_key_callback((EditControl *)self,parent);
      }
      if (pass_through == 0) {
        return 1;
      }
      result = CallWindowProcA(lpPrevWndFunc,hwnd,0x102,wparam,lparam);
      return result;
    }
  }
  else if (msg == 0x204) goto click_focus_parent;
  result = CallWindowProcA(lpPrevWndFunc,hwnd,msg,wparam,lparam);
  return result;
}

/* 005d2d3d auto */
void __cdecl edit_hwnd_cleanup_stub(i32 hwnd)

{
  return;
}

/* 005d2da1 auto */
void __cdecl edit_hwnd_limit_text(HWND hwnd,WPARAM max_len)

{
  SendMessageA(hwnd,0xc5,max_len,0);
  return;
}

/* 005d2dc6 auto */
void __cdecl edit_hwnd_set_sel(HWND hwnd,WPARAM sel_start,LPARAM sel_end)

{
  SendMessageA(hwnd,0xb1,sel_start,sel_end);
  return;
}

/* 005d2ded auto */
iptr __cdecl edit_hwnd_get_line(HWND hwnd,WPARAM line,short *buffer,i32 buf_size)

{
  iptr copied_len;
  
  *buffer = (short)buf_size - 1;
  copied_len = SendMessageA(hwnd,0xc4,line,(LPARAM)buffer);
  *(i8 *)(copied_len + (int)buffer) = 0;
  return copied_len;
}

/* 005d2e31 auto */
LRESULT __cdecl edit_hwnd_get_line_count(HWND hwnd)

{
  LRESULT line_count;
  
  line_count = SendMessageA(hwnd,0xba,0,0);
  return line_count;
}

/* 005d2e9c auto */
LRESULT __cdecl edit_line_index(HWND hwnd,WPARAM line)

{
  LRESULT line_index;
  
  line_index = SendMessageA(hwnd,0xbb,line,0);
  return line_index;
}

/* 005d2ec1 auto */
LRESULT __cdecl edit_line_length(HWND hwnd,WPARAM char_index)

{
  LRESULT line_start;
  
  line_start = SendMessageA(hwnd,0xc1,char_index,0);
  return line_start;
}

/* 005d2f0d auto */
void __cdecl edit_hwnd_set_caret(HWND hwnd,WPARAM pos)

{
  SendMessageA(hwnd,0xb1,pos,pos);
  SendMessageA(hwnd,0xb7,0,0);
  return;
}

/* 005d2f47 auto */
uint __cdecl edit_ctl_get_sel_end(HWND hwnd)

{
  uint sel;
  
  sel = SendMessageA(hwnd,0xb0,0,0);
  return sel >> 0x10;
}

/* 005d2f7e auto */
int __cdecl edit_hwnd_get_text_end(i32 hwnd)

{
  int line_start;
  int line_len;
  
  line_start = edit_hwnd_get_line_count(hwnd);
  line_start = edit_line_index(hwnd,line_start - 1);
  line_len = edit_line_length(hwnd,line_start);
  return line_start + line_len;
}

/* 005d3035 auto */
void __cdecl edit_hwnd_replace_sel(HWND hwnd,LPARAM text)

{
  SendMessageA(hwnd,0xc2,0,text);
  return;
}

/* 005d30e0 auto */
i32 __thiscall edit_fire_key_callback(EditControl *self,iptr key)

{
  i32 result;
  
  if (self->on_key == 0) {
    result = 1;
  }
  else {
    result = self->on_key(self->ctrl_id,key);
  }
  return result;
}

/* 005d3130 auto */
HWND __cdecl combo_create_window(int *rect,iptr ctrl,int visible)

{
  WndBase *parent_wnd;
  NativeWindow *window;
  iptr height;
  int value;
  int nWidth;
  HWND parent_hwnd;
  HMENU menu;
  HINSTANCE hinst;
  LPVOID create_param;
  DWORD style2;
  WNDCLASSA wc;
  HWND hwnd2;
  
  style2 = 0x40a10003;
  if (visible != 0) {
    style2 = 0x50a10003;
  }
  if (combo_class_registered == 0) {
    create_param = (LPVOID)0x0;
    menu = (HMENU)0x0;
    hinst = err_report_ctx_block.app_hinstance;
    parent_wnd = (WndBase *)ctrl_get_parent((Control *)ctrl);
    window = wnd_get_window(parent_wnd);
    parent_hwnd = window->hwnd;
    height = rect_height((RECT *)rect);
    value = rect_width((RECT *)rect);
    hwnd2 = CreateWindowExA(4,str_combobox,((i8 *)&combo_probe_wnd_title),style2,*rect,rect[1],value
                              ,height,parent_hwnd,menu,hinst,create_param);
    default_draw_font_obj_block.combo_base_wndproc = (WNDPROC)GetWindowLongA(hwnd2,-4);
    wc.style = 0x88;
    wc.cbClsExtra = 0;
    wc.lpfnWndProc = default_draw_font_obj_block.combo_base_wndproc;
    default_draw_font_obj_block.combo_base_wnd_extra = GetClassLongA(hwnd2,-0x12);
    wc.cbWndExtra = default_draw_font_obj_block.combo_base_wnd_extra + 8;
    wc.hInstance = err_report_ctx_block.app_hinstance;
    wc.hIcon = (HICON)0x0;
    wc.hCursor = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
    wc.hbrBackground = (HBRUSH)0x0;
    wc.lpszMenuName = (LPCSTR)0x0;
    wc.lpszClassName = str_mscomboboxclass;
    RegisterClassA(&wc);
    combo_class_registered = 1;
    DestroyWindow(hwnd2);
  }
  style2 = 0x40a10203;
  if (visible != 0) {
    style2 = 0x50a10203;
  }
  create_param = (LPVOID)0x0;
  menu = (HMENU)0x0;
  hinst = err_report_ctx_block.app_hinstance;
  parent_wnd = (WndBase *)ctrl_get_parent((Control *)ctrl);
  value = (int)wnd_get_window(parent_wnd);
  parent_hwnd = ((NativeWindow *)value)->hwnd;
  value = rect_height((RECT *)rect);
  nWidth = rect_width((RECT *)rect);
  hwnd2 = CreateWindowExA(4,str_mscomboboxclass_2,((i8 *)&combo_wnd_title),style2,*rect,rect[1],
                            nWidth,value,parent_hwnd,menu,hinst,create_param);
  SetWindowLongA(hwnd2,-4,(iptr)combo_subclass_wndproc);
  SetWindowLongA(hwnd2,default_draw_font_obj_block.combo_base_wnd_extra,(LONG)default_draw_font_obj_block.combo_base_wndproc);
  SetWindowLongA(hwnd2,default_draw_font_obj_block.combo_base_wnd_extra + 4,ctrl);
  return hwnd2;
}

/* 005d3310 auto */
LRESULT __stdcall combo_subclass_wndproc(HWND hwnd,uint msg,uint wparam,LPARAM lparam)

{
  DWORD class_extra;
  WNDPROC lpPrevWndFunc;
  Button *self;
  iptr parent;
  HWND parent_hwnd;
  WndBase *this_00;
  NativeWindow *window;
  LRESULT result;
  iptr long_index;
  
  class_extra = GetClassLongA(hwnd,-0x12);
  lpPrevWndFunc = (WNDPROC)GetWindowLongA(hwnd,class_extra - 8);
  self = (Button *)GetWindowLongA(hwnd,class_extra - 4);
  if (self == (Button *)0x0) {
    return 1;
  }
  parent = ctrl_get_parent(self);
  wnd_set_active_child(parent);
  if (msg < 0x103) {
    if (0xff < msg) {
      if (((wparam != 9) && (wparam != 0xd)) && (wparam != 0x1b)) {
        result = CallWindowProcA(lpPrevWndFunc,hwnd,msg,wparam,lparam);
        return result;
      }
      parent_hwnd = GetParent(hwnd);
      SendMessageA(parent_hwnd,msg,wparam,lparam);
      return 1;
    }
    if (msg == 2) {
      if (self != (Button *)0x0) {
        control_set_hwnd(self,0);
      }
      result = CallWindowProcA(lpPrevWndFunc,hwnd,2,wparam,lparam);
      return result;
    }
  }
  else {
    if ((msg == 0x201) || (msg == 0x204)) {
      long_index = 0;
      parent_hwnd = GetParent(hwnd);
      this_00 = (WndBase *)GetWindowLongA(parent_hwnd,long_index);
      window = wnd_get_window(this_00);
      if ((window->flags_bytes[1] & 2) != 0) {
        parent_hwnd = GetParent(hwnd);
        SetFocus(parent_hwnd);
        parent_hwnd = GetParent(hwnd);
        BringWindowToTop(parent_hwnd);
      }
      result = CallWindowProcA(lpPrevWndFunc,hwnd,msg,wparam,lparam);
      return result;
    }
    if (msg == 0x4c8) {
      if (wparam >> 0x10 == 1) {
        if (self == (Button *)0x0) {
          return 1;
        }
        combo_fire_selchange((ComboBox *)self);
        return 1;
      }
      if (wparam >> 0x10 != 2) {
        return 1;
      }
      combo_fire_dblclick((ComboBox *)self);
      return 1;
    }
  }
  result = CallWindowProcA(lpPrevWndFunc,hwnd,msg,wparam,lparam);
  return result;
}

/* 005d356e auto */
void __cdecl combo_hwnd_cleanup_stub(i32 hwnd)

{
  return;
}

/* 005d357e auto */
void __cdecl combo_hwnd_add_string(HWND hwnd,LPARAM text)

{
  SendMessageA(hwnd,0x143,0,text);
  return;
}

/* 005d35c8 auto */
void __cdecl combo_hwnd_set_font(HWND hwnd,i32 font_handle)

{
  WPARAM *font_ptr;
  
  font_ptr = (WPARAM *)mem_handle_lock(font_handle);
  SendMessageA(hwnd,0x30,*font_ptr,0);
  mem_handle_unlock(font_handle);
  return;
}

/* 005d360a auto */
void __cdecl combo_hwnd_clear(HWND hwnd)

{
  SendMessageA(hwnd,0x14b,0,0);
  return;
}

/* 005d36b1 auto */
LRESULT __cdecl combo_hwnd_get_cur_sel(HWND hwnd)

{
  LRESULT cur_sel;
  
  cur_sel = SendMessageA(hwnd,0x147,0,0);
  if (cur_sel == -1) {
    cur_sel = -1;
  }
  return cur_sel;
}

/* 005d36f6 auto */
void __cdecl combo_hwnd_set_cur_sel(HWND hwnd,WPARAM index)

{
  SendMessageA(hwnd,0x14e,index,0);
  return;
}

/* 005d3720 auto */
void __thiscall combo_fire_dblclick(ComboBox *self)

{
  if (self->on_dblclick != 0) {
    self->on_dblclick(self->ctrl_id);
  }
  return;
}

/* 005d3760 auto */
void __thiscall combo_fire_selchange(ComboBox *self)

{
  if (self->on_select != 0) {
    self->on_select(self->ctrl_id);
  }
  return;
}

/* 005d37a0 auto */
HWND __cdecl listbox_create_hwnd(int *rect,iptr ctrl,int visible,int multi_column,GameFont *font)

{
  uint style_bits;
  WndBase *parent_wnd;
  NativeWindow *window;
  iptr height;
  int value;
  int nWidth;
  i32 font_handle;
  WPARAM *font_ptr;
  HWND parent_hwnd;
  HMENU menu;
  HINSTANCE hinst;
  LPVOID create_param;
  uint style2;
  WNDCLASSA wc;
  HWND hwnd2;
  
  style2 = 0;
  if (multi_column == 1) {
    style2 = 0x800;
  }
  style_bits = style2 | 0x40a10000;
  if (visible != 0) {
    style_bits = style2 | 0x50a10000;
  }
  style2 = style_bits;
  if (listbox_class_registered == 0) {
    create_param = (LPVOID)0x0;
    menu = (HMENU)0x0;
    hinst = err_report_ctx_block.app_hinstance;
    parent_wnd = (WndBase *)ctrl_get_parent((Control *)ctrl);
    window = wnd_get_window(parent_wnd);
    parent_hwnd = window->hwnd;
    height = rect_height((RECT *)rect);
    value = rect_width((RECT *)rect);
    hwnd2 = CreateWindowExA(4,str_listbox_2,((i8 *)&listbox_probe_wnd_title),style2,*rect,rect[1],value,
                              height,parent_hwnd,menu,hinst,create_param);
    default_draw_font_obj_block.listbox_base_wndproc = (WNDPROC)GetWindowLongA(hwnd2,-4);
    wc.style = 0x88;
    wc.cbClsExtra = 0;
    wc.lpfnWndProc = default_draw_font_obj_block.listbox_base_wndproc;
    default_draw_font_obj_block.listbox_base_wnd_extra = GetClassLongA(hwnd2,-0x12);
    wc.cbWndExtra = default_draw_font_obj_block.listbox_base_wnd_extra + 8;
    wc.hInstance = err_report_ctx_block.app_hinstance;
    wc.hIcon = (HICON)0x0;
    wc.hCursor = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
    wc.hbrBackground = (HBRUSH)0x0;
    wc.lpszMenuName = (LPCSTR)0x0;
    wc.lpszClassName = str_mslistboxclass;
    RegisterClassA(&wc);
    listbox_class_registered = 1;
    DestroyWindow(hwnd2);
  }
  style2 = 0x40a10001;
  if (visible != 0) {
    style2 = 0x50a10001;
  }
  if (multi_column == 1) {
    style2 = style2 | 0x800;
  }
  create_param = (LPVOID)0x0;
  menu = (HMENU)0x0;
  hinst = err_report_ctx_block.app_hinstance;
  parent_wnd = (WndBase *)ctrl_get_parent((Control *)ctrl);
  value = (int)wnd_get_window(parent_wnd);
  parent_hwnd = ((NativeWindow *)value)->hwnd;
  value = rect_height((RECT *)rect);
  nWidth = rect_width((RECT *)rect);
  hwnd2 = CreateWindowExA(4,str_mslistboxclass_2,((i8 *)&listbox_wnd_title),style2,*rect,rect[1],
                            nWidth,value,parent_hwnd,menu,hinst,create_param);
  font_handle = font_get_handle(font);
  font_ptr = (WPARAM *)mem_handle_lock(font_handle);
  SendMessageA(hwnd2,0x30,*font_ptr,0);
  font_handle = font_get_handle(font);
  mem_handle_unlock(font_handle);
  SetWindowLongA(hwnd2,-4,(iptr)listbox_subclass_wndproc);
  SetWindowLongA(hwnd2,default_draw_font_obj_block.listbox_base_wnd_extra,(LONG)default_draw_font_obj_block.listbox_base_wndproc);
  SetWindowLongA(hwnd2,default_draw_font_obj_block.listbox_base_wnd_extra + 4,ctrl);
  return hwnd2;
}

/* 005d39e2 auto */
LRESULT __stdcall listbox_subclass_wndproc(HWND hwnd,uint msg,uint wparam,LPARAM lparam)

{
  DWORD class_extra;
  WNDPROC lpPrevWndFunc;
  Button *self;
  iptr parent;
  HWND parent_hwnd;
  WndBase *this_00;
  NativeWindow *window;
  LRESULT result;
  iptr long_index;
  
  class_extra = GetClassLongA(hwnd,-0x12);
  lpPrevWndFunc = (WNDPROC)GetWindowLongA(hwnd,class_extra - 8);
  self = (Button *)GetWindowLongA(hwnd,class_extra - 4);
  if (self == (Button *)0x0) {
    return 1;
  }
  parent = ctrl_get_parent(self);
  wnd_set_active_child(parent);
  if (msg < 0x103) {
    if (0xff < msg) {
      if (((wparam != 9) && (wparam != 0xd)) && (wparam != 0x1b)) {
        result = CallWindowProcA(lpPrevWndFunc,hwnd,msg,wparam,lparam);
        return result;
      }
      parent_hwnd = GetParent(hwnd);
      SendMessageA(parent_hwnd,msg,wparam,lparam);
      return 1;
    }
    if (msg == 2) {
      if (self != (Button *)0x0) {
        control_set_hwnd(self,0);
      }
      result = CallWindowProcA(lpPrevWndFunc,hwnd,2,wparam,lparam);
      return result;
    }
  }
  else {
    if ((msg == 0x201) || (msg == 0x204)) {
      long_index = 0;
      parent_hwnd = GetParent(hwnd);
      this_00 = (WndBase *)GetWindowLongA(parent_hwnd,long_index);
      window = wnd_get_window(this_00);
      if ((window->flags_bytes[1] & 2) != 0) {
        parent_hwnd = GetParent(hwnd);
        SetFocus(parent_hwnd);
        parent_hwnd = GetParent(hwnd);
        BringWindowToTop(parent_hwnd);
      }
      result = CallWindowProcA(lpPrevWndFunc,hwnd,msg,wparam,lparam);
      return result;
    }
    if (msg == 0x4c8) {
      if (wparam >> 0x10 == 1) {
        if (self == (Button *)0x0) {
          return 1;
        }
        listbox_fire_selchange((ListBox *)self);
        return 1;
      }
      if (wparam >> 0x10 != 2) {
        return 1;
      }
      listbox_fire_dblclick((ListBox *)self);
      return 1;
    }
  }
  result = CallWindowProcA(lpPrevWndFunc,hwnd,msg,wparam,lparam);
  return result;
}

/* 005d3c40 auto */
void __cdecl listbox_hwnd_cleanup_stub(i32 hwnd)

{
  return;
}

/* 005d3c50 auto */
void __cdecl listbox_hwnd_add_string(HWND hwnd,LPARAM text)

{
  SendMessageA(hwnd,0x180,0,text);
  return;
}

/* 005d3c9a auto */
void __cdecl listbox_hwnd_set_font(HWND hwnd,i32 font_handle)

{
  WPARAM *font_ptr;
  
  font_ptr = (WPARAM *)mem_handle_lock(font_handle);
  SendMessageA(hwnd,0x30,*font_ptr,0);
  mem_handle_unlock(font_handle);
  return;
}

/* 005d3cdc auto */
void __cdecl listbox_hwnd_clear(HWND hwnd)

{
  SendMessageA(hwnd,0x184,0,0);
  return;
}

/* 005d3cff auto */
void __cdecl listbox_hwnd_get_text(HWND hwnd,WPARAM index,LPARAM buffer)

{
  SendMessageA(hwnd,0x189,index,buffer);
  return;
}

/* 005d3d62 auto */
void __cdecl listbox_hwnd_get_sel_text(HWND hwnd,char *buffer)

{
  LRESULT cur_sel;
  
  cur_sel = SendMessageA(hwnd,0x188,0,0);
  if (cur_sel == -1) {
    crt_strcpy((char *)((void *)buffer),((i8 *)&listbox_no_sel_text));
  }
  else {
    listbox_hwnd_get_text(hwnd,cur_sel,(LPARAM)(buffer));
  }
  return;
}

/* 005d3dbf auto */
LRESULT __cdecl listbox_hwnd_get_cur_sel(HWND hwnd)

{
  LRESULT cur_sel;
  
  cur_sel = SendMessageA(hwnd,0x188,0,0);
  if (cur_sel == -1) {
    cur_sel = -1;
  }
  return cur_sel;
}

/* 005d3e92 auto */
void __cdecl listbox_hwnd_set_cur_sel(HWND hwnd,WPARAM index)

{
  SendMessageA(hwnd,0x186,index,0);
  return;
}

/* 005d3f30 auto */
void __thiscall listbox_fire_dblclick(ListBox *self)

{
  if (self->on_dblclick != 0) {
    self->on_dblclick(self->ctrl_id);
  }
  return;
}

/* 005d3f70 auto */
void __thiscall listbox_fire_selchange(ListBox *self)

{
  if (self->on_select != 0) {
    self->on_select(self->ctrl_id);
  }
  return;
}

/* 005d4014 auto */
void __thiscall radiogrp_show_all(RadioGroup *self)

{
  int i;
  
  for (i = 0; i < (int)self->item_count; i++) {
    hwnd_show((i32)((RadioItem *)self->items)[i].hwnd);
    wnd_invalidate((i32)((RadioItem *)self->items)[i].hwnd);
  }
  return;
}

/* 005d4167 auto */
void __cdecl ctrl_set_pending_font(iptr font)

{
  (*(i8 * *)(draw_current_font_rest + 4)) = (i8 *)font;
  return;
}

/* 005d7cb0 auto */
void __thiscall
spritebtn_init_from_sprite
          (SpriteButton *self,WndBase *parent,i32 ctrl_id,int x,int y,
          int width,int height,iptr sprite,uint bg_color)

{
  u32 value;
  int size;
  WndBase *parent_wnd;
  i32 palette;
  int yBottom;
  i8 draw_ctx_b[16];
  i8 draw_ctx_a[16];
  i32 origin_y2;
  i32 origin_x2;
  i32 scale_den2;
  i32 scale_num2;
  int center_y;
  int center_x;
  tagRECT rect;
  int half_h;
  int half_w;
  tagRECT dst_rect;
  RECT src_rect;
  
  self->pressed_state = '\0';
  value = wnd_get_palette(parent);
  self->ctrl_palette = value;
  SetRect(&rect,x,y,width + x,y + height);
  ctrl_init(self,(iptr)parent,6,ctrl_id,&rect);
  self->on_click = 0;
  self->on_rclick = 0;
  gfx_get_scale_ratio((iptr)&scale_num2,(iptr)&scale_den2);
  gfx_set_scale_ratio(1,1);
  surface_create((DibSurface *)self->button_surface,width,height);
  surface_create((DibSurface *)&self->on_select,width,height);
  surface_fill((DibSurface *)self->button_surface,bg_color & 0xff);
  surface_fill((DibSurface *)&self->on_select,bg_color & 0xff);
  center_x = width >> 1;
  center_y = height >> 1;
  sprite_get_origin((SpriteOriginGetView *)sprite,(iptr)&origin_x2,(iptr)&origin_y2);
  half_w = sprite_get_width((Sprite *)sprite);
  half_w = half_w >> 1;
  half_h = sprite_get_height((Sprite *)sprite);
  half_h = half_h >> 1;
  sprite_set_origin((SpriteOriginSetView *)sprite,-half_w,-half_h);
  sprite_draw
            ((Sprite *)sprite,(iptr)draw_ctx_a,(iptr)(self->button_surface),center_x,center_y);
  sprite_draw
            ((Sprite *)sprite,(iptr)draw_ctx_b,(iptr)&self->on_select,center_x,center_y);
  sprite_set_origin((SpriteOriginSetView *)sprite,origin_x2,origin_y2);
  gfx_set_scale_ratio(scale_num2,scale_den2);
  size = surface_height((DibSurface *)self->button_surface);
  yBottom = y + size - 1;
  size = surface_width((DibSurface *)self->button_surface);
  SetRect(&rect,x,y,x + size - 1,yBottom);
  OffsetRect(&rect,-rect.left,-rect.top);
  dst_rect.left = rect.left;
  dst_rect.top = rect.top;
  dst_rect.right = rect.right;
  dst_rect.bottom = rect.bottom;
  SetRect(&dst_rect,rect.left,rect.top,rect.right - 2,rect.bottom - 2);
  src_rect.left = dst_rect.left;
  src_rect.top = dst_rect.top;
  src_rect.right = dst_rect.right;
  src_rect.bottom = dst_rect.bottom;
  OffsetRect(&dst_rect,2,2);
  surface_fill((DibSurface *)self->button_surface,(uint)(*(byte *)&gfx_black_color_index));
  surface_blit
            ((DibSurface *)&self->on_select,(DibSurface *)(iptr)(self->button_surface),&src_rect,
             &dst_rect);
  parent_wnd = (WndBase *)ctrl_get_parent(self);
  palette = wnd_get_palette(parent_wnd);
  surface_apply_palette((DibSurface *)self->button_surface,(PaletteVersionView *)palette);
  parent_wnd = (WndBase *)ctrl_get_parent(self);
  palette = wnd_get_palette(parent_wnd);
  surface_apply_palette((DibSurface *)&self->on_select,(PaletteVersionView *)palette);
  value = spritebtn_create_hwnd(x,y,width,height,(iptr)self,1);
  self->hwnd = value;
  return;
}

/* 005d8da1 auto */
int __cdecl radiogrp_item_height(GameFont *font)

{
  HDC hdc;
  HDC hdc_00;
  i32 font_handle;
  int height2;
  tagTEXTMETRICA metrics;
  i32 *font_data;
  
  hdc = GetDC((HWND)0x0);
  hdc_00 = CreateCompatibleDC(hdc);
  ReleaseDC((HWND)0x0,hdc);
  font_handle = font_get_handle(font);
  font_data = (i32 *)mem_handle_lock(font_handle);
  SelectObject(hdc_00,(HGDIOBJ)*font_data);
  font_handle = font_get_handle(font);
  mem_handle_unlock(font_handle);
  GetTextMetricsA(hdc_00,&metrics);
  height2 = metrics.tmHeight;
  DeleteDC(hdc_00);
  if (metrics.tmHeight < 0x14) {
    height2 = 0x14;
  }
  return height2;
}

/* 005d8e3f auto */
i32 __cdecl
radiogrp_create_items(iptr count_out,int *rect,int columns,iptr group,int item_count,iptr labels,int visible
            ,i32 font)

{
  int *hotkey_pos;
  HBITMAP bmp_unchecked;
  HBITMAP bmp_checked;
  HBITMAP bmp_focus;
  i32 handle;
  iptr items;
  int col_width;
  int row_height;
  int nHeight;
  WndBase *self;
  NativeWindow *window;
  int half_row;
  HWND item_hwnd;
  ControlBlock *block;
  size_t len;
  int half_item;
  HMENU hMenu;
  HINSTANCE hInstance;
  LPVOID lpParam;
  int item_x;
  DWORD style2;
  uint index;
  char *cursor;
  char *label;
  char hotkey[4];
  int item_y;
  
  bmp_unchecked = LoadBitmapA(err_report_ctx_block.app_hinstance,(LPCSTR)0x12d);
  bmp_checked = LoadBitmapA(err_report_ctx_block.app_hinstance,(LPCSTR)0x12f);
  bmp_focus = LoadBitmapA(err_report_ctx_block.app_hinstance,(LPCSTR)0x12e);
  handle = mem_handle_alloc(item_count * 0xa4);
  items = (iptr)mem_handle_lock((HGLOBAL)handle);
  col_width = rect_width((RECT *)rect);
  col_width = col_width / columns;
  row_height = rect_height((RECT *)rect);
  row_height = (row_height * columns) / item_count;
  nHeight = radiogrp_item_height((GameFont *)font);
  item_x = *rect;
  item_y = rect[1];
  style2 = 0x40010000;
  if (visible != 0) {
    style2 = 0x50010000;
  }
  index = 0;
  do {
    if (item_count <= (int)index) {
      *(int *)count_out = item_count;
      mem_handle_unlock(handle);
      return handle;
    }
    lpParam = (LPVOID)0x0;
    hMenu = (HMENU)0x0;
    hInstance = err_report_ctx_block.app_hinstance;
    self = (WndBase *)ctrl_get_parent((Control *)group);
    window = wnd_get_window(self);
    half_row = row_height >> 1;
    half_item = nHeight >> 1;
    item_hwnd = CreateWindowExA(4,str_mscontrolclass_5,((i8 *)&radiogrp_item_wnd_title),style2,item_x,
                              (half_row - half_item) + item_y,col_width,nHeight,window->hwnd,hMenu,
                              hInstance,lpParam);
    ((RadioItem *)items)[index].hwnd = item_hwnd;
    block = ctrl_init_block((i32)((RadioItem *)items)[index].hwnd,group);
    if (index == 0) {
      block->shared_bitmaps = 0;
    }
    else {
      block->shared_bitmaps = 1;
    }
    block->bitmaps[0] = bmp_unchecked;
    block->bitmaps[1] = bmp_checked;
    block->bitmaps[2] = bmp_focus;
    block->data = (iptr)&((RadioItem *)items)[index];
    block->kind = 3;
    SetWindowLongA(((RadioItem *)items)[index].hwnd,-4,(iptr)radiogrp_item_wndproc);
    SetRect(&((RadioItem *)items)[index].rect,item_x,(half_row - half_item) + item_y,
            item_x + col_width,(half_row - half_item) + item_y + nHeight);
    ((RadioItem *)items)[index].index = index;
    label = *(char **)(labels + index * 4);
    if (*label == '!') {
      ((RadioItem *)items)[index].enabled = 0;
      label++;
    }
    else if (*label == '^') {
      ((RadioItem *)items)[index].enabled = 1;
      radiogrp_set_selected((RadioGroup *)group,index);
      label++;
    }
    else {
      ((RadioItem *)items)[index].enabled = 1;
    }
    crt_strcpy(((RadioItem *)items)[index].label,(const char *)((void *)label));
    cursor = ((RadioItem *)items)[index].label;
    ((RadioItem *)items)[index].hotkey_pos = 0;
    while( true ) {
      if (*cursor == '\0') goto store_hotkey;
      if (*cursor == '~') break;
      hotkey_pos = &((RadioItem *)items)[index].hotkey_pos;
      *hotkey_pos = *hotkey_pos + 1;
      cursor++;
    }
    for (index = (uint)((RadioItem *)items)[index].hotkey_pos;
        len = _strlen(((RadioItem *)items)[index].label), index < len;
        index = index + 1) {
      *(i8 *)(index * 0xa5 + 0x1c + items) =
           *(i8 *)(index * 0xa5 + 0x1d + items);
    }
store_hotkey:
    len = _strlen(((RadioItem *)items)[index].label);
    if ((uint)((RadioItem *)items)[index].hotkey_pos < len) {
      hotkey[0] = ((RadioItem *)items)[index].label[((RadioItem *)items)[index].hotkey_pos];
      hotkey[1] = 0;
      __strlwr(hotkey);
      ((RadioItem *)items)[index].hotkey = hotkey[0];
    }
    else {
      ((RadioItem *)items)[index].hotkey_pos = 0xffffffff;
    }
    item_y += row_height;
    if (rect[3] <= item_y) {
      item_x += col_width;
      item_y = rect[1];
    }
    index++;
  } while( true );
}

/* 005d99f4 auto */
void __cdecl radiogrp_destroy_items(int count,int handle)

{
  iptr items;
  i32 i;
  
  if (handle == 0) {
    dbg_log((const char *)&str_error_tried_to_dismantle_null_radioset_i);
  }
  else {
    items = (iptr)mem_handle_lock((HGLOBAL)handle);
    for (i = 0; i < count; i++) {
      if ((int)((RadioItem *)items)[i].hwnd != 0) {
        DestroyWindow(((RadioItem *)items)[i].hwnd);
      }
    }
    mem_handle_unlock(handle);
    mem_handle_free(handle);
  }
  return;
}

/* 005d9a9a auto */
void __cdecl radiogrp_item_activate(HWND hwnd)

{
  RadioGroup *self;
  ControlBlock *block;
  iptr selected;
  iptr old_sel;
  iptr items;
  iptr new_sel;
  RadioItem *item;
  i32 sel_index;
  i32 ctrl_id;
  RECT *null_rect;
  BOOL erase;
  
  block = wnd_from_hwnd(hwnd);
  if (block != 0) {
    self = (RadioGroup *)block->owner;
    item = (RadioItem *)block->data;
    SetFocus(hwnd);
    selected = radiogrp_get_selected(self);
    if ((selected != item->index) && (item->enabled == 1)) {
      erase = 0;
      null_rect = (RECT *)0x0;
      old_sel = radiogrp_get_selected(self);
      items = radiogrp_get_items(self);
      InvalidateRect(((RadioItem *)items)[old_sel].hwnd,null_rect,erase);
      radiogrp_set_selected(self,item->index);
      erase = 0;
      null_rect = (RECT *)0x0;
      new_sel = radiogrp_get_selected(self);
      item = (RadioItem *)radiogrp_get_items(self);
      InvalidateRect(item[new_sel].hwnd,null_rect,erase);
    }
    wnd_active_child = ctrl_get_parent(self);
    sel_index = radiogrp_get_selected(self);
    ctrl_id = ctrl_get_id(self);
    radiogrp_fire_callback(self,ctrl_id,sel_index);
  }
  return;
}

/* 005d9b86 auto */
i32 __stdcall radiogrp_item_wndproc(HWND hwnd,uint msg,WPARAM wparam,LPARAM lparam)

{
  char nav_enabled;
  int items;
  iptr selected;
  iptr height;
  uint color_index;
  WndBase *parent_wnd;
  GamePalette *game_palette2;
  size_t len;
  WndBase *parent_base;
  int value;
  iptr parent;
  HWND hwnd_tmp;
  Wnd *nav_wnd;
  iptr items2;
  i32 ctrl_id;
  iptr items3;
  i32 result;
  i8 *red_out;
  i8 *green_out;
  tagRECT *draw_rect;
  RECT *null_rect;
  i8 *blue_out;
  UINT draw_flags;
  BOOL erase;
  tagRECT rect;
  HBITMAP bitmap;
  ControlBlock *block;
  tagPAINTSTRUCT ps;
  HGDIOBJ old_font;
  tagSIZE bmp_size;
  int remaining;
  HDC hdc;
  int underline_end;
  int next_index;
  i8 green[4];
  int underline_start;
  RadioItem *item;
  int box_left;
  int box_top;
  int box_right;
  int box_bottom;
  HBRUSH brush;
  i8 red[4];
  i8 blue[4];
  RadioGroup *group;
  i32 *font_data;
  tagRECT text_rect;
  char prefix[128];
  
  block = wnd_from_hwnd(hwnd);
  group = (RadioGroup *)block->owner;
  item = (RadioItem *)block->data;
  if (msg < 0x10) {
    if (msg == 0xf) {
      if (item->enabled == 1) {
        selected = radiogrp_get_selected(group);
        if (selected == item->index) {
          bitmap = block->bitmaps[2];
        }
        else {
          bitmap = block->bitmaps[1];
        }
      }
      else {
        bitmap = block->bitmaps[0];
      }
      GetBitmapDimensionEx(bitmap,&bmp_size);
      rect.left = item->rect.left;
      rect.top = item->rect.top;
      rect.right = item->rect.right;
      rect.bottom = item->rect.bottom;
      box_left = rect.left;
      box_top = rect.top;
      box_right = rect.right;
      box_bottom = rect.bottom;
      if (radio_lbutton_captured != 0) {
        box_right = rect.left + 0x20;
        height = rect_height(&rect);
        box_top = height - 0x14 + rect.top >> 1;
        box_bottom = rect.top + 0x14;
      }
      InvalidateRect(hwnd,(RECT *)0x0,1);
      OffsetRect(&rect,-rect.left,-rect.top);
      hdc = BeginPaint(hwnd,&ps);
      ctrl_paint_parent_bkgnd((iptr)&ps,hwnd);
      result = font_get_handle((GameFont *)(group)->radio_font);
      font_data = (i32 *)mem_handle_lock(result);
      old_font = SelectObject(hdc,(HGDIOBJ)*font_data);
      result = font_get_handle((GameFont *)(group)->radio_font);
      mem_handle_unlock(result);
      SetBkMode(hdc,1);
      gdi_blit_transparent(hdc,bitmap,rect.left,rect.bottom - 0x14 >> 1,0x20,0x14,0,7);
      rect.left += 0x25;
      if ((radio_shadow_dx != 0) || (radio_shadow_dy != 0)) {
        OffsetRect(&rect,(uint)radio_shadow_dx,(uint)radio_shadow_dy);
        blue_out = blue;
        green_out = green;
        red_out = red;
        color_index = (uint)radio_shadow_color_index;
        parent_wnd = (WndBase *)ctrl_get_parent(group);
        game_palette2 = (GamePalette *)wnd_get_palette(parent_wnd);
        palette_get_entry(game_palette2,color_index,(iptr)red_out,(iptr)green_out,(iptr)blue_out);
        SetTextColor(hdc,CONCAT12(blue[0],CONCAT11(green[0],red[0])));
        draw_flags = 0x24;
        draw_rect = &rect;
        len = _strlen(item->label);
        DrawTextA(hdc,item->label,len,draw_rect,draw_flags);
        OffsetRect(&rect,-(uint)radio_shadow_dx,-(uint)radio_shadow_dy);
      }
      if (item->enabled == 1) {
        parent_base = (WndBase *)ctrl_get_parent(group);
        value = (int)wnd_get_window(parent_base);
        if (((NativeWindow *)value)->field_40 == 8) {
          if (radio_text_color_index == 0) {
            SetTextColor(hdc,0);
          }
          else {
            blue_out = blue;
            green_out = green;
            red_out = red;
            color_index = (uint)radio_text_color_index;
            parent_wnd = (WndBase *)ctrl_get_parent(group);
            game_palette2 = (GamePalette *)wnd_get_palette(parent_wnd);
            parent = (iptr)palette_get_logpalette(game_palette2);
            palette_get_entry_rgb((GameLogPalette *)parent,color_index,(iptr)red_out,(iptr)green_out,(iptr)blue_out);
            SetTextColor(hdc,CONCAT12(blue[0],CONCAT11(green[0],red[0])));
          }
        }
        else if (radio_text_rgb_set == '\0') {
          SetTextColor(hdc,0);
        }
        else {
          SetTextColor(hdc,CONCAT12(radio_text_rgb_b,CONCAT11(radio_text_rgb_g,radio_text_rgb_r)));
        }
      }
      else if (item->enabled == 0) {
        parent_base = (WndBase *)ctrl_get_parent(group);
        value = (int)wnd_get_window(parent_base);
        if (((NativeWindow *)value)->field_40 == 8) {
          if (radio_disabled_color_index == 0) {
            SetTextColor(hdc,0x404040);
          }
          else {
            blue_out = blue;
            green_out = green;
            red_out = red;
            color_index = (uint)radio_disabled_color_index;
            parent_wnd = (WndBase *)ctrl_get_parent(group);
            game_palette2 = (GamePalette *)wnd_get_palette(parent_wnd);
            parent = (iptr)palette_get_logpalette(game_palette2);
            palette_get_entry_rgb((GameLogPalette *)parent,color_index,(iptr)red_out,(iptr)green_out,(iptr)blue_out);
            SetTextColor(hdc,CONCAT12(blue[0],CONCAT11(green[0],red[0])));
          }
        }
        else if (radio_disabled_rgb_set == '\0') {
          SetTextColor(hdc,0x404040);
        }
        else {
          SetTextColor(hdc,CONCAT12(radio_disabled_rgb_b,CONCAT11(radio_disabled_rgb_g,radio_disabled_rgb_r)));
        }
      }
      draw_flags = 0x24;
      draw_rect = &rect;
      len = _strlen(item->label);
      DrawTextA(hdc,item->label,len,draw_rect,draw_flags);
      if (item->hotkey_pos != -1) {
        crt_strcpy(prefix,item->label);
        prefix[item->hotkey_pos] = '\0';
        text_rect.left = rect.left;
        text_rect.top = rect.top;
        text_rect.right = rect.right;
        text_rect.bottom = rect.bottom;
        len = _strlen(prefix);
        if (len == 0) {
          underline_start = text_rect.left;
        }
        else {
          draw_flags = 0x424;
          draw_rect = &text_rect;
          len = _strlen(prefix);
          DrawTextA(hdc,prefix,len,draw_rect,draw_flags);
          underline_start = text_rect.right - 1;
        }
        crt_strcpy(prefix,item->label);
        prefix[item->hotkey_pos + 1] = '\0';
        text_rect.left = rect.left;
        text_rect.top = rect.top;
        text_rect.right = rect.right;
        text_rect.bottom = rect.bottom;
        draw_flags = 0x424;
        draw_rect = &text_rect;
        len = _strlen(prefix);
        DrawTextA(hdc,prefix,len,draw_rect,draw_flags);
        underline_start = underline_start + ((text_rect.right + 1) - underline_start >> 1) - 5;
        underline_end = underline_start + 10;
        brush = GetStockObject(3);
        SelectObject(hdc,brush);
        MoveToEx(hdc,underline_start,rect.bottom - 3,(LPPOINT)0x0);
        LineTo(hdc,underline_end,rect.bottom - 3);
        MoveToEx(hdc,underline_start,rect.bottom - 2,(LPPOINT)0x0);
        LineTo(hdc,underline_end,rect.bottom - 2);
      }
      SelectObject(hdc,old_font);
      EndPaint(hwnd,&ps);
      hwnd_tmp = GetFocus();
      if (hwnd_tmp != hwnd) {
        return 0;
      }
    }
    else if (msg != 7) {
      if (msg == 8) {
        wnd_redraw_client(hwnd);
        return 0;
      }
      goto default_proc;
    }
    nav_wnd = (Wnd *)ctrl_get_parent(group);
    nav_enabled = wnd_keyboard_nav_enabled(nav_wnd);
    if (nav_enabled == '\0') {
      result = ctrl_default_wndproc(hwnd,msg,wparam,lparam);
      return result;
    }
    hdc = GetDC(hwnd);
    brush = GetStockObject(3);
    GetClientRect(hwnd,&rect);
    SelectObject(hdc,brush);
    rect.left += 0x20;
    FrameRect(hdc,&rect,brush);
    DeleteObject(brush);
    ReleaseDC(hwnd,hdc);
  }
  else if (msg < 0x202) {
    if (msg == 0x201) {
      if (radio_lbutton_captured == 0) {
        value = radiogrp_get_selected(group);
        if ((value != item->index) && (item->enabled == 1)) {
          value = radiogrp_get_selected(group);
          if (value != -1) {
            erase = 0;
            null_rect = (RECT *)0x0;
            value = radiogrp_get_selected(group);
            items = radiogrp_get_items(group);
            InvalidateRect(((RadioItem *)items)[value].hwnd,null_rect,erase);
          }
          radiogrp_set_selected(group,item->index);
          SetFocus(hwnd);
          InvalidateRect(hwnd,(RECT *)0x0,0);
          parent = ctrl_get_parent(group);
          wnd_set_active_child(parent);
          result = radiogrp_get_selected(group);
          ctrl_id = ctrl_get_id(group);
          radiogrp_fire_callback(group,ctrl_id,result);
        }
        radio_lbutton_captured = 1;
        SetCapture(hwnd);
      }
    }
    else {
      if (msg != 0x100) goto default_proc;
      if (wparam == 9) {
        hwnd_tmp = GetParent(hwnd);
        SendMessageA(hwnd_tmp,msg,wparam,lparam);
      }
      else {
        if (wparam == 0x20) {
          nav_wnd = (Wnd *)ctrl_get_parent(group);
          nav_enabled = wnd_keyboard_nav_enabled(nav_wnd);
          if (nav_enabled != '\0') {
            SendMessageA(hwnd,0x201,0,0);
            SendMessageA(hwnd,0x202,0,0);
            return 0;
          }
        }
        if ((((wparam == 0x27) || (wparam == 0x28)) || (wparam == 0x66)) || (wparam == 0x62)) {
          nav_wnd = (Wnd *)ctrl_get_parent(group);
          nav_enabled = wnd_keyboard_nav_enabled(nav_wnd);
          if (nav_enabled != '\0') {
            remaining = radiogrp_item_count(group);
            next_index = item->index + 1;
            value = radiogrp_item_count(group);
            if (value <= next_index) {
              next_index = 0;
            }
            while ((0 < remaining &&
                   (value = radiogrp_get_items(group),
                   ((RadioItem *)value)[next_index].enabled == 0))) {
              remaining--;
              next_index++;
              value = radiogrp_item_count(group);
              if (value <= next_index) {
                next_index = 0;
              }
            }
            if (remaining < 1) {
              return 0;
            }
            value = radiogrp_get_items(group);
            SetFocus(((RadioItem *)value)[next_index].hwnd);
            erase = 0;
            null_rect = (RECT *)0x0;
            value = radiogrp_get_selected(group);
            items2 = radiogrp_get_items(group);
            InvalidateRect(((RadioItem *)items2)[value].hwnd,null_rect,erase);
            radiogrp_set_selected(group,next_index);
            erase = 0;
            null_rect = (RECT *)0x0;
            value = radiogrp_get_items(group);
            InvalidateRect(((RadioItem *)value)[next_index].hwnd,null_rect,erase);
            parent = ctrl_get_parent(group);
            wnd_set_active_child(parent);
            result = radiogrp_get_selected(group);
            ctrl_id = ctrl_get_id(group);
            radiogrp_fire_callback(group,ctrl_id,result);
            return 0;
          }
        }
        if (((wparam == 0x26) || (wparam == 0x25)) || ((wparam == 0x68 || (wparam == 100)))) {
          nav_wnd = (Wnd *)ctrl_get_parent(group);
          nav_enabled = wnd_keyboard_nav_enabled(nav_wnd);
          if (nav_enabled != '\0') {
            remaining = radiogrp_item_count(group);
            next_index = item->index - 1;
            if (next_index < 0) {
              next_index = radiogrp_item_count(group);
              next_index--;
            }
            while ((0 < remaining &&
                   (value = radiogrp_get_items(group),
                   ((RadioItem *)value)[next_index].enabled == 0))) {
              remaining--;
              next_index--;
              if (next_index < 0) {
                next_index = radiogrp_item_count(group);
                next_index--;
              }
            }
            if (remaining < 1) {
              return 0;
            }
            value = radiogrp_get_items(group);
            SetFocus(((RadioItem *)value)[next_index].hwnd);
            erase = 0;
            null_rect = (RECT *)0x0;
            value = radiogrp_get_selected(group);
            items3 = radiogrp_get_items(group);
            InvalidateRect(((RadioItem *)items3)[value].hwnd,null_rect,erase);
            radiogrp_set_selected(group,next_index);
            erase = 0;
            null_rect = (RECT *)0x0;
            value = radiogrp_get_items(group);
            InvalidateRect(((RadioItem *)value)[next_index].hwnd,null_rect,erase);
            parent = ctrl_get_parent(group);
            wnd_set_active_child(parent);
            result = radiogrp_get_selected(group);
            ctrl_id = ctrl_get_id(group);
            radiogrp_fire_callback(group,ctrl_id,result);
            return 0;
          }
        }
        hwnd_tmp = GetParent(hwnd);
        SendMessageA(hwnd_tmp,msg,wparam,lparam);
      }
    }
  }
  else {
    switch(msg) {
    case 0x202:
      ReleaseCapture();
      radio_lbutton_captured = 0;
      break;
    case 0x203:
      if (item->enabled == 1) {
        parent = ctrl_get_parent(group);
        wnd_set_active_child(parent);
        value = radiogrp_get_selected(group);
        if (value != item->index) {
          value = radiogrp_get_selected(group);
          if (value != -1) {
            erase = 0;
            null_rect = (RECT *)0x0;
            value = radiogrp_get_selected(group);
            items = radiogrp_get_items(group);
            InvalidateRect(((RadioItem *)items)[value].hwnd,null_rect,erase);
          }
          radiogrp_set_selected(group,item->index);
        }
        result = item->index;
        ctrl_id = ctrl_get_id(group);
        radiogrp_fire_dblclick(group,ctrl_id,result);
      }
      break;
    case 0x204:
      if (radio_rbutton_captured == 0) {
        radio_rbutton_captured = 1;
        SetCapture(hwnd);
        parent = ctrl_get_parent(group);
        wnd_set_active_child(parent);
        result = item->index;
        ctrl_id = ctrl_get_id(group);
        radiogrp_fire_rclick(group,ctrl_id,result);
      }
      break;
    case 0x205:
      ReleaseCapture();
      radio_rbutton_captured = 0;
      break;
    default:
default_proc:
      result = ctrl_default_wndproc(hwnd,msg,wparam,lparam);
      return result;
    }
  }
  return 0;
}

/* 005dab5a auto */
i32 __cdecl ctrl_hwnd_is_radio(HWND hwnd)

{
  char *_Str1;
  iptr cmp;
  iptr block;
  char *_Str2;
  CHAR class_name[52];
  
  GetClassNameA(hwnd,class_name,0x32);
  _Str2 = str_mscontrolclass_6;
  _Str1 = __strupr(class_name);
  cmp = _strcmp(_Str1,_Str2);
  if ((cmp == 0) && (block = (iptr)wnd_from_hwnd(hwnd), *(int *)(block + 0x2c) == 3)) {
    return 1;
  }
  return 0;
}

/* 005dabc7 auto */
void __cdecl radiogrp_hwnd_invalidate(HWND hwnd)

{
  InvalidateRect(hwnd,(RECT *)0x0,0);
  return;
}

/* 005dabe5 auto */
uint __cdecl radiogrp_hwnd_is_selected(i32 hwnd)

{
  ControlBlock *block;
  int selected;
  RadioItem *item;
  
  block = wnd_from_hwnd(hwnd);
  item = (RadioItem *)block->data;
  selected = radiogrp_get_selected((RadioGroup *)block->owner);
  return (uint)(selected == item->index);
}

/* 005dac39 auto */
i32 __cdecl radiogrp_hwnds_same_group(int hwnd_a,int hwnd_b)

{
  iptr is_radio_a;
  iptr is_radio_b;
  ControlBlock *block_a;
  ControlBlock *block_b;
  
  is_radio_a = ctrl_hwnd_is_radio(hwnd_a);
  if ((is_radio_a == 0) || (is_radio_b = ctrl_hwnd_is_radio(hwnd_b), is_radio_b == 0)) {
    return 0;
  }
  if (hwnd_a == hwnd_b) {
    return 1;
  }
  block_a = wnd_from_hwnd(hwnd_a);
  block_b = wnd_from_hwnd(hwnd_b);
  if (block_b->owner == block_a->owner) {
    return 1;
  }
  return 0;
}

/* 005dad40 auto */
void __thiscall radiogrp_fire_callback(RadioGroup *self,i32 ctrl_id,i32 index)

{
  if (self->on_select != 0) {
    self->on_select(ctrl_id,index);
  }
  return;
}

/* 005dad80 auto */
void __thiscall radiogrp_fire_dblclick(RadioGroup *self,i32 ctrl_id,i32 index)

{
  if (self->on_dblclick != 0) {
    self->on_dblclick(ctrl_id,index);
  }
  return;
}

/* 005dadc0 auto */
void __thiscall radiogrp_fire_rclick(RadioGroup *self,i32 ctrl_id,i32 index)

{
  if (self->on_rclick != 0) {
    self->on_rclick(ctrl_id,index);
  }
  return;
}

/* 005db0d0 auto */
void __thiscall scrollbar_set_page_size(Scrollbar *self,u32 page_size)

{
  int min_pos;
  int max_pos;
  
  scrollbar_get_ctl_range(self,(iptr)&min_pos,(iptr)&max_pos);
  if ((int)page_size <= max_pos - min_pos) {
    self->page_size = page_size;
  }
  return;
}

/* 005db110 auto */
void __thiscall scrollbar_get_ctl_range(Scrollbar *self,iptr min_out,iptr max_out)

{
  scrollbar_hwnd_get_range(self->hwnd,(LPINT)min_out,(LPINT)max_out);
  return;
}

/* 005ea7d7 auto */
i32 __cdecl ctrl_list_find_by_hwnd(int hwnd,Control *list)

{
  int ctrl_hwnd;
  Control *ctrl;
  
  ctrl = list;
  while( true ) {
    if (ctrl == (Control *)0x0) {
      return 0;
    }
    ctrl_hwnd = control_get_hwnd(ctrl);
    if (ctrl_hwnd == hwnd) break;
    ctrl = (Control *)control_get_next(ctrl);
  }
  return (i32)ctrl;
}

/* 005eac6d auto */
i32 __cdecl ctrl_list_find_type11_hwnd(Control *list)

{
  int ctrl_type;
  i32 hwnd;
  Control *ctrl;
  
  ctrl = list;
  while( true ) {
    if (ctrl == (Control *)0x0) {
      return 0;
    }
    ctrl_type = control_get_type(ctrl);
    if (ctrl_type == 0xb) break;
    ctrl = (Control *)control_get_next(ctrl);
  }
  hwnd = control_get_hwnd(ctrl);
  return hwnd;
}

/* 005eacc0: written by hand in src/game/retvals.cpp */

/* 005eb2f0 auto */
void __thiscall edit_fire_maxtext_callback(EditControl *self)

{
  if (self->on_maxtext != 0) {
    self->on_maxtext(self->ctrl_id);
  }
  return;
}

/* 005eb330 auto */
void __thiscall edit_fire_change_callback(EditControl *self)

{
  if (self->on_change != 0) {
    self->on_change(self->ctrl_id);
  }
  return;
}

/* 005eb3ed auto */
uint __cdecl input_map_vkey(uint vkey)

{
  int key_down;
  uint key_code;
  
  key_code = (uint)input_vkey_map_table[vkey & 0xff];
  if (key_code != 0) {
    key_down = input_ctrl_key_down();
    if (key_down != 0) {
      key_code = key_code | 0x200;
    }
    key_down = input_shift_key_down();
    if (key_down != 0) {
      key_code = key_code | 0x100;
    }
  }
  return key_code;
}

/* 005eb447: written by hand in src/game/fixups.cpp */

/* 005ecef0 auto */
uint __cdecl input_shift_key_down(void)

{
  SHORT key_state;
  
  key_state = GetKeyState(0x10);
  return (uint)(((int)key_state & 0x8000U) != 0);
}

/* 005ecf20 auto */
uint __cdecl input_ctrl_key_down(void)

{
  SHORT key_state;
  
  key_state = GetKeyState(0x11);
  return (uint)(((int)key_state & 0x8000U) != 0);
}

/* 005f0620 auto */
/* Library Function - Single Match
    protected: struct _CRT_CRITICAL_SECTION * __thiscall ios::lockptr(void)
   
   Library: Visual Studio 1998 Debug */

int __thiscall ddctrl_get_rect(DDControl *self)

{
  return (int)&self->rect_left;
}

/* 005f0f05 auto */
void __cdecl ddctrl_set_msg_target(iptr target)

{
  ddctrl_current_target = target;
  return;
}

/* 005f130f auto */
i32 __thiscall ddctrl_dispatch_msg(DDControl *self,int msg,int x,int y)

{
  char handled;
  i32 result;
  
  handled = ddctrl_dispatch_to_children(self,msg,x,y);
  if (handled == '\0') {
    ddctrl_set_msg_target((iptr)self);
    if ((msg == 0x100) && (self->is_active != '\0')) {
      call_untyped(((code **)self->vtable)[6], x);
      result = 1;
    }
    else if ((msg == 0x102) && (self->is_active != '\0')) {
      call_untyped(((code **)self->vtable)[7], x);
      result = 1;
    }
    else if (msg == 0xfff0) {
      call_untyped(((code **)self->vtable)[9], x,y);
      result = 1;
    }
    else if ((((x < (int)self->rect_left) || (y < (int)self->rect_top)) ||
             ((int)self->rect_right < x)) || ((int)self->rect_bottom < y)) {
      result = 0;
    }
    else {
      switch(msg) {
      case 0x200:
        call_untyped(((code **)self->vtable)[4], x,y);
        break;
      case 0x201:
        call_untyped(((code **)self->vtable)[0], self,x,y);
        break;
      case 0x202:
        call_untyped(((code **)self->vtable)[2], x,y);
        break;
      case 0x203:
        call_untyped(((code **)self->vtable)[5], x,y);
        break;
      case 0x204:
        call_untyped(((code **)self->vtable)[1], x,y);
        break;
      case 0x205:
        call_untyped(((code **)self->vtable)[3], x,y);
      }
      result = 1;
    }
  }
  else {
    result = 1;
  }
  return result;
}

/* 005f1514 auto */
uptr __thiscall ddctrl_get_parent_window(DDControlParentView *self)

{
  uptr parent_wnd;
  uptr result;
  
  if (self->parent_wnd == 0) {
    if (self->parent_control == 0) {
      result = 0;
    }
    else {
      parent_wnd = ddctrl_get_parent_window((DDControlParentView *)self->parent_control);
      self->parent_wnd = parent_wnd;
      result = self->parent_wnd;
    }
  }
  else {
    result = self->parent_wnd;
  }
  return result;
}

/* 005f15a9 auto */
void __thiscall ddctrl_on_paint_default(DDControlParentView *self,i32 paint_arg)

{
  int parent_wnd;
  
  parent_wnd = ddctrl_get_parent_window(self);
  if (parent_wnd == 0) {
    __assert(str_getparentgamewin,str_d_ss_smeds32_ddcntrl_cpp,0xd8);
  }
  return;
}

/* 005f1622 auto */
void __thiscall ddctrl_activate(DDControlActivateView *self)

{
  if (self->is_active == '\0') {
    if (self->parent_control == 0) {
      ddwin_deactivate_controls((DDWindow *)(void *)self->owner_ddwin);
    }
    else {
      ddctrl_deactivate_children((DDControl *)(void *)self->parent_control);
    }
    self->is_active = 1;
    call_untyped(((code **)self->vtable)[8], 1);
  }
  return;
}

/* 005f1683 auto */
void __thiscall ddctrl_deactivate(DDControl *self)

{
  if ((char)self->is_active != '\0') {
    ddctrl_deactivate_children(self);
    self->is_active = 0;
    call_untyped(((code **)((int *)self->vtable))[8], self,0);
  }
  return;
}

/* 005f179c auto */
void __thiscall ddctrl_on_lbuttondown(DDControlActivateView *self,i32 x,i32 y)

{
  ddctrl_activate(self);
  return;
}

/* 005f17bc auto */
void __thiscall ddctrl_on_rbuttondown_nop(void *self,i32 x,i32 y)

{
  return;
}

/* 005f17d4 auto */
void __thiscall ddctrl_on_lbuttonup(DdctrlOnLbuttonupView *self,i32 x,i32 y)

{
  if (self->on_lbutton_up != 0) {
    self->on_lbutton_up(self->control_id,x,y);
  }
  return;
}

/* 005f1811 auto */
void __thiscall ddctrl_on_rbuttonup(DdctrlOnRbuttonupView *self,i32 x,i32 y)

{
  if (self->on_rbutton_up != 0) {
    self->on_rbutton_up(self->control_id,x,y);
  }
  return;
}

/* 005f184e auto */
void __thiscall ddctrl_on_mousemove(DdctrlOnMousemoveView *self,i32 x,i32 y)

{
  if (self->on_mouse_move != 0) {
    self->on_mouse_move(self->control_id,x,y);
  }
  return;
}

/* 005f188b auto */
void __thiscall ddctrl_on_dblclick(DdctrlOnDblclickView *self,i32 x,i32 y)

{
  if (self->on_dblclick != 0) {
    self->on_dblclick(self->control_id,x,y);
  }
  return;
}

/* 005f18c8 auto */
void __thiscall ddctrl_on_msg_fff0_nop(void *self,i32 x,i32 y)

{
  return;
}

/* 005f18e0 auto */
void __thiscall ddctrl_on_keydown_nop(void *self,i32 key)

{
  return;
}

/* 005f18f8 auto */
void __thiscall ddctrl_on_char_nop(void *self,i32 ch)

{
  return;
}

/* 005f1910 auto */
void __thiscall ddctrl_on_set_active_nop(void *self,i32 active)

{
  return;
}

/* 005f19a6 auto */
void __thiscall ddctrl_deactivate_children(DDControl *self)

{
  i32 child;
  
  child = ptrlist_first((PtrList *)self->child_controls);
  while (child != 0) {
    ddctrl_deactivate((DDControl *)child);
    child = ptrlist_next((PtrList *)self->child_controls);
  }
  return;
}

/* 005f1a40 auto */
i8 __thiscall ddctrl_dispatch_to_children(DDControl *self,int msg,int x,int y)

{
  int *child_rect;
  int handled;
  DDControl *child;
  
  if ((self->hover_child != 0) && (msg == 0x200)) {
    child_rect = (int *)ddctrl_get_rect((DDControl *)self->hover_child);
    if ((x < *child_rect) ||
       (((child_rect[2] < x || (y < child_rect[1])) || (child_rect[3] < y)))) {
      ddctrl_dispatch_msg((DDControl *)self->hover_child,0xfff0,x,y);
      self->hover_child = 0;
    }
  }
  child = (DDControl *)ptrlist_first((PtrList *)self->child_controls);
  while( true ) {
    if (child == (DDControl *)0x0) {
      return 0;
    }
    handled = ddctrl_dispatch_msg(child,msg,x,y);
    if (handled != 0) break;
    child = (DDControl *)ptrlist_next((PtrList *)self->child_controls);
  }
  if (msg == 0x200) {
    self->hover_child = (uptr)child;
  }
  return 1;
}

/* 00601300: written by hand in src/crt/locale.c */

/* 00601560: written by hand in src/crt/locale.c */

/* 00606330: written by hand in src/crt/locale.c */

/* 00606690: written by hand in src/crt/locale.c */
