/*
 * Large functions whose generated translation contained EBP-relative code
 * (exception-unwind funclets run with the caller's EBP, or a lost stack slot).
 * Bodies follow the generated versions; the funclets are inlined as plain
 * code on the function's own locals, exception bookkeeping is dropped.
 */
#include "game.h"

/* 0x0041ba52: new-game setup dialogs (difficulty, enemies, barbarity, ...).
 * Unwind funclet 0x0041d3f2 destroys the dialog object at EBP-0x320 (local_324). */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __cdecl setup_new_game_dialogs(int param_1)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  i32 uVar4;
  int iVar5;
  i32 uVar6;
  int local_458;
  int local_454;
  int local_450;
  int local_448;
  int local_444;
  i8 local_43c;
  char local_438;
  i8 local_434[260];
  i32 local_330;
  int local_32c;
  int local_328;
  Dialog local_324;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  i32 uStack_10;
  i32 local_8;
  
  local_8 = 0xffffffff;
  local_330 = 1;
  local_28 = 0;
  local_328 = 0;
  dialog_ctor(&local_324,0x2000);
  local_8 = 0;
  leaders_fixup_names();
  game.field_0e = 0;
LAB_0041bab3:
  do {
    do {
      setup_picwnd_show(((i8 *)&setup_picwnd_block.setup_picwnd),3,6,3);
      dlg_load_game_section(&local_324,str_difficulty_2,1);
      dialog_set_default_choice(&local_324,(int)prefs_game_rules_block.prefs_difficulty);
      dialog_set_position(&local_324,
                         ((int)(caption_font_block.screen_width + -0x280 + (caption_font_block.screen_width + -0x280 >> 0x1f & 7U)) >> 3)
                         + 1,-(((int)(caption_font_block.screen_height + -0x1e0 + (caption_font_block.screen_height + -0x1e0 >> 0x1f & 7U))
                               >> 3) + 1));
      local_18 = dlg_show_modal(&local_324,0);
      snd_play_effect(0x6a,0,0,0);
      setup_picwnd_close(((i8 *)&setup_picwnd_block.setup_picwnd));
      if (local_18 < 0) {
LAB_0041d3cf:
        uVar4 = local_330;
        local_8 = 0xffffffff;
        /* inlined unwind funclet 0041d3f2 */ { dialog_dtor((void *)((iptr)&local_324)); }
        return uVar4;
      }
      game.difficulty = (byte)local_18;
      prefs_game_rules_block.prefs_difficulty = (short)local_18;
      setup_picwnd_show(((i8 *)&setup_picwnd_block.setup_picwnd),1,6,4);
      dlg_load_game_section(&local_324,str_enemies,1);
      dialog_set_default_choice(&local_324,(int)prefs_game_rules_block.prefs_enemies_choice);
      dialog_set_position(&local_324,
                         -(((int)(caption_font_block.screen_width + -0x280 + (caption_font_block.screen_width + -0x280 >> 0x1f & 7U)) >> 3
                           ) + 1),-(((int)(caption_font_block.screen_height + -0x1e0 +
                                          (caption_font_block.screen_height + -0x1e0 >> 0x1f & 7U)) >> 3) + 1));
      local_32c = dlg_show_modal(&local_324,0);
      snd_play_effect(0x6a,0,0,0);
      setup_picwnd_close(((i8 *)&setup_picwnd_block.setup_picwnd));
    } while (local_32c < 0);
    if ((int)local_324.result_extra == 0) {
      prefs_game_rules_block.prefs_enemies_choice = (short)local_32c;
      game.num_enemies = 6 - (char)local_32c;
    }
    else {
      iVar2 = _rand();
      game.num_enemies = (char)(iVar2 % 5) + 2;
    }
    setup_picwnd_show(((i8 *)&setup_picwnd_block.setup_picwnd),3,6,5);
    dlg_load_game_section(&local_324,str_barbarity,1);
    dialog_set_default_choice(&local_324,(int)prefs_game_rules_block.prefs_barbarity);
    dialog_set_position(&local_324,
                       ((int)(caption_font_block.screen_width + -0x280 + (caption_font_block.screen_width + -0x280 >> 0x1f & 7U)) >> 3) +
                       1,-(((int)(caption_font_block.screen_height + -0x1e0 + (caption_font_block.screen_height + -0x1e0 >> 0x1f & 7U)) >> 3
                           ) + 1));
    iVar2 = dlg_show_modal(&local_324,0);
    snd_play_effect(0x6a,0,0,0);
    setup_picwnd_close(((i8 *)&setup_picwnd_block.setup_picwnd));
  } while (iVar2 < 0);
  if ((int)local_324.result_extra == 0) {
    local_438 = (char)iVar2;
    game.barbarian_activity = local_438;
    prefs_game_rules_block.prefs_barbarity = (short)iVar2;
  }
  else if (game.difficulty < 2) {
    iVar2 = _rand();
    bVar1 = (byte)(iVar2 >> 0x1f);
    game.barbarian_activity = ((((byte)iVar2 ^ bVar1) - bVar1 & 1 ^ bVar1) - bVar1) + game.difficulty;
  }
  else if (game.difficulty < 5) {
    iVar2 = _rand();
    game.barbarian_activity = (char)(iVar2 % 3) + '\x01';
  }
  else {
    iVar2 = _rand();
    bVar1 = (byte)(iVar2 >> 0x1f);
    game.barbarian_activity = ((((byte)iVar2 ^ bVar1) - bVar1 & 1 ^ bVar1) - bVar1) + '\x02';
  }
  do {
    game.rules = 0x3f;
    setup_picwnd_show(((i8 *)&setup_picwnd_block.setup_picwnd),1,6,9);
    dlg_load_game_section(&local_324,str_rules_2,1);
    dialog_set_default_choice(&local_324,(int)prefs_game_rules_block.prefs_rules_choice);
    dialog_set_position(&local_324,
                       -(((int)(caption_font_block.screen_width + -0x280 + (caption_font_block.screen_width + -0x280 >> 0x1f & 7U)) >> 3)
                        + 1),-(((int)(caption_font_block.screen_height + -0x1e0 + (caption_font_block.screen_height + -0x1e0 >> 0x1f & 7U))
                               >> 3) + 1));
    iVar2 = dlg_show_modal(&local_324,0);
    snd_play_effect(0x6a,0,0,0);
    setup_picwnd_close(((i8 *)&setup_picwnd_block.setup_picwnd));
    if (iVar2 < 0) goto LAB_0041d3cf;
    prefs_game_rules_block.prefs_rules_choice = (short)iVar2;
    if (iVar2 == 0) goto LAB_0041c35d;
    game.rules = prefs_game_rules_block.prefs_game_rules[0];
    if (param_1 == 1) {
      game.rules = prefs_game_rules_block.prefs_game_rules[0] & 0x7fff;
    }
    else if (param_1 == 2) {
      game.rules = prefs_game_rules_block.prefs_game_rules[0] | 0x8000;
    }
    dlg_checks_clear();
    dlg_check_set(0,(uint)((game.rules & 0x10) == 0));
    dlg_check_set(1,game.rules & 0x8000);
    dlg_check_set(2,0);
    dlg_check_set(3,(int)prefs_game_rules_block.prefs_accelerated_start);
    dlg_check_set(4,game.rules & 0x80);
    dlg_check_set(5,game.rules & 0x100);
    setup_picwnd_show(((i8 *)&setup_picwnd_block.setup_picwnd),3,6,9);
    dialog_load_text_section(&local_324,((i32 *)&str_game_7),str_advanced,0,0,0,0,0,0);
    if (((byte)local_324.style_flags & 4) != 0) {
      for (local_30 = 0; local_30 < (int)local_324.option_count; local_30 = local_30 + 1) {
        dialog_set_option_checked(&local_324,local_30,1 << ((byte)local_30 & 0x1f) & dlg_check_bits);
      }
    }
    dialog_set_position(&local_324,
                       ((int)(caption_font_block.screen_width + -0x280 + (caption_font_block.screen_width + -0x280 >> 0x1f & 7U)) >> 3) +
                       1,-(((int)(caption_font_block.screen_height + -0x1e0 + (caption_font_block.screen_height + -0x1e0 >> 0x1f & 7U)) >> 3
                           ) + 1));
    dlg_show_modal(&local_324,0);
    snd_play_effect(0x6a,0,0,0);
    setup_picwnd_close(((i8 *)&setup_picwnd_block.setup_picwnd));
    dlg_help_pressed = (int)local_324.result_extra;
    if (((byte)local_324.style_flags & 4) != 0) {
      dlg_check_bits = 0;
      for (local_30 = 0; local_30 < (int)local_324.option_count; local_30 = local_30 + 1) {
        iVar2 = dialog_option_is_checked(&local_324,local_30);
        if (iVar2 != 0) {
          dlg_check_bits = dlg_check_bits | 1 << ((byte)local_30 & 0x1f);
        }
      }
    }
    game.rules = 0x2f;
    iVar2 = dlg_check_get(0);
    if (iVar2 == 0) {
      game.rules = game.rules | 0x10;
    }
    iVar2 = dlg_check_get(1);
    if (iVar2 != 0) {
      game.rules = game.rules | 0x8000;
    }
    local_28 = dlg_check_get(2);
    local_328 = dlg_check_get(3);
    iVar2 = dlg_check_get(4);
    if (iVar2 != 0) {
      game.rules = game.rules | 0x80;
    }
    iVar2 = dlg_check_get(5);
    if (iVar2 != 0) {
      game.rules = game.rules | 0x100;
    }
    if (param_1 == 0) {
      prefs_game_rules_block.prefs_game_rules[0] = game.rules;
    }
    else {
      prefs_game_rules_block.prefs_game_rules[0] = game.rules & 0x7fff | prefs_game_rules_block.prefs_game_rules[0] & 0x8000;
    }
    if (local_328 == 0) break;
    game.first_launch_turn = 0xffff;
    iVar2 = game_turn_to_year(0);
    if (iVar2 < 1) {
      uVar3 = game_turn_to_year(0);
      local_450 = ~uVar3 + 1;
    }
    else {
      local_450 = game_turn_to_year(0);
    }
    text_set_number_arg(0,local_450);
    iVar2 = game_turn_to_year(0x15);
    if (iVar2 < 1) {
      uVar3 = game_turn_to_year(0x15);
      local_454 = ~uVar3 + 1;
    }
    else {
      local_454 = game_turn_to_year(0x15);
    }
    text_set_number_arg(1,local_454);
    iVar2 = game_turn_to_year(0x29);
    if (iVar2 < 1) {
      uVar3 = game_turn_to_year(0x29);
      local_458 = ~uVar3 + 1;
    }
    else {
      local_458 = game_turn_to_year(0x29);
    }
    text_set_number_arg(2,local_458);
    setup_picwnd_show(((i8 *)&setup_picwnd_block.setup_picwnd),1,6,9);
    dlg_load_game_section(&local_324,str_accelerated,1);
    dialog_set_default_choice(&local_324,(int)prefs_game_rules_block.prefs_accelerated_start);
    dialog_set_position(&local_324,
                       -(((int)(caption_font_block.screen_width + -0x280 + (caption_font_block.screen_width + -0x280 >> 0x1f & 7U)) >> 3)
                        + 1),-(((int)(caption_font_block.screen_height + -0x1e0 + (caption_font_block.screen_height + -0x1e0 >> 0x1f & 7U))
                               >> 3) + 1));
    local_328 = dlg_show_modal(&local_324,0);
    snd_play_effect(0x6a,0,0,0);
    setup_picwnd_close(((i8 *)&setup_picwnd_block.setup_picwnd));
  } while (local_328 < 0);
  prefs_game_rules_block.prefs_accelerated_start = (short)local_328;
