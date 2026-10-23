/*
 * Functions whose decompilation got a callee's return value wrong
 * (values left in ECX/EAX by callees declared with the wrong return type).
 */
#include "game.h"

/* 0x00452315 */
/* _strrchr is declared __thiscall without parameters in protos.h; it is the
   plain cdecl CRT strrchr. */
#define STRRCHR ((char *(__cdecl *)(const char *, int))_strrchr)

/*
 * 0x00452315: show the description of a Civilopedia topic.  A __thiscall
 * method (ECX = the Civilopedia window); the decompiler took ECX for a value
 * left over from the __chkstk call.
 */
void __thiscall pedia_load_description(void *this, int param_1)
{
  int self = (iptr)this;
  bool bVar1;
  int iVar2;
  char *pcVar3;
  size_t sVar4;
  size_t sVar5;
  int local_1110;
  char local_110c[4096];
  char *local_10c;
  char local_108[3];
  i8 local_104[228];
  
  str_clear(local_104);
  pedia_clear_links((void *)self);
  ui_pump_messages();
  switch(*(i32 *)(self + 0x118)) {
  case 1:
    param_1 = *(int *)(self + 0x65c + param_1 * 4);
    crt_strcpy(local_104,str_advance_index);
    break;
  case 2:
    param_1 = *(int *)(self + 0x980 + param_1 * 4);
    crt_strcpy(local_104,str_improvement_index);
    break;
  case 3:
    param_1 = *(int *)(self + 0xabc + param_1 * 4);
    crt_strcpy(local_104,str_wonder_index);
    break;
  case 4:
    param_1 = *(int *)(self + 0xba0 + param_1 * 4);
    crt_strcpy(local_104,str_unit_index);
    break;
  case 5:
    param_1 = *(int *)(self + 0xdd0 + param_1 * 4);
    crt_strcpy(local_104,str_terrain_index);
    break;
  case 6:
    param_1 = *(int *)(self + 0xd94 + param_1 * 4);
    crt_strcpy(local_104,str_government_index);
    break;
  case 7:
    param_1 = *(int *)(self + 0xedc + param_1 * 4);
    crt_strcpy(local_104,str_concept_descriptions);
    break;
  default:
    crt_strcpy(local_104,str_unknown_topic_group);
  }
  iVar2 = text_open_section(str_describe,local_104);
  if (iVar2 == 0) {
    local_1110 = param_1 + 1;
    local_108[2] = 0;
    bVar1 = true;
    do {
      while( true ) {
        if (local_1110 == 0) goto LAB_0045259e;
        text_read_line(1);
        _strncpy(local_108,((i8 *)&map_views_block.text_buffer),2);
        iVar2 = _strcmp(local_108,((i8 *)&pedia_desc_marker_str));
        if (iVar2 != 0) break;
        local_1110 = local_1110 + -1;
      }
    } while (local_108[0] != '@');
    bVar1 = false;
LAB_0045259e:
    if (bVar1) {
      str_clear(local_110c);
      do {
        do {
          if (!bVar1) {
            text_close_file();
            goto LAB_00452724;
          }
          if (CRT_FEOF(text_file_handle) != 0) goto LAB_00452724;
          pcVar3 = _fgets(((i8 *)&map_views_block.text_buffer),0x800,text_file_handle);
          if ((pcVar3 == (char *)0x0) || (map_views_block.text_buffer[0] == '@')) goto LAB_00452724;
        } while (map_views_block.text_buffer[0] == ';');
        local_10c = STRRCHR(((i8 *)&map_views_block.text_buffer),10);
        if (local_10c != (char *)0x0) {
          *local_10c = '\0';
          crt_strcat(((i8 *)&map_views_block.text_buffer),((i8 *)&pedia_desc_crlf_str));
        }
        sVar4 = _strlen(local_110c);
        sVar5 = _strlen(((i8 *)&map_views_block.text_buffer));
        if (0xffe < sVar4 + sVar5) {
          sVar4 = _strlen(local_110c);
          *(i8 *)((iptr)(((u8 *)&diffeng_events_section_block.diffeng_events_section + 7)) - sVar4) = 0;
        }
        crt_strcat(local_110c,((i8 *)&map_views_block.text_buffer));
        sVar4 = _strlen(local_110c);
      } while (sVar4 != 0xfff);
    }
    else {
      text_append_label(0xe);
      crt_strcpy(local_110c,((i8 *)&map_views_block.text_buffer));
    }
LAB_00452724:
    ctrl_set_text((void *)(self + 0x1a98),local_110c);
    ctrl_show_and_redraw(self + 0x1a98);
  }
  return;
}

/* 0x00475666 */
int __cdecl save_read_game(char *param_1)

