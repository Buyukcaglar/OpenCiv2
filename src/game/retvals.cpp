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
void __thiscall pedia_load_description(void *self, int topic2)
{
  int obj_addr = (iptr)self;
  bool section_missing;
  int found;
  char *line;
  size_t cur_len;
  size_t line_len;
  int remaining;
  char desc_text[4096];
  char *newline_ptr;
  char marker[3];
  i8 section_name[228];
  
  str_clear((iptr)section_name);
  pedia_clear_links((WindowObjectView *)obj_addr);
  ui_pump_messages();
  switch(*(i32 *)(obj_addr + 0x118)) {
  case 1:
    topic2 = *(int *)(obj_addr + 0x65c + topic2 * 4);
    crt_strcpy(section_name,str_advance_index);
    break;
  case 2:
    topic2 = *(int *)(obj_addr + 0x980 + topic2 * 4);
    crt_strcpy(section_name,str_improvement_index);
    break;
  case 3:
    topic2 = *(int *)(obj_addr + 0xabc + topic2 * 4);
    crt_strcpy(section_name,str_wonder_index);
    break;
  case 4:
    topic2 = *(int *)(obj_addr + 0xba0 + topic2 * 4);
    crt_strcpy(section_name,str_unit_index);
    break;
  case 5:
    topic2 = *(int *)(obj_addr + 0xdd0 + topic2 * 4);
    crt_strcpy(section_name,str_terrain_index);
    break;
  case 6:
    topic2 = *(int *)(obj_addr + 0xd94 + topic2 * 4);
    crt_strcpy(section_name,str_government_index);
    break;
  case 7:
    topic2 = *(int *)(obj_addr + 0xedc + topic2 * 4);
    crt_strcpy(section_name,str_concept_descriptions);
    break;
  default:
    crt_strcpy(section_name,str_unknown_topic_group);
  }
  found = text_open_section((iptr)str_describe,(iptr)section_name);
  if (found == 0) {
    remaining = topic2 + 1;
    marker[2] = 0;
    section_missing = true;
    do {
      while( true ) {
        if (remaining == 0) goto read_text_lines;
        text_read_line(1);
        _strncpy(marker,((i8 *)&map_views_block.text_buffer),2);
        found = _strcmp(marker,((i8 *)&pedia_desc_marker_str));
        if (found != 0) break;
        remaining = remaining + -1;
      }
    } while (marker[0] != '@');
    section_missing = false;
read_text_lines:
    if (section_missing) {
      str_clear((iptr)desc_text);
      do {
        do {
          if (!section_missing) {
            text_close_file();
            goto set_control_text;
          }
          if (CRT_FEOF(text_file_handle) != 0) goto set_control_text;
          line = _fgets(((i8 *)&map_views_block.text_buffer),0x800,text_file_handle);
          if ((line == (char *)0x0) || (map_views_block.text_buffer[0] == '@')) goto set_control_text;
        } while (map_views_block.text_buffer[0] == ';');
        newline_ptr = STRRCHR(((i8 *)&map_views_block.text_buffer),10);
        if (newline_ptr != (char *)0x0) {
          *newline_ptr = '\0';
          crt_strcat(((i8 *)&map_views_block.text_buffer),((i8 *)&pedia_desc_crlf_str));
        }
        cur_len = _strlen(desc_text);
        line_len = _strlen(((i8 *)&map_views_block.text_buffer));
        if (0xffe < cur_len + line_len) {
          cur_len = _strlen(desc_text);
          *(i8 *)((iptr)(((u8 *)&diffeng_events_section_block.diffeng_events_section + 7)) - cur_len) = 0;
        }
        crt_strcat(desc_text,((i8 *)&map_views_block.text_buffer));
        cur_len = _strlen(desc_text);
      } while (cur_len != 0xfff);
    }
    else {
      text_append_label(0xe);
      crt_strcpy(desc_text,((i8 *)&map_views_block.text_buffer));
    }
set_control_text:
    ctrl_set_text((ControlTextView *)(obj_addr + 0x1a98),(iptr)desc_text);
    ctrl_show_and_redraw((Control *)(obj_addr + 0x1a98));
  }
  return;
}

/* 0x00475666 */
int __cdecl save_read_game(char *path)