LAB_0041c35d:
  do {
    for (local_448 = 0; local_448 < 0x15; local_448 = local_448 + 1) {
      if (leaders[local_448].leader_name < 1) {
        leaders[local_448].leader_name =
             ~leaders[local_448].leader_name + 1;
      }
      if (leaders[local_448].plural < 1) {
        leaders[local_448].plural =
             ~leaders[local_448].plural + 1;
      }
      if (leaders[local_448].adjective < 1) {
        leaders[local_448].adjective =
             ~leaders[local_448].adjective + 1;
      }
      for (local_20 = 0; local_20 < 7; local_20 = local_20 + 1) {
        if (leaders[local_448].titles[local_20][0] < 1) {
          leaders[local_448].titles[local_20][0] =
               ~leaders[local_448].titles[local_20][0] + 1;
        }
        if (leaders[local_448].titles[local_20][1] < 1) {
          leaders[local_448].titles[local_20][1] =
               ~leaders[local_448].titles[local_20][1] + 1;
        }
      }
    }
    setup_picwnd_show(((i8 *)&setup_picwnd_block.setup_picwnd),2,6,6);
    dlg_load_game_section(&local_324,str_gender,1);
    dialog_set_default_choice(&local_324,(int)prefs_game_rules_block.prefs_gender);
    dialog_set_position(&local_324,0xfffffc19,
                       -(((int)(caption_font_block.screen_height + -0x1e0 + (caption_font_block.screen_height + -0x1e0 >> 0x1f & 7U)) >> 3)
                        + 1));
    iVar2 = dlg_show_modal(&local_324,0);
    snd_play_effect(0x6a,0,0,0);
    setup_picwnd_close(((i8 *)&setup_picwnd_block.setup_picwnd));
    if (iVar2 < 0) goto LAB_0041bab3;
    prefs_game_rules_block.prefs_gender = (short)iVar2;
    setup_picwnd_show(((i8 *)&setup_picwnd_block.setup_picwnd),2,6,7);
    local_14 = dialog_load_text(&local_324,((i32 *)&str_game),str_tribe,1);
    if (local_14 != 0) {
      setup_picwnd_close(((i8 *)&setup_picwnd_block.setup_picwnd));
      goto LAB_0041d3cf;
    }
    dialog_set_columns(&local_324,3);
    for (local_448 = 0; local_448 < 0x15; local_448 = local_448 + 1) {
      uVar6 = 0;
      iVar5 = local_448;
      uVar4 = label_string((int)leaders[local_448].plural);
      dialog_add_option(&local_324,uVar4,iVar5,uVar6);
    }
    dialog_set_default_choice(&local_324,(int)prefs_game_rules_block.prefs_tribe);
    dialog_set_position(&local_324,0xfffffc19,
                       -(((int)(caption_font_block.screen_height + -0x1e0 + (caption_font_block.screen_height + -0x1e0 >> 0x1f & 7U)) >> 3)
                        + 1));
    local_1c = dlg_show_modal(&local_324,0);
    snd_play_effect(0x6a,0,0,0);
    setup_picwnd_close(((i8 *)&setup_picwnd_block.setup_picwnd));
    if (-1 < local_1c) {
      game.player_civ = leaders[local_1c].color;
      prefs_game_rules_block.prefs_tribe = (short)local_1c;
      civs[(char)game.player_civ].tribe = prefs_game_rules_block.prefs_tribe;
      civs[(char)game.player_civ].leader_portrait = (i8)local_1c;
      if (iVar2 != 0) {
        civs[(char)game.player_civ].leader_portrait =
             civs[(char)game.player_civ].leader_portrait + '\x15';
      }
      human_civ[0] = (int)(char)game.player_civ;
      game.human_players = (byte)(1 << (game.player_civ & 0x1f));
      local_43c = (i8)iVar2;
      leaders[civs[(char)game.player_civ].tribe].female = local_43c;
      leaders[civs[(char)game.player_civ].tribe].leader_name
           = leaders[civs[(char)game.player_civ].tribe].names[(uint)(byte)(&leaders[0].female)
                          [civs[(char)game.player_civ].tribe * 0x30]];
      uVar4 = label_string((int)leaders[civs[(char)game.player_civ].tribe].leader_name);
      crt_strcpy(&civ_names[(char)game.player_civ].leader_name[0],uVar4);
      leaders[civs[(char)game.player_civ].tribe].leader_name =
           -leaders[civs[(char)game.player_civ].tribe].leader_name;
      if ((int)local_324.result_extra == 0) {
        setup_picwnd_show(((i8 *)&setup_picwnd_block.setup_picwnd),2,6,7);
        dialog_load_text_section(&local_324,((i32 *)&str_game_7),((i32 *)&str_name),0x17,
                           &civ_names[(char)game.player_civ].leader_name[0],0,0,0,1);
        dialog_set_position(&local_324,0xfffffc19,
                           -(((int)(caption_font_block.screen_height + -0x1e0 + (caption_font_block.screen_height + -0x1e0 >> 0x1f & 7U)) >>
                             3) + 1));
        local_14 = dialog_run_modal(&local_324,local_434,0);
        snd_play_effect(0x6a,0,0,0);
        setup_picwnd_close(((i8 *)&setup_picwnd_block.setup_picwnd));
        if (local_14 != 0) goto LAB_0041c35d;
        crt_strcpy(&civ_names[(char)game.player_civ].leader_name[0],local_434);
      }
      else {
        uVar4 = label_string((int)leaders[civs[(char)game.player_civ].tribe].plural);
        crt_strcpy(&civ_names[(char)game.player_civ].tribe_name[0],uVar4);
        uVar4 = label_string((int)leaders[civs[(char)game.player_civ].tribe].adjective);
        crt_strcpy(&civ_names[(char)game.player_civ].adjective[0],uVar4);
        leaders[civs[(char)game.player_civ].tribe].plural =
             -leaders[civs[(char)game.player_civ].tribe].plural;
        leaders[civs[(char)game.player_civ].tribe].adjective =
             -leaders[civs[(char)game.player_civ].tribe].adjective;
        for (local_20 = 0; local_20 < 7; local_20 = local_20 + 1) {
          uVar4 = label_string((int)leaders[civs[(char)game.player_civ].tribe].titles[local_20][iVar2]);
          crt_strcpy(&civ_names[(char)game.player_civ].titles[local_20][0],uVar4);
          leaders[civs[(char)game.player_civ].tribe].titles[local_20][iVar2] =
               -leaders[civs[(char)game.player_civ].tribe].titles[local_20][iVar2]
          ;
        }
        while( true ) {
          while( true ) {
            text_set_string_arg_b(1,&civ_names[(char)game.player_civ].tribe_name[0]);
            text_set_string_arg_b(2,&civ_names[(char)game.player_civ].adjective[0]);
            setup_picwnd_show(((i8 *)&setup_picwnd_block.setup_picwnd),2,6,7);
            local_14 = dialog_load_text_section(&local_324,((i32 *)&str_game_7),str_customtribe,0x17,
                                          &civ_names[(char)game.player_civ].leader_name[0],0,0,0,1);
            if (local_14 != 0) {
              setup_picwnd_close(((i8 *)&setup_picwnd_block.setup_picwnd));
              goto LAB_0041d3cf;
            }
            dialog_set_position(&local_324,0xfffffc19,
                               -(((int)(caption_font_block.screen_height + -0x1e0 + (caption_font_block.screen_height + -0x1e0 >> 0x1f & 7U)
                                       ) >> 3) + 1));
            iVar2 = dlg_show_modal(&local_324,0);
            snd_play_effect(0x6a,0,0,0);
            setup_picwnd_close(((i8 *)&setup_picwnd_block.setup_picwnd));
            if (iVar2 < 0) goto LAB_0041c35d;
            crt_strcpy(&civ_names[(char)game.player_civ].leader_name[0],((i8 *)&minimap_window_block.text_string_args));
            crt_strcpy(&civ_names[(char)game.player_civ].tribe_name[0],((i8 *)&minimap_window_block.text_string_arg1));
            crt_strcpy(&civ_names[(char)game.player_civ].adjective[0],((i8 *)&minimap_window_block.text_string_arg2));
            if ((int)local_324.result_extra != 1) break;
            setup_picwnd_show(((i8 *)&setup_picwnd_block.setup_picwnd),2,6,7);
            local_14 = dlg_load_game_section(&local_324,str_customtribe2,1);
            if (local_14 != 0) {
              setup_picwnd_close(((i8 *)&setup_picwnd_block.setup_picwnd));
              goto LAB_0041d3cf;
            }
            local_14 = 0;
            for (local_20 = 0; local_20 < 7; local_20 = local_20 + 1) {
              text_clear();
              text_append_string_id(government_names[local_20]);
              text_append_colon();
              dialog_add_edit_field(&local_324,((i8 *)&map_views_block.text_buffer),
                                 &civ_names[(char)game.player_civ].titles[local_20][0],0x17);
            }
            dialog_set_position(&local_324,0xfffffc19,
                               -(((int)(caption_font_block.screen_height + -0x1e0 + (caption_font_block.screen_height + -0x1e0 >> 0x1f & 7U)
                                       ) >> 3) + 1));
            iVar2 = dlg_show_modal(&local_324,0);
            if (iVar2 == 0) {
              for (local_20 = 0; local_20 < 7; local_20 = local_20 + 1) {
                crt_strcpy(&civ_names[(char)game.player_civ].titles[local_20][0],
                             ((i8 *)&minimap_window_block.text_string_args) + local_20 * 0x104);
              }
            }
            snd_play_effect(0x6a,0,0,0);
            setup_picwnd_close(((i8 *)&setup_picwnd_block.setup_picwnd));
          }
          if ((int)local_324.result_extra != 2) break;
          portrait_dlg_show((int)(char)game.player_civ);
        }
      }
LAB_0041cfad:
      setup_picwnd_show(((i8 *)&setup_picwnd_block.setup_picwnd),1,6,8);
      dlg_load_game_section(&local_324,str_customcity,0x20001);
      for (local_444 = 0; local_444 < 4; local_444 = local_444 + 1) {
        uVar4 = label_string(*(i32 *)(label_string_ids + 0x3d8 + local_444 * 4));
        dialog_add_sprite(&local_324,local_444 * 0x1e0 + (iptr)(((u8 *)&gfx_sheet_surface_block.city_walled_sprites + 360)),local_444,uVar4);
      }
      dialog_set_default_choice(&local_324,
                         (int)leaders[civs[(char)game.player_civ].tribe].city_style);
      dialog_set_position(&local_324,
                         -(((int)(caption_font_block.screen_width + -0x280 + (caption_font_block.screen_width + -0x280 >> 0x1f & 7U)) >> 3
                           ) + 1),-(((int)(caption_font_block.screen_height + -0x1e0 +
                                          (caption_font_block.screen_height + -0x1e0 >> 0x1f & 7U)) >> 3) + 1));
      iVar2 = dlg_show_modal(&local_324,0);
      snd_play_effect(0x6a,0,0,0);
      setup_picwnd_close(((i8 *)&setup_picwnd_block.setup_picwnd));
      if (-1 < iVar2) {
        civ_names[(char)game.player_civ].city_style = (short)iVar2;
        game.civs_alive = game.human_players | 1;
        for (local_20 = 0; local_20 < (int)(uint)game.num_enemies; local_20 = local_20 + 1) {
          iVar2 = _rand();
          (*(i8 *)((char *)&local_448 + 0)) = (byte)(iVar2 >> 0x1f);
          (*(i8 *)((char *)&local_448 + 0)) =
               (((byte)iVar2 ^ (byte)local_448) - (byte)local_448 & 7 ^ (byte)local_448) -
               (byte)local_448;
          if ((1 << ((byte)local_448 & 0x1f) & (uint)game.civs_alive) == 0) {
            game.civs_alive = game.civs_alive | (byte)(1 << ((byte)local_448 & 0x1f));
          }
          else {
            local_20 = local_20 + -1;
          }
        }
        if (local_28 != 0) {
          local_24 = 0;
          local_448 = 1;
          do {
            if (7 < local_448) break;
            if (((1 << ((byte)local_448 & 0x1f) & (uint)game.human_players) == 0) &&
               ((1 << ((byte)local_448 & 0x1f) & (uint)game.civs_alive) != 0)) {
              local_24 = local_24 + 1;
              text_set_number_arg(0,local_24);
              setup_picwnd_show(((i8 *)&setup_picwnd_block.setup_picwnd),2,6,9);
              dlg_load_game_section(&local_324,str_opponent,1);
              *(i32 *)((int)local_324.option_list + 4) = 0x15;
              for (local_2c = 0; local_2c < 0x15; local_2c = local_2c + 1) {
                if (leaders[local_2c].color == local_448) {
                  text_clear();
                  text_append_string_id((int)leaders[local_2c].plural);
                  text_append_space();
                  text_append_lparen();
                  text_append_string_id((int)leaders[local_2c].leader_name);
                  text_append_rparen();
                  dialog_add_option(&local_324,((i8 *)&map_views_block.text_buffer),local_2c,0);
                }
              }
              dialog_set_position(&local_324,0xfffffc19,
                                 -(((int)(caption_font_block.screen_height + -0x1e0 +
                                         (caption_font_block.screen_height + -0x1e0 >> 0x1f & 7U)) >> 3) + 1));
              local_2c = dlg_show_modal(&local_324,0);
              snd_play_effect(0x6a,0,0,0);
              setup_picwnd_close(((i8 *)&setup_picwnd_block.setup_picwnd));
              if (local_2c < 0) goto LAB_0041cfad;
              if (local_2c < 0x15) {
                (((i8 *)&setup_chosen_leaders))[local_448] = (i8)local_2c;
              }
            }
            local_448 = local_448 + 1;
          } while( true );
        }
        prefs_save_civ2dat();
        rules_load_advances(1);
        rules_load_units(1);
        rules_load_improvements(1);
        snd_menu_end();
        map_generate(param_1);
        game_init_new();
        if (local_328 != 0) {
          game_accelerated_start(local_328 + -1);
        }
        civ_intro_popup((int)(char)game.player_civ);
        local_330 = 0;
        goto LAB_0041d3cf;
      }
    }
  } while( true );
}

/* 0x004d17bf: unwind funclet 0x004d4a11 destroys the control at EBP-0x12c (local_130). */
i32 __thiscall spaceship_wnd_render_ship(void *this)