{
  char cVar1;
  char *pcVar2;
  FILE *_File;
  int iVar3;
  size_t sVar4;
  size_t sVar5;
  void *pvVar6;
  i32 uVar7;
  int iVar8;
  int local_74c;
  int local_748;
  int local_744;
  int local_73c;
  int local_738;
  int local_734;
  int local_730;
  i8 local_728[0x3f0];  /* 21 tribes x 0x30 bytes read from the file */
  int local_338;
  uint local_334;
  int local_330;
  uint local_32c;
  int local_328;
  char local_324[260];
  int local_220;
  int local_21c;
  char local_218[260];
  char local_114[4];
  int local_110;
  char *local_10c;
  i8 local_108[260];
  
  local_338 = 1;
  local_110 = 0;
  local_334 = (uint)game.multiplayer;
  save_set_file_ext(0);
  crt_strcpy(local_218,param_1);
  pcVar2 = _strchr(local_218,0x2e);
  if (pcVar2 == (char *)0x0) {
    crt_strcat(local_218,((i8 *)&grey_palette_block.save_file_path));
  }
  _File = _fopen(local_218,((i8 *)&save_read_mode));
  if ((_File == (FILE *)0x0) || (iVar3 = save_read_cstr(local_324,_File), iVar3 == 0))
  goto LAB_00477352;
  iVar3 = _strcmp(str_ptr_civilize,local_324);
  if (iVar3 != 0) {
    local_338 = 1;
    goto LAB_00477352;
  }
  sVar4 = _fread(&local_32c,2,1,_File);
  if (sVar4 == 0) goto LAB_00477352;
  if (0x2c < (local_32c & 0xffff)) {
    local_338 = 4;
    goto LAB_00477352;
  }
  if (((((local_32c & 0xffff) < 0x26) || ((local_32c & 0xffff) == 0x29)) ||
      ((local_32c & 0xffff) == 0x2a)) || ((local_32c & 0xffff) == 0x2b)) {
    local_338 = 2;
    goto LAB_00477352;
  }
  ui_flush_input();
  crt_strcpy(((i8 *)&net_map_lock_slots_block.scenario_dir_path),param_1);
  local_10c = STRRCHR(((i8 *)&net_map_lock_slots_block.scenario_dir_path),0x5c);
  *local_10c = '\0';
  __chdir(((i8 *)&net_map_lock_slots_block.scenario_dir_path));
  crt_strcpy(local_108,str_game_3);
  crt_strcat(local_108,((i8 *)&lang_file_ext));
  iVar3 = file_exists(local_108);
  if (iVar3 == 0) {
    crt_strcpy(((i8 *)&main_frame_wnd_block.game_txt_path),((i8 *)&game_txt_default_name_str));
  }
  else {
    crt_strcpy(((i8 *)&main_frame_wnd_block.game_txt_path),((i8 *)&net_map_lock_slots_block.scenario_dir_path));
    crt_strcat(((i8 *)&main_frame_wnd_block.game_txt_path),str_game_4);
  }
  local_10c = STRRCHR(param_1,0x5c);
  local_10c = local_10c + 1;
  crt_strcpy(((i8 *)&net_session_block.loaded_file_name),local_10c);
  sVar4 = _strlen(((i8 *)&civ_saved_cursor_x_block.game_home_dir));
  iVar3 = __strnicmp(param_1,((i8 *)&civ_saved_cursor_x_block.game_home_dir),sVar4);
  if (iVar3 == 0) {
    sVar4 = _strlen(((i8 *)&civ_saved_cursor_x_block.game_home_dir));
    local_10c = param_1 + sVar4;
    sVar4 = _strlen(local_10c);
    sVar5 = _strlen(((i8 *)&net_session_block.loaded_file_name));
    if (sVar4 != sVar5) {
      _memset(((i8 *)&net_session_block.loaded_file_subdir),0,0x104);
      sVar4 = _strlen(local_10c);
      sVar5 = _strlen(((i8 *)&net_session_block.loaded_file_name));
      _strncpy(((i8 *)&net_session_block.loaded_file_subdir),local_10c,(sVar4 - sVar5) - 1);
    }
  }
  __chdir(((i8 *)&civ_saved_cursor_x_block.game_home_dir));
  ui_flush_input();
  rules_load(1);
  local_338 = 3;
  ui_flush_input();
  iVar3 = save_load_gpk(local_32c & 0xffff,_File);
  if (iVar3 == 0) goto LAB_00477352;
  if (game.multiplayer != 0) {
    game.game_options = game.game_options & 0xffff7fff;
  }
  if (((game.game_flags & 0x40) == 0) && ((game.game_flags & 0x80) == 0)) {
    local_220 = 0;
  }
  else {
    local_220 = 1;
  }
  if (local_220 != 0) {
    game.game_flags = game.game_flags | 0x80;
  }
  if ((game.game_flags & 0x40) != 0) {
    game.game_options = game.game_options & 0xffff7fff;
    game.reveal_map = 0;
    game.game_flags = game.game_flags & 0xffef;
  }
  game.game_flags = game.game_flags & 0xffbf;
  iVar3 = map_read(_File,0);
  if (((iVar3 != 0) ||
      (sVar4 = _fread(map_coarse[0],(int)map.quarter_w * (int)map.quarter_h,1,_File), sVar4 == 0)) ||
     (sVar4 = _fread(map_coarse[1],(int)map.quarter_w * (int)map.quarter_h,1,_File), sVar4 == 0))
  goto LAB_00477352;
  ui_flush_input();
  sVar4 = _fread(((i8 *)&landmass_table_block.landmass_table),0x400,1,_File);
  if ((sVar4 == 0) || (iVar3 = save_read_units_cities(local_32c & 0xffff,_File), iVar3 == 0))
  goto LAB_00477352;
  for (local_21c = 0; local_21c < 0x15; local_21c = local_21c + 1) {
    sVar4 = _fread(&leaders[local_21c].times_used,1,1,_File);
    if (((sVar4 == 0) || (sVar4 = _fread(&leaders[local_21c].city_name_index,1,1,_File), sVar4 == 0))
       || (sVar4 = _fread(&leaders[local_21c].female,1,1,_File), sVar4 == 0))
    goto LAB_00477352;
  }
  sVar4 = _fread(((i16 *)&map_cursor_x),2,1,_File);
  if ((sVar4 == 0) ||
     (sVar4 = _fread(((i16 *)&map_cursor_y),2,1,_File), cVar1 = game.player_civ, game.player_civ = cVar1,
     sVar4 == 0)) goto LAB_00477352;
  if (game.multiplayer == 0) {
    sVar4 = _fread(local_728,0x30,1,_File);
    if (sVar4 == 0) goto LAB_00477352;
  }
  else {
    for (local_21c = 0; game.player_civ = cVar1, local_21c < 8; local_21c = local_21c + 1) {
      if ((1 << ((byte)local_21c & 0x1f) & (uint)game.human_players) != 0) {
        game.player_civ = (byte)local_21c;
        sVar4 = _fread(local_728 + civs[(char)(byte)local_21c].tribe * 0x30,
                       0x30,1,_File);
        game.player_civ = cVar1;
        if (sVar4 == 0) goto LAB_00477352;
      }
    }
  }
  sVar4 = _fread(((i8 *)&power_graph_history_block.power_graph_history),0x4b0,1,_File);
  if ((sVar4 == 0) || (sVar4 = _fread(((i16 *)&grey_palette_block.save_layout_record),0x6a,1,_File), sVar4 == 0)) goto LAB_00477352;
  save_unpack_layout_rects();
  ui_flush_input();
  for (local_21c = 0; local_21c < 8; local_21c = local_21c + 1) {
    sVar4 = _fread(((i8 *)&map_views_block.map_view_open_flags) + local_21c * 0x3f0,2,1,_File);
    if ((((sVar4 == 0) || (sVar4 = _fread(((i8 *)&map_views_block.mapview_track_moves) + local_21c * 0x3f0,2,1,_File), sVar4 == 0))
        || (sVar4 = _fread(((i16 *)&map_views_block.map_view_center_x) + local_21c * 0x1f8,2,1,_File), sVar4 == 0)) ||
       ((sVar4 = _fread(((i16 *)&map_views_block.mapview_center_y) + local_21c * 0x1f8,2,1,_File), sVar4 == 0 ||
        (sVar4 = _fread(((i16 *)&map_views_block.mapview_zoom) + local_21c * 0x1f8,2,1,_File), sVar4 == 0))))
    goto LAB_00477352;
  }
  if ((local_220 == 0) && ((game.game_flags & 0x80) == 0)) {
    scenario_reset_params();
  }
  else {
    sVar4 = _fread(((i16 *)&prefs_game_rules_block.scenario_flags),100,1,_File);
    if (sVar4 == 0) goto LAB_00477352;
  }
  if (local_110 == 0) {
    sVar4 = _fread(((i16 *)&destroyed_civ_count_block.destroyed_civ_count),0x152,1,_File);
    if (sVar4 == 0) goto LAB_00477352;
  }
  else {
    destroyed_civs_clear();
  }
  human_civ[0] = (int)game.field_1c;
  if (((local_32c & 0xffff) < 0x29) || (game.multiplayer == 0)) {
    passwords_reset();
    civ_saved_cursor_x_block.mp_open_game = 1;
    civ_saved_cursor_x_block.mp_kill_civ_on_retire = prefs_main_menu_choice_block.prefs_mp_kill_on_retire;
    civ_saved_cursor_x_block.mp_show_human_starts = prefs_main_menu_choice_block.prefs_mp_show_human_starts;
    civ_saved_cursor_x_block.mp_chat_from_start = prefs_main_menu_choice_block.prefs_mp_chat_from_start;
    civ_saved_cursor_x_block.mp_double_production = 0;
    civ_saved_cursor_x_block.mp_double_moves = 0;
    prefs_main_menu_choice_block.prefs_mp_simultaneous_moves = 0;
    (*(byte *)&civ_saved_cursor_x_block.saved_turn_civ) = (byte)human_civ[0];
    (*(byte *)&turn_resume_civ) = (byte)human_civ[0];
  }
  else {
    _memset(((i8 *)&civ_saved_cursor_x_block.civ_saved_cursor_x),0,0x494);
    sVar4 = _fread(((i8 *)&civ_saved_cursor_x_block.civ_saved_cursor_x),0x494,1,_File);
    if (sVar4 == 0) goto LAB_00477352;
    if ((*(byte *)&civ_saved_cursor_x_block.saved_turn_civ) == 0) {
      (*(byte *)&civ_saved_cursor_x_block.saved_turn_civ) = game.turn_civ;
    }
    if ((*(byte *)&civ_saved_cursor_x_block.saved_turn_civ) == 0) {
      for (local_328 = 1; local_328 < 8; local_328 = local_328 + 1) {
        if ((1 << ((byte)local_328 & 0x1f) & (uint)game.civs_alive) != 0) {
          (*(byte *)&civ_saved_cursor_x_block.saved_turn_civ) = (byte)local_328;
          break;
        }
      }
    }
    (*(byte *)&turn_resume_civ) = (*(byte *)&civ_saved_cursor_x_block.saved_turn_civ);
    passwords_refresh_flags();
  }
  scenario_events_loaded = 0;
  sVar4 = _fread(local_114,4,1,_File);
  if ((sVar4 != 0) && (iVar3 = _strncmp(local_114,((i8 *)&save_events_tag_check_str),4), iVar3 == 0)) {
    sVar4 = _fread(&local_328,4,1,_File);
    if (sVar4 == 0) goto LAB_00477352;
    events_reset(((i8 *)&unit_types_block.scenario_events),50000);
    for (local_330 = 0; local_330 < local_328; local_330 = local_330 + 1) {
      pvVar6 = (void *)events_alloc(((i8 *)&unit_types_block.scenario_events));
      if (pvVar6 == (void *)0x0) {
        error_report(0xfffffff7,3,0,0,0);
      }
      sVar4 = _fread(pvVar6,0x1bc,1,_File);
      if (sVar4 == 0) goto LAB_00477352;
    }
    for (local_734 = unit_types_block.events_list_head; local_734 != 0; local_734 = *(int *)(local_734 + 0x1bc)) {
      if (*(int *)(local_734 + 8) != 0) {
        uVar7 = save_read_event_str(_File);
        *(i32 *)(local_734 + 8) = uVar7;
        if (*(int *)(local_734 + 8) == 0) goto LAB_00477352;
      }
      if (*(int *)(local_734 + 0x10) != 0) {
        uVar7 = save_read_event_str(_File);
        *(i32 *)(local_734 + 0x10) = uVar7;
        if (*(int *)(local_734 + 0x10) == 0) goto LAB_00477352;
      }
      if (*(int *)(local_734 + 0x14) != 0) {
        uVar7 = save_read_event_str(_File);
        *(i32 *)(local_734 + 0x14) = uVar7;
        if (*(int *)(local_734 + 0x14) == 0) goto LAB_00477352;
      }
      if (*(int *)(local_734 + 0x20) != 0) {
        uVar7 = save_read_event_str(_File);
        *(i32 *)(local_734 + 0x20) = uVar7;
        if (*(int *)(local_734 + 0x20) == 0) goto LAB_00477352;
      }
      for (local_330 = 0; (local_330 < 0x14 && (*(int *)(local_734 + 0x38 + local_330 * 4) != 0));
          local_330 = local_330 + 1) {
        uVar7 = save_read_event_str(_File);
        *(i32 *)(local_734 + 0x38 + local_330 * 4) = uVar7;
        if (*(int *)(local_734 + 0x38 + local_330 * 4) == 0) goto LAB_00477352;
      }
      if (*(int *)(local_734 + 0x88) != 0) {
        uVar7 = save_read_event_str(_File);
        *(i32 *)(local_734 + 0x88) = uVar7;
        if (*(int *)(local_734 + 0x88) == 0) goto LAB_00477352;
      }
      if (*(int *)(local_734 + 0x90) != 0) {
        uVar7 = save_read_event_str(_File);
        *(i32 *)(local_734 + 0x90) = uVar7;
        if (*(int *)(local_734 + 0x90) == 0) goto LAB_00477352;
      }
      if (*(int *)(local_734 + 0xc4) != 0) {
        uVar7 = save_read_event_str(_File);
        *(i32 *)(local_734 + 0xc4) = uVar7;
        if (*(int *)(local_734 + 0xc4) == 0) goto LAB_00477352;
      }
      if (*(int *)(local_734 + 0xcc) != 0) {
        uVar7 = save_read_event_str(_File);
        *(i32 *)(local_734 + 0xcc) = uVar7;
        if (*(int *)(local_734 + 0xcc) == 0) goto LAB_00477352;
      }
      if (*(int *)(local_734 + 0xd4) != 0) {
        uVar7 = save_read_event_str(_File);
        *(i32 *)(local_734 + 0xd4) = uVar7;
        if (*(int *)(local_734 + 0xd4) == 0) goto LAB_00477352;
      }
      if (*(int *)(local_734 + 0xdc) != 0) {
        uVar7 = save_read_event_str(_File);
        *(i32 *)(local_734 + 0xdc) = uVar7;
        if (*(int *)(local_734 + 0xdc) == 0) goto LAB_00477352;
      }
      if (*(int *)(local_734 + 0x13c) != 0) {
        uVar7 = save_read_event_str(_File);
        *(i32 *)(local_734 + 0x13c) = uVar7;
        if (*(int *)(local_734 + 0x13c) == 0) goto LAB_00477352;
      }
      if (*(int *)(local_734 + 0x140) != 0) {
        uVar7 = save_read_event_str(_File);
        *(i32 *)(local_734 + 0x140) = uVar7;
        if (*(int *)(local_734 + 0x140) == 0) goto LAB_00477352;
      }
      if (*(int *)(local_734 + 0x148) != 0) {
        uVar7 = save_read_event_str(_File);
        *(i32 *)(local_734 + 0x148) = uVar7;
        if (*(int *)(local_734 + 0x148) == 0) goto LAB_00477352;
      }
      if (*(int *)(local_734 + 0x174) != 0) {
        uVar7 = save_read_event_str(_File);
        *(i32 *)(local_734 + 0x174) = uVar7;
        if (*(int *)(local_734 + 0x174) == 0) goto LAB_00477352;
      }
      if (*(int *)(local_734 + 0x184) != 0) {
        uVar7 = save_read_event_str(_File);
        *(i32 *)(local_734 + 0x184) = uVar7;
        if (*(int *)(local_734 + 0x184) == 0) goto LAB_00477352;
      }
    }
    events_compact();
    scenario_events_loaded = 1;
  }
  ui_flush_input();
  leaders_fixup_names();
  cVar1 = game.player_civ;
  if ((local_220 == 0) && ((game.game_flags & 0x80) == 0)) {
    if (game.multiplayer == 0) {
      leaders[civs[(char)game.player_civ].tribe].leader_name =
           -leaders[civs[(char)game.player_civ].tribe].leader_name;
      if (((short *)(local_728 + 12))[0] < 0) {
        leaders[civs[(char)game.player_civ].tribe].plural =
             -leaders[civs[(char)game.player_civ].tribe].plural;
      }
      if (((short *)(local_728 + 12))[1] < 0) {
        leaders[civs[(char)game.player_civ].tribe].adjective =
             -leaders[civs[(char)game.player_civ].tribe].adjective;
      }
      for (local_21c = 0; local_21c < 7; local_21c = local_21c + 1) {
        for (local_738 = 0; local_738 < 2; local_738 = local_738 + 1) {
          if (((short *)(local_728 + 12))[local_738 + local_21c * 2 + 4] < 0) {
            leaders[civs[(char)game.player_civ].tribe].titles[local_21c][local_738]
                 = -leaders[civs[(char)game.player_civ].tribe].titles[local_21c][local_738];
          }
        }
      }
    }
    else {
      for (local_748 = 0; game.player_civ = cVar1, local_748 < 8; local_748 = local_748 + 1) {
        if ((1 << ((byte)local_748 & 0x1f) & (uint)game.human_players) != 0) {
          game.player_civ = (byte)local_748;
          leaders[civs[(char)(byte)local_748].tribe].leader_name =
               -leaders[civs[(char)(byte)local_748].tribe].leader_name;
          if (((short *)(local_728 + 12))[civs[(char)game.player_civ].tribe * 0x18] < 0) {
            leaders[civs[(char)game.player_civ].tribe].plural = -leaders[civs[(char)game.player_civ].tribe].plural;
          }
          if (((short *)(local_728 + 12))[civs[(char)game.player_civ].tribe * 0x18 + 1] < 0) {
            leaders[civs[(char)game.player_civ].tribe].adjective = -leaders[civs[(char)game.player_civ].tribe].adjective;
          }
          for (local_21c = 0; local_21c < 7; local_21c = local_21c + 1) {
            for (local_738 = 0; local_738 < 2; local_738 = local_738 + 1) {
              if (((short *)(local_728 + 12))[local_21c * 2 +
                            local_738 +
                            civs[(char)game.player_civ].tribe * 0x18 + 4] < 0)
              {
                leaders[civs[(char)game.player_civ].tribe].titles[local_21c][local_738] =
                     -leaders[civs[(char)game.player_civ].tribe].titles[local_21c][local_738];
              }
            }
          }
        }
      }
    }
  }
  else {
    for (local_748 = 1; local_748 < 8; local_748 = local_748 + 1) {
      if ((civs[local_748].flags & 0x200) == 0) {
        leaders[civs[local_748].tribe].female = 0;
      }
      else {
        leaders[civs[local_748].tribe].female = 1;
      }
      civs[local_748].leader_portrait = civs[local_748].tribe;
      if (leaders[civs[local_748].tribe].female != '\0') {
        civs[local_748].leader_portrait = civs[local_748].leader_portrait + '\x15';
      }
      if (leaders[civs[local_748].tribe].plural < 1) {
        local_74c = ~(int)leaders[civs[local_748].tribe].plural + 1;
      }
      else {
        local_74c = (int)leaders[civs[local_748].tribe].plural;
      }
      pcVar2 = (char *)label_string(local_74c);
      iVar3 = _strcmp(&civ_names[local_748].tribe_name[0],pcVar2);
      if (iVar3 == 0) {
        for (local_21c = 0; local_21c < 7; local_21c = local_21c + 1) {
          for (local_738 = 0; local_738 < 2; local_738 = local_738 + 1) {
            leaders[civs[local_748].tribe].titles[local_21c][local_738] =
                 (short)(&government_titles[local_21c].male)[local_738]   /* [0] male, [1] female */;
          }
        }
      }
      leaders[civs[local_748].tribe].leader_name =
           -leaders[civs[local_748].tribe].leader_name;
      leaders[civs[local_748].tribe].plural =
           -leaders[civs[local_748].tribe].plural;
      leaders[civs[local_748].tribe].adjective =
           -leaders[civs[local_748].tribe].adjective;
    }
  }
  ui_flush_input();
  for (local_748 = 0; local_748 < 8; local_748 = local_748 + 1) {
    for (local_730 = 0; local_730 < 0x3e; local_730 = local_730 + 1) {
      civs[local_748].units_in_production[local_730] = 0;
      civs[local_748].units_active[local_730] = 0;
    }
    for (local_744 = 0; local_744 < game.num_units; local_744 = local_744 + 1) {
      if ((units[local_744].id != 0) &&
         ((char)units[local_744].owner == local_748)) {
        civs[local_748].units_active[(uint)(byte)units[local_744].type] =
             civs[local_748].units_active[(uint)(byte)units[local_744].type] +
             '\x01';
      }
    }
    for (local_73c = 0; local_73c < game.num_cities; local_73c = local_73c + 1) {
      if (((cities[local_73c].id != 0) &&
          ((char)cities[local_73c].owner == local_748)) &&
         (-1 < (char)cities[local_73c].building)) {
        civs[local_748].units_in_production[(int)(char)cities[local_73c].building] =
             civs[local_748].units_in_production[(int)(char)cities[local_73c].building] +
             '\x01';
      }
    }
  }
  city_calc_cached_id = 0xffffffff;
  rules_load_advances(1);
  rules_load_improvements(1);
  rules_load_units(1);
  text_close_file();
  destroyed_civ_count_block.saved_layout_valid = 1;
  iVar3 = rect_width(((i32 *)&saved_screen_rect_block.saved_screen_rect));
  iVar8 = rect_width(((i32 *)&caption_small_font_block.screen_rect));
  if (iVar3 == iVar8) {
    iVar3 = rect_height(((i32 *)&saved_screen_rect_block.saved_screen_rect));
    iVar8 = rect_height(((i32 *)&caption_small_font_block.screen_rect));
    if ((iVar3 != iVar8) || (local_220 != 0)) goto LAB_0047733e;
  }
  else {
LAB_0047733e:
    destroyed_civ_count_block.saved_layout_valid = 0;
  }
  local_338 = 0;
LAB_00477352:
  if (_File != (FILE *)0x0) {
    _fclose(_File);
  }
  if ((local_338 == 0) && (game.multiplayer != local_334)) {
    civ_saved_cursor_x_block.mp_open_game = 1;
    if (local_334 == 0) {
      civ_saved_cursor_x_block.mp_double_production = 0;
      civ_saved_cursor_x_block.mp_double_moves = 0;
    }
    prefs_main_menu_choice_block.prefs_mp_simultaneous_moves = 0;
    if (game.human_players == 0) {
      if (((*(byte *)&turn_resume_civ) == 0) || ((1 << ((*(byte *)&turn_resume_civ) & 0x1f) & (uint)game.civs_alive) == 0)) {
        for (local_330 = 1; local_330 < 8; local_330 = local_330 + 1) {
          if ((1 << ((byte)local_330 & 0x1f) & (uint)game.civs_alive) != 0) {
            game.human_players = (byte)(1 << ((byte)local_330 & 0x1f));
            break;
          }
        }
      }
      else {
        game.human_players = (byte)(1 << ((*(byte *)&turn_resume_civ) & 0x1f));
      }
    }
    if (local_334 != 0) {
      game.multiplayer = (byte)local_334;
    }
  }
  return local_338;
}


