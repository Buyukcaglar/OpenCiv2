/*
 * Large functions whose generated translation contained EBP-relative code
 * (exception-unwind funclets run with the caller's EBP, or a lost stack slot).
 * Bodies follow the generated versions; the funclets are inlined against the
 * function's own emulated frame (`frame_`), exception bookkeeping is dropped.
 */
#include "game.h"

/* 0x0041ba52: new-game setup dialogs (difficulty, enemies, barbarity, ...).
 * Unwind funclet 0x0041d3f2 destroys the dialog object at EBP-0x320 (local_324). */
#define dlg_check_bits (*(uint *)((u8 *)&g.d_00631ed8))
#define dlg_help_pressed (*(int *)((u8 *)&g.d_00631edc))
#define prefs_game_rules (*(ushort *)((u8 *)&g.d_0064bc10))
#define prefs_difficulty (*(short *)((u8 *)&g.d_0064bc14))
#define prefs_tribe (*(short *)((u8 *)&g.d_0064bc16))
#define prefs_gender (*(short *)((u8 *)&g.d_0064bc18))
#define prefs_enemies_choice (*(short *)((u8 *)&g.d_0064bc24))
#define prefs_barbarity (*(short *)((u8 *)&g.d_0064bc28))
#define prefs_rules_choice (*(short *)((u8 *)&g.d_0064bc54))
#define prefs_accelerated_start (*(short *)((u8 *)&g.d_0064bc56))
#define screen_height (*(int *)((u8 *)&g.d_006ab19c))
#define DAT_006d1da0 (*(int *)((u8 *)&g.d_006d1da0))
#define local_458 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_454 (*(int *)(frame_ + FRAME_OFF(4)))
#define local_450 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_448 (*(int *)(frame_ + FRAME_OFF(16)))
#define local_444 (*(int *)(frame_ + FRAME_OFF(20)))
#define local_43c (*(i8 *)(frame_ + FRAME_OFF(28)))
#define local_438 (*(char *)(frame_ + FRAME_OFF(32)))
#define local_434 (*(i8 (*)[260])(frame_ + FRAME_OFF(36)))
#define local_330 (*(i32 *)(frame_ + FRAME_OFF(296)))
#define local_32c (*(int *)(frame_ + FRAME_OFF(300)))
#define local_328 (*(int *)(frame_ + FRAME_OFF(304)))
#define local_324 (*(i8 (*)[40])(frame_ + FRAME_OFF(308)))
#define local_2fc (*(int *)(frame_ + FRAME_OFF(348)))
#define local_2e8 (*(byte *)(frame_ + FRAME_OFF(368)))
#define local_248 (*(int *)(frame_ + FRAME_OFF(528)))
#define local_fc (*(int *)(frame_ + FRAME_OFF(860)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(1064)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(1068)))
#define local_28 (*(int *)(frame_ + FRAME_OFF(1072)))
#define local_24 (*(int *)(frame_ + FRAME_OFF(1076)))
#define local_20 (*(int *)(frame_ + FRAME_OFF(1080)))
#define local_1c (*(int *)(frame_ + FRAME_OFF(1084)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(1088)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(1092)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(1096)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(1100)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(1104)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