{
  char saved_player_civ;
  char *dot_ptr;
  FILE *_File;
  int result;
  size_t count_read;
  size_t name_len;
  void *event;
  i32 event_str;
  int screen_h;
  int title_label;
  int civ;
  int unit_idx;
  int city_idx;
  int gender;
  int event_node;
  int type_idx;
  i8 leader_buf[0x3f0];  /* 21 tribes x 0x30 bytes read from the file */
  int status;
  uint saved_multiplayer;
  int event_idx;
  uint version;
  int event_count2;
  char header_str[260];
  int is_scenario;
  int idx;
  char save_path[260];
  char events_tag[4];
  int skip_destroyed;
  char *slash_ptr;
  i8 game_txt_path2[260];
  
  status = 1;
  skip_destroyed = 0;
  saved_multiplayer = (uint)game.multiplayer;
  save_set_file_ext(0);
  crt_strcpy(save_path,path);
  dot_ptr = _strchr(save_path,0x2e);
  if (dot_ptr == (char *)0x0) {
    crt_strcat(save_path,((i8 *)&grey_palette_block.save_file_path));
  }
  _File = _fopen(save_path,((i8 *)&save_read_mode));
  if ((_File == (FILE *)0x0) || (result = save_read_cstr((iptr)header_str,(iptr)_File), result == 0))
  goto close_file;
  result = _strcmp(str_ptr_civilize,header_str);
  if (result != 0) {
    status = 1;
    goto close_file;
  }
  count_read = _fread(&version,2,1,_File);
  if (count_read == 0) goto close_file;
  if (0x2c < (version & 0xffff)) {
    status = 4;
    goto close_file;
  }
  if (((((version & 0xffff) < 0x26) || ((version & 0xffff) == 0x29)) ||
      ((version & 0xffff) == 0x2a)) || ((version & 0xffff) == 0x2b)) {
    status = 2;
    goto close_file;
  }
  ui_flush_input();
  crt_strcpy(((i8 *)&net_map_lock_slots_block.scenario_dir_path),path);
  slash_ptr = STRRCHR(((i8 *)&net_map_lock_slots_block.scenario_dir_path),0x5c);
  *slash_ptr = '\0';
  __chdir(((i8 *)&net_map_lock_slots_block.scenario_dir_path));
  crt_strcpy(game_txt_path2,str_game_3);
  crt_strcat(game_txt_path2,((i8 *)&lang_file_ext));
  result = file_exists((iptr)game_txt_path2);
  if (result == 0) {
    crt_strcpy(((i8 *)&main_frame_wnd_block.game_txt_path),((i8 *)&game_txt_default_name_str));
  }
  else {
    crt_strcpy(((i8 *)&main_frame_wnd_block.game_txt_path),((i8 *)&net_map_lock_slots_block.scenario_dir_path));
    crt_strcat(((i8 *)&main_frame_wnd_block.game_txt_path),str_game_4);
  }
  slash_ptr = STRRCHR(path,0x5c);
  slash_ptr = slash_ptr + 1;
  crt_strcpy(((i8 *)&net_session_block.loaded_file_name),slash_ptr);
  count_read = _strlen(((i8 *)&civ_saved_cursor_x_block.game_home_dir));
  result = __strnicmp(path,((i8 *)&civ_saved_cursor_x_block.game_home_dir),count_read);
  if (result == 0) {
    count_read = _strlen(((i8 *)&civ_saved_cursor_x_block.game_home_dir));
    slash_ptr = path + count_read;
    count_read = _strlen(slash_ptr);
    name_len = _strlen(((i8 *)&net_session_block.loaded_file_name));
    if (count_read != name_len) {
      _memset(((i8 *)&net_session_block.loaded_file_subdir),0,0x104);
      count_read = _strlen(slash_ptr);
      name_len = _strlen(((i8 *)&net_session_block.loaded_file_name));
      _strncpy(((i8 *)&net_session_block.loaded_file_subdir),slash_ptr,(count_read - name_len) - 1);
    }
  }
  __chdir(((i8 *)&civ_saved_cursor_x_block.game_home_dir));
  ui_flush_input();
  rules_load(1);
  status = 3;
  ui_flush_input();
  result = save_load_gpk(version & 0xffff,(iptr)_File);
  if (result == 0) goto close_file;
  if (game.multiplayer != 0) {
    game.game_options = game.game_options & 0xffff7fff;
  }
  if (((game.game_flags & 0x40) == 0) && ((game.game_flags & 0x80) == 0)) {
    is_scenario = 0;
  }
  else {
    is_scenario = 1;
  }
  if (is_scenario != 0) {
    game.game_flags = game.game_flags | 0x80;
  }
  if ((game.game_flags & 0x40) != 0) {
    game.game_options = game.game_options & 0xffff7fff;
    game.reveal_map = 0;
    game.game_flags = game.game_flags & 0xffef;
  }
  game.game_flags = game.game_flags & 0xffbf;
  result = map_read((iptr)_File,0);
  if (((result != 0) ||
      (count_read = _fread(map_coarse[0],(int)map.quarter_w * (int)map.quarter_h,1,_File), count_read == 0)) ||
     (count_read = _fread(map_coarse[1],(int)map.quarter_w * (int)map.quarter_h,1,_File), count_read == 0))
  goto close_file;
  ui_flush_input();
  count_read = _fread(((i8 *)&landmass_table_block.landmass_table),0x400,1,_File);
  if ((count_read == 0) || (result = save_read_units_cities(version & 0xffff,(iptr)_File), result == 0))
  goto close_file;
  for (idx = 0; idx < 0x15; idx = idx + 1) {
    count_read = _fread(&leaders[idx].times_used,1,1,_File);
    if (((count_read == 0) || (count_read = _fread(&leaders[idx].city_name_index,1,1,_File), count_read == 0))
       || (count_read = _fread(&leaders[idx].female,1,1,_File), count_read == 0))
    goto close_file;
  }
  count_read = _fread(((i16 *)&map_cursor_x),2,1,_File);
  if ((count_read == 0) ||
     (count_read = _fread(((i16 *)&map_cursor_y),2,1,_File), saved_player_civ = game.player_civ, game.player_civ = saved_player_civ,
     count_read == 0)) goto close_file;
  if (game.multiplayer == 0) {
    count_read = _fread(leader_buf,0x30,1,_File);
    if (count_read == 0) goto close_file;
  }
  else {
    for (idx = 0; game.player_civ = saved_player_civ, idx < 8; idx = idx + 1) {
      if ((1 << ((byte)idx & 0x1f) & (uint)game.human_players) != 0) {
        game.player_civ = (byte)idx;
        count_read = _fread(leader_buf + civs[(char)(byte)idx].tribe * 0x30,
                       0x30,1,_File);
        game.player_civ = saved_player_civ;
        if (count_read == 0) goto close_file;
      }
    }
  }
  count_read = _fread(((i8 *)&power_graph_history_block.power_graph_history),0x4b0,1,_File);
  if ((count_read == 0) || (count_read = _fread(((i16 *)&grey_palette_block.save_layout_record),0x6a,1,_File), count_read == 0)) goto close_file;
  save_unpack_layout_rects();
  ui_flush_input();
  for (idx = 0; idx < 8; idx = idx + 1) {
    count_read = _fread(((i8 *)&map_views_block.map_view_open_flags) + idx * 0x3f0,2,1,_File);
    if ((((count_read == 0) || (count_read = _fread(((i8 *)&map_views_block.mapview_track_moves) + idx * 0x3f0,2,1,_File), count_read == 0))
        || (count_read = _fread(((i16 *)&map_views_block.map_view_center_x) + idx * 0x1f8,2,1,_File), count_read == 0)) ||
       ((count_read = _fread(((i16 *)&map_views_block.mapview_center_y) + idx * 0x1f8,2,1,_File), count_read == 0 ||
        (count_read = _fread(((i16 *)&map_views_block.mapview_zoom) + idx * 0x1f8,2,1,_File), count_read == 0))))
    goto close_file;
  }
  if ((is_scenario == 0) && ((game.game_flags & 0x80) == 0)) {
    scenario_reset_params();
  }
  else {
    count_read = _fread(((i16 *)&prefs_game_rules_block.scenario_flags),100,1,_File);
    if (count_read == 0) goto close_file;
  }
  if (skip_destroyed == 0) {
    count_read = _fread(((i16 *)&destroyed_civ_count_block.destroyed_civ_count),0x152,1,_File);
    if (count_read == 0) goto close_file;
  }
  else {
    destroyed_civs_clear();
  }
  human_civ[0] = (int)game.field_1c;
  if (((version & 0xffff) < 0x29) || (game.multiplayer == 0)) {
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
    count_read = _fread(((i8 *)&civ_saved_cursor_x_block.civ_saved_cursor_x),0x494,1,_File);
    if (count_read == 0) goto close_file;
    if ((*(byte *)&civ_saved_cursor_x_block.saved_turn_civ) == 0) {
      (*(byte *)&civ_saved_cursor_x_block.saved_turn_civ) = game.turn_civ;
    }
    if ((*(byte *)&civ_saved_cursor_x_block.saved_turn_civ) == 0) {
      for (event_count2 = 1; event_count2 < 8; event_count2 = event_count2 + 1) {
        if ((1 << ((byte)event_count2 & 0x1f) & (uint)game.civs_alive) != 0) {
          (*(byte *)&civ_saved_cursor_x_block.saved_turn_civ) = (byte)event_count2;
          break;
        }
      }
    }
    (*(byte *)&turn_resume_civ) = (*(byte *)&civ_saved_cursor_x_block.saved_turn_civ);
    passwords_refresh_flags();
  }
  scenario_events_loaded = 0;
  count_read = _fread(events_tag,4,1,_File);
  if ((count_read != 0) && (result = _strncmp(events_tag,((i8 *)&save_events_tag_check_str),4), result == 0)) {
    count_read = _fread(&event_count2,4,1,_File);
    if (count_read == 0) goto close_file;
    events_reset(((ScenarioEvents*)((i8 *)&unit_types_block.scenario_events)),50000);
    for (event_idx = 0; event_idx < event_count2; event_idx = event_idx + 1) {
      event = (void *)events_alloc(((ScenarioEvents*)((i8 *)&unit_types_block.scenario_events)));
      if (event == (void *)0x0) {
        error_report(0xfffffff7,3,0,0,0);
      }
      count_read = _fread(event,0x1bc,1,_File);
      if (count_read == 0) goto close_file;
    }
    for (event_node = unit_types_block.events_list_head; event_node != 0; event_node = *(int *)(event_node + 0x1bc)) {
      if (*(int *)(event_node + 8) != 0) {
        event_str = save_read_event_str((iptr)_File);
        *(i32 *)(event_node + 8) = event_str;
        if (*(int *)(event_node + 8) == 0) goto close_file;
      }
      if (*(int *)(event_node + 0x10) != 0) {
        event_str = save_read_event_str((iptr)_File);
        *(i32 *)(event_node + 0x10) = event_str;
        if (*(int *)(event_node + 0x10) == 0) goto close_file;
      }
      if (*(int *)(event_node + 0x14) != 0) {
        event_str = save_read_event_str((iptr)_File);
        *(i32 *)(event_node + 0x14) = event_str;
        if (*(int *)(event_node + 0x14) == 0) goto close_file;
      }
      if (*(int *)(event_node + 0x20) != 0) {
        event_str = save_read_event_str((iptr)_File);
        *(i32 *)(event_node + 0x20) = event_str;
        if (*(int *)(event_node + 0x20) == 0) goto close_file;
      }
      for (event_idx = 0; (event_idx < 0x14 && (*(int *)(event_node + 0x38 + event_idx * 4) != 0));
          event_idx = event_idx + 1) {
        event_str = save_read_event_str((iptr)_File);
        *(i32 *)(event_node + 0x38 + event_idx * 4) = event_str;
        if (*(int *)(event_node + 0x38 + event_idx * 4) == 0) goto close_file;
      }
      if (*(int *)(event_node + 0x88) != 0) {
        event_str = save_read_event_str((iptr)_File);
        *(i32 *)(event_node + 0x88) = event_str;
        if (*(int *)(event_node + 0x88) == 0) goto close_file;
      }
      if (*(int *)(event_node + 0x90) != 0) {
        event_str = save_read_event_str((iptr)_File);
        *(i32 *)(event_node + 0x90) = event_str;
        if (*(int *)(event_node + 0x90) == 0) goto close_file;
      }
      if (*(int *)(event_node + 0xc4) != 0) {
        event_str = save_read_event_str((iptr)_File);
        *(i32 *)(event_node + 0xc4) = event_str;
        if (*(int *)(event_node + 0xc4) == 0) goto close_file;
      }
      if (*(int *)(event_node + 0xcc) != 0) {
        event_str = save_read_event_str((iptr)_File);
        *(i32 *)(event_node + 0xcc) = event_str;
        if (*(int *)(event_node + 0xcc) == 0) goto close_file;
      }
      if (*(int *)(event_node + 0xd4) != 0) {
        event_str = save_read_event_str((iptr)_File);
        *(i32 *)(event_node + 0xd4) = event_str;
        if (*(int *)(event_node + 0xd4) == 0) goto close_file;
      }
      if (*(int *)(event_node + 0xdc) != 0) {
        event_str = save_read_event_str((iptr)_File);
        *(i32 *)(event_node + 0xdc) = event_str;
        if (*(int *)(event_node + 0xdc) == 0) goto close_file;
      }
      if (*(int *)(event_node + 0x13c) != 0) {
        event_str = save_read_event_str((iptr)_File);
        *(i32 *)(event_node + 0x13c) = event_str;
        if (*(int *)(event_node + 0x13c) == 0) goto close_file;
      }
      if (*(int *)(event_node + 0x140) != 0) {
        event_str = save_read_event_str((iptr)_File);
        *(i32 *)(event_node + 0x140) = event_str;
        if (*(int *)(event_node + 0x140) == 0) goto close_file;
      }
      if (*(int *)(event_node + 0x148) != 0) {
        event_str = save_read_event_str((iptr)_File);
        *(i32 *)(event_node + 0x148) = event_str;
        if (*(int *)(event_node + 0x148) == 0) goto close_file;
      }
      if (*(int *)(event_node + 0x174) != 0) {
        event_str = save_read_event_str((iptr)_File);
        *(i32 *)(event_node + 0x174) = event_str;
        if (*(int *)(event_node + 0x174) == 0) goto close_file;
      }
      if (*(int *)(event_node + 0x184) != 0) {
        event_str = save_read_event_str((iptr)_File);
        *(i32 *)(event_node + 0x184) = event_str;
        if (*(int *)(event_node + 0x184) == 0) goto close_file;
      }
    }
    events_compact();
    scenario_events_loaded = 1;
  }
  ui_flush_input();
  leaders_fixup_names();
  saved_player_civ = game.player_civ;
  if ((is_scenario == 0) && ((game.game_flags & 0x80) == 0)) {
    if (game.multiplayer == 0) {
      leaders[civs[(char)game.player_civ].tribe].leader_name =
           -leaders[civs[(char)game.player_civ].tribe].leader_name;
      if (((short *)(leader_buf + 12))[0] < 0) {
        leaders[civs[(char)game.player_civ].tribe].plural =
             -leaders[civs[(char)game.player_civ].tribe].plural;
      }
      if (((short *)(leader_buf + 12))[1] < 0) {
        leaders[civs[(char)game.player_civ].tribe].adjective =
             -leaders[civs[(char)game.player_civ].tribe].adjective;
      }
      for (idx = 0; idx < 7; idx = idx + 1) {
        for (gender = 0; gender < 2; gender = gender + 1) {
          if (((short *)(leader_buf + 12))[gender + idx * 2 + 4] < 0) {
            leaders[civs[(char)game.player_civ].tribe].titles[idx][gender]
                 = -leaders[civs[(char)game.player_civ].tribe].titles[idx][gender];
          }
        }
      }
    }
    else {
      for (civ = 0; game.player_civ = saved_player_civ, civ < 8; civ = civ + 1) {
        if ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0) {
          game.player_civ = (byte)civ;
          leaders[civs[(char)(byte)civ].tribe].leader_name =
               -leaders[civs[(char)(byte)civ].tribe].leader_name;
          if (((short *)(leader_buf + 12))[civs[(char)game.player_civ].tribe * 0x18] < 0) {
            leaders[civs[(char)game.player_civ].tribe].plural = -leaders[civs[(char)game.player_civ].tribe].plural;
          }
          if (((short *)(leader_buf + 12))[civs[(char)game.player_civ].tribe * 0x18 + 1] < 0) {
            leaders[civs[(char)game.player_civ].tribe].adjective = -leaders[civs[(char)game.player_civ].tribe].adjective;
          }
          for (idx = 0; idx < 7; idx = idx + 1) {
            for (gender = 0; gender < 2; gender = gender + 1) {
              if (((short *)(leader_buf + 12))[idx * 2 +
                            gender +
                            civs[(char)game.player_civ].tribe * 0x18 + 4] < 0)
              {
                leaders[civs[(char)game.player_civ].tribe].titles[idx][gender] =
                     -leaders[civs[(char)game.player_civ].tribe].titles[idx][gender];
              }
            }
          }
        }
      }
    }
  }
  else {
    for (civ = 1; civ < 8; civ = civ + 1) {
      if ((civs[civ].flags & 0x200) == 0) {
        leaders[civs[civ].tribe].female = 0;
      }
      else {
        leaders[civs[civ].tribe].female = 1;
      }
      civs[civ].leader_portrait = civs[civ].tribe;
      if (leaders[civs[civ].tribe].female != '\0') {
        civs[civ].leader_portrait = civs[civ].leader_portrait + '\x15';
      }
      if (leaders[civs[civ].tribe].plural < 1) {
        title_label = ~(int)leaders[civs[civ].tribe].plural + 1;
      }
      else {
        title_label = (int)leaders[civs[civ].tribe].plural;
      }
      dot_ptr = (char *)label_string(title_label);
      result = _strcmp(&civ_names[civ].tribe_name[0],dot_ptr);
      if (result == 0) {
        for (idx = 0; idx < 7; idx = idx + 1) {
          for (gender = 0; gender < 2; gender = gender + 1) {
            leaders[civs[civ].tribe].titles[idx][gender] =
                 (short)(&government_titles[idx].male)[gender]   /* [0] male, [1] female */;
          }
        }
      }
      leaders[civs[civ].tribe].leader_name =
           -leaders[civs[civ].tribe].leader_name;
      leaders[civs[civ].tribe].plural =
           -leaders[civs[civ].tribe].plural;
      leaders[civs[civ].tribe].adjective =
           -leaders[civs[civ].tribe].adjective;
    }
  }
  ui_flush_input();
  for (civ = 0; civ < 8; civ = civ + 1) {
    for (type_idx = 0; type_idx < 0x3e; type_idx = type_idx + 1) {
      civs[civ].units_in_production[type_idx] = 0;
      civs[civ].units_active[type_idx] = 0;
    }
    for (unit_idx = 0; unit_idx < game.num_units; unit_idx = unit_idx + 1) {
      if ((units[unit_idx].id != 0) &&
         ((char)units[unit_idx].owner == civ)) {
        civs[civ].units_active[(uint)(byte)units[unit_idx].type] =
             civs[civ].units_active[(uint)(byte)units[unit_idx].type] +
             '\x01';
      }
    }
    for (city_idx = 0; city_idx < game.num_cities; city_idx = city_idx + 1) {
      if (((cities[city_idx].id != 0) &&
          ((char)cities[city_idx].owner == civ)) &&
         (-1 < (char)cities[city_idx].building)) {
        civs[civ].units_in_production[(int)(char)cities[city_idx].building] =
             civs[civ].units_in_production[(int)(char)cities[city_idx].building] +
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
  result = rect_width((iptr)&saved_screen_rect_block.saved_screen_rect);
  screen_h = rect_width((iptr)&caption_small_font_block.screen_rect);
  if (result == screen_h) {
    result = rect_height((iptr)&saved_screen_rect_block.saved_screen_rect);
    screen_h = rect_height((iptr)&caption_small_font_block.screen_rect);
    if ((result != screen_h) || (is_scenario != 0)) goto invalid_layout;
  }
  else {
invalid_layout:
    destroyed_civ_count_block.saved_layout_valid = 0;
  }
  status = 0;
close_file:
  if (_File != (FILE *)0x0) {
    _fclose(_File);
  }
  if ((status == 0) && (game.multiplayer != saved_multiplayer)) {
    civ_saved_cursor_x_block.mp_open_game = 1;
    if (saved_multiplayer == 0) {
      civ_saved_cursor_x_block.mp_double_production = 0;
      civ_saved_cursor_x_block.mp_double_moves = 0;
    }
    prefs_main_menu_choice_block.prefs_mp_simultaneous_moves = 0;
    if (game.human_players == 0) {
      if (((*(byte *)&turn_resume_civ) == 0) || ((1 << ((*(byte *)&turn_resume_civ) & 0x1f) & (uint)game.civs_alive) == 0)) {
        for (event_idx = 1; event_idx < 8; event_idx = event_idx + 1) {
          if ((1 << ((byte)event_idx & 0x1f) & (uint)game.civs_alive) != 0) {
            game.human_players = (byte)(1 << ((byte)event_idx & 0x1f));
            break;
          }
        }
      }
      else {
        game.human_players = (byte)(1 << ((*(byte *)&turn_resume_civ) & 0x1f));
      }
    }
    if (saved_multiplayer != 0) {
      game.multiplayer = (byte)saved_multiplayer;
    }
  }
  return status;
}


/* wnd_get_style_flags is declared to return i8 but returns the whole window
   style dword (*this); callers test bit 0x200 (SWS_ATTACHED) in AH.  Read
   here directly (a call through a cast to another return type traps in
   wasm). */
#define WIN_STYLE(w) (*(uint *)(w))

/* 0x005bd566 */
void __cdecl wnd_obj_set_topmost_child(int parent_obj,int child_obj)

{
  HWND child_parent;
  void *self;
  
  if (parent_obj != 0) {
    if (child_obj == 0) {
      *(i32 *)(parent_obj + 0x10) = 0;
    }
    else {
      child_parent = GetParent(*(HWND *)(child_obj + 4));
      if (child_parent == *(HWND *)(parent_obj + 4)) {
        self = (void *)GetWindowLongA(*(HWND *)(child_obj + 4),0);
        if ((WIN_STYLE(self) & 0x200) == 0) {
          dbg_log((iptr)str_window_not_sws_attached_in_mssettopmostc);
        }
        else {
          *(i32 *)(parent_obj + 0x10) = *(i32 *)(child_obj + 4);
        }
      }
      else {
        dbg_log((iptr)str_window_not_a_child_in_mssettopmostchild);
      }
    }
  }
  return;
}


/* 0x005dbe88 */
LRESULT __stdcall wnd_base_wndproc(HWND hwnd,uint msg,WPARAM wparam,uint lparam)

{
  HWND parent_hwnd;
  HDC dc;
  BOOL iconic;
  HICON hIcon;
  LRESULT result;
  void *tmp_wnd;
  int wnd_data;
  int offset_x;
  tagRECT *src_rect;
  tagRECT *dst_rect;
  int hit;
  tagPAINTSTRUCT ps;
  int row;
  void *wnd2;
  HDC paint_dc;
  int col;
  int pos_y2;
  int tile_h;
  int pos_x2;
  int tile_w;
  RECT paint_rect;
  tagRECT blit_rect;
  int parent_data;
  tagRECT win_rect;
  
  if (msg < 0x10) {
    if (msg == 0xf) {
      paint_dc = BeginPaint(hwnd,&ps);
      wnd2 = (void *)GetWindowLongA(hwnd,0);
      iconic = IsIconic(hwnd);
      if (iconic != 0) {
        GetWindowRect(hwnd,&win_rect);
        wnd_data = wnd_get_window((WndBase *)wnd2);
        if (*(int *)(wnd_data + 0x20) == 0) {
          hIcon = LoadIconA((HINSTANCE)0x0,(LPCSTR)0x7f00);
          DrawIcon(paint_dc,0,0,hIcon);
        }
        else {
          wnd_data = wnd_get_window((WndBase *)wnd2);
          if ((*(int *)(wnd_data + 0x18) != 0) && (gfx_palettized_display == 1)) {
            wnd_data = wnd_get_window((WndBase *)wnd2);
            RealizePalette(*(HDC *)(wnd_data + 8));
          }
          wnd_data = wnd_get_window((WndBase *)wnd2);
          DrawIcon(paint_dc,0,0,*(HICON *)(wnd_data + 0x20));
        }
        return 0;
      }
      wnd_data = wnd_get_window((WndBase *)wnd2);
      if (*(int *)(wnd_data + 0x24) == 0) {
        wnd_data = wnd_get_window((WndBase *)wnd2);
        if (*(int *)(wnd_data + 0x14) != 0) {
          wnd_data = wnd_get_window((WndBase *)wnd2);
          FillRect(paint_dc,&ps.rcPaint,*(HBRUSH *)(wnd_data + 0x14));
        }
      }
      else {
        wnd_data = wnd_get_window((WndBase *)wnd2);
        tile_w = surface_width((DibSurface *)*(void **)(wnd_data + 0x24));
        wnd_data = wnd_get_window((WndBase *)wnd2);
        tile_h = surface_height((DibSurface *)*(void **)(wnd_data + 0x24));
        if ((tile_w != 0) && (tile_h != 0)) {
          paint_rect.left = ps.rcPaint.left;
          paint_rect.top = ps.rcPaint.top;
          paint_rect.right = ps.rcPaint.right;
          paint_rect.bottom = ps.rcPaint.bottom;
          SetRect(&win_rect,0,0,tile_w,tile_h);
          for (row = paint_rect.top / tile_h; row < paint_rect.bottom / tile_h + 1;
              row = row + 1) {
            for (col = paint_rect.left / tile_w; col < paint_rect.right / tile_w + 1;
                col = col + 1) {
              SetRect(&blit_rect,col * tile_w,row * tile_h,
                      col * tile_w + tile_w,row * tile_h + tile_h);
              dst_rect = &blit_rect;
              src_rect = &win_rect;
              tmp_wnd = wnd2;
              wnd_data = wnd_get_window((WndBase *)wnd2);
              surface_blit_to_wnd((DibSurface *)*(void **)(wnd_data + 0x24),(iptr)tmp_wnd,(iptr)src_rect,(iptr)dst_rect);
            }
          }
        }
      }
      wnd_data = wnd_get_window((WndBase *)wnd2);
      if (*(int *)(wnd_data + 0x2c) != 0) {
        wnd_data = wnd_get_window((WndBase *)wnd2);
        tile_w = surface_width((DibSurface *)*(void **)(wnd_data + 0x2c));
        wnd_data = wnd_get_window((WndBase *)wnd2);
        tile_h = surface_height((DibSurface *)*(void **)(wnd_data + 0x2c));
        paint_rect.left = ps.rcPaint.left;
        paint_rect.top = ps.rcPaint.top;
        paint_rect.right = ps.rcPaint.right;
        paint_rect.bottom = ps.rcPaint.bottom;
        SetRect(&win_rect,0,0,tile_w,tile_h);
        wnd_data = wnd_client_height((WndBase *)wnd2);
        wnd_data = wnd_data - tile_h >> 1;
        offset_x = wnd_client_width((WndBase *)wnd2);
        OffsetRect(&win_rect,offset_x - tile_w >> 1,wnd_data);
        iconic = IntersectRect(&blit_rect,&win_rect,&paint_rect);
        if (iconic != 0) {
          win_rect.left = blit_rect.left;
          win_rect.top = blit_rect.top;
          win_rect.right = blit_rect.right;
          win_rect.bottom = blit_rect.bottom;
          wnd_data = wnd_client_height((WndBase *)wnd2);
          wnd_data = -(wnd_data - tile_h >> 1);
          offset_x = wnd_client_width((WndBase *)wnd2);
          OffsetRect(&win_rect,-(offset_x - tile_w >> 1),wnd_data);
          dst_rect = &blit_rect;
          src_rect = &win_rect;
          tmp_wnd = wnd2;
          wnd_data = wnd_get_window((WndBase *)wnd2);
          surface_blit_to_wnd((DibSurface *)*(void **)(wnd_data + 0x2c),(iptr)tmp_wnd,(iptr)src_rect,(iptr)dst_rect);
        }
      }
      EndPaint(hwnd,&ps);
      return 0;
    }
    switch(msg) {
    case 2:
      SetMenu(hwnd,(HMENU)0x0);
      tmp_wnd = (void *)GetWindowLongA(hwnd,0);
      wnd_data = wnd_get_window((WndBase *)tmp_wnd);
      *(i32 *)(wnd_data + 0x44) = 1;
      if ((*(byte *)(wnd_data + 0x49) & 2) != 0) {
        wnd_data = 0;
        parent_hwnd = GetParent(hwnd);
        tmp_wnd = (void *)GetWindowLongA(parent_hwnd,wnd_data);
        parent_data = wnd_get_window((WndBase *)tmp_wnd);
        if (*(HWND *)(parent_data + 0xc) == hwnd) {
          *(i32 *)(parent_data + 0xc) = 0;
        }
      }
      result = DefWindowProcA(hwnd,msg,wparam,lparam);
      return result;
    case 3:
      wnd2 = (void *)GetWindowLongA(hwnd,0);
      if (wnd2 != (void *)0x0) {
        wnd_data = wnd_get_window((WndBase *)wnd2);
        dc = *(HDC *)(wnd_data + 8);
        wnd_data = wnd_get_window((WndBase *)wnd2);
        ReleaseDC(*(HWND *)(wnd_data + 4),dc);
        wnd_data = wnd_get_window((WndBase *)wnd2);
        offset_x = wnd_get_window((WndBase *)wnd2);
        dc = GetDC(*(HWND *)(offset_x + 4));
        *(HDC *)(wnd_data + 8) = dc;
      }
      break;
    case 5:
      wnd2 = (void *)GetWindowLongA(hwnd,0);
      if ((wnd2 != (void *)0x0) &&
         (wnd_data = wnd_get_window((WndBase *)wnd2), *(int *)(wnd_data + 0x2c) != 0)) {
        InvalidateRect(hwnd,(RECT *)0x0,1);
      }
      if (wnd2 != (void *)0x0) {
        wnd_data = wnd_get_window((WndBase *)wnd2);
        dc = *(HDC *)(wnd_data + 8);
        wnd_data = wnd_get_window((WndBase *)wnd2);
        ReleaseDC(*(HWND *)(wnd_data + 4),dc);
        wnd_data = wnd_get_window((WndBase *)wnd2);
        offset_x = wnd_get_window((WndBase *)wnd2);
        dc = GetDC(*(HWND *)(offset_x + 4));
        *(HDC *)(wnd_data + 8) = dc;
      }
      break;
    case 7:
      tmp_wnd = (void *)GetWindowLongA(hwnd,0);
      wnd_data = wnd_get_window((WndBase *)tmp_wnd);
      if (*(int *)(wnd_data + 0xc) != 0) {
        SendMessageA(*(HWND *)(wnd_data + 0xc),0x86,1,0);
      }
      break;
    case 8:
      tmp_wnd = (void *)GetWindowLongA(hwnd,0);
      wnd_data = wnd_get_window((WndBase *)tmp_wnd);
      if (*(int *)(wnd_data + 0xc) != 0) {
        SendMessageA(*(HWND *)(wnd_data + 0xc),0x86,0,0);
      }
    }
  }
  else if (msg < 0x47) {
    if (msg == 0x46) {
      if ((*(byte *)(lparam + 0x18) & 4) == 0) {
        wnd2 = (void *)GetWindowLongA(hwnd,0);
        wnd_get_window((WndBase *)wnd2);
        if ((WIN_STYLE(wnd2) & 0x200) != 0) {
          wnd_data = 0;
          parent_hwnd = GetParent(hwnd);
          tmp_wnd = (void *)GetWindowLongA(parent_hwnd,wnd_data);
          parent_data = wnd_get_window((WndBase *)tmp_wnd);
          if (((*(int *)(parent_data + 0x10) != 0) && (*(HWND *)(parent_data + 0x10) != hwnd)) &&
             (iconic = IsWindowVisible(*(HWND *)(parent_data + 0x10)), iconic != 0)) {
            *(i32 *)(lparam + 4) = *(i32 *)(parent_data + 0x10);
          }
        }
      }
    }
    else if (msg == 0x22) {
      tmp_wnd = (void *)GetWindowLongA(hwnd,0);
      wnd_data = wnd_get_window((WndBase *)tmp_wnd);
      if ((*(byte *)(wnd_data + 0x49) & 2) != 0) {
        wnd_data = 0;
        parent_hwnd = GetParent(hwnd);
        tmp_wnd = (void *)GetWindowLongA(parent_hwnd,wnd_data);
        parent_data = wnd_get_window((WndBase *)tmp_wnd);
        if (*(int *)(parent_data + 0xc) != 0) {
          SendMessageA(*(HWND *)(parent_data + 0xc),0x86,0,0);
        }
        SendMessageA(hwnd,0x86,1,0);
        *(HWND *)(parent_data + 0xc) = hwnd;
      }
    }
  }
  else {
    if (msg < 0xa5) {
      if ((msg != 0xa4) && (msg != 0xa1)) goto default_wndproc;
    }
    else {
      if (msg == 0x112) {
        if ((wparam == 0xf100) || (wparam == 0xf090)) {
          tmp_wnd = (void *)GetWindowLongA(hwnd,0);
          wnd_data = wnd_get_window((WndBase *)tmp_wnd);
          if ((*(byte *)(wnd_data + 0x48) & 0x20) == 0) {
            return 0;
          }
        }
        goto default_wndproc;
      }
      if ((msg != 0x201) && (msg != 0x204)) goto default_wndproc;
    }
    tmp_wnd = (void *)GetWindowLongA(hwnd,0);
    wnd_data = wnd_get_window((WndBase *)tmp_wnd);
    if ((*(byte *)(wnd_data + 0x49) & 2) != 0) {
      SetFocus(*(HWND *)(wnd_data + 4));
      BringWindowToTop(hwnd);
    }
  }
default_wndproc:
  hit = DefWindowProcA(hwnd,msg,wparam,lparam);
  if (msg == 0x84) {
    tmp_wnd = (void *)GetWindowLongA(hwnd,0);
    wnd_data = wnd_get_window((WndBase *)tmp_wnd);
    if ((*(int *)(wnd_data + 0x34) != 0) && (hit == 1)) {
      GetWindowRect(hwnd,&win_rect);
      pos_x2 = (lparam & 0xffff) - win_rect.left;
      pos_y2 = (lparam >> 0x10) - win_rect.top;
      if (*(int *)(wnd_data + 0x3c) == 0) {
        tile_w = 5;
      }
      else {
        tile_w = *(int *)(wnd_data + 0x3c);
      }
      GetClientRect(hwnd,&blit_rect);
      row = 0;
      col = 0;
      if (pos_y2 < tile_w) {
        row = -1;
      }
      else {
        offset_x = rect_height((iptr)&blit_rect);
        if (offset_x - tile_w < pos_y2) {
          row = 1;
        }
      }
      if (pos_x2 < tile_w) {
        col = -1;
      }
      else {
        offset_x = rect_width((iptr)&blit_rect);
        if (offset_x - tile_w < pos_x2) {
          col = 1;
        }
      }
      if (row < 0) {
        if (pos_x2 < tile_w * 4) {
          col = -1;
        }
        else {
          offset_x = rect_width((iptr)&blit_rect);
          if (offset_x + tile_w * -4 < pos_x2) {
            col = 1;
          }
        }
        if (col < 0) {
          hit = 0xd;
        }
        else if (col < 1) {
          hit = 0xc;
        }
        else {
          hit = 0xe;
        }
      }
      else if (row < 1) {
        if (col < 0) {
          if (pos_y2 < tile_w * 4) {
            row = -1;
          }
          else {
            offset_x = rect_height((iptr)&blit_rect);
            if (offset_x + tile_w * -4 < pos_y2) {
              row = 1;
            }
          }
          if (row < 0) {
            hit = 0xd;
          }
          else if (row < 1) {
            hit = 10;
          }
          else {
            hit = 0x10;
          }
        }
        else if (0 < col) {
          if (pos_y2 < tile_w * 4) {
            row = -1;
          }
          else {
            offset_x = rect_height((iptr)&blit_rect);
            if (offset_x + tile_w * -4 < pos_y2) {
              row = 1;
            }
          }
          if (row < 0) {
            hit = 0xe;
          }
          else if (row < 1) {
            hit = 0xb;
          }
          else {
            hit = 0x11;
          }
        }
      }
      else {
        if (pos_x2 < tile_w * 4) {
          col = -1;
        }
        else {
          offset_x = rect_width((iptr)&blit_rect);
          if (offset_x + tile_w * -4 < pos_x2) {
            col = 1;
          }
        }
        if (col < 0) {
          hit = 0x10;
        }
        else if (col < 1) {
          hit = 0xf;
        }
        else {
          hit = 0x11;
        }
      }
    }
    if ((*(int *)(wnd_data + 0x30) != 0) && (hit == 1)) {
      GetWindowRect(hwnd,&win_rect);
      pos_y2 = (lparam >> 0x10) - win_rect.top;
      if ((*(int *)(wnd_data + 0x38) == 0) || (pos_y2 < *(int *)(wnd_data + 0x38))) {
        hit = 2;
      }
    }
    if (hit == 1) {
      SetCursor(*(HCURSOR *)(wnd_data + 0x1c));
    }
  }
  return hit;
}


/* 0x005eacc0 */
LRESULT __stdcall wnd_frame_wndproc(HWND hwnd,uint msg,uint wparam,HWND lparam)

{
  char nav_enabled;
  SHORT shift_state;
  LRESULT result;
  HWND parent_hwnd;
  void *parent_wnd;
  i32 ctrl_arg;
  BOOL valid;
  uint notify_code;
  DWORD class_bytes;
  int tmp;
  tagRECT moving_rect;
  HWND visible_type11;
  int insert_after;
  HWND type11_hwnd;
  HWND ctrl_hwnd;
  i32 shift_flags;
  i32 wnd_data;
  void *wnd2;
  int edit_offset;
  LONG parent_frame;
  void *frame;
  LONG edit_obj;
  HWND notify_hwnd;
  HWND scroll_hwnd;
  int parent_data;
  
  frame = (void *)GetWindowLongA(hwnd,8);
  if (frame == (void *)0x0) {
    result = wnd_child_wndproc(hwnd,msg,wparam,lparam);
    return result;
  }
  if (msg < 6) {
    if (msg == 5) {
      type11_hwnd = (HWND)ctrl_list_find_type11_hwnd((ControlNextView *)*(i32 *)((int)frame + 0xb8));
      if (type11_hwnd != (HWND)0x0) {
        SendMessageA(type11_hwnd,5,wparam,(LPARAM)lparam);
      }
      result = wnd_child_wndproc(hwnd,5,wparam,lparam);
      return result;
    }
    if (msg == 2) {
      *(i32 *)((int)frame + 0xb8) = 0;
      SetWindowLongA(hwnd,8,0);
      result = wnd_child_wndproc(hwnd,2,wparam,lparam);
      return result;
    }
  }
  else if (msg < 0x101) {
    if (msg == 0x100) {
      shift_state = GetAsyncKeyState(0x10);
      tmp = (int)shift_state;
      (*(i8 *)((char *)&shift_flags + 1)) = (char)((ushort)shift_state >> 8);
      shift_flags = tmp;
      if ((wparam == 9) && ((*(i8 *)((char *)&shift_flags + 1)) == '\0')) {
        nav_enabled = wnd_keyboard_nav_enabled((WndKeyNavView *)frame);
        if (nav_enabled != '\0') {
          wnd_cycle_control_focus((iptr)frame,0,2);
        }
      }
      else if ((wparam == 9) && ((*(i8 *)((char *)&shift_flags + 1)) != '\0')) {
        nav_enabled = wnd_keyboard_nav_enabled((WndKeyNavView *)frame);
        if (nav_enabled != '\0') {
          wnd_cycle_control_focus((iptr)frame,0,3);
        }
      }
      else if ((wparam == 0xd) && ((*(i8 *)((char *)&shift_flags + 1)) == '\0')) {
        if (*(int *)((int)frame + 0xbc) != 0) {
          ctrl_arg = control_get_hwnd((ControlHwndView *)*(void **)((int)frame + 0xbc));
          button_press_animated(ctrl_arg);
        }
      }
      else if ((wparam == 0x1b) && ((*(i8 *)((char *)&shift_flags + 1)) == '\0')) {
        if (*(int *)((int)frame + 0xc0) != 0) {
          ctrl_arg = control_get_hwnd((ControlHwndView *)*(void **)((int)frame + 0xc0));
          button_press_animated(ctrl_arg);
        }
      }
      else {
        ctrl_arg = input_map_vkey(wparam);
        wnd_dispatch_hotkey_char(frame,ctrl_arg);
      }
      valid = IsWindow(hwnd);
      if (valid == 0) {
        return 0;
      }
      result = wnd_child_wndproc(hwnd,0x100,wparam,lparam);
      return result;
    }
    if (msg == 0x46) {
      if ((((WINDOWPOS *)lparam)->flags & 4) == 0) {   /* WM_WINDOWPOSCHANGING: SWP_NOZORDER */
        wnd2 = (void *)GetWindowLongA(hwnd,0);
        wnd_data = wnd_get_window((WndBase *)wnd2);
        if ((WIN_STYLE(wnd2) & 0x200) != 0) {
          tmp = 0;
          parent_hwnd = GetParent(hwnd);
          parent_wnd = (void *)GetWindowLongA(parent_hwnd,tmp);
          parent_data = wnd_get_window((WndBase *)parent_wnd);
          parent_frame = GetWindowLongA(*(HWND *)(parent_data + 4),8);
          if ((parent_frame != 0) &&
             (insert_after = ctrl_list_find_type11_hwnd((ControlNextView *)*(i32 *)(parent_frame + 0xb8)), insert_after != 0)) {
            ((WINDOWPOS *)lparam)->hwndInsertAfter = (HWND)(iptr)insert_after;
            result = DefWindowProcA(hwnd,0x46,wparam,(LPARAM)lparam);
            return result;
          }
        }
      }
      result = wnd_child_wndproc(hwnd,0x46,wparam,lparam);
      return result;
    }
  }
  else {
    if (msg < 0x116) {
      if (msg < 0x114) {
        if (msg != 0x111) goto forward_to_child;
        notify_code = wparam >> 0x10;
        if (notify_code < 0x301) {
          if (notify_code == 0x300) {
            notify_hwnd = lparam;
            class_bytes = GetClassLongA(lparam,-0x12);
            edit_offset = class_bytes - 4;
            edit_obj = GetWindowLongA(notify_hwnd,edit_offset);
            edit_fire_change_callback((EditChangeView *)edit_obj);
          }
          else if (notify_code == 1) {
            ctrl_hwnd = lparam;
            SendMessageA(lparam,0x4c8,wparam,(LPARAM)lparam);
          }
          else {
            if (notify_code != 2) goto forward_command;
            ctrl_hwnd = lparam;
            SendMessageA(lparam,0x4c8,wparam,(LPARAM)lparam);
          }
        }
        else {
          if (notify_code != 0x501) {
forward_command:
            result = wnd_child_wndproc(hwnd,0x111,wparam,lparam);
            return result;
          }
          notify_hwnd = lparam;
          class_bytes = GetClassLongA(lparam,-0x12);
          edit_offset = class_bytes - 4;
          edit_obj = GetWindowLongA(notify_hwnd,edit_offset);
          edit_fire_maxtext_callback((EditMaxTextView *)edit_obj);
        }
      }
      else {
        tmp = wnd_get_window((WndBase *)frame);
        if (((*(byte *)(tmp + 0x48) & 0x80) != 0) ||
           (tmp = wnd_get_window((WndBase *)frame), (*(byte *)(tmp + 0x49) & 1) != 0)) {
          result = wnd_child_wndproc(hwnd,msg,wparam,lparam);
          return result;
        }
        scroll_hwnd = lparam;
        scrollbar_hwnd_handle_msg(lparam,msg,wparam,lparam);
      }
      return 0;
    }
    if (msg == 0x216) {
      wnd2 = (void *)GetWindowLongA(hwnd,0);
      wnd_data = wnd_get_window((WndBase *)wnd2);
      if ((WIN_STYLE(wnd2) & 0x200) != 0) {
        tmp = 0;
        parent_hwnd = GetParent(hwnd);
        parent_wnd = (void *)GetWindowLongA(parent_hwnd,tmp);
        parent_data = wnd_get_window((WndBase *)parent_wnd);
        parent_frame = GetWindowLongA(*(HWND *)(parent_data + 4),8);
        if (((parent_frame != 0) &&
            (visible_type11 = (HWND)ctrl_list_find_type11_hwnd((ControlNextView *)*(i32 *)(parent_frame + 0xb8)), visible_type11 != (HWND)0x0)
            ) && (valid = IsWindowVisible(visible_type11), valid != 0)) {
          tmp = GetSystemMetrics(4);
          GetWindowRect(visible_type11,&moving_rect);
          shift_flags = rect_width(lparam);
          if (moving_rect.top - tmp <= ((RECT *)lparam)->top) {   /* WM_MOVING */
            ((RECT *)lparam)->top = moving_rect.top - tmp;
            ((RECT *)lparam)->bottom = (moving_rect.top - tmp) + shift_flags;
          }
        }
      }
      result = wnd_child_wndproc(hwnd,0x216,wparam,lparam);
      return result;
    }
  }
forward_to_child:
  result = wnd_child_wndproc(hwnd,msg,wparam,lparam);
  return result;
}


/* 0x0048aa24 */
uint __cdecl game_turn_start_popups(void)

{
  uint ret;
  int has_improv;
  i32 civ_name;
  int city_idx;
  int best_city;
  int best_score;
  int score;
  
  best_city = -1;
  ret = (uint)(short)game.turn;
  if (((1 < (int)ret) &&
      (ret = ((short)game.turn + -1) / 0x32, ((short)game.turn + -1) % 0x32 == 0)) &&
     (((*(i8 *)((char *)&game.game_options + 2)) & 0x10) != 0)) {
    best_score = -1;
    for (city_idx = 0; city_idx < game.num_cities; city_idx = city_idx + 1) {
      if ((cities[city_idx].id != 0) &&
         ((char)cities[city_idx].owner == human_civ[0])) {
        score = (int)(char)cities[city_idx].size;
        has_improv = city_has_improvement(city_idx,1);
        if (has_improv != 0) {
          score = score << 1;
        }
        if (score == 1 || score + -1 < 0) {
          score = 0;
        }
        else {
          has_improv = _rand();
          score = has_improv % score;
        }
        if (best_score < score) {
          best_score = score;
          best_city = city_idx;
        }
      }
    }
    civ_name = civ_name_plural(human_civ[0]);
    text_set_string_arg(0,civ_name);
    text_clear();
    text_append_year((int)game.year);
    text_set_string_arg(2,(iptr)&map_views_block.text_buffer);
    text_clear();
    if (best_city < 0) {
      text_append_label(0xe);
    }
    else {
      text_append((iptr)cities[best_city].name);
      mapview_center_on(((ViewWindow*)((i8 *)&map_views_block.map_views)),(int)cities[best_city].x,
                         (int)cities[best_city].y);
    }
    text_set_string_arg(1,(iptr)&map_views_block.text_buffer);
    ret = popup_game_with_sprite((iptr)str_counciltime,(iptr)&popup_info_icon_sprite,0);
    if (ret == 0) {
      council_show(human_civ[0],0);   /* void; result left in EAX is garbage */
    }
  }
  if (((*(i8 *)((char *)&game.game_options + 1)) & 1) != 0) {
    if (game.turn == 1) {
      popup_file_with_sprite(((iptr)*(i8 * *)str_ptr_labels_rest),(iptr)str_firstmove,(iptr)&tutorial_icon_sprite_block.tutorial_icon_sprite,0);
    }
    if ((game.turn == 0x14) || (game.turn == 0x3c)) {
      popup_file_with_sprite(((iptr)*(i8 * *)str_ptr_labels_rest),(iptr)str_help1,(iptr)&tutorial_icon_sprite_block.tutorial_icon_sprite,0);
    }
    if ((game.turn == 0x28) || (game.turn == 0x50)) {
      popup_file_with_sprite(((iptr)*(i8 * *)str_ptr_labels_rest),(iptr)str_help2,(iptr)&tutorial_icon_sprite_block.tutorial_icon_sprite,0);
    }
    if ((((civs[human_civ[0]].num_cities == 1) &&
         (2 < civs[human_civ[0]].total_city_size)) && (game.turn == 0x23)) &&
       ((civs[human_civ[0]].units_active[0] == '\0' &&
        (civs[human_civ[0]].units_in_production[0] == '\0')))) {
      ret = city_find_nearest((int)map.width / 2,(int)map.height / 2,human_civ[0],0xffffffff
                                 ,0xffffffff);
      if (-1 < (int)ret) {
        text_set_string_arg(0,(iptr)cities[ret].name);
        popup_text_with_city_noflags(((iptr)*(i8 * *)str_ptr_labels_rest),(iptr)str_onecity,ret);
        ret = (int)(short)game.turn - 0x19;
        civs[human_civ[0]].last_city_turn = (short)ret;
      }
    }
    else {
      ret = (int)(short)game.turn - (int)civs[human_civ[0]].last_city_turn;
      if ((0x18 < (int)ret) &&
         ((ret = (uint)civs[human_civ[0]].num_cities, (int)ret < 6 &&
          (ret = human_civ[0] * 0x165, civs[human_civ[0]].units_active[0] == '\0')))) {
        popup_file_with_sprite(((iptr)*(i8 * *)str_ptr_labels_rest),(iptr)str_expand0,(iptr)&tutorial_icon_sprite_block.tutorial_icon_sprite,0);
        ret = (uint)game.turn;
        civs[human_civ[0]].last_city_turn = game.turn;
      }
    }
  }
  return ret;
}


/* 0x004eb4ed */
int __cdecl city_recalc(int city,int full)

{
  int result;
  
  if (city == -1) {
    result = 0;
  }
  else if (full == 0) {
    result = main_menu_block.city_happy_count - main_menu_block.city_unhappy_count;
  }
  else {
    city_calc_cached_id = city;
    city_calc_tile_flags(city);
    city_calc_capital_link(city);
    city_calc_unit_support(city);
    /* city_calc_all_stats, which is declared void but returns its last call's
       (city_calc_trade_happiness's) int: */
    city_assign_workers(city);
    city_count_food_routes(city);
    city_fill_specialists(city);
    city_calc_shields_pollution(city);
    result = city_calc_trade_happiness(city);
  }
  return result;
}


/* 0x004efd44 */
int __cdecl city_process_pollution(int city)

{
  char owner;
  int roll;
  i32 tile_x;
  int check;
  uint improvements2;
  int meltdown_roll;
  int pollution_roll;
  int pollution_chance;
  
  owner = cities[city].owner;
  pollution_chance = (int)((uint)(byte)civs[owner].num_advances * (uint)game.difficulty) >> 1;
  if (((game.game_flags & 0x80) != 0) && ((prefs_game_rules_block.scenario_flags[0] & 0x40) != 0)) {
    pollution_chance = 0;
    main_menu_block.city_pollution = 0;
  }
  roll = city_has_improvement(city,0x1d);
  if (roll != 0) {
    for (; 0xff < pollution_chance; pollution_chance = pollution_chance / 2) {
    }
  }
  if (-pollution_chance == -0xff || -pollution_chance + 0xff < 0) {
    pollution_roll = 0;
  }
  else {
    pollution_roll = _rand();
    pollution_roll = pollution_roll % (0x100 - pollution_chance);
  }
  if (pollution_roll < main_menu_block.city_pollution * 2) {
    roll = _rand();
    tile_x = map_wrap_x((int)cities[city].x +
                               (int)(char)(((i8 *)&dir_dy_table_block.city_tile_dx_table))[roll % 0x14]);
    roll = (int)cities[city].y +
            (int)(char)(((i8 *)&dir_dy_table_block.city_tile_dy_table))[roll % 0x14];
    check = map_in_bounds(tile_x,roll);
    if (check != 0) {
      improvements2 = tile_improvements(tile_x,roll);
      if ((improvements2 & 0x82) == 0) {
        check = tile_is_ocean(tile_x,roll);
        if (check == 0) {
          tile_add_pollution(tile_x,roll);
          check = tile_visible_to(tile_x,roll,human_civ[0]);
          if (check != 0) {
            mapview_center_on(((ViewWindow*)((i8 *)&map_views_block.map_views)),tile_x,roll);
            if ((game.message_options & 0x100) == 0) {
              city_notify_dialog_ex((iptr)str_pollution,city,0,0);
            }
          }
        }
      }
    }
  }
  roll = city * 0xb;
  if ((cities[city].flags & 1) != 0) {
    check = city_has_improvement(city,0x15);
    roll = 0;
    if (check != 0) {
      roll = civ_has_advance((int)owner,0x20);
      if (roll == 0) {
        roll = 5 - (uint)game.difficulty;
        if (roll < 1) {
          meltdown_roll = 0;
        }
        else {
          meltdown_roll = _rand();
          roll = meltdown_roll / (int)(6 - (uint)game.difficulty);
          meltdown_roll = meltdown_roll % (int)(6 - (uint)game.difficulty);
        }
        if (meltdown_roll == 0) {
          roll = tile_visible_to((int)cities[city].x,
                                     (int)cities[city].y,human_civ[0]);
          if (roll != 0) {
            mapviews_ensure_visible((int)cities[city].x,
                               (int)cities[city].y,
                               (int)(char)cities[city].owner);
          }
          map_animate_nuke((int)cities[city].x,
                             (int)cities[city].y);
          nuclear_blast((int)cities[city].x,
                             (int)cities[city].y);
          city_set_improvement(city,0x15,0);
          roll = (int)civ_saved_cursor_x_block.autoplay_active;
          if (roll == 0) {
            /* city_notify_dialog is declared void but returns city_notify_dialog_ex's int:
               it is city_notify_dialog_ex(a, b, 0, c) */
            roll = city_notify_dialog_ex((iptr)str_chernobyl,city,0,(iptr)&caption_close_button_sprite_block.city_notify_sprite);
          }
        }
      }
    }
  }
  return roll;
}


/* 0x0058f040 */
uint __cdecl unit_enter_hut(int unit_id)

{
  Tile *tile;
  bool single_spawn;
  byte owner_byte;
  uint civ;
  int x;
  uint y;
  int tmp;
  uint rnd;
  i32 tile_x;
  int check;
  uint sign;
  i32 spawn_type;
  uint outcome;
  int tech_id;
  int settler_count;
  int attempts;
  i32 flat_type;
  i32 chosen_type;
  i32 rough_type;
  int gold2;
  i32 merc_type_a;
  int step;
  i32 merc_type_b;
  int settlers;
  
  owner_byte = units[unit_id].owner;
  civ = (uint)(char)owner_byte;
  x = (int)units[unit_id].x;
  y = (uint)units[unit_id].y;
  outcome = y;
  if ((civ != 0) &&
     (outcome = (int)(char)unit_types[(uint)(byte)units[unit_id].type].domain,
     (int)(char)unit_types[(uint)(byte)units[unit_id].type].domain == 0)) {
    city_find_nearest(x,y,0xffffffff,0xffffffff,0xffffffff);
    tmp = _rand();
    outcome = tmp % 5;
    if ((((((1 << (owner_byte & 0x1f) & (uint)game.human_players) == 0) || (tmp = _rand(), tmp % 3 == 0))
         && ((civs[civ].num_cities != 0 &&
             (tmp = tile_landmass(x,y),
             civs[civ].continent_cities[tmp] == '\0')))) &&
        (((civs[civ].continent_flags[tmp] & 0x7f) == 0 || (0xc < advisor_window_block.nearest_city_dist)))) &&
       (civs[civ].continent_cities[tmp] == '\0')) {
      outcome = 0;
    }
hut_outcome_dispatch:
    switch(outcome) {
    case 0:
      if (advisor_window_block.nearest_city_dist < 4) {
        outcome = 1;
        goto hut_outcome_dispatch;
      }
      if ((civs[civ].num_cities == 0) && (game.turn < 0x32)) {
        settlers = 0;
        for (unit_id = 0; unit_id < game.num_units; unit_id = unit_id + 1) {
          if (((units[unit_id].id != 0) &&
              (unit_types[(uint)(byte)units[unit_id].type].role == '\x05')) &&
             (units[unit_id].home_city == -1)) {
            settlers = settlers + 1;
          }
        }
        if (1 < settlers) {
          outcome = 1;
          goto hut_outcome_dispatch;
        }
      }
      tmp = tile_owner_or_fertility(x,y);
      if (0xb < tmp) {
        if (unit_sound_editor_window_block.unit_move_by_local_human != '\0') {
          popup_game_with_sprite((iptr)str_surprisetribe,(iptr)&popup_info_icon_sprite,0);
        }
        tmp = city_create(x,y,civ);
        if (999 < game.year) {
          check = _rand();
          owner_byte = (byte)(check >> 0x1f);
          cities[tmp].size =
               ((((byte)check ^ owner_byte) - owner_byte & 3 ^ owner_byte) - owner_byte) + '\x01';
          city_set_improvement(tmp,4,1);
          civ = _rand();
          rnd = (int)civ >> 0x1f;
          if (((civ ^ rnd) - rnd & 1 ^ rnd) == rnd) {
            city_set_improvement(tmp,5,1);
          }
          check = _rand();
          if (check % 3 == 0) {
            city_set_improvement(tmp,3,1);
          }
          civ = _rand();
          rnd = (int)civ >> 0x1f;
          if (((civ ^ rnd) - rnd & 3 ^ rnd) == rnd) {
            city_set_improvement(tmp,6,1);
          }
        }
        if (unit_sound_editor_window_block.unit_move_by_local_human == '\0') {
          return 0;
        }
        map_redraw_neighbors_all_views(x,y);
        civ = net_send_message(0x75,0xff,x,y,0,0,0,0,0,0);
        if (tmp < 0) {
          return civ;
        }
        city_window_open(((ScaledWindowView*)((i8 *)&city_window_block.city_window)),tmp);   /* void: the caller ignores our result */
        return civ;
      }
      outcome = 5;
      goto hut_outcome_dispatch;
    case 1:
      if (unit_sound_editor_window_block.unit_move_by_local_human != '\0') {
        popup_game_with_sprite((iptr)str_surprisemercs,(iptr)&popup_info_icon_sprite,0);
      }
      merc_type_a = 0x13;
      if (game.advance_known_by[11] == '\0') {
        tmp = _rand();
        if (tmp % 3 == 0) {
          merc_type_a = 0x10;
        }
        else {
          merc_type_a = 0xf;
        }
        if (game.advance_known_by[64] != '\0') {
          rnd = _rand();
          sign = (int)rnd >> 0x1f;
          if (((rnd ^ sign) - sign & 1 ^ sign) != sign) {
            merc_type_a = 0x11;
          }
        }
      }
      if (game.advance_known_by[55] != '\0') {
        merc_type_a = 0x12;
      }
      if (game.advance_known_by[42] != '\0') {
        merc_type_a = 0x14;
      }
      if (game.advance_known_by[17] != '\0') {
        merc_type_a = 0xb;
      }
      merc_type_b = 8;
      if (game.advance_known_by[34] == '\0') {
        merc_type_b = 7;
      }
      if (game.advance_known_by[35] == '\0') {
        merc_type_b = 5;
      }
      if (game.advance_known_by[39] == '\0') {
        merc_type_b = 4;
      }
      rnd = _rand();
      sign = (int)rnd >> 0x1f;
      if (((rnd ^ sign) - sign & 1 ^ sign) == sign) {
        spawn_type = merc_type_a;
      }
      else {
        spawn_type = merc_type_b;
      }
      tmp = unit_create(spawn_type,civ,x,y);
      if ((unit_sound_editor_window_block.unit_move_by_local_human == '\0') && ((*(uint *)&human_civ) != civ)) {
        outcome = civ;
        if (-1 < tmp) {
          outcome = tmp * 0x20;
          *((i8 *)&units[0].home_city + outcome) = -1;   /* outcome is a byte offset (unit index * 0x20) */
        }
      }
      else {
        map_redraw_neighbors_all_views(x,y);
        outcome = net_send_message(0x75,0xff,x,y,0,0,0,0,0,0);
      }
      break;
    case 2:
      gold2 = 0x32;
      x = _rand();
      if (x % 3 == 0) {
        x = _rand();
        if ((int)((x % 10 - (uint)game.difficulty) + 2) < 5) {
          gold2 = 0x19;
        }
        else {
          gold2 = 100;
        }
      }
      if (1000 < game.year) {
        gold2 = gold2 << 1;
      }
      civs[civ].gold = civs[civ].gold + gold2;
      text_set_number_arg(0,gold2);
      if (unit_sound_editor_window_block.unit_move_by_local_human != '\0') {
        popup_game_with_sprite((iptr)str_surprisemetals,(iptr)&popup_info_icon_sprite,0);
      }
      if ((*(uint *)&human_civ) != civ) {
        return civ;
      }
      status_draw_info(1);   /* void */
      return civ;
    case 3:
      if ((advisor_window_block.nearest_city_dist < 4) ||
         ((civs[civ].num_cities == 0 && (game.turn < 0x32)))) {
        outcome = 1;
        goto hut_outcome_dispatch;
      }
      if (((1 << (owner_byte & 0x1f) & (uint)game.human_players) == 0) &&
         ((byte)game.power_rank[civ] < (byte)game.power_rank[game.field_139])) {
        rnd = _rand();
        sign = (int)rnd >> 0x1f;
        if ((int)(((rnd ^ sign) - sign & 7 ^ sign) - sign) < (int)(uint)game.difficulty) {
          outcome = 0;
          goto hut_outcome_dispatch;
        }
      }
      single_spawn = false;
      if (game.barbarian_activity < 3) {
        if (game.turn < 0x1e) {
check_nearby_city:
          city_find_nearest(x,y,civ,0xffffffff,0xffffffff);
          tmp = tile_landmass(x,y);
          if ((civs[civ].continent_cities[tmp] != '\0') && (advisor_window_block.nearest_city_dist < 0x18)) {
            if (unit_sound_editor_window_block.unit_move_by_local_human == '\0') {
              return 0;
            }
            civ = popup_game_with_sprite((iptr)str_surprisenothing,(iptr)&popup_info_icon_sprite,0);
            return civ;
          }
        }
        else if (game.turn < 0x32) {
          rnd = _rand();
          sign = (int)rnd >> 0x1f;
          if (((rnd ^ sign) - sign & 1 ^ sign) == sign) goto check_nearby_city;
        }
      }
      if (0x31 < game.turn) {
        if (0x4a < game.turn) goto barbarian_surprise;
        rnd = _rand();
        sign = (int)rnd >> 0x1f;
        if (((rnd ^ sign) - sign & 1 ^ sign) != sign) goto barbarian_surprise;
      }
      single_spawn = true;
barbarian_surprise:
      rnd = 0;
      if (unit_sound_editor_window_block.unit_move_by_local_human != '\0') {
        rnd = popup_game_with_sprite((iptr)str_surprisebarb,(iptr)&popup_info_icon_sprite,0);
      }
      step = 0;
      do {
        if (7 < step) {
          return rnd;
        }
        rnd = game.turn + step >> 0x1f;
        tmp = ((game.turn + step ^ rnd) - rnd & 7 ^ rnd) - rnd;
        tile_x = map_wrap_x((char)(((i8 *)&dir_dx_table_block.dir_dx_table))[tmp] + x);
        tmp = (int)(char)(((i8 *)&dir_dy_table_block.dir_dy_table))[tmp] + y;
        check = map_in_bounds(tile_x,tmp);
        if ((((check != 0) && (check = tile_unit_owner(tile_x,tmp), check < 0)) &&
            (check = tile_city_owner(tile_x,tmp), check < 0)) &&
           (check = tile_is_ocean(tile_x,tmp), check == 0)) {
          owner_byte = tile_terrain(tile_x,tmp);
          rough_type = 5;
          flat_type = 0xf;
          if (game.advance_known_by[51] != '\0') {
            rough_type = 7;
            flat_type = 0x13;
          }
          if (game.advance_known_by[unit_types[22].prerequisite] != '\0') {
            rough_type = 0xb;
            flat_type = 0x15;
          }
          if (game.advance_known_by[34] != '\0') {
            rough_type = 8;
            flat_type = 9;
          }
          if ((char)terrain_types[(uint)owner_byte].move_cost < '\x03') {
            chosen_type = flat_type;
          }
          else {
            chosen_type = rough_type;
          }
          rnd = unit_create(chosen_type,0,tile_x,tmp);
          if (-1 < (int)rnd) {
            tile = tile_at(x,y);
            units[rnd].visibility = tile->visible | units[rnd].visibility;
            map_redraw_tile_all_views(tile_x,tmp);
            rnd = (uint)game.multiplayer;
            if (2 < game.multiplayer) {
              rnd = net_send_message(0x72,0xff,tile_x,tmp,0,0,0,0,0,0);
            }
          }
          if (single_spawn) {
            return rnd;
          }
        }
        rnd = int_clamp(4 - civs[civ].num_cities,1,4);
        step = step + rnd;
      } while( true );
    case 4:
      if ((game.turn == 0) || (tmp = civ_has_advance(civ,0x26), tmp != 0)) {
        outcome = 2;
      }
      else {
        attempts = 0;
        tech_id = _rand();
        tech_id = tech_id % 100;
        do {
          tmp = civ_can_research_advance(civ,tech_id);
          if (tmp == 0) {
            rnd = (tech_id + 1) / 100;
            tech_id = (tech_id + 1) % 100;
          }
          else {
            if (unit_sound_editor_window_block.unit_move_by_local_human != '\0') {
              popup_game_with_sprite((iptr)str_surprisescrolls,(iptr)&popup_info_icon_sprite,0);
            }
            civ_give_advance(civ,tech_id,civ,0,0);   /* void */
            tech_id = -1;
          }
          attempts = attempts + 1;
        } while ((attempts < 999) && (-1 < tech_id));
        if (tech_id < 0) {
          return rnd;
        }
        outcome = 0;
      }
      goto hut_outcome_dispatch;
    case 5:
      if (game.advance_known_by[28] == '\0') {
        settler_count = 0;
        for (unit_id = 0; unit_id < game.num_units; unit_id = unit_id + 1) {
          if ((((units[unit_id].id != 0) &&
               ((int)(char)units[unit_id].owner == civ)) &&
              (unit_types[(uint)(byte)units[unit_id].type].role == '\x05')) &&
             (units[unit_id].home_city == -1)) {
            settler_count = settler_count + 1;
          }
        }
        if (settler_count <= (int)civs[civ].num_cities >> 3) {
          if (unit_sound_editor_window_block.unit_move_by_local_human != '\0') {
            popup_game_with_sprite((iptr)str_surprisenomads,(iptr)&popup_info_icon_sprite,0);
          }
          tmp = unit_create(0,civ,x,y);
          if (-1 < tmp) {
            units[tmp].home_city = 0xff;
          }
          if (unit_sound_editor_window_block.unit_move_by_local_human == '\0') {
            return 0;
          }
          map_redraw_neighbors_all_views(x,y);
          civ = net_send_message(0x75,0xff,x,y,0,0,0,0,0,0);
          return civ;
        }
        outcome = 4;
      }
      else {
        outcome = 2;
      }
      goto hut_outcome_dispatch;
    default:
      break;
    }
  }
  return outcome;
}

