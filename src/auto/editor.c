/* The game, the scenario editors: functions translated from the original
 * (tools/gen_c.py, now edited directly), in address order. */
#include "auto_common.h"

/* 00417fa0 auto */
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
C_004083b0_a28 * __thiscall editor_wnd_ctor(C_004083b0_a28 *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  frame_wnd_ctor((SurfaceWindow *)this);
  local_8 = 0;
  FUN_005f2620(&this->field_2fc,0x38,6,((void *)ADDR(0x0040388c, combo_ctor)),((void *)ADDR(0x00403553, combo_dtor)));
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  FUN_005f2620(this->pad_3c0 + 0x8c,0x48,9,edit_ctor,
               edit_dtor);
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  button_ctor((Control *)(this->pad_65c + 0x78));
  (*(i8 *)((char *)&local_8 + 0)) = 3;
  button_ctor((Control *)(this->pad_65c + 0xb4));
  (*(i8 *)((char *)&local_8 + 0)) = 4;
  button_ctor((Control *)(this->pad_65c + 0xf0));
  (*(i8 *)((char *)&local_8 + 0)) = 5;
  button_ctor((Control *)(this->pad_65c + 300));
  (*(i8 *)((char *)&local_8 + 0)) = 6;
  button_ctor((Control *)(this->pad_65c + 0x168));
  (*(i8 *)((char *)&local_8 + 0)) = 7;
  button_ctor((Control *)(this->pad_65c + 0x1a4));
  (*(i8 *)((char *)&local_8 + 0)) = 8;
  button_ctor((Control *)(this->pad_65c + 0x1e0));
  (*(i8 *)((char *)&local_8 + 0)) = 9;
  button_ctor((Control *)(this->pad_65c + 0x21c));
  (*(i8 *)((char *)&local_8 + 0)) = 10;
  button_ctor((Control *)(this->pad_65c + 600));
  (*(i8 *)((char *)&local_8 + 0)) = 0xb;
  button_ctor((Control *)(this->pad_65c + 0x294));
  (*(i8 *)((char *)&local_8 + 0)) = 0xc;
  button_ctor((Control *)(this->pad_65c + 0x2d0));
  (*(i8 *)((char *)&local_8 + 0)) = 0xd;
  button_ctor((Control *)(this->pad_65c + 0x30c));
  (*(i8 *)((char *)&local_8 + 0)) = 0xe;
  button_ctor((Control *)(this->pad_980 + 0x24));
  (*(i8 *)((char *)&local_8 + 0)) = 0xf;
  button_ctor((Control *)(this->pad_980 + 0x60));
  (*(i8 *)((char *)&local_8 + 0)) = 0x10;
  button_ctor((Control *)&this->edit_action_button);
  (*(i8 *)((char *)&local_8 + 0)) = 0x11;
  button_ctor((Control *)&this[1].field_30);
  (*(i8 *)((char *)&local_8 + 0)) = 0x12;
  checkbox_ctor((Control *)(this[1].pad_48 + 0x24));
  (*(i8 *)((char *)&local_8 + 0)) = 0x13;
  checkbox_ctor((Control *)(this[1].pad_48 + 0x60));
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),0x14);
  checkbox_ctor((Control *)(this[1].pad_48 + 0x9c));
  this->vtable = (u32)&PTR_FUN_0061c058;
  return this;
}
#undef local_10
#undef puStack_c
#undef local_8

/* 004183d0 auto */
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __thiscall editor_wnd_dtor(void *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  (*(i32 *)((char *)&local_8 + 1)) = 0;
  (*(i8 *)((char *)&local_8 + 0)) = 0x14;
  /* inlined unwind funclet FUN_0041851f */ { listbox_dtor((ListBoxControl *)(*(int *)((iptr)&this) + 0xb0c)); }
  (*(i8 *)((char *)&local_8 + 0)) = 0x13;
  /* inlined unwind funclet FUN_0041852e */ { listbox_dtor((ListBoxControl *)(*(int *)((iptr)&this) + 0xad0)); }
  (*(i8 *)((char *)&local_8 + 0)) = 0x12;
  /* inlined unwind funclet FUN_0041853d */ { listbox_dtor((ListBoxControl *)(*(int *)((iptr)&this) + 0xa94)); }
  (*(i8 *)((char *)&local_8 + 0)) = 0x11;
  /* inlined unwind funclet FUN_0041854c */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0xa58)); }
  (*(i8 *)((char *)&local_8 + 0)) = 0x10;
  /* inlined unwind funclet FUN_0041855b */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0xa1c)); }
  (*(i8 *)((char *)&local_8 + 0)) = 0xf;
  /* inlined unwind funclet FUN_0041856a */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x9e0)); }
  (*(i8 *)((char *)&local_8 + 0)) = 0xe;
  /* inlined unwind funclet FUN_00418579 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x9a4)); }
  (*(i8 *)((char *)&local_8 + 0)) = 0xd;
  /* inlined unwind funclet FUN_00418588 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x968)); }
  (*(i8 *)((char *)&local_8 + 0)) = 0xc;
  /* inlined unwind funclet FUN_00418597 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x92c)); }
  (*(i8 *)((char *)&local_8 + 0)) = 0xb;
  /* inlined unwind funclet FUN_004185a6 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x8f0)); }
  (*(i8 *)((char *)&local_8 + 0)) = 10;
  /* inlined unwind funclet FUN_004185b5 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x8b4)); }
  (*(i8 *)((char *)&local_8 + 0)) = 9;
  /* inlined unwind funclet FUN_004185c4 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x878)); }
  (*(i8 *)((char *)&local_8 + 0)) = 8;
  /* inlined unwind funclet FUN_004185d3 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x83c)); }
  (*(i8 *)((char *)&local_8 + 0)) = 7;
  /* inlined unwind funclet FUN_004185e2 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x800)); }
  (*(i8 *)((char *)&local_8 + 0)) = 6;
  /* inlined unwind funclet FUN_004185f1 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x7c4)); }
  (*(i8 *)((char *)&local_8 + 0)) = 5;
  /* inlined unwind funclet FUN_00418600 */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x788)); }
  (*(i8 *)((char *)&local_8 + 0)) = 4;
  /* inlined unwind funclet FUN_0041860f */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x74c)); }
  (*(i8 *)((char *)&local_8 + 0)) = 3;
  /* inlined unwind funclet FUN_0041861e */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x710)); }
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  /* inlined unwind funclet FUN_0041862d */ { ctrl_dtor((Control *)(*(int *)((iptr)&this) + 0x6d4)); }
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  /* inlined unwind funclet FUN_0041863c */ { FUN_005f2490(*(int *)((iptr)&this) + 0x44c,0x48,9,edit_dtor); }
  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
  /* inlined unwind funclet FUN_00418654 */ { FUN_005f2490(*(int *)((iptr)&this) + 0x2fc,0x38,6,((void *)ADDR(0x00403553, combo_dtor))); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_0041866c */ { frame_wnd_dtor(*(DibSurface **)((iptr)&this)); }
  return;
}
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00447fc2 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl editor_unit_backdrop_sprite_global_init(void)

{
  editor_unit_backdrop_sprite_static_init();
  editor_unit_backdrop_sprite_reg_atexit();
  return;
}

/* 00447fdc auto */
void __cdecl editor_unit_backdrop_sprite_static_init(void)

{
  sprite_init((Sprite *)&editor_unit_backdrop_sprite);
  return;
}

/* 00447ff6 auto */
void __cdecl editor_unit_backdrop_sprite_reg_atexit(void)

{
  _atexit(editor_unit_backdrop_sprite_static_dtor);
  return;
}

/* 00448013 auto */
void __cdecl editor_unit_backdrop_sprite_static_dtor(void)

{
  sprite_destroy((Sprite *)&editor_unit_backdrop_sprite);
  return;
}

/* 0044802d auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl editor_tile_backdrop_sprite_global_init(void)

{
  editor_tile_backdrop_sprite_static_init();
  editor_tile_backdrop_sprite_reg_atexit();
  return;
}

/* 00448047 auto */
void __cdecl editor_tile_backdrop_sprite_static_init(void)

{
  sprite_init((Sprite *)&editor_tile_backdrop_sprite);
  return;
}

/* 00448061 auto */
void __cdecl editor_tile_backdrop_sprite_reg_atexit(void)

{
  _atexit(editor_tile_backdrop_sprite_static_dtor);
  return;
}

/* 0044807e auto */
void __cdecl editor_tile_backdrop_sprite_static_dtor(void)

{
  sprite_destroy((Sprite *)&editor_tile_backdrop_sprite);
  return;
}

/* 004a3060 auto */
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(8)))
#define civ (*(iptr *)(frame_ + FRAME_OFF(12)))
#define leader (*(iptr *)(frame_ + FRAME_OFF(16)))
void __cdecl tribe_editor_load_tables(void)

