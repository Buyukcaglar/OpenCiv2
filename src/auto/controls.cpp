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
Control * __thiscall button_ctor(Control *self)

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
i32 __thiscall ctrl_base_dtor(ControlBase *self)

{
  i32 result;
  
  if (self->owner_wnd != 0) {
    wnd_remove_control((WndControlRemoveView *)self->owner_wnd,self->control_id);
  }
  self->next_control = 0;
  result = ctrl_destroy_hwnd((iptr)self);
  return result;
}

/* 0040f570 auto */
i32 __thiscall ctrl_dtor(Control *self)

{
  i32 seh_prev;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0;
  if (self->hwnd != 0) {
    ctrl_destroy(self);
  }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 0040f5c3 */ { ctrl_base_dtor(*(ControlBase **)&self); }
  return seh_prev;
}

/* 0040f610 auto */
void __thiscall ctrl_destroy(Control *self)

{
  if (self->hwnd != 0) {
    if (self->parent != 0) {
      wnd_remove_control((WndControlRemoveView *)self->parent,self->ctrl_id);
    }
    self->next_ctrl = 0;
    ctrl_destroy_hwnd((iptr)self);
  }
  return;
}

/* 0040f680 auto */
void __thiscall
button_create
          (Control *self,iptr parent,i32 ctrl_id,iptr rect,iptr label)

{
  u32 new_hwnd;
  
  if (self->hwnd != 0) {
    ctrl_destroy(self);
  }
  self->font = (u32)(*(i8 * *)draw_current_font_rest);
  ctrl_init(self,parent,6,ctrl_id,rect);
  self->on_click = 0;
  new_hwnd = button_create_hwnd((int *)rect,(iptr)self,label,1,(GameFont *)self->font);
  self->hwnd = new_hwnd;
  self->is_enabled = 1;
  return;
}

/* 0040f730 auto */
void __thiscall
ctrl_init(Control *self,iptr parent_wnd,u32 type_code,u32 id,iptr rect)

{
  self->parent = parent_wnd;
  self->ctrl_type = type_code;
  self->ctrl_id = id;
  self->rect_left = *(u32 *)rect;
  self->rect_top = *(u32 *)(rect + 4);
  self->rect_right = *(u32 *)(rect + 8);
  self->rect_bottom = *(u32 *)(rect + 0xc);
  self->next_ctrl = 0;
  self->hwnd = 0;
  self->wants_initial_focus = '\0';
  wnd_append_control((WndControlListView *)parent_wnd,(iptr)self);
  return;
}

/* 0040f7d0 auto */
void __thiscall ctrl_set_default_button(Control *self)

{
  iptr parent;
  
  parent = ctrl_get_parent(self);
  *(Control **)(parent + 0xbc) = self;
  return;
}

/* 0040f810 auto */
uptr __thiscall ctrl_get_parent(Control *self)

{
  return self->parent;
}

/* 0040f840 auto */
void __thiscall ctrl_set_cancel_button(Control *self)

{
  iptr parent;
  
  parent = ctrl_get_parent(self);
  *(Control **)(parent + 0xc0) = self;
  return;
}

/* 0040f880 auto */
void __thiscall button_set_callback(Control *self,iptr callback)

{
  self->on_click = callback;
  return;
}

/* 0040f8b0 auto */
Control * __thiscall checkbox_elem_ctor(Control *self)

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
  /* inlined unwind funclet 0040f98a */ { ctrl_base_dtor(*(ControlBase **)&self); }
  return;
}

/* 0040f9d0 auto */
void __thiscall
checkbox_create
          (Control *self,iptr parent,i32 ctrl_id,i32 x,i32 y
          ,iptr label)

{
  u32 new_hwnd;
  i8 rect[16];
  
  self->font = (u32)(*(i8 * *)(draw_current_font_rest + 8));
  checkbox_calc_rect((char *)label,x,y,(iptr)rect,(GameFont *)self->font);
  if (self->hwnd != 0) {
    ctrl_destroy(self);
  }
  ctrl_init(self,parent,2,ctrl_id,(iptr)rect);
  self->is_enabled = 0;
  self->on_select = 1;
  self->on_click = 0;
  new_hwnd = checkbox_create_hwnd((iptr)rect,(iptr)self,(char *)label,1);
  self->hwnd = new_hwnd;
  return;
}

/* 0040faa0 auto */
void __thiscall checkbox_set_callback(CheckboxCallbackSetView *self,iptr callback)

{
  self->on_toggle = callback;
  return;
}

/* 0040fad0 auto */
void __thiscall checkbox_set_checked(Control *self,u32 checked)

{
  self->on_click = checked;
  return;
}

/* 0040fb00 auto */
Control * __thiscall scrollbar_ctor(Control *self)

{
  i32 seh_prev;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0xffffffff;
  ctrl_base_ctor(self);
  self->on_select = 1;
  self->is_enabled = 0;
  self->on_click = 0;
  return self;
}

/* 0040fbb0 auto */
void __thiscall scrollbar_dtor(Control *self)

{
  i32 seh_prev;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0;
  if (self->hwnd != 0) {
    scrollbar_destroy_hwnd(self->hwnd);
  }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 0040fc0a */ { ctrl_base_dtor(*(ControlBase **)&self); }
  return;
}

/* 0040fc50 auto */
void __thiscall
scrollbar_create
          (Control *self,iptr parent,iptr ctrl_id,iptr rect,i32 style)

{
  u32 new_hwnd;
  
  if (self->hwnd != 0) {
    ctrl_destroy(self);
  }
  ctrl_init(self,parent,8,ctrl_id,rect);
  new_hwnd = scrollbar_create_hwnd((int *)rect,(iptr)self,style,1);
  self->hwnd = new_hwnd;
  scrollbar_hwnd_set_range(self->hwnd,1,100);
  self->font = 1;
  return;
}

/* 0040fcf0 auto */
void __thiscall scrollbar_set_pos(ClickControl *self,iptr pos)

{
  self->scroll_pos = pos;
  scrollbar_hwnd_set_pos(self->hwnd,pos);
  return;
}

/* 0040fd40 auto */
void __thiscall
scrollbar_set_range(Control *self,i32 min_value,i32 max_value)

{
  scrollbar_hwnd_set_range(self->hwnd,min_value,max_value);
  return;
}

/* 0040fd80 auto */
void __thiscall scrollbar_set_callback(Control *self,iptr callback)

{
  self->is_enabled = callback;
  return;
}

/* 00418740 auto */
u32 __thiscall ctrl_get_id(ControlIdView *self)

{
  return self->ctrl_id;
}

/* 00418770 auto */
u32 __thiscall control_get_hwnd(ControlHwndView *self)

{
  return self->hwnd;
}

/* 004187a0 auto */
InputControl * __thiscall edit_ctor(InputControl *self)

{
  i32 seh_prev;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0xffffffff;
  ctrl_base_ctor((Control *)self);
  self->on_click = 0;
  self->is_enabled = 0;
  self->items_handle = 0;
  self->on_select = 0;
  *(i8 *)&self->font = 0;
  *(i8 *)((int)&self->font + 1) = 0;
  return self;
}

/* 00418870 auto */
void __thiscall edit_dtor(Control *self)

{
  i32 seh_prev;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0;
  if (self->hwnd != 0) {
    edit_hwnd_cleanup_stub(self->hwnd);
  }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 004188ca */ { ctrl_base_dtor(*(ControlBase **)&self); }
  return;
}

/* 00418910 auto */
void __thiscall
edit_create
          (EditControl *self,iptr parent,i32 ctrl_id,iptr rect,iptr text)

{
  u32 new_hwnd;
  
  if (self->hwnd != 0) {
    ctrl_destroy((Control *)self);
  }
  self->edit_font = (u32)(*(i8 * *)(draw_current_font_rest + 12));
  ctrl_init((Control *)self,parent,4,ctrl_id,rect);
  new_hwnd = edit_create_window((int *)rect,(iptr)self,1,1,(GameFont *)self->edit_font);
  self->hwnd = new_hwnd;
  hwnd_send_settext(self->hwnd,text);
  return;
}

/* 004189c0 auto */
void __thiscall edit_set_max_len(EditMaxLenView *self,i32 max_len)

{
  edit_hwnd_limit_text(self->hwnd,max_len);
  return;
}

/* 00418a00 auto */
void __thiscall edit_set_callback(EditCallbackSetView *self,iptr callback)

{
  self->on_change = callback;
  return;
}

/* 00418a30 auto */
void __thiscall ctrl_set_text(ControlTextView *self,iptr text)

{
  hwnd_send_settext(self->hwnd,text);
  return;
}

/* 00418a70 auto */
void __thiscall ctrl_get_text(ControlTextView *self,iptr buffer)

{
  hwnd_get_text(self->hwnd,buffer);
  return;
}

/* 00418ab0 auto */
Control * __thiscall combo_ctor(Control *self)

{
  i32 seh_prev;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0xffffffff;
  ctrl_base_ctor(self);
  self->on_click = 0;
  self->on_select = 0;
  return self;
}

/* 00418b50 auto */
void __thiscall combo_dtor(ComboDtorView *self)

{
  i32 seh_prev;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0;
  if (self->hwnd != 0) {
    combo_hwnd_cleanup_stub(self->hwnd);
  }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 00418baa */ { ctrl_base_dtor(*(ControlBase **)&self); }
  return;
}

/* 00418bf0 auto */
void __thiscall
combo_create(Control *self,iptr parent,i32 ctrl_id,iptr rect)

{
  u32 new_hwnd;
  
  if (self->hwnd != 0) {
    ctrl_destroy(self);
  }
  ctrl_init(self,parent,10,ctrl_id,rect);
  new_hwnd = combo_create_window((int *)rect,(iptr)self,1);
  self->hwnd = new_hwnd;
  self->is_enabled = 0;
  return;
}

/* 00418c70 auto */
void __thiscall combo_set_font(ComboBoxFontView *self,iptr font)

{
  i32 hfont;
  
  hfont = font_get_hfont((GameFont *)font);
  combo_hwnd_set_font(self->hwnd,hfont);
  return;
}

/* 00418ce0 auto */
void __thiscall combo_add_string(ComboBoxAddView *self,iptr text)

{
  combo_hwnd_add_string(self->hwnd,text);
  self->item_count++;
  return;
}

