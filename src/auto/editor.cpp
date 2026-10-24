/* The game, the scenario editors: functions translated from the original
 * (tools/gen_c.py, now edited directly), in address order. */
#include "auto_common.h"

/* 00417fa0 auto */
DocumentWindow * __thiscall editor_wnd_ctor(DocumentWindow *self)

{
  i32 eh_frame;
  i8 *eh_prev;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  frame_wnd_ctor((SurfaceWindow *)self);
  eh_state = 0;
  crt_vector_ctor_iterator(&self->dialog_h,0x38,6,((code *)combo_ctor),((code *)combo_dtor));
  (*((char *)&eh_state + 0)) = 1;
  crt_vector_ctor_iterator(self->editor_edit_controls,0x48,9,(code *)edit_ctor,
               (code *)edit_dtor);
  (*((char *)&eh_state + 0)) = 2;
  button_ctor((Control *)self->editor_ok_button);
  (*((char *)&eh_state + 0)) = 3;
  button_ctor((Control *)self->editor_help_button);
  (*((char *)&eh_state + 0)) = 4;
  button_ctor((Control *)self->editor_cancel_button);
  (*((char *)&eh_state + 0)) = 5;
  button_ctor((Control *)self->editor_rename_button);
  (*((char *)&eh_state + 0)) = 6;
  button_ctor((Control *)self->editor_icon_button);
  (*((char *)&eh_state + 0)) = 7;
  button_ctor((Control *)self->editor_misc_button);
  (*((char *)&eh_state + 0)) = 8;
  button_ctor((Control *)self->terrain_coast_button);
  (*((char *)&eh_state + 0)) = 9;
  button_ctor((Control *)((u8 *)&self->terrain_misc_button));
  (*((char *)&eh_state + 0)) = 10;
  button_ctor((Control *)self->unit_flags_button);
  (*((char *)&eh_state + 0)) = 0xb;
  button_ctor((Control *)self->unit_sound_button);
  (*((char *)&eh_state + 0)) = 0xc;
  button_ctor((Control *)self->add_trigger_button);
  (*((char *)&eh_state + 0)) = 0xd;
  button_ctor((Control *)self->edit_trigger_button);
  (*((char *)&eh_state + 0)) = 0xe;
  button_ctor((Control *)((u8 *)&self->delete_trigger_button));
  (*((char *)&eh_state + 0)) = 0xf;
  button_ctor((Control *)self->add_action_button);
  (*((char *)&eh_state + 0)) = 0x10;
  button_ctor((Control *)&self->edit_action_button);
  (*((char *)&eh_state + 0)) = 0x11;
  button_ctor((Control *)&((PictureWindow *)self)->delete_action_button);
  (*((char *)&eh_state + 0)) = 0x12;
  checkbox_ctor((Control *)((u8 *)&((PictureWindow *)self)->editor_list_box));
  (*((char *)&eh_state + 0)) = 0x13;
  checkbox_ctor((Control *)(((PictureWindow *)self)->trigger_listbox));
  eh_state = (eh_state & 0xffffff00 | (byte)(0x14));
  checkbox_ctor((Control *)(((PictureWindow *)self)->action_listbox));
  self->vtable = (u32)((pointer *)ptr_fun_rest);
  return self;
}

/* 004183d0 auto */
void __thiscall editor_wnd_dtor(void *self)

{
  i32 eh_handler;
  i8 *eh_prev;
  int eh_state;
  
  eh_state = eh_state & 0xff;
  (*((char *)&eh_state + 0)) = 0x14;
  /* inlined unwind funclet 0041851f */ { listbox_dtor((ListBoxControl *)(*(int *)&self + 0xb0c)); }
  (*((char *)&eh_state + 0)) = 0x13;
  /* inlined unwind funclet 0041852e */ { listbox_dtor((ListBoxControl *)(*(int *)&self + 0xad0)); }
  (*((char *)&eh_state + 0)) = 0x12;
  /* inlined unwind funclet 0041853d */ { listbox_dtor((ListBoxControl *)(*(int *)&self + 0xa94)); }
  (*((char *)&eh_state + 0)) = 0x11;
  /* inlined unwind funclet 0041854c */ { ctrl_dtor((Control *)(*(int *)&self + 0xa58)); }
  (*((char *)&eh_state + 0)) = 0x10;
  /* inlined unwind funclet 0041855b */ { ctrl_dtor((Control *)(*(int *)&self + 0xa1c)); }
  (*((char *)&eh_state + 0)) = 0xf;
  /* inlined unwind funclet 0041856a */ { ctrl_dtor((Control *)(*(int *)&self + 0x9e0)); }
  (*((char *)&eh_state + 0)) = 0xe;
  /* inlined unwind funclet 00418579 */ { ctrl_dtor((Control *)(*(int *)&self + 0x9a4)); }
  (*((char *)&eh_state + 0)) = 0xd;
  /* inlined unwind funclet 00418588 */ { ctrl_dtor((Control *)(*(int *)&self + 0x968)); }
  (*((char *)&eh_state + 0)) = 0xc;
  /* inlined unwind funclet 00418597 */ { ctrl_dtor((Control *)(*(int *)&self + 0x92c)); }
  (*((char *)&eh_state + 0)) = 0xb;
  /* inlined unwind funclet 004185a6 */ { ctrl_dtor((Control *)(*(int *)&self + 0x8f0)); }
  (*((char *)&eh_state + 0)) = 10;
  /* inlined unwind funclet 004185b5 */ { ctrl_dtor((Control *)(*(int *)&self + 0x8b4)); }
  (*((char *)&eh_state + 0)) = 9;
  /* inlined unwind funclet 004185c4 */ { ctrl_dtor((Control *)(*(int *)&self + 0x878)); }
  (*((char *)&eh_state + 0)) = 8;
  /* inlined unwind funclet 004185d3 */ { ctrl_dtor((Control *)(*(int *)&self + 0x83c)); }
  (*((char *)&eh_state + 0)) = 7;
  /* inlined unwind funclet 004185e2 */ { ctrl_dtor((Control *)(*(int *)&self + 0x800)); }
  (*((char *)&eh_state + 0)) = 6;
  /* inlined unwind funclet 004185f1 */ { ctrl_dtor((Control *)(*(int *)&self + 0x7c4)); }
  (*((char *)&eh_state + 0)) = 5;
  /* inlined unwind funclet 00418600 */ { ctrl_dtor((Control *)(*(int *)&self + 0x788)); }
  (*((char *)&eh_state + 0)) = 4;
  /* inlined unwind funclet 0041860f */ { ctrl_dtor((Control *)(*(int *)&self + 0x74c)); }
  (*((char *)&eh_state + 0)) = 3;
  /* inlined unwind funclet 0041861e */ { ctrl_dtor((Control *)(*(int *)&self + 0x710)); }
  (*((char *)&eh_state + 0)) = 2;
  /* inlined unwind funclet 0041862d */ { ctrl_dtor((Control *)(*(int *)&self + 0x6d4)); }
  (*((char *)&eh_state + 0)) = 1;
  /* inlined unwind funclet 0041863c */ { crt_vector_dtor_iterator((u8 *)self + 0x44c,0x48,9,(code *)edit_dtor); }
  eh_state = eh_state & 0xffffff00;
  /* inlined unwind funclet 00418654 */ { crt_vector_dtor_iterator((u8 *)self + 0x2fc,0x38,6,((code *)combo_dtor)); }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 0041866c */ { frame_wnd_dtor(*(DibSurface **)&self); }
  return;
}

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
  sprite_init((Sprite *)((i8 *)&editor_unit_backdrop_sprite));
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
  sprite_destroy((Sprite *)((i8 *)&editor_unit_backdrop_sprite));
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
  sprite_init((Sprite *)((i8 *)&editor_tile_backdrop_sprite_block.editor_tile_backdrop_sprite));
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
  sprite_destroy((Sprite *)((i8 *)&editor_tile_backdrop_sprite_block.editor_tile_backdrop_sprite));
  return;
}

/* 004a3060 auto */
void __cdecl tribe_editor_load_tables(void)

{
  char *text;
  size_t max_len;
  int adjective_id;
  int plural_id;
  iptr civ;
  iptr leader;
  
  for (leader = 0; leader < 0x15; leader++) {
    civ = 1;
    while ((civ < 8 && (civs[civ].tribe != leader))) {
      civ++;
    }
    if (civ < 8) {
      max_len = 0x18;
      text = civ_name_plural(civ);
      _strncpy(((i8 *)&editor_text_dlg_wnd_block.editor_item_names) + (leader * 5 + 0xd2) * 8,text,max_len);
      (((i8 *)&editor_text_dlg_wnd_block.editor_item_name24_ends))[(leader * 5 + 0xd2) * 8] = 0;
      max_len = 0x18;
      text = (char *)civ_adjective(civ);
      _strncpy(((i8 *)&editor_text_dlg_wnd_block.editor_item_names) + (leader * 5 + 0x13b) * 8,text,max_len);
      (((i8 *)&editor_text_dlg_wnd_block.editor_item_name24_ends))[(leader * 5 + 0x13b) * 8] = 0;
      *(int *)(((i8 *)&editor_text_dlg_wnd_block.editor_items) + leader * 0x58) = (int)civ_names[civ].city_style;
    }
    else {
      if (leaders[leader].plural < 1) {
        plural_id = ~(int)leaders[leader].plural + 1;
      }
      else {
        plural_id = (int)leaders[leader].plural;
      }
      max_len = 0x18;
      text = label_string(plural_id);
      _strncpy(((i8 *)&editor_text_dlg_wnd_block.editor_item_names) + (leader * 5 + 0xd2) * 8,text,max_len);
      (((i8 *)&editor_text_dlg_wnd_block.editor_item_name24_ends))[(leader * 5 + 0xd2) * 8] = 0;
      if (leaders[leader].adjective < 1) {
        adjective_id = ~(int)leaders[leader].adjective + 1;
      }
      else {
        adjective_id = (int)leaders[leader].adjective;
      }
      max_len = 0x18;
      text = label_string(adjective_id);
      _strncpy(((i8 *)&editor_text_dlg_wnd_block.editor_item_names) + (leader * 5 + 0x13b) * 8,text,max_len);
      (((i8 *)&editor_text_dlg_wnd_block.editor_item_name24_ends))[(leader * 5 + 0x13b) * 8] = 0;
      *(int *)(((i8 *)&editor_text_dlg_wnd_block.editor_items) + leader * 0x58) = (int)leaders[leader].city_style;
    }
    *(int *)(((i8 *)&editor_text_dlg_wnd_block.editor_item_field1) + leader * 0x58) = leaders[leader].attack + 1;
    *(int *)(((i8 *)&editor_text_dlg_wnd_block.editor_item_field2) + leader * 0x58) = leaders[leader].expand + 1;
    *(int *)(((i8 *)&editor_text_dlg_wnd_block.editor_item_field3) + leader * 0x58) = leaders[leader].civilize + 1;
  }
  for (leader = 0; leader < 7; leader++) {
    max_len = 0xf;
    text = label_string(government_names[leader]);
    _strncpy(((i8 *)&editor_text_dlg_wnd_block.editor_govt_names) + leader * 0xf,text,max_len);
    (((i8 *)&editor_text_dlg_wnd_block.editor_govt_name_ends))[leader * 0xf] = 0;
    max_len = 0xf;
    text = label_string(government_titles[leader].male);
    _strncpy(((i8 *)&editor_text_dlg_wnd_block.editor_govt_names) + (leader * 3 + 0x15) * 5,text,max_len);
    (((i8 *)&editor_text_dlg_wnd_block.editor_govt_name_ends))[leader * 0xf] = 0;
    max_len = 0xf;
    text = label_string(government_titles[leader].female);
    _strncpy(((i8 *)&editor_text_dlg_wnd_block.editor_govt_names) + (leader * 3 + 0x2a) * 5,text,max_len);
    (((i8 *)&editor_text_dlg_wnd_block.editor_govt_name_ends))[leader * 0xf] = 0;
  }
  for (leader = 0; leader < 0x10; leader++) {
    max_len = 10;
    text = label_string(commodity_names[leader]);
    _strncpy(((i8 *)&editor_text_dlg_wnd_block.editor_commodity_names) + leader * 10,text,max_len);
    (((i8 *)&editor_text_dlg_wnd_block.editor_commodity_name_ends))[leader * 10] = 0;
  }
  return;
}