{
  char *pcVar1;
  size_t sVar2;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (leader = 0; leader < 0x15; leader++) {
    civ = 1;
    while ((civ < 8 && (civs[civ].tribe != leader))) {
      civ++;
    }
    if (civ < 8) {
      sVar2 = 0x18;
      pcVar1 = (char *)civ_name_plural(civ);
      _strncpy(&editor_item_names + (leader * 5 + 0xd2) * 8,pcVar1,sVar2);
      (&editor_item_name24_ends)[(leader * 5 + 0xd2) * 8] = 0;
      sVar2 = 0x18;
      pcVar1 = (char *)civ_adjective(civ);
      _strncpy(&editor_item_names + (leader * 5 + 0x13b) * 8,pcVar1,sVar2);
      (&editor_item_name24_ends)[(leader * 5 + 0x13b) * 8] = 0;
      *(int *)(&editor_items + leader * 0x58) = (int)civ_names[civ].city_style;
    }
    else {
      if (leaders[leader].plural < 1) {
        local_10 = ~(int)leaders[leader].plural + 1;
      }
      else {
        local_10 = (int)leaders[leader].plural;
      }
      sVar2 = 0x18;
      pcVar1 = (char *)label_string(local_10);
      _strncpy(&editor_item_names + (leader * 5 + 0xd2) * 8,pcVar1,sVar2);
      (&editor_item_name24_ends)[(leader * 5 + 0xd2) * 8] = 0;
      if (leaders[leader].adjective < 1) {
        local_14 = ~(int)leaders[leader].adjective + 1;
      }
      else {
        local_14 = (int)leaders[leader].adjective;
      }
      sVar2 = 0x18;
      pcVar1 = (char *)label_string(local_14);
      _strncpy(&editor_item_names + (leader * 5 + 0x13b) * 8,pcVar1,sVar2);
      (&editor_item_name24_ends)[(leader * 5 + 0x13b) * 8] = 0;
      *(int *)(&editor_items + leader * 0x58) = (int)leaders[leader].city_style;
    }
    *(int *)(&editor_item_field1 + leader * 0x58) = leaders[leader].attack + 1;
    *(int *)(&editor_item_field2 + leader * 0x58) = leaders[leader].expand + 1;
    *(int *)(&editor_item_field3 + leader * 0x58) = leaders[leader].civilize + 1;
  }
  for (leader = 0; leader < 7; leader++) {
    sVar2 = 0xf;
    pcVar1 = (char *)label_string(government_names[leader]);
    _strncpy(&editor_govt_names + leader * 0xf,pcVar1,sVar2);
    (&editor_govt_name_ends)[leader * 0xf] = 0;
    sVar2 = 0xf;
    pcVar1 = (char *)label_string(government_titles[leader].male);
    _strncpy(&editor_govt_names + (leader * 3 + 0x15) * 5,pcVar1,sVar2);
    (&editor_govt_name_ends)[leader * 0xf] = 0;
    sVar2 = 0xf;
    pcVar1 = (char *)label_string(government_titles[leader].female);
    _strncpy(&editor_govt_names + (leader * 3 + 0x2a) * 5,pcVar1,sVar2);
    (&editor_govt_name_ends)[leader * 0xf] = 0;
  }
  for (leader = 0; leader < 0x10; leader++) {
    sVar2 = 10;
    pcVar1 = (char *)label_string(commodity_names[leader]);
    _strncpy(&editor_commodity_names + leader * 10,pcVar1,sVar2);
    (&editor_commodity_name_ends)[leader * 10] = 0;
  }
  return;
}
#undef local_14
#undef local_10
#undef civ
#undef leader

/* 004a3426 auto */
#define civ (*(iptr *)(frame_ + FRAME_OFF(4)))
#define leader (*(iptr *)(frame_ + FRAME_OFF(8)))
void __cdecl tribe_editor_apply_tables(void)

{
  char *pcVar1;
  char *pcVar2;
  size_t sVar3;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (leader = 0; leader < 0x15; leader++) {
    civ = 1;
    while ((civ < 8 && (civs[civ].tribe != leader))) {
      civ++;
    }
    if (civ < 8) {
      civ_names[civ].city_style = (i16)*(i32 *)(&editor_items + leader * 0x58);
    }
    leaders[leader].city_style = (i16)*(i32 *)(&editor_items + leader * 0x58);
    leaders[leader].attack = (char)*(i32 *)(&editor_item_field1 + leader * 0x58) - 1;
    leaders[leader].expand = (char)*(i32 *)(&editor_item_field2 + leader * 0x58) - 1;
    leaders[leader].civilize = (char)*(i32 *)(&editor_item_field3 + leader * 0x58) - 1;
  }
  for (leader = 0; leader < 7; leader++) {
    sVar3 = 0xf;
    pcVar1 = &editor_govt_names + leader * 0xf;
    pcVar2 = (char *)label_string(government_names[leader]);
    _strncpy(pcVar2,pcVar1,sVar3);
    sVar3 = 0xf;
    pcVar1 = &editor_govt_names + (leader * 3 + 0x15) * 5;
    pcVar2 = (char *)label_string(government_titles[leader].male);
    _strncpy(pcVar2,pcVar1,sVar3);
    sVar3 = 0xf;
    pcVar1 = &editor_govt_names + (leader * 3 + 0x2a) * 5;
    pcVar2 = (char *)label_string(government_titles[leader].female);
    _strncpy(pcVar2,pcVar1,sVar3);
  }
  for (leader = 0; leader < 0x10; leader++) {
    sVar3 = 10;
    pcVar1 = &editor_commodity_names + leader * 10;
    pcVar2 = (char *)label_string(commodity_names[leader]);
    _strncpy(pcVar2,pcVar1,sVar3);
  }
  return;
}
#undef civ
#undef leader

/* 004a3640 auto */
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
void __cdecl tribe_editor_load_controls(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_c = 1; local_c < 5; local_c++) {
    if (*(int *)(&tribe_editor_ctrl_kinds + local_c * 8) == 9) {
      ctrl_set_text
                ((ControlTextView *)
                 (*(int *)(&tribe_editor_ctrl_slots + local_c * 8) * 0x48 + 0x44c + active_editor_wnd),
                 (iptr)(&editor_item_names + (*(int *)(active_editor_wnd + 0x2ec) * 5 + 0x13b) * 8));
    }
    else if (*(int *)(&tribe_editor_ctrl_kinds + local_c * 8) == 0xc) {
      iVar1 = ctrl_get_id
                        ((ControlIdView *)
                         (active_editor_wnd + 0x2fc + *(int *)(&tribe_editor_ctrl_slots + local_c * 8) * 0x38));
      combo_set_cur_sel
                ((ComboBoxSetSelView *)
                 (active_editor_wnd + 0x2fc + *(int *)(&tribe_editor_ctrl_slots + local_c * 8) * 0x38),
                 *(iptr *)(&editor_ctrl_values + iVar1 * 4 + *(int *)(active_editor_wnd + 0x2ec) * 0x58));
    }
  }
  return;
}
#undef local_c

/* 004a3757 auto */
#define local_24 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_20 (*(char (*)[24])(frame_ + FRAME_OFF(8)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(32)))
void __cdecl tribe_editor_store_controls(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_24 = 1; local_24 < 5; local_24++) {
    if (*(int *)(&tribe_editor_ctrl_kinds + local_24 * 8) == 9) {
      ctrl_get_text
                ((ControlTextView *)
                 (*(int *)(&tribe_editor_ctrl_slots + local_24 * 8) * 0x48 + 0x44c + active_editor_wnd),
                 (iptr)local_20);
      _strncpy(&editor_item_names + (*(int *)(active_editor_wnd + 0x2ec) * 5 + 0x13b) * 8,local_20,0x18);
    }
    else if (*(int *)(&tribe_editor_ctrl_kinds + local_24 * 8) == 0xc) {
      local_8 = combo_get_cur_sel
                          ((ComboBoxGetSelView *)
                           (active_editor_wnd + 0x2fc + *(int *)(&tribe_editor_ctrl_slots + local_24 * 8) * 0x38));
      iVar1 = ctrl_get_id
                        ((ControlIdView *)
                         (active_editor_wnd + 0x2fc + *(int *)(&tribe_editor_ctrl_slots + local_24 * 8) * 0x38));
      *(i32 *)(&editor_ctrl_values + *(int *)(active_editor_wnd + 0x2ec) * 0x58 + iVar1 * 4) = local_8;
    }
  }
  return;
}
#undef local_24
#undef local_20
#undef local_8

/* 004a3889 auto */
void __cdecl tribe_editor_redraw(void)

{
  tribe_editor_paint((C_004083b0_430 *)active_editor_wnd);
  return;
}