i32 __cdecl setup_new_game_dialogs(int param_1)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  i32 uVar4;
  int iVar5;
  i32 uVar6;
  i8 frame_[FRAME_OFF(1112)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0041d3fe;
  local_330 = 1;
  local_28 = 0;
  local_328 = 0;
  dialog_ctor(local_324,0x2000);
  local_8 = 0;
  leaders_fixup_names();
  game.field_0e = 0;
LAB_0041bab3:
  do {
    do {
      setup_picwnd_show(&setup_picwnd,3,6,3);
      dlg_load_game_section(local_324,s_DIFFICULTY_006254a8,1);
      dialog_set_default_choice(local_324,(int)prefs_difficulty);
      dialog_set_position(local_324,
                         ((int)(screen_width + -0x280 + (screen_width + -0x280 >> 0x1f & 7U)) >> 3)
                         + 1,-(((int)(screen_height + -0x1e0 + (screen_height + -0x1e0 >> 0x1f & 7U))
                               >> 3) + 1));
      local_18 = dlg_show_modal(local_324,0);
      snd_play_effect(0x6a,0,0,0);
      setup_picwnd_close(&setup_picwnd);
      if (local_18 < 0) {
LAB_0041d3cf:
        uVar4 = local_330;
        local_8 = 0xffffffff;
        /* inlined unwind funclet 0041d3f2 */ { dialog_dtor((void *)((iptr)&local_324)); }
        return uVar4;
      }
      game.difficulty = (byte)local_18;
      prefs_difficulty = (short)local_18;
      setup_picwnd_show(&setup_picwnd,1,6,4);
      dlg_load_game_section(local_324,s_ENEMIES_006254b4,1);
      dialog_set_default_choice(local_324,(int)prefs_enemies_choice);
      dialog_set_position(local_324,
                         -(((int)(screen_width + -0x280 + (screen_width + -0x280 >> 0x1f & 7U)) >> 3
                           ) + 1),-(((int)(screen_height + -0x1e0 +
                                          (screen_height + -0x1e0 >> 0x1f & 7U)) >> 3) + 1));
      local_32c = dlg_show_modal(local_324,0);
      snd_play_effect(0x6a,0,0,0);
      setup_picwnd_close(&setup_picwnd);
    } while (local_32c < 0);
    if (local_248 == 0) {
      prefs_enemies_choice = (short)local_32c;
      game.num_enemies = 6 - (char)local_32c;
    }
    else {
      iVar2 = _rand();
      game.num_enemies = (char)(iVar2 % 5) + 2;
    }
    setup_picwnd_show(&setup_picwnd,3,6,5);
    dlg_load_game_section(local_324,s_BARBARITY_006254bc,1);
    dialog_set_default_choice(local_324,(int)prefs_barbarity);
    dialog_set_position(local_324,
                       ((int)(screen_width + -0x280 + (screen_width + -0x280 >> 0x1f & 7U)) >> 3) +
                       1,-(((int)(screen_height + -0x1e0 + (screen_height + -0x1e0 >> 0x1f & 7U)) >> 3
                           ) + 1));
    iVar2 = dlg_show_modal(local_324,0);
    snd_play_effect(0x6a,0,0,0);
    setup_picwnd_close(&setup_picwnd);
  } while (iVar2 < 0);
  if (local_248 == 0) {
    local_438 = (char)iVar2;
    game.barbarian_activity = local_438;
    prefs_barbarity = (short)iVar2;
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
    setup_picwnd_show(&setup_picwnd,1,6,9);
    dlg_load_game_section(local_324,s_RULES_006254c8,1);
    dialog_set_default_choice(local_324,(int)prefs_rules_choice);
    dialog_set_position(local_324,
                       -(((int)(screen_width + -0x280 + (screen_width + -0x280 >> 0x1f & 7U)) >> 3)
                        + 1),-(((int)(screen_height + -0x1e0 + (screen_height + -0x1e0 >> 0x1f & 7U))
                               >> 3) + 1));
    iVar2 = dlg_show_modal(local_324,0);
    snd_play_effect(0x6a,0,0,0);
    setup_picwnd_close(&setup_picwnd);
    if (iVar2 < 0) goto LAB_0041d3cf;
    prefs_rules_choice = (short)iVar2;
    if (iVar2 == 0) goto LAB_0041c35d;
    game.rules = prefs_game_rules;
    if (param_1 == 1) {
      game.rules = prefs_game_rules & 0x7fff;
    }
    else if (param_1 == 2) {
      game.rules = prefs_game_rules | 0x8000;
    }
    dlg_checks_clear();
    dlg_check_set(0,(uint)((game.rules & 0x10) == 0));
    dlg_check_set(1,game.rules & 0x8000);
    dlg_check_set(2,0);
    dlg_check_set(3,(int)prefs_accelerated_start);
    dlg_check_set(4,game.rules & 0x80);
    dlg_check_set(5,game.rules & 0x100);
    setup_picwnd_show(&setup_picwnd,3,6,9);
    dialog_load_text_section(local_324,&DAT_006359d4,s_ADVANCED_006254d0,0,0,0,0,0,0);
    if ((local_2e8 & 4) != 0) {
      for (local_30 = 0; local_30 < local_2fc; local_30 = local_30 + 1) {
        dialog_set_option_checked(local_324,local_30,1 << ((byte)local_30 & 0x1f) & dlg_check_bits);
      }
    }
    dialog_set_position(local_324,
                       ((int)(screen_width + -0x280 + (screen_width + -0x280 >> 0x1f & 7U)) >> 3) +
                       1,-(((int)(screen_height + -0x1e0 + (screen_height + -0x1e0 >> 0x1f & 7U)) >> 3
                           ) + 1));
    dlg_show_modal(local_324,0);
    snd_play_effect(0x6a,0,0,0);
    setup_picwnd_close(&setup_picwnd);
    dlg_help_pressed = local_248;
    if ((local_2e8 & 4) != 0) {
      dlg_check_bits = 0;
      for (local_30 = 0; local_30 < local_2fc; local_30 = local_30 + 1) {
        iVar2 = dialog_option_is_checked(local_324,local_30);
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
      prefs_game_rules = game.rules;
    }
    else {
      prefs_game_rules = game.rules & 0x7fff | prefs_game_rules & 0x8000;
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
    setup_picwnd_show(&setup_picwnd,1,6,9);
    dlg_load_game_section(local_324,s_ACCELERATED_006254dc,1);
    dialog_set_default_choice(local_324,(int)prefs_accelerated_start);
    dialog_set_position(local_324,
                       -(((int)(screen_width + -0x280 + (screen_width + -0x280 >> 0x1f & 7U)) >> 3)
                        + 1),-(((int)(screen_height + -0x1e0 + (screen_height + -0x1e0 >> 0x1f & 7U))
                               >> 3) + 1));
    local_328 = dlg_show_modal(local_324,0);
    snd_play_effect(0x6a,0,0,0);
    setup_picwnd_close(&setup_picwnd);
  } while (local_328 < 0);
  prefs_accelerated_start = (short)local_328;
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
    setup_picwnd_show(&setup_picwnd,2,6,6);
    dlg_load_game_section(local_324,s_GENDER_006254e8,1);
    dialog_set_default_choice(local_324,(int)prefs_gender);
    dialog_set_position(local_324,0xfffffc19,
                       -(((int)(screen_height + -0x1e0 + (screen_height + -0x1e0 >> 0x1f & 7U)) >> 3)
                        + 1));
    iVar2 = dlg_show_modal(local_324,0);
    snd_play_effect(0x6a,0,0,0);
    setup_picwnd_close(&setup_picwnd);
    if (iVar2 < 0) goto LAB_0041bab3;
    prefs_gender = (short)iVar2;
    setup_picwnd_show(&setup_picwnd,2,6,7);
    local_14 = dialog_load_text(local_324,&DAT_006254f8,s_TRIBE_006254f0,1);
    if (local_14 != 0) {
      setup_picwnd_close(&setup_picwnd);
      goto LAB_0041d3cf;
    }
    dialog_set_columns(local_324,3);
    for (local_448 = 0; local_448 < 0x15; local_448 = local_448 + 1) {
      uVar6 = 0;
      iVar5 = local_448;
      uVar4 = label_string((int)leaders[local_448].plural);
      dialog_add_option(local_324,uVar4,iVar5,uVar6);
    }
    dialog_set_default_choice(local_324,(int)prefs_tribe);
    dialog_set_position(local_324,0xfffffc19,
                       -(((int)(screen_height + -0x1e0 + (screen_height + -0x1e0 >> 0x1f & 7U)) >> 3)
                        + 1));
    local_1c = dlg_show_modal(local_324,0);
    snd_play_effect(0x6a,0,0,0);
    setup_picwnd_close(&setup_picwnd);
    if (-1 < local_1c) {
      game.player_civ = leaders[local_1c].color;
      prefs_tribe = (short)local_1c;
      civs[(char)game.player_civ].tribe = prefs_tribe;
      civs[(char)game.player_civ].leader_portrait = (i8)local_1c;
      if (iVar2 != 0) {
        civs[(char)game.player_civ].leader_portrait =
             civs[(char)game.player_civ].leader_portrait + '\x15';
      }
      DAT_006d1da0 = (int)(char)game.player_civ;
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
      if (local_248 == 0) {
        setup_picwnd_show(&setup_picwnd,2,6,7);
        dialog_load_text_section(local_324,&DAT_006359d4,&DAT_0062551c,0x17,
                           &civ_names[(char)game.player_civ].leader_name[0],0,0,0,1);
        dialog_set_position(local_324,0xfffffc19,
                           -(((int)(screen_height + -0x1e0 + (screen_height + -0x1e0 >> 0x1f & 7U)) >>
                             3) + 1));
        local_14 = dialog_run_modal(local_324,local_434,0);
        snd_play_effect(0x6a,0,0,0);
        setup_picwnd_close(&setup_picwnd);
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
            setup_picwnd_show(&setup_picwnd,2,6,7);
            local_14 = dialog_load_text_section(local_324,&DAT_006359d4,s_CUSTOMTRIBE_00625500,0x17,
                                          &civ_names[(char)game.player_civ].leader_name[0],0,0,0,1);
            if (local_14 != 0) {
              setup_picwnd_close(&setup_picwnd);
              goto LAB_0041d3cf;
            }
            dialog_set_position(local_324,0xfffffc19,
                               -(((int)(screen_height + -0x1e0 + (screen_height + -0x1e0 >> 0x1f & 7U)
                                       ) >> 3) + 1));
            iVar2 = dlg_show_modal(local_324,0);
            snd_play_effect(0x6a,0,0,0);
            setup_picwnd_close(&setup_picwnd);
            if (iVar2 < 0) goto LAB_0041c35d;
            crt_strcpy(&civ_names[(char)game.player_civ].leader_name[0],&text_string_args);
            crt_strcpy(&civ_names[(char)game.player_civ].tribe_name[0],&text_string_arg1);
            crt_strcpy(&civ_names[(char)game.player_civ].adjective[0],&text_string_arg2);
            if (local_248 != 1) break;
            setup_picwnd_show(&setup_picwnd,2,6,7);
            local_14 = dlg_load_game_section(local_324,s_CUSTOMTRIBE2_0062550c,1);
            if (local_14 != 0) {
              setup_picwnd_close(&setup_picwnd);
              goto LAB_0041d3cf;
            }
            local_14 = 0;
            for (local_20 = 0; local_20 < 7; local_20 = local_20 + 1) {
              text_clear();
              text_append_string_id(government_names[local_20]);
              text_append_colon();
              dialog_add_edit_field(local_324,&text_buffer,
                                 &civ_names[(char)game.player_civ].titles[local_20][0],0x17);
            }
            dialog_set_position(local_324,0xfffffc19,
                               -(((int)(screen_height + -0x1e0 + (screen_height + -0x1e0 >> 0x1f & 7U)
                                       ) >> 3) + 1));
            iVar2 = dlg_show_modal(local_324,0);
            if (iVar2 == 0) {
              for (local_20 = 0; local_20 < 7; local_20 = local_20 + 1) {
                crt_strcpy(&civ_names[(char)game.player_civ].titles[local_20][0],
                             &text_string_args + local_20 * 0x104);
              }
            }
            snd_play_effect(0x6a,0,0,0);
            setup_picwnd_close(&setup_picwnd);
          }
          if (local_248 != 2) break;
          portrait_dlg_show((int)(char)game.player_civ);
        }
      }
LAB_0041cfad:
      setup_picwnd_show(&setup_picwnd,1,6,8);
      dlg_load_game_section(local_324,s_CUSTOMCITY_00625524,0x20001);
      for (local_444 = 0; local_444 < 4; local_444 = local_444 + 1) {
        uVar4 = label_string(*(i32 *)(DAT_00628420 + 0x3d8 + local_444 * 4));
        dialog_add_sprite(local_324,local_444 * 0x1e0 + ADDR(0x63fff4, ((u8 *)&g.d_0063fe8c + 360)),local_444,uVar4);
      }
      dialog_set_default_choice(local_324,
                         (int)leaders[civs[(char)game.player_civ].tribe].city_style);
      dialog_set_position(local_324,
                         -(((int)(screen_width + -0x280 + (screen_width + -0x280 >> 0x1f & 7U)) >> 3
                           ) + 1),-(((int)(screen_height + -0x1e0 +
                                          (screen_height + -0x1e0 >> 0x1f & 7U)) >> 3) + 1));
      iVar2 = dlg_show_modal(local_324,0);
      snd_play_effect(0x6a,0,0,0);
      setup_picwnd_close(&setup_picwnd);
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
              setup_picwnd_show(&setup_picwnd,2,6,9);
              dlg_load_game_section(local_324,s_OPPONENT_00625530,1);
              *(i32 *)(local_fc + 4) = 0x15;
              for (local_2c = 0; local_2c < 0x15; local_2c = local_2c + 1) {
                if (leaders[local_2c].color == local_448) {
                  text_clear();
                  text_append_string_id((int)leaders[local_2c].plural);
                  text_append_space();
                  text_append_lparen();
                  text_append_string_id((int)leaders[local_2c].leader_name);
                  text_append_rparen();
                  dialog_add_option(local_324,&text_buffer,local_2c,0);
                }
              }
              dialog_set_position(local_324,0xfffffc19,
                                 -(((int)(screen_height + -0x1e0 +
                                         (screen_height + -0x1e0 >> 0x1f & 7U)) >> 3) + 1));
              local_2c = dlg_show_modal(local_324,0);
              snd_play_effect(0x6a,0,0,0);
              setup_picwnd_close(&setup_picwnd);
              if (local_2c < 0) goto LAB_0041cfad;
              if (local_2c < 0x15) {
                (&setup_chosen_leaders)[local_448] = (i8)local_2c;
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
#undef dlg_check_bits
#undef dlg_help_pressed
#undef prefs_game_rules
#undef prefs_difficulty
#undef prefs_tribe
#undef prefs_gender
#undef prefs_enemies_choice
#undef prefs_barbarity
#undef prefs_rules_choice
#undef prefs_accelerated_start
#undef screen_height
#undef DAT_006d1da0
#undef local_458
#undef local_454
#undef local_450
#undef local_448
#undef local_444
#undef local_43c
#undef local_438
#undef local_434
#undef local_330
#undef local_32c
#undef local_328
#undef local_324
#undef local_2fc
#undef local_2e8
#undef local_248
#undef local_fc
#undef local_30
#undef local_2c
#undef local_28
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0x004d17bf: unwind funclet 0x004d4a11 destroys the control at EBP-0x12c (local_130). */
#define local_d88 (*(i8 (*)[16])(frame_ + FRAME_OFF(0)))
#define local_d78 (*(i8 (*)[16])(frame_ + FRAME_OFF(16)))
#define local_d68 (*(i8 (*)[16])(frame_ + FRAME_OFF(32)))
#define local_d58 (*(i32 *)(frame_ + FRAME_OFF(48)))
#define local_d54 (*(i8 (*)[16])(frame_ + FRAME_OFF(52)))
#define local_d44 (*(i32 *)(frame_ + FRAME_OFF(68)))
#define local_d40 (*(i32 *)(frame_ + FRAME_OFF(72)))
#define local_d3c (*(i32 *)(frame_ + FRAME_OFF(76)))
#define local_d38 (*(i32 *)(frame_ + FRAME_OFF(80)))
#define local_d34 (*(i32 *)(frame_ + FRAME_OFF(84)))
#define local_d30 (*(i32 *)(frame_ + FRAME_OFF(88)))
#define local_d2c (*(i32 *)(frame_ + FRAME_OFF(92)))
#define local_d28 (*(i32 *)(frame_ + FRAME_OFF(96)))
#define local_d24 (*(i32 *)(frame_ + FRAME_OFF(100)))
#define local_d20 (*(i32 *)(frame_ + FRAME_OFF(104)))
#define local_d1c (*(i32 *)(frame_ + FRAME_OFF(108)))
#define local_d18 (*(i8 (*)[72])(frame_ + FRAME_OFF(112)))
#define local_cd0 (*(i8 (*)[72])(frame_ + FRAME_OFF(184)))
#define local_c88 (*(byte (*)[4])(frame_ + FRAME_OFF(256)))
#define local_c84 (*(int (*)[6])(frame_ + FRAME_OFF(260)))
#define local_c6c (*(i8 *)(frame_ + FRAME_OFF(284)))
#define local_c6b (*(i8 *)(frame_ + FRAME_OFF(285)))
#define local_c68 (*(i32 *)(frame_ + FRAME_OFF(288)))
#define local_c64 (*(i32 *)(frame_ + FRAME_OFF(292)))
#define local_c60 (*(i32 *)(frame_ + FRAME_OFF(296)))
#define local_c5c (*(i32 *)(frame_ + FRAME_OFF(300)))
#define local_c58 (*(i32 *)(frame_ + FRAME_OFF(304)))
#define local_c54 (*(i32 *)(frame_ + FRAME_OFF(308)))
#define local_c50 (*(i8 *)(frame_ + FRAME_OFF(312)))
#define local_c4f (*(i8 *)(frame_ + FRAME_OFF(313)))
#define local_c4c (*(i32 *)(frame_ + FRAME_OFF(316)))
#define local_c48 (*(i32 *)(frame_ + FRAME_OFF(320)))
#define local_c44 (*(i32 *)(frame_ + FRAME_OFF(324)))
#define local_c40 (*(i32 *)(frame_ + FRAME_OFF(328)))
#define local_c3c (*(i32 *)(frame_ + FRAME_OFF(332)))
#define local_c38 (*(i32 *)(frame_ + FRAME_OFF(336)))
#define local_c34 (*(i8 *)(frame_ + FRAME_OFF(340)))
#define local_c33 (*(i8 *)(frame_ + FRAME_OFF(341)))
#define local_c30 (*(i32 *)(frame_ + FRAME_OFF(344)))
#define local_c2c (*(i32 *)(frame_ + FRAME_OFF(348)))
#define local_c28 (*(i32 *)(frame_ + FRAME_OFF(352)))
#define local_c24 (*(i32 *)(frame_ + FRAME_OFF(356)))
#define local_c20 (*(i32 *)(frame_ + FRAME_OFF(360)))
#define local_c1c (*(i32 *)(frame_ + FRAME_OFF(364)))
#define local_c18 (*(i8 *)(frame_ + FRAME_OFF(368)))
#define local_c17 (*(i8 *)(frame_ + FRAME_OFF(369)))
#define local_c14 (*(i32 *)(frame_ + FRAME_OFF(372)))
#define local_c10 (*(i32 *)(frame_ + FRAME_OFF(376)))
#define local_c0c (*(i32 *)(frame_ + FRAME_OFF(380)))
#define local_c08 (*(i32 *)(frame_ + FRAME_OFF(384)))
#define local_c04 (*(i32 *)(frame_ + FRAME_OFF(388)))
#define local_c00 (*(i32 *)(frame_ + FRAME_OFF(392)))
#define local_bfc (*(i8 *)(frame_ + FRAME_OFF(396)))
#define local_bfb (*(i8 *)(frame_ + FRAME_OFF(397)))
#define local_bf8 (*(i32 *)(frame_ + FRAME_OFF(400)))
#define local_bf4 (*(i32 *)(frame_ + FRAME_OFF(404)))
#define local_bf0 (*(i32 *)(frame_ + FRAME_OFF(408)))
#define local_bec (*(i32 *)(frame_ + FRAME_OFF(412)))
#define local_be8 (*(i32 *)(frame_ + FRAME_OFF(416)))
#define local_be4 (*(i32 *)(frame_ + FRAME_OFF(420)))
#define local_be0 (*(i8 *)(frame_ + FRAME_OFF(424)))
#define local_bdf (*(i8 *)(frame_ + FRAME_OFF(425)))
#define local_bdc (*(i32 *)(frame_ + FRAME_OFF(428)))
#define local_bd8 (*(i32 *)(frame_ + FRAME_OFF(432)))
#define local_bd4 (*(i32 *)(frame_ + FRAME_OFF(436)))
#define local_bd0 (*(i32 *)(frame_ + FRAME_OFF(440)))
#define local_bcc (*(i32 *)(frame_ + FRAME_OFF(444)))
#define local_bc8 (*(i32 *)(frame_ + FRAME_OFF(448)))
#define local_bc4 (*(byte (*)[676])(frame_ + FRAME_OFF(452)))
#define local_920 (*(i32 *)(frame_ + FRAME_OFF(1128)))
#define local_91c (*(i32 *)(frame_ + FRAME_OFF(1132)))
#define local_918 (*(i32 *)(frame_ + FRAME_OFF(1136)))
#define local_914 (*(i32 *)(frame_ + FRAME_OFF(1140)))
#define local_910 (*(i32 *)(frame_ + FRAME_OFF(1144)))
#define local_90c (*(i32 *)(frame_ + FRAME_OFF(1148)))
#define local_908 (*(i8 *)(frame_ + FRAME_OFF(1152)))
#define local_907 (*(i8 *)(frame_ + FRAME_OFF(1153)))
#define local_904 (*(i32 *)(frame_ + FRAME_OFF(1156)))
#define local_900 (*(i32 *)(frame_ + FRAME_OFF(1160)))
#define local_8fc (*(i32 *)(frame_ + FRAME_OFF(1164)))
#define local_8f8 (*(i32 *)(frame_ + FRAME_OFF(1168)))
#define local_8f4 (*(i32 *)(frame_ + FRAME_OFF(1172)))
#define local_8f0 (*(i32 *)(frame_ + FRAME_OFF(1176)))
#define local_8ec (*(i8 *)(frame_ + FRAME_OFF(1180)))
#define local_8eb (*(i8 *)(frame_ + FRAME_OFF(1181)))
#define local_8e8 (*(i32 *)(frame_ + FRAME_OFF(1184)))
#define local_8e4 (*(i32 *)(frame_ + FRAME_OFF(1188)))
#define local_8e0 (*(i32 *)(frame_ + FRAME_OFF(1192)))
#define local_8dc (*(i32 *)(frame_ + FRAME_OFF(1196)))
#define local_8d8 (*(i32 *)(frame_ + FRAME_OFF(1200)))
#define local_8d4 (*(i32 *)(frame_ + FRAME_OFF(1204)))
#define local_8d0 (*(i8 *)(frame_ + FRAME_OFF(1208)))
#define local_8cf (*(i8 *)(frame_ + FRAME_OFF(1209)))
#define local_8cc (*(i32 *)(frame_ + FRAME_OFF(1212)))
#define local_8c8 (*(i32 *)(frame_ + FRAME_OFF(1216)))
#define local_8c4 (*(i32 *)(frame_ + FRAME_OFF(1220)))
#define local_8c0 (*(i32 *)(frame_ + FRAME_OFF(1224)))
#define local_8bc (*(i32 *)(frame_ + FRAME_OFF(1228)))
#define local_8b8 (*(i32 *)(frame_ + FRAME_OFF(1232)))
#define local_8b4 (*(i8 *)(frame_ + FRAME_OFF(1236)))
#define local_8b3 (*(i8 *)(frame_ + FRAME_OFF(1237)))
#define local_8b0 (*(i32 *)(frame_ + FRAME_OFF(1240)))
#define local_8ac (*(i32 *)(frame_ + FRAME_OFF(1244)))
#define local_8a8 (*(i32 *)(frame_ + FRAME_OFF(1248)))
#define local_8a4 (*(i32 *)(frame_ + FRAME_OFF(1252)))
#define local_8a0 (*(i32 *)(frame_ + FRAME_OFF(1256)))
#define local_89c (*(i32 *)(frame_ + FRAME_OFF(1260)))
#define local_898 (*(i8 *)(frame_ + FRAME_OFF(1264)))
#define local_897 (*(i8 *)(frame_ + FRAME_OFF(1265)))
#define local_894 (*(i32 *)(frame_ + FRAME_OFF(1268)))
#define local_890 (*(i32 *)(frame_ + FRAME_OFF(1272)))
#define local_88c (*(i32 *)(frame_ + FRAME_OFF(1276)))
#define local_888 (*(i32 *)(frame_ + FRAME_OFF(1280)))
#define local_884 (*(i32 *)(frame_ + FRAME_OFF(1284)))
#define local_880 (*(i32 *)(frame_ + FRAME_OFF(1288)))
#define local_87c (*(i8 *)(frame_ + FRAME_OFF(1292)))
#define local_87b (*(i8 *)(frame_ + FRAME_OFF(1293)))
#define local_878 (*(i32 *)(frame_ + FRAME_OFF(1296)))
#define local_874 (*(i32 *)(frame_ + FRAME_OFF(1300)))
#define local_870 (*(i32 *)(frame_ + FRAME_OFF(1304)))
#define local_86c (*(i32 *)(frame_ + FRAME_OFF(1308)))
#define local_868 (*(i32 *)(frame_ + FRAME_OFF(1312)))
#define local_864 (*(i32 *)(frame_ + FRAME_OFF(1316)))
#define local_860 (*(i8 *)(frame_ + FRAME_OFF(1320)))
#define local_85f (*(i8 *)(frame_ + FRAME_OFF(1321)))
#define local_85c (*(i32 *)(frame_ + FRAME_OFF(1324)))
#define local_858 (*(i32 *)(frame_ + FRAME_OFF(1328)))
#define local_854 (*(i32 *)(frame_ + FRAME_OFF(1332)))
#define local_850 (*(i32 *)(frame_ + FRAME_OFF(1336)))
#define local_84c (*(i32 *)(frame_ + FRAME_OFF(1340)))
#define local_848 (*(i32 *)(frame_ + FRAME_OFF(1344)))
#define local_844 (*(i8 *)(frame_ + FRAME_OFF(1348)))
#define local_843 (*(i8 *)(frame_ + FRAME_OFF(1349)))
#define local_840 (*(i32 *)(frame_ + FRAME_OFF(1352)))
#define local_83c (*(i32 *)(frame_ + FRAME_OFF(1356)))
#define local_838 (*(i32 *)(frame_ + FRAME_OFF(1360)))
#define local_834 (*(i32 *)(frame_ + FRAME_OFF(1364)))
#define local_830 (*(i32 *)(frame_ + FRAME_OFF(1368)))
#define local_82c (*(i32 *)(frame_ + FRAME_OFF(1372)))
#define local_828 (*(i8 *)(frame_ + FRAME_OFF(1376)))
#define local_827 (*(i8 *)(frame_ + FRAME_OFF(1377)))
#define local_824 (*(i32 *)(frame_ + FRAME_OFF(1380)))
#define local_820 (*(i32 *)(frame_ + FRAME_OFF(1384)))
#define local_81c (*(i32 *)(frame_ + FRAME_OFF(1388)))
#define local_818 (*(i32 *)(frame_ + FRAME_OFF(1392)))
#define local_814 (*(i32 *)(frame_ + FRAME_OFF(1396)))
#define local_810 (*(i32 *)(frame_ + FRAME_OFF(1400)))
#define local_80c (*(i8 *)(frame_ + FRAME_OFF(1404)))
#define local_80b (*(i8 *)(frame_ + FRAME_OFF(1405)))
#define local_808 (*(i32 *)(frame_ + FRAME_OFF(1408)))
#define local_804 (*(i32 *)(frame_ + FRAME_OFF(1412)))
#define local_800 (*(i32 *)(frame_ + FRAME_OFF(1416)))
#define local_7fc (*(i32 *)(frame_ + FRAME_OFF(1420)))
#define local_7f8 (*(i32 *)(frame_ + FRAME_OFF(1424)))
#define local_7f4 (*(i32 *)(frame_ + FRAME_OFF(1428)))
#define local_7f0 (*(i8 *)(frame_ + FRAME_OFF(1432)))
#define local_7ef (*(i8 *)(frame_ + FRAME_OFF(1433)))
#define local_7ec (*(i32 *)(frame_ + FRAME_OFF(1436)))
#define local_7e8 (*(i32 *)(frame_ + FRAME_OFF(1440)))
#define local_7e4 (*(i32 *)(frame_ + FRAME_OFF(1444)))
#define local_7e0 (*(i32 *)(frame_ + FRAME_OFF(1448)))
#define local_7dc (*(i32 *)(frame_ + FRAME_OFF(1452)))
#define local_7d8 (*(i32 *)(frame_ + FRAME_OFF(1456)))
#define local_7d4 (*(i8 *)(frame_ + FRAME_OFF(1460)))
#define local_7d3 (*(i8 *)(frame_ + FRAME_OFF(1461)))
#define local_7d0 (*(i32 *)(frame_ + FRAME_OFF(1464)))
#define local_7cc (*(i32 *)(frame_ + FRAME_OFF(1468)))
#define local_7c8 (*(i32 *)(frame_ + FRAME_OFF(1472)))
#define local_7c4 (*(i32 *)(frame_ + FRAME_OFF(1476)))
#define local_7c0 (*(i32 *)(frame_ + FRAME_OFF(1480)))
#define local_7bc (*(i32 *)(frame_ + FRAME_OFF(1484)))
#define local_7b8 (*(i8 *)(frame_ + FRAME_OFF(1488)))
#define local_7b7 (*(i8 *)(frame_ + FRAME_OFF(1489)))
#define local_7b4 (*(i32 *)(frame_ + FRAME_OFF(1492)))
#define local_7b0 (*(i32 *)(frame_ + FRAME_OFF(1496)))
#define local_7ac (*(i32 *)(frame_ + FRAME_OFF(1500)))
#define local_7a8 (*(i32 *)(frame_ + FRAME_OFF(1504)))
#define local_7a4 (*(i32 *)(frame_ + FRAME_OFF(1508)))
#define local_7a0 (*(i32 *)(frame_ + FRAME_OFF(1512)))
#define local_79c (*(i8 *)(frame_ + FRAME_OFF(1516)))
#define local_79b (*(i8 *)(frame_ + FRAME_OFF(1517)))
#define local_798 (*(i32 *)(frame_ + FRAME_OFF(1520)))
#define local_794 (*(i32 *)(frame_ + FRAME_OFF(1524)))
#define local_790 (*(i32 *)(frame_ + FRAME_OFF(1528)))
#define local_78c (*(i32 *)(frame_ + FRAME_OFF(1532)))
#define local_788 (*(i32 *)(frame_ + FRAME_OFF(1536)))
#define local_784 (*(i32 *)(frame_ + FRAME_OFF(1540)))
#define local_780 (*(i8 *)(frame_ + FRAME_OFF(1544)))
#define local_77f (*(i8 *)(frame_ + FRAME_OFF(1545)))
#define local_77c (*(i32 *)(frame_ + FRAME_OFF(1548)))
#define local_778 (*(i32 *)(frame_ + FRAME_OFF(1552)))
#define local_774 (*(i32 *)(frame_ + FRAME_OFF(1556)))
#define local_770 (*(i32 *)(frame_ + FRAME_OFF(1560)))
#define local_76c (*(i32 *)(frame_ + FRAME_OFF(1564)))
#define local_768 (*(i32 *)(frame_ + FRAME_OFF(1568)))
#define local_764 (*(i8 *)(frame_ + FRAME_OFF(1572)))
#define local_763 (*(i8 *)(frame_ + FRAME_OFF(1573)))
#define local_760 (*(i32 *)(frame_ + FRAME_OFF(1576)))
#define local_75c (*(i32 *)(frame_ + FRAME_OFF(1580)))
#define local_758 (*(i32 *)(frame_ + FRAME_OFF(1584)))
#define local_754 (*(i32 *)(frame_ + FRAME_OFF(1588)))
#define local_750 (*(i32 *)(frame_ + FRAME_OFF(1592)))
#define local_74c (*(i32 *)(frame_ + FRAME_OFF(1596)))
#define local_748 (*(i8 *)(frame_ + FRAME_OFF(1600)))
#define local_747 (*(i8 *)(frame_ + FRAME_OFF(1601)))
#define local_744 (*(i32 *)(frame_ + FRAME_OFF(1604)))
#define local_740 (*(i32 *)(frame_ + FRAME_OFF(1608)))
#define local_73c (*(i32 *)(frame_ + FRAME_OFF(1612)))
#define local_738 (*(i32 *)(frame_ + FRAME_OFF(1616)))
#define local_734 (*(i32 *)(frame_ + FRAME_OFF(1620)))
#define local_730 (*(i32 *)(frame_ + FRAME_OFF(1624)))
#define local_72c (*(i8 *)(frame_ + FRAME_OFF(1628)))
#define local_72b (*(i8 *)(frame_ + FRAME_OFF(1629)))
#define local_728 (*(i32 *)(frame_ + FRAME_OFF(1632)))
#define local_724 (*(i32 *)(frame_ + FRAME_OFF(1636)))
#define local_720 (*(i32 *)(frame_ + FRAME_OFF(1640)))
#define local_71c (*(i32 *)(frame_ + FRAME_OFF(1644)))
#define local_718 (*(i32 *)(frame_ + FRAME_OFF(1648)))
#define local_714 (*(i32 *)(frame_ + FRAME_OFF(1652)))
#define local_710 (*(i8 *)(frame_ + FRAME_OFF(1656)))
#define local_70f (*(i8 *)(frame_ + FRAME_OFF(1657)))
#define local_70c (*(i32 *)(frame_ + FRAME_OFF(1660)))
#define local_708 (*(i32 *)(frame_ + FRAME_OFF(1664)))
#define local_704 (*(i32 *)(frame_ + FRAME_OFF(1668)))
#define local_700 (*(i32 *)(frame_ + FRAME_OFF(1672)))
#define local_6fc (*(i32 *)(frame_ + FRAME_OFF(1676)))
#define local_6f8 (*(i32 *)(frame_ + FRAME_OFF(1680)))
#define local_6f4 (*(i8 *)(frame_ + FRAME_OFF(1684)))
#define local_6f3 (*(i8 *)(frame_ + FRAME_OFF(1685)))
#define local_6f0 (*(i32 *)(frame_ + FRAME_OFF(1688)))
#define local_6ec (*(i32 *)(frame_ + FRAME_OFF(1692)))
#define local_6e8 (*(i32 *)(frame_ + FRAME_OFF(1696)))
#define local_6e4 (*(i32 *)(frame_ + FRAME_OFF(1700)))
#define local_6e0 (*(i32 *)(frame_ + FRAME_OFF(1704)))
#define local_6dc (*(i32 *)(frame_ + FRAME_OFF(1708)))
#define local_6d8 (*(i8 *)(frame_ + FRAME_OFF(1712)))
#define local_6d7 (*(i8 *)(frame_ + FRAME_OFF(1713)))
#define local_6d4 (*(i32 *)(frame_ + FRAME_OFF(1716)))
#define local_6d0 (*(i32 *)(frame_ + FRAME_OFF(1720)))
#define local_6cc (*(i32 *)(frame_ + FRAME_OFF(1724)))
#define local_6c8 (*(i32 *)(frame_ + FRAME_OFF(1728)))
#define local_6c4 (*(i32 *)(frame_ + FRAME_OFF(1732)))
#define local_6c0 (*(i32 *)(frame_ + FRAME_OFF(1736)))
#define local_6bc (*(i8 *)(frame_ + FRAME_OFF(1740)))
#define local_6bb (*(i8 *)(frame_ + FRAME_OFF(1741)))
#define local_6b8 (*(i32 *)(frame_ + FRAME_OFF(1744)))
#define local_6b4 (*(i32 *)(frame_ + FRAME_OFF(1748)))
#define local_6b0 (*(i32 *)(frame_ + FRAME_OFF(1752)))
#define local_6ac (*(i32 *)(frame_ + FRAME_OFF(1756)))
#define local_6a8 (*(i32 *)(frame_ + FRAME_OFF(1760)))
#define local_6a4 (*(i32 *)(frame_ + FRAME_OFF(1764)))
#define local_6a0 (*(i8 *)(frame_ + FRAME_OFF(1768)))
#define local_69f (*(i8 *)(frame_ + FRAME_OFF(1769)))
#define local_69c (*(i32 *)(frame_ + FRAME_OFF(1772)))
#define local_698 (*(i32 *)(frame_ + FRAME_OFF(1776)))
#define local_694 (*(i32 *)(frame_ + FRAME_OFF(1780)))
#define local_690 (*(i32 *)(frame_ + FRAME_OFF(1784)))
#define local_68c (*(i32 *)(frame_ + FRAME_OFF(1788)))
#define local_688 (*(i32 *)(frame_ + FRAME_OFF(1792)))
#define local_684 (*(i8 *)(frame_ + FRAME_OFF(1796)))
#define local_683 (*(i8 *)(frame_ + FRAME_OFF(1797)))
#define local_680 (*(i32 *)(frame_ + FRAME_OFF(1800)))
#define local_67c (*(i32 *)(frame_ + FRAME_OFF(1804)))
#define local_678 (*(i32 *)(frame_ + FRAME_OFF(1808)))
#define local_674 (*(i32 *)(frame_ + FRAME_OFF(1812)))
#define local_670 (*(i32 *)(frame_ + FRAME_OFF(1816)))
#define local_66c (*(i32 *)(frame_ + FRAME_OFF(1820)))
#define local_668 (*(i8 *)(frame_ + FRAME_OFF(1824)))
#define local_667 (*(i8 *)(frame_ + FRAME_OFF(1825)))
#define local_664 (*(i32 *)(frame_ + FRAME_OFF(1828)))
#define local_660 (*(i32 *)(frame_ + FRAME_OFF(1832)))
#define local_65c (*(i32 *)(frame_ + FRAME_OFF(1836)))
#define local_658 (*(i32 *)(frame_ + FRAME_OFF(1840)))
#define local_654 (*(i32 *)(frame_ + FRAME_OFF(1844)))
#define local_650 (*(i32 *)(frame_ + FRAME_OFF(1848)))
#define local_64c (*(i8 *)(frame_ + FRAME_OFF(1852)))
#define local_64b (*(i8 *)(frame_ + FRAME_OFF(1853)))
#define local_648 (*(i32 *)(frame_ + FRAME_OFF(1856)))
#define local_644 (*(i32 *)(frame_ + FRAME_OFF(1860)))
#define local_640 (*(i32 *)(frame_ + FRAME_OFF(1864)))
#define local_63c (*(i32 *)(frame_ + FRAME_OFF(1868)))
#define local_638 (*(i32 *)(frame_ + FRAME_OFF(1872)))
#define local_634 (*(i32 *)(frame_ + FRAME_OFF(1876)))
#define local_630 (*(i8 *)(frame_ + FRAME_OFF(1880)))
#define local_62f (*(i8 *)(frame_ + FRAME_OFF(1881)))
#define local_62c (*(i32 *)(frame_ + FRAME_OFF(1884)))
#define local_628 (*(i32 *)(frame_ + FRAME_OFF(1888)))
#define local_624 (*(i32 *)(frame_ + FRAME_OFF(1892)))
#define local_620 (*(i32 *)(frame_ + FRAME_OFF(1896)))
#define local_61c (*(i32 *)(frame_ + FRAME_OFF(1900)))
#define local_618 (*(i32 *)(frame_ + FRAME_OFF(1904)))
#define local_614 (*(i8 *)(frame_ + FRAME_OFF(1908)))
#define local_613 (*(i8 *)(frame_ + FRAME_OFF(1909)))
#define local_610 (*(i32 *)(frame_ + FRAME_OFF(1912)))
#define local_60c (*(i32 *)(frame_ + FRAME_OFF(1916)))
#define local_608 (*(i32 *)(frame_ + FRAME_OFF(1920)))
#define local_604 (*(i32 *)(frame_ + FRAME_OFF(1924)))
#define local_600 (*(i32 *)(frame_ + FRAME_OFF(1928)))
#define local_5fc (*(i32 *)(frame_ + FRAME_OFF(1932)))
#define local_5f8 (*(i8 *)(frame_ + FRAME_OFF(1936)))
#define local_5f7 (*(i8 *)(frame_ + FRAME_OFF(1937)))
#define local_5f4 (*(i32 *)(frame_ + FRAME_OFF(1940)))
#define local_5f0 (*(i32 *)(frame_ + FRAME_OFF(1944)))
#define local_5ec (*(i32 *)(frame_ + FRAME_OFF(1948)))
#define local_5e8 (*(i32 *)(frame_ + FRAME_OFF(1952)))
#define local_5e4 (*(i32 *)(frame_ + FRAME_OFF(1956)))
#define local_5e0 (*(i32 *)(frame_ + FRAME_OFF(1960)))
#define local_5dc (*(i8 *)(frame_ + FRAME_OFF(1964)))
#define local_5db (*(i8 *)(frame_ + FRAME_OFF(1965)))
#define local_5d8 (*(i32 *)(frame_ + FRAME_OFF(1968)))
#define local_5d4 (*(i32 *)(frame_ + FRAME_OFF(1972)))
#define local_5d0 (*(i32 *)(frame_ + FRAME_OFF(1976)))
#define local_5cc (*(i32 *)(frame_ + FRAME_OFF(1980)))
#define local_5c8 (*(i32 *)(frame_ + FRAME_OFF(1984)))
#define local_5c4 (*(i32 *)(frame_ + FRAME_OFF(1988)))
#define local_5c0 (*(i8 *)(frame_ + FRAME_OFF(1992)))
#define local_5bf (*(i8 *)(frame_ + FRAME_OFF(1993)))
#define local_5bc (*(i32 *)(frame_ + FRAME_OFF(1996)))
#define local_5b8 (*(i32 *)(frame_ + FRAME_OFF(2000)))
#define local_5b4 (*(i32 *)(frame_ + FRAME_OFF(2004)))
#define local_5b0 (*(i32 *)(frame_ + FRAME_OFF(2008)))
#define local_5ac (*(i32 *)(frame_ + FRAME_OFF(2012)))
#define local_5a8 (*(i32 *)(frame_ + FRAME_OFF(2016)))
#define local_5a4 (*(i8 *)(frame_ + FRAME_OFF(2020)))
#define local_5a3 (*(i8 *)(frame_ + FRAME_OFF(2021)))
#define local_5a0 (*(i32 *)(frame_ + FRAME_OFF(2024)))
#define local_59c (*(i32 *)(frame_ + FRAME_OFF(2028)))
#define local_598 (*(i32 *)(frame_ + FRAME_OFF(2032)))
#define local_594 (*(i32 *)(frame_ + FRAME_OFF(2036)))
#define local_590 (*(i32 *)(frame_ + FRAME_OFF(2040)))
#define local_58c (*(i32 *)(frame_ + FRAME_OFF(2044)))
#define local_588 (*(i8 *)(frame_ + FRAME_OFF(2048)))
#define local_587 (*(i8 *)(frame_ + FRAME_OFF(2049)))
#define local_584 (*(i32 *)(frame_ + FRAME_OFF(2052)))
#define local_580 (*(i32 *)(frame_ + FRAME_OFF(2056)))
#define local_57c (*(i32 *)(frame_ + FRAME_OFF(2060)))
#define local_578 (*(i32 *)(frame_ + FRAME_OFF(2064)))
#define local_574 (*(i32 *)(frame_ + FRAME_OFF(2068)))
#define local_570 (*(i32 *)(frame_ + FRAME_OFF(2072)))
#define local_56c (*(i8 *)(frame_ + FRAME_OFF(2076)))
#define local_56b (*(i8 *)(frame_ + FRAME_OFF(2077)))
#define local_568 (*(i32 *)(frame_ + FRAME_OFF(2080)))
#define local_564 (*(i32 *)(frame_ + FRAME_OFF(2084)))
#define local_560 (*(i32 *)(frame_ + FRAME_OFF(2088)))
#define local_55c (*(i32 *)(frame_ + FRAME_OFF(2092)))
#define local_558 (*(i32 *)(frame_ + FRAME_OFF(2096)))
#define local_554 (*(i32 *)(frame_ + FRAME_OFF(2100)))
#define local_550 (*(i8 *)(frame_ + FRAME_OFF(2104)))
#define local_54f (*(i8 *)(frame_ + FRAME_OFF(2105)))
#define local_54c (*(i32 *)(frame_ + FRAME_OFF(2108)))
#define local_548 (*(i32 *)(frame_ + FRAME_OFF(2112)))
#define local_544 (*(i32 *)(frame_ + FRAME_OFF(2116)))
#define local_540 (*(i32 *)(frame_ + FRAME_OFF(2120)))
#define local_53c (*(i32 *)(frame_ + FRAME_OFF(2124)))
#define local_538 (*(i32 *)(frame_ + FRAME_OFF(2128)))
#define local_534 (*(i8 *)(frame_ + FRAME_OFF(2132)))
#define local_533 (*(i8 *)(frame_ + FRAME_OFF(2133)))
#define local_530 (*(i32 *)(frame_ + FRAME_OFF(2136)))
#define local_52c (*(i32 *)(frame_ + FRAME_OFF(2140)))
#define local_528 (*(i32 *)(frame_ + FRAME_OFF(2144)))
#define local_524 (*(i32 *)(frame_ + FRAME_OFF(2148)))
#define local_520 (*(i32 *)(frame_ + FRAME_OFF(2152)))
#define local_51c (*(i32 *)(frame_ + FRAME_OFF(2156)))
#define local_518 (*(i8 *)(frame_ + FRAME_OFF(2160)))
#define local_517 (*(i8 *)(frame_ + FRAME_OFF(2161)))
#define local_514 (*(i32 *)(frame_ + FRAME_OFF(2164)))
#define local_510 (*(i32 *)(frame_ + FRAME_OFF(2168)))
#define local_50c (*(i32 *)(frame_ + FRAME_OFF(2172)))
#define local_508 (*(i32 *)(frame_ + FRAME_OFF(2176)))
#define local_504 (*(i32 *)(frame_ + FRAME_OFF(2180)))
#define local_500 (*(i32 *)(frame_ + FRAME_OFF(2184)))
#define local_4fc (*(i8 *)(frame_ + FRAME_OFF(2188)))
#define local_4fb (*(i8 *)(frame_ + FRAME_OFF(2189)))
#define local_4f8 (*(i32 *)(frame_ + FRAME_OFF(2192)))
#define local_4f4 (*(i32 *)(frame_ + FRAME_OFF(2196)))
#define local_4f0 (*(i32 *)(frame_ + FRAME_OFF(2200)))
#define local_4ec (*(i32 *)(frame_ + FRAME_OFF(2204)))
#define local_4e8 (*(i32 *)(frame_ + FRAME_OFF(2208)))
#define local_4e4 (*(i32 *)(frame_ + FRAME_OFF(2212)))
#define local_4e0 (*(i8 *)(frame_ + FRAME_OFF(2216)))
#define local_4df (*(i8 *)(frame_ + FRAME_OFF(2217)))
#define local_4dc (*(i32 *)(frame_ + FRAME_OFF(2220)))
#define local_4d8 (*(i32 *)(frame_ + FRAME_OFF(2224)))
#define local_4d4 (*(i32 *)(frame_ + FRAME_OFF(2228)))
#define local_4d0 (*(i32 *)(frame_ + FRAME_OFF(2232)))
#define local_4cc (*(i32 *)(frame_ + FRAME_OFF(2236)))
#define local_4c8 (*(i32 *)(frame_ + FRAME_OFF(2240)))
#define local_4c4 (*(i8 *)(frame_ + FRAME_OFF(2244)))
#define local_4c3 (*(i8 *)(frame_ + FRAME_OFF(2245)))
#define local_4c0 (*(i32 *)(frame_ + FRAME_OFF(2248)))
#define local_4bc (*(i32 *)(frame_ + FRAME_OFF(2252)))
#define local_4b8 (*(i32 *)(frame_ + FRAME_OFF(2256)))
#define local_4b4 (*(i32 *)(frame_ + FRAME_OFF(2260)))
#define local_4b0 (*(i32 *)(frame_ + FRAME_OFF(2264)))
#define local_4ac (*(i32 *)(frame_ + FRAME_OFF(2268)))
#define local_4a8 (*(i8 *)(frame_ + FRAME_OFF(2272)))
#define local_4a7 (*(i8 *)(frame_ + FRAME_OFF(2273)))
#define local_4a4 (*(i32 *)(frame_ + FRAME_OFF(2276)))
#define local_4a0 (*(i32 *)(frame_ + FRAME_OFF(2280)))
#define local_49c (*(i32 *)(frame_ + FRAME_OFF(2284)))
#define local_498 (*(i32 *)(frame_ + FRAME_OFF(2288)))
#define local_494 (*(i32 *)(frame_ + FRAME_OFF(2292)))
#define local_490 (*(i32 *)(frame_ + FRAME_OFF(2296)))
#define local_48c (*(i8 *)(frame_ + FRAME_OFF(2300)))
#define local_48b (*(i8 *)(frame_ + FRAME_OFF(2301)))
#define local_488 (*(i32 *)(frame_ + FRAME_OFF(2304)))
#define local_484 (*(i32 *)(frame_ + FRAME_OFF(2308)))
#define local_480 (*(i32 *)(frame_ + FRAME_OFF(2312)))
#define local_47c (*(i32 *)(frame_ + FRAME_OFF(2316)))
#define local_478 (*(i32 *)(frame_ + FRAME_OFF(2320)))
#define local_474 (*(i32 *)(frame_ + FRAME_OFF(2324)))
#define local_470 (*(i8 *)(frame_ + FRAME_OFF(2328)))
#define local_46f (*(i8 *)(frame_ + FRAME_OFF(2329)))
#define local_46c (*(i32 *)(frame_ + FRAME_OFF(2332)))
#define local_468 (*(i32 *)(frame_ + FRAME_OFF(2336)))
#define local_464 (*(i32 *)(frame_ + FRAME_OFF(2340)))
#define local_460 (*(i32 *)(frame_ + FRAME_OFF(2344)))
#define local_45c (*(i32 *)(frame_ + FRAME_OFF(2348)))
#define local_458 (*(i32 *)(frame_ + FRAME_OFF(2352)))
#define local_454 (*(i8 *)(frame_ + FRAME_OFF(2356)))
#define local_453 (*(i8 *)(frame_ + FRAME_OFF(2357)))
#define local_450 (*(i32 *)(frame_ + FRAME_OFF(2360)))
#define local_44c (*(i32 *)(frame_ + FRAME_OFF(2364)))
#define local_448 (*(i32 *)(frame_ + FRAME_OFF(2368)))
#define local_444 (*(i32 *)(frame_ + FRAME_OFF(2372)))
#define local_440 (*(i32 *)(frame_ + FRAME_OFF(2376)))
#define local_43c (*(i32 *)(frame_ + FRAME_OFF(2380)))
#define local_438 (*(i8 *)(frame_ + FRAME_OFF(2384)))
#define local_437 (*(i8 *)(frame_ + FRAME_OFF(2385)))
#define local_434 (*(i32 *)(frame_ + FRAME_OFF(2388)))
#define local_430 (*(i32 *)(frame_ + FRAME_OFF(2392)))
#define local_42c (*(i32 *)(frame_ + FRAME_OFF(2396)))
#define local_428 (*(i32 *)(frame_ + FRAME_OFF(2400)))
#define local_424 (*(i32 *)(frame_ + FRAME_OFF(2404)))
#define local_420 (*(i32 *)(frame_ + FRAME_OFF(2408)))
#define local_41c (*(i8 *)(frame_ + FRAME_OFF(2412)))
#define local_41b (*(i8 *)(frame_ + FRAME_OFF(2413)))
#define local_418 (*(i32 *)(frame_ + FRAME_OFF(2416)))
#define local_414 (*(i32 *)(frame_ + FRAME_OFF(2420)))
#define local_410 (*(i32 *)(frame_ + FRAME_OFF(2424)))
#define local_40c (*(i32 *)(frame_ + FRAME_OFF(2428)))
#define local_408 (*(i32 *)(frame_ + FRAME_OFF(2432)))
#define local_404 (*(i32 *)(frame_ + FRAME_OFF(2436)))
#define local_400 (*(i8 *)(frame_ + FRAME_OFF(2440)))
#define local_3ff (*(i8 *)(frame_ + FRAME_OFF(2441)))
#define local_3fc (*(i32 *)(frame_ + FRAME_OFF(2444)))
#define local_3f8 (*(i32 *)(frame_ + FRAME_OFF(2448)))
#define local_3f4 (*(i32 *)(frame_ + FRAME_OFF(2452)))
#define local_3f0 (*(i32 *)(frame_ + FRAME_OFF(2456)))
#define local_3ec (*(i32 *)(frame_ + FRAME_OFF(2460)))
#define local_3e8 (*(i32 *)(frame_ + FRAME_OFF(2464)))
#define local_3e4 (*(i8 *)(frame_ + FRAME_OFF(2468)))
#define local_3e3 (*(i8 *)(frame_ + FRAME_OFF(2469)))
#define local_3e0 (*(i32 *)(frame_ + FRAME_OFF(2472)))
#define local_3dc (*(i32 *)(frame_ + FRAME_OFF(2476)))
#define local_3d8 (*(i32 *)(frame_ + FRAME_OFF(2480)))
#define local_3d4 (*(i32 *)(frame_ + FRAME_OFF(2484)))
#define local_3d0 (*(i32 *)(frame_ + FRAME_OFF(2488)))
#define local_3cc (*(i32 *)(frame_ + FRAME_OFF(2492)))
#define local_3c8 (*(i8 *)(frame_ + FRAME_OFF(2496)))
#define local_3c7 (*(i8 *)(frame_ + FRAME_OFF(2497)))
#define local_3c4 (*(i32 *)(frame_ + FRAME_OFF(2500)))
#define local_3c0 (*(i32 *)(frame_ + FRAME_OFF(2504)))
#define local_3bc (*(i32 *)(frame_ + FRAME_OFF(2508)))
#define local_3b8 (*(i32 *)(frame_ + FRAME_OFF(2512)))
#define local_3b4 (*(i32 *)(frame_ + FRAME_OFF(2516)))
#define local_3b0 (*(i32 *)(frame_ + FRAME_OFF(2520)))
#define local_3ac (*(i8 *)(frame_ + FRAME_OFF(2524)))
#define local_3ab (*(i8 *)(frame_ + FRAME_OFF(2525)))
#define local_3a8 (*(i32 *)(frame_ + FRAME_OFF(2528)))
#define local_3a4 (*(i32 *)(frame_ + FRAME_OFF(2532)))
#define local_3a0 (*(i32 *)(frame_ + FRAME_OFF(2536)))
#define local_39c (*(i32 *)(frame_ + FRAME_OFF(2540)))
#define local_398 (*(i32 *)(frame_ + FRAME_OFF(2544)))
#define local_394 (*(i32 *)(frame_ + FRAME_OFF(2548)))
#define local_390 (*(i8 *)(frame_ + FRAME_OFF(2552)))
#define local_38f (*(i8 *)(frame_ + FRAME_OFF(2553)))
#define local_38c (*(i32 *)(frame_ + FRAME_OFF(2556)))
#define local_388 (*(i32 *)(frame_ + FRAME_OFF(2560)))
#define local_384 (*(i32 *)(frame_ + FRAME_OFF(2564)))
#define local_380 (*(i32 *)(frame_ + FRAME_OFF(2568)))
#define local_37c (*(i32 *)(frame_ + FRAME_OFF(2572)))
#define local_378 (*(i32 *)(frame_ + FRAME_OFF(2576)))
#define local_374 (*(i8 *)(frame_ + FRAME_OFF(2580)))
#define local_373 (*(i8 *)(frame_ + FRAME_OFF(2581)))
#define local_370 (*(i32 *)(frame_ + FRAME_OFF(2584)))
#define local_36c (*(i32 *)(frame_ + FRAME_OFF(2588)))
#define local_368 (*(i32 *)(frame_ + FRAME_OFF(2592)))
#define local_364 (*(i32 *)(frame_ + FRAME_OFF(2596)))
#define local_360 (*(i32 *)(frame_ + FRAME_OFF(2600)))
#define local_35c (*(i32 *)(frame_ + FRAME_OFF(2604)))
#define local_358 (*(i8 *)(frame_ + FRAME_OFF(2608)))
#define local_357 (*(i8 *)(frame_ + FRAME_OFF(2609)))
#define local_354 (*(i32 *)(frame_ + FRAME_OFF(2612)))
#define local_350 (*(i32 *)(frame_ + FRAME_OFF(2616)))
#define local_34c (*(i32 *)(frame_ + FRAME_OFF(2620)))
#define local_348 (*(i32 *)(frame_ + FRAME_OFF(2624)))
#define local_344 (*(i32 *)(frame_ + FRAME_OFF(2628)))
#define local_340 (*(i32 *)(frame_ + FRAME_OFF(2632)))
#define local_33c (*(i8 *)(frame_ + FRAME_OFF(2636)))
#define local_33b (*(i8 *)(frame_ + FRAME_OFF(2637)))
#define local_338 (*(i32 *)(frame_ + FRAME_OFF(2640)))
#define local_334 (*(i32 *)(frame_ + FRAME_OFF(2644)))
#define local_330 (*(i32 *)(frame_ + FRAME_OFF(2648)))
#define local_32c (*(i32 *)(frame_ + FRAME_OFF(2652)))
#define local_328 (*(i32 *)(frame_ + FRAME_OFF(2656)))
#define local_324 (*(i32 *)(frame_ + FRAME_OFF(2660)))
#define local_320 (*(i8 *)(frame_ + FRAME_OFF(2664)))
#define local_31f (*(i8 *)(frame_ + FRAME_OFF(2665)))
#define local_31c (*(i32 *)(frame_ + FRAME_OFF(2668)))
#define local_318 (*(i32 *)(frame_ + FRAME_OFF(2672)))
#define local_314 (*(i32 *)(frame_ + FRAME_OFF(2676)))
#define local_310 (*(i32 *)(frame_ + FRAME_OFF(2680)))
#define local_30c (*(i32 *)(frame_ + FRAME_OFF(2684)))
#define local_308 (*(i32 *)(frame_ + FRAME_OFF(2688)))
#define local_304 (*(i8 *)(frame_ + FRAME_OFF(2692)))
#define local_303 (*(i8 *)(frame_ + FRAME_OFF(2693)))
#define local_300 (*(i32 *)(frame_ + FRAME_OFF(2696)))
#define local_2fc (*(i32 *)(frame_ + FRAME_OFF(2700)))
#define local_2f8 (*(i32 *)(frame_ + FRAME_OFF(2704)))
#define local_2f4 (*(i32 *)(frame_ + FRAME_OFF(2708)))
#define local_2f0 (*(i32 *)(frame_ + FRAME_OFF(2712)))
#define local_2ec (*(i32 *)(frame_ + FRAME_OFF(2716)))
#define local_2e8 (*(i8 (*)[72])(frame_ + FRAME_OFF(2720)))
#define local_2a0 (*(int *)(frame_ + FRAME_OFF(2792)))
#define local_29c (*(i8 (*)[72])(frame_ + FRAME_OFF(2796)))
#define local_254 (*(i8 (*)[72])(frame_ + FRAME_OFF(2868)))
#define local_20c (*(i8 (*)[72])(frame_ + FRAME_OFF(2940)))
#define local_1c4 (*(i8 (*)[72])(frame_ + FRAME_OFF(3012)))
#define local_17c (*(int *)(frame_ + FRAME_OFF(3084)))
#define local_178 (*(i8 (*)[72])(frame_ + FRAME_OFF(3088)))
#define local_130 (*(i8 (*)[72])(frame_ + FRAME_OFF(3160)))
#define local_e8 (*(i8 (*)[72])(frame_ + FRAME_OFF(3232)))
#define local_a0 (*(i8 (*)[72])(frame_ + FRAME_OFF(3304)))
#define local_58 (*(i8 (*)[72])(frame_ + FRAME_OFF(3376)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(3448)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(3452)))
#define local_8 (*(int *)(frame_ + FRAME_OFF(3456)))
i32 __thiscall spaceship_wnd_render_ship(void *this)

{
  byte bVar1;
  int iVar2;
  i8 frame_[FRAME_OFF(3464)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004d4a62;
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
  local_c88[0] = 2;
  local_c88[1] = 6;
  local_c84[0] = 0x1cf;
  local_c84[1] = 0xb2;
  local_c84[2] = 0xaa;
  local_c84[3] = 0x2b;
  local_c84[4] = 0x33;
  local_c84[5] = 0x204;
  local_c6c = 2;
  local_c6b = 6;
  local_c68 = 0x1d0;
  local_c64 = 0x189;
  local_c60 = 0x68;
  local_c5c = 0x3d;
  local_c58 = 0x28;
  local_c54 = 0x230;
  local_c50 = 0;
  local_c4f = 7;
  local_c4c = 0x197;
  local_c48 = 0x1df;
  local_c44 = 0x13c;
  local_c40 = 0x3a;
  local_c3c = 0x22;
  local_c38 = 0x44;
  local_c34 = 2;
  local_c33 = 2;
  local_c30 = 0x1c9;
  local_c2c = 0x1de;
  local_c28 = 0x144;
  local_c24 = 0x19;
  local_c20 = 0x36;
  local_c1c = 0x92;
  local_c18 = 2;
  local_c17 = 2;
  local_c14 = 0x1ca;
  local_c10 = 0x1fa;
  local_c0c = 0x139;
  local_c08 = 0x26;
  local_c04 = 0x27;
  local_c00 = 0xac;
  local_bfc = 0;
  local_bfb = 9;
  local_bf8 = 0x199;
  local_bf4 = 0x1e2;
  local_bf0 = 0x145;
  local_bec = 0x42;
  local_be8 = 0x37;
  local_be4 = 0x7f;
  local_be0 = 1;
  local_bdf = 2;
  local_bdc = 0x1bb;
  local_bd8 = 0x1df;
  local_bd4 = 0x13f;
  local_bd0 = 0x4d;
  local_bcc = 0x4e;
  local_bc8 = 0x69;
  local_bc4[0] = 0;
  local_bc4[1] = 0;
  local_bc4[4] = 0x90;
  local_bc4[5] = 1;
  local_bc4[6] = 0;
  local_bc4[7] = 0;
  local_bc4[8] = 0x38;
  local_bc4[9] = 1;
  local_bc4[10] = 0;
  local_bc4[0xb] = 0;
  local_bc4[0xc] = 0x9d;
  local_bc4[0xd] = 0;
  local_bc4[0xe] = 0;
  local_bc4[0xf] = 0;
  local_bc4[0x10] = 0xfd;
  local_bc4[0x11] = 0;
  local_bc4[0x12] = 0;
  local_bc4[0x13] = 0;
  local_bc4[0x14] = 0xf0;
  local_bc4[0x15] = 0;
  local_bc4[0x16] = 0;
  local_bc4[0x17] = 0;
  local_bc4[0x18] = 0;
  local_bc4[0x19] = 0;
  local_bc4[0x1a] = 0;
  local_bc4[0x1b] = 0;
  local_bc4[0x1c] = 0;
  local_bc4[0x1d] = 1;
  local_bc4[0x20] = 0x91;
  local_bc4[0x21] = 1;
  local_bc4[0x22] = 0;
  local_bc4[0x23] = 0;
  local_bc4[0x24] = 0x38;
  local_bc4[0x25] = 1;
  local_bc4[0x26] = 0;
  local_bc4[0x27] = 0;
  local_bc4[0x28] = 0x9d;
  local_bc4[0x29] = 0;
  local_bc4[0x2a] = 0;
  local_bc4[0x2b] = 0;
  local_bc4[0x2c] = 0xfd;
  local_bc4[0x2d] = 0;
  local_bc4[0x2e] = 0;
  local_bc4[0x2f] = 0;
  local_bc4[0x30] = 0xf0;
  local_bc4[0x31] = 0;
  local_bc4[0x32] = 0;
  local_bc4[0x33] = 0;
  local_bc4[0x34] = 0;
  local_bc4[0x35] = 0;
  local_bc4[0x36] = 0;
  local_bc4[0x37] = 0;
  local_bc4[0x38] = 0;
  local_bc4[0x39] = 2;
  local_bc4[0x3c] = 0x92;
  local_bc4[0x3d] = 1;
  local_bc4[0x3e] = 0;
  local_bc4[0x3f] = 0;
  local_bc4[0x40] = 0x38;
  local_bc4[0x41] = 1;
  local_bc4[0x42] = 0;
  local_bc4[0x43] = 0;
  local_bc4[0x44] = 0x9d;
  local_bc4[0x45] = 0;
  local_bc4[0x46] = 0;
  local_bc4[0x47] = 0;
  local_bc4[0x48] = 0xfd;
  local_bc4[0x49] = 0;
  local_bc4[0x4a] = 0;
  local_bc4[0x4b] = 0;
  local_bc4[0x4c] = 0xf0;
  local_bc4[0x4d] = 0;
  local_bc4[0x4e] = 0;
  local_bc4[0x4f] = 0;
  local_bc4[0x50] = 0;
  local_bc4[0x51] = 0;
  local_bc4[0x52] = 0;
  local_bc4[0x53] = 0;
  local_bc4[0x54] = 0;
  local_bc4[0x55] = 3;
  local_bc4[0x58] = 0x93;
  local_bc4[0x59] = 1;
  local_bc4[0x5a] = 0;
  local_bc4[0x5b] = 0;
  local_bc4[0x5c] = 0x38;
  local_bc4[0x5d] = 1;
  local_bc4[0x5e] = 0;
  local_bc4[0x5f] = 0;
  local_bc4[0x60] = 0x9d;
  local_bc4[0x61] = 0;
  local_bc4[0x62] = 0;
  local_bc4[99] = 0;
  local_bc4[100] = 0xfd;
  local_bc4[0x65] = 0;
  local_bc4[0x66] = 0;
  local_bc4[0x67] = 0;
  local_bc4[0x68] = 0xf0;
  local_bc4[0x69] = 0;
  local_bc4[0x6a] = 0;
  local_bc4[0x6b] = 0;
  local_bc4[0x6c] = 0;
  local_bc4[0x6d] = 0;
  local_bc4[0x6e] = 0;
  local_bc4[0x6f] = 0;
  local_bc4[0x70] = 0;
  local_bc4[0x71] = 4;
  local_bc4[0x74] = 0x94;
  local_bc4[0x75] = 1;
  local_bc4[0x76] = 0;
  local_bc4[0x77] = 0;
  local_bc4[0x78] = 0x38;
  local_bc4[0x79] = 1;
  local_bc4[0x7a] = 0;
  local_bc4[0x7b] = 0;
  local_bc4[0x7c] = 0x9d;
  local_bc4[0x7d] = 0;
  local_bc4[0x7e] = 0;
  local_bc4[0x7f] = 0;
  local_bc4[0x80] = 0xfd;
  local_bc4[0x81] = 0;
  local_bc4[0x82] = 0;
  local_bc4[0x83] = 0;
  local_bc4[0x84] = 0xf0;
  local_bc4[0x85] = 0;
  local_bc4[0x86] = 0;
  local_bc4[0x87] = 0;
  local_bc4[0x88] = 0;
  local_bc4[0x89] = 0;
  local_bc4[0x8a] = 0;
  local_bc4[0x8b] = 0;
  local_bc4[0x8c] = 0;
  local_bc4[0x8d] = 6;
  local_bc4[0x90] = 0x96;
  local_bc4[0x91] = 1;
  local_bc4[0x92] = 0;
  local_bc4[0x93] = 0;
  local_bc4[0x94] = 0x38;
  local_bc4[0x95] = 1;
  local_bc4[0x96] = 0;
  local_bc4[0x97] = 0;
  local_bc4[0x98] = 0x9d;
  local_bc4[0x99] = 0;
  local_bc4[0x9a] = 0;
  local_bc4[0x9b] = 0;
  local_bc4[0x9c] = 0xfd;
  local_bc4[0x9d] = 0;
  local_bc4[0x9e] = 0;
  local_bc4[0x9f] = 0;
  local_bc4[0xa0] = 0xf0;
  local_bc4[0xa1] = 0;
  local_bc4[0xa2] = 0;
  local_bc4[0xa3] = 0;
  local_bc4[0xa4] = 0;
  local_bc4[0xa5] = 0;
  local_bc4[0xa6] = 0;
  local_bc4[0xa7] = 0;
  local_bc4[0xa8] = 0;
  local_bc4[0xa9] = 8;
  local_bc4[0xac] = 0x98;
  local_bc4[0xad] = 1;
  local_bc4[0xae] = 0;
  local_bc4[0xaf] = 0;
  local_bc4[0xb0] = 0x38;
  local_bc4[0xb1] = 1;
  local_bc4[0xb2] = 0;
  local_bc4[0xb3] = 0;
  local_bc4[0xb4] = 0x9d;
  local_bc4[0xb5] = 0;
  local_bc4[0xb6] = 0;
  local_bc4[0xb7] = 0;
  local_bc4[0xb8] = 0xfd;
  local_bc4[0xb9] = 0;
  local_bc4[0xba] = 0;
  local_bc4[0xbb] = 0;
  local_bc4[0xbc] = 0xf0;
  local_bc4[0xbd] = 0;
  local_bc4[0xbe] = 0;
  local_bc4[0xbf] = 0;
  local_bc4[0xc0] = 0;
  local_bc4[0xc1] = 0;
  local_bc4[0xc2] = 0;
  local_bc4[0xc3] = 0;
  local_bc4[0xc4] = 0;
  local_bc4[0xc5] = 10;
  local_bc4[200] = 0x9a;
  local_bc4[0xc9] = 1;
  local_bc4[0xca] = 0;
  local_bc4[0xcb] = 0;
  local_bc4[0xcc] = 0x38;
  local_bc4[0xcd] = 1;
  local_bc4[0xce] = 0;
  local_bc4[0xcf] = 0;
  local_bc4[0xd0] = 0x9d;
  local_bc4[0xd1] = 0;
  local_bc4[0xd2] = 0;
  local_bc4[0xd3] = 0;
  local_bc4[0xd4] = 0xfd;
  local_bc4[0xd5] = 0;
  local_bc4[0xd6] = 0;
  local_bc4[0xd7] = 0;
  local_bc4[0xd8] = 0xf0;
  local_bc4[0xd9] = 0;
  local_bc4[0xda] = 0;
  local_bc4[0xdb] = 0;
  local_bc4[0xdc] = 0;
  local_bc4[0xdd] = 0;
  local_bc4[0xde] = 0;
  local_bc4[0xdf] = 0;
  local_bc4[0xe0] = 0;
  local_bc4[0xe1] = 0xc;
  local_bc4[0xe4] = 0x9c;
  local_bc4[0xe5] = 1;
  local_bc4[0xe6] = 0;
  local_bc4[0xe7] = 0;
  local_bc4[0xe8] = 0x38;
  local_bc4[0xe9] = 1;
  local_bc4[0xea] = 0;
  local_bc4[0xeb] = 0;
  local_bc4[0xec] = 0x9d;
  local_bc4[0xed] = 0;
  local_bc4[0xee] = 0;
  local_bc4[0xef] = 0;
  local_bc4[0xf0] = 0xfd;
  local_bc4[0xf1] = 0;
  local_bc4[0xf2] = 0;
  local_bc4[0xf3] = 0;
  local_bc4[0xf4] = 0xf0;
  local_bc4[0xf5] = 0;
  local_bc4[0xf6] = 0;
  local_bc4[0xf7] = 0;
  local_bc4[0xf8] = 0;
  local_bc4[0xf9] = 0;
  local_bc4[0xfa] = 0;
  local_bc4[0xfb] = 0;
  local_bc4[0xfc] = 0;
  local_bc4[0xfd] = 0xe;
  local_bc4[0x100] = 0x9e;
  local_bc4[0x101] = 1;
  local_bc4[0x102] = 0;
  local_bc4[0x103] = 0;
  local_bc4[0x104] = 0x37;
  local_bc4[0x105] = 1;
  local_bc4[0x106] = 0;
  local_bc4[0x107] = 0;
  local_bc4[0x108] = 0x9d;
  local_bc4[0x109] = 0;
  local_bc4[0x10a] = 0;
  local_bc4[0x10b] = 0;
  local_bc4[0x10c] = 0xfe;
  local_bc4[0x10d] = 0;
  local_bc4[0x10e] = 0;
  local_bc4[0x10f] = 0;
  local_bc4[0x110] = 0xf0;
  local_bc4[0x111] = 0;
  local_bc4[0x112] = 0;
  local_bc4[0x113] = 0;
  local_bc4[0x114] = 0;
  local_bc4[0x115] = 0;
  local_bc4[0x116] = 0;
  local_bc4[0x117] = 0;
  local_bc4[0x118] = 0;
  local_bc4[0x119] = 0x10;
  local_bc4[0x11c] = 0xa0;
  local_bc4[0x11d] = 1;
  local_bc4[0x11e] = 0;
  local_bc4[0x11f] = 0;
  local_bc4[0x120] = 0x37;
  local_bc4[0x121] = 1;
  local_bc4[0x122] = 0;
  local_bc4[0x123] = 0;
  local_bc4[0x124] = 0x9d;
  local_bc4[0x125] = 0;
  local_bc4[0x126] = 0;
  local_bc4[0x127] = 0;
  local_bc4[0x128] = 0xfe;
  local_bc4[0x129] = 0;
  local_bc4[0x12a] = 0;
  local_bc4[299] = 0;
  local_bc4[300] = 0xf0;
  local_bc4[0x12d] = 0;
  local_bc4[0x12e] = 0;
  local_bc4[0x12f] = 0;
  local_bc4[0x130] = 0;
  local_bc4[0x131] = 0;
  local_bc4[0x132] = 0;
  local_bc4[0x133] = 0;
  local_bc4[0x134] = 0;
  local_bc4[0x135] = 0x12;
  local_bc4[0x138] = 0xa2;
  local_bc4[0x139] = 1;
  local_bc4[0x13a] = 0;
  local_bc4[0x13b] = 0;
  local_bc4[0x13c] = 0x37;
  local_bc4[0x13d] = 1;
  local_bc4[0x13e] = 0;
  local_bc4[0x13f] = 0;
  local_bc4[0x140] = 0x9d;
  local_bc4[0x141] = 0;
  local_bc4[0x142] = 0;
  local_bc4[0x143] = 0;
  local_bc4[0x144] = 0xfe;
  local_bc4[0x145] = 0;
  local_bc4[0x146] = 0;
  local_bc4[0x147] = 0;
  local_bc4[0x148] = 0xf0;
  local_bc4[0x149] = 0;
  local_bc4[0x14a] = 0;
  local_bc4[0x14b] = 0;
  local_bc4[0x14c] = 0;
  local_bc4[0x14d] = 0;
  local_bc4[0x14e] = 0;
  local_bc4[0x14f] = 0;
  local_bc4[0x150] = 0;
  local_bc4[0x151] = 0x14;
  local_bc4[0x154] = 0xa5;
  local_bc4[0x155] = 1;
  local_bc4[0x156] = 0;
  local_bc4[0x157] = 0;
  local_bc4[0x158] = 0x37;
  local_bc4[0x159] = 1;
  local_bc4[0x15a] = 0;
  local_bc4[0x15b] = 0;
  local_bc4[0x15c] = 0x9d;
  local_bc4[0x15d] = 0;
  local_bc4[0x15e] = 0;
  local_bc4[0x15f] = 0;
  local_bc4[0x160] = 0xfe;
  local_bc4[0x161] = 0;
  local_bc4[0x162] = 0;
  local_bc4[0x163] = 0;
  local_bc4[0x164] = 0xf0;
  local_bc4[0x165] = 0;
  local_bc4[0x166] = 0;
  local_bc4[0x167] = 0;
  local_bc4[0x168] = 0;
  local_bc4[0x169] = 0;
  local_bc4[0x16a] = 0;
  local_bc4[0x16b] = 0;
  local_bc4[0x16c] = 0;
  local_bc4[0x16d] = 0x16;
  local_bc4[0x170] = 0xa8;
  local_bc4[0x171] = 1;
  local_bc4[0x172] = 0;
  local_bc4[0x173] = 0;
  local_bc4[0x174] = 0x37;
  local_bc4[0x175] = 1;
  local_bc4[0x176] = 0;
  local_bc4[0x177] = 0;
  local_bc4[0x178] = 0x9d;
  local_bc4[0x179] = 0;
  local_bc4[0x17a] = 0;
  local_bc4[0x17b] = 0;
  local_bc4[0x17c] = 0x15;
  local_bc4[0x17d] = 1;
  local_bc4[0x17e] = 0;
  local_bc4[0x17f] = 0;
  local_bc4[0x180] = 0xf0;
  local_bc4[0x181] = 0;
  local_bc4[0x182] = 0;
  local_bc4[0x183] = 0;
  local_bc4[0x184] = 0;
  local_bc4[0x185] = 0;
  local_bc4[0x186] = 0;
  local_bc4[0x187] = 0;
  local_bc4[0x188] = 0;
  local_bc4[0x189] = 0x17;
  local_bc4[0x18c] = 0xa9;
  local_bc4[0x18d] = 1;
  local_bc4[0x18e] = 0;
  local_bc4[399] = 0;
  local_bc4[400] = 0xbb;
  local_bc4[0x191] = 0;
  local_bc4[0x192] = 0;
  local_bc4[0x193] = 0;
  local_bc4[0x194] = 0x72;
  local_bc4[0x195] = 0;
  local_bc4[0x196] = 0;
  local_bc4[0x197] = 0;
  local_bc4[0x198] = 0x91;
  local_bc4[0x199] = 1;
  local_bc4[0x19a] = 0;
  local_bc4[0x19b] = 0;
  local_bc4[0x19c] = 0x1b;
  local_bc4[0x19d] = 1;
  local_bc4[0x19e] = 0;
  local_bc4[0x19f] = 0;
  local_bc4[0x1a0] = 0;
  local_bc4[0x1a1] = 0;
  local_bc4[0x1a2] = 0;
  local_bc4[0x1a3] = 0;
  local_bc4[0x1a4] = 0;
  local_bc4[0x1a5] = 0x18;
  local_bc4[0x1a8] = 0xaa;
  local_bc4[0x1a9] = 1;
  local_bc4[0x1aa] = 0;
  local_bc4[0x1ab] = 0;
  local_bc4[0x1ac] = 0xbb;
  local_bc4[0x1ad] = 0;
  local_bc4[0x1ae] = 0;
  local_bc4[0x1af] = 0;
  local_bc4[0x1b0] = 0x72;
  local_bc4[0x1b1] = 0;
  local_bc4[0x1b2] = 0;
  local_bc4[0x1b3] = 0;
  local_bc4[0x1b4] = 0x91;
  local_bc4[0x1b5] = 1;
  local_bc4[0x1b6] = 0;
  local_bc4[0x1b7] = 0;
  local_bc4[0x1b8] = 0x1b;
  local_bc4[0x1b9] = 1;
  local_bc4[0x1ba] = 0;
  local_bc4[0x1bb] = 0;
  local_bc4[0x1bc] = 0;
  local_bc4[0x1bd] = 0;
  local_bc4[0x1be] = 0;
  local_bc4[0x1bf] = 0;
  local_bc4[0x1c0] = 0;
  local_bc4[0x1c1] = 0x19;
  local_bc4[0x1c4] = 0xab;
  local_bc4[0x1c5] = 1;
  local_bc4[0x1c6] = 0;
  local_bc4[0x1c7] = 0;
  local_bc4[0x1c8] = 0xba;
  local_bc4[0x1c9] = 0;
  local_bc4[0x1ca] = 0;
  local_bc4[0x1cb] = 0;
  local_bc4[0x1cc] = 0x72;
  local_bc4[0x1cd] = 0;
  local_bc4[0x1ce] = 0;
  local_bc4[0x1cf] = 0;
  local_bc4[0x1d0] = 0x92;
  local_bc4[0x1d1] = 1;
  local_bc4[0x1d2] = 0;
  local_bc4[0x1d3] = 0;
  local_bc4[0x1d4] = 0x1b;
  local_bc4[0x1d5] = 1;
  local_bc4[0x1d6] = 0;
  local_bc4[0x1d7] = 0;
  local_bc4[0x1d8] = 0;
  local_bc4[0x1d9] = 0;
  local_bc4[0x1da] = 0;
  local_bc4[0x1db] = 0;
  local_bc4[0x1dc] = 0;
  local_bc4[0x1dd] = 0x1a;
  local_bc4[0x1e0] = 0xac;
  local_bc4[0x1e1] = 1;
  local_bc4[0x1e2] = 0;
  local_bc4[0x1e3] = 0;
  local_bc4[0x1e4] = 0xba;
  local_bc4[0x1e5] = 0;
  local_bc4[0x1e6] = 0;
  local_bc4[0x1e7] = 0;
  local_bc4[0x1e8] = 0x72;
  local_bc4[0x1e9] = 0;
  local_bc4[0x1ea] = 0;
  local_bc4[0x1eb] = 0;
  local_bc4[0x1ec] = 0x92;
  local_bc4[0x1ed] = 1;
  local_bc4[0x1ee] = 0;
  local_bc4[0x1ef] = 0;
  local_bc4[0x1f0] = 0x1b;
  local_bc4[0x1f1] = 1;
  local_bc4[0x1f2] = 0;
  local_bc4[499] = 0;
  local_bc4[500] = 0;
  local_bc4[0x1f5] = 0;
  local_bc4[0x1f6] = 0;
  local_bc4[0x1f7] = 0;
  local_bc4[0x1f8] = 0;
  local_bc4[0x1f9] = 0x1b;
  local_bc4[0x1fc] = 0xad;
  local_bc4[0x1fd] = 1;
  local_bc4[0x1fe] = 0;
  local_bc4[0x1ff] = 0;
  local_bc4[0x200] = 0xbb;
  local_bc4[0x201] = 0;
  local_bc4[0x202] = 0;
  local_bc4[0x203] = 0;
  local_bc4[0x204] = 0x72;
  local_bc4[0x205] = 0;
  local_bc4[0x206] = 0;
  local_bc4[0x207] = 0;
  local_bc4[0x208] = 0x91;
  local_bc4[0x209] = 1;
  local_bc4[0x20a] = 0;
  local_bc4[0x20b] = 0;
  local_bc4[0x20c] = 0x1b;
  local_bc4[0x20d] = 1;
  local_bc4[0x20e] = 0;
  local_bc4[0x20f] = 0;
  local_bc4[0x210] = 0;
  local_bc4[0x211] = 0;
  local_bc4[0x212] = 0;
  local_bc4[0x213] = 0;
  local_bc4[0x214] = 0;
  local_bc4[0x215] = 0x1c;
  local_bc4[0x218] = 0xae;
  local_bc4[0x219] = 1;
  local_bc4[0x21a] = 0;
  local_bc4[0x21b] = 0;
  local_bc4[0x21c] = 0xbb;
  local_bc4[0x21d] = 0;
  local_bc4[0x21e] = 0;
  local_bc4[0x21f] = 0;
  local_bc4[0x220] = 0x72;
  local_bc4[0x221] = 0;
  local_bc4[0x222] = 0;
  local_bc4[0x223] = 0;
  local_bc4[0x224] = 0x91;
  local_bc4[0x225] = 1;
  local_bc4[0x226] = 0;
  local_bc4[0x227] = 0;
  local_bc4[0x228] = 0x1b;
  local_bc4[0x229] = 1;
  local_bc4[0x22a] = 0;
  local_bc4[0x22b] = 0;
  local_bc4[0x22c] = 0;
  local_bc4[0x22d] = 0;
  local_bc4[0x22e] = 0;
  local_bc4[0x22f] = 0;
  local_bc4[0x230] = 0;
  local_bc4[0x231] = 0x1e;
  local_bc4[0x234] = 0xb1;
  local_bc4[0x235] = 1;
  local_bc4[0x236] = 0;
  local_bc4[0x237] = 0;
  local_bc4[0x238] = 0xbb;
  local_bc4[0x239] = 0;
  local_bc4[0x23a] = 0;
  local_bc4[0x23b] = 0;
  local_bc4[0x23c] = 0x72;
  local_bc4[0x23d] = 0;
  local_bc4[0x23e] = 0;
  local_bc4[0x23f] = 0;
  local_bc4[0x240] = 0x91;
  local_bc4[0x241] = 1;
  local_bc4[0x242] = 0;
  local_bc4[0x243] = 0;
  local_bc4[0x244] = 0x1b;
  local_bc4[0x245] = 1;
  local_bc4[0x246] = 0;
  local_bc4[0x247] = 0;
  local_bc4[0x248] = 0;
  local_bc4[0x249] = 0;
  local_bc4[0x24a] = 0;
  local_bc4[0x24b] = 0;
  local_bc4[0x24c] = 0;
  local_bc4[0x24d] = 0x20;
  local_bc4[0x250] = 0xb4;
  local_bc4[0x251] = 1;
  local_bc4[0x252] = 0;
  local_bc4[0x253] = 0;
  local_bc4[0x254] = 0xbb;
  local_bc4[0x255] = 0;
  local_bc4[0x256] = 0;
  local_bc4[599] = 0;
  local_bc4[600] = 0x72;
  local_bc4[0x259] = 0;
  local_bc4[0x25a] = 0;
  local_bc4[0x25b] = 0;
  local_bc4[0x25c] = 0x91;
  local_bc4[0x25d] = 1;
  local_bc4[0x25e] = 0;
  local_bc4[0x25f] = 0;
  local_bc4[0x260] = 0x1b;
  local_bc4[0x261] = 1;
  local_bc4[0x262] = 0;
  local_bc4[0x263] = 0;
  local_bc4[0x264] = 0;
  local_bc4[0x265] = 0;
  local_bc4[0x266] = 0;
  local_bc4[0x267] = 0;
  local_bc4[0x268] = 0;
  local_bc4[0x269] = 0x24;
  local_bc4[0x26c] = 0xb7;
  local_bc4[0x26d] = 1;
  local_bc4[0x26e] = 0;
  local_bc4[0x26f] = 0;
  local_bc4[0x270] = 0xbb;
  local_bc4[0x271] = 0;
  local_bc4[0x272] = 0;
  local_bc4[0x273] = 0;
  local_bc4[0x274] = 0x72;
  local_bc4[0x275] = 0;
  local_bc4[0x276] = 0;
  local_bc4[0x277] = 0;
  local_bc4[0x278] = 0x91;
  local_bc4[0x279] = 1;
  local_bc4[0x27a] = 0;
  local_bc4[0x27b] = 0;
  local_bc4[0x27c] = 0x1b;
  local_bc4[0x27d] = 1;
  local_bc4[0x27e] = 0;
  local_bc4[0x27f] = 0;
  local_bc4[0x280] = 0;
  local_bc4[0x281] = 0;
  local_bc4[0x282] = 0;
  local_bc4[0x283] = 0;
  local_bc4[0x284] = 0;
  local_bc4[0x285] = 0x26;
  local_bc4[0x288] = 0xb8;
  local_bc4[0x289] = 1;
  local_bc4[0x28a] = 0;
  local_bc4[0x28b] = 0;
  local_bc4[0x28c] = 0xba;
  local_bc4[0x28d] = 0;
  local_bc4[0x28e] = 0;
  local_bc4[0x28f] = 0;
  local_bc4[0x290] = 0x72;
  local_bc4[0x291] = 0;
  local_bc4[0x292] = 0;
  local_bc4[0x293] = 0;
  local_bc4[0x294] = 0x92;
  local_bc4[0x295] = 1;
  local_bc4[0x296] = 0;
  local_bc4[0x297] = 0;
  local_bc4[0x298] = 0x1b;
  local_bc4[0x299] = 1;
  local_bc4[0x29a] = 0;
  local_bc4[0x29b] = 0;
  local_bc4[0x29c] = 0;
  local_bc4[0x29d] = 0;
  local_bc4[0x29e] = 0;
  local_bc4[0x29f] = 0;
  local_bc4[0x2a0] = 1;
  local_bc4[0x2a1] = 6;
  local_920 = 0x1c1;
  local_91c = 0x1ba;
  local_918 = 0x75;
  local_914 = 0x21;
  local_910 = 0x2b;
  local_90c = 0x1ce;
  local_908 = 5;
  local_907 = 4;
  local_904 = 0x1f0;
  local_900 = 0x18e;
  local_8fc = 0xa5;
  local_8f8 = 0x30;
  local_8f4 = 0x16;
  local_8f0 = 400;
  local_8ec = 3;
  local_8eb = 3;
  local_8e8 = 0x1d9;
  local_8e4 = 0x17d;
  local_8e0 = 0xa4;
  local_8dc = 0x3e;
  local_8d8 = 0x35;
  local_8d4 = 0xd2;
  local_8d0 = 4;
  local_8cf = 4;
  local_8cc = 0x1e7;
  local_8c8 = 0x1c5;
  local_8c4 = 0xa9;
  local_8c0 = 0x30;
  local_8bc = 0x24;
  local_8b8 = 0x168;
  local_8b4 = 4;
  local_8b3 = 3;
  local_8b0 = 0x1e5;
  local_8ac = 0x1e0;
  local_8a8 = 0xbd;
  local_8a4 = 0x32;
  local_8a0 = 0x24;
  local_89c = 0x103;
  local_898 = 5;
  local_897 = 4;
  local_894 = 0x1f1;
  local_890 = 0x1ad;
  local_88c = 0xb4;
  local_888 = 0x47;
  local_884 = 0x26;
  local_880 = 0x1c1;
  local_87c = 4;
  local_87b = 1;
  local_878 = 0x1e1;
  local_874 = 0x1fc;
  local_870 = 0xd2;
  local_86c = 0x2b;
  local_868 = 0x20;
  local_864 = 0x30;
  local_860 = 4;
  local_85f = 2;
  local_85c = 0x1e3;
  local_858 = 0x211;
  local_854 = 0xe1;
  local_850 = 0x37;
  local_84c = 0x2a;
  local_848 = 0x96;
  local_844 = 5;
  local_843 = 2;
  local_840 = 0x1ec;
  local_83c = 0x1af;
  local_838 = 199;
  local_834 = 0x4a;
  local_830 = 0x24;
  local_82c = 0x97;
  local_828 = 3;
  local_827 = 2;
  local_824 = 0x1d7;
  local_820 = 0x1af;
  local_81c = 0xce;
  local_818 = 0x45;
  local_814 = 0x3a;
  local_810 = 0x4a;
  local_80c = 5;
  local_80b = 2;
  local_808 = 0x1ed;
  local_804 = 0x1ca;
  local_800 = 0xe9;
  local_7fc = 0x50;
  local_7f8 = 0x2f;
  local_7f4 = 0xe2;
  local_7f0 = 1;
  local_7ef = 6;
  local_7ec = 0x1c0;
  local_7e8 = 0xb2;
  local_7e4 = 200;
  local_7e0 = 0x3e;
  local_7dc = 0x28;
  local_7d8 = 399;
  local_7d4 = 5;
  local_7d3 = 3;
  local_7d0 = 0x1ee;
  local_7cc = 300;
  local_7c8 = 0xc5;
  local_7c4 = 0x12;
  local_7c0 = 0x18;
  local_7bc = 0x133;
  local_7b8 = 3;
  local_7b7 = 4;
  local_7b4 = 0x1d8;
  local_7b0 = 0x136;
  local_7ac = 0xbc;
  local_7a8 = 0x41;
  local_7a4 = 0x38;
  local_7a0 = 0x90;
  local_79c = 5;
  local_79b = 1;
  local_798 = 0x1ea;
  local_794 = 0x153;
  local_790 = 0xe8;
  local_78c = 0x25;
  local_788 = 0x29;
  local_784 = 1;
  local_780 = 5;
  local_77f = 3;
  local_77c = 0x1ef;
  local_778 = 300;
  local_774 = 0xd9;
  local_770 = 0x49;
  local_76c = 0x3c;
  local_768 = 0x146;
  local_764 = 3;
  local_763 = 1;
  local_760 = 0x1d6;
  local_75c = 0x164;
  local_758 = 0xe9;
  local_754 = 0x48;
  local_750 = 0x40;
  local_74c = 1;
  local_748 = 5;
  local_747 = 1;
  local_744 = 0x1eb;
  local_740 = 0x15e;
  local_73c = 0xfb;
  local_738 = 0x6f;
  local_734 = 0x45;
  local_730 = 0x27;
  local_72c = 4;
  local_72b = 4;
  local_728 = 0x1e6;
  local_724 = 0x109;
  local_720 = 0xed;
  local_71c = 0x31;
  local_718 = 0x2c;
  local_714 = 0x136;
  local_710 = 4;
  local_70f = 3;
  local_70c = 0x1e4;
  local_708 = 0x11f;
  local_704 = 0x107;
  local_700 = 0x34;
  local_6fc = 0x2e;
  local_6f8 = 0xce;
  local_6f4 = 4;
  local_6f3 = 1;
  local_6f0 = 0x1e0;
  local_6ec = 0x137;
  local_6e8 = 0x122;
  local_6e4 = 0x2e;
  local_6e0 = 0x28;
  local_6dc = 1;
  local_6d8 = 4;
  local_6d7 = 2;
  local_6d4 = 0x1e2;
  local_6d0 = 0x148;
  local_6cc = 0x136;
  local_6c8 = 0x39;
  local_6c4 = 0x35;
  local_6c0 = 0x5c;
  local_6bc = 2;
  local_6bb = 8;
  local_6b8 = 0x1d4;
  local_6b4 = 0x20e;
  local_6b0 = 0xf6;
  local_6ac = 0x51;
  local_6a8 = 0x36;
  local_6a4 = 0x334;
  local_6a0 = 0;
  local_69f = 0x21;
  local_69c = 0x1b6;
  local_698 = 0x24b;
  local_694 = 0x114;
  local_690 = 0x15;
  local_68c = 0x19;
  local_688 = 0x2d1;
  local_684 = 1;
  local_683 = 8;
  local_680 = 0x1c5;
  local_67c = 0x246;
  local_678 = 0x111;
  local_674 = 0x2f;
  local_670 = 0x2b;
  local_66c = 0x285;
  local_668 = 0;
  local_667 = 0x1f;
  local_664 = 0x1b3;
  local_660 = 0x210;
  local_65c = 0xfd;
  local_658 = 0x30;
  local_654 = 0x26;
  local_650 = 0x282;
  local_64c = 2;
  local_64b = 7;
  local_648 = 0x1d2;
  local_644 = 0x1f7;
  local_640 = 0x102;
  local_63c = 0x4d;
  local_638 = 0x3a;
  local_634 = 0x2ab;
  local_630 = 0;
  local_62f = 0x1d;
  local_62c = 0x1b0;
  local_628 = 0x22d;
  local_624 = 0x123;
  local_620 = 0x19;
  local_61c = 0x19;
  local_618 = 0x243;
  local_614 = 1;
  local_613 = 7;
  local_610 = 0x1c3;
  local_60c = 0x228;
  local_608 = 0x11d;
  local_604 = 0x2f;
  local_600 = 0x2e;
  local_5fc = 0x222;
  local_5f8 = 2;
  local_5f7 = 5;
  local_5f4 = 0x1ce;
  local_5f0 = 0x1f1;
  local_5ec = 0xfd;
  local_5e8 = 0x4e;
  local_5e4 = 0x39;
  local_5e0 = 0x1b5;
  local_5dc = 0;
  local_5db = 0x15;
  local_5d8 = 0x1a7;
  local_5d4 = 0x228;
  local_5d0 = 0x11d;
  local_5cc = 0x18;
  local_5c8 = 0x1a;
  local_5c4 = 0x20c;
  local_5c0 = 1;
  local_5bf = 5;
  local_5bc = 0x1bf;
  local_5b8 = 0x224;
  local_5b4 = 0x118;
  local_5b0 = 0x31;
  local_5ac = 0x2e;
  local_5a8 = 0x15d;
  local_5a4 = 0;
  local_5a3 = 0x13;
  local_5a0 = 0x1a4;
  local_59c = 0x1f0;
  local_598 = 0x107;
  local_594 = 0x34;
  local_590 = 0x35;
  local_58c = 0x1b9;
  local_588 = 2;
  local_587 = 1;
  local_584 = 0x1c8;
  local_580 = 0x1da;
  local_57c = 0x10b;
  local_578 = 0x4b;
  local_574 = 0x41;
  local_570 = 0x46;
  local_56c = 0;
  local_56b = 0xb;
  local_568 = 0x19b;
  local_564 = 0x1cf;
  local_560 = 0x108;
  local_55c = 0x42;
  local_558 = 0x3d;
  local_554 = 0xc2;
  local_550 = 2;
  local_54f = 3;
  local_54c = 0x1cb;
  local_548 = 0x1ce;
  local_544 = 0x109;
  local_540 = 0x4d;
  local_53c = 0x40;
  local_538 = 0xd3;
  local_534 = 2;
  local_533 = 1;
  local_530 = 0x1c7;
  local_52c = 0x1bc;
  local_528 = 0x11b;
  local_524 = 0x44;
  local_520 = 0x44;
  local_51c = 1;
  local_518 = 0;
  local_517 = 5;
  local_514 = 0x195;
  local_510 = 0x1e4;
  local_50c = 0x12f;
  local_508 = 0x42;
  local_504 = 0x31;
  local_500 = 1;
  local_4fc = 0;
  local_4fb = 0xd;
  local_4f8 = 0x19d;
  local_4f4 = 0x1fb;
  local_4f0 = 299;
  local_4ec = 0x20;
  local_4e8 = 0x1f;
  local_4e4 = 0x105;
  local_4e0 = 1;
  local_4df = 1;
  local_4dc = 0x1ba;
  local_4d8 = 0x204;
  local_4d4 = 0x129;
  local_4d0 = 0x2f;
  local_4cc = 0x33;
  local_4c8 = 0x39;
  local_4c4 = 1;
  local_4c3 = 3;
  local_4c0 = 0x1bc;
  local_4bc = 0x1f9;
  local_4b8 = 0x125;
  local_4b4 = 0x37;
  local_4b0 = 0x35;
  local_4ac = 0xb7;
  local_4a8 = 1;
  local_4a7 = 1;
  local_4a4 = 0x1b9;
  local_4a0 = 0x1df;
  local_49c = 0x13e;
  local_498 = 0x33;
  local_494 = 0x34;
  local_490 = 1;
  local_48c = 0;
  local_48b = 0x13;
  local_488 = 0x1a3;
  local_484 = 0x1be;
  local_480 = 0x11f;
  local_47c = 0x2c;
  local_478 = 0x40;
  local_474 = 0x18c;
  local_470 = 2;
  local_46f = 5;
  local_46c = 0x1cd;
  local_468 = 0x1ac;
  local_464 = 0x117;
  local_460 = 0x42;
  local_45c = 0x46;
  local_458 = 0x172;
  local_454 = 0;
  local_453 = 0x15;
  local_450 = 0x1a6;
  local_44c = 0x1d1;
  local_448 = 0x142;
  local_444 = 0x1d;
  local_440 = 0x1d;
  local_43c = 0x1ee;
  local_438 = 1;
  local_437 = 5;
  local_434 = 0x1be;
  local_430 = 0x1cd;
  local_42c = 0x13c;
  local_428 = 0x34;
  local_424 = 0x33;
  local_420 = 0x128;
  local_41c = 2;
  local_41b = 7;
  local_418 = 0x1d1;
  local_414 = 0x19d;
  local_410 = 300;
  local_40c = 0x3c;
  local_408 = 0x4b;
  local_404 = 0x26e;
  local_400 = 0;
  local_3ff = 0x1f;
  local_3fc = 0x1b2;
  local_3f8 = 0x19e;
  local_3f4 = 299;
  local_3f0 = 0x24;
  local_3ec = 0x41;
  local_3e8 = 0x25d;
  local_3e4 = 0;
  local_3e3 = 0x1d;
  local_3e0 = 0x1af;
  local_3dc = 0x1bd;
  local_3d8 = 0x15c;
  local_3d4 = 0x1d;
  local_3d0 = 0x1d;
  local_3cc = 0x225;
  local_3c8 = 1;
  local_3c7 = 7;
  local_3c4 = 0x1c2;
  local_3c0 = 0x1b9;
  local_3bc = 0x157;
  local_3b8 = 0x31;
  local_3b4 = 0x34;
  local_3b0 = 0x1f0;
  local_3ac = 2;
  local_3ab = 8;
  local_3a8 = 0x1d3;
  local_3a4 = 0x188;
  local_3a0 = 0x129;
  local_39c = 0x3a;
  local_398 = 0x4e;
  local_394 = 0x2f9;
  local_390 = 0;
  local_38f = 0x21;
  local_38c = 0x1b5;
  local_388 = 0x1a5;
  local_384 = 0x15c;
  local_380 = 0x1c;
  local_37c = 0x1e;
  local_378 = 0x2b3;
  local_374 = 1;
  local_373 = 8;
  local_370 = 0x1c4;
  local_36c = 0x1a0;
  local_368 = 0x156;
  local_364 = 0x32;
  local_360 = 0x35;
  local_35c = 0x252;
  local_358 = 0;
  local_357 = 0xf;
  local_354 = 0x19f;
  local_350 = 0x1d1;
  local_34c = 0x107;
  local_348 = 0x43;
  local_344 = 0x2a;
  local_340 = 0x126;
  local_33c = 2;
  local_33b = 4;
  local_338 = 0x1cc;
  local_334 = 0x1cf;
  local_330 = 0x101;
  local_32c = 0x50;
  local_328 = 0x32;
  local_324 = 0x121;
  local_320 = 0;
  local_31f = 0x11;
  local_31c = 0x1a1;
  local_318 = 0x201;
  local_314 = 0x11a;
  local_310 = 0x21;
  local_30c = 0x1a;
  local_308 = 0x16a;
  local_304 = 1;
  local_303 = 4;
  local_300 = 0x1bd;
  local_2fc = 0x1fb;
  local_2f8 = 0x116;
  local_2f4 = 0x38;
  local_2f0 = 0x2d;
  local_2ec = 0xef;
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
    local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
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
      local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
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
        local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
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
          local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
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
            local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
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
              local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
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
                local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
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
                  local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
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
                    local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
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
                      local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
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
                        local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
                        /* inlined unwind funclet 004d4a4a */ { surface_dtor((void *)((iptr)&local_29c)); }
                        local_8 = 0xffffffff;
                        /* inlined unwind funclet 004d4a56 */ { surface_dtor((void *)((iptr)&local_2e8)); }
                        local_d1c = local_d44;
                      }
                      else {
                        win_flush_pending_msgs();
                        for (local_2a0 = 0; local_2a0 < 7; local_2a0 = local_2a0 + 1) {
                          win_flush_pending_msgs();
                          if ((int)(uint)local_c88[local_2a0 * 0x1c + 1] <=
                              *(int *)(&spaceship_wnd_part_counts + (uint)local_c88[local_2a0 * 0x1c] * 4)) {
                            if (local_c88[local_2a0 * 0x1c] == 1) {
                              bVar1 = local_c88[local_2a0 * 0x1c + 1];
                              iVar2 = spaceship_part_count(*(i32 *)((iptr)this + 0x1cc),1);
                              if (iVar2 < (int)(uint)bVar1) {
                                sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_178,9,
                                             local_c84[local_2a0 * 7 + 5],1,
                                             local_c84[local_2a0 * 7 + 3],
                                             local_c84[local_2a0 * 7 + 4]);
                              }
                              else {
                                sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_29c,9,
                                             local_c84[local_2a0 * 7 + 5],1,
                                             local_c84[local_2a0 * 7 + 3],
                                             local_c84[local_2a0 * 7 + 4]);
                              }
                            }
                            else if (local_c88[local_2a0 * 0x1c] == 4) {
                              bVar1 = local_c88[local_2a0 * 0x1c + 1];
                              iVar2 = spaceship_part_count(*(i32 *)((iptr)this + 0x1cc),4);
                              if (iVar2 < (int)(uint)bVar1) {
                                sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_20c,9,
                                             local_c84[local_2a0 * 7 + 5],1,
                                             local_c84[local_2a0 * 7 + 3],
                                             local_c84[local_2a0 * 7 + 4]);
                              }
                              else {
                                sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_1c4,9,
                                             local_c84[local_2a0 * 7 + 5],1,
                                             local_c84[local_2a0 * 7 + 3],
                                             local_c84[local_2a0 * 7 + 4]);
                              }
                            }
                            else if (local_c88[local_2a0 * 0x1c] == 2) {
                              bVar1 = local_c88[local_2a0 * 0x1c + 1];
                              iVar2 = spaceship_part_count(*(i32 *)((iptr)this + 0x1cc),2);
                              if (iVar2 < (int)(uint)bVar1) {
                                sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_254,9,
                                             local_c84[local_2a0 * 7 + 5],1,
                                             local_c84[local_2a0 * 7 + 3],
                                             local_c84[local_2a0 * 7 + 4]);
                              }
                              else {
                                sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_58,9,
                                             local_c84[local_2a0 * 7 + 5],1,
                                             local_c84[local_2a0 * 7 + 3],
                                             local_c84[local_2a0 * 7 + 4]);
                              }
                            }
                            else if (local_c88[local_2a0 * 0x1c] == 5) {
                              bVar1 = local_c88[local_2a0 * 0x1c + 1];
                              iVar2 = spaceship_part_count(*(i32 *)((iptr)this + 0x1cc),5);
                              if (iVar2 < (int)(uint)bVar1) {
                                sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_e8,9,
                                             local_c84[local_2a0 * 7 + 5],1,
                                             local_c84[local_2a0 * 7 + 3],
                                             local_c84[local_2a0 * 7 + 4]);
                              }
                              else {
                                sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_d18,9,
                                             local_c84[local_2a0 * 7 + 5],1,
                                             local_c84[local_2a0 * 7 + 3],
                                             local_c84[local_2a0 * 7 + 4]);
                              }
                            }
                            else if (local_c88[local_2a0 * 0x1c] == 3) {
                              bVar1 = local_c88[local_2a0 * 0x1c + 1];
                              iVar2 = spaceship_part_count(*(i32 *)((iptr)this + 0x1cc),3);
                              if (iVar2 < (int)(uint)bVar1) {
                                sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_a0,9,
                                             local_c84[local_2a0 * 7 + 5],1,
                                             local_c84[local_2a0 * 7 + 3],
                                             local_c84[local_2a0 * 7 + 4]);
                              }
                              else {
                                sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_cd0,9,
                                             local_c84[local_2a0 * 7 + 5],1,
                                             local_c84[local_2a0 * 7 + 3],
                                             local_c84[local_2a0 * 7 + 4]);
                              }
                            }
                            else {
                              sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_130,9,
                                           local_c84[local_2a0 * 7 + 5],1,
                                           local_c84[local_2a0 * 7 + 3],local_c84[local_2a0 * 7 + 4]
                                          );
                            }
                            sprite_draw((void *)((iptr)this + 0x93c),local_d54,(iptr)this + 0x8f4,
                                         local_c84[local_2a0 * 7 + 1] + -0xaf,
                                         local_c84[local_2a0 * 7 + 2] + -99);
                          }
                        }
                        local_17c = 0;
                        for (local_2a0 = 7; local_2a0 < 0x1f; local_2a0 = local_2a0 + 1) {
                          if ((int)(uint)local_c88[local_2a0 * 0x1c + 1] <=
                              *(int *)(&spaceship_wnd_part_counts + (uint)local_c88[local_2a0 * 0x1c] * 4)) {
                            local_17c = local_2a0;
                          }
                        }
                        win_flush_pending_msgs();
                        iVar2 = surface_load_gif_resource(local_2e8,local_c84[local_17c * 7],10,0xec,
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
                          local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
                          /* inlined unwind funclet 004d4a4a */ { surface_dtor((void *)((iptr)&local_29c)); }
                          local_8 = 0xffffffff;
                          /* inlined unwind funclet 004d4a56 */ { surface_dtor((void *)((iptr)&local_2e8)); }
                          local_d1c = local_d58;
                        }
                        else {
                          win_flush_pending_msgs();
                          sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_2e8,9,
                                       local_c84[local_17c * 7 + 1],local_c84[local_17c * 7 + 2],
                                       local_c84[local_17c * 7 + 3],local_c84[local_17c * 7 + 4]);
                          sprite_draw((void *)((iptr)this + 0x93c),local_d68,(iptr)this + 0x8f4,
                                       local_c84[local_17c * 7 + 1] + -0xaf,
                                       local_c84[local_17c * 7 + 2] + -99);
                          for (local_2a0 = 0x1f; local_2a0 < 0x58; local_2a0 = local_2a0 + 1) {
                            win_flush_pending_msgs();
                            win_flush_pending_msgs();
                            if ((int)(uint)local_c88[local_2a0 * 0x1c + 1] <=
                                *(int *)(&spaceship_wnd_part_counts + (uint)local_c88[local_2a0 * 0x1c] * 4)) {
                              if (local_c88[local_2a0 * 0x1c] == 1) {
                                bVar1 = local_c88[local_2a0 * 0x1c + 1];
                                iVar2 = spaceship_part_count(*(i32 *)((iptr)this + 0x1cc),1);
                                if (iVar2 < (int)(uint)bVar1) {
                                  sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_178,9,
                                               local_c84[local_2a0 * 7 + 5],1,
                                               local_c84[local_2a0 * 7 + 3],
                                               local_c84[local_2a0 * 7 + 4]);
                                }
                                else {
                                  sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_29c,9,
                                               local_c84[local_2a0 * 7 + 5],1,
                                               local_c84[local_2a0 * 7 + 3],
                                               local_c84[local_2a0 * 7 + 4]);
                                }
                              }
                              else if (local_c88[local_2a0 * 0x1c] == 4) {
                                bVar1 = local_c88[local_2a0 * 0x1c + 1];
                                iVar2 = spaceship_part_count(*(i32 *)((iptr)this + 0x1cc),4);
                                if (iVar2 < (int)(uint)bVar1) {
                                  sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_20c,9,
                                               local_c84[local_2a0 * 7 + 5],1,
                                               local_c84[local_2a0 * 7 + 3],
                                               local_c84[local_2a0 * 7 + 4]);
                                }
                                else {
                                  sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_1c4,9,
                                               local_c84[local_2a0 * 7 + 5],1,
                                               local_c84[local_2a0 * 7 + 3],
                                               local_c84[local_2a0 * 7 + 4]);
                                }
                              }
                              else if (local_c88[local_2a0 * 0x1c] == 2) {
                                bVar1 = local_c88[local_2a0 * 0x1c + 1];
                                iVar2 = spaceship_part_count(*(i32 *)((iptr)this + 0x1cc),2);
                                if (iVar2 < (int)(uint)bVar1) {
                                  sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_254,9,
                                               local_c84[local_2a0 * 7 + 5],1,
                                               local_c84[local_2a0 * 7 + 3],
                                               local_c84[local_2a0 * 7 + 4]);
                                }
                                else {
                                  sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_58,9,
                                               local_c84[local_2a0 * 7 + 5],1,
                                               local_c84[local_2a0 * 7 + 3],
                                               local_c84[local_2a0 * 7 + 4]);
                                }
                              }
                              else if (local_c88[local_2a0 * 0x1c] == 5) {
                                bVar1 = local_c88[local_2a0 * 0x1c + 1];
                                iVar2 = spaceship_part_count(*(i32 *)((iptr)this + 0x1cc),5);
                                if (iVar2 < (int)(uint)bVar1) {
                                  sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_e8,9,
                                               local_c84[local_2a0 * 7 + 5],1,
                                               local_c84[local_2a0 * 7 + 3],
                                               local_c84[local_2a0 * 7 + 4]);
                                }
                                else {
                                  sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_d18,9,
                                               local_c84[local_2a0 * 7 + 5],1,
                                               local_c84[local_2a0 * 7 + 3],
                                               local_c84[local_2a0 * 7 + 4]);
                                }
                              }
                              else if (local_c88[local_2a0 * 0x1c] == 3) {
                                bVar1 = local_c88[local_2a0 * 0x1c + 1];
                                iVar2 = spaceship_part_count(*(i32 *)((iptr)this + 0x1cc),3);
                                if (iVar2 < (int)(uint)bVar1) {
                                  sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_a0,9,
                                               local_c84[local_2a0 * 7 + 5],1,
                                               local_c84[local_2a0 * 7 + 3],
                                               local_c84[local_2a0 * 7 + 4]);
                                }
                                else {
                                  sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_cd0,9,
                                               local_c84[local_2a0 * 7 + 5],1,
                                               local_c84[local_2a0 * 7 + 3],
                                               local_c84[local_2a0 * 7 + 4]);
                                }
                              }
                              else {
                                sprite_grab_from_surface((void *)((iptr)this + 0x93c),local_130,9,
                                             local_c84[local_2a0 * 7 + 5],1,
                                             local_c84[local_2a0 * 7 + 3],
                                             local_c84[local_2a0 * 7 + 4]);
                              }
                              sprite_draw((void *)((iptr)this + 0x93c),local_d78,(iptr)this + 0x8f4,
                                           local_c84[local_2a0 * 7 + 1] + -0xaf,
                                           local_c84[local_2a0 * 7 + 2] + -99);
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
                          local_8 = (uint)(*(i32 *)((char *)&local_8 + 1)) << 8;
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
#undef local_d88
#undef local_d78
#undef local_d68
#undef local_d58
#undef local_d54
#undef local_d44
#undef local_d40
#undef local_d3c
#undef local_d38
#undef local_d34
#undef local_d30
#undef local_d2c
#undef local_d28
#undef local_d24
#undef local_d20
#undef local_d1c
#undef local_d18
#undef local_cd0
#undef local_c88
#undef local_c84
#undef local_c6c
#undef local_c6b
#undef local_c68
#undef local_c64
#undef local_c60
#undef local_c5c
#undef local_c58
#undef local_c54
#undef local_c50
#undef local_c4f
#undef local_c4c
#undef local_c48
#undef local_c44
#undef local_c40
#undef local_c3c
#undef local_c38
#undef local_c34
#undef local_c33
#undef local_c30
#undef local_c2c
#undef local_c28
#undef local_c24
#undef local_c20
#undef local_c1c
#undef local_c18
#undef local_c17
#undef local_c14
#undef local_c10
#undef local_c0c
#undef local_c08
#undef local_c04
#undef local_c00
#undef local_bfc
#undef local_bfb
#undef local_bf8
#undef local_bf4
#undef local_bf0
#undef local_bec
#undef local_be8
#undef local_be4
#undef local_be0
#undef local_bdf
#undef local_bdc
#undef local_bd8
#undef local_bd4
#undef local_bd0
#undef local_bcc
#undef local_bc8
#undef local_bc4
#undef local_920
#undef local_91c
#undef local_918
#undef local_914
#undef local_910
#undef local_90c
#undef local_908
#undef local_907
#undef local_904
#undef local_900
#undef local_8fc
#undef local_8f8
#undef local_8f4
#undef local_8f0
#undef local_8ec
#undef local_8eb
#undef local_8e8
#undef local_8e4
#undef local_8e0
#undef local_8dc
#undef local_8d8
#undef local_8d4
#undef local_8d0
#undef local_8cf
#undef local_8cc
#undef local_8c8
#undef local_8c4
#undef local_8c0
#undef local_8bc
#undef local_8b8
#undef local_8b4
#undef local_8b3
#undef local_8b0
#undef local_8ac
#undef local_8a8
#undef local_8a4
#undef local_8a0
#undef local_89c
#undef local_898
#undef local_897
#undef local_894
#undef local_890
#undef local_88c
#undef local_888
#undef local_884
#undef local_880
#undef local_87c
#undef local_87b
#undef local_878
#undef local_874
#undef local_870
#undef local_86c
#undef local_868
#undef local_864
#undef local_860
#undef local_85f
#undef local_85c
#undef local_858
#undef local_854
#undef local_850
#undef local_84c
#undef local_848
#undef local_844
#undef local_843
#undef local_840
#undef local_83c
#undef local_838
#undef local_834
#undef local_830
#undef local_82c
#undef local_828
#undef local_827
#undef local_824
#undef local_820
#undef local_81c
#undef local_818
#undef local_814
#undef local_810
#undef local_80c
#undef local_80b
#undef local_808
#undef local_804
#undef local_800
#undef local_7fc
#undef local_7f8
#undef local_7f4
#undef local_7f0
#undef local_7ef
#undef local_7ec
#undef local_7e8
#undef local_7e4
#undef local_7e0
#undef local_7dc
#undef local_7d8
#undef local_7d4
#undef local_7d3
#undef local_7d0
#undef local_7cc
#undef local_7c8
#undef local_7c4
#undef local_7c0
#undef local_7bc
#undef local_7b8
#undef local_7b7
#undef local_7b4
#undef local_7b0
#undef local_7ac
#undef local_7a8
#undef local_7a4
#undef local_7a0
#undef local_79c
#undef local_79b
#undef local_798
#undef local_794
#undef local_790
#undef local_78c
#undef local_788
#undef local_784
#undef local_780
#undef local_77f
#undef local_77c
#undef local_778
#undef local_774
#undef local_770
#undef local_76c
#undef local_768
#undef local_764
#undef local_763
#undef local_760
#undef local_75c
#undef local_758
#undef local_754
#undef local_750
#undef local_74c
#undef local_748
#undef local_747
#undef local_744
#undef local_740
#undef local_73c
#undef local_738
#undef local_734
#undef local_730
#undef local_72c
#undef local_72b
#undef local_728
#undef local_724
#undef local_720
#undef local_71c
#undef local_718
#undef local_714
#undef local_710
#undef local_70f
#undef local_70c
#undef local_708
#undef local_704
#undef local_700
#undef local_6fc
#undef local_6f8
#undef local_6f4
#undef local_6f3
#undef local_6f0
#undef local_6ec
#undef local_6e8
#undef local_6e4
#undef local_6e0
#undef local_6dc
#undef local_6d8
#undef local_6d7
#undef local_6d4
#undef local_6d0
#undef local_6cc
#undef local_6c8
#undef local_6c4
#undef local_6c0
#undef local_6bc
#undef local_6bb
#undef local_6b8
#undef local_6b4
#undef local_6b0
#undef local_6ac
#undef local_6a8
#undef local_6a4
#undef local_6a0
#undef local_69f
#undef local_69c
#undef local_698
#undef local_694
#undef local_690
#undef local_68c
#undef local_688
#undef local_684
#undef local_683
#undef local_680
#undef local_67c
#undef local_678
#undef local_674
#undef local_670
#undef local_66c
#undef local_668
#undef local_667
#undef local_664
#undef local_660
#undef local_65c
#undef local_658
#undef local_654
#undef local_650
#undef local_64c
#undef local_64b
#undef local_648
#undef local_644
#undef local_640
#undef local_63c
#undef local_638
#undef local_634
#undef local_630
#undef local_62f
#undef local_62c
#undef local_628
#undef local_624
#undef local_620
#undef local_61c
#undef local_618
#undef local_614
#undef local_613
#undef local_610
#undef local_60c
#undef local_608
#undef local_604
#undef local_600
#undef local_5fc
#undef local_5f8
#undef local_5f7
#undef local_5f4
#undef local_5f0
#undef local_5ec
#undef local_5e8
#undef local_5e4
#undef local_5e0
#undef local_5dc
#undef local_5db
#undef local_5d8
#undef local_5d4
#undef local_5d0
#undef local_5cc
#undef local_5c8
#undef local_5c4
#undef local_5c0
#undef local_5bf
#undef local_5bc
#undef local_5b8
#undef local_5b4
#undef local_5b0
#undef local_5ac
#undef local_5a8
#undef local_5a4
#undef local_5a3
#undef local_5a0
#undef local_59c
#undef local_598
#undef local_594
#undef local_590
#undef local_58c
#undef local_588
#undef local_587
#undef local_584
#undef local_580
#undef local_57c
#undef local_578
#undef local_574
#undef local_570
#undef local_56c
#undef local_56b
#undef local_568
#undef local_564
#undef local_560
#undef local_55c
#undef local_558
#undef local_554
#undef local_550
#undef local_54f
#undef local_54c
#undef local_548
#undef local_544
#undef local_540
#undef local_53c
#undef local_538
#undef local_534
#undef local_533
#undef local_530
#undef local_52c
#undef local_528
#undef local_524
#undef local_520
#undef local_51c
#undef local_518
#undef local_517
#undef local_514
#undef local_510
#undef local_50c
#undef local_508
#undef local_504
#undef local_500
#undef local_4fc
#undef local_4fb
#undef local_4f8
#undef local_4f4
#undef local_4f0
#undef local_4ec
#undef local_4e8
#undef local_4e4
#undef local_4e0
#undef local_4df
#undef local_4dc
#undef local_4d8
#undef local_4d4
#undef local_4d0
#undef local_4cc
#undef local_4c8
#undef local_4c4
#undef local_4c3
#undef local_4c0
#undef local_4bc
#undef local_4b8
#undef local_4b4
#undef local_4b0
#undef local_4ac
#undef local_4a8
#undef local_4a7
#undef local_4a4
#undef local_4a0
#undef local_49c
#undef local_498
#undef local_494
#undef local_490
#undef local_48c
#undef local_48b
#undef local_488
#undef local_484
#undef local_480
#undef local_47c
#undef local_478
#undef local_474
#undef local_470
#undef local_46f
#undef local_46c
#undef local_468
#undef local_464
#undef local_460
#undef local_45c
#undef local_458
#undef local_454
#undef local_453
#undef local_450
#undef local_44c
#undef local_448
#undef local_444
#undef local_440
#undef local_43c
#undef local_438
#undef local_437
#undef local_434
#undef local_430
#undef local_42c
#undef local_428
#undef local_424
#undef local_420
#undef local_41c
#undef local_41b
#undef local_418
#undef local_414
#undef local_410
#undef local_40c
#undef local_408
#undef local_404
#undef local_400
#undef local_3ff
#undef local_3fc
#undef local_3f8
#undef local_3f4
#undef local_3f0
#undef local_3ec
#undef local_3e8
#undef local_3e4
#undef local_3e3
#undef local_3e0
#undef local_3dc
#undef local_3d8
#undef local_3d4
#undef local_3d0
#undef local_3cc
#undef local_3c8
#undef local_3c7
#undef local_3c4
#undef local_3c0
#undef local_3bc
#undef local_3b8
#undef local_3b4
#undef local_3b0
#undef local_3ac
#undef local_3ab
#undef local_3a8
#undef local_3a4
#undef local_3a0
#undef local_39c
#undef local_398
#undef local_394
#undef local_390
#undef local_38f
#undef local_38c
#undef local_388
#undef local_384
#undef local_380
#undef local_37c
#undef local_378
#undef local_374
#undef local_373
#undef local_370
#undef local_36c
#undef local_368
#undef local_364
#undef local_360
#undef local_35c
#undef local_358
#undef local_357
#undef local_354
#undef local_350
#undef local_34c
#undef local_348
#undef local_344
#undef local_340
#undef local_33c
#undef local_33b
#undef local_338
#undef local_334
#undef local_330
#undef local_32c
#undef local_328
#undef local_324
#undef local_320
#undef local_31f
#undef local_31c
#undef local_318
#undef local_314
#undef local_310
#undef local_30c
#undef local_308
#undef local_304
#undef local_303
#undef local_300
#undef local_2fc
#undef local_2f8
#undef local_2f4
#undef local_2f0
#undef local_2ec
#undef local_2e8
#undef local_2a0
#undef local_29c
#undef local_254
#undef local_20c
#undef local_1c4
#undef local_17c
#undef local_178
#undef local_130
#undef local_e8
#undef local_a0
#undef local_58
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0x005aa0e5: unwind funclet 0x005ab07f destroys the object at EBP-0x320 (local_324). */
#define scenario_events_loaded (*(int *)((u8 *)&g.d_00627670))
#define game_loop_active (*(char *)((u8 *)&g.d_00628044))
#define turn_resume_civ (*(byte *)((u8 *)&g.d_00628048))
#define turn_resume_new_game (*(int *)((u8 *)&g.d_0062c488))
#define dlg_pending_idle_callback (*(i8 * *)((u8 *)&g.d_00635a3c))
#define game_over_reason (*(int *)((u8 *)&g.d_0064b1ac))
#define mp_turn_time_limit_ms (*(int *)((u8 *)&g.d_00654b70))
#define saved_turn_civ (*(i8 *)((u8 *)&g.d_00654fa4))
#define saved_resume_new_game (*(i16 *)((u8 *)&g.d_00654fa6))
#define autoplay_active (*(short *)((u8 *)&g.d_00654fa8))
#define autoplay_turns_left (*(short *)((u8 *)&g.d_00654faa))
#define net_claimed_civs_mask (*(i16 *)((u8 *)&g.d_00654fb0))
#define saved_human_players (*(byte *)((u8 *)&g.d_00673b08))
#define DAT_006ad108 (*(i32 *)((u8 *)&g.d_006ad108))
#define net_local_slot (*(int *)((u8 *)&g.d_006ad304))
#define DAT_006ad308 (*(int *)((u8 *)&g.d_006ad308))
#define net_slot_civs (*(i32 *)((u8 *)&g.d_006ad35c))
#define mp_turn_civ (*(i8 *)((u8 *)&g.d_006ad578))
#define player_has_quit (*(char *)((u8 *)&g.d_006ad685))
#define net_tile_sync_enabled (*(i8 *)((u8 *)&g.d_006ad699))
#define nm_production_complete_count (*(i32 *)((u8 *)&g.d_006c9210))
#define nm_human_move_complete_count (*(i32 *)((u8 *)&g.d_006c921c))
#define DAT_006d1da0 (*(int *)((u8 *)&g.d_006d1da0))
#define main_view_timer_cache_i32 (*(i32 *)((u8 *)&g.d_0066c990))
#define saved_human_players_i32 (*(i32 *)((u8 *)&g.d_00673b08))
#define mp_turn_civ_i32 (*(i32 *)((u8 *)&g.d_006ad578))
#define local_330 (*(int *)(frame_ + FRAME_OFF(0)))
#define local_32c (*(int *)(frame_ + FRAME_OFF(4)))
#define local_328 (*(int *)(frame_ + FRAME_OFF(8)))
#define local_324 (*(i8 (*)[220])(frame_ + FRAME_OFF(12)))
#define local_248 (*(int *)(frame_ + FRAME_OFF(232)))
#define local_30 (*(int *)(frame_ + FRAME_OFF(768)))
#define local_2c (*(int *)(frame_ + FRAME_OFF(772)))
#define local_28 (*(i32 *)(frame_ + FRAME_OFF(776)))
#define local_24 (*(i32 *)(frame_ + FRAME_OFF(780)))
#define local_20 (*(i32 *)(frame_ + FRAME_OFF(784)))
#define local_1c (*(i32 *)(frame_ + FRAME_OFF(788)))
#define local_18 (*(int *)(frame_ + FRAME_OFF(792)))
#define local_14 (*(int *)(frame_ + FRAME_OFF(796)))
#define uStack_10 (*(i32 *)(frame_ + FRAME_OFF(800)))
#define puStack_c (*(i8 * *)(frame_ + FRAME_OFF(804)))
#define local_8 (*(i32 *)(frame_ + FRAME_OFF(808)))
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl net_host_turn_loop(void)