/* 004a3426 auto */
void __cdecl tribe_editor_apply_tables(void)

{
  char *src;
  char *dest;
  size_t max_len;
  iptr civ;
  iptr leader;
  
  for (leader = 0; leader < 0x15; leader++) {
    civ = 1;
    while ((civ < 8 && (civs[civ].tribe != leader))) {
      civ++;
    }
    if (civ < 8) {
      civ_names[civ].city_style = (i16)*(i32 *)(((i8 *)&editor_text_dlg_wnd_block.editor_items) + leader * 0x58);
    }
    leaders[leader].city_style = (i16)*(i32 *)(((i8 *)&editor_text_dlg_wnd_block.editor_items) + leader * 0x58);
    leaders[leader].attack = (char)*(i32 *)(((i8 *)&editor_text_dlg_wnd_block.editor_item_field1) + leader * 0x58) - 1;
    leaders[leader].expand = (char)*(i32 *)(((i8 *)&editor_text_dlg_wnd_block.editor_item_field2) + leader * 0x58) - 1;
    leaders[leader].civilize = (char)*(i32 *)(((i8 *)&editor_text_dlg_wnd_block.editor_item_field3) + leader * 0x58) - 1;
  }
  for (leader = 0; leader < 7; leader++) {
    max_len = 0xf;
    src = ((i8 *)&editor_text_dlg_wnd_block.editor_govt_names) + leader * 0xf;
    dest = label_string(government_names[leader]);
    _strncpy(dest,src,max_len);
    max_len = 0xf;
    src = ((i8 *)&editor_text_dlg_wnd_block.editor_govt_names) + (leader * 3 + 0x15) * 5;
    dest = label_string(government_titles[leader].male);
    _strncpy(dest,src,max_len);
    max_len = 0xf;
    src = ((i8 *)&editor_text_dlg_wnd_block.editor_govt_names) + (leader * 3 + 0x2a) * 5;
    dest = label_string(government_titles[leader].female);
    _strncpy(dest,src,max_len);
  }
  for (leader = 0; leader < 0x10; leader++) {
    max_len = 10;
    src = ((i8 *)&editor_text_dlg_wnd_block.editor_commodity_names) + leader * 10;
    dest = label_string(commodity_names[leader]);
    _strncpy(dest,src,max_len);
  }
  return;
}

/* 004a3640 auto */
void __cdecl tribe_editor_load_controls(void)

{
  int ctrl_id;
  int i;
  
  for (i = 1; i < 5; i++) {
    if (*(int *)(((i8 *)&tribe_editor_ctrl_kinds_block.tribe_editor_ctrl_kinds) + i * 8) == 9) {
      ctrl_set_text
                ((ControlTextView *)
                 (*(int *)(((i8 *)&tribe_editor_ctrl_kinds_block.tribe_editor_ctrl_slots) + i * 8) * 0x48 + 0x44c + editor_text_dlg_wnd_block.active_editor_wnd),
                 (const char *)(((i8 *)&editor_text_dlg_wnd_block.editor_item_names) + (*(int *)(editor_text_dlg_wnd_block.active_editor_wnd + 0x2ec) * 5 + 0x13b) * 8));
    }
    else if (*(int *)(((i8 *)&tribe_editor_ctrl_kinds_block.tribe_editor_ctrl_kinds) + i * 8) == 0xc) {
      ctrl_id = ctrl_get_id
                        ((ControlIdView *)
                         (editor_text_dlg_wnd_block.active_editor_wnd + 0x2fc + *(int *)(((i8 *)&tribe_editor_ctrl_kinds_block.tribe_editor_ctrl_slots) + i * 8) * 0x38));
      combo_set_cur_sel
                ((ComboBoxSetSelView *)
                 (editor_text_dlg_wnd_block.active_editor_wnd + 0x2fc + *(int *)(((i8 *)&tribe_editor_ctrl_kinds_block.tribe_editor_ctrl_slots) + i * 8) * 0x38),
                 *(iptr *)(((i8 *)&editor_text_dlg_wnd_block.editor_ctrl_values) + ctrl_id * 4 + *(int *)(editor_text_dlg_wnd_block.active_editor_wnd + 0x2ec) * 0x58));
    }
  }
  return;
}

/* 004a3757 auto */
void __cdecl tribe_editor_store_controls(void)

{
  int ctrl_id;
  int i;
  char text[24];
  i32 selection;
  
  for (i = 1; i < 5; i++) {
    if (*(int *)(((i8 *)&tribe_editor_ctrl_kinds_block.tribe_editor_ctrl_kinds) + i * 8) == 9) {
      ctrl_get_text
                ((ControlTextView *)
                 (*(int *)(((i8 *)&tribe_editor_ctrl_kinds_block.tribe_editor_ctrl_slots) + i * 8) * 0x48 + 0x44c + editor_text_dlg_wnd_block.active_editor_wnd),
                 (char *)text);
      _strncpy(((i8 *)&editor_text_dlg_wnd_block.editor_item_names) + (*(int *)(editor_text_dlg_wnd_block.active_editor_wnd + 0x2ec) * 5 + 0x13b) * 8,text,0x18);
    }
    else if (*(int *)(((i8 *)&tribe_editor_ctrl_kinds_block.tribe_editor_ctrl_kinds) + i * 8) == 0xc) {
      selection = combo_get_cur_sel
                          ((ComboBoxGetSelView *)
                           (editor_text_dlg_wnd_block.active_editor_wnd + 0x2fc + *(int *)(((i8 *)&tribe_editor_ctrl_kinds_block.tribe_editor_ctrl_slots) + i * 8) * 0x38));
      ctrl_id = ctrl_get_id
                        ((ControlIdView *)
                         (editor_text_dlg_wnd_block.active_editor_wnd + 0x2fc + *(int *)(((i8 *)&tribe_editor_ctrl_kinds_block.tribe_editor_ctrl_slots) + i * 8) * 0x38));
      *(i32 *)(((i8 *)&editor_text_dlg_wnd_block.editor_ctrl_values) + *(int *)(editor_text_dlg_wnd_block.active_editor_wnd + 0x2ec) * 0x58 + ctrl_id * 4) = selection;
    }
  }
  return;
}

/* 004a3889 auto */
void __cdecl tribe_editor_redraw(void)

{
  tribe_editor_paint((ViewWindow *)editor_text_dlg_wnd_block.active_editor_wnd);
  return;
}

/* 004a38a4 auto */
i32 __cdecl tribe_editor_write_governments(FILE *file)

{
  char *text;
  size_t len;
  size_t title_len;
  size_t name_len;
  iptr gov;
  
  for (gov = 0; gov < 7; gov++) {
    text_clear();
    text_append_string_id(government_names[gov]);
    crt_strcat(((i8 *)&map_views_block.text_buffer),((i8 *)&tribe_editor_ctrl_kinds_block.rules_gov_name_sep_str));
    text = label_string(government_names[gov]);
    len = _strlen(text);
    if (len < 0xf) {
      text = label_string(government_names[gov]);
      name_len = _strlen(text);
    }
    else {
      name_len = 0xf;
    }
    text_append_spaces(0xf - name_len);
    text_append_string_id(government_titles[gov].male);
    crt_strcat(((i8 *)&map_views_block.text_buffer),((i8 *)&tribe_editor_ctrl_kinds_block.rules_gov_male_title_sep_str));
    text = label_string(government_titles[gov].male);
    len = _strlen(text);
    if (len < 0xc) {
      text = label_string(government_titles[gov].male);
      title_len = _strlen(text);
    }
    else {
      title_len = 0xc;
    }
    text_append_spaces(0xc - title_len);
    text_append_string_id(government_titles[gov].female);
    crt_strcat(((i8 *)&map_views_block.text_buffer),((i8 *)&tribe_editor_ctrl_kinds_block.rules_gov_line_end_str));
    _fputs(((i8 *)&map_views_block.text_buffer),file);
  }
  return 1;
}

/* 004a3a21 auto */
i32 __cdecl tribe_editor_write_leaders(FILE *file,i32 src_handle)