/* 004a38a4 auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define local_10 (*(size_t *)(frame_ + FRAME_OFF(0)))
#define local_c (*(size_t *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(8)))
i32 __cdecl tribe_editor_write_governments(FILE *param_1)

{
  char *pcVar1;
  size_t sVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; local_8 < 7; local_8++) {
    text_clear();
    text_append_string_id(government_names[local_8]);
    FUN_005f22e0(&text_buffer,&rules_gov_name_sep_str);
    pcVar1 = (char *)label_string(government_names[local_8]);
    sVar2 = _strlen(pcVar1);
    if (sVar2 < 0xf) {
      pcVar1 = (char *)label_string(government_names[local_8]);
      local_c = _strlen(pcVar1);
    }
    else {
      local_c = 0xf;
    }
    text_append_spaces(0xf - local_c);
    text_append_string_id(government_titles[local_8].male);
    FUN_005f22e0(&text_buffer,&rules_gov_male_title_sep_str);
    pcVar1 = (char *)label_string(government_titles[local_8].male);
    sVar2 = _strlen(pcVar1);
    if (sVar2 < 0xc) {
      pcVar1 = (char *)label_string(government_titles[local_8].male);
      local_10 = _strlen(pcVar1);
    }
    else {
      local_10 = 0xc;
    }
    text_append_spaces(0xc - local_10);
    text_append_string_id(government_titles[local_8].female);
    FUN_005f22e0(&text_buffer,&rules_gov_line_end_str);
    _fputs(&text_buffer,param_1);
  }
  return 1;
}
#undef text_buffer
#undef local_10
#undef local_c
#undef local_8

/* 004a3a21 auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define text_file_handle (*(i32 *)((u8 *)&g.d_0062cd20))
#define text_line_cursor (*(i32 *)((u8 *)&g.d_00673f14))
#define local_d0 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_cc (*(int *)(frame_ + FRAME_OFF(4)))
#define local_c8 (*(size_t *)(frame_ + FRAME_OFF(8)))
#define local_c4 (*(int *)(frame_ + FRAME_OFF(12)))
#define local_c0 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_bc (*(int *)(frame_ + FRAME_OFF(20)))
#define local_b8 (*(size_t *)(frame_ + FRAME_OFF(24)))
#define local_b4 (*(int *)(frame_ + FRAME_OFF(28)))
#define local_b0 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_ac (*(int *)(frame_ + FRAME_OFF(36)))
#define local_a8 (*(size_t *)(frame_ + FRAME_OFF(40)))
#define local_a4 (*(int *)(frame_ + FRAME_OFF(44)))
#define local_a0 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_9c (*(int *)(frame_ + FRAME_OFF(52)))
#define local_98 (*(size_t *)(frame_ + FRAME_OFF(56)))
#define local_94 (*(int *)(frame_ + FRAME_OFF(60)))
#define leader (*(iptr *)(frame_ + FRAME_OFF(72)))
#define local_84 (*(i8 (*)[128])(frame_ + FRAME_OFF(76)))
i32 __cdecl tribe_editor_write_leaders(FILE *param_1,i32 param_2)

{
  i32 uVar1;
  iptr iVar2;
  char *pcVar3;
  size_t sVar4;
  i32 uVar5;
  i32 uVar6;
  i8 frame_[FRAME_OFF(208)] __attribute__((aligned(8)));  /* original stack frame */
  
  uVar1 = text_file_handle;
  text_file_handle = param_2;
  for (leader = 0; leader < 0x15; leader++) {
    text_read_line(1);
    text_next_token();
    text_next_token();
    uVar6 = 1;
    uVar5 = 0;
    iVar2 = text_next_int();
    iVar2 = int_clamp(iVar2,uVar5,uVar6);
    text_next_int();
    text_next_int();
    text_next_token();
    text_next_token();
    text_next_int();
    text_next_int();
    text_next_int();
    FUN_005f22d0(local_84,text_line_cursor);
    text_clear();
    if (leaders[leader].names[0] < 1) {
      local_94 = ~(int)leaders[leader].names[0] + 1;
    }
    else {
      local_94 = (int)leaders[leader].names[0];
    }
    text_append_string_id(local_94);
    FUN_005f22e0(&text_buffer,&rules_leader_male_name_sep_str);
    if (leaders[leader].names[0] < 1) {
      local_9c = ~(int)leaders[leader].names[0] + 1;
    }
    else {
      local_9c = (int)leaders[leader].names[0];
    }
    pcVar3 = (char *)label_string(local_9c);
    sVar4 = _strlen(pcVar3);
    if (sVar4 < 0xd) {
      if (leaders[leader].names[0] < 1) {
        local_a0 = ~(int)leaders[leader].names[0] + 1;
      }
      else {
        local_a0 = (int)leaders[leader].names[0];
      }
      pcVar3 = (char *)label_string(local_a0);
      local_98 = _strlen(pcVar3);
    }
    else {
      local_98 = 0xd;
    }
    text_append_spaces(0xd - local_98);
    if (leaders[leader].names[1] < 1) {
      local_a4 = ~(int)leaders[leader].names[1] + 1;
    }
    else {
      local_a4 = (int)leaders[leader].names[1];
    }
    text_append_string_id(local_a4);
    FUN_005f22e0(&text_buffer,&rules_leader_female_name_sep_str);
    if (leaders[leader].names[1] < 1) {
      local_ac = ~(int)leaders[leader].names[1] + 1;
    }
    else {
      local_ac = (int)leaders[leader].names[1];
    }
    pcVar3 = (char *)label_string(local_ac);
    sVar4 = _strlen(pcVar3);
    if (sVar4 < 0x14) {
      if (leaders[leader].names[1] < 1) {
        local_b0 = ~(int)leaders[leader].names[1] + 1;
      }
      else {
        local_b0 = (int)leaders[leader].names[1];
      }
      pcVar3 = (char *)label_string(local_b0);
      local_a8 = _strlen(pcVar3);
    }
    else {
      local_a8 = 0x14;
    }
    text_append_spaces(0x14 - local_a8);
    text_append_int(iVar2);
    FUN_005f22e0(&text_buffer,&rules_leader_female_flag_sep_str);
    text_append_int((int)leaders[leader].color);
    FUN_005f22e0(&text_buffer,&rules_leader_color_sep_str);
    text_append_int((int)leaders[leader].city_style);
    FUN_005f22e0(&text_buffer,&rules_leader_city_style_sep_str);
    if (leaders[leader].plural < 1) {
      local_b4 = ~(int)leaders[leader].plural + 1;
    }
    else {
      local_b4 = (int)leaders[leader].plural;
    }
    text_append_string_id(local_b4);
    FUN_005f22e0(&text_buffer,&rules_leader_plural_sep_str);
    if (leaders[leader].plural < 1) {
      local_bc = ~(int)leaders[leader].plural + 1;
    }
    else {
      local_bc = (int)leaders[leader].plural;
    }
    pcVar3 = (char *)label_string(local_bc);
    sVar4 = _strlen(pcVar3);
    if (sVar4 < 0xc) {
      if (leaders[leader].plural < 1) {
        local_c0 = ~(int)leaders[leader].plural + 1;
      }
      else {
        local_c0 = (int)leaders[leader].plural;
      }
      pcVar3 = (char *)label_string(local_c0);
      local_b8 = _strlen(pcVar3);
    }
    else {
      local_b8 = 0xc;
    }
    text_append_spaces(0xc - local_b8);
    if (leaders[leader].adjective < 1) {
      local_c4 = ~(int)leaders[leader].adjective + 1;
    }
    else {
      local_c4 = (int)leaders[leader].adjective;
    }
    text_append_string_id(local_c4);
    FUN_005f22e0(&text_buffer,&rules_leader_adjective_sep_str);
    if (leaders[leader].adjective < 1) {
      local_cc = ~(int)leaders[leader].adjective + 1;
    }
    else {
      local_cc = (int)leaders[leader].adjective;
    }
    pcVar3 = (char *)label_string(local_cc);
    sVar4 = _strlen(pcVar3);
    if (sVar4 < 0xb) {
      if (leaders[leader].adjective < 1) {
        local_d0 = ~(int)leaders[leader].adjective + 1;
      }
      else {
        local_d0 = (int)leaders[leader].adjective;
      }
      pcVar3 = (char *)label_string(local_d0);
      local_c8 = _strlen(pcVar3);
    }
    else {
      local_c8 = 0xb;
    }
    text_append_spaces(0xb - local_c8);
    text_append_int_2d((int)leaders[leader].attack);
    FUN_005f22e0(&text_buffer,&rules_leader_attack_sep_str);
    text_append_int_2d((int)leaders[leader].expand);
    FUN_005f22e0(&text_buffer,&rules_leader_expand_sep_str);
    text_append_int_2d((int)leaders[leader].civilize);
    FUN_005f22e0(&text_buffer,&rules_leader_civilize_sep_str);
    FUN_005f22e0(&text_buffer,local_84);
    FUN_005f22e0(&text_buffer,&rules_leader_line_end_str);
    _fputs(&text_buffer,param_1);
  }
  text_file_handle = uVar1;
  return 1;
}
#undef text_buffer
#undef text_file_handle
#undef text_line_cursor
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
#undef leader
#undef local_84

/* 004a41d8 auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
i32 __cdecl tribe_editor_write_caravan(FILE *param_1)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; local_8 < 0x10; local_8++) {
    text_clear();
    text_append_string_id(commodity_names[local_8]);
    FUN_005f22e0(&text_buffer,&rules_commodity_line_end_str);
    _fputs(&text_buffer,param_1);
  }
  return 1;
}
#undef text_buffer
#undef local_8

/* 004a4249 auto */
#define editor_running (*(i32 *)((u8 *)&g.d_006a1d7c))
#define local_24 (*(char (*)[32])(frame_ + FRAME_OFF(4)))
void __cdecl tribe_editor_on_ok(void)

{
  iptr iVar1;
  iptr iVar2;
  char *lpText;
  char *lpCaption;
  UINT uType;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  tribe_editor_store_controls();
  tribe_editor_update_city_file();
  tribe_editor_apply_tables();
  rules_edit_set_section(ADDR(0x62cdcc, ((u8 *)&g.d_0062cdcc)),ADDR(0x401ba4, tribe_editor_write_governments));
  rules_edit_add_section(ADDR(0x62cdd8, ((u8 *)&g.d_0062cdd8)),ADDR(0x40211c, tribe_editor_write_leaders));
  rules_edit_add_section(ADDR(0x62cde0, ((u8 *)&g.d_0062cde0)),ADDR(0x401f87, tribe_editor_write_caravan));
  iVar1 = rules_write_sections();
  if (iVar1 == 0) {
    _sprintf(local_24,s_Error_updating_RULES__s_0062cde8,&lang_file_ext);
    uType = 0x10;
    lpCaption = s_File_I_O_Error_0062ce00;
    lpText = local_24;
    iVar2 = wnd_get_window((WndBase *)(active_editor_wnd + 0x48));
    MessageBoxA(*(HWND *)(iVar2 + 4),lpText,lpCaption,uType);
  }
  editor_running = 0;
  wnd_end_modal_loop((C_00408010_b8 *)(active_editor_wnd + 0x48));
  menu_update_states();
  return;
}
#undef editor_running
#undef local_24

/* 004a4304 auto */
#define local_414 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_410 (*(char (*)[260])(frame_ + FRAME_OFF(8)))
#define local_30c (*(Dialog *)(frame_ + FRAME_OFF(268)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(1024)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(1028)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1032)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1036)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1040)))
void __cdecl tribe_editor_rename_commodity(void)

{
  size_t sVar1;
  i8 frame_[FRAME_OFF(1048)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_30c,0x4000);
  local_8 = 0;
  if (active_editor_wnd == 0) {
    local_414 = 0;
  }
  else {
    local_414 = active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(local_414);
  dialog_load_text(&local_30c,ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x62ce10, ((u8 *)&g.d_0062ce10)),1);
  dialog_set_width((DialogWindowView *)&local_30c,0xdc);
  dialog_set_listbox((DialogTextView *)&local_30c,0x10,0xdc,0);
  for (local_18 = 0; local_18 < 0x10; local_18++) {
    dialog_add_option
              ((DialogOptionList *)&local_30c,(iptr)(&editor_commodity_names + local_18 * 10),local_18,0);
  }
  local_30c.field_118 = 0xdc;
  local_18 = dlg_show_modal(&local_30c,0);
  if (-1 < local_18) {
    do {
      local_14 = dlg_text_input(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x62ce1c, ((u8 *)&g.d_0062ce1c)),9,(iptr)(&editor_commodity_names + local_18 * 10),
                                    (iptr)local_410);
      if (local_14 == -1) break;
      sVar1 = _strlen(local_410);
    } while (sVar1 == 0);
    if (-1 < local_14) {
      _strncpy(&editor_commodity_names + local_18 * 10,local_410,10);
    }
  }
  dlg_set_parent_window(0);
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_004a44a2 */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
  return;
}
#undef local_414
#undef local_410
#undef local_30c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004a44c6 auto */
#define local_414 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_410 (*(char (*)[260])(frame_ + FRAME_OFF(8)))
#define local_30c (*(Dialog *)(frame_ + FRAME_OFF(268)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(1024)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(1028)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1032)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1036)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1040)))
void __cdecl tribe_editor_rename_govt(void)