{
  byte bVar1;
  SHORT SVar2;
  i32 uVar3;
  int iVar4;
  i8 frame_[FRAME_OFF(816)] __attribute__((aligned(8)));  /* original stack frame */
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_005ab08b;
  dialog_ctor(local_324,0x4000);
  local_8 = 0;
  iVar4 = DAT_006d1da0;
  uVar3 = civ_name_plural(DAT_006d1da0);
  dbg_logf_str_int(s_Server___s___d__00635c68,uVar3,iVar4);
  for (local_330 = 1; local_330 < 8; local_330 = local_330 + 1) {
    if (((DAT_006d1da0 != local_330) && ((1 << ((byte)local_330 & 0x1f) & (uint)game.civs_alive) != 0))
       && ((1 << ((byte)local_330 & 0x1f) & (uint)game.human_players) != 0)) {
      iVar4 = local_330;
      uVar3 = civ_name_plural(local_330);
      dbg_logf_str_int(s_Client___s___d__00635c78,uVar3,iVar4);
    }
  }
  net_reset_error_counts();
  map_rebuild_unit_flags();
  picwnd_close(&advisor_window);
  picwnd_close(&casualty_window);
  menu_update_states();
  ui_redraw_all_maps(1);
  mapview_update_title(&map_views);
  local_18 = 0;
  for (local_328 = 0; local_328 < game.num_units; local_328 = local_328 + 1) {
    if ((units[local_328].id != 0) &&
       ((char)units[local_328].owner == DAT_006d1da0)) {
      mapview_center_on(&map_views,(int)units[local_328].x,
                         (int)units[local_328].y);
      local_18 = local_18 + 1;
      break;
    }
  }
  if (local_18 == 0) {
    for (local_328 = 0; local_328 < game.num_cities; local_328 = local_328 + 1) {
      if ((cities[local_328].id != 0) &&
         ((char)cities[local_328].owner == DAT_006d1da0)) {
        mapview_center_on(&map_views,(int)cities[local_328].x,
                           (int)cities[local_328].y);
        break;
      }
    }
  }
  bVar1 = turn_resume_civ;
  if (turn_resume_civ != 0) {
    do {
      if ((1 << (turn_resume_civ & 0x1f) & (uint)game.civs_alive) != 0) goto LAB_005aa3dc;
      turn_resume_civ = turn_resume_civ + 1;
      if (turn_resume_civ == 8) {
        turn_resume_civ = 0;
      }
    } while (turn_resume_civ != bVar1);
    game_over_reason = 1;
  }
LAB_005aa3dc:
  do {
    game.human_players = pending_human_players | game.human_players;
    pending_human_players = 0;
    _memset(&net_map_lock_slots,-1,0xc0);
    units_reset_for_turn(0xfffffffd);
    net_send_state_diff(0xff,2,0,0,0);
    XD_FlushSendBuffer(60000);
    while ((net_msgq_priority_count != 0 || (net_msgq_normal_count != 0))) {
      net_process_messages(&DAT_006ad108,1,0);
    }
    game_calc_human_wonder_range();
    if (turn_resume_civ == 0) {
      game_advance_turn(0xfffffffd);
      net_send_state_diff(0xff,2,0,0,0);
      XD_FlushSendBuffer(60000);
    }
    iVar4 = game_check_retirement();
    if ((iVar4 != 0) || (game_over_reason != 0)) {
      game_loop_active = '\0';
      break;
    }
    if ((scenario_events_loaded != 0) && ((turn_resume_civ == 0 || (turn_resume_new_game != 0)))) {
      events_check_turn(&scenario_events,(int)game.turn);
      events_check_turn_interval(&scenario_events,(int)game.turn);
      events_check_random_turn(&scenario_events,(int)game.turn);
      events_check_received_tech(&scenario_events);
      net_send_state_diff(0xff,2,0,0,0);
      XD_FlushSendBuffer(5000);
    }
    game.human_players = (pending_human_players | game.human_players) & (byte)net_claimed_civs_mask;
    pending_human_players = 0;
    net_tile_sync_enabled = 0;
    for (local_330 = 0; (game_loop_active != '\0' && (local_330 < 8)); local_330 = local_330 + 1) {
      game.turn_civ = (byte)local_330;
      if (((1 << ((byte)local_330 & 0x1f) & (uint)game.civs_alive) != 0) &&
         ((1 << ((byte)local_330 & 0x1f) & (uint)game.human_players) == 0)) {
        civ_process_turn(local_330);
        net_send_state_diff(0xff,2,0,0,0);
      }
    }
    net_tile_sync_enabled = 1;
    XD_FlushSendBuffer(60000);
    net_reset_msg_counts();
    for (local_330 = 0; local_330 < 8; local_330 = local_330 + 1) {
      *(i32 *)(&net_civ_phase_done + local_330 * 4) = 0;
    }
    net_send_message(0x8b,0xff,0,0,0,0,0,0,0,0);
    DAT_006d1da0 = (&net_slot_civs)[net_local_slot * 0x15];
    game.player_civ = (byte)DAT_006d1da0;
    game.turn_civ = (byte)DAT_006d1da0;
    if (turn_resume_civ == 0) {
      civ_check_throne_room_upgrade();
    }
    civ_process_turn(DAT_006d1da0);
    net_send_state_diff(0xff,2,0,0,0);
    *(int *)(&net_civ_phase_done + DAT_006d1da0 * 4) = *(int *)(&net_civ_phase_done + DAT_006d1da0 * 4) + 1;
    dlg_pending_idle_callback = ((void *)ADDR(0x00403233, net_host_wait_production_idle));
    popup_game_with_sprite(s_WAITPRODUCTION_00635c88,&popup_info_icon_sprite,0);
    local_2c = 0;
LAB_005aa732:
    if (local_2c == 0) {
      net_process_messages(&DAT_006ad108,1,0);
      if (DAT_006ad308 < 2) {
        local_2c = 1;
        goto LAB_005aa7ee;
      }
      local_2c = 1;
      for (local_330 = 1; local_330 < 8; local_330 = local_330 + 1) {
        if ((((1 << ((byte)local_330 & 0x1f) & (uint)game.civs_alive) != 0) &&
            ((1 << ((byte)local_330 & 0x1f) & (uint)game.human_players) != 0)) &&
           (*(int *)(&net_civ_phase_done + local_330 * 4) == 0)) {
          local_2c = 0;
          break;
        }
      }
      goto LAB_005aa732;
    }
LAB_005aa7ee:
    nm_production_complete_count = 0;
    net_send_state_diff(0xff,2,0,0,0);
    XD_FlushSendBuffer(60000);
    net_send_message(0x8d,0xff,0,0,0,0,0,0,0,0);
    DAT_006d1da0 = (&net_slot_civs)[net_local_slot * 0x15];
    game.player_civ = (byte)DAT_006d1da0;
    net_tile_sync_enabled = 0;
    if (turn_resume_civ == 0) {
      units_reset_for_turn(0xffffffff);
    }
    for (local_330 = 0; (game_loop_active != '\0' && (local_330 < 8)); local_330 = local_330 + 1) {
      if (((1 << ((byte)local_330 & 0x1f) & (uint)game.civs_alive) != 0) &&
         ((1 << ((byte)local_330 & 0x1f) & (uint)game.human_players) == 0)) {
        game.turn_civ = (byte)local_330;
        mp_turn_civ_i32 = local_330;
        menu_update_states();
        status_draw_civ_color(local_330);
        if ((((turn_resume_civ == 0) || (turn_resume_new_game != 0)) && (turn_resume_civ != 0)) &&
           (turn_resume_new_game != 0)) {
          mapview_update_title(&map_views);
          map_redraw_all_views(DAT_006d1da0,1);
          wnd_flush_paint();
        }
        ai_process_civ_units();
      }
    }
    for (local_330 = 0; local_330 < 8; local_330 = local_330 + 1) {
      *(i32 *)(&net_civ_phase_done + local_330 * 4) = 0;
      *(i32 *)(&net_civ_new_player_flags + local_330 * 4) = 0;
    }
    net_send_state_diff(0xff,2,0,0,0);
    net_send_message(0x8e,0xff,0,0,0,0,0,0,0,0);
    XD_FlushSendBuffer(60000);
    game.turn_civ = (byte)DAT_006d1da0;
    net_tile_sync_enabled = 1;
    if (game_loop_active == '\0') {
      net_send_message(0x31,0,0,DAT_006d1da0,0,0,0,0,0,0);
      break;
    }
    if ((*(short *)(&civ_intro_shown + DAT_006d1da0 * 2) == 0) && (autoplay_active == 0)) {
      civ_intro_popup(DAT_006d1da0);
      *(i16 *)(&civ_intro_shown + DAT_006d1da0 * 2) = 1;
    }
    if (mp_turn_time_limit_ms != 0) {
      mp_turn_seconds_left = mp_turn_time_limit_ms / 1000;
      main_view_timer_cache_i32 = 0xffffffff;
    }
    mp_turn_civ_i32 = DAT_006d1da0;
    menu_update_states();
    main_view_timer_cache_i32 = 0xffffffff;
    frame_wnd_draw_caption(&map_views);
    local_28 = main_view_frame_left;
    local_24 = main_view_frame_top;
    local_20 = main_view_frame_right;
    local_1c = main_view_client_top;
    wnd_blit_surface_rect(&map_views,&local_28);
    mapview_update_title(&map_views);
    map_redraw_all_views(DAT_006d1da0,1);
    status_draw_civ_color(DAT_006d1da0);
    local_14 = *(int *)(&casualty_counts + DAT_006d1da0 * 4) -
               *(int *)(&casualty_reported_counts + DAT_006d1da0 * 4);
    if (autoplay_active == 0) {
      dlg_pending_idle_callback = ((void *)ADDR(0x00403c74, turn_popup_timeout_idle));
      uVar3 = civ_leader_title(DAT_006d1da0);
      text_set_string_arg(0,uVar3);
      uVar3 = civ_leader_name(DAT_006d1da0);
      text_set_string_arg(1,uVar3);
      if (*(int *)(&casualty_reported_counts + DAT_006d1da0 * 4) < *(int *)(&casualty_counts + DAT_006d1da0 * 4)) {
        *(i32 *)(&casualty_reported_counts + DAT_006d1da0 * 4) =
             *(i32 *)(&casualty_counts + DAT_006d1da0 * 4);
        text_set_number_arg(0,local_14);
        if (local_14 == 1) {
          dialog_load_text_noflags(local_324,&DAT_006359d4,s_CASUALTY_00635c98);
        }
        else {
          dialog_load_text_noflags(local_324,&DAT_006359d4,s_CASUALTIES_00635ca4);
        }
        dialog_add_sprite(local_324,&popup_info_icon_sprite,0,0);
        dialog_set_image_zoom(local_324,0);
        input_flush_events();
        snd_play_effect(0x30,0,0,0);
        dlg_show_modal(local_324,0);
        if (local_248 != 0) {
          casualty_timeline_show(DAT_006d1da0);
        }
      }
      else {
        dialog_load_text_noflags(local_324,&DAT_006359d4,s_OURTURNTOMOVE_00635cb0);
        dialog_add_sprite(local_324,&popup_info_icon_sprite,0,0);
        dialog_set_image_zoom(local_324,0);
        input_flush_events();
        snd_play_effect(0x30,0,0,0);
        dlg_show_modal(local_324,0);
      }
    }
    if (autoplay_active == 0) {
      game_turn_start_popups();
      if (mp_turn_time_limit_ms != 0) {
        mp_turn_timer_start(1);
      }
      game_player_move_loop();
    }
    else {
      saved_human_players_i32 = (uint)game.human_players;
      game.human_players = 0;
      if (mp_turn_time_limit_ms != 0) {
        mp_turn_timer_start(1);
      }
      ai_process_civ_units();
      game.human_players = saved_human_players;
      SVar2 = GetAsyncKeyState(0x1b);
      if (((int)SVar2 & 0x8001U) != 0) {
        autoplay_turns_left = 1;
      }
      autoplay_turns_left = autoplay_turns_left + -1;
      if (autoplay_turns_left == 0) {
        autoplay_active = 0;
      }
    }
    if (mp_turn_time_limit_ms != 0) {
      mp_turn_timer_stop(1);
    }
    status_redraw(1);
    net_send_state_diff(0xff,2,0,0,0);
    saved_turn_civ = 0;
    turn_resume_civ = 0;
    saved_resume_new_game = 0;
    turn_resume_new_game = 0;
    game.field_06 = game.field_06 & 0xfffe;
    *(int *)(&net_civ_phase_done + DAT_006d1da0 * 4) = *(int *)(&net_civ_phase_done + DAT_006d1da0 * 4) + 1;
    XD_FlushSendBuffer(60000);
    dlg_pending_idle_callback = ((void *)ADDR(0x004030ee, net_host_wait_human_moves_idle));
    popup_game_with_sprite(s_WAITHUMANMOVES_00635cc0,&popup_info_icon_sprite,0);
    local_30 = 0;
LAB_005aae35:
    if (local_30 == 0) {
      net_process_messages(&DAT_006ad108,1,0);
      if (DAT_006ad308 < 2) {
        local_30 = 1;
        goto LAB_005aaef1;
      }
      local_30 = 1;
      for (local_330 = 1; local_330 < 8; local_330 = local_330 + 1) {
        if ((((1 << ((byte)local_330 & 0x1f) & (uint)game.civs_alive) != 0) &&
            ((1 << ((byte)local_330 & 0x1f) & (uint)game.human_players) != 0)) &&
           (*(int *)(&net_civ_phase_done + local_330 * 4) == 0)) {
          local_30 = 0;
          break;
        }
      }
      goto LAB_005aae35;
    }
LAB_005aaef1:
    nm_human_move_complete_count = 0;
    net_check_lost_connections();
    if ((player_has_quit == '\0') || (mp_turn_civ_i32 == DAT_006d1da0)) {
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
#undef scenario_events_loaded
#undef game_loop_active
#undef turn_resume_civ
#undef turn_resume_new_game
#undef dlg_pending_idle_callback
#undef game_over_reason
#undef mp_turn_time_limit_ms
#undef saved_turn_civ
#undef saved_resume_new_game
#undef autoplay_active
#undef autoplay_turns_left
#undef net_claimed_civs_mask
#undef saved_human_players
#undef DAT_006ad108
#undef net_local_slot
#undef DAT_006ad308
#undef net_slot_civs
#undef mp_turn_civ
#undef player_has_quit
#undef net_tile_sync_enabled
#undef nm_production_complete_count
#undef nm_human_move_complete_count
#undef DAT_006d1da0
#undef main_view_timer_cache_i32
#undef saved_human_players_i32
#undef mp_turn_civ_i32
#undef local_330
#undef local_32c
#undef local_328
#undef local_324
#undef local_248
#undef local_30
#undef local_2c
#undef local_28
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14
#undef uStack_10
#undef puStack_c
#undef local_8

/* 0x0055f5a3: pick a starting/setup choice for civ param_1 by scoring options
 * 1..n with civ_can_choose_government and taking the best score (ties go to the later one).
 * Ghidra lost the stack frame and passed garbage register/stack values to
 * civ_can_choose_government; the real call is civ_can_choose_government(civ, i). */
#define g_flags_655af0  (*(ushort *)((u8 *)&game + 8))
#define g_flags_64bc60  (*(ushort *)((u8 *)&g.d_0064bc60))
#define g_player_civ    (*(char *)((u8 *)&game + 27))
void __cdecl ai_choose_government(int param_1, int param_2)
{
    int count;          /* EBP-4 */
    int best_score;     /* EBP-8 */
    int diff;           /* EBP-0xc */
    int i;              /* EBP-0x10 */
    int best;           /* EBP-0x14 */

    if ((g_flags_655af0 & 0x80) != 0 && ((short)g_flags_64bc60 & 0x10) != 0 &&
        (byte)civs[param_1].government >= 1)
        return;
    count = 6;
    if (param_2 != 0) {
        count--;
        if (_rand() % 3 != 0)
            count--;
    }
    if ((g_flags_655af0 & 1) != 0) {
        diff = (uint)(byte)civs[g_player_civ].num_advances -
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
#undef g_flags_655af0
#undef g_flags_64bc60
#undef g_player_civ