{
  byte bVar1;
  int iVar2;
  i8 local_d88[16];
  i8 local_d78[16];
  i8 local_d68[16];
  i32 local_d58;
  i8 local_d54[16];
  i32 local_d44;
  i32 local_d40;
  i32 local_d3c;
  i32 local_d38;
  i32 local_d34;
  i32 local_d30;
  i32 local_d2c;
  i32 local_d28;
  i32 local_d24;
  i32 local_d20;
  i32 local_d1c;
  i8 local_d18[72];
  i8 local_cd0[72];
  struct { u8 kind; u8 count; u8 pad[2]; i32 v[6]; } part_rows[88];  /* the spaceship structure rows */
  i8 local_2e8[72];
  int local_2a0;
  i8 local_29c[72];
  i8 local_254[72];
  i8 local_20c[72];
  i8 local_1c4[72];
  int local_17c;
  i8 local_178[72];
  i8 local_130[72];
  i8 local_e8[72];
  i8 local_a0[72];
  i8 local_58[72];
  i32 uStack_10;
  int local_8;
  
  local_8 = 0xffffffff;
  surface_ctor(local_2e8);
  local_8 = 0;
  surface_ctor(local_29c);
  (*(i8 *)((char *)&local_8 + 0)) = 1;
  surface_ctor(local_1c4);
  (*(i8 *)((char *)&local_8 + 0)) = 2;
  surface_ctor(local_58);
  (*(i8 *)((char *)&local_8 + 0)) = 3;
  surface_ctor(local_d18);
  (*(i8 *)((char *)&local_8 + 0)) = 4;
  surface_ctor(local_cd0);
  (*(i8 *)((char *)&local_8 + 0)) = 5;
  surface_ctor(local_130);
  (*(i8 *)((char *)&local_8 + 0)) = 6;
  surface_ctor(local_178);
  (*(i8 *)((char *)&local_8 + 0)) = 7;
  surface_ctor(local_20c);
  (*(i8 *)((char *)&local_8 + 0)) = 8;
  surface_ctor(local_254);
  (*(i8 *)((char *)&local_8 + 0)) = 9;
  surface_ctor(local_e8);
  (*(i8 *)((char *)&local_8 + 0)) = 10;
  surface_ctor(local_a0);
  (*(i8 *)((char *)&local_8 + 0)) = 0xb;
  part_rows[0].kind = 2;
  part_rows[0].count = 6;
  part_rows[0].v[0] = 0x1cf;
  part_rows[0].v[1] = 0xb2;
  part_rows[0].v[2] = 0xaa;
  part_rows[0].v[3] = 0x2b;
  part_rows[0].v[4] = 0x33;
  part_rows[0].v[5] = 0x204;
  part_rows[1].kind = 2;
  part_rows[1].count = 6;
  part_rows[1].v[0] = 0x1d0;
  part_rows[1].v[1] = 0x189;
  part_rows[1].v[2] = 0x68;
  part_rows[1].v[3] = 0x3d;
  part_rows[1].v[4] = 0x28;
  part_rows[1].v[5] = 0x230;
  part_rows[2].kind = 0;
  part_rows[2].count = 7;
  part_rows[2].v[0] = 0x197;
  part_rows[2].v[1] = 0x1df;
  part_rows[2].v[2] = 0x13c;
  part_rows[2].v[3] = 0x3a;
  part_rows[2].v[4] = 0x22;
  part_rows[2].v[5] = 0x44;
  part_rows[3].kind = 2;
  part_rows[3].count = 2;
  part_rows[3].v[0] = 0x1c9;
  part_rows[3].v[1] = 0x1de;
  part_rows[3].v[2] = 0x144;
  part_rows[3].v[3] = 0x19;
  part_rows[3].v[4] = 0x36;
  part_rows[3].v[5] = 0x92;
  part_rows[4].kind = 2;
  part_rows[4].count = 2;
  part_rows[4].v[0] = 0x1ca;
  part_rows[4].v[1] = 0x1fa;
  part_rows[4].v[2] = 0x139;
  part_rows[4].v[3] = 0x26;
  part_rows[4].v[4] = 0x27;
  part_rows[4].v[5] = 0xac;
  part_rows[5].kind = 0;
  part_rows[5].count = 9;
  part_rows[5].v[0] = 0x199;
  part_rows[5].v[1] = 0x1e2;
  part_rows[5].v[2] = 0x145;
  part_rows[5].v[3] = 0x42;
  part_rows[5].v[4] = 0x37;
  part_rows[5].v[5] = 0x7f;
  part_rows[6].kind = 1;
  part_rows[6].count = 2;
  part_rows[6].v[0] = 0x1bb;
  part_rows[6].v[1] = 0x1df;
  part_rows[6].v[2] = 0x13f;
  part_rows[6].v[3] = 0x4d;
  part_rows[6].v[4] = 0x4e;
  part_rows[6].v[5] = 0x69;
  part_rows[7].kind = 0;
  part_rows[7].count = 0;
  part_rows[7].v[0] = 0x190;
  part_rows[7].v[1] = 0x138;
  part_rows[7].v[2] = 0x9d;
  part_rows[7].v[3] = 0xfd;
  part_rows[7].v[4] = 0xf0;
  part_rows[7].v[5] = 0x0;
  part_rows[8].kind = 0;
  part_rows[8].count = 1;
  part_rows[8].v[0] = 0x191;
  part_rows[8].v[1] = 0x138;
  part_rows[8].v[2] = 0x9d;
  part_rows[8].v[3] = 0xfd;
  part_rows[8].v[4] = 0xf0;
  part_rows[8].v[5] = 0x0;
  part_rows[9].kind = 0;
  part_rows[9].count = 2;
  part_rows[9].v[0] = 0x192;
  part_rows[9].v[1] = 0x138;
  part_rows[9].v[2] = 0x9d;
  part_rows[9].v[3] = 0xfd;
  part_rows[9].v[4] = 0xf0;
  part_rows[9].v[5] = 0x0;
  part_rows[10].kind = 0;
  part_rows[10].count = 3;
  part_rows[10].v[0] = 0x193;
  part_rows[10].v[1] = 0x138;
  part_rows[10].v[2] = 0x9d;
  part_rows[10].v[3] = 0xfd;
  part_rows[10].v[4] = 0xf0;
  part_rows[10].v[5] = 0x0;
  part_rows[11].kind = 0;
  part_rows[11].count = 4;
  part_rows[11].v[0] = 0x194;
  part_rows[11].v[1] = 0x138;
  part_rows[11].v[2] = 0x9d;
  part_rows[11].v[3] = 0xfd;
  part_rows[11].v[4] = 0xf0;
  part_rows[11].v[5] = 0x0;
  part_rows[12].kind = 0;
  part_rows[12].count = 6;
  part_rows[12].v[0] = 0x196;
  part_rows[12].v[1] = 0x138;
  part_rows[12].v[2] = 0x9d;
  part_rows[12].v[3] = 0xfd;
  part_rows[12].v[4] = 0xf0;
  part_rows[12].v[5] = 0x0;
  part_rows[13].kind = 0;
  part_rows[13].count = 8;
  part_rows[13].v[0] = 0x198;
  part_rows[13].v[1] = 0x138;
  part_rows[13].v[2] = 0x9d;
  part_rows[13].v[3] = 0xfd;
  part_rows[13].v[4] = 0xf0;
  part_rows[13].v[5] = 0x0;
  part_rows[14].kind = 0;
  part_rows[14].count = 10;
  part_rows[14].v[0] = 0x19a;
  part_rows[14].v[1] = 0x138;
  part_rows[14].v[2] = 0x9d;
  part_rows[14].v[3] = 0xfd;
  part_rows[14].v[4] = 0xf0;
  part_rows[14].v[5] = 0x0;
  part_rows[15].kind = 0;
  part_rows[15].count = 12;
  part_rows[15].v[0] = 0x19c;
  part_rows[15].v[1] = 0x138;
  part_rows[15].v[2] = 0x9d;
  part_rows[15].v[3] = 0xfd;
  part_rows[15].v[4] = 0xf0;
  part_rows[15].v[5] = 0x0;
  part_rows[16].kind = 0;
  part_rows[16].count = 14;
  part_rows[16].v[0] = 0x19e;
  part_rows[16].v[1] = 0x137;
  part_rows[16].v[2] = 0x9d;
  part_rows[16].v[3] = 0xfe;
  part_rows[16].v[4] = 0xf0;
  part_rows[16].v[5] = 0x0;
  part_rows[17].kind = 0;
  part_rows[17].count = 16;
  part_rows[17].v[0] = 0x1a0;
  part_rows[17].v[1] = 0x137;
  part_rows[17].v[2] = 0x9d;
  part_rows[17].v[3] = 0xfe;
  part_rows[17].v[4] = 0xf0;
  part_rows[17].v[5] = 0x0;
  part_rows[18].kind = 0;
  part_rows[18].count = 18;
  part_rows[18].v[0] = 0x1a2;
  part_rows[18].v[1] = 0x137;
  part_rows[18].v[2] = 0x9d;
  part_rows[18].v[3] = 0xfe;
  part_rows[18].v[4] = 0xf0;
  part_rows[18].v[5] = 0x0;
  part_rows[19].kind = 0;
  part_rows[19].count = 20;
  part_rows[19].v[0] = 0x1a5;
  part_rows[19].v[1] = 0x137;
  part_rows[19].v[2] = 0x9d;
  part_rows[19].v[3] = 0xfe;
  part_rows[19].v[4] = 0xf0;
  part_rows[19].v[5] = 0x0;
  part_rows[20].kind = 0;
  part_rows[20].count = 22;
  part_rows[20].v[0] = 0x1a8;
  part_rows[20].v[1] = 0x137;
  part_rows[20].v[2] = 0x9d;
  part_rows[20].v[3] = 0x115;
  part_rows[20].v[4] = 0xf0;
  part_rows[20].v[5] = 0x0;
  part_rows[21].kind = 0;
  part_rows[21].count = 23;
  part_rows[21].v[0] = 0x1a9;
  part_rows[21].v[1] = 0xbb;
  part_rows[21].v[2] = 0x72;
  part_rows[21].v[3] = 0x191;
  part_rows[21].v[4] = 0x11b;
  part_rows[21].v[5] = 0x0;
  part_rows[22].kind = 0;
  part_rows[22].count = 24;
  part_rows[22].v[0] = 0x1aa;
  part_rows[22].v[1] = 0xbb;
  part_rows[22].v[2] = 0x72;
  part_rows[22].v[3] = 0x191;
  part_rows[22].v[4] = 0x11b;
  part_rows[22].v[5] = 0x0;
  part_rows[23].kind = 0;
  part_rows[23].count = 25;
  part_rows[23].v[0] = 0x1ab;
  part_rows[23].v[1] = 0xba;
  part_rows[23].v[2] = 0x72;
  part_rows[23].v[3] = 0x192;
  part_rows[23].v[4] = 0x11b;
  part_rows[23].v[5] = 0x0;
  part_rows[24].kind = 0;
  part_rows[24].count = 26;
  part_rows[24].v[0] = 0x1ac;
  part_rows[24].v[1] = 0xba;
  part_rows[24].v[2] = 0x72;
  part_rows[24].v[3] = 0x192;
  part_rows[24].v[4] = 0x11b;
  part_rows[24].v[5] = 0x0;
  part_rows[25].kind = 0;
  part_rows[25].count = 27;
  part_rows[25].v[0] = 0x1ad;
  part_rows[25].v[1] = 0xbb;
  part_rows[25].v[2] = 0x72;
  part_rows[25].v[3] = 0x191;
  part_rows[25].v[4] = 0x11b;
  part_rows[25].v[5] = 0x0;
  part_rows[26].kind = 0;
  part_rows[26].count = 28;
  part_rows[26].v[0] = 0x1ae;
  part_rows[26].v[1] = 0xbb;
  part_rows[26].v[2] = 0x72;
  part_rows[26].v[3] = 0x191;
  part_rows[26].v[4] = 0x11b;
  part_rows[26].v[5] = 0x0;
  part_rows[27].kind = 0;
  part_rows[27].count = 30;
  part_rows[27].v[0] = 0x1b1;
  part_rows[27].v[1] = 0xbb;
  part_rows[27].v[2] = 0x72;
  part_rows[27].v[3] = 0x191;
  part_rows[27].v[4] = 0x11b;
  part_rows[27].v[5] = 0x0;
  part_rows[28].kind = 0;
  part_rows[28].count = 32;
  part_rows[28].v[0] = 0x1b4;
  part_rows[28].v[1] = 0xbb;
  part_rows[28].v[2] = 0x72;
  part_rows[28].v[3] = 0x191;
  part_rows[28].v[4] = 0x11b;
  part_rows[28].v[5] = 0x0;
  part_rows[29].kind = 0;
  part_rows[29].count = 36;
  part_rows[29].v[0] = 0x1b7;
  part_rows[29].v[1] = 0xbb;
  part_rows[29].v[2] = 0x72;
  part_rows[29].v[3] = 0x191;
  part_rows[29].v[4] = 0x11b;
  part_rows[29].v[5] = 0x0;
  part_rows[30].kind = 0;
  part_rows[30].count = 38;
  part_rows[30].v[0] = 0x1b8;
  part_rows[30].v[1] = 0xba;
  part_rows[30].v[2] = 0x72;
  part_rows[30].v[3] = 0x192;
  part_rows[30].v[4] = 0x11b;
  part_rows[30].v[5] = 0x0;
  part_rows[31].kind = 1;
  part_rows[31].count = 6;
  part_rows[31].v[0] = 0x1c1;
  part_rows[31].v[1] = 0x1ba;
  part_rows[31].v[2] = 0x75;
  part_rows[31].v[3] = 0x21;
  part_rows[31].v[4] = 0x2b;
  part_rows[31].v[5] = 0x1ce;
  part_rows[32].kind = 5;
  part_rows[32].count = 4;
  part_rows[32].v[0] = 0x1f0;
  part_rows[32].v[1] = 0x18e;
  part_rows[32].v[2] = 0xa5;
  part_rows[32].v[3] = 0x30;
  part_rows[32].v[4] = 0x16;
  part_rows[32].v[5] = 0x190;
  part_rows[33].kind = 3;
  part_rows[33].count = 3;
  part_rows[33].v[0] = 0x1d9;
  part_rows[33].v[1] = 0x17d;
  part_rows[33].v[2] = 0xa4;
  part_rows[33].v[3] = 0x3e;
  part_rows[33].v[4] = 0x35;
  part_rows[33].v[5] = 0xd2;
  part_rows[34].kind = 4;
  part_rows[34].count = 4;
  part_rows[34].v[0] = 0x1e7;
  part_rows[34].v[1] = 0x1c5;
  part_rows[34].v[2] = 0xa9;
  part_rows[34].v[3] = 0x30;
  part_rows[34].v[4] = 0x24;
  part_rows[34].v[5] = 0x168;
  part_rows[35].kind = 4;
  part_rows[35].count = 3;
  part_rows[35].v[0] = 0x1e5;
  part_rows[35].v[1] = 0x1e0;
  part_rows[35].v[2] = 0xbd;
  part_rows[35].v[3] = 0x32;
  part_rows[35].v[4] = 0x24;
  part_rows[35].v[5] = 0x103;
  part_rows[36].kind = 5;
  part_rows[36].count = 4;
  part_rows[36].v[0] = 0x1f1;
  part_rows[36].v[1] = 0x1ad;
  part_rows[36].v[2] = 0xb4;
  part_rows[36].v[3] = 0x47;
  part_rows[36].v[4] = 0x26;
  part_rows[36].v[5] = 0x1c1;
  part_rows[37].kind = 4;
  part_rows[37].count = 1;
  part_rows[37].v[0] = 0x1e1;
  part_rows[37].v[1] = 0x1fc;
  part_rows[37].v[2] = 0xd2;
  part_rows[37].v[3] = 0x2b;
  part_rows[37].v[4] = 0x20;
  part_rows[37].v[5] = 0x30;
  part_rows[38].kind = 4;
  part_rows[38].count = 2;
  part_rows[38].v[0] = 0x1e3;
  part_rows[38].v[1] = 0x211;
  part_rows[38].v[2] = 0xe1;
  part_rows[38].v[3] = 0x37;
  part_rows[38].v[4] = 0x2a;
  part_rows[38].v[5] = 0x96;
  part_rows[39].kind = 5;
  part_rows[39].count = 2;
  part_rows[39].v[0] = 0x1ec;
  part_rows[39].v[1] = 0x1af;
  part_rows[39].v[2] = 0xc7;
  part_rows[39].v[3] = 0x4a;
  part_rows[39].v[4] = 0x24;
  part_rows[39].v[5] = 0x97;
  part_rows[40].kind = 3;
  part_rows[40].count = 2;
  part_rows[40].v[0] = 0x1d7;
  part_rows[40].v[1] = 0x1af;
  part_rows[40].v[2] = 0xce;
  part_rows[40].v[3] = 0x45;
  part_rows[40].v[4] = 0x3a;
  part_rows[40].v[5] = 0x4a;
  part_rows[41].kind = 5;
  part_rows[41].count = 2;
  part_rows[41].v[0] = 0x1ed;
  part_rows[41].v[1] = 0x1ca;
  part_rows[41].v[2] = 0xe9;
  part_rows[41].v[3] = 0x50;
  part_rows[41].v[4] = 0x2f;
  part_rows[41].v[5] = 0xe2;
  part_rows[42].kind = 1;
  part_rows[42].count = 6;
  part_rows[42].v[0] = 0x1c0;
  part_rows[42].v[1] = 0xb2;
  part_rows[42].v[2] = 0xc8;
  part_rows[42].v[3] = 0x3e;
  part_rows[42].v[4] = 0x28;
  part_rows[42].v[5] = 0x18f;
  part_rows[43].kind = 5;
  part_rows[43].count = 3;
  part_rows[43].v[0] = 0x1ee;
  part_rows[43].v[1] = 0x12c;
  part_rows[43].v[2] = 0xc5;
  part_rows[43].v[3] = 0x12;
  part_rows[43].v[4] = 0x18;
  part_rows[43].v[5] = 0x133;
  part_rows[44].kind = 3;
  part_rows[44].count = 4;
  part_rows[44].v[0] = 0x1d8;
  part_rows[44].v[1] = 0x136;
  part_rows[44].v[2] = 0xbc;
  part_rows[44].v[3] = 0x41;
  part_rows[44].v[4] = 0x38;
  part_rows[44].v[5] = 0x90;
  part_rows[45].kind = 5;
  part_rows[45].count = 1;
  part_rows[45].v[0] = 0x1ea;
  part_rows[45].v[1] = 0x153;
  part_rows[45].v[2] = 0xe8;
  part_rows[45].v[3] = 0x25;
  part_rows[45].v[4] = 0x29;
  part_rows[45].v[5] = 0x1;
  part_rows[46].kind = 5;
  part_rows[46].count = 3;
  part_rows[46].v[0] = 0x1ef;
  part_rows[46].v[1] = 0x12c;
  part_rows[46].v[2] = 0xd9;
  part_rows[46].v[3] = 0x49;
  part_rows[46].v[4] = 0x3c;
  part_rows[46].v[5] = 0x146;
  part_rows[47].kind = 3;
  part_rows[47].count = 1;
  part_rows[47].v[0] = 0x1d6;
  part_rows[47].v[1] = 0x164;
  part_rows[47].v[2] = 0xe9;
  part_rows[47].v[3] = 0x48;
  part_rows[47].v[4] = 0x40;
  part_rows[47].v[5] = 0x1;
  part_rows[48].kind = 5;
  part_rows[48].count = 1;
  part_rows[48].v[0] = 0x1eb;
  part_rows[48].v[1] = 0x15e;
  part_rows[48].v[2] = 0xfb;
  part_rows[48].v[3] = 0x6f;
  part_rows[48].v[4] = 0x45;
  part_rows[48].v[5] = 0x27;
  part_rows[49].kind = 4;
  part_rows[49].count = 4;
  part_rows[49].v[0] = 0x1e6;
  part_rows[49].v[1] = 0x109;
  part_rows[49].v[2] = 0xed;
  part_rows[49].v[3] = 0x31;
  part_rows[49].v[4] = 0x2c;
  part_rows[49].v[5] = 0x136;
  part_rows[50].kind = 4;
  part_rows[50].count = 3;
  part_rows[50].v[0] = 0x1e4;
  part_rows[50].v[1] = 0x11f;
  part_rows[50].v[2] = 0x107;
  part_rows[50].v[3] = 0x34;
  part_rows[50].v[4] = 0x2e;
  part_rows[50].v[5] = 0xce;
  part_rows[51].kind = 4;
  part_rows[51].count = 1;
  part_rows[51].v[0] = 0x1e0;
  part_rows[51].v[1] = 0x137;
  part_rows[51].v[2] = 0x122;
  part_rows[51].v[3] = 0x2e;
  part_rows[51].v[4] = 0x28;
  part_rows[51].v[5] = 0x1;
  part_rows[52].kind = 4;
  part_rows[52].count = 2;
  part_rows[52].v[0] = 0x1e2;
  part_rows[52].v[1] = 0x148;
  part_rows[52].v[2] = 0x136;
  part_rows[52].v[3] = 0x39;
  part_rows[52].v[4] = 0x35;
  part_rows[52].v[5] = 0x5c;
  part_rows[53].kind = 2;
  part_rows[53].count = 8;
  part_rows[53].v[0] = 0x1d4;
  part_rows[53].v[1] = 0x20e;
  part_rows[53].v[2] = 0xf6;
  part_rows[53].v[3] = 0x51;
  part_rows[53].v[4] = 0x36;
  part_rows[53].v[5] = 0x334;
  part_rows[54].kind = 0;
  part_rows[54].count = 33;
  part_rows[54].v[0] = 0x1b6;
  part_rows[54].v[1] = 0x24b;
  part_rows[54].v[2] = 0x114;
  part_rows[54].v[3] = 0x15;
  part_rows[54].v[4] = 0x19;
  part_rows[54].v[5] = 0x2d1;
  part_rows[55].kind = 1;
  part_rows[55].count = 8;
  part_rows[55].v[0] = 0x1c5;
  part_rows[55].v[1] = 0x246;
  part_rows[55].v[2] = 0x111;
  part_rows[55].v[3] = 0x2f;
  part_rows[55].v[4] = 0x2b;
  part_rows[55].v[5] = 0x285;
  part_rows[56].kind = 0;
  part_rows[56].count = 31;
  part_rows[56].v[0] = 0x1b3;
  part_rows[56].v[1] = 0x210;
  part_rows[56].v[2] = 0xfd;
  part_rows[56].v[3] = 0x30;
  part_rows[56].v[4] = 0x26;
  part_rows[56].v[5] = 0x282;
  part_rows[57].kind = 2;
  part_rows[57].count = 7;
  part_rows[57].v[0] = 0x1d2;
  part_rows[57].v[1] = 0x1f7;
  part_rows[57].v[2] = 0x102;
  part_rows[57].v[3] = 0x4d;
  part_rows[57].v[4] = 0x3a;
  part_rows[57].v[5] = 0x2ab;
  part_rows[58].kind = 0;
  part_rows[58].count = 29;
  part_rows[58].v[0] = 0x1b0;
  part_rows[58].v[1] = 0x22d;
  part_rows[58].v[2] = 0x123;
  part_rows[58].v[3] = 0x19;
  part_rows[58].v[4] = 0x19;
  part_rows[58].v[5] = 0x243;
  part_rows[59].kind = 1;
  part_rows[59].count = 7;
  part_rows[59].v[0] = 0x1c3;
  part_rows[59].v[1] = 0x228;
  part_rows[59].v[2] = 0x11d;
  part_rows[59].v[3] = 0x2f;
  part_rows[59].v[4] = 0x2e;
  part_rows[59].v[5] = 0x222;
  part_rows[60].kind = 2;
  part_rows[60].count = 5;
  part_rows[60].v[0] = 0x1ce;
  part_rows[60].v[1] = 0x1f1;
  part_rows[60].v[2] = 0xfd;
  part_rows[60].v[3] = 0x4e;
  part_rows[60].v[4] = 0x39;
  part_rows[60].v[5] = 0x1b5;
  part_rows[61].kind = 0;
  part_rows[61].count = 21;
  part_rows[61].v[0] = 0x1a7;
  part_rows[61].v[1] = 0x228;
  part_rows[61].v[2] = 0x11d;
  part_rows[61].v[3] = 0x18;
  part_rows[61].v[4] = 0x1a;
  part_rows[61].v[5] = 0x20c;
  part_rows[62].kind = 1;
  part_rows[62].count = 5;
  part_rows[62].v[0] = 0x1bf;
  part_rows[62].v[1] = 0x224;
  part_rows[62].v[2] = 0x118;
  part_rows[62].v[3] = 0x31;
  part_rows[62].v[4] = 0x2e;
  part_rows[62].v[5] = 0x15d;
  part_rows[63].kind = 0;
  part_rows[63].count = 19;
  part_rows[63].v[0] = 0x1a4;
  part_rows[63].v[1] = 0x1f0;
  part_rows[63].v[2] = 0x107;
  part_rows[63].v[3] = 0x34;
  part_rows[63].v[4] = 0x35;
  part_rows[63].v[5] = 0x1b9;
  part_rows[64].kind = 2;
  part_rows[64].count = 1;
  part_rows[64].v[0] = 0x1c8;
  part_rows[64].v[1] = 0x1da;
  part_rows[64].v[2] = 0x10b;
  part_rows[64].v[3] = 0x4b;
  part_rows[64].v[4] = 0x41;
  part_rows[64].v[5] = 0x46;
  part_rows[65].kind = 0;
  part_rows[65].count = 11;
  part_rows[65].v[0] = 0x19b;
  part_rows[65].v[1] = 0x1cf;
  part_rows[65].v[2] = 0x108;
  part_rows[65].v[3] = 0x42;
  part_rows[65].v[4] = 0x3d;
  part_rows[65].v[5] = 0xc2;
  part_rows[66].kind = 2;
  part_rows[66].count = 3;
  part_rows[66].v[0] = 0x1cb;
  part_rows[66].v[1] = 0x1ce;
  part_rows[66].v[2] = 0x109;
  part_rows[66].v[3] = 0x4d;
  part_rows[66].v[4] = 0x40;
  part_rows[66].v[5] = 0xd3;
  part_rows[67].kind = 2;
  part_rows[67].count = 1;
  part_rows[67].v[0] = 0x1c7;
  part_rows[67].v[1] = 0x1bc;
  part_rows[67].v[2] = 0x11b;
  part_rows[67].v[3] = 0x44;
  part_rows[67].v[4] = 0x44;
  part_rows[67].v[5] = 0x1;
  part_rows[68].kind = 0;
  part_rows[68].count = 5;
  part_rows[68].v[0] = 0x195;
  part_rows[68].v[1] = 0x1e4;
  part_rows[68].v[2] = 0x12f;
  part_rows[68].v[3] = 0x42;
  part_rows[68].v[4] = 0x31;
  part_rows[68].v[5] = 0x1;
  part_rows[69].kind = 0;
  part_rows[69].count = 13;
  part_rows[69].v[0] = 0x19d;
  part_rows[69].v[1] = 0x1fb;
  part_rows[69].v[2] = 0x12b;
  part_rows[69].v[3] = 0x20;
  part_rows[69].v[4] = 0x1f;
  part_rows[69].v[5] = 0x105;
  part_rows[70].kind = 1;
  part_rows[70].count = 1;
  part_rows[70].v[0] = 0x1ba;
  part_rows[70].v[1] = 0x204;
  part_rows[70].v[2] = 0x129;
  part_rows[70].v[3] = 0x2f;
  part_rows[70].v[4] = 0x33;
  part_rows[70].v[5] = 0x39;
  part_rows[71].kind = 1;
  part_rows[71].count = 3;
  part_rows[71].v[0] = 0x1bc;
  part_rows[71].v[1] = 0x1f9;
  part_rows[71].v[2] = 0x125;
  part_rows[71].v[3] = 0x37;
  part_rows[71].v[4] = 0x35;
  part_rows[71].v[5] = 0xb7;
  part_rows[72].kind = 1;
  part_rows[72].count = 1;
  part_rows[72].v[0] = 0x1b9;
  part_rows[72].v[1] = 0x1df;
  part_rows[72].v[2] = 0x13e;
  part_rows[72].v[3] = 0x33;
  part_rows[72].v[4] = 0x34;
  part_rows[72].v[5] = 0x1;
  part_rows[73].kind = 0;
  part_rows[73].count = 19;
  part_rows[73].v[0] = 0x1a3;
  part_rows[73].v[1] = 0x1be;
  part_rows[73].v[2] = 0x11f;
  part_rows[73].v[3] = 0x2c;
  part_rows[73].v[4] = 0x40;
  part_rows[73].v[5] = 0x18c;
  part_rows[74].kind = 2;
  part_rows[74].count = 5;
  part_rows[74].v[0] = 0x1cd;
  part_rows[74].v[1] = 0x1ac;
  part_rows[74].v[2] = 0x117;
  part_rows[74].v[3] = 0x42;
  part_rows[74].v[4] = 0x46;
  part_rows[74].v[5] = 0x172;
  part_rows[75].kind = 0;
  part_rows[75].count = 21;
  part_rows[75].v[0] = 0x1a6;
  part_rows[75].v[1] = 0x1d1;
  part_rows[75].v[2] = 0x142;
  part_rows[75].v[3] = 0x1d;
  part_rows[75].v[4] = 0x1d;
  part_rows[75].v[5] = 0x1ee;
  part_rows[76].kind = 1;
  part_rows[76].count = 5;
  part_rows[76].v[0] = 0x1be;
  part_rows[76].v[1] = 0x1cd;
  part_rows[76].v[2] = 0x13c;
  part_rows[76].v[3] = 0x34;
  part_rows[76].v[4] = 0x33;
  part_rows[76].v[5] = 0x128;
  part_rows[77].kind = 2;
  part_rows[77].count = 7;
  part_rows[77].v[0] = 0x1d1;
  part_rows[77].v[1] = 0x19d;
  part_rows[77].v[2] = 0x12c;
  part_rows[77].v[3] = 0x3c;
  part_rows[77].v[4] = 0x4b;
  part_rows[77].v[5] = 0x26e;
  part_rows[78].kind = 0;
  part_rows[78].count = 31;
  part_rows[78].v[0] = 0x1b2;
  part_rows[78].v[1] = 0x19e;
  part_rows[78].v[2] = 0x12b;
  part_rows[78].v[3] = 0x24;
  part_rows[78].v[4] = 0x41;
  part_rows[78].v[5] = 0x25d;
  part_rows[79].kind = 0;
  part_rows[79].count = 29;
  part_rows[79].v[0] = 0x1af;
  part_rows[79].v[1] = 0x1bd;
  part_rows[79].v[2] = 0x15c;
  part_rows[79].v[3] = 0x1d;
  part_rows[79].v[4] = 0x1d;
  part_rows[79].v[5] = 0x225;
  part_rows[80].kind = 1;
  part_rows[80].count = 7;
  part_rows[80].v[0] = 0x1c2;
  part_rows[80].v[1] = 0x1b9;
  part_rows[80].v[2] = 0x157;
  part_rows[80].v[3] = 0x31;
  part_rows[80].v[4] = 0x34;
  part_rows[80].v[5] = 0x1f0;
  part_rows[81].kind = 2;
  part_rows[81].count = 8;
  part_rows[81].v[0] = 0x1d3;
  part_rows[81].v[1] = 0x188;
  part_rows[81].v[2] = 0x129;
  part_rows[81].v[3] = 0x3a;
  part_rows[81].v[4] = 0x4e;
  part_rows[81].v[5] = 0x2f9;
  part_rows[82].kind = 0;
  part_rows[82].count = 33;
  part_rows[82].v[0] = 0x1b5;
  part_rows[82].v[1] = 0x1a5;
  part_rows[82].v[2] = 0x15c;
  part_rows[82].v[3] = 0x1c;
  part_rows[82].v[4] = 0x1e;
  part_rows[82].v[5] = 0x2b3;
  part_rows[83].kind = 1;
  part_rows[83].count = 8;
  part_rows[83].v[0] = 0x1c4;
  part_rows[83].v[1] = 0x1a0;
  part_rows[83].v[2] = 0x156;
  part_rows[83].v[3] = 0x32;
  part_rows[83].v[4] = 0x35;
  part_rows[83].v[5] = 0x252;
  part_rows[84].kind = 0;
  part_rows[84].count = 15;
  part_rows[84].v[0] = 0x19f;
  part_rows[84].v[1] = 0x1d1;
  part_rows[84].v[2] = 0x107;
  part_rows[84].v[3] = 0x43;
  part_rows[84].v[4] = 0x2a;
  part_rows[84].v[5] = 0x126;
  part_rows[85].kind = 2;
  part_rows[85].count = 4;
  part_rows[85].v[0] = 0x1cc;
  part_rows[85].v[1] = 0x1cf;
  part_rows[85].v[2] = 0x101;
  part_rows[85].v[3] = 0x50;
  part_rows[85].v[4] = 0x32;
  part_rows[85].v[5] = 0x121;
  part_rows[86].kind = 0;
  part_rows[86].count = 17;
  part_rows[86].v[0] = 0x1a1;
  part_rows[86].v[1] = 0x201;
  part_rows[86].v[2] = 0x11a;
  part_rows[86].v[3] = 0x21;
  part_rows[86].v[4] = 0x1a;
  part_rows[86].v[5] = 0x16a;
  part_rows[87].kind = 1;
  part_rows[87].count = 4;
  part_rows[87].v[0] = 0x1bd;
  part_rows[87].v[1] = 0x1fb;
  part_rows[87].v[2] = 0x116;
  part_rows[87].v[3] = 0x38;
  part_rows[87].v[4] = 0x2d;
  part_rows[87].v[5] = 0xef;
  iVar2 = surface_load_gif_resource(local_29c,0x1b9,10,0xec,(iptr)this + 0x1f8);
  if (iVar2 == 0) {
    local_d1c = 0;
    (*(i8 *)((char *)&local_8 + 0)) = 10;
    /* inlined unwind funclet 004d49d5 */ { surface_dtor((void *)((iptr)&local_a0)); }
    (*(i8 *)((char *)&local_8 + 0)) = 9;
    /* inlined unwind funclet 004d49e1 */ { surface_dtor((void *)((iptr)&local_e8)); }
    (*(i8 *)((char *)&local_8 + 0)) = 8;
    /* inlined unwind funclet 004d49ed */ { surface_dtor((void *)((iptr)&local_254)); }
    (*(i8 *)((char *)&local_8 + 0)) = 7;
    /* inlined unwind funclet 004d49f9 */ { surface_dtor((void *)((iptr)&local_20c)); }
    (*(i8 *)((char *)&local_8 + 0)) = 6;
    /* inlined unwind funclet 004d4a05 */ { surface_dtor((void *)((iptr)&local_178)); }
    (*(i8 *)((char *)&local_8 + 0)) = 5;
    /* inlined unwind funclet 004d4a11 */ { surface_dtor((void *)((iptr)&local_130)); }
    (*(i8 *)((char *)&local_8 + 0)) = 4;
    /* inlined unwind funclet 004d4a1d */ { surface_dtor((void *)((iptr)&local_cd0)); }
    (*(i8 *)((char *)&local_8 + 0)) = 3;
    /* inlined unwind funclet 004d4a29 */ { surface_dtor((void *)((iptr)&local_d18)); }
    (*(i8 *)((char *)&local_8 + 0)) = 2;
    /* inlined unwind funclet 004d4a35 */ { surface_dtor((void *)((iptr)&local_58)); }
    (*(i8 *)((char *)&local_8 + 0)) = 1;
    /* inlined unwind funclet 004d4a3e */ { surface_dtor((void *)((iptr)&local_1c4)); }
    local_8 = local_8 & 0xffffff00;
    /* inlined unwind funclet 004d4a4a */ { surface_dtor((void *)((iptr)&local_29c)); }
    local_8 = 0xffffffff;
    /* inlined unwind funclet 004d4a56 */ { surface_dtor((void *)((iptr)&local_2e8)); }
  }
  else {
    win_flush_pending_msgs();
    iVar2 = surface_load_gif_resource(local_1c4,0x1e0,10,0xec,(iptr)this + 0x1f8);
    if (iVar2 == 0) {
      local_d20 = 0;
      (*(i8 *)((char *)&local_8 + 0)) = 10;
      /* inlined unwind funclet 004d49d5 */ { surface_dtor((void *)((iptr)&local_a0)); }
      (*(i8 *)((char *)&local_8 + 0)) = 9;
      /* inlined unwind funclet 004d49e1 */ { surface_dtor((void *)((iptr)&local_e8)); }
      (*(i8 *)((char *)&local_8 + 0)) = 8;
      /* inlined unwind funclet 004d49ed */ { surface_dtor((void *)((iptr)&local_254)); }
      (*(i8 *)((char *)&local_8 + 0)) = 7;
      /* inlined unwind funclet 004d49f9 */ { surface_dtor((void *)((iptr)&local_20c)); }
      (*(i8 *)((char *)&local_8 + 0)) = 6;
      /* inlined unwind funclet 004d4a05 */ { surface_dtor((void *)((iptr)&local_178)); }
      (*(i8 *)((char *)&local_8 + 0)) = 5;
      /* inlined unwind funclet 004d4a11 */ { surface_dtor((void *)((iptr)&local_130)); }
      (*(i8 *)((char *)&local_8 + 0)) = 4;
      /* inlined unwind funclet 004d4a1d */ { surface_dtor((void *)((iptr)&local_cd0)); }
      (*(i8 *)((char *)&local_8 + 0)) = 3;
      /* inlined unwind funclet 004d4a29 */ { surface_dtor((void *)((iptr)&local_d18)); }
      (*(i8 *)((char *)&local_8 + 0)) = 2;
      /* inlined unwind funclet 004d4a35 */ { surface_dtor((void *)((iptr)&local_58)); }
      (*(i8 *)((char *)&local_8 + 0)) = 1;
      /* inlined unwind funclet 004d4a3e */ { surface_dtor((void *)((iptr)&local_1c4)); }
      local_8 = local_8 & 0xffffff00;
      /* inlined unwind funclet 004d4a4a */ { surface_dtor((void *)((iptr)&local_29c)); }
      local_8 = 0xffffffff;
      /* inlined unwind funclet 004d4a56 */ { surface_dtor((void *)((iptr)&local_2e8)); }
      local_d1c = local_d20;
    }
    else {
      win_flush_pending_msgs();
      iVar2 = surface_load_gif_resource(local_58,0x1c7,10,0xec,(iptr)this + 0x1f8);
      if (iVar2 == 0) {
        local_d24 = 0;
        (*(i8 *)((char *)&local_8 + 0)) = 10;
        /* inlined unwind funclet 004d49d5 */ { surface_dtor((void *)((iptr)&local_a0)); }
        (*(i8 *)((char *)&local_8 + 0)) = 9;
        /* inlined unwind funclet 004d49e1 */ { surface_dtor((void *)((iptr)&local_e8)); }
        (*(i8 *)((char *)&local_8 + 0)) = 8;
        /* inlined unwind funclet 004d49ed */ { surface_dtor((void *)((iptr)&local_254)); }
        (*(i8 *)((char *)&local_8 + 0)) = 7;
        /* inlined unwind funclet 004d49f9 */ { surface_dtor((void *)((iptr)&local_20c)); }
        (*(i8 *)((char *)&local_8 + 0)) = 6;
        /* inlined unwind funclet 004d4a05 */ { surface_dtor((void *)((iptr)&local_178)); }
        (*(i8 *)((char *)&local_8 + 0)) = 5;
        /* inlined unwind funclet 004d4a11 */ { surface_dtor((void *)((iptr)&local_130)); }
        (*(i8 *)((char *)&local_8 + 0)) = 4;
        /* inlined unwind funclet 004d4a1d */ { surface_dtor((void *)((iptr)&local_cd0)); }
        (*(i8 *)((char *)&local_8 + 0)) = 3;
        /* inlined unwind funclet 004d4a29 */ { surface_dtor((void *)((iptr)&local_d18)); }
        (*(i8 *)((char *)&local_8 + 0)) = 2;
        /* inlined unwind funclet 004d4a35 */ { surface_dtor((void *)((iptr)&local_58)); }
        (*(i8 *)((char *)&local_8 + 0)) = 1;
        /* inlined unwind funclet 004d4a3e */ { surface_dtor((void *)((iptr)&local_1c4)); }
        local_8 = local_8 & 0xffffff00;
        /* inlined unwind funclet 004d4a4a */ { surface_dtor((void *)((iptr)&local_29c)); }
        local_8 = 0xffffffff;
        /* inlined unwind funclet 004d4a56 */ { surface_dtor((void *)((iptr)&local_2e8)); }
        local_d1c = local_d24;
      }
      else {
        win_flush_pending_msgs();
        iVar2 = surface_load_gif_resource(local_d18,0x1ea,10,0xec,(iptr)this + 0x1f8);
        if (iVar2 == 0) {
          local_d28 = 0;
          (*(i8 *)((char *)&local_8 + 0)) = 10;
          /* inlined unwind funclet 004d49d5 */ { surface_dtor((void *)((iptr)&local_a0)); }
          (*(i8 *)((char *)&local_8 + 0)) = 9;
          /* inlined unwind funclet 004d49e1 */ { surface_dtor((void *)((iptr)&local_e8)); }
          (*(i8 *)((char *)&local_8 + 0)) = 8;
          /* inlined unwind funclet 004d49ed */ { surface_dtor((void *)((iptr)&local_254)); }
          (*(i8 *)((char *)&local_8 + 0)) = 7;
          /* inlined unwind funclet 004d49f9 */ { surface_dtor((void *)((iptr)&local_20c)); }
          (*(i8 *)((char *)&local_8 + 0)) = 6;
          /* inlined unwind funclet 004d4a05 */ { surface_dtor((void *)((iptr)&local_178)); }
          (*(i8 *)((char *)&local_8 + 0)) = 5;
          /* inlined unwind funclet 004d4a11 */ { surface_dtor((void *)((iptr)&local_130)); }
          (*(i8 *)((char *)&local_8 + 0)) = 4;
          /* inlined unwind funclet 004d4a1d */ { surface_dtor((void *)((iptr)&local_cd0)); }
          (*(i8 *)((char *)&local_8 + 0)) = 3;
          /* inlined unwind funclet 004d4a29 */ { surface_dtor((void *)((iptr)&local_d18)); }
          (*(i8 *)((char *)&local_8 + 0)) = 2;
          /* inlined unwind funclet 004d4a35 */ { surface_dtor((void *)((iptr)&local_58)); }
          (*(i8 *)((char *)&local_8 + 0)) = 1;
          /* inlined unwind funclet 004d4a3e */ { surface_dtor((void *)((iptr)&local_1c4)); }
          local_8 = local_8 & 0xffffff00;
          /* inlined unwind funclet 004d4a4a */ { surface_dtor((void *)((iptr)&local_29c)); }
          local_8 = 0xffffffff;
          /* inlined unwind funclet 004d4a56 */ { surface_dtor((void *)((iptr)&local_2e8)); }
          local_d1c = local_d28;
        }
        else {
          win_flush_pending_msgs();
          iVar2 = surface_load_gif_resource(local_cd0,0x1d6,10,0xec,(iptr)this + 0x1f8);
          if (iVar2 == 0) {
            local_d2c = 0;
            (*(i8 *)((char *)&local_8 + 0)) = 10;
            /* inlined unwind funclet 004d49d5 */ { surface_dtor((void *)((iptr)&local_a0)); }
            (*(i8 *)((char *)&local_8 + 0)) = 9;
            /* inlined unwind funclet 004d49e1 */ { surface_dtor((void *)((iptr)&local_e8)); }
            (*(i8 *)((char *)&local_8 + 0)) = 8;
            /* inlined unwind funclet 004d49ed */ { surface_dtor((void *)((iptr)&local_254)); }
            (*(i8 *)((char *)&local_8 + 0)) = 7;
            /* inlined unwind funclet 004d49f9 */ { surface_dtor((void *)((iptr)&local_20c)); }
            (*(i8 *)((char *)&local_8 + 0)) = 6;
            /* inlined unwind funclet 004d4a05 */ { surface_dtor((void *)((iptr)&local_178)); }
            (*(i8 *)((char *)&local_8 + 0)) = 5;
            /* inlined unwind funclet 004d4a11 */ { surface_dtor((void *)((iptr)&local_130)); }
            (*(i8 *)((char *)&local_8 + 0)) = 4;
            /* inlined unwind funclet 004d4a1d */ { surface_dtor((void *)((iptr)&local_cd0)); }
            (*(i8 *)((char *)&local_8 + 0)) = 3;
            /* inlined unwind funclet 004d4a29 */ { surface_dtor((void *)((iptr)&local_d18)); }
            (*(i8 *)((char *)&local_8 + 0)) = 2;
            /* inlined unwind funclet 004d4a35 */ { surface_dtor((void *)((iptr)&local_58)); }
            (*(i8 *)((char *)&local_8 + 0)) = 1;
            /* inlined unwind funclet 004d4a3e */ { surface_dtor((void *)((iptr)&local_1c4)); }
            local_8 = local_8 & 0xffffff00;
            /* inlined unwind funclet 004d4a4a */ { surface_dtor((void *)((iptr)&local_29c)); }
            local_8 = 0xffffffff;
            /* inlined unwind funclet 004d4a56 */ { surface_dtor((void *)((iptr)&local_2e8)); }
            local_d1c = local_d2c;
          }
          else {
            win_flush_pending_msgs();
            iVar2 = surface_load_gif_resource(local_178,0x1ba,10,0xec,(iptr)this + 0x1f8);
            if (iVar2 == 0) {
              local_d30 = 0;
              (*(i8 *)((char *)&local_8 + 0)) = 10;
              /* inlined unwind funclet 004d49d5 */ { surface_dtor((void *)((iptr)&local_a0)); }
              (*(i8 *)((char *)&local_8 + 0)) = 9;
              /* inlined unwind funclet 004d49e1 */ { surface_dtor((void *)((iptr)&local_e8)); }
              (*(i8 *)((char *)&local_8 + 0)) = 8;
              /* inlined unwind funclet 004d49ed */ { surface_dtor((void *)((iptr)&local_254)); }
              (*(i8 *)((char *)&local_8 + 0)) = 7;
              /* inlined unwind funclet 004d49f9 */ { surface_dtor((void *)((iptr)&local_20c)); }
              (*(i8 *)((char *)&local_8 + 0)) = 6;
              /* inlined unwind funclet 004d4a05 */ { surface_dtor((void *)((iptr)&local_178)); }
              (*(i8 *)((char *)&local_8 + 0)) = 5;
              /* inlined unwind funclet 004d4a11 */ { surface_dtor((void *)((iptr)&local_130)); }
              (*(i8 *)((char *)&local_8 + 0)) = 4;
              /* inlined unwind funclet 004d4a1d */ { surface_dtor((void *)((iptr)&local_cd0)); }
              (*(i8 *)((char *)&local_8 + 0)) = 3;
              /* inlined unwind funclet 004d4a29 */ { surface_dtor((void *)((iptr)&local_d18)); }
              (*(i8 *)((char *)&local_8 + 0)) = 2;
              /* inlined unwind funclet 004d4a35 */ { surface_dtor((void *)((iptr)&local_58)); }
              (*(i8 *)((char *)&local_8 + 0)) = 1;
              /* inlined unwind funclet 004d4a3e */ { surface_dtor((void *)((iptr)&local_1c4)); }
              local_8 = local_8 & 0xffffff00;
              /* inlined unwind funclet 004d4a4a */ { surface_dtor((void *)((iptr)&local_29c)); }
              local_8 = 0xffffffff;
              /* inlined unwind funclet 004d4a56 */ { surface_dtor((void *)((iptr)&local_2e8)); }
              local_d1c = local_d30;
            }
            else {
              win_flush_pending_msgs();
              iVar2 = surface_load_gif_resource(local_20c,0x1e1,10,0xec,(iptr)this + 0x1f8);
              if (iVar2 == 0) {
                local_d34 = 0;
                (*(i8 *)((char *)&local_8 + 0)) = 10;
                /* inlined unwind funclet 004d49d5 */ { surface_dtor((void *)((iptr)&local_a0)); }
                (*(i8 *)((char *)&local_8 + 0)) = 9;
                /* inlined unwind funclet 004d49e1 */ { surface_dtor((void *)((iptr)&local_e8)); }
                (*(i8 *)((char *)&local_8 + 0)) = 8;
                /* inlined unwind funclet 004d49ed */ { surface_dtor((void *)((iptr)&local_254)); }
                (*(i8 *)((char *)&local_8 + 0)) = 7;
                /* inlined unwind funclet 004d49f9 */ { surface_dtor((void *)((iptr)&local_20c)); }
                (*(i8 *)((char *)&local_8 + 0)) = 6;
                /* inlined unwind funclet 004d4a05 */ { surface_dtor((void *)((iptr)&local_178)); }
                (*(i8 *)((char *)&local_8 + 0)) = 5;
                /* inlined unwind funclet 004d4a11 */ { surface_dtor((void *)((iptr)&local_130)); }
                (*(i8 *)((char *)&local_8 + 0)) = 4;
                /* inlined unwind funclet 004d4a1d */ { surface_dtor((void *)((iptr)&local_cd0)); }
                (*(i8 *)((char *)&local_8 + 0)) = 3;
                /* inlined unwind funclet 004d4a29 */ { surface_dtor((void *)((iptr)&local_d18)); }
                (*(i8 *)((char *)&local_8 + 0)) = 2;
                /* inlined unwind funclet 004d4a35 */ { surface_dtor((void *)((iptr)&local_58)); }
                (*(i8 *)((char *)&local_8 + 0)) = 1;
                /* inlined unwind funclet 004d4a3e */ { surface_dtor((void *)((iptr)&local_1c4)); }
                local_8 = local_8 & 0xffffff00;
                /* inlined unwind funclet 004d4a4a */ { surface_dtor((void *)((iptr)&local_29c)); }
                local_8 = 0xffffffff;
                /* inlined unwind funclet 004d4a56 */ { surface_dtor((void *)((iptr)&local_2e8)); }
                local_d1c = local_d34;
              }
              else {
                win_flush_pending_msgs();
                iVar2 = surface_load_gif_resource(local_254,0x1c8,10,0xec,(iptr)this + 0x1f8);
                if (iVar2 == 0) {
                  local_d38 = 0;
                  (*(i8 *)((char *)&local_8 + 0)) = 10;
                  /* inlined unwind funclet 004d49d5 */ { surface_dtor((void *)((iptr)&local_a0)); }
                  (*(i8 *)((char *)&local_8 + 0)) = 9;
                  /* inlined unwind funclet 004d49e1 */ { surface_dtor((void *)((iptr)&local_e8)); }
                  (*(i8 *)((char *)&local_8 + 0)) = 8;
                  /* inlined unwind funclet 004d49ed */ { surface_dtor((void *)((iptr)&local_254)); }
                  (*(i8 *)((char *)&local_8 + 0)) = 7;
                  /* inlined unwind funclet 004d49f9 */ { surface_dtor((void *)((iptr)&local_20c)); }
                  (*(i8 *)((char *)&local_8 + 0)) = 6;
                  /* inlined unwind funclet 004d4a05 */ { surface_dtor((void *)((iptr)&local_178)); }
                  (*(i8 *)((char *)&local_8 + 0)) = 5;
                  /* inlined unwind funclet 004d4a11 */ { surface_dtor((void *)((iptr)&local_130)); }
                  (*(i8 *)((char *)&local_8 + 0)) = 4;
                  /* inlined unwind funclet 004d4a1d */ { surface_dtor((void *)((iptr)&local_cd0)); }
                  (*(i8 *)((char *)&local_8 + 0)) = 3;
                  /* inlined unwind funclet 004d4a29 */ { surface_dtor((void *)((iptr)&local_d18)); }
                  (*(i8 *)((char *)&local_8 + 0)) = 2;
                  /* inlined unwind funclet 004d4a35 */ { surface_dtor((void *)((iptr)&local_58)); }
                  (*(i8 *)((char *)&local_8 + 0)) = 1;
                  /* inlined unwind funclet 004d4a3e */ { surface_dtor((void *)((iptr)&local_1c4)); }
                  local_8 = local_8 & 0xffffff00;
                  /* inlined unwind funclet 004d4a4a */ { surface_dtor((void *)((iptr)&local_29c)); }
                  local_8 = 0xffffffff;
                  /* inlined unwind funclet 004d4a56 */ { surface_dtor((void *)((iptr)&local_2e8)); }
                  local_d1c = local_d38;
                }
                else {
                  win_flush_pending_msgs();
                  iVar2 = surface_load_gif_resource(local_e8,0x1e9,10,0xec,(iptr)this + 0x1f8);
                  if (iVar2 == 0) {
                    local_d3c = 0;
                    (*(i8 *)((char *)&local_8 + 0)) = 10;
                    /* inlined unwind funclet 004d49d5 */ { surface_dtor((void *)((iptr)&local_a0)); }
                    (*(i8 *)((char *)&local_8 + 0)) = 9;
                    /* inlined unwind funclet 004d49e1 */ { surface_dtor((void *)((iptr)&local_e8)); }
                    (*(i8 *)((char *)&local_8 + 0)) = 8;
                    /* inlined unwind funclet 004d49ed */ { surface_dtor((void *)((iptr)&local_254)); }
                    (*(i8 *)((char *)&local_8 + 0)) = 7;
                    /* inlined unwind funclet 004d49f9 */ { surface_dtor((void *)((iptr)&local_20c)); }
                    (*(i8 *)((char *)&local_8 + 0)) = 6;
                    /* inlined unwind funclet 004d4a05 */ { surface_dtor((void *)((iptr)&local_178)); }
                    (*(i8 *)((char *)&local_8 + 0)) = 5;
                    /* inlined unwind funclet 004d4a11 */ { surface_dtor((void *)((iptr)&local_130)); }
                    (*(i8 *)((char *)&local_8 + 0)) = 4;
                    /* inlined unwind funclet 004d4a1d */ { surface_dtor((void *)((iptr)&local_cd0)); }
                    (*(i8 *)((char *)&local_8 + 0)) = 3;
                    /* inlined unwind funclet 004d4a29 */ { surface_dtor((void *)((iptr)&local_d18)); }
                    (*(i8 *)((char *)&local_8 + 0)) = 2;
                    /* inlined unwind funclet 004d4a35 */ { surface_dtor((void *)((iptr)&local_58)); }
                    (*(i8 *)((char *)&local_8 + 0)) = 1;
                    /* inlined unwind funclet 004d4a3e */ { surface_dtor((void *)((iptr)&local_1c4)); }
                    local_8 = local_8 & 0xffffff00;
                    /* inlined unwind funclet 004d4a4a */ { surface_dtor((void *)((iptr)&local_29c)); }
                    local_8 = 0xffffffff;
                    /* inlined unwind funclet 004d4a56 */ { surface_dtor((void *)((iptr)&local_2e8)); }
                    local_d1c = local_d3c;
                  }
                  else {
                    win_flush_pending_msgs();
                    iVar2 = surface_load_gif_resource(local_a0,0x1d7,10,0xec,(iptr)this + 0x1f8);
                    if (iVar2 == 0) {
                      local_d40 = 0;
                      (*(i8 *)((char *)&local_8 + 0)) = 10;
                      /* inlined unwind funclet 004d49d5 */ { surface_dtor((void *)((iptr)&local_a0)); }
                      (*(i8 *)((char *)&local_8 + 0)) = 9;
                      /* inlined unwind funclet 004d49e1 */ { surface_dtor((void *)((iptr)&local_e8)); }
                      (*(i8 *)((char *)&local_8 + 0)) = 8;
                      /* inlined unwind funclet 004d49ed */ { surface_dtor((void *)((iptr)&local_254)); }
                      (*(i8 *)((char *)&local_8 + 0)) = 7;
                      /* inlined unwind funclet 004d49f9 */ { surface_dtor((void *)((iptr)&local_20c)); }
                      (*(i8 *)((char *)&local_8 + 0)) = 6;
                      /* inlined unwind funclet 004d4a05 */ { surface_dtor((void *)((iptr)&local_178)); }
                      (*(i8 *)((char *)&local_8 + 0)) = 5;
                      /* inlined unwind funclet 004d4a11 */ { surface_dtor((void *)((iptr)&local_130)); }
                      (*(i8 *)((char *)&local_8 + 0)) = 4;
                      /* inlined unwind funclet 004d4a1d */ { surface_dtor((void *)((iptr)&local_cd0)); }
                      (*(i8 *)((char *)&local_8 + 0)) = 3;
                      /* inlined unwind funclet 004d4a29 */ { surface_dtor((void *)((iptr)&local_d18)); }
                      (*(i8 *)((char *)&local_8 + 0)) = 2;
                      /* inlined unwind funclet 004d4a35 */ { surface_dtor((void *)((iptr)&local_58)); }
                      (*(i8 *)((char *)&local_8 + 0)) = 1;
                      /* inlined unwind funclet 004d4a3e */ { surface_dtor((void *)((iptr)&local_1c4)); }
                      local_8 = local_8 & 0xffffff00;
                      /* inlined unwind funclet 004d4a4a */ { surface_dtor((void *)((iptr)&local_29c)); }
                      local_8 = 0xffffffff;
                      /* inlined unwind funclet 004d4a56 */ { surface_dtor((void *)((iptr)&local_2e8)); }
                      local_d1c = local_d40;
                    }
                    else {
                      win_flush_pending_msgs();
                      iVar2 = surface_load_gif_resource(local_130,0x1eb,10,0xec,(iptr)this + 0x1f8);
                      if (iVar2 == 0) {
                        local_d44 = 0;
                        (*(i8 *)((char *)&local_8 + 0)) = 10;
                        /* inlined unwind funclet 004d49d5 */ { surface_dtor((void *)((iptr)&local_a0)); }
                        (*(i8 *)((char *)&local_8 + 0)) = 9;
                        /* inlined unwind funclet 004d49e1 */ { surface_dtor((void *)((iptr)&local_e8)); }
                        (*(i8 *)((char *)&local_8 + 0)) = 8;
                        /* inlined unwind funclet 004d49ed */ { surface_dtor((void *)((iptr)&local_254)); }
                        (*(i8 *)((char *)&local_8 + 0)) = 7;
                        /* inlined unwind funclet 004d49f9 */ { surface_dtor((void *)((iptr)&local_20c)); }
                        (*(i8 *)((char *)&local_8 + 0)) = 6;
                        /* inlined unwind funclet 004d4a05 */ { surface_dtor((void *)((iptr)&local_178)); }
                        (*(i8 *)((char *)&local_8 + 0)) = 5;
                        /* inlined unwind funclet 004d4a11 */ { surface_dtor((void *)((iptr)&local_130)); }
                        (*(i8 *)((char *)&local_8 + 0)) = 4;
                        /* inlined unwind funclet 004d4a1d */ { surface_dtor((void *)((iptr)&local_cd0)); }
                        (*(i8 *)((char *)&local_8 + 0)) = 3;
                        /* inlined unwind funclet 004d4a29 */ { surface_dtor((void *)((iptr)&local_d18)); }
                        (*(i8 *)((char *)&local_8 + 0)) = 2;
                        /* inlined unwind funclet 004d4a35 */ { surface_dtor((void *)((iptr)&local_58)); }
                        (*(i8 *)((char *)&local_8 + 0)) = 1;
                        /* inlined unwind funclet 004d4a3e */ { surface_dtor((void *)((iptr)&local_1c4)); }
                        local_8 = local_8 & 0xffffff00;
                        /* inlined unwind funclet 004d4a4a */ { surface_dtor((void *)((iptr)&local_29c)); }
                        local_8 = 0xffffffff;
                        /* inlined unwind funclet 004d4a56 */ { surface_dtor((void *)((iptr)&local_2e8)); }
                        local_d1c = local_d44;
                      }
                      else {
                        win_flush_pending_msgs();
                        for (local_2a0 = 0; local_2a0 < 7; local_2a0 = local_2a0 + 1) {
                          win_flush_pending_msgs();
                          if ((int)(uint)part_rows[local_2a0].count <=
                              *(int *)(((i8 *)&editor_text_edit_block.spaceship_wnd_part_counts) + (uint)part_rows[local_2a0].kind * 4)) {
                            if (part_rows[local_2a0].kind == 1) {
                              bVar1 = part_rows[local_2a0].count;
                              iVar2 = spaceship_part_count(*(i32 *)((iptr)this + 0x1cc),1);
                              if (iVar2 < (int)(uint)bVar1) {
                                sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_178,9,
                                             part_rows[local_2a0].v[5],1,
                                             part_rows[local_2a0].v[3],
                                             part_rows[local_2a0].v[4]);
                              }
                              else {
                                sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_29c,9,
                                             part_rows[local_2a0].v[5],1,
                                             part_rows[local_2a0].v[3],
                                             part_rows[local_2a0].v[4]);
                              }
                            }
                            else if (part_rows[local_2a0].kind == 4) {
                              bVar1 = part_rows[local_2a0].count;
                              iVar2 = spaceship_part_count(*(i32 *)((iptr)this + 0x1cc),4);
                              if (iVar2 < (int)(uint)bVar1) {
                                sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_20c,9,
                                             part_rows[local_2a0].v[5],1,
                                             part_rows[local_2a0].v[3],
                                             part_rows[local_2a0].v[4]);
                              }
                              else {
                                sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_1c4,9,
                                             part_rows[local_2a0].v[5],1,
                                             part_rows[local_2a0].v[3],
                                             part_rows[local_2a0].v[4]);
                              }
                            }
                            else if (part_rows[local_2a0].kind == 2) {
                              bVar1 = part_rows[local_2a0].count;
                              iVar2 = spaceship_part_count(*(i32 *)((iptr)this + 0x1cc),2);
                              if (iVar2 < (int)(uint)bVar1) {
                                sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_254,9,
                                             part_rows[local_2a0].v[5],1,
                                             part_rows[local_2a0].v[3],
                                             part_rows[local_2a0].v[4]);
                              }
                              else {
                                sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_58,9,
                                             part_rows[local_2a0].v[5],1,
                                             part_rows[local_2a0].v[3],
                                             part_rows[local_2a0].v[4]);
                              }
                            }
                            else if (part_rows[local_2a0].kind == 5) {
                              bVar1 = part_rows[local_2a0].count;
                              iVar2 = spaceship_part_count(*(i32 *)((iptr)this + 0x1cc),5);
                              if (iVar2 < (int)(uint)bVar1) {
                                sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_e8,9,
                                             part_rows[local_2a0].v[5],1,
                                             part_rows[local_2a0].v[3],
                                             part_rows[local_2a0].v[4]);
                              }
                              else {
                                sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_d18,9,
                                             part_rows[local_2a0].v[5],1,
                                             part_rows[local_2a0].v[3],
                                             part_rows[local_2a0].v[4]);
                              }
                            }
                            else if (part_rows[local_2a0].kind == 3) {
                              bVar1 = part_rows[local_2a0].count;
                              iVar2 = spaceship_part_count(*(i32 *)((iptr)this + 0x1cc),3);
                              if (iVar2 < (int)(uint)bVar1) {
                                sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_a0,9,
                                             part_rows[local_2a0].v[5],1,
                                             part_rows[local_2a0].v[3],
                                             part_rows[local_2a0].v[4]);
                              }
                              else {
                                sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_cd0,9,
                                             part_rows[local_2a0].v[5],1,
                                             part_rows[local_2a0].v[3],
                                             part_rows[local_2a0].v[4]);
                              }
                            }
                            else {
                              sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_130,9,
                                           part_rows[local_2a0].v[5],1,
                                           part_rows[local_2a0].v[3],part_rows[local_2a0].v[4]
                                          );
                            }
                            sprite_draw((void *)((iptr)this + 0x93c),local_d54,(iptr)this + 0x8f4,
                                         part_rows[local_2a0].v[1] + -0xaf,
                                         part_rows[local_2a0].v[2] + -99);
                          }
                        }
                        local_17c = 0;
                        for (local_2a0 = 7; local_2a0 < 0x1f; local_2a0 = local_2a0 + 1) {
                          if ((int)(uint)part_rows[local_2a0].count <=
                              *(int *)(((i8 *)&editor_text_edit_block.spaceship_wnd_part_counts) + (uint)part_rows[local_2a0].kind * 4)) {
                            local_17c = local_2a0;
                          }
                        }
                        win_flush_pending_msgs();
                        iVar2 = surface_load_gif_resource(local_2e8,part_rows[local_17c].v[0],10,0xec,
                                             (iptr)this + 0x1f8);
                        if (iVar2 == 0) {
                          local_d58 = 0;
                          (*(i8 *)((char *)&local_8 + 0)) = 10;
                          /* inlined unwind funclet 004d49d5 */ { surface_dtor((void *)((iptr)&local_a0)); }
                          (*(i8 *)((char *)&local_8 + 0)) = 9;
                          /* inlined unwind funclet 004d49e1 */ { surface_dtor((void *)((iptr)&local_e8)); }
                          (*(i8 *)((char *)&local_8 + 0)) = 8;
                          /* inlined unwind funclet 004d49ed */ { surface_dtor((void *)((iptr)&local_254)); }
                          (*(i8 *)((char *)&local_8 + 0)) = 7;
                          /* inlined unwind funclet 004d49f9 */ { surface_dtor((void *)((iptr)&local_20c)); }
                          (*(i8 *)((char *)&local_8 + 0)) = 6;
                          /* inlined unwind funclet 004d4a05 */ { surface_dtor((void *)((iptr)&local_178)); }
                          (*(i8 *)((char *)&local_8 + 0)) = 5;
                          /* inlined unwind funclet 004d4a11 */ { surface_dtor((void *)((iptr)&local_130)); }
                          (*(i8 *)((char *)&local_8 + 0)) = 4;
                          /* inlined unwind funclet 004d4a1d */ { surface_dtor((void *)((iptr)&local_cd0)); }
                          (*(i8 *)((char *)&local_8 + 0)) = 3;
                          /* inlined unwind funclet 004d4a29 */ { surface_dtor((void *)((iptr)&local_d18)); }
                          (*(i8 *)((char *)&local_8 + 0)) = 2;
                          /* inlined unwind funclet 004d4a35 */ { surface_dtor((void *)((iptr)&local_58)); }
                          (*(i8 *)((char *)&local_8 + 0)) = 1;
                          /* inlined unwind funclet 004d4a3e */ { surface_dtor((void *)((iptr)&local_1c4)); }
                          local_8 = local_8 & 0xffffff00;
                          /* inlined unwind funclet 004d4a4a */ { surface_dtor((void *)((iptr)&local_29c)); }
                          local_8 = 0xffffffff;
                          /* inlined unwind funclet 004d4a56 */ { surface_dtor((void *)((iptr)&local_2e8)); }
                          local_d1c = local_d58;
                        }
                        else {
                          win_flush_pending_msgs();
                          sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_2e8,9,
                                       part_rows[local_17c].v[1],part_rows[local_17c].v[2],
                                       part_rows[local_17c].v[3],part_rows[local_17c].v[4]);
                          sprite_draw((void *)((iptr)this + 0x93c),local_d68,(iptr)this + 0x8f4,
                                       part_rows[local_17c].v[1] + -0xaf,
                                       part_rows[local_17c].v[2] + -99);
                          for (local_2a0 = 0x1f; local_2a0 < 0x58; local_2a0 = local_2a0 + 1) {
                            win_flush_pending_msgs();
                            win_flush_pending_msgs();
                            if ((int)(uint)part_rows[local_2a0].count <=
                                *(int *)(((i8 *)&editor_text_edit_block.spaceship_wnd_part_counts) + (uint)part_rows[local_2a0].kind * 4)) {
                              if (part_rows[local_2a0].kind == 1) {
                                bVar1 = part_rows[local_2a0].count;
                                iVar2 = spaceship_part_count(*(i32 *)((iptr)this + 0x1cc),1);
                                if (iVar2 < (int)(uint)bVar1) {
                                  sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_178,9,
                                               part_rows[local_2a0].v[5],1,
                                               part_rows[local_2a0].v[3],
                                               part_rows[local_2a0].v[4]);
                                }
                                else {
                                  sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_29c,9,
                                               part_rows[local_2a0].v[5],1,
                                               part_rows[local_2a0].v[3],
                                               part_rows[local_2a0].v[4]);
                                }
                              }
                              else if (part_rows[local_2a0].kind == 4) {
                                bVar1 = part_rows[local_2a0].count;
                                iVar2 = spaceship_part_count(*(i32 *)((iptr)this + 0x1cc),4);
                                if (iVar2 < (int)(uint)bVar1) {
                                  sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_20c,9,
                                               part_rows[local_2a0].v[5],1,
                                               part_rows[local_2a0].v[3],
                                               part_rows[local_2a0].v[4]);
                                }
                                else {
                                  sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_1c4,9,
                                               part_rows[local_2a0].v[5],1,
                                               part_rows[local_2a0].v[3],
                                               part_rows[local_2a0].v[4]);
                                }
                              }
                              else if (part_rows[local_2a0].kind == 2) {
                                bVar1 = part_rows[local_2a0].count;
                                iVar2 = spaceship_part_count(*(i32 *)((iptr)this + 0x1cc),2);
                                if (iVar2 < (int)(uint)bVar1) {
                                  sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_254,9,
                                               part_rows[local_2a0].v[5],1,
                                               part_rows[local_2a0].v[3],
                                               part_rows[local_2a0].v[4]);
                                }
                                else {
                                  sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_58,9,
                                               part_rows[local_2a0].v[5],1,
                                               part_rows[local_2a0].v[3],
                                               part_rows[local_2a0].v[4]);
                                }
                              }
                              else if (part_rows[local_2a0].kind == 5) {
                                bVar1 = part_rows[local_2a0].count;
                                iVar2 = spaceship_part_count(*(i32 *)((iptr)this + 0x1cc),5);
                                if (iVar2 < (int)(uint)bVar1) {
                                  sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_e8,9,
                                               part_rows[local_2a0].v[5],1,
                                               part_rows[local_2a0].v[3],
                                               part_rows[local_2a0].v[4]);
                                }
                                else {
                                  sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_d18,9,
                                               part_rows[local_2a0].v[5],1,
                                               part_rows[local_2a0].v[3],
                                               part_rows[local_2a0].v[4]);
                                }
                              }
                              else if (part_rows[local_2a0].kind == 3) {
                                bVar1 = part_rows[local_2a0].count;
                                iVar2 = spaceship_part_count(*(i32 *)((iptr)this + 0x1cc),3);
                                if (iVar2 < (int)(uint)bVar1) {
                                  sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_a0,9,
                                               part_rows[local_2a0].v[5],1,
                                               part_rows[local_2a0].v[3],
                                               part_rows[local_2a0].v[4]);
                                }
                                else {
                                  sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_cd0,9,
                                               part_rows[local_2a0].v[5],1,
                                               part_rows[local_2a0].v[3],
                                               part_rows[local_2a0].v[4]);
                                }
                              }
                              else {
                                sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_130,9,
                                             part_rows[local_2a0].v[5],1,
                                             part_rows[local_2a0].v[3],
                                             part_rows[local_2a0].v[4]);
                              }
                              sprite_draw((void *)((iptr)this + 0x93c),local_d78,(iptr)this + 0x8f4,
                                           part_rows[local_2a0].v[1] + -0xaf,
                                           part_rows[local_2a0].v[2] + -99);
                            }
                          }
                          sprite_grab_from_surface((void *)((iptr)this + 0x93c),(iptr)this + 0x8f4,9,0,0,0x1c9,
                                       0x130);
                          win_flush_pending_msgs();
                          if (*(int *)((iptr)this + 0xae0) == 3) {
                            surface_fill((void *)((iptr)this + 0xb8),0);
                          }
                          sprite_draw((void *)((iptr)this + 0x93c),local_d88,(iptr)this + 0xb8,0xaf,
                                       99);
                          spaceship_wnd_draw_title(*(i32 *)((iptr)this + 0x1cc));
                          (*(i8 *)((char *)&local_8 + 0)) = 10;
                          /* inlined unwind funclet 004d49d5 */ { surface_dtor((void *)((iptr)&local_a0)); }
                          (*(i8 *)((char *)&local_8 + 0)) = 9;
                          /* inlined unwind funclet 004d49e1 */ { surface_dtor((void *)((iptr)&local_e8)); }
                          (*(i8 *)((char *)&local_8 + 0)) = 8;
                          /* inlined unwind funclet 004d49ed */ { surface_dtor((void *)((iptr)&local_254)); }
                          (*(i8 *)((char *)&local_8 + 0)) = 7;
                          /* inlined unwind funclet 004d49f9 */ { surface_dtor((void *)((iptr)&local_20c)); }
                          (*(i8 *)((char *)&local_8 + 0)) = 6;
                          /* inlined unwind funclet 004d4a05 */ { surface_dtor((void *)((iptr)&local_178)); }
                          (*(i8 *)((char *)&local_8 + 0)) = 5;
                          /* inlined unwind funclet 004d4a11 */ { surface_dtor((void *)((iptr)&local_130)); }
                          (*(i8 *)((char *)&local_8 + 0)) = 4;
                          /* inlined unwind funclet 004d4a1d */ { surface_dtor((void *)((iptr)&local_cd0)); }
                          (*(i8 *)((char *)&local_8 + 0)) = 3;
                          /* inlined unwind funclet 004d4a29 */ { surface_dtor((void *)((iptr)&local_d18)); }
                          (*(i8 *)((char *)&local_8 + 0)) = 2;
                          /* inlined unwind funclet 004d4a35 */ { surface_dtor((void *)((iptr)&local_58)); }
                          (*(i8 *)((char *)&local_8 + 0)) = 1;
                          /* inlined unwind funclet 004d4a3e */ { surface_dtor((void *)((iptr)&local_1c4)); }
                          local_8 = local_8 & 0xffffff00;
                          /* inlined unwind funclet 004d4a4a */ { surface_dtor((void *)((iptr)&local_29c)); }
                          local_8 = 0xffffffff;
                          /* inlined unwind funclet 004d4a56 */ { surface_dtor((void *)((iptr)&local_2e8)); }
                          local_d1c = 1;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return local_d1c;
}