{
  i32 saved_handle;
  iptr female_flag;
  char *text;
  size_t len;
  i32 min_val;
  i32 max_val;
  int adjective_id3;
  int adjective_id2;
  size_t adjective_len;
  int adjective_id;
  int plural_id3;
  int plural_id2;
  size_t plural_len;
  int plural_id;
  int female_id3;
  int female_id2;
  size_t female_len;
  int female_id;
  int male_id3;
  int male_id2;
  size_t male_len;
  int male_id;
  iptr leader;
  i8 line_tail[128];
  
  saved_handle = (*(i32 *)&text_file_handle);
  (*(i32 *)&text_file_handle) = src_handle;
  for (leader = 0; leader < 0x15; leader++) {
    text_read_line(1);
    text_next_token();
    text_next_token();
    max_val = 1;
    min_val = 0;
    female_flag = text_next_int();
    female_flag = int_clamp(female_flag,min_val,max_val);
    text_next_int();
    text_next_int();
    text_next_token();
    text_next_token();
    text_next_int();
    text_next_int();
    text_next_int();
    crt_strcpy(line_tail,(const char *)((const void *)map_views_block.text_line_cursor));
    text_clear();
    if (leaders[leader].names[0] < 1) {
      male_id = ~(int)leaders[leader].names[0] + 1;
    }
    else {
      male_id = (int)leaders[leader].names[0];
    }
    text_append_string_id(male_id);
    crt_strcat(((i8 *)&map_views_block.text_buffer),((i8 *)&tribe_editor_ctrl_kinds_block.rules_leader_male_name_sep_str));
    if (leaders[leader].names[0] < 1) {
      male_id2 = ~(int)leaders[leader].names[0] + 1;
    }
    else {
      male_id2 = (int)leaders[leader].names[0];
    }
    text = label_string(male_id2);
    len = _strlen(text);
    if (len < 0xd) {
      if (leaders[leader].names[0] < 1) {
        male_id3 = ~(int)leaders[leader].names[0] + 1;
      }
      else {
        male_id3 = (int)leaders[leader].names[0];
      }
      text = label_string(male_id3);
      male_len = _strlen(text);
    }
    else {
      male_len = 0xd;
    }
    text_append_spaces(0xd - male_len);
    if (leaders[leader].names[1] < 1) {
      female_id = ~(int)leaders[leader].names[1] + 1;
    }
    else {
      female_id = (int)leaders[leader].names[1];
    }
    text_append_string_id(female_id);
    crt_strcat(((i8 *)&map_views_block.text_buffer),((i8 *)&tribe_editor_ctrl_kinds_block.rules_leader_female_name_sep_str));
    if (leaders[leader].names[1] < 1) {
      female_id2 = ~(int)leaders[leader].names[1] + 1;
    }
    else {
      female_id2 = (int)leaders[leader].names[1];
    }
    text = label_string(female_id2);
    len = _strlen(text);
    if (len < 0x14) {
      if (leaders[leader].names[1] < 1) {
        female_id3 = ~(int)leaders[leader].names[1] + 1;
      }
      else {
        female_id3 = (int)leaders[leader].names[1];
      }
      text = label_string(female_id3);
      female_len = _strlen(text);
    }
    else {
      female_len = 0x14;
    }
    text_append_spaces(0x14 - female_len);
    text_append_int(female_flag);
    crt_strcat(((i8 *)&map_views_block.text_buffer),((i8 *)&tribe_editor_ctrl_kinds_block.rules_leader_female_flag_sep_str));
    text_append_int((int)leaders[leader].color);
    crt_strcat(((i8 *)&map_views_block.text_buffer),((i8 *)&tribe_editor_ctrl_kinds_block.rules_leader_color_sep_str));
    text_append_int((int)leaders[leader].city_style);
    crt_strcat(((i8 *)&map_views_block.text_buffer),((i8 *)&tribe_editor_ctrl_kinds_block.rules_leader_city_style_sep_str));
    if (leaders[leader].plural < 1) {
      plural_id = ~(int)leaders[leader].plural + 1;
    }
    else {
      plural_id = (int)leaders[leader].plural;
    }
    text_append_string_id(plural_id);
    crt_strcat(((i8 *)&map_views_block.text_buffer),((i8 *)&tribe_editor_ctrl_kinds_block.rules_leader_plural_sep_str));
    if (leaders[leader].plural < 1) {
      plural_id2 = ~(int)leaders[leader].plural + 1;
    }
    else {
      plural_id2 = (int)leaders[leader].plural;
    }
    text = label_string(plural_id2);
    len = _strlen(text);
    if (len < 0xc) {
      if (leaders[leader].plural < 1) {
        plural_id3 = ~(int)leaders[leader].plural + 1;
      }
      else {
        plural_id3 = (int)leaders[leader].plural;
      }
      text = label_string(plural_id3);
      plural_len = _strlen(text);
    }
    else {
      plural_len = 0xc;
    }
    text_append_spaces(0xc - plural_len);
    if (leaders[leader].adjective < 1) {
      adjective_id = ~(int)leaders[leader].adjective + 1;
    }
    else {
      adjective_id = (int)leaders[leader].adjective;
    }
    text_append_string_id(adjective_id);
    crt_strcat(((i8 *)&map_views_block.text_buffer),((i8 *)&tribe_editor_ctrl_kinds_block.rules_leader_adjective_sep_str));
    if (leaders[leader].adjective < 1) {
      adjective_id2 = ~(int)leaders[leader].adjective + 1;
    }
    else {
      adjective_id2 = (int)leaders[leader].adjective;
    }
    text = label_string(adjective_id2);
    len = _strlen(text);
    if (len < 0xb) {
      if (leaders[leader].adjective < 1) {
        adjective_id3 = ~(int)leaders[leader].adjective + 1;
      }
      else {
        adjective_id3 = (int)leaders[leader].adjective;
      }
      text = label_string(adjective_id3);
      adjective_len = _strlen(text);
    }
    else {
      adjective_len = 0xb;
    }
    text_append_spaces(0xb - adjective_len);
    text_append_int_2d((int)leaders[leader].attack);
    crt_strcat(((i8 *)&map_views_block.text_buffer),((i8 *)&tribe_editor_ctrl_kinds_block.rules_leader_attack_sep_str));
    text_append_int_2d((int)leaders[leader].expand);
    crt_strcat(((i8 *)&map_views_block.text_buffer),((i8 *)&tribe_editor_ctrl_kinds_block.rules_leader_expand_sep_str));
    text_append_int_2d((int)leaders[leader].civilize);
    crt_strcat(((i8 *)&map_views_block.text_buffer),((i8 *)&tribe_editor_ctrl_kinds_block.rules_leader_civilize_sep_str));
    crt_strcat(((i8 *)&map_views_block.text_buffer),line_tail);
    crt_strcat(((i8 *)&map_views_block.text_buffer),((i8 *)&tribe_editor_ctrl_kinds_block.rules_leader_line_end_str));
    _fputs(((i8 *)&map_views_block.text_buffer),file);
  }
  (*(i32 *)&text_file_handle) = saved_handle;
  return 1;
}

/* 004a41d8 auto */
i32 __cdecl tribe_editor_write_caravan(FILE *file)

{
  iptr commodity;
  
  for (commodity = 0; commodity < 0x10; commodity++) {
    text_clear();
    text_append_string_id(commodity_names[commodity]);
    crt_strcat(((i8 *)&map_views_block.text_buffer),((i8 *)&tribe_editor_ctrl_kinds_block.rules_commodity_line_end_str));
    _fputs(((i8 *)&map_views_block.text_buffer),file);
  }
  return 1;
}

/* 004a4249 auto */
void __cdecl tribe_editor_on_ok(void)

{
  iptr ok;
  iptr wnd;
  char *lpText;
  char *lpCaption;
  UINT uType;
  char msg[32];
  
  tribe_editor_store_controls();
  tribe_editor_update_city_file();
  tribe_editor_apply_tables();
  rules_edit_set_section((iptr)&str_governments_2,(iptr)tribe_editor_write_governments);
  rules_edit_add_section((const char *)&str_leaders_2,(iptr)tribe_editor_write_leaders);
  rules_edit_add_section((const char *)&str_caravan_5,(iptr)tribe_editor_write_caravan);
  ok = rules_write_sections();
  if (ok == 0) {
    _sprintf(msg,str_error_updating_rules_s_2,((i8 *)&lang_file_ext));
    uType = 0x10;
    lpCaption = str_file_i_o_error_2;
    lpText = msg;
    wnd = wnd_get_window((WndBase *)(editor_text_dlg_wnd_block.active_editor_wnd + 0x48));
    MessageBoxA(*(HWND *)(wnd + 4),lpText,lpCaption,uType);
  }
  editor_text_dlg_wnd_block.editor_running = 0;
  wnd_end_modal_loop((ModalMenuWindow *)(editor_text_dlg_wnd_block.active_editor_wnd + 0x48));
  menu_update_states();
  return;
}

/* 004a4304 auto */
void __cdecl tribe_editor_rename_commodity(void)

