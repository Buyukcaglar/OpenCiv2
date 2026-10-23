/* The game, controls: buttons, lists, combo and check boxes, edit fields, scroll bars: functions translated from the original
 * (tools/gen_c.py, now edited directly), in address order. */
#include "auto_common.h"

/* 0040f380 auto */
void __thiscall ctrl_show_and_redraw(Control *this)

{
  if (this->hwnd != 0) {
    hwnd_show(this->hwnd);
    wnd_invalidate(this->hwnd);
  }
  return;
}

/* 0040f3e0 auto */
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
Control * __thiscall button_ctor(Control *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  ctrl_base_ctor(this);
  this->hotkey_char = '\0';
  this->on_select = 0xffffffff;
  return this;
}
#undef seh_prev
#undef seh_handler
#undef seh_state

/* 0040f480 auto */
Control * __thiscall ctrl_base_ctor(Control *this)

{
  this->ctrl_id = 0;
  this->parent = 0;
  SetRect((LPRECT)&this->rect_left,0,0,0,0);
  this->hwnd = 0;
  this->next_ctrl = 0;
  this->wants_initial_focus = '\0';
  this->hotkey_char = '\0';
  this->hotkey_pos = 0xffffffff;
  return this;
}

/* 0040f510 auto */
i32 __thiscall ctrl_base_dtor(ControlBase *this)

{
  i32 result;
  
  if (this->owner_wnd != 0) {
    wnd_remove_control((WndControlRemoveView *)this->owner_wnd,this->control_id);
  }
  this->next_control = 0;
  result = ctrl_destroy_hwnd((iptr)this);
  return result;
}

/* 0040f570 auto */
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
i32 __thiscall ctrl_dtor(Control *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0;
  if (this->hwnd != 0) {
    ctrl_destroy(this);
  }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 0040f5c3 */ { ctrl_base_dtor(*(ControlBase **)((iptr)&this)); }
  return seh_prev;
}
#undef seh_prev
#undef seh_handler
#undef seh_state

/* 0040f610 auto */
void __thiscall ctrl_destroy(Control *this)

{
  if (this->hwnd != 0) {
    if (this->parent != 0) {
      wnd_remove_control((WndControlRemoveView *)this->parent,this->ctrl_id);
    }
    this->next_ctrl = 0;
    ctrl_destroy_hwnd((iptr)this);
  }
  return;
}

/* 0040f680 auto */
void __thiscall
button_create
          (Control *this,iptr parent,i32 ctrl_id,iptr rect,iptr label)

{
  u32 new_hwnd;
  
  if (this->hwnd != 0) {
    ctrl_destroy(this);
  }
  this->font = (u32)button_default_font;
  ctrl_init(this,parent,6,ctrl_id,rect);
  this->on_click = 0;
  new_hwnd = button_create_hwnd(rect,(iptr)this,label,1,this->font);
  this->hwnd = new_hwnd;
  this->is_enabled = 1;
  return;
}

/* 0040f730 auto */
void __thiscall
ctrl_init(Control *this,iptr parent_wnd,u32 type_code,u32 id,iptr rect)

{
  this->parent = parent_wnd;
  this->ctrl_type = type_code;
  this->ctrl_id = id;
  this->rect_left = *(u32 *)rect;
  this->rect_top = *(u32 *)(rect + 4);
  this->rect_right = *(u32 *)(rect + 8);
  this->rect_bottom = *(u32 *)(rect + 0xc);
  this->next_ctrl = 0;
  this->hwnd = 0;
  this->wants_initial_focus = '\0';
  wnd_append_control((WndControlListView *)parent_wnd,(iptr)this);
  return;
}

/* 0040f7d0 auto */
void __thiscall ctrl_set_default_button(Control *this)

{
  iptr parent;
  
  parent = ctrl_get_parent(this);
  *(Control **)(parent + 0xbc) = this;
  return;
}

/* 0040f810 auto */
uptr __thiscall ctrl_get_parent(Control *this)

{
  return this->parent;
}

/* 0040f840 auto */
void __thiscall ctrl_set_cancel_button(Control *this)

{
  iptr parent;
  
  parent = ctrl_get_parent(this);
  *(Control **)(parent + 0xc0) = this;
  return;
}

/* 0040f880 auto */
void __thiscall button_set_callback(Control *this,iptr callback)

{
  this->on_click = callback;
  return;
}

/* 0040f8b0 auto */
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
Control * __thiscall checkbox_elem_ctor(Control *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  ctrl_base_ctor(this);
  return this;
}
#undef seh_prev
#undef seh_handler
#undef seh_state

/* 0040f930 auto */
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
void __thiscall checkbox_dtor(Checkbox *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0;
  if (this->hwnd != 0) {
    checkbox_destroy_hwnd(this->hwnd);
  }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 0040f98a */ { ctrl_base_dtor(*(ControlBase **)((iptr)&this)); }
  return;
}
#undef seh_prev
#undef seh_handler
#undef seh_state

/* 0040f9d0 auto */
#define rect (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
void __thiscall
checkbox_create
          (Control *this,iptr parent,i32 ctrl_id,i32 x,i32 y
          ,iptr label)

{
  u32 new_hwnd;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  this->font = (u32)checkbox_default_font;
  checkbox_calc_rect(label,x,y,(iptr)rect,this->font);
  if (this->hwnd != 0) {
    ctrl_destroy(this);
  }
  ctrl_init(this,parent,2,ctrl_id,(iptr)rect);
  this->is_enabled = 0;
  this->on_select = 1;
  this->on_click = 0;
  new_hwnd = checkbox_create_hwnd((iptr)rect,(iptr)this,label,1);
  this->hwnd = new_hwnd;
  return;
}
#undef rect

/* 0040faa0 auto */
void __thiscall checkbox_set_callback(CheckboxCallbackSetView *this,iptr callback)

{
  this->on_toggle = callback;
  return;
}

/* 0040fad0 auto */
void __thiscall checkbox_set_checked(Control *this,u32 checked)

{
  this->on_click = checked;
  return;
}

/* 0040fb00 auto */
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
Control * __thiscall scrollbar_ctor(Control *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  ctrl_base_ctor(this);
  this->on_select = 1;
  this->is_enabled = 0;
  this->on_click = 0;
  return this;
}
#undef seh_prev
#undef seh_handler
#undef seh_state

/* 0040fbb0 auto */
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
void __thiscall scrollbar_dtor(Control *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0;
  if (this->hwnd != 0) {
    scrollbar_destroy_hwnd(this->hwnd);
  }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 0040fc0a */ { ctrl_base_dtor(*(ControlBase **)((iptr)&this)); }
  return;
}
#undef seh_prev
#undef seh_handler
#undef seh_state

/* 0040fc50 auto */
void __thiscall
scrollbar_create
          (Control *this,iptr parent,iptr ctrl_id,iptr rect,i32 style)

{
  u32 new_hwnd;
  
  if (this->hwnd != 0) {
    ctrl_destroy(this);
  }
  ctrl_init(this,parent,8,ctrl_id,rect);
  new_hwnd = scrollbar_create_hwnd(rect,(iptr)this,style,1);
  this->hwnd = new_hwnd;
  scrollbar_hwnd_set_range(this->hwnd,1,100);
  this->font = 1;
  return;
}

/* 0040fcf0 auto */
void __thiscall scrollbar_set_pos(ClickControl *this,iptr pos)

{
  this->scroll_pos = pos;
  scrollbar_hwnd_set_pos(this->hwnd,pos);
  return;
}

/* 0040fd40 auto */
void __thiscall
scrollbar_set_range(Control *this,i32 min_value,i32 max_value)

{
  scrollbar_hwnd_set_range(this->hwnd,min_value,max_value);
  return;
}

/* 0040fd80 auto */
void __thiscall scrollbar_set_callback(Control *this,iptr callback)

{
  this->is_enabled = callback;
  return;
}

/* 00418740 auto */
u32 __thiscall ctrl_get_id(ControlIdView *this)

{
  return this->ctrl_id;
}

/* 00418770 auto */
u32 __thiscall control_get_hwnd(ControlHwndView *this)

{
  return this->hwnd;
}

/* 004187a0 auto */
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
InputControl * __thiscall edit_ctor(InputControl *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  ctrl_base_ctor((Control *)this);
  this->on_click = 0;
  this->is_enabled = 0;
  this->items_handle = 0;
  this->on_select = 0;
  *(i8 *)&this->font = 0;
  *(i8 *)((int)&this->font + 1) = 0;
  return this;
}
#undef seh_prev
#undef seh_handler
#undef seh_state

/* 00418870 auto */
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
void __thiscall edit_dtor(Control *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0;
  if (this->hwnd != 0) {
    edit_hwnd_cleanup_stub(this->hwnd);
  }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 004188ca */ { ctrl_base_dtor(*(ControlBase **)((iptr)&this)); }
  return;
}
#undef seh_prev
#undef seh_handler
#undef seh_state

/* 00418910 auto */
void __thiscall
edit_create
          (EditControl *this,iptr parent,i32 ctrl_id,iptr rect,iptr text)

{
  u32 new_hwnd;
  
  if (this->hwnd != 0) {
    ctrl_destroy((Control *)this);
  }
  this->edit_font = (u32)ctrl_default_font;
  ctrl_init((Control *)this,parent,4,ctrl_id,rect);
  new_hwnd = edit_create_window(rect,(iptr)this,1,1,this->edit_font);
  this->hwnd = new_hwnd;
  hwnd_send_settext(this->hwnd,text);
  return;
}

/* 004189c0 auto */
void __thiscall edit_set_max_len(EditMaxLenView *this,i32 max_len)

{
  edit_hwnd_limit_text(this->hwnd,max_len);
  return;
}

/* 00418a00 auto */
void __thiscall edit_set_callback(EditCallbackSetView *this,iptr callback)

{
  this->on_change = callback;
  return;
}

/* 00418a30 auto */
void __thiscall ctrl_set_text(ControlTextView *this,iptr text)

{
  hwnd_send_settext(this->hwnd,text);
  return;
}

/* 00418a70 auto */
void __thiscall ctrl_get_text(ControlTextView *this,iptr buffer)

{
  hwnd_get_text(this->hwnd,buffer);
  return;
}

/* 00418ab0 auto */
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
Control * __thiscall combo_ctor(Control *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  ctrl_base_ctor(this);
  this->on_click = 0;
  this->on_select = 0;
  return this;
}
#undef seh_prev
#undef seh_handler
#undef seh_state

/* 00418b50 auto */
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
void __thiscall combo_dtor(ComboDtorView *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0;
  if (this->hwnd != 0) {
    combo_hwnd_cleanup_stub(this->hwnd);
  }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 00418baa */ { ctrl_base_dtor(*(ControlBase **)((iptr)&this)); }
  return;
}
#undef seh_prev
#undef seh_handler
#undef seh_state

/* 00418bf0 auto */
void __thiscall
combo_create(Control *this,iptr parent,i32 ctrl_id,iptr rect)

{
  u32 new_hwnd;
  
  if (this->hwnd != 0) {
    ctrl_destroy(this);
  }
  ctrl_init(this,parent,10,ctrl_id,rect);
  new_hwnd = combo_create_window(rect,(iptr)this,1);
  this->hwnd = new_hwnd;
  this->is_enabled = 0;
  return;
}

/* 00418c70 auto */
void __thiscall combo_set_font(ComboBoxFontView *this,iptr font)

{
  i32 hfont;
  
  hfont = font_get_hfont((GameFont *)font);
  combo_hwnd_set_font(this->hwnd,hfont);
  return;
}

/* 00418ce0 auto */
void __thiscall combo_add_string(ComboBoxAddView *this,iptr text)

{
  combo_hwnd_add_string(this->hwnd,text);
  this->item_count++;
  return;
}

/* 00418d20 auto */
void __thiscall combo_clear(ComboBoxClearView *this)

{
  combo_hwnd_clear(this->hwnd);
  this->item_count = 0;
  return;
}

/* 00418d60 auto */
i32 __thiscall combo_get_cur_sel(ComboBoxGetSelView *this)

{
  i32 sel;
  
  sel = combo_hwnd_get_cur_sel(this->hwnd);
  return sel;
}

/* 00418d90 auto */
void __thiscall combo_set_cur_sel(ComboBoxSetSelView *this,iptr index)

{
  combo_hwnd_set_cur_sel(this->hwnd,index);
  return;
}

/* 00418dd0 auto */
void __thiscall combo_set_callback(ComboBoxCallbackSetView *this,iptr callback)

{
  this->on_select = callback;
  return;
}

/* 00418e00 auto */
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
Control * __thiscall checkbox_ctor(Control *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  ctrl_base_ctor(this);
  this->on_click = 0;
  this->on_select = 0;
  return this;
}
#undef seh_prev
#undef seh_handler
#undef seh_state

/* 00418ea0 auto */
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
void __thiscall listbox_dtor(ListBoxControl *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0;
  if (this->hwnd != 0) {
    listbox_hwnd_cleanup_stub(this->hwnd);
  }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 00418efa */ { ctrl_base_dtor(*(ControlBase **)((iptr)&this)); }
  return;
}
#undef seh_prev
#undef seh_handler
#undef seh_state

/* 00418f40 auto */
void __thiscall
listbox_create(Control *this,iptr parent,i32 ctrl_id,iptr rect)

{
  u32 new_hwnd;
  
  if (this->hwnd != 0) {
    ctrl_destroy(this);
  }
  this->font = (u32)listbox_default_font;
  ctrl_init(this,parent,7,ctrl_id,rect);
  new_hwnd = listbox_create_hwnd(rect,(iptr)this,1,0,this->font);
  this->hwnd = new_hwnd;
  this->is_enabled = 0;
  return;
}

/* 00418fe0 auto */
void __thiscall listbox_set_font(ListBoxFontView *this,iptr font)

{
  i32 hfont;
  
  hfont = font_get_hfont((GameFont *)font);
  listbox_hwnd_set_font(this->hwnd,hfont);
  return;
}

/* 00419020 auto */
void __thiscall listbox_add_string(ListBoxAddView *this,iptr text)

{
  listbox_hwnd_add_string(this->hwnd,text);
  this->item_count++;
  return;
}

/* 00419060 auto */
void __thiscall listbox_clear(ListBoxClearView *this)

{
  listbox_hwnd_clear(this->hwnd);
  this->item_count = 0;
  return;
}

/* 00421bd0 auto */
void __cdecl input_flush_events(void)

{
  win_drain_input_msgs();
  return;
}

/* 00421ca0 auto */
void __thiscall radiogrp_enable_item(RadioGroupEnableView *this,iptr index)

{
  if ((index < (int)this->item_count) && (-1 < index)) {
    *(i32 *)(this->items + 0x18 + index * 0xa4) = 1;
    radiogrp_hwnd_invalidate(*(i32 *)(this->items + index * 0xa4));
  }
  return;
}

/* 0043c5f0 auto */
void __thiscall control_hide(Control *this)

{
  if (this->hwnd != 0) {
    hwnd_hide(this->hwnd);
  }
  return;
}

/* 00447210 auto */
void __thiscall radiogrp_disable_item(RadioGroupDisableView *this,iptr index)

{
  if ((index < (int)this->item_count) && (-1 < index)) {
    if (this->selected_index == index) {
      this->selected_index = 0xffffffff;
    }
    *(i32 *)(this->items + 0x18 + index * 0xa4) = 0;
    radiogrp_hwnd_invalidate(*(i32 *)(this->items + index * 0xa4));
  }
  return;
}

/* 004472c0 auto */
/* Library Function - Single Match
    public: unsigned int __thiscall CCheckListBox::GetCheckStyle(void)
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall radiogrp_get_selected(RadioGroupGetSelView *this)

{
  return this->selected;
}

/* 004472f0 auto */
void __thiscall radiogrp_set_selected(RadioGroupSetSelView *this,u32 value)

{
  this->selected = value;
  return;
}

/* 00451ac0 auto */
void __thiscall scrollbar_set_track_callback(ScrollbarTrackSetView *this,iptr callback)

{
  this->on_track = callback;
  return;
}

/* 00453c40 auto */
void __thiscall ctrl_disable(Control *this)

{
  this->is_enabled = 0;
  wnd_invalidate(this->hwnd);
  return;
}

/* 00453c80 auto */
void __thiscall ctrl_enable(Control *this)

{
  this->is_enabled = 1;
  wnd_invalidate(this->hwnd);
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
  scrollbar_ctor((Control *)&static_scrollbar_1);
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
  scrollbar_dtor((Control *)&static_scrollbar_1);
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
  scrollbar_ctor((Control *)&static_scrollbar_2);
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
  scrollbar_dtor((Control *)&static_scrollbar_2);
  return;
}

/* 00492ab0 auto */
i32 __thiscall edit_get_sel_end(EditSelEndView *this)

{
  i32 sel_end;
  
  sel_end = edit_ctl_get_sel_end(this->hwnd);
  return sel_end;
}

/* 00492ae0 auto */
void __thiscall edit_replace_sel(Control *this,iptr text)

{
  edit_hwnd_replace_sel(this->hwnd,text);
  return;
}

/* 00492b20 auto */
void __thiscall edit_set_sel(EditSelView *this,i32 sel_start,i32 sel_end)

{
  edit_hwnd_set_sel(this->hwnd,sel_start,sel_end);
  return;
}

/* 00497d40 auto */
void __thiscall
button_create_with_callback
          (Control *this,iptr parent,i32 ctrl_id,iptr rect,u32 callback,iptr label
          )

{
  this->on_select = callback;
  this->font = (u32)button_default_font;
  button_create(this,parent,ctrl_id,rect,label);
  return;
}

/* 004bb3b0 auto */
Control * __thiscall ctrl_scalar_dtor(Control *this,uint flags)