/* 00418d20 auto */
void __thiscall combo_clear(ComboBoxClearView *self)

{
  combo_hwnd_clear(self->hwnd);
  self->item_count = 0;
  return;
}

/* 00418d60 auto */
i32 __thiscall combo_get_cur_sel(ComboBoxGetSelView *self)

{
  i32 sel;
  
  sel = combo_hwnd_get_cur_sel(self->hwnd);
  return sel;
}

/* 00418d90 auto */
void __thiscall combo_set_cur_sel(ComboBoxSetSelView *self,iptr index)

{
  combo_hwnd_set_cur_sel(self->hwnd,index);
  return;
}

/* 00418dd0 auto */
void __thiscall combo_set_callback(ComboBoxCallbackSetView *self,iptr callback)

{
  self->on_select = callback;
  return;
}

/* 00418e00 auto */
Control * __thiscall checkbox_ctor(Control *self)

{
  i32 seh_prev;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0xffffffff;
  ctrl_base_ctor(self);
  self->on_click = 0;
  self->on_select = 0;
  return self;
}

/* 00418ea0 auto */
void __thiscall listbox_dtor(ListBoxControl *self)

{
  i32 seh_prev;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0;
  if (self->hwnd != 0) {
    listbox_hwnd_cleanup_stub(self->hwnd);
  }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 00418efa */ { ctrl_base_dtor(*(ControlBase **)&self); }
  return;
}

/* 00418f40 auto */
void __thiscall
listbox_create(Control *self,iptr parent,i32 ctrl_id,iptr rect)

{
  u32 new_hwnd;
  
  if (self->hwnd != 0) {
    ctrl_destroy(self);
  }
  self->font = (u32)(*(i8 * *)(draw_current_font_rest + 16));
  ctrl_init(self,parent,7,ctrl_id,rect);
  new_hwnd = listbox_create_hwnd((int *)rect,(iptr)self,1,0,(GameFont *)self->font);
  self->hwnd = new_hwnd;
  self->is_enabled = 0;
  return;
}

/* 00418fe0 auto */
void __thiscall listbox_set_font(ListBoxFontView *self,iptr font)

{
  i32 hfont;
  
  hfont = font_get_hfont((GameFont *)font);
  listbox_hwnd_set_font(self->hwnd,hfont);
  return;
}

/* 00419020 auto */
void __thiscall listbox_add_string(ListBoxAddView *self,iptr text)

{
  listbox_hwnd_add_string(self->hwnd,text);
  self->item_count++;
  return;
}

/* 00419060 auto */
void __thiscall listbox_clear(ListBoxClearView *self)

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
void __thiscall radiogrp_enable_item(RadioGroupEnableView *self,iptr index)

{
  if ((index < (int)self->item_count) && (-1 < index)) {
    *(i32 *)(self->items + 0x18 + index * 0xa4) = 1;
    radiogrp_hwnd_invalidate(*(i32 *)(self->items + index * 0xa4));
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
void __thiscall radiogrp_disable_item(RadioGroupDisableView *self,iptr index)

{
  if ((index < (int)self->item_count) && (-1 < index)) {
    if (self->selected_index == index) {
      self->selected_index = 0xffffffff;
    }
    *(i32 *)(self->items + 0x18 + index * 0xa4) = 0;
    radiogrp_hwnd_invalidate(*(i32 *)(self->items + index * 0xa4));
  }
  return;
}

/* 004472c0 auto */
/* Library Function - Single Match
    public: unsigned int __thiscall CCheckListBox::GetCheckStyle(void)
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall radiogrp_get_selected(RadioGroupGetSelView *self)

{
  return self->selected;
}

/* 004472f0 auto */
void __thiscall radiogrp_set_selected(RadioGroupSetSelView *self,u32 value)

{
  self->selected = value;
  return;
}

/* 00451ac0 auto */
void __thiscall scrollbar_set_track_callback(ScrollbarTrackSetView *self,iptr callback)

{
  self->on_track = callback;
  return;
}

/* 00453c40 auto */
void __thiscall ctrl_disable(Control *self)

{
  self->is_enabled = 0;
  wnd_invalidate(self->hwnd);
  return;
}

/* 00453c80 auto */
void __thiscall ctrl_enable(Control *self)

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
  scrollbar_ctor((Control *)((i8 *)&static_scrollbar_1));
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
  scrollbar_dtor((Control *)((i8 *)&static_scrollbar_1));
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
  scrollbar_ctor((Control *)((i8 *)&static_scrollbar_2));
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
  scrollbar_dtor((Control *)((i8 *)&static_scrollbar_2));
  return;
}

/* 00492ab0 auto */
i32 __thiscall edit_get_sel_end(EditSelEndView *self)

{
  i32 sel_end;
  
  sel_end = edit_ctl_get_sel_end(self->hwnd);
  return sel_end;
}

/* 00492ae0 auto */
void __thiscall edit_replace_sel(Control *self,iptr text)

{
  edit_hwnd_replace_sel(self->hwnd,text);
  return;
}

/* 00492b20 auto */
void __thiscall edit_set_sel(EditSelView *self,i32 sel_start,i32 sel_end)

{
  edit_hwnd_set_sel(self->hwnd,sel_start,sel_end);
  return;
}

/* 00497d40 auto */
void __thiscall
button_create_with_callback
          (Control *self,iptr parent,i32 ctrl_id,iptr rect,u32 callback,iptr label
          )

{
  self->on_select = callback;
  self->font = (u32)(*(i8 * *)draw_current_font_rest);
  button_create(self,parent,ctrl_id,rect,label);
  return;
}

/* 004bb3b0 auto */
Control * __thiscall ctrl_scalar_dtor(Control *self,uint flags)

{
  ctrl_dtor(self);
  if ((flags & 1) != 0) {
    operator_delete(self);
  }
  return self;
}

/* 004bb400 auto */
Control * __thiscall edit_scalar_dtor(Control *self,uint flags)

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
RadioGroupDtorView * __thiscall radiogrp_scalar_dtor(RadioGroupDtorView *self,uint flags)

{
  radiogrp_dtor(self);
  if ((flags & 1) != 0) {
    operator_delete(self);
  }
  return self;
}

/* 004bb4f0 auto */
Control * __thiscall scrollbar_scalar_dtor(Control *self,uint flags)

{
  scrollbar_dtor(self);
  if ((flags & 1) != 0) {
    operator_delete(self);
  }
  return self;
}

/* 004bb5b0 auto */
void __thiscall ctrl_set_initial_focus(CtrlSetInitialFocusView *self)

{
  self->wants_initial_focus = 1;
  return;
}

/* 004bb5e0 auto */
void __thiscall ctrl_set_focus(ControlFocusView *self)

{
  if (self->hwnd != 0) {
    ctrl_hwnd_set_focus(self->hwnd);
  }
  return;
}

/* 004bb620 auto */
void __thiscall
edit_create_styled
          (EditControl *self,iptr parent,i32 ctrl_id,iptr rect,iptr text,
          i32 multiline,i32 style)

{
  u32 new_hwnd;
  
  if (self->hwnd != 0) {
    ctrl_destroy((Control *)self);
  }
  self->edit_font = (u32)(*(i8 * *)(draw_current_font_rest + 12));
  ctrl_init((Control *)self,parent,4,ctrl_id,rect);
  new_hwnd = edit_create_window((int *)rect,(iptr)self,multiline,style,(GameFont *)self->edit_font);
  self->hwnd = new_hwnd;
  hwnd_send_settext(self->hwnd,text);
  return;
}

/* 004bb6d0 auto */
void __thiscall edit_set_caret(ControlTextView *self,i32 pos)

{
  edit_hwnd_set_caret(self->hwnd,pos);
  return;
}

/* 004bb710 auto */
i32 __thiscall edit_get_text_end(ControlTextView *self)

{
  i32 text_end;
  
  text_end = edit_hwnd_get_text_end(self->hwnd);
  return text_end;
}

/* 004bb740 auto */
void __thiscall radiogrp_dtor(RadioGroupDtorView *self)

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
  /* inlined unwind funclet 004bb7b0 */ { ctrl_base_dtor(*(ControlBase **)&self); }
  return;
}

/* 004cffb0 auto */
i32 __thiscall
edit_get_line(EditLineView *self,i32 line,iptr buffer,i32 max_len)

{
  i32 length;
  
  length = edit_hwnd_get_line(self->hwnd,line,(short *)buffer,max_len);
  return length;
}

/* 005011b4 auto */
void __cdecl
spritebtn_create_icon_button(iptr parent,i32 ctrl_id,SpriteButton *button,iptr sprite,iptr rect)

{
  int *surf_rect;
  int size;
  WndPaletteView *parent_wnd;
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
            (button,(WndPaletteView *)parent,ctrl_id,*(i32 *)rect,*(i32 *)(rect + 4),width2,
             height2,sprite,0x17);
  surf_rect = (int *)surface_get_rect((DibSurface *)&button->on_select);
  rect2.left = *surf_rect;
  rect2.top = surf_rect[1];
  rect2.right = surf_rect[2];
  rect2.bottom = surf_rect[3];
  size = rect_width((iptr)&rect2);
  center = rect2.left + size / 2;
  size = sprite_width((Sprite *)sprite);
  icon_x = center - size / 2;
  size = rect_height((iptr)&rect2);
  center = rect2.top + size / 2;
  size = sprite_height((Sprite *)sprite);
  icon_y = center - size / 2;
  sprite_draw
            ((Sprite *)sprite,(iptr)draw_ctx,(iptr)&button->on_select,icon_x,icon_y);
  sprite_draw
            ((Sprite *)sprite,(iptr)shadow_ctx,(iptr)(button->button_surface),icon_x + 2,
             icon_y + 2);
  gfx_draw_rect_frame((iptr)&button->on_select,(iptr)&rect2,10);
  gfx_draw_rect_frame((iptr)(button->button_surface),(iptr)&rect2,10);
  inner_rect.left = rect2.left;
  inner_rect.top = rect2.top;
  inner_rect.right = rect2.right;
  inner_rect.bottom = rect2.bottom;
  rect_deflate((iptr)&inner_rect,1,1);
  gfx_draw_bevel_rect((iptr)&button->on_select,(iptr)&inner_rect,0x1f,0xf);
  gfx_draw_bevel_rect((iptr)(button->button_surface),(iptr)&inner_rect,0xf,10);
  rect_deflate((iptr)&inner_rect,1,1);
  gfx_draw_bevel_rect((iptr)&button->on_select,(iptr)&inner_rect,0x1f,0xf);
  gfx_draw_bevel_rect((iptr)(button->button_surface),(iptr)&inner_rect,0xf,10);
  parent_wnd = (WndPaletteView *)ctrl_get_parent((Control *)button);
  palette = wnd_get_palette(parent_wnd);
  surface_set_palette((DibSurface *)button->button_surface,palette);
  parent_wnd = (WndPaletteView *)ctrl_get_parent((Control *)button);
  palette = wnd_get_palette(parent_wnd);
  surface_set_palette((DibSurface *)&button->on_select,palette);
  return;
}