{
  size_t sVar1;
  i8 frame_[FRAME_OFF(1048)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_30c,0x4000);
  local_8 = 0;
  if (active_editor_wnd == 0) {
    local_414 = 0;
  }
  else {
    local_414 = active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(local_414);
  dialog_load_text(&local_30c,ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x62ce28, ((u8 *)&g.d_0062ce28)),1);
  dialog_set_width((DialogWindowView *)&local_30c,0xdc);
  dialog_set_listbox((DialogTextView *)&local_30c,7,0xdc,0);
  for (local_18 = 0; local_18 < 7; local_18++) {
    dialog_add_option
              ((DialogOptionList *)&local_30c,(iptr)(&editor_govt_names + local_18 * 0xf),local_18,0);
  }
  local_30c.field_118 = 0xdc;
  local_18 = dlg_show_modal(&local_30c,0);
  if (-1 < local_18) {
    do {
      local_14 = dlg_text_input(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x62ce34, ((u8 *)&g.d_0062ce34)),0xe,(iptr)(&editor_govt_names + local_18 * 0xf),
                                    (iptr)local_410);
      if (local_14 == -1) break;
      sVar1 = _strlen(local_410);
    } while (sVar1 == 0);
    if (-1 < local_14) {
      _strncpy(&editor_govt_names + local_18 * 0xf,local_410,0xf);
    }
  }
  dlg_set_parent_window(0);
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_004a4667 */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
  return;
}
#undef local_414
#undef local_410
#undef local_30c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004a468b auto */
#define local_464 (*(char * *)(frame_ + FRAME_OFF(4)))
#define local_460 (*(i8 * *)(frame_ + FRAME_OFF(8)))
#define local_45c (*(i32 *)(frame_ + FRAME_OFF(12)))
#define local_458 (*(i8 * *)(frame_ + FRAME_OFF(16)))
#define local_454 (*(iptr *)(frame_ + FRAME_OFF(20)))
#define local_450 (*(char (*)[260])(frame_ + FRAME_OFF(24)))
#define local_34c (*(char (*)[64])(frame_ + FRAME_OFF(284)))
#define local_30c (*(Dialog *)(frame_ + FRAME_OFF(348)))
#define local_18 (*(uint *)(frame_ + FRAME_OFF(1104)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(1108)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1112)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1116)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1120)))
void __cdecl tribe_editor_rename_title(void)

{
  int iVar1;
  size_t sVar2;
  i8 frame_[FRAME_OFF(1128)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_30c,0x4000);
  local_8 = 0;
  if (active_editor_wnd == 0) {
    local_454 = 0;
  }
  else {
    local_454 = active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(local_454);
  dialog_load_text(&local_30c,ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x62ce40, ((u8 *)&g.d_0062ce40)),1);
  dialog_set_width((DialogWindowView *)&local_30c,400);
  dialog_set_listbox((DialogTextView *)&local_30c,0xe,400,0);
  for (local_18 = 0; (int)local_18 < 0xe; local_18++) {
    if ((local_18 & 1) == 0) {
      iVar1 = ((int)local_18 >> 1) * 3 + 0x15;
    }
    else {
      iVar1 = ((int)local_18 >> 1) * 3 + 0x2a;
    }
    local_458 = &editor_govt_names + iVar1 * 5;
    if ((local_18 & 1) == 0) {
      local_45c = label_string(*(i32 *)(label_string_ids + 0x8fc));
    }
    else {
      local_45c = label_string(*(i32 *)(label_string_ids + 0x900));
    }
    _sprintf(local_34c,s__s__s___s__0062ce4c,&editor_govt_names + ((int)local_18 >> 1) * 0xf,local_45c,
             local_458);
    dialog_add_option((DialogOptionList *)&local_30c,(iptr)local_34c,local_18,0);
  }
  local_30c.field_118 = 400;
  local_18 = dlg_show_modal(&local_30c,0);
  if (-1 < (int)local_18) {
    do {
      if ((local_18 & 1) == 0) {
        iVar1 = ((int)local_18 >> 1) * 3 + 0x15;
      }
      else {
        iVar1 = ((int)local_18 >> 1) * 3 + 0x2a;
      }
      local_460 = &editor_govt_names + iVar1 * 5;
      local_14 = dlg_text_input(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x62ce58, ((u8 *)&g.d_0062ce58)),0xe,(iptr)local_460,(iptr)local_450);
      if (local_14 == -1) break;
      sVar2 = _strlen(local_450);
    } while (sVar2 == 0);
    if (-1 < local_14) {
      if ((local_18 & 1) == 0) {
        iVar1 = ((int)local_18 >> 1) * 3 + 0x15;
      }
      else {
        iVar1 = ((int)local_18 >> 1) * 3 + 0x2a;
      }
      local_464 = &editor_govt_names + iVar1 * 5;
      _strncpy(local_464,local_450,0xf);
    }
  }
  dlg_set_parent_window(0);
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_004a4948 */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
  return;
}
#undef local_464
#undef local_460
#undef local_45c
#undef local_458
#undef local_454
#undef local_450
#undef local_34c
#undef local_30c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004a496c auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
void __cdecl tribe_editor_on_help(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (active_editor_wnd == 0) {
    local_8 = 0;
  }
  else {
    local_8 = active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(local_8);
  popup_text(ADDR(0x62ce6c, ((u8 *)&g.d_0062ce6c)),ADDR(0x62ce64, ((u8 *)&g.d_0062ce64)));
  dlg_set_parent_window(0);
  return;
}
#undef local_8

/* 004a49cb auto */
#define editor_running (*(i32 *)((u8 *)&g.d_006a1d7c))
void __cdecl tribe_editor_on_cancel(void)

{
  editor_running = 0;
  wnd_end_modal_loop((C_00408010_b8 *)(active_editor_wnd + 0x48));
  return;
}
#undef editor_running

/* 004a49f3 auto */
void __cdecl tribe_editor_on_combo(int param_1)

{
  i32 uVar1;
  
  if (param_1 == 0xc9) {
    tribe_editor_store_controls();
    uVar1 = combo_get_cur_sel((ComboBoxGetSelView *)(active_editor_wnd + 0x2fc));
    *(i32 *)(active_editor_wnd + 0x2ec) = uVar1;
    tribe_editor_load_controls();
    tribe_editor_redraw();
  }
  else if (param_1 == 0xca) {
    tribe_editor_store_controls();
    tribe_editor_redraw();
  }
  return;
}

/* 004a4a58 auto */
#define editor_next_ctrl_id (*(int *)((u8 *)&g.d_006a1d80))
#define local_28 (*(u8 * *)(frame_ + FRAME_OFF(0)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
void __thiscall tribe_editor_create_combo(C_004083b0_430 *this,int param_1)

{
  int iVar1;
  int iVar2;
  iptr iVar3;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = *(int *)(&tribe_editor_combo_x_table + param_1 * 8) + this->client_x;
  iVar2 = *(int *)(&tribe_editor_combo_y_table + param_1 * 8) + this->client_y;
  if (param_1 == 0) {
    rect_set_xywh((iptr)local_14,iVar1 - 0x32,iVar2,200,this->field_2e8 << 3);
  }
  else if (param_1 < 2) {
    rect_set_xywh((iptr)local_14,iVar1 - 0xf,iVar2,0x82,this->field_2e8 << 3);
  }
  else {
    rect_set_xywh((iptr)local_14,iVar1,iVar2,100,this->field_2e8 << 3);
  }
  iVar1 = editor_next_ctrl_id;
  editor_next_ctrl_id++;
  if (this == (C_004083b0_430 *)0x0) {
    local_28 = (u8 *)0x0;
  }
  else {
    local_28 = this->pad_48;
  }
  combo_create
            ((Control *)(this->pad_2d4 + param_1 * 0x38 + 0x28),(iptr)local_28,iVar1,
             (iptr)local_14);
  combo_set_font((ComboBoxFontView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),ADDR(0x6a4f90, ((u8 *)&g.d_006a4f90)));
  combo_set_callback((ComboBoxCallbackSetView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),ADDR(0x401424, tribe_editor_on_combo));
  switch(param_1) {
  case 0:
    for (local_18 = 0; local_18 < 0x15; local_18++) {
      combo_add_string
                ((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),
                 (iptr)(&editor_item_names + (local_18 * 5 + 0xd2) * 8));
    }
    break;
  case 1:
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x834));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x838));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x83c));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x840));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
    break;
  case 2:
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x904));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x908));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x90c));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
    break;
  case 3:
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x910));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x914));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x918));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
    break;
  case 4:
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x91c));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x914));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x920));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar3);
  }
  return;
}
#undef editor_next_ctrl_id
#undef local_28
#undef local_18
#undef local_14

/* 004a4eb2 auto */
#define editor_next_ctrl_id (*(int *)((u8 *)&g.d_006a1d80))
#define tribe_editor_edit_x_table (*(i32 *)((u8 *)&g.d_0062cd60))
#define tribe_editor_edit_y_table (*(i32 *)((u8 *)&g.d_0062cd64))
#define local_24 (*(u8 * *)(frame_ + FRAME_OFF(4)))
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
void __thiscall tribe_editor_create_edit(C_004083b0_430 *this,int param_1)

