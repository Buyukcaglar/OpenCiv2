/* The game, multiplayer: network sessions, negotiation, lobby and chat: functions translated from the original
 * (tools/gen_c.py, now edited directly), in address order. */
#include "auto_common.h"

/* 00421f40 auto */
i8 __thiscall net_is_host(void *self)

{
  return *(i8 *)((int)self + 0x1ef);
}

/* 00421f70 auto */
NetGamelistViewCtorView * __thiscall net_gamelist_view_ctor(NetGamelistViewCtorView *self)

{
  self->next_game_id = 1;
  self->option_list = 0;
  self->refresh_timer = 0;
  return self;
}

/* 00421fad auto */
void __thiscall net_gamelist_view_dtor(void *self)

{
  net_free_game_list(((iptr *)&net_session_block.net_session));
  return;
}

/* 00421fcd: written by hand in src/native/crt.c */

/* 0042415c auto */
void __cdecl net_gamelist_poll_idle(void)

{
  net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
  return;
}

/* 0042417a auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl net_join_wait_server_idle(void)

{
  timer_ticks();
  net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
  if ((((net_session_block.nm_player_list_count != 0) || (net_session_block.nm_server_canceled_count != 0)) || (net_session_block.nm_server_reject_count != 0)) || (net_session_block.nm_server_full_count != 0))
  {
    net_session_block.dialog_stack_top[0xf] = net_session_block.dialog_stack_top[0xf] | 0x400;
    wnd_end_modal_loop((ModalMenuWindow *)(*net_session_block.dialog_stack_top + 0x48));
  }
  return;
}

/* 004241f8 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl net_join_wait_gamestate_idle(void)

{
  int elapsed;
  size_t text_len;
  char *marker;
  char *text;
  
  elapsed = timer_ticks();
  elapsed -= net_session_block.net_wait_start_ticks_i32;
  net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
  if ((net_session_block.nm_join_gamestate_count == 0) && (net_session_block.nm_server_canceled_count == 0)) {
    if (2 < elapsed) {
      text = *(char **)(*(int *)((*(Dialog * *)&net_session_block.dialog_stack_top)->line_list + 0x1c) + 8);
      text_len = _strlen(text);
      marker = _strchr(text,0x3e);
      if (text + (text_len - 1) == marker) {
        *marker = '<';
      }
      else {
        *marker = '-';
        marker[1] = '>';
      }
      marker = _strchr(text,0x3c);
      if (marker == (char *)0x0) {
        text = _strchr(text,0x3e);
        text[-1] = '<';
      }
      else if (marker == text) {
        *marker = '>';
      }
      else {
        *marker = '-';
        marker[-1] = '<';
      }
      dialog_render((*(Dialog * *)&net_session_block.dialog_stack_top));
      net_session_block.net_wait_start_ticks_i32 = timer_ticks();
    }
  }
  else {
    (*(Dialog * *)&net_session_block.dialog_stack_top)->style_flags = (*(Dialog * *)&net_session_block.dialog_stack_top)->style_flags | 0x400;
    wnd_end_modal_loop((ModalMenuWindow *)((*(Dialog * *)&net_session_block.dialog_stack_top)->surf_wnd + 0x48));
  }
  return;
}

/* 0042433c auto */
void __cdecl net_join_wait_player_list_idle(void)

{
  net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
  if (((net_session_block.nm_player_list_count != 0) || (net_session_block.nm_server_canceled_count != 0)) || (net_session_block.nm_lost_server_on_join_count != 0)) {
    net_session_block.dialog_stack_top[0xf] = net_session_block.dialog_stack_top[0xf] | 0x400;
    wnd_end_modal_loop((ModalMenuWindow *)(*net_session_block.dialog_stack_top + 0x48));
  }
  return;
}

/* 0042439c auto */
void __cdecl net_join_wait_start_civ_idle(void)

{
  net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
  if ((net_session_block.nm_start_civ_count != 0) || (net_session_block.nm_server_canceled_count != 0)) {
    net_session_block.dialog_stack_top[0xf] = net_session_block.dialog_stack_top[0xf] | 0x400;
    wnd_end_modal_loop((ModalMenuWindow *)(*net_session_block.dialog_stack_top + 0x48));
  }
  return;
}

/* 004243ef auto */
void __cdecl net_join_wait_answer_idle(void)

{
  net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
  if (((net_session_block.nm_server_answer_count != 0) || (net_session_block.nm_server_canceled_count != 0)) || (net_session_block.nm_server_reject_count != 0)) {
    net_session_block.dialog_stack_top[0xf] = net_session_block.dialog_stack_top[0xf] | 0x400;
    wnd_end_modal_loop((ModalMenuWindow *)(*net_session_block.dialog_stack_top + 0x48));
  }
  return;
}

/* 0042444f auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl net_join_wait_idle_cb(void)

{
  int elapsed;
  
  elapsed = timer_ticks();
  elapsed -= net_session_block.net_wait_start_ticks_i32;
  net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
  if ((net_session_block.net_server_conn_id == -1) && (0x4d8 < elapsed)) {
    net_session_block.dialog_stack_top[0xf] = net_session_block.dialog_stack_top[0xf] | 0x400;
    wnd_end_modal_loop((ModalMenuWindow *)(*net_session_block.dialog_stack_top + 0x48));
  }
  else if (net_session_block.net_server_conn_id != -1) {
    net_session_block.dialog_stack_top[0xf] = net_session_block.dialog_stack_top[0xf] | 0x400;
    wnd_end_modal_loop((ModalMenuWindow *)(*net_session_block.dialog_stack_top + 0x48));
  }
  return;
}

/* 004244e0 auto */
void __thiscall net_gamelist_restore_selection(NetGameListRefreshView *self)

{
  int option_count;
  i32 option;
  int top_index;
  int selected_index;
  iptr scroll_pos;
  
  option_count = dialog_count_group_options((DialogOptionList *)self->list_dialog,0);
  scrollbar_set_range(*(Control **)(self->list_dialog + 0x284),0,option_count - 1);
  option = net_gamelist_find_option(self,(iptr)&self->selected_game_name,(iptr)&self->selected_host_name);
  *(i32 *)(self->list_dialog + 0x220) = option;
  if (option_count < 0xb) {
    *(u32 *)(self->list_dialog + 0x210) = self->first_option_value;
  }
  else {
    option = net_gamelist_find_option(self,(iptr)&self->top_game_name,(iptr)&self->top_host_name);
    *(i32 *)(self->list_dialog + 0x210) = option;
  }
  if (*(int *)(self->list_dialog + 0x1b8) != 0) {
    top_index = dialog_option_group_index
                      ((DialogOptionList *)self->list_dialog,*(uptr *)(self->list_dialog + 0x210));
    option_count = *(int *)(self->list_dialog + 0x5c);
    selected_index = dialog_option_group_index
                      ((DialogOptionList *)self->list_dialog,*(uptr *)(self->list_dialog + 0x220));
    if (option_count + top_index <= selected_index) {
      option_count = dialog_option_group_index
                        ((DialogOptionList *)self->list_dialog,*(uptr *)(self->list_dialog + 0x220));
      option = dialog_option_at
                        ((DialogOptionList *)self->list_dialog,
                         (option_count - *(int *)(self->list_dialog + 0x5c)) + 1);
      *(i32 *)(self->list_dialog + 0x210) = option;
    }
    option_count = dialog_option_group_index
                      ((DialogOptionList *)self->list_dialog,*(uptr *)(self->list_dialog + 0x210));
    top_index = dialog_option_group_index
                      ((DialogOptionList *)self->list_dialog,*(uptr *)(self->list_dialog + 0x220));
    if (top_index < option_count) {
      *(i32 *)(self->list_dialog + 0x210) = *(i32 *)(self->list_dialog + 0x220);
    }
  }
  scroll_pos = dialog_option_group_index
                    ((DialogOptionList *)self->list_dialog,*(uptr *)(self->list_dialog + 0x210));
  scrollbar_set_pos(*(ClickControl **)(self->list_dialog + 0x284),scroll_pos);
  return;
}

/* 00424688 auto */
u32 __thiscall net_gamelist_find_option(NetGameListRefreshView *self,iptr game_name,iptr host_name)

{
  int cmp;
  uptr option;
  iptr game2;
  
  option = self->first_option_value;
  game2 = net_session_block.net_found_games;
  while( true ) {
    if (game2 == 0) {
      return self->first_option_value;
    }
    cmp = _strcmp((char *)(game2 + 0x70),(char *)game_name);
    if ((cmp == 0) && (cmp = _strcmp((char *)(game2 + 0x90),(char *)host_name), cmp == 0))
    break;
    option = *(uptr *)(option + 0x10);
    game2 = *(iptr *)(game2 + 0x20);
  }
  return option;
}

/* 0042472a auto */
void __thiscall net_gamelist_update_details(NetGameList *self)

{
  if (net_session_block.net_found_games == 0) {
    self->selected_game_name = '\0';
    self->selected_host_name = '\0';
    self->top_game_name = '\0';
    self->top_host_name = '\0';
  }
  else {
    net_gamelist_get_entry_names(self,*(iptr *)(self->list_dialog + 0x220),(iptr)&self->selected_game_name,
                       (iptr)&self->selected_host_name);
    net_gamelist_get_entry_names(self,*(iptr *)(self->list_dialog + 0x210),(iptr)&self->top_game_name,
                       (iptr)&self->top_host_name);
  }
  return;
}

/* 004247b2 auto */
void __thiscall net_gamelist_get_entry_names(NetGameList *self,iptr option,iptr out_game_name,iptr out_host_name)

{
  int remaining;
  iptr game2;
  
  for (game2 = net_session_block.net_found_games;
      (game2 != 0 && (*(int *)(option + 4) != *(int *)(game2 + 0x2c)));
      game2 = *(iptr *)(game2 + 0x20)) {
  }
  if (game2 == 0) {
    game2 = net_session_block.net_found_games;
    for (remaining = dialog_option_group_index((DialogOptionList *)self->list_dialog,option);
        (*(int *)(game2 + 0x20) != 0 && (remaining != 0)); remaining--) {
      game2 = *(iptr *)(game2 + 0x20);
    }
  }
  crt_strcpy(out_game_name,game2 + 0x70);
  crt_strcpy(out_host_name,game2 + 0x90);
  return;
}

/* 0042486f auto */
void __thiscall net_gamelist_add_info_lines(NetGamelistAddInfoLinesView *self)

{
  int line_y;
  u32 *line;
  int spacing;
  
  dialog_compute_layout((DialogOptionList *)self->dialog);
  line_y = *(int *)(self->dialog + 0xd0) + *(int *)(self->dialog + 0xb8) + 2;
  line = (u32 *)dialog_add_line
                            ((DialogAddLineView *)self->dialog,(iptr)&str_empty_14,0xe6,line_y,0x80,0);
  self->line_0 = *line;
  spacing = font_line_spacing(*(GameFont **)(self->dialog + 8));
  line_y += spacing;
  line = (u32 *)dialog_add_line
                            ((DialogAddLineView *)self->dialog,(iptr)&str_empty_15,0xe6,line_y,0x80,0);
  self->line_1 = *line;
  spacing = font_line_spacing(*(GameFont **)(self->dialog + 8));
  line_y += spacing;
  line = (u32 *)dialog_add_line
                            ((DialogAddLineView *)self->dialog,(iptr)&str_empty_16,0xe6,line_y,0x80,0);
  self->line_2 = *line;
  spacing = font_line_spacing(*(GameFont **)(self->dialog + 8));
  line_y += spacing;
  line = (u32 *)dialog_add_line
                            ((DialogAddLineView *)self->dialog,(iptr)&str_empty_17,0xe6,line_y,0x80,0);
  self->line_3 = *line;
  spacing = font_line_spacing(*(GameFont **)(self->dialog + 8));
  line_y += spacing;
  line = (u32 *)dialog_add_line
                            ((DialogAddLineView *)self->dialog,(iptr)&str_empty_18,0xe6,line_y,0x80,0);
  self->line_4 = *line;
  spacing = font_line_spacing(*(GameFont **)(self->dialog + 8));
  line_y += spacing;
  line = (u32 *)dialog_add_line
                            ((DialogAddLineView *)self->dialog,(iptr)&str_empty_19,0xe6,line_y,0x80,0);
  self->line_5 = *line;
  spacing = font_line_spacing(*(GameFont **)(self->dialog + 8));
  line_y += spacing;
  line = (u32 *)dialog_add_line
                            ((DialogAddLineView *)self->dialog,(iptr)&str_empty_20,0xe6,line_y,0x80,0);
  self->line_6 = *line;
  spacing = font_line_spacing(*(GameFont **)(self->dialog + 8));
  line_y += spacing;
  line = (u32 *)dialog_add_line
                            ((DialogAddLineView *)self->dialog,(iptr)&str_empty_21,0xe6,line_y,0x80,0);
  self->line_7 = *line;
  spacing = font_line_spacing(*(GameFont **)(self->dialog + 8));
  line = (u32 *)dialog_add_line
                            ((DialogAddLineView *)self->dialog,(iptr)&str_empty_22,0xe6,line_y + spacing,0x80,0);
  self->line_8 = *line;
  font_line_spacing(*(GameFont **)(self->dialog + 8));
  return;
}

/* 00424ae9 auto */
i32 __cdecl net_gamelist_show_game_info(void *dialog,i32 unused)

{
  size_t text_len;
  i32 year;
  int seconds;
  int minutes;
  iptr scroll_pos;
  uint civ_bits;
  int civ_count;
  int bit;
  char text[21];
  i8 text_cutoff;
  iptr found_game;
  
  found_game = net_session_block.net_found_games;
  if (net_session_block.net_found_games == 0) {
    dialog_set_item_text(dialog,*(i32 *)(net_session_block.net_session[0] + 0x128),(iptr)&str_empty_23);
    dialog_set_item_text(dialog,*(i32 *)(net_session_block.net_session[0] + 300),(iptr)&str_empty_24);
    dialog_set_item_text(dialog,*(i32 *)(net_session_block.net_session[0] + 0x130),(iptr)&str_empty_25);
    dialog_set_item_text(dialog,*(i32 *)(net_session_block.net_session[0] + 0x134),(iptr)&str_empty_26);
    dialog_set_item_text(dialog,*(i32 *)(net_session_block.net_session[0] + 0x138),(iptr)&str_empty_27);
    dialog_set_item_text(dialog,*(i32 *)(net_session_block.net_session[0] + 0x13c),(iptr)&str_empty_28);
    dialog_set_item_text(dialog,*(i32 *)(net_session_block.net_session[0] + 0x140),(iptr)&str_empty_29);
    dialog_set_item_text(dialog,*(i32 *)(net_session_block.net_session[0] + 0x144),(iptr)&str_empty_30);
    dialog_set_item_text(dialog,*(i32 *)(net_session_block.net_session[0] + 0x148),(iptr)&str_empty_31);
  }
  else {
    for (; (found_game != 0 &&
           (*(int *)(found_game + 0x2c) != *(int *)(*(int *)(*(int *)net_session_block.net_session[0] + 0x220) + 4)));
        found_game = *(iptr *)(found_game + 0x20)) {
    }
    if (found_game != 0) {
      str_clear((iptr)text);
      str_append_label((iptr)text,0x26f);
      str_append_space((iptr)text);
      crt_strcat(text,found_game + 0x70);
      str_append_space((iptr)text);
      str_append_lparen((iptr)text);
      str_append_label((iptr)text,(*(short *)(found_game + 0xb0) == 0) + 0x277);
      str_append_rparen((iptr)text);
      dialog_set_item_text(dialog,*(i32 *)(net_session_block.net_session[0] + 0x128),(iptr)text);
      str_clear((iptr)text);
      str_append_label((iptr)text,0x270);
      str_append_space((iptr)text);
      crt_strcat(text,found_game + 0x90);
      dialog_set_item_text(dialog,*(i32 *)(net_session_block.net_session[0] + 300),(iptr)text);
      str_clear((iptr)text);
      text_len = _strlen((char *)(found_game + 0xbc));
      if (text_len == 0) {
        str_append_label((iptr)text,0x34c);
      }
      else {
        crt_strcpy(text,found_game + 0xbc);
      }
      text_len = _strlen(text);
      if (0x19 < text_len) {
        text_cutoff = 0;
      }
      str_append_space((iptr)text);
      str_append_lparen((iptr)text);
      game.game_flags = *(u16 *)(found_game + 0x110);
      game.first_launch_turn = *(i16 *)(found_game + 0x112);
      prefs_game_rules_block.scenario_year_increment[0] = *(i16 *)(found_game + 0x114);
      prefs_game_rules_block.scenario_start_year = *(i16 *)(found_game + 0x116);
      game.difficulty = *(u8 *)(found_game + 0xb2);
      year = game_turn_to_year((int)*(short *)(found_game + 0x118));
      str_append_year((iptr)text,year);
      str_append_rparen((iptr)text);
      dialog_set_item_text(dialog,*(i32 *)(net_session_block.net_session[0] + 0x130),(iptr)text);
      str_clear((iptr)text);
      str_append_label((iptr)text,*(byte *)(found_game + 0xb2) + 0x279);
      str_append_space((iptr)text);
      str_append_lparen((iptr)text);
      str_append_label((iptr)text,0x34e - (uint)(*(short *)(found_game + 0x11e) == 0));
      str_append_rparen((iptr)text);
      dialog_set_item_text(dialog,*(i32 *)(net_session_block.net_session[0] + 0x134),(iptr)text);
      str_clear((iptr)text);
      str_append_label((iptr)text,0x36c);
      str_append_space((iptr)text);
      str_append_int((iptr)text,(int)*(short *)(found_game + 0x11a) / 2);
      crt_strcat(text,((i8 *)&gamelist_map_size_sep_str));
      str_append_int((iptr)text,(int)*(short *)(found_game + 0x11c));
      dialog_set_item_text(dialog,*(i32 *)(net_session_block.net_session[0] + 0x138),(iptr)text);
      str_clear((iptr)text);
      str_append_label((iptr)text,0x350 - (uint)(*(short *)(found_game + 0x10e) == 0));
      crt_strcat(text,((i8 *)&gamelist_double_opts_sep_str));
      str_append_label((iptr)text,0x352 - (uint)(*(short *)(found_game + 0x10c) == 0));
      dialog_set_item_text(dialog,*(i32 *)(net_session_block.net_session[0] + 0x13c),(iptr)text);
      str_clear((iptr)text);
      str_append_label((iptr)text,0x273);
      str_append_space((iptr)text);
      str_append_label((iptr)text,*(byte *)(found_game + 0xb3) + 0x27f);
      dialog_set_item_text(dialog,*(i32 *)(net_session_block.net_session[0] + 0x140),(iptr)text);
      str_clear((iptr)text);
      str_append_label((iptr)text,0x276);
      str_append_space((iptr)text);
      if (*(int *)(found_game + 0xb8) == 0) {
        str_append_label((iptr)text,0x285);
      }
      else {
        seconds = *(int *)(found_game + 0xb8) / 1000;
        minutes = seconds / 0x3c;
        seconds = seconds % 0x3c;
        if (minutes < 10) {
          str_append_int((iptr)text,0);
        }
        str_append_int((iptr)text,minutes);
        crt_strcat(text,((i8 *)&gamelist_timer_colon_str));
        if (seconds < 10) {
          str_append_int((iptr)text,0);
        }
        str_append_int((iptr)text,seconds);
      }
      dialog_set_item_text(dialog,*(i32 *)(net_session_block.net_session[0] + 0x144),(iptr)text);
      bit = 1;
      civ_count = 0;
      civ_bits = (uint)*(byte *)(found_game + 0xb4);
      for (; civ_bits = (int)civ_bits >> 1, bit < 8; bit++) {
        if ((civ_bits & 1) != 0) {
          civ_count++;
        }
      }
      str_clear((iptr)text);
      str_append_label((iptr)text,0x274);
      str_append_space((iptr)text);
      str_append_int((iptr)text,civ_count);
      crt_strcat(text,((i8 *)&gamelist_open_paren_str));
      str_append_label((iptr)text,0x275);
      str_append_space((iptr)text);
      bit = 0;
      civ_count = 0;
      civ_bits = (uint)*(byte *)(found_game + 0xb5);
      for (; bit < 8; bit++) {
        if ((civ_bits & 1) != 0) {
          civ_count++;
        }
        civ_bits = (int)civ_bits >> 1;
      }
      if ((*(short *)(found_game + 0x120) < 3) || (civ_count == 0)) {
        str_append_label((iptr)text,0x353);
      }
      else {
        str_append_int((iptr)text,civ_count);
      }
      str_append_rparen((iptr)text);
      dialog_set_item_text(dialog,*(i32 *)(net_session_block.net_session[0] + 0x148),(iptr)text);
    }
  }
  scroll_pos = dialog_option_group_index
                    (*(DialogOptionList **)net_session_block.net_session[0],*(uptr *)(*(int *)net_session_block.net_session[0] + 0x210));
  scrollbar_set_pos(*(ClickControl **)(*(int *)net_session_block.net_session[0] + 0x284),scroll_pos);
  dialog_render(*(Dialog **)net_session_block.net_session[0]);
  return 1;
}

/* 004253ef auto */
void __thiscall net_gamelist_clear(NetGameList *self)

{
  void *next;
  void *option;
  
  option = (void *)self->first_option_value;
  net_gamelist_update_details(self);
  while (option != (void *)0x0) {
    next = *(void **)((int)option + 0x10);
    operator_delete(*(void **)((int)option + 8));
    operator_delete(option);
    option = next;
  }
  self->first_option_value = 0;
  *(i32 *)(self->list_dialog + 0x28) = 0;
  *(i32 *)(self->list_dialog + 0x228) = 0;
  *(i32 *)(self->list_dialog + 0x220) = 0;
  return;
}

/* 004254a8 auto */
uint * __thiscall net_gamelist_add_entry(NetGameListAddView *self,iptr name2,uint id)

{
  int *count_ptr;
  uint *entry;
  size_t name_len;
  void *name_copy;
  int entry_width;
  int max_width;
  uptr last;
  uptr option;
  
  last = 0;
  for (option = self->first_option_value; option != 0; option = *(uptr *)(option + 0x10)) {
    last = option;
  }
  entry = operator_new(0x18);
  entry[4] = 0;
  entry[5] = last;
  if (last == 0) {
    self->first_option_value = (u32)entry;
    *(uint **)(self->list_dialog + 0x228) = entry;
  }
  else {
    *(uint **)(last + 0x10) = entry;
  }
  *entry = 0;
  name_len = _strlen((char *)name2);
  name_copy = operator_new(name_len + 1);
  entry[2] = (uint)name_copy;
  crt_strcpy(entry[2],name2);
  if (*(char *)name2 == '\0') {
    *entry = *entry | 1;
  }
  entry[1] = id;
  entry[3] = 0;
  entry_width = font_text_width(*(GameFont **)(self->list_dialog + 8),entry[2]);
  max_width = dialog_option_icon_width((DialogCore *)self->list_dialog);
  entry_width = entry_width + max_width + *(int *)(self->list_dialog + 0xac) + 5;
  max_width = *(int *)(self->list_dialog + 0x118);
  if (max_width <= entry_width) {
    max_width = entry_width;
  }
  *(int *)(self->list_dialog + 0x118) = max_width;
  count_ptr = (int *)(self->list_dialog + 0x28);
  *count_ptr = *count_ptr + 1;
  return entry;
}

/* 00425607 auto */
void __thiscall net_gamelist_start_timer(NetGameListTimerView *self,iptr callback)

{
  u32 timer;
  
  if (self->refresh_timer != 0) {
    net_gamelist_kill_timer(self);
  }
  timer = game_timer_create(callback,0x32,1);
  self->refresh_timer = timer;
  return;
}

/* 00425650 auto */
void __thiscall net_gamelist_kill_timer(NetGameListTimerView *self)

{
  if (self->refresh_timer != 0) {
    game_timer_destroy(self->refresh_timer);
    self->refresh_timer = 0;
  }
  return;
}

/* 00425695 auto */
void __cdecl net_gamelist_poll_tick(void)

{
  i32 timer;
  
  net_send_message(1,0,0,0,0,0,0,0,0,0);
  net_gamelist_expire_stale();
  if (*(int *)(net_session_block.net_session[0] + 0x174) != 0) {
    game_timer_destroy(*(i32 *)(net_session_block.net_session[0] + 0x174));
  }
  timer = game_timer_create((iptr)net_gamelist_poll_tick,0xfa,1);
  *(i32 *)(net_session_block.net_session[0] + 0x174) = timer;
  return;
}

/* 0042570c auto */
void __cdecl net_gamelist_expire_stale(void)

{
  bool removed;
  int now;
  iptr next;
  iptr game2;
  
  removed = false;
  game2 = net_session_block.net_found_games;
  now = timer_ticks();
  while (game2 != 0) {
    if (net_session_block.net_timeout_seconds * 0x3c < now - *(int *)(game2 + 0x28)) {
      if (net_session_block.net_found_games == game2) {
        net_session_block.net_found_games = *(iptr *)(game2 + 0x20);
      }
      if (*(int *)(game2 + 0x24) != 0) {
        *(i32 *)(*(int *)(game2 + 0x24) + 0x20) = *(i32 *)(game2 + 0x20);
      }
      if (*(int *)(game2 + 0x20) != 0) {
        *(i32 *)(*(int *)(game2 + 0x20) + 0x24) = *(i32 *)(game2 + 0x24);
      }
      next = *(iptr *)(game2 + 0x20);
      operator_delete((void *)game2);
      removed = true;
      game2 = next;
    }
    else {
      game2 = *(iptr *)(game2 + 0x20);
    }
  }
  if (removed) {
    net_gamelist_refresh();
  }
  return;
}

/* 004257fe auto */
void __cdecl net_gamelist_refresh(void)

{
  uint *entry;
  i32 civ_bits;
  i32 bit;
  i32 total_civs;
  iptr game2;
  i32 human_count;
  
  if (net_session_block.net_session[0] != 0) {
    net_gamelist_clear((NetGameList *)net_session_block.net_session[0]);
    if (net_session_block.net_found_games == 0) {
      text_clear();
      text_append_label(0x286);
      net_gamelist_add_entry((NetGameListAddView *)net_session_block.net_session[0],(iptr)&map_views_block.text_buffer,0);
      net_gamelist_update_details((NetGameList *)net_session_block.net_session[0]);
    }
    else {
      for (game2 = net_session_block.net_found_games; game2 != 0; game2 = *(iptr *)(game2 + 0x20)) {
        if (*(int *)(game2 + 0x2c) == 0) {
          *(i32 *)(game2 + 0x2c) = *(i32 *)(net_session_block.net_session[0] + 4);
          *(int *)(net_session_block.net_session[0] + 4) = *(int *)(net_session_block.net_session[0] + 4) + 1;
        }
        entry = (uint *)net_gamelist_add_entry
                                   ((NetGameListAddView *)net_session_block.net_session[0],game2 + 0x70,
                                    *(i32 *)(game2 + 0x2c));
        bit = 0;
        total_civs = 0;
        civ_bits = (uint)*(byte *)(game2 + 0xb4);
        for (; bit < 8; bit++) {
          if ((civ_bits & 1) != 0) {
            total_civs++;
          }
          civ_bits = (int)civ_bits >> 1;
        }
        bit = 0;
        human_count = 0;
        civ_bits = (uint)*(byte *)(game2 + 0xb5);
        for (; bit < 8; bit++) {
          if ((civ_bits & 1) != 0) {
            human_count++;
          }
          civ_bits = (int)civ_bits >> 1;
        }
        if (((net_session_block.net_max_players <= human_count) || (total_civs <= human_count)) ||
           (*(short *)(game2 + 0xb0) == 0)) {
          *entry = *entry | 1;
        }
      }
    }
    net_gamelist_restore_selection((NetGameListRefreshView *)net_session_block.net_session[0]);
    net_gamelist_show_game_info(*(i32 *)net_session_block.net_session[0],0);
  }
  return;
}

/* 00430822 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl mp_meeting_wait_idle(void)

{
  int now;
  
  net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
  now = timer_ticks();
  if (((net_session_block.net_timeout_seconds * 0x3c <= now - civ_rating_title_font_block.mp_meeting_wait_start_i32) || (advisor_window_block.mp_meeting_reply != -1)) ||
     (net_session_block.nm_parley_cancel_count != 0)) {
    net_session_block.dialog_stack_top[0xf] = net_session_block.dialog_stack_top[0xf] | 0x400;
    wnd_end_modal_loop((ModalMenuWindow *)(*net_session_block.dialog_stack_top + 0x48));
    if (advisor_window_block.mp_meeting_reply == -1) {
      advisor_window_block.mp_meeting_reply = 0;
    }
  }
  return;
}

/* 0044528e auto */
i32 __cdecl net_prompt_ip_address(void)

{
  char *proto_addr;
  size_t input_len;
  i32 result;
  char input[260];
  Dialog dlg;
  int choice;
  i32 seh_prev;
  i8 *seh_handler;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  dialog_ctor(&dlg,0x4000);
  eh_state = 0;
  if ((net_session_block.net_lobby_launch_mode == -1) || (net_session_block.net_lobby_launch_mode == 1)) {
    proto_addr = XD_GetCurrentProtoAddr(net_session_block.net_adapter_index,net_session_block.net_protocol);
    if (proto_addr == (char *)0x0) {
      do {
        dialog_load_text_section(&dlg,(iptr)&str_game_7,(iptr)&str_ipaddress,0x1f,(iptr)&prefs_main_menu_choice_block.prefs_net_ip_address,0,0,0,1);
        choice = dialog_run_modal(&dlg,(iptr)input,0);
        if (choice == -1) {
          eh_state = 0xffffffff;
          /* inlined unwind funclet 00445407 */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
          result = 0;
          goto return_result;
        }
        input_len = _strlen(input);
      } while (input_len == 0);
      crt_strcpy(((i8 *)&prefs_main_menu_choice_block.prefs_net_ip_address),input);
    }
    else {
      proto_addr = XD_GetCurrentProtoAddr(net_session_block.net_adapter_index,net_session_block.net_protocol);
      crt_strcpy(((i8 *)&prefs_main_menu_choice_block.prefs_net_ip_address),proto_addr);
    }
  }
  else {
    crt_strcpy(((i8 *)&prefs_main_menu_choice_block.prefs_net_ip_address),((i8 *)&net_session_block.net_lobby_launch_info));
  }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 00445407 */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
  result = 1;
return_result:
  return result;
}

/* 0044542c auto */
i32 __cdecl net_prompt_player_name(void)

{
  size_t input_len;
  i32 result;
  char input[260];
  Dialog dlg;
  int choice;
  i32 seh_prev;
  i8 *seh_handler;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  dialog_ctor(&dlg,0x4000);
  eh_state = 0;
  if (net_session_block.net_lobby_launch_mode == -1) {
    do {
      dialog_load_text_section(&dlg,(iptr)&str_game_7,(iptr)&str_netname,0x1f,(iptr)&prefs_main_menu_choice_block.prefs_net_player_name,0,0,0,1);
      choice = dialog_run_modal(&dlg,(iptr)input,0);
      if (choice == -1) {
        eh_state = 0xffffffff;
        /* inlined unwind funclet 0044556d */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
        result = 0;
        goto return_result;
      }
      input_len = _strlen(input);
    } while (input_len == 0);
    crt_strcpy(((i8 *)&prefs_main_menu_choice_block.prefs_net_player_name),input);
    prefs_save_civ2dat();
  }
  else {
    _memset(((i8 *)&prefs_main_menu_choice_block.prefs_net_player_name),0,0x20);
    _strncpy(((i8 *)&prefs_main_menu_choice_block.prefs_net_player_name),((i8 *)&net_session_block.net_lobby_short_name),0x1f);
  }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 0044556d */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
  result = 1;
return_result:
  return result;
}

/* 00445592 auto */
i32 __cdecl net_prompt_game_name(void)

{
  size_t input_len;
  i32 result;
  char input[260];
  Dialog dlg;
  int choice;
  i32 seh_prev;
  i8 *seh_handler;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  dialog_ctor(&dlg,0x4000);
  eh_state = 0;
  if (net_session_block.net_lobby_launch_mode == -1) {
    do {
      dialog_load_text_section(&dlg,(iptr)&str_game_7,(iptr)&str_gamename,0x1f,(iptr)&prefs_main_menu_choice_block.prefs_net_game_name,0,0,0,1);
      choice = dialog_run_modal(&dlg,(iptr)input,0);
      if (choice == -1) {
        eh_state = 0xffffffff;
        /* inlined unwind funclet 004456ed */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
        result = 0;
        goto return_result;
      }
      input_len = _strlen(input);
    } while (input_len == 0);
    crt_strcpy(((i8 *)&prefs_main_menu_choice_block.prefs_net_game_name),input);
    crt_strcpy(((i8 *)&net_session_block.net_game_name),input);
    prefs_save_civ2dat();
  }
  else {
    _memset(((i8 *)&prefs_main_menu_choice_block.prefs_net_game_name),0,0x20);
    _strncpy(((i8 *)&prefs_main_menu_choice_block.prefs_net_game_name),((i8 *)&net_session_block.net_lobby_session_name),0x1f);
  }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 004456ed */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
  result = 1;
return_result:
  return result;
}

/* 00445e46 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __cdecl net_choose_civ_dialog(int title_offset)

{
  iptr civ2;
  iptr choice;
  int result;
  iptr leader_str;
  i32 ret;
  i32 arg6;
  i32 arg7;
  i32 arg8;
  iptr civ;
  u8 is_female;
  i8 input[260];
  int index;
  int available_count;
  int option_count2;
  iptr selected2;
  Dialog dlg;
  byte *option;
  iptr option_civs[8];
  int wait_start;
  i32 seh_prev;
  i8 *seh_handler;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  dialog_ctor(&dlg,0x4000);
  eh_state = 0;
  selected2 = 0;
  net_session_block.net_player_info_has_names_i32 = 0;
  net_session_block.net_player_info_has_titles_i32 = 0;
  do {
    dlg_reset(&dlg,0x801);
    dialog_prepend_title_label((iptr)&dlg,title_offset + 0x25e);
    index = 0;
    for (civ = 1; civ < 8; civ++) {
      if ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0) {
        text_clear();
        civ2 = civ_name_plural(civ);
        text_append(civ2);
        text_append_space();
        text_append_lparen();
        civ2 = civ_leader_name(civ);
        text_append(civ2);
        text_append_rparen();
        text_append_space();
        text_append_lparen();
        text_append_int((int)civs[civ].num_cities);
        text_append_space();
        text_append_label(0xc5);
        text_append((iptr)&str_empty_65);
        text_append_int((int)civs[civ].num_military_units);
        text_append_space();
        text_append_label(0xc4);
        text_append((iptr)&str_empty_66);
        result = index;
        index++;
        option = (byte *)dialog_add_option
                                     ((DialogOptionList *)&dlg,(iptr)&map_views_block.text_buffer,result,0);
        option_civs[*(int *)(option + 4)] = civ;
      }
    }
    option_count2 = index;
choose_loop:
    do {
      available_count = 0;
      for (index = 0; index < option_count2; index++) {
        option = (byte *)dialog_find_option
                                     ((DialogOptionList *)&dlg,index);
        if (option != (byte *)0x0) {
          (*(i8 *)((char *)&civ + 0)) = (byte)option_civs[*(int *)(option + 4)];
          if (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) &&
             ((1 << ((byte)civ & 0x1f) & (int)civ_saved_cursor_x_block.net_claimed_civs_mask) == 0)) {
            available_count++;
            dialog_set_option_disabled
                      ((DialogOptionList *)&dlg,*(iptr *)(option + 4),0);
            if ((RadioGroupDisableView *)dlg.radio_group != (RadioGroupDisableView *)0x0) {
              radiogrp_enable_item
                        ((RadioGroupEnableView *)dlg.radio_group,*(iptr *)(option + 4));
            }
          }
          else {
            dialog_set_option_disabled
                      ((DialogOptionList *)&dlg,*(iptr *)(option + 4),1);
            if ((RadioGroupDisableView *)dlg.radio_group != (RadioGroupDisableView *)0x0) {
              radiogrp_disable_item
                        ((RadioGroupDisableView *)dlg.radio_group,*(iptr *)(option + 4));
            }
          }
        }
      }
      if (available_count == 0) {
        popup_game((iptr)&str_joinedmax);
        dialog_close(&dlg);
        eh_state = 0xffffffff;
        /* inlined unwind funclet 004467fa */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
        ret = 1;
        goto return_ret;
      }
      for (index = 0; index < option_count2; index++) {
        option = (byte *)dialog_find_option
                                     ((DialogOptionList *)&dlg,selected2);
        if ((option != (byte *)0x0) && ((*option & 1) == 0)) {
          dialog_set_default_choice((DialogOptionList *)&dlg,*(iptr *)(option + 4));
          if ((RadioGroupDisableView *)dlg.radio_group != (RadioGroupDisableView *)0x0) {
            radiogrp_set_selected
                      ((RadioGroupSetSelView *)dlg.radio_group,*(i32 *)(option + 4));
          }
          break;
        }
        selected2++;
        if (selected2 == option_count2) {
          selected2 = 0;
        }
      }
      net_reset_msg_counts();
      net_session_block.net_wait_start_ticks_i32 = timer_ticks();
      dlg.style_flags = dlg.style_flags & 0xfffffbff;
      dlg.result_id = 0;
      dlg.result_extra = 0;
      dlg_pending_idle_callback = ((i8*)(net_lock_wait_idle_cb));
      choice = dlg_show_modal(&dlg,0);
      selected2 = radiogrp_get_selected((RadioGroupGetSelView *)dlg.radio_group);
      if (choice < 0) {
        eh_state = 0xffffffff;
        /* inlined unwind funclet 004467fa */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
        ret = 1;
        goto return_ret;
      }
    } while (net_session_block.nm_lock_data_count != 0);
    if (net_session_block.nm_server_canceled_count != 0) {
      popup_game_with_sprite((iptr)&str_gamecanceled,(iptr)&popup_info_icon_sprite,0);
      eh_state = 0xffffffff;
      /* inlined unwind funclet 004467fa */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
      ret = 1;
      goto return_ret;
    }
    civ2 = option_civs[choice];
    net_session_block.net_player_info_civ_i32 = civ2;
    selected2 = choice;
    net_send_message(0x30,0,0,civ2,0,0,0,0,0,0);
    if (net_session_block.net_host_flag == '\0') {
      net_reset_msg_counts();
      wait_start = timer_ticks();
      while (((net_session_block.nm_nation_accept_count == 0 && (net_session_block.nm_nation_reject_count == 0)) &&
             (result = timer_ticks(), result - wait_start < net_session_block.net_timeout_seconds * 0x3c))) {
        net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
      }
    }
    if ((net_session_block.nm_nation_accept_count == 0) && (net_session_block.nm_nation_reject_count == 0)) {
      dialog_close(&dlg);
      popup_game_with_sprite((iptr)&str_serverconnectfail,(iptr)&popup_info_icon_sprite,0);
      eh_state = 0xffffffff;
      /* inlined unwind funclet 004467fa */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
      ret = 1;
      goto return_ret;
    }
    if (net_session_block.nm_nation_reject_count != 0) {
      popup_game_with_sprite((iptr)&str_alreadychosen,(iptr)&popup_info_icon_sprite,0);
      goto choose_loop;
    }
    dialog_close(&dlg);
    (*(i8 *)((char *)&civ + 0)) = (byte)civ2;
    game.human_players = game.human_players | (byte)(1 << ((byte)civ & 0x1f));
    game.player_civ = (byte)civ;
    game.turn_civ = (byte)civ;
    game.game_options = game.game_options & 0xfffffeff;
    human_civ[0] = civ2;
    result = civ_check_password(civ2);
    if (result == 0) {
      game.human_players = game.human_players & ~(byte)(1 << ((byte)civ & 0x1f));
      net_send_message(0x31,0,0,civ2,0,0,0,0,0,0);
    }
    else {
      dlg_load_game_section(&dlg,(iptr)&str_gender_4,1);
      dialog_prepend_title_label((iptr)&dlg,title_offset + 0x25e);
      dialog_set_default_choice
                ((DialogOptionList *)&dlg,(uint)leaders[civs[game.player_civ].tribe].female);
      dialog_set_position
                ((DialogCore *)&dlg,0xfffffc19,
                 -(((int)(caption_font_block.screen_height - 0x1e0 + (caption_font_block.screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
      dlg_pending_idle_callback = ((i8*)(net_pump_idle_cb));
      result = dlg_show_modal(&dlg,0);
      net_session_block.net_player_info_gender_i32 = result;
      snd_play_effect(0x6a,0,0,0);
      if (result < 0) {
        game.human_players = game.human_players & ~(byte)(1 << ((byte)civ & 0x1f));
        net_send_message(0x31,0,0,civ2,0,0,0,0,0,0);
      }
      else {
        is_female = (u8)result;
        leaders[civs[game.player_civ].tribe].female = is_female;
        civs[human_civ[0]].flags = civs[human_civ[0]].flags & 0xfdff;
        if (result != 0) {
          civs[human_civ[0]].flags = civs[human_civ[0]].flags | 0x200;
        }
        arg8 = 1;
        arg7 = 0;
        arg6 = 0;
        ret = 0;
        leader_str = civ_leader_name((int)game.player_civ);
        result = dialog_load_text_section
                          (&dlg,(iptr)&str_game_7,(iptr)&str_name_4,0x17,leader_str,ret,arg6,arg7,arg8);
        if (result == 0) {
          dialog_prepend_title_label((iptr)&dlg,title_offset + 0x25e);
          dlg_pending_idle_callback = ((i8*)(net_pump_idle_cb));
          result = dialog_run_modal(&dlg,(iptr)input,0);
          if (result == 0) {
            crt_strcpy(&civ_names[game.player_civ].leader_name,input);
            crt_strcpy(((i8 *)&net_session_block.net_player_info_leader_name),input);
            net_session_block.net_player_info_tribe_name[0] = 0;
            net_session_block.net_player_info_adjective[0] = 0;
            eh_state = 0xffffffff;
            /* inlined unwind funclet 004467fa */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
            ret = 0;
return_ret:
            return ret;
          }
          game.human_players = game.human_players & ~(byte)(1 << ((byte)civ & 0x1f));
          net_send_message(0x31,0,0,civ2,0,0,0,0,0,0);
        }
      }
    }
  } while( true );
}

/* 00447170 auto */
void * __thiscall net_gamelist_view_scalar_dtor(void *self,uint flags)

{
  net_gamelist_view_dtor(self);
  if ((flags & 1) != 0) {
    operator_delete(self);
  }
  return self;
}

/* 004471c0 auto */
LobbyList * __thiscall lobby_list_scalar_dtor(LobbyList *self,uint flags)

{
  lobby_list_dtor(self);
  if ((flags & 1) != 0) {
    operator_delete(self);
  }
  return self;
}

/* 00450480 auto */
void __thiscall parley_create_advance_list_pane(WindowObjectView *self,iptr rect,iptr pane,int their_side)

{
  int result;
  int scroll_width;
  Control *new_ctrl;
  WindowObjectView *parent22;
  WindowObjectView *parent2;
  u32 hotspot;
  u32 scrollbar;
  uptr advance;
  RECT sb_rect;
  int can_see_other;
  iptr civ;
  i32 seh_prev;
  i8 *seh_handler;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  can_see_other = 0;
  sb_rect.left = *(int *)rect;
  sb_rect.top = *(i32 *)(rect + 4);
  sb_rect.right = *(int *)(rect + 8);
  sb_rect.bottom = *(i32 *)(rect + 0xc);
  result = civ_has_wonder(human_civ[0],0x18);
  if ((((result == 0) && (result = civ_has_wonder(human_civ[0],9), result == 0)) &&
      ((*(byte *)&civs[human_civ[0]].treaties[parley_wnd_block.parley_other_civ] & 0x80) == 0)) &&
     (((*(byte *)&civs[human_civ[0]].treaties[parley_wnd_block.parley_other_civ] & 8) == 0 &&
      (game.reveal_map == '\0')))) {
    can_see_other = 0;
  }
  else {
    can_see_other = 1;
  }
  ((u32 *)&((ViewWindow *)self)->advance_pane_item_counts)[pane] = 0;
  civ = human_civ[0];
  if ((their_side != 0) && (can_see_other != 0)) {
    civ = parley_wnd_block.parley_other_civ;
  }
  for (advance = 0; (int)advance < 100; advance++) {
    if (their_side == 0) {
      result = civ_has_advance(human_civ[0],advance);
      if ((result != 0) &&
         ((can_see_other == 0 || (result = civ_has_advance(parley_wnd_block.parley_other_civ,advance), result == 0)))) {
        ((u32 *)&((ViewWindow *)self)->advance_pane_items)[((u32 *)&((ViewWindow *)self)->advance_pane_item_counts)[pane] + pane * 0x801] = advance;
        ((u32 *)&((PictureWindow *)self)->advance_pane_item_flags)[((u32 *)&((ViewWindow *)self)->advance_pane_item_counts)[pane] + pane * 0x801] = 0;
        ((u32 *)&((ViewWindow *)self)->advance_pane_item_counts)[pane]++;
      }
    }
    else if (((human_civ[0] == civ) ||
             (result = civ_has_advance(human_civ[0],advance), result != 0)) ||
            (result = civ_has_advance(civ,advance), result == 0)) {
      if (((human_civ[0] == civ) &&
          (result = civ_has_advance(human_civ[0],advance), result == 0)) &&
         (((int)advance < 0x59 && (advances[advance].enabled == 1)))) {
        ((u32 *)&((ViewWindow *)self)->advance_pane_items)[((u32 *)&((ViewWindow *)self)->advance_pane_item_counts)[pane] + pane * 0x801] = advance;
        ((u32 *)&((PictureWindow *)self)->advance_pane_item_flags)[((u32 *)&((ViewWindow *)self)->advance_pane_item_counts)[pane] + pane * 0x801] = 0;
        ((u32 *)&((ViewWindow *)self)->advance_pane_item_counts)[pane]++;
      }
    }
    else {
      ((u32 *)&((ViewWindow *)self)->advance_pane_items)[((u32 *)&((ViewWindow *)self)->advance_pane_item_counts)[pane] + pane * 0x801] = advance;
      ((u32 *)&((PictureWindow *)self)->advance_pane_item_flags)[((u32 *)&((ViewWindow *)self)->advance_pane_item_counts)[pane] + pane * 0x801] = 0;
      ((u32 *)&((ViewWindow *)self)->advance_pane_item_counts)[pane]++;
    }
  }
  if ((int)((u32 *)&((ViewWindow *)self)->advance_pane_item_counts)[pane] < 1) {
    ((u32 *)&((PictureWindow *)self)->parley_list_top_index)[pane] = 0xffffffff;
  }
  else {
    ((u32 *)&((PictureWindow *)self)->parley_list_top_index)[pane] = 0;
  }
  ((u32 *)&((ViewWindow *)self)->advance_pane_columns)[pane] = 3;
  ((u32 *)&((ViewWindow *)self)->advance_pane_rects)[pane * 4] = *(u32 *)rect;
  ((u32 *)&((ViewWindow *)self)->advance_pane_rect_top)[pane * 4] = *(u32 *)(rect + 4);
  ((u32 *)&((ViewWindow *)self)->advance_pane_rect_right)[pane * 4] = *(u32 *)(rect + 8);
  ((u32 *)&((ViewWindow *)self)->advance_pane_rect_bottom)[pane * 4] = *(u32 *)(rect + 0xc);
  if ((int)((u32 *)&((PictureWindow *)self)->parley_list_page_rows)[pane] < (int)((u32 *)&((ViewWindow *)self)->advance_pane_item_counts)[pane]) {
    scroll_width = GetSystemMetrics(2);
    result = sb_rect.right;
    ((u32 *)&((ViewWindow *)self)->advance_pane_rect_right)[pane * 4] -= scroll_width;
    sb_rect.left = GetSystemMetrics(2);
    sb_rect.left = result - sb_rect.left;
    new_ctrl = operator_new(0x40);
    eh_state = 0;
    if (new_ctrl == (Control *)0x0) {
      scrollbar = 0;
    }
    else {
      scrollbar = scrollbar_ctor(new_ctrl);
    }
    eh_state = 0xffffffff;
    ((u32 *)&((ViewWindow *)self)->advance_list_scrollbars)[pane] = scrollbar;
    if (self == (WindowObjectView *)0x0) {
      parent2 = (WindowObjectView *)0x0;
    }
    else {
      parent2 = self + 0x12;
    }
    scrollbar_create
              ((Control *)((u32 *)&((ViewWindow *)self)->advance_list_scrollbars)[pane],(iptr)parent2,pane + 0x411,
               (iptr)&sb_rect,1);
    scrollbar_set_range
              ((Control *)((u32 *)&((ViewWindow *)self)->advance_list_scrollbars)[pane],0,
               (((u32 *)&((ViewWindow *)self)->advance_pane_item_counts)[pane] - 1) - ((u32 *)&((PictureWindow *)self)->parley_list_page_rows)[pane]);
    scrollbar_set_pos((ClickControl *)((u32 *)&((ViewWindow *)self)->advance_list_scrollbars)[pane],0);
    scrollbar_set_page_size
              ((Control *)((u32 *)&((ViewWindow *)self)->advance_list_scrollbars)[pane],((u32 *)&((PictureWindow *)self)->parley_list_page_rows)[pane]);
    scrollbar_set_callback
              ((Control *)((u32 *)&((ViewWindow *)self)->advance_list_scrollbars)[pane],
               (iptr)(((void *)(iptr)parley_advance_list0_on_scroll) + ((pane == 0) - 1 & 0xffffdd37)));
    scrollbar_set_track_callback
              ((ScrollbarTrackSetView *)((u32 *)&((ViewWindow *)self)->advance_list_scrollbars)[pane],
               (iptr)(((void *)(iptr)parley_advance_list0_on_scroll) + ((pane == 0) - 1 & 0xffffdd37)));
  }
  new_ctrl = operator_new(0x40);
  eh_state = 1;
  if (new_ctrl == (Control *)0x0) {
    hotspot = 0;
  }
  else {
    hotspot = hotspot_ctor(new_ctrl);
  }
  eh_state = 0xffffffff;
  ((u32 *)&((ViewWindow *)self)->advance_list_hotspots)[pane] = hotspot;
  if (self == (WindowObjectView *)0x0) {
    parent22 = (WindowObjectView *)0x0;
  }
  else {
    parent22 = self + 0x12;
  }
  hotspot_create
            ((ClickControl *)((u32 *)&((ViewWindow *)self)->advance_list_hotspots)[pane],(iptr)parent22,pane + 0x413,
             (iptr)(self + pane * 4 + 0xf0));
  hotspot_set_click_callback((HotspotClickSetView *)((u32 *)&((ViewWindow *)self)->advance_list_hotspots)[pane],(iptr)parley_advance_list_on_click);
  hotspot_set_dblclick_callback((HotspotDblClickSetView *)((u32 *)&((ViewWindow *)self)->advance_list_hotspots)[pane],(iptr)parley_advance_list_on_click);
  parley_draw_advance_list(pane);
  return;
}

/* 00450ae6 auto */
void __cdecl parley_advance_list0_on_scroll(i32 pos)

{
  parley_advance_list_on_scroll(0,pos);
  return;
}

/* 00450b22 auto */
void __cdecl parley_advance_list_on_scroll(int pane,i32 pos)

{
  int child;
  iptr window;
  
  child = wnd_get_active_child();
  if (child == 0) {
    window = 0;
  }
  else {
    window = child - 0x48;
  }
  wnd_activate((Wnd *)(window + 0x48));
  *(i32 *)(window + 0x10410 + pane * 4) = pos;
  parley_draw_advance_list(pane);
  return;
}

/* 00450b83 auto */
void __cdecl parley_advance_list_on_click(int control_id)

{
  uint *sel_flag;
  int row;
  int key_down;
  int range_end;
  int i;
  i32 cursor_y;
  i32 cursor_x;
  int pane;
  iptr window;
  
  row = wnd_get_active_child();
  if (row == 0) {
    window = 0;
  }
  else {
    window = row - 0x48;
  }
  wnd_activate((Wnd *)(window + 0x48));
  pane = control_id - 0x413;
  wnd_get_cursor_pos
            ((WndBase *)(window + 0x48),(iptr)&cursor_x,(iptr)&cursor_y);
  if (((*(int *)(window + 1000 + pane * 4) != 0) &&
      (row = parley_advance_list_hit_test(cursor_x,cursor_y,pane), -1 < row)) &&
     (row < *(int *)(window + 1000 + pane * 4))) {
    key_down = wnd_is_shift_down((void *)(window + 0x48));
    if (key_down == 0) {
      key_down = wnd_is_ctrl_down((void *)(window + 0x48));
      if (key_down == 0) {
        for (i = 0; i < *(int *)(window + 1000 + pane * 4);
            i = i + 1) {
          if (i != row) {
            *(i32 *)(i * 4 + pane * 0x2004 + 0x8400 + window) = 0;
          }
        }
        *(int *)(window + 0x10418 + pane * 4) = row;
        sel_flag = (uint *)(row * 4 + pane * 0x2004 + 0x8400 + window);
        *sel_flag = *sel_flag ^ 1;
      }
      else {
        *(int *)(window + 0x10418 + pane * 4) = row;
        sel_flag = (uint *)(row * 4 + pane * 0x2004 + 0x8400 + window);
        *sel_flag = *sel_flag ^ 1;
      }
    }
    else {
      for (i = 0; i < *(int *)(window + 1000 + pane * 4); i++)
      {
        *(i32 *)(i * 4 + pane * 0x2004 + 0x8400 + window) = 0;
      }
      if (*(int *)(window + 0x10418 + pane * 4) < row) {
        i = *(int *)(window + 0x10418 + pane * 4);
        range_end = row;
      }
      else {
        range_end = *(int *)(window + 0x10418 + pane * 4);
        i = row;
      }
      for (; i <= range_end; i++) {
        *(i32 *)(i * 4 + pane * 0x2004 + 0x8400 + window) = 1;
      }
    }
    parley_draw_advance_list(pane);
  }
  return;
}

/* 00450df6 auto */
int __cdecl parley_advance_list_hit_test(int px,int py,int pane)

{
  iptr child;
  int result;
  int list_height;
  iptr window;
  
  child = wnd_get_active_child();
  if (child == 0) {
    window = 0;
  }
  else {
    window = child - 0x48;
  }
  if (py < *(int *)(pane * 0x10 + 0x3c4 + window)) {
    result = -1;
  }
  else if (py < *(int *)(pane * 0x10 + 0x3cc + window)) {
    if (px < *(int *)(pane * 0x10 + 0x3c0 + window)) {
      result = -3;
    }
    else if (px < *(int *)(pane * 0x10 + 0x3c8 + window)) {
      result = *(int *)(pane * 0x10 + 0x3c4 + window);
      list_height = rect_height(pane * 0x10 + window + 0x3c0);
      result = (py - result) / (list_height / (*(int *)(window + 0x10420 + pane * 4) + 1)) +
              *(int *)(window + 0x10410 + pane * 4);
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

/* 00450f0b auto */
void __cdecl parley_draw_advance_list(iptr pane)

{
  u8 *has_sel;
  int tmp;
  int tmp2;
  iptr name_label;
  int icon_x;
  i32 bg_color2;
  i8 sprite_rect[16];
  int text_y_offset;
  iptr advance;
  int icon_step;
  int row;
  int row_top;
  int list_left;
  int list_width2;
  int shadow_color2;
  int text_x_offset;
  Sprite *icon_sprite;
  int text_color2;
  ViewWindow *window;
  int selected2;
  tagRECT row_rect;
  int row_height;
  i8 saved_clip[16];
  GameFont *font2;
  
  tmp = wnd_get_active_child();
  if (tmp == 0) {
    window = (ViewWindow *)0x0;
  }
  else {
    window = (ViewWindow *)(tmp - 0x48);
  }
  surface_get_clip((DibSurface *)window,(iptr)saved_clip);
  surface_set_clip((DibSurface *)window,(iptr)((u8 *)&window->advance_pane_rects + pane * 0x10));
  surface_fill_rect
            ((DibSurface *)window,(iptr)((u8 *)&window->advance_pane_rects + pane * 0x10),list_bg_color);
  if (window->large_layout == 0) {
    font2 = (GameFont *)((i8 *)&font_size14);
  }
  else {
    font2 = (GameFont *)((i8 *)&font_size21);
  }
  list_left = *(int *)((u8 *)&window->advance_pane_rects + pane * 0x10);
  list_width2 = rect_width((iptr)((u8 *)&window->advance_pane_rects + pane * 0x10));
  row_height = rect_height((iptr)((u8 *)&window->advance_pane_rects + pane * 0x10));
  row_height = row_height / (*(int *)(((PictureWindow *)window)->parley_pane_rows_base + pane * 4 + 0x38) + 1);
  tmp = row_height / 2;
  tmp2 = font_cached_height(font2);
  text_y_offset = tmp - tmp2 / 2;
  has_sel = window->pane_selection_flags_area + pane * 4 - 0x1c;
  has_sel[0] = '\0';
  has_sel[1] = '\0';
  has_sel[2] = '\0';
  has_sel[3] = '\0';
  row = 0;
  do {
    if (*(int *)((u8 *)&window->advance_pane_rects + pane * 4 + 0x28) <= row) {
draw_rows:
      for (row = 0; row < *(int *)(((PictureWindow *)window)->parley_pane_rows_base + pane * 4 + 0x38) + 1;
          row = row + 1) {
        row_top = *(int *)((u8 *)&window->advance_pane_rects + pane * 0x10 + 4) + row * row_height +
                   panel_margin_y;
        SetRect(&row_rect,list_left,row_top,list_left + list_width2,row_top + row_height);
        if (((row == 0) || (*(int *)(((PictureWindow *)window)->parley_pane_rows_base + pane * 4 + 0x28) != -1)) &&
           (*(int *)(((PictureWindow *)window)->parley_pane_rows_base + pane * 4 + 0x28) + row <
            *(int *)((u8 *)&window->advance_pane_rects + pane * 4 + 0x28))) {
          selected2 = *(int *)(pane * 0x2004 +
                              (*(int *)(((PictureWindow *)window)->parley_pane_rows_base + pane * 4 + 0x28) + row) * 4
                              + 0x8400 + (int)window);
          if (selected2 == 0) {
            text_color2 = list_text_color;
            shadow_color2 = list_shadow_color;
          }
          else {
            text_color2 = dlg_sel_text_color;
            shadow_color2 = dlg_sel_text_shadow_color;
          }
          advance = *(int *)(pane * 0x2004 +
                              (*(int *)(((PictureWindow *)window)->parley_pane_rows_base + pane * 4 + 0x28) + row) * 4
                              + 0x3f0 + (int)window);
          icon_sprite = (Sprite *)
                     (((i8 *)&government_sprites_block.advance_category_icon_sprites) +
                     (char)advances[advance].category * 0xf0 +
                     (char)advances[advance].epoch * 0x3c);
          tmp = sprite_get_width(icon_sprite);
          text_x_offset = panel_margin_x * 3 + tmp * 2;
          row_rect.left += text_x_offset;
          if (selected2 == 0) {
            bg_color2 = list_bg_color;
          }
          else {
            bg_color2 = list_sel_bg_color;
          }
          surface_fill_rect((DibSurface *)window,(iptr)&row_rect,bg_color2);
          if (*(int *)(((PictureWindow *)window)->parley_pane_rows_base + pane * 4 + 0x28) == -1) {
            text_clear();
            if ((pane == 0) || (parley_wnd_block.parley_mode == 7)) {
              text_append_label(0x36b);
            }
            else {
              text_append_label(0x36a);
            }
            has_sel = window->pane_selection_flags_area + pane * 4 - 0x1c;
            has_sel[0] = '\0';
            has_sel[1] = '\0';
            has_sel[2] = '\0';
            has_sel[3] = '\0';
            tmp = rect_width((iptr)((u8 *)&window->advance_pane_rects + pane * 0x10));
            tmp2 = font_text_width(font2,(iptr)&map_views_block.text_buffer);
            text_x_offset = (tmp - tmp2) / 2;
          }
          else {
            icon_step = sprite_get_width(icon_sprite);
            icon_step += panel_margin_x * 2;
            icon_x = icon_step;
            if ((*(int *)(((PictureWindow *)window)->parley_pane_rows_base + pane * 4 + 0x28) + row & 1U) == 0) {
              icon_x = panel_margin_x;
            }
            tmp2 = row_top + row_height / 2;
            tmp = sprite_get_height(icon_sprite);
            sprite_draw
                      (icon_sprite,(iptr)sprite_rect,(iptr)&parley_wnd_block.parley_wnd,list_left + icon_x,tmp2 - tmp / 2);
            text_clear();
            name_label = label_string(advances[advance].name);
            text_append(name_label);
          }
          if (shadow_color2 != text_color2) {
            gfx_set_text_color_index(shadow_color2);
            surface_draw_text
                      ((DibSurface *)window,(iptr)font2,(iptr)&map_views_block.text_buffer,list_left + text_x_offset + 2,
                       row_top + text_y_offset + 1,5);
            gfx_set_text_color_index(text_color2);
            surface_draw_text
                      ((DibSurface *)window,(iptr)font2,(iptr)&map_views_block.text_buffer,list_left + text_x_offset + 1,
                       row_top + text_y_offset,5);
          }
          gfx_set_text_color_index(text_color2);
          surface_draw_text
                    ((DibSurface *)window,(iptr)font2,(iptr)&map_views_block.text_buffer,list_left + text_x_offset,
                     row_top + text_y_offset,5);
        }
      }
      surface_set_clip((DibSurface *)window,(iptr)saved_clip);
      parley_update_buttons(window);
      ctrl_show_and_redraw(*(Control **)(window->rate_values + pane * 4 + 0x20))
      ;
      return;
    }
    if (*(int *)(pane * 0x2004 + row * 4 + 0x8400 + (int)window) != 0) {
      has_sel = window->pane_selection_flags_area + pane * 4 - 0x1c;
      has_sel[0] = 1;
      has_sel[1] = '\0';
      has_sel[2] = '\0';
      has_sel[3] = '\0';
      goto draw_rows;
    }
    row++;
  } while( true );
}

/* 004683f0 auto */
void __thiscall
parley_create_unit_list_pane(ListPaneWindow *self,iptr rect,int pane,i32 own_side)

{
  u8 *field;
  int sb_right_orig;
  int scroll_width;
  Control *new_ctrl;
  u8 *parent22;
  u8 *parent2;
  i32 hotspot;
  i32 scrollbar;
  RECT sb_rect;
  int window;
  i32 seh_prev;
  i8 *seh_handler;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  window = wnd_get_active_child();
  if (window == 0) {
    window = 0;
  }
  else {
    window -= 0x48;
  }
  *(i32 *)(((i8 *)&prefs_main_menu_choice_block.parley_list_own_side) + pane * 4) = own_side;
  sb_rect.left = *(int *)rect;
  sb_rect.top = *(i32 *)(rect + 4);
  sb_rect.right = *(int *)(rect + 8);
  sb_rect.bottom = *(i32 *)(rect + 0xc);
  prefs_main_menu_choice_block.parley_units_by_city = 0;
  parley_build_unit_list(self,pane,0);
  if (*(int *)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 4 + 0x4c) < 1) {
    field = ((PictureWindow *)self)->parley_pane_arrays_base + pane * 4 + 0x30;
    field[0] = 0xff;
    field[1] = 0xff;
    field[2] = 0xff;
    field[3] = 0xff;
  }
  else {
    field = ((PictureWindow *)self)->parley_pane_arrays_base + pane * 4 + 0x30;
    field[0] = '\0';
    field[1] = '\0';
    field[2] = '\0';
    field[3] = '\0';
  }
  field = ((PediaRedrawView *)self)->pedia_pane_layout + pane * 4 + 0x44;
  field[0] = '\0';
  field[1] = '\0';
  field[2] = '\0';
  field[3] = '\0';
  *(i32 *)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 0x10 + 0x24) = *(i32 *)rect;
  *(i32 *)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 0x10 + 0x28) = *(i32 *)(rect + 4);
  *(i32 *)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 0x10 + 0x2c) = *(i32 *)(rect + 8);
  *(i32 *)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 0x10 + 0x30) = *(i32 *)(rect + 0xc);
  if (*(int *)(((PictureWindow *)self)->parley_pane_arrays_base + pane * 4 + 0x40) <
      *(int *)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 4 + 0x4c)) {
    scroll_width = GetSystemMetrics(2);
    sb_right_orig = sb_rect.right;
    *(int *)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 0x10 + 0x2c) =
         *(int *)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 0x10 + 0x2c) - scroll_width;
    sb_rect.left = GetSystemMetrics(2);
    sb_rect.left = sb_right_orig - sb_rect.left;
    new_ctrl = operator_new(0x40);
    eh_state = 0;
    if (new_ctrl == (Control *)0x0) {
      scrollbar = 0;
    }
    else {
      scrollbar = scrollbar_ctor(new_ctrl);
    }
    eh_state = 0xffffffff;
    *(i32 *)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 4 - 0x20) = scrollbar;
    if (self == (ListPaneWindow *)0x0) {
      parent2 = (u8 *)0x0;
    }
    else {
      parent2 = self->window_2;
    }
    scrollbar_create
              (*(Control **)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 4 - 0x20),(iptr)parent2,
               pane + 0x3fa,(iptr)&sb_rect,1);
    scrollbar_set_range
              (*(Control **)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 4 - 0x20),0,
               *(int *)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 4 + 0x4c) -
               *(int *)(((PictureWindow *)self)->parley_pane_arrays_base + pane * 4 + 0x40));
    scrollbar_set_pos(*(ClickControl **)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 4 - 0x20),0);
    scrollbar_set_page_size
              (*(Control **)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 4 - 0x20),
               *(int *)(((PictureWindow *)self)->parley_pane_arrays_base + pane * 4 + 0x40) - 1);
    scrollbar_set_callback
              (*(Control **)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 4 - 0x20),
               (iptr)(((void *)(iptr)parley_unit_list_scroll_left) + ((pane == 0) - 1 & 0x276)));
    scrollbar_set_track_callback
              (*(ScrollbarTrackSetView **)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 4 - 0x20),
               (iptr)(((void *)(iptr)parley_unit_list_scroll_left) + ((pane == 0) - 1 & 0x276)));
  }
  new_ctrl = operator_new(0x40);
  eh_state = 1;
  if (new_ctrl == (Control *)0x0) {
    hotspot = 0;
  }
  else {
    hotspot = hotspot_ctor(new_ctrl);
  }
  eh_state = 0xffffffff;
  *(i32 *)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 4 - 0x18) = hotspot;
  if (self == (ListPaneWindow *)0x0) {
    parent22 = (u8 *)0x0;
  }
  else {
    parent22 = self->window_2;
  }
  hotspot_create
            (*(ClickControl **)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 4 - 0x18),(iptr)parent22,
             pane + 0x3fc,(iptr)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 0x10 + 0x24));
  hotspot_set_click_callback(*(HotspotClickSetView **)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 4 - 0x18),(iptr)parley_unit_list_on_click);
  hotspot_set_dblclick_callback(*(HotspotDblClickSetView **)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 4 - 0x18),(iptr)parley_unit_list_on_click);
  parley_draw_unit_list(pane);
  return;
}

/* 00468797 auto */
void __cdecl parley_unit_list_scroll_left(i32 pos)

{
  parley_unit_list_on_scroll(0,pos);
  return;
}

/* 004687d3 auto */
void __cdecl parley_unit_list_on_scroll(int pane,i32 pos)

{
  int child;
  iptr window;
  
  child = wnd_get_active_child();
  if (child == 0) {
    window = 0;
  }
  else {
    window = child - 0x48;
  }
  wnd_activate((Wnd *)(window + 0x48));
  *(i32 *)(window + 0x10410 + pane * 4) = pos;
  parley_draw_unit_list(pane);
  return;
}

/* 00468834 auto */
void __cdecl parley_unit_list_on_click(int control_id)

{
  uint *sel_flag;
  int row;
  int key_down;
  int range_end;
  int i;
  i32 cursor_y;
  i32 cursor_x;
  int pane;
  iptr window;
  
  row = wnd_get_active_child();
  if (row == 0) {
    window = 0;
  }
  else {
    window = row - 0x48;
  }
  wnd_activate((Wnd *)(window + 0x48));
  pane = control_id - 0x3fc;
  wnd_get_cursor_pos
            ((WndBase *)(window + 0x48),(iptr)&cursor_x,(iptr)&cursor_y);
  if (((*(int *)(window + 1000 + pane * 4) != 0) &&
      (row = parley_unit_list_hit_test(cursor_x,cursor_y,pane), -1 < row)) &&
     (row < *(int *)(window + 1000 + pane * 4))) {
    key_down = wnd_is_shift_down((void *)(window + 0x48));
    if (key_down == 0) {
      key_down = wnd_is_ctrl_down((void *)(window + 0x48));
      if (key_down == 0) {
        for (i = 0; i < *(int *)(window + 1000 + pane * 4);
            i = i + 1) {
          if (i != row) {
            *(i32 *)(pane * 0x2004 + i * 4 + 0x8400 + window) = 0;
          }
        }
        *(int *)(window + 0x10418 + pane * 4) = row;
        sel_flag = (uint *)(pane * 0x2004 + row * 4 + 0x8400 + window);
        *sel_flag = *sel_flag ^ 1;
      }
      else {
        *(int *)(window + 0x10418 + pane * 4) = row;
        sel_flag = (uint *)(pane * 0x2004 + row * 4 + 0x8400 + window);
        *sel_flag = *sel_flag ^ 1;
      }
    }
    else {
      for (i = 0; i < *(int *)(window + 1000 + pane * 4); i++)
      {
        *(i32 *)(pane * 0x2004 + i * 4 + 0x8400 + window) = 0;
      }
      if (*(int *)(window + 0x10418 + pane * 4) < row) {
        i = *(int *)(window + 0x10418 + pane * 4);
        range_end = row;
      }
      else {
        range_end = *(int *)(window + 0x10418 + pane * 4);
        i = row;
      }
      for (; i <= range_end; i++) {
        *(i32 *)(pane * 0x2004 + i * 4 + 0x8400 + window) = 1;
      }
    }
    parley_draw_unit_list(pane);
  }
  return;
}

/* 00468aa7 auto */
int __cdecl parley_unit_list_hit_test(int px,int py,int pane)

{
  iptr child;
  int result;
  int list_height;
  iptr window;
  
  child = wnd_get_active_child();
  if (child == 0) {
    window = 0;
  }
  else {
    window = child - 0x48;
  }
  if (py < *(int *)(pane * 0x10 + 0x3c4 + window)) {
    result = -1;
  }
  else if (py < *(int *)(pane * 0x10 + 0x3cc + window)) {
    if (px < *(int *)(pane * 0x10 + 0x3c0 + window)) {
      result = -3;
    }
    else if (px < *(int *)(pane * 0x10 + 0x3c8 + window)) {
      result = *(int *)(pane * 0x10 + 0x3c4 + window);
      list_height = rect_height(pane * 0x10 + window + 0x3c0);
      result = (py - result) / (list_height / *(int *)(window + 0x10420 + pane * 4)) +
              *(int *)(window + 0x10410 + pane * 4);
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

/* 00468bb9 auto */
void __cdecl parley_draw_unit_list(iptr pane)

{
  u8 *has_sel;
  int tmp;
  int tmp2;
  iptr str;
  int row_mid;
  i32 denom;
  int icon_x;
  i32 bg_color2;
  int icon_width;
  i8 sprite_rect[16];
  int text_y_offset;
  iptr unit;
  int icon_step;
  int row;
  int row_top;
  int list_left;
  int list_width2;
  int shadow_color2;
  int text_x_offset;
  Sprite *unit_sprite;
  int text_color2;
  ViewWindow *this2;
  int selected2;
  tagRECT row_rect;
  int row_height;
  i8 saved_clip[16];
  GameFont *font2;
  
  tmp = wnd_get_active_child();
  if (tmp == 0) {
    this2 = (ViewWindow *)0x0;
  }
  else {
    this2 = (ViewWindow *)(tmp - 0x48);
  }
  surface_get_clip((DibSurface *)this2,(iptr)saved_clip);
  surface_set_clip((DibSurface *)this2,(iptr)((u8 *)&this2->advance_pane_rects + pane * 0x10));
fill_list_bg:
  surface_fill_rect
            ((DibSurface *)this2,(iptr)((u8 *)&this2->advance_pane_rects + pane * 0x10),list_bg_color);
  if (this2->large_layout == 0) {
    font2 = (GameFont *)((i8 *)&font_size14);
  }
  else {
    font2 = (GameFont *)((i8 *)&font_size21);
  }
  list_left = *(int *)((u8 *)&this2->advance_pane_rects + pane * 0x10);
  list_width2 = rect_width((iptr)((u8 *)&this2->advance_pane_rects + pane * 0x10));
  row_height = rect_height((iptr)((u8 *)&this2->advance_pane_rects + pane * 0x10));
  row_height = row_height / *(int *)(((PictureWindow *)this2)->parley_pane_rows_base + pane * 4 + 0x38);
  tmp = row_height / 2;
  tmp2 = font_cached_height(font2);
  text_y_offset = tmp - tmp2 / 2;
  has_sel = this2->pane_selection_flags_area + pane * 4 - 0x1c;
  has_sel[0] = '\0';
  has_sel[1] = '\0';
  has_sel[2] = '\0';
  has_sel[3] = '\0';
  for (row = 0; row < *(int *)((u8 *)&this2->advance_pane_rects + pane * 4 + 0x28);
      row = row + 1) {
    if (*(int *)(row * 4 + pane * 0x2004 + 0x8400 + (int)this2) != 0) {
      has_sel = this2->pane_selection_flags_area + pane * 4 - 0x1c;
      has_sel[0] = 1;
      has_sel[1] = '\0';
      has_sel[2] = '\0';
      has_sel[3] = '\0';
      break;
    }
  }
  row = 0;
  do {
    if (*(int *)(((PictureWindow *)this2)->parley_pane_rows_base + pane * 4 + 0x38) <= row) {
restore_clip_and_finish:
      surface_set_clip((DibSurface *)this2,(iptr)saved_clip);
      parley_update_buttons(this2);
      ctrl_show_and_redraw(*(Control **)(this2->rate_values + pane * 4 + 0x20))
      ;
      return;
    }
    row_top = *(int *)((u8 *)&this2->advance_pane_rects + pane * 0x10 + 4) + row_height * row;
    SetRect(&row_rect,list_left,row_top,list_width2 + list_left,row_height + row_top);
    if ((row != 0) && (*(int *)(((PictureWindow *)this2)->parley_pane_rows_base + pane * 4 + 0x28) == -1))
    goto restore_clip_and_finish;
    if (*(int *)(((PictureWindow *)this2)->parley_pane_rows_base + pane * 4 + 0x28) + row <
        *(int *)((u8 *)&this2->advance_pane_rects + pane * 4 + 0x28)) {
      selected2 = *(int *)(pane * 0x2004 +
                          (*(int *)(((PictureWindow *)this2)->parley_pane_rows_base + pane * 4 + 0x28) + row) * 4 +
                          0x8400 + (int)this2);
      if (selected2 == 0) {
        text_color2 = list_text_color;
        shadow_color2 = list_shadow_color;
      }
      else {
        text_color2 = dlg_sel_text_color;
        shadow_color2 = dlg_sel_text_shadow_color;
      }
      unit = 0;
      if ((0 < *(int *)((u8 *)&this2->advance_pane_rects + pane * 4 + 0x28)) &&
         (unit = parley_find_unit_by_id
                               ((WindowObjectView *)this2,
                                *(i32 *)
                                 (pane * 0x2004 +
                                  (*(int *)(((PictureWindow *)this2)->parley_pane_rows_base + pane * 4 + 0x28) + row)
                                  * 4 + 0x43f8 + (int)this2)), unit < 0)) break;
      unit_sprite = (Sprite *)(((i8 *)&pollution_sprite_block.unit_sprites) + (uint)units[unit].type * 0x3c);
      if (this2->large_layout == 0) {
        tmp = sprite_get_width(unit_sprite);
        icon_width = (tmp * 2) / 3;
      }
      else {
        icon_width = sprite_get_width(unit_sprite);
      }
      text_x_offset = (-(uint)(this2->large_layout == 0) & 0xfffffffc) + 10 + icon_width * 2;
      row_rect.left = row_rect.left + text_x_offset - 3;
      if (selected2 == 0) {
        bg_color2 = list_bg_color;
      }
      else {
        bg_color2 = list_sel_bg_color;
      }
      surface_fill_rect((DibSurface *)this2,(iptr)&row_rect,bg_color2);
      if (*(int *)(((PictureWindow *)this2)->parley_pane_rows_base + pane * 4 + 0x28) == -1) {
        text_clear();
        str = label_string(*(i32 *)(label_string_ids + 0xb7c));
        text_append(str);
        has_sel = this2->pane_selection_flags_area + pane * 4 - 0x1c;
        has_sel[0] = '\0';
        has_sel[1] = '\0';
        has_sel[2] = '\0';
        has_sel[3] = '\0';
        tmp = rect_width((iptr)((u8 *)&this2->advance_pane_rects + pane * 0x10));
        tmp2 = font_text_width(font2,(iptr)&map_views_block.text_buffer);
        text_x_offset = (tmp - tmp2) / 2;
      }
      else {
        denom = 0x30;
        tmp = font_cached_height(font2);
        gfx_set_scale_ratio(tmp * 2,denom);
        tmp = font_cached_height(font2);
        icon_step = (tmp << 7) / 0x30;
        icon_x = icon_step;
        if ((*(int *)(((PictureWindow *)this2)->parley_pane_rows_base + pane * 4 + 0x28) + row & 1U) == 0) {
          icon_x = 0;
        }
        row_mid = row_top + row_height / 2;
        tmp = sprite_get_height(unit_sprite);
        tmp2 = font_cached_height(font2);
        sprite_draw
                  (unit_sprite,(iptr)sprite_rect,(iptr)&parley_wnd_block.parley_wnd,list_left + icon_x,
                   row_mid - (tmp * tmp2) / 0x30);
        gfx_set_scale_ratio(1,1);
        if (prefs_main_menu_choice_block.parley_units_by_city == 0) {
          text_clear();
          text_append_string_id(unit_types[units[unit].type].name);
          if (((parley_wnd_block.parley_mode == 9) ||
              (((parley_wnd_block.parley_mode == 0xe && (pane == 0)) && (this2->left_side_accepted != '\0')))) ||
             ((((parley_wnd_block.parley_mode == 0xe && (pane == 1)) && (this2->right_side_accepted != '\0')) ||
              ((parley_wnd_block.parley_mode == 0xf && (this2->right_side_accepted != '\0')))))) {
            text_append_str((iptr)&str_empty_76);
            str = unit_home_city_name(unit);
            text_append_str(str);
            text_append_str((iptr)&str_empty_77);
          }
        }
        else {
          text_clear();
          str = unit_home_city_name(unit);
          text_append_str(str);
          text_append_str((iptr)&str_empty_78);
          text_append_string_id(unit_types[units[unit].type].name);
          text_append_str((iptr)&str_empty_79);
        }
      }
      if (shadow_color2 != text_color2) {
        gfx_set_text_color_index(shadow_color2);
        surface_draw_text
                  ((DibSurface *)this2,(iptr)font2,(iptr)&map_views_block.text_buffer,text_x_offset + list_left + 2,
                   text_y_offset + row_top + 1,5);
        gfx_set_text_color_index(text_color2);
        surface_draw_text
                  ((DibSurface *)this2,(iptr)font2,(iptr)&map_views_block.text_buffer,text_x_offset + list_left + 1,
                   text_y_offset + row_top,5);
      }
      gfx_set_text_color_index(text_color2);
      surface_draw_text
                ((DibSurface *)this2,(iptr)font2,(iptr)&map_views_block.text_buffer,text_x_offset + list_left,
                 text_y_offset + row_top,5);
    }
    row++;
  } while( true );
  parley_build_unit_list((ListPaneWindow *)this2,pane,1);
  if (*(int *)((u8 *)&this2->advance_pane_rects + pane * 4 + 0x28) == 0) {
    has_sel = ((PictureWindow *)this2)->parley_pane_rows_base + pane * 4 + 0x28;
    has_sel[0] = 0xff;
    has_sel[1] = 0xff;
    has_sel[2] = 0xff;
    has_sel[3] = 0xff;
  }
  else if (*(int *)((u8 *)&this2->advance_pane_rects + pane * 4 + 0x28) <
           *(int *)((u8 *)&this2->advance_pane_rects + pane * 4 + 0x28)) {
    *(int *)(((PictureWindow *)this2)->parley_pane_rows_base + pane * 4 + 0x28) =
         *(int *)((u8 *)&this2->advance_pane_rects + pane * 4 + 0x28) - 1;
  }
  goto fill_list_bg;
}

/* 004692ea auto */
void __cdecl parley_reveal_city_origin_clicked(void)

{
  iptr child;
  iptr window;
  
  child = wnd_get_active_child();
  if (child == 0) {
    window = 0;
  }
  else {
    window = child - 0x48;
  }
  wnd_activate((Wnd *)(window + 0x48));
  ctrl_show_and_redraw(*(Control **)(window + 0x3a4));
  control_hide(*(Control **)(window + 0x39c));
  *(i8 *)(window + 0x3bd) = 1;
  ctrl_enable(*(Control **)(window + 0x38c));
  ctrl_enable(*(Control **)(window + 0x394));
  net_send_message(0xa7,*(i32 *)
                           (((i8 *)&net_session_block.net_player_slots) +
                           *(int *)(((i8 *)&net_session_block.net_civ_slots) + *(int *)(window + 0x118) * 4) * 0x54),
                     human_civ[0],(int)*(char *)(window + 0x3bd),0,0,0,0,0,0);
  parley_draw_unit_list(0);
  return;
}

/* 004693c5 auto */
void __cdecl parley_hide_city_origin_clicked(void)

{
  int child;
  WindowObjectView *window;
  
  child = wnd_get_active_child();
  if (child == 0) {
    window = (WindowObjectView *)0x0;
  }
  else {
    window = (WindowObjectView *)(child - 0x48);
  }
  wnd_activate((Wnd *)(window + 0x12));
  ctrl_show_and_redraw((Control *)window[0xe7].vtable);
  control_hide((Control *)window[0xe9].vtable);
  *(i8 *)((int)&window[0xef].vtable + 1) = 0;
  ctrl_disable((Control *)window[0xe3].vtable);
  ctrl_disable((Control *)window[0xe5].vtable);
  net_send_message(0xa8,*(i32 *)
                           (((i8 *)&net_session_block.net_player_slots) +
                           *(int *)(((i8 *)&net_session_block.net_civ_slots) + window[0x46].vtable * 4) * 0x54),human_civ[0]
                     ,(int)*(char *)((int)&window[0xef].vtable + 1),0,0,0,0,0,0);
  parley_sort_unit_list(window,0,window[0xfa].vtable - 1,0);
  parley_draw_unit_list(0);
  return;
}

/* 00469547 auto */
void __cdecl parley_sort_by_city_left_clicked(void)

{
  parley_sort_by_city_clicked(0);
  return;
}

/* 0046957b auto */
void __cdecl parley_sort_by_city_clicked(iptr pane)

{
  int child;
  void *window;
  
  child = wnd_get_active_child();
  if (child == 0) {
    window = (void *)0x0;
  }
  else {
    window = (void *)(child - 0x48);
  }
  wnd_activate((Wnd *)((int)window + 0x48));
  parley_sort_units_by_city(window,0,*(int *)((int)window + pane * 4 + 1000) - 1,pane);
  parley_draw_unit_list(pane);
  return;
}

/* 004695e9 auto */
void __cdecl parley_sort_by_unit_left_clicked(void)

{
  parley_sort_by_unit_clicked(0);
  return;
}

/* 0046961d auto */
void __cdecl parley_sort_by_unit_clicked(iptr pane)

{
  int child;
  WindowObjectView *window;
  
  child = wnd_get_active_child();
  if (child == 0) {
    window = (WindowObjectView *)0x0;
  }
  else {
    window = (WindowObjectView *)(child - 0x48);
  }
  wnd_activate((Wnd *)(window + 0x12));
  parley_sort_unit_list(window,0,window[pane + 0xfa].vtable - 1,pane);
  parley_draw_unit_list(pane);
  return;
}

/* 0046968b auto */
void __thiscall parley_sort_unit_list(WindowObjectView *self,int first,int last,iptr pane)

{
  i32 swap;
  iptr child;
  int cmp;
  int j;
  int i;
  iptr window;
  
  child = wnd_get_active_child();
  if (child == 0) {
    window = 0;
  }
  else {
    window = child - 0x48;
  }
  if (1 < *(int *)(window + 1000 + pane * 4)) {
    prefs_main_menu_choice_block.parley_units_by_city = 0;
    for (i = first; j = i, i < last; i++) {
      while (j = j + 1, j <= last) {
        cmp = _strcmp(*(char **)(((i8 *)&prefs_main_menu_choice_block.unit_type_name_ptrs) +
                                  (uint)units[*(int *)(i * 4 + pane * 0x2004 + 0x3f0 +
                                                      window)].type * 4),
                        *(char **)(((i8 *)&prefs_main_menu_choice_block.unit_type_name_ptrs) +
                                  (uint)units[*(int *)(j * 4 + pane * 0x2004 + 0x3f0 +
                                                      window)].type * 4));
        if (0 < cmp) {
          swap = *(i32 *)(i * 4 + pane * 0x2004 + 0x3f0 + window);
          *(i32 *)(i * 4 + pane * 0x2004 + 0x3f0 + window) =
               *(i32 *)(j * 4 + pane * 0x2004 + 0x3f0 + window);
          *(i32 *)(j * 4 + pane * 0x2004 + 0x3f0 + window) = swap;
          swap = *(i32 *)(i * 4 + pane * 0x2004 + 0x43f8 + window);
          *(i32 *)(i * 4 + pane * 0x2004 + 0x43f8 + window) =
               *(i32 *)(j * 4 + pane * 0x2004 + 0x43f8 + window);
          *(i32 *)(j * 4 + pane * 0x2004 + 0x43f8 + window) = swap;
          swap = *(i32 *)(i * 4 + pane * 0x2004 + 0x8400 + window);
          *(i32 *)(i * 4 + pane * 0x2004 + 0x8400 + window) =
               *(i32 *)(j * 4 + pane * 0x2004 + 0x8400 + window);
          *(i32 *)(j * 4 + pane * 0x2004 + 0x8400 + window) = swap;
        }
      }
    }
  }
  return;
}

/* 0046990a auto */
void __thiscall parley_sort_units_by_city(void *self,int first,int last,iptr pane)

{
  i32 swap;
  iptr child;
  char *_Str2;
  char *_Str1;
  int cmp;
  int j;
  int i;
  iptr window;
  
  child = wnd_get_active_child();
  if (child == 0) {
    window = 0;
  }
  else {
    window = child - 0x48;
  }
  if (*(int *)(window + 1000 + pane * 4) < 2) {
    return;
  }
  prefs_main_menu_choice_block.parley_units_by_city = 1;
  i = first;
outer_loop:
  j = i;
  if (last <= i) {
    return;
  }
inner_loop:
  do {
    j++;
    if (last < j) break;
    if (units[*(int *)(i * 4 + pane * 0x2004 + 0x3f0 + window)].home_city != -1) {
      if (units[*(int *)(j * 4 + pane * 0x2004 + 0x3f0 + window)].home_city != -1) {
        _Str2 = (char *)unit_home_city_name(*(iptr *)(j * 4 + pane * 0x2004 + 0x3f0 +
                                                    window));
        _Str1 = (char *)unit_home_city_name(*(iptr *)(i * 4 + pane * 0x2004 + 0x3f0 +
                                                    window));
        cmp = _strcmp(_Str1,_Str2);
        if (cmp < 1) goto inner_loop;
      }
      swap = *(i32 *)(i * 4 + pane * 0x2004 + 0x3f0 + window);
      *(i32 *)(i * 4 + pane * 0x2004 + 0x3f0 + window) =
           *(i32 *)(j * 4 + pane * 0x2004 + 0x3f0 + window);
      *(i32 *)(j * 4 + pane * 0x2004 + 0x3f0 + window) = swap;
      swap = *(i32 *)(i * 4 + pane * 0x2004 + 0x43f8 + window);
      *(i32 *)(i * 4 + pane * 0x2004 + 0x43f8 + window) =
           *(i32 *)(j * 4 + pane * 0x2004 + 0x43f8 + window);
      *(i32 *)(j * 4 + pane * 0x2004 + 0x43f8 + window) = swap;
      swap = *(i32 *)(i * 4 + pane * 0x2004 + 0x8400 + window);
      *(i32 *)(i * 4 + pane * 0x2004 + 0x8400 + window) =
           *(i32 *)(j * 4 + pane * 0x2004 + 0x8400 + window);
      *(i32 *)(j * 4 + pane * 0x2004 + 0x8400 + window) = swap;
    }
  } while( true );
  i++;
  goto outer_loop;
}

/* 00469bdc auto */
void __thiscall parley_build_unit_list(ListPaneWindow *self,int pane,int keep_selection)

{
  int *count_ptr;
  short x2;
  short y2;
  bool near_land;
  iptr child;
  iptr x;
  int y;
  int in_bounds;
  iptr unit;
  int old_count;
  int k;
  void *selected_ids;
  iptr dir;
  iptr window;
  
  selected_ids = (void *)0x0;
  child = wnd_get_active_child();
  if (child == 0) {
    window = 0;
  }
  else {
    window = child - 0x48;
  }
  if (keep_selection != 0) {
    selected_ids = operator_new(*(int *)(window + 1000 + pane * 4) << 2);
    if (selected_ids == (void *)0x0) {
      keep_selection = 0;
    }
    else {
      old_count = *(int *)(window + 1000 + pane * 4);
      for (unit = 0; unit < old_count; unit++) {
        if (*(int *)(pane * 0x2004 + unit * 4 + 0x8400 + window) == 0) {
          *(i32 *)((int)selected_ids + unit * 4) = 0xffffffff;
        }
        else {
          *(i32 *)((int)selected_ids + unit * 4) =
               *(i32 *)(pane * 0x2004 + unit * 4 + 0x43f8 + window);
        }
      }
    }
  }
  *(i32 *)(window + 1000 + pane * 4) = 0;
  unit = 0;
  do {
    if (game.num_units <= unit) {
      if ((keep_selection != 0) && (selected_ids != (void *)0x0)) {
        operator_delete(selected_ids);
      }
      if (prefs_main_menu_choice_block.parley_units_by_city == 0) {
        parley_sort_unit_list
                  ((WindowObjectView *)self,0,*(int *)(window + 1000 + pane * 4) - 1,pane);
      }
      else {
        parley_sort_units_by_city(self,0,*(int *)(window + 1000 + pane * 4) - 1,pane);
      }
      return;
    }
    if ((units[unit].id != 0) &&
       (((*(int *)(((i8 *)&prefs_main_menu_choice_block.parley_list_own_side) + pane * 4) != 0 && (units[unit].owner == (*(i8 *)&human_civ))) ||
        (((*(int *)(((i8 *)&prefs_main_menu_choice_block.parley_list_own_side) + pane * 4) == 0 &&
          ((int)units[unit].owner == self->caption_height)) &&
         (((1 << ((byte)(*(i8 *)&human_civ) & 0x1f) & (uint)units[unit].visibility) != 0 ||
          ((int)units[unit].owner == ((*(i8 *)&human_civ) & 0xffU))))))))) {
      x2 = units[unit].x;
      y2 = units[unit].y;
      near_land = false;
      for (dir = 0; dir < 8; dir++) {
        x = map_wrap_x((int)(char)(((i8 *)&dir_dx_table_block.dir_dx_table))[dir] + (int)x2);
        y = (int)(char)(((i8 *)&dir_dy_table_block.dir_dy_table))[dir] + (int)y2;
        in_bounds = map_in_bounds(x,y);
        if ((in_bounds != 0) && (y = tile_is_ocean(x,y), y == 0)) {
          near_land = true;
          break;
        }
      }
      if ((near_land) || (y = unit_stack_sum(unit,2), y == 1)) {
        *(iptr *)(pane * 0x2004 + *(int *)(window + 1000 + pane * 4) * 4 + 0x3f0 + window) =
             unit;
        *(i32 *)(pane * 0x2004 + *(int *)(window + 1000 + pane * 4) * 4 + 0x43f8 + window) =
             units[unit].id;
        *(i32 *)
         (pane * 0x2004 + *(int *)(window + 1000 + pane * 4) * 4 + 0x8400 + window) = 0;
        if ((keep_selection == 1) && (selected_ids != (void *)0x0)) {
          for (k = 0; k < old_count; k++) {
            if (units[unit].id == *(int *)((int)selected_ids + k * 4)) {
              *(i32 *)
               (pane * 0x2004 + *(int *)(window + 1000 + pane * 4) * 4 + 0x8400 + window) =
                   1;
              break;
            }
          }
        }
        count_ptr = (int *)(window + 1000 + pane * 4);
        *count_ptr = *count_ptr + 1;
      }
    }
    unit++;
  } while( true );
}

/* 0046af70 auto */
i8 __thiscall net_session_send_to(void *self,int player,iptr msg)

{
  i8 ok;
  int sent;
  
  if ((((player < 0) || (7 < player)) && (player != 0xff)) && (player != 0)) {
    err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_sock_0_sock_max_net_players_sock_broadca,(iptr)&str_d_ss_franklinton_netmgr_send_cpp,0x139);
  }
  if (*(int *)(msg + 8) == 0) {
    err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_pmsg_size_0,(iptr)&str_d_ss_franklinton_netmgr_send_cpp_2,0x13a);
  }
  *(int *)(msg + 0xc) = net_send_sequence;
  net_send_sequence++;
  sent = XD_SendSecureData((ushort)player,(void *)msg,*(ulong *)(msg + 8),0);
  *(int *)((int)self + 0x578) = sent;
  if (*(int *)((int)self + 0x578) < 0) {
    dbg_logf3((iptr)&str_sendtoconnections_failed_on_send_to_conn,player,*(i32 *)((int)self + 0x578),*(i32 *)(msg + 4));
    if (*(int *)(msg + 4) == 0x6a) {
      dbg_logf_str((iptr)&str_popup_type_s,(iptr)(((char *)&str_nm_pop_retiredie) + *(int *)(msg + 0x10) * 0x20))
      ;
    }
    ok = 0;
  }
  else {
    ok = 1;
  }
  return ok;
}

/* 0046b0a1 auto */
bool __thiscall net_session_send_to_all(void *self,iptr msg)

{
  bool failed;
  int sent;
  
  *(int *)(msg + 0xc) = net_send_sequence;
  net_send_sequence++;
  sent = XD_SendBroadcastData((void *)msg,*(ulong *)(msg + 8),0);
  *(int *)((int)self + 0x578) = sent;
  failed = *(int *)((int)self + 0x578) < *(int *)(msg + 8);
  if (failed) {
    dbg_logf((iptr)&str_sendtoeveryone_failed_return_val_d,*(iptr *)((int)self + 0x578));
  }
  return !failed;
}

/* 0046b14d auto */
/* WARNING: Removing unreachable block (ram,0x0046cdce) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl
net_send_message(int msg_type,i32 dest,iptr arg1,iptr arg2,iptr arg3,iptr arg4,
            iptr arg5,i32 arg6,iptr text,iptr raw_msg)

{
  char sent;
  size_t text_len;
  NetMsgHeader msg_5b[2];
  NetMsgHeader msg_2b[2];
  NetMsgHeader msg_9c[2];
  NetMsgHeader msg_58[2];
  NetMsgHeader msg_8d[2];
  NetMsgHeader msg_8b[2];
  NetMsgHeader msg_26[2];
  NetMsgHeader msg_46[2];
  NetMsgHeader msg_44[2];
  NetMsgHeader msg_42[2];
  NetMsgHeader msg_40[2];
  NetMsgHeader msg_8a[2];
  NetMsgHeader msg_83[2];
  NetMsgHeader msg_35[2];
  NetMsgHeader msg_79[2];
  NetMsgHeader msg_78[2];
  NetMsgHeader msg_74[2];
  NetMsgHeader whose_turn_msg[2];
  RECT caption_rect;
  NetMsgHeader msg_16[2];
  NetMsgHeader msg_5d[2];
  NetMsgHeader msg_14[2];
  NetMsgHeader answer_msg[38];
  NetMsgHeader msg_12[2];
  NetMsgHeader msg_6f[2];
  NetMsgHeader msg_6e[2];
  NetMsgHeader msg_6d[2];
  NetMsgHeader simple_msg[2];
  uint image_result;
  void *image_buf;
  NetMsgHeader player_node_msg[12];
  NetMsgHeader player_list_msg[2];
  i8 player_list_data[624];
  NetMsgHeader server_path_msg[2];
  i16 path_kind;
  i8 path_name[260];
  i8 path_subdir[262];
  NetMsgHeader msg_05[2];
  NetMsgHeader server_info_msg[50];
  i16 server_phase;
  NetMsgHeader announce_msg[15];
  void *packet;
  int result;
  
  packet = (void *)0x0;
  switch(msg_type) {
  case 1:
    net_msg_init_header(announce_msg,msg_type,(iptr)&str_empty_80);
    sent = net_session_send_to_all(((iptr *)&net_session_block.net_session),(iptr)announce_msg);
    return (int)sent;
  case 2:
    net_msg_server_info_init(server_info_msg);
    server_phase = (i16)net_session_block.net_session_phase;
    sent = net_session_send_to_all(((iptr *)&net_session_block.net_session),(iptr)server_info_msg);
    return (int)sent;
  default:
    return 0;
  case 4:
    net_msg_player_list_init(player_list_msg);
    crt_memcpy(player_list_data,((iptr *)&net_session_block.net_player_count),0x270);
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)player_list_msg);
    return (int)sent;
  case 5:
    net_msg_header_init(msg_05,msg_type);
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)msg_05);
    return (int)sent;
  case 6:
    net_msg_server_path_init(server_path_msg);
    path_kind = net_session_block.loaded_file_kind;
    crt_strcpy(path_name,((i8 *)&net_session_block.loaded_file_name));
    crt_strcpy(path_subdir,((i8 *)&net_session_block.loaded_file_subdir));
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)server_path_msg);
    return (int)sent;
  case 7:
  case 8:
  case 9:
  case 10:
    image_buf = (void *)0x0;
    if (msg_type == 7) {
      image_result = diffeng_build_full_image((iptr)&image_buf);
    }
    else if (msg_type == 8) {
      image_result = diffeng_build_delta_image((iptr)&image_buf);
    }
    else if (msg_type == 9) {
      image_result = diffeng_build_civ_image((iptr)&image_buf);
    }
    else if (msg_type == 10) {
      image_result = diffeng_build_map_header_image((iptr)&image_buf);
    }
    image_result = (uint)(image_result != -1);
    if (image_buf == (void *)0x0) {
      err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_address_null,(iptr)&str_d_ss_franklinton_netmgr_send_cpp_3,0x22c);
    }
    image_buf = (void *)net_msg_build_packet(msg_type,(iptr)image_buf,image_result,0,0,0,0,0,0);
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)image_buf);
    image_result = (uint)sent;
    operator_delete(image_buf);
    return image_result;
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
  case 0xf:
  case 0x10:
  case 0x11:
  case 0x32:
    net_msg_header_init(simple_msg,msg_type);
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)simple_msg);
    return (int)sent;
  case 0x12:
    net_msg_header_init(msg_12,msg_type);
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)msg_12);
    return (int)sent;
  case 0x13:
    net_msg_server_answer_init(answer_msg);
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)answer_msg);
    return (int)sent;
  case 0x14:
    net_msg_header_init(msg_14,msg_type);
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)msg_14);
    return (int)sent;
  case 0x15:
  case 0x5c:
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,raw_msg);
    if (sent == '\0') {
      return 0;
    }
    return *(i32 *)(raw_msg + 8);
  case 0x16:
    net_msg_header_init(msg_16,msg_type);
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)msg_16);
    return (int)sent;
  case 0x17:
    packet = (void *)net_msg_build_packet(msg_type,(iptr)&cosmic,0,0,0,0,0,0,0x29);
    break;
  case 0x18:
    packet = (void *)net_msg_build_packet(msg_type,(iptr)&advances,0,0,0,0,0,0,0x640);
    break;
  case 0x19:
    packet = (void *)net_msg_build_packet(msg_type,(iptr)&improvements,0,0,0,0,0,0,0x218);
    break;
  case 0x1a:
    packet = (void *)net_msg_build_packet(msg_type,(iptr)((u8 *)wonder_expires),0,0,0,0,0,0,0x1c);
    break;
  case 0x1b:
    packet = (void *)net_msg_build_packet(msg_type,(iptr)((u8 *)unit_types),0,0,0,0,0,0,0x4d8);
    break;
  case 0x1c:
    packet = (void *)net_msg_build_packet(msg_type,(iptr)&terrain_types,0,0,0,0,0,0,0x318);
    break;
  case 0x1d:
    packet = (void *)net_msg_build_packet(msg_type,(iptr)&government_names,0,0,0,0,0,0,0x1c);
    break;
  case 0x1e:
    packet = (void *)net_msg_build_packet(msg_type,(iptr)((u8 *)government_titles),0,0,0,0,0,0,0x38);
    break;
  case 0x1f:
    packet = (void *)net_msg_build_packet(msg_type,(iptr)((u8 *)leaders),0,0,0,0,0,0,0x3f0);
    break;
  case 0x20:
    packet = (void *)net_msg_build_packet(msg_type,(iptr)&civs,0,0,0,0,0,0,0x7524);
    break;
  case 0x21:
    packet = (void *)net_msg_build_packet(msg_type,(iptr)&commodity_names,0,0,0,0,0,0,0x40);
    break;
  case 0x22:
    packet = (void *)net_msg_build_packet(msg_type,(iptr)((u8 *)order_names),0,0,0,0,0,0,0x68);
    break;
  case 0x23:
    packet = (void *)net_msg_build_packet(msg_type,(iptr)((u8 *)difficulty_names),0,0,0,0,0,0,0x18);
    break;
  case 0x24:
    packet = (void *)net_msg_build_packet(msg_type,(iptr)&attitude_names,0,0,0,0,0,0,0x24);
    break;
  case 0x25:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,0,0,0,0,0);
    break;
  case 0x26:
  case 0x27:
    net_msg_header_init(msg_26,msg_type);
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)msg_26);
    return (int)sent;
  case 0x28:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,0,0,0,0,0,0);
    break;
  case 0x2a:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,0,0,0,0,0,0);
    net_session_block.nm_lock_data_count++;
    break;
  case 0x2b:
  case 0x2c:
    net_msg_header_init(msg_2b,msg_type);
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)msg_2b);
    return (int)sent;
  case 0x2d:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,0,0,0,0,0,0);
    break;
  case 0x2e:
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)&net_session_block.net_ping_message);
    return (int)sent;
  case 0x2f:
    net_msg_player_list_node_init(player_node_msg,arg1);
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)player_node_msg);
    return (int)sent;
  case 0x30:
    if (net_session_block.net_host_flag == '\0') {
      packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,0,0,0,0,0);
      break;
    }
    if ((1 << ((byte)arg2 & 0x1f) & (int)(short)(*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask)) == 0) {
      (*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask) = (*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask) | (ushort)(1 << ((byte)arg2 & 0x1f));
      net_send_message(0x2a,0xff,(int)(short)(*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask),0,0,0,0,0,0,0);
      net_session_block.nm_nation_accept_count++;
      return 1;
    }
    net_session_block.nm_nation_reject_count++;
  case 0x31:
    if (net_session_block.net_host_flag != '\0') {
      game.human_players = game.human_players & (byte)(*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask);
      if ((1 << ((byte)arg2 & 0x1f) & (int)(short)(*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask)) != 0) {
        (*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask) = (*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask) & ~(ushort)(1 << ((byte)arg2 & 0x1f));
        game.human_players = game.human_players & (byte)(*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask);
        net_send_message(0x2a,0xff,(int)(short)(*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask),0,0,0,0,0,0,0);
        net_session_block.nm_lock_data_count++;
      }
      return 1;
    }
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,0,0,0,0,0);
    break;
  case 0x33:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,arg3,0,0,0,0);
    break;
  case 0x34:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,0,0,0,0,0,0);
    break;
  case 0x35:
  case 0x81:
    net_msg_header_init(msg_35,msg_type);
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)msg_35);
    return (int)sent;
  case 0x37:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,0,0,0,0,0,0);
    break;
  case 0x38:
    packet = (void *)net_msg_build_packet(msg_type,(iptr)(units + arg1),arg1,(int)game.num_units
                                         ,arg3,arg4,arg5,arg6,0x20);
    break;
  case 0x39:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,0,0,0,0,0,0);
    break;
  case 0x3a:
    packet = (void *)net_msg_build_packet(msg_type,(iptr)(cities + arg1),arg1,
                                         (int)game.num_cities,arg3,arg4,arg5,arg6,0x58);
    break;
  case 0x3b:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,arg3,0,0,0,0);
    break;
  case 0x3c:
    if (arg1 == -1) {
      packet = (void *)net_msg_build_packet(msg_type,0,0xffffffff,0,0,0,0,0,0);
    }
    else {
      packet = (void *)net_msg_build_packet(msg_type,(iptr)(cities + arg1),arg1,
                                           (int)game.num_cities,arg3,arg4,arg5,arg6,0x58
                                          );
    }
    break;
  case 0x3d:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,arg3,arg4,0,0,0);
    break;
  case 0x3e:
    if (arg1 == -1) {
      packet = (void *)net_msg_build_packet(msg_type,0,0xffffffff,0,0,0,0,0,0);
    }
    else {
      packet = (void *)net_msg_build_packet(msg_type,(iptr)(units + arg1),arg1,
                                           (int)game.num_units,arg3,arg4,arg5,arg6,0x20)
      ;
    }
    break;
  case 0x3f:
  case 0x4b:
  case 0x4d:
  case 0x4f:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,0,0,0,0,0,0);
    break;
  case 0x40:
  case 0x4c:
  case 0x4e:
  case 0x50:
    net_msg_header_init(msg_40,msg_type);
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)msg_40);
    return (int)sent;
  case 0x41:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,arg3,0,0,0,0);
    break;
  case 0x42:
    net_msg_header_init(msg_42,msg_type);
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)msg_42);
    return (int)sent;
  case 0x43:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,0,0,0,0,0,0);
    break;
  case 0x44:
    net_msg_header_init(msg_44,msg_type);
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)msg_44);
    return (int)sent;
  case 0x45:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,arg3,0,0,0,0);
    break;
  case 0x46:
    net_msg_header_init(msg_46,msg_type);
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)msg_46);
    return (int)sent;
  case 0x47:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,arg3,arg4,arg5,0,0);
    break;
  case 0x48:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,0,0,0,0,0,0);
    break;
  case 0x49:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,0,0,0,0,0);
    break;
  case 0x4a:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,0,0,0,0,0,0);
    break;
  case 0x51:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,arg3,arg4,arg5,0,0);
    break;
  case 0x52:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,0,0,0,0,0,0);
    break;
  case 0x53:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,0,0,0,0,0);
    break;
  case 0x54:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,0,0,0,0,0,0);
    break;
  case 0x55:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,arg3,arg4,arg5,0,0);
    break;
  case 0x56:
  case 0x57:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,0,0,0,0,0,0);
    break;
  case 0x58:
    net_msg_header_init(msg_58,msg_type);
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)msg_58);
    return (int)sent;
  case 0x59:
    packet = (void *)net_msg_build_packet(msg_type,(iptr)&net_batch_buffer,0,0,0,0,0,0,net_batch_used_dwords << 2);
    break;
  case 0x5a:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,arg3,arg4,arg5,arg6,0
                                        );
    break;
  case 0x5b:
  case 0x65:
  case 0x66:
  case 0xa3:
    net_msg_header_init(msg_5b,msg_type);
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)msg_5b);
    return (int)sent;
  case 0x5d:
  case 0x5e:
    net_msg_header_init(msg_5d,msg_type);
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)msg_5d);
    return (int)sent;
  case 0x5f:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,0,0,0,0,0,0);
    break;
  case 0x60:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,0,0,0,0,0);
    break;
  case 0x61:
  case 0x62:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,0,0,0,0,0,0);
    break;
  case 99:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,arg3,0,0,0,0);
    break;
  case 100:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,arg3,arg4,arg5,0,0);
    break;
  case 0x68:
    text_len = _strlen((char *)text);
    packet = (void *)net_msg_build_packet(msg_type,text,arg1,arg2,arg3,0,0,0,text_len + 1);
    break;
  case 0x69:
    net_msg_whose_turn_init(whose_turn_msg,arg1);
    map_views_block.main_view_timer_cache_i32 = 0xffffffff;
    frame_wnd_draw_caption((FrameWindow *)((i8 *)&map_views_block.map_views));
    caption_rect.left = map_views_block.main_view_frame_left;
    caption_rect.top = map_views_block.main_view_frame_top;
    caption_rect.right = map_views_block.main_view_frame_right;
    caption_rect.bottom = map_views_block.main_view_client_top;
    wnd_blit_surface_rect((DibSurface *)((i8 *)&map_views_block.map_views),(iptr)&caption_rect);
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)whose_turn_msg);
    return (int)sent;
  case 0x6a:
    packet = (void *)net_msg_build_packet(msg_type,raw_msg,arg1,arg2,arg3,arg4,arg5,0,
                                         0);
    break;
  case 0x6b:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,arg3,0,0,0,0);
    break;
  case 0x6c:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,0,0,0,0,0,0);
    break;
  case 0x6d:
    net_msg_header_init(msg_6d,msg_type);
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)msg_6d);
    return (int)sent;
  case 0x6e:
    net_msg_header_init(msg_6e,msg_type);
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)msg_6e);
    return (int)sent;
  case 0x6f:
    net_msg_header_init(msg_6f,msg_type);
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)msg_6f);
    return (int)sent;
  case 0x70:
    packet = (void *)net_msg_build_packet(msg_type,(iptr)(units + arg1),arg1,arg2,arg3,
                                         arg4,arg5,arg6,0x20);
    break;
  case 0x71:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,arg3,0,0,0,0);
    break;
  case 0x72:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,0,0,0,0,0);
    break;
  case 0x73:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,arg3,arg4,0,0,0);
    break;
  case 0x74:
    net_msg_header_init(msg_74,msg_type);
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)msg_74);
    return (int)sent;
  case 0x75:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,0,0,0,0,0);
    break;
  case 0x76:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,arg3,arg4,0,0,0);
    break;
  case 0x77:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,0,0,0,0,0,0);
    break;
  case 0x78:
    net_msg_header_init(msg_78,msg_type);
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)msg_78);
    return (int)sent;
  case 0x79:
    net_msg_header_init(msg_79,msg_type);
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)msg_79);
    return (int)sent;
  case 0x7a:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,0,0,0,0,0);
    break;
  case 0x7b:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,0,0,0,0,0,0);
    break;
  case 0x7c:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,arg3,0,0,0,0);
    break;
  case 0x7d:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,0,0,0,0,0);
    break;
  case 0x7e:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,0,0,0,0,0);
    break;
  case 0x7f:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,0,0,0,0,0,0);
    break;
  case 0x80:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,0,0,0,0,0,0);
    break;
  case 0x82:
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,raw_msg);
    if (sent == '\0') {
      return 0;
    }
    return *(i32 *)(raw_msg + 8);
  case 0x83:
  case 0x84:
  case 0x85:
    net_msg_header_init(msg_83,msg_type);
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)msg_83);
    return (int)sent;
  case 0x86:
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,raw_msg);
    if (sent == '\0') {
      return 0;
    }
    return *(i32 *)(raw_msg + 8);
  case 0x87:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,arg3,0,0,0,0);
    break;
  case 0x88:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,0,0,0,0,0,0);
    break;
  case 0x89:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,0,0,0,0,0,0);
    break;
  case 0x8a:
    net_msg_header_init(msg_8a,msg_type);
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)msg_8a);
    return (int)sent;
  case 0x8b:
    net_msg_header_init(msg_8b,msg_type);
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)msg_8b);
    return (int)sent;
  case 0x8c:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,0,0,0,0,0,0);
    break;
  case 0x8d:
  case 0x8e:
    net_msg_header_init(msg_8d,msg_type);
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)msg_8d);
    return (int)sent;
  case 0x8f:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,0,0,0,0,0,0);
    break;
  case 0x90:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,arg3,arg4,arg5,0,0);
    break;
  case 0x91:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,arg3,arg4,0,0,0);
    break;
  case 0x92:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,arg3,arg4,arg5,0,0);
    break;
  case 0x93:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,arg3,arg4,0,0,0);
    break;
  case 0x94:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,arg3,arg4,0,0,0);
    break;
  case 0x95:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,arg3,arg4,0,0,0);
    break;
  case 0x96:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,arg3,arg4,0,0,0);
    break;
  case 0x97:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,arg3,arg4,arg5,arg6,0
                                        );
    break;
  case 0x98:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,arg3,0,0,0,0);
    break;
  case 0x99:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,arg3,arg4,0,0,0);
    break;
  case 0x9a:
  case 0xa0:
  case 0xa1:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,0,0,0,0,0);
    break;
  case 0x9b:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,arg3,arg4,0,0,0);
    break;
  case 0x9c:
  case 0x9d:
  case 0x9e:
    net_msg_header_init(msg_9c,msg_type);
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)msg_9c);
    return (int)sent;
  case 0x9f:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,0,0,0,0,0,0);
    break;
  case 0xa2:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,0,0,0,0,0,0);
    break;
  case 0xa4:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,0,0,0,0,0);
    break;
  case 0xa5:
  case 0xa6:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,0,0,0,0,0);
    break;
  case 0xa7:
  case 0xa8:
    packet = (void *)net_msg_build_packet(msg_type,0,arg1,arg2,0,0,0,0,0);
  }
  if (packet == (void *)0x0) {
    err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_address,(iptr)&str_d_ss_franklinton_netmgr_send_cpp_4,0x523);
    result = 0;
  }
  else {
    sent = net_session_send_to(((iptr *)&net_session_block.net_session),dest,(iptr)packet);
    result = (int)sent;
    operator_delete(packet);
  }
  return result;
}

/* 0046d5a0 auto */
NetMsgHeader * __thiscall net_msg_header_init(NetMsgHeader *self,u32 type)

{
  ((NetMsgHeaderExt *)self)->msg_size_2 = 0x10;
  self->msg_magic = 0x66606660;
  self->msg_type = type;
  return self;
}

/* 0046d5f0 auto */
NetMsgHeader * __thiscall net_msg_init_header(NetMsgHeader *self,u32 msg_type,iptr name2)

{
  net_msg_addr_header_init(self,0);
  ((NetMsgHeaderExt *)self)->inner_msg_type = msg_type;
  _memset(self + 6,0,0x20);
  _strncpy((char *)(self + 6),(char *)name2,0x20);
  _memset(self + 10,0,0x20);
  _strncpy((char *)(self + 10),((i8 *)&prefs_main_menu_choice_block.prefs_net_ip_address),0x20);
  ((NetMsgHeaderExt *)self)->msg_size_2 = 0x74;
  return self;
}

/* 0046d6a0 auto */
NetMsgHeader * __thiscall net_msg_addr_header_init(NetMsgHeader *self,i32 msg_type)

{
  net_msg_header_init(self,msg_type);
  _memset(self + 2,0,0x20);
  _strncpy((char *)(self + 2),((i8 *)&prefs_main_menu_choice_block.prefs_net_ip_address),0x20);
  ((NetMsgHeaderExt *)self)->msg_size_2 = 0x30;
  return self;
}

/* 0046d720 auto */
NetMsgHeader * __thiscall net_msg_server_info_init(NetMsgHeader *self)

{
  net_msg_init_header(self,2,(iptr)&str_empty_81);
  net_fill_game_info((iptr)&((NetMsgHeaderExt *)self)->game_info);
  ((NetMsgHeaderExt *)self)->msg_size_2 = 0x198;
  return self;
}

/* 0046d780 auto */
NetMsgHeader * __thiscall net_msg_player_list_node_init(NetMsgHeader *self,u32 player_id)

{
  net_msg_header_init(self,0x2f);
  ((NetMsgHeaderExt *)self)->player_id = player_id;
  _memset(&((NetMsgHeaderExt *)self)->ip_address,0,0x20);
  _strncpy((char *)&((NetMsgHeaderExt *)self)->ip_address,((i8 *)&prefs_main_menu_choice_block.prefs_net_ip_address),0x20);
  crt_strcpy(&((NetMsgHeaderExt *)self)->player_name,((i8 *)&prefs_main_menu_choice_block.prefs_net_player_name));
  ((NetMsgHeaderExt *)self)->node_status_54 = 0;
  ((NetMsgHeaderExt *)self)->node_status_58 = 0;
  *(i8 *)&((NetMsgHeaderExt *)self)->node_flag_bytes = 0;
  *(i8 *)((int)&((NetMsgHeaderExt *)self)->node_flag_bytes + 1) = 0;
  ((NetMsgHeaderExt *)self)->node_slot_index = 0xffffffff;
  ((NetMsgHeaderExt *)self)->msg_size_2 = 100;
  return self;
}

/* 0046d860 auto */
NetMsgHeader * __thiscall net_msg_player_list_init(NetMsgHeader *self)

{
  net_msg_header_init(self,4);
  ((NetMsgHeaderExt *)self)->msg_size_2 = 0x280;
  return self;
}

/* 0046d8a0 auto */
NetMsgHeader * __thiscall net_msg_server_path_init(NetMsgHeader *self)

{
  net_msg_header_init(self,6);
  ((NetMsgHeaderExt *)self)->msg_size_2 = 0x21c;
  return self;
}

/* 0046d8e0 auto */
NetMsgHeader * __thiscall net_msg_server_answer_init(NetMsgHeader *self)

{
  net_msg_header_init(self,0x13);
  net_fill_game_info((iptr)(self + 2));
  ((NetMsgHeaderExt *)self)->msg_size_2 = 0x134;
  return self;
}

/* 0046d930 auto */
NetMsgHeader * __thiscall net_msg_whose_turn_init(NetMsgHeader *self,u32 turn_civ)

{
  net_msg_header_init(self,0x69);
  ((NetMsgHeaderExt *)self)->player_id = turn_civ;
  ((NetMsgHeaderExt *)self)->msg_size_2 = 0x14;
  return self;
}

/* 0047e0e5 auto */
int __cdecl net_stacked_draw_push(int kind,iptr args,iptr unit_data)

{
  int result;
  i8 dummy_args[28];
  int i;
  
  if ((net_session_block.net_stacked_draw_last == net_session_block.net_stacked_draw_first) && (net_session_block.net_stacked_draw_count != 0)) {
    dbg_log((iptr)&str_stacked_draw_stack_full_flushing);
    if (net_session_block.unit_stack_check_enabled != 0) {
      net_session_block.net_stacked_draw_last = (net_session_block.net_stacked_draw_first + 1) % 100;
    }
    else {
      net_session_block.net_stacked_draw_first = 0;
      net_session_block.net_stacked_draw_last = 0;
    }
    net_session_block.net_stacked_draw_count = (uint)(net_session_block.unit_stack_check_enabled != 0);
    net_stacked_draw_push(0xa3,(iptr)dummy_args,0);
    result = net_stacked_draw_push(0x74,(iptr)dummy_args,0);
  }
  else {
    if ((net_session_block.net_stacked_draw_first < 0) || (99 < net_session_block.net_stacked_draw_first)) {
      err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_gnetmgr_firststackeddraw_0_gnetmgr_first,(iptr)&str_d_ss_franklinton_netmgr_poll_cpp,0x5a);
    }
    if ((net_session_block.net_stacked_draw_last < 0) || (99 < net_session_block.net_stacked_draw_last)) {
      err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_gnetmgr_laststackeddraw_0_gnetmgr_lastst,(iptr)&str_d_ss_franklinton_netmgr_poll_cpp_2,0x5b);
    }
    *(int *)(((i8 *)&net_session_block.net_stacked_draw_kinds) + net_session_block.net_stacked_draw_last * 0x40) = kind;
    for (i = 0; i < 7; i++) {
      *(i32 *)(((i8 *)&net_session_block.net_stacked_draw_args) + i * 4 + net_session_block.net_stacked_draw_last * 0x40) =
           *(i32 *)(args + i * 4);
    }
    if (kind == 0x70) {
      crt_memcpy(net_session_block.net_stacked_draw_last * 0x40 + (iptr)(((u8 *)&net_session_block.net_stacked_draw_arg4 + 12)),unit_data,0x20);
    }
    net_session_block.net_stacked_draw_count++;
    if ((int)net_session_block.net_stacked_draw_peak < (int)net_session_block.net_stacked_draw_count) {
      net_session_block.net_stacked_draw_peak = net_session_block.net_stacked_draw_count;
    }
    result = (net_session_block.net_stacked_draw_last + 1) / 100;
    net_session_block.net_stacked_draw_last = (net_session_block.net_stacked_draw_last + 1) % 100;
  }
  return result;
}

/* 0047e2b3 auto */
int __cdecl net_stacked_draw_run_next(void)

{
  int y;
  iptr visible;
  iptr tile;
  iptr unit;
  iptr unit2;
  int count;
  int x;
  i32 sum_mode;
  int stack_count;
  
  switch(*(i32 *)(((i8 *)&net_session_block.net_stacked_draw_kinds) + net_session_block.net_stacked_draw_first * 0x40)) {
  case 0x70:
    x = *(int *)(((i8 *)&net_session_block.net_stacked_draw_arg1) + net_session_block.net_stacked_draw_first * 0x40);
    y = *(int *)(((i8 *)&net_session_block.net_stacked_draw_arg2) + net_session_block.net_stacked_draw_first * 0x40);
    unit2 = *(iptr *)(((i8 *)&net_session_block.net_stacked_draw_arg3) + net_session_block.net_stacked_draw_first * 0x40);
    unit_stack_validate(*(iptr *)(((i8 *)&net_session_block.net_stacked_draw_args) + net_session_block.net_stacked_draw_first * 0x40));
    visible = mapviews_tile_visible(x,y);
    if (visible != 0) {
      crt_memcpy(((short *)&power_graph_history_block.stacked_draw_unit_copy),net_session_block.net_stacked_draw_first * 0x40 + (iptr)(((u8 *)&net_session_block.net_stacked_draw_arg4 + 12)),0x20);
      power_graph_history_block.stacked_draw_unit_prev = -1;
      power_graph_history_block.stacked_draw_unit_next = -1;
      mapviews_ensure_visible(x,y,(int)power_graph_history_block.stacked_draw_unit_owner);
      if (*(int *)(((i8 *)&net_session_block.net_stacked_draw_arg4) + net_session_block.net_stacked_draw_first * 0x40) == -1) {
        snd_play_effect(99,1,0,0);
      }
      tile = tile_at(x,y);
      sum_mode = 2;
      unit = tile_first_unit(x,y);
      stack_count = unit_stack_sum(unit,sum_mode);
      if ((power_graph_history_block.stacked_draw_unit_copy[0] != x) || (power_graph_history_block.stacked_draw_unit_y != y)) {
        stack_count++;
      }
      if (stack_count == 1) {
        *(byte *)(tile + 1) = *(byte *)(tile + 1) & 0xfe;
      }
      else if (1 < stack_count) {
        anim_origin_x = (int)power_graph_history_block.stacked_draw_unit_copy[0];
        anim_origin_y = (int)power_graph_history_block.stacked_draw_unit_y;
        count = unit_stack_sum(0x801,5);
        if (count == 0) {
          if (power_graph_history_block.stacked_draw_unit_next < 0) {
            if (power_graph_history_block.stacked_draw_unit_prev < 0) {
              *(byte *)(tile + 1) = *(byte *)(tile + 1) & 0xfe;
            }
            else {
              anim_origin_stack_unit = (iptr)power_graph_history_block.stacked_draw_unit_prev;
            }
          }
          else {
            anim_origin_stack_unit = (iptr)power_graph_history_block.stacked_draw_unit_next;
          }
        }
        else {
          count = unit_stack_sum(0x801,5);
          if (count < 2) {
            *(byte *)(tile + 1) = *(byte *)(tile + 1) & 0xfe;
          }
          else {
            anim_origin_stack_unit = unit_stack_first(0x801);
            do {
              if ((anim_origin_stack_unit != 0x801) &&
                 (unit_types[units[anim_origin_stack_unit].type].domain == 2)) goto animate_move;
              anim_origin_stack_unit = (iptr)units[anim_origin_stack_unit].next_in_stack;
            } while (-1 < anim_origin_stack_unit);
            *(byte *)(tile + 1) = *(byte *)(tile + 1) & 0xfe;
          }
        }
      }
animate_move:
      unit_move_anim_active = 1;
      map_animate_unit_move(0x801,x,y,unit2,net_session_block.net_move_anim_sound,net_session_block.net_move_anim_sound_arg);
      unit_move_anim_active = 0;
      sum_mode = 2;
      unit2 = tile_first_unit(x,y);
      count = unit_stack_sum(unit2,sum_mode);
      if (count != 0) {
        if (net_session_block.net_host_flag == '\0') {
          *(byte *)(tile + 1) = *(byte *)(tile + 1) | 1;
        }
        else {
          tile_set_improvements(x,y,1,1,1);
        }
      }
    }
    break;
  case 0x71:
    x = tile_visible_to(*(i32 *)(((i8 *)&net_session_block.net_stacked_draw_args) + net_session_block.net_stacked_draw_first * 0x40),
                            *(i32 *)(((i8 *)&net_session_block.net_stacked_draw_arg1) + net_session_block.net_stacked_draw_first * 0x40),human_civ[0]);
    if (x != 0) {
      mapviews_ensure_visible(*(i32 *)(((i8 *)&net_session_block.net_stacked_draw_args) + net_session_block.net_stacked_draw_first * 0x40),
                         *(i32 *)(((i8 *)&net_session_block.net_stacked_draw_arg1) + net_session_block.net_stacked_draw_first * 0x40),
                         *(iptr *)(((i8 *)&net_session_block.net_stacked_draw_arg2) + net_session_block.net_stacked_draw_first * 0x40));
    }
    break;
  case 0x72:
    map_redraw_tile_all_views(*(i32 *)(((i8 *)&net_session_block.net_stacked_draw_args) + net_session_block.net_stacked_draw_first * 0x40),
                       *(i32 *)(((i8 *)&net_session_block.net_stacked_draw_arg1) + net_session_block.net_stacked_draw_first * 0x40));
    break;
  case 0x73:
    map_redraw_combat_tiles(*(i32 *)(((i8 *)&net_session_block.net_stacked_draw_args) + net_session_block.net_stacked_draw_first * 0x40),
                       *(i32 *)(((i8 *)&net_session_block.net_stacked_draw_arg1) + net_session_block.net_stacked_draw_first * 0x40),
                       *(i32 *)(((i8 *)&net_session_block.net_stacked_draw_arg2) + net_session_block.net_stacked_draw_first * 0x40),
                       *(i32 *)(((i8 *)&net_session_block.net_stacked_draw_arg3) + net_session_block.net_stacked_draw_first * 0x40));
    break;
  case 0x74:
    map_redraw_all_views(human_civ[0],1);
    break;
  case 0x75:
    map_redraw_neighbors_all_views(*(i32 *)(((i8 *)&net_session_block.net_stacked_draw_args) + net_session_block.net_stacked_draw_first * 0x40),
                       *(iptr *)(((i8 *)&net_session_block.net_stacked_draw_arg1) + net_session_block.net_stacked_draw_first * 0x40));
    break;
  case 0x76:
    map_redraw_area_all_views(*(i32 *)(((i8 *)&net_session_block.net_stacked_draw_args) + net_session_block.net_stacked_draw_first * 0x40),
                       *(i32 *)(((i8 *)&net_session_block.net_stacked_draw_arg1) + net_session_block.net_stacked_draw_first * 0x40),
                       *(i32 *)(((i8 *)&net_session_block.net_stacked_draw_arg2) + net_session_block.net_stacked_draw_first * 0x40),
                       *(iptr *)(((i8 *)&net_session_block.net_stacked_draw_arg3) + net_session_block.net_stacked_draw_first * 0x40),1);
    break;
  case 0x7c:
    x = mapviews_tile_visible(*(iptr *)(((i8 *)&net_session_block.net_stacked_draw_args) + net_session_block.net_stacked_draw_first * 0x40),
                               *(iptr *)(((i8 *)&net_session_block.net_stacked_draw_arg1) + net_session_block.net_stacked_draw_first * 0x40));
    if (x != 0) {
      map_animate_explosion(*(i32 *)(((i8 *)&net_session_block.net_stacked_draw_args) + net_session_block.net_stacked_draw_first * 0x40),
                         *(i32 *)(((i8 *)&net_session_block.net_stacked_draw_arg1) + net_session_block.net_stacked_draw_first * 0x40),
                         *(i32 *)(((i8 *)&net_session_block.net_stacked_draw_arg2) + net_session_block.net_stacked_draw_first * 0x40));
    }
    break;
  case 0x7d:
    x = mapviews_tile_visible(*(iptr *)(((i8 *)&net_session_block.net_stacked_draw_args) + net_session_block.net_stacked_draw_first * 0x40),
                               *(iptr *)(((i8 *)&net_session_block.net_stacked_draw_arg1) + net_session_block.net_stacked_draw_first * 0x40));
    if (x != 0) {
      map_animate_nuke(*(i32 *)(((i8 *)&net_session_block.net_stacked_draw_args) + net_session_block.net_stacked_draw_first * 0x40),
                         *(i32 *)(((i8 *)&net_session_block.net_stacked_draw_arg1) + net_session_block.net_stacked_draw_first * 0x40));
    }
    break;
  case 0xa3:
    net_session_block.nm_abort_kaboom_count++;
  }
  (*(int *)&net_session_block.net_stacked_draw_count)--;
  x = net_session_block.net_stacked_draw_first + 1;
  net_session_block.net_stacked_draw_first = x % 100;
  return x / 100;
}

/* 0047e94e auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall net_process_messages(NetSession *self,int max_msgs,int wait_mode)

{
  int *drop_counter;
  u8 *civ_flag;
  char *type_count;
  char civ;
  iptr flush_pending;
  iptr flush_pending2;
  u32 now;
  i32 x;
  iptr ret_val;
  int city;
  bool had_pending;
  uptr civ2;
  uptr unit5;
  int *popup_data;
  int dequeue_wait;
  iptr dblclick_wnd;
  iptr click_wnd;
  i8 home_city_id;
  i8 new_owner;
  i8 draw_args[28];
  RECT caption_rect;
  uint section_id2;
  u8 saved_multiplayer;
  iptr unit2;
  uint *rle_src;
  int rle_src_end;
  int rle_dst;
  int rle_dst_end;
  i16 saved_moving_unit;
  i8 saved_player_civ;
  int decoded_size;
  int section_idx;
  int units_saved;
  int turn_civ_changed;
  uint section_offset;
  int city_changed;
  u16 saved_msg_options;
  i8 saved_field_1c;
  i8 saved_turn_civ_val;
  uptr section_size;
  i16 saved_active_unit;
  u32 saved_game_options;
  int slot;
  Dialog join_dialog;
  int wait_start;
  Dialog wait_dialog;
  u32 saved_busy;
  int *hello_msg;
  int y4;
  int x3;
  RECT timer_rect;
  int input_kind;
  u32 deferred_input;
  uint input_char;
  uint msg_size;
  int sender;
  iptr unit4;
  int image_kind;
  i32 header_size;
  uint *payload;
  i8 unused_flag;
  uptr unit;
  uptr civ3;
  uptr unit3;
  iptr y2;
  iptr x2;
  int y3;
  int extra_len;
  int *msg_hdr;
  int *msg;
  char gamelist_dirty;
  int image_size;
  iptr result;
  i32 seh_prev;
  i8 *seh_handler;
  i32 unwind_state;
  
  unwind_state = 0xffffffff;
  gamelist_dirty = '\0';
  unused_flag = 0;
  if ((((((((((NetSessionExt *)self)->pending_count_7b4 == 0) && (*(int *)((NetSessionExt *)self)->pending_count_7b8 == 0)) &&
          (((NetSessionExt *)self)->pending_count_7bc == 0)) &&
         ((*(int *)((NetSessionExt *)self)->pending_count_7c0 == 0 && (((NetSessionExt *)self)->pending_count_7c4 == 0)))) &&
        (*(int *)((NetSessionExt *)self)->pending_count_7c8 == 0)) &&
       (((*(int *)((NetSessionExt *)self)->pending_count_7d0 == 0 && (((NetSessionExt *)self)->pending_count_7d4 == 0)) &&
        ((*(int *)((NetSessionExt *)self)->pending_count_7d8 == 0 &&
         (((((NetSessionExt *)self)->pending_count_7dc == 0 && (*(int *)((NetSessionExt *)self)->pending_count_7e0 == 0)) && (((NetSessionExt *)self)->pending_count_7e4 == 0)
          ))))))) && ((*(int *)((NetSessionExt *)self)->pending_count_7e8 == 0 && (((NetSessionExt *)self)->pending_count_7ec == 0)))) &&
     ((*(int *)((NetSessionExt *)self)->gather_cargo_busy == 0 &&
      (((((NetSessionExt *)self)->lift_off_map_busy == 0 && (*(int *)((NetSessionExt *)self)->delete_cargo_busy == 0)) &&
       ((((NetSessionExt *)self)->destroy_redraw_busy == 0 && (flush_pending = XD_InFlushSendBuffer(), flush_pending == 0)))))))) {
    if (((((NetSessionExt *)self)->deferred_input_kind != 0) && (net_deferred_input_busy == '\0')) &&
       (flush_pending2 = XD_InFlushSendBuffer(), flush_pending2 == 0)) {
      deferred_input = ((NetSessionExt *)self)->deferred_input_kind;
      net_deferred_input_busy = 1;
      dbg_log((iptr)&str_poll_unstacking_xd_flushsendbuffer_block);
      ((NetSessionExt *)self)->deferred_input_kind = 0;
      switch(deferred_input) {
      case 1:
        if (*(short *)(((NetSessionExt *)self)->deferred_input_window + 0x2dc) != 0) {
          if (((NetSessionExt *)self)->deferred_input_window == 0) {
            click_wnd = 0;
          }
          else {
            click_wnd = ((NetSessionExt *)self)->deferred_input_window + 0x48;
          }
          wnd_set_active_child(click_wnd);
          map_window_click(*(i32 *)((NetSessionExt *)self)->deferred_input_arg1,((NetSessionExt *)self)->deferred_input_arg2,
                             *(i32 *)((NetSessionExt *)self)->deferred_input_arg3);
        }
        break;
      case 2:
        if (*(short *)(((NetSessionExt *)self)->deferred_input_window + 0x2dc) != 0) {
          if (((NetSessionExt *)self)->deferred_input_window == 0) {
            dblclick_wnd = 0;
          }
          else {
            dblclick_wnd = ((NetSessionExt *)self)->deferred_input_window + 0x48;
          }
          wnd_set_active_child(dblclick_wnd);
          map_window_double_click(*(i32 *)((NetSessionExt *)self)->deferred_input_arg1,((NetSessionExt *)self)->deferred_input_arg2);
        }
        break;
      case 4:
        input_kind = net_session_block.blocked_input_char_pending;
        input_char = (input_char & 0xffffff00 | (byte)(net_session_block.blocked_input_char));
        map_window_key(*(i32 *)((NetSessionExt *)self)->deferred_input_arg1);
        if (input_kind == 3) {
          map_window_ascii(input_char);
        }
        break;
      case 5:
        menu_command(*(i32 *)((NetSessionExt *)self)->deferred_input_arg1,((NetSessionExt *)self)->deferred_input_arg2);
        break;
      case 6:
        if (((city_window_block.city_window_closed == 0) && (cities[*(int *)((NetSessionExt *)self)->deferred_input_arg1].id != 0)) &&
           ((int)cities[*(int *)((NetSessionExt *)self)->deferred_input_arg1].owner == ((NetSessionExt *)self)->deferred_input_arg2)) {
          city_window_on_mouse(*(i32 *)((NetSessionExt *)self)->deferred_input_arg3,((NetSessionExt *)self)->deferred_input_arg4,
                             *(i32 *)((NetSessionExt *)self)->deferred_input_arg5);
        }
        break;
      case 7:
        if (((city_window_block.city_window_closed == 0) && (cities[*(int *)((NetSessionExt *)self)->deferred_input_arg1].id != 0)) &&
           ((int)cities[*(int *)((NetSessionExt *)self)->deferred_input_arg1].owner == ((NetSessionExt *)self)->deferred_input_arg2)) {
          city_button_buy(*(i32 *)((NetSessionExt *)self)->deferred_input_arg3);
        }
        break;
      case 8:
        if (((city_window_block.city_window_closed == 0) && (cities[*(int *)((NetSessionExt *)self)->deferred_input_arg1].id != 0)) &&
           ((int)cities[*(int *)((NetSessionExt *)self)->deferred_input_arg1].owner == ((NetSessionExt *)self)->deferred_input_arg2)) {
          city_button_change(*(i32 *)((NetSessionExt *)self)->deferred_input_arg3);
        }
        break;
      case 9:
        if (((city_window_block.city_window_closed == 0) && (cities[*(int *)((NetSessionExt *)self)->deferred_input_arg1].id != 0)) &&
           ((int)cities[*(int *)((NetSessionExt *)self)->deferred_input_arg1].owner == ((NetSessionExt *)self)->deferred_input_arg2)) {
          city_button_view(*(i32 *)((NetSessionExt *)self)->deferred_input_arg3);
        }
        break;
      case 10:
        if (((city_window_block.city_window_closed == 0) && (cities[*(int *)((NetSessionExt *)self)->deferred_input_arg1].id != 0)) &&
           ((int)cities[*(int *)((NetSessionExt *)self)->deferred_input_arg1].owner == ((NetSessionExt *)self)->deferred_input_arg2)) {
          city_button_rename(*(i32 *)((NetSessionExt *)self)->deferred_input_arg3);
        }
      }
      net_deferred_input_busy = '\0';
    }
    *(int *)((NetSessionExt *)self)->process_depth = *(int *)((NetSessionExt *)self)->process_depth + 1;
    if ((int)((NetSessionExt *)self)->max_process_depth < *(int *)((NetSessionExt *)self)->process_depth) {
      ((NetSessionExt *)self)->max_process_depth = *(u32 *)((NetSessionExt *)self)->process_depth;
    }
    while (max_msgs != 0) {
      if (((*(int *)((NetSessionExt *)self)->stacked_draw_active == 0) && (*(int *)((NetSessionExt *)self)->map_redraw_busy_2 == 0)) &&
         (0 < (int)((NetSessionExt *)self)->stacked_draw_count)) {
        ((NetSessionExt *)self)->stacked_draw_active[0] = 1;
        ((NetSessionExt *)self)->stacked_draw_active_b1[0] = '\0';
        ((NetSessionExt *)self)->stacked_draw_active_b2[0] = '\0';
        ((NetSessionExt *)self)->stacked_draw_active_b3[0] = '\0';
        if ((int)((NetSessionExt *)self)->stacked_draw_count < 0x22) {
          unit4 = 1;
        }
        else {
          unit4 = 2;
        }
        for (; 0 < unit4; unit4--) {
          net_stacked_draw_run_next();
        }
        ((NetSessionExt *)self)->stacked_draw_active[0] = '\0';
        ((NetSessionExt *)self)->stacked_draw_active_b1[0] = '\0';
        ((NetSessionExt *)self)->stacked_draw_active_b2[0] = '\0';
        ((NetSessionExt *)self)->stacked_draw_active_b3[0] = '\0';
      }
      if ((net_session_block.net_msgq_normal_count < 0x12d) && (net_session_block.net_msgq_priority_count < 0x22)) {
        ui_pump_messages();
        max_msgs--;
      }
      if (net_session_block.net_msgq_priority_count < 0x22) {
        dequeue_wait = wait_mode;
      }
      else {
        dequeue_wait = 1;
      }
      civ = net_msgq_dequeue
                        ((NetMessageQueue *)(self + 0x2c1a),(iptr)&sender,(iptr)&msg,
                         (iptr)&msg_size,dequeue_wait);
      if (civ == '\0') break;
      if (msg == (int *)0x0) {
        err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_pdata_null,(iptr)&str_d_ss_franklinton_netmgr_poll_cpp_3,0x195);
      }
      msg_hdr = msg;
      if (*msg == 0x66606660) {
        *(int *)(((i8 *)&net_session_block.nm_recv_counts) + msg[1] * 4) = *(int *)(((i8 *)&net_session_block.nm_recv_counts) + msg[1] * 4) + 1;
        if ((0x35 < msg[1]) && (civ_saved_cursor_x_block.game_setup_complete == 0)) {
          operator_delete(msg);
          break;
        }
        payload = (uint *)(msg + 0xb);
        switch(msg[1]) {
        case 0:
          hello_msg = msg;
          *(int *)(((i8 *)&net_session_block.nm_recv_counts) + msg[0x1c] * 4) =
               *(int *)(((i8 *)&net_session_block.nm_recv_counts) + msg[0x1c] * 4) + 1;
          if (msg[0x1c] == 1) {
            if (((*(char *)((int)&((NetSessionExt *)self)->session_flags + 3) != '\0') && (net_session_block.net_host_handoff_stage == '\0')) &&
               (net_session_block.net_connection_type != 0)) {
              net_send_message(2,0,0,0,0,0,0,0,0,0);
            }
          }
          else if (msg[0x1c] == 2) {
            net_game_list_add(self,(iptr)msg);
            gamelist_dirty = 1;
          }
          break;
        default:
          dbg_log((iptr)&str_received_unknown_message_type);
          break;
        case 4:
          crt_memcpy(self + 0x40,msg + 4,0x270);
          for (unit4 = 0; unit4 < 7; unit4++) {
            if ((*(char *)((int)self + unit4 * 0x54 + 0x251) != '\0') &&
               (*(int *)((int)self + unit4 * 0x54 + 0x204) == *(int *)((NetSessionExt *)self)->local_player_net_id)) {
              ((NetSessionExt *)self)->local_player_slot = unit4;
              break;
            }
          }
          break;
        case 5:
          now = timer_ticks();
          ((NetSessionExt *)self)->last_message_time = now;
          break;
        case 6:
          net_session_block.loaded_file_kind = (i16)msg[4];
          crt_strcpy(((i8 *)&net_session_block.loaded_file_name),(int)msg + 0x12);
          crt_strcpy(((i8 *)&net_session_block.loaded_file_subdir),(int)msg_hdr + 0x116);
          break;
        case 7:
        case 8:
        case 9:
          header_size = 0x2c;
          image_kind = msg[4];
          image_size = msg_size - 0x2c;
          crt_memmove(msg,msg + 0xb,image_size);
          msg = (int *)crt_realloc(msg,image_size);
          diffeng_apply_image((int*)(&msg),image_kind);
          break;
        case 10:
          header_size = 0x2c;
          image_kind = msg[4];
          image_size = msg_size - 0x2c;
          crt_memmove(msg,msg + 0xb,image_size);
          msg = (int *)crt_realloc(msg,image_size);
          diffeng_apply_map_header_image((int*)(&msg),image_kind);
          break;
        case 0xb:
        case 0xc:
        case 0x11:
          break;
        case 0xd:
          break;
        case 0xe:
          ((NetSessionExt *)self)->ack_message_counts[0]++;
          break;
        case 0xf:
          ((NetSessionExt *)self)->ack_message_counts[0]++;
          break;
        case 0x10:
          net_session_block.net_players_awaited--;
          break;
        case 0x12:
          net_send_message(0x13,sender,0,0,0,0,0,0,0,0);
          break;
        case 0x13:
          if (net_session_block.net_session[0] != 0) {
            crt_strcpy(net_session_block.net_session[0] + 0x88,msg + 4);
            crt_strcpy(net_session_block.net_session[0] + 0xa8,msg_hdr + 0x20);
            crt_strcpy(net_session_block.net_session[0] + 200,msg_hdr + 0x28);
            crt_strcpy(net_session_block.net_session[0] + 0xe8,msg_hdr + 0x10);
          }
          crt_strcpy(((i8 *)&net_session_block.net_server_address),msg_hdr + 4);
          crt_strcpy(((i8 *)&net_session_block.net_game_name),msg_hdr + 0x20);
          crt_strcpy(((i8 *)&net_session_block.net_local_player_name),((i8 *)&prefs_main_menu_choice_block.prefs_net_player_name));
          crt_strcpy(((i8 *)&net_session_block.net_server_version),msg_hdr + 0x10);
          break;
        case 0x14:
          break;
        case 0x15:
        case 0x5c:
          city_changed = 0;
          units_saved = 0;
          turn_civ_changed = 0;
          net_msg_get_args((iptr)msg,&unit);
          if (diffeng_mirror_buf != 0) {
            for (section_idx = 0; section_idx < (int)unit; section_idx++) {
              section_id2 = *payload;
              section_offset = payload[1];
              section_size = payload[2];
              payload += 3;
              if ((section_id2 & 0x7fff) == 1) {
                saved_active_unit = game.active_unit;
                saved_moving_unit = game.moving_unit;
                saved_multiplayer = game.multiplayer;
                saved_player_civ = game.player_civ;
                saved_field_1c = game.saved_current_civ;
                saved_turn_civ_val = game.turn_civ;
                saved_game_options = game.game_options;
                saved_msg_options = game.message_options;
              }
              else if (((net_session_block.net_host_flag == '\0') || ((section_id2 & 0x7fff) != 5)) || (units_saved != 0))
              {
                if ((section_id2 & 0x7fff) == 0xb) {
                  turn_civ_changed = 1;
                }
              }
              else {
                units_saved = 1;
                for (unit2 = 0; unit2 < game.num_units; unit2++) {
                  *(i16 *)(((i8 *)&map_views_block.net_saved_unit_x) + unit2 * 2) = units[unit2].x;
                  *(i16 *)(((i8 *)&map_views_block.net_saved_unit_y) + unit2 * 2) = units[unit2].y;
                  *(i16 *)(((i8 *)&map_views_block.net_saved_unit_next) + unit2 * 2) = units[unit2].next_in_stack;
                  *(i16 *)(((i8 *)&map_views_block.net_saved_unit_prev) + unit2 * 2) = units[unit2].prev_in_stack;
                }
              }
              if ((section_id2 & 0x8000) == 0) {
                crt_memcpy((((iptr *)&diffeng_sections_block.diffeng_section_ptrs))[section_id2 * 6] + section_offset,payload,section_size);
                crt_memcpy(*(int *)(((i8 *)&diffeng_sections_block.diffeng_section_offsets) + section_id2 * 0x18) + section_offset + diffeng_mirror_buf,
                             payload,section_size);
              }
              else {
                section_id2 = section_id2 & 0x7fff;
                rle_src_end = section_size + (int)payload;
                rle_src = payload;
                decoded_size = diffeng_rle_decoded_size((iptr)&rle_src);
                rle_dst = (((iptr *)&diffeng_sections_block.diffeng_section_ptrs))[section_id2 * 6] + section_offset;
                rle_dst_end = rle_dst + decoded_size;
                diffeng_rle_decode((iptr)&rle_src);
                crt_memcpy(*(int *)(((i8 *)&diffeng_sections_block.diffeng_section_offsets) + section_id2 * 0x18) + section_offset + diffeng_mirror_buf,
                             (((iptr *)&diffeng_sections_block.diffeng_section_ptrs))[section_id2 * 6] + section_offset,decoded_size);
              }
              if (section_id2 == 1) {
                game.active_unit = saved_active_unit;
                game.moving_unit = saved_moving_unit;
                game.multiplayer = saved_multiplayer;
                game.player_civ = saved_player_civ;
                game.saved_current_civ = saved_field_1c;
                game.turn_civ = saved_turn_civ_val;
                game.game_options = saved_game_options;
                game.message_options = saved_msg_options;
              }
              if (section_id2 == 6) {
                city_changed = 1;
              }
              payload = (uint *)((int)payload + section_size);
            }
            if (city_changed != 0) {
              city_window_refresh((FrameWindow *)((i8 *)&city_window_block.city_window));
            }
            if ((net_session_block.net_host_flag != '\0') && (units_saved != 0)) {
              for (unit2 = 0; unit2 < game.num_units; unit2++) {
                units[unit2].x = *(i16 *)(((i8 *)&map_views_block.net_saved_unit_x) + unit2 * 2);
                units[unit2].y = *(i16 *)(((i8 *)&map_views_block.net_saved_unit_y) + unit2 * 2);
                units[unit2].next_in_stack = *(i16 *)(((i8 *)&map_views_block.net_saved_unit_next) + unit2 * 2);
                units[unit2].prev_in_stack = *(i16 *)(((i8 *)&map_views_block.net_saved_unit_prev) + unit2 * 2);
              }
            }
            if (turn_civ_changed != 0) {
              turn_resume_civ = civ_saved_cursor_x_block.saved_turn_civ;
            }
          }
          break;
        case 0x16:
          break;
        case 0x17:
          crt_memcpy(&cosmic,payload,0x29);
          break;
        case 0x18:
          crt_memcpy(advances,payload,0x640);
          break;
        case 0x19:
          crt_memcpy(improvements,payload,0x218);
          break;
        case 0x1a:
          crt_memcpy(wonder_expires,payload,0x1c);
          break;
        case 0x1b:
          crt_memcpy(unit_types,payload,0x4d8);
          break;
        case 0x1c:
          crt_memcpy(terrain_types,payload,0x318);
          break;
        case 0x1d:
          crt_memcpy(government_names,payload,0x1c);
          break;
        case 0x1e:
          crt_memcpy(government_titles,payload,0x38);
          break;
        case 0x1f:
          crt_memcpy(leaders,payload,0x3f0);
          break;
        case 0x20:
          crt_memcpy(civs,payload,0x7524);
          break;
        case 0x21:
          crt_memcpy(commodity_names,payload,0x40);
          break;
        case 0x22:
          crt_memcpy(order_names,payload,0x68);
          break;
        case 0x23:
          crt_memcpy(difficulty_names,payload,0x18);
          break;
        case 0x24:
          crt_memcpy(attitude_names,payload,0x24);
          break;
        case 0x25:
          net_msg_get_args((iptr)msg,&unit);
          (*(uptr *)&scenario_events_loaded) = unit;
          (*(uptr *)&unit_types_block.scenario_event_count) = civ3;
          if (unit != 0) {
            events_relink_pool();
          }
          break;
        case 0x26:
          break;
        case 0x27:
          break;
        case 0x28:
          net_msg_get_args((iptr)msg,&unit);
          (*(uptr *)&net_session_block.net_session_phase) = unit;
          break;
        case 0x2a:
          net_msg_get_args((iptr)msg,&unit);
          (*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask) = (ushort)unit;
          game.human_players = game.human_players & (byte)unit;
          net_session_block.nm_lock_nation_count_i32++;
          break;
        case 0x2b:
          net_send_message(0x2c,sender,0,0,0,0,0,0,0,0);
          break;
        case 0x2c:
          break;
        case 0x2d:
          net_msg_get_args((iptr)msg,&unit);
          *(i32 *)(((i8 *)&net_session_block.net_civ_drop_requested) + unit * 4) = 1;
          net_drop_flagged_players();
          break;
        case 0x2e:
          if (net_session_block.net_host_flag == '\0') {
            err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_gnetmgr_bserver,(iptr)&str_d_ss_franklinton_netmgr_poll_cpp_4,0x22a);
          }
          if (net_session_block.net_host_handoff_stage == '\0') {
            city = net_host_register_player_civ((iptr)msg_hdr,sender);
            if (city == 0) {
              net_send_message(0xc,sender,0,0,0,0,0,0,0,0);
            }
            else {
              net_session_block.nm_lock_nation_count_i32++;
              if (2 < (int)(*(uptr *)&net_session_block.net_session_phase)) {
                dialog_ctor(&join_dialog,0x4000);
                unwind_state = 1;
                net_send_message(0x65,0xff,0,0,0,0,0,0,0,0);
                mp_turn_timer_stop(0);
                dlg_load_game_section(&join_dialog,(iptr)&str_waitongamexmit_2,0x2000000);
                dlg_show_modal(&join_dialog,0);
                net_send_message(0x33,sender,(int)civ_saved_cursor_x_block.mp_double_production,(int)civ_saved_cursor_x_block.mp_double_moves,
                                   (int)civ_saved_cursor_x_block.mp_simultaneous_setting,0,0,0,0,0);
                net_send_message(4,0xff,0,0,0,0,0,0,0,0);
                XD_FlushSendBuffer(5000);
                net_send_state_diff(0xff,2,0,0,0);
                XD_FlushSendBuffer(5000);
                net_send_message(10,sender,0,0,0,0,0,0,0,0);
                net_send_state_diff(sender,1,0,0,0);
                XD_FlushSendBuffer(5000);
                net_send_message(0x25,sender,(*(uptr *)&scenario_events_loaded),(*(uptr *)&unit_types_block.scenario_event_count),0,0,0,0,0,0);
                net_send_rules_tables(sender);
                XD_FlushSendBuffer(5000);
                net_send_message(0x28,sender,(*(uptr *)&net_session_block.net_session_phase),0,0,0,0,0,0,0);
                net_send_message(0x16,sender,0,0,0,0,0,0,0,0);
                net_send_message(0x9c,0xff,0,0,0,0,0,0,0,0);
                wait_start = timer_ticks();
                do {
                  city = XD_FlushSendBuffer(5000);
                  if (city == 0) break;
                  net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),100,0);
                  city = timer_ticks();
                } while (17999 < city - wait_start);
                net_send_message(0x66,0xff,0,0,0,0,0,0,0,0);
                dialog_close(&join_dialog);
                mp_turn_timer_resume(0);
                for (slot = 0;
                    (slot < 7 && (*(int *)(((i8 *)&net_session_block.net_player_slots) + slot * 0x54) != sender));
                    slot = slot + 1) {
                }
                if (slot < 7) {
                  civ_flag = ((NetSessionExt *)self)->civ_flags + (((i32 *)&net_session_block.net_slot_civs))[slot * 0x15] * 4 + 4;
                  civ_flag[0] = 1;
                  civ_flag[1] = '\0';
                  civ_flag[2] = '\0';
                  civ_flag[3] = '\0';
                }
                unwind_state = 0xffffffff;
                /* inlined unwind funclet 00482305 */ { dialog_dtor((Dialog *)((iptr)&join_dialog)); }
              }
            }
          }
          else {
            net_send_message(0xb,sender,0,0,0,0,0,0,0,0);
          }
          break;
        case 0x2f:
          if (net_session_block.net_host_handoff_stage == '\0') {
            if (net_session_block.net_player_count[0] < net_session_block.net_max_players) {
              net_add_player(self,(iptr)msg);
              if (((*(int * *)&net_session_block.net_lobby_list) == (int *)0x0) || (*(*(int * *)&net_session_block.net_lobby_list) == 0)) {
                if (0 < (int)(*(uptr *)&net_session_block.net_session_phase)) {
                  net_send_message(0x28,sender,(*(uptr *)&net_session_block.net_session_phase),0,0,0,0,0,0,0);
                  net_send_message(4,0xff,0,0,0,0,0,0,0,0);
                  net_send_message(6,sender,0,0,0,0,0,0,0,0);
                  net_send_message(9,sender,0,0,0,0,0,0,0,0);
                }
              }
              else {
                lobby_refresh_player_list();
              }
            }
            else {
              net_send_message(0x11,sender,0,0,0,0,0,0,0,0);
            }
          }
          else {
            net_send_message(0xb,sender,0,0,0,0,0,0,0,0);
          }
          break;
        case 0x30:
          net_msg_get_args((iptr)msg,&unit);
          if (((int)(short)(*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask) & 1 << ((byte)civ3 & 0x1f)) == 0) {
            (*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask) = (ushort)(1 << ((byte)civ3 & 0x1f)) | (*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask);
            net_send_message(0x26,sender,(int)(short)(*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask),0,0,0,0,0,0,0);
            net_send_message(0x2a,0xff,(int)(short)(*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask),0,0,0,0,0,0,0);
            net_session_block.nm_lock_nation_count_i32++;
          }
          else {
            net_send_message(0x27,sender,0,0,0,0,0,0,0,0);
          }
          break;
        case 0x31:
          net_msg_get_args((iptr)msg,&unit);
          game.human_players = game.human_players & (byte)(*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask);
          if (((int)(short)(*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask) & 1 << ((byte)civ3 & 0x1f)) != 0) {
            (*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask) = ~(ushort)(1 << ((byte)civ3 & 0x1f)) & (*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask);
            game.human_players = game.human_players & (byte)(*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask);
            net_send_message(0x2a,0xff,(int)(short)(*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask),0,0,0,0,0,0,0);
            net_session_block.nm_lock_nation_count_i32++;
          }
          break;
        case 0x32:
          *(i32 *)(((i8 *)&net_session_block.net_lost_conn_by_player) + sender * 4) = 0xffffffff;
          net_remove_player(self,sender);
          if ((self->player_stats != 0) &&
             (drop_counter = (int *)(self->player_stats + 0x54 + sender * 4), *drop_counter = *drop_counter + 1,
             *(*(int * *)&net_session_block.net_lobby_list) != 0)) {
            lobby_refresh_player_list();
          }
          break;
        case 0x33:
          net_msg_get_args((iptr)msg,&unit);
          civ_saved_cursor_x_block.mp_double_production = (short)unit;
          civ_saved_cursor_x_block.mp_double_moves = (short)civ3;
          net_session_block.mp_simultaneous_moves = (char)unit3;
          civ_saved_cursor_x_block.mp_simultaneous_setting = (short)(char)unit3;
          break;
        case 0x34:
          net_msg_get_args((iptr)msg,&unit);
          civ_eliminate(unit,0,0);
          net_send_message(0x35,sender,0,0,0,0,0,0,0,0);
          break;
        case 0x35:
          net_session_block.net_kill_or_quit_ack = 1;
          break;
        case 0x37:
          net_msg_get_args((iptr)msg,&unit);
          if ((-1 < (int)unit) && (units[unit].id != 0)) {
            x3 = (int)units[unit].x;
            y4 = (int)units[unit].y;
          }
          unit_delete(unit,1);
          net_send_message(0x38,sender,unit,0,0,0,0,0,0,0);
          XD_FlushSendBuffer(5000);
          break;
        case 0x38:
          net_msg_get_args((iptr)msg,&unit);
          net_session_block.net_unit_deleted_ack = 1;
          break;
        case 0x39:
          net_msg_get_args((iptr)msg,&unit);
          city_delete(unit,0);
          net_send_message(0x3a,sender,unit,0,0,0,0,0,0,0);
          XD_FlushSendBuffer(5000);
          break;
        case 0x3a:
          net_msg_get_args((iptr)msg,&unit);
          net_session_block.net_city_deleted_ack = 1;
          crt_memcpy(cities + unit,payload,0x58);
          break;
        case 0x3b:
          net_msg_get_args((iptr)msg,&unit);
          result = city_create(unit,civ3,unit3);
          net_send_message(0x3c,sender,result,0,0,0,0,0,0,0);
          XD_FlushSendBuffer(5000);
          break;
        case 0x3c:
          net_msg_get_args((iptr)msg,&unit);
          net_session_block.nm_city_created_result = unit;
          if (unit != 0xffffffff) {
            crt_memcpy(cities + unit,payload,0x58);
            game.num_cities = (i16)civ3;
          }
          break;
        case 0x3d:
          net_msg_get_args((iptr)msg,&unit);
          result = unit_create(unit,civ3,unit3,y2);
          net_send_message(0x3e,sender,result,0,0,0,0,0,0,0);
          XD_FlushSendBuffer(5000);
          break;
        case 0x3e:
          net_msg_get_args((iptr)msg,&unit);
          net_session_block.nm_unit_created_result = unit;
          if (unit != 0xffffffff) {
            game.num_units = (i16)civ3;
          }
          break;
        case 0x3f:
          net_msg_get_args((iptr)msg,&unit);
          unit_stack_unlink(unit,1);
          net_send_message(0x40,sender,0,0,0,0,0,0,0,0);
          XD_FlushSendBuffer(5000);
          break;
        case 0x40:
          net_session_block.nm_unit_picked_up_count = 1;
          break;
        case 0x41:
          net_msg_get_args((iptr)msg,&unit);
          unit_stack_link(unit,civ3,unit3,1);
          net_send_message(0x42,sender,0,0,0,0,0,0,0,0);
          XD_FlushSendBuffer(5000);
          break;
        case 0x42:
          net_session_block.nm_unit_put_down_count = 1;
          break;
        case 0x43:
          net_msg_get_args((iptr)msg,&unit);
          unit_move_to_stack_bottom(unit,1);
          net_send_message(0x44,sender,0,0,0,0,0,0,0,0);
          XD_FlushSendBuffer(5000);
          break;
        case 0x44:
          net_session_block.nm_bottomed_count = 1;
          break;
        case 0x45:
          net_msg_get_args((iptr)msg,&unit);
          unit_relocate(unit,civ3,unit3,1);
          net_send_message(0x46,sender,0,0,0,0,0,0,0,0);
          XD_FlushSendBuffer(5000);
          break;
        case 0x46:
          net_session_block.nm_unit_relocated_count = 1;
          break;
        case 0x47:
          net_msg_get_args((iptr)msg,&unit);
          result = city_acquire_wonder(unit,civ3,unit3,y2,x2);
          net_send_message(0x48,sender,result,0,0,0,0,0,0,0);
          XD_FlushSendBuffer(5000);
          break;
        case 0x48:
          net_msg_get_args((iptr)msg,&unit);
          (*(uptr *)&net_session_block.nm_wonder_acquired_result) = unit;
          break;
        case 0x49:
          net_msg_get_args((iptr)msg,&unit);
          ret_val = unit_gather_cargo(unit,civ3,1);
          net_send_message(0x4a,sender,ret_val,0,0,0,0,0,0,0);
          break;
        case 0x4a:
          net_msg_get_args((iptr)msg,&unit);
          net_session_block.nm_ship_stacked_result = unit;
          break;
        case 0x4b:
          net_msg_get_args((iptr)msg,&unit);
          unit_lift_off_map(unit,1);
          net_send_message(0x4c,sender,0,0,0,0,0,0,0,0);
          break;
        case 0x4c:
          net_session_block.nm_unit_stacked_count = 1;
          break;
        case 0x4d:
          net_msg_get_args((iptr)msg,&unit);
          unit_delete_with_cargo(unit,1);
          net_send_message(0x4e,sender,0,0,0,0,0,0,0,0);
          break;
        case 0x4e:
          net_session_block.nm_safely_deleted_count = 1;
          break;
        case 0x4f:
          net_msg_get_args((iptr)msg,&unit);
          unit_destroy_redraw(unit,1);
          net_send_message(0x50,sender,0,0,0,0,0,0,0,0);
          break;
        case 0x50:
          net_session_block.nm_visibly_deleted_count = 1;
          break;
        case 0x51:
          net_msg_get_args((iptr)msg,&unit);
          net_lock_map(unit,civ3,unit3,y2,x2,0);
          break;
        case 0x52:
          net_msg_get_args((iptr)msg,&unit);
          net_unlock_map(unit,0);
          net_send_message(0x54,sender,unit,0,0,0,0,0,0,0);
          break;
        case 0x53:
          net_msg_get_args((iptr)msg,&unit);
          *(uptr *)(((i8 *)&net_map_lock_slots_block.net_map_lock_replies) + unit * 0x18) = civ3;
          break;
        case 0x54:
          net_msg_get_args((iptr)msg,&unit);
          *(int *)(((i8 *)&net_map_lock_slots_block.net_map_lock_slots) + unit * 0x18) = *(int *)(((i8 *)&net_map_lock_slots_block.net_map_lock_slots) + unit * 0x18) + 1;
          break;
        case 0x55:
          net_msg_get_args((iptr)msg,&unit);
          *(uptr *)(((i8 *)&net_map_lock_slots_block.net_map_lock_src_x) + unit * 0x18) = civ3;
          *(uptr *)(((i8 *)&net_map_lock_slots_block.net_map_lock_src_y) + unit * 0x18) = unit3;
          *(iptr *)(((i8 *)&net_map_lock_slots_block.net_map_lock_dst_x) + unit * 0x18) = y2;
          *(iptr *)(((i8 *)&net_map_lock_slots_block.net_map_lock_dst_y) + unit * 0x18) = x2;
          *(i32 *)(((i8 *)&net_map_lock_slots_block.net_map_lock_replies) + unit * 0x18) = 0;
          *(i32 *)(((i8 *)&net_map_lock_slots_block.net_map_lock_slots) + unit * 0x18) =
               *(i32 *)(((i8 *)&net_map_lock_slots_block.net_map_lock_replies) + unit * 0x18);
          break;
        case 0x56:
        case 0x57:
          net_msg_get_args((iptr)msg,&unit);
          net_session_block.net_vote_replies_pending--;
          if (unit == 2) {
            net_session_block.net_vote_status = 0xffffffff;
          }
          break;
        case 0x58:
          wonder_apollo_reveal_map();
          break;
        case 0x59:
          net_apply_tile_updates((iptr)payload);
          break;
        case 0x5a:
          net_msg_get_args((iptr)msg,&unit);
          unit_lift_off_map(unit3,0);
          unit_stack_clear_visibility(unit3);
          if (y2 == 0) {
            unit_stack_set_seen_by(unit3,civ3);
          }
          unit_stack_relocate_all(unit3,x2,y3,0);
          if ((-1 < units[unit3].next_in_stack) &&
             (unit_types[units[unit3].type].attack == '\0')) {
            unit_move_to_stack_bottom(unit3,0);
          }
          if (net_session_block.mp_simultaneous_moves != '\0') {
            net_unlock_map(unit,0);
          }
          net_send_state_diff(0xff,2,0,0,1);
          net_send_message(0x5b,sender,0,0,0,0,0,0,0,0);
          XD_FlushSendBuffer(60000);
          break;
        case 0x5b:
          net_session_block.nm_stacker_ack_count = 1;
          break;
        case 0x5d:
          net_session_block.net_drag_hold = 1;
          dbg_log((iptr)&str_hold_on);
          break;
        case 0x5e:
          net_session_block.net_drag_hold = 0;
          dbg_log((iptr)&str_hold_off);
          break;
        case 0x5f:
          net_msg_get_args((iptr)msg,&unit);
          result = civ_create(unit);
          net_send_message(0x61,sender,result,0,0,0,0,0,0,0);
          break;
        case 0x60:
          net_msg_get_args((iptr)msg,&unit);
          result = civ_check_destroyed(unit,civ3);
          net_send_message(0x62,sender,result,0,0,0,0,0,0,0);
          break;
        case 0x61:
          net_msg_get_args((iptr)msg,&unit);
          (*(uptr *)&net_session_block.nm_new_civ_ack_result) = unit;
          break;
        case 0x62:
          net_msg_get_args((iptr)msg,&unit);
          (*(uptr *)&net_session_block.nm_kill_civ_ack_result) = unit;
          break;
        case 99:
          net_msg_get_args((iptr)msg,&unit);
          civ2 = civ3;
          unit5 = unit;
          civ = units[unit].owner;
          civs[civ3].gold -= unit3;
          type_count = (char *)(units[unit].type + (iptr)((u8 *)&civs + 216) + civ * 0x594);
          *type_count = *type_count - 1;
          type_count = (char *)(units[unit].type + (iptr)((u8 *)&civs + 216) + civ3 * 0x594);
          *type_count = *type_count + 1;
          civs[civ3].subversion_count++;
          new_owner = (i8)civ3;
          units[unit].owner = new_owner;
          units[unit].home_city = -1;
          units[unit].moves_used = '\0';
          units[unit].orders = -1;
          city = city_find_nearest((int)units[unit].x,(int)units[unit].y,-1,0xffffffff,-1)
          ;
          if ((-1 < city) && ((int)cities[city].owner == civ2)) {
            home_city_id = (i8)city;
            units[unit5].home_city = home_city_id;
          }
          unit_set_seen_by(unit5,(int)civ);
          tile_set_owner((int)units[unit5].x,(int)units[unit5].y,civ2,1);
          net_send_state_diff(0xff,2,0,0,1);
          break;
        case 100:
          net_msg_get_args((iptr)msg,&unit);
          casualty_log_add(unit,civ3,unit3,y2,x2);
          break;
        case 0x65:
          dialog_ctor(&wait_dialog,0x4000);
          unwind_state = 0;
          saved_busy = ((NetSessionExt *)self)->popup_busy;
          ((NetSessionExt *)self)->popup_busy = 1;
          mp_turn_timer_stop(0);
          net_session_block.nm_continue_after_join_count = 0;
          dlg_pending_idle_callback = ((i8*)(net_game_xmit_wait_idle));
          popup_game_sprite_flags((iptr)&str_waitongamexmit,0x2000000,(iptr)&popup_info_icon_sprite,0);
          dialog_close(&wait_dialog);
          ((NetSessionExt *)self)->popup_busy = saved_busy;
          mp_turn_timer_resume(0);
          unwind_state = 0xffffffff;
          /* inlined unwind funclet 00482311 */ { dialog_dtor((Dialog *)((iptr)&wait_dialog)); }
          break;
        case 0x66:
          break;
        case 0x68:
          net_msg_get_args((iptr)msg,&unit);
          header_size = 0x2c;
          chat_receive_message
                    ((WindowObjectView *)((i8 *)&chat_wnd_block.chat_wnd),unit,civ3,unit3,(iptr)(msg + 0xb)
                    );
          break;
        case 0x69:
          had_pending = *(int *)((NetSessionExt *)self)->stacked_draw_active != 0;
          if (had_pending) {
            net_session_block.net_stacked_draw_last = (net_session_block.net_stacked_draw_first + 1) % 100;
          }
          else {
            net_session_block.net_stacked_draw_first = 0;
            net_session_block.net_stacked_draw_last = 0;
          }
          net_session_block.net_stacked_draw_count = (uint)had_pending;
          net_stacked_draw_push(0xa3,(iptr)draw_args,0);
          net_stacked_draw_push(0x74,(iptr)draw_args,0);
          game.turn_civ = (i8)msg_hdr[4];
          net_session_block.mp_turn_civ = (int)game.turn_civ;
          mp_turn_timer_stop(1);
          menu_update_states();
          map_views_block.main_view_timer_cache_i32 = 0xffffffff;
          frame_wnd_draw_caption((FrameWindow *)((i8 *)&map_views_block.map_views));
          caption_rect.left = map_views_block.main_view_frame_left;
          caption_rect.top = map_views_block.main_view_frame_top;
          caption_rect.right = map_views_block.main_view_frame_right;
          caption_rect.bottom = map_views_block.main_view_client_top;
          wnd_blit_surface_rect((DibSurface *)((i8 *)&map_views_block.map_views),(iptr)&caption_rect);
          break;
        case 0x6a:
          net_msg_get_args((iptr)msg,&unit);
          header_size = 0x2c;
          if ((unit == 0x3d) &&
             (((1 << ((byte)(*(i8 *)&human_civ) & 0x1f) & (uint)game.human_players) == 0 ||
              (mp_meeting_pending != 0)))) {
            net_send_message(0x80,sender,2,0,0,0,0,0,0,0);
          }
          else {
            if (unit == 0x3d) {
              mp_meeting_pending = 1;
            }
            if (((unit != 100) || (parley_reveal_units_prompt_open != 1)) &&
               ((unit != 0x65 || (parley_reveal_city_prompt_open != 1)))) {
              if (extra_len == 0) {
                popup_data = (int *)0x0;
              }
              else {
                popup_data = msg + 0xb;
              }
              net_popup_queue_push(unit,civ3,unit3,y2,x2,popup_data,extra_len);
            }
          }
          break;
        case 0x6b:
          net_msg_get_args((iptr)msg,&unit);
          game.game_flags = (u16)unit;
          (*(uptr *)&game_over_reason) = civ3;
          (*(uptr *)&year_table_start_years_block.spaceship_winner_civ) = unit3;
          break;
        case 0x6c:
          net_msg_get_args((iptr)msg,&unit);
          (*(uptr *)&civ_saved_cursor_x_block.mp_turn_time_limit_ms) = unit;
          if (unit == 0) {
            map_views_block.main_view_timer_shown[0] = 0;
            frame_wnd_draw_caption((FrameWindow *)((i8 *)&map_views_block.map_views));
            timer_rect.left = map_views_block.main_view_frame_left;
            timer_rect.top = map_views_block.main_view_frame_top;
            timer_rect.right = map_views_block.main_view_frame_right;
            timer_rect.bottom = map_views_block.main_view_client_top;
            wnd_blit_surface_rect((DibSurface *)((i8 *)&map_views_block.map_views),(iptr)&timer_rect);
          }
          else {
            map_views_block.main_view_timer_shown[0] = 1;
            mp_turn_timer_start(1);
          }
          break;
        case 0x6d:
          if ((*(uptr *)&civ_saved_cursor_x_block.mp_turn_time_limit_ms) != 0) {
            map_views_block.main_view_timer_shown[0] = 1;
          }
          mp_turn_timer_start(0);
          break;
        case 0x6e:
          mp_turn_timer_stop(0);
          break;
        case 0x6f:
          mp_turn_timer_resume(0);
          break;
        case 0x70:
          net_msg_get_args((iptr)msg,&unit);
          if (y3 != 0) {
            x = map_wrap_x((int)(char)(((i8 *)&dir_dx_table_block.dir_dx_table))[y2] + civ3);
            city = city_at(x,(int)(char)(((i8 *)&dir_dy_table_block.dir_dy_table))[y2] + unit3);
            if ((city < 0) && ((game.game_options & 0x1000) == 0)) {
              msg_hdr[1] = 0x72;
              unit = civ3;
              civ3 = unit3;
            }
          }
          net_stacked_draw_push(msg_hdr[1],(iptr)&unit,(iptr)payload);
          break;
        case 0x71:
          net_msg_get_args((iptr)msg,&unit);
          net_stacked_draw_push(msg_hdr[1],(iptr)&unit,0);
          break;
        case 0x72:
          net_msg_get_args((iptr)msg,&unit);
          city = mapviews_tile_visible(unit,civ3);
          if (city != 0) {
            net_stacked_draw_push(msg_hdr[1],(iptr)&unit,0);
          }
          break;
        case 0x73:
          net_msg_get_args((iptr)msg,&unit);
          city = mapviews_tile_visible(unit,civ3);
          if ((city != 0) || (city = mapviews_tile_visible(unit3,y2), city != 0)) {
            net_stacked_draw_push(msg_hdr[1],(iptr)&unit,0);
          }
          break;
        case 0x74:
          net_stacked_draw_push(msg[1],(iptr)&unit,0);
          break;
        case 0x75:
          net_msg_get_args((iptr)msg,&unit);
          city = mapviews_tile_visible(unit,civ3);
          if (city != 0) {
            net_stacked_draw_push(msg_hdr[1],(iptr)&unit,0);
          }
          break;
        case 0x76:
          net_msg_get_args((iptr)msg,&unit);
          city = mapviews_tile_visible(unit,civ3);
          if (city != 0) {
            net_stacked_draw_push(msg_hdr[1],(iptr)&unit,0);
          }
          break;
        case 0x77:
          net_msg_get_args((iptr)msg,&unit);
          (*(uptr *)&sprite_picker_sprite_block.net_can_escape_reply) = unit;
          break;
        case 0x78:
          status_draw_info(1);
          break;
        case 0x79:
          status_redraw(1);
          break;
        case 0x7a:
          net_msg_get_args((iptr)msg,&unit);
          snd_play_effect(unit,civ3,0,0);
          break;
        case 0x7b:
          net_msg_get_args((iptr)msg,&unit);
          font_size16_bold_block.net_bribe_answer = unit;
          break;
        case 0x7c:
          net_msg_get_args((iptr)msg,&unit);
          net_stacked_draw_push(msg_hdr[1],(iptr)&unit,0);
          break;
        case 0x7d:
          net_msg_get_args((iptr)msg,&unit);
          net_stacked_draw_push(msg_hdr[1],(iptr)&unit,0);
          break;
        case 0x7e:
          net_msg_get_args((iptr)msg,&unit);
          diplo_ally_demand_help(unit,civ3);
          break;
        case 0x7f:
          net_msg_get_args((iptr)msg,&unit);
          advisor_refresh_if_open(unit);
          break;
        case 0x80:
          net_msg_get_args((iptr)msg,&unit);
          (*(uptr *)&advisor_window_block.mp_meeting_reply) = unit;
          break;
        case 0x81:
          if ((((((i32 *)&net_session_block.net_slot_civs))[sender * 0x15] == (*(uptr *)&parley_wnd_block.parley_other_civ)) || ((*(uptr *)&parley_wnd_block.parley_other_civ) == 0xfffffffe))
             || (parley_wnd_block.parley_wnd_closed == 0)) {
            if (parley_wnd_block.parley_wnd_closed == 0) {
              parley_wnd_close();
            }
            else if ((*(uptr *)&parley_wnd_block.parley_other_civ) == 0xfffffffe) {
              (*(uptr *)&parley_wnd_block.parley_other_civ) = 0xffffffff;
            }
            mp_meeting_pending = 0;
          }
          break;
        case 0x82:
          if (parley_wnd_block.parley_received_offer != (void *)0x0) {
            operator_delete(parley_wnd_block.parley_received_offer);
            parley_wnd_block.parley_received_offer = (void *)0x0;
          }
          parley_wnd_block.parley_received_offer = operator_new(msg_size);
          if (parley_wnd_block.parley_received_offer != (void *)0x0) {
            crt_memcpy(parley_wnd_block.parley_received_offer,msg,msg_size);
          }
          parley_poll_net_replies();
          break;
        case 0x83:
          parley_poll_net_replies();
          break;
        case 0x84:
          parley_poll_net_replies();
          break;
        case 0x85:
          parley_poll_net_replies();
          break;
        case 0x86:
          parley_execute_transaction((iptr)msg);
          break;
        case 0x87:
          net_msg_get_args((iptr)msg,&unit);
          city_window_on_unit_change
                    ((FrameWindow *)((i8 *)&city_window_block.city_window),unit,civ3,unit3);
          break;
        case 0x88:
          net_msg_get_args((iptr)msg,&unit);
          city_window_refresh_if_city((FrameWindow *)((i8 *)&city_window_block.city_window),unit);
          break;
        case 0x89:
          net_msg_get_args((iptr)msg,&unit);
          city_window_close_if_city((WindowObjectView *)((i8 *)&city_window_block.city_window),unit);
          break;
        case 0x8a:
          if (city_window_block.city_window_refresh_locked == 0) {
            city_window_refresh((FrameWindow *)((i8 *)&city_window_block.city_window));
          }
          break;
        case 0x8b:
          break;
        case 0x8c:
          net_msg_get_args((iptr)msg,&unit);
          *(int *)(((i8 *)&dialog_text_font_obj_block.net_civ_phase_done) + unit * 4) = *(int *)(((i8 *)&dialog_text_font_obj_block.net_civ_phase_done) + unit * 4) + 1;
          break;
        case 0x8d:
          break;
        case 0x8e:
          break;
        case 0x8f:
          net_msg_get_args((iptr)msg,&unit);
          *(int *)(((i8 *)&dialog_text_font_obj_block.net_civ_phase_done) + unit * 4) = *(int *)(((i8 *)&dialog_text_font_obj_block.net_civ_phase_done) + unit * 4) + 1;
          for (unit4 = 0; unit4 < game.num_units; unit4++) {
            if ((units[unit4].id != 0) && ((int)units[unit4].owner == unit)) {
              unit_exhaust_moves(unit4);
            }
          }
          break;
        case 0x90:
          net_msg_get_args((iptr)msg,&unit);
          tile_set_improvements(unit,civ3,unit3,y2,x2);
          break;
        case 0x91:
          net_msg_get_args((iptr)msg,&unit);
          tile_set_terrain(unit,civ3,unit3,y2);
          break;
        case 0x92:
          net_msg_get_args((iptr)msg,&unit);
          tile_set_visible(unit,civ3,unit3,y2,x2);
          break;
        case 0x93:
          net_msg_get_args((iptr)msg,&unit);
          tile_set_fertility(unit,civ3,unit3,y2);
          break;
        case 0x94:
          net_msg_get_args((iptr)msg,&unit);
          tile_set_owner(unit,civ3,unit3,y2);
          break;
        case 0x95:
          net_msg_get_args((iptr)msg,&unit);
          tile_set_landmass(unit,civ3,unit3,y2);
          break;
        case 0x96:
          net_msg_get_args((iptr)msg,&unit);
          tile_set_radius_civ(unit,civ3,unit3,y2);
          break;
        case 0x97:
          net_msg_get_args((iptr)msg,&unit);
          known_set(unit,civ3,unit3,y2,x2,y3);
          break;
        case 0x98:
          net_msg_get_args((iptr)msg,&unit);
          *(char *)&civs[unit].attitude[civ3] = (char)unit3;
          break;
        case 0x99:
          net_msg_get_args((iptr)msg,&unit);
          *(i32 *)(((i8 *)&net_meet_pending_flags) + civ3 * 4) = 1;
          *(uptr *)(((i8 *)&map_views_block.net_meet_pending_ai_civ) + civ3 * 4) = unit;
          *(uptr *)(((i8 *)&map_views_block.net_meet_pending_civ) + civ3 * 4) = civ3;
          *(uptr *)(((i8 *)&map_views_block.net_meet_pending_x) + civ3 * 4) = unit3;
          *(iptr *)(((i8 *)&map_views_block.net_meet_pending_y) + civ3 * 4) = y2;
          break;
        case 0x9a:
          net_msg_get_args((iptr)msg,&unit);
          (*(uptr *)&net_session_block.net_move_anim_sound) = unit;
          (*(uptr *)&net_session_block.net_move_anim_sound_arg) = civ3;
          break;
        case 0x9b:
          net_msg_get_args((iptr)msg,&unit);
          civ_give_advance(unit,civ3,unit3,y2,0);
          break;
        case 0x9c:
          break;
        case 0x9d:
          taxrate_dialog_show((*(i8 *)&human_civ));
          break;
        case 0x9e:
          taxrate_enforce_max_rate((*(i8 *)&human_civ));
          break;
        case 0x9f:
          net_msg_get_args((iptr)msg,&unit);
          civ_select_government_dialog((*(i8 *)&human_civ),unit);
          break;
        case 0xa0:
          net_msg_get_args((iptr)msg,&unit);
          diplo_ai_review_relations(unit,civ3);
          break;
        case 0xa1:
          net_msg_get_args((iptr)msg,&unit);
          diplo_ai_seek_war_ally(unit,civ3);
          break;
        case 0xa2:
          net_msg_get_args((iptr)msg,&unit);
          *(int *)(((i8 *)&net_session_block.net_civ_turn_ended) + unit * 4) = *(int *)(((i8 *)&net_session_block.net_civ_turn_ended) + unit * 4) + 1;
          break;
        case 0xa3:
          net_stacked_draw_push(msg[1],(iptr)&unit,0);
          break;
        case 0xa4:
          net_msg_get_args((iptr)msg,&unit);
          ret_val = civ_name_plural(unit);
          text_set_string_arg(0,ret_val);
          ret_val = civ_name_plural(civ3);
          text_set_string_arg(1,ret_val);
          if ((*(byte *)&civs[civ3].treaties[unit] & 8) == 0) {
            city = popup_game_with_sprite((iptr)&str_pretext,(iptr)&war_icon_sprite_block.war_icon_sprite,0);
            if (city == 1) {
              diplo_set_treaty_flags(unit,civ3,0x2000);
              civs[civ3].last_treaty_turn[unit] = game.turn;
            }
          }
          else {
            city = popup_game_with_sprite((iptr)&str_pretextallied,(iptr)(((i8 *)&diplo_popup_portrait_sprite) +
                                                      ((game.advance_known_by[0xf] != '\0') - 1 &
                                                      0xffff7c80)),0);
            if (city == 1) {
              diplo_clear_treaty_flags(unit,civ3,8);
              civs[civ3].last_treaty_turn[unit] = game.turn;
            }
          }
          break;
        case 0xa5:
          net_msg_get_args((iptr)msg,&unit);
          if ((parley_wnd_block.parley_wnd_closed == 0) && ((*(uptr *)&parley_wnd_block.parley_other_civ) == unit)) {
            parley_wnd_block.parley_remote_cities_revealed = (byte)civ3;
            if (((parley_wnd_block.parley_mode == 0xe) && (parley_wnd_block.parley_barter_want_kind == 3)) ||
               ((parley_wnd_block.parley_mode == 0xf && (parley_wnd_block.parley_demand_kind == 3)))) {
              ctrl_disable(parley_wnd_block.parley_request_done_button);
              ctrl_disable(parley_wnd_block.parley_request_origin_button);
              parley_draw_city_list(1);
            }
          }
          break;
        case 0xa6:
          net_msg_get_args((iptr)msg,&unit);
          if ((parley_wnd_block.parley_wnd_closed == 0) && ((*(uptr *)&parley_wnd_block.parley_other_civ) == unit)) {
            parley_wnd_block.parley_remote_cities_revealed = (byte)civ3;
            if (((parley_wnd_block.parley_mode == 0xe) && (parley_wnd_block.parley_barter_want_kind == 3)) ||
               ((parley_wnd_block.parley_mode == 0xf && (parley_wnd_block.parley_demand_kind == 3)))) {
              ctrl_enable(parley_wnd_block.parley_request_done_button);
              ctrl_enable(parley_wnd_block.parley_request_origin_button);
              parley_draw_city_list(1);
            }
          }
          break;
        case 0xa7:
          net_msg_get_args((iptr)msg,&unit);
          if ((parley_wnd_block.parley_wnd_closed == 0) && ((*(uptr *)&parley_wnd_block.parley_other_civ) == unit)) {
            parley_wnd_block.parley_remote_units_revealed = (byte)civ3;
            if (((parley_wnd_block.parley_mode == 0xe) && (parley_wnd_block.parley_barter_want_kind == 2)) ||
               ((parley_wnd_block.parley_mode == 0xf && (parley_wnd_block.parley_demand_kind == 2)))) {
              ctrl_disable(parley_wnd_block.parley_request_done_button);
              ctrl_disable(parley_wnd_block.parley_request_origin_button);
              ctrl_enable(parley_wnd_block.parley_sort_by_city_right);
              ctrl_enable(parley_wnd_block.parley_sort_by_unit_right);
              parley_draw_unit_list(1);
            }
          }
          break;
        case 0xa8:
          net_msg_get_args((iptr)msg,&unit);
          if ((parley_wnd_block.parley_wnd_closed == 0) && ((*(uptr *)&parley_wnd_block.parley_other_civ) == unit)) {
            parley_wnd_block.parley_remote_units_revealed = (byte)civ3;
            if (((parley_wnd_block.parley_mode == 0xe) && (parley_wnd_block.parley_barter_want_kind == 2)) ||
               ((parley_wnd_block.parley_mode == 0xf && (parley_wnd_block.parley_demand_kind == 2)))) {
              ctrl_enable(parley_wnd_block.parley_request_done_button);
              ctrl_enable(parley_wnd_block.parley_request_origin_button);
              ctrl_disable(parley_wnd_block.parley_sort_by_city_right);
              ctrl_disable(parley_wnd_block.parley_sort_by_unit_right);
              parley_sort_unit_list((WindowObjectView *)((i8 *)&parley_wnd_block.parley_wnd),0,parley_wnd_block.parley_list_count_right - 1,1);
              parley_draw_unit_list(1);
            }
          }
        }
        operator_delete(msg);
      }
      else {
        dbg_logf_int2((iptr)&str_poll_retrieved_non_civ_message_message_d,msg[1],msg[2]);
      }
    }
    if (((wait_mode == 0) && (*(char *)((int)&((NetSessionExt *)self)->session_flags + 2) != '\0')) && (gamelist_dirty != '\0'))
    {
      net_gamelist_refresh();
    }
    if (((wait_mode == 0) && (((NetSessionExt *)self)->popup_busy == 0)) && (net_popup_queue_head != 0)) {
      net_popup_queue_show_next();
    }
    *(int *)((NetSessionExt *)self)->process_depth = *(int *)((NetSessionExt *)self)->process_depth - 1;
  }
  return;
}

/* 00482337 auto */
void __cdecl net_game_xmit_wait_idle(void)

{
  net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
  if (net_session_block.nm_continue_after_join_count != 0) {
    net_session_block.dialog_stack_top[0xf] = net_session_block.dialog_stack_top[0xf] | 0x400;
    wnd_end_modal_loop((ModalMenuWindow *)(*net_session_block.dialog_stack_top + 0x48));
  }
  return;
}

/* 004823d6 auto */
void __cdecl net_msg_get_args(iptr msg,i32 *args)

{
  *args = *(i32 *)(msg + 0x10);
  args[1] = *(i32 *)(msg + 0x14);
  args[2] = *(i32 *)(msg + 0x18);
  args[3] = *(i32 *)(msg + 0x1c);
  args[4] = *(i32 *)(msg + 0x20);
  args[5] = *(i32 *)(msg + 0x24);
  args[6] = *(i32 *)(msg + 0x28);
  return;
}

/* 00482470 auto */
void __cdecl net_server_quit_wait_idle(void)

{
  int human_count;
  
  net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
  if (((net_session_block.net_players_awaited != 0) &&
      (human_count = bits_count8((uint)(game.human_players == '\0')), human_count == 0)) &&
     (1 < net_session_block.net_player_count[0])) {
    return;
  }
  net_session_block.dialog_stack_top[0xf] = net_session_block.dialog_stack_top[0xf] | 0x400;
  wnd_end_modal_loop((ModalMenuWindow *)(*net_session_block.dialog_stack_top + 0x48));
  return;
}

/* 004824e3 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl net_host_quit_handoff(void)

{
  byte sign;
  int human_count;
  int slot;
  
  net_session_block.net_host_handoff_stage = 1;
  net_drop_flagged_players();
  game.human_players = net_session_block.pending_human_players | game.human_players;
  net_session_block.pending_human_players = 0;
  if (1 < net_session_block.net_player_count[0]) {
    game.human_players = game.human_players & ~(byte)(1 << ((byte)(*(i8 *)&human_civ) & 0x1f));
    net_session_block.net_players_awaited = net_session_block.net_player_count[0] - 1;
    net_send_message(0xe,0xff,0,0,0,0,0,0,0,0);
    net_drop_flagged_players();
    dlg_pending_idle_callback = ((i8*)(net_server_quit_wait_idle));
    popup_game_sprite_flags((iptr)&str_serverquitwait,0x2000000,(iptr)&popup_info_icon_sprite,0);
    human_count = bits_count8((uint)(game.human_players == '\0'));
    if (human_count == 0) {
      net_send_message(0xf,0xff,0,0,0,0,0,0,0,0);
      sign = (byte)(net_session_block.mp_turn_civ + 1 >> 0x1f);
      civ_saved_cursor_x_block.saved_turn_civ = (((byte)(net_session_block.mp_turn_civ + 1) ^ sign) - sign & 7 ^ sign) - sign;
      for (slot = 1; (slot < 7 && ((((i8 *)&net_session_block.net_slot_active_flags))[slot * 0x54] == '\0'));
          slot = slot + 1) {
      }
      if (slot < 7) {
        crt_memcpy(((i8 *)&net_session_block.net_player_slots),((i8 *)&net_session_block.net_player_slots) + slot * 0x54,0x54);
        net_session_block.net_slot_host_flags[0] = 1;
        net_session_block.net_player_slots[0] = 0;
        net_session_block.net_civ_slots[0] = *(i32 *)(((i8 *)&net_session_block.net_civ_slots) + slot * 4);
        net_session_block.net_player_count[0]--;
        *(i32 *)(((i8 *)&net_session_block.net_civ_slots) + slot * 4) = 0xffffffff;
        _memset(((i8 *)&net_session_block.net_player_slots) + slot * 0x54,0,0x54);
        net_send_state_diff(0xff,2,0,1,0);
        net_send_message(0x16,0xff,0,0,0,0,0,0,0,0);
        net_send_message(4,0xff,0,0,0,0,0,0,0,0);
        XD_FlushSendBuffer(60000);
      }
    }
  }
  return;
}

/* 00482724 auto */
void __cdecl net_client_quit_wait_idle(void)

{
  net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
  if (net_session_block.net_host_handoff_stage == 2) {
    net_session_block.dialog_stack_top[0xf] = net_session_block.dialog_stack_top[0xf] | 0x400;
    wnd_end_modal_loop((ModalMenuWindow *)(*net_session_block.dialog_stack_top + 0x48));
  }
  return;
}

/* 0048276d auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl net_quit_wait_start_civ_idle(void)

{
  int now;
  
  net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
  if ((net_session_block.nm_start_civ_count == 0) &&
     (now = timer_ticks(), now - map_views_block.net_handoff_wait_ticks_i32 <= net_session_block.net_timeout_seconds * 0x3c)) {
    return;
  }
  net_session_block.dialog_stack_top[0xf] = net_session_block.dialog_stack_top[0xf] | 0x400;
  wnd_end_modal_loop((ModalMenuWindow *)(*net_session_block.dialog_stack_top + 0x48));
  return;
}

/* 004827d5 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl net_quit_wait_player_list_idle(void)

{
  int now;
  
  net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
  if ((net_session_block.nm_player_list_count == 0) &&
     (now = timer_ticks(), now - map_views_block.net_handoff_wait_ticks_i32 <= net_session_block.net_timeout_seconds * 0x3c)) {
    return;
  }
  net_session_block.dialog_stack_top[0xf] = net_session_block.dialog_stack_top[0xf] | 0x400;
  wnd_end_modal_loop((ModalMenuWindow *)(*net_session_block.dialog_stack_top + 0x48));
  return;
}

/* 0048283d auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl net_quit_wait_players_idle(void)

{
  int now;
  
  net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
  if ((net_session_block.net_players_awaited != 0) &&
     (now = timer_ticks(), now - map_views_block.net_handoff_wait_ticks_i32 <= net_session_block.net_timeout_seconds * 0x3c)) {
    return;
  }
  net_session_block.dialog_stack_top[0xf] = net_session_block.dialog_stack_top[0xf] | 0x400;
  wnd_end_modal_loop((ModalMenuWindow *)(*net_session_block.dialog_stack_top + 0x48));
  return;
}

/* 004828a5 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __cdecl net_client_transfer_server(void)

{
  char transport_ok;
  i32 result;
  int cmp;
  int slot;
  int old_slot;
  struct { int slots[2]; char addresses[76]; int civ_ids[135]; } saved;  /* a copy of the player table */
  int status;
  int slot_civ;
  
  net_session_block.nm_server_quit_count_i32 = 0;
  net_session_block.nm_start_civ_count = 0;
  net_session_block.nm_player_list_count = 0;
  net_send_message(0x10,0,0,0,0,0,0,0,0,0);
  dlg_pending_idle_callback = ((i8*)(net_client_quit_wait_idle));
  popup_game_sprite_flags((iptr)&str_clientquitwait,0x2000000,(iptr)&popup_info_icon_sprite,0);
  net_session_block.net_host_handoff_stage = 0;
  dlg_pending_idle_callback = ((i8*)(net_quit_wait_start_civ_idle));
  map_views_block.net_handoff_wait_ticks_i32 = timer_ticks();
  popup_game_sprite_flags((iptr)&str_clientquitwait_2,0x2000000,(iptr)&popup_info_icon_sprite,0);
  if (net_session_block.nm_start_civ_count == 0) {
    dbg_log((iptr)&str_clienttransferserver_waiting_for_nm_star);
    crt_strcpy(((i8 *)&minimap_window_block.text_string_args),net_session_block.net_connection_title);
    popup_game_with_sprite((iptr)&str_lanconnectfail_3,(iptr)&popup_info_icon_sprite,0);
    player_turn_active = 0;
    game_loop_active = 0;
    result = 0;
  }
  else {
    turn_resume_civ = civ_saved_cursor_x_block.saved_turn_civ;
    dlg_pending_idle_callback = ((i8*)(net_quit_wait_player_list_idle));
    map_views_block.net_handoff_wait_ticks_i32 = timer_ticks();
    popup_game_sprite_flags((iptr)&str_clientquitwait_3,0x2000000,(iptr)&popup_info_icon_sprite,0);
    if (net_session_block.nm_player_list_count == 0) {
      dbg_log((iptr)&str_clienttransferserver_waiting_for_nm_play);
      crt_strcpy(((i8 *)&minimap_window_block.text_string_args),net_session_block.net_connection_title);
      popup_game_with_sprite((iptr)&str_lanconnectfail_4,(iptr)&popup_info_icon_sprite,0);
      player_turn_active = 0;
      game_loop_active = 0;
      result = 0;
    }
    else {
      crt_memcpy(&saved,((iptr *)&net_session_block.net_player_count),0x270);
      cmp = _strcmp(((i8 *)&prefs_main_menu_choice_block.prefs_net_ip_address),((i8 *)&net_session_block.net_slot_addresses));
      if (cmp == 0) {
        dbg_log((iptr)&str_clienttransferserver_disconnecting_from);
        net_session_shutdown(((iptr *)&net_session_block.net_session),0);
        transport_ok = net_init_transport(((iptr *)&net_session_block.net_session),net_session_block.net_protocol,1);
        status = (int)transport_ok;
        if (status == 0) {
          dbg_log((iptr)&str_clienttransferserver_could_not_reconnect);
          crt_strcpy(((i8 *)&minimap_window_block.text_string_args),net_session_block.net_connection_title);
          popup_game_with_sprite((iptr)&str_lanconnectfail_5,(iptr)&popup_info_icon_sprite,0);
          game_loop_active = 0;
          player_turn_active = 0;
          return 0;
        }
        dbg_log((iptr)&str_reconnected_to_network_as_server);
        crt_strcpy(((i8 *)&net_session_block.net_server_address),((i8 *)&prefs_main_menu_choice_block.prefs_net_ip_address));
        net_session_block.net_server_conn_id = 0;
        net_session_block.net_local_slot = 0;
        map_views_block.diffeng_mirror_end = (*(int *)&map_views_block.diffeng_mirror_size) + diffeng_mirror_buf;
        net_session_block.net_players_awaited = saved.slots[0] - 1;
        net_session_block.net_players_awaited_initial = net_session_block.net_players_awaited;
        if (net_session_block.net_players_awaited < 1) {
          slot_civ = saved.civ_ids[0];
          *(i32 *)(((i8 *)&net_session_block.net_civ_slots) + saved.civ_ids[0] * 4) = 0;
          net_session_block.net_slot_civs[0] = saved.civ_ids[0];
        }
        else {
          dlg_pending_idle_callback = ((i8*)(net_quit_wait_players_idle));
          map_views_block.net_handoff_wait_ticks_i32 = timer_ticks();
          popup_game_sprite_flags((iptr)&str_clientquitwait_4,0x2000000,(iptr)&popup_info_icon_sprite,0);
          cmp = timer_ticks();
          if ((net_session_block.net_timeout_seconds * 0x3c < cmp - map_views_block.net_handoff_wait_ticks_i32) && (net_session_block.net_players_awaited != 0)) {
            crt_strcpy(((i8 *)&minimap_window_block.text_string_args),net_session_block.net_connection_title);
            if (net_session_block.net_players_awaited == net_session_block.net_players_awaited_initial) {
              popup_game_with_sprite((iptr)&str_nooneshowed,(iptr)&popup_info_icon_sprite,0);
              game_loop_active = 0;
              player_turn_active = 0;
              return 0;
            }
            popup_game_with_sprite((iptr)&str_someshowed,(iptr)&popup_info_icon_sprite,0);
          }
          for (slot = 0; slot < 7; slot++) {
            if ((((i8 *)&net_session_block.net_slot_active_flags))[slot * 0x54] != '\0') {
              old_slot = 0;
              while ((old_slot < 7 &&
                     (cmp = _strcmp(saved.addresses + old_slot * 0x54,
                                      ((i8 *)&net_session_block.net_slot_addresses) + slot * 0x54), cmp != 0))) {
                old_slot++;
              }
              if (6 < old_slot) {
                err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_oldindex_max_net_players,(iptr)&str_d_ss_franklinton_netmgr_poll_cpp_5,0x8a7);
              }
              slot_civ = saved.civ_ids[old_slot * 0x15];
              *(int *)(((i8 *)&net_session_block.net_civ_slots) + slot_civ * 4) = slot;
              (((i32 *)&net_session_block.net_slot_civs))[slot * 0x15] = slot_civ;
            }
          }
          net_session_block.mp_simultaneous_moves = (i8)(*(i8 *)&civ_saved_cursor_x_block.mp_simultaneous_setting);
          net_send_message(0x33,0xff,(int)civ_saved_cursor_x_block.mp_double_production,(int)civ_saved_cursor_x_block.mp_double_moves,(int)(*(i8 *)&civ_saved_cursor_x_block.mp_simultaneous_setting),0,0,0,0
                             ,0);
          net_send_message(4,0xff,0,0,0,0,0,0,0,0);
          XD_FlushSendBuffer(60000);
        }
        _memset(((i8 *)&net_map_lock_slots_block.net_map_lock_slots),-1,0xc0);
        net_session_block.net_session_phase = 3;
        net_reset_error_counts();
        net_session_block.nm_server_quit_count_i32 = 0;
        net_session_block.nm_start_civ_count = 0;
        net_session_block.nm_player_list_count = 0;
        if (game_over_reason != 2) {
          popup_game_with_sprite((iptr)&str_hostchangeserver,(iptr)&popup_info_icon_sprite,0);
        }
      }
      else {
        dbg_logf_str((iptr)&str_disconnecting_from_server_s,(iptr)&net_session_block.net_server_address);
        status = XD_CloseConnection();
        if (status != 0) {
          dbg_logf_str_int((iptr)&str_clienttransferserver_disconnection_from,(iptr)&net_session_block.net_server_address,status);
          crt_strcpy(((i8 *)&minimap_window_block.text_string_args),net_session_block.net_connection_title);
          popup_game_with_sprite((iptr)&str_lanconnectfail_6,(iptr)&popup_info_icon_sprite,0);
          game_loop_active = 0;
          player_turn_active = 0;
          return 0;
        }
        crt_strcpy(((i8 *)&net_session_block.net_server_address),((i8 *)&net_session_block.net_slot_addresses));
        map_views_block.net_handoff_wait_ticks_i32 = timer_ticks();
        do {
          cmp = timer_ticks();
        } while (cmp - map_views_block.net_handoff_wait_ticks_i32 < 0x3c);
        dbg_logf_str((iptr)&str_attempting_to_reconnect_to_new_server_s,(iptr)&net_session_block.net_server_address);
        status = XD_OpenConnection(((i8 *)&net_session_block.net_server_address),net_session_block.net_timeout_seconds * 1000);
        if (status < 0) {
          dbg_logf((iptr)&str_connecttogame_open_connection_failed_err,status);
          crt_strcpy(((i8 *)&minimap_window_block.text_string_args),net_session_block.net_connection_title);
          popup_game_with_sprite((iptr)&str_serverconnectfail_2,(iptr)&popup_info_icon_sprite,0);
          game_loop_active = 0;
          player_turn_active = 0;
          return 0;
        }
        dbg_log((iptr)&str_connection_to_new_server_successful);
        net_session_block.nm_server_quit_count_i32 = 0;
        net_session_block.nm_start_civ_count = 0;
        dlg_pending_idle_callback = ((i8*)(net_quit_wait_player_list_idle));
        map_views_block.net_handoff_wait_ticks_i32 = timer_ticks();
        popup_game_sprite_flags((iptr)&str_clientquitwait_5,0x2000000,(iptr)&popup_info_icon_sprite,0);
        if (net_session_block.nm_player_list_count == 0) {
          dbg_log((iptr)&str_clienttransferserver_client_timed_out_wa);
          crt_strcpy(((i8 *)&minimap_window_block.text_string_args),net_session_block.net_connection_title);
          popup_game_with_sprite((iptr)&str_lanconnectfail_7,(iptr)&popup_info_icon_sprite,0);
          game_loop_active = 0;
          player_turn_active = 0;
          return 0;
        }
        crt_strcpy(((i8 *)&minimap_window_block.text_string_args),((i8 *)&net_session_block.net_slot_player_names));
        net_reset_error_counts();
        net_session_block.nm_player_list_count = 0;
        popup_game_with_sprite((iptr)&str_hostchangeclient,(iptr)&popup_info_icon_sprite,0);
      }
      result = 1;
    }
  }
  return result;
}

/* 0048bf51 auto */
void __cdecl net_client_hot_wait_idle(void)

{
  net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
  net_heartbeat_check(net_session_block.net_slot_civs[0]);
  if ((((net_session_block.nm_start_civ_count != 0) || (net_session_block.net_host_handoff_stage != '\0')) || (net_session_block.nm_end_sequence_count != 0)) ||
     (((net_session_block.player_has_quit != '\0' || (game_loop_active == '\0')) || (net_session_block.net_lost_conn_total != 0)))) {
    net_session_block.dialog_stack_top[0xf] = net_session_block.dialog_stack_top[0xf] | 0x400;
    wnd_end_modal_loop((ModalMenuWindow *)(*net_session_block.dialog_stack_top + 0x48));
  }
  return;
}

/* 0048d9ad auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl net_heartbeat_send(iptr civ)

{
  if (net_session_block.net_drag_hold == '\0') {
    net_session_block.nm_heartbeat_ack_count = 0;
    net_send_message(0x2b,*(i32 *)
                             (((i8 *)&net_session_block.net_player_slots) + *(int *)(((i8 *)&net_session_block.net_civ_slots) + civ * 4) * 0x54),0,0,0,0,
                       0,0,0,0);
  }
  else {
    net_session_block.nm_heartbeat_ack_count = 1;
  }
  if ((parley_wnd_block.parley_wnd_closed == 1) && (net_popup_queue_head == 0)) {
    mp_meeting_pending = 0;
    net_session_block.nm_parley_cancel_count = 0;
  }
  map_views_block.net_heartbeat_last_tick_i32 = timer_ticks();
  return;
}

/* 0048da51 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl net_heartbeat_check(iptr civ)

{
  int now;
  
  now = timer_ticks();
  if (0xe0f < now - map_views_block.net_heartbeat_last_tick_i32) {
    if (net_session_block.nm_heartbeat_ack_count == 0) {
      *(int *)(((i8 *)&net_session_block.net_civ_turn_ended) + civ * 4) = *(int *)(((i8 *)&net_session_block.net_civ_turn_ended) + civ * 4) + 1;
      if (net_session_block.net_host_flag == '\0') {
        net_session_block.net_lost_conn_total++;
      }
    }
    else {
      net_heartbeat_send(civ);
    }
  }
  return;
}

/* 0048dab9 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __cdecl net_check_lost_connections(void)

{
  int slot_civ;
  bool no_player;
  int civ;
  int dropped_count;
  int lost_counts[7];
  iptr slot;
  
  if (net_session_block.net_host_flag == '\0') {
    if (net_session_block.net_lost_conn_total != 0) {
      game_loop_active = 0;
      dbg_log((iptr)&str_we_lost_connection_to_the_server_heartbe);
      net_session_shutdown(((iptr *)&net_session_block.net_session),1);
      popup_game_with_sprite((iptr)&str_lostserver,(iptr)&popup_info_icon_sprite,0);
      return 1;
    }
  }
  else {
    dropped_count = net_drop_flagged_players();
    for (civ = 1; civ < 8; civ++) {
      no_player = true;
      if (((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0) &&
         ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) {
        for (slot = 0; slot < 7; slot++) {
          if (((((i8 *)&net_session_block.net_slot_active_flags))[slot * 0x54] != '\0') &&
             ((((i32 *)&net_session_block.net_slot_civs))[slot * 0x15] == civ)) {
            no_player = false;
            break;
          }
        }
        if (no_player) {
          game.human_players = game.human_players & ~(byte)(1 << ((byte)civ & 0x1f));
          if ((1 << ((byte)civ & 0x1f) & (int)(short)(*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask)) != 0) {
            (*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask) = (*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask) & ~(ushort)(1 << ((byte)civ & 0x1f));
            net_send_message(0x2a,0xff,(int)(short)(*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask),0,0,0,0,0,0,0);
            net_session_block.nm_lock_nation_count_i32++;
          }
          dropped_count++;
        }
      }
    }
    if (net_session_block.net_lost_conn_total != 0) {
      crt_memcpy(lost_counts,((i8 *)&net_session_block.net_lost_conn_by_player),0x1c);
      net_reset_error_counts();
      for (slot = 1; slot < 7; slot++) {
        if ((0 < lost_counts[slot]) && ((((i8 *)&net_session_block.net_slot_active_flags))[slot * 0x54] != '\0')) {
          dropped_count++;
          slot_civ = (((i32 *)&net_session_block.net_slot_civs))[slot * 0x15];
          text_set_string_arg(0,(iptr)(((i8 *)&net_session_block.net_slot_player_names) + slot * 0x54));
          net_send_text_args(0x53,0xff,1,0,0,0);
          *(i32 *)(((i8 *)&net_session_block.net_civ_drop_requested) + slot_civ * 4) = 0;
          (*(i8 *)((char *)&civ + 0)) = (byte)slot_civ;
          game.human_players = game.human_players & ~(byte)(1 << ((byte)civ & 0x1f));
          net_remove_player
                    ((NetSession *)((iptr *)&net_session_block.net_session),*(i32 *)(((i8 *)&net_session_block.net_player_slots) + slot * 0x54));
          if ((1 << ((byte)civ & 0x1f) & (int)(short)(*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask)) != 0) {
            (*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask) = (*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask) & ~(ushort)(1 << ((byte)civ & 0x1f));
            net_send_message(0x2a,0xff,(int)(short)(*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask),0,0,0,0,0,0,0);
            net_session_block.nm_lock_nation_count_i32++;
          }
          popup_game_with_sprite((iptr)&str_lostclient,(iptr)&popup_info_icon_sprite,0);
        }
      }
    }
    if (dropped_count != 0) {
      net_session_block.net_player_count[0] = 0;
      for (slot = 0; slot < 7; slot++) {
        if ((((i8 *)&net_session_block.net_slot_active_flags))[slot * 0x54] != '\0') {
          net_session_block.net_player_count[0]++;
        }
      }
      net_send_message(4,0xff,0,0,0,0,0,0,0,0);
      net_send_state_diff(0xff,2,0,0,1);
    }
  }
  return 0;
}

/* 0048de75 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl net_drop_flagged_players(void)

{
  int slot_civ;
  byte civ_bit;
  int dropped_count;
  int slot;
  
  dropped_count = 0;
  for (slot = 1; slot < 7; slot++) {
    if (((((i8 *)&net_session_block.net_slot_active_flags))[slot * 0x54] != '\0') &&
       (*(int *)(((i8 *)&net_session_block.net_civ_drop_requested) + (((i32 *)&net_session_block.net_slot_civs))[slot * 0x15] * 4) != 0)) {
      dropped_count++;
      slot_civ = (((i32 *)&net_session_block.net_slot_civs))[slot * 0x15];
      *(i32 *)(((i8 *)&net_session_block.net_civ_drop_requested) + slot_civ * 4) = 0;
      *(i32 *)(((i8 *)&net_session_block.net_lost_conn_by_player) + *(int *)(((i8 *)&net_session_block.net_player_slots) + slot * 0x54) * 4) = 0;
      civ_bit = (byte)slot_civ;
      game.human_players = game.human_players & ~(byte)(1 << (civ_bit & 0x1f));
      net_remove_player
                ((NetSession *)((iptr *)&net_session_block.net_session),*(i32 *)(((i8 *)&net_session_block.net_player_slots) + slot * 0x54));
      if ((1 << (civ_bit & 0x1f) & (int)(short)(*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask)) != 0) {
        (*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask) = (*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask) & ~(ushort)(1 << (civ_bit & 0x1f));
        net_session_block.nm_lock_nation_count_i32++;
      }
    }
  }
  if (dropped_count != 0) {
    net_send_message(0x2a,0xff,(int)(short)(*(ushort *)&civ_saved_cursor_x_block.net_claimed_civs_mask),0,0,0,0,0,0,0);
    net_send_message(4,0xff,0,0,0,0,0,0,0,0);
  }
  return dropped_count;
}

/* 004923f0 auto */
void __cdecl chat_insert_macro_text(Control *edit,i32 macro_id)

{
  bool all_contact;
  int civ;
  iptr name2;
  size_t text_len;
  int tries;
  
  text_clear();
  tries = 0;
  if (((game.wonder_city[0x18] == -1) && (civ = civ_has_wonder(human_civ[0],9), civ == 0))
     && (game.reveal_map == '\0')) {
    all_contact = false;
  }
  else {
    all_contact = true;
  }
  switch(macro_id) {
  case 0x2b0:
    while (((((civ = chat_macro_next_adj_civ, tries < 8 && (human_civ[0] != chat_macro_next_adj_civ)) && (!all_contact))
            && ((civ_saved_cursor_x_block.mp_chat_from_start == 0 ||
                ((1 << ((byte)chat_macro_next_adj_civ & 0x1f) & (uint)game.human_players) == 0)))) &&
           ((*(byte *)&civs[chat_macro_next_adj_civ].treaties[human_civ[0]] & 1) == 0))) {
      tries++;
      chat_macro_next_adj_civ++;
      if (chat_macro_next_adj_civ == 8) {
        chat_macro_next_adj_civ = 1;
      }
    }
    if (tries == 8) {
      return;
    }
    chat_macro_next_adj_civ++;
    name2 = civ_adjective(civ);
    text_append(name2);
    text_append_space();
    if (chat_macro_next_adj_civ == 8) {
      chat_macro_next_adj_civ = 1;
    }
    goto replace_selection;
  case 0x2b1:
    while ((((tries < 8 && (human_civ[0] != chat_macro_next_leader_civ)) &&
            ((!all_contact &&
             ((civ_saved_cursor_x_block.mp_chat_from_start == 0 ||
              ((1 << ((byte)chat_macro_next_leader_civ & 0x1f) & (uint)game.human_players) == 0)))))) &&
           ((*(byte *)&civs[chat_macro_next_leader_civ].treaties[human_civ[0]] & 1) == 0))) {
      tries++;
      chat_macro_next_leader_civ++;
      if (chat_macro_next_leader_civ == 8) {
        chat_macro_next_leader_civ = 1;
      }
    }
    if (tries == 8) {
      return;
    }
    name2 = civ_leader_title(chat_macro_next_leader_civ);
    text_append(name2);
    text_append_space();
    civ = chat_macro_next_leader_civ;
    chat_macro_next_leader_civ++;
    name2 = civ_leader_name(civ);
    text_append(name2);
    text_append_space();
    if (chat_macro_next_leader_civ == 8) {
      chat_macro_next_leader_civ = 1;
    }
    goto replace_selection;
  case 0x2b2:
    chat_read_macro_line((iptr)&str_chatmac1_txt,(iptr)&chat_macro1_file_offset);
    civ = chat_macro1_file_offset;
    break;
  case 0x2b3:
    chat_read_macro_line((iptr)&str_chatmac2_txt,(iptr)&chat_macro2_file_offset);
    civ = chat_macro2_file_offset;
    break;
  case 0x2b4:
    chat_read_macro_line((iptr)&str_chatmac3_txt,(iptr)&chat_macro3_file_offset);
    civ = chat_macro3_file_offset;
    break;
  default:
    goto replace_selection;
  }
  if (civ == 0) {
    return;
  }
replace_selection:
  edit_replace_sel(edit,(iptr)&map_views_block.text_buffer);
  civ = edit_get_sel_end((EditSelEndView *)edit);
  text_len = _strlen(((i8 *)&map_views_block.text_buffer));
  edit_set_sel((EditSelView *)edit,civ - text_len,civ);
  return;
}

/* 0049275a auto */
void __cdecl chat_read_macro_line(iptr path,iptr file_offset)

{
  int ok;
  size_t line_len;
  i8 file[160];
  i32 unwind_state;
  
  unwind_state = 0xffffffff;
  file_obj_init((FileObject *)file);
  unwind_state = 0;
  ok = file_obj_open((FileObject *)file,path);
  if (ok == 0) {
    *(i32 *)file_offset = 0;
    unwind_state = 0xffffffff;
    /* inlined unwind funclet 00492868 */ { file_obj_close((FileObject *)((iptr)&file)); }
  }
  else {
    ok = file_obj_get_size((FileObject *)file);
    if (ok <= *(int *)file_offset) {
      *(i32 *)file_offset = 0;
    }
    ok = file_obj_seek_cur((FileSeekView *)file,*(i32 *)file_offset);
    if (ok == 0) {
      *(i32 *)file_offset = 0;
      file_map_close((FileObject *)file);
      unwind_state = 0xffffffff;
      /* inlined unwind funclet 00492868 */ { file_obj_close((FileObject *)((iptr)&file)); }
    }
    else {
      file_obj_read_line((FileReadLineView *)file,(iptr)&map_views_block.text_buffer,0x100);
      file_map_close((FileObject *)file);
      line_len = _strlen(((i8 *)&map_views_block.text_buffer));
      *(size_t *)file_offset = *(int *)file_offset + line_len + 2;
      unwind_state = 0xffffffff;
      /* inlined unwind funclet 00492868 */ { file_obj_close((FileObject *)((iptr)&file)); }
    }
  }
  return;
}

/* 004af3e0 auto */
void __thiscall parley_build_civ_list(ListPaneWindow *self,iptr rect,int side)

{
  u8 *field;
  int has_wonder;
  int scroll_width;
  Control *new_ctrl;
  u8 *hotspot_parent;
  u8 *scroll_parent;
  i32 hotspot;
  i32 scrollbar;
  u32 other_civ;
  RECT rect2;
  int all_contact;
  i32 seh_prev;
  i8 *seh_handler;
  i32 unwind_state;
  
  unwind_state = 0xffffffff;
  rect2.left = *(int *)rect;
  rect2.top = *(i32 *)(rect + 4);
  rect2.right = *(int *)(rect + 8);
  rect2.bottom = *(i32 *)(rect + 0xc);
  if (game.wonder_city[0x18] == -1) {
    has_wonder = civ_has_wonder(human_civ[0],9);
    if ((has_wonder == 0) && (game.reveal_map == '\0')) {
      all_contact = 0;
      goto reset_contact_field;
    }
  }
  all_contact = 1;
reset_contact_field:
  field = ((PediaRedrawView *)self)->pedia_pane_layout + side * 4 + 0x4c;
  field[0] = '\0';
  field[1] = '\0';
  field[2] = '\0';
  field[3] = '\0';
  for (other_civ = 1; (int)other_civ < 8; other_civ++) {
    if (((human_civ[0] != other_civ) && (self->caption_height != other_civ)) &&
       ((all_contact != 0 || ((*(byte *)&civs[human_civ[0]].treaties[other_civ] & 1) != 0))))
    {
      *(u32 *)(side * 0x2004 + *(int *)(((PediaRedrawView *)self)->pedia_pane_layout + side * 4 + 0x4c) * 4 + 0x3f0 +
              (int)self) = other_civ;
      *(i32 *)
       (side * 0x2004 + *(int *)(((PediaRedrawView *)self)->pedia_pane_layout + side * 4 + 0x4c) * 4 + 0x8400 + (int)self) =
           0;
      *(int *)(((PediaRedrawView *)self)->pedia_pane_layout + side * 4 + 0x4c) =
           *(int *)(((PediaRedrawView *)self)->pedia_pane_layout + side * 4 + 0x4c) + 1;
    }
  }
  if (*(int *)(((PediaRedrawView *)self)->pedia_pane_layout + side * 4 + 0x4c) < 1) {
    field = ((PictureWindow *)self)->parley_pane_arrays_base + side * 4 + 0x30;
    field[0] = 0xff;
    field[1] = 0xff;
    field[2] = 0xff;
    field[3] = 0xff;
  }
  else {
    field = ((PictureWindow *)self)->parley_pane_arrays_base + side * 4 + 0x30;
    field[0] = '\0';
    field[1] = '\0';
    field[2] = '\0';
    field[3] = '\0';
  }
  field = ((PediaRedrawView *)self)->pedia_pane_layout + side * 4 + 0x44;
  field[0] = 2;
  field[1] = '\0';
  field[2] = '\0';
  field[3] = '\0';
  *(i32 *)(((PediaRedrawView *)self)->pedia_pane_layout + side * 0x10 + 0x24) = *(i32 *)rect;
  *(i32 *)(((PediaRedrawView *)self)->pedia_pane_layout + side * 0x10 + 0x28) = *(i32 *)(rect + 4);
  *(i32 *)(((PediaRedrawView *)self)->pedia_pane_layout + side * 0x10 + 0x2c) = *(i32 *)(rect + 8);
  *(i32 *)(((PediaRedrawView *)self)->pedia_pane_layout + side * 0x10 + 0x30) = *(i32 *)(rect + 0xc);
  if (*(int *)(((PictureWindow *)self)->parley_pane_arrays_base + side * 4 + 0x40) <
      *(int *)(((PediaRedrawView *)self)->pedia_pane_layout + side * 4 + 0x4c)) {
    scroll_width = GetSystemMetrics(2);
    has_wonder = rect2.right;
    *(int *)(((PediaRedrawView *)self)->pedia_pane_layout + side * 0x10 + 0x2c) =
         *(int *)(((PediaRedrawView *)self)->pedia_pane_layout + side * 0x10 + 0x2c) - scroll_width;
    rect2.left = GetSystemMetrics(2);
    rect2.left = has_wonder - rect2.left;
    new_ctrl = operator_new(0x40);
    unwind_state = 0;
    if (new_ctrl == (Control *)0x0) {
      scrollbar = 0;
    }
    else {
      scrollbar = scrollbar_ctor(new_ctrl);
    }
    unwind_state = 0xffffffff;
    *(i32 *)(((PediaRedrawView *)self)->pedia_pane_layout + side * 4 - 0x20) = scrollbar;
    if (self == (ListPaneWindow *)0x0) {
      scroll_parent = (u8 *)0x0;
    }
    else {
      scroll_parent = self->window_2;
    }
    scrollbar_create
              (*(Control **)(((PediaRedrawView *)self)->pedia_pane_layout + side * 4 - 0x20),(iptr)scroll_parent,
               side + 0x40d,(iptr)&rect2,1);
    scrollbar_set_range
              (*(Control **)(((PediaRedrawView *)self)->pedia_pane_layout + side * 4 - 0x20),0,
               *(int *)(((PediaRedrawView *)self)->pedia_pane_layout + side * 4 + 0x4c) -
               *(int *)(((PictureWindow *)self)->parley_pane_arrays_base + side * 4 + 0x40));
    scrollbar_set_pos(*(ClickControl **)(((PediaRedrawView *)self)->pedia_pane_layout + side * 4 - 0x20),0);
    scrollbar_set_page_size
              (*(Control **)(((PediaRedrawView *)self)->pedia_pane_layout + side * 4 - 0x20),
               *(i32 *)(((PictureWindow *)self)->parley_pane_arrays_base + side * 4 + 0x40));
    scrollbar_set_callback
              (*(Control **)(((PediaRedrawView *)self)->pedia_pane_layout + side * 4 - 0x20),
               (iptr)(((void *)(iptr)parley_civ_list_scroll_local) + ((side == 0) - 1 & 0xb3b)));
    scrollbar_set_track_callback
              (*(ScrollbarTrackSetView **)(((PediaRedrawView *)self)->pedia_pane_layout + side * 4 - 0x20),
               (iptr)(((void *)(iptr)parley_civ_list_scroll_local) + ((side == 0) - 1 & 0xb3b)));
  }
  new_ctrl = operator_new(0x40);
  unwind_state = 1;
  if (new_ctrl == (Control *)0x0) {
    hotspot = 0;
  }
  else {
    hotspot = hotspot_ctor(new_ctrl);
  }
  unwind_state = 0xffffffff;
  *(i32 *)(((PediaRedrawView *)self)->pedia_pane_layout + side * 4 - 0x18) = hotspot;
  if (self == (ListPaneWindow *)0x0) {
    hotspot_parent = (u8 *)0x0;
  }
  else {
    hotspot_parent = self->window_2;
  }
  hotspot_create
            (*(ClickControl **)(((PediaRedrawView *)self)->pedia_pane_layout + side * 4 - 0x18),(iptr)hotspot_parent,
             side + 0x40f,(iptr)(((PediaRedrawView *)self)->pedia_pane_layout + side * 0x10 + 0x24));
  hotspot_set_click_callback(*(HotspotClickSetView **)(((PediaRedrawView *)self)->pedia_pane_layout + side * 4 - 0x18),(iptr)parley_civ_list_click);
  hotspot_set_dblclick_callback(*(HotspotDblClickSetView **)(((PediaRedrawView *)self)->pedia_pane_layout + side * 4 - 0x18),(iptr)parley_civ_list_click);
  parley_draw_civ_list(side);
  return;
}

/* 004af867 auto */
void __cdecl parley_civ_list_scroll_local(i32 pos)

{
  parley_civ_list_scroll(0,pos);
  return;
}

/* 004af8a3 auto */
void __cdecl parley_civ_list_scroll(int side,i32 pos)

{
  int active;
  iptr wnd2;
  
  active = wnd_get_active_child();
  if (active == 0) {
    wnd2 = 0;
  }
  else {
    wnd2 = active - 0x48;
  }
  wnd_activate((Wnd *)(wnd2 + 0x48));
  *(i32 *)(wnd2 + 0x10410 + side * 4) = pos;
  parley_draw_civ_list(side);
  return;
}

/* 004af904 auto */
void __cdecl parley_civ_list_click(int ctrl_id)

{
  uint *sel_flag;
  int row;
  int key_down;
  int range_end;
  int i;
  i32 cursor_y;
  i32 cursor_x;
  int side;
  iptr wnd2;
  
  row = wnd_get_active_child();
  if (row == 0) {
    wnd2 = 0;
  }
  else {
    wnd2 = row - 0x48;
  }
  wnd_activate((Wnd *)(wnd2 + 0x48));
  side = ctrl_id - 0x40f;
  wnd_get_cursor_pos
            ((WndBase *)(wnd2 + 0x48),(iptr)&cursor_x,(iptr)&cursor_y);
  if (((*(int *)(wnd2 + 1000 + side * 4) != 0) &&
      (row = parley_civ_list_hit_test(cursor_x,cursor_y,side), -1 < row)) &&
     (row < *(int *)(wnd2 + 1000 + side * 4))) {
    key_down = wnd_is_shift_down((void *)(wnd2 + 0x48));
    if (key_down == 0) {
      key_down = wnd_is_ctrl_down((void *)(wnd2 + 0x48));
      if (key_down == 0) {
        for (i = 0; i < *(int *)(wnd2 + 1000 + side * 4);
            i = i + 1) {
          if (i != row) {
            *(i32 *)(i * 4 + side * 0x2004 + 0x8400 + wnd2) = 0;
          }
        }
        *(int *)(wnd2 + 0x10418 + side * 4) = row;
        sel_flag = (uint *)(row * 4 + side * 0x2004 + 0x8400 + wnd2);
        *sel_flag = *sel_flag ^ 1;
      }
      else {
        *(int *)(wnd2 + 0x10418 + side * 4) = row;
        sel_flag = (uint *)(row * 4 + side * 0x2004 + 0x8400 + wnd2);
        *sel_flag = *sel_flag ^ 1;
      }
    }
    else {
      for (i = 0; i < *(int *)(wnd2 + 1000 + side * 4); i++)
      {
        *(i32 *)(i * 4 + side * 0x2004 + 0x8400 + wnd2) = 0;
      }
      if (*(int *)(wnd2 + 0x10418 + side * 4) < row) {
        i = *(int *)(wnd2 + 0x10418 + side * 4);
        range_end = row;
      }
      else {
        range_end = *(int *)(wnd2 + 0x10418 + side * 4);
        i = row;
      }
      for (; i <= range_end; i++) {
        *(i32 *)(i * 4 + side * 0x2004 + 0x8400 + wnd2) = 1;
      }
    }
    parley_draw_civ_list(side);
  }
  return;
}

/* 004afb77 auto */
int __cdecl parley_civ_list_hit_test(int x,int y,int side)

{
  iptr active;
  int row;
  int list_height;
  iptr wnd2;
  
  active = wnd_get_active_child();
  if (active == 0) {
    wnd2 = 0;
  }
  else {
    wnd2 = active - 0x48;
  }
  if (y < *(int *)(side * 0x10 + 0x3c4 + wnd2)) {
    row = -1;
  }
  else if (y < *(int *)(side * 0x10 + 0x3cc + wnd2)) {
    if (x < *(int *)(side * 0x10 + 0x3c0 + wnd2)) {
      row = -3;
    }
    else if (x < *(int *)(side * 0x10 + 0x3c8 + wnd2)) {
      row = *(int *)(side * 0x10 + 0x3c4 + wnd2);
      list_height = rect_height(side * 0x10 + wnd2 + 0x3c0);
      row = (y - row) / (list_height / *(int *)(wnd2 + 0x10420 + side * 4)) +
              *(int *)(wnd2 + 0x10410 + side * 4);
    }
    else {
      row = -4;
    }
  }
  else {
    row = -2;
  }
  return row;
}

/* 004afc89 auto */
void __cdecl parley_draw_civ_list(int side)

{
  u8 *field;
  int xLeft;
  int selected;
  iptr active;
  int list_width;
  int text_dy;
  int row_top;
  int text_dx;
  i32 font_height;
  iptr text;
  i32 bg_color2;
  int row;
  int shadow_color2;
  int text_color2;
  ViewWindow *wnd2;
  tagRECT row_rect;
  int row_height;
  i8 saved_clip[16];
  GameFont *font2;
  
  active = wnd_get_active_child();
  if (active == 0) {
    wnd2 = (ViewWindow *)0x0;
  }
  else {
    wnd2 = (ViewWindow *)(active - 0x48);
  }
  surface_get_clip((DibSurface *)wnd2,(iptr)saved_clip);
  surface_set_clip((DibSurface *)wnd2,(iptr)((u8 *)&wnd2->advance_pane_rects + side * 0x10));
  surface_fill_rect
            ((DibSurface *)wnd2,(iptr)((u8 *)&wnd2->advance_pane_rects + side * 0x10),list_bg_color);
  if (wnd2->large_layout == 0) {
    font2 = (GameFont *)((i8 *)&font_size14);
  }
  else {
    font2 = (GameFont *)((i8 *)&font_size21);
  }
  xLeft = *(int *)((u8 *)&wnd2->advance_pane_rects + side * 0x10);
  list_width = rect_width((iptr)((u8 *)&wnd2->advance_pane_rects + side * 0x10));
  row_height = rect_height((iptr)((u8 *)&wnd2->advance_pane_rects + side * 0x10));
  row_height = row_height / *(int *)(((PictureWindow *)wnd2)->parley_pane_rows_base + side * 4 + 0x38);
  text_dy = row_height / 2;
  row_top = font_cached_height(font2);
  text_dy -= row_top / 2;
  field = wnd2->pane_selection_flags_area + side * 4 - 0x1c;
  field[0] = '\0';
  field[1] = '\0';
  field[2] = '\0';
  field[3] = '\0';
  row = 0;
  do {
    if (*(int *)((u8 *)&wnd2->advance_pane_rects + side * 4 + 0x28) <= row) {
draw_rows:
      for (row = 0; row < *(int *)(((PictureWindow *)wnd2)->parley_pane_rows_base + side * 4 + 0x38);
          row = row + 1) {
        row_top = *(int *)((u8 *)&wnd2->advance_pane_rects + side * 0x10 + 4) + row_height * row;
        SetRect(&row_rect,xLeft,row_top,list_width + xLeft,row_height + row_top);
        if (((row == 0) || (*(int *)(((PictureWindow *)wnd2)->parley_pane_rows_base + side * 4 + 0x28) != -1)) &&
           (*(int *)(((PictureWindow *)wnd2)->parley_pane_rows_base + side * 4 + 0x28) + row <
            *(int *)((u8 *)&wnd2->advance_pane_rects + side * 4 + 0x28))) {
          selected = *(int *)(side * 0x2004 +
                           (*(int *)(((PictureWindow *)wnd2)->parley_pane_rows_base + side * 4 + 0x28) + row) * 4 +
                           0x8400 + (int)wnd2);
          if (selected == 0) {
            text_color2 = list_text_color;
            shadow_color2 = list_shadow_color;
          }
          else {
            text_color2 = dlg_sel_text_color;
            shadow_color2 = dlg_sel_text_shadow_color;
          }
          text_dx = (-(uint)(wnd2->large_layout == 0) & 0xffffffe2) + 0x5a + panel_margin_x;
          row_rect.left = row_rect.left + text_dx - 3;
          if (selected == 0) {
            bg_color2 = list_bg_color;
          }
          else {
            bg_color2 = list_sel_bg_color;
          }
          surface_fill_rect((DibSurface *)wnd2,(iptr)&row_rect,bg_color2);
          if (*(int *)(((PictureWindow *)wnd2)->parley_pane_rows_base + side * 4 + 0x28) == -1) {
            text_clear();
            text = label_string(*(i32 *)(label_string_ids + 0xb84));
            text_append(text);
            field = wnd2->pane_selection_flags_area + side * 4 - 0x1c;
            field[0] = '\0';
            field[1] = '\0';
            field[2] = '\0';
            field[3] = '\0';
          }
          else {
            font_height = font_cached_height(font2);
            parley_draw_civ_capital(*(i32 *)
                                (side * 0x2004 +
                                 (*(int *)(((PictureWindow *)wnd2)->parley_pane_rows_base + side * 4 + 0x28) + row) *
                                 4 + 0x3f0 + (int)wnd2),
                               *(int *)(((PictureWindow *)wnd2)->parley_pane_rows_base + side * 4 + 0x28) + row,
                               xLeft + 2,row_top,font_height);
            text_clear();
            text = civ_name_plural(*(iptr *)(side * 0x2004 +
                                                 (*(int *)(((PictureWindow *)wnd2)->parley_pane_rows_base +
                                                          side * 4 + 0x28) + row) * 4 +
                                                 0x3f0 + (int)wnd2));
            text_append(text);
            text_append_space();
            text_append_lparen();
            text = civ_leader_name(*(iptr *)(side * 0x2004 +
                                                 (*(int *)(((PictureWindow *)wnd2)->parley_pane_rows_base +
                                                          side * 4 + 0x28) + row) * 4 +
                                                 0x3f0 + (int)wnd2));
            text_append(text);
            text_append_rparen();
          }
          if (shadow_color2 != text_color2) {
            gfx_set_text_color_index(shadow_color2);
            surface_draw_text
                      ((DibSurface *)wnd2,(iptr)font2,(iptr)&map_views_block.text_buffer,text_dx + xLeft + 2,
                       text_dy + row_top + 1,5);
            gfx_set_text_color_index(text_color2);
            surface_draw_text
                      ((DibSurface *)wnd2,(iptr)font2,(iptr)&map_views_block.text_buffer,text_dx + xLeft + 1,
                       text_dy + row_top,5);
          }
          gfx_set_text_color_index(text_color2);
          surface_draw_text
                    ((DibSurface *)wnd2,(iptr)font2,(iptr)&map_views_block.text_buffer,text_dx + xLeft,text_dy + row_top,5)
          ;
        }
      }
      surface_set_clip((DibSurface *)wnd2,(iptr)saved_clip);
      parley_update_buttons(wnd2);
      ctrl_show_and_redraw(*(Control **)(wnd2->rate_values + side * 4 + 0x20))
      ;
      return;
    }
    if (*(int *)(side * 0x2004 + row * 4 + 0x8400 + (int)wnd2) != 0) {
      field = wnd2->pane_selection_flags_area + side * 4 - 0x1c;
      field[0] = 1;
      field[1] = '\0';
      field[2] = '\0';
      field[3] = '\0';
      goto draw_rows;
    }
    row++;
  } while( true );
}

/* 004b0157 auto */
void __cdecl parley_draw_civ_capital(int civ,uint row,int x,int y,int row_height)

{
  iptr active;
  int has_palace;
  iptr city2;
  i32 zoom2;
  iptr city;
  int draw_x;
  int icon_width;
  iptr wnd2;
  int best_score;
  int score;
  
  active = wnd_get_active_child();
  if (active == 0) {
    wnd2 = 0;
  }
  else {
    wnd2 = active - 0x48;
  }
  if (*(int *)(wnd2 + 0x154) == 0) {
    zoom2 = 0xfffffffc;
  }
  else {
    zoom2 = 0xfffffffe;
  }
  best_score = 0;
  city2 = -1;
  for (city = 0; city < game.num_cities; city++) {
    if ((cities[city].id != 0) && (cities[city].owner == civ)) {
      score = (int)cities[city].size;
      has_palace = city_has_improvement(city,1);
      if (has_palace != 0) {
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
    if (*(int *)(wnd2 + 0x154) == 0) {
      icon_width = 0x18;
    }
    else {
      icon_width = 0x24;
    }
    if ((row & 1) != 0) {
      draw_x = x + icon_width + 2;
    }
    has_palace = gfx_zoom_scale(0x30,zoom2);
    gfx_draw_city((iptr)&parley_wnd_block.parley_wnd,city2,0,draw_x,y - (has_palace - row_height) / 2,zoom2);
  }
  return;
}

/* 004b0b53 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl
net_send_state_diff(i32 dest,uint flags,int limit,i32 force,i32 alt_msg)

{
  int *mirror_start;
  int *run_start;
  int encoded;
  int bytes_changed;
  uint run_section;
  uint run_size;
  int *cur_ptr;
  int *rle_src;
  int rle_src_end;
  uint *rle_dst;
  i32 *rle_size_ptr;
  uint encoded_size;
  int *start_ptr;
  uint run_offset;
  iptr game_mirror;
  uint *out_ptr;
  int record_count;
  int runs_left;
  int deadline;
  int *section_end;
  
  if (game.multiplayer < 3) {
    bytes_changed = 0;
  }
  else if (((char)force == '\0') && (net_session_block.net_player_count[0] == 1)) {
    bytes_changed = 0;
  }
  else {
    bytes_changed = 0;
    runs_left = 0;
    deadline = 0;
    start_ptr = (*(int * *)&map_views_block.diffeng_scan_ptr);
    diffeng_send_count_i32++;
    if ((flags & 1) != 0) {
      diffeng_invalidate_mirror();
    }
    if ((flags & 4) == 0) {
      if ((flags & 8) != 0) {
        runs_left = limit;
      }
    }
    else {
      deadline = timer_ticks();
      deadline = limit + deadline;
    }
    cur_ptr = (int *)((((iptr *)&diffeng_sections_block.diffeng_section_ptrs))[(*(uint *)&map_views_block.diffeng_scan_section) * 6] + map_views_block.diffeng_scan_offset_i32);
    section_end = (int *)((((i32 *)&diffeng_sections_block.diffeng_section_padded_sizes))[(*(uint *)&map_views_block.diffeng_scan_section) * 6] + (((iptr *)&diffeng_sections_block.diffeng_section_ptrs))[(*(uint *)&map_views_block.diffeng_scan_section) * 6]);
    if ((*(uint *)&map_views_block.diffeng_scan_section) == 1) {
      game_mirror = diffeng_game_section_block.diffeng_game_offset + diffeng_mirror_buf;
      *(i16 *)(game_mirror + 0x16) = game.active_unit;
      *(i16 *)(game_mirror + 0x18) = game.moving_unit;
      *(u8 *)(game_mirror + 0x1a) = game.multiplayer;
      *(i8 *)(game_mirror + 0x1b) = game.player_civ;
      *(i8 *)(game_mirror + 0x1c) = game.saved_current_civ;
      *(i8 *)(game_mirror + 0x1d) = game.turn_civ;
      *(u32 *)(game_mirror + 2) = game.game_options;
      *(u16 *)(game_mirror + 10) = game.message_options;
    }
    map_views_block.diffeng_packet_i32 = 0x66606660;
    if ((char)alt_msg == '\0') {
      map_views_block.diffeng_packet_msg_type_i32 = 0x15;
    }
    else {
      map_views_block.diffeng_packet_msg_type_i32 = 0x5c;
    }
    out_ptr = ((i32 *)&map_views_block.diffeng_packet_payload);
    record_count = 0;
    do {
      run_start = cur_ptr;
      mirror_start = (*(int * *)&map_views_block.diffeng_scan_ptr);
      if (*cur_ptr == *(*(int * *)&map_views_block.diffeng_scan_ptr)) {
        (*(int * *)&map_views_block.diffeng_scan_ptr)++;
        if ((*(int * *)&map_views_block.diffeng_scan_ptr) < (*(int * *)&map_views_block.diffeng_mirror_end)) {
          cur_ptr++;
          if (section_end <= cur_ptr) {
            (*(uint *)&map_views_block.diffeng_scan_section)++;
            if ((*(uint *)&map_views_block.diffeng_scan_section) == 1) {
              game_mirror = diffeng_game_section_block.diffeng_game_offset + diffeng_mirror_buf;
              *(i16 *)(game_mirror + 0x16) = game.active_unit;
              *(i16 *)(game_mirror + 0x18) = game.moving_unit;
              *(u8 *)(game_mirror + 0x1a) = game.multiplayer;
              *(i8 *)(game_mirror + 0x1b) = game.player_civ;
              *(i8 *)(game_mirror + 0x1c) = game.saved_current_civ;
              *(i8 *)(game_mirror + 0x1d) = game.turn_civ;
              *(u32 *)(game_mirror + 2) = game.game_options;
              *(u16 *)(game_mirror + 10) = game.message_options;
            }
            map_views_block.diffeng_scan_offset_i32 = 0;
            cur_ptr = (int *)(((iptr *)&diffeng_sections_block.diffeng_section_ptrs))[(*(uint *)&map_views_block.diffeng_scan_section) * 6];
            section_end = (int *)((((i32 *)&diffeng_sections_block.diffeng_section_padded_sizes))[(*(uint *)&map_views_block.diffeng_scan_section) * 6] + (((iptr *)&diffeng_sections_block.diffeng_section_ptrs))[(*(uint *)&map_views_block.diffeng_scan_section) * 6]
                             );
          }
        }
        else {
          (*(int * *)&map_views_block.diffeng_scan_ptr) = (int *)diffeng_mirror_buf;
          (*(uint *)&map_views_block.diffeng_scan_section) = 0;
          map_views_block.diffeng_scan_offset_i32 = 0;
          cur_ptr = (int *)diffeng_sections_block.diffeng_section_ptrs[0];
          section_end = (int *)(diffeng_sections_block.diffeng_section_padded_sizes[0] + diffeng_sections_block.diffeng_section_ptrs[0]);
        }
      }
      else {
        run_size = 0;
        do {
          (*(int * *)&map_views_block.diffeng_scan_ptr)++;
          if ((*(int * *)&map_views_block.diffeng_scan_ptr) < (*(int * *)&map_views_block.diffeng_mirror_end)) {
            cur_ptr++;
            if (section_end <= cur_ptr) {
              run_offset = (int)run_start - (((iptr *)&diffeng_sections_block.diffeng_section_ptrs))[(*(uint *)&map_views_block.diffeng_scan_section) * 6];
              run_size = (int)section_end - (int)run_start;
              run_section = (*(uint *)&map_views_block.diffeng_scan_section);
              (*(uint *)&map_views_block.diffeng_scan_section)++;
              if ((*(uint *)&map_views_block.diffeng_scan_section) == 1) {
                game_mirror = diffeng_game_section_block.diffeng_game_offset + diffeng_mirror_buf;
                *(i16 *)(game_mirror + 0x16) = game.active_unit;
                *(i16 *)(game_mirror + 0x18) = game.moving_unit;
                *(u8 *)(game_mirror + 0x1a) = game.multiplayer;
                *(i8 *)(game_mirror + 0x1b) = game.player_civ;
                *(i8 *)(game_mirror + 0x1c) = game.saved_current_civ;
                *(i8 *)(game_mirror + 0x1d) = game.turn_civ;
                *(u32 *)(game_mirror + 2) = game.game_options;
                *(u16 *)(game_mirror + 10) = game.message_options;
              }
              map_views_block.diffeng_scan_offset_i32 = 0;
              cur_ptr = (int *)(((iptr *)&diffeng_sections_block.diffeng_section_ptrs))[(*(uint *)&map_views_block.diffeng_scan_section) * 6];
              section_end = (int *)((((i32 *)&diffeng_sections_block.diffeng_section_padded_sizes))[(*(uint *)&map_views_block.diffeng_scan_section) * 6] +
                               (((iptr *)&diffeng_sections_block.diffeng_section_ptrs))[(*(uint *)&map_views_block.diffeng_scan_section) * 6]);
            }
          }
          else {
            run_offset = (int)run_start - (((iptr *)&diffeng_sections_block.diffeng_section_ptrs))[(*(uint *)&map_views_block.diffeng_scan_section) * 6];
            run_size = (int)(*(int * *)&map_views_block.diffeng_mirror_end) - (int)mirror_start;
            run_section = (*(uint *)&map_views_block.diffeng_scan_section);
            (*(int * *)&map_views_block.diffeng_scan_ptr) = (int *)diffeng_mirror_buf;
            (*(uint *)&map_views_block.diffeng_scan_section) = 0;
            map_views_block.diffeng_scan_offset_i32 = 0;
            cur_ptr = (int *)diffeng_sections_block.diffeng_section_ptrs[0];
            section_end = (int *)(diffeng_sections_block.diffeng_section_padded_sizes[0] + diffeng_sections_block.diffeng_section_ptrs[0]);
          }
        } while (((run_size == 0) &&
                 ((int)(*(int * *)&map_views_block.diffeng_scan_ptr) + (-(iptr)&map_views_block.diffeng_packet_i32 - (int)mirror_start) + (int)out_ptr < diffeng_packet_flush_size)) &&
                (*cur_ptr != *(*(int * *)&map_views_block.diffeng_scan_ptr)));
        if (0x400 < run_size) {
          err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_difflength_diff_engine_message_length,(iptr)&str_d_ss_franklinton_difference_engine_cpp_2,0xee);
        }
        if (run_size == 0) {
          run_offset = (int)run_start - (((iptr *)&diffeng_sections_block.diffeng_section_ptrs))[(*(uint *)&map_views_block.diffeng_scan_section) * 6];
          run_section = (*(uint *)&map_views_block.diffeng_scan_section);
          run_size = (int)(*(int * *)&map_views_block.diffeng_scan_ptr) - (int)mirror_start;
        }
        if (0x400 < run_size) {
          err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_difflength_diff_engine_message_length_2,(iptr)&str_d_ss_franklinton_difference_engine_cpp_3,0xf7);
        }
        if ((flags & 0x10) == 0) {
          crt_memcpy(mirror_start,run_start,run_size);
        }
        rle_src = run_start;
        rle_src_end = (int)run_start + run_size;
        rle_dst = out_ptr + 3;
        rle_size_ptr = ((i32 *)&map_views_block.diffeng_mirror_size);
        encoded = diffeng_rle_encode((iptr)&rle_src);
        if (encoded == 0) {
          crt_memcpy(out_ptr + 3,run_start,run_size);
          *out_ptr = run_section;
          out_ptr[1] = run_offset;
          out_ptr[2] = run_size;
          out_ptr = (uint *)((int)out_ptr + run_size + 0xc);
        }
        else {
          *out_ptr = run_section | 0x8000;
          out_ptr[1] = run_offset;
          out_ptr[2] = encoded_size;
          out_ptr = (uint *)((int)out_ptr + encoded_size + 0xc);
        }
        record_count++;
        bytes_changed += run_size;
        if (diffeng_packet_flush_size <= (int)(out_ptr - 0x19e7fc)) {
          map_views_block.diffeng_packet_size_i32 = out_ptr - 0x19e7fc;
          map_views_block.diffeng_packet_record_count_i32 = record_count;
          net_send_message(0x5c,dest,0,0,0,0,0,0,0,(iptr)&map_views_block.diffeng_packet_i32);
          if ((flags & 1) != 0) {
            XD_FlushSendBuffer(5000);
          }
          out_ptr = ((i32 *)&map_views_block.diffeng_packet_payload);
          record_count = 0;
        }
        if ((((flags & 4) != 0) && (encoded = timer_ticks(), deadline < encoded)) ||
           (((flags & 8) != 0 && (runs_left = runs_left - 1, runs_left == 0)))) break;
      }
    } while (start_ptr != (*(int * *)&map_views_block.diffeng_scan_ptr));
    if (((i32 *)&map_views_block.diffeng_packet_payload) < out_ptr) {
      map_views_block.diffeng_packet_size_i32 = out_ptr - 0x19e7fc;
      map_views_block.diffeng_packet_record_count_i32 = record_count;
      net_send_message(0x5c,dest,0,0,0,0,0,0,0,(iptr)&map_views_block.diffeng_packet_i32);
      if ((flags & 1) != 0) {
        XD_FlushSendBuffer(5000);
      }
    }
    map_views_block.diffeng_scan_offset_i32 = (int)cur_ptr - (((iptr *)&diffeng_sections_block.diffeng_section_ptrs))[(*(uint *)&map_views_block.diffeng_scan_section) * 6];
  }
  return bytes_changed;
}

/* 004b401c auto */
void __cdecl parley_wnd_global_init(void)

{
  parley_wnd_static_init();
  parley_wnd_reg_atexit();
  return;
}

/* 004b4036 auto */
void __cdecl parley_wnd_static_init(void)

{
  parley_wnd_ctor((ViewWindow *)((i8 *)&parley_wnd_block.parley_wnd),(iptr)&prefs_main_menu_choice_block.prefs_parley_wnd_rect);
  return;
}

/* 004b405b auto */
void __cdecl parley_wnd_reg_atexit(void)

{
  _atexit(parley_wnd_static_dtor);
  return;
}

/* 004b4078 auto */
void __cdecl parley_wnd_static_dtor(void)

{
  parley_wnd_dtor((ViewWindow *)((i8 *)&parley_wnd_block.parley_wnd));
  return;
}

/* 004b4092 auto */
void __cdecl chat_wnd_global_init(void)

{
  chat_wnd_static_init();
  chat_wnd_reg_atexit();
  return;
}

/* 004b40ac auto */
void __cdecl chat_wnd_static_init(void)

{
  parley_wnd_ctor((ViewWindow *)((i8 *)&chat_wnd_block.chat_wnd),(iptr)&prefs_main_menu_choice_block.prefs_chat_wnd_rect);
  return;
}

/* 004b40d1 auto */
void __cdecl chat_wnd_reg_atexit(void)

{
  _atexit(chat_wnd_static_dtor);
  return;
}

/* 004b40ee auto */
void __cdecl chat_wnd_static_dtor(void)

{
  parley_wnd_dtor((ViewWindow *)((i8 *)&chat_wnd_block.chat_wnd));
  return;
}

/* 004b4108 auto */
ViewWindow * __thiscall parley_wnd_ctor(ViewWindow *self,iptr rect)

{
  u8 *field;
  int width;
  int i;
  i32 seh_prev;
  i8 *seh_handler;
  i32 unwind_state;
  
  unwind_state = 0xffffffff;
  surfwnd_ctor((SurfaceWindow *)self);
  unwind_state = 0;
  self->vtable = (u32)((pointer *)&leader_anim_frame_starts_block.ptr_fun_3 + 1);
  self->init_rect = rect;
  self->style_flags = 1;
  prefs_load_civ2dat();
  width = rect_width(self->init_rect);
  if (width < 1) {
    self->border_width = 0;
    self->resize_border = 0;
  }
  else {
    self->border_width = *(u32 *)self->init_rect;
    self->resize_border = *(u32 *)(self->init_rect + 4);
    if (width < 0x321) {
      self->large_layout = 0;
    }
    else {
      self->large_layout = 1;
    }
  }
  self->close_button = 0;
  self->send_button_value = 0;
  self->clear_button_value = 0;
  self->conceal_button_value = 0;
  self->reveal_button_value = 0;
  self->rates_clamped = 0;
  self->intel_button_value = 0;
  self->mode2_button_value = 0;
  self->never_mind_button_value = 0;
  self->tax_scrollbar = 0;
  self->no_thanks_button_value = 0;
  self->counter_button_value = 0;
  for (i = 0; i < 8; i++) {
    field = self->parley_checkboxes + i * 4 - 0x1c;
    field[0] = '\0';
    field[1] = '\0';
    field[2] = '\0';
    field[3] = '\0';
    field = self->parley_checkboxes + i * 4 + 4;
    field[0] = '\0';
    field[1] = '\0';
    field[2] = '\0';
    field[3] = '\0';
    field = self->editor_combo_boxes + i * 4 + 0x2c;
    field[0] = '\0';
    field[1] = '\0';
    field[2] = '\0';
    field[3] = '\0';
    field = self->rate_values + i * 4 - 0x44;
    field[0] = '\0';
    field[1] = '\0';
    field[2] = '\0';
    field[3] = '\0';
  }
  self->init_sci_rate = 0;
  self->dialog_w = 0;
  self->dialog_h = 0;
  self->init_lux_rate = 0;
  self->sci_rate_sel = 0;
  self->init_tax_rate = 0;
  self->side_text_edit = 0;
  self->caption_height = 0xffffffff;
  self->item_buffer = 0;
  self->left_exchange_kind = 0;
  self->right_exchange_kind = 1;
  self->demand_choice = 0;
  self->saved_mode_choice = 0xffffffff;
  self->exchange_choice = 0;
  self->side0_amount_init = 0;
  self->side0_amount = self->side0_amount_init;
  self->side1_amount_init = 0;
  self->side1_amount = self->side1_amount_init;
  self->gift_choice = 0;
  self->treaty_type_choice = 0;
  self->timer_last_value = 0;
  self->show_turn_status = self->timer_last_value;
  self->text_offset_y = 0;
  self->list_font = 0;
  self->reset_value_28c = 0;
  self->chat_input_edit = 0;
  self->chat_history_edit = 0;
  (*(i32 *)&chat_input_buffer) = 0;
  (*(i32 *)&chat_log_buffer) = 0;
  font_size16_bold_block.chat_log_capacity = 0;
  for (i = 0; i < 2; i++) {
    field = self->rate_values + i * 4;
    field[0] = '\0';
    field[1] = '\0';
    field[2] = '\0';
    field[3] = '\0';
    field = self->rate_values + i * 4 + 8;
    field[0] = '\0';
    field[1] = '\0';
    field[2] = '\0';
    field[3] = '\0';
    field = self->rate_values + i * 4 + 0x10;
    field[0] = '\0';
    field[1] = '\0';
    field[2] = '\0';
    field[3] = '\0';
    field = self->rate_values + i * 4 + 0x18;
    field[0] = '\0';
    field[1] = '\0';
    field[2] = '\0';
    field[3] = '\0';
    field = self->rate_values + i * 4 + 0x20;
    field[0] = '\0';
    field[1] = '\0';
    field[2] = '\0';
    field[3] = '\0';
    field = self->rate_values + i * 4 + 0x28;
    field[0] = '\0';
    field[1] = '\0';
    field[2] = '\0';
    field[3] = '\0';
    field = self->rate_values + i * 4 + 0x30;
    field[0] = '\0';
    field[1] = '\0';
    field[2] = '\0';
    field[3] = '\0';
    field = (u8 *)&self->advance_pane_rects + i * 4 - 0x24;
    field[0] = '\0';
    field[1] = '\0';
    field[2] = '\0';
    field[3] = '\0';
    field = (u8 *)&self->advance_pane_rects + i * 4 - 0x1c;
    field[0] = '\0';
    field[1] = '\0';
    field[2] = '\0';
    field[3] = '\0';
  }
  self->right_side_accepted = '\0';
  self->left_side_accepted = '\0';
  self->left_side_confirmed = '\0';
  self->remote_side_agreed = '\0';
  return self;
}

/* 004b4593 auto */
void __thiscall parley_wnd_dtor(ViewWindow *self)

{
  int created;
  size_t log_len;
  FileObject log_file;
  i32 seh_prev;
  i8 *seh_handler;
  uint unwind_state;
  
  self->vtable = (u32)((pointer *)&leader_anim_frame_starts_block.ptr_fun_3 + 1);
  unwind_state = 0;
  if (self->session_mode == 4) {
    file_obj_init(&log_file);
    unwind_state = (unwind_state & 0xffffff00 | (byte)(1));
    if ((prefs_main_menu_choice_block.prefs_clear_chat_on_boot != 0) && (chat_log_buffer != (char *)0x0)) {
      *chat_log_buffer = '\0';
      created = file_obj_create(&log_file,(iptr)&str_chatlog_txt_2);
      if (created != 0) {
        log_len = _strlen(chat_log_buffer);
        file_obj_write(&log_file,(iptr)chat_log_buffer,log_len);
        file_map_close(&log_file);
      }
    }
    if (chat_log_buffer != (char *)0x0) {
      operator_delete(chat_log_buffer);
      chat_log_buffer = (char *)0x0;
    }
    if (chat_input_buffer != (void *)0x0) {
      operator_delete(chat_input_buffer);
      chat_input_buffer = (void *)0x0;
    }
    unwind_state = unwind_state & 0xffffff00;
    /* inlined unwind funclet 004b4705 */ { file_obj_close((FileObject *)((iptr)&log_file)); }
  }
  parley_wnd_destroy_controls(self);
  wnd_destroy_with_surface((DibSurface *)self);
  unwind_state = 0xffffffff;
  /* inlined unwind funclet 004b4711 */ { surfwnd_dtor(*(SurfaceWindow **)((iptr)&self)); }
  return;
}

/* 004b4735 auto */
void __thiscall parley_wnd_create(ViewWindow *self,u32 mode)

{
  int file_size;
  i32 height;
  i32 width;
  i8 *palette;
  i8 *parent;
  u8 *wnd2;
  i8 log_file[160];
  i32 unwind_state;
  
  unwind_state = 0xffffffff;
  self->style_flags = 1;
  if (self == (ViewWindow *)0x0) {
    wnd2 = (u8 *)0x0;
  }
  else {
    wnd2 = self->window_2;
  }
  wnd_set_active_child((iptr)wnd2);
  self->session_mode = mode;
  if (self->session_mode != 4) goto pick_size_mode;
  (*(UINT *)&font_size16_bold_block.chat_log_capacity) = GetPrivateProfileIntA
                           (str_civilization_gold_7,str_chatshowsize,-1,
                            str_civ_ini_7);
  if (((*(UINT *)&font_size16_bold_block.chat_log_capacity) == 0xffffffff) || ((int)(*(UINT *)&font_size16_bold_block.chat_log_capacity) < 0x2000)) {
    WritePrivateProfileStringA
              (str_civilization_gold_8,str_chatshowsize_2,((i8 *)&chat_show_size_default_str),str_civ_ini_8
              );
    (*(UINT *)&font_size16_bold_block.chat_log_capacity) = 0x2000;
  }
  else if (0xdfff < (int)(*(UINT *)&font_size16_bold_block.chat_log_capacity)) {
    WritePrivateProfileStringA
              (str_civilization_gold_9,str_chatshowsize_3,str_57344,
               str_civ_ini_9);
    (*(UINT *)&font_size16_bold_block.chat_log_capacity) = 0xe000;
  }
  if ((*(i8 * *)&chat_log_buffer) == (i8 *)0x0) {
    (*(i8 * *)&chat_log_buffer) = operator_new((*(UINT *)&font_size16_bold_block.chat_log_capacity) + 1);
  }
  _memset((*(i8 * *)&chat_log_buffer),0,(*(UINT *)&font_size16_bold_block.chat_log_capacity) + 1);
  if (chat_input_buffer == (void *)0x0) {
    chat_input_buffer = operator_new(0x101);
  }
  _memset(chat_input_buffer,0,0x101);
  file_obj_init((FileObject *)log_file);
  unwind_state = 0;
  if (prefs_main_menu_choice_block.prefs_clear_chat_on_new_game == 0) {
    file_size = file_obj_open((FileObject *)log_file,(iptr)&str_chatlog_txt_3);
    if (file_size == 0) goto clear_chat_buffer;
    file_size = file_obj_get_size((FileObject *)log_file);
    if ((int)(*(UINT *)&font_size16_bold_block.chat_log_capacity) < file_size) {
      file_obj_seek_cur((FileSeekView *)log_file,file_size - (*(UINT *)&font_size16_bold_block.chat_log_capacity));
    }
    file_obj_read((FileObject *)log_file,(iptr)(*(i8 * *)&chat_log_buffer),(*(UINT *)&font_size16_bold_block.chat_log_capacity));
    file_map_close((FileObject *)log_file);
  }
  else {
clear_chat_buffer:
    *(*(i8 * *)&chat_log_buffer) = 0;
  }
  unwind_state = 0xffffffff;
  /* inlined unwind funclet 004b4be3 */ { file_obj_close((FileObject *)((iptr)&log_file)); }
pick_size_mode:
  if ((self->border_width == 0) && (self->resize_border == 0)) {
    parley_wnd_pick_size_mode((ParleyWindowLayout *)self);
  }
  crt_strcpy(self->parley_title,((i8 *)&parley_wnd_empty_title_str));
  if (self->session_mode == 4) {
    parent = ((i8 *)&main_frame_wnd_block.main_frame_wnd);
    palette = ((i8 *)&game_palette_block.game_palette);
    height = rect_height(self->init_rect);
    width = rect_width(self->init_rect);
    wnd_create_with_surface
              ((DibSurface *)self,0,0x602,*(i32 *)self->init_rect,
               *(i32 *)(self->init_rect + 4),width,height,(iptr)palette,(iptr)parent);
  }
  else {
    parent = ((i8 *)&main_frame_wnd_block.main_frame_wnd);
    palette = ((i8 *)&game_palette_block.game_palette);
    height = rect_height(self->init_rect);
    width = rect_width(self->init_rect);
    wnd_create_with_surface
              ((DibSurface *)self,0,0x602,*(i32 *)self->init_rect,
               *(i32 *)(self->init_rect + 4),width,height,(iptr)palette,(iptr)parent);
  }
  parley_wnd_calc_rect((ParleyWindowLayout *)self);
  wnd_move_to_rect((WndBase *)self->window_2,self->init_rect);
  self->built_layout = 0xffffffff;
  self->left_civ = parley_mode3_left_kind;
  self->right_civ = parley_mode3_right_kind;
  self->shown_left_civ = 0x15;
  self->caption_button_count = 0x15;
  wnd_set_close_handler((WndEventHandlers *)(self->event_handlers),(iptr)diplo_wnd_close_active);
  wnd_set_redraw_callback((SurfaceWindow *)self,(iptr)parley_wnd_redraw);
  wnd_set_move_handler((WndEventHandlers *)(self->event_handlers),(iptr)parley_wnd_on_move);
  wnd_set_keydown_handler((WndEventHandlers *)(self->event_handlers),(iptr)parley_wnd_on_key);
  parley_wnd_calc_layout((ParleyWindowLayout *)self);
  parley_wnd_sync_sides(self);
  if (((self->session_mode == 3) || (self->session_mode == 2)) || (self->session_mode == 1)) {
    ctrl_disable((Control *)self->never_mind_button_value);
  }
  parley_update_buttons(self);
  return;
}

/* 004b4c09 auto */
void __cdecl parley_wnd_on_move(void)

{
  iptr active;
  iptr wnd2;
  
  active = wnd_get_active_child();
  if (active == 0) {
    wnd2 = 0;
  }
  else {
    wnd2 = active - 0x48;
  }
  wnd_get_rect_in_parent((WndBase *)(wnd2 + 0x48),*(iptr *)(wnd2 + 0x150));
  *(i32 *)(wnd2 + 0x11c) = **(i32 **)(wnd2 + 0x150);
  *(i32 *)(wnd2 + 0x120) = *(i32 *)(*(int *)(wnd2 + 0x150) + 4);
  return;
}

/* 004b4c81 auto */
void __thiscall parley_wnd_pick_size_mode(ParleyWindowLayout *self)

{
  iptr active;
  iptr wnd2;
  
  active = wnd_get_active_child();
  if (active == 0) {
    wnd2 = 0;
  }
  else {
    wnd2 = active - 0x48;
  }
  *(i32 *)(wnd2 + 0x154) = 0;
  if (999 < caption_font_block.screen_width) {
    *(i32 *)(wnd2 + 0x154) = 1;
  }
  parley_wnd_calc_rect(self);
  return;
}

/* 004b4cf0 auto */
void __thiscall parley_wnd_calc_rect(ParleyWindowLayout *self)

{
  int size;
  int font_height;
  int height2;
  int width2;
  u32 top;
  u32 left;
  
  if (self->large_layout == 0) {
    width2 = 0x208;
  }
  else {
    width2 = 800;
  }
  if (self->large_layout == 0) {
    height2 = 0x14f;
  }
  else {
    height2 = 0x1cc;
  }
  if (self->large_layout == 0) {
    font_height = font_cached_height((GameFont *)((i8 *)&font_size20));
  }
  else {
    font_height = font_cached_height((GameFont *)((i8 *)&font_size30));
  }
  self->client_width = panel_margin_y * 2 + panel_bevel_width * 2 + font_height;
  width2 = width2 + (panel_padding_x + panel_margin_x) * 2 + 6;
  height2 = height2 + panel_margin_y * 2 + self->client_width * 2 + 0xe;
  size = rect_width(self->init_rect);
  if (size == 0) {
    size = wnd_client_width((WndBase *)((i8 *)&main_frame_wnd_block.main_frame_wnd));
    self->border_width = (size >> 1) - (width2 >> 1);
    left = self->border_width;
    size = wnd_client_height((WndBase *)((i8 *)&main_frame_wnd_block.main_frame_wnd));
    self->resize_border = (size >> 1) - (height2 >> 1);
    top = self->resize_border;
  }
  else {
    left = self->border_width;
    top = self->resize_border;
  }
  SetRect((LPRECT)self->init_rect,left,top,width2 + left,height2 + top);
  wnd_set_caption_height((WndBase *)self->window_2,self->client_width);
  return;
}

/* 004b4e8a auto */
void __thiscall parley_wnd_calc_layout(ParleyWindowLayout *self)

{
  u32 dim;
  int font_height;
  
  dim = surface_get_width((DibSurface *)self);
  self->client_x = dim;
  dim = surface_get_height((DibSurface *)self);
  self->client_y = dim;
  if (self->large_layout == 0) {
    font_height = font_cached_height((GameFont *)((i8 *)&font_size20));
  }
  else {
    font_height = font_cached_height((GameFont *)((i8 *)&font_size30));
  }
  self->client_width = panel_margin_y * 2 + panel_bevel_width * 2 + font_height;
  SetRect((LPRECT)&self->client_height,0,0,self->client_x,self->client_y);
  SetRect((LPRECT)&self->panel_rect,0,0,self->client_x + (panel_padding_x + panel_margin_x) * -2,
          self->client_y - (panel_margin_y * 2 + self->client_width * 2 + panel_padding_x));
  OffsetRect((LPRECT)&self->panel_rect,panel_padding_x + panel_margin_x,self->client_width + panel_margin_y);
  return;
}

/* 004b4fb2 auto */
void __thiscall parley_wnd_sync_sides(ViewWindow *self)

{
  if (self->built_layout == self->large_layout) {
    if (self->shown_left_civ != self->left_civ) {
      parley_add_side_dialog(self,self->left_civ,0);
      self->shown_left_civ = self->left_civ;
    }
    if (self->caption_button_count != self->right_civ) {
      parley_add_side_dialog(self,self->right_civ,1);
      self->caption_button_count = self->right_civ;
    }
  }
  else {
    parley_wnd_destroy_controls(self);
    parley_wnd_create_controls(self);
    parley_add_side_dialog(self,self->left_civ,0);
    parley_add_side_dialog(self,self->right_civ,1);
    self->shown_left_civ = self->left_civ;
    self->caption_button_count = self->right_civ;
    self->built_layout = self->large_layout;
  }
  return;
}

/* 004b50cf auto */
void __thiscall parley_wnd_destroy_controls(ViewWindow *self)

{
  u8 *slot;
  int i;
  
  if (self->item_buffer != 0) {
    operator_delete((void *)self->item_buffer);
    self->item_buffer = 0;
  }
  for (i = 0; i < 3; i++) {
    if (*(int *)(self->caption_button_hotspots + i * 0x1c - 4) != 0) {
      if (*(Hotspot **)(self->caption_button_hotspots + i * 0x1c - 4) != (Hotspot *)0x0) {
        hotspot_scalar_dtor(*(Hotspot **)(self->caption_button_hotspots + i * 0x1c - 4),1);
      }
      slot = self->caption_button_hotspots + i * 0x1c - 4;
      slot[0] = '\0';
      slot[1] = '\0';
      slot[2] = '\0';
      slot[3] = '\0';
    }
  }
  if (self->close_button != 0) {
    if ((Control *)self->close_button != (Control *)0x0) {
      ctrl_scalar_dtor((Control *)self->close_button,1);
    }
    self->close_button = 0;
  }
  if (self->send_button_value != 0) {
    if ((Control *)self->send_button_value != (Control *)0x0) {
      ctrl_scalar_dtor((Control *)self->send_button_value,1);
    }
    self->send_button_value = 0;
  }
  if (self->clear_button_value != 0) {
    if ((Control *)self->clear_button_value != (Control *)0x0) {
      ctrl_scalar_dtor((Control *)self->clear_button_value,1);
    }
    self->clear_button_value = 0;
  }
  if (self->reveal_button_value != 0) {
    if ((Control *)self->reveal_button_value != (Control *)0x0) {
      ctrl_scalar_dtor((Control *)self->reveal_button_value,1);
    }
    self->reveal_button_value = 0;
  }
  if (self->conceal_button_value != 0) {
    if ((Control *)self->conceal_button_value != (Control *)0x0) {
      ctrl_scalar_dtor((Control *)self->conceal_button_value,1);
    }
    self->conceal_button_value = 0;
  }
  if (self->rates_clamped != 0) {
    if ((Control *)self->rates_clamped != (Control *)0x0) {
      ctrl_scalar_dtor((Control *)self->rates_clamped,1);
    }
    self->rates_clamped = 0;
  }
  if (self->intel_button_value != 0) {
    if ((Control *)self->intel_button_value != (Control *)0x0) {
      ctrl_scalar_dtor((Control *)self->intel_button_value,1);
    }
    self->intel_button_value = 0;
  }
  if (self->mode2_button_value != 0) {
    if ((Control *)self->mode2_button_value != (Control *)0x0) {
      ctrl_scalar_dtor((Control *)self->mode2_button_value,1);
    }
    self->mode2_button_value = 0;
  }
  if (self->never_mind_button_value != 0) {
    if ((Control *)self->never_mind_button_value != (Control *)0x0) {
      ctrl_scalar_dtor((Control *)self->never_mind_button_value,1);
    }
    self->never_mind_button_value = 0;
  }
  if (self->tax_scrollbar != 0) {
    if ((Control *)self->tax_scrollbar != (Control *)0x0) {
      ctrl_scalar_dtor((Control *)self->tax_scrollbar,1);
    }
    self->tax_scrollbar = 0;
  }
  if (self->no_thanks_button_value != 0) {
    if ((Control *)self->no_thanks_button_value != (Control *)0x0) {
      ctrl_scalar_dtor((Control *)self->no_thanks_button_value,1);
    }
    self->no_thanks_button_value = 0;
  }
  if (self->counter_button_value != 0) {
    if ((Control *)self->counter_button_value != (Control *)0x0) {
      ctrl_scalar_dtor((Control *)self->counter_button_value,1);
    }
    self->counter_button_value = 0;
  }
  if (self->chat_history_edit != 0) {
    if ((Control *)self->chat_history_edit != (Control *)0x0) {
      edit_scalar_dtor((Control *)self->chat_history_edit,1);
    }
    self->chat_history_edit = 0;
  }
  if (self->chat_input_edit != 0) {
    if ((Control *)self->chat_input_edit != (Control *)0x0) {
      edit_scalar_dtor((Control *)self->chat_input_edit,1);
    }
    self->chat_input_edit = 0;
  }
  if (self->sci_rate_sel != 0) {
    if ((Checkbox *)self->sci_rate_sel != (Checkbox *)0x0) {
      checkbox_scalar_dtor((Checkbox *)self->sci_rate_sel,1);
    }
    self->sci_rate_sel = 0;
  }
  if (self->init_tax_rate != 0) {
    if ((Checkbox *)self->init_tax_rate != (Checkbox *)0x0) {
      checkbox_scalar_dtor((Checkbox *)self->init_tax_rate,1);
    }
    self->init_tax_rate = 0;
  }
  if (self->side_text_edit != 0) {
    if ((Control *)self->side_text_edit != (Control *)0x0) {
      edit_scalar_dtor((Control *)self->side_text_edit,1);
    }
    self->side_text_edit = 0;
  }
  if (self->init_lux_rate != 0) {
    if ((Checkbox *)self->init_lux_rate != (Checkbox *)0x0) {
      checkbox_scalar_dtor((Checkbox *)self->init_lux_rate,1);
    }
    self->init_lux_rate = 0;
  }
  for (i = 0; i < 8; i++) {
    if (*(int *)(self->parley_checkboxes + i * 4 - 0x1c) != 0) {
      if (*(Checkbox **)(self->parley_checkboxes + i * 4 - 0x1c) != (Checkbox *)0x0) {
        checkbox_scalar_dtor(*(Checkbox **)(self->parley_checkboxes + i * 4 - 0x1c),1);
      }
      slot = self->parley_checkboxes + i * 4 - 0x1c;
      slot[0] = '\0';
      slot[1] = '\0';
      slot[2] = '\0';
      slot[3] = '\0';
    }
    if (*(int *)(self->parley_checkboxes + i * 4 + 4) != 0) {
      if (*(Checkbox **)(self->parley_checkboxes + i * 4 + 4) != (Checkbox *)0x0) {
        checkbox_scalar_dtor(*(Checkbox **)(self->parley_checkboxes + i * 4 + 4),1);
      }
      slot = self->parley_checkboxes + i * 4 + 4;
      slot[0] = '\0';
      slot[1] = '\0';
      slot[2] = '\0';
      slot[3] = '\0';
    }
  }
  for (i = 0; i < 2; i++) {
    if (*(int *)(self->rate_values + i * 4) != 0) {
      if (*(Checkbox **)(self->rate_values + i * 4) != (Checkbox *)0x0) {
        checkbox_scalar_dtor(*(Checkbox **)(self->rate_values + i * 4),1);
      }
      slot = self->rate_values + i * 4;
      slot[0] = '\0';
      slot[1] = '\0';
      slot[2] = '\0';
      slot[3] = '\0';
    }
    if (*(int *)(self->rate_values + i * 4 + 8) != 0) {
      if (*(RadioGroupDtorView **)(self->rate_values + i * 4 + 8) != (RadioGroupDtorView *)0x0) {
        radiogrp_scalar_dtor(*(RadioGroupDtorView **)(self->rate_values + i * 4 + 8),1);
      }
      slot = self->rate_values + i * 4 + 8;
      slot[0] = '\0';
      slot[1] = '\0';
      slot[2] = '\0';
      slot[3] = '\0';
    }
    if (*(int *)(self->rate_values + i * 4 + 0x10) != 0) {
      if (*(Control **)(self->rate_values + i * 4 + 0x10) != (Control *)0x0) {
        edit_scalar_dtor(*(Control **)(self->rate_values + i * 4 + 0x10),1)
        ;
      }
      slot = self->rate_values + i * 4 + 0x10;
      slot[0] = '\0';
      slot[1] = '\0';
      slot[2] = '\0';
      slot[3] = '\0';
    }
    if (*(int *)(self->rate_values + i * 4 + 0x18) != 0) {
      if (*(Control **)(self->rate_values + i * 4 + 0x18) != (Control *)0x0) {
        scrollbar_scalar_dtor(*(Control **)(self->rate_values + i * 4 + 0x18),1)
        ;
      }
      slot = self->rate_values + i * 4 + 0x18;
      slot[0] = '\0';
      slot[1] = '\0';
      slot[2] = '\0';
      slot[3] = '\0';
    }
    if (*(int *)(self->rate_values + i * 4 + 0x20) != 0) {
      if (*(Hotspot **)(self->rate_values + i * 4 + 0x20) != (Hotspot *)0x0) {
        hotspot_scalar_dtor(*(Hotspot **)(self->rate_values + i * 4 + 0x20),1);
      }
      slot = self->rate_values + i * 4 + 0x20;
      slot[0] = '\0';
      slot[1] = '\0';
      slot[2] = '\0';
      slot[3] = '\0';
    }
    if (*(int *)(self->rate_values + i * 4 + 0x28) != 0) {
      if (*(Control **)(self->rate_values + i * 4 + 0x28) != (Control *)0x0) {
        ctrl_scalar_dtor(*(Control **)(self->rate_values + i * 4 + 0x28),1)
        ;
      }
      slot = self->rate_values + i * 4 + 0x28;
      slot[0] = '\0';
      slot[1] = '\0';
      slot[2] = '\0';
      slot[3] = '\0';
    }
    if (*(int *)(self->rate_values + i * 4 + 0x30) != 0) {
      if (*(Control **)(self->rate_values + i * 4 + 0x30) != (Control *)0x0) {
        ctrl_scalar_dtor(*(Control **)(self->rate_values + i * 4 + 0x30),1)
        ;
      }
      slot = self->rate_values + i * 4 + 0x30;
      slot[0] = '\0';
      slot[1] = '\0';
      slot[2] = '\0';
      slot[3] = '\0';
    }
    if (*(int *)((u8 *)&self->advance_pane_rects + i * 4 - 0x24) != 0) {
      if (*(Control **)((u8 *)&self->advance_pane_rects + i * 4 - 0x24) != (Control *)0x0) {
        ctrl_scalar_dtor
                  (*(Control **)((u8 *)&self->advance_pane_rects + i * 4 - 0x24),1);
      }
      slot = (u8 *)&self->advance_pane_rects + i * 4 - 0x24;
      slot[0] = '\0';
      slot[1] = '\0';
      slot[2] = '\0';
      slot[3] = '\0';
    }
    if (*(int *)((u8 *)&self->advance_pane_rects + i * 4 - 0x1c) != 0) {
      if (*(Control **)((u8 *)&self->advance_pane_rects + i * 4 - 0x1c) != (Control *)0x0) {
        ctrl_scalar_dtor
                  (*(Control **)((u8 *)&self->advance_pane_rects + i * 4 - 0x1c),1);
      }
      slot = (u8 *)&self->advance_pane_rects + i * 4 - 0x1c;
      slot[0] = '\0';
      slot[1] = '\0';
      slot[2] = '\0';
      slot[3] = '\0';
    }
  }
  return;
}

/* 004b5c93 auto */
void __thiscall parley_wnd_create_controls(ViewWindow *self)

{
  u8 *slot_ptr;
  u32 wnd_width;
  int y_delta;
  LONG xLeft;
  i32 sprite_dim;
  int ctrl_width;
  int ctrl_left;
  Control *new_ctrl;
  int yTop;
  InputControl *new_edit;
  iptr label;
  u8 *counter_parent;
  u8 *no_thanks_parent;
  u8 *accept_parent;
  u8 *never_mind_parent;
  u8 *mode2_parent;
  u8 *mode_parent;
  u8 *intel_parent;
  u8 *reveal_parent;
  u8 *conceal_parent;
  int footer_line_h;
  u8 *clear_parent;
  u8 *send_parent;
  u8 *input_parent;
  int input_font_h4;
  int input_font_h3;
  int input_font_h2;
  int input_font_h1;
  u8 *history_parent;
  int hist_font_h4;
  int hist_font_h3;
  int hist_font_h2;
  int hist_font_h1;
  u8 *close_parent;
  iptr close_label;
  int close_line_h2;
  int close_line_h;
  u8 *caption_parent;
  uptr counter_button;
  uptr no_thanks_button;
  uptr accept_button;
  uptr never_mind_button;
  uptr mode2_button;
  uptr mode_button;
  uptr intel_button;
  uptr reveal_button;
  uptr conceal_button;
  uptr clear_button;
  uptr send_button;
  i8 *input_font;
  uptr input_edit;
  i8 *history_font;
  uptr history_edit;
  uptr close_btn;
  i8 *button_font;
  i32 hotspot;
  int ctrl_top;
  int caption_x;
  int i;
  tagRECT rect;
  int ctrl_height;
  i32 input_style;
  i32 unused_10;
  i8 *eh_prev;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  caption_x = panel_padding_x;
  for (i = 0; i < 3; i++) {
    if (i == 0) {
      *(i8 **)(self->close_caption_sprite_slot) = ((i8 *)&caption_close_button_sprite_block.caption_close_button_sprite);
    }
    else if (i == 1) {
      *(i8 **)(self->zoom_out_caption_sprite_slot) = ((i8 *)&caption_zoom_out_sprite);
    }
    else {
      *(i8 **)(self->parley_caption_buttons + i * 0x1c + 0x14) = ((i8 *)&caption_zoom_out_button_sprite_block.caption_zoom_out_button_sprite);
    }
    *(int *)(self->parley_caption_buttons + i * 0x1c) = i + 1;
    sprite_dim = sprite_width
                      (*(Sprite **)(self->parley_caption_buttons + i * 0x1c + 0x14));
    *(i32 *)(self->parley_caption_buttons + i * 0x1c + 0xc) = sprite_dim;
    sprite_dim = sprite_height
                      (*(Sprite **)(self->parley_caption_buttons + i * 0x1c + 0x14));
    *(i32 *)(self->parley_caption_buttons + i * 0x1c + 0x10) = sprite_dim;
    slot_ptr = self->caption_button_hotspots + i * 0x1c - 4;
    slot_ptr[0] = '\0';
    slot_ptr[1] = '\0';
    slot_ptr[2] = '\0';
    slot_ptr[3] = '\0';
    ctrl_width = (int)(*(int *)(self->parley_caption_buttons + i * 0x1c + 0xc) * self->client_width) / 0x18;
    ctrl_height = (int)(*(int *)(self->parley_caption_buttons + i * 0x1c + 0x10) * self->client_width) / 0x18;
    ctrl_left = ((int)self->client_width >> 1) - (ctrl_height >> 1);
    SetRect(&rect,caption_x,ctrl_left,ctrl_width + caption_x,ctrl_left + ctrl_height);
    new_ctrl = operator_new(0x40);
    eh_state = 0;
    if (new_ctrl == (Control *)0x0) {
      hotspot = 0;
    }
    else {
      hotspot = hotspot_ctor(new_ctrl);
    }
    eh_state = 0xffffffff;
    *(i32 *)(self->caption_button_hotspots + i * 0x1c - 4) = hotspot;
    if (self == (ViewWindow *)0x0) {
      caption_parent = (u8 *)0x0;
    }
    else {
      caption_parent = self->window_2;
    }
    hotspot_create
              (*(ClickControl **)(self->caption_button_hotspots + i * 0x1c - 4),(iptr)caption_parent,
               *(int *)(self->parley_caption_buttons + i * 0x1c) + 1000,(iptr)&rect);
    hotspot_set_click_callback(*(HotspotClickSetView **)(self->caption_button_hotspots + i * 0x1c - 4),(iptr)parley_wnd_on_caption_click);
    caption_x = caption_x + ctrl_width + panel_margin_x;
  }
  if (self->large_layout == 0) {
    button_font = ((i8 *)&font_size16);
  }
  else {
    button_font = ((i8 *)&font_size24);
  }
  ui_set_button_font((iptr)button_font);
  new_ctrl = operator_new(0x3c);
  eh_state = 1;
  if (new_ctrl == (Control *)0x0) {
    close_btn = 0;
  }
  else {
    close_btn = button_ctor(new_ctrl);
  }
  eh_state = 0xffffffff;
  self->close_button = close_btn;
  ctrl_width = panel_bevel_width + panel_margin_x + 2;
  if (self->large_layout == 0) {
    close_line_h = font_line_spacing((GameFont *)((i8 *)&font_size16));
  }
  else {
    close_line_h = font_line_spacing((GameFont *)((i8 *)&font_size24));
  }
  yTop = self->client_y - ((panel_margin_y + panel_padding_y) * 2 + close_line_h);
  wnd_width = self->client_x;
  y_delta = panel_margin_x * 2;
  ctrl_left = panel_bevel_width * 2;
  if (self->large_layout == 0) {
    close_line_h2 = font_line_spacing((GameFont *)((i8 *)&font_size16));
  }
  else {
    close_line_h2 = font_line_spacing((GameFont *)((i8 *)&font_size24));
  }
  ctrl_height = panel_padding_y * 2 + close_line_h2;
  SetRect(&rect,ctrl_width,yTop,(wnd_width - (y_delta + ctrl_left + 5)) + ctrl_width,yTop + ctrl_height);
  if (self->session_mode == 4) {
    close_label = label_string(*(i32 *)(label_string_ids + 0xb2c));
  }
  else {
    close_label = label_string(*(i32 *)(label_string_ids + 0xb30));
  }
  if (self == (ViewWindow *)0x0) {
    close_parent = (u8 *)0x0;
  }
  else {
    close_parent = self->window_2;
  }
  button_create
            ((Control *)self->close_button,(iptr)close_parent,0x3ed,(iptr)&rect,close_label);
  button_set_callback((Control *)self->close_button,(iptr)diplo_wnd_escape_close);
  new_edit = operator_new(0x48);
  eh_state = 2;
  if (new_edit == (InputControl *)0x0) {
    history_edit = 0;
  }
  else {
    history_edit = edit_ctor(new_edit);
  }
  eh_state = 0xffffffff;
  self->chat_history_edit = history_edit;
  ctrl_left = self->panel_rect + panel_margin_x;
  ctrl_width = rect_width((iptr)&self->panel_rect);
  ctrl_width += panel_margin_x * -2;
  if (self->session_mode == 4) {
    if (self->large_layout == 0) {
      hist_font_h3 = font_cached_height((GameFont *)((i8 *)&font_size14));
    }
    else {
      hist_font_h3 = font_cached_height((GameFont *)((i8 *)&font_size21));
    }
    ctrl_top = self->panel_bottom + (panel_margin_y + hist_font_h3) * -9;
    if (self->large_layout == 0) {
      hist_font_h4 = font_cached_height((GameFont *)((i8 *)&font_size14));
    }
    else {
      hist_font_h4 = font_cached_height((GameFont *)((i8 *)&font_size21));
    }
    ctrl_height = hist_font_h4 * 9 + panel_margin_y * 8;
  }
  else {
    if (self->large_layout == 0) {
      hist_font_h1 = font_cached_height((GameFont *)((i8 *)&font_size14));
    }
    else {
      hist_font_h1 = font_cached_height((GameFont *)((i8 *)&font_size21));
    }
    ctrl_top = self->panel_bottom + (panel_margin_y + hist_font_h1) * -6;
    if (self->large_layout == 0) {
      hist_font_h2 = font_cached_height((GameFont *)((i8 *)&font_size14));
    }
    else {
      hist_font_h2 = font_cached_height((GameFont *)((i8 *)&font_size21));
    }
    ctrl_height = panel_margin_y * 5 + hist_font_h2 * 6;
  }
  SetRect(&rect,ctrl_left,ctrl_top,ctrl_width + ctrl_left,ctrl_top + ctrl_height);
  if (self->large_layout == 0) {
    history_font = ((i8 *)&font_size14);
  }
  else {
    history_font = ((i8 *)&font_size21);
  }
  ui_set_default_font((iptr)history_font);
  if (self == (ViewWindow *)0x0) {
    history_parent = (u8 *)0x0;
  }
  else {
    history_parent = self->window_2;
  }
  edit_create_styled
            ((EditControl *)self->chat_history_edit,(iptr)history_parent,0x3ee,(iptr)&rect,(*(iptr *)&chat_log_buffer),
             0x122,0);
  edit_set_max_len((EditMaxLenView *)self->chat_history_edit,0x2000);
  edit_set_callback((EditCallbackSetView *)self->chat_history_edit,(iptr)parley_edit_escape_filter);
  ctrl_show_and_redraw((Control *)self->chat_history_edit);
  new_edit = operator_new(0x48);
  eh_state = 3;
  if (new_edit == (InputControl *)0x0) {
    input_edit = 0;
  }
  else {
    input_edit = edit_ctor(new_edit);
  }
  eh_state = 0xffffffff;
  self->chat_input_edit = input_edit;
  ctrl_width -= ctrl_width / 10;
  if (self->session_mode == 4) {
    if (self->large_layout == 0) {
      input_font_h3 = font_cached_height((GameFont *)((i8 *)&font_size14));
    }
    else {
      input_font_h3 = font_cached_height((GameFont *)((i8 *)&font_size21));
    }
    y_delta = panel_margin_y * -4 + input_font_h3 * -3;
    if (self->large_layout == 0) {
      input_font_h4 = font_cached_height((GameFont *)((i8 *)&font_size14));
    }
    else {
      input_font_h4 = font_cached_height((GameFont *)((i8 *)&font_size21));
    }
    ctrl_height = input_font_h4 * 3 + panel_margin_y * 3;
  }
  else {
    if (self->large_layout == 0) {
      input_font_h1 = font_cached_height((GameFont *)((i8 *)&font_size14));
    }
    else {
      input_font_h1 = font_cached_height((GameFont *)((i8 *)&font_size21));
    }
    y_delta = panel_margin_y * -3 + input_font_h1 * -2;
    if (self->large_layout == 0) {
      input_font_h2 = font_cached_height((GameFont *)((i8 *)&font_size14));
    }
    else {
      input_font_h2 = font_cached_height((GameFont *)((i8 *)&font_size21));
    }
    ctrl_height = panel_margin_y * 2 + input_font_h2 * 2;
  }
  ctrl_top += y_delta;
  SetRect(&rect,ctrl_left,ctrl_top,ctrl_width + ctrl_left,ctrl_top + ctrl_height);
  if (self->large_layout == 0) {
    input_font = ((i8 *)&font_size14);
  }
  else {
    input_font = ((i8 *)&font_size21);
  }
  ui_set_default_font((iptr)input_font);
  if (self->session_mode == 4) {
    input_style = 0x200;
  }
  else {
    input_style = 0x220;
  }
  if (self == (ViewWindow *)0x0) {
    input_parent = (u8 *)0x0;
  }
  else {
    input_parent = self->window_2;
  }
  edit_create_styled
            ((EditControl *)self->chat_input_edit,(iptr)input_parent,0x3ef,(iptr)&rect,(*(iptr *)&chat_input_buffer),
             input_style,0);
  edit_set_max_len((EditMaxLenView *)self->chat_input_edit,0x100);
  edit_set_callback((EditCallbackSetView *)self->chat_input_edit,(iptr)chat_input_on_key);
  ctrl_set_initial_focus((CtrlSetInitialFocusView *)self->chat_input_edit);
  ctrl_show_and_redraw((Control *)self->chat_input_edit);
  new_ctrl = operator_new(0x3c);
  eh_state = 4;
  if (new_ctrl == (Control *)0x0) {
    send_button = 0;
  }
  else {
    send_button = button_ctor(new_ctrl);
  }
  xLeft = rect.right;
  eh_state = 0xffffffff;
  self->send_button_value = send_button;
  ctrl_width = ctrl_width / 9;
  ctrl_height = ctrl_height / 2;
  SetRect(&rect,rect.right,ctrl_top,ctrl_width + rect.right,ctrl_top + ctrl_height);
  if (self == (ViewWindow *)0x0) {
    send_parent = (u8 *)0x0;
  }
  else {
    send_parent = self->window_2;
  }
  label = label_string(*(i32 *)(label_string_ids + 0xb34));
  button_create
            ((Control *)self->send_button_value,(iptr)send_parent,0x3f0,(iptr)&rect,label);
  button_set_callback((Control *)self->send_button_value,(iptr)chat_send_button_on_click);
  new_ctrl = operator_new(0x3c);
  eh_state = 5;
  if (new_ctrl == (Control *)0x0) {
    clear_button = 0;
  }
  else {
    clear_button = button_ctor(new_ctrl);
  }
  eh_state = 0xffffffff;
  self->clear_button_value = clear_button;
  ctrl_top += ctrl_height;
  SetRect(&rect,xLeft,ctrl_top,ctrl_width + xLeft,ctrl_top + ctrl_height);
  if (self == (ViewWindow *)0x0) {
    clear_parent = (u8 *)0x0;
  }
  else {
    clear_parent = self->window_2;
  }
  label = label_string(*(i32 *)(label_string_ids + 0xb38));
  button_create
            ((Control *)self->clear_button_value,(iptr)clear_parent,0x41e,(iptr)&rect,label);
  button_set_callback((Control *)self->clear_button_value,(iptr)chat_clear_button_on_click);
  ctrl_top -= ctrl_height;
  if (self->large_layout == 0) {
    footer_line_h = font_line_spacing((GameFont *)((i8 *)&font_size16));
  }
  else {
    footer_line_h = font_line_spacing((GameFont *)((i8 *)&font_size24));
  }
  ctrl_height = panel_padding_y * 2 + footer_line_h;
  ctrl_top -= (panel_margin_y + ctrl_height);
  self->show_turn_timer = ctrl_top - panel_margin_y;
  if (self->session_mode != 4) {
    new_ctrl = operator_new(0x3c);
    eh_state = 6;
    if (new_ctrl == (Control *)0x0) {
      conceal_button = 0;
    }
    else {
      conceal_button = button_ctor(new_ctrl);
    }
    eh_state = 0xffffffff;
    self->conceal_button_value = conceal_button;
    ctrl_width = self->panel_rect + panel_margin_x;
    ctrl_left = rect_width((iptr)&self->panel_rect);
    ctrl_left += panel_margin_x * -2;
    SetRect(&rect,ctrl_width,ctrl_top - ctrl_height,ctrl_left + ctrl_width,ctrl_top);
    if (self == (ViewWindow *)0x0) {
      conceal_parent = (u8 *)0x0;
    }
    else {
      conceal_parent = self->window_2;
    }
    label = label_string(*(i32 *)(label_string_ids + 0xdb4));
    button_create
              ((Control *)self->conceal_button_value,(iptr)conceal_parent,0x431,(iptr)&rect,label);
    button_set_callback((Control *)self->conceal_button_value,(iptr)parley_on_conceal_info);
    control_hide((Control *)self->conceal_button_value);
    ctrl_disable((Control *)self->conceal_button_value);
    new_ctrl = operator_new(0x3c);
    eh_state = 7;
    if (new_ctrl == (Control *)0x0) {
      reveal_button = 0;
    }
    else {
      reveal_button = button_ctor(new_ctrl);
    }
    eh_state = 0xffffffff;
    self->reveal_button_value = reveal_button;
    ctrl_width = self->panel_rect + panel_margin_x;
    SetRect(&rect,ctrl_width,ctrl_top - ctrl_height,ctrl_left + ctrl_width,ctrl_top);
    if (self == (ViewWindow *)0x0) {
      reveal_parent = (u8 *)0x0;
    }
    else {
      reveal_parent = self->window_2;
    }
    label = label_string(*(i32 *)(label_string_ids + 0xdb8));
    button_create
              ((Control *)self->reveal_button_value,(iptr)reveal_parent,0x432,(iptr)&rect,label);
    button_set_callback((Control *)self->reveal_button_value,(iptr)parley_on_reveal_info);
    control_hide((Control *)self->reveal_button_value);
    ctrl_disable((Control *)self->reveal_button_value);
    new_ctrl = operator_new(0x3c);
    eh_state = 8;
    if (new_ctrl == (Control *)0x0) {
      intel_button = 0;
    }
    else {
      intel_button = button_ctor(new_ctrl);
    }
    eh_state = 0xffffffff;
    self->intel_button_value = intel_button;
    ctrl_width = self->panel_rect + panel_margin_x;
    ctrl_left = rect_width((iptr)&self->panel_rect);
    ctrl_left = (ctrl_left + panel_margin_x * -2) / 3;
    SetRect(&rect,ctrl_width,ctrl_top,ctrl_left + ctrl_width,ctrl_top + ctrl_height);
    if (self == (ViewWindow *)0x0) {
      intel_parent = (u8 *)0x0;
    }
    else {
      intel_parent = self->window_2;
    }
    label = label_string(*(i32 *)(label_string_ids + 0x1a0));
    button_create
              ((Control *)self->intel_button_value,(iptr)intel_parent,0x428,(iptr)&rect,label);
    button_set_callback((Control *)self->intel_button_value,(iptr)parley_on_check_intel);
    ctrl_enable((Control *)self->intel_button_value);
    new_ctrl = operator_new(0x3c);
    eh_state = 9;
    if (new_ctrl == (Control *)0x0) {
      mode_button = 0;
    }
    else {
      mode_button = button_ctor(new_ctrl);
    }
    eh_state = 0xffffffff;
    self->rates_clamped = mode_button;
    SetRect(&rect,rect.right,ctrl_top,ctrl_left + rect.right,ctrl_top + ctrl_height);
    if (self == (ViewWindow *)0x0) {
      mode_parent = (u8 *)0x0;
    }
    else {
      mode_parent = self->window_2;
    }
    label = label_string(*(i32 *)(label_string_ids + 0xb3c));
    button_create
              ((Control *)self->rates_clamped,(iptr)mode_parent,0x3f1,(iptr)&rect,label);
    button_set_callback((Control *)self->rates_clamped,(iptr)parley_on_mode_chosen);
    ctrl_enable((Control *)self->rates_clamped);
    new_ctrl = operator_new(0x3c);
    eh_state = 10;
    if (new_ctrl == (Control *)0x0) {
      mode2_button = 0;
    }
    else {
      mode2_button = button_ctor(new_ctrl);
    }
    eh_state = 0xffffffff;
    self->mode2_button_value = mode2_button;
    if (self == (ViewWindow *)0x0) {
      mode2_parent = (u8 *)0x0;
    }
    else {
      mode2_parent = self->window_2;
    }
    label = label_string(*(i32 *)(label_string_ids + 0xd10));
    button_create
              ((Control *)self->mode2_button_value,(iptr)mode2_parent,0x427,(iptr)&rect,label);
    button_set_callback((Control *)self->mode2_button_value,(iptr)parley_on_mode_chosen);
    ctrl_disable((Control *)self->mode2_button_value);
    control_hide((Control *)self->mode2_button_value);
    new_ctrl = operator_new(0x3c);
    eh_state = 0xb;
    if (new_ctrl == (Control *)0x0) {
      never_mind_button = 0;
    }
    else {
      never_mind_button = button_ctor(new_ctrl);
    }
    eh_state = 0xffffffff;
    self->never_mind_button_value = never_mind_button;
    SetRect(&rect,rect.right,ctrl_top,ctrl_left + rect.right,ctrl_top + ctrl_height);
    if (self == (ViewWindow *)0x0) {
      never_mind_parent = (u8 *)0x0;
    }
    else {
      never_mind_parent = self->window_2;
    }
    label = label_string(*(i32 *)(label_string_ids + 0xb40));
    button_create
              ((Control *)self->never_mind_button_value,(iptr)never_mind_parent,0x3f2,(iptr)&rect,label);
    button_set_callback((Control *)self->never_mind_button_value,(iptr)parley_on_never_mind);
    new_ctrl = operator_new(0x3c);
    eh_state = 0xc;
    if (new_ctrl == (Control *)0x0) {
      accept_button = 0;
    }
    else {
      accept_button = button_ctor(new_ctrl);
    }
    eh_state = 0xffffffff;
    self->tax_scrollbar = accept_button;
    ctrl_width = self->panel_rect + panel_margin_x;
    ctrl_left = rect_width((iptr)&self->panel_rect);
    ctrl_left = (ctrl_left + panel_margin_x * -2) / 3;
    SetRect(&rect,ctrl_width,ctrl_top,ctrl_left + ctrl_width,ctrl_top + ctrl_height);
    if (self == (ViewWindow *)0x0) {
      accept_parent = (u8 *)0x0;
    }
    else {
      accept_parent = self->window_2;
    }
    label = label_string(*(i32 *)(label_string_ids + 0xb44));
    button_create
              ((Control *)self->tax_scrollbar,(iptr)accept_parent,0x3f2,(iptr)&rect,label);
    button_set_callback((Control *)self->tax_scrollbar,(iptr)parley_on_accept_offer);
    control_hide((Control *)self->tax_scrollbar);
    new_ctrl = operator_new(0x3c);
    eh_state = 0xd;
    if (new_ctrl == (Control *)0x0) {
      no_thanks_button = 0;
    }
    else {
      no_thanks_button = button_ctor(new_ctrl);
    }
    eh_state = 0xffffffff;
    self->no_thanks_button_value = no_thanks_button;
    SetRect(&rect,rect.right,ctrl_top,ctrl_left + rect.right,ctrl_top + ctrl_height);
    if (self == (ViewWindow *)0x0) {
      no_thanks_parent = (u8 *)0x0;
    }
    else {
      no_thanks_parent = self->window_2;
    }
    label = label_string(*(i32 *)(label_string_ids + 0xb48));
    button_create
              ((Control *)self->no_thanks_button_value,(iptr)no_thanks_parent,0x3f2,(iptr)&rect,label);
    button_set_callback((Control *)self->no_thanks_button_value,(iptr)parley_on_no_thanks);
    control_hide((Control *)self->no_thanks_button_value);
    new_ctrl = operator_new(0x3c);
    eh_state = 0xe;
    if (new_ctrl == (Control *)0x0) {
      counter_button = 0;
    }
    else {
      counter_button = button_ctor(new_ctrl);
    }
    eh_state = 0xffffffff;
    self->counter_button_value = counter_button;
    SetRect(&rect,rect.right,ctrl_top,ctrl_left + rect.right,ctrl_top + ctrl_height);
    if (self == (ViewWindow *)0x0) {
      counter_parent = (u8 *)0x0;
    }
    else {
      counter_parent = self->window_2;
    }
    label = label_string(*(i32 *)(label_string_ids + 0xb4c));
    button_create
              ((Control *)self->counter_button_value,(iptr)counter_parent,0x3f2,(iptr)&rect,label);
    button_set_callback((Control *)self->counter_button_value,(iptr)parley_on_counter_offer);
    control_hide((Control *)self->counter_button_value);
  }
  return;
}

/* 004b74c4 auto */
void __cdecl parley_wnd_on_caption_click(int control_id)

{
  iptr child_wnd;
  ParleyWindowLayout *parley_wnd_ptr;
  
  child_wnd = wnd_get_active_child();
  if (child_wnd == 0) {
    parley_wnd_ptr = (ParleyWindowLayout *)0x0;
  }
  else {
    parley_wnd_ptr = (ParleyWindowLayout *)(child_wnd - 0x48);
  }
  wnd_activate((Wnd *)parley_wnd_ptr->window_2);
  if (control_id == 0x3e9) {
    diplo_wnd_close_active();
  }
  else if (control_id == 0x3ea) {
    if (0 < (int)parley_wnd_ptr->large_layout) {
      wnd_hide((WndBase *)parley_wnd_ptr->window_2);
      parley_wnd_ptr->large_layout--;
      parley_wnd_calc_rect(parley_wnd_ptr);
      wnd_move_to_rect((WndBase *)parley_wnd_ptr->window_2,parley_wnd_ptr->init_rect);
      window_show((WindowObjectView *)parley_wnd_ptr);
    }
  }
  else if (((control_id == 0x3eb) && ((int)parley_wnd_ptr->large_layout < 1)) && (999 < caption_font_block.screen_width)) {
    wnd_hide((WndBase *)parley_wnd_ptr->window_2);
    parley_wnd_ptr->large_layout++;
    parley_wnd_calc_rect(parley_wnd_ptr);
    wnd_move_to_rect((WndBase *)parley_wnd_ptr->window_2,parley_wnd_ptr->init_rect);
    window_show((WindowObjectView *)parley_wnd_ptr);
  }
  return;
}

/* 004b7645 auto */
/* WARNING: Removing unreachable block (ram,0x004b766b) */

void __cdecl parley_wnd_close(void)

{
  wnd_set_active_child((iptr)&parley_wnd_block.parley_wnd_frame);
  diplo_wnd_close_active();
  return;
}

/* 004b768d auto */
/* WARNING: Removing unreachable block (ram,0x004b76b3) */

void __cdecl chat_wnd_close(void)

{
  wnd_set_active_child((iptr)&chat_wnd_block.chat_wnd_frame);
  diplo_wnd_close_active();
  return;
}

/* 004b7885 auto */
void __cdecl parley_wnd_redraw(void)

{
  iptr child_wnd;
  i32 caret_pos;
  ViewWindow *wnd2;
  
  child_wnd = wnd_get_active_child();
  if (child_wnd == 0) {
    wnd2 = (ViewWindow *)0x0;
  }
  else {
    wnd2 = (ViewWindow *)(child_wnd - 0x48);
  }
  if (wnd2->style_flags == 0) {
    parley_wnd_calc_layout((ParleyWindowLayout *)wnd2);
    parley_wnd_build_title((ParleyTitleView *)wnd2);
    gfx_set_draw_target((iptr)wnd2);
    parley_wnd_draw_frame((ParleyWindowLayout *)wnd2);
    parley_wnd_sync_sides(wnd2);
    wnd_blit_surface((DibSurface *)wnd2);
    window_show((WindowObjectView *)wnd2);
    caret_pos = edit_get_text_end((ControlTextView *)wnd2->chat_history_edit);
    edit_set_caret((ControlTextView *)wnd2->chat_history_edit,caret_pos);
    caret_pos = edit_get_sel_end((EditSelEndView *)wnd2->chat_input_edit);
    edit_set_caret((ControlTextView *)wnd2->chat_input_edit,caret_pos);
  }
  return;
}

/* 004b794a auto */
void __thiscall parley_wnd_draw_frame(ParleyWindowLayout *self)

{
  int free_width;
  int title_width;
  i8 sprite_rect[16];
  int icon_height;
  int icon_width;
  int y2;
  int x2;
  GameFont *title_font2;
  int i;
  tagRECT rect;
  
  surface_reset_clip((DibSurface *)self);
  crt_memcpy(&rect,&self->client_height,0x10);
  for (i = 0; i < panel_bevel_width; i++) {
    gfx_draw_bevel_rect((iptr)self,(iptr)&rect,(uint)dlg_bevel_light_color,(uint)dlg_bevel_dark_color);
    rect_deflate((iptr)&rect,1,1);
  }
  parley_fill_background((WindowObjectView *)self,(iptr)&rect,1);
  rect_deflate((iptr)&rect,panel_padding_x + panel_bevel_width * -2,0);
  rect.top = rect.top + self->client_width + panel_bevel_width * -2;
  free_width = rect_height((iptr)&self->client_height);
  rect.bottom = (free_width - self->client_width) + panel_bevel_width * -2;
  for (i = 0; i < panel_bevel_width; i++) {
    gfx_draw_bevel_rect((iptr)self,(iptr)&rect,(uint)dlg_bevel_dark_color,(uint)dlg_bevel_light_color);
    rect_deflate((iptr)&rect,1,1);
  }
  parley_fill_background((WindowObjectView *)self,(iptr)&rect,2);
  x2 = panel_padding_x;
  for (i = 0; i < 3; i++) {
    icon_width = (int)(*(int *)(((PortraitDialog *)self)->timer_seconds_digits + i * 0x1c + 0x8c) * self->client_width) / 0x18;
    icon_height = (int)(*(int *)(((PortraitDialog *)self)->timer_seconds_digits + i * 0x1c + 0x90) * self->client_width) / 0x18;
    y2 = ((int)self->client_width >> 1) - (icon_height >> 1);
    SetRect(&rect,x2,y2,icon_width + x2,icon_height + y2);
    gfx_set_scale_ratio(self->client_width,0x18);
    sprite_draw
              (*(Sprite **)(((PortraitDialog *)self)->timer_seconds_digits + i * 0x1c + 0x94),(iptr)sprite_rect,
               (iptr)self,x2,y2);
    gfx_reset_zoom_scale();
    x2 = x2 + panel_margin_x + icon_width;
  }
  if (self->large_layout == 0) {
    title_font2 = (GameFont *)((i8 *)&font_size20);
  }
  else {
    title_font2 = (GameFont *)((i8 *)&font_size30);
  }
  x2 -= panel_margin_x;
  free_width = (self->dlg_width - x2) - panel_padding_x;
  title_width = font_text_width(title_font2,(iptr)(u8 *)&self->parley_title);
  x2 += (free_width / 2 - (title_width >> 1));
  y2 = panel_bevel_width + panel_margin_y;
  gfx_set_text_color_index(10);
  surface_draw_text
            ((DibSurface *)self,(iptr)title_font2,(iptr)(u8 *)&self->parley_title,x2 + 2,y2 + 1,5);
  gfx_set_text_color_index(0x1a);
  surface_draw_text
            ((DibSurface *)self,(iptr)title_font2,(iptr)(u8 *)&self->parley_title,x2 + 1,y2,5);
  surface_draw_text
            ((DibSurface *)self,(iptr)title_font2,(iptr)(u8 *)&self->parley_title,x2,y2,5);
  surface_set_clip((DibSurface *)self,(iptr)&self->panel_rect);
  return;
}

/* 004b7c90 auto */
void __thiscall parley_fill_background(WindowObjectView *self,iptr rect,int area_kind)

{
  i32 height;
  i32 width;
  i32 tile_x;
  i32 tile_y;
  
  if ((dlg_frame_tile_surface == 0) || (area_kind != 1)) {
    if ((dlg_client_tile_surface == 0) || (area_kind != 2)) {
      gfx_fill_rect((iptr)self,rect,(uint)dlg_bg_color);
    }
    else {
      tile_y = 0;
      tile_x = 0;
      height = rect_height(rect);
      width = rect_width(rect);
      gfx_tile_fill((iptr)self,dlg_client_tile_surface,*(i32 *)rect,*(i32 *)(rect + 4)
                         ,width,height,tile_x,tile_y);
    }
  }
  else {
    tile_y = 0;
    tile_x = 0;
    height = rect_height(rect);
    width = rect_width(rect);
    gfx_tile_fill((iptr)self,dlg_frame_tile_surface,*(i32 *)rect,*(i32 *)(rect + 4),
                       width,height,tile_x,tile_y);
  }
  return;
}

/* 004b7d72 auto */
void __thiscall parley_wnd_build_title(ParleyTitleView *self)

{
  iptr text;
  iptr attitude_level;
  
  text_clear();
  if (self->parley_kind == 4) {
    text = label_string(*(i32 *)(label_string_ids + 0xb54));
    text_append(text);
    crt_strcpy(self->title_text,((i8 *)&map_views_block.text_buffer));
  }
  else {
    text = label_string(*(i32 *)(label_string_ids + 0xb50));
    text_append(text);
    text_append_space();
    text = civ_name_plural(self->civ_id);
    text_append(text);
    text_append_space();
    text_append_lparen();
    if (*(char *)&civs[(self->civ_id)].attitude[human_civ[0]] == '\0') {
      attitude_level = 0;
    }
    else {
      attitude_level = diplo_attitude_level((uint)civs[(self->civ_id)].attitude[human_civ[0]]);
    }
    text_append_string_id(attitude_names[attitude_level]);
    text_append_rparen();
    crt_strcpy(self->title_text,((i8 *)&map_views_block.text_buffer));
  }
  return;
}

/* 004b7eb6 auto */
/* WARNING: Removing unreachable block (ram,0x004b8008) */
/* WARNING: Removing unreachable block (ram,0x004b8051) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall parley_wnd_open(ViewWindow *self,iptr other_civ,u32 mode)

{
  bool can_see_all;
  bool has_contact;
  iptr has_wonder;
  iptr child_wnd;
  i32 caret_pos;
  int civ;
  ParleyTitleView *wnd2;
  
  if (mode == 4) {
    has_contact = false;
    if (((game.wonder_city[0x18] == -1) && (has_wonder = civ_has_wonder(human_civ[0],9), has_wonder == 0)
        ) && (game.reveal_map == '\0')) {
      can_see_all = false;
    }
    else {
      can_see_all = true;
    }
    for (civ = 1; civ < 8; civ++) {
      if ((((human_civ[0] != civ) &&
           ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0)) &&
          ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) &&
         (((can_see_all || (civ_saved_cursor_x_block.mp_chat_from_start != 0)) ||
          ((*(byte *)&civs[civ].treaties[human_civ[0]] & 1) != 0)))) {
        has_contact = true;
        break;
      }
    }
    if (!has_contact) {
      popup_game((iptr)&str_noforeignhuman);
      return;
    }
    wnd_set_active_child((iptr)&chat_wnd_block.chat_wnd_frame);
    net_session_block.chat_unread_count = 0;
    net_session_block.chat_missed_message_count_i32 = 0;
  }
  else {
    wnd_set_active_child((iptr)&parley_wnd_block.parley_wnd_frame);
    parley_wnd_block.parley_selected_action = 0xffffffff;
    self->right_side_accepted = '\0';
    self->left_side_accepted = '\0';
    self->left_side_confirmed = '\0';
    self->remote_side_agreed = '\0';
    if (mode == 3) {
      parley_set_mode_sides((WindowObjectView *)((i8 *)&parley_wnd_block.parley_wnd),0);
    }
  }
  child_wnd = wnd_get_active_child();
  if (child_wnd == 0) {
    wnd2 = (ParleyTitleView *)0x0;
  }
  else {
    wnd2 = (ParleyTitleView *)(child_wnd - 0x48);
  }
  if (*(int *)(wnd2->wnd_closed) == 0) {
    window_show((WindowObjectView *)wnd2);
  }
  else {
    wnd2->window_base[0x114] = '\0';
    wnd2->window_base[0x115] = '\0';
    wnd2->window_base[0x116] = '\0';
    wnd2->window_base[0x117] = '\0';
    wnd2->civ_id = other_civ;
    if (mode != 3) {
      wnd2->parley_kind = mode;
      *(i32 *)((ParleyTitleViewExt *)wnd2)->left_kind = (((i32 *)&parley_mode_left_kinds))[mode * 2];
      *(i32 *)(((ParleyTitleViewExt *)wnd2)->right_kind) = (((i32 *)&parley_mode_right_kinds))[mode * 2];
    }
    parley_wnd_build_title(wnd2);
    ((ParleyTitleViewExt *)wnd2)->shown_left_kind[0] = 21;
    ((ParleyTitleViewExt *)wnd2)->shown_left_kind_b1[0] = '\0';
    ((ParleyTitleViewExt *)wnd2)->shown_left_kind_b2[0] = '\0';
    ((ParleyTitleViewExt *)wnd2)->shown_left_kind_b3[0] = '\0';
    ((ParleyTitleViewExt *)wnd2)->shown_right_kind[0] = 21;
    ((ParleyTitleViewExt *)wnd2)->shown_right_kind_b1[0] = '\0';
    ((ParleyTitleViewExt *)wnd2)->shown_right_kind_b2[0] = '\0';
    ((ParleyTitleViewExt *)wnd2)->shown_right_kind_b3[0] = '\0';
    wnd_repaint((SurfaceWindow *)wnd2);
    window_show((WindowObjectView *)wnd2);
    caret_pos = edit_get_text_end(*(ControlTextView **)(((ParleyTitleViewExt *)wnd2)->chat_log_edit_2));
    edit_set_caret(*(ControlTextView **)(((ParleyTitleViewExt *)wnd2)->chat_log_edit_2),caret_pos);
    caret_pos = edit_get_sel_end(*(EditSelEndView **)(((ParleyTitleViewExt *)wnd2)->chat_input_edit));
    edit_set_caret(*(ControlTextView **)(((ParleyTitleViewExt *)wnd2)->chat_input_edit),caret_pos);
  }
  snd_play_effect(((uint)map.seed + other_civ & 7) + 0x53,1,0,0);
  return;
}

/* 004b81dd auto */
/* WARNING: Removing unreachable block (ram,0x004b8211) */

void __cdecl parley_poll_net_replies(void)

{
  iptr civ_name;
  
  net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
  wnd_set_active_child((iptr)&parley_wnd_block.parley_wnd_frame);
  if ((net_session_block.nm_parley_transaction_count == 0) || (parley_wnd_block.parley_mode != 2)) {
    if ((net_session_block.nm_parley_accept_offer_count == 0) || (parley_wnd_block.parley_mode != 1)) {
      if ((net_session_block.nm_parley_no_thanks_count == 0) || (parley_wnd_block.parley_mode != 1)) {
        if ((net_session_block.nm_parley_counter_offer_count != 0) && (parley_wnd_block.parley_mode == 1)) {
          net_session_block.nm_parley_counter_offer_count = 0;
          parley_wnd_block.parley_mode = 2;
          parley_wnd_block.parley_left_kind = parley_mode2_left_kind;
          parley_wnd_block.parley_right_kind = parley_mode2_right_kind;
          parley_wnd_block.parley_shown_left_kind = parley_wnd_block.parley_left_kind;
          parley_wnd_block.parley_shown_right_kind = parley_wnd_block.parley_right_kind;
          parley_add_side_dialog((ViewWindow *)((i8 *)&parley_wnd_block.parley_wnd),parley_mode2_left_kind,0);
          parley_add_side_dialog((ViewWindow *)((i8 *)&parley_wnd_block.parley_wnd),parley_wnd_block.parley_right_kind,1);
          civ_name = civ_name_plural(parley_wnd_block.parley_other_civ);
          text_set_string_arg(0,civ_name);
          dlg_pending_idle_callback = (i8*)(parley_poll_net_replies);
          popup_game_with_sprite((iptr)&str_parleycounteroffer,(iptr)&popup_info_icon_sprite,0);
        }
      }
      else {
        net_session_block.nm_parley_no_thanks_count = 0;
        parley_wnd_block.parley_mode = 3;
        parley_wnd_block.parley_selected_action = 0xffffffff;
        parley_set_mode_sides((WindowObjectView *)((i8 *)&parley_wnd_block.parley_wnd),1);
        civ_name = civ_name_plural(parley_wnd_block.parley_other_civ);
        text_set_string_arg(0,civ_name);
        dlg_pending_idle_callback = (i8*)(parley_poll_net_replies);
        popup_game_with_sprite((iptr)&str_parleynothanks,(iptr)&popup_info_icon_sprite,0);
      }
    }
    else {
      net_session_block.nm_parley_accept_offer_count = 0;
      if (parley_wnd_block.parley_received_offer != (void *)0x0) {
        *(i32 *)((int)parley_wnd_block.parley_received_offer + 4) = 0x86;
        if (net_session_block.net_host_flag == '\0') {
          net_send_message(0x86,0,0,0,0,0,0,0,0,(iptr)parley_wnd_block.parley_received_offer);
        }
        else {
          parley_execute_transaction((iptr)parley_wnd_block.parley_received_offer);
        }
        operator_delete(parley_wnd_block.parley_received_offer);
        parley_wnd_block.parley_received_offer = (void *)0x0;
      }
      parley_wnd_block.parley_mode = 2;
      parley_wnd_block.parley_left_kind = parley_mode2_left_kind;
      parley_wnd_block.parley_right_kind = parley_mode2_right_kind;
      parley_wnd_block.parley_shown_left_kind = parley_wnd_block.parley_left_kind;
      parley_wnd_block.parley_shown_right_kind = parley_wnd_block.parley_right_kind;
      parley_add_side_dialog((ViewWindow *)((i8 *)&parley_wnd_block.parley_wnd),parley_mode2_left_kind,0);
      parley_add_side_dialog((ViewWindow *)((i8 *)&parley_wnd_block.parley_wnd),parley_wnd_block.parley_right_kind,1);
      dlg_pending_idle_callback = (i8*)(parley_poll_net_replies);
      popup_game_with_sprite((iptr)&str_parleyaccept,(iptr)&popup_info_icon_sprite,0);
    }
  }
  else {
    net_session_block.nm_parley_transaction_count = 0;
    if ((*(int *)((int)parley_wnd_block.parley_received_offer + 0x10) == 6) && (*(int *)((int)parley_wnd_block.parley_received_offer + 0x28) == 3)) {
      civ_name = civ_name_plural(parley_wnd_block.parley_other_civ);
      text_set_string_arg(0,civ_name);
      civ_name = civ_name_plural(human_civ[0]);
      text_set_string_arg(1,civ_name);
      if ((*(byte *)&civs[human_civ[0]].treaties[parley_wnd_block.parley_other_civ] & 8) == 0) {
        if ((*(byte *)&civs[human_civ[0]].treaties[parley_wnd_block.parley_other_civ] & 4) == 0) {
          if ((*(byte *)&civs[human_civ[0]].treaties[parley_wnd_block.parley_other_civ] & 2) != 0) {
            diplo_clear_treaty_flags(human_civ[0],parley_wnd_block.parley_other_civ,2);
            popup_game((iptr)&str_breakcease);
          }
        }
        else {
          diplo_clear_treaty_flags(human_civ[0],parley_wnd_block.parley_other_civ,4);
          popup_game((iptr)&str_cancelpeace);
        }
      }
      else {
        diplo_clear_treaty_flags(human_civ[0],parley_wnd_block.parley_other_civ,8);
        popup_game((iptr)&str_cancelallied);
      }
    }
    else {
      parley_wnd_block.parley_mode = 0;
      parley_wnd_block.parley_left_kind = parley_mode_left_kinds[0];
      parley_wnd_block.parley_right_kind = parley_mode_right_kinds[0];
      parley_wnd_block.parley_shown_left_kind = parley_wnd_block.parley_left_kind;
      parley_wnd_block.parley_shown_right_kind = parley_wnd_block.parley_right_kind;
      parley_add_side_dialog((ViewWindow *)((i8 *)&parley_wnd_block.parley_wnd),parley_mode_left_kinds[0],0);
      parley_add_side_dialog((ViewWindow *)((i8 *)&parley_wnd_block.parley_wnd),parley_wnd_block.parley_right_kind,1);
    }
  }
  return;
}

/* 004b8676 auto */
/* WARNING: Removing unreachable block (ram,0x004b869f) */

void __thiscall parley_set_mode_sides(WindowObjectView *self,int refresh)

{
  wnd_set_active_child((iptr)&parley_wnd_block.parley_wnd_frame);
  if (parley_wnd_block.parley_selected_action == -1) {
    parley_wnd_block.parley_mode = 3;
    ctrl_disable(parley_wnd_block.parley_never_mind_button);
  }
  else if (parley_wnd_block.parley_selected_action == 0) {
    parley_wnd_block.parley_mode = 6;
    ctrl_enable(parley_wnd_block.parley_never_mind_button);
  }
  else if (parley_wnd_block.parley_selected_action == 1) {
    parley_wnd_block.parley_mode = 0xc;
    if (parley_wnd_block.parley_proposal_kind != 0) {
      parley_wnd_block.parley_mode = 0xd;
    }
    ctrl_enable(parley_wnd_block.parley_never_mind_button);
  }
  else if (parley_wnd_block.parley_selected_action == 2) {
    if (parley_wnd_block.parley_gift_kind == 0) {
      parley_wnd_block.parley_mode = 7;
    }
    else if (parley_wnd_block.parley_gift_kind == 1) {
      parley_wnd_block.parley_mode = 8;
    }
    else if (parley_wnd_block.parley_gift_kind == 2) {
      parley_wnd_block.parley_mode = 9;
    }
    else if (parley_wnd_block.parley_gift_kind == 3) {
      parley_wnd_block.parley_mode = 10;
    }
    else {
      parley_wnd_block.parley_mode = 0xb;
    }
    ctrl_enable(parley_wnd_block.parley_never_mind_button);
  }
  else if (parley_wnd_block.parley_selected_action == 3) {
    parley_wnd_block.parley_mode = 5;
    ctrl_enable(parley_wnd_block.parley_never_mind_button);
  }
  else if (parley_wnd_block.parley_selected_action == 4) {
    parley_wnd_block.parley_mode = 0xf;
    ctrl_enable(parley_wnd_block.parley_never_mind_button);
  }
  parley_wnd_block.parley_left_kind = (((i32 *)&parley_mode_left_kinds))[parley_wnd_block.parley_mode * 2];
  parley_wnd_block.parley_right_kind = (((i32 *)&parley_mode_right_kinds))[parley_wnd_block.parley_mode * 2];
  parley_wnd_block.parley_shown_left_kind = parley_wnd_block.parley_left_kind;
  parley_wnd_block.parley_shown_right_kind = parley_wnd_block.parley_right_kind;
  if (refresh != 0) {
    parley_add_side_dialog((ViewWindow *)((i8 *)&parley_wnd_block.parley_wnd),parley_wnd_block.parley_left_kind,0);
    parley_add_side_dialog((ViewWindow *)((i8 *)&parley_wnd_block.parley_wnd),parley_wnd_block.parley_right_kind,1);
  }
  return;
}

/* 004b888e auto */
void __thiscall parley_clear_side_controls(ViewWindow *self,int side)

{
  u8 *slot_ptr;
  int half_width;
  int i;
  
  if ((side != 0) && (side != 1)) {
    err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_leftright_left_leftright_right,(iptr)&str_d_ss_franklinton_parleywin_cpp,0x4ea);
  }
  if (side == 1) {
    if (self->side_text_edit != 0) {
      if ((Control *)self->side_text_edit != (Control *)0x0) {
        edit_scalar_dtor((Control *)self->side_text_edit,1);
      }
      self->side_text_edit = 0;
    }
    if (self->sci_rate_sel != 0) {
      if ((Checkbox *)self->sci_rate_sel != (Checkbox *)0x0) {
        checkbox_scalar_dtor((Checkbox *)self->sci_rate_sel,1);
      }
      self->sci_rate_sel = 0;
    }
    if (self->init_tax_rate != 0) {
      if ((Checkbox *)self->init_tax_rate != (Checkbox *)0x0) {
        checkbox_scalar_dtor((Checkbox *)self->init_tax_rate,1);
      }
      self->init_tax_rate = 0;
    }
    if (self->init_lux_rate != 0) {
      if ((Checkbox *)self->init_lux_rate != (Checkbox *)0x0) {
        checkbox_scalar_dtor((Checkbox *)self->init_lux_rate,1);
      }
      self->init_lux_rate = 0;
    }
    for (i = 0; i < 8; i++) {
      if (*(int *)(self->parley_checkboxes + i * 4 - 0x1c) != 0) {
        if (*(Checkbox **)(self->parley_checkboxes + i * 4 - 0x1c) != (Checkbox *)0x0) {
          checkbox_scalar_dtor(*(Checkbox **)(self->parley_checkboxes + i * 4 - 0x1c),1);
        }
        slot_ptr = self->parley_checkboxes + i * 4 - 0x1c;
        slot_ptr[0] = '\0';
        slot_ptr[1] = '\0';
        slot_ptr[2] = '\0';
        slot_ptr[3] = '\0';
      }
      if (*(int *)(self->parley_checkboxes + i * 4 + 4) != 0) {
        if (*(Checkbox **)(self->parley_checkboxes + i * 4 + 4) != (Checkbox *)0x0) {
          checkbox_scalar_dtor(*(Checkbox **)(self->parley_checkboxes + i * 4 + 4),1);
        }
        slot_ptr = self->parley_checkboxes + i * 4 + 4;
        slot_ptr[0] = '\0';
        slot_ptr[1] = '\0';
        slot_ptr[2] = '\0';
        slot_ptr[3] = '\0';
      }
    }
  }
  if (*(int *)(self->rate_values + side * 4) != 0) {
    if (*(Checkbox **)(self->rate_values + side * 4) != (Checkbox *)0x0) {
      checkbox_scalar_dtor(*(Checkbox **)(self->rate_values + side * 4),1);
    }
    slot_ptr = self->rate_values + side * 4;
    slot_ptr[0] = '\0';
    slot_ptr[1] = '\0';
    slot_ptr[2] = '\0';
    slot_ptr[3] = '\0';
  }
  if (*(int *)(self->rate_values + side * 4 + 8) != 0) {
    if (*(RadioGroupDtorView **)(self->rate_values + side * 4 + 8) != (RadioGroupDtorView *)0x0) {
      radiogrp_scalar_dtor(*(RadioGroupDtorView **)(self->rate_values + side * 4 + 8),1);
    }
    slot_ptr = self->rate_values + side * 4 + 8;
    slot_ptr[0] = '\0';
    slot_ptr[1] = '\0';
    slot_ptr[2] = '\0';
    slot_ptr[3] = '\0';
  }
  if (*(int *)(self->rate_values + side * 4 + 0x10) != 0) {
    if (*(Control **)(self->rate_values + side * 4 + 0x10) != (Control *)0x0) {
      edit_scalar_dtor(*(Control **)(self->rate_values + side * 4 + 0x10),1);
    }
    slot_ptr = self->rate_values + side * 4 + 0x10;
    slot_ptr[0] = '\0';
    slot_ptr[1] = '\0';
    slot_ptr[2] = '\0';
    slot_ptr[3] = '\0';
  }
  if (*(int *)(self->rate_values + side * 4 + 0x18) != 0) {
    if (*(Control **)(self->rate_values + side * 4 + 0x18) != (Control *)0x0) {
      scrollbar_scalar_dtor(*(Control **)(self->rate_values + side * 4 + 0x18),1);
    }
    slot_ptr = self->rate_values + side * 4 + 0x18;
    slot_ptr[0] = '\0';
    slot_ptr[1] = '\0';
    slot_ptr[2] = '\0';
    slot_ptr[3] = '\0';
  }
  if (*(int *)(self->rate_values + side * 4 + 0x20) != 0) {
    if (*(Hotspot **)(self->rate_values + side * 4 + 0x20) != (Hotspot *)0x0) {
      hotspot_scalar_dtor(*(Hotspot **)(self->rate_values + side * 4 + 0x20),1);
    }
    slot_ptr = self->rate_values + side * 4 + 0x20;
    slot_ptr[0] = '\0';
    slot_ptr[1] = '\0';
    slot_ptr[2] = '\0';
    slot_ptr[3] = '\0';
  }
  if (*(int *)(self->rate_values + side * 4 + 0x28) != 0) {
    if (*(Control **)(self->rate_values + side * 4 + 0x28) != (Control *)0x0) {
      ctrl_scalar_dtor(*(Control **)(self->rate_values + side * 4 + 0x28),1);
    }
    slot_ptr = self->rate_values + side * 4 + 0x28;
    slot_ptr[0] = '\0';
    slot_ptr[1] = '\0';
    slot_ptr[2] = '\0';
    slot_ptr[3] = '\0';
  }
  if (*(int *)(self->rate_values + side * 4 + 0x30) != 0) {
    if (*(Control **)(self->rate_values + side * 4 + 0x30) != (Control *)0x0) {
      ctrl_scalar_dtor(*(Control **)(self->rate_values + side * 4 + 0x30),1);
    }
    slot_ptr = self->rate_values + side * 4 + 0x30;
    slot_ptr[0] = '\0';
    slot_ptr[1] = '\0';
    slot_ptr[2] = '\0';
    slot_ptr[3] = '\0';
  }
  if (*(int *)((u8 *)&self->advance_pane_rects + side * 4 - 0x24) != 0) {
    if (*(Control **)((u8 *)&self->advance_pane_rects + side * 4 - 0x24) != (Control *)0x0) {
      ctrl_scalar_dtor(*(Control **)((u8 *)&self->advance_pane_rects + side * 4 - 0x24),1);
    }
    slot_ptr = (u8 *)&self->advance_pane_rects + side * 4 - 0x24;
    slot_ptr[0] = '\0';
    slot_ptr[1] = '\0';
    slot_ptr[2] = '\0';
    slot_ptr[3] = '\0';
  }
  if (*(int *)((u8 *)&self->advance_pane_rects + side * 4 - 0x1c) != 0) {
    if (*(Control **)((u8 *)&self->advance_pane_rects + side * 4 - 0x1c) != (Control *)0x0) {
      ctrl_scalar_dtor(*(Control **)((u8 *)&self->advance_pane_rects + side * 4 - 0x1c),1);
    }
    slot_ptr = (u8 *)&self->advance_pane_rects + side * 4 - 0x1c;
    slot_ptr[0] = '\0';
    slot_ptr[1] = '\0';
    slot_ptr[2] = '\0';
    slot_ptr[3] = '\0';
  }
  self->fill_rect_left = self->panel_rect;
  self->fill_rect_top = self->panel_top;
  self->fill_rect_right = self->panel_right;
  self->fill_rect_bottom = self->panel_bottom;
  self->fill_rect_bottom = self->show_turn_timer;
  if (side == 0) {
    half_width = rect_width((iptr)&self->panel_rect);
    self->fill_rect_right = half_width / 2;
  }
  else {
    half_width = rect_width((iptr)&self->panel_rect);
    self->fill_rect_left = half_width / 2;
  }
  parley_fill_background((WindowObjectView *)self,(iptr)&self->fill_rect_left,2);
  return;
}

/* 004b8e5c auto */
void __cdecl parley_gold_edit_on_change(int control_id)

{
  char *src_ptr;
  size_t len;
  int amount;
  size_t text_len;
  uptr i;
  char gold_text[32];
  uint edit_index;
  i32 modified;
  char text[32];
  uint caret;
  
  modified = 0;
  _memset(text,0,0x20);
  _memset(gold_text,0,0x20);
  edit_index = (uint)(control_id != 0x3f8);
  caret = edit_get_sel_end(*(EditSelEndView **)(((i8 *)&parley_wnd_block.parley_gold_edits) + edit_index * 4));
  ctrl_get_text(*(ControlTextView **)(((i8 *)&parley_wnd_block.parley_gold_edits) + edit_index * 4),(iptr)text);
  __itoa(civs[human_civ[0]].gold,gold_text,10);
  for (i = 0; len = _strlen(text), i < len; i++) {
    if ((text[i] < '0') || ('9' < text[i])) {
      modified = 1;
      crt_strcpy(text + i,text + i + 1);
    }
  }
  amount = _atoi(text);
  if (((parley_wnd_block.parley_mode == 0xe) && (edit_index == 0)) || ((parley_wnd_block.parley_mode != 0xf && (parley_wnd_block.parley_mode != 0xe)))
     ) {
    len = _strlen(gold_text);
    text_len = _strlen(text);
    if ((len < text_len) || (civs[human_civ[0]].gold < amount)) {
      modified = 1;
      src_ptr = text + caret;
      amount = caret - 1;
      caret--;
      crt_strcpy(text + amount,src_ptr);
    }
  }
  amount = _atoi(text);
  if (amount < 1) {
    *(i32 *)(((i8 *)&parley_wnd_block.parley_gold_entered) + edit_index * 4) = 0;
  }
  else {
    *(i32 *)(((i8 *)&parley_wnd_block.parley_gold_entered) + edit_index * 4) = 1;
  }
  parley_update_buttons((ViewWindow *)((i8 *)&parley_wnd_block.parley_wnd));
  if (modified != 0) {
    len = _strlen(text);
    if (len < caret) {
      caret = _strlen(text);
    }
    ctrl_set_text(*(ControlTextView **)(((i8 *)&parley_wnd_block.parley_gold_edits) + edit_index * 4),(iptr)text);
    edit_set_caret(*(ControlTextView **)(((i8 *)&parley_wnd_block.parley_gold_edits) + edit_index * 4),caret);
  }
  return;
}

/* 004b90ad auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall
chat_receive_message(WindowObjectView *self,iptr civ,iptr civ2,iptr is_private,iptr message)

{
  u32 muted;
  size_t log_len;
  i32 label;
  int listener;
  
  ctrl_get_text(chat_wnd_block.chat_log_edit,(iptr)chat_log_buffer);
  text_clear();
  log_len = _strlen(chat_log_buffer);
  if (log_len != 0) {
    crt_strcat(((i8 *)&map_views_block.text_buffer),((i8 *)&chat_recv_newline_str));
  }
  if ((char)is_private == '\0') {
    label = label_string(*(i32 *)(label_string_ids + 0xb60));
    crt_strcat(((i8 *)&map_views_block.text_buffer),label);
    text_append_space();
    chat_append_sender_name(civ);
    crt_strcat(((i8 *)&map_views_block.text_buffer),((i8 *)&chat_recv_year_open_str));
    text_append_year((int)game.year);
    crt_strcat(((i8 *)&map_views_block.text_buffer),((i8 *)&chat_recv_year_close_str));
  }
  else {
    label = label_string(*(i32 *)(label_string_ids + 0xb58));
    crt_strcat(((i8 *)&map_views_block.text_buffer),label);
    text_append_space();
    chat_append_sender_name(civ);
    label = label_string(*(i32 *)(label_string_ids + 0xb5c));
    crt_strcat(((i8 *)&map_views_block.text_buffer),label);
    text_append_space();
    chat_append_sender_name(civ2);
    crt_strcat(((i8 *)&map_views_block.text_buffer),((i8 *)&chat_recv_private_year_open_str));
    text_append_year((int)game.year);
    crt_strcat(((i8 *)&map_views_block.text_buffer),((i8 *)&chat_recv_private_year_close_str));
  }
  crt_strcat(((i8 *)&map_views_block.text_buffer),message);
  if ((civ == 0) && (chat_wnd_block.chat_mute_anonymous != 0)) {
    return;
  }
  if ((char)is_private == '\0') {
    if (parley_wnd_block.parley_wnd_closed == 0) {
      if (parley_wnd_block.parley_other_civ == civ) goto relay_to_listeners;
      muted = ((u32 *)&((PediaRedrawView *)self)->civ_muted_flags)[civ];
    }
    else {
      muted = ((u32 *)&((PediaRedrawView *)self)->civ_muted_flags)[civ];
    }
    if (muted != 0) {
      return;
    }
  }
relay_to_listeners:
  for (listener = 1; listener < 8; listener++) {
    if ((((listener != civ) && (human_civ[0] != listener)) &&
        ((1 << ((byte)listener & 0x1f) & (uint)game.human_players) != 0)) &&
       ((*(byte *)(listener * 0x594 + (iptr)((u8 *)&civs + 35) + human_civ[0] * 4) & 1) != 0)) {
      net_send_message(0x68,*(i32 *)
                               (((i8 *)&net_session_block.net_player_slots) + *(int *)(((i8 *)&net_session_block.net_civ_slots) + listener * 4) * 0x54),
                         civ,civ2,1,0,0,0,message,0);
    }
  }
  chat_log_append((iptr)&map_views_block.text_buffer);
  if (chat_wnd_block.chat_wnd_closed != 0) {
    net_session_block.chat_unread_count++;
    net_session_block.chat_missed_message_count_i32++;
  }
  if ((parley_wnd_block.parley_wnd_closed != 0) && (chat_wnd_block.chat_wnd_closed != 0)) {
    parley_wnd_open((ViewWindow *)((i8 *)&chat_wnd_block.chat_wnd),0,4);
  }
  return;
}

/* 004b93a2 auto */
void __cdecl chat_log_append(iptr line)

{
  int capacity;
  size_t log_len;
  size_t line_len;
  i32 caret_pos;
  uptr trim_len;
  
  capacity = font_size16_bold_block.chat_log_capacity;
  trim_len = 0;
  log_len = _strlen(chat_log_buffer);
  line_len = _strlen((char *)line);
  if (capacity - (log_len + 1) < line_len + 1) {
    trim_len = _strlen((char *)line);
    do {
      trim_len++;
      if ((chat_log_buffer[trim_len] == '\r') || (chat_log_buffer[trim_len] == '\n')) break;
    } while (chat_log_buffer[trim_len] != '\0');
    if (chat_log_buffer[trim_len] != '\0') {
      for (; (chat_log_buffer[trim_len] == '\r' || (chat_log_buffer[trim_len] == '\n'));
          trim_len = trim_len + 1) {
      }
    }
  }
  crt_strcpy(chat_log_buffer,chat_log_buffer + trim_len);
  crt_strcat(chat_log_buffer,line);
  ctrl_set_text(chat_wnd_block.chat_log_edit,(iptr)chat_log_buffer);
  ctrl_set_text(parley_wnd_block.parley_chat_log_edit,(iptr)chat_log_buffer);
  caret_pos = edit_get_text_end(chat_wnd_block.chat_log_edit);
  edit_set_caret(chat_wnd_block.chat_log_edit,caret_pos);
  caret_pos = edit_get_text_end(chat_wnd_block.chat_log_edit);
  edit_set_caret(parley_wnd_block.parley_chat_log_edit,caret_pos);
  return;
}

/* 004b9504 auto */
void __cdecl chat_append_sender_name(int civ)

{
  i32 name_text;
  
  if (civ == 0) {
    name_text = label_string(*(i32 *)(label_string_ids + 0xb64));
    crt_strcat(((i8 *)&map_views_block.text_buffer),name_text);
  }
  else {
    name_text = civ_leader_title(civ);
    crt_strcat(((i8 *)&map_views_block.text_buffer),name_text);
    text_append_space();
    name_text = civ_leader_name(civ);
    crt_strcat(((i8 *)&map_views_block.text_buffer),name_text);
  }
  return;
}

/* 004b957e auto */
void __cdecl parley_wnd_on_key(int key)

{
  if (key == 0xd2) {
    diplo_wnd_escape_close(0);
  }
  return;
}

/* 004b95c2 auto */
void __cdecl chat_send_button_on_click(void)

{
  chat_input_on_key(0,0xd0);
  return;
}

/* 004b95e1 auto */
void __cdecl chat_clear_button_on_click(void)

{
  _memset((*(void * *)&chat_log_buffer),0,font_size16_bold_block.chat_log_capacity + 1);
  ctrl_set_text(chat_wnd_block.chat_log_edit,(iptr)(*(void * *)&chat_log_buffer));
  ctrl_set_text(parley_wnd_block.parley_chat_log_edit,(iptr)(*(void * *)&chat_log_buffer));
  ctrl_set_focus(parley_wnd_block.parley_chat_input_edit);
  return;
}

/* 004b9635 auto */
i32 __cdecl parley_edit_escape_filter(i32 control,int key)

{
  i32 result;
  
  if ((key == 0x1b) || (key == 0xd2)) {
    diplo_wnd_escape_close(0);
    result = 0;
  }
  else {
    result = 1;
  }
  return result;
}

/* 004b968a auto */
i32 __cdecl chat_input_on_key(i32 control,int key)

{
  iptr child_wnd;
  size_t len;
  i32 label;
  iptr relay_sender;
  iptr sender;
  int count;
  int civ;
  iptr wnd2;
  
  child_wnd = wnd_get_active_child();
  if (child_wnd == 0) {
    wnd2 = 0;
  }
  else {
    wnd2 = child_wnd - 0x48;
  }
  if (key < 0x2b5) {
    if (0x2af < key) {
      chat_insert_macro_text(*(i32 *)(wnd2 + 0x298),key);
      return 0;
    }
    if (key == 0xd0) {
      ctrl_get_text(*(ControlTextView **)(wnd2 + 0x298),(iptr)(*(char * *)&chat_input_buffer));
      len = _strlen((*(char * *)&chat_input_buffer));
      if (len == 0) {
        return 0;
      }
      ctrl_get_text(chat_wnd_block.chat_log_edit,(iptr)chat_log_buffer);
      text_clear();
      len = _strlen(chat_log_buffer);
      if (len != 0) {
        crt_strcat(((i8 *)&map_views_block.text_buffer),((i8 *)&chat_send_newline_str));
      }
      label = label_string(*(i32 *)(label_string_ids + 0xb68));
      crt_strcat(((i8 *)&map_views_block.text_buffer),label);
      text_append_space();
      if (*(int *)(wnd2 + 0x1ec) == 4) {
        count = 0;
        for (civ = 1; civ < 8; civ++) {
          if (*(int *)(((i8 *)&chat_wnd_block.chat_send_to_civs) + civ * 4) != 0) {
            if (count != 0) {
              crt_strcat(((i8 *)&map_views_block.text_buffer),((i8 *)&chat_send_recipient_sep_str));
            }
            chat_append_sender_name(civ);
            count++;
          }
        }
      }
      else {
        chat_append_sender_name(*(i32 *)(wnd2 + 0x118));
        count = 1;
      }
      if (count == 0) {
        return 0;
      }
      crt_strcat(((i8 *)&map_views_block.text_buffer),((i8 *)&chat_send_year_open_str));
      text_append_year((int)game.year);
      crt_strcat(((i8 *)&map_views_block.text_buffer),((i8 *)&chat_send_year_close_str));
      crt_strcat(((i8 *)&map_views_block.text_buffer),(*(char * *)&chat_input_buffer));
      chat_log_append((iptr)&map_views_block.text_buffer);
      if (*(int *)(wnd2 + 0x1ec) == 4) {
        for (civ = 1; civ < 8; civ++) {
          if ((((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) &&
              (human_civ[0] != civ)) && (*(int *)(((i8 *)&chat_wnd_block.chat_send_to_civs) + civ * 4) != 0)) {
            if (chat_wnd_block.chat_remain_anonymous == 0) {
              sender = human_civ[0];
            }
            else {
              sender = 0;
            }
            net_send_message(0x68,*(i32 *)
                                     (((i8 *)&net_session_block.net_player_slots) + *(int *)(((i8 *)&net_session_block.net_civ_slots) + civ * 4) * 0x54),
                               sender,civ,0,0,0,0,(iptr)(*(char * *)&chat_input_buffer),0);
            for (count = 1; count < 8; count++) {
              if ((((1 << ((byte)count & 0x1f) & (uint)game.human_players) != 0) &&
                  (human_civ[0] != count)) &&
                 ((count != civ &&
                  ((*(byte *)(count * 0x594 + (iptr)((u8 *)&civs + 35) + human_civ[0] * 4) & 1) != 0)))) {
                if (chat_wnd_block.chat_remain_anonymous == 0) {
                  relay_sender = human_civ[0];
                }
                else {
                  relay_sender = 0;
                }
                net_send_message(0x68,*(i32 *)
                                         (((i8 *)&net_session_block.net_player_slots) +
                                         *(int *)(((i8 *)&net_session_block.net_civ_slots) + count * 4) * 0x54),relay_sender,
                                   civ,1,0,0,0,(iptr)(*(char * *)&chat_input_buffer),0);
              }
            }
          }
        }
      }
      else {
        net_send_message(0x68,*(i32 *)
                                 (((i8 *)&net_session_block.net_player_slots) +
                                 *(int *)(((i8 *)&net_session_block.net_civ_slots) + *(int *)(wnd2 + 0x118) * 4) * 0x54),
                           human_civ[0],*(iptr *)(wnd2 + 0x118),0,0,0,0,(iptr)(*(char * *)&chat_input_buffer),0);
        for (count = 1; count < 8; count++) {
          if ((((1 << ((byte)count & 0x1f) & (uint)game.human_players) != 0) &&
              (human_civ[0] != count)) &&
             ((*(int *)(wnd2 + 0x118) != count &&
              ((*(byte *)(count * 0x594 + (iptr)((u8 *)&civs + 35) + human_civ[0] * 4) & 1) != 0)))) {
            net_send_message(0x68,*(i32 *)
                                     (((i8 *)&net_session_block.net_player_slots) + *(int *)(((i8 *)&net_session_block.net_civ_slots) + count * 4) * 0x54)
                               ,human_civ[0],*(iptr *)(wnd2 + 0x118),1,0,0,0,(iptr)(*(char * *)&chat_input_buffer),
                               0);
          }
        }
      }
      *(*(char * *)&chat_input_buffer) = '\0';
      ctrl_set_text(*(ControlTextView **)(wnd2 + 0x298),(iptr)(*(char * *)&chat_input_buffer));
      ctrl_set_focus(*(ControlFocusView **)(wnd2 + 0x298));
      return 0;
    }
    if (key == 0xd2) {
      diplo_wnd_escape_close(0);
      return 0;
    }
  }
  return 1;
}

/* 004db690 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 * __thiscall parley_send_offer(ParleyOfferBuffer *self,int mode)

{
  i32 offer_kind;
  i32 *msg;
  int left_items;
  int i;
  uint total_size;
  int right_size;
  int left_size;
  
  offer_kind = *(i32 *)(((i8 *)&parley_offer_kinds) + mode * 4);
  parley_wnd_block.parley_offer_left_count_i32 = 0;
  parley_wnd_block.parley_offer_right_count_i32 = 0;
  right_size = *(int *)(((i8 *)&parley_item_header_sizes) + self->offer_type_right * 4);
  switch(self->offer_type_right) {
  case 8:
  case 0xc:
    for (i = 0; i < parley_wnd_block.parley_list_count_right; i++) {
      if (*(int *)(((i8 *)&parley_wnd_block.parley_list_selected_right) + i * 4) == 1) {
        parley_wnd_block.parley_offer_right_count_i32++;
      }
    }
    right_size = self->selected_count_right * 4 + right_size;
    break;
  case 10:
  case 0x11:
    for (i = 0; i < parley_wnd_block.parley_list_count_right; i++) {
      if (*(int *)(((i8 *)&parley_wnd_block.parley_list_selected_right) + i * 4) == 1) {
        parley_wnd_block.parley_offer_right_count_i32++;
      }
    }
    right_size = self->selected_count_right * 4 + right_size;
    if (self->offer_type_right == 0x11) {
      right_size = self->selected_count_right * 4 + right_size;
    }
  }
  total_size = right_size + 0x20;
  if (mode == 0xe) {
    left_size = *(int *)(((i8 *)&parley_item_header_sizes) + self->offer_type_left * 4);
    switch(self->offer_type_left) {
    case 8:
    case 0xc:
      for (i = 0; i < parley_wnd_block.parley_list_counts[0]; i++) {
        if (*(int *)(((i8 *)&parley_wnd_block.parley_list_selected) + i * 4) == 1) {
          parley_wnd_block.parley_offer_left_count_i32++;
        }
      }
      left_size = self->selected_count_left * 4 + left_size;
      break;
    case 10:
    case 0x11:
      for (i = 0; i < parley_wnd_block.parley_list_counts[0]; i++) {
        if (*(int *)(((i8 *)&parley_wnd_block.parley_list_selected) + i * 4) == 1) {
          parley_wnd_block.parley_offer_left_count_i32++;
        }
      }
      left_size = self->selected_count_left * 4 + left_size;
      if (self->offer_type_left == 0x11) {
        left_size = self->selected_count_left * 4 + left_size;
      }
    }
    total_size += left_size;
  }
  msg = operator_new(total_size);
  if (msg == (i32 *)0x0) {
    dbg_log((iptr)&str_failed_to_allocate_buffer_for_parley_tra);
    msg = (i32 *)0x0;
  }
  else {
    *msg = 0x66606660;
    msg[1] = 0x82;
    msg[2] = total_size;
    msg[4] = self->parley_kind;
    msg[5] = human_civ[0];
    msg[6] = self->civ_id;
    msg[7] = offer_kind;
    if (total_size + (int)msg < (uint)(right_size + (int)(msg + 8))) {
      err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_charptr_pchunk_sizechunk0_charptr_pmessa,(iptr)&str_d_ss_franklinton_parleywin_transaction_c,0x9f);
    }
    parley_pack_offer_items(self,(iptr)(msg + 8),self->offer_type_right,right_size,1);
    if (mode == 0xe) {
      left_items = (int)msg + right_size + 0x20;
      if (left_size + left_items != total_size + (int)msg) {
        err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_charptr_pchunk_sizechunk1_charptr_pmessa,(iptr)&str_d_ss_franklinton_parleywin_transaction_c_2,0xa4);
      }
      parley_pack_offer_items(self,left_items,self->offer_type_left,left_size,0);
    }
    net_send_message(0x82,*(i32 *)
                             (((i8 *)&net_session_block.net_player_slots) + *(int *)(((i8 *)&net_session_block.net_civ_slots) + parley_wnd_block.parley_other_civ * 4) * 0x54),0,0
                       ,0,0,0,0,0,(iptr)msg);
  }
  return msg;
}

/* 004dbab4 auto */
void __thiscall
parley_pack_offer_items
          (ParleyOfferBuffer *self,iptr dest,i32 item_type,i32 item_size,iptr side)

{
  int gold;
  i32 *item_ptr2;
  int packed_count;
  int i;
  i32 *pair_ptr;
  char gold_text[32];
  
  switch(item_type) {
  case 5:
  case 6:
    *(i32 *)dest = item_type;
    *(i32 *)(dest + 4) = item_size;
    *(u32 *)(dest + 8) = self->treaty_choice;
    break;
  case 8:
    *(i32 *)dest = item_type;
    *(i32 *)(dest + 4) = item_size;
    *(i32 *)(dest + 8) = *(i32 *)(self->proposal_kind + side * 4 + 0x1020c);
    item_ptr2 = (i32 *)(dest + 0xc);
    packed_count = 0;
    for (i = 0; i < (int)(((i32 *)&parley_wnd_block.parley_list_counts))[side]; i++) {
      if (*(int *)(((i8 *)&parley_wnd_block.parley_list_selected) + i * 4 + side * 0x2004) == 1) {
        *item_ptr2 = *(i32 *)(self->proposal_kind + side * 0x2004 + i * 4 + 0x1d4);
        item_ptr2++;
        packed_count++;
        if (*(int *)(self->proposal_kind + side * 4 + 0x1020c) == packed_count) {
          return;
        }
      }
    }
    break;
  case 9:
    *(i32 *)dest = item_type;
    *(i32 *)(dest + 4) = item_size;
    ctrl_get_text(*(ControlTextView **)(((i8 *)&parley_wnd_block.parley_gold_edits) + side * 4),(iptr)gold_text);
    gold = _atoi(gold_text);
    *(int *)(dest + 8) = gold;
    break;
  case 10:
    *(i32 *)dest = item_type;
    *(i32 *)(dest + 4) = item_size;
    *(i32 *)(dest + 8) = *(i32 *)(self->proposal_kind + side * 4 + 0x1020c);
    pair_ptr = (i32 *)(dest + 0xc);
    packed_count = 0;
    for (i = 0; i < (int)(((i32 *)&parley_wnd_block.parley_list_counts))[side]; i++) {
      if (*(int *)(((i8 *)&parley_wnd_block.parley_list_selected) + i * 4 + side * 0x2004) == 1) {
        *pair_ptr = *(i32 *)(self->proposal_kind + side * 0x2004 + i * 4 + 0x41dc);
        pair_ptr++;
        packed_count++;
        if (*(int *)(self->proposal_kind + side * 4 + 0x1020c) == packed_count) {
          return;
        }
      }
    }
    break;
  case 0xc:
    *(i32 *)dest = item_type;
    *(i32 *)(dest + 4) = item_size;
    *(i32 *)(dest + 8) = *(i32 *)(self->proposal_kind + side * 4 + 0x1020c);
    item_ptr2 = (i32 *)(dest + 0xc);
    packed_count = 0;
    for (i = 0; i < (int)(((i32 *)&parley_wnd_block.parley_list_counts))[side]; i++) {
      if (*(int *)(((i8 *)&parley_wnd_block.parley_list_selected) + i * 4 + side * 0x2004) == 1) {
        *item_ptr2 = *(i32 *)(self->proposal_kind + side * 0x2004 + i * 4 + 0x1d4);
        item_ptr2++;
        packed_count++;
        if (*(int *)(self->proposal_kind + side * 4 + 0x1020c) == packed_count) {
          return;
        }
      }
    }
    break;
  case 0xd:
    *(i32 *)dest = item_type;
    *(i32 *)(dest + 4) = item_size;
    *(i32 *)(dest + 8) = *(i32 *)(self->proposal_kind + side * 4 + 8);
    break;
  case 0x11:
    *(i32 *)dest = item_type;
    *(i32 *)(dest + 4) = item_size;
    *(i32 *)(dest + 8) = *(i32 *)(self->proposal_kind + side * 4 + 0x1020c);
    pair_ptr = (i32 *)(dest + 0xc);
    packed_count = 0;
    for (i = 0; i < (int)(((i32 *)&parley_wnd_block.parley_list_counts))[side]; i++) {
      if (*(int *)(((i8 *)&parley_wnd_block.parley_list_selected) + i * 4 + side * 0x2004) == 1) {
        *pair_ptr = *(i32 *)(self->proposal_kind + side * 0x2004 + i * 4 + 0x41dc);
        pair_ptr[1] = *(i32 *)(self->proposal_kind + side * 0x2004 + i * 4 + 0xc1ec);
        pair_ptr += 2;
        packed_count++;
        if (*(int *)(self->proposal_kind + side * 4 + 0x1020c) == packed_count) {
          return;
        }
      }
    }
  }
  return;
}

/* 004dbee6 auto */
void __thiscall parley_build_description(WindowObjectView *self,iptr offer,int received)

{
  int maps_kind;
  int *first_items;
  iptr second_offer;
  i32 *second_items;
  size_t desc_len;
  iptr label;
  
  if (offer != 0) {
    first_items = (int *)(offer + 0x20);
    second_offer = *(int *)(offer + 0x24) + offer;
    second_items = (i32 *)(second_offer + 0x20);
    str_clear((iptr)&text_section_index_pool_block.parley_description);
    desc_len = _strlen(((i8 *)&text_section_index_pool_block.parley_description));
    if (desc_len != 0) {
      err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_strlen_parleydescription_0,(iptr)&str_d_ss_franklinton_parleywin_transaction_c_3,0x120);
    }
    if (received == 0) {
      label = label_string(*(i32 *)(label_string_ids + 0xc70));
      str_concat((iptr)&text_section_index_pool_block.parley_description,label);
      crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_desc_transmitted_crlf_str));
    }
    desc_len = _strlen(((i8 *)&text_section_index_pool_block.parley_description));
    if (0x7ff < desc_len) {
      err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_strlen_parleydescription_2048,(iptr)&str_d_ss_franklinton_parleywin_transaction_c_4,0x126);
    }
    switch(*(i32 *)(offer + 0x10)) {
    case 6:
      parley_describe_treaty(self,*(i32 *)(offer + 0x28),0);
      break;
    case 7:
      label = label_string(*(i32 *)(label_string_ids + 0xc98));
      str_concat((iptr)&text_section_index_pool_block.parley_description,label);
      crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_desc_gift_adv_crlf_str));
      label = label_string(*(i32 *)(label_string_ids + 0xc9c));
      str_concat((iptr)&text_section_index_pool_block.parley_description,label);
      crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_desc_gift_adv_head_crlf_str));
      parley_describe_advances((iptr)first_items);
      break;
    case 8:
      label = label_string(*(i32 *)(label_string_ids + 0xc98));
      str_concat((iptr)&text_section_index_pool_block.parley_description,label);
      crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_desc_gift_gold_crlf_str));
      label = label_string(*(i32 *)(label_string_ids + 0xca4));
      str_concat((iptr)&text_section_index_pool_block.parley_description,label);
      crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_desc_gift_gold_head_crlf_str));
      str_concat((iptr)&text_section_index_pool_block.parley_description,(iptr)&str_empty_139);
      parley_describe_gold(*(i32 *)(offer + 0x28));
      break;
    case 9:
      label = label_string(*(i32 *)(label_string_ids + 0xc98));
      str_concat((iptr)&text_section_index_pool_block.parley_description,label);
      crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_desc_gift_units_crlf_str));
      label = label_string(*(i32 *)(label_string_ids + 0xca0));
      str_concat((iptr)&text_section_index_pool_block.parley_description,label);
      crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_desc_gift_units_head_crlf_str));
      parley_describe_units((iptr)first_items);
      break;
    case 10:
      label = label_string(*(i32 *)(label_string_ids + 0xc98));
      str_concat((iptr)&text_section_index_pool_block.parley_description,label);
      crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_desc_gift_cities_crlf_str));
      label = label_string(*(i32 *)(label_string_ids + 0xca8));
      str_concat((iptr)&text_section_index_pool_block.parley_description,label);
      crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_desc_gift_cities_head_crlf_str));
      parley_describe_cities((iptr)first_items);
      break;
    case 0xb:
      label = label_string(*(i32 *)(label_string_ids + 0xc98));
      str_concat((iptr)&text_section_index_pool_block.parley_description,label);
      crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_desc_gift_maps_crlf_str));
      parley_describe_maps(*(i32 *)(offer + 0x28),0);
      break;
    case 0xc:
      label = label_string(*(i32 *)(label_string_ids + 0xc84));
      str_concat((iptr)&text_section_index_pool_block.parley_description,label);
      crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_desc_war_offer_crlf_str));
      label = label_string(*(i32 *)(label_string_ids + 0xc94));
      str_concat((iptr)&text_section_index_pool_block.parley_description,label);
      crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_desc_war_head_crlf_str));
      parley_describe_war_targets((iptr)first_items);
      break;
    case 0xd:
      label = label_string(*(i32 *)(label_string_ids + 0xc84));
      str_concat((iptr)&text_section_index_pool_block.parley_description,label);
      crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_desc_maps_offer_crlf_str));
      maps_kind = *(int *)(offer + 0x28);
      if (maps_kind == 0) {
        label = label_string(*(i32 *)(label_string_ids + 0xc88));
        str_concat((iptr)&text_section_index_pool_block.parley_description,label);
      }
      else if (maps_kind == 1) {
        label = label_string(*(i32 *)(label_string_ids + 0xc8c));
        str_concat((iptr)&text_section_index_pool_block.parley_description,label);
      }
      else if (maps_kind == 2) {
        label = label_string(*(i32 *)(label_string_ids + 0xc90));
        str_concat((iptr)&text_section_index_pool_block.parley_description,label);
      }
      crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_desc_maps_kind_crlf_str));
      break;
    case 0xe:
      label = label_string(*(i32 *)(label_string_ids + 0xcb4));
      str_concat((iptr)&text_section_index_pool_block.parley_description,label);
      crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_desc_barter_crlf_str));
      switch(*second_items) {
      case 5:
      case 6:
        label = label_string(*(i32 *)(label_string_ids + 0xd1c));
        str_concat((iptr)&text_section_index_pool_block.parley_description,label);
        crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_desc_give_treaty_crlf_str));
        parley_describe_treaty(self,*(i32 *)(second_offer + 0x28),1);
        break;
      case 8:
        label = label_string(*(i32 *)(label_string_ids + 0xcb8));
        str_concat((iptr)&text_section_index_pool_block.parley_description,label);
        crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_desc_give_adv_crlf_str));
        parley_describe_advances((iptr)second_items);
        break;
      case 9:
        label = label_string(*(i32 *)(label_string_ids + 0xcbc));
        str_concat((iptr)&text_section_index_pool_block.parley_description,label);
        crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_desc_give_gold_crlf_str));
        str_concat((iptr)&text_section_index_pool_block.parley_description,(iptr)&str_empty_140);
        parley_describe_gold(*(i32 *)(second_offer + 0x28));
        break;
      case 10:
        label = label_string(*(i32 *)(label_string_ids + 0xcc0));
        str_concat((iptr)&text_section_index_pool_block.parley_description,label);
        crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_desc_give_units_crlf_str));
        parley_describe_units((iptr)second_items);
        break;
      case 0xc:
        label = label_string(*(i32 *)(label_string_ids + 0xccc));
        str_concat((iptr)&text_section_index_pool_block.parley_description,label);
        crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_desc_give_war_crlf_str));
        parley_describe_war_targets((iptr)second_items);
        break;
      case 0xd:
        label = label_string(*(i32 *)(label_string_ids + 0xcc8));
        str_concat((iptr)&text_section_index_pool_block.parley_description,label);
        crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_desc_give_maps_crlf_str));
        parley_describe_maps(*(i32 *)(second_offer + 0x28),0);
        break;
      case 0x11:
        label = label_string(*(i32 *)(label_string_ids + 0xcc4));
        str_concat((iptr)&text_section_index_pool_block.parley_description,label);
        crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_desc_give_cities_crlf_str));
        parley_describe_cities((iptr)second_items);
      }
      crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_desc_barter_sep_crlf_str));
      switch(*first_items) {
      case 5:
      case 6:
        label = label_string(*(i32 *)(label_string_ids + 0xd20));
        str_concat((iptr)&text_section_index_pool_block.parley_description,label);
        crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_exch_for_treaty_crlf_str));
        parley_describe_treaty(self,*(i32 *)(offer + 0x28),1);
        break;
      case 8:
        label = label_string(*(i32 *)(label_string_ids + 0xcd0));
        str_concat((iptr)&text_section_index_pool_block.parley_description,label);
        crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_desc_want_adv_crlf_str));
        parley_describe_advances((iptr)first_items);
        break;
      case 9:
        label = label_string(*(i32 *)(label_string_ids + 0xcd4));
        str_concat((iptr)&text_section_index_pool_block.parley_description,label);
        crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_desc_want_gold_crlf_str));
        str_concat((iptr)&text_section_index_pool_block.parley_description,(iptr)&str_empty_141);
        parley_describe_gold(*(i32 *)(offer + 0x28));
        break;
      case 10:
        label = label_string(*(i32 *)(label_string_ids + 0xcd8));
        str_concat((iptr)&text_section_index_pool_block.parley_description,label);
        crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_desc_want_units_crlf_str));
        parley_describe_units((iptr)first_items);
        break;
      case 0xc:
        label = label_string(*(i32 *)(label_string_ids + 0xce4));
        str_concat((iptr)&text_section_index_pool_block.parley_description,label);
        crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_exch_for_war_targets_crlf_str));
        parley_describe_war_targets((iptr)first_items);
        break;
      case 0xd:
        label = label_string(*(i32 *)(label_string_ids + 0xce0));
        str_concat((iptr)&text_section_index_pool_block.parley_description,label);
        crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_exch_for_maps_crlf_str));
        parley_describe_maps(*(i32 *)(offer + 0x28),1);
        break;
      case 0x11:
        label = label_string(*(i32 *)(label_string_ids + 0xcdc));
        str_concat((iptr)&text_section_index_pool_block.parley_description,label);
        crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_exch_for_cities_crlf_str));
        parley_describe_cities((iptr)first_items);
      }
      break;
    case 0xf:
      label = label_string(*(i32 *)(label_string_ids + 0xcac));
      str_concat((iptr)&text_section_index_pool_block.parley_description,label);
      str_append_space((iptr)&text_section_index_pool_block.parley_description);
      if (*first_items == 0xc) {
        label = label_string(*(i32 *)(label_string_ids + 0xd18));
        str_concat((iptr)&text_section_index_pool_block.parley_description,label);
      }
      else if ((*first_items == 5) || (*first_items == 6)) {
        label = label_string(*(i32 *)(label_string_ids + 0xd14));
        str_concat((iptr)&text_section_index_pool_block.parley_description,label);
      }
      else {
        label = label_string(*(i32 *)(label_string_ids + 0xcb0));
        str_concat((iptr)&text_section_index_pool_block.parley_description,label);
      }
      crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_desc_threat_crlf_str));
      switch(*first_items) {
      case 5:
      case 6:
        parley_describe_treaty(self,*(i32 *)(offer + 0x28),1);
        break;
      case 8:
        parley_describe_advances((iptr)first_items);
        break;
      case 9:
        parley_describe_gold(*(i32 *)(offer + 0x28));
        break;
      case 10:
        parley_describe_units((iptr)first_items);
        break;
      case 0xc:
        parley_describe_war_targets((iptr)first_items);
        break;
      case 0xd:
        parley_describe_maps(*(i32 *)(offer + 0x28),1);
        break;
      case 0x11:
        parley_describe_cities((iptr)first_items);
      }
    }
    desc_len = _strlen(((i8 *)&text_section_index_pool_block.parley_description));
    if (0x7ff < desc_len) {
      err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_strlen_parleydescription_2048_2,(iptr)&str_d_ss_franklinton_parleywin_transaction_c_5,0x1f1);
    }
  }
  return;
}

/* 004dcafa auto */
void __cdecl parley_describe_advances(iptr items)

{
  int count;
  iptr adv_name;
  int i;
  int *adv_ptr;
  
  count = *(int *)(items + 8);
  adv_ptr = (int *)(items + 0xc);
  for (i = 0; i < count; i++) {
    adv_name = label_string(advances[*adv_ptr].name);
    str_concat((iptr)&text_section_index_pool_block.parley_description,adv_name);
    if (1 < count) {
      if (i < count - 2) {
        crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_advances_comma_str));
      }
      else if (count - 2 == i) {
        str_append_space((iptr)&text_section_index_pool_block.parley_description);
        adv_name = label_string(*(i32 *)(label_string_ids + 0xce8));
        str_concat((iptr)&text_section_index_pool_block.parley_description,adv_name);
        str_append_space((iptr)&text_section_index_pool_block.parley_description);
      }
      else {
        crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_advances_period_str));
      }
    }
    adv_ptr++;
  }
  crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_advances_crlf_str));
  return;
}

/* 004dcc0c auto */
void __cdecl parley_describe_gold(int gold)

{
  i32 label;
  char gold_text[16];
  
  __itoa(gold,gold_text,10);
  crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),gold_text);
  str_append_space((iptr)&text_section_index_pool_block.parley_description);
  label = label_string(*(i32 *)(label_string_ids + 0xcec));
  crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),label);
  crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_gold_crlf_str));
  return;
}

/* 004dcc83 auto */
void __cdecl parley_describe_units(iptr items)

{
  iptr unit;
  iptr label;
  int type_counts[62];
  int listed;
  iptr unit_ids;
  iptr unit_type;
  int distinct_types;
  int unit_count;
  char count_text[16];
  
  for (unit_type = 0; unit_type < 0x3e; unit_type++) {
    type_counts[unit_type] = 0;
  }
  unit_count = *(int *)(items + 8);
  unit_ids = items + 0xc;
  distinct_types = 0;
  for (unit_type = 0; unit_type < unit_count; unit_type++) {
    unit = parley_find_unit_by_id
                      ((WindowObjectView *)((i8 *)&parley_wnd_block.parley_wnd),*(i32 *)(unit_ids + unit_type * 4));
    if (-1 < unit) {
      if (type_counts[units[unit].type] == 0) {
        distinct_types++;
      }
      type_counts[units[unit].type] = type_counts[units[unit].type] + 1;
    }
  }
  listed = 0;
  for (unit_type = 0; unit_type < 0x3e; unit_type++) {
    if (type_counts[unit_type] != 0) {
      str_append_string_id((iptr)&text_section_index_pool_block.parley_description,unit_types[unit_type].name);
      crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_units_open_paren_str));
      __itoa(type_counts[unit_type],count_text,10);
      crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),count_text);
      crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_units_close_paren_str));
      if (1 < unit_count) {
        if (listed < distinct_types - 2) {
          crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_units_comma_str));
        }
        else if (distinct_types - 2 == listed) {
          str_append_space((iptr)&text_section_index_pool_block.parley_description);
          label = label_string(*(i32 *)(label_string_ids + 0xce8));
          str_concat((iptr)&text_section_index_pool_block.parley_description,label);
          str_append_space((iptr)&text_section_index_pool_block.parley_description);
        }
        else {
          crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_units_period_str));
        }
      }
      listed++;
    }
  }
  crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_units_crlf_str));
  return;
}

/* 004dcea5 auto */
void __cdecl parley_describe_cities(iptr items)

{
  int count;
  int city;
  iptr label;
  int i;
  char size_text[16];
  
  count = *(int *)(items + 8);
  for (i = 0; i < count; i++) {
    city = parley_find_city_by_id
                      ((WindowObjectView *)((i8 *)&parley_wnd_block.parley_wnd),*(i32 *)(items + 0xc + i * 8));
    str_append((iptr)&text_section_index_pool_block.parley_description,(iptr)&cities[city].name);
    crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_cities_open_paren_str));
    __itoa(*(int *)(items + 0x10 + i * 8),size_text,10);
    crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),size_text);
    crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_cities_close_paren_str));
    if (1 < count) {
      if (i < count - 2) {
        crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_cities_comma_str));
      }
      else if (count - 2 == i) {
        str_append_space((iptr)&text_section_index_pool_block.parley_description);
        label = label_string(*(i32 *)(label_string_ids + 0xce8));
        str_concat((iptr)&text_section_index_pool_block.parley_description,label);
        str_append_space((iptr)&text_section_index_pool_block.parley_description);
      }
      else {
        crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_cities_period_str));
      }
    }
  }
  crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_cities_crlf_str));
  return;
}

/* 004dd016 auto */
void __cdecl parley_describe_maps(int map_kind,int exchange)

{
  iptr label;
  
  if (map_kind == 0) {
    if (exchange == 0) {
      label = label_string(*(i32 *)(label_string_ids + 0xcf0));
      str_concat((iptr)&text_section_index_pool_block.parley_description,label);
    }
    else {
      label = label_string(*(i32 *)(label_string_ids + 0xcf4));
      str_concat((iptr)&text_section_index_pool_block.parley_description,label);
    }
  }
  else if (map_kind == 1) {
    if (exchange == 0) {
      label = label_string(*(i32 *)(label_string_ids + 0xcf8));
      str_concat((iptr)&text_section_index_pool_block.parley_description,label);
    }
    else {
      label = label_string(*(i32 *)(label_string_ids + 0xcfc));
      str_concat((iptr)&text_section_index_pool_block.parley_description,label);
    }
  }
  else if (map_kind == 2) {
    if (exchange == 0) {
      label = label_string(*(i32 *)(label_string_ids + 0xd00));
      str_concat((iptr)&text_section_index_pool_block.parley_description,label);
    }
    else {
      label = label_string(*(i32 *)(label_string_ids + 0xd04));
      str_concat((iptr)&text_section_index_pool_block.parley_description,label);
    }
  }
  crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_maps_crlf_str));
  return;
}

/* 004dd176 auto */
void __cdecl parley_describe_war_targets(iptr items)

{
  int count;
  iptr text;
  iptr *civ_ptr;
  int i;
  
  count = *(int *)(items + 8);
  civ_ptr = (iptr *)(items + 0xc);
  for (i = 0; i < count; i++) {
    text = civ_name_plural(*civ_ptr);
    str_concat((iptr)&text_section_index_pool_block.parley_description,text);
    if (1 < count) {
      if (i < count - 2) {
        crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_war_targets_comma_str));
      }
      else if (count - 2 == i) {
        str_append_space((iptr)&text_section_index_pool_block.parley_description);
        text = label_string(*(i32 *)(label_string_ids + 0xce8));
        str_concat((iptr)&text_section_index_pool_block.parley_description,text);
        str_append_space((iptr)&text_section_index_pool_block.parley_description);
      }
      else {
        crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_war_targets_period_str));
      }
    }
    civ_ptr++;
  }
  crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_war_targets_crlf_str));
  return;
}

/* 004dd285 auto */
void __cdecl parley_execute_transaction(iptr offer)

{
  i32 *first_items;
  iptr second_offer;
  i32 *second_items;
  iptr civ;
  iptr civ2;
  
  if (offer != 0) {
    dbg_logf((iptr)&str_start_executeparleytransaction_message_d,net_send_sequence);
    civ = *(iptr *)(offer + 0x14);
    civ2 = *(iptr *)(offer + 0x18);
    first_items = (i32 *)(offer + 0x20);
    second_offer = *(int *)(offer + 0x24) + offer;
    second_items = (i32 *)(second_offer + 0x20);
    switch(*(i32 *)(offer + 0x10)) {
    case 6:
      parley_apply_treaty(*(i32 *)(offer + 0x28),civ,civ2);
      break;
    case 7:
      parley_transfer_advances(civ2,civ,(iptr)first_items);
      break;
    case 8:
      parley_transfer_gold(civ2,civ,*(i32 *)(offer + 0x28));
      break;
    case 9:
      parley_transfer_units(civ2,(iptr)first_items);
      break;
    case 10:
      parley_transfer_cities(civ2,(iptr)first_items);
      break;
    case 0xb:
      parley_give_maps(civ2,civ,*(i32 *)(offer + 0x28));
      break;
    case 0xc:
      parley_apply_war_pact(civ,(iptr)first_items);
      parley_apply_war_pact(civ2,(iptr)first_items);
      break;
    case 0xd:
      parley_give_maps(civ,civ2,*(i32 *)(offer + 0x28));
      parley_give_maps(civ2,civ,*(i32 *)(offer + 0x28));
      break;
    case 0xe:
      switch(*second_items) {
      case 5:
      case 6:
        parley_apply_treaty(*(i32 *)(second_offer + 0x28),civ,civ2);
        break;
      case 8:
        parley_transfer_advances(civ2,civ,(iptr)second_items);
        break;
      case 9:
        parley_transfer_gold(civ2,civ,*(i32 *)(second_offer + 0x28));
        break;
      case 10:
        parley_transfer_units(civ2,(iptr)second_items);
        break;
      case 0xc:
        parley_apply_war_pact(civ,(iptr)second_items);
        break;
      case 0xd:
        parley_give_maps(civ2,civ,*(i32 *)(second_offer + 0x28));
        break;
      case 0x11:
        parley_transfer_cities(civ2,(iptr)second_items);
      }
      switch(*first_items) {
      case 5:
      case 6:
        parley_apply_treaty(*(i32 *)(offer + 0x28),civ,civ2);
        break;
      case 8:
        parley_transfer_advances(civ,civ2,(iptr)first_items);
        break;
      case 9:
        parley_transfer_gold(civ,civ2,*(i32 *)(offer + 0x28));
        break;
      case 10:
        parley_transfer_units(civ,(iptr)first_items);
        break;
      case 0xc:
        parley_apply_war_pact(civ2,(iptr)first_items);
        break;
      case 0xd:
        parley_give_maps(civ,civ2,*(i32 *)(offer + 0x28));
        break;
      case 0x11:
        parley_transfer_cities(civ,(iptr)first_items);
      }
      break;
    case 0xf:
      switch(*first_items) {
      case 5:
      case 6:
        parley_apply_treaty(*(i32 *)(offer + 0x28),civ,civ2);
        break;
      case 8:
        parley_transfer_advances(civ,civ2,(iptr)first_items);
        break;
      case 9:
        parley_transfer_gold(civ,civ2,*(i32 *)(offer + 0x28));
        break;
      case 10:
        parley_transfer_units(civ,(iptr)first_items);
        break;
      case 0xc:
        parley_apply_war_pact(civ2,(iptr)first_items);
        break;
      case 0xd:
        parley_give_maps(civ,civ2,*(i32 *)(offer + 0x28));
        break;
      case 0x11:
        parley_transfer_cities(civ,(iptr)first_items);
      }
    }
    net_send_state_diff(0xff,2,0,0,0);
    if (human_civ[0] == civ2) {
      status_redraw(1);
    }
    else {
      net_send_message(0x79,*(i32 *)
                               (((i8 *)&net_session_block.net_player_slots) + *(int *)(((i8 *)&net_session_block.net_civ_slots) + civ2 * 4) * 0x54),0,0,0,0,
                         0,0,0,0);
    }
    if (human_civ[0] == civ) {
      status_redraw(1);
    }
    else {
      net_send_message(0x79,*(i32 *)
                               (((i8 *)&net_session_block.net_player_slots) + *(int *)(((i8 *)&net_session_block.net_civ_slots) + civ * 4) * 0x54),0,0,0,0,
                         0,0,0,0);
    }
    if ((*(int *)(((i8 *)&civ_unit_counts_block.civ_unit_counts) + civ2 * 4) == 0) && (civs[civ2].num_cities == 0)) {
      civ_check_destroyed(civ2,civ);
    }
    if ((*(int *)(((i8 *)&civ_unit_counts_block.civ_unit_counts) + civ * 4) == 0) && (civs[civ].num_cities == 0)) {
      civ_check_destroyed(civ,civ2);
    }
    dbg_logf((iptr)&str_end_executeparleytransaction_message_d,net_send_sequence);
  }
  return;
}

/* 004dd8ad auto */
void __cdecl parley_give_maps(iptr receiver,iptr civ,int map_kind)

{
  byte recv_bits;
  byte giver_bits;
  uint recv_mask;
  uint giver_mask;
  iptr tile;
  byte *recv_known;
  byte *giver_known;
  iptr tile2;
  iptr tile3;
  int y;
  iptr x;
  int in_bounds;
  i32 set_flag;
  i32 redraw_flag;
  iptr target_civ;
  iptr unit;
  byte known_bits;
  byte recv_bit;
  iptr city;
  uint y2;
  uint x2;
  iptr i;
  
  recv_mask = 1 << ((byte)receiver & 0x1f);
  giver_mask = 1 << ((byte)civ & 0x1f);
  y2 = 0;
  x2 = 0;
  net_batch_begin();
  for (i = 0; i < map.area; i++) {
    tile = tile_at(x2,y2);
    recv_known = (byte *)known_at(x2,y2,receiver);
    giver_known = (byte *)known_at(x2,y2,civ);
    if ((giver_mask & *(byte *)(tile + 4)) != 0) {
      if ((recv_mask & *(byte *)(tile + 4)) == 0) {
        known_set(x2,y2,0,receiver,0,1);
        tile_set_visible(x2,y2,recv_mask,1,1);
      }
      if (map_kind == 0) {
        if (((*recv_known & 0x80) == 0) || ((*giver_known & 0x80) == 0)) {
          giver_bits = *giver_known;
          recv_bits = *recv_known;
          tile2 = tile_at(x2,y2);
          known_bits = (giver_bits | recv_bits) & *(byte *)(tile2 + 1) & 0x80;
        }
        else {
          known_bits = 0x80;
        }
        redraw_flag = 1;
        set_flag = 0;
        target_civ = receiver;
        recv_known = (byte *)known_at(x2,y2,receiver);
        known_set(x2,y2,*recv_known & 0xffffff7f | (uint)known_bits,target_civ,set_flag,redraw_flag);
        redraw_flag = 1;
        set_flag = 1;
        x = receiver;
        tile3 = tile_at(x2,y2);
        giver_bits = *(byte *)(tile3 + 1);
        recv_known = (byte *)known_at(x2,y2,civ);
        known_set(x2,y2,(uint)(giver_bits & *recv_known),x,set_flag,redraw_flag);
      }
    }
    x2 += 2;
    if ((int)map.width <= (int)x2) {
      y2++;
      x2 = y2 & 1;
    }
  }
  recv_bit = (byte)recv_mask;
  if (map_kind == 0) {
    for (unit = 0; unit < game.num_units; unit++) {
      if ((units[unit].id != 0) &&
         (((giver_mask & units[unit].visibility) != 0 || (units[unit].owner == civ)))) {
        units[unit].visibility = units[unit].visibility | recv_bit;
        y = tile_at((int)units[unit].x,(int)units[unit].y);
        if (((recv_mask & *(byte *)(y + 4)) == 0) || ((giver_mask & *(byte *)(y + 4)) == 0)) {
          for (i = 0; i < 0x15; i++) {
            x = map_wrap_x((int)(char)(((i8 *)&dir_dy_table_block.city_tile_dx_table))[i] + x2);
            y = (int)(char)(((i8 *)&dir_dy_table_block.city_tile_dy_table))[i] + y2;
            in_bounds = map_in_bounds(x,y);
            if (in_bounds != 0) {
              tile_set_visible(x,y,recv_mask,1,1);
              tile_set_visible(x,y,giver_mask,1,1);
            }
          }
        }
      }
    }
  }
  if ((map_kind == 0) || (map_kind == 1)) {
    for (city = 0; city < game.num_cities; city++) {
      if ((cities[city].id != 0) &&
         (((giver_mask & (int)(char)cities[city].known_to) != 0 ||
          (cities[city].owner == civ)))) {
        if (cities[city].owner == civ) {
          *(i8 *)&cities[city].revealed_size[receiver] = cities[city].size;
        }
        else {
          *(i8 *)&cities[city].revealed_size[receiver] =
               *(i8 *)&cities[city].revealed_size[civ];
        }
        cities[city].known_to = cities[city].known_to | recv_bit;
        y = tile_at((int)cities[city].x,(int)cities[city].y);
        if (((recv_mask & *(byte *)(y + 4)) == 0) || ((giver_mask & *(byte *)(y + 4)) == 0)) {
          for (i = 0; i < 0x15; i++) {
            x = map_wrap_x((int)(char)(((i8 *)&dir_dy_table_block.city_tile_dx_table))[i] + x2);
            y = (int)(char)(((i8 *)&dir_dy_table_block.city_tile_dy_table))[i] + y2;
            in_bounds = map_in_bounds(x,y);
            if (in_bounds != 0) {
              tile_set_visible(x,y,recv_mask,1,1);
              tile_set_visible(x,y,giver_mask,1,1);
            }
          }
        }
      }
    }
  }
  net_batch_flush();
  net_send_state_diff(0xff,2,0,0,0);
  if (human_civ[0] == receiver) {
    map_redraw_all_views(human_civ[0],1);
  }
  else {
    net_send_message(0x74,*(i32 *)
                             (((i8 *)&net_session_block.net_player_slots) + *(int *)(((i8 *)&net_session_block.net_civ_slots) + receiver * 4) * 0x54),0,0,0,0,
                       0,0,0,0);
  }
  return;
}

/* 004dde9e auto */
void __cdecl parley_apply_war_pact(iptr civ,iptr items)

{
  int count;
  iptr *civ_ptr;
  int i;
  
  count = *(int *)(items + 8);
  civ_ptr = (iptr *)(items + 0xc);
  for (i = 0; i < count; i++) {
    diplo_set_treaty_flags(civ,*civ_ptr,0x2000);
    civ_ptr++;
  }
  return;
}

/* 004ddf04 auto */
void __cdecl parley_transfer_gold(iptr civ2,iptr civ,i32 amount)

{
  int attitude_value;
  
  if (civs[civ].gold < amount) {
    amount = civs[civ].gold;
  }
  civs[civ].gold -= amount;
  civs[civ2].gold += amount;
  attitude_value = diplo_gold_attitude_value(amount);
  civ_adjust_attitude(civ2,civ,-((attitude_value * 3) / 2));
  return;
}

/* 004ddfb2 auto */
void __cdecl parley_transfer_advances(iptr civ,iptr civ2,iptr items)

{
  int count;
  int has_adv;
  iptr *adv_ptr;
  int i;
  
  count = *(int *)(items + 8);
  adv_ptr = (iptr *)(items + 0xc);
  for (i = 0; i < count; i++) {
    has_adv = civ_has_advance(civ2,*adv_ptr);
    if (has_adv != 0) {
      has_adv = civ_has_advance(civ,*adv_ptr);
      if (has_adv == 0) {
        civ_give_advance(civ,*adv_ptr,civ2,1,0);
      }
    }
    adv_ptr++;
  }
  return;
}

/* 004de049 auto */
void __cdecl parley_transfer_cities(iptr civ,iptr items)

{
  int count;
  iptr city;
  i32 *city_id_ptr;
  int i;
  
  count = *(int *)(items + 8);
  city_id_ptr = (i32 *)(items + 0xc);
  for (i = 0; i < count; i++) {
    city = parley_find_city_by_id((WindowObjectView *)((i8 *)&parley_wnd_block.parley_wnd),*city_id_ptr);
    if ((-1 < city) && (cities[city].id != 0)) {
      parley_cede_city(city,civ);
    }
    city_id_ptr += 2;
  }
  return;
}

/* 004de0e2 auto */
void __cdecl parley_cede_city(uptr city,iptr civ)

{
  char *count_ptr;
  char civ3;
  iptr civ2;
  int x;
  int y;
  iptr x2;
  iptr y3;
  iptr in_bounds;
  int y2;
  iptr in_bounds2;
  int tile;
  uptr leonardo_city;
  iptr improvement;
  iptr unit;
  iptr unit_type;
  iptr i;
  int defense_ratio;
  
  civ3 = cities[city].owner;
  civ2 = (iptr)civ3;
  x = (int)cities[city].x;
  y = (int)cities[city].y;
  city_set_improvement(city,1,0);
  city_set_improvement(city,4,0);
  city_set_improvement(city,0xb,0);
  city_set_improvement(city,7,0);
  civs[civ].last_city_turn = game.turn;
  civs[civ].num_cities++;
  if (civs[civ2].num_cities != 0) {
    civs[civ2].num_cities--;
  }
  net_batch_begin();
  for (i = 0; i < 0x15; i++) {
    x2 = map_wrap_x((char)(((i8 *)&dir_dy_table_block.city_tile_dx_table))[i] + x);
    y3 = (char)(((i8 *)&dir_dy_table_block.city_tile_dy_table))[i] + y;
    in_bounds = map_in_bounds(x2,y3);
    if (in_bounds != 0) {
      tile_set_radius_civ(x2,y3,civ,1);
      tile_set_visible(x2,y3,1 << ((byte)civ & 0x1f),1,1);
    }
  }
  cities[city].owner = (byte)civ;
  city_reveal_to_civ(city,civ2);
  if (scenario_events_loaded != 0) {
    events_check_city_taken
              ((ScenarioEvents *)((i8 *)&unit_types_block.scenario_events),(iptr)&cities[city].name,civ,civ2);
  }
  tile_set_owner(x,y,civ,1);
  unit = (iptr)game.num_units;
  while (unit = unit - 1, -1 < unit) {
    if ((units[unit].id != 0) && (units[unit].owner == civ2)) {
      if (((byte)units[unit].home_city == city) &&
         ((cities[city].x != units[unit].x || (cities[city].y != units[unit].y)))) {
        unit_delete_with_cargo(unit,1);
      }
      else if ((cities[city].x == units[unit].x) && (cities[city].y == units[unit].y))
      {
        count_ptr = (char *)(units[unit].type + (iptr)((u8 *)&civs + 216) + civ * 0x594);
        *count_ptr = *count_ptr + 1;
        count_ptr = (char *)(units[unit].type + (iptr)((u8 *)&civs + 216) + civ2 * 0x594);
        *count_ptr = *count_ptr - 1;
        units[unit].owner = (byte)civ;
        units[unit].home_city = -1;
        units[unit].moves_used = '\0';
        units[unit].orders = -1;
        city = city_find_nearest((int)units[unit].x,(int)units[unit].y,civ,
                                     0xffffffff,-1);
        if ((-1 < (int)city) && (cities[city].owner == civ)) {
          units[unit].home_city = (i8)city;
        }
        unit_set_seen_by(unit,civ);
        if ((char)unit_types[units[unit].type].role < 5) {
          civs[civ].num_military_units++;
        }
        *(int *)(((i8 *)&civ_unit_counts_block.civ_unit_counts) + civ * 4) = *(int *)(((i8 *)&civ_unit_counts_block.civ_unit_counts) + civ * 4) + 1;
        if ((civs[civ2].num_military_units != 0) &&
           ((char)unit_types[units[unit].type].role < 5)) {
          civs[civ2].num_military_units--;
        }
        if (*(int *)(((i8 *)&civ_unit_counts_block.civ_unit_counts) + civ2 * 4) != 0) {
          *(int *)(((i8 *)&civ_unit_counts_block.civ_unit_counts) + civ2 * 4) = *(int *)(((i8 *)&civ_unit_counts_block.civ_unit_counts) + civ2 * 4) - 1;
        }
      }
    }
  }
  if ((cities[city].building < '\0') ||
     (y2 = civ_can_build_unit(civ,city,(int)cities[city].building), y2 != 0)) {
    if (-1 < cities[city].building) goto redraw_and_notify;
    if (cities[city].building < 1) {
      improvement = ~(int)cities[city].building + 1;
    }
    else {
      improvement = (iptr)cities[city].building;
    }
    y2 = city_can_build_improvement(civ,city,improvement);
    if (y2 != 0) goto redraw_and_notify;
  }
  cities[city].building = '\0';
  for (unit_type = 0x3e; -1 < unit_type; unit_type--) {
    if ((unit_types[unit_type].role == 1) &&
       (y2 = civ_can_build_unit(civ,city,unit_type), y2 != 0)) {
      defense_ratio = ((int)(char)unit_types[unit_type].defense << 3) /
                (int)(char)unit_types[unit_type].cost;
      if ((unit_types[unit_type].flags & 0x400) != 0) {
        defense_ratio++;
      }
      if (0 < defense_ratio) {
        cities[city].building = (i8)unit_type;
      }
      break;
    }
  }
redraw_and_notify:
  map_redraw_neighbors_all_views((int)cities[city].x,(int)cities[city].y);
  net_send_state_diff(0xff,2,0,0,0);
  net_send_message(0x75,0xff,(int)cities[city].x,(int)cities[city].y,0,0,0,0,0,0);
  y2 = tile_at(x,y);
  if ((1 << ((byte)civ & 0x1f) & (uint)*(byte *)(y2 + 4)) == 0) {
    tile_set_visible(x,y,1 << ((byte)civ & 0x1f),1,1);
    map_redraw_tile_all_views(x,y);
  }
  for (i = 0; i < 8; i++) {
    x2 = map_wrap_x((char)(((i8 *)&dir_dx_table_block.dir_dx_table))[i] + x);
    y2 = (char)(((i8 *)&dir_dy_table_block.dir_dy_table))[i] + y;
    in_bounds2 = map_in_bounds(x2,y2);
    if ((in_bounds2 != 0) &&
       (tile = tile_at(x2,y2),
       (1 << ((byte)civ & 0x1f) & (uint)*(byte *)(tile + 4)) == 0)) {
      tile_set_visible(x2,y2,1 << ((byte)civ & 0x1f),1,1);
      map_redraw_tile_all_views(x2,y2);
    }
  }
  net_batch_flush();
  net_send_message(0x75,0xff,x,y,0,0,0,0,0,0);
  cities[city].founder = civ3;
  cities[city].turns_captured = (u8)game.turn;
  leonardo_city = wonder_get_city(0xe);
  if (leonardo_city == city) {
    civ_leonardo_upgrade(civ);
  }
  return;
}

/* 004de990 auto */
void __cdecl parley_transfer_units(iptr civ,iptr items)

{
  char *count_ptr;
  i32 unit_id;
  int result;
  iptr x3;
  iptr unit;
  iptr city;
  iptr unit2;
  int i;
  iptr y2;
  iptr x2;
  int count;
  iptr civ2;
  iptr y3;
  i32 *id_ptr;
  
  count = *(int *)(items + 8);
  id_ptr = (i32 *)(items + 0xc);
  for (i = 0; i < count; i++) {
    unit_id = *id_ptr;
    id_ptr++;
    unit = parley_find_unit_by_id((WindowObjectView *)((i8 *)&parley_wnd_block.parley_wnd),unit_id);
    if ((-1 < unit) && (civ2 = (iptr)units[unit].owner, civ != civ2)) {
      if ((unit_types[units[unit].type].domain == 2) &&
         (result = unit_stack_sum(unit,2), 1 < result)) {
        while (result = unit_stack_sum(unit,2), 1 < result) {
          unit2 = unit_stack_first(unit);
          if (unit2 == unit) {
            unit2 = unit_next_in_stack(unit2);
          }
          result = parley_find_unit_drop_tile(unit2,(iptr)&x3,(iptr)&y3,
                                     (int)units[unit2].owner,1);
          if (result == 0) {
            unit_delete_with_cargo(unit2,1);
          }
          else {
            unit_relocate(unit2,x3,y3,1);
          }
        }
      }
      result = parley_find_unit_drop_tile(unit,(iptr)&x2,(iptr)&y2,civ,0);
      if (result != 0) {
        count_ptr = (char *)(units[unit].type + (iptr)((u8 *)&civs + 216) + civ * 0x594);
        *count_ptr = *count_ptr + 1;
        count_ptr = (char *)(units[unit].type + (iptr)((u8 *)&civs + 216) + civ2 * 0x594);
        *count_ptr = *count_ptr - 1;
        units[unit].owner = (i8)civ;
        units[unit].home_city = -1;
        units[unit].moves_used = '\0';
        units[unit].orders = -1;
        city = city_find_nearest((int)units[unit].x,(int)units[unit].y,civ,
                                      0xffffffff,-1);
        if ((-1 < city) && (cities[city].owner == civ)) {
          units[unit].home_city = (i8)city;
        }
        unit_set_seen_by(unit,civ);
        if ((char)unit_types[units[unit].type].role < 5) {
          civs[civ].num_military_units++;
        }
        *(int *)(((i8 *)&civ_unit_counts_block.civ_unit_counts) + civ * 4) = *(int *)(((i8 *)&civ_unit_counts_block.civ_unit_counts) + civ * 4) + 1;
        if ((civs[civ2].num_military_units != 0) &&
           ((char)unit_types[units[unit].type].role < 5)) {
          civs[civ2].num_military_units--;
        }
        if (*(int *)(((i8 *)&civ_unit_counts_block.civ_unit_counts) + civ2 * 4) != 0) {
          *(int *)(((i8 *)&civ_unit_counts_block.civ_unit_counts) + civ2 * 4) = *(int *)(((i8 *)&civ_unit_counts_block.civ_unit_counts) + civ2 * 4) - 1;
        }
        unit_relocate(unit,x2,y2,1);
        unit_reveal_surroundings(unit,0);
      }
    }
  }
  XD_FlushSendBuffer(5000);
  return;
}

/* 004ded07 auto */
i32 __cdecl parley_find_unit_drop_tile(iptr unit,iptr x,iptr y,iptr civ,int must_move)

{
  iptr x2;
  int y2;
  int result;
  i32 wrapped_x;
  iptr i;
  i32 found;
  
  *(int *)x = (int)units[unit].x;
  x2 = *(iptr *)x;
  *(int *)y = (int)units[unit].y;
  y2 = *(int *)y;
  found = 1;
  if (((must_move != 0) || (result = tile_city_owner(x2,y2), result != -1)) ||
     (result = unit_stack_sum(unit,2), 1 < result)) {
    found = 0;
    for (i = 0; i < 0x2d; i++) {
      wrapped_x = map_wrap_x((char)(((i8 *)&dir_dy_table_block.city_tile_dx_table))[i] + x2);
      *(i32 *)x = wrapped_x;
      *(int *)y = (char)(((i8 *)&dir_dy_table_block.city_tile_dy_table))[i] + y2;
      if ((((((must_move == 0) || (*(int *)x != x2)) || (*(int *)y != y2)) &&
           (result = map_in_bounds(*(iptr *)x,*(iptr *)y), result != 0)) &&
          (((result = tile_city_owner(*(iptr *)x,*(i32 *)y), result == civ ||
            (result = tile_unit_owner(*(i32 *)x,*(i32 *)y),
            result == civ)) ||
           ((result = tile_city_owner(*(iptr *)x,*(i32 *)y), result == -1 &&
            (result = tile_unit_owner(*(i32 *)x,*(i32 *)y), result == -1))))
          )) && ((((unit_types[units[unit].type].domain == '\0' &&
                   (result = tile_is_ocean(*(i32 *)x,*(i32 *)y), result == 0
                   )) || ((unit_types[units[unit].type].domain == 2 &&
                          (result = tile_is_ocean(*(i32 *)x,*(i32 *)y),
                          result != 0)))) || (unit_types[units[unit].type].domain == 1)))) {
        return 1;
      }
    }
  }
  return found;
}

/* 004def54 auto */
void __thiscall parley_describe_treaty(WindowObjectView *self,int treaty_kind,int exchange)

{
  iptr label;
  
  if (exchange == 0) {
    switch(treaty_kind) {
    case 0:
      label = label_string(*(i32 *)(label_string_ids + 0xc74));
      str_concat((iptr)&text_section_index_pool_block.parley_description,label);
      break;
    case 1:
      label = label_string(*(i32 *)(label_string_ids + 0xc78));
      str_concat((iptr)&text_section_index_pool_block.parley_description,label);
      break;
    case 2:
      label = label_string(*(i32 *)(label_string_ids + 0xc7c));
      str_concat((iptr)&text_section_index_pool_block.parley_description,label);
      break;
    case 3:
      label = label_string(*(i32 *)(label_string_ids + 0xc80));
      str_concat((iptr)&text_section_index_pool_block.parley_description,label);
    }
  }
  else if (exchange == 1) {
    if (treaty_kind == 0) {
      label = label_string(*(i32 *)(label_string_ids + 0xbcc));
      str_concat((iptr)&text_section_index_pool_block.parley_description,label);
    }
    else if (treaty_kind == 1) {
      label = label_string(*(i32 *)(label_string_ids + 0xbd0));
      str_concat((iptr)&text_section_index_pool_block.parley_description,label);
    }
    else if (treaty_kind == 2) {
      label = label_string(*(i32 *)(label_string_ids + 0xbd4));
      str_concat((iptr)&text_section_index_pool_block.parley_description,label);
    }
  }
  crt_strcat(((i8 *)&text_section_index_pool_block.parley_description),((i8 *)&parley_treaty_crlf_str));
  return;
}

/* 004df10f auto */
void __cdecl parley_apply_treaty(i32 treaty_kind,iptr civ,iptr other_civ)

{
  switch(treaty_kind) {
  case 0:
    diplo_set_treaty_flags(civ,other_civ,2);
    break;
  case 1:
    diplo_set_treaty_flags(civ,other_civ,4);
    break;
  case 2:
    diplo_set_treaty_flags(civ,other_civ,8);
    break;
  case 3:
    if ((*(byte *)&civs[civ].treaties[other_civ] & 2) != 0) {
      diplo_clear_treaty_flags(civ,other_civ,2);
    }
    if ((*(byte *)&civs[civ].treaties[other_civ] & 4) != 0) {
      diplo_clear_treaty_flags(civ,other_civ,4);
    }
    if ((*(byte *)&civs[civ].treaties[other_civ] & 8) != 0) {
      diplo_clear_treaty_flags(civ,other_civ,8);
    }
  }
  return;
}

/* 00511880 auto */
void __cdecl
net_send_text_args(iptr popup_kind,i32 player_id,int string_count,int number_count,iptr arg_a,iptr arg_b)

{
  size_t len;
  void *write_ptr;
  uint payload_size;
  int i;
  void *payload;
  
  payload = (void *)0x0;
  payload_size = 0;
  if (2 < game.multiplayer) {
    if (string_count != 0) {
      for (i = 0; i < string_count; i++) {
        len = _strlen(((i8 *)&minimap_window_block.text_string_args) + i * 0x104);
        payload_size = payload_size + len + 1;
      }
    }
    if (number_count != 0) {
      payload_size = number_count * 4 + payload_size;
    }
    if (payload_size != 0) {
      payload = operator_new(payload_size);
      write_ptr = payload;
      if (string_count != 0) {
        for (i = 0; i < string_count; i++) {
          crt_strcpy(write_ptr,((i8 *)&minimap_window_block.text_string_args) + i * 0x104);
          len = _strlen(((i8 *)&minimap_window_block.text_string_args) + i * 0x104);
          write_ptr = (void *)((int)write_ptr + len + 1);
        }
      }
      if (number_count != 0) {
        for (i = 0; i < number_count; i++) {
          crt_memcpy(write_ptr,((i8 *)&minimap_window_block.text_number_args) + i * 4,4);
          write_ptr = (void *)((int)write_ptr + 4);
        }
      }
    }
    net_send_message(0x6a,player_id,popup_kind,string_count,number_count,arg_a,arg_b,0,0,(iptr)payload);
  }
  return;
}

/* 00511a0e auto */
void __cdecl
net_popup_queue_push(i32 popup_kind,i32 string_count,i32 number_count,i32 arg_a,
            i32 arg_b,i32 payload,int payload_size)

{
  i32 *new_head;
  i32 *entry;
  
  entry = operator_new(payload_size + 0x1c);
  *entry = 0;
  entry[1] = popup_kind;
  entry[2] = string_count;
  entry[3] = number_count;
  entry[4] = arg_a;
  entry[5] = arg_b;
  entry[6] = payload_size;
  if (payload_size != 0) {
    crt_memcpy(entry + 7,payload,payload_size);
  }
  new_head = entry;
  if ((*(i32 * *)&net_popup_queue_head) != (i32 *)0x0) {
    *(*(i32 * *)&net_popup_queue_tail) = entry;
    new_head = (*(i32 * *)&net_popup_queue_head);
  }
  (*(i32 * *)&net_popup_queue_head) = new_head;
  (*(i32 * *)&net_popup_queue_tail) = entry;
  return;
}

/* 00511acf auto */
void __cdecl net_popup_queue_clear(void)

{
  i32 *entry;
  
  while (entry = (*(i32 * *)&net_popup_queue_head), (*(i32 * *)&net_popup_queue_head) != (i32 *)0x0) {
    (*(i32 * *)&net_popup_queue_head) = (i32 *)*(*(i32 * *)&net_popup_queue_head);
    operator_delete(entry);
  }
  net_popup_queue_tail = 0;
  return;
}

/* 00511b2d auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl net_popup_idle_autoclose(void)

{
  int now;
  
  net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
  if (((net_session_block.net_host_handoff_stage == '\0') && (net_session_block.nm_parley_cancel_count == 0)) &&
     (now = timer_ticks(), now - dialog_title_font_obj_block.dialog_timeout_start_i32 < 0x4b1)) {
    return;
  }
  net_session_block.dialog_stack_top[0xf] = net_session_block.dialog_stack_top[0xf] | 0x400;
  wnd_end_modal_loop((ModalMenuWindow *)(*net_session_block.dialog_stack_top + 0x48));
  dialog_title_font_obj_block.dialog_timeout_start_i32 = timer_ticks();
  return;
}

/* 00511ba2 auto */
/* WARNING: Removing unreachable block (ram,0x0051343e) */
/* WARNING: Removing unreachable block (ram,0x0051347e) */
/* WARNING: Removing unreachable block (ram,0x0051369c) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl net_popup_queue_show_next(void)

{
  int *entry;
  size_t len;
  int choice;
  iptr text;
  i8 *icon_sprite;
  iptr attitude_level;
  int i;
  Dialog dlg;
  int *arg_ptr;
  i32 eh_handler;
  i8 *eh_prev;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  entry = (*(int * *)&net_popup_queue_head);
  dialog_ctor(&dlg,0x4000);
  eh_state = 0;
  if (entry != (int *)0x0) {
    net_session_block.net_popup_in_progress_i32 = 1;
    (*(int * *)&net_popup_queue_head) = (int *)*entry;
    if ((*(int * *)&net_popup_queue_head) == (int *)0x0) {
      net_popup_queue_tail = 0;
    }
    if ((entry[2] != 0) || (entry[3] != 0)) {
      arg_ptr = entry + 7;
    }
    if (entry[2] != 0) {
      for (i = 0; i < entry[2]; i++) {
        crt_strcpy(((i8 *)&minimap_window_block.text_string_args) + i * 0x104,arg_ptr);
        len = _strlen(((i8 *)&minimap_window_block.text_string_args) + i * 0x104);
        arg_ptr = (int *)((int)arg_ptr + len + 1);
      }
    }
    if (entry[3] != 0) {
      for (i = 0; i < entry[3]; i++) {
        crt_memcpy(((i8 *)&minimap_window_block.text_number_args) + i * 4,arg_ptr,4);
        arg_ptr++;
      }
    }
    dlg_pending_idle_callback = ((i8*)(turn_popup_timeout_idle));
    switch(entry[1]) {
    case 0:
      popup_game((iptr)&str_retiredie);
      break;
    case 1:
      popup_game((iptr)&str_retireai);
      break;
    case 2:
      dlg_game_txt_with_unit((iptr)&str_barbarians_2,entry[4]);
      break;
    case 3:
      popup_game_with_sprite((iptr)&str_globalwarming_2,(iptr)&popup_info_icon_sprite,0);
      break;
    case 4:
      popup_game_with_sprite((iptr)&str_fearwarming_2,(iptr)&popup_info_icon_sprite,0);
      break;
    case 5:
      historian_report_show();
      break;
    case 6:
      popup_game_with_sprite((iptr)&str_eaglehaslanded_2,(iptr)&popup_info_icon_sprite,0);
      break;
    case 7:
      popup_game_with_sprite((iptr)&str_scenarioends_2,(iptr)&tutorial_icon_sprite_block.tutorial_icon_sprite,0);
      break;
    case 8:
      popup_game_with_sprite((iptr)&str_scenarioend_2,(iptr)&tutorial_icon_sprite_block.tutorial_icon_sprite,0);
      break;
    case 9:
      text = civ_leader_title(human_civ[0]);
      text_set_string_arg(0,text);
      text = civ_leader_name(human_civ[0]);
      text_set_string_arg(1,text);
      popup_game_with_sprite((iptr)&str_planretire_2,(iptr)&tutorial_icon_sprite_block.tutorial_icon_sprite,0);
      break;
    case 10:
      text = civ_leader_name(human_civ[0]);
      text_set_string_arg(1,text);
      popup_game_with_sprite((iptr)&str_doretire_2,(iptr)&tutorial_icon_sprite_block.tutorial_icon_sprite,0);
      break;
    case 0xb:
      popup_game((iptr)&str_launched);
      spaceship_wnd_run(-entry[4]);
      break;
    case 0xc:
      popup_game((iptr)&str_spacereturns_2);
      break;
    case 0xd:
      popup_game((iptr)&str_spacedestroyed_2);
      break;
    case 0xe:
      music_play_track(2,1);
      popup_game_with_sprite((iptr)&str_destroyed_2,(iptr)(((i8 *)&road_sprites_block.civ_portrait_sprites) + entry[4] * 0x3c),0);
      break;
    case 0xf:
      snd_play_effect((-(uint)(entry[5] == 0) & 0x14) + 0x16,1,0,0);
      dlg_game_txt_with_unit((iptr)&str_caravan_6,entry[4]);
      break;
    case 0x10:
      snd_play_effect((-(uint)(entry[5] == 0) & 0x14) + 0x16,1,0,0);
      dlg_game_txt_with_unit((iptr)&str_foodcaravan_4,entry[4]);
      break;
    case 0x11:
      dlg_game_txt_with_unit_flags((iptr)&str_caravanother_3,entry[4],entry[5]);
      break;
    case 0x12:
      dialog_load_game_text(&dlg,(iptr)&str_startwonder_2);
      dialog_add_sprite
                ((DialogOptionList *)&dlg,(iptr)(((i8 *)&caption_close_button_sprite_block.improvement_icon_sprites) + entry[4] * 0x3c),0,0);
      dialog_set_image_zoom((DialogWindowView *)&dlg,entry[5]);
      dlg_show_modal(&dlg,0);
      break;
    case 0x13:
      dialog_load_game_text(&dlg,(iptr)&str_switchwonder_2);
      dialog_add_sprite
                ((DialogOptionList *)&dlg,(iptr)(((i8 *)&caption_close_button_sprite_block.improvement_icon_sprites) + entry[4] * 0x3c),0,0);
      dialog_set_image_zoom((DialogWindowView *)&dlg,entry[5]);
      dlg_show_modal(&dlg,0);
      break;
    case 0x14:
      dialog_load_game_text(&dlg,(iptr)&str_abandonwonder_2);
      dialog_add_sprite
                ((DialogOptionList *)&dlg,(iptr)(((i8 *)&caption_close_button_sprite_block.improvement_icon_sprites) + entry[4] * 0x3c),0,0);
      dialog_set_image_zoom((DialogWindowView *)&dlg,entry[5]);
      dlg_show_modal(&dlg,0);
      break;
    case 0x15:
      dlg_game_txt_with_unit((iptr)&str_paradrop_2,entry[4]);
      break;
    case 0x16:
      popup_game((iptr)&str_schism_2);
      break;
    case 0x17:
      text = popup_game_with_sprite((iptr)&str_canescape,(iptr)&popup_info_icon_sprite,0);
      net_send_message(0x77,*(i32 *)
                               (((i8 *)&net_session_block.net_player_slots) + *(int *)(((i8 *)&net_session_block.net_civ_slots) + entry[4] * 4) * 0x54),
                         text,0,0,0,0,0,0,0);
      break;
    case 0x18:
      popup_game_with_city((iptr)&str_escape,entry[4]);
      break;
    case 0x19:
      dialog_load_game_text(&dlg,(iptr)&str_capturewonder);
      dialog_add_sprite
                ((DialogOptionList *)&dlg,(iptr)(((i8 *)&caption_close_button_sprite_block.improvement_icon_sprites) + entry[4] * 0x3c),0,0);
      dialog_set_image_zoom((DialogWindowView *)&dlg,8);
      dlg_show_modal(&dlg,0);
      break;
    case 0x1a:
      dialog_load_game_text(&dlg,(iptr)&str_lostwonder);
      dialog_add_sprite
                ((DialogOptionList *)&dlg,(iptr)(((i8 *)&caption_close_button_sprite_block.improvement_icon_sprites) + entry[4] * 0x3c),0,0);
      dialog_set_image_zoom((DialogWindowView *)&dlg,8);
      dlg_show_modal(&dlg,0);
      break;
    case 0x1b:
      snd_play_effect(5,0,0,0);
      popup_city_picture_zoom((iptr)&str_citycapture,entry[5],0x46,1,entry[4]);
      break;
    case 0x1c:
      snd_play_effect(5,0,0,0);
      popup_city_picture_zoom((iptr)&str_citywinally,entry[5],0x46,1,entry[4]);
      break;
    case 0x1d:
      snd_play_effect(5,0,0,0);
      popup_city_picture_zoom((iptr)&str_cityloseally,entry[5],0x46,1,entry[4]);
      break;
    case 0x1e:
      snd_play_effect(5,0,0,0);
      popup_city_picture_zoom((iptr)&str_citycapture2,entry[5],0x46,1,entry[4]);
      break;
    case 0x1f:
      dlg_game_txt_with_unit((iptr)&str_partisans,entry[4]);
      break;
    case 0x20:
      dlg_game_txt_with_unit((iptr)&str_promoted,entry[4]);
      break;
    case 0x21:
      popup_game_with_sprite((iptr)&str_incorruptible_2,(iptr)&government_sprites_block.government_sprite_democracy,0);
      break;
    case 0x22:
      dlg_game_txt_with_unit((iptr)&str_deserted_2,entry[4]);
      break;
    case 0x23:
      text = dlg_game_txt_with_unit((iptr)&str_desert_3,entry[5]);
      net_send_message(0x7b,*(i32 *)
                               (((i8 *)&net_session_block.net_player_slots) + *(int *)(((i8 *)&net_session_block.net_civ_slots) + entry[4] * 4) * 0x54),
                         text,0,0,0,0,0,0,0);
      break;
    case 0x24:
      text = dlg_game_txt_with_unit((iptr)&str_desert2,entry[5]);
      net_send_message(0x7b,*(i32 *)
                               (((i8 *)&net_session_block.net_player_slots) + *(int *)(((i8 *)&net_session_block.net_civ_slots) + entry[4] * 4) * 0x54),
                         text,0,0,0,0,0,0,0);
      break;
    case 0x25:
      dlg_game_txt_with_unit((iptr)&str_blewitup_2,entry[4]);
      break;
    case 0x26:
      popup_game_with_sprite((iptr)&str_bond007_2,(iptr)(((i8 *)&pollution_sprite_block.unit_sprites) + entry[4] * 0x3c),entry[5]);
      break;
    case 0x27:
      popup_game_with_sprite((iptr)&str_bond_2,(iptr)(((i8 *)&pollution_sprite_block.unit_sprites) + entry[4] * 0x3c),entry[5]);
      break;
    case 0x28:
      popup_game_with_sprite((iptr)&str_bondglory_2,(iptr)(((i8 *)&pollution_sprite_block.unit_sprites) + entry[4] * 0x3c),entry[5]);
      break;
    case 0x29:
      popup_game_with_improvement((iptr)&str_useweapons,0x3e,8);
      break;
    case 0x2a:
      popup_game_with_improvement((iptr)&str_sdi,0x11,8);
      break;
    case 0x2b:
      popup_game_with_sprite((iptr)&str_changed,(iptr)(((i8 *)&government_sprites_block.government_sprites) + entry[4] * 0x3c),entry[5]);
      break;
    case 0x2c:
      popup_game_with_sprite((iptr)&str_overthrown,(iptr)(((i8 *)&government_sprites_block.government_sprites) + entry[4] * 0x3c),entry[5]);
      break;
    case 0x2d:
      dlg_game_txt_with_unit((iptr)&str_breakcease_2,entry[4]);
      break;
    case 0x2e:
      dlg_game_txt_with_unit((iptr)&str_sneak,entry[4]);
      break;
    case 0x2f:
      dlg_game_txt_with_unit((iptr)&str_missileattack,entry[4]);
      break;
    case 0x30:
      dlg_game_txt_with_unit((iptr)&str_pearlharbor,entry[4]);
      break;
    case 0x31:
      popup_game_with_improvement((iptr)&str_battery2,entry[4],8);
      break;
    case 0x32:
      popup_game_with_improvement((iptr)&str_battery,entry[4],8);
      break;
    case 0x33:
      dlg_game_txt_with_unit((iptr)&str_scramble,entry[4]);
      break;
    case 0x34:
      dlg_game_txt_with_unit((iptr)&str_amphibmotize,entry[4]);
      break;
    case 0x35:
      popup_game((iptr)&str_multiplelose);
      break;
    case 0x36:
      popup_game((iptr)&str_multiplewin);
      break;
    case 0x37:
      dlg_game_txt_with_unit_flags((iptr)&str_ransom,entry[4],0);
      break;
    case 0x38:
      popup_game_with_sprite((iptr)&str_activateally_2,(iptr)((game.advance_known_by[0xf] != '\0') ? ((i8 *)&diplo_popup_portrait_sprite) : ((i8 *)&signal_allied_icon_sprite)),0);
      break;
    case 0x39:
      popup_game_with_sprite((iptr)&str_allyhelps_2,(iptr)((game.advance_known_by[0xf] != '\0') ? ((i8 *)&diplo_popup_portrait_sprite) : ((i8 *)&signal_allied_icon_sprite)),0);
      break;
    case 0x3a:
      popup_game((iptr)&str_cancelpeace_2);
      break;
    case 0x3b:
      popup_game((iptr)&str_allyunderattack);
      break;
    case 0x3c:
      popup_game((iptr)&str_allyattacking);
      break;
    case 0x3d:
      civs[human_civ[0]].last_treaty_turn[entry[4]] = game.turn;
      civs[entry[4]].last_treaty_turn[human_civ[0]] = game.turn;
      if (parley_wnd_block.parley_other_civ == -1) {
        parley_wnd_block.parley_other_civ = -2;
        text_clear();
        text = civ_leader_title(entry[4]);
        text_append(text);
        text_append_space();
        text = civ_leader_name(entry[4]);
        text_append(text);
        text_append_space();
        text_append_label(0x8c);
        text_append_space();
        text = civ_name_plural(entry[4]);
        text_append(text);
        text_set_string_arg(0,(iptr)&map_views_block.text_buffer);
        text = civ_leader_name(human_civ[0]);
        text_set_string_arg(1,text);
        text = civ_name_plural(human_civ[0]);
        text_set_string_arg(2,text);
        if (*(char *)&civs[entry[4]].attitude[human_civ[0]] == '\0') {
          attitude_level = 0;
        }
        else {
          attitude_level = diplo_attitude_level((uint)civs[entry[4]].attitude[human_civ[0]]);
        }
        text = label_string(attitude_names[attitude_level]);
        text_set_string_arg(3,text);
        dlg_pending_idle_callback = ((i8*)(net_popup_idle_autoclose));
        choice = popup_game_with_sprite((iptr)&str_parleyrequest,(iptr)&popup_info_icon_sprite,0);
        if (net_session_block.net_host_handoff_stage == '\0') {
          if (net_session_block.nm_parley_cancel_count == 0) {
            net_send_message(0x80,*(i32 *)
                                     (((i8 *)&net_session_block.net_player_slots) + *(int *)(((i8 *)&net_session_block.net_civ_slots) + entry[4] * 4) * 0x54
                                     ),choice,0,0,0,0,0,0,0);
          }
          if (net_session_block.nm_parley_cancel_count == 0) {
            if (choice == 1) {
              text = entry[4];
              operator_delete(entry);
              net_session_block.net_popup_in_progress_i32 = 0;
              parley_wnd_open((ViewWindow *)((i8 *)&parley_wnd_block.parley_wnd),text,2);
              eh_state = 0xffffffff;
              /* inlined unwind funclet 0051399d */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
              goto done;
            }
          }
          else {
            net_session_block.nm_parley_cancel_count = 0;
            text = civ_name_plural(entry[4]);
            text_set_string_arg(0,text);
            dlg_pending_idle_callback = ((i8*)(turn_popup_timeout_idle));
            popup_game_with_sprite((iptr)&str_parleycancel_4,(iptr)&popup_info_icon_sprite,0);
          }
          parley_wnd_block.parley_other_civ = -1;
          mp_meeting_pending = 0;
        }
        else {
          net_send_message(0x80,*(i32 *)
                                   (((i8 *)&net_session_block.net_player_slots) + *(int *)(((i8 *)&net_session_block.net_civ_slots) + entry[4] * 4) * 0x54),
                             2,0,0,0,0,0,0,0);
          parley_wnd_block.parley_other_civ = -1;
          mp_meeting_pending = 0;
        }
      }
      else {
        net_send_message(0x80,*(i32 *)
                                 (((i8 *)&net_session_block.net_player_slots) + *(int *)(((i8 *)&net_session_block.net_civ_slots) + entry[4] * 4) * 0x54),2,
                           0,0,0,0,0,0,0);
      }
      break;
    case 0x3e:
      dlg_game_txt_with_unit_flags((iptr)&str_upgrade_2,entry[4],(entry[5] == 0) - 1 & 8);
      break;
    case 0x3f:
      if (*(int *)(((i8 *)&net_session_block.net_player_slots) + *(int *)(((i8 *)&net_session_block.net_civ_slots) + human_civ[0] * 4) * 0x54) != entry[4])
      {
        popup_game_with_sprite((iptr)&str_newplayer_2,(iptr)&popup_info_icon_sprite,0);
      }
      break;
    case 0x40:
      dlg_load_game_section(&dlg,(iptr)&str_newturntimerclient,0x2000000);
      text = label_string(*(i32 *)(label_string_ids + 0xd50));
      dialog_add_button((DialogButtonsView *)&dlg,text);
      text = label_string(*(i32 *)(label_string_ids + 0xd54));
      dialog_add_button((DialogButtonsView *)&dlg,text);
      dlg_show_modal(&dlg,0x28);
      net_send_message(0x56,0,dlg.result_extra,0,0,0,0,0,0,0);
      break;
    case 0x41:
      popup_game_with_sprite((iptr)&str_newturntimerno,(iptr)&popup_info_icon_sprite,0);
      break;
    case 0x42:
      popup_game_with_sprite((iptr)&str_newturntimeryes,(iptr)&popup_info_icon_sprite,0);
      break;
    case 0x43:
      dlg_load_game_section(&dlg,(iptr)&str_pmchangeclient,0x2000000);
      text = label_string(*(i32 *)(label_string_ids + 0xd50));
      dialog_add_button((DialogButtonsView *)&dlg,text);
      text = label_string(*(i32 *)(label_string_ids + 0xd54));
      dialog_add_button((DialogButtonsView *)&dlg,text);
      dlg_show_modal(&dlg,0);
      net_send_message(0x57,0,dlg.result_extra,0,0,0,0,0,0,0);
      break;
    case 0x44:
      popup_game_with_sprite((iptr)&str_pmchangeno_2,(iptr)&popup_info_icon_sprite,0);
      break;
    case 0x45:
      popup_game_with_sprite((iptr)&str_pmchangeyes_2,(iptr)&popup_info_icon_sprite,0);
      break;
    case 0x46:
      snd_play_effect(0x23,1,0,0);
      city_notify_dialog_ex((iptr)&str_manhattan_2,entry[4],1,(iptr)&caption_close_button_sprite_block.city_notify_sprite);
      break;
    case 0x47:
      dialog_load_game_text(&dlg,(iptr)&str_built2_2);
      if (entry[4] < 0) {
        icon_sprite = ((i8 *)&caption_close_button_sprite_block.improvement_icon_sprites) + entry[5] * 0x3c;
      }
      else {
        icon_sprite = ((i8 *)&caption_close_button_sprite_block.wonder_icon_sprites) + entry[4] * 0x3c;
      }
      dialog_add_sprite((DialogOptionList *)&dlg,(iptr)icon_sprite,0,0);
      dialog_set_image_zoom((DialogWindowView *)&dlg,8);
      dlg_show_modal(&dlg,0);
      break;
    case 0x48:
      popup_game((iptr)&str_movecapital_2);
      break;
    case 0x49:
      popup_game((iptr)&str_astronauts_2);
      break;
    case 0x4a:
      dialog_load_game_text(&dlg,(iptr)&str_almostwonder_2);
      dialog_add_sprite
                ((DialogOptionList *)&dlg,(iptr)(((i8 *)&caption_close_button_sprite_block.improvement_icon_sprites) + entry[4] * 0x3c),0,0);
      dialog_set_image_zoom((DialogWindowView *)&dlg,8);
      dlg_show_modal(&dlg,0);
      break;
    case 0x4b:
      dialog_load_game_text(&dlg,(iptr)&str_stillwonder1);
      dialog_add_sprite
                ((DialogOptionList *)&dlg,(iptr)(((i8 *)&caption_close_button_sprite_block.improvement_icon_sprites) + entry[4] * 0x3c),0,0);
      dialog_set_image_zoom((DialogWindowView *)&dlg,8);
      dlg_show_modal(&dlg,0);
      break;
    case 0x4c:
      dialog_load_game_text(&dlg,(iptr)&str_stillwonder2);
      dialog_add_sprite
                ((DialogOptionList *)&dlg,(iptr)(((i8 *)&caption_close_button_sprite_block.improvement_icon_sprites) + entry[4] * 0x3c),0,0);
      dialog_set_image_zoom((DialogWindowView *)&dlg,8);
      dlg_show_modal(&dlg,0);
      break;
    case 0x4d:
      dialog_load_game_text(&dlg,(iptr)&str_endwonder_4);
      dialog_add_sprite
                ((DialogOptionList *)&dlg,
                 (iptr)(((i8 *)&government_sprites_block.advance_category_icon_sprites) +
                       (char)advances[entry[4]].category * 0xf0 +
                       (char)advances[entry[4]].epoch * 0x3c),0,0);
      dialog_add_sprite
                ((DialogOptionList *)&dlg,(iptr)(((i8 *)&caption_close_button_sprite_block.improvement_icon_sprites) + entry[5] * 0x3c),0,0);
      dialog_set_image_zoom((DialogWindowView *)&dlg,8);
      dlg_show_modal(&dlg,0);
      break;
    case 0x4e:
      dlg_game_txt_with_unit((iptr)&str_barbariansland,entry[4]);
      break;
    case 0x4f:
      dialog_init_default(&dlg);
      for (i = 0; i < entry[2]; i++) {
        dialog_add_line
                  ((DialogAddLineView *)&dlg,(iptr)(((i8 *)&minimap_window_block.text_string_args) + i * 0x104),0xffffffff,
                   0xffffffff,0xffffffff,0);
      }
      dlg_show_modal(&dlg,0);
      break;
    case 0x50:
      popup_game_with_sprite((iptr)&str_warends,(iptr)&ceasefire_icon_sprite,0);
      break;
    case 0x51:
      dlg_game_txt_with_unit((iptr)&str_militaryaid1,entry[4]);
      break;
    case 0x52:
      dlg_game_txt_with_unit((iptr)&str_militaryaid2,entry[4]);
      break;
    case 0x53:
      popup_game_with_sprite((iptr)&str_lostclient_2,(iptr)&popup_info_icon_sprite,0);
      break;
    case 0x54:
      popup_game_with_advance((iptr)&str_goldenage_2,0x3c,8);
      break;
    case 0x55:
      snd_play_effect(0x44,1,0,0);
      popup_game_with_sprite((iptr)&str_enemyembassy_2,(iptr)&popup_info_icon_sprite,0);
      break;
    case 0x56:
      snd_play_effect(0x44,1,0,0);
      popup_game_with_sprite((iptr)&str_enemyinvestigate_2,(iptr)&popup_info_icon_sprite,0);
      break;
    case 0x57:
      choice = civ_has_advance(entry[4],0x23);
      if (choice == 0) {
        snd_play_effect(0x44,1,0,0);
      }
      else {
        snd_play_effect(0x27,1,0,0);
      }
      popup_game_with_sprite((iptr)&str_steal_2,(iptr)&popup_info_icon_sprite,0);
      break;
    case 0x58:
      snd_play_effect(0x44,1,0,0);
      popup_game_with_sprite((iptr)&str_foiledagain,(iptr)&popup_info_icon_sprite,0);
      break;
    case 0x59:
      choice = civ_has_advance(entry[5],0x23);
      if (choice == 0) {
        snd_play_effect(0x44,1,0,0);
      }
      else {
        snd_play_effect(0x27,1,0,0);
      }
      popup_game_with_sprite((iptr)&str_sabotageone_2,(iptr)(((i8 *)&caption_close_button_sprite_block.improvement_icon_sprites) + entry[4] * 0x3c),8);
      break;
    case 0x5a:
      choice = civ_has_advance(entry[4],0x23);
      if (choice == 0) {
        snd_play_effect(0x44,1,0,0);
      }
      else {
        snd_play_effect(0x27,1,0,0);
      }
      popup_game((iptr)&str_sabotagetwo_2);
      break;
    case 0x5b:
      snd_play_effect(0x44,1,0,0);
      popup_game_with_sprite((iptr)&str_watersupply_2,(iptr)&popup_info_icon_sprite,0);
      break;
    case 0x5c:
      text_clear();
      text_append((iptr)&str_plantednuke_2);
      popup_game_with_improvement((iptr)&map_views_block.text_buffer,0x3e,8);
      break;
    case 0x5d:
      text_clear();
      text_append((iptr)&str_plantednuke2);
      popup_game_with_improvement((iptr)&map_views_block.text_buffer,0x3e,8);
      break;
    case 0x5e:
      snd_play_effect(0x44,1,0,0);
      popup_game((iptr)&str_civilwar_2);
      break;
    case 0x5f:
      snd_play_effect(0x5d,0,0,0);
      dlg_game_txt_with_unit((iptr)&str_upmine,entry[4]);
      break;
    case 0x60:
      snd_play_effect(0x5d,0,0,0);
      dlg_game_txt_with_unit((iptr)&str_upyours,entry[4]);
      break;
    case 0x61:
      snd_play_effect(0x5d,0,0,0);
      dlg_game_txt_with_unit((iptr)&str_upyourstoo,entry[4]);
      break;
    case 0x62:
      popup_game((iptr)&str_mercdeclare_2);
      break;
    case 99:
      popup_game_with_advance((iptr)&str_tookciv,entry[4],0);
      break;
    case 100:
      if ((parley_wnd_block.parley_wnd_closed == 0) && (entry[4] == parley_wnd_block.parley_other_civ)) {
        parley_reveal_units_prompt_open = 1;
        dlg_load_game_section(&dlg,(iptr)&str_revealunitorigins,0x2000000);
        text = label_string(*(i32 *)(label_string_ids + 0xdd4));
        dialog_add_button((DialogButtonsView *)&dlg,text);
        text = label_string(*(i32 *)(label_string_ids + 0xdd8));
        dialog_add_button((DialogButtonsView *)&dlg,text);
        dlg_show_modal(&dlg,0x14);
        if (dlg.result_extra == 1) {
          parley_wnd_block.parley_local_units_revealed = 1;
          if (parley_wnd_block.parley_mode == 2) {
            ctrl_show_and_redraw(parley_wnd_block.parley_conceal_info_button);
            ctrl_enable(parley_wnd_block.parley_conceal_info_button);
            control_hide(parley_wnd_block.parley_reveal_info_button);
            ctrl_disable(parley_wnd_block.parley_reveal_info_button);
          }
          else {
            control_hide(parley_wnd_block.parley_conceal_info_button);
            ctrl_disable(parley_wnd_block.parley_conceal_info_button);
            control_hide(parley_wnd_block.parley_reveal_info_button);
            ctrl_disable(parley_wnd_block.parley_reveal_info_button);
          }
          net_send_message(0xa7,*(i32 *)
                                   (((i8 *)&net_session_block.net_player_slots) +
                                   *(int *)(((i8 *)&net_session_block.net_civ_slots) + parley_wnd_block.parley_other_civ * 4) * 0x54),human_civ[0],
                             (int)parley_wnd_block.parley_local_units_revealed,0,0,0,0,0,0);
          if (((parley_wnd_block.parley_mode == 0xe) && (parley_wnd_block.parley_barter_want_kind == 2)) ||
             ((parley_wnd_block.parley_mode == 0xf && (parley_wnd_block.parley_demand_kind == 2)))) {
            ctrl_show_and_redraw(parley_wnd_block.parley_hide_origin_button);
            control_hide(parley_wnd_block.parley_reveal_origin_button);
            parley_wnd_block.parley_local_units_revealed = 1;
            ctrl_enable(parley_wnd_block.parley_sort_by_unit_buttons);
            ctrl_enable(parley_wnd_block.parley_sort_by_city_buttons);
            parley_draw_unit_list(0);
          }
        }
        parley_reveal_units_prompt_open = 0;
      }
      break;
    case 0x65:
      if ((parley_wnd_block.parley_wnd_closed == 0) && (entry[4] == parley_wnd_block.parley_other_civ)) {
        parley_reveal_city_prompt_open = 1;
        dlg_load_game_section(&dlg,(iptr)&str_revealcityinfo,0x2000000);
        text = label_string(*(i32 *)(label_string_ids + 0xddc));
        dialog_add_button((DialogButtonsView *)&dlg,text);
        text = label_string(*(i32 *)(label_string_ids + 0xdd8));
        dialog_add_button((DialogButtonsView *)&dlg,text);
        dlg_show_modal(&dlg,0x14);
        if (dlg.result_extra == 1) {
          parley_wnd_block.parley_local_cities_revealed = 1;
          if (parley_wnd_block.parley_mode == 2) {
            ctrl_show_and_redraw(parley_wnd_block.parley_conceal_info_button);
            ctrl_enable(parley_wnd_block.parley_conceal_info_button);
            control_hide(parley_wnd_block.parley_reveal_info_button);
            ctrl_disable(parley_wnd_block.parley_reveal_info_button);
          }
          else {
            control_hide(parley_wnd_block.parley_conceal_info_button);
            ctrl_disable(parley_wnd_block.parley_conceal_info_button);
            control_hide(parley_wnd_block.parley_reveal_info_button);
            ctrl_disable(parley_wnd_block.parley_reveal_info_button);
          }
          net_send_message(0xa5,*(i32 *)
                                   (((i8 *)&net_session_block.net_player_slots) +
                                   *(int *)(((i8 *)&net_session_block.net_civ_slots) + parley_wnd_block.parley_other_civ * 4) * 0x54),human_civ[0],
                             (int)parley_wnd_block.parley_local_cities_revealed,0,0,0,0,0,0);
          if (((parley_wnd_block.parley_mode == 0xe) && (parley_wnd_block.parley_barter_want_kind == 3)) ||
             ((parley_wnd_block.parley_mode == 0xf && (parley_wnd_block.parley_demand_kind == 3)))) {
            ctrl_show_and_redraw(parley_wnd_block.parley_hide_origin_button);
            control_hide(parley_wnd_block.parley_reveal_origin_button);
            parley_draw_city_list(0);
          }
        }
        parley_reveal_city_prompt_open = 0;
      }
    }
    operator_delete(entry);
    net_session_block.net_popup_in_progress_i32 = 0;
  }
  eh_state = 0xffffffff;
  /* inlined unwind funclet 0051399d */ { dialog_dtor((Dialog *)((iptr)&dlg)); }
done:
  return;
}

/* 00514220 auto */
NetMsgQueue * __thiscall net_msgq_ctor(NetMsgQueue *self)

{
  _memset(self,0,24000);
  net_msgq_reset(self);
  return self;
}

/* 00514254 auto */
void __thiscall net_msgq_clear(NetMsgQueue *self)

{
  net_msgq_reset(self);
  return;
}

/* 00514272 auto */
void __thiscall net_msgq_reset(NetMsgQueue *self)

{
  u8 *field_ptr;
  int i;
  
  for (i = 0; i < 2000; i++) {
    if (*(int *)(self->msg_slots + i * 0xc + 4) != 0) {
      operator_delete(*(void **)(self->msg_slots + i * 0xc + 4));
      field_ptr = self->msg_slots + i * 0xc + 4;
      field_ptr[0] = '\0';
      field_ptr[1] = '\0';
      field_ptr[2] = '\0';
      field_ptr[3] = '\0';
    }
    field_ptr = self->msg_slots + i * 0xc + 8;
    field_ptr[0] = '\0';
    field_ptr[1] = '\0';
    field_ptr[2] = '\0';
    field_ptr[3] = '\0';
    field_ptr = self->msg_slots + i * 0xc;
    field_ptr[0] = '\0';
    field_ptr[1] = '\0';
    field_ptr[2] = '\0';
    field_ptr[3] = '\0';
  }
  self->low_read_index = 400;
  self->main_tail = 400;
  self->main_count = 0;
  self->prio_head = 0;
  self->prio_tail = 0;
  self->prio_count = 0;
  return;
}

/* 0051435f auto */
i32 __cdecl net_msg_is_priority(int msg_type)

{
  i32 is_priority;
  
  if ((msg_type < 0x2a) || (0x66 < msg_type)) {
    is_priority = 0;
  }
  else {
    is_priority = 1;
  }
  return is_priority;
}

/* 0051438f auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __thiscall
net_msgq_enqueue(NetMsgQueueEnqueueView *self,int sender,iptr msg,uint msg_size)

{
  int is_priority;
  void *msg_buf;
  i8 lost_msg_text[256];
  iptr msg_copy;
  i8 lost_prio_text[256];
  
  if ((((game.multiplayer == 5) || (game.multiplayer == 6)) && (sender != 0)) &&
     (sender != 0xff)) {
    if (net_session_block.net_host_flag == '\0') {
      sender = 0;
    }
    else {
      sender = 1;
    }
  }
  if (*(int *)(msg + 4) == 0x2b) {
    net_session_block.nm_heart_beat_count_i32++;
    net_send_message(0x2c,sender,0,0,0,0,0,0,0,0);
  }
  else if (*(int *)(msg + 4) == 0x2c) {
    net_session_block.nm_heartbeat_ack_count++;
  }
  else {
    is_priority = net_msg_is_priority(*(i32 *)(msg + 4));
    if (is_priority == 0) {
      if ((self->normal_head == self->normal_tail) && (self->normal_count != 0)) {
        crt_strcpy(lost_msg_text,str_message_lost_in_enqueuemessage);
        crt_strcat(lost_msg_text,((char *)&str_nm_datagram) + *(int *)(msg + 4) * 0x20);
        crt_strcat(lost_msg_text,str_from_d_size_d_2);
        dbg_logf_int2((iptr)lost_msg_text,sender,msg_size);
        return 0;
      }
      if (((int)self->normal_head < 400) || (1999 < (int)self->normal_head)) {
        err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_head_400_head_max_msgs_in_queue,(iptr)&str_d_ss_franklinton_netmessagequeue_cpp_4,0x130);
      }
      if (((int)self->normal_tail < 400) || (1999 < (int)self->normal_tail)) {
        err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_tail_400_tail_max_msgs_in_queue,(iptr)&str_d_ss_franklinton_netmessagequeue_cpp_5,0x131);
      }
      msg_buf = operator_new(msg_size);
      *(void **)(self->msg_slots + self->normal_tail * 0xc + 4) = msg_buf;
      if (*(int *)(self->msg_slots + self->normal_tail * 0xc + 4) == 0) {
        dbg_logf_int2((iptr)&str_enqueuemessage_primary_failed_to_allocat,*(i32 *)(msg + 4),*(i32 *)(msg + 8));
        return 0;
      }
      if (*(int *)(self->msg_slots + self->normal_tail * 0xc + 4) == 0) {
        err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_msgqueue_tail_pdata,(iptr)&str_d_ss_franklinton_netmessagequeue_cpp_6,0x136);
      }
      crt_memcpy(*(i32 *)(self->msg_slots + self->normal_tail * 0xc + 4),msg,msg_size);
      *(int *)(self->msg_slots + self->normal_tail * 0xc) = sender;
      *(uint *)(self->msg_slots + self->normal_tail * 0xc + 8) = msg_size;
      self->normal_tail = (int)(self->normal_tail + 1) % 2000;
      if (self->normal_tail == 0) {
        self->normal_tail = 400;
      }
      self->normal_count++;
      if ((int)net_session_block.net_msgq_normal_peak < (int)self->normal_count) {
        net_session_block.net_msgq_normal_peak = self->normal_count;
      }
    }
    else {
      if ((self->prio_head == self->prio_tail) && (self->prio_count != 0)) {
        crt_strcpy(lost_prio_text,str_message_lost_in_alpha_enqueuemessage);
        crt_strcat(lost_prio_text,((char *)&str_nm_datagram) + *(int *)(msg + 4) * 0x20);
        crt_strcat(lost_prio_text,str_from_d_size_d);
        dbg_logf_int2((iptr)lost_prio_text,sender,msg_size);
        return 0;
      }
      if (((int)self->prio_head < 0) || (399 < (int)self->prio_head)) {
        err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_alphahead_0_alphahead_400,(iptr)&str_d_ss_franklinton_netmessagequeue_cpp,0x10c);
      }
      if (((int)self->prio_tail < 0) || (399 < (int)self->prio_tail)) {
        err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_alphatail_0_alphatail_400,(iptr)&str_d_ss_franklinton_netmessagequeue_cpp_2,0x10d);
      }
      msg_buf = operator_new(msg_size);
      *(void **)(self->msg_slots + self->prio_tail * 0xc + 4) = msg_buf;
      if (*(int *)(self->msg_slots + self->prio_tail * 0xc + 4) == 0) {
        msg_copy = msg;
        dbg_logf_int2((iptr)&str_enqueuemessage_alpha_failed_to_allocate,*(i32 *)(msg + 4),*(i32 *)(msg + 8));
        return 0;
      }
      if (*(int *)(self->msg_slots + self->prio_tail * 0xc + 4) == 0) {
        err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_msgqueue_alphatail_pdata,(iptr)&str_d_ss_franklinton_netmessagequeue_cpp_3,0x112);
      }
      crt_memcpy(*(i32 *)(self->msg_slots + self->prio_tail * 0xc + 4),msg,msg_size);
      *(int *)(self->msg_slots + self->prio_tail * 0xc) = sender;
      *(uint *)(self->msg_slots + self->prio_tail * 0xc + 8) = msg_size;
      self->prio_tail = (int)(self->prio_tail + 1) % 400;
      self->prio_count++;
      if ((int)net_session_block.net_msgq_priority_peak < (int)self->prio_count) {
        net_session_block.net_msgq_priority_peak = self->prio_count;
      }
    }
  }
  return 1;
}

/* 005149d6 auto */
i32 __thiscall
net_msgq_dequeue(NetMessageQueue *self,iptr out_sender,iptr out_msg,iptr out_size,int priority_only)

{
  u8 *slot_field;
  i32 result;
  
  if (self->high_count == 0) {
    if ((priority_only == 0) && (self->low_count != 0)) {
      *(i32 *)out_sender = *(i32 *)(self->msg_slots + self->low_read_index * 0xc);
      slot_field = self->msg_slots + self->low_read_index * 0xc;
      slot_field[0] = '\0';
      slot_field[1] = '\0';
      slot_field[2] = '\0';
      slot_field[3] = '\0';
      *(i32 *)out_msg = *(i32 *)(self->msg_slots + self->low_read_index * 0xc + 4);
      slot_field = self->msg_slots + self->low_read_index * 0xc + 4;
      slot_field[0] = '\0';
      slot_field[1] = '\0';
      slot_field[2] = '\0';
      slot_field[3] = '\0';
      *(i32 *)out_size = *(i32 *)(self->msg_slots + self->low_read_index * 0xc + 8);
      slot_field = self->msg_slots + self->low_read_index * 0xc + 8;
      slot_field[0] = '\0';
      slot_field[1] = '\0';
      slot_field[2] = '\0';
      slot_field[3] = '\0';
      self->low_read_index = (int)(self->low_read_index + 1) % 2000;
      if (self->low_read_index == 0) {
        self->low_read_index = 400;
      }
      self->low_count--;
      result = 1;
    }
    else {
      result = 0;
    }
  }
  else {
    *(i32 *)out_sender = *(i32 *)(self->msg_slots + self->high_read_index * 0xc);
    slot_field = self->msg_slots + self->high_read_index * 0xc;
    slot_field[0] = '\0';
    slot_field[1] = '\0';
    slot_field[2] = '\0';
    slot_field[3] = '\0';
    *(i32 *)out_msg = *(i32 *)(self->msg_slots + self->high_read_index * 0xc + 4);
    slot_field = self->msg_slots + self->high_read_index * 0xc + 4;
    slot_field[0] = '\0';
    slot_field[1] = '\0';
    slot_field[2] = '\0';
    slot_field[3] = '\0';
    *(i32 *)out_size = *(i32 *)(self->msg_slots + self->high_read_index * 0xc + 8);
    slot_field = self->msg_slots + self->high_read_index * 0xc + 8;
    slot_field[0] = '\0';
    slot_field[1] = '\0';
    slot_field[2] = '\0';
    slot_field[3] = '\0';
    self->high_read_index = (int)(self->high_read_index + 1) % 400;
    self->high_count--;
    result = 1;
  }
  return result;
}

/* 0051ea0c auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl net_vote_wait_idle_cb(void)

{
  int now_ticks;
  
  net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
  if ((((net_session_block.net_host_handoff_stage == '\0') && (now_ticks = timer_ticks(), now_ticks - dialog_title_font_obj_block.dialog_timeout_start_i32 < 0x961)) &&
      (net_session_block.net_vote_replies_pending != 0)) && (net_session_block.net_vote_status != -1)) {
    return;
  }
  net_session_block.dialog_stack_top[0xf] = net_session_block.dialog_stack_top[0xf] | 0x400;
  wnd_end_modal_loop((ModalMenuWindow *)(*net_session_block.dialog_stack_top + 0x48));
  dialog_title_font_obj_block.dialog_timeout_start_i32 = timer_ticks();
  return;
}

/* 0051f11a auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl net_lock_wait_idle_cb(void)

{
  timer_ticks();
  net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
  if ((net_session_block.nm_lock_data_count != 0) || (net_session_block.nm_server_canceled_count != 0)) {
    net_session_block.dialog_stack_top[0xf] = net_session_block.dialog_stack_top[0xf] | 0x400;
    wnd_end_modal_loop((ModalMenuWindow *)(*net_session_block.dialog_stack_top + 0x48));
  }
  return;
}

/* 0051f17e auto */
void __cdecl net_pump_idle_cb(void)

{
  net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
  return;
}

/* 005233fc auto */
i32 __cdecl net_host_register_player_civ(iptr player_info,int player_id)

{
  int is_female;
  i8 saved_player_civ;
  i8 saved_turn_civ_val;
  i32 result;
  iptr saved_human_civ;
  int title_label_id;
  iptr join_civ;
  int slot;
  u8 female_byte;
  int title_idx;
  u8 portrait;
  
  if (net_session_block.net_host_flag == '\0') {
    err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_gnetmgr_bserver_2,(iptr)&str_d_ss_franklinton_startup_multiplayer_cpp_2,0x778);
  }
  saved_human_civ = human_civ[0];
  saved_turn_civ_val = game.turn_civ;
  saved_player_civ = game.player_civ;
  if (((civ_saved_cursor_x_block.saved_resume_new_game == 0) && (civ_saved_cursor_x_block.saved_turn_civ == '\0')) && (net_session_block.net_session_phase < 2)) {
    is_female = *(int *)(player_info + 0x18);
    result = *(i32 *)(player_info + 0x14);
    join_civ = *(iptr *)(player_info + 0x10);
    game.player_civ = (byte)join_civ;
    civs[(char)(byte)join_civ].tribe = (i16)result;
    portrait = (u8)result;
    civs[game.player_civ].leader_portrait = portrait;
    if (is_female != 0) {
      civs[game.player_civ].leader_portrait += 21;
    }
    human_civ[0] = (iptr)game.player_civ;
    if (net_session_block.net_session_phase < 3) {
      game.human_players = game.human_players | (byte)(1 << ((byte)join_civ & 0x1f));
    }
    else {
      net_session_block.pending_human_players = net_session_block.pending_human_players | (byte)(1 << ((byte)join_civ & 0x1f));
    }
    female_byte = (u8)is_female;
    leaders[civs[game.player_civ].tribe].female = female_byte;
    leaders[civs[game.player_civ].tribe].leader_name =
         leaders[civs[game.player_civ].tribe].names[((uint)leaders[civs[game.player_civ].tribe].female)];
    result = label_string((int)leaders[civs[game.player_civ].tribe].leader_name);
    crt_strcpy(&civ_names[game.player_civ].leader_name,result);
    if (0 < leaders[civs[game.player_civ].tribe].leader_name) {
      leaders[civs[game.player_civ].tribe].leader_name =
           -leaders[civs[game.player_civ].tribe].leader_name;
    }
    crt_strcpy(&civ_names[game.player_civ].leader_name,player_info + 0x20);
    if (*(int *)(player_info + 0x1c) != 0) {
      leaders[civs[game.player_civ].tribe].plural = -leaders[civs[game.player_civ].tribe].plural;
      leaders[civs[game.player_civ].tribe].adjective =
           -leaders[civs[game.player_civ].tribe].adjective;
      for (title_idx = 0; title_idx < 7; title_idx++) {
        if (leaders[civs[game.player_civ].tribe].titles[title_idx][is_female] < 1)
        {
          title_label_id = ~(int)leaders[civs[game.player_civ].tribe].titles[title_idx][is_female] + 1;
        }
        else {
          title_label_id = (int)leaders[civs[game.player_civ].tribe].titles[title_idx][is_female];
        }
        result = label_string(title_label_id);
        crt_strcpy(&civ_names[game.player_civ].titles[title_idx],result);
        leaders[civs[game.player_civ].tribe].titles[title_idx][is_female] =
             -leaders[civs[game.player_civ].tribe].titles[title_idx][is_female];
      }
      crt_strcpy(&civ_names[game.player_civ].tribe_name,player_info + 0x38);
      crt_strcpy(&civ_names[game.player_civ].adjective,player_info + 0x50);
      if (*(int *)(player_info + 0x68) != 0) {
        for (title_idx = 0; title_idx < 7; title_idx++) {
          crt_strcpy(&civ_names[game.player_civ].titles[title_idx],
                       title_idx * 0x18 + player_info + 0x6c);
        }
      }
    }
    civ_names[game.player_civ].city_style = (i16)*(i32 *)(player_info + 0x114);
  }
  else {
    join_civ = *(iptr *)(player_info + 0x10);
    if (net_session_block.net_session_phase < 3) {
      game.human_players = game.human_players | (byte)(1 << ((byte)join_civ & 0x1f));
    }
    else {
      net_session_block.pending_human_players = net_session_block.pending_human_players | (byte)(1 << ((byte)join_civ & 0x1f));
    }
    game.player_civ = (byte)join_civ;
    game.turn_civ = (byte)join_civ;
    human_civ[0] = join_civ;
    crt_strcpy(&civ_names[((char)(byte)join_civ)].leader_name,player_info + 0x20);
    if (0 < leaders[civs[game.player_civ].tribe].leader_name) {
      leaders[civs[game.player_civ].tribe].leader_name =
           -leaders[civs[game.player_civ].tribe].leader_name;
    }
    is_female = *(int *)(player_info + 0x18);
    civs[human_civ[0]].flags = civs[human_civ[0]].flags & 0xfdff;
    if (is_female != 0) {
      civs[human_civ[0]].flags = civs[human_civ[0]].flags | 0x200;
    }
    female_byte = (u8)is_female;
    leaders[civs[game.player_civ].tribe].female = female_byte;
  }
  for (slot = 0; (slot < 7 && (*(int *)(((i8 *)&net_session_block.net_player_slots) + slot * 0x54) != player_id));
      slot = slot + 1) {
  }
  if (slot < 7) {
    *(int *)(((i8 *)&net_session_block.net_civ_slots) + game.player_civ * 4) = slot;
    (((i32 *)&net_session_block.net_slot_civs))[slot * 0x15] = (int)game.player_civ;
    (((i8 *)&net_session_block.net_slot_active_flags))[slot * 0x54] = 1;
    if (player_id == 0) {
      (((i8 *)&net_session_block.net_slot_host_flags))[slot * 0x54] = 1;
    }
    else {
      (((i8 *)&net_session_block.net_slot_host_flags))[slot * 0x54] = 0;
    }
    result = 1;
  }
  else {
    if (net_session_block.net_session_phase < 3) {
      game.human_players = game.human_players & ~(byte)(1 << ((byte)join_civ & 0x1f));
    }
    else {
      net_session_block.pending_human_players = net_session_block.pending_human_players & ~(byte)(1 << ((byte)join_civ & 0x1f));
    }
    net_send_message(0x31,0,*(iptr *)(player_info + 0x14),*(iptr *)(player_info + 0x10),0,0,0,0,0,0);
    result = 0;
  }
  human_civ[0] = saved_human_civ;
  game.turn_civ = saved_turn_civ_val;
  game.player_civ = saved_player_civ;
  return result;
}

/* 00523d8a auto */
void __cdecl net_send_rules_tables(i32 dest_player)

{
  net_send_message(0x17,dest_player,0,0,0,0,0,0,0,0);
  net_send_message(0x18,dest_player,0,0,0,0,0,0,0,0);
  net_send_message(0x19,dest_player,0,0,0,0,0,0,0,0);
  net_send_message(0x1a,dest_player,0,0,0,0,0,0,0,0);
  net_send_message(0x1b,dest_player,0,0,0,0,0,0,0,0);
  net_send_message(0x1c,dest_player,0,0,0,0,0,0,0,0);
  net_send_message(0x1d,dest_player,0,0,0,0,0,0,0,0);
  net_send_message(0x1e,dest_player,0,0,0,0,0,0,0,0);
  net_send_message(0x21,dest_player,0,0,0,0,0,0,0,0);
  net_send_message(0x22,dest_player,0,0,0,0,0,0,0,0);
  net_send_message(0x23,dest_player,0,0,0,0,0,0,0,0);
  net_send_message(0x24,dest_player,0,0,0,0,0,0,0,0);
  return;
}

/* 00526ca0 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall parley_add_side_dialog(ViewWindow *self,int side_kind,int side)

{
  u8 *flag_ptr;
  int tmp;
  InputControl *new_input;
  iptr label;
  int header_x;
  Control *new_ctrl;
  uptr title_x;
  u32 text_x;
  uptr draw_x;
  i32 text_align;
  uptr item_buf;
  u8 *city_hide_parent;
  iptr city_hide_label;
  u8 *city_reveal_parent;
  iptr city_reveal_label;
  int city_btn_font_height;
  int city_header_height;
  int city_side_height;
  iptr city_side_title;
  u8 *offer_parent;
  int offer_row_height;
  int offer_header_height;
  int offer_title_height;
  int offer_line_height;
  int civlist_item_height;
  int civlist_box_offset;
  int civlist_header_height;
  int civlist_title_height;
  int civlist_row_height;
  int civlist_side_height;
  iptr civlist_side_title;
  u8 *map_parent;
  int map_box_offset;
  int map_header_height;
  int map_title_height;
  int map_row_height;
  int map_side_height;
  iptr map_side_title;
  u8 *proposal_parent;
  int proposal_row_height;
  int proposal_title_height;
  int proposal_line_height;
  u8 *sort_city_parent;
  u8 *sort_unit_parent;
  int unit_line_spacing;
  int unit_btn_offset;
  u8 *hide_parent;
  iptr hide_label;
  u8 *reveal_parent;
  iptr reveal_label;
  int unit_line_spacing_alt;
  int unit_btn_offset_alt;
  int unit_header_height;
  int unit_side_height;
  iptr unit_side_title;
  u8 *gold_edit_parent;
  int gold_prompt_width;
  int gold_edit_text_width;
  int gold_box_offset;
  int gold_header_height;
  iptr gold_side_title;
  int gold_title_height;
  int gold_line_height;
  int tech_header_height;
  int tech_side_height;
  iptr tech_side_title;
  u8 *gift_parent;
  int gift_row_height;
  int gift_header_height;
  int gift_title_height;
  int gift_line_height;
  int status_box_offset;
  int status_header_height;
  int status_title_height;
  int status_line_height;
  u8 *treaty_parent;
  int treaty_row_height;
  int treaty_row_height_alt;
  int treaty_title_height;
  iptr treaty_title;
  int treaty_line_height;
  int treaty_line_height_alt;
  int treaty_side_height;
  iptr treaty_side_title;
  u8 *exch_parent_r;
  int exch_title_height_r;
  u8 *exch_parent_l;
  int exch_title_height_l;
  u8 *send_parent;
  u8 *mute_parent;
  u8 *broadcast_parent;
  u8 *mute_anon_parent;
  u8 *anon_parent;
  int chat_font_height;
  u32 selected_mode;
  u8 *mode_radio_parent;
  int mode_title_height;
  int waiting_font_height;
  u8 *review_parent;
  u8 *desc_parent;
  i8 *city_header_font;
  i32 city_hide_button;
  i32 city_reveal_button;
  i8 *city_side_font;
  i32 offer_radio;
  i8 *offer_radio_font;
  i8 *offer_header_font;
  i8 *offer_title_font;
  i8 *civlist_header_font;
  i8 *civlist_side_font;
  i32 map_radio;
  i8 *map_radio_font;
  i8 *map_header_font;
  i8 *map_side_font;
  i32 proposal_radio;
  i8 *proposal_radio_font;
  i8 *proposal_title_font;
  i32 sort_city_button;
  i32 sort_unit_button;
  i32 hide_button;
  i32 reveal_button;
  i8 *unit_header_font;
  i8 *unit_side_font;
  i8 *gold_edit_font;
  i32 gold_edit;
  i8 *gold_prompt_font;
  i8 *gold_header_font;
  i8 *gold_side_font;
  i8 *tech_header_font;
  i8 *tech_side_font;
  i32 gift_radio;
  i8 *gift_radio_font;
  i8 *gift_title_font;
  i8 *status_text_font;
  i8 *status_header_font;
  i32 treaty_radio;
  i8 *treaty_radio_font;
  i8 *treaty_title_font;
  i8 *treaty_side_font;
  i32 exch_radio_r;
  i8 *exch_radio_font_r;
  i8 *exch_title_font_r;
  i32 exch_radio_l;
  i8 *exch_radio_font_l;
  i8 *exch_title_font_l;
  i32 send_checkbox;
  i32 mute_checkbox;
  i8 *right_header_font;
  i8 *left_header_font;
  uptr broadcast_checkbox;
  uptr mute_anon_checkbox;
  uptr anon_checkbox;
  i8 *chat_font;
  i32 mode_radio;
  i8 *mode_radio_font;
  i8 *mode_title_font;
  i8 *waiting_font;
  i8 *review_font;
  uptr review_edit;
  i8 *desc_font;
  uptr desc_edit;
  tagRECT city_btn_rect;
  int city_btn_width;
  int city_btn_top;
  iptr city_header_label;
  int city_btn_height;
  i32 city_list_mode;
  i32 offer_labels;
  i32 offer_label1;
  i32 offer_label2;
  i32 offer_label3;
  i32 offer_label4;
  i32 offer_label5;
  i32 offer_label6;
  iptr civlist_title_idx;
  iptr civlist_titles[4];
  uptr map_title_idx;
  iptr map_labels[4];
  i32 map_label_last;
  i32 proposal_labels;
  i32 proposal_label2;
  tagRECT btn_rect;
  int btn_area_bottom;
  int btn_width;
  int btn_top;
  int btn_height;
  i32 unit_list_mode;
  char gold_text[32];
  i32 tech_list_pick_mode;
  i32 gift_labels;
  i32 gift_label1;
  i32 gift_label2;
  i32 gift_label3;
  i32 gift_label4;
  i32 treaty_labels;
  i32 treaty_label1;
  i32 treaty_label2;
  i32 treaty_label3;
  i32 exch_labels_r;
  i32 exch_label_r1;
  i32 exch_label_r2;
  i32 exch_label_r3;
  i32 exch_label_r4;
  i32 exch_label_r5;
  i32 exch_label_r6;
  i32 exch_labels_l;
  i32 exch_label_l1;
  i32 exch_label_l2;
  i32 exch_label_l3;
  i32 exch_label_l4;
  i32 exch_label_l5;
  i32 exch_label_l6;
  uptr left_col_x;
  uint shown_civ_count;
  int civ;
  u32 right_col_x;
  int has_full_intel;
  int checkbox_indent;
  int max_label_width;
  int label_width;
  iptr label_idx;
  iptr mode_labels[4];
  i32 mode_label_last;
  int waiting_text_width;
  i8 waiting_text[80];
  int *item_kind_ptr;
  iptr *tech_ptr;
  int tech_idx;
  int tech_count;
  int cur_y;
  uptr cur_x;
  int col_width;
  char is_demand_side;
  u32 side_x;
  char is_exchange_side;
  tagRECT ctrl_rect;
  int block_height;
  i32 eh_next;
  i8 *eh_prev;
  i32 eh_state;
  
  eh_state = 0xffffffff;
  if ((side != 0) && (side != 1)) {
    err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_leftright_left_leftright_right_2,(iptr)&str_d_ss_franklinton_parleywin_add_dialog_cp,0xc);
  }
  if (side_kind < 0) {
    err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_thedialog_pdt_null_pdt_null_pdt_count,(iptr)&str_d_ss_franklinton_parleywin_add_dialog_cp_2,0xd);
  }
  is_exchange_side = '\0';
  is_demand_side = '\0';
  flag_ptr = self->pane_selection_flags_area + side * 4 - 0x1c;
  flag_ptr[0] = '\0';
  flag_ptr[1] = '\0';
  flag_ptr[2] = '\0';
  flag_ptr[3] = '\0';
  if (side == 0) {
    side_x = self->panel_rect + panel_margin_x;
  }
  else if (side == 1) {
    tmp = rect_width((iptr)&self->panel_rect);
    side_x = self->panel_rect + tmp / 2 + panel_margin_x;
  }
  if (side_kind == 0xe) {
    is_exchange_side = 1;
    switch(*(i32 *)(self->pane_selection_flags_area + side * 4 + 0xc)) {
    case 0:
      side_kind = 9;
      break;
    case 1:
      side_kind = 8;
      break;
    case 2:
      side_kind = 10;
      break;
    case 3:
      side_kind = 0x11;
      break;
    case 4:
      side_kind = 0xd;
      break;
    case 5:
      side_kind = 0xc;
      break;
    case 6:
      side_kind = 5;
    }
  }
  else if (side_kind == 0x10) {
    is_demand_side = 1;
    switch(self->demand_choice) {
    case 0:
      side_kind = 9;
      break;
    case 1:
      side_kind = 8;
      break;
    case 2:
      side_kind = 10;
      break;
    case 3:
      side_kind = 0x11;
      break;
    case 4:
      side_kind = 0xd;
      break;
    case 5:
      side_kind = 0xc;
      break;
    case 6:
      side_kind = 5;
    }
  }
  parley_clear_side_controls(self,side);
  *(int *)(self->pane_selection_flags_area + side * 4) = side_kind;
  if (((parley_wnd_block.parley_wnd_closed == 0) && (side_kind != 1)) && (side_kind != 0)) {
    if (side_kind == 0x14) {
      control_hide((Control *)self->rates_clamped);
      ctrl_disable((Control *)self->rates_clamped);
      control_hide((Control *)self->mode2_button_value);
      ctrl_disable((Control *)self->mode2_button_value);
      control_hide((Control *)self->never_mind_button_value);
      ctrl_show_and_redraw((Control *)self->tax_scrollbar);
      control_hide((Control *)self->intel_button_value);
      ctrl_show_and_redraw((Control *)self->no_thanks_button_value);
      ctrl_show_and_redraw((Control *)self->counter_button_value);
    }
    else {
      ctrl_show_and_redraw((Control *)self->rates_clamped);
      ctrl_enable((Control *)self->rates_clamped);
      control_hide((Control *)self->mode2_button_value);
      ctrl_disable((Control *)self->mode2_button_value);
      ctrl_show_and_redraw((Control *)self->never_mind_button_value);
      control_hide((Control *)self->tax_scrollbar);
      ctrl_show_and_redraw((Control *)self->intel_button_value);
      control_hide((Control *)self->no_thanks_button_value);
      control_hide((Control *)self->counter_button_value);
    }
  }
  switch(side_kind) {
  case 0:
    break;
  case 1:
    if (((game.wonder_city[0x18] == -1) && (tmp = civ_has_wonder(human_civ[0],9), tmp == 0)
        ) && (game.reveal_map == '\0')) {
      has_full_intel = 0;
    }
    else {
      has_full_intel = 1;
    }
    right_col_x = side_x;
    left_col_x = self->panel_rect + panel_margin_x;
    cur_y = self->panel_top + panel_margin_y;
    cur_x = left_col_x;
    tmp = rect_width((iptr)&self->panel_rect);
    col_width = (tmp + panel_margin_x * -2) / 3;
    if (self->large_layout == 0) {
      chat_font_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
    }
    else {
      chat_font_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
    }
    block_height = panel_margin_y * 2 + chat_font_height;
    if (self->large_layout == 0) {
      chat_font = ((i8 *)&font_size16_bold_block.font_size16_bold);
    }
    else {
      chat_font = ((i8 *)&font_size24_bold);
    }
    ui_set_ctrl_font((iptr)chat_font);
    new_ctrl = operator_new(0x3c);
    eh_state = 3;
    if (new_ctrl == (Control *)0x0) {
      anon_checkbox = 0;
    }
    else {
      anon_checkbox = checkbox_elem_ctor(new_ctrl);
    }
    eh_state = 0xffffffff;
    self->sci_rate_sel = anon_checkbox;
    if (self == (ViewWindow *)0x0) {
      anon_parent = (u8 *)0x0;
    }
    else {
      anon_parent = self->window_2;
    }
    label = label_string(*(i32 *)(label_string_ids + 0xba4));
    checkbox_create_fixed
              ((Control *)self->sci_rate_sel,(iptr)anon_parent,0x415,cur_x,cur_y,col_width,
               label);
    checkbox_set_checked((Control *)self->sci_rate_sel,chat_wnd_block.chat_remain_anonymous);
    checkbox_enable((CheckboxEnableView *)self->sci_rate_sel);
    checkbox_set_callback((CheckboxCallbackSetView *)self->sci_rate_sel,(iptr)chat_on_send_checkbox);
    new_ctrl = operator_new(0x3c);
    eh_state = 4;
    if (new_ctrl == (Control *)0x0) {
      mute_anon_checkbox = 0;
    }
    else {
      mute_anon_checkbox = checkbox_elem_ctor(new_ctrl);
    }
    eh_state = 0xffffffff;
    self->init_tax_rate = mute_anon_checkbox;
    if (self == (ViewWindow *)0x0) {
      mute_anon_parent = (u8 *)0x0;
    }
    else {
      mute_anon_parent = self->window_2;
    }
    label = label_string(*(i32 *)(label_string_ids + 0xd84));
    checkbox_create_fixed
              ((Control *)self->init_tax_rate,(iptr)mute_anon_parent,0x430,col_width + cur_x,cur_y,
               col_width,label);
    checkbox_set_checked((Control *)self->init_tax_rate,chat_wnd_block.chat_mute_anonymous);
    checkbox_enable((CheckboxEnableView *)self->init_tax_rate);
    checkbox_set_callback((CheckboxCallbackSetView *)self->init_tax_rate,(iptr)chat_on_send_checkbox);
    new_ctrl = operator_new(0x3c);
    eh_state = 5;
    if (new_ctrl == (Control *)0x0) {
      broadcast_checkbox = 0;
    }
    else {
      broadcast_checkbox = checkbox_elem_ctor(new_ctrl);
    }
    eh_state = 0xffffffff;
    self->init_lux_rate = broadcast_checkbox;
    if (self == (ViewWindow *)0x0) {
      broadcast_parent = (u8 *)0x0;
    }
    else {
      broadcast_parent = self->window_2;
    }
    label = label_string(*(i32 *)(label_string_ids + 0xba8));
    checkbox_create_fixed
              ((Control *)self->init_lux_rate,(iptr)broadcast_parent,0x416,col_width * 2 + cur_x,
               cur_y,col_width,label);
    checkbox_set_checked((Control *)self->init_lux_rate,chat_wnd_block.chat_broadcast_all);
    checkbox_enable((CheckboxEnableView *)self->init_lux_rate);
    checkbox_set_callback((CheckboxCallbackSetView *)self->init_lux_rate,(iptr)chat_on_send_checkbox);
    cur_y += block_height;
    gfx_set_text_color_index(10);
    if (self->large_layout == 0) {
      left_header_font = ((i8 *)&font_size16_bold_block.font_size16_bold);
    }
    else {
      left_header_font = ((i8 *)&font_size24_bold);
    }
    text_align = 5;
    draw_x = left_col_x;
    tmp = cur_y;
    label = label_string(*(i32 *)(label_string_ids + 0xd2c));
    surface_draw_text((DibSurface *)self,(iptr)left_header_font,label,draw_x,tmp,text_align);
    if (self->large_layout == 0) {
      right_header_font = ((i8 *)&font_size16_bold_block.font_size16_bold);
    }
    else {
      right_header_font = ((i8 *)&font_size24_bold);
    }
    text_align = 5;
    header_x = right_col_x - ((self->large_layout == 0) - 1 & 0x17);
    tmp = cur_y;
    label = label_string(*(i32 *)(label_string_ids + 0xd2c));
    surface_draw_text((DibSurface *)self,(iptr)right_header_font,label,header_x,tmp,text_align);
    cur_x = left_col_x;
    if (self->large_layout == 0) {
      checkbox_indent = 5;
    }
    else {
      checkbox_indent = 0x17;
    }
    cur_y += block_height;
    tmp = rect_width((iptr)&self->panel_rect);
    col_width = (tmp + panel_margin_x * -2) / 2;
    shown_civ_count = 0;
    for (civ = 1; civ < 8; civ++) {
      if (((human_civ[0] == civ) ||
          ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) == 0)) ||
         (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0 ||
          (((has_full_intel == 0 && (civ_saved_cursor_x_block.mp_chat_from_start == 0)) &&
           ((*(byte *)&civs[civ].treaties[human_civ[0]] & 1) == 0)))))) {
        *(i32 *)(((i8 *)&chat_wnd_block.chat_send_to_civs) + civ * 4) = 0;
        *(i32 *)(((i8 *)&chat_wnd_block.chat_muted_civs) + civ * 4) = 0;
      }
      else {
        new_ctrl = operator_new(0x3c);
        eh_state = 6;
        if (new_ctrl == (Control *)0x0) {
          mute_checkbox = 0;
        }
        else {
          mute_checkbox = checkbox_elem_ctor(new_ctrl);
        }
        eh_state = 0xffffffff;
        *(i32 *)(self->parley_checkboxes + civ * 4 + 4) = mute_checkbox;
        if (self == (ViewWindow *)0x0) {
          mute_parent = (u8 *)0x0;
        }
        else {
          mute_parent = self->window_2;
        }
        checkbox_create_fixed
                  (*(Control **)(self->parley_checkboxes + civ * 4 + 4),(iptr)mute_parent,
                   civ + 0x428,cur_x + checkbox_indent,cur_y,0x23,(iptr)&str_empty_167);
        checkbox_set_checked
                  (*(Control **)(self->parley_checkboxes + civ * 4 + 4),
                   *(i32 *)(((i8 *)&chat_wnd_block.chat_muted_civs) + civ * 4));
        checkbox_enable(*(CheckboxEnableView **)(self->parley_checkboxes + civ * 4 + 4));
        checkbox_set_callback(*(CheckboxCallbackSetView **)(self->parley_checkboxes + civ * 4 + 4),(iptr)chat_on_mute_checkbox);
        new_ctrl = operator_new(0x3c);
        eh_state = 7;
        if (new_ctrl == (Control *)0x0) {
          send_checkbox = 0;
        }
        else {
          send_checkbox = checkbox_elem_ctor(new_ctrl);
        }
        eh_state = 0xffffffff;
        *(i32 *)(self->parley_checkboxes + civ * 4 - 0x1c) = send_checkbox;
        if (self == (ViewWindow *)0x0) {
          send_parent = (u8 *)0x0;
        }
        else {
          send_parent = self->window_2;
        }
        label = civ_adjective(civ);
        checkbox_create_fixed
                  (*(Control **)(self->parley_checkboxes + civ * 4 - 0x1c),(iptr)send_parent,
                   civ + 0x416,cur_x + checkbox_indent + 0x23,cur_y,
                   (col_width - 0x23) - checkbox_indent,label);
        checkbox_set_checked
                  (*(Control **)(self->parley_checkboxes + civ * 4 - 0x1c),
                   *(i32 *)(((i8 *)&chat_wnd_block.chat_send_to_civs) + civ * 4));
        checkbox_enable(*(CheckboxEnableView **)(self->parley_checkboxes + civ * 4 - 0x1c));
        checkbox_set_callback
                  (*(CheckboxCallbackSetView **)(self->parley_checkboxes + civ * 4 - 0x1c),(iptr)chat_on_send_checkbox);
        shown_civ_count++;
        if ((shown_civ_count & 1) == 0) {
          cur_x = left_col_x;
        }
        else {
          cur_x = right_col_x;
        }
        if ((shown_civ_count & 1) == 0) {
          if (self->large_layout == 0) {
            checkbox_indent = 5;
          }
          else {
            checkbox_indent = 0x17;
          }
        }
        else if (self->large_layout == 0) {
          checkbox_indent = 5;
        }
        else {
          checkbox_indent = 0;
        }
        if ((shown_civ_count & 1) == 0) {
          cur_y += block_height;
        }
      }
    }
    break;
  case 2:
    mode_labels[0] = label_string(*(i32 *)(label_string_ids + 0xb90));
    mode_labels[1] = label_string(*(i32 *)(label_string_ids + 0xb94));
    mode_labels[2] = label_string(*(i32 *)(label_string_ids + 0xb98));
    mode_labels[3] = label_string(*(i32 *)(label_string_ids + 0xb9c));
    mode_label_last = label_string(*(i32 *)(label_string_ids + 0xba0));
    gfx_set_text_color_index(10);
    if (self->large_layout == 0) {
      label = label_string(*(i32 *)(label_string_ids + 0xb8c));
      max_label_width = font_text_width((GameFont *)((i8 *)&font_size20),label);
    }
    else {
      label = label_string(*(i32 *)(label_string_ids + 0xb8c));
      max_label_width = font_text_width((GameFont *)((i8 *)&font_size30),label);
    }
    title_x = (self->panel_rect + (int)(self->panel_right - self->panel_rect) / 2) - max_label_width / 2;
    tmp = self->panel_top + panel_margin_y;
    if (self->large_layout == 0) {
      mode_title_font = ((i8 *)&font_size20);
    }
    else {
      mode_title_font = ((i8 *)&font_size30);
    }
    text_align = 5;
    cur_y = tmp;
    cur_x = title_x;
    label = label_string(*(i32 *)(label_string_ids + 0xb8c));
    surface_draw_text((DibSurface *)self,(iptr)mode_title_font,label,title_x,tmp,text_align);
    if (self->large_layout == 0) {
      max_label_width = font_text_width((GameFont *)((i8 *)&font_size20),mode_labels[0]);
    }
    else {
      max_label_width = font_text_width((GameFont *)((i8 *)&font_size30),mode_labels[0]);
    }
    for (label_idx = 1; label_idx < 5; label_idx++) {
      if (self->large_layout == 0) {
        label_width = font_text_width
                             ((GameFont *)((i8 *)&font_size20),mode_labels[label_idx]);
      }
      else {
        label_width = font_text_width
                             ((GameFont *)((i8 *)&font_size30),mode_labels[label_idx]);
      }
      if (max_label_width < label_width) {
        max_label_width = label_width;
      }
    }
    side_x = (self->panel_rect + (int)(self->panel_right - self->panel_rect) / 2) - max_label_width / 2;
    self->fill_rect_left = side_x;
    if ((int)cur_x < (int)side_x) {
      side_x = cur_x;
      self->fill_rect_left = cur_x;
    }
    if (self->large_layout == 0) {
      mode_radio_font = ((i8 *)&font_size20);
    }
    else {
      mode_radio_font = ((i8 *)&font_size30);
    }
    ctrl_set_pending_font((iptr)mode_radio_font);
    new_input = operator_new(0x50);
    eh_state = 2;
    if (new_input == (InputControl *)0x0) {
      mode_radio = 0;
    }
    else {
      mode_radio = radiogrp_ctor(new_input);
    }
    eh_state = 0xffffffff;
    *(i32 *)(self->rate_values + side * 4 + 8) = mode_radio;
    cur_x = side_x;
    col_width = max_label_width + max_label_width / 2;
    if (self->large_layout == 0) {
      mode_title_height = font_cached_height((GameFont *)((i8 *)&font_size20));
    }
    else {
      mode_title_height = font_cached_height((GameFont *)((i8 *)&font_size30));
    }
    cur_y = self->panel_top + panel_margin_y * 2 + mode_title_height;
    block_height = self->show_turn_timer - cur_y;
    SetRect(&ctrl_rect,cur_x,cur_y,col_width + cur_x,block_height + cur_y);
    if (self == (ViewWindow *)0x0) {
      mode_radio_parent = (u8 *)0x0;
    }
    else {
      mode_radio_parent = self->window_2;
    }
    radiogrp_create
              (*(RadioGroup **)(self->rate_values + side * 4 + 8),(iptr)mode_radio_parent,0x3f3,
               (iptr)&ctrl_rect,1,5,(iptr)mode_labels);
    if (self->saved_mode_choice == 0xffffffff) {
      selected_mode = 0;
    }
    else {
      selected_mode = self->saved_mode_choice;
    }
    radiogrp_set_selected(*(RadioGroupSetSelView **)(self->rate_values + side * 4 + 8),selected_mode);
    radiogrp_set_dblclick_callback(*(Control **)(self->rate_values + side * 4 + 8),(iptr)parley_on_radio_dblclick)
    ;
    flag_ptr = self->pane_selection_flags_area + side * 4 - 0x1c;
    flag_ptr[0] = 1;
    flag_ptr[1] = '\0';
    flag_ptr[2] = '\0';
    flag_ptr[3] = '\0';
    break;
  case 3:
    exch_labels_l = label_string(*(i32 *)(label_string_ids + 0xbac));
    exch_label_l1 = label_string(*(i32 *)(label_string_ids + 0xbb0));
    exch_label_l2 = label_string(*(i32 *)(label_string_ids + 0xbb4));
    exch_label_l3 = label_string(*(i32 *)(label_string_ids + 3000));
    exch_label_l4 = label_string(*(i32 *)(label_string_ids + 0xbbc));
    exch_label_l5 = label_string(*(i32 *)(label_string_ids + 0xbc0));
    exch_label_l6 = label_string(*(i32 *)(label_string_ids + 0xd08));
    gfx_set_text_color_index(10);
    cur_x = side_x;
    tmp = self->panel_top + panel_margin_y;
    if (self->large_layout == 0) {
      exch_title_font_l = ((i8 *)&font_size16_bold_block.font_size16_bold);
    }
    else {
      exch_title_font_l = ((i8 *)&font_size24_bold);
    }
    text_align = 5;
    text_x = side_x;
    cur_y = tmp;
    label = label_string(*(i32 *)(label_string_ids + 0xc0c));
    surface_draw_text((DibSurface *)self,(iptr)exch_title_font_l,label,text_x,tmp,text_align);
    if (self->large_layout == 0) {
      exch_radio_font_l = ((i8 *)&font_size16_bold_block.font_size16_bold);
    }
    else {
      exch_radio_font_l = ((i8 *)&font_size24_bold);
    }
    ctrl_set_pending_font((iptr)exch_radio_font_l);
    new_input = operator_new(0x50);
    eh_state = 8;
    if (new_input == (InputControl *)0x0) {
      exch_radio_l = 0;
    }
    else {
      exch_radio_l = radiogrp_ctor(new_input);
    }
    eh_state = 0xffffffff;
    *(i32 *)(self->rate_values + side * 4 + 8) = exch_radio_l;
    cur_x = side_x;
    tmp = rect_width((iptr)&self->panel_rect);
    col_width = (tmp + panel_margin_x * -2) / 2;
    if (self->large_layout == 0) {
      exch_title_height_l = font_cached_height((GameFont *)((i8 *)&font_size16));
    }
    else {
      exch_title_height_l = font_cached_height((GameFont *)((i8 *)&font_size24));
    }
    cur_y = self->panel_top + panel_margin_y + exch_title_height_l;
    SetRect(&ctrl_rect,cur_x,cur_y,col_width + cur_x,self->show_turn_timer);
    if (self == (ViewWindow *)0x0) {
      exch_parent_l = (u8 *)0x0;
    }
    else {
      exch_parent_l = self->window_2;
    }
    radiogrp_create
              (*(RadioGroup **)(self->rate_values + side * 4 + 8),(iptr)exch_parent_l,0x3f4,
               (iptr)&ctrl_rect,1,7,(iptr)&exch_labels_l);
    if (self->right_exchange_kind == 0) {
      radiogrp_disable_item(*(RadioGroupDisableView **)(self->rate_values + side * 4 + 8),0);
    }
    else if (self->right_exchange_kind == 6) {
      radiogrp_disable_item(*(RadioGroupDisableView **)(self->rate_values + side * 4 + 8),6);
    }
    radiogrp_set_selected
              (*(RadioGroupSetSelView **)(self->rate_values + side * 4 + 8),self->left_exchange_kind);
    radiogrp_set_dblclick_callback(*(Control **)(self->rate_values + side * 4 + 8),(iptr)parley_on_radio_dblclick)
    ;
    radiogrp_set_select_callback(*(Control **)(self->rate_values + side * 4 + 8),(iptr)parley_on_exchange_kind_select)
    ;
    flag_ptr = self->pane_selection_flags_area + side * 4 - 0x1c;
    flag_ptr[0] = 1;
    flag_ptr[1] = '\0';
    flag_ptr[2] = '\0';
    flag_ptr[3] = '\0';
    break;
  case 4:
    exch_labels_r = label_string(*(i32 *)(label_string_ids + 0xbac));
    exch_label_r1 = label_string(*(i32 *)(label_string_ids + 0xbb0));
    exch_label_r2 = label_string(*(i32 *)(label_string_ids + 0xbb4));
    exch_label_r3 = label_string(*(i32 *)(label_string_ids + 3000));
    exch_label_r4 = label_string(*(i32 *)(label_string_ids + 0xbbc));
    exch_label_r5 = label_string(*(i32 *)(label_string_ids + 0xbc4));
    exch_label_r6 = label_string(*(i32 *)(label_string_ids + 0xd08));
    gfx_set_text_color_index(10);
    cur_x = side_x;
    tmp = self->panel_top + panel_margin_y;
    if (self->large_layout == 0) {
      exch_title_font_r = ((i8 *)&font_size16_bold_block.font_size16_bold);
    }
    else {
      exch_title_font_r = ((i8 *)&font_size24_bold);
    }
    text_align = 5;
    text_x = side_x;
    cur_y = tmp;
    label = label_string(*(i32 *)(label_string_ids + 0xc10));
    surface_draw_text((DibSurface *)self,(iptr)exch_title_font_r,label,text_x,tmp,text_align);
    if (self->large_layout == 0) {
      exch_radio_font_r = ((i8 *)&font_size16_bold_block.font_size16_bold);
    }
    else {
      exch_radio_font_r = ((i8 *)&font_size24_bold);
    }
    ctrl_set_pending_font((iptr)exch_radio_font_r);
    new_input = operator_new(0x50);
    eh_state = 9;
    if (new_input == (InputControl *)0x0) {
      exch_radio_r = 0;
    }
    else {
      exch_radio_r = radiogrp_ctor(new_input);
    }
    eh_state = 0xffffffff;
    *(i32 *)(self->rate_values + side * 4 + 8) = exch_radio_r;
    tmp = rect_width((iptr)&self->panel_rect);
    col_width = (tmp + panel_margin_x * -2) / 2;
    cur_x = side_x;
    if (self->large_layout == 0) {
      exch_title_height_r = font_cached_height((GameFont *)((i8 *)&font_size16));
    }
    else {
      exch_title_height_r = font_cached_height((GameFont *)((i8 *)&font_size24));
    }
    cur_y = self->panel_top + panel_margin_y + exch_title_height_r;
    SetRect(&ctrl_rect,cur_x,cur_y,col_width + cur_x,self->show_turn_timer);
    if (self == (ViewWindow *)0x0) {
      exch_parent_r = (u8 *)0x0;
    }
    else {
      exch_parent_r = self->window_2;
    }
    radiogrp_create
              (*(RadioGroup **)(self->rate_values + side * 4 + 8),(iptr)exch_parent_r,0x3f5,
               (iptr)&ctrl_rect,1,7,(iptr)&exch_labels_r);
    if (self->left_exchange_kind == 0) {
      radiogrp_disable_item(*(RadioGroupDisableView **)(self->rate_values + side * 4 + 8),0);
    }
    else if (self->left_exchange_kind == 6) {
      radiogrp_disable_item(*(RadioGroupDisableView **)(self->rate_values + side * 4 + 8),6);
    }
    radiogrp_set_selected
              (*(RadioGroupSetSelView **)(self->rate_values + side * 4 + 8),self->right_exchange_kind);
    radiogrp_set_dblclick_callback(*(Control **)(self->rate_values + side * 4 + 8),(iptr)parley_on_radio_dblclick)
    ;
    radiogrp_set_select_callback(*(Control **)(self->rate_values + side * 4 + 8),(iptr)parley_on_exchange_kind_select)
    ;
    flag_ptr = self->pane_selection_flags_area + side * 4 - 0x1c;
    flag_ptr[0] = 1;
    flag_ptr[1] = '\0';
    flag_ptr[2] = '\0';
    flag_ptr[3] = '\0';
    break;
  case 5:
    treaty_labels = label_string(*(i32 *)(label_string_ids + 0xbcc));
    treaty_label1 = label_string(*(i32 *)(label_string_ids + 0xbd0));
    treaty_label2 = label_string(*(i32 *)(label_string_ids + 0xbd4));
    treaty_label3 = label_string(*(i32 *)(label_string_ids + 0xbd8));
    gfx_set_text_color_index(10);
    cur_x = side_x;
    cur_y = self->panel_top + panel_margin_y;
    tmp = rect_width((iptr)&self->panel_rect);
    col_width = (tmp + panel_margin_x * -2) / 2 + panel_margin_x * -5;
    if ((is_exchange_side != '\0') || (is_demand_side != '\0')) {
      str_clear((iptr)&map_views_block.text_buffer);
      if (side == 0) {
        treaty_side_title = label_string(*(i32 *)(label_string_ids + 0xc0c));
      }
      else {
        treaty_side_title = label_string(*(i32 *)(label_string_ids + 0xc10));
      }
      text_append_str(treaty_side_title);
      if (self->large_layout == 0) {
        treaty_side_font = ((i8 *)&font_size16_bold_block.font_size16_bold);
      }
      else {
        treaty_side_font = ((i8 *)&font_size24_bold);
      }
      surface_draw_text
                ((DibSurface *)self,(iptr)treaty_side_font,(iptr)&map_views_block.text_buffer,cur_x,cur_y,5);
      if (self->large_layout == 0) {
        treaty_side_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
      }
      else {
        treaty_side_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
      }
      cur_y = cur_y + panel_margin_y + treaty_side_height;
    }
    if ((is_exchange_side == '\0') && (is_demand_side == '\0')) {
      if (self->large_layout == 0) {
        treaty_line_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
      }
      else {
        treaty_line_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
      }
      block_height = treaty_line_height * 5 + panel_margin_y * 4;
    }
    else {
      if (self->large_layout == 0) {
        treaty_line_height_alt = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
      }
      else {
        treaty_line_height_alt = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
      }
      block_height = panel_margin_y * 3 + treaty_line_height_alt * 4;
    }
    cur_y = self->panel_top + (int)((self->show_turn_timer - self->panel_top) - block_height) / 2;
    if (is_demand_side == '\0' && is_exchange_side == '\0') {
      treaty_title = label_string(*(i32 *)(label_string_ids + 0xb90));
    }
    else {
      treaty_title = label_string(*(i32 *)(label_string_ids + 0xd08));
    }
    if (self->large_layout == 0) {
      treaty_title_font = ((i8 *)&font_size16_bold_block.font_size16_bold);
    }
    else {
      treaty_title_font = ((i8 *)&font_size24_bold);
    }
    surface_draw_text((DibSurface *)self,(iptr)treaty_title_font,treaty_title,cur_x,cur_y,5)
    ;
    if (self->large_layout == 0) {
      treaty_radio_font = ((i8 *)&font_size16_bold_block.font_size16_bold);
    }
    else {
      treaty_radio_font = ((i8 *)&font_size24_bold);
    }
    ctrl_set_pending_font((iptr)treaty_radio_font);
    new_input = operator_new(0x50);
    eh_state = 10;
    if (new_input == (InputControl *)0x0) {
      treaty_radio = 0;
    }
    else {
      treaty_radio = radiogrp_ctor(new_input);
    }
    eh_state = 0xffffffff;
    *(i32 *)(self->rate_values + side * 4 + 8) = treaty_radio;
    cur_x = side_x;
    if (self->large_layout == 0) {
      treaty_title_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
    }
    else {
      treaty_title_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
    }
    cur_y = cur_y + panel_margin_y + treaty_title_height;
    if ((is_exchange_side == '\0') && (is_demand_side == '\0')) {
      if (self->large_layout == 0) {
        treaty_row_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
      }
      else {
        treaty_row_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
      }
      block_height = panel_margin_y * 3 + treaty_row_height * 4;
    }
    else {
      if (self->large_layout == 0) {
        treaty_row_height_alt = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
      }
      else {
        treaty_row_height_alt = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
      }
      block_height = treaty_row_height_alt * 3 + panel_margin_y * 2;
    }
    SetRect(&ctrl_rect,cur_x,cur_y,col_width + cur_x,block_height + cur_y);
    if (self == (ViewWindow *)0x0) {
      treaty_parent = (u8 *)0x0;
    }
    else {
      treaty_parent = self->window_2;
    }
    radiogrp_create
              (*(RadioGroup **)(self->rate_values + side * 4 + 8),(iptr)treaty_parent,0x3f6,
               (iptr)&ctrl_rect,1,(is_demand_side == '\0' && is_exchange_side == '\0') + 3,(iptr)&treaty_labels);
    if (((*(byte *)&civs[human_civ[0]].treaties[(self->caption_height)] & 2) != 0) &&
       (radiogrp_disable_item(*(RadioGroupDisableView **)(self->rate_values + side * 4 + 8),0),
       self->treaty_type_choice == 0)) {
      self->treaty_type_choice++;
    }
    if (((*(byte *)&civs[human_civ[0]].treaties[(self->caption_height)] & 4) != 0) &&
       (radiogrp_disable_item(*(RadioGroupDisableView **)(self->rate_values + side * 4 + 8),1),
       self->treaty_type_choice == 1)) {
      self->treaty_type_choice++;
    }
    if (((*(byte *)&civs[human_civ[0]].treaties[(self->caption_height)] & 8) != 0) &&
       (radiogrp_disable_item(*(RadioGroupDisableView **)(self->rate_values + side * 4 + 8),2),
       self->treaty_type_choice == 2)) {
      if (is_demand_side == '\0' && is_exchange_side == '\0') {
        self->treaty_type_choice = 3;
      }
      else {
        self->treaty_type_choice = 0;
      }
    }
    if ((((is_exchange_side == '\0') && (is_demand_side == '\0')) &&
        ((*(byte *)&civs[human_civ[0]].treaties[(self->caption_height)] & 0xe) == 0)) &&
       (radiogrp_disable_item(*(RadioGroupDisableView **)(self->rate_values + side * 4 + 8),3),
       self->treaty_type_choice == 3)) {
      self->treaty_type_choice = 0;
    }
    radiogrp_set_selected
              (*(RadioGroupSetSelView **)(self->rate_values + side * 4 + 8),self->treaty_type_choice);
    radiogrp_set_dblclick_callback(*(Control **)(self->rate_values + side * 4 + 8),(iptr)parley_on_radio_dblclick)
    ;
    radiogrp_set_select_callback(*(Control **)(self->rate_values + side * 4 + 8),(iptr)parley_on_treaty_type_select)
    ;
    flag_ptr = self->pane_selection_flags_area + side * 4 - 0x1c;
    flag_ptr[0] = 1;
    flag_ptr[1] = '\0';
    flag_ptr[2] = '\0';
    flag_ptr[3] = '\0';
    break;
  case 6:
    gfx_set_text_color_index(10);
    cur_x = side_x;
    tmp = rect_width((iptr)&self->panel_rect);
    col_width = (tmp + panel_margin_x * -2) / 2 - panel_margin_x;
    if (self->large_layout == 0) {
      status_line_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
    }
    else {
      status_line_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
    }
    if (self->large_layout == 0) {
      status_title_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
    }
    else {
      status_title_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
    }
    block_height = panel_margin_y * 2 + status_line_height * 4 + status_title_height;
    cur_y = self->panel_top + (int)((self->show_turn_timer - self->panel_top) - block_height) / 2;
    SetRect(&ctrl_rect,cur_x,cur_y,col_width + cur_x,block_height + cur_y);
    gfx_set_draw_target((iptr)&parley_wnd_block.parley_wnd);
    gfx_target_frame_rect((iptr)&ctrl_rect,10);
    rect_deflate((iptr)&ctrl_rect,1,1);
    gfx_target_frame_rect((iptr)&ctrl_rect,10);
    tmp = rect_width((iptr)&ctrl_rect);
    cur_x = ctrl_rect.left + tmp / 2;
    if (self->large_layout == 0) {
      status_header_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
    }
    else {
      status_header_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
    }
    tmp = cur_y + panel_margin_y + status_header_height / 2;
    if (self->large_layout == 0) {
      status_header_font = ((i8 *)&font_size16_bold_block.font_size16_bold);
    }
    else {
      status_header_font = ((i8 *)&font_size24_bold);
    }
    text_align = 0;
    draw_x = cur_x;
    cur_y = tmp;
    label = label_string(*(i32 *)(label_string_ids + 0xbdc));
    surface_draw_text((DibSurface *)self,(iptr)status_header_font,label,draw_x,tmp,text_align);
    ctrl_rect.bottom += panel_margin_y * -2;
    ctrl_rect.left += panel_margin_x * 2;
    ctrl_rect.right += panel_margin_x * -2;
    if (self->large_layout == 0) {
      status_box_offset = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
    }
    else {
      status_box_offset = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
    }
    ctrl_rect.top = ctrl_rect.top + panel_margin_y + status_box_offset;
    gfx_target_frame_rect((iptr)&ctrl_rect,10);
    rect_deflate((iptr)&ctrl_rect,1,1);
    surface_fill_rect((DibSurface *)self,(iptr)&ctrl_rect,list_bg_color);
    tmp = rect_width((iptr)&ctrl_rect);
    cur_x = ctrl_rect.left + tmp / 2;
    tmp = rect_height((iptr)&ctrl_rect);
    cur_y = ctrl_rect.top + tmp / 2;
    text_clear();
    if ((*(byte *)&civs[human_civ[0]].treaties[(self->caption_height)] & 8) == 0) {
      if ((*(byte *)&civs[human_civ[0]].treaties[(self->caption_height)] & 4) == 0) {
        if ((*(byte *)&civs[human_civ[0]].treaties[(self->caption_height)] & 2) == 0) {
          if ((*(byte *)(human_civ[0] * 0x594 + (iptr)((u8 *)&civs + 33) + self->caption_height * 4) & 0x20) == 0) {
            label = label_string(*(i32 *)(label_string_ids + 0xbec));
            text_append(label);
          }
          else {
            label = label_string(*(i32 *)(label_string_ids + 0xbe8));
            text_append(label);
          }
        }
        else {
          label = label_string(*(i32 *)(label_string_ids + 0xbcc));
          text_append(label);
        }
      }
      else {
        label = label_string(*(i32 *)(label_string_ids + 0xbe4));
        text_append(label);
      }
    }
    else {
      label = label_string(*(i32 *)(label_string_ids + 0xbe0));
      text_append(label);
    }
    if (self->large_layout == 0) {
      status_text_font = ((i8 *)&font_size16_bold_block.font_size16_bold);
    }
    else {
      status_text_font = ((i8 *)&font_size24_bold);
    }
    surface_draw_text((DibSurface *)self,(iptr)status_text_font,(iptr)&map_views_block.text_buffer,cur_x,cur_y,0);
    flag_ptr = self->pane_selection_flags_area + side * 4 - 0x1c;
    flag_ptr[0] = 1;
    flag_ptr[1] = '\0';
    flag_ptr[2] = '\0';
    flag_ptr[3] = '\0';
    break;
  case 7:
    gift_labels = label_string(*(i32 *)(label_string_ids + 0xbf4));
    gift_label1 = label_string(*(i32 *)(label_string_ids + 0xbf8));
    gift_label2 = label_string(*(i32 *)(label_string_ids + 0xbfc));
    gift_label3 = label_string(*(i32 *)(label_string_ids + 0xc00));
    gift_label4 = label_string(*(i32 *)(label_string_ids + 0xc04));
    gfx_set_text_color_index(10);
    cur_x = side_x;
    if (self->large_layout == 0) {
      gift_line_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
    }
    else {
      gift_line_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
    }
    if (self->large_layout == 0) {
      gift_title_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
    }
    else {
      gift_title_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
    }
    block_height = panel_margin_y * 5 + gift_line_height * 5 + gift_title_height;
    tmp = self->panel_top + (int)((self->show_turn_timer - self->panel_top) - block_height) / 2;
    if (self->large_layout == 0) {
      gift_title_font = ((i8 *)&font_size16_bold_block.font_size16_bold);
    }
    else {
      gift_title_font = ((i8 *)&font_size24_bold);
    }
    text_align = 5;
    draw_x = cur_x;
    cur_y = tmp;
    label = label_string(*(i32 *)(label_string_ids + 0xbf0));
    surface_draw_text((DibSurface *)self,(iptr)gift_title_font,label,draw_x,tmp,text_align);
    if (self->large_layout == 0) {
      gift_radio_font = ((i8 *)&font_size16_bold_block.font_size16_bold);
    }
    else {
      gift_radio_font = ((i8 *)&font_size24_bold);
    }
    ctrl_set_pending_font((iptr)gift_radio_font);
    new_input = operator_new(0x50);
    eh_state = 0xb;
    if (new_input == (InputControl *)0x0) {
      gift_radio = 0;
    }
    else {
      gift_radio = radiogrp_ctor(new_input);
    }
    eh_state = 0xffffffff;
    *(i32 *)(self->rate_values + side * 4 + 8) = gift_radio;
    cur_x = side_x;
    tmp = rect_width((iptr)&self->panel_rect);
    col_width = (tmp + panel_margin_x * -2) / 2;
    if (self->large_layout == 0) {
      gift_header_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
    }
    else {
      gift_header_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
    }
    cur_y = cur_y + panel_margin_y + gift_header_height;
    if (self->large_layout == 0) {
      gift_row_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
    }
    else {
      gift_row_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
    }
    block_height = gift_row_height * 5 + panel_margin_y * 4;
    SetRect(&ctrl_rect,cur_x,cur_y,col_width + cur_x,block_height + cur_y);
    if (self == (ViewWindow *)0x0) {
      gift_parent = (u8 *)0x0;
    }
    else {
      gift_parent = self->window_2;
    }
    radiogrp_create
              (*(RadioGroup **)(self->rate_values + side * 4 + 8),(iptr)gift_parent,0x3f7,
               (iptr)&ctrl_rect,1,5,(iptr)&gift_labels);
    radiogrp_set_selected
              (*(RadioGroupSetSelView **)(self->rate_values + side * 4 + 8),self->exchange_choice);
    radiogrp_set_dblclick_callback(*(Control **)(self->rate_values + side * 4 + 8),(iptr)parley_on_radio_dblclick)
    ;
    radiogrp_set_select_callback(*(Control **)(self->rate_values + side * 4 + 8),(iptr)parley_on_gift_kind_select)
    ;
    flag_ptr = self->pane_selection_flags_area + side * 4 - 0x1c;
    flag_ptr[0] = 1;
    flag_ptr[1] = '\0';
    flag_ptr[2] = '\0';
    flag_ptr[3] = '\0';
    break;
  case 8:
    if (is_exchange_side == '\0') {
      flag_ptr = ((PictureWindow *)self)->parley_pane_rows_base + side * 4 + 0x38;
      flag_ptr[0] = 7;
      flag_ptr[1] = '\0';
      flag_ptr[2] = '\0';
      flag_ptr[3] = '\0';
    }
    else {
      flag_ptr = ((PictureWindow *)self)->parley_pane_rows_base + side * 4 + 0x38;
      flag_ptr[0] = 6;
      flag_ptr[1] = '\0';
      flag_ptr[2] = '\0';
      flag_ptr[3] = '\0';
    }
    gfx_set_text_color_index(10);
    cur_x = side_x;
    cur_y = self->panel_top + panel_margin_y;
    tmp = rect_width((iptr)&self->panel_rect);
    col_width = (tmp + panel_margin_x * -2) / 2 + panel_margin_x * -5;
    if (is_exchange_side != '\0') {
      str_clear((iptr)&map_views_block.text_buffer);
      if (side == 0) {
        tech_side_title = label_string(*(i32 *)(label_string_ids + 0xc0c));
      }
      else {
        tech_side_title = label_string(*(i32 *)(label_string_ids + 0xc10));
      }
      text_append_str(tech_side_title);
      if (self->large_layout == 0) {
        tech_side_font = ((i8 *)&font_size16_bold_block.font_size16_bold);
      }
      else {
        tech_side_font = ((i8 *)&font_size24_bold);
      }
      surface_draw_text
                ((DibSurface *)self,(iptr)tech_side_font,(iptr)&map_views_block.text_buffer,cur_x,cur_y,5);
      if (self->large_layout == 0) {
        tech_side_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
      }
      else {
        tech_side_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
      }
      cur_y = cur_y + panel_margin_y + tech_side_height;
    }
    SetRect(&ctrl_rect,cur_x,cur_y,col_width + cur_x,self->show_turn_timer);
    gfx_set_draw_target((iptr)&parley_wnd_block.parley_wnd);
    gfx_target_frame_rect((iptr)&ctrl_rect,10);
    rect_deflate((iptr)&ctrl_rect,1,1);
    gfx_target_frame_rect((iptr)&ctrl_rect,10);
    tmp = rect_width((iptr)&ctrl_rect);
    cur_x = ctrl_rect.left + tmp / 2;
    if (self->large_layout == 0) {
      tech_header_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
    }
    else {
      tech_header_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
    }
    tmp = cur_y + tech_header_height / 2;
    if (self->large_layout == 0) {
      tech_header_font = ((i8 *)&font_size16_bold_block.font_size16_bold);
    }
    else {
      tech_header_font = ((i8 *)&font_size24_bold);
    }
    text_align = 0;
    draw_x = cur_x;
    cur_y = tmp;
    label = label_string(*(i32 *)(label_string_ids + 0xc08));
    surface_draw_text((DibSurface *)self,(iptr)tech_header_font,label,draw_x,tmp,text_align);
    if (self->large_layout == 0) {
      tmp = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
      ctrl_rect.top += tmp;
    }
    else {
      tmp = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
      ctrl_rect.top += tmp;
    }
    ctrl_rect.bottom = self->show_turn_timer + panel_margin_y * -2;
    ctrl_rect.left += panel_margin_x * 2;
    ctrl_rect.right += panel_margin_x * -2;
    gfx_target_frame_rect((iptr)&ctrl_rect,10);
    rect_deflate((iptr)&ctrl_rect,1,1);
    surface_fill_rect((DibSurface *)self,(iptr)&ctrl_rect,list_bg_color);
    tech_list_pick_mode = 0;
    if ((is_demand_side != '\0') || ((is_exchange_side != '\0' && (side == 1)))) {
      tech_list_pick_mode = 1;
    }
    parley_create_advance_list_pane((WindowObjectView *)self,(iptr)&ctrl_rect,side,tech_list_pick_mode);
    break;
  case 9:
    gfx_set_text_color_index(10);
    cur_x = side_x;
    tmp = rect_width((iptr)&self->panel_rect);
    col_width = (tmp + panel_margin_x * -2) / 2 + panel_margin_x * -5;
    if (self->large_layout == 0) {
      gold_line_height = font_cached_height((GameFont *)((i8 *)&font_size14));
    }
    else {
      gold_line_height = font_cached_height((GameFont *)((i8 *)&font_size21));
    }
    if (self->large_layout == 0) {
      gold_title_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
    }
    else {
      gold_title_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
    }
    block_height = panel_margin_y * 2 + gold_line_height * 4 + gold_title_height;
    cur_y = self->panel_top + (int)((self->show_turn_timer - self->panel_top) - block_height) / 2;
    if (is_exchange_side != '\0') {
      str_clear((iptr)&map_views_block.text_buffer);
      if (side == 0) {
        gold_side_title = label_string(*(i32 *)(label_string_ids + 0xc0c));
      }
      else {
        gold_side_title = label_string(*(i32 *)(label_string_ids + 0xc10));
      }
      text_append_str(gold_side_title);
      if (self->large_layout == 0) {
        gold_side_font = ((i8 *)&font_size16_bold_block.font_size16_bold);
      }
      else {
        gold_side_font = ((i8 *)&font_size24_bold);
      }
      surface_draw_text
                ((DibSurface *)self,(iptr)gold_side_font,(iptr)&map_views_block.text_buffer,cur_x,
                 self->panel_top + panel_margin_y,5);
    }
    SetRect(&ctrl_rect,cur_x,cur_y,col_width + cur_x,block_height + cur_y);
    gfx_set_draw_target((iptr)&parley_wnd_block.parley_wnd);
    gfx_target_frame_rect((iptr)&ctrl_rect,10);
    rect_deflate((iptr)&ctrl_rect,1,1);
    gfx_target_frame_rect((iptr)&ctrl_rect,10);
    tmp = rect_width((iptr)&ctrl_rect);
    cur_x = ctrl_rect.left + tmp / 2;
    if (self->large_layout == 0) {
      gold_header_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
    }
    else {
      gold_header_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
    }
    cur_y = cur_y + panel_margin_y + gold_header_height / 2;
    str_clear((iptr)&map_views_block.text_buffer);
    if (is_demand_side == '\0') {
      label = label_string(*(i32 *)(label_string_ids + 0xc18));
      text_append_str(label);
      text_append_space();
      text_append_int(civs[human_civ[0]].gold);
      text_append_space();
      label = label_string(*(i32 *)(label_string_ids + 0xc1c));
      text_append_str(label);
    }
    else {
      label = label_string(*(i32 *)(label_string_ids + 0xc14));
      text_append_str(label);
    }
    if (self->large_layout == 0) {
      gold_header_font = ((i8 *)&font_size16_bold_block.font_size16_bold);
    }
    else {
      gold_header_font = ((i8 *)&font_size24_bold);
    }
    surface_draw_text((DibSurface *)self,(iptr)gold_header_font,(iptr)&map_views_block.text_buffer,cur_x,cur_y,0);
    ctrl_rect.bottom += panel_margin_y * -2;
    ctrl_rect.left += panel_margin_x * 2;
    ctrl_rect.right += panel_margin_x * -2;
    if (self->large_layout == 0) {
      gold_box_offset = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
    }
    else {
      gold_box_offset = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
    }
    ctrl_rect.top = ctrl_rect.top + panel_margin_y + gold_box_offset;
    gfx_target_frame_rect((iptr)&ctrl_rect,10);
    rect_deflate((iptr)&ctrl_rect,1,1);
    surface_fill_rect((DibSurface *)self,(iptr)&ctrl_rect,list_bg_color);
    str_clear((iptr)&map_views_block.text_buffer);
    text_append_str((iptr)&str_000000);
    if (self->large_layout == 0) {
      gold_edit_text_width = font_text_width((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold),(iptr)&map_views_block.text_buffer);
    }
    else {
      gold_edit_text_width = font_text_width((GameFont *)((i8 *)&font_size24_bold),(iptr)&map_views_block.text_buffer);
    }
    col_width = (gold_edit_text_width * 3) / 2;
    str_clear((iptr)&map_views_block.text_buffer);
    label = label_string(*(i32 *)(label_string_ids + 0xc20));
    text_append_str(label);
    text_append_space();
    if (self->large_layout == 0) {
      gold_prompt_width = font_text_width((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold),(iptr)&map_views_block.text_buffer);
    }
    else {
      gold_prompt_width = font_text_width((GameFont *)((i8 *)&font_size24_bold),(iptr)&map_views_block.text_buffer);
    }
    tmp = rect_width((iptr)&ctrl_rect);
    cur_x = (ctrl_rect.left + tmp / 2) - (col_width + gold_prompt_width) / 2;
    tmp = rect_height((iptr)&ctrl_rect);
    cur_y = ctrl_rect.top + tmp / 2;
    if (self->large_layout == 0) {
      gold_prompt_font = ((i8 *)&font_size16_bold_block.font_size16_bold);
    }
    else {
      gold_prompt_font = ((i8 *)&font_size24_bold);
    }
    surface_draw_text((DibSurface *)self,(iptr)gold_prompt_font,(iptr)&map_views_block.text_buffer,cur_x,cur_y,1);
    new_input = operator_new(0x48);
    eh_state = 0xc;
    if (new_input == (InputControl *)0x0) {
      gold_edit = 0;
    }
    else {
      gold_edit = edit_ctor(new_input);
    }
    eh_state = 0xffffffff;
    *(i32 *)(self->rate_values + side * 4 + 0x10) = gold_edit;
    if (self->large_layout == 0) {
      gold_edit_font = ((i8 *)&font_size16_bold_block.font_size16_bold);
    }
    else {
      gold_edit_font = ((i8 *)&font_size24_bold);
    }
    ui_set_default_font((iptr)gold_edit_font);
    if (self->large_layout == 0) {
      tmp = font_text_width((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold),(iptr)&map_views_block.text_buffer);
      cur_x += tmp;
    }
    else {
      tmp = font_text_width((GameFont *)((i8 *)&font_size24_bold),(iptr)&map_views_block.text_buffer);
      cur_x += tmp;
    }
    if (self->large_layout == 0) {
      block_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
    }
    else {
      block_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
    }
    cur_y -= block_height / 2;
    SetRect(&ctrl_rect,cur_x,cur_y,col_width + cur_x,block_height + cur_y);
    __itoa(*(int *)(self->parley_caption_buttons + side * 4 - 0x10),gold_text,10);
    if (self == (ViewWindow *)0x0) {
      gold_edit_parent = (u8 *)0x0;
    }
    else {
      gold_edit_parent = self->window_2;
    }
    edit_create
              (*(EditControl **)(self->rate_values + side * 4 + 0x10),(iptr)gold_edit_parent,
               side + 0x3f8,(iptr)&ctrl_rect,(iptr)gold_text);
    edit_set_max_len(*(EditMaxLenView **)(self->rate_values + side * 4 + 0x10),6);
    edit_set_change_callback(*(EditChangeSetView **)(self->rate_values + side * 4 + 0x10),(iptr)parley_gold_edit_on_change);
    ctrl_set_focus(*(ControlFocusView **)(self->rate_values + side * 4 + 0x10));
    break;
  case 10:
    if (is_exchange_side == '\0') {
      flag_ptr = ((PictureWindow *)self)->parley_pane_rows_base + side * 4 + 0x38;
      flag_ptr[0] = 6;
      flag_ptr[1] = '\0';
      flag_ptr[2] = '\0';
      flag_ptr[3] = '\0';
    }
    else {
      flag_ptr = ((PictureWindow *)self)->parley_pane_rows_base + side * 4 + 0x38;
      flag_ptr[0] = 5;
      flag_ptr[1] = '\0';
      flag_ptr[2] = '\0';
      flag_ptr[3] = '\0';
    }
    gfx_set_text_color_index(10);
    cur_x = side_x;
    cur_y = self->panel_top + panel_margin_y;
    tmp = rect_width((iptr)&self->panel_rect);
    col_width = (tmp + panel_margin_x * -2) / 2 + panel_margin_x * -5;
    if (is_exchange_side != '\0') {
      str_clear((iptr)&map_views_block.text_buffer);
      if (side == 0) {
        unit_side_title = label_string(*(i32 *)(label_string_ids + 0xc0c));
      }
      else {
        unit_side_title = label_string(*(i32 *)(label_string_ids + 0xc10));
      }
      text_append_str(unit_side_title);
      if (self->large_layout == 0) {
        unit_side_font = ((i8 *)&font_size16_bold_block.font_size16_bold);
      }
      else {
        unit_side_font = ((i8 *)&font_size24_bold);
      }
      surface_draw_text
                ((DibSurface *)self,(iptr)unit_side_font,(iptr)&map_views_block.text_buffer,cur_x,cur_y,5);
      if (self->large_layout == 0) {
        unit_side_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
      }
      else {
        unit_side_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
      }
      cur_y = cur_y + panel_margin_y + unit_side_height;
    }
    SetRect(&ctrl_rect,cur_x,cur_y,col_width + cur_x,self->show_turn_timer);
    gfx_set_draw_target((iptr)&parley_wnd_block.parley_wnd);
    gfx_target_frame_rect((iptr)&ctrl_rect,10);
    rect_deflate((iptr)&ctrl_rect,1,1);
    gfx_target_frame_rect((iptr)&ctrl_rect,10);
    tmp = rect_width((iptr)&ctrl_rect);
    cur_x = ctrl_rect.left + tmp / 2;
    if (self->large_layout == 0) {
      unit_header_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
    }
    else {
      unit_header_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
    }
    tmp = cur_y + unit_header_height / 2;
    cur_y = tmp;
    if (is_exchange_side == '\0') {
      if (self->large_layout == 0) {
        unit_header_font = ((i8 *)&font_size16_bold_block.font_size16_bold);
      }
      else {
        unit_header_font = ((i8 *)&font_size24_bold);
      }
      text_align = 0;
      draw_x = cur_x;
      label = label_string(*(i32 *)(label_string_ids + 0xc24));
      surface_draw_text((DibSurface *)self,(iptr)unit_header_font,label,draw_x,tmp,text_align);
    }
    if ((is_exchange_side == '\0') && (is_demand_side == '\0')) {
      if (self->large_layout == 0) {
        unit_btn_offset = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
      }
      else {
        unit_btn_offset = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
      }
      btn_top = ctrl_rect.top + unit_btn_offset;
      btn_width = col_width / 2;
      if (self->large_layout == 0) {
        unit_line_spacing = font_line_spacing((GameFont *)((i8 *)&font_size16));
      }
      else {
        unit_line_spacing = font_line_spacing((GameFont *)((i8 *)&font_size24));
      }
      btn_height = panel_padding_y * 2 + unit_line_spacing;
      SetRect(&btn_rect,panel_margin_x * 2 + ctrl_rect.left,btn_top,ctrl_rect.left + btn_width,
              btn_top + btn_height);
    }
    else {
      btn_top = panel_margin_y * 2 + ctrl_rect.top - 1;
      if (self->large_layout == 0) {
        unit_btn_offset_alt = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
      }
      else {
        unit_btn_offset_alt = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
      }
      if (self->large_layout == 0) {
        unit_line_spacing_alt = font_line_spacing((GameFont *)((i8 *)&font_size16));
      }
      else {
        unit_line_spacing_alt = font_line_spacing((GameFont *)((i8 *)&font_size24));
      }
      btn_area_bottom = ctrl_rect.top + panel_padding_y * 2 + unit_btn_offset_alt + unit_line_spacing_alt;
      btn_width = col_width + panel_margin_x * -3;
      btn_height = (btn_area_bottom - btn_top) / 2;
      SetRect(&btn_rect,panel_margin_x * 2 + ctrl_rect.left,btn_top,ctrl_rect.left + btn_width,
              btn_top + btn_height);
      new_ctrl = operator_new(0x3c);
      eh_state = 0xd;
      if (new_ctrl == (Control *)0x0) {
        reveal_button = 0;
      }
      else {
        reveal_button = button_ctor(new_ctrl);
      }
      eh_state = 0xffffffff;
      *(i32 *)((u8 *)&self->advance_pane_rects + side * 4 - 0x24) = reveal_button;
      if (side == 0) {
        reveal_label = label_string(*(i32 *)(label_string_ids + 0xdbc));
      }
      else {
        reveal_label = label_string(*(i32 *)(label_string_ids + 0xdc0));
      }
      if (self == (ViewWindow *)0x0) {
        reveal_parent = (u8 *)0x0;
      }
      else {
        reveal_parent = self->window_2;
      }
      button_create
                (*(Control **)((u8 *)&self->advance_pane_rects + side * 4 - 0x24),(iptr)reveal_parent,
                 side + 0x404,(iptr)&btn_rect,reveal_label);
      button_set_callback
                (*(Control **)((u8 *)&self->advance_pane_rects + side * 4 - 0x24),
                 (iptr)(((void *)(iptr)parley_reveal_city_origin_clicked) + ((side == 0) - 1 & 0xffffef93)));
      new_ctrl = operator_new(0x3c);
      eh_state = 0xe;
      if (new_ctrl == (Control *)0x0) {
        hide_button = 0;
      }
      else {
        hide_button = button_ctor(new_ctrl);
      }
      eh_state = 0xffffffff;
      *(i32 *)((u8 *)&self->advance_pane_rects + side * 4 - 0x1c) = hide_button;
      if (side == 0) {
        hide_label = label_string(*(i32 *)(label_string_ids + 0xdc4));
      }
      else {
        hide_label = label_string(*(i32 *)(label_string_ids + 0xdc0));
      }
      if (self == (ViewWindow *)0x0) {
        hide_parent = (u8 *)0x0;
      }
      else {
        hide_parent = self->window_2;
      }
      button_create
                (*(Control **)((u8 *)&self->advance_pane_rects + side * 4 - 0x1c),(iptr)hide_parent,
                 side + 0x406,(iptr)&btn_rect,hide_label);
      button_set_callback
                (*(Control **)((u8 *)&self->advance_pane_rects + side * 4 - 0x1c),
                 (iptr)(((void *)(iptr)parley_hide_city_origin_clicked) + ((side == 0) - 1 & 0xffffdf58)));
      if ((side == 0) && (self->left_side_accepted != '\0')) {
        control_hide((Control *)self->left_accept_button);
        ctrl_show_and_redraw((Control *)self->left_agreed_button);
      }
      else if (side == 0) {
        ctrl_show_and_redraw((Control *)self->left_accept_button);
        control_hide((Control *)self->left_agreed_button);
      }
      if ((side == 1) && (self->right_side_accepted != '\0')) {
        control_hide((Control *)self->right_accept_button);
        ctrl_show_and_redraw((Control *)self->right_agreed_button);
        ctrl_disable((Control *)self->right_agreed_button);
      }
      else if (side == 1) {
        ctrl_show_and_redraw((Control *)self->right_accept_button);
        control_hide((Control *)self->right_agreed_button);
      }
      btn_top += btn_height;
      btn_width = col_width / 2;
      SetRect(&btn_rect,panel_margin_x * 2 + ctrl_rect.left,btn_top,ctrl_rect.left + btn_width,
              btn_top + btn_height);
    }
    new_ctrl = operator_new(0x3c);
    eh_state = 0xf;
    if (new_ctrl == (Control *)0x0) {
      sort_unit_button = 0;
    }
    else {
      sort_unit_button = button_ctor(new_ctrl);
    }
    eh_state = 0xffffffff;
    *(i32 *)(self->rate_values + side * 4 + 0x28) = sort_unit_button;
    if (self == (ViewWindow *)0x0) {
      sort_unit_parent = (u8 *)0x0;
    }
    else {
      sort_unit_parent = self->window_2;
    }
    label = label_string(*(i32 *)(label_string_ids + 0xc28));
    button_create
              (*(Control **)(self->rate_values + side * 4 + 0x28),(iptr)sort_unit_parent,
               side + 0x400,(iptr)&btn_rect,label);
    button_set_callback
              (*(Control **)(self->rate_values + side * 4 + 0x28),
               (iptr)(((void *)(iptr)parley_sort_by_unit_left_clicked) + ((side == 0) - 1 & 0xfffff637)));
    if ((parley_wnd_block.parley_mode != 9) &&
       (((side == 0 && (self->left_side_accepted == '\0')) ||
        ((side == 1 && (self->right_side_accepted == '\0')))))) {
      ctrl_disable(*(Control **)(self->rate_values + side * 4 + 0x28));
    }
    SetRect(&btn_rect,btn_rect.right,btn_top,btn_rect.right + btn_width + panel_margin_x * -3,
            btn_top + btn_height);
    new_ctrl = operator_new(0x3c);
    eh_state = 0x10;
    if (new_ctrl == (Control *)0x0) {
      sort_city_button = 0;
    }
    else {
      sort_city_button = button_ctor(new_ctrl);
    }
    eh_state = 0xffffffff;
    *(i32 *)(self->rate_values + side * 4 + 0x30) = sort_city_button;
    if (self == (ViewWindow *)0x0) {
      sort_city_parent = (u8 *)0x0;
    }
    else {
      sort_city_parent = self->window_2;
    }
    label = label_string(*(i32 *)(label_string_ids + 0xc2c));
    button_create
              (*(Control **)(self->rate_values + side * 4 + 0x30),(iptr)sort_city_parent,
               side + 0x402,(iptr)&btn_rect,label);
    button_set_callback
              (*(Control **)(self->rate_values + side * 4 + 0x30),
               (iptr)(((void *)(iptr)parley_sort_by_city_left_clicked) + ((side == 0) - 1 & 0xfffff5a1)));
    if ((parley_wnd_block.parley_mode != 9) &&
       (((side == 0 && (self->left_side_accepted == '\0')) ||
        ((side == 1 && (self->right_side_accepted == '\0')))))) {
      ctrl_disable(*(Control **)(self->rate_values + side * 4 + 0x30));
    }
    ctrl_rect.top = btn_rect.bottom;
    ctrl_rect.bottom = self->show_turn_timer + panel_margin_y * -2;
    ctrl_rect.left += panel_margin_x * 2;
    ctrl_rect.right += panel_margin_x * -2;
    gfx_target_frame_rect((iptr)&ctrl_rect,10);
    rect_deflate((iptr)&ctrl_rect,1,1);
    surface_fill_rect((DibSurface *)self,(iptr)&ctrl_rect,list_bg_color);
    unit_list_mode = 1;
    if ((is_demand_side != '\0') || ((is_exchange_side != '\0' && (side == 1)))) {
      unit_list_mode = 0;
    }
    parley_create_unit_list_pane((ListPaneWindow *)self,(iptr)&ctrl_rect,side,unit_list_mode);
    break;
  case 0xb:
    gfx_set_text_color_index(10);
    if (self->large_layout == 0) {
      proposal_line_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
    }
    else {
      proposal_line_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
    }
    block_height = proposal_line_height * 3 + panel_margin_y * 2;
    tmp = self->panel_top + (int)((self->show_turn_timer - self->panel_top) - block_height) / 2;
    cur_x = side_x;
    if (self->large_layout == 0) {
      proposal_title_font = ((i8 *)&font_size16_bold_block.font_size16_bold);
    }
    else {
      proposal_title_font = ((i8 *)&font_size24_bold);
    }
    text_align = 5;
    text_x = side_x;
    cur_y = tmp;
    label = label_string(*(i32 *)(label_string_ids + 0xc30));
    surface_draw_text((DibSurface *)self,(iptr)proposal_title_font,label,text_x,tmp,text_align);
    proposal_labels = label_string(*(i32 *)(label_string_ids + 0xc34));
    proposal_label2 = label_string(*(i32 *)(label_string_ids + 0xc38));
    if (self->large_layout == 0) {
      proposal_radio_font = ((i8 *)&font_size16_bold_block.font_size16_bold);
    }
    else {
      proposal_radio_font = ((i8 *)&font_size24_bold);
    }
    ctrl_set_pending_font((iptr)proposal_radio_font);
    new_input = operator_new(0x50);
    eh_state = 0x11;
    if (new_input == (InputControl *)0x0) {
      proposal_radio = 0;
    }
    else {
      proposal_radio = radiogrp_ctor(new_input);
    }
    eh_state = 0xffffffff;
    *(i32 *)(self->rate_values + side * 4 + 8) = proposal_radio;
    cur_x = side_x;
    tmp = rect_width((iptr)&self->panel_rect);
    col_width = (tmp + panel_margin_x * -2) / 2;
    if (self->large_layout == 0) {
      proposal_title_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
    }
    else {
      proposal_title_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
    }
    cur_y = cur_y + panel_margin_y + proposal_title_height;
    if (self->large_layout == 0) {
      proposal_row_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
    }
    else {
      proposal_row_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
    }
    block_height = proposal_row_height * 2 + panel_margin_y;
    SetRect(&ctrl_rect,cur_x,cur_y,col_width + cur_x,block_height + cur_y);
    if (self == (ViewWindow *)0x0) {
      proposal_parent = (u8 *)0x0;
    }
    else {
      proposal_parent = self->window_2;
    }
    radiogrp_create
              (*(RadioGroup **)(self->rate_values + side * 4 + 8),(iptr)proposal_parent,0x40c,
               (iptr)&ctrl_rect,1,2,(iptr)&proposal_labels);
    radiogrp_set_selected
              (*(RadioGroupSetSelView **)(self->rate_values + side * 4 + 8),self->gift_choice);
    radiogrp_set_dblclick_callback(*(Control **)(self->rate_values + side * 4 + 8),(iptr)parley_on_radio_dblclick)
    ;
    radiogrp_set_select_callback(*(Control **)(self->rate_values + side * 4 + 8),(iptr)parley_on_proposal_kind_select)
    ;
    flag_ptr = self->pane_selection_flags_area + side * 4 - 0x1c;
    flag_ptr[0] = 1;
    flag_ptr[1] = '\0';
    flag_ptr[2] = '\0';
    flag_ptr[3] = '\0';
    break;
  case 0xc:
    civlist_titles[0] = label_string(*(i32 *)(label_string_ids + 0xc50));
    civlist_titles[1] = label_string(*(i32 *)(label_string_ids + 0xc54));
    civlist_titles[2] = label_string(*(i32 *)(label_string_ids + 0xc58));
    civlist_titles[3] = label_string(*(i32 *)(label_string_ids + 0xd0c));
    if (is_exchange_side == '\0') {
      if (is_demand_side == '\0') {
        civlist_title_idx = 0;
      }
      else {
        civlist_title_idx = 3;
      }
    }
    else if (side == 0) {
      civlist_title_idx = 1;
    }
    else {
      civlist_title_idx = 2;
    }
    flag_ptr = ((PictureWindow *)self)->parley_pane_rows_base + side * 4 + 0x38;
    flag_ptr[0] = 5;
    flag_ptr[1] = '\0';
    flag_ptr[2] = '\0';
    flag_ptr[3] = '\0';
    gfx_set_text_color_index(10);
    cur_x = side_x;
    cur_y = self->panel_top + panel_margin_y;
    if (is_exchange_side != '\0') {
      str_clear((iptr)&map_views_block.text_buffer);
      if (side == 0) {
        civlist_side_title = label_string(*(i32 *)(label_string_ids + 0xc0c));
      }
      else {
        civlist_side_title = label_string(*(i32 *)(label_string_ids + 0xc10));
      }
      text_append_str(civlist_side_title);
      if (self->large_layout == 0) {
        civlist_side_font = ((i8 *)&font_size16_bold_block.font_size16_bold);
      }
      else {
        civlist_side_font = ((i8 *)&font_size24_bold);
      }
      surface_draw_text
                ((DibSurface *)self,(iptr)civlist_side_font,(iptr)&map_views_block.text_buffer,cur_x,cur_y,5);
      if (self->large_layout == 0) {
        civlist_side_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
      }
      else {
        civlist_side_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
      }
      cur_y = cur_y + panel_margin_y + civlist_side_height;
    }
    tmp = rect_width((iptr)&self->panel_rect);
    col_width = (tmp + panel_margin_x * -2) / 2 + panel_margin_x * -5;
    if (self->large_layout == 0) {
      civlist_row_height = font_cached_height((GameFont *)((i8 *)&font_size14));
    }
    else {
      civlist_row_height = font_cached_height((GameFont *)((i8 *)&font_size21));
    }
    if (self->large_layout == 0) {
      civlist_title_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
    }
    else {
      civlist_title_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
    }
    block_height = *(int *)(((PictureWindow *)self)->parley_pane_rows_base + side * 4 + 0x38) * civlist_row_height +
               *(int *)(((PictureWindow *)self)->parley_pane_rows_base + side * 4 + 0x38) * panel_margin_y + panel_margin_y * 4 +
               civlist_title_height;
    cur_y += (int)((self->show_turn_timer - cur_y) - block_height) / 2;
    SetRect(&ctrl_rect,cur_x,cur_y,col_width + cur_x,block_height + cur_y);
    gfx_set_draw_target((iptr)&parley_wnd_block.parley_wnd);
    gfx_target_frame_rect((iptr)&ctrl_rect,10);
    rect_deflate((iptr)&ctrl_rect,1,1);
    gfx_target_frame_rect((iptr)&ctrl_rect,10);
    tmp = rect_width((iptr)&ctrl_rect);
    cur_x = ctrl_rect.left + tmp / 2;
    if (self->large_layout == 0) {
      civlist_header_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
    }
    else {
      civlist_header_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
    }
    cur_y = cur_y + panel_margin_y + civlist_header_height / 2;
    if (self->large_layout == 0) {
      civlist_header_font = ((i8 *)&font_size16_bold_block.font_size16_bold);
    }
    else {
      civlist_header_font = ((i8 *)&font_size24_bold);
    }
    surface_draw_text
              ((DibSurface *)self,(iptr)civlist_header_font,civlist_titles[civlist_title_idx],cur_x,cur_y,0);
    if (self->large_layout == 0) {
      civlist_box_offset = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
    }
    else {
      civlist_box_offset = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
    }
    ctrl_rect.top = ctrl_rect.top + panel_margin_y + civlist_box_offset;
    if (self->large_layout == 0) {
      civlist_item_height = font_cached_height((GameFont *)((i8 *)&font_size14));
    }
    else {
      civlist_item_height = font_cached_height((GameFont *)((i8 *)&font_size21));
    }
    ctrl_rect.bottom =
         *(int *)(((PictureWindow *)self)->parley_pane_rows_base + side * 4 + 0x38) * civlist_item_height +
         *(int *)(((PictureWindow *)self)->parley_pane_rows_base + side * 4 + 0x38) * panel_margin_y + ctrl_rect.top + 2;
    ctrl_rect.left += panel_margin_x * 2;
    ctrl_rect.right += panel_margin_x * -2;
    gfx_target_frame_rect((iptr)&ctrl_rect,10);
    rect_deflate((iptr)&ctrl_rect,1,1);
    surface_fill_rect((DibSurface *)self,(iptr)&ctrl_rect,list_bg_color);
    parley_build_civ_list((ListPaneWindow *)self,(iptr)&ctrl_rect,side);
    break;
  case 0xd:
    map_labels[0] = label_string(*(i32 *)(label_string_ids + 0xc3c));
    map_labels[1] = label_string(*(i32 *)(label_string_ids + 0xc40));
    map_title_idx = 0;
    map_labels[2] = label_string(*(i32 *)(label_string_ids + 0xc44));
    map_labels[3] = label_string(*(i32 *)(label_string_ids + 0xc48));
    map_label_last = label_string(*(i32 *)(label_string_ids + 0xc4c));
    gfx_set_text_color_index(10);
    cur_x = side_x;
    cur_y = self->panel_top + panel_margin_y;
    if (is_exchange_side != '\0') {
      map_title_idx = (uptr)(side != 0);
      str_clear((iptr)&map_views_block.text_buffer);
      if (side == 0) {
        map_side_title = label_string(*(i32 *)(label_string_ids + 0xc0c));
      }
      else {
        map_side_title = label_string(*(i32 *)(label_string_ids + 0xc10));
      }
      text_append_str(map_side_title);
      if (self->large_layout == 0) {
        map_side_font = ((i8 *)&font_size16_bold_block.font_size16_bold);
      }
      else {
        map_side_font = ((i8 *)&font_size24_bold);
      }
      surface_draw_text
                ((DibSurface *)self,(iptr)map_side_font,(iptr)&map_views_block.text_buffer,cur_x,cur_y,5);
      if (self->large_layout == 0) {
        map_side_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
      }
      else {
        map_side_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
      }
      cur_y = cur_y + panel_margin_y + map_side_height;
    }
    tmp = rect_width((iptr)&self->panel_rect);
    col_width = (tmp + panel_margin_x * -2) / 2 + panel_margin_x * -5;
    if (self->large_layout == 0) {
      map_row_height = font_cached_height((GameFont *)((i8 *)&font_size14));
    }
    else {
      map_row_height = font_cached_height((GameFont *)((i8 *)&font_size21));
    }
    if (self->large_layout == 0) {
      map_title_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
    }
    else {
      map_title_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
    }
    block_height = map_row_height * 3 + panel_margin_y * 9 + map_title_height;
    cur_y += (int)((self->show_turn_timer - cur_y) - block_height) / 2;
    SetRect(&ctrl_rect,cur_x,cur_y,col_width + cur_x,block_height + cur_y);
    gfx_set_draw_target((iptr)&parley_wnd_block.parley_wnd);
    gfx_target_frame_rect((iptr)&ctrl_rect,10);
    rect_deflate((iptr)&ctrl_rect,1,1);
    gfx_target_frame_rect((iptr)&ctrl_rect,10);
    tmp = rect_width((iptr)&ctrl_rect);
    cur_x = ctrl_rect.left + tmp / 2;
    if (self->large_layout == 0) {
      map_header_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
    }
    else {
      map_header_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
    }
    cur_y = cur_y + panel_margin_y + map_header_height / 2;
    if (self->large_layout == 0) {
      map_header_font = ((i8 *)&font_size16_bold_block.font_size16_bold);
    }
    else {
      map_header_font = ((i8 *)&font_size24_bold);
    }
    surface_draw_text
              ((DibSurface *)self,(iptr)map_header_font,map_labels[map_title_idx],cur_x,cur_y,0);
    if (self->large_layout == 0) {
      map_box_offset = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
    }
    else {
      map_box_offset = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
    }
    ctrl_rect.top = ctrl_rect.top + panel_margin_y + map_box_offset;
    ctrl_rect.bottom += panel_margin_y * -2;
    ctrl_rect.left += panel_margin_x * 2;
    ctrl_rect.right += panel_margin_x * -2;
    gfx_target_frame_rect((iptr)&ctrl_rect,10);
    rect_deflate((iptr)&ctrl_rect,1,1);
    surface_fill_rect((DibSurface *)self,(iptr)&ctrl_rect,list_bg_color);
    if (self->large_layout == 0) {
      map_radio_font = ((i8 *)&font_size16_bold_block.font_size16_bold);
    }
    else {
      map_radio_font = ((i8 *)&font_size24_bold);
    }
    ctrl_set_pending_font((iptr)map_radio_font);
    new_input = operator_new(0x50);
    eh_state = 0x12;
    if (new_input == (InputControl *)0x0) {
      map_radio = 0;
    }
    else {
      map_radio = radiogrp_ctor(new_input);
    }
    eh_state = 0xffffffff;
    *(i32 *)(self->rate_values + side * 4 + 8) = map_radio;
    if (self == (ViewWindow *)0x0) {
      map_parent = (u8 *)0x0;
    }
    else {
      map_parent = self->window_2;
    }
    radiogrp_create
              (*(RadioGroup **)(self->rate_values + side * 4 + 8),(iptr)map_parent,side + 0x424,
               (iptr)&ctrl_rect,1,3,(iptr)(map_labels + 2));
    radiogrp_set_selected
              (*(RadioGroupSetSelView **)(self->rate_values + side * 4 + 8),
               *(i32 *)(self->parley_caption_buttons + side * 4 - 0x18));
    radiogrp_set_dblclick_callback(*(Control **)(self->rate_values + side * 4 + 8),(iptr)parley_on_radio_dblclick)
    ;
    radiogrp_set_select_callback(*(Control **)(self->rate_values + side * 4 + 8),(iptr)parley_on_map_choice_select)
    ;
    flag_ptr = self->pane_selection_flags_area + side * 4 - 0x1c;
    flag_ptr[0] = 1;
    flag_ptr[1] = '\0';
    flag_ptr[2] = '\0';
    flag_ptr[3] = '\0';
    break;
  case 0xf:
    offer_labels = label_string(*(i32 *)(label_string_ids + 0xbac));
    offer_label1 = label_string(*(i32 *)(label_string_ids + 0xbb0));
    offer_label2 = label_string(*(i32 *)(label_string_ids + 0xbb4));
    offer_label3 = label_string(*(i32 *)(label_string_ids + 3000));
    offer_label4 = label_string(*(i32 *)(label_string_ids + 0xbbc));
    offer_label5 = label_string(*(i32 *)(label_string_ids + 0xbc4));
    offer_label6 = label_string(*(i32 *)(label_string_ids + 0xd08));
    gfx_set_text_color_index(10);
    cur_x = side_x;
    if (self->large_layout == 0) {
      offer_line_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
    }
    else {
      offer_line_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
    }
    block_height = panel_margin_y * 7 + offer_line_height * 8;
    tmp = self->panel_top + (int)((self->show_turn_timer - self->panel_top) - block_height) / 2;
    if (self->large_layout == 0) {
      offer_title_font = ((i8 *)&font_size16_bold_block.font_size16_bold);
    }
    else {
      offer_title_font = ((i8 *)&font_size24_bold);
    }
    text_align = 5;
    draw_x = cur_x;
    cur_y = tmp;
    label = label_string(*(i32 *)(label_string_ids + 0xc5c));
    surface_draw_text((DibSurface *)self,(iptr)offer_title_font,label,draw_x,tmp,text_align);
    if (self->large_layout == 0) {
      offer_title_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
    }
    else {
      offer_title_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
    }
    tmp = cur_y + panel_margin_y * 2 + offer_title_height;
    if (self->large_layout == 0) {
      offer_header_font = ((i8 *)&font_size16_bold_block.font_size16_bold);
    }
    else {
      offer_header_font = ((i8 *)&font_size24_bold);
    }
    text_align = 5;
    draw_x = cur_x;
    cur_y = tmp;
    label = label_string(*(i32 *)(label_string_ids + 0xc60));
    surface_draw_text((DibSurface *)self,(iptr)offer_header_font,label,draw_x,tmp,text_align);
    if (self->large_layout == 0) {
      offer_header_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
    }
    else {
      offer_header_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
    }
    cur_y = cur_y + panel_margin_y + offer_header_height;
    if (self->large_layout == 0) {
      offer_radio_font = ((i8 *)&font_size16_bold_block.font_size16_bold);
    }
    else {
      offer_radio_font = ((i8 *)&font_size24_bold);
    }
    ctrl_set_pending_font((iptr)offer_radio_font);
    new_input = operator_new(0x50);
    eh_state = 0x13;
    if (new_input == (InputControl *)0x0) {
      offer_radio = 0;
    }
    else {
      offer_radio = radiogrp_ctor(new_input);
    }
    eh_state = 0xffffffff;
    *(i32 *)(self->rate_values + side * 4 + 8) = offer_radio;
    cur_x = side_x;
    tmp = rect_width((iptr)&self->panel_rect);
    col_width = (tmp + panel_margin_x * -2) / 2;
    if (self->large_layout == 0) {
      offer_row_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
    }
    else {
      offer_row_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
    }
    block_height = panel_margin_y * 5 + offer_row_height * 6;
    SetRect(&ctrl_rect,cur_x,cur_y,col_width + cur_x,block_height + cur_y);
    if (self == (ViewWindow *)0x0) {
      offer_parent = (u8 *)0x0;
    }
    else {
      offer_parent = self->window_2;
    }
    radiogrp_create
              (*(RadioGroup **)(self->rate_values + side * 4 + 8),(iptr)offer_parent,0x41f,
               (iptr)&ctrl_rect,1,7,(iptr)&offer_labels);
    radiogrp_set_selected
              (*(RadioGroupSetSelView **)(self->rate_values + side * 4 + 8),self->demand_choice);
    radiogrp_set_dblclick_callback(*(Control **)(self->rate_values + side * 4 + 8),(iptr)parley_on_radio_dblclick)
    ;
    radiogrp_set_select_callback(*(Control **)(self->rate_values + side * 4 + 8),(iptr)parley_on_demand_kind_select)
    ;
    flag_ptr = self->pane_selection_flags_area + side * 4 - 0x1c;
    flag_ptr[0] = 1;
    flag_ptr[1] = '\0';
    flag_ptr[2] = '\0';
    flag_ptr[3] = '\0';
    break;
  case 0x11:
    if (is_exchange_side == '\0') {
      flag_ptr = ((PictureWindow *)self)->parley_pane_rows_base + side * 4 + 0x38;
      flag_ptr[0] = 7;
      flag_ptr[1] = '\0';
      flag_ptr[2] = '\0';
      flag_ptr[3] = '\0';
    }
    else {
      flag_ptr = ((PictureWindow *)self)->parley_pane_rows_base + side * 4 + 0x38;
      flag_ptr[0] = 6;
      flag_ptr[1] = '\0';
      flag_ptr[2] = '\0';
      flag_ptr[3] = '\0';
    }
    gfx_set_text_color_index(10);
    cur_x = side_x;
    cur_y = self->panel_top + panel_margin_y;
    tmp = rect_width((iptr)&self->panel_rect);
    col_width = (tmp + panel_margin_x * -2) / 2 + panel_margin_x * -5;
    if (is_exchange_side != '\0') {
      str_clear((iptr)&map_views_block.text_buffer);
      if (side == 0) {
        city_side_title = label_string(*(i32 *)(label_string_ids + 0xc0c));
      }
      else {
        city_side_title = label_string(*(i32 *)(label_string_ids + 0xc10));
      }
      text_append_str(city_side_title);
      if (self->large_layout == 0) {
        city_side_font = ((i8 *)&font_size16_bold_block.font_size16_bold);
      }
      else {
        city_side_font = ((i8 *)&font_size24_bold);
      }
      surface_draw_text
                ((DibSurface *)self,(iptr)city_side_font,(iptr)&map_views_block.text_buffer,cur_x,cur_y,5);
      if (self->large_layout == 0) {
        city_side_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
      }
      else {
        city_side_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
      }
      cur_y = cur_y + panel_margin_y + city_side_height;
    }
    SetRect(&ctrl_rect,cur_x,cur_y,col_width + cur_x,self->show_turn_timer);
    gfx_set_draw_target((iptr)&parley_wnd_block.parley_wnd);
    gfx_target_frame_rect((iptr)&ctrl_rect,10);
    rect_deflate((iptr)&ctrl_rect,1,1);
    gfx_target_frame_rect((iptr)&ctrl_rect,10);
    tmp = rect_width((iptr)&ctrl_rect);
    cur_x = ctrl_rect.left + tmp / 2;
    if (self->large_layout == 0) {
      city_header_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
    }
    else {
      city_header_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
    }
    cur_y += city_header_height / 2;
    if ((is_exchange_side == '\0') && (is_demand_side == '\0')) {
      city_header_label = label_string(*(i32 *)(label_string_ids + 0xc68));
      if (self->large_layout == 0) {
        city_header_font = ((i8 *)&font_size16_bold_block.font_size16_bold);
      }
      else {
        city_header_font = ((i8 *)&font_size24_bold);
      }
      surface_draw_text
                ((DibSurface *)self,(iptr)city_header_font,city_header_label,cur_x,cur_y,0);
    }
    else {
      city_btn_top = panel_margin_y * 2 + ctrl_rect.top - 1;
      city_btn_width = col_width + panel_margin_x * -3;
      if (self->large_layout == 0) {
        city_btn_font_height = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
      }
      else {
        city_btn_font_height = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
      }
      city_btn_height = city_btn_font_height - (panel_margin_y * 2 - 1);
      SetRect(&city_btn_rect,panel_margin_x * 2 + ctrl_rect.left,city_btn_top,ctrl_rect.left + city_btn_width,
              city_btn_height + city_btn_top);
      new_ctrl = operator_new(0x3c);
      eh_state = 0x14;
      if (new_ctrl == (Control *)0x0) {
        city_reveal_button = 0;
      }
      else {
        city_reveal_button = button_ctor(new_ctrl);
      }
      eh_state = 0xffffffff;
      *(i32 *)((u8 *)&self->advance_pane_rects + side * 4 - 0x24) = city_reveal_button;
      if (side == 0) {
        city_reveal_label = label_string(*(i32 *)(label_string_ids + 0xdc8));
      }
      else {
        city_reveal_label = label_string(*(i32 *)(label_string_ids + 0xdcc));
      }
      if (self == (ViewWindow *)0x0) {
        city_reveal_parent = (u8 *)0x0;
      }
      else {
        city_reveal_parent = self->window_2;
      }
      button_create
                (*(Control **)((u8 *)&self->advance_pane_rects + side * 4 - 0x24),(iptr)city_reveal_parent,
                 side + 0x408,(iptr)&city_btn_rect,city_reveal_label);
      button_set_callback
                (*(Control **)((u8 *)&self->advance_pane_rects + side * 4 - 0x24),
                 (iptr)(((void *)(iptr)parley_reveal_city_info) + ((side == 0) - 1 & 0xffffdd6e)));
      new_ctrl = operator_new(0x3c);
      eh_state = 0x15;
      if (new_ctrl == (Control *)0x0) {
        city_hide_button = 0;
      }
      else {
        city_hide_button = button_ctor(new_ctrl);
      }
      eh_state = 0xffffffff;
      *(i32 *)((u8 *)&self->advance_pane_rects + side * 4 - 0x1c) = city_hide_button;
      if (side == 0) {
        city_hide_label = label_string(*(i32 *)(label_string_ids + 0xdd0));
      }
      else {
        city_hide_label = label_string(*(i32 *)(label_string_ids + 0xdcc));
      }
      if (self == (ViewWindow *)0x0) {
        city_hide_parent = (u8 *)0x0;
      }
      else {
        city_hide_parent = self->window_2;
      }
      button_create
                (*(Control **)((u8 *)&self->advance_pane_rects + side * 4 - 0x1c),(iptr)city_hide_parent,
                 side + 0x40a,(iptr)&city_btn_rect,city_hide_label);
      button_set_callback
                (*(Control **)((u8 *)&self->advance_pane_rects + side * 4 - 0x1c),
                 (iptr)(((void *)(iptr)parley_hide_city_info) + ((side == 0) - 1 & 0xfffffccc)));
      if ((side == 0) && (self->left_side_confirmed != '\0')) {
        control_hide((Control *)self->left_accept_button);
        ctrl_show_and_redraw((Control *)self->left_agreed_button);
      }
      else if (side == 0) {
        ctrl_show_and_redraw((Control *)self->left_accept_button);
        control_hide((Control *)self->left_agreed_button);
      }
      if ((side == 1) && (self->remote_side_agreed != '\0')) {
        control_hide((Control *)self->right_accept_button);
        ctrl_show_and_redraw((Control *)self->right_agreed_button);
        ctrl_disable((Control *)self->right_agreed_button);
      }
      else if (side == 1) {
        ctrl_show_and_redraw((Control *)self->right_accept_button);
        control_hide((Control *)self->right_agreed_button);
      }
    }
    if (self->large_layout == 0) {
      tmp = font_cached_height((GameFont *)((i8 *)&font_size16_bold_block.font_size16_bold));
      ctrl_rect.top += tmp;
    }
    else {
      tmp = font_cached_height((GameFont *)((i8 *)&font_size24_bold));
      ctrl_rect.top += tmp;
    }
    ctrl_rect.bottom = self->show_turn_timer + panel_margin_y * -2;
    ctrl_rect.left += panel_margin_x * 2;
    ctrl_rect.right += panel_margin_x * -2;
    gfx_target_frame_rect((iptr)&ctrl_rect,10);
    rect_deflate((iptr)&ctrl_rect,1,1);
    surface_fill_rect((DibSurface *)self,(iptr)&ctrl_rect,list_bg_color);
    city_list_mode = 1;
    if ((is_demand_side != '\0') || ((is_exchange_side != '\0' && (side == 1)))) {
      city_list_mode = 0;
    }
    parley_create_city_list_pane((ListPaneWindow *)self,(iptr)&ctrl_rect,side,city_list_mode);
    break;
  case 0x12:
    label = civ_get_adjective(self->caption_height);
    text_set_string_arg_b(0,label);
    text_clear();
    text_append_label(0x2e2);
    text_expand_vars((iptr)&map_views_block.text_buffer,(iptr)waiting_text);
    gfx_set_text_color_index(10);
    if (self->large_layout == 0) {
      waiting_text_width = font_text_width((GameFont *)((i8 *)&font_size20),(iptr)waiting_text);
    }
    else {
      waiting_text_width = font_text_width((GameFont *)((i8 *)&font_size30),(iptr)waiting_text);
    }
    cur_x = (self->panel_rect + (int)(self->panel_right - self->panel_rect) / 2) - waiting_text_width / 2;
    if (self->large_layout == 0) {
      waiting_font_height = font_cached_height((GameFont *)((i8 *)&font_size20));
    }
    else {
      waiting_font_height = font_cached_height((GameFont *)((i8 *)&font_size30));
    }
    cur_y = (self->panel_top + (int)(self->show_turn_timer - self->panel_top) / 2 + panel_margin_y) -
               waiting_font_height / 2;
    if (self->large_layout == 0) {
      waiting_font = ((i8 *)&font_size20);
    }
    else {
      waiting_font = ((i8 *)&font_size30);
    }
    surface_draw_text
              ((DibSurface *)self,(iptr)waiting_font,(iptr)waiting_text,cur_x,cur_y,5);
    control_hide((Control *)self->mode2_button_value);
    ctrl_disable((Control *)self->mode2_button_value);
    ctrl_show_and_redraw((Control *)self->rates_clamped);
    ctrl_disable((Control *)self->rates_clamped);
    ctrl_disable((Control *)self->never_mind_button_value);
    if ((self->left_side_accepted == '\0') && (self->left_side_confirmed == '\0')) {
      control_hide((Control *)self->conceal_button_value);
      ctrl_disable((Control *)self->conceal_button_value);
      ctrl_show_and_redraw((Control *)self->reveal_button_value);
      ctrl_enable((Control *)self->reveal_button_value);
    }
    else {
      ctrl_show_and_redraw((Control *)self->conceal_button_value);
      ctrl_enable((Control *)self->conceal_button_value);
      control_hide((Control *)self->reveal_button_value);
      ctrl_disable((Control *)self->reveal_button_value);
    }
    break;
  case 0x13:
    parley_build_description((WindowObjectView *)self,self->item_buffer,0);
    new_input = operator_new(0x48);
    eh_state = 0;
    if (new_input == (InputControl *)0x0) {
      desc_edit = 0;
    }
    else {
      desc_edit = edit_ctor(new_input);
    }
    eh_state = 0xffffffff;
    self->side_text_edit = desc_edit;
    cur_x = self->panel_rect + panel_margin_x;
    col_width = rect_width((iptr)&self->panel_rect);
    col_width += panel_margin_x * -2;
    cur_y = self->panel_top + panel_margin_y;
    block_height = self->show_turn_timer - cur_y;
    SetRect(&ctrl_rect,cur_x,cur_y,col_width + cur_x,block_height + cur_y);
    if (self->large_layout == 0) {
      desc_font = ((i8 *)&font_size14);
    }
    else {
      desc_font = ((i8 *)&font_size21);
    }
    ui_set_default_font((iptr)desc_font);
    if (self == (ViewWindow *)0x0) {
      desc_parent = (u8 *)0x0;
    }
    else {
      desc_parent = self->window_2;
    }
    edit_create_styled
              ((EditControl *)self->side_text_edit,(iptr)desc_parent,0x426,(iptr)&ctrl_rect,(iptr)&text_section_index_pool_block.parley_description,0x122
               ,0);
    edit_set_max_len((EditMaxLenView *)self->side_text_edit,0x2000);
    edit_set_callback((EditCallbackSetView *)self->side_text_edit,(iptr)parley_edit_escape_filter);
    ctrl_show_and_redraw((Control *)self->side_text_edit);
    break;
  case 0x14:
    window_show((WindowObjectView *)((i8 *)&parley_wnd_block.parley_wnd));
    parley_build_description((WindowObjectView *)self,self->item_buffer,1);
    new_input = operator_new(0x48);
    eh_state = 1;
    if (new_input == (InputControl *)0x0) {
      review_edit = 0;
    }
    else {
      review_edit = edit_ctor(new_input);
    }
    eh_state = 0xffffffff;
    self->side_text_edit = review_edit;
    cur_x = self->panel_rect + panel_margin_x;
    col_width = rect_width((iptr)&self->panel_rect);
    col_width += panel_margin_x * -2;
    cur_y = self->panel_top + panel_margin_y;
    block_height = self->show_turn_timer - cur_y;
    SetRect(&ctrl_rect,cur_x,cur_y,col_width + cur_x,block_height + cur_y);
    if (self->large_layout == 0) {
      review_font = ((i8 *)&font_size14);
    }
    else {
      review_font = ((i8 *)&font_size21);
    }
    ui_set_default_font((iptr)review_font);
    if (self == (ViewWindow *)0x0) {
      review_parent = (u8 *)0x0;
    }
    else {
      review_parent = self->window_2;
    }
    edit_create_styled
              ((EditControl *)self->side_text_edit,(iptr)review_parent,0x426,(iptr)&ctrl_rect,(iptr)&text_section_index_pool_block.parley_description,0x122
               ,0);
    edit_set_max_len((EditMaxLenView *)self->side_text_edit,0x2000);
    edit_set_callback((EditCallbackSetView *)self->side_text_edit,(iptr)parley_edit_escape_filter);
    ctrl_show_and_redraw((Control *)self->side_text_edit);
    parley_wnd_block.parley_offer_acceptable_i32 = 1;
    if (self->item_buffer != 0) {
      item_buf = self->item_buffer;
      item_kind_ptr = (int *)(item_buf + 0x20);
      if (((*(int *)(self->item_buffer + 0x10) == 0xf) && (*item_kind_ptr == 8)) ||
         ((*(int *)(self->item_buffer + 0x10) == 0xe && (*item_kind_ptr == 8)))) {
        tech_count = *(int *)(item_buf + 0x28);
        tech_ptr = (iptr *)(item_buf + 0x2c);
        for (tech_idx = 0; tech_idx < tech_count; tech_idx++) {
          label = *tech_ptr;
          tech_ptr++;
          tmp = civ_has_advance(human_civ[0],label);
          if (tmp == 0) {
            self->techs_all_known = 0;
          }
        }
      }
    }
    if (self->techs_all_known == 0) {
      ctrl_disable((Control *)self->tax_scrollbar);
    }
    else {
      ctrl_enable((Control *)self->tax_scrollbar);
    }
  }
  parley_update_buttons(self);
  wnd_blit_surface_rect((DibSurface *)self,(iptr)&self->fill_rect_left);
  return;
}

/* 0052d4d2 auto */
void __cdecl parley_on_treaty_type_select(i32 ctrl_id,i32 treaty_type)

{
  iptr active_child;
  iptr parley;
  
  active_child = wnd_get_active_child();
  if (active_child == 0) {
    parley = 0;
  }
  else {
    parley = active_child - 0x48;
  }
  wnd_activate((Wnd *)(parley + 0x48));
  *(i32 *)(parley + 0x218) = treaty_type;
  return;
}

/* 0052d523 auto */
void __cdecl parley_on_demand_kind_select(i32 ctrl_id,u32 demand_kind)

{
  iptr active_child;
  ViewWindow *this2;
  
  active_child = wnd_get_active_child();
  if (active_child == 0) {
    this2 = (ViewWindow *)0x0;
  }
  else {
    this2 = (ViewWindow *)(active_child - 0x48);
  }
  wnd_activate((Wnd *)this2->window_2);
  this2->demand_choice = demand_kind;
  parley_add_side_dialog(this2,this2->right_civ,1);
  return;
}

/* 0052d588 auto */
void __cdecl parley_on_map_choice_select(int side,i32 map_choice)

{
  int active_child;
  iptr parley;
  
  active_child = wnd_get_active_child();
  if (active_child == 0) {
    parley = 0;
  }
  else {
    parley = active_child - 0x48;
  }
  wnd_activate((Wnd *)(parley + 0x48));
  *(i32 *)(parley - 0xe6c + side * 4) = map_choice;
  return;
}

/* 0052d5dd auto */
void __cdecl parley_on_gift_kind_select(i32 ctrl_id,u32 gift_kind)

{
  iptr active_child;
  ViewWindow *this2;
  
  active_child = wnd_get_active_child();
  if (active_child == 0) {
    this2 = (ViewWindow *)0x0;
  }
  else {
    this2 = (ViewWindow *)(active_child - 0x48);
  }
  wnd_activate((Wnd *)this2->window_2);
  this2->exchange_choice = gift_kind;
  switch(gift_kind) {
  case 0:
    this2->session_mode = 7;
    break;
  case 1:
    this2->session_mode = 8;
    break;
  case 2:
    this2->session_mode = 9;
    break;
  case 3:
    this2->session_mode = 10;
    break;
  case 4:
    this2->session_mode = 0xb;
  }
  this2->caption_button_count = (((i32 *)&parley_mode_right_kinds))[this2->session_mode * 2];
  this2->right_civ = this2->caption_button_count;
  parley_add_side_dialog(this2,this2->right_civ,1);
  return;
}

/* 0052d6ff auto */
void __cdecl parley_on_proposal_kind_select(i32 ctrl_id,u32 proposal_kind)

{
  iptr active_child;
  ViewWindow *this2;
  
  active_child = wnd_get_active_child();
  if (active_child == 0) {
    this2 = (ViewWindow *)0x0;
  }
  else {
    this2 = (ViewWindow *)(active_child - 0x48);
  }
  wnd_activate((Wnd *)this2->window_2);
  this2->gift_choice = proposal_kind;
  if (proposal_kind == 0) {
    this2->session_mode = 0xc;
  }
  else if (proposal_kind == 1) {
    this2->session_mode = 0xd;
  }
  this2->caption_button_count = (((i32 *)&parley_mode_right_kinds))[this2->session_mode * 2];
  this2->right_civ = this2->caption_button_count;
  parley_add_side_dialog(this2,this2->right_civ,1);
  return;
}

/* 0052d7dc auto */
void __cdecl parley_on_exchange_kind_select(int ctrl_id,i32 exchange_kind)

{
  iptr active_child;
  int selected;
  iptr parley;
  uint is_right_side;
  
  active_child = wnd_get_active_child();
  if (active_child == 0) {
    parley = 0;
  }
  else {
    parley = active_child - 0x48;
  }
  wnd_activate((Wnd *)(parley + 0x48));
  is_right_side = (uint)(ctrl_id == 0x3f4);
  switch(exchange_kind) {
  case 0:
    selected = radiogrp_get_selected(*(RadioGroupGetSelView **)(parley + 0x36c + is_right_side * 4));
    radiogrp_disable_item(*(RadioGroupDisableView **)(parley + 0x36c + is_right_side * 4),0);
    radiogrp_enable_item(*(RadioGroupEnableView **)(parley + 0x370),6);
    radiogrp_enable_item(*(RadioGroupEnableView **)(parley + 0x36c),6);
    if (selected == 0) {
      radiogrp_set_selected(*(RadioGroupSetSelView **)(parley + 0x36c + is_right_side * 4),1);
    }
    break;
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
    radiogrp_enable_item(*(RadioGroupEnableView **)(parley + 0x36c),0);
    radiogrp_enable_item(*(RadioGroupEnableView **)(parley + 0x370),0);
    radiogrp_enable_item(*(RadioGroupEnableView **)(parley + 0x370),6);
    radiogrp_enable_item(*(RadioGroupEnableView **)(parley + 0x36c),6);
    break;
  case 6:
    selected = radiogrp_get_selected(*(RadioGroupGetSelView **)(parley + 0x36c + is_right_side * 4));
    radiogrp_enable_item(*(RadioGroupEnableView **)(parley + 0x36c),0);
    radiogrp_enable_item(*(RadioGroupEnableView **)(parley + 0x370),0);
    radiogrp_disable_item(*(RadioGroupDisableView **)(parley + 0x36c + is_right_side * 4),6);
    if (selected == 6) {
      radiogrp_set_selected(*(RadioGroupSetSelView **)(parley + 0x36c + is_right_side * 4),0);
    }
  }
  return;
}

/* 0052d9a1 auto */
void __cdecl parley_on_radio_dblclick(i32 ctrl_id)

{
  iptr active_child;
  int enabled;
  iptr parley;
  
  active_child = wnd_get_active_child();
  if (active_child == 0) {
    parley = 0;
  }
  else {
    parley = active_child - 0x48;
  }
  enabled = ctrl_is_enabled(*(ControlEnabledView **)(parley + 0x348));
  if ((enabled != 0) ||
     (enabled = ctrl_is_enabled(*(ControlEnabledView **)(parley + 0x34c)), enabled != 0)) {
    wnd_activate((Wnd *)(parley + 0x48));
    parley_on_mode_chosen(ctrl_id);
  }
  return;
}

/* 0052da23 auto */
void __cdecl parley_on_conceal_info(void)

{
  iptr active_child;
  iptr parley;
  
  active_child = wnd_get_active_child();
  if (active_child == 0) {
    parley = 0;
  }
  else {
    parley = active_child - 0x48;
  }
  *(i8 *)(parley + 0x3bd) = 0;
  *(i8 *)(parley + 0x3be) = 0;
  net_send_message(0xa6,*(i32 *)
                           (((i8 *)&net_session_block.net_player_slots) +
                           *(int *)(((i8 *)&net_session_block.net_civ_slots) + *(int *)(parley + 0x118) * 4) * 0x54),
                     human_civ[0],(int)*(char *)(parley + 0x3be),0,0,0,0,0,0);
  net_send_message(0xa8,*(i32 *)
                           (((i8 *)&net_session_block.net_player_slots) +
                           *(int *)(((i8 *)&net_session_block.net_civ_slots) + *(int *)(parley + 0x118) * 4) * 0x54),
                     human_civ[0],(int)*(char *)(parley + 0x3bd),0,0,0,0,0,0);
  control_hide(*(Control **)(parley + 0x340));
  ctrl_disable(*(Control **)(parley + 0x340));
  ctrl_show_and_redraw(*(Control **)(parley + 0x344));
  ctrl_enable(*(Control **)(parley + 0x344));
  return;
}

/* 0052db3d auto */
void __cdecl parley_on_reveal_info(void)

{
  iptr active_child;
  iptr parley;
  
  wnd_get_active_child();
  active_child = wnd_get_active_child();
  if (active_child == 0) {
    parley = 0;
  }
  else {
    parley = active_child - 0x48;
  }
  *(i8 *)(parley + 0x3bd) = 1;
  *(i8 *)(parley + 0x3be) = 1;
  net_send_message(0xa5,*(i32 *)
                           (((i8 *)&net_session_block.net_player_slots) +
                           *(int *)(((i8 *)&net_session_block.net_civ_slots) + *(int *)(parley + 0x118) * 4) * 0x54),
                     human_civ[0],(int)*(char *)(parley + 0x3be),0,0,0,0,0,0);
  net_send_message(0xa7,*(i32 *)
                           (((i8 *)&net_session_block.net_player_slots) +
                           *(int *)(((i8 *)&net_session_block.net_civ_slots) + *(int *)(parley + 0x118) * 4) * 0x54),
                     human_civ[0],(int)*(char *)(parley + 0x3bd),0,0,0,0,0,0);
  ctrl_show_and_redraw(*(Control **)(parley + 0x340));
  ctrl_enable(*(Control **)(parley + 0x340));
  control_hide(*(Control **)(parley + 0x344));
  ctrl_disable(*(Control **)(parley + 0x344));
  return;
}

/* 0052dc7e auto */
void __cdecl parley_on_check_intel(void)

{
  bool has_intel_wonder;
  iptr active_child;
  int has_wonder;
  iptr parley;
  
  active_child = wnd_get_active_child();
  if (active_child == 0) {
    parley = 0;
  }
  else {
    parley = active_child - 0x48;
  }
  has_wonder = civ_has_wonder(human_civ[0],0x18);
  if (has_wonder == 0) {
    has_wonder = civ_has_wonder(human_civ[0],9);
    if (has_wonder == 0) {
      has_intel_wonder = false;
      goto check_intel_access;
    }
  }
  has_intel_wonder = true;
check_intel_access:
  if ((((*(byte *)&civs[human_civ[0]].treaties[(*(int *)(parley + 0x118))] & 0x80) != 0)
      || (has_intel_wonder)) || (game.reveal_map != '\0')) {
    intel_report_show(human_civ[0],*(iptr *)(parley + 0x118));
  }
  else {
    popup_game_with_sprite((iptr)&str_nointel_2,(iptr)&popup_info_icon_sprite,0);
  }
  return;
}

/* 0052dd73 auto */
void __cdecl parley_on_mode_chosen(i32 ctrl_id)

{
  iptr active_child;
  i32 value;
  ParleyOfferBuffer *this2;
  
  active_child = wnd_get_active_child();
  if (active_child == 0) {
    this2 = (ParleyOfferBuffer *)0x0;
  }
  else {
    this2 = (ParleyOfferBuffer *)(active_child - 0x48);
  }
  wnd_activate((Wnd *)(this2->inner_wnd));
  switch(this2->parley_kind) {
  case 3:
    value = radiogrp_get_selected(*(RadioGroupGetSelView **)(this2->action_radio_group));
    *(i32 *)this2->selected_action = value;
    if (*(int *)this2->selected_action == 0) {
      this2->parley_kind = 6;
      ctrl_enable(*(Control **)(this2->never_mind_button_2));
    }
    else if (*(int *)this2->selected_action == 1) {
      this2->parley_kind = 0xc;
      if (*(int *)this2->proposal_kind != 0) {
        this2->parley_kind = 0xd;
      }
      ctrl_enable(*(Control **)(this2->never_mind_button_2));
    }
    else if (*(int *)this2->selected_action == 2) {
      if (*(int *)(this2->gift_kind) == 0) {
        this2->parley_kind = 7;
      }
      else if (*(int *)(this2->gift_kind) == 1) {
        this2->parley_kind = 8;
      }
      else if (*(int *)(this2->gift_kind) == 2) {
        this2->parley_kind = 9;
      }
      else if (*(int *)(this2->gift_kind) == 3) {
        this2->parley_kind = 10;
      }
      else {
        this2->parley_kind = 0xb;
      }
      ctrl_enable(*(Control **)(this2->never_mind_button_2));
    }
    else if (*(int *)this2->selected_action == 3) {
      this2->parley_kind = 5;
      ctrl_enable(*(Control **)(this2->never_mind_button_2));
    }
    else if (*(int *)this2->selected_action == 4) {
      this2->parley_kind = 0xf;
      ctrl_enable(*(Control **)(this2->never_mind_button_2));
    }
    *(i32 *)(this2->shown_left_kind) = (((i32 *)&parley_mode_left_kinds))[this2->parley_kind * 2];
    *(i32 *)this2->left_kind = *(i32 *)(this2->shown_left_kind);
    *(i32 *)(this2->shown_right_kind) = (((i32 *)&parley_mode_right_kinds))[this2->parley_kind * 2];
    *(i32 *)(this2->right_kind) = *(i32 *)(this2->shown_right_kind);
    parley_add_side_dialog((ViewWindow *)this2,*(i32 *)this2->left_kind,0);
    parley_add_side_dialog
              ((ViewWindow *)this2,*(i32 *)(this2->right_kind),1);
    break;
  case 5:
    value = radiogrp_get_selected(*(RadioGroupGetSelView **)(this2->barter_give_radio_group));
    *(i32 *)(this2->barter_give_kind) = value;
    value = radiogrp_get_selected(*(RadioGroupGetSelView **)(this2->action_radio_group));
    *(i32 *)(this2->barter_want_kind) = value;
    this2->parley_kind = 0xe;
    *(i32 *)(this2->shown_left_kind) = (((i32 *)&parley_mode_left_kinds))[this2->parley_kind * 2];
    *(i32 *)this2->left_kind = *(i32 *)(this2->shown_left_kind);
    *(i32 *)(this2->shown_right_kind) = (((i32 *)&parley_mode_right_kinds))[this2->parley_kind * 2];
    *(i32 *)(this2->right_kind) = *(i32 *)(this2->shown_right_kind);
    parley_add_side_dialog((ViewWindow *)this2,*(i32 *)this2->left_kind,0);
    parley_add_side_dialog
              ((ViewWindow *)this2,*(i32 *)(this2->right_kind),1);
    break;
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
  case 0xf:
    if (*(int *)(this2->received_offer) != 0) {
      operator_delete(*(void **)(this2->received_offer));
      this2->proposal_kind[0x18] = '\0';
      this2->proposal_kind[0x19] = '\0';
      this2->proposal_kind[0x1a] = '\0';
      this2->proposal_kind[0x1b] = '\0';
    }
    value = parley_send_offer(this2,this2->parley_kind);
    *(i32 *)(this2->received_offer) = value;
    if ((this2->parley_kind == 6) && (this2->treaty_choice == 3)) {
      if ((*(byte *)&civs[human_civ[0]].treaties[(this2->civ_id)] & 8) == 0) {
        if ((*(byte *)&civs[human_civ[0]].treaties[(this2->civ_id)] & 4) == 0) {
          if ((*(byte *)&civs[human_civ[0]].treaties[(this2->civ_id)] & 2) != 0) {
            diplo_clear_treaty_flags(human_civ[0],this2->civ_id,2);
          }
        }
        else {
          diplo_clear_treaty_flags(human_civ[0],this2->civ_id,4);
        }
      }
      else {
        diplo_clear_treaty_flags(human_civ[0],this2->civ_id,8);
      }
      parley_add_side_dialog
                ((ViewWindow *)this2,*(i32 *)this2->left_kind,0);
      parley_add_side_dialog
                ((ViewWindow *)this2,*(i32 *)(this2->right_kind),1);
    }
    else if (*(int *)(this2->received_offer) != 0) {
      this2->parley_kind = 1;
      *(i32 *)(this2->shown_left_kind) = (((i32 *)&parley_mode_left_kinds))[this2->parley_kind * 2];
      *(i32 *)this2->left_kind = *(i32 *)(this2->shown_left_kind);
      *(i32 *)(this2->shown_right_kind) = (((i32 *)&parley_mode_right_kinds))[this2->parley_kind * 2];
      *(i32 *)(this2->right_kind) = *(i32 *)(this2->shown_right_kind);
      parley_add_side_dialog
                ((ViewWindow *)this2,*(i32 *)this2->left_kind,0);
      parley_add_side_dialog
                ((ViewWindow *)this2,*(i32 *)(this2->right_kind),1);
      ctrl_disable(*(Control **)(this2->never_mind_button_2));
    }
  }
  return;
}

/* 0052e326 auto */
void __cdecl parley_on_never_mind(void)

{
  iptr active_child;
  ViewWindow *this2;
  
  active_child = wnd_get_active_child();
  if (active_child == 0) {
    this2 = (ViewWindow *)0x0;
  }
  else {
    this2 = (ViewWindow *)(active_child - 0x48);
  }
  wnd_activate((Wnd *)this2->window_2);
  switch(this2->session_mode) {
  case 3:
    break;
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xf:
    this2->session_mode = 3;
    ctrl_disable((Control *)this2->never_mind_button_value);
    this2->shown_left_civ = parley_mode3_left_kind;
    this2->left_civ = this2->shown_left_civ;
    this2->caption_button_count = parley_mode3_right_kind;
    this2->right_civ = this2->caption_button_count;
    parley_add_side_dialog(this2,this2->left_civ,0);
    parley_add_side_dialog(this2,this2->right_civ,1);
    break;
  case 0xe:
    this2->session_mode = 5;
    this2->shown_left_civ = parley_mode5_left_kind;
    this2->left_civ = this2->shown_left_civ;
    this2->caption_button_count = parley_mode5_right_kind;
    this2->right_civ = this2->caption_button_count;
    parley_add_side_dialog(this2,this2->left_civ,0);
    parley_add_side_dialog(this2,this2->right_civ,1);
  }
  return;
}

/* 0052e4c9 auto */
void __cdecl parley_on_accept_offer(void)

{
  int active_child;
  WindowObjectView *parley;
  
  active_child = wnd_get_active_child();
  if (active_child == 0) {
    parley = (WindowObjectView *)0x0;
  }
  else {
    parley = (WindowObjectView *)(active_child - 0x48);
  }
  wnd_activate((Wnd *)(parley + 0x12));
  net_send_message(0x83,*(i32 *)
                           (((i8 *)&net_session_block.net_player_slots) + *(int *)(((i8 *)&net_session_block.net_civ_slots) + parley_wnd_block.parley_other_civ * 4) * 0x54),0,0,0
                     ,0,0,0,0,0);
  dlg_pending_idle_callback = ((i8*)(turn_popup_timeout_idle));
  popup_game_with_sprite((iptr)&str_parleyaccept2,(iptr)&popup_info_icon_sprite,0);
  parley[0x7b].vtable = 3;
  parley_set_mode_sides(parley,1);
  return;
}

/* 0052e57c auto */
void __cdecl parley_on_no_thanks(void)

{
  iptr active_child;
  ViewWindow *this2;
  
  active_child = wnd_get_active_child();
  if (active_child == 0) {
    this2 = (ViewWindow *)0x0;
  }
  else {
    this2 = (ViewWindow *)(active_child - 0x48);
  }
  wnd_activate((Wnd *)this2->window_2);
  net_send_message(0x84,*(i32 *)
                           (((i8 *)&net_session_block.net_player_slots) + *(int *)(((i8 *)&net_session_block.net_civ_slots) + parley_wnd_block.parley_other_civ * 4) * 0x54),0,0,0
                     ,0,0,0,0,0);
  this2->session_mode = 2;
  this2->shown_left_civ = (((i32 *)&parley_mode_left_kinds))[this2->session_mode * 2];
  this2->left_civ = this2->shown_left_civ;
  this2->caption_button_count = (((i32 *)&parley_mode_right_kinds))[this2->session_mode * 2];
  this2->right_civ = this2->caption_button_count;
  parley_add_side_dialog(this2,this2->left_civ,0);
  parley_add_side_dialog(this2,this2->right_civ,1);
  return;
}

/* 0052e685 auto */
void __cdecl parley_on_counter_offer(void)

{
  int active_child;
  WindowObjectView *parley;
  
  active_child = wnd_get_active_child();
  if (active_child == 0) {
    parley = (WindowObjectView *)0x0;
  }
  else {
    parley = (WindowObjectView *)(active_child - 0x48);
  }
  wnd_activate((Wnd *)(parley + 0x12));
  net_send_message(0x85,*(i32 *)
                           (((i8 *)&net_session_block.net_player_slots) + *(int *)(((i8 *)&net_session_block.net_civ_slots) + parley_wnd_block.parley_other_civ * 4) * 0x54),0,0,0
                     ,0,0,0,0,0);
  parley[0x7b].vtable = 3;
  parley_set_mode_sides(parley,1);
  return;
}

/* 0052e71a auto */
void __cdecl chat_on_mute_checkbox(int ctrl_id)

{
  i32 checked;
  int chat_wnd2;
  
  chat_wnd2 = wnd_get_active_child();
  if (chat_wnd2 == 0) {
    chat_wnd2 = 0;
  }
  else {
    chat_wnd2 -= 0x48;
  }
  wnd_activate((Wnd *)(chat_wnd2 + 0x48));
  if ((0x428 < ctrl_id) && (ctrl_id < 0x430)) {
    checked = checkbox_is_checked
                      (*(Control **)(((i8 *)&chat_wnd_block.chat_mute_checkboxes) + (ctrl_id - 0x428) * 4));
    *(i32 *)(((i8 *)&chat_wnd_block.chat_muted_civs) + (ctrl_id - 0x428) * 4) = checked;
  }
  return;
}

/* 0052e7b7 auto */
void __cdecl chat_on_send_checkbox(int ctrl_id)

{
  i32 checked;
  int slot;
  int chat_wnd2;
  
  chat_wnd2 = wnd_get_active_child();
  if (chat_wnd2 == 0) {
    chat_wnd2 = 0;
  }
  else {
    chat_wnd2 -= 0x48;
  }
  wnd_activate((Wnd *)(chat_wnd2 + 0x48));
  switch(ctrl_id) {
  case 0x415:
    chat_wnd_block.chat_remain_anonymous = checkbox_is_checked(chat_wnd_block.chat_anonymous_checkbox);
    break;
  case 0x416:
    chat_wnd_block.chat_broadcast_all = checkbox_is_checked(chat_wnd_block.chat_broadcast_checkbox);
    if (chat_wnd_block.chat_broadcast_all != 0) {
      for (slot = 1; slot < 8; slot++) {
        if (*(int *)(((i8 *)&chat_wnd_block.chat_send_checkboxes) + slot * 4) != 0) {
          checkbox_set_checked(*(Control **)(((i8 *)&chat_wnd_block.chat_send_checkboxes) + slot * 4),1);
          ctrl_show_and_redraw(*(Control **)(((i8 *)&chat_wnd_block.chat_send_checkboxes) + slot * 4));
          *(i32 *)(((i8 *)&chat_wnd_block.chat_send_to_civs) + slot * 4) = 1;
        }
      }
    }
    break;
  case 0x417:
  case 0x418:
  case 0x419:
  case 0x41a:
  case 0x41b:
  case 0x41c:
  case 0x41d:
    ctrl_id -= 0x416;
    checked = checkbox_is_checked(*(Control **)(((i8 *)&chat_wnd_block.chat_send_checkboxes) + ctrl_id * 4));
    *(i32 *)(((i8 *)&chat_wnd_block.chat_send_to_civs) + ctrl_id * 4) = checked;
    if ((*(int *)(((i8 *)&chat_wnd_block.chat_send_to_civs) + ctrl_id * 4) == 0) && (chat_wnd_block.chat_broadcast_all != 0)) {
      checkbox_set_checked(chat_wnd_block.chat_broadcast_checkbox,0);
      ctrl_show_and_redraw(chat_wnd_block.chat_broadcast_checkbox);
      chat_wnd_block.chat_broadcast_all = 0;
    }
    break;
  case 0x430:
    chat_wnd_block.chat_mute_anonymous = checkbox_is_checked(chat_wnd_block.chat_mute_anonymous_checkbox);
  }
  return;
}

/* 0052e971 auto */
void __thiscall parley_update_buttons(ViewWindow *self)

{
  if ((self->rates_clamped != 0) && (self->mode2_button_value != 0)) {
    if (self->session_mode != 2) {
      control_hide((Control *)self->conceal_button_value);
      ctrl_disable((Control *)self->conceal_button_value);
      control_hide((Control *)self->reveal_button_value);
      ctrl_disable((Control *)self->reveal_button_value);
    }
    switch(self->session_mode) {
    case 1:
    case 2:
      control_hide((Control *)self->mode2_button_value);
      ctrl_disable((Control *)self->mode2_button_value);
      ctrl_show_and_redraw((Control *)self->rates_clamped);
      ctrl_disable((Control *)self->rates_clamped);
      if (self->session_mode == 2) {
        if ((self->left_side_accepted == '\0') && (self->left_side_confirmed == '\0')) {
          control_hide((Control *)self->conceal_button_value);
          ctrl_disable((Control *)self->conceal_button_value);
          ctrl_show_and_redraw((Control *)self->reveal_button_value);
          ctrl_enable((Control *)self->reveal_button_value);
        }
        else {
          ctrl_show_and_redraw((Control *)self->conceal_button_value);
          ctrl_enable((Control *)self->conceal_button_value);
          control_hide((Control *)self->reveal_button_value);
          ctrl_disable((Control *)self->reveal_button_value);
        }
      }
      break;
    case 3:
    case 5:
      control_hide((Control *)self->mode2_button_value);
      ctrl_disable((Control *)self->mode2_button_value);
      ctrl_show_and_redraw((Control *)self->rates_clamped);
      ctrl_enable((Control *)self->rates_clamped);
      break;
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xf:
      ctrl_show_and_redraw((Control *)self->mode2_button_value);
      control_hide((Control *)self->rates_clamped);
      ctrl_disable((Control *)self->rates_clamped);
      if (self->timer_last_value == 0) {
        ctrl_disable((Control *)self->mode2_button_value);
      }
      else {
        ctrl_enable((Control *)self->mode2_button_value);
      }
      break;
    case 0xe:
      ctrl_show_and_redraw((Control *)self->mode2_button_value);
      control_hide((Control *)self->rates_clamped);
      ctrl_disable((Control *)self->rates_clamped);
      if ((self->show_turn_status == 0) || (self->timer_last_value == 0)) {
        ctrl_disable((Control *)self->mode2_button_value);
      }
      else {
        ctrl_enable((Control *)self->mode2_button_value);
      }
    }
  }
  return;
}

/* 0052ec47 auto */
iptr __thiscall parley_find_unit_by_id(WindowObjectView *self,int unit_id)

{
  short x2;
  short y2;
  bool near_land;
  iptr x;
  int y;
  int in_bounds;
  iptr unit;
  iptr dir;
  
  unit = (iptr)game.num_units;
  do {
    unit--;
    if (unit < 0) {
      return 0xffffffff;
    }
  } while ((units[unit].id == 0) || (units[unit].id != unit_id));
  x2 = units[unit].x;
  y2 = units[unit].y;
  near_land = false;
  dir = 0;
  do {
    if (7 < dir) {
check_stack_result:
      if ((!near_land) && (y = unit_stack_sum(unit,2), y != 1)) {
        unit = -2;
      }
      return unit;
    }
    x = map_wrap_x((int)(char)(((i8 *)&dir_dx_table_block.dir_dx_table))[dir] + (int)x2);
    y = (int)(char)(((i8 *)&dir_dy_table_block.dir_dy_table))[dir] + (int)y2;
    in_bounds = map_in_bounds(x,y);
    if ((in_bounds != 0) && (y = tile_is_ocean(x,y), y == 0)) {
      near_land = true;
      goto check_stack_result;
    }
    dir++;
  } while( true );
}

/* 0052ed95 auto */
iptr __thiscall parley_find_city_by_id(WindowObjectView *self,int city_id)

{
  iptr city;
  
  city = (iptr)game.num_cities;
  do {
    city--;
    if (city < 0) {
      return 0xffffffff;
    }
  } while ((cities[city].id == 0) || (cities[city].id != city_id));
  return city;
}

/* 0055ae80 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl mp_turn_timer_stop(int notify)

{
  if (net_session_block.mp_turn_civ == human_civ[0]) {
    city_window_close();
    intel_report_end_modal();
    throneroom_close();
    pedia_end_modal();
  }
  if (mp_turn_timer_handle != 0) {
    game_timer_destroy(mp_turn_timer_handle);
    mp_turn_timer_handle = 0;
    status_draw_timer_bar(100,0xffffffff);
    if (((notify != 0) && (2 < game.multiplayer)) && (player_turn_active != '\0')) {
      net_send_message(0x6e,0xff,0,0,0,0,0,0,0,0);
    }
  }
  return;
}

/* 0055af2e auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl mp_turn_timer_start(int notify)

{
  RECT caption_rect;
  
  if (net_session_block.mp_turn_civ == human_civ[0]) {
    city_window_close();
    intel_report_end_modal();
    throneroom_close();
    pedia_end_modal();
  }
  mp_turn_seconds_left = civ_saved_cursor_x_block.mp_turn_time_limit_ms / 1000;
  setup_picwnd_block.g_timer_blink[0] = 0;
  map_views_block.main_view_timer_cache_i32 = 0xffffffff;
  frame_wnd_draw_caption((FrameWindow *)((i8 *)&map_views_block.map_views));
  caption_rect.left = map_views_block.main_view_frame_left;
  caption_rect.top = map_views_block.main_view_frame_top;
  caption_rect.right = map_views_block.main_view_frame_right;
  caption_rect.bottom = map_views_block.main_view_client_top;
  wnd_blit_surface_rect((DibSurface *)((i8 *)&map_views_block.map_views),(iptr)&caption_rect);
  if (mp_turn_timer_handle != 0) {
    game_timer_destroy(mp_turn_timer_handle);
  }
  mp_turn_timer_handle = game_timer_create((iptr)mp_turn_timer_tick,500,1);
  g_timer_last_tick = timer_ticks();
  if ((notify != 0) && (2 < game.multiplayer)) {
    net_send_message(0x6d,0xff,0,0,0,0,0,0,0,0);
  }
  return;
}

/* 0055b046 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl mp_turn_timer_resume(int notify)

{
  city_window_close();
  intel_report_end_modal();
  throneroom_close();
  pedia_end_modal();
  if ((mp_turn_seconds_left != 0) && (map_views_block.main_view_timer_shown[0] != 0)) {
    if (mp_turn_timer_handle != 0) {
      game_timer_destroy(mp_turn_timer_handle);
    }
    mp_turn_timer_handle = game_timer_create((iptr)mp_turn_timer_tick,500,1);
    g_timer_last_tick = timer_ticks();
    if ((notify != 0) && (2 < game.multiplayer)) {
      net_send_message(0x6f,0xff,0,0,0,0,0,0,0,0);
    }
  }
  return;
}

/* 0055b0fb: written by hand in src/game/timer_display.c */

/* 0055b2c6 auto */
void __cdecl mp_cmd_change_timer(void)

{
  int cancelled;
  RECT caption_rect;
  
  mp_turn_timer_stop(1);
  GetAsyncKeyState(0x1b);
  cancelled = setup_choose_game_timer(1);
  if (cancelled == 0) {
    if (civ_saved_cursor_x_block.mp_turn_time_limit_ms == 0) {
      map_views_block.main_view_timer_shown[0] = 0;
      frame_wnd_draw_caption((FrameWindow *)((i8 *)&map_views_block.map_views));
      caption_rect.left = map_views_block.main_view_frame_left;
      caption_rect.top = map_views_block.main_view_frame_top;
      caption_rect.right = map_views_block.main_view_frame_right;
      caption_rect.bottom = map_views_block.main_view_client_top;
      wnd_blit_surface_rect((DibSurface *)((i8 *)&map_views_block.map_views),(iptr)&caption_rect);
    }
    else {
      map_views_block.main_view_timer_shown[0] = 1;
      mp_turn_timer_start(1);
    }
    if (2 < game.multiplayer) {
      net_send_message(0x6c,0xff,civ_saved_cursor_x_block.mp_turn_time_limit_ms,0,0,0,0,0,0,0);
    }
  }
  else {
    mp_turn_timer_resume(1);
  }
  if (civ_saved_cursor_x_block.autoplay_active != 0) {
    player_turn_active = 0;
  }
  return;
}

/* 0055b3c8 auto */
void __cdecl mp_mouse_watchdog_stop(void)

{
  if (mp_mouse_watchdog_timer != 0) {
    game_timer_destroy(mp_mouse_watchdog_timer);
    mp_mouse_watchdog_timer = 0;
  }
  return;
}

/* 0055b3fd auto */
void __cdecl mp_mouse_watchdog_start(void)

{
  if (2 < game.multiplayer) {
    if (mp_mouse_watchdog_timer != 0) {
      game_timer_destroy(mp_mouse_watchdog_timer);
    }
    mp_mouse_watchdog_timer = game_timer_create((iptr)mp_mouse_watchdog_tick,500,1);
  }
  return;
}

/* 0055b451 auto */
i32 __cdecl mp_window_drag_mouse_hook(void)

{
  if (mp_window_drag_active != '\0') {
    mp_mouse_watchdog_tick(0,0);
  }
  return 0;
}

/* 0055b47e auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl mp_window_drag_begin(void)

{
  dbg_log((iptr)&str_enter_window_drag);
  mp_window_drag_active = 1;
  mp_window_drag_start_ticks = timer_ticks();
  mp_window_drag_flag_i32 = 0;
  mp_window_drag_wnd = wnd_get_active_child();
  if (net_session_block.net_host_flag != '\0') {
    net_send_message(0x5d,0xff,0,0,0,0,0,0,0,0);
    XD_FlushSendBuffer(5000);
  }
  setup_picwnd_block.mp_window_drag_hook = SetWindowsHookExA(7,(HOOKPROC)((void *)(iptr)mp_window_drag_mouse_hook),err_report_ctx_block.app_hinstance,0);
  return;
}

/* 0055b515 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl mp_window_drag_end(void)

{
  dbg_log((iptr)&str_exit_window_drag);
  mp_window_drag_active = 0;
  mp_window_drag_start_ticks = 0;
  mp_window_drag_flag_i32 = 0;
  mp_window_drag_wnd = 0;
  UnhookWindowsHookEx(setup_picwnd_block.mp_window_drag_hook);
  if (net_session_block.net_host_flag != '\0') {
    net_send_message(0x5e,0xff,0,0,0,0,0,0,0,0);
    XD_FlushSendBuffer(5000);
  }
  return;
}

/* 0055b59e auto */
void __cdecl mp_release_mouse_capture(void)

{
  iptr wnd;
  UINT Msg;
  WPARAM wParam;
  LPARAM lParam;
  
  if (mp_window_drag_active != '\0') {
    if ((*(WndBase * *)&mp_window_drag_wnd) != (WndBase *)0x0) {
      lParam = 0;
      wParam = 0;
      Msg = 0x202;
      wnd = wnd_get_window((*(WndBase * *)&mp_window_drag_wnd));
      PostMessageA(*(HWND *)(wnd + 4),Msg,wParam,lParam);
      wnd_release_capture((*(WndBase * *)&mp_window_drag_wnd));
    }
    mp_window_drag_active = '\0';
  }
  return;
}

/* 0055b5fa auto */
void __cdecl mp_mouse_watchdog_tick(i32 timer_id,i32 timer_arg)

{
  int now_ticks;
  
  if ((((2 < game.multiplayer) && (net_session_block.net_player_count[0] != 1)) && (mp_window_drag_active != '\0')) &&
     ((now_ticks = timer_ticks(), mp_window_drag_start_ticks + 0x26c < now_ticks && (net_session_block.player_has_quit == '\0')))) {
    mp_release_mouse_capture();
  }
  mp_mouse_watchdog_start();
  return;
}

/* 0056e270 auto */
LobbyListCtorView * __thiscall lobby_list_ctor(LobbyListCtorView *self)

{
  u8 *slot_ptr;
  int i;
  
  self->next_id = 1;
  self->entries = 0;
  for (i = 0; i < 7; i++) {
    slot_ptr = self->player_slots_area + i * 4 + 0x28;
    slot_ptr[0] = '\0';
    slot_ptr[1] = '\0';
    slot_ptr[2] = '\0';
    slot_ptr[3] = '\0';
  }
  return self;
}

/* 0056e2c9 auto */
void __thiscall lobby_list_dtor(void *self)

{
  net_free_game_list(((iptr *)&net_session_block.net_session));
  return;
}

/* 0056e2e9 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __thiscall lobby_host_wait_players(LobbyList *self,i32 map_arg,int launch_mode)

{
  uint *flags_ptr;
  Dialog *this_00;
  int result;
  int entry;
  int waiting_entry;
  i32 ret;
  uptr new_dialog;
  i32 seh_frame;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0xffffffff;
  if ((launch_mode == 2) || (launch_mode == 3)) {
    net_send_message(2,0,0,0,0,0,0,0,0,0);
    self->dialog = 0;
    net_session_block.net_server_address[0] = 0;
    crt_strcpy(((i8 *)&net_session_block.net_game_name),((i8 *)&prefs_main_menu_choice_block.prefs_net_game_name));
    crt_strcpy(((i8 *)&net_session_block.net_local_player_name),((i8 *)&prefs_main_menu_choice_block.prefs_net_player_name));
    crt_strcpy(((i8 *)&net_session_block.net_host_player_name),((i8 *)&prefs_main_menu_choice_block.prefs_net_player_name));
  }
  else {
    this_00 = operator_new(0x2f4);
    seh_state = 0;
    if (this_00 == (Dialog *)0x0) {
      new_dialog = 0;
    }
    else {
      new_dialog = dialog_ctor(this_00,0x4000);
    }
    seh_state = 0xffffffff;
    self->dialog = new_dialog;
    if (self->dialog == 0) {
      err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_pplayerpopup_null,(iptr)&str_d_ss_franklinton_startup_playerbox_cpp,0x34);
    }
    *(i8 **)(((LobbyListExt *)self)->saved_button_labels) = dialog_button_labels[0];
    str_clear((iptr)(self + 1));
    str_append_label((iptr)(self + 1),0x28b);
    dialog_button_labels[0] = (i8 *)(self + 1);
    dlg_reset((Dialog *)self->dialog,0x81801);
    text_clear();
    text_append_label(0x288);
    if (launch_mode == 0) {
      crt_strcat(((i8 *)&map_views_block.text_buffer),((i8 *)&lobby_ip_sep_str));
      crt_strcat(((i8 *)&map_views_block.text_buffer),((i8 *)&prefs_main_menu_choice_block.prefs_net_ip_address));
    }
    dialog_set_title((DialogWindowView *)self->dialog,(iptr)&map_views_block.text_buffer);
    text_clear();
    text_append_label(0x120);
    dialog_add_button((DialogButtonsView *)self->dialog,(iptr)&map_views_block.text_buffer);
    lobby_add_waiting_entry(self);
    dialog_set_listbox((DialogTextView *)self->dialog,7,0x1b7,0);
    dialog_set_default_choice((DialogOptionList *)self->dialog,self->next_id - 1);
    dialog_render((Dialog *)self->dialog);
    wnd_set_modal_idle_callback((ModalMenuWindow *)(*(int *)self->dialog + 0x48),(iptr)lobby_dialog_idle);
    if (net_session_block.net_lobby_launch_mode == 2) {
      dbg_log((iptr)&str_igz_sending_dplsys_connectionsettingsrea);
      result = XD_LobbySendMessage(1);
      if (result != 0) {
        dbg_logf((iptr)&str_igz_xd_lobbysendmessage_returned_error_d_2,result);
      }
      dbg_log((iptr)&str_igz_sending_dplsys_dplayconnectsucceeded);
      result = XD_LobbySendMessage(3);
      if (result != 0) {
        dbg_logf((iptr)&str_igz_xd_lobbysendmessage_returned_error_d_3,result);
      }
    }
    while( true ) {
      net_send_message(2,0,0,0,0,0,0,0,0,0);
      flags_ptr = (uint *)(self->dialog + 0x3c);
      *flags_ptr = *flags_ptr & 0xfffffbff;
      *(i32 *)(self->dialog + 0xd8) = 0;
      *(i32 *)(self->dialog + 0xdc) = *(i32 *)(self->dialog + 0xd8);
      result = dlg_show_modal((Dialog *)self->dialog,0);
      if (*(int *)(self->dialog + 0xdc) != 1) break;
      entry = lobby_find_entry_by_id(self,result);
      result = lobby_slot_for_entry_id(self,result);
      if ((entry != 0) && (waiting_entry = lobby_find_waiting_entry(self), waiting_entry == 0)) {
        net_send_message(5,*(i32 *)(((i8 *)&net_session_block.net_player_slots) + result * 0x54),0,0,0,0,0,0,0,0);
        XD_FlushSendBuffer(180000);
        XD_ServerCloseConnection((ushort)*(i32 *)(((i8 *)&net_session_block.net_player_slots) + result * 0x54));
        ret = lobby_entry_neighbor(self,entry);
        *(i32 *)(self->dialog + 0x220) = ret;
        lobby_remove_entry(self,entry);
        net_remove_player
                  ((NetSession *)((iptr *)&net_session_block.net_session),*(i32 *)(((i8 *)&net_session_block.net_player_slots) + result * 0x54));
        lobby_add_waiting_entry(self);
      }
    }
    if (result < 0) {
      net_send_message(0xb,0xff,0,0,0,0,0,0,0,0);
      dialog_button_labels[0] = *(i8 **)(((LobbyListExt *)self)->saved_button_labels);
      lobby_clear_player_list(self);
      if ((Dialog *)self->dialog != (Dialog *)0x0) {
        dialog_scalar_dtor((Dialog *)self->dialog,1);
      }
      self->dialog = 0;
      XD_StopConnections();
      ret = 0;
      goto return_ret;
    }
    crt_strcpy(((i8 *)&net_session_block.net_server_address),((i8 *)&prefs_main_menu_choice_block.prefs_net_ip_address));
    crt_strcpy(((i8 *)&net_session_block.net_game_name),((i8 *)&prefs_main_menu_choice_block.prefs_net_game_name));
    crt_strcpy(((i8 *)&net_session_block.net_local_player_name),((i8 *)&prefs_main_menu_choice_block.prefs_net_player_name));
    crt_strcpy(((i8 *)&net_session_block.net_host_player_name),((i8 *)&prefs_main_menu_choice_block.prefs_net_player_name));
    dialog_close((Dialog *)self->dialog);
    dialog_button_labels[0] = *(i8 **)(((LobbyListExt *)self)->saved_button_labels);
    lobby_clear_player_list(self);
    if ((Dialog *)self->dialog != (Dialog *)0x0) {
      dialog_scalar_dtor((Dialog *)self->dialog,1);
    }
    self->dialog = 0;
    wnd_flush_paint();
  }
  if (1 < net_session_block.net_player_count[0]) {
    net_send_message(4,0xff,0,0,0,0,0,0,0,0);
  }
  net_session_block.net_session_phase = 1;
  net_send_message(0x28,0xff,1,0,0,0,0,0,0,0);
  crt_strcpy(((i8 *)&net_session_block.net_slot_player_names),((i8 *)&prefs_main_menu_choice_block.prefs_net_player_name));
  diffeng_register_blocks();
  net_reset_msg_counts();
  net_send_message(6,0xff,0,0,0,0,0,0,0,0);
  net_send_message(9,0xff,0,0,0,0,0,0,0,0);
  net_session_block.net_local_slot = 0;
  result = game_profile_popup(1);
  if (result == -1) {
    net_send_message(0x32,0,0,0,0,0,0,0,0,0);
    XD_FlushSendBuffer(180000);
    ret = 0;
  }
  else {
    if ((civ_saved_cursor_x_block.saved_resume_new_game == 0) && (civ_saved_cursor_x_block.saved_turn_civ == '\0')) {
      leaders_reset_custom_names();
      game.civs_alive = '\0';
      result = setup_choose_tribe(0,3,0);
      if (result != 0) {
        if (1 < net_session_block.net_player_count[0]) {
          net_send_message(0xb,0xff,0,0,0,0,0,0,0,0);
        }
        XD_StopConnections();
        ret = 0;
        goto return_ret;
      }
    }
    else {
      result = net_choose_civ_dialog(0);
      if (result != 0) {
        if (1 < net_session_block.net_player_count[0]) {
          net_send_message(0xb,0xff,0,0,0,0,0,0,0,0);
        }
        XD_StopConnections();
        ret = 0;
        goto return_ret;
      }
    }
    *(i32 *)(((i8 *)&net_session_block.net_civ_slots) + game.player_civ * 4) = 0;
    net_session_block.net_slot_civs[0] = (int)game.player_civ;
    net_session_block.net_slot_active_flags[0] = 1;
    net_session_block.net_slot_host_flags[0] = 1;
    if (1 < net_session_block.net_player_count[0]) {
      crt_strcpy(((i8 *)&minimap_window_block.text_string_args),net_session_block.net_connection_title);
      dlg_pending_idle_callback = ((i8*)(lobby_wait_civs_chosen_idle));
      net_session_block.net_wait_start_ticks_i32 = timer_ticks();
      result = popup_game_sprite_flags((iptr)&str_waitingonjoin,0x2000001,(iptr)&popup_info_icon_sprite,0);
      if (result == -1) {
        net_send_message(0xb,0xff,0,0,0,0,0,0,0,0);
        XD_StopConnections();
        ret = 0;
        goto return_ret;
      }
    }
    if (1 < net_session_block.net_player_count[0]) {
      net_send_message(4,0xff,0,0,0,0,0,0,0,0);
    }
    if ((turn_resume_civ == '\0') && (turn_resume_new_game == 0)) {
      ret = setup_choose_hotseat_players();
      setup_choose_opponents(ret);
      prefs_save_civ2dat();
      rules_load_advances(1);
      rules_load_units(1);
      rules_load_improvements(1);
      snd_menu_end();
      map_generate(map_arg);
      diffeng_register_blocks();
      diffeng_alloc_mirror();
      game_init_new();
      if (setup_accelerated_start != 0) {
        game_accelerated_start(setup_accelerated_start - 1);
      }
      if (turn_resume_civ != '\0') {
        game.player_civ = turn_resume_civ;
        human_civ[0] = (iptr)turn_resume_civ;
      }
    }
    else {
      diffeng_register_blocks();
      diffeng_alloc_mirror();
    }
    text_close_file();
    if (1 < net_session_block.net_player_count[0]) {
      net_send_message(10,0xff,0,0,0,0,0,0,0,0);
      net_send_state_diff(0xff,1,0,0,0);
      XD_FlushSendBuffer(5000);
      net_send_message(0x25,0xff,scenario_events_loaded,unit_types_block.scenario_event_count,0,0,0,0,0,0);
      net_send_message(0x16,0xff,0,0,0,0,0,0,0,0);
      XD_FlushSendBuffer(180000);
    }
    net_reset_msg_counts();
    net_session_block.net_session_phase = 3;
    net_send_message(0x28,0xff,3,0,0,0,0,0,0,0);
    ret = 1;
  }
return_ret:
  return ret;
}

/* 0056ec92 auto */
void __cdecl lobby_wait_civs_chosen_idle(void)

{
  int slot;
  int pending_count;
  
  net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
  pending_count = 0;
  for (slot = 1; slot < 7; slot++) {
    if (((((i8 *)&net_session_block.net_slot_active_flags))[slot * 0x54] == 1) && ((((i32 *)&net_session_block.net_slot_civs))[slot * 0x15] == -1)) {
      pending_count++;
    }
  }
  if (pending_count == 0) {
    net_session_block.dialog_stack_top[0xf] = net_session_block.dialog_stack_top[0xf] | 0x400;
    net_session_block.net_session_phase = 2;
    net_send_message(0x28,0xff,2,0,0,0,0,0,0,0);
    wnd_end_modal_loop((ModalMenuWindow *)(*net_session_block.dialog_stack_top + 0x48));
  }
  return;
}

/* 0056ed62 auto */
void __cdecl lobby_dialog_idle(void)

{
  net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
  return;
}

/* 0056edd3 auto */
iptr __thiscall lobby_entry_neighbor(LobbyList *self,iptr entry)

{
  iptr neighbor;
  
  neighbor = entry;
  if (*(int *)(entry + 0x10) != 0) {
    neighbor = *(iptr *)(entry + 0x10);
  }
  if ((neighbor == entry) && (*(int *)(entry + 0x14) != 0)) {
    neighbor = *(iptr *)(entry + 0x14);
  }
  return neighbor;
}

/* 0056ee2c auto */
void __thiscall lobby_clear_player_list(LobbyList *self)

{
  void *next;
  void *entry;
  
  entry = (void *)self->entries;
  while (entry != (void *)0x0) {
    next = *(void **)((int)entry + 0x10);
    operator_delete(*(void **)((int)entry + 8));
    operator_delete(entry);
    entry = next;
  }
  self->entries = 0;
  *(i32 *)(self->dialog + 0x28) = 0;
  *(i32 *)(self->dialog + 0x228) = 0;
  *(i32 *)(self->dialog + 0x220) = 0;
  return;
}

/* 0056eed7 auto */
void __thiscall lobby_remove_entry(LobbyList *self,void *entry)

{
  int *count_ptr;
  
  if (entry != (void *)0x0) {
    if (*(int *)((int)entry + 0x14) == 0) {
      *(i32 *)(self->dialog + 0x228) = *(i32 *)((int)entry + 0x10);
      self->entries = *(uptr *)(self->dialog + 0x228);
    }
    else {
      *(i32 *)(*(int *)((int)entry + 0x14) + 0x10) = *(i32 *)((int)entry + 0x10);
    }
    if (*(int *)((int)entry + 0x10) != 0) {
      *(i32 *)(*(int *)((int)entry + 0x10) + 0x14) = *(i32 *)((int)entry + 0x14);
    }
    operator_delete(*(void **)((int)entry + 8));
    operator_delete(entry);
    count_ptr = (int *)(self->dialog + 0x28);
    *count_ptr = *count_ptr - 1;
  }
  return;
}

/* 0056ef93 auto */
uint * __thiscall lobby_add_player_entry(LobbyList *self,iptr name2,uint entry_id)

{
  int *count_ptr;
  uint *entry;
  size_t name_len;
  void *name_copy;
  int width;
  int max_width;
  uptr tail2;
  uptr node2;
  
  tail2 = 0;
  for (node2 = self->entries; node2 != 0; node2 = *(uptr *)(node2 + 0x10)) {
    tail2 = node2;
  }
  entry = operator_new(0x18);
  entry[4] = 0;
  entry[5] = tail2;
  if (tail2 == 0) {
    self->entries = (uptr)entry;
    *(uint **)(self->dialog + 0x228) = entry;
  }
  else {
    *(uint **)(tail2 + 0x10) = entry;
  }
  *entry = 0;
  name_len = _strlen((char *)name2);
  name_copy = operator_new(name_len + 1);
  entry[2] = (uint)name_copy;
  crt_strcpy(entry[2],name2);
  if (*(char *)name2 == '\0') {
    *entry = *entry | 1;
  }
  entry[1] = entry_id;
  entry[3] = 0;
  width = font_text_width(*(GameFont **)(self->dialog + 8),entry[2]);
  max_width = dialog_option_icon_width((DialogCore *)self->dialog);
  width = width + max_width + *(int *)(self->dialog + 0xac) + 5;
  max_width = *(int *)(self->dialog + 0x118);
  if (max_width <= width) {
    max_width = width;
  }
  *(int *)(self->dialog + 0x118) = max_width;
  count_ptr = (int *)(self->dialog + 0x28);
  *count_ptr = *count_ptr + 1;
  *(uptr *)(self->dialog + 0x228) = self->entries;
  *(i32 *)(self->dialog + 0x210) = *(i32 *)(self->dialog + 0x228);
  return entry;
}

/* 0056f113 auto */
void __cdecl lobby_refresh_player_list(void)

{
  int selected_id;
  int slot;
  uptr entry;
  
  if (net_session_block.net_lobby_list != (LobbyList *)0x0) {
    selected_id = *(int *)(*(int *)(net_session_block.net_lobby_list->dialog + 0x220) + 4);
    lobby_clear_player_list(net_session_block.net_lobby_list);
    if (net_session_block.net_player_count[0] == 0) {
      lobby_add_waiting_entry(net_session_block.net_lobby_list);
    }
    else {
      for (slot = 1; slot < 7; slot++) {
        if ((((i8 *)&net_session_block.net_slot_active_flags))[slot * 0x54] != '\0') {
          if (*(int *)(((i8 *)&net_session_block.net_slot_lobby_ids) + slot * 0x54) == 0) {
            *(u32 *)(((i8 *)&net_session_block.net_slot_lobby_ids) + slot * 0x54) = net_session_block.net_lobby_list->next_id;
            net_session_block.net_lobby_list->next_id++;
          }
          lobby_add_player_entry
                    (net_session_block.net_lobby_list,(iptr)(((i8 *)&net_session_block.net_slot_player_names) + slot * 0x54),
                     *(i32 *)(((i8 *)&net_session_block.net_slot_lobby_ids) + slot * 0x54));
        }
      }
      lobby_add_waiting_entry(net_session_block.net_lobby_list);
    }
    for (entry = net_session_block.net_lobby_list->entries; (entry != 0 && (*(int *)(entry + 4) != selected_id));
        entry = *(uptr *)(entry + 0x10)) {
    }
    if (entry == 0) {
      for (entry = net_session_block.net_lobby_list->entries;
          (*(int *)(entry + 0x10) != 0 && (*(int *)(entry + 4) < selected_id));
          entry = *(uptr *)(entry + 0x10)) {
      }
      if (entry == 0) {
        entry = net_session_block.net_lobby_list->entries;
      }
    }
    *(uptr *)(net_session_block.net_lobby_list->dialog + 0x228) = net_session_block.net_lobby_list->entries;
    *(i32 *)(net_session_block.net_lobby_list->dialog + 0x210) = *(i32 *)(net_session_block.net_lobby_list->dialog + 0x228);
    dialog_set_default_choice
              ((DialogOptionList *)net_session_block.net_lobby_list->dialog,*(iptr *)(entry + 4));
    dialog_render((Dialog *)net_session_block.net_lobby_list->dialog);
  }
  return;
}

/* 0056f301 auto */
void __thiscall lobby_add_waiting_entry(LobbyList *self)

{
  i32 entry_id;
  
  if (self->entries == 0) {
    text_clear();
    text_append_label(0x28c);
    entry_id = (*(i32 * *)&net_session_block.net_lobby_list)[1];
    (*(i32 * *)&net_session_block.net_lobby_list)[1]++;
    lobby_add_player_entry(self,(iptr)&map_views_block.text_buffer,entry_id);
    dialog_set_default_choice
              ((DialogOptionList *)*(*(i32 * *)&net_session_block.net_lobby_list),*(iptr *)((*(i32 * *)&net_session_block.net_lobby_list)[10] + 4));
  }
  return;
}

/* 0056f372 auto */
i32 __thiscall lobby_find_waiting_entry(LobbyList *self)

{
  int cmp;
  uptr entry;
  
  text_clear();
  text_append_label(0x28c);
  entry = self->entries;
  if (((entry != 0) && (*(int *)(entry + 0x10) == 0)) &&
     (cmp = _strcmp(((i8 *)&map_views_block.text_buffer),*(char **)(entry + 8)), cmp == 0)) {
    return entry;
  }
  return 0;
}

/* 0056f3e0 auto */
uptr __thiscall lobby_find_entry_by_id(LobbyList *self,int entry_id)

{
  uptr entry;
  
  for (entry = self->entries; (entry != 0 && (*(int *)(entry + 4) != entry_id));
      entry = *(uptr *)(entry + 0x10)) {
  }
  return entry;
}

/* 0056f42b auto */
int __thiscall lobby_slot_for_entry_id(LobbyList *self,int entry_id)

{
  int slot;
  
  for (slot = 0; (slot < 7 && (*(int *)(((i8 *)&net_session_block.net_slot_lobby_ids) + slot * 0x54) != entry_id));
      slot = slot + 1) {
  }
  return slot;
}

/* 00587a90 auto */
void __thiscall
parley_create_city_list_pane(ListPaneWindow *self,iptr rect,int pane,i32 own_cities)

{
  u8 *field_ptr;
  int right;
  int scroll_width;
  Control *new_ctrl;
  u8 *hotspot_parent;
  u8 *scroll_parent;
  i32 hotspot;
  i32 scrollbar;
  RECT rect2;
  i32 seh_frame;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0xffffffff;
  rect2.left = *(int *)rect;
  rect2.top = *(i32 *)(rect + 4);
  rect2.right = *(int *)(rect + 8);
  rect2.bottom = *(i32 *)(rect + 0xc);
  *(i32 *)(((i8 *)&sprite_picker_sprite_block.parley_pane_own_cities) + pane * 4) = own_cities;
  parley_build_city_list(self,pane,0);
  if (*(int *)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 4 + 0x4c) < 1) {
    field_ptr = ((PictureWindow *)self)->parley_pane_arrays_base + pane * 4 + 0x30;
    field_ptr[0] = 0xff;
    field_ptr[1] = 0xff;
    field_ptr[2] = 0xff;
    field_ptr[3] = 0xff;
  }
  else {
    field_ptr = ((PictureWindow *)self)->parley_pane_arrays_base + pane * 4 + 0x30;
    field_ptr[0] = '\0';
    field_ptr[1] = '\0';
    field_ptr[2] = '\0';
    field_ptr[3] = '\0';
  }
  field_ptr = ((PediaRedrawView *)self)->pedia_pane_layout + pane * 4 + 0x44;
  field_ptr[0] = 4;
  field_ptr[1] = '\0';
  field_ptr[2] = '\0';
  field_ptr[3] = '\0';
  *(i32 *)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 0x10 + 0x24) = *(i32 *)rect;
  *(i32 *)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 0x10 + 0x28) = *(i32 *)(rect + 4);
  *(i32 *)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 0x10 + 0x2c) = *(i32 *)(rect + 8);
  *(i32 *)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 0x10 + 0x30) = *(i32 *)(rect + 0xc);
  if (*(int *)(((PictureWindow *)self)->parley_pane_arrays_base + pane * 4 + 0x40) <
      *(int *)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 4 + 0x4c)) {
    scroll_width = GetSystemMetrics(2);
    right = rect2.right;
    *(int *)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 0x10 + 0x2c) =
         *(int *)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 0x10 + 0x2c) - scroll_width;
    rect2.left = GetSystemMetrics(2);
    rect2.left = right - rect2.left;
    new_ctrl = operator_new(0x40);
    seh_state = 0;
    if (new_ctrl == (Control *)0x0) {
      scrollbar = 0;
    }
    else {
      scrollbar = scrollbar_ctor(new_ctrl);
    }
    seh_state = 0xffffffff;
    *(i32 *)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 4 - 0x20) = scrollbar;
    if (self == (ListPaneWindow *)0x0) {
      scroll_parent = (u8 *)0x0;
    }
    else {
      scroll_parent = self->window_2;
    }
    scrollbar_create
              (*(Control **)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 4 - 0x20),(iptr)scroll_parent,
               pane + 0x420,(iptr)&rect2,1);
    scrollbar_set_range
              (*(Control **)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 4 - 0x20),0,
               *(int *)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 4 + 0x4c) -
               *(int *)(((PictureWindow *)self)->parley_pane_arrays_base + pane * 4 + 0x40));
    scrollbar_set_pos(*(ClickControl **)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 4 - 0x20),0);
    scrollbar_set_page_size
              (*(Control **)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 4 - 0x20),
               *(i32 *)(((PictureWindow *)self)->parley_pane_arrays_base + pane * 4 + 0x40));
    scrollbar_set_callback
              (*(Control **)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 4 - 0x20),
               (iptr)(((void *)(iptr)parley_city_list_scroll_local) + ((pane == 0) - 1 & 0xfb9)));
    scrollbar_set_track_callback
              (*(ScrollbarTrackSetView **)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 4 - 0x20),
               (iptr)(((void *)(iptr)parley_city_list_scroll_local) + ((pane == 0) - 1 & 0xfb9)));
  }
  new_ctrl = operator_new(0x40);
  seh_state = 1;
  if (new_ctrl == (Control *)0x0) {
    hotspot = 0;
  }
  else {
    hotspot = hotspot_ctor(new_ctrl);
  }
  seh_state = 0xffffffff;
  *(i32 *)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 4 - 0x18) = hotspot;
  if (self == (ListPaneWindow *)0x0) {
    hotspot_parent = (u8 *)0x0;
  }
  else {
    hotspot_parent = self->window_2;
  }
  hotspot_create
            (*(ClickControl **)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 4 - 0x18),(iptr)hotspot_parent,
             pane + 0x422,(iptr)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 0x10 + 0x24));
  hotspot_set_click_callback(*(HotspotClickSetView **)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 4 - 0x18),(iptr)parley_city_list_click);
  hotspot_set_dblclick_callback(*(HotspotDblClickSetView **)(((PediaRedrawView *)self)->pedia_pane_layout + pane * 4 - 0x18),(iptr)parley_city_list_click);
  parley_draw_city_list(pane);
  return;
}

/* 00587e05 auto */
void __cdecl parley_city_list_scroll_local(i32 pos)

{
  parley_city_list_scroll(0,pos);
  return;
}

/* 00587e41 auto */
void __cdecl parley_reveal_city_info(void)

{
  iptr child;
  iptr parley_wnd2;
  
  child = wnd_get_active_child();
  if (child == 0) {
    parley_wnd2 = 0;
  }
  else {
    parley_wnd2 = child - 0x48;
  }
  wnd_activate((Wnd *)(parley_wnd2 + 0x48));
  ctrl_show_and_redraw(*(Control **)(parley_wnd2 + 0x3a4));
  control_hide(*(Control **)(parley_wnd2 + 0x39c));
  *(i8 *)(parley_wnd2 + 0x3be) = 1;
  net_send_message(0xa5,*(i32 *)
                           (((i8 *)&net_session_block.net_player_slots) +
                           *(int *)(((i8 *)&net_session_block.net_civ_slots) + *(int *)(parley_wnd2 + 0x118) * 4) * 0x54),
                     human_civ[0],(int)*(char *)(parley_wnd2 + 0x3be),0,0,0,0,0,0);
  parley_draw_city_list(0);
  return;
}

/* 00587f00 auto */
void __cdecl parley_hide_city_info(void)

{
  iptr child;
  iptr parley_wnd2;
  
  child = wnd_get_active_child();
  if (child == 0) {
    parley_wnd2 = 0;
  }
  else {
    parley_wnd2 = child - 0x48;
  }
  wnd_activate((Wnd *)(parley_wnd2 + 0x48));
  ctrl_show_and_redraw(*(Control **)(parley_wnd2 + 0x39c));
  control_hide(*(Control **)(parley_wnd2 + 0x3a4));
  *(i8 *)(parley_wnd2 + 0x3be) = 0;
  net_send_message(0xa6,*(i32 *)
                           (((i8 *)&net_session_block.net_player_slots) +
                           *(int *)(((i8 *)&net_session_block.net_civ_slots) + *(int *)(parley_wnd2 + 0x118) * 4) * 0x54),
                     human_civ[0],(int)*(char *)(parley_wnd2 + 0x3be),0,0,0,0,0,0);
  parley_draw_city_list(0);
  return;
}

/* 0058804f auto */
void __cdecl parley_city_list_scroll(int pane,i32 pos)

{
  int child;
  iptr parley_wnd2;
  
  child = wnd_get_active_child();
  if (child == 0) {
    parley_wnd2 = 0;
  }
  else {
    parley_wnd2 = child - 0x48;
  }
  wnd_activate((Wnd *)(parley_wnd2 + 0x48));
  *(i32 *)(parley_wnd2 + 0x10410 + pane * 4) = pos;
  parley_draw_city_list(pane);
  return;
}

/* 005880b0 auto */
void __cdecl parley_city_list_click(int control_id)

{
  uint *sel_flag;
  int hit_row;
  int key_down;
  int sel_end;
  int row;
  i32 cursor_y;
  i32 cursor_x;
  int pane;
  iptr parley_wnd2;
  
  hit_row = wnd_get_active_child();
  if (hit_row == 0) {
    parley_wnd2 = 0;
  }
  else {
    parley_wnd2 = hit_row - 0x48;
  }
  wnd_activate((Wnd *)(parley_wnd2 + 0x48));
  pane = control_id - 0x422;
  wnd_get_cursor_pos
            ((WndBase *)(parley_wnd2 + 0x48),(iptr)&cursor_x,(iptr)&cursor_y);
  if (((*(int *)(parley_wnd2 + 1000 + pane * 4) != 0) &&
      (hit_row = parley_city_list_hit_test(cursor_x,cursor_y,pane), 0 < hit_row)) &&
     (hit_row < *(int *)(parley_wnd2 + 1000 + pane * 4))) {
    key_down = wnd_is_shift_down((void *)(parley_wnd2 + 0x48));
    if (key_down == 0) {
      key_down = wnd_is_ctrl_down((void *)(parley_wnd2 + 0x48));
      if (key_down == 0) {
        for (row = 0; row < *(int *)(parley_wnd2 + 1000 + pane * 4);
            row = row + 1) {
          if (row != hit_row) {
            *(i32 *)(pane * 0x2004 + row * 4 + 0x8400 + parley_wnd2) = 0;
          }
        }
        *(int *)(parley_wnd2 + 0x10418 + pane * 4) = hit_row;
        sel_flag = (uint *)(pane * 0x2004 + hit_row * 4 + 0x8400 + parley_wnd2);
        *sel_flag = *sel_flag ^ 1;
      }
      else {
        *(int *)(parley_wnd2 + 0x10418 + pane * 4) = hit_row;
        sel_flag = (uint *)(pane * 0x2004 + hit_row * 4 + 0x8400 + parley_wnd2);
        *sel_flag = *sel_flag ^ 1;
      }
    }
    else {
      for (row = 0; row < *(int *)(parley_wnd2 + 1000 + pane * 4); row++)
      {
        *(i32 *)(pane * 0x2004 + row * 4 + 0x8400 + parley_wnd2) = 0;
      }
      if (*(int *)(parley_wnd2 + 0x10418 + pane * 4) < hit_row) {
        row = *(int *)(parley_wnd2 + 0x10418 + pane * 4);
        sel_end = hit_row;
      }
      else {
        sel_end = *(int *)(parley_wnd2 + 0x10418 + pane * 4);
        row = hit_row;
      }
      for (; row <= sel_end; row++) {
        if (0 < row) {
          *(i32 *)(pane * 0x2004 + row * 4 + 0x8400 + parley_wnd2) = 1;
        }
      }
    }
    parley_draw_city_list(pane);
  }
  return;
}

/* 0058832d auto */
int __cdecl parley_city_list_hit_test(int x,int y,int pane)

{
  iptr child;
  int result;
  int height;
  iptr parley_wnd2;
  
  child = wnd_get_active_child();
  if (child == 0) {
    parley_wnd2 = 0;
  }
  else {
    parley_wnd2 = child - 0x48;
  }
  if (y < *(int *)(pane * 0x10 + 0x3c4 + parley_wnd2)) {
    result = -1;
  }
  else if (y < *(int *)(pane * 0x10 + 0x3cc + parley_wnd2)) {
    if (x < *(int *)(pane * 0x10 + 0x3c0 + parley_wnd2)) {
      result = -3;
    }
    else if (x < *(int *)(pane * 0x10 + 0x3c8 + parley_wnd2)) {
      result = *(int *)(pane * 0x10 + 0x3c4 + parley_wnd2);
      height = rect_height(pane * 0x10 + parley_wnd2 + 0x3c0);
      result = (y - result) / (height / *(int *)(parley_wnd2 + 0x10420 + pane * 4)) +
              *(int *)(parley_wnd2 + 0x10410 + pane * 4);
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

/* 0058843f auto */
void __thiscall parley_sort_city_list(void *self,int first,int last,int pane)

{
  i32 tmp;
  iptr child;
  int cmp;
  int j;
  int i;
  iptr parley_wnd2;
  
  child = wnd_get_active_child();
  if (child == 0) {
    parley_wnd2 = 0;
  }
  else {
    parley_wnd2 = child - 0x48;
  }
  if (1 < *(int *)(parley_wnd2 + 1000 + pane * 4)) {
    for (i = first; j = i, i < last; i++) {
      while (j = j + 1, j <= last) {
        cmp = city_has_improvement(*(iptr *)(j * 4 + pane * 0x2004 + 0x3f0 + parley_wnd2),1);
        if ((cmp != 0) ||
           ((cmp = city_has_improvement(*(iptr *)(i * 4 + pane * 0x2004 + 0x3f0 + parley_wnd2)
                                        ,1), cmp == 0 &&
            (cmp = _strcmp(cities[*(int *)(i * 4 + pane * 0x2004 + 0x3f0 + parley_wnd2)].
                             name,cities[*(int *)(j * 4 + pane * 0x2004 + 0x3f0 + parley_wnd2)
                                        ].name), 0 < cmp)))) {
          tmp = *(i32 *)(i * 4 + pane * 0x2004 + 0x3f0 + parley_wnd2);
          *(i32 *)(i * 4 + pane * 0x2004 + 0x3f0 + parley_wnd2) =
               *(i32 *)(j * 4 + pane * 0x2004 + 0x3f0 + parley_wnd2);
          *(i32 *)(j * 4 + pane * 0x2004 + 0x3f0 + parley_wnd2) = tmp;
          tmp = *(i32 *)(i * 4 + pane * 0x2004 + 0x8400 + parley_wnd2);
          *(i32 *)(i * 4 + pane * 0x2004 + 0x8400 + parley_wnd2) =
               *(i32 *)(j * 4 + pane * 0x2004 + 0x8400 + parley_wnd2);
          *(i32 *)(j * 4 + pane * 0x2004 + 0x8400 + parley_wnd2) = tmp;
          tmp = *(i32 *)(i * 4 + pane * 0x2004 + 0xc408 + parley_wnd2);
          *(i32 *)(i * 4 + pane * 0x2004 + 0xc408 + parley_wnd2) =
               *(i32 *)(j * 4 + pane * 0x2004 + 0xc408 + parley_wnd2);
          *(i32 *)(j * 4 + pane * 0x2004 + 0xc408 + parley_wnd2) = tmp;
          tmp = *(i32 *)(i * 4 + pane * 0x2004 + 0x43f8 + parley_wnd2);
          *(i32 *)(i * 4 + pane * 0x2004 + 0x43f8 + parley_wnd2) =
               *(i32 *)(j * 4 + pane * 0x2004 + 0x43f8 + parley_wnd2);
          *(i32 *)(j * 4 + pane * 0x2004 + 0x43f8 + parley_wnd2) = tmp;
        }
      }
    }
  }
  return;
}

/* 0058878e auto */
void __cdecl parley_draw_city_list(int pane)

{
  u8 *field_ptr;
  int xLeft;
  iptr child;
  int width;
  int text_offset_y;
  int row_y;
  int text_offset_x;
  i32 font_height;
  int selected;
  iptr label;
  i32 bg_color2;
  int city;
  int row;
  uint shadow_color2;
  uint text_color2;
  ViewWindow *this2;
  tagRECT row_rect;
  int row_height;
  int sprite_style;
  i8 saved_clip[16];
  GameFont *font2;
  
  child = wnd_get_active_child();
  if (child == 0) {
    this2 = (ViewWindow *)0x0;
  }
  else {
    this2 = (ViewWindow *)(child - 0x48);
  }
  surface_get_clip((DibSurface *)this2,(iptr)saved_clip);
  surface_set_clip((DibSurface *)this2,(iptr)((u8 *)&this2->advance_pane_rects + pane * 0x10));
fill_list_bg:
  surface_fill_rect
            ((DibSurface *)this2,(iptr)((u8 *)&this2->advance_pane_rects + pane * 0x10),list_bg_color);
  if (this2->large_layout == 0) {
    font2 = (GameFont *)((i8 *)&font_size14);
  }
  else {
    font2 = (GameFont *)((i8 *)&font_size21);
  }
  xLeft = *(int *)((u8 *)&this2->advance_pane_rects + pane * 0x10);
  width = rect_width((iptr)((u8 *)&this2->advance_pane_rects + pane * 0x10));
  row_height = rect_height((iptr)((u8 *)&this2->advance_pane_rects + pane * 0x10));
  row_height = row_height / *(int *)(((PictureWindow *)this2)->parley_pane_rows_base + pane * 4 + 0x38);
  text_offset_y = row_height / 2;
  row_y = font_cached_height(font2);
  text_offset_y -= row_y / 2;
  field_ptr = this2->pane_selection_flags_area + pane * 4 - 0x1c;
  field_ptr[0] = '\0';
  field_ptr[1] = '\0';
  field_ptr[2] = '\0';
  field_ptr[3] = '\0';
  for (row = 0; row < *(int *)((u8 *)&this2->advance_pane_rects + pane * 4 + 0x28);
      row = row + 1) {
    if (*(int *)(pane * 0x2004 + row * 4 + 0x8400 + (int)this2) != 0) {
      field_ptr = this2->pane_selection_flags_area + pane * 4 - 0x1c;
      field_ptr[0] = 1;
      field_ptr[1] = '\0';
      field_ptr[2] = '\0';
      field_ptr[3] = '\0';
      break;
    }
  }
  row = 0;
  do {
    if (*(int *)(((PictureWindow *)this2)->parley_pane_rows_base + pane * 4 + 0x38) <= row) {
restore_clip_and_finish:
      surface_set_clip((DibSurface *)this2,(iptr)saved_clip);
      parley_update_buttons(this2);
      ctrl_show_and_redraw(*(Control **)(this2->rate_values + pane * 4 + 0x20))
      ;
      return;
    }
    row_y = *(int *)((u8 *)&this2->advance_pane_rects + pane * 0x10 + 4) + row * row_height;
    SetRect(&row_rect,xLeft,row_y,width + xLeft,row_y + row_height);
    if ((row != 0) && (*(int *)(((PictureWindow *)this2)->parley_pane_rows_base + pane * 4 + 0x28) == -1))
    goto restore_clip_and_finish;
    if (*(int *)(((PictureWindow *)this2)->parley_pane_rows_base + pane * 4 + 0x28) + row <
        *(int *)((u8 *)&this2->advance_pane_rects + pane * 4 + 0x28)) {
      selected = *(int *)(pane * 0x2004 +
                       (*(int *)(((PictureWindow *)this2)->parley_pane_rows_base + pane * 4 + 0x28) + row) * 4 +
                       0x8400 + (int)this2);
      if (selected == 0) {
        if (*(int *)(((PictureWindow *)this2)->parley_pane_rows_base + pane * 4 + 0x28) + row == 0) {
          text_color2 = (uint)dlg_highlight_text_color;
          shadow_color2 = (*(uint *)&dlg_sel_text_shadow_color);
        }
        else {
          text_color2 = (*(uint *)&list_text_color);
          shadow_color2 = (*(uint *)&list_shadow_color);
        }
      }
      else {
        text_color2 = (*(uint *)&dlg_sel_text_color);
        shadow_color2 = (*(uint *)&dlg_sel_text_shadow_color);
      }
      city = 0;
      if ((0 < *(int *)((u8 *)&this2->advance_pane_rects + pane * 4 + 0x28)) &&
         (city = parley_find_city_by_id
                               ((WindowObjectView *)this2,
                                *(i32 *)
                                 (pane * 0x2004 +
                                  (*(int *)(((PictureWindow *)this2)->parley_pane_rows_base + pane * 4 + 0x28) + row)
                                  * 4 + 0x43f8 + (int)this2)), city == -1)) break;
      text_offset_x = (-(uint)(this2->large_layout == 0) & 0xffffffe2) + 0x5a + panel_margin_x;
      row_rect.left = row_rect.left + text_offset_x - 3;
      if (selected == 0) {
        bg_color2 = list_bg_color;
      }
      else {
        bg_color2 = list_sel_bg_color;
      }
      surface_fill_rect((DibSurface *)this2,(iptr)&row_rect,bg_color2);
      if (pane == 0) {
        if (this2->left_side_confirmed == '\0') {
          sprite_style = 3;
        }
        else {
          sprite_style = 0;
        }
      }
      else if (this2->remote_side_agreed == '\0') {
        sprite_style = 3;
      }
      else {
        sprite_style = 0;
      }
      if (parley_wnd_block.parley_mode == 10) {
        sprite_style = 0;
      }
      if (*(int *)(((PictureWindow *)this2)->parley_pane_rows_base + pane * 4 + 0x28) == -1) {
        text_clear();
        label = label_string(*(i32 *)(label_string_ids + 0xb78));
        text_append(label);
        field_ptr = this2->pane_selection_flags_area + pane * 4 - 0x1c;
        field_ptr[0] = '\0';
        field_ptr[1] = '\0';
        field_ptr[2] = '\0';
        field_ptr[3] = '\0';
      }
      else {
        selected = sprite_style;
        font_height = font_cached_height(font2);
        parley_draw_city_sprite(city,*(int *)(((PictureWindow *)this2)->parley_pane_rows_base + pane * 4 + 0x28) + row,
                           xLeft + 2,row_y,font_height,selected);
        text_clear();
        text_append(city * 0x58 + (iptr)((u8 *)&cities + 32));
        text_append_space();
        selected = city_has_improvement(city,1);
        if ((selected == 0) && (sprite_style == 0)) {
          text_append_lparen();
          text_append_int(*(iptr *)(pane * 0x2004 +
                                       (*(int *)(((PictureWindow *)this2)->parley_pane_rows_base + pane * 4 + 0x28) +
                                       row) * 4 + 0xc408 + (int)this2));
          text_append_space();
          if (*(int *)(pane * 0x2004 +
                       (*(int *)(((PictureWindow *)this2)->parley_pane_rows_base + pane * 4 + 0x28) + row) * 4 +
                       0xc408 + (int)this2) < 2) {
            label = label_string(*(i32 *)(label_string_ids + 0xb70));
            text_append(label);
          }
          else {
            label = label_string(*(i32 *)(label_string_ids + 0xb6c));
            text_append(label);
          }
        }
        else {
          selected = city_has_improvement(city,1);
          if (selected != 0) {
            label = label_string(*(i32 *)(label_string_ids + 0xb74));
            text_append(label);
          }
        }
      }
      if (shadow_color2 != text_color2) {
        gfx_set_text_color_index(shadow_color2);
        surface_draw_text
                  ((DibSurface *)this2,(iptr)font2,(iptr)&map_views_block.text_buffer,xLeft + text_offset_x + 2,
                   row_y + text_offset_y + 1,5);
        gfx_set_text_color_index(text_color2);
        surface_draw_text
                  ((DibSurface *)this2,(iptr)font2,(iptr)&map_views_block.text_buffer,xLeft + text_offset_x + 1,row_y + text_offset_y,
                   5);
      }
      gfx_set_text_color_index(text_color2);
      surface_draw_text
                ((DibSurface *)this2,(iptr)font2,(iptr)&map_views_block.text_buffer,xLeft + text_offset_x,row_y + text_offset_y,5);
    }
    row++;
  } while( true );
  parley_build_city_list((ListPaneWindow *)this2,pane,1);
  if (*(int *)((u8 *)&this2->advance_pane_rects + pane * 4 + 0x28) == 0) {
    field_ptr = ((PictureWindow *)this2)->parley_pane_rows_base + pane * 4 + 0x28;
    field_ptr[0] = 0xff;
    field_ptr[1] = 0xff;
    field_ptr[2] = 0xff;
    field_ptr[3] = 0xff;
  }
  else if (*(int *)((u8 *)&this2->advance_pane_rects + pane * 4 + 0x28) <
           *(int *)((u8 *)&this2->advance_pane_rects + pane * 4 + 0x28)) {
    *(int *)(((PictureWindow *)this2)->parley_pane_rows_base + pane * 4 + 0x28) =
         *(int *)((u8 *)&this2->advance_pane_rects + pane * 4 + 0x28) - 1;
  }
  goto fill_list_bg;
}

/* 00588e47 auto */
void __cdecl
parley_draw_city_sprite(iptr city,uint row_index,int x,int y,int row_height,i32 style)

{
  iptr child;
  int sprite_height2;
  i32 zoom2;
  i32 draw_x;
  i32 sprite_width2;
  iptr parley_wnd2;
  
  child = wnd_get_active_child();
  if (child == 0) {
    parley_wnd2 = 0;
  }
  else {
    parley_wnd2 = child - 0x48;
  }
  if (*(int *)(parley_wnd2 + 0x154) == 0) {
    zoom2 = 0xfffffffc;
  }
  else {
    zoom2 = 0xfffffffe;
  }
  draw_x = x;
  if (*(int *)(parley_wnd2 + 0x154) == 0) {
    sprite_width2 = 0x18;
  }
  else {
    sprite_width2 = 0x24;
  }
  if ((row_index & 1) != 0) {
    draw_x = x + sprite_width2 + 2;
  }
  sprite_height2 = gfx_zoom_scale(0x30,zoom2);
  gfx_draw_city((iptr)&parley_wnd_block.parley_wnd,city,style,draw_x,y - (sprite_height2 - row_height) / 2,zoom2);
  return;
}

/* 00588f36 auto */
void __thiscall parley_build_city_list(ListPaneWindow *self,int pane,int keep_selection)

{
  int *count_ptr;
  iptr child;
  iptr city;
  int old_count;
  iptr unit;
  void *old_selection;
  iptr parley_wnd2;
  
  old_selection = (void *)0x0;
  child = wnd_get_active_child();
  if (child == 0) {
    parley_wnd2 = 0;
  }
  else {
    parley_wnd2 = child - 0x48;
  }
  if (keep_selection != 0) {
    old_selection = operator_new(*(int *)(parley_wnd2 + 1000 + pane * 4) << 2);
    if (old_selection == (void *)0x0) {
      keep_selection = 0;
    }
    else {
      old_count = *(int *)(parley_wnd2 + 1000 + pane * 4);
      for (city = 0; city < old_count; city++) {
        if (*(int *)(pane * 0x2004 + city * 4 + 0x8400 + parley_wnd2) == 0) {
          *(i32 *)((int)old_selection + city * 4) = 0xffffffff;
        }
        else {
          *(i32 *)((int)old_selection + city * 4) =
               *(i32 *)(pane * 0x2004 + city * 4 + 0x43f8 + parley_wnd2);
        }
      }
    }
  }
  *(i32 *)(parley_wnd2 + 1000 + pane * 4) = 0;
  city = 0;
  do {
    if (game.num_cities <= city) {
      if (keep_selection != 0) {
        operator_delete(old_selection);
      }
      parley_sort_city_list(self,0,*(int *)(parley_wnd2 + 1000 + pane * 4) - 1,pane);
      return;
    }
    if ((cities[city].id != 0) &&
       (((*(int *)(((i8 *)&sprite_picker_sprite_block.parley_pane_own_cities) + pane * 4) != 0 && (cities[city].owner == (*(i8 *)&human_civ)))
        || (((*(int *)(((i8 *)&sprite_picker_sprite_block.parley_pane_own_cities) + pane * 4) == 0 &&
             ((int)cities[city].owner == self->caption_height)) &&
            (((1 << ((byte)(*(i8 *)&human_civ) & 0x1f) & (int)(char)cities[city].known_to) != 0 ||
             ((int)cities[city].owner == ((*(i8 *)&human_civ) & 0xffU))))))))) {
      *(iptr *)(pane * 0x2004 + *(int *)(parley_wnd2 + 1000 + pane * 4) * 4 + 0x3f0 + parley_wnd2) =
           city;
      *(i32 *)(pane * 0x2004 + *(int *)(parley_wnd2 + 1000 + pane * 4) * 4 + 0x43f8 + parley_wnd2) =
           cities[city].id;
      if (keep_selection == 0) {
        *(i32 *)
         (pane * 0x2004 + *(int *)(parley_wnd2 + 1000 + pane * 4) * 4 + 0x8400 + parley_wnd2) = 0;
      }
      else {
        *(i32 *)
         (pane * 0x2004 + *(int *)(parley_wnd2 + 1000 + pane * 4) * 4 + 0x8400 + parley_wnd2) = 0;
        for (unit = 0; unit < old_count; unit++) {
          if (cities[city].id == *(int *)((int)old_selection + unit * 4)) {
            *(i32 *)
             (pane * 0x2004 + *(int *)(parley_wnd2 + 1000 + pane * 4) * 4 + 0x8400 + parley_wnd2) = 1;
            break;
          }
        }
      }
      *(i32 *)
       (pane * 0x2004 + *(int *)(parley_wnd2 + 1000 + pane * 4) * 4 + 0xc408 + parley_wnd2) = 0;
      for (unit = 0; unit < game.num_units; unit++) {
        if (((units[unit].id != 0) && (cities[city].x == units[unit].x)) &&
           (cities[city].y == units[unit].y)) {
          count_ptr = (int *)(pane * 0x2004 + *(int *)(parley_wnd2 + 1000 + pane * 4) * 4 + 0xc408 +
                          parley_wnd2);
          *count_ptr = *count_ptr + 1;
        }
      }
      count_ptr = (int *)(parley_wnd2 + 1000 + pane * 4);
      *count_ptr = *count_ptr + 1;
    }
    city++;
  } while( true );
}

/* 00594d42 auto */
i32 __cdecl
net_lock_map(iptr civ,iptr src_x,iptr src_y,iptr dst_x,int dst_y,int wait_reply)

{
  i32 result;
  int start_ticks;
  int now_ticks;
  int src_conflict;
  int dst_conflict;
  int slot;
  
  net_session_block.net_lock_map_busy = 1;
  *(i32 *)(((i8 *)&net_map_lock_slots_block.net_map_lock_replies) + civ * 0x18) = 0;
  *(i32 *)(((i8 *)&net_map_lock_slots_block.net_map_lock_slots) + civ * 0x18) = *(i32 *)(((i8 *)&net_map_lock_slots_block.net_map_lock_replies) + civ * 0x18);
  if (net_session_block.net_host_flag == '\0') {
    net_session_block.net_lock_map_busy = 0;
    net_send_message(0x51,0,civ,src_x,src_y,dst_x,dst_y,0,0,0);
    XD_FlushSendBuffer(60000);
    if (wait_reply == 0) {
      result = 1;
    }
    else {
      start_ticks = timer_ticks();
      while( true ) {
        now_ticks = timer_ticks();
        if ((0xe0f < now_ticks - start_ticks) || (*(int *)(((i8 *)&net_map_lock_slots_block.net_map_lock_replies) + civ * 0x18) != 0)) break;
        net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,1);
      }
      if (*(int *)(((i8 *)&net_map_lock_slots_block.net_map_lock_replies) + civ * 0x18) == 0) {
        dbg_log((iptr)&str_lockmap_connection_to_server_timed_out);
        popup_game_with_sprite((iptr)&str_serverconnecttime_8,(iptr)&popup_info_icon_sprite,0);
        game_loop_active = 0;
        result = 0;
      }
      else if (*(int *)(((i8 *)&net_map_lock_slots_block.net_map_lock_replies) + civ * 0x18) == 1) {
        result = 1;
      }
      else {
        result = 0;
      }
    }
  }
  else {
    dst_conflict = -1;
    src_conflict = -1;
    for (slot = 1; slot < 8; slot++) {
      if (((*(int *)(((i8 *)&net_map_lock_slots_block.net_map_lock_src_x) + slot * 0x18) == src_x) &&
          (*(int *)(((i8 *)&net_map_lock_slots_block.net_map_lock_src_y) + slot * 0x18) == src_y)) ||
         ((*(int *)(((i8 *)&net_map_lock_slots_block.net_map_lock_dst_x) + slot * 0x18) == src_x &&
          (*(int *)(((i8 *)&net_map_lock_slots_block.net_map_lock_dst_y) + slot * 0x18) == src_y)))) {
        src_conflict = 0;
        break;
      }
      if (((*(int *)(((i8 *)&net_map_lock_slots_block.net_map_lock_src_x) + slot * 0x18) == dst_x) &&
          (*(int *)(((i8 *)&net_map_lock_slots_block.net_map_lock_src_y) + slot * 0x18) == dst_y)) ||
         ((*(int *)(((i8 *)&net_map_lock_slots_block.net_map_lock_dst_x) + slot * 0x18) == dst_x &&
          (*(int *)(((i8 *)&net_map_lock_slots_block.net_map_lock_dst_y) + slot * 0x18) == dst_y)))) {
        dst_conflict = 0;
        break;
      }
    }
    if ((src_conflict == -1) && (dst_conflict == -1)) {
      *(iptr *)(((i8 *)&net_map_lock_slots_block.net_map_lock_src_x) + civ * 0x18) = src_x;
      *(iptr *)(((i8 *)&net_map_lock_slots_block.net_map_lock_src_y) + civ * 0x18) = src_y;
      *(iptr *)(((i8 *)&net_map_lock_slots_block.net_map_lock_dst_x) + civ * 0x18) = dst_x;
      *(int *)(((i8 *)&net_map_lock_slots_block.net_map_lock_dst_y) + civ * 0x18) = dst_y;
      if ((human_civ[0] != civ) &&
         (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0 &&
          ((((i8 *)&net_session_block.net_slot_active_flags))[*(int *)(((i8 *)&net_session_block.net_civ_slots) + civ * 4) * 0x54] != '\0')))) {
        net_send_message(0x53,*(i32 *)
                                 (((i8 *)&net_session_block.net_player_slots) + *(int *)(((i8 *)&net_session_block.net_civ_slots) + civ * 4) * 0x54),
                           civ,1,0,0,0,0,0,0);
        XD_FlushSendBuffer(60000);
      }
      net_session_block.net_lock_map_busy = 0;
      result = 1;
    }
    else {
      if (((human_civ[0] != civ) &&
          ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) &&
         ((((i8 *)&net_session_block.net_slot_active_flags))[*(int *)(((i8 *)&net_session_block.net_civ_slots) + civ * 4) * 0x54] != '\0')) {
        net_send_message(0x53,*(i32 *)
                                 (((i8 *)&net_session_block.net_player_slots) + *(int *)(((i8 *)&net_session_block.net_civ_slots) + civ * 4) * 0x54),
                           civ,-1,0,0,0,0,0,0);
        XD_FlushSendBuffer(60000);
      }
      net_session_block.net_lock_map_busy = 0;
      result = 0;
    }
  }
  return result;
}

/* 0059511c auto */
void __cdecl net_unlock_map(iptr civ,int wait_reply)

{
  int start_ticks;
  int now_ticks;
  
  net_session_block.net_unlock_map_busy = 1;
  if (net_session_block.net_host_flag == '\0') {
    net_session_block.net_unlock_map_busy = 0;
    *(i32 *)(((i8 *)&net_map_lock_slots_block.net_map_lock_slots) + civ * 0x18) = 0;
    net_send_message(0x52,0,civ,0,0,0,0,0,0,0);
    if (wait_reply != 0) {
      start_ticks = timer_ticks();
      while( true ) {
        now_ticks = timer_ticks();
        if ((0xe0f < now_ticks - start_ticks) || (*(int *)(((i8 *)&net_map_lock_slots_block.net_map_lock_slots) + civ * 0x18) != 0)) break;
        net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,1);
      }
      if (*(int *)(((i8 *)&net_map_lock_slots_block.net_map_lock_slots) + civ * 0x18) == 0) {
        dbg_log((iptr)&str_unlockmap_connection_to_server_timed_out);
        popup_game_with_sprite((iptr)&str_serverconnecttime_9,(iptr)&popup_info_icon_sprite,0);
        game_loop_active = 0;
      }
    }
  }
  else {
    _memset(((i8 *)&net_map_lock_slots_block.net_map_lock_slots) + civ * 0x18,-1,0x18);
    net_send_message(0x55,0xff,civ,0,0,0,0,0,0,0);
    XD_FlushSendBuffer(60000);
    net_session_block.net_unlock_map_busy = 0;
  }
  return;
}

/* 0059a850 auto */
/* Library Function - Multiple Matches With Different Base Names
    _$E26
    _$E31
    _$E353
    _$E354
   
   Library: Visual Studio 1998 Debug */

void __cdecl net_session_global_init(void)

{
  net_session_static_init();
  net_session_reg_atexit();
  return;
}

/* 0059a86a auto */
void __cdecl net_session_static_init(void)

{
  net_session_ctor((NetSessionCtorView *)((iptr *)&net_session_block.net_session));
  return;
}

/* 0059a884 auto */
void __cdecl net_session_reg_atexit(void)

{
  _atexit(net_session_static_dtor);
  return;
}

/* 0059a8a1 auto */
void __cdecl net_session_static_dtor(void)

{
  net_session_dtor(((iptr *)&net_session_block.net_session));
  return;
}

/* 0059a8bb auto */
NetSessionCtorView * __thiscall net_session_ctor(NetSessionCtorView *self)

{
  i32 seh_frame;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0xffffffff;
  net_msg_player_info_init((NetMsgHeader *)&self->player_info_msg);
  net_msgq_ctor((NetMsgQueue *)(((NetSessionCtorViewExt *)self)->msg_queue));
  seh_state = 0;
  ((NetSessionCtorViewExt *)self)->connection_title[0] = '\0';
  ((NetSessionCtorViewExt *)self)->connection_title_b1[0] = '\0';
  ((NetSessionCtorViewExt *)self)->connection_title_b2[0] = '\0';
  ((NetSessionCtorViewExt *)self)->connection_title_b3[0] = '\0';
  XD_SetBroadcastReceive(net_on_broadcast_receive);
  XD_SetSecureReceive(net_on_secure_receive);
  XD_SetOnClientConnectionToServer(net_on_connected_to_server);
  XD_SetNewClientConnection(net_on_new_client);
  XD_SetOnConnectionLost(net_on_connection_lost);
  XD_SetOversizedMessageCB(50000,net_on_oversized_message);
  return self;
}

/* 0059a998 auto */
void __thiscall net_session_clear(void *self)

{
  int i;
  
  *(i8 *)((int)self + 0x1ec) = 0;
  *(i8 *)((int)self + 0x1ed) = 0;
  *(i32 *)((int)self + 0x574) = 0;
  *(i8 *)((int)self + 0x1ee) = 0;
  *(i32 *)((int)self + 0x538) = 0;
  *(i32 *)((int)self + 0x160cc) = 0;
  *(i32 *)self = 0;
  *(i32 *)((int)self + 4) = 0;
  *(i32 *)((int)self + 0x570) = 0;
  *(i32 *)((int)self + 0x1f8) = 0xffffffff;
  (*(i32 *)&net_session_block.net_xd_adapter_index) = 0;
  *(i32 *)((int)self + 500) = 0;
  net_session_block.net_active_protocol = 0xffffffff;
  *(i32 *)((int)self + 0x1f0) = 0xffffffff;
  *(i32 *)((int)self + 0x470) = 0;
  *(i8 *)((int)self + 0x57d) = 0;
  *(i32 *)((int)self + 0x580) = 0;
  *(i32 *)((int)self + 0x584) = 0;
  *(i32 *)((int)self + 0x588) = 0;
  *(i32 *)((int)self + 0x58c) = 0;
  *(i8 *)((int)self + 0x590) = 0;
  *(i8 *)((int)self + 0x57c) = 0;
  *(i8 *)((int)self + 0x591) = 0;
  *(i8 *)((int)self + 0x592) = 0;
  *(i32 *)((int)self + 0x594) = 8;
  *(i32 *)((int)self + 0x598) = 0;
  *(i32 *)((int)self + 0x7b0) = 0x3c;
  *(i32 *)((int)self + 0x59c) = 0xffffffff;
  *(i32 *)((int)self + 0x5a0) = 0xffffffff;
  *(i32 *)((int)self + 0x7b4) = 0;
  *(i32 *)((int)self + 0x7b8) = 0;
  *(i32 *)((int)self + 0x7bc) = 0;
  *(i32 *)((int)self + 0x7c0) = 0;
  *(i32 *)((int)self + 0x7c4) = 0;
  *(i32 *)((int)self + 0x7c8) = 0;
  *(i32 *)((int)self + 0x7cc) = 0;
  *(i32 *)((int)self + 2000) = 0;
  *(i32 *)((int)self + 0x7d4) = 0;
  *(i32 *)((int)self + 0x7d8) = 0;
  *(i32 *)((int)self + 0x7dc) = 0;
  *(i32 *)((int)self + 0x7e0) = 0;
  *(i32 *)((int)self + 0x7e4) = 0;
  *(i32 *)((int)self + 0x7e8) = 0;
  *(i32 *)((int)self + 0x7ec) = 0;
  *(i32 *)((int)self + 0x800) = 0;
  *(i32 *)((int)self + 0x804) = 0;
  *(i32 *)((int)self + 0x808) = 0;
  *(i32 *)((int)self + 0x80c) = 0;
  *(i32 *)((int)self + 0x810) = 0;
  *(i32 *)((int)self + 0x814) = 0;
  for (i = 0; i < 8; i++) {
    *(i32 *)((int)self + i * 4 + 0x2118) = 0;
    *(i32 *)((int)self + i * 4 + 0x2138) = 0;
    *(i32 *)((int)self + i * 4 + 0x2158) = 0;
    *(i32 *)((int)self + i * 4 + 0x2178) = 0;
  }
  *(i8 *)((int)self + 0x160a1) = 0;
  *(i32 *)((int)self + 0x7f0) = 0;
  *(i32 *)((int)self + 0x7f4) = 0;
  *(i32 *)((int)self + 0x7f8) = 0;
  *(i32 *)((int)self + 0x7fc) = 0;
  mp_meeting_pending = 0;
  *(i8 *)((int)self + 0x160a0) = 0;
  for (i = 0; i < 8; i++) {
    *(i32 *)((int)self + i * 4 + 0x53c) = 0;
    *(i32 *)((int)self + i * 4 + 0x16060) = 0;
    *(i32 *)((int)self + i * 4 + 0x16080) = 0;
  }
  *(i32 *)((int)self + 0x160a4) = 0;
  *(i8 *)((int)self + 0x160c8) = 0;
  net_session_shutdown(self,1);
  net_reset_error_counts();
  return;
}

/* 0059ad40 auto */
void __thiscall net_session_dtor(void *self)

{
  i32 seh_frame;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0;
  if (*(int *)((int)self + 0x534) != 0) {
    operator_delete(*(void **)((int)self + 0x534));
    *(i32 *)((int)self + 0x534) = 0;
  }
  net_session_shutdown(self,1);
  net_reset_error_counts();
  seh_state = 0xffffffff;
  /* inlined unwind funclet 0059adc8 */ { net_msgq_clear((NetMsgQueue *)(*(int *)((iptr)&self) + 0x160d0)); }
  return;
}

/* 0059adef auto */
i8 __thiscall net_init_transport(void *self,i32 protocol,int is_server)

{
  i32 saved_protocol;
  i8 result;
  UINT timeout_secs;
  int activate_error;
  int init_error;
  
  if (*(char *)((int)self + 0x1ec) != '\0') {
    err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_bconnectedtonet,(iptr)&str_d_ss_franklinton_netmgr_cpp,0x92);
  }
  saved_protocol = net_session_block.net_protocol;
  net_msgq_reset((NetMsgQueue *)((int)self + 0x160d0));
  net_session_clear(self);
  _memset((void *)((int)self + 0x200),0,0x270);
  switch(protocol) {
  case 0:
    init_error = XD_InitializeSocketsTCP
                        (3,0x1381,0x1382,(int)(char)is_server,7,NULL
                        );
    game.multiplayer = 3;
    if (*(int *)((int)self + 0x1e8) == 0) {
      timeout_secs = GetPrivateProfileIntA
                        (str_civilization_gold_17,str_internet_timeout,-1,
                         str_civ_ini_17);
      if ((timeout_secs == 0xffffffff) || ((int)timeout_secs < 0x3c)) {
        WritePrivateProfileStringA
                  (str_civilization_gold_18,str_internet_timeout_2,((i8 *)&net_internet_timeout_default),
                   str_civ_ini_18);
        *(i32 *)((int)self + 0x7b0) = 0x3c;
      }
      else {
        *(UINT *)((int)self + 0x7b0) = timeout_secs;
      }
    }
    else {
      timeout_secs = GetPrivateProfileIntA
                        (str_civilization_gold_19,str_tcpip_timeout,-1,str_civ_ini_19
                        );
      if ((timeout_secs == 0xffffffff) || ((int)timeout_secs < 0xf)) {
        WritePrivateProfileStringA
                  (str_civilization_gold_20,str_tcpip_timeout_2,((i8 *)&net_tcpip_timeout_default),
                   str_civ_ini_20);
        *(i32 *)((int)self + 0x7b0) = 0xf;
      }
      else {
        *(UINT *)((int)self + 0x7b0) = timeout_secs;
      }
    }
    break;
  case 1:
    init_error = XD_InitializeSocketsIPXSPX
                        (3,0x1381,0x1382,(int)(char)is_server,7,NULL
                        );
    game.multiplayer = 3;
    timeout_secs = GetPrivateProfileIntA
                      (str_civilization_gold_21,str_ipxspx_timeout,-1,str_civ_ini_21)
    ;
    if ((timeout_secs == 0xffffffff) || ((int)timeout_secs < 0xf)) {
      WritePrivateProfileStringA
                (str_civilization_gold_22,str_ipxspx_timeout_2,((i8 *)&net_ipxspx_timeout_default),
                 str_civ_ini_22);
      *(i32 *)((int)self + 0x7b0) = 0xf;
    }
    else {
      *(UINT *)((int)self + 0x7b0) = timeout_secs;
    }
    break;
  case 2:
    game.multiplayer = 5;
    timeout_secs = GetPrivateProfileIntA
                      (str_civilization_gold_23,str_modem_timeout,-1,str_civ_ini_23);
    if ((timeout_secs == 0xffffffff) || ((int)timeout_secs < 0x1e)) {
      WritePrivateProfileStringA
                (str_civilization_gold_24,str_modem_timeout_2,((i8 *)&net_modem_timeout_default),
                 str_civ_ini_24);
      *(i32 *)((int)self + 0x7b0) = 0x1e;
    }
    else {
      *(UINT *)((int)self + 0x7b0) = timeout_secs;
    }
    init_error = XD_InitializeModem((int)(char)is_server);
    break;
  case 3:
    game.multiplayer = 6;
    timeout_secs = GetPrivateProfileIntA
                      (str_civilization_gold_25,str_direct_timeout,-1,str_civ_ini_25)
    ;
    if ((timeout_secs == 0xffffffff) || ((int)timeout_secs < 0x1e)) {
      WritePrivateProfileStringA
                (str_civilization_gold_26,str_direct_timeout_2,((i8 *)&net_direct_timeout_default),
                 str_civ_ini_26);
      *(i32 *)((int)self + 0x7b0) = 0x1e;
    }
    else {
      *(UINT *)((int)self + 0x7b0) = timeout_secs;
    }
    init_error = XD_InitializeSerial((int)(char)is_server);
    break;
  default:
    err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_0_6,(iptr)&str_d_ss_franklinton_netmgr_cpp_2,0xf4);
  }
  if (init_error == 0) {
    if (((char)is_server == '\0') || (activate_error = XD_ActivateServer(), activate_error == 0)) {
      *(char *)((int)self + 0x1ef) = (char)is_server;
      *(i8 *)((int)self + 0x1ec) = 1;
      net_session_block.net_active_protocol = protocol;
      *(i32 *)((int)self + 0x1f0) = protocol;
      net_reset_error_counts();
      net_reset_msg_counts();
      _memset((void *)((int)self + 0x208),0,0x20);
      _strncpy((char *)((int)self + 0x208),((i8 *)&prefs_main_menu_choice_block.prefs_net_ip_address),0x20);
      _memset((void *)((int)self + 0x228),0,0x20);
      _strncpy((char *)((int)self + 0x228),((i8 *)&prefs_main_menu_choice_block.prefs_net_player_name),0x20);
      *(i32 *)((int)self + 0x200) = 1;
      *(i8 *)((int)self + 0x251) = 1;
      *(i8 *)((int)self + 0x250) = *(i8 *)((int)self + 0x1ef);
      result = 1;
    }
    else {
      dbg_logf((iptr)&str_connecttonet_xd_activateserver_failed_re,activate_error);
      result = 0;
      net_session_block.net_protocol = saved_protocol;
    }
  }
  else {
    dbg_logf((iptr)&str_connecttonet_xd_initialize_failed_return,init_error);
    result = 0;
    net_session_block.net_protocol = saved_protocol;
  }
  return result;
}

/* 0059b293 auto */
/* WARNING: Removing unreachable block (ram,0x0059b3ca) */

void __thiscall net_session_shutdown(void *self,int delay_after)

{
  dbg_log((iptr)&str_disconnecting_from_network);
  if (*(char *)((int)self + 0x1ef) != '\0') {
    delay_after = 0;
  }
  if (*(char *)((int)self + 0x1ec) == '\0') {
    XD_ResetLibrary();
    dbg_log((iptr)&str_xd_resetlibrary_2);
  }
  else {
    net_free_game_list(self);
    if (*(char *)((int)self + 0x1ed) != '\0') {
      XD_FlushSendBuffer(60000);
      dbg_log((iptr)&str_send_buffer_has_flushed);
      net_msgq_reset((NetMsgQueue *)((int)self + 0x160d0));
      net_popup_queue_clear();
      XD_CloseConnection();
      net_msgq_reset((NetMsgQueue *)((int)self + 0x160d0));
      net_popup_queue_clear();
      dbg_log((iptr)&str_xd_closeconnection);
      net_session_close_hook_nop(self);
    }
    switch(*(i32 *)((int)self + 0x1f0)) {
    case 0:
      XD_ShutdownSockets();
      dbg_log((iptr)&str_xd_shutdownsockets);
      break;
    case 1:
      XD_ShutdownSockets();
      dbg_log((iptr)&str_xd_shutdownsockets_2);
      break;
    case 2:
      XD_ShutdownModem();
      dbg_log((iptr)&str_xd_shutdownmodem);
      break;
    case 3:
      XD_ShutdownTEN();
      dbg_log((iptr)&str_xd_shutdownten);
    }
    net_msgq_reset((NetMsgQueue *)((int)self + 0x160d0));
    net_popup_queue_clear();
    if (0 < *(int *)((int)self + 0x584)) {
      dbg_logf((iptr)&str_maximum_gnetmgr_poll_call_depth_d,*(iptr *)((int)self + 0x584));
    }
    if (0 < *(int *)((int)self + 0x58c)) {
      dbg_logf((iptr)&str_maximum_alpha_message_queue_load_d,*(iptr *)((int)self + 0x58c));
    }
    if (0 < *(int *)((int)self + 0x588)) {
      dbg_logf((iptr)&str_maximum_message_queue_load_d,*(iptr *)((int)self + 0x588));
    }
    if (*(int *)((int)self + 0x814) != 0) {
      dbg_logf((iptr)&str_maximum_draw_stack_load_d,*(iptr *)((int)self + 0x814));
    }
    XD_ResetLibrary();
    dbg_log((iptr)&str_xd_resetlibrary);
    if (delay_after != 0) {
      dbg_log((iptr)&str_disconnection_delay_2_seconds);
      ui_delay_ticks(0x78);
    }
  }
  *(i8 *)((int)self + 0x1ec) = 0;
  *(i8 *)((int)self + 0x1ed) = 0;
  *(i8 *)((int)self + 0x1ee) = 0;
  *(i32 *)((int)self + 0x1f8) = 0xffffffff;
  net_reset_error_counts();
  net_msgq_reset((NetMsgQueue *)((int)self + 0x160d0));
  net_popup_queue_clear();
  return;
}

/* 0059b55b auto */
void __thiscall net_session_close_hook_nop(void *self)

{
  return;
}

/* 0059b571 auto */
void __thiscall net_game_list_add(NetSession *self,iptr msg)

{
  int cmp;
  void *entry;
  i32 now_ticks;
  char *prev;
  char *node2;
  i32 saved_value;
  
  if (*(char *)((int)&((NetSessionExt *)self)->session_flags + 2) != '\0') {
    node2 = (char *)((NetSessionExt *)self)->game_list_head;
    saved_value = 0;
    for (; node2 != (char *)0x0; node2 = *(char **)(node2 + 0x20)) {
      cmp = _strncmp(node2,(char *)(msg + 0x74),0x20);
      if (cmp == 0) {
        if ((char *)((NetSessionExt *)self)->game_list_head == node2) {
          ((NetSessionExt *)self)->game_list_head = *(u32 *)(node2 + 0x20);
        }
        if (*(int *)(node2 + 0x24) != 0) {
          *(i32 *)(*(int *)(node2 + 0x24) + 0x20) = *(i32 *)(node2 + 0x20);
        }
        if (*(int *)(node2 + 0x20) != 0) {
          *(i32 *)(*(int *)(node2 + 0x20) + 0x24) = *(i32 *)(node2 + 0x24);
        }
        saved_value = *(i32 *)(node2 + 0x2c);
        operator_delete(node2);
        break;
      }
    }
    node2 = (char *)((NetSessionExt *)self)->game_list_head;
    prev = (char *)0x0;
    while ((node2 != (char *)0x0 &&
           (cmp = __strcmpi((char *)(msg + 0xe4),node2 + 0x70), 0 < cmp))) {
      prev = node2;
      node2 = *(char **)(node2 + 0x20);
    }
    while (((node2 != (char *)0x0 &&
            (cmp = __strcmpi((char *)(msg + 0xe4),node2 + 0x70), cmp == 0)) &&
           (cmp = __strcmpi((char *)(msg + 0x74),node2), 0 < cmp))) {
      prev = node2;
      node2 = *(char **)(node2 + 0x20);
    }
    entry = operator_new(0x124);
    if (entry == (void *)0x0) {
      err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_pcur_null,(iptr)&str_d_ss_franklinton_netmgr_cpp_3,0x1cf);
    }
    crt_memcpy(entry,msg + 0x74,0x124);
    if (prev == (char *)0x0) {
      *(u32 *)((int)entry + 0x20) = ((NetSessionExt *)self)->game_list_head;
      *(i32 *)((int)entry + 0x24) = 0;
      if (((NetSessionExt *)self)->game_list_head != 0) {
        *(void **)(((NetSessionExt *)self)->game_list_head + 0x24) = entry;
      }
      ((NetSessionExt *)self)->game_list_head = (u32)entry;
    }
    else {
      *(i32 *)((int)entry + 0x20) = *(i32 *)(prev + 0x20);
      *(char **)((int)entry + 0x24) = prev;
      *(void **)(prev + 0x20) = entry;
      if (*(int *)((int)entry + 0x20) != 0) {
        *(void **)(*(int *)((int)entry + 0x20) + 0x24) = entry;
      }
    }
    now_ticks = timer_ticks();
    *(i32 *)((int)entry + 0x28) = now_ticks;
    *(i32 *)((int)entry + 0x2c) = saved_value;
  }
  return;
}

/* 0059b7fc auto */
void __thiscall net_add_player(NetSession *self,iptr player_info)

{
  int slot;
  
  slot = 0;
  while( true ) {
    if (6 < slot) {
      return;
    }
    if (*(char *)((int)self + slot * 0x54 + 0x251) == '\0') break;
    slot++;
  }
  *(i32 *)((int)self + slot * 0x54 + 0x204) = *(i32 *)(player_info + 0x10);
  _memset((void *)((int)self + slot * 0x54 + 0x208),0,0x20);
  _strncpy((char *)((int)self + slot * 0x54 + 0x208),(char *)(player_info + 0x14),0x20);
  *(i8 *)((int)self + slot * 0x54 + 0x250) = 0;
  *(i8 *)((int)self + slot * 0x54 + 0x251) = 1;
  *(i32 *)((int)self + slot * 0x54 + 0x254) = 0xffffffff;
  crt_strcpy((int)self + slot * 0x54 + 0x228,player_info + 0x34);
  *(i32 *)((int)self + slot * 0x54 + 0x248) = 0;
  *(i32 *)((int)self + slot * 0x54 + 0x24c) = 0;
  *(int *)((NetSessionExt *)self)->player_slots = *(int *)((NetSessionExt *)self)->player_slots + 1;
  ((NetSessionExt *)self)->open_slot_count--;
  return;
}

/* 0059b96a auto */
void __thiscall net_remove_player(NetSession *self,int player_id)

{
  u8 *civ_slot_ptr;
  int slot;
  
  slot = 0;
  while ((slot < 7 && (*(int *)((int)self + slot * 0x54 + 0x204) != player_id))) {
    slot++;
  }
  if ((slot < 7) && (*(char *)((int)self + slot * 0x54 + 0x251) != '\0')) {
    if ((0 < *(int *)((int)self + slot * 0x54 + 0x254)) &&
       (*(int *)((int)self + slot * 0x54 + 0x254) < 8)) {
      game.human_players =
           ~(byte)(1 << (*(byte *)((int)self + slot * 0x54 + 0x254) & 0x1f)) & game.human_players
      ;
    }
    *(i32 *)((int)self + slot * 0x54 + 0x204) = 0;
    *(i8 *)((int)self + slot * 0x54 + 0x208) = 0;
    *(i8 *)((int)self + slot * 0x54 + 0x250) = 0;
    *(i8 *)((int)self + slot * 0x54 + 0x251) = 0;
    civ_slot_ptr = ((NetSessionExt *)self)->civ_slot_map + *(int *)((int)self + slot * 0x54 + 0x254) * 4;
    civ_slot_ptr[0] = 0xff;
    civ_slot_ptr[1] = 0xff;
    civ_slot_ptr[2] = 0xff;
    civ_slot_ptr[3] = 0xff;
    *(i32 *)((int)self + slot * 0x54 + 0x254) = 0xffffffff;
    *(int *)((NetSessionExt *)self)->player_slots = *(int *)((NetSessionExt *)self)->player_slots - 1;
  }
  return;
}

/* 0059baf0 auto */
void __thiscall net_free_game_list(void *self)

{
  i32 next;
  
  while (*(int *)((int)self + 0x160cc) != 0) {
    next = *(i32 *)(*(int *)((int)self + 0x160cc) + 0x20);
    operator_delete(*(void **)((int)self + 0x160cc));
    *(i32 *)((int)self + 0x160cc) = next;
  }
  return;
}

/* 0059bb54 auto */
void __cdecl net_on_broadcast_receive(int *msg,ushort size)

{
  int cmp;
  
  if (size < 0x10) {
    dbg_log((iptr)&str_broadcastreceivefunc_killed_message_tiny);
  }
  else if (*msg == 0x66606660) {
    if ((msg[1] != 0) ||
       ((((char)msg[0xc] == '\0' ||
         (cmp = _strcmp((char *)(msg + 0xc),((i8 *)&prefs_main_menu_choice_block.prefs_net_ip_address)), cmp == 0)) &&
        (((char)msg[0x14] == '\0' ||
         (cmp = _strcmp((char *)(msg + 0x14),((i8 *)&prefs_main_menu_choice_block.prefs_net_ip_address)), cmp != 0)))))) {
      net_msgq_enqueue((NetMsgQueueEnqueueView *)((i8 *)&net_session_block.net_msg_queue),0,(iptr)msg,(uint)size);
    }
  }
  else {
    dbg_log((iptr)&str_broadcastreceivefunc_killed_message_not);
  }
  return;
}

/* 0059bc41 auto */
void __cdecl net_on_secure_receive(uint conn_id,int *msg,uint size)

{
  size_t len;
  int *scan_ptr;
  uptr byte_idx;
  uptr offset;
  char num_buf[32];
  i8 hex_line[64];
  uint byte_val;
  int *header;
  
  if (3 < size) {
    if (*msg == 0x66606660) {
      net_msgq_enqueue
                ((NetMsgQueueEnqueueView *)((i8 *)&net_session_block.net_msg_queue),conn_id & 0xffff,(iptr)msg,size);
      net_session_block.net_last_recv_callback_size = size;
      net_session_block.net_last_queued_send_seq = net_send_sequence;
      header = msg;
      net_session_block.net_last_recv_msg_size = msg[2];
      net_last_recv_msg_type = msg[1];
    }
    else {
      dbg_log((iptr)&str_securereceivefunc_killed_message_not_civ);
      if (-1 < net_last_recv_msg_type) {
        __ultoa(net_session_block.net_last_recv_callback_size,num_buf,10);
        dbg_logf_str((iptr)&str_last_callback_size_s,(iptr)num_buf);
        __itoa(net_session_block.net_last_queued_send_seq,num_buf,10);
        dbg_logf_str((iptr)&str_last_legal_sequence_number_s,(iptr)num_buf);
        __itoa(net_last_recv_msg_type,num_buf,10);
        dbg_logf_str((iptr)&str_last_legal_type_s,(iptr)num_buf);
        __ultoa(net_session_block.net_last_recv_msg_size,num_buf,10);
        dbg_logf_str((iptr)&str_last_legal_netmsg_size_s,(iptr)num_buf);
      }
      __itoa(net_send_sequence,num_buf,10);
      dbg_logf_str((iptr)&str_sequence_number_s,(iptr)num_buf);
      __ultoa(size,num_buf,10);
      dbg_logf_str((iptr)&str_message_size_s,(iptr)num_buf);
      for (offset = 0; (offset < 0x20 && (hex_line[0] = 0, offset <= size));
          offset = offset + 8) {
        for (byte_idx = offset; (byte_idx < offset + 8 && (byte_idx < size));
            byte_idx = byte_idx + 1) {
          byte_val = (uint)*(byte *)(byte_idx + (int)msg);
          __itoa(byte_val,num_buf,0x10);
          len = _strlen(num_buf);
          if (len == 1) {
            num_buf[1] = num_buf[0];
            num_buf[2] = 0;
            num_buf[0] = '0';
          }
          crt_strcat(hex_line,num_buf);
          crt_strcat(hex_line,((i8 *)&net_hexdump_space_str));
        }
        dbg_logf_str((iptr)&str_s_3,(iptr)hex_line);
      }
      dbg_log((iptr)&str_empty_184);
      net_last_recv_msg_type = -1;
      scan_ptr = msg;
      for (offset = 0; offset < 0x20; offset++) {
        if (*scan_ptr == 0x66606660) {
          header = scan_ptr;
          dbg_log((iptr)&str_potential_offset_message_found);
          __itoa(offset,num_buf,10);
          dbg_logf_str((iptr)&str_offset_s_bytes,(iptr)num_buf);
          dbg_logf_str((iptr)&str_type_s,(iptr)(((char *)&str_nm_datagram) + header[1] * 0x20));
          __ultoa(header[2],num_buf,10);
          dbg_logf_str((iptr)&str_size_s_bytes,(iptr)num_buf);
          __ultoa(header[3],num_buf,10);
          dbg_logf_str((iptr)&str_sequence_number_s_2,(iptr)num_buf);
          break;
        }
        scan_ptr = (int *)((int)scan_ptr + 1);
      }
    }
  }
  if (((300 < net_session_block.net_msgq_normal_count) || (0x21 < net_session_block.net_msgq_priority_count)) && (mp_window_drag_active != '\0')) {
    mp_release_mouse_capture();
  }
  return;
}

/* 0059bfb5 auto */
void __cdecl net_on_new_client(i32 client_info,uint conn_id)

{
  dbg_logf((iptr)&str_newclientreceivefunc_new_client_connecti,conn_id & 0xffff);
  return;
}

/* 0059bfdb auto */
void __cdecl net_on_connected_to_server(short conn_id)

{
  dbg_logf((iptr)&str_connectedtoserverfunc_new_server_connect,(int)conn_id);
  if ((-1 < conn_id) && (conn_id < 8)) {
    net_session_block.net_server_conn_id = (int)conn_id;
    net_session_block.net_connected_to_server = 1;
    net_send_message(0x2f,0,(int)conn_id,0,0,0,0,0,0,0);
  }
  return;
}

/* 0059c04b auto */
void __cdecl net_on_connection_lost(ushort player_id)

{
  dbg_logf((iptr)&str_lostconnectionfunc_connection_to_d_has_s,(uint)player_id);
  net_session_block.net_lost_conn_total++;
  if (player_id < 7) {
    *(int *)(((i8 *)&net_session_block.net_lost_conn_by_player) + (uint)player_id * 4) = *(int *)(((i8 *)&net_session_block.net_lost_conn_by_player) + (uint)player_id * 4) + 1;
  }
  return;
}

/* 0059c0a4 auto */
void __cdecl net_on_oversized_message(i32 size)

{
  char msg_buf[256];
  
  _sprintf(msg_buf,str_oversized_xdaemon_message_ul,size);
  dbg_log((iptr)msg_buf);
  return;
}

/* 0059c0e1 auto */
void * __cdecl
net_msg_build_packet(i32 msg_type,iptr payload,i32 arg1,i32 arg2,
            i32 arg3,i32 arg4,i32 arg5,i32 arg6,
            size_t payload_len)

{
  void *packet;
  NetMsgHeaderExt header;  /* the 16-byte message header */
  size_t payload_size;
  
  net_msg_header_init(&header.base,msg_type);
  if (payload_len == 0) {
    if (payload == 0) {
      payload_size = 0;
      packet = operator_new(0x2c);
    }
    else {
      payload_size = __msize((void *)payload);
      packet = (void *)crt_realloc(payload,payload_size + 0x2c);
      crt_memmove((int)packet + 0x2c,packet,payload_size);
    }
  }
  else {
    payload_size = payload_len;
    packet = operator_new(payload_len + 0x2c);
    crt_memcpy((int)packet + 0x2c,payload,payload_size);
  }
  header.msg_size_2 = payload_size + 0x2c;
  crt_memcpy(packet,&header,0x10);
  crt_memcpy((int)packet + 0x10,&arg1,4);
  crt_memcpy((int)packet + 0x14,&arg2,4);
  crt_memcpy((int)packet + 0x18,&arg3,4);
  crt_memcpy((int)packet + 0x1c,&arg4,4);
  crt_memcpy((int)packet + 0x20,&arg5,4);
  crt_memcpy((int)packet + 0x24,&arg6,4);
  crt_memcpy((int)packet + 0x28,&payload_size,4);
  return packet;
}

/* 0059c276 auto */
void __cdecl net_reset_msg_counts(void)

{
  int i;
  
  for (i = 0; i < 0xa9; i++) {
    *(i32 *)(((i8 *)&net_session_block.nm_recv_counts) + i * 4) = 0;
  }
  return;
}

/* 0059c2b8 auto */
void __cdecl net_reset_error_counts(void)

{
  int i;
  
  net_session_block.net_lost_conn_total = 0;
  for (i = 0; i < 7; i++) {
    *(i32 *)(((i8 *)&net_session_block.net_lost_conn_by_player) + i * 4) = 0;
  }
  return;
}

/* 0059c301 auto */
void __cdecl net_modal_idle_poll(void)

{
  net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
  return;
}

/* 0059c31f auto */
/* WARNING: Type propagation algorithm not settling */

void __cdecl net_fill_game_info(iptr info)

{
  i32 bit_masks[9];
  
  bit_masks[0] = 0;
  bit_masks[1] = 1;
  bit_masks[2] = 3;
  bit_masks[3] = 7;
  bit_masks[4] = 0xf;
  bit_masks[5] = 0x1f;
  bit_masks[6] = 0x3f;
  bit_masks[7] = 0x7f;
  bit_masks[8] = 0xff;
  crt_strcpy(info + 0x30,str_ptr_5_4_0f_multiplayer_26_march_99);
  _memset((void *)info,0,0x20);
  _strncpy((char *)info,((i8 *)&prefs_main_menu_choice_block.prefs_net_ip_address),0x20);
  _memset((void *)(info + 0x70),0,0x20);
  _strncpy((char *)(info + 0x70),((i8 *)&net_session_block.net_game_name),0x20);
  _memset((void *)(info + 0x90),0,0x20);
  _strncpy((char *)(info + 0x90),((i8 *)&prefs_main_menu_choice_block.prefs_net_player_name),0x20);
  *(i16 *)(info + 0xb0) = civ_saved_cursor_x_block.mp_open_game;
  *(u8 *)(info + 0xb2) = game.difficulty;
  *(u8 *)(info + 0xb3) = game.barbarian_activity;
  if (game.civs_alive == '\0') {
    *(i8 *)(info + 0xb4) = *(i8 *)(bit_masks + (uint)game.num_enemies + 2);
  }
  else {
    *(u8 *)(info + 0xb4) = game.civs_alive;
  }
  *(i8 *)(info + 0xb5) = *(i8 *)(bit_masks + net_session_block.net_player_count[0]);
  *(i32 *)(info + 0xb8) = civ_saved_cursor_x_block.mp_turn_time_limit_ms;
  crt_strcpy(info + 0xbc,((i8 *)&prefs_game_rules_block.scenario_name));
  *(i16 *)(info + 0x10c) = civ_saved_cursor_x_block.mp_double_moves;
  *(i16 *)(info + 0x10e) = civ_saved_cursor_x_block.mp_double_production;
  *(u16 *)(info + 0x110) = game.game_flags;
  *(i16 *)(info + 0x112) = game.first_launch_turn;
  *(i16 *)(info + 0x114) = prefs_game_rules_block.scenario_year_increment[0];
  *(i16 *)(info + 0x116) = prefs_game_rules_block.scenario_start_year;
  *(i16 *)(info + 0x118) = game.turn;
  *(i16 *)(info + 0x11e) = civ_saved_cursor_x_block.mp_simultaneous_setting;
  *(i32 *)(info + 0x24) = 0;
  *(i32 *)(info + 0x20) = *(i32 *)(info + 0x24);
  *(i32 *)(info + 0x2c) = 0;
  *(i32 *)(info + 0x28) = *(i32 *)(info + 0x2c);
  *(i16 *)(info + 0x11a) = map.width;
  *(i16 *)(info + 0x11c) = map.height;
  return;
}

/* 0059d080 auto */
NetMsgHeader * __thiscall net_msg_player_info_init(NetMsgHeader *self)

{
  iptr j;
  int i;
  
  net_msg_header_init(self,0x2e);
  ((NetMsgHeaderExt *)self)->player_id = 0;
  ((NetMsgHeaderExt *)self)->ip_address = 0;
  ((NetMsgHeaderExt *)self)->info_word_18 = 0;
  *(i8 *)&((NetMsgHeaderExt *)self)->info_string_20 = 0;
  *(i8 *)&((NetMsgHeaderExt *)self)->info_string_38 = 0;
  *(i8 *)&((NetMsgHeaderExt *)self)->info_string_50 = 0;
  ((NetMsgHeaderExt *)self)->info_trailer_flag = 0;
  for (i = 0; i < 7; i++) {
    for (j = 0; j < 0x18; j++) {
      *(i8 *)((int)&((u32 *)&((NetMsgHeaderExt *)self)->info_string_table)[(i * 3) * 2] + j) = 0;
    }
  }
  ((NetMsgHeaderExt *)self)->info_word_1c = 0;
  ((NetMsgHeaderExt *)self)->info_count_68 = 0;
  ((NetMsgHeaderExt *)self)->msg_size_2 = 0x118;
  return self;
}

/* 005a9f30 auto */
void __cdecl net_host_wait_production_idle(void)

{
  bool all_done;
  int civ;
  
  net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
  if ((net_session_block.nm_production_complete_count != 0) || (net_session_block.net_player_count[0] < 2)) {
    all_done = true;
    for (civ = 1; civ < 8; civ++) {
      if ((((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0) &&
          ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) &&
         (*(int *)(((i8 *)&dialog_text_font_obj_block.net_civ_phase_done) + civ * 4) == 0)) {
        all_done = false;
        break;
      }
    }
    if (all_done) {
      net_session_block.dialog_stack_top[0xf] = net_session_block.dialog_stack_top[0xf] | 0x400;
      wnd_end_modal_loop((ModalMenuWindow *)(*net_session_block.dialog_stack_top + 0x48));
    }
  }
  return;
}

/* 005aa004 auto */
void __cdecl net_host_wait_human_moves_idle(void)

{
  bool all_done;
  int civ;
  
  net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
  if ((net_session_block.nm_human_move_complete_count != 0) || (net_session_block.net_player_count[0] < 2)) {
    all_done = true;
    for (civ = 1; civ < 8; civ++) {
      if ((((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0) &&
          ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) &&
         (*(int *)(((i8 *)&dialog_text_font_obj_block.net_civ_phase_done) + civ * 4) == 0)) {
        all_done = false;
        break;
      }
    }
    if ((all_done) || (net_session_block.net_player_count[0] < 2)) {
      net_session_block.dialog_stack_top[0xf] = net_session_block.dialog_stack_top[0xf] | 0x400;
      wnd_end_modal_loop((ModalMenuWindow *)(*net_session_block.dialog_stack_top + 0x48));
    }
  }
  return;
}

/* 005aa0e5: written by hand in src/game/bigframes.c */

/* 005ab0a3 auto */
void __cdecl net_client_wait_production_idle(void)

{
  net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
  net_heartbeat_check(net_session_block.net_slot_civs[0]);
  if ((((net_session_block.nm_ai_movement_count != 0) || (net_session_block.nm_end_sequence_count != 0)) || (game_loop_active == '\0')) ||
     (net_session_block.net_lost_conn_total != 0)) {
    net_session_block.dialog_stack_top[0xf] = net_session_block.dialog_stack_top[0xf] | 0x400;
    wnd_end_modal_loop((ModalMenuWindow *)(*net_session_block.dialog_stack_top + 0x48));
  }
  return;
}

/* 005ab120 auto */
void __cdecl net_client_wait_ai_moves_idle(void)

{
  net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
  net_heartbeat_check(net_session_block.net_slot_civs[0]);
  if ((((net_session_block.nm_human_movement_count != 0) || (net_session_block.nm_end_sequence_count != 0)) || (game_loop_active == '\0')) ||
     (net_session_block.net_lost_conn_total != 0)) {
    net_session_block.dialog_stack_top[0xf] = net_session_block.dialog_stack_top[0xf] | 0x400;
    wnd_end_modal_loop((ModalMenuWindow *)(*net_session_block.dialog_stack_top + 0x48));
  }
  return;
}

/* 005ab19d auto */
void __cdecl net_client_wait_human_moves_idle(void)

{
  net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
  net_heartbeat_check(net_session_block.net_slot_civs[0]);
  if ((((net_session_block.nm_production_begin_count != 0) || (net_session_block.net_host_handoff_stage == 1)) || (net_session_block.nm_end_sequence_count != 0)) ||
     (((net_session_block.player_has_quit == 1 || (game_loop_active == '\0')) || (net_session_block.net_lost_conn_total != 0)))) {
    net_session_block.dialog_stack_top[0xf] = net_session_block.dialog_stack_top[0xf] | 0x400;
    wnd_end_modal_loop((ModalMenuWindow *)(*net_session_block.dialog_stack_top + 0x48));
  }
  return;
}

/* 005ab23a auto */
void __cdecl net_client_hotwait_idle(void)

{
  net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
  net_heartbeat_check(net_session_block.net_slot_civs[0]);
  if ((((net_session_block.nm_production_begin_count != 0) || (net_session_block.net_host_handoff_stage != '\0')) || (net_session_block.nm_end_sequence_count != 0)) ||
     (((net_session_block.player_has_quit != '\0' || (game_loop_active == '\0')) || (net_session_block.net_lost_conn_total != 0)))) {
    net_session_block.dialog_stack_top[0xf] = net_session_block.dialog_stack_top[0xf] | 0x400;
    wnd_end_modal_loop((ModalMenuWindow *)(*net_session_block.dialog_stack_top + 0x48));
  }
  return;
}

/* 005ab2d5 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __cdecl net_client_turn_loop(void)

{
  char resume_civ;
  SHORT esc_state;
  iptr str;
  int status;
  i32 ret;
  iptr slot_civ;
  int civ;
  iptr unit;
  Dialog dialog2;
  i8 turn_ok;
  int centered;
  int new_casualties;
  int is_first_turn;
  i32 seh_frame;
  i8 *seh_handler;
  i32 seh_state;
  
  seh_state = 0xffffffff;
  is_first_turn = 1;
  dialog_ctor(&dialog2,0x4000);
  seh_state = 0;
  turn_ok = 1;
  slot_civ = net_session_block.net_slot_civs[0];
  str = civ_name_plural(net_session_block.net_slot_civs[0]);
  dbg_logf_str_int((iptr)&str_server_s_d_4,str,slot_civ);
  for (civ = 1; civ < 8; civ++) {
    if (((*(int *)(((i8 *)&net_session_block.net_player_slots) + *(int *)(((i8 *)&net_session_block.net_civ_slots) + civ * 4) * 0x54) != 0) &&
        ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0)) &&
       ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) {
      status = civ;
      str = civ_name_plural(civ);
      dbg_logf_str_int((iptr)&str_client_s_d_4,str,status);
    }
  }
  net_reset_error_counts();
  human_civ[0] = (((i32 *)&net_session_block.net_slot_civs))[net_session_block.net_local_slot * 0x15];
  turn_resume_civ = civ_saved_cursor_x_block.saved_turn_civ;
  turn_resume_new_game = (int)civ_saved_cursor_x_block.saved_resume_new_game;
  picwnd_close((PictureWindowCore *)((i8 *)&advisor_window_block.advisor_window));
  picwnd_close((PictureWindowCore *)((i8 *)&casualty_window_block.casualty_window));
  menu_update_states();
  game.player_civ = (byte)human_civ[0];
  game.turn_civ = (byte)human_civ[0];
  mapview_update_title((FrameWindow *)((i8 *)&map_views_block.map_views));
  centered = 0;
  for (unit = 0; unit < game.num_units; unit++) {
    if ((units[unit].id != 0) && (units[unit].owner == human_civ[0])) {
      mapview_center_on
                ((ViewWindow *)((i8 *)&map_views_block.map_views),(int)units[unit].x,(int)units[unit].y);
      centered++;
      break;
    }
  }
  if (centered == 0) {
    for (unit = 0; unit < game.num_cities; unit++) {
      if ((cities[unit].id != 0) && (cities[unit].owner == human_civ[0])) {
        mapview_center_on
                  ((ViewWindow *)((i8 *)&map_views_block.map_views),(int)cities[unit].x,(int)cities[unit].y
                  );
        break;
      }
    }
  }
  status_draw_info(1);
  status_draw_civ_color(human_civ[0]);
  ui_redraw_all_maps(1);
  resume_civ = turn_resume_civ;
  if ((1 << ((byte)human_civ[0] & 0x1f) & (uint)game.human_players) == 0) {
    net_heartbeat_send(net_session_block.net_slot_civs[0]);
    dlg_pending_idle_callback = ((i8*)(net_client_hotwait_idle));
    popup_game_sprite_flags((iptr)&str_clienthotwait_2,0x2000000,(iptr)&popup_info_icon_sprite,0);
    resume_civ = turn_resume_civ;
  }
turn_loop:
  do {
    turn_resume_civ = resume_civ;
    for (unit = 0; unit < game.num_units; unit++) {
      if ((units[unit].id != 0) && (units[unit].owner == human_civ[0])) {
        unit_exhaust_moves(unit);
      }
    }
    if (is_first_turn == 0) {
      net_heartbeat_send(net_session_block.net_slot_civs[0]);
      dlg_pending_idle_callback = ((i8*)(net_client_wait_human_moves_idle));
      popup_game_with_sprite((iptr)&str_waithumanmoves_2,(iptr)&popup_info_icon_sprite,0);
    }
    net_heartbeat_send(net_session_block.net_slot_civs[0]);
    while ((((net_session_block.nm_production_begin_count == 0 && (net_session_block.net_host_handoff_stage == '\0')) && (net_session_block.nm_end_sequence_count == 0)) &&
           ((net_session_block.player_has_quit == '\0' && (game_loop_active != '\0'))))) {
      net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
      net_heartbeat_check(net_session_block.net_slot_civs[0]);
      status = net_check_lost_connections();
      if (status != 0) {
        seh_state = 0xffffffff;
        /* inlined unwind funclet 005abfdb */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
        ret = 0;
        goto return_ret;
      }
    }
    if (net_session_block.net_host_handoff_stage != '\0') {
      status = net_client_transfer_server();
      if (status == 0) {
        seh_state = 0xffffffff;
        /* inlined unwind funclet 005abfdb */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
        ret = 0;
        goto return_ret;
      }
      if (net_session_block.net_host_flag != '\0') {
        seh_state = 0xffffffff;
        /* inlined unwind funclet 005abfdb */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
        ret = 1;
        goto return_ret;
      }
      if (((net_session_block.nm_production_begin_count == 0) && (net_session_block.nm_end_sequence_count == 0)) &&
         ((net_session_block.player_has_quit == '\0' && (resume_civ = turn_resume_civ, game_loop_active != '\0'))))
      goto turn_loop;
    }
    if ((net_session_block.nm_end_sequence_count == 0) && (game_loop_active != '\0')) {
      net_session_block.nm_start_civ_count = 0;
      net_session_block.nm_production_begin_count = 0;
      human_civ[0] = (((i32 *)&net_session_block.net_slot_civs))[net_session_block.net_local_slot * 0x15];
      game.player_civ = (byte)human_civ[0];
      game.turn_civ = (byte)human_civ[0];
      if (civ_saved_cursor_x_block.mp_turn_time_limit_ms != 0) {
        mp_turn_seconds_left = civ_saved_cursor_x_block.mp_turn_time_limit_ms / 1000;
        map_views_block.main_view_timer_cache_i32 = 0xffffffff;
      }
      while ((net_session_block.net_msgq_priority_count != 0 || (net_session_block.net_msgq_normal_count != 0))) {
        net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
      }
      net_session_block.mp_turn_civ = human_civ[0];
      mapview_update_title((FrameWindow *)((i8 *)&map_views_block.map_views));
      map_redraw_all_views(human_civ[0],1);
      status_draw_info(1);
      status_draw_civ_color(human_civ[0]);
      if (civ_saved_cursor_x_block.autoplay_active == 0) {
        if (turn_resume_civ == '\0') {
          civ_check_throne_room_upgrade();
        }
        if ((turn_resume_civ == '\0') || (turn_resume_new_game != 0)) {
          civ_process_turn(human_civ[0]);
          net_send_state_diff(0xff,2,0,0,0);
        }
        XD_FlushSendBuffer(60000);
        game_turn_start_popups();
        net_send_message(0x8c,0,human_civ[0],0,0,0,0,0,0,0);
        net_heartbeat_send(net_session_block.net_slot_civs[0]);
        dlg_pending_idle_callback = ((i8*)(net_client_wait_production_idle));
        popup_game_with_sprite((iptr)&str_waitproduction_3,(iptr)&popup_info_icon_sprite,0);
        while (((net_session_block.nm_ai_movement_count == 0 && (net_session_block.nm_end_sequence_count == 0)) && (game_loop_active != '\0'))) {
          net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
          net_heartbeat_check(net_session_block.net_slot_civs[0]);
          status = net_check_lost_connections();
          if (status != 0) {
            seh_state = 0xffffffff;
            /* inlined unwind funclet 005abfdb */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
            ret = 0;
            goto return_ret;
          }
        }
        if ((net_session_block.nm_end_sequence_count == 0) && (game_loop_active != '\0')) {
          net_session_block.nm_ai_movement_count = 0;
          net_heartbeat_send(net_session_block.net_slot_civs[0]);
          dlg_pending_idle_callback = ((i8*)(net_client_wait_ai_moves_idle));
          popup_game_with_sprite((iptr)&str_waitaimoves,(iptr)&popup_info_icon_sprite,0);
          while (((net_session_block.nm_human_movement_count == 0 && (net_session_block.nm_end_sequence_count == 0)) && (game_loop_active != '\0'))) {
            net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
            net_heartbeat_check(net_session_block.net_slot_civs[0]);
            status = net_check_lost_connections();
            if (status != 0) {
              seh_state = 0xffffffff;
              /* inlined unwind funclet 005abfdb */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
              ret = 0;
              goto return_ret;
            }
          }
          if ((net_session_block.nm_end_sequence_count == 0) && (game_loop_active != '\0')) {
            net_session_block.nm_human_movement_count = 0;
            if ((*(short *)(((i8 *)&civ_saved_cursor_x_block.civ_intro_shown) + human_civ[0] * 2) == 0) && (civ_saved_cursor_x_block.autoplay_active == 0)) {
              civ_intro_popup(human_civ[0]);
              *(i16 *)(((i8 *)&civ_saved_cursor_x_block.civ_intro_shown) + human_civ[0] * 2) = 1;
            }
            new_casualties = *(int *)(((i8 *)&net_session_block.casualty_counts) + human_civ[0] * 4) -
                       *(int *)(((i8 *)&net_session_block.casualty_reported_counts) + human_civ[0] * 4);
            if (civ_saved_cursor_x_block.autoplay_active == 0) {
              dlg_pending_idle_callback = ((i8*)(turn_popup_timeout_idle));
              str = civ_leader_title(human_civ[0]);
              text_set_string_arg(0,str);
              str = civ_leader_name(human_civ[0]);
              text_set_string_arg(1,str);
              if (new_casualties < 1) {
                dialog_load_text_noflags(&dialog2,(iptr)&str_game_7,(iptr)&str_ourturntomove_4);
                dialog_add_sprite((DialogOptionList *)&dialog2,(iptr)&popup_info_icon_sprite,0,0);
                dialog_set_image_zoom((DialogWindowView *)&dialog2,0);
                input_flush_events();
                snd_play_effect(0x30,0,0,0);
                dlg_show_modal(&dialog2,0);
              }
              else {
                *(i32 *)(((i8 *)&net_session_block.casualty_reported_counts) + human_civ[0] * 4) =
                     *(i32 *)(((i8 *)&net_session_block.casualty_counts) + human_civ[0] * 4);
                text_set_number_arg(0,new_casualties);
                if (new_casualties == 1) {
                  dialog_load_text_noflags(&dialog2,(iptr)&str_game_7,(iptr)&str_casualty_5);
                }
                else {
                  dialog_load_text_noflags(&dialog2,(iptr)&str_game_7,(iptr)&str_casualties_5);
                }
                dialog_add_sprite((DialogOptionList *)&dialog2,(iptr)&popup_info_icon_sprite,0,0);
                dialog_set_image_zoom((DialogWindowView *)&dialog2,0);
                input_flush_events();
                snd_play_effect(0x30,0,0,0);
                dlg_show_modal(&dialog2,0);
                if (dialog2.result_extra != 0) {
                  casualty_timeline_show(human_civ[0]);
                }
              }
            }
            if (civ_saved_cursor_x_block.mp_turn_time_limit_ms != 0) {
              mp_turn_timer_start(1);
            }
            game_player_move_loop();
          }
          else {
            net_session_block.nm_end_sequence_count = 0;
          }
        }
        else {
          turn_ok = 0;
        }
      }
      else {
        map_views_block.saved_human_players = (uint)game.human_players;
        game.human_players = '\0';
        if ((turn_resume_civ == '\0') || (turn_resume_new_game != 0)) {
          civ_process_turn(human_civ[0]);
        }
        net_send_message(0x8c,0,human_civ[0],0,0,0,0,0,0,0);
        net_heartbeat_send(net_session_block.net_slot_civs[0]);
        dlg_pending_idle_callback = ((i8*)(net_client_wait_production_idle));
        popup_game_with_sprite((iptr)&str_waitproduction_2,(iptr)&popup_info_icon_sprite,0);
        while (((net_session_block.nm_ai_movement_count == 0 && (net_session_block.nm_end_sequence_count == 0)) && (game_loop_active != '\0'))) {
          net_process_messages((NetSession *)((iptr *)&net_session_block.net_session),1,0);
          net_heartbeat_check(net_session_block.net_slot_civs[0]);
          status = net_check_lost_connections();
          if (status != 0) {
            seh_state = 0xffffffff;
            /* inlined unwind funclet 005abfdb */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
            ret = 0;
            goto return_ret;
          }
        }
        if ((net_session_block.nm_end_sequence_count == 0) && (game_loop_active != '\0')) {
          net_session_block.nm_ai_movement_count = 0;
          if (civ_saved_cursor_x_block.mp_turn_time_limit_ms != 0) {
            mp_turn_timer_start(1);
          }
          ai_process_civ_units();
          game.human_players = (*(u8 *)&map_views_block.saved_human_players);
          esc_state = GetAsyncKeyState(0x1b);
          if (((int)esc_state & 0x8001U) != 0) {
            civ_saved_cursor_x_block.autoplay_turns_left = 1;
          }
        }
        else {
          turn_ok = 0;
        }
      }
    }
    else {
      turn_ok = 0;
    }
    mp_turn_timer_stop(1);
    status_redraw(1);
    ui_pump_messages();
    if (game_over_reason != 0) {
      game_loop_active = '\0';
    }
    net_send_state_diff(0xff,2,0,0,0);
    net_send_message(0x8f,0,human_civ[0],0,0,0,0,0,0,0);
    XD_FlushSendBuffer(60000);
    civ_saved_cursor_x_block.saved_turn_civ = '\0';
    turn_resume_civ = '\0';
    civ_saved_cursor_x_block.saved_resume_new_game = 0;
    turn_resume_new_game = 0;
    is_first_turn = 0;
    resume_civ = '\0';
    if (game_loop_active == '\0') {
      net_send_message(0x2d,0,human_civ[0],0,0,0,0,0,0,0);
      XD_FlushSendBuffer(60000);
      net_session_shutdown(((iptr *)&net_session_block.net_session),1);
      if (game_over_reason != 0) {
        game_handle_game_over();
      }
      seh_state = 0xffffffff;
      /* inlined unwind funclet 005abfdb */ { dialog_dtor((Dialog *)((iptr)&dialog2)); }
      ret = 0;
return_ret:
      return ret;
    }
  } while( true );
}

/* 005b9ec6 auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl net_batch_begin(void)

{
  if (2 < game.multiplayer) {
    net_session_block.net_tile_sync_enabled = 0;
    net_session_block.net_tile_batch_active = 1;
    _memset(((i8 *)&net_batch_buffer),0,0x400);
    net_batch_buffer[0] = 0;
    net_batch_used_dwords = 1;
  }
  return;
}

/* 005b9f1c auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl net_batch_flush(void)

{
  if (2 < game.multiplayer) {
    net_session_block.net_tile_sync_enabled = 1;
    net_session_block.net_tile_batch_active = 0;
    if (net_session_block.net_host_flag == '\0') {
      if (1 < net_batch_used_dwords) {
        net_send_message(0x59,0,0,0,0,0,0,0,0,0);
        XD_FlushSendBuffer(5000);
        _memset(((i8 *)&net_batch_buffer),0,0x400);
        net_batch_buffer[0] = 0;
        net_batch_used_dwords = 1;
      }
    }
    else {
      net_send_state_diff(0xff,2,0,0,0);
      XD_FlushSendBuffer(5000);
    }
  }
  return;
}

/* 005b9fde auto */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl
net_batch_add(int record_type,i32 x,i32 y,i32 arg1,iptr arg2,
            i32 arg3)

{
  if (net_session_block.net_host_flag != '\0') {
    err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_gnetmgr_bserver_3,(iptr)&str_d_ss_franklinton_map_cpp,0x3de);
  }
  if (0x100 - net_batch_used_dwords < *(int *)(((i8 *)&net_batch_record_sizes) + record_type * 4) + 1) {
    net_send_message(0x59,0,0,0,0,0,0,0,0,0);
    XD_FlushSendBuffer(5000);
    _memset(((i8 *)&net_batch_buffer),0,0x400);
    net_batch_buffer[0] = 0;
    net_batch_used_dwords = 1;
  }
  net_batch_buffer[0]++;
  *(int *)(((i8 *)&net_batch_buffer) + net_batch_used_dwords * 4) = record_type;
  net_batch_used_dwords++;
  switch(record_type) {
  case 0:
  case 2:
    *(i32 *)(((i8 *)&net_batch_buffer) + net_batch_used_dwords * 4) = x;
    net_batch_used_dwords++;
    *(i32 *)(((i8 *)&net_batch_buffer) + net_batch_used_dwords * 4) = y;
    net_batch_used_dwords++;
    *(i32 *)(((i8 *)&net_batch_buffer) + net_batch_used_dwords * 4) = arg1;
    net_batch_used_dwords++;
    *(iptr *)(((i8 *)&net_batch_buffer) + net_batch_used_dwords * 4) = arg2;
    net_batch_used_dwords++;
    break;
  case 1:
  case 3:
  case 4:
  case 5:
  case 6:
    *(i32 *)(((i8 *)&net_batch_buffer) + net_batch_used_dwords * 4) = x;
    net_batch_used_dwords++;
    *(i32 *)(((i8 *)&net_batch_buffer) + net_batch_used_dwords * 4) = y;
    net_batch_used_dwords++;
    *(i32 *)(((i8 *)&net_batch_buffer) + net_batch_used_dwords * 4) = arg1;
    net_batch_used_dwords++;
    break;
  case 7:
    *(i32 *)(((i8 *)&net_batch_buffer) + net_batch_used_dwords * 4) = x;
    net_batch_used_dwords++;
    *(i32 *)(((i8 *)&net_batch_buffer) + net_batch_used_dwords * 4) = y;
    net_batch_used_dwords++;
    *(i32 *)(((i8 *)&net_batch_buffer) + net_batch_used_dwords * 4) = arg1;
    net_batch_used_dwords++;
    *(iptr *)(((i8 *)&net_batch_buffer) + net_batch_used_dwords * 4) = arg2;
    net_batch_used_dwords++;
    *(i32 *)(((i8 *)&net_batch_buffer) + net_batch_used_dwords * 4) = arg3;
    net_batch_used_dwords++;
  }
  return;
}

/* 005ba206 auto */
void __cdecl net_apply_tile_updates(iptr batch)

{
  int record_type;
  i8 saved_sync;
  iptr count_offset;
  int records_left;
  iptr arg_idx;
  iptr args[5];
  int pos;
  
  pos = 0;
  if (2 < game.multiplayer) {
    if (net_session_block.net_host_flag == '\0') {
      err_report((ErrorContext *)((i8 *)&err_report_ctx_block.err_report_ctx),7,(iptr)&str_gnetmgr_bserver_4,(iptr)&str_d_ss_franklinton_map_cpp_2,0x416);
    }
    saved_sync = net_session_block.net_tile_sync_enabled;
    net_session_block.net_tile_sync_enabled = 0;
    count_offset = pos * 4;
    pos++;
    for (records_left = *(int *)(batch + count_offset); 0 < records_left; records_left--) {
      record_type = *(int *)(batch + pos * 4);
      for (arg_idx = 0; pos = pos + 1, arg_idx < *(int *)(((i8 *)&net_batch_record_sizes) + record_type * 4) - 1;
          arg_idx = arg_idx + 1) {
        args[arg_idx] = *(iptr *)(batch + pos * 4);
      }
      switch(record_type) {
      case 0:
        tile_set_improvements(args[0],args[1],args[2],args[3],1);
        break;
      case 1:
        tile_set_terrain(args[0],args[1],args[2],1);
        break;
      case 2:
        tile_set_visible(args[0],args[1],args[2],args[3],1);
        break;
      case 3:
        tile_set_fertility(args[0],args[1],args[2],1);
        break;
      case 4:
        tile_set_owner(args[0],args[1],args[2],1);
        break;
      case 5:
        tile_set_landmass(args[0],args[1],args[2],1);
        break;
      case 6:
        tile_set_radius_civ(args[0],args[1],args[2],1);
        break;
      case 7:
        known_set(args[0],args[1],args[2],args[3],args[4],1);
      }
    }
    net_session_block.net_tile_sync_enabled = saved_sync;
    net_send_state_diff(0xff,2,0,0,0);
  }
  return;
}
