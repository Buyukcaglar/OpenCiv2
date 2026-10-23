/* The game, multiplayer: network sessions, negotiation, lobby and chat: functions translated from the original
 * (tools/gen_c.py, now edited directly), in address order. */
#include "auto_common.h"

/* 00421f40 auto */
i8 __thiscall net_is_host(void *this)

{
  return *(i8 *)((int)this + 0x1ef);
}

/* 00421f70 auto */
NetGamelistViewCtorView * __thiscall net_gamelist_view_ctor(NetGamelistViewCtorView *this)

{
  this->next_game_id = 1;
  this->option_list = 0;
  this->refresh_timer = 0;
  return this;
}

/* 00421fad auto */
void __thiscall net_gamelist_view_dtor(void *this)

{
  net_free_game_list(&net_session);
  return;
}

/* 00421fcd: written by hand in src/native/crt.c */

/* 0042415c auto */
void __cdecl net_gamelist_poll_idle(void)

{
  net_process_messages((NetSession *)&net_session,1,0);
  return;
}

/* 0042417a auto */
#define dialog_stack_top (*(int * *)((u8 *)&g.d_006ad678))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl net_join_wait_server_idle(void)

{
  timer_ticks();
  net_process_messages((NetSession *)&net_session,1,0);
  if ((((nm_player_list_count != 0) || (nm_server_canceled_count != 0)) || (nm_server_reject_count != 0)) || (nm_server_full_count != 0))
  {
    dialog_stack_top[0xf] = dialog_stack_top[0xf] | 0x400;
    wnd_end_modal_loop((ModalMenuWindow *)(*dialog_stack_top + 0x48));
  }
  return;
}
#undef dialog_stack_top

/* 004241f8 auto */
#define dialog_stack_top (*(Dialog * *)((u8 *)&g.d_006ad678))
#define net_wait_start_ticks_i32 (*(i32 *)((u8 *)&g.d_006ad674))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl net_join_wait_gamestate_idle(void)

{
  int iVar1;
  size_t sVar2;
  char *pcVar3;
  char *pcVar4;
  
  iVar1 = timer_ticks();
  iVar1 -= net_wait_start_ticks_i32;
  net_process_messages((NetSession *)&net_session,1,0);
  if ((nm_join_gamestate_count == 0) && (nm_server_canceled_count == 0)) {
    if (2 < iVar1) {
      pcVar4 = *(char **)(*(int *)(dialog_stack_top->field_230 + 0x1c) + 8);
      sVar2 = _strlen(pcVar4);
      pcVar3 = _strchr(pcVar4,0x3e);
      if (pcVar4 + (sVar2 - 1) == pcVar3) {
        *pcVar3 = '<';
      }
      else {
        *pcVar3 = '-';
        pcVar3[1] = '>';
      }
      pcVar3 = _strchr(pcVar4,0x3c);
      if (pcVar3 == (char *)0x0) {
        pcVar4 = _strchr(pcVar4,0x3e);
        pcVar4[-1] = '<';
      }
      else if (pcVar3 == pcVar4) {
        *pcVar3 = '>';
      }
      else {
        *pcVar3 = '-';
        pcVar3[-1] = '<';
      }
      dialog_render(dialog_stack_top);
      net_wait_start_ticks_i32 = timer_ticks();
    }
  }
  else {
    dialog_stack_top->field_3c = dialog_stack_top->field_3c | 0x400;
    wnd_end_modal_loop((ModalMenuWindow *)(dialog_stack_top->field_0 + 0x48));
  }
  return;
}
#undef dialog_stack_top
#undef net_wait_start_ticks_i32

/* 0042433c auto */
#define dialog_stack_top (*(int * *)((u8 *)&g.d_006ad678))
void __cdecl net_join_wait_player_list_idle(void)

{
  net_process_messages((NetSession *)&net_session,1,0);
  if (((nm_player_list_count != 0) || (nm_server_canceled_count != 0)) || (nm_lost_server_on_join_count != 0)) {
    dialog_stack_top[0xf] = dialog_stack_top[0xf] | 0x400;
    wnd_end_modal_loop((ModalMenuWindow *)(*dialog_stack_top + 0x48));
  }
  return;
}
#undef dialog_stack_top

/* 0042439c auto */
#define dialog_stack_top (*(int * *)((u8 *)&g.d_006ad678))
#define nm_start_civ_count (*(int *)((u8 *)&g.d_006c9038))
void __cdecl net_join_wait_start_civ_idle(void)

{
  net_process_messages((NetSession *)&net_session,1,0);
  if ((nm_start_civ_count != 0) || (nm_server_canceled_count != 0)) {
    dialog_stack_top[0xf] = dialog_stack_top[0xf] | 0x400;
    wnd_end_modal_loop((ModalMenuWindow *)(*dialog_stack_top + 0x48));
  }
  return;
}
#undef dialog_stack_top
#undef nm_start_civ_count

/* 004243ef auto */
#define dialog_stack_top (*(int * *)((u8 *)&g.d_006ad678))
void __cdecl net_join_wait_answer_idle(void)

{
  net_process_messages((NetSession *)&net_session,1,0);
  if (((nm_server_answer_count != 0) || (nm_server_canceled_count != 0)) || (nm_server_reject_count != 0)) {
    dialog_stack_top[0xf] = dialog_stack_top[0xf] | 0x400;
    wnd_end_modal_loop((ModalMenuWindow *)(*dialog_stack_top + 0x48));
  }
  return;
}
#undef dialog_stack_top

/* 0042444f auto */
#define dialog_stack_top (*(int * *)((u8 *)&g.d_006ad678))
#define net_server_conn_id (*(int *)((u8 *)&g.d_006ad300))
#define net_wait_start_ticks_i32 (*(i32 *)((u8 *)&g.d_006ad674))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl net_join_wait_idle_cb(void)

{
  int iVar1;
  
  iVar1 = timer_ticks();
  iVar1 -= net_wait_start_ticks_i32;
  net_process_messages((NetSession *)&net_session,1,0);
  if ((net_server_conn_id == -1) && (0x4d8 < iVar1)) {
    dialog_stack_top[0xf] = dialog_stack_top[0xf] | 0x400;
    wnd_end_modal_loop((ModalMenuWindow *)(*dialog_stack_top + 0x48));
  }
  else if (net_server_conn_id != -1) {
    dialog_stack_top[0xf] = dialog_stack_top[0xf] | 0x400;
    wnd_end_modal_loop((ModalMenuWindow *)(*dialog_stack_top + 0x48));
  }
  return;
}
#undef dialog_stack_top
#undef net_server_conn_id
#undef net_wait_start_ticks_i32

/* 004244e0 auto */
void __thiscall net_gamelist_restore_selection(NetGameListRefreshView *this)

{
  int iVar1;
  i32 uVar2;
  int iVar3;
  int iVar4;
  iptr iVar5;
  
  iVar1 = dialog_count_group_options((DialogOptionList *)this->field_0,0);
  scrollbar_set_range(*(Control **)(this->field_0 + 0x284),0,iVar1 - 1);
  uVar2 = net_gamelist_find_option(this,(iptr)&this->field_8,(iptr)&this->field_28);
  *(i32 *)(this->field_0 + 0x220) = uVar2;
  if (iVar1 < 0xb) {
    *(u32 *)(this->field_0 + 0x210) = this->field_14c;
  }
  else {
    uVar2 = net_gamelist_find_option(this,(iptr)&this->field_48,(iptr)&this->field_68);
    *(i32 *)(this->field_0 + 0x210) = uVar2;
  }
  if (*(int *)(this->field_0 + 0x1b8) != 0) {
    iVar3 = dialog_option_group_index
                      ((DialogOptionList *)this->field_0,*(uptr *)(this->field_0 + 0x210));
    iVar1 = *(int *)(this->field_0 + 0x5c);
    iVar4 = dialog_option_group_index
                      ((DialogOptionList *)this->field_0,*(uptr *)(this->field_0 + 0x220));
    if (iVar1 + iVar3 <= iVar4) {
      iVar1 = dialog_option_group_index
                        ((DialogOptionList *)this->field_0,*(uptr *)(this->field_0 + 0x220));
      uVar2 = dialog_option_at
                        ((DialogOptionList *)this->field_0,
                         (iVar1 - *(int *)(this->field_0 + 0x5c)) + 1);
      *(i32 *)(this->field_0 + 0x210) = uVar2;
    }
    iVar1 = dialog_option_group_index
                      ((DialogOptionList *)this->field_0,*(uptr *)(this->field_0 + 0x210));
    iVar3 = dialog_option_group_index
                      ((DialogOptionList *)this->field_0,*(uptr *)(this->field_0 + 0x220));
    if (iVar3 < iVar1) {
      *(i32 *)(this->field_0 + 0x210) = *(i32 *)(this->field_0 + 0x220);
    }
  }
  iVar5 = dialog_option_group_index
                    ((DialogOptionList *)this->field_0,*(uptr *)(this->field_0 + 0x210));
  scrollbar_set_pos(*(ClickControl **)(this->field_0 + 0x284),iVar5);
  return;
}

/* 00424688 auto */
#define local_c (*(uptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(8)))
u32 __thiscall net_gamelist_find_option(NetGameListRefreshView *this,iptr param_1,iptr param_2)

{
  int iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = this->field_14c;
  local_8 = net_found_games;
  while( true ) {
    if (local_8 == 0) {
      return this->field_14c;
    }
    iVar1 = _strcmp((char *)(local_8 + 0x70),(char *)param_1);
    if ((iVar1 == 0) && (iVar1 = _strcmp((char *)(local_8 + 0x90),(char *)param_2), iVar1 == 0))
    break;
    local_c = *(uptr *)(local_c + 0x10);
    local_8 = *(iptr *)(local_8 + 0x20);
  }
  return local_c;
}
#undef local_c
#undef local_8

/* 0042472a auto */
void __thiscall net_gamelist_update_details(NetGameList *this)

{
  if (net_found_games == 0) {
    this->field_8 = '\0';
    this->field_28 = '\0';
    this->field_48 = '\0';
    this->field_68 = '\0';
  }
  else {
    net_gamelist_get_entry_names(this,*(iptr *)(this->field_0 + 0x220),(iptr)&this->field_8,
                       (iptr)&this->field_28);
    net_gamelist_get_entry_names(this,*(iptr *)(this->field_0 + 0x210),(iptr)&this->field_48,
                       (iptr)&this->field_68);
  }
  return;
}

/* 004247b2 auto */
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(8)))
void __thiscall net_gamelist_get_entry_names(NetGameList *this,iptr param_1,iptr param_2,iptr param_3)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = net_found_games;
      (local_8 != 0 && (*(int *)(param_1 + 4) != *(int *)(local_8 + 0x2c)));
      local_8 = *(iptr *)(local_8 + 0x20)) {
  }
  if (local_8 == 0) {
    local_8 = net_found_games;
    for (local_c = dialog_option_group_index((DialogOptionList *)this->field_0,param_1);
        (*(int *)(local_8 + 0x20) != 0 && (local_c != 0)); local_c--) {
      local_8 = *(iptr *)(local_8 + 0x20);
    }
  }
  crt_strcpy(param_2,local_8 + 0x70);
  crt_strcpy(param_3,local_8 + 0x90);
  return;
}
#undef local_c
#undef local_8

/* 0042486f auto */
void __thiscall net_gamelist_add_info_lines(NetGamelistAddInfoLinesView *this)

{
  int iVar1;
  u32 *puVar2;
  int iVar3;
  
  dialog_compute_layout((DialogOptionList *)this->dialog);
  iVar1 = *(int *)(this->dialog + 0xd0) + *(int *)(this->dialog + 0xb8) + 2;
  puVar2 = (u32 *)dialog_add_line
                            ((DialogAddLineView *)this->dialog,ADDR(0x625d14, ((u8 *)&g.d_00625d14)),0xe6,iVar1,0x80,0);
  this->line_0 = *puVar2;
  iVar3 = font_line_spacing(*(GameFont **)(this->dialog + 8));
  iVar1 += iVar3;
  puVar2 = (u32 *)dialog_add_line
                            ((DialogAddLineView *)this->dialog,ADDR(0x625d18, ((u8 *)&g.d_00625d18)),0xe6,iVar1,0x80,0);
  this->line_1 = *puVar2;
  iVar3 = font_line_spacing(*(GameFont **)(this->dialog + 8));
  iVar1 += iVar3;
  puVar2 = (u32 *)dialog_add_line
                            ((DialogAddLineView *)this->dialog,ADDR(0x625d1c, ((u8 *)&g.d_00625d1c)),0xe6,iVar1,0x80,0);
  this->line_2 = *puVar2;
  iVar3 = font_line_spacing(*(GameFont **)(this->dialog + 8));
  iVar1 += iVar3;
  puVar2 = (u32 *)dialog_add_line
                            ((DialogAddLineView *)this->dialog,ADDR(0x625d20, ((u8 *)&g.d_00625d20)),0xe6,iVar1,0x80,0);
  this->line_3 = *puVar2;
  iVar3 = font_line_spacing(*(GameFont **)(this->dialog + 8));
  iVar1 += iVar3;
  puVar2 = (u32 *)dialog_add_line
                            ((DialogAddLineView *)this->dialog,ADDR(0x625d24, ((u8 *)&g.d_00625d24)),0xe6,iVar1,0x80,0);
  this->line_4 = *puVar2;
  iVar3 = font_line_spacing(*(GameFont **)(this->dialog + 8));
  iVar1 += iVar3;
  puVar2 = (u32 *)dialog_add_line
                            ((DialogAddLineView *)this->dialog,ADDR(0x625d28, ((u8 *)&g.d_00625d28)),0xe6,iVar1,0x80,0);
  this->line_5 = *puVar2;
  iVar3 = font_line_spacing(*(GameFont **)(this->dialog + 8));
  iVar1 += iVar3;
  puVar2 = (u32 *)dialog_add_line
                            ((DialogAddLineView *)this->dialog,ADDR(0x625d2c, ((u8 *)&g.d_00625d2c)),0xe6,iVar1,0x80,0);
  this->line_6 = *puVar2;
  iVar3 = font_line_spacing(*(GameFont **)(this->dialog + 8));
  iVar1 += iVar3;
  puVar2 = (u32 *)dialog_add_line
                            ((DialogAddLineView *)this->dialog,ADDR(0x625d30, ((u8 *)&g.d_00625d30)),0xe6,iVar1,0x80,0);
  this->line_7 = *puVar2;
  iVar3 = font_line_spacing(*(GameFont **)(this->dialog + 8));
  puVar2 = (u32 *)dialog_add_line
                            ((DialogAddLineView *)this->dialog,ADDR(0x625d34, ((u8 *)&g.d_00625d34)),0xe6,iVar1 + iVar3,0x80,0);
  this->line_8 = *puVar2;
  font_line_spacing(*(GameFont **)(this->dialog + 8));
  return;
}

/* 00424ae9 auto */
#define scenario_start_year (*(i16 *)((u8 *)&g.d_0064bcb6))
#define scenario_year_increment (*(i16 *)((u8 *)&g.d_0064bcb4))
#define local_118 (*(uint *)(frame_ + FRAME_OFF(0)))
#define local_114 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_110 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_108 (*(char (*)[21])(frame_ + FRAME_OFF(16)))
#define local_f3 (*(i8 *)(frame_ + FRAME_OFF(37)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(272)))
i32 __cdecl net_gamelist_show_game_info(void *param_1,i32 param_2)

{
  size_t sVar1;
  i32 uVar2;
  int iVar3;
  int iVar4;
  iptr iVar5;
  i8 frame_[FRAME_OFF(280)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = net_found_games;
  if (net_found_games == 0) {
    dialog_set_item_text(param_1,*(i32 *)(net_session + 0x128),ADDR(0x625d48, ((u8 *)&g.d_00625d48)));
    dialog_set_item_text(param_1,*(i32 *)(net_session + 300),ADDR(0x625d4c, ((u8 *)&g.d_00625d4c)));
    dialog_set_item_text(param_1,*(i32 *)(net_session + 0x130),ADDR(0x625d50, ((u8 *)&g.d_00625d50)));
    dialog_set_item_text(param_1,*(i32 *)(net_session + 0x134),ADDR(0x625d54, ((u8 *)&g.d_00625d54)));
    dialog_set_item_text(param_1,*(i32 *)(net_session + 0x138),ADDR(0x625d58, ((u8 *)&g.d_00625d58)));
    dialog_set_item_text(param_1,*(i32 *)(net_session + 0x13c),ADDR(0x625d5c, ((u8 *)&g.d_00625d5c)));
    dialog_set_item_text(param_1,*(i32 *)(net_session + 0x140),ADDR(0x625d60, ((u8 *)&g.d_00625d60)));
    dialog_set_item_text(param_1,*(i32 *)(net_session + 0x144),ADDR(0x625d64, ((u8 *)&g.d_00625d64)));
    dialog_set_item_text(param_1,*(i32 *)(net_session + 0x148),ADDR(0x625d68, ((u8 *)&g.d_00625d68)));
  }
  else {
    for (; (local_8 != 0 &&
           (*(int *)(local_8 + 0x2c) != *(int *)(*(int *)(*(int *)net_session + 0x220) + 4)));
        local_8 = *(iptr *)(local_8 + 0x20)) {
    }
    if (local_8 != 0) {
      str_clear((iptr)local_108);
      str_append_label((iptr)local_108,0x26f);
      str_append_space((iptr)local_108);
      crt_strcat(local_108,local_8 + 0x70);
      str_append_space((iptr)local_108);
      str_append_lparen((iptr)local_108);
      str_append_label((iptr)local_108,(*(short *)(local_8 + 0xb0) == 0) + 0x277);
      str_append_rparen((iptr)local_108);
      dialog_set_item_text(param_1,*(i32 *)(net_session + 0x128),(iptr)local_108);
      str_clear((iptr)local_108);
      str_append_label((iptr)local_108,0x270);
      str_append_space((iptr)local_108);
      crt_strcat(local_108,local_8 + 0x90);
      dialog_set_item_text(param_1,*(i32 *)(net_session + 300),(iptr)local_108);
      str_clear((iptr)local_108);
      sVar1 = _strlen((char *)(local_8 + 0xbc));
      if (sVar1 == 0) {
        str_append_label((iptr)local_108,0x34c);
      }
      else {
        crt_strcpy(local_108,local_8 + 0xbc);
      }
      sVar1 = _strlen(local_108);
      if (0x19 < sVar1) {
        local_f3 = 0;
      }
      str_append_space((iptr)local_108);
      str_append_lparen((iptr)local_108);
      game.game_flags = *(u16 *)(local_8 + 0x110);
      game.first_launch_turn = *(i16 *)(local_8 + 0x112);
      scenario_year_increment = *(i16 *)(local_8 + 0x114);
      scenario_start_year = *(i16 *)(local_8 + 0x116);
      game.difficulty = *(u8 *)(local_8 + 0xb2);
      uVar2 = game_turn_to_year((int)*(short *)(local_8 + 0x118));
      str_append_year((iptr)local_108,uVar2);
      str_append_rparen((iptr)local_108);
      dialog_set_item_text(param_1,*(i32 *)(net_session + 0x130),(iptr)local_108);
      str_clear((iptr)local_108);
      str_append_label((iptr)local_108,*(byte *)(local_8 + 0xb2) + 0x279);
      str_append_space((iptr)local_108);
      str_append_lparen((iptr)local_108);
      str_append_label((iptr)local_108,0x34e - (uint)(*(short *)(local_8 + 0x11e) == 0));
      str_append_rparen((iptr)local_108);
      dialog_set_item_text(param_1,*(i32 *)(net_session + 0x134),(iptr)local_108);
      str_clear((iptr)local_108);
      str_append_label((iptr)local_108,0x36c);
      str_append_space((iptr)local_108);
      str_append_int((iptr)local_108,(int)*(short *)(local_8 + 0x11a) / 2);
      crt_strcat(local_108,&gamelist_map_size_sep_str);
      str_append_int((iptr)local_108,(int)*(short *)(local_8 + 0x11c));
      dialog_set_item_text(param_1,*(i32 *)(net_session + 0x138),(iptr)local_108);
      str_clear((iptr)local_108);
      str_append_label((iptr)local_108,0x350 - (uint)(*(short *)(local_8 + 0x10e) == 0));
      crt_strcat(local_108,&gamelist_double_opts_sep_str);
      str_append_label((iptr)local_108,0x352 - (uint)(*(short *)(local_8 + 0x10c) == 0));
      dialog_set_item_text(param_1,*(i32 *)(net_session + 0x13c),(iptr)local_108);
      str_clear((iptr)local_108);
      str_append_label((iptr)local_108,0x273);
      str_append_space((iptr)local_108);
      str_append_label((iptr)local_108,*(byte *)(local_8 + 0xb3) + 0x27f);
      dialog_set_item_text(param_1,*(i32 *)(net_session + 0x140),(iptr)local_108);
      str_clear((iptr)local_108);
      str_append_label((iptr)local_108,0x276);
      str_append_space((iptr)local_108);
      if (*(int *)(local_8 + 0xb8) == 0) {
        str_append_label((iptr)local_108,0x285);
      }
      else {
        iVar3 = *(int *)(local_8 + 0xb8) / 1000;
        iVar4 = iVar3 / 0x3c;
        iVar3 = iVar3 % 0x3c;
        if (iVar4 < 10) {
          str_append_int((iptr)local_108,0);
        }
        str_append_int((iptr)local_108,iVar4);
        crt_strcat(local_108,&gamelist_timer_colon_str);
        if (iVar3 < 10) {
          str_append_int((iptr)local_108,0);
        }
        str_append_int((iptr)local_108,iVar3);
      }
      dialog_set_item_text(param_1,*(i32 *)(net_session + 0x144),(iptr)local_108);
      local_110 = 1;
      local_114 = 0;
      local_118 = (uint)*(byte *)(local_8 + 0xb4);
      for (; local_118 = (int)local_118 >> 1, local_110 < 8; local_110++) {
        if ((local_118 & 1) != 0) {
          local_114++;
        }
      }
      str_clear((iptr)local_108);
      str_append_label((iptr)local_108,0x274);
      str_append_space((iptr)local_108);
      str_append_int((iptr)local_108,local_114);
      crt_strcat(local_108,&gamelist_open_paren_str);
      str_append_label((iptr)local_108,0x275);
      str_append_space((iptr)local_108);
      local_110 = 0;
      local_114 = 0;
      local_118 = (uint)*(byte *)(local_8 + 0xb5);
      for (; local_110 < 8; local_110++) {
        if ((local_118 & 1) != 0) {
          local_114++;
        }
        local_118 = (int)local_118 >> 1;
      }
      if ((*(short *)(local_8 + 0x120) < 3) || (local_114 == 0)) {
        str_append_label((iptr)local_108,0x353);
      }
      else {
        str_append_int((iptr)local_108,local_114);
      }
      str_append_rparen((iptr)local_108);
      dialog_set_item_text(param_1,*(i32 *)(net_session + 0x148),(iptr)local_108);
    }
  }
  iVar5 = dialog_option_group_index
                    (*(DialogOptionList **)net_session,*(uptr *)(*(int *)net_session + 0x210));
  scrollbar_set_pos(*(ClickControl **)(*(int *)net_session + 0x284),iVar5);
  dialog_render(*(Dialog **)net_session);
  return 1;
}
#undef scenario_start_year
#undef scenario_year_increment
#undef local_118
#undef local_114
#undef local_110
#undef local_108
#undef local_f3
#undef local_8

/* 004253ef auto */
#define local_c (*(void * *)(frame_ + FRAME_OFF(4)))
void __thiscall net_gamelist_clear(NetGameList *this)

{
  void *pvVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = (void *)this->field_14c;
  net_gamelist_update_details(this);
  while (local_c != (void *)0x0) {
    pvVar1 = *(void **)((int)local_c + 0x10);
    operator_delete(*(void **)((int)local_c + 8));
    operator_delete(local_c);
    local_c = pvVar1;
  }
  this->field_14c = 0;
  *(i32 *)(this->field_0 + 0x28) = 0;
  *(i32 *)(this->field_0 + 0x228) = 0;
  *(i32 *)(this->field_0 + 0x220) = 0;
  return;
}
#undef local_c

/* 004254a8 auto */
#define local_10 (*(uptr *)(frame_ + FRAME_OFF(0)))
#define local_c (*(uptr *)(frame_ + FRAME_OFF(4)))
uint * __thiscall net_gamelist_add_entry(NetGameListAddView *this,iptr param_1,uint param_2)

{
  int *piVar1;
  uint *puVar2;
  size_t sVar3;
  void *pvVar4;
  int iVar5;
  int iVar6;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_10 = 0;
  for (local_c = this->field_14c; local_c != 0; local_c = *(uptr *)(local_c + 0x10)) {
    local_10 = local_c;
  }
  puVar2 = operator_new(0x18);
  puVar2[4] = 0;
  puVar2[5] = local_10;
  if (local_10 == 0) {
    this->field_14c = (u32)puVar2;
    *(uint **)(this->field_0 + 0x228) = puVar2;
  }
  else {
    *(uint **)(local_10 + 0x10) = puVar2;
  }
  *puVar2 = 0;
  sVar3 = _strlen((char *)param_1);
  pvVar4 = operator_new(sVar3 + 1);
  puVar2[2] = (uint)pvVar4;
  crt_strcpy(puVar2[2],param_1);
  if (*(char *)param_1 == '\0') {
    *puVar2 = *puVar2 | 1;
  }
  puVar2[1] = param_2;
  puVar2[3] = 0;
  iVar5 = font_text_width(*(GameFont **)(this->field_0 + 8),puVar2[2]);
  iVar6 = dialog_option_icon_width((DialogCore *)this->field_0);
  iVar5 = iVar5 + iVar6 + *(int *)(this->field_0 + 0xac) + 5;
  iVar6 = *(int *)(this->field_0 + 0x118);
  if (iVar6 <= iVar5) {
    iVar6 = iVar5;
  }
  *(int *)(this->field_0 + 0x118) = iVar6;
  piVar1 = (int *)(this->field_0 + 0x28);
  *piVar1 = *piVar1 + 1;
  return puVar2;
}
#undef local_10
#undef local_c

/* 00425607 auto */
void __thiscall net_gamelist_start_timer(NetGameListTimerView *this,iptr param_1)

{
  u32 uVar1;
  
  if (this->refresh_timer != 0) {
    net_gamelist_kill_timer(this);
  }
  uVar1 = game_timer_create(param_1,0x32,1);
  this->refresh_timer = uVar1;
  return;
}

/* 00425650 auto */
void __thiscall net_gamelist_kill_timer(NetGameListTimerView *this)

{
  if (this->refresh_timer != 0) {
    game_timer_destroy(this->refresh_timer);
    this->refresh_timer = 0;
  }
  return;
}

/* 00425695 auto */
void __cdecl net_gamelist_poll_tick(void)

{
  i32 uVar1;
  
  net_send_message(1,0,0,0,0,0,0,0,0,0);
  net_gamelist_expire_stale();
  if (*(int *)(net_session + 0x174) != 0) {
    game_timer_destroy(*(i32 *)(net_session + 0x174));
  }
  uVar1 = game_timer_create(ADDR(0x40130c, net_gamelist_poll_tick),0xfa,1);
  *(i32 *)(net_session + 0x174) = uVar1;
  return;
}

/* 0042570c auto */
#define net_timeout_seconds (*(int *)((u8 *)&g.d_006ad8b8))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(4)))
void __cdecl net_gamelist_expire_stale(void)

{
  bool bVar1;
  int iVar2;
  iptr iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  bVar1 = false;
  local_c = net_found_games;
  iVar2 = timer_ticks();
  while (local_c != 0) {
    if (net_timeout_seconds * 0x3c < iVar2 - *(int *)(local_c + 0x28)) {
      if (net_found_games == local_c) {
        net_found_games = *(iptr *)(local_c + 0x20);
      }
      if (*(int *)(local_c + 0x24) != 0) {
        *(i32 *)(*(int *)(local_c + 0x24) + 0x20) = *(i32 *)(local_c + 0x20);
      }
      if (*(int *)(local_c + 0x20) != 0) {
        *(i32 *)(*(int *)(local_c + 0x20) + 0x24) = *(i32 *)(local_c + 0x24);
      }
      iVar1 = *(iptr *)(local_c + 0x20);
      operator_delete((void *)local_c);
      bVar1 = true;
      local_c = iVar1;
    }
    else {
      local_c = *(iptr *)(local_c + 0x20);
    }
  }
  if (bVar1) {
    net_gamelist_refresh();
  }
  return;
}
#undef net_timeout_seconds
#undef local_c

/* 004257fe auto */
#define net_max_players (*(int *)((u8 *)&g.d_006c3164))
#define local_1c (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(i32 *)(frame_ + FRAME_OFF(8)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(16)))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(24)))
void __cdecl net_gamelist_refresh(void)

{
  uint *puVar1;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (net_session != 0) {
    net_gamelist_clear((NetGameList *)net_session);
    if (net_found_games == 0) {
      text_clear();
      text_append_label(0x286);
      net_gamelist_add_entry((NetGameListAddView *)net_session,ADDR(0x679640, ((u8 *)&g.d_00679640)),0);
      net_gamelist_update_details((NetGameList *)net_session);
    }
    else {
      for (local_c = net_found_games; local_c != 0; local_c = *(iptr *)(local_c + 0x20)) {
        if (*(int *)(local_c + 0x2c) == 0) {
          *(i32 *)(local_c + 0x2c) = *(i32 *)(net_session + 4);
          *(int *)(net_session + 4) = *(int *)(net_session + 4) + 1;
        }
        puVar1 = (uint *)net_gamelist_add_entry
                                   ((NetGameListAddView *)net_session,local_c + 0x70,
                                    *(i32 *)(local_c + 0x2c));
        local_18 = 0;
        local_10 = 0;
        local_1c = (uint)*(byte *)(local_c + 0xb4);
        for (; local_18 < 8; local_18++) {
          if ((local_1c & 1) != 0) {
            local_10++;
          }
          local_1c = (int)local_1c >> 1;
        }
        local_18 = 0;
        local_8 = 0;
        local_1c = (uint)*(byte *)(local_c + 0xb5);
        for (; local_18 < 8; local_18++) {
          if ((local_1c & 1) != 0) {
            local_8++;
          }
          local_1c = (int)local_1c >> 1;
        }
        if (((net_max_players <= local_8) || (local_10 <= local_8)) ||
           (*(short *)(local_c + 0xb0) == 0)) {
          *puVar1 = *puVar1 | 1;
        }
      }
    }
    net_gamelist_restore_selection((NetGameListRefreshView *)net_session);
    net_gamelist_show_game_info(*(i32 *)net_session,0);
  }
  return;
}
#undef net_max_players
#undef local_1c
#undef local_18
#undef local_10
#undef local_c
#undef local_8

/* 00430822 auto */
#define dialog_stack_top (*(int * *)((u8 *)&g.d_006ad678))
#define mp_meeting_reply (*(int *)((u8 *)&g.d_0063f278))
#define net_timeout_seconds (*(int *)((u8 *)&g.d_006ad8b8))
#define nm_parley_cancel_count (*(int *)((u8 *)&g.d_006c91e4))
#define mp_meeting_wait_start_i32 (*(i32 *)((u8 *)&g.d_0063e4e8))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl mp_meeting_wait_idle(void)

{
  int iVar1;
  
  net_process_messages((NetSession *)&net_session,1,0);
  iVar1 = timer_ticks();
  if (((net_timeout_seconds * 0x3c <= iVar1 - mp_meeting_wait_start_i32) || (mp_meeting_reply != -1)) ||
     (nm_parley_cancel_count != 0)) {
    dialog_stack_top[0xf] = dialog_stack_top[0xf] | 0x400;
    wnd_end_modal_loop((ModalMenuWindow *)(*dialog_stack_top + 0x48));
    if (mp_meeting_reply == -1) {
      mp_meeting_reply = 0;
    }
  }
  return;
}
#undef dialog_stack_top
#undef mp_meeting_reply
#undef net_timeout_seconds
#undef nm_parley_cancel_count
#undef mp_meeting_wait_start_i32

/* 0044528e auto */
#define net_adapter_index (*(uint *)((u8 *)&g.d_006ad2fc))
#define net_protocol (*(int *)((u8 *)&g.d_006ad2f8))
#define prefs_net_ip_address (*(i8 *)((u8 *)&g.d_006665b0))
#define local_40c (*(char (*)[260])(frame_ + FRAME_OFF(4)))
#define local_308 (*(Dialog *)(frame_ + FRAME_OFF(264)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(1020)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1024)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1028)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1032)))
i32 __cdecl net_prompt_ip_address(void)

{
  char *pcVar1;
  size_t sVar2;
  i32 uVar3;
  i8 frame_[FRAME_OFF(1040)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_308,0x4000);
  local_8 = 0;
  if ((net_lobby_launch_mode == -1) || (net_lobby_launch_mode == 1)) {
    pcVar1 = XD_GetCurrentProtoAddr(net_adapter_index,net_protocol);
    if (pcVar1 == (char *)0x0) {
      do {
        dialog_load_text_section(&local_308,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x6265b8, ((u8 *)&g.d_006265b8)),0x1f,ADDR(0x6665b0, ((u8 *)&g.d_006665b0)),0,0,0,1);
        local_14 = dialog_run_modal(&local_308,(iptr)local_40c,0);
        if (local_14 == -1) {
          local_8 = 0xffffffff;
          /* inlined unwind funclet 00445407 */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
          uVar3 = 0;
          goto LAB_0044541d;
        }
        sVar2 = _strlen(local_40c);
      } while (sVar2 == 0);
      crt_strcpy(&prefs_net_ip_address,local_40c);
    }
    else {
      pcVar1 = XD_GetCurrentProtoAddr(net_adapter_index,net_protocol);
      crt_strcpy(&prefs_net_ip_address,pcVar1);
    }
  }
  else {
    crt_strcpy(&prefs_net_ip_address,&net_lobby_launch_info);
  }
  local_8 = 0xffffffff;
  /* inlined unwind funclet 00445407 */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
  uVar3 = 1;
LAB_0044541d:
  return uVar3;
}
#undef net_adapter_index
#undef net_protocol
#undef prefs_net_ip_address
#undef local_40c
#undef local_308
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0044542c auto */
#define prefs_net_player_name (*(i8 *)((u8 *)&g.d_00666570))
#define local_40c (*(char (*)[260])(frame_ + FRAME_OFF(4)))
#define local_308 (*(Dialog *)(frame_ + FRAME_OFF(264)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(1020)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1024)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1028)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1032)))
i32 __cdecl net_prompt_player_name(void)

{
  size_t sVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(1040)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_308,0x4000);
  local_8 = 0;
  if (net_lobby_launch_mode == -1) {
    do {
      dialog_load_text_section(&local_308,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x6265c4, ((u8 *)&g.d_006265c4)),0x1f,ADDR(0x666570, ((u8 *)&g.d_00666570)),0,0,0,1);
      local_14 = dialog_run_modal(&local_308,(iptr)local_40c,0);
      if (local_14 == -1) {
        local_8 = 0xffffffff;
        /* inlined unwind funclet 0044556d */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
        uVar2 = 0;
        goto LAB_00445583;
      }
      sVar1 = _strlen(local_40c);
    } while (sVar1 == 0);
    crt_strcpy(&prefs_net_player_name,local_40c);
    prefs_save_civ2dat();
  }
  else {
    _memset(&prefs_net_player_name,0,0x20);
    _strncpy(&prefs_net_player_name,&net_lobby_short_name,0x1f);
  }
  local_8 = 0xffffffff;
  /* inlined unwind funclet 0044556d */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
  uVar2 = 1;
LAB_00445583:
  return uVar2;
}
#undef prefs_net_player_name
#undef local_40c
#undef local_308
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00445592 auto */
#define prefs_net_game_name (*(i8 *)((u8 *)&g.d_00666550))
#define local_40c (*(char (*)[260])(frame_ + FRAME_OFF(4)))
#define local_308 (*(Dialog *)(frame_ + FRAME_OFF(264)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(1020)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1024)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1028)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1032)))
i32 __cdecl net_prompt_game_name(void)

{
  size_t sVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(1040)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_308,0x4000);
  local_8 = 0;
  if (net_lobby_launch_mode == -1) {
    do {
      dialog_load_text_section(&local_308,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x6265cc, ((u8 *)&g.d_006265cc)),0x1f,ADDR(0x666550, ((u8 *)&g.d_00666550)),0,0,0,1);
      local_14 = dialog_run_modal(&local_308,(iptr)local_40c,0);
      if (local_14 == -1) {
        local_8 = 0xffffffff;
        /* inlined unwind funclet 004456ed */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
        uVar2 = 0;
        goto LAB_00445703;
      }
      sVar1 = _strlen(local_40c);
    } while (sVar1 == 0);
    crt_strcpy(&prefs_net_game_name,local_40c);
    crt_strcpy(&net_game_name,local_40c);
    prefs_save_civ2dat();
  }
  else {
    _memset(&prefs_net_game_name,0,0x20);
    _strncpy(&prefs_net_game_name,&net_lobby_session_name,0x1f);
  }
  local_8 = 0xffffffff;
  /* inlined unwind funclet 004456ed */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
  uVar2 = 1;
LAB_00445703:
  return uVar2;
}
#undef prefs_net_game_name
#undef local_40c
#undef local_308
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00445e46 auto */
#define dlg_pending_idle_callback (*(i8 * *)((u8 *)&g.d_00635a3c))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define net_claimed_civs_mask (*(short *)((u8 *)&g.d_00654fb0))
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define net_timeout_seconds (*(int *)((u8 *)&g.d_006ad8b8))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define net_player_info_civ_i32 (*(i32 *)((u8 *)&g.d_006ad120))
#define net_player_info_gender_i32 (*(i32 *)((u8 *)&g.d_006ad128))
#define net_player_info_has_names_i32 (*(i32 *)((u8 *)&g.d_006ad12c))
#define net_player_info_has_titles_i32 (*(i32 *)((u8 *)&g.d_006ad178))
#define net_wait_start_ticks_i32 (*(i32 *)((u8 *)&g.d_006ad674))
#define civ (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_444 (*(u8 *)(frame_ + FRAME_OFF(4)))
#define local_440 (*(i8 (*)[260])(frame_ + FRAME_OFF(8)))
#define local_33c (*(int *)(frame_ + FRAME_OFF(268)))
#define local_338 (*(int *)(frame_ + FRAME_OFF(272)))
#define local_334 (*(int *)(frame_ + FRAME_OFF(276)))
#define local_330 (*(iptr *)(frame_ + FRAME_OFF(280)))
#define local_32c (*(Dialog *)(frame_ + FRAME_OFF(284)))
#define local_38 (*(byte * *)(frame_ + FRAME_OFF(1040)))
#define aiStack_34 (*(iptr (*)[8])(frame_ + FRAME_OFF(1044)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(1076)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1080)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1084)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1088)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __cdecl net_choose_civ_dialog(int param_1)

{
  iptr civ2;
  iptr iVar3;
  int iVar2;
  iptr iVar4;
  i32 uVar5;
  i32 uVar6;
  i32 uVar7;
  i32 uVar8;
  i8 frame_[FRAME_OFF(1096)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_32c,0x4000);
  local_8 = 0;
  local_330 = 0;
  net_player_info_has_names_i32 = 0;
  net_player_info_has_titles_i32 = 0;
  do {
    dlg_reset(&local_32c,0x801);
    dialog_prepend_title_label((iptr)&local_32c,param_1 + 0x25e);
    local_33c = 0;
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
        text_append(ADDR(0x62660c, ((u8 *)&g.d_0062660c)));
        text_append_int((int)civs[civ].num_military_units);
        text_append_space();
        text_append_label(0xc4);
        text_append(ADDR(0x626610, ((u8 *)&g.d_00626610)));
        iVar2 = local_33c;
        local_33c++;
        local_38 = (byte *)dialog_add_option
                                     ((DialogOptionList *)&local_32c,ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar2,0);
        aiStack_34[*(int *)(local_38 + 4)] = civ;
      }
    }
    local_334 = local_33c;
LAB_00446036:
    do {
      local_338 = 0;
      for (local_33c = 0; local_33c < local_334; local_33c++) {
        local_38 = (byte *)dialog_find_option
                                     ((DialogOptionList *)&local_32c,local_33c);
        if (local_38 != (byte *)0x0) {
          (*(i8 *)((char *)&civ + 0)) = (byte)aiStack_34[*(int *)(local_38 + 4)];
          if (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0) &&
             ((1 << ((byte)civ & 0x1f) & (int)net_claimed_civs_mask) == 0)) {
            local_338++;
            dialog_set_option_disabled
                      ((DialogOptionList *)&local_32c,*(iptr *)(local_38 + 4),0);
            if ((RadioGroupDisableView *)local_32c.field_268 != (RadioGroupDisableView *)0x0) {
              radiogrp_enable_item
                        ((RadioGroupEnableView *)local_32c.field_268,*(iptr *)(local_38 + 4));
            }
          }
          else {
            dialog_set_option_disabled
                      ((DialogOptionList *)&local_32c,*(iptr *)(local_38 + 4),1);
            if ((RadioGroupDisableView *)local_32c.field_268 != (RadioGroupDisableView *)0x0) {
              radiogrp_disable_item
                        ((RadioGroupDisableView *)local_32c.field_268,*(iptr *)(local_38 + 4));
            }
          }
        }
      }
      if (local_338 == 0) {
        popup_game(ADDR(0x626614, ((u8 *)&g.d_00626614)));
        dialog_close(&local_32c);
        local_8 = 0xffffffff;
        /* inlined unwind funclet 004467fa */ { dialog_dtor((Dialog *)((iptr)&local_32c)); }
        uVar5 = 1;
        goto LAB_00446810;
      }
      for (local_33c = 0; local_33c < local_334; local_33c++) {
        local_38 = (byte *)dialog_find_option
                                     ((DialogOptionList *)&local_32c,local_330);
        if ((local_38 != (byte *)0x0) && ((*local_38 & 1) == 0)) {
          dialog_set_default_choice((DialogOptionList *)&local_32c,*(iptr *)(local_38 + 4));
          if ((RadioGroupDisableView *)local_32c.field_268 != (RadioGroupDisableView *)0x0) {
            radiogrp_set_selected
                      ((RadioGroupSetSelView *)local_32c.field_268,*(i32 *)(local_38 + 4));
          }
          break;
        }
        local_330++;
        if (local_330 == local_334) {
          local_330 = 0;
        }
      }
      net_reset_msg_counts();
      net_wait_start_ticks_i32 = timer_ticks();
      local_32c.field_3c = local_32c.field_3c & 0xfffffbff;
      local_32c.field_d8 = 0;
      local_32c.field_dc = 0;
      dlg_pending_idle_callback = ((void *)ADDR(0x0040126c, net_lock_wait_idle_cb));
      iVar3 = dlg_show_modal(&local_32c,0);
      local_330 = radiogrp_get_selected((RadioGroupGetSelView *)local_32c.field_268);
      if (iVar3 < 0) {
        local_8 = 0xffffffff;
        /* inlined unwind funclet 004467fa */ { dialog_dtor((Dialog *)((iptr)&local_32c)); }
        uVar5 = 1;
        goto LAB_00446810;
      }
    } while (nm_lock_data_count != 0);
    if (nm_server_canceled_count != 0) {
      popup_game_with_sprite(ADDR(0x626620, ((u8 *)&g.d_00626620)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      local_8 = 0xffffffff;
      /* inlined unwind funclet 004467fa */ { dialog_dtor((Dialog *)((iptr)&local_32c)); }
      uVar5 = 1;
      goto LAB_00446810;
    }
    civ2 = aiStack_34[iVar3];
    net_player_info_civ_i32 = civ2;
    local_330 = iVar3;
    net_send_message(0x30,0,0,civ2,0,0,0,0,0,0);
    if (net_host_flag == '\0') {
      net_reset_msg_counts();
      local_14 = timer_ticks();
      while (((nm_nation_accept_count == 0 && (nm_nation_reject_count == 0)) &&
             (iVar2 = timer_ticks(), iVar2 - local_14 < net_timeout_seconds * 0x3c))) {
        net_process_messages((NetSession *)&net_session,1,0);
      }
    }
    if ((nm_nation_accept_count == 0) && (nm_nation_reject_count == 0)) {
      dialog_close(&local_32c);
      popup_game_with_sprite(ADDR(0x626630, ((u8 *)&g.d_00626630)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      local_8 = 0xffffffff;
      /* inlined unwind funclet 004467fa */ { dialog_dtor((Dialog *)((iptr)&local_32c)); }
      uVar5 = 1;
      goto LAB_00446810;
    }
    if (nm_nation_reject_count != 0) {
      popup_game_with_sprite(ADDR(0x626644, ((u8 *)&g.d_00626644)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      goto LAB_00446036;
    }
    dialog_close(&local_32c);
    (*(i8 *)((char *)&civ + 0)) = (byte)civ2;
    game.human_players = game.human_players | (byte)(1 << ((byte)civ & 0x1f));
    game.player_civ = (byte)civ;
    game.turn_civ = (byte)civ;
    game.game_options = game.game_options & 0xfffffeff;
    human_civ = civ2;
    iVar2 = civ_check_password(civ2);
    if (iVar2 == 0) {
      game.human_players = game.human_players & ~(byte)(1 << ((byte)civ & 0x1f));
      net_send_message(0x31,0,0,civ2,0,0,0,0,0,0);
    }
    else {
      dlg_load_game_section(&local_32c,ADDR(0x626654, ((u8 *)&g.d_00626654)),1);
      dialog_prepend_title_label((iptr)&local_32c,param_1 + 0x25e);
      dialog_set_default_choice
                ((DialogOptionList *)&local_32c,(uint)leaders[civs[game.player_civ].tribe].female);
      dialog_set_position
                ((DialogCore *)&local_32c,0xfffffc19,
                 -(((int)(screen_height - 0x1e0 + (screen_height - 0x1e0 >> 0x1f & 7U)) >> 3) + 1));
      dlg_pending_idle_callback = ((void *)ADDR(0x00402c3e, net_pump_idle_cb));
      iVar2 = dlg_show_modal(&local_32c,0);
      net_player_info_gender_i32 = iVar2;
      snd_play_effect(0x6a,0,0,0);
      if (iVar2 < 0) {
        game.human_players = game.human_players & ~(byte)(1 << ((byte)civ & 0x1f));
        net_send_message(0x31,0,0,civ2,0,0,0,0,0,0);
      }
      else {
        local_444 = (u8)iVar2;
        leaders[civs[game.player_civ].tribe].female = local_444;
        civs[human_civ].flags = civs[human_civ].flags & 0xfdff;
        if (iVar2 != 0) {
          civs[human_civ].flags = civs[human_civ].flags | 0x200;
        }
        uVar8 = 1;
        uVar7 = 0;
        uVar6 = 0;
        uVar5 = 0;
        iVar4 = civ_leader_name((int)game.player_civ);
        iVar2 = dialog_load_text_section
                          (&local_32c,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x62665c, ((u8 *)&g.d_0062665c)),0x17,iVar4,uVar5,uVar6,uVar7,uVar8);
        if (iVar2 == 0) {
          dialog_prepend_title_label((iptr)&local_32c,param_1 + 0x25e);
          dlg_pending_idle_callback = ((void *)ADDR(0x00402c3e, net_pump_idle_cb));
          iVar2 = dialog_run_modal(&local_32c,(iptr)local_440,0);
          if (iVar2 == 0) {
            crt_strcpy((iptr)&civ_names[game.player_civ].leader_name,local_440);
            crt_strcpy(&net_player_info_leader_name,local_440);
            net_player_info_tribe_name = 0;
            net_player_info_adjective = 0;
            local_8 = 0xffffffff;
            /* inlined unwind funclet 004467fa */ { dialog_dtor((Dialog *)((iptr)&local_32c)); }
            uVar5 = 0;
LAB_00446810:
            return uVar5;
          }
          game.human_players = game.human_players & ~(byte)(1 << ((byte)civ & 0x1f));
          net_send_message(0x31,0,0,civ2,0,0,0,0,0,0);
        }
      }
    }
  } while( true );
}
#undef dlg_pending_idle_callback
#undef human_civ
#undef net_claimed_civs_mask
#undef net_host_flag
#undef net_timeout_seconds
#undef screen_height
#undef net_player_info_civ_i32
#undef net_player_info_gender_i32
#undef net_player_info_has_names_i32
#undef net_player_info_has_titles_i32
#undef net_wait_start_ticks_i32
#undef civ
#undef local_444
#undef local_440
#undef local_33c
#undef local_338
#undef local_334
#undef local_330
#undef local_32c
#undef local_38
#undef aiStack_34
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00447170 auto */
void * __thiscall net_gamelist_view_scalar_dtor(void *this,uint param_1)

{
  net_gamelist_view_dtor(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 004471c0 auto */
LobbyList * __thiscall lobby_list_scalar_dtor(LobbyList *this,uint param_1)

{
  lobby_list_dtor(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}

/* 00450480 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define parley_other_civ (*(int *)((u8 *)&g.d_0067a8c0))
#define local_44 (*(WindowObjectView * *)(frame_ + FRAME_OFF(4)))
#define local_40 (*(WindowObjectView * *)(frame_ + FRAME_OFF(8)))
#define local_3c (*(u32 *)(frame_ + FRAME_OFF(12)))
#define local_34 (*(u32 *)(frame_ + FRAME_OFF(20)))
#define advance (*(uptr *)(frame_ + FRAME_OFF(28)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_24 (*(i32 *)(frame_ + FRAME_OFF(36)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_1c (*(i32 *)(frame_ + FRAME_OFF(44)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(48)))
#define civ (*(iptr *)(frame_ + FRAME_OFF(52)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(56)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(60)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(64)))
void __thiscall parley_create_advance_list_pane(WindowObjectView *this,iptr param_1,iptr param_2,int param_3)

{
  int iVar1;
  int iVar2;
  Control *pCVar3;
  i8 frame_[FRAME_OFF(72)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  local_18 = 0;
  local_28 = *(int *)param_1;
  local_24 = *(i32 *)(param_1 + 4);
  local_20 = *(int *)(param_1 + 8);
  local_1c = *(i32 *)(param_1 + 0xc);
  iVar1 = civ_has_wonder(human_civ,0x18);
  if ((((iVar1 == 0) && (iVar1 = civ_has_wonder(human_civ,9), iVar1 == 0)) &&
      ((*(byte *)&civs[human_civ].treaties[parley_other_civ] & 0x80) == 0)) &&
     (((*(byte *)&civs[human_civ].treaties[parley_other_civ] & 8) == 0 &&
      (game.reveal_map == '\0')))) {
    local_18 = 0;
  }
  else {
    local_18 = 1;
  }
  this[param_2 + 0xfa].field_0 = 0;
  civ = human_civ;
  if ((param_3 != 0) && (local_18 != 0)) {
    civ = parley_other_civ;
  }
  for (advance = 0; (int)advance < 100; advance++) {
    if (param_3 == 0) {
      iVar1 = civ_has_advance(human_civ,advance);
      if ((iVar1 != 0) &&
         ((local_18 == 0 || (iVar1 = civ_has_advance(parley_other_civ,advance), iVar1 == 0)))) {
        this[this[param_2 + 0xfa].field_0 + param_2 * 0x801 + 0xfc].field_0 = advance;
        this[this[param_2 + 0xfa].field_0 + param_2 * 0x801 + 0x2100].field_0 = 0;
        this[param_2 + 0xfa].field_0++;
      }
    }
    else if (((human_civ == civ) ||
             (iVar1 = civ_has_advance(human_civ,advance), iVar1 != 0)) ||
            (iVar1 = civ_has_advance(civ,advance), iVar1 == 0)) {
      if (((human_civ == civ) &&
          (iVar1 = civ_has_advance(human_civ,advance), iVar1 == 0)) &&
         (((int)advance < 0x59 && (advances[advance].enabled == 1)))) {
        this[this[param_2 + 0xfa].field_0 + param_2 * 0x801 + 0xfc].field_0 = advance;
        this[this[param_2 + 0xfa].field_0 + param_2 * 0x801 + 0x2100].field_0 = 0;
        this[param_2 + 0xfa].field_0++;
      }
    }
    else {
      this[this[param_2 + 0xfa].field_0 + param_2 * 0x801 + 0xfc].field_0 = advance;
      this[this[param_2 + 0xfa].field_0 + param_2 * 0x801 + 0x2100].field_0 = 0;
      this[param_2 + 0xfa].field_0++;
    }
  }
  if ((int)this[param_2 + 0xfa].field_0 < 1) {
    this[param_2 + 0x4104].field_0 = 0xffffffff;
  }
  else {
    this[param_2 + 0x4104].field_0 = 0;
  }
  this[param_2 + 0xf8].field_0 = 3;
  this[param_2 * 4 + 0xf0].field_0 = *(u32 *)param_1;
  this[param_2 * 4 + 0xf1].field_0 = *(u32 *)(param_1 + 4);
  this[param_2 * 4 + 0xf2].field_0 = *(u32 *)(param_1 + 8);
  this[param_2 * 4 + 0xf3].field_0 = *(u32 *)(param_1 + 0xc);
  if ((int)this[param_2 + 0x4108].field_0 < (int)this[param_2 + 0xfa].field_0) {
    iVar2 = GetSystemMetrics(2);
    iVar1 = local_20;
    this[param_2 * 4 + 0xf2].field_0 -= iVar2;
    local_28 = GetSystemMetrics(2);
    local_28 = iVar1 - local_28;
    pCVar3 = operator_new(0x40);
    local_8 = 0;
    if (pCVar3 == (Control *)0x0) {
      local_34 = 0;
    }
    else {
      local_34 = scrollbar_ctor(pCVar3);
    }
    local_8 = 0xffffffff;
    this[param_2 + 0xdf].field_0 = local_34;
    if (this == (WindowObjectView *)0x0) {
      local_40 = (WindowObjectView *)0x0;
    }
    else {
      local_40 = this + 0x12;
    }
    scrollbar_create
              ((Control *)this[param_2 + 0xdf].field_0,(iptr)local_40,param_2 + 0x411,
               (iptr)&local_28,1);
    scrollbar_set_range
              ((Control *)this[param_2 + 0xdf].field_0,0,
               (this[param_2 + 0xfa].field_0 - 1) - this[param_2 + 0x4108].field_0);
    scrollbar_set_pos((ClickControl *)this[param_2 + 0xdf].field_0,0);
    scrollbar_set_page_size
              ((Control *)this[param_2 + 0xdf].field_0,this[param_2 + 0x4108].field_0);
    scrollbar_set_callback
              ((Control *)this[param_2 + 0xdf].field_0,
               (iptr)(((void *)ADDR(0x0040349f, parley_advance_list0_on_scroll)) + ((param_2 == 0) - 1 & 0xffffdd37)));
    scrollbar_set_track_callback
              ((ScrollbarTrackSetView *)this[param_2 + 0xdf].field_0,
               (iptr)(((void *)ADDR(0x0040349f, parley_advance_list0_on_scroll)) + ((param_2 == 0) - 1 & 0xffffdd37)));
  }
  pCVar3 = operator_new(0x40);
  local_8 = 1;
  if (pCVar3 == (Control *)0x0) {
    local_3c = 0;
  }
  else {
    local_3c = hotspot_ctor(pCVar3);
  }
  local_8 = 0xffffffff;
  this[param_2 + 0xe1].field_0 = local_3c;
  if (this == (WindowObjectView *)0x0) {
    local_44 = (WindowObjectView *)0x0;
  }
  else {
    local_44 = this + 0x12;
  }
  hotspot_create
            ((ClickControl *)this[param_2 + 0xe1].field_0,(iptr)local_44,param_2 + 0x413,
             (iptr)(this + param_2 * 4 + 0xf0));
  hotspot_set_click_callback((HotspotClickSetView *)this[param_2 + 0xe1].field_0,ADDR(0x4017da, parley_advance_list_on_click));
  hotspot_set_dblclick_callback((HotspotDblClickSetView *)this[param_2 + 0xe1].field_0,ADDR(0x4017da, parley_advance_list_on_click));
  parley_draw_advance_list(param_2);
  return;
}
#undef human_civ
#undef parley_other_civ
#undef local_44
#undef local_40
#undef local_3c
#undef local_34
#undef advance
#undef local_28
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef civ
#undef local_10
#undef puStack_c
#undef local_8

/* 00450ae6 auto */
void __cdecl parley_advance_list0_on_scroll(i32 param_1)

{
  parley_advance_list_on_scroll(0,param_1);
  return;
}

/* 00450b22 auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl parley_advance_list_on_scroll(int param_1,i32 param_2)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar1 - 0x48;
  }
  wnd_activate((Wnd *)(local_8 + 0x48));
  *(i32 *)(local_8 + 0x10410 + param_1 * 4) = param_2;
  parley_draw_advance_list(param_1);
  return;
}
#undef local_8

/* 00450b83 auto */
#define local_1c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(12)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(16)))
#define local_c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(24)))
void __cdecl parley_advance_list_on_click(int param_1)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar2 = wnd_get_active_child();
  if (iVar2 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar2 - 0x48;
  }
  wnd_activate((Wnd *)(local_8 + 0x48));
  local_c = param_1 - 0x413;
  wnd_get_cursor_pos
            ((WndBase *)(local_8 + 0x48),(iptr)&local_10,(iptr)&local_14);
  if (((*(int *)(local_8 + 1000 + local_c * 4) != 0) &&
      (iVar2 = parley_advance_list_hit_test(local_10,local_14,local_c), -1 < iVar2)) &&
     (iVar2 < *(int *)(local_8 + 1000 + local_c * 4))) {
    iVar3 = wnd_is_shift_down((void *)(local_8 + 0x48));
    if (iVar3 == 0) {
      iVar3 = wnd_is_ctrl_down((void *)(local_8 + 0x48));
      if (iVar3 == 0) {
        for (local_18 = 0; local_18 < *(int *)(local_8 + 1000 + local_c * 4);
            local_18 = local_18 + 1) {
          if (local_18 != iVar2) {
            *(i32 *)(local_18 * 4 + local_c * 0x2004 + 0x8400 + local_8) = 0;
          }
        }
        *(int *)(local_8 + 0x10418 + local_c * 4) = iVar2;
        puVar1 = (uint *)(iVar2 * 4 + local_c * 0x2004 + 0x8400 + local_8);
        *puVar1 = *puVar1 ^ 1;
      }
      else {
        *(int *)(local_8 + 0x10418 + local_c * 4) = iVar2;
        puVar1 = (uint *)(iVar2 * 4 + local_c * 0x2004 + 0x8400 + local_8);
        *puVar1 = *puVar1 ^ 1;
      }
    }
    else {
      for (local_18 = 0; local_18 < *(int *)(local_8 + 1000 + local_c * 4); local_18++)
      {
        *(i32 *)(local_18 * 4 + local_c * 0x2004 + 0x8400 + local_8) = 0;
      }
      if (*(int *)(local_8 + 0x10418 + local_c * 4) < iVar2) {
        local_18 = *(int *)(local_8 + 0x10418 + local_c * 4);
        local_1c = iVar2;
      }
      else {
        local_1c = *(int *)(local_8 + 0x10418 + local_c * 4);
        local_18 = iVar2;
      }
      for (; local_18 <= local_1c; local_18++) {
        *(i32 *)(local_18 * 4 + local_c * 0x2004 + 0x8400 + local_8) = 1;
      }
    }
    parley_draw_advance_list(local_c);
  }
  return;
}
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 00450df6 auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
int __cdecl parley_advance_list_hit_test(int param_1,int param_2,int param_3)

{
  iptr iVar1;
  int iVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar1 - 0x48;
  }
  if (param_2 < *(int *)(param_3 * 0x10 + 0x3c4 + local_8)) {
    iVar2 = -1;
  }
  else if (param_2 < *(int *)(param_3 * 0x10 + 0x3cc + local_8)) {
    if (param_1 < *(int *)(param_3 * 0x10 + 0x3c0 + local_8)) {
      iVar2 = -3;
    }
    else if (param_1 < *(int *)(param_3 * 0x10 + 0x3c8 + local_8)) {
      iVar2 = *(int *)(param_3 * 0x10 + 0x3c4 + local_8);
      iVar3 = rect_height(param_3 * 0x10 + local_8 + 0x3c0);
      iVar2 = (param_2 - iVar2) / (iVar3 / (*(int *)(local_8 + 0x10420 + param_3 * 4) + 1)) +
              *(int *)(local_8 + 0x10410 + param_3 * 4);
    }
    else {
      iVar2 = -4;
    }
  }
  else {
    iVar2 = -2;
  }
  return iVar2;
}
#undef local_8

/* 00450f0b auto */
#define dlg_sel_text_color (*(int *)((u8 *)&g.d_00635a28))
#define dlg_sel_text_shadow_color (*(int *)((u8 *)&g.d_00635a2c))
#define list_bg_color (*(i32 *)((u8 *)&g.d_00635a18))
#define list_sel_bg_color (*(i32 *)((u8 *)&g.d_00635a24))
#define list_shadow_color (*(int *)((u8 *)&g.d_00635a20))
#define list_text_color (*(int *)((u8 *)&g.d_00635a1c))
#define panel_margin_x (*(int *)((u8 *)&g.d_0062d858))
#define local_7c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_78 (*(i32 *)(frame_ + FRAME_OFF(8)))
#define local_70 (*(i8 (*)[16])(frame_ + FRAME_OFF(16)))
#define local_60 (*(int *)(frame_ + FRAME_OFF(32)))
#define advance (*(iptr *)(frame_ + FRAME_OFF(36)))
#define local_58 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_54 (*(int *)(frame_ + FRAME_OFF(44)))
#define local_50 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_4c (*(int *)(frame_ + FRAME_OFF(52)))
#define local_48 (*(int *)(frame_ + FRAME_OFF(56)))
#define local_44 (*(int *)(frame_ + FRAME_OFF(60)))
#define local_40 (*(int *)(frame_ + FRAME_OFF(64)))
#define local_3c (*(Sprite * *)(frame_ + FRAME_OFF(68)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(72)))
#define local_34 (*(ViewWindow * *)(frame_ + FRAME_OFF(76)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(80)))
#define local_2c (*(tagRECT *)(frame_ + FRAME_OFF(84)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(100)))
#define local_18 (*(i8 (*)[16])(frame_ + FRAME_OFF(104)))
#define local_8 (*(GameFont * *)(frame_ + FRAME_OFF(120)))
void __cdecl parley_draw_advance_list(iptr param_1)

{
  u8 *puVar1;
  int iVar2;
  int iVar3;
  iptr iVar4;
  i8 frame_[FRAME_OFF(128)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar2 = wnd_get_active_child();
  if (iVar2 == 0) {
    local_34 = (ViewWindow *)0x0;
  }
  else {
    local_34 = (ViewWindow *)(iVar2 - 0x48);
  }
  surface_get_clip((DibSurface *)local_34,(iptr)local_18);
  surface_set_clip((DibSurface *)local_34,(iptr)(local_34->pad_3c0 + param_1 * 0x10));
  surface_fill_rect
            ((DibSurface *)local_34,(iptr)(local_34->pad_3c0 + param_1 * 0x10),list_bg_color);
  if (local_34->field_154 == 0) {
    local_8 = (GameFont *)&font_size14;
  }
  else {
    local_8 = (GameFont *)&font_size21;
  }
  local_4c = *(int *)(local_34->pad_3c0 + param_1 * 0x10);
  local_48 = rect_width((iptr)(local_34->pad_3c0 + param_1 * 0x10));
  local_1c = rect_height((iptr)(local_34->pad_3c0 + param_1 * 0x10));
  local_1c = local_1c / (*(int *)(local_34[0x3e].pad_48 + param_1 * 4 + 0x38) + 1);
  iVar2 = local_1c / 2;
  iVar3 = font_cached_height(local_8);
  local_60 = iVar2 - iVar3 / 2;
  puVar1 = local_34->pad_200 + param_1 * 4 - 0x1c;
  puVar1[0] = '\0';
  puVar1[1] = '\0';
  puVar1[2] = '\0';
  puVar1[3] = '\0';
  local_54 = 0;
  do {
    if (*(int *)(local_34->pad_3c0 + param_1 * 4 + 0x28) <= local_54) {
LAB_00451089:
      for (local_54 = 0; local_54 < *(int *)(local_34[0x3e].pad_48 + param_1 * 4 + 0x38) + 1;
          local_54 = local_54 + 1) {
        local_50 = *(int *)(local_34->pad_3c0 + param_1 * 0x10 + 4) + local_54 * local_1c +
                   panel_margin_y;
        SetRect(&local_2c,local_4c,local_50,local_4c + local_48,local_50 + local_1c);
        if (((local_54 == 0) || (*(int *)(local_34[0x3e].pad_48 + param_1 * 4 + 0x28) != -1)) &&
           (*(int *)(local_34[0x3e].pad_48 + param_1 * 4 + 0x28) + local_54 <
            *(int *)(local_34->pad_3c0 + param_1 * 4 + 0x28))) {
          local_30 = *(int *)(param_1 * 0x2004 +
                              (*(int *)(local_34[0x3e].pad_48 + param_1 * 4 + 0x28) + local_54) * 4
                              + 0x8400 + (int)local_34);
          if (local_30 == 0) {
            local_38 = list_text_color;
            local_44 = list_shadow_color;
          }
          else {
            local_38 = dlg_sel_text_color;
            local_44 = dlg_sel_text_shadow_color;
          }
          advance = *(int *)(param_1 * 0x2004 +
                              (*(int *)(local_34[0x3e].pad_48 + param_1 * 4 + 0x28) + local_54) * 4
                              + 0x3f0 + (int)local_34);
          local_3c = (Sprite *)
                     (&advance_category_icon_sprites +
                     (char)advances[advance].category * 0xf0 +
                     (char)advances[advance].epoch * 0x3c);
          iVar2 = sprite_get_width(local_3c);
          local_40 = panel_margin_x * 3 + iVar2 * 2;
          local_2c.left += local_40;
          if (local_30 == 0) {
            local_78 = list_bg_color;
          }
          else {
            local_78 = list_sel_bg_color;
          }
          surface_fill_rect((DibSurface *)local_34,(iptr)&local_2c,local_78);
          if (*(int *)(local_34[0x3e].pad_48 + param_1 * 4 + 0x28) == -1) {
            text_clear();
            if ((param_1 == 0) || (parley_mode == 7)) {
              text_append_label(0x36b);
            }
            else {
              text_append_label(0x36a);
            }
            puVar1 = local_34->pad_200 + param_1 * 4 - 0x1c;
            puVar1[0] = '\0';
            puVar1[1] = '\0';
            puVar1[2] = '\0';
            puVar1[3] = '\0';
            iVar2 = rect_width((iptr)(local_34->pad_3c0 + param_1 * 0x10));
            iVar3 = font_text_width(local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)));
            local_40 = (iVar2 - iVar3) / 2;
          }
          else {
            local_58 = sprite_get_width(local_3c);
            local_58 += panel_margin_x * 2;
            local_7c = local_58;
            if ((*(int *)(local_34[0x3e].pad_48 + param_1 * 4 + 0x28) + local_54 & 1U) == 0) {
              local_7c = panel_margin_x;
            }
            iVar3 = local_50 + local_1c / 2;
            iVar2 = sprite_get_height(local_3c);
            sprite_draw
                      (local_3c,(iptr)local_70,ADDR(0x67a7a8, ((u8 *)&g.d_0067a7a8)),local_4c + local_7c,iVar3 - iVar2 / 2);
            text_clear();
            iVar4 = label_string(advances[advance].name);
            text_append(iVar4);
          }
          if (local_44 != local_38) {
            gfx_set_text_color_index(local_44);
            surface_draw_text
                      ((DibSurface *)local_34,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_4c + local_40 + 2,
                       local_50 + local_60 + 1,5);
            gfx_set_text_color_index(local_38);
            surface_draw_text
                      ((DibSurface *)local_34,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_4c + local_40 + 1,
                       local_50 + local_60,5);
          }
          gfx_set_text_color_index(local_38);
          surface_draw_text
                    ((DibSurface *)local_34,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_4c + local_40,
                     local_50 + local_60,5);
        }
      }
      surface_set_clip((DibSurface *)local_34,(iptr)local_18);
      parley_update_buttons(local_34);
      ctrl_show_and_redraw(*(Control **)(local_34->pad_364 + param_1 * 4 + 0x20))
      ;
      return;
    }
    if (*(int *)(param_1 * 0x2004 + local_54 * 4 + 0x8400 + (int)local_34) != 0) {
      puVar1 = local_34->pad_200 + param_1 * 4 - 0x1c;
      puVar1[0] = 1;
      puVar1[1] = '\0';
      puVar1[2] = '\0';
      puVar1[3] = '\0';
      goto LAB_00451089;
    }
    local_54++;
  } while( true );
}
#undef dlg_sel_text_color
#undef dlg_sel_text_shadow_color
#undef list_bg_color
#undef list_sel_bg_color
#undef list_shadow_color
#undef list_text_color
#undef panel_margin_x
#undef local_7c
#undef local_78
#undef local_70
#undef local_60
#undef advance
#undef local_58
#undef local_54
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
#undef local_1c
#undef local_18
#undef local_8

/* 004683f0 auto */
#define parley_units_by_city (*(i32 *)((u8 *)&g.d_0066be78))
#define local_40 (*(u8 * *)(frame_ + FRAME_OFF(0)))
#define local_3c (*(u8 * *)(frame_ + FRAME_OFF(4)))
#define local_34 (*(i32 *)(frame_ + FRAME_OFF(12)))
#define local_2c (*(i32 *)(frame_ + FRAME_OFF(20)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(28)))
#define local_20 (*(i32 *)(frame_ + FRAME_OFF(32)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(36)))
#define local_18 (*(i32 *)(frame_ + FRAME_OFF(40)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(44)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(48)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(52)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(56)))
void __thiscall
parley_create_unit_list_pane(ListPaneWindow *this,iptr param_1,int param_2,i32 param_3)

{
  u8 *puVar1;
  int iVar2;
  int iVar3;
  Control *pCVar4;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  local_14 = wnd_get_active_child();
  if (local_14 == 0) {
    local_14 = 0;
  }
  else {
    local_14 -= 0x48;
  }
  *(i32 *)(&parley_list_own_side + param_2 * 4) = param_3;
  local_24 = *(int *)param_1;
  local_20 = *(i32 *)(param_1 + 4);
  local_1c = *(int *)(param_1 + 8);
  local_18 = *(i32 *)(param_1 + 0xc);
  parley_units_by_city = 0;
  parley_build_unit_list(this,param_2,0);
  if (*(int *)(this[3].pad_48 + param_2 * 4 + 0x4c) < 1) {
    puVar1 = this[0xea].pad_48 + param_2 * 4 + 0x30;
    puVar1[0] = 0xff;
    puVar1[1] = 0xff;
    puVar1[2] = 0xff;
    puVar1[3] = 0xff;
  }
  else {
    puVar1 = this[0xea].pad_48 + param_2 * 4 + 0x30;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
  }
  puVar1 = this[3].pad_48 + param_2 * 4 + 0x44;
  puVar1[0] = '\0';
  puVar1[1] = '\0';
  puVar1[2] = '\0';
  puVar1[3] = '\0';
  *(i32 *)(this[3].pad_48 + param_2 * 0x10 + 0x24) = *(i32 *)param_1;
  *(i32 *)(this[3].pad_48 + param_2 * 0x10 + 0x28) = *(i32 *)(param_1 + 4);
  *(i32 *)(this[3].pad_48 + param_2 * 0x10 + 0x2c) = *(i32 *)(param_1 + 8);
  *(i32 *)(this[3].pad_48 + param_2 * 0x10 + 0x30) = *(i32 *)(param_1 + 0xc);
  if (*(int *)(this[0xea].pad_48 + param_2 * 4 + 0x40) <
      *(int *)(this[3].pad_48 + param_2 * 4 + 0x4c)) {
    iVar3 = GetSystemMetrics(2);
    iVar2 = local_1c;
    *(int *)(this[3].pad_48 + param_2 * 0x10 + 0x2c) =
         *(int *)(this[3].pad_48 + param_2 * 0x10 + 0x2c) - iVar3;
    local_24 = GetSystemMetrics(2);
    local_24 = iVar2 - local_24;
    pCVar4 = operator_new(0x40);
    local_8 = 0;
    if (pCVar4 == (Control *)0x0) {
      local_2c = 0;
    }
    else {
      local_2c = scrollbar_ctor(pCVar4);
    }
    local_8 = 0xffffffff;
    *(i32 *)(this[3].pad_48 + param_2 * 4 - 0x20) = local_2c;
    if (this == (ListPaneWindow *)0x0) {
      local_3c = (u8 *)0x0;
    }
    else {
      local_3c = this->pad_48;
    }
    scrollbar_create
              (*(Control **)(this[3].pad_48 + param_2 * 4 - 0x20),(iptr)local_3c,
               param_2 + 0x3fa,(iptr)&local_24,1);
    scrollbar_set_range
              (*(Control **)(this[3].pad_48 + param_2 * 4 - 0x20),0,
               *(int *)(this[3].pad_48 + param_2 * 4 + 0x4c) -
               *(int *)(this[0xea].pad_48 + param_2 * 4 + 0x40));
    scrollbar_set_pos(*(ClickControl **)(this[3].pad_48 + param_2 * 4 - 0x20),0);
    scrollbar_set_page_size
              (*(Control **)(this[3].pad_48 + param_2 * 4 - 0x20),
               *(int *)(this[0xea].pad_48 + param_2 * 4 + 0x40) - 1);
    scrollbar_set_callback
              (*(Control **)(this[3].pad_48 + param_2 * 4 - 0x20),
               (iptr)(((void *)ADDR(0x004035fd, parley_unit_list_scroll_left)) + ((param_2 == 0) - 1 & 0x276)));
    scrollbar_set_track_callback
              (*(ScrollbarTrackSetView **)(this[3].pad_48 + param_2 * 4 - 0x20),
               (iptr)(((void *)ADDR(0x004035fd, parley_unit_list_scroll_left)) + ((param_2 == 0) - 1 & 0x276)));
  }
  pCVar4 = operator_new(0x40);
  local_8 = 1;
  if (pCVar4 == (Control *)0x0) {
    local_34 = 0;
  }
  else {
    local_34 = hotspot_ctor(pCVar4);
  }
  local_8 = 0xffffffff;
  *(i32 *)(this[3].pad_48 + param_2 * 4 - 0x18) = local_34;
  if (this == (ListPaneWindow *)0x0) {
    local_40 = (u8 *)0x0;
  }
  else {
    local_40 = this->pad_48;
  }
  hotspot_create
            (*(ClickControl **)(this[3].pad_48 + param_2 * 4 - 0x18),(iptr)local_40,
             param_2 + 0x3fc,(iptr)(this[3].pad_48 + param_2 * 0x10 + 0x24));
  hotspot_set_click_callback(*(HotspotClickSetView **)(this[3].pad_48 + param_2 * 4 - 0x18),ADDR(0x401dac, parley_unit_list_on_click));
  hotspot_set_dblclick_callback(*(HotspotDblClickSetView **)(this[3].pad_48 + param_2 * 4 - 0x18),ADDR(0x401dac, parley_unit_list_on_click));
  parley_draw_unit_list(param_2);
  return;
}
#undef parley_units_by_city
#undef local_40
#undef local_3c
#undef local_34
#undef local_2c
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef puStack_c
#undef local_8

/* 00468797 auto */
void __cdecl parley_unit_list_scroll_left(i32 param_1)

{
  parley_unit_list_on_scroll(0,param_1);
  return;
}

/* 004687d3 auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl parley_unit_list_on_scroll(int param_1,i32 param_2)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar1 - 0x48;
  }
  wnd_activate((Wnd *)(local_8 + 0x48));
  *(i32 *)(local_8 + 0x10410 + param_1 * 4) = param_2;
  parley_draw_unit_list(param_1);
  return;
}
#undef local_8

/* 00468834 auto */
#define local_1c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(12)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(16)))
#define local_c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(24)))
void __cdecl parley_unit_list_on_click(int param_1)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar2 = wnd_get_active_child();
  if (iVar2 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar2 - 0x48;
  }
  wnd_activate((Wnd *)(local_8 + 0x48));
  local_c = param_1 - 0x3fc;
  wnd_get_cursor_pos
            ((WndBase *)(local_8 + 0x48),(iptr)&local_10,(iptr)&local_14);
  if (((*(int *)(local_8 + 1000 + local_c * 4) != 0) &&
      (iVar2 = parley_unit_list_hit_test(local_10,local_14,local_c), -1 < iVar2)) &&
     (iVar2 < *(int *)(local_8 + 1000 + local_c * 4))) {
    iVar3 = wnd_is_shift_down((void *)(local_8 + 0x48));
    if (iVar3 == 0) {
      iVar3 = wnd_is_ctrl_down((void *)(local_8 + 0x48));
      if (iVar3 == 0) {
        for (local_18 = 0; local_18 < *(int *)(local_8 + 1000 + local_c * 4);
            local_18 = local_18 + 1) {
          if (local_18 != iVar2) {
            *(i32 *)(local_c * 0x2004 + local_18 * 4 + 0x8400 + local_8) = 0;
          }
        }
        *(int *)(local_8 + 0x10418 + local_c * 4) = iVar2;
        puVar1 = (uint *)(local_c * 0x2004 + iVar2 * 4 + 0x8400 + local_8);
        *puVar1 = *puVar1 ^ 1;
      }
      else {
        *(int *)(local_8 + 0x10418 + local_c * 4) = iVar2;
        puVar1 = (uint *)(local_c * 0x2004 + iVar2 * 4 + 0x8400 + local_8);
        *puVar1 = *puVar1 ^ 1;
      }
    }
    else {
      for (local_18 = 0; local_18 < *(int *)(local_8 + 1000 + local_c * 4); local_18++)
      {
        *(i32 *)(local_c * 0x2004 + local_18 * 4 + 0x8400 + local_8) = 0;
      }
      if (*(int *)(local_8 + 0x10418 + local_c * 4) < iVar2) {
        local_18 = *(int *)(local_8 + 0x10418 + local_c * 4);
        local_1c = iVar2;
      }
      else {
        local_1c = *(int *)(local_8 + 0x10418 + local_c * 4);
        local_18 = iVar2;
      }
      for (; local_18 <= local_1c; local_18++) {
        *(i32 *)(local_c * 0x2004 + local_18 * 4 + 0x8400 + local_8) = 1;
      }
    }
    parley_draw_unit_list(local_c);
  }
  return;
}
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 00468aa7 auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
int __cdecl parley_unit_list_hit_test(int param_1,int param_2,int param_3)

{
  iptr iVar1;
  int iVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar1 - 0x48;
  }
  if (param_2 < *(int *)(param_3 * 0x10 + 0x3c4 + local_8)) {
    iVar2 = -1;
  }
  else if (param_2 < *(int *)(param_3 * 0x10 + 0x3cc + local_8)) {
    if (param_1 < *(int *)(param_3 * 0x10 + 0x3c0 + local_8)) {
      iVar2 = -3;
    }
    else if (param_1 < *(int *)(param_3 * 0x10 + 0x3c8 + local_8)) {
      iVar2 = *(int *)(param_3 * 0x10 + 0x3c4 + local_8);
      iVar3 = rect_height(param_3 * 0x10 + local_8 + 0x3c0);
      iVar2 = (param_2 - iVar2) / (iVar3 / *(int *)(local_8 + 0x10420 + param_3 * 4)) +
              *(int *)(local_8 + 0x10410 + param_3 * 4);
    }
    else {
      iVar2 = -4;
    }
  }
  else {
    iVar2 = -2;
  }
  return iVar2;
}
#undef local_8

/* 00468bb9 auto */
#define dlg_sel_text_color (*(int *)((u8 *)&g.d_00635a28))
#define dlg_sel_text_shadow_color (*(int *)((u8 *)&g.d_00635a2c))
#define list_bg_color (*(i32 *)((u8 *)&g.d_00635a18))
#define list_sel_bg_color (*(i32 *)((u8 *)&g.d_00635a24))
#define list_shadow_color (*(int *)((u8 *)&g.d_00635a20))
#define list_text_color (*(int *)((u8 *)&g.d_00635a1c))
#define parley_units_by_city (*(int *)((u8 *)&g.d_0066be78))
#define local_80 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_7c (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_78 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_70 (*(i8 (*)[16])(frame_ + FRAME_OFF(16)))
#define local_60 (*(int *)(frame_ + FRAME_OFF(32)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(36)))
#define local_58 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_54 (*(int *)(frame_ + FRAME_OFF(44)))
#define local_50 (*(int *)(frame_ + FRAME_OFF(48)))
#define local_4c (*(int *)(frame_ + FRAME_OFF(52)))
#define local_48 (*(int *)(frame_ + FRAME_OFF(56)))
#define local_44 (*(int *)(frame_ + FRAME_OFF(60)))
#define local_40 (*(int *)(frame_ + FRAME_OFF(64)))
#define local_3c (*(Sprite * *)(frame_ + FRAME_OFF(68)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(72)))
#define this2 (*(ViewWindow * *)(frame_ + FRAME_OFF(76)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(80)))
#define local_2c (*(tagRECT *)(frame_ + FRAME_OFF(84)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(100)))
#define local_18 (*(i8 (*)[16])(frame_ + FRAME_OFF(104)))
#define local_8 (*(GameFont * *)(frame_ + FRAME_OFF(120)))
void __cdecl parley_draw_unit_list(iptr param_1)

{
  u8 *puVar1;
  int iVar2;
  int iVar3;
  iptr iVar4;
  int iVar5;
  i32 uVar6;
  i8 frame_[FRAME_OFF(128)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar2 = wnd_get_active_child();
  if (iVar2 == 0) {
    this2 = (ViewWindow *)0x0;
  }
  else {
    this2 = (ViewWindow *)(iVar2 - 0x48);
  }
  surface_get_clip((DibSurface *)this2,(iptr)local_18);
  surface_set_clip((DibSurface *)this2,(iptr)(this2->pad_3c0 + param_1 * 0x10));
LAB_00468c0c:
  surface_fill_rect
            ((DibSurface *)this2,(iptr)(this2->pad_3c0 + param_1 * 0x10),list_bg_color);
  if (this2->field_154 == 0) {
    local_8 = (GameFont *)&font_size14;
  }
  else {
    local_8 = (GameFont *)&font_size21;
  }
  local_4c = *(int *)(this2->pad_3c0 + param_1 * 0x10);
  local_48 = rect_width((iptr)(this2->pad_3c0 + param_1 * 0x10));
  local_1c = rect_height((iptr)(this2->pad_3c0 + param_1 * 0x10));
  local_1c = local_1c / *(int *)(this2[0x3e].pad_48 + param_1 * 4 + 0x38);
  iVar2 = local_1c / 2;
  iVar3 = font_cached_height(local_8);
  local_60 = iVar2 - iVar3 / 2;
  puVar1 = this2->pad_200 + param_1 * 4 - 0x1c;
  puVar1[0] = '\0';
  puVar1[1] = '\0';
  puVar1[2] = '\0';
  puVar1[3] = '\0';
  for (local_54 = 0; local_54 < *(int *)(this2->pad_3c0 + param_1 * 4 + 0x28);
      local_54 = local_54 + 1) {
    if (*(int *)(local_54 * 4 + param_1 * 0x2004 + 0x8400 + (int)this2) != 0) {
      puVar1 = this2->pad_200 + param_1 * 4 - 0x1c;
      puVar1[0] = 1;
      puVar1[1] = '\0';
      puVar1[2] = '\0';
      puVar1[3] = '\0';
      break;
    }
  }
  local_54 = 0;
  do {
    if (*(int *)(this2[0x3e].pad_48 + param_1 * 4 + 0x38) <= local_54) {
LAB_004692ba:
      surface_set_clip((DibSurface *)this2,(iptr)local_18);
      parley_update_buttons(this2);
      ctrl_show_and_redraw(*(Control **)(this2->pad_364 + param_1 * 4 + 0x20))
      ;
      return;
    }
    local_50 = *(int *)(this2->pad_3c0 + param_1 * 0x10 + 4) + local_1c * local_54;
    SetRect(&local_2c,local_4c,local_50,local_48 + local_4c,local_1c + local_50);
    if ((local_54 != 0) && (*(int *)(this2[0x3e].pad_48 + param_1 * 4 + 0x28) == -1))
    goto LAB_004692ba;
    if (*(int *)(this2[0x3e].pad_48 + param_1 * 4 + 0x28) + local_54 <
        *(int *)(this2->pad_3c0 + param_1 * 4 + 0x28)) {
      local_30 = *(int *)(param_1 * 0x2004 +
                          (*(int *)(this2[0x3e].pad_48 + param_1 * 4 + 0x28) + local_54) * 4 +
                          0x8400 + (int)this2);
      if (local_30 == 0) {
        local_38 = list_text_color;
        local_44 = list_shadow_color;
      }
      else {
        local_38 = dlg_sel_text_color;
        local_44 = dlg_sel_text_shadow_color;
      }
      unit = 0;
      if ((0 < *(int *)(this2->pad_3c0 + param_1 * 4 + 0x28)) &&
         (unit = parley_find_unit_by_id
                               ((WindowObjectView *)this2,
                                *(i32 *)
                                 (param_1 * 0x2004 +
                                  (*(int *)(this2[0x3e].pad_48 + param_1 * 4 + 0x28) + local_54)
                                  * 4 + 0x43f8 + (int)this2)), unit < 0)) break;
      local_3c = (Sprite *)(&unit_sprites + (uint)units[unit].type * 0x3c);
      if (this2->field_154 == 0) {
        iVar2 = sprite_get_width(local_3c);
        local_78 = (iVar2 * 2) / 3;
      }
      else {
        local_78 = sprite_get_width(local_3c);
      }
      local_40 = (-(uint)(this2->field_154 == 0) & 0xfffffffc) + 10 + local_78 * 2;
      local_2c.left = local_2c.left + local_40 - 3;
      if (local_30 == 0) {
        local_7c = list_bg_color;
      }
      else {
        local_7c = list_sel_bg_color;
      }
      surface_fill_rect((DibSurface *)this2,(iptr)&local_2c,local_7c);
      if (*(int *)(this2[0x3e].pad_48 + param_1 * 4 + 0x28) == -1) {
        text_clear();
        iVar4 = label_string(*(i32 *)(label_string_ids + 0xb7c));
        text_append(iVar4);
        puVar1 = this2->pad_200 + param_1 * 4 - 0x1c;
        puVar1[0] = '\0';
        puVar1[1] = '\0';
        puVar1[2] = '\0';
        puVar1[3] = '\0';
        iVar2 = rect_width((iptr)(this2->pad_3c0 + param_1 * 0x10));
        iVar3 = font_text_width(local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)));
        local_40 = (iVar2 - iVar3) / 2;
      }
      else {
        uVar6 = 0x30;
        iVar2 = font_cached_height(local_8);
        gfx_set_scale_ratio(iVar2 * 2,uVar6);
        iVar2 = font_cached_height(local_8);
        local_58 = (iVar2 << 7) / 0x30;
        local_80 = local_58;
        if ((*(int *)(this2[0x3e].pad_48 + param_1 * 4 + 0x28) + local_54 & 1U) == 0) {
          local_80 = 0;
        }
        iVar5 = local_50 + local_1c / 2;
        iVar2 = sprite_get_height(local_3c);
        iVar3 = font_cached_height(local_8);
        sprite_draw
                  (local_3c,(iptr)local_70,ADDR(0x67a7a8, ((u8 *)&g.d_0067a7a8)),local_4c + local_80,
                   iVar5 - (iVar2 * iVar3) / 0x30);
        gfx_set_scale_ratio(1,1);
        if (parley_units_by_city == 0) {
          text_clear();
          text_append_string_id(unit_types[units[unit].type].name);
          if (((parley_mode == 9) ||
              (((parley_mode == 0xe && (param_1 == 0)) && (this2->field_3bd != '\0')))) ||
             ((((parley_mode == 0xe && (param_1 == 1)) && (this2->field_3bc != '\0')) ||
              ((parley_mode == 0xf && (this2->field_3bc != '\0')))))) {
            text_append_str(ADDR(0x62840c, ((u8 *)&g.d_0062840c)));
            iVar4 = unit_home_city_name(unit);
            text_append_str(iVar4);
            text_append_str(ADDR(0x628410, ((u8 *)&g.d_00628410)));
          }
        }
        else {
          text_clear();
          iVar4 = unit_home_city_name(unit);
          text_append_str(iVar4);
          text_append_str(ADDR(0x628414, ((u8 *)&g.d_00628414)));
          text_append_string_id(unit_types[units[unit].type].name);
          text_append_str(ADDR(0x628418, ((u8 *)&g.d_00628418)));
        }
      }
      if (local_44 != local_38) {
        gfx_set_text_color_index(local_44);
        surface_draw_text
                  ((DibSurface *)this2,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_40 + local_4c + 2,
                   local_60 + local_50 + 1,5);
        gfx_set_text_color_index(local_38);
        surface_draw_text
                  ((DibSurface *)this2,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_40 + local_4c + 1,
                   local_60 + local_50,5);
      }
      gfx_set_text_color_index(local_38);
      surface_draw_text
                ((DibSurface *)this2,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_40 + local_4c,
                 local_60 + local_50,5);
    }
    local_54++;
  } while( true );
  parley_build_unit_list((ListPaneWindow *)this2,param_1,1);
  if (*(int *)(this2->pad_3c0 + param_1 * 4 + 0x28) == 0) {
    puVar1 = this2[0x3e].pad_48 + param_1 * 4 + 0x28;
    puVar1[0] = 0xff;
    puVar1[1] = 0xff;
    puVar1[2] = 0xff;
    puVar1[3] = 0xff;
  }
  else if (*(int *)(this2->pad_3c0 + param_1 * 4 + 0x28) <
           *(int *)(this2->pad_3c0 + param_1 * 4 + 0x28)) {
    *(int *)(this2[0x3e].pad_48 + param_1 * 4 + 0x28) =
         *(int *)(this2->pad_3c0 + param_1 * 4 + 0x28) - 1;
  }
  goto LAB_00468c0c;
}
#undef dlg_sel_text_color
#undef dlg_sel_text_shadow_color
#undef list_bg_color
#undef list_sel_bg_color
#undef list_shadow_color
#undef list_text_color
#undef parley_units_by_city
#undef local_80
#undef local_7c
#undef local_78
#undef local_70
#undef local_60
#undef unit
#undef local_58
#undef local_54
#undef local_50
#undef local_4c
#undef local_48
#undef local_44
#undef local_40
#undef local_3c
#undef local_38
#undef this2
#undef local_30
#undef local_2c
#undef local_1c
#undef local_18
#undef local_8

/* 004692ea auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl parley_reveal_city_origin_clicked(void)

{
  iptr iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar1 - 0x48;
  }
  wnd_activate((Wnd *)(local_8 + 0x48));
  ctrl_show_and_redraw(*(Control **)(local_8 + 0x3a4));
  control_hide(*(Control **)(local_8 + 0x39c));
  *(i8 *)(local_8 + 0x3bd) = 1;
  ctrl_enable(*(Control **)(local_8 + 0x38c));
  ctrl_enable(*(Control **)(local_8 + 0x394));
  net_send_message(0xa7,*(i32 *)
                           (&net_player_slots +
                           *(int *)(&net_civ_slots + *(int *)(local_8 + 0x118) * 4) * 0x54),
                     human_civ,(int)*(char *)(local_8 + 0x3bd),0,0,0,0,0,0);
  parley_draw_unit_list(0);
  return;
}
#undef human_civ
#undef local_8

/* 004693c5 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define local_8 (*(WindowObjectView * *)(frame_ + FRAME_OFF(0)))
void __cdecl parley_hide_city_origin_clicked(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = (WindowObjectView *)0x0;
  }
  else {
    local_8 = (WindowObjectView *)(iVar1 - 0x48);
  }
  wnd_activate((Wnd *)(local_8 + 0x12));
  ctrl_show_and_redraw((Control *)local_8[0xe7].field_0);
  control_hide((Control *)local_8[0xe9].field_0);
  *(i8 *)((int)&local_8[0xef].field_0 + 1) = 0;
  ctrl_disable((Control *)local_8[0xe3].field_0);
  ctrl_disable((Control *)local_8[0xe5].field_0);
  net_send_message(0xa8,*(i32 *)
                           (&net_player_slots +
                           *(int *)(&net_civ_slots + local_8[0x46].field_0 * 4) * 0x54),human_civ
                     ,(int)*(char *)((int)&local_8[0xef].field_0 + 1),0,0,0,0,0,0);
  parley_sort_unit_list(local_8,0,local_8[0xfa].field_0 - 1,0);
  parley_draw_unit_list(0);
  return;
}
#undef human_civ
#undef local_8

/* 00469547 auto */
void __cdecl parley_sort_by_city_left_clicked(void)

{
  parley_sort_by_city_clicked(0);
  return;
}

/* 0046957b auto */
#define local_8 (*(void * *)(frame_ + FRAME_OFF(0)))
void __cdecl parley_sort_by_city_clicked(iptr param_1)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = (void *)0x0;
  }
  else {
    local_8 = (void *)(iVar1 - 0x48);
  }
  wnd_activate((Wnd *)((int)local_8 + 0x48));
  parley_sort_units_by_city(local_8,0,*(int *)((int)local_8 + param_1 * 4 + 1000) - 1,param_1);
  parley_draw_unit_list(param_1);
  return;
}
#undef local_8

/* 004695e9 auto */
void __cdecl parley_sort_by_unit_left_clicked(void)

{
  parley_sort_by_unit_clicked(0);
  return;
}

/* 0046961d auto */
#define local_8 (*(WindowObjectView * *)(frame_ + FRAME_OFF(0)))
void __cdecl parley_sort_by_unit_clicked(iptr param_1)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = (WindowObjectView *)0x0;
  }
  else {
    local_8 = (WindowObjectView *)(iVar1 - 0x48);
  }
  wnd_activate((Wnd *)(local_8 + 0x12));
  parley_sort_unit_list(local_8,0,local_8[param_1 + 0xfa].field_0 - 1,param_1);
  parley_draw_unit_list(param_1);
  return;
}
#undef local_8

/* 0046968b auto */
#define parley_units_by_city (*(i32 *)((u8 *)&g.d_0066be78))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(16)))
void __thiscall parley_sort_unit_list(WindowObjectView *this,int param_1,int param_2,iptr param_3)

{
  i32 uVar1;
  iptr iVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar2 = wnd_get_active_child();
  if (iVar2 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar2 - 0x48;
  }
  if (1 < *(int *)(local_8 + 1000 + param_3 * 4)) {
    parley_units_by_city = 0;
    for (local_10 = param_1; local_14 = local_10, local_10 < param_2; local_10++) {
      while (local_14 = local_14 + 1, local_14 <= param_2) {
        iVar3 = _strcmp(*(char **)(&unit_type_name_ptrs +
                                  (uint)units[*(int *)(local_10 * 4 + param_3 * 0x2004 + 0x3f0 +
                                                      local_8)].type * 4),
                        *(char **)(&unit_type_name_ptrs +
                                  (uint)units[*(int *)(local_14 * 4 + param_3 * 0x2004 + 0x3f0 +
                                                      local_8)].type * 4));
        if (0 < iVar3) {
          uVar1 = *(i32 *)(local_10 * 4 + param_3 * 0x2004 + 0x3f0 + local_8);
          *(i32 *)(local_10 * 4 + param_3 * 0x2004 + 0x3f0 + local_8) =
               *(i32 *)(local_14 * 4 + param_3 * 0x2004 + 0x3f0 + local_8);
          *(i32 *)(local_14 * 4 + param_3 * 0x2004 + 0x3f0 + local_8) = uVar1;
          uVar1 = *(i32 *)(local_10 * 4 + param_3 * 0x2004 + 0x43f8 + local_8);
          *(i32 *)(local_10 * 4 + param_3 * 0x2004 + 0x43f8 + local_8) =
               *(i32 *)(local_14 * 4 + param_3 * 0x2004 + 0x43f8 + local_8);
          *(i32 *)(local_14 * 4 + param_3 * 0x2004 + 0x43f8 + local_8) = uVar1;
          uVar1 = *(i32 *)(local_10 * 4 + param_3 * 0x2004 + 0x8400 + local_8);
          *(i32 *)(local_10 * 4 + param_3 * 0x2004 + 0x8400 + local_8) =
               *(i32 *)(local_14 * 4 + param_3 * 0x2004 + 0x8400 + local_8);
          *(i32 *)(local_14 * 4 + param_3 * 0x2004 + 0x8400 + local_8) = uVar1;
        }
      }
    }
  }
  return;
}
#undef parley_units_by_city
#undef local_14
#undef local_10
#undef local_8

/* 0046990a auto */
#define parley_units_by_city (*(i32 *)((u8 *)&g.d_0066be78))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(16)))
void __thiscall parley_sort_units_by_city(void *this,int param_1,int param_2,iptr param_3)

{
  i32 uVar1;
  iptr iVar2;
  char *_Str2;
  char *_Str1;
  int iVar3;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar2 = wnd_get_active_child();
  if (iVar2 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar2 - 0x48;
  }
  if (*(int *)(local_8 + 1000 + param_3 * 4) < 2) {
    return;
  }
  parley_units_by_city = 1;
  local_10 = param_1;
LAB_0046996e:
  local_14 = local_10;
  if (param_2 <= local_10) {
    return;
  }
LAB_00469989:
  do {
    local_14++;
    if (param_2 < local_14) break;
    if (units[*(int *)(local_10 * 4 + param_3 * 0x2004 + 0x3f0 + local_8)].home_city != -1) {
      if (units[*(int *)(local_14 * 4 + param_3 * 0x2004 + 0x3f0 + local_8)].home_city != -1) {
        _Str2 = (char *)unit_home_city_name(*(iptr *)(local_14 * 4 + param_3 * 0x2004 + 0x3f0 +
                                                    local_8));
        _Str1 = (char *)unit_home_city_name(*(iptr *)(local_10 * 4 + param_3 * 0x2004 + 0x3f0 +
                                                    local_8));
        iVar3 = _strcmp(_Str1,_Str2);
        if (iVar3 < 1) goto LAB_00469989;
      }
      uVar1 = *(i32 *)(local_10 * 4 + param_3 * 0x2004 + 0x3f0 + local_8);
      *(i32 *)(local_10 * 4 + param_3 * 0x2004 + 0x3f0 + local_8) =
           *(i32 *)(local_14 * 4 + param_3 * 0x2004 + 0x3f0 + local_8);
      *(i32 *)(local_14 * 4 + param_3 * 0x2004 + 0x3f0 + local_8) = uVar1;
      uVar1 = *(i32 *)(local_10 * 4 + param_3 * 0x2004 + 0x43f8 + local_8);
      *(i32 *)(local_10 * 4 + param_3 * 0x2004 + 0x43f8 + local_8) =
           *(i32 *)(local_14 * 4 + param_3 * 0x2004 + 0x43f8 + local_8);
      *(i32 *)(local_14 * 4 + param_3 * 0x2004 + 0x43f8 + local_8) = uVar1;
      uVar1 = *(i32 *)(local_10 * 4 + param_3 * 0x2004 + 0x8400 + local_8);
      *(i32 *)(local_10 * 4 + param_3 * 0x2004 + 0x8400 + local_8) =
           *(i32 *)(local_14 * 4 + param_3 * 0x2004 + 0x8400 + local_8);
      *(i32 *)(local_14 * 4 + param_3 * 0x2004 + 0x8400 + local_8) = uVar1;
    }
  } while( true );
  local_10++;
  goto LAB_0046996e;
}
#undef parley_units_by_city
#undef local_14
#undef local_10
#undef local_8

/* 00469bdc auto */
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define parley_units_by_city (*(int *)((u8 *)&g.d_0066be78))
#define unit (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_18 (*(void * *)(frame_ + FRAME_OFF(24)))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(36)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(40)))
void __thiscall parley_build_unit_list(ListPaneWindow *this,int param_1,int param_2)

{
  int *piVar1;
  short x2;
  short y2;
  bool bVar4;
  iptr iVar5;
  iptr x;
  int y;
  int iVar8;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_18 = (void *)0x0;
  iVar5 = wnd_get_active_child();
  if (iVar5 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar5 - 0x48;
  }
  if (param_2 != 0) {
    local_18 = operator_new(*(int *)(local_8 + 1000 + param_1 * 4) << 2);
    if (local_18 == (void *)0x0) {
      param_2 = 0;
    }
    else {
      local_2c = *(int *)(local_8 + 1000 + param_1 * 4);
      for (unit = 0; unit < local_2c; unit++) {
        if (*(int *)(param_1 * 0x2004 + unit * 4 + 0x8400 + local_8) == 0) {
          *(i32 *)((int)local_18 + unit * 4) = 0xffffffff;
        }
        else {
          *(i32 *)((int)local_18 + unit * 4) =
               *(i32 *)(param_1 * 0x2004 + unit * 4 + 0x43f8 + local_8);
        }
      }
    }
  }
  *(i32 *)(local_8 + 1000 + param_1 * 4) = 0;
  unit = 0;
  do {
    if (game.num_units <= unit) {
      if ((param_2 != 0) && (local_18 != (void *)0x0)) {
        operator_delete(local_18);
      }
      if (parley_units_by_city == 0) {
        parley_sort_unit_list
                  ((WindowObjectView *)this,0,*(int *)(local_8 + 1000 + param_1 * 4) - 1,param_1);
      }
      else {
        parley_sort_units_by_city(this,0,*(int *)(local_8 + 1000 + param_1 * 4) - 1,param_1);
      }
      return;
    }
    if ((units[unit].id != 0) &&
       (((*(int *)(&parley_list_own_side + param_1 * 4) != 0 && (units[unit].owner == human_civ)) ||
        (((*(int *)(&parley_list_own_side + param_1 * 4) == 0 &&
          ((int)units[unit].owner == this->caption_height)) &&
         (((1 << ((byte)human_civ & 0x1f) & (uint)units[unit].visibility) != 0 ||
          ((int)units[unit].owner == (human_civ & 0xffU))))))))) {
      x2 = units[unit].x;
      y2 = units[unit].y;
      bVar4 = false;
      for (local_c = 0; local_c < 8; local_c++) {
        x = map_wrap_x((int)(char)(&dir_dx_table)[local_c] + (int)x2);
        y = (int)(char)(&dir_dy_table)[local_c] + (int)y2;
        iVar8 = map_in_bounds(x,y);
        if ((iVar8 != 0) && (y = tile_is_ocean(x,y), y == 0)) {
          bVar4 = true;
          break;
        }
      }
      if ((bVar4) || (y = unit_stack_sum(unit,2), y == 1)) {
        *(iptr *)(param_1 * 0x2004 + *(int *)(local_8 + 1000 + param_1 * 4) * 4 + 0x3f0 + local_8) =
             unit;
        *(i32 *)(param_1 * 0x2004 + *(int *)(local_8 + 1000 + param_1 * 4) * 4 + 0x43f8 + local_8) =
             units[unit].id;
        *(i32 *)
         (param_1 * 0x2004 + *(int *)(local_8 + 1000 + param_1 * 4) * 4 + 0x8400 + local_8) = 0;
        if ((param_2 == 1) && (local_18 != (void *)0x0)) {
          for (local_28 = 0; local_28 < local_2c; local_28++) {
            if (units[unit].id == *(int *)((int)local_18 + local_28 * 4)) {
              *(i32 *)
               (param_1 * 0x2004 + *(int *)(local_8 + 1000 + param_1 * 4) * 4 + 0x8400 + local_8) =
                   1;
              break;
            }
          }
        }
        piVar1 = (int *)(local_8 + 1000 + param_1 * 4);
        *piVar1 = *piVar1 + 1;
      }
    }
    unit++;
  } while( true );
}
#undef human_civ
#undef parley_units_by_city
#undef unit
#undef local_2c
#undef local_28
#undef local_18
#undef local_c
#undef local_8

/* 0046af70 auto */
#define net_send_sequence (*(int *)((u8 *)&g.d_00628468))
i8 __thiscall net_session_send_to(void *this,int param_1,iptr param_2)

{
  i8 uVar1;
  int iVar2;
  
  if ((((param_1 < 0) || (7 < param_1)) && (param_1 != 0xff)) && (param_1 != 0)) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62a67c, ((u8 *)&g.d_0062a67c)),ADDR(0x62a658, ((u8 *)&g.d_0062a658)),0x139);
  }
  if (*(int *)(param_2 + 8) == 0) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62a6f4, ((u8 *)&g.d_0062a6f4)),ADDR(0x62a6d0, ((u8 *)&g.d_0062a6d0)),0x13a);
  }
  *(int *)(param_2 + 0xc) = net_send_sequence;
  net_send_sequence++;
  iVar2 = XD_SendSecureData((ushort)param_1,(void *)param_2,*(ulong *)(param_2 + 8),0);
  *(int *)((int)this + 0x578) = iVar2;
  if (*(int *)((int)this + 0x578) < 0) {
    dbg_logf3(ADDR(0x62a704, ((u8 *)&g.d_0062a704)),param_1,*(i32 *)((int)this + 0x578),*(i32 *)(param_2 + 4));
    if (*(int *)(param_2 + 4) == 0x6a) {
      dbg_logf_str(ADDR(0x62a754, ((u8 *)&g.d_0062a754)),(iptr)(s__NM_POP_RETIREDIE__00629990 + *(int *)(param_2 + 0x10) * 0x20))
      ;
    }
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}
#undef net_send_sequence

/* 0046b0a1 auto */
#define net_send_sequence (*(int *)((u8 *)&g.d_00628468))
bool __thiscall net_session_send_to_all(void *this,iptr param_1)

{
  bool bVar1;
  int iVar2;
  
  *(int *)(param_1 + 0xc) = net_send_sequence;
  net_send_sequence++;
  iVar2 = XD_SendBroadcastData((void *)param_1,*(ulong *)(param_1 + 8),0);
  *(int *)((int)this + 0x578) = iVar2;
  bVar1 = *(int *)((int)this + 0x578) < *(int *)(param_1 + 8);
  if (bVar1) {
    dbg_logf(ADDR(0x62a764, ((u8 *)&g.d_0062a764)),*(iptr *)((int)this + 0x578));
  }
  return !bVar1;
}
#undef net_send_sequence

/* 0046b14d auto */
#define loaded_file_kind (*(i16 *)((u8 *)&g.d_006ad6ac))
#define loaded_file_name (*(i8 *)((u8 *)&g.d_006ad6ae))
#define loaded_file_subdir (*(i8 *)((u8 *)&g.d_006ad7b2))
#define net_batch_used_dwords (*(int *)((u8 *)&g.d_006365f4))
#define net_claimed_civs_mask (*(ushort *)((u8 *)&g.d_00654fb0))
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define net_session_phase (*(i32 *)((u8 *)&g.d_006ad640))
#define main_view_timer_cache_i32 (*(i32 *)((u8 *)&g.d_0066c990))
#define local_a24 (*(NetMsgHeader (*)[2])(frame_ + FRAME_OFF(4)))
#define local_a14 (*(NetMsgHeader (*)[2])(frame_ + FRAME_OFF(20)))
#define local_a04 (*(NetMsgHeader (*)[2])(frame_ + FRAME_OFF(36)))
#define local_9f4 (*(NetMsgHeader (*)[2])(frame_ + FRAME_OFF(52)))
#define local_9e4 (*(NetMsgHeader (*)[2])(frame_ + FRAME_OFF(68)))
#define local_9d4 (*(NetMsgHeader (*)[2])(frame_ + FRAME_OFF(84)))
#define local_9c4 (*(NetMsgHeader (*)[2])(frame_ + FRAME_OFF(100)))
#define local_9b4 (*(NetMsgHeader (*)[2])(frame_ + FRAME_OFF(116)))
#define local_9a4 (*(NetMsgHeader (*)[2])(frame_ + FRAME_OFF(132)))
#define local_994 (*(NetMsgHeader (*)[2])(frame_ + FRAME_OFF(148)))
#define local_984 (*(NetMsgHeader (*)[2])(frame_ + FRAME_OFF(164)))
#define local_974 (*(NetMsgHeader (*)[2])(frame_ + FRAME_OFF(180)))
#define local_964 (*(NetMsgHeader (*)[2])(frame_ + FRAME_OFF(196)))
#define local_950 (*(NetMsgHeader (*)[2])(frame_ + FRAME_OFF(216)))
#define local_940 (*(NetMsgHeader (*)[2])(frame_ + FRAME_OFF(232)))
#define local_930 (*(NetMsgHeader (*)[2])(frame_ + FRAME_OFF(248)))
#define local_920 (*(NetMsgHeader (*)[2])(frame_ + FRAME_OFF(264)))
#define local_910 (*(NetMsgHeader (*)[2])(frame_ + FRAME_OFF(280)))
#define local_8fc (*(i32 *)(frame_ + FRAME_OFF(300)))
#define local_8f8 (*(i32 *)(frame_ + FRAME_OFF(304)))
#define local_8f4 (*(i32 *)(frame_ + FRAME_OFF(308)))
#define local_8f0 (*(i32 *)(frame_ + FRAME_OFF(312)))
#define local_8ec (*(NetMsgHeader (*)[2])(frame_ + FRAME_OFF(316)))
#define local_8d8 (*(NetMsgHeader (*)[2])(frame_ + FRAME_OFF(336)))
#define local_8c8 (*(NetMsgHeader (*)[2])(frame_ + FRAME_OFF(352)))
#define local_8b8 (*(NetMsgHeader (*)[38])(frame_ + FRAME_OFF(368)))
#define local_784 (*(NetMsgHeader (*)[2])(frame_ + FRAME_OFF(676)))
#define local_774 (*(NetMsgHeader (*)[2])(frame_ + FRAME_OFF(692)))
#define local_764 (*(NetMsgHeader (*)[2])(frame_ + FRAME_OFF(708)))
#define local_754 (*(NetMsgHeader (*)[2])(frame_ + FRAME_OFF(724)))
#define local_744 (*(NetMsgHeader (*)[2])(frame_ + FRAME_OFF(740)))
#define local_734 (*(uint *)(frame_ + FRAME_OFF(756)))
#define local_730 (*(void * *)(frame_ + FRAME_OFF(760)))
#define local_72c (*(NetMsgHeader (*)[12])(frame_ + FRAME_OFF(764)))
#define local_6c8 (*(NetMsgHeader (*)[2])(frame_ + FRAME_OFF(864)))
#define local_6b8 (*(i8 (*)[624])(frame_ + FRAME_OFF(880)))
#define local_448 (*(NetMsgHeader (*)[2])(frame_ + FRAME_OFF(1504)))
#define local_438 (*(i16 *)(frame_ + FRAME_OFF(1520)))
#define local_436 (*(i8 (*)[260])(frame_ + FRAME_OFF(1522)))
#define local_332 (*(i8 (*)[262])(frame_ + FRAME_OFF(1782)))
#define local_22c (*(NetMsgHeader (*)[2])(frame_ + FRAME_OFF(2044)))
#define local_21c (*(NetMsgHeader (*)[50])(frame_ + FRAME_OFF(2060)))
#define local_88 (*(i16 *)(frame_ + FRAME_OFF(2464)))
#define local_84 (*(NetMsgHeader (*)[15])(frame_ + FRAME_OFF(2468)))
#define local_c (*(void * *)(frame_ + FRAME_OFF(2588)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(2592)))
/* WARNING: Removing unreachable block (ram,0x0046cdce) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl
net_send_message(int param_1,i32 param_2,iptr param_3,iptr param_4,iptr param_5,iptr param_6,
            iptr param_7,i32 param_8,iptr param_9,iptr param_10)

{
  char cVar1;
  size_t sVar2;
  i8 frame_[FRAME_OFF(2600)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = (void *)0x0;
  switch(param_1) {
  case 1:
    net_msg_init_header(local_84,param_1,ADDR(0x62a78c, ((u8 *)&g.d_0062a78c)));
    cVar1 = net_session_send_to_all(&net_session,(iptr)local_84);
    return (int)cVar1;
  case 2:
    net_msg_server_info_init(local_21c);
    local_88 = (i16)net_session_phase;
    cVar1 = net_session_send_to_all(&net_session,(iptr)local_21c);
    return (int)cVar1;
  default:
    return 0;
  case 4:
    net_msg_player_list_init(local_6c8);
    crt_memcpy(local_6b8,&net_player_count,0x270);
    cVar1 = net_session_send_to(&net_session,param_2,(iptr)local_6c8);
    return (int)cVar1;
  case 5:
    net_msg_header_init(local_22c,param_1);
    cVar1 = net_session_send_to(&net_session,param_2,(iptr)local_22c);
    return (int)cVar1;
  case 6:
    net_msg_server_path_init(local_448);
    local_438 = loaded_file_kind;
    crt_strcpy(local_436,&loaded_file_name);
    crt_strcpy(local_332,&loaded_file_subdir);
    cVar1 = net_session_send_to(&net_session,param_2,(iptr)local_448);
    return (int)cVar1;
  case 7:
  case 8:
  case 9:
  case 10:
    local_730 = (void *)0x0;
    if (param_1 == 7) {
      local_734 = diffeng_build_full_image((iptr)&local_730);
    }
    else if (param_1 == 8) {
      local_734 = diffeng_build_delta_image((iptr)&local_730);
    }
    else if (param_1 == 9) {
      local_734 = diffeng_build_civ_image((iptr)&local_730);
    }
    else if (param_1 == 10) {
      local_734 = diffeng_build_map_header_image((iptr)&local_730);
    }
    local_734 = (uint)(local_734 != -1);
    if (local_730 == (void *)0x0) {
      err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62a7b4, ((u8 *)&g.d_0062a7b4)),ADDR(0x62a790, ((u8 *)&g.d_0062a790)),0x22c);
    }
    local_730 = (void *)net_msg_build_packet(param_1,(iptr)local_730,local_734,0,0,0,0,0,0);
    cVar1 = net_session_send_to(&net_session,param_2,(iptr)local_730);
    local_734 = (uint)cVar1;
    operator_delete(local_730);
    return local_734;
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
  case 0xf:
  case 0x10:
  case 0x11:
  case 0x32:
    net_msg_header_init(local_744,param_1);
    cVar1 = net_session_send_to(&net_session,param_2,(iptr)local_744);
    return (int)cVar1;
  case 0x12:
    net_msg_header_init(local_784,param_1);
    cVar1 = net_session_send_to(&net_session,param_2,(iptr)local_784);
    return (int)cVar1;
  case 0x13:
    net_msg_server_answer_init(local_8b8);
    cVar1 = net_session_send_to(&net_session,param_2,(iptr)local_8b8);
    return (int)cVar1;
  case 0x14:
    net_msg_header_init(local_8c8,param_1);
    cVar1 = net_session_send_to(&net_session,param_2,(iptr)local_8c8);
    return (int)cVar1;
  case 0x15:
  case 0x5c:
    cVar1 = net_session_send_to(&net_session,param_2,param_10);
    if (cVar1 == '\0') {
      return 0;
    }
    return *(i32 *)(param_10 + 8);
  case 0x16:
    net_msg_header_init(local_8ec,param_1);
    cVar1 = net_session_send_to(&net_session,param_2,(iptr)local_8ec);
    return (int)cVar1;
  case 0x17:
    local_c = (void *)net_msg_build_packet(param_1,ADDR(0x64bcc8, ((u8 *)&cosmic)),0,0,0,0,0,0,0x29);
    break;
  case 0x18:
    local_c = (void *)net_msg_build_packet(param_1,ADDR(0x627680, ((u8 *)&advances)),0,0,0,0,0,0,0x640);
    break;
  case 0x19:
    local_c = (void *)net_msg_build_packet(param_1,ADDR(0x64c488, ((u8 *)&improvements)),0,0,0,0,0,0,0x218);
    break;
  case 0x1a:
    local_c = (void *)net_msg_build_packet(param_1,ADDR(0x64ba28, ((u8 *)&wonder_expires)),0,0,0,0,0,0,0x1c);
    break;
  case 0x1b:
    local_c = (void *)net_msg_build_packet(param_1,ADDR(0x64b1b8, ((u8 *)&unit_types)),0,0,0,0,0,0,0x4d8);
    break;
  case 0x1c:
    local_c = (void *)net_msg_build_packet(param_1,ADDR(0x627cc0, ((u8 *)&terrain_types)),0,0,0,0,0,0,0x318);
    break;
  case 0x1d:
    local_c = (void *)net_msg_build_packet(param_1,ADDR(0x64b9a0, ((u8 *)&government_names)),0,0,0,0,0,0,0x1c);
    break;
  case 0x1e:
    local_c = (void *)net_msg_build_packet(param_1,ADDR(0x654fe0, ((u8 *)&government_titles)),0,0,0,0,0,0,0x38);
    break;
  case 0x1f:
    local_c = (void *)net_msg_build_packet(param_1,ADDR(0x6554f8, ((u8 *)&leaders)),0,0,0,0,0,0,0x3f0);
    break;
  case 0x20:
    local_c = (void *)net_msg_build_packet(param_1,ADDR(0x64c6a0, ((u8 *)&civs)),0,0,0,0,0,0,0x7524);
    break;
  case 0x21:
    local_c = (void *)net_msg_build_packet(param_1,ADDR(0x64b168, ((u8 *)&commodity_names)),0,0,0,0,0,0,0x40);
    break;
  case 0x22:
    local_c = (void *)net_msg_build_packet(param_1,ADDR(0x655490, ((u8 *)&order_names)),0,0,0,0,0,0,0x68);
    break;
  case 0x23:
    local_c = (void *)net_msg_build_packet(param_1,ADDR(0x64ba10, ((u8 *)&difficulty_names)),0,0,0,0,0,0,0x18);
    break;
  case 0x24:
    local_c = (void *)net_msg_build_packet(param_1,ADDR(0x64b9c0, ((u8 *)&attitude_names)),0,0,0,0,0,0,0x24);
    break;
  case 0x25:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,0,0,0,0,0);
    break;
  case 0x26:
  case 0x27:
    net_msg_header_init(local_9c4,param_1);
    cVar1 = net_session_send_to(&net_session,param_2,(iptr)local_9c4);
    return (int)cVar1;
  case 0x28:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,0,0,0,0,0,0);
    break;
  case 0x2a:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,0,0,0,0,0,0);
    nm_lock_data_count++;
    break;
  case 0x2b:
  case 0x2c:
    net_msg_header_init(local_a14,param_1);
    cVar1 = net_session_send_to(&net_session,param_2,(iptr)local_a14);
    return (int)cVar1;
  case 0x2d:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,0,0,0,0,0,0);
    break;
  case 0x2e:
    cVar1 = net_session_send_to(&net_session,param_2,ADDR(0x6ad110, ((u8 *)&g.d_006ad110)));
    return (int)cVar1;
  case 0x2f:
    net_msg_player_list_node_init(local_72c,param_3);
    cVar1 = net_session_send_to(&net_session,param_2,(iptr)local_72c);
    return (int)cVar1;
  case 0x30:
    if (net_host_flag == '\0') {
      local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,0,0,0,0,0);
      break;
    }
    if ((1 << ((byte)param_4 & 0x1f) & (int)(short)net_claimed_civs_mask) == 0) {
      net_claimed_civs_mask = net_claimed_civs_mask | (ushort)(1 << ((byte)param_4 & 0x1f));
      net_send_message(0x2a,0xff,(int)(short)net_claimed_civs_mask,0,0,0,0,0,0,0);
      nm_nation_accept_count++;
      return 1;
    }
    nm_nation_reject_count++;
  case 0x31:
    if (net_host_flag != '\0') {
      game.human_players = game.human_players & (byte)net_claimed_civs_mask;
      if ((1 << ((byte)param_4 & 0x1f) & (int)(short)net_claimed_civs_mask) != 0) {
        net_claimed_civs_mask = net_claimed_civs_mask & ~(ushort)(1 << ((byte)param_4 & 0x1f));
        game.human_players = game.human_players & (byte)net_claimed_civs_mask;
        net_send_message(0x2a,0xff,(int)(short)net_claimed_civs_mask,0,0,0,0,0,0,0);
        nm_lock_data_count++;
      }
      return 1;
    }
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,0,0,0,0,0);
    break;
  case 0x33:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,param_5,0,0,0,0);
    break;
  case 0x34:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,0,0,0,0,0,0);
    break;
  case 0x35:
  case 0x81:
    net_msg_header_init(local_950,param_1);
    cVar1 = net_session_send_to(&net_session,param_2,(iptr)local_950);
    return (int)cVar1;
  case 0x37:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,0,0,0,0,0,0);
    break;
  case 0x38:
    local_c = (void *)net_msg_build_packet(param_1,(iptr)(units + param_3),param_3,(int)game.num_units
                                         ,param_5,param_6,param_7,param_8,0x20);
    break;
  case 0x39:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,0,0,0,0,0,0);
    break;
  case 0x3a:
    local_c = (void *)net_msg_build_packet(param_1,(iptr)(cities + param_3),param_3,
                                         (int)game.num_cities,param_5,param_6,param_7,param_8,0x58);
    break;
  case 0x3b:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,param_5,0,0,0,0);
    break;
  case 0x3c:
    if (param_3 == -1) {
      local_c = (void *)net_msg_build_packet(param_1,0,0xffffffff,0,0,0,0,0,0);
    }
    else {
      local_c = (void *)net_msg_build_packet(param_1,(iptr)(cities + param_3),param_3,
                                           (int)game.num_cities,param_5,param_6,param_7,param_8,0x58
                                          );
    }
    break;
  case 0x3d:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,param_5,param_6,0,0,0);
    break;
  case 0x3e:
    if (param_3 == -1) {
      local_c = (void *)net_msg_build_packet(param_1,0,0xffffffff,0,0,0,0,0,0);
    }
    else {
      local_c = (void *)net_msg_build_packet(param_1,(iptr)(units + param_3),param_3,
                                           (int)game.num_units,param_5,param_6,param_7,param_8,0x20)
      ;
    }
    break;
  case 0x3f:
  case 0x4b:
  case 0x4d:
  case 0x4f:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,0,0,0,0,0,0);
    break;
  case 0x40:
  case 0x4c:
  case 0x4e:
  case 0x50:
    net_msg_header_init(local_984,param_1);
    cVar1 = net_session_send_to(&net_session,param_2,(iptr)local_984);
    return (int)cVar1;
  case 0x41:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,param_5,0,0,0,0);
    break;
  case 0x42:
    net_msg_header_init(local_994,param_1);
    cVar1 = net_session_send_to(&net_session,param_2,(iptr)local_994);
    return (int)cVar1;
  case 0x43:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,0,0,0,0,0,0);
    break;
  case 0x44:
    net_msg_header_init(local_9a4,param_1);
    cVar1 = net_session_send_to(&net_session,param_2,(iptr)local_9a4);
    return (int)cVar1;
  case 0x45:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,param_5,0,0,0,0);
    break;
  case 0x46:
    net_msg_header_init(local_9b4,param_1);
    cVar1 = net_session_send_to(&net_session,param_2,(iptr)local_9b4);
    return (int)cVar1;
  case 0x47:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,param_5,param_6,param_7,0,0);
    break;
  case 0x48:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,0,0,0,0,0,0);
    break;
  case 0x49:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,0,0,0,0,0);
    break;
  case 0x4a:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,0,0,0,0,0,0);
    break;
  case 0x51:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,param_5,param_6,param_7,0,0);
    break;
  case 0x52:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,0,0,0,0,0,0);
    break;
  case 0x53:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,0,0,0,0,0);
    break;
  case 0x54:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,0,0,0,0,0,0);
    break;
  case 0x55:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,param_5,param_6,param_7,0,0);
    break;
  case 0x56:
  case 0x57:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,0,0,0,0,0,0);
    break;
  case 0x58:
    net_msg_header_init(local_9f4,param_1);
    cVar1 = net_session_send_to(&net_session,param_2,(iptr)local_9f4);
    return (int)cVar1;
  case 0x59:
    local_c = (void *)net_msg_build_packet(param_1,ADDR(0x6d1190, ((u8 *)&g.d_006d1190)),0,0,0,0,0,0,net_batch_used_dwords << 2);
    break;
  case 0x5a:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,param_5,param_6,param_7,param_8,0
                                        );
    break;
  case 0x5b:
  case 0x65:
  case 0x66:
  case 0xa3:
    net_msg_header_init(local_a24,param_1);
    cVar1 = net_session_send_to(&net_session,param_2,(iptr)local_a24);
    return (int)cVar1;
  case 0x5d:
  case 0x5e:
    net_msg_header_init(local_8d8,param_1);
    cVar1 = net_session_send_to(&net_session,param_2,(iptr)local_8d8);
    return (int)cVar1;
  case 0x5f:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,0,0,0,0,0,0);
    break;
  case 0x60:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,0,0,0,0,0);
    break;
  case 0x61:
  case 0x62:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,0,0,0,0,0,0);
    break;
  case 99:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,param_5,0,0,0,0);
    break;
  case 100:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,param_5,param_6,param_7,0,0);
    break;
  case 0x68:
    sVar2 = _strlen((char *)param_9);
    local_c = (void *)net_msg_build_packet(param_1,param_9,param_3,param_4,param_5,0,0,0,sVar2 + 1);
    break;
  case 0x69:
    net_msg_whose_turn_init(local_910,param_3);
    main_view_timer_cache_i32 = 0xffffffff;
    frame_wnd_draw_caption((FrameWindow *)&map_views);
    local_8fc = main_view_frame_left;
    local_8f8 = main_view_frame_top;
    local_8f4 = main_view_frame_right;
    local_8f0 = main_view_client_top;
    wnd_blit_surface_rect((DibSurface *)&map_views,(iptr)&local_8fc);
    cVar1 = net_session_send_to(&net_session,param_2,(iptr)local_910);
    return (int)cVar1;
  case 0x6a:
    local_c = (void *)net_msg_build_packet(param_1,param_10,param_3,param_4,param_5,param_6,param_7,0,
                                         0);
    break;
  case 0x6b:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,param_5,0,0,0,0);
    break;
  case 0x6c:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,0,0,0,0,0,0);
    break;
  case 0x6d:
    net_msg_header_init(local_754,param_1);
    cVar1 = net_session_send_to(&net_session,param_2,(iptr)local_754);
    return (int)cVar1;
  case 0x6e:
    net_msg_header_init(local_764,param_1);
    cVar1 = net_session_send_to(&net_session,param_2,(iptr)local_764);
    return (int)cVar1;
  case 0x6f:
    net_msg_header_init(local_774,param_1);
    cVar1 = net_session_send_to(&net_session,param_2,(iptr)local_774);
    return (int)cVar1;
  case 0x70:
    local_c = (void *)net_msg_build_packet(param_1,(iptr)(units + param_3),param_3,param_4,param_5,
                                         param_6,param_7,param_8,0x20);
    break;
  case 0x71:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,param_5,0,0,0,0);
    break;
  case 0x72:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,0,0,0,0,0);
    break;
  case 0x73:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,param_5,param_6,0,0,0);
    break;
  case 0x74:
    net_msg_header_init(local_920,param_1);
    cVar1 = net_session_send_to(&net_session,param_2,(iptr)local_920);
    return (int)cVar1;
  case 0x75:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,0,0,0,0,0);
    break;
  case 0x76:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,param_5,param_6,0,0,0);
    break;
  case 0x77:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,0,0,0,0,0,0);
    break;
  case 0x78:
    net_msg_header_init(local_930,param_1);
    cVar1 = net_session_send_to(&net_session,param_2,(iptr)local_930);
    return (int)cVar1;
  case 0x79:
    net_msg_header_init(local_940,param_1);
    cVar1 = net_session_send_to(&net_session,param_2,(iptr)local_940);
    return (int)cVar1;
  case 0x7a:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,0,0,0,0,0);
    break;
  case 0x7b:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,0,0,0,0,0,0);
    break;
  case 0x7c:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,param_5,0,0,0,0);
    break;
  case 0x7d:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,0,0,0,0,0);
    break;
  case 0x7e:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,0,0,0,0,0);
    break;
  case 0x7f:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,0,0,0,0,0,0);
    break;
  case 0x80:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,0,0,0,0,0,0);
    break;
  case 0x82:
    cVar1 = net_session_send_to(&net_session,param_2,param_10);
    if (cVar1 == '\0') {
      return 0;
    }
    return *(i32 *)(param_10 + 8);
  case 0x83:
  case 0x84:
  case 0x85:
    net_msg_header_init(local_964,param_1);
    cVar1 = net_session_send_to(&net_session,param_2,(iptr)local_964);
    return (int)cVar1;
  case 0x86:
    cVar1 = net_session_send_to(&net_session,param_2,param_10);
    if (cVar1 == '\0') {
      return 0;
    }
    return *(i32 *)(param_10 + 8);
  case 0x87:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,param_5,0,0,0,0);
    break;
  case 0x88:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,0,0,0,0,0,0);
    break;
  case 0x89:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,0,0,0,0,0,0);
    break;
  case 0x8a:
    net_msg_header_init(local_974,param_1);
    cVar1 = net_session_send_to(&net_session,param_2,(iptr)local_974);
    return (int)cVar1;
  case 0x8b:
    net_msg_header_init(local_9d4,param_1);
    cVar1 = net_session_send_to(&net_session,param_2,(iptr)local_9d4);
    return (int)cVar1;
  case 0x8c:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,0,0,0,0,0,0);
    break;
  case 0x8d:
  case 0x8e:
    net_msg_header_init(local_9e4,param_1);
    cVar1 = net_session_send_to(&net_session,param_2,(iptr)local_9e4);
    return (int)cVar1;
  case 0x8f:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,0,0,0,0,0,0);
    break;
  case 0x90:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,param_5,param_6,param_7,0,0);
    break;
  case 0x91:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,param_5,param_6,0,0,0);
    break;
  case 0x92:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,param_5,param_6,param_7,0,0);
    break;
  case 0x93:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,param_5,param_6,0,0,0);
    break;
  case 0x94:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,param_5,param_6,0,0,0);
    break;
  case 0x95:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,param_5,param_6,0,0,0);
    break;
  case 0x96:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,param_5,param_6,0,0,0);
    break;
  case 0x97:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,param_5,param_6,param_7,param_8,0
                                        );
    break;
  case 0x98:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,param_5,0,0,0,0);
    break;
  case 0x99:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,param_5,param_6,0,0,0);
    break;
  case 0x9a:
  case 0xa0:
  case 0xa1:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,0,0,0,0,0);
    break;
  case 0x9b:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,param_5,param_6,0,0,0);
    break;
  case 0x9c:
  case 0x9d:
  case 0x9e:
    net_msg_header_init(local_a04,param_1);
    cVar1 = net_session_send_to(&net_session,param_2,(iptr)local_a04);
    return (int)cVar1;
  case 0x9f:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,0,0,0,0,0,0);
    break;
  case 0xa2:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,0,0,0,0,0,0);
    break;
  case 0xa4:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,0,0,0,0,0);
    break;
  case 0xa5:
  case 0xa6:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,0,0,0,0,0);
    break;
  case 0xa7:
  case 0xa8:
    local_c = (void *)net_msg_build_packet(param_1,0,param_3,param_4,0,0,0,0,0);
  }
  if (local_c == (void *)0x0) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62a7e8, ((u8 *)&g.d_0062a7e8)),ADDR(0x62a7c4, ((u8 *)&g.d_0062a7c4)),0x523);
    local_8 = 0;
  }
  else {
    cVar1 = net_session_send_to(&net_session,param_2,(iptr)local_c);
    local_8 = (int)cVar1;
    operator_delete(local_c);
  }
  return local_8;
}
#undef loaded_file_kind
#undef loaded_file_name
#undef loaded_file_subdir
#undef net_batch_used_dwords
#undef net_claimed_civs_mask
#undef net_host_flag
#undef net_session_phase
#undef main_view_timer_cache_i32
#undef local_a24
#undef local_a14
#undef local_a04
#undef local_9f4
#undef local_9e4
#undef local_9d4
#undef local_9c4
#undef local_9b4
#undef local_9a4
#undef local_994
#undef local_984
#undef local_974
#undef local_964
#undef local_950
#undef local_940
#undef local_930
#undef local_920
#undef local_910
#undef local_8fc
#undef local_8f8
#undef local_8f4
#undef local_8f0
#undef local_8ec
#undef local_8d8
#undef local_8c8
#undef local_8b8
#undef local_784
#undef local_774
#undef local_764
#undef local_754
#undef local_744
#undef local_734
#undef local_730
#undef local_72c
#undef local_6c8
#undef local_6b8
#undef local_448
#undef local_438
#undef local_436
#undef local_332
#undef local_22c
#undef local_21c
#undef local_88
#undef local_84
#undef local_c
#undef local_8

/* 0046d5a0 auto */
NetMsgHeader * __thiscall net_msg_header_init(NetMsgHeader *this,u32 param_1)

{
  this[1].field_0 = 0x10;
  this->msg_magic = 0x66606660;
  this->msg_type = param_1;
  return this;
}

/* 0046d5f0 auto */
#define prefs_net_ip_address (*(i8 *)((u8 *)&g.d_006665b0))
NetMsgHeader * __thiscall net_msg_init_header(NetMsgHeader *this,u32 param_1,iptr param_2)

{
  net_msg_addr_header_init(this,0);
  this[0xe].field_0 = param_1;
  _memset(this + 6,0,0x20);
  _strncpy((char *)(this + 6),(char *)param_2,0x20);
  _memset(this + 10,0,0x20);
  _strncpy((char *)(this + 10),&prefs_net_ip_address,0x20);
  this[1].field_0 = 0x74;
  return this;
}
#undef prefs_net_ip_address

/* 0046d6a0 auto */
#define prefs_net_ip_address (*(i8 *)((u8 *)&g.d_006665b0))
NetMsgHeader * __thiscall net_msg_addr_header_init(NetMsgHeader *this,i32 param_1)

{
  net_msg_header_init(this,param_1);
  _memset(this + 2,0,0x20);
  _strncpy((char *)(this + 2),&prefs_net_ip_address,0x20);
  this[1].field_0 = 0x30;
  return this;
}
#undef prefs_net_ip_address

/* 0046d720 auto */
NetMsgHeader * __thiscall net_msg_server_info_init(NetMsgHeader *this)

{
  net_msg_init_header(this,2,ADDR(0x62af0c, ((u8 *)&g.d_0062af0c)));
  net_fill_game_info((iptr)&this[0xe].field_4);
  this[1].field_0 = 0x198;
  return this;
}

/* 0046d780 auto */
#define prefs_net_ip_address (*(i8 *)((u8 *)&g.d_006665b0))
#define prefs_net_player_name (*(i8 *)((u8 *)&g.d_00666570))
NetMsgHeader * __thiscall net_msg_player_list_node_init(NetMsgHeader *this,u32 param_1)

{
  net_msg_header_init(this,0x2f);
  this[2].field_0 = param_1;
  _memset(&this[2].field_4,0,0x20);
  _strncpy((char *)&this[2].field_4,&prefs_net_ip_address,0x20);
  crt_strcpy(&this[6].field_4,&prefs_net_player_name);
  this[10].field_4 = 0;
  this[0xb].field_0 = 0;
  *(i8 *)&this[0xb].field_4 = 0;
  *(i8 *)((int)&this[0xb].field_4 + 1) = 0;
  this[0xc].field_0 = 0xffffffff;
  this[1].field_0 = 100;
  return this;
}
#undef prefs_net_ip_address
#undef prefs_net_player_name

/* 0046d860 auto */
NetMsgHeader * __thiscall net_msg_player_list_init(NetMsgHeader *this)

{
  net_msg_header_init(this,4);
  this[1].field_0 = 0x280;
  return this;
}

/* 0046d8a0 auto */
NetMsgHeader * __thiscall net_msg_server_path_init(NetMsgHeader *this)

{
  net_msg_header_init(this,6);
  this[1].field_0 = 0x21c;
  return this;
}

/* 0046d8e0 auto */
NetMsgHeader * __thiscall net_msg_server_answer_init(NetMsgHeader *this)

{
  net_msg_header_init(this,0x13);
  net_fill_game_info((iptr)(this + 2));
  this[1].field_0 = 0x134;
  return this;
}

/* 0046d930 auto */
NetMsgHeader * __thiscall net_msg_whose_turn_init(NetMsgHeader *this,u32 param_1)

{
  net_msg_header_init(this,0x69);
  this[2].field_0 = param_1;
  this[1].field_0 = 0x14;
  return this;
}

/* 0047e0e5 auto */
#define net_stacked_draw_count (*(uint *)((u8 *)&g.d_006ad90c))
#define local_24 (*(i8 (*)[28])(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(32)))
int __cdecl net_stacked_draw_push(int param_1,iptr param_2,iptr param_3)

{
  int iVar1;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((net_stacked_draw_last == net_stacked_draw_first) && (net_stacked_draw_count != 0)) {
    dbg_log(ADDR(0x62bcf0, ((u8 *)&g.d_0062bcf0)));
    if (unit_stack_check_enabled != 0) {
      net_stacked_draw_last = (net_stacked_draw_first + 1) % 100;
    }
    else {
      net_stacked_draw_first = 0;
      net_stacked_draw_last = 0;
    }
    net_stacked_draw_count = (uint)(unit_stack_check_enabled != 0);
    net_stacked_draw_push(0xa3,(iptr)local_24,0);
    iVar1 = net_stacked_draw_push(0x74,(iptr)local_24,0);
  }
  else {
    if ((net_stacked_draw_first < 0) || (99 < net_stacked_draw_first)) {
      err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62bd38, ((u8 *)&g.d_0062bd38)),ADDR(0x62bd14, ((u8 *)&g.d_0062bd14)),0x5a);
    }
    if ((net_stacked_draw_last < 0) || (99 < net_stacked_draw_last)) {
      err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62bdac, ((u8 *)&g.d_0062bdac)),ADDR(0x62bd88, ((u8 *)&g.d_0062bd88)),0x5b);
    }
    *(int *)(&net_stacked_draw_kinds + net_stacked_draw_last * 0x40) = param_1;
    for (local_8 = 0; local_8 < 7; local_8++) {
      *(i32 *)(&net_stacked_draw_args + local_8 * 4 + net_stacked_draw_last * 0x40) =
           *(i32 *)(param_2 + local_8 * 4);
    }
    if (param_1 == 0x70) {
      crt_memcpy(net_stacked_draw_last * 0x40 + ADDR(0x6ad940, ((u8 *)&g.d_006ad934 + 12)),param_3,0x20);
    }
    net_stacked_draw_count++;
    if ((int)net_stacked_draw_peak < (int)net_stacked_draw_count) {
      net_stacked_draw_peak = net_stacked_draw_count;
    }
    iVar1 = (net_stacked_draw_last + 1) / 100;
    net_stacked_draw_last = (net_stacked_draw_last + 1) % 100;
  }
  return iVar1;
}
#undef net_stacked_draw_count
#undef local_24
#undef local_8

/* 0047e2b3 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define net_move_anim_sound (*(i32 *)((u8 *)&g.d_006ad6a4))
#define net_move_anim_sound_arg (*(i32 *)((u8 *)&g.d_006ad6a8))
#define net_stacked_draw_count (*(int *)((u8 *)&g.d_006ad90c))
#define unit_move_anim_active (*(i32 *)((u8 *)&g.d_00636058))
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
int __cdecl net_stacked_draw_run_next(void)

{
  int y;
  iptr iVar2;
  iptr iVar3;
  iptr unit;
  iptr unit2;
  int iVar6;
  int x;
  i32 uVar8;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  switch(*(i32 *)(&net_stacked_draw_kinds + net_stacked_draw_first * 0x40)) {
  case 0x70:
    x = *(int *)(&net_stacked_draw_arg1 + net_stacked_draw_first * 0x40);
    y = *(int *)(&net_stacked_draw_arg2 + net_stacked_draw_first * 0x40);
    unit2 = *(iptr *)(&net_stacked_draw_arg3 + net_stacked_draw_first * 0x40);
    unit_stack_validate(*(iptr *)(&net_stacked_draw_args + net_stacked_draw_first * 0x40));
    iVar2 = mapviews_tile_visible(x,y);
    if (iVar2 != 0) {
      crt_memcpy(&stacked_draw_unit_copy,net_stacked_draw_first * 0x40 + ADDR(0x6ad940, ((u8 *)&g.d_006ad934 + 12)),0x20);
      stacked_draw_unit_prev = -1;
      stacked_draw_unit_next = -1;
      mapviews_ensure_visible(x,y,(int)stacked_draw_unit_owner);
      if (*(int *)(&net_stacked_draw_arg4 + net_stacked_draw_first * 0x40) == -1) {
        snd_play_effect(99,1,0,0);
      }
      iVar3 = tile_at(x,y);
      uVar8 = 2;
      unit = tile_first_unit(x,y);
      local_8 = unit_stack_sum(unit,uVar8);
      if ((stacked_draw_unit_copy != x) || (stacked_draw_unit_y != y)) {
        local_8++;
      }
      if (local_8 == 1) {
        *(byte *)(iVar3 + 1) = *(byte *)(iVar3 + 1) & 0xfe;
      }
      else if (1 < local_8) {
        anim_origin_x = (int)stacked_draw_unit_copy;
        anim_origin_y = (int)stacked_draw_unit_y;
        iVar6 = unit_stack_sum(0x801,5);
        if (iVar6 == 0) {
          if (stacked_draw_unit_next < 0) {
            if (stacked_draw_unit_prev < 0) {
              *(byte *)(iVar3 + 1) = *(byte *)(iVar3 + 1) & 0xfe;
            }
            else {
              anim_origin_stack_unit = (iptr)stacked_draw_unit_prev;
            }
          }
          else {
            anim_origin_stack_unit = (iptr)stacked_draw_unit_next;
          }
        }
        else {
          iVar6 = unit_stack_sum(0x801,5);
          if (iVar6 < 2) {
            *(byte *)(iVar3 + 1) = *(byte *)(iVar3 + 1) & 0xfe;
          }
          else {
            anim_origin_stack_unit = unit_stack_first(0x801);
            do {
              if ((anim_origin_stack_unit != 0x801) &&
                 (unit_types[units[anim_origin_stack_unit].type].domain == 2)) goto LAB_0047e5c2;
              anim_origin_stack_unit = (iptr)units[anim_origin_stack_unit].next_in_stack;
            } while (-1 < anim_origin_stack_unit);
            *(byte *)(iVar3 + 1) = *(byte *)(iVar3 + 1) & 0xfe;
          }
        }
      }
LAB_0047e5c2:
      unit_move_anim_active = 1;
      map_animate_unit_move(0x801,x,y,unit2,net_move_anim_sound,net_move_anim_sound_arg);
      unit_move_anim_active = 0;
      uVar8 = 2;
      unit2 = tile_first_unit(x,y);
      iVar6 = unit_stack_sum(unit2,uVar8);
      if (iVar6 != 0) {
        if (net_host_flag == '\0') {
          *(byte *)(iVar3 + 1) = *(byte *)(iVar3 + 1) | 1;
        }
        else {
          tile_set_improvements(x,y,1,1,1);
        }
      }
    }
    break;
  case 0x71:
    x = tile_visible_to(*(i32 *)(&net_stacked_draw_args + net_stacked_draw_first * 0x40),
                            *(i32 *)(&net_stacked_draw_arg1 + net_stacked_draw_first * 0x40),human_civ);
    if (x != 0) {
      mapviews_ensure_visible(*(i32 *)(&net_stacked_draw_args + net_stacked_draw_first * 0x40),
                         *(i32 *)(&net_stacked_draw_arg1 + net_stacked_draw_first * 0x40),
                         *(iptr *)(&net_stacked_draw_arg2 + net_stacked_draw_first * 0x40));
    }
    break;
  case 0x72:
    map_redraw_tile_all_views(*(i32 *)(&net_stacked_draw_args + net_stacked_draw_first * 0x40),
                       *(i32 *)(&net_stacked_draw_arg1 + net_stacked_draw_first * 0x40));
    break;
  case 0x73:
    map_redraw_combat_tiles(*(i32 *)(&net_stacked_draw_args + net_stacked_draw_first * 0x40),
                       *(i32 *)(&net_stacked_draw_arg1 + net_stacked_draw_first * 0x40),
                       *(i32 *)(&net_stacked_draw_arg2 + net_stacked_draw_first * 0x40),
                       *(i32 *)(&net_stacked_draw_arg3 + net_stacked_draw_first * 0x40));
    break;
  case 0x74:
    map_redraw_all_views(human_civ,1);
    break;
  case 0x75:
    map_redraw_neighbors_all_views(*(i32 *)(&net_stacked_draw_args + net_stacked_draw_first * 0x40),
                       *(iptr *)(&net_stacked_draw_arg1 + net_stacked_draw_first * 0x40));
    break;
  case 0x76:
    map_redraw_area_all_views(*(i32 *)(&net_stacked_draw_args + net_stacked_draw_first * 0x40),
                       *(i32 *)(&net_stacked_draw_arg1 + net_stacked_draw_first * 0x40),
                       *(i32 *)(&net_stacked_draw_arg2 + net_stacked_draw_first * 0x40),
                       *(iptr *)(&net_stacked_draw_arg3 + net_stacked_draw_first * 0x40),1);
    break;
  case 0x7c:
    x = mapviews_tile_visible(*(iptr *)(&net_stacked_draw_args + net_stacked_draw_first * 0x40),
                               *(iptr *)(&net_stacked_draw_arg1 + net_stacked_draw_first * 0x40));
    if (x != 0) {
      map_animate_explosion(*(i32 *)(&net_stacked_draw_args + net_stacked_draw_first * 0x40),
                         *(i32 *)(&net_stacked_draw_arg1 + net_stacked_draw_first * 0x40),
                         *(i32 *)(&net_stacked_draw_arg2 + net_stacked_draw_first * 0x40));
    }
    break;
  case 0x7d:
    x = mapviews_tile_visible(*(iptr *)(&net_stacked_draw_args + net_stacked_draw_first * 0x40),
                               *(iptr *)(&net_stacked_draw_arg1 + net_stacked_draw_first * 0x40));
    if (x != 0) {
      map_animate_nuke(*(i32 *)(&net_stacked_draw_args + net_stacked_draw_first * 0x40),
                         *(i32 *)(&net_stacked_draw_arg1 + net_stacked_draw_first * 0x40));
    }
    break;
  case 0xa3:
    nm_abort_kaboom_count++;
  }
  net_stacked_draw_count--;
  x = net_stacked_draw_first + 1;
  net_stacked_draw_first = x % 100;
  return x / 100;
}
#undef human_civ
#undef net_host_flag
#undef net_move_anim_sound
#undef net_move_anim_sound_arg
#undef net_stacked_draw_count
#undef unit_move_anim_active
#undef local_8

/* 0047e94e auto */
#define blocked_input_char (*(i8 *)((u8 *)&g.d_006c31c8))
#define blocked_input_char_pending (*(int *)((u8 *)&g.d_006c31c4))
#define city_window_closed (*(int *)((u8 *)&g.d_006aa75c))
#define city_window_refresh_locked (*(int *)((u8 *)&g.d_006aa760))
#define dlg_pending_idle_callback (*(i8 * *)((u8 *)&g.d_00635a3c))
#define game_over_reason (*(uptr *)((u8 *)&g.d_0064b1ac))
#define game_setup_complete (*(int *)((u8 *)&g.d_00654fd8))
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define loaded_file_kind (*(i16 *)((u8 *)&g.d_006ad6ac))
#define loaded_file_name (*(i8 *)((u8 *)&g.d_006ad6ae))
#define loaded_file_subdir (*(i8 *)((u8 *)&g.d_006ad7b2))
#define main_view_timer_shown (*(i32 *)((u8 *)&g.d_0066c988))
#define mp_double_moves (*(short *)((u8 *)&g.d_00654fae))
#define mp_double_production (*(short *)((u8 *)&g.d_00654fac))
#define mp_meeting_pending (*(int *)((u8 *)&g.d_00626a2c))
#define mp_meeting_reply (*(uptr *)((u8 *)&g.d_0063f278))
#define mp_simultaneous_moves (*(char *)((u8 *)&g.d_006ad684))
#define mp_simultaneous_setting (*(short *)((u8 *)&g.d_00654c7c))
#define mp_turn_civ (*(i8 *)((u8 *)&g.d_006ad578))
#define mp_turn_time_limit_ms (*(uptr *)((u8 *)&g.d_00654b70))
#define net_bribe_answer (*(uptr *)((u8 *)&g.d_006a1870))
#define net_can_escape_reply (*(uptr *)((u8 *)&g.d_006acb38))
#define net_city_deleted_ack (*(i32 *)((u8 *)&g.d_006c90c8))
#define net_claimed_civs_mask (*(ushort *)((u8 *)&g.d_00654fb0))
#define net_drag_hold (*(i8 *)((u8 *)&g.d_006c31d0))
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define net_host_handoff_stage (*(char *)((u8 *)&g.d_006ad698))
#define net_kill_or_quit_ack (*(i32 *)((u8 *)&g.d_006c90b4))
#define net_lobby_list (*(int * *)((u8 *)&g.d_006ad10c))
#define net_max_players (*(int *)((u8 *)&g.d_006c3164))
#define net_move_anim_sound (*(uptr *)((u8 *)&g.d_006ad6a4))
#define net_move_anim_sound_arg (*(uptr *)((u8 *)&g.d_006ad6a8))
#define net_popup_queue_head (*(int *)((u8 *)&g.d_00631130))
#define net_session_phase (*(uptr *)((u8 *)&g.d_006ad640))
#define net_slot_civs (*(i32 *)((u8 *)&g.d_006ad35c))
#define net_stacked_draw_count (*(uint *)((u8 *)&g.d_006ad90c))
#define net_unit_deleted_ack (*(i32 *)((u8 *)&g.d_006c90c0))
#define net_vote_status (*(i32 *)((u8 *)&g.d_006ad670))
#define nm_bottomed_count (*(i32 *)((u8 *)&g.d_006c90f0))
#define nm_continue_after_join_count (*(i32 *)((u8 *)&g.d_006c9178))
#define nm_kill_civ_ack_result (*(uptr *)((u8 *)&g.d_006c9168))
#define nm_new_civ_ack_result (*(uptr *)((u8 *)&g.d_006c9164))
#define nm_safely_deleted_count (*(i32 *)((u8 *)&g.d_006c9118))
#define nm_ship_stacked_result (*(uptr *)((u8 *)&g.d_006c9108))
#define nm_stacker_ack_count (*(i32 *)((u8 *)&g.d_006c914c))
#define nm_unit_created_result (*(uptr *)((u8 *)&g.d_006c90d8))
#define nm_unit_picked_up_count (*(i32 *)((u8 *)&g.d_006c90e0))
#define nm_unit_put_down_count (*(i32 *)((u8 *)&g.d_006c90e8))
#define nm_unit_relocated_count (*(i32 *)((u8 *)&g.d_006c90f8))
#define nm_unit_stacked_count (*(i32 *)((u8 *)&g.d_006c9110))
#define nm_visibly_deleted_count (*(i32 *)((u8 *)&g.d_006c9120))
#define nm_wonder_acquired_result (*(uptr *)((u8 *)&g.d_006c9100))
#define parley_other_civ (*(uptr *)((u8 *)&g.d_0067a8c0))
#define parley_reveal_city_prompt_open (*(int *)((u8 *)&g.d_0063113c))
#define parley_reveal_units_prompt_open (*(int *)((u8 *)&g.d_00631138))
#define prefs_net_player_name (*(i8 *)((u8 *)&g.d_00666570))
#define saved_turn_civ (*(i8 *)((u8 *)&g.d_00654fa4))
#define scenario_event_count (*(uptr *)((u8 *)&g.d_0064b998))
#define scenario_events_loaded (*(uptr *)((u8 *)&g.d_00627670))
#define spaceship_winner_civ (*(uptr *)((u8 *)&g.d_0062c5b4))
#define turn_resume_civ (*(i8 *)((u8 *)&g.d_00628048))
#define main_view_timer_cache_i32 (*(i32 *)((u8 *)&g.d_0066c990))
#define mp_turn_civ_i32 (*(i32 *)((u8 *)&g.d_006ad578))
#define nm_lock_nation_count_i32 (*(i32 *)((u8 *)&g.d_006c90a0))
#define local_748 (*(int * *)(frame_ + FRAME_OFF(0)))
#define local_740 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_738 (*(iptr *)(frame_ + FRAME_OFF(16)))
#define local_734 (*(iptr *)(frame_ + FRAME_OFF(20)))
#define local_718 (*(i8 *)(frame_ + FRAME_OFF(48)))
#define local_714 (*(i8 *)(frame_ + FRAME_OFF(52)))
#define local_6fc (*(i8 (*)[28])(frame_ + FRAME_OFF(76)))
#define local_6e0 (*(i32 *)(frame_ + FRAME_OFF(104)))
#define local_6dc (*(i32 *)(frame_ + FRAME_OFF(108)))
#define local_6d8 (*(i32 *)(frame_ + FRAME_OFF(112)))
#define local_6d4 (*(i32 *)(frame_ + FRAME_OFF(116)))
#define local_6d0 (*(uint *)(frame_ + FRAME_OFF(120)))
#define local_6cc (*(u8 *)(frame_ + FRAME_OFF(124)))
#define unit2 (*(iptr *)(frame_ + FRAME_OFF(128)))
#define local_6c4 (*(uint * *)(frame_ + FRAME_OFF(132)))
#define local_6c0 (*(int *)(frame_ + FRAME_OFF(136)))
#define local_6bc (*(int *)(frame_ + FRAME_OFF(140)))
#define local_6b8 (*(int *)(frame_ + FRAME_OFF(144)))
#define local_6b0 (*(i16 *)(frame_ + FRAME_OFF(152)))
#define local_6ac (*(i8 *)(frame_ + FRAME_OFF(156)))
#define local_6a8 (*(int *)(frame_ + FRAME_OFF(160)))
#define local_6a4 (*(int *)(frame_ + FRAME_OFF(164)))
#define local_6a0 (*(int *)(frame_ + FRAME_OFF(168)))
#define local_69c (*(int *)(frame_ + FRAME_OFF(172)))
#define local_698 (*(uint *)(frame_ + FRAME_OFF(176)))
#define local_694 (*(int *)(frame_ + FRAME_OFF(180)))
#define local_690 (*(u16 *)(frame_ + FRAME_OFF(184)))
#define local_68c (*(i8 *)(frame_ + FRAME_OFF(188)))
#define local_688 (*(i8 *)(frame_ + FRAME_OFF(192)))
#define local_684 (*(uptr *)(frame_ + FRAME_OFF(196)))
#define local_680 (*(i16 *)(frame_ + FRAME_OFF(200)))
#define local_67c (*(u32 *)(frame_ + FRAME_OFF(204)))
#define local_678 (*(int *)(frame_ + FRAME_OFF(208)))
#define local_674 (*(Dialog *)(frame_ + FRAME_OFF(212)))
#define local_380 (*(int *)(frame_ + FRAME_OFF(968)))
#define local_37c (*(Dialog *)(frame_ + FRAME_OFF(972)))
#define local_88 (*(u32 *)(frame_ + FRAME_OFF(1728)))
#define local_84 (*(int * *)(frame_ + FRAME_OFF(1732)))
#define y4 (*(int *)(frame_ + FRAME_OFF(1736)))
#define x3 (*(int *)(frame_ + FRAME_OFF(1740)))
#define local_78 (*(i32 *)(frame_ + FRAME_OFF(1744)))
#define local_74 (*(i32 *)(frame_ + FRAME_OFF(1748)))
#define local_70 (*(i32 *)(frame_ + FRAME_OFF(1752)))
#define local_6c (*(i32 *)(frame_ + FRAME_OFF(1756)))
#define local_68 (*(int *)(frame_ + FRAME_OFF(1760)))
#define local_64 (*(u32 *)(frame_ + FRAME_OFF(1764)))
#define local_60 (*(uint *)(frame_ + FRAME_OFF(1768)))
#define local_5c (*(uint *)(frame_ + FRAME_OFF(1772)))
#define local_58 (*(int *)(frame_ + FRAME_OFF(1776)))
#define unit4 (*(iptr *)(frame_ + FRAME_OFF(1780)))
#define local_50 (*(int *)(frame_ + FRAME_OFF(1784)))
#define local_4c (*(i32 *)(frame_ + FRAME_OFF(1788)))
#define local_48 (*(uint * *)(frame_ + FRAME_OFF(1792)))
#define local_44 (*(i8 *)(frame_ + FRAME_OFF(1796)))
#define unit (*(uptr *)(frame_ + FRAME_OFF(1800)))
#define local_3c (*(uptr *)(frame_ + FRAME_OFF(1804)))
#define unit3 (*(uptr *)(frame_ + FRAME_OFF(1808)))
#define y2 (*(iptr *)(frame_ + FRAME_OFF(1812)))
#define x2 (*(iptr *)(frame_ + FRAME_OFF(1816)))
#define y3 (*(int *)(frame_ + FRAME_OFF(1820)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(1824)))
#define local_24 (*(int * *)(frame_ + FRAME_OFF(1828)))
#define local_20 (*(int * *)(frame_ + FRAME_OFF(1832)))
#define local_1c (*(char *)(frame_ + FRAME_OFF(1836)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(1840)))
#define local_14 (*(iptr *)(frame_ + FRAME_OFF(1844)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1848)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1852)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1856)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall net_process_messages(NetSession *this,int param_1,int param_2)

{
  int *piVar1;
  u8 *puVar2;
  char *pcVar3;
  char civ;
  iptr iVar6;
  iptr iVar7;
  u32 uVar6;
  i32 x;
  iptr iVar8;
  int city;
  bool bVar10;
  uptr civ2;
  uptr unit5;
  i8 frame_[FRAME_OFF(1864)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  local_1c = '\0';
  local_44 = 0;
  if ((((((((this[0xf6].field_4 == 0) && (*(int *)this[0xf7].pad_0 == 0)) &&
          (this[0xf7].field_4 == 0)) &&
         ((*(int *)this[0xf8].pad_0 == 0 && (this[0xf8].field_4 == 0)))) &&
        (*(int *)this[0xf9].pad_0 == 0)) &&
       (((*(int *)this[0xfa].pad_0 == 0 && (this[0xfa].field_4 == 0)) &&
        ((*(int *)this[0xfb].pad_0 == 0 &&
         (((this[0xfb].field_4 == 0 && (*(int *)this[0xfc].pad_0 == 0)) && (this[0xfc].field_4 == 0)
          ))))))) && ((*(int *)this[0xfd].pad_0 == 0 && (this[0xfd].field_4 == 0)))) &&
     ((*(int *)this[0xfe].pad_0 == 0 &&
      (((this[0xfe].field_4 == 0 && (*(int *)this[0xff].pad_0 == 0)) &&
       ((this[0xff].field_4 == 0 && (iVar6 = XD_InFlushSendBuffer(), iVar6 == 0)))))))) {
    if (((this[0x2c14].field_4 != 0) && (net_deferred_input_busy == '\0')) &&
       (iVar7 = XD_InFlushSendBuffer(), iVar7 == 0)) {
      local_64 = this[0x2c14].field_4;
      net_deferred_input_busy = 1;
      dbg_log(ADDR(0x62bdf8, ((u8 *)&g.d_0062bdf8)));
      this[0x2c14].field_4 = 0;
      switch(local_64) {
      case 1:
        if (*(short *)(this[0x2c18].field_4 + 0x2dc) != 0) {
          if (this[0x2c18].field_4 == 0) {
            local_734 = 0;
          }
          else {
            local_734 = this[0x2c18].field_4 + 0x48;
          }
          wnd_set_active_child(local_734);
          map_window_click(*(i32 *)this[0x2c15].pad_0,this[0x2c15].field_4,
                             *(i32 *)this[0x2c16].pad_0);
        }
        break;
      case 2:
        if (*(short *)(this[0x2c18].field_4 + 0x2dc) != 0) {
          if (this[0x2c18].field_4 == 0) {
            local_738 = 0;
          }
          else {
            local_738 = this[0x2c18].field_4 + 0x48;
          }
          wnd_set_active_child(local_738);
          map_window_double_click(*(i32 *)this[0x2c15].pad_0,this[0x2c15].field_4);
        }
        break;
      case 4:
        local_68 = blocked_input_char_pending;
        local_60 = CONCAT31((*(i32 *)((char *)&local_60 + 1)),blocked_input_char);
        map_window_key(*(i32 *)this[0x2c15].pad_0);
        if (local_68 == 3) {
          map_window_ascii(local_60);
        }
        break;
      case 5:
        menu_command(*(i32 *)this[0x2c15].pad_0,this[0x2c15].field_4);
        break;
      case 6:
        if (((city_window_closed == 0) && (cities[*(int *)this[0x2c15].pad_0].id != 0)) &&
           ((int)cities[*(int *)this[0x2c15].pad_0].owner == this[0x2c15].field_4)) {
          city_window_on_mouse(*(i32 *)this[0x2c16].pad_0,this[0x2c16].field_4,
                             *(i32 *)this[0x2c17].pad_0);
        }
        break;
      case 7:
        if (((city_window_closed == 0) && (cities[*(int *)this[0x2c15].pad_0].id != 0)) &&
           ((int)cities[*(int *)this[0x2c15].pad_0].owner == this[0x2c15].field_4)) {
          city_button_buy(*(i32 *)this[0x2c16].pad_0);
        }
        break;
      case 8:
        if (((city_window_closed == 0) && (cities[*(int *)this[0x2c15].pad_0].id != 0)) &&
           ((int)cities[*(int *)this[0x2c15].pad_0].owner == this[0x2c15].field_4)) {
          city_button_change(*(i32 *)this[0x2c16].pad_0);
        }
        break;
      case 9:
        if (((city_window_closed == 0) && (cities[*(int *)this[0x2c15].pad_0].id != 0)) &&
           ((int)cities[*(int *)this[0x2c15].pad_0].owner == this[0x2c15].field_4)) {
          city_button_view(*(i32 *)this[0x2c16].pad_0);
        }
        break;
      case 10:
        if (((city_window_closed == 0) && (cities[*(int *)this[0x2c15].pad_0].id != 0)) &&
           ((int)cities[*(int *)this[0x2c15].pad_0].owner == this[0x2c15].field_4)) {
          city_button_rename(*(i32 *)this[0x2c16].pad_0);
        }
      }
      net_deferred_input_busy = '\0';
    }
    *(int *)this[0xb0].pad_0 = *(int *)this[0xb0].pad_0 + 1;
    if ((int)this[0xb0].field_4 < *(int *)this[0xb0].pad_0) {
      this[0xb0].field_4 = *(u32 *)this[0xb0].pad_0;
    }
    while (param_1 != 0) {
      if (((*(int *)this[0x102].pad_0 == 0) && (*(int *)this[0x100].pad_0 == 0)) &&
         (0 < (int)this[0x100].field_4)) {
        this[0x102].pad_0[0] = 1;
        this[0x102].pad_0[1] = '\0';
        this[0x102].pad_0[2] = '\0';
        this[0x102].pad_0[3] = '\0';
        if ((int)this[0x100].field_4 < 0x22) {
          unit4 = 1;
        }
        else {
          unit4 = 2;
        }
        for (; 0 < unit4; unit4--) {
          net_stacked_draw_run_next();
        }
        this[0x102].pad_0[0] = '\0';
        this[0x102].pad_0[1] = '\0';
        this[0x102].pad_0[2] = '\0';
        this[0x102].pad_0[3] = '\0';
      }
      if ((net_msgq_normal_count < 0x12d) && (net_msgq_priority_count < 0x22)) {
        ui_pump_messages();
        param_1--;
      }
      if (net_msgq_priority_count < 0x22) {
        local_740 = param_2;
      }
      else {
        local_740 = 1;
      }
      civ = net_msgq_dequeue
                        ((NetMessageQueue *)(this + 0x2c1a),(iptr)&local_58,(iptr)&local_20,
                         (iptr)&local_5c,local_740);
      if (civ == '\0') break;
      if (local_20 == (int *)0x0) {
        err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62be4c, ((u8 *)&g.d_0062be4c)),ADDR(0x62be28, ((u8 *)&g.d_0062be28)),0x195);
      }
      local_24 = local_20;
      if (*local_20 == 0x66606660) {
        *(int *)(&nm_recv_counts + local_20[1] * 4) = *(int *)(&nm_recv_counts + local_20[1] * 4) + 1;
        if ((0x35 < local_20[1]) && (game_setup_complete == 0)) {
          operator_delete(local_20);
          break;
        }
        local_48 = (uint *)(local_20 + 0xb);
        switch(local_20[1]) {
        case 0:
          local_84 = local_20;
          *(int *)(&nm_recv_counts + local_20[0x1c] * 4) =
               *(int *)(&nm_recv_counts + local_20[0x1c] * 4) + 1;
          if (local_20[0x1c] == 1) {
            if (((*(char *)((int)&this[0x3d].field_4 + 3) != '\0') && (net_host_handoff_stage == '\0')) &&
               (net_connection_type != 0)) {
              net_send_message(2,0,0,0,0,0,0,0,0,0);
            }
          }
          else if (local_20[0x1c] == 2) {
            net_game_list_add(this,(iptr)local_20);
            local_1c = 1;
          }
          break;
        default:
          dbg_log(ADDR(0x62bf14, ((u8 *)&g.d_0062bf14)));
          break;
        case 4:
          crt_memcpy(this + 0x40,local_20 + 4,0x270);
          for (unit4 = 0; unit4 < 7; unit4++) {
            if ((*(char *)((int)this + unit4 * 0x54 + 0x251) != '\0') &&
               (*(int *)((int)this + unit4 * 0x54 + 0x204) == *(int *)this[0x3f].pad_0)) {
              this[0x3f].field_4 = unit4;
              break;
            }
          }
          break;
        case 5:
          uVar6 = timer_ticks();
          this[0xad].field_4 = uVar6;
          break;
        case 6:
          loaded_file_kind = (i16)local_20[4];
          crt_strcpy(&loaded_file_name,(int)local_20 + 0x12);
          crt_strcpy(&loaded_file_subdir,(int)local_24 + 0x116);
          break;
        case 7:
        case 8:
        case 9:
          local_4c = 0x2c;
          local_50 = local_20[4];
          local_18 = local_5c - 0x2c;
          crt_memmove(local_20,local_20 + 0xb,local_18);
          local_20 = (int *)crt_realloc(local_20,local_18);
          diffeng_apply_image(&local_20,local_50);
          break;
        case 10:
          local_4c = 0x2c;
          local_50 = local_20[4];
          local_18 = local_5c - 0x2c;
          crt_memmove(local_20,local_20 + 0xb,local_18);
          local_20 = (int *)crt_realloc(local_20,local_18);
          diffeng_apply_map_header_image(&local_20,local_50);
          break;
        case 0xb:
        case 0xc:
        case 0x11:
          break;
        case 0xd:
          break;
        case 0xe:
          this[0xb2].pad_0[0]++;
          break;
        case 0xf:
          this[0xb2].pad_0[0]++;
          break;
        case 0x10:
          net_players_awaited--;
          break;
        case 0x12:
          net_send_message(0x13,local_58,0,0,0,0,0,0,0,0);
          break;
        case 0x13:
          if (net_session != 0) {
            crt_strcpy(net_session + 0x88,local_20 + 4);
            crt_strcpy(net_session + 0xa8,local_24 + 0x20);
            crt_strcpy(net_session + 200,local_24 + 0x28);
            crt_strcpy(net_session + 0xe8,local_24 + 0x10);
          }
          crt_strcpy(&net_server_address,local_24 + 4);
          crt_strcpy(&net_game_name,local_24 + 0x20);
          crt_strcpy(&net_local_player_name,&prefs_net_player_name);
          crt_strcpy(&net_server_version,local_24 + 0x10);
          break;
        case 0x14:
          break;
        case 0x15:
        case 0x5c:
          local_694 = 0;
          local_6a0 = 0;
          local_69c = 0;
          net_msg_get_args((iptr)local_20,&unit);
          if (diffeng_mirror_buf != 0) {
            for (local_6a4 = 0; local_6a4 < (int)unit; local_6a4++) {
              local_6d0 = *local_48;
              local_698 = local_48[1];
              local_684 = local_48[2];
              local_48 += 3;
              if ((local_6d0 & 0x7fff) == 1) {
                local_680 = game.active_unit;
                local_6b0 = game.moving_unit;
                local_6cc = game.multiplayer;
                local_6ac = game.player_civ;
                local_68c = game.field_1c;
                local_688 = game.turn_civ;
                local_67c = game.game_options;
                local_690 = game.message_options;
              }
              else if (((net_host_flag == '\0') || ((local_6d0 & 0x7fff) != 5)) || (local_6a0 != 0))
              {
                if ((local_6d0 & 0x7fff) == 0xb) {
                  local_69c = 1;
                }
              }
              else {
                local_6a0 = 1;
                for (unit2 = 0; unit2 < game.num_units; unit2++) {
                  *(i16 *)(&net_saved_unit_x + unit2 * 2) = units[unit2].x;
                  *(i16 *)(&net_saved_unit_y + unit2 * 2) = units[unit2].y;
                  *(i16 *)(&net_saved_unit_next + unit2 * 2) = units[unit2].next_in_stack;
                  *(i16 *)(&net_saved_unit_prev + unit2 * 2) = units[unit2].prev_in_stack;
                }
              }
              if ((local_6d0 & 0x8000) == 0) {
                crt_memcpy((&diffeng_section_ptrs)[local_6d0 * 6] + local_698,local_48,local_684);
                crt_memcpy(*(int *)(&diffeng_section_offsets + local_6d0 * 0x18) + local_698 + diffeng_mirror_buf,
                             local_48,local_684);
              }
              else {
                local_6d0 = local_6d0 & 0x7fff;
                local_6c0 = local_684 + (int)local_48;
                local_6c4 = local_48;
                local_6a8 = diffeng_rle_decoded_size((iptr)&local_6c4);
                local_6bc = (&diffeng_section_ptrs)[local_6d0 * 6] + local_698;
                local_6b8 = local_6bc + local_6a8;
                diffeng_rle_decode((iptr)&local_6c4);
                crt_memcpy(*(int *)(&diffeng_section_offsets + local_6d0 * 0x18) + local_698 + diffeng_mirror_buf,
                             (&diffeng_section_ptrs)[local_6d0 * 6] + local_698,local_6a8);
              }
              if (local_6d0 == 1) {
                game.active_unit = local_680;
                game.moving_unit = local_6b0;
                game.multiplayer = local_6cc;
                game.player_civ = local_6ac;
                game.field_1c = local_68c;
                game.turn_civ = local_688;
                game.game_options = local_67c;
                game.message_options = local_690;
              }
              if (local_6d0 == 6) {
                local_694 = 1;
              }
              local_48 = (uint *)((int)local_48 + local_684);
            }
            if (local_694 != 0) {
              city_window_refresh((FrameWindow *)&city_window);
            }
            if ((net_host_flag != '\0') && (local_6a0 != 0)) {
              for (unit2 = 0; unit2 < game.num_units; unit2++) {
                units[unit2].x = *(i16 *)(&net_saved_unit_x + unit2 * 2);
                units[unit2].y = *(i16 *)(&net_saved_unit_y + unit2 * 2);
                units[unit2].next_in_stack = *(i16 *)(&net_saved_unit_next + unit2 * 2);
                units[unit2].prev_in_stack = *(i16 *)(&net_saved_unit_prev + unit2 * 2);
              }
            }
            if (local_69c != 0) {
              turn_resume_civ = saved_turn_civ;
            }
          }
          break;
        case 0x16:
          break;
        case 0x17:
          crt_memcpy(&cosmic,local_48,0x29);
          break;
        case 0x18:
          crt_memcpy(advances,local_48,0x640);
          break;
        case 0x19:
          crt_memcpy(improvements,local_48,0x218);
          break;
        case 0x1a:
          crt_memcpy(wonder_expires,local_48,0x1c);
          break;
        case 0x1b:
          crt_memcpy(unit_types,local_48,0x4d8);
          break;
        case 0x1c:
          crt_memcpy(terrain_types,local_48,0x318);
          break;
        case 0x1d:
          crt_memcpy(government_names,local_48,0x1c);
          break;
        case 0x1e:
          crt_memcpy(government_titles,local_48,0x38);
          break;
        case 0x1f:
          crt_memcpy(leaders,local_48,0x3f0);
          break;
        case 0x20:
          crt_memcpy(civs,local_48,0x7524);
          break;
        case 0x21:
          crt_memcpy(commodity_names,local_48,0x40);
          break;
        case 0x22:
          crt_memcpy(order_names,local_48,0x68);
          break;
        case 0x23:
          crt_memcpy(difficulty_names,local_48,0x18);
          break;
        case 0x24:
          crt_memcpy(attitude_names,local_48,0x24);
          break;
        case 0x25:
          net_msg_get_args((iptr)local_20,&unit);
          scenario_events_loaded = unit;
          scenario_event_count = local_3c;
          if (unit != 0) {
            events_relink_pool();
          }
          break;
        case 0x26:
          break;
        case 0x27:
          break;
        case 0x28:
          net_msg_get_args((iptr)local_20,&unit);
          net_session_phase = unit;
          break;
        case 0x2a:
          net_msg_get_args((iptr)local_20,&unit);
          net_claimed_civs_mask = (ushort)unit;
          game.human_players = game.human_players & (byte)unit;
          nm_lock_nation_count_i32++;
          break;
        case 0x2b:
          net_send_message(0x2c,local_58,0,0,0,0,0,0,0,0);
          break;
        case 0x2c:
          break;
        case 0x2d:
          net_msg_get_args((iptr)local_20,&unit);
          *(i32 *)(&net_civ_drop_requested + unit * 4) = 1;
          net_drop_flagged_players();
          break;
        case 0x2e:
          if (net_host_flag == '\0') {
            err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62bec8, ((u8 *)&g.d_0062bec8)),ADDR(0x62bea4, ((u8 *)&g.d_0062bea4)),0x22a);
          }
          if (net_host_handoff_stage == '\0') {
            city = net_host_register_player_civ((iptr)local_24,local_58);
            if (city == 0) {
              net_send_message(0xc,local_58,0,0,0,0,0,0,0,0);
            }
            else {
              nm_lock_nation_count_i32++;
              if (2 < (int)net_session_phase) {
                dialog_ctor(&local_674,0x4000);
                local_8 = 1;
                net_send_message(0x65,0xff,0,0,0,0,0,0,0,0);
                mp_turn_timer_stop(0);
                dlg_load_game_section(&local_674,ADDR(0x62bed8, ((u8 *)&g.d_0062bed8)),0x2000000);
                dlg_show_modal(&local_674,0);
                net_send_message(0x33,local_58,(int)mp_double_production,(int)mp_double_moves,
                                   (int)mp_simultaneous_setting,0,0,0,0,0);
                net_send_message(4,0xff,0,0,0,0,0,0,0,0);
                XD_FlushSendBuffer(5000);
                net_send_state_diff(0xff,2,0,0,0);
                XD_FlushSendBuffer(5000);
                net_send_message(10,local_58,0,0,0,0,0,0,0,0);
                net_send_state_diff(local_58,1,0,0,0);
                XD_FlushSendBuffer(5000);
                net_send_message(0x25,local_58,scenario_events_loaded,scenario_event_count,0,0,0,0,0,0);
                net_send_rules_tables(local_58);
                XD_FlushSendBuffer(5000);
                net_send_message(0x28,local_58,net_session_phase,0,0,0,0,0,0,0);
                net_send_message(0x16,local_58,0,0,0,0,0,0,0,0);
                net_send_message(0x9c,0xff,0,0,0,0,0,0,0,0);
                local_380 = timer_ticks();
                do {
                  city = XD_FlushSendBuffer(5000);
                  if (city == 0) break;
                  net_process_messages((NetSession *)&net_session,100,0);
                  city = timer_ticks();
                } while (17999 < city - local_380);
                net_send_message(0x66,0xff,0,0,0,0,0,0,0,0);
                dialog_close(&local_674);
                mp_turn_timer_resume(0);
                for (local_678 = 0;
                    (local_678 < 7 && (*(int *)(&net_player_slots + local_678 * 0x54) != local_58));
                    local_678 = local_678 + 1) {
                }
                if (local_678 < 7) {
                  puVar2 = this[0xa7].pad_0 + (&net_slot_civs)[local_678 * 0x15] * 4 + 4;
                  puVar2[0] = 1;
                  puVar2[1] = '\0';
                  puVar2[2] = '\0';
                  puVar2[3] = '\0';
                }
                local_8 = 0xffffffff;
                /* inlined unwind funclet 00482305 */ { dialog_dtor((Dialog *)((iptr)&local_674)); }
              }
            }
          }
          else {
            net_send_message(0xb,local_58,0,0,0,0,0,0,0,0);
          }
          break;
        case 0x2f:
          if (net_host_handoff_stage == '\0') {
            if (net_player_count < net_max_players) {
              net_add_player(this,(iptr)local_20);
              if ((net_lobby_list == (int *)0x0) || (*net_lobby_list == 0)) {
                if (0 < (int)net_session_phase) {
                  net_send_message(0x28,local_58,net_session_phase,0,0,0,0,0,0,0);
                  net_send_message(4,0xff,0,0,0,0,0,0,0,0);
                  net_send_message(6,local_58,0,0,0,0,0,0,0,0);
                  net_send_message(9,local_58,0,0,0,0,0,0,0,0);
                }
              }
              else {
                lobby_refresh_player_list();
              }
            }
            else {
              net_send_message(0x11,local_58,0,0,0,0,0,0,0,0);
            }
          }
          else {
            net_send_message(0xb,local_58,0,0,0,0,0,0,0,0);
          }
          break;
        case 0x30:
          net_msg_get_args((iptr)local_20,&unit);
          if (((int)(short)net_claimed_civs_mask & 1 << ((byte)local_3c & 0x1f)) == 0) {
            net_claimed_civs_mask = (ushort)(1 << ((byte)local_3c & 0x1f)) | net_claimed_civs_mask;
            net_send_message(0x26,local_58,(int)(short)net_claimed_civs_mask,0,0,0,0,0,0,0);
            net_send_message(0x2a,0xff,(int)(short)net_claimed_civs_mask,0,0,0,0,0,0,0);
            nm_lock_nation_count_i32++;
          }
          else {
            net_send_message(0x27,local_58,0,0,0,0,0,0,0,0);
          }
          break;
        case 0x31:
          net_msg_get_args((iptr)local_20,&unit);
          game.human_players = game.human_players & (byte)net_claimed_civs_mask;
          if (((int)(short)net_claimed_civs_mask & 1 << ((byte)local_3c & 0x1f)) != 0) {
            net_claimed_civs_mask = ~(ushort)(1 << ((byte)local_3c & 0x1f)) & net_claimed_civs_mask;
            game.human_players = game.human_players & (byte)net_claimed_civs_mask;
            net_send_message(0x2a,0xff,(int)(short)net_claimed_civs_mask,0,0,0,0,0,0,0);
            nm_lock_nation_count_i32++;
          }
          break;
        case 0x32:
          *(i32 *)(&net_lost_conn_by_player + local_58 * 4) = 0xffffffff;
          net_remove_player(this,local_58);
          if ((this->field_4 != 0) &&
             (piVar1 = (int *)(this->field_4 + 0x54 + local_58 * 4), *piVar1 = *piVar1 + 1,
             *net_lobby_list != 0)) {
            lobby_refresh_player_list();
          }
          break;
        case 0x33:
          net_msg_get_args((iptr)local_20,&unit);
          mp_double_production = (short)unit;
          mp_double_moves = (short)local_3c;
          mp_simultaneous_moves = (char)unit3;
          mp_simultaneous_setting = (short)(char)unit3;
          break;
        case 0x34:
          net_msg_get_args((iptr)local_20,&unit);
          civ_eliminate(unit,0,0);
          net_send_message(0x35,local_58,0,0,0,0,0,0,0,0);
          break;
        case 0x35:
          net_kill_or_quit_ack = 1;
          break;
        case 0x37:
          net_msg_get_args((iptr)local_20,&unit);
          if ((-1 < (int)unit) && (units[unit].id != 0)) {
            x3 = (int)units[unit].x;
            y4 = (int)units[unit].y;
          }
          unit_delete(unit,1);
          net_send_message(0x38,local_58,unit,0,0,0,0,0,0,0);
          XD_FlushSendBuffer(5000);
          break;
        case 0x38:
          net_msg_get_args((iptr)local_20,&unit);
          net_unit_deleted_ack = 1;
          break;
        case 0x39:
          net_msg_get_args((iptr)local_20,&unit);
          city_delete(unit,0);
          net_send_message(0x3a,local_58,unit,0,0,0,0,0,0,0);
          XD_FlushSendBuffer(5000);
          break;
        case 0x3a:
          net_msg_get_args((iptr)local_20,&unit);
          net_city_deleted_ack = 1;
          crt_memcpy(cities + unit,local_48,0x58);
          break;
        case 0x3b:
          net_msg_get_args((iptr)local_20,&unit);
          local_14 = city_create(unit,local_3c,unit3);
          net_send_message(0x3c,local_58,local_14,0,0,0,0,0,0,0);
          XD_FlushSendBuffer(5000);
          break;
        case 0x3c:
          net_msg_get_args((iptr)local_20,&unit);
          nm_city_created_result = unit;
          if (unit != 0xffffffff) {
            crt_memcpy(cities + unit,local_48,0x58);
            game.num_cities = (i16)local_3c;
          }
          break;
        case 0x3d:
          net_msg_get_args((iptr)local_20,&unit);
          local_14 = unit_create(unit,local_3c,unit3,y2);
          net_send_message(0x3e,local_58,local_14,0,0,0,0,0,0,0);
          XD_FlushSendBuffer(5000);
          break;
        case 0x3e:
          net_msg_get_args((iptr)local_20,&unit);
          nm_unit_created_result = unit;
          if (unit != 0xffffffff) {
            game.num_units = (i16)local_3c;
          }
          break;
        case 0x3f:
          net_msg_get_args((iptr)local_20,&unit);
          unit_stack_unlink(unit,1);
          net_send_message(0x40,local_58,0,0,0,0,0,0,0,0);
          XD_FlushSendBuffer(5000);
          break;
        case 0x40:
          nm_unit_picked_up_count = 1;
          break;
        case 0x41:
          net_msg_get_args((iptr)local_20,&unit);
          unit_stack_link(unit,local_3c,unit3,1);
          net_send_message(0x42,local_58,0,0,0,0,0,0,0,0);
          XD_FlushSendBuffer(5000);
          break;
        case 0x42:
          nm_unit_put_down_count = 1;
          break;
        case 0x43:
          net_msg_get_args((iptr)local_20,&unit);
          unit_move_to_stack_bottom(unit,1);
          net_send_message(0x44,local_58,0,0,0,0,0,0,0,0);
          XD_FlushSendBuffer(5000);
          break;
        case 0x44:
          nm_bottomed_count = 1;
          break;
        case 0x45:
          net_msg_get_args((iptr)local_20,&unit);
          unit_relocate(unit,local_3c,unit3,1);
          net_send_message(0x46,local_58,0,0,0,0,0,0,0,0);
          XD_FlushSendBuffer(5000);
          break;
        case 0x46:
          nm_unit_relocated_count = 1;
          break;
        case 0x47:
          net_msg_get_args((iptr)local_20,&unit);
          local_14 = city_acquire_wonder(unit,local_3c,unit3,y2,x2);
          net_send_message(0x48,local_58,local_14,0,0,0,0,0,0,0);
          XD_FlushSendBuffer(5000);
          break;
        case 0x48:
          net_msg_get_args((iptr)local_20,&unit);
          nm_wonder_acquired_result = unit;
          break;
        case 0x49:
          net_msg_get_args((iptr)local_20,&unit);
          iVar8 = unit_gather_cargo(unit,local_3c,1);
          net_send_message(0x4a,local_58,iVar8,0,0,0,0,0,0,0);
          break;
        case 0x4a:
          net_msg_get_args((iptr)local_20,&unit);
          nm_ship_stacked_result = unit;
          break;
        case 0x4b:
          net_msg_get_args((iptr)local_20,&unit);
          unit_lift_off_map(unit,1);
          net_send_message(0x4c,local_58,0,0,0,0,0,0,0,0);
          break;
        case 0x4c:
          nm_unit_stacked_count = 1;
          break;
        case 0x4d:
          net_msg_get_args((iptr)local_20,&unit);
          unit_delete_with_cargo(unit,1);
          net_send_message(0x4e,local_58,0,0,0,0,0,0,0,0);
          break;
        case 0x4e:
          nm_safely_deleted_count = 1;
          break;
        case 0x4f:
          net_msg_get_args((iptr)local_20,&unit);
          unit_destroy_redraw(unit,1);
          net_send_message(0x50,local_58,0,0,0,0,0,0,0,0);
          break;
        case 0x50:
          nm_visibly_deleted_count = 1;
          break;
        case 0x51:
          net_msg_get_args((iptr)local_20,&unit);
          net_lock_map(unit,local_3c,unit3,y2,x2,0);
          break;
        case 0x52:
          net_msg_get_args((iptr)local_20,&unit);
          net_unlock_map(unit,0);
          net_send_message(0x54,local_58,unit,0,0,0,0,0,0,0);
          break;
        case 0x53:
          net_msg_get_args((iptr)local_20,&unit);
          *(uptr *)(&net_map_lock_replies + unit * 0x18) = local_3c;
          break;
        case 0x54:
          net_msg_get_args((iptr)local_20,&unit);
          *(int *)(&net_map_lock_slots + unit * 0x18) = *(int *)(&net_map_lock_slots + unit * 0x18) + 1;
          break;
        case 0x55:
          net_msg_get_args((iptr)local_20,&unit);
          *(uptr *)(&net_map_lock_src_x + unit * 0x18) = local_3c;
          *(uptr *)(&net_map_lock_src_y + unit * 0x18) = unit3;
          *(iptr *)(&net_map_lock_dst_x + unit * 0x18) = y2;
          *(iptr *)(&net_map_lock_dst_y + unit * 0x18) = x2;
          *(i32 *)(&net_map_lock_replies + unit * 0x18) = 0;
          *(i32 *)(&net_map_lock_slots + unit * 0x18) =
               *(i32 *)(&net_map_lock_replies + unit * 0x18);
          break;
        case 0x56:
        case 0x57:
          net_msg_get_args((iptr)local_20,&unit);
          net_vote_replies_pending--;
          if (unit == 2) {
            net_vote_status = 0xffffffff;
          }
          break;
        case 0x58:
          wonder_apollo_reveal_map();
          break;
        case 0x59:
          net_apply_tile_updates((iptr)local_48);
          break;
        case 0x5a:
          net_msg_get_args((iptr)local_20,&unit);
          unit_lift_off_map(unit3,0);
          unit_stack_clear_visibility(unit3);
          if (y2 == 0) {
            unit_stack_set_seen_by(unit3,local_3c);
          }
          unit_stack_relocate_all(unit3,x2,y3,0);
          if ((-1 < units[unit3].next_in_stack) &&
             (unit_types[units[unit3].type].attack == '\0')) {
            unit_move_to_stack_bottom(unit3,0);
          }
          if (mp_simultaneous_moves != '\0') {
            net_unlock_map(unit,0);
          }
          net_send_state_diff(0xff,2,0,0,1);
          net_send_message(0x5b,local_58,0,0,0,0,0,0,0,0);
          XD_FlushSendBuffer(60000);
          break;
        case 0x5b:
          nm_stacker_ack_count = 1;
          break;
        case 0x5d:
          net_drag_hold = 1;
          dbg_log(ADDR(0x62bee8, ((u8 *)&g.d_0062bee8)));
          break;
        case 0x5e:
          net_drag_hold = 0;
          dbg_log(ADDR(0x62bef0, ((u8 *)&g.d_0062bef0)));
          break;
        case 0x5f:
          net_msg_get_args((iptr)local_20,&unit);
          local_14 = civ_create(unit);
          net_send_message(0x61,local_58,local_14,0,0,0,0,0,0,0);
          break;
        case 0x60:
          net_msg_get_args((iptr)local_20,&unit);
          local_14 = civ_check_destroyed(unit,local_3c);
          net_send_message(0x62,local_58,local_14,0,0,0,0,0,0,0);
          break;
        case 0x61:
          net_msg_get_args((iptr)local_20,&unit);
          nm_new_civ_ack_result = unit;
          break;
        case 0x62:
          net_msg_get_args((iptr)local_20,&unit);
          nm_kill_civ_ack_result = unit;
          break;
        case 99:
          net_msg_get_args((iptr)local_20,&unit);
          civ2 = local_3c;
          unit5 = unit;
          civ = units[unit].owner;
          civs[local_3c].gold -= unit3;
          pcVar3 = (char *)(units[unit].type + ADDR(0x64c778, ((u8 *)&civs + 216)) + civ * 0x594);
          *pcVar3 = *pcVar3 - 1;
          pcVar3 = (char *)(units[unit].type + ADDR(0x64c778, ((u8 *)&civs + 216)) + local_3c * 0x594);
          *pcVar3 = *pcVar3 + 1;
          civs[local_3c].field_1c++;
          local_714 = (i8)local_3c;
          units[unit].owner = local_714;
          units[unit].home_city = -1;
          units[unit].moves_used = '\0';
          units[unit].orders = -1;
          city = city_find_nearest((int)units[unit].x,(int)units[unit].y,-1,0xffffffff,-1)
          ;
          if ((-1 < city) && ((int)cities[city].owner == civ2)) {
            local_718 = (i8)city;
            units[unit5].home_city = local_718;
          }
          unit_set_seen_by(unit5,(int)civ);
          tile_set_owner((int)units[unit5].x,(int)units[unit5].y,civ2,1);
          net_send_state_diff(0xff,2,0,0,1);
          break;
        case 100:
          net_msg_get_args((iptr)local_20,&unit);
          casualty_log_add(unit,local_3c,unit3,y2,x2);
          break;
        case 0x65:
          dialog_ctor(&local_37c,0x4000);
          local_8 = 0;
          local_88 = this[0xae].field_4;
          this[0xae].field_4 = 1;
          mp_turn_timer_stop(0);
          nm_continue_after_join_count = 0;
          dlg_pending_idle_callback = ((void *)ADDR(0x00402c2a, net_game_xmit_wait_idle));
          popup_game_sprite_flags(ADDR(0x62be94, ((u8 *)&g.d_0062be94)),0x2000000,ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
          dialog_close(&local_37c);
          this[0xae].field_4 = local_88;
          mp_turn_timer_resume(0);
          local_8 = 0xffffffff;
          /* inlined unwind funclet 00482311 */ { dialog_dtor((Dialog *)((iptr)&local_37c)); }
          break;
        case 0x66:
          break;
        case 0x68:
          net_msg_get_args((iptr)local_20,&unit);
          local_4c = 0x2c;
          chat_receive_message
                    ((WindowObjectView *)&chat_wnd,unit,local_3c,unit3,(iptr)(local_20 + 0xb)
                    );
          break;
        case 0x69:
          bVar10 = *(int *)this[0x102].pad_0 != 0;
          if (bVar10) {
            net_stacked_draw_last = (net_stacked_draw_first + 1) % 100;
          }
          else {
            net_stacked_draw_first = 0;
            net_stacked_draw_last = 0;
          }
          net_stacked_draw_count = (uint)bVar10;
          net_stacked_draw_push(0xa3,(iptr)local_6fc,0);
          net_stacked_draw_push(0x74,(iptr)local_6fc,0);
          game.turn_civ = (i8)local_24[4];
          mp_turn_civ_i32 = (int)game.turn_civ;
          mp_turn_timer_stop(1);
          menu_update_states();
          main_view_timer_cache_i32 = 0xffffffff;
          frame_wnd_draw_caption((FrameWindow *)&map_views);
          local_6e0 = main_view_frame_left;
          local_6dc = main_view_frame_top;
          local_6d8 = main_view_frame_right;
          local_6d4 = main_view_client_top;
          wnd_blit_surface_rect((DibSurface *)&map_views,(iptr)&local_6e0);
          break;
        case 0x6a:
          net_msg_get_args((iptr)local_20,&unit);
          local_4c = 0x2c;
          if ((unit == 0x3d) &&
             (((1 << ((byte)human_civ & 0x1f) & (uint)game.human_players) == 0 ||
              (mp_meeting_pending != 0)))) {
            net_send_message(0x80,local_58,2,0,0,0,0,0,0,0);
          }
          else {
            if (unit == 0x3d) {
              mp_meeting_pending = 1;
            }
            if (((unit != 100) || (parley_reveal_units_prompt_open != 1)) &&
               ((unit != 0x65 || (parley_reveal_city_prompt_open != 1)))) {
              if (local_28 == 0) {
                local_748 = (int *)0x0;
              }
              else {
                local_748 = local_20 + 0xb;
              }
              net_popup_queue_push(unit,local_3c,unit3,y2,x2,local_748,local_28);
            }
          }
          break;
        case 0x6b:
          net_msg_get_args((iptr)local_20,&unit);
          game.game_flags = (u16)unit;
          game_over_reason = local_3c;
          spaceship_winner_civ = unit3;
          break;
        case 0x6c:
          net_msg_get_args((iptr)local_20,&unit);
          mp_turn_time_limit_ms = unit;
          if (unit == 0) {
            main_view_timer_shown = 0;
            frame_wnd_draw_caption((FrameWindow *)&map_views);
            local_78 = main_view_frame_left;
            local_74 = main_view_frame_top;
            local_70 = main_view_frame_right;
            local_6c = main_view_client_top;
            wnd_blit_surface_rect((DibSurface *)&map_views,(iptr)&local_78);
          }
          else {
            main_view_timer_shown = 1;
            mp_turn_timer_start(1);
          }
          break;
        case 0x6d:
          if (mp_turn_time_limit_ms != 0) {
            main_view_timer_shown = 1;
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
          net_msg_get_args((iptr)local_20,&unit);
          if (y3 != 0) {
            x = map_wrap_x((int)(char)(&dir_dx_table)[y2] + local_3c);
            city = city_at(x,(int)(char)(&dir_dy_table)[y2] + unit3);
            if ((city < 0) && ((game.game_options & 0x1000) == 0)) {
              local_24[1] = 0x72;
              unit = local_3c;
              local_3c = unit3;
            }
          }
          net_stacked_draw_push(local_24[1],(iptr)&unit,(iptr)local_48);
          break;
        case 0x71:
          net_msg_get_args((iptr)local_20,&unit);
          net_stacked_draw_push(local_24[1],(iptr)&unit,0);
          break;
        case 0x72:
          net_msg_get_args((iptr)local_20,&unit);
          city = mapviews_tile_visible(unit,local_3c);
          if (city != 0) {
            net_stacked_draw_push(local_24[1],(iptr)&unit,0);
          }
          break;
        case 0x73:
          net_msg_get_args((iptr)local_20,&unit);
          city = mapviews_tile_visible(unit,local_3c);
          if ((city != 0) || (city = mapviews_tile_visible(unit3,y2), city != 0)) {
            net_stacked_draw_push(local_24[1],(iptr)&unit,0);
          }
          break;
        case 0x74:
          net_stacked_draw_push(local_20[1],(iptr)&unit,0);
          break;
        case 0x75:
          net_msg_get_args((iptr)local_20,&unit);
          city = mapviews_tile_visible(unit,local_3c);
          if (city != 0) {
            net_stacked_draw_push(local_24[1],(iptr)&unit,0);
          }
          break;
        case 0x76:
          net_msg_get_args((iptr)local_20,&unit);
          city = mapviews_tile_visible(unit,local_3c);
          if (city != 0) {
            net_stacked_draw_push(local_24[1],(iptr)&unit,0);
          }
          break;
        case 0x77:
          net_msg_get_args((iptr)local_20,&unit);
          net_can_escape_reply = unit;
          break;
        case 0x78:
          status_draw_info(1);
          break;
        case 0x79:
          status_redraw(1);
          break;
        case 0x7a:
          net_msg_get_args((iptr)local_20,&unit);
          snd_play_effect(unit,local_3c,0,0);
          break;
        case 0x7b:
          net_msg_get_args((iptr)local_20,&unit);
          net_bribe_answer = unit;
          break;
        case 0x7c:
          net_msg_get_args((iptr)local_20,&unit);
          net_stacked_draw_push(local_24[1],(iptr)&unit,0);
          break;
        case 0x7d:
          net_msg_get_args((iptr)local_20,&unit);
          net_stacked_draw_push(local_24[1],(iptr)&unit,0);
          break;
        case 0x7e:
          net_msg_get_args((iptr)local_20,&unit);
          diplo_ally_demand_help(unit,local_3c);
          break;
        case 0x7f:
          net_msg_get_args((iptr)local_20,&unit);
          advisor_refresh_if_open(unit);
          break;
        case 0x80:
          net_msg_get_args((iptr)local_20,&unit);
          mp_meeting_reply = unit;
          break;
        case 0x81:
          if ((((&net_slot_civs)[local_58 * 0x15] == parley_other_civ) || (parley_other_civ == 0xfffffffe))
             || (parley_wnd_closed == 0)) {
            if (parley_wnd_closed == 0) {
              parley_wnd_close();
            }
            else if (parley_other_civ == 0xfffffffe) {
              parley_other_civ = 0xffffffff;
            }
            mp_meeting_pending = 0;
          }
          break;
        case 0x82:
          if (parley_received_offer != (void *)0x0) {
            operator_delete(parley_received_offer);
            parley_received_offer = (void *)0x0;
          }
          parley_received_offer = operator_new(local_5c);
          if (parley_received_offer != (void *)0x0) {
            crt_memcpy(parley_received_offer,local_20,local_5c);
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
          parley_execute_transaction((iptr)local_20);
          break;
        case 0x87:
          net_msg_get_args((iptr)local_20,&unit);
          city_window_on_unit_change
                    ((FrameWindow *)&city_window,unit,local_3c,unit3);
          break;
        case 0x88:
          net_msg_get_args((iptr)local_20,&unit);
          city_window_refresh_if_city((FrameWindow *)&city_window,unit);
          break;
        case 0x89:
          net_msg_get_args((iptr)local_20,&unit);
          city_window_close_if_city((WindowObjectView *)&city_window,unit);
          break;
        case 0x8a:
          if (city_window_refresh_locked == 0) {
            city_window_refresh((FrameWindow *)&city_window);
          }
          break;
        case 0x8b:
          break;
        case 0x8c:
          net_msg_get_args((iptr)local_20,&unit);
          *(int *)(&net_civ_phase_done + unit * 4) = *(int *)(&net_civ_phase_done + unit * 4) + 1;
          break;
        case 0x8d:
          break;
        case 0x8e:
          break;
        case 0x8f:
          net_msg_get_args((iptr)local_20,&unit);
          *(int *)(&net_civ_phase_done + unit * 4) = *(int *)(&net_civ_phase_done + unit * 4) + 1;
          for (unit4 = 0; unit4 < game.num_units; unit4++) {
            if ((units[unit4].id != 0) && ((int)units[unit4].owner == unit)) {
              unit_exhaust_moves(unit4);
            }
          }
          break;
        case 0x90:
          net_msg_get_args((iptr)local_20,&unit);
          tile_set_improvements(unit,local_3c,unit3,y2,x2);
          break;
        case 0x91:
          net_msg_get_args((iptr)local_20,&unit);
          tile_set_terrain(unit,local_3c,unit3,y2);
          break;
        case 0x92:
          net_msg_get_args((iptr)local_20,&unit);
          tile_set_visible(unit,local_3c,unit3,y2,x2);
          break;
        case 0x93:
          net_msg_get_args((iptr)local_20,&unit);
          tile_set_fertility(unit,local_3c,unit3,y2);
          break;
        case 0x94:
          net_msg_get_args((iptr)local_20,&unit);
          tile_set_owner(unit,local_3c,unit3,y2);
          break;
        case 0x95:
          net_msg_get_args((iptr)local_20,&unit);
          tile_set_landmass(unit,local_3c,unit3,y2);
          break;
        case 0x96:
          net_msg_get_args((iptr)local_20,&unit);
          tile_set_radius_civ(unit,local_3c,unit3,y2);
          break;
        case 0x97:
          net_msg_get_args((iptr)local_20,&unit);
          known_set(unit,local_3c,unit3,y2,x2,y3);
          break;
        case 0x98:
          net_msg_get_args((iptr)local_20,&unit);
          *(char *)&civs[unit].attitude[local_3c] = (char)unit3;
          break;
        case 0x99:
          net_msg_get_args((iptr)local_20,&unit);
          *(i32 *)(&net_meet_pending_flags + local_3c * 4) = 1;
          *(uptr *)(&net_meet_pending_ai_civ + local_3c * 4) = unit;
          *(uptr *)(&net_meet_pending_civ + local_3c * 4) = local_3c;
          *(uptr *)(&net_meet_pending_x + local_3c * 4) = unit3;
          *(iptr *)(&net_meet_pending_y + local_3c * 4) = y2;
          break;
        case 0x9a:
          net_msg_get_args((iptr)local_20,&unit);
          net_move_anim_sound = unit;
          net_move_anim_sound_arg = local_3c;
          break;
        case 0x9b:
          net_msg_get_args((iptr)local_20,&unit);
          civ_give_advance(unit,local_3c,unit3,y2,0);
          break;
        case 0x9c:
          break;
        case 0x9d:
          taxrate_dialog_show(human_civ);
          break;
        case 0x9e:
          taxrate_enforce_max_rate(human_civ);
          break;
        case 0x9f:
          net_msg_get_args((iptr)local_20,&unit);
          civ_select_government_dialog(human_civ,unit);
          break;
        case 0xa0:
          net_msg_get_args((iptr)local_20,&unit);
          diplo_ai_review_relations(unit,local_3c);
          break;
        case 0xa1:
          net_msg_get_args((iptr)local_20,&unit);
          diplo_ai_seek_war_ally(unit,local_3c);
          break;
        case 0xa2:
          net_msg_get_args((iptr)local_20,&unit);
          *(int *)(&net_civ_turn_ended + unit * 4) = *(int *)(&net_civ_turn_ended + unit * 4) + 1;
          break;
        case 0xa3:
          net_stacked_draw_push(local_20[1],(iptr)&unit,0);
          break;
        case 0xa4:
          net_msg_get_args((iptr)local_20,&unit);
          iVar8 = civ_name_plural(unit);
          text_set_string_arg(0,iVar8);
          iVar8 = civ_name_plural(local_3c);
          text_set_string_arg(1,iVar8);
          if ((*(byte *)&civs[local_3c].treaties[unit] & 8) == 0) {
            city = popup_game_with_sprite(ADDR(0x62bf0c, ((u8 *)&g.d_0062bf0c)),ADDR(0x644e48, ((u8 *)&g.d_00644e48)),0);
            if (city == 1) {
              diplo_set_treaty_flags(unit,local_3c,0x2000);
              civs[local_3c].last_treaty_turn[unit] = game.turn;
            }
          }
          else {
            city = popup_game_with_sprite(ADDR(0x62befc, ((u8 *)&g.d_0062befc)),(iptr)(&diplo_popup_portrait_sprite +
                                                      ((game.advance_known_by[0xf] != '\0') - 1 &
                                                      0xffff7c80)),0);
            if (city == 1) {
              diplo_clear_treaty_flags(unit,local_3c,8);
              civs[local_3c].last_treaty_turn[unit] = game.turn;
            }
          }
          break;
        case 0xa5:
          net_msg_get_args((iptr)local_20,&unit);
          if ((parley_wnd_closed == 0) && (parley_other_civ == unit)) {
            parley_remote_cities_revealed = (byte)local_3c;
            if (((parley_mode == 0xe) && (parley_barter_want_kind == 3)) ||
               ((parley_mode == 0xf && (parley_demand_kind == 3)))) {
              ctrl_disable(parley_request_done_button);
              ctrl_disable(parley_request_origin_button);
              parley_draw_city_list(1);
            }
          }
          break;
        case 0xa6:
          net_msg_get_args((iptr)local_20,&unit);
          if ((parley_wnd_closed == 0) && (parley_other_civ == unit)) {
            parley_remote_cities_revealed = (byte)local_3c;
            if (((parley_mode == 0xe) && (parley_barter_want_kind == 3)) ||
               ((parley_mode == 0xf && (parley_demand_kind == 3)))) {
              ctrl_enable(parley_request_done_button);
              ctrl_enable(parley_request_origin_button);
              parley_draw_city_list(1);
            }
          }
          break;
        case 0xa7:
          net_msg_get_args((iptr)local_20,&unit);
          if ((parley_wnd_closed == 0) && (parley_other_civ == unit)) {
            parley_remote_units_revealed = (byte)local_3c;
            if (((parley_mode == 0xe) && (parley_barter_want_kind == 2)) ||
               ((parley_mode == 0xf && (parley_demand_kind == 2)))) {
              ctrl_disable(parley_request_done_button);
              ctrl_disable(parley_request_origin_button);
              ctrl_enable(parley_sort_by_city_right);
              ctrl_enable(parley_sort_by_unit_right);
              parley_draw_unit_list(1);
            }
          }
          break;
        case 0xa8:
          net_msg_get_args((iptr)local_20,&unit);
          if ((parley_wnd_closed == 0) && (parley_other_civ == unit)) {
            parley_remote_units_revealed = (byte)local_3c;
            if (((parley_mode == 0xe) && (parley_barter_want_kind == 2)) ||
               ((parley_mode == 0xf && (parley_demand_kind == 2)))) {
              ctrl_enable(parley_request_done_button);
              ctrl_enable(parley_request_origin_button);
              ctrl_disable(parley_sort_by_city_right);
              ctrl_disable(parley_sort_by_unit_right);
              parley_sort_unit_list((WindowObjectView *)&parley_wnd,0,parley_list_count_right - 1,1);
              parley_draw_unit_list(1);
            }
          }
        }
        operator_delete(local_20);
      }
      else {
        dbg_logf_int2(ADDR(0x62be5c, ((u8 *)&g.d_0062be5c)),local_20[1],local_20[2]);
      }
    }
    if (((param_2 == 0) && (*(char *)((int)&this[0x3d].field_4 + 2) != '\0')) && (local_1c != '\0'))
    {
      net_gamelist_refresh();
    }
    if (((param_2 == 0) && (this[0xae].field_4 == 0)) && (net_popup_queue_head != 0)) {
      net_popup_queue_show_next();
    }
    *(int *)this[0xb0].pad_0 = *(int *)this[0xb0].pad_0 - 1;
  }
  return;
}
#undef blocked_input_char
#undef blocked_input_char_pending
#undef city_window_closed
#undef city_window_refresh_locked
#undef dlg_pending_idle_callback
#undef game_over_reason
#undef game_setup_complete
#undef human_civ
#undef loaded_file_kind
#undef loaded_file_name
#undef loaded_file_subdir
#undef main_view_timer_shown
#undef mp_double_moves
#undef mp_double_production
#undef mp_meeting_pending
#undef mp_meeting_reply
#undef mp_simultaneous_moves
#undef mp_simultaneous_setting
#undef mp_turn_civ
#undef mp_turn_time_limit_ms
#undef net_bribe_answer
#undef net_can_escape_reply
#undef net_city_deleted_ack
#undef net_claimed_civs_mask
#undef net_drag_hold
#undef net_host_flag
#undef net_host_handoff_stage
#undef net_kill_or_quit_ack
#undef net_lobby_list
#undef net_max_players
#undef net_move_anim_sound
#undef net_move_anim_sound_arg
#undef net_popup_queue_head
#undef net_session_phase
#undef net_slot_civs
#undef net_stacked_draw_count
#undef net_unit_deleted_ack
#undef net_vote_status
#undef nm_bottomed_count
#undef nm_continue_after_join_count
#undef nm_kill_civ_ack_result
#undef nm_new_civ_ack_result
#undef nm_safely_deleted_count
#undef nm_ship_stacked_result
#undef nm_stacker_ack_count
#undef nm_unit_created_result
#undef nm_unit_picked_up_count
#undef nm_unit_put_down_count
#undef nm_unit_relocated_count
#undef nm_unit_stacked_count
#undef nm_visibly_deleted_count
#undef nm_wonder_acquired_result
#undef parley_other_civ
#undef parley_reveal_city_prompt_open
#undef parley_reveal_units_prompt_open
#undef prefs_net_player_name
#undef saved_turn_civ
#undef scenario_event_count
#undef scenario_events_loaded
#undef spaceship_winner_civ
#undef turn_resume_civ
#undef main_view_timer_cache_i32
#undef mp_turn_civ_i32
#undef nm_lock_nation_count_i32
#undef local_748
#undef local_740
#undef local_738
#undef local_734
#undef local_718
#undef local_714
#undef local_6fc
#undef local_6e0
#undef local_6dc
#undef local_6d8
#undef local_6d4
#undef local_6d0
#undef local_6cc
#undef unit2
#undef local_6c4
#undef local_6c0
#undef local_6bc
#undef local_6b8
#undef local_6b0
#undef local_6ac
#undef local_6a8
#undef local_6a4
#undef local_6a0
#undef local_69c
#undef local_698
#undef local_694
#undef local_690
#undef local_68c
#undef local_688
#undef local_684
#undef local_680
#undef local_67c
#undef local_678
#undef local_674
#undef local_380
#undef local_37c
#undef local_88
#undef local_84
#undef y4
#undef x3
#undef local_78
#undef local_74
#undef local_70
#undef local_6c
#undef local_68
#undef local_64
#undef local_60
#undef local_5c
#undef local_58
#undef unit4
#undef local_50
#undef local_4c
#undef local_48
#undef local_44
#undef unit
#undef local_3c
#undef unit3
#undef y2
#undef x2
#undef y3
#undef local_28
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00482337 auto */
#define dialog_stack_top (*(int * *)((u8 *)&g.d_006ad678))
#define nm_continue_after_join_count (*(int *)((u8 *)&g.d_006c9178))
void __cdecl net_game_xmit_wait_idle(void)

{
  net_process_messages((NetSession *)&net_session,1,0);
  if (nm_continue_after_join_count != 0) {
    dialog_stack_top[0xf] = dialog_stack_top[0xf] | 0x400;
    wnd_end_modal_loop((ModalMenuWindow *)(*dialog_stack_top + 0x48));
  }
  return;
}
#undef dialog_stack_top
#undef nm_continue_after_join_count

/* 004823d6 auto */
void __cdecl net_msg_get_args(iptr param_1,i32 *param_2)

{
  *param_2 = *(i32 *)(param_1 + 0x10);
  param_2[1] = *(i32 *)(param_1 + 0x14);
  param_2[2] = *(i32 *)(param_1 + 0x18);
  param_2[3] = *(i32 *)(param_1 + 0x1c);
  param_2[4] = *(i32 *)(param_1 + 0x20);
  param_2[5] = *(i32 *)(param_1 + 0x24);
  param_2[6] = *(i32 *)(param_1 + 0x28);
  return;
}

/* 00482470 auto */
#define dialog_stack_top (*(int * *)((u8 *)&g.d_006ad678))
void __cdecl net_server_quit_wait_idle(void)

{
  int iVar1;
  
  net_process_messages((NetSession *)&net_session,1,0);
  if (((net_players_awaited != 0) &&
      (iVar1 = bits_count8((uint)(game.human_players == '\0')), iVar1 == 0)) &&
     (1 < net_player_count)) {
    return;
  }
  dialog_stack_top[0xf] = dialog_stack_top[0xf] | 0x400;
  wnd_end_modal_loop((ModalMenuWindow *)(*dialog_stack_top + 0x48));
  return;
}
#undef dialog_stack_top

/* 004824e3 auto */
#define dlg_pending_idle_callback (*(i8 * *)((u8 *)&g.d_00635a3c))
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define mp_turn_civ (*(i8 *)((u8 *)&g.d_006ad578))
#define net_host_handoff_stage (*(i8 *)((u8 *)&g.d_006ad698))
#define net_slot_active_flags (*(i8 *)((u8 *)&g.d_006ad359))
#define net_slot_host_flags (*(i8 *)((u8 *)&g.d_006ad358))
#define saved_turn_civ (*(char *)((u8 *)&g.d_00654fa4))
#define net_player_slots_i32 (*(i32 *)((u8 *)&g.d_006ad30c))
#define net_civ_slots_i32 (*(i32 *)((u8 *)&g.d_006ad558))
#define mp_turn_civ_i32 (*(i32 *)((u8 *)&g.d_006ad578))
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl net_host_quit_handoff(void)

{
  byte bVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  net_host_handoff_stage = 1;
  net_drop_flagged_players();
  game.human_players = pending_human_players | game.human_players;
  pending_human_players = 0;
  if (1 < net_player_count) {
    game.human_players = game.human_players & ~(byte)(1 << ((byte)human_civ & 0x1f));
    net_players_awaited = net_player_count - 1;
    net_send_message(0xe,0xff,0,0,0,0,0,0,0,0);
    net_drop_flagged_players();
    dlg_pending_idle_callback = ((void *)ADDR(0x00403cc9, net_server_quit_wait_idle));
    popup_game_sprite_flags(ADDR(0x62bf34, ((u8 *)&g.d_0062bf34)),0x2000000,ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
    iVar2 = bits_count8((uint)(game.human_players == '\0'));
    if (iVar2 == 0) {
      net_send_message(0xf,0xff,0,0,0,0,0,0,0,0);
      bVar1 = (byte)(mp_turn_civ_i32 + 1 >> 0x1f);
      saved_turn_civ = (((byte)(mp_turn_civ_i32 + 1) ^ bVar1) - bVar1 & 7 ^ bVar1) - bVar1;
      for (local_8 = 1; (local_8 < 7 && ((&net_slot_active_flags)[local_8 * 0x54] == '\0'));
          local_8 = local_8 + 1) {
      }
      if (local_8 < 7) {
        crt_memcpy(&net_player_slots,&net_player_slots + local_8 * 0x54,0x54);
        net_slot_host_flags = 1;
        net_player_slots_i32 = 0;
        net_civ_slots_i32 = *(i32 *)(&net_civ_slots + local_8 * 4);
        net_player_count--;
        *(i32 *)(&net_civ_slots + local_8 * 4) = 0xffffffff;
        _memset(&net_player_slots + local_8 * 0x54,0,0x54);
        net_send_state_diff(0xff,2,0,1,0);
        net_send_message(0x16,0xff,0,0,0,0,0,0,0,0);
        net_send_message(4,0xff,0,0,0,0,0,0,0,0);
        XD_FlushSendBuffer(60000);
      }
    }
  }
  return;
}
#undef dlg_pending_idle_callback
#undef human_civ
#undef mp_turn_civ
#undef net_host_handoff_stage
#undef net_slot_active_flags
#undef net_slot_host_flags
#undef saved_turn_civ
#undef net_player_slots_i32
#undef net_civ_slots_i32
#undef mp_turn_civ_i32
#undef local_8

/* 00482724 auto */
#define dialog_stack_top (*(int * *)((u8 *)&g.d_006ad678))
#define net_host_handoff_stage (*(char *)((u8 *)&g.d_006ad698))
void __cdecl net_client_quit_wait_idle(void)

{
  net_process_messages((NetSession *)&net_session,1,0);
  if (net_host_handoff_stage == 2) {
    dialog_stack_top[0xf] = dialog_stack_top[0xf] | 0x400;
    wnd_end_modal_loop((ModalMenuWindow *)(*dialog_stack_top + 0x48));
  }
  return;
}
#undef dialog_stack_top
#undef net_host_handoff_stage

/* 0048276d auto */
#define dialog_stack_top (*(int * *)((u8 *)&g.d_006ad678))
#define net_timeout_seconds (*(int *)((u8 *)&g.d_006ad8b8))
#define nm_start_civ_count (*(int *)((u8 *)&g.d_006c9038))
#define net_handoff_wait_ticks_i32 (*(i32 *)((u8 *)&g.d_00670d98))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl net_quit_wait_start_civ_idle(void)

{
  int iVar1;
  
  net_process_messages((NetSession *)&net_session,1,0);
  if ((nm_start_civ_count == 0) &&
     (iVar1 = timer_ticks(), iVar1 - net_handoff_wait_ticks_i32 <= net_timeout_seconds * 0x3c)) {
    return;
  }
  dialog_stack_top[0xf] = dialog_stack_top[0xf] | 0x400;
  wnd_end_modal_loop((ModalMenuWindow *)(*dialog_stack_top + 0x48));
  return;
}
#undef dialog_stack_top
#undef net_timeout_seconds
#undef nm_start_civ_count
#undef net_handoff_wait_ticks_i32

/* 004827d5 auto */
#define dialog_stack_top (*(int * *)((u8 *)&g.d_006ad678))
#define net_timeout_seconds (*(int *)((u8 *)&g.d_006ad8b8))
#define net_handoff_wait_ticks_i32 (*(i32 *)((u8 *)&g.d_00670d98))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl net_quit_wait_player_list_idle(void)

{
  int iVar1;
  
  net_process_messages((NetSession *)&net_session,1,0);
  if ((nm_player_list_count == 0) &&
     (iVar1 = timer_ticks(), iVar1 - net_handoff_wait_ticks_i32 <= net_timeout_seconds * 0x3c)) {
    return;
  }
  dialog_stack_top[0xf] = dialog_stack_top[0xf] | 0x400;
  wnd_end_modal_loop((ModalMenuWindow *)(*dialog_stack_top + 0x48));
  return;
}
#undef dialog_stack_top
#undef net_timeout_seconds
#undef net_handoff_wait_ticks_i32

/* 0048283d auto */
#define dialog_stack_top (*(int * *)((u8 *)&g.d_006ad678))
#define net_timeout_seconds (*(int *)((u8 *)&g.d_006ad8b8))
#define net_handoff_wait_ticks_i32 (*(i32 *)((u8 *)&g.d_00670d98))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl net_quit_wait_players_idle(void)

{
  int iVar1;
  
  net_process_messages((NetSession *)&net_session,1,0);
  if ((net_players_awaited != 0) &&
     (iVar1 = timer_ticks(), iVar1 - net_handoff_wait_ticks_i32 <= net_timeout_seconds * 0x3c)) {
    return;
  }
  dialog_stack_top[0xf] = dialog_stack_top[0xf] | 0x400;
  wnd_end_modal_loop((ModalMenuWindow *)(*dialog_stack_top + 0x48));
  return;
}
#undef dialog_stack_top
#undef net_timeout_seconds
#undef net_handoff_wait_ticks_i32

/* 004828a5 auto */
#define diffeng_mirror_end (*(int *)((u8 *)&g.d_0067a408))
#define diffeng_mirror_size (*(int *)((u8 *)&g.d_0067a400))
#define dlg_pending_idle_callback (*(i8 * *)((u8 *)&g.d_00635a3c))
#define game_loop_active (*(i8 *)((u8 *)&g.d_00628044))
#define game_over_reason (*(int *)((u8 *)&g.d_0064b1ac))
#define mp_double_moves (*(short *)((u8 *)&g.d_00654fae))
#define mp_double_production (*(short *)((u8 *)&g.d_00654fac))
#define mp_simultaneous_moves (*(i8 *)((u8 *)&g.d_006ad684))
#define mp_simultaneous_setting (*(i8 *)((u8 *)&g.d_00654c7c))
#define net_connection_title (*(i32 *)((u8 *)&g.d_006ad63c))
#define net_host_handoff_stage (*(i8 *)((u8 *)&g.d_006ad698))
#define net_local_slot (*(i32 *)((u8 *)&g.d_006ad304))
#define net_protocol (*(i32 *)((u8 *)&g.d_006ad2f8))
#define net_server_conn_id (*(i32 *)((u8 *)&g.d_006ad300))
#define net_session_phase (*(i32 *)((u8 *)&g.d_006ad640))
#define net_slot_active_flags (*(i8 *)((u8 *)&g.d_006ad359))
#define net_slot_civs (*(i32 *)((u8 *)&g.d_006ad35c))
#define net_timeout_seconds (*(int *)((u8 *)&g.d_006ad8b8))
#define nm_start_civ_count (*(int *)((u8 *)&g.d_006c9038))
#define player_turn_active (*(i8 *)((u8 *)&g.d_0064b9bc))
#define prefs_net_ip_address (*(i8 *)((u8 *)&g.d_006665b0))
#define saved_turn_civ (*(i8 *)((u8 *)&g.d_00654fa4))
#define turn_resume_civ (*(i8 *)((u8 *)&g.d_00628048))
#define net_handoff_wait_ticks_i32 (*(i32 *)((u8 *)&g.d_00670d98))
#define nm_server_quit_count_i32 (*(i32 *)((u8 *)&g.d_006c901c))
#define local_284 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_280 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_27c (*(int (*)[2])(frame_ + FRAME_OFF(12)))
#define acStack_274 (*(char (*)[76])(frame_ + FRAME_OFF(20)))
#define local_228 (*(int (*)[135])(frame_ + FRAME_OFF(96)))
#define local_c (*(int *)(frame_ + FRAME_OFF(636)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(640)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __cdecl net_client_transfer_server(void)

{
  char cVar1;
  i32 uVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(648)] __attribute__((aligned(8)));  /* original stack frame */
  
  nm_server_quit_count_i32 = 0;
  nm_start_civ_count = 0;
  nm_player_list_count = 0;
  net_send_message(0x10,0,0,0,0,0,0,0,0,0);
  dlg_pending_idle_callback = ((void *)ADDR(0x004021fd, net_client_quit_wait_idle));
  popup_game_sprite_flags(ADDR(0x62bf44, ((u8 *)&g.d_0062bf44)),0x2000000,ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
  net_host_handoff_stage = 0;
  dlg_pending_idle_callback = ((void *)ADDR(0x00402f22, net_quit_wait_start_civ_idle));
  net_handoff_wait_ticks_i32 = timer_ticks();
  popup_game_sprite_flags(ADDR(0x62bf54, ((u8 *)&g.d_0062bf54)),0x2000000,ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
  if (nm_start_civ_count == 0) {
    dbg_log(ADDR(0x62bf64, ((u8 *)&g.d_0062bf64)));
    crt_strcpy(&text_string_args,net_connection_title);
    popup_game_with_sprite(ADDR(0x62bf9c, ((u8 *)&g.d_0062bf9c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
    player_turn_active = 0;
    game_loop_active = 0;
    uVar2 = 0;
  }
  else {
    turn_resume_civ = saved_turn_civ;
    dlg_pending_idle_callback = ((void *)ADDR(0x00402f54, net_quit_wait_player_list_idle));
    net_handoff_wait_ticks_i32 = timer_ticks();
    popup_game_sprite_flags(ADDR(0x62bfac, ((u8 *)&g.d_0062bfac)),0x2000000,ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
    if (nm_player_list_count == 0) {
      dbg_log(ADDR(0x62bfbc, ((u8 *)&g.d_0062bfbc)));
      crt_strcpy(&text_string_args,net_connection_title);
      popup_game_with_sprite(ADDR(0x62bff0, ((u8 *)&g.d_0062bff0)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      player_turn_active = 0;
      game_loop_active = 0;
      uVar2 = 0;
    }
    else {
      crt_memcpy(local_27c,&net_player_count,0x270);
      iVar3 = _strcmp(&prefs_net_ip_address,&net_slot_addresses);
      if (iVar3 == 0) {
        dbg_log(ADDR(0x62c000, ((u8 *)&g.d_0062c000)));
        net_session_shutdown(&net_session,0);
        cVar1 = net_init_transport(&net_session,net_protocol,1);
        local_c = (int)cVar1;
        if (local_c == 0) {
          dbg_log(ADDR(0x62c034, ((u8 *)&g.d_0062c034)));
          crt_strcpy(&text_string_args,net_connection_title);
          popup_game_with_sprite(ADDR(0x62c06c, ((u8 *)&g.d_0062c06c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
          game_loop_active = 0;
          player_turn_active = 0;
          return 0;
        }
        dbg_log(ADDR(0x62c07c, ((u8 *)&g.d_0062c07c)));
        crt_strcpy(&net_server_address,&prefs_net_ip_address);
        net_server_conn_id = 0;
        net_local_slot = 0;
        diffeng_mirror_end = diffeng_mirror_size + diffeng_mirror_buf;
        net_players_awaited = local_27c[0] - 1;
        net_players_awaited_initial = net_players_awaited;
        if (net_players_awaited < 1) {
          local_8 = local_228[0];
          *(i32 *)(&net_civ_slots + local_228[0] * 4) = 0;
          net_slot_civs = local_228[0];
        }
        else {
          dlg_pending_idle_callback = ((void *)ADDR(0x00402ff4, net_quit_wait_players_idle));
          net_handoff_wait_ticks_i32 = timer_ticks();
          popup_game_sprite_flags(ADDR(0x62c0a0, ((u8 *)&g.d_0062c0a0)),0x2000000,ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
          iVar3 = timer_ticks();
          if ((net_timeout_seconds * 0x3c < iVar3 - net_handoff_wait_ticks_i32) && (net_players_awaited != 0)) {
            crt_strcpy(&text_string_args,net_connection_title);
            if (net_players_awaited == net_players_awaited_initial) {
              popup_game_with_sprite(ADDR(0x62c0b0, ((u8 *)&g.d_0062c0b0)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
              game_loop_active = 0;
              player_turn_active = 0;
              return 0;
            }
            popup_game_with_sprite(ADDR(0x62c0bc, ((u8 *)&g.d_0062c0bc)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
          }
          for (local_284 = 0; local_284 < 7; local_284++) {
            if ((&net_slot_active_flags)[local_284 * 0x54] != '\0') {
              local_280 = 0;
              while ((local_280 < 7 &&
                     (iVar3 = _strcmp(acStack_274 + local_280 * 0x54,
                                      &net_slot_addresses + local_284 * 0x54), iVar3 != 0))) {
                local_280++;
              }
              if (6 < local_280) {
                err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62c0ec, ((u8 *)&g.d_0062c0ec)),ADDR(0x62c0c8, ((u8 *)&g.d_0062c0c8)),0x8a7);
              }
              local_8 = local_228[local_280 * 0x15];
              *(int *)(&net_civ_slots + local_8 * 4) = local_284;
              (&net_slot_civs)[local_284 * 0x15] = local_8;
            }
          }
          mp_simultaneous_moves = (i8)mp_simultaneous_setting;
          net_send_message(0x33,0xff,(int)mp_double_production,(int)mp_double_moves,(int)mp_simultaneous_setting,0,0,0,0
                             ,0);
          net_send_message(4,0xff,0,0,0,0,0,0,0,0);
          XD_FlushSendBuffer(60000);
        }
        _memset(&net_map_lock_slots,-1,0xc0);
        net_session_phase = 3;
        net_reset_error_counts();
        nm_server_quit_count_i32 = 0;
        nm_start_civ_count = 0;
        nm_player_list_count = 0;
        if (game_over_reason != 2) {
          popup_game_with_sprite(ADDR(0x62c108, ((u8 *)&g.d_0062c108)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        }
      }
      else {
        dbg_logf_str(ADDR(0x62c11c, ((u8 *)&g.d_0062c11c)),ADDR(0x6ad57c, ((u8 *)&g.d_006ad57c)));
        local_c = XD_CloseConnection();
        if (local_c != 0) {
          dbg_logf_str_int(ADDR(0x62c13c, ((u8 *)&g.d_0062c13c)),ADDR(0x6ad57c, ((u8 *)&g.d_006ad57c)),local_c);
          crt_strcpy(&text_string_args,net_connection_title);
          popup_game_with_sprite(ADDR(0x62c184, ((u8 *)&g.d_0062c184)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
          game_loop_active = 0;
          player_turn_active = 0;
          return 0;
        }
        crt_strcpy(&net_server_address,&net_slot_addresses);
        net_handoff_wait_ticks_i32 = timer_ticks();
        do {
          iVar3 = timer_ticks();
        } while (iVar3 - net_handoff_wait_ticks_i32 < 0x3c);
        dbg_logf_str(ADDR(0x62c194, ((u8 *)&g.d_0062c194)),ADDR(0x6ad57c, ((u8 *)&g.d_006ad57c)));
        local_c = XD_OpenConnection(&net_server_address,net_timeout_seconds * 1000);
        if (local_c < 0) {
          dbg_logf(ADDR(0x62c1c0, ((u8 *)&g.d_0062c1c0)),local_c);
          crt_strcpy(&text_string_args,net_connection_title);
          popup_game_with_sprite(ADDR(0x62c1f0, ((u8 *)&g.d_0062c1f0)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
          game_loop_active = 0;
          player_turn_active = 0;
          return 0;
        }
        dbg_log(ADDR(0x62c204, ((u8 *)&g.d_0062c204)));
        nm_server_quit_count_i32 = 0;
        nm_start_civ_count = 0;
        dlg_pending_idle_callback = ((void *)ADDR(0x00402f54, net_quit_wait_player_list_idle));
        net_handoff_wait_ticks_i32 = timer_ticks();
        popup_game_sprite_flags(ADDR(0x62c22c, ((u8 *)&g.d_0062c22c)),0x2000000,ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        if (nm_player_list_count == 0) {
          dbg_log(ADDR(0x62c23c, ((u8 *)&g.d_0062c23c)));
          crt_strcpy(&text_string_args,net_connection_title);
          popup_game_with_sprite(ADDR(0x62c27c, ((u8 *)&g.d_0062c27c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
          game_loop_active = 0;
          player_turn_active = 0;
          return 0;
        }
        crt_strcpy(&text_string_args,&net_slot_player_names);
        net_reset_error_counts();
        nm_player_list_count = 0;
        popup_game_with_sprite(ADDR(0x62c28c, ((u8 *)&g.d_0062c28c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      }
      uVar2 = 1;
    }
  }
  return uVar2;
}
#undef diffeng_mirror_end
#undef diffeng_mirror_size
#undef dlg_pending_idle_callback
#undef game_loop_active
#undef game_over_reason
#undef mp_double_moves
#undef mp_double_production
#undef mp_simultaneous_moves
#undef mp_simultaneous_setting
#undef net_connection_title
#undef net_host_handoff_stage
#undef net_local_slot
#undef net_protocol
#undef net_server_conn_id
#undef net_session_phase
#undef net_slot_active_flags
#undef net_slot_civs
#undef net_timeout_seconds
#undef nm_start_civ_count
#undef player_turn_active
#undef prefs_net_ip_address
#undef saved_turn_civ
#undef turn_resume_civ
#undef net_handoff_wait_ticks_i32
#undef nm_server_quit_count_i32
#undef local_284
#undef local_280
#undef local_27c
#undef acStack_274
#undef local_228
#undef local_c
#undef local_8

/* 0048bf51 auto */
#define dialog_stack_top (*(int * *)((u8 *)&g.d_006ad678))
#define game_loop_active (*(char *)((u8 *)&g.d_00628044))
#define net_host_handoff_stage (*(char *)((u8 *)&g.d_006ad698))
#define net_lost_conn_total (*(int *)((u8 *)&g.d_006c8fb4))
#define net_slot_civs (*(iptr *)((u8 *)&g.d_006ad35c))
#define nm_start_civ_count (*(int *)((u8 *)&g.d_006c9038))
#define player_has_quit (*(char *)((u8 *)&g.d_006ad685))
void __cdecl net_client_hot_wait_idle(void)

{
  net_process_messages((NetSession *)&net_session,1,0);
  net_heartbeat_check(net_slot_civs);
  if ((((nm_start_civ_count != 0) || (net_host_handoff_stage != '\0')) || (nm_end_sequence_count != 0)) ||
     (((player_has_quit != '\0' || (game_loop_active == '\0')) || (net_lost_conn_total != 0)))) {
    dialog_stack_top[0xf] = dialog_stack_top[0xf] | 0x400;
    wnd_end_modal_loop((ModalMenuWindow *)(*dialog_stack_top + 0x48));
  }
  return;
}
#undef dialog_stack_top
#undef game_loop_active
#undef net_host_handoff_stage
#undef net_lost_conn_total
#undef net_slot_civs
#undef nm_start_civ_count
#undef player_has_quit

/* 0048d9ad auto */
#define mp_meeting_pending (*(i32 *)((u8 *)&g.d_00626a2c))
#define net_drag_hold (*(char *)((u8 *)&g.d_006c31d0))
#define net_popup_queue_head (*(int *)((u8 *)&g.d_00631130))
#define nm_heartbeat_ack_count (*(i32 *)((u8 *)&g.d_006c9090))
#define nm_parley_cancel_count (*(i32 *)((u8 *)&g.d_006c91e4))
#define net_heartbeat_last_tick_i32 (*(i32 *)((u8 *)&g.d_00673b00))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl net_heartbeat_send(iptr param_1)

{
  if (net_drag_hold == '\0') {
    nm_heartbeat_ack_count = 0;
    net_send_message(0x2b,*(i32 *)
                             (&net_player_slots + *(int *)(&net_civ_slots + param_1 * 4) * 0x54),0,0,0,0,
                       0,0,0,0);
  }
  else {
    nm_heartbeat_ack_count = 1;
  }
  if ((parley_wnd_closed == 1) && (net_popup_queue_head == 0)) {
    mp_meeting_pending = 0;
    nm_parley_cancel_count = 0;
  }
  net_heartbeat_last_tick_i32 = timer_ticks();
  return;
}
#undef mp_meeting_pending
#undef net_drag_hold
#undef net_popup_queue_head
#undef nm_heartbeat_ack_count
#undef nm_parley_cancel_count
#undef net_heartbeat_last_tick_i32

/* 0048da51 auto */
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define net_lost_conn_total (*(int *)((u8 *)&g.d_006c8fb4))
#define nm_heartbeat_ack_count (*(int *)((u8 *)&g.d_006c9090))
#define net_heartbeat_last_tick_i32 (*(i32 *)((u8 *)&g.d_00673b00))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl net_heartbeat_check(iptr param_1)

{
  int iVar1;
  
  iVar1 = timer_ticks();
  if (0xe0f < iVar1 - net_heartbeat_last_tick_i32) {
    if (nm_heartbeat_ack_count == 0) {
      *(int *)(&net_civ_turn_ended + param_1 * 4) = *(int *)(&net_civ_turn_ended + param_1 * 4) + 1;
      if (net_host_flag == '\0') {
        net_lost_conn_total++;
      }
    }
    else {
      net_heartbeat_send(param_1);
    }
  }
  return;
}
#undef net_host_flag
#undef net_lost_conn_total
#undef nm_heartbeat_ack_count
#undef net_heartbeat_last_tick_i32

/* 0048dab9 auto */
#define game_loop_active (*(i8 *)((u8 *)&g.d_00628044))
#define net_claimed_civs_mask (*(ushort *)((u8 *)&g.d_00654fb0))
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define net_lost_conn_total (*(int *)((u8 *)&g.d_006c8fb4))
#define net_slot_active_flags (*(i8 *)((u8 *)&g.d_006ad359))
#define net_slot_civs (*(i32 *)((u8 *)&g.d_006ad35c))
#define nm_lock_nation_count_i32 (*(i32 *)((u8 *)&g.d_006c90a0))
#define local_30 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_24 (*(int (*)[7])(frame_ + FRAME_OFF(12)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(40)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __cdecl net_check_lost_connections(void)

{
  int iVar1;
  bool bVar2;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (net_host_flag == '\0') {
    if (net_lost_conn_total != 0) {
      game_loop_active = 0;
      dbg_log(ADDR(0x62c824, ((u8 *)&g.d_0062c824)));
      net_session_shutdown(&net_session,1);
      popup_game_with_sprite(ADDR(0x62c85c, ((u8 *)&g.d_0062c85c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      return 1;
    }
  }
  else {
    local_28 = net_drop_flagged_players();
    for (local_30 = 1; local_30 < 8; local_30++) {
      bVar2 = true;
      if (((1 << ((byte)local_30 & 0x1f) & (uint)game.civs_alive) != 0) &&
         ((1 << ((byte)local_30 & 0x1f) & (uint)game.human_players) != 0)) {
        for (local_8 = 0; local_8 < 7; local_8++) {
          if (((&net_slot_active_flags)[local_8 * 0x54] != '\0') &&
             ((&net_slot_civs)[local_8 * 0x15] == local_30)) {
            bVar2 = false;
            break;
          }
        }
        if (bVar2) {
          game.human_players = game.human_players & ~(byte)(1 << ((byte)local_30 & 0x1f));
          if ((1 << ((byte)local_30 & 0x1f) & (int)(short)net_claimed_civs_mask) != 0) {
            net_claimed_civs_mask = net_claimed_civs_mask & ~(ushort)(1 << ((byte)local_30 & 0x1f));
            net_send_message(0x2a,0xff,(int)(short)net_claimed_civs_mask,0,0,0,0,0,0,0);
            nm_lock_nation_count_i32++;
          }
          local_28++;
        }
      }
    }
    if (net_lost_conn_total != 0) {
      crt_memcpy(local_24,&net_lost_conn_by_player,0x1c);
      net_reset_error_counts();
      for (local_8 = 1; local_8 < 7; local_8++) {
        if ((0 < local_24[local_8]) && ((&net_slot_active_flags)[local_8 * 0x54] != '\0')) {
          local_28++;
          iVar1 = (&net_slot_civs)[local_8 * 0x15];
          text_set_string_arg(0,(iptr)(&net_slot_player_names + local_8 * 0x54));
          net_send_text_args(0x53,0xff,1,0,0,0);
          *(i32 *)(&net_civ_drop_requested + iVar1 * 4) = 0;
          (*(i8 *)((char *)&local_30 + 0)) = (byte)iVar1;
          game.human_players = game.human_players & ~(byte)(1 << ((byte)local_30 & 0x1f));
          net_remove_player
                    ((NetSession *)&net_session,*(i32 *)(&net_player_slots + local_8 * 0x54));
          if ((1 << ((byte)local_30 & 0x1f) & (int)(short)net_claimed_civs_mask) != 0) {
            net_claimed_civs_mask = net_claimed_civs_mask & ~(ushort)(1 << ((byte)local_30 & 0x1f));
            net_send_message(0x2a,0xff,(int)(short)net_claimed_civs_mask,0,0,0,0,0,0,0);
            nm_lock_nation_count_i32++;
          }
          popup_game_with_sprite(ADDR(0x62c868, ((u8 *)&g.d_0062c868)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        }
      }
    }
    if (local_28 != 0) {
      net_player_count = 0;
      for (local_8 = 0; local_8 < 7; local_8++) {
        if ((&net_slot_active_flags)[local_8 * 0x54] != '\0') {
          net_player_count++;
        }
      }
      net_send_message(4,0xff,0,0,0,0,0,0,0,0);
      net_send_state_diff(0xff,2,0,0,1);
    }
  }
  return 0;
}
#undef game_loop_active
#undef net_claimed_civs_mask
#undef net_host_flag
#undef net_lost_conn_total
#undef net_slot_active_flags
#undef net_slot_civs
#undef nm_lock_nation_count_i32
#undef local_30
#undef local_28
#undef local_24
#undef local_8

/* 0048de75 auto */
#define net_claimed_civs_mask (*(ushort *)((u8 *)&g.d_00654fb0))
#define net_slot_active_flags (*(i8 *)((u8 *)&g.d_006ad359))
#define net_slot_civs (*(i32 *)((u8 *)&g.d_006ad35c))
#define nm_lock_nation_count_i32 (*(i32 *)((u8 *)&g.d_006c90a0))
#define local_10 (*(byte *)(frame_ + FRAME_OFF(0)))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl net_drop_flagged_players(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = 0;
  for (local_8 = 1; local_8 < 7; local_8++) {
    if (((&net_slot_active_flags)[local_8 * 0x54] != '\0') &&
       (*(int *)(&net_civ_drop_requested + (&net_slot_civs)[local_8 * 0x15] * 4) != 0)) {
      local_c++;
      iVar1 = (&net_slot_civs)[local_8 * 0x15];
      *(i32 *)(&net_civ_drop_requested + iVar1 * 4) = 0;
      *(i32 *)(&net_lost_conn_by_player + *(int *)(&net_player_slots + local_8 * 0x54) * 4) = 0;
      local_10 = (byte)iVar1;
      game.human_players = game.human_players & ~(byte)(1 << (local_10 & 0x1f));
      net_remove_player
                ((NetSession *)&net_session,*(i32 *)(&net_player_slots + local_8 * 0x54));
      if ((1 << (local_10 & 0x1f) & (int)(short)net_claimed_civs_mask) != 0) {
        net_claimed_civs_mask = net_claimed_civs_mask & ~(ushort)(1 << (local_10 & 0x1f));
        nm_lock_nation_count_i32++;
      }
    }
  }
  if (local_c != 0) {
    net_send_message(0x2a,0xff,(int)(short)net_claimed_civs_mask,0,0,0,0,0,0,0);
    net_send_message(4,0xff,0,0,0,0,0,0,0,0);
  }
  return local_c;
}
#undef net_claimed_civs_mask
#undef net_slot_active_flags
#undef net_slot_civs
#undef nm_lock_nation_count_i32
#undef local_10
#undef local_c
#undef local_8

/* 004923f0 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define mp_chat_from_start (*(short *)((u8 *)&g.d_00654c7a))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
void __cdecl chat_insert_macro_text(Control *param_1,i32 param_2)

{
  bool bVar1;
  int civ;
  iptr iVar3;
  size_t sVar4;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  text_clear();
  local_14 = 0;
  if (((game.wonder_city[0x18] == -1) && (civ = civ_has_wonder(human_civ,9), civ == 0))
     && (game.reveal_map == '\0')) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  switch(param_2) {
  case 0x2b0:
    while (((((civ = chat_macro_next_adj_civ, local_14 < 8 && (human_civ != chat_macro_next_adj_civ)) && (!bVar1))
            && ((mp_chat_from_start == 0 ||
                ((1 << ((byte)chat_macro_next_adj_civ & 0x1f) & (uint)game.human_players) == 0)))) &&
           ((*(byte *)&civs[chat_macro_next_adj_civ].treaties[human_civ] & 1) == 0))) {
      local_14++;
      chat_macro_next_adj_civ++;
      if (chat_macro_next_adj_civ == 8) {
        chat_macro_next_adj_civ = 1;
      }
    }
    if (local_14 == 8) {
      return;
    }
    chat_macro_next_adj_civ++;
    iVar3 = civ_adjective(civ);
    text_append(iVar3);
    text_append_space();
    if (chat_macro_next_adj_civ == 8) {
      chat_macro_next_adj_civ = 1;
    }
    goto switchD_004926f8_default;
  case 0x2b1:
    while ((((local_14 < 8 && (human_civ != chat_macro_next_leader_civ)) &&
            ((!bVar1 &&
             ((mp_chat_from_start == 0 ||
              ((1 << ((byte)chat_macro_next_leader_civ & 0x1f) & (uint)game.human_players) == 0)))))) &&
           ((*(byte *)&civs[chat_macro_next_leader_civ].treaties[human_civ] & 1) == 0))) {
      local_14++;
      chat_macro_next_leader_civ++;
      if (chat_macro_next_leader_civ == 8) {
        chat_macro_next_leader_civ = 1;
      }
    }
    if (local_14 == 8) {
      return;
    }
    iVar3 = civ_leader_title(chat_macro_next_leader_civ);
    text_append(iVar3);
    text_append_space();
    civ = chat_macro_next_leader_civ;
    chat_macro_next_leader_civ++;
    iVar3 = civ_leader_name(civ);
    text_append(iVar3);
    text_append_space();
    if (chat_macro_next_leader_civ == 8) {
      chat_macro_next_leader_civ = 1;
    }
    goto switchD_004926f8_default;
  case 0x2b2:
    chat_read_macro_line(ADDR(0x62c9a4, ((u8 *)&g.d_0062c9a4)),ADDR(0x62c998, ((u8 *)&g.d_0062c998)));
    civ = chat_macro1_file_offset;
    break;
  case 0x2b3:
    chat_read_macro_line(ADDR(0x62c9b4, ((u8 *)&g.d_0062c9b4)),ADDR(0x62c99c, ((u8 *)&g.d_0062c99c)));
    civ = chat_macro2_file_offset;
    break;
  case 0x2b4:
    chat_read_macro_line(ADDR(0x62c9c4, ((u8 *)&g.d_0062c9c4)),ADDR(0x62c9a0, ((u8 *)&g.d_0062c9a0)));
    civ = chat_macro3_file_offset;
    break;
  default:
    goto switchD_004926f8_default;
  }
  if (civ == 0) {
    return;
  }
switchD_004926f8_default:
  edit_replace_sel(param_1,ADDR(0x679640, ((u8 *)&g.d_00679640)));
  civ = edit_get_sel_end((EditSelEndView *)param_1);
  sVar4 = _strlen(&text_buffer);
  edit_set_sel((EditSelView *)param_1,civ - sVar4,civ);
  return;
}
#undef human_civ
#undef mp_chat_from_start
#undef text_buffer
#undef local_14

/* 0049275a auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define local_a8 (*(i8 (*)[160])(frame_ + FRAME_OFF(0)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(160)))
void __cdecl chat_read_macro_line(iptr param_1,iptr param_2)

{
  int iVar1;
  size_t sVar2;
  i8 frame_[FRAME_OFF(168)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  (*(i32 *)((char *)&local_a8 + 156)) = &LAB_00492874;
  file_obj_init((FileObject *)local_a8);
  local_8 = 0;
  iVar1 = file_obj_open((FileObject *)local_a8,param_1);
  if (iVar1 == 0) {
    *(i32 *)param_2 = 0;
    local_8 = 0xffffffff;
    /* inlined unwind funclet 00492868 */ { file_obj_close((FileObject *)((iptr)&local_a8)); }
  }
  else {
    iVar1 = file_obj_get_size((FileObject *)local_a8);
    if (iVar1 <= *(int *)param_2) {
      *(i32 *)param_2 = 0;
    }
    iVar1 = file_obj_seek_cur((FileSeekView *)local_a8,*(i32 *)param_2);
    if (iVar1 == 0) {
      *(i32 *)param_2 = 0;
      file_map_close((FileObject *)local_a8);
      local_8 = 0xffffffff;
      /* inlined unwind funclet 00492868 */ { file_obj_close((FileObject *)((iptr)&local_a8)); }
    }
    else {
      file_obj_read_line((FileReadLineView *)local_a8,ADDR(0x679640, ((u8 *)&g.d_00679640)),0x100);
      file_map_close((FileObject *)local_a8);
      sVar2 = _strlen(&text_buffer);
      *(size_t *)param_2 = *(int *)param_2 + sVar2 + 2;
      local_8 = 0xffffffff;
      /* inlined unwind funclet 00492868 */ { file_obj_close((FileObject *)((iptr)&local_a8)); }
    }
  }
  return;
}
#undef text_buffer
#undef local_a8
#undef local_8

/* 004af3e0 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define local_40 (*(u8 * *)(frame_ + FRAME_OFF(0)))
#define local_3c (*(u8 * *)(frame_ + FRAME_OFF(4)))
#define local_38 (*(i32 *)(frame_ + FRAME_OFF(8)))
#define local_30 (*(i32 *)(frame_ + FRAME_OFF(16)))
#define local_28 (*(u32 *)(frame_ + FRAME_OFF(24)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(28)))
#define local_20 (*(i32 *)(frame_ + FRAME_OFF(32)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(36)))
#define local_18 (*(i32 *)(frame_ + FRAME_OFF(40)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(44)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(48)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(52)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(56)))
void __thiscall parley_build_civ_list(ListPaneWindow *this,iptr param_1,int param_2)

{
  u8 *puVar1;
  int iVar2;
  int iVar3;
  Control *pCVar4;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  local_24 = *(int *)param_1;
  local_20 = *(i32 *)(param_1 + 4);
  local_1c = *(int *)(param_1 + 8);
  local_18 = *(i32 *)(param_1 + 0xc);
  if (game.wonder_city[0x18] == -1) {
    iVar2 = civ_has_wonder(human_civ,9);
    if ((iVar2 == 0) && (game.reveal_map == '\0')) {
      local_14 = 0;
      goto LAB_004af467;
    }
  }
  local_14 = 1;
LAB_004af467:
  puVar1 = this[3].pad_48 + param_2 * 4 + 0x4c;
  puVar1[0] = '\0';
  puVar1[1] = '\0';
  puVar1[2] = '\0';
  puVar1[3] = '\0';
  for (local_28 = 1; (int)local_28 < 8; local_28++) {
    if (((human_civ != local_28) && (this->caption_height != local_28)) &&
       ((local_14 != 0 || ((*(byte *)&civs[human_civ].treaties[local_28] & 1) != 0))))
    {
      *(u32 *)(param_2 * 0x2004 + *(int *)(this[3].pad_48 + param_2 * 4 + 0x4c) * 4 + 0x3f0 +
              (int)this) = local_28;
      *(i32 *)
       (param_2 * 0x2004 + *(int *)(this[3].pad_48 + param_2 * 4 + 0x4c) * 4 + 0x8400 + (int)this) =
           0;
      *(int *)(this[3].pad_48 + param_2 * 4 + 0x4c) =
           *(int *)(this[3].pad_48 + param_2 * 4 + 0x4c) + 1;
    }
  }
  if (*(int *)(this[3].pad_48 + param_2 * 4 + 0x4c) < 1) {
    puVar1 = this[0xea].pad_48 + param_2 * 4 + 0x30;
    puVar1[0] = 0xff;
    puVar1[1] = 0xff;
    puVar1[2] = 0xff;
    puVar1[3] = 0xff;
  }
  else {
    puVar1 = this[0xea].pad_48 + param_2 * 4 + 0x30;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
  }
  puVar1 = this[3].pad_48 + param_2 * 4 + 0x44;
  puVar1[0] = 2;
  puVar1[1] = '\0';
  puVar1[2] = '\0';
  puVar1[3] = '\0';
  *(i32 *)(this[3].pad_48 + param_2 * 0x10 + 0x24) = *(i32 *)param_1;
  *(i32 *)(this[3].pad_48 + param_2 * 0x10 + 0x28) = *(i32 *)(param_1 + 4);
  *(i32 *)(this[3].pad_48 + param_2 * 0x10 + 0x2c) = *(i32 *)(param_1 + 8);
  *(i32 *)(this[3].pad_48 + param_2 * 0x10 + 0x30) = *(i32 *)(param_1 + 0xc);
  if (*(int *)(this[0xea].pad_48 + param_2 * 4 + 0x40) <
      *(int *)(this[3].pad_48 + param_2 * 4 + 0x4c)) {
    iVar3 = GetSystemMetrics(2);
    iVar2 = local_1c;
    *(int *)(this[3].pad_48 + param_2 * 0x10 + 0x2c) =
         *(int *)(this[3].pad_48 + param_2 * 0x10 + 0x2c) - iVar3;
    local_24 = GetSystemMetrics(2);
    local_24 = iVar2 - local_24;
    pCVar4 = operator_new(0x40);
    local_8 = 0;
    if (pCVar4 == (Control *)0x0) {
      local_30 = 0;
    }
    else {
      local_30 = scrollbar_ctor(pCVar4);
    }
    local_8 = 0xffffffff;
    *(i32 *)(this[3].pad_48 + param_2 * 4 - 0x20) = local_30;
    if (this == (ListPaneWindow *)0x0) {
      local_3c = (u8 *)0x0;
    }
    else {
      local_3c = this->pad_48;
    }
    scrollbar_create
              (*(Control **)(this[3].pad_48 + param_2 * 4 - 0x20),(iptr)local_3c,
               param_2 + 0x40d,(iptr)&local_24,1);
    scrollbar_set_range
              (*(Control **)(this[3].pad_48 + param_2 * 4 - 0x20),0,
               *(int *)(this[3].pad_48 + param_2 * 4 + 0x4c) -
               *(int *)(this[0xea].pad_48 + param_2 * 4 + 0x40));
    scrollbar_set_pos(*(ClickControl **)(this[3].pad_48 + param_2 * 4 - 0x20),0);
    scrollbar_set_page_size
              (*(Control **)(this[3].pad_48 + param_2 * 4 - 0x20),
               *(i32 *)(this[0xea].pad_48 + param_2 * 4 + 0x40));
    scrollbar_set_callback
              (*(Control **)(this[3].pad_48 + param_2 * 4 - 0x20),
               (iptr)(((void *)ADDR(0x00401410, parley_civ_list_scroll_local)) + ((param_2 == 0) - 1 & 0xb3b)));
    scrollbar_set_track_callback
              (*(ScrollbarTrackSetView **)(this[3].pad_48 + param_2 * 4 - 0x20),
               (iptr)(((void *)ADDR(0x00401410, parley_civ_list_scroll_local)) + ((param_2 == 0) - 1 & 0xb3b)));
  }
  pCVar4 = operator_new(0x40);
  local_8 = 1;
  if (pCVar4 == (Control *)0x0) {
    local_38 = 0;
  }
  else {
    local_38 = hotspot_ctor(pCVar4);
  }
  local_8 = 0xffffffff;
  *(i32 *)(this[3].pad_48 + param_2 * 4 - 0x18) = local_38;
  if (this == (ListPaneWindow *)0x0) {
    local_40 = (u8 *)0x0;
  }
  else {
    local_40 = this->pad_48;
  }
  hotspot_create
            (*(ClickControl **)(this[3].pad_48 + param_2 * 4 - 0x18),(iptr)local_40,
             param_2 + 0x40f,(iptr)(this[3].pad_48 + param_2 * 0x10 + 0x24));
  hotspot_set_click_callback(*(HotspotClickSetView **)(this[3].pad_48 + param_2 * 4 - 0x18),ADDR(0x401e42, parley_civ_list_click));
  hotspot_set_dblclick_callback(*(HotspotDblClickSetView **)(this[3].pad_48 + param_2 * 4 - 0x18),ADDR(0x401e42, parley_civ_list_click));
  parley_draw_civ_list(param_2);
  return;
}
#undef human_civ
#undef local_40
#undef local_3c
#undef local_38
#undef local_30
#undef local_28
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef puStack_c
#undef local_8

/* 004af867 auto */
void __cdecl parley_civ_list_scroll_local(i32 param_1)

{
  parley_civ_list_scroll(0,param_1);
  return;
}

/* 004af8a3 auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl parley_civ_list_scroll(int param_1,i32 param_2)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar1 - 0x48;
  }
  wnd_activate((Wnd *)(local_8 + 0x48));
  *(i32 *)(local_8 + 0x10410 + param_1 * 4) = param_2;
  parley_draw_civ_list(param_1);
  return;
}
#undef local_8

/* 004af904 auto */
#define local_1c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(12)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(16)))
#define local_c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(24)))
void __cdecl parley_civ_list_click(int param_1)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar2 = wnd_get_active_child();
  if (iVar2 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar2 - 0x48;
  }
  wnd_activate((Wnd *)(local_8 + 0x48));
  local_c = param_1 - 0x40f;
  wnd_get_cursor_pos
            ((WndBase *)(local_8 + 0x48),(iptr)&local_10,(iptr)&local_14);
  if (((*(int *)(local_8 + 1000 + local_c * 4) != 0) &&
      (iVar2 = parley_civ_list_hit_test(local_10,local_14,local_c), -1 < iVar2)) &&
     (iVar2 < *(int *)(local_8 + 1000 + local_c * 4))) {
    iVar3 = wnd_is_shift_down((void *)(local_8 + 0x48));
    if (iVar3 == 0) {
      iVar3 = wnd_is_ctrl_down((void *)(local_8 + 0x48));
      if (iVar3 == 0) {
        for (local_18 = 0; local_18 < *(int *)(local_8 + 1000 + local_c * 4);
            local_18 = local_18 + 1) {
          if (local_18 != iVar2) {
            *(i32 *)(local_18 * 4 + local_c * 0x2004 + 0x8400 + local_8) = 0;
          }
        }
        *(int *)(local_8 + 0x10418 + local_c * 4) = iVar2;
        puVar1 = (uint *)(iVar2 * 4 + local_c * 0x2004 + 0x8400 + local_8);
        *puVar1 = *puVar1 ^ 1;
      }
      else {
        *(int *)(local_8 + 0x10418 + local_c * 4) = iVar2;
        puVar1 = (uint *)(iVar2 * 4 + local_c * 0x2004 + 0x8400 + local_8);
        *puVar1 = *puVar1 ^ 1;
      }
    }
    else {
      for (local_18 = 0; local_18 < *(int *)(local_8 + 1000 + local_c * 4); local_18++)
      {
        *(i32 *)(local_18 * 4 + local_c * 0x2004 + 0x8400 + local_8) = 0;
      }
      if (*(int *)(local_8 + 0x10418 + local_c * 4) < iVar2) {
        local_18 = *(int *)(local_8 + 0x10418 + local_c * 4);
        local_1c = iVar2;
      }
      else {
        local_1c = *(int *)(local_8 + 0x10418 + local_c * 4);
        local_18 = iVar2;
      }
      for (; local_18 <= local_1c; local_18++) {
        *(i32 *)(local_18 * 4 + local_c * 0x2004 + 0x8400 + local_8) = 1;
      }
    }
    parley_draw_civ_list(local_c);
  }
  return;
}
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 004afb77 auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
int __cdecl parley_civ_list_hit_test(int param_1,int param_2,int param_3)

{
  iptr iVar1;
  int iVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar1 - 0x48;
  }
  if (param_2 < *(int *)(param_3 * 0x10 + 0x3c4 + local_8)) {
    iVar2 = -1;
  }
  else if (param_2 < *(int *)(param_3 * 0x10 + 0x3cc + local_8)) {
    if (param_1 < *(int *)(param_3 * 0x10 + 0x3c0 + local_8)) {
      iVar2 = -3;
    }
    else if (param_1 < *(int *)(param_3 * 0x10 + 0x3c8 + local_8)) {
      iVar2 = *(int *)(param_3 * 0x10 + 0x3c4 + local_8);
      iVar3 = rect_height(param_3 * 0x10 + local_8 + 0x3c0);
      iVar2 = (param_2 - iVar2) / (iVar3 / *(int *)(local_8 + 0x10420 + param_3 * 4)) +
              *(int *)(local_8 + 0x10410 + param_3 * 4);
    }
    else {
      iVar2 = -4;
    }
  }
  else {
    iVar2 = -2;
  }
  return iVar2;
}
#undef local_8

/* 004afc89 auto */
#define dlg_sel_text_color (*(int *)((u8 *)&g.d_00635a28))
#define dlg_sel_text_shadow_color (*(int *)((u8 *)&g.d_00635a2c))
#define list_bg_color (*(i32 *)((u8 *)&g.d_00635a18))
#define list_sel_bg_color (*(i32 *)((u8 *)&g.d_00635a24))
#define list_shadow_color (*(int *)((u8 *)&g.d_00635a20))
#define list_text_color (*(int *)((u8 *)&g.d_00635a1c))
#define panel_margin_x (*(int *)((u8 *)&g.d_0062d858))
#define local_5c (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_50 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_40 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_34 (*(ViewWindow * *)(frame_ + FRAME_OFF(44)))
#define local_2c (*(tagRECT *)(frame_ + FRAME_OFF(52)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(68)))
#define local_18 (*(i8 (*)[16])(frame_ + FRAME_OFF(72)))
#define local_8 (*(GameFont * *)(frame_ + FRAME_OFF(88)))
void __cdecl parley_draw_civ_list(int param_1)

{
  u8 *puVar1;
  int xLeft;
  int iVar2;
  iptr iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  i32 uVar8;
  iptr iVar9;
  i8 frame_[FRAME_OFF(96)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar3 = wnd_get_active_child();
  if (iVar3 == 0) {
    local_34 = (ViewWindow *)0x0;
  }
  else {
    local_34 = (ViewWindow *)(iVar3 - 0x48);
  }
  surface_get_clip((DibSurface *)local_34,(iptr)local_18);
  surface_set_clip((DibSurface *)local_34,(iptr)(local_34->pad_3c0 + param_1 * 0x10));
  surface_fill_rect
            ((DibSurface *)local_34,(iptr)(local_34->pad_3c0 + param_1 * 0x10),list_bg_color);
  if (local_34->field_154 == 0) {
    local_8 = (GameFont *)&font_size14;
  }
  else {
    local_8 = (GameFont *)&font_size21;
  }
  xLeft = *(int *)(local_34->pad_3c0 + param_1 * 0x10);
  iVar4 = rect_width((iptr)(local_34->pad_3c0 + param_1 * 0x10));
  local_1c = rect_height((iptr)(local_34->pad_3c0 + param_1 * 0x10));
  local_1c = local_1c / *(int *)(local_34[0x3e].pad_48 + param_1 * 4 + 0x38);
  iVar5 = local_1c / 2;
  iVar6 = font_cached_height(local_8);
  iVar5 -= iVar6 / 2;
  puVar1 = local_34->pad_200 + param_1 * 4 - 0x1c;
  puVar1[0] = '\0';
  puVar1[1] = '\0';
  puVar1[2] = '\0';
  puVar1[3] = '\0';
  local_50 = 0;
  do {
    if (*(int *)(local_34->pad_3c0 + param_1 * 4 + 0x28) <= local_50) {
LAB_004afe04:
      for (local_50 = 0; local_50 < *(int *)(local_34[0x3e].pad_48 + param_1 * 4 + 0x38);
          local_50 = local_50 + 1) {
        iVar6 = *(int *)(local_34->pad_3c0 + param_1 * 0x10 + 4) + local_1c * local_50;
        SetRect(&local_2c,xLeft,iVar6,iVar4 + xLeft,local_1c + iVar6);
        if (((local_50 == 0) || (*(int *)(local_34[0x3e].pad_48 + param_1 * 4 + 0x28) != -1)) &&
           (*(int *)(local_34[0x3e].pad_48 + param_1 * 4 + 0x28) + local_50 <
            *(int *)(local_34->pad_3c0 + param_1 * 4 + 0x28))) {
          iVar2 = *(int *)(param_1 * 0x2004 +
                           (*(int *)(local_34[0x3e].pad_48 + param_1 * 4 + 0x28) + local_50) * 4 +
                           0x8400 + (int)local_34);
          if (iVar2 == 0) {
            local_38 = list_text_color;
            local_40 = list_shadow_color;
          }
          else {
            local_38 = dlg_sel_text_color;
            local_40 = dlg_sel_text_shadow_color;
          }
          iVar7 = (-(uint)(local_34->field_154 == 0) & 0xffffffe2) + 0x5a + panel_margin_x;
          local_2c.left = local_2c.left + iVar7 - 3;
          if (iVar2 == 0) {
            local_5c = list_bg_color;
          }
          else {
            local_5c = list_sel_bg_color;
          }
          surface_fill_rect((DibSurface *)local_34,(iptr)&local_2c,local_5c);
          if (*(int *)(local_34[0x3e].pad_48 + param_1 * 4 + 0x28) == -1) {
            text_clear();
            iVar9 = label_string(*(i32 *)(label_string_ids + 0xb84));
            text_append(iVar9);
            puVar1 = local_34->pad_200 + param_1 * 4 - 0x1c;
            puVar1[0] = '\0';
            puVar1[1] = '\0';
            puVar1[2] = '\0';
            puVar1[3] = '\0';
          }
          else {
            uVar8 = font_cached_height(local_8);
            parley_draw_civ_capital(*(i32 *)
                                (param_1 * 0x2004 +
                                 (*(int *)(local_34[0x3e].pad_48 + param_1 * 4 + 0x28) + local_50) *
                                 4 + 0x3f0 + (int)local_34),
                               *(int *)(local_34[0x3e].pad_48 + param_1 * 4 + 0x28) + local_50,
                               xLeft + 2,iVar6,uVar8);
            text_clear();
            iVar9 = civ_name_plural(*(iptr *)(param_1 * 0x2004 +
                                                 (*(int *)(local_34[0x3e].pad_48 +
                                                          param_1 * 4 + 0x28) + local_50) * 4 +
                                                 0x3f0 + (int)local_34));
            text_append(iVar9);
            text_append_space();
            text_append_lparen();
            iVar9 = civ_leader_name(*(iptr *)(param_1 * 0x2004 +
                                                 (*(int *)(local_34[0x3e].pad_48 +
                                                          param_1 * 4 + 0x28) + local_50) * 4 +
                                                 0x3f0 + (int)local_34));
            text_append(iVar9);
            text_append_rparen();
          }
          if (local_40 != local_38) {
            gfx_set_text_color_index(local_40);
            surface_draw_text
                      ((DibSurface *)local_34,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar7 + xLeft + 2,
                       iVar5 + iVar6 + 1,5);
            gfx_set_text_color_index(local_38);
            surface_draw_text
                      ((DibSurface *)local_34,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar7 + xLeft + 1,
                       iVar5 + iVar6,5);
          }
          gfx_set_text_color_index(local_38);
          surface_draw_text
                    ((DibSurface *)local_34,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),iVar7 + xLeft,iVar5 + iVar6,5)
          ;
        }
      }
      surface_set_clip((DibSurface *)local_34,(iptr)local_18);
      parley_update_buttons(local_34);
      ctrl_show_and_redraw(*(Control **)(local_34->pad_364 + param_1 * 4 + 0x20))
      ;
      return;
    }
    if (*(int *)(param_1 * 0x2004 + local_50 * 4 + 0x8400 + (int)local_34) != 0) {
      puVar1 = local_34->pad_200 + param_1 * 4 - 0x1c;
      puVar1[0] = 1;
      puVar1[1] = '\0';
      puVar1[2] = '\0';
      puVar1[3] = '\0';
      goto LAB_004afe04;
    }
    local_50++;
  } while( true );
}
#undef dlg_sel_text_color
#undef dlg_sel_text_shadow_color
#undef list_bg_color
#undef list_sel_bg_color
#undef list_shadow_color
#undef list_text_color
#undef panel_margin_x
#undef local_5c
#undef local_50
#undef local_40
#undef local_38
#undef local_34
#undef local_2c
#undef local_1c
#undef local_18
#undef local_8

/* 004b0157 auto */
#define city2 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_2c (*(i32 *)(frame_ + FRAME_OFF(4)))
#define city (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_14 (*(iptr *)(frame_ + FRAME_OFF(28)))
#define local_c (*(int *)(frame_ + FRAME_OFF(36)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(40)))
void __cdecl parley_draw_civ_capital(int civ,uint param_2,int param_3,int param_4,int param_5)

{
  iptr iVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_14 = 0;
  }
  else {
    local_14 = iVar1 - 0x48;
  }
  if (*(int *)(local_14 + 0x154) == 0) {
    local_2c = 0xfffffffc;
  }
  else {
    local_2c = 0xfffffffe;
  }
  local_c = 0;
  city2 = -1;
  for (city = 0; city < game.num_cities; city++) {
    if ((cities[city].id != 0) && (cities[city].owner == civ)) {
      local_8 = (int)cities[city].size;
      iVar2 = city_has_improvement(city,1);
      if (iVar2 != 0) {
        local_8 += 200;
      }
      if (cities[city].building == -1) {
        local_8 += 100;
      }
      if (local_c < local_8) {
        local_c = local_8;
        city2 = city;
      }
    }
  }
  if (-1 < city2) {
    local_20 = param_3;
    if (*(int *)(local_14 + 0x154) == 0) {
      local_18 = 0x18;
    }
    else {
      local_18 = 0x24;
    }
    if ((param_2 & 1) != 0) {
      local_20 = param_3 + local_18 + 2;
    }
    iVar2 = gfx_zoom_scale(0x30,local_2c);
    gfx_draw_city(ADDR(0x67a7a8, ((u8 *)&g.d_0067a7a8)),city2,0,local_20,param_4 - (iVar2 - param_5) / 2,local_2c);
  }
  return;
}
#undef city2
#undef local_2c
#undef city
#undef local_20
#undef local_18
#undef local_14
#undef local_c
#undef local_8

/* 004b0b53 auto */
#define diffeng_mirror_end (*(int * *)((u8 *)&g.d_0067a408))
#define diffeng_mirror_size (*(i32 *)((u8 *)&g.d_0067a400))
#define diffeng_scan_ptr (*(int * *)((u8 *)&g.d_00679fe8))
#define diffeng_scan_section (*(uint *)((u8 *)&g.d_0067a404))
#define diffeng_send_count_i32 (*(i32 *)((u8 *)&g.d_0062d0c4))
#define diffeng_scan_offset_i32 (*(i32 *)((u8 *)&g.d_00679fec))
#define diffeng_packet_i32 (*(i32 *)((u8 *)&g.d_00679ff0))
#define diffeng_packet_msg_type_i32 (*(i32 *)((u8 *)&g.d_00679ff4))
#define diffeng_packet_size_i32 (*(i32 *)((u8 *)&g.d_00679ff8))
#define diffeng_packet_record_count_i32 (*(i32 *)((u8 *)&g.d_0067a000))
#define local_4c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_48 (*(uint *)(frame_ + FRAME_OFF(8)))
#define local_44 (*(uint *)(frame_ + FRAME_OFF(12)))
#define local_40 (*(int * *)(frame_ + FRAME_OFF(16)))
#define local_38 (*(int * *)(frame_ + FRAME_OFF(24)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(28)))
#define local_30 (*(uint * *)(frame_ + FRAME_OFF(32)))
#define local_2c (*(i32 * *)(frame_ + FRAME_OFF(36)))
#define local_28 (*(uint *)(frame_ + FRAME_OFF(40)))
#define local_24 (*(int * *)(frame_ + FRAME_OFF(44)))
#define local_20 (*(uint *)(frame_ + FRAME_OFF(48)))
#define local_1c (*(iptr *)(frame_ + FRAME_OFF(52)))
#define local_18 (*(uint * *)(frame_ + FRAME_OFF(56)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(60)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(64)))
#define local_c (*(int *)(frame_ + FRAME_OFF(68)))
#define local_8 (*(int * *)(frame_ + FRAME_OFF(72)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl
net_send_state_diff(i32 param_1,uint param_2,int param_3,i32 param_4,i32 param_5)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(80)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (game.multiplayer < 3) {
    local_4c = 0;
  }
  else if (((char)param_4 == '\0') && (net_player_count == 1)) {
    local_4c = 0;
  }
  else {
    local_4c = 0;
    local_10 = 0;
    local_c = 0;
    local_24 = diffeng_scan_ptr;
    diffeng_send_count_i32++;
    if ((param_2 & 1) != 0) {
      diffeng_invalidate_mirror();
    }
    if ((param_2 & 4) == 0) {
      if ((param_2 & 8) != 0) {
        local_10 = param_3;
      }
    }
    else {
      local_c = timer_ticks();
      local_c = param_3 + local_c;
    }
    local_40 = (int *)((&diffeng_section_ptrs)[diffeng_scan_section * 6] + diffeng_scan_offset_i32);
    local_8 = (int *)((&diffeng_section_padded_sizes)[diffeng_scan_section * 6] + (&diffeng_section_ptrs)[diffeng_scan_section * 6]);
    if (diffeng_scan_section == 1) {
      local_1c = diffeng_game_offset + diffeng_mirror_buf;
      *(i16 *)(local_1c + 0x16) = game.active_unit;
      *(i16 *)(local_1c + 0x18) = game.moving_unit;
      *(u8 *)(local_1c + 0x1a) = game.multiplayer;
      *(i8 *)(local_1c + 0x1b) = game.player_civ;
      *(i8 *)(local_1c + 0x1c) = game.field_1c;
      *(i8 *)(local_1c + 0x1d) = game.turn_civ;
      *(u32 *)(local_1c + 2) = game.game_options;
      *(u16 *)(local_1c + 10) = game.message_options;
    }
    diffeng_packet_i32 = 0x66606660;
    if ((char)param_5 == '\0') {
      diffeng_packet_msg_type_i32 = 0x15;
    }
    else {
      diffeng_packet_msg_type_i32 = 0x5c;
    }
    local_18 = &diffeng_packet_payload;
    local_14 = 0;
    do {
      piVar2 = local_40;
      piVar1 = diffeng_scan_ptr;
      if (*local_40 == *diffeng_scan_ptr) {
        diffeng_scan_ptr++;
        if (diffeng_scan_ptr < diffeng_mirror_end) {
          local_40++;
          if (local_8 <= local_40) {
            diffeng_scan_section++;
            if (diffeng_scan_section == 1) {
              local_1c = diffeng_game_offset + diffeng_mirror_buf;
              *(i16 *)(local_1c + 0x16) = game.active_unit;
              *(i16 *)(local_1c + 0x18) = game.moving_unit;
              *(u8 *)(local_1c + 0x1a) = game.multiplayer;
              *(i8 *)(local_1c + 0x1b) = game.player_civ;
              *(i8 *)(local_1c + 0x1c) = game.field_1c;
              *(i8 *)(local_1c + 0x1d) = game.turn_civ;
              *(u32 *)(local_1c + 2) = game.game_options;
              *(u16 *)(local_1c + 10) = game.message_options;
            }
            diffeng_scan_offset_i32 = 0;
            local_40 = (int *)(&diffeng_section_ptrs)[diffeng_scan_section * 6];
            local_8 = (int *)((&diffeng_section_padded_sizes)[diffeng_scan_section * 6] + (&diffeng_section_ptrs)[diffeng_scan_section * 6]
                             );
          }
        }
        else {
          diffeng_scan_ptr = (int *)diffeng_mirror_buf;
          diffeng_scan_section = 0;
          diffeng_scan_offset_i32 = 0;
          local_40 = (int *)diffeng_section_ptrs;
          local_8 = (int *)(diffeng_section_padded_sizes + diffeng_section_ptrs);
        }
      }
      else {
        local_44 = 0;
        do {
          diffeng_scan_ptr++;
          if (diffeng_scan_ptr < diffeng_mirror_end) {
            local_40++;
            if (local_8 <= local_40) {
              local_20 = (int)piVar2 - (&diffeng_section_ptrs)[diffeng_scan_section * 6];
              local_44 = (int)local_8 - (int)piVar2;
              local_48 = diffeng_scan_section;
              diffeng_scan_section++;
              if (diffeng_scan_section == 1) {
                local_1c = diffeng_game_offset + diffeng_mirror_buf;
                *(i16 *)(local_1c + 0x16) = game.active_unit;
                *(i16 *)(local_1c + 0x18) = game.moving_unit;
                *(u8 *)(local_1c + 0x1a) = game.multiplayer;
                *(i8 *)(local_1c + 0x1b) = game.player_civ;
                *(i8 *)(local_1c + 0x1c) = game.field_1c;
                *(i8 *)(local_1c + 0x1d) = game.turn_civ;
                *(u32 *)(local_1c + 2) = game.game_options;
                *(u16 *)(local_1c + 10) = game.message_options;
              }
              diffeng_scan_offset_i32 = 0;
              local_40 = (int *)(&diffeng_section_ptrs)[diffeng_scan_section * 6];
              local_8 = (int *)((&diffeng_section_padded_sizes)[diffeng_scan_section * 6] +
                               (&diffeng_section_ptrs)[diffeng_scan_section * 6]);
            }
          }
          else {
            local_20 = (int)piVar2 - (&diffeng_section_ptrs)[diffeng_scan_section * 6];
            local_44 = (int)diffeng_mirror_end - (int)piVar1;
            local_48 = diffeng_scan_section;
            diffeng_scan_ptr = (int *)diffeng_mirror_buf;
            diffeng_scan_section = 0;
            diffeng_scan_offset_i32 = 0;
            local_40 = (int *)diffeng_section_ptrs;
            local_8 = (int *)(diffeng_section_padded_sizes + diffeng_section_ptrs);
          }
        } while (((local_44 == 0) &&
                 ((int)diffeng_scan_ptr + (-ADDR(0x679ff0, ((u8 *)&g.d_00679ff0)) - (int)piVar1) + (int)local_18 < diffeng_packet_flush_size)) &&
                (*local_40 != *diffeng_scan_ptr));
        if (0x400 < local_44) {
          err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62d13c, ((u8 *)&g.d_0062d13c)),ADDR(0x62d114, ((u8 *)&g.d_0062d114)),0xee);
        }
        if (local_44 == 0) {
          local_20 = (int)piVar2 - (&diffeng_section_ptrs)[diffeng_scan_section * 6];
          local_48 = diffeng_scan_section;
          local_44 = (int)diffeng_scan_ptr - (int)piVar1;
        }
        if (0x400 < local_44) {
          err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62d190, ((u8 *)&g.d_0062d190)),ADDR(0x62d168, ((u8 *)&g.d_0062d168)),0xf7);
        }
        if ((param_2 & 0x10) == 0) {
          crt_memcpy(piVar1,piVar2,local_44);
        }
        local_38 = piVar2;
        local_34 = (int)piVar2 + local_44;
        local_30 = local_18 + 3;
        local_2c = &diffeng_mirror_size;
        iVar3 = diffeng_rle_encode((iptr)&local_38);
        if (iVar3 == 0) {
          crt_memcpy(local_18 + 3,piVar2,local_44);
          *local_18 = local_48;
          local_18[1] = local_20;
          local_18[2] = local_44;
          local_18 = (uint *)((int)local_18 + local_44 + 0xc);
        }
        else {
          *local_18 = local_48 | 0x8000;
          local_18[1] = local_20;
          local_18[2] = local_28;
          local_18 = (uint *)((int)local_18 + local_28 + 0xc);
        }
        local_14++;
        local_4c += local_44;
        if (diffeng_packet_flush_size <= (int)(local_18 - 0x19e7fc)) {
          diffeng_packet_size_i32 = local_18 - 0x19e7fc;
          diffeng_packet_record_count_i32 = local_14;
          net_send_message(0x5c,param_1,0,0,0,0,0,0,0,ADDR(0x679ff0, ((u8 *)&g.d_00679ff0)));
          if ((param_2 & 1) != 0) {
            XD_FlushSendBuffer(5000);
          }
          local_18 = &diffeng_packet_payload;
          local_14 = 0;
        }
        if ((((param_2 & 4) != 0) && (iVar3 = timer_ticks(), local_c < iVar3)) ||
           (((param_2 & 8) != 0 && (local_10 = local_10 - 1, local_10 == 0)))) break;
      }
    } while (local_24 != diffeng_scan_ptr);
    if (&diffeng_packet_payload < local_18) {
      diffeng_packet_size_i32 = local_18 - 0x19e7fc;
      diffeng_packet_record_count_i32 = local_14;
      net_send_message(0x5c,param_1,0,0,0,0,0,0,0,ADDR(0x679ff0, ((u8 *)&g.d_00679ff0)));
      if ((param_2 & 1) != 0) {
        XD_FlushSendBuffer(5000);
      }
    }
    diffeng_scan_offset_i32 = (int)local_40 - (&diffeng_section_ptrs)[diffeng_scan_section * 6];
  }
  return local_4c;
}
#undef diffeng_mirror_end
#undef diffeng_mirror_size
#undef diffeng_scan_ptr
#undef diffeng_scan_section
#undef diffeng_send_count_i32
#undef diffeng_scan_offset_i32
#undef diffeng_packet_i32
#undef diffeng_packet_msg_type_i32
#undef diffeng_packet_size_i32
#undef diffeng_packet_record_count_i32
#undef local_4c
#undef local_48
#undef local_44
#undef local_40
#undef local_38
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
  parley_wnd_ctor((ViewWindow *)&parley_wnd,ADDR(0x6665da, ((u8 *)&g.d_006665da)));
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
  parley_wnd_dtor((ViewWindow *)&parley_wnd);
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
  parley_wnd_ctor((ViewWindow *)&chat_wnd,ADDR(0x6665ea, ((u8 *)&g.d_006665ea)));
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
  parley_wnd_dtor((ViewWindow *)&chat_wnd);
  return;
}

/* 004b4108 auto */
#define chat_input_buffer (*(i32 *)((u8 *)&g.d_0062d86c))
#define chat_log_buffer (*(i32 *)((u8 *)&g.d_0062d870))
#define chat_log_capacity (*(i32 *)((u8 *)&g.d_0069b03c))
#define local_18 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(8)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(16)))
ViewWindow * __thiscall parley_wnd_ctor(ViewWindow *this,iptr param_1)

{
  u8 *puVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  surfwnd_ctor((SurfaceWindow *)this);
  local_8 = 0;
  this->vtable = (u32)&PTR_FUN_0061d6c4;
  this->init_rect = param_1;
  this->style_flags = 1;
  prefs_load_civ2dat();
  iVar2 = rect_width(this->init_rect);
  if (iVar2 < 1) {
    this->border_width = 0;
    this->resize_border = 0;
  }
  else {
    this->border_width = *(u32 *)this->init_rect;
    this->resize_border = *(u32 *)(this->init_rect + 4);
    if (iVar2 < 0x321) {
      this->large_layout = 0;
    }
    else {
      this->large_layout = 1;
    }
  }
  this->close_button = 0;
  this->field_2a0 = 0;
  this->field_2a4 = 0;
  this->field_340 = 0;
  this->field_344 = 0;
  this->field_348 = 0;
  this->field_354 = 0;
  this->field_34c = 0;
  this->field_350 = 0;
  this->field_358 = 0;
  this->field_35c = 0;
  this->field_360 = 0;
  for (local_18 = 0; local_18 < 8; local_18++) {
    puVar1 = this->pad_2c4 + local_18 * 4 - 0x1c;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
    puVar1 = this->pad_2c4 + local_18 * 4 + 4;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
    puVar1 = this->pad_2d4 + local_18 * 4 + 0x2c;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
    puVar1 = this->pad_364 + local_18 * 4 - 0x44;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
  }
  this->field_2f4 = 0;
  this->field_2f8 = 0;
  this->field_2fc = 0;
  this->field_2f0 = 0;
  this->field_2e8 = 0;
  this->field_2ec = 0;
  this->side_text_edit = 0;
  this->caption_height = 0xffffffff;
  this->item_buffer = 0;
  this->left_exchange_kind = 0;
  this->right_exchange_kind = 1;
  this->field_214 = 0;
  this->field_208 = 0xffffffff;
  this->field_220 = 0;
  this->field_228 = 0;
  this->field_224 = this->field_228;
  this->field_230 = 0;
  this->field_22c = this->field_230;
  this->field_21c = 0;
  this->treaty_type_choice = 0;
  this->timer_last_value = 0;
  this->show_turn_status = this->timer_last_value;
  this->field_254 = 0;
  this->field_270 = 0;
  this->field_28c = 0;
  this->chat_input_edit = 0;
  this->chat_history_edit = 0;
  chat_input_buffer = 0;
  chat_log_buffer = 0;
  chat_log_capacity = 0;
  for (local_18 = 0; local_18 < 2; local_18++) {
    puVar1 = this->pad_364 + local_18 * 4;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
    puVar1 = this->pad_364 + local_18 * 4 + 8;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
    puVar1 = this->pad_364 + local_18 * 4 + 0x10;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
    puVar1 = this->pad_364 + local_18 * 4 + 0x18;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
    puVar1 = this->pad_364 + local_18 * 4 + 0x20;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
    puVar1 = this->pad_364 + local_18 * 4 + 0x28;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
    puVar1 = this->pad_364 + local_18 * 4 + 0x30;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
    puVar1 = this->pad_3c0 + local_18 * 4 - 0x24;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
    puVar1 = this->pad_3c0 + local_18 * 4 - 0x1c;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
  }
  this->field_3bc = '\0';
  this->field_3bd = '\0';
  this->field_3be = '\0';
  this->remote_side_agreed = '\0';
  return this;
}
#undef chat_input_buffer
#undef chat_log_buffer
#undef chat_log_capacity
#undef local_18
#undef local_10
#undef puStack_c
#undef local_8

/* 004b4593 auto */
#define chat_input_buffer (*(void * *)((u8 *)&g.d_0062d86c))
#define chat_log_buffer (*(char * *)((u8 *)&g.d_0062d870))
#define prefs_clear_chat_on_boot (*(short *)((u8 *)&g.d_006665fc))
#define local_a8 (*(FileObject *)(frame_ + FRAME_OFF(0)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(152)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(156)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(160)))
void __thiscall parley_wnd_dtor(ViewWindow *this)

{
  int iVar1;
  size_t sVar2;
  i8 frame_[FRAME_OFF(168)] __attribute__((aligned(8)));  /* original stack frame */
  
  this->vtable = (u32)&PTR_FUN_0061d6c4;
  local_8 = 0;
  if (this->session_mode == 4) {
    file_obj_init(&local_a8);
    local_8 = CONCAT31((*(i32 *)((char *)&local_8 + 1)),1);
    if ((prefs_clear_chat_on_boot != 0) && (chat_log_buffer != (char *)0x0)) {
      *chat_log_buffer = '\0';
      iVar1 = file_obj_create(&local_a8,ADDR(0x62d874, ((u8 *)&g.d_0062d874)));
      if (iVar1 != 0) {
        sVar2 = _strlen(chat_log_buffer);
        file_obj_write(&local_a8,(iptr)chat_log_buffer,sVar2);
        file_map_close(&local_a8);
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
    local_8 = local_8 & 0xffffff00;
    /* inlined unwind funclet 004b4705 */ { file_obj_close((FileObject *)((iptr)&local_a8)); }
  }
  parley_wnd_destroy_controls(this);
  wnd_destroy_with_surface((DibSurface *)this);
  local_8 = 0xffffffff;
  /* inlined unwind funclet 004b4711 */ { surfwnd_dtor(*(SurfaceWindow **)((iptr)&this)); }
  return;
}
#undef chat_input_buffer
#undef chat_log_buffer
#undef prefs_clear_chat_on_boot
#undef local_a8
#undef uStack_10
#undef puStack_c
#undef local_8

/* 004b4735 auto */
#define chat_input_buffer (*(void * *)((u8 *)&g.d_0062d86c))
#define chat_log_buffer (*(i8 * *)((u8 *)&g.d_0062d870))
#define chat_log_capacity (*(UINT *)((u8 *)&g.d_0069b03c))
#define prefs_clear_chat_on_new_game (*(short *)((u8 *)&g.d_006665fa))
#define local_b0 (*(u8 * *)(frame_ + FRAME_OFF(0)))
#define local_a8 (*(i8 (*)[160])(frame_ + FRAME_OFF(8)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(168)))
void __thiscall parley_wnd_create(ViewWindow *this,u32 param_1)

{
  int iVar1;
  i32 uVar2;
  i32 uVar3;
  i8 *puVar4;
  i8 *puVar5;
  i8 frame_[FRAME_OFF(176)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  (*(i32 *)((char *)&local_a8 + 156)) = &LAB_004b4bef;
  this->style_flags = 1;
  if (this == (ViewWindow *)0x0) {
    local_b0 = (u8 *)0x0;
  }
  else {
    local_b0 = this->pad_48;
  }
  wnd_set_active_child((iptr)local_b0);
  this->session_mode = param_1;
  if (this->session_mode != 4) goto LAB_004b4982;
  chat_log_capacity = GetPrivateProfileIntA
                           (s_Civilization_Gold_0062d898,s_ChatShowSize_0062d888,-1,
                            s_CIV_INI_0062d880);
  if ((chat_log_capacity == 0xffffffff) || ((int)chat_log_capacity < 0x2000)) {
    WritePrivateProfileStringA
              (s_Civilization_Gold_0062d8cc,s_ChatShowSize_0062d8bc,&chat_show_size_default_str,s_CIV_INI_0062d8ac
              );
    chat_log_capacity = 0x2000;
  }
  else if (0xdfff < (int)chat_log_capacity) {
    WritePrivateProfileStringA
              (s_Civilization_Gold_0062d900,s_ChatShowSize_0062d8f0,s_57344_0062d8e8,
               s_CIV_INI_0062d8e0);
    chat_log_capacity = 0xe000;
  }
  if (chat_log_buffer == (i8 *)0x0) {
    chat_log_buffer = operator_new(chat_log_capacity + 1);
  }
  _memset(chat_log_buffer,0,chat_log_capacity + 1);
  if (chat_input_buffer == (void *)0x0) {
    chat_input_buffer = operator_new(0x101);
  }
  _memset(chat_input_buffer,0,0x101);
  file_obj_init((FileObject *)local_a8);
  local_8 = 0;
  if (prefs_clear_chat_on_new_game == 0) {
    iVar1 = file_obj_open((FileObject *)local_a8,ADDR(0x62d914, ((u8 *)&g.d_0062d914)));
    if (iVar1 == 0) goto LAB_004b496e;
    iVar1 = file_obj_get_size((FileObject *)local_a8);
    if ((int)chat_log_capacity < iVar1) {
      file_obj_seek_cur((FileSeekView *)local_a8,iVar1 - chat_log_capacity);
    }
    file_obj_read((FileObject *)local_a8,(iptr)chat_log_buffer,chat_log_capacity);
    file_map_close((FileObject *)local_a8);
  }
  else {
LAB_004b496e:
    *chat_log_buffer = 0;
  }
  local_8 = 0xffffffff;
  /* inlined unwind funclet 004b4be3 */ { file_obj_close((FileObject *)((iptr)&local_a8)); }
LAB_004b4982:
  if ((this->border_width == 0) && (this->resize_border == 0)) {
    parley_wnd_pick_size_mode((ParleyWindowLayout *)this);
  }
  crt_strcpy(this->pad_15c,&parley_wnd_empty_title_str);
  if (this->session_mode == 4) {
    puVar5 = &main_frame_wnd;
    puVar4 = &game_palette;
    uVar2 = rect_height(this->init_rect);
    uVar3 = rect_width(this->init_rect);
    wnd_create_with_surface
              ((DibSurface *)this,0,0x602,*(i32 *)this->init_rect,
               *(i32 *)(this->init_rect + 4),uVar3,uVar2,(iptr)puVar4,(iptr)puVar5);
  }
  else {
    puVar5 = &main_frame_wnd;
    puVar4 = &game_palette;
    uVar2 = rect_height(this->init_rect);
    uVar3 = rect_width(this->init_rect);
    wnd_create_with_surface
              ((DibSurface *)this,0,0x602,*(i32 *)this->init_rect,
               *(i32 *)(this->init_rect + 4),uVar3,uVar2,(iptr)puVar4,(iptr)puVar5);
  }
  parley_wnd_calc_rect((ParleyWindowLayout *)this);
  wnd_move_to_rect((WndBase *)this->pad_48,this->init_rect);
  this->field_158 = 0xffffffff;
  this->left_civ = parley_mode3_left_kind;
  this->right_civ = parley_mode3_right_kind;
  this->shown_left_civ = 0x15;
  this->caption_button_count = 0x15;
  wnd_set_close_handler((WndEventHandlers *)(this->pad_48 + 0x10),ADDR(0x4028d8, diplo_wnd_close_active));
  wnd_set_redraw_callback((SurfaceWindow *)this,ADDR(0x402680, parley_wnd_redraw));
  wnd_set_move_handler((WndEventHandlers *)(this->pad_48 + 0x10),ADDR(0x403d32, parley_wnd_on_move));
  wnd_set_keydown_handler((WndEventHandlers *)(this->pad_48 + 0x10),ADDR(0x401203, parley_wnd_on_key));
  parley_wnd_calc_layout((ParleyWindowLayout *)this);
  parley_wnd_sync_sides(this);
  if (((this->session_mode == 3) || (this->session_mode == 2)) || (this->session_mode == 1)) {
    ctrl_disable((Control *)this->field_350);
  }
  parley_update_buttons(this);
  return;
}
#undef chat_input_buffer
#undef chat_log_buffer
#undef chat_log_capacity
#undef prefs_clear_chat_on_new_game
#undef local_b0
#undef local_a8
#undef local_8

/* 004b4c09 auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl parley_wnd_on_move(void)

{
  iptr iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar1 - 0x48;
  }
  wnd_get_rect_in_parent((WndBase *)(local_8 + 0x48),*(iptr *)(local_8 + 0x150));
  *(i32 *)(local_8 + 0x11c) = **(i32 **)(local_8 + 0x150);
  *(i32 *)(local_8 + 0x120) = *(i32 *)(*(int *)(local_8 + 0x150) + 4);
  return;
}
#undef local_8

/* 004b4c81 auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __thiscall parley_wnd_pick_size_mode(ParleyWindowLayout *this)

{
  iptr iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar1 - 0x48;
  }
  *(i32 *)(local_8 + 0x154) = 0;
  if (999 < screen_width) {
    *(i32 *)(local_8 + 0x154) = 1;
  }
  parley_wnd_calc_rect(this);
  return;
}
#undef local_8

/* 004b4cf0 auto */
#define panel_margin_x (*(int *)((u8 *)&g.d_0062d858))
#define local_18 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_c (*(u32 *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(u32 *)(frame_ + FRAME_OFF(16)))
void __thiscall parley_wnd_calc_rect(ParleyWindowLayout *this)

{
  int iVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (this->large_layout == 0) {
    local_10 = 0x208;
  }
  else {
    local_10 = 800;
  }
  if (this->large_layout == 0) {
    local_14 = 0x14f;
  }
  else {
    local_14 = 0x1cc;
  }
  if (this->large_layout == 0) {
    local_18 = font_cached_height((GameFont *)&font_size20);
  }
  else {
    local_18 = font_cached_height((GameFont *)&font_size30);
  }
  this->client_width = panel_margin_y * 2 + panel_bevel_width * 2 + local_18;
  local_10 = local_10 + (panel_padding_x + panel_margin_x) * 2 + 6;
  local_14 = local_14 + panel_margin_y * 2 + this->client_width * 2 + 0xe;
  iVar1 = rect_width(this->init_rect);
  if (iVar1 == 0) {
    iVar1 = wnd_client_width((WndBase *)&main_frame_wnd);
    this->border_width = (iVar1 >> 1) - (local_10 >> 1);
    local_8 = this->border_width;
    iVar1 = wnd_client_height((WndBase *)&main_frame_wnd);
    this->resize_border = (iVar1 >> 1) - (local_14 >> 1);
    local_c = this->resize_border;
  }
  else {
    local_8 = this->border_width;
    local_c = this->resize_border;
  }
  SetRect((LPRECT)this->init_rect,local_8,local_c,local_10 + local_8,local_14 + local_c);
  wnd_set_caption_height((WndBase *)this->pad_48,this->client_width);
  return;
}
#undef panel_margin_x
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 004b4e8a auto */
#define panel_margin_x (*(int *)((u8 *)&g.d_0062d858))
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall parley_wnd_calc_layout(ParleyWindowLayout *this)

{
  u32 uVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  uVar1 = surface_get_width((DibSurface *)this);
  this->client_x = uVar1;
  uVar1 = surface_get_height((DibSurface *)this);
  this->client_y = uVar1;
  if (this->large_layout == 0) {
    local_8 = font_cached_height((GameFont *)&font_size20);
  }
  else {
    local_8 = font_cached_height((GameFont *)&font_size30);
  }
  this->client_width = panel_margin_y * 2 + panel_bevel_width * 2 + local_8;
  SetRect((LPRECT)&this->client_height,0,0,this->client_x,this->client_y);
  SetRect((LPRECT)&this->panel_rect,0,0,this->client_x + (panel_padding_x + panel_margin_x) * -2,
          this->client_y - (panel_margin_y * 2 + this->client_width * 2 + panel_padding_x));
  OffsetRect((LPRECT)&this->panel_rect,panel_padding_x + panel_margin_x,this->client_width + panel_margin_y);
  return;
}
#undef panel_margin_x
#undef local_8

/* 004b4fb2 auto */
void __thiscall parley_wnd_sync_sides(ViewWindow *this)

{
  if (this->field_158 == this->large_layout) {
    if (this->shown_left_civ != this->left_civ) {
      parley_add_side_dialog(this,this->left_civ,0);
      this->shown_left_civ = this->left_civ;
    }
    if (this->caption_button_count != this->right_civ) {
      parley_add_side_dialog(this,this->right_civ,1);
      this->caption_button_count = this->right_civ;
    }
  }
  else {
    parley_wnd_destroy_controls(this);
    parley_wnd_create_controls(this);
    parley_add_side_dialog(this,this->left_civ,0);
    parley_add_side_dialog(this,this->right_civ,1);
    this->shown_left_civ = this->left_civ;
    this->caption_button_count = this->right_civ;
    this->field_158 = this->large_layout;
  }
  return;
}

/* 004b50cf auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall parley_wnd_destroy_controls(ViewWindow *this)

{
  u8 *puVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (this->item_buffer != 0) {
    operator_delete((void *)this->item_buffer);
    this->item_buffer = 0;
  }
  for (local_8 = 0; local_8 < 3; local_8++) {
    if (*(int *)(this->pad_258 + local_8 * 0x1c - 4) != 0) {
      if (*(Hotspot **)(this->pad_258 + local_8 * 0x1c - 4) != (Hotspot *)0x0) {
        hotspot_scalar_dtor(*(Hotspot **)(this->pad_258 + local_8 * 0x1c - 4),1);
      }
      puVar1 = this->pad_258 + local_8 * 0x1c - 4;
      puVar1[0] = '\0';
      puVar1[1] = '\0';
      puVar1[2] = '\0';
      puVar1[3] = '\0';
    }
  }
  if (this->close_button != 0) {
    if ((Control *)this->close_button != (Control *)0x0) {
      ctrl_scalar_dtor((Control *)this->close_button,1);
    }
    this->close_button = 0;
  }
  if (this->field_2a0 != 0) {
    if ((Control *)this->field_2a0 != (Control *)0x0) {
      ctrl_scalar_dtor((Control *)this->field_2a0,1);
    }
    this->field_2a0 = 0;
  }
  if (this->field_2a4 != 0) {
    if ((Control *)this->field_2a4 != (Control *)0x0) {
      ctrl_scalar_dtor((Control *)this->field_2a4,1);
    }
    this->field_2a4 = 0;
  }
  if (this->field_344 != 0) {
    if ((Control *)this->field_344 != (Control *)0x0) {
      ctrl_scalar_dtor((Control *)this->field_344,1);
    }
    this->field_344 = 0;
  }
  if (this->field_340 != 0) {
    if ((Control *)this->field_340 != (Control *)0x0) {
      ctrl_scalar_dtor((Control *)this->field_340,1);
    }
    this->field_340 = 0;
  }
  if (this->field_348 != 0) {
    if ((Control *)this->field_348 != (Control *)0x0) {
      ctrl_scalar_dtor((Control *)this->field_348,1);
    }
    this->field_348 = 0;
  }
  if (this->field_354 != 0) {
    if ((Control *)this->field_354 != (Control *)0x0) {
      ctrl_scalar_dtor((Control *)this->field_354,1);
    }
    this->field_354 = 0;
  }
  if (this->field_34c != 0) {
    if ((Control *)this->field_34c != (Control *)0x0) {
      ctrl_scalar_dtor((Control *)this->field_34c,1);
    }
    this->field_34c = 0;
  }
  if (this->field_350 != 0) {
    if ((Control *)this->field_350 != (Control *)0x0) {
      ctrl_scalar_dtor((Control *)this->field_350,1);
    }
    this->field_350 = 0;
  }
  if (this->field_358 != 0) {
    if ((Control *)this->field_358 != (Control *)0x0) {
      ctrl_scalar_dtor((Control *)this->field_358,1);
    }
    this->field_358 = 0;
  }
  if (this->field_35c != 0) {
    if ((Control *)this->field_35c != (Control *)0x0) {
      ctrl_scalar_dtor((Control *)this->field_35c,1);
    }
    this->field_35c = 0;
  }
  if (this->field_360 != 0) {
    if ((Control *)this->field_360 != (Control *)0x0) {
      ctrl_scalar_dtor((Control *)this->field_360,1);
    }
    this->field_360 = 0;
  }
  if (this->chat_history_edit != 0) {
    if ((Control *)this->chat_history_edit != (Control *)0x0) {
      edit_scalar_dtor((Control *)this->chat_history_edit,1);
    }
    this->chat_history_edit = 0;
  }
  if (this->chat_input_edit != 0) {
    if ((Control *)this->chat_input_edit != (Control *)0x0) {
      edit_scalar_dtor((Control *)this->chat_input_edit,1);
    }
    this->chat_input_edit = 0;
  }
  if (this->field_2e8 != 0) {
    if ((Checkbox *)this->field_2e8 != (Checkbox *)0x0) {
      checkbox_scalar_dtor((Checkbox *)this->field_2e8,1);
    }
    this->field_2e8 = 0;
  }
  if (this->field_2ec != 0) {
    if ((Checkbox *)this->field_2ec != (Checkbox *)0x0) {
      checkbox_scalar_dtor((Checkbox *)this->field_2ec,1);
    }
    this->field_2ec = 0;
  }
  if (this->side_text_edit != 0) {
    if ((Control *)this->side_text_edit != (Control *)0x0) {
      edit_scalar_dtor((Control *)this->side_text_edit,1);
    }
    this->side_text_edit = 0;
  }
  if (this->field_2f0 != 0) {
    if ((Checkbox *)this->field_2f0 != (Checkbox *)0x0) {
      checkbox_scalar_dtor((Checkbox *)this->field_2f0,1);
    }
    this->field_2f0 = 0;
  }
  for (local_8 = 0; local_8 < 8; local_8++) {
    if (*(int *)(this->pad_2c4 + local_8 * 4 - 0x1c) != 0) {
      if (*(Checkbox **)(this->pad_2c4 + local_8 * 4 - 0x1c) != (Checkbox *)0x0) {
        checkbox_scalar_dtor(*(Checkbox **)(this->pad_2c4 + local_8 * 4 - 0x1c),1);
      }
      puVar1 = this->pad_2c4 + local_8 * 4 - 0x1c;
      puVar1[0] = '\0';
      puVar1[1] = '\0';
      puVar1[2] = '\0';
      puVar1[3] = '\0';
    }
    if (*(int *)(this->pad_2c4 + local_8 * 4 + 4) != 0) {
      if (*(Checkbox **)(this->pad_2c4 + local_8 * 4 + 4) != (Checkbox *)0x0) {
        checkbox_scalar_dtor(*(Checkbox **)(this->pad_2c4 + local_8 * 4 + 4),1);
      }
      puVar1 = this->pad_2c4 + local_8 * 4 + 4;
      puVar1[0] = '\0';
      puVar1[1] = '\0';
      puVar1[2] = '\0';
      puVar1[3] = '\0';
    }
  }
  for (local_8 = 0; local_8 < 2; local_8++) {
    if (*(int *)(this->pad_364 + local_8 * 4) != 0) {
      if (*(Checkbox **)(this->pad_364 + local_8 * 4) != (Checkbox *)0x0) {
        checkbox_scalar_dtor(*(Checkbox **)(this->pad_364 + local_8 * 4),1);
      }
      puVar1 = this->pad_364 + local_8 * 4;
      puVar1[0] = '\0';
      puVar1[1] = '\0';
      puVar1[2] = '\0';
      puVar1[3] = '\0';
    }
    if (*(int *)(this->pad_364 + local_8 * 4 + 8) != 0) {
      if (*(RadioGroupDtorView **)(this->pad_364 + local_8 * 4 + 8) != (RadioGroupDtorView *)0x0) {
        radiogrp_scalar_dtor(*(RadioGroupDtorView **)(this->pad_364 + local_8 * 4 + 8),1);
      }
      puVar1 = this->pad_364 + local_8 * 4 + 8;
      puVar1[0] = '\0';
      puVar1[1] = '\0';
      puVar1[2] = '\0';
      puVar1[3] = '\0';
    }
    if (*(int *)(this->pad_364 + local_8 * 4 + 0x10) != 0) {
      if (*(Control **)(this->pad_364 + local_8 * 4 + 0x10) != (Control *)0x0) {
        edit_scalar_dtor(*(Control **)(this->pad_364 + local_8 * 4 + 0x10),1)
        ;
      }
      puVar1 = this->pad_364 + local_8 * 4 + 0x10;
      puVar1[0] = '\0';
      puVar1[1] = '\0';
      puVar1[2] = '\0';
      puVar1[3] = '\0';
    }
    if (*(int *)(this->pad_364 + local_8 * 4 + 0x18) != 0) {
      if (*(Control **)(this->pad_364 + local_8 * 4 + 0x18) != (Control *)0x0) {
        scrollbar_scalar_dtor(*(Control **)(this->pad_364 + local_8 * 4 + 0x18),1)
        ;
      }
      puVar1 = this->pad_364 + local_8 * 4 + 0x18;
      puVar1[0] = '\0';
      puVar1[1] = '\0';
      puVar1[2] = '\0';
      puVar1[3] = '\0';
    }
    if (*(int *)(this->pad_364 + local_8 * 4 + 0x20) != 0) {
      if (*(Hotspot **)(this->pad_364 + local_8 * 4 + 0x20) != (Hotspot *)0x0) {
        hotspot_scalar_dtor(*(Hotspot **)(this->pad_364 + local_8 * 4 + 0x20),1);
      }
      puVar1 = this->pad_364 + local_8 * 4 + 0x20;
      puVar1[0] = '\0';
      puVar1[1] = '\0';
      puVar1[2] = '\0';
      puVar1[3] = '\0';
    }
    if (*(int *)(this->pad_364 + local_8 * 4 + 0x28) != 0) {
      if (*(Control **)(this->pad_364 + local_8 * 4 + 0x28) != (Control *)0x0) {
        ctrl_scalar_dtor(*(Control **)(this->pad_364 + local_8 * 4 + 0x28),1)
        ;
      }
      puVar1 = this->pad_364 + local_8 * 4 + 0x28;
      puVar1[0] = '\0';
      puVar1[1] = '\0';
      puVar1[2] = '\0';
      puVar1[3] = '\0';
    }
    if (*(int *)(this->pad_364 + local_8 * 4 + 0x30) != 0) {
      if (*(Control **)(this->pad_364 + local_8 * 4 + 0x30) != (Control *)0x0) {
        ctrl_scalar_dtor(*(Control **)(this->pad_364 + local_8 * 4 + 0x30),1)
        ;
      }
      puVar1 = this->pad_364 + local_8 * 4 + 0x30;
      puVar1[0] = '\0';
      puVar1[1] = '\0';
      puVar1[2] = '\0';
      puVar1[3] = '\0';
    }
    if (*(int *)(this->pad_3c0 + local_8 * 4 - 0x24) != 0) {
      if (*(Control **)(this->pad_3c0 + local_8 * 4 - 0x24) != (Control *)0x0) {
        ctrl_scalar_dtor
                  (*(Control **)(this->pad_3c0 + local_8 * 4 - 0x24),1);
      }
      puVar1 = this->pad_3c0 + local_8 * 4 - 0x24;
      puVar1[0] = '\0';
      puVar1[1] = '\0';
      puVar1[2] = '\0';
      puVar1[3] = '\0';
    }
    if (*(int *)(this->pad_3c0 + local_8 * 4 - 0x1c) != 0) {
      if (*(Control **)(this->pad_3c0 + local_8 * 4 - 0x1c) != (Control *)0x0) {
        ctrl_scalar_dtor
                  (*(Control **)(this->pad_3c0 + local_8 * 4 - 0x1c),1);
      }
      puVar1 = this->pad_3c0 + local_8 * 4 - 0x1c;
      puVar1[0] = '\0';
      puVar1[1] = '\0';
      puVar1[2] = '\0';
      puVar1[3] = '\0';
    }
  }
  return;
}
#undef local_8

/* 004b5c93 auto */
#define chat_input_buffer (*(iptr *)((u8 *)&g.d_0062d86c))
#define chat_log_buffer (*(iptr *)((u8 *)&g.d_0062d870))
#define panel_margin_x (*(int *)((u8 *)&g.d_0062d858))
#define local_134 (*(u8 * *)(frame_ + FRAME_OFF(4)))
#define local_130 (*(u8 * *)(frame_ + FRAME_OFF(8)))
#define local_12c (*(u8 * *)(frame_ + FRAME_OFF(12)))
#define local_128 (*(u8 * *)(frame_ + FRAME_OFF(16)))
#define local_124 (*(u8 * *)(frame_ + FRAME_OFF(20)))
#define local_120 (*(u8 * *)(frame_ + FRAME_OFF(24)))
#define local_11c (*(u8 * *)(frame_ + FRAME_OFF(28)))
#define local_118 (*(u8 * *)(frame_ + FRAME_OFF(32)))
#define local_114 (*(u8 * *)(frame_ + FRAME_OFF(36)))
#define local_110 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_10c (*(u8 * *)(frame_ + FRAME_OFF(44)))
#define local_108 (*(u8 * *)(frame_ + FRAME_OFF(48)))
#define local_104 (*(u8 * *)(frame_ + FRAME_OFF(52)))
#define local_fc (*(int *)(frame_ + FRAME_OFF(60)))
#define local_f8 (*(int *)(frame_ + FRAME_OFF(64)))
#define local_f4 (*(int *)(frame_ + FRAME_OFF(68)))
#define local_f0 (*(int *)(frame_ + FRAME_OFF(72)))
#define local_ec (*(u8 * *)(frame_ + FRAME_OFF(76)))
#define local_e4 (*(int *)(frame_ + FRAME_OFF(84)))
#define local_e0 (*(int *)(frame_ + FRAME_OFF(88)))
#define local_dc (*(int *)(frame_ + FRAME_OFF(92)))
#define local_d8 (*(int *)(frame_ + FRAME_OFF(96)))
#define local_d4 (*(u8 * *)(frame_ + FRAME_OFF(100)))
#define local_d0 (*(iptr *)(frame_ + FRAME_OFF(104)))
#define local_cc (*(int *)(frame_ + FRAME_OFF(108)))
#define local_c8 (*(int *)(frame_ + FRAME_OFF(112)))
#define local_c0 (*(u8 * *)(frame_ + FRAME_OFF(120)))
#define local_bc (*(uptr *)(frame_ + FRAME_OFF(124)))
#define local_b4 (*(uptr *)(frame_ + FRAME_OFF(132)))
#define local_ac (*(uptr *)(frame_ + FRAME_OFF(140)))
#define local_a4 (*(uptr *)(frame_ + FRAME_OFF(148)))
#define local_9c (*(uptr *)(frame_ + FRAME_OFF(156)))
#define local_94 (*(uptr *)(frame_ + FRAME_OFF(164)))
#define local_8c (*(uptr *)(frame_ + FRAME_OFF(172)))
#define local_84 (*(uptr *)(frame_ + FRAME_OFF(180)))
#define local_7c (*(uptr *)(frame_ + FRAME_OFF(188)))
#define local_74 (*(uptr *)(frame_ + FRAME_OFF(196)))
#define local_6c (*(uptr *)(frame_ + FRAME_OFF(204)))
#define local_64 (*(i8 * *)(frame_ + FRAME_OFF(212)))
#define local_60 (*(uptr *)(frame_ + FRAME_OFF(216)))
#define local_58 (*(i8 * *)(frame_ + FRAME_OFF(224)))
#define local_54 (*(uptr *)(frame_ + FRAME_OFF(228)))
#define local_4c (*(uptr *)(frame_ + FRAME_OFF(236)))
#define local_44 (*(i8 * *)(frame_ + FRAME_OFF(244)))
#define local_40 (*(i32 *)(frame_ + FRAME_OFF(248)))
#define local_38 (*(int *)(frame_ + FRAME_OFF(256)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(260)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(268)))
#define local_28 (*(tagRECT *)(frame_ + FRAME_OFF(272)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(288)))
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(292)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(296)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(300)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(304)))
void __thiscall parley_wnd_create_controls(ViewWindow *this)

{
  u8 *puVar1;
  u32 uVar2;
  int iVar3;
  LONG xLeft;
  i32 uVar4;
  int iVar5;
  int iVar6;
  Control *pCVar7;
  int yTop;
  InputControl *pCVar8;
  iptr iVar9;
  i8 frame_[FRAME_OFF(312)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  local_34 = panel_padding_x;
  for (local_2c = 0; local_2c < 3; local_2c++) {
    if (local_2c == 0) {
      *(i8 **)(this->pad_23c + 0x14) = &caption_close_button_sprite;
    }
    else if (local_2c == 1) {
      *(i8 **)(this->pad_258 + 0x14) = &caption_zoom_out_sprite;
    }
    else {
      *(i8 **)(this->pad_23c + local_2c * 0x1c + 0x14) = &caption_zoom_out_button_sprite;
    }
    *(int *)(this->pad_23c + local_2c * 0x1c) = local_2c + 1;
    uVar4 = sprite_width
                      (*(Sprite **)(this->pad_23c + local_2c * 0x1c + 0x14));
    *(i32 *)(this->pad_23c + local_2c * 0x1c + 0xc) = uVar4;
    uVar4 = sprite_height
                      (*(Sprite **)(this->pad_23c + local_2c * 0x1c + 0x14));
    *(i32 *)(this->pad_23c + local_2c * 0x1c + 0x10) = uVar4;
    puVar1 = this->pad_258 + local_2c * 0x1c - 4;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
    iVar5 = (int)(*(int *)(this->pad_23c + local_2c * 0x1c + 0xc) * this->client_width) / 0x18;
    local_18 = (int)(*(int *)(this->pad_23c + local_2c * 0x1c + 0x10) * this->client_width) / 0x18;
    iVar6 = ((int)this->client_width >> 1) - (local_18 >> 1);
    SetRect(&local_28,local_34,iVar6,iVar5 + local_34,iVar6 + local_18);
    pCVar7 = operator_new(0x40);
    local_8 = 0;
    if (pCVar7 == (Control *)0x0) {
      local_40 = 0;
    }
    else {
      local_40 = hotspot_ctor(pCVar7);
    }
    local_8 = 0xffffffff;
    *(i32 *)(this->pad_258 + local_2c * 0x1c - 4) = local_40;
    if (this == (ViewWindow *)0x0) {
      local_c0 = (u8 *)0x0;
    }
    else {
      local_c0 = this->pad_48;
    }
    hotspot_create
              (*(ClickControl **)(this->pad_258 + local_2c * 0x1c - 4),(iptr)local_c0,
               *(int *)(this->pad_23c + local_2c * 0x1c) + 1000,(iptr)&local_28);
    hotspot_set_click_callback(*(HotspotClickSetView **)(this->pad_258 + local_2c * 0x1c - 4),ADDR(0x4012da, parley_wnd_on_caption_click));
    local_34 = local_34 + iVar5 + panel_margin_x;
  }
  if (this->large_layout == 0) {
    local_44 = &font_size16;
  }
  else {
    local_44 = &font_size24;
  }
  ui_set_button_font((iptr)local_44);
  pCVar7 = operator_new(0x3c);
  local_8 = 1;
  if (pCVar7 == (Control *)0x0) {
    local_4c = 0;
  }
  else {
    local_4c = button_ctor(pCVar7);
  }
  local_8 = 0xffffffff;
  this->close_button = local_4c;
  iVar5 = panel_bevel_width + panel_margin_x + 2;
  if (this->large_layout == 0) {
    local_c8 = font_line_spacing((GameFont *)&font_size16);
  }
  else {
    local_c8 = font_line_spacing((GameFont *)&font_size24);
  }
  yTop = this->client_y - ((panel_margin_y + panel_padding_y) * 2 + local_c8);
  uVar2 = this->client_x;
  iVar3 = panel_margin_x * 2;
  iVar6 = panel_bevel_width * 2;
  if (this->large_layout == 0) {
    local_cc = font_line_spacing((GameFont *)&font_size16);
  }
  else {
    local_cc = font_line_spacing((GameFont *)&font_size24);
  }
  local_18 = panel_padding_y * 2 + local_cc;
  SetRect(&local_28,iVar5,yTop,(uVar2 - (iVar3 + iVar6 + 5)) + iVar5,yTop + local_18);
  if (this->session_mode == 4) {
    local_d0 = label_string(*(i32 *)(label_string_ids + 0xb2c));
  }
  else {
    local_d0 = label_string(*(i32 *)(label_string_ids + 0xb30));
  }
  if (this == (ViewWindow *)0x0) {
    local_d4 = (u8 *)0x0;
  }
  else {
    local_d4 = this->pad_48;
  }
  button_create
            ((Control *)this->close_button,(iptr)local_d4,0x3ed,(iptr)&local_28,local_d0);
  button_set_callback((Control *)this->close_button,ADDR(0x4028f6, diplo_wnd_escape_close));
  pCVar8 = operator_new(0x48);
  local_8 = 2;
  if (pCVar8 == (InputControl *)0x0) {
    local_54 = 0;
  }
  else {
    local_54 = edit_ctor(pCVar8);
  }
  local_8 = 0xffffffff;
  this->chat_history_edit = local_54;
  iVar6 = this->panel_rect + panel_margin_x;
  iVar5 = rect_width((iptr)&this->panel_rect);
  iVar5 += panel_margin_x * -2;
  if (this->session_mode == 4) {
    if (this->large_layout == 0) {
      local_e0 = font_cached_height((GameFont *)&font_size14);
    }
    else {
      local_e0 = font_cached_height((GameFont *)&font_size21);
    }
    local_38 = this->panel_bottom + (panel_margin_y + local_e0) * -9;
    if (this->large_layout == 0) {
      local_e4 = font_cached_height((GameFont *)&font_size14);
    }
    else {
      local_e4 = font_cached_height((GameFont *)&font_size21);
    }
    local_18 = local_e4 * 9 + panel_margin_y * 8;
  }
  else {
    if (this->large_layout == 0) {
      local_d8 = font_cached_height((GameFont *)&font_size14);
    }
    else {
      local_d8 = font_cached_height((GameFont *)&font_size21);
    }
    local_38 = this->panel_bottom + (panel_margin_y + local_d8) * -6;
    if (this->large_layout == 0) {
      local_dc = font_cached_height((GameFont *)&font_size14);
    }
    else {
      local_dc = font_cached_height((GameFont *)&font_size21);
    }
    local_18 = panel_margin_y * 5 + local_dc * 6;
  }
  SetRect(&local_28,iVar6,local_38,iVar5 + iVar6,local_38 + local_18);
  if (this->large_layout == 0) {
    local_58 = &font_size14;
  }
  else {
    local_58 = &font_size21;
  }
  ui_set_default_font((iptr)local_58);
  if (this == (ViewWindow *)0x0) {
    local_ec = (u8 *)0x0;
  }
  else {
    local_ec = this->pad_48;
  }
  edit_create_styled
            ((EditControl *)this->chat_history_edit,(iptr)local_ec,0x3ee,(iptr)&local_28,chat_log_buffer,
             0x122,0);
  edit_set_max_len((EditMaxLenView *)this->chat_history_edit,0x2000);
  edit_set_callback((EditCallbackSetView *)this->chat_history_edit,ADDR(0x402040, parley_edit_escape_filter));
  ctrl_show_and_redraw((Control *)this->chat_history_edit);
  pCVar8 = operator_new(0x48);
  local_8 = 3;
  if (pCVar8 == (InputControl *)0x0) {
    local_60 = 0;
  }
  else {
    local_60 = edit_ctor(pCVar8);
  }
  local_8 = 0xffffffff;
  this->chat_input_edit = local_60;
  iVar5 -= iVar5 / 10;
  if (this->session_mode == 4) {
    if (this->large_layout == 0) {
      local_f8 = font_cached_height((GameFont *)&font_size14);
    }
    else {
      local_f8 = font_cached_height((GameFont *)&font_size21);
    }
    iVar3 = panel_margin_y * -4 + local_f8 * -3;
    if (this->large_layout == 0) {
      local_fc = font_cached_height((GameFont *)&font_size14);
    }
    else {
      local_fc = font_cached_height((GameFont *)&font_size21);
    }
    local_18 = local_fc * 3 + panel_margin_y * 3;
  }
  else {
    if (this->large_layout == 0) {
      local_f0 = font_cached_height((GameFont *)&font_size14);
    }
    else {
      local_f0 = font_cached_height((GameFont *)&font_size21);
    }
    iVar3 = panel_margin_y * -3 + local_f0 * -2;
    if (this->large_layout == 0) {
      local_f4 = font_cached_height((GameFont *)&font_size14);
    }
    else {
      local_f4 = font_cached_height((GameFont *)&font_size21);
    }
    local_18 = panel_margin_y * 2 + local_f4 * 2;
  }
  local_38 += iVar3;
  SetRect(&local_28,iVar6,local_38,iVar5 + iVar6,local_38 + local_18);
  if (this->large_layout == 0) {
    local_64 = &font_size14;
  }
  else {
    local_64 = &font_size21;
  }
  ui_set_default_font((iptr)local_64);
  if (this->session_mode == 4) {
    local_14 = 0x200;
  }
  else {
    local_14 = 0x220;
  }
  if (this == (ViewWindow *)0x0) {
    local_104 = (u8 *)0x0;
  }
  else {
    local_104 = this->pad_48;
  }
  edit_create_styled
            ((EditControl *)this->chat_input_edit,(iptr)local_104,0x3ef,(iptr)&local_28,chat_input_buffer,
             local_14,0);
  edit_set_max_len((EditMaxLenView *)this->chat_input_edit,0x100);
  edit_set_callback((EditCallbackSetView *)this->chat_input_edit,ADDR(0x403562, chat_input_on_key));
  ctrl_set_initial_focus((CtrlSetInitialFocusView *)this->chat_input_edit);
  ctrl_show_and_redraw((Control *)this->chat_input_edit);
  pCVar7 = operator_new(0x3c);
  local_8 = 4;
  if (pCVar7 == (Control *)0x0) {
    local_6c = 0;
  }
  else {
    local_6c = button_ctor(pCVar7);
  }
  xLeft = local_28.right;
  local_8 = 0xffffffff;
  this->field_2a0 = local_6c;
  iVar5 = iVar5 / 9;
  local_18 = local_18 / 2;
  SetRect(&local_28,local_28.right,local_38,iVar5 + local_28.right,local_38 + local_18);
  if (this == (ViewWindow *)0x0) {
    local_108 = (u8 *)0x0;
  }
  else {
    local_108 = this->pad_48;
  }
  iVar9 = label_string(*(i32 *)(label_string_ids + 0xb34));
  button_create
            ((Control *)this->field_2a0,(iptr)local_108,0x3f0,(iptr)&local_28,iVar9);
  button_set_callback((Control *)this->field_2a0,ADDR(0x40308a, chat_send_button_on_click));
  pCVar7 = operator_new(0x3c);
  local_8 = 5;
  if (pCVar7 == (Control *)0x0) {
    local_74 = 0;
  }
  else {
    local_74 = button_ctor(pCVar7);
  }
  local_8 = 0xffffffff;
  this->field_2a4 = local_74;
  local_38 += local_18;
  SetRect(&local_28,xLeft,local_38,iVar5 + xLeft,local_38 + local_18);
  if (this == (ViewWindow *)0x0) {
    local_10c = (u8 *)0x0;
  }
  else {
    local_10c = this->pad_48;
  }
  iVar9 = label_string(*(i32 *)(label_string_ids + 0xb38));
  button_create
            ((Control *)this->field_2a4,(iptr)local_10c,0x41e,(iptr)&local_28,iVar9);
  button_set_callback((Control *)this->field_2a4,ADDR(0x403639, chat_clear_button_on_click));
  local_38 -= local_18;
  if (this->large_layout == 0) {
    local_110 = font_line_spacing((GameFont *)&font_size16);
  }
  else {
    local_110 = font_line_spacing((GameFont *)&font_size24);
  }
  local_18 = panel_padding_y * 2 + local_110;
  local_38 -= (panel_margin_y + local_18);
  this->show_turn_timer = local_38 - panel_margin_y;
  if (this->session_mode != 4) {
    pCVar7 = operator_new(0x3c);
    local_8 = 6;
    if (pCVar7 == (Control *)0x0) {
      local_7c = 0;
    }
    else {
      local_7c = button_ctor(pCVar7);
    }
    local_8 = 0xffffffff;
    this->field_340 = local_7c;
    iVar5 = this->panel_rect + panel_margin_x;
    iVar6 = rect_width((iptr)&this->panel_rect);
    iVar6 += panel_margin_x * -2;
    SetRect(&local_28,iVar5,local_38 - local_18,iVar6 + iVar5,local_38);
    if (this == (ViewWindow *)0x0) {
      local_114 = (u8 *)0x0;
    }
    else {
      local_114 = this->pad_48;
    }
    iVar9 = label_string(*(i32 *)(label_string_ids + 0xdb4));
    button_create
              ((Control *)this->field_340,(iptr)local_114,0x431,(iptr)&local_28,iVar9);
    button_set_callback((Control *)this->field_340,ADDR(0x40349a, parley_on_conceal_info));
    control_hide((Control *)this->field_340);
    ctrl_disable((Control *)this->field_340);
    pCVar7 = operator_new(0x3c);
    local_8 = 7;
    if (pCVar7 == (Control *)0x0) {
      local_84 = 0;
    }
    else {
      local_84 = button_ctor(pCVar7);
    }
    local_8 = 0xffffffff;
    this->field_344 = local_84;
    iVar5 = this->panel_rect + panel_margin_x;
    SetRect(&local_28,iVar5,local_38 - local_18,iVar6 + iVar5,local_38);
    if (this == (ViewWindow *)0x0) {
      local_118 = (u8 *)0x0;
    }
    else {
      local_118 = this->pad_48;
    }
    iVar9 = label_string(*(i32 *)(label_string_ids + 0xdb8));
    button_create
              ((Control *)this->field_344,(iptr)local_118,0x432,(iptr)&local_28,iVar9);
    button_set_callback((Control *)this->field_344,ADDR(0x4016b3, parley_on_reveal_info));
    control_hide((Control *)this->field_344);
    ctrl_disable((Control *)this->field_344);
    pCVar7 = operator_new(0x3c);
    local_8 = 8;
    if (pCVar7 == (Control *)0x0) {
      local_8c = 0;
    }
    else {
      local_8c = button_ctor(pCVar7);
    }
    local_8 = 0xffffffff;
    this->field_354 = local_8c;
    iVar5 = this->panel_rect + panel_margin_x;
    iVar6 = rect_width((iptr)&this->panel_rect);
    iVar6 = (iVar6 + panel_margin_x * -2) / 3;
    SetRect(&local_28,iVar5,local_38,iVar6 + iVar5,local_38 + local_18);
    if (this == (ViewWindow *)0x0) {
      local_11c = (u8 *)0x0;
    }
    else {
      local_11c = this->pad_48;
    }
    iVar9 = label_string(*(i32 *)(label_string_ids + 0x1a0));
    button_create
              ((Control *)this->field_354,(iptr)local_11c,0x428,(iptr)&local_28,iVar9);
    button_set_callback((Control *)this->field_354,ADDR(0x40144c, parley_on_check_intel));
    ctrl_enable((Control *)this->field_354);
    pCVar7 = operator_new(0x3c);
    local_8 = 9;
    if (pCVar7 == (Control *)0x0) {
      local_94 = 0;
    }
    else {
      local_94 = button_ctor(pCVar7);
    }
    local_8 = 0xffffffff;
    this->field_348 = local_94;
    SetRect(&local_28,local_28.right,local_38,iVar6 + local_28.right,local_38 + local_18);
    if (this == (ViewWindow *)0x0) {
      local_120 = (u8 *)0x0;
    }
    else {
      local_120 = this->pad_48;
    }
    iVar9 = label_string(*(i32 *)(label_string_ids + 0xb3c));
    button_create
              ((Control *)this->field_348,(iptr)local_120,0x3f1,(iptr)&local_28,iVar9);
    button_set_callback((Control *)this->field_348,ADDR(0x402a09, parley_on_mode_chosen));
    ctrl_enable((Control *)this->field_348);
    pCVar7 = operator_new(0x3c);
    local_8 = 10;
    if (pCVar7 == (Control *)0x0) {
      local_9c = 0;
    }
    else {
      local_9c = button_ctor(pCVar7);
    }
    local_8 = 0xffffffff;
    this->field_34c = local_9c;
    if (this == (ViewWindow *)0x0) {
      local_124 = (u8 *)0x0;
    }
    else {
      local_124 = this->pad_48;
    }
    iVar9 = label_string(*(i32 *)(label_string_ids + 0xd10));
    button_create
              ((Control *)this->field_34c,(iptr)local_124,0x427,(iptr)&local_28,iVar9);
    button_set_callback((Control *)this->field_34c,ADDR(0x402a09, parley_on_mode_chosen));
    ctrl_disable((Control *)this->field_34c);
    control_hide((Control *)this->field_34c);
    pCVar7 = operator_new(0x3c);
    local_8 = 0xb;
    if (pCVar7 == (Control *)0x0) {
      local_a4 = 0;
    }
    else {
      local_a4 = button_ctor(pCVar7);
    }
    local_8 = 0xffffffff;
    this->field_350 = local_a4;
    SetRect(&local_28,local_28.right,local_38,iVar6 + local_28.right,local_38 + local_18);
    if (this == (ViewWindow *)0x0) {
      local_128 = (u8 *)0x0;
    }
    else {
      local_128 = this->pad_48;
    }
    iVar9 = label_string(*(i32 *)(label_string_ids + 0xb40));
    button_create
              ((Control *)this->field_350,(iptr)local_128,0x3f2,(iptr)&local_28,iVar9);
    button_set_callback((Control *)this->field_350,ADDR(0x40339b, parley_on_never_mind));
    pCVar7 = operator_new(0x3c);
    local_8 = 0xc;
    if (pCVar7 == (Control *)0x0) {
      local_ac = 0;
    }
    else {
      local_ac = button_ctor(pCVar7);
    }
    local_8 = 0xffffffff;
    this->field_358 = local_ac;
    iVar5 = this->panel_rect + panel_margin_x;
    iVar6 = rect_width((iptr)&this->panel_rect);
    iVar6 = (iVar6 + panel_margin_x * -2) / 3;
    SetRect(&local_28,iVar5,local_38,iVar6 + iVar5,local_38 + local_18);
    if (this == (ViewWindow *)0x0) {
      local_12c = (u8 *)0x0;
    }
    else {
      local_12c = this->pad_48;
    }
    iVar9 = label_string(*(i32 *)(label_string_ids + 0xb44));
    button_create
              ((Control *)this->field_358,(iptr)local_12c,0x3f2,(iptr)&local_28,iVar9);
    button_set_callback((Control *)this->field_358,ADDR(0x4030a8, parley_on_accept_offer));
    control_hide((Control *)this->field_358);
    pCVar7 = operator_new(0x3c);
    local_8 = 0xd;
    if (pCVar7 == (Control *)0x0) {
      local_b4 = 0;
    }
    else {
      local_b4 = button_ctor(pCVar7);
    }
    local_8 = 0xffffffff;
    this->field_35c = local_b4;
    SetRect(&local_28,local_28.right,local_38,iVar6 + local_28.right,local_38 + local_18);
    if (this == (ViewWindow *)0x0) {
      local_130 = (u8 *)0x0;
    }
    else {
      local_130 = this->pad_48;
    }
    iVar9 = label_string(*(i32 *)(label_string_ids + 0xb48));
    button_create
              ((Control *)this->field_35c,(iptr)local_130,0x3f2,(iptr)&local_28,iVar9);
    button_set_callback((Control *)this->field_35c,ADDR(0x4019a1, parley_on_no_thanks));
    control_hide((Control *)this->field_35c);
    pCVar7 = operator_new(0x3c);
    local_8 = 0xe;
    if (pCVar7 == (Control *)0x0) {
      local_bc = 0;
    }
    else {
      local_bc = button_ctor(pCVar7);
    }
    local_8 = 0xffffffff;
    this->field_360 = local_bc;
    SetRect(&local_28,local_28.right,local_38,iVar6 + local_28.right,local_38 + local_18);
    if (this == (ViewWindow *)0x0) {
      local_134 = (u8 *)0x0;
    }
    else {
      local_134 = this->pad_48;
    }
    iVar9 = label_string(*(i32 *)(label_string_ids + 0xb4c));
    button_create
              ((Control *)this->field_360,(iptr)local_134,0x3f2,(iptr)&local_28,iVar9);
    button_set_callback((Control *)this->field_360,ADDR(0x40334b, parley_on_counter_offer));
    control_hide((Control *)this->field_360);
  }
  return;
}
#undef chat_input_buffer
#undef chat_log_buffer
#undef panel_margin_x
#undef local_134
#undef local_130
#undef local_12c
#undef local_128
#undef local_124
#undef local_120
#undef local_11c
#undef local_118
#undef local_114
#undef local_110
#undef local_10c
#undef local_108
#undef local_104
#undef local_fc
#undef local_f8
#undef local_f4
#undef local_f0
#undef local_ec
#undef local_e4
#undef local_e0
#undef local_dc
#undef local_d8
#undef local_d4
#undef local_d0
#undef local_cc
#undef local_c8
#undef local_c0
#undef local_bc
#undef local_b4
#undef local_ac
#undef local_a4
#undef local_9c
#undef local_94
#undef local_8c
#undef local_84
#undef local_7c
#undef local_74
#undef local_6c
#undef local_64
#undef local_60
#undef local_58
#undef local_54
#undef local_4c
#undef local_44
#undef local_40
#undef local_38
#undef local_34
#undef local_2c
#undef local_28
#undef local_18
#undef local_14
#undef local_10
#undef puStack_c
#undef local_8

/* 004b74c4 auto */
#define local_8 (*(ParleyWindowLayout * *)(frame_ + FRAME_OFF(0)))
void __cdecl parley_wnd_on_caption_click(int param_1)

{
  iptr iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = (ParleyWindowLayout *)0x0;
  }
  else {
    local_8 = (ParleyWindowLayout *)(iVar1 - 0x48);
  }
  wnd_activate((Wnd *)local_8->pad_48);
  if (param_1 == 0x3e9) {
    diplo_wnd_close_active();
  }
  else if (param_1 == 0x3ea) {
    if (0 < (int)local_8->field_154) {
      wnd_hide((WndBase *)local_8->pad_48);
      local_8->field_154--;
      parley_wnd_calc_rect(local_8);
      wnd_move_to_rect((WndBase *)local_8->pad_48,local_8->field_150);
      window_show((WindowObjectView *)local_8);
    }
  }
  else if (((param_1 == 0x3eb) && ((int)local_8->field_154 < 1)) && (999 < screen_width)) {
    wnd_hide((WndBase *)local_8->pad_48);
    local_8->field_154++;
    parley_wnd_calc_rect(local_8);
    wnd_move_to_rect((WndBase *)local_8->pad_48,local_8->field_150);
    window_show((WindowObjectView *)local_8);
  }
  return;
}
#undef local_8

/* 004b7645 auto */
/* WARNING: Removing unreachable block (ram,0x004b766b) */

void __cdecl parley_wnd_close(void)

{
  wnd_set_active_child(ADDR(0x67a7f0, ((u8 *)&g.d_0067a7f0)));
  diplo_wnd_close_active();
  return;
}

/* 004b768d auto */
/* WARNING: Removing unreachable block (ram,0x004b76b3) */

void __cdecl chat_wnd_close(void)

{
  wnd_set_active_child(ADDR(0x68ac30, ((u8 *)&g.d_0068ac30)));
  diplo_wnd_close_active();
  return;
}

/* 004b7885 auto */
#define local_8 (*(ViewWindow * *)(frame_ + FRAME_OFF(0)))
void __cdecl parley_wnd_redraw(void)

{
  iptr iVar1;
  i32 uVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = (ViewWindow *)0x0;
  }
  else {
    local_8 = (ViewWindow *)(iVar1 - 0x48);
  }
  if (local_8->field_114 == 0) {
    parley_wnd_calc_layout((ParleyWindowLayout *)local_8);
    parley_wnd_build_title((ParleyTitleView *)local_8);
    gfx_set_draw_target((iptr)local_8);
    parley_wnd_draw_frame((ParleyWindowLayout *)local_8);
    parley_wnd_sync_sides(local_8);
    wnd_blit_surface((DibSurface *)local_8);
    window_show((WindowObjectView *)local_8);
    uVar1 = edit_get_text_end((ControlTextView *)local_8->field_29c);
    edit_set_caret((ControlTextView *)local_8->field_29c,uVar1);
    uVar1 = edit_get_sel_end((EditSelEndView *)local_8->field_298);
    edit_set_caret((ControlTextView *)local_8->field_298,uVar1);
  }
  return;
}
#undef local_8

/* 004b794a auto */
#define dlg_bevel_dark_color (*(byte *)((u8 *)&g.d_00635a0c))
#define dlg_bevel_light_color (*(byte *)((u8 *)&g.d_00635a08))
#define panel_margin_x (*(int *)((u8 *)&g.d_0062d858))
#define local_3c (*(i8 (*)[16])(frame_ + FRAME_OFF(4)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(28)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_1c (*(GameFont * *)(frame_ + FRAME_OFF(36)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_14 (*(tagRECT *)(frame_ + FRAME_OFF(44)))
void __thiscall parley_wnd_draw_frame(ParleyWindowLayout *this)

{
  int iVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(64)] __attribute__((aligned(8)));  /* original stack frame */
  
  surface_reset_clip((DibSurface *)this);
  crt_memcpy(&local_14,&this->client_height,0x10);
  for (local_18 = 0; local_18 < panel_bevel_width; local_18++) {
    gfx_draw_bevel_rect((iptr)this,(iptr)&local_14,(uint)dlg_bevel_light_color,(uint)dlg_bevel_dark_color);
    rect_deflate((iptr)&local_14,1,1);
  }
  parley_fill_background((WindowObjectView *)this,(iptr)&local_14,1);
  rect_deflate((iptr)&local_14,panel_padding_x + panel_bevel_width * -2,0);
  local_14.top = local_14.top + this->client_width + panel_bevel_width * -2;
  iVar1 = rect_height((iptr)&this->client_height);
  local_14.bottom = (iVar1 - this->client_width) + panel_bevel_width * -2;
  for (local_18 = 0; local_18 < panel_bevel_width; local_18++) {
    gfx_draw_bevel_rect((iptr)this,(iptr)&local_14,(uint)dlg_bevel_dark_color,(uint)dlg_bevel_light_color);
    rect_deflate((iptr)&local_14,1,1);
  }
  parley_fill_background((WindowObjectView *)this,(iptr)&local_14,2);
  local_20 = panel_padding_x;
  for (local_18 = 0; local_18 < 3; local_18++) {
    local_28 = (int)(*(int *)(this[1].pad_48 + local_18 * 0x1c + 0x8c) * this->client_width) / 0x18;
    local_2c = (int)(*(int *)(this[1].pad_48 + local_18 * 0x1c + 0x90) * this->client_width) / 0x18;
    local_24 = ((int)this->client_width >> 1) - (local_2c >> 1);
    SetRect(&local_14,local_20,local_24,local_28 + local_20,local_2c + local_24);
    gfx_set_scale_ratio(this->client_width,0x18);
    sprite_draw
              (*(Sprite **)(this[1].pad_48 + local_18 * 0x1c + 0x94),(iptr)local_3c,
               (iptr)this,local_20,local_24);
    gfx_reset_zoom_scale();
    local_20 = local_20 + panel_margin_x + local_28;
  }
  if (this->large_layout == 0) {
    local_1c = (GameFont *)&font_size20;
  }
  else {
    local_1c = (GameFont *)&font_size30;
  }
  local_20 -= panel_margin_x;
  iVar1 = (this->field_138 - local_20) - panel_padding_x;
  iVar2 = font_text_width(local_1c,(iptr)this->pad_15c);
  local_20 += (iVar1 / 2 - (iVar2 >> 1));
  local_24 = panel_bevel_width + panel_margin_y;
  gfx_set_text_color_index(10);
  surface_draw_text
            ((DibSurface *)this,(iptr)local_1c,(iptr)this->pad_15c,local_20 + 2,local_24 + 1,5);
  gfx_set_text_color_index(0x1a);
  surface_draw_text
            ((DibSurface *)this,(iptr)local_1c,(iptr)this->pad_15c,local_20 + 1,local_24,5);
  surface_draw_text
            ((DibSurface *)this,(iptr)local_1c,(iptr)this->pad_15c,local_20,local_24,5);
  surface_set_clip((DibSurface *)this,(iptr)&this->panel_rect);
  return;
}
#undef dlg_bevel_dark_color
#undef dlg_bevel_light_color
#undef panel_margin_x
#undef local_3c
#undef local_2c
#undef local_28
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14

/* 004b7c90 auto */
#define dlg_bg_color (*(byte *)((u8 *)&g.d_00635a04))
#define dlg_client_tile_surface (*(int *)((u8 *)&g.d_00635aa4))
#define dlg_frame_tile_surface (*(int *)((u8 *)&g.d_00635aa0))
void __thiscall parley_fill_background(WindowObjectView *this,iptr param_1,int param_2)

{
  i32 uVar1;
  i32 uVar2;
  i32 uVar3;
  i32 uVar4;
  
  if ((dlg_frame_tile_surface == 0) || (param_2 != 1)) {
    if ((dlg_client_tile_surface == 0) || (param_2 != 2)) {
      gfx_fill_rect((iptr)this,param_1,(uint)dlg_bg_color);
    }
    else {
      uVar4 = 0;
      uVar3 = 0;
      uVar1 = rect_height(param_1);
      uVar2 = rect_width(param_1);
      gfx_tile_fill((iptr)this,dlg_client_tile_surface,*(i32 *)param_1,*(i32 *)(param_1 + 4)
                         ,uVar2,uVar1,uVar3,uVar4);
    }
  }
  else {
    uVar4 = 0;
    uVar3 = 0;
    uVar1 = rect_height(param_1);
    uVar2 = rect_width(param_1);
    gfx_tile_fill((iptr)this,dlg_frame_tile_surface,*(i32 *)param_1,*(i32 *)(param_1 + 4),
                       uVar2,uVar1,uVar3,uVar4);
  }
  return;
}
#undef dlg_bg_color
#undef dlg_client_tile_surface
#undef dlg_frame_tile_surface

/* 004b7d72 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __thiscall parley_wnd_build_title(ParleyTitleView *this)

{
  iptr iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  text_clear();
  if (this->parley_kind == 4) {
    iVar1 = label_string(*(i32 *)(label_string_ids + 0xb54));
    text_append(iVar1);
    crt_strcpy(this->pad_11c + 0x40,&text_buffer);
  }
  else {
    iVar1 = label_string(*(i32 *)(label_string_ids + 0xb50));
    text_append(iVar1);
    text_append_space();
    iVar1 = civ_name_plural(this->civ_id);
    text_append(iVar1);
    text_append_space();
    text_append_lparen();
    if (*(char *)&civs[(this->civ_id)].attitude[human_civ] == '\0') {
      local_8 = 0;
    }
    else {
      local_8 = diplo_attitude_level((uint)civs[(this->civ_id)].attitude[human_civ]);
    }
    text_append_string_id(attitude_names[local_8]);
    text_append_rparen();
    crt_strcpy(this->pad_11c + 0x40,&text_buffer);
  }
  return;
}
#undef human_civ
#undef text_buffer
#undef local_8

/* 004b7eb6 auto */
#define chat_unread_count (*(i32 *)((u8 *)&g.d_006ad6a0))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define mp_chat_from_start (*(short *)((u8 *)&g.d_00654c7a))
#define parley_selected_action (*(i32 *)((u8 *)&g.d_0067a9b0))
#define chat_missed_message_count_i32 (*(i32 *)((u8 *)&g.d_006ad69c))
#define civ (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(ParleyTitleView * *)(frame_ + FRAME_OFF(16)))
/* WARNING: Removing unreachable block (ram,0x004b8008) */
/* WARNING: Removing unreachable block (ram,0x004b8051) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall parley_wnd_open(ViewWindow *this,iptr param_1,u32 param_2)

{
  bool bVar1;
  bool bVar2;
  iptr iVar3;
  iptr iVar4;
  i32 uVar3;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (param_2 == 4) {
    bVar2 = false;
    if (((game.wonder_city[0x18] == -1) && (iVar3 = civ_has_wonder(human_civ,9), iVar3 == 0)
        ) && (game.reveal_map == '\0')) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    for (civ = 1; civ < 8; civ++) {
      if ((((human_civ != civ) &&
           ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0)) &&
          ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) &&
         (((bVar1 || (mp_chat_from_start != 0)) ||
          ((*(byte *)&civs[civ].treaties[human_civ] & 1) != 0)))) {
        bVar2 = true;
        break;
      }
    }
    if (!bVar2) {
      popup_game(ADDR(0x62d934, ((u8 *)&g.d_0062d934)));
      return;
    }
    wnd_set_active_child(ADDR(0x68ac30, ((u8 *)&g.d_0068ac30)));
    chat_unread_count = 0;
    chat_missed_message_count_i32 = 0;
  }
  else {
    wnd_set_active_child(ADDR(0x67a7f0, ((u8 *)&g.d_0067a7f0)));
    parley_selected_action = 0xffffffff;
    this->field_3bc = '\0';
    this->field_3bd = '\0';
    this->field_3be = '\0';
    this->remote_side_agreed = '\0';
    if (param_2 == 3) {
      parley_set_mode_sides((WindowObjectView *)&parley_wnd,0);
    }
  }
  iVar4 = wnd_get_active_child();
  if (iVar4 == 0) {
    local_8 = (ParleyTitleView *)0x0;
  }
  else {
    local_8 = (ParleyTitleView *)(iVar4 - 0x48);
  }
  if (*(int *)(local_8->pad_0 + 0x114) == 0) {
    window_show((WindowObjectView *)local_8);
  }
  else {
    local_8->pad_0[0x114] = '\0';
    local_8->pad_0[0x115] = '\0';
    local_8->pad_0[0x116] = '\0';
    local_8->pad_0[0x117] = '\0';
    local_8->field_118 = param_1;
    if (param_2 != 3) {
      local_8->field_1ec = param_2;
      *(i32 *)local_8[1].pad_0 = (&parley_mode_left_kinds)[param_2 * 2];
      *(i32 *)(local_8[1].pad_0 + 4) = (&parley_mode_right_kinds)[param_2 * 2];
    }
    parley_wnd_build_title(local_8);
    local_8[1].pad_0[8] = 21;
    local_8[1].pad_0[9] = '\0';
    local_8[1].pad_0[10] = '\0';
    local_8[1].pad_0[0xb] = '\0';
    local_8[1].pad_0[0xc] = 21;
    local_8[1].pad_0[0xd] = '\0';
    local_8[1].pad_0[0xe] = '\0';
    local_8[1].pad_0[0xf] = '\0';
    wnd_repaint((SurfaceWindow *)local_8);
    window_show((WindowObjectView *)local_8);
    uVar3 = edit_get_text_end(*(ControlTextView **)(local_8[1].pad_0 + 0xac));
    edit_set_caret(*(ControlTextView **)(local_8[1].pad_0 + 0xac),uVar3);
    uVar3 = edit_get_sel_end(*(EditSelEndView **)(local_8[1].pad_0 + 0xa8));
    edit_set_caret(*(ControlTextView **)(local_8[1].pad_0 + 0xa8),uVar3);
  }
  snd_play_effect(((uint)map.seed + param_1 & 7) + 0x53,1,0,0);
  return;
}
#undef chat_unread_count
#undef human_civ
#undef mp_chat_from_start
#undef parley_selected_action
#undef chat_missed_message_count_i32
#undef civ
#undef local_8

/* 004b81dd auto */
#define dlg_pending_idle_callback (*(i8 * *)((u8 *)&g.d_00635a3c))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define parley_other_civ (*(iptr *)((u8 *)&g.d_0067a8c0))
#define parley_selected_action (*(i32 *)((u8 *)&g.d_0067a9b0))
/* WARNING: Removing unreachable block (ram,0x004b8211) */

void __cdecl parley_poll_net_replies(void)

{
  iptr iVar1;
  
  net_process_messages((NetSession *)&net_session,1,0);
  wnd_set_active_child(ADDR(0x67a7f0, ((u8 *)&g.d_0067a7f0)));
  if ((nm_parley_transaction_count == 0) || (parley_mode != 2)) {
    if ((nm_parley_accept_offer_count == 0) || (parley_mode != 1)) {
      if ((nm_parley_no_thanks_count == 0) || (parley_mode != 1)) {
        if ((nm_parley_counter_offer_count != 0) && (parley_mode == 1)) {
          nm_parley_counter_offer_count = 0;
          parley_mode = 2;
          parley_left_kind = parley_mode2_left_kind;
          parley_right_kind = parley_mode2_right_kind;
          parley_shown_left_kind = parley_left_kind;
          parley_shown_right_kind = parley_right_kind;
          parley_add_side_dialog((ViewWindow *)&parley_wnd,parley_mode2_left_kind,0);
          parley_add_side_dialog((ViewWindow *)&parley_wnd,parley_right_kind,1);
          iVar1 = civ_name_plural(parley_other_civ);
          text_set_string_arg(0,iVar1);
          dlg_pending_idle_callback = parley_poll_net_replies;
          popup_game_with_sprite(ADDR(0x62d98c, ((u8 *)&g.d_0062d98c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        }
      }
      else {
        nm_parley_no_thanks_count = 0;
        parley_mode = 3;
        parley_selected_action = 0xffffffff;
        parley_set_mode_sides((WindowObjectView *)&parley_wnd,1);
        iVar1 = civ_name_plural(parley_other_civ);
        text_set_string_arg(0,iVar1);
        dlg_pending_idle_callback = parley_poll_net_replies;
        popup_game_with_sprite(ADDR(0x62d97c, ((u8 *)&g.d_0062d97c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      }
    }
    else {
      nm_parley_accept_offer_count = 0;
      if (parley_received_offer != (void *)0x0) {
        *(i32 *)((int)parley_received_offer + 4) = 0x86;
        if (net_host_flag == '\0') {
          net_send_message(0x86,0,0,0,0,0,0,0,0,(iptr)parley_received_offer);
        }
        else {
          parley_execute_transaction((iptr)parley_received_offer);
        }
        operator_delete(parley_received_offer);
        parley_received_offer = (void *)0x0;
      }
      parley_mode = 2;
      parley_left_kind = parley_mode2_left_kind;
      parley_right_kind = parley_mode2_right_kind;
      parley_shown_left_kind = parley_left_kind;
      parley_shown_right_kind = parley_right_kind;
      parley_add_side_dialog((ViewWindow *)&parley_wnd,parley_mode2_left_kind,0);
      parley_add_side_dialog((ViewWindow *)&parley_wnd,parley_right_kind,1);
      dlg_pending_idle_callback = parley_poll_net_replies;
      popup_game_with_sprite(ADDR(0x62d96c, ((u8 *)&g.d_0062d96c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
    }
  }
  else {
    nm_parley_transaction_count = 0;
    if ((*(int *)((int)parley_received_offer + 0x10) == 6) && (*(int *)((int)parley_received_offer + 0x28) == 3)) {
      iVar1 = civ_name_plural(parley_other_civ);
      text_set_string_arg(0,iVar1);
      iVar1 = civ_name_plural(human_civ);
      text_set_string_arg(1,iVar1);
      if ((*(byte *)&civs[human_civ].treaties[parley_other_civ] & 8) == 0) {
        if ((*(byte *)&civs[human_civ].treaties[parley_other_civ] & 4) == 0) {
          if ((*(byte *)&civs[human_civ].treaties[parley_other_civ] & 2) != 0) {
            diplo_clear_treaty_flags(human_civ,parley_other_civ,2);
            popup_game(ADDR(0x62d960, ((u8 *)&g.d_0062d960)));
          }
        }
        else {
          diplo_clear_treaty_flags(human_civ,parley_other_civ,4);
          popup_game(ADDR(0x62d954, ((u8 *)&g.d_0062d954)));
        }
      }
      else {
        diplo_clear_treaty_flags(human_civ,parley_other_civ,8);
        popup_game(ADDR(0x62d944, ((u8 *)&g.d_0062d944)));
      }
    }
    else {
      parley_mode = 0;
      parley_left_kind = parley_mode_left_kinds;
      parley_right_kind = parley_mode_right_kinds;
      parley_shown_left_kind = parley_left_kind;
      parley_shown_right_kind = parley_right_kind;
      parley_add_side_dialog((ViewWindow *)&parley_wnd,parley_mode_left_kinds,0);
      parley_add_side_dialog((ViewWindow *)&parley_wnd,parley_right_kind,1);
    }
  }
  return;
}
#undef dlg_pending_idle_callback
#undef human_civ
#undef net_host_flag
#undef parley_other_civ
#undef parley_selected_action

/* 004b8676 auto */
#define parley_selected_action (*(int *)((u8 *)&g.d_0067a9b0))
/* WARNING: Removing unreachable block (ram,0x004b869f) */

void __thiscall parley_set_mode_sides(WindowObjectView *this,int param_1)

{
  wnd_set_active_child(ADDR(0x67a7f0, ((u8 *)&g.d_0067a7f0)));
  if (parley_selected_action == -1) {
    parley_mode = 3;
    ctrl_disable(parley_never_mind_button);
  }
  else if (parley_selected_action == 0) {
    parley_mode = 6;
    ctrl_enable(parley_never_mind_button);
  }
  else if (parley_selected_action == 1) {
    parley_mode = 0xc;
    if (parley_proposal_kind != 0) {
      parley_mode = 0xd;
    }
    ctrl_enable(parley_never_mind_button);
  }
  else if (parley_selected_action == 2) {
    if (parley_gift_kind == 0) {
      parley_mode = 7;
    }
    else if (parley_gift_kind == 1) {
      parley_mode = 8;
    }
    else if (parley_gift_kind == 2) {
      parley_mode = 9;
    }
    else if (parley_gift_kind == 3) {
      parley_mode = 10;
    }
    else {
      parley_mode = 0xb;
    }
    ctrl_enable(parley_never_mind_button);
  }
  else if (parley_selected_action == 3) {
    parley_mode = 5;
    ctrl_enable(parley_never_mind_button);
  }
  else if (parley_selected_action == 4) {
    parley_mode = 0xf;
    ctrl_enable(parley_never_mind_button);
  }
  parley_left_kind = (&parley_mode_left_kinds)[parley_mode * 2];
  parley_right_kind = (&parley_mode_right_kinds)[parley_mode * 2];
  parley_shown_left_kind = parley_left_kind;
  parley_shown_right_kind = parley_right_kind;
  if (param_1 != 0) {
    parley_add_side_dialog((ViewWindow *)&parley_wnd,parley_left_kind,0);
    parley_add_side_dialog((ViewWindow *)&parley_wnd,parley_right_kind,1);
  }
  return;
}
#undef parley_selected_action

/* 004b888e auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall parley_clear_side_controls(ViewWindow *this,int param_1)

{
  u8 *puVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((param_1 != 0) && (param_1 != 1)) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62d9c0, ((u8 *)&g.d_0062d9c0)),ADDR(0x62d9a0, ((u8 *)&g.d_0062d9a0)),0x4ea);
  }
  if (param_1 == 1) {
    if (this->side_text_edit != 0) {
      if ((Control *)this->side_text_edit != (Control *)0x0) {
        edit_scalar_dtor((Control *)this->side_text_edit,1);
      }
      this->side_text_edit = 0;
    }
    if (this->field_2e8 != 0) {
      if ((Checkbox *)this->field_2e8 != (Checkbox *)0x0) {
        checkbox_scalar_dtor((Checkbox *)this->field_2e8,1);
      }
      this->field_2e8 = 0;
    }
    if (this->field_2ec != 0) {
      if ((Checkbox *)this->field_2ec != (Checkbox *)0x0) {
        checkbox_scalar_dtor((Checkbox *)this->field_2ec,1);
      }
      this->field_2ec = 0;
    }
    if (this->field_2f0 != 0) {
      if ((Checkbox *)this->field_2f0 != (Checkbox *)0x0) {
        checkbox_scalar_dtor((Checkbox *)this->field_2f0,1);
      }
      this->field_2f0 = 0;
    }
    for (local_8 = 0; local_8 < 8; local_8++) {
      if (*(int *)(this->pad_2c4 + local_8 * 4 - 0x1c) != 0) {
        if (*(Checkbox **)(this->pad_2c4 + local_8 * 4 - 0x1c) != (Checkbox *)0x0) {
          checkbox_scalar_dtor(*(Checkbox **)(this->pad_2c4 + local_8 * 4 - 0x1c),1);
        }
        puVar1 = this->pad_2c4 + local_8 * 4 - 0x1c;
        puVar1[0] = '\0';
        puVar1[1] = '\0';
        puVar1[2] = '\0';
        puVar1[3] = '\0';
      }
      if (*(int *)(this->pad_2c4 + local_8 * 4 + 4) != 0) {
        if (*(Checkbox **)(this->pad_2c4 + local_8 * 4 + 4) != (Checkbox *)0x0) {
          checkbox_scalar_dtor(*(Checkbox **)(this->pad_2c4 + local_8 * 4 + 4),1);
        }
        puVar1 = this->pad_2c4 + local_8 * 4 + 4;
        puVar1[0] = '\0';
        puVar1[1] = '\0';
        puVar1[2] = '\0';
        puVar1[3] = '\0';
      }
    }
  }
  if (*(int *)(this->pad_364 + param_1 * 4) != 0) {
    if (*(Checkbox **)(this->pad_364 + param_1 * 4) != (Checkbox *)0x0) {
      checkbox_scalar_dtor(*(Checkbox **)(this->pad_364 + param_1 * 4),1);
    }
    puVar1 = this->pad_364 + param_1 * 4;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
  }
  if (*(int *)(this->pad_364 + param_1 * 4 + 8) != 0) {
    if (*(RadioGroupDtorView **)(this->pad_364 + param_1 * 4 + 8) != (RadioGroupDtorView *)0x0) {
      radiogrp_scalar_dtor(*(RadioGroupDtorView **)(this->pad_364 + param_1 * 4 + 8),1);
    }
    puVar1 = this->pad_364 + param_1 * 4 + 8;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
  }
  if (*(int *)(this->pad_364 + param_1 * 4 + 0x10) != 0) {
    if (*(Control **)(this->pad_364 + param_1 * 4 + 0x10) != (Control *)0x0) {
      edit_scalar_dtor(*(Control **)(this->pad_364 + param_1 * 4 + 0x10),1);
    }
    puVar1 = this->pad_364 + param_1 * 4 + 0x10;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
  }
  if (*(int *)(this->pad_364 + param_1 * 4 + 0x18) != 0) {
    if (*(Control **)(this->pad_364 + param_1 * 4 + 0x18) != (Control *)0x0) {
      scrollbar_scalar_dtor(*(Control **)(this->pad_364 + param_1 * 4 + 0x18),1);
    }
    puVar1 = this->pad_364 + param_1 * 4 + 0x18;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
  }
  if (*(int *)(this->pad_364 + param_1 * 4 + 0x20) != 0) {
    if (*(Hotspot **)(this->pad_364 + param_1 * 4 + 0x20) != (Hotspot *)0x0) {
      hotspot_scalar_dtor(*(Hotspot **)(this->pad_364 + param_1 * 4 + 0x20),1);
    }
    puVar1 = this->pad_364 + param_1 * 4 + 0x20;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
  }
  if (*(int *)(this->pad_364 + param_1 * 4 + 0x28) != 0) {
    if (*(Control **)(this->pad_364 + param_1 * 4 + 0x28) != (Control *)0x0) {
      ctrl_scalar_dtor(*(Control **)(this->pad_364 + param_1 * 4 + 0x28),1);
    }
    puVar1 = this->pad_364 + param_1 * 4 + 0x28;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
  }
  if (*(int *)(this->pad_364 + param_1 * 4 + 0x30) != 0) {
    if (*(Control **)(this->pad_364 + param_1 * 4 + 0x30) != (Control *)0x0) {
      ctrl_scalar_dtor(*(Control **)(this->pad_364 + param_1 * 4 + 0x30),1);
    }
    puVar1 = this->pad_364 + param_1 * 4 + 0x30;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
  }
  if (*(int *)(this->pad_3c0 + param_1 * 4 - 0x24) != 0) {
    if (*(Control **)(this->pad_3c0 + param_1 * 4 - 0x24) != (Control *)0x0) {
      ctrl_scalar_dtor(*(Control **)(this->pad_3c0 + param_1 * 4 - 0x24),1);
    }
    puVar1 = this->pad_3c0 + param_1 * 4 - 0x24;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
  }
  if (*(int *)(this->pad_3c0 + param_1 * 4 - 0x1c) != 0) {
    if (*(Control **)(this->pad_3c0 + param_1 * 4 - 0x1c) != (Control *)0x0) {
      ctrl_scalar_dtor(*(Control **)(this->pad_3c0 + param_1 * 4 - 0x1c),1);
    }
    puVar1 = this->pad_3c0 + param_1 * 4 - 0x1c;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
  }
  this->field_3ac = this->panel_rect;
  this->field_3b0 = this->panel_top;
  this->field_3b4 = this->panel_right;
  this->field_3b8 = this->panel_bottom;
  this->field_3b8 = this->show_turn_timer;
  if (param_1 == 0) {
    iVar2 = rect_width((iptr)&this->panel_rect);
    this->field_3b4 = iVar2 / 2;
  }
  else {
    iVar2 = rect_width((iptr)&this->panel_rect);
    this->field_3ac = iVar2 / 2;
  }
  parley_fill_background((WindowObjectView *)this,(iptr)&this->field_3ac,2);
  return;
}
#undef local_8

/* 004b8e5c auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define local_58 (*(uptr *)(frame_ + FRAME_OFF(0)))
#define local_50 (*(char (*)[32])(frame_ + FRAME_OFF(8)))
#define local_30 (*(uint *)(frame_ + FRAME_OFF(40)))
#define local_2c (*(i32 *)(frame_ + FRAME_OFF(44)))
#define local_28 (*(char (*)[32])(frame_ + FRAME_OFF(48)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(80)))
void __cdecl parley_gold_edit_on_change(int param_1)

{
  char *pcVar1;
  size_t sVar2;
  int iVar3;
  size_t sVar4;
  i8 frame_[FRAME_OFF(88)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_2c = 0;
  _memset(local_28,0,0x20);
  _memset(local_50,0,0x20);
  local_30 = (uint)(param_1 != 0x3f8);
  local_8 = edit_get_sel_end(*(EditSelEndView **)(&parley_gold_edits + local_30 * 4));
  ctrl_get_text(*(ControlTextView **)(&parley_gold_edits + local_30 * 4),(iptr)local_28);
  __itoa(civs[human_civ].gold,local_50,10);
  for (local_58 = 0; sVar2 = _strlen(local_28), local_58 < sVar2; local_58++) {
    if ((local_28[local_58] < '0') || ('9' < local_28[local_58])) {
      local_2c = 1;
      crt_strcpy(local_28 + local_58,local_28 + local_58 + 1);
    }
  }
  iVar3 = _atoi(local_28);
  if (((parley_mode == 0xe) && (local_30 == 0)) || ((parley_mode != 0xf && (parley_mode != 0xe)))
     ) {
    sVar2 = _strlen(local_50);
    sVar4 = _strlen(local_28);
    if ((sVar2 < sVar4) || (civs[human_civ].gold < iVar3)) {
      local_2c = 1;
      pcVar1 = local_28 + local_8;
      iVar3 = local_8 - 1;
      local_8--;
      crt_strcpy(local_28 + iVar3,pcVar1);
    }
  }
  iVar3 = _atoi(local_28);
  if (iVar3 < 1) {
    *(i32 *)(&parley_gold_entered + local_30 * 4) = 0;
  }
  else {
    *(i32 *)(&parley_gold_entered + local_30 * 4) = 1;
  }
  parley_update_buttons((ViewWindow *)&parley_wnd);
  if (local_2c != 0) {
    sVar2 = _strlen(local_28);
    if (sVar2 < local_8) {
      local_8 = _strlen(local_28);
    }
    ctrl_set_text(*(ControlTextView **)(&parley_gold_edits + local_30 * 4),(iptr)local_28);
    edit_set_caret(*(ControlTextView **)(&parley_gold_edits + local_30 * 4),local_8);
  }
  return;
}
#undef human_civ
#undef local_58
#undef local_50
#undef local_30
#undef local_2c
#undef local_28
#undef local_8

/* 004b90ad auto */
#define chat_log_buffer (*(char * *)((u8 *)&g.d_0062d870))
#define chat_mute_anonymous (*(int *)((u8 *)&g.d_0068aee0))
#define chat_unread_count (*(int *)((u8 *)&g.d_006ad6a0))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define parley_other_civ (*(int *)((u8 *)&g.d_0067a8c0))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define chat_missed_message_count_i32 (*(i32 *)((u8 *)&g.d_006ad69c))
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall
chat_receive_message(WindowObjectView *this,iptr civ,iptr civ2,iptr param_3,iptr param_4)

{
  u32 uVar1;
  size_t sVar2;
  i32 uVar3;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  ctrl_get_text(chat_log_edit,(iptr)chat_log_buffer);
  text_clear();
  sVar2 = _strlen(chat_log_buffer);
  if (sVar2 != 0) {
    crt_strcat(&text_buffer,&chat_recv_newline_str);
  }
  if ((char)param_3 == '\0') {
    uVar3 = label_string(*(i32 *)(label_string_ids + 0xb60));
    crt_strcat(&text_buffer,uVar3);
    text_append_space();
    chat_append_sender_name(civ);
    crt_strcat(&text_buffer,&chat_recv_year_open_str);
    text_append_year((int)game.year);
    crt_strcat(&text_buffer,&chat_recv_year_close_str);
  }
  else {
    uVar3 = label_string(*(i32 *)(label_string_ids + 0xb58));
    crt_strcat(&text_buffer,uVar3);
    text_append_space();
    chat_append_sender_name(civ);
    uVar3 = label_string(*(i32 *)(label_string_ids + 0xb5c));
    crt_strcat(&text_buffer,uVar3);
    text_append_space();
    chat_append_sender_name(civ2);
    crt_strcat(&text_buffer,&chat_recv_private_year_open_str);
    text_append_year((int)game.year);
    crt_strcat(&text_buffer,&chat_recv_private_year_close_str);
  }
  crt_strcat(&text_buffer,param_4);
  if ((civ == 0) && (chat_mute_anonymous != 0)) {
    return;
  }
  if ((char)param_3 == '\0') {
    if (parley_wnd_closed == 0) {
      if (parley_other_civ == civ) goto LAB_004b9295;
      uVar1 = this[civ + 200].field_0;
    }
    else {
      uVar1 = this[civ + 200].field_0;
    }
    if (uVar1 != 0) {
      return;
    }
  }
LAB_004b9295:
  for (local_8 = 1; local_8 < 8; local_8++) {
    if ((((local_8 != civ) && (human_civ != local_8)) &&
        ((1 << ((byte)local_8 & 0x1f) & (uint)game.human_players) != 0)) &&
       ((*(byte *)(local_8 * 0x594 + ADDR(0x64c6c3, ((u8 *)&civs + 35)) + human_civ * 4) & 1) != 0)) {
      net_send_message(0x68,*(i32 *)
                               (&net_player_slots + *(int *)(&net_civ_slots + local_8 * 4) * 0x54),
                         civ,civ2,1,0,0,0,param_4,0);
    }
  }
  chat_log_append(ADDR(0x679640, ((u8 *)&g.d_00679640)));
  if (chat_wnd_closed != 0) {
    chat_unread_count++;
    chat_missed_message_count_i32++;
  }
  if ((parley_wnd_closed != 0) && (chat_wnd_closed != 0)) {
    parley_wnd_open((ViewWindow *)&chat_wnd,0,4);
  }
  return;
}
#undef chat_log_buffer
#undef chat_mute_anonymous
#undef chat_unread_count
#undef human_civ
#undef parley_other_civ
#undef text_buffer
#undef chat_missed_message_count_i32
#undef local_8

/* 004b93a2 auto */
#define chat_log_buffer (*(char * *)((u8 *)&g.d_0062d870))
#define chat_log_capacity (*(int *)((u8 *)&g.d_0069b03c))
#define local_8 (*(uptr *)(frame_ + FRAME_OFF(0)))
void __cdecl chat_log_append(iptr param_1)

{
  int iVar1;
  size_t sVar2;
  size_t sVar3;
  i32 uVar4;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = chat_log_capacity;
  local_8 = 0;
  sVar2 = _strlen(chat_log_buffer);
  sVar3 = _strlen((char *)param_1);
  if (iVar1 - (sVar2 + 1) < sVar3 + 1) {
    local_8 = _strlen((char *)param_1);
    do {
      local_8++;
      if ((chat_log_buffer[local_8] == '\r') || (chat_log_buffer[local_8] == '\n')) break;
    } while (chat_log_buffer[local_8] != '\0');
    if (chat_log_buffer[local_8] != '\0') {
      for (; (chat_log_buffer[local_8] == '\r' || (chat_log_buffer[local_8] == '\n'));
          local_8 = local_8 + 1) {
      }
    }
  }
  crt_strcpy(chat_log_buffer,chat_log_buffer + local_8);
  crt_strcat(chat_log_buffer,param_1);
  ctrl_set_text(chat_log_edit,(iptr)chat_log_buffer);
  ctrl_set_text(parley_chat_log_edit,(iptr)chat_log_buffer);
  uVar4 = edit_get_text_end(chat_log_edit);
  edit_set_caret(chat_log_edit,uVar4);
  uVar4 = edit_get_text_end(chat_log_edit);
  edit_set_caret(parley_chat_log_edit,uVar4);
  return;
}
#undef chat_log_buffer
#undef chat_log_capacity
#undef local_8

/* 004b9504 auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
void __cdecl chat_append_sender_name(int civ)

{
  i32 uVar1;
  
  if (civ == 0) {
    uVar1 = label_string(*(i32 *)(label_string_ids + 0xb64));
    crt_strcat(&text_buffer,uVar1);
  }
  else {
    uVar1 = civ_leader_title(civ);
    crt_strcat(&text_buffer,uVar1);
    text_append_space();
    uVar1 = civ_leader_name(civ);
    crt_strcat(&text_buffer,uVar1);
  }
  return;
}
#undef text_buffer

/* 004b957e auto */
void __cdecl parley_wnd_on_key(int param_1)

{
  if (param_1 == 0xd2) {
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
#define chat_log_buffer (*(void * *)((u8 *)&g.d_0062d870))
#define chat_log_capacity (*(int *)((u8 *)&g.d_0069b03c))
void __cdecl chat_clear_button_on_click(void)

{
  _memset(chat_log_buffer,0,chat_log_capacity + 1);
  ctrl_set_text(chat_log_edit,(iptr)chat_log_buffer);
  ctrl_set_text(parley_chat_log_edit,(iptr)chat_log_buffer);
  ctrl_set_focus(parley_chat_input_edit);
  return;
}
#undef chat_log_buffer
#undef chat_log_capacity

/* 004b9635 auto */
i32 __cdecl parley_edit_escape_filter(i32 param_1,int param_2)

{
  i32 uVar1;
  
  if ((param_2 == 0x1b) || (param_2 == 0xd2)) {
    diplo_wnd_escape_close(0);
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

/* 004b968a auto */
#define chat_input_buffer (*(char * *)((u8 *)&g.d_0062d86c))
#define chat_log_buffer (*(char * *)((u8 *)&g.d_0062d870))
#define chat_remain_anonymous (*(int *)((u8 *)&g.d_0068aedc))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define local_1c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(16)))
#define civ (*(int *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(24)))
i32 __cdecl chat_input_on_key(i32 param_1,int param_2)

{
  iptr iVar1;
  size_t sVar1;
  i32 uVar2;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar1 - 0x48;
  }
  if (param_2 < 0x2b5) {
    if (0x2af < param_2) {
      chat_insert_macro_text(*(i32 *)(local_8 + 0x298),param_2);
      return 0;
    }
    if (param_2 == 0xd0) {
      ctrl_get_text(*(ControlTextView **)(local_8 + 0x298),(iptr)chat_input_buffer);
      sVar1 = _strlen(chat_input_buffer);
      if (sVar1 == 0) {
        return 0;
      }
      ctrl_get_text(chat_log_edit,(iptr)chat_log_buffer);
      text_clear();
      sVar1 = _strlen(chat_log_buffer);
      if (sVar1 != 0) {
        crt_strcat(&text_buffer,&chat_send_newline_str);
      }
      uVar2 = label_string(*(i32 *)(label_string_ids + 0xb68));
      crt_strcat(&text_buffer,uVar2);
      text_append_space();
      if (*(int *)(local_8 + 0x1ec) == 4) {
        local_10 = 0;
        for (civ = 1; civ < 8; civ++) {
          if (*(int *)(&chat_send_to_civs + civ * 4) != 0) {
            if (local_10 != 0) {
              crt_strcat(&text_buffer,&chat_send_recipient_sep_str);
            }
            chat_append_sender_name(civ);
            local_10++;
          }
        }
      }
      else {
        chat_append_sender_name(*(i32 *)(local_8 + 0x118));
        local_10 = 1;
      }
      if (local_10 == 0) {
        return 0;
      }
      crt_strcat(&text_buffer,&chat_send_year_open_str);
      text_append_year((int)game.year);
      crt_strcat(&text_buffer,&chat_send_year_close_str);
      crt_strcat(&text_buffer,chat_input_buffer);
      chat_log_append(ADDR(0x679640, ((u8 *)&g.d_00679640)));
      if (*(int *)(local_8 + 0x1ec) == 4) {
        for (civ = 1; civ < 8; civ++) {
          if ((((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) &&
              (human_civ != civ)) && (*(int *)(&chat_send_to_civs + civ * 4) != 0)) {
            if (chat_remain_anonymous == 0) {
              local_18 = human_civ;
            }
            else {
              local_18 = 0;
            }
            net_send_message(0x68,*(i32 *)
                                     (&net_player_slots + *(int *)(&net_civ_slots + civ * 4) * 0x54),
                               local_18,civ,0,0,0,0,(iptr)chat_input_buffer,0);
            for (local_10 = 1; local_10 < 8; local_10++) {
              if ((((1 << ((byte)local_10 & 0x1f) & (uint)game.human_players) != 0) &&
                  (human_civ != local_10)) &&
                 ((local_10 != civ &&
                  ((*(byte *)(local_10 * 0x594 + ADDR(0x64c6c3, ((u8 *)&civs + 35)) + human_civ * 4) & 1) != 0)))) {
                if (chat_remain_anonymous == 0) {
                  local_1c = human_civ;
                }
                else {
                  local_1c = 0;
                }
                net_send_message(0x68,*(i32 *)
                                         (&net_player_slots +
                                         *(int *)(&net_civ_slots + local_10 * 4) * 0x54),local_1c,
                                   civ,1,0,0,0,(iptr)chat_input_buffer,0);
              }
            }
          }
        }
      }
      else {
        net_send_message(0x68,*(i32 *)
                                 (&net_player_slots +
                                 *(int *)(&net_civ_slots + *(int *)(local_8 + 0x118) * 4) * 0x54),
                           human_civ,*(iptr *)(local_8 + 0x118),0,0,0,0,(iptr)chat_input_buffer,0);
        for (local_10 = 1; local_10 < 8; local_10++) {
          if ((((1 << ((byte)local_10 & 0x1f) & (uint)game.human_players) != 0) &&
              (human_civ != local_10)) &&
             ((*(int *)(local_8 + 0x118) != local_10 &&
              ((*(byte *)(local_10 * 0x594 + ADDR(0x64c6c3, ((u8 *)&civs + 35)) + human_civ * 4) & 1) != 0)))) {
            net_send_message(0x68,*(i32 *)
                                     (&net_player_slots + *(int *)(&net_civ_slots + local_10 * 4) * 0x54)
                               ,human_civ,*(iptr *)(local_8 + 0x118),1,0,0,0,(iptr)chat_input_buffer,
                               0);
          }
        }
      }
      *chat_input_buffer = '\0';
      ctrl_set_text(*(ControlTextView **)(local_8 + 0x298),(iptr)chat_input_buffer);
      ctrl_set_focus(*(ControlFocusView **)(local_8 + 0x298));
      return 0;
    }
    if (param_2 == 0xd2) {
      diplo_wnd_escape_close(0);
      return 0;
    }
  }
  return 1;
}
#undef chat_input_buffer
#undef chat_log_buffer
#undef chat_remain_anonymous
#undef human_civ
#undef text_buffer
#undef local_1c
#undef local_18
#undef local_10
#undef civ
#undef local_8

/* 004db690 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define parley_list_counts (*(int *)((u8 *)&g.d_0067ab90))
#define parley_other_civ (*(int *)((u8 *)&g.d_0067a8c0))
#define parley_offer_left_count_i32 (*(i32 *)((u8 *)&g.d_0068abd0))
#define parley_offer_right_count_i32 (*(i32 *)((u8 *)&g.d_0068abd4))
#define local_1c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(uint *)(frame_ + FRAME_OFF(16)))
#define local_c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(24)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 * __thiscall parley_send_offer(ParleyOfferBuffer *this,int param_1)

{
  i32 uVar1;
  i32 *puVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  uVar1 = *(i32 *)(&parley_offer_kinds + param_1 * 4);
  parley_offer_left_count_i32 = 0;
  parley_offer_right_count_i32 = 0;
  local_c = *(int *)(&parley_item_header_sizes + this->offer_type_right * 4);
  switch(this->offer_type_right) {
  case 8:
  case 0xc:
    for (local_1c = 0; local_1c < parley_list_count_right; local_1c++) {
      if (*(int *)(&parley_list_selected_right + local_1c * 4) == 1) {
        parley_offer_right_count_i32++;
      }
    }
    local_c = this->selected_count_right * 4 + local_c;
    break;
  case 10:
  case 0x11:
    for (local_1c = 0; local_1c < parley_list_count_right; local_1c++) {
      if (*(int *)(&parley_list_selected_right + local_1c * 4) == 1) {
        parley_offer_right_count_i32++;
      }
    }
    local_c = this->selected_count_right * 4 + local_c;
    if (this->offer_type_right == 0x11) {
      local_c = this->selected_count_right * 4 + local_c;
    }
  }
  local_10 = local_c + 0x20;
  if (param_1 == 0xe) {
    local_8 = *(int *)(&parley_item_header_sizes + this->offer_type_left * 4);
    switch(this->offer_type_left) {
    case 8:
    case 0xc:
      for (local_1c = 0; local_1c < parley_list_counts; local_1c++) {
        if (*(int *)(&parley_list_selected + local_1c * 4) == 1) {
          parley_offer_left_count_i32++;
        }
      }
      local_8 = this->selected_count_left * 4 + local_8;
      break;
    case 10:
    case 0x11:
      for (local_1c = 0; local_1c < parley_list_counts; local_1c++) {
        if (*(int *)(&parley_list_selected + local_1c * 4) == 1) {
          parley_offer_left_count_i32++;
        }
      }
      local_8 = this->selected_count_left * 4 + local_8;
      if (this->offer_type_left == 0x11) {
        local_8 = this->selected_count_left * 4 + local_8;
      }
    }
    local_10 += local_8;
  }
  puVar2 = operator_new(local_10);
  if (puVar2 == (i32 *)0x0) {
    dbg_log(ADDR(0x62e6ec, ((u8 *)&g.d_0062e6ec)));
    puVar2 = (i32 *)0x0;
  }
  else {
    *puVar2 = 0x66606660;
    puVar2[1] = 0x82;
    puVar2[2] = local_10;
    puVar2[4] = this->parley_kind;
    puVar2[5] = human_civ;
    puVar2[6] = this->civ_id;
    puVar2[7] = uVar1;
    if (local_10 + (int)puVar2 < (uint)(local_c + (int)(puVar2 + 8))) {
      err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62e764, ((u8 *)&g.d_0062e764)),ADDR(0x62e738, ((u8 *)&g.d_0062e738)),0x9f);
    }
    parley_pack_offer_items(this,(iptr)(puVar2 + 8),this->offer_type_right,local_c,1);
    if (param_1 == 0xe) {
      iVar3 = (int)puVar2 + local_c + 0x20;
      if (local_8 + iVar3 != local_10 + (int)puVar2) {
        err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62e7cc, ((u8 *)&g.d_0062e7cc)),ADDR(0x62e7a0, ((u8 *)&g.d_0062e7a0)),0xa4);
      }
      parley_pack_offer_items(this,iVar3,this->offer_type_left,local_8,0);
    }
    net_send_message(0x82,*(i32 *)
                             (&net_player_slots + *(int *)(&net_civ_slots + parley_other_civ * 4) * 0x54),0,0
                       ,0,0,0,0,0,(iptr)puVar2);
  }
  return puVar2;
}
#undef human_civ
#undef parley_list_counts
#undef parley_other_civ
#undef parley_offer_left_count_i32
#undef parley_offer_right_count_i32
#undef local_1c
#undef local_10
#undef local_c
#undef local_8

/* 004dbab4 auto */
#define parley_list_counts (*(i32 *)((u8 *)&g.d_0067ab90))
#define local_34 (*(i32 * *)(frame_ + FRAME_OFF(4)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_28 (*(i32 * *)(frame_ + FRAME_OFF(16)))
#define local_24 (*(char (*)[32])(frame_ + FRAME_OFF(20)))
void __thiscall
parley_pack_offer_items
          (ParleyOfferBuffer *this,iptr param_1,i32 param_2,i32 param_3,iptr param_4)

{
  int iVar1;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  switch(param_2) {
  case 5:
  case 6:
    *(i32 *)param_1 = param_2;
    *(i32 *)(param_1 + 4) = param_3;
    *(u32 *)(param_1 + 8) = this->field_218;
    break;
  case 8:
    *(i32 *)param_1 = param_2;
    *(i32 *)(param_1 + 4) = param_3;
    *(i32 *)(param_1 + 8) = *(i32 *)(this->pad_21c + param_4 * 4 + 0x1020c);
    local_34 = (i32 *)(param_1 + 0xc);
    local_30 = 0;
    for (local_2c = 0; local_2c < (int)(&parley_list_counts)[param_4]; local_2c++) {
      if (*(int *)(&parley_list_selected + local_2c * 4 + param_4 * 0x2004) == 1) {
        *local_34 = *(i32 *)(this->pad_21c + param_4 * 0x2004 + local_2c * 4 + 0x1d4);
        local_34++;
        local_30++;
        if (*(int *)(this->pad_21c + param_4 * 4 + 0x1020c) == local_30) {
          return;
        }
      }
    }
    break;
  case 9:
    *(i32 *)param_1 = param_2;
    *(i32 *)(param_1 + 4) = param_3;
    ctrl_get_text(*(ControlTextView **)(&parley_gold_edits + param_4 * 4),(iptr)local_24);
    iVar1 = _atoi(local_24);
    *(int *)(param_1 + 8) = iVar1;
    break;
  case 10:
    *(i32 *)param_1 = param_2;
    *(i32 *)(param_1 + 4) = param_3;
    *(i32 *)(param_1 + 8) = *(i32 *)(this->pad_21c + param_4 * 4 + 0x1020c);
    local_28 = (i32 *)(param_1 + 0xc);
    local_30 = 0;
    for (local_2c = 0; local_2c < (int)(&parley_list_counts)[param_4]; local_2c++) {
      if (*(int *)(&parley_list_selected + local_2c * 4 + param_4 * 0x2004) == 1) {
        *local_28 = *(i32 *)(this->pad_21c + param_4 * 0x2004 + local_2c * 4 + 0x41dc);
        local_28++;
        local_30++;
        if (*(int *)(this->pad_21c + param_4 * 4 + 0x1020c) == local_30) {
          return;
        }
      }
    }
    break;
  case 0xc:
    *(i32 *)param_1 = param_2;
    *(i32 *)(param_1 + 4) = param_3;
    *(i32 *)(param_1 + 8) = *(i32 *)(this->pad_21c + param_4 * 4 + 0x1020c);
    local_34 = (i32 *)(param_1 + 0xc);
    local_30 = 0;
    for (local_2c = 0; local_2c < (int)(&parley_list_counts)[param_4]; local_2c++) {
      if (*(int *)(&parley_list_selected + local_2c * 4 + param_4 * 0x2004) == 1) {
        *local_34 = *(i32 *)(this->pad_21c + param_4 * 0x2004 + local_2c * 4 + 0x1d4);
        local_34++;
        local_30++;
        if (*(int *)(this->pad_21c + param_4 * 4 + 0x1020c) == local_30) {
          return;
        }
      }
    }
    break;
  case 0xd:
    *(i32 *)param_1 = param_2;
    *(i32 *)(param_1 + 4) = param_3;
    *(i32 *)(param_1 + 8) = *(i32 *)(this->pad_21c + param_4 * 4 + 8);
    break;
  case 0x11:
    *(i32 *)param_1 = param_2;
    *(i32 *)(param_1 + 4) = param_3;
    *(i32 *)(param_1 + 8) = *(i32 *)(this->pad_21c + param_4 * 4 + 0x1020c);
    local_28 = (i32 *)(param_1 + 0xc);
    local_30 = 0;
    for (local_2c = 0; local_2c < (int)(&parley_list_counts)[param_4]; local_2c++) {
      if (*(int *)(&parley_list_selected + local_2c * 4 + param_4 * 0x2004) == 1) {
        *local_28 = *(i32 *)(this->pad_21c + param_4 * 0x2004 + local_2c * 4 + 0x41dc);
        local_28[1] = *(i32 *)(this->pad_21c + param_4 * 0x2004 + local_2c * 4 + 0xc1ec);
        local_28 += 2;
        local_30++;
        if (*(int *)(this->pad_21c + param_4 * 4 + 0x1020c) == local_30) {
          return;
        }
      }
    }
  }
  return;
}
#undef parley_list_counts
#undef local_34
#undef local_30
#undef local_2c
#undef local_28
#undef local_24

/* 004dbee6 auto */
void __thiscall parley_build_description(WindowObjectView *this,iptr param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  iptr iVar2;
  i32 *puVar3;
  size_t sVar4;
  iptr iVar5;
  
  if (param_1 != 0) {
    piVar2 = (int *)(param_1 + 0x20);
    iVar2 = *(int *)(param_1 + 0x24) + param_1;
    puVar3 = (i32 *)(iVar2 + 0x20);
    str_clear(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)));
    sVar4 = _strlen(&parley_description);
    if (sVar4 != 0) {
      err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62e834, ((u8 *)&g.d_0062e834)),ADDR(0x62e808, ((u8 *)&g.d_0062e808)),0x120);
    }
    if (param_2 == 0) {
      iVar5 = label_string(*(i32 *)(label_string_ids + 0xc70));
      str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
      crt_strcat(&parley_description,&parley_desc_transmitted_crlf_str);
    }
    sVar4 = _strlen(&parley_description);
    if (0x7ff < sVar4) {
      err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62e888, ((u8 *)&g.d_0062e888)),ADDR(0x62e85c, ((u8 *)&g.d_0062e85c)),0x126);
    }
    switch(*(i32 *)(param_1 + 0x10)) {
    case 6:
      parley_describe_treaty(this,*(i32 *)(param_1 + 0x28),0);
      break;
    case 7:
      iVar5 = label_string(*(i32 *)(label_string_ids + 0xc98));
      str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
      crt_strcat(&parley_description,&parley_desc_gift_adv_crlf_str);
      iVar5 = label_string(*(i32 *)(label_string_ids + 0xc9c));
      str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
      crt_strcat(&parley_description,&parley_desc_gift_adv_head_crlf_str);
      parley_describe_advances((iptr)piVar2);
      break;
    case 8:
      iVar5 = label_string(*(i32 *)(label_string_ids + 0xc98));
      str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
      crt_strcat(&parley_description,&parley_desc_gift_gold_crlf_str);
      iVar5 = label_string(*(i32 *)(label_string_ids + 0xca4));
      str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
      crt_strcat(&parley_description,&parley_desc_gift_gold_head_crlf_str);
      str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),ADDR(0x62e8e8, ((u8 *)&g.d_0062e8e8)));
      parley_describe_gold(*(i32 *)(param_1 + 0x28));
      break;
    case 9:
      iVar5 = label_string(*(i32 *)(label_string_ids + 0xc98));
      str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
      crt_strcat(&parley_description,&parley_desc_gift_units_crlf_str);
      iVar5 = label_string(*(i32 *)(label_string_ids + 0xca0));
      str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
      crt_strcat(&parley_description,&parley_desc_gift_units_head_crlf_str);
      parley_describe_units((iptr)piVar2);
      break;
    case 10:
      iVar5 = label_string(*(i32 *)(label_string_ids + 0xc98));
      str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
      crt_strcat(&parley_description,&parley_desc_gift_cities_crlf_str);
      iVar5 = label_string(*(i32 *)(label_string_ids + 0xca8));
      str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
      crt_strcat(&parley_description,&parley_desc_gift_cities_head_crlf_str);
      parley_describe_cities((iptr)piVar2);
      break;
    case 0xb:
      iVar5 = label_string(*(i32 *)(label_string_ids + 0xc98));
      str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
      crt_strcat(&parley_description,&parley_desc_gift_maps_crlf_str);
      parley_describe_maps(*(i32 *)(param_1 + 0x28),0);
      break;
    case 0xc:
      iVar5 = label_string(*(i32 *)(label_string_ids + 0xc84));
      str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
      crt_strcat(&parley_description,&parley_desc_war_offer_crlf_str);
      iVar5 = label_string(*(i32 *)(label_string_ids + 0xc94));
      str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
      crt_strcat(&parley_description,&parley_desc_war_head_crlf_str);
      parley_describe_war_targets((iptr)piVar2);
      break;
    case 0xd:
      iVar5 = label_string(*(i32 *)(label_string_ids + 0xc84));
      str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
      crt_strcat(&parley_description,&parley_desc_maps_offer_crlf_str);
      iVar1 = *(int *)(param_1 + 0x28);
      if (iVar1 == 0) {
        iVar5 = label_string(*(i32 *)(label_string_ids + 0xc88));
        str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
      }
      else if (iVar1 == 1) {
        iVar5 = label_string(*(i32 *)(label_string_ids + 0xc8c));
        str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
      }
      else if (iVar1 == 2) {
        iVar5 = label_string(*(i32 *)(label_string_ids + 0xc90));
        str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
      }
      crt_strcat(&parley_description,&parley_desc_maps_kind_crlf_str);
      break;
    case 0xe:
      iVar5 = label_string(*(i32 *)(label_string_ids + 0xcb4));
      str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
      crt_strcat(&parley_description,&parley_desc_barter_crlf_str);
      switch(*puVar3) {
      case 5:
      case 6:
        iVar5 = label_string(*(i32 *)(label_string_ids + 0xd1c));
        str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
        crt_strcat(&parley_description,&parley_desc_give_treaty_crlf_str);
        parley_describe_treaty(this,*(i32 *)(iVar2 + 0x28),1);
        break;
      case 8:
        iVar5 = label_string(*(i32 *)(label_string_ids + 0xcb8));
        str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
        crt_strcat(&parley_description,&parley_desc_give_adv_crlf_str);
        parley_describe_advances((iptr)puVar3);
        break;
      case 9:
        iVar5 = label_string(*(i32 *)(label_string_ids + 0xcbc));
        str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
        crt_strcat(&parley_description,&parley_desc_give_gold_crlf_str);
        str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),ADDR(0x62e920, ((u8 *)&g.d_0062e920)));
        parley_describe_gold(*(i32 *)(iVar2 + 0x28));
        break;
      case 10:
        iVar5 = label_string(*(i32 *)(label_string_ids + 0xcc0));
        str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
        crt_strcat(&parley_description,&parley_desc_give_units_crlf_str);
        parley_describe_units((iptr)puVar3);
        break;
      case 0xc:
        iVar5 = label_string(*(i32 *)(label_string_ids + 0xccc));
        str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
        crt_strcat(&parley_description,&parley_desc_give_war_crlf_str);
        parley_describe_war_targets((iptr)puVar3);
        break;
      case 0xd:
        iVar5 = label_string(*(i32 *)(label_string_ids + 0xcc8));
        str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
        crt_strcat(&parley_description,&parley_desc_give_maps_crlf_str);
        parley_describe_maps(*(i32 *)(iVar2 + 0x28),0);
        break;
      case 0x11:
        iVar5 = label_string(*(i32 *)(label_string_ids + 0xcc4));
        str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
        crt_strcat(&parley_description,&parley_desc_give_cities_crlf_str);
        parley_describe_cities((iptr)puVar3);
      }
      crt_strcat(&parley_description,&parley_desc_barter_sep_crlf_str);
      switch(*piVar2) {
      case 5:
      case 6:
        iVar5 = label_string(*(i32 *)(label_string_ids + 0xd20));
        str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
        crt_strcat(&parley_description,&parley_exch_for_treaty_crlf_str);
        parley_describe_treaty(this,*(i32 *)(param_1 + 0x28),1);
        break;
      case 8:
        iVar5 = label_string(*(i32 *)(label_string_ids + 0xcd0));
        str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
        crt_strcat(&parley_description,&parley_desc_want_adv_crlf_str);
        parley_describe_advances((iptr)piVar2);
        break;
      case 9:
        iVar5 = label_string(*(i32 *)(label_string_ids + 0xcd4));
        str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
        crt_strcat(&parley_description,&parley_desc_want_gold_crlf_str);
        str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),ADDR(0x62e94c, ((u8 *)&g.d_0062e94c)));
        parley_describe_gold(*(i32 *)(param_1 + 0x28));
        break;
      case 10:
        iVar5 = label_string(*(i32 *)(label_string_ids + 0xcd8));
        str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
        crt_strcat(&parley_description,&parley_desc_want_units_crlf_str);
        parley_describe_units((iptr)piVar2);
        break;
      case 0xc:
        iVar5 = label_string(*(i32 *)(label_string_ids + 0xce4));
        str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
        crt_strcat(&parley_description,&parley_exch_for_war_targets_crlf_str);
        parley_describe_war_targets((iptr)piVar2);
        break;
      case 0xd:
        iVar5 = label_string(*(i32 *)(label_string_ids + 0xce0));
        str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
        crt_strcat(&parley_description,&parley_exch_for_maps_crlf_str);
        parley_describe_maps(*(i32 *)(param_1 + 0x28),1);
        break;
      case 0x11:
        iVar5 = label_string(*(i32 *)(label_string_ids + 0xcdc));
        str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
        crt_strcat(&parley_description,&parley_exch_for_cities_crlf_str);
        parley_describe_cities((iptr)piVar2);
      }
      break;
    case 0xf:
      iVar5 = label_string(*(i32 *)(label_string_ids + 0xcac));
      str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
      str_append_space(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)));
      if (*piVar2 == 0xc) {
        iVar5 = label_string(*(i32 *)(label_string_ids + 0xd18));
        str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
      }
      else if ((*piVar2 == 5) || (*piVar2 == 6)) {
        iVar5 = label_string(*(i32 *)(label_string_ids + 0xd14));
        str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
      }
      else {
        iVar5 = label_string(*(i32 *)(label_string_ids + 0xcb0));
        str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar5);
      }
      crt_strcat(&parley_description,&parley_desc_threat_crlf_str);
      switch(*piVar2) {
      case 5:
      case 6:
        parley_describe_treaty(this,*(i32 *)(param_1 + 0x28),1);
        break;
      case 8:
        parley_describe_advances((iptr)piVar2);
        break;
      case 9:
        parley_describe_gold(*(i32 *)(param_1 + 0x28));
        break;
      case 10:
        parley_describe_units((iptr)piVar2);
        break;
      case 0xc:
        parley_describe_war_targets((iptr)piVar2);
        break;
      case 0xd:
        parley_describe_maps(*(i32 *)(param_1 + 0x28),1);
        break;
      case 0x11:
        parley_describe_cities((iptr)piVar2);
      }
    }
    sVar4 = _strlen(&parley_description);
    if (0x7ff < sVar4) {
      err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x62e998, ((u8 *)&g.d_0062e998)),ADDR(0x62e96c, ((u8 *)&g.d_0062e96c)),0x1f1);
    }
  }
  return;
}

/* 004dcafa auto */
#define local_10 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_8 (*(int * *)(frame_ + FRAME_OFF(8)))
void __cdecl parley_describe_advances(iptr param_1)

{
  int iVar1;
  iptr iVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = *(int *)(param_1 + 8);
  local_8 = (int *)(param_1 + 0xc);
  for (local_10 = 0; local_10 < iVar1; local_10++) {
    iVar2 = label_string(advances[*local_8].name);
    str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar2);
    if (1 < iVar1) {
      if (local_10 < iVar1 - 2) {
        crt_strcat(&parley_description,&parley_advances_comma_str);
      }
      else if (iVar1 - 2 == local_10) {
        str_append_space(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)));
        iVar2 = label_string(*(i32 *)(label_string_ids + 0xce8));
        str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar2);
        str_append_space(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)));
      }
      else {
        crt_strcat(&parley_description,&parley_advances_period_str);
      }
    }
    local_8++;
  }
  crt_strcat(&parley_description,&parley_advances_crlf_str);
  return;
}
#undef local_10
#undef local_8

/* 004dcc0c auto */
#define local_14 (*(char (*)[16])(frame_ + FRAME_OFF(4)))
void __cdecl parley_describe_gold(int param_1)

{
  i32 uVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  __itoa(param_1,local_14,10);
  crt_strcat(&parley_description,local_14);
  str_append_space(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)));
  uVar1 = label_string(*(i32 *)(label_string_ids + 0xcec));
  crt_strcat(&parley_description,uVar1);
  crt_strcat(&parley_description,&parley_gold_crlf_str);
  return;
}
#undef local_14

/* 004dcc83 auto */
#define aiStack_120 (*(int (*)[62])(frame_ + FRAME_OFF(0)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(248)))
#define local_24 (*(iptr *)(frame_ + FRAME_OFF(252)))
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(256)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(260)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(264)))
#define local_14 (*(char (*)[16])(frame_ + FRAME_OFF(268)))
void __cdecl parley_describe_units(iptr param_1)

{
  iptr unit;
  iptr iVar2;
  i8 frame_[FRAME_OFF(288)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (unit_type = 0; unit_type < 0x3e; unit_type++) {
    aiStack_120[unit_type] = 0;
  }
  local_18 = *(int *)(param_1 + 8);
  local_24 = param_1 + 0xc;
  local_1c = 0;
  for (unit_type = 0; unit_type < local_18; unit_type++) {
    unit = parley_find_unit_by_id
                      ((WindowObjectView *)&parley_wnd,*(i32 *)(local_24 + unit_type * 4));
    if (-1 < unit) {
      if (aiStack_120[units[unit].type] == 0) {
        local_1c++;
      }
      aiStack_120[units[unit].type] = aiStack_120[units[unit].type] + 1;
    }
  }
  local_28 = 0;
  for (unit_type = 0; unit_type < 0x3e; unit_type++) {
    if (aiStack_120[unit_type] != 0) {
      str_append_string_id(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),unit_types[unit_type].name);
      crt_strcat(&parley_description,&parley_units_open_paren_str);
      __itoa(aiStack_120[unit_type],local_14,10);
      crt_strcat(&parley_description,local_14);
      crt_strcat(&parley_description,&parley_units_close_paren_str);
      if (1 < local_18) {
        if (local_28 < local_1c - 2) {
          crt_strcat(&parley_description,&parley_units_comma_str);
        }
        else if (local_1c - 2 == local_28) {
          str_append_space(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)));
          iVar2 = label_string(*(i32 *)(label_string_ids + 0xce8));
          str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar2);
          str_append_space(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)));
        }
        else {
          crt_strcat(&parley_description,&parley_units_period_str);
        }
      }
      local_28++;
    }
  }
  crt_strcat(&parley_description,&parley_units_crlf_str);
  return;
}
#undef aiStack_120
#undef local_28
#undef local_24
#undef unit_type
#undef local_1c
#undef local_18
#undef local_14

/* 004dcea5 auto */
#define local_1c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_14 (*(char (*)[16])(frame_ + FRAME_OFF(12)))
void __cdecl parley_describe_cities(iptr param_1)

{
  int iVar1;
  int city;
  iptr iVar3;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = *(int *)(param_1 + 8);
  for (local_1c = 0; local_1c < iVar1; local_1c++) {
    city = parley_find_city_by_id
                      ((WindowObjectView *)&parley_wnd,*(i32 *)(param_1 + 0xc + local_1c * 8));
    str_append(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),(iptr)&cities[city].name);
    crt_strcat(&parley_description,&parley_cities_open_paren_str);
    __itoa(*(int *)(param_1 + 0x10 + local_1c * 8),local_14,10);
    crt_strcat(&parley_description,local_14);
    crt_strcat(&parley_description,&parley_cities_close_paren_str);
    if (1 < iVar1) {
      if (local_1c < iVar1 - 2) {
        crt_strcat(&parley_description,&parley_cities_comma_str);
      }
      else if (iVar1 - 2 == local_1c) {
        str_append_space(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)));
        iVar3 = label_string(*(i32 *)(label_string_ids + 0xce8));
        str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar3);
        str_append_space(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)));
      }
      else {
        crt_strcat(&parley_description,&parley_cities_period_str);
      }
    }
  }
  crt_strcat(&parley_description,&parley_cities_crlf_str);
  return;
}
#undef local_1c
#undef local_14

/* 004dd016 auto */
void __cdecl parley_describe_maps(int param_1,int param_2)

{
  iptr iVar1;
  
  if (param_1 == 0) {
    if (param_2 == 0) {
      iVar1 = label_string(*(i32 *)(label_string_ids + 0xcf0));
      str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar1);
    }
    else {
      iVar1 = label_string(*(i32 *)(label_string_ids + 0xcf4));
      str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar1);
    }
  }
  else if (param_1 == 1) {
    if (param_2 == 0) {
      iVar1 = label_string(*(i32 *)(label_string_ids + 0xcf8));
      str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar1);
    }
    else {
      iVar1 = label_string(*(i32 *)(label_string_ids + 0xcfc));
      str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar1);
    }
  }
  else if (param_1 == 2) {
    if (param_2 == 0) {
      iVar1 = label_string(*(i32 *)(label_string_ids + 0xd00));
      str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar1);
    }
    else {
      iVar1 = label_string(*(i32 *)(label_string_ids + 0xd04));
      str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar1);
    }
  }
  crt_strcat(&parley_description,&parley_maps_crlf_str);
  return;
}

/* 004dd176 auto */
#define local_10 (*(iptr * *)(frame_ + FRAME_OFF(0)))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
void __cdecl parley_describe_war_targets(iptr param_1)

{
  int iVar1;
  iptr iVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = *(int *)(param_1 + 8);
  local_10 = (iptr *)(param_1 + 0xc);
  for (local_c = 0; local_c < iVar1; local_c++) {
    iVar2 = civ_name_plural(*local_10);
    str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar2);
    if (1 < iVar1) {
      if (local_c < iVar1 - 2) {
        crt_strcat(&parley_description,&parley_war_targets_comma_str);
      }
      else if (iVar1 - 2 == local_c) {
        str_append_space(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)));
        iVar2 = label_string(*(i32 *)(label_string_ids + 0xce8));
        str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar2);
        str_append_space(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)));
      }
      else {
        crt_strcat(&parley_description,&parley_war_targets_period_str);
      }
    }
    local_10++;
  }
  crt_strcat(&parley_description,&parley_war_targets_crlf_str);
  return;
}
#undef local_10
#undef local_c

/* 004dd285 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define net_send_sequence (*(iptr *)((u8 *)&g.d_00628468))
void __cdecl parley_execute_transaction(iptr param_1)

{
  i32 *puVar1;
  iptr iVar4;
  i32 *puVar2;
  iptr civ;
  iptr civ2;
  
  if (param_1 != 0) {
    dbg_logf(ADDR(0x62ea04, ((u8 *)&g.d_0062ea04)),net_send_sequence);
    civ = *(iptr *)(param_1 + 0x14);
    civ2 = *(iptr *)(param_1 + 0x18);
    puVar1 = (i32 *)(param_1 + 0x20);
    iVar4 = *(int *)(param_1 + 0x24) + param_1;
    puVar2 = (i32 *)(iVar4 + 0x20);
    switch(*(i32 *)(param_1 + 0x10)) {
    case 6:
      parley_apply_treaty(*(i32 *)(param_1 + 0x28),civ,civ2);
      break;
    case 7:
      parley_transfer_advances(civ2,civ,(iptr)puVar1);
      break;
    case 8:
      parley_transfer_gold(civ2,civ,*(i32 *)(param_1 + 0x28));
      break;
    case 9:
      parley_transfer_units(civ2,(iptr)puVar1);
      break;
    case 10:
      parley_transfer_cities(civ2,(iptr)puVar1);
      break;
    case 0xb:
      parley_give_maps(civ2,civ,*(i32 *)(param_1 + 0x28));
      break;
    case 0xc:
      parley_apply_war_pact(civ,(iptr)puVar1);
      parley_apply_war_pact(civ2,(iptr)puVar1);
      break;
    case 0xd:
      parley_give_maps(civ,civ2,*(i32 *)(param_1 + 0x28));
      parley_give_maps(civ2,civ,*(i32 *)(param_1 + 0x28));
      break;
    case 0xe:
      switch(*puVar2) {
      case 5:
      case 6:
        parley_apply_treaty(*(i32 *)(iVar4 + 0x28),civ,civ2);
        break;
      case 8:
        parley_transfer_advances(civ2,civ,(iptr)puVar2);
        break;
      case 9:
        parley_transfer_gold(civ2,civ,*(i32 *)(iVar4 + 0x28));
        break;
      case 10:
        parley_transfer_units(civ2,(iptr)puVar2);
        break;
      case 0xc:
        parley_apply_war_pact(civ,(iptr)puVar2);
        break;
      case 0xd:
        parley_give_maps(civ2,civ,*(i32 *)(iVar4 + 0x28));
        break;
      case 0x11:
        parley_transfer_cities(civ2,(iptr)puVar2);
      }
      switch(*puVar1) {
      case 5:
      case 6:
        parley_apply_treaty(*(i32 *)(param_1 + 0x28),civ,civ2);
        break;
      case 8:
        parley_transfer_advances(civ,civ2,(iptr)puVar1);
        break;
      case 9:
        parley_transfer_gold(civ,civ2,*(i32 *)(param_1 + 0x28));
        break;
      case 10:
        parley_transfer_units(civ,(iptr)puVar1);
        break;
      case 0xc:
        parley_apply_war_pact(civ2,(iptr)puVar1);
        break;
      case 0xd:
        parley_give_maps(civ,civ2,*(i32 *)(param_1 + 0x28));
        break;
      case 0x11:
        parley_transfer_cities(civ,(iptr)puVar1);
      }
      break;
    case 0xf:
      switch(*puVar1) {
      case 5:
      case 6:
        parley_apply_treaty(*(i32 *)(param_1 + 0x28),civ,civ2);
        break;
      case 8:
        parley_transfer_advances(civ,civ2,(iptr)puVar1);
        break;
      case 9:
        parley_transfer_gold(civ,civ2,*(i32 *)(param_1 + 0x28));
        break;
      case 10:
        parley_transfer_units(civ,(iptr)puVar1);
        break;
      case 0xc:
        parley_apply_war_pact(civ2,(iptr)puVar1);
        break;
      case 0xd:
        parley_give_maps(civ,civ2,*(i32 *)(param_1 + 0x28));
        break;
      case 0x11:
        parley_transfer_cities(civ,(iptr)puVar1);
      }
    }
    net_send_state_diff(0xff,2,0,0,0);
    if (human_civ == civ2) {
      status_redraw(1);
    }
    else {
      net_send_message(0x79,*(i32 *)
                               (&net_player_slots + *(int *)(&net_civ_slots + civ2 * 4) * 0x54),0,0,0,0,
                         0,0,0,0);
    }
    if (human_civ == civ) {
      status_redraw(1);
    }
    else {
      net_send_message(0x79,*(i32 *)
                               (&net_player_slots + *(int *)(&net_civ_slots + civ * 4) * 0x54),0,0,0,0,
                         0,0,0,0);
    }
    if ((*(int *)(&civ_unit_counts + civ2 * 4) == 0) && (civs[civ2].num_cities == 0)) {
      civ_check_destroyed(civ2,civ);
    }
    if ((*(int *)(&civ_unit_counts + civ * 4) == 0) && (civs[civ].num_cities == 0)) {
      civ_check_destroyed(civ,civ2);
    }
    dbg_logf(ADDR(0x62ea30, ((u8 *)&g.d_0062ea30)),net_send_sequence);
  }
  return;
}
#undef human_civ
#undef net_send_sequence

/* 004dd8ad auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define unit (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_2c (*(byte *)(frame_ + FRAME_OFF(12)))
#define local_24 (*(byte *)(frame_ + FRAME_OFF(20)))
#define city (*(iptr *)(frame_ + FRAME_OFF(24)))
#define y2 (*(uint *)(frame_ + FRAME_OFF(28)))
#define x2 (*(uint *)(frame_ + FRAME_OFF(36)))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(44)))
void __cdecl parley_give_maps(iptr param_1,iptr civ,int param_3)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  iptr iVar5;
  byte *pbVar5;
  byte *pbVar6;
  iptr iVar7;
  iptr iVar8;
  int y;
  iptr x;
  int iVar12;
  i32 uVar13;
  i32 uVar14;
  iptr iVar10;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  uVar3 = 1 << ((byte)param_1 & 0x1f);
  uVar4 = 1 << ((byte)civ & 0x1f);
  y2 = 0;
  x2 = 0;
  net_batch_begin();
  for (local_c = 0; local_c < map.area; local_c++) {
    iVar5 = tile_at(x2,y2);
    pbVar5 = (byte *)known_at(x2,y2,param_1);
    pbVar6 = (byte *)known_at(x2,y2,civ);
    if ((uVar4 & *(byte *)(iVar5 + 4)) != 0) {
      if ((uVar3 & *(byte *)(iVar5 + 4)) == 0) {
        known_set(x2,y2,0,param_1,0,1);
        tile_set_visible(x2,y2,uVar3,1,1);
      }
      if (param_3 == 0) {
        if (((*pbVar5 & 0x80) == 0) || ((*pbVar6 & 0x80) == 0)) {
          bVar2 = *pbVar6;
          bVar1 = *pbVar5;
          iVar7 = tile_at(x2,y2);
          local_2c = (bVar2 | bVar1) & *(byte *)(iVar7 + 1) & 0x80;
        }
        else {
          local_2c = 0x80;
        }
        uVar14 = 1;
        uVar13 = 0;
        iVar10 = param_1;
        pbVar5 = (byte *)known_at(x2,y2,param_1);
        known_set(x2,y2,*pbVar5 & 0xffffff7f | (uint)local_2c,iVar10,uVar13,uVar14);
        uVar14 = 1;
        uVar13 = 1;
        x = param_1;
        iVar8 = tile_at(x2,y2);
        bVar2 = *(byte *)(iVar8 + 1);
        pbVar5 = (byte *)known_at(x2,y2,civ);
        known_set(x2,y2,(uint)(bVar2 & *pbVar5),x,uVar13,uVar14);
      }
    }
    x2 += 2;
    if ((int)map.width <= (int)x2) {
      y2++;
      x2 = y2 & 1;
    }
  }
  local_24 = (byte)uVar3;
  if (param_3 == 0) {
    for (unit = 0; unit < game.num_units; unit++) {
      if ((units[unit].id != 0) &&
         (((uVar4 & units[unit].visibility) != 0 || (units[unit].owner == civ)))) {
        units[unit].visibility = units[unit].visibility | local_24;
        y = tile_at((int)units[unit].x,(int)units[unit].y);
        if (((uVar3 & *(byte *)(y + 4)) == 0) || ((uVar4 & *(byte *)(y + 4)) == 0)) {
          for (local_c = 0; local_c < 0x15; local_c++) {
            x = map_wrap_x((int)(char)(&city_tile_dx_table)[local_c] + x2);
            y = (int)(char)(&city_tile_dy_table)[local_c] + y2;
            iVar12 = map_in_bounds(x,y);
            if (iVar12 != 0) {
              tile_set_visible(x,y,uVar3,1,1);
              tile_set_visible(x,y,uVar4,1,1);
            }
          }
        }
      }
    }
  }
  if ((param_3 == 0) || (param_3 == 1)) {
    for (city = 0; city < game.num_cities; city++) {
      if ((cities[city].id != 0) &&
         (((uVar4 & (int)(char)cities[city].known_to) != 0 ||
          (cities[city].owner == civ)))) {
        if (cities[city].owner == civ) {
          *(i8 *)&cities[city].revealed_size[param_1] = cities[city].size;
        }
        else {
          *(i8 *)&cities[city].revealed_size[param_1] =
               *(i8 *)&cities[city].revealed_size[civ];
        }
        cities[city].known_to = cities[city].known_to | local_24;
        y = tile_at((int)cities[city].x,(int)cities[city].y);
        if (((uVar3 & *(byte *)(y + 4)) == 0) || ((uVar4 & *(byte *)(y + 4)) == 0)) {
          for (local_c = 0; local_c < 0x15; local_c++) {
            x = map_wrap_x((int)(char)(&city_tile_dx_table)[local_c] + x2);
            y = (int)(char)(&city_tile_dy_table)[local_c] + y2;
            iVar12 = map_in_bounds(x,y);
            if (iVar12 != 0) {
              tile_set_visible(x,y,uVar3,1,1);
              tile_set_visible(x,y,uVar4,1,1);
            }
          }
        }
      }
    }
  }
  net_batch_flush();
  net_send_state_diff(0xff,2,0,0,0);
  if (human_civ == param_1) {
    map_redraw_all_views(human_civ,1);
  }
  else {
    net_send_message(0x74,*(i32 *)
                             (&net_player_slots + *(int *)(&net_civ_slots + param_1 * 4) * 0x54),0,0,0,0,
                       0,0,0,0);
  }
  return;
}
#undef human_civ
#undef unit
#undef local_2c
#undef local_24
#undef city
#undef y2
#undef x2
#undef local_c

/* 004dde9e auto */
#define local_10 (*(iptr * *)(frame_ + FRAME_OFF(0)))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
void __cdecl parley_apply_war_pact(iptr param_1,iptr param_2)

{
  int iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = *(int *)(param_2 + 8);
  local_10 = (iptr *)(param_2 + 0xc);
  for (local_c = 0; local_c < iVar1; local_c++) {
    diplo_set_treaty_flags(param_1,*local_10,0x2000);
    local_10++;
  }
  return;
}
#undef local_10
#undef local_c

/* 004ddf04 auto */
void __cdecl parley_transfer_gold(iptr civ2,iptr civ,i32 param_3)

{
  int iVar1;
  
  if (civs[civ].gold < param_3) {
    param_3 = civs[civ].gold;
  }
  civs[civ].gold -= param_3;
  civs[civ2].gold += param_3;
  iVar1 = diplo_gold_attitude_value(param_3);
  civ_adjust_attitude(civ2,civ,-((iVar1 * 3) / 2));
  return;
}

/* 004ddfb2 auto */
#define local_10 (*(iptr * *)(frame_ + FRAME_OFF(0)))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
void __cdecl parley_transfer_advances(iptr civ,iptr civ2,iptr param_3)

{
  int iVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = *(int *)(param_3 + 8);
  local_10 = (iptr *)(param_3 + 0xc);
  for (local_c = 0; local_c < iVar1; local_c++) {
    iVar2 = civ_has_advance(civ2,*local_10);
    if (iVar2 != 0) {
      iVar2 = civ_has_advance(civ,*local_10);
      if (iVar2 == 0) {
        civ_give_advance(civ,*local_10,civ2,1,0);
      }
    }
    local_10++;
  }
  return;
}
#undef local_10
#undef local_c

/* 004de049 auto */
#define local_14 (*(i32 * *)(frame_ + FRAME_OFF(4)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
void __cdecl parley_transfer_cities(iptr civ,iptr param_2)

{
  int iVar1;
  iptr city;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = *(int *)(param_2 + 8);
  local_14 = (i32 *)(param_2 + 0xc);
  for (local_c = 0; local_c < iVar1; local_c++) {
    city = parley_find_city_by_id((WindowObjectView *)&parley_wnd,*local_14);
    if ((-1 < city) && (cities[city].id != 0)) {
      parley_cede_city(city,civ);
    }
    local_14 += 2;
  }
  return;
}
#undef local_14
#undef local_c

/* 004de0e2 auto */
#define scenario_events_loaded (*(int *)((u8 *)&g.d_00627670))
#define improvement (*(iptr *)(frame_ + FRAME_OFF(4)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(12)))
#define unit_type (*(iptr *)(frame_ + FRAME_OFF(16)))
#define local_10 (*(iptr *)(frame_ + FRAME_OFF(40)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(48)))
void __cdecl parley_cede_city(uptr city,iptr civ)

{
  char *pcVar1;
  char civ3;
  iptr civ2;
  int x;
  int y;
  iptr x2;
  iptr y3;
  iptr iVar8;
  int y2;
  iptr iVar9;
  int iVar11;
  uptr uVar12;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
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
  for (local_10 = 0; local_10 < 0x15; local_10++) {
    x2 = map_wrap_x((char)(&city_tile_dx_table)[local_10] + x);
    y3 = (char)(&city_tile_dy_table)[local_10] + y;
    iVar8 = map_in_bounds(x2,y3);
    if (iVar8 != 0) {
      tile_set_radius_civ(x2,y3,civ,1);
      tile_set_visible(x2,y3,1 << ((byte)civ & 0x1f),1,1);
    }
  }
  cities[city].owner = (byte)civ;
  city_reveal_to_civ(city,civ2);
  if (scenario_events_loaded != 0) {
    events_check_city_taken
              ((ScenarioEvents *)&scenario_events,(iptr)&cities[city].name,civ,civ2);
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
        pcVar1 = (char *)(units[unit].type + ADDR(0x64c778, ((u8 *)&civs + 216)) + civ * 0x594);
        *pcVar1 = *pcVar1 + 1;
        pcVar1 = (char *)(units[unit].type + ADDR(0x64c778, ((u8 *)&civs + 216)) + civ2 * 0x594);
        *pcVar1 = *pcVar1 - 1;
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
        *(int *)(&civ_unit_counts + civ * 4) = *(int *)(&civ_unit_counts + civ * 4) + 1;
        if ((civs[civ2].num_military_units != 0) &&
           ((char)unit_types[units[unit].type].role < 5)) {
          civs[civ2].num_military_units--;
        }
        if (*(int *)(&civ_unit_counts + civ2 * 4) != 0) {
          *(int *)(&civ_unit_counts + civ2 * 4) = *(int *)(&civ_unit_counts + civ2 * 4) - 1;
        }
      }
    }
  }
  if ((cities[city].building < '\0') ||
     (y2 = civ_can_build_unit(civ,city,(int)cities[city].building), y2 != 0)) {
    if (-1 < cities[city].building) goto LAB_004de76b;
    if (cities[city].building < 1) {
      improvement = ~(int)cities[city].building + 1;
    }
    else {
      improvement = (iptr)cities[city].building;
    }
    y2 = city_can_build_improvement(civ,city,improvement);
    if (y2 != 0) goto LAB_004de76b;
  }
  cities[city].building = '\0';
  for (unit_type = 0x3e; -1 < unit_type; unit_type--) {
    if ((unit_types[unit_type].role == 1) &&
       (y2 = civ_can_build_unit(civ,city,unit_type), y2 != 0)) {
      local_8 = ((int)(char)unit_types[unit_type].defense << 3) /
                (int)(char)unit_types[unit_type].cost;
      if ((unit_types[unit_type].flags & 0x400) != 0) {
        local_8++;
      }
      if (0 < local_8) {
        cities[city].building = (i8)unit_type;
      }
      break;
    }
  }
LAB_004de76b:
  map_redraw_neighbors_all_views((int)cities[city].x,(int)cities[city].y);
  net_send_state_diff(0xff,2,0,0,0);
  net_send_message(0x75,0xff,(int)cities[city].x,(int)cities[city].y,0,0,0,0,0,0);
  y2 = tile_at(x,y);
  if ((1 << ((byte)civ & 0x1f) & (uint)*(byte *)(y2 + 4)) == 0) {
    tile_set_visible(x,y,1 << ((byte)civ & 0x1f),1,1);
    map_redraw_tile_all_views(x,y);
  }
  for (local_10 = 0; local_10 < 8; local_10++) {
    x2 = map_wrap_x((char)(&dir_dx_table)[local_10] + x);
    y2 = (char)(&dir_dy_table)[local_10] + y;
    iVar9 = map_in_bounds(x2,y2);
    if ((iVar9 != 0) &&
       (iVar11 = tile_at(x2,y2),
       (1 << ((byte)civ & 0x1f) & (uint)*(byte *)(iVar11 + 4)) == 0)) {
      tile_set_visible(x2,y2,1 << ((byte)civ & 0x1f),1,1);
      map_redraw_tile_all_views(x2,y2);
    }
  }
  net_batch_flush();
  net_send_message(0x75,0xff,x,y,0,0,0,0,0,0);
  cities[city].founder = civ3;
  cities[city].turns_captured = (u8)game.turn;
  uVar12 = wonder_get_city(0xe);
  if (uVar12 == city) {
    civ_leonardo_upgrade(civ);
  }
  return;
}
#undef scenario_events_loaded
#undef improvement
#undef unit
#undef unit_type
#undef local_10
#undef local_8

/* 004de990 auto */
#define x3 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(4)))
#define city (*(iptr *)(frame_ + FRAME_OFF(8)))
#define unit2 (*(iptr *)(frame_ + FRAME_OFF(12)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(16)))
#define y2 (*(iptr *)(frame_ + FRAME_OFF(20)))
#define x2 (*(iptr *)(frame_ + FRAME_OFF(24)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(28)))
#define civ2 (*(iptr *)(frame_ + FRAME_OFF(32)))
#define y3 (*(iptr *)(frame_ + FRAME_OFF(36)))
#define local_8 (*(i32 * *)(frame_ + FRAME_OFF(40)))
void __cdecl parley_transfer_units(iptr civ,iptr param_2)

{
  char *pcVar1;
  i32 uVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(48)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_14 = *(int *)(param_2 + 8);
  local_8 = (i32 *)(param_2 + 0xc);
  for (local_20 = 0; local_20 < local_14; local_20++) {
    uVar2 = *local_8;
    local_8++;
    unit = parley_find_unit_by_id((WindowObjectView *)&parley_wnd,uVar2);
    if ((-1 < unit) && (civ2 = (iptr)units[unit].owner, civ != civ2)) {
      if ((unit_types[units[unit].type].domain == 2) &&
         (iVar3 = unit_stack_sum(unit,2), 1 < iVar3)) {
        while (iVar3 = unit_stack_sum(unit,2), 1 < iVar3) {
          unit2 = unit_stack_first(unit);
          if (unit2 == unit) {
            unit2 = unit_next_in_stack(unit2);
          }
          iVar3 = parley_find_unit_drop_tile(unit2,(iptr)&x3,(iptr)&y3,
                                     (int)units[unit2].owner,1);
          if (iVar3 == 0) {
            unit_delete_with_cargo(unit2,1);
          }
          else {
            unit_relocate(unit2,x3,y3,1);
          }
        }
      }
      iVar3 = parley_find_unit_drop_tile(unit,(iptr)&x2,(iptr)&y2,civ,0);
      if (iVar3 != 0) {
        pcVar1 = (char *)(units[unit].type + ADDR(0x64c778, ((u8 *)&civs + 216)) + civ * 0x594);
        *pcVar1 = *pcVar1 + 1;
        pcVar1 = (char *)(units[unit].type + ADDR(0x64c778, ((u8 *)&civs + 216)) + civ2 * 0x594);
        *pcVar1 = *pcVar1 - 1;
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
        *(int *)(&civ_unit_counts + civ * 4) = *(int *)(&civ_unit_counts + civ * 4) + 1;
        if ((civs[civ2].num_military_units != 0) &&
           ((char)unit_types[units[unit].type].role < 5)) {
          civs[civ2].num_military_units--;
        }
        if (*(int *)(&civ_unit_counts + civ2 * 4) != 0) {
          *(int *)(&civ_unit_counts + civ2 * 4) = *(int *)(&civ_unit_counts + civ2 * 4) - 1;
        }
        unit_relocate(unit,x2,y2,1);
        unit_reveal_surroundings(unit,0);
      }
    }
  }
  XD_FlushSendBuffer(5000);
  return;
}
#undef x3
#undef unit
#undef city
#undef unit2
#undef local_20
#undef y2
#undef x2
#undef local_14
#undef civ2
#undef y3
#undef local_8

/* 004ded07 auto */
#define local_c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
i32 __cdecl parley_find_unit_drop_tile(iptr unit,iptr x,iptr y,iptr param_4,int param_5)

{
  iptr x2;
  int y2;
  int iVar3;
  i32 uVar4;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  *(int *)x = (int)units[unit].x;
  x2 = *(iptr *)x;
  *(int *)y = (int)units[unit].y;
  y2 = *(int *)y;
  local_8 = 1;
  if (((param_5 != 0) || (iVar3 = tile_city_owner(x2,y2), iVar3 != -1)) ||
     (iVar3 = unit_stack_sum(unit,2), 1 < iVar3)) {
    local_8 = 0;
    for (local_c = 0; local_c < 0x2d; local_c++) {
      uVar4 = map_wrap_x((char)(&city_tile_dx_table)[local_c] + x2);
      *(i32 *)x = uVar4;
      *(int *)y = (char)(&city_tile_dy_table)[local_c] + y2;
      if ((((((param_5 == 0) || (*(int *)x != x2)) || (*(int *)y != y2)) &&
           (iVar3 = map_in_bounds(*(iptr *)x,*(iptr *)y), iVar3 != 0)) &&
          (((iVar3 = tile_city_owner(*(iptr *)x,*(i32 *)y), iVar3 == param_4 ||
            (iVar3 = tile_unit_owner(*(i32 *)x,*(i32 *)y),
            iVar3 == param_4)) ||
           ((iVar3 = tile_city_owner(*(iptr *)x,*(i32 *)y), iVar3 == -1 &&
            (iVar3 = tile_unit_owner(*(i32 *)x,*(i32 *)y), iVar3 == -1))))
          )) && ((((unit_types[units[unit].type].domain == '\0' &&
                   (iVar3 = tile_is_ocean(*(i32 *)x,*(i32 *)y), iVar3 == 0
                   )) || ((unit_types[units[unit].type].domain == 2 &&
                          (iVar3 = tile_is_ocean(*(i32 *)x,*(i32 *)y),
                          iVar3 != 0)))) || (unit_types[units[unit].type].domain == 1)))) {
        return 1;
      }
    }
  }
  return local_8;
}
#undef local_c
#undef local_8

/* 004def54 auto */
void __thiscall parley_describe_treaty(WindowObjectView *this,int param_1,int param_2)

{
  iptr iVar1;
  
  if (param_2 == 0) {
    switch(param_1) {
    case 0:
      iVar1 = label_string(*(i32 *)(label_string_ids + 0xc74));
      str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar1);
      break;
    case 1:
      iVar1 = label_string(*(i32 *)(label_string_ids + 0xc78));
      str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar1);
      break;
    case 2:
      iVar1 = label_string(*(i32 *)(label_string_ids + 0xc7c));
      str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar1);
      break;
    case 3:
      iVar1 = label_string(*(i32 *)(label_string_ids + 0xc80));
      str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar1);
    }
  }
  else if (param_2 == 1) {
    if (param_1 == 0) {
      iVar1 = label_string(*(i32 *)(label_string_ids + 0xbcc));
      str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar1);
    }
    else if (param_1 == 1) {
      iVar1 = label_string(*(i32 *)(label_string_ids + 0xbd0));
      str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar1);
    }
    else if (param_1 == 2) {
      iVar1 = label_string(*(i32 *)(label_string_ids + 0xbd4));
      str_concat(ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),iVar1);
    }
  }
  crt_strcat(&parley_description,&parley_treaty_crlf_str);
  return;
}

/* 004df10f auto */
void __cdecl parley_apply_treaty(i32 param_1,iptr civ,iptr param_3)

{
  switch(param_1) {
  case 0:
    diplo_set_treaty_flags(civ,param_3,2);
    break;
  case 1:
    diplo_set_treaty_flags(civ,param_3,4);
    break;
  case 2:
    diplo_set_treaty_flags(civ,param_3,8);
    break;
  case 3:
    if ((*(byte *)&civs[civ].treaties[param_3] & 2) != 0) {
      diplo_clear_treaty_flags(civ,param_3,2);
    }
    if ((*(byte *)&civs[civ].treaties[param_3] & 4) != 0) {
      diplo_clear_treaty_flags(civ,param_3,4);
    }
    if ((*(byte *)&civs[civ].treaties[param_3] & 8) != 0) {
      diplo_clear_treaty_flags(civ,param_3,8);
    }
  }
  return;
}

/* 00511880 auto */
#define local_14 (*(void * *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(uint *)(frame_ + FRAME_OFF(8)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(void * *)(frame_ + FRAME_OFF(16)))
void __cdecl
net_send_text_args(iptr param_1,i32 param_2,int param_3,int param_4,iptr param_5,iptr param_6)

{
  size_t sVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = (void *)0x0;
  local_10 = 0;
  if (2 < game.multiplayer) {
    if (param_3 != 0) {
      for (local_c = 0; local_c < param_3; local_c++) {
        sVar1 = _strlen(&text_string_args + local_c * 0x104);
        local_10 = local_10 + sVar1 + 1;
      }
    }
    if (param_4 != 0) {
      local_10 = param_4 * 4 + local_10;
    }
    if (local_10 != 0) {
      local_8 = operator_new(local_10);
      local_14 = local_8;
      if (param_3 != 0) {
        for (local_c = 0; local_c < param_3; local_c++) {
          crt_strcpy(local_14,&text_string_args + local_c * 0x104);
          sVar1 = _strlen(&text_string_args + local_c * 0x104);
          local_14 = (void *)((int)local_14 + sVar1 + 1);
        }
      }
      if (param_4 != 0) {
        for (local_c = 0; local_c < param_4; local_c++) {
          crt_memcpy(local_14,&text_number_args + local_c * 4,4);
          local_14 = (void *)((int)local_14 + 4);
        }
      }
    }
    net_send_message(0x6a,param_2,param_1,param_3,param_4,param_5,param_6,0,0,(iptr)local_8);
  }
  return;
}
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 00511a0e auto */
#define net_popup_queue_head (*(i32 * *)((u8 *)&g.d_00631130))
#define net_popup_queue_tail (*(i32 * *)((u8 *)&g.d_00631134))
void __cdecl
net_popup_queue_push(i32 param_1,i32 param_2,i32 param_3,i32 param_4,
            i32 param_5,i32 param_6,int param_7)

{
  i32 *puVar1;
  i32 *puVar2;
  
  puVar2 = operator_new(param_7 + 0x1c);
  *puVar2 = 0;
  puVar2[1] = param_1;
  puVar2[2] = param_2;
  puVar2[3] = param_3;
  puVar2[4] = param_4;
  puVar2[5] = param_5;
  puVar2[6] = param_7;
  if (param_7 != 0) {
    crt_memcpy(puVar2 + 7,param_6,param_7);
  }
  puVar1 = puVar2;
  if (net_popup_queue_head != (i32 *)0x0) {
    *net_popup_queue_tail = puVar2;
    puVar1 = net_popup_queue_head;
  }
  net_popup_queue_head = puVar1;
  net_popup_queue_tail = puVar2;
  return;
}
#undef net_popup_queue_head
#undef net_popup_queue_tail

/* 00511acf auto */
#define net_popup_queue_head (*(i32 * *)((u8 *)&g.d_00631130))
#define net_popup_queue_tail (*(i32 *)((u8 *)&g.d_00631134))
void __cdecl net_popup_queue_clear(void)

{
  i32 *puVar1;
  
  while (puVar1 = net_popup_queue_head, net_popup_queue_head != (i32 *)0x0) {
    net_popup_queue_head = (i32 *)*net_popup_queue_head;
    operator_delete(puVar1);
  }
  net_popup_queue_tail = 0;
  return;
}
#undef net_popup_queue_head
#undef net_popup_queue_tail

/* 00511b2d auto */
#define dialog_stack_top (*(int * *)((u8 *)&g.d_006ad678))
#define net_host_handoff_stage (*(char *)((u8 *)&g.d_006ad698))
#define nm_parley_cancel_count (*(int *)((u8 *)&g.d_006c91e4))
#define dialog_timeout_start_i32 (*(i32 *)((u8 *)&g.d_006cec80))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl net_popup_idle_autoclose(void)

{
  int iVar1;
  
  net_process_messages((NetSession *)&net_session,1,0);
  if (((net_host_handoff_stage == '\0') && (nm_parley_cancel_count == 0)) &&
     (iVar1 = timer_ticks(), iVar1 - dialog_timeout_start_i32 < 0x4b1)) {
    return;
  }
  dialog_stack_top[0xf] = dialog_stack_top[0xf] | 0x400;
  wnd_end_modal_loop((ModalMenuWindow *)(*dialog_stack_top + 0x48));
  dialog_timeout_start_i32 = timer_ticks();
  return;
}
#undef dialog_stack_top
#undef net_host_handoff_stage
#undef nm_parley_cancel_count
#undef dialog_timeout_start_i32

/* 00511ba2 auto */
#define dlg_pending_idle_callback (*(i8 * *)((u8 *)&g.d_00635a3c))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define mp_meeting_pending (*(i32 *)((u8 *)&g.d_00626a2c))
#define net_host_handoff_stage (*(char *)((u8 *)&g.d_006ad698))
#define net_popup_queue_head (*(int * *)((u8 *)&g.d_00631130))
#define net_popup_queue_tail (*(i32 *)((u8 *)&g.d_00631134))
#define nm_parley_cancel_count (*(int *)((u8 *)&g.d_006c91e4))
#define parley_other_civ (*(int *)((u8 *)&g.d_0067a8c0))
#define parley_reveal_city_prompt_open (*(i32 *)((u8 *)&g.d_0063113c))
#define parley_reveal_units_prompt_open (*(i32 *)((u8 *)&g.d_00631138))
#define net_popup_in_progress_i32 (*(i32 *)((u8 *)&g.d_006ad67c))
#define local_338 (*(i8 * *)(frame_ + FRAME_OFF(0)))
#define local_330 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_310 (*(int *)(frame_ + FRAME_OFF(40)))
#define local_308 (*(Dialog *)(frame_ + FRAME_OFF(48)))
#define local_14 (*(int * *)(frame_ + FRAME_OFF(804)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(808)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(812)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(816)))
/* WARNING: Removing unreachable block (ram,0x0051343e) */
/* WARNING: Removing unreachable block (ram,0x0051347e) */
/* WARNING: Removing unreachable block (ram,0x0051369c) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl net_popup_queue_show_next(void)

{
  int *piVar1;
  size_t sVar2;
  int iVar3;
  iptr iVar4;
  i8 frame_[FRAME_OFF(824)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  piVar1 = net_popup_queue_head;
  dialog_ctor(&local_308,0x4000);
  local_8 = 0;
  if (piVar1 != (int *)0x0) {
    net_popup_in_progress_i32 = 1;
    net_popup_queue_head = (int *)*piVar1;
    if (net_popup_queue_head == (int *)0x0) {
      net_popup_queue_tail = 0;
    }
    if ((piVar1[2] != 0) || (piVar1[3] != 0)) {
      local_14 = piVar1 + 7;
    }
    if (piVar1[2] != 0) {
      for (local_310 = 0; local_310 < piVar1[2]; local_310++) {
        crt_strcpy(&text_string_args + local_310 * 0x104,local_14);
        sVar2 = _strlen(&text_string_args + local_310 * 0x104);
        local_14 = (int *)((int)local_14 + sVar2 + 1);
      }
    }
    if (piVar1[3] != 0) {
      for (local_310 = 0; local_310 < piVar1[3]; local_310++) {
        crt_memcpy(&text_number_args + local_310 * 4,local_14,4);
        local_14++;
      }
    }
    dlg_pending_idle_callback = ((void *)ADDR(0x00403c74, turn_popup_timeout_idle));
    switch(piVar1[1]) {
    case 0:
      popup_game(ADDR(0x631140, ((u8 *)&g.d_00631140)));
      break;
    case 1:
      popup_game(ADDR(0x63114c, ((u8 *)&g.d_0063114c)));
      break;
    case 2:
      dlg_game_txt_with_unit(ADDR(0x631158, ((u8 *)&g.d_00631158)),piVar1[4]);
      break;
    case 3:
      popup_game_with_sprite(ADDR(0x631164, ((u8 *)&g.d_00631164)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      break;
    case 4:
      popup_game_with_sprite(ADDR(0x631174, ((u8 *)&g.d_00631174)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      break;
    case 5:
      historian_report_show();
      break;
    case 6:
      popup_game_with_sprite(ADDR(0x631180, ((u8 *)&g.d_00631180)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      break;
    case 7:
      popup_game_with_sprite(ADDR(0x631190, ((u8 *)&g.d_00631190)),ADDR(0x643af8, ((u8 *)&g.d_00643af8)),0);
      break;
    case 8:
      popup_game_with_sprite(ADDR(0x6311a0, ((u8 *)&g.d_006311a0)),ADDR(0x643af8, ((u8 *)&g.d_00643af8)),0);
      break;
    case 9:
      iVar4 = civ_leader_title(human_civ);
      text_set_string_arg(0,iVar4);
      iVar4 = civ_leader_name(human_civ);
      text_set_string_arg(1,iVar4);
      popup_game_with_sprite(ADDR(0x6311ac, ((u8 *)&g.d_006311ac)),ADDR(0x643af8, ((u8 *)&g.d_00643af8)),0);
      break;
    case 10:
      iVar4 = civ_leader_name(human_civ);
      text_set_string_arg(1,iVar4);
      popup_game_with_sprite(ADDR(0x6311b8, ((u8 *)&g.d_006311b8)),ADDR(0x643af8, ((u8 *)&g.d_00643af8)),0);
      break;
    case 0xb:
      popup_game(ADDR(0x6311c4, ((u8 *)&g.d_006311c4)));
      spaceship_wnd_run(-piVar1[4]);
      break;
    case 0xc:
      popup_game(ADDR(0x6311d0, ((u8 *)&g.d_006311d0)));
      break;
    case 0xd:
      popup_game(ADDR(0x6311e0, ((u8 *)&g.d_006311e0)));
      break;
    case 0xe:
      music_play_track(2,1);
      popup_game_with_sprite(ADDR(0x6311f0, ((u8 *)&g.d_006311f0)),(iptr)(&civ_portrait_sprites + piVar1[4] * 0x3c),0);
      break;
    case 0xf:
      snd_play_effect((-(uint)(piVar1[5] == 0) & 0x14) + 0x16,1,0,0);
      dlg_game_txt_with_unit(ADDR(0x6311fc, ((u8 *)&g.d_006311fc)),piVar1[4]);
      break;
    case 0x10:
      snd_play_effect((-(uint)(piVar1[5] == 0) & 0x14) + 0x16,1,0,0);
      dlg_game_txt_with_unit(ADDR(0x631204, ((u8 *)&g.d_00631204)),piVar1[4]);
      break;
    case 0x11:
      dlg_game_txt_with_unit_flags(ADDR(0x631210, ((u8 *)&g.d_00631210)),piVar1[4],piVar1[5]);
      break;
    case 0x12:
      dialog_load_game_text(&local_308,ADDR(0x631220, ((u8 *)&g.d_00631220)));
      dialog_add_sprite
                ((DialogOptionList *)&local_308,(iptr)(&improvement_icon_sprites + piVar1[4] * 0x3c),0,0);
      dialog_set_image_zoom((DialogWindowView *)&local_308,piVar1[5]);
      dlg_show_modal(&local_308,0);
      break;
    case 0x13:
      dialog_load_game_text(&local_308,ADDR(0x63122c, ((u8 *)&g.d_0063122c)));
      dialog_add_sprite
                ((DialogOptionList *)&local_308,(iptr)(&improvement_icon_sprites + piVar1[4] * 0x3c),0,0);
      dialog_set_image_zoom((DialogWindowView *)&local_308,piVar1[5]);
      dlg_show_modal(&local_308,0);
      break;
    case 0x14:
      dialog_load_game_text(&local_308,ADDR(0x63123c, ((u8 *)&g.d_0063123c)));
      dialog_add_sprite
                ((DialogOptionList *)&local_308,(iptr)(&improvement_icon_sprites + piVar1[4] * 0x3c),0,0);
      dialog_set_image_zoom((DialogWindowView *)&local_308,piVar1[5]);
      dlg_show_modal(&local_308,0);
      break;
    case 0x15:
      dlg_game_txt_with_unit(ADDR(0x63124c, ((u8 *)&g.d_0063124c)),piVar1[4]);
      break;
    case 0x16:
      popup_game(ADDR(0x631258, ((u8 *)&g.d_00631258)));
      break;
    case 0x17:
      iVar4 = popup_game_with_sprite(ADDR(0x631260, ((u8 *)&g.d_00631260)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      net_send_message(0x77,*(i32 *)
                               (&net_player_slots + *(int *)(&net_civ_slots + piVar1[4] * 4) * 0x54),
                         iVar4,0,0,0,0,0,0,0);
      break;
    case 0x18:
      popup_game_with_city(ADDR(0x63126c, ((u8 *)&g.d_0063126c)),piVar1[4]);
      break;
    case 0x19:
      dialog_load_game_text(&local_308,ADDR(0x631274, ((u8 *)&g.d_00631274)));
      dialog_add_sprite
                ((DialogOptionList *)&local_308,(iptr)(&improvement_icon_sprites + piVar1[4] * 0x3c),0,0);
      dialog_set_image_zoom((DialogWindowView *)&local_308,8);
      dlg_show_modal(&local_308,0);
      break;
    case 0x1a:
      dialog_load_game_text(&local_308,ADDR(0x631284, ((u8 *)&g.d_00631284)));
      dialog_add_sprite
                ((DialogOptionList *)&local_308,(iptr)(&improvement_icon_sprites + piVar1[4] * 0x3c),0,0);
      dialog_set_image_zoom((DialogWindowView *)&local_308,8);
      dlg_show_modal(&local_308,0);
      break;
    case 0x1b:
      snd_play_effect(5,0,0,0);
      popup_city_picture_zoom(ADDR(0x631290, ((u8 *)&g.d_00631290)),piVar1[5],0x46,1,piVar1[4]);
      break;
    case 0x1c:
      snd_play_effect(5,0,0,0);
      popup_city_picture_zoom(ADDR(0x63129c, ((u8 *)&g.d_0063129c)),piVar1[5],0x46,1,piVar1[4]);
      break;
    case 0x1d:
      snd_play_effect(5,0,0,0);
      popup_city_picture_zoom(ADDR(0x6312a8, ((u8 *)&g.d_006312a8)),piVar1[5],0x46,1,piVar1[4]);
      break;
    case 0x1e:
      snd_play_effect(5,0,0,0);
      popup_city_picture_zoom(ADDR(0x6312b8, ((u8 *)&g.d_006312b8)),piVar1[5],0x46,1,piVar1[4]);
      break;
    case 0x1f:
      dlg_game_txt_with_unit(ADDR(0x6312c8, ((u8 *)&g.d_006312c8)),piVar1[4]);
      break;
    case 0x20:
      dlg_game_txt_with_unit(ADDR(0x6312d4, ((u8 *)&g.d_006312d4)),piVar1[4]);
      break;
    case 0x21:
      popup_game_with_sprite(ADDR(0x6312e0, ((u8 *)&g.d_006312e0)),ADDR(0x6469e0, ((u8 *)&g.d_006469e0)),0);
      break;
    case 0x22:
      dlg_game_txt_with_unit(ADDR(0x6312f0, ((u8 *)&g.d_006312f0)),piVar1[4]);
      break;
    case 0x23:
      iVar4 = dlg_game_txt_with_unit(ADDR(0x6312fc, ((u8 *)&g.d_006312fc)),piVar1[5]);
      net_send_message(0x7b,*(i32 *)
                               (&net_player_slots + *(int *)(&net_civ_slots + piVar1[4] * 4) * 0x54),
                         iVar4,0,0,0,0,0,0,0);
      break;
    case 0x24:
      iVar4 = dlg_game_txt_with_unit(ADDR(0x631304, ((u8 *)&g.d_00631304)),piVar1[5]);
      net_send_message(0x7b,*(i32 *)
                               (&net_player_slots + *(int *)(&net_civ_slots + piVar1[4] * 4) * 0x54),
                         iVar4,0,0,0,0,0,0,0);
      break;
    case 0x25:
      dlg_game_txt_with_unit(ADDR(0x63130c, ((u8 *)&g.d_0063130c)),piVar1[4]);
      break;
    case 0x26:
      popup_game_with_sprite(ADDR(0x631318, ((u8 *)&g.d_00631318)),(iptr)(&unit_sprites + piVar1[4] * 0x3c),piVar1[5]);
      break;
    case 0x27:
      popup_game_with_sprite(ADDR(0x631320, ((u8 *)&g.d_00631320)),(iptr)(&unit_sprites + piVar1[4] * 0x3c),piVar1[5]);
      break;
    case 0x28:
      popup_game_with_sprite(ADDR(0x631328, ((u8 *)&g.d_00631328)),(iptr)(&unit_sprites + piVar1[4] * 0x3c),piVar1[5]);
      break;
    case 0x29:
      popup_game_with_improvement(ADDR(0x631334, ((u8 *)&g.d_00631334)),0x3e,8);
      break;
    case 0x2a:
      popup_game_with_improvement(ADDR(0x631340, ((u8 *)&g.d_00631340)),0x11,8);
      break;
    case 0x2b:
      popup_game_with_sprite(ADDR(0x631344, ((u8 *)&g.d_00631344)),(iptr)(&government_sprites + piVar1[4] * 0x3c),piVar1[5]);
      break;
    case 0x2c:
      popup_game_with_sprite(ADDR(0x63134c, ((u8 *)&g.d_0063134c)),(iptr)(&government_sprites + piVar1[4] * 0x3c),piVar1[5]);
      break;
    case 0x2d:
      dlg_game_txt_with_unit(ADDR(0x631358, ((u8 *)&g.d_00631358)),piVar1[4]);
      break;
    case 0x2e:
      dlg_game_txt_with_unit(ADDR(0x631364, ((u8 *)&g.d_00631364)),piVar1[4]);
      break;
    case 0x2f:
      dlg_game_txt_with_unit(ADDR(0x63136c, ((u8 *)&g.d_0063136c)),piVar1[4]);
      break;
    case 0x30:
      dlg_game_txt_with_unit(ADDR(0x63137c, ((u8 *)&g.d_0063137c)),piVar1[4]);
      break;
    case 0x31:
      popup_game_with_improvement(ADDR(0x631388, ((u8 *)&g.d_00631388)),piVar1[4],8);
      break;
    case 0x32:
      popup_game_with_improvement(ADDR(0x631394, ((u8 *)&g.d_00631394)),piVar1[4],8);
      break;
    case 0x33:
      dlg_game_txt_with_unit(ADDR(0x63139c, ((u8 *)&g.d_0063139c)),piVar1[4]);
      break;
    case 0x34:
      dlg_game_txt_with_unit(ADDR(0x6313a8, ((u8 *)&g.d_006313a8)),piVar1[4]);
      break;
    case 0x35:
      popup_game(ADDR(0x6313b8, ((u8 *)&g.d_006313b8)));
      break;
    case 0x36:
      popup_game(ADDR(0x6313c8, ((u8 *)&g.d_006313c8)));
      break;
    case 0x37:
      dlg_game_txt_with_unit_flags(ADDR(0x6313d4, ((u8 *)&g.d_006313d4)),piVar1[4],0);
      break;
    case 0x38:
      popup_game_with_sprite(ADDR(0x6313dc, ((u8 *)&g.d_006313dc)),(iptr)(&diplo_popup_portrait_sprite +
                                        ((game.advance_known_by[0xf] != '\0') - 1 & 0xffff7c80)),0);
      break;
    case 0x39:
      popup_game_with_sprite(ADDR(0x6313ec, ((u8 *)&g.d_006313ec)),(iptr)(&diplo_popup_portrait_sprite +
                                        ((game.advance_known_by[0xf] != '\0') - 1 & 0xffff7c80)),0);
      break;
    case 0x3a:
      popup_game(ADDR(0x6313f8, ((u8 *)&g.d_006313f8)));
      break;
    case 0x3b:
      popup_game(ADDR(0x631404, ((u8 *)&g.d_00631404)));
      break;
    case 0x3c:
      popup_game(ADDR(0x631414, ((u8 *)&g.d_00631414)));
      break;
    case 0x3d:
      civs[human_civ].last_treaty_turn[piVar1[4]] = game.turn;
      civs[piVar1[4]].last_treaty_turn[human_civ] = game.turn;
      if (parley_other_civ == -1) {
        parley_other_civ = -2;
        text_clear();
        iVar4 = civ_leader_title(piVar1[4]);
        text_append(iVar4);
        text_append_space();
        iVar4 = civ_leader_name(piVar1[4]);
        text_append(iVar4);
        text_append_space();
        text_append_label(0x8c);
        text_append_space();
        iVar4 = civ_name_plural(piVar1[4]);
        text_append(iVar4);
        text_set_string_arg(0,ADDR(0x679640, ((u8 *)&g.d_00679640)));
        iVar4 = civ_leader_name(human_civ);
        text_set_string_arg(1,iVar4);
        iVar4 = civ_name_plural(human_civ);
        text_set_string_arg(2,iVar4);
        if (*(char *)&civs[piVar1[4]].attitude[human_civ] == '\0') {
          local_330 = 0;
        }
        else {
          local_330 = diplo_attitude_level((uint)civs[piVar1[4]].attitude[human_civ]);
        }
        iVar4 = label_string(attitude_names[local_330]);
        text_set_string_arg(3,iVar4);
        dlg_pending_idle_callback = ((void *)ADDR(0x00403d0f, net_popup_idle_autoclose));
        iVar3 = popup_game_with_sprite(ADDR(0x631424, ((u8 *)&g.d_00631424)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        if (net_host_handoff_stage == '\0') {
          if (nm_parley_cancel_count == 0) {
            net_send_message(0x80,*(i32 *)
                                     (&net_player_slots + *(int *)(&net_civ_slots + piVar1[4] * 4) * 0x54
                                     ),iVar3,0,0,0,0,0,0,0);
          }
          if (nm_parley_cancel_count == 0) {
            if (iVar3 == 1) {
              iVar4 = piVar1[4];
              operator_delete(piVar1);
              net_popup_in_progress_i32 = 0;
              parley_wnd_open((ViewWindow *)&parley_wnd,iVar4,2);
              local_8 = 0xffffffff;
              /* inlined unwind funclet 0051399d */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
              goto LAB_005139b3;
            }
          }
          else {
            nm_parley_cancel_count = 0;
            iVar4 = civ_name_plural(piVar1[4]);
            text_set_string_arg(0,iVar4);
            dlg_pending_idle_callback = ((void *)ADDR(0x00403c74, turn_popup_timeout_idle));
            popup_game_with_sprite(ADDR(0x631434, ((u8 *)&g.d_00631434)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
          }
          parley_other_civ = -1;
          mp_meeting_pending = 0;
        }
        else {
          net_send_message(0x80,*(i32 *)
                                   (&net_player_slots + *(int *)(&net_civ_slots + piVar1[4] * 4) * 0x54),
                             2,0,0,0,0,0,0,0);
          parley_other_civ = -1;
          mp_meeting_pending = 0;
        }
      }
      else {
        net_send_message(0x80,*(i32 *)
                                 (&net_player_slots + *(int *)(&net_civ_slots + piVar1[4] * 4) * 0x54),2,
                           0,0,0,0,0,0,0);
      }
      break;
    case 0x3e:
      dlg_game_txt_with_unit_flags(ADDR(0x631444, ((u8 *)&g.d_00631444)),piVar1[4],(piVar1[5] == 0) - 1 & 8);
      break;
    case 0x3f:
      if (*(int *)(&net_player_slots + *(int *)(&net_civ_slots + human_civ * 4) * 0x54) != piVar1[4])
      {
        popup_game_with_sprite(ADDR(0x63144c, ((u8 *)&g.d_0063144c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      }
      break;
    case 0x40:
      dlg_load_game_section(&local_308,ADDR(0x631458, ((u8 *)&g.d_00631458)),0x2000000);
      iVar4 = label_string(*(i32 *)(label_string_ids + 0xd50));
      dialog_add_button((DialogButtonsView *)&local_308,iVar4);
      iVar4 = label_string(*(i32 *)(label_string_ids + 0xd54));
      dialog_add_button((DialogButtonsView *)&local_308,iVar4);
      dlg_show_modal(&local_308,0x28);
      net_send_message(0x56,0,local_308.field_dc,0,0,0,0,0,0,0);
      break;
    case 0x41:
      popup_game_with_sprite(ADDR(0x63146c, ((u8 *)&g.d_0063146c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      break;
    case 0x42:
      popup_game_with_sprite(ADDR(0x63147c, ((u8 *)&g.d_0063147c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      break;
    case 0x43:
      dlg_load_game_section(&local_308,ADDR(0x63148c, ((u8 *)&g.d_0063148c)),0x2000000);
      iVar4 = label_string(*(i32 *)(label_string_ids + 0xd50));
      dialog_add_button((DialogButtonsView *)&local_308,iVar4);
      iVar4 = label_string(*(i32 *)(label_string_ids + 0xd54));
      dialog_add_button((DialogButtonsView *)&local_308,iVar4);
      dlg_show_modal(&local_308,0);
      net_send_message(0x57,0,local_308.field_dc,0,0,0,0,0,0,0);
      break;
    case 0x44:
      popup_game_with_sprite(ADDR(0x63149c, ((u8 *)&g.d_0063149c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      break;
    case 0x45:
      popup_game_with_sprite(ADDR(0x6314a8, ((u8 *)&g.d_006314a8)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      break;
    case 0x46:
      snd_play_effect(0x23,1,0,0);
      city_notify_dialog_ex(ADDR(0x6314b4, ((u8 *)&g.d_006314b4)),piVar1[4],1,ADDR(0x645fe8, ((u8 *)&g.d_00645fe8)));
      break;
    case 0x47:
      dialog_load_game_text(&local_308,ADDR(0x6314c0, ((u8 *)&g.d_006314c0)));
      if (piVar1[4] < 0) {
        local_338 = &improvement_icon_sprites + piVar1[5] * 0x3c;
      }
      else {
        local_338 = &wonder_icon_sprites + piVar1[4] * 0x3c;
      }
      dialog_add_sprite((DialogOptionList *)&local_308,(iptr)local_338,0,0);
      dialog_set_image_zoom((DialogWindowView *)&local_308,8);
      dlg_show_modal(&local_308,0);
      break;
    case 0x48:
      popup_game(ADDR(0x6314c8, ((u8 *)&g.d_006314c8)));
      break;
    case 0x49:
      popup_game(ADDR(0x6314d4, ((u8 *)&g.d_006314d4)));
      break;
    case 0x4a:
      dialog_load_game_text(&local_308,ADDR(0x6314e0, ((u8 *)&g.d_006314e0)));
      dialog_add_sprite
                ((DialogOptionList *)&local_308,(iptr)(&improvement_icon_sprites + piVar1[4] * 0x3c),0,0);
      dialog_set_image_zoom((DialogWindowView *)&local_308,8);
      dlg_show_modal(&local_308,0);
      break;
    case 0x4b:
      dialog_load_game_text(&local_308,ADDR(0x6314f0, ((u8 *)&g.d_006314f0)));
      dialog_add_sprite
                ((DialogOptionList *)&local_308,(iptr)(&improvement_icon_sprites + piVar1[4] * 0x3c),0,0);
      dialog_set_image_zoom((DialogWindowView *)&local_308,8);
      dlg_show_modal(&local_308,0);
      break;
    case 0x4c:
      dialog_load_game_text(&local_308,ADDR(0x631500, ((u8 *)&g.d_00631500)));
      dialog_add_sprite
                ((DialogOptionList *)&local_308,(iptr)(&improvement_icon_sprites + piVar1[4] * 0x3c),0,0);
      dialog_set_image_zoom((DialogWindowView *)&local_308,8);
      dlg_show_modal(&local_308,0);
      break;
    case 0x4d:
      dialog_load_game_text(&local_308,ADDR(0x631510, ((u8 *)&g.d_00631510)));
      dialog_add_sprite
                ((DialogOptionList *)&local_308,
                 (iptr)(&advance_category_icon_sprites +
                       (char)advances[piVar1[4]].category * 0xf0 +
                       (char)advances[piVar1[4]].epoch * 0x3c),0,0);
      dialog_add_sprite
                ((DialogOptionList *)&local_308,(iptr)(&improvement_icon_sprites + piVar1[5] * 0x3c),0,0);
      dialog_set_image_zoom((DialogWindowView *)&local_308,8);
      dlg_show_modal(&local_308,0);
      break;
    case 0x4e:
      dlg_game_txt_with_unit(ADDR(0x63151c, ((u8 *)&g.d_0063151c)),piVar1[4]);
      break;
    case 0x4f:
      dialog_init_default(&local_308);
      for (local_310 = 0; local_310 < piVar1[2]; local_310++) {
        dialog_add_line
                  ((DialogAddLineView *)&local_308,(iptr)(&text_string_args + local_310 * 0x104),0xffffffff,
                   0xffffffff,0xffffffff,0);
      }
      dlg_show_modal(&local_308,0);
      break;
    case 0x50:
      popup_game_with_sprite(ADDR(0x63152c, ((u8 *)&g.d_0063152c)),ADDR(0x647748, ((u8 *)&g.d_00647748)),0);
      break;
    case 0x51:
      dlg_game_txt_with_unit(ADDR(0x631534, ((u8 *)&g.d_00631534)),piVar1[4]);
      break;
    case 0x52:
      dlg_game_txt_with_unit(ADDR(0x631544, ((u8 *)&g.d_00631544)),piVar1[4]);
      break;
    case 0x53:
      popup_game_with_sprite(ADDR(0x631554, ((u8 *)&g.d_00631554)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      break;
    case 0x54:
      popup_game_with_advance(ADDR(0x631560, ((u8 *)&g.d_00631560)),0x3c,8);
      break;
    case 0x55:
      snd_play_effect(0x44,1,0,0);
      popup_game_with_sprite(ADDR(0x63156c, ((u8 *)&g.d_0063156c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      break;
    case 0x56:
      snd_play_effect(0x44,1,0,0);
      popup_game_with_sprite(ADDR(0x63157c, ((u8 *)&g.d_0063157c)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      break;
    case 0x57:
      iVar3 = civ_has_advance(piVar1[4],0x23);
      if (iVar3 == 0) {
        snd_play_effect(0x44,1,0,0);
      }
      else {
        snd_play_effect(0x27,1,0,0);
      }
      popup_game_with_sprite(ADDR(0x631590, ((u8 *)&g.d_00631590)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      break;
    case 0x58:
      snd_play_effect(0x44,1,0,0);
      popup_game_with_sprite(ADDR(0x631598, ((u8 *)&g.d_00631598)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      break;
    case 0x59:
      iVar3 = civ_has_advance(piVar1[5],0x23);
      if (iVar3 == 0) {
        snd_play_effect(0x44,1,0,0);
      }
      else {
        snd_play_effect(0x27,1,0,0);
      }
      popup_game_with_sprite(ADDR(0x6315d8, ((u8 *)&g.d_006315d8)),(iptr)(&improvement_icon_sprites + piVar1[4] * 0x3c),8);
      break;
    case 0x5a:
      iVar3 = civ_has_advance(piVar1[4],0x23);
      if (iVar3 == 0) {
        snd_play_effect(0x44,1,0,0);
      }
      else {
        snd_play_effect(0x27,1,0,0);
      }
      popup_game(ADDR(0x6315e4, ((u8 *)&g.d_006315e4)));
      break;
    case 0x5b:
      snd_play_effect(0x44,1,0,0);
      popup_game_with_sprite(ADDR(0x6315a4, ((u8 *)&g.d_006315a4)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      break;
    case 0x5c:
      text_clear();
      text_append(ADDR(0x6315b0, ((u8 *)&g.d_006315b0)));
      popup_game_with_improvement(ADDR(0x679640, ((u8 *)&g.d_00679640)),0x3e,8);
      break;
    case 0x5d:
      text_clear();
      text_append(ADDR(0x6315bc, ((u8 *)&g.d_006315bc)));
      popup_game_with_improvement(ADDR(0x679640, ((u8 *)&g.d_00679640)),0x3e,8);
      break;
    case 0x5e:
      snd_play_effect(0x44,1,0,0);
      popup_game(ADDR(0x6315cc, ((u8 *)&g.d_006315cc)));
      break;
    case 0x5f:
      snd_play_effect(0x5d,0,0,0);
      dlg_game_txt_with_unit(ADDR(0x6315f0, ((u8 *)&g.d_006315f0)),piVar1[4]);
      break;
    case 0x60:
      snd_play_effect(0x5d,0,0,0);
      dlg_game_txt_with_unit(ADDR(0x6315f8, ((u8 *)&g.d_006315f8)),piVar1[4]);
      break;
    case 0x61:
      snd_play_effect(0x5d,0,0,0);
      dlg_game_txt_with_unit(ADDR(0x631600, ((u8 *)&g.d_00631600)),piVar1[4]);
      break;
    case 0x62:
      popup_game(ADDR(0x63160c, ((u8 *)&g.d_0063160c)));
      break;
    case 99:
      popup_game_with_advance(ADDR(0x631618, ((u8 *)&g.d_00631618)),piVar1[4],0);
      break;
    case 100:
      if ((parley_wnd_closed == 0) && (piVar1[4] == parley_other_civ)) {
        parley_reveal_units_prompt_open = 1;
        dlg_load_game_section(&local_308,ADDR(0x631620, ((u8 *)&g.d_00631620)),0x2000000);
        iVar4 = label_string(*(i32 *)(label_string_ids + 0xdd4));
        dialog_add_button((DialogButtonsView *)&local_308,iVar4);
        iVar4 = label_string(*(i32 *)(label_string_ids + 0xdd8));
        dialog_add_button((DialogButtonsView *)&local_308,iVar4);
        dlg_show_modal(&local_308,0x14);
        if (local_308.field_dc == 1) {
          parley_local_units_revealed = 1;
          if (parley_mode == 2) {
            ctrl_show_and_redraw(parley_conceal_info_button);
            ctrl_enable(parley_conceal_info_button);
            control_hide(parley_reveal_info_button);
            ctrl_disable(parley_reveal_info_button);
          }
          else {
            control_hide(parley_conceal_info_button);
            ctrl_disable(parley_conceal_info_button);
            control_hide(parley_reveal_info_button);
            ctrl_disable(parley_reveal_info_button);
          }
          net_send_message(0xa7,*(i32 *)
                                   (&net_player_slots +
                                   *(int *)(&net_civ_slots + parley_other_civ * 4) * 0x54),human_civ,
                             (int)parley_local_units_revealed,0,0,0,0,0,0);
          if (((parley_mode == 0xe) && (parley_barter_want_kind == 2)) ||
             ((parley_mode == 0xf && (parley_demand_kind == 2)))) {
            ctrl_show_and_redraw(parley_hide_origin_button);
            control_hide(parley_reveal_origin_button);
            parley_local_units_revealed = 1;
            ctrl_enable(parley_sort_by_unit_buttons);
            ctrl_enable(parley_sort_by_city_buttons);
            parley_draw_unit_list(0);
          }
        }
        parley_reveal_units_prompt_open = 0;
      }
      break;
    case 0x65:
      if ((parley_wnd_closed == 0) && (piVar1[4] == parley_other_civ)) {
        parley_reveal_city_prompt_open = 1;
        dlg_load_game_section(&local_308,ADDR(0x631634, ((u8 *)&g.d_00631634)),0x2000000);
        iVar4 = label_string(*(i32 *)(label_string_ids + 0xddc));
        dialog_add_button((DialogButtonsView *)&local_308,iVar4);
        iVar4 = label_string(*(i32 *)(label_string_ids + 0xdd8));
        dialog_add_button((DialogButtonsView *)&local_308,iVar4);
        dlg_show_modal(&local_308,0x14);
        if (local_308.field_dc == 1) {
          parley_local_cities_revealed = 1;
          if (parley_mode == 2) {
            ctrl_show_and_redraw(parley_conceal_info_button);
            ctrl_enable(parley_conceal_info_button);
            control_hide(parley_reveal_info_button);
            ctrl_disable(parley_reveal_info_button);
          }
          else {
            control_hide(parley_conceal_info_button);
            ctrl_disable(parley_conceal_info_button);
            control_hide(parley_reveal_info_button);
            ctrl_disable(parley_reveal_info_button);
          }
          net_send_message(0xa5,*(i32 *)
                                   (&net_player_slots +
                                   *(int *)(&net_civ_slots + parley_other_civ * 4) * 0x54),human_civ,
                             (int)parley_local_cities_revealed,0,0,0,0,0,0);
          if (((parley_mode == 0xe) && (parley_barter_want_kind == 3)) ||
             ((parley_mode == 0xf && (parley_demand_kind == 3)))) {
            ctrl_show_and_redraw(parley_hide_origin_button);
            control_hide(parley_reveal_origin_button);
            parley_draw_city_list(0);
          }
        }
        parley_reveal_city_prompt_open = 0;
      }
    }
    operator_delete(piVar1);
    net_popup_in_progress_i32 = 0;
  }
  local_8 = 0xffffffff;
  /* inlined unwind funclet 0051399d */ { dialog_dtor((Dialog *)((iptr)&local_308)); }
LAB_005139b3:
  return;
}
#undef dlg_pending_idle_callback
#undef human_civ
#undef mp_meeting_pending
#undef net_host_handoff_stage
#undef net_popup_queue_head
#undef net_popup_queue_tail
#undef nm_parley_cancel_count
#undef parley_other_civ
#undef parley_reveal_city_prompt_open
#undef parley_reveal_units_prompt_open
#undef net_popup_in_progress_i32
#undef local_338
#undef local_330
#undef local_310
#undef local_308
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 00514220 auto */
NetMsgQueue * __thiscall net_msgq_ctor(NetMsgQueue *this)

{
  _memset(this,0,24000);
  net_msgq_reset(this);
  return this;
}

/* 00514254 auto */
void __thiscall net_msgq_clear(NetMsgQueue *this)

{
  net_msgq_reset(this);
  return;
}

/* 00514272 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall net_msgq_reset(NetMsgQueue *this)

{
  u8 *puVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; local_8 < 2000; local_8++) {
    if (*(int *)(this->pad_0 + local_8 * 0xc + 4) != 0) {
      operator_delete(*(void **)(this->pad_0 + local_8 * 0xc + 4));
      puVar1 = this->pad_0 + local_8 * 0xc + 4;
      puVar1[0] = '\0';
      puVar1[1] = '\0';
      puVar1[2] = '\0';
      puVar1[3] = '\0';
    }
    puVar1 = this->pad_0 + local_8 * 0xc + 8;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
    puVar1 = this->pad_0 + local_8 * 0xc;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
  }
  this->low_read_index = 400;
  this->main_tail = 400;
  this->main_count = 0;
  this->prio_head = 0;
  this->prio_tail = 0;
  this->prio_count = 0;
  return;
}
#undef local_8

/* 0051435f auto */
i32 __cdecl net_msg_is_priority(int param_1)

{
  i32 uVar1;
  
  if ((param_1 < 0x2a) || (0x66 < param_1)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

/* 0051438f auto */
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define nm_heartbeat_ack_count (*(int *)((u8 *)&g.d_006c9090))
#define nm_heart_beat_count_i32 (*(i32 *)((u8 *)&g.d_006c908c))
#define local_208 (*(i8 (*)[256])(frame_ + FRAME_OFF(0)))
#define local_108 (*(iptr *)(frame_ + FRAME_OFF(256)))
#define local_104 (*(i8 (*)[256])(frame_ + FRAME_OFF(260)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __thiscall
net_msgq_enqueue(NetMsgQueueEnqueueView *this,int param_1,iptr param_2,uint param_3)

{
  int iVar1;
  void *pvVar2;
  i8 frame_[FRAME_OFF(520)] __attribute__((aligned(8)));  /* original stack frame */
  
  if ((((game.multiplayer == 5) || (game.multiplayer == 6)) && (param_1 != 0)) &&
     (param_1 != 0xff)) {
    if (net_host_flag == '\0') {
      param_1 = 0;
    }
    else {
      param_1 = 1;
    }
  }
  if (*(int *)(param_2 + 4) == 0x2b) {
    nm_heart_beat_count_i32++;
    net_send_message(0x2c,param_1,0,0,0,0,0,0,0,0);
  }
  else if (*(int *)(param_2 + 4) == 0x2c) {
    nm_heartbeat_ack_count++;
  }
  else {
    iVar1 = net_msg_is_priority(*(i32 *)(param_2 + 4));
    if (iVar1 == 0) {
      if ((this->normal_head == this->normal_tail) && (this->normal_count != 0)) {
        crt_strcpy(local_208,s_MESSAGE_LOST_in_EnqueueMessage__006318a8);
        crt_strcat(local_208,s_NM_DATAGRAM_00628470 + *(int *)(param_2 + 4) * 0x20);
        crt_strcat(local_208,s_From___d_Size___d_006318cc);
        dbg_logf_int2((iptr)local_208,param_1,param_3);
        return 0;
      }
      if (((int)this->normal_head < 400) || (1999 < (int)this->normal_head)) {
        err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x631908, ((u8 *)&g.d_00631908)),ADDR(0x6318e0, ((u8 *)&g.d_006318e0)),0x130);
      }
      if (((int)this->normal_tail < 400) || (1999 < (int)this->normal_tail)) {
        err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x631958, ((u8 *)&g.d_00631958)),ADDR(0x631930, ((u8 *)&g.d_00631930)),0x131);
      }
      pvVar2 = operator_new(param_3);
      *(void **)(this->pad_0 + this->normal_tail * 0xc + 4) = pvVar2;
      if (*(int *)(this->pad_0 + this->normal_tail * 0xc + 4) == 0) {
        dbg_logf_int2(ADDR(0x6319c0, ((u8 *)&g.d_006319c0)),*(i32 *)(param_2 + 4),*(i32 *)(param_2 + 8));
        return 0;
      }
      if (*(int *)(this->pad_0 + this->normal_tail * 0xc + 4) == 0) {
        err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x6319a8, ((u8 *)&g.d_006319a8)),ADDR(0x631980, ((u8 *)&g.d_00631980)),0x136);
      }
      crt_memcpy(*(i32 *)(this->pad_0 + this->normal_tail * 0xc + 4),param_2,param_3);
      *(int *)(this->pad_0 + this->normal_tail * 0xc) = param_1;
      *(uint *)(this->pad_0 + this->normal_tail * 0xc + 8) = param_3;
      this->normal_tail = (int)(this->normal_tail + 1) % 2000;
      if (this->normal_tail == 0) {
        this->normal_tail = 400;
      }
      this->normal_count++;
      if ((int)net_msgq_normal_peak < (int)this->normal_count) {
        net_msgq_normal_peak = this->normal_count;
      }
    }
    else {
      if ((this->prio_head == this->prio_tail) && (this->prio_count != 0)) {
        crt_strcpy(local_104,s_MESSAGE_LOST_in_Alpha_EnqueueMes_00631748);
        crt_strcat(local_104,s_NM_DATAGRAM_00628470 + *(int *)(param_2 + 4) * 0x20);
        crt_strcat(local_104,s_From___d_Size___d_00631770);
        dbg_logf_int2((iptr)local_104,param_1,param_3);
        return 0;
      }
      if (((int)this->prio_head < 0) || (399 < (int)this->prio_head)) {
        err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x6317ac, ((u8 *)&g.d_006317ac)),ADDR(0x631784, ((u8 *)&g.d_00631784)),0x10c);
      }
      if (((int)this->prio_tail < 0) || (399 < (int)this->prio_tail)) {
        err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x6317f8, ((u8 *)&g.d_006317f8)),ADDR(0x6317d0, ((u8 *)&g.d_006317d0)),0x10d);
      }
      pvVar2 = operator_new(param_3);
      *(void **)(this->pad_0 + this->prio_tail * 0xc + 4) = pvVar2;
      if (*(int *)(this->pad_0 + this->prio_tail * 0xc + 4) == 0) {
        local_108 = param_2;
        dbg_logf_int2(ADDR(0x631860, ((u8 *)&g.d_00631860)),*(i32 *)(param_2 + 4),*(i32 *)(param_2 + 8));
        return 0;
      }
      if (*(int *)(this->pad_0 + this->prio_tail * 0xc + 4) == 0) {
        err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x631844, ((u8 *)&g.d_00631844)),ADDR(0x63181c, ((u8 *)&g.d_0063181c)),0x112);
      }
      crt_memcpy(*(i32 *)(this->pad_0 + this->prio_tail * 0xc + 4),param_2,param_3);
      *(int *)(this->pad_0 + this->prio_tail * 0xc) = param_1;
      *(uint *)(this->pad_0 + this->prio_tail * 0xc + 8) = param_3;
      this->prio_tail = (int)(this->prio_tail + 1) % 400;
      this->prio_count++;
      if ((int)net_msgq_priority_peak < (int)this->prio_count) {
        net_msgq_priority_peak = this->prio_count;
      }
    }
  }
  return 1;
}
#undef net_host_flag
#undef nm_heartbeat_ack_count
#undef nm_heart_beat_count_i32
#undef local_208
#undef local_108
#undef local_104

/* 005149d6 auto */
i32 __thiscall
net_msgq_dequeue(NetMessageQueue *this,iptr param_1,iptr param_2,iptr param_3,int param_4)

{
  u8 *puVar1;
  i32 uVar2;
  
  if (this->high_count == 0) {
    if ((param_4 == 0) && (this->low_count != 0)) {
      *(i32 *)param_1 = *(i32 *)(this->pad_0 + this->low_read_index * 0xc);
      puVar1 = this->pad_0 + this->low_read_index * 0xc;
      puVar1[0] = '\0';
      puVar1[1] = '\0';
      puVar1[2] = '\0';
      puVar1[3] = '\0';
      *(i32 *)param_2 = *(i32 *)(this->pad_0 + this->low_read_index * 0xc + 4);
      puVar1 = this->pad_0 + this->low_read_index * 0xc + 4;
      puVar1[0] = '\0';
      puVar1[1] = '\0';
      puVar1[2] = '\0';
      puVar1[3] = '\0';
      *(i32 *)param_3 = *(i32 *)(this->pad_0 + this->low_read_index * 0xc + 8);
      puVar1 = this->pad_0 + this->low_read_index * 0xc + 8;
      puVar1[0] = '\0';
      puVar1[1] = '\0';
      puVar1[2] = '\0';
      puVar1[3] = '\0';
      this->low_read_index = (int)(this->low_read_index + 1) % 2000;
      if (this->low_read_index == 0) {
        this->low_read_index = 400;
      }
      this->low_count--;
      uVar2 = 1;
    }
    else {
      uVar2 = 0;
    }
  }
  else {
    *(i32 *)param_1 = *(i32 *)(this->pad_0 + this->high_read_index * 0xc);
    puVar1 = this->pad_0 + this->high_read_index * 0xc;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
    *(i32 *)param_2 = *(i32 *)(this->pad_0 + this->high_read_index * 0xc + 4);
    puVar1 = this->pad_0 + this->high_read_index * 0xc + 4;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
    *(i32 *)param_3 = *(i32 *)(this->pad_0 + this->high_read_index * 0xc + 8);
    puVar1 = this->pad_0 + this->high_read_index * 0xc + 8;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
    this->high_read_index = (int)(this->high_read_index + 1) % 400;
    this->high_count--;
    uVar2 = 1;
  }
  return uVar2;
}

/* 0051ea0c auto */
#define dialog_stack_top (*(int * *)((u8 *)&g.d_006ad678))
#define net_host_handoff_stage (*(char *)((u8 *)&g.d_006ad698))
#define net_vote_status (*(int *)((u8 *)&g.d_006ad670))
#define dialog_timeout_start_i32 (*(i32 *)((u8 *)&g.d_006cec80))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl net_vote_wait_idle_cb(void)

{
  int iVar1;
  
  net_process_messages((NetSession *)&net_session,1,0);
  if ((((net_host_handoff_stage == '\0') && (iVar1 = timer_ticks(), iVar1 - dialog_timeout_start_i32 < 0x961)) &&
      (net_vote_replies_pending != 0)) && (net_vote_status != -1)) {
    return;
  }
  dialog_stack_top[0xf] = dialog_stack_top[0xf] | 0x400;
  wnd_end_modal_loop((ModalMenuWindow *)(*dialog_stack_top + 0x48));
  dialog_timeout_start_i32 = timer_ticks();
  return;
}
#undef dialog_stack_top
#undef net_host_handoff_stage
#undef net_vote_status
#undef dialog_timeout_start_i32

/* 0051f11a auto */
#define dialog_stack_top (*(int * *)((u8 *)&g.d_006ad678))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl net_lock_wait_idle_cb(void)

{
  timer_ticks();
  net_process_messages((NetSession *)&net_session,1,0);
  if ((nm_lock_data_count != 0) || (nm_server_canceled_count != 0)) {
    dialog_stack_top[0xf] = dialog_stack_top[0xf] | 0x400;
    wnd_end_modal_loop((ModalMenuWindow *)(*dialog_stack_top + 0x48));
  }
  return;
}
#undef dialog_stack_top

/* 0051f17e auto */
void __cdecl net_pump_idle_cb(void)

{
  net_process_messages((NetSession *)&net_session,1,0);
  return;
}

/* 005233fc auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define net_session_phase (*(int *)((u8 *)&g.d_006ad640))
#define net_slot_active_flags (*(i8 *)((u8 *)&g.d_006ad359))
#define net_slot_civs (*(i32 *)((u8 *)&g.d_006ad35c))
#define net_slot_host_flags (*(i8 *)((u8 *)&g.d_006ad358))
#define saved_resume_new_game (*(short *)((u8 *)&g.d_00654fa6))
#define saved_turn_civ (*(char *)((u8 *)&g.d_00654fa4))
#define local_28 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_24 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_1c (*(u8 *)(frame_ + FRAME_OFF(12)))
#define local_c (*(int *)(frame_ + FRAME_OFF(28)))
#define local_8 (*(u8 *)(frame_ + FRAME_OFF(32)))
i32 __cdecl net_host_register_player_civ(iptr param_1,int param_2)

{
  int iVar1;
  i8 iVar2;
  i8 iVar3;
  i32 uVar4;
  iptr iVar4;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (net_host_flag == '\0') {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x632320, ((u8 *)&g.d_00632320)),ADDR(0x6322f4, ((u8 *)&g.d_006322f4)),0x778);
  }
  iVar4 = human_civ;
  iVar3 = game.turn_civ;
  iVar2 = game.player_civ;
  if (((saved_resume_new_game == 0) && (saved_turn_civ == '\0')) && (net_session_phase < 2)) {
    iVar1 = *(int *)(param_1 + 0x18);
    uVar4 = *(i32 *)(param_1 + 0x14);
    local_24 = *(iptr *)(param_1 + 0x10);
    game.player_civ = (byte)local_24;
    civs[(char)(byte)local_24].tribe = (i16)uVar4;
    local_8 = (u8)uVar4;
    civs[game.player_civ].leader_portrait = local_8;
    if (iVar1 != 0) {
      civs[game.player_civ].leader_portrait += 21;
    }
    human_civ = (iptr)game.player_civ;
    if (net_session_phase < 3) {
      game.human_players = game.human_players | (byte)(1 << ((byte)local_24 & 0x1f));
    }
    else {
      pending_human_players = pending_human_players | (byte)(1 << ((byte)local_24 & 0x1f));
    }
    local_1c = (u8)iVar1;
    leaders[civs[game.player_civ].tribe].female = local_1c;
    leaders[civs[game.player_civ].tribe].leader_name =
         leaders[civs[game.player_civ].tribe].names[((uint)leaders[civs[game.player_civ].tribe].female)];
    uVar4 = label_string((int)leaders[civs[game.player_civ].tribe].leader_name);
    crt_strcpy((iptr)&civ_names[game.player_civ].leader_name,uVar4);
    if (0 < leaders[civs[game.player_civ].tribe].leader_name) {
      leaders[civs[game.player_civ].tribe].leader_name =
           -leaders[civs[game.player_civ].tribe].leader_name;
    }
    crt_strcpy((iptr)&civ_names[game.player_civ].leader_name,param_1 + 0x20);
    if (*(int *)(param_1 + 0x1c) != 0) {
      leaders[civs[game.player_civ].tribe].plural = -leaders[civs[game.player_civ].tribe].plural;
      leaders[civs[game.player_civ].tribe].adjective =
           -leaders[civs[game.player_civ].tribe].adjective;
      for (local_c = 0; local_c < 7; local_c++) {
        if (leaders[civs[game.player_civ].tribe].titles[local_c][iVar1] < 1)
        {
          local_28 = ~(int)leaders[civs[game.player_civ].tribe].titles[local_c][iVar1] + 1;
        }
        else {
          local_28 = (int)leaders[civs[game.player_civ].tribe].titles[local_c][iVar1];
        }
        uVar4 = label_string(local_28);
        crt_strcpy((iptr)&civ_names[game.player_civ].titles[local_c],uVar4);
        leaders[civs[game.player_civ].tribe].titles[local_c][iVar1] =
             -leaders[civs[game.player_civ].tribe].titles[local_c][iVar1];
      }
      crt_strcpy((iptr)&civ_names[game.player_civ].tribe_name,param_1 + 0x38);
      crt_strcpy((iptr)&civ_names[game.player_civ].adjective,param_1 + 0x50);
      if (*(int *)(param_1 + 0x68) != 0) {
        for (local_c = 0; local_c < 7; local_c++) {
          crt_strcpy((iptr)&civ_names[game.player_civ].titles[local_c],
                       local_c * 0x18 + param_1 + 0x6c);
        }
      }
    }
    civ_names[game.player_civ].city_style = (i16)*(i32 *)(param_1 + 0x114);
  }
  else {
    local_24 = *(iptr *)(param_1 + 0x10);
    if (net_session_phase < 3) {
      game.human_players = game.human_players | (byte)(1 << ((byte)local_24 & 0x1f));
    }
    else {
      pending_human_players = pending_human_players | (byte)(1 << ((byte)local_24 & 0x1f));
    }
    game.player_civ = (byte)local_24;
    game.turn_civ = (byte)local_24;
    human_civ = local_24;
    crt_strcpy((iptr)&civ_names[((char)(byte)local_24)].leader_name,param_1 + 0x20);
    if (0 < leaders[civs[game.player_civ].tribe].leader_name) {
      leaders[civs[game.player_civ].tribe].leader_name =
           -leaders[civs[game.player_civ].tribe].leader_name;
    }
    iVar1 = *(int *)(param_1 + 0x18);
    civs[human_civ].flags = civs[human_civ].flags & 0xfdff;
    if (iVar1 != 0) {
      civs[human_civ].flags = civs[human_civ].flags | 0x200;
    }
    local_1c = (u8)iVar1;
    leaders[civs[game.player_civ].tribe].female = local_1c;
  }
  for (local_20 = 0; (local_20 < 7 && (*(int *)(&net_player_slots + local_20 * 0x54) != param_2));
      local_20 = local_20 + 1) {
  }
  if (local_20 < 7) {
    *(int *)(&net_civ_slots + game.player_civ * 4) = local_20;
    (&net_slot_civs)[local_20 * 0x15] = (int)game.player_civ;
    (&net_slot_active_flags)[local_20 * 0x54] = 1;
    if (param_2 == 0) {
      (&net_slot_host_flags)[local_20 * 0x54] = 1;
    }
    else {
      (&net_slot_host_flags)[local_20 * 0x54] = 0;
    }
    uVar4 = 1;
  }
  else {
    if (net_session_phase < 3) {
      game.human_players = game.human_players & ~(byte)(1 << ((byte)local_24 & 0x1f));
    }
    else {
      pending_human_players = pending_human_players & ~(byte)(1 << ((byte)local_24 & 0x1f));
    }
    net_send_message(0x31,0,*(iptr *)(param_1 + 0x14),*(iptr *)(param_1 + 0x10),0,0,0,0,0,0);
    uVar4 = 0;
  }
  human_civ = iVar4;
  game.turn_civ = iVar3;
  game.player_civ = iVar2;
  return uVar4;
}
#undef human_civ
#undef net_host_flag
#undef net_session_phase
#undef net_slot_active_flags
#undef net_slot_civs
#undef net_slot_host_flags
#undef saved_resume_new_game
#undef saved_turn_civ
#undef local_28
#undef local_24
#undef local_20
#undef local_1c
#undef local_c
#undef local_8

/* 00523d8a auto */
void __cdecl net_send_rules_tables(i32 param_1)

{
  net_send_message(0x17,param_1,0,0,0,0,0,0,0,0);
  net_send_message(0x18,param_1,0,0,0,0,0,0,0,0);
  net_send_message(0x19,param_1,0,0,0,0,0,0,0,0);
  net_send_message(0x1a,param_1,0,0,0,0,0,0,0,0);
  net_send_message(0x1b,param_1,0,0,0,0,0,0,0,0);
  net_send_message(0x1c,param_1,0,0,0,0,0,0,0,0);
  net_send_message(0x1d,param_1,0,0,0,0,0,0,0,0);
  net_send_message(0x1e,param_1,0,0,0,0,0,0,0,0);
  net_send_message(0x21,param_1,0,0,0,0,0,0,0,0);
  net_send_message(0x22,param_1,0,0,0,0,0,0,0,0);
  net_send_message(0x23,param_1,0,0,0,0,0,0,0,0);
  net_send_message(0x24,param_1,0,0,0,0,0,0,0,0);
  return;
}

/* 00526ca0 auto */
#define chat_broadcast_all (*(i32 *)((u8 *)&g.d_0068aee4))
#define chat_mute_anonymous (*(i32 *)((u8 *)&g.d_0068aee0))
#define chat_remain_anonymous (*(i32 *)((u8 *)&g.d_0068aedc))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define list_bg_color (*(i32 *)((u8 *)&g.d_00635a18))
#define mp_chat_from_start (*(short *)((u8 *)&g.d_00654c7a))
#define panel_margin_x (*(int *)((u8 *)&g.d_0062d858))
#define parley_offer_acceptable_i32 (*(i32 *)((u8 *)&g.d_0067a9e0))
#define local_53c (*(u8 * *)(frame_ + FRAME_OFF(4)))
#define local_538 (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_534 (*(u8 * *)(frame_ + FRAME_OFF(12)))
#define local_530 (*(iptr *)(frame_ + FRAME_OFF(16)))
#define local_52c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_528 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_524 (*(int *)(frame_ + FRAME_OFF(28)))
#define local_51c (*(iptr *)(frame_ + FRAME_OFF(36)))
#define local_518 (*(u8 * *)(frame_ + FRAME_OFF(40)))
#define local_514 (*(int *)(frame_ + FRAME_OFF(44)))
#define local_50c (*(int *)(frame_ + FRAME_OFF(52)))
#define local_504 (*(int *)(frame_ + FRAME_OFF(60)))
#define local_4fc (*(int *)(frame_ + FRAME_OFF(68)))
#define local_4f8 (*(int *)(frame_ + FRAME_OFF(72)))
#define local_4f4 (*(int *)(frame_ + FRAME_OFF(76)))
#define local_4ec (*(int *)(frame_ + FRAME_OFF(84)))
#define local_4e8 (*(int *)(frame_ + FRAME_OFF(88)))
#define local_4e4 (*(int *)(frame_ + FRAME_OFF(92)))
#define local_4e0 (*(int *)(frame_ + FRAME_OFF(96)))
#define local_4d8 (*(iptr *)(frame_ + FRAME_OFF(104)))
#define local_4d4 (*(u8 * *)(frame_ + FRAME_OFF(108)))
#define local_4cc (*(int *)(frame_ + FRAME_OFF(116)))
#define local_4c4 (*(int *)(frame_ + FRAME_OFF(124)))
#define local_4c0 (*(int *)(frame_ + FRAME_OFF(128)))
#define local_4bc (*(int *)(frame_ + FRAME_OFF(132)))
#define local_4b8 (*(int *)(frame_ + FRAME_OFF(136)))
#define local_4b0 (*(iptr *)(frame_ + FRAME_OFF(144)))
#define local_4ac (*(u8 * *)(frame_ + FRAME_OFF(148)))
#define local_4a8 (*(int *)(frame_ + FRAME_OFF(152)))
#define local_4a4 (*(int *)(frame_ + FRAME_OFF(156)))
#define local_498 (*(int *)(frame_ + FRAME_OFF(168)))
#define local_494 (*(u8 * *)(frame_ + FRAME_OFF(172)))
#define local_490 (*(u8 * *)(frame_ + FRAME_OFF(176)))
#define local_48c (*(int *)(frame_ + FRAME_OFF(180)))
#define local_488 (*(int *)(frame_ + FRAME_OFF(184)))
#define local_484 (*(u8 * *)(frame_ + FRAME_OFF(188)))
#define local_480 (*(iptr *)(frame_ + FRAME_OFF(192)))
#define local_47c (*(u8 * *)(frame_ + FRAME_OFF(196)))
#define local_478 (*(iptr *)(frame_ + FRAME_OFF(200)))
#define local_474 (*(int *)(frame_ + FRAME_OFF(204)))
#define local_470 (*(int *)(frame_ + FRAME_OFF(208)))
#define local_468 (*(int *)(frame_ + FRAME_OFF(216)))
#define local_464 (*(int *)(frame_ + FRAME_OFF(220)))
#define local_45c (*(iptr *)(frame_ + FRAME_OFF(228)))
#define local_458 (*(u8 * *)(frame_ + FRAME_OFF(232)))
#define local_44c (*(int *)(frame_ + FRAME_OFF(244)))
#define local_448 (*(int *)(frame_ + FRAME_OFF(248)))
#define local_444 (*(int *)(frame_ + FRAME_OFF(252)))
#define local_43c (*(int *)(frame_ + FRAME_OFF(260)))
#define local_434 (*(iptr *)(frame_ + FRAME_OFF(268)))
#define local_430 (*(int *)(frame_ + FRAME_OFF(272)))
#define local_42c (*(int *)(frame_ + FRAME_OFF(276)))
#define local_424 (*(int *)(frame_ + FRAME_OFF(284)))
#define local_420 (*(int *)(frame_ + FRAME_OFF(288)))
#define local_418 (*(iptr *)(frame_ + FRAME_OFF(296)))
#define local_414 (*(u8 * *)(frame_ + FRAME_OFF(300)))
#define local_410 (*(int *)(frame_ + FRAME_OFF(304)))
#define local_40c (*(int *)(frame_ + FRAME_OFF(308)))
#define local_400 (*(int *)(frame_ + FRAME_OFF(320)))
#define local_3fc (*(int *)(frame_ + FRAME_OFF(324)))
#define local_3f4 (*(int *)(frame_ + FRAME_OFF(332)))
#define local_3ec (*(int *)(frame_ + FRAME_OFF(340)))
#define local_3e8 (*(int *)(frame_ + FRAME_OFF(344)))
#define local_3e4 (*(int *)(frame_ + FRAME_OFF(348)))
#define local_3e0 (*(u8 * *)(frame_ + FRAME_OFF(352)))
#define local_3dc (*(int *)(frame_ + FRAME_OFF(356)))
#define local_3d8 (*(int *)(frame_ + FRAME_OFF(360)))
#define local_3d4 (*(int *)(frame_ + FRAME_OFF(364)))
#define local_3c8 (*(iptr *)(frame_ + FRAME_OFF(376)))
#define local_3c4 (*(int *)(frame_ + FRAME_OFF(380)))
#define local_3c0 (*(int *)(frame_ + FRAME_OFF(384)))
#define local_3bc (*(int *)(frame_ + FRAME_OFF(388)))
#define local_3b4 (*(iptr *)(frame_ + FRAME_OFF(396)))
#define local_3b0 (*(u8 * *)(frame_ + FRAME_OFF(400)))
#define local_3ac (*(int *)(frame_ + FRAME_OFF(404)))
#define local_3a0 (*(u8 * *)(frame_ + FRAME_OFF(416)))
#define local_39c (*(int *)(frame_ + FRAME_OFF(420)))
#define local_390 (*(u8 * *)(frame_ + FRAME_OFF(432)))
#define local_38c (*(u8 * *)(frame_ + FRAME_OFF(436)))
#define local_380 (*(u8 * *)(frame_ + FRAME_OFF(448)))
#define local_37c (*(u8 * *)(frame_ + FRAME_OFF(452)))
#define local_378 (*(u8 * *)(frame_ + FRAME_OFF(456)))
#define local_370 (*(int *)(frame_ + FRAME_OFF(464)))
#define local_36c (*(u32 *)(frame_ + FRAME_OFF(468)))
#define local_368 (*(u8 * *)(frame_ + FRAME_OFF(472)))
#define local_364 (*(int *)(frame_ + FRAME_OFF(476)))
#define local_354 (*(int *)(frame_ + FRAME_OFF(492)))
#define local_34c (*(u8 * *)(frame_ + FRAME_OFF(500)))
#define local_344 (*(u8 * *)(frame_ + FRAME_OFF(508)))
#define local_33c (*(i8 * *)(frame_ + FRAME_OFF(516)))
#define local_338 (*(i32 *)(frame_ + FRAME_OFF(520)))
#define local_330 (*(i32 *)(frame_ + FRAME_OFF(528)))
#define local_328 (*(i8 * *)(frame_ + FRAME_OFF(536)))
#define local_324 (*(i32 *)(frame_ + FRAME_OFF(540)))
#define local_31c (*(i8 * *)(frame_ + FRAME_OFF(548)))
#define local_318 (*(i8 * *)(frame_ + FRAME_OFF(552)))
#define local_314 (*(i8 * *)(frame_ + FRAME_OFF(556)))
#define local_310 (*(i8 * *)(frame_ + FRAME_OFF(560)))
#define local_30c (*(i8 * *)(frame_ + FRAME_OFF(564)))
#define local_308 (*(i32 *)(frame_ + FRAME_OFF(568)))
#define local_300 (*(i8 * *)(frame_ + FRAME_OFF(576)))
#define local_2fc (*(i8 * *)(frame_ + FRAME_OFF(580)))
#define local_2f8 (*(i8 * *)(frame_ + FRAME_OFF(584)))
#define local_2f4 (*(i32 *)(frame_ + FRAME_OFF(588)))
#define local_2ec (*(i8 * *)(frame_ + FRAME_OFF(596)))
#define local_2e8 (*(i8 * *)(frame_ + FRAME_OFF(600)))
#define local_2e4 (*(i32 *)(frame_ + FRAME_OFF(604)))
#define local_2dc (*(i32 *)(frame_ + FRAME_OFF(612)))
#define local_2d4 (*(i32 *)(frame_ + FRAME_OFF(620)))
#define local_2cc (*(i32 *)(frame_ + FRAME_OFF(628)))
#define local_2c4 (*(i8 * *)(frame_ + FRAME_OFF(636)))
#define local_2c0 (*(i8 * *)(frame_ + FRAME_OFF(640)))
#define local_2bc (*(i8 * *)(frame_ + FRAME_OFF(644)))
#define local_2b8 (*(i32 *)(frame_ + FRAME_OFF(648)))
#define local_2b0 (*(i8 * *)(frame_ + FRAME_OFF(656)))
#define local_2ac (*(i8 * *)(frame_ + FRAME_OFF(660)))
#define local_2a8 (*(i8 * *)(frame_ + FRAME_OFF(664)))
#define local_2a4 (*(i8 * *)(frame_ + FRAME_OFF(668)))
#define local_2a0 (*(i8 * *)(frame_ + FRAME_OFF(672)))
#define local_29c (*(i32 *)(frame_ + FRAME_OFF(676)))
#define local_294 (*(i8 * *)(frame_ + FRAME_OFF(684)))
#define local_290 (*(i8 * *)(frame_ + FRAME_OFF(688)))
#define local_28c (*(i8 * *)(frame_ + FRAME_OFF(692)))
#define local_288 (*(i8 * *)(frame_ + FRAME_OFF(696)))
#define local_284 (*(i32 *)(frame_ + FRAME_OFF(700)))
#define local_27c (*(i8 * *)(frame_ + FRAME_OFF(708)))
#define local_278 (*(i8 * *)(frame_ + FRAME_OFF(712)))
#define local_274 (*(i8 * *)(frame_ + FRAME_OFF(716)))
#define local_270 (*(i32 *)(frame_ + FRAME_OFF(720)))
#define local_268 (*(i8 * *)(frame_ + FRAME_OFF(728)))
#define local_264 (*(i8 * *)(frame_ + FRAME_OFF(732)))
#define local_260 (*(i32 *)(frame_ + FRAME_OFF(736)))
#define local_258 (*(i8 * *)(frame_ + FRAME_OFF(744)))
#define local_254 (*(i8 * *)(frame_ + FRAME_OFF(748)))
#define local_250 (*(i32 *)(frame_ + FRAME_OFF(752)))
#define local_248 (*(i32 *)(frame_ + FRAME_OFF(760)))
#define local_240 (*(i8 * *)(frame_ + FRAME_OFF(768)))
#define local_23c (*(i8 * *)(frame_ + FRAME_OFF(772)))
#define local_238 (*(uptr *)(frame_ + FRAME_OFF(776)))
#define local_230 (*(uptr *)(frame_ + FRAME_OFF(784)))
#define local_228 (*(uptr *)(frame_ + FRAME_OFF(792)))
#define local_220 (*(i8 * *)(frame_ + FRAME_OFF(800)))
#define local_21c (*(i32 *)(frame_ + FRAME_OFF(804)))
#define local_214 (*(i8 * *)(frame_ + FRAME_OFF(812)))
#define local_210 (*(i8 * *)(frame_ + FRAME_OFF(816)))
#define local_20c (*(i8 * *)(frame_ + FRAME_OFF(820)))
#define local_208 (*(i8 * *)(frame_ + FRAME_OFF(824)))
#define local_204 (*(uptr *)(frame_ + FRAME_OFF(828)))
#define local_1fc (*(i8 * *)(frame_ + FRAME_OFF(836)))
#define local_1f8 (*(uptr *)(frame_ + FRAME_OFF(840)))
#define local_1f0 (*(tagRECT *)(frame_ + FRAME_OFF(848)))
#define local_1e0 (*(int *)(frame_ + FRAME_OFF(864)))
#define local_1dc (*(int *)(frame_ + FRAME_OFF(868)))
#define local_1d8 (*(iptr *)(frame_ + FRAME_OFF(872)))
#define local_1d4 (*(int *)(frame_ + FRAME_OFF(876)))
#define local_1d0 (*(i32 *)(frame_ + FRAME_OFF(880)))
#define local_1cc (*(i32 *)(frame_ + FRAME_OFF(884)))
#define local_1c8 (*(i32 *)(frame_ + FRAME_OFF(888)))
#define local_1c4 (*(i32 *)(frame_ + FRAME_OFF(892)))
#define local_1c0 (*(i32 *)(frame_ + FRAME_OFF(896)))
#define local_1bc (*(i32 *)(frame_ + FRAME_OFF(900)))
#define local_1b8 (*(i32 *)(frame_ + FRAME_OFF(904)))
#define local_1b4 (*(i32 *)(frame_ + FRAME_OFF(908)))
#define local_1b0 (*(iptr *)(frame_ + FRAME_OFF(912)))
#define local_1ac (*(iptr (*)[4])(frame_ + FRAME_OFF(916)))
#define local_19c (*(uptr *)(frame_ + FRAME_OFF(932)))
#define local_198 (*(iptr (*)[4])(frame_ + FRAME_OFF(936)))
#define local_188 (*(i32 *)(frame_ + FRAME_OFF(952)))
#define local_184 (*(i32 *)(frame_ + FRAME_OFF(956)))
#define local_180 (*(i32 *)(frame_ + FRAME_OFF(960)))
#define local_17c (*(tagRECT *)(frame_ + FRAME_OFF(964)))
#define local_16c (*(int *)(frame_ + FRAME_OFF(980)))
#define local_168 (*(int *)(frame_ + FRAME_OFF(984)))
#define local_164 (*(int *)(frame_ + FRAME_OFF(988)))
#define local_160 (*(int *)(frame_ + FRAME_OFF(992)))
#define local_15c (*(i32 *)(frame_ + FRAME_OFF(996)))
#define local_158 (*(char (*)[32])(frame_ + FRAME_OFF(1000)))
#define local_138 (*(i32 *)(frame_ + FRAME_OFF(1032)))
#define local_134 (*(i32 *)(frame_ + FRAME_OFF(1036)))
#define local_130 (*(i32 *)(frame_ + FRAME_OFF(1040)))
#define local_12c (*(i32 *)(frame_ + FRAME_OFF(1044)))
#define local_128 (*(i32 *)(frame_ + FRAME_OFF(1048)))
#define local_124 (*(i32 *)(frame_ + FRAME_OFF(1052)))
#define local_120 (*(i32 *)(frame_ + FRAME_OFF(1056)))
#define local_11c (*(i32 *)(frame_ + FRAME_OFF(1060)))
#define local_118 (*(i32 *)(frame_ + FRAME_OFF(1064)))
#define local_114 (*(i32 *)(frame_ + FRAME_OFF(1068)))
#define local_110 (*(i32 *)(frame_ + FRAME_OFF(1072)))
#define local_10c (*(i32 *)(frame_ + FRAME_OFF(1076)))
#define local_108 (*(i32 *)(frame_ + FRAME_OFF(1080)))
#define local_104 (*(i32 *)(frame_ + FRAME_OFF(1084)))
#define local_100 (*(i32 *)(frame_ + FRAME_OFF(1088)))
#define local_fc (*(i32 *)(frame_ + FRAME_OFF(1092)))
#define local_f8 (*(i32 *)(frame_ + FRAME_OFF(1096)))
#define local_f4 (*(i32 *)(frame_ + FRAME_OFF(1100)))
#define local_f0 (*(i32 *)(frame_ + FRAME_OFF(1104)))
#define local_ec (*(i32 *)(frame_ + FRAME_OFF(1108)))
#define local_e8 (*(i32 *)(frame_ + FRAME_OFF(1112)))
#define local_e4 (*(i32 *)(frame_ + FRAME_OFF(1116)))
#define local_e0 (*(i32 *)(frame_ + FRAME_OFF(1120)))
#define local_dc (*(i32 *)(frame_ + FRAME_OFF(1124)))
#define local_d8 (*(uptr *)(frame_ + FRAME_OFF(1128)))
#define local_d4 (*(uint *)(frame_ + FRAME_OFF(1132)))
#define civ (*(int *)(frame_ + FRAME_OFF(1136)))
#define local_cc (*(u32 *)(frame_ + FRAME_OFF(1140)))
#define local_c8 (*(int *)(frame_ + FRAME_OFF(1144)))
#define local_c4 (*(int *)(frame_ + FRAME_OFF(1148)))
#define local_c0 (*(int *)(frame_ + FRAME_OFF(1152)))
#define local_bc (*(int *)(frame_ + FRAME_OFF(1156)))
#define local_b8 (*(iptr *)(frame_ + FRAME_OFF(1160)))
#define local_b4 (*(iptr (*)[4])(frame_ + FRAME_OFF(1164)))
#define local_a4 (*(i32 *)(frame_ + FRAME_OFF(1180)))
#define local_a0 (*(int *)(frame_ + FRAME_OFF(1184)))
#define local_9c (*(i8 (*)[80])(frame_ + FRAME_OFF(1188)))
#define local_4c (*(int * *)(frame_ + FRAME_OFF(1268)))
#define local_48 (*(iptr * *)(frame_ + FRAME_OFF(1272)))
#define local_44 (*(int *)(frame_ + FRAME_OFF(1276)))
#define local_40 (*(int *)(frame_ + FRAME_OFF(1280)))
#define local_3c (*(int *)(frame_ + FRAME_OFF(1284)))
#define local_38 (*(uptr *)(frame_ + FRAME_OFF(1288)))
#define local_34 (*(int *)(frame_ + FRAME_OFF(1292)))
#define local_30 (*(char *)(frame_ + FRAME_OFF(1296)))
#define local_2c (*(u32 *)(frame_ + FRAME_OFF(1300)))
#define local_28 (*(char *)(frame_ + FRAME_OFF(1304)))
#define local_24 (*(tagRECT *)(frame_ + FRAME_OFF(1308)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(1324)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(1328)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1332)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1336)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall parley_add_side_dialog(ViewWindow *this,int param_1,int param_2)

{
  u8 *puVar1;
  int iVar2;
  InputControl *pCVar3;
  iptr iVar4;
  int iVar5;
  Control *pCVar6;
  uptr uVar7;
  u32 uVar8;
  uptr uVar9;
  i32 uVar10;
  uptr uVar2;
  i8 frame_[FRAME_OFF(1344)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  if ((param_2 != 0) && (param_2 != 1)) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x632458, ((u8 *)&g.d_00632458)),ADDR(0x63242c, ((u8 *)&g.d_0063242c)),0xc);
  }
  if (param_1 < 0) {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x6324ac, ((u8 *)&g.d_006324ac)),ADDR(0x632480, ((u8 *)&g.d_00632480)),0xd);
  }
  local_28 = '\0';
  local_30 = '\0';
  puVar1 = this->pad_200 + param_2 * 4 - 0x1c;
  puVar1[0] = '\0';
  puVar1[1] = '\0';
  puVar1[2] = '\0';
  puVar1[3] = '\0';
  if (param_2 == 0) {
    local_2c = this->panel_rect + panel_margin_x;
  }
  else if (param_2 == 1) {
    iVar2 = rect_width((iptr)&this->panel_rect);
    local_2c = this->panel_rect + iVar2 / 2 + panel_margin_x;
  }
  if (param_1 == 0xe) {
    local_28 = 1;
    switch(*(i32 *)(this->pad_200 + param_2 * 4 + 0xc)) {
    case 0:
      param_1 = 9;
      break;
    case 1:
      param_1 = 8;
      break;
    case 2:
      param_1 = 10;
      break;
    case 3:
      param_1 = 0x11;
      break;
    case 4:
      param_1 = 0xd;
      break;
    case 5:
      param_1 = 0xc;
      break;
    case 6:
      param_1 = 5;
    }
  }
  else if (param_1 == 0x10) {
    local_30 = 1;
    switch(this->field_214) {
    case 0:
      param_1 = 9;
      break;
    case 1:
      param_1 = 8;
      break;
    case 2:
      param_1 = 10;
      break;
    case 3:
      param_1 = 0x11;
      break;
    case 4:
      param_1 = 0xd;
      break;
    case 5:
      param_1 = 0xc;
      break;
    case 6:
      param_1 = 5;
    }
  }
  parley_clear_side_controls(this,param_2);
  *(int *)(this->pad_200 + param_2 * 4) = param_1;
  if (((parley_wnd_closed == 0) && (param_1 != 1)) && (param_1 != 0)) {
    if (param_1 == 0x14) {
      control_hide((Control *)this->field_348);
      ctrl_disable((Control *)this->field_348);
      control_hide((Control *)this->field_34c);
      ctrl_disable((Control *)this->field_34c);
      control_hide((Control *)this->field_350);
      ctrl_show_and_redraw((Control *)this->field_358);
      control_hide((Control *)this->field_354);
      ctrl_show_and_redraw((Control *)this->field_35c);
      ctrl_show_and_redraw((Control *)this->field_360);
    }
    else {
      ctrl_show_and_redraw((Control *)this->field_348);
      ctrl_enable((Control *)this->field_348);
      control_hide((Control *)this->field_34c);
      ctrl_disable((Control *)this->field_34c);
      ctrl_show_and_redraw((Control *)this->field_350);
      control_hide((Control *)this->field_358);
      ctrl_show_and_redraw((Control *)this->field_354);
      control_hide((Control *)this->field_35c);
      control_hide((Control *)this->field_360);
    }
  }
  switch(param_1) {
  case 0:
    break;
  case 1:
    if (((game.wonder_city[0x18] == -1) && (iVar2 = civ_has_wonder(human_civ,9), iVar2 == 0)
        ) && (game.reveal_map == '\0')) {
      local_c8 = 0;
    }
    else {
      local_c8 = 1;
    }
    local_cc = local_2c;
    local_d8 = this->panel_rect + panel_margin_x;
    local_3c = this->panel_top + panel_margin_y;
    local_38 = local_d8;
    iVar2 = rect_width((iptr)&this->panel_rect);
    local_34 = (iVar2 + panel_margin_x * -2) / 3;
    if (this->large_layout == 0) {
      local_370 = font_cached_height((GameFont *)&font_size16_bold);
    }
    else {
      local_370 = font_cached_height((GameFont *)&font_size24_bold);
    }
    local_14 = panel_margin_y * 2 + local_370;
    if (this->large_layout == 0) {
      local_220 = &font_size16_bold;
    }
    else {
      local_220 = &font_size24_bold;
    }
    ui_set_ctrl_font((iptr)local_220);
    pCVar6 = operator_new(0x3c);
    local_8 = 3;
    if (pCVar6 == (Control *)0x0) {
      local_228 = 0;
    }
    else {
      local_228 = checkbox_elem_ctor(pCVar6);
    }
    local_8 = 0xffffffff;
    this->field_2e8 = local_228;
    if (this == (ViewWindow *)0x0) {
      local_378 = (u8 *)0x0;
    }
    else {
      local_378 = this->pad_48;
    }
    iVar4 = label_string(*(i32 *)(label_string_ids + 0xba4));
    checkbox_create_fixed
              ((Control *)this->field_2e8,(iptr)local_378,0x415,local_38,local_3c,local_34,
               iVar4);
    checkbox_set_checked((Control *)this->field_2e8,chat_remain_anonymous);
    checkbox_enable((CheckboxEnableView *)this->field_2e8);
    checkbox_set_callback((CheckboxCallbackSetView *)this->field_2e8,ADDR(0x403d28, chat_on_send_checkbox));
    pCVar6 = operator_new(0x3c);
    local_8 = 4;
    if (pCVar6 == (Control *)0x0) {
      local_230 = 0;
    }
    else {
      local_230 = checkbox_elem_ctor(pCVar6);
    }
    local_8 = 0xffffffff;
    this->field_2ec = local_230;
    if (this == (ViewWindow *)0x0) {
      local_37c = (u8 *)0x0;
    }
    else {
      local_37c = this->pad_48;
    }
    iVar4 = label_string(*(i32 *)(label_string_ids + 0xd84));
    checkbox_create_fixed
              ((Control *)this->field_2ec,(iptr)local_37c,0x430,local_34 + local_38,local_3c,
               local_34,iVar4);
    checkbox_set_checked((Control *)this->field_2ec,chat_mute_anonymous);
    checkbox_enable((CheckboxEnableView *)this->field_2ec);
    checkbox_set_callback((CheckboxCallbackSetView *)this->field_2ec,ADDR(0x403d28, chat_on_send_checkbox));
    pCVar6 = operator_new(0x3c);
    local_8 = 5;
    if (pCVar6 == (Control *)0x0) {
      local_238 = 0;
    }
    else {
      local_238 = checkbox_elem_ctor(pCVar6);
    }
    local_8 = 0xffffffff;
    this->field_2f0 = local_238;
    if (this == (ViewWindow *)0x0) {
      local_380 = (u8 *)0x0;
    }
    else {
      local_380 = this->pad_48;
    }
    iVar4 = label_string(*(i32 *)(label_string_ids + 0xba8));
    checkbox_create_fixed
              ((Control *)this->field_2f0,(iptr)local_380,0x416,local_34 * 2 + local_38,
               local_3c,local_34,iVar4);
    checkbox_set_checked((Control *)this->field_2f0,chat_broadcast_all);
    checkbox_enable((CheckboxEnableView *)this->field_2f0);
    checkbox_set_callback((CheckboxCallbackSetView *)this->field_2f0,ADDR(0x403d28, chat_on_send_checkbox));
    local_3c += local_14;
    gfx_set_text_color_index(10);
    if (this->large_layout == 0) {
      local_23c = &font_size16_bold;
    }
    else {
      local_23c = &font_size24_bold;
    }
    uVar10 = 5;
    uVar9 = local_d8;
    iVar2 = local_3c;
    iVar4 = label_string(*(i32 *)(label_string_ids + 0xd2c));
    surface_draw_text((DibSurface *)this,(iptr)local_23c,iVar4,uVar9,iVar2,uVar10);
    if (this->large_layout == 0) {
      local_240 = &font_size16_bold;
    }
    else {
      local_240 = &font_size24_bold;
    }
    uVar10 = 5;
    iVar5 = local_cc - ((this->large_layout == 0) - 1 & 0x17);
    iVar2 = local_3c;
    iVar4 = label_string(*(i32 *)(label_string_ids + 0xd2c));
    surface_draw_text((DibSurface *)this,(iptr)local_240,iVar4,iVar5,iVar2,uVar10);
    local_38 = local_d8;
    if (this->large_layout == 0) {
      local_c4 = 5;
    }
    else {
      local_c4 = 0x17;
    }
    local_3c += local_14;
    iVar2 = rect_width((iptr)&this->panel_rect);
    local_34 = (iVar2 + panel_margin_x * -2) / 2;
    local_d4 = 0;
    for (civ = 1; civ < 8; civ++) {
      if (((human_civ == civ) ||
          ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) == 0)) ||
         (((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0 ||
          (((local_c8 == 0 && (mp_chat_from_start == 0)) &&
           ((*(byte *)&civs[civ].treaties[human_civ] & 1) == 0)))))) {
        *(i32 *)(&chat_send_to_civs + civ * 4) = 0;
        *(i32 *)(&chat_muted_civs + civ * 4) = 0;
      }
      else {
        pCVar6 = operator_new(0x3c);
        local_8 = 6;
        if (pCVar6 == (Control *)0x0) {
          local_248 = 0;
        }
        else {
          local_248 = checkbox_elem_ctor(pCVar6);
        }
        local_8 = 0xffffffff;
        *(i32 *)(this->pad_2c4 + civ * 4 + 4) = local_248;
        if (this == (ViewWindow *)0x0) {
          local_38c = (u8 *)0x0;
        }
        else {
          local_38c = this->pad_48;
        }
        checkbox_create_fixed
                  (*(Control **)(this->pad_2c4 + civ * 4 + 4),(iptr)local_38c,
                   civ + 0x428,local_38 + local_c4,local_3c,0x23,ADDR(0x6324dc, ((u8 *)&g.d_006324dc)));
        checkbox_set_checked
                  (*(Control **)(this->pad_2c4 + civ * 4 + 4),
                   *(i32 *)(&chat_muted_civs + civ * 4));
        checkbox_enable(*(CheckboxEnableView **)(this->pad_2c4 + civ * 4 + 4));
        checkbox_set_callback(*(CheckboxCallbackSetView **)(this->pad_2c4 + civ * 4 + 4),ADDR(0x403657, chat_on_mute_checkbox));
        pCVar6 = operator_new(0x3c);
        local_8 = 7;
        if (pCVar6 == (Control *)0x0) {
          local_250 = 0;
        }
        else {
          local_250 = checkbox_elem_ctor(pCVar6);
        }
        local_8 = 0xffffffff;
        *(i32 *)(this->pad_2c4 + civ * 4 - 0x1c) = local_250;
        if (this == (ViewWindow *)0x0) {
          local_390 = (u8 *)0x0;
        }
        else {
          local_390 = this->pad_48;
        }
        iVar4 = civ_adjective(civ);
        checkbox_create_fixed
                  (*(Control **)(this->pad_2c4 + civ * 4 - 0x1c),(iptr)local_390,
                   civ + 0x416,local_38 + local_c4 + 0x23,local_3c,
                   (local_34 - 0x23) - local_c4,iVar4);
        checkbox_set_checked
                  (*(Control **)(this->pad_2c4 + civ * 4 - 0x1c),
                   *(i32 *)(&chat_send_to_civs + civ * 4));
        checkbox_enable(*(CheckboxEnableView **)(this->pad_2c4 + civ * 4 - 0x1c));
        checkbox_set_callback
                  (*(CheckboxCallbackSetView **)(this->pad_2c4 + civ * 4 - 0x1c),ADDR(0x403d28, chat_on_send_checkbox));
        local_d4++;
        if ((local_d4 & 1) == 0) {
          local_38 = local_d8;
        }
        else {
          local_38 = local_cc;
        }
        if ((local_d4 & 1) == 0) {
          if (this->large_layout == 0) {
            local_c4 = 5;
          }
          else {
            local_c4 = 0x17;
          }
        }
        else if (this->large_layout == 0) {
          local_c4 = 5;
        }
        else {
          local_c4 = 0;
        }
        if ((local_d4 & 1) == 0) {
          local_3c += local_14;
        }
      }
    }
    break;
  case 2:
    local_b4[0] = label_string(*(i32 *)(label_string_ids + 0xb90));
    local_b4[1] = label_string(*(i32 *)(label_string_ids + 0xb94));
    local_b4[2] = label_string(*(i32 *)(label_string_ids + 0xb98));
    local_b4[3] = label_string(*(i32 *)(label_string_ids + 0xb9c));
    local_a4 = label_string(*(i32 *)(label_string_ids + 0xba0));
    gfx_set_text_color_index(10);
    if (this->large_layout == 0) {
      iVar4 = label_string(*(i32 *)(label_string_ids + 0xb8c));
      local_c0 = font_text_width((GameFont *)&font_size20,iVar4);
    }
    else {
      iVar4 = label_string(*(i32 *)(label_string_ids + 0xb8c));
      local_c0 = font_text_width((GameFont *)&font_size30,iVar4);
    }
    uVar7 = (this->panel_rect + (int)(this->panel_right - this->panel_rect) / 2) - local_c0 / 2;
    iVar2 = this->panel_top + panel_margin_y;
    if (this->large_layout == 0) {
      local_210 = &font_size20;
    }
    else {
      local_210 = &font_size30;
    }
    uVar10 = 5;
    local_3c = iVar2;
    local_38 = uVar7;
    iVar4 = label_string(*(i32 *)(label_string_ids + 0xb8c));
    surface_draw_text((DibSurface *)this,(iptr)local_210,iVar4,uVar7,iVar2,uVar10);
    if (this->large_layout == 0) {
      local_c0 = font_text_width((GameFont *)&font_size20,local_b4[0]);
    }
    else {
      local_c0 = font_text_width((GameFont *)&font_size30,local_b4[0]);
    }
    for (local_b8 = 1; local_b8 < 5; local_b8++) {
      if (this->large_layout == 0) {
        local_bc = font_text_width
                             ((GameFont *)&font_size20,local_b4[local_b8]);
      }
      else {
        local_bc = font_text_width
                             ((GameFont *)&font_size30,local_b4[local_b8]);
      }
      if (local_c0 < local_bc) {
        local_c0 = local_bc;
      }
    }
    local_2c = (this->panel_rect + (int)(this->panel_right - this->panel_rect) / 2) - local_c0 / 2;
    this->field_3ac = local_2c;
    if ((int)local_38 < (int)local_2c) {
      local_2c = local_38;
      this->field_3ac = local_38;
    }
    if (this->large_layout == 0) {
      local_214 = &font_size20;
    }
    else {
      local_214 = &font_size30;
    }
    ctrl_set_pending_font((iptr)local_214);
    pCVar3 = operator_new(0x50);
    local_8 = 2;
    if (pCVar3 == (InputControl *)0x0) {
      local_21c = 0;
    }
    else {
      local_21c = radiogrp_ctor(pCVar3);
    }
    local_8 = 0xffffffff;
    *(i32 *)(this->pad_364 + param_2 * 4 + 8) = local_21c;
    local_38 = local_2c;
    local_34 = local_c0 + local_c0 / 2;
    if (this->large_layout == 0) {
      local_364 = font_cached_height((GameFont *)&font_size20);
    }
    else {
      local_364 = font_cached_height((GameFont *)&font_size30);
    }
    local_3c = this->panel_top + panel_margin_y * 2 + local_364;
    local_14 = this->show_turn_timer - local_3c;
    SetRect(&local_24,local_38,local_3c,local_34 + local_38,local_14 + local_3c);
    if (this == (ViewWindow *)0x0) {
      local_368 = (u8 *)0x0;
    }
    else {
      local_368 = this->pad_48;
    }
    radiogrp_create
              (*(RadioGroup **)(this->pad_364 + param_2 * 4 + 8),(iptr)local_368,0x3f3,
               (iptr)&local_24,1,5,(iptr)local_b4);
    if (this->field_208 == 0xffffffff) {
      local_36c = 0;
    }
    else {
      local_36c = this->field_208;
    }
    radiogrp_set_selected(*(RadioGroupSetSelView **)(this->pad_364 + param_2 * 4 + 8),local_36c);
    radiogrp_set_dblclick_callback(*(Control **)(this->pad_364 + param_2 * 4 + 8),ADDR(0x401d75, parley_on_radio_dblclick))
    ;
    puVar1 = this->pad_200 + param_2 * 4 - 0x1c;
    puVar1[0] = 1;
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
    break;
  case 3:
    local_f4 = label_string(*(i32 *)(label_string_ids + 0xbac));
    local_f0 = label_string(*(i32 *)(label_string_ids + 0xbb0));
    local_ec = label_string(*(i32 *)(label_string_ids + 0xbb4));
    local_e8 = label_string(*(i32 *)(label_string_ids + 3000));
    local_e4 = label_string(*(i32 *)(label_string_ids + 0xbbc));
    local_e0 = label_string(*(i32 *)(label_string_ids + 0xbc0));
    local_dc = label_string(*(i32 *)(label_string_ids + 0xd08));
    gfx_set_text_color_index(10);
    local_38 = local_2c;
    iVar2 = this->panel_top + panel_margin_y;
    if (this->large_layout == 0) {
      local_254 = &font_size16_bold;
    }
    else {
      local_254 = &font_size24_bold;
    }
    uVar10 = 5;
    uVar8 = local_2c;
    local_3c = iVar2;
    iVar4 = label_string(*(i32 *)(label_string_ids + 0xc0c));
    surface_draw_text((DibSurface *)this,(iptr)local_254,iVar4,uVar8,iVar2,uVar10);
    if (this->large_layout == 0) {
      local_258 = &font_size16_bold;
    }
    else {
      local_258 = &font_size24_bold;
    }
    ctrl_set_pending_font((iptr)local_258);
    pCVar3 = operator_new(0x50);
    local_8 = 8;
    if (pCVar3 == (InputControl *)0x0) {
      local_260 = 0;
    }
    else {
      local_260 = radiogrp_ctor(pCVar3);
    }
    local_8 = 0xffffffff;
    *(i32 *)(this->pad_364 + param_2 * 4 + 8) = local_260;
    local_38 = local_2c;
    iVar2 = rect_width((iptr)&this->panel_rect);
    local_34 = (iVar2 + panel_margin_x * -2) / 2;
    if (this->large_layout == 0) {
      local_39c = font_cached_height((GameFont *)&font_size16);
    }
    else {
      local_39c = font_cached_height((GameFont *)&font_size24);
    }
    local_3c = this->panel_top + panel_margin_y + local_39c;
    SetRect(&local_24,local_38,local_3c,local_34 + local_38,this->show_turn_timer);
    if (this == (ViewWindow *)0x0) {
      local_3a0 = (u8 *)0x0;
    }
    else {
      local_3a0 = this->pad_48;
    }
    radiogrp_create
              (*(RadioGroup **)(this->pad_364 + param_2 * 4 + 8),(iptr)local_3a0,0x3f4,
               (iptr)&local_24,1,7,(iptr)&local_f4);
    if (this->right_exchange_kind == 0) {
      radiogrp_disable_item(*(RadioGroupDisableView **)(this->pad_364 + param_2 * 4 + 8),0);
    }
    else if (this->right_exchange_kind == 6) {
      radiogrp_disable_item(*(RadioGroupDisableView **)(this->pad_364 + param_2 * 4 + 8),6);
    }
    radiogrp_set_selected
              (*(RadioGroupSetSelView **)(this->pad_364 + param_2 * 4 + 8),this->left_exchange_kind);
    radiogrp_set_dblclick_callback(*(Control **)(this->pad_364 + param_2 * 4 + 8),ADDR(0x401d75, parley_on_radio_dblclick))
    ;
    radiogrp_set_select_callback(*(Control **)(this->pad_364 + param_2 * 4 + 8),ADDR(0x4035d0, parley_on_exchange_kind_select))
    ;
    puVar1 = this->pad_200 + param_2 * 4 - 0x1c;
    puVar1[0] = 1;
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
    break;
  case 4:
    local_110 = label_string(*(i32 *)(label_string_ids + 0xbac));
    local_10c = label_string(*(i32 *)(label_string_ids + 0xbb0));
    local_108 = label_string(*(i32 *)(label_string_ids + 0xbb4));
    local_104 = label_string(*(i32 *)(label_string_ids + 3000));
    local_100 = label_string(*(i32 *)(label_string_ids + 0xbbc));
    local_fc = label_string(*(i32 *)(label_string_ids + 0xbc4));
    local_f8 = label_string(*(i32 *)(label_string_ids + 0xd08));
    gfx_set_text_color_index(10);
    local_38 = local_2c;
    iVar2 = this->panel_top + panel_margin_y;
    if (this->large_layout == 0) {
      local_264 = &font_size16_bold;
    }
    else {
      local_264 = &font_size24_bold;
    }
    uVar10 = 5;
    uVar8 = local_2c;
    local_3c = iVar2;
    iVar4 = label_string(*(i32 *)(label_string_ids + 0xc10));
    surface_draw_text((DibSurface *)this,(iptr)local_264,iVar4,uVar8,iVar2,uVar10);
    if (this->large_layout == 0) {
      local_268 = &font_size16_bold;
    }
    else {
      local_268 = &font_size24_bold;
    }
    ctrl_set_pending_font((iptr)local_268);
    pCVar3 = operator_new(0x50);
    local_8 = 9;
    if (pCVar3 == (InputControl *)0x0) {
      local_270 = 0;
    }
    else {
      local_270 = radiogrp_ctor(pCVar3);
    }
    local_8 = 0xffffffff;
    *(i32 *)(this->pad_364 + param_2 * 4 + 8) = local_270;
    iVar2 = rect_width((iptr)&this->panel_rect);
    local_34 = (iVar2 + panel_margin_x * -2) / 2;
    local_38 = local_2c;
    if (this->large_layout == 0) {
      local_3ac = font_cached_height((GameFont *)&font_size16);
    }
    else {
      local_3ac = font_cached_height((GameFont *)&font_size24);
    }
    local_3c = this->panel_top + panel_margin_y + local_3ac;
    SetRect(&local_24,local_38,local_3c,local_34 + local_38,this->show_turn_timer);
    if (this == (ViewWindow *)0x0) {
      local_3b0 = (u8 *)0x0;
    }
    else {
      local_3b0 = this->pad_48;
    }
    radiogrp_create
              (*(RadioGroup **)(this->pad_364 + param_2 * 4 + 8),(iptr)local_3b0,0x3f5,
               (iptr)&local_24,1,7,(iptr)&local_110);
    if (this->left_exchange_kind == 0) {
      radiogrp_disable_item(*(RadioGroupDisableView **)(this->pad_364 + param_2 * 4 + 8),0);
    }
    else if (this->left_exchange_kind == 6) {
      radiogrp_disable_item(*(RadioGroupDisableView **)(this->pad_364 + param_2 * 4 + 8),6);
    }
    radiogrp_set_selected
              (*(RadioGroupSetSelView **)(this->pad_364 + param_2 * 4 + 8),this->right_exchange_kind);
    radiogrp_set_dblclick_callback(*(Control **)(this->pad_364 + param_2 * 4 + 8),ADDR(0x401d75, parley_on_radio_dblclick))
    ;
    radiogrp_set_select_callback(*(Control **)(this->pad_364 + param_2 * 4 + 8),ADDR(0x4035d0, parley_on_exchange_kind_select))
    ;
    puVar1 = this->pad_200 + param_2 * 4 - 0x1c;
    puVar1[0] = 1;
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
    break;
  case 5:
    local_120 = label_string(*(i32 *)(label_string_ids + 0xbcc));
    local_11c = label_string(*(i32 *)(label_string_ids + 0xbd0));
    local_118 = label_string(*(i32 *)(label_string_ids + 0xbd4));
    local_114 = label_string(*(i32 *)(label_string_ids + 0xbd8));
    gfx_set_text_color_index(10);
    local_38 = local_2c;
    local_3c = this->panel_top + panel_margin_y;
    iVar2 = rect_width((iptr)&this->panel_rect);
    local_34 = (iVar2 + panel_margin_x * -2) / 2 + panel_margin_x * -5;
    if ((local_28 != '\0') || (local_30 != '\0')) {
      str_clear(ADDR(0x679640, ((u8 *)&g.d_00679640)));
      if (param_2 == 0) {
        local_3b4 = label_string(*(i32 *)(label_string_ids + 0xc0c));
      }
      else {
        local_3b4 = label_string(*(i32 *)(label_string_ids + 0xc10));
      }
      text_append_str(local_3b4);
      if (this->large_layout == 0) {
        local_274 = &font_size16_bold;
      }
      else {
        local_274 = &font_size24_bold;
      }
      surface_draw_text
                ((DibSurface *)this,(iptr)local_274,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_38,local_3c,5);
      if (this->large_layout == 0) {
        local_3bc = font_cached_height((GameFont *)&font_size16_bold);
      }
      else {
        local_3bc = font_cached_height((GameFont *)&font_size24_bold);
      }
      local_3c = local_3c + panel_margin_y + local_3bc;
    }
    if ((local_28 == '\0') && (local_30 == '\0')) {
      if (this->large_layout == 0) {
        local_3c4 = font_cached_height((GameFont *)&font_size16_bold);
      }
      else {
        local_3c4 = font_cached_height((GameFont *)&font_size24_bold);
      }
      local_14 = local_3c4 * 5 + panel_margin_y * 4;
    }
    else {
      if (this->large_layout == 0) {
        local_3c0 = font_cached_height((GameFont *)&font_size16_bold);
      }
      else {
        local_3c0 = font_cached_height((GameFont *)&font_size24_bold);
      }
      local_14 = panel_margin_y * 3 + local_3c0 * 4;
    }
    local_3c = this->panel_top + (int)((this->show_turn_timer - this->panel_top) - local_14) / 2;
    if (local_30 == '\0' && local_28 == '\0') {
      local_3c8 = label_string(*(i32 *)(label_string_ids + 0xb90));
    }
    else {
      local_3c8 = label_string(*(i32 *)(label_string_ids + 0xd08));
    }
    if (this->large_layout == 0) {
      local_278 = &font_size16_bold;
    }
    else {
      local_278 = &font_size24_bold;
    }
    surface_draw_text((DibSurface *)this,(iptr)local_278,local_3c8,local_38,local_3c,5)
    ;
    if (this->large_layout == 0) {
      local_27c = &font_size16_bold;
    }
    else {
      local_27c = &font_size24_bold;
    }
    ctrl_set_pending_font((iptr)local_27c);
    pCVar3 = operator_new(0x50);
    local_8 = 10;
    if (pCVar3 == (InputControl *)0x0) {
      local_284 = 0;
    }
    else {
      local_284 = radiogrp_ctor(pCVar3);
    }
    local_8 = 0xffffffff;
    *(i32 *)(this->pad_364 + param_2 * 4 + 8) = local_284;
    local_38 = local_2c;
    if (this->large_layout == 0) {
      local_3d4 = font_cached_height((GameFont *)&font_size16_bold);
    }
    else {
      local_3d4 = font_cached_height((GameFont *)&font_size24_bold);
    }
    local_3c = local_3c + panel_margin_y + local_3d4;
    if ((local_28 == '\0') && (local_30 == '\0')) {
      if (this->large_layout == 0) {
        local_3dc = font_cached_height((GameFont *)&font_size16_bold);
      }
      else {
        local_3dc = font_cached_height((GameFont *)&font_size24_bold);
      }
      local_14 = panel_margin_y * 3 + local_3dc * 4;
    }
    else {
      if (this->large_layout == 0) {
        local_3d8 = font_cached_height((GameFont *)&font_size16_bold);
      }
      else {
        local_3d8 = font_cached_height((GameFont *)&font_size24_bold);
      }
      local_14 = local_3d8 * 3 + panel_margin_y * 2;
    }
    SetRect(&local_24,local_38,local_3c,local_34 + local_38,local_14 + local_3c);
    if (this == (ViewWindow *)0x0) {
      local_3e0 = (u8 *)0x0;
    }
    else {
      local_3e0 = this->pad_48;
    }
    radiogrp_create
              (*(RadioGroup **)(this->pad_364 + param_2 * 4 + 8),(iptr)local_3e0,0x3f6,
               (iptr)&local_24,1,(local_30 == '\0' && local_28 == '\0') + 3,(iptr)&local_120);
    if (((*(byte *)&civs[human_civ].treaties[(this->caption_height)] & 2) != 0) &&
       (radiogrp_disable_item(*(RadioGroupDisableView **)(this->pad_364 + param_2 * 4 + 8),0),
       this->treaty_type_choice == 0)) {
      this->treaty_type_choice++;
    }
    if (((*(byte *)&civs[human_civ].treaties[(this->caption_height)] & 4) != 0) &&
       (radiogrp_disable_item(*(RadioGroupDisableView **)(this->pad_364 + param_2 * 4 + 8),1),
       this->treaty_type_choice == 1)) {
      this->treaty_type_choice++;
    }
    if (((*(byte *)&civs[human_civ].treaties[(this->caption_height)] & 8) != 0) &&
       (radiogrp_disable_item(*(RadioGroupDisableView **)(this->pad_364 + param_2 * 4 + 8),2),
       this->treaty_type_choice == 2)) {
      if (local_30 == '\0' && local_28 == '\0') {
        this->treaty_type_choice = 3;
      }
      else {
        this->treaty_type_choice = 0;
      }
    }
    if ((((local_28 == '\0') && (local_30 == '\0')) &&
        ((*(byte *)&civs[human_civ].treaties[(this->caption_height)] & 0xe) == 0)) &&
       (radiogrp_disable_item(*(RadioGroupDisableView **)(this->pad_364 + param_2 * 4 + 8),3),
       this->treaty_type_choice == 3)) {
      this->treaty_type_choice = 0;
    }
    radiogrp_set_selected
              (*(RadioGroupSetSelView **)(this->pad_364 + param_2 * 4 + 8),this->treaty_type_choice);
    radiogrp_set_dblclick_callback(*(Control **)(this->pad_364 + param_2 * 4 + 8),ADDR(0x401d75, parley_on_radio_dblclick))
    ;
    radiogrp_set_select_callback(*(Control **)(this->pad_364 + param_2 * 4 + 8),ADDR(0x403c2e, parley_on_treaty_type_select))
    ;
    puVar1 = this->pad_200 + param_2 * 4 - 0x1c;
    puVar1[0] = 1;
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
    break;
  case 6:
    gfx_set_text_color_index(10);
    local_38 = local_2c;
    iVar2 = rect_width((iptr)&this->panel_rect);
    local_34 = (iVar2 + panel_margin_x * -2) / 2 - panel_margin_x;
    if (this->large_layout == 0) {
      local_3e4 = font_cached_height((GameFont *)&font_size16_bold);
    }
    else {
      local_3e4 = font_cached_height((GameFont *)&font_size24_bold);
    }
    if (this->large_layout == 0) {
      local_3e8 = font_cached_height((GameFont *)&font_size16_bold);
    }
    else {
      local_3e8 = font_cached_height((GameFont *)&font_size24_bold);
    }
    local_14 = panel_margin_y * 2 + local_3e4 * 4 + local_3e8;
    local_3c = this->panel_top + (int)((this->show_turn_timer - this->panel_top) - local_14) / 2;
    SetRect(&local_24,local_38,local_3c,local_34 + local_38,local_14 + local_3c);
    gfx_set_draw_target(ADDR(0x67a7a8, ((u8 *)&g.d_0067a7a8)));
    gfx_target_frame_rect((iptr)&local_24,10);
    rect_deflate((iptr)&local_24,1,1);
    gfx_target_frame_rect((iptr)&local_24,10);
    iVar2 = rect_width((iptr)&local_24);
    local_38 = local_24.left + iVar2 / 2;
    if (this->large_layout == 0) {
      local_3ec = font_cached_height((GameFont *)&font_size16_bold);
    }
    else {
      local_3ec = font_cached_height((GameFont *)&font_size24_bold);
    }
    iVar2 = local_3c + panel_margin_y + local_3ec / 2;
    if (this->large_layout == 0) {
      local_288 = &font_size16_bold;
    }
    else {
      local_288 = &font_size24_bold;
    }
    uVar10 = 0;
    uVar9 = local_38;
    local_3c = iVar2;
    iVar4 = label_string(*(i32 *)(label_string_ids + 0xbdc));
    surface_draw_text((DibSurface *)this,(iptr)local_288,iVar4,uVar9,iVar2,uVar10);
    local_24.bottom += panel_margin_y * -2;
    local_24.left += panel_margin_x * 2;
    local_24.right += panel_margin_x * -2;
    if (this->large_layout == 0) {
      local_3f4 = font_cached_height((GameFont *)&font_size16_bold);
    }
    else {
      local_3f4 = font_cached_height((GameFont *)&font_size24_bold);
    }
    local_24.top = local_24.top + panel_margin_y + local_3f4;
    gfx_target_frame_rect((iptr)&local_24,10);
    rect_deflate((iptr)&local_24,1,1);
    surface_fill_rect((DibSurface *)this,(iptr)&local_24,list_bg_color);
    iVar2 = rect_width((iptr)&local_24);
    local_38 = local_24.left + iVar2 / 2;
    iVar2 = rect_height((iptr)&local_24);
    local_3c = local_24.top + iVar2 / 2;
    text_clear();
    if ((*(byte *)&civs[human_civ].treaties[(this->caption_height)] & 8) == 0) {
      if ((*(byte *)&civs[human_civ].treaties[(this->caption_height)] & 4) == 0) {
        if ((*(byte *)&civs[human_civ].treaties[(this->caption_height)] & 2) == 0) {
          if ((*(byte *)(human_civ * 0x594 + ADDR(0x64c6c1, ((u8 *)&civs + 33)) + this->caption_height * 4) & 0x20) == 0) {
            iVar4 = label_string(*(i32 *)(label_string_ids + 0xbec));
            text_append(iVar4);
          }
          else {
            iVar4 = label_string(*(i32 *)(label_string_ids + 0xbe8));
            text_append(iVar4);
          }
        }
        else {
          iVar4 = label_string(*(i32 *)(label_string_ids + 0xbcc));
          text_append(iVar4);
        }
      }
      else {
        iVar4 = label_string(*(i32 *)(label_string_ids + 0xbe4));
        text_append(iVar4);
      }
    }
    else {
      iVar4 = label_string(*(i32 *)(label_string_ids + 0xbe0));
      text_append(iVar4);
    }
    if (this->large_layout == 0) {
      local_28c = &font_size16_bold;
    }
    else {
      local_28c = &font_size24_bold;
    }
    surface_draw_text((DibSurface *)this,(iptr)local_28c,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_38,local_3c,0);
    puVar1 = this->pad_200 + param_2 * 4 - 0x1c;
    puVar1[0] = 1;
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
    break;
  case 7:
    local_134 = label_string(*(i32 *)(label_string_ids + 0xbf4));
    local_130 = label_string(*(i32 *)(label_string_ids + 0xbf8));
    local_12c = label_string(*(i32 *)(label_string_ids + 0xbfc));
    local_128 = label_string(*(i32 *)(label_string_ids + 0xc00));
    local_124 = label_string(*(i32 *)(label_string_ids + 0xc04));
    gfx_set_text_color_index(10);
    local_38 = local_2c;
    if (this->large_layout == 0) {
      local_3fc = font_cached_height((GameFont *)&font_size16_bold);
    }
    else {
      local_3fc = font_cached_height((GameFont *)&font_size24_bold);
    }
    if (this->large_layout == 0) {
      local_400 = font_cached_height((GameFont *)&font_size16_bold);
    }
    else {
      local_400 = font_cached_height((GameFont *)&font_size24_bold);
    }
    local_14 = panel_margin_y * 5 + local_3fc * 5 + local_400;
    iVar2 = this->panel_top + (int)((this->show_turn_timer - this->panel_top) - local_14) / 2;
    if (this->large_layout == 0) {
      local_290 = &font_size16_bold;
    }
    else {
      local_290 = &font_size24_bold;
    }
    uVar10 = 5;
    uVar9 = local_38;
    local_3c = iVar2;
    iVar4 = label_string(*(i32 *)(label_string_ids + 0xbf0));
    surface_draw_text((DibSurface *)this,(iptr)local_290,iVar4,uVar9,iVar2,uVar10);
    if (this->large_layout == 0) {
      local_294 = &font_size16_bold;
    }
    else {
      local_294 = &font_size24_bold;
    }
    ctrl_set_pending_font((iptr)local_294);
    pCVar3 = operator_new(0x50);
    local_8 = 0xb;
    if (pCVar3 == (InputControl *)0x0) {
      local_29c = 0;
    }
    else {
      local_29c = radiogrp_ctor(pCVar3);
    }
    local_8 = 0xffffffff;
    *(i32 *)(this->pad_364 + param_2 * 4 + 8) = local_29c;
    local_38 = local_2c;
    iVar2 = rect_width((iptr)&this->panel_rect);
    local_34 = (iVar2 + panel_margin_x * -2) / 2;
    if (this->large_layout == 0) {
      local_40c = font_cached_height((GameFont *)&font_size16_bold);
    }
    else {
      local_40c = font_cached_height((GameFont *)&font_size24_bold);
    }
    local_3c = local_3c + panel_margin_y + local_40c;
    if (this->large_layout == 0) {
      local_410 = font_cached_height((GameFont *)&font_size16_bold);
    }
    else {
      local_410 = font_cached_height((GameFont *)&font_size24_bold);
    }
    local_14 = local_410 * 5 + panel_margin_y * 4;
    SetRect(&local_24,local_38,local_3c,local_34 + local_38,local_14 + local_3c);
    if (this == (ViewWindow *)0x0) {
      local_414 = (u8 *)0x0;
    }
    else {
      local_414 = this->pad_48;
    }
    radiogrp_create
              (*(RadioGroup **)(this->pad_364 + param_2 * 4 + 8),(iptr)local_414,0x3f7,
               (iptr)&local_24,1,5,(iptr)&local_134);
    radiogrp_set_selected
              (*(RadioGroupSetSelView **)(this->pad_364 + param_2 * 4 + 8),this->field_220);
    radiogrp_set_dblclick_callback(*(Control **)(this->pad_364 + param_2 * 4 + 8),ADDR(0x401d75, parley_on_radio_dblclick))
    ;
    radiogrp_set_select_callback(*(Control **)(this->pad_364 + param_2 * 4 + 8),ADDR(0x4010ff, parley_on_gift_kind_select))
    ;
    puVar1 = this->pad_200 + param_2 * 4 - 0x1c;
    puVar1[0] = 1;
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
    break;
  case 8:
    if (local_28 == '\0') {
      puVar1 = this[0x3e].pad_48 + param_2 * 4 + 0x38;
      puVar1[0] = 7;
      puVar1[1] = '\0';
      puVar1[2] = '\0';
      puVar1[3] = '\0';
    }
    else {
      puVar1 = this[0x3e].pad_48 + param_2 * 4 + 0x38;
      puVar1[0] = 6;
      puVar1[1] = '\0';
      puVar1[2] = '\0';
      puVar1[3] = '\0';
    }
    gfx_set_text_color_index(10);
    local_38 = local_2c;
    local_3c = this->panel_top + panel_margin_y;
    iVar2 = rect_width((iptr)&this->panel_rect);
    local_34 = (iVar2 + panel_margin_x * -2) / 2 + panel_margin_x * -5;
    if (local_28 != '\0') {
      str_clear(ADDR(0x679640, ((u8 *)&g.d_00679640)));
      if (param_2 == 0) {
        local_418 = label_string(*(i32 *)(label_string_ids + 0xc0c));
      }
      else {
        local_418 = label_string(*(i32 *)(label_string_ids + 0xc10));
      }
      text_append_str(local_418);
      if (this->large_layout == 0) {
        local_2a0 = &font_size16_bold;
      }
      else {
        local_2a0 = &font_size24_bold;
      }
      surface_draw_text
                ((DibSurface *)this,(iptr)local_2a0,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_38,local_3c,5);
      if (this->large_layout == 0) {
        local_420 = font_cached_height((GameFont *)&font_size16_bold);
      }
      else {
        local_420 = font_cached_height((GameFont *)&font_size24_bold);
      }
      local_3c = local_3c + panel_margin_y + local_420;
    }
    SetRect(&local_24,local_38,local_3c,local_34 + local_38,this->show_turn_timer);
    gfx_set_draw_target(ADDR(0x67a7a8, ((u8 *)&g.d_0067a7a8)));
    gfx_target_frame_rect((iptr)&local_24,10);
    rect_deflate((iptr)&local_24,1,1);
    gfx_target_frame_rect((iptr)&local_24,10);
    iVar2 = rect_width((iptr)&local_24);
    local_38 = local_24.left + iVar2 / 2;
    if (this->large_layout == 0) {
      local_424 = font_cached_height((GameFont *)&font_size16_bold);
    }
    else {
      local_424 = font_cached_height((GameFont *)&font_size24_bold);
    }
    iVar2 = local_3c + local_424 / 2;
    if (this->large_layout == 0) {
      local_2a4 = &font_size16_bold;
    }
    else {
      local_2a4 = &font_size24_bold;
    }
    uVar10 = 0;
    uVar9 = local_38;
    local_3c = iVar2;
    iVar4 = label_string(*(i32 *)(label_string_ids + 0xc08));
    surface_draw_text((DibSurface *)this,(iptr)local_2a4,iVar4,uVar9,iVar2,uVar10);
    if (this->large_layout == 0) {
      iVar2 = font_cached_height((GameFont *)&font_size16_bold);
      local_24.top += iVar2;
    }
    else {
      iVar2 = font_cached_height((GameFont *)&font_size24_bold);
      local_24.top += iVar2;
    }
    local_24.bottom = this->show_turn_timer + panel_margin_y * -2;
    local_24.left += panel_margin_x * 2;
    local_24.right += panel_margin_x * -2;
    gfx_target_frame_rect((iptr)&local_24,10);
    rect_deflate((iptr)&local_24,1,1);
    surface_fill_rect((DibSurface *)this,(iptr)&local_24,list_bg_color);
    local_138 = 0;
    if ((local_30 != '\0') || ((local_28 != '\0' && (param_2 == 1)))) {
      local_138 = 1;
    }
    parley_create_advance_list_pane((WindowObjectView *)this,(iptr)&local_24,param_2,local_138);
    break;
  case 9:
    gfx_set_text_color_index(10);
    local_38 = local_2c;
    iVar2 = rect_width((iptr)&this->panel_rect);
    local_34 = (iVar2 + panel_margin_x * -2) / 2 + panel_margin_x * -5;
    if (this->large_layout == 0) {
      local_42c = font_cached_height((GameFont *)&font_size14);
    }
    else {
      local_42c = font_cached_height((GameFont *)&font_size21);
    }
    if (this->large_layout == 0) {
      local_430 = font_cached_height((GameFont *)&font_size16_bold);
    }
    else {
      local_430 = font_cached_height((GameFont *)&font_size24_bold);
    }
    local_14 = panel_margin_y * 2 + local_42c * 4 + local_430;
    local_3c = this->panel_top + (int)((this->show_turn_timer - this->panel_top) - local_14) / 2;
    if (local_28 != '\0') {
      str_clear(ADDR(0x679640, ((u8 *)&g.d_00679640)));
      if (param_2 == 0) {
        local_434 = label_string(*(i32 *)(label_string_ids + 0xc0c));
      }
      else {
        local_434 = label_string(*(i32 *)(label_string_ids + 0xc10));
      }
      text_append_str(local_434);
      if (this->large_layout == 0) {
        local_2a8 = &font_size16_bold;
      }
      else {
        local_2a8 = &font_size24_bold;
      }
      surface_draw_text
                ((DibSurface *)this,(iptr)local_2a8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_38,
                 this->panel_top + panel_margin_y,5);
    }
    SetRect(&local_24,local_38,local_3c,local_34 + local_38,local_14 + local_3c);
    gfx_set_draw_target(ADDR(0x67a7a8, ((u8 *)&g.d_0067a7a8)));
    gfx_target_frame_rect((iptr)&local_24,10);
    rect_deflate((iptr)&local_24,1,1);
    gfx_target_frame_rect((iptr)&local_24,10);
    iVar2 = rect_width((iptr)&local_24);
    local_38 = local_24.left + iVar2 / 2;
    if (this->large_layout == 0) {
      local_43c = font_cached_height((GameFont *)&font_size16_bold);
    }
    else {
      local_43c = font_cached_height((GameFont *)&font_size24_bold);
    }
    local_3c = local_3c + panel_margin_y + local_43c / 2;
    str_clear(ADDR(0x679640, ((u8 *)&g.d_00679640)));
    if (local_30 == '\0') {
      iVar4 = label_string(*(i32 *)(label_string_ids + 0xc18));
      text_append_str(iVar4);
      text_append_space();
      text_append_int(civs[human_civ].gold);
      text_append_space();
      iVar4 = label_string(*(i32 *)(label_string_ids + 0xc1c));
      text_append_str(iVar4);
    }
    else {
      iVar4 = label_string(*(i32 *)(label_string_ids + 0xc14));
      text_append_str(iVar4);
    }
    if (this->large_layout == 0) {
      local_2ac = &font_size16_bold;
    }
    else {
      local_2ac = &font_size24_bold;
    }
    surface_draw_text((DibSurface *)this,(iptr)local_2ac,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_38,local_3c,0);
    local_24.bottom += panel_margin_y * -2;
    local_24.left += panel_margin_x * 2;
    local_24.right += panel_margin_x * -2;
    if (this->large_layout == 0) {
      local_444 = font_cached_height((GameFont *)&font_size16_bold);
    }
    else {
      local_444 = font_cached_height((GameFont *)&font_size24_bold);
    }
    local_24.top = local_24.top + panel_margin_y + local_444;
    gfx_target_frame_rect((iptr)&local_24,10);
    rect_deflate((iptr)&local_24,1,1);
    surface_fill_rect((DibSurface *)this,(iptr)&local_24,list_bg_color);
    str_clear(ADDR(0x679640, ((u8 *)&g.d_00679640)));
    text_append_str(ADDR(0x6324e0, ((u8 *)&g.d_006324e0)));
    if (this->large_layout == 0) {
      local_448 = font_text_width((GameFont *)&font_size16_bold,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    }
    else {
      local_448 = font_text_width((GameFont *)&font_size24_bold,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    }
    local_34 = (local_448 * 3) / 2;
    str_clear(ADDR(0x679640, ((u8 *)&g.d_00679640)));
    iVar4 = label_string(*(i32 *)(label_string_ids + 0xc20));
    text_append_str(iVar4);
    text_append_space();
    if (this->large_layout == 0) {
      local_44c = font_text_width((GameFont *)&font_size16_bold,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    }
    else {
      local_44c = font_text_width((GameFont *)&font_size24_bold,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    }
    iVar2 = rect_width((iptr)&local_24);
    local_38 = (local_24.left + iVar2 / 2) - (local_34 + local_44c) / 2;
    iVar2 = rect_height((iptr)&local_24);
    local_3c = local_24.top + iVar2 / 2;
    if (this->large_layout == 0) {
      local_2b0 = &font_size16_bold;
    }
    else {
      local_2b0 = &font_size24_bold;
    }
    surface_draw_text((DibSurface *)this,(iptr)local_2b0,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_38,local_3c,1);
    pCVar3 = operator_new(0x48);
    local_8 = 0xc;
    if (pCVar3 == (InputControl *)0x0) {
      local_2b8 = 0;
    }
    else {
      local_2b8 = edit_ctor(pCVar3);
    }
    local_8 = 0xffffffff;
    *(i32 *)(this->pad_364 + param_2 * 4 + 0x10) = local_2b8;
    if (this->large_layout == 0) {
      local_2bc = &font_size16_bold;
    }
    else {
      local_2bc = &font_size24_bold;
    }
    ui_set_default_font((iptr)local_2bc);
    if (this->large_layout == 0) {
      iVar2 = font_text_width((GameFont *)&font_size16_bold,ADDR(0x679640, ((u8 *)&g.d_00679640)));
      local_38 += iVar2;
    }
    else {
      iVar2 = font_text_width((GameFont *)&font_size24_bold,ADDR(0x679640, ((u8 *)&g.d_00679640)));
      local_38 += iVar2;
    }
    if (this->large_layout == 0) {
      local_14 = font_cached_height((GameFont *)&font_size16_bold);
    }
    else {
      local_14 = font_cached_height((GameFont *)&font_size24_bold);
    }
    local_3c -= local_14 / 2;
    SetRect(&local_24,local_38,local_3c,local_34 + local_38,local_14 + local_3c);
    __itoa(*(int *)(this->pad_23c + param_2 * 4 - 0x10),local_158,10);
    if (this == (ViewWindow *)0x0) {
      local_458 = (u8 *)0x0;
    }
    else {
      local_458 = this->pad_48;
    }
    edit_create
              (*(EditControl **)(this->pad_364 + param_2 * 4 + 0x10),(iptr)local_458,
               param_2 + 0x3f8,(iptr)&local_24,(iptr)local_158);
    edit_set_max_len(*(EditMaxLenView **)(this->pad_364 + param_2 * 4 + 0x10),6);
    edit_set_change_callback(*(EditChangeSetView **)(this->pad_364 + param_2 * 4 + 0x10),ADDR(0x4020e5, parley_gold_edit_on_change));
    ctrl_set_focus(*(ControlFocusView **)(this->pad_364 + param_2 * 4 + 0x10));
    break;
  case 10:
    if (local_28 == '\0') {
      puVar1 = this[0x3e].pad_48 + param_2 * 4 + 0x38;
      puVar1[0] = 6;
      puVar1[1] = '\0';
      puVar1[2] = '\0';
      puVar1[3] = '\0';
    }
    else {
      puVar1 = this[0x3e].pad_48 + param_2 * 4 + 0x38;
      puVar1[0] = 5;
      puVar1[1] = '\0';
      puVar1[2] = '\0';
      puVar1[3] = '\0';
    }
    gfx_set_text_color_index(10);
    local_38 = local_2c;
    local_3c = this->panel_top + panel_margin_y;
    iVar2 = rect_width((iptr)&this->panel_rect);
    local_34 = (iVar2 + panel_margin_x * -2) / 2 + panel_margin_x * -5;
    if (local_28 != '\0') {
      str_clear(ADDR(0x679640, ((u8 *)&g.d_00679640)));
      if (param_2 == 0) {
        local_45c = label_string(*(i32 *)(label_string_ids + 0xc0c));
      }
      else {
        local_45c = label_string(*(i32 *)(label_string_ids + 0xc10));
      }
      text_append_str(local_45c);
      if (this->large_layout == 0) {
        local_2c0 = &font_size16_bold;
      }
      else {
        local_2c0 = &font_size24_bold;
      }
      surface_draw_text
                ((DibSurface *)this,(iptr)local_2c0,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_38,local_3c,5);
      if (this->large_layout == 0) {
        local_464 = font_cached_height((GameFont *)&font_size16_bold);
      }
      else {
        local_464 = font_cached_height((GameFont *)&font_size24_bold);
      }
      local_3c = local_3c + panel_margin_y + local_464;
    }
    SetRect(&local_24,local_38,local_3c,local_34 + local_38,this->show_turn_timer);
    gfx_set_draw_target(ADDR(0x67a7a8, ((u8 *)&g.d_0067a7a8)));
    gfx_target_frame_rect((iptr)&local_24,10);
    rect_deflate((iptr)&local_24,1,1);
    gfx_target_frame_rect((iptr)&local_24,10);
    iVar2 = rect_width((iptr)&local_24);
    local_38 = local_24.left + iVar2 / 2;
    if (this->large_layout == 0) {
      local_468 = font_cached_height((GameFont *)&font_size16_bold);
    }
    else {
      local_468 = font_cached_height((GameFont *)&font_size24_bold);
    }
    iVar2 = local_3c + local_468 / 2;
    local_3c = iVar2;
    if (local_28 == '\0') {
      if (this->large_layout == 0) {
        local_2c4 = &font_size16_bold;
      }
      else {
        local_2c4 = &font_size24_bold;
      }
      uVar10 = 0;
      uVar9 = local_38;
      iVar4 = label_string(*(i32 *)(label_string_ids + 0xc24));
      surface_draw_text((DibSurface *)this,(iptr)local_2c4,iVar4,uVar9,iVar2,uVar10);
    }
    if ((local_28 == '\0') && (local_30 == '\0')) {
      if (this->large_layout == 0) {
        local_488 = font_cached_height((GameFont *)&font_size16_bold);
      }
      else {
        local_488 = font_cached_height((GameFont *)&font_size24_bold);
      }
      local_164 = local_24.top + local_488;
      local_168 = local_34 / 2;
      if (this->large_layout == 0) {
        local_48c = font_line_spacing((GameFont *)&font_size16);
      }
      else {
        local_48c = font_line_spacing((GameFont *)&font_size24);
      }
      local_160 = panel_padding_y * 2 + local_48c;
      SetRect(&local_17c,panel_margin_x * 2 + local_24.left,local_164,local_24.left + local_168,
              local_164 + local_160);
    }
    else {
      local_164 = panel_margin_y * 2 + local_24.top - 1;
      if (this->large_layout == 0) {
        local_470 = font_cached_height((GameFont *)&font_size16_bold);
      }
      else {
        local_470 = font_cached_height((GameFont *)&font_size24_bold);
      }
      if (this->large_layout == 0) {
        local_474 = font_line_spacing((GameFont *)&font_size16);
      }
      else {
        local_474 = font_line_spacing((GameFont *)&font_size24);
      }
      local_16c = local_24.top + panel_padding_y * 2 + local_470 + local_474;
      local_168 = local_34 + panel_margin_x * -3;
      local_160 = (local_16c - local_164) / 2;
      SetRect(&local_17c,panel_margin_x * 2 + local_24.left,local_164,local_24.left + local_168,
              local_164 + local_160);
      pCVar6 = operator_new(0x3c);
      local_8 = 0xd;
      if (pCVar6 == (Control *)0x0) {
        local_2cc = 0;
      }
      else {
        local_2cc = button_ctor(pCVar6);
      }
      local_8 = 0xffffffff;
      *(i32 *)(this->pad_3c0 + param_2 * 4 - 0x24) = local_2cc;
      if (param_2 == 0) {
        local_478 = label_string(*(i32 *)(label_string_ids + 0xdbc));
      }
      else {
        local_478 = label_string(*(i32 *)(label_string_ids + 0xdc0));
      }
      if (this == (ViewWindow *)0x0) {
        local_47c = (u8 *)0x0;
      }
      else {
        local_47c = this->pad_48;
      }
      button_create
                (*(Control **)(this->pad_3c0 + param_2 * 4 - 0x24),(iptr)local_47c,
                 param_2 + 0x404,(iptr)&local_17c,local_478);
      button_set_callback
                (*(Control **)(this->pad_3c0 + param_2 * 4 - 0x24),
                 (iptr)(((void *)ADDR(0x00402496, parley_reveal_city_origin_clicked)) + ((param_2 == 0) - 1 & 0xffffef93)));
      pCVar6 = operator_new(0x3c);
      local_8 = 0xe;
      if (pCVar6 == (Control *)0x0) {
        local_2d4 = 0;
      }
      else {
        local_2d4 = button_ctor(pCVar6);
      }
      local_8 = 0xffffffff;
      *(i32 *)(this->pad_3c0 + param_2 * 4 - 0x1c) = local_2d4;
      if (param_2 == 0) {
        local_480 = label_string(*(i32 *)(label_string_ids + 0xdc4));
      }
      else {
        local_480 = label_string(*(i32 *)(label_string_ids + 0xdc0));
      }
      if (this == (ViewWindow *)0x0) {
        local_484 = (u8 *)0x0;
      }
      else {
        local_484 = this->pad_48;
      }
      button_create
                (*(Control **)(this->pad_3c0 + param_2 * 4 - 0x1c),(iptr)local_484,
                 param_2 + 0x406,(iptr)&local_17c,local_480);
      button_set_callback
                (*(Control **)(this->pad_3c0 + param_2 * 4 - 0x1c),
                 (iptr)(((void *)ADDR(0x004034d1, parley_hide_city_origin_clicked)) + ((param_2 == 0) - 1 & 0xffffdf58)));
      if ((param_2 == 0) && (this->field_3bd != '\0')) {
        control_hide((Control *)this->field_39c);
        ctrl_show_and_redraw((Control *)this->field_3a4);
      }
      else if (param_2 == 0) {
        ctrl_show_and_redraw((Control *)this->field_39c);
        control_hide((Control *)this->field_3a4);
      }
      if ((param_2 == 1) && (this->field_3bc != '\0')) {
        control_hide((Control *)this->field_3a0);
        ctrl_show_and_redraw((Control *)this->field_3a8);
        ctrl_disable((Control *)this->field_3a8);
      }
      else if (param_2 == 1) {
        ctrl_show_and_redraw((Control *)this->field_3a0);
        control_hide((Control *)this->field_3a8);
      }
      local_164 += local_160;
      local_168 = local_34 / 2;
      SetRect(&local_17c,panel_margin_x * 2 + local_24.left,local_164,local_24.left + local_168,
              local_164 + local_160);
    }
    pCVar6 = operator_new(0x3c);
    local_8 = 0xf;
    if (pCVar6 == (Control *)0x0) {
      local_2dc = 0;
    }
    else {
      local_2dc = button_ctor(pCVar6);
    }
    local_8 = 0xffffffff;
    *(i32 *)(this->pad_364 + param_2 * 4 + 0x28) = local_2dc;
    if (this == (ViewWindow *)0x0) {
      local_490 = (u8 *)0x0;
    }
    else {
      local_490 = this->pad_48;
    }
    iVar4 = label_string(*(i32 *)(label_string_ids + 0xc28));
    button_create
              (*(Control **)(this->pad_364 + param_2 * 4 + 0x28),(iptr)local_490,
               param_2 + 0x400,(iptr)&local_17c,iVar4);
    button_set_callback
              (*(Control **)(this->pad_364 + param_2 * 4 + 0x28),
               (iptr)(((void *)ADDR(0x00401f55, parley_sort_by_unit_left_clicked)) + ((param_2 == 0) - 1 & 0xfffff637)));
    if ((parley_mode != 9) &&
       (((param_2 == 0 && (this->field_3bd == '\0')) ||
        ((param_2 == 1 && (this->field_3bc == '\0')))))) {
      ctrl_disable(*(Control **)(this->pad_364 + param_2 * 4 + 0x28));
    }
    SetRect(&local_17c,local_17c.right,local_164,local_17c.right + local_168 + panel_margin_x * -3,
            local_164 + local_160);
    pCVar6 = operator_new(0x3c);
    local_8 = 0x10;
    if (pCVar6 == (Control *)0x0) {
      local_2e4 = 0;
    }
    else {
      local_2e4 = button_ctor(pCVar6);
    }
    local_8 = 0xffffffff;
    *(i32 *)(this->pad_364 + param_2 * 4 + 0x30) = local_2e4;
    if (this == (ViewWindow *)0x0) {
      local_494 = (u8 *)0x0;
    }
    else {
      local_494 = this->pad_48;
    }
    iVar4 = label_string(*(i32 *)(label_string_ids + 0xc2c));
    button_create
              (*(Control **)(this->pad_364 + param_2 * 4 + 0x30),(iptr)local_494,
               param_2 + 0x402,(iptr)&local_17c,iVar4);
    button_set_callback
              (*(Control **)(this->pad_364 + param_2 * 4 + 0x30),
               (iptr)(((void *)ADDR(0x004033d7, parley_sort_by_city_left_clicked)) + ((param_2 == 0) - 1 & 0xfffff5a1)));
    if ((parley_mode != 9) &&
       (((param_2 == 0 && (this->field_3bd == '\0')) ||
        ((param_2 == 1 && (this->field_3bc == '\0')))))) {
      ctrl_disable(*(Control **)(this->pad_364 + param_2 * 4 + 0x30));
    }
    local_24.top = local_17c.bottom;
    local_24.bottom = this->show_turn_timer + panel_margin_y * -2;
    local_24.left += panel_margin_x * 2;
    local_24.right += panel_margin_x * -2;
    gfx_target_frame_rect((iptr)&local_24,10);
    rect_deflate((iptr)&local_24,1,1);
    surface_fill_rect((DibSurface *)this,(iptr)&local_24,list_bg_color);
    local_15c = 1;
    if ((local_30 != '\0') || ((local_28 != '\0' && (param_2 == 1)))) {
      local_15c = 0;
    }
    parley_create_unit_list_pane((ListPaneWindow *)this,(iptr)&local_24,param_2,local_15c);
    break;
  case 0xb:
    gfx_set_text_color_index(10);
    if (this->large_layout == 0) {
      local_498 = font_cached_height((GameFont *)&font_size16_bold);
    }
    else {
      local_498 = font_cached_height((GameFont *)&font_size24_bold);
    }
    local_14 = local_498 * 3 + panel_margin_y * 2;
    iVar2 = this->panel_top + (int)((this->show_turn_timer - this->panel_top) - local_14) / 2;
    local_38 = local_2c;
    if (this->large_layout == 0) {
      local_2e8 = &font_size16_bold;
    }
    else {
      local_2e8 = &font_size24_bold;
    }
    uVar10 = 5;
    uVar8 = local_2c;
    local_3c = iVar2;
    iVar4 = label_string(*(i32 *)(label_string_ids + 0xc30));
    surface_draw_text((DibSurface *)this,(iptr)local_2e8,iVar4,uVar8,iVar2,uVar10);
    local_184 = label_string(*(i32 *)(label_string_ids + 0xc34));
    local_180 = label_string(*(i32 *)(label_string_ids + 0xc38));
    if (this->large_layout == 0) {
      local_2ec = &font_size16_bold;
    }
    else {
      local_2ec = &font_size24_bold;
    }
    ctrl_set_pending_font((iptr)local_2ec);
    pCVar3 = operator_new(0x50);
    local_8 = 0x11;
    if (pCVar3 == (InputControl *)0x0) {
      local_2f4 = 0;
    }
    else {
      local_2f4 = radiogrp_ctor(pCVar3);
    }
    local_8 = 0xffffffff;
    *(i32 *)(this->pad_364 + param_2 * 4 + 8) = local_2f4;
    local_38 = local_2c;
    iVar2 = rect_width((iptr)&this->panel_rect);
    local_34 = (iVar2 + panel_margin_x * -2) / 2;
    if (this->large_layout == 0) {
      local_4a4 = font_cached_height((GameFont *)&font_size16_bold);
    }
    else {
      local_4a4 = font_cached_height((GameFont *)&font_size24_bold);
    }
    local_3c = local_3c + panel_margin_y + local_4a4;
    if (this->large_layout == 0) {
      local_4a8 = font_cached_height((GameFont *)&font_size16_bold);
    }
    else {
      local_4a8 = font_cached_height((GameFont *)&font_size24_bold);
    }
    local_14 = local_4a8 * 2 + panel_margin_y;
    SetRect(&local_24,local_38,local_3c,local_34 + local_38,local_14 + local_3c);
    if (this == (ViewWindow *)0x0) {
      local_4ac = (u8 *)0x0;
    }
    else {
      local_4ac = this->pad_48;
    }
    radiogrp_create
              (*(RadioGroup **)(this->pad_364 + param_2 * 4 + 8),(iptr)local_4ac,0x40c,
               (iptr)&local_24,1,2,(iptr)&local_184);
    radiogrp_set_selected
              (*(RadioGroupSetSelView **)(this->pad_364 + param_2 * 4 + 8),this->field_21c);
    radiogrp_set_dblclick_callback(*(Control **)(this->pad_364 + param_2 * 4 + 8),ADDR(0x401d75, parley_on_radio_dblclick))
    ;
    radiogrp_set_select_callback(*(Control **)(this->pad_364 + param_2 * 4 + 8),ADDR(0x401c99, parley_on_proposal_kind_select))
    ;
    puVar1 = this->pad_200 + param_2 * 4 - 0x1c;
    puVar1[0] = 1;
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
    break;
  case 0xc:
    local_1ac[0] = label_string(*(i32 *)(label_string_ids + 0xc50));
    local_1ac[1] = label_string(*(i32 *)(label_string_ids + 0xc54));
    local_1ac[2] = label_string(*(i32 *)(label_string_ids + 0xc58));
    local_1ac[3] = label_string(*(i32 *)(label_string_ids + 0xd0c));
    if (local_28 == '\0') {
      if (local_30 == '\0') {
        local_1b0 = 0;
      }
      else {
        local_1b0 = 3;
      }
    }
    else if (param_2 == 0) {
      local_1b0 = 1;
    }
    else {
      local_1b0 = 2;
    }
    puVar1 = this[0x3e].pad_48 + param_2 * 4 + 0x38;
    puVar1[0] = 5;
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
    gfx_set_text_color_index(10);
    local_38 = local_2c;
    local_3c = this->panel_top + panel_margin_y;
    if (local_28 != '\0') {
      str_clear(ADDR(0x679640, ((u8 *)&g.d_00679640)));
      if (param_2 == 0) {
        local_4d8 = label_string(*(i32 *)(label_string_ids + 0xc0c));
      }
      else {
        local_4d8 = label_string(*(i32 *)(label_string_ids + 0xc10));
      }
      text_append_str(local_4d8);
      if (this->large_layout == 0) {
        local_30c = &font_size16_bold;
      }
      else {
        local_30c = &font_size24_bold;
      }
      surface_draw_text
                ((DibSurface *)this,(iptr)local_30c,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_38,local_3c,5);
      if (this->large_layout == 0) {
        local_4e0 = font_cached_height((GameFont *)&font_size16_bold);
      }
      else {
        local_4e0 = font_cached_height((GameFont *)&font_size24_bold);
      }
      local_3c = local_3c + panel_margin_y + local_4e0;
    }
    iVar2 = rect_width((iptr)&this->panel_rect);
    local_34 = (iVar2 + panel_margin_x * -2) / 2 + panel_margin_x * -5;
    if (this->large_layout == 0) {
      local_4e4 = font_cached_height((GameFont *)&font_size14);
    }
    else {
      local_4e4 = font_cached_height((GameFont *)&font_size21);
    }
    if (this->large_layout == 0) {
      local_4e8 = font_cached_height((GameFont *)&font_size16_bold);
    }
    else {
      local_4e8 = font_cached_height((GameFont *)&font_size24_bold);
    }
    local_14 = *(int *)(this[0x3e].pad_48 + param_2 * 4 + 0x38) * local_4e4 +
               *(int *)(this[0x3e].pad_48 + param_2 * 4 + 0x38) * panel_margin_y + panel_margin_y * 4 +
               local_4e8;
    local_3c += (int)((this->show_turn_timer - local_3c) - local_14) / 2;
    SetRect(&local_24,local_38,local_3c,local_34 + local_38,local_14 + local_3c);
    gfx_set_draw_target(ADDR(0x67a7a8, ((u8 *)&g.d_0067a7a8)));
    gfx_target_frame_rect((iptr)&local_24,10);
    rect_deflate((iptr)&local_24,1,1);
    gfx_target_frame_rect((iptr)&local_24,10);
    iVar2 = rect_width((iptr)&local_24);
    local_38 = local_24.left + iVar2 / 2;
    if (this->large_layout == 0) {
      local_4ec = font_cached_height((GameFont *)&font_size16_bold);
    }
    else {
      local_4ec = font_cached_height((GameFont *)&font_size24_bold);
    }
    local_3c = local_3c + panel_margin_y + local_4ec / 2;
    if (this->large_layout == 0) {
      local_310 = &font_size16_bold;
    }
    else {
      local_310 = &font_size24_bold;
    }
    surface_draw_text
              ((DibSurface *)this,(iptr)local_310,local_1ac[local_1b0],local_38,local_3c,0);
    if (this->large_layout == 0) {
      local_4f4 = font_cached_height((GameFont *)&font_size16_bold);
    }
    else {
      local_4f4 = font_cached_height((GameFont *)&font_size24_bold);
    }
    local_24.top = local_24.top + panel_margin_y + local_4f4;
    if (this->large_layout == 0) {
      local_4f8 = font_cached_height((GameFont *)&font_size14);
    }
    else {
      local_4f8 = font_cached_height((GameFont *)&font_size21);
    }
    local_24.bottom =
         *(int *)(this[0x3e].pad_48 + param_2 * 4 + 0x38) * local_4f8 +
         *(int *)(this[0x3e].pad_48 + param_2 * 4 + 0x38) * panel_margin_y + local_24.top + 2;
    local_24.left += panel_margin_x * 2;
    local_24.right += panel_margin_x * -2;
    gfx_target_frame_rect((iptr)&local_24,10);
    rect_deflate((iptr)&local_24,1,1);
    surface_fill_rect((DibSurface *)this,(iptr)&local_24,list_bg_color);
    parley_build_civ_list((ListPaneWindow *)this,(iptr)&local_24,param_2);
    break;
  case 0xd:
    local_198[0] = label_string(*(i32 *)(label_string_ids + 0xc3c));
    local_198[1] = label_string(*(i32 *)(label_string_ids + 0xc40));
    local_19c = 0;
    local_198[2] = label_string(*(i32 *)(label_string_ids + 0xc44));
    local_198[3] = label_string(*(i32 *)(label_string_ids + 0xc48));
    local_188 = label_string(*(i32 *)(label_string_ids + 0xc4c));
    gfx_set_text_color_index(10);
    local_38 = local_2c;
    local_3c = this->panel_top + panel_margin_y;
    if (local_28 != '\0') {
      local_19c = (uptr)(param_2 != 0);
      str_clear(ADDR(0x679640, ((u8 *)&g.d_00679640)));
      if (param_2 == 0) {
        local_4b0 = label_string(*(i32 *)(label_string_ids + 0xc0c));
      }
      else {
        local_4b0 = label_string(*(i32 *)(label_string_ids + 0xc10));
      }
      text_append_str(local_4b0);
      if (this->large_layout == 0) {
        local_2f8 = &font_size16_bold;
      }
      else {
        local_2f8 = &font_size24_bold;
      }
      surface_draw_text
                ((DibSurface *)this,(iptr)local_2f8,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_38,local_3c,5);
      if (this->large_layout == 0) {
        local_4b8 = font_cached_height((GameFont *)&font_size16_bold);
      }
      else {
        local_4b8 = font_cached_height((GameFont *)&font_size24_bold);
      }
      local_3c = local_3c + panel_margin_y + local_4b8;
    }
    iVar2 = rect_width((iptr)&this->panel_rect);
    local_34 = (iVar2 + panel_margin_x * -2) / 2 + panel_margin_x * -5;
    if (this->large_layout == 0) {
      local_4bc = font_cached_height((GameFont *)&font_size14);
    }
    else {
      local_4bc = font_cached_height((GameFont *)&font_size21);
    }
    if (this->large_layout == 0) {
      local_4c0 = font_cached_height((GameFont *)&font_size16_bold);
    }
    else {
      local_4c0 = font_cached_height((GameFont *)&font_size24_bold);
    }
    local_14 = local_4bc * 3 + panel_margin_y * 9 + local_4c0;
    local_3c += (int)((this->show_turn_timer - local_3c) - local_14) / 2;
    SetRect(&local_24,local_38,local_3c,local_34 + local_38,local_14 + local_3c);
    gfx_set_draw_target(ADDR(0x67a7a8, ((u8 *)&g.d_0067a7a8)));
    gfx_target_frame_rect((iptr)&local_24,10);
    rect_deflate((iptr)&local_24,1,1);
    gfx_target_frame_rect((iptr)&local_24,10);
    iVar2 = rect_width((iptr)&local_24);
    local_38 = local_24.left + iVar2 / 2;
    if (this->large_layout == 0) {
      local_4c4 = font_cached_height((GameFont *)&font_size16_bold);
    }
    else {
      local_4c4 = font_cached_height((GameFont *)&font_size24_bold);
    }
    local_3c = local_3c + panel_margin_y + local_4c4 / 2;
    if (this->large_layout == 0) {
      local_2fc = &font_size16_bold;
    }
    else {
      local_2fc = &font_size24_bold;
    }
    surface_draw_text
              ((DibSurface *)this,(iptr)local_2fc,local_198[local_19c],local_38,local_3c,0);
    if (this->large_layout == 0) {
      local_4cc = font_cached_height((GameFont *)&font_size16_bold);
    }
    else {
      local_4cc = font_cached_height((GameFont *)&font_size24_bold);
    }
    local_24.top = local_24.top + panel_margin_y + local_4cc;
    local_24.bottom += panel_margin_y * -2;
    local_24.left += panel_margin_x * 2;
    local_24.right += panel_margin_x * -2;
    gfx_target_frame_rect((iptr)&local_24,10);
    rect_deflate((iptr)&local_24,1,1);
    surface_fill_rect((DibSurface *)this,(iptr)&local_24,list_bg_color);
    if (this->large_layout == 0) {
      local_300 = &font_size16_bold;
    }
    else {
      local_300 = &font_size24_bold;
    }
    ctrl_set_pending_font((iptr)local_300);
    pCVar3 = operator_new(0x50);
    local_8 = 0x12;
    if (pCVar3 == (InputControl *)0x0) {
      local_308 = 0;
    }
    else {
      local_308 = radiogrp_ctor(pCVar3);
    }
    local_8 = 0xffffffff;
    *(i32 *)(this->pad_364 + param_2 * 4 + 8) = local_308;
    if (this == (ViewWindow *)0x0) {
      local_4d4 = (u8 *)0x0;
    }
    else {
      local_4d4 = this->pad_48;
    }
    radiogrp_create
              (*(RadioGroup **)(this->pad_364 + param_2 * 4 + 8),(iptr)local_4d4,param_2 + 0x424,
               (iptr)&local_24,1,3,(iptr)(local_198 + 2));
    radiogrp_set_selected
              (*(RadioGroupSetSelView **)(this->pad_364 + param_2 * 4 + 8),
               *(i32 *)(this->pad_23c + param_2 * 4 - 0x18));
    radiogrp_set_dblclick_callback(*(Control **)(this->pad_364 + param_2 * 4 + 8),ADDR(0x401d75, parley_on_radio_dblclick))
    ;
    radiogrp_set_select_callback(*(Control **)(this->pad_364 + param_2 * 4 + 8),ADDR(0x401bd6, parley_on_map_choice_select))
    ;
    puVar1 = this->pad_200 + param_2 * 4 - 0x1c;
    puVar1[0] = 1;
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
    break;
  case 0xf:
    local_1cc = label_string(*(i32 *)(label_string_ids + 0xbac));
    local_1c8 = label_string(*(i32 *)(label_string_ids + 0xbb0));
    local_1c4 = label_string(*(i32 *)(label_string_ids + 0xbb4));
    local_1c0 = label_string(*(i32 *)(label_string_ids + 3000));
    local_1bc = label_string(*(i32 *)(label_string_ids + 0xbbc));
    local_1b8 = label_string(*(i32 *)(label_string_ids + 0xbc4));
    local_1b4 = label_string(*(i32 *)(label_string_ids + 0xd08));
    gfx_set_text_color_index(10);
    local_38 = local_2c;
    if (this->large_layout == 0) {
      local_4fc = font_cached_height((GameFont *)&font_size16_bold);
    }
    else {
      local_4fc = font_cached_height((GameFont *)&font_size24_bold);
    }
    local_14 = panel_margin_y * 7 + local_4fc * 8;
    iVar2 = this->panel_top + (int)((this->show_turn_timer - this->panel_top) - local_14) / 2;
    if (this->large_layout == 0) {
      local_314 = &font_size16_bold;
    }
    else {
      local_314 = &font_size24_bold;
    }
    uVar10 = 5;
    uVar9 = local_38;
    local_3c = iVar2;
    iVar4 = label_string(*(i32 *)(label_string_ids + 0xc5c));
    surface_draw_text((DibSurface *)this,(iptr)local_314,iVar4,uVar9,iVar2,uVar10);
    if (this->large_layout == 0) {
      local_504 = font_cached_height((GameFont *)&font_size16_bold);
    }
    else {
      local_504 = font_cached_height((GameFont *)&font_size24_bold);
    }
    iVar2 = local_3c + panel_margin_y * 2 + local_504;
    if (this->large_layout == 0) {
      local_318 = &font_size16_bold;
    }
    else {
      local_318 = &font_size24_bold;
    }
    uVar10 = 5;
    uVar9 = local_38;
    local_3c = iVar2;
    iVar4 = label_string(*(i32 *)(label_string_ids + 0xc60));
    surface_draw_text((DibSurface *)this,(iptr)local_318,iVar4,uVar9,iVar2,uVar10);
    if (this->large_layout == 0) {
      local_50c = font_cached_height((GameFont *)&font_size16_bold);
    }
    else {
      local_50c = font_cached_height((GameFont *)&font_size24_bold);
    }
    local_3c = local_3c + panel_margin_y + local_50c;
    if (this->large_layout == 0) {
      local_31c = &font_size16_bold;
    }
    else {
      local_31c = &font_size24_bold;
    }
    ctrl_set_pending_font((iptr)local_31c);
    pCVar3 = operator_new(0x50);
    local_8 = 0x13;
    if (pCVar3 == (InputControl *)0x0) {
      local_324 = 0;
    }
    else {
      local_324 = radiogrp_ctor(pCVar3);
    }
    local_8 = 0xffffffff;
    *(i32 *)(this->pad_364 + param_2 * 4 + 8) = local_324;
    local_38 = local_2c;
    iVar2 = rect_width((iptr)&this->panel_rect);
    local_34 = (iVar2 + panel_margin_x * -2) / 2;
    if (this->large_layout == 0) {
      local_514 = font_cached_height((GameFont *)&font_size16_bold);
    }
    else {
      local_514 = font_cached_height((GameFont *)&font_size24_bold);
    }
    local_14 = panel_margin_y * 5 + local_514 * 6;
    SetRect(&local_24,local_38,local_3c,local_34 + local_38,local_14 + local_3c);
    if (this == (ViewWindow *)0x0) {
      local_518 = (u8 *)0x0;
    }
    else {
      local_518 = this->pad_48;
    }
    radiogrp_create
              (*(RadioGroup **)(this->pad_364 + param_2 * 4 + 8),(iptr)local_518,0x41f,
               (iptr)&local_24,1,7,(iptr)&local_1cc);
    radiogrp_set_selected
              (*(RadioGroupSetSelView **)(this->pad_364 + param_2 * 4 + 8),this->field_214);
    radiogrp_set_dblclick_callback(*(Control **)(this->pad_364 + param_2 * 4 + 8),ADDR(0x401d75, parley_on_radio_dblclick))
    ;
    radiogrp_set_select_callback(*(Control **)(this->pad_364 + param_2 * 4 + 8),ADDR(0x403a30, parley_on_demand_kind_select))
    ;
    puVar1 = this->pad_200 + param_2 * 4 - 0x1c;
    puVar1[0] = 1;
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
    break;
  case 0x11:
    if (local_28 == '\0') {
      puVar1 = this[0x3e].pad_48 + param_2 * 4 + 0x38;
      puVar1[0] = 7;
      puVar1[1] = '\0';
      puVar1[2] = '\0';
      puVar1[3] = '\0';
    }
    else {
      puVar1 = this[0x3e].pad_48 + param_2 * 4 + 0x38;
      puVar1[0] = 6;
      puVar1[1] = '\0';
      puVar1[2] = '\0';
      puVar1[3] = '\0';
    }
    gfx_set_text_color_index(10);
    local_38 = local_2c;
    local_3c = this->panel_top + panel_margin_y;
    iVar2 = rect_width((iptr)&this->panel_rect);
    local_34 = (iVar2 + panel_margin_x * -2) / 2 + panel_margin_x * -5;
    if (local_28 != '\0') {
      str_clear(ADDR(0x679640, ((u8 *)&g.d_00679640)));
      if (param_2 == 0) {
        local_51c = label_string(*(i32 *)(label_string_ids + 0xc0c));
      }
      else {
        local_51c = label_string(*(i32 *)(label_string_ids + 0xc10));
      }
      text_append_str(local_51c);
      if (this->large_layout == 0) {
        local_328 = &font_size16_bold;
      }
      else {
        local_328 = &font_size24_bold;
      }
      surface_draw_text
                ((DibSurface *)this,(iptr)local_328,ADDR(0x679640, ((u8 *)&g.d_00679640)),local_38,local_3c,5);
      if (this->large_layout == 0) {
        local_524 = font_cached_height((GameFont *)&font_size16_bold);
      }
      else {
        local_524 = font_cached_height((GameFont *)&font_size24_bold);
      }
      local_3c = local_3c + panel_margin_y + local_524;
    }
    SetRect(&local_24,local_38,local_3c,local_34 + local_38,this->show_turn_timer);
    gfx_set_draw_target(ADDR(0x67a7a8, ((u8 *)&g.d_0067a7a8)));
    gfx_target_frame_rect((iptr)&local_24,10);
    rect_deflate((iptr)&local_24,1,1);
    gfx_target_frame_rect((iptr)&local_24,10);
    iVar2 = rect_width((iptr)&local_24);
    local_38 = local_24.left + iVar2 / 2;
    if (this->large_layout == 0) {
      local_528 = font_cached_height((GameFont *)&font_size16_bold);
    }
    else {
      local_528 = font_cached_height((GameFont *)&font_size24_bold);
    }
    local_3c += local_528 / 2;
    if ((local_28 == '\0') && (local_30 == '\0')) {
      local_1d8 = label_string(*(i32 *)(label_string_ids + 0xc68));
      if (this->large_layout == 0) {
        local_33c = &font_size16_bold;
      }
      else {
        local_33c = &font_size24_bold;
      }
      surface_draw_text
                ((DibSurface *)this,(iptr)local_33c,local_1d8,local_38,local_3c,0);
    }
    else {
      local_1dc = panel_margin_y * 2 + local_24.top - 1;
      local_1e0 = local_34 + panel_margin_x * -3;
      if (this->large_layout == 0) {
        local_52c = font_cached_height((GameFont *)&font_size16_bold);
      }
      else {
        local_52c = font_cached_height((GameFont *)&font_size24_bold);
      }
      local_1d4 = local_52c - (panel_margin_y * 2 - 1);
      SetRect(&local_1f0,panel_margin_x * 2 + local_24.left,local_1dc,local_24.left + local_1e0,
              local_1d4 + local_1dc);
      pCVar6 = operator_new(0x3c);
      local_8 = 0x14;
      if (pCVar6 == (Control *)0x0) {
        local_330 = 0;
      }
      else {
        local_330 = button_ctor(pCVar6);
      }
      local_8 = 0xffffffff;
      *(i32 *)(this->pad_3c0 + param_2 * 4 - 0x24) = local_330;
      if (param_2 == 0) {
        local_530 = label_string(*(i32 *)(label_string_ids + 0xdc8));
      }
      else {
        local_530 = label_string(*(i32 *)(label_string_ids + 0xdcc));
      }
      if (this == (ViewWindow *)0x0) {
        local_534 = (u8 *)0x0;
      }
      else {
        local_534 = this->pad_48;
      }
      button_create
                (*(Control **)(this->pad_3c0 + param_2 * 4 - 0x24),(iptr)local_534,
                 param_2 + 0x408,(iptr)&local_1f0,local_530);
      button_set_callback
                (*(Control **)(this->pad_3c0 + param_2 * 4 - 0x24),
                 (iptr)(((void *)ADDR(0x004038d7, parley_reveal_city_info)) + ((param_2 == 0) - 1 & 0xffffdd6e)));
      pCVar6 = operator_new(0x3c);
      local_8 = 0x15;
      if (pCVar6 == (Control *)0x0) {
        local_338 = 0;
      }
      else {
        local_338 = button_ctor(pCVar6);
      }
      local_8 = 0xffffffff;
      *(i32 *)(this->pad_3c0 + param_2 * 4 - 0x1c) = local_338;
      if (param_2 == 0) {
        local_538 = label_string(*(i32 *)(label_string_ids + 0xdd0));
      }
      else {
        local_538 = label_string(*(i32 *)(label_string_ids + 0xdcc));
      }
      if (this == (ViewWindow *)0x0) {
        local_53c = (u8 *)0x0;
      }
      else {
        local_53c = this->pad_48;
      }
      button_create
                (*(Control **)(this->pad_3c0 + param_2 * 4 - 0x1c),(iptr)local_53c,
                 param_2 + 0x40a,(iptr)&local_1f0,local_538);
      button_set_callback
                (*(Control **)(this->pad_3c0 + param_2 * 4 - 0x1c),
                 (iptr)(((void *)ADDR(0x00401979, parley_hide_city_info)) + ((param_2 == 0) - 1 & 0xfffffccc)));
      if ((param_2 == 0) && (this->field_3be != '\0')) {
        control_hide((Control *)this->field_39c);
        ctrl_show_and_redraw((Control *)this->field_3a4);
      }
      else if (param_2 == 0) {
        ctrl_show_and_redraw((Control *)this->field_39c);
        control_hide((Control *)this->field_3a4);
      }
      if ((param_2 == 1) && (this->remote_side_agreed != '\0')) {
        control_hide((Control *)this->field_3a0);
        ctrl_show_and_redraw((Control *)this->field_3a8);
        ctrl_disable((Control *)this->field_3a8);
      }
      else if (param_2 == 1) {
        ctrl_show_and_redraw((Control *)this->field_3a0);
        control_hide((Control *)this->field_3a8);
      }
    }
    if (this->large_layout == 0) {
      iVar2 = font_cached_height((GameFont *)&font_size16_bold);
      local_24.top += iVar2;
    }
    else {
      iVar2 = font_cached_height((GameFont *)&font_size24_bold);
      local_24.top += iVar2;
    }
    local_24.bottom = this->show_turn_timer + panel_margin_y * -2;
    local_24.left += panel_margin_x * 2;
    local_24.right += panel_margin_x * -2;
    gfx_target_frame_rect((iptr)&local_24,10);
    rect_deflate((iptr)&local_24,1,1);
    surface_fill_rect((DibSurface *)this,(iptr)&local_24,list_bg_color);
    local_1d0 = 1;
    if ((local_30 != '\0') || ((local_28 != '\0' && (param_2 == 1)))) {
      local_1d0 = 0;
    }
    parley_create_city_list_pane((ListPaneWindow *)this,(iptr)&local_24,param_2,local_1d0);
    break;
  case 0x12:
    iVar4 = civ_get_adjective(this->caption_height);
    text_set_string_arg_b(0,iVar4);
    text_clear();
    text_append_label(0x2e2);
    text_expand_vars(ADDR(0x679640, ((u8 *)&g.d_00679640)),(iptr)local_9c);
    gfx_set_text_color_index(10);
    if (this->large_layout == 0) {
      local_a0 = font_text_width((GameFont *)&font_size20,(iptr)local_9c);
    }
    else {
      local_a0 = font_text_width((GameFont *)&font_size30,(iptr)local_9c);
    }
    local_38 = (this->panel_rect + (int)(this->panel_right - this->panel_rect) / 2) - local_a0 / 2;
    if (this->large_layout == 0) {
      local_354 = font_cached_height((GameFont *)&font_size20);
    }
    else {
      local_354 = font_cached_height((GameFont *)&font_size30);
    }
    local_3c = (this->panel_top + (int)(this->show_turn_timer - this->panel_top) / 2 + panel_margin_y) -
               local_354 / 2;
    if (this->large_layout == 0) {
      local_20c = &font_size20;
    }
    else {
      local_20c = &font_size30;
    }
    surface_draw_text
              ((DibSurface *)this,(iptr)local_20c,(iptr)local_9c,local_38,local_3c,5);
    control_hide((Control *)this->field_34c);
    ctrl_disable((Control *)this->field_34c);
    ctrl_show_and_redraw((Control *)this->field_348);
    ctrl_disable((Control *)this->field_348);
    ctrl_disable((Control *)this->field_350);
    if ((this->field_3bd == '\0') && (this->field_3be == '\0')) {
      control_hide((Control *)this->field_340);
      ctrl_disable((Control *)this->field_340);
      ctrl_show_and_redraw((Control *)this->field_344);
      ctrl_enable((Control *)this->field_344);
    }
    else {
      ctrl_show_and_redraw((Control *)this->field_340);
      ctrl_enable((Control *)this->field_340);
      control_hide((Control *)this->field_344);
      ctrl_disable((Control *)this->field_344);
    }
    break;
  case 0x13:
    parley_build_description((WindowObjectView *)this,this->item_buffer,0);
    pCVar3 = operator_new(0x48);
    local_8 = 0;
    if (pCVar3 == (InputControl *)0x0) {
      local_1f8 = 0;
    }
    else {
      local_1f8 = edit_ctor(pCVar3);
    }
    local_8 = 0xffffffff;
    this->side_text_edit = local_1f8;
    local_38 = this->panel_rect + panel_margin_x;
    local_34 = rect_width((iptr)&this->panel_rect);
    local_34 += panel_margin_x * -2;
    local_3c = this->panel_top + panel_margin_y;
    local_14 = this->show_turn_timer - local_3c;
    SetRect(&local_24,local_38,local_3c,local_34 + local_38,local_14 + local_3c);
    if (this->large_layout == 0) {
      local_1fc = &font_size14;
    }
    else {
      local_1fc = &font_size21;
    }
    ui_set_default_font((iptr)local_1fc);
    if (this == (ViewWindow *)0x0) {
      local_344 = (u8 *)0x0;
    }
    else {
      local_344 = this->pad_48;
    }
    edit_create_styled
              ((EditControl *)this->side_text_edit,(iptr)local_344,0x426,(iptr)&local_24,ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),0x122
               ,0);
    edit_set_max_len((EditMaxLenView *)this->side_text_edit,0x2000);
    edit_set_callback((EditCallbackSetView *)this->side_text_edit,ADDR(0x402040, parley_edit_escape_filter));
    ctrl_show_and_redraw((Control *)this->side_text_edit);
    break;
  case 0x14:
    window_show((WindowObjectView *)&parley_wnd);
    parley_build_description((WindowObjectView *)this,this->item_buffer,1);
    pCVar3 = operator_new(0x48);
    local_8 = 1;
    if (pCVar3 == (InputControl *)0x0) {
      local_204 = 0;
    }
    else {
      local_204 = edit_ctor(pCVar3);
    }
    local_8 = 0xffffffff;
    this->side_text_edit = local_204;
    local_38 = this->panel_rect + panel_margin_x;
    local_34 = rect_width((iptr)&this->panel_rect);
    local_34 += panel_margin_x * -2;
    local_3c = this->panel_top + panel_margin_y;
    local_14 = this->show_turn_timer - local_3c;
    SetRect(&local_24,local_38,local_3c,local_34 + local_38,local_14 + local_3c);
    if (this->large_layout == 0) {
      local_208 = &font_size14;
    }
    else {
      local_208 = &font_size21;
    }
    ui_set_default_font((iptr)local_208);
    if (this == (ViewWindow *)0x0) {
      local_34c = (u8 *)0x0;
    }
    else {
      local_34c = this->pad_48;
    }
    edit_create_styled
              ((EditControl *)this->side_text_edit,(iptr)local_34c,0x426,(iptr)&local_24,ADDR(0x6a5b58, ((u8 *)&g.d_006a5b58)),0x122
               ,0);
    edit_set_max_len((EditMaxLenView *)this->side_text_edit,0x2000);
    edit_set_callback((EditCallbackSetView *)this->side_text_edit,ADDR(0x402040, parley_edit_escape_filter));
    ctrl_show_and_redraw((Control *)this->side_text_edit);
    parley_offer_acceptable_i32 = 1;
    if (this->item_buffer != 0) {
      uVar2 = this->item_buffer;
      local_4c = (int *)(uVar2 + 0x20);
      if (((*(int *)(this->item_buffer + 0x10) == 0xf) && (*local_4c == 8)) ||
         ((*(int *)(this->item_buffer + 0x10) == 0xe && (*local_4c == 8)))) {
        local_40 = *(int *)(uVar2 + 0x28);
        local_48 = (iptr *)(uVar2 + 0x2c);
        for (local_44 = 0; local_44 < local_40; local_44++) {
          iVar4 = *local_48;
          local_48++;
          iVar2 = civ_has_advance(human_civ,iVar4);
          if (iVar2 == 0) {
            this->techs_all_known = 0;
          }
        }
      }
    }
    if (this->techs_all_known == 0) {
      ctrl_disable((Control *)this->field_358);
    }
    else {
      ctrl_enable((Control *)this->field_358);
    }
  }
  parley_update_buttons(this);
  wnd_blit_surface_rect((DibSurface *)this,(iptr)&this->field_3ac);
  return;
}
#undef chat_broadcast_all
#undef chat_mute_anonymous
#undef chat_remain_anonymous
#undef human_civ
#undef list_bg_color
#undef mp_chat_from_start
#undef panel_margin_x
#undef parley_offer_acceptable_i32
#undef local_53c
#undef local_538
#undef local_534
#undef local_530
#undef local_52c
#undef local_528
#undef local_524
#undef local_51c
#undef local_518
#undef local_514
#undef local_50c
#undef local_504
#undef local_4fc
#undef local_4f8
#undef local_4f4
#undef local_4ec
#undef local_4e8
#undef local_4e4
#undef local_4e0
#undef local_4d8
#undef local_4d4
#undef local_4cc
#undef local_4c4
#undef local_4c0
#undef local_4bc
#undef local_4b8
#undef local_4b0
#undef local_4ac
#undef local_4a8
#undef local_4a4
#undef local_498
#undef local_494
#undef local_490
#undef local_48c
#undef local_488
#undef local_484
#undef local_480
#undef local_47c
#undef local_478
#undef local_474
#undef local_470
#undef local_468
#undef local_464
#undef local_45c
#undef local_458
#undef local_44c
#undef local_448
#undef local_444
#undef local_43c
#undef local_434
#undef local_430
#undef local_42c
#undef local_424
#undef local_420
#undef local_418
#undef local_414
#undef local_410
#undef local_40c
#undef local_400
#undef local_3fc
#undef local_3f4
#undef local_3ec
#undef local_3e8
#undef local_3e4
#undef local_3e0
#undef local_3dc
#undef local_3d8
#undef local_3d4
#undef local_3c8
#undef local_3c4
#undef local_3c0
#undef local_3bc
#undef local_3b4
#undef local_3b0
#undef local_3ac
#undef local_3a0
#undef local_39c
#undef local_390
#undef local_38c
#undef local_380
#undef local_37c
#undef local_378
#undef local_370
#undef local_36c
#undef local_368
#undef local_364
#undef local_354
#undef local_34c
#undef local_344
#undef local_33c
#undef local_338
#undef local_330
#undef local_328
#undef local_324
#undef local_31c
#undef local_318
#undef local_314
#undef local_310
#undef local_30c
#undef local_308
#undef local_300
#undef local_2fc
#undef local_2f8
#undef local_2f4
#undef local_2ec
#undef local_2e8
#undef local_2e4
#undef local_2dc
#undef local_2d4
#undef local_2cc
#undef local_2c4
#undef local_2c0
#undef local_2bc
#undef local_2b8
#undef local_2b0
#undef local_2ac
#undef local_2a8
#undef local_2a4
#undef local_2a0
#undef local_29c
#undef local_294
#undef local_290
#undef local_28c
#undef local_288
#undef local_284
#undef local_27c
#undef local_278
#undef local_274
#undef local_270
#undef local_268
#undef local_264
#undef local_260
#undef local_258
#undef local_254
#undef local_250
#undef local_248
#undef local_240
#undef local_23c
#undef local_238
#undef local_230
#undef local_228
#undef local_220
#undef local_21c
#undef local_214
#undef local_210
#undef local_20c
#undef local_208
#undef local_204
#undef local_1fc
#undef local_1f8
#undef local_1f0
#undef local_1e0
#undef local_1dc
#undef local_1d8
#undef local_1d4
#undef local_1d0
#undef local_1cc
#undef local_1c8
#undef local_1c4
#undef local_1c0
#undef local_1bc
#undef local_1b8
#undef local_1b4
#undef local_1b0
#undef local_1ac
#undef local_19c
#undef local_198
#undef local_188
#undef local_184
#undef local_180
#undef local_17c
#undef local_16c
#undef local_168
#undef local_164
#undef local_160
#undef local_15c
#undef local_158
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
#undef local_110
#undef local_10c
#undef local_108
#undef local_104
#undef local_100
#undef local_fc
#undef local_f8
#undef local_f4
#undef local_f0
#undef local_ec
#undef local_e8
#undef local_e4
#undef local_e0
#undef local_dc
#undef local_d8
#undef local_d4
#undef civ
#undef local_cc
#undef local_c8
#undef local_c4
#undef local_c0
#undef local_bc
#undef local_b8
#undef local_b4
#undef local_a4
#undef local_a0
#undef local_9c
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
#undef local_24
#undef local_14
#undef local_10
#undef puStack_c
#undef local_8

/* 0052d4d2 auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl parley_on_treaty_type_select(i32 param_1,i32 param_2)

{
  iptr iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar1 - 0x48;
  }
  wnd_activate((Wnd *)(local_8 + 0x48));
  *(i32 *)(local_8 + 0x218) = param_2;
  return;
}
#undef local_8

/* 0052d523 auto */
#define this2 (*(ViewWindow * *)(frame_ + FRAME_OFF(0)))
void __cdecl parley_on_demand_kind_select(i32 param_1,u32 param_2)

{
  iptr iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    this2 = (ViewWindow *)0x0;
  }
  else {
    this2 = (ViewWindow *)(iVar1 - 0x48);
  }
  wnd_activate((Wnd *)this2->pad_48);
  this2->field_214 = param_2;
  parley_add_side_dialog(this2,this2->field_1f4,1);
  return;
}
#undef this2

/* 0052d588 auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl parley_on_map_choice_select(int param_1,i32 param_2)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar1 - 0x48;
  }
  wnd_activate((Wnd *)(local_8 + 0x48));
  *(i32 *)(local_8 - 0xe6c + param_1 * 4) = param_2;
  return;
}
#undef local_8

/* 0052d5dd auto */
#define this2 (*(ViewWindow * *)(frame_ + FRAME_OFF(0)))
void __cdecl parley_on_gift_kind_select(i32 param_1,u32 param_2)

{
  iptr iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    this2 = (ViewWindow *)0x0;
  }
  else {
    this2 = (ViewWindow *)(iVar1 - 0x48);
  }
  wnd_activate((Wnd *)this2->pad_48);
  this2->field_220 = param_2;
  switch(param_2) {
  case 0:
    this2->field_1ec = 7;
    break;
  case 1:
    this2->field_1ec = 8;
    break;
  case 2:
    this2->field_1ec = 9;
    break;
  case 3:
    this2->field_1ec = 10;
    break;
  case 4:
    this2->field_1ec = 0xb;
  }
  this2->field_1fc = (&parley_mode_right_kinds)[this2->field_1ec * 2];
  this2->field_1f4 = this2->field_1fc;
  parley_add_side_dialog(this2,this2->field_1f4,1);
  return;
}
#undef this2

/* 0052d6ff auto */
#define this2 (*(ViewWindow * *)(frame_ + FRAME_OFF(0)))
void __cdecl parley_on_proposal_kind_select(i32 param_1,u32 param_2)

{
  iptr iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    this2 = (ViewWindow *)0x0;
  }
  else {
    this2 = (ViewWindow *)(iVar1 - 0x48);
  }
  wnd_activate((Wnd *)this2->pad_48);
  this2->field_21c = param_2;
  if (param_2 == 0) {
    this2->field_1ec = 0xc;
  }
  else if (param_2 == 1) {
    this2->field_1ec = 0xd;
  }
  this2->field_1fc = (&parley_mode_right_kinds)[this2->field_1ec * 2];
  this2->field_1f4 = this2->field_1fc;
  parley_add_side_dialog(this2,this2->field_1f4,1);
  return;
}
#undef this2

/* 0052d7dc auto */
#define local_10 (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_8 (*(uint *)(frame_ + FRAME_OFF(8)))
void __cdecl parley_on_exchange_kind_select(int param_1,i32 param_2)

{
  iptr iVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_10 = 0;
  }
  else {
    local_10 = iVar1 - 0x48;
  }
  wnd_activate((Wnd *)(local_10 + 0x48));
  local_8 = (uint)(param_1 == 0x3f4);
  switch(param_2) {
  case 0:
    iVar2 = radiogrp_get_selected(*(RadioGroupGetSelView **)(local_10 + 0x36c + local_8 * 4));
    radiogrp_disable_item(*(RadioGroupDisableView **)(local_10 + 0x36c + local_8 * 4),0);
    radiogrp_enable_item(*(RadioGroupEnableView **)(local_10 + 0x370),6);
    radiogrp_enable_item(*(RadioGroupEnableView **)(local_10 + 0x36c),6);
    if (iVar2 == 0) {
      radiogrp_set_selected(*(RadioGroupSetSelView **)(local_10 + 0x36c + local_8 * 4),1);
    }
    break;
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
    radiogrp_enable_item(*(RadioGroupEnableView **)(local_10 + 0x36c),0);
    radiogrp_enable_item(*(RadioGroupEnableView **)(local_10 + 0x370),0);
    radiogrp_enable_item(*(RadioGroupEnableView **)(local_10 + 0x370),6);
    radiogrp_enable_item(*(RadioGroupEnableView **)(local_10 + 0x36c),6);
    break;
  case 6:
    iVar2 = radiogrp_get_selected(*(RadioGroupGetSelView **)(local_10 + 0x36c + local_8 * 4));
    radiogrp_enable_item(*(RadioGroupEnableView **)(local_10 + 0x36c),0);
    radiogrp_enable_item(*(RadioGroupEnableView **)(local_10 + 0x370),0);
    radiogrp_disable_item(*(RadioGroupDisableView **)(local_10 + 0x36c + local_8 * 4),6);
    if (iVar2 == 6) {
      radiogrp_set_selected(*(RadioGroupSetSelView **)(local_10 + 0x36c + local_8 * 4),0);
    }
  }
  return;
}
#undef local_10
#undef local_8

/* 0052d9a1 auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl parley_on_radio_dblclick(i32 param_1)

{
  iptr iVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar1 - 0x48;
  }
  iVar2 = ctrl_is_enabled(*(ControlEnabledView **)(local_8 + 0x348));
  if ((iVar2 != 0) ||
     (iVar2 = ctrl_is_enabled(*(ControlEnabledView **)(local_8 + 0x34c)), iVar2 != 0)) {
    wnd_activate((Wnd *)(local_8 + 0x48));
    parley_on_mode_chosen(param_1);
  }
  return;
}
#undef local_8

/* 0052da23 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl parley_on_conceal_info(void)

{
  iptr iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar1 - 0x48;
  }
  *(i8 *)(local_8 + 0x3bd) = 0;
  *(i8 *)(local_8 + 0x3be) = 0;
  net_send_message(0xa6,*(i32 *)
                           (&net_player_slots +
                           *(int *)(&net_civ_slots + *(int *)(local_8 + 0x118) * 4) * 0x54),
                     human_civ,(int)*(char *)(local_8 + 0x3be),0,0,0,0,0,0);
  net_send_message(0xa8,*(i32 *)
                           (&net_player_slots +
                           *(int *)(&net_civ_slots + *(int *)(local_8 + 0x118) * 4) * 0x54),
                     human_civ,(int)*(char *)(local_8 + 0x3bd),0,0,0,0,0,0);
  control_hide(*(Control **)(local_8 + 0x340));
  ctrl_disable(*(Control **)(local_8 + 0x340));
  ctrl_show_and_redraw(*(Control **)(local_8 + 0x344));
  ctrl_enable(*(Control **)(local_8 + 0x344));
  return;
}
#undef human_civ
#undef local_8

/* 0052db3d auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl parley_on_reveal_info(void)

{
  iptr iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  wnd_get_active_child();
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar1 - 0x48;
  }
  *(i8 *)(local_8 + 0x3bd) = 1;
  *(i8 *)(local_8 + 0x3be) = 1;
  net_send_message(0xa5,*(i32 *)
                           (&net_player_slots +
                           *(int *)(&net_civ_slots + *(int *)(local_8 + 0x118) * 4) * 0x54),
                     human_civ,(int)*(char *)(local_8 + 0x3be),0,0,0,0,0,0);
  net_send_message(0xa7,*(i32 *)
                           (&net_player_slots +
                           *(int *)(&net_civ_slots + *(int *)(local_8 + 0x118) * 4) * 0x54),
                     human_civ,(int)*(char *)(local_8 + 0x3bd),0,0,0,0,0,0);
  ctrl_show_and_redraw(*(Control **)(local_8 + 0x340));
  ctrl_enable(*(Control **)(local_8 + 0x340));
  control_hide(*(Control **)(local_8 + 0x344));
  ctrl_disable(*(Control **)(local_8 + 0x344));
  return;
}
#undef human_civ
#undef local_8

/* 0052dc7e auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl parley_on_check_intel(void)

{
  bool bVar1;
  iptr iVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar2 = wnd_get_active_child();
  if (iVar2 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar2 - 0x48;
  }
  iVar3 = civ_has_wonder(human_civ,0x18);
  if (iVar3 == 0) {
    iVar3 = civ_has_wonder(human_civ,9);
    if (iVar3 == 0) {
      bVar1 = false;
      goto LAB_0052dcf1;
    }
  }
  bVar1 = true;
LAB_0052dcf1:
  if ((((*(byte *)&civs[human_civ].treaties[(*(int *)(local_8 + 0x118))] & 0x80) != 0)
      || (bVar1)) || (game.reveal_map != '\0')) {
    intel_report_show(human_civ,*(iptr *)(local_8 + 0x118));
  }
  else {
    popup_game_with_sprite(ADDR(0x6324e8, ((u8 *)&g.d_006324e8)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
  }
  return;
}
#undef human_civ
#undef local_8

/* 0052dd73 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define this2 (*(ParleyOfferBuffer * *)(frame_ + FRAME_OFF(0)))
void __cdecl parley_on_mode_chosen(i32 param_1)

{
  iptr iVar1;
  i32 uVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    this2 = (ParleyOfferBuffer *)0x0;
  }
  else {
    this2 = (ParleyOfferBuffer *)(iVar1 - 0x48);
  }
  wnd_activate((Wnd *)(this2->pad_0 + 0x48));
  switch(this2->field_1ec) {
  case 3:
    uVar1 = radiogrp_get_selected(*(RadioGroupGetSelView **)(this2->pad_21c + 0x154));
    *(i32 *)this2->pad_208 = uVar1;
    if (*(int *)this2->pad_208 == 0) {
      this2->field_1ec = 6;
      ctrl_enable(*(Control **)(this2->pad_21c + 0x134));
    }
    else if (*(int *)this2->pad_208 == 1) {
      this2->field_1ec = 0xc;
      if (*(int *)this2->pad_21c != 0) {
        this2->field_1ec = 0xd;
      }
      ctrl_enable(*(Control **)(this2->pad_21c + 0x134));
    }
    else if (*(int *)this2->pad_208 == 2) {
      if (*(int *)(this2->pad_21c + 4) == 0) {
        this2->field_1ec = 7;
      }
      else if (*(int *)(this2->pad_21c + 4) == 1) {
        this2->field_1ec = 8;
      }
      else if (*(int *)(this2->pad_21c + 4) == 2) {
        this2->field_1ec = 9;
      }
      else if (*(int *)(this2->pad_21c + 4) == 3) {
        this2->field_1ec = 10;
      }
      else {
        this2->field_1ec = 0xb;
      }
      ctrl_enable(*(Control **)(this2->pad_21c + 0x134));
    }
    else if (*(int *)this2->pad_208 == 3) {
      this2->field_1ec = 5;
      ctrl_enable(*(Control **)(this2->pad_21c + 0x134));
    }
    else if (*(int *)this2->pad_208 == 4) {
      this2->field_1ec = 0xf;
      ctrl_enable(*(Control **)(this2->pad_21c + 0x134));
    }
    *(i32 *)(this2->pad_1f0 + 8) = (&parley_mode_left_kinds)[this2->field_1ec * 2];
    *(i32 *)this2->pad_1f0 = *(i32 *)(this2->pad_1f0 + 8);
    *(i32 *)(this2->pad_1f0 + 0xc) = (&parley_mode_right_kinds)[this2->field_1ec * 2];
    *(i32 *)(this2->pad_1f0 + 4) = *(i32 *)(this2->pad_1f0 + 0xc);
    parley_add_side_dialog((ViewWindow *)this2,*(i32 *)this2->pad_1f0,0);
    parley_add_side_dialog
              ((ViewWindow *)this2,*(i32 *)(this2->pad_1f0 + 4),1);
    break;
  case 5:
    uVar1 = radiogrp_get_selected(*(RadioGroupGetSelView **)(this2->pad_21c + 0x150));
    *(i32 *)(this2->pad_208 + 4) = uVar1;
    uVar1 = radiogrp_get_selected(*(RadioGroupGetSelView **)(this2->pad_21c + 0x154));
    *(i32 *)(this2->pad_208 + 8) = uVar1;
    this2->field_1ec = 0xe;
    *(i32 *)(this2->pad_1f0 + 8) = (&parley_mode_left_kinds)[this2->field_1ec * 2];
    *(i32 *)this2->pad_1f0 = *(i32 *)(this2->pad_1f0 + 8);
    *(i32 *)(this2->pad_1f0 + 0xc) = (&parley_mode_right_kinds)[this2->field_1ec * 2];
    *(i32 *)(this2->pad_1f0 + 4) = *(i32 *)(this2->pad_1f0 + 0xc);
    parley_add_side_dialog((ViewWindow *)this2,*(i32 *)this2->pad_1f0,0);
    parley_add_side_dialog
              ((ViewWindow *)this2,*(i32 *)(this2->pad_1f0 + 4),1);
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
    if (*(int *)(this2->pad_21c + 0x18) != 0) {
      operator_delete(*(void **)(this2->pad_21c + 0x18));
      this2->pad_21c[0x18] = '\0';
      this2->pad_21c[0x19] = '\0';
      this2->pad_21c[0x1a] = '\0';
      this2->pad_21c[0x1b] = '\0';
    }
    uVar1 = parley_send_offer(this2,this2->field_1ec);
    *(i32 *)(this2->pad_21c + 0x18) = uVar1;
    if ((this2->field_1ec == 6) && (this2->field_218 == 3)) {
      if ((*(byte *)&civs[human_civ].treaties[(this2->field_118)] & 8) == 0) {
        if ((*(byte *)&civs[human_civ].treaties[(this2->field_118)] & 4) == 0) {
          if ((*(byte *)&civs[human_civ].treaties[(this2->field_118)] & 2) != 0) {
            diplo_clear_treaty_flags(human_civ,this2->field_118,2);
          }
        }
        else {
          diplo_clear_treaty_flags(human_civ,this2->field_118,4);
        }
      }
      else {
        diplo_clear_treaty_flags(human_civ,this2->field_118,8);
      }
      parley_add_side_dialog
                ((ViewWindow *)this2,*(i32 *)this2->pad_1f0,0);
      parley_add_side_dialog
                ((ViewWindow *)this2,*(i32 *)(this2->pad_1f0 + 4),1);
    }
    else if (*(int *)(this2->pad_21c + 0x18) != 0) {
      this2->field_1ec = 1;
      *(i32 *)(this2->pad_1f0 + 8) = (&parley_mode_left_kinds)[this2->field_1ec * 2];
      *(i32 *)this2->pad_1f0 = *(i32 *)(this2->pad_1f0 + 8);
      *(i32 *)(this2->pad_1f0 + 0xc) = (&parley_mode_right_kinds)[this2->field_1ec * 2];
      *(i32 *)(this2->pad_1f0 + 4) = *(i32 *)(this2->pad_1f0 + 0xc);
      parley_add_side_dialog
                ((ViewWindow *)this2,*(i32 *)this2->pad_1f0,0);
      parley_add_side_dialog
                ((ViewWindow *)this2,*(i32 *)(this2->pad_1f0 + 4),1);
      ctrl_disable(*(Control **)(this2->pad_21c + 0x134));
    }
  }
  return;
}
#undef human_civ
#undef this2

/* 0052e326 auto */
#define this2 (*(ViewWindow * *)(frame_ + FRAME_OFF(0)))
void __cdecl parley_on_never_mind(void)

{
  iptr iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    this2 = (ViewWindow *)0x0;
  }
  else {
    this2 = (ViewWindow *)(iVar1 - 0x48);
  }
  wnd_activate((Wnd *)this2->pad_48);
  switch(this2->field_1ec) {
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
    this2->field_1ec = 3;
    ctrl_disable((Control *)this2->field_350);
    this2->field_1f8 = parley_mode3_left_kind;
    this2->field_1f0 = this2->field_1f8;
    this2->field_1fc = parley_mode3_right_kind;
    this2->field_1f4 = this2->field_1fc;
    parley_add_side_dialog(this2,this2->field_1f0,0);
    parley_add_side_dialog(this2,this2->field_1f4,1);
    break;
  case 0xe:
    this2->field_1ec = 5;
    this2->field_1f8 = parley_mode5_left_kind;
    this2->field_1f0 = this2->field_1f8;
    this2->field_1fc = parley_mode5_right_kind;
    this2->field_1f4 = this2->field_1fc;
    parley_add_side_dialog(this2,this2->field_1f0,0);
    parley_add_side_dialog(this2,this2->field_1f4,1);
  }
  return;
}
#undef this2

/* 0052e4c9 auto */
#define dlg_pending_idle_callback (*(i8 * *)((u8 *)&g.d_00635a3c))
#define parley_other_civ (*(int *)((u8 *)&g.d_0067a8c0))
#define local_8 (*(WindowObjectView * *)(frame_ + FRAME_OFF(0)))
void __cdecl parley_on_accept_offer(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = (WindowObjectView *)0x0;
  }
  else {
    local_8 = (WindowObjectView *)(iVar1 - 0x48);
  }
  wnd_activate((Wnd *)(local_8 + 0x12));
  net_send_message(0x83,*(i32 *)
                           (&net_player_slots + *(int *)(&net_civ_slots + parley_other_civ * 4) * 0x54),0,0,0
                     ,0,0,0,0,0);
  dlg_pending_idle_callback = ((void *)ADDR(0x00403c74, turn_popup_timeout_idle));
  popup_game_with_sprite(ADDR(0x6324f0, ((u8 *)&g.d_006324f0)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
  local_8[0x7b].field_0 = 3;
  parley_set_mode_sides(local_8,1);
  return;
}
#undef dlg_pending_idle_callback
#undef parley_other_civ
#undef local_8

/* 0052e57c auto */
#define parley_other_civ (*(int *)((u8 *)&g.d_0067a8c0))
#define this2 (*(ViewWindow * *)(frame_ + FRAME_OFF(0)))
void __cdecl parley_on_no_thanks(void)

{
  iptr iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    this2 = (ViewWindow *)0x0;
  }
  else {
    this2 = (ViewWindow *)(iVar1 - 0x48);
  }
  wnd_activate((Wnd *)this2->pad_48);
  net_send_message(0x84,*(i32 *)
                           (&net_player_slots + *(int *)(&net_civ_slots + parley_other_civ * 4) * 0x54),0,0,0
                     ,0,0,0,0,0);
  this2->field_1ec = 2;
  this2->field_1f8 = (&parley_mode_left_kinds)[this2->field_1ec * 2];
  this2->field_1f0 = this2->field_1f8;
  this2->field_1fc = (&parley_mode_right_kinds)[this2->field_1ec * 2];
  this2->field_1f4 = this2->field_1fc;
  parley_add_side_dialog(this2,this2->field_1f0,0);
  parley_add_side_dialog(this2,this2->field_1f4,1);
  return;
}
#undef parley_other_civ
#undef this2

/* 0052e685 auto */
#define parley_other_civ (*(int *)((u8 *)&g.d_0067a8c0))
#define local_8 (*(WindowObjectView * *)(frame_ + FRAME_OFF(0)))
void __cdecl parley_on_counter_offer(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = (WindowObjectView *)0x0;
  }
  else {
    local_8 = (WindowObjectView *)(iVar1 - 0x48);
  }
  wnd_activate((Wnd *)(local_8 + 0x12));
  net_send_message(0x85,*(i32 *)
                           (&net_player_slots + *(int *)(&net_civ_slots + parley_other_civ * 4) * 0x54),0,0,0
                     ,0,0,0,0,0);
  local_8[0x7b].field_0 = 3;
  parley_set_mode_sides(local_8,1);
  return;
}
#undef parley_other_civ
#undef local_8

/* 0052e71a auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl chat_on_mute_checkbox(int param_1)

{
  i32 uVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = wnd_get_active_child();
  if (local_8 == 0) {
    local_8 = 0;
  }
  else {
    local_8 -= 0x48;
  }
  wnd_activate((Wnd *)(local_8 + 0x48));
  if ((0x428 < param_1) && (param_1 < 0x430)) {
    uVar1 = checkbox_is_checked
                      (*(Control **)(&chat_mute_checkboxes + (param_1 - 0x428) * 4));
    *(i32 *)(&chat_muted_civs + (param_1 - 0x428) * 4) = uVar1;
  }
  return;
}
#undef local_8

/* 0052e7b7 auto */
#define chat_broadcast_all (*(int *)((u8 *)&g.d_0068aee4))
#define chat_mute_anonymous (*(i32 *)((u8 *)&g.d_0068aee0))
#define chat_remain_anonymous (*(i32 *)((u8 *)&g.d_0068aedc))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl chat_on_send_checkbox(int param_1)

{
  i32 uVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = wnd_get_active_child();
  if (local_8 == 0) {
    local_8 = 0;
  }
  else {
    local_8 -= 0x48;
  }
  wnd_activate((Wnd *)(local_8 + 0x48));
  switch(param_1) {
  case 0x415:
    chat_remain_anonymous = checkbox_is_checked(chat_anonymous_checkbox);
    break;
  case 0x416:
    chat_broadcast_all = checkbox_is_checked(chat_broadcast_checkbox);
    if (chat_broadcast_all != 0) {
      for (local_c = 1; local_c < 8; local_c++) {
        if (*(int *)(&chat_send_checkboxes + local_c * 4) != 0) {
          checkbox_set_checked(*(Control **)(&chat_send_checkboxes + local_c * 4),1);
          ctrl_show_and_redraw(*(Control **)(&chat_send_checkboxes + local_c * 4));
          *(i32 *)(&chat_send_to_civs + local_c * 4) = 1;
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
    param_1 -= 0x416;
    uVar1 = checkbox_is_checked(*(Control **)(&chat_send_checkboxes + param_1 * 4));
    *(i32 *)(&chat_send_to_civs + param_1 * 4) = uVar1;
    if ((*(int *)(&chat_send_to_civs + param_1 * 4) == 0) && (chat_broadcast_all != 0)) {
      checkbox_set_checked(chat_broadcast_checkbox,0);
      ctrl_show_and_redraw(chat_broadcast_checkbox);
      chat_broadcast_all = 0;
    }
    break;
  case 0x430:
    chat_mute_anonymous = checkbox_is_checked(chat_mute_anonymous_checkbox);
  }
  return;
}
#undef chat_broadcast_all
#undef chat_mute_anonymous
#undef chat_remain_anonymous
#undef local_c
#undef local_8

/* 0052e971 auto */
void __thiscall parley_update_buttons(ViewWindow *this)

{
  if ((this->field_348 != 0) && (this->field_34c != 0)) {
    if (this->session_mode != 2) {
      control_hide((Control *)this->field_340);
      ctrl_disable((Control *)this->field_340);
      control_hide((Control *)this->field_344);
      ctrl_disable((Control *)this->field_344);
    }
    switch(this->session_mode) {
    case 1:
    case 2:
      control_hide((Control *)this->field_34c);
      ctrl_disable((Control *)this->field_34c);
      ctrl_show_and_redraw((Control *)this->field_348);
      ctrl_disable((Control *)this->field_348);
      if (this->session_mode == 2) {
        if ((this->field_3bd == '\0') && (this->field_3be == '\0')) {
          control_hide((Control *)this->field_340);
          ctrl_disable((Control *)this->field_340);
          ctrl_show_and_redraw((Control *)this->field_344);
          ctrl_enable((Control *)this->field_344);
        }
        else {
          ctrl_show_and_redraw((Control *)this->field_340);
          ctrl_enable((Control *)this->field_340);
          control_hide((Control *)this->field_344);
          ctrl_disable((Control *)this->field_344);
        }
      }
      break;
    case 3:
    case 5:
      control_hide((Control *)this->field_34c);
      ctrl_disable((Control *)this->field_34c);
      ctrl_show_and_redraw((Control *)this->field_348);
      ctrl_enable((Control *)this->field_348);
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
      ctrl_show_and_redraw((Control *)this->field_34c);
      control_hide((Control *)this->field_348);
      ctrl_disable((Control *)this->field_348);
      if (this->timer_last_value == 0) {
        ctrl_disable((Control *)this->field_34c);
      }
      else {
        ctrl_enable((Control *)this->field_34c);
      }
      break;
    case 0xe:
      ctrl_show_and_redraw((Control *)this->field_34c);
      control_hide((Control *)this->field_348);
      ctrl_disable((Control *)this->field_348);
      if ((this->show_turn_status == 0) || (this->timer_last_value == 0)) {
        ctrl_disable((Control *)this->field_34c);
      }
      else {
        ctrl_enable((Control *)this->field_34c);
      }
    }
  }
  return;
}

/* 0052ec47 auto */
#define unit (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(24)))
iptr __thiscall parley_find_unit_by_id(WindowObjectView *this,int param_1)

{
  short x2;
  short y2;
  bool bVar3;
  iptr x;
  int y;
  int iVar6;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  unit = (iptr)game.num_units;
  do {
    unit--;
    if (unit < 0) {
      return 0xffffffff;
    }
  } while ((units[unit].id == 0) || (units[unit].id != param_1));
  x2 = units[unit].x;
  y2 = units[unit].y;
  bVar3 = false;
  local_8 = 0;
  do {
    if (7 < local_8) {
LAB_0052ed47:
      if ((!bVar3) && (y = unit_stack_sum(unit,2), y != 1)) {
        unit = -2;
      }
      return unit;
    }
    x = map_wrap_x((int)(char)(&dir_dx_table)[local_8] + (int)x2);
    y = (int)(char)(&dir_dy_table)[local_8] + (int)y2;
    iVar6 = map_in_bounds(x,y);
    if ((iVar6 != 0) && (y = tile_is_ocean(x,y), y == 0)) {
      bVar3 = true;
      goto LAB_0052ed47;
    }
    local_8++;
  } while( true );
}
#undef unit
#undef local_8

/* 0052ed95 auto */
#define city (*(iptr *)(frame_ + FRAME_OFF(0)))
iptr __thiscall parley_find_city_by_id(WindowObjectView *this,int param_1)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  city = (iptr)game.num_cities;
  do {
    city--;
    if (city < 0) {
      return 0xffffffff;
    }
  } while ((cities[city].id == 0) || (cities[city].id != param_1));
  return city;
}
#undef city

/* 0055ae80 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define mp_turn_civ (*(i8 *)((u8 *)&g.d_006ad578))
#define player_turn_active (*(char *)((u8 *)&g.d_0064b9bc))
#define mp_turn_civ_i32 (*(i32 *)((u8 *)&g.d_006ad578))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl mp_turn_timer_stop(int param_1)

{
  if (mp_turn_civ_i32 == human_civ) {
    city_window_close();
    intel_report_end_modal();
    throneroom_close();
    pedia_end_modal();
  }
  if (mp_turn_timer_handle != 0) {
    game_timer_destroy(mp_turn_timer_handle);
    mp_turn_timer_handle = 0;
    status_draw_timer_bar(100,0xffffffff);
    if (((param_1 != 0) && (2 < game.multiplayer)) && (player_turn_active != '\0')) {
      net_send_message(0x6e,0xff,0,0,0,0,0,0,0,0);
    }
  }
  return;
}
#undef human_civ
#undef mp_turn_civ
#undef player_turn_active
#undef mp_turn_civ_i32

/* 0055af2e auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define mp_turn_civ (*(i8 *)((u8 *)&g.d_006ad578))
#define mp_turn_seconds_left (*(int *)((u8 *)&g.d_00633a78))
#define mp_turn_time_limit_ms (*(int *)((u8 *)&g.d_00654b70))
#define mp_turn_timer_blink (*(i32 *)((u8 *)&g.d_006ab5ac))
#define mp_turn_timer_last_ticks_i32 (*(i32 *)((u8 *)&g.d_00633a7c))
#define main_view_timer_cache_i32 (*(i32 *)((u8 *)&g.d_0066c990))
#define mp_turn_civ_i32 (*(i32 *)((u8 *)&g.d_006ad578))
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(8)))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(16)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl mp_turn_timer_start(int param_1)

{
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (mp_turn_civ_i32 == human_civ) {
    city_window_close();
    intel_report_end_modal();
    throneroom_close();
    pedia_end_modal();
  }
  mp_turn_seconds_left = mp_turn_time_limit_ms / 1000;
  mp_turn_timer_blink = 0;
  main_view_timer_cache_i32 = 0xffffffff;
  frame_wnd_draw_caption((FrameWindow *)&map_views);
  local_14 = main_view_frame_left;
  local_10 = main_view_frame_top;
  local_c = main_view_frame_right;
  local_8 = main_view_client_top;
  wnd_blit_surface_rect((DibSurface *)&map_views,(iptr)&local_14);
  if (mp_turn_timer_handle != 0) {
    game_timer_destroy(mp_turn_timer_handle);
  }
  mp_turn_timer_handle = game_timer_create(ADDR(0x402220, mp_turn_timer_tick),500,1);
  mp_turn_timer_last_ticks_i32 = timer_ticks();
  if ((param_1 != 0) && (2 < game.multiplayer)) {
    net_send_message(0x6d,0xff,0,0,0,0,0,0,0,0);
  }
  return;
}
#undef human_civ
#undef mp_turn_civ
#undef mp_turn_seconds_left
#undef mp_turn_time_limit_ms
#undef mp_turn_timer_blink
#undef mp_turn_timer_last_ticks_i32
#undef main_view_timer_cache_i32
#undef mp_turn_civ_i32
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 0055b046 auto */
#define main_view_timer_shown (*(int *)((u8 *)&g.d_0066c988))
#define mp_turn_seconds_left (*(int *)((u8 *)&g.d_00633a78))
#define mp_turn_timer_last_ticks_i32 (*(i32 *)((u8 *)&g.d_00633a7c))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl mp_turn_timer_resume(int param_1)

{
  city_window_close();
  intel_report_end_modal();
  throneroom_close();
  pedia_end_modal();
  if ((mp_turn_seconds_left != 0) && (main_view_timer_shown != 0)) {
    if (mp_turn_timer_handle != 0) {
      game_timer_destroy(mp_turn_timer_handle);
    }
    mp_turn_timer_handle = game_timer_create(ADDR(0x402220, mp_turn_timer_tick),500,1);
    mp_turn_timer_last_ticks_i32 = timer_ticks();
    if ((param_1 != 0) && (2 < game.multiplayer)) {
      net_send_message(0x6f,0xff,0,0,0,0,0,0,0,0);
    }
  }
  return;
}
#undef main_view_timer_shown
#undef mp_turn_seconds_left
#undef mp_turn_timer_last_ticks_i32

/* 0055b0fb: written by hand in src/game/timer_display.c */

/* 0055b2c6 auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define main_view_timer_shown (*(i32 *)((u8 *)&g.d_0066c988))
#define mp_turn_time_limit_ms (*(int *)((u8 *)&g.d_00654b70))
#define player_turn_active (*(i8 *)((u8 *)&g.d_0064b9bc))
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(8)))
#define local_c (*(i32 *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(16)))
void __cdecl mp_cmd_change_timer(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  mp_turn_timer_stop(1);
  GetAsyncKeyState(0x1b);
  iVar1 = setup_choose_game_timer(1);
  if (iVar1 == 0) {
    if (mp_turn_time_limit_ms == 0) {
      main_view_timer_shown = 0;
      frame_wnd_draw_caption((FrameWindow *)&map_views);
      local_14 = main_view_frame_left;
      local_10 = main_view_frame_top;
      local_c = main_view_frame_right;
      local_8 = main_view_client_top;
      wnd_blit_surface_rect((DibSurface *)&map_views,(iptr)&local_14);
    }
    else {
      main_view_timer_shown = 1;
      mp_turn_timer_start(1);
    }
    if (2 < game.multiplayer) {
      net_send_message(0x6c,0xff,mp_turn_time_limit_ms,0,0,0,0,0,0,0);
    }
  }
  else {
    mp_turn_timer_resume(1);
  }
  if (autoplay_active != 0) {
    player_turn_active = 0;
  }
  return;
}
#undef autoplay_active
#undef main_view_timer_shown
#undef mp_turn_time_limit_ms
#undef player_turn_active
#undef local_14
#undef local_10
#undef local_c
#undef local_8

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
    mp_mouse_watchdog_timer = game_timer_create(ADDR(0x401451, mp_mouse_watchdog_tick),500,1);
  }
  return;
}

/* 0055b451 auto */
#define mp_window_drag_active (*(char *)((u8 *)&g.d_00633a84))
i32 __cdecl mp_window_drag_mouse_hook(void)

{
  if (mp_window_drag_active != '\0') {
    mp_mouse_watchdog_tick(0,0);
  }
  return 0;
}
#undef mp_window_drag_active

/* 0055b47e auto */
#define app_hinstance (*(HINSTANCE *)((u8 *)&g.d_006e4ff0))
#define mp_window_drag_active (*(i8 *)((u8 *)&g.d_00633a84))
#define mp_window_drag_start_ticks (*(i32 *)((u8 *)&g.d_00633a88))
#define mp_window_drag_wnd (*(i32 *)((u8 *)&g.d_00633a90))
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define mp_window_drag_flag_i32 (*(i32 *)((u8 *)&g.d_00633a8c))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl mp_window_drag_begin(void)

{
  dbg_log(ADDR(0x633a94, ((u8 *)&g.d_00633a94)));
  mp_window_drag_active = 1;
  mp_window_drag_start_ticks = timer_ticks();
  mp_window_drag_flag_i32 = 0;
  mp_window_drag_wnd = wnd_get_active_child();
  if (net_host_flag != '\0') {
    net_send_message(0x5d,0xff,0,0,0,0,0,0,0,0);
    XD_FlushSendBuffer(5000);
  }
  mp_window_drag_hook = SetWindowsHookExA(7,(HOOKPROC)((void *)ADDR(0x00402856, mp_window_drag_mouse_hook)),app_hinstance,0);
  return;
}
#undef app_hinstance
#undef mp_window_drag_active
#undef mp_window_drag_start_ticks
#undef mp_window_drag_wnd
#undef net_host_flag
#undef mp_window_drag_flag_i32

/* 0055b515 auto */
#define mp_window_drag_active (*(i8 *)((u8 *)&g.d_00633a84))
#define mp_window_drag_start_ticks (*(i32 *)((u8 *)&g.d_00633a88))
#define mp_window_drag_wnd (*(i32 *)((u8 *)&g.d_00633a90))
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define mp_window_drag_flag_i32 (*(i32 *)((u8 *)&g.d_00633a8c))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl mp_window_drag_end(void)

{
  dbg_log(ADDR(0x633aa8, ((u8 *)&g.d_00633aa8)));
  mp_window_drag_active = 0;
  mp_window_drag_start_ticks = 0;
  mp_window_drag_flag_i32 = 0;
  mp_window_drag_wnd = 0;
  UnhookWindowsHookEx(mp_window_drag_hook);
  if (net_host_flag != '\0') {
    net_send_message(0x5e,0xff,0,0,0,0,0,0,0,0);
    XD_FlushSendBuffer(5000);
  }
  return;
}
#undef mp_window_drag_active
#undef mp_window_drag_start_ticks
#undef mp_window_drag_wnd
#undef net_host_flag
#undef mp_window_drag_flag_i32

/* 0055b59e auto */
#define mp_window_drag_active (*(char *)((u8 *)&g.d_00633a84))
#define mp_window_drag_wnd (*(WndBase * *)((u8 *)&g.d_00633a90))
void __cdecl mp_release_mouse_capture(void)

{
  iptr iVar1;
  UINT Msg;
  WPARAM wParam;
  LPARAM lParam;
  
  if (mp_window_drag_active != '\0') {
    if (mp_window_drag_wnd != (WndBase *)0x0) {
      lParam = 0;
      wParam = 0;
      Msg = 0x202;
      iVar1 = wnd_get_window(mp_window_drag_wnd);
      PostMessageA(*(HWND *)(iVar1 + 4),Msg,wParam,lParam);
      wnd_release_capture(mp_window_drag_wnd);
    }
    mp_window_drag_active = '\0';
  }
  return;
}
#undef mp_window_drag_active
#undef mp_window_drag_wnd

/* 0055b5fa auto */
#define mp_window_drag_active (*(char *)((u8 *)&g.d_00633a84))
#define mp_window_drag_start_ticks (*(int *)((u8 *)&g.d_00633a88))
#define player_has_quit (*(char *)((u8 *)&g.d_006ad685))
void __cdecl mp_mouse_watchdog_tick(i32 param_1,i32 param_2)

{
  int iVar1;
  
  if ((((2 < game.multiplayer) && (net_player_count != 1)) && (mp_window_drag_active != '\0')) &&
     ((iVar1 = timer_ticks(), mp_window_drag_start_ticks + 0x26c < iVar1 && (player_has_quit == '\0')))) {
    mp_release_mouse_capture();
  }
  mp_mouse_watchdog_start();
  return;
}
#undef mp_window_drag_active
#undef mp_window_drag_start_ticks
#undef player_has_quit

/* 0056e270 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
LobbyListCtorView * __thiscall lobby_list_ctor(LobbyListCtorView *this)

{
  u8 *puVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  this->next_id = 1;
  this->entries = 0;
  for (local_8 = 0; local_8 < 7; local_8++) {
    puVar1 = this->pad_2c + local_8 * 4 + 0x28;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
  }
  return this;
}
#undef local_8

/* 0056e2c9 auto */
void __thiscall lobby_list_dtor(void *this)

{
  net_free_game_list(&net_session);
  return;
}

/* 0056e2e9 auto */
#define dlg_pending_idle_callback (*(i8 * *)((u8 *)&g.d_00635a3c))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define net_connection_title (*(i32 *)((u8 *)&g.d_006ad63c))
#define net_local_slot (*(i32 *)((u8 *)&g.d_006ad304))
#define net_session_phase (*(i32 *)((u8 *)&g.d_006ad640))
#define net_slot_active_flags (*(i8 *)((u8 *)&g.d_006ad359))
#define net_slot_civs (*(int *)((u8 *)&g.d_006ad35c))
#define net_slot_host_flags (*(i8 *)((u8 *)&g.d_006ad358))
#define prefs_net_game_name (*(i8 *)((u8 *)&g.d_00666550))
#define prefs_net_ip_address (*(i8 *)((u8 *)&g.d_006665b0))
#define prefs_net_player_name (*(i8 *)((u8 *)&g.d_00666570))
#define saved_resume_new_game (*(short *)((u8 *)&g.d_00654fa6))
#define saved_turn_civ (*(char *)((u8 *)&g.d_00654fa4))
#define scenario_event_count (*(iptr *)((u8 *)&g.d_0064b998))
#define scenario_events_loaded (*(iptr *)((u8 *)&g.d_00627670))
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
#define turn_resume_civ (*(char *)((u8 *)&g.d_00628048))
#define turn_resume_new_game (*(int *)((u8 *)&g.d_0062c488))
#define net_wait_start_ticks_i32 (*(i32 *)((u8 *)&g.d_006ad674))
#define local_28 (*(uptr *)(frame_ + FRAME_OFF(0)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(24)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(28)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(32)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __thiscall lobby_host_wait_players(LobbyList *this,i32 param_1,int param_2)

{
  uint *puVar1;
  Dialog *this_00;
  int iVar2;
  int iVar3;
  int iVar4;
  i32 uVar5;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  if ((param_2 == 2) || (param_2 == 3)) {
    net_send_message(2,0,0,0,0,0,0,0,0,0);
    this->dialog = 0;
    net_server_address = 0;
    crt_strcpy(&net_game_name,&prefs_net_game_name);
    crt_strcpy(&net_local_player_name,&prefs_net_player_name);
    crt_strcpy(&net_host_player_name,&prefs_net_player_name);
  }
  else {
    this_00 = operator_new(0x2f4);
    local_8 = 0;
    if (this_00 == (Dialog *)0x0) {
      local_28 = 0;
    }
    else {
      local_28 = dialog_ctor(this_00,0x4000);
    }
    local_8 = 0xffffffff;
    this->dialog = local_28;
    if (this->dialog == 0) {
      err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x633ec4, ((u8 *)&g.d_00633ec4)),ADDR(0x633e9c, ((u8 *)&g.d_00633e9c)),0x34);
    }
    *(i8 **)(this[1].pad_8 + 0x18) = dialog_button_labels;
    str_clear((iptr)(this + 1));
    str_append_label((iptr)(this + 1),0x28b);
    dialog_button_labels = (i8 *)(this + 1);
    dlg_reset((Dialog *)this->dialog,0x81801);
    text_clear();
    text_append_label(0x288);
    if (param_2 == 0) {
      crt_strcat(&text_buffer,&lobby_ip_sep_str);
      crt_strcat(&text_buffer,&prefs_net_ip_address);
    }
    dialog_set_title((DialogWindowView *)this->dialog,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    text_clear();
    text_append_label(0x120);
    dialog_add_button((DialogButtonsView *)this->dialog,ADDR(0x679640, ((u8 *)&g.d_00679640)));
    lobby_add_waiting_entry(this);
    dialog_set_listbox((DialogTextView *)this->dialog,7,0x1b7,0);
    dialog_set_default_choice((DialogOptionList *)this->dialog,this->next_id - 1);
    dialog_render((Dialog *)this->dialog);
    wnd_set_modal_idle_callback((ModalMenuWindow *)(*(int *)this->dialog + 0x48),ADDR(0x402dba, lobby_dialog_idle));
    if (net_lobby_launch_mode == 2) {
      dbg_log(ADDR(0x633ee0, ((u8 *)&g.d_00633ee0)));
      iVar2 = XD_LobbySendMessage(1);
      if (iVar2 != 0) {
        dbg_logf(ADDR(0x633f18, ((u8 *)&g.d_00633f18)),iVar2);
      }
      dbg_log(ADDR(0x633f48, ((u8 *)&g.d_00633f48)));
      iVar2 = XD_LobbySendMessage(3);
      if (iVar2 != 0) {
        dbg_logf(ADDR(0x633f7c, ((u8 *)&g.d_00633f7c)),iVar2);
      }
    }
    while( true ) {
      net_send_message(2,0,0,0,0,0,0,0,0,0);
      puVar1 = (uint *)(this->dialog + 0x3c);
      *puVar1 = *puVar1 & 0xfffffbff;
      *(i32 *)(this->dialog + 0xd8) = 0;
      *(i32 *)(this->dialog + 0xdc) = *(i32 *)(this->dialog + 0xd8);
      iVar2 = dlg_show_modal((Dialog *)this->dialog,0);
      if (*(int *)(this->dialog + 0xdc) != 1) break;
      iVar3 = lobby_find_entry_by_id(this,iVar2);
      iVar2 = lobby_slot_for_entry_id(this,iVar2);
      if ((iVar3 != 0) && (iVar4 = lobby_find_waiting_entry(this), iVar4 == 0)) {
        net_send_message(5,*(i32 *)(&net_player_slots + iVar2 * 0x54),0,0,0,0,0,0,0,0);
        XD_FlushSendBuffer(180000);
        XD_ServerCloseConnection((ushort)*(i32 *)(&net_player_slots + iVar2 * 0x54));
        uVar5 = lobby_entry_neighbor(this,iVar3);
        *(i32 *)(this->dialog + 0x220) = uVar5;
        lobby_remove_entry(this,iVar3);
        net_remove_player
                  ((NetSession *)&net_session,*(i32 *)(&net_player_slots + iVar2 * 0x54));
        lobby_add_waiting_entry(this);
      }
    }
    if (iVar2 < 0) {
      net_send_message(0xb,0xff,0,0,0,0,0,0,0,0);
      dialog_button_labels = *(i8 **)(this[1].pad_8 + 0x18);
      lobby_clear_player_list(this);
      if ((Dialog *)this->dialog != (Dialog *)0x0) {
        dialog_scalar_dtor((Dialog *)this->dialog,1);
      }
      this->dialog = 0;
      XD_StopConnections();
      uVar5 = 0;
      goto LAB_0056ec81;
    }
    crt_strcpy(&net_server_address,&prefs_net_ip_address);
    crt_strcpy(&net_game_name,&prefs_net_game_name);
    crt_strcpy(&net_local_player_name,&prefs_net_player_name);
    crt_strcpy(&net_host_player_name,&prefs_net_player_name);
    dialog_close((Dialog *)this->dialog);
    dialog_button_labels = *(i8 **)(this[1].pad_8 + 0x18);
    lobby_clear_player_list(this);
    if ((Dialog *)this->dialog != (Dialog *)0x0) {
      dialog_scalar_dtor((Dialog *)this->dialog,1);
    }
    this->dialog = 0;
    wnd_flush_paint();
  }
  if (1 < net_player_count) {
    net_send_message(4,0xff,0,0,0,0,0,0,0,0);
  }
  net_session_phase = 1;
  net_send_message(0x28,0xff,1,0,0,0,0,0,0,0);
  crt_strcpy(&net_slot_player_names,&prefs_net_player_name);
  diffeng_register_blocks();
  net_reset_msg_counts();
  net_send_message(6,0xff,0,0,0,0,0,0,0,0);
  net_send_message(9,0xff,0,0,0,0,0,0,0,0);
  net_local_slot = 0;
  iVar2 = game_profile_popup(1);
  if (iVar2 == -1) {
    net_send_message(0x32,0,0,0,0,0,0,0,0,0);
    XD_FlushSendBuffer(180000);
    uVar5 = 0;
  }
  else {
    if ((saved_resume_new_game == 0) && (saved_turn_civ == '\0')) {
      leaders_reset_custom_names();
      game.civs_alive = '\0';
      iVar2 = setup_choose_tribe(0,3,0);
      if (iVar2 != 0) {
        if (1 < net_player_count) {
          net_send_message(0xb,0xff,0,0,0,0,0,0,0,0);
        }
        XD_StopConnections();
        uVar5 = 0;
        goto LAB_0056ec81;
      }
    }
    else {
      iVar2 = net_choose_civ_dialog(0);
      if (iVar2 != 0) {
        if (1 < net_player_count) {
          net_send_message(0xb,0xff,0,0,0,0,0,0,0,0);
        }
        XD_StopConnections();
        uVar5 = 0;
        goto LAB_0056ec81;
      }
    }
    *(i32 *)(&net_civ_slots + game.player_civ * 4) = 0;
    net_slot_civs = (int)game.player_civ;
    net_slot_active_flags = 1;
    net_slot_host_flags = 1;
    if (1 < net_player_count) {
      crt_strcpy(&text_string_args,net_connection_title);
      dlg_pending_idle_callback = ((void *)ADDR(0x0040266c, lobby_wait_civs_chosen_idle));
      net_wait_start_ticks_i32 = timer_ticks();
      iVar2 = popup_game_sprite_flags(ADDR(0x633fac, ((u8 *)&g.d_00633fac)),0x2000001,ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
      if (iVar2 == -1) {
        net_send_message(0xb,0xff,0,0,0,0,0,0,0,0);
        XD_StopConnections();
        uVar5 = 0;
        goto LAB_0056ec81;
      }
    }
    if (1 < net_player_count) {
      net_send_message(4,0xff,0,0,0,0,0,0,0,0);
    }
    if ((turn_resume_civ == '\0') && (turn_resume_new_game == 0)) {
      uVar5 = setup_choose_hotseat_players();
      setup_choose_opponents(uVar5);
      prefs_save_civ2dat();
      rules_load_advances(1);
      rules_load_units(1);
      rules_load_improvements(1);
      snd_menu_end();
      map_generate(param_1);
      diffeng_register_blocks();
      diffeng_alloc_mirror();
      game_init_new();
      if (setup_accelerated_start != 0) {
        game_accelerated_start(setup_accelerated_start - 1);
      }
      if (turn_resume_civ != '\0') {
        game.player_civ = turn_resume_civ;
        human_civ = (iptr)turn_resume_civ;
      }
    }
    else {
      diffeng_register_blocks();
      diffeng_alloc_mirror();
    }
    text_close_file();
    if (1 < net_player_count) {
      net_send_message(10,0xff,0,0,0,0,0,0,0,0);
      net_send_state_diff(0xff,1,0,0,0);
      XD_FlushSendBuffer(5000);
      net_send_message(0x25,0xff,scenario_events_loaded,scenario_event_count,0,0,0,0,0,0);
      net_send_message(0x16,0xff,0,0,0,0,0,0,0,0);
      XD_FlushSendBuffer(180000);
    }
    net_reset_msg_counts();
    net_session_phase = 3;
    net_send_message(0x28,0xff,3,0,0,0,0,0,0,0);
    uVar5 = 1;
  }
LAB_0056ec81:
  return uVar5;
}
#undef dlg_pending_idle_callback
#undef human_civ
#undef net_connection_title
#undef net_local_slot
#undef net_session_phase
#undef net_slot_active_flags
#undef net_slot_civs
#undef net_slot_host_flags
#undef prefs_net_game_name
#undef prefs_net_ip_address
#undef prefs_net_player_name
#undef saved_resume_new_game
#undef saved_turn_civ
#undef scenario_event_count
#undef scenario_events_loaded
#undef text_buffer
#undef turn_resume_civ
#undef turn_resume_new_game
#undef net_wait_start_ticks_i32
#undef local_28
#undef local_10
#undef puStack_c
#undef local_8

/* 0056ec92 auto */
#define dialog_stack_top (*(int * *)((u8 *)&g.d_006ad678))
#define net_session_phase (*(i32 *)((u8 *)&g.d_006ad640))
#define net_slot_active_flags (*(i8 *)((u8 *)&g.d_006ad359))
#define net_slot_civs (*(i32 *)((u8 *)&g.d_006ad35c))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
void __cdecl lobby_wait_civs_chosen_idle(void)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  net_process_messages((NetSession *)&net_session,1,0);
  local_8 = 0;
  for (local_c = 1; local_c < 7; local_c++) {
    if (((&net_slot_active_flags)[local_c * 0x54] == 1) && ((&net_slot_civs)[local_c * 0x15] == -1)) {
      local_8++;
    }
  }
  if (local_8 == 0) {
    dialog_stack_top[0xf] = dialog_stack_top[0xf] | 0x400;
    net_session_phase = 2;
    net_send_message(0x28,0xff,2,0,0,0,0,0,0,0);
    wnd_end_modal_loop((ModalMenuWindow *)(*dialog_stack_top + 0x48));
  }
  return;
}
#undef dialog_stack_top
#undef net_session_phase
#undef net_slot_active_flags
#undef net_slot_civs
#undef local_c
#undef local_8

/* 0056ed62 auto */
void __cdecl lobby_dialog_idle(void)

{
  net_process_messages((NetSession *)&net_session,1,0);
  return;
}

/* 0056edd3 auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
iptr __thiscall lobby_entry_neighbor(LobbyList *this,iptr param_1)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = param_1;
  if (*(int *)(param_1 + 0x10) != 0) {
    local_8 = *(iptr *)(param_1 + 0x10);
  }
  if ((local_8 == param_1) && (*(int *)(param_1 + 0x14) != 0)) {
    local_8 = *(iptr *)(param_1 + 0x14);
  }
  return local_8;
}
#undef local_8

/* 0056ee2c auto */
#define local_c (*(void * *)(frame_ + FRAME_OFF(4)))
void __thiscall lobby_clear_player_list(LobbyList *this)

{
  void *pvVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = (void *)this->entries;
  while (local_c != (void *)0x0) {
    pvVar1 = *(void **)((int)local_c + 0x10);
    operator_delete(*(void **)((int)local_c + 8));
    operator_delete(local_c);
    local_c = pvVar1;
  }
  this->entries = 0;
  *(i32 *)(this->dialog + 0x28) = 0;
  *(i32 *)(this->dialog + 0x228) = 0;
  *(i32 *)(this->dialog + 0x220) = 0;
  return;
}
#undef local_c

/* 0056eed7 auto */
void __thiscall lobby_remove_entry(LobbyList *this,void *param_1)

{
  int *piVar1;
  
  if (param_1 != (void *)0x0) {
    if (*(int *)((int)param_1 + 0x14) == 0) {
      *(i32 *)(this->dialog + 0x228) = *(i32 *)((int)param_1 + 0x10);
      this->entries = *(uptr *)(this->dialog + 0x228);
    }
    else {
      *(i32 *)(*(int *)((int)param_1 + 0x14) + 0x10) = *(i32 *)((int)param_1 + 0x10);
    }
    if (*(int *)((int)param_1 + 0x10) != 0) {
      *(i32 *)(*(int *)((int)param_1 + 0x10) + 0x14) = *(i32 *)((int)param_1 + 0x14);
    }
    operator_delete(*(void **)((int)param_1 + 8));
    operator_delete(param_1);
    piVar1 = (int *)(this->dialog + 0x28);
    *piVar1 = *piVar1 - 1;
  }
  return;
}

/* 0056ef93 auto */
#define local_10 (*(uptr *)(frame_ + FRAME_OFF(0)))
#define local_c (*(uptr *)(frame_ + FRAME_OFF(4)))
uint * __thiscall lobby_add_player_entry(LobbyList *this,iptr param_1,uint param_2)

{
  int *piVar1;
  uint *puVar2;
  size_t sVar3;
  void *pvVar4;
  int iVar5;
  int iVar6;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_10 = 0;
  for (local_c = this->entries; local_c != 0; local_c = *(uptr *)(local_c + 0x10)) {
    local_10 = local_c;
  }
  puVar2 = operator_new(0x18);
  puVar2[4] = 0;
  puVar2[5] = local_10;
  if (local_10 == 0) {
    this->entries = (uptr)puVar2;
    *(uint **)(this->dialog + 0x228) = puVar2;
  }
  else {
    *(uint **)(local_10 + 0x10) = puVar2;
  }
  *puVar2 = 0;
  sVar3 = _strlen((char *)param_1);
  pvVar4 = operator_new(sVar3 + 1);
  puVar2[2] = (uint)pvVar4;
  crt_strcpy(puVar2[2],param_1);
  if (*(char *)param_1 == '\0') {
    *puVar2 = *puVar2 | 1;
  }
  puVar2[1] = param_2;
  puVar2[3] = 0;
  iVar5 = font_text_width(*(GameFont **)(this->dialog + 8),puVar2[2]);
  iVar6 = dialog_option_icon_width((DialogCore *)this->dialog);
  iVar5 = iVar5 + iVar6 + *(int *)(this->dialog + 0xac) + 5;
  iVar6 = *(int *)(this->dialog + 0x118);
  if (iVar6 <= iVar5) {
    iVar6 = iVar5;
  }
  *(int *)(this->dialog + 0x118) = iVar6;
  piVar1 = (int *)(this->dialog + 0x28);
  *piVar1 = *piVar1 + 1;
  *(uptr *)(this->dialog + 0x228) = this->entries;
  *(i32 *)(this->dialog + 0x210) = *(i32 *)(this->dialog + 0x228);
  return puVar2;
}
#undef local_10
#undef local_c

/* 0056f113 auto */
#define net_lobby_list (*(LobbyList * *)((u8 *)&g.d_006ad10c))
#define net_slot_active_flags (*(i8 *)((u8 *)&g.d_006ad359))
#define local_10 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_c (*(uptr *)(frame_ + FRAME_OFF(4)))
void __cdecl lobby_refresh_player_list(void)

{
  int iVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (net_lobby_list != (LobbyList *)0x0) {
    iVar1 = *(int *)(*(int *)(net_lobby_list->field_0 + 0x220) + 4);
    lobby_clear_player_list(net_lobby_list);
    if (net_player_count == 0) {
      lobby_add_waiting_entry(net_lobby_list);
    }
    else {
      for (local_10 = 1; local_10 < 7; local_10++) {
        if ((&net_slot_active_flags)[local_10 * 0x54] != '\0') {
          if (*(int *)(&net_slot_lobby_ids + local_10 * 0x54) == 0) {
            *(u32 *)(&net_slot_lobby_ids + local_10 * 0x54) = net_lobby_list->field_4;
            net_lobby_list->field_4++;
          }
          lobby_add_player_entry
                    (net_lobby_list,(iptr)(&net_slot_player_names + local_10 * 0x54),
                     *(i32 *)(&net_slot_lobby_ids + local_10 * 0x54));
        }
      }
      lobby_add_waiting_entry(net_lobby_list);
    }
    for (local_c = net_lobby_list->field_28; (local_c != 0 && (*(int *)(local_c + 4) != iVar1));
        local_c = *(uptr *)(local_c + 0x10)) {
    }
    if (local_c == 0) {
      for (local_c = net_lobby_list->field_28;
          (*(int *)(local_c + 0x10) != 0 && (*(int *)(local_c + 4) < iVar1));
          local_c = *(uptr *)(local_c + 0x10)) {
      }
      if (local_c == 0) {
        local_c = net_lobby_list->field_28;
      }
    }
    *(uptr *)(net_lobby_list->field_0 + 0x228) = net_lobby_list->field_28;
    *(i32 *)(net_lobby_list->field_0 + 0x210) = *(i32 *)(net_lobby_list->field_0 + 0x228);
    dialog_set_default_choice
              ((DialogOptionList *)net_lobby_list->field_0,*(iptr *)(local_c + 4));
    dialog_render((Dialog *)net_lobby_list->field_0);
  }
  return;
}
#undef net_lobby_list
#undef net_slot_active_flags
#undef local_10
#undef local_c

/* 0056f301 auto */
#define net_lobby_list (*(i32 * *)((u8 *)&g.d_006ad10c))
void __thiscall lobby_add_waiting_entry(LobbyList *this)

{
  i32 uVar1;
  
  if (this->entries == 0) {
    text_clear();
    text_append_label(0x28c);
    uVar1 = net_lobby_list[1];
    net_lobby_list[1]++;
    lobby_add_player_entry(this,ADDR(0x679640, ((u8 *)&g.d_00679640)),uVar1);
    dialog_set_default_choice
              ((DialogOptionList *)*net_lobby_list,*(iptr *)(net_lobby_list[10] + 4));
  }
  return;
}
#undef net_lobby_list

/* 0056f372 auto */
#define text_buffer (*(i8 *)((u8 *)&g.d_00679640))
i32 __thiscall lobby_find_waiting_entry(LobbyList *this)

{
  int iVar1;
  uptr uVar1;
  
  text_clear();
  text_append_label(0x28c);
  uVar1 = this->entries;
  if (((uVar1 != 0) && (*(int *)(uVar1 + 0x10) == 0)) &&
     (iVar1 = _strcmp(&text_buffer,*(char **)(uVar1 + 8)), iVar1 == 0)) {
    return uVar1;
  }
  return 0;
}
#undef text_buffer

/* 0056f3e0 auto */
#define local_8 (*(uptr *)(frame_ + FRAME_OFF(0)))
uptr __thiscall lobby_find_entry_by_id(LobbyList *this,int param_1)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = this->entries; (local_8 != 0 && (*(int *)(local_8 + 4) != param_1));
      local_8 = *(uptr *)(local_8 + 0x10)) {
  }
  return local_8;
}
#undef local_8

/* 0056f42b auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
int __thiscall lobby_slot_for_entry_id(LobbyList *this,int param_1)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; (local_8 < 7 && (*(int *)(&net_slot_lobby_ids + local_8 * 0x54) != param_1));
      local_8 = local_8 + 1) {
  }
  return local_8;
}
#undef local_8

/* 00587a90 auto */
#define local_38 (*(u8 * *)(frame_ + FRAME_OFF(0)))
#define local_34 (*(u8 * *)(frame_ + FRAME_OFF(4)))
#define local_30 (*(i32 *)(frame_ + FRAME_OFF(8)))
#define local_28 (*(i32 *)(frame_ + FRAME_OFF(16)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(24)))
#define local_1c (*(i32 *)(frame_ + FRAME_OFF(28)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(32)))
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(36)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(40)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(44)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(48)))
void __thiscall
parley_create_city_list_pane(ListPaneWindow *this,iptr param_1,int param_2,i32 param_3)

{
  u8 *puVar1;
  int iVar2;
  int iVar3;
  Control *pCVar4;
  i8 frame_[FRAME_OFF(56)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  local_20 = *(int *)param_1;
  local_1c = *(i32 *)(param_1 + 4);
  local_18 = *(int *)(param_1 + 8);
  local_14 = *(i32 *)(param_1 + 0xc);
  *(i32 *)(&parley_pane_own_cities + param_2 * 4) = param_3;
  parley_build_city_list(this,param_2,0);
  if (*(int *)(this[3].pad_48 + param_2 * 4 + 0x4c) < 1) {
    puVar1 = this[0xea].pad_48 + param_2 * 4 + 0x30;
    puVar1[0] = 0xff;
    puVar1[1] = 0xff;
    puVar1[2] = 0xff;
    puVar1[3] = 0xff;
  }
  else {
    puVar1 = this[0xea].pad_48 + param_2 * 4 + 0x30;
    puVar1[0] = '\0';
    puVar1[1] = '\0';
    puVar1[2] = '\0';
    puVar1[3] = '\0';
  }
  puVar1 = this[3].pad_48 + param_2 * 4 + 0x44;
  puVar1[0] = 4;
  puVar1[1] = '\0';
  puVar1[2] = '\0';
  puVar1[3] = '\0';
  *(i32 *)(this[3].pad_48 + param_2 * 0x10 + 0x24) = *(i32 *)param_1;
  *(i32 *)(this[3].pad_48 + param_2 * 0x10 + 0x28) = *(i32 *)(param_1 + 4);
  *(i32 *)(this[3].pad_48 + param_2 * 0x10 + 0x2c) = *(i32 *)(param_1 + 8);
  *(i32 *)(this[3].pad_48 + param_2 * 0x10 + 0x30) = *(i32 *)(param_1 + 0xc);
  if (*(int *)(this[0xea].pad_48 + param_2 * 4 + 0x40) <
      *(int *)(this[3].pad_48 + param_2 * 4 + 0x4c)) {
    iVar3 = GetSystemMetrics(2);
    iVar2 = local_18;
    *(int *)(this[3].pad_48 + param_2 * 0x10 + 0x2c) =
         *(int *)(this[3].pad_48 + param_2 * 0x10 + 0x2c) - iVar3;
    local_20 = GetSystemMetrics(2);
    local_20 = iVar2 - local_20;
    pCVar4 = operator_new(0x40);
    local_8 = 0;
    if (pCVar4 == (Control *)0x0) {
      local_28 = 0;
    }
    else {
      local_28 = scrollbar_ctor(pCVar4);
    }
    local_8 = 0xffffffff;
    *(i32 *)(this[3].pad_48 + param_2 * 4 - 0x20) = local_28;
    if (this == (ListPaneWindow *)0x0) {
      local_34 = (u8 *)0x0;
    }
    else {
      local_34 = this->pad_48;
    }
    scrollbar_create
              (*(Control **)(this[3].pad_48 + param_2 * 4 - 0x20),(iptr)local_34,
               param_2 + 0x420,(iptr)&local_20,1);
    scrollbar_set_range
              (*(Control **)(this[3].pad_48 + param_2 * 4 - 0x20),0,
               *(int *)(this[3].pad_48 + param_2 * 4 + 0x4c) -
               *(int *)(this[0xea].pad_48 + param_2 * 4 + 0x40));
    scrollbar_set_pos(*(ClickControl **)(this[3].pad_48 + param_2 * 4 - 0x20),0);
    scrollbar_set_page_size
              (*(Control **)(this[3].pad_48 + param_2 * 4 - 0x20),
               *(i32 *)(this[0xea].pad_48 + param_2 * 4 + 0x40));
    scrollbar_set_callback
              (*(Control **)(this[3].pad_48 + param_2 * 4 - 0x20),
               (iptr)(((void *)ADDR(0x0040166d, parley_city_list_scroll_local)) + ((param_2 == 0) - 1 & 0xfb9)));
    scrollbar_set_track_callback
              (*(ScrollbarTrackSetView **)(this[3].pad_48 + param_2 * 4 - 0x20),
               (iptr)(((void *)ADDR(0x0040166d, parley_city_list_scroll_local)) + ((param_2 == 0) - 1 & 0xfb9)));
  }
  pCVar4 = operator_new(0x40);
  local_8 = 1;
  if (pCVar4 == (Control *)0x0) {
    local_30 = 0;
  }
  else {
    local_30 = hotspot_ctor(pCVar4);
  }
  local_8 = 0xffffffff;
  *(i32 *)(this[3].pad_48 + param_2 * 4 - 0x18) = local_30;
  if (this == (ListPaneWindow *)0x0) {
    local_38 = (u8 *)0x0;
  }
  else {
    local_38 = this->pad_48;
  }
  hotspot_create
            (*(ClickControl **)(this[3].pad_48 + param_2 * 4 - 0x18),(iptr)local_38,
             param_2 + 0x422,(iptr)(this[3].pad_48 + param_2 * 0x10 + 0x24));
  hotspot_set_click_callback(*(HotspotClickSetView **)(this[3].pad_48 + param_2 * 4 - 0x18),ADDR(0x402234, parley_city_list_click));
  hotspot_set_dblclick_callback(*(HotspotDblClickSetView **)(this[3].pad_48 + param_2 * 4 - 0x18),ADDR(0x402234, parley_city_list_click));
  parley_draw_city_list(param_2);
  return;
}
#undef local_38
#undef local_34
#undef local_30
#undef local_28
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef puStack_c
#undef local_8

/* 00587e05 auto */
void __cdecl parley_city_list_scroll_local(i32 param_1)

{
  parley_city_list_scroll(0,param_1);
  return;
}

/* 00587e41 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl parley_reveal_city_info(void)

{
  iptr iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar1 - 0x48;
  }
  wnd_activate((Wnd *)(local_8 + 0x48));
  ctrl_show_and_redraw(*(Control **)(local_8 + 0x3a4));
  control_hide(*(Control **)(local_8 + 0x39c));
  *(i8 *)(local_8 + 0x3be) = 1;
  net_send_message(0xa5,*(i32 *)
                           (&net_player_slots +
                           *(int *)(&net_civ_slots + *(int *)(local_8 + 0x118) * 4) * 0x54),
                     human_civ,(int)*(char *)(local_8 + 0x3be),0,0,0,0,0,0);
  parley_draw_city_list(0);
  return;
}
#undef human_civ
#undef local_8

/* 00587f00 auto */
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl parley_hide_city_info(void)

{
  iptr iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar1 - 0x48;
  }
  wnd_activate((Wnd *)(local_8 + 0x48));
  ctrl_show_and_redraw(*(Control **)(local_8 + 0x39c));
  control_hide(*(Control **)(local_8 + 0x3a4));
  *(i8 *)(local_8 + 0x3be) = 0;
  net_send_message(0xa6,*(i32 *)
                           (&net_player_slots +
                           *(int *)(&net_civ_slots + *(int *)(local_8 + 0x118) * 4) * 0x54),
                     human_civ,(int)*(char *)(local_8 + 0x3be),0,0,0,0,0,0);
  parley_draw_city_list(0);
  return;
}
#undef human_civ
#undef local_8

/* 0058804f auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
void __cdecl parley_city_list_scroll(int param_1,i32 param_2)

{
  int iVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar1 - 0x48;
  }
  wnd_activate((Wnd *)(local_8 + 0x48));
  *(i32 *)(local_8 + 0x10410 + param_1 * 4) = param_2;
  parley_draw_city_list(param_1);
  return;
}
#undef local_8

/* 005880b0 auto */
#define local_1c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_14 (*(i32 *)(frame_ + FRAME_OFF(12)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(16)))
#define local_c (*(int *)(frame_ + FRAME_OFF(20)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(24)))
void __cdecl parley_city_list_click(int param_1)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar2 = wnd_get_active_child();
  if (iVar2 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar2 - 0x48;
  }
  wnd_activate((Wnd *)(local_8 + 0x48));
  local_c = param_1 - 0x422;
  wnd_get_cursor_pos
            ((WndBase *)(local_8 + 0x48),(iptr)&local_10,(iptr)&local_14);
  if (((*(int *)(local_8 + 1000 + local_c * 4) != 0) &&
      (iVar2 = parley_city_list_hit_test(local_10,local_14,local_c), 0 < iVar2)) &&
     (iVar2 < *(int *)(local_8 + 1000 + local_c * 4))) {
    iVar3 = wnd_is_shift_down((void *)(local_8 + 0x48));
    if (iVar3 == 0) {
      iVar3 = wnd_is_ctrl_down((void *)(local_8 + 0x48));
      if (iVar3 == 0) {
        for (local_18 = 0; local_18 < *(int *)(local_8 + 1000 + local_c * 4);
            local_18 = local_18 + 1) {
          if (local_18 != iVar2) {
            *(i32 *)(local_c * 0x2004 + local_18 * 4 + 0x8400 + local_8) = 0;
          }
        }
        *(int *)(local_8 + 0x10418 + local_c * 4) = iVar2;
        puVar1 = (uint *)(local_c * 0x2004 + iVar2 * 4 + 0x8400 + local_8);
        *puVar1 = *puVar1 ^ 1;
      }
      else {
        *(int *)(local_8 + 0x10418 + local_c * 4) = iVar2;
        puVar1 = (uint *)(local_c * 0x2004 + iVar2 * 4 + 0x8400 + local_8);
        *puVar1 = *puVar1 ^ 1;
      }
    }
    else {
      for (local_18 = 0; local_18 < *(int *)(local_8 + 1000 + local_c * 4); local_18++)
      {
        *(i32 *)(local_c * 0x2004 + local_18 * 4 + 0x8400 + local_8) = 0;
      }
      if (*(int *)(local_8 + 0x10418 + local_c * 4) < iVar2) {
        local_18 = *(int *)(local_8 + 0x10418 + local_c * 4);
        local_1c = iVar2;
      }
      else {
        local_1c = *(int *)(local_8 + 0x10418 + local_c * 4);
        local_18 = iVar2;
      }
      for (; local_18 <= local_1c; local_18++) {
        if (0 < local_18) {
          *(i32 *)(local_c * 0x2004 + local_18 * 4 + 0x8400 + local_8) = 1;
        }
      }
    }
    parley_draw_city_list(local_c);
  }
  return;
}
#undef local_1c
#undef local_18
#undef local_14
#undef local_10
#undef local_c
#undef local_8

/* 0058832d auto */
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(0)))
int __cdecl parley_city_list_hit_test(int param_1,int param_2,int param_3)

{
  iptr iVar1;
  int iVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar1 - 0x48;
  }
  if (param_2 < *(int *)(param_3 * 0x10 + 0x3c4 + local_8)) {
    iVar2 = -1;
  }
  else if (param_2 < *(int *)(param_3 * 0x10 + 0x3cc + local_8)) {
    if (param_1 < *(int *)(param_3 * 0x10 + 0x3c0 + local_8)) {
      iVar2 = -3;
    }
    else if (param_1 < *(int *)(param_3 * 0x10 + 0x3c8 + local_8)) {
      iVar2 = *(int *)(param_3 * 0x10 + 0x3c4 + local_8);
      iVar3 = rect_height(param_3 * 0x10 + local_8 + 0x3c0);
      iVar2 = (param_2 - iVar2) / (iVar3 / *(int *)(local_8 + 0x10420 + param_3 * 4)) +
              *(int *)(local_8 + 0x10410 + param_3 * 4);
    }
    else {
      iVar2 = -4;
    }
  }
  else {
    iVar2 = -2;
  }
  return iVar2;
}
#undef local_8

/* 0058843f auto */
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(16)))
void __thiscall parley_sort_city_list(void *this,int param_1,int param_2,int param_3)

{
  i32 uVar1;
  iptr iVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar2 = wnd_get_active_child();
  if (iVar2 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar2 - 0x48;
  }
  if (1 < *(int *)(local_8 + 1000 + param_3 * 4)) {
    for (local_10 = param_1; local_14 = local_10, local_10 < param_2; local_10++) {
      while (local_14 = local_14 + 1, local_14 <= param_2) {
        iVar3 = city_has_improvement(*(iptr *)(local_14 * 4 + param_3 * 0x2004 + 0x3f0 + local_8),1);
        if ((iVar3 != 0) ||
           ((iVar3 = city_has_improvement(*(iptr *)(local_10 * 4 + param_3 * 0x2004 + 0x3f0 + local_8)
                                        ,1), iVar3 == 0 &&
            (iVar3 = _strcmp(cities[*(int *)(local_10 * 4 + param_3 * 0x2004 + 0x3f0 + local_8)].
                             name,cities[*(int *)(local_14 * 4 + param_3 * 0x2004 + 0x3f0 + local_8)
                                        ].name), 0 < iVar3)))) {
          uVar1 = *(i32 *)(local_10 * 4 + param_3 * 0x2004 + 0x3f0 + local_8);
          *(i32 *)(local_10 * 4 + param_3 * 0x2004 + 0x3f0 + local_8) =
               *(i32 *)(local_14 * 4 + param_3 * 0x2004 + 0x3f0 + local_8);
          *(i32 *)(local_14 * 4 + param_3 * 0x2004 + 0x3f0 + local_8) = uVar1;
          uVar1 = *(i32 *)(local_10 * 4 + param_3 * 0x2004 + 0x8400 + local_8);
          *(i32 *)(local_10 * 4 + param_3 * 0x2004 + 0x8400 + local_8) =
               *(i32 *)(local_14 * 4 + param_3 * 0x2004 + 0x8400 + local_8);
          *(i32 *)(local_14 * 4 + param_3 * 0x2004 + 0x8400 + local_8) = uVar1;
          uVar1 = *(i32 *)(local_10 * 4 + param_3 * 0x2004 + 0xc408 + local_8);
          *(i32 *)(local_10 * 4 + param_3 * 0x2004 + 0xc408 + local_8) =
               *(i32 *)(local_14 * 4 + param_3 * 0x2004 + 0xc408 + local_8);
          *(i32 *)(local_14 * 4 + param_3 * 0x2004 + 0xc408 + local_8) = uVar1;
          uVar1 = *(i32 *)(local_10 * 4 + param_3 * 0x2004 + 0x43f8 + local_8);
          *(i32 *)(local_10 * 4 + param_3 * 0x2004 + 0x43f8 + local_8) =
               *(i32 *)(local_14 * 4 + param_3 * 0x2004 + 0x43f8 + local_8);
          *(i32 *)(local_14 * 4 + param_3 * 0x2004 + 0x43f8 + local_8) = uVar1;
        }
      }
    }
  }
  return;
}
#undef local_14
#undef local_10
#undef local_8

/* 0058878e auto */
#define dlg_highlight_text_color (*(byte *)((u8 *)&g.d_00635a00))
#define dlg_sel_text_color (*(uint *)((u8 *)&g.d_00635a28))
#define dlg_sel_text_shadow_color (*(uint *)((u8 *)&g.d_00635a2c))
#define list_bg_color (*(i32 *)((u8 *)&g.d_00635a18))
#define list_sel_bg_color (*(i32 *)((u8 *)&g.d_00635a24))
#define list_shadow_color (*(uint *)((u8 *)&g.d_00635a20))
#define list_text_color (*(uint *)((u8 *)&g.d_00635a1c))
#define panel_margin_x (*(int *)((u8 *)&g.d_0062d858))
#define local_64 (*(i32 *)(frame_ + FRAME_OFF(4)))
#define city (*(int *)(frame_ + FRAME_OFF(16)))
#define local_54 (*(int *)(frame_ + FRAME_OFF(20)))
#define local_44 (*(uint *)(frame_ + FRAME_OFF(36)))
#define local_3c (*(uint *)(frame_ + FRAME_OFF(44)))
#define this2 (*(ViewWindow * *)(frame_ + FRAME_OFF(48)))
#define local_30 (*(tagRECT *)(frame_ + FRAME_OFF(56)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(72)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(76)))
#define local_18 (*(i8 (*)[16])(frame_ + FRAME_OFF(80)))
#define local_8 (*(GameFont * *)(frame_ + FRAME_OFF(96)))
void __cdecl parley_draw_city_list(int param_1)

{
  u8 *puVar1;
  int xLeft;
  iptr iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  i32 uVar7;
  int iVar8;
  iptr iVar9;
  i8 frame_[FRAME_OFF(104)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar2 = wnd_get_active_child();
  if (iVar2 == 0) {
    this2 = (ViewWindow *)0x0;
  }
  else {
    this2 = (ViewWindow *)(iVar2 - 0x48);
  }
  surface_get_clip((DibSurface *)this2,(iptr)local_18);
  surface_set_clip((DibSurface *)this2,(iptr)(this2->pad_3c0 + param_1 * 0x10));
LAB_005887e1:
  surface_fill_rect
            ((DibSurface *)this2,(iptr)(this2->pad_3c0 + param_1 * 0x10),list_bg_color);
  if (this2->field_154 == 0) {
    local_8 = (GameFont *)&font_size14;
  }
  else {
    local_8 = (GameFont *)&font_size21;
  }
  xLeft = *(int *)(this2->pad_3c0 + param_1 * 0x10);
  iVar3 = rect_width((iptr)(this2->pad_3c0 + param_1 * 0x10));
  local_20 = rect_height((iptr)(this2->pad_3c0 + param_1 * 0x10));
  local_20 = local_20 / *(int *)(this2[0x3e].pad_48 + param_1 * 4 + 0x38);
  iVar4 = local_20 / 2;
  iVar5 = font_cached_height(local_8);
  iVar4 -= iVar5 / 2;
  puVar1 = this2->pad_200 + param_1 * 4 - 0x1c;
  puVar1[0] = '\0';
  puVar1[1] = '\0';
  puVar1[2] = '\0';
  puVar1[3] = '\0';
  for (local_54 = 0; local_54 < *(int *)(this2->pad_3c0 + param_1 * 4 + 0x28);
      local_54 = local_54 + 1) {
    if (*(int *)(param_1 * 0x2004 + local_54 * 4 + 0x8400 + (int)this2) != 0) {
      puVar1 = this2->pad_200 + param_1 * 4 - 0x1c;
      puVar1[0] = 1;
      puVar1[1] = '\0';
      puVar1[2] = '\0';
      puVar1[3] = '\0';
      break;
    }
  }
  local_54 = 0;
  do {
    if (*(int *)(this2[0x3e].pad_48 + param_1 * 4 + 0x38) <= local_54) {
LAB_00588e17:
      surface_set_clip((DibSurface *)this2,(iptr)local_18);
      parley_update_buttons(this2);
      ctrl_show_and_redraw(*(Control **)(this2->pad_364 + param_1 * 4 + 0x20))
      ;
      return;
    }
    iVar5 = *(int *)(this2->pad_3c0 + param_1 * 0x10 + 4) + local_54 * local_20;
    SetRect(&local_30,xLeft,iVar5,iVar3 + xLeft,iVar5 + local_20);
    if ((local_54 != 0) && (*(int *)(this2[0x3e].pad_48 + param_1 * 4 + 0x28) == -1))
    goto LAB_00588e17;
    if (*(int *)(this2[0x3e].pad_48 + param_1 * 4 + 0x28) + local_54 <
        *(int *)(this2->pad_3c0 + param_1 * 4 + 0x28)) {
      iVar8 = *(int *)(param_1 * 0x2004 +
                       (*(int *)(this2[0x3e].pad_48 + param_1 * 4 + 0x28) + local_54) * 4 +
                       0x8400 + (int)this2);
      if (iVar8 == 0) {
        if (*(int *)(this2[0x3e].pad_48 + param_1 * 4 + 0x28) + local_54 == 0) {
          local_3c = (uint)dlg_highlight_text_color;
          local_44 = dlg_sel_text_shadow_color;
        }
        else {
          local_3c = list_text_color;
          local_44 = list_shadow_color;
        }
      }
      else {
        local_3c = dlg_sel_text_color;
        local_44 = dlg_sel_text_shadow_color;
      }
      city = 0;
      if ((0 < *(int *)(this2->pad_3c0 + param_1 * 4 + 0x28)) &&
         (city = parley_find_city_by_id
                               ((WindowObjectView *)this2,
                                *(i32 *)
                                 (param_1 * 0x2004 +
                                  (*(int *)(this2[0x3e].pad_48 + param_1 * 4 + 0x28) + local_54)
                                  * 4 + 0x43f8 + (int)this2)), city == -1)) break;
      iVar6 = (-(uint)(this2->field_154 == 0) & 0xffffffe2) + 0x5a + panel_margin_x;
      local_30.left = local_30.left + iVar6 - 3;
      if (iVar8 == 0) {
        local_64 = list_bg_color;
      }
      else {
        local_64 = list_sel_bg_color;
      }
      surface_fill_rect((DibSurface *)this2,(iptr)&local_30,local_64);
      if (param_1 == 0) {
        if (this2->field_3be == '\0') {
          local_1c = 3;
        }
        else {
          local_1c = 0;
        }
      }
      else if (this2->field_3bf == '\0') {
        local_1c = 3;
      }
      else {
        local_1c = 0;
      }
      if (parley_mode == 10) {
        local_1c = 0;
      }
      if (*(int *)(this2[0x3e].pad_48 + param_1 * 4 + 0x28) == -1) {
        text_clear();
        iVar9 = label_string(*(i32 *)(label_string_ids + 0xb78));
        text_append(iVar9);
        puVar1 = this2->pad_200 + param_1 * 4 - 0x1c;
        puVar1[0] = '\0';
        puVar1[1] = '\0';
        puVar1[2] = '\0';
        puVar1[3] = '\0';
      }
      else {
        iVar8 = local_1c;
        uVar7 = font_cached_height(local_8);
        parley_draw_city_sprite(city,*(int *)(this2[0x3e].pad_48 + param_1 * 4 + 0x28) + local_54,
                           xLeft + 2,iVar5,uVar7,iVar8);
        text_clear();
        text_append(city * 0x58 + ADDR(0x64f360, ((u8 *)&cities + 32)));
        text_append_space();
        iVar8 = city_has_improvement(city,1);
        if ((iVar8 == 0) && (local_1c == 0)) {
          text_append_lparen();
          text_append_int(*(iptr *)(param_1 * 0x2004 +
                                       (*(int *)(this2[0x3e].pad_48 + param_1 * 4 + 0x28) +
                                       local_54) * 4 + 0xc408 + (int)this2));
          text_append_space();
          if (*(int *)(param_1 * 0x2004 +
                       (*(int *)(this2[0x3e].pad_48 + param_1 * 4 + 0x28) + local_54) * 4 +
                       0xc408 + (int)this2) < 2) {
            iVar9 = label_string(*(i32 *)(label_string_ids + 0xb70));
            text_append(iVar9);
          }
          else {
            iVar9 = label_string(*(i32 *)(label_string_ids + 0xb6c));
            text_append(iVar9);
          }
        }
        else {
          iVar8 = city_has_improvement(city,1);
          if (iVar8 != 0) {
            iVar9 = label_string(*(i32 *)(label_string_ids + 0xb74));
            text_append(iVar9);
          }
        }
      }
      if (local_44 != local_3c) {
        gfx_set_text_color_index(local_44);
        surface_draw_text
                  ((DibSurface *)this2,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),xLeft + iVar6 + 2,
                   iVar5 + iVar4 + 1,5);
        gfx_set_text_color_index(local_3c);
        surface_draw_text
                  ((DibSurface *)this2,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),xLeft + iVar6 + 1,iVar5 + iVar4,
                   5);
      }
      gfx_set_text_color_index(local_3c);
      surface_draw_text
                ((DibSurface *)this2,(iptr)local_8,ADDR(0x679640, ((u8 *)&g.d_00679640)),xLeft + iVar6,iVar5 + iVar4,5);
    }
    local_54++;
  } while( true );
  parley_build_city_list((ListPaneWindow *)this2,param_1,1);
  if (*(int *)(this2->pad_3c0 + param_1 * 4 + 0x28) == 0) {
    puVar1 = this2[0x3e].pad_48 + param_1 * 4 + 0x28;
    puVar1[0] = 0xff;
    puVar1[1] = 0xff;
    puVar1[2] = 0xff;
    puVar1[3] = 0xff;
  }
  else if (*(int *)(this2->pad_3c0 + param_1 * 4 + 0x28) <
           *(int *)(this2->pad_3c0 + param_1 * 4 + 0x28)) {
    *(int *)(this2[0x3e].pad_48 + param_1 * 4 + 0x28) =
         *(int *)(this2->pad_3c0 + param_1 * 4 + 0x28) - 1;
  }
  goto LAB_005887e1;
}
#undef dlg_highlight_text_color
#undef dlg_sel_text_color
#undef dlg_sel_text_shadow_color
#undef list_bg_color
#undef list_sel_bg_color
#undef list_shadow_color
#undef list_text_color
#undef panel_margin_x
#undef local_64
#undef city
#undef local_54
#undef local_44
#undef local_3c
#undef this2
#undef local_30
#undef local_20
#undef local_1c
#undef local_18
#undef local_8

/* 00588e47 auto */
#define local_20 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define local_18 (*(i32 *)(frame_ + FRAME_OFF(8)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(16)))
#define local_c (*(iptr *)(frame_ + FRAME_OFF(20)))
void __cdecl
parley_draw_city_sprite(iptr city,uint param_2,int param_3,int param_4,int param_5,i32 param_6)

{
  iptr iVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  
  iVar1 = wnd_get_active_child();
  if (iVar1 == 0) {
    local_c = 0;
  }
  else {
    local_c = iVar1 - 0x48;
  }
  if (*(int *)(local_c + 0x154) == 0) {
    local_20 = 0xfffffffc;
  }
  else {
    local_20 = 0xfffffffe;
  }
  local_18 = param_3;
  if (*(int *)(local_c + 0x154) == 0) {
    local_10 = 0x18;
  }
  else {
    local_10 = 0x24;
  }
  if ((param_2 & 1) != 0) {
    local_18 = param_3 + local_10 + 2;
  }
  iVar2 = gfx_zoom_scale(0x30,local_20);
  gfx_draw_city(ADDR(0x67a7a8, ((u8 *)&g.d_0067a7a8)),city,param_6,local_18,param_4 - (iVar2 - param_5) / 2,local_20);
  return;
}
#undef local_20
#undef local_18
#undef local_10
#undef local_c

/* 00588f36 auto */
#define human_civ (*(i8 *)((u8 *)&g.d_006d1da0))
#define city (*(iptr *)(frame_ + FRAME_OFF(0)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_c (*(void * *)(frame_ + FRAME_OFF(12)))
#define local_8 (*(iptr *)(frame_ + FRAME_OFF(16)))
void __thiscall parley_build_city_list(ListPaneWindow *this,int param_1,int param_2)

{
  int *piVar1;
  iptr iVar2;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_c = (void *)0x0;
  iVar2 = wnd_get_active_child();
  if (iVar2 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = iVar2 - 0x48;
  }
  if (param_2 != 0) {
    local_c = operator_new(*(int *)(local_8 + 1000 + param_1 * 4) << 2);
    if (local_c == (void *)0x0) {
      param_2 = 0;
    }
    else {
      local_14 = *(int *)(local_8 + 1000 + param_1 * 4);
      for (city = 0; city < local_14; city++) {
        if (*(int *)(param_1 * 0x2004 + city * 4 + 0x8400 + local_8) == 0) {
          *(i32 *)((int)local_c + city * 4) = 0xffffffff;
        }
        else {
          *(i32 *)((int)local_c + city * 4) =
               *(i32 *)(param_1 * 0x2004 + city * 4 + 0x43f8 + local_8);
        }
      }
    }
  }
  *(i32 *)(local_8 + 1000 + param_1 * 4) = 0;
  city = 0;
  do {
    if (game.num_cities <= city) {
      if (param_2 != 0) {
        operator_delete(local_c);
      }
      parley_sort_city_list(this,0,*(int *)(local_8 + 1000 + param_1 * 4) - 1,param_1);
      return;
    }
    if ((cities[city].id != 0) &&
       (((*(int *)(&parley_pane_own_cities + param_1 * 4) != 0 && (cities[city].owner == human_civ))
        || (((*(int *)(&parley_pane_own_cities + param_1 * 4) == 0 &&
             ((int)cities[city].owner == this->caption_height)) &&
            (((1 << ((byte)human_civ & 0x1f) & (int)(char)cities[city].known_to) != 0 ||
             ((int)cities[city].owner == (human_civ & 0xffU))))))))) {
      *(iptr *)(param_1 * 0x2004 + *(int *)(local_8 + 1000 + param_1 * 4) * 4 + 0x3f0 + local_8) =
           city;
      *(i32 *)(param_1 * 0x2004 + *(int *)(local_8 + 1000 + param_1 * 4) * 4 + 0x43f8 + local_8) =
           cities[city].id;
      if (param_2 == 0) {
        *(i32 *)
         (param_1 * 0x2004 + *(int *)(local_8 + 1000 + param_1 * 4) * 4 + 0x8400 + local_8) = 0;
      }
      else {
        *(i32 *)
         (param_1 * 0x2004 + *(int *)(local_8 + 1000 + param_1 * 4) * 4 + 0x8400 + local_8) = 0;
        for (unit = 0; unit < local_14; unit++) {
          if (cities[city].id == *(int *)((int)local_c + unit * 4)) {
            *(i32 *)
             (param_1 * 0x2004 + *(int *)(local_8 + 1000 + param_1 * 4) * 4 + 0x8400 + local_8) = 1;
            break;
          }
        }
      }
      *(i32 *)
       (param_1 * 0x2004 + *(int *)(local_8 + 1000 + param_1 * 4) * 4 + 0xc408 + local_8) = 0;
      for (unit = 0; unit < game.num_units; unit++) {
        if (((units[unit].id != 0) && (cities[city].x == units[unit].x)) &&
           (cities[city].y == units[unit].y)) {
          piVar1 = (int *)(param_1 * 0x2004 + *(int *)(local_8 + 1000 + param_1 * 4) * 4 + 0xc408 +
                          local_8);
          *piVar1 = *piVar1 + 1;
        }
      }
      piVar1 = (int *)(local_8 + 1000 + param_1 * 4);
      *piVar1 = *piVar1 + 1;
    }
    city++;
  } while( true );
}
#undef human_civ
#undef city
#undef local_14
#undef unit
#undef local_c
#undef local_8

/* 00594d42 auto */
#define game_loop_active (*(i8 *)((u8 *)&g.d_00628044))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define net_lock_map_busy (*(i32 *)((u8 *)&g.d_006ad8cc))
#define net_slot_active_flags (*(i8 *)((u8 *)&g.d_006ad359))
#define local_14 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_c (*(int *)(frame_ + FRAME_OFF(12)))
i32 __cdecl
net_lock_map(iptr param_1,iptr param_2,iptr param_3,iptr param_4,int param_5,int param_6)

{
  i32 uVar1;
  int iVar2;
  int iVar3;
  i8 frame_[FRAME_OFF(24)] __attribute__((aligned(8)));  /* original stack frame */
  
  net_lock_map_busy = 1;
  *(i32 *)(&net_map_lock_replies + param_1 * 0x18) = 0;
  *(i32 *)(&net_map_lock_slots + param_1 * 0x18) = *(i32 *)(&net_map_lock_replies + param_1 * 0x18);
  if (net_host_flag == '\0') {
    net_lock_map_busy = 0;
    net_send_message(0x51,0,param_1,param_2,param_3,param_4,param_5,0,0,0);
    XD_FlushSendBuffer(60000);
    if (param_6 == 0) {
      uVar1 = 1;
    }
    else {
      iVar2 = timer_ticks();
      while( true ) {
        iVar3 = timer_ticks();
        if ((0xe0f < iVar3 - iVar2) || (*(int *)(&net_map_lock_replies + param_1 * 0x18) != 0)) break;
        net_process_messages((NetSession *)&net_session,1,1);
      }
      if (*(int *)(&net_map_lock_replies + param_1 * 0x18) == 0) {
        dbg_log(ADDR(0x634e6c, ((u8 *)&g.d_00634e6c)));
        popup_game_with_sprite(ADDR(0x634e98, ((u8 *)&g.d_00634e98)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        game_loop_active = 0;
        uVar1 = 0;
      }
      else if (*(int *)(&net_map_lock_replies + param_1 * 0x18) == 1) {
        uVar1 = 1;
      }
      else {
        uVar1 = 0;
      }
    }
  }
  else {
    local_10 = -1;
    local_14 = -1;
    for (local_c = 1; local_c < 8; local_c++) {
      if (((*(int *)(&net_map_lock_src_x + local_c * 0x18) == param_2) &&
          (*(int *)(&net_map_lock_src_y + local_c * 0x18) == param_3)) ||
         ((*(int *)(&net_map_lock_dst_x + local_c * 0x18) == param_2 &&
          (*(int *)(&net_map_lock_dst_y + local_c * 0x18) == param_3)))) {
        local_14 = 0;
        break;
      }
      if (((*(int *)(&net_map_lock_src_x + local_c * 0x18) == param_4) &&
          (*(int *)(&net_map_lock_src_y + local_c * 0x18) == param_5)) ||
         ((*(int *)(&net_map_lock_dst_x + local_c * 0x18) == param_4 &&
          (*(int *)(&net_map_lock_dst_y + local_c * 0x18) == param_5)))) {
        local_10 = 0;
        break;
      }
    }
    if ((local_14 == -1) && (local_10 == -1)) {
      *(iptr *)(&net_map_lock_src_x + param_1 * 0x18) = param_2;
      *(iptr *)(&net_map_lock_src_y + param_1 * 0x18) = param_3;
      *(iptr *)(&net_map_lock_dst_x + param_1 * 0x18) = param_4;
      *(int *)(&net_map_lock_dst_y + param_1 * 0x18) = param_5;
      if ((human_civ != param_1) &&
         (((1 << ((byte)param_1 & 0x1f) & (uint)game.human_players) != 0 &&
          ((&net_slot_active_flags)[*(int *)(&net_civ_slots + param_1 * 4) * 0x54] != '\0')))) {
        net_send_message(0x53,*(i32 *)
                                 (&net_player_slots + *(int *)(&net_civ_slots + param_1 * 4) * 0x54),
                           param_1,1,0,0,0,0,0,0);
        XD_FlushSendBuffer(60000);
      }
      net_lock_map_busy = 0;
      uVar1 = 1;
    }
    else {
      if (((human_civ != param_1) &&
          ((1 << ((byte)param_1 & 0x1f) & (uint)game.human_players) != 0)) &&
         ((&net_slot_active_flags)[*(int *)(&net_civ_slots + param_1 * 4) * 0x54] != '\0')) {
        net_send_message(0x53,*(i32 *)
                                 (&net_player_slots + *(int *)(&net_civ_slots + param_1 * 4) * 0x54),
                           param_1,-1,0,0,0,0,0,0);
        XD_FlushSendBuffer(60000);
      }
      net_lock_map_busy = 0;
      uVar1 = 0;
    }
  }
  return uVar1;
}
#undef game_loop_active
#undef human_civ
#undef net_host_flag
#undef net_lock_map_busy
#undef net_slot_active_flags
#undef local_14
#undef local_10
#undef local_c

/* 0059511c auto */
#define game_loop_active (*(i8 *)((u8 *)&g.d_00628044))
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define net_unlock_map_busy (*(i32 *)((u8 *)&g.d_006ad8d0))
void __cdecl net_unlock_map(iptr param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  net_unlock_map_busy = 1;
  if (net_host_flag == '\0') {
    net_unlock_map_busy = 0;
    *(i32 *)(&net_map_lock_slots + param_1 * 0x18) = 0;
    net_send_message(0x52,0,param_1,0,0,0,0,0,0,0);
    if (param_2 != 0) {
      iVar1 = timer_ticks();
      while( true ) {
        iVar2 = timer_ticks();
        if ((0xe0f < iVar2 - iVar1) || (*(int *)(&net_map_lock_slots + param_1 * 0x18) != 0)) break;
        net_process_messages((NetSession *)&net_session,1,1);
      }
      if (*(int *)(&net_map_lock_slots + param_1 * 0x18) == 0) {
        dbg_log(ADDR(0x634eac, ((u8 *)&g.d_00634eac)));
        popup_game_with_sprite(ADDR(0x634ed8, ((u8 *)&g.d_00634ed8)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        game_loop_active = 0;
      }
    }
  }
  else {
    _memset(&net_map_lock_slots + param_1 * 0x18,-1,0x18);
    net_send_message(0x55,0xff,param_1,0,0,0,0,0,0,0);
    XD_FlushSendBuffer(60000);
    net_unlock_map_busy = 0;
  }
  return;
}
#undef game_loop_active
#undef net_host_flag
#undef net_unlock_map_busy

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
  net_session_ctor((NetSessionCtorView *)&net_session);
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
  net_session_dtor(&net_session);
  return;
}

/* 0059a8bb auto */
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
NetSessionCtorView * __thiscall net_session_ctor(NetSessionCtorView *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  net_msg_player_info_init((NetMsgHeader *)&this->field_8);
  net_msgq_ctor((NetMsgQueue *)(this[0x2733].pad_0 + 5));
  local_8 = 0;
  this[0x94].pad_0[0] = '\0';
  this[0x94].pad_0[1] = '\0';
  this[0x94].pad_0[2] = '\0';
  this[0x94].pad_0[3] = '\0';
  XD_SetBroadcastReceive((code *)((void *)ADDR(0x00403c29, net_on_broadcast_receive)));
  XD_SetSecureReceive(net_on_secure_receive);
  XD_SetOnClientConnectionToServer(net_on_connected_to_server);
  XD_SetNewClientConnection(net_on_new_client);
  XD_SetOnConnectionLost(net_on_connection_lost);
  XD_SetOversizedMessageCB(50000,net_on_oversized_message);
  return this;
}
#undef local_10
#undef puStack_c
#undef local_8

/* 0059a998 auto */
#define mp_meeting_pending (*(i32 *)((u8 *)&g.d_00626a2c))
#define net_active_protocol (*(i32 *)((u8 *)&g.d_006c9288))
#define net_xd_adapter_index (*(i32 *)((u8 *)&g.d_006c8fbc))
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall net_session_clear(void *this)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  *(i8 *)((int)this + 0x1ec) = 0;
  *(i8 *)((int)this + 0x1ed) = 0;
  *(i32 *)((int)this + 0x574) = 0;
  *(i8 *)((int)this + 0x1ee) = 0;
  *(i32 *)((int)this + 0x538) = 0;
  *(i32 *)((int)this + 0x160cc) = 0;
  *(i32 *)this = 0;
  *(i32 *)((int)this + 4) = 0;
  *(i32 *)((int)this + 0x570) = 0;
  *(i32 *)((int)this + 0x1f8) = 0xffffffff;
  net_xd_adapter_index = 0;
  *(i32 *)((int)this + 500) = 0;
  net_active_protocol = 0xffffffff;
  *(i32 *)((int)this + 0x1f0) = 0xffffffff;
  *(i32 *)((int)this + 0x470) = 0;
  *(i8 *)((int)this + 0x57d) = 0;
  *(i32 *)((int)this + 0x580) = 0;
  *(i32 *)((int)this + 0x584) = 0;
  *(i32 *)((int)this + 0x588) = 0;
  *(i32 *)((int)this + 0x58c) = 0;
  *(i8 *)((int)this + 0x590) = 0;
  *(i8 *)((int)this + 0x57c) = 0;
  *(i8 *)((int)this + 0x591) = 0;
  *(i8 *)((int)this + 0x592) = 0;
  *(i32 *)((int)this + 0x594) = 8;
  *(i32 *)((int)this + 0x598) = 0;
  *(i32 *)((int)this + 0x7b0) = 0x3c;
  *(i32 *)((int)this + 0x59c) = 0xffffffff;
  *(i32 *)((int)this + 0x5a0) = 0xffffffff;
  *(i32 *)((int)this + 0x7b4) = 0;
  *(i32 *)((int)this + 0x7b8) = 0;
  *(i32 *)((int)this + 0x7bc) = 0;
  *(i32 *)((int)this + 0x7c0) = 0;
  *(i32 *)((int)this + 0x7c4) = 0;
  *(i32 *)((int)this + 0x7c8) = 0;
  *(i32 *)((int)this + 0x7cc) = 0;
  *(i32 *)((int)this + 2000) = 0;
  *(i32 *)((int)this + 0x7d4) = 0;
  *(i32 *)((int)this + 0x7d8) = 0;
  *(i32 *)((int)this + 0x7dc) = 0;
  *(i32 *)((int)this + 0x7e0) = 0;
  *(i32 *)((int)this + 0x7e4) = 0;
  *(i32 *)((int)this + 0x7e8) = 0;
  *(i32 *)((int)this + 0x7ec) = 0;
  *(i32 *)((int)this + 0x800) = 0;
  *(i32 *)((int)this + 0x804) = 0;
  *(i32 *)((int)this + 0x808) = 0;
  *(i32 *)((int)this + 0x80c) = 0;
  *(i32 *)((int)this + 0x810) = 0;
  *(i32 *)((int)this + 0x814) = 0;
  for (local_8 = 0; local_8 < 8; local_8++) {
    *(i32 *)((int)this + local_8 * 4 + 0x2118) = 0;
    *(i32 *)((int)this + local_8 * 4 + 0x2138) = 0;
    *(i32 *)((int)this + local_8 * 4 + 0x2158) = 0;
    *(i32 *)((int)this + local_8 * 4 + 0x2178) = 0;
  }
  *(i8 *)((int)this + 0x160a1) = 0;
  *(i32 *)((int)this + 0x7f0) = 0;
  *(i32 *)((int)this + 0x7f4) = 0;
  *(i32 *)((int)this + 0x7f8) = 0;
  *(i32 *)((int)this + 0x7fc) = 0;
  mp_meeting_pending = 0;
  *(i8 *)((int)this + 0x160a0) = 0;
  for (local_8 = 0; local_8 < 8; local_8++) {
    *(i32 *)((int)this + local_8 * 4 + 0x53c) = 0;
    *(i32 *)((int)this + local_8 * 4 + 0x16060) = 0;
    *(i32 *)((int)this + local_8 * 4 + 0x16080) = 0;
  }
  *(i32 *)((int)this + 0x160a4) = 0;
  *(i8 *)((int)this + 0x160c8) = 0;
  net_session_shutdown(this,1);
  net_reset_error_counts();
  return;
}
#undef mp_meeting_pending
#undef net_active_protocol
#undef net_xd_adapter_index
#undef local_8

/* 0059ad40 auto */
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(0)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
void __thiscall net_session_dtor(void *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  if (*(int *)((int)this + 0x534) != 0) {
    operator_delete(*(void **)((int)this + 0x534));
    *(i32 *)((int)this + 0x534) = 0;
  }
  net_session_shutdown(this,1);
  net_reset_error_counts();
  local_8 = 0xffffffff;
  /* inlined unwind funclet 0059adc8 */ { net_msgq_clear((NetMsgQueue *)(*(int *)((iptr)&this) + 0x160d0)); }
  return;
}
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0059adef auto */
#define net_active_protocol (*(i32 *)((u8 *)&g.d_006c9288))
#define net_protocol (*(i32 *)((u8 *)&g.d_006ad2f8))
#define prefs_net_ip_address (*(i8 *)((u8 *)&g.d_006665b0))
#define prefs_net_player_name (*(i8 *)((u8 *)&g.d_00666570))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
i8 __thiscall net_init_transport(void *this,i32 param_1,int param_2)

{
  i32 uVar1;
  i8 uVar2;
  UINT UVar3;
  int iVar4;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (*(char *)((int)this + 0x1ec) != '\0') {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x6350bc, ((u8 *)&g.d_006350bc)),ADDR(0x63509c, ((u8 *)&g.d_0063509c)),0x92);
  }
  uVar1 = net_protocol;
  net_msgq_reset((NetMsgQueue *)((int)this + 0x160d0));
  net_session_clear(this);
  _memset((void *)((int)this + 0x200),0,0x270);
  switch(param_1) {
  case 0:
    local_c = XD_InitializeSocketsTCP
                        (3,0x1381,0x1382,(int)(char)param_2,7,(code *)0x0
                        );
    game.multiplayer = 3;
    if (*(int *)((int)this + 0x1e8) == 0) {
      UVar3 = GetPrivateProfileIntA
                        (s_Civilization_Gold_006350ec,s_INTERNET_Timeout_006350d8,-1,
                         s_CIV_INI_006350d0);
      if ((UVar3 == 0xffffffff) || ((int)UVar3 < 0x3c)) {
        WritePrivateProfileStringA
                  (s_Civilization_Gold_00635120,s_INTERNET_Timeout_0063510c,&net_internet_timeout_default,
                   s_CIV_INI_00635100);
        *(i32 *)((int)this + 0x7b0) = 0x3c;
      }
      else {
        *(UINT *)((int)this + 0x7b0) = UVar3;
      }
    }
    else {
      UVar3 = GetPrivateProfileIntA
                        (s_Civilization_Gold_0063514c,s_TCPIP_Timeout_0063513c,-1,s_CIV_INI_00635134
                        );
      if ((UVar3 == 0xffffffff) || ((int)UVar3 < 0xf)) {
        WritePrivateProfileStringA
                  (s_Civilization_Gold_0063517c,s_TCPIP_Timeout_0063516c,&net_tcpip_timeout_default,
                   s_CIV_INI_00635160);
        *(i32 *)((int)this + 0x7b0) = 0xf;
      }
      else {
        *(UINT *)((int)this + 0x7b0) = UVar3;
      }
    }
    break;
  case 1:
    local_c = XD_InitializeSocketsIPXSPX
                        (3,0x1381,0x1382,(int)(char)param_2,7,(code *)0x0
                        );
    game.multiplayer = 3;
    UVar3 = GetPrivateProfileIntA
                      (s_Civilization_Gold_006351a8,s_IPXSPX_Timeout_00635198,-1,s_CIV_INI_00635190)
    ;
    if ((UVar3 == 0xffffffff) || ((int)UVar3 < 0xf)) {
      WritePrivateProfileStringA
                (s_Civilization_Gold_006351d8,s_IPXSPX_Timeout_006351c8,&net_ipxspx_timeout_default,
                 s_CIV_INI_006351bc);
      *(i32 *)((int)this + 0x7b0) = 0xf;
    }
    else {
      *(UINT *)((int)this + 0x7b0) = UVar3;
    }
    break;
  case 2:
    game.multiplayer = 5;
    UVar3 = GetPrivateProfileIntA
                      (s_Civilization_Gold_00635204,s_MODEM_Timeout_006351f4,-1,s_CIV_INI_006351ec);
    if ((UVar3 == 0xffffffff) || ((int)UVar3 < 0x1e)) {
      WritePrivateProfileStringA
                (s_Civilization_Gold_00635234,s_MODEM_Timeout_00635224,&net_modem_timeout_default,
                 s_CIV_INI_00635218);
      *(i32 *)((int)this + 0x7b0) = 0x1e;
    }
    else {
      *(UINT *)((int)this + 0x7b0) = UVar3;
    }
    local_c = XD_InitializeModem((int)(char)param_2);
    break;
  case 3:
    game.multiplayer = 6;
    UVar3 = GetPrivateProfileIntA
                      (s_Civilization_Gold_00635260,s_DIRECT_Timeout_00635250,-1,s_CIV_INI_00635248)
    ;
    if ((UVar3 == 0xffffffff) || ((int)UVar3 < 0x1e)) {
      WritePrivateProfileStringA
                (s_Civilization_Gold_00635290,s_DIRECT_Timeout_00635280,&net_direct_timeout_default,
                 s_CIV_INI_00635274);
      *(i32 *)((int)this + 0x7b0) = 0x1e;
    }
    else {
      *(UINT *)((int)this + 0x7b0) = UVar3;
    }
    local_c = XD_InitializeSerial((int)(char)param_2);
    break;
  default:
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x6352c4, ((u8 *)&g.d_006352c4)),ADDR(0x6352a4, ((u8 *)&g.d_006352a4)),0xf4);
  }
  if (local_c == 0) {
    if (((char)param_2 == '\0') || (iVar4 = XD_ActivateServer(), iVar4 == 0)) {
      *(char *)((int)this + 0x1ef) = (char)param_2;
      *(i8 *)((int)this + 0x1ec) = 1;
      net_active_protocol = param_1;
      *(i32 *)((int)this + 0x1f0) = param_1;
      net_reset_error_counts();
      net_reset_msg_counts();
      _memset((void *)((int)this + 0x208),0,0x20);
      _strncpy((char *)((int)this + 0x208),&prefs_net_ip_address,0x20);
      _memset((void *)((int)this + 0x228),0,0x20);
      _strncpy((char *)((int)this + 0x228),&prefs_net_player_name,0x20);
      *(i32 *)((int)this + 0x200) = 1;
      *(i8 *)((int)this + 0x251) = 1;
      *(i8 *)((int)this + 0x250) = *(i8 *)((int)this + 0x1ef);
      uVar2 = 1;
    }
    else {
      dbg_logf(ADDR(0x635300, ((u8 *)&g.d_00635300)),iVar4);
      uVar2 = 0;
      net_protocol = uVar1;
    }
  }
  else {
    dbg_logf(ADDR(0x6352c8, ((u8 *)&g.d_006352c8)),local_c);
    uVar2 = 0;
    net_protocol = uVar1;
  }
  return uVar2;
}
#undef net_active_protocol
#undef net_protocol
#undef prefs_net_ip_address
#undef prefs_net_player_name
#undef local_c

/* 0059b293 auto */
/* WARNING: Removing unreachable block (ram,0x0059b3ca) */

void __thiscall net_session_shutdown(void *this,int param_1)

{
  dbg_log(ADDR(0x635338, ((u8 *)&g.d_00635338)));
  if (*(char *)((int)this + 0x1ef) != '\0') {
    param_1 = 0;
  }
  if (*(char *)((int)this + 0x1ec) == '\0') {
    XD_ResetLibrary();
    dbg_log(ADDR(0x63553c, ((u8 *)&g.d_0063553c)));
  }
  else {
    net_free_game_list(this);
    if (*(char *)((int)this + 0x1ed) != '\0') {
      XD_FlushSendBuffer(60000);
      dbg_log(ADDR(0x635354, ((u8 *)&g.d_00635354)));
      net_msgq_reset((NetMsgQueue *)((int)this + 0x160d0));
      net_popup_queue_clear();
      XD_CloseConnection();
      net_msgq_reset((NetMsgQueue *)((int)this + 0x160d0));
      net_popup_queue_clear();
      dbg_log(ADDR(0x635370, ((u8 *)&g.d_00635370)));
      net_session_close_hook_nop(this);
    }
    switch(*(i32 *)((int)this + 0x1f0)) {
    case 0:
      XD_ShutdownSockets();
      dbg_log(ADDR(0x63538c, ((u8 *)&g.d_0063538c)));
      break;
    case 1:
      XD_ShutdownSockets();
      dbg_log(ADDR(0x6353a8, ((u8 *)&g.d_006353a8)));
      break;
    case 2:
      XD_ShutdownModem();
      dbg_log(ADDR(0x6353c4, ((u8 *)&g.d_006353c4)));
      break;
    case 3:
      XD_ShutdownTEN();
      dbg_log(ADDR(0x6353dc, ((u8 *)&g.d_006353dc)));
    }
    net_msgq_reset((NetMsgQueue *)((int)this + 0x160d0));
    net_popup_queue_clear();
    if (0 < *(int *)((int)this + 0x584)) {
      dbg_logf(ADDR(0x635468, ((u8 *)&g.d_00635468)),*(iptr *)((int)this + 0x584));
    }
    if (0 < *(int *)((int)this + 0x58c)) {
      dbg_logf(ADDR(0x635494, ((u8 *)&g.d_00635494)),*(iptr *)((int)this + 0x58c));
    }
    if (0 < *(int *)((int)this + 0x588)) {
      dbg_logf(ADDR(0x6354bc, ((u8 *)&g.d_006354bc)),*(iptr *)((int)this + 0x588));
    }
    if (*(int *)((int)this + 0x814) != 0) {
      dbg_logf(ADDR(0x6354e0, ((u8 *)&g.d_006354e0)),*(iptr *)((int)this + 0x814));
    }
    XD_ResetLibrary();
    dbg_log(ADDR(0x635500, ((u8 *)&g.d_00635500)));
    if (param_1 != 0) {
      dbg_log(ADDR(0x635518, ((u8 *)&g.d_00635518)));
      ui_delay_ticks(0x78);
    }
  }
  *(i8 *)((int)this + 0x1ec) = 0;
  *(i8 *)((int)this + 0x1ed) = 0;
  *(i8 *)((int)this + 0x1ee) = 0;
  *(i32 *)((int)this + 0x1f8) = 0xffffffff;
  net_reset_error_counts();
  net_msgq_reset((NetMsgQueue *)((int)this + 0x160d0));
  net_popup_queue_clear();
  return;
}

/* 0059b55b auto */
void __thiscall net_session_close_hook_nop(void *this)

{
  return;
}

/* 0059b571 auto */
#define local_10 (*(char * *)(frame_ + FRAME_OFF(0)))
#define local_c (*(char * *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(8)))
void __thiscall net_game_list_add(NetSession *this,iptr param_1)

{
  int iVar1;
  void *pvVar2;
  i32 uVar3;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (*(char *)((int)&this[0x3d].field_4 + 2) != '\0') {
    local_c = (char *)this[0x2c19].field_4;
    local_8 = 0;
    for (; local_c != (char *)0x0; local_c = *(char **)(local_c + 0x20)) {
      iVar1 = _strncmp(local_c,(char *)(param_1 + 0x74),0x20);
      if (iVar1 == 0) {
        if ((char *)this[0x2c19].field_4 == local_c) {
          this[0x2c19].field_4 = *(u32 *)(local_c + 0x20);
        }
        if (*(int *)(local_c + 0x24) != 0) {
          *(i32 *)(*(int *)(local_c + 0x24) + 0x20) = *(i32 *)(local_c + 0x20);
        }
        if (*(int *)(local_c + 0x20) != 0) {
          *(i32 *)(*(int *)(local_c + 0x20) + 0x24) = *(i32 *)(local_c + 0x24);
        }
        local_8 = *(i32 *)(local_c + 0x2c);
        operator_delete(local_c);
        break;
      }
    }
    local_c = (char *)this[0x2c19].field_4;
    local_10 = (char *)0x0;
    while ((local_c != (char *)0x0 &&
           (iVar1 = __strcmpi((char *)(param_1 + 0xe4),local_c + 0x70), 0 < iVar1))) {
      local_10 = local_c;
      local_c = *(char **)(local_c + 0x20);
    }
    while (((local_c != (char *)0x0 &&
            (iVar1 = __strcmpi((char *)(param_1 + 0xe4),local_c + 0x70), iVar1 == 0)) &&
           (iVar1 = __strcmpi((char *)(param_1 + 0x74),local_c), 0 < iVar1))) {
      local_10 = local_c;
      local_c = *(char **)(local_c + 0x20);
    }
    pvVar2 = operator_new(0x124);
    if (pvVar2 == (void *)0x0) {
      err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x635574, ((u8 *)&g.d_00635574)),ADDR(0x635554, ((u8 *)&g.d_00635554)),0x1cf);
    }
    crt_memcpy(pvVar2,param_1 + 0x74,0x124);
    if (local_10 == (char *)0x0) {
      *(u32 *)((int)pvVar2 + 0x20) = this[0x2c19].field_4;
      *(i32 *)((int)pvVar2 + 0x24) = 0;
      if (this[0x2c19].field_4 != 0) {
        *(void **)(this[0x2c19].field_4 + 0x24) = pvVar2;
      }
      this[0x2c19].field_4 = (u32)pvVar2;
    }
    else {
      *(i32 *)((int)pvVar2 + 0x20) = *(i32 *)(local_10 + 0x20);
      *(char **)((int)pvVar2 + 0x24) = local_10;
      *(void **)(local_10 + 0x20) = pvVar2;
      if (*(int *)((int)pvVar2 + 0x20) != 0) {
        *(void **)(*(int *)((int)pvVar2 + 0x20) + 0x24) = pvVar2;
      }
    }
    uVar3 = timer_ticks();
    *(i32 *)((int)pvVar2 + 0x28) = uVar3;
    *(i32 *)((int)pvVar2 + 0x2c) = local_8;
  }
  return;
}
#undef local_10
#undef local_c
#undef local_8

/* 0059b7fc auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall net_add_player(NetSession *this,iptr param_1)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  while( true ) {
    if (6 < local_8) {
      return;
    }
    if (*(char *)((int)this + local_8 * 0x54 + 0x251) == '\0') break;
    local_8++;
  }
  *(i32 *)((int)this + local_8 * 0x54 + 0x204) = *(i32 *)(param_1 + 0x10);
  _memset((void *)((int)this + local_8 * 0x54 + 0x208),0,0x20);
  _strncpy((char *)((int)this + local_8 * 0x54 + 0x208),(char *)(param_1 + 0x14),0x20);
  *(i8 *)((int)this + local_8 * 0x54 + 0x250) = 0;
  *(i8 *)((int)this + local_8 * 0x54 + 0x251) = 1;
  *(i32 *)((int)this + local_8 * 0x54 + 0x254) = 0xffffffff;
  crt_strcpy((int)this + local_8 * 0x54 + 0x228,param_1 + 0x34);
  *(i32 *)((int)this + local_8 * 0x54 + 0x248) = 0;
  *(i32 *)((int)this + local_8 * 0x54 + 0x24c) = 0;
  *(int *)this[0x40].pad_0 = *(int *)this[0x40].pad_0 + 1;
  this[0xab].field_4--;
  return;
}
#undef local_8

/* 0059b96a auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __thiscall net_remove_player(NetSession *this,int param_1)

{
  u8 *puVar1;
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  while ((local_8 < 7 && (*(int *)((int)this + local_8 * 0x54 + 0x204) != param_1))) {
    local_8++;
  }
  if ((local_8 < 7) && (*(char *)((int)this + local_8 * 0x54 + 0x251) != '\0')) {
    if ((0 < *(int *)((int)this + local_8 * 0x54 + 0x254)) &&
       (*(int *)((int)this + local_8 * 0x54 + 0x254) < 8)) {
      game.human_players =
           ~(byte)(1 << (*(byte *)((int)this + local_8 * 0x54 + 0x254) & 0x1f)) & game.human_players
      ;
    }
    *(i32 *)((int)this + local_8 * 0x54 + 0x204) = 0;
    *(i8 *)((int)this + local_8 * 0x54 + 0x208) = 0;
    *(i8 *)((int)this + local_8 * 0x54 + 0x250) = 0;
    *(i8 *)((int)this + local_8 * 0x54 + 0x251) = 0;
    puVar1 = this[0x8a].pad_0 + *(int *)((int)this + local_8 * 0x54 + 0x254) * 4;
    puVar1[0] = 0xff;
    puVar1[1] = 0xff;
    puVar1[2] = 0xff;
    puVar1[3] = 0xff;
    *(i32 *)((int)this + local_8 * 0x54 + 0x254) = 0xffffffff;
    *(int *)this[0x40].pad_0 = *(int *)this[0x40].pad_0 - 1;
  }
  return;
}
#undef local_8

/* 0059baf0 auto */
void __thiscall net_free_game_list(void *this)

{
  i32 uVar1;
  
  while (*(int *)((int)this + 0x160cc) != 0) {
    uVar1 = *(i32 *)(*(int *)((int)this + 0x160cc) + 0x20);
    operator_delete(*(void **)((int)this + 0x160cc));
    *(i32 *)((int)this + 0x160cc) = uVar1;
  }
  return;
}

/* 0059bb54 auto */
#define prefs_net_ip_address (*(i8 *)((u8 *)&g.d_006665b0))
void __cdecl net_on_broadcast_receive(int *param_1,ushort param_2)

{
  int iVar1;
  
  if (param_2 < 0x10) {
    dbg_log(ADDR(0x635584, ((u8 *)&g.d_00635584)));
  }
  else if (*param_1 == 0x66606660) {
    if ((param_1[1] != 0) ||
       ((((char)param_1[0xc] == '\0' ||
         (iVar1 = _strcmp((char *)(param_1 + 0xc),&prefs_net_ip_address), iVar1 == 0)) &&
        (((char)param_1[0x14] == '\0' ||
         (iVar1 = _strcmp((char *)(param_1 + 0x14),&prefs_net_ip_address), iVar1 != 0)))))) {
      net_msgq_enqueue((NetMsgQueueEnqueueView *)&net_msg_queue,0,(iptr)param_1,(uint)param_2);
    }
  }
  else {
    dbg_log(ADDR(0x6355cc, ((u8 *)&g.d_006355cc)));
  }
  return;
}
#undef prefs_net_ip_address

/* 0059bc41 auto */
#define mp_window_drag_active (*(char *)((u8 *)&g.d_00633a84))
#define net_send_sequence (*(int *)((u8 *)&g.d_00628468))
#define local_78 (*(int * *)(frame_ + FRAME_OFF(0)))
#define local_74 (*(uptr *)(frame_ + FRAME_OFF(4)))
#define local_70 (*(uptr *)(frame_ + FRAME_OFF(8)))
#define local_6c (*(char *)(frame_ + FRAME_OFF(12)))
#define local_6b (*(char *)(frame_ + FRAME_OFF(13)))
#define local_6a (*(i8 *)(frame_ + FRAME_OFF(14)))
#define local_4c (*(i8 (*)[64])(frame_ + FRAME_OFF(44)))
#define local_c (*(uint *)(frame_ + FRAME_OFF(108)))
#define local_8 (*(int * *)(frame_ + FRAME_OFF(112)))
void __cdecl net_on_secure_receive(uint param_1,int *param_2,uint param_3)

{
  size_t sVar1;
  i8 frame_[FRAME_OFF(120)] __attribute__((aligned(8)));  /* original stack frame */
  
  if (3 < param_3) {
    if (*param_2 == 0x66606660) {
      net_msgq_enqueue
                ((NetMsgQueueEnqueueView *)&net_msg_queue,param_1 & 0xffff,(iptr)param_2,param_3);
      net_last_recv_callback_size = param_3;
      net_last_queued_send_seq = net_send_sequence;
      local_8 = param_2;
      net_last_recv_msg_size = param_2[2];
      net_last_recv_msg_type = param_2[1];
    }
    else {
      dbg_log(ADDR(0x635608, ((u8 *)&g.d_00635608)));
      if (-1 < net_last_recv_msg_type) {
        __ultoa(net_last_recv_callback_size,&local_6c,10);
        dbg_logf_str(ADDR(0x635640, ((u8 *)&g.d_00635640)),(iptr)&local_6c);
        __itoa(net_last_queued_send_seq,&local_6c,10);
        dbg_logf_str(ADDR(0x635658, ((u8 *)&g.d_00635658)),(iptr)&local_6c);
        __itoa(net_last_recv_msg_type,&local_6c,10);
        dbg_logf_str(ADDR(0x635678, ((u8 *)&g.d_00635678)),(iptr)&local_6c);
        __ultoa(net_last_recv_msg_size,&local_6c,10);
        dbg_logf_str(ADDR(0x63568c, ((u8 *)&g.d_0063568c)),(iptr)&local_6c);
      }
      __itoa(net_send_sequence,&local_6c,10);
      dbg_logf_str(ADDR(0x6356a8, ((u8 *)&g.d_006356a8)),(iptr)&local_6c);
      __ultoa(param_3,&local_6c,10);
      dbg_logf_str(ADDR(0x6356bc, ((u8 *)&g.d_006356bc)),(iptr)&local_6c);
      for (local_70 = 0; (local_70 < 0x20 && (local_4c[0] = 0, local_70 <= param_3));
          local_70 = local_70 + 8) {
        for (local_74 = local_70; (local_74 < local_70 + 8 && (local_74 < param_3));
            local_74 = local_74 + 1) {
          local_c = (uint)*(byte *)(local_74 + (int)param_2);
          __itoa(local_c,&local_6c,0x10);
          sVar1 = _strlen(&local_6c);
          if (sVar1 == 1) {
            local_6b = local_6c;
            local_6a = 0;
            local_6c = '0';
          }
          crt_strcat(local_4c,&local_6c);
          crt_strcat(local_4c,&net_hexdump_space_str);
        }
        dbg_logf_str(ADDR(0x6356d4, ((u8 *)&g.d_006356d4)),(iptr)local_4c);
      }
      dbg_log(ADDR(0x6356d8, ((u8 *)&g.d_006356d8)));
      net_last_recv_msg_type = -1;
      local_78 = param_2;
      for (local_70 = 0; local_70 < 0x20; local_70++) {
        if (*local_78 == 0x66606660) {
          local_8 = local_78;
          dbg_log(ADDR(0x6356dc, ((u8 *)&g.d_006356dc)));
          __itoa(local_70,&local_6c,10);
          dbg_logf_str(ADDR(0x6356fc, ((u8 *)&g.d_006356fc)),(iptr)&local_6c);
          dbg_logf_str(ADDR(0x63571c, ((u8 *)&g.d_0063571c)),(iptr)(s_NM_DATAGRAM_00628470 + local_8[1] * 0x20));
          __ultoa(local_8[2],&local_6c,10);
          dbg_logf_str(ADDR(0x635738, ((u8 *)&g.d_00635738)),(iptr)&local_6c);
          __ultoa(local_8[3],&local_6c,10);
          dbg_logf_str(ADDR(0x635758, ((u8 *)&g.d_00635758)),(iptr)&local_6c);
          break;
        }
        local_78 = (int *)((int)local_78 + 1);
      }
    }
  }
  if (((300 < net_msgq_normal_count) || (0x21 < net_msgq_priority_count)) && (mp_window_drag_active != '\0')) {
    mp_release_mouse_capture();
  }
  return;
}
#undef mp_window_drag_active
#undef net_send_sequence
#undef local_78
#undef local_74
#undef local_70
#undef local_6c
#undef local_6b
#undef local_6a
#undef local_4c
#undef local_c
#undef local_8

/* 0059bfb5 auto */
void __cdecl net_on_new_client(i32 param_1,uint param_2)

{
  dbg_logf(ADDR(0x635774, ((u8 *)&g.d_00635774)),param_2 & 0xffff);
  return;
}

/* 0059bfdb auto */
#define net_server_conn_id (*(int *)((u8 *)&g.d_006ad300))
void __cdecl net_on_connected_to_server(short param_1)

{
  dbg_logf(ADDR(0x6357a8, ((u8 *)&g.d_006357a8)),(int)param_1);
  if ((-1 < param_1) && (param_1 < 8)) {
    net_server_conn_id = (int)param_1;
    net_connected_to_server = 1;
    net_send_message(0x2f,0,(int)param_1,0,0,0,0,0,0,0);
  }
  return;
}
#undef net_server_conn_id

/* 0059c04b auto */
#define net_lost_conn_total (*(int *)((u8 *)&g.d_006c8fb4))
void __cdecl net_on_connection_lost(ushort param_1)

{
  dbg_logf(ADDR(0x6357e0, ((u8 *)&g.d_006357e0)),(uint)param_1);
  net_lost_conn_total++;
  if (param_1 < 7) {
    *(int *)(&net_lost_conn_by_player + (uint)param_1 * 4) = *(int *)(&net_lost_conn_by_player + (uint)param_1 * 4) + 1;
  }
  return;
}
#undef net_lost_conn_total

/* 0059c0a4 auto */
#define local_104 (*(char (*)[256])(frame_ + FRAME_OFF(4)))
void __cdecl net_on_oversized_message(i32 param_1)

{
  i8 frame_[FRAME_OFF(264)] __attribute__((aligned(8)));  /* original stack frame */
  
  _sprintf(local_104,s_Oversized_XDaemon_message___ul_00635814,param_1);
  dbg_log((iptr)local_104);
  return;
}
#undef local_104

/* 0059c0e1 auto */
#define local_1c (*(void * *)(frame_ + FRAME_OFF(4)))
#define local_18 (*(NetMsgHeader *)(frame_ + FRAME_OFF(8)))
#define local_10 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_8 (*(size_t *)(frame_ + FRAME_OFF(24)))
void * __cdecl
net_msg_build_packet(i32 param_1,iptr param_2,i32 param_3,i32 param_4,
            i32 param_5,i32 param_6,i32 param_7,i32 param_8,
            size_t param_9)

{
  i8 frame_[FRAME_OFF(32)] __attribute__((aligned(8)));  /* original stack frame */
  u32 pargs_[7] = {(u32)(uptr)param_3, (u32)(uptr)param_4, (u32)(uptr)param_5, (u32)(uptr)param_6, (u32)(uptr)param_7, (u32)(uptr)param_8, (u32)(uptr)param_9};  /* the arguments, contiguous as on the original stack */
#define param_3 (*(i32 *)&pargs_[0])
#define param_4 (*(i32 *)&pargs_[1])
#define param_5 (*(i32 *)&pargs_[2])
#define param_6 (*(i32 *)&pargs_[3])
#define param_7 (*(i32 *)&pargs_[4])
#define param_8 (*(i32 *)&pargs_[5])
#define param_9 (*(size_t *)&pargs_[6])
  
  net_msg_header_init(&local_18,param_1);
  if (param_9 == 0) {
    if (param_2 == 0) {
      local_8 = 0;
      local_1c = operator_new(0x2c);
    }
    else {
      local_8 = __msize((void *)param_2);
      local_1c = (void *)crt_realloc(param_2,local_8 + 0x2c);
      crt_memmove((int)local_1c + 0x2c,local_1c,local_8);
    }
  }
  else {
    local_8 = param_9;
    local_1c = operator_new(param_9 + 0x2c);
    crt_memcpy((int)local_1c + 0x2c,param_2,local_8);
  }
  local_10 = local_8 + 0x2c;
  crt_memcpy(local_1c,&local_18,0x10);
  crt_memcpy((int)local_1c + 0x10,&param_3,4);
  crt_memcpy((int)local_1c + 0x14,&param_4,4);
  crt_memcpy((int)local_1c + 0x18,&param_5,4);
  crt_memcpy((int)local_1c + 0x1c,&param_6,4);
  crt_memcpy((int)local_1c + 0x20,&param_7,4);
  crt_memcpy((int)local_1c + 0x24,&param_8,4);
  crt_memcpy((int)local_1c + 0x28,&local_8,4);
  return local_1c;
}
#undef local_1c
#undef local_18
#undef local_10
#undef local_8
#undef param_3
#undef param_4
#undef param_5
#undef param_6
#undef param_7
#undef param_8
#undef param_9

/* 0059c276 auto */
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl net_reset_msg_counts(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  for (local_8 = 0; local_8 < 0xa9; local_8++) {
    *(i32 *)(&nm_recv_counts + local_8 * 4) = 0;
  }
  return;
}
#undef local_8

/* 0059c2b8 auto */
#define net_lost_conn_total (*(i32 *)((u8 *)&g.d_006c8fb4))
#define local_8 (*(int *)(frame_ + FRAME_OFF(0)))
void __cdecl net_reset_error_counts(void)

{
  i8 frame_[FRAME_OFF(8)] __attribute__((aligned(8)));  /* original stack frame */
  
  net_lost_conn_total = 0;
  for (local_8 = 0; local_8 < 7; local_8++) {
    *(i32 *)(&net_lost_conn_by_player + local_8 * 4) = 0;
  }
  return;
}
#undef net_lost_conn_total
#undef local_8

/* 0059c301 auto */
void __cdecl net_modal_idle_poll(void)

{
  net_process_messages((NetSession *)&net_session,1,0);
  return;
}

/* 0059c31f auto */
#define mp_double_moves (*(i16 *)((u8 *)&g.d_00654fae))
#define mp_double_production (*(i16 *)((u8 *)&g.d_00654fac))
#define mp_open_game (*(i16 *)((u8 *)&g.d_00654c74))
#define mp_simultaneous_setting (*(i16 *)((u8 *)&g.d_00654c7c))
#define mp_turn_time_limit_ms (*(i32 *)((u8 *)&g.d_00654b70))
#define prefs_net_ip_address (*(i8 *)((u8 *)&g.d_006665b0))
#define prefs_net_player_name (*(i8 *)((u8 *)&g.d_00666570))
#define scenario_name (*(i8 *)((u8 *)&g.d_0064bc62))
#define scenario_start_year (*(i16 *)((u8 *)&g.d_0064bcb6))
#define scenario_year_increment (*(i16 *)((u8 *)&g.d_0064bcb4))
#define local_28 (*(i32 (*)[9])(frame_ + FRAME_OFF(0)))
/* WARNING: Type propagation algorithm not settling */

void __cdecl net_fill_game_info(iptr param_1)

{
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_28[0] = 0;
  local_28[1] = 1;
  local_28[2] = 3;
  local_28[3] = 7;
  local_28[4] = 0xf;
  local_28[5] = 0x1f;
  local_28[6] = 0x3f;
  local_28[7] = 0x7f;
  local_28[8] = 0xff;
  crt_strcpy(param_1 + 0x30,PTR_s_5_4_0f_Multiplayer_26_March_99_0062765c);
  _memset((void *)param_1,0,0x20);
  _strncpy((char *)param_1,&prefs_net_ip_address,0x20);
  _memset((void *)(param_1 + 0x70),0,0x20);
  _strncpy((char *)(param_1 + 0x70),&net_game_name,0x20);
  _memset((void *)(param_1 + 0x90),0,0x20);
  _strncpy((char *)(param_1 + 0x90),&prefs_net_player_name,0x20);
  *(i16 *)(param_1 + 0xb0) = mp_open_game;
  *(u8 *)(param_1 + 0xb2) = game.difficulty;
  *(u8 *)(param_1 + 0xb3) = game.barbarian_activity;
  if (game.civs_alive == '\0') {
    *(i8 *)(param_1 + 0xb4) = *(i8 *)(local_28 + (uint)game.num_enemies + 2);
  }
  else {
    *(u8 *)(param_1 + 0xb4) = game.civs_alive;
  }
  *(i8 *)(param_1 + 0xb5) = *(i8 *)(local_28 + net_player_count);
  *(i32 *)(param_1 + 0xb8) = mp_turn_time_limit_ms;
  crt_strcpy(param_1 + 0xbc,&scenario_name);
  *(i16 *)(param_1 + 0x10c) = mp_double_moves;
  *(i16 *)(param_1 + 0x10e) = mp_double_production;
  *(u16 *)(param_1 + 0x110) = game.game_flags;
  *(i16 *)(param_1 + 0x112) = game.first_launch_turn;
  *(i16 *)(param_1 + 0x114) = scenario_year_increment;
  *(i16 *)(param_1 + 0x116) = scenario_start_year;
  *(i16 *)(param_1 + 0x118) = game.turn;
  *(i16 *)(param_1 + 0x11e) = mp_simultaneous_setting;
  *(i32 *)(param_1 + 0x24) = 0;
  *(i32 *)(param_1 + 0x20) = *(i32 *)(param_1 + 0x24);
  *(i32 *)(param_1 + 0x2c) = 0;
  *(i32 *)(param_1 + 0x28) = *(i32 *)(param_1 + 0x2c);
  *(i16 *)(param_1 + 0x11a) = map.width;
  *(i16 *)(param_1 + 0x11c) = map.height;
  return;
}
#undef mp_double_moves
#undef mp_double_production
#undef mp_open_game
#undef mp_simultaneous_setting
#undef mp_turn_time_limit_ms
#undef prefs_net_ip_address
#undef prefs_net_player_name
#undef scenario_name
#undef scenario_start_year
#undef scenario_year_increment
#undef local_28

/* 0059d080 auto */
#define local_c (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(8)))
NetMsgHeader * __thiscall net_msg_player_info_init(NetMsgHeader *this)

{
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  net_msg_header_init(this,0x2e);
  this[2].field_0 = 0;
  this[2].field_4 = 0;
  this[3].field_0 = 0;
  *(i8 *)&this[4].field_0 = 0;
  *(i8 *)&this[7].field_0 = 0;
  *(i8 *)&this[10].field_0 = 0;
  this[0x22].field_4 = 0;
  for (local_8 = 0; local_8 < 7; local_8++) {
    for (local_c = 0; local_c < 0x18; local_c++) {
      *(i8 *)((int)&this[local_8 * 3 + 0xd].field_4 + local_c) = 0;
    }
  }
  this[3].field_4 = 0;
  this[0xd].field_0 = 0;
  this[1].field_0 = 0x118;
  return this;
}
#undef local_c
#undef local_8

/* 005a9f30 auto */
#define dialog_stack_top (*(int * *)((u8 *)&g.d_006ad678))
#define nm_production_complete_count (*(int *)((u8 *)&g.d_006c9210))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
void __cdecl net_host_wait_production_idle(void)

{
  bool bVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  net_process_messages((NetSession *)&net_session,1,0);
  if ((nm_production_complete_count != 0) || (net_player_count < 2)) {
    bVar1 = true;
    for (local_c = 1; local_c < 8; local_c++) {
      if ((((1 << ((byte)local_c & 0x1f) & (uint)game.civs_alive) != 0) &&
          ((1 << ((byte)local_c & 0x1f) & (uint)game.human_players) != 0)) &&
         (*(int *)(&net_civ_phase_done + local_c * 4) == 0)) {
        bVar1 = false;
        break;
      }
    }
    if (bVar1) {
      dialog_stack_top[0xf] = dialog_stack_top[0xf] | 0x400;
      wnd_end_modal_loop((ModalMenuWindow *)(*dialog_stack_top + 0x48));
    }
  }
  return;
}
#undef dialog_stack_top
#undef nm_production_complete_count
#undef local_c

/* 005aa004 auto */
#define dialog_stack_top (*(int * *)((u8 *)&g.d_006ad678))
#define nm_human_move_complete_count (*(int *)((u8 *)&g.d_006c921c))
#define local_c (*(int *)(frame_ + FRAME_OFF(4)))
void __cdecl net_host_wait_human_moves_idle(void)

{
  bool bVar1;
  i8 frame_[FRAME_OFF(16)] __attribute__((aligned(8)));  /* original stack frame */
  
  net_process_messages((NetSession *)&net_session,1,0);
  if ((nm_human_move_complete_count != 0) || (net_player_count < 2)) {
    bVar1 = true;
    for (local_c = 1; local_c < 8; local_c++) {
      if ((((1 << ((byte)local_c & 0x1f) & (uint)game.civs_alive) != 0) &&
          ((1 << ((byte)local_c & 0x1f) & (uint)game.human_players) != 0)) &&
         (*(int *)(&net_civ_phase_done + local_c * 4) == 0)) {
        bVar1 = false;
        break;
      }
    }
    if ((bVar1) || (net_player_count < 2)) {
      dialog_stack_top[0xf] = dialog_stack_top[0xf] | 0x400;
      wnd_end_modal_loop((ModalMenuWindow *)(*dialog_stack_top + 0x48));
    }
  }
  return;
}
#undef dialog_stack_top
#undef nm_human_move_complete_count
#undef local_c

/* 005aa0e5: written by hand in src/game/bigframes.c */

/* 005ab0a3 auto */
#define dialog_stack_top (*(int * *)((u8 *)&g.d_006ad678))
#define game_loop_active (*(char *)((u8 *)&g.d_00628044))
#define net_lost_conn_total (*(int *)((u8 *)&g.d_006c8fb4))
#define net_slot_civs (*(iptr *)((u8 *)&g.d_006ad35c))
void __cdecl net_client_wait_production_idle(void)

{
  net_process_messages((NetSession *)&net_session,1,0);
  net_heartbeat_check(net_slot_civs);
  if ((((nm_ai_movement_count != 0) || (nm_end_sequence_count != 0)) || (game_loop_active == '\0')) ||
     (net_lost_conn_total != 0)) {
    dialog_stack_top[0xf] = dialog_stack_top[0xf] | 0x400;
    wnd_end_modal_loop((ModalMenuWindow *)(*dialog_stack_top + 0x48));
  }
  return;
}
#undef dialog_stack_top
#undef game_loop_active
#undef net_lost_conn_total
#undef net_slot_civs

/* 005ab120 auto */
#define dialog_stack_top (*(int * *)((u8 *)&g.d_006ad678))
#define game_loop_active (*(char *)((u8 *)&g.d_00628044))
#define net_lost_conn_total (*(int *)((u8 *)&g.d_006c8fb4))
#define net_slot_civs (*(iptr *)((u8 *)&g.d_006ad35c))
void __cdecl net_client_wait_ai_moves_idle(void)

{
  net_process_messages((NetSession *)&net_session,1,0);
  net_heartbeat_check(net_slot_civs);
  if ((((nm_human_movement_count != 0) || (nm_end_sequence_count != 0)) || (game_loop_active == '\0')) ||
     (net_lost_conn_total != 0)) {
    dialog_stack_top[0xf] = dialog_stack_top[0xf] | 0x400;
    wnd_end_modal_loop((ModalMenuWindow *)(*dialog_stack_top + 0x48));
  }
  return;
}
#undef dialog_stack_top
#undef game_loop_active
#undef net_lost_conn_total
#undef net_slot_civs

/* 005ab19d auto */
#define dialog_stack_top (*(int * *)((u8 *)&g.d_006ad678))
#define game_loop_active (*(char *)((u8 *)&g.d_00628044))
#define net_host_handoff_stage (*(char *)((u8 *)&g.d_006ad698))
#define net_lost_conn_total (*(int *)((u8 *)&g.d_006c8fb4))
#define net_slot_civs (*(iptr *)((u8 *)&g.d_006ad35c))
#define player_has_quit (*(char *)((u8 *)&g.d_006ad685))
void __cdecl net_client_wait_human_moves_idle(void)

{
  net_process_messages((NetSession *)&net_session,1,0);
  net_heartbeat_check(net_slot_civs);
  if ((((nm_production_begin_count != 0) || (net_host_handoff_stage == 1)) || (nm_end_sequence_count != 0)) ||
     (((player_has_quit == 1 || (game_loop_active == '\0')) || (net_lost_conn_total != 0)))) {
    dialog_stack_top[0xf] = dialog_stack_top[0xf] | 0x400;
    wnd_end_modal_loop((ModalMenuWindow *)(*dialog_stack_top + 0x48));
  }
  return;
}
#undef dialog_stack_top
#undef game_loop_active
#undef net_host_handoff_stage
#undef net_lost_conn_total
#undef net_slot_civs
#undef player_has_quit

/* 005ab23a auto */
#define dialog_stack_top (*(int * *)((u8 *)&g.d_006ad678))
#define game_loop_active (*(char *)((u8 *)&g.d_00628044))
#define net_host_handoff_stage (*(char *)((u8 *)&g.d_006ad698))
#define net_lost_conn_total (*(int *)((u8 *)&g.d_006c8fb4))
#define net_slot_civs (*(iptr *)((u8 *)&g.d_006ad35c))
#define player_has_quit (*(char *)((u8 *)&g.d_006ad685))
void __cdecl net_client_hotwait_idle(void)

{
  net_process_messages((NetSession *)&net_session,1,0);
  net_heartbeat_check(net_slot_civs);
  if ((((nm_production_begin_count != 0) || (net_host_handoff_stage != '\0')) || (nm_end_sequence_count != 0)) ||
     (((player_has_quit != '\0' || (game_loop_active == '\0')) || (net_lost_conn_total != 0)))) {
    dialog_stack_top[0xf] = dialog_stack_top[0xf] | 0x400;
    wnd_end_modal_loop((ModalMenuWindow *)(*dialog_stack_top + 0x48));
  }
  return;
}
#undef dialog_stack_top
#undef game_loop_active
#undef net_host_handoff_stage
#undef net_lost_conn_total
#undef net_slot_civs
#undef player_has_quit

/* 005ab2d5 auto */
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define autoplay_turns_left (*(i16 *)((u8 *)&g.d_00654faa))
#define dlg_pending_idle_callback (*(i8 * *)((u8 *)&g.d_00635a3c))
#define game_loop_active (*(char *)((u8 *)&g.d_00628044))
#define game_over_reason (*(int *)((u8 *)&g.d_0064b1ac))
#define human_civ (*(iptr *)((u8 *)&g.d_006d1da0))
#define mp_turn_civ (*(i8 *)((u8 *)&g.d_006ad578))
#define mp_turn_seconds_left (*(int *)((u8 *)&g.d_00633a78))
#define mp_turn_time_limit_ms (*(int *)((u8 *)&g.d_00654b70))
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define net_host_handoff_stage (*(char *)((u8 *)&g.d_006ad698))
#define net_local_slot (*(int *)((u8 *)&g.d_006ad304))
#define net_slot_civs (*(i32 *)((u8 *)&g.d_006ad35c))
#define nm_start_civ_count (*(i32 *)((u8 *)&g.d_006c9038))
#define player_has_quit (*(char *)((u8 *)&g.d_006ad685))
#define saved_human_players (*(u8 *)((u8 *)&g.d_00673b08))
#define saved_resume_new_game (*(short *)((u8 *)&g.d_00654fa6))
#define saved_turn_civ (*(char *)((u8 *)&g.d_00654fa4))
#define turn_resume_civ (*(char *)((u8 *)&g.d_00628048))
#define turn_resume_new_game (*(int *)((u8 *)&g.d_0062c488))
#define main_view_timer_cache_i32 (*(i32 *)((u8 *)&g.d_0066c990))
#define saved_human_players_i32 (*(i32 *)((u8 *)&g.d_00673b08))
#define mp_turn_civ_i32 (*(i32 *)((u8 *)&g.d_006ad578))
#define civ (*(int *)(frame_ + FRAME_OFF(4)))
#define unit (*(iptr *)(frame_ + FRAME_OFF(8)))
#define local_314 (*(Dialog *)(frame_ + FRAME_OFF(12)))
#define local_20 (*(i8 *)(frame_ + FRAME_OFF(768)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(772)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(776)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(780)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(784)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(788)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(792)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __cdecl net_client_turn_loop(void)

{
  char cVar1;
  SHORT SVar2;
  iptr iVar3;
  int iVar4;
  i32 uVar5;
  iptr iVar5;
  i8 frame_[FRAME_OFF(800)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  local_14 = 1;
  dialog_ctor(&local_314,0x4000);
  local_8 = 0;
  local_20 = 1;
  iVar5 = net_slot_civs;
  iVar3 = civ_name_plural(net_slot_civs);
  dbg_logf_str_int(ADDR(0x635cd0, ((u8 *)&g.d_00635cd0)),iVar3,iVar5);
  for (civ = 1; civ < 8; civ++) {
    if (((*(int *)(&net_player_slots + *(int *)(&net_civ_slots + civ * 4) * 0x54) != 0) &&
        ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0)) &&
       ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) {
      iVar4 = civ;
      iVar3 = civ_name_plural(civ);
      dbg_logf_str_int(ADDR(0x635ce0, ((u8 *)&g.d_00635ce0)),iVar3,iVar4);
    }
  }
  net_reset_error_counts();
  human_civ = (&net_slot_civs)[net_local_slot * 0x15];
  turn_resume_civ = saved_turn_civ;
  turn_resume_new_game = (int)saved_resume_new_game;
  picwnd_close((PictureWindowCore *)&advisor_window);
  picwnd_close((PictureWindowCore *)&casualty_window);
  menu_update_states();
  game.player_civ = (byte)human_civ;
  game.turn_civ = (byte)human_civ;
  mapview_update_title((FrameWindow *)&map_views);
  local_1c = 0;
  for (unit = 0; unit < game.num_units; unit++) {
    if ((units[unit].id != 0) && (units[unit].owner == human_civ)) {
      mapview_center_on
                ((ViewWindow *)&map_views,(int)units[unit].x,(int)units[unit].y);
      local_1c++;
      break;
    }
  }
  if (local_1c == 0) {
    for (unit = 0; unit < game.num_cities; unit++) {
      if ((cities[unit].id != 0) && (cities[unit].owner == human_civ)) {
        mapview_center_on
                  ((ViewWindow *)&map_views,(int)cities[unit].x,(int)cities[unit].y
                  );
        break;
      }
    }
  }
  status_draw_info(1);
  status_draw_civ_color(human_civ);
  ui_redraw_all_maps(1);
  cVar1 = turn_resume_civ;
  if ((1 << ((byte)human_civ & 0x1f) & (uint)game.human_players) == 0) {
    net_heartbeat_send(net_slot_civs);
    dlg_pending_idle_callback = ((void *)ADDR(0x00401c35, net_client_hotwait_idle));
    popup_game_sprite_flags(ADDR(0x635cf0, ((u8 *)&g.d_00635cf0)),0x2000000,ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
    cVar1 = turn_resume_civ;
  }
LAB_005ab60f:
  do {
    turn_resume_civ = cVar1;
    for (unit = 0; unit < game.num_units; unit++) {
      if ((units[unit].id != 0) && (units[unit].owner == human_civ)) {
        unit_exhaust_moves(unit);
      }
    }
    if (local_14 == 0) {
      net_heartbeat_send(net_slot_civs);
      dlg_pending_idle_callback = ((void *)ADDR(0x00402450, net_client_wait_human_moves_idle));
      popup_game_with_sprite(ADDR(0x635d00, ((u8 *)&g.d_00635d00)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
    }
    net_heartbeat_send(net_slot_civs);
    while ((((nm_production_begin_count == 0 && (net_host_handoff_stage == '\0')) && (nm_end_sequence_count == 0)) &&
           ((player_has_quit == '\0' && (game_loop_active != '\0'))))) {
      net_process_messages((NetSession *)&net_session,1,0);
      net_heartbeat_check(net_slot_civs);
      iVar4 = net_check_lost_connections();
      if (iVar4 != 0) {
        local_8 = 0xffffffff;
        /* inlined unwind funclet 005abfdb */ { dialog_dtor((Dialog *)((iptr)&local_314)); }
        uVar5 = 0;
        goto LAB_005abff1;
      }
    }
    if (net_host_handoff_stage != '\0') {
      iVar4 = net_client_transfer_server();
      if (iVar4 == 0) {
        local_8 = 0xffffffff;
        /* inlined unwind funclet 005abfdb */ { dialog_dtor((Dialog *)((iptr)&local_314)); }
        uVar5 = 0;
        goto LAB_005abff1;
      }
      if (net_host_flag != '\0') {
        local_8 = 0xffffffff;
        /* inlined unwind funclet 005abfdb */ { dialog_dtor((Dialog *)((iptr)&local_314)); }
        uVar5 = 1;
        goto LAB_005abff1;
      }
      if (((nm_production_begin_count == 0) && (nm_end_sequence_count == 0)) &&
         ((player_has_quit == '\0' && (cVar1 = turn_resume_civ, game_loop_active != '\0'))))
      goto LAB_005ab60f;
    }
    if ((nm_end_sequence_count == 0) && (game_loop_active != '\0')) {
      nm_start_civ_count = 0;
      nm_production_begin_count = 0;
      human_civ = (&net_slot_civs)[net_local_slot * 0x15];
      game.player_civ = (byte)human_civ;
      game.turn_civ = (byte)human_civ;
      if (mp_turn_time_limit_ms != 0) {
        mp_turn_seconds_left = mp_turn_time_limit_ms / 1000;
        main_view_timer_cache_i32 = 0xffffffff;
      }
      while ((net_msgq_priority_count != 0 || (net_msgq_normal_count != 0))) {
        net_process_messages((NetSession *)&net_session,1,0);
      }
      mp_turn_civ_i32 = human_civ;
      mapview_update_title((FrameWindow *)&map_views);
      map_redraw_all_views(human_civ,1);
      status_draw_info(1);
      status_draw_civ_color(human_civ);
      if (autoplay_active == 0) {
        if (turn_resume_civ == '\0') {
          civ_check_throne_room_upgrade();
        }
        if ((turn_resume_civ == '\0') || (turn_resume_new_game != 0)) {
          civ_process_turn(human_civ);
          net_send_state_diff(0xff,2,0,0,0);
        }
        XD_FlushSendBuffer(60000);
        game_turn_start_popups();
        net_send_message(0x8c,0,human_civ,0,0,0,0,0,0,0);
        net_heartbeat_send(net_slot_civs);
        dlg_pending_idle_callback = ((void *)ADDR(0x004028c4, net_client_wait_production_idle));
        popup_game_with_sprite(ADDR(0x635d20, ((u8 *)&g.d_00635d20)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        while (((nm_ai_movement_count == 0 && (nm_end_sequence_count == 0)) && (game_loop_active != '\0'))) {
          net_process_messages((NetSession *)&net_session,1,0);
          net_heartbeat_check(net_slot_civs);
          iVar4 = net_check_lost_connections();
          if (iVar4 != 0) {
            local_8 = 0xffffffff;
            /* inlined unwind funclet 005abfdb */ { dialog_dtor((Dialog *)((iptr)&local_314)); }
            uVar5 = 0;
            goto LAB_005abff1;
          }
        }
        if ((nm_end_sequence_count == 0) && (game_loop_active != '\0')) {
          nm_ai_movement_count = 0;
          net_heartbeat_send(net_slot_civs);
          dlg_pending_idle_callback = ((void *)ADDR(0x00401695, net_client_wait_ai_moves_idle));
          popup_game_with_sprite(ADDR(0x635d30, ((u8 *)&g.d_00635d30)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
          while (((nm_human_movement_count == 0 && (nm_end_sequence_count == 0)) && (game_loop_active != '\0'))) {
            net_process_messages((NetSession *)&net_session,1,0);
            net_heartbeat_check(net_slot_civs);
            iVar4 = net_check_lost_connections();
            if (iVar4 != 0) {
              local_8 = 0xffffffff;
              /* inlined unwind funclet 005abfdb */ { dialog_dtor((Dialog *)((iptr)&local_314)); }
              uVar5 = 0;
              goto LAB_005abff1;
            }
          }
          if ((nm_end_sequence_count == 0) && (game_loop_active != '\0')) {
            nm_human_movement_count = 0;
            if ((*(short *)(&civ_intro_shown + human_civ * 2) == 0) && (autoplay_active == 0)) {
              civ_intro_popup(human_civ);
              *(i16 *)(&civ_intro_shown + human_civ * 2) = 1;
            }
            local_18 = *(int *)(&casualty_counts + human_civ * 4) -
                       *(int *)(&casualty_reported_counts + human_civ * 4);
            if (autoplay_active == 0) {
              dlg_pending_idle_callback = ((void *)ADDR(0x00403c74, turn_popup_timeout_idle));
              iVar3 = civ_leader_title(human_civ);
              text_set_string_arg(0,iVar3);
              iVar3 = civ_leader_name(human_civ);
              text_set_string_arg(1,iVar3);
              if (local_18 < 1) {
                dialog_load_text_noflags(&local_314,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x635d54, ((u8 *)&g.d_00635d54)));
                dialog_add_sprite((DialogOptionList *)&local_314,ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0,0);
                dialog_set_image_zoom((DialogWindowView *)&local_314,0);
                input_flush_events();
                snd_play_effect(0x30,0,0,0);
                dlg_show_modal(&local_314,0);
              }
              else {
                *(i32 *)(&casualty_reported_counts + human_civ * 4) =
                     *(i32 *)(&casualty_counts + human_civ * 4);
                text_set_number_arg(0,local_18);
                if (local_18 == 1) {
                  dialog_load_text_noflags(&local_314,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x635d3c, ((u8 *)&g.d_00635d3c)));
                }
                else {
                  dialog_load_text_noflags(&local_314,ADDR(0x6359d4, ((u8 *)&g.d_006359d4)),ADDR(0x635d48, ((u8 *)&g.d_00635d48)));
                }
                dialog_add_sprite((DialogOptionList *)&local_314,ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0,0);
                dialog_set_image_zoom((DialogWindowView *)&local_314,0);
                input_flush_events();
                snd_play_effect(0x30,0,0,0);
                dlg_show_modal(&local_314,0);
                if (local_314.field_dc != 0) {
                  casualty_timeline_show(human_civ);
                }
              }
            }
            if (mp_turn_time_limit_ms != 0) {
              mp_turn_timer_start(1);
            }
            game_player_move_loop();
          }
          else {
            nm_end_sequence_count = 0;
          }
        }
        else {
          local_20 = 0;
        }
      }
      else {
        saved_human_players_i32 = (uint)game.human_players;
        game.human_players = '\0';
        if ((turn_resume_civ == '\0') || (turn_resume_new_game != 0)) {
          civ_process_turn(human_civ);
        }
        net_send_message(0x8c,0,human_civ,0,0,0,0,0,0,0);
        net_heartbeat_send(net_slot_civs);
        dlg_pending_idle_callback = ((void *)ADDR(0x004028c4, net_client_wait_production_idle));
        popup_game_with_sprite(ADDR(0x635d10, ((u8 *)&g.d_00635d10)),ADDR(0x63fc58, ((u8 *)&g.d_0063fc58)),0);
        while (((nm_ai_movement_count == 0 && (nm_end_sequence_count == 0)) && (game_loop_active != '\0'))) {
          net_process_messages((NetSession *)&net_session,1,0);
          net_heartbeat_check(net_slot_civs);
          iVar4 = net_check_lost_connections();
          if (iVar4 != 0) {
            local_8 = 0xffffffff;
            /* inlined unwind funclet 005abfdb */ { dialog_dtor((Dialog *)((iptr)&local_314)); }
            uVar5 = 0;
            goto LAB_005abff1;
          }
        }
        if ((nm_end_sequence_count == 0) && (game_loop_active != '\0')) {
          nm_ai_movement_count = 0;
          if (mp_turn_time_limit_ms != 0) {
            mp_turn_timer_start(1);
          }
          ai_process_civ_units();
          game.human_players = saved_human_players;
          SVar2 = GetAsyncKeyState(0x1b);
          if (((int)SVar2 & 0x8001U) != 0) {
            autoplay_turns_left = 1;
          }
        }
        else {
          local_20 = 0;
        }
      }
    }
    else {
      local_20 = 0;
    }
    mp_turn_timer_stop(1);
    status_redraw(1);
    ui_pump_messages();
    if (game_over_reason != 0) {
      game_loop_active = '\0';
    }
    net_send_state_diff(0xff,2,0,0,0);
    net_send_message(0x8f,0,human_civ,0,0,0,0,0,0,0);
    XD_FlushSendBuffer(60000);
    saved_turn_civ = '\0';
    turn_resume_civ = '\0';
    saved_resume_new_game = 0;
    turn_resume_new_game = 0;
    local_14 = 0;
    cVar1 = '\0';
    if (game_loop_active == '\0') {
      net_send_message(0x2d,0,human_civ,0,0,0,0,0,0,0);
      XD_FlushSendBuffer(60000);
      net_session_shutdown(&net_session,1);
      if (game_over_reason != 0) {
        game_handle_game_over();
      }
      local_8 = 0xffffffff;
      /* inlined unwind funclet 005abfdb */ { dialog_dtor((Dialog *)((iptr)&local_314)); }
      uVar5 = 0;
LAB_005abff1:
      return uVar5;
    }
  } while( true );
}
#undef autoplay_active
#undef autoplay_turns_left
#undef dlg_pending_idle_callback
#undef game_loop_active
#undef game_over_reason
#undef human_civ
#undef mp_turn_civ
#undef mp_turn_seconds_left
#undef mp_turn_time_limit_ms
#undef net_host_flag
#undef net_host_handoff_stage
#undef net_local_slot
#undef net_slot_civs
#undef nm_start_civ_count
#undef player_has_quit
#undef saved_human_players
#undef saved_resume_new_game
#undef saved_turn_civ
#undef turn_resume_civ
#undef turn_resume_new_game
#undef main_view_timer_cache_i32
#undef saved_human_players_i32
#undef mp_turn_civ_i32
#undef civ
#undef unit
#undef local_314
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 005b9ec6 auto */
#define net_batch_used_dwords (*(i32 *)((u8 *)&g.d_006365f4))
#define net_tile_batch_active (*(i8 *)((u8 *)&g.d_006ad69a))
#define net_tile_sync_enabled (*(i8 *)((u8 *)&g.d_006ad699))
#define net_batch_buffer_i32 (*(i32 *)((u8 *)&g.d_006d1190))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl net_batch_begin(void)

{
  if (2 < game.multiplayer) {
    net_tile_sync_enabled = 0;
    net_tile_batch_active = 1;
    _memset(&net_batch_buffer,0,0x400);
    net_batch_buffer_i32 = 0;
    net_batch_used_dwords = 1;
  }
  return;
}
#undef net_batch_used_dwords
#undef net_tile_batch_active
#undef net_tile_sync_enabled
#undef net_batch_buffer_i32

/* 005b9f1c auto */
#define net_batch_used_dwords (*(int *)((u8 *)&g.d_006365f4))
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define net_tile_batch_active (*(i8 *)((u8 *)&g.d_006ad69a))
#define net_tile_sync_enabled (*(i8 *)((u8 *)&g.d_006ad699))
#define net_batch_buffer_i32 (*(i32 *)((u8 *)&g.d_006d1190))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl net_batch_flush(void)

{
  if (2 < game.multiplayer) {
    net_tile_sync_enabled = 1;
    net_tile_batch_active = 0;
    if (net_host_flag == '\0') {
      if (1 < net_batch_used_dwords) {
        net_send_message(0x59,0,0,0,0,0,0,0,0,0);
        XD_FlushSendBuffer(5000);
        _memset(&net_batch_buffer,0,0x400);
        net_batch_buffer_i32 = 0;
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
#undef net_batch_used_dwords
#undef net_host_flag
#undef net_tile_batch_active
#undef net_tile_sync_enabled
#undef net_batch_buffer_i32

/* 005b9fde auto */
#define net_batch_used_dwords (*(int *)((u8 *)&g.d_006365f4))
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define net_batch_buffer_i32 (*(i32 *)((u8 *)&g.d_006d1190))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl
net_batch_add(int param_1,i32 param_2,i32 param_3,i32 param_4,iptr param_5,
            i32 param_6)

{
  if (net_host_flag != '\0') {
    err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x636634, ((u8 *)&g.d_00636634)),ADDR(0x636618, ((u8 *)&g.d_00636618)),0x3de);
  }
  if (0x100 - net_batch_used_dwords < *(int *)(&net_batch_record_sizes + param_1 * 4) + 1) {
    net_send_message(0x59,0,0,0,0,0,0,0,0,0);
    XD_FlushSendBuffer(5000);
    _memset(&net_batch_buffer,0,0x400);
    net_batch_buffer_i32 = 0;
    net_batch_used_dwords = 1;
  }
  net_batch_buffer_i32++;
  *(int *)(&net_batch_buffer + net_batch_used_dwords * 4) = param_1;
  net_batch_used_dwords++;
  switch(param_1) {
  case 0:
  case 2:
    *(i32 *)(&net_batch_buffer + net_batch_used_dwords * 4) = param_2;
    net_batch_used_dwords++;
    *(i32 *)(&net_batch_buffer + net_batch_used_dwords * 4) = param_3;
    net_batch_used_dwords++;
    *(i32 *)(&net_batch_buffer + net_batch_used_dwords * 4) = param_4;
    net_batch_used_dwords++;
    *(iptr *)(&net_batch_buffer + net_batch_used_dwords * 4) = param_5;
    net_batch_used_dwords++;
    break;
  case 1:
  case 3:
  case 4:
  case 5:
  case 6:
    *(i32 *)(&net_batch_buffer + net_batch_used_dwords * 4) = param_2;
    net_batch_used_dwords++;
    *(i32 *)(&net_batch_buffer + net_batch_used_dwords * 4) = param_3;
    net_batch_used_dwords++;
    *(i32 *)(&net_batch_buffer + net_batch_used_dwords * 4) = param_4;
    net_batch_used_dwords++;
    break;
  case 7:
    *(i32 *)(&net_batch_buffer + net_batch_used_dwords * 4) = param_2;
    net_batch_used_dwords++;
    *(i32 *)(&net_batch_buffer + net_batch_used_dwords * 4) = param_3;
    net_batch_used_dwords++;
    *(i32 *)(&net_batch_buffer + net_batch_used_dwords * 4) = param_4;
    net_batch_used_dwords++;
    *(iptr *)(&net_batch_buffer + net_batch_used_dwords * 4) = param_5;
    net_batch_used_dwords++;
    *(i32 *)(&net_batch_buffer + net_batch_used_dwords * 4) = param_6;
    net_batch_used_dwords++;
  }
  return;
}
#undef net_batch_used_dwords
#undef net_host_flag
#undef net_batch_buffer_i32

/* 005ba206 auto */
#define net_host_flag (*(char *)((u8 *)&g.d_006ad2f7))
#define net_tile_sync_enabled (*(i8 *)((u8 *)&g.d_006ad699))
#define local_28 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_24 (*(iptr *)(frame_ + FRAME_OFF(4)))
#define local_20 (*(iptr (*)[4])(frame_ + FRAME_OFF(8)))
#define local_10 (*(i32 *)(frame_ + FRAME_OFF(24)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(32)))
void __cdecl net_apply_tile_updates(iptr param_1)

{
  int iVar2;
  i8 uVar3;
  iptr iVar1;
  i8 frame_[FRAME_OFF(40)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0;
  if (2 < game.multiplayer) {
    if (net_host_flag == '\0') {
      err_report((ErrorContext *)&err_report_ctx,7,ADDR(0x636664, ((u8 *)&g.d_00636664)),ADDR(0x636648, ((u8 *)&g.d_00636648)),0x416);
    }
    uVar3 = net_tile_sync_enabled;
    net_tile_sync_enabled = 0;
    iVar1 = local_8 * 4;
    local_8++;
    for (local_28 = *(int *)(param_1 + iVar1); 0 < local_28; local_28--) {
      iVar2 = *(int *)(param_1 + local_8 * 4);
      for (local_24 = 0; local_8 = local_8 + 1, local_24 < *(int *)(&net_batch_record_sizes + iVar2 * 4) - 1;
          local_24 = local_24 + 1) {
        local_20[local_24] = *(iptr *)(param_1 + local_8 * 4);
      }
      switch(iVar2) {
      case 0:
        tile_set_improvements(local_20[0],local_20[1],local_20[2],local_20[3],1);
        break;
      case 1:
        tile_set_terrain(local_20[0],local_20[1],local_20[2],1);
        break;
      case 2:
        tile_set_visible(local_20[0],local_20[1],local_20[2],local_20[3],1);
        break;
      case 3:
        tile_set_fertility(local_20[0],local_20[1],local_20[2],1);
        break;
      case 4:
        tile_set_owner(local_20[0],local_20[1],local_20[2],1);
        break;
      case 5:
        tile_set_landmass(local_20[0],local_20[1],local_20[2],1);
        break;
      case 6:
        tile_set_radius_civ(local_20[0],local_20[1],local_20[2],1);
        break;
      case 7:
        known_set(local_20[0],local_20[1],local_20[2],local_20[3],local_10,1);
      }
    }
    net_tile_sync_enabled = uVar3;
    net_send_state_diff(0xff,2,0,0,0);
  }
  return;
}
#undef net_host_flag
#undef net_tile_sync_enabled
#undef local_28
#undef local_24
#undef local_20
#undef local_10
#undef local_8