{
  int iVar1;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  rect_set_xywh((iptr)local_14,(&tribe_editor_edit_x_table)[param_1 * 2] + this->client_x,
                     (&tribe_editor_edit_y_table)[param_1 * 2] + this->client_y,100,this->field_2e8 + 6);
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
             (iptr)local_14,ADDR(0x62ce74, ((u8 *)&g.d_0062ce74)));
  edit_set_max_len((EditMaxLenView *)(this[1].pad_48 + param_1 * 0x48 - 0x2c),0x17);
  return;
}
#undef editor_next_ctrl_id
#undef tribe_editor_edit_x_table
#undef tribe_editor_edit_y_table
#undef local_24
#undef local_14

/* 004a4f89 auto */
#define editor_bg_surface (*(int *)((u8 *)&g.d_0062e018))
#define editor_running (*(int *)((u8 *)&g.d_006a1d7c))
#define tribe_editor_edit_x_table (*(int *)((u8 *)&g.d_0062cd60))
#define tribe_editor_edit_y_table (*(int *)((u8 *)&g.d_0062cd64))
#define local_28 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_18 (*(Sprite * *)(frame_ + FRAME_OFF(16)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(20)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_c (*(int *)(frame_ + FRAME_OFF(28)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(32)))
void __thiscall tribe_editor_paint(C_004083b0_430 *this)

