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
#define local_10 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(undefined1 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(8)))
Control * __thiscall button_ctor(Control *this)

{
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  ctrl_base_ctor(this);
  this->hotkey_char = '\0';
  this->on_select = 0xffffffff;
  return this;
}
#undef local_10
#undef puStack_c
#undef local_8

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
undefined4 __thiscall ctrl_base_dtor(ControlBase *this)

{
  undefined4 uVar1;
  
  if (this->owner_wnd != 0) {
    wnd_remove_control((WndControlRemoveView *)this->owner_wnd,this->control_id);
  }
  this->next_control = 0;
  uVar1 = ctrl_destroy_hwnd((iptr)this);
  return uVar1;
}

/* 0040f570 auto */
#define uStack_10 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(undefined1 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(8)))
undefined4 __thiscall ctrl_dtor(Control *this)

{
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  if (this->hwnd != 0) {
    ctrl_destroy(this);
  }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_0040f5c3 */ { ctrl_base_dtor(*(ControlBase **)((iptr)&this)); }
  return uStack_10;
}
#undef uStack_10
#undef puStack_c
#undef local_8

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
          (Control *this,iptr param_1,undefined4 param_2,iptr param_3,iptr param_4)

{
  u32 uVar1;
  
  if (this->hwnd != 0) {
    ctrl_destroy(this);
  }
  this->font = (u32)button_default_font;
  ctrl_init(this,param_1,6,param_2,param_3);
  this->on_click = 0;
  uVar1 = button_create_hwnd(param_3,(iptr)this,param_4,1,this->font);
  this->hwnd = uVar1;
  this->is_enabled = 1;
  return;
}

/* 0040f730 auto */
void __thiscall
ctrl_init(Control *this,iptr param_1,u32 param_2,u32 param_3,iptr param_4)

{
  this->parent = param_1;
  this->ctrl_type = param_2;
  this->ctrl_id = param_3;
  this->rect_left = *(u32 *)param_4;
  this->rect_top = *(u32 *)(param_4 + 4);
  this->rect_right = *(u32 *)(param_4 + 8);
  this->rect_bottom = *(u32 *)(param_4 + 0xc);
  this->next_ctrl = 0;
  this->hwnd = 0;
  this->wants_initial_focus = '\0';
  wnd_append_control((WndControlListView *)param_1,(iptr)this);
  return;
}

/* 0040f7d0 auto */
void __thiscall ctrl_set_default_button(Control *this)

{
  iptr iVar1;
  
  iVar1 = ctrl_get_parent(this);
  *(Control **)(iVar1 + 0xbc) = this;
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
  iptr iVar1;
  
  iVar1 = ctrl_get_parent(this);
  *(Control **)(iVar1 + 0xc0) = this;
  return;
}

/* 0040f880 auto */
void __thiscall button_set_callback(Control *this,iptr param_1)

{
  this->on_click = param_1;
  return;
}

/* 0040f8b0 auto */
#define local_10 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(undefined1 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(8)))
Control * __thiscall checkbox_elem_ctor(Control *this)

{
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  ctrl_base_ctor(this);
  return this;
}
#undef local_10
#undef puStack_c
#undef local_8

/* 0040f930 auto */
#define uStack_10 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(undefined1 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(8)))
void __thiscall checkbox_dtor(Checkbox *this)

{
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  if (this->hwnd != 0) {
    checkbox_destroy_hwnd(this->hwnd);
  }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_0040f98a */ { ctrl_base_dtor(*(ControlBase **)((iptr)&this)); }
  return;
}
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0040f9d0 auto */
#define local_14 (*(undefined1 (*)[16])(frame_ + FRAME_OFF(4)))
void __thiscall
checkbox_create
          (Control *this,iptr param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4
          ,iptr param_5)

{
  u32 uVar1;
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  this->font = (u32)checkbox_default_font;
  checkbox_calc_rect(param_5,param_3,param_4,(iptr)local_14,this->font);
  if (this->hwnd != 0) {
    ctrl_destroy(this);
  }
  ctrl_init(this,param_1,2,param_2,(iptr)local_14);
  this->is_enabled = 0;
  this->on_select = 1;
  this->on_click = 0;
  uVar1 = checkbox_create_hwnd((iptr)local_14,(iptr)this,param_5,1);
  this->hwnd = uVar1;
  return;
}
#undef local_14

/* 0040faa0 auto */
void __thiscall checkbox_set_callback(CheckboxCallbackSetView *this,iptr param_1)

{
  this->on_toggle = param_1;
  return;
}

/* 0040fad0 auto */
void __thiscall checkbox_set_checked(Control *this,u32 param_1)

{
  this->on_click = param_1;
  return;
}

/* 0040fb00 auto */
#define local_10 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(undefined1 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(8)))
Control * __thiscall scrollbar_ctor(Control *this)

{
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  ctrl_base_ctor(this);
  this->on_select = 1;
  this->is_enabled = 0;
  this->on_click = 0;
  return this;
}
#undef local_10
#undef puStack_c
#undef local_8

/* 0040fbb0 auto */
#define uStack_10 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(undefined1 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(8)))
void __thiscall scrollbar_dtor(Control *this)

{
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  if (this->hwnd != 0) {
    scrollbar_destroy_hwnd(this->hwnd);
  }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_0040fc0a */ { ctrl_base_dtor(*(ControlBase **)((iptr)&this)); }
  return;
}
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0040fc50 auto */
void __thiscall
scrollbar_create
          (Control *this,iptr param_1,iptr param_2,iptr param_3,undefined4 param_4)

{
  u32 uVar1;
  
  if (this->hwnd != 0) {
    ctrl_destroy(this);
  }
  ctrl_init(this,param_1,8,param_2,param_3);
  uVar1 = scrollbar_create_hwnd(param_3,(iptr)this,param_4,1);
  this->hwnd = uVar1;
  scrollbar_hwnd_set_range(this->hwnd,1,100);
  this->font = 1;
  return;
}

/* 0040fcf0 auto */
void __thiscall scrollbar_set_pos(C_0040f380_40 *this,iptr param_1)

{
  this->scroll_pos = param_1;
  scrollbar_hwnd_set_pos(this->hwnd,param_1);
  return;
}

/* 0040fd40 auto */
void __thiscall
scrollbar_set_range(Control *this,undefined4 param_1,undefined4 param_2)

{
  scrollbar_hwnd_set_range(this->hwnd,param_1,param_2);
  return;
}

/* 0040fd80 auto */
void __thiscall scrollbar_set_callback(Control *this,iptr param_1)