{
  ctrl_dtor(this);
  if ((flags & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 004bb400 auto */
Control * __thiscall edit_scalar_dtor(Control *this,uint flags)

{
  edit_dtor(this);
  if ((flags & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 004bb450 auto */
Checkbox * __thiscall checkbox_scalar_dtor(Checkbox *this,uint flags)

{
  checkbox_dtor(this);
  if ((flags & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 004bb4a0 auto */
RadioGroupDtorView * __thiscall radiogrp_scalar_dtor(RadioGroupDtorView *this,uint flags)

{
  radiogrp_dtor(this);
  if ((flags & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 004bb4f0 auto */
Control * __thiscall scrollbar_scalar_dtor(Control *this,uint flags)

{
  scrollbar_dtor(this);
  if ((flags & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 004bb5b0 auto */
void __thiscall ctrl_set_initial_focus(CtrlSetInitialFocusView *this)

{
  this->wants_initial_focus = 1;
  return;
}

/* 004bb5e0 auto */
void __thiscall ctrl_set_focus(ControlFocusView *this)

{
  if (this->hwnd != 0) {
    ctrl_hwnd_set_focus(this->hwnd);
  }
  return;
}

/* 004bb620 auto */
void __thiscall
edit_create_styled
          (EditControl *this,iptr parent,i32 ctrl_id,iptr rect,iptr text,
          i32 multiline,i32 style)

{
  u32 new_hwnd;
  
  if (this->hwnd != 0) {
    ctrl_destroy((Control *)this);
  }
  this->edit_font = (u32)ctrl_default_font;
  ctrl_init((Control *)this,parent,4,ctrl_id,rect);
  new_hwnd = edit_create_window(rect,(iptr)this,multiline,style,this->edit_font);
  this->hwnd = new_hwnd;
  hwnd_send_settext(this->hwnd,text);
  return;
}

/* 004bb6d0 auto */
void __thiscall edit_set_caret(ControlTextView *this,i32 pos)

{
  edit_hwnd_set_caret(this->hwnd,pos);
  return;
}

/* 004bb710 auto */
i32 __thiscall edit_get_text_end(ControlTextView *this)

{
  i32 text_end;
  
  text_end = edit_hwnd_get_text_end(this->hwnd);
  return text_end;
}

/* 004bb740 auto */
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
void __thiscall radiogrp_dtor(RadioGroupDtorView *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0;
  if (this->items_handle != 0) {
    mem_handle_unlock(this->items_handle);
    radiogrp_destroy_items(this->item_count,this->items_handle);
  }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 004bb7b0 */ { ctrl_base_dtor(*(ControlBase **)((iptr)&this)); }
  return;
}
#undef seh_prev
#undef seh_handler
#undef seh_state

/* 004cffb0 auto */
i32 __thiscall
edit_get_line(EditLineView *this,i32 line,iptr buffer,i32 max_len)

{
  i32 length;
  
  length = edit_hwnd_get_line(this->hwnd,line,buffer,max_len);
  return length;
}

/* 005011b4 auto */
#define shadow_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define draw_ctx (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
#define height2 (*(i32 *)(frame_ + FRAME_OFF(36)))
#define rect_left2 (*(int *)(frame_ + FRAME_OFF(40)))
#define rect_top2 (*(int *)(frame_ + FRAME_OFF(44)))
#define rect_right2 (*(int *)(frame_ + FRAME_OFF(48)))
#define rect_bottom2 (*(int *)(frame_ + FRAME_OFF(52)))
#define inner_left (*(int *)(frame_ + FRAME_OFF(56)))
#define inner_top (*(int *)(frame_ + FRAME_OFF(60)))
#define inner_right (*(int *)(frame_ + FRAME_OFF(64)))
#define inner_bottom (*(int *)(frame_ + FRAME_OFF(68)))
#define width2 (*(i32 *)(frame_ + FRAME_OFF(72)))
#define icon_y (*(int *)(frame_ + FRAME_OFF(76)))
#define icon_x (*(int *)(frame_ + FRAME_OFF(80)))
void __cdecl
spritebtn_create_icon_button(iptr parent,i32 ctrl_id,SpriteButton *button,iptr sprite,iptr rect)

{
  int *surf_rect;
  int size;
  WndPaletteView *pCVar3;
  iptr palette;
  int center;
  i8 frame_[FRAME_OFF(88)] __attribute__((aligned(8)));  /* original stack frame */
  
  width2 = rect_width(rect);
  height2 = rect_height(rect);
  spritebtn_init_from_sprite
            (button,parent,ctrl_id,*(i32 *)rect,*(i32 *)(rect + 4),width2,
             height2,sprite,0x17);
  surf_rect = (int *)surface_get_rect((DibSurface *)&button->on_select);
  rect_left2 = *surf_rect;
  rect_top2 = surf_rect[1];
  rect_right2 = surf_rect[2];
  rect_bottom2 = surf_rect[3];
  size = rect_width((iptr)&rect_left2);
  center = rect_left2 + size / 2;
  size = sprite_width((Sprite *)sprite);
  icon_x = center - size / 2;
  size = rect_height((iptr)&rect_left2);
  center = rect_top2 + size / 2;
  size = sprite_height((Sprite *)sprite);
  icon_y = center - size / 2;
  sprite_draw
            ((Sprite *)sprite,(iptr)draw_ctx,(iptr)&button->on_select,icon_x,icon_y);
  sprite_draw
            ((Sprite *)sprite,(iptr)shadow_ctx,(iptr)(button->button_surface),icon_x + 2,
             icon_y + 2);
  gfx_draw_rect_frame((iptr)&button->on_select,(iptr)&rect_left2,10);
  gfx_draw_rect_frame((iptr)(button->button_surface),(iptr)&rect_left2,10);
  inner_left = rect_left2;
  inner_top = rect_top2;
  inner_right = rect_right2;
  inner_bottom = rect_bottom2;
  rect_deflate((iptr)&inner_left,1,1);
  gfx_draw_bevel_rect((iptr)&button->on_select,(iptr)&inner_left,0x1f,0xf);
  gfx_draw_bevel_rect((iptr)(button->button_surface),(iptr)&inner_left,0xf,10);
  rect_deflate((iptr)&inner_left,1,1);
  gfx_draw_bevel_rect((iptr)&button->on_select,(iptr)&inner_left,0x1f,0xf);
  gfx_draw_bevel_rect((iptr)(button->button_surface),(iptr)&inner_left,0xf,10);
  pCVar3 = (WndPaletteView *)ctrl_get_parent((Control *)button);
  palette = wnd_get_palette(pCVar3);
  surface_set_palette((DibSurface *)(button->button_surface),palette);
  pCVar3 = (WndPaletteView *)ctrl_get_parent((Control *)button);
  palette = wnd_get_palette(pCVar3);
  surface_set_palette((DibSurface *)&button->on_select,palette);
  return;
}
#undef shadow_ctx
#undef draw_ctx
#undef height2
#undef rect_left2
#undef rect_top2
#undef rect_right2
#undef rect_bottom2
#undef inner_left
#undef inner_top
#undef inner_right
#undef inner_bottom
#undef width2
#undef icon_y
#undef icon_x

/* 00511560 auto */
SpriteButtonCore * __thiscall spritebtn_scalar_dtor(SpriteButtonCore *this,uint flags)

{
  spritebtn_dtor(this);
  if ((flags & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 005115b0 auto */
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define seh_state (*(int *)(frame_ + FRAME_OFF(8)))
void __thiscall spritebtn_dtor(SpriteButtonCore *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  (*(i32 *)((char *)&seh_state + 1)) = 0;
  (*(i8 *)((char *)&seh_state + 0)) = 2;
  if (this->hwnd != 0) {
    spritebtn_hwnd_cleanup_stub(this->hwnd);
  }
  (*(i8 *)((char *)&seh_state + 0)) = 1;
  /* inlined unwind funclet 00511624 */ { surface_dtor((DibSurface *)(*(int *)((iptr)&this) + 0x7c)); }
  seh_state = (uint)(*(i32 *)((char *)&seh_state + 1)) << 8;
  /* inlined unwind funclet 00511630 */ { surface_dtor((DibSurface *)(*(int *)((iptr)&this) + 0x34)); }
  seh_state = 0xffffffff;
  /* inlined unwind funclet 0051163c */ { ctrl_base_dtor(*(ControlBase **)((iptr)&this)); }
  return;
}
#undef seh_prev
#undef seh_handler
#undef seh_state

/* 00511720 auto */
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
SpriteButton * __thiscall spritebtn_ctor(SpriteButton *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  ctrl_base_ctor((Control *)this);
  seh_state = 0;
  surface_ctor((DibSurface *)&this->on_select);
  seh_state = CONCAT31((*(i32 *)((char *)&seh_state + 1)),1);
  surface_ctor((DibSurface *)(this->button_surface));
  this->pressed_state = '\0';
  return this;
}
#undef seh_prev
#undef seh_handler
#undef seh_state

/* 005117f0 auto */
void __thiscall spritebtn_set_click_handler(SpritebtnSetClickHandlerView *this,iptr callback)

{
  this->on_click = callback;
  return;
}

/* 00530e80 auto */
/* Library Function - Single Match
    protected: char * __thiscall streambuf::egptr(void)const 
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall ctrl_is_enabled(ControlEnabledView *this)

{
  return this->is_enabled;
}

/* 00530eb0 auto */
void __thiscall edit_set_change_callback(EditChangeSetView *this,iptr callback)

{
  this->on_change = callback;
  return;
}

/* 00530ee0 auto */
#define rect (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
void __thiscall
checkbox_create_fixed
          (Control *this,iptr parent,i32 ctrl_id,i32 x,i32 y
          ,i32 width,iptr label)

{
  u32 hwnd;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  this->font = (u32)checkbox_default_font;
  checkbox_calc_rect_fixed(x,y,width,(iptr)rect,this->font);
  if (this->hwnd != 0) {
    ctrl_destroy(this);
  }
  ctrl_init(this,parent,2,ctrl_id,(iptr)rect);
  this->is_enabled = 0;
  this->on_select = 1;
  this->on_click = 0;
  hwnd = checkbox_create_hwnd((iptr)rect,(iptr)this,label,1);
  this->hwnd = hwnd;
  return;
}
#undef rect

/* 00530fb0 auto */
void __thiscall checkbox_enable(CheckboxEnableView *this)

{
  this->is_enabled = 1;
  return;
}

/* 00530fe0 auto */
/* Library Function - Single Match
    public: int __thiscall ios::width(void)const 
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall checkbox_is_checked(Control *this)

{
  return this->on_click;
}

/* 00531010 auto */
#define seh_prev (*(i32 *)(frame_ + FRAME_OFF(0)))
#define seh_handler (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define seh_state (*(i32 *)(frame_ + FRAME_OFF(8)))
InputControl * __thiscall radiogrp_ctor(InputControl *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  seh_state = 0xffffffff;
  ctrl_base_ctor((Control *)this);
  this->items_handle = 0;
  return this;
}
#undef seh_prev
#undef seh_handler
#undef seh_state

/* 005310a0 auto */
void __thiscall
radiogrp_create
          (RadioGroup *this,iptr parent,i32 ctrl_id,iptr rect,u32 columns,u32 item_count,
          iptr labels)

{
  u32 handle;
  
  if (this->items_handle != 0) {
    ctrl_destroy((Control *)this);
  }
  this->radio_font = (u32)radio_default_font;
  ctrl_init((Control *)this,parent,3,ctrl_id,rect);
  this->is_enabled = 0;
  this->on_click = 0;
  this->on_select = 0;
  this->font = item_count;
  this->scroll_pos = columns;
  this->edit_font = 0;
  handle = radiogrp_create_items((iptr)&this->font,rect,columns,(iptr)this,item_count,labels,1,
                       this->radio_font);
  this->items_handle = handle;
  handle = mem_handle_lock(this->items_handle);
  this->items_ptr = handle;
  return;
}

/* 005311b0 auto */
void __thiscall radiogrp_set_select_callback(Control *this,iptr callback)

{
  this->is_enabled = callback;
  return;
}

/* 005311e0 auto */
void __thiscall radiogrp_set_dblclick_callback(Control *this,iptr callback)

{
  this->on_click = callback;
  return;
}

/* 00551d20 auto */
/* Library Function - Single Match
    protected: char * __thiscall streambuf::egptr(void)const 
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall listbox_get_count(ListboxGetCountView *this)

{
  return this->item_count;
}

/* 00551d50 auto */
i32 __thiscall listbox_get_cur_sel(ListBoxGetSelView *this)

{
  i32 cur_sel;
  
  cur_sel = listbox_hwnd_get_cur_sel(this->hwnd);
  return cur_sel;
}

/* 00551d80 auto */
void __thiscall listbox_set_cur_sel(ListBoxSetSelView *this,i32 index)

{
  listbox_hwnd_set_cur_sel(this->hwnd,index);
  return;
}

/* 00551dc0 auto */
void __thiscall listbox_set_dblclick_callback(ListBoxDblClickSetView *this,iptr callback)

{
  this->on_dblclick = callback;
  return;
}

/* 00551df0 auto */
void __thiscall listbox_set_select_callback(ListBoxSelectSetView *this,iptr callback)

{
  this->on_select = callback;
  return;
}

/* 005a9320 auto */
/* Library Function - Multiple Matches With Different Base Names
    public: void * __thiscall CDaoIndexFieldInfo::`vector deleting destructor'(unsigned int)
    public: void * __thiscall CDaoRelationFieldInfo::`vector deleting destructor'(unsigned int)
    public: void * __thiscall CODBCFieldInfo::`vector deleting destructor'(unsigned int)
    public: void * __thiscall CString::`vector deleting destructor'(unsigned int)
   
   Library: Visual Studio 1998 Debug */

Checkbox * __thiscall checkbox_vector_dtor(Checkbox *this,uint flags)

{
  if ((flags & 2) == 0) {
    checkbox_dtor(this);
    if ((flags & 1) != 0) {
      operator_delete(this);
    }
  }
  else {
    crt_vector_dtor_iterator(this,0x3c,VECTOR_COUNT(this),checkbox_dtor);
    operator_delete(&VECTOR_COUNT(this));
  }
  return this;
}

/* 005a93b0 auto */
/* Library Function - Multiple Matches With Different Base Names
    public: void * __thiscall CDaoIndexFieldInfo::`vector deleting destructor'(unsigned int)
    public: void * __thiscall CDaoRelationFieldInfo::`vector deleting destructor'(unsigned int)
    public: void * __thiscall CODBCFieldInfo::`vector deleting destructor'(unsigned int)
    public: void * __thiscall CString::`vector deleting destructor'(unsigned int)
   
   Library: Visual Studio 1998 Debug */

Control * __thiscall edit_vector_dtor(Control *this,uint flags)

{
  if ((flags & 2) == 0) {
    edit_dtor(this);
    if ((flags & 1) != 0) {
      operator_delete(this);
    }
  }
  else {
    crt_vector_dtor_iterator(this,0x48,VECTOR_COUNT(this),edit_dtor);
    operator_delete(&VECTOR_COUNT(this));
  }
  return this;
}

/* 005a9440 auto */
/* Library Function - Multiple Matches With Different Base Names
    public: void * __thiscall CDaoIndexFieldInfo::`vector deleting destructor'(unsigned int)
    public: void * __thiscall CDaoRelationFieldInfo::`vector deleting destructor'(unsigned int)
    public: void * __thiscall CODBCFieldInfo::`vector deleting destructor'(unsigned int)
    public: void * __thiscall CString::`vector deleting destructor'(unsigned int)
   
   Library: Visual Studio 1998 Debug */

Control * __thiscall ctrl_vector_dtor(Control *this,uint flags)

{
  if ((flags & 2) == 0) {
    ctrl_dtor(this);
    if ((flags & 1) != 0) {
      operator_delete(this);
    }
  }
  else {
    crt_vector_dtor_iterator(this,0x3c,VECTOR_COUNT(this),ctrl_dtor);
    operator_delete(&VECTOR_COUNT(this));
  }
  return this;
}

/* 005a94d0 auto */
ListBoxControl * __thiscall listbox_scalar_dtor(ListBoxControl *this,uint flags)

{
  listbox_dtor(this);
  if ((flags & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 005a9640 auto */
void __thiscall checkbox_disable(CheckboxDisableView *this)

{
  this->is_enabled = 0;
  return;
}

/* 005a9670 auto */
void __thiscall listbox_get_text(ListBoxTextView *this,i32 index,iptr buffer)

{
  listbox_hwnd_get_text(this->hwnd,index,buffer);
  return;
}

/* 005a96b0 auto */
void __thiscall listbox_get_sel_text(ListBoxSelTextView *this,iptr buffer)

{
  listbox_hwnd_get_sel_text(this->hwnd,buffer);
  return;
}

/* 005bd39e auto */
#define msg (*(tagMSG *)(frame_ + FRAME_OFF(4)))
#define pressed (*(char *)(frame_ + FRAME_OFF(32)))
int __cdecl input_poll_modifier(int modifier)

{
  SHORT SVar1;
  BOOL BVar2;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  pressed = '\0';
  if (modifier == 0x200) {
    SVar1 = GetKeyState(0x11);
    pressed = ((int)SVar1 & 0x8000U) != 0;
  }
  else if (modifier == 0x100) {
    SVar1 = GetKeyState(0x10);
    pressed = ((int)SVar1 & 0x8000U) != 0;
  }
  else if (modifier == 0x400) {
    while (BVar2 = PeekMessageA(&msg,(HWND)0x0,0,0,1), BVar2 != 0) {
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
#undef msg
#undef pressed

/* 005bd4cd auto */
uint __cdecl input_lbutton_down(void)

{
  SHORT SVar1;
  
  SVar1 = GetAsyncKeyState(1);
  return (uint)((char)((ushort)SVar1 >> 8) != '\0');
}

/* 005c5e60 auto */
u32 __thiscall control_get_type(ControlTypeView *this)

{
  return this->ctrl_type;
}

/* 005c5e80 auto */
u32 __thiscall control_get_next(ControlNextView *this)

{
  return this->next_control;
}

/* 005c5ea0 auto */
u8 __thiscall ctrl_get_initial_focus(ControlInitialFocusView *this)

{
  return this->initial_focus;
}

/* 005c5ec0 auto */
u32 __thiscall checkbox_is_enabled(CheckboxEnabledView *this)

{
  return this->is_enabled;
}

/* 005c5ee0 auto */
u32 __thiscall radiogrp_get_items(RadioGroupItemsView *this)

{
  return this->items;
}

/* 005c5f00 auto */
u32 __thiscall radiogrp_item_count(RadioGroupCountView *this)

{
  return this->item_count;
}

/* 005c8f50 auto */
int __thiscall ctrl_get_rect(void *this)

{
  return (int)this + 0xc;
}

/* 005c90b0 auto */
void __cdecl ctrl_hwnd_set_focus(HWND hwnd)

{
  SetFocus(hwnd);
  return;
}

/* 005c90ca auto */
#define origin (*(tagPOINT *)(frame_ + FRAME_OFF(4)))
#define dib2 (*(iptr *)(frame_ + FRAME_OFF(12)))
#define parent_hwnd (*(HWND *)(frame_ + FRAME_OFF(16)))
void __cdecl ctrl_paint_parent_bkgnd(iptr paint,HWND hwnd)

{
  LONG LVar1;
  DibSurface *this;
  WndBase *pCVar2;
  iptr window;
  iptr height;
  int value;
  HDC hdcSrc;
  LONG y1;
  DWORD rop;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  parent_hwnd = GetParent(hwnd);
  LVar1 = GetWindowLongA(parent_hwnd,0xc);
  if (LVar1 == 0) {
    pCVar2 = (WndBase *)GetWindowLongA(parent_hwnd,0);
    value = wnd_get_window(pCVar2);
    if (*(int *)(value + 0x14) != 0) {
      FillRect(*(HDC *)paint,(RECT *)(paint + 8),*(HBRUSH *)(value + 0x14));
    }
  }
  else {
    this = (DibSurface *)GetWindowLongA(parent_hwnd,0xc);
    pCVar2 = (WndBase *)GetWindowLongA(parent_hwnd,0);
    window = wnd_get_window(pCVar2);
    dib2 = surface_get_dib(this);
    origin.x = *(int *)(paint + 8);
    origin.y = *(int *)(paint + 0xc);
    MapWindowPoints(hwnd,*(HWND *)(window + 4),&origin,1);
    if ((*(int *)(window + 0x18) != 0) && (gfx_palettized_display == 1)) {
      SelectPalette(*(HDC *)paint,*(HPALETTE *)(window + 0x18),0);
      RealizePalette(*(HDC *)paint);
    }
    rop = 0xcc0020;
    hdcSrc = *(HDC *)(dib2 + 4);
    LVar1 = origin.x;
    y1 = origin.y;
    height = rect_height(paint + 8);
    value = rect_width(paint + 8);
    BitBlt(*(HDC *)paint,*(int *)(paint + 8),*(int *)(paint + 0xc),value,height,hdcSrc,LVar1,y1
           ,rop);
  }
  return;
}
#undef origin
#undef dib2
#undef parent_hwnd

/* 005c9222 auto */
#define pos (*(uptr *)(frame_ + FRAME_OFF(0)))
#define cursor (*(char * *)(frame_ + FRAME_OFF(4)))
#define hotkey (*(char (*)[4])(frame_ + FRAME_OFF(8)))
void __cdecl ctrl_parse_hotkey(iptr ctrl,iptr text)

{
  size_t len;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  cursor = (char *)text;
  *(i32 *)(ctrl + 0x28) = 0;
  while( true ) {
    if (*cursor == '\0') goto LAB_005c92ae;
    if (*cursor == '~') break;
    *(int *)(ctrl + 0x28) = *(int *)(ctrl + 0x28) + 1;
    cursor++;
  }
  for (pos = *(uptr *)(ctrl + 0x28); len = _strlen((char *)text), pos < len;
      pos = pos + 1) {
    *(i8 *)(pos + text) = *(i8 *)(pos + 1 + text);
  }
LAB_005c92ae:
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
#undef pos
#undef cursor
#undef hotkey

/* 005c9307 auto */
#define ps (*(tagPAINTSTRUCT *)(frame_ + FRAME_OFF(4)))
LRESULT __stdcall ctrl_default_wndproc(HWND hwnd,uint msg,WPARAM wparam,LPARAM lparam)

{
  HWND hWnd;
  iptr block;
  LRESULT LVar1;
  i8 frame_[FRAME_OFF(72)] __attribute__((aligned(8)));  /* original stack frame */
  
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
      LVar1 = DefWindowProcA(hwnd,2,wparam,lparam);
      return LVar1;
    }
  }
  else if ((0xff < msg) && (msg < 0x103)) {
    hWnd = GetParent(hwnd);
    SendMessageA(hWnd,msg,wparam,lparam);
    return 0;
  }
  LVar1 = DefWindowProcA(hwnd,msg,wparam,lparam);
  return LVar1;
}
#undef ps

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
      hWnd = (HWND)control_get_hwnd((ControlHwndView *)ctrl);
      result = DestroyWindow(hWnd);
    }
  }
  return result;
}

/* 005c9499 auto */
#define block (*(i32 * *)(frame_ + FRAME_OFF(4)))
i32 * __cdecl ctrl_init_block(HWND hwnd,iptr owner)

{
  i32 handle;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  block = (i32 *)0x0;
  if (hwnd == (HWND)0x0) {
    dbg_log(ADDR(0x637cf4, ((u8 *)&g.d_00637cf4)));
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
#undef block

/* 005c9595 auto */
void __cdecl ctrl_hwnd_free_block(HWND hwnd)

{
  i32 handle;
  i32 *block;
  
  if (hwnd == (HWND)0x0) {
    dbg_log(ADDR(0x637d30, ((u8 *)&g.d_00637d30)));
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
      SetWindowLongA(hwnd,-4,ADDR(0x5c9307, ctrl_default_wndproc));
      SetWindowLongA(hwnd,0,0);
    }
  }
  return;
}

/* 005c9710 auto */
/* Library Function - Single Match
    public: void __thiscall ios::delbuf(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall control_set_hwnd(ControlHwndSetView *this,u32 hwnd)

{
  this->hwnd = hwnd;
  return;
}

/* 005c9740 auto */
#define app_hinstance (*(HINSTANCE *)((u8 *)&g.d_006e4ff0))
#define style2 (*(DWORD *)(frame_ + FRAME_OFF(0)))
#define label_text (*(char (*)[256])(frame_ + FRAME_OFF(40)))
#define line_y (*(int *)(frame_ + FRAME_OFF(296)))
#define green (*(i8 (*)[4])(frame_ + FRAME_OFF(300)))
#define button (*(Control * *)(frame_ + FRAME_OFF(304)))
#define text_width (*(int *)(frame_ + FRAME_OFF(308)))
#define bmp_disabled (*(HBITMAP *)(frame_ + FRAME_OFF(312)))
#define mem_dc (*(HDC *)(frame_ + FRAME_OFF(316)))
#define red (*(i8 (*)[4])(frame_ + FRAME_OFF(320)))
#define blue (*(i8 (*)[4])(frame_ + FRAME_OFF(324)))
#define underline_end (*(int *)(frame_ + FRAME_OFF(328)))
#define hwnd2 (*(HWND *)(frame_ + FRAME_OFF(332)))
#define bounds (*(tagRECT *)(frame_ + FRAME_OFF(336)))
#define old_obj (*(HGDIOBJ *)(frame_ + FRAME_OFF(352)))
#define prefix (*(char (*)[256])(frame_ + FRAME_OFF(356)))
#define saved_left (*(int *)(frame_ + FRAME_OFF(612)))
#define saved_top (*(int *)(frame_ + FRAME_OFF(616)))
#define saved_right (*(int *)(frame_ + FRAME_OFF(620)))
#define saved_bottom (*(int *)(frame_ + FRAME_OFF(624)))
#define underline_start (*(int *)(frame_ + FRAME_OFF(628)))
#define text_rect (*(tagRECT *)(frame_ + FRAME_OFF(632)))
#define bg_pen (*(HPEN *)(frame_ + FRAME_OFF(648)))
#define orig_left (*(int *)(frame_ + FRAME_OFF(652)))
#define orig_top (*(int *)(frame_ + FRAME_OFF(656)))
#define orig_right (*(int *)(frame_ + FRAME_OFF(660)))
#define orig_bottom (*(int *)(frame_ + FRAME_OFF(664)))
HWND __cdecl
button_create_hwnd(int *rect,iptr ctrl,i32 label,int visible,GameFont *font)

{
  WndBase *this;
  iptr window;
  iptr height;
  int value;
  HDC hdc;
  int value2;
  HBITMAP h;
  HBITMAP h_00;
  WndPaletteView *pCVar5;
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
  LONG LVar12;
  HINSTANCE hInstance;
  i8 *green_out;
  tagRECT *draw_rect;
  LPVOID lpParam;
  BOOL bForceBkgd;
  i8 *blue_out;
  UINT UVar16;
  LONG LVar17;
  i8 frame_[FRAME_OFF(672)] __attribute__((aligned(8)));  /* original stack frame */
  
  crt_strcpy(label_text,label);
  button = (Control *)ctrl;
  style2 = 0x40810000;
  if (visible != 0) {
    style2 = 0x50810000;
  }
  lpParam = (LPVOID)0x0;
  hMenu = (HMENU)0x0;
  hInstance = app_hinstance;
  this = (WndBase *)ctrl_get_parent((Control *)ctrl);
  window = wnd_get_window(this);
  hWndParent = *(HWND *)(window + 4);
  height = rect_height((iptr)rect);
  value = rect_width((iptr)rect);
  hwnd2 = CreateWindowExA(4,s_MSControlClass_00637d70,&button_wnd_title,style2,*rect,
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
    dbg_log(ADDR(0x637d80, ((u8 *)&g.d_00637d80)));
    DestroyWindow(hwnd2);
    hwnd2 = (HWND)0x0;
  }
  else {
    value = rect_height((iptr)&bounds);
    value2 = rect_width((iptr)&bounds);
    h_00 = CreateCompatibleBitmap(hdc,value2,value);
    if (h_00 == (HBITMAP)0x0) {
      dbg_log(ADDR(0x637da8, ((u8 *)&g.d_00637da8)));
      DestroyWindow(hwnd2);
      hwnd2 = (HWND)0x0;
    }
    else {
      value = rect_height((iptr)&bounds);
      value2 = rect_width((iptr)&bounds);
      bmp_disabled = CreateCompatibleBitmap(hdc,value2,value);
      if (bmp_disabled == (HBITMAP)0x0) {
        dbg_log(ADDR(0x637dd0, ((u8 *)&g.d_00637dd0)));
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
            pCVar5 = (WndPaletteView *)ctrl_get_parent(button);
            this_00 = (PaletteHandleView *)wnd_get_palette(pCVar5);
            hPal = (HPALETTE)palette_get_hpalette(this_00);
            SelectPalette(mem_dc,hPal,bForceBkgd);
            RealizePalette(mem_dc);
          }
          blue_out = blue;
          green_out = green;
          red_out = red;
          color_index = button->on_select;
          pCVar5 = (WndPaletteView *)ctrl_get_parent(button);
          this_01 = (GamePalette *)wnd_get_palette(pCVar5);
          logpal = palette_get_logpalette(this_01);
          palette_get_entry_rgb(logpal,color_index,(iptr)red_out,(iptr)green_out,(iptr)blue_out);
          bg_pen = CreatePen(0,1,(uint)CONCAT12(blue[0],CONCAT11(green[0],red[0])))
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
          FillRect(mem_dc,&bounds,(HBRUSH)bg_pen);
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
        UVar16 = 0x424;
        draw_rect = &text_rect;
        len = _strlen(label_text);
        DrawTextA(mem_dc,label_text,len,draw_rect,UVar16);
        text_width = rect_width((iptr)&text_rect);
        LVar17 = bounds.bottom;
        value = rect_width((iptr)&bounds);
        value2 = ((bounds.left + value / 2) - text_width / 2) + text_width;
        LVar12 = bounds.top;
        value = rect_width((iptr)&bounds);
        SetRect(&text_rect,(bounds.left + value / 2) - text_width / 2,LVar12,value2,LVar17);
        UVar16 = 0x24;
        draw_rect = &text_rect;
        len = _strlen(label_text);
        DrawTextA(mem_dc,label_text,len,draw_rect,UVar16);
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
            UVar16 = 0x424;
            draw_rect = &text_rect;
            len = _strlen(prefix);
            DrawTextA(mem_dc,prefix,len,draw_rect,UVar16);
            underline_start = text_rect.right - 1;
          }
          crt_strcpy(prefix,label_text);
          prefix[button->hotkey_pos + 1] = '\0';
          text_rect.left = saved_left;
          text_rect.top = saved_top;
          text_rect.right = saved_right;
          text_rect.bottom = saved_bottom;
          UVar16 = 0x424;
          draw_rect = &text_rect;
          len = _strlen(prefix);
          DrawTextA(mem_dc,prefix,len,draw_rect,UVar16);
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
          FillRect(mem_dc,&bounds,(HBRUSH)bg_pen);
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
        UVar16 = 0x424;
        draw_rect = &text_rect;
        text_rect.left = bounds.left;
        text_rect.top = bounds.top;
        len = _strlen(label_text);
        DrawTextA(mem_dc,label_text,len,draw_rect,UVar16);
        text_width = rect_width((iptr)&text_rect);
        LVar17 = bounds.bottom;
        value = rect_width((iptr)&bounds);
        value = (((value >> 1) + bounds.left) - (text_width >> 1)) + text_width;
        LVar12 = bounds.top;
        value2 = rect_width((iptr)&bounds);
        SetRect(&text_rect,((value2 >> 1) + bounds.left) - (text_width >> 1),LVar12,value,LVar17);
        UVar16 = 0x24;
        draw_rect = &text_rect;
        len = _strlen(label_text);
        DrawTextA(mem_dc,label_text,len,draw_rect,UVar16);
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
            UVar16 = 0x424;
            draw_rect = &text_rect;
            len = _strlen(prefix);
            DrawTextA(mem_dc,prefix,len,draw_rect,UVar16);
            underline_start = text_rect.right - 1;
          }
          crt_strcpy(prefix,label_text);
          prefix[button->hotkey_pos + 1] = '\0';
          text_rect.left = saved_left;
          text_rect.top = saved_top;
          text_rect.right = saved_right;
          text_rect.bottom = saved_bottom;
          UVar16 = 0x424;
          draw_rect = &text_rect;
          len = _strlen(prefix);
          DrawTextA(mem_dc,prefix,len,draw_rect,UVar16);
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
          FillRect(mem_dc,&bounds,(HBRUSH)bg_pen);
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
        UVar16 = 0x424;
        draw_rect = &text_rect;
        len = _strlen(label_text);
        DrawTextA(mem_dc,label_text,len,draw_rect,UVar16);
        text_width = rect_width((iptr)&text_rect);
        LVar17 = bounds.bottom;
        value = rect_width((iptr)&bounds);
        value = (((value >> 1) + bounds.left) - (text_width >> 1)) + text_width;
        LVar12 = bounds.top;
        value2 = rect_width((iptr)&bounds);
        SetRect(&text_rect,((value2 >> 1) + bounds.left) - (text_width >> 1),LVar12,value,LVar17);
        SetTextColor(mem_dc,0xffffff);
        UVar16 = 0x24;
        draw_rect = &text_rect;
        len = _strlen(label_text);
        DrawTextA(mem_dc,label_text,len,draw_rect,UVar16);
        OffsetRect(&text_rect,-1,-1);
        SetTextColor(mem_dc,0x808080);
        UVar16 = 0x24;
        draw_rect = &text_rect;
        len = _strlen(label_text);
        DrawTextA(mem_dc,label_text,len,draw_rect,UVar16);
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
            UVar16 = 0x424;
            draw_rect = &text_rect;
            len = _strlen(prefix);
            DrawTextA(mem_dc,prefix,len,draw_rect,UVar16);
            underline_start = text_rect.right - 1;
          }
          crt_strcpy(prefix,label_text);
          prefix[button->hotkey_pos + 1] = '\0';
          text_rect.left = saved_left;
          text_rect.top = saved_top;
          text_rect.right = saved_right;
          text_rect.bottom = saved_bottom;
          UVar16 = 0x424;
          draw_rect = &text_rect;
          len = _strlen(prefix);
          DrawTextA(mem_dc,prefix,len,draw_rect,UVar16);
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
        value = ctrl_init_block(hwnd2,ctrl);
        *(HBITMAP *)(value + 0xc) = h;
        *(HBITMAP *)(value + 0x10) = h_00;
        *(HBITMAP *)(value + 0x14) = bmp_disabled;
        *(i32 *)(value + 0x2c) = 6;
        SetWindowLongA(hwnd2,-4,ADDR(0x5cacd4, button_wndproc));
      }
    }
  }
  return hwnd2;
}
#undef app_hinstance
#undef style2
#undef label_text
#undef line_y
#undef green
#undef button
#undef text_width
#undef bmp_disabled
#undef mem_dc
#undef red
#undef blue
#undef underline_end
#undef hwnd2
#undef bounds
#undef old_obj
#undef prefix
#undef saved_left
#undef saved_top
#undef saved_right
#undef saved_bottom
#undef underline_start
#undef text_rect
#undef bg_pen
#undef orig_left
#undef orig_top
#undef orig_right
#undef orig_bottom

/* 005cac22 auto */
#define wnd_active_child (*(i32 *)((u8 *)&g.d_00637ea4))
void __cdecl button_press_animated(HWND hwnd)

{
  Control *this;
  iptr block;
  int enabled;
  i32 ctrl_id;
  
  block = wnd_from_hwnd(hwnd);
  if (block != 0) {
    this = *(Control **)(block + 4);
    enabled = ctrl_is_enabled((ControlEnabledView *)this);
    if (enabled != 0) {
      SetFocus(hwnd);
      *(i32 *)(block + 0x18) = 1;
      wnd_redraw_client(hwnd);
      *(i32 *)(block + 0x18) = 0;
      ui_pump_messages();
      ui_wait_ticks(8);
      wnd_redraw_client(hwnd);
      wnd_active_child = ctrl_get_parent(this);
      ctrl_id = ctrl_get_id((ControlIdView *)this);
      button_fire_callback((ButtonClickView *)this,ctrl_id);
    }
  }
  return;
}
#undef wnd_active_child

/* 005cacd4: written by hand in src/game/fixups.c */

/* 005cb601 auto */
#define app_hinstance (*(HINSTANCE *)((u8 *)&g.d_006e4ff0))
#define style2 (*(DWORD *)(frame_ + FRAME_OFF(4)))
#define rect (*(tagRECT *)(frame_ + FRAME_OFF(12)))
#define owner2 (*(iptr *)(frame_ + FRAME_OFF(28)))
#define hwnd2 (*(HWND *)(frame_ + FRAME_OFF(32)))
HWND __cdecl spritebtn_create_hwnd(int x,int y,int width,int height,iptr ctrl,int visible)

{
  WndBase *this;
  iptr window;
  iptr rect_h;
  int value;
  HWND hWndParent;
  HMENU hMenu;
  HINSTANCE hInstance;
  LPVOID lpParam;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  style2 = 0x40810000;
  if (visible != 0) {
    style2 = 0x50810000;
  }
  owner2 = ctrl;
  SetRect(&rect,x,y,x + width,y + height);
  lpParam = (LPVOID)0x0;
  hMenu = (HMENU)0x0;
  hInstance = app_hinstance;
  this = (WndBase *)ctrl_get_parent((Control *)ctrl);
  window = wnd_get_window(this);
  hWndParent = *(HWND *)(window + 4);
  rect_h = rect_height((iptr)&rect);
  value = rect_width((iptr)&rect);
  hwnd2 = CreateWindowExA(4,s_MSControlClass_00637e48,&spritebtn_wnd_title,style2,x,y,value
                            ,rect_h,hWndParent,hMenu,hInstance,lpParam);
  value = ctrl_init_block(hwnd2,ctrl);
  *(i32 *)(value + 0x2c) = 5;
  SetWindowLongA(hwnd2,-4,ADDR(0x5cb6eb, spritebtn_wndproc));
  return hwnd2;
}
#undef app_hinstance
#undef style2
#undef rect
#undef owner2
#undef hwnd2

/* 005cb6db auto */
void __cdecl spritebtn_hwnd_cleanup_stub(i32 hwnd)

{
  return;
}

/* 005cb6eb: written by hand in src/game/fixups.c */

/* 005cbdf0 auto */
void __thiscall button_fire_callback(ButtonClickView *this,i32 ctrl_id)

{
  if (this->on_click != 0) {
    (*(code *)this->on_click)(ctrl_id);
  }
  return;
}

/* 005cbe30 auto */
void __thiscall spritebtn_fire_click(SpriteButtonClickView *this,i32 ctrl_id)

{
  if (this->on_click != 0) {
    (*(code *)this->on_click)(ctrl_id);
  }
  return;
}

/* 005cbe70 auto */
void __thiscall spritebtn_fire_rclick(SpriteButtonRClickView *this,i32 ctrl_id)

{
  if (this->on_rclick != 0) {
    (*(code *)this->on_rclick)(ctrl_id);
  }
  return;
}

/* 005cbf40 auto */
#define height2 (*(int *)(frame_ + FRAME_OFF(4)))
#define text_size (*(tagSIZE *)(frame_ + FRAME_OFF(20)))
#define metrics (*(tagTEXTMETRICA *)(frame_ + FRAME_OFF(28)))
#define width2 (*(int *)(frame_ + FRAME_OFF(84)))
#define font_data (*(i32 * *)(frame_ + FRAME_OFF(88)))
void __cdecl checkbox_calc_rect(char *label,int x,int y,iptr out_rect,GameFont *font)

{
  HDC hdc;
  HDC hdc_00;
  i32 font_handle;
  HGDIOBJ h;
  size_t c;
  tagSIZE *lpsz;
  i8 frame_[FRAME_OFF(96)] __attribute__((aligned(8)));  /* original stack frame */
  
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
#undef height2
#undef text_size
#undef metrics
#undef width2
#undef font_data

/* 005cc035 auto */
#define height2 (*(int *)(frame_ + FRAME_OFF(4)))
#define metrics (*(tagTEXTMETRICA *)(frame_ + FRAME_OFF(16)))
#define font_data (*(i32 * *)(frame_ + FRAME_OFF(72)))
void __cdecl checkbox_calc_rect_fixed(int x,int y,int width,iptr out_rect,GameFont *font)

{
  HDC hdc;
  HDC hdc_00;
  i32 font_handle;
  i8 frame_[FRAME_OFF(80)] __attribute__((aligned(8)));  /* original stack frame */
  
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
#undef height2
#undef metrics
#undef font_data

/* 005cc0f0 auto */
#define app_hinstance (*(HINSTANCE *)((u8 *)&g.d_006e4ff0))
#define style2 (*(DWORD *)(frame_ + FRAME_OFF(4)))
HWND __cdecl checkbox_create_hwnd(iptr rect,iptr ctrl,char *label,int visible)

{
  size_t len;
  void *label_copy;
  WndBase *this;
  iptr window;
  iptr height;
  int value;
  HWND pHVar6;
  HBITMAP pHVar7;
  HBITMAP pHVar8;
  HBITMAP pHVar9;
  HMENU hMenu;
  HINSTANCE hInstance;
  LPVOID lpParam;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  len = _strlen(label);
  label_copy = operator_new(len + 1);
  crt_strcpy(label_copy,label);
  style2 = 0x40010000;
  if (visible != 0) {
    style2 = 0x50010000;
  }
  lpParam = (LPVOID)0x0;
  hMenu = (HMENU)0x0;
  hInstance = app_hinstance;
  this = (WndBase *)ctrl_get_parent((Control *)ctrl);
  window = wnd_get_window(this);
  pHVar6 = *(HWND *)(window + 4);
  height = rect_height(rect);
  value = rect_width(rect);
  pHVar6 = CreateWindowExA(4,s_MSControlClass_00637f10,&checkbox_wnd_title,style2,*(int *)rect,
                           *(int *)(rect + 4),value,height,pHVar6,hMenu,hInstance,lpParam);
  ctrl_parse_hotkey(ctrl,(iptr)label_copy);
  pHVar7 = LoadBitmapA(app_hinstance,(LPCSTR)0x132);
  pHVar8 = LoadBitmapA(app_hinstance,(LPCSTR)0x131);
  pHVar9 = LoadBitmapA(app_hinstance,(LPCSTR)0x130);
  value = ctrl_init_block(pHVar6,ctrl);
  *(HBITMAP *)(value + 0xc) = pHVar7;
  *(HBITMAP *)(value + 0x10) = pHVar8;
  *(HBITMAP *)(value + 0x14) = pHVar9;
  *(i32 *)(value + 0x2c) = 2;
  *(void **)(value + 0x24) = label_copy;
  SetWindowLongA(pHVar6,-4,ADDR(0x5cc320, checkbox_wndproc));
  return pHVar6;
}
#undef app_hinstance
#undef style2

/* 005cc248 auto */
void __cdecl checkbox_destroy_hwnd(int hwnd)

{
  if (hwnd == 0) {
    dbg_log(ADDR(0x637f20, ((u8 *)&g.d_00637f20)));
  }
  return;
}

/* 005cc274 auto */
#define wnd_active_child (*(i32 *)((u8 *)&g.d_00637ea4))
void __cdecl checkbox_toggle_by_hotkey(HWND hwnd)

{
  Control *this;
  iptr block;
  int checked;
  i32 is_checked;
  i32 ctrl_id;
  
  block = wnd_from_hwnd(hwnd);
  if (block != 0) {
    this = *(Control **)(block + 4);
    SetFocus(hwnd);
    checked = checkbox_is_checked(this);
    if (checked == 0) {
      checkbox_set_checked(this,1);
    }
    else {
      checkbox_set_checked(this,0);
    }
    SetCapture(hwnd);
    InvalidateRect(hwnd,(RECT *)0x0,0);
    wnd_active_child = ctrl_get_parent(this);
    is_checked = checkbox_is_checked(this);
    ctrl_id = ctrl_get_id((ControlIdView *)this);
    checkbox_fire_callback((CheckboxClickView *)this,ctrl_id,is_checked);
  }
  return;
}
#undef wnd_active_child

/* 005cc320 auto */
#define ctrl_disabled_color_index (*(byte *)((u8 *)&g.d_00637ea0))
#define ctrl_disabled_rgb_set (*(char *)((u8 *)&g.d_00637f07))
#define ctrl_shadow_color_index (*(byte *)((u8 *)&g.d_00637e94))
#define ctrl_shadow_dx (*(byte *)((u8 *)&g.d_00637e98))
#define ctrl_shadow_dy (*(byte *)((u8 *)&g.d_00637e9c))
#define ctrl_text_color_index (*(byte *)((u8 *)&g.d_00637e90))
#define ctrl_text_rgb_set (*(char *)((u8 *)&g.d_00637f03))
#define rect (*(tagRECT *)(frame_ + FRAME_OFF(0)))
#define bitmap (*(HBITMAP *)(frame_ + FRAME_OFF(16)))
#define block (*(iptr *)(frame_ + FRAME_OFF(20)))
#define checkbox (*(Control * *)(frame_ + FRAME_OFF(24)))
#define ps (*(tagPAINTSTRUCT *)(frame_ + FRAME_OFF(28)))
#define old_font (*(HGDIOBJ *)(frame_ + FRAME_OFF(92)))
#define bmp_size (*(tagSIZE *)(frame_ + FRAME_OFF(96)))
#define green (*(i8 (*)[4])(frame_ + FRAME_OFF(104)))
#define hdc (*(HDC *)(frame_ + FRAME_OFF(108)))
#define label (*(char * *)(frame_ + FRAME_OFF(112)))
#define underline_end (*(int *)(frame_ + FRAME_OFF(116)))
#define underline_start (*(int *)(frame_ + FRAME_OFF(120)))
#define box_left (*(int *)(frame_ + FRAME_OFF(124)))
#define box_top (*(int *)(frame_ + FRAME_OFF(128)))
#define box_right (*(int *)(frame_ + FRAME_OFF(132)))
#define box_bottom (*(int *)(frame_ + FRAME_OFF(136)))
#define red (*(i8 (*)[4])(frame_ + FRAME_OFF(140)))
#define blue (*(i8 (*)[4])(frame_ + FRAME_OFF(144)))
#define brush (*(HBRUSH *)(frame_ + FRAME_OFF(148)))
#define font_data (*(i32 * *)(frame_ + FRAME_OFF(152)))
#define prefix (*(char (*)[256])(frame_ + FRAME_OFF(156)))
#define text_rect (*(tagRECT *)(frame_ + FRAME_OFF(412)))
i32 __stdcall checkbox_wndproc(HWND hwnd,uint msg,WPARAM wparam,LPARAM lparam)

{
  char nav_enabled;
  i32 ctrl_id;
  iptr enabled;
  iptr checked;
  int *ctrl_rect;
  int value;
  uint color_index;
  WndPaletteView *pCVar7;
  GamePalette *pCVar8;
  size_t len;
  WndBase *pCVar10;
  iptr logpal;
  HWND pHVar12;
  WndKeyNavView *pCVar13;
  i32 result;
  i8 *red_out;
  i8 *green_out;
  tagRECT *draw_rect;
  i8 *blue_out;
  UINT UVar19;
  i8 frame_[FRAME_OFF(432)] __attribute__((aligned(8)));  /* original stack frame */
  
  block = wnd_from_hwnd(hwnd);
  checkbox = *(Control **)(block + 4);
  if (msg < 0x10) {
    if (msg == 0xf) {
      enabled = checkbox_is_enabled((CheckboxEnabledView *)checkbox);
      if (enabled == 0) {
        pHVar12 = GetFocus();
        if (pHVar12 == hwnd) {
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
      if (checkbox_mouse_pressed != 0) {
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
        pCVar7 = (WndPaletteView *)ctrl_get_parent(checkbox);
        pCVar8 = (GamePalette *)wnd_get_palette(pCVar7);
        palette_get_entry(pCVar8,color_index,(iptr)red_out,(iptr)green_out,(iptr)blue_out);
        SetTextColor(hdc,(uint)CONCAT12(blue[0],CONCAT11(green[0],red[0])));
        UVar19 = 0x24;
        draw_rect = &rect;
        len = _strlen(label);
        DrawTextA(hdc,label,len,draw_rect,UVar19);
        OffsetRect(&rect,-(uint)ctrl_shadow_dx,-(uint)ctrl_shadow_dy);
      }
      value = checkbox_is_enabled((CheckboxEnabledView *)checkbox);
      if (value == 1) {
        pCVar10 = (WndBase *)ctrl_get_parent(checkbox);
        value = wnd_get_window(pCVar10);
        if (*(int *)(value + 0x40) == 8) {
          if (ctrl_text_color_index == 0) {
            SetTextColor(hdc,0);
          }
          else {
            blue_out = blue;
            green_out = green;
            red_out = red;
            color_index = (uint)ctrl_text_color_index;
            pCVar7 = (WndPaletteView *)ctrl_get_parent(checkbox);
            pCVar8 = (GamePalette *)wnd_get_palette(pCVar7);
            logpal = palette_get_logpalette(pCVar8);
            palette_get_entry_rgb(logpal,color_index,(iptr)red_out,(iptr)green_out,(iptr)blue_out);
            SetTextColor(hdc,(uint)CONCAT12(blue[0],CONCAT11(green[0],red[0])))
            ;
          }
        }
        else if (ctrl_text_rgb_set == '\0') {
          SetTextColor(hdc,0);
        }
        else {
          SetTextColor(hdc,(uint)CONCAT12(ctrl_text_rgb_b,CONCAT11(ctrl_text_rgb_g,ctrl_text_rgb_r)));
        }
      }
      else {
        value = checkbox_is_enabled((CheckboxEnabledView *)checkbox);
        if (value == 0) {
          pCVar10 = (WndBase *)ctrl_get_parent(checkbox);
          value = wnd_get_window(pCVar10);
          if (*(int *)(value + 0x40) == 8) {
            if (ctrl_disabled_color_index == 0) {
              SetTextColor(hdc,0x404040);
            }
            else {
              blue_out = blue;
              green_out = green;
              red_out = red;
              color_index = (uint)ctrl_disabled_color_index;
              pCVar7 = (WndPaletteView *)ctrl_get_parent(checkbox);
              pCVar8 = (GamePalette *)wnd_get_palette(pCVar7);
              logpal = palette_get_logpalette(pCVar8);
              palette_get_entry_rgb(logpal,color_index,(iptr)red_out,(iptr)green_out,(iptr)blue_out);
              SetTextColor(hdc,
                           (uint)CONCAT12(blue[0],CONCAT11(green[0],red[0])));
            }
          }
          else if (ctrl_disabled_rgb_set == '\0') {
            SetTextColor(hdc,0x404040);
          }
          else {
            SetTextColor(hdc,(uint)CONCAT12(ctrl_disabled_rgb_b,CONCAT11(ctrl_disabled_rgb_g,ctrl_disabled_rgb_r)))
            ;
          }
        }
      }
      UVar19 = 0x24;
      draw_rect = &rect;
      len = _strlen(label);
      DrawTextA(hdc,label,len,draw_rect,UVar19);
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
          UVar19 = 0x424;
          draw_rect = &text_rect;
          len = _strlen(prefix);
          DrawTextA(hdc,prefix,len,draw_rect,UVar19);
          underline_start = text_rect.right - 1;
        }
        crt_strcpy(prefix,label);
        prefix[checkbox->hotkey_pos + 1] = '\0';
        text_rect.left = rect.left;
        text_rect.top = rect.top;
        text_rect.right = rect.right;
        text_rect.bottom = rect.bottom;
        UVar19 = 0x424;
        draw_rect = &text_rect;
        len = _strlen(prefix);
        DrawTextA(hdc,prefix,len,draw_rect,UVar19);
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
      pHVar12 = GetFocus();
      if (pHVar12 != hwnd) {
        return 0;
      }
    }
    else if (msg != 7) {
      if (msg == 8) {
        wnd_redraw_client(hwnd);
        return 0;
      }
LAB_005ccd4b:
      result = ctrl_default_wndproc(hwnd,msg,wparam,lparam);
      return result;
    }
    pCVar13 = (WndKeyNavView *)ctrl_get_parent(checkbox);
    nav_enabled = wnd_keyboard_nav_enabled(pCVar13);
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
      pHVar12 = GetParent(hwnd);
      SendMessageA(pHVar12,msg,wparam,lparam);
    }
    else {
      if (wparam == 0x20) {
        pCVar13 = (WndKeyNavView *)ctrl_get_parent(checkbox);
        nav_enabled = wnd_keyboard_nav_enabled(pCVar13);
        if (nav_enabled != '\0') {
          SendMessageA(hwnd,0x201,0,0);
          SendMessageA(hwnd,0x202,0,0);
          return 0;
        }
      }
      pHVar12 = GetParent(hwnd);
      SendMessageA(pHVar12,msg,wparam,lparam);
    }
  }
  else if (msg == 0x201) {
    value = checkbox_is_enabled((CheckboxEnabledView *)checkbox);
    if ((value != 0) && (checkbox_mouse_pressed == 0)) {
      SetFocus(hwnd);
      value = checkbox_is_checked(checkbox);
      if (value == 0) {
        checkbox_set_checked(checkbox,1);
      }
      else {
        checkbox_set_checked(checkbox,0);
      }
      checkbox_mouse_pressed = 1;
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
    if (msg != 0x202) goto LAB_005ccd4b;
    value = checkbox_is_enabled((CheckboxEnabledView *)checkbox);
    if (value != 0) {
      ReleaseCapture();
      checkbox_mouse_pressed = 0;
    }
  }
  return 0;
}
#undef ctrl_disabled_color_index
#undef ctrl_disabled_rgb_set
#undef ctrl_shadow_color_index
#undef ctrl_shadow_dx
#undef ctrl_shadow_dy
#undef ctrl_text_color_index
#undef ctrl_text_rgb_set
#undef rect
#undef bitmap
#undef block
#undef checkbox
#undef ps
#undef old_font
#undef bmp_size
#undef green
#undef hdc
#undef label
#undef underline_end
#undef underline_start
#undef box_left
#undef box_top
#undef box_right
#undef box_bottom
#undef red
#undef blue
#undef brush
#undef font_data
#undef prefix
#undef text_rect

/* 005cce40 auto */
void __thiscall checkbox_fire_callback(CheckboxClickView *this,i32 ctrl_id,i32 checked)

{
  if (this->on_toggle != 0) {
    (*(code *)this->on_toggle)(ctrl_id,checked);
  }
  return;
}

/* 005cce80 auto */
void __stdcall control_subclass_wndproc(HWND hwnd,int msg,i32 wparam,i32 lparam)

{
  DWORD DVar1;
  code *base_proc;
  ControlHwndSetView *this;
  
  DVar1 = GetClassLongA(hwnd,-0x12);
  base_proc = (code *)GetWindowLongA(hwnd,DVar1 - 4);
  if ((msg == 2) &&
     (this = (ControlHwndSetView *)GetWindowLongA(hwnd,DVar1 - 8), this != (ControlHwndSetView *)0x0)) {
    control_set_hwnd(this,0);
  }
  (*base_proc)(hwnd,msg,wparam,lparam);
  return;
}

/* 005ccf17 auto */
#define app_hinstance (*(HINSTANCE *)((u8 *)&g.d_006e4ff0))
#define style2 (*(uint *)(frame_ + FRAME_OFF(4)))
#define wc (*(WNDCLASSA *)(frame_ + FRAME_OFF(8)))
#define hwnd2 (*(HWND *)(frame_ + FRAME_OFF(48)))
HWND __cdecl scrollbar_create_hwnd(int *rect,iptr ctrl,uint style_flags,int visible)

{
  WndBase *pCVar1;
  iptr window;
  iptr height;
  int value;
  int nWidth;
  HWND pHVar5;
  HMENU pHVar6;
  HINSTANCE pHVar7;
  LPVOID create_param;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
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
    pHVar6 = (HMENU)0x0;
    pHVar7 = app_hinstance;
    pCVar1 = (WndBase *)ctrl_get_parent((Control *)ctrl);
    window = wnd_get_window(pCVar1);
    pHVar5 = *(HWND *)(window + 4);
    height = rect_height((iptr)rect);
    value = rect_width((iptr)rect);
    hwnd2 = CreateWindowExA(4,s_SCROLLBAR_00637f60,&scrollbar_probe_wnd_title,style_flags | 0x40000000,*rect,
                              rect[1],value,height,pHVar5,pHVar6,pHVar7,create_param);
    scrollbar_base_wndproc = (WNDPROC)GetWindowLongA(hwnd2,-4);
    style2 = GetWindowLongA(hwnd2,-0x10);
    wc.style = 0x8b;
    wc.lpfnWndProc = scrollbar_base_wndproc;
    wc.cbClsExtra = 0;
    scrollbar_base_wnd_extra = GetClassLongA(hwnd2,-0x12);
    wc.cbWndExtra = scrollbar_base_wnd_extra + 8;
    wc.hInstance = app_hinstance;
    wc.hIcon = (HICON)0x0;
    wc.hCursor = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
    wc.hbrBackground = GetStockObject(1);
    wc.lpszMenuName = (LPCSTR)0x0;
    wc.lpszClassName = s_MSScrollBarClass_00637f6c;
    RegisterClassA(&wc);
    scrollbar_class_registered = 1;
    DestroyWindow(hwnd2);
  }
  create_param = (LPVOID)0x0;
  pHVar6 = (HMENU)0x0;
  pHVar7 = app_hinstance;
  pCVar1 = (WndBase *)ctrl_get_parent((Control *)ctrl);
  value = wnd_get_window(pCVar1);
  pHVar5 = *(HWND *)(value + 4);
  value = rect_height((iptr)rect);
  nWidth = rect_width((iptr)rect);
  hwnd2 = CreateWindowExA(4,s_MSScrollBarClass_00637f84,&scrollbar_wnd_title,style2,*rect,rect[1]
                            ,nWidth,value,pHVar5,pHVar6,pHVar7,create_param);
  SetWindowLongA(hwnd2,-4,ADDR(0x5cce80, control_subclass_wndproc));
  SetWindowLongA(hwnd2,scrollbar_base_wnd_extra,ctrl);
  SetWindowLongA(hwnd2,scrollbar_base_wnd_extra + 4,(LONG)scrollbar_base_wndproc);
  ShowScrollBar(hwnd2,2,1);
  scrollbar_hwnd_set_range(hwnd2,1,100);
  return hwnd2;
}
#undef app_hinstance
#undef style2
#undef wc
#undef hwnd2

/* 005cd139 auto */
void __cdecl scrollbar_destroy_hwnd(i32 hwnd)

{
  return;
}

/* 005cd149 auto */
void __cdecl scrollbar_hwnd_handle_msg(HWND hwnd,uint msg,uint wparam,int lparam)

{
  short thumb_pos;
  DWORD DVar2;
  ScrollbarPosView *this;
  iptr cur_pos;
  iptr parent;
  WPARAM *pWVar5;
  iptr page_size;
  int value;
  u32 new_pos;
  LPARAM LVar8;
  
  DVar2 = GetClassLongA(hwnd,-0x12);
  this = (ScrollbarPosView *)GetWindowLongA(hwnd,DVar2 - 8);
  cur_pos = scrollbar_get_cur_pos(this);
  if (msg == 0x111) {
    if (wparam == 0x7f) {
      SetScrollPos(hwnd,2,lparam,1);
      new_pos = GetScrollPos(hwnd,2);
      this->cur_pos = new_pos;
    }
  }
  else if ((0x113 < msg) && (msg < 0x116)) {
    thumb_pos = (short)(wparam >> 0x10);
    switch(wparam & 0xffff) {
    case 0:
      value = input_lbutton_down();
      if (value == 0) {
        value = ctrl_get_rect(this);
        LVar8 = *(LPARAM *)(value + 4);
        pWVar5 = (WPARAM *)ctrl_get_rect(this);
        PostMessageA(hwnd,0x202,*pWVar5,LVar8);
      }
      else {
        SetScrollPos(hwnd,2,cur_pos - 1,1);
        new_pos = GetScrollPos(hwnd,2);
        parent = ctrl_get_parent((Control *)this);
        wnd_set_active_child(parent);
        this->cur_pos = new_pos;
        scrollbar_fire_change((ScrollbarChangeView *)this,new_pos);
      }
      break;
    case 1:
      value = input_lbutton_down();
      if (value == 0) {
        value = ctrl_get_rect(this);
        LVar8 = *(LPARAM *)(value + 4);
        pWVar5 = (WPARAM *)ctrl_get_rect(this);
        PostMessageA(hwnd,0x202,*pWVar5,LVar8);
      }
      else {
        SetScrollPos(hwnd,2,cur_pos + 1,1);
        new_pos = GetScrollPos(hwnd,2);
        parent = ctrl_get_parent((Control *)this);
        wnd_set_active_child(parent);
        this->cur_pos = new_pos;
        scrollbar_fire_change((ScrollbarChangeView *)this,new_pos);
      }
      break;
    case 2:
      value = scrollbar_get_page_size((ScrollbarPageView *)this);
      SetScrollPos(hwnd,2,cur_pos - value,1);
      new_pos = GetScrollPos(hwnd,2);
      parent = ctrl_get_parent((Control *)this);
      wnd_set_active_child(parent);
      this->cur_pos = new_pos;
      scrollbar_fire_change((ScrollbarChangeView *)this,new_pos);
      break;
    case 3:
      page_size = scrollbar_get_page_size((ScrollbarPageView *)this);
      SetScrollPos(hwnd,2,cur_pos + page_size,1);
      new_pos = GetScrollPos(hwnd,2);
      parent = ctrl_get_parent((Control *)this);
      wnd_set_active_child(parent);
      this->cur_pos = new_pos;
      scrollbar_fire_change((ScrollbarChangeView *)this,new_pos);
      break;
    case 4:
      SetScrollPos(hwnd,2,(int)thumb_pos,1);
      parent = ctrl_get_parent((Control *)this);
      wnd_set_active_child(parent);
      this->cur_pos = (int)thumb_pos;
      scrollbar_fire_change((ScrollbarChangeView *)this,this->cur_pos);
      break;
    case 5:
      parent = ctrl_get_parent((Control *)this);
      wnd_set_active_child(parent);
      scrollbar_fire_track((ScrollbarTrackView *)this,(int)thumb_pos);
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
u32 __thiscall scrollbar_get_cur_pos(ScrollbarPosView *this)

{
  return this->cur_pos;
}

/* 005cd640 auto */
void __thiscall scrollbar_fire_change(ScrollbarChangeView *this,i32 pos)

{
  if (this->on_change != 0) {
    (*(code *)this->on_change)(pos);
  }
  return;
}

/* 005cd680 auto */
void __thiscall scrollbar_fire_track(ScrollbarTrackView *this,i32 pos)

{
  if (this->on_track != 0) {
    (*(code *)this->on_track)(pos);
  }
  return;
}

/* 005cd6c0 auto */
u32 __thiscall scrollbar_get_page_size(ScrollbarPageView *this)

{
  return this->page_size;
}

/* 005d25c0 auto */
#define rect (*(tagRECT *)(frame_ + FRAME_OFF(4)))
void __thiscall
edit_create_at
          (EditControl *this,iptr parent,i32 ctrl_id,int x,int y,int width,
          iptr text)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  this->edit_font = (u32)ctrl_default_font;
  this->is_enabled = 0;
  SetRect(&rect,x,y,width + x,y + 0x1e);
  edit_create(this,parent,ctrl_id,(iptr)&rect,text);
  return;
}
#undef rect

/* 005d2740 auto */
#define app_hinstance (*(HINSTANCE *)((u8 *)&g.d_006e4ff0))
#define wc (*(WNDCLASSA *)(frame_ + FRAME_OFF(4)))
#define hwnd2 (*(HWND *)(frame_ + FRAME_OFF(44)))
#define style2 (*(uint *)(frame_ + FRAME_OFF(48)))
HWND __cdecl edit_create_window(int *rect,iptr ctrl,uint flags,int visible,GameFont *font)

{
  WndBase *pCVar1;
  iptr window;
  iptr height;
  int value;
  int nWidth;
  i32 font_handle;
  WPARAM *pWVar6;
  HWND pHVar7;
  HMENU pHVar8;
  HINSTANCE pHVar9;
  LPVOID create_param;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
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
    pHVar8 = (HMENU)0x0;
    pHVar9 = app_hinstance;
    pCVar1 = (WndBase *)ctrl_get_parent((Control *)ctrl);
    window = wnd_get_window(pCVar1);
    pHVar7 = *(HWND *)(window + 4);
    height = rect_height((iptr)rect);
    value = rect_width((iptr)rect);
    hwnd2 = CreateWindowExA(4,&editbox_native_class_name,&editbox_probe_wnd_title,style2,*rect,rect[1],value,height,
                              pHVar7,pHVar8,pHVar9,create_param);
    edit_base_wndproc = (WNDPROC)GetWindowLongA(hwnd2,-4);
    wc.style = 0x88;
    wc.cbClsExtra = 0;
    wc.lpfnWndProc = edit_base_wndproc;
    edit_base_wnd_extra = GetClassLongA(hwnd2,-0x12);
    wc.cbWndExtra = edit_base_wnd_extra + 8;
    wc.hInstance = app_hinstance;
    wc.hIcon = (HICON)0x0;
    wc.hCursor = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f01);
    wc.hbrBackground = (HBRUSH)0x0;
    wc.lpszMenuName = (LPCSTR)0x0;
    wc.lpszClassName = s_MSEditBoxClass_00638324;
    RegisterClassA(&wc);
    editbox_class_registered = 1;
    DestroyWindow(hwnd2);
  }
  create_param = (LPVOID)0x0;
  pHVar8 = (HMENU)0x0;
  pHVar9 = app_hinstance;
  pCVar1 = (WndBase *)ctrl_get_parent((Control *)ctrl);
  value = wnd_get_window(pCVar1);
  pHVar7 = *(HWND *)(value + 4);
  value = rect_height((iptr)rect);
  nWidth = rect_width((iptr)rect);
  hwnd2 = CreateWindowExA(4,s_MSEditBoxClass_00638338,&editbox_wnd_title,style2 | 0x40800000,*rect,
                            rect[1],nWidth,value,pHVar7,pHVar8,pHVar9,create_param);
  font_handle = font_get_handle(font);
  pWVar6 = (WPARAM *)mem_handle_lock(font_handle);
  SendMessageA(hwnd2,0x30,*pWVar6,0);
  font_handle = font_get_handle(font);
  mem_handle_unlock(font_handle);
  SetWindowLongA(hwnd2,-4,ADDR(0x5d2a01, edit_subclass_wndproc));
  SetWindowLongA(hwnd2,edit_base_wnd_extra,(LONG)edit_base_wndproc);
  SetWindowLongA(hwnd2,edit_base_wnd_extra + 4,ctrl);
  return hwnd2;
}
#undef app_hinstance
#undef wc
#undef hwnd2
#undef style2

/* 005d2a01 auto */
#define pass_through (*(int *)(frame_ + FRAME_OFF(0)))
LRESULT __stdcall edit_subclass_wndproc(HWND hwnd,uint msg,WPARAM wparam,LPARAM lparam)

{
  Control *this;
  DWORD DVar1;
  WNDPROC lpPrevWndFunc;
  iptr key;
  HWND pHVar2;
  iptr parent;
  WndBase *this_00;
  int window;
  LRESULT LVar5;
  iptr long_index;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  this = (Control *)GetWindowLongA(hwnd,10);
  DVar1 = GetClassLongA(hwnd,-0x12);
  lpPrevWndFunc = (WNDPROC)GetWindowLongA(hwnd,DVar1 - 8);
  if (msg < 8) {
    if (msg == 7) {
      parent = ctrl_get_parent(this);
      wnd_set_active_child(parent);
      if ((char)this->font == '\0') {
        edit_hwnd_set_sel(hwnd,0,0xffffffff);
      }
      LVar5 = CallWindowProcA(lpPrevWndFunc,hwnd,7,wparam,lparam);
      return LVar5;
    }
    if (msg == 2) {
      if (this != (Control *)0x0) {
        control_set_hwnd((ControlHwndSetView *)this,0);
      }
      LVar5 = CallWindowProcA(lpPrevWndFunc,hwnd,2,wparam,lparam);
      return LVar5;
    }
  }
  else if (msg < 0x202) {
    if (msg == 0x201) {
LAB_005d2c05:
      long_index = 0;
      pHVar2 = GetParent(hwnd);
      this_00 = (WndBase *)GetWindowLongA(pHVar2,long_index);
      window = wnd_get_window(this_00);
      if ((*(byte *)(window + 0x49) & 2) != 0) {
        pHVar2 = GetParent(hwnd);
        SetFocus(pHVar2);
        pHVar2 = GetParent(hwnd);
        BringWindowToTop(pHVar2);
      }
      LVar5 = CallWindowProcA(lpPrevWndFunc,hwnd,msg,wparam,lparam);
      return LVar5;
    }
    if (msg == 0x100) {
      if (((wparam != 9) && (wparam != 0xd)) && (wparam != 0x1b)) {
        LVar5 = CallWindowProcA(lpPrevWndFunc,hwnd,0x100,wparam,lparam);
        return LVar5;
      }
      pHVar2 = GetParent(hwnd);
      SendMessageA(pHVar2,msg,wparam,lparam);
      return 1;
    }
    if (msg == 0x101) {
      parent = ctrl_get_parent(this);
      wnd_set_active_child(parent);
      key = input_map_vkey(wparam);
      if ((0x2af < key) && (key < 0x2b5)) {
        edit_fire_key_callback((EditKeyView *)this,key);
      }
      LVar5 = CallWindowProcA(lpPrevWndFunc,hwnd,0x101,wparam,lparam);
      return LVar5;
    }
    if (msg == 0x102) {
      parent = ctrl_get_parent(this);
      wnd_set_active_child(parent);
      pass_through = 0;
      if (wparam != 9) {
        parent = input_map_vkey(wparam);
        pass_through = edit_fire_key_callback((EditKeyView *)this,parent);
      }
      if (pass_through == 0) {
        return 1;
      }
      LVar5 = CallWindowProcA(lpPrevWndFunc,hwnd,0x102,wparam,lparam);
      return LVar5;
    }
  }
  else if (msg == 0x204) goto LAB_005d2c05;
  LVar5 = CallWindowProcA(lpPrevWndFunc,hwnd,msg,wparam,lparam);
  return LVar5;
}
#undef pass_through

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
  iptr LVar1;
  
  *buffer = (short)buf_size - 1;
  LVar1 = SendMessageA(hwnd,0xc4,line,(LPARAM)buffer);
  *(i8 *)(LVar1 + (int)buffer) = 0;
  return LVar1;
}

/* 005d2e31 auto */
LRESULT __cdecl edit_hwnd_get_line_count(HWND hwnd)

{
  LRESULT LVar1;
  
  LVar1 = SendMessageA(hwnd,0xba,0,0);
  return LVar1;
}

/* 005d2e9c auto */
LRESULT __cdecl edit_line_index(HWND hwnd,WPARAM line)

{
  LRESULT LVar1;
  
  LVar1 = SendMessageA(hwnd,0xbb,line,0);
  return LVar1;
}

/* 005d2ec1 auto */
LRESULT __cdecl edit_line_length(HWND hwnd,WPARAM char_index)

{
  LRESULT LVar1;
  
  LVar1 = SendMessageA(hwnd,0xc1,char_index,0);
  return LVar1;
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
i32 __thiscall edit_fire_key_callback(EditKeyView *this,iptr key)

{
  i32 result;
  
  if (this->on_key == 0) {
    result = 1;
  }
  else {
    result = (*(code *)this->on_key)(this->control_id,key);
  }
  return result;
}

/* 005d3130 auto */
#define app_hinstance (*(HINSTANCE *)((u8 *)&g.d_006e4ff0))
#define style2 (*(DWORD *)(frame_ + FRAME_OFF(4)))
#define wc (*(WNDCLASSA *)(frame_ + FRAME_OFF(8)))
#define hwnd2 (*(HWND *)(frame_ + FRAME_OFF(48)))
HWND __cdecl combo_create_window(int *rect,iptr ctrl,int visible)

{
  WndBase *pCVar1;
  iptr window;
  iptr height;
  int value;
  int nWidth;
  HWND pHVar5;
  HMENU pHVar6;
  HINSTANCE pHVar7;
  LPVOID create_param;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  style2 = 0x40a10003;
  if (visible != 0) {
    style2 = 0x50a10003;
  }
  if (combo_class_registered == 0) {
    create_param = (LPVOID)0x0;
    pHVar6 = (HMENU)0x0;
    pHVar7 = app_hinstance;
    pCVar1 = (WndBase *)ctrl_get_parent((Control *)ctrl);
    window = wnd_get_window(pCVar1);
    pHVar5 = *(HWND *)(window + 4);
    height = rect_height((iptr)rect);
    value = rect_width((iptr)rect);
    hwnd2 = CreateWindowExA(4,s_COMBOBOX_00638350,&combo_probe_wnd_title,style2,*rect,rect[1],value
                              ,height,pHVar5,pHVar6,pHVar7,create_param);
    combo_base_wndproc = (WNDPROC)GetWindowLongA(hwnd2,-4);
    wc.style = 0x88;
    wc.cbClsExtra = 0;
    wc.lpfnWndProc = combo_base_wndproc;
    combo_base_wnd_extra = GetClassLongA(hwnd2,-0x12);
    wc.cbWndExtra = combo_base_wnd_extra + 8;
    wc.hInstance = app_hinstance;
    wc.hIcon = (HICON)0x0;
    wc.hCursor = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
    wc.hbrBackground = (HBRUSH)0x0;
    wc.lpszMenuName = (LPCSTR)0x0;
    wc.lpszClassName = s_MSComboBoxClass_0063835c;
    RegisterClassA(&wc);
    combo_class_registered = 1;
    DestroyWindow(hwnd2);
  }
  style2 = 0x40a10203;
  if (visible != 0) {
    style2 = 0x50a10203;
  }
  create_param = (LPVOID)0x0;
  pHVar6 = (HMENU)0x0;
  pHVar7 = app_hinstance;
  pCVar1 = (WndBase *)ctrl_get_parent((Control *)ctrl);
  value = wnd_get_window(pCVar1);
  pHVar5 = *(HWND *)(value + 4);
  value = rect_height((iptr)rect);
  nWidth = rect_width((iptr)rect);
  hwnd2 = CreateWindowExA(4,s_MSComboBoxClass_00638370,&combo_wnd_title,style2,*rect,rect[1],
                            nWidth,value,pHVar5,pHVar6,pHVar7,create_param);
  SetWindowLongA(hwnd2,-4,ADDR(0x5d3310, combo_subclass_wndproc));
  SetWindowLongA(hwnd2,combo_base_wnd_extra,(LONG)combo_base_wndproc);
  SetWindowLongA(hwnd2,combo_base_wnd_extra + 4,ctrl);
  return hwnd2;
}
#undef app_hinstance
#undef style2
#undef wc
#undef hwnd2

/* 005d3310 auto */
LRESULT __stdcall combo_subclass_wndproc(HWND hwnd,uint msg,uint wparam,LPARAM lparam)

{
  DWORD DVar1;
  WNDPROC lpPrevWndFunc;
  Control *this;
  iptr parent;
  HWND pHVar3;
  WndBase *this_00;
  iptr window;
  LRESULT LVar4;
  iptr long_index;
  
  DVar1 = GetClassLongA(hwnd,-0x12);
  lpPrevWndFunc = (WNDPROC)GetWindowLongA(hwnd,DVar1 - 8);
  this = (Control *)GetWindowLongA(hwnd,DVar1 - 4);
  if (this == (Control *)0x0) {
    return 1;
  }
  parent = ctrl_get_parent(this);
  wnd_set_active_child(parent);
  if (msg < 0x103) {
    if (0xff < msg) {
      if (((wparam != 9) && (wparam != 0xd)) && (wparam != 0x1b)) {
        LVar4 = CallWindowProcA(lpPrevWndFunc,hwnd,msg,wparam,lparam);
        return LVar4;
      }
      pHVar3 = GetParent(hwnd);
      SendMessageA(pHVar3,msg,wparam,lparam);
      return 1;
    }
    if (msg == 2) {
      if (this != (Control *)0x0) {
        control_set_hwnd((ControlHwndSetView *)this,0);
      }
      LVar4 = CallWindowProcA(lpPrevWndFunc,hwnd,2,wparam,lparam);
      return LVar4;
    }
  }
  else {
    if ((msg == 0x201) || (msg == 0x204)) {
      long_index = 0;
      pHVar3 = GetParent(hwnd);
      this_00 = (WndBase *)GetWindowLongA(pHVar3,long_index);
      window = wnd_get_window(this_00);
      if ((*(byte *)(window + 0x49) & 2) != 0) {
        pHVar3 = GetParent(hwnd);
        SetFocus(pHVar3);
        pHVar3 = GetParent(hwnd);
        BringWindowToTop(pHVar3);
      }
      LVar4 = CallWindowProcA(lpPrevWndFunc,hwnd,msg,wparam,lparam);
      return LVar4;
    }
    if (msg == 0x4c8) {
      if (wparam >> 0x10 == 1) {
        if (this == (Control *)0x0) {
          return 1;
        }
        combo_fire_selchange((ComboBoxSelChangeView *)this);
        return 1;
      }
      if (wparam >> 0x10 != 2) {
        return 1;
      }
      combo_fire_dblclick((ComboBoxDblClickView *)this);
      return 1;
    }
  }
  LVar4 = CallWindowProcA(lpPrevWndFunc,hwnd,msg,wparam,lparam);
  return LVar4;
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
  WPARAM *pWVar1;
  
  pWVar1 = (WPARAM *)mem_handle_lock(font_handle);
  SendMessageA(hwnd,0x30,*pWVar1,0);
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
  LRESULT LVar1;
  
  LVar1 = SendMessageA(hwnd,0x147,0,0);
  if (LVar1 == -1) {
    LVar1 = -1;
  }
  return LVar1;
}

/* 005d36f6 auto */
void __cdecl combo_hwnd_set_cur_sel(HWND hwnd,WPARAM index)

{
  SendMessageA(hwnd,0x14e,index,0);
  return;
}

/* 005d3720 auto */
void __thiscall combo_fire_dblclick(ComboBoxDblClickView *this)

{
  if (this->on_dblclick != 0) {
    (*(code *)this->on_dblclick)(this->control_id);
  }
  return;
}

/* 005d3760 auto */
void __thiscall combo_fire_selchange(ComboBoxSelChangeView *this)

{
  if (this->on_selchange != 0) {
    (*(code *)this->on_selchange)(this->control_id);
  }
  return;
}

/* 005d37a0 auto */
#define app_hinstance (*(HINSTANCE *)((u8 *)&g.d_006e4ff0))
#define style2 (*(uint *)(frame_ + FRAME_OFF(0)))
#define wc (*(WNDCLASSA *)(frame_ + FRAME_OFF(8)))
#define hwnd2 (*(HWND *)(frame_ + FRAME_OFF(48)))
HWND __cdecl listbox_create_hwnd(int *rect,iptr ctrl,int visible,int multi_column,GameFont *font)

{
  uint style_bits;
  WndBase *pCVar2;
  iptr window;
  iptr height;
  int value;
  int nWidth;
  i32 font_handle;
  WPARAM *pWVar7;
  HWND pHVar8;
  HMENU pHVar9;
  HINSTANCE pHVar10;
  LPVOID create_param;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
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
    pHVar9 = (HMENU)0x0;
    pHVar10 = app_hinstance;
    pCVar2 = (WndBase *)ctrl_get_parent((Control *)ctrl);
    window = wnd_get_window(pCVar2);
    pHVar8 = *(HWND *)(window + 4);
    height = rect_height((iptr)rect);
    value = rect_width((iptr)rect);
    hwnd2 = CreateWindowExA(4,s_LISTBOX_0063838c,&listbox_probe_wnd_title,style2,*rect,rect[1],value,
                              height,pHVar8,pHVar9,pHVar10,create_param);
    listbox_base_wndproc = (WNDPROC)GetWindowLongA(hwnd2,-4);
    wc.style = 0x88;
    wc.cbClsExtra = 0;
    wc.lpfnWndProc = listbox_base_wndproc;
    listbox_base_wnd_extra = GetClassLongA(hwnd2,-0x12);
    wc.cbWndExtra = listbox_base_wnd_extra + 8;
    wc.hInstance = app_hinstance;
    wc.hIcon = (HICON)0x0;
    wc.hCursor = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
    wc.hbrBackground = (HBRUSH)0x0;
    wc.lpszMenuName = (LPCSTR)0x0;
    wc.lpszClassName = s_MSListBoxClass_00638394;
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
  pHVar9 = (HMENU)0x0;
  pHVar10 = app_hinstance;
  pCVar2 = (WndBase *)ctrl_get_parent((Control *)ctrl);
  value = wnd_get_window(pCVar2);
  pHVar8 = *(HWND *)(value + 4);
  value = rect_height((iptr)rect);
  nWidth = rect_width((iptr)rect);
  hwnd2 = CreateWindowExA(4,s_MSListBoxClass_006383a8,&listbox_wnd_title,style2,*rect,rect[1],
                            nWidth,value,pHVar8,pHVar9,pHVar10,create_param);
  font_handle = font_get_handle(font);
  pWVar7 = (WPARAM *)mem_handle_lock(font_handle);
  SendMessageA(hwnd2,0x30,*pWVar7,0);
  font_handle = font_get_handle(font);
  mem_handle_unlock(font_handle);
  SetWindowLongA(hwnd2,-4,ADDR(0x5d39e2, listbox_subclass_wndproc));
  SetWindowLongA(hwnd2,listbox_base_wnd_extra,(LONG)listbox_base_wndproc);
  SetWindowLongA(hwnd2,listbox_base_wnd_extra + 4,ctrl);
  return hwnd2;
}
#undef app_hinstance
#undef style2
#undef wc
#undef hwnd2

/* 005d39e2 auto */
LRESULT __stdcall listbox_subclass_wndproc(HWND hwnd,uint msg,uint wparam,LPARAM lparam)

{
  DWORD DVar1;
  WNDPROC lpPrevWndFunc;
  Control *this;
  iptr parent;
  HWND pHVar3;
  WndBase *this_00;
  iptr window;
  LRESULT LVar4;
  iptr long_index;
  
  DVar1 = GetClassLongA(hwnd,-0x12);
  lpPrevWndFunc = (WNDPROC)GetWindowLongA(hwnd,DVar1 - 8);
  this = (Control *)GetWindowLongA(hwnd,DVar1 - 4);
  if (this == (Control *)0x0) {
    return 1;
  }
  parent = ctrl_get_parent(this);
  wnd_set_active_child(parent);
  if (msg < 0x103) {
    if (0xff < msg) {
      if (((wparam != 9) && (wparam != 0xd)) && (wparam != 0x1b)) {
        LVar4 = CallWindowProcA(lpPrevWndFunc,hwnd,msg,wparam,lparam);
        return LVar4;
      }
      pHVar3 = GetParent(hwnd);
      SendMessageA(pHVar3,msg,wparam,lparam);
      return 1;
    }
    if (msg == 2) {
      if (this != (Control *)0x0) {
        control_set_hwnd((ControlHwndSetView *)this,0);
      }
      LVar4 = CallWindowProcA(lpPrevWndFunc,hwnd,2,wparam,lparam);
      return LVar4;
    }
  }
  else {
    if ((msg == 0x201) || (msg == 0x204)) {
      long_index = 0;
      pHVar3 = GetParent(hwnd);
      this_00 = (WndBase *)GetWindowLongA(pHVar3,long_index);
      window = wnd_get_window(this_00);
      if ((*(byte *)(window + 0x49) & 2) != 0) {
        pHVar3 = GetParent(hwnd);
        SetFocus(pHVar3);
        pHVar3 = GetParent(hwnd);
        BringWindowToTop(pHVar3);
      }
      LVar4 = CallWindowProcA(lpPrevWndFunc,hwnd,msg,wparam,lparam);
      return LVar4;
    }
    if (msg == 0x4c8) {
      if (wparam >> 0x10 == 1) {
        if (this == (Control *)0x0) {
          return 1;
        }
        listbox_fire_selchange((ListBoxSelChangeView *)this);
        return 1;
      }
      if (wparam >> 0x10 != 2) {
        return 1;
      }
      listbox_fire_dblclick((ListBoxDblClickView *)this);
      return 1;
    }
  }
  LVar4 = CallWindowProcA(lpPrevWndFunc,hwnd,msg,wparam,lparam);
  return LVar4;
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
  WPARAM *pWVar1;
  
  pWVar1 = (WPARAM *)mem_handle_lock(font_handle);
  SendMessageA(hwnd,0x30,*pWVar1,0);
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
  LRESULT LVar1;
  
  LVar1 = SendMessageA(hwnd,0x188,0,0);
  if (LVar1 == -1) {
    crt_strcpy(buffer,&listbox_no_sel_text);
  }
  else {
    listbox_hwnd_get_text(hwnd,LVar1,buffer);
  }
  return;
}

/* 005d3dbf auto */
LRESULT __cdecl listbox_hwnd_get_cur_sel(HWND hwnd)

{
  LRESULT LVar1;
  
  LVar1 = SendMessageA(hwnd,0x188,0,0);
  if (LVar1 == -1) {
    LVar1 = -1;
  }
  return LVar1;
}

/* 005d3e92 auto */
void __cdecl listbox_hwnd_set_cur_sel(HWND hwnd,WPARAM index)

{
  SendMessageA(hwnd,0x186,index,0);
  return;
}

/* 005d3f30 auto */
void __thiscall listbox_fire_dblclick(ListBoxDblClickView *this)

{
  if (this->on_dblclick != 0) {
    (*(code *)this->on_dblclick)(this->control_id);
  }
  return;
}

/* 005d3f70 auto */
void __thiscall listbox_fire_selchange(ListBoxSelChangeView *this)

{
  if (this->on_selchange != 0) {
    (*(code *)this->on_selchange)(this->control_id);
  }
  return;
}

/* 005d4014 auto */
#define i (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall radiogrp_show_all(RadioGroupShowView *this)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (i = 0; i < (int)this->item_count; i++) {
    hwnd_show(*(i32 *)(this->items + i * 0xa4));
    wnd_invalidate(*(i32 *)(this->items + i * 0xa4));
  }
  return;
}
#undef i

/* 005d4167 auto */
void __cdecl ctrl_set_pending_font(iptr font)

{
  radio_default_font = (i8 *)font;
  return;
}

/* 005d7cb0 auto */
#define gfx_black_color_index (*(byte *)((u8 *)&g.d_00638b40))
#define draw_ctx_b (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define draw_ctx_a (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
#define origin_y2 (*(i32 *)(frame_ + FRAME_OFF(36)))
#define origin_x2 (*(i32 *)(frame_ + FRAME_OFF(40)))
#define scale_den2 (*(i32 *)(frame_ + FRAME_OFF(44)))
#define scale_num2 (*(i32 *)(frame_ + FRAME_OFF(48)))
#define center_y (*(int *)(frame_ + FRAME_OFF(52)))
#define center_x (*(int *)(frame_ + FRAME_OFF(56)))
#define rect (*(tagRECT *)(frame_ + FRAME_OFF(60)))
#define half_h (*(int *)(frame_ + FRAME_OFF(76)))
#define half_w (*(int *)(frame_ + FRAME_OFF(80)))
#define dst_rect (*(tagRECT *)(frame_ + FRAME_OFF(84)))
#define src_left (*(int *)(frame_ + FRAME_OFF(100)))
#define src_top (*(int *)(frame_ + FRAME_OFF(104)))
#define src_right (*(int *)(frame_ + FRAME_OFF(108)))
#define src_bottom (*(int *)(frame_ + FRAME_OFF(112)))
void __thiscall
spritebtn_init_from_sprite
          (SpriteButton *this,WndPaletteView *parent,i32 ctrl_id,int x,int y,
          int width,int height,iptr sprite,uint bg_color)

{
  u32 value;
  int size;
  WndPaletteView *pCVar3;
  i32 palette;
  int yBottom;
  i8 frame_[FRAME_OFF(120)] __attribute__((aligned(8)));  /* original stack frame */
  
  this->pressed_state = '\0';
  value = wnd_get_palette(parent);
  this->ctrl_palette = value;
  SetRect(&rect,x,y,width + x,y + height);
  ctrl_init((Control *)this,(iptr)parent,6,ctrl_id,(iptr)&rect);
  this->is_enabled = 0;
  this->on_click = 0;
  gfx_get_scale_ratio((iptr)&scale_num2,(iptr)&scale_den2);
  gfx_set_scale_ratio(1,1);
  surface_create((DibSurface *)(this->button_surface),width,height);
  surface_create((DibSurface *)&this->on_select,width,height);
  surface_fill((DibSurface *)(this->button_surface),bg_color & 0xff);
  surface_fill((DibSurface *)&this->on_select,bg_color & 0xff);
  center_x = width >> 1;
  center_y = height >> 1;
  sprite_get_origin((SpriteOriginGetView *)sprite,(iptr)&origin_x2,(iptr)&origin_y2);
  half_w = sprite_get_width((Sprite *)sprite);
  half_w = half_w >> 1;
  half_h = sprite_get_height((Sprite *)sprite);
  half_h = half_h >> 1;
  sprite_set_origin((SpriteOriginSetView *)sprite,-half_w,-half_h);
  sprite_draw
            ((Sprite *)sprite,(iptr)draw_ctx_a,(iptr)(this->button_surface),center_x,center_y);
  sprite_draw
            ((Sprite *)sprite,(iptr)draw_ctx_b,(iptr)&this->on_select,center_x,center_y);
  sprite_set_origin((SpriteOriginSetView *)sprite,origin_x2,origin_y2);
  gfx_set_scale_ratio(scale_num2,scale_den2);
  size = surface_height((DibSurface *)(this->button_surface));
  yBottom = y + size - 1;
  size = surface_width((DibSurface *)(this->button_surface));
  SetRect(&rect,x,y,x + size - 1,yBottom);
  OffsetRect(&rect,-rect.left,-rect.top);
  dst_rect.left = rect.left;
  dst_rect.top = rect.top;
  dst_rect.right = rect.right;
  dst_rect.bottom = rect.bottom;
  SetRect(&dst_rect,rect.left,rect.top,rect.right - 2,rect.bottom - 2);
  src_left = dst_rect.left;
  src_top = dst_rect.top;
  src_right = dst_rect.right;
  src_bottom = dst_rect.bottom;
  OffsetRect(&dst_rect,2,2);
  surface_fill((DibSurface *)(this->button_surface),(uint)gfx_black_color_index);
  surface_blit
            ((DibSurface *)&this->on_select,(iptr)(this->button_surface),(iptr)&src_left,
             (iptr)&dst_rect);
  pCVar3 = (WndPaletteView *)ctrl_get_parent((Control *)this);
  palette = wnd_get_palette(pCVar3);
  surface_apply_palette((DibSurface *)(this->button_surface),palette);
  pCVar3 = (WndPaletteView *)ctrl_get_parent((Control *)this);
  palette = wnd_get_palette(pCVar3);
  surface_apply_palette((DibSurface *)&this->on_select,palette);
  value = spritebtn_create_hwnd(x,y,width,height,(iptr)this,1);
  this->hwnd = value;
  return;
}
#undef gfx_black_color_index
#undef draw_ctx_b
#undef draw_ctx_a
#undef origin_y2
#undef origin_x2
#undef scale_den2
#undef scale_num2
#undef center_y
#undef center_x
#undef rect
#undef half_h
#undef half_w
#undef dst_rect
#undef src_left
#undef src_top
#undef src_right
#undef src_bottom

/* 005d8da1 auto */
#define height2 (*(int *)(frame_ + FRAME_OFF(4)))
#define metrics (*(tagTEXTMETRICA *)(frame_ + FRAME_OFF(16)))
#define font_data (*(i32 * *)(frame_ + FRAME_OFF(72)))
int __cdecl radiogrp_item_height(GameFont *font)

{
  HDC hdc;
  HDC hdc_00;
  i32 font_handle;
  i8 frame_[FRAME_OFF(80)] __attribute__((aligned(8)));  /* original stack frame */
  
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
#undef height2
#undef metrics
#undef font_data

/* 005d8e3f auto */
#define app_hinstance (*(HINSTANCE *)((u8 *)&g.d_006e4ff0))
#define item_x (*(int *)(frame_ + FRAME_OFF(4)))
#define style2 (*(DWORD *)(frame_ + FRAME_OFF(8)))
#define index (*(uint *)(frame_ + FRAME_OFF(32)))
#define cursor (*(char * *)(frame_ + FRAME_OFF(48)))
#define label (*(char * *)(frame_ + FRAME_OFF(56)))
#define hotkey (*(char (*)[4])(frame_ + FRAME_OFF(60)))
#define item_y (*(int *)(frame_ + FRAME_OFF(64)))
i32 __cdecl
radiogrp_create_items(iptr count_out,int *rect,int columns,iptr group,int item_count,iptr labels,int visible
            ,i32 font)

{
  int *hotkey_pos;
  HBITMAP pHVar2;
  HBITMAP pHVar3;
  HBITMAP pHVar4;
  i32 handle;
  iptr items;
  int col_width;
  int row_height;
  int nHeight;
  WndBase *this;
  iptr window;
  int half_row;
  HWND pHVar11;
  iptr block;
  size_t len;
  int half_item;
  HMENU hMenu;
  HINSTANCE hInstance;
  LPVOID lpParam;
  i8 frame_[FRAME_OFF(72)] __attribute__((aligned(8)));  /* original stack frame */
  
  pHVar2 = LoadBitmapA(app_hinstance,(LPCSTR)0x12d);
  pHVar3 = LoadBitmapA(app_hinstance,(LPCSTR)0x12f);
  pHVar4 = LoadBitmapA(app_hinstance,(LPCSTR)0x12e);
  handle = mem_handle_alloc(item_count * 0xa4);
  items = mem_handle_lock(handle);
  col_width = rect_width((iptr)rect);
  col_width = col_width / columns;
  row_height = rect_height((iptr)rect);
  row_height = (row_height * columns) / item_count;
  nHeight = radiogrp_item_height(font);
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
    hInstance = app_hinstance;
    this = (WndBase *)ctrl_get_parent((Control *)group);
    window = wnd_get_window(this);
    half_row = row_height >> 1;
    half_item = nHeight >> 1;
    pHVar11 = CreateWindowExA(4,s_MSControlClass_00638708,&radiogrp_item_wnd_title,style2,item_x,
                              (half_row - half_item) + item_y,col_width,nHeight,*(HWND *)(window + 4),hMenu,
                              hInstance,lpParam);
    *(HWND *)(items + index * 0xa4) = pHVar11;
    block = ctrl_init_block(*(i32 *)(items + index * 0xa4),group);
    if (index == 0) {
      *(i32 *)(block + 8) = 0;
    }
    else {
      *(i32 *)(block + 8) = 1;
    }
    *(HBITMAP *)(block + 0xc) = pHVar2;
    *(HBITMAP *)(block + 0x10) = pHVar3;
    *(HBITMAP *)(block + 0x14) = pHVar4;
    *(uint *)(block + 0x24) = index * 0xa4 + items;
    *(i32 *)(block + 0x2c) = 3;
    SetWindowLongA(*(HWND *)(items + index * 0xa4),-4,ADDR(0x5d9b86, radiogrp_item_wndproc));
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
    crt_strcpy(index * 0xa4 + items + 0x1c,label);
    cursor = (char *)(index * 0xa4 + items + 0x1c);
    *(i32 *)(items + 0xa0 + index * 0xa4) = 0;
    while( true ) {
      if (*cursor == '\0') goto LAB_005d9226;
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
LAB_005d9226:
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
#undef app_hinstance
#undef item_x
#undef style2
#undef index
#undef cursor
#undef label
#undef hotkey
#undef item_y

/* 005d99f4 auto */
#define i (*(i32 *)(frame_ + FRAME_OFF(0)))
void __cdecl radiogrp_destroy_items(int count,int handle)

{
  iptr items;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (handle == 0) {
    dbg_log(ADDR(0x63872c, ((u8 *)&g.d_0063872c)));
  }
  else {
    items = mem_handle_lock(handle);
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
#undef i

/* 005d9a9a auto */
#define wnd_active_child (*(i32 *)((u8 *)&g.d_00637ea4))
void __cdecl radiogrp_item_activate(HWND hwnd)

{
  RadioGroupItemsView *this;
  iptr block;
  iptr selected;
  iptr old_sel;
  iptr items;
  iptr new_sel;
  int item;
  i32 sel_index;
  i32 ctrl_id;
  RECT *pRVar9;
  BOOL BVar10;
  
  block = wnd_from_hwnd(hwnd);
  if (block != 0) {
    this = *(RadioGroupItemsView **)(block + 4);
    item = *(int *)(block + 0x24);
    SetFocus(hwnd);
    selected = radiogrp_get_selected((RadioGroupGetSelView *)this);
    if ((selected != *(int *)(item + 0x14)) && (*(int *)(item + 0x18) == 1)) {
      BVar10 = 0;
      pRVar9 = (RECT *)0x0;
      old_sel = radiogrp_get_selected((RadioGroupGetSelView *)this);
      items = radiogrp_get_items(this);
      InvalidateRect(*(HWND *)(items + old_sel * 0xa4),pRVar9,BVar10);
      radiogrp_set_selected((RadioGroupSetSelView *)this,*(i32 *)(item + 0x14));
      BVar10 = 0;
      pRVar9 = (RECT *)0x0;
      new_sel = radiogrp_get_selected((RadioGroupGetSelView *)this);
      item = radiogrp_get_items(this);
      InvalidateRect(*(HWND *)(item + new_sel * 0xa4),pRVar9,BVar10);
    }
    wnd_active_child = ctrl_get_parent((Control *)this);
    sel_index = radiogrp_get_selected((RadioGroupGetSelView *)this);
    ctrl_id = ctrl_get_id((ControlIdView *)this);
    radiogrp_fire_callback((RadioGroupClickView *)this,ctrl_id,sel_index);
  }
  return;
}
#undef wnd_active_child

/* 005d9b86 auto */
#define radio_disabled_color_index (*(byte *)((u8 *)&g.d_00637e8c))
#define radio_disabled_rgb_set (*(char *)((u8 *)&g.d_006386fb))
#define radio_shadow_color_index (*(byte *)((u8 *)&g.d_00637e80))
#define radio_shadow_dx (*(byte *)((u8 *)&g.d_00637e84))
#define radio_shadow_dy (*(byte *)((u8 *)&g.d_00637e88))
#define radio_text_color_index (*(byte *)((u8 *)&g.d_00637e7c))
#define radio_text_rgb_set (*(char *)((u8 *)&g.d_006386f7))
#define rect (*(tagRECT *)(frame_ + FRAME_OFF(0)))
#define bitmap (*(HBITMAP *)(frame_ + FRAME_OFF(16)))
#define block (*(iptr *)(frame_ + FRAME_OFF(20)))
#define ps (*(tagPAINTSTRUCT *)(frame_ + FRAME_OFF(24)))
#define old_font (*(HGDIOBJ *)(frame_ + FRAME_OFF(88)))
#define bmp_size (*(tagSIZE *)(frame_ + FRAME_OFF(92)))
#define remaining (*(int *)(frame_ + FRAME_OFF(100)))
#define hdc (*(HDC *)(frame_ + FRAME_OFF(104)))
#define underline_end (*(int *)(frame_ + FRAME_OFF(108)))
#define next_index (*(int *)(frame_ + FRAME_OFF(112)))
#define green (*(i8 (*)[4])(frame_ + FRAME_OFF(116)))
#define underline_start (*(int *)(frame_ + FRAME_OFF(120)))
#define item (*(iptr *)(frame_ + FRAME_OFF(124)))
#define box_left (*(int *)(frame_ + FRAME_OFF(128)))
#define box_top (*(int *)(frame_ + FRAME_OFF(132)))
#define box_right (*(int *)(frame_ + FRAME_OFF(136)))
#define box_bottom (*(int *)(frame_ + FRAME_OFF(140)))
#define brush (*(HBRUSH *)(frame_ + FRAME_OFF(144)))
#define red (*(i8 (*)[4])(frame_ + FRAME_OFF(148)))
#define blue (*(i8 (*)[4])(frame_ + FRAME_OFF(152)))
#define group (*(RadioGroupItemsView * *)(frame_ + FRAME_OFF(156)))
#define font_data (*(i32 * *)(frame_ + FRAME_OFF(160)))
#define text_rect (*(tagRECT *)(frame_ + FRAME_OFF(164)))
#define prefix (*(char (*)[128])(frame_ + FRAME_OFF(180)))
i32 __stdcall radiogrp_item_wndproc(HWND hwnd,uint msg,WPARAM wparam,LPARAM lparam)

{
  char nav_enabled;
  int items;
  iptr selected;
  iptr height;
  uint color_index;
  WndPaletteView *pCVar6;
  GamePalette *pCVar7;
  size_t len;
  WndBase *pCVar9;
  int value;
  iptr parent;
  HWND pHVar13;
  WndKeyNavView *pCVar14;
  iptr items2;
  i32 ctrl_id;
  iptr items3;
  i32 result;
  i8 *red_out;
  i8 *green_out;
  tagRECT *draw_rect;
  RECT *pRVar20;
  i8 *blue_out;
  UINT UVar22;
  BOOL BVar23;
  i8 frame_[FRAME_OFF(312)] __attribute__((aligned(8)));  /* original stack frame */
  
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
        pCVar6 = (WndPaletteView *)ctrl_get_parent((Control *)group);
        pCVar7 = (GamePalette *)wnd_get_palette(pCVar6);
        palette_get_entry(pCVar7,color_index,(iptr)red_out,(iptr)green_out,(iptr)blue_out);
        SetTextColor(hdc,(uint)CONCAT12(blue[0],CONCAT11(green[0],red[0])));
        UVar22 = 0x24;
        draw_rect = &rect;
        len = _strlen((char *)(item + 0x1c));
        DrawTextA(hdc,(LPCSTR)(item + 0x1c),len,draw_rect,UVar22);
        OffsetRect(&rect,-(uint)radio_shadow_dx,-(uint)radio_shadow_dy);
      }
      if (*(int *)(item + 0x18) == 1) {
        pCVar9 = (WndBase *)ctrl_get_parent((Control *)group);
        value = wnd_get_window(pCVar9);
        if (*(int *)(value + 0x40) == 8) {
          if (radio_text_color_index == 0) {
            SetTextColor(hdc,0);
          }
          else {
            blue_out = blue;
            green_out = green;
            red_out = red;
            color_index = (uint)radio_text_color_index;
            pCVar6 = (WndPaletteView *)ctrl_get_parent((Control *)group);
            pCVar7 = (GamePalette *)wnd_get_palette(pCVar6);
            parent = palette_get_logpalette(pCVar7);
            palette_get_entry_rgb(parent,color_index,(iptr)red_out,(iptr)green_out,(iptr)blue_out);
            SetTextColor(hdc,(uint)CONCAT12(blue[0],CONCAT11(green[0],red[0])));
          }
        }
        else if (radio_text_rgb_set == '\0') {
          SetTextColor(hdc,0);
        }
        else {
          SetTextColor(hdc,(uint)CONCAT12(radio_text_rgb_b,CONCAT11(radio_text_rgb_g,radio_text_rgb_r)));
        }
      }
      else if (*(int *)(item + 0x18) == 0) {
        pCVar9 = (WndBase *)ctrl_get_parent((Control *)group);
        value = wnd_get_window(pCVar9);
        if (*(int *)(value + 0x40) == 8) {
          if (radio_disabled_color_index == 0) {
            SetTextColor(hdc,0x404040);
          }
          else {
            blue_out = blue;
            green_out = green;
            red_out = red;
            color_index = (uint)radio_disabled_color_index;
            pCVar6 = (WndPaletteView *)ctrl_get_parent((Control *)group);
            pCVar7 = (GamePalette *)wnd_get_palette(pCVar6);
            parent = palette_get_logpalette(pCVar7);
            palette_get_entry_rgb(parent,color_index,(iptr)red_out,(iptr)green_out,(iptr)blue_out);
            SetTextColor(hdc,(uint)CONCAT12(blue[0],CONCAT11(green[0],red[0])));
          }
        }
        else if (radio_disabled_rgb_set == '\0') {
          SetTextColor(hdc,0x404040);
        }
        else {
          SetTextColor(hdc,(uint)CONCAT12(radio_disabled_rgb_b,CONCAT11(radio_disabled_rgb_g,radio_disabled_rgb_r)));
        }
      }
      UVar22 = 0x24;
      draw_rect = &rect;
      len = _strlen((char *)(item + 0x1c));
      DrawTextA(hdc,(LPCSTR)(item + 0x1c),len,draw_rect,UVar22);
      if (*(int *)(item + 0xa0) != -1) {
        crt_strcpy(prefix,item + 0x1c);
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
          UVar22 = 0x424;
          draw_rect = &text_rect;
          len = _strlen(prefix);
          DrawTextA(hdc,prefix,len,draw_rect,UVar22);
          underline_start = text_rect.right - 1;
        }
        crt_strcpy(prefix,item + 0x1c);
        prefix[*(int *)(item + 0xa0) + 1] = '\0';
        text_rect.left = rect.left;
        text_rect.top = rect.top;
        text_rect.right = rect.right;
        text_rect.bottom = rect.bottom;
        UVar22 = 0x424;
        draw_rect = &text_rect;
        len = _strlen(prefix);
        DrawTextA(hdc,prefix,len,draw_rect,UVar22);
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
      pHVar13 = GetFocus();
      if (pHVar13 != hwnd) {
        return 0;
      }
    }
    else if (msg != 7) {
      if (msg == 8) {
        wnd_redraw_client(hwnd);
        return 0;
      }
      goto switchD_005dab35_default;
    }
    pCVar14 = (WndKeyNavView *)ctrl_get_parent((Control *)group);
    nav_enabled = wnd_keyboard_nav_enabled(pCVar14);
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
            BVar23 = 0;
            pRVar20 = (RECT *)0x0;
            value = radiogrp_get_selected((RadioGroupGetSelView *)group);
            items = radiogrp_get_items(group);
            InvalidateRect(*(HWND *)(items + value * 0xa4),pRVar20,BVar23);
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
      if (msg != 0x100) goto switchD_005dab35_default;
      if (wparam == 9) {
        pHVar13 = GetParent(hwnd);
        SendMessageA(pHVar13,msg,wparam,lparam);
      }
      else {
        if (wparam == 0x20) {
          pCVar14 = (WndKeyNavView *)ctrl_get_parent((Control *)group);
          nav_enabled = wnd_keyboard_nav_enabled(pCVar14);
          if (nav_enabled != '\0') {
            SendMessageA(hwnd,0x201,0,0);
            SendMessageA(hwnd,0x202,0,0);
            return 0;
          }
        }
        if ((((wparam == 0x27) || (wparam == 0x28)) || (wparam == 0x66)) || (wparam == 0x62)) {
          pCVar14 = (WndKeyNavView *)ctrl_get_parent((Control *)group);
          nav_enabled = wnd_keyboard_nav_enabled(pCVar14);
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
            BVar23 = 0;
            pRVar20 = (RECT *)0x0;
            value = radiogrp_get_selected((RadioGroupGetSelView *)group);
            items2 = radiogrp_get_items(group);
            InvalidateRect(*(HWND *)(items2 + value * 0xa4),pRVar20,BVar23);
            radiogrp_set_selected((RadioGroupSetSelView *)group,next_index);
            BVar23 = 0;
            pRVar20 = (RECT *)0x0;
            value = radiogrp_get_items(group);
            InvalidateRect(*(HWND *)(value + next_index * 0xa4),pRVar20,BVar23);
            parent = ctrl_get_parent((Control *)group);
            wnd_set_active_child(parent);
            result = radiogrp_get_selected((RadioGroupGetSelView *)group);
            ctrl_id = ctrl_get_id((ControlIdView *)group);
            radiogrp_fire_callback((RadioGroupClickView *)group,ctrl_id,result);
            return 0;
          }
        }
        if (((wparam == 0x26) || (wparam == 0x25)) || ((wparam == 0x68 || (wparam == 100)))) {
          pCVar14 = (WndKeyNavView *)ctrl_get_parent((Control *)group);
          nav_enabled = wnd_keyboard_nav_enabled(pCVar14);
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
            BVar23 = 0;
            pRVar20 = (RECT *)0x0;
            value = radiogrp_get_selected((RadioGroupGetSelView *)group);
            items3 = radiogrp_get_items(group);
            InvalidateRect(*(HWND *)(items3 + value * 0xa4),pRVar20,BVar23);
            radiogrp_set_selected((RadioGroupSetSelView *)group,next_index);
            BVar23 = 0;
            pRVar20 = (RECT *)0x0;
            value = radiogrp_get_items(group);
            InvalidateRect(*(HWND *)(value + next_index * 0xa4),pRVar20,BVar23);
            parent = ctrl_get_parent((Control *)group);
            wnd_set_active_child(parent);
            result = radiogrp_get_selected((RadioGroupGetSelView *)group);
            ctrl_id = ctrl_get_id((ControlIdView *)group);
            radiogrp_fire_callback((RadioGroupClickView *)group,ctrl_id,result);
            return 0;
          }
        }
        pHVar13 = GetParent(hwnd);
        SendMessageA(pHVar13,msg,wparam,lparam);
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
            BVar23 = 0;
            pRVar20 = (RECT *)0x0;
            value = radiogrp_get_selected((RadioGroupGetSelView *)group);
            items = radiogrp_get_items(group);
            InvalidateRect(*(HWND *)(items + value * 0xa4),pRVar20,BVar23);
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
switchD_005dab35_default:
      result = ctrl_default_wndproc(hwnd,msg,wparam,lparam);
      return result;
    }
  }
  return 0;
}
#undef radio_disabled_color_index
#undef radio_disabled_rgb_set
#undef radio_shadow_color_index
#undef radio_shadow_dx
#undef radio_shadow_dy
#undef radio_text_color_index
#undef radio_text_rgb_set
#undef rect
#undef bitmap
#undef block
#undef ps
#undef old_font
#undef bmp_size
#undef remaining
#undef hdc
#undef underline_end
#undef next_index
#undef green
#undef underline_start
#undef item
#undef box_left
#undef box_top
#undef box_right
#undef box_bottom
#undef brush
#undef red
#undef blue
#undef group
#undef font_data
#undef text_rect
#undef prefix

/* 005dab5a auto */
#define class_name (*(CHAR (*)[52])(frame_ + FRAME_OFF(0)))
i32 __cdecl ctrl_hwnd_is_radio(HWND hwnd)

{
  char *_Str1;
  iptr cmp;
  iptr block;
  char *_Str2;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  GetClassNameA(hwnd,class_name,0x32);
  _Str2 = s_MSCONTROLCLASS_00638768;
  _Str1 = __strupr(class_name);
  cmp = _strcmp(_Str1,_Str2);
  if ((cmp == 0) && (block = wnd_from_hwnd(hwnd), *(int *)(block + 0x2c) == 3)) {
    return 1;
  }
  return 0;
}
#undef class_name

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
void __thiscall radiogrp_fire_callback(RadioGroupClickView *this,i32 ctrl_id,i32 index)

{
  if (this->on_select != 0) {
    (*(code *)this->on_select)(ctrl_id,index);
  }
  return;
}

/* 005dad80 auto */
void __thiscall radiogrp_fire_dblclick(RadioGroupDblClickView *this,i32 ctrl_id,i32 index)

{
  if (this->on_dblclick != 0) {
    (*(code *)this->on_dblclick)(ctrl_id,index);
  }
  return;
}

/* 005dadc0 auto */
void __thiscall radiogrp_fire_rclick(RadioGroupRClickView *this,i32 ctrl_id,i32 index)

{
  if (this->on_rclick != 0) {
    (*(code *)this->on_rclick)(ctrl_id,index);
  }
  return;
}

/* 005db0d0 auto */
#define min_pos (*(int *)(frame_ + FRAME_OFF(4)))
#define max_pos (*(int *)(frame_ + FRAME_OFF(8)))
void __thiscall scrollbar_set_page_size(Control *this,u32 page_size)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  scrollbar_get_ctl_range(this,(iptr)&min_pos,(iptr)&max_pos);
  if ((int)page_size <= max_pos - min_pos) {
    this->on_select = page_size;
  }
  return;
}
#undef min_pos
#undef max_pos

/* 005db110 auto */
void __thiscall scrollbar_get_ctl_range(Control *this,iptr min_out,iptr max_out)

{
  scrollbar_hwnd_get_range(this->hwnd,min_out,max_out);
  return;
}

/* 005ea7d7 auto */
#define ctrl (*(ControlNextView * *)(frame_ + FRAME_OFF(0)))
i32 __cdecl ctrl_list_find_by_hwnd(int hwnd,ControlNextView *list)

{
  int ctrl_hwnd;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  ctrl = list;
  while( true ) {
    if (ctrl == (ControlNextView *)0x0) {
      return 0;
    }
    ctrl_hwnd = control_get_hwnd((ControlHwndView *)ctrl);
    if (ctrl_hwnd == hwnd) break;
    ctrl = (ControlNextView *)control_get_next(ctrl);
  }
  return ctrl;
}
#undef ctrl

/* 005eac6d auto */
#define ctrl (*(ControlNextView * *)(frame_ + FRAME_OFF(0)))
i32 __cdecl ctrl_list_find_type11_hwnd(ControlNextView *list)

{
  int ctrl_type;
  i32 hwnd;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
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
#undef ctrl

/* 005eacc0: written by hand in src/game/retvals.c */

/* 005eb2f0 auto */
void __thiscall edit_fire_maxtext_callback(EditMaxTextView *this)

{
  if (this->on_maxtext != 0) {
    (*(code *)this->on_maxtext)(this->control_id);
  }
  return;
}

/* 005eb330 auto */
void __thiscall edit_fire_change_callback(EditChangeView *this)

{
  if (this->on_change != 0) {
    (*(code *)this->on_change)(this->control_id);
  }
  return;
}

/* 005eb3ed auto */
#define key_code (*(uint *)(frame_ + FRAME_OFF(0)))
uint __cdecl input_map_vkey(uint vkey)

{
  int key_down;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  key_code = *(uint *)(&input_vkey_map_table + (vkey & 0xff) * 4);
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
#undef key_code

/* 005eb447: written by hand in src/game/fixups.c */

/* 005ecef0 auto */
uint __cdecl input_shift_key_down(void)

{
  SHORT SVar1;
  
  SVar1 = GetKeyState(0x10);
  return (uint)(((int)SVar1 & 0x8000U) != 0);
}

/* 005ecf20 auto */
uint __cdecl input_ctrl_key_down(void)

{
  SHORT SVar1;
  
  SVar1 = GetKeyState(0x11);
  return (uint)(((int)SVar1 & 0x8000U) != 0);
}

/* 005f0620 auto */
/* Library Function - Single Match
    protected: struct _CRT_CRITICAL_SECTION * __thiscall ios::lockptr(void)
   
   Library: Visual Studio 1998 Debug */

int __thiscall ddctrl_get_rect(void *this)

{
  return (int)this + 0x38;
}

/* 005f0f05 auto */
#define ddctrl_current_target (*(iptr *)((u8 *)&g.d_00639dc8))
void __cdecl ddctrl_set_msg_target(iptr target)

{
  ddctrl_current_target = target;
  return;
}
#undef ddctrl_current_target

/* 005f130f auto */
i32 __thiscall ddctrl_dispatch_msg(DDControl *this,int msg,int x,int y)

{
  char handled;
  i32 result;
  
  handled = ddctrl_dispatch_to_children(this,msg,x,y);
  if (handled == '\0') {
    ddctrl_set_msg_target((iptr)this);
    if ((msg == 0x100) && (this->is_active != '\0')) {
      (*((code **)(this->vtable))[6])(x);
      result = 1;
    }
    else if ((msg == 0x102) && (this->is_active != '\0')) {
      (*((code **)(this->vtable))[7])(x);
      result = 1;
    }
    else if (msg == 0xfff0) {
      (*((code **)(this->vtable))[9])(x,y);
      result = 1;
    }
    else if ((((x < (int)this->rect_left) || (y < (int)this->rect_top)) ||
             ((int)this->rect_right < x)) || ((int)this->rect_bottom < y)) {
      result = 0;
    }
    else {
      switch(msg) {
      case 0x200:
        (*((code **)(this->vtable))[4])(x,y);
        break;
      case 0x201:
        (*((code **)(this->vtable))[0])(this,x,y);
        break;
      case 0x202:
        (*((code **)(this->vtable))[2])(x,y);
        break;
      case 0x203:
        (*((code **)(this->vtable))[5])(x,y);
        break;
      case 0x204:
        (*((code **)(this->vtable))[1])(x,y);
        break;
      case 0x205:
        (*((code **)(this->vtable))[3])(x,y);
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
uptr __thiscall ddctrl_get_parent_window(DDControlParentView *this)

{
  uptr parent_wnd;
  uptr result;
  
  if (this->parent_wnd == 0) {
    if (this->parent_control == 0) {
      result = 0;
    }
    else {
      parent_wnd = ddctrl_get_parent_window((DDControlParentView *)this->parent_control);
      this->parent_wnd = parent_wnd;
      result = this->parent_wnd;
    }
  }
  else {
    result = this->parent_wnd;
  }
  return result;
}

/* 005f15a9 auto */
void __thiscall ddctrl_on_paint_default(DDControlParentView *this,i32 paint_arg)

{
  int parent_wnd;
  
  parent_wnd = ddctrl_get_parent_window(this);
  if (parent_wnd == 0) {
    __assert(s_GetParentGameWin___00639e24,s_D__Ss_Smeds32_ddcntrl_cpp_00639e08,0xd8);
  }
  return;
}

/* 005f1622 auto */
void __thiscall ddctrl_activate(DDControlActivateView *this)

{
  if (this->is_active == '\0') {
    if (this->parent_control == 0) {
      ddwin_deactivate_controls(this->owner_ddwin);
    }
    else {
      ddctrl_deactivate_children(this->parent_control);
    }
    this->is_active = 1;
    (*((code **)(this->vtable))[8])(1);
  }
  return;
}

/* 005f1683 auto */
void __thiscall ddctrl_deactivate(void *this)

{
  if (*(char *)((int)this + 0x34) != '\0') {
    ddctrl_deactivate_children(this);
    *(i8 *)((int)this + 0x34) = 0;
    (*((code **)(*(int **)this))[8])(this,0);
  }
  return;
}

/* 005f179c auto */
void __thiscall ddctrl_on_lbuttondown(DDControlActivateView *this,i32 x,i32 y)

{
  ddctrl_activate(this);
  return;
}

/* 005f17bc auto */
void __thiscall ddctrl_on_rbuttondown_nop(void *this,i32 x,i32 y)

{
  return;
}

/* 005f17d4 auto */
void __thiscall ddctrl_on_lbuttonup(DdctrlOnLbuttonupView *this,i32 x,i32 y)

{
  if (this->on_lbutton_up != 0) {
    (*(code *)this->on_lbutton_up)(this->control_id,x,y);
  }
  return;
}

/* 005f1811 auto */
void __thiscall ddctrl_on_rbuttonup(DdctrlOnRbuttonupView *this,i32 x,i32 y)

{
  if (this->on_rbutton_up != 0) {
    (*(code *)this->on_rbutton_up)(this->control_id,x,y);
  }
  return;
}

/* 005f184e auto */
void __thiscall ddctrl_on_mousemove(DdctrlOnMousemoveView *this,i32 x,i32 y)

{
  if (this->on_mouse_move != 0) {
    (*(code *)this->on_mouse_move)(this->control_id,x,y);
  }
  return;
}

/* 005f188b auto */
void __thiscall ddctrl_on_dblclick(DdctrlOnDblclickView *this,i32 x,i32 y)

{
  if (this->on_dblclick != 0) {
    (*(code *)this->on_dblclick)(this->control_id,x,y);
  }
  return;
}

/* 005f18c8 auto */
void __thiscall ddctrl_on_msg_fff0_nop(void *this,i32 x,i32 y)

{
  return;
}

/* 005f18e0 auto */
void __thiscall ddctrl_on_keydown_nop(void *this,i32 key)

{
  return;
}

/* 005f18f8 auto */
void __thiscall ddctrl_on_char_nop(void *this,i32 ch)

{
  return;
}

/* 005f1910 auto */
void __thiscall ddctrl_on_set_active_nop(void *this,i32 active)

{
  return;
}

/* 005f19a6 auto */
#define child (*(i32 *)(frame_ + FRAME_OFF(0)))
void __thiscall ddctrl_deactivate_children(void *this)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  child = ptrlist_first((PtrList *)((int)this + 0x10));
  while (child != 0) {
    ddctrl_deactivate(child);
    child = ptrlist_next((PtrList *)((int)this + 0x10));
  }
  return;
}
#undef child

/* 005f1a40 auto */
#define child (*(DDControl * *)(frame_ + FRAME_OFF(0)))
i8 __thiscall ddctrl_dispatch_to_children(DDControl *this,int msg,int x,int y)

{
  int *child_rect;
  int handled;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((this->hover_child != 0) && (msg == 0x200)) {
    child_rect = (int *)ddctrl_get_rect((void *)this->hover_child);
    if ((x < *child_rect) ||
       (((child_rect[2] < x || (y < child_rect[1])) || (child_rect[3] < y)))) {
      ddctrl_dispatch_msg((DDControl *)this->hover_child,0xfff0,x,y);
      this->hover_child = 0;
    }
  }
  child = (DDControl *)ptrlist_first((PtrList *)(this->child_controls));
  while( true ) {
    if (child == (DDControl *)0x0) {
      return 0;
    }
    handled = ddctrl_dispatch_msg(child,msg,x,y);
    if (handled != 0) break;
    child = (DDControl *)ptrlist_next((PtrList *)(this->child_controls));
  }
  if (msg == 0x200) {
    this->hover_child = (uptr)child;
  }
  return 1;
}
#undef child

/* 00601300: written by hand in src/crt/locale.c */

/* 00601560: written by hand in src/crt/locale.c */

/* 00606330: written by hand in src/crt/locale.c */

/* 00606690: written by hand in src/crt/locale.c */