/* 00511560 auto */
SpriteButtonCore * __thiscall spritebtn_scalar_dtor(SpriteButtonCore *self,uint flags)

{
  spritebtn_dtor(self);
  if ((flags & 1) != 0) {
    operator_delete(self);
  }
  return self;
}

/* 005115b0 auto */
void __thiscall spritebtn_dtor(SpriteButtonCore *self)

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
  /* inlined unwind funclet 0051163c */ { ctrl_base_dtor(*(ControlBase **)&self); }
  return;
}

/* 00511720 auto */
SpriteButton * __thiscall spritebtn_ctor(SpriteButton *self)

{
  i32 seh_prev;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0xffffffff;
  ctrl_base_ctor((Control *)self);
  seh_state = 0;
  surface_ctor((DibSurface *)&self->on_select);
  seh_state = (seh_state & 0xffffff00 | (byte)(1));
  surface_ctor((DibSurface *)self->button_surface);
  self->pressed_state = '\0';
  return self;
}

/* 005117f0 auto */
void __thiscall spritebtn_set_click_handler(SpritebtnSetClickHandlerView *self,iptr callback)

{
  self->on_click = callback;
  return;
}

/* 00530e80 auto */
/* Library Function - Single Match
    protected: char * __thiscall streambuf::egptr(void)const 
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall ctrl_is_enabled(ControlEnabledView *self)

{
  return self->is_enabled;
}

/* 00530eb0 auto */
void __thiscall edit_set_change_callback(EditChangeSetView *self,iptr callback)

{
  self->on_change = callback;
  return;
}

/* 00530ee0 auto */
void __thiscall
checkbox_create_fixed
          (Control *self,iptr parent,i32 ctrl_id,i32 x,i32 y
          ,i32 width,iptr label)

{
  u32 hwnd;
  i8 rect[16];
  
  self->font = (u32)(*(i8 * *)(draw_current_font_rest + 8));
  checkbox_calc_rect_fixed(x,y,width,(iptr)rect,(GameFont *)self->font);
  if (self->hwnd != 0) {
    ctrl_destroy(self);
  }
  ctrl_init(self,parent,2,ctrl_id,(iptr)rect);
  self->is_enabled = 0;
  self->on_select = 1;
  self->on_click = 0;
  hwnd = checkbox_create_hwnd((iptr)rect,(iptr)self,(char *)label,1);
  self->hwnd = hwnd;
  return;
}

/* 00530fb0 auto */
void __thiscall checkbox_enable(CheckboxEnableView *self)

{
  self->is_enabled = 1;
  return;
}

/* 00530fe0 auto */
/* Library Function - Single Match
    public: int __thiscall ios::width(void)const 
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall checkbox_is_checked(Control *self)

{
  return self->on_click;
}

/* 00531010 auto */
InputControl * __thiscall radiogrp_ctor(InputControl *self)

{
  i32 seh_prev;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0xffffffff;
  ctrl_base_ctor((Control *)self);
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
    ctrl_destroy((Control *)self);
  }
  self->radio_font = (u32)(*(i8 * *)(draw_current_font_rest + 4));
  ctrl_init((Control *)self,parent,3,ctrl_id,rect);
  self->is_enabled = 0;
  self->on_click = 0;
  self->on_select = 0;
  self->font = item_count;
  self->scroll_pos = columns;
  self->edit_font = 0;
  handle = radiogrp_create_items((iptr)&self->font,(int *)rect,columns,(iptr)self,item_count,labels,1,
                       self->radio_font);
  self->items_handle = handle;
  handle = (u32)mem_handle_lock(self->items_handle);
  self->items_ptr = handle;
  return;
}

/* 005311b0 auto */
void __thiscall radiogrp_set_select_callback(Control *self,iptr callback)

{
  self->is_enabled = callback;
  return;
}

/* 005311e0 auto */
void __thiscall radiogrp_set_dblclick_callback(Control *self,iptr callback)

{
  self->on_click = callback;
  return;
}

/* 00551d20 auto */
/* Library Function - Single Match
    protected: char * __thiscall streambuf::egptr(void)const 
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall listbox_get_count(ListboxGetCountView *self)

{
  return self->item_count;
}

/* 00551d50 auto */
i32 __thiscall listbox_get_cur_sel(ListBoxGetSelView *self)

{
  i32 cur_sel;
  
  cur_sel = listbox_hwnd_get_cur_sel(self->hwnd);
  return cur_sel;
}

/* 00551d80 auto */
void __thiscall listbox_set_cur_sel(ListBoxSetSelView *self,i32 index)

{
  listbox_hwnd_set_cur_sel(self->hwnd,index);
  return;
}

/* 00551dc0 auto */
void __thiscall listbox_set_dblclick_callback(ListBoxDblClickSetView *self,iptr callback)

{
  self->on_dblclick = callback;
  return;
}

/* 00551df0 auto */
void __thiscall listbox_set_select_callback(ListBoxSelectSetView *self,iptr callback)

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
    crt_vector_dtor_iterator(self,0x3c,VECTOR_COUNT(self),(code *)checkbox_dtor);
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

Control * __thiscall edit_vector_dtor(Control *self,uint flags)

