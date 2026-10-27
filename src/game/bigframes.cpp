/*
 * Large functions whose generated translation contained EBP-relative code
 * (exception-unwind funclets run with the caller's EBP, or a lost stack slot).
 * Bodies follow the generated versions; the funclets are inlined as plain
 * code on the function's own locals, exception bookkeeping is dropped.
 */
#include "game.h"

/* 0x0041ba52: new-game setup dialogs (difficulty, enemies, barbarity, ...).
 * Unwind funclet 0x0041d3f2 destroys the dialog object at EBP-0x320 (dlg). */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __cdecl setup_new_game_dialogs(int setup_mode)

{
  byte rand_sign;
  int choice;
  uint year_abs;
  i32 label;
  char *label_text;
  int leader_arg;
  i32 option_arg;
  int year_c;
  int year_b;
  int year_a;
  int leader_i;
  int style_i;
  i8 female_flag;
  char barb_level;
  i8 custom_name[260];
  i32 result;
  int enemies_choice;
  int accel_choice;
  Dialog dlg;
  int opt_i;
  int leader_pick;
  int pick_opponents;
  int opp_number;
  int title_i;
  int tribe_choice;
  int difficulty_choice;
  int dlg_err;
  i32 unused_10;
  i32 unwind_state;
  
  unwind_state = 0xffffffff;
  result = 1;
  pick_opponents = 0;
  accel_choice = 0;
  dlg.Dialog::construct(0x2000);
  unwind_state = 0;
  leaders_fixup_names();
  game.field_0e = 0;
difficulty_dialog:
  do {
    do {
      ((SetupPicWindow *)((i8 *)&setup_picwnd_block.setup_picwnd))->show(3,6,3);
      dlg.load_game_section((const char *)str_difficulty_2,1);
      dlg.set_default_choice((int)prefs_game_rules_block.prefs_difficulty);
      dlg.set_position(
                         ((int)(caption_font_block.screen_width + -0x280 + (caption_font_block.screen_width + -0x280 >> 0x1f & 7U)) >> 3)
                         + 1,-(((int)(caption_font_block.screen_height + -0x1e0 + (caption_font_block.screen_height + -0x1e0 >> 0x1f & 7U))
                               >> 3) + 1));
      difficulty_choice = dlg.show_modal(0);
      snd_play_effect(0x6a,0,0,0);
      ((SetupPicWindow *)((i8 *)&setup_picwnd_block.setup_picwnd))->close();
      if (difficulty_choice < 0) {
cleanup_return:
        label = result;
        unwind_state = 0xffffffff;
        /* inlined unwind funclet 0041d3f2 */ { dlg.Dialog::destruct(); }
        return label;
      }
      game.difficulty = (byte)difficulty_choice;
      prefs_game_rules_block.prefs_difficulty = (short)difficulty_choice;
      ((SetupPicWindow *)((i8 *)&setup_picwnd_block.setup_picwnd))->show(1,6,4);
      dlg.load_game_section((const char *)str_enemies,1);
      dlg.set_default_choice((int)prefs_game_rules_block.prefs_enemies_choice);
      dlg.set_position(
                         -(((int)(caption_font_block.screen_width + -0x280 + (caption_font_block.screen_width + -0x280 >> 0x1f & 7U)) >> 3
                           ) + 1),-(((int)(caption_font_block.screen_height + -0x1e0 +
                                          (caption_font_block.screen_height + -0x1e0 >> 0x1f & 7U)) >> 3) + 1));
      enemies_choice = dlg.show_modal(0);
      snd_play_effect(0x6a,0,0,0);
      ((SetupPicWindow *)((i8 *)&setup_picwnd_block.setup_picwnd))->close();
    } while (enemies_choice < 0);
    if (dlg.result_extra == 0) {
      prefs_game_rules_block.prefs_enemies_choice = (short)enemies_choice;
      game.num_enemies = 6 - (char)enemies_choice;
    }
    else {
      choice = _rand();
      game.num_enemies = (char)(choice % 5) + 2;
    }
    ((SetupPicWindow *)((i8 *)&setup_picwnd_block.setup_picwnd))->show(3,6,5);
    dlg.load_game_section((const char *)str_barbarity,1);
    dlg.set_default_choice((int)prefs_game_rules_block.prefs_barbarity);
    dlg.set_position(
                       ((int)(caption_font_block.screen_width + -0x280 + (caption_font_block.screen_width + -0x280 >> 0x1f & 7U)) >> 3) +
                       1,-(((int)(caption_font_block.screen_height + -0x1e0 + (caption_font_block.screen_height + -0x1e0 >> 0x1f & 7U)) >> 3
                           ) + 1));
    choice = dlg.show_modal(0);
    snd_play_effect(0x6a,0,0,0);
    ((SetupPicWindow *)((i8 *)&setup_picwnd_block.setup_picwnd))->close();
  } while (choice < 0);
  if (dlg.result_extra == 0) {
    barb_level = (char)choice;
    game.barbarian_activity = barb_level;
    prefs_game_rules_block.prefs_barbarity = (short)choice;
  }
  else if (game.difficulty < 2) {
    choice = _rand();
    rand_sign = (byte)(choice >> 0x1f);
    game.barbarian_activity = ((((byte)choice ^ rand_sign) - rand_sign & 1 ^ rand_sign) - rand_sign) + game.difficulty;
  }
  else if (game.difficulty < 5) {
    choice = _rand();
    game.barbarian_activity = (char)(choice % 3) + '\x01';
  }
  else {
    choice = _rand();
    rand_sign = (byte)(choice >> 0x1f);
    game.barbarian_activity = ((((byte)choice ^ rand_sign) - rand_sign & 1 ^ rand_sign) - rand_sign) + '\x02';
  }
  do {
    game.rules = 0x3f;
    ((SetupPicWindow *)((i8 *)&setup_picwnd_block.setup_picwnd))->show(1,6,9);
    dlg.load_game_section((const char *)str_rules_2,1);
    dlg.set_default_choice((int)prefs_game_rules_block.prefs_rules_choice);
    dlg.set_position(
                       -(((int)(caption_font_block.screen_width + -0x280 + (caption_font_block.screen_width + -0x280 >> 0x1f & 7U)) >> 3)
                        + 1),-(((int)(caption_font_block.screen_height + -0x1e0 + (caption_font_block.screen_height + -0x1e0 >> 0x1f & 7U))
                               >> 3) + 1));
    choice = dlg.show_modal(0);
    snd_play_effect(0x6a,0,0,0);
    ((SetupPicWindow *)((i8 *)&setup_picwnd_block.setup_picwnd))->close();
    if (choice < 0) goto cleanup_return;
    prefs_game_rules_block.prefs_rules_choice = (short)choice;
    if (choice == 0) goto leaders_setup;
    game.rules = prefs_game_rules_block.prefs_game_rules[0];
    if (setup_mode == 1) {
      game.rules = prefs_game_rules_block.prefs_game_rules[0] & 0x7fff;
    }
    else if (setup_mode == 2) {
      game.rules = prefs_game_rules_block.prefs_game_rules[0] | 0x8000;
    }
    dlg_checks_clear();
    dlg_check_set(0,(uint)((game.rules & 0x10) == 0));
    dlg_check_set(1,game.rules & 0x8000);
    dlg_check_set(2,0);
    dlg_check_set(3,(int)prefs_game_rules_block.prefs_accelerated_start);
    dlg_check_set(4,game.rules & 0x80);
    dlg_check_set(5,game.rules & 0x100);
    ((SetupPicWindow *)((i8 *)&setup_picwnd_block.setup_picwnd))->show(3,6,9);
    dlg.load_text_section((const char *)&str_game_7,(const char *)str_advanced,0,0,0,0,0,0);
    if (((byte)dlg.style_flags & 4) != 0) {
      for (opt_i = 0; opt_i < (int)dlg.option_count; opt_i = opt_i + 1) {
        dlg.set_option_checked(opt_i,1 << ((byte)opt_i & 0x1f) & dlg_check_bits);
      }
    }
    dlg.set_position(
                       ((int)(caption_font_block.screen_width + -0x280 + (caption_font_block.screen_width + -0x280 >> 0x1f & 7U)) >> 3) +
                       1,-(((int)(caption_font_block.screen_height + -0x1e0 + (caption_font_block.screen_height + -0x1e0 >> 0x1f & 7U)) >> 3
                           ) + 1));
    dlg.show_modal(0);
    snd_play_effect(0x6a,0,0,0);
    ((SetupPicWindow *)((i8 *)&setup_picwnd_block.setup_picwnd))->close();
    dlg_help_pressed = (int)dlg.result_extra;
    if (((byte)dlg.style_flags & 4) != 0) {
      dlg_check_bits = 0;
      for (opt_i = 0; opt_i < (int)dlg.option_count; opt_i = opt_i + 1) {
        choice = dlg.option_is_checked(opt_i);
        if (choice != 0) {
          dlg_check_bits = dlg_check_bits | 1 << ((byte)opt_i & 0x1f);
        }
      }
    }
    game.rules = 0x2f;
    choice = dlg_check_get(0);
    if (choice == 0) {
      game.rules = game.rules | 0x10;
    }
    choice = dlg_check_get(1);
    if (choice != 0) {
      game.rules = game.rules | 0x8000;
    }
    pick_opponents = dlg_check_get(2);
    accel_choice = dlg_check_get(3);
    choice = dlg_check_get(4);
    if (choice != 0) {
      game.rules = game.rules | 0x80;
    }
    choice = dlg_check_get(5);
    if (choice != 0) {
      game.rules = game.rules | 0x100;
    }
    if (setup_mode == 0) {
      prefs_game_rules_block.prefs_game_rules[0] = game.rules;
    }
    else {
      prefs_game_rules_block.prefs_game_rules[0] = game.rules & 0x7fff | prefs_game_rules_block.prefs_game_rules[0] & 0x8000;
    }
    if (accel_choice == 0) break;
    game.first_launch_turn = 0xffff;
    choice = game_turn_to_year(0);
    if (choice < 1) {
      year_abs = game_turn_to_year(0);
      year_a = ~year_abs + 1;
    }
    else {
      year_a = game_turn_to_year(0);
    }
    text_set_number_arg(0,year_a);
    choice = game_turn_to_year(0x15);
    if (choice < 1) {
      year_abs = game_turn_to_year(0x15);
      year_b = ~year_abs + 1;
    }
    else {
      year_b = game_turn_to_year(0x15);
    }
    text_set_number_arg(1,year_b);
    choice = game_turn_to_year(0x29);
    if (choice < 1) {
      year_abs = game_turn_to_year(0x29);
      year_c = ~year_abs + 1;
    }
    else {
      year_c = game_turn_to_year(0x29);
    }
    text_set_number_arg(2,year_c);
    ((SetupPicWindow *)((i8 *)&setup_picwnd_block.setup_picwnd))->show(1,6,9);
    dlg.load_game_section((const char *)str_accelerated,1);
    dlg.set_default_choice((int)prefs_game_rules_block.prefs_accelerated_start);
    dlg.set_position(
                       -(((int)(caption_font_block.screen_width + -0x280 + (caption_font_block.screen_width + -0x280 >> 0x1f & 7U)) >> 3)
                        + 1),-(((int)(caption_font_block.screen_height + -0x1e0 + (caption_font_block.screen_height + -0x1e0 >> 0x1f & 7U))
                               >> 3) + 1));
    accel_choice = dlg.show_modal(0);
    snd_play_effect(0x6a,0,0,0);
    ((SetupPicWindow *)((i8 *)&setup_picwnd_block.setup_picwnd))->close();
  } while (accel_choice < 0);
  prefs_game_rules_block.prefs_accelerated_start = (short)accel_choice;
leaders_setup:
  do {
    for (leader_i = 0; leader_i < 0x15; leader_i = leader_i + 1) {
      if (leaders[leader_i].leader_name < 1) {
        leaders[leader_i].leader_name =
             ~leaders[leader_i].leader_name + 1;
      }
      if (leaders[leader_i].plural < 1) {
        leaders[leader_i].plural =
             ~leaders[leader_i].plural + 1;
      }
      if (leaders[leader_i].adjective < 1) {
        leaders[leader_i].adjective =
             ~leaders[leader_i].adjective + 1;
      }
      for (title_i = 0; title_i < 7; title_i = title_i + 1) {
        if (leaders[leader_i].titles[title_i][0] < 1) {
          leaders[leader_i].titles[title_i][0] =
               ~leaders[leader_i].titles[title_i][0] + 1;
        }
        if (leaders[leader_i].titles[title_i][1] < 1) {
          leaders[leader_i].titles[title_i][1] =
               ~leaders[leader_i].titles[title_i][1] + 1;
        }
      }
    }
    ((SetupPicWindow *)((i8 *)&setup_picwnd_block.setup_picwnd))->show(2,6,6);
    dlg.load_game_section((const char *)str_gender,1);
    dlg.set_default_choice((int)prefs_game_rules_block.prefs_gender);
    dlg.set_position(0xfffffc19,
                       -(((int)(caption_font_block.screen_height + -0x1e0 + (caption_font_block.screen_height + -0x1e0 >> 0x1f & 7U)) >> 3)
                        + 1));
    choice = dlg.show_modal(0);
    snd_play_effect(0x6a,0,0,0);
    ((SetupPicWindow *)((i8 *)&setup_picwnd_block.setup_picwnd))->close();
    if (choice < 0) goto difficulty_dialog;
    prefs_game_rules_block.prefs_gender = (short)choice;
    ((SetupPicWindow *)((i8 *)&setup_picwnd_block.setup_picwnd))->show(2,6,7);
    dlg_err = dlg.load_text((const char *)&str_game,(const char *)str_tribe,1);
    if (dlg_err != 0) {
      ((SetupPicWindow *)((i8 *)&setup_picwnd_block.setup_picwnd))->close();
      goto cleanup_return;
    }
    dlg.set_columns(3);
    for (leader_i = 0; leader_i < 0x15; leader_i = leader_i + 1) {
      option_arg = 0;
      leader_arg = leader_i;
      label_text = label_string((int)leaders[leader_i].plural);
      dlg.add_option((const char *)label_text,leader_arg,option_arg);
    }
    dlg.set_default_choice((int)prefs_game_rules_block.prefs_tribe);
    dlg.set_position(0xfffffc19,
                       -(((int)(caption_font_block.screen_height + -0x1e0 + (caption_font_block.screen_height + -0x1e0 >> 0x1f & 7U)) >> 3)
                        + 1));
    tribe_choice = dlg.show_modal(0);
    snd_play_effect(0x6a,0,0,0);
    ((SetupPicWindow *)((i8 *)&setup_picwnd_block.setup_picwnd))->close();
    if (-1 < tribe_choice) {
      game.player_civ = leaders[tribe_choice].color;
      prefs_game_rules_block.prefs_tribe = (short)tribe_choice;
      civs[game.player_civ].tribe = prefs_game_rules_block.prefs_tribe;
      civs[game.player_civ].leader_portrait = (i8)tribe_choice;
      if (choice != 0) {
        civs[game.player_civ].leader_portrait =
             civs[game.player_civ].leader_portrait + '\x15';
      }
      human_civ[0] = (int)game.player_civ;
      game.human_players = (byte)(1 << (game.player_civ & 0x1f));
      female_flag = (i8)choice;
      leaders[civs[game.player_civ].tribe].female = female_flag;
      leaders[civs[game.player_civ].tribe].leader_name
           = leaders[civs[game.player_civ].tribe].names[(uint)(&leaders[0].female)
                          [civs[game.player_civ].tribe * 0x30]];
      label_text = label_string((int)leaders[civs[game.player_civ].tribe].leader_name);
      crt_strcpy(&civ_names[game.player_civ].leader_name[0],label_text);
      leaders[civs[game.player_civ].tribe].leader_name =
           -leaders[civs[game.player_civ].tribe].leader_name;
      if (dlg.result_extra == 0) {
        ((SetupPicWindow *)((i8 *)&setup_picwnd_block.setup_picwnd))->show(2,6,7);
        dlg.load_text_section((const char *)&str_game_7,(const char *)&str_name,0x17,
                           (iptr)&civ_names[game.player_civ].leader_name[0],0,0,0,1);
        dlg.set_position(0xfffffc19,
                           -(((int)(caption_font_block.screen_height + -0x1e0 + (caption_font_block.screen_height + -0x1e0 >> 0x1f & 7U)) >>
                             3) + 1));
        dlg_err = dlg.run_modal((iptr)custom_name,0);
        snd_play_effect(0x6a,0,0,0);
        ((SetupPicWindow *)((i8 *)&setup_picwnd_block.setup_picwnd))->close();
        if (dlg_err != 0) goto leaders_setup;
        crt_strcpy(&civ_names[game.player_civ].leader_name[0],custom_name);
      }
      else {
        label_text = label_string((int)leaders[civs[game.player_civ].tribe].plural);
        crt_strcpy(&civ_names[game.player_civ].tribe_name[0],label_text);
        label_text = label_string((int)leaders[civs[game.player_civ].tribe].adjective);
        crt_strcpy(&civ_names[game.player_civ].adjective[0],label_text);
        leaders[civs[game.player_civ].tribe].plural =
             -leaders[civs[game.player_civ].tribe].plural;
        leaders[civs[game.player_civ].tribe].adjective =
             -leaders[civs[game.player_civ].tribe].adjective;
        for (title_i = 0; title_i < 7; title_i = title_i + 1) {
          label_text = label_string((int)leaders[civs[game.player_civ].tribe].titles[title_i][choice]);
          crt_strcpy(&civ_names[game.player_civ].titles[title_i][0],label_text);
          leaders[civs[game.player_civ].tribe].titles[title_i][choice] =
               -leaders[civs[game.player_civ].tribe].titles[title_i][choice]
          ;
        }
        while( true ) {
          while( true ) {
            text_set_string_arg_b(1,(const char *)&civ_names[game.player_civ].tribe_name[0]);
            text_set_string_arg_b(2,(const char *)&civ_names[game.player_civ].adjective[0]);
            ((SetupPicWindow *)((i8 *)&setup_picwnd_block.setup_picwnd))->show(2,6,7);
            dlg_err = dlg.load_text_section((const char *)&str_game_7,(const char *)str_customtribe,0x17,
                                          (iptr)&civ_names[game.player_civ].leader_name[0],0,0,0,1);
            if (dlg_err != 0) {
              ((SetupPicWindow *)((i8 *)&setup_picwnd_block.setup_picwnd))->close();
              goto cleanup_return;
            }
            dlg.set_position(0xfffffc19,
                               -(((int)(caption_font_block.screen_height + -0x1e0 + (caption_font_block.screen_height + -0x1e0 >> 0x1f & 7U)
                                       ) >> 3) + 1));
            choice = dlg.show_modal(0);
            snd_play_effect(0x6a,0,0,0);
            ((SetupPicWindow *)((i8 *)&setup_picwnd_block.setup_picwnd))->close();
            if (choice < 0) goto leaders_setup;
            crt_strcpy(&civ_names[game.player_civ].leader_name[0],((i8 *)&minimap_window_block.text_string_args));
            crt_strcpy(&civ_names[game.player_civ].tribe_name[0],((i8 *)&minimap_window_block.text_string_arg1));
            crt_strcpy(&civ_names[game.player_civ].adjective[0],((i8 *)&minimap_window_block.text_string_arg2));
            if ((int)dlg.result_extra != 1) break;
            ((SetupPicWindow *)((i8 *)&setup_picwnd_block.setup_picwnd))->show(2,6,7);
            dlg_err = dlg.load_game_section((const char *)str_customtribe2,1);
            if (dlg_err != 0) {
              ((SetupPicWindow *)((i8 *)&setup_picwnd_block.setup_picwnd))->close();
              goto cleanup_return;
            }
            dlg_err = 0;
            for (title_i = 0; title_i < 7; title_i = title_i + 1) {
              text_clear();
              text_append_string_id(government_names[title_i]);
              text_append_colon();
              dlg.add_edit_field((const char *)&map_views_block.text_buffer,
                                 (iptr)&civ_names[game.player_civ].titles[title_i][0],0x17);
            }
            dlg.set_position(0xfffffc19,
                               -(((int)(caption_font_block.screen_height + -0x1e0 + (caption_font_block.screen_height + -0x1e0 >> 0x1f & 7U)
                                       ) >> 3) + 1));
            choice = dlg.show_modal(0);
            if (choice == 0) {
              for (title_i = 0; title_i < 7; title_i = title_i + 1) {
                crt_strcpy(&civ_names[game.player_civ].titles[title_i][0],
                             ((i8 *)&minimap_window_block.text_string_args) + title_i * 0x104);
              }
            }
            snd_play_effect(0x6a,0,0,0);
            ((SetupPicWindow *)((i8 *)&setup_picwnd_block.setup_picwnd))->close();
          }
          if ((int)dlg.result_extra != 2) break;
          portrait_dlg_show((int)game.player_civ);
        }
      }
city_style_dialog:
      ((SetupPicWindow *)((i8 *)&setup_picwnd_block.setup_picwnd))->show(1,6,8);
      dlg.load_game_section((const char *)str_customcity,0x20001);
      for (style_i = 0; style_i < 4; style_i = style_i + 1) {
        label_text = label_string(label_string_ids[0xf6 + style_i]);
        dlg.add_sprite(style_i * 0x1e0 + (iptr)(((u8 *)&gfx_sheet_surface_block.city_walled_sprites + 360)),style_i,(const char *)label_text);
      }
      dlg.set_default_choice(
                         (int)leaders[civs[game.player_civ].tribe].city_style);
      dlg.set_position(
                         -(((int)(caption_font_block.screen_width + -0x280 + (caption_font_block.screen_width + -0x280 >> 0x1f & 7U)) >> 3
                           ) + 1),-(((int)(caption_font_block.screen_height + -0x1e0 +
                                          (caption_font_block.screen_height + -0x1e0 >> 0x1f & 7U)) >> 3) + 1));
      choice = dlg.show_modal(0);
      snd_play_effect(0x6a,0,0,0);
      ((SetupPicWindow *)((i8 *)&setup_picwnd_block.setup_picwnd))->close();
      if (-1 < choice) {
        civ_names[game.player_civ].city_style = (short)choice;
        game.civs_alive = game.human_players | 1;
        for (title_i = 0; title_i < (int)(uint)game.num_enemies; title_i = title_i + 1) {
          choice = _rand();
          (*((char *)&leader_i + 0)) = (byte)(choice >> 0x1f);
          (*((char *)&leader_i + 0)) =
               (((byte)choice ^ (byte)leader_i) - (byte)leader_i & 7 ^ (byte)leader_i) -
               (byte)leader_i;
          if ((1 << ((byte)leader_i & 0x1f) & (uint)game.civs_alive) == 0) {
            game.civs_alive = game.civs_alive | (byte)(1 << ((byte)leader_i & 0x1f));
          }
          else {
            title_i = title_i + -1;
          }
        }
        if (pick_opponents != 0) {
          opp_number = 0;
          leader_i = 1;
          do {
            if (7 < leader_i) break;
            if (((1 << ((byte)leader_i & 0x1f) & (uint)game.human_players) == 0) &&
               ((1 << ((byte)leader_i & 0x1f) & (uint)game.civs_alive) != 0)) {
              opp_number = opp_number + 1;
              text_set_number_arg(0,opp_number);
              ((SetupPicWindow *)((i8 *)&setup_picwnd_block.setup_picwnd))->show(2,6,9);
              dlg.load_game_section((const char *)str_opponent,1);
              dlg.option_list->id = 0x15;
              for (leader_pick = 0; leader_pick < 0x15; leader_pick = leader_pick + 1) {
                if (leaders[leader_pick].color == leader_i) {
                  text_clear();
                  text_append_string_id((int)leaders[leader_pick].plural);
                  text_append_space();
                  text_append_lparen();
                  text_append_string_id((int)leaders[leader_pick].leader_name);
                  text_append_rparen();
                  dlg.add_option((const char *)&map_views_block.text_buffer,leader_pick,0);
                }
              }
              dlg.set_position(0xfffffc19,
                                 -(((int)(caption_font_block.screen_height + -0x1e0 +
                                         (caption_font_block.screen_height + -0x1e0 >> 0x1f & 7U)) >> 3) + 1));
              leader_pick = dlg.show_modal(0);
              snd_play_effect(0x6a,0,0,0);
              ((SetupPicWindow *)((i8 *)&setup_picwnd_block.setup_picwnd))->close();
              if (leader_pick < 0) goto city_style_dialog;
              if (leader_pick < 0x15) {
                (((i8 *)&setup_chosen_leaders))[leader_i] = (i8)leader_pick;
              }
            }
            leader_i = leader_i + 1;
          } while( true );
        }
        prefs_save_civ2dat();
        rules_load_advances(1);
        rules_load_units(1);
        rules_load_improvements(1);
        snd_menu_end();
        map_generate(setup_mode);
        game_init_new();
        if (accel_choice != 0) {
          game_accelerated_start(accel_choice + -1);
        }
        civ_intro_popup((int)game.player_civ);
        result = 0;
        goto cleanup_return;
      }
    }
  } while( true );
}