/* 0x005aa0e5: unwind funclet 0x005ab07f destroys the object at EBP-0x320 (local_324). */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl net_host_turn_loop(void)

{
  byte bVar1;
  SHORT SVar2;
  i32 uVar3;
  int iVar4;
  int local_330;
  int local_32c;
  int local_328;
  Dialog local_324;
  int local_30;
  int local_2c;
  i32 local_28;
  i32 local_24;
  i32 local_20;
  i32 local_1c;
  int local_18;
  int local_14;
  i32 uStack_10;
  i32 local_8;
  
  local_8 = 0xffffffff;
  dialog_ctor(&local_324,0x4000);
  local_8 = 0;
  iVar4 = human_civ[0];
  uVar3 = civ_name_plural(human_civ[0]);
  dbg_logf_str_int(str_server_s_d_3,uVar3,iVar4);
  for (local_330 = 1; local_330 < 8; local_330 = local_330 + 1) {
    if (((human_civ[0] != local_330) && ((1 << ((byte)local_330 & 0x1f) & (uint)game.civs_alive) != 0))
       && ((1 << ((byte)local_330 & 0x1f) & (uint)game.human_players) != 0)) {
      iVar4 = local_330;
      uVar3 = civ_name_plural(local_330);
      dbg_logf_str_int(str_client_s_d_3,uVar3,iVar4);
    }
  }
  net_reset_error_counts();
  map_rebuild_unit_flags();
  picwnd_close(((i8 *)&advisor_window_block.advisor_window));
  picwnd_close(((i8 *)&casualty_window_block.casualty_window));
  menu_update_states();
  ui_redraw_all_maps(1);
  mapview_update_title(((i8 *)&map_views_block.map_views));
  local_18 = 0;
  for (local_328 = 0; local_328 < game.num_units; local_328 = local_328 + 1) {
    if ((units[local_328].id != 0) &&
       ((char)units[local_328].owner == human_civ[0])) {
      mapview_center_on(((i8 *)&map_views_block.map_views),(int)units[local_328].x,
                         (int)units[local_328].y);
      local_18 = local_18 + 1;
      break;
    }
  }
  if (local_18 == 0) {
    for (local_328 = 0; local_328 < game.num_cities; local_328 = local_328 + 1) {
      if ((cities[local_328].id != 0) &&
         ((char)cities[local_328].owner == human_civ[0])) {
        mapview_center_on(((i8 *)&map_views_block.map_views),(int)cities[local_328].x,
                           (int)cities[local_328].y);
        break;
      }
    }
  }
  bVar1 = (*(byte *)&turn_resume_civ);
  if ((*(byte *)&turn_resume_civ) != 0) {
    do {
      if ((1 << ((*(byte *)&turn_resume_civ) & 0x1f) & (uint)game.civs_alive) != 0) goto LAB_005aa3dc;
      (*(byte *)&turn_resume_civ) = (*(byte *)&turn_resume_civ) + 1;
      if ((*(byte *)&turn_resume_civ) == 8) {
        (*(byte *)&turn_resume_civ) = 0;
      }
    } while ((*(byte *)&turn_resume_civ) != bVar1);
    game_over_reason = 1;
  }
LAB_005aa3dc:
  do {
    game.human_players = net_session_block.pending_human_players | game.human_players;
    net_session_block.pending_human_players = 0;
    _memset(((i8 *)&net_map_lock_slots_block.net_map_lock_slots),-1,0xc0);
    units_reset_for_turn(0xfffffffd);
    net_send_state_diff(0xff,2,0,0,0);
    XD_FlushSendBuffer(60000);
    while ((net_session_block.net_msgq_priority_count != 0 || (net_session_block.net_msgq_normal_count != 0))) {
      net_process_messages(((i32 *)&net_session_block.net_session),1,0);
    }
    game_calc_human_wonder_range();
    if ((*(byte *)&turn_resume_civ) == 0) {
      game_advance_turn(0xfffffffd);
      net_send_state_diff(0xff,2,0,0,0);
      XD_FlushSendBuffer(60000);
    }
    iVar4 = game_check_retirement();
    if ((iVar4 != 0) || (game_over_reason != 0)) {
      game_loop_active = '\0';
      break;
    }
    if ((scenario_events_loaded != 0) && (((*(byte *)&turn_resume_civ) == 0 || (turn_resume_new_game != 0)))) {
      events_check_turn(((i8 *)&unit_types_block.scenario_events),(int)game.turn);
      events_check_turn_interval(((i8 *)&unit_types_block.scenario_events),(int)game.turn);
      events_check_random_turn(((i8 *)&unit_types_block.scenario_events),(int)game.turn);
      events_check_received_tech(((i8 *)&unit_types_block.scenario_events));
      net_send_state_diff(0xff,2,0,0,0);
      XD_FlushSendBuffer(5000);
    }
    game.human_players = (net_session_block.pending_human_players | game.human_players) & (byte)civ_saved_cursor_x_block.net_claimed_civs_mask;
    net_session_block.pending_human_players = 0;
    net_session_block.net_tile_sync_enabled = 0;
    for (local_330 = 0; (game_loop_active != '\0' && (local_330 < 8)); local_330 = local_330 + 1) {
      game.turn_civ = (byte)local_330;
      if (((1 << ((byte)local_330 & 0x1f) & (uint)game.civs_alive) != 0) &&
         ((1 << ((byte)local_330 & 0x1f) & (uint)game.human_players) == 0)) {
        civ_process_turn(local_330);
        net_send_state_diff(0xff,2,0,0,0);
      }
    }
    net_session_block.net_tile_sync_enabled = 1;
    XD_FlushSendBuffer(60000);
    net_reset_msg_counts();
    for (local_330 = 0; local_330 < 8; local_330 = local_330 + 1) {
      *(i32 *)(((i8 *)&dialog_text_font_obj_block.net_civ_phase_done) + local_330 * 4) = 0;
    }
    net_send_message(0x8b,0xff,0,0,0,0,0,0,0,0);
    human_civ[0] = (((i32 *)&net_session_block.net_slot_civs))[net_session_block.net_local_slot * 0x15];
    game.player_civ = (byte)human_civ[0];
    game.turn_civ = (byte)human_civ[0];
    if ((*(byte *)&turn_resume_civ) == 0) {
      civ_check_throne_room_upgrade();
    }
    civ_process_turn(human_civ[0]);
    net_send_state_diff(0xff,2,0,0,0);
    *(int *)(((i8 *)&dialog_text_font_obj_block.net_civ_phase_done) + human_civ[0] * 4) = *(int *)(((i8 *)&dialog_text_font_obj_block.net_civ_phase_done) + human_civ[0] * 4) + 1;
    dlg_pending_idle_callback = ((void *)(iptr)net_host_wait_production_idle);
    popup_game_with_sprite(str_waitproduction,((i8 *)&popup_info_icon_sprite),0);
    local_2c = 0;
LAB_005aa732:
    if (local_2c == 0) {
      net_process_messages(((i32 *)&net_session_block.net_session),1,0);
      if (net_session_block.net_player_count[0] < 2) {
        local_2c = 1;
        goto LAB_005aa7ee;
      }
      local_2c = 1;
      for (local_330 = 1; local_330 < 8; local_330 = local_330 + 1) {
        if ((((1 << ((byte)local_330 & 0x1f) & (uint)game.civs_alive) != 0) &&
            ((1 << ((byte)local_330 & 0x1f) & (uint)game.human_players) != 0)) &&
           (*(int *)(((i8 *)&dialog_text_font_obj_block.net_civ_phase_done) + local_330 * 4) == 0)) {
          local_2c = 0;
          break;
        }
      }
      goto LAB_005aa732;
    }
LAB_005aa7ee:
    net_session_block.nm_production_complete_count = 0;
    net_send_state_diff(0xff,2,0,0,0);
    XD_FlushSendBuffer(60000);
    net_send_message(0x8d,0xff,0,0,0,0,0,0,0,0);
    human_civ[0] = (((i32 *)&net_session_block.net_slot_civs))[net_session_block.net_local_slot * 0x15];
    game.player_civ = (byte)human_civ[0];
    net_session_block.net_tile_sync_enabled = 0;
    if ((*(byte *)&turn_resume_civ) == 0) {
      units_reset_for_turn(0xffffffff);
    }
    for (local_330 = 0; (game_loop_active != '\0' && (local_330 < 8)); local_330 = local_330 + 1) {
      if (((1 << ((byte)local_330 & 0x1f) & (uint)game.civs_alive) != 0) &&
         ((1 << ((byte)local_330 & 0x1f) & (uint)game.human_players) == 0)) {
        game.turn_civ = (byte)local_330;
        net_session_block.mp_turn_civ = local_330;
        menu_update_states();
        status_draw_civ_color(local_330);
        if (((((*(byte *)&turn_resume_civ) == 0) || (turn_resume_new_game != 0)) && ((*(byte *)&turn_resume_civ) != 0)) &&
           (turn_resume_new_game != 0)) {
          mapview_update_title(((i8 *)&map_views_block.map_views));
          map_redraw_all_views(human_civ[0],1);
          wnd_flush_paint();
        }
        ai_process_civ_units();
      }
    }
    for (local_330 = 0; local_330 < 8; local_330 = local_330 + 1) {
      *(i32 *)(((i8 *)&dialog_text_font_obj_block.net_civ_phase_done) + local_330 * 4) = 0;
      *(i32 *)(((i8 *)&net_session_block.net_civ_new_player_flags) + local_330 * 4) = 0;
    }
    net_send_state_diff(0xff,2,0,0,0);
    net_send_message(0x8e,0xff,0,0,0,0,0,0,0,0);
    XD_FlushSendBuffer(60000);
    game.turn_civ = (byte)human_civ[0];
    net_session_block.net_tile_sync_enabled = 1;
    if (game_loop_active == '\0') {
      net_send_message(0x31,0,0,human_civ[0],0,0,0,0,0,0);
      break;
    }
    if ((*(short *)(((i8 *)&civ_saved_cursor_x_block.civ_intro_shown) + human_civ[0] * 2) == 0) && (civ_saved_cursor_x_block.autoplay_active == 0)) {
      civ_intro_popup(human_civ[0]);
      *(i16 *)(((i8 *)&civ_saved_cursor_x_block.civ_intro_shown) + human_civ[0] * 2) = 1;
    }
    if (civ_saved_cursor_x_block.mp_turn_time_limit_ms != 0) {
      mp_turn_seconds_left = civ_saved_cursor_x_block.mp_turn_time_limit_ms / 1000;
      map_views_block.main_view_timer_cache_i32 = 0xffffffff;
    }
    net_session_block.mp_turn_civ = human_civ[0];
    menu_update_states();
    map_views_block.main_view_timer_cache_i32 = 0xffffffff;
    frame_wnd_draw_caption(((i8 *)&map_views_block.map_views));
    local_28 = map_views_block.main_view_frame_left;
    local_24 = map_views_block.main_view_frame_top;
    local_20 = map_views_block.main_view_frame_right;
    local_1c = map_views_block.main_view_client_top;
    wnd_blit_surface_rect(((i8 *)&map_views_block.map_views),&local_28);
    mapview_update_title(((i8 *)&map_views_block.map_views));
    map_redraw_all_views(human_civ[0],1);
    status_draw_civ_color(human_civ[0]);
    local_14 = *(int *)(((i8 *)&net_session_block.casualty_counts) + human_civ[0] * 4) -
               *(int *)(((i8 *)&net_session_block.casualty_reported_counts) + human_civ[0] * 4);
    if (civ_saved_cursor_x_block.autoplay_active == 0) {
      dlg_pending_idle_callback = ((void *)(iptr)turn_popup_timeout_idle);
      uVar3 = civ_leader_title(human_civ[0]);
      text_set_string_arg(0,uVar3);
      uVar3 = civ_leader_name(human_civ[0]);
      text_set_string_arg(1,uVar3);
      if (*(int *)(((i8 *)&net_session_block.casualty_reported_counts) + human_civ[0] * 4) < *(int *)(((i8 *)&net_session_block.casualty_counts) + human_civ[0] * 4)) {
        *(i32 *)(((i8 *)&net_session_block.casualty_reported_counts) + human_civ[0] * 4) =
             *(i32 *)(((i8 *)&net_session_block.casualty_counts) + human_civ[0] * 4);
        text_set_number_arg(0,local_14);
        if (local_14 == 1) {
          dialog_load_text_noflags(&local_324,((i32 *)&str_game_7),str_casualty_4);
        }
        else {
          dialog_load_text_noflags(&local_324,((i32 *)&str_game_7),str_casualties_4);
        }
        dialog_add_sprite(&local_324,((i8 *)&popup_info_icon_sprite),0,0);
        dialog_set_image_zoom(&local_324,0);
        input_flush_events();
        snd_play_effect(0x30,0,0,0);
        dlg_show_modal(&local_324,0);
        if ((int)local_324.result_extra != 0) {
          casualty_timeline_show(human_civ[0]);
        }
      }
      else {
        dialog_load_text_noflags(&local_324,((i32 *)&str_game_7),str_ourturntomove_3);
        dialog_add_sprite(&local_324,((i8 *)&popup_info_icon_sprite),0,0);
        dialog_set_image_zoom(&local_324,0);
        input_flush_events();
        snd_play_effect(0x30,0,0,0);
        dlg_show_modal(&local_324,0);
      }
    }
    if (civ_saved_cursor_x_block.autoplay_active == 0) {
      game_turn_start_popups();
      if (civ_saved_cursor_x_block.mp_turn_time_limit_ms != 0) {
        mp_turn_timer_start(1);
      }
      game_player_move_loop();
    }
    else {
      map_views_block.saved_human_players = (uint)game.human_players;
      game.human_players = 0;
      if (civ_saved_cursor_x_block.mp_turn_time_limit_ms != 0) {
        mp_turn_timer_start(1);
      }
      ai_process_civ_units();
      game.human_players = (*(byte *)&map_views_block.saved_human_players);
      SVar2 = GetAsyncKeyState(0x1b);
      if (((int)SVar2 & 0x8001U) != 0) {
        civ_saved_cursor_x_block.autoplay_turns_left = 1;
      }
      civ_saved_cursor_x_block.autoplay_turns_left = civ_saved_cursor_x_block.autoplay_turns_left + -1;
      if (civ_saved_cursor_x_block.autoplay_turns_left == 0) {
        civ_saved_cursor_x_block.autoplay_active = 0;
      }
    }
    if (civ_saved_cursor_x_block.mp_turn_time_limit_ms != 0) {
      mp_turn_timer_stop(1);
    }
    status_redraw(1);
    net_send_state_diff(0xff,2,0,0,0);
    civ_saved_cursor_x_block.saved_turn_civ = 0;
    (*(byte *)&turn_resume_civ) = 0;
    civ_saved_cursor_x_block.saved_resume_new_game = 0;
    turn_resume_new_game = 0;
    game.field_06 = game.field_06 & 0xfffe;
    *(int *)(((i8 *)&dialog_text_font_obj_block.net_civ_phase_done) + human_civ[0] * 4) = *(int *)(((i8 *)&dialog_text_font_obj_block.net_civ_phase_done) + human_civ[0] * 4) + 1;
    XD_FlushSendBuffer(60000);
    dlg_pending_idle_callback = ((void *)(iptr)net_host_wait_human_moves_idle);
    popup_game_with_sprite(str_waithumanmoves,((i8 *)&popup_info_icon_sprite),0);
    local_30 = 0;
LAB_005aae35:
    if (local_30 == 0) {
      net_process_messages(((i32 *)&net_session_block.net_session),1,0);
      if (net_session_block.net_player_count[0] < 2) {
        local_30 = 1;
        goto LAB_005aaef1;
      }
      local_30 = 1;
      for (local_330 = 1; local_330 < 8; local_330 = local_330 + 1) {
        if ((((1 << ((byte)local_330 & 0x1f) & (uint)game.civs_alive) != 0) &&
            ((1 << ((byte)local_330 & 0x1f) & (uint)game.human_players) != 0)) &&
           (*(int *)(((i8 *)&dialog_text_font_obj_block.net_civ_phase_done) + local_330 * 4) == 0)) {
          local_30 = 0;
          break;
        }
      }
      goto LAB_005aae35;
    }
LAB_005aaef1:
    net_session_block.nm_human_move_complete_count = 0;
    net_check_lost_connections();
    if ((net_session_block.player_has_quit == '\0') || (net_session_block.mp_turn_civ == human_civ[0])) {
      for (local_328 = 0; local_328 < game.num_units; local_328 = local_328 + 1) {
        if ((units[local_328].id != 0) &&
           ((char)units[local_328].owner == local_330)) {
          unit_exhaust_moves(local_328);
        }
      }
      local_32c = (int)game.num_cities;
      while (local_32c = local_32c + -1, -1 < local_32c) {
        if (cities[local_32c].id != 0) {
          cities[local_32c].flags =
               cities[local_32c].flags & 0xffbfffff;
        }
      }
    }
    ui_pump_messages();
    if (game_loop_active == '\0') break;
    if ((game_loop_active != '\0') && (game_over_reason != 0)) {
      game_loop_active = '\0';
      break;
    }
  } while (game_loop_active != '\0');
  mp_turn_timer_stop(0);
  net_host_quit_handoff();
  if (game_over_reason != 0) {
    game_handle_game_over();
  }
  local_8 = 0xffffffff;
  /* inlined unwind funclet 005ab07f */ { dialog_dtor((void *)((iptr)&local_324)); }
  return;
}

