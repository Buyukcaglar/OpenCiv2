/* The game, civilizations: advances, research, government, the rules: functions translated from the original
 * (tools/gen_c.py, now edited directly), in address order. */
#include "auto_common.h"

/* 0040bd10 auto */
i32 __cdecl civ_max_tax_rate(iptr civ)

{
  i32 uVar1;
  
  if (civs[civ].government < 2) {
    uVar1 = 6;
  }
  else if (civs[civ].government == 2) {
    uVar1 = 7;
  }
  else if (civs[civ].government < 6) {
    uVar1 = 8;
  }
  else {
    uVar1 = 10;
  }
  return uVar1;
}

/* 00410070 auto */
i32 __cdecl civ_get_adjective(iptr civ)

{
  i32 uVar1;
  
  uVar1 = civ_adjective(civ);
  return uVar1;
}

/* 004151e0 auto */
#define advance (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl tech_editor_load_items(void)

{
  char *_Source;
  size_t _Count;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (advance = 0; advance < 100; advance++) {
    _Count = 0x28;
    _Source = (char *)label_string(advances[advance].name);
    _strncpy(&editor_item_names + advance * 0x28,_Source,_Count);
    (&editor_item_name_ends)[advance * 0x28] = 0;
    *(int *)(&editor_items + advance * 0x58) = (int)advances[advance].preq[0];
    *(int *)(&editor_item_field1 + advance * 0x58) = (int)advances[advance].preq[1];
    *(int *)(&editor_item_field2 + advance * 0x58) = (int)(char)advances[advance].epoch;
    *(int *)(&editor_item_field3 + advance * 0x58) = (int)(char)advances[advance].category;
    *(int *)(&editor_item_field4 + advance * 0x58) = (int)advances[advance].ai_value;
    *(int *)(&editor_item_field5 + advance * 0x58) = (int)advances[advance].civilized_mod;
  }
  return;
}
#undef advance

/* 00415307 auto */
#define advance (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl tech_editor_save_items(void)

{
  char *_Dest;
  char *_Source;
  size_t _Count;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (advance = 0; advance < 100; advance++) {
    _Count = 0x14;
    _Source = &editor_item_names + advance * 0x28;
    _Dest = (char *)label_string(advances[advance].name);
    _strncpy(_Dest,_Source,_Count);
    advances[advance].preq[0] = (&editor_items)[advance * 0x58];
    advances[advance].preq[1] = (&editor_item_field1)[advance * 0x58];
    advances[advance].epoch = (&editor_item_field2)[advance * 0x58];
    advances[advance].category = (&editor_item_field3)[advance * 0x58];
    advances[advance].ai_value = (&editor_item_field4)[advance * 0x58];
    advances[advance].civilized_mod = (&editor_item_field5)[advance * 0x58];
  }
  return;
}
#undef advance

/* 0041541a auto */
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(char (*)[8])(frame_ + FRAME_OFF(8)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(16)))
void __cdecl tech_editor_update_controls(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_14 = 1; local_14 < 7; local_14++) {
    if (*(int *)(&tech_editor_ctrl_kinds + local_14 * 8) == 9) {
      iVar1 = ctrl_get_id
                        ((ControlIdView *)
                         (*(int *)(&tech_editor_ctrl_slots + local_14 * 8) * 0x48 + 0x44c + active_editor_wnd));
      _sprintf(local_10,&tech_editor_int_fmt,
               *(i32 *)(&editor_ctrl_values + iVar1 * 4 + *(int *)(active_editor_wnd + 0x2ec) * 0x58));
      ctrl_set_text
                ((ControlTextView *)
                 (*(int *)(&tech_editor_ctrl_slots + local_14 * 8) * 0x48 + 0x44c + active_editor_wnd),
                 (iptr)local_10);
    }
    else if (*(int *)(&tech_editor_ctrl_kinds + local_14 * 8) == 0xc) {
      iVar1 = ctrl_get_id
                        ((ControlIdView *)
                         (active_editor_wnd + 0x2fc + *(int *)(&tech_editor_ctrl_slots + local_14 * 8) * 0x38));
      local_8 = *(iptr *)(&editor_ctrl_values + iVar1 * 4 + *(int *)(active_editor_wnd + 0x2ec) * 0x58);
      if (local_14 < 3) {
        local_8 += 2;
      }
      combo_set_cur_sel
                ((ComboBoxSetSelView *)
                 (active_editor_wnd + 0x2fc + *(int *)(&tech_editor_ctrl_slots + local_14 * 8) * 0x38),local_8);
    }
  }
  return;
}
#undef local_14
#undef local_10
#undef local_8

/* 0041557b auto */
#define local_18 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(char (*)[8])(frame_ + FRAME_OFF(8)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
int __cdecl tech_editor_store_controls(void)

{
  int iVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_14 = 0;
  for (local_18 = 1; local_18 < 7; local_18++) {
    if (*(int *)(&tech_editor_ctrl_kinds + local_18 * 8) == 9) {
      ctrl_get_text
                ((ControlTextView *)
                 (*(int *)(&tech_editor_ctrl_slots + local_18 * 8) * 0x48 + 0x44c + active_editor_wnd),
                 (iptr)local_10);
      local_8 = _atoi(local_10);
      iVar1 = ctrl_get_id
                        ((ControlIdView *)
                         (*(int *)(&tech_editor_ctrl_slots + local_18 * 8) * 0x48 + 0x44c + active_editor_wnd));
      iVar1 -= 0xca;
      uVar2 = int_clamp(local_8,*(i32 *)(&tech_editor_field_min_table + iVar1 * 4),
                                 *(i32 *)(&tech_editor_field_max_table + iVar1 * 4));
      *(i32 *)(&editor_items + *(int *)(active_editor_wnd + 0x2ec) * 0x58 + iVar1 * 4) = uVar2;
      iVar1 = ctrl_get_id
                        ((ControlIdView *)
                         (*(int *)(&tech_editor_ctrl_slots + local_18 * 8) * 0x48 + 0x44c + active_editor_wnd));
      if (*(int *)(&editor_ctrl_values + iVar1 * 4 + *(int *)(active_editor_wnd + 0x2ec) * 0x58) != local_8) {
        local_14++;
      }
    }
    else if (*(int *)(&tech_editor_ctrl_kinds + local_18 * 8) == 0xc) {
      local_8 = combo_get_cur_sel
                          ((ComboBoxGetSelView *)
                           (active_editor_wnd + 0x2fc + *(int *)(&tech_editor_ctrl_slots + local_18 * 8) * 0x38));
      if (local_18 < 3) {
        local_8 -= 2;
      }
      iVar1 = ctrl_get_id
                        ((ControlIdView *)
                         (active_editor_wnd + 0x2fc + *(int *)(&tech_editor_ctrl_slots + local_18 * 8) * 0x38));
      *(int *)(&editor_ctrl_values + *(int *)(active_editor_wnd + 0x2ec) * 0x58 + iVar1 * 4) = local_8;
    }
  }
  return local_14;
}
#undef local_18
#undef local_14
#undef local_10
#undef local_8

/* 00415765 auto */
void __cdecl tech_editor_redraw(void)

{
  tech_editor_paint((ViewWindow *)active_editor_wnd);
  return;
}

/* 00415780 auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define local_c (*(size_t *)(frame_ + FRAME_OFF(4)))
#define advance (*(iptr *)(frame_ + FRAME_OFF(8)))
i32 __cdecl tech_editor_write_civilize(FILE *param_1)

{
  char *pcVar1;
  size_t sVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (advance = 0; advance < 100; advance++) {
    text_clear();
    text_append_string_id(advances[advance].name);
    crt_strcat(&text_buffer,&civilize_rules_name_sep_str);
    pcVar1 = (char *)label_string(advances[advance].name);
    sVar2 = _strlen(pcVar1);
    if (sVar2 < 0x13) {
      pcVar1 = (char *)label_string(advances[advance].name);
      local_c = _strlen(pcVar1);
    }
    else {
      local_c = 0x13;
    }
    text_append_spaces(0x13 - local_c);
    text_append_int((int)advances[advance].ai_value);
    crt_strcat(&text_buffer,&civilize_rules_ai_sep_str);
    text_append_int_2d((int)advances[advance].civilized_mod);
    crt_strcat(&text_buffer,&civilize_rules_mod_sep_str);
    text_append_advance_abbrev((int)advances[advance].preq[0],1);
    text_append_space();
    text_append_advance_abbrev((int)advances[advance].preq[1],1);
    text_append_space();
    text_append_int((int)(char)advances[advance].epoch);
    crt_strcat(&text_buffer,&civilize_rules_epoch_sep_str);
    text_append_int((int)(char)advances[advance].category);
    crt_strcat(&text_buffer,s___006251bc);
    text_append_advance_abbrev(advance,0);
    crt_strcat(&text_buffer,&civilize_rules_newline_str);
    _fputs(&text_buffer,param_1);
  }
  return 1;
}
#undef text_buffer
#undef local_c
#undef advance

/* 00415952 auto */
#define advance2 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define advance (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(12)))
void __cdecl tech_editor_relink_prereqs(void)

{
  bool bVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  game.num_advances = 0;
  for (advance = 0; advance < 100; advance++) {
    if (advances[advance].enabled != '\0') {
      game.num_advances++;
      for (local_c = 0; local_c < 2; local_c++) {
        advance2 = (iptr)advances[advance].preq[local_c];
        bVar1 = false;
        while ((-1 < advance2 && (!bVar1))) {
          if (advances[advance2].enabled == '\0') {
            advance2 = (iptr)advances[advance2].preq[0];
          }
          else {
            bVar1 = true;
          }
        }
        advances[advance].preq[local_c] = (i8)advance2;
      }
    }
  }
  return;
}
#undef advance2
#undef advance
#undef local_c

/* 00415a40 auto */
#define editor_running (*(i32 *)((u8 *)&g.d_006a1d7c))
#define local_28 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_24 (*(char (*)[32])(frame_ + FRAME_OFF(4)))
void __cdecl tech_editor_on_ok(void)

{
  iptr iVar1;
  HWND hWnd;
  iptr iVar2;
  int iVar3;
  char *lpText;
  char *lpCaption;
  UINT uType;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = tech_editor_store_controls();
  if (iVar1 == 0) {
    tech_editor_save_items();
    tech_editor_relink_prereqs();
    rules_edit_set_section(ADDR(0x6251d0, ((u8 *)&g.d_006251d0)),ADDR(0x401be5, tech_editor_write_civilize));
    iVar2 = rules_write_sections();
    if (iVar2 == 0) {
      _sprintf(local_24,s_Error_updating_RULES__s_006251dc,&lang_file_ext);
      uType = 0x10;
      lpCaption = s_File_I_O_Error_006251f4;
      lpText = local_24;
      iVar3 = wnd_get_window((WndBase *)(active_editor_wnd + 0x48));
      MessageBoxA(*(HWND *)(iVar3 + 4),lpText,lpCaption,uType);
    }
    editor_running = 0;
    wnd_end_modal_loop((ModalMenuWindow *)(active_editor_wnd + 0x48));
    menu_update_states();
  }
  else {
    tech_editor_update_controls();
    tech_editor_redraw();
    if (active_editor_wnd == 0) {
      local_28 = 0;
    }
    else {
      local_28 = active_editor_wnd + 0x48;
    }
    dlg_set_parent_window(local_28);
    popup_text(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x6251c8, ((u8 *)&g.d_006251c8)));
    dlg_set_parent_window(0);
    hWnd = (HWND)control_get_hwnd((ControlHwndView *)(active_editor_wnd + 0x2fc));
    SetFocus(hWnd);
  }
  return;
}
#undef editor_running
#undef local_28
#undef local_24

/* 00415b52 auto */
#define advance (*(iptr *)(frame_ + FRAME_OFF(4)))
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_54 (*(char (*)[80])(frame_ + FRAME_OFF(20)))
void __cdecl tech_editor_fill_usage_list(void)

{
  bool bVar1;
  bool bVar2;
  iptr iVar3;
  i32 uVar4;
  i32 uVar5;
  i32 uVar6;
  i8 frame_[FRAME_OFF(104)] __attribute__((aligned(8)));  /* original stack frame */
  
  bVar2 = false;
  bVar1 = false;
  listbox_clear((ListBoxClearView *)(active_editor_wnd + 0xa94));
  for (unit_type = 0; unit_type < 0x3e; unit_type++) {
    if ((int)unit_types[unit_type].prerequisite == *(int *)(active_editor_wnd + 0x2ec)) {
      if (!bVar1) {
        iVar3 = label_string(*(i32 *)(label_string_ids + 0x808));
        listbox_add_string((ListBoxAddView *)(active_editor_wnd + 0xa94),iVar3);
        bVar1 = true;
      }
      iVar3 = label_string(unit_types[unit_type].name);
      listbox_add_string((ListBoxAddView *)(active_editor_wnd + 0xa94),iVar3);
    }
  }
  for (advance = 0; advance < 100; advance++) {
    if ((int)advances[advance].preq[0] == *(int *)(active_editor_wnd + 0x2ec)) {
      if (!bVar2) {
        iVar3 = label_string(*(i32 *)(label_string_ids + 0x80c));
        listbox_add_string((ListBoxAddView *)(active_editor_wnd + 0xa94),iVar3);
        bVar2 = true;
      }
      if (advances[advance].preq[1] < '\0') {
        uVar4 = label_string(advances[advance].name);
        _sprintf(local_54,&tech_editor_usage_preq1_fmt,uVar4);
      }
      else {
        uVar4 = label_string(advances[advances[advance].preq[1]].name);
        uVar5 = label_string(*(i32 *)(label_string_ids + 0x1ec));
        uVar6 = label_string(advances[advance].name);
        _sprintf(local_54,s__s___s__s__00625204,uVar6,uVar5,uVar4);
      }
      listbox_add_string((ListBoxAddView *)(active_editor_wnd + 0xa94),(iptr)local_54);
    }
    else if ((int)advances[advance].preq[1] == *(int *)(active_editor_wnd + 0x2ec)) {
      if (!bVar2) {
        iVar3 = label_string(*(i32 *)(label_string_ids + 0x80c));
        listbox_add_string((ListBoxAddView *)(active_editor_wnd + 0xa94),iVar3);
        bVar2 = true;
      }
      if (advances[advance].preq[0] < '\0') {
        uVar4 = label_string(advances[advance].name);
        _sprintf(local_54,&tech_editor_usage_preq2_fmt,uVar4);
      }
      else {
        uVar4 = label_string(advances[advances[advance].preq[0]].name);
        uVar5 = label_string(*(i32 *)(label_string_ids + 0x1ec));
        uVar6 = label_string(advances[advance].name);
        _sprintf(local_54,s__s___s__s__00625214,uVar6,uVar5,uVar4);
      }
      listbox_add_string((ListBoxAddView *)(active_editor_wnd + 0xa94),(iptr)local_54);
    }
  }
  return;
}
#undef advance
#undef unit_type
#undef local_54

/* 00415e53 auto */
#define local_134 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_130 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_12c (*(char (*)[19])(frame_ + FRAME_OFF(12)))
#define local_119 (*(i8 *)(frame_ + FRAME_OFF(31)))
#define local_118 (*(char (*)[260])(frame_ + FRAME_OFF(32)))
#define local_14 (*(iptr *)(frame_ + FRAME_OFF(292)))
#define local_10 (*(iptr *)(frame_ + FRAME_OFF(296)))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(300)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(304)))
void __cdecl tech_editor_on_rename(void)

{
  int iVar1;
  size_t sVar2;
  iptr iVar3;
  i8 frame_[FRAME_OFF(312)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = *(int *)(active_editor_wnd + 0x2ec);
  _strncpy(local_12c,&editor_item_names + iVar1 * 0x28,0x14);
  local_119 = 0;
  do {
    if (active_editor_wnd == 0) {
      local_134 = 0;
    }
    else {
      local_134 = active_editor_wnd + 0x48;
    }
    dlg_push_parent_window(local_134);
    local_8 = dlg_text_input(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x625224, ((u8 *)&g.d_00625224)),0x13,(iptr)local_12c,(iptr)local_118);
    dlg_pop_parent_window();
    if (local_8 == -1) break;
    sVar2 = _strlen(local_118);
  } while (sVar2 == 0);
  if (-1 < local_8) {
    crt_strcpy(&editor_item_names + iVar1 * 0x28,local_118);
    local_c = combo_get_cur_sel((ComboBoxGetSelView *)(active_editor_wnd + 0x2fc));
    local_10 = combo_get_cur_sel((ComboBoxGetSelView *)(active_editor_wnd + 0x334));
    local_14 = combo_get_cur_sel((ComboBoxGetSelView *)(active_editor_wnd + 0x36c));
    combo_clear((ComboBoxClearView *)(active_editor_wnd + 0x2fc));
    combo_clear((ComboBoxClearView *)(active_editor_wnd + 0x334));
    combo_clear((ComboBoxClearView *)(active_editor_wnd + 0x36c));
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x7c0));
    combo_add_string((ComboBoxAddView *)(active_editor_wnd + 0x334),iVar3);
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x7c0));
    combo_add_string((ComboBoxAddView *)(active_editor_wnd + 0x36c),iVar3);
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x7c4));
    combo_add_string((ComboBoxAddView *)(active_editor_wnd + 0x334),iVar3);
    iVar3 = label_string(*(i32 *)(label_string_ids + 0x7c4));
    combo_add_string((ComboBoxAddView *)(active_editor_wnd + 0x36c),iVar3);
    for (local_130 = 0; local_130 < 100; local_130++) {
      combo_add_string
                ((ComboBoxAddView *)(active_editor_wnd + 0x2fc),(iptr)(&editor_item_names + local_130 * 0x28));
      combo_add_string
                ((ComboBoxAddView *)(active_editor_wnd + 0x334),(iptr)(&editor_item_names + local_130 * 0x28));
      combo_add_string
                ((ComboBoxAddView *)(active_editor_wnd + 0x36c),(iptr)(&editor_item_names + local_130 * 0x28));
    }
    combo_set_cur_sel((ComboBoxSetSelView *)(active_editor_wnd + 0x2fc),local_c);
    combo_set_cur_sel((ComboBoxSetSelView *)(active_editor_wnd + 0x334),local_10);
    combo_set_cur_sel((ComboBoxSetSelView *)(active_editor_wnd + 0x36c),local_14);
    tech_editor_fill_usage_list();
    tech_editor_redraw();
  }
  return;
}
#undef local_134
#undef local_130
#undef local_12c
#undef local_119
#undef local_118
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 0041612e auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
void __cdecl tech_editor_on_help(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (active_editor_wnd == 0) {
    local_8 = 0;
  }
  else {
    local_8 = active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(local_8);
  popup_text(ADDR(0x62523c, ((u8 *)&g.d_0062523c)),ADDR(0x625230, ((u8 *)&g.d_00625230)));
  dlg_set_parent_window(0);
  return;
}
#undef local_8

/* 0041618d auto */
#define editor_running (*(i32 *)((u8 *)&g.d_006a1d7c))
void __cdecl tech_editor_on_cancel(void)

{
  editor_running = 0;
  wnd_end_modal_loop((ModalMenuWindow *)(active_editor_wnd + 0x48));
  return;
}
#undef editor_running

/* 004161b5 auto */
void __cdecl tech_editor_on_edit_icon(void)

{
  i32 uVar1;
  i32 uVar2;
  i8 *puVar3;
  
  puVar3 = ((void *)ADDR(0x00401d8e, sprite_sheet_save_tech_icons));
  uVar2 = 0;
  uVar1 = label_string(*(i32 *)(label_string_ids + 0x7d8));
  sprite_editor_run((iptr)(&advance_category_icon_sprites +
                           *(int *)(&editor_item_field3 + *(int *)(active_editor_wnd + 0x2ec) * 0x58) * 0xf0 +
                           *(int *)(&editor_item_field2 + *(int *)(active_editor_wnd + 0x2ec) * 0x58) * 0x3c),
                     uVar1,uVar2,(iptr)puVar3);
  tech_editor_redraw();
  return;
}

/* 0041623d auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
void __cdecl tech_editor_on_combo(int param_1)

{
  int iVar1;
  HWND hWnd;
  i32 uVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_1 == 0xc9) {
    iVar1 = tech_editor_store_controls();
    if (iVar1 == 0) {
      uVar2 = combo_get_cur_sel((ComboBoxGetSelView *)(active_editor_wnd + 0x2fc));
      *(i32 *)(active_editor_wnd + 0x2ec) = uVar2;
      tech_editor_update_controls();
      tech_editor_fill_usage_list();
      tech_editor_redraw();
    }
    else {
      combo_set_cur_sel
                ((ComboBoxSetSelView *)(active_editor_wnd + 0x2fc),*(iptr *)(active_editor_wnd + 0x2ec));
      tech_editor_update_controls();
      tech_editor_redraw();
      if (active_editor_wnd == 0) {
        local_8 = 0;
      }
      else {
        local_8 = active_editor_wnd + 0x48;
      }
      dlg_set_parent_window(local_8);
      popup_text(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x625244, ((u8 *)&g.d_00625244)));
      dlg_set_parent_window(0);
      hWnd = (HWND)control_get_hwnd((ControlHwndView *)(active_editor_wnd + 0x2fc));
      SetFocus(hWnd);
    }
  }
  else if ((param_1 == 0xcc) || (param_1 == 0xcd)) {
    tech_editor_store_controls();
    tech_editor_fill_usage_list();
    tech_editor_redraw();
  }
  return;
}
#undef local_8

/* 00416354 auto */
#define editor_next_ctrl_id (*(int *)((u8 *)&g.d_006a1d80))
#define local_28 (*(u8 * *)(frame_ + FRAME_OFF(0)))
#define advance (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
void __thiscall tech_editor_create_combo(ViewWindow *this,int param_1)

{
  int iVar1;
  iptr iVar2;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  rect_set_xywh((iptr)local_14,*(int *)(&tech_editor_combo_x_table + param_1 * 8) + this->client_x - 0x1e,
                     *(int *)(&tech_editor_combo_y_table + param_1 * 8) + this->client_y,0xa0,
                     this->field_2e8 << 3);
  iVar1 = editor_next_ctrl_id;
  editor_next_ctrl_id++;
  if (this == (ViewWindow *)0x0) {
    local_28 = (u8 *)0x0;
  }
  else {
    local_28 = this->pad_48;
  }
  combo_create
            ((Control *)(this->pad_2d4 + param_1 * 0x38 + 0x28),(iptr)local_28,iVar1,
             (iptr)local_14);
  combo_set_font((ComboBoxFontView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),ADDR(0x6a4f90, ((u8 *)&g.d_006a4f90)));
  combo_set_callback((ComboBoxCallbackSetView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),ADDR(0x401f7d, tech_editor_on_combo));
  switch(param_1) {
  case 0:
    for (advance = 0; advance < 100; advance++) {
      iVar2 = label_string(advances[advance].name);
      combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar2);
    }
    break;
  case 1:
  case 2:
    iVar2 = label_string(*(i32 *)(label_string_ids + 0x7c0));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar2);
    iVar2 = label_string(*(i32 *)(label_string_ids + 0x7c4));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar2);
    for (advance = 0; advance < 100; advance++) {
      iVar2 = label_string(advances[advance].name);
      combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar2);
    }
    break;
  case 3:
    iVar2 = label_string(*(i32 *)(label_string_ids + 0x810));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar2);
    iVar2 = label_string(*(i32 *)(label_string_ids + 0x814));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar2);
    iVar2 = label_string(*(i32 *)(label_string_ids + 0x818));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar2);
    iVar2 = label_string(*(i32 *)(label_string_ids + 0x81c));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar2);
    break;
  case 4:
    iVar2 = label_string(*(i32 *)(label_string_ids + 0x820));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar2);
    iVar2 = label_string(*(i32 *)(label_string_ids + 0x824));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar2);
    iVar2 = label_string(*(i32 *)(label_string_ids + 0x828));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar2);
    iVar2 = label_string(*(i32 *)(label_string_ids + 0x82c));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar2);
    iVar2 = label_string(*(i32 *)(label_string_ids + 0x830));
    combo_add_string((ComboBoxAddView *)(this->pad_2d4 + param_1 * 0x38 + 0x28),iVar2);
  }
  return;
}
#undef editor_next_ctrl_id
#undef local_28
#undef advance
#undef local_14

/* 00416734 auto */
#define editor_next_ctrl_id (*(int *)((u8 *)&g.d_006a1d80))
#define tech_editor_edit_x_table (*(i32 *)((u8 *)&g.d_00625150))
#define tech_editor_edit_y_table (*(i32 *)((u8 *)&g.d_00625154))
#define local_24 (*(u8 * *)(frame_ + FRAME_OFF(4)))
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(20)))
void __thiscall tech_editor_create_edit(ViewWindow *this,int param_1)

{
  int iVar1;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  rect_set_xywh((iptr)local_14,(&tech_editor_edit_x_table)[param_1 * 2] + this->client_x,
                     (&tech_editor_edit_y_table)[param_1 * 2] + this->client_y,0x30,this->field_2e8 + 6);
  iVar1 = editor_next_ctrl_id;
  editor_next_ctrl_id++;
  if (this == (ViewWindow *)0x0) {
    local_24 = (u8 *)0x0;
  }
  else {
    local_24 = this->pad_48;
  }
  edit_create
            ((EditControl *)(this[1].pad_48 + param_1 * 0x48 - 0x2c),(iptr)local_24,iVar1,
             (iptr)local_14,ADDR(0x62524c, ((u8 *)&g.d_0062524c)));
  edit_set_max_len((EditMaxLenView *)(this[1].pad_48 + param_1 * 0x48 - 0x2c),4);
  edit_set_callback((EditCallbackSetView *)(this[1].pad_48 + param_1 * 0x48 - 0x2c),ADDR(0x401019, editor_numeric_edit_filter));
  return;
}
#undef editor_next_ctrl_id
#undef tech_editor_edit_x_table
#undef tech_editor_edit_y_table
#undef local_24
#undef local_14

/* 00416828 auto */
#define editor_bg_surface (*(int *)((u8 *)&g.d_0062e018))
#define editor_running (*(int *)((u8 *)&g.d_006a1d7c))
#define tech_editor_edit_x_table (*(int *)((u8 *)&g.d_00625150))
#define tech_editor_edit_y_table (*(int *)((u8 *)&g.d_00625154))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define tech_editor_category_ctrl_y_i32 (*(i32 *)((u8 *)&g.d_0062514c))
#define local_28 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_18 (*(Sprite * *)(frame_ + FRAME_OFF(16)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(20)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_c (*(int *)(frame_ + FRAME_OFF(28)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(32)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall tech_editor_paint(ViewWindow *this)

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
             (&advance_category_icon_sprites +
             *(int *)(&editor_item_field3 + this->field_2ec * 0x58) * 0xf0 +
             *(int *)(&editor_item_field2 + this->field_2ec * 0x58) * 0x3c);
  bVar1 = sprite_get_key_color(local_18);
  gfx_fill_rect_xywh((iptr)this,local_8,local_c,0x48,0x28,(uint)bVar1);
  gfx_set_scale_ratio(2,1);
  sprite_draw(local_18,(iptr)local_28,(iptr)this,local_8,local_c);
  gfx_set_scale_ratio(1,1);
  gfx_draw_tiled_frame((iptr)this,local_8,local_c,0x48,0x28,6);
  text_set_surface((iptr)this);
  text_set_font(ADDR(0x6a4f90, ((u8 *)&g.d_006a4f90)));
  text_set_colors(0x29,0x12,1,1);
  local_10 = tech_editor_prereq1_ctrl_x + this->client_x + 0x32;
  local_14 = ((tech_editor_prereq1_ctrl_y + this->client_y) - this->field_2e8) - 2;
  text_clear();
  text_append_label(0x7e);
  crt_strcat(&text_buffer,&tech_editor_prereq1_suffix_str);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = tech_editor_prereq2_ctrl_x + this->client_x + 0x32;
  local_14 = ((tech_editor_prereq2_ctrl_y + this->client_y) - this->field_2e8) - 2;
  text_clear();
  text_append_label(0x7e);
  crt_strcat(&text_buffer,&tech_editor_prereq2_suffix_str);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = tech_editor_epoch_ctrl_x + this->client_x + 0x32;
  local_14 = ((tech_editor_epoch_ctrl_y + this->client_y) - this->field_2e8) - 2;
  text_clear();
  text_append_label(0x1eb);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = tech_editor_category_ctrl_x + this->client_x + 0x32;
  local_14 = ((this->client_y + tech_editor_category_ctrl_y_i32) - this->field_2e8) - 2;
  text_clear();
  text_append_label(0x1ec);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = tech_editor_edit_x_table + this->client_x + 0x18;
  local_14 = ((tech_editor_edit_y_table + this->client_y) - this->field_2e8) - 2;
  text_clear();
  text_append_label(0x1ed);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = tech_editor_modifier_edit_x + this->client_x + 0x18;
  local_14 = ((tech_editor_modifier_edit_y + this->client_y) - this->field_2e8) - 2;
  text_clear();
  text_append_label(0x1ee);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  local_10 = this->client_x + (int)this->field_2d8 / 2;
  local_14 = (this->client_y - this->field_2e8) + 0xe6;
  text_clear();
  text_append_label(0x1ea);
  text_draw_centered((iptr)this,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_10,local_14,0);
  wnd_blit_surface((DibSurface *)this);
  return;
}
#undef editor_bg_surface
#undef editor_running
#undef tech_editor_edit_x_table
#undef tech_editor_edit_y_table
#undef text_buffer
#undef tech_editor_category_ctrl_y_i32
#undef local_28
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 00416c9e auto */
#define editor_bg_surface (*(DibSurface * *)((u8 *)&g.d_0062e018))
#define editor_next_ctrl_id (*(int *)((u8 *)&g.d_006a1d80))
#define editor_running (*(int *)((u8 *)&g.d_006a1d7c))
#define local_48c (*(u8 * *)(frame_ + FRAME_OFF(4)))
#define local_488 (*(u8 * *)(frame_ + FRAME_OFF(8)))
#define local_484 (*(u8 * *)(frame_ + FRAME_OFF(12)))
#define local_480 (*(u8 * *)(frame_ + FRAME_OFF(16)))
#define local_47c (*(u8 * *)(frame_ + FRAME_OFF(20)))
#define local_478 (*(u8 * *)(frame_ + FRAME_OFF(24)))
#define local_468 (*(DibSurface * *)(frame_ + FRAME_OFF(40)))
#define local_460 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_454 (*(i8 (*)[16])(frame_ + FRAME_OFF(60)))
#define local_444 (*(GamePalette *)(frame_ + FRAME_OFF(76)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1152)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1156)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(1160)))
void __thiscall tech_editor_dialog_run(ViewWindow *this)

{
  DibSurface *this_00;
  uptr uVar1;
  i32 uVar2;
  int iVar3;
  int iVar4;
  iptr iVar5;
  i32 uVar6;
  i32 uVar7;
  i32 uVar8;
  u32 uVar9;
  u32 uVar10;
  i32 uVar11;
  i32 uVar12;
  i32 uVar13;
  i8 frame_[FRAME_OFF(1168)] __attribute__((aligned(8)));  /* original stack frame */
  
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
  ui_set_ctrl_font(ADDR(0x6a4f90, ((u8 *)&g.d_006a4f90)));
  ui_set_ctrl_text_color(0x29);
  ui_set_ctrl_text_shadow(0x12,1,1);
  ui_set_ctrl_disabled_color(0x25);
  this->field_2d8 = 0x230;
  this->field_2dc = 0x17c;
  this->field_2ec = 0;
  editor_next_ctrl_id = 0xc9;
  surface_load_gif_file(editor_bg_surface,ADDR(0x625258, ((u8 *)&g.d_00625258)),10,0xc0,(iptr)&local_444);
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
  uVar2 = label_string(*(i32 *)(label_string_ids + 0x734));
  frame_wnd_create
            ((FrameWindow *)this,uVar2,uVar6,uVar7,uVar8,uVar9,uVar10,uVar11,uVar12,uVar13);
  for (local_460 = 0; local_460 < 7; local_460++) {
    if (*(int *)(&tech_editor_ctrl_kinds + local_460 * 8) == 9) {
      tech_editor_create_edit(this,*(i32 *)(&tech_editor_ctrl_slots + local_460 * 8));
    }
    else if (*(int *)(&tech_editor_ctrl_kinds + local_460 * 8) == 0xc) {
      tech_editor_create_combo(this,*(i32 *)(&tech_editor_ctrl_slots + local_460 * 8));
    }
  }
  rect_set_xywh((iptr)local_454,this->client_x + 0x32,this->client_y + 0xe7,0x1cb,0x6e);
  iVar3 = editor_next_ctrl_id;
  editor_next_ctrl_id++;
  if (this == (ViewWindow *)0x0) {
    local_478 = (u8 *)0x0;
  }
  else {
    local_478 = this->pad_48;
  }
  listbox_create
            ((Control *)&this[2].field_234,(iptr)local_478,iVar3,(iptr)local_454);
  listbox_set_font((ListBoxFontView *)&this[2].field_234,ADDR(0x6a4f90, ((u8 *)&g.d_006a4f90)));
  iVar3 = font_line_spacing((GameFont *)dialog_font_ptr);
  this->field_2e4 = iVar3 + 8;
  iVar3 = this->client_width - 10;
  this->field_2e0 = (int)(iVar3 + (iVar3 >> 0x1f & 3U)) >> 2;
  iVar4 = (this->client_y + this->client_height) - (this->field_2e4 + 2);
  iVar3 = this->client_x + 2;
  rect_set_xywh((iptr)local_454,iVar3,iVar4,this->field_2e0,this->field_2e4);
  if (this == (ViewWindow *)0x0) {
    local_47c = (u8 *)0x0;
  }
  else {
    local_47c = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x3f8));
  button_create
            ((Control *)&this[1].field_2a4,(iptr)local_47c,0x65,(iptr)local_454,iVar5);
  button_set_callback((Control *)&this[1].field_2a4,ADDR(0x401e51, tech_editor_on_ok));
  iVar3 = iVar3 + this->field_2e0 + 2;
  rect_set_xywh((iptr)local_454,iVar3,iVar4,this->field_2e0,this->field_2e4);
  if (this == (ViewWindow *)0x0) {
    local_480 = (u8 *)0x0;
  }
  else {
    local_480 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0xa8));
  button_create
            ((Control *)&this[1].field_358,(iptr)local_480,0x65,(iptr)local_454,iVar5);
  button_set_callback((Control *)&this[1].field_358,ADDR(0x402054, tech_editor_on_rename));
  iVar3 = iVar3 + this->field_2e0 + 2;
  rect_set_xywh((iptr)local_454,iVar3,iVar4,this->field_2e0,this->field_2e4);
  if (this == (ViewWindow *)0x0) {
    local_484 = (u8 *)0x0;
  }
  else {
    local_484 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x8ec));
  button_create
            ((Control *)&this[1].field_2e0,(iptr)local_484,0x66,(iptr)local_454,iVar5);
  button_set_callback((Control *)&this[1].field_2e0,ADDR(0x403bb1, tech_editor_on_help));
  rect_set_xywh((iptr)local_454,iVar3 + this->field_2e0 + 2,iVar4,this->field_2e0,
                     this->field_2e4);
  if (this == (ViewWindow *)0x0) {
    local_488 = (u8 *)0x0;
  }
  else {
    local_488 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x3fc));
  button_create
            ((Control *)&this[1].field_31c,(iptr)local_488,0x66,(iptr)local_454,iVar5);
  button_set_callback((Control *)&this[1].field_31c,ADDR(0x40394a, tech_editor_on_cancel));
  ctrl_set_cancel_button((Control *)&this[1].field_31c);
  this->field_2e0 = 0x55;
  iVar3 = font_line_spacing((GameFont *)dialog_font_ptr);
  this->field_2e4 = iVar3 + 8;
  rect_set_xywh((iptr)local_454,this->client_x + 0x19,this->client_y + 0x50,this->field_2e0,
                     this->field_2e4);
  if (this == (ViewWindow *)0x0) {
    local_48c = (u8 *)0x0;
  }
  else {
    local_48c = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x7cc));
  button_create
            ((Control *)(this[1].pad_364 + 0x30),(iptr)local_48c,0x65,(iptr)local_454,iVar5);
  button_set_callback((Control *)(this[1].pad_364 + 0x30),ADDR(0x4019d3, tech_editor_on_edit_icon));
  wnd_set_keyboard_nav((Wnd *)this->pad_48,0);
  tech_editor_load_items();
  combo_set_cur_sel((ComboBoxSetSelView *)&this->field_2fc,this->field_2ec);
  tech_editor_update_controls();
  this->field_2f8 = 5;
  wnd_set_move_handler((WndEventHandlers *)(this->pad_48 + 0x10),ADDR(0x4019d8, editor_wnd_on_move_close_dropdowns));
  wnd_set_redraw_callback((SurfaceWindow *)this,ADDR(0x402a68, tech_editor_redraw));
  tech_editor_on_combo(0xc9);
  wnd_repaint((SurfaceWindow *)this);
  window_show((WindowObjectView *)this);
  wnd_run_modal_loop((ModalMenuWindow *)this->pad_48);
  while (editor_running != 0) {
    win_pump_one_message();
  }
  if (editor_bg_surface != (DibSurface *)0x0) {
    surface_delete(editor_bg_surface,1);
  }
  editor_bg_surface = (DibSurface *)0x0;
  this->field_2f8 = 0;
  local_8 = 0xffffffff;
  /* inlined unwind funclet 00417542 */ { palette_destroy((GamePalette *)((iptr)&local_444)); }
  return;
}
#undef editor_bg_surface
#undef editor_next_ctrl_id
#undef editor_running
#undef local_48c
#undef local_488
#undef local_484
#undef local_480
#undef local_47c
#undef local_478
#undef local_468
#undef local_460
#undef local_454
#undef local_444
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00417566 auto */
#define local_b58 (*(DocumentWindow *)(frame_ + FRAME_OFF(0)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(2888)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(2892)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(2896)))
void __cdecl tech_editor_run(void)

{
  i8 frame_[FRAME_OFF(2904)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  editor_wnd_ctor(&local_b58);
  local_8 = 0;
  tech_editor_dialog_run((ViewWindow *)&local_b58);
  wnd_repaint((SurfaceWindow *)&map_views);
  local_8 = 0xffffffff;
  /* inlined unwind funclet 004175bf */ { editor_wnd_dtor((EditorWindow *)((iptr)&local_b58)); }
  return;
}
#undef local_b58
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00419cbb auto */
i8 __cdecl rules_next_line_byte_clamped(i32 param_1,i32 param_2)

{
  iptr iVar1;
  i32 uVar2;
  
  text_read_line(1);
  iVar1 = text_next_int();
  uVar2 = int_clamp(iVar1,param_1,param_2);
  return (char)uVar2;
}

/* 00419cf4 auto */
i8 __cdecl rules_next_byte_clamped(i32 param_1,i32 param_2)

{
  iptr iVar1;
  i32 uVar2;
  
  iVar1 = text_next_int();
  uVar2 = int_clamp(iVar1,param_1,param_2);
  return (char)uVar2;
}

/* 00419d23 auto */
void __cdecl rules_load_cosmic(void)

{
  text_open_section(ADDR(0x6559e8, ((u8 *)&g.d_006559e8)),ADDR(0x6252cc, ((u8 *)&g.d_006252cc)));
  cosmic.road_move_mult = rules_next_line_byte_clamped(1,10);
  cosmic.trireme_loss_chance = rules_next_line_byte_clamped(1,100);
  cosmic.food_per_citizen = rules_next_line_byte_clamped(0,10);
  cosmic.food_box_rows = rules_next_line_byte_clamped(4,0x14);
  if ((cosmic.food_box_rows & 1) != 0) {
    cosmic.food_box_rows++;
  }
  cosmic.shield_box_rows = rules_next_line_byte_clamped(4,0x14);
  cosmic.settler_food_low = rules_next_line_byte_clamped(0,10);
  cosmic.settler_food_high = rules_next_line_byte_clamped(0,10);
  cosmic.unhappy_size = rules_next_line_byte_clamped(4,0xc);
  cosmic.riot_factor = rules_next_line_byte_clamped(10,100);
  cosmic.aqueduct_size = rules_next_line_byte_clamped(4,0x32);
  cosmic.sewer_size = rules_next_line_byte_clamped(4,0x32);
  cosmic.tech_paradigm = rules_next_line_byte_clamped(3,10);
  cosmic.transform_time = rules_next_line_byte_clamped(5,100);
  cosmic.monarchy_free_support = rules_next_line_byte_clamped(0,8);
  cosmic.communism_free_support = rules_next_line_byte_clamped(0,8);
  cosmic.fundamentalism_free_support = rules_next_line_byte_clamped(0,8);
  cosmic.communism_palace_dist = rules_next_line_byte_clamped(1,0x14);
  cosmic.fund_science_loss = rules_next_line_byte_clamped(0,100);
  cosmic.change_penalty = rules_next_line_byte_clamped(0,100);
  cosmic.paradrop_range = rules_next_line_byte_clamped(4,100);
  cosmic.mass_thrust_paradigm = rules_next_line_byte_clamped(0x19,200);
  cosmic.fund_max_science = rules_next_line_byte_clamped(0,10);
  return;
}

/* 0041a046 auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define text_token_buf (*(i8 *)((u8 *)&g.d_00673e10))
#define advance2 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define advance (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(12)))
void __cdecl rules_load_advances(int param_1)

{
  bool bVar1;
  i8 uVar2;
  size_t sVar3;
  i32 uVar4;
  i32 iVar5;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  text_open_section(ADDR(0x6559e8, ((u8 *)&g.d_006559e8)),ADDR(0x6252d4, ((u8 *)&g.d_006252d4)));
  game.num_advances = 0;
  for (advance = 0; advance < 100; advance++) {
    advances[advance].preq[1] = -2;
    advances[advance].preq[0] = advances[advance].preq[1];
    if (advances[advance].preq[0] == -2) {
      advances[advance].enabled = '\0';
    }
    else {
      advances[advance].enabled = 1;
    }
  }
  for (advance = 0; advance < 100; advance++) {
    text_read_line(1);
    sVar3 = _strlen(&text_buffer);
    if ((sVar3 == 0) || (text_buffer == ';')) break;
    if (param_1 == 0) {
      iVar5 = text_next_token_str_id(0x14);
      advances[advance].name = iVar5;
    }
    else {
      text_next_token();
    }
    uVar4 = text_next_int();
    advances[advance].ai_value = (i8)uVar4;
    uVar4 = text_next_int();
    advances[advance].civilized_mod = (i8)uVar4;
    for (local_c = 0; local_c < 2; local_c++) {
      uVar4 = text_next_token();
      uVar2 = rules_parse_advance_abbrev(uVar4);
      advances[advance].preq[local_c] = uVar2;
      if (advances[advance].preq[local_c] == -3) {
        error_report(0xfffffffc,3,ADDR(0x679640, ((u8 *)&g.d_00679640)),advance,local_c);
      }
    }
    uVar4 = text_next_int();
    advances[advance].epoch = (u8)uVar4;
    uVar4 = text_next_int();
    advances[advance].category = (u8)uVar4;
    if (advances[advance].preq[0] == -2) {
      advances[advance].enabled = '\0';
    }
    else {
      advances[advance].enabled = 1;
    }
  }
  for (; advance < 100; advance++) {
    if (param_1 == 0) {
      _sprintf(&text_token_buf,s_Advance__d_006252e0,advance + 1);
      iVar5 = strpool_add_padded(ADDR(0x673e10, ((u8 *)&g.d_00673e10)),0x14);
      advances[advance].name = iVar5;
    }
    advances[advance].ai_value = 3;
    advances[advance].civilized_mod = '\0';
    for (local_c = 0; local_c < 2; local_c++) {
      advances[advance].preq[local_c] = 0xfe;
    }
    advances[advance].epoch = '\0';
    advances[advance].category = '\0';
    if (advances[advance].preq[0] == -2) {
      advances[advance].enabled = '\0';
    }
    else {
      advances[advance].enabled = 1;
    }
  }
  for (advance = 0; advance < 100; advance++) {
    if (advances[advance].enabled != '\0') {
      game.num_advances++;
      for (local_c = 0; local_c < 2; local_c++) {
        advance2 = (iptr)advances[advance].preq[local_c];
        bVar1 = false;
        while ((-1 < advance2 && (!bVar1))) {
          if (advances[advance2].enabled == '\0') {
            advance2 = (iptr)advances[advance2].preq[0];
          }
          else {
            bVar1 = true;
          }
        }
        advances[advance].preq[local_c] = (i8)advance2;
      }
    }
  }
  return;
}
#undef text_buffer
#undef text_token_buf
#undef advance2
#undef advance
#undef local_c

/* 0041a422 auto */
#define improvement (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl rules_load_improvements(int param_1)

{
  i8 iVar1;
  i32 iVar2;
  i32 uVar3;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  text_open_section(ADDR(0x6559e8, ((u8 *)&g.d_006559e8)),ADDR(0x6252ec, ((u8 *)&g.d_006252ec)));
  for (improvement = 0; improvement < 0x43; improvement++) {
    text_read_line(1);
    if (param_1 == 0) {
      iVar2 = text_next_token_str_id(0x19);
      improvements[improvement].name = iVar2;
    }
    else {
      text_next_token();
    }
    uVar3 = text_next_int();
    improvements[improvement].cost = (u8)uVar3;
    uVar3 = text_next_int();
    improvements[improvement].upkeep = (u8)uVar3;
    uVar3 = text_next_token();
    iVar1 = rules_parse_advance_abbrev(uVar3);
    improvements[improvement].preq = iVar1;
    if (improvements[improvement].preq == -3) {
      error_report(0xfffffffb,3,ADDR(0x679640, ((u8 *)&g.d_00679640)),improvement,0);
    }
    while ((-1 < improvements[improvement].preq &&
           (advances[improvements[improvement].preq].enabled == '\0'))) {
      improvements[improvement].preq = advances[improvements[improvement].preq].preq[0];
    }
  }
  text_open_section(0,ADDR(0x6252f4, ((u8 *)&g.d_006252f4)));
  for (improvement = 0; improvement < 0x1c; improvement++) {
    text_read_line(1);
    uVar3 = text_next_token();
    iVar1 = rules_parse_advance_abbrev(uVar3);
    wonder_expires[improvement] = iVar1;
    if (wonder_expires[improvement] == -3) {
      error_report(0xfffffffc,3,ADDR(0x679640, ((u8 *)&g.d_00679640)),improvement,0);
    }
  }
  return;
}
#undef improvement

/* 0041a5c4 auto */
#define double_moves_applied (*(i32 *)((u8 *)&g.d_00628068))
#define strpool_last_string (*(i32 *)((u8 *)&g.d_0063e4b8))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define text_token_buf (*(i8 *)((u8 *)&g.d_00673e10))
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl rules_load_units(int param_1)

{
  i8 iVar1;
  u8 uVar2;
  ushort uVar3;
  size_t sVar4;
  i32 uVar5;
  i32 iVar6;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  double_moves_applied = 0;
  for (unit_type = 0; unit_type < 0x3e; unit_type++) {
    unit_types[unit_type].prerequisite = -2;
  }
  text_open_section(0,ADDR(0x625300, ((u8 *)&g.d_00625300)));
  for (unit_type = 0; unit_type < 0x3e; unit_type++) {
    text_read_line(1);
    sVar4 = _strlen(&text_buffer);
    if ((sVar4 == 0) || (text_buffer == ';')) break;
    if (param_1 == 0) {
      iVar6 = text_next_token_str_id(0xf);
      unit_types[unit_type].name = iVar6;
      *(i32 *)(&unit_type_name_ptrs + unit_type * 4) = strpool_last_string;
    }
    else {
      text_next_token();
    }
    uVar5 = text_next_token();
    iVar1 = rules_parse_advance_abbrev(uVar5);
    unit_types[unit_type].obsolete_by = iVar1;
    uVar5 = text_next_int();
    unit_types[unit_type].domain = (u8)uVar5;
    uVar5 = text_next_int();
    unit_types[unit_type].move = (char)uVar5 * cosmic.road_move_mult;
    uVar5 = text_next_int();
    unit_types[unit_type].range = (u8)uVar5;
    uVar5 = text_next_int();
    unit_types[unit_type].attack = (u8)uVar5;
    uVar5 = text_next_int();
    unit_types[unit_type].defense = (u8)uVar5;
    uVar5 = text_next_int();
    unit_types[unit_type].hit_points = (char)uVar5 * '\n';
    uVar5 = text_next_int();
    unit_types[unit_type].firepower = (u8)uVar5;
    uVar2 = rules_next_byte_clamped(1,200);
    unit_types[unit_type].cost = uVar2;
    uVar5 = text_next_int();
    unit_types[unit_type].hold = (u8)uVar5;
    uVar5 = text_next_int();
    unit_types[unit_type].role = (u8)uVar5;
    uVar5 = text_next_token();
    iVar1 = rules_parse_advance_abbrev(uVar5);
    unit_types[unit_type].prerequisite = iVar1;
    uVar3 = text_next_binary();
    unit_types[unit_type].flags = (uint)uVar3;
    if ((unit_types[unit_type].obsolete_by == -3) || (unit_types[unit_type].prerequisite == -3)) {
      error_report(0xfffffffa,3,ADDR(0x679640, ((u8 *)&g.d_00679640)),unit_type,0);
    }
  }
  for (; unit_type < 0x3e; unit_type++) {
    if (param_1 == 0) {
      _sprintf(&text_token_buf,s_Unit__d_00625308,unit_type + 1);
      iVar6 = strpool_add_padded(ADDR(0x673e10, ((u8 *)&g.d_00673e10)),0xf);
      unit_types[unit_type].name = iVar6;
    }
    unit_types[unit_type].obsolete_by = -2;
    unit_types[unit_type].domain = '\0';
    unit_types[unit_type].move = '\0';
    unit_types[unit_type].range = '\0';
    unit_types[unit_type].attack = 1;
    unit_types[unit_type].defense = '\0';
    unit_types[unit_type].hit_points = '\0';
    unit_types[unit_type].firepower = '\0';
    unit_types[unit_type].cost = 1;
    unit_types[unit_type].hold = '\0';
    unit_types[unit_type].role = '\0';
    unit_types[unit_type].prerequisite = -2;
    unit_types[unit_type].flags = 0;
    if ((unit_types[unit_type].obsolete_by == -3) || (unit_types[unit_type].prerequisite == -3)) {
      error_report(0xfffffffa,3,ADDR(0x679640, ((u8 *)&g.d_00679640)),unit_type,0);
    }
  }
  return;
}
#undef double_moves_applied
#undef strpool_last_string
#undef text_buffer
#undef text_token_buf
#undef unit_type

/* 0041a95f auto */
#define terrain2 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(8)))
void __cdecl rules_load_terrain(void)

{
  i8 uVar1;
  i8 iVar2;
  i32 iVar3;
  i32 uVar4;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  text_open_section(0,ADDR(0x625310, ((u8 *)&g.d_00625310)));
  for (terrain2 = 0; terrain2 < 0x21; terrain2++) {
    text_read_line(1);
    iVar3 = text_next_token_str_id(0xf);
    terrain_types[terrain2].name = iVar3;
    uVar4 = text_next_int();
    terrain_types[terrain2].move_cost = (u8)uVar4;
    uVar4 = text_next_int();
    terrain_types[terrain2].defense = (u8)uVar4;
    for (local_8 = 0; local_8 < 3; local_8++) {
      uVar4 = text_next_int();
      *(char *)(local_8 + ADDR(0x627cca, ((u8 *)&terrain_types + 10)) + terrain2 * 0x18) = (char)uVar4;
    }
    if (terrain2 < 0xb) {
      for (local_8 = 0; local_8 < 2; local_8++) {
        uVar4 = text_next_token();
        uVar1 = rules_parse_terrain_abbrev(uVar4);
        *(i8 *)(local_8 + ADDR(0x627cce, ((u8 *)&terrain_types + 14)) + terrain2 * 0x18) = uVar1;
        uVar4 = text_next_int();
        *(char *)(local_8 + ADDR(0x627cd0, ((u8 *)&terrain_types + 16)) + terrain2 * 0x18) = (char)uVar4;
        uVar4 = text_next_int();
        *(char *)(local_8 + ADDR(0x627cd2, ((u8 *)&terrain_types + 18)) + terrain2 * 0x18) = (char)uVar4;
        uVar4 = text_next_int();
        *(char *)(local_8 + ADDR(0x627cd4, ((u8 *)&terrain_types + 20)) + terrain2 * 0x18) = (char)uVar4;
        if (*(char *)(local_8 + ADDR(0x627cce, ((u8 *)&terrain_types + 14)) + terrain2 * 0x18) == -3) {
          error_report(0xfffffff9,3,ADDR(0x679640, ((u8 *)&g.d_00679640)),terrain2,local_8);
        }
      }
      uVar4 = text_next_token();
      iVar2 = rules_parse_terrain_abbrev(uVar4);
      terrain_types[terrain2].transform_to = iVar2;
      if (terrain_types[terrain2].transform_to == -3) {
        error_report(0xfffffff9,3,ADDR(0x679640, ((u8 *)&g.d_00679640)),terrain2,99);
      }
    }
  }
  return;
}
#undef terrain2
#undef local_8

/* 0041ab18 auto */
#define local_1c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define leader (*(iptr *)(frame_ + FRAME_OFF(16)))
void __cdecl rules_load_govts_leaders(int param_1)

{
  u8 uVar1;
  i8 iVar2;
  i16 iVar3;
  i16 iVar4;
  i16 uVar5;
  i16 uVar6;
  i32 iVar7;
  i32 uVar8;
  iptr iVar9;
  int iVar10;
  i32 uVar11;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  text_open_section(0,ADDR(0x625318, ((u8 *)&g.d_00625318)));
  for (leader = 0; leader < 7; leader++) {
    text_read_line(1);
    iVar7 = text_next_token_str_id(0xf);
    government_names[leader] = iVar7;
    iVar7 = text_next_token_str_id(0xf);
    government_titles[leader].male = iVar7;
    iVar7 = text_next_token_str_id(0xf);
    government_titles[leader].female = iVar7;
  }
  text_open_section(0,ADDR(0x625324, ((u8 *)&g.d_00625324)));
  for (leader = 0; leader < 0x15; leader++) {
    text_read_line(1);
    iVar3 = leaders[leader].names[0];
    iVar4 = leaders[leader].names[1];
    uVar8 = text_next_token_str_id(0x18);
    leaders[leader].names[0] = (i16)uVar8;
    uVar8 = text_next_token_str_id(0x18);
    leaders[leader].names[1] = (i16)uVar8;
    if (param_1 == 0) {
      leaders[leader].names[0] = iVar3;
      leaders[leader].names[1] = iVar4;
    }
    uVar1 = leaders[leader].female;
    uVar11 = 1;
    uVar8 = 0;
    iVar9 = text_next_int();
    uVar8 = int_clamp(iVar9,uVar8,uVar11);
    leaders[leader].female = (u8)uVar8;
    if (param_1 == 0) {
      leaders[leader].female = uVar1;
    }
    else {
      leaders[leader].leader_name =
           leaders[leader].names[((uint)leaders[leader].female)];
    }
    iVar3 = leaders[leader].color;
    uVar8 = text_next_int();
    leaders[leader].color = (i16)uVar8;
    if (param_1 == 0) {
      leaders[leader].color = iVar3;
    }
    else {
      uVar8 = int_clamp((int)leaders[leader].color,1,7);
      leaders[leader].color = (i16)uVar8;
    }
    iVar3 = leaders[leader].city_style;
    uVar8 = text_next_int();
    leaders[leader].city_style = (i16)uVar8;
    if (param_1 == 0) {
      leaders[leader].city_style = iVar3;
    }
    else {
      uVar8 = int_clamp((int)leaders[leader].city_style,0,3);
      leaders[leader].city_style = (i16)uVar8;
    }
    iVar3 = leaders[leader].plural;
    iVar4 = leaders[leader].adjective;
    uVar8 = text_next_token_str_id(0x18);
    leaders[leader].plural = (i16)uVar8;
    uVar8 = text_next_token_str_id(0x18);
    leaders[leader].adjective = (i16)uVar8;
    if (param_1 == 0) {
      leaders[leader].plural = iVar3;
      leaders[leader].adjective = iVar4;
    }
    iVar2 = leaders[leader].attack;
    uVar8 = text_next_int();
    leaders[leader].attack = (i8)uVar8;
    if (param_1 == 0) {
      leaders[leader].attack = iVar2;
    }
    iVar2 = leaders[leader].expand;
    uVar8 = text_next_int();
    leaders[leader].expand = (i8)uVar8;
    if (param_1 == 0) {
      leaders[leader].expand = iVar2;
    }
    iVar2 = leaders[leader].civilize;
    uVar8 = text_next_int();
    leaders[leader].civilize = (i8)uVar8;
    if (param_1 == 0) {
      leaders[leader].civilize = iVar2;
    }
    for (local_18 = 0; local_18 < 7; local_18++) {
      for (local_1c = 0; local_1c < 2; local_1c++) {
        if (param_1 != 0) {
          leaders[leader].titles[local_18][local_1c] =
               (short)(&government_titles[local_18].male)[local_1c];
        }
      }
    }
    do {
      iVar10 = text_next_int();
      if (0 < iVar10) {
        uVar5 = leaders[leader].titles[iVar10][0];
        uVar6 = leaders[leader].titles[iVar10][1];
        uVar8 = text_next_token_pooled();
        leaders[leader].titles[iVar10][0] = (short)uVar8;
        uVar8 = text_next_token_pooled();
        leaders[leader].titles[iVar10][1] = (short)uVar8;
        if (param_1 == 0) {
          leaders[leader].titles[iVar10][0] = uVar5;
          leaders[leader].titles[iVar10][1] = uVar6;
        }
      }
    } while (0 < iVar10);
  }
  return;
}
#undef local_1c
#undef local_18
#undef leader

/* 0041b00e auto */
#define text_token_buf (*(char *)((u8 *)&g.d_00673e10))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl rules_parse_sections(i32 param_1)

{
  i32 iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  rules_load_cosmic();
  rules_load_advances(0);
  rules_load_improvements(0);
  rules_load_units(0);
  rules_load_terrain();
  rules_load_govts_leaders(param_1);
  text_open_section(0,ADDR(0x62532c, ((u8 *)&g.d_0062532c)));
  for (local_8 = 0; local_8 < 0x10; local_8++) {
    text_read_line(1);
    iVar1 = text_next_token_str_id(10);
    commodity_names[local_8] = iVar1;
  }
  text_open_section(0,ADDR(0x625334, ((u8 *)&g.d_00625334)));
  for (local_8 = 1; local_8 < 0xd; local_8++) {
    text_read_line(1);
    iVar1 = text_next_token_pooled();
    order_names[local_8].name = iVar1;
    text_next_token();
    order_names[local_8].key = text_token_buf;
  }
  text_open_section(0,ADDR(0x62533c, ((u8 *)&g.d_0062533c)));
  for (local_8 = 0; local_8 < 6; local_8++) {
    iVar1 = text_read_line_pooled();
    difficulty_names[local_8] = iVar1;
  }
  text_open_section(0,ADDR(0x625348, ((u8 *)&g.d_00625348)));
  for (local_8 = 0; local_8 < 9; local_8++) {
    iVar1 = text_read_line_pooled();
    attitude_names[local_8] = iVar1;
  }
  text_close_file();
  return;
}
#undef text_token_buf
#undef local_8

/* 0041b8ff auto */
#define dlg_pending_idle_callback (*(i8 * *)((u8 *)&g.d_00635a3c))
#define advance (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_38 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define aiStack_34 (*(iptr (*)[12])(frame_ + FRAME_OFF(12)))
void __cdecl civ_intro_popup(iptr civ)

{
  int iVar1;
  iptr iVar2;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  advance = 100;
  local_38 = 0;
  while ((0 < advance && (local_38 < 0xc))) {
    if (((advances[advance].preq[0] != -2) || (advances[advance].preq[1] != -2)) &&
       (iVar1 = civ_has_advance(civ,advance), iVar1 != 0)) {
      aiStack_34[local_38] = advance;
      local_38++;
    }
    advance--;
  }
  iVar2 = civ_leader_name(civ);
  text_set_string_arg(0,iVar2);
  iVar2 = civ_name_plural(civ);
  text_set_string_arg(1,iVar2);
  text_clear();
  advance = local_38;
  if (0 < local_38) {
    while (advance = advance - 1, -1 < advance) {
      text_append_string_id(advances[aiStack_34[advance]].name);
      text_append_comma();
      text_append_space();
    }
  }
  text_set_string_arg(2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  if (2 < game.multiplayer) {
    dlg_pending_idle_callback = ((void *)ADDR(0x00403c74, turn_popup_timeout_idle));
  }
  popup_game_with_sprite(ADDR(0x6254a0, ((u8 *)&g.d_006254a0)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
  return;
}
#undef dlg_pending_idle_callback
#undef advance
#undef local_38
#undef aiStack_34

/* 0041ba52: written by hand in src/game/bigframes.c */

/* 0041e864 auto */
#define local_108 (*(i8 (*)[260])(frame_ + FRAME_OFF(0)))
void __cdecl rules_load(i32 param_1)

{
  int iVar1;
  i8 frame_[FRAME_OFF(264)] __attribute__((aligned(8)));  /* original stack frame */
  
  labels_reload();
  gfx_load_game_sprites();
  __chdir(&scenario_dir_path);
  crt_strcpy(local_108,s_RULES__0062562c);
  crt_strcat(local_108,&lang_file_ext);
  iVar1 = file_exists((iptr)local_108);
  if (iVar1 == 0) {
    __chdir(&game_home_dir);
  }
  rules_parse_sections(param_1);
  __chdir(&game_home_dir);
  input_flush_events();
  return;
}
#undef local_108

/* 0042a542 auto */
void __cdecl civ_rating_title_font_global_init(void)

{
  civ_rating_title_font_static_init();
  civ_rating_title_font_reg_atexit();
  return;
}

/* 0042a55c auto */
void __cdecl civ_rating_title_font_static_init(void)

{
  font_init_styled((GameFont *)&civ_rating_title_font,0,0xc,1);
  return;
}

/* 0042a57c auto */
void __cdecl civ_rating_title_font_reg_atexit(void)

{
  _atexit(civ_rating_title_font_static_dtor);
  return;
}

/* 0042a599 auto */
void __cdecl civ_rating_title_font_static_dtor(void)

{
  font_destroy((GameFont *)&civ_rating_title_font);
  return;
}

/* 0042ad8f auto */
#define advisor_client_width (*(int *)((u8 *)&g.d_0063ec3c))
#define advisor_client_x (*(int *)((u8 *)&g.d_0063ec34))
#define advisor_first_row (*(iptr *)((u8 *)&g.d_0063ef70))
#define advisor_row_height (*(i32 *)((u8 *)&g.d_0063ef80))
#define advisor_page_count_i32 (*(i32 *)((u8 *)&g.d_0063ef68))
#define advisor_list_top_i32 (*(i32 *)((u8 *)&g.d_0063ef78))
#define advisor_list_height_i32 (*(i32 *)((u8 *)&g.d_0063ef7c))
#define advisor_list_left_i32 (*(i32 *)((u8 *)&g.d_0063ef90))
#define local_80 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define civ (*(iptr *)(frame_ + FRAME_OFF(16)))
#define local_6c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_68 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_64 (*(int *)(frame_ + FRAME_OFF(28)))
#define local_60 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_5c (*(iptr *)(frame_ + FRAME_OFF(36)))
#define local_58 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_54 (*(int *)(frame_ + FRAME_OFF(44)))
#define local_50 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_4c (*(int *)(frame_ + FRAME_OFF(52)))
#define city (*(iptr *)(frame_ + FRAME_OFF(56)))
#define local_44 (*(int *)(frame_ + FRAME_OFF(60)))
#define advance (*(iptr *)(frame_ + FRAME_OFF(64)))
#define local_3c (*(int *)(frame_ + FRAME_OFF(68)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(72)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(76)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(80)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(84)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(88)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(92)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(96)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(100)))
#define local_18 (*(i8 (*)[16])(frame_ + FRAME_OFF(104)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(120)))
/* WARNING: Removing unreachable block (ram,0x0042b48e) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl science_advisor_draw(void)

{
  iptr iVar1;
  int iVar2;
  i32 uVar3;
  int iVar4;
  i32 uVar5;
  i32 uVar6;
  i8 frame_[FRAME_OFF(128)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ = advisor_report_civ;
  frame_wnd_layout((FrameWindow *)&advisor_window);
  frame_wnd_draw_caption((FrameWindow *)&advisor_window);
  picwnd_blit((PictureWindow *)&advisor_window);
  local_50 = advisor_client_y + 2;
  local_64 = advisor_client_y + 0x174;
  local_1c = font_line_spacing((GameFont *)&advisor_font);
  text_set_surface(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)));
  text_set_font(ADDR(0x63eac0, ((u8 *)&g.d_0063eac0)));
  text_set_colors(0x25,0x12,2,1);
  text_clear();
  iVar1 = label_string(*(i32 *)(label_string_ids + 0x54c));
  text_append(iVar1);
  gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,local_50,advisor_client_width);
  local_50 += local_1c;
  text_clear();
  local_60 = int_clamp(civs[civ].government - 1,0,4);
  text_append_label(local_60 + 0x148);
  text_append_space();
  text_append_label(0x8c);
  text_append_space();
  iVar1 = civ_name_plural(civ);
  text_append(iVar1);
  gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,local_50,advisor_client_width);
  local_50 += local_1c;
  text_clear();
  iVar1 = civ_leader_title(civ);
  text_append(iVar1);
  text_append_space();
  iVar1 = civ_leader_name(civ);
  text_append(iVar1);
  text_append_colon();
  text_append_year((int)game.year);
  gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,local_50,advisor_client_width);
  local_50 = local_50 + local_1c + 6;
  if (-1 < civs[civ].researching) {
    local_44 = local_50;
    text_clear();
    text_append_label(0xec);
    text_append_colon();
    text_append_string_id(advances[civs[civ].researching].name);
    gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,local_50,advisor_client_width);
    local_50 += local_1c;
    local_6c = local_50 + 9;
    uVar6 = 1;
    iVar2 = rect_width(ADDR(0x63edcc, ((u8 *)&g.d_0063edcc)));
    iVar2 -= 10;
    uVar5 = 0xe;
    uVar3 = civ_research_cost(civ);
    sprite_draw_spaced_row(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),ADDR(0x6488d8, ((u8 *)&g.d_006488d8)),advisor_client_rect + 5,local_6c,
                       (int)civs[civ].research_progress,uVar3,uVar5,iVar2,uVar6);
    local_54 = local_50 + 0x20;
    local_50 = local_54;
    rect_set((iptr)local_18,advisor_client_rect + 2,local_44,advisor_client_right - 2,local_54);
    gfx_draw_rect_frame(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),(iptr)local_18,0x29);
    local_50 += 6;
  }
  local_34 = civ_research_cost(civ);
  local_68 = 0;
  for (city = 0; city < game.num_cities; city++) {
    if ((cities[city].id != 0) && (cities[city].owner == civ)) {
      local_68 += cities[city].science;
    }
  }
  if (local_68 != 0) {
    text_clear();
    text_append_label(0x170);
    text_append_space();
    text_append_int((local_68 - 1 + local_34) / local_68);
    text_append_space();
    text_append_label(0x171);
    gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,local_50,advisor_client_width);
    local_50 = local_50 + local_1c + 6;
  }
  local_3c = GetSystemMetrics(3);
  local_64 -= (local_3c + 2);
  local_1c = 0x16;
  advisor_row_height = 0x16;
  advisor_list_top_i32 = local_50;
  advisor_list_height_i32 = local_64 - local_50;
  advisor_rows_per_page = int_clamp((local_64 - local_50) / 0x16,1,99);
  advisor_list_left_i32 = advisor_client_x + 2;
  local_38 = advisor_client_width + advisor_client_x - 2;
  advisor_list_width = local_38 - advisor_list_left_i32;
  advisor_column_width = advisor_list_width / 3;
  advisor_items_per_page = advisor_rows_per_page * 3;
  local_2c = 0;
  local_30 = advisor_list_left_i32;
  local_8 = advisor_rows_per_page;
  for (advance = 0; advance < 100; advance++) {
    iVar2 = civ_has_advance(civ,advance);
    if (iVar2 != 0) {
      local_2c++;
    }
  }
  advisor_page_count_i32 = int_clamp((local_8 - 1 + local_2c) / local_8,1,99);
  uVar3 = int_clamp(local_2c - 1,0,999);
  advisor_first_row = int_clamp(advisor_first_row,0,uVar3);
  local_4c = 0;
  local_24 = 0;
  local_20 = 0;
  local_6c = local_50;
  local_5c = advisor_first_row;
  text_set_font(ADDR(0x63eab8, ((u8 *)&g.d_0063eab8)));
  for (advance = 0; advance < 100; advance++) {
    iVar4 = civ_has_advance(civ,advance);
    iVar2 = local_4c;
    if (((iVar4 != 0) && (iVar2 = local_4c + 1, local_5c <= local_4c)) &&
       (local_4c < advisor_items_per_page + local_5c)) {
      local_6c = local_20 * local_1c + local_50;
      local_58 = advisor_column_width * local_24 + local_30;
      local_4c = iVar2;
      sprite_draw
                ((Sprite *)
                 (&advance_category_icon_sprites +
                 (char)advances[advance].epoch * 0x3c + (char)advances[advance].category * 0xf0),
                 (iptr)local_80,ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),local_58,local_6c);
      local_28 = local_58 + 0x26;
      text_set_colors((-(uint)((char)game.first_discoverer[advance] == civ) & 0xffffffcb) +
                         0x5e,0x12,1,1);
      iVar4 = local_6c + 2;
      iVar2 = local_28;
      iVar1 = label_string(advances[advance].name);
      gfx_draw_text(iVar1,iVar2,iVar4);
      local_20++;
      iVar2 = local_4c;
      if (local_8 <= local_20) {
        local_20 = 0;
        local_24++;
        if (2 < local_24) break;
      }
    }
    local_4c = iVar2;
  }
  if (advisor_controls_created == 0) {
    rect_set((iptr)local_18,local_30,local_64,local_38,local_64 + local_3c);
    scrollbar_create((Control *)&advisor_scrollbar,ADDR(0x63eb58, ((u8 *)&g.d_0063eb58)),200,(iptr)local_18,0);
    uVar3 = int_clamp((local_8 - 1 + local_2c) / local_8 - 1,0,999);
    scrollbar_set_range((Control *)&advisor_scrollbar,0,uVar3);
    scrollbar_set_pos((ClickControl *)&advisor_scrollbar,advisor_first_row);
    scrollbar_set_page_size((Control *)&advisor_scrollbar,1);
    scrollbar_set_callback((Control *)&advisor_scrollbar,ADDR(0x402798, science_advisor_on_scroll));
    ctrl_show_and_redraw((Control *)&advisor_scrollbar);
    wnd_set_lbuttonup_handler((WndEventHandlers *)&advisor_wnd_events,ADDR(0x4034c2, science_advisor_on_click));
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
#undef advisor_list_left_i32
#undef local_80
#undef civ
#undef local_6c
#undef local_68
#undef local_64
#undef local_60
#undef local_5c
#undef local_58
#undef local_54
#undef local_50
#undef local_4c
#undef city
#undef local_44
#undef advance
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
#undef local_8

/* 0042b540 auto */
#define advisor_first_row (*(int *)((u8 *)&g.d_0063ef70))
void __cdecl science_advisor_on_scroll(int param_1)

{
  advisor_first_row = advisor_rows_per_page * param_1;
  science_advisor_draw();
  return;
}
#undef advisor_first_row

/* 0042b563 auto */
#define advisor_first_row (*(int *)((u8 *)&g.d_0063ef70))
#define advisor_row_height (*(int *)((u8 *)&g.d_0063ef80))
#define advisor_list_top_i32 (*(i32 *)((u8 *)&g.d_0063ef78))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(8)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl science_advisor_on_click(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((((-1 < param_2 - advisor_list_top_i32) &&
       (iVar1 = (param_2 - advisor_list_top_i32) / advisor_row_height, iVar1 < advisor_rows_per_page)) &&
      (-1 < param_1 - 2)) && (iVar2 = (param_1 - 2) / advisor_column_width, iVar2 < 3)) {
    iVar2 = advisor_rows_per_page * iVar2 + advisor_first_row;
    local_10 = 0;
    for (local_14 = 0; local_14 < 100; local_14++) {
      iVar3 = civ_has_advance(advisor_report_civ,local_14);
      if ((iVar3 != 0) && (bVar4 = local_10 == iVar2 + iVar1, local_10 = local_10 + 1, bVar4)) {
        pedia_show_topic_modal((DocumentWindow *)&pedia_window,local_14);
        return;
      }
    }
  }
  return;
}
#undef advisor_first_row
#undef advisor_row_height
#undef advisor_list_top_i32
#undef local_14
#undef local_10

/* 0042b65b auto */
void __cdecl science_advisor_on_goal_clicked(void)

{
  civ_research_goal_dialog(advisor_report_civ,1,0);
  return;
}

/* 0042b67d auto */
#define advisor_client_x (*(i32 *)((u8 *)&g.d_0063ec34))
#define local_14 (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
/* WARNING: Removing unreachable block (ram,0x0042b72b) */
/* WARNING: Removing unreachable block (ram,0x0042b7b6) */

void __cdecl science_advisor_show(iptr param_1)

{
  int iVar1;
  int iVar2;
  iptr iVar3;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  picwnd_open((PictureWindow *)&advisor_window,6,6,0,600,400,0,0);
  advisor_report_civ = param_1;
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
  iVar3 = label_string(*(i32 *)(label_string_ids + 0x5cc));
  button_create
            ((Control *)&advisor_toggle_button,ADDR(0x63eb58, ((u8 *)&g.d_0063eb58)),0x65,(iptr)local_14,iVar3);
  button_set_callback((Control *)&advisor_toggle_button,ADDR(0x401ae6, science_advisor_on_goal_clicked));
  wnd_set_redraw_callback((SurfaceWindow *)&advisor_window,ADDR(0x402b67, science_advisor_draw));
  wnd_repaint((SurfaceWindow *)&advisor_window);
  window_show((WindowObjectView *)&advisor_window);
  return;
}
#undef advisor_client_x
#undef local_14

/* 00434e39 auto */
#define advisor_client_width (*(int *)((u8 *)&g.d_0063ec3c))
#define advisor_client_x (*(int *)((u8 *)&g.d_0063ec34))
#define advisor_row_height (*(int *)((u8 *)&g.d_0063ef80))
#define city_angry_count (*(int *)((u8 *)&g.d_006a659c))
#define city_happy_count (*(int *)((u8 *)&g.d_006a6550))
#define city_specialist_count (*(int *)((u8 *)&g.d_006a6604))
#define city_unhappy_count (*(int *)((u8 *)&g.d_006a65a8))
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
#define scenario_objective_civ (*(short *)((u8 *)&g.d_0064bcba))
#define scenario_victory_thresholds (*(i16 *)((u8 *)&g.d_0064bcbc))
#define score_citizens (*(iptr *)((u8 *)&g.d_00673f78))
#define score_civ_objective_value (*(iptr *)((u8 *)&g.d_00673f80))
#define score_objective_civ_value (*(iptr *)((u8 *)&g.d_00673f64))
#define score_total_objective_value (*(iptr *)((u8 *)&g.d_00673f70))
#define score_wonders (*(iptr *)((u8 *)&g.d_00673f5c))
#define advisor_list_top_i32 (*(i32 *)((u8 *)&g.d_0063ef78))
#define advisor_list_height_i32 (*(i32 *)((u8 *)&g.d_0063ef7c))
#define local_90 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_80 (*(i8 (*)[16])(frame_ + FRAME_OFF(16)))
#define civ (*(iptr *)(frame_ + FRAME_OFF(32)))
#define local_6c (*(int *)(frame_ + FRAME_OFF(36)))
#define local_68 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_64 (*(int *)(frame_ + FRAME_OFF(44)))
#define local_60 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_5c (*(int *)(frame_ + FRAME_OFF(52)))
#define local_58 (*(uint *)(frame_ + FRAME_OFF(56)))
#define city (*(iptr *)(frame_ + FRAME_OFF(60)))
#define local_50 (*(int *)(frame_ + FRAME_OFF(64)))
#define local_4c (*(int *)(frame_ + FRAME_OFF(68)))
#define local_48 (*(int *)(frame_ + FRAME_OFF(72)))
#define local_44 (*(uint *)(frame_ + FRAME_OFF(76)))
#define local_40 (*(int *)(frame_ + FRAME_OFF(80)))
#define local_3c (*(iptr *)(frame_ + FRAME_OFF(84)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(88)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(92)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(96)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(100)))
#define local_28 (*(iptr *)(frame_ + FRAME_OFF(104)))
#define civ2 (*(iptr *)(frame_ + FRAME_OFF(108)))
#define local_20 (*(uint *)(frame_ + FRAME_OFF(112)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(116)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(120)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(124)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(128)))
#define local_c (*(int *)(frame_ + FRAME_OFF(132)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(136)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl civ_score_window_draw(void)

{
  iptr iVar1;
  int iVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(144)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ = advisor_report_civ;
  frame_wnd_layout((FrameWindow *)&advisor_window);
  frame_wnd_draw_caption((FrameWindow *)&advisor_window);
  picwnd_blit((PictureWindow *)&advisor_window);
  local_5c = advisor_client_y + 2;
  local_64 = advisor_client_y + 0x174;
  local_10 = font_line_spacing((GameFont *)&advisor_font);
  text_set_surface(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)));
  text_set_font(ADDR(0x63eac0, ((u8 *)&g.d_0063eac0)));
  text_set_colors(0x25,0x12,2,1);
  text_clear();
  iVar1 = label_string(*(i32 *)(label_string_ids + 0x55c));
  text_append(iVar1);
  gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,local_5c,advisor_client_width);
  local_5c += local_10;
  text_set_font(ADDR(0x63eab8, ((u8 *)&g.d_0063eab8)));
  local_10 = font_line_spacing((GameFont *)&advisor_bold_font);
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
  text_append_comma();
  text_append_year((int)game.year);
  gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,local_5c,advisor_client_width);
  advisor_list_top_i32 = local_5c + local_10 + 4;
  advisor_row_height = local_10;
  advisor_list_height_i32 = local_64 - advisor_list_top_i32;
  local_60 = advisor_client_x + 2;
  local_6c = advisor_list_top_i32;
  if ((game.game_flags & 0x20) == 0) {
    if (((game.game_flags & 0x80) == 0) || ((scenario_flags & 2) == 0)) {
      local_5c = advisor_list_top_i32;
      local_c = civ_city_style_era(civ);
      local_38 = local_6c;
      local_34 = local_60;
      local_44 = 0;
      local_20 = 0;
      local_50 = 0;
      local_18 = 0x12;
      local_8 = 0x14;
      local_14 = 0;
      for (city = 0; city < game.num_cities; city++) {
        if ((cities[city].id != 0) && (cities[city].owner == civ)) {
          city_recalc(city,1);
          local_4c = city_happy_count;
          local_2c = city_unhappy_count;
          local_68 = (((cities[city].size - city_happy_count) - city_unhappy_count) - city_specialist_count) -
                     city_angry_count;
          for (local_30 = 0; local_30 < cities[city].size; local_30++) {
            if (local_30 < local_4c) {
              local_58 = local_44 & 1;
            }
            else if (local_30 - local_4c < local_68) {
              local_58 = (local_44 & 1) + 2;
            }
            else if ((local_30 - local_4c) - local_68 < local_2c) {
              local_58 = (local_44 & 1) + 4;
            }
            else if (((local_30 - local_4c) - local_68) - local_2c < city_angry_count) {
              local_58 = (local_44 & 1) + 6;
            }
            else {
              iVar3 = city_specialist_type(city,(((local_30 - local_4c) - local_68) - local_2c) -
                                                  city_angry_count);
              local_58 = iVar3 + 7;
            }
            local_44++;
            sprite_draw
                      ((Sprite *)(&citizen_sprites + local_c * 0x294 + local_58 * 0x3c),
                       (iptr)local_80,ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),local_34,local_38);
            local_14 = 0;
            local_34 += local_8;
            local_50++;
            if (advisor_client_width + advisor_client_x - 0x1d < local_34) {
              local_50 = 0;
              local_20++;
              local_14 = 1;
              local_34 = (local_8 / 2) * (local_20 & 1) + local_60;
              local_38 += local_18;
              if ((6 < (int)local_20) || (0xf0 < local_38)) goto LAB_004355c2;
            }
          }
        }
      }
LAB_004355c2:
      if (local_14 != 0) {
        local_38 -= local_18;
      }
      local_6c = local_38 + 0x22;
      civ_calc_score(civ);
      text_clear();
      if (game_language != 1) {
        iVar1 = civ_get_adjective(civ);
        text_append(iVar1);
        text_append_space();
      }
      text_append_label(0x193);
      text_append_space();
      text_append_lparen();
      text_append_int(score_citizens);
      text_append_rparen();
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_60,local_6c);
      local_6c = local_6c + local_10 + 4;
      local_34 = local_60;
      local_50 = 0;
      local_14 = 0;
      local_38 = local_6c;
      for (local_28 = 0; local_28 < 0x1c; local_28++) {
        if ((((-1 < game.wonder_city[local_28]) && (game.wonder_city[local_28] < game.num_cities))
            && (cities[game.wonder_city[local_28]].id != 0)) &&
           (city = (iptr)game.wonder_city[local_28], cities[city].owner == civ)) {
          sprite_draw
                    ((Sprite *)(&wonder_icon_sprites + local_28 * 0x3c),(iptr)local_90,ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)),
                     local_34,local_38);
          local_40 = local_34 + 0x26;
          text_set_colors(0x5e,0x12,0xffffffff,0xffffffff);
          iVar2 = local_38 + 3;
          iVar3 = local_40;
          iVar1 = label_string(improvements[local_28 + 0x27].name);
          gfx_draw_text(iVar1,iVar3,iVar2);
          local_14 = 0;
          local_50++;
          local_34 += 0xc4;
          if (2 < local_50) {
            local_50 = 0;
            local_34 = local_60;
            local_38 += 0x16;
            local_14 = 1;
            if (0x122 < local_38) break;
          }
        }
      }
      if (local_14 == 0) {
        local_38 += 0x16;
      }
      local_6c = local_38 + 4;
      text_set_colors(0x25,0x12,0xffffffff,0xffffffff);
      text_clear();
      if (game_language != 1) {
        iVar1 = civ_get_adjective(civ);
        text_append(iVar1);
        text_append_space();
      }
      text_append_label(0x194);
      text_append_space();
      text_append_lparen();
      text_append_int(score_wonders);
      text_append_rparen();
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_60,local_6c);
      local_6c += local_10;
      if ((score_spaceship_arrived != 0) || (score_spaceship_in_flight != 0)) {
        text_clear();
        text_append_label(0x195);
        text_append_colon();
        text_append_lparen();
        if (score_spaceship_arrived == 0) {
          text_append_int(score_spaceship_in_flight);
          text_append_space();
          text_append_label(0x199);
        }
        else {
          text_append_int(score_spaceship_arrived);
        }
        text_append_rparen();
        gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_60,local_6c);
        local_6c += local_10;
      }
      local_14 = 0;
      text_clear();
      if (score_pollution != 0) {
        text_append_label(0x17c);
        text_append_space();
        text_append_lparen();
        text_append_int(score_pollution);
        text_append_rparen();
        text_append(ADDR(0x626090, ((u8 *)&g.d_00626090)));
        local_14 = 1;
      }
      if ((199 < game.turn) && (score_peace != 0)) {
        text_append_label(0x196);
        text_append_colon();
        text_append_lparen();
        text_append(ADDR(0x626098, ((u8 *)&g.d_00626098)));
        text_append_int(score_peace);
        text_append_rparen();
        text_append(ADDR(0x62609c, ((u8 *)&g.d_0062609c)));
        local_14 = 1;
      }
      if (score_future_techs != 0) {
        text_append_string_id(advances[0x59].name);
        text_append_colon();
        text_append_lparen();
        text_append(ADDR(0x6260a4, ((u8 *)&g.d_006260a4)));
        text_append_int(score_future_techs);
        text_append_rparen();
        text_append(ADDR(0x6260a8, ((u8 *)&g.d_006260a8)));
        local_14 = 1;
      }
      text_append_label(0xf);
      text_append_colon();
      text_append_lparen();
      if (-1 < score_barbarian_bonus) {
        text_append(ADDR(0x6260b0, ((u8 *)&g.d_006260b0)));
      }
      text_append_int(score_barbarian_bonus);
      text_append_rparen();
      local_14 = 1;
      gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_60,local_6c);
      local_6c += local_10;
    }
    else {
      local_6c = local_5c + local_10 + 0x2a;
      local_5c = advisor_list_top_i32;
      civ_calc_score(civ);
      text_clear();
      text_append_label(0x1b1);
      text_append_colon();
      text_append_int(score_total_objective_value);
      gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,local_6c,advisor_client_width);
      local_6c += local_10;
      if (scenario_objective_civ != 0) {
        text_clear();
        iVar1 = civ_get_adjective((int)scenario_objective_civ);
        text_append(iVar1);
        text_append_space();
        text_append_label(0x1b2);
        text_append_colon();
        text_append_int(score_objective_civ_value);
        gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,local_6c,advisor_client_width);
        local_6c += local_10;
      }
      if ((scenario_objective_civ == 0) || (scenario_objective_civ != civ)) {
        text_clear();
        iVar1 = civ_get_adjective(civ);
        text_append(iVar1);
        text_append_space();
        text_append_label(0x1b2);
        text_append_colon();
        text_append_int(score_civ_objective_value);
        gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,local_6c,advisor_client_width);
        local_6c += local_10;
      }
      if (scenario_objective_civ == 0) {
        civ2 = civ;
      }
      else {
        civ2 = (iptr)scenario_objective_civ;
      }
      local_6c += 6;
      text_set_colors(0x5e,0x12,1,1);
      for (local_3c = 0; local_3c < 4; local_3c++) {
        text_clear();
        iVar1 = civ_get_adjective(civ2);
        text_append(iVar1);
        text_append_space();
        if (local_3c == 0) {
          text_append_label(0x1b3);
        }
        else if (local_3c == 1) {
          text_append_label(0x1b4);
        }
        else if (local_3c == 2) {
          text_append_label(0x1b6);
        }
        else if (local_3c == 3) {
          text_append_label(0x1b7);
        }
        text_append_colon();
        text_append_int((int)(short)(&scenario_victory_thresholds)[local_3c]);
        gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,local_6c,advisor_client_width);
        local_6c += local_10;
      }
      local_6c += 6;
      text_set_colors(0x7a,0x12,1,1);
      text_set_font(ADDR(0x63eac0, ((u8 *)&g.d_0063eac0)));
      local_10 = font_line_spacing((GameFont *)&advisor_font);
      text_clear();
      iVar1 = civ_get_adjective(civ2);
      text_append(iVar1);
      text_append_space();
      text_append_label(score_objective_outcome + 0x1b3);
      gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,local_6c,advisor_client_width);
      local_6c = local_6c + local_10 + 6;
    }
    local_1c = 0;
    local_48 = 0;
    if (((game.game_flags & 0x80) != 0) && ((scenario_flags & 2) != 0)) {
      score_conquest_bonus = -1;
      score_total = score_scenario_points;
      local_1c = 1;
    }
    while( true ) {
      text_set_font(ADDR(0x63eac0, ((u8 *)&g.d_0063eac0)));
      text_clear();
      if (score_total < score_conquest_bonus) {
        text_append_label(0x198);
        text_append_colon();
        text_append_int(score_conquest_bonus);
      }
      else {
        text_append_label(0x197);
        text_append_colon();
        text_append_int(score_total);
      }
      if (local_1c == 1) {
        iVar3 = font_text_width((GameFont *)&advisor_font,ADDR(0x679640, ((u8 *)&g.d_00679640)));
        local_48 += iVar3;
      }
      else {
        text_set_colors(0x25,0x12,1,1);
        local_34 = gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_60,local_6c);
      }
      if ((game.game_flags & 0x80) != 0) {
        local_34 += 0x19;
        text_set_colors(0x7a,0x12,0xffffffff,0xffffffff);
        text_clear();
        text_append_label(0x1a2);
        if (local_1c == 1) {
          iVar3 = font_text_width((GameFont *)&advisor_font,ADDR(0x679640, ((u8 *)&g.d_00679640)));
          local_48 = local_48 + iVar3 + 0x19;
        }
        else {
          local_34 = gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_34,local_6c);
        }
      }
      local_34 += 0x19;
      if ((game.game_flags & 0x10) != 0) {
        text_set_colors(0x6a,0x12,0xffffffff,0xffffffff);
        text_clear();
        text_append_label(0x19a);
        if (local_1c == 1) {
          iVar3 = font_text_width((GameFont *)&advisor_font,ADDR(0x679640, ((u8 *)&g.d_00679640)));
          local_48 = local_48 + iVar3 + 0x19;
        }
        else {
          gfx_draw_text(ADDR(0x679640, ((u8 *)&g.d_00679640)),local_34,local_6c);
        }
      }
      if (local_1c != 1) break;
      local_60 = ((advisor_client_width >> 1) + advisor_client_x) - (local_48 >> 1);
      local_1c = 2;
    }
  }
  else {
    local_5c = advisor_list_top_i32;
    text_clear();
    text_append_label(0x1c9);
    gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,local_5c,advisor_client_width);
  }
  wnd_blit_surface((DibSurface *)&advisor_window);
  return;
}
#undef advisor_client_width
#undef advisor_client_x
#undef advisor_row_height
#undef city_angry_count
#undef city_happy_count
#undef city_specialist_count
#undef city_unhappy_count
#undef scenario_flags
#undef scenario_objective_civ
#undef scenario_victory_thresholds
#undef score_citizens
#undef score_civ_objective_value
#undef score_objective_civ_value
#undef score_total_objective_value
#undef score_wonders
#undef advisor_list_top_i32
#undef advisor_list_height_i32
#undef local_90
#undef local_80
#undef civ
#undef local_6c
#undef local_68
#undef local_64
#undef local_60
#undef local_5c
#undef local_58
#undef city
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
#undef civ2
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 00435d15 auto */
#define advisor_modal_start_ticks_i32 (*(i32 *)((u8 *)&g.d_00625ec0))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl civ_score_window_show(iptr param_1)

{
  picwnd_open((PictureWindow *)&advisor_window,10,10,1,600,400,0,0);
  advisor_report_civ = param_1;
  advisor_add_close_button((ViewWindow *)&advisor_window);
  wnd_set_redraw_callback((SurfaceWindow *)&advisor_window,ADDR(0x402428, civ_score_window_draw));
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

/* 00435dc4 auto */
#define advisor_client_width (*(i32 *)((u8 *)&g.d_0063ec3c))
#define advisor_client_x (*(i32 *)((u8 *)&g.d_0063ec34))
#define advisor_row_height (*(int *)((u8 *)&g.d_0063ef80))
#define civ_rating_percent (*(int *)((u8 *)&g.d_0063ea18))
#define civ_rating_title_index (*(int *)((u8 *)&g.d_0063e4ec))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define advisor_list_top_i32 (*(i32 *)((u8 *)&g.d_0063ef78))
#define advisor_list_height_i32 (*(i32 *)((u8 *)&g.d_0063ef7c))
#define local_80 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_74 (*(int *)(frame_ + FRAME_OFF(12)))
#define local_68 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_64 (*(int *)(frame_ + FRAME_OFF(28)))
#define local_60 (*(i8 (*)[80])(frame_ + FRAME_OFF(32)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(112)))
#define local_c (*(int *)(frame_ + FRAME_OFF(116)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(120)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl civ_rating_window_draw(void)

{
  int iVar2;
  int iVar3;
  iptr iVar4;
  iptr civ;
  i8 frame_[FRAME_OFF(128)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ = advisor_report_civ;
  frame_wnd_layout((FrameWindow *)&advisor_window);
  frame_wnd_draw_caption((FrameWindow *)&advisor_window);
  picwnd_blit((PictureWindow *)&advisor_window);
  iVar2 = advisor_client_y + 1;
  local_80 = advisor_client_y + 0x174;
  local_10 = font_line_spacing((GameFont *)&advisor_font);
  local_10 -= 3;
  local_68 = game.difficulty + 4;
  if (2 < game.difficulty) {
    local_68 = game.difficulty + 5;
  }
  if (3 < game.difficulty) {
    local_68++;
  }
  if (4 < game.difficulty) {
    local_68 += 2;
  }
  local_8 = score_total;
  if (score_total <= score_conquest_bonus) {
    local_8 = score_conquest_bonus;
  }
  iVar3 = (local_68 * local_8) / 100;
  local_74 = 0;
  for (local_64 = 1; local_64 < 0x19; local_64++) {
    if ((local_64 * local_64) / 3 <= iVar3) {
      local_74 = local_64 - 1;
    }
  }
  if (0x17 < local_74) {
    local_74 = 0x17;
  }
  civ_rating_title_index = local_74;
  civ_rating_percent = iVar3;
  text_set_surface(ADDR(0x63eb10, ((u8 *)&g.d_0063eb10)));
  text_set_font(ADDR(0x63eac0, ((u8 *)&g.d_0063eac0)));
  text_set_colors(0x25,0x12,2,1);
  text_clear();
  iVar4 = label_string(*(i32 *)(label_string_ids + 0x670));
  text_append(iVar4);
  text_append_colon();
  text_append_int(iVar3);
  text_append(ADDR(0x6260b4, ((u8 *)&g.d_006260b4)));
  gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,iVar2,advisor_client_width);
  iVar2 += local_10;
  text_clear();
  text_append_label(0x19d);
  gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,iVar2,advisor_client_width);
  iVar2 += local_10;
  text_clear();
  text_append_label(0x19e);
  gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,iVar2,advisor_client_width);
  advisor_list_top_i32 = iVar2 + local_10 + 4;
  advisor_row_height = local_10;
  advisor_list_height_i32 = local_80 - advisor_list_top_i32;
  if (leaders[civs[civ].tribe].female == '\0') {
    crt_strcpy(local_60,s_MALEFAME_006260c4);
  }
  else {
    crt_strcpy(local_60,s_FEMALEFAME_006260b8);
  }
  local_c = text_open_section(ADDR(0x6558e8, ((u8 *)&g.d_006558e8)),(iptr)local_60);
  iVar4 = civ_leader_name(civ);
  text_set_string_arg(0,iVar4);
  for (local_64 = 0; local_64 <= local_74; local_64++) {
    if (local_c == 0) {
      text_read_line(1);
      crt_strcpy(local_60,&text_buffer);
    }
    else if (local_74 == local_64) {
      crt_strcpy(local_60,s__STRING0_006260d0);
    }
    else {
      crt_strcpy(local_60,s_Error_006260dc);
    }
    text_expand_vars((iptr)local_60,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    if (local_64 < local_74) {
      text_set_font(ADDR(0x63e4e0, ((u8 *)&g.d_0063e4e0)));
      text_set_colors(0x1d,0x12,0xffffffff,0xffffffff);
      local_10 = font_line_spacing((GameFont *)&civ_rating_title_font);
      local_10 -= 3;
    }
    else {
      text_set_font(ADDR(0x63eac0, ((u8 *)&g.d_0063eac0)));
      local_10 = font_line_spacing((GameFont *)&advisor_font);
      local_10 -= 4;
      text_set_colors(0x25,0x12,0xffffffff,0xffffffff);
    }
    local_80 -= local_10;
    gfx_draw_text_centered(ADDR(0x679640, ((u8 *)&g.d_00679640)),advisor_client_x,local_80,advisor_client_width);
  }
  wnd_blit_surface((DibSurface *)&advisor_window);
  return;
}
#undef advisor_client_width
#undef advisor_client_x
#undef advisor_row_height
#undef civ_rating_percent
#undef civ_rating_title_index
#undef text_buffer
#undef advisor_list_top_i32
#undef advisor_list_height_i32
#undef local_80
#undef local_74
#undef local_68
#undef local_64
#undef local_60
#undef local_10
#undef local_c
#undef local_8

/* 004361cc auto */
#define advisor_modal_start_ticks_i32 (*(i32 *)((u8 *)&g.d_00625ec0))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl civ_rating_window_show(iptr param_1)

{
  picwnd_open((PictureWindow *)&advisor_window,10,10,1,600,400,0,0);
  advisor_report_civ = param_1;
  advisor_add_close_button((ViewWindow *)&advisor_window);
  wnd_set_redraw_callback((SurfaceWindow *)&advisor_window,ADDR(0x402432, civ_rating_window_draw));
  wnd_repaint((SurfaceWindow *)&advisor_window);
  music_play_track(3,0);
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

/* 0043cab0 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
i32 __cdecl civ_color_primary(iptr civ)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (civ == 0) {
    local_8 = 0;
  }
  else {
    local_8 = (int)leaders[civs[civ].tribe].color;
  }
  return *(i32 *)(&civ_primary_colors + local_8 * 0x10);
}
#undef local_8

/* 0043cb30 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
i32 __cdecl civ_color_secondary(iptr civ)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (civ == 0) {
    local_8 = 0;
  }
  else {
    local_8 = (int)leaders[civs[civ].tribe].color;
  }
  return *(i32 *)(&civ_secondary_colors + local_8 * 0x10);
}
#undef local_8

/* 0043cce5 auto */
#define city (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
int __cdecl civ_total_population(iptr civ)

{
  int iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  for (city = 0; city < game.num_cities; city++) {
    if ((cities[city].id != 0) && (cities[city].owner == civ)) {
      iVar1 = city_population_units(city);
      local_8 += iVar1;
    }
  }
  if ((local_8 < 0) || (32000 < local_8)) {
    local_8 = 32000;
  }
  if (local_8 < 2) {
    local_8 = 1;
  }
  return local_8;
}
#undef city
#undef local_8

/* 00442541 auto */
#define hotseat_human_players (*(byte *)((u8 *)&g.d_006c31a9))
#define city (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl civ_reset_city_production(uptr param_1,iptr param_2)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((game.multiplayer != 1) || ((1 << ((byte)param_1 & 0x1f) & (uint)hotseat_human_players) == 0)) {
    for (city = 0; city < game.num_cities; city++) {
      if (((cities[city].id != 0) && ((int)cities[city].owner == (param_1 & 0xff))) &&
         ((param_2 < 0 ||
          (iVar1 = tile_landmass((int)cities[city].x,(int)cities[city].y), iVar1 == param_2)))
         ) {
        city_set_production(city,99);
      }
    }
  }
  return;
}
#undef hotseat_human_players
#undef city

/* 004481f0 auto */
void __cdecl civ_flag_sprites_global_init(void)

{
  civ_flag_sprites_static_init();
  civ_flag_sprites_reg_atexit();
  return;
}

/* 0044820a auto */
void __cdecl civ_flag_sprites_static_init(void)

{
  crt_vector_ctor_iterator(&civ_flag_sprites,0x3c,0x10,sprite_init,sprite_destroy);
  return;
}

/* 00448232 auto */
void __cdecl civ_flag_sprites_reg_atexit(void)

{
  _atexit(civ_flag_sprites_static_dtor);
  return;
}

/* 0044824f auto */
void __cdecl civ_flag_sprites_static_dtor(void)

{
  crt_vector_dtor_iterator(&civ_flag_sprites,0x3c,0x10,sprite_destroy);
  return;
}

/* 00448758 auto */
void __cdecl research_flask_sprites_global_init(void)

{
  research_flask_sprites_static_init();
  research_flask_sprites_reg_atexit();
  return;
}

/* 00448772 auto */
void __cdecl research_flask_sprites_static_init(void)

{
  crt_vector_ctor_iterator(&research_flask_sprites,0x3c,4,sprite_init,sprite_destroy);
  return;
}

/* 0044879a auto */
void __cdecl research_flask_sprites_reg_atexit(void)

{
  _atexit(research_flask_sprites_static_dtor);
  return;
}

/* 004487b7 auto */
void __cdecl research_flask_sprites_static_dtor(void)

{
  crt_vector_dtor_iterator(&research_flask_sprites,0x3c,4,sprite_destroy);
  return;
}

/* 004487da auto */
void __cdecl global_warming_sprites_global_init(void)

{
  global_warming_sprites_static_init();
  global_warming_sprites_reg_atexit();
  return;
}

/* 004487f4 auto */
void __cdecl global_warming_sprites_static_init(void)

{
  crt_vector_ctor_iterator(&global_warming_sprites,0x3c,4,sprite_init,sprite_destroy);
  return;
}

/* 0044881c auto */
void __cdecl global_warming_sprites_reg_atexit(void)

{
  _atexit(global_warming_sprites_static_dtor);
  return;
}

/* 00448839 auto */
void __cdecl global_warming_sprites_static_dtor(void)

{
  crt_vector_dtor_iterator(&global_warming_sprites,0x3c,4,sprite_destroy);
  return;
}

/* 004489cb auto */
void __cdecl advance_cat_icon_sprites_global_init(void)

{
  advance_category_icon_sprites_static_init();
  advance_category_icon_sprites_reg_atexit();
  return;
}

/* 004489e5 auto */
void __cdecl advance_category_icon_sprites_static_init(void)

{
  crt_vector_ctor_iterator(&advance_category_icon_sprites,0x3c,0x14,sprite_init,sprite_destroy);
  return;
}

/* 00448a0d auto */
void __cdecl advance_category_icon_sprites_reg_atexit(void)

{
  _atexit(advance_cat_icon_sprites_static_dtor);
  return;
}

/* 00448a2a auto */
void __cdecl advance_cat_icon_sprites_static_dtor(void)

{
  crt_vector_dtor_iterator(&advance_category_icon_sprites,0x3c,0x14,sprite_destroy);
  return;
}

/* 00448bbc auto */
void __cdecl government_sprites_global_init(void)

{
  government_sprites_static_init();
  government_sprites_reg_atexit();
  return;
}

/* 00448bd6 auto */
void __cdecl government_sprites_static_init(void)

{
  crt_vector_ctor_iterator(&government_sprites,0x3c,7,sprite_init,sprite_destroy);
  return;
}

/* 00448bfe auto */
void __cdecl government_sprites_reg_atexit(void)

{
  _atexit(government_sprites_static_dtor);
  return;
}

/* 00448c1b auto */
void __cdecl government_sprites_static_dtor(void)

{
  crt_vector_dtor_iterator(&government_sprites,0x3c,7,sprite_destroy);
  return;
}

/* 00448c3e auto */
void __cdecl civ_portrait_sprites_global_init(void)

{
  civ_portrait_sprites_static_init();
  civ_portrait_sprites_reg_atexit();
  return;
}

/* 00448c58 auto */
void __cdecl civ_portrait_sprites_static_init(void)

{
  crt_vector_ctor_iterator(&civ_portrait_sprites,0x3c,8,sprite_init,sprite_destroy);
  return;
}

/* 00448c80 auto */
void __cdecl civ_portrait_sprites_reg_atexit(void)

{
  _atexit(civ_portrait_sprites_static_dtor);
  return;
}

/* 00448c9d auto */
void __cdecl civ_portrait_sprites_static_dtor(void)

{
  crt_vector_dtor_iterator(&civ_portrait_sprites,0x3c,8,sprite_destroy);
  return;
}

/* 00448f92 auto */
i32 __cdecl civ_city_style_era(iptr civ)

{
  int iVar1;
  i32 uVar2;
  
  iVar1 = civ_has_advance(civ,0x18);
  if ((iVar1 != 0) && (iVar1 = civ_has_advance(civ,5), iVar1 != 0)) {
    return 3;
  }
  iVar1 = civ_has_advance(civ,0x25);
  if (iVar1 == 0) {
    iVar1 = civ_has_advance(civ,0x26);
    if ((iVar1 != 0) && (iVar1 = civ_has_advance(civ,0x3c), iVar1 != 0)) {
      return 1;
    }
    uVar2 = 0;
  }
  else {
    uVar2 = 2;
  }
  return uVar2;
}

/* 00453e51 auto */
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
i32 __cdecl civ_has_wonder(iptr civ,iptr param_2)

{
  i32 uVar1;
  iptr city;
  
  if (((param_2 == 0x14) && ((game.game_flags & 0x80) != 0)) && ((scenario_flags & 1) != 0)) {
    uVar1 = 0;
  }
  else {
    city = wonder_get_city(param_2);
    if (city < 0) {
      uVar1 = 0;
    }
    else if (cities[city].owner == (char)civ) {
      uVar1 = 1;
    }
    else {
      uVar1 = 0;
    }
  }
  return uVar1;
}
#undef scenario_flags

/* 00456f20 auto */
#define diplo_attitude_civ (*(int *)((u8 *)&g.d_0064b110))
#define diplo_attitude_target (*(int *)((u8 *)&g.d_0064b120))
#define diplo_cur_attitude (*(int *)((u8 *)&g.d_0064b114))
void __cdecl civ_adjust_attitude(iptr civ,iptr param_2,int param_3)

{
  int iVar1;
  
  iVar1 = civ_get_attitude(civ,param_2);
  civ_set_attitude(civ,param_2,param_3 + iVar1);
  if ((civ == diplo_attitude_civ) && (param_2 == diplo_attitude_target)) {
    diplo_cur_attitude += param_3;
  }
  civ_get_attitude(civ,param_2);
  return;
}
#undef diplo_attitude_civ
#undef diplo_attitude_target
#undef diplo_cur_attitude

/* 00467904 auto */
uint __cdecl civ_get_attitude(iptr civ,iptr param_2)

{
  return (uint)civs[civ].attitude[param_2];
}

/* 00467933 auto */
#define hotseat_human_players (*(byte *)((u8 *)&g.d_006c31a9))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
void __cdecl civ_set_attitude(iptr civ,iptr param_2,iptr param_3)

{
  i32 uVar1;
  
  if (((game.multiplayer != 1) || ((1 << ((byte)civ & 0x1f) & (uint)hotseat_human_players) == 0)) ||
     (human_civ == civ)) {
    uVar1 = int_clamp(param_3,0,100);
    *(char *)&civs[civ].attitude[param_2] = (char)uVar1;
  }
  return;
}
#undef hotseat_human_players
#undef human_civ

/* 004853e7 auto */
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
#define civ (*(uptr *)(frame_ + FRAME_OFF(0)))
#define local_4c (*(int *)(frame_ + FRAME_OFF(4)))
#define aiStack_48 (*(int (*)[8])(frame_ + FRAME_OFF(8)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(40)))
#define city (*(iptr *)(frame_ + FRAME_OFF(44)))
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(48)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(52)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(56)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(60)))
#define civ2 (*(uptr *)(frame_ + FRAME_OFF(64)))
#define local_c (*(int *)(frame_ + FRAME_OFF(68)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(72)))
void __cdecl civ_update_power_ranks(void)

{
  uint *puVar1;
  int iVar2;
  i32 uVar3;
  uint uVar4;
  uint uVar5;
  uptr uVar2;
  i8 frame_[FRAME_OFF(80)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (civ = 1; (int)civ < 8; civ++) {
    if ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) == 0) {
      aiStack_48[civ] = 0;
    }
    else if (((game.game_flags & 0x80) == 0) || ((scenario_flags & 2) == 0)) {
      aiStack_48[civ] =
           (uint)civs[civ].num_advances * 3 + civs[civ].total_city_size * 8 +
           (civs[civ].gold >> 5);
      local_c = 0;
      for (unit_type = 0; unit_type < 0x3e; unit_type++) {
        if ((char)unit_types[unit_type].role < 5) {
          if (unit_types[unit_type].domain == '\0') {
            local_18 = ((char)unit_types[unit_type].hit_points + 1 +
                       (int)(char)unit_types[unit_type].firepower) / 2;
          }
          else {
            local_18 = 1;
          }
          local_4c = (char)unit_types[unit_type].attack * local_18 +
                     (int)(char)unit_types[unit_type].defense >> 1;
        }
        else {
          local_4c = ((char)unit_types[unit_type].cost + 1) / 2;
        }
        local_c += (uint)civs[civ].units_active[unit_type] * local_4c;
      }
    }
    else {
      aiStack_48[civ] = 0;
      for (city = 0; city < game.num_cities; city++) {
        if ((cities[city].id != 0) && ((int)cities[city].owner == civ)) {
          iVar2 = city_objective_value(city);
          aiStack_48[civ] += iVar2 * 2;
        }
      }
    }
    if (((game.game_flags & 0x80) == 0) || ((scenario_flags & 2) == 0)) {
      if (game.turn < 600) {
        uVar3 = int_clamp(aiStack_48[civ] >> 3,0,0xff);
        (&power_graph_history)
        [(int)(CONCAT44((int)game.turn >> 0x1f,(int)game.turn >> 2) % 0x96) * 8 + civ] =
             (char)uVar3;
      }
    }
    else if (game.turn < 0x4b) {
      uVar3 = int_clamp(aiStack_48[civ],0,0xff);
      (&power_graph_history)
      [(int)(CONCAT44((int)game.turn >> 0x1f,(int)game.turn >> 1) % 0x96) * 8 + civ] =
           (char)uVar3;
    }
  }
  for (local_28 = 1; local_28 < 8; local_28++) {
    local_8 = -1;
    civ = 0;
    for (civ2 = 1; (int)civ2 < 8; civ2++) {
      if (local_8 < aiStack_48[civ2]) {
        civ = civ2;
        local_8 = aiStack_48[civ2];
      }
    }
    game.power_rank[civ] = 8 - (char)local_28;
    aiStack_48[civ] = -1;
  }
  game.game_flags = game.game_flags & 0xfffe;
  for (civ = 0; (int)civ < 8; civ++) {
    game.civ_by_rank[civ] = '\0';
  }
  for (civ = 1; (int)civ < 8; civ++) {
    if ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0) {
      game.civ_by_rank[game.power_rank[civ]] = (byte)civ;
    }
  }
  game.field_138 = '\0';
  game.field_139 = '\0';
  for (civ = 7; -1 < (int)civ; civ--) {
    if (((uint)game.human_players & 1 << (game.civ_by_rank[civ] & 0x1f)) != 0) {
      game.field_138 = (byte)civ;
      break;
    }
  }
  civ = 0;
  do {
    if (7 < (int)civ) {
LAB_00485891:
      local_1c = 0;
      civ = (uptr)game.civ_by_rank[7];
      if ((((((uint)game.human_players & 1 << (game.civ_by_rank[7] & 0x1f)) != 0) &&
           (4 < civs[game.civ_by_rank[7]].num_cities)) &&
          (civs[game.civ_by_rank[7]].units_active[0x2d] == '\0')) &&
         ((200 < game.turn && (game.difficulty != '\0')))) {
        local_1c = 1;
      }
      if (3 < game.difficulty) {
        for (civ2 = 1; (int)civ2 < 8; civ2++) {
          if (((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) &&
             (iVar2 = civ_spaceship_launched(civ2), iVar2 != 0)) {
            civ = civ2;
            local_1c = 1;
          }
        }
      }
      uVar2 = civ;
      if (local_1c != 0) {
        game.game_flags = game.game_flags | 1;
        civ2 = civ;
        local_14 = 0;
        for (civ = 1; (int)civ < 8; civ++) {
          if ((*(byte *)(uVar2 * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ * 4) & 0x20) != 0) {
            local_14++;
          }
        }
        for (civ = 1; (int)civ < 8; civ++) {
          if (((((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0) &&
               ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0)) &&
              (1 < civs[civ].num_cities)) &&
             (((local_14 * 3 + 3 < (int)(uint)civs[civ2].reputation ||
               ((*(byte *)&civs[civ].treaties[civ2] & 0x10) != 0)) ||
              (iVar2 = spaceship_race_active(), iVar2 != 0)))) {
            if ((*(byte *)&civs[civ].treaties[civ2] & 8) == 0) {
              if ((*(byte *)&civs[civ].treaties[civ2] & 6) == 0) {
                civ_adjust_attitude(civ,civ2,1);
                puVar1 = (uint *)(civ2 * 4 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ * 0x594);
                *puVar1 = *puVar1 | 1;
              }
              else {
                uVar4 = _rand();
                uVar5 = (int)uVar4 >> 0x1f;
                if (((int)(((uVar4 ^ uVar5) - uVar5 & 0x1f ^ uVar5) - uVar5) <=
                     (int)(uint)game.difficulty) ||
                   (iVar2 = civ_spaceship_launched(civ), iVar2 != 0)) {
                  puVar1 = (uint *)(civ2 * 4 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ * 0x594);
                  *puVar1 = *puVar1 | 0x20;
                }
              }
            }
            else {
              iVar2 = civ_spaceship_launched(civ);
              if ((iVar2 != 0) && (3 < game.difficulty)) {
                puVar1 = (uint *)(civ2 * 4 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ * 0x594);
                *puVar1 = *puVar1 | 0x20;
              }
            }
          }
        }
      }
      return;
    }
    if (((uint)game.human_players & 1 << (game.civ_by_rank[civ] & 0x1f)) != 0) {
      game.field_139 = (byte)civ;
      goto LAB_00485891;
    }
    civ++;
  } while( true );
}
#undef scenario_flags
#undef civ
#undef local_4c
#undef aiStack_48
#undef local_28
#undef city
#undef unit_type
#undef local_1c
#undef local_18
#undef local_14
#undef civ2
#undef local_c
#undef local_8

/* 00486e15 auto */
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
int __cdecl civ_throne_upgrade_threshold(int param_1)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  for (local_c = 0; local_c <= param_1; local_c++) {
    local_8 += (7 - (uint)game.difficulty) * local_c;
  }
  return local_8 / 2 + 1;
}
#undef local_c
#undef local_8

/* 00486e6f auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define prefs_accelerated_start (*(short *)((u8 *)&g.d_0064bc56))
#define city (*(iptr *)(frame_ + FRAME_OFF(4)))
void __cdecl civ_check_throne_room_upgrade(void)

{
  bool bVar1;
  int iVar3;
  int iVar4;
  iptr civ;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  civ = human_civ;
  if (((game.game_flags & 0x80) == 0) && (game.multiplayer != 1)) {
    bVar1 = false;
    for (city = 0; city < game.num_cities; city++) {
      if (((cities[city].id != 0) && (cities[city].owner == civ)) &&
         (iVar3 = city_has_improvement(city,1), iVar3 != 0)) {
        bVar1 = true;
        break;
      }
    }
    if ((bVar1) && (prefs_accelerated_start * 0x14 + 1 < (int)game.turn)) {
      iVar3 = civ_calc_score(civ);
      iVar4 = civ_throne_upgrade_threshold(civs[civ].throne_room_upgrades + 1);
      if ((iVar4 <= iVar3) &&
         ((civs[civ].throne_room_upgrades = civs[civ].throne_room_upgrades + 1,
          civs[civ].throne_room_upgrades < 0x26 && (((*(i8 *)((char *)&game.game_options + 2)) & 2) != 0)))) {
        throneroom_show_upgrade(human_civ);
      }
    }
  }
  return;
}
#undef human_civ
#undef prefs_accelerated_start
#undef city

/* 00487a41 auto */
#define city_zoom_requested (*(int *)((u8 *)&g.d_006a65a0))
#define local_38 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_2c (*(iptr *)(frame_ + FRAME_OFF(12)))
#define city (*(iptr *)(frame_ + FRAME_OFF(20)))
#define local_20 (*(iptr *)(frame_ + FRAME_OFF(24)))
#define local_1c (*(uint *)(frame_ + FRAME_OFF(28)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_14 (*(iptr *)(frame_ + FRAME_OFF(36)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_c (*(int *)(frame_ + FRAME_OFF(44)))
void __cdecl civ_process_cities_turn(uptr civ)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  i32 uVar4;
  int iVar5;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_1c = 0;
  civs[civ].field_3d2 = 0;
  for (local_38 = 0; local_38 < 7; local_38++) {
    civs[civ].government_score[local_38] = 0;
  }
  for (local_14 = 0; local_14 < 0x1c; local_14++) {
    (&wonder_notice_flags)[civ * 0x1c + local_14] = 0;
  }
  game.field_06 = game.field_06 & 0xfffb;
  city_window_begin_notice((WindowObjectView *)&city_window);
  city = (iptr)game.num_cities;
  while( true ) {
    city--;
    if (city < 0) break;
    if (2 < game.multiplayer) {
      net_process_messages((NetSession *)&net_session,1,0);
    }
    if ((cities[city].id != 0) && ((int)cities[city].owner == (civ & 0xff))) {
      cities[city].flags = cities[city].flags & 0xfffeffff;
      iVar3 = city_process_turn(city);
      if (iVar3 != -999) {
        if ((iVar3 == 0) && (5 < cities[city].size)) {
          local_1c = local_1c | 1;
        }
        if ((cities[city].flags & 1) != 0) {
          local_1c = local_1c | 2;
        }
        for (local_2c = 1; local_2c < 8; local_2c++) {
          if (((*(byte *)&civs[civ].treaties[local_2c] & 8) != 0) ||
             (game.wonder_city[0x19] != -1)) {
            *(i8 *)&cities[city].revealed_size[local_2c] = cities[city].size;
          }
        }
        iVar3 = citywnd_get_city((WindowObjectView *)&city_window);
        if ((iVar3 == city) && (city_zoom_requested == 0)) {
          city_window_refresh((FrameWindow *)&city_window);
        }
      }
    }
  }
  city_window_end_notice((ScaledWindowView *)&city_window);
  civs[civ].government_score[0] =
       civs[civ].government_score[0] + civs[civ].government_score[1] * 2;
  if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
    iVar3 = -((uint)civs[civ].science_rate + (uint)civs[civ].tax_rate);
    local_18 = iVar3 + 10;
    if (((local_1c & 2) != 0) && (local_18 < 4)) {
      local_18 = iVar3 + 0xb;
    }
    if ((((game.turn & 3U) == 0) && (local_1c == 0)) && (2 < local_18)) {
      local_18--;
    }
    iVar3 = int_clamp(local_18,0,4);
    civs[civ].science_rate = leaders[civs[civ].tribe].civilize + (char)(10 - iVar3 >> 1);
    if (game.turn + 100 < civs[civ].gold) {
      civs[civ].science_rate++;
    }
    if (2000 < civs[civ].gold) {
      civs[civ].science_rate++;
    }
    if (8000 < civs[civ].gold) {
      civs[civ].science_rate = '\n' - (char)iVar3;
    }
    bVar2 = false;
    for (local_20 = 1; local_20 < 0x40; local_20++) {
      if (*(char *)&civs[civ].continent_cities[local_20] != '\0') {
        if ((*(char *)&civs[civ].continent_policy[local_20] == '\0') ||
           (*(char *)&civs[civ].continent_policy[local_20] == 1)) {
          bVar2 = true;
        }
        if ((*(char *)&civs[civ].continent_policy[local_20] == 5) &&
           (*(char *)&civs[civ].continent_flags[local_20] != '\0')) {
          bVar2 = true;
        }
      }
    }
    if ((!bVar2) && (civs[civ].science_rate < 7)) {
      civs[civ].science_rate++;
    }
    local_10 = 6;
    if (1 < civs[civ].government) {
      local_10 = 7;
    }
    if (4 < civs[civ].government) {
      local_10 = 8;
    }
    if (5 < civs[civ].government) {
      local_10 = 10;
    }
    iVar5 = 10 - iVar3;
    if (local_10 <= 10 - iVar3) {
      iVar5 = local_10;
    }
    uVar4 = int_clamp((uint)civs[civ].science_rate,0,iVar5);
    civs[civ].science_rate = (u8)uVar4;
    iVar5 = civ_has_advance(civ,0x20);
    if ((((iVar5 != 0) && (iVar5 = civ_has_advance(civ,0x29), iVar5 != 0)) &&
        (iVar5 = civ_has_advance(civ,(int)improvements[0x23].preq), iVar5 != 0)) &&
       ((iVar5 = civ_has_advance(civ,(int)improvements[0x24].preq), iVar5 != 0 &&
        (iVar5 = civ_has_advance(civ,(int)improvements[0x25].preq), iVar5 != 0)))) {
      civs[civ].science_rate = '\0';
    }
    civs[civ].tax_rate = '\n' - (civs[civ].science_rate + (char)iVar3);
  }
  local_c = 0;
  iVar3 = civ_has_advance(civ,0x15);
  if (((iVar3 != 0) || (iVar3 = civ_has_wonder(civ,0x13), iVar3 != 0)) &&
     (civs[game.field_138].government == 4)) {
    local_c = civs[game.field_138].field_1c + 1;
  }
  civs[civ].government_score[6] =
       ((ushort)civs[game.field_138].units_active[0x2e] +
        (ushort)civs[game.field_138].units_active[0x2f] + civs[game.field_138].field_1c) *
       (civs[game.field_138].field_1c + (short)local_c) + civs[civ].government_score[6];
  if (civs[civ].gold < civs[game.field_138].gold) {
    civs[civ].government_score[6] += 10;
  }
  if ((local_c == 0) &&
     ((((iVar3 = civ_has_advance(civ,0xf), iVar3 != 0 ||
        (iVar3 = civ_has_advance(civ,0x1f), iVar3 != 0)) ||
       (iVar3 = civ_has_wonder(civ,0x13), iVar3 != 0)) &&
      ((cVar1 = leaders[civs[civ].tribe].attack, iVar3 = spaceship_race_active(),
       (int)(uint)game.power_rank[civ] <= (int)((int)cVar1 + (4 - (uint)(iVar3 == 0))) &&
       (civs[civ].num_advances < civs[game.field_138].num_advances)))))) {
    civs[civ].government_score[6] = 0;
    civs[civ].government_score[5] = 0;
  }
  if (-1 < leaders[civs[civ].tribe].attack) {
    if ((((uint)game.human_players & 1 << (game.civ_by_rank[7] & 0x1f)) == 0) &&
       ((leaders[civs[civ].tribe].attack == 1 ||
        ((leaders[civs[civ].tribe].attack == '\0' &&
         (leaders[civs[civ].tribe].civilize < '\0')))))) {
      iVar3 = civs[civ].government_score[6] * 3;
      civs[civ].government_score[6] = (i16)((int)(iVar3 + (iVar3 >> 0x1f & 3U)) >> 2);
      iVar3 = civs[civ].government_score[5] * 3;
      civs[civ].government_score[5] = (i16)((int)(iVar3 + (iVar3 >> 0x1f & 3U)) >> 2);
    }
    if ((leaders[civs[civ].tribe].attack != '\0') ||
       ((leaders[civs[civ].tribe].civilize < '\0' && (local_c == 0)))) {
      iVar3 = leaders[civs[civ].tribe].attack * 2 - (int)leaders[civs[civ].tribe].civilize;
      if (((int)(game.power_rank[game.field_138] - 1) <= (int)(uint)game.power_rank[civ]) ||
         (civs[game.field_138].num_advances <= civs[civ].num_advances)) {
        if ((int)((uint)civs[civ].num_advances + iVar3 * 4) <
            (int)(uint)civs[game.field_138].num_advances) {
          if ((int)(uint)civs[game.field_138].num_advances <=
              (int)((uint)civs[civ].num_advances + iVar3 * 8)) {
            civs[civ].government_score[6] = civs[civ].government_score[6] / 2;
            civs[civ].government_score[5] = civs[civ].government_score[5] / 2;
          }
        }
        else {
          civs[civ].government_score[6] = 0;
          civs[civ].government_score[5] = 0;
        }
      }
    }
  }
  iVar3 = civ_spaceship_launched(civ);
  if ((iVar3 != 0) && (3 < game.difficulty)) {
    civs[civ].government_score[6] = civs[civ].government_score[6] / 2;
    civs[civ].government_score[5] = civs[civ].government_score[5] / 2;
  }
  if ((((game.rules & 0x80) != 0) && (civs[civ].science_rate == '\0')) &&
     (civs[civ].government_score[6] = 0, -1 < leaders[civs[civ].tribe].attack)) {
    civs[civ].government_score[5] = 0;
  }
  for (local_14 = 0; local_14 < 0x1c; local_14++) {
    (&wonder_notice_flags)[civ * 0x1c + local_14] = 0;
  }
  return;
}
#undef city_zoom_requested
#undef local_38
#undef local_2c
#undef city
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c

/* 00488cef auto */
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define unit (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(24)))
void __cdecl civ_heal_units(iptr civ)

{
  u8 uVar1;
  ushort uVar2;
  bool bVar3;
  uint uVar4;
  iptr iVar5;
  iptr iVar6;
  i32 uVar5;
  int city;
  int iVar8;
  iptr civ2;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (unit = 0; unit < game.num_units; unit++) {
    if (2 < game.multiplayer) {
      net_process_messages((NetSession *)&net_session,1,0);
    }
    if ((units[unit].id != 0) && (units[unit].owner == civ)) {
      uVar2 = units[unit].flags;
      units[unit].flags = units[unit].flags & 0xffaf;
      if ((uVar2 & 0x40) == 0) {
        if (units[unit].damage != '\0') {
          local_8 = 1;
          civ2 = -1;
          uVar5 = tile_landmass((int)units[unit].x,(int)units[unit].y);
          city = city_find_nearest((int)units[unit].x,(int)units[unit].y,civ,uVar5,
                                     civ2);
          if (-1 < city) {
            nearest_city_dist = map_distance((int)units[unit].x,(int)units[unit].y,
                                              (int)cities[city].x,(int)cities[city].y);
          }
          uVar5 = tile_improvements((int)units[unit].x,(int)units[unit].y);
          if (((byte)uVar5 & 0x42) == 0x40) {
            local_8 = 2;
          }
          bVar3 = false;
          uVar4 = local_8;
          if ((nearest_city_dist < 4) && (unit_types[units[unit].type].domain == '\0')) {
            iVar8 = city_has_improvement(city,2);
            uVar4 = local_8 + 1;
            if (iVar8 != 0) {
              uVar4 = local_8 + 2;
            }
          }
          local_8 = uVar4;
          if (nearest_city_dist == 0) {
            uVar1 = unit_types[units[unit].type].domain;
            if (uVar1 == '\0') {
              local_18 = 2;
            }
            else if (uVar1 == 1) {
              local_18 = 0x20;
            }
            else if (uVar1 == 2) {
              local_18 = 0x22;
            }
            city = city_has_improvement(city,local_18);
            if ((city != 0) &&
               ((unit_types[units[unit].type].domain == '\0' || (nearest_city_dist == 0)))) {
              bVar3 = true;
              local_8 = local_8 << 1;
            }
          }
          if (nearest_city_dist == 0) {
            local_8 = local_8 << 1;
          }
          city = unit_max_hp(unit);
          local_8 = (city / 10) * local_8;
          if ((bVar3) && (nearest_city_dist == 0)) {
            local_8 = (uint)units[unit].damage;
          }
          if ((unit_types[units[unit].type].domain == 1) &&
             (city = tile_airbase_owner((int)units[unit].x,(int)units[unit].y), 0 < city))
          {
            local_8 = (uint)units[unit].damage;
          }
          uVar4 = (uint)units[unit].damage;
          if ((int)local_8 <= (int)(uint)units[unit].damage) {
            uVar4 = local_8;
          }
          units[unit].damage -= (char)uVar4;
          if (((units[unit].damage == '\0') && (units[unit].orders == 3)) &&
             ((unit_types[units[unit].type].domain != '\0' ||
              (city = tile_is_ocean((int)units[unit].x,(int)units[unit].y), city == 0))))
          {
            units[unit].orders = -1;
          }
          if (((human_civ == civ) ||
              ((1 << ((byte)human_civ & 0x1f) & (uint)units[unit].visibility) != 0)) ||
             ((int)units[unit].owner == (human_civ & 0xffU))) {
            map_redraw_tile_all_views((int)units[unit].x,(int)units[unit].y);
          }
        }
      }
      else if (((unit_types[units[unit].type].domain == 1) &&
               (unit_types[units[unit].type].range == '\0')) &&
              (uVar4 = tile_improvements((int)units[unit].x,(int)units[unit].y),
              (uVar4 & 2) == 0)) {
        iVar5 = unit_max_hp(unit);
        iVar6 = unit_max_hp(unit);
        uVar5 = int_clamp((uint)units[unit].damage + iVar5 / 10,0,iVar6 - 1);
        units[unit].damage = (u8)uVar5;
      }
    }
  }
  return;
}
#undef human_civ
#undef unit
#undef local_18
#undef local_8

/* 00489292 auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define game_loop_active (*(char *)((u8 *)&g.d_00628044))
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl civ_check_pop_and_funds(iptr civ,int param_2)

{
  short sVar1;
  int iVar2;
  iptr iVar3;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = -1;
  iVar2 = civ_total_population(civ);
  sVar1 = civs[civ].population_milestone;
  if (iVar2 < 100) {
    if (civs[civ].population_milestone * 10 < iVar2) {
      local_8 = (iVar2 / 10) * 10;
      civs[civ].population_milestone = (i16)(iVar2 / 10);
    }
  }
  else if ((civs[civ].population_milestone - 9) * 100 < iVar2) {
    local_8 = (iVar2 / 100) * 100;
    civs[civ].population_milestone = (short)(iVar2 / 100) + 9;
  }
  if (((sVar1 < civs[civ].population_milestone) &&
      ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) && (autoplay_active == 0)) {
    iVar3 = civ_get_adjective(civ);
    text_set_string_arg(1,iVar3);
    text_clear();
    text_append_population(civ,local_8);
    text_set_string_arg(2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    popup_game_with_sprite(ADDR(0x62c618, ((u8 *)&g.d_0062c618)),(iptr)(&civ_portrait_sprites + civ * 0x3c),0);
  }
  if ((((((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) && (autoplay_active == 0)) &&
       ((game_loop_active != '\0' && ((1 < civs[civ].num_cities && (civs[civ].gold < 100))))))
      && ((civs[civ].gold - param_2) * 10 + civs[civ].gold < 0)) &&
     (iVar2 = popup_game_with_sprite(ADDR(0x62c620, ((u8 *)&g.d_0062c620)),(iptr)(&civ_portrait_sprites + civ * 0x3c),0), iVar2 != 0)) {
    taxrate_dialog_show(civ);
  }
  return;
}
#undef autoplay_active
#undef game_loop_active
#undef local_8

/* 00489553 auto */
#define civ_turn_in_progress (*(i32 *)((u8 *)&g.d_0062c5b8))
#define local_10 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
void __cdecl civ_process_turn(uptr civ)

{
  i32 iVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 0;
  civ_turn_in_progress = 1;
  if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) {
    iVar2 = civ_spaceship_exists(civ);
    if (iVar2 != 0) {
      for (local_10 = 0; local_10 < 6; local_10++) {
        local_c += civs[civ].spaceship_parts[local_10];
      }
    }
  }
  spaceship_wnd_load_parts(civ);
  picwnd_close((PictureWindowCore *)&advisor_window);
  if (30000 < civs[civ].gold) {
    civs[civ].gold = 30000;
  }
  if (civs[civ].gold < -0x4000) {
    civs[civ].gold = 30000;
  }
  if (civs[civ].gold < 0) {
    civs[civ].gold = 0;
  }
  iVar1 = civs[civ].gold;
  civ_heal_units(civ);
  civ_process_cities_turn(civ);
  civ_turn_update_diplomacy(civ);
  ai_civ_turn_assess(civ);
  civ_check_pop_and_funds(civ,iVar1);
  if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) {
    iVar2 = civ_spaceship_exists(civ);
    if (iVar2 != 0) {
      for (local_10 = 0; local_10 < 6; local_10++) {
        local_c -= civs[civ].spaceship_parts[local_10];
      }
    }
  }
  if (local_c != 0) {
    iVar2 = spaceship_wnd_show_for_civ(civ);
    if (iVar2 == 0) {
      spaceship_status_dialog(civ,(uint)game.human_players & 1 << ((byte)civ & 0x1f));
    }
  }
  civ_turn_in_progress = 0;
  if (((*(i8 *)((char *)&game.game_options + 1)) & 0x20) != 0) {
    __chdir(&scenario_dir_path);
    game_autosave(civ);
    __chdir(&game_home_dir);
  }
  return;
}
#undef civ_turn_in_progress
#undef local_10
#undef local_c

/* 00492b60 auto */
void __cdecl civ_ai_goal_negate_priority(int civ,int param_2)

{
  char cVar1;
  
  if (civs[civ].ai_goals[param_2].priority < 1) {
    cVar1 = ~*(byte *)&civs[civ].ai_goals[param_2].priority + 1;
  }
  else {
    cVar1 = civs[civ].ai_goals[param_2].priority;
  }
  civs[civ].ai_goals[param_2].priority = -cVar1;
  return;
}

/* 00492c15 auto */
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
void __cdecl
civ_clear_standing_goals_near(iptr civ,i32 param_2,i32 param_3,i32 param_4,int param_5)

{
  int iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_c = 0; local_c < 0x10; local_c++) {
    if (civs[civ].ai_standing_goals[local_c].role == (char)param_2) {
      iVar1 = map_distance_diag(param_3,param_4,
                                 (int)civs[civ].ai_standing_goals[local_c].x,
                                 (int)civs[civ].ai_standing_goals[local_c].y);
      if (iVar1 <= param_5) {
        civs[civ].ai_standing_goals[local_c].role = 0xff;
        civs[civ].ai_standing_goals[local_c].priority = 0;
      }
    }
  }
  return;
}
#undef local_c

/* 00492d18 auto */
void __cdecl civ_ai_goal_insert_gap(iptr civ,iptr param_2)

{
  i16 iVar1;
  i8 iVar2;
  
  if ((param_2 < 0x2f) && (civs[civ].ai_goals[param_2].role != -1)) {
    civ_ai_goal_insert_gap(civ,param_2 + 1);
    iVar1 = civs[civ].ai_goals[param_2].y;
    civs[civ].ai_goals[param_2 + 1].x = civs[civ].ai_goals[param_2].x;
    civs[civ].ai_goals[param_2 + 1].y = iVar1;
    iVar2 = civs[civ].ai_goals[param_2].priority;
    civs[civ].ai_goals[param_2 + 1].role = civs[civ].ai_goals[param_2].role;
    civs[civ].ai_goals[param_2 + 1].priority = iVar2;
  }
  return;
}

/* 00492dd0 auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl civ_standing_goal_insert_gap(iptr civ,int param_2)

{
  i16 iVar1;
  i8 iVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0xe; param_2 <= local_8; local_8--) {
    iVar1 = civs[civ].ai_standing_goals[local_8].y;
    civs[civ].ai_standing_goals[local_8 + 1].x = civs[civ].ai_standing_goals[local_8].x;
    civs[civ].ai_standing_goals[local_8 + 1].y = iVar1;
    iVar2 = civs[civ].ai_standing_goals[local_8].priority;
    civs[civ].ai_standing_goals[local_8 + 1].role =
         civs[civ].ai_standing_goals[local_8].role;
    civs[civ].ai_standing_goals[local_8 + 1].priority = iVar2;
  }
  return;
}
#undef local_8

/* 00492e60 auto */
#define local_10 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
int __cdecl civ_ai_goal_get_priority(iptr civ,int param_2,int param_3,i32 param_4)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 0;
  for (local_8 = 0; local_8 < 0x30; local_8++) {
    if (((civs[civ].ai_goals[local_8].x == param_2) &&
        (civs[civ].ai_goals[local_8].y == param_3)) &&
       (civs[civ].ai_goals[local_8].role == (char)param_4)) {
      if (civs[civ].ai_goals[local_8].priority < 1) {
        local_10 = ~(int)civs[civ].ai_goals[local_8].priority + 1;
      }
      else {
        local_10 = (int)civs[civ].ai_goals[local_8].priority;
      }
      if ((char)local_c <= local_10) {
        if (civs[civ].ai_goals[local_8].priority < 1) {
          local_c = ~(int)civs[civ].ai_goals[local_8].priority + 1;
        }
        else {
          local_c = (int)civs[civ].ai_goals[local_8].priority;
        }
      }
    }
  }
  return local_c;
}
#undef local_10
#undef local_c
#undef local_8

/* 0049301b auto */
#define unit (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
void __cdecl civ_add_ai_goal(iptr civ,int x,int y,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 0;
  while( true ) {
    if (0x2f < local_c) {
      if (((game.turn_civ == civ) &&
          ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0)) &&
         ((param_4 == 2 || (param_4 == 3)))) {
        for (unit = 0; unit < game.num_units; unit++) {
          if ((((units[unit].id != 0) && (units[unit].owner == civ)) &&
              (iVar1 = unit_is_awake_with_moves(unit), iVar1 != 0)) &&
             ((char)unit_types[units[unit].type].role == param_4)) {
            iVar1 = tile_landmass((int)units[unit].x,(int)units[unit].y);
            iVar2 = tile_landmass(x,y);
            if (iVar1 == iVar2) {
              iVar1 = map_distance_diag(x,y,(int)units[unit].x,
                                         (int)units[unit].y);
              iVar2 = unit_moves_left(unit);
              if (iVar1 * 2 <= iVar2) {
                units[unit].orders = 11;
                units[unit].goto_x = (i16)x;
                units[unit].goto_y = (i16)y;
              }
            }
          }
        }
      }
      local_c = 0;
      while( true ) {
        if (0x2f < local_c) {
          return;
        }
        if ((civs[civ].ai_goals[local_c].priority < (char)param_5) ||
           (civs[civ].ai_goals[local_c].role == -1)) break;
        local_c++;
      }
      civ_ai_goal_insert_gap(civ,local_c);
      civs[civ].ai_goals[local_c].x = (i16)x;
      civs[civ].ai_goals[local_c].y = (i16)y;
      civs[civ].ai_goals[local_c].role = (char)param_4;
      civs[civ].ai_goals[local_c].priority = (char)param_5;
      return;
    }
    if (((civs[civ].ai_goals[local_c].x == x) &&
        (civs[civ].ai_goals[local_c].y == y)) &&
       ((civs[civ].ai_goals[local_c].role == (char)param_4 &&
        ((char)param_5 <= civs[civ].ai_goals[local_c].priority)))) break;
    local_c++;
  }
  return;
}
#undef unit
#undef local_c

/* 004933f2 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl civ_add_standing_goal(iptr civ,int param_2,int param_3,i32 param_4,int param_5)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  while( true ) {
    if (0xf < local_8) {
      local_8 = 0;
      while( true ) {
        if (0xf < local_8) {
          return;
        }
        if ((civs[civ].ai_standing_goals[local_8].priority < (char)param_5) ||
           (civs[civ].ai_standing_goals[local_8].role == -1)) break;
        local_8++;
      }
      civ_standing_goal_insert_gap(civ,local_8);
      civs[civ].ai_standing_goals[local_8].x = (short)param_2;
      civs[civ].ai_standing_goals[local_8].y = (short)param_3;
      civs[civ].ai_standing_goals[local_8].role = (char)param_4;
      civs[civ].ai_standing_goals[local_8].priority = (char)param_5;
      return;
    }
    if ((((civs[civ].ai_standing_goals[local_8].x == param_2) &&
         (civs[civ].ai_standing_goals[local_8].y == param_3)) &&
        (civs[civ].ai_standing_goals[local_8].role == (char)param_4)) &&
       ((char)param_5 <= civs[civ].ai_standing_goals[local_8].priority)) break;
    local_8++;
  }
  return;
}
#undef local_8

/* 00493602 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl civ_refresh_ai_goals(iptr civ)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; local_8 < 0x30; local_8++) {
    if (civs[civ].ai_goals[local_8].priority < '\0') {
      civs[civ].ai_goals[local_8].role = 0xff;
    }
    civ_ai_goal_negate_priority(civ,local_8);
  }
  for (local_8 = 0; local_8 < 0x10; local_8++) {
    if (-1 < civs[civ].ai_standing_goals[local_8].role) {
      civ_add_ai_goal(civ,(int)civs[civ].ai_standing_goals[local_8].x,
                         (int)civs[civ].ai_standing_goals[local_8].y,
                         (int)civs[civ].ai_standing_goals[local_8].role,
                         (int)civs[civ].ai_standing_goals[local_8].priority);
    }
  }
  return;
}
#undef local_8

/* 0049376f auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl civ_reset_standing_goals(iptr civ)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; local_8 < 0x10; local_8++) {
    civs[civ].ai_standing_goals[local_8].role = 0xff;
    civs[civ].ai_standing_goals[local_8].priority = 0;
  }
  return;
}
#undef local_8

/* 00493b10 auto */
int __cdecl civ_leader_name(iptr civ)

{
  int iVar1;
  
  if (civ < 1) {
    iVar1 = label_string(*(i32 *)(label_string_ids + 0x44));
  }
  else if (leaders[civs[civ].tribe].leader_name < 0) {
    iVar1 = civ * 0xf2 + ADDR(0x64bcfa, ((u8 *)&civ_names + 2));
  }
  else {
    iVar1 = label_string((int)leaders[civs[civ].tribe].leader_name);
  }
  return iVar1;
}

/* 00493ba6 auto */
int __cdecl civ_leader_title(iptr civ)

{
  int iVar1;
  
  if (civ < 1) {
    iVar1 = label_string(government_titles[2].male);
  }
  else {
    iVar1 = (int)leaders[civs[civ].tribe].titles[((uint)civs[civ].government)][((uint)leaders[civs[civ].tribe].female)];
    if (iVar1 < 0) {
      iVar1 = civ * 0xf2 + ADDR(0x64bd42, ((u8 *)&civ_names + 74)) + (uint)civs[civ].government * 0x18;
    }
    else {
      iVar1 = label_string(iVar1);
    }
  }
  return iVar1;
}

/* 00493c7d auto */
int __cdecl civ_name_plural(iptr civ)

{
  int iVar1;
  
  if (civ < 1) {
    iVar1 = label_string(*(i32 *)(label_string_ids + 0x3c));
  }
  else if (leaders[civs[civ].tribe].plural < 0) {
    iVar1 = civ * 0xf2 + ADDR(0x64bd12, ((u8 *)&civ_names + 26));
  }
  else {
    iVar1 = label_string((int)leaders[civs[civ].tribe].plural);
  }
  return iVar1;
}

/* 00493d13 auto */
int __cdecl civ_adjective(iptr civ)

{
  int iVar1;
  
  if (civ < 1) {
    iVar1 = label_string(*(i32 *)(label_string_ids + 0x40));
  }
  else if (leaders[civs[civ].tribe].adjective < 0) {
    iVar1 = civ * 0xf2 + ADDR(0x64bd2a, ((u8 *)&civ_names + 50));
  }
  else {
    iVar1 = label_string((int)leaders[civs[civ].tribe].adjective);
  }
  return iVar1;
}

/* 00494dae auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl advance_count_prereq_depth(iptr advance)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (tech_prereq_walk_count < 0x65) {
    for (local_8 = 0; local_8 < 2; local_8++) {
      if ('\0' < advances[advance].preq[local_8]) {
        tech_prereq_walk_count++;
        advance_count_prereq_depth((int)advances[advance].preq[local_8]);
      }
    }
  }
  return;
}
#undef local_8

/* 00498310 auto */
#define local_24 (*(char (*)[32])(frame_ + FRAME_OFF(4)))
void __cdecl civ_password_ensure_set(int civ)

{
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  mp_turn_timer_stop(1);
  passwords_unscramble();
  crt_strcpy(local_24,&civ_passwords + civ * 0x20);
  passwords_scramble();
  if (local_24[0] == '\0') {
    civ_change_password_dialog(civ);
  }
  return;
}
#undef local_24

/* 0049836a auto */
#define local_348 (*(char (*)[32])(frame_ + FRAME_OFF(0)))
#define local_328 (*(Dialog *)(frame_ + FRAME_OFF(32)))
#define local_34 (*(char (*)[32])(frame_ + FRAME_OFF(788)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(820)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(824)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(828)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(832)))
void __cdecl civ_change_password_dialog(iptr civ)

{
  i8 frame_[FRAME_OFF(840)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_328,0x4000);
  local_8 = 0;
  mp_turn_timer_stop(1);
  passwords_unscramble();
  crt_strcpy(local_34,&civ_passwords + civ * 0x20);
  passwords_scramble();
  if (local_34[0] == '\0') {
    dialog_load_text_section(&local_328,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x62cc78, ((u8 *)&g.d_0062cc78)),0x1f,ADDR(0x62cc74, ((u8 *)&g.d_0062cc74)),0,0,0,1);
    password_dialog_set_title((iptr)&local_328,civ,0x26c);
    local_14 = dialog_run_modal(&local_328,(iptr)local_348,0);
  }
  else {
    dialog_load_text_section(&local_328,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x62cc4c, ((u8 *)&g.d_0062cc4c)),0x1f,ADDR(0x62cc48, ((u8 *)&g.d_0062cc48)),0,0,0,1);
    password_dialog_set_title((iptr)&local_328,civ,0x26d);
    local_14 = dialog_run_modal(&local_328,(iptr)local_348,0);
    if (local_14 < 0) goto LAB_004985a2;
    local_14 = _strcmp(local_348,local_34);
    if (local_14 != 0) {
      popup_game(ADDR(0x62cc58, ((u8 *)&g.d_0062cc58)));
      goto LAB_004985a2;
    }
    dialog_load_text_section(&local_328,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x62cc68, ((u8 *)&g.d_0062cc68)),0x1f,ADDR(0x62cc64, ((u8 *)&g.d_0062cc64)),0,0,0,1);
    password_dialog_set_title((iptr)&local_328,civ,0x26c);
    local_14 = dialog_run_modal(&local_328,(iptr)local_348,0);
  }
  if (-1 < local_14) {
    passwords_unscramble();
    crt_strcpy(&civ_passwords + civ * 0x20,local_348);
    crt_strcpy(local_34,local_348);
    passwords_scramble();
    if (local_34[0] != '\0') {
      popup_game(ADDR(0x62cc84, ((u8 *)&g.d_0062cc84)));
    }
  }
LAB_004985a2:
  passwords_refresh_flags();
  *(i32 *)(&civ_password_prompt_pending + civ * 4) = 0;
  mp_turn_timer_resume(1);
  local_8 = 0xffffffff;
  /* inlined unwind funclet 004985d0 */ { dialog_dtor((Dialog *)((iptr)&local_328)); }
  return;
}
#undef local_348
#undef local_328
#undef local_34
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004985f4 auto */
#define dlg_pending_idle_callback (*(i8 * *)((u8 *)&g.d_00635a3c))
#define local_328 (*(char (*)[32])(frame_ + FRAME_OFF(0)))
#define local_308 (*(Dialog *)(frame_ + FRAME_OFF(32)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(788)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(792)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(796)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(800)))
i32 __cdecl civ_password_prompt(int civ)

{
  i32 uVar1;
  i8 frame_[FRAME_OFF(808)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_308,0x4000);
  local_8 = 0;
  dialog_load_text_section(&local_308,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x62cc94, ((u8 *)&g.d_0062cc94)),0x1f,ADDR(0x62cc90, ((u8 *)&g.d_0062cc90)),0,0,0,1);
  password_dialog_set_title((iptr)&local_308,civ,0x26b);
  local_328[0] = '\0';
  dlg_pending_idle_callback = ((void *)ADDR(0x00402c3e, net_pump_idle_cb));
  local_14 = dialog_run_modal(&local_308,(iptr)local_328,0);
  if (local_14 < 0) {
    local_8 = 0xffffffff;
    /* inlined unwind funclet 0049875f */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
    uVar1 = 2;
  }
  else {
    passwords_unscramble();
    local_14 = _strcmp(local_328,&civ_passwords + civ * 0x20);
    passwords_scramble();
    if (local_14 == 0) {
      local_8 = 0xffffffff;
      /* inlined unwind funclet 0049875f */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
      uVar1 = 0;
    }
    else {
      dlg_pending_idle_callback = ((void *)ADDR(0x00402c3e, net_pump_idle_cb));
      popup_game(ADDR(0x62cca0, ((u8 *)&g.d_0062cca0)));
      local_8 = 0xffffffff;
      /* inlined unwind funclet 0049875f */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
      uVar1 = 1;
    }
  }
  return uVar1;
}
#undef dlg_pending_idle_callback
#undef local_328
#undef local_308
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00498a5c auto */
#define game_loop_active (*(i8 *)((u8 *)&g.d_00628044))
i32 __cdecl civ_check_password(iptr civ)

{
  int iVar1;
  
  if (*(int *)(&civ_password_prompt_pending + civ * 4) == 0) {
    if (game.multiplayer == 2) {
      civ_password_ensure_set(civ);
    }
    else {
      game_loop_active = 1;
    }
  }
  else {
    do {
      game_loop_active = 1;
      iVar1 = civ_password_prompt(civ);
      if (iVar1 == 0) {
        *(i32 *)(&civ_password_prompt_pending + civ * 4) = 0;
        return 1;
      }
    } while (iVar1 == 1);
    if (iVar1 == 2) {
      game_loop_active = 0;
      return 0;
    }
  }
  return 1;
}
#undef game_loop_active

/* 004a28b0 auto */
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
#define scenario_objective_civ (*(short *)((u8 *)&g.d_0064bcba))
#define scenario_victory_thresholds (*(short *)((u8 *)&g.d_0064bcbc))
#define score_citizens (*(int *)((u8 *)&g.d_00673f78))
#define score_civ_objective_value (*(int *)((u8 *)&g.d_00673f80))
#define score_objective_civ_value (*(int *)((u8 *)&g.d_00673f64))
#define score_total_objective_value (*(int *)((u8 *)&g.d_00673f70))
#define score_wonders (*(int *)((u8 *)&g.d_00673f5c))
#define spaceship_success_pct (*(int *)((u8 *)&g.d_006ad0ec))
#define local_18 (*(int *)(frame_ + FRAME_OFF(0)))
#define city (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
int __cdecl civ_calc_score(iptr civ)

{
  int iVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  score_citizens = 0;
  for (city = 0; city < game.num_cities; city++) {
    if ((cities[city].id != 0) && (cities[city].owner == civ)) {
      score_citizens = score_citizens +
                     (((int)cities[city].size + (int)(char)cities[city].happy) -
                     (int)(char)cities[city].unhappy);
    }
  }
  score_wonders = 0;
  for (local_c = 0; local_c < 0x1c; local_c++) {
    if ((-1 < game.wonder_city[local_c]) && (cities[game.wonder_city[local_c]].owner == civ)) {
      score_wonders += 0x14;
    }
  }
  score_spaceship_in_flight = 0;
  score_spaceship_arrived = 0;
  spaceship_calc_stats(civ,1);
  if (((spaceship_success_pct != 0) && (civs[civ].spaceship_population != 0)) &&
     (iVar1 = civs[civ].spaceship_population * spaceship_success_pct, score_spaceship_in_flight = iVar1,
     (civs[civ].spaceship_flags & 0x10) != 0)) {
    score_spaceship_in_flight = 0;
    score_spaceship_arrived = iVar1;
  }
  score_pollution = ((int)game.polluted_tiles - (int)game.field_28) * -10;
  score_peace = 0;
  if (199 < game.turn) {
    score_peace = int_clamp(game.field_2c * 3,0,100);
  }
  score_future_techs = (uint)civs[civ].future_techs * 5;
  score_barbarian_bonus = (uint)game.barbarian_activity * 0x19 - 0x32;
  score_total = score_peace + score_pollution + score_spaceship_arrived + score_wonders + score_citizens +
                 score_barbarian_bonus + score_future_techs;
  if (score_total < 0) {
    score_total = 0;
  }
  score_conquest_bonus = 0;
  if ((game.civs_alive & 0xfffffffe) == 1 << ((byte)civ & 0x1f)) {
    local_18 = (int)game.turn;
    if (((game.rules & 0x100) != 0) && (local_18 < 0xfb)) {
      local_18 = 0xfa;
    }
    score_conquest_bonus = (uint)game.num_enemies * 100 + (0x23a - local_18) * 2 + 400;
    if ((game.game_flags & 4) != 0) {
      score_conquest_bonus = (int)(score_conquest_bonus * 5 + (score_conquest_bonus * 5 >> 0x1f & 3U)) >> 2;
    }
    if ((game.game_flags & 8) != 0) {
      score_conquest_bonus = (score_conquest_bonus << 2) / 5;
    }
  }
  score_scenario_points = 0;
  if (((game.game_flags & 0x80) == 0) || ((scenario_flags & 2) == 0)) {
    iVar1 = score_total;
    if (score_total <= score_conquest_bonus) {
      iVar1 = score_conquest_bonus;
    }
  }
  else {
    score_total_objective_value = 0;
    score_objective_civ_value = 0;
    score_civ_objective_value = 0;
    for (city = 0; city < game.num_cities; city++) {
      if (cities[city].id != 0) {
        iVar1 = city_objective_value(city);
        score_total_objective_value += iVar1;
        if ((int)cities[city].owner == (int)scenario_objective_civ) {
          score_objective_civ_value += iVar1;
        }
        if (cities[city].owner == civ) {
          score_civ_objective_value += iVar1;
        }
      }
    }
    if (scenario_objective_civ == 0) {
      score_objective_civ_value = score_civ_objective_value;
    }
    score_objective_outcome = 2;
    if (score_objective_civ_value < scenario_victory_thresholds) {
      if (score_objective_civ_value < scenario_marginal_victory_score) {
        if (scenario_decisive_defeat_score < score_objective_civ_value) {
          if (score_objective_civ_value <= scenario_marginal_defeat_score) {
            score_objective_outcome = 3;
          }
        }
        else {
          score_objective_outcome = 4;
        }
      }
      else {
        score_objective_outcome = 1;
      }
    }
    else {
      score_objective_outcome = 0;
    }
    local_8 = score_objective_outcome;
    if ((scenario_objective_civ != 0) && (scenario_objective_civ != civ)) {
      local_8 = 4 - score_objective_outcome;
    }
    switch(local_8) {
    case 0:
      score_scenario_points = 1000;
      break;
    case 1:
      score_scenario_points = 0x2ee;
      break;
    case 2:
      score_scenario_points = 500;
      break;
    case 3:
      score_scenario_points = 0xfa;
      break;
    case 4:
      score_scenario_points = 0;
    }
    score_scenario_points += score_civ_objective_value * 10;
    if (0 < score_conquest_bonus) {
      score_scenario_points = score_scenario_points * 2;
    }
    score_conquest_bonus = -1;
    score_total = score_scenario_points;
    iVar1 = score_scenario_points;
  }
  return iVar1;
}
#undef scenario_flags
#undef scenario_objective_civ
#undef scenario_victory_thresholds
#undef score_citizens
#undef score_civ_objective_value
#undef score_objective_civ_value
#undef score_total_objective_value
#undef score_wonders
#undef spaceship_success_pct
#undef local_18
#undef city
#undef local_c
#undef local_8

/* 004a74bc auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl civ_reset_spaceship(iptr civ)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  civs[civ].spaceship_flags = '\0';
  civs[civ].spaceship_population = 0;
  civs[civ].spaceship_launch_year = 0;
  civs[civ].spaceship_arrival_year = 0;
  for (local_8 = 0; local_8 < 6; local_8++) {
    civs[civ].spaceship_parts[local_8] = 0;
  }
  return;
}
#undef local_8

/* 004a7577 auto */
uint __cdecl civ_spaceship_launched(iptr civ)

{
  return civs[civ].spaceship_flags & 2;
}

/* 004a75a6 auto */
uint __cdecl civ_spaceship_exists(iptr civ)

{
  return civs[civ].spaceship_flags & 1;
}

/* 004a75d5 auto */
i32 __cdecl civ_spaceship_arrived(iptr civ)

{
  int iVar1;
  i32 uVar2;
  
  iVar1 = civ_spaceship_launched(civ);
  if ((iVar1 == 0) || (game.year < civs[civ].spaceship_arrival_year)) {
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}

/* 004a762d auto */
void __cdecl civ_spaceship_lost_notify(iptr civ)

{
  iptr iVar1;
  int iVar2;
  
  iVar1 = civ_get_adjective(civ);
  text_set_string_arg(0,iVar1);
  iVar2 = civ_spaceship_launched(civ);
  if (iVar2 == 0) {
    iVar2 = civ_spaceship_exists(civ);
    if (iVar2 != 0) {
      if (2 < game.multiplayer) {
        net_send_text_args(0xd,0xff,1,0,0,0);
      }
      popup_game(ADDR(0x62cf04, ((u8 *)&g.d_0062cf04)));
    }
  }
  else {
    if (2 < game.multiplayer) {
      net_send_text_args(0xc,0xff,1,0,0,0);
    }
    popup_game(ADDR(0x62cef4, ((u8 *)&g.d_0062cef4)));
  }
  civ_reset_spaceship(civ);
  return;
}

/* 004a7ce9 auto */
#define civ_create_busy (*(i32 *)((u8 *)&g.d_006ad8f0))
#define game_loop_active (*(i8 *)((u8 *)&g.d_00628044))
#define game_over_reason (*(i32 *)((u8 *)&g.d_0064b1ac))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define map_view_center_x (*(i16 *)((u8 *)&g.d_0066ca88))
#define mapview_center_y (*(i16 *)((u8 *)&g.d_0066ca8a))
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define nm_new_civ_ack_result (*(int *)((u8 *)&g.d_006c9164))
#define local_1c0 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_1bc (*(int *)(frame_ + FRAME_OFF(4)))
#define local_1b8 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_1b4 (*(int *)(frame_ + FRAME_OFF(12)))
#define aiStack_1b0 (*(iptr (*)[21])(frame_ + FRAME_OFF(16)))
#define x3 (*(iptr *)(frame_ + FRAME_OFF(100)))
#define local_158 (*(int *)(frame_ + FRAME_OFF(104)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(108)))
#define local_150 (*(int *)(frame_ + FRAME_OFF(112)))
#define local_14c (*(int *)(frame_ + FRAME_OFF(116)))
#define local_148 (*(uint *)(frame_ + FRAME_OFF(120)))
#define local_144 (*(iptr *)(frame_ + FRAME_OFF(124)))
#define y2 (*(uint *)(frame_ + FRAME_OFF(128)))
#define aiStack_13c (*(int (*)[64])(frame_ + FRAME_OFF(132)))
#define x2 (*(uint *)(frame_ + FRAME_OFF(388)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(392)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(396)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(400)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(404)))
#define local_28 (*(uint *)(frame_ + FRAME_OFF(408)))
#define leader (*(iptr *)(frame_ + FRAME_OFF(412)))
#define y3 (*(iptr *)(frame_ + FRAME_OFF(416)))
#define local_1c (*(iptr *)(frame_ + FRAME_OFF(420)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(424)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(428)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(432)))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(436)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(440)))
int __cdecl civ_create(iptr civ)

{
  short sVar1;
  byte bVar2;
  i16 iVar3;
  iptr iVar4;
  iptr iVar5;
  int iVar6;
  i32 uVar7;
  i32 uVar8;
  i8 frame_[FRAME_OFF(448)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) || (game.turn == 0)) {
    civ_create_busy = 1;
    if ((game.multiplayer < 3) || (net_host_flag != '\0')) {
      local_30 = (int)civs[civ].tribe;
      civs[civ].gold = 0;
      civs[civ].research_progress = 0;
      civs[civ].num_advances = '\0';
      civs[civ].field_12 = '\0';
      iVar3 = game.turn;
      if (game.turn < 0xb) {
        iVar3 = 10;
      }
      civs[civ].last_city_turn = iVar3;
      civs[civ].government = 1;
      civs[civ].tax_rate = 4;
      civs[civ].science_rate = 4;
      civs[civ].field_1c = 0;
      civs[civ].reputation = '\0';
      civs[civ].field_1f = '\0';
      civs[civ].field_3d2 = 0;
      for (local_1c = 0; local_1c < 10; local_1c++) {
        *(i8 *)&civs[civ].throne_room[local_1c] = 0;
      }
      civs[civ].throne_room[0] = 1;
      civs[civ].throne_room[1] = 1;
      civs[civ].throne_room[3] = 1;
      civs[civ].throne_room[6] = 1;
      civs[civ].throne_room_upgrades = 0;
      for (leader = 0; leader < 8; leader++) {
        civs[civ].field_48[leader] = 0;
        civs[leader].field_48[civ] = 0;
        *(i8 *)&civs[civ].field_50[leader] = 0;
        *(i8 *)&civs[leader].field_50[civ] = 0;
      }
      civs[civ].attitude[0] = 'd';
      for (leader = 1; leader < 8; leader++) {
        if (civ == 0) {
          civs[0].attitude[leader] = 'd';
        }
        else if ((1 << ((byte)leader & 0x1f) & (uint)game.human_players) == 0) {
          iVar5 = _rand();
          *(char *)&civs[leader].attitude[civ] = (char)(iVar5 % 0x50) + '\n';
          *(i8 *)&civs[civ].attitude[leader] =
               *(i8 *)&civs[leader].attitude[civ];
        }
        else {
          uVar8 = 0x4b;
          uVar7 = 10;
          iVar6 = _rand();
          uVar7 = int_clamp((uint)game.difficulty * 5 + iVar6 % 0x50 + 10,uVar7,uVar8);
          *(char *)&civs[leader].attitude[civ] = (char)uVar7;
          *(i8 *)&civs[civ].attitude[leader] =
               *(i8 *)&civs[leader].attitude[civ];
        }
      }
      civ_refresh_ai_goals(civ);
      civ_reset_standing_goals(civ);
      for (local_1c = 0; local_1c < 0x40; local_1c++) {
        *(i8 *)&civs[civ].continent_policy[local_1c] = 5;
        aiStack_13c[local_1c] = 0;
        for (leader = 1; leader < 8; leader++) {
          aiStack_13c[local_1c] =
               aiStack_13c[local_1c] + (uint)civs[leader].continent_cities[local_1c];
        }
      }
      civs[civ].num_cities = 0;
      *(i32 *)(&civ_unit_counts + civ * 4) = 0;
      civs[civ].num_military_units = 0;
      civs[civ].military_strength = 0;
      civs[civ].total_attack = 0;
      civs[civ].total_city_size = 0;
      civs[civ].num_ships = 0;
      civs[civ].population_milestone = 0;
      for (local_1c = 0; local_1c < 4; local_1c++) {
        *(i8 *)&civs[civ].wonders_by_group[local_1c] = 0;
      }
      for (leader = 0; leader < 8; leader++) {
        civs[leader].last_treaty_turn[civ] = 0xffff;
      }
      local_148 = ~(1 << ((byte)civ & 0x1f));
      for (local_1c = 0; local_1c < 100; local_1c++) {
        *(i8 *)&civs[civ].advance_source[local_1c] = 0xff;
        game.advance_known_by[local_1c] = game.advance_known_by[local_1c] & (byte)local_148;
      }
      for (leader = 0; leader < 8; leader++) {
        *(i32 *)&civs[civ].treaties[leader] = 0;
        *(i32 *)&civs[leader].treaties[civ] = 0;
      }
      for (local_1c = 0; local_1c < 0xd; local_1c++) {
        *(i8 *)&civs[civ].advances[local_1c] = 0;
      }
      if (game.turn != 0) {
        local_28 = (uint)game.civs_alive & 1 << ((byte)civ & 0x1f);
        game.civs_alive = game.civs_alive & ~(byte)(1 << ((byte)civ & 0x1f));
        for (local_1c = 0; local_1c < 99; local_1c++) {
          if (((((uint)game.human_players & 1 << (game.first_discoverer[local_1c] & 0x1f)) == 0) ||
              (iVar6 = bits_count8((int)(char)game.advance_known_by[local_1c]), 2 < iVar6))
             && ((game.human_players & game.advance_known_by[local_1c]) != 0)) {
            if (game.difficulty == '\0') {
              local_1b4 = 0;
            }
            else {
              local_1b4 = _rand();
              local_1b4 = local_1b4 % (int)(game.difficulty + 1);
            }
            if (local_1b4 != 0) {
              civ_give_advance(civ,local_1c,civ,0,0);
            }
          }
        }
        if (local_28 != 0) {
          game.civs_alive = game.civs_alive | (byte)(1 << ((byte)civ & 0x1f));
        }
      }
      for (local_1c = 0; local_1c < 0x3e; local_1c++) {
        *(i8 *)&civs[civ].units_active[local_1c] = 0;
        *(i8 *)&civs[civ].units_in_production[local_1c] = 0;
        *(i8 *)&civs[civ].units_lost[local_1c] = 0;
      }
      if (civ == 0) {
        civ_create_busy = 0;
        iVar6 = 1;
      }
      else {
        local_158 = 0;
        if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
          local_c = 0;
          for (local_34 = 0; (local_c == 0 && (local_34 < 3)); local_34++) {
            for (local_1c = 0; local_1c < 0x15; local_1c++) {
              sVar1 = leaders[local_1c].color;
              local_2c = (int)sVar1;
              iVar6 = local_2c;
              (*(i8 *)((char *)&local_2c + 0)) = (byte)sVar1;
              bVar2 = (byte)local_2c & 0x1f;
              local_2c = iVar6;
              if ((((1 << bVar2 & (uint)game.human_players) == 0) && (civ == sVar1)) &&
                 ((leaders[local_1c].times_used == '\0' || (0 < local_34)))) {
                aiStack_1b0[local_c] = local_1c;
                local_c++;
              }
            }
          }
          if (local_c == 0) {
            game.civs_alive = game.civs_alive & ~(byte)(1 << ((byte)civ & 0x1f));
            civ_create_busy = 0;
            return 1;
          }
          if (local_c == 1 || local_c - 1 < 0) {
            local_1b8 = 0;
          }
          else {
            iVar6 = _rand();
            local_1b8 = iVar6 % local_c;
          }
          leader = aiStack_1b0[local_1b8];
          if ((game.turn == 0) && (-1 < (char)(&setup_chosen_leaders)[civ])) {
            leader = (iptr)(char)(&setup_chosen_leaders)[civ];
            (&setup_chosen_leaders)[civ] = 0xff;
          }
          if (leaders[leader].times_used == '\0') {
            local_158 = 0;
          }
          else {
            local_158 = _rand();
            local_158 = local_158 % (int)(leaders[leader].times_used + 1);
          }
          civs[civ].tribe = (i16)leader;
          leaders[leader].times_used++;
          leaders[leader].city_name_index = '\0';
          iVar6 = _rand();
          if (iVar6 % 3 == 0) {
            if (leaders[leader].female == '\0') {
              leaders[leader].female = 1;
            }
            else {
              leaders[leader].female = '\0';
            }
          }
          leaders[leader].leader_name =
               leaders[leader].names[((uint)leaders[leader].female)];
          civs[civ].leader_portrait = (byte)leader;
          civs[civ].flags = civs[civ].flags & 0xfdff;
          if (leaders[leader].female != '\0') {
            civs[civ].leader_portrait += 21;
            civs[civ].flags = civs[civ].flags | 0x200;
          }
        }
        if ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) == 0) {
          civ_create_busy = 0;
          iVar6 = 1;
        }
        else {
          local_14c = 0;
          do {
            if ((((game.rules & 0x8000) == 0) || (map.width < 0x51)) || (0x5db < local_14c)) {
              if (map.width == 1 || map.width - 1 < 0) {
                x2 = 0;
              }
              else {
                iVar6 = _rand();
                x2 = iVar6 % (int)map.width;
              }
            }
            else {
              if (map.width == 0x11 || map.width - 0x11 < 0) {
                local_1bc = 0;
              }
              else {
                local_1bc = _rand();
                local_1bc = local_1bc % (map.width - 0x10);
              }
              x2 = local_1bc + 8;
            }
            if ((((game.rules & 0x8000) == 0) || (map.height < 0x28)) || (0x5db < local_14c)) {
              if (map.height == 1 || map.height - 1 < 0) {
                y2 = 0;
              }
              else {
                iVar6 = _rand();
                y2 = iVar6 % (int)map.height;
              }
            }
            else {
              if (map.height == 0x11 || map.height - 0x11 < 0) {
                local_1c0 = 0;
              }
              else {
                local_1c0 = _rand();
                local_1c0 = local_1c0 % (map.height - 0x10);
              }
              y2 = local_1c0 + 8;
            }
            if ((x2 & 1) != 0) {
              x2--;
            }
            if ((y2 & 1) != 0) {
              x2++;
            }
            local_14 = city_find_nearest(x2,y2,-1,0xffffffff,-1);
            if (local_14 < 0) {
              nearest_city_dist = 0x1e;
            }
            if (game.turn == 0) {
              for (unit = 0; unit < game.num_units; unit++) {
                if ((units[unit].id != 0) &&
                   (local_38 = map_distance_diag(x2,y2,(int)units[unit].x,
                                                  (int)units[unit].y), local_38 < nearest_city_dist)
                   ) {
                  nearest_city_dist = local_38;
                }
              }
            }
            local_18 = tile_owner_or_fertility(x2,y2);
            local_144 = tile_landmass(x2,y2);
            local_150 = (int)*(short *)(&landmass_fertile_tiles + local_144 * 0x10);
            local_14c++;
          } while (((local_14c < 0x7d1) ||
                   (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0 &&
                    (game.turn == 0)))) &&
                  (((((iVar6 = tile_is_ocean(x2,y2), iVar6 != 0 ||
                      ((local_18 < 0xc - (local_14c >> 5) ||
                       (nearest_city_dist < 0x10 - (local_14c >> 7))))) ||
                     (((nearest_city_dist < 2 && (local_14c < 0x7d1)) ||
                      ((nearest_city_dist < 1 ||
                       (local_150 < (0x20 - ((int)game.turn >> 4)) - (local_14c >> 6))))))) ||
                    ((200 < game.turn && (aiStack_13c[local_144] != 0)))) ||
                   (((iVar6 = tile_has_hut(x2,y2), iVar6 != 0 && (local_14c < 0x7d1))
                    || (iVar6 = tile_city_or_unit_owner(x2,y2), -1 < iVar6))))));
          if ((game.turn == 0) &&
             (iVar6 = map_in_bounds((int)start_x[civs[civ].tribe],
                                    (int)start_y[civs[civ].tribe]), iVar6 != 0)) {
            x2 = (uint)start_x[civs[civ].tribe];
            y2 = (uint)start_y[civs[civ].tribe];
            local_14c = 0;
          }
          if (2000 < local_14c) {
            local_158 = 1;
          }
          if (((int)y2 < 3) || (map.height - 3 <= (int)y2)) {
            local_158 = 1;
          }
          if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
            civs[civ].science_rate = leaders[civs[civ].tribe].civilize + 3;
            civs[civ].tax_rate = '\t' - civs[civ].science_rate;
          }
          if (((local_158 == 0) &&
              (((game.turn == 0 || ((game.rules & 0x100) == 0)) &&
               ((int)game.turn <= (int)((uint)game.difficulty * -0x23 + 0x15e))))) ||
             ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) {
            civs[civ].num_advances = 1;
            unit = (iptr)game.num_units;
            while (unit = unit - 1, -1 < unit) {
              if (((units[unit].id != 0) && (units[unit].owner == '\0')) &&
                 (iVar6 = map_distance_diag(x2,y2,(int)units[unit].x,
                                             (int)units[unit].y), iVar6 < 9)) {
                unit_delete(unit,1);
              }
            }
            if (human_civ == civ) {
              map_view_center_x = (i16)x2;
              mapview_center_y = (i16)y2;
            }
            unit = unit_create(0,civ,x2,y2);
            civs[civ].capital_x = (i16)x2;
            if (((0x14 < game.turn) && (local_158 == 0)) &&
               ((iVar6 = tile_at(x2,y2),
                (game.human_players & *(byte *)(iVar6 + 4)) == 0 &&
                ((unit_create(0,civ,x2,y2), 0x28 < game.turn &&
                 (iVar6 = civ_can_build_unit(civ,-1,3), iVar6 != 0)))))) {
              unit_create(3,civ,x2,y2);
            }
            net_batch_begin();
            for (local_1c = 0; local_1c < 0x15; local_1c++) {
              x3 = map_wrap_x((int)(char)(&city_tile_dx_table)[local_1c] + x2);
              y3 = (int)(char)(&city_tile_dy_table)[local_1c] + y2;
              iVar6 = map_in_bounds(x3,y3);
              if (iVar6 != 0) {
                tile_set_visible(x3,y3,1 << ((byte)civ & 0x1f),1,1);
              }
            }
            net_batch_flush();
            civ_create_busy = 0;
            iVar6 = 1;
          }
          else {
            game.civs_alive = game.civs_alive & ~(byte)(1 << ((byte)civ & 0x1f));
            civs[civ].tribe = (i16)local_30;
            local_10 = 0;
            for (local_1c = 1; local_1c < 8; local_1c++) {
              if ((1 << ((byte)local_1c & 0x1f) & (uint)game.civs_alive) != 0) {
                local_10++;
              }
            }
            if (local_10 < 2) {
              if ((game.game_flags & 2) == 0) {
                game_over_reason = 3;
                game.game_flags = game.game_flags | 2;
              }
              civ_create_busy = 0;
              iVar6 = -1;
            }
            else {
              civ_create_busy = 0;
              iVar6 = 0;
            }
          }
        }
      }
    }
    else {
      civ_create_busy = 0;
      nm_new_civ_ack_result = -0x1b;
      net_send_message(0x5f,0,civ,0,0,0,0,0,0,0);
      local_8 = timer_ticks();
      while ((nm_new_civ_ack_result == -0x1b && (iVar4 = timer_ticks(), iVar4 - local_8 < 0xe10))) {
        net_process_messages((NetSession *)&net_session,1,1);
      }
      if (nm_new_civ_ack_result == -0x1b) {
        dbg_log(ADDR(0x62cf14, ((u8 *)&g.d_0062cf14)));
        popup_game_with_sprite(ADDR(0x62cf40, ((u8 *)&g.d_0062cf40)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        game_loop_active = 0;
      }
      else {
        dbg_log(ADDR(0x62cf54, ((u8 *)&g.d_0062cf54)));
      }
      while ((net_msgq_priority_count != 0 || (iVar6 = nm_new_civ_ack_result, net_msgq_normal_count != 0))) {
        net_process_messages((NetSession *)&net_session,1,0);
      }
    }
  }
  else {
    iVar6 = 0;
  }
  return iVar6;
}
#undef civ_create_busy
#undef game_loop_active
#undef game_over_reason
#undef human_civ
#undef map_view_center_x
#undef mapview_center_y
#undef net_host_flag
#undef nm_new_civ_ack_result
#undef local_1c0
#undef local_1bc
#undef local_1b8
#undef local_1b4
#undef aiStack_1b0
#undef x3
#undef local_158
#undef unit
#undef local_150
#undef local_14c
#undef local_148
#undef local_144
#undef y2
#undef aiStack_13c
#undef x2
#undef local_38
#undef local_34
#undef local_30
#undef local_2c
#undef local_28
#undef leader
#undef y3
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 004aa378 auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define civ_check_destroyed_busy (*(i32 *)((u8 *)&g.d_006ad8f4))
#define destroyed_civ_count (*(short *)((u8 *)&g.d_00655128))
#define game_loop_active (*(i8 *)((u8 *)&g.d_00628044))
#define game_over_reason (*(i32 *)((u8 *)&g.d_0064b1ac))
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define nm_kill_civ_ack_result (*(int *)((u8 *)&g.d_006c9168))
#define unit (*(iptr *)(frame_ + FRAME_OFF(4)))
#define city (*(iptr *)(frame_ + FRAME_OFF(8)))
#define y2 (*(int *)(frame_ + FRAME_OFF(16)))
#define x2 (*(int *)(frame_ + FRAME_OFF(20)))
int __cdecl civ_check_destroyed(iptr civ,iptr civ2)

{
  uint *puVar1;
  iptr iVar2;
  iptr iVar3;
  iptr iVar4;
  int iVar5;
  i32 uVar6;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (civ == 0) {
    iVar5 = 0;
  }
  else {
    civ_check_destroyed_busy = 1;
    if ((game.multiplayer < 3) || (net_host_flag != '\0')) {
      for (city = 0; city < game.num_cities; city++) {
        if ((cities[city].id != 0) && (cities[city].owner == civ)) {
          civ_check_destroyed_busy = 0;
          return 0;
        }
      }
      if (civ2 == -1) {
        civ_reset_spaceship(civ);
      }
      else {
        if (autoplay_active == 0) {
          iVar4 = civ_adjective(civ);
          text_set_string_arg_b(0,iVar4);
          iVar4 = civ_name_plural(civ2);
          text_set_string_arg_b(1,iVar4);
          if (2 < game.multiplayer) {
            net_send_text_args(0xe,0xff,2,0,civ,0);
          }
          music_play_track(2,1);
          popup_game_with_sprite(ADDR(0x62cff4, ((u8 *)&g.d_0062cff4)),(iptr)(&civ_portrait_sprites + civ * 0x3c),0);
        }
        if (destroyed_civ_count < 0xc) {
          iVar5 = (int)destroyed_civ_count;
          destroyed_civ_count++;
          *(i16 *)(&destroyed_civ_turns + iVar5 * 2) = game.turn;
          (&destroyed_civ_killers)[iVar5] = (i8)civ2;
          (&destroyed_civ_portraits)[iVar5] = civs[civ].leader_portrait;
          uVar6 = civ_name_plural(civ);
          crt_strcpy(&destroyed_civ_names + iVar5 * 0x18,uVar6);
        }
        civ_spaceship_lost_notify(civ);
      }
      unit = (iptr)game.num_units;
      while (unit = unit - 1, -1 < unit) {
        if (units[unit].id != 0) {
          if (((units[unit].owner == civ) || ((units[unit].flags & 2) == 0)) ||
             ((char)units[unit].counter != civ)) {
            if (units[unit].owner == civ) {
              unit_delete(unit,1);
            }
          }
          else {
            units[unit].flags = units[unit].flags & 0xfffd;
            puVar1 = (uint *)(civ * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + (char)units[unit].counter * 4);
            *puVar1 = *puVar1 & 0xfeffffff;
            spy_try_escape(unit,0,(int)(char)units[unit].counter);
          }
        }
      }
      if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) {
        if (human_civ == civ) {
          game_over_reason = 4;
        }
        else if ((2 < game.multiplayer) && (human_civ != civ)) {
          net_send_message(0x6b,*(i32 *)
                                   (&net_player_slots + *(int *)(&net_civ_slots + civ * 4) * 0x54),
                             (uint)game.game_flags,4,0,0,0,0,0,0);
        }
        passwords_unscramble();
        (&civ_passwords)[civ * 0x20] = 0;
        passwords_scramble();
        if ((~(1 << ((byte)civ & 0x1f)) & (uint)game.human_players) == 0) {
          civ_check_destroyed_busy = 0;
          return 0;
        }
      }
      net_batch_begin();
      for (x2 = 0; x2 < map.width; x2++) {
        for (y2 = 0; y2 < map.height; y2++) {
          tile_set_visible(x2,y2,1 << ((byte)civ & 0x1f),0,1);
        }
      }
      net_batch_flush();
      if (2 < game.multiplayer) {
        game.human_players = game.human_players & ~(byte)(1 << ((byte)civ & 0x1f));
        net_send_message(0x31,0,0,civ,0,0,0,0,0,0);
      }
      if (game.multiplayer == 1) {
        game.human_players = game.human_players & ~(byte)(1 << ((byte)civ & 0x1f));
      }
      civ_create(civ);
      if (2 < game.multiplayer) {
        net_send_state_diff(0xff,2,0,0,0);
        net_send_message(0x74,0xff,0,0,0,0,0,0,0,0);
      }
      if ((game.multiplayer != 1) ||
         ((1 << ((byte)human_civ & 0x1f) & (uint)game.civs_alive) != 0)) {
        map_redraw_all_views(human_civ,1);
      }
      civ_check_destroyed_busy = 0;
      iVar5 = 1;
    }
    else {
      civ_check_destroyed_busy = 0;
      nm_kill_civ_ack_result = -0x1b;
      net_send_message(0x60,0,civ,civ2,0,0,0,0,0,0);
      iVar2 = timer_ticks();
      while ((nm_kill_civ_ack_result == -0x1b && (iVar3 = timer_ticks(), iVar3 - iVar2 < 0xe10))) {
        net_process_messages((NetSession *)&net_session,1,1);
      }
      if (nm_kill_civ_ack_result == -0x1b) {
        dbg_log(ADDR(0x62cf84, ((u8 *)&g.d_0062cf84)));
        popup_game_with_sprite(ADDR(0x62cfb0, ((u8 *)&g.d_0062cfb0)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        game_loop_active = 0;
      }
      else {
        dbg_log(ADDR(0x62cfc4, ((u8 *)&g.d_0062cfc4)));
      }
      while ((net_msgq_priority_count != 0 || (iVar5 = nm_kill_civ_ack_result, net_msgq_normal_count != 0))) {
        net_process_messages((NetSession *)&net_session,1,0);
      }
    }
  }
  return iVar5;
}
#undef autoplay_active
#undef civ_check_destroyed_busy
#undef destroyed_civ_count
#undef game_loop_active
#undef game_over_reason
#undef human_civ
#undef net_host_flag
#undef nm_kill_civ_ack_result
#undef unit
#undef city
#undef y2
#undef x2

/* 004b0720 auto */
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define advance (*(int *)(frame_ + FRAME_OFF(8)))
i8 __cdecl rules_parse_advance_abbrev(char *param_1)

{
  i8 uVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar2 = _strcmp(param_1,&rules_advance_no_str);
  if (iVar2 == 0) {
    uVar1 = 0xfe;
  }
  else {
    iVar2 = _strcmp(param_1,&rules_advance_nil_str);
    if (iVar2 == 0) {
      uVar1 = 0xff;
    }
    else {
      local_c = -3;
      for (advance = 0; (local_c < 0 && (advance < 100)); advance++) {
        iVar2 = _strcmp(param_1,advances[advance].abbrev);
        if (iVar2 == 0) {
          local_c = advance;
        }
      }
      uVar1 = (i8)local_c;
    }
  }
  return uVar1;
}
#undef local_c
#undef advance

/* 004b07d1 auto */
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define terrain2 (*(int *)(frame_ + FRAME_OFF(8)))
i8 __cdecl rules_parse_terrain_abbrev(char *param_1)

{
  i8 uVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar2 = __strcmpi(param_1,&rules_terrain_no_str);
  if (iVar2 == 0) {
    uVar1 = 0xff;
  }
  else {
    iVar2 = __strcmpi(param_1,&rules_terrain_yes_str);
    if (iVar2 == 0) {
      uVar1 = 0xfe;
    }
    else {
      local_c = -3;
      for (terrain2 = 0; (local_c < 0 && (terrain2 < 0xb)); terrain2++) {
        iVar2 = _strcmp(param_1,terrain_types[terrain2].abbrev);
        if (iVar2 == 0) {
          local_c = terrain2;
        }
      }
      uVar1 = (i8)local_c;
    }
  }
  return uVar1;
}
#undef local_c
#undef terrain2

/* 004bd9f0 auto */
#define advance (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(byte (*)[4])(frame_ + FRAME_OFF(8)))
i32 __cdecl civ_has_advance(iptr civ,iptr param_2)

{
  i32 uVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_2 == -2) {
    uVar1 = 0;
  }
  else if (param_2 < 0) {
    uVar1 = 1;
  }
  else if (param_2 == 0x59) {
    uVar1 = 0;
  }
  else if (param_2 < 100) {
    if (civ < 1) {
      uVar1 = 0;
    }
    else {
      bit_index_split(param_2,(iptr)&advance,(iptr)local_8);
      if ((local_8[0] & civs[civ].advances[advance]) == 0) {
        uVar1 = 0;
      }
      else {
        uVar1 = 1;
      }
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}
#undef advance
#undef local_8

/* 004bdaa5 auto */
i32 __cdecl advance_has_prereq(iptr advance,iptr param_2)

{
  i32 uVar1;
  int iVar2;
  
  if (advance < 0) {
    uVar1 = 0;
  }
  else if (advance == param_2) {
    uVar1 = 1;
  }
  else {
    iVar2 = advance_has_prereq((int)advances[advance].preq[0],param_2);
    if ((iVar2 == 0) &&
       (iVar2 = advance_has_prereq((int)advances[advance].preq[1],param_2), iVar2 == 0)) {
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
  }
  return uVar1;
}

/* 004be6ba auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define ui_large_screen (*(int *)((u8 *)&g.d_00633584))
#define unit (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_50 (*(int *)(frame_ + FRAME_OFF(8)))
#define unit_type3 (*(iptr *)(frame_ + FRAME_OFF(12)))
#define unit_type2 (*(iptr *)(frame_ + FRAME_OFF(16)))
#define acStack_44 (*(char (*)[64])(frame_ + FRAME_OFF(20)))
void __cdecl civ_leonardo_upgrade(iptr civ)

{
  byte unit_type;
  int iVar2;
  i8 frame_[FRAME_OFF(88)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar2 = civ_has_wonder(civ,0xe);
  if (iVar2 != 0) {
    for (unit_type2 = 0; unit_type2 < 0x3e; unit_type2++) {
      acStack_44[unit_type2] = '\0';
    }
    for (unit = 0; unit < game.num_units; unit++) {
      if ((units[unit].id != 0) && (units[unit].owner == civ)) {
        unit_type = units[unit].type;
        local_50 = (int)unit_types[unit_type].obsolete_by;
        if ((unit_types[unit_type].role == 1) &&
           (((char)unit_types[unit_type].defense < (char)unit_types[7].defense &&
            (iVar2 = civ_has_advance(civ,0x23), iVar2 != 0)))) {
          local_50 = 0x23;
        }
        if ((-1 < local_50) && (iVar2 = civ_has_advance(civ,local_50), iVar2 != 0)) {
          unit_type3 = -1;
          for (unit_type2 = 0; unit_type2 < 0x3e; unit_type2++) {
            if (((unit_types[unit_type2].prerequisite == local_50) &&
                (unit_types[units[unit].type].role == unit_types[unit_type2].role)) &&
               ((char)unit_types[units[unit].type].hold <= (char)unit_types[unit_type2].hold)) {
              unit_type3 = unit_type2;
            }
          }
          if (-1 < unit_type3) {
            if ((acStack_44[units[unit].type] == '\0') &&
               ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) {
              acStack_44[units[unit].type] = 1;
              text_set_label_arg(0,unit_types[units[unit].type].name);
              text_set_label_arg(1,unit_types[unit_type3].name);
              text_set_label_arg(2,improvements[0x35].name);
              if ((game.multiplayer < 3) || (human_civ == civ)) {
                dlg_game_txt_with_unit_flags(ADDR(0x62db04, ((u8 *)&g.d_0062db04)),unit_type3,(ui_large_screen == 0) - 1 & 8);
              }
              else {
                net_send_text_args(0x3e,*(i32 *)
                                         (&net_player_slots +
                                         *(int *)(&net_civ_slots + civ * 4) * 0x54),3,0,unit_type3,
                                   ui_large_screen);
              }
            }
            units[unit].type = (u8)unit_type3;
            units[unit].flags = units[unit].flags & 0xdfff;
            map_redraw_tile_all_views((int)units[unit].x,(int)units[unit].y);
            if (2 < game.multiplayer) {
              net_send_state_diff(0xff,2,0,0,0);
              net_send_message(0x72,0xff,(int)units[unit].x,(int)units[unit].y,0,0,0,0,0,0
                                );
            }
          }
        }
      }
    }
  }
  return;
}
#undef human_civ
#undef ui_large_screen
#undef unit
#undef local_50
#undef unit_type3
#undef unit_type2
#undef acStack_44

/* 004bea84 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl civ_advance_gov_prompts(iptr civ,iptr advance)

{
  int iVar1;
  iptr iVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (advance == 0x36) {
    if ((civs[civ].government == 1) &&
       (iVar1 = popup_game_with_sprite(ADDR(0x62db0c, ((u8 *)&g.d_0062db0c)),ADDR(0x6468f0, ((u8 *)&g.d_006468f0)),0), iVar1 == 1)) {
      iVar2 = civ_name_plural(civ);
      text_set_string_arg(0,iVar2);
      popup_game_with_sprite(ADDR(0x62db1c, ((u8 *)&g.d_0062db1c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      civ_set_government(civ,0);
    }
  }
  else if ((((advance == 0x47) || (advance == 0x15)) || (advance == 0xf)) || (advance == 0x1f)) {
    if (((((*(i8 *)((char *)&game.game_options + 1)) & 1) != 0) && (advance == 0x47)) &&
       (civs[civ].government < 3)) {
      popup_file_with_sprite((iptr)PTR_s_TUTORIAL_00627678,ADDR(0x62db28, ((u8 *)&g.d_0062db28)),ADDR(0x643af8, ((u8 *)&g.d_00643af8)),0);
      return;
    }
    if (advance == 0xf) {
      local_8 = 3;
    }
    else if (advance == 0x1f) {
      local_8 = 4;
    }
    else if (advance == 0x47) {
      local_8 = 5;
    }
    else {
      local_8 = 6;
    }
    if ((advance == 0x47) && (civs[civ].government == 5)) {
      return;
    }
    if ((advance == 0xf) && (civs[civ].government == 3)) {
      return;
    }
    if ((advance == 0x1f) && (civs[civ].government == 4)) {
      return;
    }
    if ((civs[civ].government != 6) && (civs[civ].government != '\0')) {
      text_set_label_arg(0,advances[advance].name);
      text_set_label_arg(1,government_names[civs[civ].government]);
      iVar1 = popup_game_with_sprite(ADDR(0x62db34, ((u8 *)&g.d_0062db34)),(iptr)(&government_sprites + local_8 * 0x3c),0);
      if (iVar1 == 1) {
        iVar2 = civ_name_plural(civ);
        text_set_string_arg(0,iVar2);
        popup_game_with_sprite(ADDR(0x62db3c, ((u8 *)&g.d_0062db3c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        civ_set_government(civ,0);
      }
    }
  }
  if (((*(i8 *)((char *)&game.game_options + 1)) & 1) != 0) {
    if (advance == 0x43) {
      popup_file_with_sprite((iptr)PTR_s_TUTORIAL_00627678,ADDR(0x62db48, ((u8 *)&g.d_0062db48)),ADDR(0x643af8, ((u8 *)&g.d_00643af8)),0);
    }
    if (advance == 0x46) {
      popup_file_with_sprite((iptr)PTR_s_TUTORIAL_00627678,ADDR(0x62db54, ((u8 *)&g.d_0062db54)),ADDR(0x643af8, ((u8 *)&g.d_00643af8)),0);
    }
    if (advance == 0x54) {
      popup_file_with_sprite((iptr)PTR_s_TUTORIAL_00627678,ADDR(0x62db60, ((u8 *)&g.d_0062db60)),ADDR(0x643af8, ((u8 *)&g.d_00643af8)),0);
    }
    if (advance == 0x4b) {
      popup_file_with_sprite((iptr)PTR_s_TUTORIAL_00627678,ADDR(0x62db68, ((u8 *)&g.d_0062db68)),ADDR(0x643af8, ((u8 *)&g.d_00643af8)),0);
    }
    if (advance == 0x58) {
      popup_file_with_sprite((iptr)PTR_s_TUTORIAL_00627678,ADDR(0x62db74, ((u8 *)&g.d_0062db74)),ADDR(0x643af8, ((u8 *)&g.d_00643af8)),0);
    }
  }
  return;
}
#undef local_8

/* 004bee56 auto */
#define local_1c (*(int *)(frame_ + FRAME_OFF(4)))
#define city2 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define city (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(24)))
void __cdecl civ_golden_age_popup(iptr civ)

{
  iptr iVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = civ_get_adjective(civ);
  text_set_string_arg(0,iVar1);
  city2 = -1;
  local_c = 0;
  for (city = 0; city < game.num_cities; city++) {
    if ((cities[city].id != 0) && (cities[city].owner == civ)) {
      local_8 = (int)cities[city].size;
      iVar2 = city_has_improvement(city,1);
      if (iVar2 != 0) {
        local_8 = local_8 << 1;
      }
      if (local_8 == 1 || local_8 - 1 < 0) {
        local_1c = 0;
      }
      else {
        local_1c = _rand();
        local_1c = local_1c % local_8;
      }
      if (local_c <= local_1c + 1) {
        city2 = city;
        local_c = local_1c + 1;
      }
    }
  }
  if (-1 < city2) {
    text_set_string_arg(1,(iptr)&cities[city2].name);
    if (2 < game.multiplayer) {
      net_send_text_args(0x54,0xff,2,0,0,0);
    }
    popup_game_with_advance(ADDR(0x62db7c, ((u8 *)&g.d_0062db7c)),0x3c,8);
  }
  return;
}
#undef local_1c
#undef city2
#undef city
#undef local_c
#undef local_8

/* 004bf05b auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define diplo_session_active (*(int *)((u8 *)&g.d_00626a24))
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(4)))
#define advance3 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define city (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_328 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_324 (*(byte (*)[4])(frame_ + FRAME_OFF(20)))
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(24)))
#define local_31c (*(Dialog *)(frame_ + FRAME_OFF(28)))
#define advance2 (*(iptr *)(frame_ + FRAME_OFF(784)))
#define local_24 (*(iptr *)(frame_ + FRAME_OFF(788)))
#define civ4 (*(int *)(frame_ + FRAME_OFF(792)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(796)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(800)))
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(804)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(808)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(812)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(816)))
void __cdecl civ_give_advance(uptr civ,iptr advance,iptr civ2,iptr param_4,int param_5)

{
  iptr iVar1;
  iptr iVar2;
  iptr iVar3;
  int improvement2;
  uptr civ3;
  i8 frame_[FRAME_OFF(824)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  local_1c = 0;
  dialog_ctor(&local_31c,0x4000);
  local_8 = 0;
  if ((((game.multiplayer < 3) || (param_5 != 0)) ||
      ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) == 0)) ||
     (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0 || (human_civ == civ)))
     ) {
    if (civs[civ].researching == advance) {
      civs[civ].researching = -1;
    }
    if ((advance == 0x59) || (99 < advance)) {
      civs[civ].future_techs++;
    }
    else {
      bit_index_split(advance,(iptr)&advance3,(iptr)local_324);
      civs[civ].advances[advance3] =
           civs[civ].advances[advance3] | local_324[0];
      *(i8 *)&civs[civ].advance_source[advance] = (i8)civ2;
      if (game.advance_known_by[advance] == '\0') {
        local_1c = 1;
      }
      game.advance_known_by[advance] =
           game.advance_known_by[advance] | (byte)(1 << ((byte)civ & 0x1f));
    }
    if (game.turn == 0) {
      if (2 < game.multiplayer) {
        net_send_state_diff(0xff,2,0,0,0);
      }
      local_8 = 0xffffffff;
      /* inlined unwind funclet 004bfd9a */ { dialog_dtor((Dialog *)((iptr)&local_31c)); }
    }
    else {
      civs[civ].num_advances++;
      if ((autoplay_active == 0) &&
         ((((human_civ == civ && (civ2 < 0)) ||
           ((human_civ == civ &&
            ((civ == civ2 && (((*(i8 *)((char *)&game.game_options + 2)) & 8) == 0)))))) ||
          ((human_civ != civ &&
           ((((((*(byte *)&civs[human_civ].treaties[civ] & 0x80) != 0 ||
               (iVar1 = civ_has_wonder(human_civ,0x18), iVar1 != 0)) ||
              (iVar2 = civ_has_wonder(human_civ,9), iVar2 != 0)) ||
             (((*(byte *)&civs[human_civ].treaties[civ] & 8) != 0 ||
              (game.reveal_map != '\0')))) &&
            ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0)))))))) {
        dialog_init_default(&local_31c);
        dialog_set_width((DialogWindowView *)&local_31c,0x140);
        text_clear();
        iVar3 = civ_name_plural(civ);
        text_append(iVar3);
        text_append_space();
        if ((civ2 == 0) || (game_language != 2)) {
          text_append_label(0x5f - (uint)(civ2 == 0));
        }
        else {
          text_append(ADDR(0x62db90, ((u8 *)&g.d_0062db90)));
        }
        text_append_space();
        text_append_string_id(advances[advance].name);
        if ((civ2 != 0) && (civ != civ2)) {
          text_append_space();
          if (game_language == 2) {
            text_append(ADDR(0x62db9c, ((u8 *)&g.d_0062db9c)));
          }
          else {
            text_append_label(0x60);
          }
          text_append_space();
          if (civ2 < 0) {
            text_append_string_id(improvements[0x2b].name);
          }
          else {
            iVar3 = civ_name_plural(civ2);
            text_append(iVar3);
          }
        }
        text_append(ADDR(0x62dba4, ((u8 *)&g.d_0062dba4)));
        dialog_add_line
                  ((DialogAddLineView *)&local_31c,ADDR(0x679640, ((u8 *)&g.d_00679640)),0xffffffff,0xffffffff,0xffffffff,0);
        if (diplo_session_active == 0) {
          dialog_add_sprite
                    ((DialogOptionList *)&local_31c,
                     (iptr)(&advance_category_icon_sprites +
                           (char)advances[advance].epoch * 0x3c +
                           (char)advances[advance].category * 0xf0),0,0);
          dialog_set_image_zoom((DialogWindowView *)&local_31c,8);
        }
        local_14 = 0;
        local_328 = 0;
        text_clear();
        if ((human_civ != civ) ||
           ((1 << ((byte)human_civ & 0x1f) & (uint)game.human_players) == 0)) {
          for (improvement = 0; improvement < 0x43; improvement++) {
            if (improvements[improvement].preq == advance) {
              text_list_append_wrapped((iptr)&local_31c,improvements[improvement].name,(iptr)&local_328,
                                 (iptr)&local_14);
            }
          }
          for (unit_type = 0; unit_type < 0x3e; unit_type++) {
            if (unit_types[unit_type].prerequisite == advance) {
              text_list_append_wrapped((iptr)&local_31c,unit_types[unit_type].name,(iptr)&local_328,
                                 (iptr)&local_14);
            }
          }
          if (local_328 != 0) {
            text_append_rparen();
            dialog_add_line
                      ((DialogAddLineView *)&local_31c,ADDR(0x679640, ((u8 *)&g.d_00679640)),0xffffffff,0xffffffff,0xffffffff,0);
          }
        }
        dlg_show_modal(&local_31c,0);
      }
      else if (((autoplay_active == 0) &&
               ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0)) &&
              (((local_1c != 0 &&
                (((improvement2 = rand_range(0,2), improvement2 == 0 &&
                  ((*(byte *)&civs[civ].treaties[human_civ] & 1) != 0)) &&
                 ((*(byte *)&civs[civ].treaties[human_civ] & 8) == 0)))) &&
               ((((*(byte *)&civs[human_civ].treaties[civ] & 0x80) == 0 &&
                 (improvement2 = civ_has_wonder(human_civ,0x18), improvement2 == 0)) &&
                (improvement2 = civ_has_wonder(human_civ,9), improvement2 == 0)))))) {
        improvement2 = diplo_ask_receive_emissary(human_civ,civ,0xffffffff,0xffffffff);
        if (improvement2 != 0) {
          iVar3 = civ_name_plural(civ);
          text_set_string_arg(1,iVar3);
          text_set_label_arg(2,advances[advance].name);
          popup_game(ADDR(0x62dba8, ((u8 *)&g.d_0062dba8)));
        }
        diplo_session_reset();
      }
      if (((((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) &&
           (human_civ == civ)) && (civ2 != 0)) && (autoplay_active == 0)) {
        if (((diplo_session_active == 0) && (((*(i8 *)((char *)&game.game_options + 2)) & 8) != 0)) && (param_4 == 0)) {
          pedia_show_topic_modal((DocumentWindow *)&pedia_window,advance);
        }
        civ_advance_gov_prompts(civ,advance);
      }
      for (advance2 = 0x35; (-1 < advance2 && (advances[advance2].enabled == '\0'));
          advance2 = (iptr)advances[advance2].preq[0]) {
      }
      if ((advance == 0x23) || (advance2 == advance)) {
        local_18 = 0;
        for (city = 0; city < game.num_cities; city++) {
          if ((cities[city].id != 0) && ((int)cities[city].owner == (civ & 0xff))) {
            improvement2 = city_has_improvement(city,2);
            if (improvement2 != 0) {
              local_18++;
            }
            city_set_improvement(city,2,0);
          }
        }
        if (local_18 != 0) {
          local_18 = (uint)improvements[2].cost * (uint)cosmic.shield_box_rows * local_18;
          if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) {
            text_set_label_arg(0,advances[advance].name);
            text_set_number_arg(0,local_18);
            dialog_load_game_text(&local_31c,ADDR(0x62dbb0, ((u8 *)&g.d_0062dbb0)));
            if (diplo_session_active == 0) {
              dialog_add_sprite
                        ((DialogOptionList *)&local_31c,
                         (iptr)(&advance_category_icon_sprites +
                               (char)advances[advance].epoch * 0x3c +
                               (char)advances[advance].category * 0xf0),0,0);
              dialog_add_sprite((DialogOptionList *)&local_31c,ADDR(0x6451d8, ((u8 *)&g.d_006451d8)),0,0);
              dialog_set_image_zoom((DialogWindowView *)&local_31c,8);
            }
            dlg_show_modal(&local_31c,0);
          }
          civs[civ].gold += local_18;
          if (human_civ == civ) {
            status_draw_info(1);
          }
        }
      }
      if (local_1c != 0) {
        if (((advance == 0x3c) &&
            (civs[civ].flags = civs[civ].flags | 0x20, autoplay_active == 0)) &&
           ((human_civ != civ || (civ2 != 0)))) {
          civ_golden_age_popup(civ);
        }
        game.first_discoverer[advance] = game.first_discoverer[advance] | (byte)civ;
        if (autoplay_active == 0) {
          for (local_24 = 0; local_24 < 0x1c; local_24++) {
            if (((wonder_expires[local_24] == advance) &&
                (city = (iptr)game.wonder_city[local_24], -1 < city)) &&
               (((uint)game.human_players & 1 << (cities[city].owner & 0x1fU)) != 0)) {
              improvement2 = local_24 + 0x27;
              text_set_label_arg(0,advances[advance].name);
              text_set_label_arg(1,improvements[improvement2].name);
              dialog_load_game_text(&local_31c,ADDR(0x62dbbc, ((u8 *)&g.d_0062dbbc)));
              if (diplo_session_active == 0) {
                dialog_add_sprite
                          ((DialogOptionList *)&local_31c,
                           (iptr)(&advance_category_icon_sprites +
                                 (char)advances[advance].epoch * 0x3c +
                                 (char)advances[advance].category * 0xf0),0,0);
                dialog_add_sprite
                          ((DialogOptionList *)&local_31c,(iptr)(&improvement_icon_sprites + improvement2 * 0x3c),0,0);
                dialog_set_image_zoom((DialogWindowView *)&local_31c,8);
              }
              if (2 < game.multiplayer) {
                net_send_text_args(0x4d,0xff,2,0,advance,improvement2);
              }
              dlg_show_modal(&local_31c,0);
            }
          }
        }
      }
      civ_leonardo_upgrade(civ);
      civ3 = wonder_get_owner(4);
      if ((0 < (int)civ3) && (improvement2 = civ_has_advance(civ3,advance), improvement2 == 0)) {
        local_18 = 0;
        for (civ4 = 1; civ4 < 8; civ4++) {
          improvement2 = civ_has_advance(civ4,advance);
          if (improvement2 != 0) {
            local_18++;
          }
        }
        if (1 < local_18) {
          civ_give_advance(civ3,advance,-2,0,0);
        }
      }
      if (2 < game.multiplayer) {
        net_send_state_diff(0xff,2,0,0,0);
      }
      local_8 = 0xffffffff;
      /* inlined unwind funclet 004bfd9a */ { dialog_dtor((Dialog *)((iptr)&local_31c)); }
    }
  }
  else {
    net_send_message(0x9b,*(i32 *)
                             (&net_player_slots + *(int *)(&net_civ_slots + civ * 4) * 0x54),civ,
                       advance,civ2,param_4,0,0,0,0);
    local_8 = 0xffffffff;
    /* inlined unwind funclet 004bfd9a */ { dialog_dtor((Dialog *)((iptr)&local_31c)); }
  }
  return;
}
#undef autoplay_active
#undef diplo_session_active
#undef human_civ
#undef improvement
#undef advance3
#undef city
#undef local_328
#undef local_324
#undef unit_type
#undef local_31c
#undef advance2
#undef local_24
#undef civ4
#undef local_1c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004bfdbe auto */
i32 __cdecl civ_can_research_advance(iptr civ,iptr advance)

{
  int iVar1;
  
  if ((((advances[advance].enabled != '\0') &&
       (iVar1 = civ_has_advance(civ,advance), iVar1 == 0)) &&
      (iVar1 = civ_has_advance(civ,(int)advances[advance].preq[0]), iVar1 != 0)) &&
     (iVar1 = civ_has_advance(civ,(int)advances[advance].preq[1]), iVar1 != 0)) {
    return 1;
  }
  return 0;
}

/* 004bfe5a auto */
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(4)))
#define unit_type2 (*(iptr *)(frame_ + FRAME_OFF(8)))
i32 __cdecl civ_can_build_unit(iptr civ,iptr city,iptr unit_type)

{
  char cVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_14 = 0;
  cVar1 = unit_types[unit_type].prerequisite;
  if ((((-2 < cVar1) &&
       ((cVar1 < '\0' || (iVar2 = civ_has_advance(civ,(int)cVar1), iVar2 != 0)))) &&
      (((unit_types[unit_type].obsolete_by < '\0' ||
        (iVar2 = civ_has_advance(civ,(int)unit_types[unit_type].obsolete_by), iVar2 == 0)) &&
       ((((unit_types[unit_type].role != 1 ||
          ((char)unit_types[7].defense <= (char)unit_types[unit_type].defense)) ||
         (iVar2 = civ_has_advance(civ,0x23), iVar2 == 0)) &&
        (((unit_types[unit_type].role != '\0' ||
          ((int)(char)unit_types[unit_type].move != (uint)cosmic.road_move_mult * 2)) ||
         (((char)unit_types[0x13].attack < (char)unit_types[unit_type].attack ||
          (((char)unit_types[0x13].defense <= (char)unit_types[unit_type].defense ||
           (iVar2 = civ_has_advance(civ,(int)unit_types[0x13].prerequisite), iVar2 == 0))))))
        )))))) &&
     ((((char)unit_types[unit_type].attack < 'c' ||
       ((game.wonder_city[0x17] != -1 && (iVar2 = civ_has_advance(civ,0x3a), iVar2 != 0))))
      && (((city < 0 || (unit_types[unit_type].domain != 2)) ||
          (((cities[city].flags & 0x200000) != 0 && ((cities[city].flags & 0x80) != 0))))))))
  {
    if (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) &&
       (((int)(uint)cosmic.road_move_mult < (int)(char)unit_types[unit_type].move &&
        (unit_types[unit_type].domain == '\0')))) {
      for (unit_type2 = 0; unit_type2 < 0x3e; unit_type2++) {
        if (((((unit_type2 != unit_type) && (unit_types[unit_type2].role == unit_types[unit_type].role)) &&
             (unit_types[unit_type2].domain == unit_types[unit_type].domain)) &&
            (((int)(uint)cosmic.road_move_mult < (int)(char)unit_types[unit_type2].move &&
             (iVar2 = civ_has_advance(civ,(int)unit_types[unit_type2].prerequisite), iVar2 != 0
             )))) && (((char)unit_types[unit_type].attack <= (char)unit_types[unit_type2].attack &&
                      ((char)unit_types[unit_type].defense <= (char)unit_types[unit_type2].defense)))) {
          if (unit_types[unit_type2].attack != unit_types[unit_type].attack) {
            return 0;
          }
          if (unit_types[unit_type2].defense != unit_types[unit_type].defense) {
            return 0;
          }
        }
      }
    }
    if ((unit_type != 8) || (civs[civ].government == 4)) {
      local_14 = 1;
    }
  }
  return local_14;
}
#undef local_14
#undef unit_type2

/* 004c02d8 auto */
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(4)))
i32 __cdecl civ_can_build_wonder(iptr civ,iptr param_2)

{
  int iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 0;
  if ((((((game.game_flags & 0x80) == 0) || ((scenario_flags & 4) == 0)) || (game.reveal_map != '\0'))
      || ((((int)(short)scenario_flags & 0x8000U) != 0 && (param_2 == 0x17)))) &&
     ((game.wonder_city[param_2] == -1 &&
      (iVar1 = civ_has_advance(civ,(int)improvements[param_2 + 0x27].preq), iVar1 != 0)))) {
    local_c = 1;
  }
  return local_c;
}
#undef scenario_flags
#undef local_c

/* 004c09b0 auto */
#define local_18 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define advance (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
iptr __cdecl civ_pick_research_advance(iptr civ)

{
  int iVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = -1;
  local_18 = -1;
  local_14 = 0;
  for (advance = 0; advance < 100; advance++) {
    iVar1 = civ_can_research_advance(civ,advance);
    if (((iVar1 != 0) && ((advances[advance].preq[0] != -2 || (advances[advance].preq[1] != -2))))
       && (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0 ||
           (((local_14 == 0 || (game.difficulty == '\0')) ||
            ((int)(advance - (uint)civs[civ].num_advances) % 3 != 0)))))) {
      local_14++;
      if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
        iVar1 = ai_advance_value(civ,advance);
        if (iVar1 == 1 || iVar1 - 1 < 0) {
          local_8 = 0;
        }
        else {
          local_8 = _rand();
          iVar1 = ai_advance_value(civ,advance);
          local_8 = local_8 % iVar1;
        }
      }
      else {
        iVar1 = _rand();
        iVar2 = ai_advance_value(civ,advance);
        local_8 = iVar1 % 3 + iVar2 - 1;
      }
      if (local_c < local_8) {
        local_c = local_8;
        local_18 = advance;
      }
    }
  }
  return local_18;
}
#undef local_18
#undef local_14
#undef advance
#undef local_c
#undef local_8

/* 004c0b51 auto */
#define local_20 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(24)))
i32 __cdecl
research_option_draw_advance(i32 param_1,iptr param_2,iptr advance,byte param_4,int param_5,int param_6,
            int param_7)

{
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = param_5;
  if ((param_4 & 1) != 0) {
    local_c = param_5 + 0x26;
  }
  local_8 = (0x14 - param_7) / 2;
  local_10 = param_6 - local_8;
  sprite_draw
            ((Sprite *)
             (&advance_category_icon_sprites +
             (char)advances[advance].category * 0xf0 + (char)advances[advance].epoch * 0x3c),
             (iptr)local_20,param_2,local_c,local_10);
  return 0;
}
#undef local_20
#undef local_10
#undef local_c
#undef local_8

/* 004c0be8 auto */
#define local_28 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_18 (*(i32 *)(frame_ + FRAME_OFF(16)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(20)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_c (*(int *)(frame_ + FRAME_OFF(28)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(32)))
i32 __cdecl
research_option_draw_unit(i32 param_1,iptr param_2,int param_3,byte param_4,int param_5,int param_6,
            int param_7)

{
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_18 = 0xfffffffe;
  local_10 = param_5;
  if ((param_4 & 1) != 0) {
    local_10 = param_5 + 0x26;
  }
  local_14 = param_6;
  local_8 = gfx_zoom_scale(0x30,0xfffffffe);
  local_c = (local_8 - param_7) / 2;
  local_14 -= local_c;
  gfx_set_zoom_scale(local_18);
  sprite_draw
            ((Sprite *)(&unit_sprites + param_3 * 0x3c),(iptr)local_28,param_2,local_10,
             local_14);
  gfx_reset_zoom_scale();
  return 0;
}
#undef local_28
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 004c0c83 auto */
#define local_20 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(24)))
i32 __cdecl
research_option_draw_improvement(i32 param_1,iptr param_2,int param_3,byte param_4,int param_5,int param_6,
            int param_7)

{
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = param_5;
  if ((param_4 & 1) != 0) {
    local_c = param_5 + 0x26;
  }
  local_8 = (0x14 - param_7) / 2;
  local_10 = param_6 - local_8;
  sprite_draw
            ((Sprite *)(&improvement_icon_sprites + param_3 * 0x3c),(iptr)local_20,param_2,local_c,
             local_10);
  return 0;
}
#undef local_20
#undef local_10
#undef local_c
#undef local_8

/* 004c0cf7 auto */
#define diplo_session_active (*(int *)((u8 *)&g.d_00626a24))
#define aiStack_4c0 (*(iptr (*)[99])(frame_ + FRAME_OFF(0)))
#define aiStack_334 (*(int (*)[4])(frame_ + FRAME_OFF(396)))
#define local_324 (*(iptr *)(frame_ + FRAME_OFF(412)))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(416)))
#define advance (*(iptr *)(frame_ + FRAME_OFF(420)))
#define local_318 (*(int *)(frame_ + FRAME_OFF(424)))
#define local_314 (*(iptr *)(frame_ + FRAME_OFF(428)))
#define local_310 (*(iptr *)(frame_ + FRAME_OFF(432)))
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(436)))
#define local_308 (*(Dialog *)(frame_ + FRAME_OFF(440)))
#define local_14 (*(iptr *)(frame_ + FRAME_OFF(1196)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1200)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1204)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1208)))
void __cdecl civ_research_goal_dialog(iptr civ,int param_2,int civ2)

{
  iptr iVar1;
  int iVar2;
  iptr iVar3;
  i32 uVar4;
  i8 frame_[FRAME_OFF(1216)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_308,0x2000);
  local_8 = 0;
  aiStack_334[1] = 0;
  while( true ) {
    while( true ) {
      local_318 = 0;
      dlg_load_game_section(&local_308,ADDR(0x62dbc8, ((u8 *)&g.d_0062dbc8)),1);
      if (aiStack_334[1] == 0) {
        dialog_set_columns((DialogButtonsView *)&local_308,2);
        if (diplo_session_active == 0) {
          dialog_set_list_indent((DialogCore *)&local_308,0x4b,0);
          dialog_set_option_draw_fn((DialogOptionList *)&local_308,ADDR(0x402f63, research_option_draw_advance));
        }
        for (advance = 0; advance < 100; advance++) {
          if (((advances[advance].enabled != '\0') &&
              (iVar2 = civ_has_advance(civ,advance), iVar2 == 0)) &&
             ((param_2 == 0 ||
              ((civs[civ].researching != advance &&
               ((advances[advance].preq[0] != -2 || (advances[advance].preq[1] != -2)))))))) {
            text_clear();
            text_append_string_id(advances[advance].name);
            if (advance == 0x59) {
              text_append_space();
              text_append_int(civs[civ].future_techs + 1);
            }
            dialog_add_option((DialogOptionList *)&local_308,ADDR(0x679640, ((u8 *)&g.d_00679640)),advance,0);
            local_318++;
          }
        }
      }
      else if (aiStack_334[1] == 1) {
        if (diplo_session_active == 0) {
          dialog_set_list_indent((DialogCore *)&local_308,0x4b,0);
          dialog_set_option_draw_fn((DialogOptionList *)&local_308,ADDR(0x401951, research_option_draw_unit));
        }
        for (unit_type = 0; unit_type < 0x3e; unit_type++) {
          advance = (iptr)unit_types[unit_type].prerequisite;
          if (((-1 < advance) && (iVar2 = civ_has_advance(civ,advance), iVar2 == 0)) &&
             ((param_2 == 0 || (civs[civ].researching != advance)))) {
            text_clear();
            text_append_string_id(unit_types[unit_type].name);
            text_append_space();
            text_append(ADDR(0x62dbd8, ((u8 *)&g.d_0062dbd8)));
            text_append_lparen();
            text_append_string_id(advances[advance].name);
            text_append_rparen();
            dialog_add_option((DialogOptionList *)&local_308,ADDR(0x679640, ((u8 *)&g.d_00679640)),unit_type,0);
            local_318++;
          }
        }
      }
      else if (aiStack_334[1] == 2) {
        if (diplo_session_active == 0) {
          dialog_set_list_indent((DialogCore *)&local_308,0x4b,0);
          dialog_set_option_draw_fn((DialogOptionList *)&local_308,ADDR(0x401776, research_option_draw_improvement));
        }
        for (improvement = 0; improvement < 0x43; improvement++) {
          advance = (iptr)improvements[improvement].preq;
          if (((-1 < advance) && (iVar2 = civ_has_advance(civ,advance), iVar2 == 0)) &&
             ((param_2 == 0 || (civs[civ].researching != advance)))) {
            text_clear();
            text_append_string_id(improvements[improvement].name);
            text_append_space();
            text_append(ADDR(0x62dbdc, ((u8 *)&g.d_0062dbdc)));
            text_append_lparen();
            text_append_string_id(advances[advance].name);
            text_append_rparen();
            dialog_add_option((DialogOptionList *)&local_308,ADDR(0x679640, ((u8 *)&g.d_00679640)),improvement,0);
            local_318++;
          }
        }
      }
      if (local_318 == 0) {
        local_8 = 0xffffffff;
        /* inlined unwind funclet 004c193a */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
        goto LAB_004c1950;
      }
      local_310 = 0;
      if (aiStack_334[1] != 0) {
        iVar1 = label_string(*(i32 *)(label_string_ids + 0x30c));
        dialog_add_button((DialogButtonsView *)&local_308,iVar1);
        aiStack_334[local_310 + 2] = 0;
        local_310++;
      }
      if (aiStack_334[1] != 1) {
        iVar1 = label_string(*(i32 *)(label_string_ids + 0x310));
        dialog_add_button((DialogButtonsView *)&local_308,iVar1);
        aiStack_334[local_310 + 2] = 1;
        local_310++;
      }
      if (aiStack_334[1] != 2) {
        iVar1 = label_string(*(i32 *)(label_string_ids + 0x314));
        dialog_add_button((DialogButtonsView *)&local_308,iVar1);
        aiStack_334[local_310 + 2] = 2;
        local_310++;
      }
      local_324 = dlg_show_modal(&local_308,0);
      if (local_324 < 0) {
        local_8 = 0xffffffff;
        /* inlined unwind funclet 004c193a */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
        goto LAB_004c1950;
      }
      if (local_308.field_dc != 1) break;
      if (diplo_session_active == 0) {
        if (aiStack_334[1] == 0) {
          pedia_show_topic_modal((DocumentWindow *)&pedia_window,local_324);
        }
        else if (aiStack_334[1] == 1) {
          advance = (iptr)unit_types[local_324].prerequisite;
          unit_type = local_324;
          dlg_load_game_section(&local_308,ADDR(0x62dbe0, ((u8 *)&g.d_0062dbe0)),1);
          uVar4 = 0;
          iVar3 = 0;
          iVar1 = label_string(unit_types[unit_type].name);
          dialog_add_option((DialogOptionList *)&local_308,iVar1,iVar3,uVar4);
          uVar4 = 0;
          iVar3 = 1;
          iVar1 = label_string(advances[advance].name);
          dialog_add_option((DialogOptionList *)&local_308,iVar1,iVar3,uVar4);
          local_324 = dlg_show_modal(&local_308,0);
          if (local_324 == 0) {
            pedia_show_unit_modal((DocumentWindow *)&pedia_window,unit_type);
          }
          if (local_324 == 1) {
            pedia_show_topic_modal((DocumentWindow *)&pedia_window,advance);
          }
        }
        else if (aiStack_334[1] == 2) {
          advance = (iptr)improvements[local_324].preq;
          improvement = local_324;
          dlg_load_game_section(&local_308,ADDR(0x62dbe8, ((u8 *)&g.d_0062dbe8)),1);
          uVar4 = 0;
          iVar3 = 0;
          iVar1 = label_string(improvements[improvement].name);
          dialog_add_option((DialogOptionList *)&local_308,iVar1,iVar3,uVar4);
          uVar4 = 0;
          iVar3 = 1;
          iVar1 = label_string(advances[advance].name);
          dialog_add_option((DialogOptionList *)&local_308,iVar1,iVar3,uVar4);
          local_324 = dlg_show_modal(&local_308,0);
          if (local_324 == 0) {
            pedia_show_improvement_modal((DocumentWindow *)&pedia_window,improvement);
          }
          if (local_324 == 1) {
            pedia_show_topic_modal((DocumentWindow *)&pedia_window,advance);
          }
        }
      }
    }
    if (((int)local_308.field_dc < 2) || (3 < (int)local_308.field_dc)) break;
    aiStack_334[1] = aiStack_334[local_308.field_dc];
  }
  if (aiStack_334[1] == 1) {
    local_324 = (iptr)unit_types[local_324].prerequisite;
  }
  else if (aiStack_334[1] == 2) {
    local_324 = (iptr)improvements[local_324].preq;
  }
  local_318 = 0;
  local_314 = 0;
  advance = 0;
  do {
    if (99 < advance) {
      text_set_label_arg(0,advances[local_324].name);
      if (local_314 == 0) {
        if (civ2 == 0) {
          popup_game(ADDR(0x62dbfc, ((u8 *)&g.d_0062dbfc)));
        }
        else {
          popup_game(ADDR(0x62dbf0, ((u8 *)&g.d_0062dbf0)));
        }
        local_8 = 0xffffffff;
        /* inlined unwind funclet 004c193a */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
      }
      else {
        if (civ2 == 0) {
          dialog_load_game_text(&local_308,ADDR(0x62dc18, ((u8 *)&g.d_0062dc18)));
        }
        else {
          dialog_load_game_text(&local_308,ADDR(0x62dc0c, ((u8 *)&g.d_0062dc0c)));
        }
        for (local_14 = 0; local_14 < local_314; local_14++) {
          advance = aiStack_4c0[local_14];
          text_clear();
          text_append_string_id(advances[advance].name);
          if ((local_14 < local_314 - 1) && (2 < local_314)) {
            text_append_comma();
          }
          else if (local_314 - 2 == local_14) {
            text_append_space();
          }
          if (local_314 - 2 == local_14) {
            text_append_label(0xb5);
          }
          if (local_314 - 1 == local_14) {
            text_append_period();
          }
          dialog_add_line
                    ((DialogAddLineView *)&local_308,ADDR(0x679640, ((u8 *)&g.d_00679640)),0xffffffff,0xffffffff,0xffffffff,0);
        }
        dlg_show_modal(&local_308,0);
        local_8 = 0xffffffff;
        /* inlined unwind funclet 004c193a */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
      }
LAB_004c1950:
      return;
    }
    if ((advances[advance].enabled != '\0') &&
       (iVar2 = civ_has_advance(civ,advance), iVar2 == 0)) {
      if (civ2 == 0) {
        iVar2 = civ_has_advance(civ,(int)advances[advance].preq[0]);
        if (((iVar2 != 0) &&
            (iVar2 = civ_has_advance(civ,(int)advances[advance].preq[1]), iVar2 != 0)) &&
           ((param_2 == 0 || (civs[civ].researching != advance)))) {
          if (((local_318 != 0) && (game.difficulty != '\0')) && ((game.game_flags & 0x80) == 0)) {
            iVar2 = (int)(advance - ((uint)civs[civ].num_advances + param_2)) % 3;
            goto joined_r0x004c1729;
          }
          goto LAB_004c1734;
        }
      }
      else {
        iVar2 = civ_has_advance(civ2,advance);
joined_r0x004c1729:
        if (iVar2 != 0) {
LAB_004c1734:
          if ((advances[advance].preq[0] != -2) || (advances[advance].preq[1] != -2)) {
            local_318++;
            iVar2 = advance_has_prereq(local_324,advance);
            if (iVar2 != 0) {
              aiStack_4c0[local_314] = advance;
              local_314++;
            }
          }
        }
      }
    }
    advance++;
  } while( true );
}
#undef diplo_session_active
#undef aiStack_4c0
#undef aiStack_334
#undef local_324
#undef improvement
#undef advance
#undef local_318
#undef local_314
#undef local_310
#undef unit_type
#undef local_308
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004c195e auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define ui_large_screen (*(int *)((u8 *)&g.d_00633584))
#define local_630 (*(int *)(frame_ + FRAME_OFF(0)))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(8)))
#define advance (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_620 (*(iptr *)(frame_ + FRAME_OFF(16)))
#define aiStack_61c (*(iptr (*)[5])(frame_ + FRAME_OFF(20)))
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(40)))
#define local_604 (*(iptr *)(frame_ + FRAME_OFF(44)))
#define local_600 (*(Dialog *)(frame_ + FRAME_OFF(48)))
#define advance3 (*(iptr *)(frame_ + FRAME_OFF(804)))
#define local_308 (*(Dialog *)(frame_ + FRAME_OFF(808)))
#define local_14 (*(iptr *)(frame_ + FRAME_OFF(1564)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1568)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1572)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(1576)))
iptr __cdecl civ_choose_research_dialog(iptr civ,int param_2)

{
  iptr advance2;
  iptr iVar1;
  int iVar4;
  iptr iVar3;
  i8 frame_[FRAME_OFF(1584)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_600,0x4000);
  local_8 = 0;
  dialog_ctor(&local_308,0x4000);
  local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),1);
  local_604 = civ_pick_research_advance(civ);
  if ((param_2 != 0) ||
     (((advance2 = local_604, game.turn != 0 &&
       ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) && (autoplay_active == 0)))) {
    while( true ) {
      advance2 = local_604;
      if ((((*(i8 *)((char *)&game.game_options + 1)) & 2) != 0) && (param_2 == 0)) {
        text_clear();
        text_append_string_id(advances[advance2].name);
        if (advance2 == 0x59) {
          text_append_space();
          text_append_int(civs[civ].future_techs + 1);
        }
        text_set_string_arg(0,ADDR(0x679640, ((u8 *)&g.d_00679640)));
        local_630 = 0;
        local_620 = 0;
        for (unit_type = 0; unit_type < 0x3e; unit_type++) {
          if ((unit_types[unit_type].prerequisite == advance2) && (local_620 < 5)) {
            aiStack_61c[local_620] = unit_type;
            local_620++;
          }
        }
        for (improvement = 1; improvement < 0x43; improvement++) {
          if ((improvements[improvement].preq == advance2) && (local_620 < 5)) {
            aiStack_61c[local_620] = -improvement;
            local_620++;
          }
        }
        if (local_620 == 0) {
          for (advance3 = 0; advance3 < 100; advance3++) {
            if ((advances[advance3].enabled != '\0') &&
               (((advances[advance3].preq[0] == advance2 || (advances[advance3].preq[1] == advance2)) &&
                (local_620 < 5)))) {
              aiStack_61c[local_620] = advance3;
              local_620++;
            }
          }
          if (local_620 != 0) {
            local_630 = 2;
          }
        }
        else {
          local_630 = 1;
        }
        text_clear();
        text_append(ADDR(0x62dc28, ((u8 *)&g.d_0062dc28)));
        text_append_int(local_630);
        dialog_load_text(&local_308,ADDR(0x62dc30, ((u8 *)&g.d_0062dc30)),ADDR(0x679640, ((u8 *)&g.d_00679640)),8);
        dialog_add_sprite
                  ((DialogOptionList *)&local_308,
                   (iptr)(&advance_category_icon_sprites +
                         (char)advances[advance2].epoch * 0x3c + (char)advances[advance2].category * 0xf0)
                   ,(ui_large_screen == 0) - 1 & 8,0);
        if (local_630 != 0) {
          text_clear();
          for (local_14 = 0; local_14 < local_620; local_14++) {
            if (local_630 == 1) {
              unit_type = aiStack_61c[local_14];
              if (unit_type < 0) {
                text_append_string_id(improvements[-unit_type].name);
              }
              else {
                text_append_string_id(unit_types[unit_type].name);
              }
            }
            else {
              text_append_string_id(advances[aiStack_61c[local_14]].name);
            }
            if (local_14 < local_620 - 1) {
              if (local_620 < 3) {
                text_append_space();
              }
              else {
                text_append_comma();
              }
              if (local_620 - 2 == local_14) {
                text_append_label(0xdb);
                text_append_space();
              }
            }
            else {
              text_append_period();
            }
          }
          dialog_add_line
                    ((DialogAddLineView *)&local_308,ADDR(0x679640, ((u8 *)&g.d_00679640)),0xffffffff,0xffffffff,0xffffffff,0);
        }
        iVar1 = timer_ticks();
        dialog_run_modal(&local_308,0,iVar1 - 300);
      }
      iVar4 = civ_has_advance(civ,0x26);
      text_set_label_arg(0,*(i32 *)(label_string_ids + 0xc4 + (uint)(iVar4 == 0) * -4));
      dialog_load_game_text(&local_600,ADDR(0x62dc38, ((u8 *)&g.d_0062dc38)));
      if (((*(i8 *)((char *)&game.game_options + 1)) & 2) != 0) {
        dialog_set_position((DialogCore *)&local_600,5,0xfffffc19);
      }
      dialog_set_option_draw_fn((DialogOptionList *)&local_600,ADDR(0x402f63, research_option_draw_advance));
      dialog_set_list_indent((DialogCore *)&local_600,0x4b,0);
      local_620 = 0;
      for (advance = 0; advance < 100; advance++) {
        if (((((advances[advance].enabled != '\0') &&
              (iVar4 = civ_has_advance(civ,advance), iVar4 == 0)) &&
             ((iVar4 = civ_has_advance(civ,(int)advances[advance].preq[0]), iVar4 != 0 &&
              (iVar4 = civ_has_advance(civ,(int)advances[advance].preq[1]), iVar4 != 0))))
            && ((advances[advance].preq[0] != -2 || (advances[advance].preq[1] != -2)))) &&
           ((local_620 == 0 ||
            ((((game.difficulty == '\0' || (param_2 != 0)) || ((game.game_flags & 0x80) != 0)) ||
             ((int)(advance - (uint)civs[civ].num_advances) % 3 != 0)))))) {
          text_clear();
          text_append_string_id(advances[advance].name);
          if (advance == 0x59) {
            text_append_space();
            text_append_int(civs[civ].future_techs + 1);
          }
          dialog_add_option((DialogOptionList *)&local_600,ADDR(0x679640, ((u8 *)&g.d_00679640)),advance,0);
          local_620++;
        }
      }
      advance2 = local_604;
      if (local_620 == 0) break;
      iVar3 = dialog_run_modal(&local_600,0,300);
      if (((*(i8 *)((char *)&game.game_options + 1)) & 2) != 0) {
        dialog_close(&local_308);
        ui_flush_input();
      }
      if (local_600.field_dc == 2) {
        civ_research_goal_dialog(civ,0,0);
      }
      else {
        advance2 = iVar3;
        if (local_600.field_dc == 0) break;
        pedia_show_topic_modal((DocumentWindow *)&pedia_window,iVar3);
      }
    }
  }
  local_604 = advance2;
  advance2 = local_604;
  civs[civ].researching = (i16)local_604;
  local_8 = local_8 & 0xffffff00;
  /* inlined unwind funclet 004c217c */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
  local_8 = 0xffffffff;
  /* inlined unwind funclet 004c2188 */ { dialog_dtor((Dialog *)((iptr)&local_600)); }
  return advance2;
}
#undef autoplay_active
#undef ui_large_screen
#undef local_630
#undef improvement
#undef advance
#undef local_620
#undef aiStack_61c
#undef unit_type
#undef local_604
#undef local_600
#undef advance3
#undef local_308
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004c21ad auto */
void __cdecl civ_choose_research(iptr civ)

{
  civ_choose_research_dialog(civ,0);
  return;
}

/* 004c21d5 auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define advance (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_304 (*(Dialog *)(frame_ + FRAME_OFF(12)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(768)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(772)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(776)))
iptr __cdecl civ_research_complete(uptr civ,iptr civ2)

{
  short sVar1;
  iptr city;
  iptr iVar3;
  int iVar4;
  i8 frame_[FRAME_OFF(784)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_304,0x4000);
  local_8 = 0;
  sVar1 = civs[civ].researching;
  if (civs[civ].researching < 0) {
    civ_choose_research(civ);
    sVar1 = civs[civ].researching;
  }
  advance = (iptr)sVar1;
  if (advance < 0) {
    local_8 = 0xffffffff;
    /* inlined unwind funclet 004c2763 */ { dialog_dtor((Dialog *)((iptr)&local_304)); }
  }
  else {
    if (research_notice_mode != 2) {
      civs[civ].research_progress = 0;
    }
    civs[civ].researching = -1;
    civ_give_advance(civ,advance,civ2,0,0);
    if ((game.turn == 0) || ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0)) {
      city = citywnd_get_city((WindowObjectView *)&city_window);
      civ_reset_city_production(civ,-1);
      if (((game.turn != 0) && (-1 < city)) &&
         ((city < game.num_cities &&
          ((cities[city].id != 0 && ((int)cities[city].owner == civ)))))) {
        city_recalc(city,0);
      }
      local_8 = 0xffffffff;
      /* inlined unwind funclet 004c2763 */ { dialog_dtor((Dialog *)((iptr)&local_304)); }
    }
    else if ((human_civ == civ) && (autoplay_active == 0)) {
      iVar3 = civ_adjective(civ);
      text_set_string_arg_b(0,iVar3);
      iVar4 = civ_has_advance(civ,0x26);
      text_set_label_arg(1,*(i32 *)(label_string_ids + 0xc4 + (uint)(iVar4 == 0) * -4));
      text_clear();
      text_append_string_id(advances[advance].name);
      if (advance == 0x59) {
        text_append_space();
        text_append_int((uint)civs[civ].future_techs);
      }
      text_set_string_arg_b(2,ADDR(0x679640, ((u8 *)&g.d_00679640)));
      dialog_load_game_text(&local_304,ADDR(0x62dc44, ((u8 *)&g.d_0062dc44)));
      dialog_add_sprite
                ((DialogOptionList *)&local_304,
                 (iptr)(&advance_category_icon_sprites +
                       (char)advances[advance].category * 0xf0 +
                       (char)advances[advance].epoch * 0x3c),0,0);
      dialog_set_image_zoom((DialogWindowView *)&local_304,8);
      dlg_show_modal(&local_304,0);
      if (((*(i8 *)((char *)&game.game_options + 2)) & 8) != 0) {
        pedia_show_topic_modal((DocumentWindow *)&pedia_window,advance);
      }
      if ((((advance == 0x3c) && ((civs[civ].flags & 0x20) != 0)) &&
          (human_civ == civ)) && (autoplay_active == 0)) {
        civ_golden_age_popup(civ);
      }
      if (unit_types[1].prerequisite == advance) {
        popup_game_with_sprite(ADDR(0x62dc50, ((u8 *)&g.d_0062dc50)),ADDR(0x641884, ((u8 *)&g.d_00641884)),8);
      }
      if (advance == 0x12) {
        popup_game_with_sprite(ADDR(0x62dc5c, ((u8 *)&g.d_0062dc5c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      }
      if (improvements[0x20].preq == advance) {
        popup_game_with_sprite(ADDR(0x62dc68, ((u8 *)&g.d_0062dc68)),ADDR(0x6458e0, ((u8 *)&g.d_006458e0)),8);
      }
      if (advance == 0x43) {
        popup_game_with_sprite(ADDR(0x62dc74, ((u8 *)&g.d_0062dc74)),ADDR(0x64292c, ((u8 *)&g.d_0064292c)),8);
      }
      if (improvements[0x18].preq == advance) {
        dialog_load_game_text(&local_304,ADDR(0x62dc80, ((u8 *)&g.d_0062dc80)));
        dialog_add_sprite((DialogOptionList *)&local_304,ADDR(0x645700, ((u8 *)&g.d_00645700)),0,0);
        dialog_add_sprite((DialogOptionList *)&local_304,ADDR(0x6446f4, ((u8 *)&g.d_006446f4)),0,0);
        dlg_show_modal(&local_304,0);
      }
      if (unit_types[0xd].prerequisite == advance) {
        text_set_number_arg_u8(0,CONCAT31(unit_types[0xd].prerequisite >> 7,cosmic.paradrop_range));
        popup_game_with_sprite(ADDR(0x62dc8c, ((u8 *)&g.d_0062dc8c)),ADDR(0x641b54, ((u8 *)&g.d_00641b54)),8);
      }
      if (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) && (game.turn != 0)) {
        civ_choose_research(civ);
        civ_advance_gov_prompts(civ,advance);
      }
      local_8 = 0xffffffff;
      /* inlined unwind funclet 004c2763 */ { dialog_dtor((Dialog *)((iptr)&local_304)); }
    }
    else {
      local_8 = 0xffffffff;
      /* inlined unwind funclet 004c2763 */ { dialog_dtor((Dialog *)((iptr)&local_304)); }
    }
  }
  return advance;
}
#undef autoplay_active
#undef human_civ
#undef advance
#undef local_304
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004c2788 auto */
#define scenario_tech_paradigm (*(short *)((u8 *)&g.d_0064bcb2))
#define scenario_year_increment (*(short *)((u8 *)&g.d_0064bcb4))
#define local_1c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(12)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(16)))
int __cdecl civ_research_cost(iptr civ)

{
  uint uVar1;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  uVar1 = (uint)civs[civ].num_advances + (uint)civs[civ].field_12;
  if (uVar1 < 2) {
    uVar1 = 1;
  }
  local_14 = int_clamp((uint)game.difficulty,0,4);
  if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
    local_14 = 0xe - local_14;
  }
  else {
    local_14 = local_14 * 2 + 6;
  }
  if (((game.game_flags & 0x80) == 0) || (scenario_year_increment == 0)) {
    if (uVar1 < (uint)civs[game.field_138].num_advances + (uint)civs[game.field_138].field_12) {
      if (game.difficulty != '\0') {
        local_14--;
      }
      if (((game.difficulty == 5) &&
          (uVar1 + 4 < (uint)civs[game.field_138].num_advances + (uint)civs[game.field_138].field_12
          )) && (0x96 < game.turn)) {
        local_14--;
      }
    }
    else {
      local_14 = local_14 +
                 (int)(uVar1 - ((uint)civs[game.field_138].num_advances +
                               (uint)civs[game.field_138].field_12)) / 3;
    }
    local_10 = 0;
    if (0x13 < uVar1) {
      local_10 = int_clamp(uVar1 - ((int)((int)game.turn + ((int)game.turn >> 0x1f & 7U))
                                            >> 3),0,6);
    }
    local_14 += local_10;
  }
  if ((game.game_flags & 0x80) == 0) {
    if (cosmic.tech_paradigm != '\n') {
      local_14 = (int)((uint)cosmic.tech_paradigm * local_14) / 10;
    }
  }
  else if (scenario_tech_paradigm != 10) {
    local_14 = (scenario_tech_paradigm * local_14) / 10;
  }
  local_1c = local_14 * 3 >> 2;
  if ((uint)civs[civ].num_advances + (uint)civs[civ].field_12 < 0x14) {
    local_1c = (int)(((uint)civs[civ].num_advances + (uint)civs[civ].field_12) * local_1c) /
               0x14;
  }
  local_14 += local_1c;
  if (0x43 < game.num_advances) {
    local_14 = (local_14 * 0x43) / (int)game.num_advances;
  }
  if ((game.game_flags & 4) != 0) {
    local_14 = (int)(local_14 * 5 + (local_14 * 5 >> 0x1f & 3U)) >> 2;
  }
  if ((game.game_flags & 8) != 0) {
    local_14 = (local_14 << 2) / 5;
  }
  if (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) &&
     (local_14 < (int)(0xb - uVar1))) {
    local_14 = 0xb - uVar1;
  }
  local_18 = local_14 * uVar1;
  if ((local_18 < 1) || (32000 < local_18)) {
    local_18 = 32000;
  }
  return local_18;
}
#undef scenario_tech_paradigm
#undef scenario_year_increment
#undef local_1c
#undef local_18
#undef local_14
#undef local_10

/* 004c2b73 auto */
void __cdecl civ_add_research_points(uptr civ,int param_2)

{
  short sVar1;
  int iVar2;
  
  if (0 < param_2) {
    civs[civ].research_progress += (short)param_2;
    if (-1 < civs[civ].researching) {
      sVar1 = civs[civ].research_progress;
      iVar2 = civ_research_cost(civ);
      if (iVar2 <= sVar1) {
        civ_research_complete(civ,0);
      }
      if ((civs[civ].flags & 0x20) != 0) {
        civs[civ].flags = civs[civ].flags & 0xffdf;
        civ_research_complete(civ,0);
      }
    }
    if ((civs[civ].research_progress != 0) && (civs[civ].researching < 0)) {
      if ((((*(i8 *)((char *)&game.game_options + 1)) & 1) != 0) &&
         ((civs[civ].num_advances < 2 &&
          ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)))) {
        popup_file_with_sprite((iptr)PTR_s_TUTORIAL_00627678,ADDR(0x62dc98, ((u8 *)&g.d_0062dc98)),ADDR(0x643af8, ((u8 *)&g.d_00643af8)),0);
      }
      civ_choose_research(civ);
    }
  }
  return;
}

/* 004c65d2 auto */
#define city (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
int __cdecl civ_distance_to_capital(iptr civ,i32 param_2,i32 param_3)

{
  int iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0x10;
  for (city = 0; city < game.num_cities; city++) {
    if ((((cities[city].id != 0) && (cities[city].owner == civ)) &&
        (iVar1 = city_has_improvement(city,1), iVar1 != 0)) &&
       (iVar1 = map_distance_diag((int)cities[city].x,(int)cities[city].y,param_2,param_3),
       iVar1 < local_8)) {
      local_8 = iVar1;
    }
  }
  return local_8;
}
#undef city
#undef local_8

/* 004ccab9 auto */
#define rules_edit_section_names_i32 (*(i32 *)((u8 *)&g.d_006a1880))
#define rules_edit_section_writers_i32 (*(i32 *)((u8 *)&g.d_006a1884))
#define rules_edit_next_name_i32 (*(i32 *)((u8 *)&g.d_006a1888))
#define rules_edit_next_writer_i32 (*(i32 *)((u8 *)&g.d_006a188c))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl rules_edit_set_section(iptr param_1,iptr param_2)

{
  rules_edit_section_names_i32 = param_1;
  rules_edit_section_writers_i32 = param_2;
  rules_edit_next_name_i32 = 0;
  rules_edit_next_writer_i32 = 0;
  return;
}
#undef rules_edit_section_names_i32
#undef rules_edit_section_writers_i32
#undef rules_edit_next_name_i32
#undef rules_edit_next_writer_i32

/* 004ccaed auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl rules_edit_add_section(iptr param_1,iptr param_2)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; (*(int *)(&rules_edit_section_names + local_8 * 8) != 0 && (local_8 < 7));
      local_8 = local_8 + 1) {
  }
  if (local_8 < 7) {
    *(iptr *)(&rules_edit_section_names + local_8 * 8) = param_1;
    *(iptr *)(&rules_edit_section_writers + local_8 * 8) = param_2;
    *(i32 *)(&rules_edit_next_name + local_8 * 8) = 0;
    *(i32 *)(&rules_edit_next_writer + local_8 * 8) = 0;
  }
  return;
}
#undef local_8

/* 004ccf2d auto */
#define local_278 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define local_274 (*(char (*)[80])(frame_ + FRAME_OFF(4)))
#define local_224 (*(FILE * *)(frame_ + FRAME_OFF(84)))
#define local_220 (*(FILE * *)(frame_ + FRAME_OFF(88)))
#define local_21c (*(char (*)[260])(frame_ + FRAME_OFF(92)))
#define local_118 (*(i8 (*)[16])(frame_ + FRAME_OFF(352)))
#define local_108 (*(int *)(frame_ + FRAME_OFF(368)))
#define s (*(char (*)[256])(frame_ + FRAME_OFF(372)))
i32 __cdecl rules_write_sections(void)

{
  iptr iVar1;
  iptr iVar2;
  int iVar3;
  char *pcVar4;
  size_t sVar5;
  char *lpCaption;
  UINT uType;
  i8 frame_[FRAME_OFF(632)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_108 = 0;
  local_278 = 0;
  local_224 = (FILE *)0x0;
  local_220 = (FILE *)0x0;
  crt_strcpy(local_118,s_RULES__0062e04c);
  crt_strcat(local_118,&lang_file_ext);
  __getcwd(local_21c,0x104);
  __chdir(&scenario_dir_path);
  iVar1 = _strcmp(&scenario_dir_path,&game_home_dir);
  if ((iVar1 == 0) || (iVar2 = file_exists((iptr)local_118), iVar2 == 0)) {
    __chdir(&game_home_dir);
    local_220 = (FILE *)file_open_path((iptr)local_118,ADDR(0x62e08c, ((u8 *)&g.d_0062e08c)));
    iVar3 = _strcmp(&scenario_dir_path,&game_home_dir);
    if (iVar3 == 0) {
      iVar3 = file_exists(ADDR(0x62e090, ((u8 *)&g.d_0062e090)));
      if ((iVar3 != 0) && (iVar3 = crt_remove(s_RULES_BAK_0062e09c), iVar3 != 0))
      goto LAB_004cd353;
      local_224 = (FILE *)file_open_path(ADDR(0x62e0ac, ((u8 *)&g.d_0062e0ac)),ADDR(0x62e0a8, ((u8 *)&g.d_0062e0a8)));
      uType = 0x40;
      lpCaption = s_Warning_0062e0b8;
      pcVar4 = s_Saving_changes_in_file_RULES_BAK_0062e0c0;
      iVar3 = wnd_get_window((WndBase *)(active_editor_wnd + 0x48));
      MessageBoxA(*(HWND *)(iVar3 + 4),pcVar4,lpCaption,uType);
    }
    else {
      __chdir(&scenario_dir_path);
      local_224 = (FILE *)file_open_path((iptr)local_118,ADDR(0x62e0e4, ((u8 *)&g.d_0062e0e4)));
    }
  }
  else {
    iVar3 = file_exists(ADDR(0x62e054, ((u8 *)&g.d_0062e054)));
    if (((iVar3 != 0) && (iVar3 = crt_remove(s_RULES_BAK_0062e060), iVar3 != 0)) ||
       (iVar3 = crt_rename(local_118,s_RULES_BAK_0062e06c), iVar3 != 0)) goto LAB_004cd353;
    local_220 = (FILE *)file_open_path(ADDR(0x62e07c, ((u8 *)&g.d_0062e07c)),ADDR(0x62e078, ((u8 *)&g.d_0062e078)));
    local_224 = (FILE *)file_open_path((iptr)local_118,ADDR(0x62e088, ((u8 *)&g.d_0062e088)));
  }
  if ((local_220 != (FILE *)0x0) && (local_224 != (FILE *)0x0)) {
    for (; *(int *)(&rules_edit_section_names + local_108 * 8) != 0; local_108++) {
      local_274[0] = '@';
      local_274[1] = 0;
      crt_strcat(local_274,*(i32 *)(&rules_edit_section_names + local_108 * 8));
      __strupr(local_274);
      do {
        pcVar4 = _fgets(s,0x100,local_220);
        if ((pcVar4 == (char *)0x0) || (iVar3 = _fputs(s,local_224), iVar3 == -1))
        goto LAB_004cd353;
        str_strip_newline((iptr)s);
        str_trim((iptr)s);
        iVar3 = __strcmpi(s,local_274);
      } while (iVar3 != 0);
      if (*(int *)(&rules_edit_section_writers + local_108 * 8) != 0) {
        (**(code **)(&rules_edit_section_writers + local_108 * 8))(local_224,local_220);
      }
      do {
        pcVar4 = _fgets(s,0x100,local_220);
        if (pcVar4 == (char *)0x0) goto LAB_004cd353;
        sVar5 = _strlen(s);
      } while (1 < sVar5);
      iVar3 = _fputs(s,local_224);
      if (iVar3 == -1) goto LAB_004cd353;
    }
    do {
      pcVar4 = _fgets(s,0x100,local_220);
      if (pcVar4 == (char *)0x0) {
        local_278 = 1;
        break;
      }
      iVar3 = _fputs(s,local_224);
    } while (iVar3 != -1);
  }
LAB_004cd353:
  if (local_220 != (FILE *)0x0) {
    _fclose(local_220);
  }
  if (local_224 != (FILE *)0x0) {
    _fclose(local_224);
  }
  __chdir(local_21c);
  return local_278;
}
#undef local_278
#undef local_274
#undef local_224
#undef local_220
#undef local_21c
#undef local_118
#undef local_108
#undef s

/* 004e1314 auto */
#define double_moves_applied (*(int *)((u8 *)&g.d_00628068))
#define mp_double_moves (*(short *)((u8 *)&g.d_00654fae))
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl rules_apply_double_moves(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (((game.multiplayer == '\0') || (mp_double_moves == 0)) || (double_moves_applied != 0)) {
    if (((game.multiplayer != '\0') && (mp_double_moves == 0)) && (double_moves_applied == 1)) {
      double_moves_applied = 0;
      for (unit_type = 0; unit_type < 0x3e; unit_type++) {
        if (unit_types[unit_type].domain == '\0') {
          unit_types[unit_type].move = (char)unit_types[unit_type].move / 2;
        }
      }
      status_redraw(1);
    }
  }
  else {
    double_moves_applied = 1;
    for (unit_type = 0; unit_type < 0x3e; unit_type++) {
      if (unit_types[unit_type].domain == '\0') {
        unit_types[unit_type].move = unit_types[unit_type].move * 2;
      }
    }
    status_redraw(1);
  }
  return;
}
#undef double_moves_applied
#undef mp_double_moves
#undef unit_type

/* 004e1763 auto */
#define civ_eliminate_busy (*(i32 *)((u8 *)&g.d_006ad8ec))
#define game_loop_active (*(i8 *)((u8 *)&g.d_00628044))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define mp_kill_civ_on_retire (*(short *)((u8 *)&g.d_00654c76))
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define net_kill_or_quit_ack (*(int *)((u8 *)&g.d_006c90b4))
#define unit (*(iptr *)(frame_ + FRAME_OFF(4)))
#define city (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_28 (*(uint *)(frame_ + FRAME_OFF(16)))
#define y3 (*(int *)(frame_ + FRAME_OFF(24)))
#define x2 (*(int *)(frame_ + FRAME_OFF(28)))
#define unit2 (*(iptr *)(frame_ + FRAME_OFF(32)))
#define local_14 (*(byte *)(frame_ + FRAME_OFF(36)))
#define city2 (*(iptr *)(frame_ + FRAME_OFF(44)))
void __cdecl civ_eliminate(iptr civ,i32 param_2,i32 param_3)

{
  uint *puVar1;
  char *pcVar2;
  short x3;
  short y4;
  bool bVar5;
  int iVar6;
  int y2;
  iptr x;
  int y;
  int iVar10;
  uint uVar11;
  iptr iVar12;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  bVar5 = false;
  civ_eliminate_busy = 1;
  if ((game.multiplayer < 3) || (net_host_flag != '\0')) {
    game.human_players = game.human_players & ~(byte)(1 << ((byte)civ & 0x1f));
    if (2 < game.multiplayer) {
      net_send_message(0x31,0,0,civ,0,0,0,0,0,0);
    }
    if ((mp_kill_civ_on_retire != 0) || ((char)param_2 != '\0')) {
      net_batch_begin();
      for (unit = 0; unit < game.num_units; unit++) {
        if (units[unit].id != 0) {
          if (((units[unit].owner == civ) || ((units[unit].flags & 2) == 0)) ||
             ((char)units[unit].counter != civ)) {
            if (units[unit].owner == civ) {
              if ((-1 < civ) && (unit < 0x800)) {
                if ((civs[civ].num_military_units != 0) &&
                   ((char)unit_types[units[unit].type].role < 5)) {
                  civs[civ].num_military_units--;
                }
                if (*(char *)&civs[civ].units_active[units[unit].type] != '\0') {
                  pcVar2 = (char *)(units[unit].type + ADDR(0x64c778, ((u8 *)&civs + 216)) + civ * 0x594);
                  *pcVar2 = *pcVar2 - 1;
                }
                if (*(int *)(&civ_unit_counts + civ * 4) != 0) {
                  *(int *)(&civ_unit_counts + civ * 4) = *(int *)(&civ_unit_counts + civ * 4) - 1
                  ;
                }
              }
              if (-1 < units[unit].prev_in_stack) {
                units[units[unit].prev_in_stack].next_in_stack = units[unit].next_in_stack;
                bVar5 = true;
              }
              if (-1 < units[unit].next_in_stack) {
                units[units[unit].next_in_stack].prev_in_stack = units[unit].prev_in_stack;
                bVar5 = true;
              }
              if ((!bVar5) &&
                 (iVar6 = map_in_bounds((int)units[unit].x,(int)units[unit].y), iVar6 != 0))
              {
                tile_set_improvements((int)units[unit].x,(int)units[unit].y,1,0,1);
              }
              units[unit].prev_in_stack = -1;
              units[unit].next_in_stack = -1;
              units[unit].x = (units[unit].owner * 4 + 4) * -0x19;
              units[unit].y = (units[unit].owner * 4 + 4) * -0x19;
              units[unit].id = 0;
              if (game.num_units - 1 == unit) {
                game.num_units--;
              }
              for (unit2 = 0; unit2 < game.num_units; unit2++) {
                if ((units[unit2].orders == 3) && (units[unit2].goto_x == unit)) {
                  units[unit2].orders = -1;
                }
              }
            }
          }
          else {
            units[unit].flags = units[unit].flags & 0xfffd;
            puVar1 = (uint *)(civ * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + (char)units[unit].counter * 4);
            *puVar1 = *puVar1 & 0xfeffffff;
            spy_try_escape(unit,0,(int)(char)units[unit].counter);
          }
        }
      }
      for (city = 0; city < game.num_cities; city++) {
        if ((cities[city].id != 0) && (cities[city].owner == civ)) {
          iVar6 = (int)cities[city].x;
          y2 = (int)cities[city].y;
          civ = (iptr)cities[city].owner;
          civs[civ].num_cities--;
          cities[city].id = 0;
          if (game.num_cities - 1 == city) {
            game.num_cities--;
          }
          for (city2 = 0; city2 < game.num_cities; city2++) {
            if (cities[city2].id != 0) {
              unit = (iptr)(char)cities[city2].trade_routes;
              while (unit = unit - 1, -1 < unit) {
                if (cities[city2].route_partner[unit] == city) {
                  city_remove_trade_route(city2,unit);
                }
              }
            }
          }
          for (city2 = 0; city2 < 0x1c; city2++) {
            if (game.wonder_city[city2] == city) {
              game.wonder_city[city2] = -2;
            }
          }
          local_28 = 0;
          tile_set_improvements(iVar6,y2,2,0,1);
          for (city2 = 0; city2 < 0x2d; city2++) {
            x = map_wrap_x((char)(&city_tile_dx_table)[city2] + iVar6);
            y = (char)(&city_tile_dy_table)[city2] + y2;
            iVar10 = map_in_bounds(x,y);
            if ((iVar10 != 0) && (iVar10 = tile_is_ocean(x,y), iVar10 == 0)) {
              iVar12 = 1;
              uVar11 = tile_get_fertility(x,y);
              tile_set_fertility(x,y,uVar11 | 8,iVar12);
              if (city2 < 0x15) {
                iVar10 = tile_radius_civ(x,y);
                if (iVar10 == civ) {
                  tile_set_radius_civ(x,y,0,1);
                }
                y = tile_city_or_unit_owner(x,y);
                if ((0 < y) && (y != civ)) {
                  local_14 = (byte)y;
                  local_28 = local_28 | 1 << (local_14 & 0x1f);
                }
              }
            }
          }
          if (local_28 != 0) {
            for (unit = tile_first_unit(iVar6,y2); -1 < unit;
                unit = unit_next_in_stack(unit)) {
              units[unit].visibility = units[unit].visibility | (byte)local_28;
            }
          }
        }
      }
      for (city = 0; city < game.num_cities; city++) {
        x3 = cities[city].x;
        y4 = cities[city].y;
        for (city2 = 0; city2 < 0x2d; city2++) {
          x = map_wrap_x((int)(char)(&city_tile_dx_table)[city2] + (int)x3);
          iVar6 = (int)(char)(&city_tile_dy_table)[city2] + (int)y4;
          y2 = map_in_bounds(x,iVar6);
          if (y2 != 0) {
            iVar12 = 1;
            uVar11 = tile_get_fertility(x,iVar6);
            tile_set_fertility(x,iVar6,uVar11 & 7,iVar12);
            if (city2 < 0x15) {
              tile_set_radius_civ(x,iVar6,civ,1);
            }
          }
        }
      }
      civ_reset_spaceship(civ);
      game.civs_alive = game.civs_alive & ~(byte)(1 << ((byte)civ & 0x1f));
      for (x2 = 0; x2 < map.width; x2++) {
        for (y3 = 0; y3 < map.height; y3++) {
          tile_set_visible(x2,y3,1 << ((byte)civ & 0x1f),0,1);
        }
      }
      net_batch_flush();
    }
    passwords_unscramble();
    (&civ_passwords)[civ * 0x20] = 0;
    passwords_scramble();
    if (2 < game.multiplayer) {
      snd_cd_stop();
      net_send_state_diff(0xff,2,0,0,0);
      XD_FlushSendBuffer(5000);
    }
    if ((~(1 << ((byte)civ & 0x1f)) & (uint)game.human_players) == 0) {
      civ_eliminate_busy = 0;
    }
    else {
      if ((char)param_3 != '\0') {
        civ_create(civ);
      }
      if (2 < game.multiplayer) {
        net_send_state_diff(0xff,2,0,0,0);
        net_send_message(0x74,0xff,0,0,0,0,0,0,0,0);
      }
      map_redraw_all_views(human_civ,1);
      civ_eliminate_busy = 0;
    }
  }
  else {
    civ_eliminate_busy = 0;
    net_kill_or_quit_ack = -2;
    net_send_message(0x34,0,civ,0,0,0,0,0,0,0);
    iVar6 = timer_ticks();
    while ((net_kill_or_quit_ack == -2 && (y2 = timer_ticks(), y2 - iVar6 < 0xe10))) {
      net_process_messages((NetSession *)&net_session,1,1);
    }
    if (net_kill_or_quit_ack == -2) {
      dbg_log(ADDR(0x62ebc4, ((u8 *)&g.d_0062ebc4)));
      popup_game_with_sprite(ADDR(0x62ebf4, ((u8 *)&g.d_0062ebf4)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      game_loop_active = 0;
    }
    else {
      dbg_log(ADDR(0x62ec08, ((u8 *)&g.d_0062ec08)));
    }
    while ((net_msgq_priority_count != 0 || (net_msgq_normal_count != 0))) {
      net_process_messages((NetSession *)&net_session,1,0);
    }
  }
  return;
}
#undef civ_eliminate_busy
#undef game_loop_active
#undef human_civ
#undef mp_kill_civ_on_retire
#undef net_host_flag
#undef net_kill_or_quit_ack
#undef unit
#undef city
#undef local_28
#undef y3
#undef x2
#undef unit2
#undef local_14
#undef city2

/* 004ec312 auto */
#define civ2 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl civ_apply_eiffel_tower(iptr civ)

{
  uint *puVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((civs[civ].flags & 0x10) == 0) {
    civs[civ].reputation = civs[civ].reputation >> 1;
    civs[civ].flags = civs[civ].flags | 0x10;
    for (civ2 = 1; civ2 < 8; civ2++) {
      if (civ2 != civ) {
        civ_adjust_attitude(civ2,civ,0xffffffe7);
        puVar1 = (uint *)(civ2 * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ * 4);
        *puVar1 = *puVar1 & 0xffffffef;
      }
    }
  }
  return;
}
#undef civ2

/* 004f00f0 auto */
#define advance (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(8)))
uint __cdecl civ_improvement_upkeep(iptr civ,iptr improvement)

{
  int iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = (uint)improvements[improvement].upkeep;
  if (improvement == 2) {
    if ((game.difficulty < 2) && (local_8 != 0)) {
      local_8--;
    }
    iVar1 = civ_has_advance(civ,0x23);
    if (iVar1 != 0) {
      local_8++;
    }
    for (advance = 0x35; (-1 < advance && (advances[advance].enabled == '\0'));
        advance = (iptr)advances[advance].preq[0]) {
    }
    iVar1 = civ_has_advance(civ,advance);
    if (iVar1 != 0) {
      local_8++;
    }
  }
  if (local_8 == 1) {
    iVar1 = civ_has_wonder(civ,0x11);
    if (iVar1 != 0) {
      local_8 = 0;
    }
  }
  if (((local_8 != 0) && (civs[civ].government == 4)) &&
     ((improvement == 4 || ((improvement == 0xe || (improvement == 0xb)))))) {
    local_8 = 0;
  }
  return local_8;
}
#undef advance
#undef local_8

/* 0055c066 auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define city (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl civ_set_government(iptr civ,iptr param_2)

{
  uint *puVar1;
  u8 uVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  uVar2 = civs[civ].government;
  civs[civ].government = (u8)param_2;
  if (civs[civ].government != uVar2) {
    if ((civs[civ].government == '\0') ||
       ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0)) {
      for (local_8 = 0; local_8 < 8; local_8++) {
        puVar1 = (uint *)(civ * 4 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + local_8 * 0x594);
        *puVar1 = *puVar1 & 0xffffffef;
      }
    }
    if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) {
      game.field_06 = game.field_06 & 0xfffb;
      for (city = 0; city < game.num_cities; city++) {
        if ((((cities[city].id != 0) && (cities[city].owner == civ)) &&
            (city_recalc(city,1), cities[city].building == 8)) &&
           (civs[civ].government != 4)) {
          cities[city].building = 11;
        }
      }
    }
  }
  if ((((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) && (0 < param_2)) &&
     (autoplay_active == 0)) {
    taxrate_dialog_show(civ);
  }
  return;
}
#undef autoplay_active
#undef city
#undef local_8

/* 0055c277 auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
i32 __cdecl
civ_can_choose_government(iptr civ,iptr param_2,i32 param_3,i32 param_4,i32 param_5,
            iptr param_6,iptr param_7,i32 param_8,iptr param_9,iptr param_10,iptr param_11,
            i32 param_12,iptr param_13,i32 param_14,i32 param_15,
            i32 param_16,i32 param_17,i32 param_18,i32 param_19,
            i32 param_20,i32 param_21)

{
  int iVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 1;
  iVar1 = civ_has_wonder(civ,0x13);
  switch(param_2) {
  case 2:
    iVar2 = civ_has_advance(civ,0x36);
    if ((iVar2 == 0) && (iVar1 == 0)) {
      local_8 = 0;
    }
    break;
  case 3:
    iVar2 = civ_has_advance(civ,0xf);
    if ((iVar2 == 0) && (iVar1 == 0)) {
      local_8 = 0;
    }
    break;
  case 4:
    iVar2 = civ_has_advance(civ,0x1f);
    if ((iVar2 == 0) && (iVar1 == 0)) {
      local_8 = 0;
    }
    if (advances[0x1f].enabled == '\0') {
      local_8 = 0;
    }
    break;
  case 5:
    iVar2 = civ_has_advance(civ,0x47);
    if ((iVar2 == 0) && (iVar1 == 0)) {
      local_8 = 0;
    }
    break;
  case 6:
    iVar2 = civ_has_advance(civ,0x15);
    if ((iVar2 == 0) && (iVar1 == 0)) {
      local_8 = 0;
    }
  }
  return local_8;
}
#undef local_8

/* 0055c3d3: written by hand in src/game/unwind.c */

/* 0055c69d auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define ui_large_screen (*(int *)((u8 *)&g.d_00633584))
#define local_10 (*(int *)(frame_ + FRAME_OFF(0)))
#define civ2 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(uptr *)(frame_ + FRAME_OFF(8)))
void __cdecl civ_change_government(iptr civ,uptr param_2)

{
  iptr iVar1;
  int iVar2;
  uint uVar3;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  uVar3 = (uint)civs[civ].government;
  if (param_2 != 0) {
    civs[civ].flags = civs[civ].flags | 8;
  }
  if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
    if ((uVar3 != param_2) || ((civs[civ].flags & 1) != 0)) {
      iVar1 = civ_adjective(civ);
      text_set_string_arg_b(0,iVar1);
      text_set_label_arg(1,government_names[param_2]);
      iVar1 = civ_leader_name(civ);
      text_set_string_arg(2,iVar1);
      iVar1 = civ_leader_title(civ);
      text_set_string_arg(3,iVar1);
      local_10 = 0;
      if (((*(byte *)&civs[human_civ].treaties[civ] & 0x80) != 0) ||
         (((iVar2 = civ_has_wonder(human_civ,0x18), iVar2 != 0 ||
           (iVar2 = civ_has_wonder(human_civ,9), iVar2 != 0)) || (game.reveal_map != '\0')))
         ) {
        if (((civs[civ].flags & 1) == 0) || (autoplay_active != 0)) {
          if (autoplay_active == 0) {
            popup_game_with_sprite(ADDR(0x633af4, ((u8 *)&g.d_00633af4)),(iptr)(&government_sprites + uVar3 * 0x3c),
                               (ui_large_screen == 0) - 1 & 8);
            civs[civ].flags = civs[civ].flags | 1;
          }
        }
        else {
          popup_game_with_sprite(ADDR(0x633aec, ((u8 *)&g.d_00633aec)),(iptr)(&government_sprites + param_2 * 0x3c),
                             (ui_large_screen == 0) - 1 & 8);
          civs[civ].flags = civs[civ].flags & 0xfffe;
        }
        if ((int)param_2 < 4) {
          local_8 = param_2;
        }
        else {
          local_8 = param_2 - 1;
        }
        civs[civ].tax_rate = 4 - (char)((int)local_8 >> 1);
      }
      if (2 < game.multiplayer) {
        for (civ2 = 1; civ2 < 8; civ2++) {
          if ((((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) &&
              (human_civ != civ2)) &&
             ((game.reveal_map != '\0' ||
              ((((*(byte *)&civs[civ2].treaties[civ] & 0x80) != 0 ||
                (iVar2 = civ_has_wonder(civ2,0x18), iVar2 != 0)) ||
               (iVar2 = civ_has_wonder(civ2,9), iVar2 != 0)))))) {
            if (((civs[civ].flags & 1) == 0) || (autoplay_active != 0)) {
              net_send_text_args(0x2c,*(i32 *)
                                       (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54
                                       ),1,0,uVar3,(ui_large_screen == 0) - 1 & 8);
              civs[civ].flags = civs[civ].flags | 1;
              local_10++;
            }
            else {
              net_send_text_args(0x2b,*(i32 *)
                                       (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54
                                       ),4,0,param_2,(ui_large_screen == 0) - 1 & 8);
              civs[civ].flags = civs[civ].flags & 0xfffe;
              local_10++;
            }
          }
        }
      }
      if (local_10 != 0) {
        if ((int)param_2 < 4) {
          local_8 = param_2;
        }
        else {
          local_8 = param_2 - 1;
        }
        civs[civ].tax_rate = 4 - (char)((int)local_8 >> 1);
      }
    }
  }
  else if (param_2 != 0) {
    civ_select_government_dialog(civ,0);
    return;
  }
  civ_set_government(civ,param_2);
  return;
}
#undef autoplay_active
#undef human_civ
#undef ui_large_screen
#undef local_10
#undef civ2
#undef local_8

/* 00560084 auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define local_20 (*(int *)(frame_ + FRAME_OFF(0)))
#define civ4 (*(uptr *)(frame_ + FRAME_OFF(12)))
#define civ2 (*(uptr *)(frame_ + FRAME_OFF(16)))
#define civ3 (*(int *)(frame_ + FRAME_OFF(20)))
void __cdecl civ_turn_update_diplomacy(uptr civ)

{
  uint *puVar1;
  u8 uVar2;
  int iVar3;
  iptr iVar4;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  uVar2 = civs[civ].government;
  civs[civ].flags = civs[civ].flags & 0xffb7;
  if (uVar2 == '\0') {
    if (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) || ((game.turn & 3U) != 0))
    {
      if ((((game.turn & 3U) == 0) || (iVar3 = civ_has_wonder(civ,0x13), iVar3 != 0)) &&
         (civ_change_government(civ,1),
         (1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) {
        civs[civ].flags = civs[civ].flags & 0xfffe;
      }
    }
    else if ((civs[civ].flags & 1) == 0) {
      civ_change_government(civ,1);
    }
    else {
      civs[civ].flags = civs[civ].flags & 0xfffe;
    }
  }
  if (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) &&
     ((civs[civ].flags & 1) != 0)) {
    civ_change_government(civ,(uint)civs[civ].government);
  }
  if (civ != 0) {
    iVar3 = _rand();
    civs[civ].field_16 = (u8)(iVar3 % 100);
    iVar3 = _rand();
    if (iVar3 % 3 == 0) {
      civs[civ].flags = civs[civ].flags ^ 4;
    }
    if (((int)game.turn % 3 == 0) && (civs[civ].field_1f != '\0')) {
      civs[civ].field_1f--;
    }
    for (civ2 = 1; (int)civ2 < 8; civ2++) {
      if (2 < game.multiplayer) {
        net_process_messages((NetSession *)&net_session,1,0);
      }
      if ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 0x40) == 0) {
        *(i32 *)(&diplo_recent_peace_table + civ2 * 4) = 0;
      }
      else {
        *(i32 *)(&diplo_recent_peace_table + civ2 * 4) = 1;
      }
      puVar1 = (uint *)(civ * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ2 * 4);
      *puVar1 = *puVar1 & 0xff5fbfff;
      if ((((1 << ((byte)civ2 & 0x1f) & (uint)game.civs_alive) != 0) && (civ2 != civ))
         && ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0)) {
        if ((*(byte *)&civs[civ].treaties[civ2] & 0x20) != 0) {
          iVar3 = int_clamp(3 - ((int)(uint)civs[civ2].reputation >> 2),1,3);
          if (iVar3 - 1 < 1) {
            local_20 = 0;
          }
          else {
            local_20 = _rand();
            local_20 = local_20 % iVar3;
          }
          if (local_20 == 0) {
            if ((*(byte *)&civs[civ].treaties[civ2] & 8) == 0) {
              puVar1 = (uint *)(civ * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ2 * 4);
              *puVar1 = *puVar1 & 0xffffffd9;
              puVar1 = (uint *)(civ * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ2 * 4);
              *puVar1 = *puVar1 | 0x80840;
              iVar3 = (int)civs[civ2].last_treaty_turn[civ];
              if (iVar3 <= game.turn - 8) {
                iVar3 = game.turn - 8;
              }
              civs[civ2].last_treaty_turn[civ] = (short)iVar3;
            }
            else {
              civ_adjust_attitude(civ,civ2,100);
              civs[civ2].last_treaty_turn[civ] = 0xffff;
              puVar1 = (uint *)(civ * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ2 * 4);
              *puVar1 = *puVar1 & 0xffffffdf;
            }
          }
        }
        if ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) == 0) {
          puVar1 = (uint *)(civ * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ2 * 4);
          *puVar1 = *puVar1 & 0xfffbffff;
          if ((game.turn & 0x1fU) == 0) {
            if ((*(byte *)(civ * 0x594 + ADDR(0x64c6c2, ((u8 *)&civs + 34)) + civ2 * 4) & 8) == 0) {
              puVar1 = (uint *)(civ * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ2 * 4);
              *puVar1 = *puVar1 & 0xfffff7ff;
            }
            puVar1 = (uint *)(civ * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ2 * 4);
            *puVar1 = *puVar1 & 0xfff7ffff;
          }
          if ((game.turn & 0xfU) == 0) {
            if ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 4) == 0) {
              if ((*(byte *)&civs[civ].treaties[civ2] & 8) == 0) {
                if (((*(byte *)&civs[civ].treaties[civ2] & 4) == 0) ||
                   ((game.game_flags & 1) == 0)) {
                  if (((*(byte *)&civs[civ].treaties[civ2] & 1) != 0) &&
                     ((((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 0x20) != 0 &&
                       ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 8) == 0)) &&
                      ((*(byte *)(civ * 4 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 0x594) & 8) == 0)))) {
                    if (((((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) &&
                         ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) == 0)) &&
                        (((*(byte *)&civs[human_civ].treaties[civ] & 0x80) != 0 ||
                         (((iVar3 = civ_has_wonder(human_civ,0x18), iVar3 != 0 ||
                           (iVar3 = civ_has_wonder(human_civ,9), iVar3 != 0)) ||
                          (((*(byte *)&civs[human_civ].treaties[civ2] & 0x80) != 0
                           || (((iVar3 = civ_has_wonder(human_civ,0x18), iVar3 != 0 ||
                                (iVar3 = civ_has_wonder(human_civ,9), iVar3 != 0)) ||
                               (game.reveal_map != '\0')))))))))) && (autoplay_active == 0)) {
                      iVar4 = civ_name_plural(civ);
                      text_set_string_arg(0,iVar4);
                      iVar4 = civ_name_plural(civ2);
                      text_set_string_arg(1,iVar4);
                      popup_game_with_sprite(ADDR(0x633c4c, ((u8 *)&g.d_00633c4c)),ADDR(0x647748, ((u8 *)&g.d_00647748)),0);
                    }
                    if (2 < game.multiplayer) {
                      for (civ3 = 1; civ3 < 8; civ3++) {
                        if ((((1 << ((byte)civ3 & 0x1f) & (uint)game.human_players) != 0) &&
                            (human_civ != civ3)) &&
                           (((game.reveal_map != '\0' ||
                             (((*(byte *)&civs[civ3].treaties[civ] & 0x80) != 0 ||
                              ((*(byte *)&civs[civ3].treaties[civ2] & 0x80) != 0)))
                             ) || ((iVar3 = civ_has_wonder(civ3,0x18), iVar3 != 0 ||
                                   (iVar3 = civ_has_wonder(civ3,9), iVar3 != 0)))))) {
                          iVar4 = civ_name_plural(civ);
                          text_set_string_arg(0,iVar4);
                          iVar4 = civ_name_plural(civ2);
                          text_set_string_arg(1,iVar4);
                          net_send_text_args(0x50,*(i32 *)
                                                   (&net_player_slots +
                                                   *(int *)(&net_civ_slots + civ3 * 4) * 0x54),2,0
                                             ,0,0);
                        }
                      }
                    }
                  }
                }
                else {
                  diplo_civs_meet(civ,civ2,0,0);
                }
              }
              else {
                diplo_ai_swap_advances(civ,civ2);
              }
              if (((((*(byte *)&civs[civ].treaties[civ2] & 1) != 0) &&
                   ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 8) == 0)) &&
                  ((*(byte *)(civ * 4 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 0x594) & 8) == 0)) &&
                 (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0 ||
                  ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) == 0)))) {
                diplo_clear_treaty_flags(civ,civ2,1);
              }
            }
            puVar1 = (uint *)(civ * 0x594 + ADDR(0x64c6c0, ((u8 *)&civs + 32)) + civ2 * 4);
            *puVar1 = *puVar1 & 0xfffffbff;
          }
          else if ((((game.turn & 7U) == 0) &&
                   ((*(byte *)&civs[civ].treaties[civ2] & 8) != 0)) &&
                  ((*(byte *)(civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + civ2 * 4) & 4) == 0)) {
            diplo_ai_swap_advances(civ,civ2);
          }
        }
      }
    }
    if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
      for (civ2 = 1; (int)civ2 < 8; civ2++) {
        if (2 < game.multiplayer) {
          net_process_messages((NetSession *)&net_session,1,0);
        }
        if ((((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) && (autoplay_active == 0)
            ) && ((*(byte *)&civs[civ].treaties[civ2] & 1) != 0)) {
          if (human_civ == civ2) {
            diplo_ai_review_relations(civ,civ2);
          }
          else if (2 < game.multiplayer) {
            net_send_message(0xa0,*(i32 *)
                                     (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54)
                               ,civ,civ2,0,0,0,0,0,0);
          }
        }
      }
      diplo_ai_military_aid(civ);
      for (civ4 = 1; (int)civ4 < 8; civ4++) {
        if (2 < game.multiplayer) {
          net_process_messages((NetSession *)&net_session,1,0);
        }
        if ((1 << ((byte)civ4 & 0x1f) & (uint)game.human_players) != 0) {
          if (human_civ == civ4) {
            diplo_ai_seek_war_ally(civ,civ4);
          }
          else if (2 < game.multiplayer) {
            net_send_message(0xa1,*(i32 *)
                                     (&net_player_slots + *(int *)(&net_civ_slots + civ4 * 4) * 0x54)
                               ,civ,civ4,0,0,0,0,0,0);
          }
        }
      }
    }
  }
  return;
}
#undef autoplay_active
#undef human_civ
#undef local_20
#undef civ4
#undef civ2
#undef civ3

/* 00568861 auto */
i32 __cdecl civ_city_art_era(iptr civ)

{
  int iVar1;
  
  iVar1 = civ_has_advance(civ,5);
  if ((iVar1 != 0) && (iVar1 = civ_has_advance(civ,0x18), iVar1 != 0)) {
    return 2;
  }
  iVar1 = civ_has_advance(civ,0x3c);
  if ((iVar1 != 0) && (iVar1 = civ_has_advance(civ,0x26), iVar1 != 0)) {
    return 1;
  }
  return 0;
}

/* 0056e1f0 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
i32 __cdecl civ_color_mid(iptr civ)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (civ == 0) {
    local_8 = 0;
  }
  else {
    local_8 = (int)leaders[civs[civ].tribe].color;
  }
  return *(i32 *)(&civ_mid_colors + local_8 * 0x10);
}
#undef local_8

/* 0057a27a auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define scenario_flags (*(ushort *)((u8 *)&g.d_0064bc60))
#define local_318 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define advance (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_30c (*(Dialog *)(frame_ + FRAME_OFF(12)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(768)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(772)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(776)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(780)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(784)))
void __cdecl civ_steal_advance(iptr civ,iptr civ2)

{
  int iVar1;
  iptr iVar2;
  bool bVar3;
  i32 uVar4;
  iptr iVar4;
  i8 frame_[FRAME_OFF(792)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  local_318 = -1;
  local_18 = -999;
  dialog_ctor(&local_30c,0x4000);
  local_8 = 0;
  if ((civ == 0) || (civ2 == 0)) {
    local_8 = 0xffffffff;
    /* inlined unwind funclet 0057a661 */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
  }
  else {
    bVar3 = human_civ == civ;
    if (autoplay_active != 0) {
      bVar3 = false;
    }
    while( true ) {
      if (bVar3) {
        dialog_load_game_text(&local_30c,ADDR(0x634380, ((u8 *)&g.d_00634380)));
      }
      for (advance = 0; advance < 100; advance++) {
        iVar1 = civ_has_advance(civ,advance);
        if ((((iVar1 == 0) && (iVar1 = civ_has_advance(civ2,advance), iVar1 != 0)) &&
            ((((game.game_flags & 0x80) == 0 || ((scenario_flags & 0x10) == 0)) ||
             ((((advance != 0x1f && (advance != 0x36)) && (advance != 0xf)) &&
              ((advance != 0x47 && (advance != 0x15)))))))) &&
           ((advances[advance].preq[0] != -2 || (advances[advance].preq[1] != -2)))) {
          if (bVar3) {
            uVar4 = 0;
            iVar4 = advance;
            iVar2 = label_string(advances[advance].name);
            dialog_add_option((DialogOptionList *)&local_30c,iVar2,iVar4,uVar4);
          }
          local_14 = ai_advance_value(civ,advance);
          if (local_18 <= local_14) {
            local_318 = advance;
            local_18 = local_14;
          }
        }
      }
      if (local_318 < 0) {
        local_8 = 0xffffffff;
        /* inlined unwind funclet 0057a661 */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
        goto LAB_0057a677;
      }
      advance = local_318;
      if (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) ||
         (advance = dlg_show_modal(&local_30c,0), local_30c.field_dc == 0))
      break;
      civ_research_goal_dialog(civ,0,civ2);
    }
    if ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0) {
      iVar2 = civ_name_plural(civ);
      text_set_string_arg(0,iVar2);
      text_set_label_arg(1,advances[advance].name);
      if ((autoplay_active == 0) && ((1 << ((byte)civ2 & 0x1f) & (uint)game.human_players) != 0)) {
        if (human_civ == civ2) {
          popup_game_with_advance(ADDR(0x634388, ((u8 *)&g.d_00634388)),advance,0);
        }
        else if (2 < game.multiplayer) {
          net_send_text_args(99,*(i32 *)
                                 (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),2,0,
                             advance,0);
        }
      }
    }
    civ_give_advance(civ,advance,civ2,0,0);
    if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) {
      civ_reset_city_production(civ,-1);
    }
    local_8 = 0xffffffff;
    /* inlined unwind funclet 0057a661 */ { dialog_dtor((Dialog *)((iptr)&local_30c)); }
  }
LAB_0057a677:
  return;
}
#undef autoplay_active
#undef human_civ
#undef scenario_flags
#undef local_318
#undef advance
#undef local_30c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0057a685 auto */
#define local_18 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define city (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(8)))
#define city2 (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(16)))
iptr __cdecl civ_find_central_city(iptr civ)

{
  int iVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_10 = 0x7fff;
  local_18 = -1;
  for (city = 0; city < game.num_cities; city++) {
    if ((cities[city].id != 0) && (cities[city].owner == civ)) {
      local_8 = 0;
      for (city2 = 0; city2 < game.num_cities; city2++) {
        if ((cities[city2].id != 0) && (cities[city2].owner == civ)) {
          iVar1 = map_distance_diag((int)cities[city].x,(int)cities[city].y,
                                     (int)cities[city2].x,(int)cities[city2].y);
          local_8 += iVar1;
        }
      }
      if (local_8 < local_10) {
        local_10 = local_8;
        local_18 = city;
      }
    }
  }
  return local_18;
}
#undef local_18
#undef city
#undef local_10
#undef city2
#undef local_8

/* 0057a904 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define x3 (*(int *)(frame_ + FRAME_OFF(4)))
#define y2 (*(uint *)(frame_ + FRAME_OFF(8)))
#define local_154 (*(iptr *)(frame_ + FRAME_OFF(12)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(16)))
#define city4 (*(iptr *)(frame_ + FRAME_OFF(20)))
#define civ3 (*(iptr *)(frame_ + FRAME_OFF(24)))
#define city3 (*(iptr *)(frame_ + FRAME_OFF(28)))
#define city (*(uptr *)(frame_ + FRAME_OFF(32)))
#define aiStack_13c (*(int (*)[64])(frame_ + FRAME_OFF(36)))
#define local_3c (*(iptr *)(frame_ + FRAME_OFF(292)))
#define local_38 (*(byte *)(frame_ + FRAME_OFF(296)))
#define x2 (*(uint *)(frame_ + FRAME_OFF(300)))
#define local_30 (*(byte *)(frame_ + FRAME_OFF(304)))
#define local_2c (*(iptr *)(frame_ + FRAME_OFF(308)))
#define local_28 (*(Tile * *)(frame_ + FRAME_OFF(312)))
#define civ2 (*(iptr *)(frame_ + FRAME_OFF(316)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(320)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(324)))
#define advance (*(iptr *)(frame_ + FRAME_OFF(328)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(332)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(336)))
#define local_c (*(int *)(frame_ + FRAME_OFF(340)))
#define y3 (*(int *)(frame_ + FRAME_OFF(344)))
i32 __cdecl civ_civil_war(iptr civ)

{
  char civ4;
  iptr iVar2;
  i32 uVar2;
  iptr iVar3;
  int city2;
  iptr iVar5;
  i8 frame_[FRAME_OFF(352)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar2 = events_check_no_schism((ScenarioEvents *)&scenario_events,civ);
  if (iVar2 == 0) {
    uVar2 = 0;
  }
  else {
    civ2 = -1;
    for (civ3 = 1; civ3 < 8; civ3++) {
      if ((civs[civ3].num_military_units == 0) && (civs[civ3].num_cities == 0)) {
        civ2 = civ3;
      }
    }
    if (civ2 < 1) {
      uVar2 = 0;
    }
    else {
      for (local_3c = 0; local_3c < 0x40; local_3c++) {
        aiStack_13c[local_3c] = 0;
      }
      local_154 = -1;
      for (city = 0; (int)city < (int)game.num_cities; city++) {
        if ((cities[city].id != 0) && (cities[city].owner == civ)) {
          local_3c = tile_landmass((int)cities[city].x,(int)cities[city].y);
          aiStack_13c[local_3c] += (int)cities[city].size;
          iVar3 = city_has_improvement(city,1);
          if ((iVar3 != 0) && ((local_154 < 0 || (civs[civ].capital_x == cities[city].x))))
          {
            local_154 = local_3c;
            x3 = (int)cities[city].x;
            y3 = (int)cities[city].y;
            city3 = city;
          }
        }
      }
      if (local_154 < 0) {
        uVar2 = 0;
      }
      else {
        game.civs_alive = game.civs_alive & ~(byte)(1 << ((byte)civ2 & 0x1f));
        city2 = civ_create(civ2);
        if (city2 == 0) {
          uVar2 = 0;
        }
        else {
          game.civs_alive = game.civs_alive | (byte)(1 << ((byte)civ2 & 0x1f));
          iVar5 = civ_get_adjective(civ);
          text_set_string_arg(0,iVar5);
          iVar5 = civ_get_adjective(civ2);
          text_set_string_arg(1,iVar5);
          popup_game(ADDR(0x634390, ((u8 *)&g.d_00634390)));
          if (2 < game.multiplayer) {
            net_send_text_args(0x16,0xff,2,0,0,0);
          }
          civs[civ2].gold = civs[civ].gold / 2;
          civs[civ].gold -= civs[civ2].gold;
          civs[civ2].military_strength = (u16)((int)(uint)civs[civ].military_strength >> 1);
          civs[civ2].government = civs[civ].government;
          civs[civ2].research_progress = civs[civ].research_progress;
          civs[civ2].num_advances = civs[civ].num_advances;
          for (advance = 0; advance < 0xd; advance++) {
            *(i8 *)&civs[civ2].advances[advance] =
                 *(i8 *)&civs[civ].advances[advance];
          }
          for (civ3 = 1; civ3 < 8; civ3++) {
            civs[civ3].last_treaty_turn[civ2] = game.turn - 8;
          }
          *(i32 *)&civs[civ2].treaties[civ] = 0x2001;
          *(i32 *)&civs[civ].treaties[civ2] = 0x82801;
          local_28 = map_tiles;
          local_30 = (byte)(1 << ((byte)civ & 0x1f));
          local_38 = (byte)(1 << ((byte)civ2 & 0x1f));
          y2 = 0;
          x2 = 0;
          net_batch_begin();
          for (advance = 0; advance < map.area; advance++) {
            city2 = tile_at(x2,y2);
            if ((local_30 & *(byte *)(city2 + 4)) != 0) {
              tile_set_visible(x2,y2,(uint)local_38,1,1);
            }
            x2 += 2;
            if ((int)map.width <= (int)x2) {
              y2++;
              x2 = y2 & 1;
            }
          }
          net_batch_flush();
          local_14 = aiStack_13c[local_154];
          local_20 = 0;
          for (local_3c = 0; local_3c < 0x40; local_3c++) {
            if (aiStack_13c[local_3c] != 0) {
              if ((local_14 < local_20) || (local_154 == local_3c)) {
                if (local_154 != local_3c) {
                  local_14 += aiStack_13c[local_3c];
                }
                aiStack_13c[local_3c] = 1;
              }
              else {
                local_20 += aiStack_13c[local_3c];
                aiStack_13c[local_3c] = 2;
              }
            }
          }
          if ((local_14 < local_20 * 2) && (local_20 <= local_14)) {
            for (city = 0; (int)city < (int)game.num_cities; city++) {
              if ((cities[city].id != 0) && (cities[city].owner == civ)) {
                local_3c = tile_landmass((int)cities[city].x,(int)cities[city].y);
                if (aiStack_13c[local_3c] == 2) {
                  city_reveal_to_civ(city,civ);
                  city_transfer_for_civil_war(city,civ,civ2);
                }
                else {
                  city_reveal_to_civ(city,civ2);
                }
              }
            }
          }
          else {
            local_20 = 0;
            local_10 = (int)civs[civ].total_city_size;
            while (local_20 * 3 < local_10) {
              local_c = 1;
              city4 = -1;
              for (city = 0; (int)city < (int)game.num_cities; city++)
              {
                if ((cities[city].id != 0) && (cities[city].owner == civ)) {
                  city_reveal_to_civ(city,civ2);
                  city_reveal_to_civ(city,civ);
                  local_1c = map_distance_diag(x3,y3,(int)cities[city].x,
                                                (int)cities[city].y);
                  if (local_c < local_1c) {
                    city4 = city;
                    local_c = local_1c;
                  }
                }
              }
              if (city4 < 0) break;
              local_20 += cities[city4].size;
              city_transfer_for_civil_war(city4,civ,civ2);
            }
          }
          for (unit = 0; unit < game.num_units; unit++) {
            if ((units[unit].id != 0) && (units[unit].owner == civ)) {
              city = city_at((int)units[unit].x,(int)units[unit].y);
              if (((int)city < 0) && (units[unit].home_city != -1)) {
                city = (uptr)(byte)units[unit].home_city;
              }
              if (-1 < (int)city) {
                civ4 = cities[city].owner;
                city2 = (int)civ4;
                if ((city2 == civ) || (city2 == civ2)) {
                  tile_set_owner((int)units[unit].x,(int)units[unit].y,city2,1);
                  local_2c = unit;
                  for (unit = unit_stack_first(unit); -1 < unit;
                      unit = unit_next_in_stack(unit)) {
                    units[unit].owner = civ4;
                    if ((units[unit].home_city != -1) &&
                       (cities[(byte)units[unit].home_city].owner != city2)) {
                      units[unit].home_city = (i8)city;
                    }
                  }
                  unit = local_2c;
                }
              }
            }
          }
          city2 = civ_find_central_city(civ2);
          if (-1 < city2) {
            city_set_improvement(city2,1,1);
            civs[civ2].capital_x = cities[city2].x;
          }
          cities[city3].owner = -1;
          city2 = civ_find_central_city(civ);
          if (-1 < city2) {
            city_set_improvement(city2,1,1);
            civs[civ].capital_x = cities[city2].x;
          }
          cities[city3].owner = (byte)civ;
          if (2 < game.multiplayer) {
            net_send_state_diff(0xff,2,0,0,0);
            net_send_message(0x74,0xff,0,0,0,0,0,0,0,0);
          }
          map_redraw_all_views(human_civ,1);
          uVar2 = 1;
        }
      }
    }
  }
  return uVar2;
}
#undef human_civ
#undef x3
#undef y2
#undef local_154
#undef unit
#undef city4
#undef civ3
#undef city3
#undef city
#undef aiStack_13c
#undef local_3c
#undef local_38
#undef x2
#undef local_30
#undef local_2c
#undef local_28
#undef civ2
#undef local_20
#undef local_1c
#undef advance
#undef local_14
#undef local_10
#undef local_c
#undef y3

/* 005866a0 auto */
void __cdecl cosmic_editor_focus_redraw(void)

{
  HWND hWnd;
  
  hWnd = (HWND)control_get_hwnd((ControlHwndView *)(active_editor_wnd + 0xa94));
  SetFocus(hWnd);
  cosmic_editor_draw_bg((FrameWindow *)active_editor_wnd);
  return;
}

/* 005866d3 auto */
#define cosmic_edit_values (*(u8 *)((u8 *)&g.d_006a2d80))
#define editor_items_i32 (*(i32 *)((u8 *)&g.d_006a2d28))
#define editor_item_field1_i32 (*(i32 *)((u8 *)&g.d_006a2d2c))
#define editor_item_field2_i32 (*(i32 *)((u8 *)&g.d_006a2d30))
#define editor_item_field3_i32 (*(i32 *)((u8 *)&g.d_006a2d34))
#define editor_item_field4_i32 (*(i32 *)((u8 *)&g.d_006a2d38))
#define editor_item_field5_i32 (*(i32 *)((u8 *)&g.d_006a2d3c))
#define editor_item_field6_i32 (*(i32 *)((u8 *)&g.d_006a2d40))
#define editor_item_field7_i32 (*(i32 *)((u8 *)&g.d_006a2d44))
#define editor_item_field8_i32 (*(i32 *)((u8 *)&g.d_006a2d48))
#define editor_item_field9_i32 (*(i32 *)((u8 *)&g.d_006a2d4c))
#define editor_item_field10_i32 (*(i32 *)((u8 *)&g.d_006a2d50))
#define editor_item_field11_i32 (*(i32 *)((u8 *)&g.d_006a2d54))
#define editor_item_flags_i32 (*(i32 *)((u8 *)&g.d_006a2d58))
#define editor_item_field13_i32 (*(i32 *)((u8 *)&g.d_006a2d5c))
#define editor_item_field14_i32 (*(i32 *)((u8 *)&g.d_006a2d60))
#define editor_item_field15_i32 (*(i32 *)((u8 *)&g.d_006a2d64))
#define editor_item_field16_i32 (*(i32 *)((u8 *)&g.d_006a2d68))
#define editor_item_field17_i32 (*(i32 *)((u8 *)&g.d_006a2d6c))
#define editor_item_field18_i32 (*(i32 *)((u8 *)&g.d_006a2d70))
#define editor_item_field19_i32 (*(i32 *)((u8 *)&g.d_006a2d74))
#define editor_item_field20_i32 (*(i32 *)((u8 *)&g.d_006a2d78))
#define editor_item_field21_i32 (*(i32 *)((u8 *)&g.d_006a2d7c))
#define cosmic_edit_values_i32 (*(i32 *)((u8 *)&g.d_006a2d80))
#define cosmic_edit_trireme_loss_i32 (*(i32 *)((u8 *)&g.d_006a2d84))
#define cosmic_edit_food_per_citizen_i32 (*(i32 *)((u8 *)&g.d_006a2d88))
#define cosmic_edit_food_box_rows_i32 (*(i32 *)((u8 *)&g.d_006a2d8c))
#define cosmic_edit_shield_box_rows_i32 (*(i32 *)((u8 *)&g.d_006a2d90))
#define cosmic_edit_settler_food_low_i32 (*(i32 *)((u8 *)&g.d_006a2d94))
#define cosmic_edit_settler_food_high_i32 (*(i32 *)((u8 *)&g.d_006a2d98))
#define cosmic_edit_unhappy_size_i32 (*(i32 *)((u8 *)&g.d_006a2d9c))
#define cosmic_edit_riot_factor_i32 (*(i32 *)((u8 *)&g.d_006a2da0))
#define cosmic_edit_aqueduct_size_i32 (*(i32 *)((u8 *)&g.d_006a2da4))
#define cosmic_edit_sewer_size_i32 (*(i32 *)((u8 *)&g.d_006a2da8))
#define cosmic_edit_tech_paradigm_i32 (*(i32 *)((u8 *)&g.d_006a2dac))
#define cosmic_edit_transform_time_i32 (*(i32 *)((u8 *)&g.d_006a2db0))
#define cosmic_edit_monarchy_support_i32 (*(i32 *)((u8 *)&g.d_006a2db4))
#define cosmic_edit_communism_support_i32 (*(i32 *)((u8 *)&g.d_006a2db8))
#define cosmic_edit_fundamentalism_support_i32 (*(i32 *)((u8 *)&g.d_006a2dbc))
#define cosmic_edit_communism_palace_dist_i32 (*(i32 *)((u8 *)&g.d_006a2dc0))
#define cosmic_edit_fund_science_loss_i32 (*(i32 *)((u8 *)&g.d_006a2dc4))
#define cosmic_edit_change_penalty_i32 (*(i32 *)((u8 *)&g.d_006a2dc8))
#define cosmic_edit_paradrop_range_i32 (*(i32 *)((u8 *)&g.d_006a2dcc))
#define cosmic_edit_mass_thrust_paradigm_i32 (*(i32 *)((u8 *)&g.d_006a2dd0))
#define cosmic_edit_fund_max_science_i32 (*(i32 *)((u8 *)&g.d_006a2dd4))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl cosmic_editor_capture_defaults(void)

{
  cosmic_edit_values_i32 = (uint)cosmic.road_move_mult;
  cosmic_edit_trireme_loss_i32 = (uint)cosmic.trireme_loss_chance;
  cosmic_edit_food_per_citizen_i32 = (uint)cosmic.food_per_citizen;
  cosmic_edit_food_box_rows_i32 = (uint)cosmic.food_box_rows;
  cosmic_edit_shield_box_rows_i32 = (uint)cosmic.shield_box_rows;
  cosmic_edit_settler_food_low_i32 = (uint)cosmic.settler_food_low;
  cosmic_edit_settler_food_high_i32 = (uint)cosmic.settler_food_high;
  cosmic_edit_unhappy_size_i32 = (uint)cosmic.unhappy_size;
  cosmic_edit_riot_factor_i32 = (uint)cosmic.riot_factor;
  cosmic_edit_aqueduct_size_i32 = (uint)cosmic.aqueduct_size;
  cosmic_edit_sewer_size_i32 = (uint)cosmic.sewer_size;
  cosmic_edit_tech_paradigm_i32 = (uint)cosmic.tech_paradigm;
  cosmic_edit_transform_time_i32 = (uint)cosmic.transform_time;
  cosmic_edit_monarchy_support_i32 = (uint)cosmic.monarchy_free_support;
  cosmic_edit_communism_support_i32 = (uint)cosmic.communism_free_support;
  cosmic_edit_fundamentalism_support_i32 = (uint)cosmic.fundamentalism_free_support;
  cosmic_edit_communism_palace_dist_i32 = (uint)cosmic.communism_palace_dist;
  cosmic_edit_fund_science_loss_i32 = (uint)cosmic.fund_science_loss;
  cosmic_edit_change_penalty_i32 = (uint)cosmic.change_penalty;
  cosmic_edit_paradrop_range_i32 = (uint)cosmic.paradrop_range;
  cosmic_edit_mass_thrust_paradigm_i32 = (uint)cosmic.mass_thrust_paradigm;
  cosmic_edit_fund_max_science_i32 = (uint)cosmic.fund_max_science;
  rules_load_cosmic();
  editor_items_i32 = (uint)cosmic.road_move_mult;
  editor_item_field1_i32 = (uint)cosmic.trireme_loss_chance;
  editor_item_field2_i32 = (uint)cosmic.food_per_citizen;
  editor_item_field3_i32 = (uint)cosmic.food_box_rows;
  editor_item_field4_i32 = (uint)cosmic.shield_box_rows;
  editor_item_field5_i32 = (uint)cosmic.settler_food_low;
  editor_item_field6_i32 = (uint)cosmic.settler_food_high;
  editor_item_field7_i32 = (uint)cosmic.unhappy_size;
  editor_item_field8_i32 = (uint)cosmic.riot_factor;
  editor_item_field9_i32 = (uint)cosmic.aqueduct_size;
  editor_item_field10_i32 = (uint)cosmic.sewer_size;
  editor_item_field11_i32 = (uint)cosmic.tech_paradigm;
  editor_item_flags_i32 = (uint)cosmic.transform_time;
  editor_item_field13_i32 = (uint)cosmic.monarchy_free_support;
  editor_item_field14_i32 = (uint)cosmic.communism_free_support;
  editor_item_field15_i32 = (uint)cosmic.fundamentalism_free_support;
  editor_item_field16_i32 = (uint)cosmic.communism_palace_dist;
  editor_item_field17_i32 = (uint)cosmic.fund_science_loss;
  editor_item_field18_i32 = (uint)cosmic.change_penalty;
  editor_item_field19_i32 = (uint)cosmic.paradrop_range;
  editor_item_field20_i32 = (uint)cosmic.mass_thrust_paradigm;
  editor_item_field21_i32 = (uint)cosmic.fund_max_science;
  cosmic.road_move_mult = cosmic_edit_values;
  cosmic.trireme_loss_chance = cosmic_edit_trireme_loss;
  cosmic.food_per_citizen = cosmic_edit_food_per_citizen;
  cosmic.food_box_rows = cosmic_edit_food_box_rows;
  cosmic.shield_box_rows = cosmic_edit_shield_box_rows;
  cosmic.settler_food_low = cosmic_edit_settler_food_low;
  cosmic.settler_food_high = cosmic_edit_settler_food_high;
  cosmic.unhappy_size = cosmic_edit_unhappy_size;
  cosmic.riot_factor = cosmic_edit_riot_factor;
  cosmic.aqueduct_size = cosmic_edit_aqueduct_size;
  cosmic.sewer_size = cosmic_edit_sewer_size;
  cosmic.tech_paradigm = cosmic_edit_tech_paradigm;
  cosmic.transform_time = cosmic_edit_transform_time;
  cosmic.monarchy_free_support = cosmic_edit_monarchy_support;
  cosmic.communism_free_support = cosmic_edit_communism_support;
  cosmic.fundamentalism_free_support = cosmic_edit_fundamentalism_support;
  cosmic.communism_palace_dist = cosmic_edit_communism_palace_dist;
  cosmic.fund_science_loss = cosmic_edit_fund_science_loss;
  cosmic.change_penalty = cosmic_edit_change_penalty;
  cosmic.paradrop_range = cosmic_edit_paradrop_range;
  cosmic.mass_thrust_paradigm = cosmic_edit_mass_thrust_paradigm;
  cosmic.fund_max_science = cosmic_edit_fund_max_science;
  return;
}
#undef cosmic_edit_values
#undef editor_items_i32
#undef editor_item_field1_i32
#undef editor_item_field2_i32
#undef editor_item_field3_i32
#undef editor_item_field4_i32
#undef editor_item_field5_i32
#undef editor_item_field6_i32
#undef editor_item_field7_i32
#undef editor_item_field8_i32
#undef editor_item_field9_i32
#undef editor_item_field10_i32
#undef editor_item_field11_i32
#undef editor_item_flags_i32
#undef editor_item_field13_i32
#undef editor_item_field14_i32
#undef editor_item_field15_i32
#undef editor_item_field16_i32
#undef editor_item_field17_i32
#undef editor_item_field18_i32
#undef editor_item_field19_i32
#undef editor_item_field20_i32
#undef editor_item_field21_i32
#undef cosmic_edit_values_i32
#undef cosmic_edit_trireme_loss_i32
#undef cosmic_edit_food_per_citizen_i32
#undef cosmic_edit_food_box_rows_i32
#undef cosmic_edit_shield_box_rows_i32
#undef cosmic_edit_settler_food_low_i32
#undef cosmic_edit_settler_food_high_i32
#undef cosmic_edit_unhappy_size_i32
#undef cosmic_edit_riot_factor_i32
#undef cosmic_edit_aqueduct_size_i32
#undef cosmic_edit_sewer_size_i32
#undef cosmic_edit_tech_paradigm_i32
#undef cosmic_edit_transform_time_i32
#undef cosmic_edit_monarchy_support_i32
#undef cosmic_edit_communism_support_i32
#undef cosmic_edit_fundamentalism_support_i32
#undef cosmic_edit_communism_palace_dist_i32
#undef cosmic_edit_fund_science_loss_i32
#undef cosmic_edit_change_penalty_i32
#undef cosmic_edit_paradrop_range_i32
#undef cosmic_edit_mass_thrust_paradigm_i32
#undef cosmic_edit_fund_max_science_i32

/* 005869d4 auto */
#define cosmic_edit_values (*(i8 *)((u8 *)&g.d_006a2d80))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define local_a8 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_a4 (*(char (*)[128])(frame_ + FRAME_OFF(4)))
#define local_24 (*(char (*)[32])(frame_ + FRAME_OFF(132)))
void __cdecl cosmic_editor_fill_list(void)

{
  char *_Str;
  size_t sVar1;
  i8 frame_[FRAME_OFF(168)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_a8 = 0;
  listbox_clear((ListBoxClearView *)(active_editor_wnd + 0xa94));
  text_open_section(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x634640, ((u8 *)&g.d_00634640)));
  while( true ) {
    _Str = (char *)text_read_line(1);
    sVar1 = _strlen(_Str);
    if ((sVar1 < 3) || (0x15 < local_a8)) break;
    if (*(int *)(&cosmic_edit_values + local_a8 * 4) < 10) {
      _sprintf(local_a4,s__d_0063464c,*(i32 *)(&cosmic_edit_values + local_a8 * 4));
    }
    else if (*(int *)(&cosmic_edit_values + local_a8 * 4) < 100) {
      _sprintf(local_a4,s__d_00634654,*(i32 *)(&cosmic_edit_values + local_a8 * 4));
    }
    else {
      _sprintf(local_a4,&cosmic_value_fmt_3digit,*(i32 *)(&cosmic_edit_values + local_a8 * 4));
    }
    if (*(int *)(&editor_items + local_a8 * 4) < 10) {
      _sprintf(local_24,s___d____00634660,*(i32 *)(&editor_items + local_a8 * 4));
    }
    else if (*(int *)(&editor_items + local_a8 * 4) < 100) {
      _sprintf(local_24,s___d____00634670,*(i32 *)(&editor_items + local_a8 * 4));
    }
    else {
      _sprintf(local_24,s___d____0063467c,*(i32 *)(&editor_items + local_a8 * 4));
    }
    crt_strcat(local_a4,local_24);
    crt_strcat(local_a4,&text_buffer);
    listbox_add_string((ListBoxAddView *)(active_editor_wnd + 0xa94),(iptr)local_a4);
    local_a8++;
  }
  text_close_file();
  return;
}
#undef cosmic_edit_values
#undef text_buffer
#undef local_a8
#undef local_a4
#undef local_24

/* 00586bb6 auto */
#define local_120 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_118 (*(char (*)[260])(frame_ + FRAME_OFF(8)))
#define local_14 (*(char (*)[16])(frame_ + FRAME_OFF(268)))
void __cdecl cosmic_editor_edit_value(void)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  i32 uVar4;
  i32 uVar5;
  char *pcVar6;
  i8 frame_[FRAME_OFF(288)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = listbox_get_cur_sel((ListBoxGetSelView *)(active_editor_wnd + 0xa94));
  if (active_editor_wnd == 0) {
    local_120 = 0;
  }
  else {
    local_120 = active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(local_120);
  text_set_number_arg(0,*(i32 *)(&cosmic_edit_min_values + iVar1 * 4));
  text_set_number_arg(1,*(i32 *)(&cosmic_edit_max_values + iVar1 * 4));
  pcVar6 = local_118;
  pcVar2 = __itoa(*(int *)(&editor_items + iVar1 * 4),local_14,10);
  iVar3 = dlg_text_input(ADDR(0x6359dc, ((u8 *)&g.d_006359dc)),ADDR(0x634688, ((u8 *)&g.d_00634688)),3,(iptr)pcVar2,(iptr)pcVar6);
  if (-1 < iVar3) {
    uVar4 = *(i32 *)(&cosmic_edit_max_values + iVar1 * 4);
    uVar5 = *(i32 *)(&cosmic_edit_min_values + iVar1 * 4);
    iVar3 = _atoi(local_118);
    uVar4 = int_clamp(iVar3,uVar5,uVar4);
    *(i32 *)(&editor_items + iVar1 * 4) = uVar4;
    cosmic_editor_fill_list();
    listbox_set_cur_sel((ListBoxSetSelView *)(active_editor_wnd + 0xa94),iVar1);
  }
  ctrl_set_focus((ControlFocusView *)(active_editor_wnd + 0xa94));
  dlg_set_parent_window(0);
  cosmic_editor_focus_redraw();
  return;
}
#undef local_120
#undef local_118
#undef local_14

/* 00586d0a auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define local_88 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_84 (*(char (*)[128])(frame_ + FRAME_OFF(4)))
i32 __cdecl cosmic_editor_write_section(FILE *param_1,FILE *param_2)

{
  char *pcVar1;
  i8 frame_[FRAME_OFF(136)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_88 = 0; local_88 < 0x16; local_88++) {
    _fgets(local_84,0x80,param_2);
    pcVar1 = _strchr(local_84,0x3b);
    _sprintf(&text_buffer,s___8d_s_00634690,*(i32 *)(&editor_items + local_88 * 4),pcVar1);
    _fputs(&text_buffer,param_1);
  }
  return 1;
}
#undef text_buffer
#undef local_88
#undef local_84

/* 00586da1 auto */
#define editor_running (*(i32 *)((u8 *)&g.d_006a1d7c))
#define local_24 (*(char (*)[32])(frame_ + FRAME_OFF(4)))
void __cdecl cosmic_editor_ok_clicked(void)

{
  iptr iVar1;
  iptr iVar2;
  char *lpText;
  char *lpCaption;
  UINT uType;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  rules_edit_set_section(ADDR(0x634698, ((u8 *)&g.d_00634698)),ADDR(0x40172b, cosmic_editor_write_section));
  iVar1 = rules_write_sections();
  if (iVar1 == 0) {
    _sprintf(local_24,s_Error_updating_RULES__s_006346a0,&lang_file_ext);
    uType = 0x10;
    lpCaption = s_File_I_O_Error_006346b8;
    lpText = local_24;
    iVar2 = wnd_get_window((WndBase *)(active_editor_wnd + 0x48));
    MessageBoxA(*(HWND *)(iVar2 + 4),lpText,lpCaption,uType);
  }
  editor_running = 0;
  wnd_end_modal_loop((ModalMenuWindow *)(active_editor_wnd + 0x48));
  return;
}
#undef editor_running
#undef local_24

/* 00586e24 auto */
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(0)))
void __cdecl cosmic_editor_help_clicked(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (active_editor_wnd == 0) {
    local_8 = 0;
  }
  else {
    local_8 = active_editor_wnd + 0x48;
  }
  dlg_set_parent_window(local_8);
  popup_text(ADDR(0x6346d0, ((u8 *)&g.d_006346d0)),ADDR(0x6346c8, ((u8 *)&g.d_006346c8)));
  dlg_set_parent_window(0);
  cosmic_editor_focus_redraw();
  return;
}
#undef local_8

/* 00586e88 auto */
#define editor_running (*(i32 *)((u8 *)&g.d_006a1d7c))
void __cdecl cosmic_editor_cancel_clicked(void)

{
  editor_running = 0;
  wnd_end_modal_loop((ModalMenuWindow *)(active_editor_wnd + 0x48));
  return;
}
#undef editor_running

/* 00586eb0 auto */
void __thiscall cosmic_editor_draw_bg(FrameWindow *this)

{
  frame_wnd_draw_caption(this);
  gfx_fill_rect((iptr)this,(iptr)&this->client_rect,0x1a);
  text_set_surface((iptr)this);
  text_set_font(ADDR(0x6a4f90, ((u8 *)&g.d_006a4f90)));
  text_set_colors(0x29,0x12,1,1);
  wnd_blit_surface((DibSurface *)this);
  return;
}

/* 00586f16 auto */
#define editor_bg_surface (*(DibSurface * *)((u8 *)&g.d_0062e018))
#define editor_next_ctrl_id (*(int *)((u8 *)&g.d_006a1d80))
#define editor_running (*(int *)((u8 *)&g.d_006a1d7c))
#define local_484 (*(u8 * *)(frame_ + FRAME_OFF(4)))
#define local_480 (*(u8 * *)(frame_ + FRAME_OFF(8)))
#define local_47c (*(u8 * *)(frame_ + FRAME_OFF(12)))
#define local_478 (*(u8 * *)(frame_ + FRAME_OFF(16)))
#define local_474 (*(u8 * *)(frame_ + FRAME_OFF(20)))
#define local_464 (*(DibSurface * *)(frame_ + FRAME_OFF(36)))
#define local_454 (*(i8 (*)[16])(frame_ + FRAME_OFF(52)))
#define local_444 (*(GamePalette *)(frame_ + FRAME_OFF(68)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1144)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1148)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(1152)))
void __thiscall cosmic_editor_dialog(ViewWindow *this)

{
  DibSurface *this_00;
  uptr uVar1;
  i32 uVar2;
  int iVar3;
  int iVar4;
  iptr iVar5;
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
    local_464 = (DibSurface *)0x0;
  }
  else {
    local_464 = (DibSurface *)surface_ctor(this_00);
  }
  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
  editor_bg_surface = local_464;
  font_set((GameFont *)&editor_font,0,editor_font_size);
  ui_set_default_font(ADDR(0x6a4f90, ((u8 *)&g.d_006a4f90)));
  ui_set_ctrl_font(ADDR(0x6a4f90, ((u8 *)&g.d_006a4f90)));
  ui_set_ctrl_text_color(0x29);
  ui_set_ctrl_text_shadow(0x12,1,1);
  ui_set_ctrl_disabled_color(0x25);
  this->field_2d8 = 0x230;
  this->field_2dc = 0x1c6;
  this->field_2ec = 0;
  editor_next_ctrl_id = 0xc9;
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
  uVar2 = label_string(*(i32 *)(label_string_ids + 0x94c));
  frame_wnd_create
            ((FrameWindow *)this,uVar2,uVar6,uVar7,uVar8,uVar9,uVar10,uVar11,uVar12,uVar13);
  rect_set_xywh((iptr)local_454,this->client_x + 2,this->client_y + 2,this->client_width - 5,
                     this->client_height - 0x14);
  iVar3 = editor_next_ctrl_id;
  editor_next_ctrl_id++;
  if (this == (ViewWindow *)0x0) {
    local_474 = (u8 *)0x0;
  }
  else {
    local_474 = this->pad_48;
  }
  listbox_create
            ((Control *)&this[2].field_234,(iptr)local_474,iVar3,(iptr)local_454);
  listbox_set_font((ListBoxFontView *)&this[2].field_234,ADDR(0x6a4f90, ((u8 *)&g.d_006a4f90)));
  listbox_set_dblclick_callback((ListBoxDblClickSetView *)&this[2].field_234,ADDR(0x4038a5, cosmic_editor_edit_value));
  cosmic_editor_capture_defaults();
  cosmic_editor_fill_list();
  listbox_set_cur_sel((ListBoxSetSelView *)&this[2].field_234,0);
  iVar3 = font_line_spacing((GameFont *)dialog_font_ptr);
  this->field_2e4 = iVar3 + 8;
  iVar3 = this->client_width - 10;
  this->field_2e0 = (int)(iVar3 + (iVar3 >> 0x1f & 3U)) >> 2;
  iVar4 = (this->client_y + this->client_height) - (this->field_2e4 + 2);
  iVar3 = this->client_x + 2;
  rect_set_xywh((iptr)local_454,iVar3,iVar4,this->field_2e0,this->field_2e4);
  if (this == (ViewWindow *)0x0) {
    local_478 = (u8 *)0x0;
  }
  else {
    local_478 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x3f8));
  button_create
            ((Control *)&this[1].field_2a4,(iptr)local_478,0x65,(iptr)local_454,iVar5);
  button_set_callback((Control *)&this[1].field_2a4,ADDR(0x40342c, cosmic_editor_ok_clicked));
  iVar3 = iVar3 + this->field_2e0 + 2;
  rect_set_xywh((iptr)local_454,iVar3,iVar4,this->field_2e0,this->field_2e4);
  if (this == (ViewWindow *)0x0) {
    local_47c = (u8 *)0x0;
  }
  else {
    local_47c = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x8e0));
  button_create
            ((Control *)&this[1].field_358,(iptr)local_47c,0x66,(iptr)local_454,iVar5);
  button_set_callback((Control *)&this[1].field_358,ADDR(0x4038a5, cosmic_editor_edit_value));
  ctrl_set_default_button((Control *)&this[1].field_358);
  iVar3 = iVar3 + this->field_2e0 + 2;
  rect_set_xywh((iptr)local_454,iVar3,iVar4,this->field_2e0,this->field_2e4);
  if (this == (ViewWindow *)0x0) {
    local_480 = (u8 *)0x0;
  }
  else {
    local_480 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x8ec));
  button_create
            ((Control *)&this[1].field_2e0,(iptr)local_480,0x66,(iptr)local_454,iVar5);
  button_set_callback((Control *)&this[1].field_2e0,ADDR(0x4010f5, cosmic_editor_help_clicked));
  rect_set_xywh((iptr)local_454,iVar3 + this->field_2e0 + 2,iVar4,this->field_2e0,
                     this->field_2e4);
  if (this == (ViewWindow *)0x0) {
    local_484 = (u8 *)0x0;
  }
  else {
    local_484 = this->pad_48;
  }
  iVar5 = label_string(*(i32 *)(label_string_ids + 0x3fc));
  button_create
            ((Control *)&this[1].field_31c,(iptr)local_484,0x66,(iptr)local_454,iVar5);
  button_set_callback((Control *)&this[1].field_31c,ADDR(0x402fae, cosmic_editor_cancel_clicked));
  ctrl_set_cancel_button((Control *)&this[1].field_31c);
  wnd_set_keyboard_nav((Wnd *)this->pad_48,0);
  wnd_set_redraw_callback((SurfaceWindow *)this,ADDR(0x401c0d, cosmic_editor_focus_redraw));
  wnd_repaint((SurfaceWindow *)this);
  window_show((WindowObjectView *)this);
  wnd_run_modal_loop((ModalMenuWindow *)this->pad_48);
  while (editor_running != 0) {
    win_pump_one_message();
  }
  if (editor_bg_surface != (DibSurface *)0x0) {
    surface_delete(editor_bg_surface,1);
  }
  editor_bg_surface = (DibSurface *)0x0;
  local_8 = 0xffffffff;
  /* inlined unwind funclet 005875e9 */ { palette_destroy((GamePalette *)((iptr)&local_444)); }
  return;
}
#undef editor_bg_surface
#undef editor_next_ctrl_id
#undef editor_running
#undef local_484
#undef local_480
#undef local_47c
#undef local_478
#undef local_474
#undef local_464
#undef local_454
#undef local_444
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0058760d auto */
#define local_b58 (*(DocumentWindow *)(frame_ + FRAME_OFF(0)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(2888)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(2892)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(2896)))
void __cdecl cosmic_editor_run(void)

{
  i8 frame_[FRAME_OFF(2904)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  editor_wnd_ctor(&local_b58);
  local_8 = 0;
  cosmic_editor_dialog((ViewWindow *)&local_b58);
  wnd_repaint((SurfaceWindow *)&map_views);
  local_8 = 0xffffffff;
  /* inlined unwind funclet 00587666 */ { editor_wnd_dtor((EditorWindow *)((iptr)&local_b58)); }
  return;
}
#undef local_b58
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00598a05 auto */
i32 __cdecl civ_spaceship_part_maxed(iptr civ,iptr param_2)

{
  if (param_2 == 0x23) {
    if (spaceship_part_max_counts <= civs[civ].spaceship_parts[0]) {
      return 1;
    }
  }
  else if (param_2 == 0x24) {
    if ((spaceship_propulsion_max <= civs[civ].spaceship_parts[1]) &&
       (spaceship_fuel_max <= civs[civ].spaceship_parts[2])) {
      return 1;
    }
  }
  else if (((spaceship_habitation_max <= civs[civ].spaceship_parts[3]) &&
           (spaceship_life_support_max <= civs[civ].spaceship_parts[4])) &&
          (spaceship_solar_panel_max <= civs[civ].spaceship_parts[5])) {
    return 1;
  }
  return 0;
}