{
  if ((flags & 2) == 0) {
    edit_dtor(self);
    if ((flags & 1) != 0) {
      operator_delete(self);
    }
  }
  else {
    crt_vector_dtor_iterator(self,0x48,VECTOR_COUNT(self),(code *)edit_dtor);
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

Control * __thiscall ctrl_vector_dtor(Control *self,uint flags)

{
  if ((flags & 2) == 0) {
    ctrl_dtor(self);
    if ((flags & 1) != 0) {
      operator_delete(self);
    }
  }
  else {
    crt_vector_dtor_iterator(self,0x3c,VECTOR_COUNT(self),(code *)ctrl_dtor);
    operator_delete(&VECTOR_COUNT(self));
  }
  return self;
}

/* 005a94d0 auto */
ListBoxControl * __thiscall listbox_scalar_dtor(ListBoxControl *self,uint flags)

{
  listbox_dtor(self);
  if ((flags & 1) != 0) {
    operator_delete(self);
  }
  return self;
}

/* 005a9640 auto */
void __thiscall checkbox_disable(CheckboxDisableView *self)

{
  self->is_enabled = 0;
  return;
}

/* 005a9670 auto */
void __thiscall listbox_get_text(ListBoxTextView *self,i32 index,iptr buffer)

{
  listbox_hwnd_get_text(self->hwnd,index,buffer);
  return;
}

/* 005a96b0 auto */
void __thiscall listbox_get_sel_text(ListBoxSelTextView *self,iptr buffer)

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
u32 __thiscall control_get_type(ControlTypeView *self)

{
  return self->ctrl_type;
}

/* 005c5e80 auto */
u32 __thiscall control_get_next(ControlNextView *self)

{
  return self->next_control;
}

/* 005c5ea0 auto */
u8 __thiscall ctrl_get_initial_focus(ControlInitialFocusView *self)

{
  return self->initial_focus;
}

/* 005c5ec0 auto */
u32 __thiscall checkbox_is_enabled(CheckboxEnabledView *self)

{
  return self->is_enabled;
}

/* 005c5ee0 auto */
u32 __thiscall radiogrp_get_items(RadioGroupItemsView *self)

{
  return self->items;
}

/* 005c5f00 auto */
u32 __thiscall radiogrp_item_count(RadioGroupCountView *self)

{
  return self->item_count;
}

/* 005c8f50 auto */
int __thiscall ctrl_get_rect(void *self)

{
  return (int)self + 0xc;
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
  iptr window;
  iptr height;
  int value;
  HDC hdcSrc;
  LONG y1;
  DWORD rop;
  tagPOINT origin;
  iptr dib2;
  HWND parent_hwnd;
  
  parent_hwnd = GetParent(hwnd);
  own_data = GetWindowLongA(parent_hwnd,0xc);
  if (own_data == 0) {
    parent_wnd = (WndBase *)GetWindowLongA(parent_hwnd,0);
    value = wnd_get_window(parent_wnd);
    if (*(int *)(value + 0x14) != 0) {
      FillRect(*(HDC *)paint,(RECT *)(paint + 8),*(HBRUSH *)(value + 0x14));
    }
  }
  else {
    self = (DibSurface *)GetWindowLongA(parent_hwnd,0xc);
    parent_wnd = (WndBase *)GetWindowLongA(parent_hwnd,0);
    window = wnd_get_window(parent_wnd);
    dib2 = surface_get_dib(self);
    origin.x = *(int *)(paint + 8);
    origin.y = *(int *)(paint + 0xc);
    MapWindowPoints(hwnd,*(HWND *)(window + 4),&origin,1);
    if ((*(int *)(window + 0x18) != 0) && (gfx_palettized_display == 1)) {
      SelectPalette(*(HDC *)paint,*(HPALETTE *)(window + 0x18),0);
      RealizePalette(*(HDC *)paint);
    }
    rop = 0xcc0020;
    hdcSrc = *(HDC *)(dib2 + 4);
    own_data = origin.x;
    y1 = origin.y;
    height = rect_height(paint + 8);
    value = rect_width(paint + 8);
    BitBlt(*(HDC *)paint,*(int *)(paint + 8),*(int *)(paint + 0xc),value,height,hdcSrc,own_data,y1
           ,rop);
  }
  return;
}

/* 005c9222 auto */
void __cdecl ctrl_parse_hotkey(iptr ctrl,iptr text)

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
  iptr block;
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
        if (*(int *)(block + 0x2c) == 3) {
          **(i32 **)(block + 0x24) = 0;
        }
        else {
          control_set_hwnd(*(ControlHwndSetView **)(block + 4),0);
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
  
  result = control_get_type((ControlTypeView *)ctrl);
  if (result != 3) {
    hwnd_val = control_get_hwnd((ControlHwndView *)ctrl);
    result = 0;
    if (hwnd_val != 0) {
      hWnd = control_get_hwnd((ControlHwndView *)ctrl);
      result = DestroyWindow(hWnd);
    }
  }
  return result;
}

/* 005c9499 auto */
i32 * __cdecl ctrl_init_block(HWND hwnd,iptr owner)

{
  i32 handle;
  i32 *block;
  
  block = (i32 *)0x0;
  if (hwnd == (HWND)0x0) {
    dbg_log((iptr)&str_error_tried_to_initialize_null_control_i);
  }
  else {
    handle = mem_handle_alloc(0x30);
    block = (i32 *)mem_handle_lock(handle);
    block[2] = 0;
    block[5] = 0;
    block[4] = block[5];
    block[3] = block[4];
    *block = handle;
    block[1] = owner;
    block[6] = 0;
    block[7] = 0;
    block[8] = 0;
    block[0xb] = 0;
    SetWindowLongA(hwnd,0,(LONG)block);
  }
  return block;
}

/* 005c9595 auto */
void __cdecl ctrl_hwnd_free_block(HWND hwnd)

{
  i32 handle;
  i32 *block;
  
  if (hwnd == (HWND)0x0) {
    dbg_log((iptr)&str_error_tried_to_dispose_null_control_in_d);
  }
  else {
    block = (i32 *)GetWindowLongA(hwnd,0);
    if (block != (i32 *)0x0) {
      if (block[2] == 0) {
        if (block[3] != 0) {
          DeleteObject((HGDIOBJ)block[3]);
          block[3] = 0;
        }
        if (block[4] != 0) {
          DeleteObject((HGDIOBJ)block[4]);
          block[4] = 0;
        }
        if (block[5] != 0) {
          DeleteObject((HGDIOBJ)block[5]);
          block[5] = 0;
        }
      }
      if (block[0xb] == 2) {
        operator_delete((void *)block[9]);
        block[9] = 0;
      }
      handle = *block;
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

void __thiscall control_set_hwnd(ControlHwndSetView *self,u32 hwnd)

{
  self->hwnd = hwnd;
  return;
}

/* 005c9740 auto */
HWND __cdecl
button_create_hwnd(int *rect,iptr ctrl,i32 label,int visible,GameFont *font)

{
  WndBase *self;
  iptr window;
  iptr height;
  int value;
  HDC hdc;
  int value2;
  HBITMAP h;
  HBITMAP h_00;
  WndPaletteView *parent_wnd;
  PaletteHandleView *this_00;
  HPALETTE hPal;
  GamePalette *this_01;
  iptr logpal;
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
  Control *button;
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
  button = (Control *)ctrl;
  style2 = 0x40810000;
  if (visible != 0) {
    style2 = 0x50810000;
  }
  lpParam = (LPVOID)0x0;
  hMenu = (HMENU)0x0;
  hInstance = err_report_ctx_block.app_hinstance;
  self = (WndBase *)ctrl_get_parent((Control *)ctrl);
  window = wnd_get_window(self);
  hWndParent = *(HWND *)(window + 4);
  height = rect_height((iptr)rect);
  value = rect_width((iptr)rect);
  hwnd2 = CreateWindowExA(4,str_mscontrolclass_2,((i8 *)&button_wnd_title),style2,*rect,
                              rect[1],value,height,hWndParent,hMenu,hInstance,lpParam);
  ctrl_parse_hotkey((iptr)button,(iptr)label_text);
  bounds.left = *rect;
  bounds.top = rect[1];
  bounds.right = rect[2];
  bounds.bottom = rect[3];
  OffsetRect(&bounds,-bounds.left,-bounds.top);
  bounds.right -= 2;
  bounds.bottom -= 2;
  hdc = GetDC(hwnd2);
  value = rect_height((iptr)&bounds);
  value2 = rect_width((iptr)&bounds);
  h = CreateCompatibleBitmap(hdc,value2,value);
  if (h == (HBITMAP)0x0) {
    dbg_log((iptr)&str_could_not_create_bitmap_in_msinitbutton);
    DestroyWindow(hwnd2);
    hwnd2 = (HWND)0x0;
  }
  else {
    value = rect_height((iptr)&bounds);
    value2 = rect_width((iptr)&bounds);
    h_00 = CreateCompatibleBitmap(hdc,value2,value);
    if (h_00 == (HBITMAP)0x0) {
      dbg_log((iptr)&str_could_not_create_bitmap_in_msinitbutton_2);
      DestroyWindow(hwnd2);
      hwnd2 = (HWND)0x0;
    }
    else {
      value = rect_height((iptr)&bounds);
      value2 = rect_width((iptr)&bounds);
      bmp_disabled = CreateCompatibleBitmap(hdc,value2,value);
      if (bmp_disabled == (HBITMAP)0x0) {
        dbg_log((iptr)&str_could_not_create_bitmap_in_msinitbutton_3);
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
            parent_wnd = (WndPaletteView *)ctrl_get_parent(button);
            this_00 = (PaletteHandleView *)wnd_get_palette(parent_wnd);
            hPal = palette_get_hpalette(this_00);
            SelectPalette(mem_dc,hPal,bForceBkgd);
            RealizePalette(mem_dc);
          }
          blue_out = blue;
          green_out = green;
          red_out = red;
          color_index = button->on_select;
          parent_wnd = (WndPaletteView *)ctrl_get_parent(button);
          this_01 = (GamePalette *)wnd_get_palette(parent_wnd);
          logpal = (iptr)palette_get_logpalette(this_01);
          palette_get_entry_rgb(logpal,color_index,(iptr)red_out,(iptr)green_out,(iptr)blue_out);
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
        text_width = rect_width((iptr)&text_rect);
        text_bottom = bounds.bottom;
        value = rect_width((iptr)&bounds);
        value2 = ((bounds.left + value / 2) - text_width / 2) + text_width;
        text_top = bounds.top;
        value = rect_width((iptr)&bounds);
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
        text_width = rect_width((iptr)&text_rect);
        text_bottom = bounds.bottom;
        value = rect_width((iptr)&bounds);
        value = (((value >> 1) + bounds.left) - (text_width >> 1)) + text_width;
        text_top = bounds.top;
        value2 = rect_width((iptr)&bounds);
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
        text_width = rect_width((iptr)&text_rect);
        text_bottom = bounds.bottom;
        value = rect_width((iptr)&bounds);
        value = (((value >> 1) + bounds.left) - (text_width >> 1)) + text_width;
        text_top = bounds.top;
        value2 = rect_width((iptr)&bounds);
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
  Control *self;
  iptr block;
  int enabled;
  i32 ctrl_id;
  
  block = wnd_from_hwnd(hwnd);
  if (block != 0) {
    self = *(Control **)(block + 4);
    enabled = ctrl_is_enabled((ControlEnabledView *)self);
    if (enabled != 0) {
      SetFocus(hwnd);
      *(i32 *)(block + 0x18) = 1;
      wnd_redraw_client(hwnd);
      *(i32 *)(block + 0x18) = 0;
      ui_pump_messages();
      ui_wait_ticks(8);
      wnd_redraw_client(hwnd);
      wnd_active_child = ctrl_get_parent(self);
      ctrl_id = ctrl_get_id((ControlIdView *)self);
      button_fire_callback((ButtonClickView *)self,ctrl_id);
    }
  }
  return;
}

/* 005cacd4: written by hand in src/game/fixups.cpp */

/* 005cb601 auto */
HWND __cdecl spritebtn_create_hwnd(int x,int y,int width,int height,iptr ctrl,int visible)

{
  WndBase *self;
  iptr window;
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
  hWndParent = *(HWND *)(window + 4);
  rect_h = rect_height((iptr)&rect);
  value = rect_width((iptr)&rect);
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
void __thiscall button_fire_callback(ButtonClickView *self,i32 ctrl_id)

{
  if (self->on_click != 0) {
    call_untyped((code *)self->on_click, ctrl_id);
  }
  return;
}

/* 005cbe30 auto */
void __thiscall spritebtn_fire_click(SpriteButtonClickView *self,i32 ctrl_id)

{
  if (self->on_click != 0) {
    call_untyped((code *)self->on_click, ctrl_id);
  }
  return;
}

/* 005cbe70 auto */
void __thiscall spritebtn_fire_rclick(SpriteButtonRClickView *self,i32 ctrl_id)

{
  if (self->on_rclick != 0) {
    call_untyped((code *)self->on_rclick, ctrl_id);
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
HWND __cdecl checkbox_create_hwnd(iptr rect,iptr ctrl,char *label,int visible)

{
  size_t len;
  void *label_copy;
  WndBase *self;
  iptr window;
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
  check_hwnd = *(HWND *)(window + 4);
  height = rect_height(rect);
  value = rect_width(rect);
  check_hwnd = CreateWindowExA(4,str_mscontrolclass_4,((i8 *)&wnd_modal_stack_below_block.checkbox_wnd_title),style2,*(int *)rect,
                           *(int *)(rect + 4),value,height,check_hwnd,hMenu,hInstance,lpParam);
  ctrl_parse_hotkey(ctrl,(iptr)label_copy);
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
    dbg_log((iptr)&str_error_tried_to_dispose_null_checkbox_in);
  }
  return;
}

/* 005cc274 auto */
void __cdecl checkbox_toggle_by_hotkey(HWND hwnd)

{
  Control *self;
  iptr block;
  int checked;
  i32 is_checked;
  i32 ctrl_id;
  
  block = wnd_from_hwnd(hwnd);
  if (block != 0) {
    self = *(Control **)(block + 4);
    SetFocus(hwnd);
    checked = checkbox_is_checked(self);
    if (checked == 0) {
      checkbox_set_checked(self,1);
    }
    else {
      checkbox_set_checked(self,0);
    }
    SetCapture(hwnd);
    InvalidateRect(hwnd,(RECT *)0x0,0);
    wnd_active_child = ctrl_get_parent(self);
    is_checked = checkbox_is_checked(self);
    ctrl_id = ctrl_get_id((ControlIdView *)self);
    checkbox_fire_callback((CheckboxClickView *)self,ctrl_id,is_checked);
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
  WndPaletteView *parent_wnd;
  GamePalette *game_palette2;
  size_t len;
  WndBase *parent_base;
  iptr logpal;
  HWND hwnd_tmp;
  WndKeyNavView *nav_wnd;
  i32 result;
  i8 *red_out;
  i8 *green_out;
  tagRECT *draw_rect;
  i8 *blue_out;
  UINT draw_flags;
  tagRECT rect;
  HBITMAP bitmap;
  iptr block;
  Control *checkbox;
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
  checkbox = *(Control **)(block + 4);
  if (msg < 0x10) {
    if (msg == 0xf) {
      enabled = checkbox_is_enabled((CheckboxEnabledView *)checkbox);
      if (enabled == 0) {
        hwnd_tmp = GetFocus();
        if (hwnd_tmp == hwnd) {
          SetFocus((HWND)0x0);
        }
        bitmap = *(HBITMAP *)(block + 0xc);
      }
      else {
        checked = checkbox_is_checked(checkbox);
        if (checked == 0) {
          bitmap = *(HBITMAP *)(block + 0x10);
        }
        else {
          bitmap = *(HBITMAP *)(block + 0x14);
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
        value = rect_height((iptr)&rect);
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
      label = *(char **)(block + 0x24);
      if ((ctrl_shadow_dx != 0) || (ctrl_shadow_dy != 0)) {
        OffsetRect(&rect,(uint)ctrl_shadow_dx,(uint)ctrl_shadow_dy);
        blue_out = blue;
        green_out = green;
        red_out = red;
        color_index = (uint)ctrl_shadow_color_index;
        parent_wnd = (WndPaletteView *)ctrl_get_parent(checkbox);
        game_palette2 = (GamePalette *)wnd_get_palette(parent_wnd);
        palette_get_entry(game_palette2,color_index,(iptr)red_out,(iptr)green_out,(iptr)blue_out);
        SetTextColor(hdc,CONCAT12(blue[0],CONCAT11(green[0],red[0])));
        draw_flags = 0x24;
        draw_rect = &rect;
        len = _strlen(label);
        DrawTextA(hdc,label,len,draw_rect,draw_flags);
        OffsetRect(&rect,-(uint)ctrl_shadow_dx,-(uint)ctrl_shadow_dy);
      }
      value = checkbox_is_enabled((CheckboxEnabledView *)checkbox);
      if (value == 1) {
        parent_base = (WndBase *)ctrl_get_parent(checkbox);
        value = wnd_get_window(parent_base);
        if (*(int *)(value + 0x40) == 8) {
          if (ctrl_text_color_index == 0) {
            SetTextColor(hdc,0);
          }
          else {
            blue_out = blue;
            green_out = green;
            red_out = red;
            color_index = (uint)ctrl_text_color_index;
            parent_wnd = (WndPaletteView *)ctrl_get_parent(checkbox);
            game_palette2 = (GamePalette *)wnd_get_palette(parent_wnd);
            logpal = (iptr)palette_get_logpalette(game_palette2);
            palette_get_entry_rgb(logpal,color_index,(iptr)red_out,(iptr)green_out,(iptr)blue_out);
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
        value = checkbox_is_enabled((CheckboxEnabledView *)checkbox);
        if (value == 0) {
          parent_base = (WndBase *)ctrl_get_parent(checkbox);
          value = wnd_get_window(parent_base);
          if (*(int *)(value + 0x40) == 8) {
            if (ctrl_disabled_color_index == 0) {
              SetTextColor(hdc,0x404040);
            }
            else {
              blue_out = blue;
              green_out = green;
              red_out = red;
              color_index = (uint)ctrl_disabled_color_index;
              parent_wnd = (WndPaletteView *)ctrl_get_parent(checkbox);
              game_palette2 = (GamePalette *)wnd_get_palette(parent_wnd);
              logpal = (iptr)palette_get_logpalette(game_palette2);
              palette_get_entry_rgb(logpal,color_index,(iptr)red_out,(iptr)green_out,(iptr)blue_out);
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
    nav_wnd = (WndKeyNavView *)ctrl_get_parent(checkbox);
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
        nav_wnd = (WndKeyNavView *)ctrl_get_parent(checkbox);
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
    value = checkbox_is_enabled((CheckboxEnabledView *)checkbox);
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
      ctrl_id = ctrl_get_id((ControlIdView *)checkbox);
      checkbox_fire_callback((CheckboxClickView *)checkbox,ctrl_id,result);
    }
  }
  else {
    if (msg != 0x202) goto default_proc;
    value = checkbox_is_enabled((CheckboxEnabledView *)checkbox);
    if (value != 0) {
      ReleaseCapture();
      wnd_modal_stack_below_block.checkbox_mouse_pressed = 0;
    }
  }
  return 0;
}

/* 005cce40 auto */
void __thiscall checkbox_fire_callback(CheckboxClickView *self,i32 ctrl_id,i32 checked)

{
  if (self->on_toggle != 0) {
    call_untyped((code *)self->on_toggle, ctrl_id,checked);
  }
  return;
}

/* 005cce80 auto */
void __stdcall control_subclass_wndproc(HWND hwnd,int msg,i32 wparam,i32 lparam)

{
  DWORD class_extra;
  WNDPROC base_proc;
  ControlHwndSetView *self;
  
  class_extra = GetClassLongA(hwnd,-0x12);
  base_proc = (WNDPROC)GetWindowLongA(hwnd,class_extra - 4);
  if ((msg == 2) &&
     (self = (ControlHwndSetView *)GetWindowLongA(hwnd,class_extra - 8), self != (ControlHwndSetView *)0x0)) {
    control_set_hwnd(self,0);
  }
  (*base_proc)(hwnd,msg,wparam,lparam);
  return;
}

/* 005ccf17 auto */
HWND __cdecl scrollbar_create_hwnd(int *rect,iptr ctrl,uint style_flags,int visible)

{
  WndBase *parent_wnd;
  iptr window;
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
    parent_hwnd = *(HWND *)(window + 4);
    height = rect_height((iptr)rect);
    value = rect_width((iptr)rect);
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
  value = wnd_get_window(parent_wnd);
  parent_hwnd = *(HWND *)(value + 4);
  value = rect_height((iptr)rect);
  nWidth = rect_width((iptr)rect);
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
  ScrollbarPosView *self;
  iptr cur_pos;
  iptr parent;
  WPARAM *rect_ptr;
  iptr page_size;
  int value;
  u32 new_pos;
  LPARAM pos_lparam;
  
  class_extra = GetClassLongA(hwnd,-0x12);
  self = (ScrollbarPosView *)GetWindowLongA(hwnd,class_extra - 8);
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
        parent = ctrl_get_parent((Control *)self);
        wnd_set_active_child(parent);
        self->cur_pos = new_pos;
        scrollbar_fire_change((ScrollbarChangeView *)self,new_pos);
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
        parent = ctrl_get_parent((Control *)self);
        wnd_set_active_child(parent);
        self->cur_pos = new_pos;
        scrollbar_fire_change((ScrollbarChangeView *)self,new_pos);
      }
      break;
    case 2:
      value = scrollbar_get_page_size((ScrollbarPageView *)self);
      SetScrollPos(hwnd,2,cur_pos - value,1);
      new_pos = GetScrollPos(hwnd,2);
      parent = ctrl_get_parent((Control *)self);
      wnd_set_active_child(parent);
      self->cur_pos = new_pos;
      scrollbar_fire_change((ScrollbarChangeView *)self,new_pos);
      break;
    case 3:
      page_size = scrollbar_get_page_size((ScrollbarPageView *)self);
      SetScrollPos(hwnd,2,cur_pos + page_size,1);
      new_pos = GetScrollPos(hwnd,2);
      parent = ctrl_get_parent((Control *)self);
      wnd_set_active_child(parent);
      self->cur_pos = new_pos;
      scrollbar_fire_change((ScrollbarChangeView *)self,new_pos);
      break;
    case 4:
      SetScrollPos(hwnd,2,(int)thumb_pos,1);
      parent = ctrl_get_parent((Control *)self);
      wnd_set_active_child(parent);
      self->cur_pos = (int)thumb_pos;
      scrollbar_fire_change((ScrollbarChangeView *)self,self->cur_pos);
      break;
    case 5:
      parent = ctrl_get_parent((Control *)self);
      wnd_set_active_child(parent);
      scrollbar_fire_track((ScrollbarTrackView *)self,(int)thumb_pos);
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
u32 __thiscall scrollbar_get_cur_pos(ScrollbarPosView *self)

{
  return self->cur_pos;
}

/* 005cd640 auto */
void __thiscall scrollbar_fire_change(ScrollbarChangeView *self,i32 pos)

{
  if (self->on_change != 0) {
    call_untyped((code *)self->on_change, pos);
  }
  return;
}

/* 005cd680 auto */
void __thiscall scrollbar_fire_track(ScrollbarTrackView *self,i32 pos)

{
  if (self->on_track != 0) {
    call_untyped((code *)self->on_track, pos);
  }
  return;
}

/* 005cd6c0 auto */
u32 __thiscall scrollbar_get_page_size(ScrollbarPageView *self)

{
  return self->page_size;
}

/* 005d25c0 auto */
void __thiscall
edit_create_at
          (EditControl *self,iptr parent,i32 ctrl_id,int x,int y,int width,
          iptr text)

{
  tagRECT rect;
  
  self->edit_font = (u32)(*(i8 * *)(draw_current_font_rest + 12));
  self->is_enabled = 0;
  SetRect(&rect,x,y,width + x,y + 0x1e);
  edit_create(self,parent,ctrl_id,(iptr)&rect,text);
  return;
}

/* 005d2740 auto */
HWND __cdecl edit_create_window(int *rect,iptr ctrl,uint flags,int visible,GameFont *font)

{
  WndBase *parent_wnd;
  iptr window;
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
    parent_hwnd = *(HWND *)(window + 4);
    height = rect_height((iptr)rect);
    value = rect_width((iptr)rect);
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
  value = wnd_get_window(parent_wnd);
  parent_hwnd = *(HWND *)(value + 4);
  value = rect_height((iptr)rect);
  nWidth = rect_width((iptr)rect);
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
  Control *self;
  DWORD class_extra;
  WNDPROC lpPrevWndFunc;
  iptr key;
  HWND parent_hwnd;
  iptr parent;
  WndBase *this_00;
  int window;
  LRESULT result;
  iptr long_index;
  int pass_through;
  
  self = (Control *)GetWindowLongA(hwnd,10);
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
      if (self != (Control *)0x0) {
        control_set_hwnd((ControlHwndSetView *)self,0);
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
      if ((*(byte *)(window + 0x49) & 2) != 0) {
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
        edit_fire_key_callback((EditKeyView *)self,key);
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
        pass_through = edit_fire_key_callback((EditKeyView *)self,parent);
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
i32 __thiscall edit_fire_key_callback(EditKeyView *self,iptr key)

{
  i32 result;
  
  if (self->on_key == 0) {
    result = 1;
  }
  else {
    result = call_untyped((code *)self->on_key, self->control_id,key);
  }
  return result;
}

/* 005d3130 auto */
HWND __cdecl combo_create_window(int *rect,iptr ctrl,int visible)

{
  WndBase *parent_wnd;
  iptr window;
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
    parent_hwnd = *(HWND *)(window + 4);
    height = rect_height((iptr)rect);
    value = rect_width((iptr)rect);
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
  value = wnd_get_window(parent_wnd);
  parent_hwnd = *(HWND *)(value + 4);
  value = rect_height((iptr)rect);
  nWidth = rect_width((iptr)rect);
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
  Control *self;
  iptr parent;
  HWND parent_hwnd;
  WndBase *this_00;
  iptr window;
  LRESULT result;
  iptr long_index;
  
  class_extra = GetClassLongA(hwnd,-0x12);
  lpPrevWndFunc = (WNDPROC)GetWindowLongA(hwnd,class_extra - 8);
  self = (Control *)GetWindowLongA(hwnd,class_extra - 4);
  if (self == (Control *)0x0) {
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
      if (self != (Control *)0x0) {
        control_set_hwnd((ControlHwndSetView *)self,0);
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
      if ((*(byte *)(window + 0x49) & 2) != 0) {
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
        if (self == (Control *)0x0) {
          return 1;
        }
        combo_fire_selchange((ComboBoxSelChangeView *)self);
        return 1;
      }
      if (wparam >> 0x10 != 2) {
        return 1;
      }
      combo_fire_dblclick((ComboBoxDblClickView *)self);
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
void __thiscall combo_fire_dblclick(ComboBoxDblClickView *self)

{
  if (self->on_dblclick != 0) {
    call_untyped((code *)self->on_dblclick, self->control_id);
  }
  return;
}

/* 005d3760 auto */
void __thiscall combo_fire_selchange(ComboBoxSelChangeView *self)

{
  if (self->on_selchange != 0) {
    call_untyped((code *)self->on_selchange, self->control_id);
  }
  return;
}

/* 005d37a0 auto */
HWND __cdecl listbox_create_hwnd(int *rect,iptr ctrl,int visible,int multi_column,GameFont *font)

{
  uint style_bits;
  WndBase *parent_wnd;
  iptr window;
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
    parent_hwnd = *(HWND *)(window + 4);
    height = rect_height((iptr)rect);
    value = rect_width((iptr)rect);
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
  value = wnd_get_window(parent_wnd);
  parent_hwnd = *(HWND *)(value + 4);
  value = rect_height((iptr)rect);
  nWidth = rect_width((iptr)rect);
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
  Control *self;
  iptr parent;
  HWND parent_hwnd;
  WndBase *this_00;
  iptr window;
  LRESULT result;
  iptr long_index;
  
  class_extra = GetClassLongA(hwnd,-0x12);
  lpPrevWndFunc = (WNDPROC)GetWindowLongA(hwnd,class_extra - 8);
  self = (Control *)GetWindowLongA(hwnd,class_extra - 4);
  if (self == (Control *)0x0) {
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
      if (self != (Control *)0x0) {
        control_set_hwnd((ControlHwndSetView *)self,0);
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
      if ((*(byte *)(window + 0x49) & 2) != 0) {
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
        if (self == (Control *)0x0) {
          return 1;
        }
        listbox_fire_selchange((ListBoxSelChangeView *)self);
        return 1;
      }
      if (wparam >> 0x10 != 2) {
        return 1;
      }
      listbox_fire_dblclick((ListBoxDblClickView *)self);
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
void __cdecl listbox_hwnd_get_sel_text(HWND hwnd,i32 buffer)

{
  LRESULT cur_sel;
  
  cur_sel = SendMessageA(hwnd,0x188,0,0);
  if (cur_sel == -1) {
    crt_strcpy((char *)((void *)buffer),((i8 *)&listbox_no_sel_text));
  }
  else {
    listbox_hwnd_get_text(hwnd,cur_sel,buffer);
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
void __thiscall listbox_fire_dblclick(ListBoxDblClickView *self)

{
  if (self->on_dblclick != 0) {
    call_untyped((code *)self->on_dblclick, self->control_id);
  }
  return;
}

/* 005d3f70 auto */
void __thiscall listbox_fire_selchange(ListBoxSelChangeView *self)

{
  if (self->on_selchange != 0) {
    call_untyped((code *)self->on_selchange, self->control_id);
  }
  return;
}

/* 005d4014 auto */
void __thiscall radiogrp_show_all(RadioGroupShowView *self)

{
  int i;
  
  for (i = 0; i < (int)self->item_count; i++) {
    hwnd_show(*(i32 *)(self->items + i * 0xa4));
    wnd_invalidate(*(i32 *)(self->items + i * 0xa4));
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
          (SpriteButton *self,WndPaletteView *parent,i32 ctrl_id,int x,int y,
          int width,int height,iptr sprite,uint bg_color)

{
  u32 value;
  int size;
  WndPaletteView *parent_wnd;
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
  ctrl_init((Control *)self,(iptr)parent,6,ctrl_id,(iptr)&rect);
  self->is_enabled = 0;
  self->on_click = 0;
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
            ((DibSurface *)&self->on_select,(iptr)(self->button_surface),(iptr)&src_rect,
             (iptr)&dst_rect);
  parent_wnd = (WndPaletteView *)ctrl_get_parent((Control *)self);
  palette = wnd_get_palette(parent_wnd);
  surface_apply_palette((DibSurface *)self->button_surface,(PaletteVersionView *)palette);
  parent_wnd = (WndPaletteView *)ctrl_get_parent((Control *)self);
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
  iptr window;
  int half_row;
  HWND item_hwnd;
  iptr block;
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
  col_width = rect_width((iptr)rect);
  col_width = col_width / columns;
  row_height = rect_height((iptr)rect);
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
                              (half_row - half_item) + item_y,col_width,nHeight,*(HWND *)(window + 4),hMenu,
                              hInstance,lpParam);
    *(HWND *)(items + index * 0xa4) = item_hwnd;
    block = (iptr)ctrl_init_block(*(i32 *)(items + index * 0xa4),group);
    if (index == 0) {
      *(i32 *)(block + 8) = 0;
    }
    else {
      *(i32 *)(block + 8) = 1;
    }
    *(HBITMAP *)(block + 0xc) = bmp_unchecked;
    *(HBITMAP *)(block + 0x10) = bmp_checked;
    *(HBITMAP *)(block + 0x14) = bmp_focus;
    *(uint *)(block + 0x24) = index * 0xa4 + items;
    *(i32 *)(block + 0x2c) = 3;
    SetWindowLongA(*(HWND *)(items + index * 0xa4),-4,(iptr)radiogrp_item_wndproc);
    SetRect((LPRECT)(index * 0xa4 + items + 4),item_x,(half_row - half_item) + item_y,
            item_x + col_width,(half_row - half_item) + item_y + nHeight);
    *(uint *)(items + 0x14 + index * 0xa4) = index;
    label = *(char **)(labels + index * 4);
    if (*label == '!') {
      *(i32 *)(items + 0x18 + index * 0xa4) = 0;
      label++;
    }
    else if (*label == '^') {
      *(i32 *)(items + 0x18 + index * 0xa4) = 1;
      radiogrp_set_selected((RadioGroupSetSelView *)group,index);
      label++;
    }
    else {
      *(i32 *)(items + 0x18 + index * 0xa4) = 1;
    }
    crt_strcpy((char *)((void *)(index * 0xa4 + items + 0x1c)),(const char *)((void *)label));
    cursor = (char *)(index * 0xa4 + items + 0x1c);
    *(i32 *)(items + 0xa0 + index * 0xa4) = 0;
    while( true ) {
      if (*cursor == '\0') goto store_hotkey;
      if (*cursor == '~') break;
      hotkey_pos = (int *)(items + 0xa0 + index * 0xa4);
      *hotkey_pos = *hotkey_pos + 1;
      cursor++;
    }
    for (index = *(uint *)(items + 0xa0 + index * 0xa4);
        len = _strlen((char *)(index * 0xa4 + items + 0x1c)), index < len;
        index = index + 1) {
      *(i8 *)(index * 0xa5 + 0x1c + items) =
           *(i8 *)(index * 0xa5 + 0x1d + items);
    }
store_hotkey:
    len = _strlen((char *)(index * 0xa4 + items + 0x1c));
    if (*(uint *)(items + 0xa0 + index * 0xa4) < len) {
      hotkey[0] = *(char *)(*(int *)(items + 0xa0 + index * 0xa4) + index * 0xa4 + 0x1c +
                            items);
      hotkey[1] = 0;
      __strlwr(hotkey);
      *(char *)(items + 0x9c + index * 0xa4) = hotkey[0];
    }
    else {
      *(i32 *)(items + 0xa0 + index * 0xa4) = 0xffffffff;
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
    dbg_log((iptr)&str_error_tried_to_dismantle_null_radioset_i);
  }
  else {
    items = (iptr)mem_handle_lock((HGLOBAL)handle);
    for (i = 0; i < count; i++) {
      if (*(int *)(items + i * 0xa4) != 0) {
        DestroyWindow(*(HWND *)(items + i * 0xa4));
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
  RadioGroupItemsView *self;
  iptr block;
  iptr selected;
  iptr old_sel;
  iptr items;
  iptr new_sel;
  int item;
  i32 sel_index;
  i32 ctrl_id;
  RECT *null_rect;
  BOOL erase;
  
  block = wnd_from_hwnd(hwnd);
  if (block != 0) {
    self = *(RadioGroupItemsView **)(block + 4);
    item = *(int *)(block + 0x24);
    SetFocus(hwnd);
    selected = radiogrp_get_selected((RadioGroupGetSelView *)self);
    if ((selected != *(int *)(item + 0x14)) && (*(int *)(item + 0x18) == 1)) {
      erase = 0;
      null_rect = (RECT *)0x0;
      old_sel = radiogrp_get_selected((RadioGroupGetSelView *)self);
      items = radiogrp_get_items(self);
      InvalidateRect(*(HWND *)(items + old_sel * 0xa4),null_rect,erase);
      radiogrp_set_selected((RadioGroupSetSelView *)self,*(i32 *)(item + 0x14));
      erase = 0;
      null_rect = (RECT *)0x0;
      new_sel = radiogrp_get_selected((RadioGroupGetSelView *)self);
      item = radiogrp_get_items(self);
      InvalidateRect(*(HWND *)(item + new_sel * 0xa4),null_rect,erase);
    }
    wnd_active_child = ctrl_get_parent((Control *)self);
    sel_index = radiogrp_get_selected((RadioGroupGetSelView *)self);
    ctrl_id = ctrl_get_id((ControlIdView *)self);
    radiogrp_fire_callback((RadioGroupClickView *)self,ctrl_id,sel_index);
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
  WndPaletteView *parent_wnd;
  GamePalette *game_palette2;
  size_t len;
  WndBase *parent_base;
  int value;
  iptr parent;
  HWND hwnd_tmp;
  WndKeyNavView *nav_wnd;
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
  iptr block;
  tagPAINTSTRUCT ps;
  HGDIOBJ old_font;
  tagSIZE bmp_size;
  int remaining;
  HDC hdc;
  int underline_end;
  int next_index;
  i8 green[4];
  int underline_start;
  iptr item;
  int box_left;
  int box_top;
  int box_right;
  int box_bottom;
  HBRUSH brush;
  i8 red[4];
  i8 blue[4];
  RadioGroupItemsView *group;
  i32 *font_data;
  tagRECT text_rect;
  char prefix[128];
  
  block = wnd_from_hwnd(hwnd);
  group = *(RadioGroupItemsView **)(block + 4);
  item = *(int *)(block + 0x24);
  if (msg < 0x10) {
    if (msg == 0xf) {
      if (*(int *)(item + 0x18) == 1) {
        selected = radiogrp_get_selected((RadioGroupGetSelView *)group);
        if (selected == *(int *)(item + 0x14)) {
          bitmap = *(HBITMAP *)(block + 0x14);
        }
        else {
          bitmap = *(HBITMAP *)(block + 0x10);
        }
      }
      else {
        bitmap = *(HBITMAP *)(block + 0xc);
      }
      GetBitmapDimensionEx(bitmap,&bmp_size);
      rect.left = *(int *)(item + 4);
      rect.top = *(int *)(item + 8);
      rect.right = *(int *)(item + 0xc);
      rect.bottom = *(int *)(item + 0x10);
      box_left = rect.left;
      box_top = rect.top;
      box_right = rect.right;
      box_bottom = rect.bottom;
      if (radio_lbutton_captured != 0) {
        box_right = rect.left + 0x20;
        height = rect_height((iptr)&rect);
        box_top = height - 0x14 + rect.top >> 1;
        box_bottom = rect.top + 0x14;
      }
      InvalidateRect(hwnd,(RECT *)0x0,1);
      OffsetRect(&rect,-rect.left,-rect.top);
      hdc = BeginPaint(hwnd,&ps);
      ctrl_paint_parent_bkgnd((iptr)&ps,hwnd);
      result = font_get_handle(*(GameFont **)((RadioGroupItemsViewExt *)group)->item_font);
      font_data = (i32 *)mem_handle_lock(result);
      old_font = SelectObject(hdc,(HGDIOBJ)*font_data);
      result = font_get_handle(*(GameFont **)((RadioGroupItemsViewExt *)group)->item_font);
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
        parent_wnd = (WndPaletteView *)ctrl_get_parent((Control *)group);
        game_palette2 = (GamePalette *)wnd_get_palette(parent_wnd);
        palette_get_entry(game_palette2,color_index,(iptr)red_out,(iptr)green_out,(iptr)blue_out);
        SetTextColor(hdc,CONCAT12(blue[0],CONCAT11(green[0],red[0])));
        draw_flags = 0x24;
        draw_rect = &rect;
        len = _strlen((char *)(item + 0x1c));
        DrawTextA(hdc,(LPCSTR)(item + 0x1c),len,draw_rect,draw_flags);
        OffsetRect(&rect,-(uint)radio_shadow_dx,-(uint)radio_shadow_dy);
      }
      if (*(int *)(item + 0x18) == 1) {
        parent_base = (WndBase *)ctrl_get_parent((Control *)group);
        value = wnd_get_window(parent_base);
        if (*(int *)(value + 0x40) == 8) {
          if (radio_text_color_index == 0) {
            SetTextColor(hdc,0);
          }
          else {
            blue_out = blue;
            green_out = green;
            red_out = red;
            color_index = (uint)radio_text_color_index;
            parent_wnd = (WndPaletteView *)ctrl_get_parent((Control *)group);
            game_palette2 = (GamePalette *)wnd_get_palette(parent_wnd);
            parent = (iptr)palette_get_logpalette(game_palette2);
            palette_get_entry_rgb(parent,color_index,(iptr)red_out,(iptr)green_out,(iptr)blue_out);
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
      else if (*(int *)(item + 0x18) == 0) {
        parent_base = (WndBase *)ctrl_get_parent((Control *)group);
        value = wnd_get_window(parent_base);
        if (*(int *)(value + 0x40) == 8) {
          if (radio_disabled_color_index == 0) {
            SetTextColor(hdc,0x404040);
          }
          else {
            blue_out = blue;
            green_out = green;
            red_out = red;
            color_index = (uint)radio_disabled_color_index;
            parent_wnd = (WndPaletteView *)ctrl_get_parent((Control *)group);
            game_palette2 = (GamePalette *)wnd_get_palette(parent_wnd);
            parent = (iptr)palette_get_logpalette(game_palette2);
            palette_get_entry_rgb(parent,color_index,(iptr)red_out,(iptr)green_out,(iptr)blue_out);
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
      len = _strlen((char *)(item + 0x1c));
      DrawTextA(hdc,(LPCSTR)(item + 0x1c),len,draw_rect,draw_flags);
      if (*(int *)(item + 0xa0) != -1) {
        crt_strcpy(prefix,(const char *)((void *)(item + 0x1c)));
        prefix[*(int *)(item + 0xa0)] = '\0';
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
        crt_strcpy(prefix,(const char *)((void *)(item + 0x1c)));
        prefix[*(int *)(item + 0xa0) + 1] = '\0';
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
    nav_wnd = (WndKeyNavView *)ctrl_get_parent((Control *)group);
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
        value = radiogrp_get_selected((RadioGroupGetSelView *)group);
        if ((value != *(int *)(item + 0x14)) && (*(int *)(item + 0x18) == 1)) {
          value = radiogrp_get_selected((RadioGroupGetSelView *)group);
          if (value != -1) {
            erase = 0;
            null_rect = (RECT *)0x0;
            value = radiogrp_get_selected((RadioGroupGetSelView *)group);
            items = radiogrp_get_items(group);
            InvalidateRect(*(HWND *)(items + value * 0xa4),null_rect,erase);
          }
          radiogrp_set_selected((RadioGroupSetSelView *)group,*(i32 *)(item + 0x14));
          SetFocus(hwnd);
          InvalidateRect(hwnd,(RECT *)0x0,0);
          parent = ctrl_get_parent((Control *)group);
          wnd_set_active_child(parent);
          result = radiogrp_get_selected((RadioGroupGetSelView *)group);
          ctrl_id = ctrl_get_id((ControlIdView *)group);
          radiogrp_fire_callback((RadioGroupClickView *)group,ctrl_id,result);
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
          nav_wnd = (WndKeyNavView *)ctrl_get_parent((Control *)group);
          nav_enabled = wnd_keyboard_nav_enabled(nav_wnd);
          if (nav_enabled != '\0') {
            SendMessageA(hwnd,0x201,0,0);
            SendMessageA(hwnd,0x202,0,0);
            return 0;
          }
        }
        if ((((wparam == 0x27) || (wparam == 0x28)) || (wparam == 0x66)) || (wparam == 0x62)) {
          nav_wnd = (WndKeyNavView *)ctrl_get_parent((Control *)group);
          nav_enabled = wnd_keyboard_nav_enabled(nav_wnd);
          if (nav_enabled != '\0') {
            remaining = radiogrp_item_count((RadioGroupCountView *)group);
            next_index = *(int *)(item + 0x14) + 1;
            value = radiogrp_item_count((RadioGroupCountView *)group);
            if (value <= next_index) {
              next_index = 0;
            }
            while ((0 < remaining &&
                   (value = radiogrp_get_items(group),
                   *(int *)(value + 0x18 + next_index * 0xa4) == 0))) {
              remaining--;
              next_index++;
              value = radiogrp_item_count((RadioGroupCountView *)group);
              if (value <= next_index) {
                next_index = 0;
              }
            }
            if (remaining < 1) {
              return 0;
            }
            value = radiogrp_get_items(group);
            SetFocus(*(HWND *)(value + next_index * 0xa4));
            erase = 0;
            null_rect = (RECT *)0x0;
            value = radiogrp_get_selected((RadioGroupGetSelView *)group);
            items2 = radiogrp_get_items(group);
            InvalidateRect(*(HWND *)(items2 + value * 0xa4),null_rect,erase);
            radiogrp_set_selected((RadioGroupSetSelView *)group,next_index);
            erase = 0;
            null_rect = (RECT *)0x0;
            value = radiogrp_get_items(group);
            InvalidateRect(*(HWND *)(value + next_index * 0xa4),null_rect,erase);
            parent = ctrl_get_parent((Control *)group);
            wnd_set_active_child(parent);
            result = radiogrp_get_selected((RadioGroupGetSelView *)group);
            ctrl_id = ctrl_get_id((ControlIdView *)group);
            radiogrp_fire_callback((RadioGroupClickView *)group,ctrl_id,result);
            return 0;
          }
        }
        if (((wparam == 0x26) || (wparam == 0x25)) || ((wparam == 0x68 || (wparam == 100)))) {
          nav_wnd = (WndKeyNavView *)ctrl_get_parent((Control *)group);
          nav_enabled = wnd_keyboard_nav_enabled(nav_wnd);
          if (nav_enabled != '\0') {
            remaining = radiogrp_item_count((RadioGroupCountView *)group);
            next_index = *(int *)(item + 0x14) - 1;
            if (next_index < 0) {
              next_index = radiogrp_item_count((RadioGroupCountView *)group);
              next_index--;
            }
            while ((0 < remaining &&
                   (value = radiogrp_get_items(group),
                   *(int *)(value + 0x18 + next_index * 0xa4) == 0))) {
              remaining--;
              next_index--;
              if (next_index < 0) {
                next_index = radiogrp_item_count((RadioGroupCountView *)group);
                next_index--;
              }
            }
            if (remaining < 1) {
              return 0;
            }
            value = radiogrp_get_items(group);
            SetFocus(*(HWND *)(value + next_index * 0xa4));
            erase = 0;
            null_rect = (RECT *)0x0;
            value = radiogrp_get_selected((RadioGroupGetSelView *)group);
            items3 = radiogrp_get_items(group);
            InvalidateRect(*(HWND *)(items3 + value * 0xa4),null_rect,erase);
            radiogrp_set_selected((RadioGroupSetSelView *)group,next_index);
            erase = 0;
            null_rect = (RECT *)0x0;
            value = radiogrp_get_items(group);
            InvalidateRect(*(HWND *)(value + next_index * 0xa4),null_rect,erase);
            parent = ctrl_get_parent((Control *)group);
            wnd_set_active_child(parent);
            result = radiogrp_get_selected((RadioGroupGetSelView *)group);
            ctrl_id = ctrl_get_id((ControlIdView *)group);
            radiogrp_fire_callback((RadioGroupClickView *)group,ctrl_id,result);
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
      if (*(int *)(item + 0x18) == 1) {
        parent = ctrl_get_parent((Control *)group);
        wnd_set_active_child(parent);
        value = radiogrp_get_selected((RadioGroupGetSelView *)group);
        if (value != *(int *)(item + 0x14)) {
          value = radiogrp_get_selected((RadioGroupGetSelView *)group);
          if (value != -1) {
            erase = 0;
            null_rect = (RECT *)0x0;
            value = radiogrp_get_selected((RadioGroupGetSelView *)group);
            items = radiogrp_get_items(group);
            InvalidateRect(*(HWND *)(items + value * 0xa4),null_rect,erase);
          }
          radiogrp_set_selected((RadioGroupSetSelView *)group,*(i32 *)(item + 0x14));
        }
        result = *(i32 *)(item + 0x14);
        ctrl_id = ctrl_get_id((ControlIdView *)group);
        radiogrp_fire_dblclick((RadioGroupDblClickView *)group,ctrl_id,result);
      }
      break;
    case 0x204:
      if (radio_rbutton_captured == 0) {
        radio_rbutton_captured = 1;
        SetCapture(hwnd);
        parent = ctrl_get_parent((Control *)group);
        wnd_set_active_child(parent);
        result = *(i32 *)(item + 0x14);
        ctrl_id = ctrl_get_id((ControlIdView *)group);
        radiogrp_fire_rclick((RadioGroupRClickView *)group,ctrl_id,result);
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
  if ((cmp == 0) && (block = wnd_from_hwnd(hwnd), *(int *)(block + 0x2c) == 3)) {
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
  iptr block;
  int selected;
  iptr item;
  
  block = wnd_from_hwnd(hwnd);
  item = *(iptr *)(block + 0x24);
  selected = radiogrp_get_selected(*(RadioGroupGetSelView **)(block + 4));
  return (uint)(selected == *(int *)(item + 0x14));
}

/* 005dac39 auto */
i32 __cdecl radiogrp_hwnds_same_group(int hwnd_a,int hwnd_b)

{
  iptr is_radio_a;
  iptr is_radio_b;
  int block_a;
  iptr block_b;
  
  is_radio_a = ctrl_hwnd_is_radio(hwnd_a);
  if ((is_radio_a == 0) || (is_radio_b = ctrl_hwnd_is_radio(hwnd_b), is_radio_b == 0)) {
    return 0;
  }
  if (hwnd_a == hwnd_b) {
    return 1;
  }
  block_a = wnd_from_hwnd(hwnd_a);
  block_b = wnd_from_hwnd(hwnd_b);
  if (*(int *)(block_b + 4) == *(int *)(block_a + 4)) {
    return 1;
  }
  return 0;
}

/* 005dad40 auto */
void __thiscall radiogrp_fire_callback(RadioGroupClickView *self,i32 ctrl_id,i32 index)

{
  if (self->on_select != 0) {
    call_untyped((code *)self->on_select, ctrl_id,index);
  }
  return;
}

/* 005dad80 auto */
void __thiscall radiogrp_fire_dblclick(RadioGroupDblClickView *self,i32 ctrl_id,i32 index)

{
  if (self->on_dblclick != 0) {
    call_untyped((code *)self->on_dblclick, ctrl_id,index);
  }
  return;
}

/* 005dadc0 auto */
void __thiscall radiogrp_fire_rclick(RadioGroupRClickView *self,i32 ctrl_id,i32 index)

{
  if (self->on_rclick != 0) {
    call_untyped((code *)self->on_rclick, ctrl_id,index);
  }
  return;
}

/* 005db0d0 auto */
void __thiscall scrollbar_set_page_size(Control *self,u32 page_size)

{
  int min_pos;
  int max_pos;
  
  scrollbar_get_ctl_range(self,(iptr)&min_pos,(iptr)&max_pos);
  if ((int)page_size <= max_pos - min_pos) {
    self->on_select = page_size;
  }
  return;
}

/* 005db110 auto */
void __thiscall scrollbar_get_ctl_range(Control *self,iptr min_out,iptr max_out)

{
  scrollbar_hwnd_get_range(self->hwnd,(LPINT)min_out,(LPINT)max_out);
  return;
}

/* 005ea7d7 auto */
i32 __cdecl ctrl_list_find_by_hwnd(int hwnd,ControlNextView *list)

{
  int ctrl_hwnd;
  ControlNextView *ctrl;
  
  ctrl = list;
  while( true ) {
    if (ctrl == (ControlNextView *)0x0) {
      return 0;
    }
    ctrl_hwnd = control_get_hwnd((ControlHwndView *)ctrl);
    if (ctrl_hwnd == hwnd) break;
    ctrl = (ControlNextView *)control_get_next(ctrl);
  }
  return (i32)ctrl;
}

/* 005eac6d auto */
i32 __cdecl ctrl_list_find_type11_hwnd(ControlNextView *list)

{
  int ctrl_type;
  i32 hwnd;
  ControlNextView *ctrl;
  
  ctrl = list;
  while( true ) {
    if (ctrl == (ControlNextView *)0x0) {
      return 0;
    }
    ctrl_type = control_get_type((ControlTypeView *)ctrl);
    if (ctrl_type == 0xb) break;
    ctrl = (ControlNextView *)control_get_next(ctrl);
  }
  hwnd = control_get_hwnd((ControlHwndView *)ctrl);
  return hwnd;
}

/* 005eacc0: written by hand in src/game/retvals.cpp */

/* 005eb2f0 auto */
void __thiscall edit_fire_maxtext_callback(EditMaxTextView *self)

{
  if (self->on_maxtext != 0) {
    call_untyped((code *)self->on_maxtext, self->control_id);
  }
  return;
}

/* 005eb330 auto */
void __thiscall edit_fire_change_callback(EditChangeView *self)

{
  if (self->on_change != 0) {
    call_untyped((code *)self->on_change, self->control_id);
  }
  return;
}

/* 005eb3ed auto */
uint __cdecl input_map_vkey(uint vkey)

{
  int key_down;
  uint key_code;
  
  key_code = *(uint *)(((i8 *)&input_vkey_map_table) + (vkey & 0xff) * 4);
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

int __thiscall ddctrl_get_rect(void *self)

{
  return (int)self + 0x38;
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
      ddwin_deactivate_controls((void *)self->owner_ddwin);
    }
    else {
      ddctrl_deactivate_children((void *)self->parent_control);
    }
    self->is_active = 1;
    call_untyped(((code **)self->vtable)[8], 1);
  }
  return;
}

/* 005f1683 auto */
void __thiscall ddctrl_deactivate(void *self)

{
  if (*(char *)((int)self + 0x34) != '\0') {
    ddctrl_deactivate_children(self);
    *(i8 *)((int)self + 0x34) = 0;
    call_untyped(((code **)(*(int **)self))[8], self,0);
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
    call_untyped((code *)self->on_lbutton_up, self->control_id,x,y);
  }
  return;
}

/* 005f1811 auto */
void __thiscall ddctrl_on_rbuttonup(DdctrlOnRbuttonupView *self,i32 x,i32 y)

{
  if (self->on_rbutton_up != 0) {
    call_untyped((code *)self->on_rbutton_up, self->control_id,x,y);
  }
  return;
}

/* 005f184e auto */
void __thiscall ddctrl_on_mousemove(DdctrlOnMousemoveView *self,i32 x,i32 y)

{
  if (self->on_mouse_move != 0) {
    call_untyped((code *)self->on_mouse_move, self->control_id,x,y);
  }
  return;
}

/* 005f188b auto */
void __thiscall ddctrl_on_dblclick(DdctrlOnDblclickView *self,i32 x,i32 y)

{
  if (self->on_dblclick != 0) {
    call_untyped((code *)self->on_dblclick, self->control_id,x,y);
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
void __thiscall ddctrl_deactivate_children(void *self)

{
  i32 child;
  
  child = ptrlist_first((PtrList *)((int)self + 0x10));
  while (child != 0) {
    ddctrl_deactivate((void *)child);
    child = ptrlist_next((PtrList *)((int)self + 0x10));
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
    child_rect = (int *)ddctrl_get_rect((void *)self->hover_child);
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