{
  byte bVar1;
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
             (*(int *)(&editor_items + *(int *)(active_editor_wnd + 0x2ec) * 0x58) * 0x1e0 + ADDR(0x63ffb8, ((u8 *)&g.d_0063fe8c + 300)));
  bVar1 = sprite_get_key_color(local_18);
  gfx_fill_rect_xywh((iptr)this,local_8,local_c,0x40,0x40,(uint)bVar1);
  sprite_draw_keyed(local_18,(iptr)local_28,(iptr)this,0,local_8,local_c + 8);
  gfx_draw_tiled_frame((iptr)this,local_8,local_c,0x40,0x40,6);
  local_8 = this->client_width + this->client_x - 0x60;
  local_c = this->client_y + 0x20;
  gfx_fill_rect_xywh((iptr)this,local_8,local_c,0x40,0x40,
                     *(i32 *)(&civ_mid_colors + leaders[this->field_2ec].color * 0x10));
  gfx_fill_rect_xywh((iptr)this,local_8 + 0x10,local_c + 0x10,0x20,0x20,
                     *(i32 *)(&civ_primary_colors + leaders[this->field_2ec].color * 0x10));
  gfx_draw_tiled_frame((iptr)this,local_8,local_c,0x40,0x40,6);
  text_set_surface((iptr)this);
  text_set_font(ADDR(0x6a4f90, ((u8 *)&g.d_006a4f90)));
  text_set_colors(10,10,0,0);
  local_8 = tribe_editor_edit_x_table + this->client_x;
  local_c = tribe_editor_edit_y_table + this->client_y;
  gfx_fill_rect_xywh((iptr)this,local_8,local_c,100,this->field_2e8 + 6,0x29);
  gfx_draw_frame_rect((iptr)this,local_8,local_c,100,this->field_2e8 + 6,10);
  text_clear();
  text_append_str((iptr)(&editor_item_names + (*(int *)(active_editor_wnd + 0x2ec) * 5 + 0x13b) * 8));
  text_draw_shadowed((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_8 + 3,local_c + 2);
  text_set_colors(0x29,0x12,1,1);
  local_8 = this->client_x + 0x59;
  local_c = this->client_y + 0x109;
  gfx_draw_tiled_frame((iptr)this,local_8,local_c,0x17c,0x45,6);
  local_10 = this->client_x + (int)this->client_width / 2;
  local_14 = this->client_y + 0x10d;
  text_clear();
  text_append_label(0x25d);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = tribe_editor_city_style_x + this->client_x + 0x32;
  local_14 = ((tribe_editor_city_style_y + this->client_y) - this->field_2e8) - 2;
  text_clear();
  text_append_label(0x219);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = tribe_editor_edit_x_table + this->client_x + 0x32;
  local_14 = ((tribe_editor_edit_y_table + this->client_y) - this->field_2e8) - 2;
  text_clear();
  text_append_label(0x249);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = tribe_editor_attack_x + this->client_x + 0x32;
  local_14 = ((tribe_editor_attack_y + this->client_y) - this->field_2e8) - 2;
  text_clear();
  text_append_label(0x1e5);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = tribe_editor_expand_x + this->client_x + 0x32;
  local_14 = ((tribe_editor_expand_y + this->client_y) - this->field_2e8) - 2;
  text_clear();
  text_append_label(0x24a);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = tribe_editor_civilize_x + this->client_x + 0x32;
  local_14 = ((tribe_editor_civilize_y + this->client_y) - this->field_2e8) - 2;
  text_clear();
  text_append_label(0x24b);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  wnd_blit_surface((DibSurface *)this);
  return;
}
#undef editor_bg_surface
#undef editor_running
#undef tribe_editor_edit_x_table
#undef tribe_editor_edit_y_table
#undef local_28
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 004a54d9 auto */
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
void __thiscall tribe_editor_main(C_004083b0_430 *this)

{
  DibSurface *this_00;
  uptr uVar1;
  i32 uVar2;
  int iVar3;
  iptr iVar4;
  int iVar5;
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
  this->field_2d8 = 0x230;
  this->field_2dc = 0x17c;
  this->field_2ec = 0;
  editor_next_ctrl_id = 0xc9;
  surface_load_gif_file(editor_bg_surface,ADDR(0x62ce78, ((u8 *)&g.d_0062ce78)),10,0xc0,(iptr)&local_444);
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
  uVar2 = label_string(*(i32 *)(label_string_ids + 0x930));
  frame_wnd_create
            ((FrameWindow *)this,uVar2,uVar6,uVar7,uVar8,uVar9,uVar10,uVar11,uVar12,uVar13);
  tribe_editor_load_tables();
  for (local_460 = 0; local_460 < 5; local_460++) {
    if (*(int *)(&tribe_editor_ctrl_kinds + local_460 * 8) == 9) {
      tribe_editor_create_edit(this,*(i32 *)(&tribe_editor_ctrl_slots + local_460 * 8));
    }
    else if (*(int *)(&tribe_editor_ctrl_kinds + local_460 * 8) == 0xc) {
      tribe_editor_create_combo(this,*(i32 *)(&tribe_editor_ctrl_slots + local_460 * 8));
    }
  }
  iVar3 = sprite_width
                    ((Sprite *)(&terrain_base_sprites + this->field_2ec * 0x3c));
  this->field_2e0 = iVar3 + 0x2d;
  iVar3 = font_line_spacing((GameFont *)dialog_font_ptr);
  this->field_2e4 = iVar3 + 8;
  iVar3 = this->client_y + (int)(this->field_2e4 * 3) / 2 + 0x101;
  uVar10 = this->client_x;
  rect_set_xywh((iptr)local_454,uVar10 + 0x69,iVar3,this->field_2e0,this->field_2e4);
  if (this == (C_004083b0_430 *)0x0) {
    local_474 = (u8 *)0x0;
  }
  else {
    local_474 = this->pad_48;
  }
  iVar4 = label_string(*(i32 *)(label_string_ids + 0x940));
  button_create
            ((Control *)(this[2].pad_48 + 0x84),(iptr)local_474,0x65,(iptr)local_454,iVar4);
  button_set_callback((Control *)(this[2].pad_48 + 0x84),ADDR(0x402775, tribe_editor_rename_commodity));
  rect_set_xywh((iptr)local_454,uVar10 + 0xe1,iVar3,this->field_2e0,this->field_2e4);
  if (this == (C_004083b0_430 *)0x0) {
    local_478 = (u8 *)0x0;
  }
  else {
    local_478 = this->pad_48;
  }
  iVar4 = label_string(*(i32 *)(label_string_ids + 0x944));
  button_create
            ((Control *)(this[2].pad_104 + 4),(iptr)local_478,0x65,(iptr)local_454,iVar4);
  button_set_callback((Control *)(this[2].pad_104 + 4),ADDR(0x401631, tribe_editor_rename_govt));
  rect_set_xywh((iptr)local_454,uVar10 + 0x159,iVar3,this->field_2e0,this->field_2e4);
  if (this == (C_004083b0_430 *)0x0) {
    local_47c = (u8 *)0x0;
  }
  else {
    local_47c = this->pad_48;
  }
  iVar4 = label_string(*(i32 *)(label_string_ids + 0x948));
  button_create
            ((Control *)&this[2].field_144,(iptr)local_47c,0x65,(iptr)local_454,iVar4);
  button_set_callback((Control *)&this[2].field_144,ADDR(0x402bda, tribe_editor_rename_title));
  iVar3 = font_line_spacing((GameFont *)dialog_font_ptr);
  this->field_2e4 = iVar3 + 8;
  this->field_2e0 = (int)(this->client_width - 8) / 3;
  iVar5 = (this->client_y + this->client_height) - (this->field_2e4 + 2);
  iVar3 = this->client_x + 2;
  rect_set_xywh((iptr)local_454,iVar3,iVar5,this->field_2e0,this->field_2e4);
  if (this == (C_004083b0_430 *)0x0) {
    local_480 = (u8 *)0x0;
  }
  else {
    local_480 = this->pad_48;
  }
  iVar4 = label_string(*(i32 *)(label_string_ids + 0x3f8));
  button_create
            ((Control *)&this[1].field_2a4,(iptr)local_480,0x65,(iptr)local_454,iVar4);
  button_set_callback((Control *)&this[1].field_2a4,ADDR(0x40275c, tribe_editor_on_ok));
  iVar3 = iVar3 + this->field_2e0 + 2;
  rect_set_xywh((iptr)local_454,iVar3,iVar5,this->field_2e0,this->field_2e4);
  if (this == (C_004083b0_430 *)0x0) {
    local_484 = (u8 *)0x0;
  }
  else {
    local_484 = this->pad_48;
  }
  iVar4 = label_string(*(i32 *)(label_string_ids + 0x8ec));
  button_create
            ((Control *)&this[1].field_2e0,(iptr)local_484,0x66,(iptr)local_454,iVar4);
  button_set_callback((Control *)&this[1].field_2e0,ADDR(0x401bea, tribe_editor_on_help));
  rect_set_xywh((iptr)local_454,iVar3 + this->field_2e0 + 2,iVar5,this->field_2e0,
                     this->field_2e4);
  if (this == (C_004083b0_430 *)0x0) {
    local_488 = (u8 *)0x0;
  }
  else {
    local_488 = this->pad_48;
  }
  iVar4 = label_string(*(i32 *)(label_string_ids + 0x3fc));
  button_create
            ((Control *)&this[1].field_31c,(iptr)local_488,0x66,(iptr)local_454,iVar4);
  button_set_callback((Control *)&this[1].field_31c,ADDR(0x40152d, tribe_editor_on_cancel));
  ctrl_set_cancel_button((Control *)&this[1].field_31c);
  wnd_set_keyboard_nav((Wnd *)this->pad_48,0);
  combo_set_cur_sel((ComboBoxSetSelView *)&this->field_2fc,this->field_2ec);
  tribe_editor_load_controls();
  this->field_2f8 = 5;
  wnd_set_move_handler((C_00408130 *)(this->pad_48 + 0x10),ADDR(0x4019d8, editor_wnd_on_move_close_dropdowns));
  wnd_set_redraw_callback((SurfaceWindow *)this,ADDR(0x403cf1, tribe_editor_redraw));
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
  /* inlined unwind funclet FUN_004a5d6e */ { palette_destroy((GamePalette *)((iptr)&local_444)); }
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

/* 004a5d92 auto */
#define local_b58 (*(C_004083b0_a28 *)(frame_ + FRAME_OFF(0)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(2888)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(2892)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(2896)))
void __cdecl tribe_editor_run(void)

{
  i8 frame_[FRAME_OFF(2904)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  editor_wnd_ctor(&local_b58);
  local_8 = 0;
  tribe_editor_main((C_004083b0_430 *)&local_b58);
  wnd_repaint((SurfaceWindow *)&map_views);
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_004a5deb */ { editor_wnd_dtor((EditorWindow *)((iptr)&local_b58)); }
  return;
}
#undef local_b58
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004cc8f0 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl editor_text_dlg_wnd_global_init(void)

{
  editor_text_dlg_wnd_static_init();
  editor_text_dlg_wnd_reg_atexit();
  return;
}

/* 004cc90a auto */
void __cdecl editor_text_dlg_wnd_static_init(void)

{
  frame_wnd_ctor((SurfaceWindow *)&editor_text_dlg_wnd);
  return;
}

/* 004cc924 auto */
void __cdecl editor_text_dlg_wnd_reg_atexit(void)

{
  _atexit(editor_text_dlg_wnd_static_dtor);
  return;
}

/* 004cc941 auto */
void __cdecl editor_text_dlg_wnd_static_dtor(void)

{
  frame_wnd_dtor((DibSurface *)&editor_text_dlg_wnd);
  return;
}

/* 004cc95b auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl editor_text_edit_global_init(void)

{
  editor_text_edit_static_init();
  editor_text_edit_reg_atexit();
  return;
}

/* 004cc975 auto */
void __cdecl editor_text_edit_static_init(void)

{
  edit_ctor((C_0040f380_48 *)&editor_text_edit);
  return;
}

/* 004cc98f auto */
void __cdecl editor_text_edit_reg_atexit(void)

{
  _atexit(editor_text_edit_static_dtor);
  return;
}

/* 004cc9ac auto */
void __cdecl editor_text_edit_static_dtor(void)

{
  edit_dtor((Control *)&editor_text_edit);
  return;
}

/* 004cc9c6 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E41
    _$E46
    _$E51
    _$E56
     6 names - too many to list
   
   Library: Visual Studio 1998 Debug */

void __cdecl editor_font_global_init(void)

{
  editor_font_static_init();
  editor_font_reg_atexit();
  return;
}

/* 004cc9e0 auto */
void __cdecl editor_font_static_init(void)

{
  font_init((GameFont *)&editor_font,0,0x10);
  return;
}

/* 004cc9fe auto */
void __cdecl editor_font_reg_atexit(void)

{
  _atexit(editor_font_static_dtor);
  return;
}

/* 004cca1b auto */
void __cdecl editor_font_static_dtor(void)

{
  font_destroy((GameFont *)&editor_font);
  return;
}

/* 004cd8a6 auto */
#define local_234 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_230 (*(i32 *)(frame_ + FRAME_OFF(8)))
#define civ (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_228 (*(FILE * *)(frame_ + FRAME_OFF(16)))
#define local_224 (*(FILE * *)(frame_ + FRAME_OFF(20)))
#define local_220 (*(char (*)[260])(frame_ + FRAME_OFF(24)))
#define leader (*(iptr *)(frame_ + FRAME_OFF(284)))
#define local_118 (*(char *)(frame_ + FRAME_OFF(288)))
#define local_117 (*(char (*)[255])(frame_ + FRAME_OFF(289)))
#define local_18 (*(i8 (*)[16])(frame_ + FRAME_OFF(544)))
#define local_8 (*(char * *)(frame_ + FRAME_OFF(560)))
i32 __cdecl tribe_editor_update_city_file(void)

{
  int iVar1;
  char *pcVar2;
  size_t _MaxCount;
  i8 frame_[FRAME_OFF(568)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_230 = 0;
  local_228 = (FILE *)0x0;
  local_224 = (FILE *)0x0;
  FUN_005f22d0(local_18,s_CITY__0062e16c);
  FUN_005f22e0(local_18,&lang_file_ext);
  __getcwd(local_220,0x104);
  __chdir(&scenario_dir_path);
  iVar1 = _strcmp(&scenario_dir_path,&game_home_dir);
  if (iVar1 != 0) {
    iVar1 = file_exists((iptr)local_18);
    if (iVar1 == 0) {
LAB_004cdc50:
      local_230 = 1;
    }
    else {
      iVar1 = file_exists(ADDR(0x62e174, ((u8 *)&g.d_0062e174)));
      if (((iVar1 == 0) || (iVar1 = FUN_005f66b0(s_CITY_TMP_0062e180), iVar1 == 0)) &&
         (iVar1 = FUN_005f6650(local_18,s_CITY_TMP_0062e18c), iVar1 == 0)) {
        local_224 = (FILE *)file_open_path(ADDR(0x62e19c, ((u8 *)&g.d_0062e19c)),ADDR(0x62e198, ((u8 *)&g.d_0062e198)));
        local_228 = (FILE *)file_open_path((iptr)local_18,ADDR(0x62e1a8, ((u8 *)&g.d_0062e1a8)));
        if ((local_224 != (FILE *)0x0) && (local_228 != (FILE *)0x0)) {
          do {
            while( true ) {
              pcVar2 = _fgets(&local_118,0x100,local_224);
              if (pcVar2 == (char *)0x0) goto LAB_004cdc50;
              if ((local_118 != '@') || (iVar1 = __strnicmp(local_117,&city_file_stop_str,4), iVar1 == 0))
              break;
              for (leader = 0; leader < 0x15; leader++) {
                civ = 1;
                while ((civ < 8 && (civs[civ].tribe != leader))) {
                  civ++;
                }
                if (civ < 8) {
                  local_8 = civ_names[civ].tribe_name;
                }
                else {
                  if (leaders[leader].plural < 1) {
                    local_234 = ~(int)leaders[leader].plural + 1;
                  }
                  else {
                    local_234 = (int)leaders[leader].plural;
                  }
                  local_8 = (char *)label_string(local_234);
                }
                _MaxCount = _strlen(local_8);
                iVar1 = __strnicmp(local_117,local_8,_MaxCount);
                if (iVar1 == 0) {
                  _sprintf(&local_118,s__c_s_0062e1b4,0x40,
                           &editor_item_names + (leader * 5 + 0xd2) * 8);
                  __strupr(&local_118);
                  iVar1 = _fputs(&local_118,local_228);
                  if (iVar1 == -1) goto LAB_004cdc5a;
                  break;
                }
              }
              if ((leader == 0x15) && (iVar1 = _fputs(&local_118,local_228), iVar1 == -1))
              goto LAB_004cdc5a;
            }
            iVar1 = _fputs(&local_118,local_228);
          } while (iVar1 != -1);
        }
      }
    }
  }
LAB_004cdc5a:
  if (local_224 != (FILE *)0x0) {
    _fclose(local_224);
  }
  if (local_228 != (FILE *)0x0) {
    _fclose(local_228);
  }
  iVar1 = file_exists(ADDR(0x62e1bc, ((u8 *)&g.d_0062e1bc)));
  if (iVar1 != 0) {
    FUN_005f66b0(s_CITY_TMP_0062e1c8);
  }
  __chdir(local_220);
  return local_230;
}
#undef local_234
#undef local_230
#undef civ
#undef local_228
#undef local_224
#undef local_220
#undef leader
#undef local_118
#undef local_117
#undef local_18
#undef local_8

/* 004cdcf6 auto */
i32 __cdecl editor_numeric_edit_filter(i32 param_1,int param_2)

{
  i32 uVar1;
  
  if ((((param_2 < 0x30) || (0x39 < param_2)) && (param_2 != 0x2d)) && (param_2 != 0xd6)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

/* 004cdd3d auto */
#define dlg_check_bits (*(uint *)((u8 *)&g.d_00631ed8))
#define dlg_help_pressed (*(u32 *)((u8 *)&g.d_00631edc))
#define local_314 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_30c (*(i32 *)(frame_ + FRAME_OFF(12)))
#define local_308 (*(Dialog *)(frame_ + FRAME_OFF(16)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(772)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(776)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(780)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(784)))
i32 __cdecl editor_options_dialog(iptr param_1,i32 param_2,uint param_3,i32 param_4)

{
  int iVar1;
  i8 frame_[FRAME_OFF(792)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_308,0x4000);
  local_8 = 0;
  if (active_editor_wnd == 0) {
    local_314 = 0;
  }
  else {
    local_314 = active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(local_314);
  iVar1 = dialog_load_text_section(&local_308,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),param_1,param_2,0,0,0,0,param_4);
  if (iVar1 == 0) {
    if (((byte)local_308.field_3c & 4) != 0) {
      for (local_14 = 0; local_14 < (int)local_308.field_28; local_14++) {
        dialog_set_option_checked
                  ((DialogOptionList *)&local_308,local_14,1 << ((byte)local_14 & 0x1f) & dlg_check_bits
                  );
      }
    }
    for (local_14 = 0; local_14 < (int)local_308.field_28; local_14++) {
      dialog_set_option_disabled
                ((DialogOptionList *)&local_308,local_14,
                 (uint)((1 << ((byte)local_14 & 0x1f) & param_3) != 0));
    }
    local_30c = dlg_show_modal(&local_308,0);
    dlg_help_pressed = local_308.field_dc;
    if (((byte)local_308.field_3c & 4) != 0) {
      dlg_check_bits = 0;
      for (local_14 = 0; local_14 < (int)local_308.field_28; local_14++) {
        iVar1 = dialog_option_is_checked((DialogOptionList *)&local_308,local_14);
        if (iVar1 != 0) {
          dlg_check_bits = dlg_check_bits | 1 << ((byte)local_14 & 0x1f);
        }
      }
    }
  }
  dlg_set_parent_window(0);
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_004cdf26 */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
  return local_30c;
}
#undef dlg_check_bits
#undef dlg_help_pressed
#undef local_314
#undef local_30c
#undef local_308
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004cdf4b auto */
#define editor_value_clamped (*(i32 *)((u8 *)&g.d_0062e014))
int __cdecl editor_clamp_value(int param_1,int param_2,int param_3)

{
  if (param_1 < param_2) {
    editor_value_clamped = 1;
  }
  else {
    param_2 = param_1;
    if (param_3 < param_1) {
      editor_value_clamped = 1;
      param_2 = param_3;
    }
  }
  return param_2;
}
#undef editor_value_clamped

/* 004cdfa4 auto */
#define frame_border_width (*(int *)((u8 *)&g.d_0063359c))
#define frame_caption_height (*(int *)((u8 *)&g.d_00633598))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define _DAT_006a19d4 (*(i32 *)((u8 *)&g.d_006a19d4))
#define _DAT_006a1abc (*(i32 *)((u8 *)&g.d_006a1abc))
#define _DAT_006a1b68 (*(i32 *)((u8 *)&g.d_006a1b68))
#define _DAT_006a1b8c (*(i32 *)((u8 *)&g.d_006a1b8c))
#define _DAT_006a1b90 (*(i32 *)((u8 *)&g.d_006a1b90))
#define _DAT_006a1b94 (*(i32 *)((u8 *)&g.d_006a1b94))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(8)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl
editor_text_dlg_create(int param_1,uint param_2,int param_3,int param_4,int param_5,int param_6,int param_7,
            int param_8,int param_9)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 == 0) {
    FUN_005f22d0(&editor_text_dlg_title,&editor_text_dlg_empty_title);
  }
  else {
    FUN_005f22d0(&editor_text_dlg_title,param_1);
  }
  _DAT_006a1b94 = &ui_text_font;
  _DAT_006a1b8c = &caption_font;
  _DAT_006a1b90 = &caption_small_font;
  _DAT_006a19d4 = param_2;
  editor_text_dlg_caption_height = param_8;
  editor_text_dlg_border_width = param_9;
  editor_text_dlg_resize_border = param_7;
  _DAT_006a1abc = 0;
  _DAT_006a1b68 = 0;
  if ((param_2 & 4) != 0) {
    editor_text_dlg_caption_height = frame_caption_height;
    editor_text_dlg_border_width = frame_border_width;
  }
  if ((param_2 & 8) == 0) {
    local_8 = 0x202;
  }
  else {
    local_8 = 0x802;
  }
  if (editor_text_dlg_caption_height != 0) {
    local_8 = local_8 | 0x400;
  }
  if (param_7 != 0) {
    local_8 = local_8 | 0x1000;
  }
  if ((param_2 & 2) == 0) {
    param_5 += editor_text_dlg_border_width * 2;
    param_6 = param_6 + editor_text_dlg_caption_height + editor_text_dlg_border_width;
  }
  if ((param_2 & 1) != 0) {
    param_3 = (screen_width >> 1) - (param_5 >> 1);
    param_4 = (screen_height >> 1) - (param_6 >> 1);
  }
  if (active_editor_wnd == 0) {
    local_c = 0;
  }
  else {
    local_c = active_editor_wnd + 0x48;
  }
  wnd_create_with_surface
            ((DibSurface *)&editor_text_dlg_wnd,0,local_8,param_3,param_4,param_5,param_6,ADDR(0x6a8c00, ((u8 *)&g.d_006a8c00)),
             local_c);
  if (editor_text_dlg_caption_height != 0) {
    wnd_set_caption_height((WndBase *)&editor_text_dlg_inner,editor_text_dlg_caption_height);
  }
  if (editor_text_dlg_resize_border != 0) {
    wnd_set_resize_border((WndBase *)&editor_text_dlg_inner,editor_text_dlg_resize_border);
  }
  frame_wnd_layout((FrameWindow *)&editor_text_dlg_wnd);
  return;
}
#undef frame_border_width
#undef frame_caption_height
#undef screen_height
#undef _DAT_006a19d4
#undef _DAT_006a1abc
#undef _DAT_006a1b68
#undef _DAT_006a1b8c
#undef _DAT_006a1b90
#undef _DAT_006a1b94
#undef local_c
#undef local_8

/* 004ce196 auto */
#define editor_text_active (*(i32 *)((u8 *)&g.d_006a4f9c))
#define local_108 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_104 (*(char (*)[256])(frame_ + FRAME_OFF(4)))
void __cdecl editor_text_dlg_on_ok(void)

{
  int iVar1;
  size_t sVar2;
  i32 uVar3;
  i8 frame_[FRAME_OFF(264)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_108 = 0; local_108 < 0x14; local_108++) {
    *(i32 *)(editor_text_lines_out + local_108 * 4) = 0;
  }
  events_compact();
  local_108 = 0;
  do {
    if (0x13 < local_108) {
LAB_004ce2ca:
      editor_text_result = 1;
      editor_text_active = 0;
      wnd_end_modal_loop((C_00408010_b8 *)&editor_text_dlg_inner);
      return;
    }
    iVar1 = edit_get_line
                      ((EditLineView *)&editor_text_edit,local_108,(iptr)local_104,0x100);
    if (iVar1 == 0) {
      *(i32 *)(editor_text_lines_out + local_108 * 4) = 0;
    }
    else {
      sVar2 = _strlen(local_104);
      uVar3 = memblock_alloc_checked(ADDR(0x64b984, ((u8 *)&g.d_0064b984)),sVar2 + 1);
      *(i32 *)(editor_text_lines_out + local_108 * 4) = uVar3;
      if (*(int *)(editor_text_lines_out + local_108 * 4) == 0) {
        *(i32 *)(editor_text_lines_out + local_108 * 4) = 0;
        goto LAB_004ce2ca;
      }
      FUN_005f22d0(*(i32 *)(editor_text_lines_out + local_108 * 4),local_104);
    }
    local_108++;
  } while( true );
}
#undef editor_text_active
#undef local_108
#undef local_104

/* 004ce2f3 auto */
#define editor_text_active (*(i32 *)((u8 *)&g.d_006a4f9c))
void __cdecl editor_text_dlg_on_cancel(void)

{
  editor_text_result = 0;
  editor_text_active = 0;
  wnd_end_modal_loop((C_00408010_b8 *)&editor_text_dlg_inner);
  return;
}
#undef editor_text_active

/* 004ce322 auto */
void __cdecl editor_text_dlg_redraw(void)

{
  frame_wnd_draw_caption((FrameWindow *)&editor_text_dlg_wnd);
  gfx_fill_rect(ADDR(0x6a18c0, ((u8 *)&g.d_006a18c0)),ADDR(0x6a1b7c, ((u8 *)&g.d_006a1b7c)),0x1d);
  text_set_surface(ADDR(0x6a18c0, ((u8 *)&g.d_006a18c0)));
  text_set_font(ADDR(0x6a4f90, ((u8 *)&g.d_006a4f90)));
  text_set_colors(0x29,0x12,1,1);
  wnd_blit_surface((DibSurface *)&editor_text_dlg_wnd);
  return;
}

/* 004ce38a auto */
#define editor_text_active (*(int *)((u8 *)&g.d_006a4f9c))
#define local_ac (*(int *)(frame_ + FRAME_OFF(4)))
#define local_a4 (*(Control *)(frame_ + FRAME_OFF(12)))
#define local_68 (*(int *)(frame_ + FRAME_OFF(72)))
#define local_64 (*(int *)(frame_ + FRAME_OFF(76)))
#define local_60 (*(int *)(frame_ + FRAME_OFF(80)))
#define local_5c (*(i8 (*)[16])(frame_ + FRAME_OFF(84)))
#define local_4c (*(Control *)(frame_ + FRAME_OFF(100)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(160)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(164)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(168)))
/* WARNING: Removing unreachable block (ram,0x004ce598) */
/* WARNING: Removing unreachable block (ram,0x004ce49e) */
/* WARNING: Removing unreachable block (ram,0x004ce621) */

i32 __cdecl editor_text_edit_dialog(iptr param_1,i32 param_2)

{
  i32 uVar1;
  int iVar2;
  iptr iVar3;
  i8 frame_[FRAME_OFF(176)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  button_ctor(&local_4c);
  local_8 = 0;
  button_ctor(&local_a4);
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),1);
  editor_text_active = 1;
  editor_text_lines_out = param_1;
  local_68 = font_line_spacing((GameFont *)dialog_font_ptr);
  local_68 += 8;
  iVar2 = font_line_spacing((GameFont *)&editor_font);
  editor_text_dlg_create(param_2,0xd,0,0x14,600,iVar2 * 0x14 + local_68,0,0,0);
  local_68 = font_line_spacing((GameFont *)dialog_font_ptr);
  local_68 += 8;
  local_60 = (editor_text_dlg_client_width - 6) / 2;
  rect_set_xywh((iptr)local_5c,editor_text_dlg_client_x + 4,editor_text_dlg_client_y + 4,editor_text_dlg_client_width - 9,
                     (editor_text_dlg_client_height - local_68) - 9);
  edit_create_styled
            ((EditControl *)&editor_text_edit,ADDR(0x6a1908, ((u8 *)&g.d_006a1908)),0xc9,(iptr)local_5c,0,2,1);
  for (local_ac = 0; (local_ac < 0x14 && (*(int *)(param_1 + local_ac * 4) != 0));
      local_ac = local_ac + 1) {
    if (local_ac != 0) {
      edit_replace_sel((Control *)&editor_text_edit,ADDR(0x62e1d8, ((u8 *)&g.d_0062e1d8)));
    }
    edit_replace_sel
              ((Control *)&editor_text_edit,*(iptr *)(param_1 + local_ac * 4));
  }
  iVar2 = (editor_text_dlg_client_y + editor_text_dlg_client_height) - (local_68 + 2);
  local_64 = editor_text_dlg_client_x + 2;
  rect_set_xywh((iptr)local_5c,local_64,iVar2,local_60,local_68);
  iVar3 = label_string(*(i32 *)(label_string_ids + 0x3f8));
  button_create(&local_4c,ADDR(0x6a1908, ((u8 *)&g.d_006a1908)),0x65,(iptr)local_5c,iVar3);
  button_set_callback(&local_4c,ADDR(0x401d84, editor_text_dlg_on_ok));
  local_64 = local_64 + local_60 + 2;
  rect_set_xywh((iptr)local_5c,local_64,iVar2,local_60,local_68);
  iVar3 = label_string(*(i32 *)(label_string_ids + 0x3fc));
  button_create(&local_a4,ADDR(0x6a1908, ((u8 *)&g.d_006a1908)),0x66,(iptr)local_5c,iVar3);
  button_set_callback(&local_a4,ADDR(0x4011d1, editor_text_dlg_on_cancel));
  ctrl_set_cancel_button(&local_a4);
  wnd_set_redraw_callback((SurfaceWindow *)&editor_text_dlg_wnd,ADDR(0x401582, editor_text_dlg_redraw));
  wnd_repaint((SurfaceWindow *)&editor_text_dlg_wnd);
  window_show((C_004083b0_4 *)&editor_text_dlg_wnd);
  wnd_run_modal_loop((C_00408010_b8 *)&editor_text_dlg_inner);
  while (editor_text_active != 0) {
    win_pump_one_message();
  }
  frame_wnd_close((DibSurface *)&editor_text_dlg_wnd);
  uVar1 = editor_text_result;
  local_8 = local_8 & 0xffffff00;
  /* inlined unwind funclet FUN_004ce6ed */ { ctrl_dtor((Control *)((iptr)&local_a4)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet FUN_004ce6f9 */ { ctrl_dtor((Control *)((iptr)&local_4c)); }
  return uVar1;
}
#undef editor_text_active
#undef local_ac
#undef local_a4
#undef local_68
#undef local_64
#undef local_60
#undef local_5c
#undef local_4c
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004ce71b auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define local_10 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_c (*(size_t *)(frame_ + FRAME_OFF(4)))
uint __cdecl editor_check_city_name(iptr param_1)

{
  int iVar1;
  size_t sVar2;
  size_t sVar3;
  uint uVar4;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = text_open_section(ADDR(0x62e1dc, ((u8 *)&g.d_0062e1dc)),0);
  if (iVar1 == 0) {
    do {
      iVar1 = text_read_line(1);
      if (iVar1 == 0) goto LAB_004ce7c5;
      sVar2 = _strlen((char *)param_1);
      sVar3 = _strlen(&text_buffer);
      if (sVar3 < sVar2) {
        local_c = _strlen((char *)param_1);
      }
      else {
        local_c = _strlen(&text_buffer);
      }
      iVar1 = __strnicmp((char *)param_1,&text_buffer,local_c);
    } while (iVar1 != 0);
    text_close_file();
    uVar4 = 1;
  }
  else {
LAB_004ce7c5:
    if (active_editor_wnd == 0) {
      local_10 = 0;
    }
    else {
      local_10 = active_editor_wnd + 0x48;
    }
    dlg_set_parent_window(local_10);
    text_set_string_arg(0,param_1);
    iVar1 = popup_debug_text(ADDR(0x62e1e4, ((u8 *)&g.d_0062e1e4)));
    dlg_set_parent_window(0);
    uVar4 = (uint)(iVar1 == 0);
  }
  return uVar4;
}
#undef text_buffer
#undef local_10
#undef local_c

/* 004ce83d auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl editor_wnd_on_move_close_dropdowns(void)

{
  HWND hWnd;
  UINT Msg;
  WPARAM wParam;
  LPARAM lParam;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; local_8 < *(int *)(active_editor_wnd + 0x2f8); local_8++) {
    lParam = 0;
    wParam = 0;
    Msg = 0x14f;
    hWnd = (HWND)control_get_hwnd
                           ((ControlHwndView *)(active_editor_wnd + 0x2fc + local_8 * 0x38));
    SendMessageA(hWnd,Msg,wParam,lParam);
  }
  return;
}
#undef local_8

/* 004ce8a4 auto */
#define local_120 (*(char (*)[260])(frame_ + FRAME_OFF(0)))
#define local_1c (*(char (*)[20])(frame_ + FRAME_OFF(260)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(280)))
i32 __cdecl editor_input_long(iptr param_1,iptr param_2,int param_3,iptr param_4)

{
  long lVar1;
  i8 frame_[FRAME_OFF(288)] __attribute__((aligned(8)));  /* original stack frame */
  
  __itoa(param_3,local_1c,10);
  local_8 = dlg_text_input(param_1,param_2,6,(iptr)local_1c,(iptr)local_120);
  lVar1 = _atol(local_120);
  *(long *)param_4 = lVar1;
  return local_8;
}
#undef local_120
#undef local_1c
#undef local_8

/* 00553dfd auto */
#define local_210 (*(char (*)[260])(frame_ + FRAME_OFF(0)))
#define local_10c (*(CHAR (*)[260])(frame_ + FRAME_OFF(260)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(520)))
i32 __cdecl editor_create_scenario_folder(void)

{
  int iVar1;
  size_t sVar2;
  DWORD DVar3;
  i8 frame_[FRAME_OFF(528)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = _strcmp(&scenario_dir_path,&game_home_dir);
  if (iVar1 == 0) {
    do {
      local_8 = 0;
      do {
        iVar1 = dlg_text_input(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x633698, ((u8 *)&g.d_00633698)),8,ADDR(0x633694, ((u8 *)&g.d_00633694)),(iptr)local_210);
        if (iVar1 < 0) {
          return 0;
        }
        sVar2 = _strlen(local_210);
      } while (sVar2 == 0);
      iVar1 = str_find_bad_filename_char((iptr)local_210);
      if (iVar1 == 0) {
        FUN_005f22d0(local_10c,&game_home_dir);
        FUN_005f22e0(local_10c,s__SCENARIO__006336ac);
        FUN_005f22e0(local_10c,local_210);
        DVar3 = GetFileAttributesA(local_10c);
        if (DVar3 != 0xffffffff) {
          text_set_string_arg(0,(iptr)local_10c);
          popup_text(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x6336b8, ((u8 *)&g.d_006336b8)));
          local_8 = 1;
        }
      }
      else {
        text_set_string_arg(0,(iptr)local_210);
        popup_text(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x6336a4, ((u8 *)&g.d_006336a4)));
        local_8 = 1;
      }
    } while (local_8 != 0);
    FUN_00607920(local_10c);
    FUN_005f22d0(&scenario_dir_path,local_10c);
    FUN_005f22e0(local_10c,s__SOUND_006336c4);
    FUN_00607920(local_10c);
    FUN_005f22d0(local_10c,&scenario_dir_path);
    FUN_005f22e0(local_10c,&scenario_path_sep_str);
    FUN_005f22e0(local_10c,local_210);
    FUN_005f22e0(local_10c,&scenario_file_ext_str);
    save_write_game((iptr)local_10c,1);
  }
  return 1;
}
#undef local_210
#undef local_10c
#undef local_8

/* 00553ff6 auto */
void __cdecl editor_toggle_scenario_flag(void)

{
  int iVar1;
  
  if (((game.game_options & 0x8000) == 0) && ((game.game_flags & 0x10) == 0)) {
    iVar1 = popup_game_with_sprite(ADDR(0x6336d8, ((u8 *)&g.d_006336d8)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
    if (iVar1 == 0) {
      return;
    }
    game.game_flags = game.game_flags | 0x10;
    game.game_options = game.game_options | 0x8000;
    iVar1 = editor_create_scenario_folder();
    if (iVar1 != 0) {
      popup_text(ADDR(0x6336ec, ((u8 *)&g.d_006336ec)),ADDR(0x6336e4, ((u8 *)&g.d_006336e4)));
      game.game_flags = game.game_flags | 0x80;
    }
  }
  else if (((game.game_options & 0x8000) == 0) ||
          (((game.game_flags & 0x80) == 0 ||
           (iVar1 = _strcmp(&scenario_dir_path,&game_home_dir), iVar1 == 0)))) {
    iVar1 = _strcmp(&scenario_dir_path,&game_home_dir);
    if (iVar1 == 0) {
      popup_text(ADDR(0x6336fc, ((u8 *)&g.d_006336fc)),ADDR(0x6336f4, ((u8 *)&g.d_006336f4)));
    }
    iVar1 = editor_create_scenario_folder();
    if (iVar1 == 0) {
      return;
    }
    game.game_options = game.game_options | 0x8000;
    game.game_flags = game.game_flags | 0x80;
  }
  else {
    game.game_flags = game.game_flags & 0xff7f;
  }
  menu_update_states();
  return;
}