/* wnd_get_style_flags is declared to return i8 but returns the whole window
   style dword (*this); callers test bit 0x200 (SWS_ATTACHED) in AH.  Read
   here directly (a call through a cast to another return type traps in
   wasm). */
#define WIN_STYLE(w) (*(uint *)(w))

/* 0x005bd566 */
void __cdecl wnd_obj_set_topmost_child(int param_1,int param_2)

{
  HWND pHVar1;
  void *this;
  
  if (param_1 != 0) {
    if (param_2 == 0) {
      *(i32 *)(param_1 + 0x10) = 0;
    }
    else {
      pHVar1 = GetParent(*(HWND *)(param_2 + 4));
      if (pHVar1 == *(HWND *)(param_1 + 4)) {
        this = (void *)GetWindowLongA(*(HWND *)(param_2 + 4),0);
        if ((WIN_STYLE(this) & 0x200) == 0) {
          dbg_log(str_window_not_sws_attached_in_mssettopmostc);
        }
        else {
          *(i32 *)(param_1 + 0x10) = *(i32 *)(param_2 + 4);
        }
      }
      else {
        dbg_log(str_window_not_a_child_in_mssettopmostchild);
      }
    }
  }
  return;
}


/* 0x005dbe88 */
LRESULT __stdcall wnd_base_wndproc(HWND param_1,uint param_2,WPARAM param_3,uint param_4)