/* 0x0055f5a3: pick a starting/setup choice for civ param_1 by scoring options
 * 1..n with civ_can_choose_government and taking the best score (ties go to the later one).
 * Ghidra lost the stack frame and passed garbage register/stack values to
 * civ_can_choose_government; the real call is civ_can_choose_government(civ, i). */
void __cdecl ai_choose_government(int param_1, int param_2)
{
    int count;          /* EBP-4 */
    int best_score;     /* EBP-8 */
    int diff;           /* EBP-0xc */
    int i;              /* EBP-0x10 */
    int best;           /* EBP-0x14 */

    if ((game.game_flags & 0x80) != 0 && ((short)prefs_game_rules_block.scenario_flags[0] & 0x10) != 0 &&
        (byte)civs[param_1].government >= 1)
        return;
    count = 6;
    if (param_2 != 0) {
        count--;
        if (_rand() % 3 != 0)
            count--;
    }
    if ((game.game_flags & 1) != 0) {
        diff = (uint)(byte)civs[game.player_civ].num_advances -
               (uint)(byte)civs[param_1].num_advances;
        if ((byte)game.power_rank[param_1] < 6) {
            if (diff > 6)
                civs[param_1].government_score[6] = -2;
            if (diff > 8)
                civs[param_1].government_score[5] = -1;
        }
    }
    if (civs[param_1].government_score[0] > 0) {
        count = 3;
        if ((byte)civs[param_1].government <= 5)
            count = 1;
    }
    best_score = -999;
    best = 1;
    for (i = 1; i <= count; i++) {
        /* (its other 19 parameters are a decompiler artifact, unused) */
        if (civ_can_choose_government(param_1, i, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) == 0)
            continue;
        if (civs[param_1].government_score[i] >= best_score) {
            best_score = civs[param_1].government_score[i];
            best = i;
        }
    }
    civ_change_government(param_1, best);
}