/* 0x004d17bf: unwind funclet 0x004d4a11 destroys the control at EBP-0x12c (surf_1eb). */
i32 SpaceshipWindow::render_ship()

{
  byte part_count;
  int load_ok;
  i8 sprite_final[16];
  i8 sprite_part[16];
  i8 sprite_struct[16];
  i32 fail_ret_12;
  i8 sprite_core[16];
  i32 fail_ret_11;
  i32 fail_ret_10;
  i32 fail_ret_9;
  i32 fail_ret_8;
  i32 fail_ret_7;
  i32 fail_ret_6;
  i32 fail_ret_5;
  i32 fail_ret_4;
  i32 fail_ret_3;
  i32 fail_ret_2;
  i32 result;
  i8 surf_1ea[72];
  i8 surf_1d6[72];
  struct { u8 kind; u8 count; u8 pad[2]; i32 v[6]; } part_rows[88];  /* the spaceship structure rows */
  i8 surf_part[72];
  int row_i;
  i8 surf_1b9[72];
  i8 surf_1c8[72];
  i8 surf_1e1[72];
  i8 surf_1e0[72];
  int struct_row;
  i8 surf_1ba[72];
  i8 surf_1eb[72];
  i8 surf_1e9[72];
  i8 surf_1d7[72];
  i8 surf_1c7[72];
  i32 unused_10;
  int unwind_state;
  
  unwind_state = 0xffffffff;
  surface_ctor((DibSurface *)surf_part);
  unwind_state = 0;
  surface_ctor((DibSurface *)surf_1b9);
  (*((char *)&unwind_state + 0)) = 1;
  surface_ctor((DibSurface *)surf_1e0);
  (*((char *)&unwind_state + 0)) = 2;
  surface_ctor((DibSurface *)surf_1c7);
  (*((char *)&unwind_state + 0)) = 3;
  surface_ctor((DibSurface *)surf_1ea);
  (*((char *)&unwind_state + 0)) = 4;
  surface_ctor((DibSurface *)surf_1d6);
  (*((char *)&unwind_state + 0)) = 5;
  surface_ctor((DibSurface *)surf_1eb);
  (*((char *)&unwind_state + 0)) = 6;
  surface_ctor((DibSurface *)surf_1ba);
  (*((char *)&unwind_state + 0)) = 7;
  surface_ctor((DibSurface *)surf_1e1);
  (*((char *)&unwind_state + 0)) = 8;
  surface_ctor((DibSurface *)surf_1c8);
  (*((char *)&unwind_state + 0)) = 9;
  surface_ctor((DibSurface *)surf_1e9);
  (*((char *)&unwind_state + 0)) = 10;
  surface_ctor((DibSurface *)surf_1d7);
  (*((char *)&unwind_state + 0)) = 0xb;
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
  load_ok = ((DibSurface *)surf_1b9)->load_gif_resource(0x1b9,10,0xec,(iptr)this + 0x1f8);
  if (load_ok == 0) {
    result = 0;
    (*((char *)&unwind_state + 0)) = 10;
    /* inlined unwind funclet 004d49d5 */ { surface_dtor((DibSurface *)(&surf_1d7)); }
    (*((char *)&unwind_state + 0)) = 9;
    /* inlined unwind funclet 004d49e1 */ { surface_dtor((DibSurface *)(&surf_1e9)); }
    (*((char *)&unwind_state + 0)) = 8;
    /* inlined unwind funclet 004d49ed */ { surface_dtor((DibSurface *)(&surf_1c8)); }
    (*((char *)&unwind_state + 0)) = 7;
    /* inlined unwind funclet 004d49f9 */ { surface_dtor((DibSurface *)(&surf_1e1)); }
    (*((char *)&unwind_state + 0)) = 6;
    /* inlined unwind funclet 004d4a05 */ { surface_dtor((DibSurface *)(&surf_1ba)); }
    (*((char *)&unwind_state + 0)) = 5;
    /* inlined unwind funclet 004d4a11 */ { surface_dtor((DibSurface *)(&surf_1eb)); }
    (*((char *)&unwind_state + 0)) = 4;
    /* inlined unwind funclet 004d4a1d */ { surface_dtor((DibSurface *)(&surf_1d6)); }
    (*((char *)&unwind_state + 0)) = 3;
    /* inlined unwind funclet 004d4a29 */ { surface_dtor((DibSurface *)(&surf_1ea)); }
    (*((char *)&unwind_state + 0)) = 2;
    /* inlined unwind funclet 004d4a35 */ { surface_dtor((DibSurface *)(&surf_1c7)); }
    (*((char *)&unwind_state + 0)) = 1;
    /* inlined unwind funclet 004d4a3e */ { surface_dtor((DibSurface *)(&surf_1e0)); }
    unwind_state = unwind_state & 0xffffff00;
    /* inlined unwind funclet 004d4a4a */ { surface_dtor((DibSurface *)(&surf_1b9)); }
    unwind_state = 0xffffffff;
    /* inlined unwind funclet 004d4a56 */ { surface_dtor((DibSurface *)(&surf_part)); }
  }
  else {
    win_flush_pending_msgs();
    load_ok = ((DibSurface *)surf_1e0)->load_gif_resource(0x1e0,10,0xec,(iptr)this + 0x1f8);
    if (load_ok == 0) {
      fail_ret_2 = 0;
      (*((char *)&unwind_state + 0)) = 10;
      /* inlined unwind funclet 004d49d5 */ { surface_dtor((DibSurface *)(&surf_1d7)); }
      (*((char *)&unwind_state + 0)) = 9;
      /* inlined unwind funclet 004d49e1 */ { surface_dtor((DibSurface *)(&surf_1e9)); }
      (*((char *)&unwind_state + 0)) = 8;
      /* inlined unwind funclet 004d49ed */ { surface_dtor((DibSurface *)(&surf_1c8)); }
      (*((char *)&unwind_state + 0)) = 7;
      /* inlined unwind funclet 004d49f9 */ { surface_dtor((DibSurface *)(&surf_1e1)); }
      (*((char *)&unwind_state + 0)) = 6;
      /* inlined unwind funclet 004d4a05 */ { surface_dtor((DibSurface *)(&surf_1ba)); }
      (*((char *)&unwind_state + 0)) = 5;
      /* inlined unwind funclet 004d4a11 */ { surface_dtor((DibSurface *)(&surf_1eb)); }
      (*((char *)&unwind_state + 0)) = 4;
      /* inlined unwind funclet 004d4a1d */ { surface_dtor((DibSurface *)(&surf_1d6)); }
      (*((char *)&unwind_state + 0)) = 3;
      /* inlined unwind funclet 004d4a29 */ { surface_dtor((DibSurface *)(&surf_1ea)); }
      (*((char *)&unwind_state + 0)) = 2;
      /* inlined unwind funclet 004d4a35 */ { surface_dtor((DibSurface *)(&surf_1c7)); }
      (*((char *)&unwind_state + 0)) = 1;
      /* inlined unwind funclet 004d4a3e */ { surface_dtor((DibSurface *)(&surf_1e0)); }
      unwind_state = unwind_state & 0xffffff00;
      /* inlined unwind funclet 004d4a4a */ { surface_dtor((DibSurface *)(&surf_1b9)); }
      unwind_state = 0xffffffff;
      /* inlined unwind funclet 004d4a56 */ { surface_dtor((DibSurface *)(&surf_part)); }
      result = fail_ret_2;
    }
    else {
      win_flush_pending_msgs();
      load_ok = ((DibSurface *)surf_1c7)->load_gif_resource(0x1c7,10,0xec,(iptr)this + 0x1f8);
      if (load_ok == 0) {
        fail_ret_3 = 0;
        (*((char *)&unwind_state + 0)) = 10;
        /* inlined unwind funclet 004d49d5 */ { surface_dtor((DibSurface *)(&surf_1d7)); }
        (*((char *)&unwind_state + 0)) = 9;
        /* inlined unwind funclet 004d49e1 */ { surface_dtor((DibSurface *)(&surf_1e9)); }
        (*((char *)&unwind_state + 0)) = 8;
        /* inlined unwind funclet 004d49ed */ { surface_dtor((DibSurface *)(&surf_1c8)); }
        (*((char *)&unwind_state + 0)) = 7;
        /* inlined unwind funclet 004d49f9 */ { surface_dtor((DibSurface *)(&surf_1e1)); }
        (*((char *)&unwind_state + 0)) = 6;
        /* inlined unwind funclet 004d4a05 */ { surface_dtor((DibSurface *)(&surf_1ba)); }
        (*((char *)&unwind_state + 0)) = 5;
        /* inlined unwind funclet 004d4a11 */ { surface_dtor((DibSurface *)(&surf_1eb)); }
        (*((char *)&unwind_state + 0)) = 4;
        /* inlined unwind funclet 004d4a1d */ { surface_dtor((DibSurface *)(&surf_1d6)); }
        (*((char *)&unwind_state + 0)) = 3;
        /* inlined unwind funclet 004d4a29 */ { surface_dtor((DibSurface *)(&surf_1ea)); }
        (*((char *)&unwind_state + 0)) = 2;
        /* inlined unwind funclet 004d4a35 */ { surface_dtor((DibSurface *)(&surf_1c7)); }
        (*((char *)&unwind_state + 0)) = 1;
        /* inlined unwind funclet 004d4a3e */ { surface_dtor((DibSurface *)(&surf_1e0)); }
        unwind_state = unwind_state & 0xffffff00;
        /* inlined unwind funclet 004d4a4a */ { surface_dtor((DibSurface *)(&surf_1b9)); }
        unwind_state = 0xffffffff;
        /* inlined unwind funclet 004d4a56 */ { surface_dtor((DibSurface *)(&surf_part)); }
        result = fail_ret_3;
      }
      else {
        win_flush_pending_msgs();
        load_ok = ((DibSurface *)surf_1ea)->load_gif_resource(0x1ea,10,0xec,(iptr)this + 0x1f8);
        if (load_ok == 0) {
          fail_ret_4 = 0;
          (*((char *)&unwind_state + 0)) = 10;
          /* inlined unwind funclet 004d49d5 */ { surface_dtor((DibSurface *)(&surf_1d7)); }
          (*((char *)&unwind_state + 0)) = 9;
          /* inlined unwind funclet 004d49e1 */ { surface_dtor((DibSurface *)(&surf_1e9)); }
          (*((char *)&unwind_state + 0)) = 8;
          /* inlined unwind funclet 004d49ed */ { surface_dtor((DibSurface *)(&surf_1c8)); }
          (*((char *)&unwind_state + 0)) = 7;
          /* inlined unwind funclet 004d49f9 */ { surface_dtor((DibSurface *)(&surf_1e1)); }
          (*((char *)&unwind_state + 0)) = 6;
          /* inlined unwind funclet 004d4a05 */ { surface_dtor((DibSurface *)(&surf_1ba)); }
          (*((char *)&unwind_state + 0)) = 5;
          /* inlined unwind funclet 004d4a11 */ { surface_dtor((DibSurface *)(&surf_1eb)); }
          (*((char *)&unwind_state + 0)) = 4;
          /* inlined unwind funclet 004d4a1d */ { surface_dtor((DibSurface *)(&surf_1d6)); }
          (*((char *)&unwind_state + 0)) = 3;
          /* inlined unwind funclet 004d4a29 */ { surface_dtor((DibSurface *)(&surf_1ea)); }
          (*((char *)&unwind_state + 0)) = 2;
          /* inlined unwind funclet 004d4a35 */ { surface_dtor((DibSurface *)(&surf_1c7)); }
          (*((char *)&unwind_state + 0)) = 1;
          /* inlined unwind funclet 004d4a3e */ { surface_dtor((DibSurface *)(&surf_1e0)); }
          unwind_state = unwind_state & 0xffffff00;
          /* inlined unwind funclet 004d4a4a */ { surface_dtor((DibSurface *)(&surf_1b9)); }
          unwind_state = 0xffffffff;
          /* inlined unwind funclet 004d4a56 */ { surface_dtor((DibSurface *)(&surf_part)); }
          result = fail_ret_4;
        }
        else {
          win_flush_pending_msgs();
          load_ok = ((DibSurface *)surf_1d6)->load_gif_resource(0x1d6,10,0xec,(iptr)this + 0x1f8);
          if (load_ok == 0) {
            fail_ret_5 = 0;
            (*((char *)&unwind_state + 0)) = 10;
            /* inlined unwind funclet 004d49d5 */ { surface_dtor((DibSurface *)(&surf_1d7)); }
            (*((char *)&unwind_state + 0)) = 9;
            /* inlined unwind funclet 004d49e1 */ { surface_dtor((DibSurface *)(&surf_1e9)); }
            (*((char *)&unwind_state + 0)) = 8;
            /* inlined unwind funclet 004d49ed */ { surface_dtor((DibSurface *)(&surf_1c8)); }
            (*((char *)&unwind_state + 0)) = 7;
            /* inlined unwind funclet 004d49f9 */ { surface_dtor((DibSurface *)(&surf_1e1)); }
            (*((char *)&unwind_state + 0)) = 6;
            /* inlined unwind funclet 004d4a05 */ { surface_dtor((DibSurface *)(&surf_1ba)); }
            (*((char *)&unwind_state + 0)) = 5;
            /* inlined unwind funclet 004d4a11 */ { surface_dtor((DibSurface *)(&surf_1eb)); }
            (*((char *)&unwind_state + 0)) = 4;
            /* inlined unwind funclet 004d4a1d */ { surface_dtor((DibSurface *)(&surf_1d6)); }
            (*((char *)&unwind_state + 0)) = 3;
            /* inlined unwind funclet 004d4a29 */ { surface_dtor((DibSurface *)(&surf_1ea)); }
            (*((char *)&unwind_state + 0)) = 2;
            /* inlined unwind funclet 004d4a35 */ { surface_dtor((DibSurface *)(&surf_1c7)); }
            (*((char *)&unwind_state + 0)) = 1;
            /* inlined unwind funclet 004d4a3e */ { surface_dtor((DibSurface *)(&surf_1e0)); }
            unwind_state = unwind_state & 0xffffff00;
            /* inlined unwind funclet 004d4a4a */ { surface_dtor((DibSurface *)(&surf_1b9)); }
            unwind_state = 0xffffffff;
            /* inlined unwind funclet 004d4a56 */ { surface_dtor((DibSurface *)(&surf_part)); }
            result = fail_ret_5;
          }
          else {
            win_flush_pending_msgs();
            load_ok = ((DibSurface *)surf_1ba)->load_gif_resource(0x1ba,10,0xec,(iptr)this + 0x1f8);
            if (load_ok == 0) {
              fail_ret_6 = 0;
              (*((char *)&unwind_state + 0)) = 10;
              /* inlined unwind funclet 004d49d5 */ { surface_dtor((DibSurface *)(&surf_1d7)); }
              (*((char *)&unwind_state + 0)) = 9;
              /* inlined unwind funclet 004d49e1 */ { surface_dtor((DibSurface *)(&surf_1e9)); }
              (*((char *)&unwind_state + 0)) = 8;
              /* inlined unwind funclet 004d49ed */ { surface_dtor((DibSurface *)(&surf_1c8)); }
              (*((char *)&unwind_state + 0)) = 7;
              /* inlined unwind funclet 004d49f9 */ { surface_dtor((DibSurface *)(&surf_1e1)); }
              (*((char *)&unwind_state + 0)) = 6;
              /* inlined unwind funclet 004d4a05 */ { surface_dtor((DibSurface *)(&surf_1ba)); }
              (*((char *)&unwind_state + 0)) = 5;
              /* inlined unwind funclet 004d4a11 */ { surface_dtor((DibSurface *)(&surf_1eb)); }
              (*((char *)&unwind_state + 0)) = 4;
              /* inlined unwind funclet 004d4a1d */ { surface_dtor((DibSurface *)(&surf_1d6)); }
              (*((char *)&unwind_state + 0)) = 3;
              /* inlined unwind funclet 004d4a29 */ { surface_dtor((DibSurface *)(&surf_1ea)); }
              (*((char *)&unwind_state + 0)) = 2;
              /* inlined unwind funclet 004d4a35 */ { surface_dtor((DibSurface *)(&surf_1c7)); }
              (*((char *)&unwind_state + 0)) = 1;
              /* inlined unwind funclet 004d4a3e */ { surface_dtor((DibSurface *)(&surf_1e0)); }
              unwind_state = unwind_state & 0xffffff00;
              /* inlined unwind funclet 004d4a4a */ { surface_dtor((DibSurface *)(&surf_1b9)); }
              unwind_state = 0xffffffff;
              /* inlined unwind funclet 004d4a56 */ { surface_dtor((DibSurface *)(&surf_part)); }
              result = fail_ret_6;
            }
            else {
              win_flush_pending_msgs();
              load_ok = ((DibSurface *)surf_1e1)->load_gif_resource(0x1e1,10,0xec,(iptr)this + 0x1f8);
              if (load_ok == 0) {
                fail_ret_7 = 0;
                (*((char *)&unwind_state + 0)) = 10;
                /* inlined unwind funclet 004d49d5 */ { surface_dtor((DibSurface *)(&surf_1d7)); }
                (*((char *)&unwind_state + 0)) = 9;
                /* inlined unwind funclet 004d49e1 */ { surface_dtor((DibSurface *)(&surf_1e9)); }
                (*((char *)&unwind_state + 0)) = 8;
                /* inlined unwind funclet 004d49ed */ { surface_dtor((DibSurface *)(&surf_1c8)); }
                (*((char *)&unwind_state + 0)) = 7;
                /* inlined unwind funclet 004d49f9 */ { surface_dtor((DibSurface *)(&surf_1e1)); }
                (*((char *)&unwind_state + 0)) = 6;
                /* inlined unwind funclet 004d4a05 */ { surface_dtor((DibSurface *)(&surf_1ba)); }
                (*((char *)&unwind_state + 0)) = 5;
                /* inlined unwind funclet 004d4a11 */ { surface_dtor((DibSurface *)(&surf_1eb)); }
                (*((char *)&unwind_state + 0)) = 4;
                /* inlined unwind funclet 004d4a1d */ { surface_dtor((DibSurface *)(&surf_1d6)); }
                (*((char *)&unwind_state + 0)) = 3;
                /* inlined unwind funclet 004d4a29 */ { surface_dtor((DibSurface *)(&surf_1ea)); }
                (*((char *)&unwind_state + 0)) = 2;
                /* inlined unwind funclet 004d4a35 */ { surface_dtor((DibSurface *)(&surf_1c7)); }
                (*((char *)&unwind_state + 0)) = 1;
                /* inlined unwind funclet 004d4a3e */ { surface_dtor((DibSurface *)(&surf_1e0)); }
                unwind_state = unwind_state & 0xffffff00;
                /* inlined unwind funclet 004d4a4a */ { surface_dtor((DibSurface *)(&surf_1b9)); }
                unwind_state = 0xffffffff;
                /* inlined unwind funclet 004d4a56 */ { surface_dtor((DibSurface *)(&surf_part)); }
                result = fail_ret_7;
              }
              else {
                win_flush_pending_msgs();
                load_ok = ((DibSurface *)surf_1c8)->load_gif_resource(0x1c8,10,0xec,(iptr)this + 0x1f8);
                if (load_ok == 0) {
                  fail_ret_8 = 0;
                  (*((char *)&unwind_state + 0)) = 10;
                  /* inlined unwind funclet 004d49d5 */ { surface_dtor((DibSurface *)(&surf_1d7)); }
                  (*((char *)&unwind_state + 0)) = 9;
                  /* inlined unwind funclet 004d49e1 */ { surface_dtor((DibSurface *)(&surf_1e9)); }
                  (*((char *)&unwind_state + 0)) = 8;
                  /* inlined unwind funclet 004d49ed */ { surface_dtor((DibSurface *)(&surf_1c8)); }
                  (*((char *)&unwind_state + 0)) = 7;
                  /* inlined unwind funclet 004d49f9 */ { surface_dtor((DibSurface *)(&surf_1e1)); }
                  (*((char *)&unwind_state + 0)) = 6;
                  /* inlined unwind funclet 004d4a05 */ { surface_dtor((DibSurface *)(&surf_1ba)); }
                  (*((char *)&unwind_state + 0)) = 5;
                  /* inlined unwind funclet 004d4a11 */ { surface_dtor((DibSurface *)(&surf_1eb)); }
                  (*((char *)&unwind_state + 0)) = 4;
                  /* inlined unwind funclet 004d4a1d */ { surface_dtor((DibSurface *)(&surf_1d6)); }
                  (*((char *)&unwind_state + 0)) = 3;
                  /* inlined unwind funclet 004d4a29 */ { surface_dtor((DibSurface *)(&surf_1ea)); }
                  (*((char *)&unwind_state + 0)) = 2;
                  /* inlined unwind funclet 004d4a35 */ { surface_dtor((DibSurface *)(&surf_1c7)); }
                  (*((char *)&unwind_state + 0)) = 1;
                  /* inlined unwind funclet 004d4a3e */ { surface_dtor((DibSurface *)(&surf_1e0)); }
                  unwind_state = unwind_state & 0xffffff00;
                  /* inlined unwind funclet 004d4a4a */ { surface_dtor((DibSurface *)(&surf_1b9)); }
                  unwind_state = 0xffffffff;
                  /* inlined unwind funclet 004d4a56 */ { surface_dtor((DibSurface *)(&surf_part)); }
                  result = fail_ret_8;
                }
                else {
                  win_flush_pending_msgs();
                  load_ok = ((DibSurface *)surf_1e9)->load_gif_resource(0x1e9,10,0xec,(iptr)this + 0x1f8);
                  if (load_ok == 0) {
                    fail_ret_9 = 0;
                    (*((char *)&unwind_state + 0)) = 10;
                    /* inlined unwind funclet 004d49d5 */ { surface_dtor((DibSurface *)(&surf_1d7)); }
                    (*((char *)&unwind_state + 0)) = 9;
                    /* inlined unwind funclet 004d49e1 */ { surface_dtor((DibSurface *)(&surf_1e9)); }
                    (*((char *)&unwind_state + 0)) = 8;
                    /* inlined unwind funclet 004d49ed */ { surface_dtor((DibSurface *)(&surf_1c8)); }
                    (*((char *)&unwind_state + 0)) = 7;
                    /* inlined unwind funclet 004d49f9 */ { surface_dtor((DibSurface *)(&surf_1e1)); }
                    (*((char *)&unwind_state + 0)) = 6;
                    /* inlined unwind funclet 004d4a05 */ { surface_dtor((DibSurface *)(&surf_1ba)); }
                    (*((char *)&unwind_state + 0)) = 5;
                    /* inlined unwind funclet 004d4a11 */ { surface_dtor((DibSurface *)(&surf_1eb)); }
                    (*((char *)&unwind_state + 0)) = 4;
                    /* inlined unwind funclet 004d4a1d */ { surface_dtor((DibSurface *)(&surf_1d6)); }
                    (*((char *)&unwind_state + 0)) = 3;
                    /* inlined unwind funclet 004d4a29 */ { surface_dtor((DibSurface *)(&surf_1ea)); }
                    (*((char *)&unwind_state + 0)) = 2;
                    /* inlined unwind funclet 004d4a35 */ { surface_dtor((DibSurface *)(&surf_1c7)); }
                    (*((char *)&unwind_state + 0)) = 1;
                    /* inlined unwind funclet 004d4a3e */ { surface_dtor((DibSurface *)(&surf_1e0)); }
                    unwind_state = unwind_state & 0xffffff00;
                    /* inlined unwind funclet 004d4a4a */ { surface_dtor((DibSurface *)(&surf_1b9)); }
                    unwind_state = 0xffffffff;
                    /* inlined unwind funclet 004d4a56 */ { surface_dtor((DibSurface *)(&surf_part)); }
                    result = fail_ret_9;
                  }
                  else {
                    win_flush_pending_msgs();
                    load_ok = ((DibSurface *)surf_1d7)->load_gif_resource(0x1d7,10,0xec,(iptr)this + 0x1f8);
                    if (load_ok == 0) {
                      fail_ret_10 = 0;
                      (*((char *)&unwind_state + 0)) = 10;
                      /* inlined unwind funclet 004d49d5 */ { surface_dtor((DibSurface *)(&surf_1d7)); }
                      (*((char *)&unwind_state + 0)) = 9;
                      /* inlined unwind funclet 004d49e1 */ { surface_dtor((DibSurface *)(&surf_1e9)); }
                      (*((char *)&unwind_state + 0)) = 8;
                      /* inlined unwind funclet 004d49ed */ { surface_dtor((DibSurface *)(&surf_1c8)); }
                      (*((char *)&unwind_state + 0)) = 7;
                      /* inlined unwind funclet 004d49f9 */ { surface_dtor((DibSurface *)(&surf_1e1)); }
                      (*((char *)&unwind_state + 0)) = 6;
                      /* inlined unwind funclet 004d4a05 */ { surface_dtor((DibSurface *)(&surf_1ba)); }
                      (*((char *)&unwind_state + 0)) = 5;
                      /* inlined unwind funclet 004d4a11 */ { surface_dtor((DibSurface *)(&surf_1eb)); }
                      (*((char *)&unwind_state + 0)) = 4;
                      /* inlined unwind funclet 004d4a1d */ { surface_dtor((DibSurface *)(&surf_1d6)); }
                      (*((char *)&unwind_state + 0)) = 3;
                      /* inlined unwind funclet 004d4a29 */ { surface_dtor((DibSurface *)(&surf_1ea)); }
                      (*((char *)&unwind_state + 0)) = 2;
                      /* inlined unwind funclet 004d4a35 */ { surface_dtor((DibSurface *)(&surf_1c7)); }
                      (*((char *)&unwind_state + 0)) = 1;
                      /* inlined unwind funclet 004d4a3e */ { surface_dtor((DibSurface *)(&surf_1e0)); }
                      unwind_state = unwind_state & 0xffffff00;
                      /* inlined unwind funclet 004d4a4a */ { surface_dtor((DibSurface *)(&surf_1b9)); }
                      unwind_state = 0xffffffff;
                      /* inlined unwind funclet 004d4a56 */ { surface_dtor((DibSurface *)(&surf_part)); }
                      result = fail_ret_10;
                    }
                    else {
                      win_flush_pending_msgs();
                      load_ok = ((DibSurface *)surf_1eb)->load_gif_resource(0x1eb,10,0xec,(iptr)this + 0x1f8);
                      if (load_ok == 0) {
                        fail_ret_11 = 0;
                        (*((char *)&unwind_state + 0)) = 10;
                        /* inlined unwind funclet 004d49d5 */ { surface_dtor((DibSurface *)(&surf_1d7)); }
                        (*((char *)&unwind_state + 0)) = 9;
                        /* inlined unwind funclet 004d49e1 */ { surface_dtor((DibSurface *)(&surf_1e9)); }
                        (*((char *)&unwind_state + 0)) = 8;
                        /* inlined unwind funclet 004d49ed */ { surface_dtor((DibSurface *)(&surf_1c8)); }
                        (*((char *)&unwind_state + 0)) = 7;
                        /* inlined unwind funclet 004d49f9 */ { surface_dtor((DibSurface *)(&surf_1e1)); }
                        (*((char *)&unwind_state + 0)) = 6;
                        /* inlined unwind funclet 004d4a05 */ { surface_dtor((DibSurface *)(&surf_1ba)); }
                        (*((char *)&unwind_state + 0)) = 5;
                        /* inlined unwind funclet 004d4a11 */ { surface_dtor((DibSurface *)(&surf_1eb)); }
                        (*((char *)&unwind_state + 0)) = 4;
                        /* inlined unwind funclet 004d4a1d */ { surface_dtor((DibSurface *)(&surf_1d6)); }
                        (*((char *)&unwind_state + 0)) = 3;
                        /* inlined unwind funclet 004d4a29 */ { surface_dtor((DibSurface *)(&surf_1ea)); }
                        (*((char *)&unwind_state + 0)) = 2;
                        /* inlined unwind funclet 004d4a35 */ { surface_dtor((DibSurface *)(&surf_1c7)); }
                        (*((char *)&unwind_state + 0)) = 1;
                        /* inlined unwind funclet 004d4a3e */ { surface_dtor((DibSurface *)(&surf_1e0)); }
                        unwind_state = unwind_state & 0xffffff00;
                        /* inlined unwind funclet 004d4a4a */ { surface_dtor((DibSurface *)(&surf_1b9)); }
                        unwind_state = 0xffffffff;
                        /* inlined unwind funclet 004d4a56 */ { surface_dtor((DibSurface *)(&surf_part)); }
                        result = fail_ret_11;
                      }
                      else {
                        win_flush_pending_msgs();
                        for (row_i = 0; row_i < 7; row_i = row_i + 1) {
                          win_flush_pending_msgs();
                          if ((int)(uint)part_rows[row_i].count <=
                              editor_text_edit_block.spaceship_wnd_part_count_list[(uint)part_rows[row_i].kind]) {
                            if (part_rows[row_i].kind == 1) {
                              part_count = part_rows[row_i].count;
                              load_ok = spaceship_part_count((i32)ship_civ,1);
                              if (load_ok < (int)(uint)part_count) {
                                ((Sprite *)((iptr)this + 0x93c))->grab_from_surface((iptr)surf_1ba,9,
                                             part_rows[row_i].v[5],1,
                                             part_rows[row_i].v[3],
                                             part_rows[row_i].v[4]);
                              }
                              else {
                                ((Sprite *)((iptr)this + 0x93c))->grab_from_surface((iptr)surf_1b9,9,
                                             part_rows[row_i].v[5],1,
                                             part_rows[row_i].v[3],
                                             part_rows[row_i].v[4]);
                              }
                            }
                            else if (part_rows[row_i].kind == 4) {
                              part_count = part_rows[row_i].count;
                              load_ok = spaceship_part_count((i32)ship_civ,4);
                              if (load_ok < (int)(uint)part_count) {
                                ((Sprite *)((iptr)this + 0x93c))->grab_from_surface((iptr)surf_1e1,9,
                                             part_rows[row_i].v[5],1,
                                             part_rows[row_i].v[3],
                                             part_rows[row_i].v[4]);
                              }
                              else {
                                ((Sprite *)((iptr)this + 0x93c))->grab_from_surface((iptr)surf_1e0,9,
                                             part_rows[row_i].v[5],1,
                                             part_rows[row_i].v[3],
                                             part_rows[row_i].v[4]);
                              }
                            }
                            else if (part_rows[row_i].kind == 2) {
                              part_count = part_rows[row_i].count;
                              load_ok = spaceship_part_count((i32)ship_civ,2);
                              if (load_ok < (int)(uint)part_count) {
                                ((Sprite *)((iptr)this + 0x93c))->grab_from_surface((iptr)surf_1c8,9,
                                             part_rows[row_i].v[5],1,
                                             part_rows[row_i].v[3],
                                             part_rows[row_i].v[4]);
                              }
                              else {
                                ((Sprite *)((iptr)this + 0x93c))->grab_from_surface((iptr)surf_1c7,9,
                                             part_rows[row_i].v[5],1,
                                             part_rows[row_i].v[3],
                                             part_rows[row_i].v[4]);
                              }
                            }
                            else if (part_rows[row_i].kind == 5) {
                              part_count = part_rows[row_i].count;
                              load_ok = spaceship_part_count((i32)ship_civ,5);
                              if (load_ok < (int)(uint)part_count) {
                                ((Sprite *)((iptr)this + 0x93c))->grab_from_surface((iptr)surf_1e9,9,
                                             part_rows[row_i].v[5],1,
                                             part_rows[row_i].v[3],
                                             part_rows[row_i].v[4]);
                              }
                              else {
                                ((Sprite *)((iptr)this + 0x93c))->grab_from_surface((iptr)surf_1ea,9,
                                             part_rows[row_i].v[5],1,
                                             part_rows[row_i].v[3],
                                             part_rows[row_i].v[4]);
                              }
                            }
                            else if (part_rows[row_i].kind == 3) {
                              part_count = part_rows[row_i].count;
                              load_ok = spaceship_part_count((i32)ship_civ,3);
                              if (load_ok < (int)(uint)part_count) {
                                ((Sprite *)((iptr)this + 0x93c))->grab_from_surface((iptr)surf_1d7,9,
                                             part_rows[row_i].v[5],1,
                                             part_rows[row_i].v[3],
                                             part_rows[row_i].v[4]);
                              }
                              else {
                                ((Sprite *)((iptr)this + 0x93c))->grab_from_surface((iptr)surf_1d6,9,
                                             part_rows[row_i].v[5],1,
                                             part_rows[row_i].v[3],
                                             part_rows[row_i].v[4]);
                              }
                            }
                            else {
                              ((Sprite *)((iptr)this + 0x93c))->grab_from_surface((iptr)surf_1eb,9,
                                           part_rows[row_i].v[5],1,
                                           part_rows[row_i].v[3],part_rows[row_i].v[4]
                                          );
                            }
                            ((Sprite *)((iptr)this + 0x93c))->draw((iptr)sprite_core,(iptr)this + 0x8f4,
                                         part_rows[row_i].v[1] + -0xaf,
                                         part_rows[row_i].v[2] + -99);
                          }
                        }
                        struct_row = 0;
                        for (row_i = 7; row_i < 0x1f; row_i = row_i + 1) {
                          if ((int)(uint)part_rows[row_i].count <=
                              editor_text_edit_block.spaceship_wnd_part_count_list[(uint)part_rows[row_i].kind]) {
                            struct_row = row_i;
                          }
                        }
                        win_flush_pending_msgs();
                        load_ok = ((DibSurface *)surf_part)->load_gif_resource(part_rows[struct_row].v[0],10,0xec,
                                             (iptr)this + 0x1f8);
                        if (load_ok == 0) {
                          fail_ret_12 = 0;
                          (*((char *)&unwind_state + 0)) = 10;
                          /* inlined unwind funclet 004d49d5 */ { surface_dtor((DibSurface *)(&surf_1d7)); }
                          (*((char *)&unwind_state + 0)) = 9;
                          /* inlined unwind funclet 004d49e1 */ { surface_dtor((DibSurface *)(&surf_1e9)); }
                          (*((char *)&unwind_state + 0)) = 8;
                          /* inlined unwind funclet 004d49ed */ { surface_dtor((DibSurface *)(&surf_1c8)); }
                          (*((char *)&unwind_state + 0)) = 7;
                          /* inlined unwind funclet 004d49f9 */ { surface_dtor((DibSurface *)(&surf_1e1)); }
                          (*((char *)&unwind_state + 0)) = 6;
                          /* inlined unwind funclet 004d4a05 */ { surface_dtor((DibSurface *)(&surf_1ba)); }
                          (*((char *)&unwind_state + 0)) = 5;
                          /* inlined unwind funclet 004d4a11 */ { surface_dtor((DibSurface *)(&surf_1eb)); }
                          (*((char *)&unwind_state + 0)) = 4;
                          /* inlined unwind funclet 004d4a1d */ { surface_dtor((DibSurface *)(&surf_1d6)); }
                          (*((char *)&unwind_state + 0)) = 3;
                          /* inlined unwind funclet 004d4a29 */ { surface_dtor((DibSurface *)(&surf_1ea)); }
                          (*((char *)&unwind_state + 0)) = 2;
                          /* inlined unwind funclet 004d4a35 */ { surface_dtor((DibSurface *)(&surf_1c7)); }
                          (*((char *)&unwind_state + 0)) = 1;
                          /* inlined unwind funclet 004d4a3e */ { surface_dtor((DibSurface *)(&surf_1e0)); }
                          unwind_state = unwind_state & 0xffffff00;
                          /* inlined unwind funclet 004d4a4a */ { surface_dtor((DibSurface *)(&surf_1b9)); }
                          unwind_state = 0xffffffff;
                          /* inlined unwind funclet 004d4a56 */ { surface_dtor((DibSurface *)(&surf_part)); }
                          result = fail_ret_12;
                        }
                        else {
                          win_flush_pending_msgs();
                          ((Sprite *)((iptr)this + 0x93c))->grab_from_surface((iptr)surf_part,9,
                                       part_rows[struct_row].v[1],part_rows[struct_row].v[2],
                                       part_rows[struct_row].v[3],part_rows[struct_row].v[4]);
                          ((Sprite *)((iptr)this + 0x93c))->draw((iptr)sprite_struct,(iptr)this + 0x8f4,
                                       part_rows[struct_row].v[1] + -0xaf,
                                       part_rows[struct_row].v[2] + -99);
                          for (row_i = 0x1f; row_i < 0x58; row_i = row_i + 1) {
                            win_flush_pending_msgs();
                            win_flush_pending_msgs();
                            if ((int)(uint)part_rows[row_i].count <=
                                editor_text_edit_block.spaceship_wnd_part_count_list[(uint)part_rows[row_i].kind]) {
                              if (part_rows[row_i].kind == 1) {
                                part_count = part_rows[row_i].count;
                                load_ok = spaceship_part_count((i32)ship_civ,1);
                                if (load_ok < (int)(uint)part_count) {
                                  ((Sprite *)((iptr)this + 0x93c))->grab_from_surface((iptr)surf_1ba,9,
                                               part_rows[row_i].v[5],1,
                                               part_rows[row_i].v[3],
                                               part_rows[row_i].v[4]);
                                }
                                else {
                                  ((Sprite *)((iptr)this + 0x93c))->grab_from_surface((iptr)surf_1b9,9,
                                               part_rows[row_i].v[5],1,
                                               part_rows[row_i].v[3],
                                               part_rows[row_i].v[4]);
                                }
                              }
                              else if (part_rows[row_i].kind == 4) {
                                part_count = part_rows[row_i].count;
                                load_ok = spaceship_part_count((i32)ship_civ,4);
                                if (load_ok < (int)(uint)part_count) {
                                  ((Sprite *)((iptr)this + 0x93c))->grab_from_surface((iptr)surf_1e1,9,
                                               part_rows[row_i].v[5],1,
                                               part_rows[row_i].v[3],
                                               part_rows[row_i].v[4]);
                                }
                                else {
                                  ((Sprite *)((iptr)this + 0x93c))->grab_from_surface((iptr)surf_1e0,9,
                                               part_rows[row_i].v[5],1,
                                               part_rows[row_i].v[3],
                                               part_rows[row_i].v[4]);
                                }
                              }
                              else if (part_rows[row_i].kind == 2) {
                                part_count = part_rows[row_i].count;
                                load_ok = spaceship_part_count((i32)ship_civ,2);
                                if (load_ok < (int)(uint)part_count) {
                                  ((Sprite *)((iptr)this + 0x93c))->grab_from_surface((iptr)surf_1c8,9,
                                               part_rows[row_i].v[5],1,
                                               part_rows[row_i].v[3],
                                               part_rows[row_i].v[4]);
                                }
                                else {
                                  ((Sprite *)((iptr)this + 0x93c))->grab_from_surface((iptr)surf_1c7,9,
                                               part_rows[row_i].v[5],1,
                                               part_rows[row_i].v[3],
                                               part_rows[row_i].v[4]);
                                }
                              }
                              else if (part_rows[row_i].kind == 5) {
                                part_count = part_rows[row_i].count;
                                load_ok = spaceship_part_count((i32)ship_civ,5);
                                if (load_ok < (int)(uint)part_count) {
                                  ((Sprite *)((iptr)this + 0x93c))->grab_from_surface((iptr)surf_1e9,9,
                                               part_rows[row_i].v[5],1,
                                               part_rows[row_i].v[3],
                                               part_rows[row_i].v[4]);
                                }
                                else {
                                  ((Sprite *)((iptr)this + 0x93c))->grab_from_surface((iptr)surf_1ea,9,
                                               part_rows[row_i].v[5],1,
                                               part_rows[row_i].v[3],
                                               part_rows[row_i].v[4]);
                                }
                              }
                              else if (part_rows[row_i].kind == 3) {
                                part_count = part_rows[row_i].count;
                                load_ok = spaceship_part_count((i32)ship_civ,3);
                                if (load_ok < (int)(uint)part_count) {
                                  ((Sprite *)((iptr)this + 0x93c))->grab_from_surface((iptr)surf_1d7,9,
                                               part_rows[row_i].v[5],1,
                                               part_rows[row_i].v[3],
                                               part_rows[row_i].v[4]);
                                }
                                else {
                                  ((Sprite *)((iptr)this + 0x93c))->grab_from_surface((iptr)surf_1d6,9,
                                               part_rows[row_i].v[5],1,
                                               part_rows[row_i].v[3],
                                               part_rows[row_i].v[4]);
                                }
                              }
                              else {
                                ((Sprite *)((iptr)this + 0x93c))->grab_from_surface((iptr)surf_1eb,9,
                                             part_rows[row_i].v[5],1,
                                             part_rows[row_i].v[3],
                                             part_rows[row_i].v[4]);
                              }
                              ((Sprite *)((iptr)this + 0x93c))->draw((iptr)sprite_part,(iptr)this + 0x8f4,
                                           part_rows[row_i].v[1] + -0xaf,
                                           part_rows[row_i].v[2] + -99);
                            }
                          }
                          ((Sprite *)((iptr)this + 0x93c))->grab_from_surface((iptr)this + 0x8f4,9,0,0,0x1c9,
                                       0x130);
                          win_flush_pending_msgs();
                          if ((int)launch_state == 3) {
                            ((DibSurface *)((iptr)this + 0xb8))->fill(0);
                          }
                          ((Sprite *)((iptr)this + 0x93c))->draw((iptr)sprite_final,(iptr)this + 0xb8,0xaf,
                                       99);
                          spaceship_wnd_draw_title((i32)ship_civ);
                          (*((char *)&unwind_state + 0)) = 10;
                          /* inlined unwind funclet 004d49d5 */ { surface_dtor((DibSurface *)(&surf_1d7)); }
                          (*((char *)&unwind_state + 0)) = 9;
                          /* inlined unwind funclet 004d49e1 */ { surface_dtor((DibSurface *)(&surf_1e9)); }
                          (*((char *)&unwind_state + 0)) = 8;
                          /* inlined unwind funclet 004d49ed */ { surface_dtor((DibSurface *)(&surf_1c8)); }
                          (*((char *)&unwind_state + 0)) = 7;
                          /* inlined unwind funclet 004d49f9 */ { surface_dtor((DibSurface *)(&surf_1e1)); }
                          (*((char *)&unwind_state + 0)) = 6;
                          /* inlined unwind funclet 004d4a05 */ { surface_dtor((DibSurface *)(&surf_1ba)); }
                          (*((char *)&unwind_state + 0)) = 5;
                          /* inlined unwind funclet 004d4a11 */ { surface_dtor((DibSurface *)(&surf_1eb)); }
                          (*((char *)&unwind_state + 0)) = 4;
                          /* inlined unwind funclet 004d4a1d */ { surface_dtor((DibSurface *)(&surf_1d6)); }
                          (*((char *)&unwind_state + 0)) = 3;
                          /* inlined unwind funclet 004d4a29 */ { surface_dtor((DibSurface *)(&surf_1ea)); }
                          (*((char *)&unwind_state + 0)) = 2;
                          /* inlined unwind funclet 004d4a35 */ { surface_dtor((DibSurface *)(&surf_1c7)); }
                          (*((char *)&unwind_state + 0)) = 1;
                          /* inlined unwind funclet 004d4a3e */ { surface_dtor((DibSurface *)(&surf_1e0)); }
                          unwind_state = unwind_state & 0xffffff00;
                          /* inlined unwind funclet 004d4a4a */ { surface_dtor((DibSurface *)(&surf_1b9)); }
                          unwind_state = 0xffffffff;
                          /* inlined unwind funclet 004d4a56 */ { surface_dtor((DibSurface *)(&surf_part)); }
                          result = 1;
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
  return result;
}

/* 0x005aa0e5: unwind funclet 0x005ab07f destroys the object at EBP-0x320 (dlg). */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl net_host_turn_loop(void)

{
  byte resume_start;
  SHORT esc_state;
  i32 civ_name;
  int result;
  int civ;
  int city_idx;
  int unit_idx;
  Dialog dlg;
  int humans_done;
  int clients_done;
  i32 rect_left2;
  i32 rect_top2;
  i32 rect_right2;
  i32 rect_bottom2;
  int found_owned;
  int new_casualties;
  i32 unused_pad;
  i32 unwind_state;
  
  unwind_state = 0xffffffff;
  dlg.Dialog::construct(0x4000);
  unwind_state = 0;
  result = human_civ[0];
  civ_name = (i32)(civ_name_plural(human_civ[0]));
  dbg_logf_str_int((const char *)str_server_s_d_3,(const char *)civ_name,result);
  for (civ = 1; civ < 8; civ = civ + 1) {
    if (((human_civ[0] != civ) && ((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0))
       && ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) {
      result = civ;
      civ_name = (i32)(civ_name_plural(civ));
      dbg_logf_str_int((const char *)str_client_s_d_3,(const char *)civ_name,result);
    }
  }
  net_reset_error_counts();
  map_rebuild_unit_flags();
  ((PictureWindow *)((i8 *)&advisor_window_block.advisor_window))->close();
  ((PictureWindow *)((i8 *)&casualty_window_block.casualty_window))->close();
  menu_update_states();
  ui_redraw_all_maps(1);
  ((MapView *)((i8 *)&map_views_block.map_views))->update_title();
  found_owned = 0;
  for (unit_idx = 0; unit_idx < game.num_units; unit_idx = unit_idx + 1) {
    if ((units[unit_idx].id != 0) &&
       (units[unit_idx].owner == human_civ[0])) {
      ((MapView *)((i8 *)&map_views_block.map_views))->center_on((int)units[unit_idx].x,
                         (int)units[unit_idx].y);
      found_owned = found_owned + 1;
      break;
    }
  }
  if (found_owned == 0) {
    for (unit_idx = 0; unit_idx < game.num_cities; unit_idx = unit_idx + 1) {
      if ((cities[unit_idx].id != 0) &&
         (cities[unit_idx].owner == human_civ[0])) {
        ((MapView *)((i8 *)&map_views_block.map_views))->center_on((int)cities[unit_idx].x,
                           (int)cities[unit_idx].y);
        break;
      }
    }
  }
  resume_start = (*(byte *)&turn_resume_civ);
  if ((*(byte *)&turn_resume_civ) != 0) {
    do {
      if ((1 << ((*(byte *)&turn_resume_civ) & 0x1f) & (uint)game.civs_alive) != 0) goto turn_start;
      (*(byte *)&turn_resume_civ) = (*(byte *)&turn_resume_civ) + 1;
      if ((*(byte *)&turn_resume_civ) == 8) {
        (*(byte *)&turn_resume_civ) = 0;
      }
    } while ((*(byte *)&turn_resume_civ) != resume_start);
    game_over_reason = 1;
  }
turn_start:
  do {
    game.human_players = net_session_block.pending_human_players | game.human_players;
    net_session_block.pending_human_players = 0;
    _memset(((i8 *)&net_map_lock_slots_block.net_map_lock_slots),-1,0xc0);
    units_reset_for_turn(0xfffffffd);
    net_send_state_diff(0xff,2,0,0,0);
    XD_FlushSendBuffer(60000);
    while ((net_session_block.net_msgq_priority_count != 0 || (net_session_block.net_msgq_normal_count != 0))) {
      net_session_block.process_messages(1,0);
    }
    game_calc_human_wonder_range();
    if ((*(byte *)&turn_resume_civ) == 0) {
      game_advance_turn(0xfffffffd);
      net_send_state_diff(0xff,2,0,0,0);
      XD_FlushSendBuffer(60000);
    }
    result = game_check_retirement();
    if ((result != 0) || (game_over_reason != 0)) {
      game_loop_active = '\0';
      break;
    }
    if ((scenario_events_loaded != 0) && (((*(byte *)&turn_resume_civ) == 0 || (turn_resume_new_game != 0)))) {
      ((ScenarioEvents *)((i8 *)&unit_types_block.scenario_events))->check_turn((int)game.turn);
      ((ScenarioEvents *)((i8 *)&unit_types_block.scenario_events))->check_turn_interval((int)game.turn);
      ((ScenarioEvents *)((i8 *)&unit_types_block.scenario_events))->check_random_turn((int)game.turn);
      ((ScenarioEvents *)((i8 *)&unit_types_block.scenario_events))->check_received_tech();
      net_send_state_diff(0xff,2,0,0,0);
      XD_FlushSendBuffer(5000);
    }
    game.human_players = (net_session_block.pending_human_players | game.human_players) & (byte)civ_saved_cursor_x_block.net_claimed_civs_mask;
    net_session_block.pending_human_players = 0;
    net_session_block.net_tile_sync_enabled = 0;
    for (civ = 0; (game_loop_active != '\0' && (civ < 8)); civ = civ + 1) {
      game.turn_civ = (byte)civ;
      if (((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0) &&
         ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0)) {
        civ_process_turn(civ);
        net_send_state_diff(0xff,2,0,0,0);
      }
    }
    net_session_block.net_tile_sync_enabled = 1;
    XD_FlushSendBuffer(60000);
    net_reset_msg_counts();
    for (civ = 0; civ < 8; civ = civ + 1) {
      dialog_text_font_obj_block.net_civ_phase_done[civ] = 0;
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
    dialog_text_font_obj_block.net_civ_phase_done[human_civ[0]] = dialog_text_font_obj_block.net_civ_phase_done[human_civ[0]] + 1;
    dlg_pending_idle_callback = net_host_wait_production_idle;
    popup_game_with_sprite((const char *)str_waitproduction,(iptr)&popup_info_icon_sprite,0);
    clients_done = 0;
wait_production_loop:
    if (clients_done == 0) {
      net_session_block.process_messages(1,0);
      if (net_session_block.net_player_count[0] < 2) {
        clients_done = 1;
        goto production_complete;
      }
      clients_done = 1;
      for (civ = 1; civ < 8; civ = civ + 1) {
        if ((((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0) &&
            ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) &&
           (dialog_text_font_obj_block.net_civ_phase_done[civ] == 0)) {
          clients_done = 0;
          break;
        }
      }
      goto wait_production_loop;
    }
production_complete:
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
    for (civ = 0; (game_loop_active != '\0' && (civ < 8)); civ = civ + 1) {
      if (((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0) &&
         ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) == 0)) {
        game.turn_civ = (byte)civ;
        net_session_block.mp_turn_civ = civ;
        menu_update_states();
        status_draw_civ_color(civ);
        if (((((*(byte *)&turn_resume_civ) == 0) || (turn_resume_new_game != 0)) && ((*(byte *)&turn_resume_civ) != 0)) &&
           (turn_resume_new_game != 0)) {
          ((MapView *)((i8 *)&map_views_block.map_views))->update_title();
          map_redraw_all_views(human_civ[0],1);
          wnd_flush_paint();
        }
        ai_process_civ_units();
      }
    }
    for (civ = 0; civ < 8; civ = civ + 1) {
      dialog_text_font_obj_block.net_civ_phase_done[civ] = 0;
      net_session_block.net_civ_new_player_flags[civ] = 0;
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
    if ((civ_saved_cursor_x_block.civ_intro_shown[human_civ[0]] == 0) && (civ_saved_cursor_x_block.autoplay_active == 0)) {
      civ_intro_popup(human_civ[0]);
      civ_saved_cursor_x_block.civ_intro_shown[human_civ[0]] = 1;
    }
    if (civ_saved_cursor_x_block.mp_turn_time_limit_ms != 0) {
      mp_turn_seconds_left = civ_saved_cursor_x_block.mp_turn_time_limit_ms / 1000;
      map_views_block.main_view_timer_cache_i32 = 0xffffffff;
    }
    net_session_block.mp_turn_civ = human_civ[0];
    menu_update_states();
    map_views_block.main_view_timer_cache_i32 = 0xffffffff;
    ((FrameWindow *)((i8 *)&map_views_block.map_views))->FrameWindow::draw_caption();
    rect_left2 = map_views_block.main_view_frame_left;
    rect_top2 = map_views_block.main_view_frame_top;
    rect_right2 = map_views_block.main_view_frame_right;
    rect_bottom2 = map_views_block.main_view_client_top;
    ((DibSurface *)((i8 *)&map_views_block.map_views))->wnd_blit_surface_rect((iptr)&rect_left2);
    ((MapView *)((i8 *)&map_views_block.map_views))->update_title();
    map_redraw_all_views(human_civ[0],1);
    status_draw_civ_color(human_civ[0]);
    new_casualties = net_session_block.casualty_counts[human_civ[0]] -
               net_session_block.casualty_reported_counts[human_civ[0]];
    if (civ_saved_cursor_x_block.autoplay_active == 0) {
      dlg_pending_idle_callback = turn_popup_timeout_idle;
      civ_name = civ_leader_title(human_civ[0]);
      text_set_string_arg(0,(const char *)civ_name);
      civ_name = (i32)(civ_leader_name(human_civ[0]));
      text_set_string_arg(1,(const char *)civ_name);
      if (net_session_block.casualty_reported_counts[human_civ[0]] < net_session_block.casualty_counts[human_civ[0]]) {
        net_session_block.casualty_reported_counts[human_civ[0]] =
             net_session_block.casualty_counts[human_civ[0]];
        text_set_number_arg(0,new_casualties);
        if (new_casualties == 1) {
          dlg.load_text_noflags((const char *)&str_game_7,(const char *)str_casualty_4);
        }
        else {
          dlg.load_text_noflags((const char *)&str_game_7,(const char *)str_casualties_4);
        }
        dlg.add_sprite((iptr)&popup_info_icon_sprite,0,0);
        dlg.set_image_zoom(0);
        input_flush_events();
        snd_play_effect(0x30,0,0,0);
        dlg.show_modal(0);
        if (dlg.result_extra != 0) {
          casualty_timeline_show(human_civ[0]);
        }
      }
      else {
        dlg.load_text_noflags((const char *)&str_game_7,(const char *)str_ourturntomove_3);
        dlg.add_sprite((iptr)&popup_info_icon_sprite,0,0);
        dlg.set_image_zoom(0);
        input_flush_events();
        snd_play_effect(0x30,0,0,0);
        dlg.show_modal(0);
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
      esc_state = GetAsyncKeyState(0x1b);
      if (((int)esc_state & 0x8001U) != 0) {
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
    dialog_text_font_obj_block.net_civ_phase_done[human_civ[0]] = dialog_text_font_obj_block.net_civ_phase_done[human_civ[0]] + 1;
    XD_FlushSendBuffer(60000);
    dlg_pending_idle_callback = net_host_wait_human_moves_idle;
    popup_game_with_sprite((const char *)str_waithumanmoves,(iptr)&popup_info_icon_sprite,0);
    humans_done = 0;
wait_human_moves_loop:
    if (humans_done == 0) {
      net_session_block.process_messages(1,0);
      if (net_session_block.net_player_count[0] < 2) {
        humans_done = 1;
        goto human_moves_complete;
      }
      humans_done = 1;
      for (civ = 1; civ < 8; civ = civ + 1) {
        if ((((1 << ((byte)civ & 0x1f) & (uint)game.civs_alive) != 0) &&
            ((1 << ((byte)civ & 0x1f) & (uint)game.human_players) != 0)) &&
           (dialog_text_font_obj_block.net_civ_phase_done[civ] == 0)) {
          humans_done = 0;
          break;
        }
      }
      goto wait_human_moves_loop;
    }
human_moves_complete:
    net_session_block.nm_human_move_complete_count = 0;
    net_check_lost_connections();
    if ((net_session_block.player_has_quit == '\0') || (net_session_block.mp_turn_civ == human_civ[0])) {
      for (unit_idx = 0; unit_idx < game.num_units; unit_idx = unit_idx + 1) {
        if ((units[unit_idx].id != 0) &&
           (units[unit_idx].owner == civ)) {
          unit_exhaust_moves(unit_idx);
        }
      }
      city_idx = (int)game.num_cities;
      while (city_idx = city_idx + -1, -1 < city_idx) {
        if (cities[city_idx].id != 0) {
          cities[city_idx].flags =
               cities[city_idx].flags & 0xffbfffff;
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
  unwind_state = 0xffffffff;
  /* inlined unwind funclet 005ab07f */ { dlg.Dialog::destruct(); }
  return;
}

/* 0x0055f5a3: pick a starting/setup choice for civ civ2 by scoring options
 * 1..n with civ_can_choose_government and taking the best score (ties go to the later one).
 * Ghidra lost the stack frame and passed garbage register/stack values to
 * civ_can_choose_government; the real call is civ_can_choose_government(civ, i). */
void __cdecl ai_choose_government(int civ2, int limit_choices)
{
    int count;          /* EBP-4 */
    int best_score;     /* EBP-8 */
    int diff;           /* EBP-0xc */
    int i;              /* EBP-0x10 */
    int best;           /* EBP-0x14 */

    if ((game.game_flags & 0x80) != 0 && ((short)prefs_game_rules_block.scenario_flags[0] & 0x10) != 0 &&
        civs[civ2].government >= 1)
        return;
    count = 6;
    if (limit_choices != 0) {
        count--;
        if (_rand() % 3 != 0)
            count--;
    }
    if ((game.game_flags & 1) != 0) {
        diff = (uint)civs[game.player_civ].num_advances -
               (uint)civs[civ2].num_advances;
        if (game.power_rank[civ2] < 6) {
            if (diff > 6)
                civs[civ2].government_score[6] = -2;
            if (diff > 8)
                civs[civ2].government_score[5] = -1;
        }
    }
    if (civs[civ2].government_score[0] > 0) {
        count = 3;
        if (civs[civ2].government <= 5)
            count = 1;
    }
    best_score = -999;
    best = 1;
    for (i = 1; i <= count; i++) {
        /* (its other 19 parameters are a decompiler artifact, unused) */
        if (civ_can_choose_government(civ2, i, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) == 0)
            continue;
        if (civs[civ2].government_score[i] >= best_score) {
            best_score = civs[civ2].government_score[i];
            best = i;
        }
    }
    civ_change_government(civ2, best);
}