{
  HWND pHVar1;
  HDC pHVar2;
  BOOL BVar3;
  HICON hIcon;
  LRESULT LVar4;
  void *pvVar5;
  int iVar6;
  int iVar7;
  tagRECT *ptVar8;
  tagRECT *ptVar9;
  int local_a0;
  tagPAINTSTRUCT local_98;
  int local_58;
  void *local_54;
  HDC local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  RECT local_38;
  tagRECT local_28;
  int local_18;
  tagRECT local_14;
  
  if (param_2 < 0x10) {
    if (param_2 == 0xf) {
      local_50 = BeginPaint(param_1,&local_98);
      local_54 = (void *)GetWindowLongA(param_1,0);
      BVar3 = IsIconic(param_1);
      if (BVar3 != 0) {
        GetWindowRect(param_1,&local_14);
        iVar6 = wnd_get_window(local_54);
        if (*(int *)(iVar6 + 0x20) == 0) {
          hIcon = LoadIconA((HINSTANCE)0x0,(LPCSTR)0x7f00);
          DrawIcon(local_50,0,0,hIcon);
        }
        else {
          iVar6 = wnd_get_window(local_54);
          if ((*(int *)(iVar6 + 0x18) != 0) && (gfx_palettized_display == 1)) {
            iVar6 = wnd_get_window(local_54);
            RealizePalette(*(HDC *)(iVar6 + 8));
          }
          iVar6 = wnd_get_window(local_54);
          DrawIcon(local_50,0,0,*(HICON *)(iVar6 + 0x20));
        }
        return 0;
      }
      iVar6 = wnd_get_window(local_54);
      if (*(int *)(iVar6 + 0x24) == 0) {
        iVar6 = wnd_get_window(local_54);
        if (*(int *)(iVar6 + 0x14) != 0) {
          iVar6 = wnd_get_window(local_54);
          FillRect(local_50,&local_98.rcPaint,*(HBRUSH *)(iVar6 + 0x14));
        }
      }
      else {
        iVar6 = wnd_get_window(local_54);
        local_3c = surface_width(*(void **)(iVar6 + 0x24));
        iVar6 = wnd_get_window(local_54);
        local_44 = surface_height(*(void **)(iVar6 + 0x24));
        if ((local_3c != 0) && (local_44 != 0)) {
          local_38.left = local_98.rcPaint.left;
          local_38.top = local_98.rcPaint.top;
          local_38.right = local_98.rcPaint.right;
          local_38.bottom = local_98.rcPaint.bottom;
          SetRect(&local_14,0,0,local_3c,local_44);
          for (local_58 = local_38.top / local_44; local_58 < local_38.bottom / local_44 + 1;
              local_58 = local_58 + 1) {
            for (local_4c = local_38.left / local_3c; local_4c < local_38.right / local_3c + 1;
                local_4c = local_4c + 1) {
              SetRect(&local_28,local_4c * local_3c,local_58 * local_44,
                      local_4c * local_3c + local_3c,local_58 * local_44 + local_44);
              ptVar9 = &local_28;
              ptVar8 = &local_14;
              pvVar5 = local_54;
              iVar6 = wnd_get_window(local_54);
              surface_blit_to_wnd(*(void **)(iVar6 + 0x24),pvVar5,ptVar8,ptVar9);
            }
          }
        }
      }
      iVar6 = wnd_get_window(local_54);
      if (*(int *)(iVar6 + 0x2c) != 0) {
        iVar6 = wnd_get_window(local_54);
        local_3c = surface_width(*(void **)(iVar6 + 0x2c));
        iVar6 = wnd_get_window(local_54);
        local_44 = surface_height(*(void **)(iVar6 + 0x2c));
        local_38.left = local_98.rcPaint.left;
        local_38.top = local_98.rcPaint.top;
        local_38.right = local_98.rcPaint.right;
        local_38.bottom = local_98.rcPaint.bottom;
        SetRect(&local_14,0,0,local_3c,local_44);
        iVar6 = wnd_client_height(local_54);
        iVar6 = iVar6 - local_44 >> 1;
        iVar7 = wnd_client_width(local_54);
        OffsetRect(&local_14,iVar7 - local_3c >> 1,iVar6);
        BVar3 = IntersectRect(&local_28,&local_14,&local_38);
        if (BVar3 != 0) {
          local_14.left = local_28.left;
          local_14.top = local_28.top;
          local_14.right = local_28.right;
          local_14.bottom = local_28.bottom;
          iVar6 = wnd_client_height(local_54);
          iVar6 = -(iVar6 - local_44 >> 1);
          iVar7 = wnd_client_width(local_54);
          OffsetRect(&local_14,-(iVar7 - local_3c >> 1),iVar6);
          ptVar9 = &local_28;
          ptVar8 = &local_14;
          pvVar5 = local_54;
          iVar6 = wnd_get_window(local_54);
          surface_blit_to_wnd(*(void **)(iVar6 + 0x2c),pvVar5,ptVar8,ptVar9);
        }
      }
      EndPaint(param_1,&local_98);
      return 0;
    }
    switch(param_2) {
    case 2:
      SetMenu(param_1,(HMENU)0x0);
      pvVar5 = (void *)GetWindowLongA(param_1,0);
      iVar6 = wnd_get_window(pvVar5);
      *(i32 *)(iVar6 + 0x44) = 1;
      if ((*(byte *)(iVar6 + 0x49) & 2) != 0) {
        iVar6 = 0;
        pHVar1 = GetParent(param_1);
        pvVar5 = (void *)GetWindowLongA(pHVar1,iVar6);
        local_18 = wnd_get_window(pvVar5);
        if (*(HWND *)(local_18 + 0xc) == param_1) {
          *(i32 *)(local_18 + 0xc) = 0;
        }
      }
      LVar4 = DefWindowProcA(param_1,param_2,param_3,param_4);
      return LVar4;
    case 3:
      local_54 = (void *)GetWindowLongA(param_1,0);
      if (local_54 != (void *)0x0) {
        iVar6 = wnd_get_window(local_54);
        pHVar2 = *(HDC *)(iVar6 + 8);
        iVar6 = wnd_get_window(local_54);
        ReleaseDC(*(HWND *)(iVar6 + 4),pHVar2);
        iVar6 = wnd_get_window(local_54);
        iVar7 = wnd_get_window(local_54);
        pHVar2 = GetDC(*(HWND *)(iVar7 + 4));
        *(HDC *)(iVar6 + 8) = pHVar2;
      }
      break;
    case 5:
      local_54 = (void *)GetWindowLongA(param_1,0);
      if ((local_54 != (void *)0x0) &&
         (iVar6 = wnd_get_window(local_54), *(int *)(iVar6 + 0x2c) != 0)) {
        InvalidateRect(param_1,(RECT *)0x0,1);
      }
      if (local_54 != (void *)0x0) {
        iVar6 = wnd_get_window(local_54);
        pHVar2 = *(HDC *)(iVar6 + 8);
        iVar6 = wnd_get_window(local_54);
        ReleaseDC(*(HWND *)(iVar6 + 4),pHVar2);
        iVar6 = wnd_get_window(local_54);
        iVar7 = wnd_get_window(local_54);
        pHVar2 = GetDC(*(HWND *)(iVar7 + 4));
        *(HDC *)(iVar6 + 8) = pHVar2;
      }
      break;
    case 7:
      pvVar5 = (void *)GetWindowLongA(param_1,0);
      iVar6 = wnd_get_window(pvVar5);
      if (*(int *)(iVar6 + 0xc) != 0) {
        SendMessageA(*(HWND *)(iVar6 + 0xc),0x86,1,0);
      }
      break;
    case 8:
      pvVar5 = (void *)GetWindowLongA(param_1,0);
      iVar6 = wnd_get_window(pvVar5);
      if (*(int *)(iVar6 + 0xc) != 0) {
        SendMessageA(*(HWND *)(iVar6 + 0xc),0x86,0,0);
      }
    }
  }
  else if (param_2 < 0x47) {
    if (param_2 == 0x46) {
      if ((*(byte *)(param_4 + 0x18) & 4) == 0) {
        local_54 = (void *)GetWindowLongA(param_1,0);
        wnd_get_window(local_54);
        if ((WIN_STYLE(local_54) & 0x200) != 0) {
          iVar6 = 0;
          pHVar1 = GetParent(param_1);
          pvVar5 = (void *)GetWindowLongA(pHVar1,iVar6);
          local_18 = wnd_get_window(pvVar5);
          if (((*(int *)(local_18 + 0x10) != 0) && (*(HWND *)(local_18 + 0x10) != param_1)) &&
             (BVar3 = IsWindowVisible(*(HWND *)(local_18 + 0x10)), BVar3 != 0)) {
            *(i32 *)(param_4 + 4) = *(i32 *)(local_18 + 0x10);
          }
        }
      }
    }
    else if (param_2 == 0x22) {
      pvVar5 = (void *)GetWindowLongA(param_1,0);
      iVar6 = wnd_get_window(pvVar5);
      if ((*(byte *)(iVar6 + 0x49) & 2) != 0) {
        iVar6 = 0;
        pHVar1 = GetParent(param_1);
        pvVar5 = (void *)GetWindowLongA(pHVar1,iVar6);
        local_18 = wnd_get_window(pvVar5);
        if (*(int *)(local_18 + 0xc) != 0) {
          SendMessageA(*(HWND *)(local_18 + 0xc),0x86,0,0);
        }
        SendMessageA(param_1,0x86,1,0);
        *(HWND *)(local_18 + 0xc) = param_1;
      }
    }
  }
  else {
    if (param_2 < 0xa5) {
      if ((param_2 != 0xa4) && (param_2 != 0xa1)) goto switchD_005dc5f2_caseD_4;
    }
    else {
      if (param_2 == 0x112) {
        if ((param_3 == 0xf100) || (param_3 == 0xf090)) {
          pvVar5 = (void *)GetWindowLongA(param_1,0);
          iVar6 = wnd_get_window(pvVar5);
          if ((*(byte *)(iVar6 + 0x48) & 0x20) == 0) {
            return 0;
          }
        }
        goto switchD_005dc5f2_caseD_4;
      }
      if ((param_2 != 0x201) && (param_2 != 0x204)) goto switchD_005dc5f2_caseD_4;
    }
    pvVar5 = (void *)GetWindowLongA(param_1,0);
    iVar6 = wnd_get_window(pvVar5);
    if ((*(byte *)(iVar6 + 0x49) & 2) != 0) {
      SetFocus(*(HWND *)(iVar6 + 4));
      BringWindowToTop(param_1);
    }
  }
switchD_005dc5f2_caseD_4:
  local_a0 = DefWindowProcA(param_1,param_2,param_3,param_4);
  if (param_2 == 0x84) {
    pvVar5 = (void *)GetWindowLongA(param_1,0);
    iVar6 = wnd_get_window(pvVar5);
    if ((*(int *)(iVar6 + 0x34) != 0) && (local_a0 == 1)) {
      GetWindowRect(param_1,&local_14);
      local_40 = (param_4 & 0xffff) - local_14.left;
      local_48 = (param_4 >> 0x10) - local_14.top;
      if (*(int *)(iVar6 + 0x3c) == 0) {
        local_3c = 5;
      }
      else {
        local_3c = *(int *)(iVar6 + 0x3c);
      }
      GetClientRect(param_1,&local_28);
      local_58 = 0;
      local_4c = 0;
      if (local_48 < local_3c) {
        local_58 = -1;
      }
      else {
        iVar7 = rect_height(&local_28);
        if (iVar7 - local_3c < local_48) {
          local_58 = 1;
        }
      }
      if (local_40 < local_3c) {
        local_4c = -1;
      }
      else {
        iVar7 = rect_width(&local_28);
        if (iVar7 - local_3c < local_40) {
          local_4c = 1;
        }
      }
      if (local_58 < 0) {
        if (local_40 < local_3c * 4) {
          local_4c = -1;
        }
        else {
          iVar7 = rect_width(&local_28);
          if (iVar7 + local_3c * -4 < local_40) {
            local_4c = 1;
          }
        }
        if (local_4c < 0) {
          local_a0 = 0xd;
        }
        else if (local_4c < 1) {
          local_a0 = 0xc;
        }
        else {
          local_a0 = 0xe;
        }
      }
      else if (local_58 < 1) {
        if (local_4c < 0) {
          if (local_48 < local_3c * 4) {
            local_58 = -1;
          }
          else {
            iVar7 = rect_height(&local_28);
            if (iVar7 + local_3c * -4 < local_48) {
              local_58 = 1;
            }
          }
          if (local_58 < 0) {
            local_a0 = 0xd;
          }
          else if (local_58 < 1) {
            local_a0 = 10;
          }
          else {
            local_a0 = 0x10;
          }
        }
        else if (0 < local_4c) {
          if (local_48 < local_3c * 4) {
            local_58 = -1;
          }
          else {
            iVar7 = rect_height(&local_28);
            if (iVar7 + local_3c * -4 < local_48) {
              local_58 = 1;
            }
          }
          if (local_58 < 0) {
            local_a0 = 0xe;
          }
          else if (local_58 < 1) {
            local_a0 = 0xb;
          }
          else {
            local_a0 = 0x11;
          }
        }
      }
      else {
        if (local_40 < local_3c * 4) {
          local_4c = -1;
        }
        else {
          iVar7 = rect_width(&local_28);
          if (iVar7 + local_3c * -4 < local_40) {
            local_4c = 1;
          }
        }
        if (local_4c < 0) {
          local_a0 = 0x10;
        }
        else if (local_4c < 1) {
          local_a0 = 0xf;
        }
        else {
          local_a0 = 0x11;
        }
      }
    }
    if ((*(int *)(iVar6 + 0x30) != 0) && (local_a0 == 1)) {
      GetWindowRect(param_1,&local_14);
      local_48 = (param_4 >> 0x10) - local_14.top;
      if ((*(int *)(iVar6 + 0x38) == 0) || (local_48 < *(int *)(iVar6 + 0x38))) {
        local_a0 = 2;
      }
    }
    if (local_a0 == 1) {
      SetCursor(*(HCURSOR *)(iVar6 + 0x1c));
    }
  }
  return local_a0;
}