{
  this->is_enabled = param_1;
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
#define local_10 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(undefined1 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(8)))
C_0040f380_48 * __thiscall edit_ctor(C_0040f380_48 *this)

{
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  ctrl_base_ctor((Control *)this);
  this->on_click = 0;
  this->is_enabled = 0;
  this->items_handle = 0;
  this->on_select = 0;
  *(undefined1 *)&this->font = 0;
  *(undefined1 *)((int)&this->font + 1) = 0;
  return this;
}
#undef local_10
#undef puStack_c
#undef local_8

/* 00418870 auto */
#define uStack_10 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(undefined1 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(8)))
void __thiscall edit_dtor(Control *this)

{
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  if (this->hwnd != 0) {
    edit_hwnd_cleanup_stub(this->hwnd);
  }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_004188ca */ { ctrl_base_dtor(*(ControlBase **)((iptr)&this)); }
  return;
}
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00418910 auto */
void __thiscall
edit_create
          (EditControl *this,iptr param_1,undefined4 param_2,iptr param_3,iptr param_4)

{
  u32 uVar1;
  
  if (this->hwnd != 0) {
    ctrl_destroy((Control *)this);
  }
  this->edit_font = (u32)ctrl_default_font;
  ctrl_init((Control *)this,param_1,4,param_2,param_3);
  uVar1 = edit_create_window(param_3,(iptr)this,1,1,this->edit_font);
  this->hwnd = uVar1;
  hwnd_send_settext(this->hwnd,param_4);
  return;
}

/* 004189c0 auto */
void __thiscall edit_set_max_len(EditMaxLenView *this,undefined4 param_1)

{
  edit_hwnd_limit_text(this->hwnd,param_1);
  return;
}

/* 00418a00 auto */
void __thiscall edit_set_callback(EditCallbackSetView *this,iptr param_1)

{
  this->on_change = param_1;
  return;
}

/* 00418a30 auto */
void __thiscall ctrl_set_text(ControlTextView *this,iptr param_1)

{
  hwnd_send_settext(this->hwnd,param_1);
  return;
}

/* 00418a70 auto */
void __thiscall ctrl_get_text(ControlTextView *this,iptr param_1)

{
  hwnd_get_text(this->hwnd,param_1);
  return;
}

/* 00418ab0 auto */
#define local_10 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(undefined1 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(8)))
Control * __thiscall combo_ctor(Control *this)

{
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  ctrl_base_ctor(this);
  this->on_click = 0;
  this->on_select = 0;
  return this;
}
#undef local_10
#undef puStack_c
#undef local_8

/* 00418b50 auto */
#define uStack_10 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(undefined1 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(8)))
void __thiscall combo_dtor(C_00418b50 *this)

{
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  if (this->hwnd != 0) {
    combo_hwnd_cleanup_stub(this->hwnd);
  }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_00418baa */ { ctrl_base_dtor(*(ControlBase **)((iptr)&this)); }
  return;
}
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00418bf0 auto */
void __thiscall
combo_create(Control *this,iptr param_1,undefined4 param_2,iptr param_3)

{
  u32 uVar1;
  
  if (this->hwnd != 0) {
    ctrl_destroy(this);
  }
  ctrl_init(this,param_1,10,param_2,param_3);
  uVar1 = combo_create_window(param_3,(iptr)this,1);
  this->hwnd = uVar1;
  this->is_enabled = 0;
  return;
}

/* 00418c70 auto */
void __thiscall combo_set_font(ComboBoxFontView *this,iptr param_1)

{
  undefined4 uVar1;
  
  uVar1 = font_get_hfont((GameFont *)param_1);
  combo_hwnd_set_font(this->hwnd,uVar1);
  return;
}

/* 00418ce0 auto */
void __thiscall combo_add_string(ComboBoxAddView *this,iptr param_1)

{
  combo_hwnd_add_string(this->hwnd,param_1);
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
undefined4 __thiscall combo_get_cur_sel(ComboBoxGetSelView *this)

{
  undefined4 uVar1;
  
  uVar1 = combo_hwnd_get_cur_sel(this->hwnd);
  return uVar1;
}

/* 00418d90 auto */
void __thiscall combo_set_cur_sel(ComboBoxSetSelView *this,iptr param_1)

{
  combo_hwnd_set_cur_sel(this->hwnd,param_1);
  return;
}

/* 00418dd0 auto */
void __thiscall combo_set_callback(ComboBoxCallbackSetView *this,iptr param_1)

{
  this->on_select = param_1;
  return;
}

/* 00418e00 auto */
#define local_10 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(undefined1 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(8)))
Control * __thiscall checkbox_ctor(Control *this)

{
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  ctrl_base_ctor(this);
  this->on_click = 0;
  this->on_select = 0;
  return this;
}
#undef local_10
#undef puStack_c
#undef local_8

/* 00418ea0 auto */
#define uStack_10 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(undefined1 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(8)))
void __thiscall listbox_dtor(ListBoxControl *this)

{
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  if (this->hwnd != 0) {
    listbox_hwnd_cleanup_stub(this->hwnd);
  }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_00418efa */ { ctrl_base_dtor(*(ControlBase **)((iptr)&this)); }
  return;
}
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00418f40 auto */
void __thiscall
listbox_create(Control *this,iptr param_1,undefined4 param_2,iptr param_3)

{
  u32 uVar1;
  
  if (this->hwnd != 0) {
    ctrl_destroy(this);
  }
  this->font = (u32)listbox_default_font;
  ctrl_init(this,param_1,7,param_2,param_3);
  uVar1 = listbox_create_hwnd(param_3,(iptr)this,1,0,this->font);
  this->hwnd = uVar1;
  this->is_enabled = 0;
  return;
}

/* 00418fe0 auto */
void __thiscall listbox_set_font(ListBoxFontView *this,iptr param_1)

{
  undefined4 uVar1;
  
  uVar1 = font_get_hfont((GameFont *)param_1);
  listbox_hwnd_set_font(this->hwnd,uVar1);
  return;
}

/* 00419020 auto */
void __thiscall listbox_add_string(ListBoxAddView *this,iptr param_1)

{
  listbox_hwnd_add_string(this->hwnd,param_1);
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
void __thiscall radiogrp_enable_item(RadioGroupEnableView *this,iptr param_1)

{
  if ((param_1 < (int)this->item_count) && (-1 < param_1)) {
    *(undefined4 *)(this->items + 0x18 + param_1 * 0xa4) = 1;
    radiogrp_hwnd_invalidate(*(undefined4 *)(this->items + param_1 * 0xa4));
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
void __thiscall radiogrp_disable_item(RadioGroupDisableView *this,iptr param_1)

{
  if ((param_1 < (int)this->item_count) && (-1 < param_1)) {
    if (this->selected_index == param_1) {
      this->selected_index = 0xffffffff;
    }
    *(undefined4 *)(this->items + 0x18 + param_1 * 0xa4) = 0;
    radiogrp_hwnd_invalidate(*(undefined4 *)(this->items + param_1 * 0xa4));
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
void __thiscall radiogrp_set_selected(RadioGroupSetSelView *this,u32 param_1)

{
  this->selected = param_1;
  return;
}

/* 00451ac0 auto */
void __thiscall scrollbar_set_track_callback(ScrollbarTrackSetView *this,iptr param_1)

{
  this->on_track = param_1;
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
  scrollbar_ctor((Control *)&DAT_0066c728);
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
  scrollbar_dtor((Control *)&DAT_0066c728);
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
  scrollbar_ctor((Control *)&DAT_0066c768);
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
  scrollbar_dtor((Control *)&DAT_0066c768);
  return;
}

/* 00492ab0 auto */
undefined4 __thiscall edit_get_sel_end(EditSelEndView *this)

{
  undefined4 uVar1;
  
  uVar1 = edit_ctl_get_sel_end(this->hwnd);
  return uVar1;
}

/* 00492ae0 auto */
void __thiscall edit_replace_sel(Control *this,iptr param_1)

{
  edit_hwnd_replace_sel(this->hwnd,param_1);
  return;
}

/* 00492b20 auto */
void __thiscall edit_set_sel(EditSelView *this,undefined4 param_1,undefined4 param_2)

{
  edit_hwnd_set_sel(this->hwnd,param_1,param_2);
  return;
}

/* 00497d40 auto */
void __thiscall
button_create_with_callback
          (Control *this,iptr param_1,undefined4 param_2,iptr param_3,u32 param_4,iptr param_5
          )

{
  this->on_select = param_4;
  this->font = (u32)button_default_font;
  button_create(this,param_1,param_2,param_3,param_5);
  return;
}

/* 004bb3b0 auto */
Control * __thiscall ctrl_scalar_dtor(Control *this,uint param_1)

{
  ctrl_dtor(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 004bb400 auto */
Control * __thiscall edit_scalar_dtor(Control *this,uint param_1)

{
  edit_dtor(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 004bb450 auto */
Checkbox * __thiscall checkbox_scalar_dtor(Checkbox *this,uint param_1)

{
  checkbox_dtor(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 004bb4a0 auto */
RadioGroupDtorView * __thiscall radiogrp_scalar_dtor(RadioGroupDtorView *this,uint param_1)

{
  radiogrp_dtor(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 004bb4f0 auto */
Control * __thiscall scrollbar_scalar_dtor(Control *this,uint param_1)

{
  scrollbar_dtor(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 004bb5b0 auto */
void __thiscall ctrl_set_initial_focus(C_004bb5b0 *this)

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
          (EditControl *this,iptr param_1,undefined4 param_2,iptr param_3,iptr param_4,
          undefined4 param_5,undefined4 param_6)

{
  u32 uVar1;
  
  if (this->hwnd != 0) {
    ctrl_destroy((Control *)this);
  }
  this->edit_font = (u32)ctrl_default_font;
  ctrl_init((Control *)this,param_1,4,param_2,param_3);
  uVar1 = edit_create_window(param_3,(iptr)this,param_5,param_6,this->edit_font);
  this->hwnd = uVar1;
  hwnd_send_settext(this->hwnd,param_4);
  return;
}

/* 004bb6d0 auto */
void __thiscall edit_set_caret(ControlTextView *this,undefined4 param_1)

{
  edit_hwnd_set_caret(this->hwnd,param_1);
  return;
}

/* 004bb710 auto */
undefined4 __thiscall edit_get_text_end(ControlTextView *this)

{
  undefined4 uVar1;
  
  uVar1 = edit_hwnd_get_text_end(this->hwnd);
  return uVar1;
}

/* 004bb740 auto */
#define uStack_10 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(undefined1 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(8)))
void __thiscall radiogrp_dtor(RadioGroupDtorView *this)

{
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  if (this->items_handle != 0) {
    mem_handle_unlock(this->items_handle);
    radiogrp_destroy_items(this->item_count,this->items_handle);
  }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_004bb7b0 */ { ctrl_base_dtor(*(ControlBase **)((iptr)&this)); }
  return;
}
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004cffb0 auto */
undefined4 __thiscall
edit_get_line(EditLineView *this,undefined4 param_1,iptr param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  uVar1 = edit_hwnd_get_line(this->field_1c,param_1,param_2,param_3);
  return uVar1;
}

/* 005011b4 auto */
#define local_54 (*(undefined1 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_44 (*(undefined1 (*)[16])(frame_ + FRAME_OFF(20)))
#define local_34 (*(undefined4 *)(frame_ + FRAME_OFF(36)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(44)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(52)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(56)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(60)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(64)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(68)))
#define local_10 (*(undefined4 *)(frame_ + FRAME_OFF(72)))
#define local_c (*(int *)(frame_ + FRAME_OFF(76)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(80)))
void __cdecl
spritebtn_create_icon_button(iptr param_1,undefined4 param_2,SpriteButton *param_3,iptr param_4,iptr param_5)

{
  int *piVar1;
  int iVar2;
  WndPaletteView *pCVar3;
  iptr iVar4;
  int iVar5;
  undefined1 frame_[FRAME_OFF(88)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_10 = rect_width(param_5);
  local_34 = rect_height(param_5);
  spritebtn_init_from_sprite
            (param_3,param_1,param_2,*(undefined4 *)param_5,*(undefined4 *)(param_5 + 4),local_10,
             local_34,param_4,0x17);
  piVar1 = (int *)surface_get_rect((DibSurface *)&param_3->field_34);
  local_30 = *piVar1;
  local_2c = piVar1[1];
  local_28 = piVar1[2];
  local_24 = piVar1[3];
  iVar2 = rect_width((iptr)&local_30);
  iVar5 = local_30 + iVar2 / 2;
  iVar2 = sprite_width((Sprite *)param_4);
  local_8 = iVar5 - iVar2 / 2;
  iVar2 = rect_height((iptr)&local_30);
  iVar5 = local_2c + iVar2 / 2;
  iVar2 = sprite_height((Sprite *)param_4);
  local_c = iVar5 - iVar2 / 2;
  sprite_draw
            ((Sprite *)param_4,(iptr)local_44,(iptr)&param_3->field_34,local_8,local_c);
  sprite_draw
            ((Sprite *)param_4,(iptr)local_54,(iptr)(param_3->pad_50 + 0x2c),local_8 + 2,
             local_c + 2);
  gfx_draw_rect_frame((iptr)&param_3->field_34,(iptr)&local_30,10);
  gfx_draw_rect_frame((iptr)(param_3->pad_50 + 0x2c),(iptr)&local_30,10);
  local_20 = local_30;
  local_1c = local_2c;
  local_18 = local_28;
  local_14 = local_24;
  rect_deflate((iptr)&local_20,1,1);
  gfx_draw_bevel_rect((iptr)&param_3->field_34,(iptr)&local_20,0x1f,0xf);
  gfx_draw_bevel_rect((iptr)(param_3->pad_50 + 0x2c),(iptr)&local_20,0xf,10);
  rect_deflate((iptr)&local_20,1,1);
  gfx_draw_bevel_rect((iptr)&param_3->field_34,(iptr)&local_20,0x1f,0xf);
  gfx_draw_bevel_rect((iptr)(param_3->pad_50 + 0x2c),(iptr)&local_20,0xf,10);
  pCVar3 = (WndPaletteView *)ctrl_get_parent((Control *)param_3);
  iVar4 = wnd_get_palette(pCVar3);
  surface_set_palette((DibSurface *)(param_3->pad_50 + 0x2c),iVar4);
  pCVar3 = (WndPaletteView *)ctrl_get_parent((Control *)param_3);
  iVar4 = wnd_get_palette(pCVar3);
  surface_set_palette((DibSurface *)&param_3->field_34,iVar4);
  return;
}
#undef local_54
#undef local_44
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

/* 00511560 auto */
C_00511560 * __thiscall spritebtn_scalar_dtor(C_00511560 *this,uint param_1)

{
  spritebtn_dtor(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 005115b0 auto */
#define uStack_10 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(undefined1 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __thiscall spritebtn_dtor(C_00511560 *this)

{
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  (*(undefined3 *)((char *)&local_8 + 1)) = 0;
  (*(undefined1 *)((char *)&local_8 + 0)) = 2;
  if (this->hwnd != 0) {
    spritebtn_hwnd_cleanup_stub(this->hwnd);
  }
  (*(undefined1 *)((char *)&local_8 + 0)) = 1;
  /* inlined unwind funclet FUN_00511624 */ { surface_dtor((DibSurface *)(*(int *)((iptr)&this) + 0x7c)); }
  local_8 = (uint)(*(undefined3 *)((char *)&local_8 + 1)) << 8;
  /* inlined unwind funclet FUN_00511630 */ { surface_dtor((DibSurface *)(*(int *)((iptr)&this) + 0x34)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_0051163c */ { ctrl_base_dtor(*(ControlBase **)((iptr)&this)); }
  return;
}
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00511720 auto */
#define local_10 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(undefined1 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(8)))
SpriteButton * __thiscall spritebtn_ctor(SpriteButton *this)

{
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  ctrl_base_ctor((Control *)this);
  local_8 = 0;
  surface_ctor((DibSurface *)&this->on_select);
  local_8 = CONCAT31((*(undefined3 *)((char *)&local_8 + 1)),1);
  surface_ctor((DibSurface *)(this->pad_50 + 0x2c));
  this->field_c8 = '\0';
  return this;
}
#undef local_10
#undef puStack_c
#undef local_8

/* 005117f0 auto */
void __thiscall spritebtn_set_click_handler(C_005117f0 *this,iptr param_1)

{
  this->on_click = param_1;
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
void __thiscall edit_set_change_callback(EditChangeSetView *this,iptr param_1)

{
  this->on_change = param_1;
  return;
}

/* 00530ee0 auto */
#define local_14 (*(undefined1 (*)[16])(frame_ + FRAME_OFF(4)))
void __thiscall
checkbox_create_fixed
          (Control *this,iptr param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4
          ,undefined4 param_5,iptr param_6)

{
  u32 uVar1;
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  this->font = (u32)checkbox_default_font;
  checkbox_calc_rect_fixed(param_3,param_4,param_5,(iptr)local_14,this->font);
  if (this->hwnd != 0) {
    ctrl_destroy(this);
  }
  ctrl_init(this,param_1,2,param_2,(iptr)local_14);
  this->is_enabled = 0;
  this->on_select = 1;
  this->on_click = 0;
  uVar1 = checkbox_create_hwnd((iptr)local_14,(iptr)this,param_6,1);
  this->hwnd = uVar1;
  return;
}
#undef local_14

/* 00530fb0 auto */
void __thiscall checkbox_enable(C_00530fb0 *this)

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
#define local_10 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(undefined1 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(8)))
C_0040f380_48 * __thiscall radiogrp_ctor(C_0040f380_48 *this)

{
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  ctrl_base_ctor((Control *)this);
  this->items_handle = 0;
  return this;
}
#undef local_10
#undef puStack_c
#undef local_8

/* 005310a0 auto */
void __thiscall
radiogrp_create
          (RadioGroup *this,iptr param_1,undefined4 param_2,iptr param_3,u32 param_4,u32 param_5,
          iptr param_6)

{
  u32 uVar1;
  
  if (this->items_handle != 0) {
    ctrl_destroy((Control *)this);
  }
  this->radio_font = (u32)radio_default_font;
  ctrl_init((Control *)this,param_1,3,param_2,param_3);
  this->is_enabled = 0;
  this->on_click = 0;
  this->on_select = 0;
  this->font = param_5;
  this->scroll_pos = param_4;
  this->edit_font = 0;
  uVar1 = radiogrp_create_items((iptr)&this->font,param_3,param_4,(iptr)this,param_5,param_6,1,
                       this->radio_font);
  this->items_handle = uVar1;
  uVar1 = mem_handle_lock(this->items_handle);
  this->items_ptr = uVar1;
  return;
}

/* 005311b0 auto */
void __thiscall radiogrp_set_select_callback(Control *this,iptr param_1)

{
  this->is_enabled = param_1;
  return;
}

/* 005311e0 auto */
void __thiscall radiogrp_set_dblclick_callback(Control *this,iptr param_1)

{
  this->on_click = param_1;
  return;
}

/* 00551d20 auto */
/* Library Function - Single Match
    protected: char * __thiscall streambuf::egptr(void)const 
   
   Library: Visual Studio 1998 Debug */

u32 __thiscall listbox_get_count(C_00551d20 *this)

{
  return this->item_count;
}

/* 00551d50 auto */
undefined4 __thiscall listbox_get_cur_sel(ListBoxGetSelView *this)

{
  undefined4 uVar1;
  
  uVar1 = listbox_hwnd_get_cur_sel(this->hwnd);
  return uVar1;
}

/* 00551d80 auto */
void __thiscall listbox_set_cur_sel(ListBoxSetSelView *this,undefined4 param_1)

{
  listbox_hwnd_set_cur_sel(this->hwnd,param_1);
  return;
}

/* 00551dc0 auto */
void __thiscall listbox_set_dblclick_callback(ListBoxDblClickSetView *this,iptr param_1)

{
  this->on_dblclick = param_1;
  return;
}

/* 00551df0 auto */
void __thiscall listbox_set_select_callback(ListBoxSelectSetView *this,iptr param_1)

{
  this->on_select = param_1;
  return;
}

/* 005a9320 auto */
/* Library Function - Multiple Matches With Different Base Names
    public: void * __thiscall CDaoIndexFieldInfo::`vector deleting destructor'(unsigned int)
    public: void * __thiscall CDaoRelationFieldInfo::`vector deleting destructor'(unsigned int)
    public: void * __thiscall CODBCFieldInfo::`vector deleting destructor'(unsigned int)
    public: void * __thiscall CString::`vector deleting destructor'(unsigned int)
   
   Library: Visual Studio 1998 Debug */

Checkbox * __thiscall checkbox_vector_dtor(Checkbox *this,uint param_1)

{
  if ((param_1 & 2) == 0) {
    checkbox_dtor(this);
    if ((param_1 & 1) != 0) {
      operator_delete(this);
    }
  }
  else {
    FUN_005f2490(this,0x3c,this[-1].field_1c,checkbox_dtor);
    operator_delete(&this[-1].field_1c);
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

Control * __thiscall edit_vector_dtor(Control *this,uint param_1)

{
  if ((param_1 & 2) == 0) {
    edit_dtor(this);
    if ((param_1 & 1) != 0) {
      operator_delete(this);
    }
  }
  else {
    FUN_005f2490(this,0x48,this[-1].field_38,edit_dtor);
    operator_delete(&this[-1].field_38);
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

Control * __thiscall ctrl_vector_dtor(Control *this,uint param_1)

{
  if ((param_1 & 2) == 0) {
    ctrl_dtor(this);
    if ((param_1 & 1) != 0) {
      operator_delete(this);
    }
  }
  else {
    FUN_005f2490(this,0x3c,this[-1].field_38,ctrl_dtor);
    operator_delete(&this[-1].field_38);
  }
  return this;
}

/* 005a94d0 auto */
ListBoxControl * __thiscall listbox_scalar_dtor(ListBoxControl *this,uint param_1)

{
  listbox_dtor(this);
  if ((param_1 & 1) != 0) {
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
void __thiscall listbox_get_text(ListBoxTextView *this,undefined4 param_1,iptr param_2)

{
  listbox_hwnd_get_text(this->hwnd,param_1,param_2);
  return;
}

/* 005a96b0 auto */
void __thiscall listbox_get_sel_text(ListBoxSelTextView *this,iptr param_1)

{
  listbox_hwnd_get_sel_text(this->hwnd,param_1);
  return;
}

/* 005bd39e auto */
#define local_24 (*(tagMSG *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(char *)(frame_ + FRAME_OFF(32)))
int __cdecl input_poll_modifier(int param_1)

{
  SHORT SVar1;
  BOOL BVar2;
  undefined1 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = '\0';
  if (param_1 == 0x200) {
    SVar1 = GetKeyState(0x11);
    local_8 = ((int)SVar1 & 0x8000U) != 0;
  }
  else if (param_1 == 0x100) {
    SVar1 = GetKeyState(0x10);
    local_8 = ((int)SVar1 & 0x8000U) != 0;
  }
  else if (param_1 == 0x400) {
    while (BVar2 = PeekMessageA(&local_24,(HWND)0x0,0,0,1), BVar2 != 0) {
      if (((local_24.message == 0x106) || (local_24.message == 0x104)) ||
         (local_24.message == 0x105)) {
        local_8 = 1;
      }
      else {
        TranslateMessage(&local_24);
        DispatchMessageA(&local_24);
      }
    }
  }
  return (int)local_8;
}
#undef local_24
#undef local_8

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
void __cdecl ctrl_hwnd_set_focus(HWND param_1)

{
  SetFocus(param_1);
  return;
}

/* 005c90ca auto */
#define local_14 (*(tagPOINT *)(frame_ + FRAME_OFF(4)))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(HWND *)(frame_ + FRAME_OFF(16)))
void __cdecl ctrl_paint_parent_bkgnd(iptr param_1,HWND param_2)

{
  LONG LVar1;
  DibSurface *this;
  WndBase *pCVar2;
  iptr iVar3;
  iptr iVar4;
  int iVar5;
  HDC hdcSrc;
  LONG y1;
  DWORD rop;
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = GetParent(param_2);
  LVar1 = GetWindowLongA(local_8,0xc);
  if (LVar1 == 0) {
    pCVar2 = (WndBase *)GetWindowLongA(local_8,0);
    iVar5 = wnd_get_window(pCVar2);
    if (*(int *)(iVar5 + 0x14) != 0) {
      FillRect(*(HDC *)param_1,(RECT *)(param_1 + 8),*(HBRUSH *)(iVar5 + 0x14));
    }
  }
  else {
    this = (DibSurface *)GetWindowLongA(local_8,0xc);
    pCVar2 = (WndBase *)GetWindowLongA(local_8,0);
    iVar3 = wnd_get_window(pCVar2);
    local_c = surface_get_dib(this);
    local_14.x = *(int *)(param_1 + 8);
    local_14.y = *(int *)(param_1 + 0xc);
    MapWindowPoints(param_2,*(HWND *)(iVar3 + 4),&local_14,1);
    if ((*(int *)(iVar3 + 0x18) != 0) && (gfx_palettized_display == 1)) {
      SelectPalette(*(HDC *)param_1,*(HPALETTE *)(iVar3 + 0x18),0);
      RealizePalette(*(HDC *)param_1);
    }
    rop = 0xcc0020;
    hdcSrc = *(HDC *)(local_c + 4);
    LVar1 = local_14.x;
    y1 = local_14.y;
    iVar4 = rect_height(param_1 + 8);
    iVar5 = rect_width(param_1 + 8);
    BitBlt(*(HDC *)param_1,*(int *)(param_1 + 8),*(int *)(param_1 + 0xc),iVar5,iVar4,hdcSrc,LVar1,y1
           ,rop);
  }
  return;
}
#undef local_14
#undef local_c
#undef local_8

/* 005c9222 auto */
#define local_10 (*(uptr *)(frame_ + FRAME_OFF(0)))
#define local_c (*(char * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(char (*)[4])(frame_ + FRAME_OFF(8)))
void __cdecl ctrl_parse_hotkey(iptr param_1,iptr param_2)

{
  size_t sVar1;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = (char *)param_2;
  *(undefined4 *)(param_1 + 0x28) = 0;
  while( true ) {
    if (*local_c == '\0') goto LAB_005c92ae;
    if (*local_c == '~') break;
    *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
    local_c++;
  }
  for (local_10 = *(uptr *)(param_1 + 0x28); sVar1 = _strlen((char *)param_2), local_10 < sVar1;
      local_10 = local_10 + 1) {
    *(undefined1 *)(local_10 + param_2) = *(undefined1 *)(local_10 + 1 + param_2);
  }
LAB_005c92ae:
  sVar1 = _strlen((char *)param_2);
  if (*(uint *)(param_1 + 0x28) < sVar1) {
    local_8[0] = *(char *)(*(int *)(param_1 + 0x28) + param_2);
    local_8[1] = 0;
    __strlwr(local_8);
    *(char *)(param_1 + 0x25) = local_8[0];
  }
  else {
    *(undefined4 *)(param_1 + 0x28) = 0xffffffff;
  }
  return;
}
#undef local_10
#undef local_c
#undef local_8

/* 005c9307 auto */
#define local_44 (*(tagPAINTSTRUCT *)(frame_ + FRAME_OFF(4)))
LRESULT __stdcall ctrl_default_wndproc(HWND param_1,uint param_2,WPARAM param_3,LPARAM param_4)

{
  HWND hWnd;
  iptr iVar1;
  LRESULT LVar1;
  undefined1 frame_[FRAME_OFF(72)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_2 < 0x10) {
    if (param_2 == 0xf) {
      BeginPaint(param_1,&local_44);
      ctrl_paint_parent_bkgnd((iptr)&local_44,param_1);
      EndPaint(param_1,&local_44);
      return 0;
    }
    if (param_2 == 2) {
      iVar1 = wnd_from_hwnd(param_1);
      if (iVar1 != 0) {
        if (*(int *)(iVar1 + 0x2c) == 3) {
          **(undefined4 **)(iVar1 + 0x24) = 0;
        }
        else {
          control_set_hwnd(*(ControlHwndSetView **)(iVar1 + 4),0);
        }
        ctrl_hwnd_free_block(param_1);
      }
      LVar1 = DefWindowProcA(param_1,2,param_3,param_4);
      return LVar1;
    }
  }
  else if ((0xff < param_2) && (param_2 < 0x103)) {
    hWnd = GetParent(param_1);
    SendMessageA(hWnd,param_2,param_3,param_4);
    return 0;
  }
  LVar1 = DefWindowProcA(param_1,param_2,param_3,param_4);
  return LVar1;
}
#undef local_44

/* 005c944b auto */
int __cdecl ctrl_destroy_hwnd(iptr param_1)

{
  int iVar1;
  int iVar2;
  HWND hWnd;
  
  iVar1 = control_get_type((ControlTypeView *)param_1);
  if (iVar1 != 3) {
    iVar2 = control_get_hwnd((ControlHwndView *)param_1);
    iVar1 = 0;
    if (iVar2 != 0) {
      hWnd = (HWND)control_get_hwnd((ControlHwndView *)param_1);
      iVar1 = DestroyWindow(hWnd);
    }
  }
  return iVar1;
}

/* 005c9499 auto */
#define local_c (*(undefined4 * *)(frame_ + FRAME_OFF(4)))
undefined4 * __cdecl ctrl_init_block(HWND param_1,iptr param_2)

{
  undefined4 uVar1;
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = (undefined4 *)0x0;
  if (param_1 == (HWND)0x0) {
    dbg_log(ADDR(0x637cf4, ((u8 *)&g.d_00637cf4)));
  }
  else {
    uVar1 = mem_handle_alloc(0x30);
    local_c = (undefined4 *)mem_handle_lock(uVar1);
    local_c[2] = 0;
    local_c[5] = 0;
    local_c[4] = local_c[5];
    local_c[3] = local_c[4];
    *local_c = uVar1;
    local_c[1] = param_2;
    local_c[6] = 0;
    local_c[7] = 0;
    local_c[8] = 0;
    local_c[0xb] = 0;
    SetWindowLongA(param_1,0,(LONG)local_c);
  }
  return local_c;
}
#undef local_c

/* 005c9595 auto */
void __cdecl ctrl_hwnd_free_block(HWND param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  if (param_1 == (HWND)0x0) {
    dbg_log(ADDR(0x637d30, ((u8 *)&g.d_00637d30)));
  }
  else {
    puVar2 = (undefined4 *)GetWindowLongA(param_1,0);
    if (puVar2 != (undefined4 *)0x0) {
      if (puVar2[2] == 0) {
        if (puVar2[3] != 0) {
          DeleteObject((HGDIOBJ)puVar2[3]);
          puVar2[3] = 0;
        }
        if (puVar2[4] != 0) {
          DeleteObject((HGDIOBJ)puVar2[4]);
          puVar2[4] = 0;
        }
        if (puVar2[5] != 0) {
          DeleteObject((HGDIOBJ)puVar2[5]);
          puVar2[5] = 0;
        }
      }
      if (puVar2[0xb] == 2) {
        operator_delete((void *)puVar2[9]);
        puVar2[9] = 0;
      }
      uVar1 = *puVar2;
      mem_handle_unlock(uVar1);
      mem_handle_free(uVar1);
      SetWindowLongA(param_1,-4,ADDR(0x5c9307, ctrl_default_wndproc));
      SetWindowLongA(param_1,0,0);
    }
  }
  return;
}

/* 005c9710 auto */
/* Library Function - Single Match
    public: void __thiscall ios::delbuf(int)
   
   Library: Visual Studio 1998 Debug */

void __thiscall control_set_hwnd(ControlHwndSetView *this,u32 param_1)

{
  this->hwnd = param_1;
  return;
}

/* 005c9740 auto */
#define app_hinstance (*(HINSTANCE *)((u8 *)&g.d_006e4ff0))
#define local_2a0 (*(DWORD *)(frame_ + FRAME_OFF(0)))
#define local_278 (*(char (*)[256])(frame_ + FRAME_OFF(40)))
#define local_178 (*(int *)(frame_ + FRAME_OFF(296)))
#define local_174 (*(undefined1 (*)[4])(frame_ + FRAME_OFF(300)))
#define local_170 (*(Control * *)(frame_ + FRAME_OFF(304)))
#define local_16c (*(int *)(frame_ + FRAME_OFF(308)))
#define local_168 (*(HBITMAP *)(frame_ + FRAME_OFF(312)))
#define local_164 (*(HDC *)(frame_ + FRAME_OFF(316)))
#define local_160 (*(undefined1 (*)[4])(frame_ + FRAME_OFF(320)))
#define local_15c (*(undefined1 (*)[4])(frame_ + FRAME_OFF(324)))
#define local_158 (*(int *)(frame_ + FRAME_OFF(328)))
#define local_154 (*(HWND *)(frame_ + FRAME_OFF(332)))
#define local_150 (*(tagRECT *)(frame_ + FRAME_OFF(336)))
#define local_140 (*(HGDIOBJ *)(frame_ + FRAME_OFF(352)))
#define local_13c (*(char (*)[256])(frame_ + FRAME_OFF(356)))
#define local_3c (*(int *)(frame_ + FRAME_OFF(612)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(616)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(620)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(624)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(628)))
#define local_28 (*(tagRECT *)(frame_ + FRAME_OFF(632)))
#define local_18 (*(HPEN *)(frame_ + FRAME_OFF(648)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(652)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(656)))
#define local_c (*(int *)(frame_ + FRAME_OFF(660)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(664)))
HWND __cdecl
button_create_hwnd(int *param_1,iptr param_2,undefined4 param_3,int param_4,GameFont *param_5)

{
  WndBase *this;
  iptr iVar1;
  iptr iVar2;
  int iVar3;
  HDC hdc;
  int iVar4;
  HBITMAP h;
  HBITMAP h_00;
  WndPaletteView *pCVar5;
  PaletteHandleView *this_00;
  HPALETTE hPal;
  GamePalette *this_01;
  iptr iVar6;
  HPEN h_01;
  HPEN h_02;
  undefined4 uVar7;
  undefined4 *puVar8;
  HGDIOBJ h_03;
  HGDIOBJ h_04;
  size_t sVar9;
  HWND hWndParent;
  u32 uVar10;
  HMENU hMenu;
  undefined1 *puVar11;
  LONG LVar12;
  HINSTANCE hInstance;
  undefined1 *puVar13;
  tagRECT *ptVar14;
  LPVOID lpParam;
  BOOL bForceBkgd;
  undefined1 *puVar15;
  UINT UVar16;
  LONG LVar17;
  undefined1 frame_[FRAME_OFF(672)] __attribute__((aligned(8)));  /* original stack frame */
  
  FUN_005f22d0(local_278,param_3);
  local_170 = (Control *)param_2;
  local_2a0 = 0x40810000;
  if (param_4 != 0) {
    local_2a0 = 0x50810000;
  }
  lpParam = (LPVOID)0x0;
  hMenu = (HMENU)0x0;
  hInstance = app_hinstance;
  this = (WndBase *)ctrl_get_parent((Control *)param_2);
  iVar1 = wnd_get_window(this);
  hWndParent = *(HWND *)(iVar1 + 4);
  iVar2 = rect_height((iptr)param_1);
  iVar3 = rect_width((iptr)param_1);
  local_154 = CreateWindowExA(4,s_MSControlClass_00637d70,&button_wnd_title,local_2a0,*param_1,
                              param_1[1],iVar3,iVar2,hWndParent,hMenu,hInstance,lpParam);
  ctrl_parse_hotkey((iptr)local_170,(iptr)local_278);
  local_150.left = *param_1;
  local_150.top = param_1[1];
  local_150.right = param_1[2];
  local_150.bottom = param_1[3];
  OffsetRect(&local_150,-local_150.left,-local_150.top);
  local_150.right -= 2;
  local_150.bottom -= 2;
  hdc = GetDC(local_154);
  iVar3 = rect_height((iptr)&local_150);
  iVar4 = rect_width((iptr)&local_150);
  h = CreateCompatibleBitmap(hdc,iVar4,iVar3);
  if (h == (HBITMAP)0x0) {
    dbg_log(ADDR(0x637d80, ((u8 *)&g.d_00637d80)));
    DestroyWindow(local_154);
    local_154 = (HWND)0x0;
  }
  else {
    iVar3 = rect_height((iptr)&local_150);
    iVar4 = rect_width((iptr)&local_150);
    h_00 = CreateCompatibleBitmap(hdc,iVar4,iVar3);
    if (h_00 == (HBITMAP)0x0) {
      dbg_log(ADDR(0x637da8, ((u8 *)&g.d_00637da8)));
      DestroyWindow(local_154);
      local_154 = (HWND)0x0;
    }
    else {
      iVar3 = rect_height((iptr)&local_150);
      iVar4 = rect_width((iptr)&local_150);
      local_168 = CreateCompatibleBitmap(hdc,iVar4,iVar3);
      if (local_168 == (HBITMAP)0x0) {
        dbg_log(ADDR(0x637dd0, ((u8 *)&g.d_00637dd0)));
        DestroyWindow(local_154);
        local_154 = (HWND)0x0;
      }
      else {
        local_164 = CreateCompatibleDC(hdc);
        ReleaseDC(local_154,hdc);
        SetBkMode(local_164,1);
        if (local_170->field_34 == 0xffffffff) {
          local_18 = GetStockObject(1);
        }
        else {
          if (gfx_palettized_display == 1) {
            bForceBkgd = 0;
            pCVar5 = (WndPaletteView *)ctrl_get_parent(local_170);
            this_00 = (PaletteHandleView *)wnd_get_palette(pCVar5);
            hPal = (HPALETTE)palette_get_hpalette(this_00);
            SelectPalette(local_164,hPal,bForceBkgd);
            RealizePalette(local_164);
          }
          puVar15 = local_15c;
          puVar13 = local_174;
          puVar11 = local_160;
          uVar10 = local_170->field_34;
          pCVar5 = (WndPaletteView *)ctrl_get_parent(local_170);
          this_01 = (GamePalette *)wnd_get_palette(pCVar5);
          iVar6 = palette_get_logpalette(this_01);
          palette_get_entry_rgb(iVar6,uVar10,(iptr)puVar11,(iptr)puVar13,(iptr)puVar15);
          local_18 = CreatePen(0,1,(uint)CONCAT12(local_15c[0],CONCAT11(local_174[0],local_160[0])))
          ;
        }
        h_01 = CreatePen(0,1,0xffffff);
        h_02 = CreatePen(0,1,0x808080);
        uVar7 = font_get_handle(param_5);
        puVar8 = (undefined4 *)mem_handle_lock(uVar7);
        h_03 = SelectObject(local_164,(HGDIOBJ)*puVar8);
        uVar7 = font_get_handle(param_5);
        mem_handle_unlock(uVar7);
        h_04 = SelectObject(local_164,h);
        local_14 = local_150.left;
        local_10 = local_150.top;
        local_c = local_150.right;
        local_8 = local_150.bottom;
        if (local_170->field_34 == 0xffffffff) {
          FillRect(local_164,&local_150,(HBRUSH)local_18);
        }
        else {
          local_140 = SelectObject(local_164,local_18);
          for (local_178 = local_150.top; local_178 < local_150.bottom; local_178++) {
            MoveToEx(local_164,local_150.left,local_178,(LPPOINT)0x0);
            LineTo(local_164,local_150.right,local_178);
          }
          SelectObject(local_164,local_140);
        }
        local_140 = SelectObject(local_164,h_01);
        MoveToEx(local_164,local_150.left,local_150.bottom,(LPPOINT)0x0);
        LineTo(local_164,local_150.left,local_150.top);
        LineTo(local_164,local_150.right,local_150.top);
        MoveToEx(local_164,local_150.left + 1,local_150.bottom - 1,(LPPOINT)0x0);
        LineTo(local_164,local_150.left + 1,local_150.top + 1);
        LineTo(local_164,local_150.right - 1,local_150.top + 1);
        SelectObject(local_164,h_02);
        MoveToEx(local_164,local_150.left + 1,local_150.bottom - 1,(LPPOINT)0x0);
        LineTo(local_164,local_150.right - 1,local_150.bottom - 1);
        LineTo(local_164,local_150.right - 1,local_150.top);
        MoveToEx(local_164,local_150.left + 2,local_150.bottom - 2,(LPPOINT)0x0);
        LineTo(local_164,local_150.right - 2,local_150.bottom - 2);
        LineTo(local_164,local_150.right - 2,local_150.top + 1);
        SelectObject(local_164,local_140);
        local_28.left = local_150.left;
        local_28.top = local_150.top;
        local_28.right = local_150.right;
        local_28.bottom = local_150.bottom;
        UVar16 = 0x424;
        ptVar14 = &local_28;
        sVar9 = _strlen(local_278);
        DrawTextA(local_164,local_278,sVar9,ptVar14,UVar16);
        local_16c = rect_width((iptr)&local_28);
        LVar17 = local_150.bottom;
        iVar3 = rect_width((iptr)&local_150);
        iVar4 = ((local_150.left + iVar3 / 2) - local_16c / 2) + local_16c;
        LVar12 = local_150.top;
        iVar3 = rect_width((iptr)&local_150);
        SetRect(&local_28,(local_150.left + iVar3 / 2) - local_16c / 2,LVar12,iVar4,LVar17);
        UVar16 = 0x24;
        ptVar14 = &local_28;
        sVar9 = _strlen(local_278);
        DrawTextA(local_164,local_278,sVar9,ptVar14,UVar16);
        local_3c = local_28.left;
        local_38 = local_28.top;
        local_34 = local_28.right;
        local_30 = local_28.bottom;
        if (-1 < (int)local_170->field_28) {
          FUN_005f22d0(local_13c,local_278);
          local_13c[local_170->field_28] = '\0';
          sVar9 = _strlen(local_13c);
          if (sVar9 == 0) {
            local_2c = local_28.left;
          }
          else {
            local_28.left = local_3c;
            local_28.top = local_38;
            local_28.right = local_34;
            local_28.bottom = local_30;
            UVar16 = 0x424;
            ptVar14 = &local_28;
            sVar9 = _strlen(local_13c);
            DrawTextA(local_164,local_13c,sVar9,ptVar14,UVar16);
            local_2c = local_28.right - 1;
          }
          FUN_005f22d0(local_13c,local_278);
          local_13c[local_170->field_28 + 1] = '\0';
          local_28.left = local_3c;
          local_28.top = local_38;
          local_28.right = local_34;
          local_28.bottom = local_30;
          UVar16 = 0x424;
          ptVar14 = &local_28;
          sVar9 = _strlen(local_13c);
          DrawTextA(local_164,local_13c,sVar9,ptVar14,UVar16);
          local_16c = (local_28.right + 1) - local_2c;
          local_2c = local_2c + (local_16c >> 1) - 5;
          local_158 = local_2c + 10;
          SelectObject(local_164,h_02);
          MoveToEx(local_164,local_2c,local_28.bottom - 2,(LPPOINT)0x0);
          LineTo(local_164,local_158,local_28.bottom - 2);
          MoveToEx(local_164,local_2c,local_28.bottom - 1,(LPPOINT)0x0);
          LineTo(local_164,local_158,local_28.bottom - 1);
          SelectObject(local_164,local_140);
        }
        SelectObject(local_164,h_00);
        if (local_170->field_34 == 0xffffffff) {
          FillRect(local_164,&local_150,(HBRUSH)local_18);
        }
        else {
          local_140 = SelectObject(local_164,local_18);
          for (local_178 = local_150.top; local_178 < local_150.bottom; local_178++) {
            MoveToEx(local_164,local_150.left,local_178,(LPPOINT)0x0);
            LineTo(local_164,local_150.right,local_178);
          }
          SelectObject(local_164,local_140);
        }
        local_140 = SelectObject(local_164,h_02);
        MoveToEx(local_164,local_150.left,local_150.bottom,(LPPOINT)0x0);
        LineTo(local_164,local_150.left,local_150.top);
        LineTo(local_164,local_150.right,local_150.top);
        MoveToEx(local_164,local_150.left + 1,local_150.bottom - 1,(LPPOINT)0x0);
        LineTo(local_164,local_150.left + 1,local_150.top + 1);
        LineTo(local_164,local_150.right - 1,local_150.top + 1);
        SelectObject(local_164,local_140);
        local_150.left += 2;
        local_150.top += 2;
        local_28.right = local_150.right;
        local_28.bottom = local_150.bottom;
        UVar16 = 0x424;
        ptVar14 = &local_28;
        local_28.left = local_150.left;
        local_28.top = local_150.top;
        sVar9 = _strlen(local_278);
        DrawTextA(local_164,local_278,sVar9,ptVar14,UVar16);
        local_16c = rect_width((iptr)&local_28);
        LVar17 = local_150.bottom;
        iVar3 = rect_width((iptr)&local_150);
        iVar3 = (((iVar3 >> 1) + local_150.left) - (local_16c >> 1)) + local_16c;
        LVar12 = local_150.top;
        iVar4 = rect_width((iptr)&local_150);
        SetRect(&local_28,((iVar4 >> 1) + local_150.left) - (local_16c >> 1),LVar12,iVar3,LVar17);
        UVar16 = 0x24;
        ptVar14 = &local_28;
        sVar9 = _strlen(local_278);
        DrawTextA(local_164,local_278,sVar9,ptVar14,UVar16);
        local_3c = local_28.left;
        local_38 = local_28.top;
        local_34 = local_28.right;
        local_30 = local_28.bottom;
        if (-1 < (int)local_170->field_28) {
          FUN_005f22d0(local_13c,local_278);
          local_13c[local_170->field_28] = '\0';
          sVar9 = _strlen(local_13c);
          if (sVar9 == 0) {
            local_2c = local_28.left;
          }
          else {
            local_28.left = local_3c;
            local_28.top = local_38;
            local_28.right = local_34;
            local_28.bottom = local_30;
            UVar16 = 0x424;
            ptVar14 = &local_28;
            sVar9 = _strlen(local_13c);
            DrawTextA(local_164,local_13c,sVar9,ptVar14,UVar16);
            local_2c = local_28.right - 1;
          }
          FUN_005f22d0(local_13c,local_278);
          local_13c[local_170->field_28 + 1] = '\0';
          local_28.left = local_3c;
          local_28.top = local_38;
          local_28.right = local_34;
          local_28.bottom = local_30;
          UVar16 = 0x424;
          ptVar14 = &local_28;
          sVar9 = _strlen(local_13c);
          DrawTextA(local_164,local_13c,sVar9,ptVar14,UVar16);
          local_16c = (local_28.right + 1) - local_2c;
          local_2c = local_2c + (local_16c >> 1) - 5;
          local_158 = local_2c + 10;
          SelectObject(local_164,h_02);
          MoveToEx(local_164,local_2c,local_28.bottom - 2,(LPPOINT)0x0);
          LineTo(local_164,local_158,local_28.bottom - 2);
          MoveToEx(local_164,local_2c,local_28.bottom - 1,(LPPOINT)0x0);
          LineTo(local_164,local_158,local_28.bottom - 1);
          SelectObject(local_164,local_140);
        }
        SelectObject(local_164,local_168);
        local_150.left = local_14;
        local_150.top = local_10;
        local_150.right = local_c;
        local_150.bottom = local_8;
        if (local_170->field_34 == 0xffffffff) {
          FillRect(local_164,&local_150,(HBRUSH)local_18);
        }
        else {
          local_140 = SelectObject(local_164,local_18);
          for (local_178 = local_150.top; local_178 < local_150.bottom; local_178++) {
            MoveToEx(local_164,local_150.left,local_178,(LPPOINT)0x0);
            LineTo(local_164,local_150.right,local_178);
          }
          SelectObject(local_164,local_140);
        }
        local_140 = SelectObject(local_164,h_01);
        MoveToEx(local_164,local_150.left,local_150.bottom,(LPPOINT)0x0);
        LineTo(local_164,local_150.left,local_150.top);
        LineTo(local_164,local_150.right,local_150.top);
        MoveToEx(local_164,local_150.left + 1,local_150.bottom - 1,(LPPOINT)0x0);
        LineTo(local_164,local_150.left + 1,local_150.top + 1);
        LineTo(local_164,local_150.right - 1,local_150.top + 1);
        SelectObject(local_164,h_02);
        MoveToEx(local_164,local_150.left + 1,local_150.bottom - 1,(LPPOINT)0x0);
        LineTo(local_164,local_150.right - 1,local_150.bottom - 1);
        LineTo(local_164,local_150.right - 1,local_150.top);
        MoveToEx(local_164,local_150.left + 2,local_150.bottom - 2,(LPPOINT)0x0);
        LineTo(local_164,local_150.right - 2,local_150.bottom - 2);
        LineTo(local_164,local_150.right - 2,local_150.top + 1);
        SelectObject(local_164,local_140);
        local_28.left = local_150.left;
        local_28.top = local_150.top;
        local_28.right = local_150.right;
        local_28.bottom = local_150.bottom;
        UVar16 = 0x424;
        ptVar14 = &local_28;
        sVar9 = _strlen(local_278);
        DrawTextA(local_164,local_278,sVar9,ptVar14,UVar16);
        local_16c = rect_width((iptr)&local_28);
        LVar17 = local_150.bottom;
        iVar3 = rect_width((iptr)&local_150);
        iVar3 = (((iVar3 >> 1) + local_150.left) - (local_16c >> 1)) + local_16c;
        LVar12 = local_150.top;
        iVar4 = rect_width((iptr)&local_150);
        SetRect(&local_28,((iVar4 >> 1) + local_150.left) - (local_16c >> 1),LVar12,iVar3,LVar17);
        SetTextColor(local_164,0xffffff);
        UVar16 = 0x24;
        ptVar14 = &local_28;
        sVar9 = _strlen(local_278);
        DrawTextA(local_164,local_278,sVar9,ptVar14,UVar16);
        OffsetRect(&local_28,-1,-1);
        SetTextColor(local_164,0x808080);
        UVar16 = 0x24;
        ptVar14 = &local_28;
        sVar9 = _strlen(local_278);
        DrawTextA(local_164,local_278,sVar9,ptVar14,UVar16);
        OffsetRect(&local_28,1,1);
        local_3c = local_28.left;
        local_38 = local_28.top;
        local_34 = local_28.right;
        local_30 = local_28.bottom;
        if (-1 < (int)local_170->field_28) {
          FUN_005f22d0(local_13c,local_278);
          local_13c[local_170->field_28] = '\0';
          sVar9 = _strlen(local_13c);
          if (sVar9 == 0) {
            local_2c = local_28.left;
          }
          else {
            local_28.left = local_3c;
            local_28.top = local_38;
            local_28.right = local_34;
            local_28.bottom = local_30;
            UVar16 = 0x424;
            ptVar14 = &local_28;
            sVar9 = _strlen(local_13c);
            DrawTextA(local_164,local_13c,sVar9,ptVar14,UVar16);
            local_2c = local_28.right - 1;
          }
          FUN_005f22d0(local_13c,local_278);
          local_13c[local_170->field_28 + 1] = '\0';
          local_28.left = local_3c;
          local_28.top = local_38;
          local_28.right = local_34;
          local_28.bottom = local_30;
          UVar16 = 0x424;
          ptVar14 = &local_28;
          sVar9 = _strlen(local_13c);
          DrawTextA(local_164,local_13c,sVar9,ptVar14,UVar16);
          local_16c = (local_28.right + 1) - local_2c;
          local_2c = local_2c + (local_16c >> 1) - 5;
          local_158 = local_2c + 10;
          SelectObject(local_164,h_02);
          MoveToEx(local_164,local_2c,local_28.bottom - 2,(LPPOINT)0x0);
          LineTo(local_164,local_158,local_28.bottom - 2);
          MoveToEx(local_164,local_2c,local_28.bottom - 1,(LPPOINT)0x0);
          LineTo(local_164,local_158,local_28.bottom - 1);
          SelectObject(local_164,local_140);
        }
        SelectObject(local_164,h_04);
        SelectObject(local_164,h_03);
        DeleteObject(h_01);
        if (local_170->field_34 != 0xffffffff) {
          DeleteObject(local_18);
        }
        DeleteObject(h_02);
        DeleteDC(local_164);
        iVar3 = ctrl_init_block(local_154,param_2);
        *(HBITMAP *)(iVar3 + 0xc) = h;
        *(HBITMAP *)(iVar3 + 0x10) = h_00;
        *(HBITMAP *)(iVar3 + 0x14) = local_168;
        *(undefined4 *)(iVar3 + 0x2c) = 6;
        SetWindowLongA(local_154,-4,ADDR(0x5cacd4, button_wndproc));
      }
    }
  }
  return local_154;
}
#undef app_hinstance
#undef local_2a0
#undef local_278
#undef local_178
#undef local_174
#undef local_170
#undef local_16c
#undef local_168
#undef local_164
#undef local_160
#undef local_15c
#undef local_158
#undef local_154
#undef local_150
#undef local_140
#undef local_13c
#undef local_3c
#undef local_38
#undef local_34
#undef local_30
#undef local_2c
#undef local_28
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 005cac22 auto */
#define wnd_active_child (*(undefined4 *)((u8 *)&g.d_00637ea4))
void __cdecl button_press_animated(HWND param_1)

{
  Control *this;
  iptr iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = wnd_from_hwnd(param_1);
  if (iVar1 != 0) {
    this = *(Control **)(iVar1 + 4);
    iVar2 = ctrl_is_enabled((ControlEnabledView *)this);
    if (iVar2 != 0) {
      SetFocus(param_1);
      *(undefined4 *)(iVar1 + 0x18) = 1;
      wnd_redraw_client(param_1);
      *(undefined4 *)(iVar1 + 0x18) = 0;
      ui_pump_messages();
      ui_wait_ticks(8);
      wnd_redraw_client(param_1);
      wnd_active_child = ctrl_get_parent(this);
      uVar3 = ctrl_get_id((ControlIdView *)this);
      button_fire_callback((ButtonClickView *)this,uVar3);
    }
  }
  return;
}
#undef wnd_active_child

/* 005cacd4: written by hand in src/game/fixups.c */

/* 005cb601 auto */
#define app_hinstance (*(HINSTANCE *)((u8 *)&g.d_006e4ff0))
#define local_24 (*(DWORD *)(frame_ + FRAME_OFF(4)))
#define local_1c (*(tagRECT *)(frame_ + FRAME_OFF(12)))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(28)))
#define local_8 (*(HWND *)(frame_ + FRAME_OFF(32)))
HWND __cdecl spritebtn_create_hwnd(int param_1,int param_2,int param_3,int param_4,iptr param_5,int param_6)

{
  WndBase *this;
  iptr iVar1;
  iptr iVar2;
  int iVar3;
  HWND hWndParent;
  HMENU hMenu;
  HINSTANCE hInstance;
  LPVOID lpParam;
  undefined1 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_24 = 0x40810000;
  if (param_6 != 0) {
    local_24 = 0x50810000;
  }
  local_c = param_5;
  SetRect(&local_1c,param_1,param_2,param_1 + param_3,param_2 + param_4);
  lpParam = (LPVOID)0x0;
  hMenu = (HMENU)0x0;
  hInstance = app_hinstance;
  this = (WndBase *)ctrl_get_parent((Control *)param_5);
  iVar1 = wnd_get_window(this);
  hWndParent = *(HWND *)(iVar1 + 4);
  iVar2 = rect_height((iptr)&local_1c);
  iVar3 = rect_width((iptr)&local_1c);
  local_8 = CreateWindowExA(4,s_MSControlClass_00637e48,&spritebtn_wnd_title,local_24,param_1,param_2,iVar3
                            ,iVar2,hWndParent,hMenu,hInstance,lpParam);
  iVar3 = ctrl_init_block(local_8,param_5);
  *(undefined4 *)(iVar3 + 0x2c) = 5;
  SetWindowLongA(local_8,-4,ADDR(0x5cb6eb, spritebtn_wndproc));
  return local_8;
}
#undef app_hinstance
#undef local_24
#undef local_1c
#undef local_c
#undef local_8

/* 005cb6db auto */
void __cdecl spritebtn_hwnd_cleanup_stub(undefined4 param_1)

{
  return;
}

/* 005cb6eb: written by hand in src/game/fixups.c */

/* 005cbdf0 auto */
void __thiscall button_fire_callback(ButtonClickView *this,undefined4 param_1)

{
  if (this->on_click != 0) {
    (*(code *)this->on_click)(param_1);
  }
  return;
}

/* 005cbe30 auto */
void __thiscall spritebtn_fire_click(SpriteButtonClickView *this,undefined4 param_1)

{
  if (this->on_click != 0) {
    (*(code *)this->on_click)(param_1);
  }
  return;
}

/* 005cbe70 auto */
void __thiscall spritebtn_fire_rclick(SpriteButtonRClickView *this,undefined4 param_1)

{
  if (this->on_rclick != 0) {
    (*(code *)this->on_rclick)(param_1);
  }
  return;
}

/* 005cbf40 auto */
#define local_5c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_4c (*(tagSIZE *)(frame_ + FRAME_OFF(20)))
#define local_44 (*(tagTEXTMETRICA *)(frame_ + FRAME_OFF(28)))
#define local_c (*(int *)(frame_ + FRAME_OFF(84)))
#define local_8 (*(undefined4 * *)(frame_ + FRAME_OFF(88)))
void __cdecl checkbox_calc_rect(char *param_1,int param_2,int param_3,iptr param_4,GameFont *param_5)

{
  HDC hdc;
  HDC hdc_00;
  undefined4 uVar1;
  HGDIOBJ h;
  size_t c;
  tagSIZE *lpsz;
  undefined1 frame_[FRAME_OFF(96)] __attribute__((aligned(8)));  /* original stack frame */
  
  hdc = GetDC((HWND)0x0);
  hdc_00 = CreateCompatibleDC(hdc);
  ReleaseDC((HWND)0x0,hdc);
  uVar1 = font_get_handle(param_5);
  local_8 = (undefined4 *)mem_handle_lock(uVar1);
  h = SelectObject(hdc_00,(HGDIOBJ)*local_8);
  uVar1 = font_get_handle(param_5);
  mem_handle_unlock(uVar1);
  GetTextMetricsA(hdc_00,&local_44);
  local_5c = local_44.tmHeight;
  lpsz = &local_4c;
  c = _strlen(param_1);
  GetTextExtentPointA(hdc_00,param_1,c,lpsz);
  local_c = local_4c.cx;
  SelectObject(hdc_00,h);
  DeleteDC(hdc_00);
  local_c += 0x25;
  if (local_44.tmHeight < 0x14) {
    local_5c = 0x14;
  }
  SetRect((LPRECT)param_4,param_2,param_3,local_c + param_2,local_5c + param_3);
  return;
}
#undef local_5c
#undef local_4c
#undef local_44
#undef local_c
#undef local_8

/* 005cc035 auto */
#define local_4c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_40 (*(tagTEXTMETRICA *)(frame_ + FRAME_OFF(16)))
#define local_8 (*(undefined4 * *)(frame_ + FRAME_OFF(72)))
void __cdecl checkbox_calc_rect_fixed(int param_1,int param_2,int param_3,iptr param_4,GameFont *param_5)

{
  HDC hdc;
  HDC hdc_00;
  undefined4 uVar1;
  undefined1 frame_[FRAME_OFF(80)] __attribute__((aligned(8)));  /* original stack frame */
  
  hdc = GetDC((HWND)0x0);
  hdc_00 = CreateCompatibleDC(hdc);
  ReleaseDC((HWND)0x0,hdc);
  uVar1 = font_get_handle(param_5);
  local_8 = (undefined4 *)mem_handle_lock(uVar1);
  SelectObject(hdc_00,(HGDIOBJ)*local_8);
  uVar1 = font_get_handle(param_5);
  mem_handle_unlock(uVar1);
  GetTextMetricsA(hdc_00,&local_40);
  local_4c = local_40.tmHeight;
  DeleteDC(hdc_00);
  if (local_40.tmHeight < 0x14) {
    local_4c = 0x14;
  }
  SetRect((LPRECT)param_4,param_1,param_2,param_3 + param_1,local_4c + param_2);
  return;
}
#undef local_4c
#undef local_40
#undef local_8

/* 005cc0f0 auto */
#define app_hinstance (*(HINSTANCE *)((u8 *)&g.d_006e4ff0))
#define local_24 (*(DWORD *)(frame_ + FRAME_OFF(4)))
HWND __cdecl checkbox_create_hwnd(iptr param_1,iptr param_2,char *param_3,int param_4)

{
  size_t sVar1;
  void *pvVar2;
  WndBase *this;
  iptr iVar3;
  iptr iVar4;
  int iVar5;
  HWND pHVar6;
  HBITMAP pHVar7;
  HBITMAP pHVar8;
  HBITMAP pHVar9;
  HMENU hMenu;
  HINSTANCE hInstance;
  LPVOID lpParam;
  undefined1 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  sVar1 = _strlen(param_3);
  pvVar2 = operator_new(sVar1 + 1);
  FUN_005f22d0(pvVar2,param_3);
  local_24 = 0x40010000;
  if (param_4 != 0) {
    local_24 = 0x50010000;
  }
  lpParam = (LPVOID)0x0;
  hMenu = (HMENU)0x0;
  hInstance = app_hinstance;
  this = (WndBase *)ctrl_get_parent((Control *)param_2);
  iVar3 = wnd_get_window(this);
  pHVar6 = *(HWND *)(iVar3 + 4);
  iVar4 = rect_height(param_1);
  iVar5 = rect_width(param_1);
  pHVar6 = CreateWindowExA(4,s_MSControlClass_00637f10,&checkbox_wnd_title,local_24,*(int *)param_1,
                           *(int *)(param_1 + 4),iVar5,iVar4,pHVar6,hMenu,hInstance,lpParam);
  ctrl_parse_hotkey(param_2,(iptr)pvVar2);
  pHVar7 = LoadBitmapA(app_hinstance,(LPCSTR)0x132);
  pHVar8 = LoadBitmapA(app_hinstance,(LPCSTR)0x131);
  pHVar9 = LoadBitmapA(app_hinstance,(LPCSTR)0x130);
  iVar5 = ctrl_init_block(pHVar6,param_2);
  *(HBITMAP *)(iVar5 + 0xc) = pHVar7;
  *(HBITMAP *)(iVar5 + 0x10) = pHVar8;
  *(HBITMAP *)(iVar5 + 0x14) = pHVar9;
  *(undefined4 *)(iVar5 + 0x2c) = 2;
  *(void **)(iVar5 + 0x24) = pvVar2;
  SetWindowLongA(pHVar6,-4,ADDR(0x5cc320, checkbox_wndproc));
  return pHVar6;
}
#undef app_hinstance
#undef local_24

/* 005cc248 auto */
void __cdecl checkbox_destroy_hwnd(int param_1)

{
  if (param_1 == 0) {
    dbg_log(ADDR(0x637f20, ((u8 *)&g.d_00637f20)));
  }
  return;
}

/* 005cc274 auto */
#define wnd_active_child (*(undefined4 *)((u8 *)&g.d_00637ea4))
void __cdecl checkbox_toggle_by_hotkey(HWND param_1)

{
  Control *this;
  iptr iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  iVar1 = wnd_from_hwnd(param_1);
  if (iVar1 != 0) {
    this = *(Control **)(iVar1 + 4);
    SetFocus(param_1);
    iVar2 = checkbox_is_checked(this);
    if (iVar2 == 0) {
      checkbox_set_checked(this,1);
    }
    else {
      checkbox_set_checked(this,0);
    }
    SetCapture(param_1);
    InvalidateRect(param_1,(RECT *)0x0,0);
    wnd_active_child = ctrl_get_parent(this);
    uVar3 = checkbox_is_checked(this);
    uVar4 = ctrl_get_id((ControlIdView *)this);
    checkbox_fire_callback((CheckboxClickView *)this,uVar4,uVar3);
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
#define local_1b0 (*(tagRECT *)(frame_ + FRAME_OFF(0)))
#define local_1a0 (*(HBITMAP *)(frame_ + FRAME_OFF(16)))
#define local_19c (*(iptr *)(frame_ + FRAME_OFF(20)))
#define local_198 (*(Control * *)(frame_ + FRAME_OFF(24)))
#define local_194 (*(tagPAINTSTRUCT *)(frame_ + FRAME_OFF(28)))
#define local_154 (*(HGDIOBJ *)(frame_ + FRAME_OFF(92)))
#define local_150 (*(tagSIZE *)(frame_ + FRAME_OFF(96)))
#define local_148 (*(undefined1 (*)[4])(frame_ + FRAME_OFF(104)))
#define local_144 (*(HDC *)(frame_ + FRAME_OFF(108)))
#define local_140 (*(char * *)(frame_ + FRAME_OFF(112)))
#define local_13c (*(int *)(frame_ + FRAME_OFF(116)))
#define local_138 (*(int *)(frame_ + FRAME_OFF(120)))
#define local_134 (*(int *)(frame_ + FRAME_OFF(124)))
#define local_130 (*(int *)(frame_ + FRAME_OFF(128)))
#define local_12c (*(int *)(frame_ + FRAME_OFF(132)))
#define local_128 (*(int *)(frame_ + FRAME_OFF(136)))
#define local_124 (*(undefined1 (*)[4])(frame_ + FRAME_OFF(140)))
#define local_120 (*(undefined1 (*)[4])(frame_ + FRAME_OFF(144)))
#define local_11c (*(HBRUSH *)(frame_ + FRAME_OFF(148)))
#define local_118 (*(undefined4 * *)(frame_ + FRAME_OFF(152)))
#define local_114 (*(char (*)[256])(frame_ + FRAME_OFF(156)))
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(412)))
undefined4 __stdcall checkbox_wndproc(HWND param_1,uint param_2,WPARAM param_3,LPARAM param_4)

{
  char cVar1;
  undefined4 uVar2;
  iptr iVar3;
  iptr iVar4;
  int *piVar3;
  int iVar5;
  uint uVar6;
  WndPaletteView *pCVar7;
  GamePalette *pCVar8;
  size_t sVar9;
  WndBase *pCVar10;
  iptr iVar11;
  HWND pHVar12;
  WndKeyNavView *pCVar13;
  undefined4 uVar14;
  undefined1 *puVar15;
  undefined1 *puVar16;
  tagRECT *ptVar17;
  undefined1 *puVar18;
  UINT UVar19;
  undefined1 frame_[FRAME_OFF(432)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_19c = wnd_from_hwnd(param_1);
  local_198 = *(Control **)(local_19c + 4);
  if (param_2 < 0x10) {
    if (param_2 == 0xf) {
      iVar3 = checkbox_is_enabled((CheckboxEnabledView *)local_198);
      if (iVar3 == 0) {
        pHVar12 = GetFocus();
        if (pHVar12 == param_1) {
          SetFocus((HWND)0x0);
        }
        local_1a0 = *(HBITMAP *)(local_19c + 0xc);
      }
      else {
        iVar4 = checkbox_is_checked(local_198);
        if (iVar4 == 0) {
          local_1a0 = *(HBITMAP *)(local_19c + 0x10);
        }
        else {
          local_1a0 = *(HBITMAP *)(local_19c + 0x14);
        }
      }
      GetBitmapDimensionEx(local_1a0,&local_150);
      piVar3 = (int *)ctrl_get_rect(local_198);
      local_1b0.left = *piVar3;
      local_1b0.top = piVar3[1];
      local_1b0.right = piVar3[2];
      local_1b0.bottom = piVar3[3];
      local_134 = local_1b0.left;
      local_130 = local_1b0.top;
      local_12c = local_1b0.right;
      local_128 = local_1b0.bottom;
      if (checkbox_mouse_pressed != 0) {
        local_12c = local_1b0.left + 0x20;
        iVar5 = rect_height((iptr)&local_1b0);
        local_130 = iVar5 - 0x14 + local_1b0.top >> 1;
        local_128 = local_1b0.top + 0x14;
      }
      OffsetRect(&local_1b0,-local_1b0.left,-local_1b0.top);
      local_144 = BeginPaint(param_1,&local_194);
      ctrl_paint_parent_bkgnd((iptr)&local_194,param_1);
      uVar14 = font_get_handle((GameFont *)local_198->field_38);
      local_118 = (undefined4 *)mem_handle_lock(uVar14);
      local_154 = SelectObject(local_144,(HGDIOBJ)*local_118);
      uVar14 = font_get_handle((GameFont *)local_198->field_38);
      mem_handle_unlock(uVar14);
      SetBkMode(local_144,1);
      gdi_blit_transparent(local_144,local_1a0,local_1b0.left,local_1b0.bottom - 0x14 >> 1,0x20,0x14,0,7);
      local_1b0.left += 0x25;
      local_140 = *(char **)(local_19c + 0x24);
      if ((ctrl_shadow_dx != 0) || (ctrl_shadow_dy != 0)) {
        OffsetRect(&local_1b0,(uint)ctrl_shadow_dx,(uint)ctrl_shadow_dy);
        puVar18 = local_120;
        puVar16 = local_148;
        puVar15 = local_124;
        uVar6 = (uint)ctrl_shadow_color_index;
        pCVar7 = (WndPaletteView *)ctrl_get_parent(local_198);
        pCVar8 = (GamePalette *)wnd_get_palette(pCVar7);
        palette_get_entry(pCVar8,uVar6,(iptr)puVar15,(iptr)puVar16,(iptr)puVar18);
        SetTextColor(local_144,(uint)CONCAT12(local_120[0],CONCAT11(local_148[0],local_124[0])));
        UVar19 = 0x24;
        ptVar17 = &local_1b0;
        sVar9 = _strlen(local_140);
        DrawTextA(local_144,local_140,sVar9,ptVar17,UVar19);
        OffsetRect(&local_1b0,-(uint)ctrl_shadow_dx,-(uint)ctrl_shadow_dy);
      }
      iVar5 = checkbox_is_enabled((CheckboxEnabledView *)local_198);
      if (iVar5 == 1) {
        pCVar10 = (WndBase *)ctrl_get_parent(local_198);
        iVar5 = wnd_get_window(pCVar10);
        if (*(int *)(iVar5 + 0x40) == 8) {
          if (ctrl_text_color_index == 0) {
            SetTextColor(local_144,0);
          }
          else {
            puVar18 = local_120;
            puVar16 = local_148;
            puVar15 = local_124;
            uVar6 = (uint)ctrl_text_color_index;
            pCVar7 = (WndPaletteView *)ctrl_get_parent(local_198);
            pCVar8 = (GamePalette *)wnd_get_palette(pCVar7);
            iVar11 = palette_get_logpalette(pCVar8);
            palette_get_entry_rgb(iVar11,uVar6,(iptr)puVar15,(iptr)puVar16,(iptr)puVar18);
            SetTextColor(local_144,(uint)CONCAT12(local_120[0],CONCAT11(local_148[0],local_124[0])))
            ;
          }
        }
        else if (ctrl_text_rgb_set == '\0') {
          SetTextColor(local_144,0);
        }
        else {
          SetTextColor(local_144,(uint)CONCAT12(ctrl_text_rgb_b,CONCAT11(ctrl_text_rgb_g,ctrl_text_rgb_r)));
        }
      }
      else {
        iVar5 = checkbox_is_enabled((CheckboxEnabledView *)local_198);
        if (iVar5 == 0) {
          pCVar10 = (WndBase *)ctrl_get_parent(local_198);
          iVar5 = wnd_get_window(pCVar10);
          if (*(int *)(iVar5 + 0x40) == 8) {
            if (ctrl_disabled_color_index == 0) {
              SetTextColor(local_144,0x404040);
            }
            else {
              puVar18 = local_120;
              puVar16 = local_148;
              puVar15 = local_124;
              uVar6 = (uint)ctrl_disabled_color_index;
              pCVar7 = (WndPaletteView *)ctrl_get_parent(local_198);
              pCVar8 = (GamePalette *)wnd_get_palette(pCVar7);
              iVar11 = palette_get_logpalette(pCVar8);
              palette_get_entry_rgb(iVar11,uVar6,(iptr)puVar15,(iptr)puVar16,(iptr)puVar18);
              SetTextColor(local_144,
                           (uint)CONCAT12(local_120[0],CONCAT11(local_148[0],local_124[0])));
            }
          }
          else if (ctrl_disabled_rgb_set == '\0') {
            SetTextColor(local_144,0x404040);
          }
          else {
            SetTextColor(local_144,(uint)CONCAT12(ctrl_disabled_rgb_b,CONCAT11(ctrl_disabled_rgb_g,ctrl_disabled_rgb_r)))
            ;
          }
        }
      }
      UVar19 = 0x24;
      ptVar17 = &local_1b0;
      sVar9 = _strlen(local_140);
      DrawTextA(local_144,local_140,sVar9,ptVar17,UVar19);
      if (local_198->field_28 != 0xffffffff) {
        FUN_005f22d0(local_114,local_140);
        local_114[local_198->field_28] = '\0';
        local_14.left = local_1b0.left;
        local_14.top = local_1b0.top;
        local_14.right = local_1b0.right;
        local_14.bottom = local_1b0.bottom;
        sVar9 = _strlen(local_114);
        if (sVar9 == 0) {
          local_138 = local_14.left;
        }
        else {
          UVar19 = 0x424;
          ptVar17 = &local_14;
          sVar9 = _strlen(local_114);
          DrawTextA(local_144,local_114,sVar9,ptVar17,UVar19);
          local_138 = local_14.right - 1;
        }
        FUN_005f22d0(local_114,local_140);
        local_114[local_198->field_28 + 1] = '\0';
        local_14.left = local_1b0.left;
        local_14.top = local_1b0.top;
        local_14.right = local_1b0.right;
        local_14.bottom = local_1b0.bottom;
        UVar19 = 0x424;
        ptVar17 = &local_14;
        sVar9 = _strlen(local_114);
        DrawTextA(local_144,local_114,sVar9,ptVar17,UVar19);
        local_138 = local_138 + ((local_14.right + 1) - local_138 >> 1) - 5;
        local_13c = local_138 + 10;
        local_11c = GetStockObject(3);
        SelectObject(local_144,local_11c);
        MoveToEx(local_144,local_138,local_1b0.bottom - 3,(LPPOINT)0x0);
        LineTo(local_144,local_13c,local_1b0.bottom - 3);
        MoveToEx(local_144,local_138,local_1b0.bottom - 2,(LPPOINT)0x0);
        LineTo(local_144,local_13c,local_1b0.bottom - 2);
      }
      SelectObject(local_144,local_154);
      EndPaint(param_1,&local_194);
      pHVar12 = GetFocus();
      if (pHVar12 != param_1) {
        return 0;
      }
    }
    else if (param_2 != 7) {
      if (param_2 == 8) {
        wnd_redraw_client(param_1);
        return 0;
      }
LAB_005ccd4b:
      uVar14 = ctrl_default_wndproc(param_1,param_2,param_3,param_4);
      return uVar14;
    }
    pCVar13 = (WndKeyNavView *)ctrl_get_parent(local_198);
    cVar1 = wnd_keyboard_nav_enabled(pCVar13);
    if (cVar1 == '\0') {
      uVar14 = ctrl_default_wndproc(param_1,param_2,param_3,param_4);
      return uVar14;
    }
    local_144 = GetDC(param_1);
    local_11c = GetStockObject(3);
    GetClientRect(param_1,&local_1b0);
    SelectObject(local_144,local_11c);
    local_1b0.left += 0x20;
    FrameRect(local_144,&local_1b0,local_11c);
    DeleteObject(local_11c);
    ReleaseDC(param_1,local_144);
  }
  else if (param_2 == 0x100) {
    if (param_3 == 9) {
      pHVar12 = GetParent(param_1);
      SendMessageA(pHVar12,param_2,param_3,param_4);
    }
    else {
      if (param_3 == 0x20) {
        pCVar13 = (WndKeyNavView *)ctrl_get_parent(local_198);
        cVar1 = wnd_keyboard_nav_enabled(pCVar13);
        if (cVar1 != '\0') {
          SendMessageA(param_1,0x201,0,0);
          SendMessageA(param_1,0x202,0,0);
          return 0;
        }
      }
      pHVar12 = GetParent(param_1);
      SendMessageA(pHVar12,param_2,param_3,param_4);
    }
  }
  else if (param_2 == 0x201) {
    iVar5 = checkbox_is_enabled((CheckboxEnabledView *)local_198);
    if ((iVar5 != 0) && (checkbox_mouse_pressed == 0)) {
      SetFocus(param_1);
      iVar5 = checkbox_is_checked(local_198);
      if (iVar5 == 0) {
        checkbox_set_checked(local_198,1);
      }
      else {
        checkbox_set_checked(local_198,0);
      }
      checkbox_mouse_pressed = 1;
      SetCapture(param_1);
      InvalidateRect(param_1,(RECT *)0x0,0);
      iVar11 = ctrl_get_parent(local_198);
      wnd_set_active_child(iVar11);
      uVar14 = checkbox_is_checked(local_198);
      uVar2 = ctrl_get_id((ControlIdView *)local_198);
      checkbox_fire_callback((CheckboxClickView *)local_198,uVar2,uVar14);
    }
  }
  else {
    if (param_2 != 0x202) goto LAB_005ccd4b;
    iVar5 = checkbox_is_enabled((CheckboxEnabledView *)local_198);
    if (iVar5 != 0) {
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
#undef local_1b0
#undef local_1a0
#undef local_19c
#undef local_198
#undef local_194
#undef local_154
#undef local_150
#undef local_148
#undef local_144
#undef local_140
#undef local_13c
#undef local_138
#undef local_134
#undef local_130
#undef local_12c
#undef local_128
#undef local_124
#undef local_120
#undef local_11c
#undef local_118
#undef local_114
#undef local_14

/* 005cce40 auto */
void __thiscall checkbox_fire_callback(CheckboxClickView *this,undefined4 param_1,undefined4 param_2)

{
  if (this->on_toggle != 0) {
    (*(code *)this->on_toggle)(param_1,param_2);
  }
  return;
}

/* 005cce80 auto */
void __stdcall control_subclass_wndproc(HWND param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  DWORD DVar1;
  code *pcVar2;
  ControlHwndSetView *this;
  
  DVar1 = GetClassLongA(param_1,-0x12);
  pcVar2 = (code *)GetWindowLongA(param_1,DVar1 - 4);
  if ((param_2 == 2) &&
     (this = (ControlHwndSetView *)GetWindowLongA(param_1,DVar1 - 8), this != (ControlHwndSetView *)0x0)) {
    control_set_hwnd(this,0);
  }
  (*pcVar2)(param_1,param_2,param_3,param_4);
  return;
}

/* 005ccf17 auto */
#define app_hinstance (*(HINSTANCE *)((u8 *)&g.d_006e4ff0))
#define local_34 (*(uint *)(frame_ + FRAME_OFF(4)))
#define local_30 (*(WNDCLASSA *)(frame_ + FRAME_OFF(8)))
#define local_8 (*(HWND *)(frame_ + FRAME_OFF(48)))
HWND __cdecl scrollbar_create_hwnd(int *param_1,iptr param_2,uint param_3,int param_4)

{
  WndBase *pCVar1;
  iptr iVar2;
  iptr iVar3;
  int iVar4;
  int nWidth;
  HWND pHVar5;
  HMENU pHVar6;
  HINSTANCE pHVar7;
  LPVOID pvVar8;
  undefined1 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_34 = 0x40000000;
  if (param_4 != 0) {
    local_34 = 0x50000000;
  }
  if (param_3 != 0) {
    local_34 = local_34 | 1;
  }
  if (param_4 != 0) {
    param_3 = param_3 | 0x10000000;
  }
  if (scrollbar_class_registered == 0) {
    pvVar8 = (LPVOID)0x0;
    pHVar6 = (HMENU)0x0;
    pHVar7 = app_hinstance;
    pCVar1 = (WndBase *)ctrl_get_parent((Control *)param_2);
    iVar2 = wnd_get_window(pCVar1);
    pHVar5 = *(HWND *)(iVar2 + 4);
    iVar3 = rect_height((iptr)param_1);
    iVar4 = rect_width((iptr)param_1);
    local_8 = CreateWindowExA(4,s_SCROLLBAR_00637f60,&scrollbar_probe_wnd_title,param_3 | 0x40000000,*param_1,
                              param_1[1],iVar4,iVar3,pHVar5,pHVar6,pHVar7,pvVar8);
    scrollbar_base_wndproc = (WNDPROC)GetWindowLongA(local_8,-4);
    local_34 = GetWindowLongA(local_8,-0x10);
    local_30.style = 0x8b;
    local_30.lpfnWndProc = scrollbar_base_wndproc;
    local_30.cbClsExtra = 0;
    scrollbar_base_wnd_extra = GetClassLongA(local_8,-0x12);
    local_30.cbWndExtra = scrollbar_base_wnd_extra + 8;
    local_30.hInstance = app_hinstance;
    local_30.hIcon = (HICON)0x0;
    local_30.hCursor = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
    local_30.hbrBackground = GetStockObject(1);
    local_30.lpszMenuName = (LPCSTR)0x0;
    local_30.lpszClassName = s_MSScrollBarClass_00637f6c;
    RegisterClassA(&local_30);
    scrollbar_class_registered = 1;
    DestroyWindow(local_8);
  }
  pvVar8 = (LPVOID)0x0;
  pHVar6 = (HMENU)0x0;
  pHVar7 = app_hinstance;
  pCVar1 = (WndBase *)ctrl_get_parent((Control *)param_2);
  iVar4 = wnd_get_window(pCVar1);
  pHVar5 = *(HWND *)(iVar4 + 4);
  iVar4 = rect_height((iptr)param_1);
  nWidth = rect_width((iptr)param_1);
  local_8 = CreateWindowExA(4,s_MSScrollBarClass_00637f84,&scrollbar_wnd_title,local_34,*param_1,param_1[1]
                            ,nWidth,iVar4,pHVar5,pHVar6,pHVar7,pvVar8);
  SetWindowLongA(local_8,-4,ADDR(0x5cce80, control_subclass_wndproc));
  SetWindowLongA(local_8,scrollbar_base_wnd_extra,param_2);
  SetWindowLongA(local_8,scrollbar_base_wnd_extra + 4,(LONG)scrollbar_base_wndproc);
  ShowScrollBar(local_8,2,1);
  scrollbar_hwnd_set_range(local_8,1,100);
  return local_8;
}
#undef app_hinstance
#undef local_34
#undef local_30
#undef local_8

/* 005cd139 auto */
void __cdecl scrollbar_destroy_hwnd(undefined4 param_1)

{
  return;
}

/* 005cd149 auto */
void __cdecl scrollbar_hwnd_handle_msg(HWND param_1,uint param_2,uint param_3,int param_4)

{
  short sVar1;
  DWORD DVar2;
  ScrollbarPosView *this;
  iptr iVar3;
  iptr iVar4;
  WPARAM *pWVar5;
  iptr iVar5;
  int iVar6;
  u32 uVar7;
  LPARAM LVar8;
  
  DVar2 = GetClassLongA(param_1,-0x12);
  this = (ScrollbarPosView *)GetWindowLongA(param_1,DVar2 - 8);
  iVar3 = scrollbar_get_cur_pos(this);
  if (param_2 == 0x111) {
    if (param_3 == 0x7f) {
      SetScrollPos(param_1,2,param_4,1);
      uVar7 = GetScrollPos(param_1,2);
      this->cur_pos = uVar7;
    }
  }
  else if ((0x113 < param_2) && (param_2 < 0x116)) {
    sVar1 = (short)(param_3 >> 0x10);
    switch(param_3 & 0xffff) {
    case 0:
      iVar6 = input_lbutton_down();
      if (iVar6 == 0) {
        iVar6 = ctrl_get_rect(this);
        LVar8 = *(LPARAM *)(iVar6 + 4);
        pWVar5 = (WPARAM *)ctrl_get_rect(this);
        PostMessageA(param_1,0x202,*pWVar5,LVar8);
      }
      else {
        SetScrollPos(param_1,2,iVar3 - 1,1);
        uVar7 = GetScrollPos(param_1,2);
        iVar4 = ctrl_get_parent((Control *)this);
        wnd_set_active_child(iVar4);
        this->cur_pos = uVar7;
        scrollbar_fire_change((ScrollbarChangeView *)this,uVar7);
      }
      break;
    case 1:
      iVar6 = input_lbutton_down();
      if (iVar6 == 0) {
        iVar6 = ctrl_get_rect(this);
        LVar8 = *(LPARAM *)(iVar6 + 4);
        pWVar5 = (WPARAM *)ctrl_get_rect(this);
        PostMessageA(param_1,0x202,*pWVar5,LVar8);
      }
      else {
        SetScrollPos(param_1,2,iVar3 + 1,1);
        uVar7 = GetScrollPos(param_1,2);
        iVar4 = ctrl_get_parent((Control *)this);
        wnd_set_active_child(iVar4);
        this->cur_pos = uVar7;
        scrollbar_fire_change((ScrollbarChangeView *)this,uVar7);
      }
      break;
    case 2:
      iVar6 = scrollbar_get_page_size((ScrollbarPageView *)this);
      SetScrollPos(param_1,2,iVar3 - iVar6,1);
      uVar7 = GetScrollPos(param_1,2);
      iVar4 = ctrl_get_parent((Control *)this);
      wnd_set_active_child(iVar4);
      this->cur_pos = uVar7;
      scrollbar_fire_change((ScrollbarChangeView *)this,uVar7);
      break;
    case 3:
      iVar5 = scrollbar_get_page_size((ScrollbarPageView *)this);
      SetScrollPos(param_1,2,iVar3 + iVar5,1);
      uVar7 = GetScrollPos(param_1,2);
      iVar4 = ctrl_get_parent((Control *)this);
      wnd_set_active_child(iVar4);
      this->cur_pos = uVar7;
      scrollbar_fire_change((ScrollbarChangeView *)this,uVar7);
      break;
    case 4:
      SetScrollPos(param_1,2,(int)sVar1,1);
      iVar4 = ctrl_get_parent((Control *)this);
      wnd_set_active_child(iVar4);
      this->cur_pos = (int)sVar1;
      scrollbar_fire_change((ScrollbarChangeView *)this,this->cur_pos);
      break;
    case 5:
      iVar4 = ctrl_get_parent((Control *)this);
      wnd_set_active_child(iVar4);
      scrollbar_fire_track((ScrollbarTrackView *)this,(int)sVar1);
    }
  }
  return;
}

/* 005cd4c7 auto */
void __cdecl scrollbar_hwnd_set_range(HWND param_1,int param_2,int param_3)

{
  SetScrollRange(param_1,2,param_2,param_3,1);
  scrollbar_hwnd_set_pos(param_1,param_2);
  return;
}

/* 005cd535 auto */
void __cdecl scrollbar_hwnd_get_range(HWND param_1,LPINT param_2,LPINT param_3)

{
  GetScrollRange(param_1,2,param_2,param_3);
  return;
}

/* 005cd559 auto */
void __cdecl scrollbar_hwnd_set_pos(undefined4 param_1,undefined4 param_2)

{
  scrollbar_hwnd_handle_msg(param_1,0x111,0x7f,param_2);
  return;
}

/* 005cd620 auto */
u32 __thiscall scrollbar_get_cur_pos(ScrollbarPosView *this)

{
  return this->cur_pos;
}

/* 005cd640 auto */
void __thiscall scrollbar_fire_change(ScrollbarChangeView *this,undefined4 param_1)

{
  if (this->on_change != 0) {
    (*(code *)this->on_change)(param_1);
  }
  return;
}

/* 005cd680 auto */
void __thiscall scrollbar_fire_track(ScrollbarTrackView *this,undefined4 param_1)

{
  if (this->on_track != 0) {
    (*(code *)this->on_track)(param_1);
  }
  return;
}

/* 005cd6c0 auto */
u32 __thiscall scrollbar_get_page_size(ScrollbarPageView *this)

{
  return this->page_size;
}

/* 005d25c0 auto */
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(4)))
void __thiscall
edit_create_at
          (EditControl *this,iptr param_1,undefined4 param_2,int param_3,int param_4,int param_5,
          iptr param_6)

{
  undefined1 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  this->edit_font = (u32)ctrl_default_font;
  this->is_enabled = 0;
  SetRect(&local_14,param_3,param_4,param_5 + param_3,param_4 + 0x1e);
  edit_create(this,param_1,param_2,(iptr)&local_14,param_6);
  return;
}
#undef local_14

/* 005d2740 auto */
#define app_hinstance (*(HINSTANCE *)((u8 *)&g.d_006e4ff0))
#define local_34 (*(WNDCLASSA *)(frame_ + FRAME_OFF(4)))
#define local_c (*(HWND *)(frame_ + FRAME_OFF(44)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(48)))
HWND __cdecl edit_create_window(int *param_1,iptr param_2,uint param_3,int param_4,GameFont *param_5)

{
  WndBase *pCVar1;
  iptr iVar2;
  iptr iVar3;
  int iVar4;
  int nWidth;
  undefined4 uVar5;
  WPARAM *pWVar6;
  HWND pHVar7;
  HMENU pHVar8;
  HINSTANCE pHVar9;
  LPVOID pvVar10;
  undefined1 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0x40800000;
  if (param_4 != 0) {
    local_8 = 0x50800000;
  }
  if ((param_3 & 1) != 0) {
    local_8 = local_8 | 0x80;
  }
  if (((param_3 & 2) != 0) || ((param_3 & 0x200) != 0)) {
    local_8 = local_8 | 4;
    *(undefined1 *)(param_2 + 0x38) = 1;
    if ((param_3 & 0x200) != 0) {
      *(undefined1 *)(param_2 + 0x39) = 1;
    }
  }
  if ((param_3 & 4) != 0) {
    local_8 = local_8 | 0xa0;
  }
  if ((param_3 & 8) != 0) {
    local_8 = local_8 | 8;
  }
  if ((param_3 & 0x10) != 0) {
    local_8 = local_8 | 0x10;
  }
  if ((param_3 & 0x20) != 0) {
    local_8 = local_8 | 0x200040;
  }
  if ((param_3 & 0x40) != 0) {
    local_8 = local_8 | 0x100080;
  }
  if ((param_3 & 0x80) != 0) {
    local_8 = local_8 | 0x1000;
  }
  if ((param_3 & 0x100) != 0) {
    local_8 = local_8 | 0x800;
  }
  *(uint *)(param_2 + 0x3c) = local_8;
  if (editbox_class_registered == 0) {
    pvVar10 = (LPVOID)0x0;
    pHVar8 = (HMENU)0x0;
    pHVar9 = app_hinstance;
    pCVar1 = (WndBase *)ctrl_get_parent((Control *)param_2);
    iVar2 = wnd_get_window(pCVar1);
    pHVar7 = *(HWND *)(iVar2 + 4);
    iVar3 = rect_height((iptr)param_1);
    iVar4 = rect_width((iptr)param_1);
    local_c = CreateWindowExA(4,&editbox_native_class_name,&editbox_probe_wnd_title,local_8,*param_1,param_1[1],iVar4,iVar3,
                              pHVar7,pHVar8,pHVar9,pvVar10);
    edit_base_wndproc = (WNDPROC)GetWindowLongA(local_c,-4);
    local_34.style = 0x88;
    local_34.cbClsExtra = 0;
    local_34.lpfnWndProc = edit_base_wndproc;
    edit_base_wnd_extra = GetClassLongA(local_c,-0x12);
    local_34.cbWndExtra = edit_base_wnd_extra + 8;
    local_34.hInstance = app_hinstance;
    local_34.hIcon = (HICON)0x0;
    local_34.hCursor = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f01);
    local_34.hbrBackground = (HBRUSH)0x0;
    local_34.lpszMenuName = (LPCSTR)0x0;
    local_34.lpszClassName = s_MSEditBoxClass_00638324;
    RegisterClassA(&local_34);
    editbox_class_registered = 1;
    DestroyWindow(local_c);
  }
  pvVar10 = (LPVOID)0x0;
  pHVar8 = (HMENU)0x0;
  pHVar9 = app_hinstance;
  pCVar1 = (WndBase *)ctrl_get_parent((Control *)param_2);
  iVar4 = wnd_get_window(pCVar1);
  pHVar7 = *(HWND *)(iVar4 + 4);
  iVar4 = rect_height((iptr)param_1);
  nWidth = rect_width((iptr)param_1);
  local_c = CreateWindowExA(4,s_MSEditBoxClass_00638338,&editbox_wnd_title,local_8 | 0x40800000,*param_1,
                            param_1[1],nWidth,iVar4,pHVar7,pHVar8,pHVar9,pvVar10);
  uVar5 = font_get_handle(param_5);
  pWVar6 = (WPARAM *)mem_handle_lock(uVar5);
  SendMessageA(local_c,0x30,*pWVar6,0);
  uVar5 = font_get_handle(param_5);
  mem_handle_unlock(uVar5);
  SetWindowLongA(local_c,-4,ADDR(0x5d2a01, edit_subclass_wndproc));
  SetWindowLongA(local_c,edit_base_wnd_extra,(LONG)edit_base_wndproc);
  SetWindowLongA(local_c,edit_base_wnd_extra + 4,param_2);
  return local_c;
}
#undef app_hinstance
#undef local_34
#undef local_c
#undef local_8

/* 005d2a01 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
LRESULT __stdcall edit_subclass_wndproc(HWND param_1,uint param_2,WPARAM param_3,LPARAM param_4)

{
  Control *this;
  DWORD DVar1;
  WNDPROC lpPrevWndFunc;
  iptr iVar2;
  HWND pHVar2;
  iptr iVar3;
  WndBase *this_00;
  int iVar4;
  LRESULT LVar5;
  iptr iVar5;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  this = (Control *)GetWindowLongA(param_1,10);
  DVar1 = GetClassLongA(param_1,-0x12);
  lpPrevWndFunc = (WNDPROC)GetWindowLongA(param_1,DVar1 - 8);
  if (param_2 < 8) {
    if (param_2 == 7) {
      iVar3 = ctrl_get_parent(this);
      wnd_set_active_child(iVar3);
      if ((char)this->font == '\0') {
        edit_hwnd_set_sel(param_1,0,0xffffffff);
      }
      LVar5 = CallWindowProcA(lpPrevWndFunc,param_1,7,param_3,param_4);
      return LVar5;
    }
    if (param_2 == 2) {
      if (this != (Control *)0x0) {
        control_set_hwnd((ControlHwndSetView *)this,0);
      }
      LVar5 = CallWindowProcA(lpPrevWndFunc,param_1,2,param_3,param_4);
      return LVar5;
    }
  }
  else if (param_2 < 0x202) {
    if (param_2 == 0x201) {
LAB_005d2c05:
      iVar5 = 0;
      pHVar2 = GetParent(param_1);
      this_00 = (WndBase *)GetWindowLongA(pHVar2,iVar5);
      iVar4 = wnd_get_window(this_00);
      if ((*(byte *)(iVar4 + 0x49) & 2) != 0) {
        pHVar2 = GetParent(param_1);
        SetFocus(pHVar2);
        pHVar2 = GetParent(param_1);
        BringWindowToTop(pHVar2);
      }
      LVar5 = CallWindowProcA(lpPrevWndFunc,param_1,param_2,param_3,param_4);
      return LVar5;
    }
    if (param_2 == 0x100) {
      if (((param_3 != 9) && (param_3 != 0xd)) && (param_3 != 0x1b)) {
        LVar5 = CallWindowProcA(lpPrevWndFunc,param_1,0x100,param_3,param_4);
        return LVar5;
      }
      pHVar2 = GetParent(param_1);
      SendMessageA(pHVar2,param_2,param_3,param_4);
      return 1;
    }
    if (param_2 == 0x101) {
      iVar3 = ctrl_get_parent(this);
      wnd_set_active_child(iVar3);
      iVar2 = input_map_vkey(param_3);
      if ((0x2af < iVar2) && (iVar2 < 0x2b5)) {
        edit_fire_key_callback((EditKeyView *)this,iVar2);
      }
      LVar5 = CallWindowProcA(lpPrevWndFunc,param_1,0x101,param_3,param_4);
      return LVar5;
    }
    if (param_2 == 0x102) {
      iVar3 = ctrl_get_parent(this);
      wnd_set_active_child(iVar3);
      local_8 = 0;
      if (param_3 != 9) {
        iVar3 = input_map_vkey(param_3);
        local_8 = edit_fire_key_callback((EditKeyView *)this,iVar3);
      }
      if (local_8 == 0) {
        return 1;
      }
      LVar5 = CallWindowProcA(lpPrevWndFunc,param_1,0x102,param_3,param_4);
      return LVar5;
    }
  }
  else if (param_2 == 0x204) goto LAB_005d2c05;
  LVar5 = CallWindowProcA(lpPrevWndFunc,param_1,param_2,param_3,param_4);
  return LVar5;
}
#undef local_8

/* 005d2d3d auto */
void __cdecl edit_hwnd_cleanup_stub(undefined4 param_1)

{
  return;
}

/* 005d2da1 auto */
void __cdecl edit_hwnd_limit_text(HWND param_1,WPARAM param_2)

{
  SendMessageA(param_1,0xc5,param_2,0);
  return;
}

/* 005d2dc6 auto */
void __cdecl edit_hwnd_set_sel(HWND param_1,WPARAM param_2,LPARAM param_3)

{
  SendMessageA(param_1,0xb1,param_2,param_3);
  return;
}

/* 005d2ded auto */
iptr __cdecl edit_hwnd_get_line(HWND param_1,WPARAM param_2,short *param_3,undefined4 param_4)

{
  iptr LVar1;
  
  *param_3 = (short)param_4 - 1;
  LVar1 = SendMessageA(param_1,0xc4,param_2,(LPARAM)param_3);
  *(undefined1 *)(LVar1 + (int)param_3) = 0;
  return LVar1;
}

/* 005d2e31 auto */
LRESULT __cdecl edit_hwnd_get_line_count(HWND param_1)

{
  LRESULT LVar1;
  
  LVar1 = SendMessageA(param_1,0xba,0,0);
  return LVar1;
}

/* 005d2e9c auto */
LRESULT __cdecl edit_line_index(HWND param_1,WPARAM param_2)

{
  LRESULT LVar1;
  
  LVar1 = SendMessageA(param_1,0xbb,param_2,0);
  return LVar1;
}

/* 005d2ec1 auto */
LRESULT __cdecl edit_line_length(HWND param_1,WPARAM param_2)

{
  LRESULT LVar1;
  
  LVar1 = SendMessageA(param_1,0xc1,param_2,0);
  return LVar1;
}

/* 005d2f0d auto */
void __cdecl edit_hwnd_set_caret(HWND param_1,WPARAM param_2)

{
  SendMessageA(param_1,0xb1,param_2,param_2);
  SendMessageA(param_1,0xb7,0,0);
  return;
}

/* 005d2f47 auto */
uint __cdecl edit_ctl_get_sel_end(HWND param_1)

{
  uint uVar1;
  
  uVar1 = SendMessageA(param_1,0xb0,0,0);
  return uVar1 >> 0x10;
}

/* 005d2f7e auto */
int __cdecl edit_hwnd_get_text_end(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = edit_hwnd_get_line_count(param_1);
  iVar1 = edit_line_index(param_1,iVar1 - 1);
  iVar2 = edit_line_length(param_1,iVar1);
  return iVar1 + iVar2;
}

/* 005d3035 auto */
void __cdecl edit_hwnd_replace_sel(HWND param_1,LPARAM param_2)

{
  SendMessageA(param_1,0xc2,0,param_2);
  return;
}

/* 005d30e0 auto */
undefined4 __thiscall edit_fire_key_callback(EditKeyView *this,iptr param_1)

{
  undefined4 uVar1;
  
  if (this->on_key == 0) {
    uVar1 = 1;
  }
  else {
    uVar1 = (*(code *)this->on_key)(this->control_id,param_1);
  }
  return uVar1;
}

/* 005d3130 auto */
#define app_hinstance (*(HINSTANCE *)((u8 *)&g.d_006e4ff0))
#define local_34 (*(DWORD *)(frame_ + FRAME_OFF(4)))
#define local_30 (*(WNDCLASSA *)(frame_ + FRAME_OFF(8)))
#define local_8 (*(HWND *)(frame_ + FRAME_OFF(48)))
HWND __cdecl combo_create_window(int *param_1,iptr param_2,int param_3)

{
  WndBase *pCVar1;
  iptr iVar2;
  iptr iVar3;
  int iVar4;
  int nWidth;
  HWND pHVar5;
  HMENU pHVar6;
  HINSTANCE pHVar7;
  LPVOID pvVar8;
  undefined1 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_34 = 0x40a10003;
  if (param_3 != 0) {
    local_34 = 0x50a10003;
  }
  if (combo_class_registered == 0) {
    pvVar8 = (LPVOID)0x0;
    pHVar6 = (HMENU)0x0;
    pHVar7 = app_hinstance;
    pCVar1 = (WndBase *)ctrl_get_parent((Control *)param_2);
    iVar2 = wnd_get_window(pCVar1);
    pHVar5 = *(HWND *)(iVar2 + 4);
    iVar3 = rect_height((iptr)param_1);
    iVar4 = rect_width((iptr)param_1);
    local_8 = CreateWindowExA(4,s_COMBOBOX_00638350,&combo_probe_wnd_title,local_34,*param_1,param_1[1],iVar4
                              ,iVar3,pHVar5,pHVar6,pHVar7,pvVar8);
    combo_base_wndproc = (WNDPROC)GetWindowLongA(local_8,-4);
    local_30.style = 0x88;
    local_30.cbClsExtra = 0;
    local_30.lpfnWndProc = combo_base_wndproc;
    combo_base_wnd_extra = GetClassLongA(local_8,-0x12);
    local_30.cbWndExtra = combo_base_wnd_extra + 8;
    local_30.hInstance = app_hinstance;
    local_30.hIcon = (HICON)0x0;
    local_30.hCursor = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
    local_30.hbrBackground = (HBRUSH)0x0;
    local_30.lpszMenuName = (LPCSTR)0x0;
    local_30.lpszClassName = s_MSComboBoxClass_0063835c;
    RegisterClassA(&local_30);
    combo_class_registered = 1;
    DestroyWindow(local_8);
  }
  local_34 = 0x40a10203;
  if (param_3 != 0) {
    local_34 = 0x50a10203;
  }
  pvVar8 = (LPVOID)0x0;
  pHVar6 = (HMENU)0x0;
  pHVar7 = app_hinstance;
  pCVar1 = (WndBase *)ctrl_get_parent((Control *)param_2);
  iVar4 = wnd_get_window(pCVar1);
  pHVar5 = *(HWND *)(iVar4 + 4);
  iVar4 = rect_height((iptr)param_1);
  nWidth = rect_width((iptr)param_1);
  local_8 = CreateWindowExA(4,s_MSComboBoxClass_00638370,&combo_wnd_title,local_34,*param_1,param_1[1],
                            nWidth,iVar4,pHVar5,pHVar6,pHVar7,pvVar8);
  SetWindowLongA(local_8,-4,ADDR(0x5d3310, combo_subclass_wndproc));
  SetWindowLongA(local_8,combo_base_wnd_extra,(LONG)combo_base_wndproc);
  SetWindowLongA(local_8,combo_base_wnd_extra + 4,param_2);
  return local_8;
}
#undef app_hinstance
#undef local_34
#undef local_30
#undef local_8

/* 005d3310 auto */
LRESULT __stdcall combo_subclass_wndproc(HWND param_1,uint param_2,uint param_3,LPARAM param_4)

{
  DWORD DVar1;
  WNDPROC lpPrevWndFunc;
  Control *this;
  iptr iVar2;
  HWND pHVar3;
  WndBase *this_00;
  iptr iVar4;
  LRESULT LVar4;
  iptr iVar5;
  
  DVar1 = GetClassLongA(param_1,-0x12);
  lpPrevWndFunc = (WNDPROC)GetWindowLongA(param_1,DVar1 - 8);
  this = (Control *)GetWindowLongA(param_1,DVar1 - 4);
  if (this == (Control *)0x0) {
    return 1;
  }
  iVar2 = ctrl_get_parent(this);
  wnd_set_active_child(iVar2);
  if (param_2 < 0x103) {
    if (0xff < param_2) {
      if (((param_3 != 9) && (param_3 != 0xd)) && (param_3 != 0x1b)) {
        LVar4 = CallWindowProcA(lpPrevWndFunc,param_1,param_2,param_3,param_4);
        return LVar4;
      }
      pHVar3 = GetParent(param_1);
      SendMessageA(pHVar3,param_2,param_3,param_4);
      return 1;
    }
    if (param_2 == 2) {
      if (this != (Control *)0x0) {
        control_set_hwnd((ControlHwndSetView *)this,0);
      }
      LVar4 = CallWindowProcA(lpPrevWndFunc,param_1,2,param_3,param_4);
      return LVar4;
    }
  }
  else {
    if ((param_2 == 0x201) || (param_2 == 0x204)) {
      iVar5 = 0;
      pHVar3 = GetParent(param_1);
      this_00 = (WndBase *)GetWindowLongA(pHVar3,iVar5);
      iVar4 = wnd_get_window(this_00);
      if ((*(byte *)(iVar4 + 0x49) & 2) != 0) {
        pHVar3 = GetParent(param_1);
        SetFocus(pHVar3);
        pHVar3 = GetParent(param_1);
        BringWindowToTop(pHVar3);
      }
      LVar4 = CallWindowProcA(lpPrevWndFunc,param_1,param_2,param_3,param_4);
      return LVar4;
    }
    if (param_2 == 0x4c8) {
      if (param_3 >> 0x10 == 1) {
        if (this == (Control *)0x0) {
          return 1;
        }
        combo_fire_selchange((ComboBoxSelChangeView *)this);
        return 1;
      }
      if (param_3 >> 0x10 != 2) {
        return 1;
      }
      combo_fire_dblclick((ComboBoxDblClickView *)this);
      return 1;
    }
  }
  LVar4 = CallWindowProcA(lpPrevWndFunc,param_1,param_2,param_3,param_4);
  return LVar4;
}

/* 005d356e auto */
void __cdecl combo_hwnd_cleanup_stub(undefined4 param_1)

{
  return;
}

/* 005d357e auto */
void __cdecl combo_hwnd_add_string(HWND param_1,LPARAM param_2)

{
  SendMessageA(param_1,0x143,0,param_2);
  return;
}

/* 005d35c8 auto */
void __cdecl combo_hwnd_set_font(HWND param_1,undefined4 param_2)

{
  WPARAM *pWVar1;
  
  pWVar1 = (WPARAM *)mem_handle_lock(param_2);
  SendMessageA(param_1,0x30,*pWVar1,0);
  mem_handle_unlock(param_2);
  return;
}

/* 005d360a auto */
void __cdecl combo_hwnd_clear(HWND param_1)

{
  SendMessageA(param_1,0x14b,0,0);
  return;
}

/* 005d36b1 auto */
LRESULT __cdecl combo_hwnd_get_cur_sel(HWND param_1)

{
  LRESULT LVar1;
  
  LVar1 = SendMessageA(param_1,0x147,0,0);
  if (LVar1 == -1) {
    LVar1 = -1;
  }
  return LVar1;
}

/* 005d36f6 auto */
void __cdecl combo_hwnd_set_cur_sel(HWND param_1,WPARAM param_2)

{
  SendMessageA(param_1,0x14e,param_2,0);
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
#define local_38 (*(uint *)(frame_ + FRAME_OFF(0)))
#define local_30 (*(WNDCLASSA *)(frame_ + FRAME_OFF(8)))
#define local_8 (*(HWND *)(frame_ + FRAME_OFF(48)))
HWND __cdecl listbox_create_hwnd(int *param_1,iptr param_2,int param_3,int param_4,GameFont *param_5)

{
  uint uVar1;
  WndBase *pCVar2;
  iptr iVar3;
  iptr iVar4;
  int iVar5;
  int nWidth;
  undefined4 uVar6;
  WPARAM *pWVar7;
  HWND pHVar8;
  HMENU pHVar9;
  HINSTANCE pHVar10;
  LPVOID pvVar11;
  undefined1 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_38 = 0;
  if (param_4 == 1) {
    local_38 = 0x800;
  }
  uVar1 = local_38 | 0x40a10000;
  if (param_3 != 0) {
    uVar1 = local_38 | 0x50a10000;
  }
  local_38 = uVar1;
  if (listbox_class_registered == 0) {
    pvVar11 = (LPVOID)0x0;
    pHVar9 = (HMENU)0x0;
    pHVar10 = app_hinstance;
    pCVar2 = (WndBase *)ctrl_get_parent((Control *)param_2);
    iVar3 = wnd_get_window(pCVar2);
    pHVar8 = *(HWND *)(iVar3 + 4);
    iVar4 = rect_height((iptr)param_1);
    iVar5 = rect_width((iptr)param_1);
    local_8 = CreateWindowExA(4,s_LISTBOX_0063838c,&listbox_probe_wnd_title,local_38,*param_1,param_1[1],iVar5,
                              iVar4,pHVar8,pHVar9,pHVar10,pvVar11);
    listbox_base_wndproc = (WNDPROC)GetWindowLongA(local_8,-4);
    local_30.style = 0x88;
    local_30.cbClsExtra = 0;
    local_30.lpfnWndProc = listbox_base_wndproc;
    listbox_base_wnd_extra = GetClassLongA(local_8,-0x12);
    local_30.cbWndExtra = listbox_base_wnd_extra + 8;
    local_30.hInstance = app_hinstance;
    local_30.hIcon = (HICON)0x0;
    local_30.hCursor = LoadCursorA((HINSTANCE)0x0,(LPCSTR)0x7f00);
    local_30.hbrBackground = (HBRUSH)0x0;
    local_30.lpszMenuName = (LPCSTR)0x0;
    local_30.lpszClassName = s_MSListBoxClass_00638394;
    RegisterClassA(&local_30);
    listbox_class_registered = 1;
    DestroyWindow(local_8);
  }
  local_38 = 0x40a10001;
  if (param_3 != 0) {
    local_38 = 0x50a10001;
  }
  if (param_4 == 1) {
    local_38 = local_38 | 0x800;
  }
  pvVar11 = (LPVOID)0x0;
  pHVar9 = (HMENU)0x0;
  pHVar10 = app_hinstance;
  pCVar2 = (WndBase *)ctrl_get_parent((Control *)param_2);
  iVar5 = wnd_get_window(pCVar2);
  pHVar8 = *(HWND *)(iVar5 + 4);
  iVar5 = rect_height((iptr)param_1);
  nWidth = rect_width((iptr)param_1);
  local_8 = CreateWindowExA(4,s_MSListBoxClass_006383a8,&listbox_wnd_title,local_38,*param_1,param_1[1],
                            nWidth,iVar5,pHVar8,pHVar9,pHVar10,pvVar11);
  uVar6 = font_get_handle(param_5);
  pWVar7 = (WPARAM *)mem_handle_lock(uVar6);
  SendMessageA(local_8,0x30,*pWVar7,0);
  uVar6 = font_get_handle(param_5);
  mem_handle_unlock(uVar6);
  SetWindowLongA(local_8,-4,ADDR(0x5d39e2, listbox_subclass_wndproc));
  SetWindowLongA(local_8,listbox_base_wnd_extra,(LONG)listbox_base_wndproc);
  SetWindowLongA(local_8,listbox_base_wnd_extra + 4,param_2);
  return local_8;
}
#undef app_hinstance
#undef local_38
#undef local_30
#undef local_8

/* 005d39e2 auto */
LRESULT __stdcall listbox_subclass_wndproc(HWND param_1,uint param_2,uint param_3,LPARAM param_4)

{
  DWORD DVar1;
  WNDPROC lpPrevWndFunc;
  Control *this;
  iptr iVar2;
  HWND pHVar3;
  WndBase *this_00;
  iptr iVar4;
  LRESULT LVar4;
  iptr iVar5;
  
  DVar1 = GetClassLongA(param_1,-0x12);
  lpPrevWndFunc = (WNDPROC)GetWindowLongA(param_1,DVar1 - 8);
  this = (Control *)GetWindowLongA(param_1,DVar1 - 4);
  if (this == (Control *)0x0) {
    return 1;
  }
  iVar2 = ctrl_get_parent(this);
  wnd_set_active_child(iVar2);
  if (param_2 < 0x103) {
    if (0xff < param_2) {
      if (((param_3 != 9) && (param_3 != 0xd)) && (param_3 != 0x1b)) {
        LVar4 = CallWindowProcA(lpPrevWndFunc,param_1,param_2,param_3,param_4);
        return LVar4;
      }
      pHVar3 = GetParent(param_1);
      SendMessageA(pHVar3,param_2,param_3,param_4);
      return 1;
    }
    if (param_2 == 2) {
      if (this != (Control *)0x0) {
        control_set_hwnd((ControlHwndSetView *)this,0);
      }
      LVar4 = CallWindowProcA(lpPrevWndFunc,param_1,2,param_3,param_4);
      return LVar4;
    }
  }
  else {
    if ((param_2 == 0x201) || (param_2 == 0x204)) {
      iVar5 = 0;
      pHVar3 = GetParent(param_1);
      this_00 = (WndBase *)GetWindowLongA(pHVar3,iVar5);
      iVar4 = wnd_get_window(this_00);
      if ((*(byte *)(iVar4 + 0x49) & 2) != 0) {
        pHVar3 = GetParent(param_1);
        SetFocus(pHVar3);
        pHVar3 = GetParent(param_1);
        BringWindowToTop(pHVar3);
      }
      LVar4 = CallWindowProcA(lpPrevWndFunc,param_1,param_2,param_3,param_4);
      return LVar4;
    }
    if (param_2 == 0x4c8) {
      if (param_3 >> 0x10 == 1) {
        if (this == (Control *)0x0) {
          return 1;
        }
        listbox_fire_selchange((ListBoxSelChangeView *)this);
        return 1;
      }
      if (param_3 >> 0x10 != 2) {
        return 1;
      }
      listbox_fire_dblclick((ListBoxDblClickView *)this);
      return 1;
    }
  }
  LVar4 = CallWindowProcA(lpPrevWndFunc,param_1,param_2,param_3,param_4);
  return LVar4;
}

/* 005d3c40 auto */
void __cdecl listbox_hwnd_cleanup_stub(undefined4 param_1)

{
  return;
}

/* 005d3c50 auto */
void __cdecl listbox_hwnd_add_string(HWND param_1,LPARAM param_2)

{
  SendMessageA(param_1,0x180,0,param_2);
  return;
}

/* 005d3c9a auto */
void __cdecl listbox_hwnd_set_font(HWND param_1,undefined4 param_2)

{
  WPARAM *pWVar1;
  
  pWVar1 = (WPARAM *)mem_handle_lock(param_2);
  SendMessageA(param_1,0x30,*pWVar1,0);
  mem_handle_unlock(param_2);
  return;
}

/* 005d3cdc auto */
void __cdecl listbox_hwnd_clear(HWND param_1)

{
  SendMessageA(param_1,0x184,0,0);
  return;
}

/* 005d3cff auto */
void __cdecl listbox_hwnd_get_text(HWND param_1,WPARAM param_2,LPARAM param_3)

{
  SendMessageA(param_1,0x189,param_2,param_3);
  return;
}

/* 005d3d62 auto */
void __cdecl listbox_hwnd_get_sel_text(HWND param_1,undefined4 param_2)

{
  LRESULT LVar1;
  
  LVar1 = SendMessageA(param_1,0x188,0,0);
  if (LVar1 == -1) {
    FUN_005f22d0(param_2,&listbox_no_sel_text);
  }
  else {
    listbox_hwnd_get_text(param_1,LVar1,param_2);
  }
  return;
}

/* 005d3dbf auto */
LRESULT __cdecl listbox_hwnd_get_cur_sel(HWND param_1)

{
  LRESULT LVar1;
  
  LVar1 = SendMessageA(param_1,0x188,0,0);
  if (LVar1 == -1) {
    LVar1 = -1;
  }
  return LVar1;
}

/* 005d3e92 auto */
void __cdecl listbox_hwnd_set_cur_sel(HWND param_1,WPARAM param_2)

{
  SendMessageA(param_1,0x186,param_2,0);
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
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall radiogrp_show_all(RadioGroupShowView *this)

{
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; local_8 < (int)this->item_count; local_8++) {
    hwnd_show(*(undefined4 *)(this->items + local_8 * 0xa4));
    wnd_invalidate(*(undefined4 *)(this->items + local_8 * 0xa4));
  }
  return;
}
#undef local_8

/* 005d4167 auto */
void __cdecl ctrl_set_pending_font(iptr param_1)

{
  radio_default_font = (undefined *)param_1;
  return;
}

/* 005d7cb0 auto */
#define gfx_black_color_index (*(byte *)((u8 *)&g.d_00638b40))
#define local_74 (*(undefined1 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_64 (*(undefined1 (*)[16])(frame_ + FRAME_OFF(20)))
#define local_54 (*(undefined4 *)(frame_ + FRAME_OFF(36)))
#define local_50 (*(undefined4 *)(frame_ + FRAME_OFF(40)))
#define local_4c (*(undefined4 *)(frame_ + FRAME_OFF(44)))
#define local_48 (*(undefined4 *)(frame_ + FRAME_OFF(48)))
#define local_44 (*(int *)(frame_ + FRAME_OFF(52)))
#define local_40 (*(int *)(frame_ + FRAME_OFF(56)))
#define local_3c (*(tagRECT *)(frame_ + FRAME_OFF(60)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(76)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(80)))
#define local_24 (*(tagRECT *)(frame_ + FRAME_OFF(84)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(100)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(104)))
#define local_c (*(int *)(frame_ + FRAME_OFF(108)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(112)))
void __thiscall
spritebtn_init_from_sprite
          (SpriteButton *this,WndPaletteView *param_1,undefined4 param_2,int param_3,int param_4,
          int param_5,int param_6,iptr param_7,uint param_8)

{
  u32 uVar1;
  int iVar2;
  WndPaletteView *pCVar3;
  undefined4 uVar4;
  int yBottom;
  undefined1 frame_[FRAME_OFF(120)] __attribute__((aligned(8)));  /* original stack frame */
  
  this->field_c8 = '\0';
  uVar1 = wnd_get_palette(param_1);
  this->ctrl_palette = uVar1;
  SetRect(&local_3c,param_3,param_4,param_5 + param_3,param_4 + param_6);
  ctrl_init((Control *)this,(iptr)param_1,6,param_2,(iptr)&local_3c);
  this->is_enabled = 0;
  this->on_click = 0;
  gfx_get_scale_ratio((iptr)&local_48,(iptr)&local_4c);
  gfx_set_scale_ratio(1,1);
  surface_create((DibSurface *)(this->pad_50 + 0x2c),param_5,param_6);
  surface_create((DibSurface *)&this->on_select,param_5,param_6);
  surface_fill((DibSurface *)(this->pad_50 + 0x2c),param_8 & 0xff);
  surface_fill((DibSurface *)&this->on_select,param_8 & 0xff);
  local_40 = param_5 >> 1;
  local_44 = param_6 >> 1;
  sprite_get_origin((SpriteOriginGetView *)param_7,(iptr)&local_50,(iptr)&local_54);
  local_28 = sprite_get_width((Sprite *)param_7);
  local_28 = local_28 >> 1;
  local_2c = sprite_get_height((Sprite *)param_7);
  local_2c = local_2c >> 1;
  sprite_set_origin((SpriteOriginSetView *)param_7,-local_28,-local_2c);
  sprite_draw
            ((Sprite *)param_7,(iptr)local_64,(iptr)(this->pad_50 + 0x2c),local_40,local_44);
  sprite_draw
            ((Sprite *)param_7,(iptr)local_74,(iptr)&this->on_select,local_40,local_44);
  sprite_set_origin((SpriteOriginSetView *)param_7,local_50,local_54);
  gfx_set_scale_ratio(local_48,local_4c);
  iVar2 = surface_height((DibSurface *)(this->pad_50 + 0x2c));
  yBottom = param_4 + iVar2 - 1;
  iVar2 = surface_width((DibSurface *)(this->pad_50 + 0x2c));
  SetRect(&local_3c,param_3,param_4,param_3 + iVar2 - 1,yBottom);
  OffsetRect(&local_3c,-local_3c.left,-local_3c.top);
  local_24.left = local_3c.left;
  local_24.top = local_3c.top;
  local_24.right = local_3c.right;
  local_24.bottom = local_3c.bottom;
  SetRect(&local_24,local_3c.left,local_3c.top,local_3c.right - 2,local_3c.bottom - 2);
  local_14 = local_24.left;
  local_10 = local_24.top;
  local_c = local_24.right;
  local_8 = local_24.bottom;
  OffsetRect(&local_24,2,2);
  surface_fill((DibSurface *)(this->pad_50 + 0x2c),(uint)gfx_black_color_index);
  surface_blit
            ((DibSurface *)&this->on_select,(iptr)(this->pad_50 + 0x2c),(iptr)&local_14,
             (iptr)&local_24);
  pCVar3 = (WndPaletteView *)ctrl_get_parent((Control *)this);
  uVar4 = wnd_get_palette(pCVar3);
  surface_apply_palette((DibSurface *)(this->pad_50 + 0x2c),uVar4);
  pCVar3 = (WndPaletteView *)ctrl_get_parent((Control *)this);
  uVar4 = wnd_get_palette(pCVar3);
  surface_apply_palette((DibSurface *)&this->on_select,uVar4);
  uVar1 = spritebtn_create_hwnd(param_3,param_4,param_5,param_6,(iptr)this,1);
  this->hwnd = uVar1;
  return;
}
#undef gfx_black_color_index
#undef local_74
#undef local_64
#undef local_54
#undef local_50
#undef local_4c
#undef local_48
#undef local_44
#undef local_40
#undef local_3c
#undef local_2c
#undef local_28
#undef local_24
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 005d8da1 auto */
#define local_4c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_40 (*(tagTEXTMETRICA *)(frame_ + FRAME_OFF(16)))
#define local_8 (*(undefined4 * *)(frame_ + FRAME_OFF(72)))
int __cdecl radiogrp_item_height(GameFont *param_1)

{
  HDC hdc;
  HDC hdc_00;
  undefined4 uVar1;
  undefined1 frame_[FRAME_OFF(80)] __attribute__((aligned(8)));  /* original stack frame */
  
  hdc = GetDC((HWND)0x0);
  hdc_00 = CreateCompatibleDC(hdc);
  ReleaseDC((HWND)0x0,hdc);
  uVar1 = font_get_handle(param_1);
  local_8 = (undefined4 *)mem_handle_lock(uVar1);
  SelectObject(hdc_00,(HGDIOBJ)*local_8);
  uVar1 = font_get_handle(param_1);
  mem_handle_unlock(uVar1);
  GetTextMetricsA(hdc_00,&local_40);
  local_4c = local_40.tmHeight;
  DeleteDC(hdc_00);
  if (local_40.tmHeight < 0x14) {
    local_4c = 0x14;
  }
  return local_4c;
}
#undef local_4c
#undef local_40
#undef local_8

/* 005d8e3f auto */
#define app_hinstance (*(HINSTANCE *)((u8 *)&g.d_006e4ff0))
#define local_44 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_40 (*(DWORD *)(frame_ + FRAME_OFF(8)))
#define local_28 (*(uint *)(frame_ + FRAME_OFF(32)))
#define local_18 (*(char * *)(frame_ + FRAME_OFF(48)))
#define local_10 (*(char * *)(frame_ + FRAME_OFF(56)))
#define local_c (*(char (*)[4])(frame_ + FRAME_OFF(60)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(64)))
undefined4 __cdecl
radiogrp_create_items(iptr param_1,int *param_2,int param_3,iptr param_4,int param_5,iptr param_6,int param_7
            ,undefined4 param_8)

{
  int *piVar1;
  HBITMAP pHVar2;
  HBITMAP pHVar3;
  HBITMAP pHVar4;
  undefined4 uVar5;
  iptr iVar6;
  int iVar7;
  int iVar8;
  int nHeight;
  WndBase *this;
  iptr iVar9;
  int iVar10;
  HWND pHVar11;
  iptr iVar12;
  size_t sVar12;
  int iVar13;
  HMENU hMenu;
  HINSTANCE hInstance;
  LPVOID lpParam;
  undefined1 frame_[FRAME_OFF(72)] __attribute__((aligned(8)));  /* original stack frame */
  
  pHVar2 = LoadBitmapA(app_hinstance,(LPCSTR)0x12d);
  pHVar3 = LoadBitmapA(app_hinstance,(LPCSTR)0x12f);
  pHVar4 = LoadBitmapA(app_hinstance,(LPCSTR)0x12e);
  uVar5 = mem_handle_alloc(param_5 * 0xa4);
  iVar6 = mem_handle_lock(uVar5);
  iVar7 = rect_width((iptr)param_2);
  iVar7 = iVar7 / param_3;
  iVar8 = rect_height((iptr)param_2);
  iVar8 = (iVar8 * param_3) / param_5;
  nHeight = radiogrp_item_height(param_8);
  local_44 = *param_2;
  local_8 = param_2[1];
  local_40 = 0x40010000;
  if (param_7 != 0) {
    local_40 = 0x50010000;
  }
  local_28 = 0;
  do {
    if (param_5 <= (int)local_28) {
      *(int *)param_1 = param_5;
      mem_handle_unlock(uVar5);
      return uVar5;
    }
    lpParam = (LPVOID)0x0;
    hMenu = (HMENU)0x0;
    hInstance = app_hinstance;
    this = (WndBase *)ctrl_get_parent((Control *)param_4);
    iVar9 = wnd_get_window(this);
    iVar10 = iVar8 >> 1;
    iVar13 = nHeight >> 1;
    pHVar11 = CreateWindowExA(4,s_MSControlClass_00638708,&radiogrp_item_wnd_title,local_40,local_44,
                              (iVar10 - iVar13) + local_8,iVar7,nHeight,*(HWND *)(iVar9 + 4),hMenu,
                              hInstance,lpParam);
    *(HWND *)(iVar6 + local_28 * 0xa4) = pHVar11;
    iVar12 = ctrl_init_block(*(undefined4 *)(iVar6 + local_28 * 0xa4),param_4);
    if (local_28 == 0) {
      *(undefined4 *)(iVar12 + 8) = 0;
    }
    else {
      *(undefined4 *)(iVar12 + 8) = 1;
    }
    *(HBITMAP *)(iVar12 + 0xc) = pHVar2;
    *(HBITMAP *)(iVar12 + 0x10) = pHVar3;
    *(HBITMAP *)(iVar12 + 0x14) = pHVar4;
    *(uint *)(iVar12 + 0x24) = local_28 * 0xa4 + iVar6;
    *(undefined4 *)(iVar12 + 0x2c) = 3;
    SetWindowLongA(*(HWND *)(iVar6 + local_28 * 0xa4),-4,ADDR(0x5d9b86, radiogrp_item_wndproc));
    SetRect((LPRECT)(local_28 * 0xa4 + iVar6 + 4),local_44,(iVar10 - iVar13) + local_8,
            local_44 + iVar7,(iVar10 - iVar13) + local_8 + nHeight);
    *(uint *)(iVar6 + 0x14 + local_28 * 0xa4) = local_28;
    local_10 = *(char **)(param_6 + local_28 * 4);
    if (*local_10 == '!') {
      *(undefined4 *)(iVar6 + 0x18 + local_28 * 0xa4) = 0;
      local_10++;
    }
    else if (*local_10 == '^') {
      *(undefined4 *)(iVar6 + 0x18 + local_28 * 0xa4) = 1;
      radiogrp_set_selected((RadioGroupSetSelView *)param_4,local_28);
      local_10++;
    }
    else {
      *(undefined4 *)(iVar6 + 0x18 + local_28 * 0xa4) = 1;
    }
    FUN_005f22d0(local_28 * 0xa4 + iVar6 + 0x1c,local_10);
    local_18 = (char *)(local_28 * 0xa4 + iVar6 + 0x1c);
    *(undefined4 *)(iVar6 + 0xa0 + local_28 * 0xa4) = 0;
    while( true ) {
      if (*local_18 == '\0') goto LAB_005d9226;
      if (*local_18 == '~') break;
      piVar1 = (int *)(iVar6 + 0xa0 + local_28 * 0xa4);
      *piVar1 = *piVar1 + 1;
      local_18++;
    }
    for (local_28 = *(uint *)(iVar6 + 0xa0 + local_28 * 0xa4);
        sVar12 = _strlen((char *)(local_28 * 0xa4 + iVar6 + 0x1c)), local_28 < sVar12;
        local_28 = local_28 + 1) {
      *(undefined1 *)(local_28 * 0xa5 + 0x1c + iVar6) =
           *(undefined1 *)(local_28 * 0xa5 + 0x1d + iVar6);
    }
LAB_005d9226:
    sVar12 = _strlen((char *)(local_28 * 0xa4 + iVar6 + 0x1c));
    if (*(uint *)(iVar6 + 0xa0 + local_28 * 0xa4) < sVar12) {
      local_c[0] = *(char *)(*(int *)(iVar6 + 0xa0 + local_28 * 0xa4) + local_28 * 0xa4 + 0x1c +
                            iVar6);
      local_c[1] = 0;
      __strlwr(local_c);
      *(char *)(iVar6 + 0x9c + local_28 * 0xa4) = local_c[0];
    }
    else {
      *(undefined4 *)(iVar6 + 0xa0 + local_28 * 0xa4) = 0xffffffff;
    }
    local_8 += iVar8;
    if (param_2[3] <= local_8) {
      local_44 += iVar7;
      local_8 = param_2[1];
    }
    local_28++;
  } while( true );
}
#undef app_hinstance
#undef local_44
#undef local_40
#undef local_28
#undef local_18
#undef local_10
#undef local_c
#undef local_8

/* 005d99f4 auto */
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
void __cdecl radiogrp_destroy_items(int param_1,int param_2)

{
  iptr iVar1;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_2 == 0) {
    dbg_log(ADDR(0x63872c, ((u8 *)&g.d_0063872c)));
  }
  else {
    iVar1 = mem_handle_lock(param_2);
    for (local_8 = 0; local_8 < param_1; local_8++) {
      if (*(int *)(iVar1 + local_8 * 0xa4) != 0) {
        DestroyWindow(*(HWND *)(iVar1 + local_8 * 0xa4));
      }
    }
    mem_handle_unlock(param_2);
    mem_handle_free(param_2);
  }
  return;
}
#undef local_8

/* 005d9a9a auto */
#define wnd_active_child (*(undefined4 *)((u8 *)&g.d_00637ea4))
void __cdecl radiogrp_item_activate(HWND param_1)

{
  RadioGroupItemsView *this;
  iptr iVar1;
  iptr iVar2;
  iptr iVar4;
  iptr iVar3;
  iptr iVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  RECT *pRVar9;
  BOOL BVar10;
  
  iVar1 = wnd_from_hwnd(param_1);
  if (iVar1 != 0) {
    this = *(RadioGroupItemsView **)(iVar1 + 4);
    iVar6 = *(int *)(iVar1 + 0x24);
    SetFocus(param_1);
    iVar2 = radiogrp_get_selected((RadioGroupGetSelView *)this);
    if ((iVar2 != *(int *)(iVar6 + 0x14)) && (*(int *)(iVar6 + 0x18) == 1)) {
      BVar10 = 0;
      pRVar9 = (RECT *)0x0;
      iVar4 = radiogrp_get_selected((RadioGroupGetSelView *)this);
      iVar3 = radiogrp_get_items(this);
      InvalidateRect(*(HWND *)(iVar3 + iVar4 * 0xa4),pRVar9,BVar10);
      radiogrp_set_selected((RadioGroupSetSelView *)this,*(undefined4 *)(iVar6 + 0x14));
      BVar10 = 0;
      pRVar9 = (RECT *)0x0;
      iVar5 = radiogrp_get_selected((RadioGroupGetSelView *)this);
      iVar6 = radiogrp_get_items(this);
      InvalidateRect(*(HWND *)(iVar6 + iVar5 * 0xa4),pRVar9,BVar10);
    }
    wnd_active_child = ctrl_get_parent((Control *)this);
    uVar7 = radiogrp_get_selected((RadioGroupGetSelView *)this);
    uVar8 = ctrl_get_id((ControlIdView *)this);
    radiogrp_fire_callback((RadioGroupClickView *)this,uVar8,uVar7);
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
#define local_138 (*(tagRECT *)(frame_ + FRAME_OFF(0)))
#define local_128 (*(HBITMAP *)(frame_ + FRAME_OFF(16)))
#define local_124 (*(iptr *)(frame_ + FRAME_OFF(20)))
#define local_120 (*(tagPAINTSTRUCT *)(frame_ + FRAME_OFF(24)))
#define local_e0 (*(HGDIOBJ *)(frame_ + FRAME_OFF(88)))
#define local_dc (*(tagSIZE *)(frame_ + FRAME_OFF(92)))
#define local_d4 (*(int *)(frame_ + FRAME_OFF(100)))
#define local_d0 (*(HDC *)(frame_ + FRAME_OFF(104)))
#define local_cc (*(int *)(frame_ + FRAME_OFF(108)))
#define local_c8 (*(int *)(frame_ + FRAME_OFF(112)))
#define local_c4 (*(undefined1 (*)[4])(frame_ + FRAME_OFF(116)))
#define local_c0 (*(int *)(frame_ + FRAME_OFF(120)))
#define local_bc (*(iptr *)(frame_ + FRAME_OFF(124)))
#define local_b8 (*(int *)(frame_ + FRAME_OFF(128)))
#define local_b4 (*(int *)(frame_ + FRAME_OFF(132)))
#define local_b0 (*(int *)(frame_ + FRAME_OFF(136)))
#define local_ac (*(int *)(frame_ + FRAME_OFF(140)))
#define local_a8 (*(HBRUSH *)(frame_ + FRAME_OFF(144)))
#define local_a4 (*(undefined1 (*)[4])(frame_ + FRAME_OFF(148)))
#define local_a0 (*(undefined1 (*)[4])(frame_ + FRAME_OFF(152)))
#define local_9c (*(RadioGroupItemsView * *)(frame_ + FRAME_OFF(156)))
#define local_98 (*(undefined4 * *)(frame_ + FRAME_OFF(160)))
#define local_94 (*(tagRECT *)(frame_ + FRAME_OFF(164)))
#define local_84 (*(char (*)[128])(frame_ + FRAME_OFF(180)))
undefined4 __stdcall radiogrp_item_wndproc(HWND param_1,uint param_2,WPARAM param_3,LPARAM param_4)

{
  char cVar1;
  int iVar4;
  iptr iVar2;
  iptr iVar3;
  uint uVar5;
  WndPaletteView *pCVar6;
  GamePalette *pCVar7;
  size_t sVar8;
  WndBase *pCVar9;
  int iVar11;
  iptr iVar12;
  HWND pHVar13;
  WndKeyNavView *pCVar14;
  iptr iVar10;
  undefined4 uVar15;
  iptr iVar13;
  undefined4 uVar16;
  undefined1 *puVar17;
  undefined1 *puVar18;
  tagRECT *ptVar19;
  RECT *pRVar20;
  undefined1 *puVar21;
  UINT UVar22;
  BOOL BVar23;
  undefined1 frame_[FRAME_OFF(312)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_124 = wnd_from_hwnd(param_1);
  local_9c = *(RadioGroupItemsView **)(local_124 + 4);
  local_bc = *(int *)(local_124 + 0x24);
  if (param_2 < 0x10) {
    if (param_2 == 0xf) {
      if (*(int *)(local_bc + 0x18) == 1) {
        iVar2 = radiogrp_get_selected((RadioGroupGetSelView *)local_9c);
        if (iVar2 == *(int *)(local_bc + 0x14)) {
          local_128 = *(HBITMAP *)(local_124 + 0x14);
        }
        else {
          local_128 = *(HBITMAP *)(local_124 + 0x10);
        }
      }
      else {
        local_128 = *(HBITMAP *)(local_124 + 0xc);
      }
      GetBitmapDimensionEx(local_128,&local_dc);
      local_138.left = *(int *)(local_bc + 4);
      local_138.top = *(int *)(local_bc + 8);
      local_138.right = *(int *)(local_bc + 0xc);
      local_138.bottom = *(int *)(local_bc + 0x10);
      local_b8 = local_138.left;
      local_b4 = local_138.top;
      local_b0 = local_138.right;
      local_ac = local_138.bottom;
      if (radio_lbutton_captured != 0) {
        local_b0 = local_138.left + 0x20;
        iVar3 = rect_height((iptr)&local_138);
        local_b4 = iVar3 - 0x14 + local_138.top >> 1;
        local_ac = local_138.top + 0x14;
      }
      InvalidateRect(param_1,(RECT *)0x0,1);
      OffsetRect(&local_138,-local_138.left,-local_138.top);
      local_d0 = BeginPaint(param_1,&local_120);
      ctrl_paint_parent_bkgnd((iptr)&local_120,param_1);
      uVar16 = font_get_handle(*(GameFont **)local_9c[1].pad_0);
      local_98 = (undefined4 *)mem_handle_lock(uVar16);
      local_e0 = SelectObject(local_d0,(HGDIOBJ)*local_98);
      uVar16 = font_get_handle(*(GameFont **)local_9c[1].pad_0);
      mem_handle_unlock(uVar16);
      SetBkMode(local_d0,1);
      gdi_blit_transparent(local_d0,local_128,local_138.left,local_138.bottom - 0x14 >> 1,0x20,0x14,0,7);
      local_138.left += 0x25;
      if ((radio_shadow_dx != 0) || (radio_shadow_dy != 0)) {
        OffsetRect(&local_138,(uint)radio_shadow_dx,(uint)radio_shadow_dy);
        puVar21 = local_a0;
        puVar18 = local_c4;
        puVar17 = local_a4;
        uVar5 = (uint)radio_shadow_color_index;
        pCVar6 = (WndPaletteView *)ctrl_get_parent((Control *)local_9c);
        pCVar7 = (GamePalette *)wnd_get_palette(pCVar6);
        palette_get_entry(pCVar7,uVar5,(iptr)puVar17,(iptr)puVar18,(iptr)puVar21);
        SetTextColor(local_d0,(uint)CONCAT12(local_a0[0],CONCAT11(local_c4[0],local_a4[0])));
        UVar22 = 0x24;
        ptVar19 = &local_138;
        sVar8 = _strlen((char *)(local_bc + 0x1c));
        DrawTextA(local_d0,(LPCSTR)(local_bc + 0x1c),sVar8,ptVar19,UVar22);
        OffsetRect(&local_138,-(uint)radio_shadow_dx,-(uint)radio_shadow_dy);
      }
      if (*(int *)(local_bc + 0x18) == 1) {
        pCVar9 = (WndBase *)ctrl_get_parent((Control *)local_9c);
        iVar11 = wnd_get_window(pCVar9);
        if (*(int *)(iVar11 + 0x40) == 8) {
          if (radio_text_color_index == 0) {
            SetTextColor(local_d0,0);
          }
          else {
            puVar21 = local_a0;
            puVar18 = local_c4;
            puVar17 = local_a4;
            uVar5 = (uint)radio_text_color_index;
            pCVar6 = (WndPaletteView *)ctrl_get_parent((Control *)local_9c);
            pCVar7 = (GamePalette *)wnd_get_palette(pCVar6);
            iVar12 = palette_get_logpalette(pCVar7);
            palette_get_entry_rgb(iVar12,uVar5,(iptr)puVar17,(iptr)puVar18,(iptr)puVar21);
            SetTextColor(local_d0,(uint)CONCAT12(local_a0[0],CONCAT11(local_c4[0],local_a4[0])));
          }
        }
        else if (radio_text_rgb_set == '\0') {
          SetTextColor(local_d0,0);
        }
        else {
          SetTextColor(local_d0,(uint)CONCAT12(radio_text_rgb_b,CONCAT11(radio_text_rgb_g,radio_text_rgb_r)));
        }
      }
      else if (*(int *)(local_bc + 0x18) == 0) {
        pCVar9 = (WndBase *)ctrl_get_parent((Control *)local_9c);
        iVar11 = wnd_get_window(pCVar9);
        if (*(int *)(iVar11 + 0x40) == 8) {
          if (radio_disabled_color_index == 0) {
            SetTextColor(local_d0,0x404040);
          }
          else {
            puVar21 = local_a0;
            puVar18 = local_c4;
            puVar17 = local_a4;
            uVar5 = (uint)radio_disabled_color_index;
            pCVar6 = (WndPaletteView *)ctrl_get_parent((Control *)local_9c);
            pCVar7 = (GamePalette *)wnd_get_palette(pCVar6);
            iVar12 = palette_get_logpalette(pCVar7);
            palette_get_entry_rgb(iVar12,uVar5,(iptr)puVar17,(iptr)puVar18,(iptr)puVar21);
            SetTextColor(local_d0,(uint)CONCAT12(local_a0[0],CONCAT11(local_c4[0],local_a4[0])));
          }
        }
        else if (radio_disabled_rgb_set == '\0') {
          SetTextColor(local_d0,0x404040);
        }
        else {
          SetTextColor(local_d0,(uint)CONCAT12(radio_disabled_rgb_b,CONCAT11(radio_disabled_rgb_g,radio_disabled_rgb_r)));
        }
      }
      UVar22 = 0x24;
      ptVar19 = &local_138;
      sVar8 = _strlen((char *)(local_bc + 0x1c));
      DrawTextA(local_d0,(LPCSTR)(local_bc + 0x1c),sVar8,ptVar19,UVar22);
      if (*(int *)(local_bc + 0xa0) != -1) {
        FUN_005f22d0(local_84,local_bc + 0x1c);
        local_84[*(int *)(local_bc + 0xa0)] = '\0';
        local_94.left = local_138.left;
        local_94.top = local_138.top;
        local_94.right = local_138.right;
        local_94.bottom = local_138.bottom;
        sVar8 = _strlen(local_84);
        if (sVar8 == 0) {
          local_c0 = local_94.left;
        }
        else {
          UVar22 = 0x424;
          ptVar19 = &local_94;
          sVar8 = _strlen(local_84);
          DrawTextA(local_d0,local_84,sVar8,ptVar19,UVar22);
          local_c0 = local_94.right - 1;
        }
        FUN_005f22d0(local_84,local_bc + 0x1c);
        local_84[*(int *)(local_bc + 0xa0) + 1] = '\0';
        local_94.left = local_138.left;
        local_94.top = local_138.top;
        local_94.right = local_138.right;
        local_94.bottom = local_138.bottom;
        UVar22 = 0x424;
        ptVar19 = &local_94;
        sVar8 = _strlen(local_84);
        DrawTextA(local_d0,local_84,sVar8,ptVar19,UVar22);
        local_c0 = local_c0 + ((local_94.right + 1) - local_c0 >> 1) - 5;
        local_cc = local_c0 + 10;
        local_a8 = GetStockObject(3);
        SelectObject(local_d0,local_a8);
        MoveToEx(local_d0,local_c0,local_138.bottom - 3,(LPPOINT)0x0);
        LineTo(local_d0,local_cc,local_138.bottom - 3);
        MoveToEx(local_d0,local_c0,local_138.bottom - 2,(LPPOINT)0x0);
        LineTo(local_d0,local_cc,local_138.bottom - 2);
      }
      SelectObject(local_d0,local_e0);
      EndPaint(param_1,&local_120);
      pHVar13 = GetFocus();
      if (pHVar13 != param_1) {
        return 0;
      }
    }
    else if (param_2 != 7) {
      if (param_2 == 8) {
        wnd_redraw_client(param_1);
        return 0;
      }
      goto switchD_005dab35_default;
    }
    pCVar14 = (WndKeyNavView *)ctrl_get_parent((Control *)local_9c);
    cVar1 = wnd_keyboard_nav_enabled(pCVar14);
    if (cVar1 == '\0') {
      uVar16 = ctrl_default_wndproc(param_1,param_2,param_3,param_4);
      return uVar16;
    }
    local_d0 = GetDC(param_1);
    local_a8 = GetStockObject(3);
    GetClientRect(param_1,&local_138);
    SelectObject(local_d0,local_a8);
    local_138.left += 0x20;
    FrameRect(local_d0,&local_138,local_a8);
    DeleteObject(local_a8);
    ReleaseDC(param_1,local_d0);
  }
  else if (param_2 < 0x202) {
    if (param_2 == 0x201) {
      if (radio_lbutton_captured == 0) {
        iVar11 = radiogrp_get_selected((RadioGroupGetSelView *)local_9c);
        if ((iVar11 != *(int *)(local_bc + 0x14)) && (*(int *)(local_bc + 0x18) == 1)) {
          iVar11 = radiogrp_get_selected((RadioGroupGetSelView *)local_9c);
          if (iVar11 != -1) {
            BVar23 = 0;
            pRVar20 = (RECT *)0x0;
            iVar11 = radiogrp_get_selected((RadioGroupGetSelView *)local_9c);
            iVar4 = radiogrp_get_items(local_9c);
            InvalidateRect(*(HWND *)(iVar4 + iVar11 * 0xa4),pRVar20,BVar23);
          }
          radiogrp_set_selected((RadioGroupSetSelView *)local_9c,*(undefined4 *)(local_bc + 0x14));
          SetFocus(param_1);
          InvalidateRect(param_1,(RECT *)0x0,0);
          iVar12 = ctrl_get_parent((Control *)local_9c);
          wnd_set_active_child(iVar12);
          uVar16 = radiogrp_get_selected((RadioGroupGetSelView *)local_9c);
          uVar15 = ctrl_get_id((ControlIdView *)local_9c);
          radiogrp_fire_callback((RadioGroupClickView *)local_9c,uVar15,uVar16);
        }
        radio_lbutton_captured = 1;
        SetCapture(param_1);
      }
    }
    else {
      if (param_2 != 0x100) goto switchD_005dab35_default;
      if (param_3 == 9) {
        pHVar13 = GetParent(param_1);
        SendMessageA(pHVar13,param_2,param_3,param_4);
      }
      else {
        if (param_3 == 0x20) {
          pCVar14 = (WndKeyNavView *)ctrl_get_parent((Control *)local_9c);
          cVar1 = wnd_keyboard_nav_enabled(pCVar14);
          if (cVar1 != '\0') {
            SendMessageA(param_1,0x201,0,0);
            SendMessageA(param_1,0x202,0,0);
            return 0;
          }
        }
        if ((((param_3 == 0x27) || (param_3 == 0x28)) || (param_3 == 0x66)) || (param_3 == 0x62)) {
          pCVar14 = (WndKeyNavView *)ctrl_get_parent((Control *)local_9c);
          cVar1 = wnd_keyboard_nav_enabled(pCVar14);
          if (cVar1 != '\0') {
            local_d4 = radiogrp_item_count((RadioGroupCountView *)local_9c);
            local_c8 = *(int *)(local_bc + 0x14) + 1;
            iVar11 = radiogrp_item_count((RadioGroupCountView *)local_9c);
            if (iVar11 <= local_c8) {
              local_c8 = 0;
            }
            while ((0 < local_d4 &&
                   (iVar11 = radiogrp_get_items(local_9c),
                   *(int *)(iVar11 + 0x18 + local_c8 * 0xa4) == 0))) {
              local_d4--;
              local_c8++;
              iVar11 = radiogrp_item_count((RadioGroupCountView *)local_9c);
              if (iVar11 <= local_c8) {
                local_c8 = 0;
              }
            }
            if (local_d4 < 1) {
              return 0;
            }
            iVar11 = radiogrp_get_items(local_9c);
            SetFocus(*(HWND *)(iVar11 + local_c8 * 0xa4));
            BVar23 = 0;
            pRVar20 = (RECT *)0x0;
            iVar11 = radiogrp_get_selected((RadioGroupGetSelView *)local_9c);
            iVar10 = radiogrp_get_items(local_9c);
            InvalidateRect(*(HWND *)(iVar10 + iVar11 * 0xa4),pRVar20,BVar23);
            radiogrp_set_selected((RadioGroupSetSelView *)local_9c,local_c8);
            BVar23 = 0;
            pRVar20 = (RECT *)0x0;
            iVar11 = radiogrp_get_items(local_9c);
            InvalidateRect(*(HWND *)(iVar11 + local_c8 * 0xa4),pRVar20,BVar23);
            iVar12 = ctrl_get_parent((Control *)local_9c);
            wnd_set_active_child(iVar12);
            uVar16 = radiogrp_get_selected((RadioGroupGetSelView *)local_9c);
            uVar15 = ctrl_get_id((ControlIdView *)local_9c);
            radiogrp_fire_callback((RadioGroupClickView *)local_9c,uVar15,uVar16);
            return 0;
          }
        }
        if (((param_3 == 0x26) || (param_3 == 0x25)) || ((param_3 == 0x68 || (param_3 == 100)))) {
          pCVar14 = (WndKeyNavView *)ctrl_get_parent((Control *)local_9c);
          cVar1 = wnd_keyboard_nav_enabled(pCVar14);
          if (cVar1 != '\0') {
            local_d4 = radiogrp_item_count((RadioGroupCountView *)local_9c);
            local_c8 = *(int *)(local_bc + 0x14) - 1;
            if (local_c8 < 0) {
              local_c8 = radiogrp_item_count((RadioGroupCountView *)local_9c);
              local_c8--;
            }
            while ((0 < local_d4 &&
                   (iVar11 = radiogrp_get_items(local_9c),
                   *(int *)(iVar11 + 0x18 + local_c8 * 0xa4) == 0))) {
              local_d4--;
              local_c8--;
              if (local_c8 < 0) {
                local_c8 = radiogrp_item_count((RadioGroupCountView *)local_9c);
                local_c8--;
              }
            }
            if (local_d4 < 1) {
              return 0;
            }
            iVar11 = radiogrp_get_items(local_9c);
            SetFocus(*(HWND *)(iVar11 + local_c8 * 0xa4));
            BVar23 = 0;
            pRVar20 = (RECT *)0x0;
            iVar11 = radiogrp_get_selected((RadioGroupGetSelView *)local_9c);
            iVar13 = radiogrp_get_items(local_9c);
            InvalidateRect(*(HWND *)(iVar13 + iVar11 * 0xa4),pRVar20,BVar23);
            radiogrp_set_selected((RadioGroupSetSelView *)local_9c,local_c8);
            BVar23 = 0;
            pRVar20 = (RECT *)0x0;
            iVar11 = radiogrp_get_items(local_9c);
            InvalidateRect(*(HWND *)(iVar11 + local_c8 * 0xa4),pRVar20,BVar23);
            iVar12 = ctrl_get_parent((Control *)local_9c);
            wnd_set_active_child(iVar12);
            uVar16 = radiogrp_get_selected((RadioGroupGetSelView *)local_9c);
            uVar15 = ctrl_get_id((ControlIdView *)local_9c);
            radiogrp_fire_callback((RadioGroupClickView *)local_9c,uVar15,uVar16);
            return 0;
          }
        }
        pHVar13 = GetParent(param_1);
        SendMessageA(pHVar13,param_2,param_3,param_4);
      }
    }
  }
  else {
    switch(param_2) {
    case 0x202:
      ReleaseCapture();
      radio_lbutton_captured = 0;
      break;
    case 0x203:
      if (*(int *)(local_bc + 0x18) == 1) {
        iVar12 = ctrl_get_parent((Control *)local_9c);
        wnd_set_active_child(iVar12);
        iVar11 = radiogrp_get_selected((RadioGroupGetSelView *)local_9c);
        if (iVar11 != *(int *)(local_bc + 0x14)) {
          iVar11 = radiogrp_get_selected((RadioGroupGetSelView *)local_9c);
          if (iVar11 != -1) {
            BVar23 = 0;
            pRVar20 = (RECT *)0x0;
            iVar11 = radiogrp_get_selected((RadioGroupGetSelView *)local_9c);
            iVar4 = radiogrp_get_items(local_9c);
            InvalidateRect(*(HWND *)(iVar4 + iVar11 * 0xa4),pRVar20,BVar23);
          }
          radiogrp_set_selected((RadioGroupSetSelView *)local_9c,*(undefined4 *)(local_bc + 0x14));
        }
        uVar16 = *(undefined4 *)(local_bc + 0x14);
        uVar15 = ctrl_get_id((ControlIdView *)local_9c);
        radiogrp_fire_dblclick((RadioGroupDblClickView *)local_9c,uVar15,uVar16);
      }
      break;
    case 0x204:
      if (radio_rbutton_captured == 0) {
        radio_rbutton_captured = 1;
        SetCapture(param_1);
        iVar12 = ctrl_get_parent((Control *)local_9c);
        wnd_set_active_child(iVar12);
        uVar16 = *(undefined4 *)(local_bc + 0x14);
        uVar15 = ctrl_get_id((ControlIdView *)local_9c);
        radiogrp_fire_rclick((RadioGroupRClickView *)local_9c,uVar15,uVar16);
      }
      break;
    case 0x205:
      ReleaseCapture();
      radio_rbutton_captured = 0;
      break;
    default:
switchD_005dab35_default:
      uVar16 = ctrl_default_wndproc(param_1,param_2,param_3,param_4);
      return uVar16;
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
#undef local_138
#undef local_128
#undef local_124
#undef local_120
#undef local_e0
#undef local_dc
#undef local_d4
#undef local_d0
#undef local_cc
#undef local_c8
#undef local_c4
#undef local_c0
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
#undef local_84

/* 005dab5a auto */
#define local_38 (*(CHAR (*)[52])(frame_ + FRAME_OFF(0)))
undefined4 __cdecl ctrl_hwnd_is_radio(HWND param_1)

{
  char *_Str1;
  iptr iVar1;
  iptr iVar2;
  char *_Str2;
  undefined1 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  GetClassNameA(param_1,local_38,0x32);
  _Str2 = s_MSCONTROLCLASS_00638768;
  _Str1 = __strupr(local_38);
  iVar1 = _strcmp(_Str1,_Str2);
  if ((iVar1 == 0) && (iVar2 = wnd_from_hwnd(param_1), *(int *)(iVar2 + 0x2c) == 3)) {
    return 1;
  }
  return 0;
}
#undef local_38

/* 005dabc7 auto */
void __cdecl radiogrp_hwnd_invalidate(HWND param_1)

{
  InvalidateRect(param_1,(RECT *)0x0,0);
  return;
}

/* 005dabe5 auto */
uint __cdecl radiogrp_hwnd_is_selected(undefined4 param_1)

{
  iptr iVar2;
  int iVar3;
  iptr iVar1;
  
  iVar2 = wnd_from_hwnd(param_1);
  iVar1 = *(iptr *)(iVar2 + 0x24);
  iVar3 = radiogrp_get_selected(*(RadioGroupGetSelView **)(iVar2 + 4));
  return (uint)(iVar3 == *(int *)(iVar1 + 0x14));
}

/* 005dac39 auto */
undefined4 __cdecl radiogrp_hwnds_same_group(int param_1,int param_2)

{
  iptr iVar1;
  iptr iVar3;
  int iVar4;
  iptr iVar2;
  
  iVar1 = ctrl_hwnd_is_radio(param_1);
  if ((iVar1 == 0) || (iVar3 = ctrl_hwnd_is_radio(param_2), iVar3 == 0)) {
    return 0;
  }
  if (param_1 == param_2) {
    return 1;
  }
  iVar4 = wnd_from_hwnd(param_1);
  iVar2 = wnd_from_hwnd(param_2);
  if (*(int *)(iVar2 + 4) == *(int *)(iVar4 + 4)) {
    return 1;
  }
  return 0;
}

/* 005dad40 auto */
void __thiscall radiogrp_fire_callback(RadioGroupClickView *this,undefined4 param_1,undefined4 param_2)

{
  if (this->on_select != 0) {
    (*(code *)this->on_select)(param_1,param_2);
  }
  return;
}

/* 005dad80 auto */
void __thiscall radiogrp_fire_dblclick(RadioGroupDblClickView *this,undefined4 param_1,undefined4 param_2)

{
  if (this->on_dblclick != 0) {
    (*(code *)this->on_dblclick)(param_1,param_2);
  }
  return;
}

/* 005dadc0 auto */
void __thiscall radiogrp_fire_rclick(RadioGroupRClickView *this,undefined4 param_1,undefined4 param_2)

{
  if (this->on_rclick != 0) {
    (*(code *)this->on_rclick)(param_1,param_2);
  }
  return;
}

/* 005db0d0 auto */
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __thiscall scrollbar_set_page_size(Control *this,u32 param_1)

{
  undefined1 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  scrollbar_get_ctl_range(this,(iptr)&local_c,(iptr)&local_8);
  if ((int)param_1 <= local_8 - local_c) {
    this->on_select = param_1;
  }
  return;
}
#undef local_c
#undef local_8

/* 005db110 auto */
void __thiscall scrollbar_get_ctl_range(Control *this,iptr param_1,iptr param_2)

{
  scrollbar_hwnd_get_range(this->hwnd,param_1,param_2);
  return;
}

/* 005ea7d7 auto */
#define local_8 (*(ControlNextView * *)(frame_ + FRAME_OFF(0)))
undefined4 __cdecl ctrl_list_find_by_hwnd(int param_1,ControlNextView *param_2)

{
  int iVar1;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = param_2;
  while( true ) {
    if (local_8 == (ControlNextView *)0x0) {
      return 0;
    }
    iVar1 = control_get_hwnd((ControlHwndView *)local_8);
    if (iVar1 == param_1) break;
    local_8 = (ControlNextView *)control_get_next(local_8);
  }
  return local_8;
}
#undef local_8

/* 005eac6d auto */
#define local_8 (*(ControlNextView * *)(frame_ + FRAME_OFF(0)))
undefined4 __cdecl ctrl_list_find_type11_hwnd(ControlNextView *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = param_1;
  while( true ) {
    if (local_8 == (ControlNextView *)0x0) {
      return 0;
    }
    iVar1 = control_get_type((ControlTypeView *)local_8);
    if (iVar1 == 0xb) break;
    local_8 = (ControlNextView *)control_get_next(local_8);
  }
  uVar2 = control_get_hwnd((ControlHwndView *)local_8);
  return uVar2;
}
#undef local_8

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
#define local_8 (*(uint *)(frame_ + FRAME_OFF(0)))
uint __cdecl input_map_vkey(uint param_1)

{
  int iVar1;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = *(uint *)(&input_vkey_map_table + (param_1 & 0xff) * 4);
  if (local_8 != 0) {
    iVar1 = input_ctrl_key_down();
    if (iVar1 != 0) {
      local_8 = local_8 | 0x200;
    }
    iVar1 = input_shift_key_down();
    if (iVar1 != 0) {
      local_8 = local_8 | 0x100;
    }
  }
  return local_8;
}
#undef local_8

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
void __cdecl ddctrl_set_msg_target(iptr param_1)

{
  ddctrl_current_target = param_1;
  return;
}
#undef ddctrl_current_target

/* 005f130f auto */
undefined4 __thiscall ddctrl_dispatch_msg(DDControl *this,int param_1,int param_2,int param_3)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = ddctrl_dispatch_to_children(this,param_1,param_2,param_3);
  if (cVar1 == '\0') {
    ddctrl_set_msg_target((iptr)this);
    if ((param_1 == 0x100) && (this->is_active != '\0')) {
      (*((code **)(this->vtable))[6])(param_2);
      uVar2 = 1;
    }
    else if ((param_1 == 0x102) && (this->is_active != '\0')) {
      (*((code **)(this->vtable))[7])(param_2);
      uVar2 = 1;
    }
    else if (param_1 == 0xfff0) {
      (*((code **)(this->vtable))[9])(param_2,param_3);
      uVar2 = 1;
    }
    else if ((((param_2 < (int)this->rect_left) || (param_3 < (int)this->rect_top)) ||
             ((int)this->rect_right < param_2)) || ((int)this->rect_bottom < param_3)) {
      uVar2 = 0;
    }
    else {
      switch(param_1) {
      case 0x200:
        (*((code **)(this->vtable))[4])(param_2,param_3);
        break;
      case 0x201:
        (*((code **)(this->vtable))[0])(this,param_2,param_3);
        break;
      case 0x202:
        (*((code **)(this->vtable))[2])(param_2,param_3);
        break;
      case 0x203:
        (*((code **)(this->vtable))[5])(param_2,param_3);
        break;
      case 0x204:
        (*((code **)(this->vtable))[1])(param_2,param_3);
        break;
      case 0x205:
        (*((code **)(this->vtable))[3])(param_2,param_3);
      }
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}

/* 005f1514 auto */
uptr __thiscall ddctrl_get_parent_window(DDControlParentView *this)

{
  uptr uVar1;
  uptr uVar2;
  
  if (this->parent_wnd == 0) {
    if (this->parent_control == 0) {
      uVar2 = 0;
    }
    else {
      uVar1 = ddctrl_get_parent_window((DDControlParentView *)this->parent_control);
      this->parent_wnd = uVar1;
      uVar2 = this->parent_wnd;
    }
  }
  else {
    uVar2 = this->parent_wnd;
  }
  return uVar2;
}

/* 005f15a9 auto */
void __thiscall ddctrl_on_paint_default(DDControlParentView *this,undefined4 param_1)

{
  int iVar1;
  
  iVar1 = ddctrl_get_parent_window(this);
  if (iVar1 == 0) {
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
    *(undefined1 *)((int)this + 0x34) = 0;
    (*((code **)(*(int **)this))[8])(this,0);
  }
  return;
}

/* 005f179c auto */
void __thiscall ddctrl_on_lbuttondown(DDControlActivateView *this,undefined4 param_1,undefined4 param_2)

{
  ddctrl_activate(this);
  return;
}

/* 005f17bc auto */
void __thiscall ddctrl_on_rbuttondown_nop(void *this,undefined4 param_1,undefined4 param_2)

{
  return;
}

/* 005f17d4 auto */
void __thiscall ddctrl_on_lbuttonup(C_005f17d4 *this,undefined4 param_1,undefined4 param_2)

{
  if (this->on_lbutton_up != 0) {
    (*(code *)this->on_lbutton_up)(this->control_id,param_1,param_2);
  }
  return;
}

/* 005f1811 auto */
void __thiscall ddctrl_on_rbuttonup(C_005f1811 *this,undefined4 param_1,undefined4 param_2)

{
  if (this->on_rbutton_up != 0) {
    (*(code *)this->on_rbutton_up)(this->control_id,param_1,param_2);
  }
  return;
}

/* 005f184e auto */
void __thiscall ddctrl_on_mousemove(C_005f184e *this,undefined4 param_1,undefined4 param_2)

{
  if (this->on_mouse_move != 0) {
    (*(code *)this->on_mouse_move)(this->control_id,param_1,param_2);
  }
  return;
}

/* 005f188b auto */
void __thiscall ddctrl_on_dblclick(C_005f188b *this,undefined4 param_1,undefined4 param_2)

{
  if (this->on_dblclick != 0) {
    (*(code *)this->on_dblclick)(this->control_id,param_1,param_2);
  }
  return;
}

/* 005f18c8 auto */
void __thiscall ddctrl_on_msg_fff0_nop(void *this,undefined4 param_1,undefined4 param_2)

{
  return;
}

/* 005f18e0 auto */
void __thiscall ddctrl_on_keydown_nop(void *this,undefined4 param_1)

{
  return;
}

/* 005f18f8 auto */
void __thiscall ddctrl_on_char_nop(void *this,undefined4 param_1)

{
  return;
}

/* 005f1910 auto */
void __thiscall ddctrl_on_set_active_nop(void *this,undefined4 param_1)

{
  return;
}

/* 005f19a6 auto */
#define local_8 (*(undefined4 *)(frame_ + FRAME_OFF(0)))
void __thiscall ddctrl_deactivate_children(void *this)

{
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = ptrlist_first((PtrList *)((int)this + 0x10));
  while (local_8 != 0) {
    ddctrl_deactivate(local_8);
    local_8 = ptrlist_next((PtrList *)((int)this + 0x10));
  }
  return;
}
#undef local_8

/* 005f1a40 auto */
#define local_8 (*(DDControl * *)(frame_ + FRAME_OFF(0)))
undefined1 __thiscall ddctrl_dispatch_to_children(DDControl *this,int param_1,int param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  undefined1 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((this->hover_child != 0) && (param_1 == 0x200)) {
    piVar1 = (int *)ddctrl_get_rect((void *)this->hover_child);
    if ((param_2 < *piVar1) ||
       (((piVar1[2] < param_2 || (param_3 < piVar1[1])) || (piVar1[3] < param_3)))) {
      ddctrl_dispatch_msg((DDControl *)this->hover_child,0xfff0,param_2,param_3);
      this->hover_child = 0;
    }
  }
  local_8 = (DDControl *)ptrlist_first((PtrList *)(this->pad_4 + 0xc));
  while( true ) {
    if (local_8 == (DDControl *)0x0) {
      return 0;
    }
    iVar2 = ddctrl_dispatch_msg(local_8,param_1,param_2,param_3);
    if (iVar2 != 0) break;
    local_8 = (DDControl *)ptrlist_next((PtrList *)(this->pad_4 + 0xc));
  }
  if (param_1 == 0x200) {
    this->hover_child = (uptr)local_8;
  }
  return 1;
}
#undef local_8

/* 00601300: written by hand in src/crt/locale.c */

/* 00601560: written by hand in src/crt/locale.c */

/* 00606330: written by hand in src/crt/locale.c */

/* 00606690: written by hand in src/crt/locale.c */