{
  size_t len;
  iptr parent_wnd2;
  char input_buf[260];
  Dialog dialog2;
  int choice;
  int input_result;
  i32 eh_handler;
  i8 *eh_prev;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  dialog_ctor(&dialog2,0x4000);
  eh_state = 0;
  if (editor_text_dlg_wnd_block.active_editor_wnd == 0) {
    parent_wnd2 = 0;
  }
  else {
    parent_wnd2 = editor_text_dlg_wnd_block.active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(parent_wnd2);
  dialog_load_text(&dialog2,(const char *)&str_debug_11,(const char *)&str_renamecommo,1);
  dialog_set_width((DialogWindowView *)&dialog2,0xdc);
  dialog_set_listbox((DialogTextView *)&dialog2,0x10,0xdc,0);
  for (choice = 0; choice < 0x10; choice++) {
    dialog_add_option
              ((DialogOptionList *)&dialog2,(const char *)(((i8 *)&editor_text_dlg_wnd_block.editor_commodity_names) + choice * 10),choice,0);
  }
  dialog2.option_width = 0xdc;
  choice = dlg_show_modal(&dialog2,0);
  if (-1 < choice) {
    do {
      input_result = dlg_text_input((iptr)&str_debug_11,(const char *)&str_commoname,9,(iptr)(((i8 *)&editor_text_dlg_wnd_block.editor_commodity_names) + choice * 10),
                                    (iptr)input_buf);
      if (input_result == -1) break;
      len = _strlen(input_buf);
    } while (len == 0);
    if (-1 < input_result) {
      _strncpy(((i8 *)&editor_text_dlg_wnd_block.editor_commodity_names) + choice * 10,input_buf,10);
    }
  }
  dlg_set_parent_window(0);
  eh_state = 0xffffffff;
  /* inlined unwind funclet 004a44a2 */ { dialog_dtor(&dialog2); }
  return;
}

/* 004a44c6 auto */
void __cdecl tribe_editor_rename_govt(void)

{
  size_t len;
  iptr parent_wnd2;
  char input_buf[260];
  Dialog dialog2;
  int choice;
  int input_result;
  i32 eh_handler;
  i8 *eh_prev;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  dialog_ctor(&dialog2,0x4000);
  eh_state = 0;
  if (editor_text_dlg_wnd_block.active_editor_wnd == 0) {
    parent_wnd2 = 0;
  }
  else {
    parent_wnd2 = editor_text_dlg_wnd_block.active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(parent_wnd2);
  dialog_load_text(&dialog2,(const char *)&str_debug_11,(const char *)&str_renamegovt,1);
  dialog_set_width((DialogWindowView *)&dialog2,0xdc);
  dialog_set_listbox((DialogTextView *)&dialog2,7,0xdc,0);
  for (choice = 0; choice < 7; choice++) {
    dialog_add_option
              ((DialogOptionList *)&dialog2,(const char *)(((i8 *)&editor_text_dlg_wnd_block.editor_govt_names) + choice * 0xf),choice,0);
  }
  dialog2.option_width = 0xdc;
  choice = dlg_show_modal(&dialog2,0);
  if (-1 < choice) {
    do {
      input_result = dlg_text_input((iptr)&str_debug_11,(const char *)&str_govtname,0xe,(iptr)(((i8 *)&editor_text_dlg_wnd_block.editor_govt_names) + choice * 0xf),
                                    (iptr)input_buf);
      if (input_result == -1) break;
      len = _strlen(input_buf);
    } while (len == 0);
    if (-1 < input_result) {
      _strncpy(((i8 *)&editor_text_dlg_wnd_block.editor_govt_names) + choice * 0xf,input_buf,0xf);
    }
  }
  dlg_set_parent_window(0);
  eh_state = 0xffffffff;
  /* inlined unwind funclet 004a4667 */ { dialog_dtor(&dialog2); }
  return;
}

/* 004a468b auto */
void __cdecl tribe_editor_rename_title(void)

{
  int title_slot;
  size_t len;
  char *dest_title;
  i8 *current_title;
  i32 gender_label;
  i8 *title_name;
  iptr parent_wnd2;
  char input_buf[260];
  char option_text[64];
  Dialog dialog2;
  uint choice;
  int input_result;
  i32 eh_handler;
  i8 *eh_prev;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  dialog_ctor(&dialog2,0x4000);
  eh_state = 0;
  if (editor_text_dlg_wnd_block.active_editor_wnd == 0) {
    parent_wnd2 = 0;
  }
  else {
    parent_wnd2 = editor_text_dlg_wnd_block.active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(parent_wnd2);
  dialog_load_text(&dialog2,(const char *)&str_debug_11,(const char *)&str_renametitle,1);
  dialog_set_width((DialogWindowView *)&dialog2,400);
  dialog_set_listbox((DialogTextView *)&dialog2,0xe,400,0);
  for (choice = 0; (int)choice < 0xe; choice++) {
    if ((choice & 1) == 0) {
      title_slot = ((int)choice >> 1) * 3 + 0x15;
    }
    else {
      title_slot = ((int)choice >> 1) * 3 + 0x2a;
    }
    title_name = ((i8 *)&editor_text_dlg_wnd_block.editor_govt_names) + title_slot * 5;
    if ((choice & 1) == 0) {
      gender_label = (i32)(label_string(*(i32 *)(label_string_ids + 0x8fc)));
    }
    else {
      gender_label = (i32)(label_string(*(i32 *)(label_string_ids + 0x900)));
    }
    _sprintf(option_text,str_s_s_s_3,((i8 *)&editor_text_dlg_wnd_block.editor_govt_names) + ((int)choice >> 1) * 0xf,gender_label,
             title_name);
    dialog_add_option((DialogOptionList *)&dialog2,(const char *)option_text,choice,0);
  }
  dialog2.option_width = 400;
  choice = dlg_show_modal(&dialog2,0);
  if (-1 < (int)choice) {
    do {
      if ((choice & 1) == 0) {
        title_slot = ((int)choice >> 1) * 3 + 0x15;
      }
      else {
        title_slot = ((int)choice >> 1) * 3 + 0x2a;
      }
      current_title = ((i8 *)&editor_text_dlg_wnd_block.editor_govt_names) + title_slot * 5;
      input_result = dlg_text_input((iptr)&str_debug_11,(const char *)&str_titlename,0xe,(iptr)current_title,(iptr)input_buf);
      if (input_result == -1) break;
      len = _strlen(input_buf);
    } while (len == 0);
    if (-1 < input_result) {
      if ((choice & 1) == 0) {
        title_slot = ((int)choice >> 1) * 3 + 0x15;
      }
      else {
        title_slot = ((int)choice >> 1) * 3 + 0x2a;
      }
      dest_title = ((i8 *)&editor_text_dlg_wnd_block.editor_govt_names) + title_slot * 5;
      _strncpy(dest_title,input_buf,0xf);
    }
  }
  dlg_set_parent_window(0);
  eh_state = 0xffffffff;
  /* inlined unwind funclet 004a4948 */ { dialog_dtor(&dialog2); }
  return;
}

/* 004a496c auto */
void __cdecl tribe_editor_on_help(void)

{
  i32 parent_wnd2;
  
  if (editor_text_dlg_wnd_block.active_editor_wnd == 0) {
    parent_wnd2 = 0;
  }
  else {
    parent_wnd2 = editor_text_dlg_wnd_block.active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(parent_wnd2);
  popup_text((const char *)&str_help_3,(const char *)&str_tribes);
  dlg_set_parent_window(0);
  return;
}

/* 004a49cb auto */
void __cdecl tribe_editor_on_cancel(void)

{
  editor_text_dlg_wnd_block.editor_running = 0;
  wnd_end_modal_loop((ModalMenuWindow *)(editor_text_dlg_wnd_block.active_editor_wnd + 0x48));
  return;
}

/* 004a49f3 auto */
void __cdecl tribe_editor_on_combo(int ctrl_id)

{
  i32 selection;
  
  if (ctrl_id == 0xc9) {
    tribe_editor_store_controls();
    selection = combo_get_cur_sel((ComboBoxGetSelView *)(editor_text_dlg_wnd_block.active_editor_wnd + 0x2fc));
    *(i32 *)(editor_text_dlg_wnd_block.active_editor_wnd + 0x2ec) = selection;
    tribe_editor_load_controls();
    tribe_editor_redraw();
  }
  else if (ctrl_id == 0xca) {
    tribe_editor_store_controls();
    tribe_editor_redraw();
  }
  return;
}

/* 004a4a58 auto */
void __thiscall tribe_editor_create_combo(ViewWindow *self,int slot)

{
  int ctrl_x;
  int ctrl_y;
  iptr label;
  u8 *parent_wnd2;
  int i;
  i8 rect[16];
  
  ctrl_x = *(int *)(((i8 *)&tribe_editor_combo_x_table_block.tribe_editor_combo_x_table) + slot * 8) + self->client_x;
  ctrl_y = *(int *)(((i8 *)&tribe_editor_combo_x_table_block.tribe_editor_combo_y_table) + slot * 8) + self->client_y;
  if (slot == 0) {
    rect_set_xywh((iptr)rect,ctrl_x - 0x32,ctrl_y,200,self->sci_rate_sel << 3);
  }
  else if (slot < 2) {
    rect_set_xywh((iptr)rect,ctrl_x - 0xf,ctrl_y,0x82,self->sci_rate_sel << 3);
  }
  else {
    rect_set_xywh((iptr)rect,ctrl_x,ctrl_y,100,self->sci_rate_sel << 3);
  }
  ctrl_x = editor_text_dlg_wnd_block.editor_next_ctrl_id;
  editor_text_dlg_wnd_block.editor_next_ctrl_id++;
  if (self == (ViewWindow *)0x0) {
    parent_wnd2 = (u8 *)0x0;
  }
  else {
    parent_wnd2 = self->window_2;
  }
  combo_create
            ((Control *)(self->editor_combo_boxes + slot * 0x38 + 0x28),(iptr)parent_wnd2,ctrl_x,
             (iptr)rect);
  combo_set_font((ComboBoxFontView *)(self->editor_combo_boxes + slot * 0x38 + 0x28),(iptr)&editor_font_block.editor_font);
  combo_set_callback((ComboBoxCallbackSetView *)(self->editor_combo_boxes + slot * 0x38 + 0x28),(iptr)tribe_editor_on_combo);
  switch(slot) {
  case 0:
    for (i = 0; i < 0x15; i++) {
      combo_add_string
                ((ComboBoxAddView *)(self->editor_combo_boxes + slot * 0x38 + 0x28),
                 (const char *)(((i8 *)&editor_text_dlg_wnd_block.editor_item_names) + (i * 5 + 0xd2) * 8));
    }
    break;
  case 1:
    label = (iptr)(label_string(*(i32 *)(label_string_ids + 0x834)));
    combo_add_string((ComboBoxAddView *)(self->editor_combo_boxes + slot * 0x38 + 0x28),(const char *)label);
    label = (iptr)(label_string(*(i32 *)(label_string_ids + 0x838)));
    combo_add_string((ComboBoxAddView *)(self->editor_combo_boxes + slot * 0x38 + 0x28),(const char *)label);
    label = (iptr)(label_string(*(i32 *)(label_string_ids + 0x83c)));
    combo_add_string((ComboBoxAddView *)(self->editor_combo_boxes + slot * 0x38 + 0x28),(const char *)label);
    label = (iptr)(label_string(*(i32 *)(label_string_ids + 0x840)));
    combo_add_string((ComboBoxAddView *)(self->editor_combo_boxes + slot * 0x38 + 0x28),(const char *)label);
    break;
  case 2:
    label = (iptr)(label_string(*(i32 *)(label_string_ids + 0x904)));
    combo_add_string((ComboBoxAddView *)(self->editor_combo_boxes + slot * 0x38 + 0x28),(const char *)label);
    label = (iptr)(label_string(*(i32 *)(label_string_ids + 0x908)));
    combo_add_string((ComboBoxAddView *)(self->editor_combo_boxes + slot * 0x38 + 0x28),(const char *)label);
    label = (iptr)(label_string(*(i32 *)(label_string_ids + 0x90c)));
    combo_add_string((ComboBoxAddView *)(self->editor_combo_boxes + slot * 0x38 + 0x28),(const char *)label);
    break;
  case 3:
    label = (iptr)(label_string(*(i32 *)(label_string_ids + 0x910)));
    combo_add_string((ComboBoxAddView *)(self->editor_combo_boxes + slot * 0x38 + 0x28),(const char *)label);
    label = (iptr)(label_string(*(i32 *)(label_string_ids + 0x914)));
    combo_add_string((ComboBoxAddView *)(self->editor_combo_boxes + slot * 0x38 + 0x28),(const char *)label);
    label = (iptr)(label_string(*(i32 *)(label_string_ids + 0x918)));
    combo_add_string((ComboBoxAddView *)(self->editor_combo_boxes + slot * 0x38 + 0x28),(const char *)label);
    break;
  case 4:
    label = (iptr)(label_string(*(i32 *)(label_string_ids + 0x91c)));
    combo_add_string((ComboBoxAddView *)(self->editor_combo_boxes + slot * 0x38 + 0x28),(const char *)label);
    label = (iptr)(label_string(*(i32 *)(label_string_ids + 0x914)));
    combo_add_string((ComboBoxAddView *)(self->editor_combo_boxes + slot * 0x38 + 0x28),(const char *)label);
    label = (iptr)(label_string(*(i32 *)(label_string_ids + 0x920)));
    combo_add_string((ComboBoxAddView *)(self->editor_combo_boxes + slot * 0x38 + 0x28),(const char *)label);
  }
  return;
}

/* 004a4eb2 auto */
void __thiscall tribe_editor_create_edit(ViewWindow *self,int slot)

{
  int ctrl_id;
  u8 *parent_wnd2;
  i8 rect[16];
  
  rect_set_xywh((iptr)rect,(((i32 *)&tribe_editor_combo_x_table_block.tribe_editor_edit_x_table))[slot * 2] + self->client_x,
                     (((i32 *)&tribe_editor_combo_x_table_block.tribe_editor_edit_y_table))[slot * 2] + self->client_y,100,self->sci_rate_sel + 6);
  ctrl_id = editor_text_dlg_wnd_block.editor_next_ctrl_id;
  editor_text_dlg_wnd_block.editor_next_ctrl_id++;
  if (self == (ViewWindow *)0x0) {
    parent_wnd2 = (u8 *)0x0;
  }
  else {
    parent_wnd2 = self->window_2;
  }
  edit_create
            ((EditControl *)(((PediaRedrawView *)self)->numeric_edit_controls_area + slot * 0x48 - 0x2c),(iptr)parent_wnd2,ctrl_id,
             (iptr)rect,(const char *)&str_empty_114);
  edit_set_max_len((EditMaxLenView *)(((PediaRedrawView *)self)->numeric_edit_controls_area + slot * 0x48 - 0x2c),0x17);
  return;
}

/* 004a4f89 auto */
void __thiscall tribe_editor_paint(ViewWindow *self)

{
  byte key_color;
  i8 draw_ctx[16];
  Sprite *sprite;
  int label_y;
  int label_x;
  int box_y;
  int box_x;
  
  frame_wnd_draw_caption((FrameWindow *)self);
  if (((*(int *)&editor_bg_surface) == 0) || (editor_text_dlg_wnd_block.editor_running == 0)) {
    gfx_fill_rect((iptr)self,(iptr)&self->client_rect,0x1d);
  }
  else {
    gfx_copy_rect_xywh((*(int *)&editor_bg_surface),(iptr)self,0,0,self->client_x,self->client_y,self->rates_civ,
                       self->max_rate_value);
  }
  box_x = self->client_x + 0x20;
  box_y = self->client_y + 0x20;
  sprite = (Sprite *)
             (*(int *)(((i8 *)&editor_text_dlg_wnd_block.editor_items) + *(int *)(editor_text_dlg_wnd_block.active_editor_wnd + 0x2ec) * 0x58) * 0x1e0 + (iptr)(((u8 *)&gfx_sheet_surface_block.city_walled_sprites + 300)));
  key_color = sprite_get_key_color(sprite);
  gfx_fill_rect_xywh((iptr)self,box_x,box_y,0x40,0x40,(uint)key_color);
  sprite_draw_keyed(sprite,(iptr)draw_ctx,(iptr)self,0,box_x,box_y + 8);
  gfx_draw_tiled_frame((iptr)self,box_x,box_y,0x40,0x40,6);
  box_x = self->client_width + self->client_x - 0x60;
  box_y = self->client_y + 0x20;
  gfx_fill_rect_xywh((iptr)self,box_x,box_y,0x40,0x40,
                     *(i32 *)(((i8 *)&civ_primary_colors_block.civ_mid_colors) + leaders[self->init_tax_rate].color * 0x10));
  gfx_fill_rect_xywh((iptr)self,box_x + 0x10,box_y + 0x10,0x20,0x20,
                     *(i32 *)(((i8 *)&civ_primary_colors_block.civ_primary_colors) + leaders[self->init_tax_rate].color * 0x10));
  gfx_draw_tiled_frame((iptr)self,box_x,box_y,0x40,0x40,6);
  text_set_surface((iptr)self);
  text_set_font((iptr)&editor_font_block.editor_font);
  text_set_colors(10,10,0,0);
  box_x = tribe_editor_combo_x_table_block.tribe_editor_edit_x_table[0] + self->client_x;
  box_y = tribe_editor_combo_x_table_block.tribe_editor_edit_y_table[0] + self->client_y;
  gfx_fill_rect_xywh((iptr)self,box_x,box_y,100,self->sci_rate_sel + 6,0x29);
  gfx_draw_frame_rect((iptr)self,box_x,box_y,100,self->sci_rate_sel + 6,10);
  text_clear();
  text_append_str((const char *)(((i8 *)&editor_text_dlg_wnd_block.editor_item_names) + (*(int *)(editor_text_dlg_wnd_block.active_editor_wnd + 0x2ec) * 5 + 0x13b) * 8));
  text_draw_shadowed((iptr)self,(const char *)&map_views_block.text_buffer,box_x + 3,box_y + 2);
  text_set_colors(0x29,0x12,1,1);
  box_x = self->client_x + 0x59;
  box_y = self->client_y + 0x109;
  gfx_draw_tiled_frame((iptr)self,box_x,box_y,0x17c,0x45,6);
  label_x = self->client_x + (int)self->client_width / 2;
  label_y = self->client_y + 0x10d;
  text_clear();
  text_append_label(0x25d);
  text_draw_centered((iptr)self,(const char *)&map_views_block.text_buffer,label_x,label_y,0);
  label_x = tribe_editor_combo_x_table_block.tribe_editor_city_style_x + self->client_x + 0x32;
  label_y = ((tribe_editor_combo_x_table_block.tribe_editor_city_style_y + self->client_y) - self->sci_rate_sel) - 2;
  text_clear();
  text_append_label(0x219);
  text_draw_centered((iptr)self,(const char *)&map_views_block.text_buffer,label_x,label_y,0);
  label_x = tribe_editor_combo_x_table_block.tribe_editor_edit_x_table[0] + self->client_x + 0x32;
  label_y = ((tribe_editor_combo_x_table_block.tribe_editor_edit_y_table[0] + self->client_y) - self->sci_rate_sel) - 2;
  text_clear();
  text_append_label(0x249);
  text_draw_centered((iptr)self,(const char *)&map_views_block.text_buffer,label_x,label_y,0);
  label_x = tribe_editor_combo_x_table_block.tribe_editor_attack_x + self->client_x + 0x32;
  label_y = ((tribe_editor_combo_x_table_block.tribe_editor_attack_y + self->client_y) - self->sci_rate_sel) - 2;
  text_clear();
  text_append_label(0x1e5);
  text_draw_centered((iptr)self,(const char *)&map_views_block.text_buffer,label_x,label_y,0);
  label_x = tribe_editor_combo_x_table_block.tribe_editor_expand_x + self->client_x + 0x32;
  label_y = ((tribe_editor_combo_x_table_block.tribe_editor_expand_y + self->client_y) - self->sci_rate_sel) - 2;
  text_clear();
  text_append_label(0x24a);
  text_draw_centered((iptr)self,(const char *)&map_views_block.text_buffer,label_x,label_y,0);
  label_x = tribe_editor_combo_x_table_block.tribe_editor_civilize_x + self->client_x + 0x32;
  label_y = ((tribe_editor_combo_x_table_block.tribe_editor_civilize_y + self->client_y) - self->sci_rate_sel) - 2;
  text_clear();
  text_append_label(0x24b);
  text_draw_centered((iptr)self,(const char *)&map_views_block.text_buffer,label_x,label_y,0);
  wnd_blit_surface((DibSurface *)self);
  return;
}

/* 004a54d9 auto */
void __thiscall tribe_editor_main(ViewWindow *self)

{
  DibSurface *this_00;
  uptr font_height;
  i32 title;
  int pos;
  iptr label;
  int button_y;
  i32 style;
  i32 pos_x;
  i32 pos_y;
  u32 width;
  u32 height;
  i32 arg7;
  i32 arg8;
  i32 arg9;
  u8 *parent_wnd6;
  u8 *parent_wnd5;
  u8 *parent_wnd4;
  u8 *parent_wnd3;
  u8 *parent_wnd2;
  u8 *parent_wnd1;
  DibSurface *bg_surface2;
  int i;
  i8 rect[16];
  GamePalette palette;
  i32 eh_handler;
  i8 *eh_prev;
  int eh_state;
  
  eh_state = 0xffffffff;
  palette_init(&palette);
  eh_state = 0;
  editor_text_dlg_wnd_block.editor_running = 1;
  editor_text_dlg_wnd_block.active_editor_wnd = (iptr)self;
  this_00 = (DibSurface *)(operator_new(0x48));
  (*((char *)&eh_state + 0)) = 1;
  if (this_00 == (DibSurface *)0x0) {
    bg_surface2 = (DibSurface *)0x0;
  }
  else {
    bg_surface2 = surface_ctor(this_00);
  }
  eh_state = eh_state & 0xffffff00;
  editor_bg_surface = bg_surface2;
  font_set((GameFont *)((i8 *)&editor_font_block.editor_font),0,editor_font_size);
  ui_set_default_font((iptr)&editor_font_block.editor_font);
  self->rates_civ = 0x230;
  self->max_rate_value = 0x17c;
  self->init_tax_rate = 0;
  editor_text_dlg_wnd_block.editor_next_ctrl_id = 0xc9;
  surface_load_gif_file(editor_bg_surface,(const char *)&str_editorsa_gif,10,0xc0,(iptr)&palette);
  font_height = font_cached_height((GameFont *)((i8 *)&editor_font_block.editor_font));
  self->sci_rate_sel = font_height;
  arg9 = 0;
  arg8 = 0;
  arg7 = 0;
  height = self->max_rate_value;
  width = self->rates_civ;
  pos_y = 0;
  pos_x = 0;
  style = 0xd;
  title = (i32)(label_string(*(i32 *)(label_string_ids + 0x930)));
  frame_wnd_create
            ((FrameWindow *)self,(const char *)title,style,pos_x,pos_y,width,height,arg7,arg8,arg9);
  tribe_editor_load_tables();
  for (i = 0; i < 5; i++) {
    if (*(int *)(((i8 *)&tribe_editor_ctrl_kinds_block.tribe_editor_ctrl_kinds) + i * 8) == 9) {
      tribe_editor_create_edit(self,*(i32 *)(((i8 *)&tribe_editor_ctrl_kinds_block.tribe_editor_ctrl_slots) + i * 8));
    }
    else if (*(int *)(((i8 *)&tribe_editor_ctrl_kinds_block.tribe_editor_ctrl_kinds) + i * 8) == 0xc) {
      tribe_editor_create_combo(self,*(i32 *)(((i8 *)&tribe_editor_ctrl_kinds_block.tribe_editor_ctrl_slots) + i * 8));
    }
  }
  pos = sprite_width
                    ((Sprite *)(((i8 *)&terrain_base_sprites_block.terrain_base_sprites) + self->init_tax_rate * 0x3c));
  self->tax_rate_sel = pos + 0x2d;
  pos = font_line_spacing((GameFont *)(*(i8 * *)(dialog_default_text_font_rest + 8)));
  self->lux_rate_sel = pos + 8;
  pos = self->client_y + (int)(self->lux_rate_sel * 3) / 2 + 0x101;
  height = self->client_x;
  rect_set_xywh((iptr)rect,height + 0x69,pos,self->tax_rate_sel,self->lux_rate_sel);
  if (self == (ViewWindow *)0x0) {
    parent_wnd1 = (u8 *)0x0;
  }
  else {
    parent_wnd1 = self->window_2;
  }
  label = (iptr)(label_string(*(i32 *)(label_string_ids + 0x940)));
  button_create
            ((Control *)(((DocumentWindow *)self)->add_trigger_button),(iptr)parent_wnd1,0x65,(iptr)rect,(const char *)label);
  button_set_callback((Control *)(((DocumentWindow *)self)->add_trigger_button),(iptr)tribe_editor_rename_commodity);
  rect_set_xywh((iptr)rect,height + 0xe1,pos,self->tax_rate_sel,self->lux_rate_sel);
  if (self == (ViewWindow *)0x0) {
    parent_wnd2 = (u8 *)0x0;
  }
  else {
    parent_wnd2 = self->window_2;
  }
  label = (iptr)(label_string(*(i32 *)(label_string_ids + 0x944)));
  button_create
            ((Control *)(((DocumentWindow *)self)->edit_trigger_button),(iptr)parent_wnd2,0x65,(iptr)rect,(const char *)label);
  button_set_callback((Control *)(((DocumentWindow *)self)->edit_trigger_button),(iptr)tribe_editor_rename_govt);
  rect_set_xywh((iptr)rect,height + 0x159,pos,self->tax_rate_sel,self->lux_rate_sel);
  if (self == (ViewWindow *)0x0) {
    parent_wnd3 = (u8 *)0x0;
  }
  else {
    parent_wnd3 = self->window_2;
  }
  label = (iptr)(label_string(*(i32 *)(label_string_ids + 0x948)));
  button_create
            ((Control *)&((DocumentWindow *)self)->delete_trigger_button,(iptr)parent_wnd3,0x65,(iptr)rect,(const char *)label);
  button_set_callback((Control *)&((DocumentWindow *)self)->delete_trigger_button,(iptr)tribe_editor_rename_title);
  pos = font_line_spacing((GameFont *)(*(i8 * *)(dialog_default_text_font_rest + 8)));
  self->lux_rate_sel = pos + 8;
  self->tax_rate_sel = (int)(self->client_width - 8) / 3;
  button_y = (self->client_y + self->client_height) - (self->lux_rate_sel + 2);
  pos = self->client_x + 2;
  rect_set_xywh((iptr)rect,pos,button_y,self->tax_rate_sel,self->lux_rate_sel);
  if (self == (ViewWindow *)0x0) {
    parent_wnd4 = (u8 *)0x0;
  }
  else {
    parent_wnd4 = self->window_2;
  }
  label = (iptr)(label_string(*(i32 *)(label_string_ids + 0x3f8)));
  button_create
            ((Control *)&((PediaAdvanceListView *)self)->editor_ok_button,(iptr)parent_wnd4,0x65,(iptr)rect,(const char *)label);
  button_set_callback((Control *)&((PediaAdvanceListView *)self)->editor_ok_button,(iptr)tribe_editor_on_ok);
  pos = pos + self->tax_rate_sel + 2;
  rect_set_xywh((iptr)rect,pos,button_y,self->tax_rate_sel,self->lux_rate_sel);
  if (self == (ViewWindow *)0x0) {
    parent_wnd5 = (u8 *)0x0;
  }
  else {
    parent_wnd5 = self->window_2;
  }
  label = (iptr)(label_string(*(i32 *)(label_string_ids + 0x8ec)));
  button_create
            ((Control *)&((PediaAdvanceListView *)self)->editor_help_button,(iptr)parent_wnd5,0x66,(iptr)rect,(const char *)label);
  button_set_callback((Control *)&((PediaAdvanceListView *)self)->editor_help_button,(iptr)tribe_editor_on_help);
  rect_set_xywh((iptr)rect,pos + self->tax_rate_sel + 2,button_y,self->tax_rate_sel,
                     self->lux_rate_sel);
  if (self == (ViewWindow *)0x0) {
    parent_wnd6 = (u8 *)0x0;
  }
  else {
    parent_wnd6 = self->window_2;
  }
  label = (iptr)(label_string(*(i32 *)(label_string_ids + 0x3fc)));
  button_create
            ((Control *)&((PediaAdvanceListView *)self)->editor_cancel_button,(iptr)parent_wnd6,0x66,(iptr)rect,(const char *)label);
  button_set_callback((Control *)&((PediaAdvanceListView *)self)->editor_cancel_button,(iptr)tribe_editor_on_cancel);
  ctrl_set_cancel_button((Control *)&((PediaAdvanceListView *)self)->editor_cancel_button);
  wnd_set_keyboard_nav((Wnd *)self->window_2,0);
  combo_set_cur_sel((ComboBoxSetSelView *)&self->dialog_h,self->init_tax_rate);
  tribe_editor_load_controls();
  self->dialog_w = 5;
  wnd_set_move_handler((WndEventHandlers *)self->event_handlers,(iptr)editor_wnd_on_move_close_dropdowns);
  wnd_set_redraw_callback((SurfaceWindow *)self,(iptr)tribe_editor_redraw);
  wnd_repaint((SurfaceWindow *)self);
  window_show((WindowObjectView *)self);
  wnd_run_modal_loop((ModalMenuWindow *)self->window_2);
  while (editor_text_dlg_wnd_block.editor_running != 0) {
    win_pump_one_message();
  }
  if (editor_bg_surface != (DibSurface *)0x0) {
    surface_delete(editor_bg_surface,1);
  }
  editor_bg_surface = (DibSurface *)0x0;
  self->dialog_w = 0;
  eh_state = 0xffffffff;
  /* inlined unwind funclet 004a5d6e */ { palette_destroy(&palette); }
  return;
}

/* 004a5d92 auto */
void __cdecl tribe_editor_run(void)

{
  EditorWindow editor_wnd;
  i32 seh_prev;
  i8 *seh_handler;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  editor_wnd_ctor((DocumentWindow *)(&editor_wnd));
  eh_state = 0;
  tribe_editor_main((ViewWindow *)&editor_wnd);
  wnd_repaint((SurfaceWindow *)((i8 *)&map_views_block.map_views));
  eh_state = 0xffffffff;
  /* inlined unwind funclet 004a5deb */ { editor_wnd_dtor(&editor_wnd); }
  return;
}

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
  frame_wnd_ctor((SurfaceWindow *)((i8 *)&editor_text_dlg_wnd_block.editor_text_dlg_wnd));
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
  frame_wnd_dtor((DibSurface *)((i8 *)&editor_text_dlg_wnd_block.editor_text_dlg_wnd));
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
  edit_ctor((InputControl *)((i8 *)&editor_text_edit_block.editor_text_edit));
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
  edit_dtor((Control *)((i8 *)&editor_text_edit_block.editor_text_edit));
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
  font_init((GameFont *)((i8 *)&editor_font_block.editor_font),0,0x10);
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
  font_destroy((GameFont *)((i8 *)&editor_font_block.editor_font));
  return;
}

/* 004cd8a6 auto */
i32 __cdecl tribe_editor_update_city_file(void)

{
  int rc;
  char *read_ptr;
  size_t _MaxCount;
  int string_id;
  i32 result;
  iptr civ;
  FILE *out_file;
  FILE *in_file;
  char saved_cwd[260];
  iptr leader;
  char line[256];
  i8 city_file_name[16];
  char *tribe_str;
  
  result = 0;
  out_file = (FILE *)0x0;
  in_file = (FILE *)0x0;
  crt_strcpy(city_file_name,str_city_3);
  crt_strcat(city_file_name,((i8 *)&lang_file_ext));
  __getcwd(saved_cwd,0x104);
  __chdir(((i8 *)&net_map_lock_slots_block.scenario_dir_path));
  rc = _strcmp(((i8 *)&net_map_lock_slots_block.scenario_dir_path),((i8 *)&civ_saved_cursor_x_block.game_home_dir));
  if (rc != 0) {
    rc = file_exists((const char *)city_file_name);
    if (rc == 0) {
success:
      result = 1;
    }
    else {
      rc = file_exists((const char *)&str_city_tmp);
      if (((rc == 0) || (rc = crt_remove(str_city_tmp_2), rc == 0)) &&
         (rc = crt_rename(city_file_name,str_city_tmp_3), rc == 0)) {
        in_file = file_open_path((const char *)&str_city_tmp_4,(iptr)&str_rt_5);
        out_file = file_open_path((const char *)city_file_name,(iptr)&str_wt_4);
        if ((in_file != (FILE *)0x0) && (out_file != (FILE *)0x0)) {
          do {
            while( true ) {
              read_ptr = _fgets(line,0x100,in_file);
              if (read_ptr == (char *)0x0) goto success;
              if ((line[0] != '@') || (rc = __strnicmp((line + 1),((i8 *)&city_file_stop_str),4), rc == 0))
              break;
              for (leader = 0; leader < 0x15; leader++) {
                civ = 1;
                while ((civ < 8 && (civs[civ].tribe != leader))) {
                  civ++;
                }
                if (civ < 8) {
                  tribe_str = civ_names[civ].tribe_name;
                }
                else {
                  if (leaders[leader].plural < 1) {
                    string_id = ~(int)leaders[leader].plural + 1;
                  }
                  else {
                    string_id = (int)leaders[leader].plural;
                  }
                  tribe_str = label_string(string_id);
                }
                _MaxCount = _strlen(tribe_str);
                rc = __strnicmp((line + 1),tribe_str,_MaxCount);
                if (rc == 0) {
                  _sprintf(line,str_c_s,0x40,
                           ((i8 *)&editor_text_dlg_wnd_block.editor_item_names) + (leader * 5 + 0xd2) * 8);
                  __strupr(line);
                  rc = _fputs(line,out_file);
                  if (rc == -1) goto cleanup;
                  break;
                }
              }
              if ((leader == 0x15) && (rc = _fputs(line,out_file), rc == -1))
              goto cleanup;
            }
            rc = _fputs(line,out_file);
          } while (rc != -1);
        }
      }
    }
  }
cleanup:
  if (in_file != (FILE *)0x0) {
    _fclose(in_file);
  }
  if (out_file != (FILE *)0x0) {
    _fclose(out_file);
  }
  rc = file_exists((const char *)&str_city_tmp_5);
  if (rc != 0) {
    crt_remove(str_city_tmp_6);
  }
  __chdir(saved_cwd);
  return result;
}

/* 004cdcf6 auto */
i32 __cdecl editor_numeric_edit_filter(i32 ctrl,int key)

{
  i32 accept;
  
  if ((((key < 0x30) || (0x39 < key)) && (key != 0x2d)) && (key != 0xd6)) {
    accept = 0;
  }
  else {
    accept = 1;
  }
  return accept;
}

/* 004cdd3d auto */
i32 __cdecl editor_options_dialog(const char *file_name,const char *section,uint disabled_mask,i32 flags)

{
  int rc;
  iptr parent_wnd2;
  i32 choice;
  Dialog dlg;
  int i;
  i32 seh_prev;
  i8 *seh_handler;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  dialog_ctor(&dlg,0x4000);
  eh_state = 0;
  if (editor_text_dlg_wnd_block.active_editor_wnd == 0) {
    parent_wnd2 = 0;
  }
  else {
    parent_wnd2 = editor_text_dlg_wnd_block.active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(parent_wnd2);
  rc = dialog_load_text_section(&dlg,(const char *)&str_game_7,file_name,(int)(section),0,0,0,0,flags);
  if (rc == 0) {
    if (((byte)dlg.style_flags & 4) != 0) {
      for (i = 0; i < (int)dlg.option_count; i++) {
        dialog_set_option_checked
                  ((DialogOptionList *)&dlg,i,1 << ((byte)i & 0x1f) & dlg_check_bits
                  );
      }
    }
    for (i = 0; i < (int)dlg.option_count; i++) {
      dialog_set_option_disabled
                ((DialogOptionList *)&dlg,i,
                 (uint)((1 << ((byte)i & 0x1f) & disabled_mask) != 0));
    }
    choice = dlg_show_modal(&dlg,0);
    (*(u32 *)&dlg_help_pressed) = dlg.result_extra;
    if (((byte)dlg.style_flags & 4) != 0) {
      dlg_check_bits = 0;
      for (i = 0; i < (int)dlg.option_count; i++) {
        rc = dialog_option_is_checked((DialogOptionList *)&dlg,i);
        if (rc != 0) {
          dlg_check_bits = dlg_check_bits | 1 << ((byte)i & 0x1f);
        }
      }
    }
  }
  dlg_set_parent_window(0);
  eh_state = 0xffffffff;
  /* inlined unwind funclet 004cdf26 */ { dialog_dtor(&dlg); }
  return choice;
}

/* 004cdf4b auto */
int __cdecl editor_clamp_value(int value,int min_value,int max_value)

{
  if (value < min_value) {
    editor_value_clamped = 1;
  }
  else {
    min_value = value;
    if (max_value < value) {
      editor_value_clamped = 1;
      min_value = max_value;
    }
  }
  return min_value;
}

/* 004cdfa4 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl
editor_text_dlg_create(const char *title,uint style,int x,int y,int width,int height,int resize_border,
            int caption_height,int border_width)

{
  iptr parent_wnd2;
  uint wnd_style;
  
  if (title == 0) {
    crt_strcpy(((i8 *)&editor_text_dlg_wnd_block.editor_text_dlg_title),((i8 *)&editor_text_dlg_empty_title));
  }
  else {
    crt_strcpy(((i8 *)&editor_text_dlg_wnd_block.editor_text_dlg_title),(const char *)((const void *)title));
  }
  editor_text_dlg_wnd_block.editor_text_dlg_text_font_i32 = ((i32)((i8 *)&ui_text_font));
  editor_text_dlg_wnd_block.editor_text_dlg_title_font_i32 = ((i32)((i8 *)&caption_font_block.caption_font));
  editor_text_dlg_wnd_block.editor_text_dlg_title_small_font_i32 = ((i32)((i8 *)&caption_small_font_block.caption_small_font));
  editor_text_dlg_wnd_block.editor_text_dlg_style_i32 = style;
  editor_text_dlg_wnd_block.editor_text_dlg_caption_height = caption_height;
  editor_text_dlg_wnd_block.editor_text_dlg_border_width = border_width;
  editor_text_dlg_wnd_block.editor_text_dlg_resize_border = resize_border;
  editor_text_dlg_wnd_block.editor_text_dlg_caption_buttons_i32 = 0;
  editor_text_dlg_wnd_block.editor_text_dlg_caption_handler_i32 = 0;
  if ((style & 4) != 0) {
    editor_text_dlg_wnd_block.editor_text_dlg_caption_height = frame_caption_height;
    editor_text_dlg_wnd_block.editor_text_dlg_border_width = frame_border_width;
  }
  if ((style & 8) == 0) {
    wnd_style = 0x202;
  }
  else {
    wnd_style = 0x802;
  }
  if (editor_text_dlg_wnd_block.editor_text_dlg_caption_height != 0) {
    wnd_style = wnd_style | 0x400;
  }
  if (resize_border != 0) {
    wnd_style = wnd_style | 0x1000;
  }
  if ((style & 2) == 0) {
    width += editor_text_dlg_wnd_block.editor_text_dlg_border_width * 2;
    height = height + editor_text_dlg_wnd_block.editor_text_dlg_caption_height + editor_text_dlg_wnd_block.editor_text_dlg_border_width;
  }
  if ((style & 1) != 0) {
    x = (caption_font_block.screen_width >> 1) - (width >> 1);
    y = (caption_font_block.screen_height >> 1) - (height >> 1);
  }
  if (editor_text_dlg_wnd_block.active_editor_wnd == 0) {
    parent_wnd2 = 0;
  }
  else {
    parent_wnd2 = editor_text_dlg_wnd_block.active_editor_wnd + 0x48;
  }
  wnd_create_with_surface
            ((DibSurface *)((i8 *)&editor_text_dlg_wnd_block.editor_text_dlg_wnd),0,wnd_style,x,y,width,height,(iptr)&game_palette_block.game_palette,
             parent_wnd2);
  if (editor_text_dlg_wnd_block.editor_text_dlg_caption_height != 0) {
    wnd_set_caption_height((WndBase *)((i8 *)&editor_text_dlg_wnd_block.editor_text_dlg_inner),editor_text_dlg_wnd_block.editor_text_dlg_caption_height);
  }
  if (editor_text_dlg_wnd_block.editor_text_dlg_resize_border != 0) {
    wnd_set_resize_border((WndBase *)((i8 *)&editor_text_dlg_wnd_block.editor_text_dlg_inner),editor_text_dlg_wnd_block.editor_text_dlg_resize_border);
  }
  frame_wnd_layout((FrameWindow *)((i8 *)&editor_text_dlg_wnd_block.editor_text_dlg_wnd));
  return;
}

/* 004ce196 auto */
void __cdecl editor_text_dlg_on_ok(void)

{
  int has_line;
  size_t len;
  i32 line_copy;
  int line_idx;
  char line_buf[256];
  
  for (line_idx = 0; line_idx < 0x14; line_idx++) {
    *(i32 *)(editor_text_dlg_wnd_block.editor_text_lines_out + line_idx * 4) = 0;
  }
  events_compact();
  line_idx = 0;
  do {
    if (0x13 < line_idx) {
finish_ok:
      editor_font_block.editor_text_result = 1;
      editor_font_block.editor_text_active = 0;
      wnd_end_modal_loop((ModalMenuWindow *)((i8 *)&editor_text_dlg_wnd_block.editor_text_dlg_inner));
      return;
    }
    has_line = edit_get_line
                      ((EditLineView *)((i8 *)&editor_text_edit_block.editor_text_edit),line_idx,(char *)line_buf,0x100);
    if (has_line == 0) {
      *(i32 *)(editor_text_dlg_wnd_block.editor_text_lines_out + line_idx * 4) = 0;
    }
    else {
      len = _strlen(line_buf);
      line_copy = memblock_alloc_checked((iptr)&unit_types_block.str_empty_188,len + 1);
      *(i32 *)(editor_text_dlg_wnd_block.editor_text_lines_out + line_idx * 4) = line_copy;
      if (*(int *)(editor_text_dlg_wnd_block.editor_text_lines_out + line_idx * 4) == 0) {
        *(i32 *)(editor_text_dlg_wnd_block.editor_text_lines_out + line_idx * 4) = 0;
        goto finish_ok;
      }
      crt_strcpy((char *)((void *)(*(i32 *)(editor_text_dlg_wnd_block.editor_text_lines_out + line_idx * 4))),line_buf);
    }
    line_idx++;
  } while( true );
}

/* 004ce2f3 auto */
void __cdecl editor_text_dlg_on_cancel(void)

{
  editor_font_block.editor_text_result = 0;
  editor_font_block.editor_text_active = 0;
  wnd_end_modal_loop((ModalMenuWindow *)((i8 *)&editor_text_dlg_wnd_block.editor_text_dlg_inner));
  return;
}

/* 004ce322 auto */
void __cdecl editor_text_dlg_redraw(void)

{
  frame_wnd_draw_caption((FrameWindow *)((i8 *)&editor_text_dlg_wnd_block.editor_text_dlg_wnd));
  gfx_fill_rect((iptr)&editor_text_dlg_wnd_block.editor_text_dlg_wnd,(iptr)&editor_text_dlg_wnd_block.editor_text_fill_rect,0x1d);
  text_set_surface((iptr)&editor_text_dlg_wnd_block.editor_text_dlg_wnd);
  text_set_font((iptr)&editor_font_block.editor_font);
  text_set_colors(0x29,0x12,1,1);
  wnd_blit_surface((DibSurface *)((i8 *)&editor_text_dlg_wnd_block.editor_text_dlg_wnd));
  return;
}

/* 004ce38a auto */
/* WARNING: Removing unreachable block (ram,0x004ce598) */
/* WARNING: Removing unreachable block (ram,0x004ce49e) */
/* WARNING: Removing unreachable block (ram,0x004ce621) */

i32 __cdecl editor_text_edit_dialog(iptr lines,const char *title)

{
  i32 result;
  int button_y;
  iptr label;
  int line_idx;
  Control cancel_btn;
  int button_height;
  int button_x;
  int button_width2;
  i8 rect[16];
  Control ok_btn;
  i32 seh_prev;
  i8 *seh_handler;
  uint eh_state;
  
  eh_state = 0xffffffff;
  button_ctor(&ok_btn);
  eh_state = 0;
  button_ctor(&cancel_btn);
  eh_state = (eh_state & 0xffffff00 | (byte)(1));
  editor_font_block.editor_text_active = 1;
  editor_text_dlg_wnd_block.editor_text_lines_out = lines;
  button_height = font_line_spacing((GameFont *)(*(i8 * *)(dialog_default_text_font_rest + 8)));
  button_height += 8;
  button_y = font_line_spacing((GameFont *)((i8 *)&editor_font_block.editor_font));
  editor_text_dlg_create(title,0xd,0,0x14,600,button_y * 0x14 + button_height,0,0,0);
  button_height = font_line_spacing((GameFont *)(*(i8 * *)(dialog_default_text_font_rest + 8)));
  button_height += 8;
  button_width2 = (editor_text_dlg_wnd_block.editor_text_dlg_client_width - 6) / 2;
  rect_set_xywh((iptr)rect,editor_text_dlg_wnd_block.editor_text_dlg_client_x + 4,editor_text_dlg_wnd_block.editor_text_dlg_client_y + 4,editor_text_dlg_wnd_block.editor_text_dlg_client_width - 9,
                     (editor_text_dlg_wnd_block.editor_text_dlg_client_height - button_height) - 9);
  edit_create_styled
            ((EditControl *)((i8 *)&editor_text_edit_block.editor_text_edit),(iptr)&editor_text_dlg_wnd_block.editor_text_dlg_inner,0xc9,(iptr)rect,0,2,1);
  for (line_idx = 0; (line_idx < 0x14 && (*(int *)(lines + line_idx * 4) != 0));
      line_idx = line_idx + 1) {
    if (line_idx != 0) {
      edit_replace_sel((Control *)((i8 *)&editor_text_edit_block.editor_text_edit),(const char *)&str_empty_122);
    }
    edit_replace_sel
              ((Control *)((i8 *)&editor_text_edit_block.editor_text_edit),(const char *)(*(iptr *)(lines + line_idx * 4)));
  }
  button_y = (editor_text_dlg_wnd_block.editor_text_dlg_client_y + editor_text_dlg_wnd_block.editor_text_dlg_client_height) - (button_height + 2);
  button_x = editor_text_dlg_wnd_block.editor_text_dlg_client_x + 2;
  rect_set_xywh((iptr)rect,button_x,button_y,button_width2,button_height);
  label = (iptr)(label_string(*(i32 *)(label_string_ids + 0x3f8)));
  button_create(&ok_btn,(iptr)&editor_text_dlg_wnd_block.editor_text_dlg_inner,0x65,(iptr)rect,(const char *)label);
  button_set_callback(&ok_btn,(iptr)editor_text_dlg_on_ok);
  button_x = button_x + button_width2 + 2;
  rect_set_xywh((iptr)rect,button_x,button_y,button_width2,button_height);
  label = (iptr)(label_string(*(i32 *)(label_string_ids + 0x3fc)));
  button_create(&cancel_btn,(iptr)&editor_text_dlg_wnd_block.editor_text_dlg_inner,0x66,(iptr)rect,(const char *)label);
  button_set_callback(&cancel_btn,(iptr)editor_text_dlg_on_cancel);
  ctrl_set_cancel_button(&cancel_btn);
  wnd_set_redraw_callback((SurfaceWindow *)((i8 *)&editor_text_dlg_wnd_block.editor_text_dlg_wnd),(iptr)editor_text_dlg_redraw);
  wnd_repaint((SurfaceWindow *)((i8 *)&editor_text_dlg_wnd_block.editor_text_dlg_wnd));
  window_show((WindowObjectView *)((i8 *)&editor_text_dlg_wnd_block.editor_text_dlg_wnd));
  wnd_run_modal_loop((ModalMenuWindow *)((i8 *)&editor_text_dlg_wnd_block.editor_text_dlg_inner));
  while (editor_font_block.editor_text_active != 0) {
    win_pump_one_message();
  }
  frame_wnd_close((DibSurface *)((i8 *)&editor_text_dlg_wnd_block.editor_text_dlg_wnd));
  result = editor_font_block.editor_text_result;
  eh_state = eh_state & 0xffffff00;
  /* inlined unwind funclet 004ce6ed */ { ctrl_dtor(&cancel_btn); }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 004ce6f9 */ { ctrl_dtor(&ok_btn); }
  return result;
}

/* 004ce71b auto */
uint __cdecl editor_check_city_name(const char *name2)

{
  int rc;
  size_t name_len;
  size_t line_len;
  uint result;
  iptr parent_wnd2;
  size_t cmp_len;
  
  rc = text_open_section((const char *)&str_city_4,0);
  if (rc == 0) {
    do {
      rc = (int)(text_read_line(1));
      if (rc == 0) goto show_error_dialog;
      name_len = _strlen((char *)name2);
      line_len = _strlen(((i8 *)&map_views_block.text_buffer));
      if (line_len < name_len) {
        cmp_len = _strlen((char *)name2);
      }
      else {
        cmp_len = _strlen(((i8 *)&map_views_block.text_buffer));
      }
      rc = __strnicmp((char *)name2,((i8 *)&map_views_block.text_buffer),cmp_len);
    } while (rc != 0);
    text_close_file();
    result = 1;
  }
  else {
show_error_dialog:
    if (editor_text_dlg_wnd_block.active_editor_wnd == 0) {
      parent_wnd2 = 0;
    }
    else {
      parent_wnd2 = editor_text_dlg_wnd_block.active_editor_wnd + 0x48;
    }
    dlg_set_parent_window(parent_wnd2);
    text_set_string_arg(0,name2);
    rc = popup_debug_text((const char *)&str_nocity);
    dlg_set_parent_window(0);
    result = (uint)(rc == 0);
  }
  return result;
}

/* 004ce83d auto */
void __cdecl editor_wnd_on_move_close_dropdowns(void)

{
  HWND hWnd;
  UINT Msg;
  WPARAM wParam;
  LPARAM lParam;
  int i;
  
  for (i = 0; i < *(int *)(editor_text_dlg_wnd_block.active_editor_wnd + 0x2f8); i++) {
    lParam = 0;
    wParam = 0;
    Msg = 0x14f;
    hWnd = control_get_hwnd
                           ((ControlHwndView *)(editor_text_dlg_wnd_block.active_editor_wnd + 0x2fc + i * 0x38));
    SendMessageA(hWnd,Msg,wParam,lParam);
  }
  return;
}

/* 004ce8a4 auto */
i32 __cdecl editor_input_long(const char *file_name,const char *section,int default_value,iptr out_value)

{
  long value;
  char input_buf[260];
  char default_buf[20];
  i32 result;
  
  __itoa(default_value,default_buf,10);
  result = dlg_text_input((iptr)(file_name),section,6,(iptr)default_buf,(iptr)input_buf);
  value = _atol(input_buf);
  *(long *)out_value = value;
  return result;
}

/* 00553dfd auto */
i32 __cdecl editor_create_scenario_folder(void)

{
  int rc;
  size_t len;
  DWORD attrs;
  char folder_name[260];
  CHAR path[260];
  int retry;
  
  rc = _strcmp(((i8 *)&net_map_lock_slots_block.scenario_dir_path),((i8 *)&civ_saved_cursor_x_block.game_home_dir));
  if (rc == 0) {
    do {
      retry = 0;
      do {
        rc = dlg_text_input((iptr)&str_debug_11,(const char *)&str_newfolder,8,(iptr)&str_empty_168,(iptr)folder_name);
        if (rc < 0) {
          return 0;
        }
        len = _strlen(folder_name);
      } while (len == 0);
      rc = str_find_bad_filename_char((const char *)folder_name);
      if (rc == 0) {
        crt_strcpy(path,((i8 *)&civ_saved_cursor_x_block.game_home_dir));
        crt_strcat(path,str_scenario_4);
        crt_strcat(path,folder_name);
        attrs = GetFileAttributesA(path);
        if (attrs != 0xffffffff) {
          text_set_string_arg(0,(const char *)path);
          popup_text((const char *)&str_debug_11,(const char *)&str_direxists);
          retry = 1;
        }
      }
      else {
        text_set_string_arg(0,(const char *)folder_name);
        popup_text((const char *)&str_debug_11,(const char *)&str_badname);
        retry = 1;
      }
    } while (retry != 0);
    crt_mkdir(path);
    crt_strcpy(((i8 *)&net_map_lock_slots_block.scenario_dir_path),path);
    crt_strcat(path,str_sound_4);
    crt_mkdir(path);
    crt_strcpy(path,((i8 *)&net_map_lock_slots_block.scenario_dir_path));
    crt_strcat(path,((i8 *)&scenario_path_sep_str));
    crt_strcat(path,folder_name);
    crt_strcat(path,((i8 *)&scenario_file_ext_str));
    save_write_game((const char *)path,1);
  }
  return 1;
}

/* 00553ff6 auto */
void __cdecl editor_toggle_scenario_flag(void)

{
  int rc;
  
  if (((game.game_options & 0x8000) == 0) && ((game.game_flags & 0x10) == 0)) {
    rc = popup_game_with_sprite((const char *)&str_reallycheat,(iptr)&popup_info_icon_sprite,0);
    if (rc == 0) {
      return;
    }
    game.game_flags = game.game_flags | 0x10;
    game.game_options = game.game_options | 0x8000;
    rc = editor_create_scenario_folder();
    if (rc != 0) {
      popup_text((const char *)&str_help_15,(const char *)&str_warning_3);
      game.game_flags = game.game_flags | 0x80;
    }
  }
  else if (((game.game_options & 0x8000) == 0) ||
          (((game.game_flags & 0x80) == 0 ||
           (rc = _strcmp(((i8 *)&net_map_lock_slots_block.scenario_dir_path),((i8 *)&civ_saved_cursor_x_block.game_home_dir)), rc == 0)))) {
    rc = _strcmp(((i8 *)&net_map_lock_slots_block.scenario_dir_path),((i8 *)&civ_saved_cursor_x_block.game_home_dir));
    if (rc == 0) {
      popup_text((const char *)&str_help_16,(const char *)&str_warning_4);
    }
    rc = editor_create_scenario_folder();
    if (rc == 0) {
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