/* 0x005eacc0 */
LRESULT __stdcall wnd_frame_wndproc(HWND param_1,uint param_2,uint param_3,HWND param_4)

{
  char cVar1;
  SHORT SVar2;
  LRESULT LVar3;
  HWND pHVar4;
  void *pvVar5;
  i32 uVar6;
  BOOL BVar7;
  uint uVar8;
  DWORD DVar9;
  int iVar10;
  tagRECT local_4c;
  HWND local_3c;
  int local_38;
  HWND local_34;
  HWND local_30;
  i32 local_2c;
  i32 local_28;
  void *local_24;
  int local_20;
  LONG local_1c;
  void *local_18;
  LONG local_14;
  HWND local_10;
  HWND local_c;
  int local_8;
  
  local_18 = (void *)GetWindowLongA(param_1,8);
  if (local_18 == (void *)0x0) {
    LVar3 = wnd_child_wndproc(param_1,param_2,param_3,param_4);
    return LVar3;
  }
  if (param_2 < 6) {
    if (param_2 == 5) {
      local_34 = (HWND)ctrl_list_find_type11_hwnd(*(i32 *)((int)local_18 + 0xb8));
      if (local_34 != (HWND)0x0) {
        SendMessageA(local_34,5,param_3,(LPARAM)param_4);
      }
      LVar3 = wnd_child_wndproc(param_1,5,param_3,param_4);
      return LVar3;
    }
    if (param_2 == 2) {
      *(i32 *)((int)local_18 + 0xb8) = 0;
      SetWindowLongA(param_1,8,0);
      LVar3 = wnd_child_wndproc(param_1,2,param_3,param_4);
      return LVar3;
    }
  }
  else if (param_2 < 0x101) {
    if (param_2 == 0x100) {
      SVar2 = GetAsyncKeyState(0x10);
      iVar10 = (int)SVar2;
      (*(i8 *)((char *)&local_2c + 1)) = (char)((ushort)SVar2 >> 8);
      local_2c = iVar10;
      if ((param_3 == 9) && ((*(i8 *)((char *)&local_2c + 1)) == '\0')) {
        cVar1 = wnd_keyboard_nav_enabled(local_18);
        if (cVar1 != '\0') {
          wnd_cycle_control_focus(local_18,0,2);
        }
      }
      else if ((param_3 == 9) && ((*(i8 *)((char *)&local_2c + 1)) != '\0')) {
        cVar1 = wnd_keyboard_nav_enabled(local_18);
        if (cVar1 != '\0') {
          wnd_cycle_control_focus(local_18,0,3);
        }
      }
      else if ((param_3 == 0xd) && ((*(i8 *)((char *)&local_2c + 1)) == '\0')) {
        if (*(int *)((int)local_18 + 0xbc) != 0) {
          uVar6 = control_get_hwnd(*(void **)((int)local_18 + 0xbc));
          button_press_animated(uVar6);
        }
      }
      else if ((param_3 == 0x1b) && ((*(i8 *)((char *)&local_2c + 1)) == '\0')) {
        if (*(int *)((int)local_18 + 0xc0) != 0) {
          uVar6 = control_get_hwnd(*(void **)((int)local_18 + 0xc0));
          button_press_animated(uVar6);
        }
      }
      else {
        uVar6 = input_map_vkey(param_3);
        wnd_dispatch_hotkey_char(local_18,uVar6);
      }
      BVar7 = IsWindow(param_1);
      if (BVar7 == 0) {
        return 0;
      }
      LVar3 = wnd_child_wndproc(param_1,0x100,param_3,param_4);
      return LVar3;
    }
    if (param_2 == 0x46) {
      if ((((WINDOWPOS *)param_4)->flags & 4) == 0) {   /* WM_WINDOWPOSCHANGING: SWP_NOZORDER */
        local_24 = (void *)GetWindowLongA(param_1,0);
        local_28 = wnd_get_window(local_24);
        if ((WIN_STYLE(local_24) & 0x200) != 0) {
          iVar10 = 0;
          pHVar4 = GetParent(param_1);
          pvVar5 = (void *)GetWindowLongA(pHVar4,iVar10);
          local_8 = wnd_get_window(pvVar5);
          local_1c = GetWindowLongA(*(HWND *)(local_8 + 4),8);
          if ((local_1c != 0) &&
             (local_38 = ctrl_list_find_type11_hwnd(*(i32 *)(local_1c + 0xb8)), local_38 != 0)) {
            ((WINDOWPOS *)param_4)->hwndInsertAfter = (HWND)(iptr)local_38;
            LVar3 = DefWindowProcA(param_1,0x46,param_3,(LPARAM)param_4);
            return LVar3;
          }
        }
      }
      LVar3 = wnd_child_wndproc(param_1,0x46,param_3,param_4);
      return LVar3;
    }
  }
  else {
    if (param_2 < 0x116) {
      if (param_2 < 0x114) {
        if (param_2 != 0x111) goto LAB_005eb241;
        uVar8 = param_3 >> 0x10;
        if (uVar8 < 0x301) {
          if (uVar8 == 0x300) {
            local_10 = param_4;
            DVar9 = GetClassLongA(param_4,-0x12);
            local_20 = DVar9 - 4;
            local_14 = GetWindowLongA(local_10,local_20);
            edit_fire_change_callback(local_14);
          }
          else if (uVar8 == 1) {
            local_30 = param_4;
            SendMessageA(param_4,0x4c8,param_3,(LPARAM)param_4);
          }
          else {
            if (uVar8 != 2) goto LAB_005eb1df;
            local_30 = param_4;
            SendMessageA(param_4,0x4c8,param_3,(LPARAM)param_4);
          }
        }
        else {
          if (uVar8 != 0x501) {
LAB_005eb1df:
            LVar3 = wnd_child_wndproc(param_1,0x111,param_3,param_4);
            return LVar3;
          }
          local_10 = param_4;
          DVar9 = GetClassLongA(param_4,-0x12);
          local_20 = DVar9 - 4;
          local_14 = GetWindowLongA(local_10,local_20);
          edit_fire_maxtext_callback(local_14);
        }
      }
      else {
        iVar10 = wnd_get_window(local_18);
        if (((*(byte *)(iVar10 + 0x48) & 0x80) != 0) ||
           (iVar10 = wnd_get_window(local_18), (*(byte *)(iVar10 + 0x49) & 1) != 0)) {
          LVar3 = wnd_child_wndproc(param_1,param_2,param_3,param_4);
          return LVar3;
        }
        local_c = param_4;
        scrollbar_hwnd_handle_msg(param_4,param_2,param_3,param_4);
      }
      return 0;
    }
    if (param_2 == 0x216) {
      local_24 = (void *)GetWindowLongA(param_1,0);
      local_28 = wnd_get_window(local_24);
      if ((WIN_STYLE(local_24) & 0x200) != 0) {
        iVar10 = 0;
        pHVar4 = GetParent(param_1);
        pvVar5 = (void *)GetWindowLongA(pHVar4,iVar10);
        local_8 = wnd_get_window(pvVar5);
        local_1c = GetWindowLongA(*(HWND *)(local_8 + 4),8);
        if (((local_1c != 0) &&
            (local_3c = (HWND)ctrl_list_find_type11_hwnd(*(i32 *)(local_1c + 0xb8)), local_3c != (HWND)0x0)
            ) && (BVar7 = IsWindowVisible(local_3c), BVar7 != 0)) {
          iVar10 = GetSystemMetrics(4);
          GetWindowRect(local_3c,&local_4c);
          local_2c = rect_width(param_4);
          if (local_4c.top - iVar10 <= ((RECT *)param_4)->top) {   /* WM_MOVING */
            ((RECT *)param_4)->top = local_4c.top - iVar10;
            ((RECT *)param_4)->bottom = (local_4c.top - iVar10) + local_2c;
          }
        }
      }
      LVar3 = wnd_child_wndproc(param_1,0x216,param_3,param_4);
      return LVar3;
    }
  }
LAB_005eb241:
  LVar3 = wnd_child_wndproc(param_1,param_2,param_3,param_4);
  return LVar3;
}


/* 0x0048aa24 */
uint __cdecl game_turn_start_popups(void)

{
  uint uVar1;
  int iVar2;
  i32 uVar3;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_10 = -1;
  uVar1 = (uint)(short)game.turn;
  if (((1 < (int)uVar1) &&
      (uVar1 = ((short)game.turn + -1) / 0x32, ((short)game.turn + -1) % 0x32 == 0)) &&
     (((*(i8 *)((char *)&game.game_options + 2)) & 0x10) != 0)) {
    local_c = -1;
    for (local_14 = 0; local_14 < game.num_cities; local_14 = local_14 + 1) {
      if ((cities[local_14].id != 0) &&
         ((char)cities[local_14].owner == human_civ[0])) {
        local_8 = (int)(char)cities[local_14].size;
        iVar2 = city_has_improvement(local_14,1);
        if (iVar2 != 0) {
          local_8 = local_8 << 1;
        }
        if (local_8 == 1 || local_8 + -1 < 0) {
          local_8 = 0;
        }
        else {
          iVar2 = _rand();
          local_8 = iVar2 % local_8;
        }
        if (local_c < local_8) {
          local_c = local_8;
          local_10 = local_14;
        }
      }
    }
    uVar3 = civ_name_plural(human_civ[0]);
    text_set_string_arg(0,uVar3);
    text_clear();
    text_append_year((int)game.year);
    text_set_string_arg(2,((i8 *)&map_views_block.text_buffer));
    text_clear();
    if (local_10 < 0) {
      text_append_label(0xe);
    }
    else {
      text_append(cities[local_10].name);
      mapview_center_on(((i8 *)&map_views_block.map_views),(int)cities[local_10].x,
                         (int)cities[local_10].y);
    }
    text_set_string_arg(1,((i8 *)&map_views_block.text_buffer));
    uVar1 = popup_game_with_sprite(str_counciltime,((i8 *)&popup_info_icon_sprite),0);
    if (uVar1 == 0) {
      council_show(human_civ[0],0);   /* void; result left in EAX is garbage */
    }
  }
  if (((*(i8 *)((char *)&game.game_options + 1)) & 1) != 0) {
    if (game.turn == 1) {
      popup_file_with_sprite((*(i8 * *)str_ptr_labels_rest),str_firstmove,((i8 *)&tutorial_icon_sprite_block.tutorial_icon_sprite),0);
    }
    if ((game.turn == 0x14) || (game.turn == 0x3c)) {
      popup_file_with_sprite((*(i8 * *)str_ptr_labels_rest),str_help1,((i8 *)&tutorial_icon_sprite_block.tutorial_icon_sprite),0);
    }
    if ((game.turn == 0x28) || (game.turn == 0x50)) {
      popup_file_with_sprite((*(i8 * *)str_ptr_labels_rest),str_help2,((i8 *)&tutorial_icon_sprite_block.tutorial_icon_sprite),0);
    }
    if ((((civs[human_civ[0]].num_cities == 1) &&
         (2 < civs[human_civ[0]].total_city_size)) && (game.turn == 0x23)) &&
       ((civs[human_civ[0]].units_active[0] == '\0' &&
        (civs[human_civ[0]].units_in_production[0] == '\0')))) {
      uVar1 = city_find_nearest((int)map.width / 2,(int)map.height / 2,human_civ[0],0xffffffff
                                 ,0xffffffff);
      if (-1 < (int)uVar1) {
        text_set_string_arg(0,cities[uVar1].name);
        popup_text_with_city_noflags((*(i8 * *)str_ptr_labels_rest),str_onecity,uVar1);
        uVar1 = (int)(short)game.turn - 0x19;
        civs[human_civ[0]].last_city_turn = (short)uVar1;
      }
    }
    else {
      uVar1 = (int)(short)game.turn - (int)civs[human_civ[0]].last_city_turn;
      if ((0x18 < (int)uVar1) &&
         ((uVar1 = (uint)civs[human_civ[0]].num_cities, (int)uVar1 < 6 &&
          (uVar1 = human_civ[0] * 0x165, civs[human_civ[0]].units_active[0] == '\0')))) {
        popup_file_with_sprite((*(i8 * *)str_ptr_labels_rest),str_expand0,((i8 *)&tutorial_icon_sprite_block.tutorial_icon_sprite),0);
        uVar1 = (uint)game.turn;
        civs[human_civ[0]].last_city_turn = game.turn;
      }
    }
  }
  return uVar1;
}


/* 0x004eb4ed */
int __cdecl city_recalc(int param_1,int param_2)

{
  int iVar1;
  
  if (param_1 == -1) {
    iVar1 = 0;
  }
  else if (param_2 == 0) {
    iVar1 = main_menu_block.city_happy_count - main_menu_block.city_unhappy_count;
  }
  else {
    city_calc_cached_id = param_1;
    city_calc_tile_flags(param_1);
    city_calc_capital_link(param_1);
    city_calc_unit_support(param_1);
    /* city_calc_all_stats, which is declared void but returns its last call's
       (city_calc_trade_happiness's) int: */
    city_assign_workers(param_1);
    city_count_food_routes(param_1);
    city_fill_specialists(param_1);
    city_calc_shields_pollution(param_1);
    iVar1 = city_calc_trade_happiness(param_1);
  }
  return iVar1;
}


/* 0x004efd44 */
int __cdecl city_process_pollution(int param_1)

{
  char cVar1;
  int iVar2;
  i32 uVar3;
  int iVar4;
  uint uVar5;
  int local_20;
  int local_1c;
  int local_14;
  
  cVar1 = cities[param_1].owner;
  local_14 = (int)((uint)(byte)civs[cVar1].num_advances * (uint)game.difficulty) >> 1;
  if (((game.game_flags & 0x80) != 0) && ((prefs_game_rules_block.scenario_flags[0] & 0x40) != 0)) {
    local_14 = 0;
    main_menu_block.city_pollution = 0;
  }
  iVar2 = city_has_improvement(param_1,0x1d);
  if (iVar2 != 0) {
    for (; 0xff < local_14; local_14 = local_14 / 2) {
    }
  }
  if (-local_14 == -0xff || -local_14 + 0xff < 0) {
    local_1c = 0;
  }
  else {
    local_1c = _rand();
    local_1c = local_1c % (0x100 - local_14);
  }
  if (local_1c < main_menu_block.city_pollution * 2) {
    iVar2 = _rand();
    uVar3 = map_wrap_x((int)cities[param_1].x +
                               (int)(char)(((i8 *)&dir_dy_table_block.city_tile_dx_table))[iVar2 % 0x14]);
    iVar2 = (int)cities[param_1].y +
            (int)(char)(((i8 *)&dir_dy_table_block.city_tile_dy_table))[iVar2 % 0x14];
    iVar4 = map_in_bounds(uVar3,iVar2);
    if (iVar4 != 0) {
      uVar5 = tile_improvements(uVar3,iVar2);
      if ((uVar5 & 0x82) == 0) {
        iVar4 = tile_is_ocean(uVar3,iVar2);
        if (iVar4 == 0) {
          tile_add_pollution(uVar3,iVar2);
          iVar4 = tile_visible_to(uVar3,iVar2,human_civ[0]);
          if (iVar4 != 0) {
            mapview_center_on(((i8 *)&map_views_block.map_views),uVar3,iVar2);
            if ((game.message_options & 0x100) == 0) {
              city_notify_dialog_ex(str_pollution,param_1,0,0);
            }
          }
        }
      }
    }
  }
  iVar2 = param_1 * 0xb;
  if ((cities[param_1].flags & 1) != 0) {
    iVar4 = city_has_improvement(param_1,0x15);
    iVar2 = 0;
    if (iVar4 != 0) {
      iVar2 = civ_has_advance((int)cVar1,0x20);
      if (iVar2 == 0) {
        iVar2 = 5 - (uint)game.difficulty;
        if (iVar2 < 1) {
          local_20 = 0;
        }
        else {
          local_20 = _rand();
          iVar2 = local_20 / (int)(6 - (uint)game.difficulty);
          local_20 = local_20 % (int)(6 - (uint)game.difficulty);
        }
        if (local_20 == 0) {
          iVar2 = tile_visible_to((int)cities[param_1].x,
                                     (int)cities[param_1].y,human_civ[0]);
          if (iVar2 != 0) {
            mapviews_ensure_visible((int)cities[param_1].x,
                               (int)cities[param_1].y,
                               (int)(char)cities[param_1].owner);
          }
          map_animate_nuke((int)cities[param_1].x,
                             (int)cities[param_1].y);
          nuclear_blast((int)cities[param_1].x,
                             (int)cities[param_1].y);
          city_set_improvement(param_1,0x15,0);
          iVar2 = (int)civ_saved_cursor_x_block.autoplay_active;
          if (iVar2 == 0) {
            /* city_notify_dialog is declared void but returns city_notify_dialog_ex's int:
               it is city_notify_dialog_ex(a, b, 0, c) */
            iVar2 = city_notify_dialog_ex(str_chernobyl,param_1,0,((i32 *)&caption_close_button_sprite_block.city_notify_sprite));
          }
        }
      }
    }
  }
  return iVar2;
}


/* 0x0058f040 */
uint __cdecl unit_enter_hut(int param_1)

{
  bool bVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  i32 uVar8;
  int iVar9;
  uint uVar10;
  i32 local_60;
  uint local_50;
  int local_4c;
  int local_48;
  int local_40;
  i32 local_3c;
  i32 local_38;
  i32 local_28;
  int local_20;
  i32 local_14;
  int local_10;
  i32 local_c;
  int local_8;
  
  bVar2 = units[param_1].owner;
  uVar3 = (uint)(char)bVar2;
  iVar4 = (int)units[param_1].x;
  uVar5 = (uint)units[param_1].y;
  local_50 = uVar5;
  if ((uVar3 != 0) &&
     (local_50 = (int)(char)unit_types[(uint)(byte)units[param_1].type].domain,
     (int)(char)unit_types[(uint)(byte)units[param_1].type].domain == 0)) {
    city_find_nearest(iVar4,uVar5,0xffffffff,0xffffffff,0xffffffff);
    iVar6 = _rand();
    local_50 = iVar6 % 5;
    if ((((((1 << (bVar2 & 0x1f) & (uint)game.human_players) == 0) || (iVar6 = _rand(), iVar6 % 3 == 0))
         && ((civs[uVar3].num_cities != 0 &&
             (iVar6 = tile_landmass(iVar4,uVar5),
             civs[uVar3].continent_cities[iVar6] == '\0')))) &&
        (((civs[uVar3].continent_flags[iVar6] & 0x7f) == 0 || (0xc < advisor_window_block.nearest_city_dist)))) &&
       (civs[uVar3].continent_cities[iVar6] == '\0')) {
      local_50 = 0;
    }
LAB_0058f1bc:
    switch(local_50) {
    case 0:
      if (advisor_window_block.nearest_city_dist < 4) {
        local_50 = 1;
        goto LAB_0058f1bc;
      }
      if ((civs[uVar3].num_cities == 0) && (game.turn < 0x32)) {
        local_8 = 0;
        for (param_1 = 0; param_1 < game.num_units; param_1 = param_1 + 1) {
          if (((units[param_1].id != 0) &&
              (unit_types[(uint)(byte)units[param_1].type].role == '\x05')) &&
             (units[param_1].home_city == -1)) {
            local_8 = local_8 + 1;
          }
        }
        if (1 < local_8) {
          local_50 = 1;
          goto LAB_0058f1bc;
        }
      }
      iVar6 = tile_owner_or_fertility(iVar4,uVar5);
      if (0xb < iVar6) {
        if (unit_sound_editor_window_block.unit_move_by_local_human != '\0') {
          popup_game_with_sprite(str_surprisetribe,((i8 *)&popup_info_icon_sprite),0);
        }
        iVar6 = city_create(iVar4,uVar5,uVar3);
        if (999 < game.year) {
          iVar9 = _rand();
          bVar2 = (byte)(iVar9 >> 0x1f);
          cities[iVar6].size =
               ((((byte)iVar9 ^ bVar2) - bVar2 & 3 ^ bVar2) - bVar2) + '\x01';
          city_set_improvement(iVar6,4,1);
          uVar3 = _rand();
          uVar7 = (int)uVar3 >> 0x1f;
          if (((uVar3 ^ uVar7) - uVar7 & 1 ^ uVar7) == uVar7) {
            city_set_improvement(iVar6,5,1);
          }
          iVar9 = _rand();
          if (iVar9 % 3 == 0) {
            city_set_improvement(iVar6,3,1);
          }
          uVar3 = _rand();
          uVar7 = (int)uVar3 >> 0x1f;
          if (((uVar3 ^ uVar7) - uVar7 & 3 ^ uVar7) == uVar7) {
            city_set_improvement(iVar6,6,1);
          }
        }
        if (unit_sound_editor_window_block.unit_move_by_local_human == '\0') {
          return 0;
        }
        map_redraw_neighbors_all_views(iVar4,uVar5);
        uVar3 = net_send_message(0x75,0xff,iVar4,uVar5,0,0,0,0,0,0);
        if (iVar6 < 0) {
          return uVar3;
        }
        city_window_open(((i8 *)&city_window_block.city_window),iVar6);   /* void: the caller ignores our result */
        return uVar3;
      }
      local_50 = 5;
      goto LAB_0058f1bc;
    case 1:
      if (unit_sound_editor_window_block.unit_move_by_local_human != '\0') {
        popup_game_with_sprite(str_surprisemercs,((i8 *)&popup_info_icon_sprite),0);
      }
      local_14 = 0x13;
      if (game.advance_known_by[11] == '\0') {
        iVar6 = _rand();
        if (iVar6 % 3 == 0) {
          local_14 = 0x10;
        }
        else {
          local_14 = 0xf;
        }
        if (game.advance_known_by[64] != '\0') {
          uVar7 = _rand();
          uVar10 = (int)uVar7 >> 0x1f;
          if (((uVar7 ^ uVar10) - uVar10 & 1 ^ uVar10) != uVar10) {
            local_14 = 0x11;
          }
        }
      }
      if (game.advance_known_by[55] != '\0') {
        local_14 = 0x12;
      }
      if (game.advance_known_by[42] != '\0') {
        local_14 = 0x14;
      }
      if (game.advance_known_by[17] != '\0') {
        local_14 = 0xb;
      }
      local_c = 8;
      if (game.advance_known_by[34] == '\0') {
        local_c = 7;
      }
      if (game.advance_known_by[35] == '\0') {
        local_c = 5;
      }
      if (game.advance_known_by[39] == '\0') {
        local_c = 4;
      }
      uVar7 = _rand();
      uVar10 = (int)uVar7 >> 0x1f;
      if (((uVar7 ^ uVar10) - uVar10 & 1 ^ uVar10) == uVar10) {
        local_60 = local_14;
      }
      else {
        local_60 = local_c;
      }
      iVar6 = unit_create(local_60,uVar3,iVar4,uVar5);
      if ((unit_sound_editor_window_block.unit_move_by_local_human == '\0') && ((*(uint *)&human_civ) != uVar3)) {
        local_50 = uVar3;
        if (-1 < iVar6) {
          local_50 = iVar6 * 0x20;
          *((i8 *)&units[0].home_city + local_50) = -1;   /* local_50 is a byte offset (unit index * 0x20) */
        }
      }
      else {
        map_redraw_neighbors_all_views(iVar4,uVar5);
        local_50 = net_send_message(0x75,0xff,iVar4,uVar5,0,0,0,0,0,0);
      }
      break;
    case 2:
      local_20 = 0x32;
      iVar4 = _rand();
      if (iVar4 % 3 == 0) {
        iVar4 = _rand();
        if ((int)((iVar4 % 10 - (uint)game.difficulty) + 2) < 5) {
          local_20 = 0x19;
        }
        else {
          local_20 = 100;
        }
      }
      if (1000 < game.year) {
        local_20 = local_20 << 1;
      }
      civs[uVar3].gold = civs[uVar3].gold + local_20;
      text_set_number_arg(0,local_20);
      if (unit_sound_editor_window_block.unit_move_by_local_human != '\0') {
        popup_game_with_sprite(str_surprisemetals,((i8 *)&popup_info_icon_sprite),0);
      }
      if ((*(uint *)&human_civ) != uVar3) {
        return uVar3;
      }
      status_draw_info(1);   /* void */
      return uVar3;
    case 3:
      if ((advisor_window_block.nearest_city_dist < 4) ||
         ((civs[uVar3].num_cities == 0 && (game.turn < 0x32)))) {
        local_50 = 1;
        goto LAB_0058f1bc;
      }
      if (((1 << (bVar2 & 0x1f) & (uint)game.human_players) == 0) &&
         ((byte)game.power_rank[uVar3] < (byte)game.power_rank[game.field_139])) {
        uVar7 = _rand();
        uVar10 = (int)uVar7 >> 0x1f;
        if ((int)(((uVar7 ^ uVar10) - uVar10 & 7 ^ uVar10) - uVar10) < (int)(uint)game.difficulty) {
          local_50 = 0;
          goto LAB_0058f1bc;
        }
      }
      bVar1 = false;
      if (game.barbarian_activity < 3) {
        if (game.turn < 0x1e) {
LAB_0058f87c:
          city_find_nearest(iVar4,uVar5,uVar3,0xffffffff,0xffffffff);
          iVar6 = tile_landmass(iVar4,uVar5);
          if ((civs[uVar3].continent_cities[iVar6] != '\0') && (advisor_window_block.nearest_city_dist < 0x18)) {
            if (unit_sound_editor_window_block.unit_move_by_local_human == '\0') {
              return 0;
            }
            uVar3 = popup_game_with_sprite(str_surprisenothing,((i8 *)&popup_info_icon_sprite),0);
            return uVar3;
          }
        }
        else if (game.turn < 0x32) {
          uVar7 = _rand();
          uVar10 = (int)uVar7 >> 0x1f;
          if (((uVar7 ^ uVar10) - uVar10 & 1 ^ uVar10) == uVar10) goto LAB_0058f87c;
        }
      }
      if (0x31 < game.turn) {
        if (0x4a < game.turn) goto LAB_0058f939;
        uVar7 = _rand();
        uVar10 = (int)uVar7 >> 0x1f;
        if (((uVar7 ^ uVar10) - uVar10 & 1 ^ uVar10) != uVar10) goto LAB_0058f939;
      }
      bVar1 = true;
LAB_0058f939:
      uVar7 = 0;
      if (unit_sound_editor_window_block.unit_move_by_local_human != '\0') {
        uVar7 = popup_game_with_sprite(str_surprisebarb,((i8 *)&popup_info_icon_sprite),0);
      }
      local_10 = 0;
      do {
        if (7 < local_10) {
          return uVar7;
        }
        uVar7 = game.turn + local_10 >> 0x1f;
        iVar6 = ((game.turn + local_10 ^ uVar7) - uVar7 & 7 ^ uVar7) - uVar7;
        uVar8 = map_wrap_x((char)(((i8 *)&dir_dx_table_block.dir_dx_table))[iVar6] + iVar4);
        iVar6 = (int)(char)(((i8 *)&dir_dy_table_block.dir_dy_table))[iVar6] + uVar5;
        iVar9 = map_in_bounds(uVar8,iVar6);
        if ((((iVar9 != 0) && (iVar9 = tile_unit_owner(uVar8,iVar6), iVar9 < 0)) &&
            (iVar9 = tile_city_owner(uVar8,iVar6), iVar9 < 0)) &&
           (iVar9 = tile_is_ocean(uVar8,iVar6), iVar9 == 0)) {
          bVar2 = tile_terrain(uVar8,iVar6);
          local_28 = 5;
          local_3c = 0xf;
          if (game.advance_known_by[51] != '\0') {
            local_28 = 7;
            local_3c = 0x13;
          }
          if (game.advance_known_by[unit_types[22].prerequisite] != '\0') {
            local_28 = 0xb;
            local_3c = 0x15;
          }
          if (game.advance_known_by[34] != '\0') {
            local_28 = 8;
            local_3c = 9;
          }
          if ((char)terrain_types[(uint)bVar2].move_cost < '\x03') {
            local_38 = local_3c;
          }
          else {
            local_38 = local_28;
          }
          uVar7 = unit_create(local_38,0,uVar8,iVar6);
          if (-1 < (int)uVar7) {
            iVar9 = tile_at(iVar4,uVar5);
            units[uVar7].visibility = *(byte *)(iVar9 + 4) | units[uVar7].visibility;
            map_redraw_tile_all_views(uVar8,iVar6);
            uVar7 = (uint)game.multiplayer;
            if (2 < game.multiplayer) {
              uVar7 = net_send_message(0x72,0xff,uVar8,iVar6,0,0,0,0,0,0);
            }
          }
          if (bVar1) {
            return uVar7;
          }
        }
        uVar7 = int_clamp(4 - civs[uVar3].num_cities,1,4);
        local_10 = local_10 + uVar7;
      } while( true );
    case 4:
      if ((game.turn == 0) || (iVar6 = civ_has_advance(uVar3,0x26), iVar6 != 0)) {
        local_50 = 2;
      }
      else {
        local_40 = 0;
        local_4c = _rand();
        local_4c = local_4c % 100;
        do {
          iVar6 = civ_can_research_advance(uVar3,local_4c);
          if (iVar6 == 0) {
            uVar7 = (local_4c + 1) / 100;
            local_4c = (local_4c + 1) % 100;
          }
          else {
            if (unit_sound_editor_window_block.unit_move_by_local_human != '\0') {
              popup_game_with_sprite(str_surprisescrolls,((i8 *)&popup_info_icon_sprite),0);
            }
            civ_give_advance(uVar3,local_4c,uVar3,0,0);   /* void */
            local_4c = -1;
          }
          local_40 = local_40 + 1;
        } while ((local_40 < 999) && (-1 < local_4c));
        if (local_4c < 0) {
          return uVar7;
        }
        local_50 = 0;
      }
      goto LAB_0058f1bc;
    case 5:
      if (game.advance_known_by[28] == '\0') {
        local_48 = 0;
        for (param_1 = 0; param_1 < game.num_units; param_1 = param_1 + 1) {
          if ((((units[param_1].id != 0) &&
               ((int)(char)units[param_1].owner == uVar3)) &&
              (unit_types[(uint)(byte)units[param_1].type].role == '\x05')) &&
             (units[param_1].home_city == -1)) {
            local_48 = local_48 + 1;
          }
        }
        if (local_48 <= (int)civs[uVar3].num_cities >> 3) {
          if (unit_sound_editor_window_block.unit_move_by_local_human != '\0') {
            popup_game_with_sprite(str_surprisenomads,((i8 *)&popup_info_icon_sprite),0);
          }
          iVar6 = unit_create(0,uVar3,iVar4,uVar5);
          if (-1 < iVar6) {
            units[iVar6].home_city = 0xff;
          }
          if (unit_sound_editor_window_block.unit_move_by_local_human == '\0') {
            return 0;
          }
          map_redraw_neighbors_all_views(iVar4,uVar5);
          uVar3 = net_send_message(0x75,0xff,iVar4,uVar5,0,0,0,0,0,0);
          return uVar3;
        }
        local_50 = 4;
      }
      else {
        local_50 = 2;
      }
      goto LAB_0058f1bc;
    default:
      break;
    }
  }
  return local_50;
}

